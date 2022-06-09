cmake_minimum_required(VERSION 3.9)

# Add all .cpp files from src
add_library(
    libStorm
    STATIC
    "src/libstorm.cpp"
    "src/game/ecs.cpp"
    "src/game/gamemanager.cpp"
    "src/input/input.cpp"
    "src/rendering/window.cpp"
    "src/rendering/msgbox.cpp"
    "src/rendering/graphics.cpp"
)

# Library properties
set_target_properties(libStorm PROPERTIES OUTPUT_NAME storm)

# External dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/external/sdl2-cmake-modules")

if(WIN32)
  set(SDL2_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/sdl2")
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_gfx REQUIRED)

# Private directories for "*.h" includes and public directories for <libstorm/*.h> includes
target_include_directories(
    libStorm
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/libstorm>
        $<INSTALL_INTERFACE:include/libstorm
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(
    libStorm
    PUBLIC
        SDL2::Core
)