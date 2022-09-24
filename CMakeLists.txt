cmake_minimum_required(VERSION 2.8.12)
project(Chip-8)

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(chip8
    src/main.cpp
    src/Opcodes.cpp
    src/Chip8Machine.cpp
)
target_link_libraries(chip8 ${CONAN_LIBS})