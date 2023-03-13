#
# ncreversi
#

#
# project configuration
#
cmake_minimum_required(VERSION 3.0)
project(ncreversi
    VERSION 0.1.0
    DESCRIPTION "parse and evaluate formula"
    LANGUAGES C CXX
)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#
# global dependencies
#
include(FetchContent)
FetchContent_Declare(
    flipstone
    GIT_REPOSITORY https://github.com/Enchan1207/flipstone
    GIT_TAG v2.2.1
)
FetchContent_MakeAvailable(flipstone)

#
# build configuration
#
set(NCURSES_ROOT "/usr/local" CACHE PATH "Root directory path of ncurses")

#
# subdirectories
#
add_subdirectory(src)
