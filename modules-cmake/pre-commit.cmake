# ######################################################################################################################
# Install the pre-commit tool and set up the git hook.
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

# Install pre-commit and formatting tools needed for it to work
function(configure_pre_commit)
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git/hook/pre-commit")
        execute_process(
            COMMAND "${Python3_EXECUTABLE}" -m pip install --upgrade editorconfig-checker black cmakelang pre-commit
            WORKING_DIRECTORY "."
            RESULT_VARIABLE COMMAND_RESULT
            OUTPUT_QUIET ERROR_QUIET)
        if(NOT COMMAND_RESULT EQUAL "0")
            message(FATAL_ERROR "Cannot install editorconfig-checker, black, pre-commit or cmakelang")
        endif()

        if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.pre-commit-config.yaml")
            message(FATAL_ERROR "The file .pre-commit-config.yaml is mandatory to config pre-commit tool")
        endif()

        find_program(
            PRE_COMMIT_TOOL
            NAMES pre-commit
            DOC "Pre-commit tool")

        execute_process(COMMAND pre-commit install WORKING_DIRECTORY ".")
        # RESULT_VARIABLE COMMAND_RESULT             OUTPUT_QUIET ERROR_QUIET)

        if(NOT COMMAND_RESULT EQUAL "0")
            message(FATAL_ERROR "Cannot install pre-commit")
        else()
            message(STATUS "Pre-commit tools install successfully")
        endif()

    endif()
endfunction()

if(NOT PRE_COMMIT_TOOL)
    configure_pre_commit()
endif()
