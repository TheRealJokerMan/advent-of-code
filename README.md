# Advent Of Code Solutions

## Overview

These are my solutions for the [Advent Of Code](https://adventofcode.com/).

Even though I am primarily a C++ engineer, not all of the solutions have been
solved with the C++, some have been engineered with Python 3, as I've spent many
years of my career working in the VFX space.

## Solution Structure

The solution for each day can be found in a subdirectory of the `src` directory,
with the following structure:

- `data.txt` - This contains the input data from the exercise.
- `lib.[cxx|hxx|py]` - The implementation of solution to the day's exercise can
be found here.
- `main.[cxx|py]` - Provides a runnable program for retrieving the answer to the
day's exercise.
- `overview.dox` - This is a copy of the description of the day's exercise.
- `test.[cxx|py]` - This is either a [Catch2](https://github.com/catchorg/Catch2)
or [pytest](https://docs.pytest.org/en/stable/) unit test which tests the solution
to the day's exercise with the sample data provided in the day's description.

## Testing

Even though not all solutions are engineered with C++, there are
[ctest](https://cmake.org/cmake/help/v2.8.12/ctest.html) based tests for the
solution to every day's exercise. The tests have been successfully exercised on:

- macOS 15
- Ubuntu 22.04 LTS
- Windows 11
