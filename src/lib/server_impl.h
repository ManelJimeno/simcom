/**
 * simcom server_impl.h
 *
 * Copyright (C) 2022, Manel J
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/TCPServer.h"

#include "helpers.h"

namespace simcom
{

class SIMCOM_API ServerImpl
{
    DISABLE_COPY_AND_MOVE(ServerImpl)

  public:
    explicit ServerImpl(unsigned short port);

    ~ServerImpl() = default;

    void start();
    void stop();

  private:
    Poco::Net::ServerSocket m_serverSocket;
    Poco::Net::TCPServer m_srv;
};

} // namespace simcom
