add_custom_target(copy_shaders
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders
        SOURCES triangle/fragment.glsl triangle/vertex.glsl ripple/vertex.glsl ripple/fragment.glsl
        )
