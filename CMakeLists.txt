cmake_minimum_required(VERSION 3.24)
project(ProjectTest1)

set(CMAKE_CXX_STANDARD 23)

add_executable(ProjectTest1
        .idea/.gitignore
        .idea/modules.xml
        .idea/ProjectTest1.iml
        .idea/workspace.xml
        main.cpp)


target_link_libraries(ProjectTest1 -lOpenGL32 -lGLU32)