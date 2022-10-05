aux_source_directory(. SERVER_SRCS)

include_directories(./include)

add_executable(server ${SERVER_SRCS})

target_link_libraries(server
    thread
)