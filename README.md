# CHIP-8

This is a chip-8 emulator I built in order to learn more about emulators

## Building

Make sure the following programs are installed:
* A C++ 11 compatible compiler
* CMake (Build System)
* Conan (Package Manager)

At project root run:
```sh
mkdir build
cd build
conan install ..
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```
> **Note** I'm passing the build type in both commands because some cmake targets requires it during generation and some during compilation

## Running 

```sh
chip8 <path_to_game>
```