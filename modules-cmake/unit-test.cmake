# ######################################################################################################################
# Unit test module
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
include(GoogleTest)
enable_testing()

# Create a unit test target
function(add_product_test)
    set(oneValueArgs TARGET)
    set(multiValueArgs LIBRARIES)
    cmake_parse_arguments(CONFIG "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(test_name u_test_${CONFIG_TARGET})
    config_target(TARGET ${test_name} SOURCES ${test_name}.cpp LIBRARIES ${CONFIG_LIBRARIES})
    set_target_properties(${test_name} PROPERTIES FOLDER "test")

    gtest_discover_tests(${test_name})
endfunction()
