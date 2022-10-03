include_directories(./include)

aux_source_directory(. SERVER_SRCS)

add_executable(server ${SERVER_SRCS})