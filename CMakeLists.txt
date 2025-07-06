cmake_minimum_required(VERSION 3.20)

project(00s-engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS})

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

find_package(glfw3 3.3 REQUIRED)

add_executable(a
    camera.cpp
    controls.cpp
    device.cpp
    entity.cpp
    input.cpp
    main.cpp
    material.cpp
    renderable_mesh.cpp
    mesh_cube.cpp
    mesh_line.cpp
    mesh_model.cpp
    mesh_quad.cpp
    mesh_triangle.cpp
    model_loader.cpp
    shader.cpp
    shape_generator.cpp
    stb_image.cpp
    texture_loader.cpp
    timer.cpp
    video.cpp
)

target_link_libraries(a OpenGL::OpenGL GLEW::GLEW glfw)