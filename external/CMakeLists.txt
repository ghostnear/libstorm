# Libstorm dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/sdl2-cmake-scripts")

if(WIN32)
  set(SDL2_PATH "${CMAKE_CURRENT_SOURCE_DIR}/sdl2")
endif()

find_package(SDL2 REQUIRED)
add_library(sdl2 INTERFACE)
target_include_directories(sdl2 INTERFACE "${SDL2_INCLUDE_DIR} ${SDL2_GPU_INCLUDE_PATH}")
target_link_libraries(sdl2 INTERFACE "${SDL2_LIBRARY}")