add_library(graphics window.cpp vulkaninstance.cpp)

target_link_libraries(graphics Vulkan::Vulkan)
target_link_libraries(graphics glfw)
target_link_libraries(graphics logging)
