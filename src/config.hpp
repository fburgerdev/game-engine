#pragma once

#define PT_UNKNOWN 0

// config
#define PT_DEBUG 1
#define PT_OPTIMIZED 2
#define PT_DIST 3

// platform
#define PT_LINUX 1
#define PT_WINDOWS 2

// render api
#define PT_OPENGL 1

// window api
#define PT_GLFW 1

// config
#if defined(DEBUG)
    #define PT_CONFIG PT_DEBUG
#elif defined(OPTIMIZED)
    #define PT_CONFIG PT_OPTIMIZED
#elif defined(DIST)
    #define PT_CONFIG PT_DIST
#else
    #define PT_CONFIG PT_UNKNOWN 
#endif
#define PT_VERSION_MAJOR 0
#define PT_VERSION_MINOR 1
#define PT_PLATFORM PT_LINUX
#define PT_RENDER_API PT_OPENGL
#define PT_WINDOW_API PT_GLFW
