cmake_minimum_required(VERSION 2.8)

project(cyber_test)

include_directories(/usr/local/apollo/cyber/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
link_directories(/usr/local/apollo/cyber/lib)

find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()

file(GLOB proto_srcs *.proto)
set(Protobuf_USE_STATIC_LIBS on)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${proto_srcs})

add_executable(${PROJECT_NAME}_talker talker.cc ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(${PROJECT_NAME}_talker 
    gflags
    glog
    pthread
    rt
    ${PROTOBUF_LIBRARIES}
    cyber
    fastrtps
)

add_executable(${PROJECT_NAME}_listener listener.cc ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(${PROJECT_NAME}_listener 
    gflags
    glog
    pthread
    rt
    ${PROTOBUF_LIBRARIES}
    cyber
    fastrtps
)