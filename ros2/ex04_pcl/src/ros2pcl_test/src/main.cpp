#include <iostream>
#include <stdio.h>
#include <chrono>

// PCL
#include <pcl-1.12/pcl/point_types.h>
#include <pcl-1.12/pcl/conversions.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl-1.12/pcl/point_cloud.h>

// ROS2
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/PointCloud2.h"

typedef pcl::PointCloud<pcl::PointXYZRGB>	PointCloudT;

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	RCLCPP_INFO(rclcpp::get_logger("ros2pclTest"), "Hello, World");

	rmw_qos_profile_t custom_qos_profile = rmw_qos_profile_default;

	custom_qos_profile.depth = 1;
	custom_qos_profile.reliability = RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT;
	custom_qos_profile.history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;

	rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("ros2pclTest");
	rclcpp::Publisher<sensor_msgs::PointCloud2>::SharedPtr pub_pointcloud;
	pub_pointcloud = node->create_publisher<sensor_msgs::PointCloud2>("points2", custom_qos_profile);

	// PCL point cloud
	pcl::PointXYZRGB point;
	PointCloudT::Ptr pointcloud(new PointCloudT);

	for(uint i=0; i<100; i++)
	{
		point.x = (float)i/100;
		point.y = (float)i/100;
		point.z = (float)i/100;
		point.r = 255;
		point.g = 0;
		point.b = 0;

		pointcloud->push_back(point);
	}

	// pcl to ros2 msg
	sensor_msgs::PointCloud2 msg;
	pcl::toROSMsg(*pointcloud, msg);

	RCLCPP_INFO(rclcpp::get_logger("ros2pclTest"), "Check Point CLoud Size : %d", pointcloud->size());

	rclcpp::shutdown();
	return 0;
}