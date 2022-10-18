# Libstorm
Simple C++ framework aimed for my ease of use. I made it open-source so anyone else that wants to use it can.

## How to use

Add the directory of the lib to your CMake project and include it using add_subdirectory.

## Requirements

### Windows
- vcpkg installed and available to use trough the commandline (added to PATH).
- preferably use scoop to install, as it is much easier.
- run the install-deps.bat script from the scripts folder.
- change the vcpkg path from the build.bat file to point in the right direction.
- TODO: make use of an environment variable or something.

### Unix

- libsdl2-dev for Ubuntu, sdl2 for Arch.
- libsdl2-ttf-dev for Ubuntu, sdl2_ttf for Arch.
- libsdl2-img-dev for Ubuntu, sdl2_img for Arch.

### PSVita

- [VitaSDK](https://vitasdk.org/)
