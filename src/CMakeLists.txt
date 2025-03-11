cmake_minimum_required( VERSION 3.15...3.31 )

project( fpsgl )

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw-3.4)
add_subdirectory(external/glad)
add_subdirectory(external/stb_image)
add_subdirectory(external/glm-1.0.1)

set( fpsgl_source
        main.cpp
        render.cpp
        mesh.cpp
        texture.cpp
        shader.cpp
        camera.cpp
        map_parser.cpp
        )

add_executable( fpsgl ${fpsgl_source} )

target_sources(fpsgl PRIVATE ${fpsgl_source})

target_link_libraries(fpsgl PRIVATE OpenGL::GL glfw glad stb_image glm)

target_include_directories(fpsgl PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          )
