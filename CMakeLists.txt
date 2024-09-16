#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT
#

# Set the minimum CMake version.
cmake_minimum_required(VERSION 3.29.5 FATAL_ERROR)

# Include pre-project definitions.
include("toolchain-defaults")

# Define the project.
project(advent-of-code VERSION 0.0.1.0 DESCRIPTION "Advent of Code" HOMEPAGE_URL "https://www.jamiekenyon.com/")
set(CMAKE_INSTALL_MESSAGE LAZY)

# Include the dependent modules.
include("options")
include("packages")
include("targets")

if(BUILD_TESTING)
    include("CTest")
    include("Catch")
endif()

# Add the sources.
add_subdirectory("src")
