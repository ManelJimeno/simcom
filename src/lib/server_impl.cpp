/**
 * simcom server_impl
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

#include "server_impl.h"
#include "server_connection.h"
#include <iostream>

namespace simcom
{

ServerImpl::ServerImpl(int port) : m_serverSocket(port), m_srv(new ServerConnectionFactory(), m_serverSocket)
{
}

void ServerImpl::start()
{
    m_srv.start();
}

void ServerImpl::stop()
{
    m_srv.start();
}

} // namespace simcom
