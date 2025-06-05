cmake_minimum_required(VERSION 3.14)  
project(knotc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -O2)

include(FetchContent)

FetchContent_Declare(
    matplotplusplus
    GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus.git
    GIT_TAG master
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/include/external/matplotplusplus
)

FetchContent_MakeAvailable(matplotplusplus)

# Source files
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(knotc ${SRC_FILES} "include/evaluate.hpp" "src/evaluate.cpp" "src/plot.cpp")

set_target_properties(knotc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build
)

target_link_libraries(knotc PRIVATE matplot)

target_include_directories(knotc PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/external
)
