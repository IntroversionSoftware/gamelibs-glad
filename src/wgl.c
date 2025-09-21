/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#if defined(__x86_64__) || defined(__i386__) || defined(_M_IX86) || defined(_M_X64)
#define XXH_VECTOR XXH_SSE2
#include <immintrin.h>
#elif defined(__aarch64__) || defined(__arm__) || defined(_M_ARM) || defined(_M_ARM64)
#define XXH_VECTOR XXH_NEON
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

typedef struct {
    uint16_t extension;
    uint16_t start;
    uint16_t count;
} GladPfnRange_t;

#endif /* GLAD_IMPL_UTIL_C_ */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
GladWGLContext glad_wgl_context = {};
#else
GladWGLContext glad_wgl_context = { 0 };
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
    /*   13 */ "wglGetLayerPaletteEntries",
    /*   14 */ "wglGetProcAddress",
    /*   15 */ "wglMakeCurrent",
    /*   16 */ "wglRealizeLayerPalette",
    /*   17 */ "wglSetLayerPaletteEntries",
    /*   18 */ "wglShareLists",
    /*   19 */ "wglSwapLayerBuffers",
    /*   20 */ "wglUseFontBitmaps",
    /*   21 */ "wglUseFontBitmapsA",
    /*   22 */ "wglUseFontBitmapsW",
    /*   23 */ "wglUseFontOutlines",
    /*   24 */ "wglUseFontOutlinesA",
    /*   25 */ "wglUseFontOutlinesW",
    /*   26 */ "wglSetStereoEmitterState3DL",
    /*   27 */ "wglGetGPUIDsAMD",
    /*   28 */ "wglGetGPUInfoAMD",
    /*   29 */ "wglGetContextGPUIDAMD",
    /*   30 */ "wglCreateAssociatedContextAMD",
    /*   31 */ "wglCreateAssociatedContextAttribsAMD",
    /*   32 */ "wglDeleteAssociatedContextAMD",
    /*   33 */ "wglMakeAssociatedContextCurrentAMD",
    /*   34 */ "wglGetCurrentAssociatedContextAMD",
    /*   35 */ "wglBlitContextFramebufferAMD",
    /*   36 */ "wglCreateBufferRegionARB",
    /*   37 */ "wglDeleteBufferRegionARB",
    /*   38 */ "wglSaveBufferRegionARB",
    /*   39 */ "wglRestoreBufferRegionARB",
    /*   40 */ "wglCreateContextAttribsARB",
    /*   41 */ "wglGetExtensionsStringARB",
    /*   42 */ "wglMakeContextCurrentARB",
    /*   43 */ "wglGetCurrentReadDCARB",
    /*   44 */ "wglCreatePbufferARB",
    /*   45 */ "wglGetPbufferDCARB",
    /*   46 */ "wglReleasePbufferDCARB",
    /*   47 */ "wglDestroyPbufferARB",
    /*   48 */ "wglQueryPbufferARB",
    /*   49 */ "wglGetPixelFormatAttribivARB",
    /*   50 */ "wglGetPixelFormatAttribfvARB",
    /*   51 */ "wglChoosePixelFormatARB",
    /*   52 */ "wglBindTexImageARB",
    /*   53 */ "wglReleaseTexImageARB",
    /*   54 */ "wglSetPbufferAttribARB",
    /*   55 */ "wglCreateDisplayColorTableEXT",
    /*   56 */ "wglLoadDisplayColorTableEXT",
    /*   57 */ "wglBindDisplayColorTableEXT",
    /*   58 */ "wglDestroyDisplayColorTableEXT",
    /*   59 */ "wglGetExtensionsStringEXT",
    /*   60 */ "wglMakeContextCurrentEXT",
    /*   61 */ "wglGetCurrentReadDCEXT",
    /*   62 */ "wglCreatePbufferEXT",
    /*   63 */ "wglGetPbufferDCEXT",
    /*   64 */ "wglReleasePbufferDCEXT",
    /*   65 */ "wglDestroyPbufferEXT",
    /*   66 */ "wglQueryPbufferEXT",
    /*   67 */ "wglGetPixelFormatAttribivEXT",
    /*   68 */ "wglGetPixelFormatAttribfvEXT",
    /*   69 */ "wglChoosePixelFormatEXT",
    /*   70 */ "wglSwapIntervalEXT",
    /*   71 */ "wglGetSwapIntervalEXT",
    /*   72 */ "wglGetDigitalVideoParametersI3D",
    /*   73 */ "wglSetDigitalVideoParametersI3D",
    /*   74 */ "wglGetGammaTableParametersI3D",
    /*   75 */ "wglSetGammaTableParametersI3D",
    /*   76 */ "wglGetGammaTableI3D",
    /*   77 */ "wglSetGammaTableI3D",
    /*   78 */ "wglEnableGenlockI3D",
    /*   79 */ "wglDisableGenlockI3D",
    /*   80 */ "wglIsEnabledGenlockI3D",
    /*   81 */ "wglGenlockSourceI3D",
    /*   82 */ "wglGetGenlockSourceI3D",
    /*   83 */ "wglGenlockSourceEdgeI3D",
    /*   84 */ "wglGetGenlockSourceEdgeI3D",
    /*   85 */ "wglGenlockSampleRateI3D",
    /*   86 */ "wglGetGenlockSampleRateI3D",
    /*   87 */ "wglGenlockSourceDelayI3D",
    /*   88 */ "wglGetGenlockSourceDelayI3D",
    /*   89 */ "wglQueryGenlockMaxSourceDelayI3D",
    /*   90 */ "wglCreateImageBufferI3D",
    /*   91 */ "wglDestroyImageBufferI3D",
    /*   92 */ "wglAssociateImageBufferEventsI3D",
    /*   93 */ "wglReleaseImageBufferEventsI3D",
    /*   94 */ "wglEnableFrameLockI3D",
    /*   95 */ "wglDisableFrameLockI3D",
    /*   96 */ "wglIsEnabledFrameLockI3D",
    /*   97 */ "wglQueryFrameLockMasterI3D",
    /*   98 */ "wglGetFrameUsageI3D",
    /*   99 */ "wglBeginFrameTrackingI3D",
    /*  100 */ "wglEndFrameTrackingI3D",
    /*  101 */ "wglQueryFrameTrackingI3D",
    /*  102 */ "wglCopyImageSubDataNV",
    /*  103 */ "wglDelayBeforeSwapNV",
    /*  104 */ "wglDXSetResourceShareHandleNV",
    /*  105 */ "wglDXOpenDeviceNV",
    /*  106 */ "wglDXCloseDeviceNV",
    /*  107 */ "wglDXRegisterObjectNV",
    /*  108 */ "wglDXUnregisterObjectNV",
    /*  109 */ "wglDXObjectAccessNV",
    /*  110 */ "wglDXLockObjectsNV",
    /*  111 */ "wglDXUnlockObjectsNV",
    /*  112 */ "wglEnumGpusNV",
    /*  113 */ "wglEnumGpuDevicesNV",
    /*  114 */ "wglCreateAffinityDCNV",
    /*  115 */ "wglEnumGpusFromAffinityDCNV",
    /*  116 */ "wglDeleteDCNV",
    /*  117 */ "wglEnumerateVideoDevicesNV",
    /*  118 */ "wglBindVideoDeviceNV",
    /*  119 */ "wglQueryCurrentContextNV",
    /*  120 */ "wglJoinSwapGroupNV",
    /*  121 */ "wglBindSwapBarrierNV",
    /*  122 */ "wglQuerySwapGroupNV",
    /*  123 */ "wglQueryMaxSwapGroupsNV",
    /*  124 */ "wglQueryFrameCountNV",
    /*  125 */ "wglResetFrameCountNV",
    /*  126 */ "wglBindVideoCaptureDeviceNV",
    /*  127 */ "wglEnumerateVideoCaptureDevicesNV",
    /*  128 */ "wglLockVideoCaptureDeviceNV",
    /*  129 */ "wglQueryVideoCaptureDeviceNV",
    /*  130 */ "wglReleaseVideoCaptureDeviceNV",
    /*  131 */ "wglGetVideoDeviceNV",
    /*  132 */ "wglReleaseVideoDeviceNV",
    /*  133 */ "wglBindVideoImageNV",
    /*  134 */ "wglReleaseVideoImageNV",
    /*  135 */ "wglSendPbufferToVideoNV",
    /*  136 */ "wglGetVideoInfoNV",
    /*  137 */ "wglAllocateMemoryNV",
    /*  138 */ "wglFreeMemoryNV",
    /*  139 */ "wglGetSyncValuesOML",
    /*  140 */ "wglGetMscRateOML",
    /*  141 */ "wglSwapBuffersMscOML",
    /*  142 */ "wglSwapLayerBuffersMscOML",
    /*  143 */ "wglWaitForMscOML",
    /*  144 */ "wglWaitForSbcOML"
};

