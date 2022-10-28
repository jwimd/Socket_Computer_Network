aux_source_directory(. DATA_SRCS)

include_directories(./include)

add_library(data ${DATA_SRCS})

find_package(Threads REQUIRED)

target_link_libraries(data
    thread
    Threads::Threads
)