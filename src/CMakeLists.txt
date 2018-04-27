add_executable(lava main.cpp game.cpp)

add_subdirectory(utils)
add_subdirectory(graphics)

target_link_libraries(lava Vulkan::Vulkan)
target_link_libraries(lava glfw)
target_link_libraries(lava logging)
target_link_libraries(lava graphics)
