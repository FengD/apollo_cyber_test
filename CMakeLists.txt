cmake_minimum_required(VERSION 2.8)

project(cyber_test)

include_directories(/apollo/cyber/include)
link_directories(/apollo/cyber/lib)

find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()

add_executable(${PROJECT_NAME}_talker talker.cc)
target_link_libraries(${PROJECT_NAME}_talker 
    gflags
    glog
    pthread
    rt
    ${PROTOBUF_LIBRARIES}
    sensor_proto
    cyber
    fastrtps
)