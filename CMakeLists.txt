cmake_minimum_required(VERSION 3.19)
project(rocksdb_play)

set(CMAKE_CXX_STANDARD 17)


message(STATUS "${CMAKE_SOURCE_DIR}")

INCLUDE_DIRECTORIES(
        ${CMAKE_SOURCE_DIR}/include/rocksdb
        ${CMAKE_SOURCE_DIR}/util
        ${CMAKE_SOURCE_DIR}/db/db_impl
        ${CMAKE_SOURCE_DIR}/db
)

add_executable(rocksdb_play main.cpp)