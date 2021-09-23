from conans import ConanFile, CMake


class CommonUtilities(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "fmt/[>=8.0.0]", "gtest/[>=1.8.1]", "stduuid/1.0"
    generators = "cmake"
