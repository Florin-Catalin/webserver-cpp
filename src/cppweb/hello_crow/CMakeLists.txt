cmake_minimum_required(VERSION 3.7)

project(hello_crow)

set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(hello_crow main.cpp)
target_link_libraries(hello_crow ${BoostLIBRARIES} Threads::Threads)
