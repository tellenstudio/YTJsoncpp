cmake_minimum_required(VERSION 3.4.1)

include_directories(${PROJECT_SOURCE_DIR}/jsoncpp)

set(APP_SRCS main.cpp)

add_executable(app ${APP_SRCS})

target_link_libraries(app jsoncpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
