cmake_minimum_required(VERSION 3.15)
project(Focus C)

set(CMAKE_C_STANDARD 11)

file(GLOB game_SRC
        "src/*.c"
        )
file(GLOB game_INCLUDE
        "src/*.h"
        )

add_executable(Focus src/main.c src/UserInterface.h src/UserInterface.c src/GAME_SETUP.h src/GAME_SETUP.c)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

if (NOT CURSES_HAVE_CURSES_H AND CURSES_HAVE_NCURSES_CURSES_H)
    include_directories(${CURSES_INCLUDE_DIR}/ncurses)
endif ()
set(CURSES_NEED_WIDE TRUE)
target_link_libraries(Focus ${CURSES_LIBRARIES})