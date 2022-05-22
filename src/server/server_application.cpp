/**
 * simcom server_application.cpp
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

#include "server_application.h"
#include "Poco/Util/HelpFormatter.h"
#include "server.h"
#include <iostream>
#include <sstream>

POCO_SERVER_MAIN(simcom::SimComServer)

using Poco::Util::HelpFormatter;
using Poco::Util::OptionCallback;
using Poco::Util::ServerApplication;

namespace simcom
{

SimComServer::SimComServer()
{
    logger().debug("Object instantiate");
}

void SimComServer::defineOptions(Poco::Util::OptionSet& options)
{
    logger().debug("Adding application options");
    ServerApplication::defineOptions(options);

    options.addOption(Poco::Util::Option("help", "h", "Display available options")
                          .required(false)
                          .repeatable(false)
                          .callback(OptionCallback<SimComServer>(this, &SimComServer::handleHelp)));
    options.addOption(Poco::Util::Option("port", "p", "Server listen port")
                          .required(true)
                          .repeatable(false)
                          .argument("value")
                          .binding("server.port"));
}

void SimComServer::initialize(Poco::Util::Application& self)
{
    loadConfiguration();
    Application::initialize(self);
}

void SimComServer::reinitialize(Poco::Util::Application& self)
{
    Application::reinitialize(self);
}

void SimComServer::uninitialize()
{
    Application::uninitialize();
}

void SimComServer::handleOption(const std::string& name, const std::string& value)
{
    Application::handleOption(name, value);
}

void SimComServer::handleHelp(const std::string& /*name*/, const std::string& /*value*/)
{
    HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("A small communications simulation project.\n"
                            "This is the server application.");
    helpFormatter.format(std::cout);
    stopOptionsProcessing();
}

int SimComServer::main(const ArgVec& /*args*/)
{
    auto port = this->config().getInt("server.port");

    Server server(port);
    logger().information("Server created");
    server.start();
    logger().information("Server listens on port %d", port);
    waitForTerminationRequest();
    logger().information("I have a termination request");
    server.stop();
    logger().information("Server stopped");
    return Application::EXIT_OK;
}

} // namespace simcom
