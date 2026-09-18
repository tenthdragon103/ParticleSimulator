cmake_minimum_required(VERSION 3.20)

project(ParticleSimulator C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

add_executable(ParticleSimulator
        src/main.c

        src/include/renderer.c

        src/drawings.c
        src/drawings.h

        src/ui.c
        src/ui.h

        src/physics/vec2.c
        src/physics/vec2.h

        src/physics/particle.c
        src/physics/particle.h

        src/physics/particle_system.c
        src/physics/particle_system.h

        src/physics/spatial_grid.c
        src/physics/spatial_grid.h

        src/physics/collision.c
        src/physics/collision.h

        src/physics/integrator.c
        src/physics/integrator.h

        src/physics/physics_world.c
        src/physics/physics_world.h

        src/physics/physics.c
        src/physics/physics.h
        src/physics/boundary.c
        src/physics/boundary.h
)

target_include_directories(ParticleSimulator
        PRIVATE
        src/include
        src/physics
)

target_link_libraries(ParticleSimulator
        PRIVATE
        raylib
)