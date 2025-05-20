cmake_minimum_required(VERSION 3.16)
project(gpu-temperature-guard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(vendor/glfw3)

find_package(CUDA)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

find_library(NVAPI_LIB_FILE_PATH 
    NAMES nvapi64
    PATHS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/nvapi/amd64/"
    NO_DEFAULT_PATH
    REQUIRED
)

add_executable(gpu-temperature-guard
    src/main.cpp
    src/nvidia_get_info.cpp
    src/ui/fonts/NotoSans-VariableFont_wdth,wght_font.h
    vendor/imgui/src/imgui.cpp
    vendor/imgui/src/imgui_draw.cpp
    vendor/imgui/src/imgui_tables.cpp
    vendor/imgui/src/imgui_widgets.cpp
    vendor/imgui/src/imgui_impl_glfw.cpp
    vendor/imgui/src/imgui_impl_opengl3.cpp
    vendor/imgui/src/imgui_demo.cpp
)

target_include_directories(gpu-temperature-guard PUBLIC
    vendor/imgui/include/
    vendor/nvapi/
    vendor/glfw3/include
)

target_link_libraries(gpu-temperature-guard PUBLIC
    OpenGL::GL
    glfw
    ${NVAPI_LIB_FILE_PATH}
)

# set_target_properties(gpu-temperature-guard PROPERTIES
#    WIN32_EXECUTABLE TRUE
# )