static const char *GLAD_WGL_ext_names[] = {
    /*    0 */ "WGL_3DFX_multisample",
    /*    1 */ "WGL_3DL_stereo_control",
    /*    2 */ "WGL_AMD_gpu_association",
    /*    3 */ "WGL_ARB_buffer_region",
    /*    4 */ "WGL_ARB_context_flush_control",
    /*    5 */ "WGL_ARB_create_context",
    /*    6 */ "WGL_ARB_create_context_no_error",
    /*    7 */ "WGL_ARB_create_context_profile",
    /*    8 */ "WGL_ARB_create_context_robustness",
    /*    9 */ "WGL_ARB_extensions_string",
    /*   10 */ "WGL_ARB_framebuffer_sRGB",
    /*   11 */ "WGL_ARB_make_current_read",
    /*   12 */ "WGL_ARB_multisample",
    /*   13 */ "WGL_ARB_pbuffer",
    /*   14 */ "WGL_ARB_pixel_format",
    /*   15 */ "WGL_ARB_pixel_format_float",
    /*   16 */ "WGL_ARB_render_texture",
    /*   17 */ "WGL_ARB_robustness_application_isolation",
    /*   18 */ "WGL_ARB_robustness_share_group_isolation",
    /*   19 */ "WGL_ATI_pixel_format_float",
    /*   20 */ "WGL_ATI_render_texture_rectangle",
    /*   21 */ "WGL_EXT_colorspace",
    /*   22 */ "WGL_EXT_create_context_es2_profile",
    /*   23 */ "WGL_EXT_create_context_es_profile",
    /*   24 */ "WGL_EXT_depth_float",
    /*   25 */ "WGL_EXT_display_color_table",
    /*   26 */ "WGL_EXT_extensions_string",
    /*   27 */ "WGL_EXT_framebuffer_sRGB",
    /*   28 */ "WGL_EXT_make_current_read",
    /*   29 */ "WGL_EXT_multisample",
    /*   30 */ "WGL_EXT_pbuffer",
    /*   31 */ "WGL_EXT_pixel_format",
    /*   32 */ "WGL_EXT_pixel_format_packed_float",
    /*   33 */ "WGL_EXT_swap_control",
    /*   34 */ "WGL_EXT_swap_control_tear",
    /*   35 */ "WGL_I3D_digital_video_control",
    /*   36 */ "WGL_I3D_gamma",
    /*   37 */ "WGL_I3D_genlock",
    /*   38 */ "WGL_I3D_image_buffer",
    /*   39 */ "WGL_I3D_swap_frame_lock",
    /*   40 */ "WGL_I3D_swap_frame_usage",
    /*   41 */ "WGL_NV_DX_interop",
    /*   42 */ "WGL_NV_DX_interop2",
    /*   43 */ "WGL_NV_copy_image",
    /*   44 */ "WGL_NV_delay_before_swap",
    /*   45 */ "WGL_NV_float_buffer",
    /*   46 */ "WGL_NV_gpu_affinity",
    /*   47 */ "WGL_NV_multigpu_context",
    /*   48 */ "WGL_NV_multisample_coverage",
    /*   49 */ "WGL_NV_present_video",
    /*   50 */ "WGL_NV_render_depth_texture",
    /*   51 */ "WGL_NV_render_texture_rectangle",
    /*   52 */ "WGL_NV_swap_group",
    /*   53 */ "WGL_NV_vertex_array_range",
    /*   54 */ "WGL_NV_video_capture",
    /*   55 */ "WGL_NV_video_output",
    /*   56 */ "WGL_OML_sync_control"
};

