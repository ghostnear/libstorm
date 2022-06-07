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
add_subdirectory(external)

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
        sdl2
)