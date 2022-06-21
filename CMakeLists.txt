cmake_minimum_required(VERSION 3.21)
project(frick)

set(CMAKE_CXX_STANDARD 20)

add_executable(frick main.cpp camera.cpp generation.cpp function.h camera.h function.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(frick sfml-system sfml-window sfml-graphics sfml-audio)