cmake_minimum_required(VERSION 3.6)
project(dorkanoid)

set(CMAKE_CXX_STANDARD 17)
# set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

add_executable(dorkanoid
    src/main.cpp
    src/entities/ball.cpp
    src/entities/brick.cpp
    src/entities/brickyard.cpp
    src/entities/paddle.cpp
    src/managers/sound_manager.cpp
    src/stages/stage_one.cpp
    src/util/timer.cpp
    src/util/util_str.cpp
)

target_include_directories(dorkanoid PRIVATE
    src
    src/entities
    src/managers
    src/stages
    src/util
)

target_sources(dorkanoid PRIVATE media/icon.rc)

# Add MSVC compiler options
if (WIN32)
    if (MSVC)
        add_compile_options(/W3 /Za /TP /permissive-)
        set_property(TARGET dorkanoid PROPERTY
             MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif (MSVC)
endif (WIN32)

# The package sfml provides CMake targets:

#     find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
#     target_link_libraries(main PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

#     # If you want SFML to provide an implementation of main():
#     target_link_libraries(main PRIVATE sfml-main)
target_link_options(dorkanoid PRIVATE "/SUBSYSTEM:WINDOWS")
target_link_libraries(dorkanoid PRIVATE sfml-system sfml-audio sfml-graphics sfml-window sfml-main)

