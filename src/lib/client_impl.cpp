/**
 * simcom client_impl.cpp
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

#include "client_impl.h"
#include "Poco/Net/DialogSocket.h"
#include <iostream>

namespace simcom
{
ClientImpl::ClientImpl(Address address, std::string clientId, int batch)
    : m_address(std::move(address)), m_id(std::move(clientId)), m_batch(batch)
{
    std::cout << "created --> server address: " << m_address << " client id: " << m_id
              << " created in the batch: " << m_batch << std::endl;
}

ClientImpl::~ClientImpl()
{
    join();
}

void ClientImpl::talkWithServer() const
{
    Poco::Net::DialogSocket ds;
    ds.connect(Poco::Net::SocketAddress(m_address.getIp(), m_address.getPort()));
    std::string str;
    ds.receiveMessage(str);
    std::cout << "Client " << m_id << " from batch " << m_batch << " receives " << str << std::endl;
}

Address ClientImpl::getAddress() const
{
    return m_address;
}

std::string ClientImpl::getId() const
{
    return m_id;
}

int ClientImpl::getBatch() const
{
    return m_batch;
}

void ClientImpl::join()
{
    if (m_thread != nullptr)
    {
        if (m_thread->joinable())
        {
            m_thread->join();
        }
    }
}

void ClientImpl::run()
{
    if (m_thread == nullptr)
    {
        m_thread = std::make_unique<std::thread>(std::thread(&ClientImpl::talkWithServer, this));
    }
}
} // namespace simcom
