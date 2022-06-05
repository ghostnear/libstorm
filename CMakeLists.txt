cmake_minimum_required(VERSION 3.9)

# Add all .cpp files from src
add_library(
    libStorm
    STATIC
    "src/msgbox.cpp"
    "src/window.cpp"
    "src/libstorm.cpp"
)

# Library properties
set_target_properties(libStorm PROPERTIES OUTPUT_NAME storm)

# SDL2 for graphics and stuff
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

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
        ${SDL2_LIBRARIES}
)