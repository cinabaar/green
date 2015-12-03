add_subdirectory(shaders)

set(SOURCE_FILES main.cpp utility.cpp utility.hpp Scene.cpp Scene.hpp)
add_executable(green ${SOURCE_FILES})
add_definitions(-DGLM_FORCE_RADIANS)

add_dependencies(green copy_shaders)
target_link_libraries(green cppformat)
target_link_libraries(green ${OPENGL_LIBRARIES})
target_link_libraries(green libglew_shared)
target_link_libraries(green ${GLFW_LIBRARIES} glfw)
target_link_libraries(green assimp)
target_link_libraries(green SOIL)