cmake_minimum_required(VERSION 3.10)
project(knotc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -O2)

# Include Matplot++
add_subdirectory(include/external/matplotplusplus)

# Gather source files
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Optional: Uncomment these if you're using these files
# set(EXTERNAL_SOURCES
#     ${PROJECT_SOURCE_DIR}/include/external/pbPlots.cpp
#     ${PROJECT_SOURCE_DIR}/include/external/supportLib.cpp
# )

# Create the executable
add_executable(knotc ${SRC_FILES} ${EXTERNAL_SOURCES} "include/evaluate.hpp" "src/evaluate.cpp" "src/plot.cpp")

# Set output directory
set_target_properties(knotc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build
)

# Link libraries
target_link_libraries(knotc PRIVATE matplot)

# Include directories
target_include_directories(knotc PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/external
    ${PROJECT_SOURCE_DIR}/include/external/matplotplusplus/include
)
