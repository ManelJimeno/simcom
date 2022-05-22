# ######################################################################################################################
# Retrieve the product version from the version file in the project root folder.
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

# Populate product version
function(populate_product_version)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/version")
        file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/version" version_string REGEX "[0-9]+\\.[0-9]+\\.[0-9]+")
        message(STATUS "The current version product is ${version_string}")
        string(REPLACE "." ";" VERSION_LIST ${version_string})
        list(GET VERSION_LIST 0 local_major)
        list(GET VERSION_LIST 1 local_minor)
        list(GET VERSION_LIST 2 local_revision)
        set(PRODUCT_VERSION_MAJOR
            ${local_major}
            PARENT_SCOPE)
        set(PRODUCT_VERSION_MINOR
            ${local_minor}
            PARENT_SCOPE)
        set(PRODUCT_VERSION_REVISION
            ${local_revision}
            PARENT_SCOPE)
        set(PRODUCT_VERSION
            "${version_string}"
            PARENT_SCOPE)
    else()
        message(FATAL_ERROR "It is mandatory to have a version of the file in the ${CMAKE_CURRENT_SOURCE_DIR} folder")
    endif()
endfunction()

if(NOT PRODUCT_VERSION)
    populate_product_version()
endif()
