/**
 * simcom client_application.h
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

#include "Poco/Util/ServerApplication.h"
#include "helpers.h"

namespace simcom
{
class ClientApplication : public Poco::Util::Application
{
    DISABLE_COPY_AND_MOVE(ClientApplication)

  public:
    explicit ClientApplication();

    ~ClientApplication() override = default;

  protected:
    int main(const ArgVec& args) override;

    void initialize(Application& self) override;

    void reinitialize(Application& self) override;

    void uninitialize() override;

    void defineOptions(Poco::Util::OptionSet& options) override;

    void handleOption(const std::string& name, const std::string& value) override;

    void handleHelp(const std::string& name, const std::string& value);
};

} // namespace simcom
