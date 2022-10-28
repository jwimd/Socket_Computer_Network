aux_source_directory(. SERVER_SRCS)

include_directories(./include)

add_executable(server ${SERVER_SRCS})

find_package(Threads REQUIRED)

target_link_libraries(server
    thread
    data
    Threads::Threads
)