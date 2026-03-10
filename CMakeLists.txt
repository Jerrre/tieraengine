cmake_minimum_required( VERSION 3.15...3.31 )

project( tieraengine )

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw-3.4)
add_subdirectory(external/glad)
add_subdirectory(external/stb_image)
add_subdirectory(external/glm-1.0.1)

set( tieraengine_source
        src/render.cpp
        src/mesh.cpp
        src/texture.cpp
        src/shader.cpp
        src/camera.cpp
        )

add_library(tieraengine STATIC ${tieraengine_source})

target_include_directories(tieraengine PUBLIC ${PROJECT_SOURCE_DIR}/include )

target_link_libraries(tieraengine
  PUBLIC
  OpenGL::GL
  glfw
  glad
  stb_image
  glm
)


