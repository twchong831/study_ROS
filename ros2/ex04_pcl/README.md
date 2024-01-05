# ROS2 with PCL

- 구동 환경 ubuntu로 변경

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

## configuration

### CMakeLists.txt

```bash
cmake_minimum_required(VERSION 3.8)
project(ros2pcl_test)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(PCL 1.12 REQUIRED)
find_package(pcl_conversions REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(ros2pcl_test src/main.cpp)

ament_target_dependencies(ros2pcl_test rclcpp pcl_conversions)
target_link_libraries( ros2pcl_test ${PCL_LIBRARIES} )

install(TARGETS ros2pcl_test
		DESTINATION lib/${PROJECT_NAME})

ament_package()

```

### package.xml

```xml
<?xml version="1.0"?>
<?xml-model href="http://download.ros.org/schema/package_format3.xsd" schematypens="http://www.w3.org/2001/XMLSchema"?>
<package format="3">
  <name>ros2pcl_test</name>
  <version>0.0.0</version>
  <description>TODO: Package description</description>
  <maintainer email="">tw</maintainer>
  <license>TODO: License declaration</license>

  <buildtool_depend>ament_cmake</buildtool_depend>

  <depend>rclcpp</depend>
  <depend>std_msgs</depend>
  <depend>sensor_msgs</depend>
  <depend>pcl_conversions</depend>

  <test_depend>ament_lint_auto</test_depend>
  <test_depend>ament_lint_common</test_depend>

  <export>
    <build_type>ament_cmake</build_type>
  </export>
</package>

```
