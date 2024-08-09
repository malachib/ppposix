cmake_minimum_required(VERSION 3.19)
project(ppposix)

add_library(${PROJECT_NAME} INTERFACE
    posix/epoll.hpp
    posix/socket.hpp)

target_include_directories(${PROJECT_NAME} INTERFACE .)
target_include_directories(${PROJECT_NAME} INTERFACE posix)
