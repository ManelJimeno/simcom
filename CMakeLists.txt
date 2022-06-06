# ######################################################################################################################
# Main modules-cmake file. We use modules-cmake-lint, see on
# https://cmake-format.readthedocs.io/en/latest/lint-summary.html
#
# Copyright (C) 2022, Manel J.
#
# This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
# License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this program.  If not, see
# <http://www.gnu.org/licenses/>.
#
# ######################################################################################################################

cmake_minimum_required(VERSION 3.22)

# Load required packages
find_package(Python3 "3.8" QUIET REQUIRED)

# Add custom modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules-cmake")
include(project-version)

# Project definition
project(
    simcom
    VERSION "${PRODUCT_VERSION}"
    LANGUAGES C CXX)

if("${CMAKE_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}")
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

# Include modules
include(clang)
include(conan)
include(settings)
include(pre-commit)
include(unit-test)

# Config conan
add_definitions("-std=c++11")
conan_configure(
    REQUIRES
    poco/1.11.2
    openssl/1.1.1o
    gtest/cci.20210126
    OPTIONS
    poco:shared=True
    openssl:shared=True
    FIND_PACKAGES
    Poco
    GTest)

# Options
option(BUILD_UNIT_TESTS "Build unit tests" ON)
option(BUILD_INTEGRATION_TESTS "Build integration tests" ON)
option(USE_CODE_WARNINGS_AS_ERRORS "Use code warnings as errors" ON)

# Add subdirs
add_subdirectory(src/lib)
add_subdirectory(src/client)
add_subdirectory(src/server)
if(BUILD_UNIT_TESTS)
    add_subdirectory(src/ut)
endif()
if(BUILD_INTEGRATION_TESTS)
    add_subdirectory(src/it)
endif()
