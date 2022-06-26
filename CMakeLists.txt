cmake_minimum_required(VERSION 3.21)
project(frick)

set(CMAKE_CXX_STANDARD 20)

add_library(default INTERFACE)
target_compile_features(default INTERFACE cxx_std_20)
enable_testing()

# Добавление SFML по инструкции с главной страницы.
add_executable(frick main.cpp camera.cpp generation.cpp function.h camera.h function.h tests.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(frick sfml-system sfml-window sfml-graphics sfml-audio)

# Добавление файла с тестами, который взяли из домашних работ.
add_library(doctest STATIC external/doctest.cpp)
target_include_directories(doctest PUBLIC external/)
set_target_properties(doctest PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_library(doctest::doctest ALIAS doctest)
add_library(Catch2::Catch2 ALIAS doctest)

add_executable(project-tests tests.cpp generation.cpp function.h)
target_link_libraries(project-tests PUBLIC doctest default)
add_test(NAME project-tests COMMAND project-tests --force-colors -d)