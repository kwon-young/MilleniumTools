
cmake_minimum_required(VERSION 2.8.3)

# Define a macro that helps defining an option
macro(mit_set_option var default type docstring)
  if(NOT DEFINED ${var})
    set(${var} ${default})
  endif()
  set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# determine whether to create a debug or release build
mit_set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release)")

# Project declaration
project(MilleniumTools)

# include the configuration file
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)
# setup version numbers
set(VERSION_MAJOR 0)

# Adding MiT include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# add an option for choosing the build type (shared or static)
mit_set_option(BUILD_SHARED_LIBS FALSE BOOL "TRUE to build MiT as shared library, FALSE to build it as static libraries")

# add an option for build the examples
mit_set_option(MiT_BUILD_EXAMPLES TRUE BOOL "TRUE to build the Mit examples, FALSE to ignore them")

# TODO : add API documentation

# Enable project folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

# Add the subdirectories
add_subdirectory(src/MiT)
if(MiT_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# setup the install rules
install(
  DIRECTORY include
  DESTINATION .
  COMPONENT devel
  FILES_MATCHING PATTERN "*.hpp")

# define an option for choosing between static and dynamic C runtime (Windows only)
if(MiT_OS_WINDOWS)
    mit_set_option(MiT_USE_STATIC_STD_LIBS FALSE BOOL "TRUE to statically link to the standard libraries, FALSE to use them as DLLs")

    # the following combination of flags is not valid
    if (BUILD_SHARED_LIBS AND MiT_USE_STATIC_STD_LIBS)
        message(FATAL_ERROR "BUILD_SHARED_LIBS and MiT_USE_STATIC_STD_LIBS cannot be used together")
    endif()

    # for VC++, we can apply it globally by modifying the compiler flags
    if(MiT_COMPILER_MSVC AND MiT_USE_STATIC_STD_LIBS)
        foreach(flag
                CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if(${flag} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
            endif()
        endforeach()
    endif()
endif()

add_custom_target(run
    COMMAND parser
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples/parser
)

#set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

#option(BUILD_SHARED_LIBS "Build shared libs" OFF)

#set (CMAKE_FIND_ROOT_PATH C:/Prog/TDM-GCC-64)

#find_package(OpenMP MODULE)

#set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

## Add Eigen library
#set(eigen3_include_dir "C:/Prog/Eigen/include/eigen3" CACHE STRING "eigen3 include directory")
#include_directories(${eigen3_include_dir})

## Generate list of source file
#file(
  #GLOB_RECURSE
  #source_files
  #src/*
  #)

#file(
  #GLOB_RECURSE
  #header_files
  #include/*
  #)

#add_subdirectory(test/parser)
#enable_testing()
#add_test(NAME parser COMMAND Test)

## Executable declaration
#add_library(
  #${CMAKE_PROJECT_NAME}
  #${source_files}
  #${header_files}
  #)

