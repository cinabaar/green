add_subdirectory(shaders)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES main.cpp utility.cpp utility.hpp input/Input.cpp input/Input.hpp
        scenes/SceneTriangle.cpp scenes/SceneTriangle.hpp
        scenes/SceneRipple.cpp scenes/SceneRipple.hpp)
add_executable(green ${SOURCE_FILES})
add_definitions(-DGLM_FORCE_RADIANS)

add_dependencies(green copy_shaders)
target_link_libraries(green cppformat)
target_link_libraries(green ${OPENGL_LIBRARIES})
target_link_libraries(green libglew_shared)
target_link_libraries(green ${GLFW_LIBRARIES} glfw)
target_link_libraries(green assimp)
target_link_libraries(green SOIL)