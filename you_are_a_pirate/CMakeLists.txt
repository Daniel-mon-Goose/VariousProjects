cmake_minimum_required(VERSION 3.12)
project(you_are_a_pirate)

set(CMAKE_CXX_STANDARD 17)

add_executable(you_are_a_pirate main.cpp battleship.cpp shipcreators.cpp seafield.cpp gameview.cpp gameprocess.cpp players.cpp observer_pattern.cpp observer_pattern.hpp)