/**
 * simcom client_impl.h
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
#include <thread>

namespace simcom
{

class ClientImpl
{
    DISABLE_COPY(ClientImpl)
  public:
    ClientImpl(Address address, std::string clientId, int batch);
    ClientImpl() = default;
    ClientImpl(ClientImpl&& other) noexcept = default;
    ClientImpl& operator=(ClientImpl&& other) noexcept = default;

    ~ClientImpl();

    NODISCARD Address getAddress() const;

    NODISCARD std::string getId() const;

    NODISCARD int getBatch() const;

    void talkWithServer() const;

    void join();

    void run();

  private:
    Address m_address;
    std::string m_id;
    int m_batch = {0};
    std::unique_ptr<std::thread> m_thread{nullptr};
};

} // namespace simcom
