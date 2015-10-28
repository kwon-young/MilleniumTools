
set(INCROOT ${PROJECT_SOURCE_DIR}/include/MiT/Parser)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/MiT/Parser)

# all source files
file(
  GLOB_RECURSE
  SRC
  ${SRCROOT}/*
  )
file(
  GLOB_RECURSE
  HEAD
  ${INCROOT}/*
  )
source_group("" FILES ${SRC} ${HEAD})

## find external libraries
#find_package(OpenMP MODULE)

# Add Eigen library
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

SET(CMAKE_CXX_FLAGS "-std=c++11")

# define the mit-parser target
mit_add_library(
  mit-parser
  SOURCES ${SRC} ${HEAD}
  )
