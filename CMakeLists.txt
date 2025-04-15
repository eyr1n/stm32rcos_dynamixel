cmake_minimum_required(VERSION 3.22)

project(stm32rcos_dynamixel LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(dynamixel_sdk
  GIT_REPOSITORY https://github.com/ROBOTIS-GIT/DynamixelSDK.git
  GIT_TAG 3.8.3
)
FetchContent_MakeAvailable(dynamixel_sdk)

add_library(${PROJECT_NAME} OBJECT
  ${dynamixel_sdk_SOURCE_DIR}/c++/src/dynamixel_sdk/group_bulk_read.cpp
  ${dynamixel_sdk_SOURCE_DIR}/c++/src/dynamixel_sdk/group_bulk_write.cpp
  ${dynamixel_sdk_SOURCE_DIR}/c++/src/dynamixel_sdk/group_sync_read.cpp
  ${dynamixel_sdk_SOURCE_DIR}/c++/src/dynamixel_sdk/group_sync_write.cpp
  ${dynamixel_sdk_SOURCE_DIR}/c++/src/dynamixel_sdk/group_fast_bulk_read.cpp
  ${dynamixel_sdk_SOURCE_DIR}/c++/src/dynamixel_sdk/group_fast_sync_read.cpp
  ${dynamixel_sdk_SOURCE_DIR}/c++/src/dynamixel_sdk/group_handler.cpp
  ${dynamixel_sdk_SOURCE_DIR}/c++/src/dynamixel_sdk/packet_handler.cpp
  ${dynamixel_sdk_SOURCE_DIR}/c++/src/dynamixel_sdk/protocol1_packet_handler.cpp
  ${dynamixel_sdk_SOURCE_DIR}/c++/src/dynamixel_sdk/protocol2_packet_handler.cpp
  src/port_handler.cpp
)
target_link_libraries(${PROJECT_NAME} PUBLIC
  stm32rcos
)
target_include_directories(${PROJECT_NAME} PUBLIC
  ${dynamixel_sdk_SOURCE_DIR}/c++/include/dynamixel_sdk
  include
)
target_compile_definitions(${PROJECT_NAME} PUBLIC
  ARDUINO
)