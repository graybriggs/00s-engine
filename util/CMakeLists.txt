#./mesh/CMakeLists.txt

set(dir ${CMAKE_CURRENT_SOURCE_DIR})

list(
    APPEND src
    ${dir}/array2d.cpp
)

set(src ${src} PARENT_SCOPE)