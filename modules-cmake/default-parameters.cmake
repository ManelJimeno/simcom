# ######################################################################################################################
# Configure project and target default parameters.
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

# Check the CMakeLists.txt location
if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/CMakeLists.txt")
    message(
        FATAL_ERROR
            "In-source builds are not allowed, please create a 'build' subfolder and use `cmake ..` inside it.\n"
            "NOTE: cmake will now create CMakeCache.txt and CMakeFiles/*.\n"
            "You must delete them, or cmake will refuse to work.")
endif()

# Multiconfig settings
get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(IS_MULTI_CONFIG)
    message(STATUS "Multi-config generator detected")
    set(CMAKE_CONFIGURATION_TYPES
        "Debug;Release"
        CACHE STRING "" FORCE)
else()
    if(NOT CMAKE_BUILD_TYPE)
        message(STATUS "Setting build type to Debug by default")
        set(CMAKE_BUILD_TYPE
            "Debug"
            CACHE STRING "" FORCE)
    endif()
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY HELPSTRING "Choose build type")
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release")
endif()

# Process the list of .in files
macro(CONFIG_AUTOGEN)
    foreach(item IN LISTS AUTOGEN_SOURCES)
        string(REGEX REPLACE "\\.[^.]*$" "" SRC ${item})
        configure_file(${item} ${SRC} @ONLY)
        list(APPEND SOURCES ${CMAKE_CURRENT_BINARY_DIR}/${SRC})
    endforeach()
endmacro()

# Setup the target specified
macro(CONFIG_TARGET target_name)
    message(STATUS "${target_name} target setup done")

    target_link_libraries(${target_name} PRIVATE ${LIBRARIES})
    target_sources(${target_name} PUBLIC ${PUBLIC_HEADERS})
    target_include_directories(
        ${target_name}
        PRIVATE "."
        PUBLIC "include")

    set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(${target_name} PROPERTIES CXX_STANDARD 17 CXX_EXTENSIONS OFF)
    target_compile_definitions(${target_name} PRIVATE _HAS_CXX17=1)
    link_directories(${CMAKE_BINARY_DIR}/lib)

    if(APPLE)
        set_target_properties(${target_name} PROPERTIES BUILD_RPATH ${BASE_RPATH})
    endif()
    set_target_properties(${target_name} PROPERTIES INSTALL_RPATH ${BASE_RPATH})

    if(USE_CODE_WARNINGS_AS_ERRORS)
        if(MSVC)
            target_compile_options(${target_name} PRIVATE /W4 /WX /wd4996)
        else()
            target_compile_options(${target_name} PRIVATE -Wall -Wextra -Werror)
        endif()
    endif()
endmacro()

# Output settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")

# RPATH
if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
    set(BASE_RPATH @executable_path/lib)
else()
    set(BASE_RPATH ./lib)
endif()

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
