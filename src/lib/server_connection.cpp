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

#include "server_connection.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Timestamp.h"
#include "Poco/Util/Application.h"

using Poco::DateTimeFormat;
using Poco::DateTimeFormatter;
using Poco::Timestamp;
using Poco::Util::Application;

namespace simcom
{

ServerConnection::ServerConnection(const Poco::Net::StreamSocket& s) : TCPServerConnection(s)
{
}

void ServerConnection::run()
{
    Application& app = Application::instance();
    app.logger().information("Request from " + this->socket().peerAddress().toString());
    try
    {
        Timestamp now;
        std::string dt(DateTimeFormatter::format(now, DateTimeFormat::ISO8601_FORMAT));
        dt.append("\r\n");
        socket().sendBytes(dt.data(), (int)dt.length());
    }
    catch (Poco::Exception& exc)
    {
        app.logger().log(exc);
    }
}

} // namespace simcom
