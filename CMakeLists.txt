cmake_minimum_required(VERSION 3.20)

project(00s-engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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
    controls.cpp
    cube.cpp
    device.cpp
    main.cpp
    material.cpp
    mesh.cpp
    shader.cpp
    shape_generator.cpp
    video.cpp
)

target_link_libraries(a OpenGL::OpenGL GLEW::GLEW glfw)