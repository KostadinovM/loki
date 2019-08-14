cmake_minimum_required(VERSION 3.0)

project(sandbox)

add_executable(${PROJECT_NAME}  src/main.cpp
								src/lightdemo.cpp
								src/imguidemo.cpp
								src/assimpdemo.cpp
								src/assimplightsdemo.cpp
								src/meshdemo.cpp
								src/architecturedemo.cpp)

include_directories(${CMAKE_SOURCE_DIR}/loki/vendor/GLFW/include/
					${CMAKE_SOURCE_DIR}/loki/vendor/Glad/include/
					${CMAKE_SOURCE_DIR}/loki/vendor/imgui/
					${CMAKE_SOURCE_DIR}/loki/vendor/glm/
					${CMAKE_SOURCE_DIR}/loki/vendor/stb_image/
					${CMAKE_SOURCE_DIR}/loki/vendor/assimp/include/
					${CMAKE_SOURCE_DIR}/loki/src/
					${CMAKE_SOURCE_DIR}/loki/src/graphics/
					)

	#Organizes the source code of the solution in folders							   
foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()				
					
target_link_libraries(sandbox loki)

install(TARGETS sandbox RUNTIME DESTINATION bin)