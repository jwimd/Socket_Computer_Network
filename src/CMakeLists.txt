cmake_minimum_required(VERSION 3.0.0)

project(socket_project VERSION 1.0.0)

include_directories(./include)
include_directories(./server/include)
include_directories(./client/include)
include_directories(./thread/include)
include_directories(./data/include)

add_subdirectory(thread)
add_subdirectory(data)
add_subdirectory(server)
add_subdirectory(client)

find_package(Threads REQUIRED)