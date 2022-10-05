aux_source_directory(. THREAD_SRCS)

include_directories(./include)

add_library(thread ${THREAD_SRCS})

find_package(Threads REQUIRED)

target_link_libraries(thread
    Threads::Threads
)