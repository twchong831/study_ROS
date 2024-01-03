#include <iostream>
#include <stdio.h>

// PCL
#include <pcl-1.12/pcl/point_types.h>
#include <pcl-1.12/pcl/conversions.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl-1.12/pcl/point_cloud.h>

// ROS2
#include "rclcpp/rclcpp.hpp"

typedef pcl::PointCloud<pcl::PointXYZRGB>	PointCloudT;

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);

	RCLCPP_INFO(rclcpp::get_logger("ros2pclTest"), "Hello, World");

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
	sensor_msgs::msg::PointCloud2 msg;
	pcl::toROSMsg(*pointcloud, msg);

	RCLCPP_INFO(rclcpp::get_logger("ros2pclTest"), "Check Point CLoud Size : %d", pointcloud->size());

	rclcpp::shutdown();
	return 0;
}