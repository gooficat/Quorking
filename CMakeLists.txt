cmake_minimum_required(VERSION 3.15)

    project(Quorking LANGUAGES CXX C)
        
    # Set CXX standard
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
        
    # Find vcpkg packages if available
    find_package(PkgConfig QUIET)
        
    # Include directories
    include_directories(include)
        
    # Add executable
    add_executable(Quorking 
            src/engine/MESH.CPP
            src/engine/MODEL.CPP
            src/engine/NODE.CPP
            src/engine/SCENE.CPP
            src/engine/SHADER.CPP
            src/engine/TRANSFORM.CPP
            src/engine/UTIL.CPP

            src/GAME.CPP
            src/MAIN.CPP
            src/glad.c
    )
        
    # Compiler-specific options
    if(MSVC)
        target_compile_options(Quorking PRIVATE /W4)
    else()
        target_compile_options(Quorking PRIVATE -Wall -Wextra -Wpedantic)
    endif()
        
    # Debug configuration
    set(CMAKE_BUILD_TYPE Debug)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(Quorking PRIVATE DEBUG)
        if(NOT MSVC)
            target_compile_options(Quorking PRIVATE -g -O0)
        endif()
    endif()
        
    # Enable testing
    enable_testing()
        
    # Install target
    #install(TARGETS Quorking RUNTIME DESTINATION bin)
    

    find_package(OpenGL REQUIRED)

    target_link_libraries(
        Quorking
        opengl32
        glfw3
    )