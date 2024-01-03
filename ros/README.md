# Robot Operating System Build ENV

## 레포지토리 설정

```powershell
sudo apt-get install curl
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
curl -s  https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
# curl -sSL 'http://keyserver.ubuntu.com/pks/lookup?op=get&search=0xC1CF6E31E6BADE8868B172B4F42ED6FBAB17C654' | sudo apt-key add – 
```

## 패키지 설치

```powershell
sudo apt update
sudo apt-get install ros-noetic-desktop-full # ubuntu version
sudo apt install python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential
```

## 환경 변수 세팅

```powershell
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

## rosdep 초기화

```powershell
sudo rosdep init
rosdep update
```

## ROS 환경 변수 확인

```powershell
printenv | grep ROS
```

## 작업 공간 생성

```powershell
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws
catkin_make # catkin ROS make command
```

## 환경 변수 설정

```powershell
echo echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
```

## 실행

```powershell
roscore &
rosrun [패키지 이름] [노드 이름]
rviz
```

## How to make ROS project

```powershell
cd ~/catkin_ws
catkin_create_pkg ros_node_test std_msgs roscpp rospy message_generation pcl_conversions pcl_ros libpcl-all-dev visualization_msgs
# catkin_create_pkg [Node name] [pkg lists] [...]
```

* [Node name]을 가지는 폴더가 생성됨.
* 해당 폴더 내의 CMakeLists.txt 파일과 package.xml을 알맞게 수정
* src를 수정하여 node 기능 완성

### make

```powershell
catkin_make
```
