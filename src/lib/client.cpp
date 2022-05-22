/**
 * simcom simcom_client.cpp
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

#include "client.h"
#include "client_impl.h"
#include <iostream>

namespace simcom
{

Client::Client(Address address, std::string clientId, int batch)
    : m_pImpl{new ClientImpl(std::move(address), std::move(clientId), batch)}
{
}

Client::Client() : m_pImpl{new ClientImpl()}
{
}

Client::Client(Client&& other) noexcept : m_pImpl(std::move(other.m_pImpl))
{
}

Client::~Client() = default;

Address Client::getAddress() const
{
    return m_pImpl->getAddress();
}

std::string Client::getId() const
{
    return m_pImpl->getId();
}

int Client::getBatch() const
{
    return m_pImpl->getBatch();
}

void Client::join()
{
    m_pImpl->join();
}

void Client::run()
{
    m_pImpl->run();
}

} // namespace simcom
