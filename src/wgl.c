/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#if defined(__x86_64__) || defined(__i386__) || defined(_M_IX86) || defined(_M_X64)
#include <immintrin.h>
#elif defined(__aarch64__) || defined(__arm__) || defined(_M_ARM) || defined(_M_ARM64)
#include <arm_neon.h>
#endif

#define XXH_INLINE_ALL
#include "xxhash.h"

#include <glad/wgl.h>

#ifdef _WIN32
#ifndef GLAD_IMPL_UTIL_C_
#define GLAD_IMPL_UTIL_C_

#ifdef _MSC_VER
#define GLAD_IMPL_UTIL_SSCANF sscanf_s
#else
#define GLAD_IMPL_UTIL_SSCANF sscanf
#endif

#undef GLAD_NO_INLINE
#ifdef _MSC_VER
#define GLAD_NO_INLINE __declspec(noinline)
#else
#define GLAD_NO_INLINE __attribute__((noinline))
#endif

#define GLAD_ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

typedef struct {
    uint16_t first;
    uint16_t second;
} GladAliasPair_t;

#endif /* GLAD_IMPL_UTIL_C_ */

#ifdef __cplusplus
extern "C" {
#endif

static const char *GLAD_WGL_fn_names[] = {
    /*    0 */ "ChoosePixelFormat",
    /*    1 */ "DescribePixelFormat",
    /*    2 */ "GetEnhMetaFilePixelFormat",
    /*    3 */ "GetPixelFormat",
    /*    4 */ "SetPixelFormat",
    /*    5 */ "SwapBuffers",
    /*    6 */ "wglCopyContext",
    /*    7 */ "wglCreateContext",
    /*    8 */ "wglCreateLayerContext",
    /*    9 */ "wglDeleteContext",
    /*   10 */ "wglDescribeLayerPlane",
    /*   11 */ "wglGetCurrentContext",
    /*   12 */ "wglGetCurrentDC",
    /*   13 */ "wglGetExtensionsStringARB",
    /*   14 */ "wglGetExtensionsStringEXT",
    /*   15 */ "wglGetLayerPaletteEntries",
    /*   16 */ "wglGetProcAddress",
    /*   17 */ "wglMakeCurrent",
    /*   18 */ "wglRealizeLayerPalette",
    /*   19 */ "wglSetLayerPaletteEntries",
    /*   20 */ "wglShareLists",
    /*   21 */ "wglSwapLayerBuffers",
    /*   22 */ "wglUseFontBitmaps",
    /*   23 */ "wglUseFontBitmapsA",
    /*   24 */ "wglUseFontBitmapsW",
    /*   25 */ "wglUseFontOutlines",
    /*   26 */ "wglUseFontOutlinesA",
    /*   27 */ "wglUseFontOutlinesW"
};

static const char *GLAD_WGL_ext_names[] = {
    /*    0 */ "WGL_ARB_extensions_string",
    /*    1 */ "WGL_EXT_extensions_string"
};

#ifdef __cplusplus
GladWGLContext glad_wgl_context = {};
#else
GladWGLContext glad_wgl_context = { 0 };
#endif

static void glad_wgl_load_WGL_VERSION_1_0(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           0, /* ChoosePixelFormat */
           1, /* DescribePixelFormat */
           2, /* GetEnhMetaFilePixelFormat */
           3, /* GetPixelFormat */
           4, /* SetPixelFormat */
           5, /* SwapBuffers */
           6, /* wglCopyContext */
           7, /* wglCreateContext */
           8, /* wglCreateLayerContext */
           9, /* wglDeleteContext */
          10, /* wglDescribeLayerPlane */
          11, /* wglGetCurrentContext */
          12, /* wglGetCurrentDC */
          15, /* wglGetLayerPaletteEntries */
          16, /* wglGetProcAddress */
          17, /* wglMakeCurrent */
          18, /* wglRealizeLayerPalette */
          19, /* wglSetLayerPaletteEntries */
          20, /* wglShareLists */
          21, /* wglSwapLayerBuffers */
          22, /* wglUseFontBitmaps */
          23, /* wglUseFontBitmapsA */
          24, /* wglUseFontBitmapsW */
          25, /* wglUseFontOutlines */
          26, /* wglUseFontOutlinesA */
          27  /* wglUseFontOutlinesW */
    };
    uint32_t i;
    if(!context->VERSION_1_0) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_extensions_string(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          13  /* wglGetExtensionsStringARB */
    };
    uint32_t i;
    if(!context->ARB_extensions_string) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_extensions_string(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          14  /* wglGetExtensionsStringEXT */
    };
    uint32_t i;
    if(!context->EXT_extensions_string) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_resolve_aliases(GladWGLContext *context) {
    GLAD_UNUSED(context);
}

static int glad_wgl_has_extension(const char *extensions, const char *ext) {
    const char *terminator;
    const char *loc;

    if(extensions == NULL || ext == NULL)
        return 0;

    while(1) {
        loc = strstr(extensions, ext);
        if(loc == NULL)
            break;

        terminator = loc + strlen(ext);
        if((loc == extensions || *(loc - 1) == ' ') &&
            (*terminator == ' ' || *terminator == '\0'))
        {
            return 1;
        }
        extensions = terminator;
    }

    return 0;
}

static GLADapiproc glad_wgl_get_proc_from_userptr(void *userptr, const char* name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_wgl_find_extensions_wgl(GladWGLContext *context, HDC hdc) {
    const char *extensions;
    uint32_t i;

    if(context->GetExtensionsStringEXT == NULL && context->GetExtensionsStringARB == NULL)
        return 0;

    if(context->GetExtensionsStringARB == NULL || hdc == INVALID_HANDLE_VALUE)
        extensions = context->GetExtensionsStringEXT();
    else
        extensions = context->GetExtensionsStringARB(hdc);

    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_WGL_ext_names); ++i)
        context->extArray[i] = glad_wgl_has_extension(extensions, GLAD_WGL_ext_names[i]);

    return 1;
}

