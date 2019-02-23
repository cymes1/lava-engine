add_library(graphics window.cpp vulkaninstance.cpp surface.cpp physicaldevice.cpp device.cpp)

target_link_libraries(graphics Vulkan::Vulkan)
target_link_libraries(graphics glfw)
target_link_libraries(graphics logging)
