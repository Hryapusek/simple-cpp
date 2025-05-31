import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout, CMakeDeps
from conan.tools.build import check_min_cppstd
from conan.tools.files import copy, rmdir


class ExampleQtTcpServerRecipe(ConanFile):
    name = "example-qt-tcp-server"
    version = "0.0.1"

    settings = "os", "compiler", "build_type"

    exports_sources = "*", "!build/*", "!CMakeUserPresets.json"

    options = {
        'shared': [True, False],
    }

    default_options = {
        'shared': True,
    }

    @property
    def _min_cppstd(self):
        return '20'

    def requirements(self):
        pass
    
    def layout(self):
        cmake_layout(self)

    def validate(self):
        if self.settings.compiler.get_safe("cppstd"):
            check_min_cppstd(self, self._min_cppstd)

    def configure(self):
        pass

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.cache_variables["BUILD_SHARED_LIBS"] = self.options.shared
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
