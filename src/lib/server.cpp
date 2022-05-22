/**
 * simcom server
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

#include "include/server.h"
#include "server_impl.h"

namespace simcom
{

Server::Server(unsigned short port) : m_pImpl(new ServerImpl(port))
{
}

void Server::start()
{
    m_pImpl->start();
}

void Server::stop()
{
    m_pImpl->stop();
}

Server::~Server() = default;

} // namespace simcom
