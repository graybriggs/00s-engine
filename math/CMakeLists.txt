#./mesh/CMakeLists.txt

set(dir ${CMAKE_CURRENT_SOURCE_DIR})

list(
    APPEND src
    ${dir}/normal_generator.cpp
)

set(src ${src} PARENT_SCOPE)