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

#include "address.h"
#include "helpers.h"

namespace simcom
{
class ClientImpl;
class Client
{
    DISABLE_COPY(Client)
  public:
    explicit SIMCOM_API Client(Address address, std::string clientId, int batch);
    SIMCOM_API Client();
    SIMCOM_API Client(Client&& other) noexcept;
    SIMCOM_API Client& operator=(Client&& other) noexcept = default;

    SIMCOM_API ~Client();

    SIMCOM_API NODISCARD Address getAddress() const;

    SIMCOM_API NODISCARD std::string getId() const;

    SIMCOM_API NODISCARD int getBatch() const;

    SIMCOM_API void join();

    SIMCOM_API void run();

  private:
    PIMPL(ClientImpl)
};

} // namespace simcom
