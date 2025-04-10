cmake_minimum_required(VERSION 3.22)

project(stm32rcos_dynamixel LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME} INTERFACE
  DynamixelSDK/c++/src/dynamixel_sdk/group_bulk_read.cpp
  DynamixelSDK/c++/src/dynamixel_sdk/group_bulk_write.cpp
  DynamixelSDK/c++/src/dynamixel_sdk/group_sync_read.cpp
  DynamixelSDK/c++/src/dynamixel_sdk/group_sync_write.cpp
  DynamixelSDK/c++/src/dynamixel_sdk/group_fast_bulk_read.cpp
  DynamixelSDK/c++/src/dynamixel_sdk/group_fast_sync_read.cpp
  DynamixelSDK/c++/src/dynamixel_sdk/group_handler.cpp
  DynamixelSDK/c++/src/dynamixel_sdk/packet_handler.cpp
  DynamixelSDK/c++/src/dynamixel_sdk/protocol1_packet_handler.cpp
  DynamixelSDK/c++/src/dynamixel_sdk/protocol2_packet_handler.cpp
  src/port_handler.cpp
)

target_include_directories(${PROJECT_NAME} INTERFACE
  DynamixelSDK/c++/include/dynamixel_sdk
  include
)

target_compile_definitions(${PROJECT_NAME} INTERFACE
  ARDUINO
)