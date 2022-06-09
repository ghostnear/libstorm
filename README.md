# Libstorm
Simple C++ framework aimed for my ease of use. I made it open-source so anyone else that wants to use it can.

## How to use

Add the directory of the lib to your CMake project and include it using add_subdirectory.

## Requirements

### Windows

- sdl2 provided from the [official SDL2 website](https://www.libsdl.org/). Use the version compatible with your compiler (MinGW / MSVSC++) and copy it to the /external/sdl2 folder (make it if it does not exist).

### Unix

- libsdl2-dev for Ubuntu, sdl2 for Arch Linux.

### PSVita

- [VitaSDK](https://vitasdk.org/)
