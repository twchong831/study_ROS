#ifndef __ROSNODE_H__
#define __ROSNODE_H__

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
	sensor_msgs::msg::PointCloud2 convertPointCloud2Msg(PointCloudT::Ptr points_)
	{
		sensor_msgs::msg::PointCloud2 msg;
		pcl::toROSMsg(*points_, msg);

		return msg;
	}

	PointCloudT::Ptr generatePointCloud()
	{
		PointCloudT::Ptr points_(new PointCloudT);
		PointT pt_;

		for (uint x = 0; x < 10; x++)
		{
			for (uint y = 0; y < 10; y++)
			{
				for (uint z = 0; z < 10; z++)
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
		if (cnt_ > 0)
		{
			cnt_ = 0;
		}

		return points_;
	}

	void timer_callback()
	{
		auto laser2pc = generatePointCloud();
		auto pc_msg = convertPointCloud2Msg(laser2pc);
		pc_pub_->publish(pc_msg);
	}

	/* data */
	std::vector<float> robot_pose_;
	PointCloudT::Ptr pointcloud_;
	// std::vector<float> scan_data_;

	std_msgs::msg::Header cur_header;
	float r_max;

	rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pc_pub_;
	rclcpp::TimerBase::SharedPtr timer_;

	int cnt_;

public:
	rosNode(/* args */) : rclcpp::Node("kanvi_hlk_sub")
	{
		robot_pose_.resize(3);

		// subscription data at odom and laser
		std::function<void(const nav_msgs::msg::Odometry::SharedPtr)> odom_callback = [this](const nav_msgs::msg::Odometry::SharedPtr _odom) -> void
		{
			robot_pose_[0] = _odom->pose.pose.position.x;
			robot_pose_[1] = _odom->pose.pose.position.y;
			robot_pose_[2] = _odom->pose.pose.position.z;
		};

		pc_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("myPC", 10);

		timer_ = this->create_wall_timer(30ms, std::bind(&rosNode::timer_callback, this));

		cnt_ = 0;
	}
	~rosNode();
};
#endif // __ROSNODE_H__