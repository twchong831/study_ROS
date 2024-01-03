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
# find_package(pcl_apps-1.12 REQUIRED)

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

# include_directories( ${PCL_INCLUDE_DIRS} )
# add_definitions( ${PCL_DEFINITIONS} )
# link_directories( ${PCL_LIBRARY_DIRS} )

add_executable(ros2pcl_test src/main.cpp)

ament_target_dependencies(ros2pcl_test rclcpp)
target_link_libraries( ros2pcl_test ${PCL_LIBRARIES} )

install(TARGETS ros2pcl_test
		DESTINATION lib/${PROJECT_NAME})

ament_package()
