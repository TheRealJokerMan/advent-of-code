#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT
#
# This module defines a set of functions for creating CMake and CTest targets. Defining CMake/CTest
# targets can be verbose and these functions help reduce that verbosity.


# Creates several CMake targets: one executable and one test executable.
function(com_exercise_cxx targetName)
    set(multiValueKeywords
        LIB_SOURCES          # List of .cxx source files.
    )

    cmake_parse_arguments(args
        "${optionKeywords}"
        "${oneValueKeywords}"
        "${multiValueKeywords}"
        ${ARGN}
    )

    com_test(${targetName}
        CXX_SOURCES
            ${args_LIB_SOURCES}
            "test.cxx"

        LIBRARIES
            com::common

        COMPILE_DEFINITIONS
            DATA_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\"
    )

    com_executable(${targetName}
        CXX_SOURCES
            ${args_LIB_SOURCES}
            "main.cxx"

        LIBRARIES
            com::common

        COMPILE_DEFINITIONS
            DATA_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\"
    )
endfunction(com_exercise_cxx)


# Create a new named CMake target. Use this function to create a Python-based unit test.
function(com_exercise_py targetName)
    add_test(
        NAME
            com.${targetName}.test
        COMMAND
            ${Python_EXECUTABLE} -m pytest ${CMAKE_CURRENT_SOURCE_DIR}
        WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR}
    )
endfunction(com_exercise_py)


