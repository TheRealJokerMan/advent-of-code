#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT
#

# Include the required modules.
include("FetchContent")

# Prefer unix-style package components to macOS Frameworks.
set(CMAKE_FIND_FRAMEWORK LAST)

# Apple frameworks.
if(APPLE)
    find_library(FRAMEWORK_COCOA Cocoa REQUIRED)
    find_library(FRAMEWORK_QUARTZ QuartzCore REQUIRED)
endif(APPLE)

# Unit-testing framework.
if(NOT TARGET Catch2::Catch2WithMain)
    FetchContent_Declare(Catch GIT_REPOSITORY "https://github.com/catchorg/Catch2.git" GIT_TAG "v3.6.0")
    FetchContent_MakeAvailable(Catch)
    list(APPEND CMAKE_MODULE_PATH "${catch_SOURCE_DIR}/extras")
endif(NOT TARGET Catch2::Catch2WithMain)

# Documentation generator.
if(BUILD_DOCS)
    find_package(Doxygen REQUIRED)
endif(BUILD_DOCS)

# Python.
find_package(Python REQUIRED COMPONENTS Interpreter)

