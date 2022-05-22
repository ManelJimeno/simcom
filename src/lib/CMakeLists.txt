# ######################################################################################################################
# simcom library
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

set(AUTOGEN_SOURCES version.cpp.in)
set(PUBLIC_HEADERS include/version.h include/server.h include/address.h include/client.h)
set(SOURCES server.cpp server_impl.cpp server_connection.cpp client.cpp client_impl.cpp address.cpp)
set(LIBRARIES Poco::Net Poco::Util Poco::Foundation Poco::XML Poco::Zip)

add_library(simcom SHARED ${SOURCES})
# Set the DLLEXPORT variable to export symbols
target_compile_definitions(simcom PRIVATE SIMCOM_EXPORTS)
config_target(
    TARGET
    simcom
    AUTOGEN_SOURCES
    ${AUTOGEN_SOURCES}
    PUBLIC_HEADERS
    ${PUBLIC_HEADERS}
    LIBRARIES
    ${LIBRARIES})
