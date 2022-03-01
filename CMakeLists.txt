cmake_minimum_required(VERSION 3.0.2)
project(ServerSerena)
file(GLOB CPPS "*.cpp")
add_executable(${PROJECT_NAME} ${CPPS})