static const GladPfnRange_t GLAD_WGL_feature_pfn_ranges[] = {
    /* WGL_VERSION_1_0 */
    {    0,    0,   26 },
};

static const GladPfnRange_t GLAD_WGL_ext_pfn_ranges[] = {
    /* WGL_3DL_stereo_control */
    {    1,   26,    1 },

    /* WGL_AMD_gpu_association */
    {    2,   27,    9 },

    /* WGL_ARB_buffer_region */
    {    3,   36,    4 },

    /* WGL_ARB_create_context */
    {    5,   40,    1 },

    /* WGL_ARB_extensions_string */
    {    9,   41,    1 },

    /* WGL_ARB_make_current_read */
    {   11,   42,    2 },

    /* WGL_ARB_pbuffer */
    {   13,   44,    5 },

    /* WGL_ARB_pixel_format */
    {   14,   49,    3 },

    /* WGL_ARB_render_texture */
    {   16,   52,    3 },

    /* WGL_EXT_display_color_table */
    {   25,   55,    4 },

    /* WGL_EXT_extensions_string */
    {   26,   59,    1 },

    /* WGL_EXT_make_current_read */
    {   28,   60,    2 },

    /* WGL_EXT_pbuffer */
    {   30,   62,    5 },

    /* WGL_EXT_pixel_format */
    {   31,   67,    3 },

    /* WGL_EXT_swap_control */
    {   33,   70,    2 },

    /* WGL_I3D_digital_video_control */
    {   35,   72,    2 },

    /* WGL_I3D_gamma */
    {   36,   74,    4 },

    /* WGL_I3D_genlock */
    {   37,   78,   12 },

    /* WGL_I3D_image_buffer */
    {   38,   90,    4 },

    /* WGL_I3D_swap_frame_lock */
    {   39,   94,    4 },

    /* WGL_I3D_swap_frame_usage */
    {   40,   98,    4 },

    /* WGL_NV_DX_interop */
    {   41,  104,    8 },

    /* WGL_NV_copy_image */
    {   43,  102,    1 },

    /* WGL_NV_delay_before_swap */
    {   44,  103,    1 },

    /* WGL_NV_gpu_affinity */
    {   46,  112,    5 },

    /* WGL_NV_present_video */
    {   49,  117,    3 },

    /* WGL_NV_swap_group */
    {   52,  120,    6 },

    /* WGL_NV_vertex_array_range */
    {   53,  137,    2 },

    /* WGL_NV_video_capture */
    {   54,  126,    5 },

    /* WGL_NV_video_output */
    {   55,  131,    6 },

    /* WGL_OML_sync_control */
    {   56,  139,    6 },
};


