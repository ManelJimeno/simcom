# ######################################################################################################################
# Configure conan with modules-cmake.
#
# Code extracted from https://github.com/conan-io/cmake-conan
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
set(CONAN_CMAKE_VERSION
    "0.18.1"
    CACHE STRING "Conan cmake script version")
option(CONAN_BUILD_MISSING "Automatically build all missing dependencies" ON)

# Conan's libraries setting helper
function(conan_configure)
    set(multiValueArgs REQUIRES OPTIONS FIND_PACKAGES)
    cmake_parse_arguments(CONFIG "" "" "${multiValueArgs}" ${ARGN})

    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan/conan.cmake")
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
             "${CMAKE_BINARY_DIR}/conan/conan.cmake" TLS_VERIFY ON)
    endif()

    include(${CMAKE_BINARY_DIR}/conan/conan.cmake)

    if(CONAN_BUILD_MISSING)
        set(build_option missing)
    else()
        set(build_option never)
    endif()

    conan_cmake_configure(
        REQUIRES
        ${CONFIG_REQUIRES}
        GENERATORS
        cmake_find_package
        IMPORTS
        "bin, *.dll -> ./bin/lib"
        IMPORTS
        "lib, *.dylib* -> ./bin/lib"
        IMPORTS
        "lib, *.so* -> ./bin/lib"
        OPTIONS
        ${CONFIG_OPTIONS})

    conan_cmake_autodetect(settings)

    conan_cmake_install(
        PATH_OR_REFERENCE
        .
        BUILD
        ${build_option}
        REMOTE
        conancenter
        SETTINGS
        ${settings})

    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")
    message(STATUS "Conan's libraries setting")
    foreach(package IN LISTS CONFIG_FIND_PACKAGES)
        find_package(${package} REQUIRED)
        message(STATUS "\tpackage ${package} loaded")
    endforeach()

endfunction()
