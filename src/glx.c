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

#include <glad/glx.h>

#ifdef __linux__
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

static const char *GLAD_GLX_fn_names[] = {
    /*    0 */ "glXChooseFBConfig",
    /*    1 */ "glXChooseVisual",
    /*    2 */ "glXCopyContext",
    /*    3 */ "glXCreateContext",
    /*    4 */ "glXCreateGLXPixmap",
    /*    5 */ "glXCreateNewContext",
    /*    6 */ "glXCreatePbuffer",
    /*    7 */ "glXCreatePixmap",
    /*    8 */ "glXCreateWindow",
    /*    9 */ "glXDestroyContext",
    /*   10 */ "glXDestroyGLXPixmap",
    /*   11 */ "glXDestroyPbuffer",
    /*   12 */ "glXDestroyPixmap",
    /*   13 */ "glXDestroyWindow",
    /*   14 */ "glXGetClientString",
    /*   15 */ "glXGetConfig",
    /*   16 */ "glXGetCurrentContext",
    /*   17 */ "glXGetCurrentDisplay",
    /*   18 */ "glXGetCurrentDrawable",
    /*   19 */ "glXGetCurrentReadDrawable",
    /*   20 */ "glXGetFBConfigAttrib",
    /*   21 */ "glXGetFBConfigs",
    /*   22 */ "glXGetProcAddress",
    /*   23 */ "glXGetSelectedEvent",
    /*   24 */ "glXGetVisualFromFBConfig",
    /*   25 */ "glXIsDirect",
    /*   26 */ "glXMakeContextCurrent",
    /*   27 */ "glXMakeCurrent",
    /*   28 */ "glXQueryContext",
    /*   29 */ "glXQueryDrawable",
    /*   30 */ "glXQueryExtension",
    /*   31 */ "glXQueryExtensionsString",
    /*   32 */ "glXQueryServerString",
    /*   33 */ "glXQueryVersion",
    /*   34 */ "glXSelectEvent",
    /*   35 */ "glXSwapBuffers",
    /*   36 */ "glXUseXFont",
    /*   37 */ "glXWaitGL",
    /*   38 */ "glXWaitX"
};

static const char *GLAD_GLX_ext_names[] = {
};

#ifdef __cplusplus
GladGLXContext glad_glx_context = {};
#else
GladGLXContext glad_glx_context = { 0 };
#endif

