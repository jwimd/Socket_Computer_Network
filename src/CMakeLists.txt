cmake_minimum_required(VERSION 3.0.0)
project(socket_project VERSION 0.1.0)

include_directories(./include)

add_subdirectory(server)
add_subdirectory(client)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})