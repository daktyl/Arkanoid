cmake_minimum_required(VERSION 3.3)
project(Arkanoid)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lallegro -lallegro_image -lallegro_dialog -lm")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES
    allegro_system.h
    blocks.c
    blocks.h
    bouncer.c
    bouncer.h
    config_file.c
    config_file.h
    floor.c
    floor.h
    global_vars.h
    main.c)

add_executable(Arkanoid ${SOURCE_FILES})