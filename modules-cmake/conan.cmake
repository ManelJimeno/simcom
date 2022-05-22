# ######################################################################################################################
# Configure conan with modules-cmake.
#
# Code extracted from https://github.com/conan-io/cmake-conan
#
# ######################################################################################################################

option(CONAN_BUILD_MISSING "Automatically build all missing dependencies" ON)

set(CONAN_CMAKE_VERSION
    "0.18.1"
    CACHE STRING "Conan cmake script version")

# Setup the conan environment at the first run
function(conan_setup)
    execute_process(
        COMMAND "${Python3_EXECUTABLE}" -m pip install --upgrade conan conan_package_tools
        WORKING_DIRECTORY "."
        RESULT_VARIABLE COMMAND_RESULT
        OUTPUT_QUIET ERROR_QUIET)

    if(NOT COMMAND_RESULT EQUAL "0")
        message(FATAL_ERROR "Cannot install conan")
    endif()

    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan (${CONAN_CMAKE_VERSION})")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/${CONAN_CMAKE_VERSION}/conan.cmake"
             "${CMAKE_BINARY_DIR}/conan.cmake" TLS_VERIFY ON)
    endif()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_cmake_run(
        CONANFILE
        conanfile.py
        INSTALL_FOLDER
        "${CMAKE_CURRENT_BINARY_DIR}/"
        CONFIGURATION_TYPES
        ${CMAKE_CONFIGURATION_TYPES}
        BUILD
        missing)

    if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo_multi.cmake")
        include("${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo_multi.cmake")
        conan_basic_setup(TARGETS SKIP_STD SKIP_FPIC)
    else()
        include("${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake")
        conan_basic_setup(NO_OUTPUT_DIRS TARGETS SKIP_STD SKIP_FPIC)
    endif()

endfunction()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake")
    conan_setup()
endif()

message(STATUS "Config ${CMAKE_CURRENT_BINARY_DIR} include conan folders ")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")
find_package(
    Poco REQUIRED
    COMPONENTS Foundation
               Util
               JSON
               Net
               NetSSL
               Data
               DataSQLite)
