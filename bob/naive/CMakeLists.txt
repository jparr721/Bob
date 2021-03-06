cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(BobNaive VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Threads REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME}
  "${PROJECT_SOURCE_DIR}/src/main.cc"
  "${PROJECT_SOURCE_DIR}/src/naive.cc"
)

target_link_libraries(
  ${PROJECT_NAME}
  BobCore
  Eigen3::Eigen
  ${CMAKE_THREAD_LIBS_INIT}
)
