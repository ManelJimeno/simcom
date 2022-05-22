/**
 * simcom simcom_client.h
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

#include "helpers.h"
#include <iostream>
#include <string>

namespace simcom
{

class Address
{
  public:
    SIMCOM_API Address() = default;

    explicit SIMCOM_API Address(std::string ip, unsigned short port);

    SIMCOM_API Address(const Address& other) = default;

    SIMCOM_API Address(Address&& other) = default;

    SIMCOM_API Address& operator=(const Address& other) = default;

    SIMCOM_API Address& operator=(Address&& other) = default;

    SIMCOM_API ~Address() = default;

    SIMCOM_API NODISCARD std::string getIp() const;

    SIMCOM_API NODISCARD unsigned short getPort() const;

    friend auto operator<<(std::ostream& os, Address const& address) -> std::ostream&;

  private:
    std::string m_ip;
    unsigned short m_port = {0};
};

} // namespace simcom
