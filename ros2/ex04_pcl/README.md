# ROS2 with PCL

## install

```bash
sudo apt-get install ros-humble-pcl-ros ros-humble-pcl-conversions ros-humble-pcl-msgs pcl-ros-tools
```

## Project

```bash
ros2 pkg create --build-type ament_cmake ros2pcl_test --dependencies rclcpp std_msgs sensor_msgs pcl_conversions pcl_apps-1.12pkg-
```

- --build-type : 빌드 시스템 설정
	- ament_cmake : catkin의 업그레이드 버전