static int glad_wgl_find_core_wgl(GladWGLContext *context) {
    int major = 1, minor = 0;
    context->VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
    return GLAD_MAKE_VERSION(major, minor);
}

GLAD_NO_INLINE int gladLoadWGLContextUserPtr(GladWGLContext *context, HDC hdc, GLADuserptrloadfunc load, void *userptr) {
    int version;
    context->GetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC) load(userptr, "wglGetExtensionsStringARB");
    context->GetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC) load(userptr, "wglGetExtensionsStringEXT");
    if(context->GetExtensionsStringARB == NULL && context->GetExtensionsStringEXT == NULL) return 0;
    version = glad_wgl_find_core_wgl(context);

    glad_wgl_load_WGL_VERSION_1_0(context, load, userptr);

    if (!glad_wgl_find_extensions_wgl(context, hdc)) return 0;
    glad_wgl_load_WGL_ARB_extensions_string(context, load, userptr);
    glad_wgl_load_WGL_EXT_extensions_string(context, load, userptr);

    glad_wgl_resolve_aliases(context);

    return version;
}

int gladLoadWGLUserPtr(HDC hdc, GLADuserptrloadfunc load, void *userptr) {
    return gladLoadWGLContextUserPtr(gladGetWGLContext(), hdc, load, userptr);
}

