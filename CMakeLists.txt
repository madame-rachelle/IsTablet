cmake_minimum_required(VERSION 3.10)
project(TestHandheld)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS OFF)

add_executable(TestHandheld test-handheld.cpp showpopup.cpp)

if(UNIX)
	set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")
	find_package(X11 REQUIRED)
	if(X11_FOUND)
		include_directories(${X11_INCLUDE_DIR})
		target_link_libraries(TestHandheld PRIVATE ${X11_LIBRARIES})
	else()
		message(FATAL_ERROR "X11 libraries not found!")
	endif()
elseif(WIN32)
	# Windows-specific libraries (Win32 API is built-in, no extra linking needed)
	target_compile_definitions(TestHandheld PRIVATE -D_WIN32_WINNT=0x0601)
endif()
