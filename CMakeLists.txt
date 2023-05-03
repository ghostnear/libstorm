# Minimum PSVita required version.
cmake_minimum_required(VERSION 2.8.12)

# Make sure the target is set as a define.
add_compile_definitions(${BUILD_TARGET})

# PSvita specifics
if(BUILD_TARGET MATCHES "VITA")

    # VitaSDK is required
    if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        if(DEFINED ENV{VITASDK})
            set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
        else()
            message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
        endif()
    endif()

    include("$ENV{VITASDK}/share/vita.cmake" REQUIRED)

endif()

project(libStorm)

file(
    GLOB
    EXECUTABLE_FILES
    "src/*.cpp"
    "src/system/*.cpp"
    "src/prefabs/*.cpp"
    "src/system/AssetTypes/*.cpp"
)

# Add all .cpp files from src
add_library(
    ${PROJECT_NAME}
    STATIC
        ${EXECUTABLE_FILES}
)

# Library properties
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        OUTPUT_NAME storm
)

target_compile_options(
    ${PROJECT_NAME}
    PUBLIC
        -Wall
        -std=c++17
)

# Private directories for "*.h" includes and public directories for <libstorm/*.h> includes
target_include_directories(
    ${PROJECT_NAME}
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
        ${PROJECT_NAME}
        PUBLIC
            # SDL libraries.
            SDL2
            SDL2_ttf
            SDL2_image

            # Stubs required by SDL.
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
            jpeg png webp
            pthread
            freetype
            z m
    )
else()
    # Use your favourite method to find SDL, then use it.
    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL2_image CONFIG REQUIRED)
    find_package(SDL2_ttf CONFIG REQUIRED)

    target_link_libraries(
        ${PROJECT_NAME}
        PUBLIC
            SDL2
            SDL2main
            SDL2_image
            SDL2_ttf
    )
endif()
