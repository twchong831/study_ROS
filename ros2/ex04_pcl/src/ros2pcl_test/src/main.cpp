// #include "rosNode/rosNode.h"

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <memory>

// PCL
#include <pcl/point_types.h>
#include <pcl/conversions.h>
#include <pcl/point_cloud.h>

// ROS2
#include <rclcpp/rclcpp.hpp>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/msg/point_cloud2.h>
#include <sensor_msgs/point_cloud_conversion.hpp>
#include <nav_msgs/msg/odometry.hpp>

typedef pcl::PointXYZRGB PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

using namespace std::chrono_literals;

class rosNode : public rclcpp::Node
{
private:
	// FUNC.
	
	/// @brief convert pcl::PointCloud to sensor_msgs::msg::PointCloud2
	/// @param points_ pcl::PointCloud<pcl::PointXYZRGB>::Ptr
	/// @return sensor::msgs::msg::PointCloud2
	sensor_msgs::msg::PointCloud2 convertPointCloud2Msg(PointCloudT::Ptr points_)
	{
		sensor_msgs::msg::PointCloud2 msg;

		// convert pointcloud to ros2 msg
		pcl::toROSMsg(*points_, msg);

		// set ros2 msg frame ID
		msg.header.set__frame_id("map");	// rviz의 fixed frame를 따라가야함
		// rclcpp::Time now = this->get_clock()->now();

		// set ros2 msg timestamp
		msg.header.set__stamp(this->get_clock()->now());

		return msg;
	}

	/// @brief generate example Pointcloud
	/// @return 
	PointCloudT::Ptr generatePointCloud()
	{
		PointCloudT::Ptr points_(new PointCloudT);
		PointT pt_;

		int size_ = 10;

		if(cnt_%2 != 0)
		{
			size_ = 20;
		}

		for (uint x = 0; x < size_; x++)
		{
			for (uint y = 0; y < size_; y++)
			{
				for (uint z = 0; z < size_; z++)
				{
					if (cnt_ % 2 == 0)
					{
						pt_.x = (float)x / 10;
						pt_.y = (float)y / 10;
						pt_.z = (float)z / 10;
						pt_.r = 255;
						pt_.g = 0;
						pt_.b = 0;
					}
					else
					{
						pt_.x = (float)x / 5;
						pt_.y = (float)y / 5;
						pt_.z = (float)z / 5;
						pt_.r = 0;
						pt_.g = 255;
						pt_.b = 0;
					}

					points_->push_back(pt_);
				}
			}
		}

		cnt_++;
		if (cnt_ > 10)
		{
			cnt_ = 0;
		}

		return points_;
	}

	/// @brief func. using timer
	void timer_callback()
	{
		// generate example pointcloud
		auto laser2pc = generatePointCloud();

		// convert pointcloud to ros2 msg format
		auto pc_msg = convertPointCloud2Msg(laser2pc);

		// log : check pointcloud size & ros2 msg data size
		RCLCPP_INFO(rclcpp::get_logger(pc_pub_->get_topic_name()), "MSG Size : %d -> %d", laser2pc->size(), pc_msg.data.size());

		// log : check ros2 msg header : frame ID 
		RCLCPP_INFO(rclcpp::get_logger(pc_pub_->get_topic_name()), "Chekc MSG HEADER - Frame ID : %s", pc_msg.header.frame_id.c_str());
		
		// log : check ros2 msg header : timestamp 
		RCLCPP_INFO(rclcpp::get_logger(pc_pub_->get_topic_name()), "Chekc MSG HEADER - TimeStamp : %u.%u sec", pc_msg.header.stamp.sec, pc_msg.header.stamp.nanosec);

		// publish ros2 msg for pointcloud
		pc_pub_->publish(pc_msg);
	}

	/* data */
	// pointcloud
	PointCloudT::Ptr pointcloud_;

	// ros2 msg publisher
	rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pc_pub_;

	// ros2 timer
	rclcpp::TimerBase::SharedPtr timer_;

	int cnt_;

public:
	rosNode(/* args */) : rclcpp::Node("kanvi_hlk_sub")
	{
		// set QoS method
		auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
		// auto qos_profile2 = rclcpp::QoS(rclcpp::SystemDefaultsQoS);

		// define publisher
		// set topic name & QoS method
		pc_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("points", qos_profile);

		// define timer
		// timer activate every 30ms
		timer_ = this->create_wall_timer(30ms, std::bind(&rosNode::timer_callback, this));

		cnt_ = 0;
	}
	// ~rosNode();
};

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<rosNode>());
	rclcpp::shutdown();

	return 0;
}