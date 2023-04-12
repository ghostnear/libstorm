cmake_minimum_required(VERSION 3.9)

file(
    GLOB
    EXECUTABLE_FILES
    "src/*.cpp"
    "src/system/*.cpp"
    "src/prefabs/*.cpp"
    "src/system/assetTypes/*.cpp"
)

# Add all .cpp files from src
add_library(
    libStorm
    STATIC
    ${EXECUTABLE_FILES}
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
elseif(BUILD_TARGET MATCHES "WIN")
    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL2-image CONFIG REQUIRED)
    find_package(SDL2_ttf CONFIG REQUIRED)

    target_link_libraries(
        libStorm
        PUBLIC
            SDL2::SDL2
            SDL2::SDL2main
            SDL2::SDL2_image
            SDL2_ttf::SDL2_ttf
    )
else()
    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL2_image CONFIG REQUIRED)
    find_package(SDL2_ttf CONFIG REQUIRED)

    target_link_libraries(
        libStorm
        PUBLIC
            SDL2
            SDL2main
            SDL2_image
            SDL2_ttf
    )
endif()
