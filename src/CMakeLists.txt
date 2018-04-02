if(WIN32)
	set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11")
else()
	set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
endif()

add_executable(lava main.cpp)

target_link_libraries(lava Vulkan::Vulkan)
target_link_libraries(lava glfw)
