# ROS2 with PCL

* 구동 환경 ubuntu로 변경

```
"/opt/ros/foxy/include",
"/usr/local/include/pcl-1.12",
"/usr/include/eigen3"
```

## install

```bash
sudo apt-get install ros-humble-pcl-ros ros-humble-pcl-conversions ros-humble-pcl-msgs pcl-ros-tools
```

## Project

```bash
ros2 pkg create --build-type ament_cmake ros2pcl_test --dependencies rclcpp std_msgs sensor_msgs pcl_conversions pcl_apps-1.12
```

- --build-type : 빌드 시스템 설정
  - ament_cmake : catkin의 업그레이드 버전

## build

### humble version

```bash
rosdep install -i --from-path src --rosdistro humble -y
colcon build --packages-select ros2pcl_test --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release 
```

### foxy version

```bash
rosdep install -i --from-path src --rosdistro foxy -y
colcon build --packages-select ros2pcl_test --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release 
```