static void glad_wgl_load_pfn_range(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr, uint16_t pfnStart, uint32_t numPfns)
{
    uint32_t pfnIdx;

    #ifdef __clang__
    #pragma nounroll
    #endif
    for (pfnIdx = pfnStart; pfnIdx < pfnStart + numPfns; ++pfnIdx) {
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

GLAD_NO_INLINE static void glad_wgl_resolve_aliases(GladWGLContext *context) {
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
    uint32_t i;

    context->GetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC) load(userptr, "wglGetExtensionsStringARB");
    context->GetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC) load(userptr, "wglGetExtensionsStringEXT");
    if(context->GetExtensionsStringARB == NULL && context->GetExtensionsStringEXT == NULL) return 0;
    version = glad_wgl_find_core_wgl(context);

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_WGL_feature_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_WGL_feature_pfn_ranges[i];
        if (context->featArray[range->extension]) {
            glad_wgl_load_pfn_range(context, load, userptr, range->start, range->count);
        }
    }

    if (!glad_wgl_find_extensions_wgl(context, hdc)) return 0;

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_WGL_ext_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_WGL_ext_pfn_ranges[i];
        if (context->extArray[range->extension]) {
            glad_wgl_load_pfn_range(context, load, userptr, range->start, range->count);
        }
    }

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
