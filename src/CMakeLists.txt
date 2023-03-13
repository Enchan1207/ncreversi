#
# ncreversi sources
#

cmake_minimum_required(VERSION 3.21)

add_executable(ncreversi)
target_sources(ncreversi PRIVATE
    game/game.cpp
    screen/initialize.cpp
    screen/static.cpp
    screen/dynamic.cpp
    player/shellplayer.cpp
    player/computerplayer.cpp

    main.cpp
)
target_include_directories(ncreversi PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${collection2_SOURCE_DIR}/include
    ${flipstone_SOURCE_DIR}/include
    ${NCURSES_ROOT}/include
)
target_link_directories(ncreversi PRIVATE
    ${NCURSES_ROOT}/lib
)
target_compile_options(ncreversi PRIVATE
    -Wall
)
target_link_libraries(ncreversi PRIVATE
    ncurses
    reversi
)
