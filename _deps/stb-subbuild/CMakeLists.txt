# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.12.2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(stb-populate NONE)

include(ExternalProject)
ExternalProject_Add(stb-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/nothings/stb.git"
                    SOURCE_DIR          "/goinfre/yechen/Desktop/Bomberman/_deps/stb-src"
                    BINARY_DIR          "/goinfre/yechen/Desktop/Bomberman/_deps/stb-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)
