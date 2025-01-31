cmake_minimum_required( VERSION 3.15...3.31 )

project( fpsgl )

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw-3.4)
add_subdirectory(external/glad)

set( fpsgl_source
        main.cpp
        render.cpp
        )

add_executable( fpsgl ${fpsgl_source} )

target_sources(fpsgl PRIVATE ${fpsgl_source})

target_link_libraries(fpsgl PRIVATE OpenGL::GL glfw glad)

target_include_directories(fpsgl PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          )
