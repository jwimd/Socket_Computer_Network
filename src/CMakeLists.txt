cmake_minimum_required(VERSION 3.0.0)

project(socket_project VERSION 0.1.0)

include_directories(./include)
include_directories(./server/include)
include_directories(./client/include)
include_directories(./thread/include)

add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(thread)