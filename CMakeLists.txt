cmake_minimum_required(VERSION 3.3)
project(green)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Resolving dependencies
#cppformat
add_subdirectory(deps/cppformat)
include_directories(deps/cppformat)

#easylogging
include_directories(deps/easylogging/src)

#OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

#glew
add_subdirectory(deps/glew)
include_directories(deps/glew/include)

#glfw
add_subdirectory(deps/glfw)
include_directories(${GLFW_SOURCE_DIR}/include)

#glm
include_directories(deps/glm)

#soil
add_subdirectory(deps/soil)
include_directories(deps/soil/src)

#nano signal-slots
include_directories(deps/nano)

IF (WIN32)
add_definitions(-DM_PI=3.14159265358979323846)
add_definitions(-DM_PI_2=1.57079632679489661923)
ENDIF()

#assimp
add_subdirectory(deps/assimp)
include_directories(deps/assimp/include)

add_subdirectory(src)