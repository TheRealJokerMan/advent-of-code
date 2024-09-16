#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT
#

# Set the minimum MacOS version.
set(CMAKE_OSX_DEPLOYMENT_TARGET "11" CACHE STRING "Minimum OS X deployment version")

# Clang Format.
find_program(CLANG_FORMAT_EXECUTABLE NAMES "clang-format" REQUIRED
    HINTS
        ENV "VCINSTALLDIR"
    PATH_SUFFIXES
         "Tools/Llvm/x64/bin"
)

# Generate values from the current date that can be used in file configuration macros.
string(TIMESTAMP BUILD_YEAR  "%Y")
string(TIMESTAMP BUILD_MONTH "%m")
string(TIMESTAMP BUILD_DAY   "%d")
string(TIMESTAMP BUILD_TIME  "%H:%M:%S")
