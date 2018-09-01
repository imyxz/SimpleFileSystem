cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project (SimpleFileSystem)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_compile_options(-std=c++11)
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/inode)
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/content)
aux_source_directory (. DIR_SRCS)
add_executable(SimpleFileSystem ${DIR_SRCS})

