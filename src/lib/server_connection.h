/**
 * simcom simcom_conenction.cpp
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

#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"

namespace simcom
{

class ServerConnection : public Poco::Net::TCPServerConnection
{
  public:
    ServerConnection(const Poco::Net::StreamSocket& s);

    void run() override;
};

class ServerConnectionFactory : public Poco::Net::TCPServerConnectionFactory
{
  public:
    ServerConnectionFactory() = default;

    Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket) override
    {
        return new ServerConnection(socket);
    }
};

} // namespace simcom
