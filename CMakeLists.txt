cmake_minimum_required(VERSION 3.14)
project(glad LANGUAGES C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

string(COMPARE EQUAL "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}" GLAD_STANDALONE)

if (MSVC)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

add_library(glad_GL STATIC
    src/gl.c)
add_library(glad_EGL STATIC
    src/egl.c)
add_library(glad_GLX STATIC
    src/glx.c)
add_library(glad_Vulkan STATIC
    src/vulkan.c)
add_library(glad_WGL STATIC
    src/wgl.c)

target_include_directories(glad_GL PUBLIC include)
target_include_directories(glad_EGL PUBLIC include)
target_include_directories(glad_GLX PUBLIC include)
target_include_directories(glad_Vulkan PUBLIC include)
target_include_directories(glad_WGL PUBLIC include)

target_link_libraries(glad_GL PUBLIC xxHash::xxhash)
target_link_libraries(glad_EGL PUBLIC xxHash::xxhash)
target_link_libraries(glad_GLX PUBLIC xxHash::xxhash)
target_link_libraries(glad_Vulkan PUBLIC xxHash::xxhash)
target_link_libraries(glad_WGL PUBLIC xxHash::xxhash)

set_target_properties(glad_GL PROPERTIES FOLDER "GLAD")
set_target_properties(glad_EGL PROPERTIES FOLDER "GLAD")
set_target_properties(glad_GLX PROPERTIES FOLDER "GLAD")
set_target_properties(glad_Vulkan PROPERTIES FOLDER "GLAD")
set_target_properties(glad_WGL PROPERTIES FOLDER "GLAD")

if (NOT GLAD_STANDALONE)
	set_target_properties(glad_GL PROPERTIES EXCLUDE_FROM_ALL TRUE)
	set_target_properties(glad_EGL PROPERTIES EXCLUDE_FROM_ALL TRUE)
	set_target_properties(glad_GLX PROPERTIES EXCLUDE_FROM_ALL TRUE)
	set_target_properties(glad_Vulkan PROPERTIES EXCLUDE_FROM_ALL TRUE)
	set_target_properties(glad_WGL PROPERTIES EXCLUDE_FROM_ALL TRUE)
endif()

add_library(glad::GL ALIAS glad_GL)
add_library(glad::EGL ALIAS glad_EGL)
add_library(glad::GLX ALIAS glad_GLX)
add_library(glad::Vulkan ALIAS glad_Vulkan)
add_library(glad::WGL ALIAS glad_WGL)
