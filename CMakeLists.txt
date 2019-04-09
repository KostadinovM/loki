cmake_minimum_required(VERSION 3.0)

project(loki)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(loki/vendor/GLFW)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(loki/vendor/assimp)

find_package(OpenGL REQUIRED)

include_directories(loki/vendor/GLFW/include/
					loki/vendor/Glad/include/
					loki/vendor/imgui/
					loki/vendor/glm/
					loki/vendor/stb_image/
					loki/vendor/assimp/include/
					)

file(GLOB_RECURSE _source_list loki/src/*.cpp
							   loki/src/*.h
							   loki/src/*.glsl
							   loki/src/*.glsl
							   loki/vendor/imgui/*.cpp
							   loki/vendor/imgui/*.h
							   loki/vendor/glad/*.c
							   loki/vendor/stb_image/*.h
							   loki/vendor/stb_image/*.cpp)
							   
#Organizes the source code of the solution in folders							   
foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

add_executable(${PROJECT_NAME} ${_source_list})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
target_link_libraries(${PROJECT_NAME} assimp glfw ${GLFW_LIBRARIES})						
						


