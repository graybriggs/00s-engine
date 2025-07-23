cmake_minimum_required(VERSION 3.20)

project(00s-engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -g")

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS})

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

find_package(glfw3 3.3 REQUIRED)

add_subdirectory(mesh)

set(SOURCES
    camera.cpp
    device.cpp
    entity.cpp
    input.cpp
    light.cpp
    main.cpp
    material.cpp
    math/normal_generator.cpp
    mesh/mesh_cube.cpp
    mesh/mesh_line.cpp
    mesh/mesh_model.cpp
    mesh/mesh_quad.cpp
    mesh/mesh_triangle.cpp
    mesh/renderable_mesh.cpp
    model_loader.cpp
    ray.cpp
    scene.cpp
    shader.cpp
    stb_image.cpp
    texture.cpp
    texture_loader.cpp
    timer.cpp
    util/array2d.cpp
    video.cpp
)

add_executable(a ${SOURCES})

target_include_directories(a PRIVATE mesh)
target_include_directories(a PRIVATE math)
target_include_directories(a PRIVATE util)
target_link_libraries(a OpenGL::OpenGL GLEW::GLEW glfw)