static void glad_glx_load_GLX_VERSION_1_0(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           1, /* glXChooseVisual */
           2, /* glXCopyContext */
           3, /* glXCreateContext */
           4, /* glXCreateGLXPixmap */
           9, /* glXDestroyContext */
          10, /* glXDestroyGLXPixmap */
          15, /* glXGetConfig */
          16, /* glXGetCurrentContext */
          18, /* glXGetCurrentDrawable */
          25, /* glXIsDirect */
          27, /* glXMakeCurrent */
          30, /* glXQueryExtension */
          33, /* glXQueryVersion */
          35, /* glXSwapBuffers */
          36, /* glXUseXFont */
          37, /* glXWaitGL */
          38  /* glXWaitX */
    };
    uint32_t i;
    if(!context->VERSION_1_0) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_VERSION_1_1(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          14, /* glXGetClientString */
          31, /* glXQueryExtensionsString */
          32  /* glXQueryServerString */
    };
    uint32_t i;
    if(!context->VERSION_1_1) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_VERSION_1_2(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          17  /* glXGetCurrentDisplay */
    };
    uint32_t i;
    if(!context->VERSION_1_2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_VERSION_1_3(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           0, /* glXChooseFBConfig */
           5, /* glXCreateNewContext */
           6, /* glXCreatePbuffer */
           7, /* glXCreatePixmap */
           8, /* glXCreateWindow */
          11, /* glXDestroyPbuffer */
          12, /* glXDestroyPixmap */
          13, /* glXDestroyWindow */
          19, /* glXGetCurrentReadDrawable */
          20, /* glXGetFBConfigAttrib */
          21, /* glXGetFBConfigs */
          23, /* glXGetSelectedEvent */
          24, /* glXGetVisualFromFBConfig */
          26, /* glXMakeContextCurrent */
          28, /* glXQueryContext */
          29, /* glXQueryDrawable */
          34  /* glXSelectEvent */
    };
    uint32_t i;
    if(!context->VERSION_1_3) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_VERSION_1_4(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          22  /* glXGetProcAddress */
    };
    uint32_t i;
    if(!context->VERSION_1_4) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_resolve_aliases(GladGLXContext *context) {
    GLAD_UNUSED(context);
}

#ifdef GLX_VERSION_1_1
static int glad_glx_has_extension(const char *extensions, const char *ext) {
    const char *terminator;
    const char *loc;

    if (extensions == NULL || ext == NULL)
        return -1;

    while(1) {
        loc = strstr(extensions, ext);
        if(loc == NULL)
            break;

        terminator = loc + strlen(ext);
        if((loc == extensions || *(loc - 1) == ' ') &&
            (*terminator == ' ' || *terminator == '\0')) {
            return 1;
        }
        extensions = terminator;
    }

    return 0;
}
#endif

static GLADapiproc glad_glx_get_proc_from_userptr(void *userptr, const char* name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_glx_find_extensions(GladGLXContext *context, Display *display, int screen) {
    GLAD_UNUSED(context);
    GLAD_UNUSED(display);
    GLAD_UNUSED(screen);
    GLAD_UNUSED(GLAD_GLX_ext_names);

    return 1;
}

static int glad_glx_find_core_glx(GladGLXContext *context, Display **display, int *screen) {
    int major = 0, minor = 0;
    if(*display == NULL) {
#ifdef GLAD_GLX_NO_X11
        GLAD_UNUSED(screen);
        return 0;
#else
        *display = XOpenDisplay(0);
        if (*display == NULL) {
            return 0;
        }
        *screen = XScreenNumberOfScreen(XDefaultScreenOfDisplay(*display));
#endif
    }
    context->QueryVersion(*display, &major, &minor);
    context->VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
    context->VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
    context->VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
    context->VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;
    context->VERSION_1_4 = (major == 1 && minor >= 4) || major > 1;
    return GLAD_MAKE_VERSION(major, minor);
}

GLAD_NO_INLINE int gladLoadGLXContextUserPtr(GladGLXContext *context, Display *display, int screen, GLADuserptrloadfunc load, void *userptr) {
    int version;
    context->QueryVersion = (PFNGLXQUERYVERSIONPROC) load(userptr, "glXQueryVersion");
    if(context->QueryVersion == NULL) return 0;
    version = glad_glx_find_core_glx(context, &display, &screen);

    glad_glx_load_GLX_VERSION_1_0(context, load, userptr);
    glad_glx_load_GLX_VERSION_1_1(context, load, userptr);
    glad_glx_load_GLX_VERSION_1_2(context, load, userptr);
    glad_glx_load_GLX_VERSION_1_3(context, load, userptr);
    glad_glx_load_GLX_VERSION_1_4(context, load, userptr);

    if (!glad_glx_find_extensions(context, display, screen)) return 0;

    glad_glx_resolve_aliases(context);

    return version;
}

int gladLoadGLXUserPtr(Display *display, int screen, GLADuserptrloadfunc load, void *userptr) {
    return gladLoadGLXContextUserPtr(gladGetGLXContext(), display, screen, load, userptr);
}

int gladLoadGLXContext(GladGLXContext *context, Display *display, int screen, GLADloadfunc load) {
    return gladLoadGLXContextUserPtr(context, display, screen, glad_glx_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}

int gladLoadGLX(Display *display, int screen, GLADloadfunc load) {
    return gladLoadGLXContext(gladGetGLXContext(), display, screen, GLAD_GNUC_EXTENSION (void*) load);
}

GladGLXContext* gladGetGLXContext() {
    return &glad_glx_context;
}

void gladSetGLXContext(GladGLXContext *context) {
    if (!context) return;
    if (&glad_glx_context == context) return;
    glad_glx_context = *context;
}


#ifdef GLAD_GLX

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

typedef void* (GLAD_API_PTR *GLADglxprocaddrfunc)(const char*);

static GLADapiproc glad_glx_get_proc(void *userptr, const char *name) {
    return GLAD_GNUC_EXTENSION ((GLADapiproc (*)(const char *name)) userptr)(name);
}

static void* _glx_handle;

static void* glad_glx_dlopen_handle(void) {
    static const char *NAMES[] = {
#if defined __CYGWIN__
        "libGL-1.so",
#endif
        "libGL.so.1",
        "libGL.so"
    };

    if (_glx_handle == NULL) {
        _glx_handle = glad_get_dlopen_handle(NAMES, GLAD_ARRAYSIZE(NAMES));
    }

    return _glx_handle;
}

int gladLoaderLoadGLX(Display *display, int screen) {
    int version = 0;
    void *handle = NULL;
    int did_load = 0;
    GLADglxprocaddrfunc loader;

    did_load = _glx_handle == NULL;
    handle = glad_glx_dlopen_handle();
    if (handle != NULL) {
        loader = (GLADglxprocaddrfunc) glad_dlsym_handle(handle, "glXGetProcAddressARB");
        if (loader != NULL) {
            version = gladLoadGLXUserPtr(display, screen, glad_glx_get_proc, GLAD_GNUC_EXTENSION (void*) loader);
        }

        if (!version && did_load) {
            gladLoaderUnloadGLX();
        }
    }

    return version;
}

void gladLoaderUnloadGLX() {
    if (_glx_handle != NULL) {
        glad_close_dlopen_handle(_glx_handle);
        _glx_handle = NULL;
    }
}

void gladLoaderResetGLX(void) {
    gladLoaderResetGLXContext(gladGetGLXContext());
}

void gladLoaderResetGLXContext(GladGLXContext *context) {
    memset(context, 0, sizeof(GladGLXContext));
}

#endif /* GLAD_GLX */

#ifdef __cplusplus
}
#endif
#endif
