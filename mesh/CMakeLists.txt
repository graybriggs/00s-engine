#./mesh/CMakeLists.txt

set(dir ${CMAKE_CURRENT_SOURCE_DIR})

list(
    APPEND src
    ${dir}/mesh_cube.cpp
    ${dir}/mesh_line.cpp
    ${dir}/mesh_model.cpp
    ${dir}/mesh_quad.cpp
    ${dir}/mesh_triangle.cpp
    #${dir}/renderable_mesh.cpp
)

set(src ${src} PARENT_SCOPE)