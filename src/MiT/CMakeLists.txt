
# include the MiT specific macros
include(${PROJECT_SOURCE_DIR}/cmake/Macros.cmake)

# add the MiT sources path
include_directories(${PROJECT_SOURCE_DIR}/src)

# define the path our additional CMake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/")

# set the output directory for MiT libraries
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

# add the modules subdirectories
add_subdirectory(Parser)
