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

# PSVita specifics
if(BUILD_TARGET MATCHES "VITA")
    target_link_libraries(
        libStorm
        PUBLIC
            SDL2
            SDL2_ttf
            SDL2_image
            SceDisplay_stub
            SceCtrl_stub
            SceAudio_stub
            SceAudioIn_stub
            SceSysmodule_stub
            SceGxm_stub
            SceCommonDialog_stub
            SceAppMgr_stub
            SceTouch_stub
            SceHid_stub
            SceMotion_stub
            jpeg
            png
            webp
            pthread
            freetype
            z
            m
    )
else()
    # External dependencies
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/external/sdl2-cmake-modules")

    if(BUILD_TARGET MATCHES "WIN")
        set(SDL2_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/sdl2")
    endif()

    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    target_link_libraries(
        libStorm
        PUBLIC
            SDL2::Core
            SDL2::TTF
            SDL2::Image
    )
endif()