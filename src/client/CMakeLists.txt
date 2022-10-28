include_directories(./include)

aux_source_directory(. CLIENT_SRCS)

add_executable(client ${CLIENT_SRCS})

find_package(Threads REQUIRED)

target_link_libraries(client
    thread
    data
    Threads::Threads
)