int gladLoadWGLContext(GladWGLContext *context, HDC hdc, GLADloadfunc load) {
    return gladLoadWGLContextUserPtr(context, hdc, glad_wgl_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}

int gladLoadWGL(HDC hdc, GLADloadfunc load) {
    return gladLoadWGLContext(gladGetWGLContext(), hdc, load);
}

GladWGLContext* gladGetWGLContext() {
    return &glad_wgl_context;
}

void gladSetWGLContext(GladWGLContext *context) {
    if (!context) return;
    if (&glad_wgl_context == context) return;
    glad_wgl_context = *context;
}

#ifdef GLAD_WGL

#ifndef GLAD_LOADER_LIBRARY_C_
#define GLAD_LOADER_LIBRARY_C_

#include <stddef.h>
#include <stdlib.h>

#if GLAD_PLATFORM_WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif


static void* glad_get_dlopen_handle(const char *lib_names[], int length) {
    void *handle = NULL;
    int i;

    for (i = 0; i < length; ++i) {
#if GLAD_PLATFORM_WIN32
  #if GLAD_PLATFORM_UWP
        size_t buffer_size = (strlen(lib_names[i]) + 1) * sizeof(WCHAR);
        LPWSTR buffer = (LPWSTR) malloc(buffer_size);
        if (buffer != NULL) {
            int ret = MultiByteToWideChar(CP_ACP, 0, lib_names[i], -1, buffer, buffer_size);
            if (ret != 0) {
                handle = (void*) LoadPackagedLibrary(buffer, 0);
            }
            free((void*) buffer);
        }
  #else
        handle = (void*) LoadLibraryA(lib_names[i]);
  #endif
#else
        handle = dlopen(lib_names[i], RTLD_LAZY | RTLD_LOCAL);
#endif
        if (handle != NULL) {
            return handle;
        }
    }

    return NULL;
}

static void glad_close_dlopen_handle(void* handle) {
    if (handle != NULL) {
#if GLAD_PLATFORM_WIN32
        FreeLibrary((HMODULE) handle);
#else
        dlclose(handle);
#endif
    }
}

static GLADapiproc glad_dlsym_handle(void* handle, const char *name) {
    if (handle == NULL) {
        return NULL;
    }

#if GLAD_PLATFORM_WIN32
    return (GLADapiproc) GetProcAddress((HMODULE) handle, name);
#else
    return GLAD_GNUC_EXTENSION (GLADapiproc) dlsym(handle, name);
#endif
}

#endif /* GLAD_LOADER_LIBRARY_C_ */

typedef void* (GLAD_API_PTR *GLADwglprocaddrfunc)(const char*);
struct _glad_wgl_userptr {
    void *handle;
    GLADwglprocaddrfunc wgl_get_proc_address_ptr;
};


static void* glad_wgl_dlopen_handle(GladWGLContext *context) {
#if GLAD_PLATFORM_APPLE
    static const char *NAMES[] = {
        "../Frameworks/OpenGL.framework/OpenGL",
        "/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
    };
#elif GLAD_PLATFORM_WIN32
    static const char *NAMES[] = {"opengl32.dll"};
#else
    static const char *NAMES[] = {
  #if defined(__CYGWIN__)
        "libGL-1.so",
  #endif
        "libGL.so.1",
        "libGL.so"
    };
#endif

    if (context->glad_loader_handle == NULL) {
        context->glad_loader_handle = glad_get_dlopen_handle(NAMES, GLAD_ARRAYSIZE(NAMES));
    }

    return context->glad_loader_handle;
}

static struct _glad_wgl_userptr glad_wgl_build_userptr(void *handle) {
    struct _glad_wgl_userptr userptr;

    userptr.handle = handle;
#if GLAD_PLATFORM_APPLE || defined(__HAIKU__)
    userptr.wgl_get_proc_address_ptr = NULL;
#elif GLAD_PLATFORM_WIN32
    userptr.wgl_get_proc_address_ptr =
        (GLADwglprocaddrfunc) glad_dlsym_handle(handle, "wglGetProcAddress");
#else
    userptr.wgl_get_proc_address_ptr =
        (GLADwglprocaddrfunc) glad_dlsym_handle(handle, "glXGetProcAddressARB");
#endif

    return userptr;
}

static GLADapiproc glad_wgl_get_proc(void *vuserptr, const char *name) {
    struct _glad_wgl_userptr userptr = *(struct _glad_wgl_userptr*) vuserptr;
    GLADapiproc result = NULL;

    if(userptr.wgl_get_proc_address_ptr != NULL) {
        result = GLAD_GNUC_EXTENSION (GLADapiproc) userptr.wgl_get_proc_address_ptr(name);
    }
    if(result == NULL) {
        result = glad_dlsym_handle(userptr.handle, name);
    }

    return result;
}

int gladLoaderLoadWGLContext(GladWGLContext *context, HDC hdc) {
    int version = 0;
    void *handle;
    int did_load = 0;
    struct _glad_wgl_userptr userptr;

    did_load = context->glad_loader_handle == NULL;
    handle = glad_wgl_dlopen_handle(context);
    if (handle) {
        userptr = glad_wgl_build_userptr(handle);

        version = gladLoadWGLContextUserPtr(context, hdc, glad_wgl_get_proc, &userptr);

        if (!version && did_load) {
            gladLoaderUnloadWGLContext(context);
        }
    }
    return version;
}

int gladLoaderLoadWGL(HDC hdc) {
    return gladLoaderLoadWGLContext(gladGetWGLContext(), hdc);
}

void gladLoaderResetWGL(void) {
    gladLoaderResetWGLContext(gladGetWGLContext());
}

void gladLoaderUnloadWGLContext(GladWGLContext *context) {
    if (context->glad_loader_handle != NULL) {
        glad_close_dlopen_handle(context->glad_loader_handle);
        context->glad_loader_handle = NULL;
    }

    gladLoaderResetWGLContext(context);
}

void gladLoaderResetWGLContext(GladWGLContext *context) {
    memset(context, 0, sizeof(GladWGLContext));
}

void gladLoaderUnloadWGL(void) {
    gladLoaderUnloadWGLContext(gladGetWGLContext());
}

#endif /* GLAD_WGL */

#ifdef __cplusplus
}
#endif
#endif
