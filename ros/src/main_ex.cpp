#include <ros/ros.h>
#include <iostream>

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <chrono>
#include <Eigen/Eigen>
#include <array>
#include <typeinfo>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>

typedef pcl::PointCloud<pcl::PointXYZRGB>	PointCloudT;

int main(int argc, char* argv[])
{
	/*---define ROS----*/
	ros::init(argc, argv, "NODE_NAME");	//ros init
	ros::Publisher pub;					//define publisher 
	ros::NodeHandle nh;					//define Node handler
	ros::Rate loop_rate(30);			//define loop Hz

	pub = nh.advertise<sensor_msgs::PointCloud2>("/topic_name", 1);
	// "/topic_name"

	PointCloudT cloud;		//define pointcloud structure.

	while(ros::ok())
	{
		//processing SOMETHIGS....
		///-----------------------

		pub.publish(cloud_to_cloud_msg(cloud.width, cloud.height, cloud, 100, "fixed_name"));

		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}