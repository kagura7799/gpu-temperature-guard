cmake_minimum_required(VERSION 3.16)
project(gpu-temperature-guard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/vcpkg/vcpkg/installed/x64-windows")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(gpu-temperature-guard
    src/main.cpp
    vendor/imgui/src/imgui.cpp
    vendor/imgui/src/imgui_draw.cpp
    vendor/imgui/src/imgui_tables.cpp
    vendor/imgui/src/imgui_widgets.cpp
    vendor/imgui/src/imgui_impl_glfw.cpp
    vendor/imgui/src/imgui_impl_opengl3.cpp
)

target_include_directories(gpu-temperature-guard PUBLIC
    vendor/imgui/include/
)

target_link_libraries(gpu-temperature-guard PUBLIC
    OpenGL::GL
    glfw
)
