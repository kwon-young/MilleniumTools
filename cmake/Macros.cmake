include(CMakeParseArguments)

# add a new target which is a MiT library
# ex: mit_add_library(mit-graphics
#                      SOURCES sprite.cpp image.cpp ...
#                      DEPENDS mit-window mit-system
#                      EXTERNAL_LIBS opengl freetype ...)
macro(mit_add_library target)

    # parse the arguments
    cmake_parse_arguments(THIS "" "" "SOURCES;DEPENDS;EXTERNAL_LIBS" ${ARGN})

    # create the target
    add_library(${target} ${THIS_SOURCES})

    # define the export symbol of the module
    string(REPLACE "-" "_" NAME_UPPER "${target}")
    string(TOUPPER "${NAME_UPPER}" NAME_UPPER)
    set_target_properties(${target} PROPERTIES DEFINE_SYMBOL ${NAME_UPPER}_EXPORTS)

    # adjust the output file prefix/suffix to match our conventions
    if(BUILD_SHARED_LIBS)
        if(MiT_OS_WINDOWS)
            # include the major version number in Windows shared library names (but not import library names)
            set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)
            set_target_properties(${target} PROPERTIES SUFFIX "-${VERSION_MAJOR}${CMAKE_SHARED_LIBRARY_SUFFIX}")
        else()
            set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)
        endif()
        if (MiT_OS_WINDOWS AND MiT_COMPILER_GCC)
            # on Windows/gcc get rid of "lib" prefix for shared libraries,
            # and transform the ".dll.a" suffix into ".a" for import libraries
            set_target_properties(${target} PROPERTIES PREFIX "")
            set_target_properties(${target} PROPERTIES IMPORT_SUFFIX ".a")
        endif()
    else()
        set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -s-d)
        set_target_properties(${target} PROPERTIES RELEASE_POSTFIX -s)
        set_target_properties(${target} PROPERTIES MINSIZEREL_POSTFIX -s)
    endif()

    # set the version and soversion of the target (for compatible systems -- mostly Linuxes)
    # except for Android which strips soversion suffixes
    if(NOT MiT_OS_ANDROID)
        set_target_properties(${target} PROPERTIES SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR})
        set_target_properties(${target} PROPERTIES VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
    endif()

    # set the target's folder (for IDEs that support it, e.g. Visual Studio)
    set_target_properties(${target} PROPERTIES FOLDER "MiT")

    # for gcc >= 4.0 on Windows, apply the MiT_USE_STATIC_STD_LIBS option if it is enabled
    if(MiT_OS_WINDOWS AND MiT_COMPILER_GCC AND NOT MiT_GCC_VERSION VERSION_LESS "4")
        if(MiT_USE_STATIC_STD_LIBS AND NOT MiT_COMPILER_GCC_TDM)
            set_target_properties(${target} PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++")
        elseif(NOT MiT_USE_STATIC_STD_LIBS AND MiT_COMPILER_GCC_TDM)
            set_target_properties(${target} PROPERTIES LINK_FLAGS "-shared-libgcc -shared-libstdc++")
        endif()
    endif()

    # if using gcc >= 4.0 or clang >= 3.0 on a non-Windows platform, we must hide public symbols by default
    # (exported ones are explicitly marked)
    if(NOT MiT_OS_WINDOWS AND ((MiT_COMPILER_GCC AND NOT MiT_GCC_VERSION VERSION_LESS "4") OR (MiT_COMPILER_CLANG AND NOT MiT_CLANG_VERSION VERSION_LESS "3")))
        set_target_properties(${target} PROPERTIES COMPILE_FLAGS -fvisibility=hidden)
    endif()

    # link the target to its MiT dependencies
    if(THIS_DEPENDS)
        target_link_libraries(${target} ${THIS_DEPENDS})
    endif()

    # link the target to its external dependencies
    if(THIS_EXTERNAL_LIBS)
        target_link_libraries(${target} ${THIS_EXTERNAL_LIBS})
    endif()

    # add the install rule
    install(TARGETS ${target}
            RUNTIME DESTINATION bin COMPONENT bin
            LIBRARY DESTINATION lib${LIB_SUFFIX} COMPONENT bin
            ARCHIVE DESTINATION lib${LIB_SUFFIX} COMPONENT devel
            FRAMEWORK DESTINATION ${CMAKE_INSTALL_FRAMEWORK_PREFIX} COMPONENT bin)
endmacro()

# add a new target which is a MiT example
# ex: mit_add_example(parser
#                      SOURCES main.cpp ...
#                      DEPENDS mit-parser)
macro(mit_add_example target)

    # parse the arguments
    cmake_parse_arguments(THIS "" "" "SOURCES;DEPENDS" ${ARGN})

    # set a source group for the source files
    source_group("" FILES ${THIS_SOURCES})

    # create the target
    if(MiT_OS_WINDOWS AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
      add_executable(${target} ${THIS_SOURCES})
    endif()

    # set the debug suffix
    set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)

    # set the target's folder (for IDEs that support it, e.g. Visual Studio)
    set_target_properties(${target} PROPERTIES FOLDER "Examples")

    # for gcc >= 4.0 on Windows, apply the MiT_USE_STATIC_STD_LIBS option if it is enabled
    if(MiT_OS_WINDOWS AND MiT_COMPILER_GCC AND NOT MiT_GCC_VERSION VERSION_LESS "4")
        if(MiT_USE_STATIC_STD_LIBS AND NOT MiT_COMPILER_GCC_TDM)
            set_target_properties(${target} PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++")
        elseif(NOT MiT_USE_STATIC_STD_LIBS AND MiT_COMPILER_GCC_TDM)
            set_target_properties(${target} PROPERTIES LINK_FLAGS "-shared-libgcc -shared-libstdc++")
        endif()
    endif()

    # link the target to its MiT dependencies
    if(THIS_DEPENDS)
        target_link_libraries(${target} ${THIS_DEPENDS})
    endif()

    # add the install rule
    install(TARGETS ${target}
            RUNTIME DESTINATION ${INSTALL_MISC_DIR}/examples/${target} COMPONENT examples
            BUNDLE DESTINATION ${INSTALL_MISC_DIR}/examples/${target} COMPONENT examples)

    # install the example's source code
    install(FILES ${THIS_SOURCES}
            DESTINATION ${INSTALL_MISC_DIR}/examples/${target}
            COMPONENT examples)

    # install the example's resources as well
    set(EXAMPLE_RESOURCES "${CMAKE_SOURCE_DIR}/examples/${target}/resources")
    if(EXISTS ${EXAMPLE_RESOURCES})
        install(DIRECTORY ${EXAMPLE_RESOURCES}
                DESTINATION ${INSTALL_MISC_DIR}/examples/${target}
                COMPONENT examples)
    endif()

endmacro()

