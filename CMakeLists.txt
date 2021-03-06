cmake_minimum_required(VERSION 3.9)

# Add all .cpp files from src
add_library(
    libStorm
    STATIC
    "src/libstorm.cpp"
    "src/ecs/base.cpp"
    "src/ecs/systems.cpp"
    "src/oop/base.cpp"
    "src/system/input.cpp"
    "src/system/window.cpp"
    "src/system/graphics.cpp"
    "src/system/gamemanager.cpp"
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
    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL2-image CONFIG REQUIRED)
    find_package(SDL2-ttf CONFIG REQUIRED)

    target_link_libraries(
        libStorm
        PUBLIC
            SDL2::SDL2
            SDL2::SDL2main
            SDL2::SDL2_ttf
            SDL2::SDL2_image
    )
endif()