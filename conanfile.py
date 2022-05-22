import os
from conans import ConanFile


class CommunicationSimulator(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        "gtest/cci.20210126",
        "poco/1.11.2",
        "openssl/1.1.1o",
    ]
    generators = "cmake_find_package", "cmake_paths", "virtualenv"
    short_paths = True

    default_options = {
        "poco:shared": True,
        "poco:enable_data": True,
        "poco:enable_mongodb": False,
        "poco:enable_data_sqlite": True,
        "poco:enable_data_mysql": False,
        "poco:enable_data_odbc": False,
        "poco:enable_data_postgresql": False,
        "poco:enable_active_record": False,
        "poco:enable_encodings": False,
        "poco:enable_jwt": False,
        "openssl:shared": True,
    }

    class Pkg(ConanFile):
        keep_imports = True

    def imports(self):
        if self.settings.os == "Windows":
            self.copy("*.dll", dst="bin/lib", src="lib")  # From bin to bin
        if self.settings.os == "Linux":
            self.copy("*.so*", dst="bin/lib", src="lib")  # From bin to bin
        if self.settings.os == "Macos":
            self.copy("*.dylib*", dst="bin/lib", src="lib")  # From lib to bin

    def configure(self):
        os.environ["CONAN_SYSREQUIRES_MODE"] = "enabled"
