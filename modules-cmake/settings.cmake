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

# Setting build type constraints
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to Debug by default")
    set(CMAKE_BUILD_TYPE
        "Debug"
        CACHE STRING "" FORCE)
endif()
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY HELPSTRING "Choose build type")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release")

# Create the target specified
function(create_target)
    set(oneValueArgs TARGET LIBRARY STATIC)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(CONFIG "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(DEFINED CONFIG_SOURCES)
        if(CONFIG_LIBRARY)
            if(CONFIG_STATIC)
                message(STATUS "Creating ${CONFIG_TARGET}, which is a static library")
                add_library(simcom STATIC ${CONFIG_SOURCES})
            else()
                message(STATUS "Creating ${CONFIG_TARGET}, which is a shared library")
                add_library(simcom SHARED ${CONFIG_SOURCES})
            endif()
            set_target_properties(${CONFIG_TARGET} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")
        else()
            message(STATUS "Creating ${CONFIG_TARGET}, which is an executable")
            add_executable(${CONFIG_TARGET} ${CONFIG_SOURCES})
            set_target_properties(${CONFIG_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
        endif()
    else()
        message(STATUS "Configuring ${CONFIG_TARGET}")
    endif()
endfunction()

# Setup the RPATH
function(config_rpath)
    set(oneValueArgs TARGET LIBRARY)
    cmake_parse_arguments(CONFIG "" "${oneValueArgs}" "" ${ARGN})
    message(STATUS "\tSetting rpath for ${CONFIG_TARGET}")
    if(CONFIG_LIBRARY)
        if(APPLE)
            set_target_properties(${CONFIG_TARGET} PROPERTIES MACOSX_RPATH 1)
        endif()
    else()
        set_target_properties(${CONFIG_TARGET} PROPERTIES BUILD_RPATH "@loader_path/lib")
    endif()
endfunction()

# Setup the target specified
function(config_target)
    set(options LIBRARY STATIC)
    set(oneValueArgs TARGET)
    set(multiValueArgs AUTOGEN_SOURCES PUBLIC_HEADERS LIBRARIES PRIVATE_DEFINITIONS SOURCES)
    cmake_parse_arguments(CONFIG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    create_target(
        TARGET
        ${CONFIG_TARGET}
        LIBRARY
        ${CONFIG_LIBRARY}
        STATIC
        ${CONFIG_STATIC}
        SOURCES
        ${CONFIG_SOURCES})

    config_rpath(TARGET ${CONFIG_TARGET} LIBRARY ${CONFIG_LIBRARY})

    if(DEFINED CONFIG_PRIVATE_DEFINITIONS)
        message(STATUS "\tPRIVATE_DEFINITIONS : ${CONFIG_PRIVATE_DEFINITIONS}")
        target_compile_definitions(${CONFIG_TARGET} PRIVATE ${PRIVATE_DEFINITIONS})
    endif()

    if(DEFINED CONFIG_AUTOGEN_SOURCES)
        message(STATUS "\tAUTOGEN_SOURCES     : ${CONFIG_AUTOGEN_SOURCES}")
        foreach(item IN LISTS AUTOGEN_SOURCES)
            string(REGEX REPLACE "\\.[^.]*$" "" SRC ${item})
            configure_file(${item} ${SRC} @ONLY)
            target_sources(${CONFIG_TARGET} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${SRC})
        endforeach()
        target_link_libraries(${CONFIG_TARGET} PRIVATE ${CONFIG_LIBRARIES})
    endif()

    if(DEFINED CONFIG_LIBRARIES)
        message(STATUS "\tLIBRARIES           : ${CONFIG_LIBRARIES}")
        target_link_libraries(${CONFIG_TARGET} PRIVATE ${CONFIG_LIBRARIES})
    endif()

    if(DEFINED CONFIG_PUBLIC_HEADERS)
        message(STATUS "\tPUBLIC_HEADERS      : ${CONFIG_PUBLIC_HEADERS}")
        target_sources(${CONFIG_TARGET} PUBLIC ${CONFIG_PUBLIC_HEADERS})
    endif()

    target_include_directories(
        ${CONFIG_TARGET}
        PRIVATE "."
        PUBLIC "include")

    set_target_properties(${CONFIG_TARGET} PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 17 CXX_EXTENSIONS OFF)

    if(USE_CODE_WARNINGS_AS_ERRORS)
        if(MSVC)
            target_compile_options(${CONFIG_TARGET} PRIVATE /W4 /WX /wd4996)
        else()
            target_compile_options(${CONFIG_TARGET} PRIVATE -Wall -Wextra -Werror)
        endif()
    endif()

endfunction()

# Default policies
message(STATUS "Setting default policies")
if(APPLE)
    message(STATUS "\tCMP0042 NEW")
    cmake_policy(SET CMP0042 NEW)
    message(STATUS "\tCMP0068 NEW")
    cmake_policy(SET CMP0068 NEW)
endif()

# Output settings
message(STATUS "Output settings")
message(STATUS "\tSetting executables files to save to this path ${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
message(STATUS "\tSetting libraries files to save to this path ${CMAKE_BINARY_DIR}/bin/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")
message(STATUS "\tSetting the other files to save to this path ${CMAKE_BINARY_DIR}/bin/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")
