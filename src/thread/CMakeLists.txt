include_directories(./include)

aux_source_directory(. THREAD_SRCS)

add_library(thread ${THREAD_SRCS})