cmake_minimum_required(VERSION 3.3)
project(Arkanoid)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lallegro -lallegro_image -lallegro_dialog -lm")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES
        src/allegro_system.h
        src/blocks.c
        src/blocks.h
        src/bouncer.c
        src/bouncer.h
        src/config_file.c
        src/config_file.h
        src/floor.c
        src/floor.h
        src/global_vars.h
        src/main.c)

add_executable(Arkanoid ${SOURCE_FILES})