# Create a new named CMake target. Use this function to create a C++ unit test.
function(com_test targetName)
    if(NOT BUILD_TESTING)
        return()
    endif()

    set(optionKeywords)

    set(oneValueKeywords)

    set(multiValueKeywords
        CXX_SOURCES          # List of .cxx source files.
        LIBRARIES            # List of dependent libraries to link that upstream consumers require.
        COMPILE_DEFINITIONS  # List of compile definitions that upstream consumers don't require.
    )

    cmake_parse_arguments(args
        "${optionKeywords}"
        "${oneValueKeywords}"
        "${multiValueKeywords}"
        ${ARGN}
    )

    if(args_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unparsed arguments: ${args_UNPARSED_ARGUMENTS}")
    endif()

    # Generate the target names.
    set(targetName "com.${targetName}.test")

    # Define the target.
    add_executable(${targetName} ${args_CXX_SOURCES})

    _set_target_defaults(${targetName})

    # Set the compile definitions.
    target_compile_definitions(${targetName}
        PRIVATE
            ${args_COMPILE_DEFINITIONS}
    )

    # Set the target's include directories.
    target_include_directories(${targetName}
        PRIVATE
            "${CMAKE_SOURCE_DIR}"
    )

    # Set the target's dependencies.
    target_link_libraries(${targetName} PRIVATE ${args_LIBRARIES} Catch2::Catch2WithMain)

    # Add the test.
    add_test(NAME ${targetName} COMMAND "$<TARGET_FILE:${targetName}>")
endfunction(com_test)


# Create a new named CMake target. Use this function to create an application.
function(com_executable targetName)
    set(optionKeywords)

    set(oneValueKeywords)

    set(multiValueKeywords
        CXX_SOURCES                 # List of .cxx source files.
        LIBRARIES                   # List of dependent libraries to link that upstream consumers don't require.
        COMPILE_DEFINITIONS         # List of compile definitions that upstream consumers don't require.
    )

    cmake_parse_arguments(args
        "${optionKeywords}"
        "${oneValueKeywords}"
        "${multiValueKeywords}"
        ${ARGN}
    )

    if(args_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unparsed arguments: ${args_UNPARSED_ARGUMENTS}")
    endif()

    # Define the target.
    add_executable(${targetName}  ${args_CXX_SOURCES})

    _set_target_defaults(${targetName})

    # Set the compile definitions.
    target_compile_definitions(${targetName}
        PRIVATE
            ${args_COMPILE_DEFINITIONS}
    )

    # Set the target's dependencies.
    target_link_libraries(${targetName} PRIVATE ${args_LIBRARIES})
endfunction(com_executable)


# Create a new named CMake target. Use this function to create a static libary.
function(com_library targetName)
    set(optionKeywords
        DYNAMIC                     # true if this is a dynamic library; false otherwise.
    )

    set(oneValueKeywords)

    set(multiValueKeywords
        CXX_SOURCES                  # List of .cxx source files.
        PRIVATE_LIBRARIES            # List of dependent libraries to link that upstream consumers don't require.
        PUBLIC_LIBRARIES             # List of dependent libraries to link that upstream consumers require.
        PUBLIC_COMPILE_DEFINITIONS   # List of compile definitions that upstream consumers require.
        PRIVATE_COMPILE_DEFINITIONS  # List of compile definitions that upstream consumers don't require.
    )

    cmake_parse_arguments(args
        "${optionKeywords}"
        "${oneValueKeywords}"
        "${multiValueKeywords}"
        ${ARGN}
    )

    if(args_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unparsed arguments: ${args_UNPARSED_ARGUMENTS}")
    endif()

    # Generate the target names.
    string(TOUPPER ${targetName} exportSymbol)
    set(targetName "com.${targetName}")
    string(REPLACE "." "::" namespacedtargetName ${targetName})

    # Get the type.
    set(libType STATIC)
    if(args_DYNAMIC)
        set(libType SHARED)
    endif()

    # Define the target.
    add_library(${targetName} ${libType} ${args_CXX_SOURCES})

    _set_target_defaults(${targetName})
    set_target_properties(${targetName} PROPERTIES DEFINE_SYMBOL "${exportSymbol}_EXPORTS")

    # Set the compile definitions.
    target_compile_definitions(${targetName}
        PUBLIC
            ${args_PUBLIC_COMPILE_DEFINITIONS}
        PRIVATE
            ${args_PRIVATE_COMPILE_DEFINITIONS}
    )

    # Set the target's dependencies.
    target_link_libraries(${targetName}
        PUBLIC  ${args_PUBLIC_LIBRARIES}
        PRIVATE ${args_PRIVATE_LIBRARIES}
    )

    # Define an alias for downstream consumption.
    add_library(${namespacedtargetName} ALIAS ${targetName})
endfunction(com_library)


# Set default target options.
function(_set_target_defaults TRGT)
    # Set properties.
    set_target_properties(${TRGT}
        PROPERTIES
            COMPILE_WARNING_AS_ERROR  ON
            C_VISIBILITY_PRESET       hidden
            CXX_VISIBILITY_PRESET     hidden
            POSITION_INDEPENDENT_CODE ON
            VISIBILITY_INLINES_HIDDEN ON
    )

    # Set the target's compile definitions.
    target_compile_definitions(${TRGT}
        PRIVATE
            $<$<CXX_COMPILER_ID:AppleClang>:_LIBCPP_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION>
            $<$<CXX_COMPILER_ID:MSVC>:_AMD64_>
            $<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>
            $<$<CXX_COMPILER_ID:MSVC>:WIN32_LEAN_AND_MEAN>
    )

    # Set the C++ standard version.
    target_compile_features(${TRGT} PRIVATE cxx_std_23)

    # Set C++ flags.
    target_compile_options(${TRGT}
        PRIVATE
            $<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall>                     # Set highest warning level.
            $<$<CXX_COMPILER_ID:MSVC>:/W4 /EHsc>                                 # Set highest warning level.
            $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/analyze>           # Enable Static Code Analysis.
            $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/Zi>              # Generate debug information in Release.
            $<$<AND:$<CXX_COMPILER_ID:AppleClang,GNU>,$<CONFIG:Release>>:-g -g2> # Generate debug information in Release.
    )

    # Set the target's include directories.
    target_include_directories(${TRGT}
        PRIVATE
            "${CMAKE_SOURCE_DIR}/src"
    )
endfunction(_set_target_defaults)
