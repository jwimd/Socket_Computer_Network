include_directories(./include)

aux_source_directory(. CLIENT_SRCS)

add_executable(client ${CLIENT_SRCS})