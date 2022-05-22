/**
 * simcom address.h
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

#include "address.h"

namespace simcom
{
Address::Address(std::string ip, int port) : m_ip(std::move(ip)), m_port(port)
{
}

std::string Address::getIp() const
{
    return m_ip;
}

int Address::getPort() const
{
    return m_port;
}

auto operator<<(std::ostream& os, const Address& address) -> std::ostream&
{
    return os << address.getIp() << ":" << address.getPort();
}

} // namespace simcom
