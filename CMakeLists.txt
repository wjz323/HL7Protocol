cmake_minimum_required(VERSION 3.0.0)
project(NSwap VERSION 0.1.0)

include(CTest)
enable_testing()


add_compile_options(-std=c++11 -Wall -Wextra -Wpedantic)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC swap)

target_include_directories(${PROJECT_NAME} PUBLIC
                           ${PROJECT_BINARY_DIR}
                           ${PROJECT_SOURCE_DIR}/src
                           )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
