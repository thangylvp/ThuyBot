cmake_minimum_required(VERSION 2.8.3)
project(ThuyBot_Camera)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  image_transport
  cv_bridge
  sensor_msgs
  std_msgs
)


find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

catkin_package()
include_directories(${catkin_INCLUDE_DIRS})

add_executable(TB_CamItf src/main.cpp)
target_link_libraries(TB_CamItf ${catkin_LIBRARIES} ${OpenCV_LIBS})


