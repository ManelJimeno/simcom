/**
 * simcom client_application.cpp
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

#include "client_application.h"
#include "Poco/Util/HelpFormatter.h"
#include "client.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

POCO_APP_MAIN(simcom::ClientApplication)

using Poco::Util::Application;
using Poco::Util::HelpFormatter;
using Poco::Util::OptionCallback;
using namespace std::chrono_literals;

namespace simcom
{

ClientApplication::ClientApplication()
{
    logger().debug("Object instantiate");
}

void ClientApplication::defineOptions(Poco::Util::OptionSet& options)
{
    logger().debug("Adding application options");
    Application::defineOptions(options);

    options.addOption(Poco::Util::Option("help", "h", "Display available options")
                          .required(false)
                          .repeatable(false)
                          .callback(OptionCallback<ClientApplication>(this, &ClientApplication::handleHelp)));

    options.addOption(
        Poco::Util::Option("server", "s",
                           "Indicates the official name, an alias, or the Internet address of a remote host")
            .required(true)
            .repeatable(false)
            .argument("value")
            .binding("server.host"));

    options.addOption(Poco::Util::Option("port", "p", "Indicates a port number")
                          .required(true)
                          .repeatable(false)
                          .argument("value")
                          .binding("server.port"));

    options.addOption(Poco::Util::Option("connections", "c", "Total number of connections")
                          .required(true)
                          .repeatable(false)
                          .argument("value")
                          .binding("server.connections"));

    options.addOption(Poco::Util::Option("delay", "d", "Delay between connections")
                          .required(true)
                          .repeatable(false)
                          .argument("value")
                          .binding("server.delay"));

    options.addOption(Poco::Util::Option("parallel", "a", "Parallel connections")
                          .required(true)
                          .repeatable(false)
                          .argument("value")
                          .binding("server.parallel"));
}

void ClientApplication::initialize(Poco::Util::Application& self)
{
    loadConfiguration();
    Application::initialize(self);
}

void ClientApplication::reinitialize(Poco::Util::Application& self)
{
    Application::reinitialize(self);
}

void ClientApplication::uninitialize()
{
    Application::uninitialize();
}

void ClientApplication::handleOption(const std::string& name, const std::string& value)
{
    Application::handleOption(name, value);
}

void ClientApplication::handleHelp(const std::string& /*name*/, const std::string& /*value*/)
{
    HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("A small communications simulation project.\n"
                            "This is the server application.");
    helpFormatter.format(std::cout);
    stopOptionsProcessing();
}

int ClientApplication::main(const ArgVec& /*args*/)
{
    Address address(this->config().getString("server.host"), this->config().getInt("server.port"));
    auto connections = this->config().getInt("server.connections");
    auto delay = this->config().getInt("server.delay");
    auto parallel = this->config().getInt("server.parallel");
    auto counter = 0;
    auto batch = 1;

    std::vector<Client> clients;

    // Create clients
    for (counter = 1; counter <= connections; counter++)
    {
        if ((counter % parallel) == 0)
        {
            batch++;
        }
        clients.emplace_back(Client(address, std::to_string(counter), batch));
    }

    // Launch the clients by batches
    batch = 1;
    for (auto& client : clients)
    {
        if (client.getBatch() != batch)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            batch = client.getBatch();
        }
        client.run();
    }

    // Wait until all clients have finished
    for (auto& client : clients)
    {
        client.join();
    }

    return Application::EXIT_OK;
}

} // namespace simcom
