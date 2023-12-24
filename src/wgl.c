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

#endif /* GLAD_IMPL_UTIL_C_ */

#ifdef __cplusplus
extern "C" {
#endif

#define GLAD_ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

typedef struct {
    uint16_t first;
    uint16_t second;
} GladAliasPair_t;

static const char *GLAD_WGL_fn_names[] = {
    /*    0 */ "ChoosePixelFormat",
    /*    1 */ "DescribePixelFormat",
    /*    2 */ "GetEnhMetaFilePixelFormat",
    /*    3 */ "GetPixelFormat",
    /*    4 */ "SetPixelFormat",
    /*    5 */ "SwapBuffers",
    /*    6 */ "wglAllocateMemoryNV",
    /*    7 */ "wglAssociateImageBufferEventsI3D",
    /*    8 */ "wglBeginFrameTrackingI3D",
    /*    9 */ "wglBindDisplayColorTableEXT",
    /*   10 */ "wglBindSwapBarrierNV",
    /*   11 */ "wglBindTexImageARB",
    /*   12 */ "wglBindVideoCaptureDeviceNV",
    /*   13 */ "wglBindVideoDeviceNV",
    /*   14 */ "wglBindVideoImageNV",
    /*   15 */ "wglBlitContextFramebufferAMD",
    /*   16 */ "wglChoosePixelFormatARB",
    /*   17 */ "wglChoosePixelFormatEXT",
    /*   18 */ "wglCopyContext",
    /*   19 */ "wglCopyImageSubDataNV",
    /*   20 */ "wglCreateAffinityDCNV",
    /*   21 */ "wglCreateAssociatedContextAMD",
    /*   22 */ "wglCreateAssociatedContextAttribsAMD",
    /*   23 */ "wglCreateBufferRegionARB",
    /*   24 */ "wglCreateContext",
    /*   25 */ "wglCreateContextAttribsARB",
    /*   26 */ "wglCreateDisplayColorTableEXT",
    /*   27 */ "wglCreateImageBufferI3D",
    /*   28 */ "wglCreateLayerContext",
    /*   29 */ "wglCreatePbufferARB",
    /*   30 */ "wglCreatePbufferEXT",
    /*   31 */ "wglDXCloseDeviceNV",
    /*   32 */ "wglDXLockObjectsNV",
    /*   33 */ "wglDXObjectAccessNV",
    /*   34 */ "wglDXOpenDeviceNV",
    /*   35 */ "wglDXRegisterObjectNV",
    /*   36 */ "wglDXSetResourceShareHandleNV",
    /*   37 */ "wglDXUnlockObjectsNV",
    /*   38 */ "wglDXUnregisterObjectNV",
    /*   39 */ "wglDelayBeforeSwapNV",
    /*   40 */ "wglDeleteAssociatedContextAMD",
    /*   41 */ "wglDeleteBufferRegionARB",
    /*   42 */ "wglDeleteContext",
    /*   43 */ "wglDeleteDCNV",
    /*   44 */ "wglDescribeLayerPlane",
    /*   45 */ "wglDestroyDisplayColorTableEXT",
    /*   46 */ "wglDestroyImageBufferI3D",
    /*   47 */ "wglDestroyPbufferARB",
    /*   48 */ "wglDestroyPbufferEXT",
    /*   49 */ "wglDisableFrameLockI3D",
    /*   50 */ "wglDisableGenlockI3D",
    /*   51 */ "wglEnableFrameLockI3D",
    /*   52 */ "wglEnableGenlockI3D",
    /*   53 */ "wglEndFrameTrackingI3D",
    /*   54 */ "wglEnumGpuDevicesNV",
    /*   55 */ "wglEnumGpusFromAffinityDCNV",
    /*   56 */ "wglEnumGpusNV",
    /*   57 */ "wglEnumerateVideoCaptureDevicesNV",
    /*   58 */ "wglEnumerateVideoDevicesNV",
    /*   59 */ "wglFreeMemoryNV",
    /*   60 */ "wglGenlockSampleRateI3D",
    /*   61 */ "wglGenlockSourceDelayI3D",
    /*   62 */ "wglGenlockSourceEdgeI3D",
    /*   63 */ "wglGenlockSourceI3D",
    /*   64 */ "wglGetContextGPUIDAMD",
    /*   65 */ "wglGetCurrentAssociatedContextAMD",
    /*   66 */ "wglGetCurrentContext",
    /*   67 */ "wglGetCurrentDC",
    /*   68 */ "wglGetCurrentReadDCARB",
    /*   69 */ "wglGetCurrentReadDCEXT",
    /*   70 */ "wglGetDigitalVideoParametersI3D",
    /*   71 */ "wglGetExtensionsStringARB",
    /*   72 */ "wglGetExtensionsStringEXT",
    /*   73 */ "wglGetFrameUsageI3D",
    /*   74 */ "wglGetGPUIDsAMD",
    /*   75 */ "wglGetGPUInfoAMD",
    /*   76 */ "wglGetGammaTableI3D",
    /*   77 */ "wglGetGammaTableParametersI3D",
    /*   78 */ "wglGetGenlockSampleRateI3D",
    /*   79 */ "wglGetGenlockSourceDelayI3D",
    /*   80 */ "wglGetGenlockSourceEdgeI3D",
    /*   81 */ "wglGetGenlockSourceI3D",
    /*   82 */ "wglGetLayerPaletteEntries",
    /*   83 */ "wglGetMscRateOML",
    /*   84 */ "wglGetPbufferDCARB",
    /*   85 */ "wglGetPbufferDCEXT",
    /*   86 */ "wglGetPixelFormatAttribfvARB",
    /*   87 */ "wglGetPixelFormatAttribfvEXT",
    /*   88 */ "wglGetPixelFormatAttribivARB",
    /*   89 */ "wglGetPixelFormatAttribivEXT",
    /*   90 */ "wglGetProcAddress",
    /*   91 */ "wglGetSwapIntervalEXT",
    /*   92 */ "wglGetSyncValuesOML",
    /*   93 */ "wglGetVideoDeviceNV",
    /*   94 */ "wglGetVideoInfoNV",
    /*   95 */ "wglIsEnabledFrameLockI3D",
    /*   96 */ "wglIsEnabledGenlockI3D",
    /*   97 */ "wglJoinSwapGroupNV",
    /*   98 */ "wglLoadDisplayColorTableEXT",
    /*   99 */ "wglLockVideoCaptureDeviceNV",
    /*  100 */ "wglMakeAssociatedContextCurrentAMD",
    /*  101 */ "wglMakeContextCurrentARB",
    /*  102 */ "wglMakeContextCurrentEXT",
    /*  103 */ "wglMakeCurrent",
    /*  104 */ "wglQueryCurrentContextNV",
    /*  105 */ "wglQueryFrameCountNV",
    /*  106 */ "wglQueryFrameLockMasterI3D",
    /*  107 */ "wglQueryFrameTrackingI3D",
    /*  108 */ "wglQueryGenlockMaxSourceDelayI3D",
    /*  109 */ "wglQueryMaxSwapGroupsNV",
    /*  110 */ "wglQueryPbufferARB",
    /*  111 */ "wglQueryPbufferEXT",
    /*  112 */ "wglQuerySwapGroupNV",
    /*  113 */ "wglQueryVideoCaptureDeviceNV",
    /*  114 */ "wglRealizeLayerPalette",
    /*  115 */ "wglReleaseImageBufferEventsI3D",
    /*  116 */ "wglReleasePbufferDCARB",
    /*  117 */ "wglReleasePbufferDCEXT",
    /*  118 */ "wglReleaseTexImageARB",
    /*  119 */ "wglReleaseVideoCaptureDeviceNV",
    /*  120 */ "wglReleaseVideoDeviceNV",
    /*  121 */ "wglReleaseVideoImageNV",
    /*  122 */ "wglResetFrameCountNV",
    /*  123 */ "wglRestoreBufferRegionARB",
    /*  124 */ "wglSaveBufferRegionARB",
    /*  125 */ "wglSendPbufferToVideoNV",
    /*  126 */ "wglSetDigitalVideoParametersI3D",
    /*  127 */ "wglSetGammaTableI3D",
    /*  128 */ "wglSetGammaTableParametersI3D",
    /*  129 */ "wglSetLayerPaletteEntries",
    /*  130 */ "wglSetPbufferAttribARB",
    /*  131 */ "wglSetStereoEmitterState3DL",
    /*  132 */ "wglShareLists",
    /*  133 */ "wglSwapBuffersMscOML",
    /*  134 */ "wglSwapIntervalEXT",
    /*  135 */ "wglSwapLayerBuffers",
    /*  136 */ "wglSwapLayerBuffersMscOML",
    /*  137 */ "wglUseFontBitmaps",
    /*  138 */ "wglUseFontBitmapsA",
    /*  139 */ "wglUseFontBitmapsW",
    /*  140 */ "wglUseFontOutlines",
    /*  141 */ "wglUseFontOutlinesA",
    /*  142 */ "wglUseFontOutlinesW",
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
          18, /* wglCopyContext */
          24, /* wglCreateContext */
          28, /* wglCreateLayerContext */
          42, /* wglDeleteContext */
          44, /* wglDescribeLayerPlane */
          66, /* wglGetCurrentContext */
          67, /* wglGetCurrentDC */
          82, /* wglGetLayerPaletteEntries */
          90, /* wglGetProcAddress */
         103, /* wglMakeCurrent */
         114, /* wglRealizeLayerPalette */
         129, /* wglSetLayerPaletteEntries */
         132, /* wglShareLists */
         135, /* wglSwapLayerBuffers */
         137, /* wglUseFontBitmaps */
         138, /* wglUseFontBitmapsA */
         139, /* wglUseFontBitmapsW */
         140, /* wglUseFontOutlines */
         141, /* wglUseFontOutlinesA */
         142  /* wglUseFontOutlinesW */
    };
    uint32_t i;
    if(!context->VERSION_1_0) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_3DL_stereo_control(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         131  /* wglSetStereoEmitterState3DL */
    };
    uint32_t i;
    if(!context->_3DL_stereo_control) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_AMD_gpu_association(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          15, /* wglBlitContextFramebufferAMD */
          21, /* wglCreateAssociatedContextAMD */
          22, /* wglCreateAssociatedContextAttribsAMD */
          40, /* wglDeleteAssociatedContextAMD */
          64, /* wglGetContextGPUIDAMD */
          65, /* wglGetCurrentAssociatedContextAMD */
          74, /* wglGetGPUIDsAMD */
          75, /* wglGetGPUInfoAMD */
         100  /* wglMakeAssociatedContextCurrentAMD */
    };
    uint32_t i;
    if(!context->AMD_gpu_association) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_buffer_region(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          23, /* wglCreateBufferRegionARB */
          41, /* wglDeleteBufferRegionARB */
         123, /* wglRestoreBufferRegionARB */
         124  /* wglSaveBufferRegionARB */
    };
    uint32_t i;
    if(!context->ARB_buffer_region) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_create_context(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          25  /* wglCreateContextAttribsARB */
    };
    uint32_t i;
    if(!context->ARB_create_context) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_extensions_string(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          71  /* wglGetExtensionsStringARB */
    };
    uint32_t i;
    if(!context->ARB_extensions_string) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_make_current_read(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          68, /* wglGetCurrentReadDCARB */
         101  /* wglMakeContextCurrentARB */
    };
    uint32_t i;
    if(!context->ARB_make_current_read) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_pbuffer(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          29, /* wglCreatePbufferARB */
          47, /* wglDestroyPbufferARB */
          84, /* wglGetPbufferDCARB */
         110, /* wglQueryPbufferARB */
         116  /* wglReleasePbufferDCARB */
    };
    uint32_t i;
    if(!context->ARB_pbuffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_pixel_format(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          16, /* wglChoosePixelFormatARB */
          86, /* wglGetPixelFormatAttribfvARB */
          88  /* wglGetPixelFormatAttribivARB */
    };
    uint32_t i;
    if(!context->ARB_pixel_format) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_render_texture(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          11, /* wglBindTexImageARB */
         118, /* wglReleaseTexImageARB */
         130  /* wglSetPbufferAttribARB */
    };
    uint32_t i;
    if(!context->ARB_render_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_display_color_table(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           9, /* wglBindDisplayColorTableEXT */
          26, /* wglCreateDisplayColorTableEXT */
          45, /* wglDestroyDisplayColorTableEXT */
          98  /* wglLoadDisplayColorTableEXT */
    };
    uint32_t i;
    if(!context->EXT_display_color_table) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_extensions_string(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          72  /* wglGetExtensionsStringEXT */
    };
    uint32_t i;
    if(!context->EXT_extensions_string) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_make_current_read(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          69, /* wglGetCurrentReadDCEXT */
         102  /* wglMakeContextCurrentEXT */
    };
    uint32_t i;
    if(!context->EXT_make_current_read) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_pbuffer(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          30, /* wglCreatePbufferEXT */
          48, /* wglDestroyPbufferEXT */
          85, /* wglGetPbufferDCEXT */
         111, /* wglQueryPbufferEXT */
         117  /* wglReleasePbufferDCEXT */
    };
    uint32_t i;
    if(!context->EXT_pbuffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_pixel_format(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          17, /* wglChoosePixelFormatEXT */
          87, /* wglGetPixelFormatAttribfvEXT */
          89  /* wglGetPixelFormatAttribivEXT */
    };
    uint32_t i;
    if(!context->EXT_pixel_format) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_swap_control(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          91, /* wglGetSwapIntervalEXT */
         134  /* wglSwapIntervalEXT */
    };
    uint32_t i;
    if(!context->EXT_swap_control) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_digital_video_control(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          70, /* wglGetDigitalVideoParametersI3D */
         126  /* wglSetDigitalVideoParametersI3D */
    };
    uint32_t i;
    if(!context->I3D_digital_video_control) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_gamma(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          76, /* wglGetGammaTableI3D */
          77, /* wglGetGammaTableParametersI3D */
         127, /* wglSetGammaTableI3D */
         128  /* wglSetGammaTableParametersI3D */
    };
    uint32_t i;
    if(!context->I3D_gamma) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_genlock(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          50, /* wglDisableGenlockI3D */
          52, /* wglEnableGenlockI3D */
          60, /* wglGenlockSampleRateI3D */
          61, /* wglGenlockSourceDelayI3D */
          62, /* wglGenlockSourceEdgeI3D */
          63, /* wglGenlockSourceI3D */
          78, /* wglGetGenlockSampleRateI3D */
          79, /* wglGetGenlockSourceDelayI3D */
          80, /* wglGetGenlockSourceEdgeI3D */
          81, /* wglGetGenlockSourceI3D */
          96, /* wglIsEnabledGenlockI3D */
         108  /* wglQueryGenlockMaxSourceDelayI3D */
    };
    uint32_t i;
    if(!context->I3D_genlock) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_image_buffer(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           7, /* wglAssociateImageBufferEventsI3D */
          27, /* wglCreateImageBufferI3D */
          46, /* wglDestroyImageBufferI3D */
         115  /* wglReleaseImageBufferEventsI3D */
    };
    uint32_t i;
    if(!context->I3D_image_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_swap_frame_lock(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          49, /* wglDisableFrameLockI3D */
          51, /* wglEnableFrameLockI3D */
          95, /* wglIsEnabledFrameLockI3D */
         106  /* wglQueryFrameLockMasterI3D */
    };
    uint32_t i;
    if(!context->I3D_swap_frame_lock) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_swap_frame_usage(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           8, /* wglBeginFrameTrackingI3D */
          53, /* wglEndFrameTrackingI3D */
          73, /* wglGetFrameUsageI3D */
         107  /* wglQueryFrameTrackingI3D */
    };
    uint32_t i;
    if(!context->I3D_swap_frame_usage) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_DX_interop(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          31, /* wglDXCloseDeviceNV */
          32, /* wglDXLockObjectsNV */
          33, /* wglDXObjectAccessNV */
          34, /* wglDXOpenDeviceNV */
          35, /* wglDXRegisterObjectNV */
          36, /* wglDXSetResourceShareHandleNV */
          37, /* wglDXUnlockObjectsNV */
          38  /* wglDXUnregisterObjectNV */
    };
    uint32_t i;
    if(!context->NV_DX_interop) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_copy_image(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          19  /* wglCopyImageSubDataNV */
    };
    uint32_t i;
    if(!context->NV_copy_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_delay_before_swap(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          39  /* wglDelayBeforeSwapNV */
    };
    uint32_t i;
    if(!context->NV_delay_before_swap) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_gpu_affinity(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          20, /* wglCreateAffinityDCNV */
          43, /* wglDeleteDCNV */
          54, /* wglEnumGpuDevicesNV */
          55, /* wglEnumGpusFromAffinityDCNV */
          56  /* wglEnumGpusNV */
    };
    uint32_t i;
    if(!context->NV_gpu_affinity) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_present_video(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          13, /* wglBindVideoDeviceNV */
          58, /* wglEnumerateVideoDevicesNV */
         104  /* wglQueryCurrentContextNV */
    };
    uint32_t i;
    if(!context->NV_present_video) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_swap_group(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          10, /* wglBindSwapBarrierNV */
          97, /* wglJoinSwapGroupNV */
         105, /* wglQueryFrameCountNV */
         109, /* wglQueryMaxSwapGroupsNV */
         112, /* wglQuerySwapGroupNV */
         122  /* wglResetFrameCountNV */
    };
    uint32_t i;
    if(!context->NV_swap_group) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_vertex_array_range(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           6, /* wglAllocateMemoryNV */
          59  /* wglFreeMemoryNV */
    };
    uint32_t i;
    if(!context->NV_vertex_array_range) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_video_capture(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          12, /* wglBindVideoCaptureDeviceNV */
          57, /* wglEnumerateVideoCaptureDevicesNV */
          99, /* wglLockVideoCaptureDeviceNV */
         113, /* wglQueryVideoCaptureDeviceNV */
         119  /* wglReleaseVideoCaptureDeviceNV */
    };
    uint32_t i;
    if(!context->NV_video_capture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_video_output(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          14, /* wglBindVideoImageNV */
          93, /* wglGetVideoDeviceNV */
          94, /* wglGetVideoInfoNV */
         120, /* wglReleaseVideoDeviceNV */
         121, /* wglReleaseVideoImageNV */
         125  /* wglSendPbufferToVideoNV */
    };
    uint32_t i;
    if(!context->NV_video_output) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_OML_sync_control(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          83, /* wglGetMscRateOML */
          92, /* wglGetSyncValuesOML */
         133, /* wglSwapBuffersMscOML */
         136, /* wglSwapLayerBuffersMscOML */
         143, /* wglWaitForMscOML */
         144  /* wglWaitForSbcOML */
    };
    uint32_t i;
    if(!context->OML_sync_control) return;
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

int gladLoadWGLContextUserPtr(GladWGLContext *context, HDC hdc, GLADuserptrloadfunc load, void *userptr) {
    int version;
    context->GetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC) load(userptr, "wglGetExtensionsStringARB");
    context->GetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC) load(userptr, "wglGetExtensionsStringEXT");
    if(context->GetExtensionsStringARB == NULL && context->GetExtensionsStringEXT == NULL) return 0;
    version = glad_wgl_find_core_wgl(context);

    glad_wgl_load_WGL_VERSION_1_0(context, load, userptr);

    if (!glad_wgl_find_extensions_wgl(context, hdc)) return 0;
    glad_wgl_load_WGL_3DL_stereo_control(context, load, userptr);
    glad_wgl_load_WGL_AMD_gpu_association(context, load, userptr);
    glad_wgl_load_WGL_ARB_buffer_region(context, load, userptr);
    glad_wgl_load_WGL_ARB_create_context(context, load, userptr);
    glad_wgl_load_WGL_ARB_extensions_string(context, load, userptr);
    glad_wgl_load_WGL_ARB_make_current_read(context, load, userptr);
    glad_wgl_load_WGL_ARB_pbuffer(context, load, userptr);
    glad_wgl_load_WGL_ARB_pixel_format(context, load, userptr);
    glad_wgl_load_WGL_ARB_render_texture(context, load, userptr);
    glad_wgl_load_WGL_EXT_display_color_table(context, load, userptr);
    glad_wgl_load_WGL_EXT_extensions_string(context, load, userptr);
    glad_wgl_load_WGL_EXT_make_current_read(context, load, userptr);
    glad_wgl_load_WGL_EXT_pbuffer(context, load, userptr);
    glad_wgl_load_WGL_EXT_pixel_format(context, load, userptr);
    glad_wgl_load_WGL_EXT_swap_control(context, load, userptr);
    glad_wgl_load_WGL_I3D_digital_video_control(context, load, userptr);
    glad_wgl_load_WGL_I3D_gamma(context, load, userptr);
    glad_wgl_load_WGL_I3D_genlock(context, load, userptr);
    glad_wgl_load_WGL_I3D_image_buffer(context, load, userptr);
    glad_wgl_load_WGL_I3D_swap_frame_lock(context, load, userptr);
    glad_wgl_load_WGL_I3D_swap_frame_usage(context, load, userptr);
    glad_wgl_load_WGL_NV_DX_interop(context, load, userptr);
    glad_wgl_load_WGL_NV_copy_image(context, load, userptr);
    glad_wgl_load_WGL_NV_delay_before_swap(context, load, userptr);
    glad_wgl_load_WGL_NV_gpu_affinity(context, load, userptr);
    glad_wgl_load_WGL_NV_present_video(context, load, userptr);
    glad_wgl_load_WGL_NV_swap_group(context, load, userptr);
    glad_wgl_load_WGL_NV_vertex_array_range(context, load, userptr);
    glad_wgl_load_WGL_NV_video_capture(context, load, userptr);
    glad_wgl_load_WGL_NV_video_output(context, load, userptr);
    glad_wgl_load_WGL_OML_sync_control(context, load, userptr);

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

static GLADapiproc glad_wgl_get_proc(void *vuserptr, const char* name) {
    GLAD_UNUSED(vuserptr);
    return GLAD_GNUC_EXTENSION (GLADapiproc) wglGetProcAddress(name);
}

int gladLoaderLoadWGL(HDC hdc) {
    return gladLoadWGLUserPtr(hdc, glad_wgl_get_proc, NULL);
}

void gladLoaderResetWGL(void) {
    gladLoaderResetWGLContext(gladGetWGLContext());
}

void gladLoaderResetWGLContext(GladWGLContext *context) {
    memset(context, 0, sizeof(GladWGLContext));
}

#endif /* GLAD_WGL */

#ifdef __cplusplus
}
#endif
#endif
