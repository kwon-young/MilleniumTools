
cmake_minimum_required(VERSION 2.6)

# Project declaration
project(MilleniumTools CXX C)

set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

option(BUILD_SHARED_LIBS "Build shared libs" OFF)

# Add Eigen library
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# Adding project include directory
include_directories(include)

# Generate list of source file
file(
  GLOB_RECURSE
  source_files
  src/*
  )

file(
  GLOB_RECURSE
  header_files
  include/*
  )

# Executable declaration
add_library(
  ${CMAKE_PROJECT_NAME}
  ${source_files}
  ${header_files}
  )

