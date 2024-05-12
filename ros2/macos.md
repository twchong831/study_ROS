# ROS2 in Macos

[install guide](https://docs.ros.org/en/crystal/Installation/macOS-Install-Binary.html)

## install

```bash
brew install python3

# install asio and tinyxml2 for Fast-RTPS
brew install asio tinyxml2

# install dependencies for robot state publisher
brew install tinyxml eigen pcre poco

# OpenCV isn't a dependency of ROS 2, but it is used by some demos.
brew install opencv

# install OpenSSL for DDS-Security
brew install openssl

# install Qt for RViz
brew install qt freetype assimp

# install dependencies for rcl_logging_log4cxx
brew install log4cxx
```

### download

[link](https://github.com/ros2/ros2/releases)

- download ros2-iron-20240423-linux-rhel9-amd64.tar.bz2
- unpacked package

```bash
mkdir -p ~/ros2_iron
cd ~/ros2_iron
tar xf ros2-[].tar.bz2
```

### setup

```bash
cd ~/ros2_iron/ros2-linux
chmod +x setup.*
chmod +x local_setup.*
./setup.bash
```

#### result

```bash
[rti_connext_dds_cmake_module][warning] No RTI Connext DDS installation specified.. RTI Connext DDS will not be available at runtime,unless you already configured DYLD_LIBRARY_PATH manually.
```
- macos의 system integrity protection 때문에 DYLD_LIBRARY_PATH 등의 환경 변수 등이 작동하지 않을 시에는 SIP가 작동 중인지 확인하고 이를 disable해야 함.[참조](https://ikaros79.tistory.com/entry/macOS%EC%97%90-ROS-2-%EC%84%A4%EC%B9%98%ED%95%98%EA%B8%B0)

```bash
csrutil status
# result
## System Integrity Protection status: enabled.
```

- failed...