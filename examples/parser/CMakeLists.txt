
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples/parser)

# all source files
set(SRC ${SRCROOT}/main.cpp)

# define the path our additional CMake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/")

# Add Eigen library
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

SET(CMAKE_CXX_FLAGS "-std=c++11")

# define the parser target
mit_add_example(parser 
  SOURCES ${SRC} 
  DEPENDS mit-parser)
