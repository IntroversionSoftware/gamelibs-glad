/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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
    /*    0 */ "GetEnhMetaFilePixelFormat",
    /*    1 */ "wglAllocateMemoryNV",
    /*    2 */ "wglAssociateImageBufferEventsI3D",
    /*    3 */ "wglBeginFrameTrackingI3D",
    /*    4 */ "wglBindDisplayColorTableEXT",
    /*    5 */ "wglBindSwapBarrierNV",
    /*    6 */ "wglBindTexImageARB",
    /*    7 */ "wglBindVideoCaptureDeviceNV",
    /*    8 */ "wglBindVideoDeviceNV",
    /*    9 */ "wglBindVideoImageNV",
    /*   10 */ "wglBlitContextFramebufferAMD",
    /*   11 */ "wglChoosePixelFormatARB",
    /*   12 */ "wglChoosePixelFormatEXT",
    /*   13 */ "wglCopyContext",
    /*   14 */ "wglCopyImageSubDataNV",
    /*   15 */ "wglCreateAffinityDCNV",
    /*   16 */ "wglCreateAssociatedContextAMD",
    /*   17 */ "wglCreateAssociatedContextAttribsAMD",
    /*   18 */ "wglCreateBufferRegionARB",
    /*   19 */ "wglCreateContextAttribsARB",
    /*   20 */ "wglCreateDisplayColorTableEXT",
    /*   21 */ "wglCreateImageBufferI3D",
    /*   22 */ "wglCreateLayerContext",
    /*   23 */ "wglCreatePbufferARB",
    /*   24 */ "wglCreatePbufferEXT",
    /*   25 */ "wglDXCloseDeviceNV",
    /*   26 */ "wglDXLockObjectsNV",
    /*   27 */ "wglDXObjectAccessNV",
    /*   28 */ "wglDXOpenDeviceNV",
    /*   29 */ "wglDXRegisterObjectNV",
    /*   30 */ "wglDXSetResourceShareHandleNV",
    /*   31 */ "wglDXUnlockObjectsNV",
    /*   32 */ "wglDXUnregisterObjectNV",
    /*   33 */ "wglDelayBeforeSwapNV",
    /*   34 */ "wglDeleteAssociatedContextAMD",
    /*   35 */ "wglDeleteBufferRegionARB",
    /*   36 */ "wglDeleteDCNV",
    /*   37 */ "wglDescribeLayerPlane",
    /*   38 */ "wglDestroyDisplayColorTableEXT",
    /*   39 */ "wglDestroyImageBufferI3D",
    /*   40 */ "wglDestroyPbufferARB",
    /*   41 */ "wglDestroyPbufferEXT",
    /*   42 */ "wglDisableFrameLockI3D",
    /*   43 */ "wglDisableGenlockI3D",
    /*   44 */ "wglEnableFrameLockI3D",
    /*   45 */ "wglEnableGenlockI3D",
    /*   46 */ "wglEndFrameTrackingI3D",
    /*   47 */ "wglEnumGpuDevicesNV",
    /*   48 */ "wglEnumGpusFromAffinityDCNV",
    /*   49 */ "wglEnumGpusNV",
    /*   50 */ "wglEnumerateVideoCaptureDevicesNV",
    /*   51 */ "wglEnumerateVideoDevicesNV",
    /*   52 */ "wglFreeMemoryNV",
    /*   53 */ "wglGenlockSampleRateI3D",
    /*   54 */ "wglGenlockSourceDelayI3D",
    /*   55 */ "wglGenlockSourceEdgeI3D",
    /*   56 */ "wglGenlockSourceI3D",
    /*   57 */ "wglGetContextGPUIDAMD",
    /*   58 */ "wglGetCurrentAssociatedContextAMD",
    /*   59 */ "wglGetCurrentContext",
    /*   60 */ "wglGetCurrentDC",
    /*   61 */ "wglGetCurrentReadDCARB",
    /*   62 */ "wglGetCurrentReadDCEXT",
    /*   63 */ "wglGetDigitalVideoParametersI3D",
    /*   64 */ "wglGetExtensionsStringARB",
    /*   65 */ "wglGetExtensionsStringEXT",
    /*   66 */ "wglGetFrameUsageI3D",
    /*   67 */ "wglGetGPUIDsAMD",
    /*   68 */ "wglGetGPUInfoAMD",
    /*   69 */ "wglGetGammaTableI3D",
    /*   70 */ "wglGetGammaTableParametersI3D",
    /*   71 */ "wglGetGenlockSampleRateI3D",
    /*   72 */ "wglGetGenlockSourceDelayI3D",
    /*   73 */ "wglGetGenlockSourceEdgeI3D",
    /*   74 */ "wglGetGenlockSourceI3D",
    /*   75 */ "wglGetLayerPaletteEntries",
    /*   76 */ "wglGetMscRateOML",
    /*   77 */ "wglGetPbufferDCARB",
    /*   78 */ "wglGetPbufferDCEXT",
    /*   79 */ "wglGetPixelFormatAttribfvARB",
    /*   80 */ "wglGetPixelFormatAttribfvEXT",
    /*   81 */ "wglGetPixelFormatAttribivARB",
    /*   82 */ "wglGetPixelFormatAttribivEXT",
    /*   83 */ "wglGetSwapIntervalEXT",
    /*   84 */ "wglGetSyncValuesOML",
    /*   85 */ "wglGetVideoDeviceNV",
    /*   86 */ "wglGetVideoInfoNV",
    /*   87 */ "wglIsEnabledFrameLockI3D",
    /*   88 */ "wglIsEnabledGenlockI3D",
    /*   89 */ "wglJoinSwapGroupNV",
    /*   90 */ "wglLoadDisplayColorTableEXT",
    /*   91 */ "wglLockVideoCaptureDeviceNV",
    /*   92 */ "wglMakeAssociatedContextCurrentAMD",
    /*   93 */ "wglMakeContextCurrentARB",
    /*   94 */ "wglMakeContextCurrentEXT",
    /*   95 */ "wglQueryCurrentContextNV",
    /*   96 */ "wglQueryFrameCountNV",
    /*   97 */ "wglQueryFrameLockMasterI3D",
    /*   98 */ "wglQueryFrameTrackingI3D",
    /*   99 */ "wglQueryGenlockMaxSourceDelayI3D",
    /*  100 */ "wglQueryMaxSwapGroupsNV",
    /*  101 */ "wglQueryPbufferARB",
    /*  102 */ "wglQueryPbufferEXT",
    /*  103 */ "wglQuerySwapGroupNV",
    /*  104 */ "wglQueryVideoCaptureDeviceNV",
    /*  105 */ "wglRealizeLayerPalette",
    /*  106 */ "wglReleaseImageBufferEventsI3D",
    /*  107 */ "wglReleasePbufferDCARB",
    /*  108 */ "wglReleasePbufferDCEXT",
    /*  109 */ "wglReleaseTexImageARB",
    /*  110 */ "wglReleaseVideoCaptureDeviceNV",
    /*  111 */ "wglReleaseVideoDeviceNV",
    /*  112 */ "wglReleaseVideoImageNV",
    /*  113 */ "wglResetFrameCountNV",
    /*  114 */ "wglRestoreBufferRegionARB",
    /*  115 */ "wglSaveBufferRegionARB",
    /*  116 */ "wglSendPbufferToVideoNV",
    /*  117 */ "wglSetDigitalVideoParametersI3D",
    /*  118 */ "wglSetGammaTableI3D",
    /*  119 */ "wglSetGammaTableParametersI3D",
    /*  120 */ "wglSetLayerPaletteEntries",
    /*  121 */ "wglSetPbufferAttribARB",
    /*  122 */ "wglSetStereoEmitterState3DL",
    /*  123 */ "wglShareLists",
    /*  124 */ "wglSwapBuffersMscOML",
    /*  125 */ "wglSwapIntervalEXT",
    /*  126 */ "wglSwapLayerBuffers",
    /*  127 */ "wglSwapLayerBuffersMscOML",
    /*  128 */ "wglUseFontBitmaps",
    /*  129 */ "wglUseFontBitmapsA",
    /*  130 */ "wglUseFontBitmapsW",
    /*  131 */ "wglUseFontOutlines",
    /*  132 */ "wglUseFontOutlinesA",
    /*  133 */ "wglUseFontOutlinesW",
    /*  134 */ "wglWaitForMscOML",
    /*  135 */ "wglWaitForSbcOML"
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
           0, /* GetEnhMetaFilePixelFormat */
          13, /* wglCopyContext */
          22, /* wglCreateLayerContext */
          37, /* wglDescribeLayerPlane */
          59, /* wglGetCurrentContext */
          60, /* wglGetCurrentDC */
          75, /* wglGetLayerPaletteEntries */
         105, /* wglRealizeLayerPalette */
         120, /* wglSetLayerPaletteEntries */
         123, /* wglShareLists */
         126, /* wglSwapLayerBuffers */
         128, /* wglUseFontBitmaps */
         129, /* wglUseFontBitmapsA */
         130, /* wglUseFontBitmapsW */
         131, /* wglUseFontOutlines */
         132, /* wglUseFontOutlinesA */
         133  /* wglUseFontOutlinesW */
    };
    uint32_t i;
    if(!context->VERSION_1_0) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_3DL_stereo_control(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         122  /* wglSetStereoEmitterState3DL */
    };
    uint32_t i;
    if(!context->_3DL_stereo_control) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_AMD_gpu_association(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          10, /* wglBlitContextFramebufferAMD */
          16, /* wglCreateAssociatedContextAMD */
          17, /* wglCreateAssociatedContextAttribsAMD */
          34, /* wglDeleteAssociatedContextAMD */
          57, /* wglGetContextGPUIDAMD */
          58, /* wglGetCurrentAssociatedContextAMD */
          67, /* wglGetGPUIDsAMD */
          68, /* wglGetGPUInfoAMD */
          92  /* wglMakeAssociatedContextCurrentAMD */
    };
    uint32_t i;
    if(!context->AMD_gpu_association) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_buffer_region(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          18, /* wglCreateBufferRegionARB */
          35, /* wglDeleteBufferRegionARB */
         114, /* wglRestoreBufferRegionARB */
         115  /* wglSaveBufferRegionARB */
    };
    uint32_t i;
    if(!context->ARB_buffer_region) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_create_context(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          19  /* wglCreateContextAttribsARB */
    };
    uint32_t i;
    if(!context->ARB_create_context) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_extensions_string(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          64  /* wglGetExtensionsStringARB */
    };
    uint32_t i;
    if(!context->ARB_extensions_string) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_make_current_read(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          61, /* wglGetCurrentReadDCARB */
          93  /* wglMakeContextCurrentARB */
    };
    uint32_t i;
    if(!context->ARB_make_current_read) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_pbuffer(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          23, /* wglCreatePbufferARB */
          40, /* wglDestroyPbufferARB */
          77, /* wglGetPbufferDCARB */
         101, /* wglQueryPbufferARB */
         107  /* wglReleasePbufferDCARB */
    };
    uint32_t i;
    if(!context->ARB_pbuffer) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_pixel_format(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          11, /* wglChoosePixelFormatARB */
          79, /* wglGetPixelFormatAttribfvARB */
          81  /* wglGetPixelFormatAttribivARB */
    };
    uint32_t i;
    if(!context->ARB_pixel_format) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_render_texture(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           6, /* wglBindTexImageARB */
         109, /* wglReleaseTexImageARB */
         121  /* wglSetPbufferAttribARB */
    };
    uint32_t i;
    if(!context->ARB_render_texture) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_display_color_table(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           4, /* wglBindDisplayColorTableEXT */
          20, /* wglCreateDisplayColorTableEXT */
          38, /* wglDestroyDisplayColorTableEXT */
          90  /* wglLoadDisplayColorTableEXT */
    };
    uint32_t i;
    if(!context->EXT_display_color_table) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_extensions_string(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          65  /* wglGetExtensionsStringEXT */
    };
    uint32_t i;
    if(!context->EXT_extensions_string) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_make_current_read(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          62, /* wglGetCurrentReadDCEXT */
          94  /* wglMakeContextCurrentEXT */
    };
    uint32_t i;
    if(!context->EXT_make_current_read) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_pbuffer(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          24, /* wglCreatePbufferEXT */
          41, /* wglDestroyPbufferEXT */
          78, /* wglGetPbufferDCEXT */
         102, /* wglQueryPbufferEXT */
         108  /* wglReleasePbufferDCEXT */
    };
    uint32_t i;
    if(!context->EXT_pbuffer) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_pixel_format(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          12, /* wglChoosePixelFormatEXT */
          80, /* wglGetPixelFormatAttribfvEXT */
          82  /* wglGetPixelFormatAttribivEXT */
    };
    uint32_t i;
    if(!context->EXT_pixel_format) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_swap_control(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          83, /* wglGetSwapIntervalEXT */
         125  /* wglSwapIntervalEXT */
    };
    uint32_t i;
    if(!context->EXT_swap_control) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_digital_video_control(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          63, /* wglGetDigitalVideoParametersI3D */
         117  /* wglSetDigitalVideoParametersI3D */
    };
    uint32_t i;
    if(!context->I3D_digital_video_control) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_gamma(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          69, /* wglGetGammaTableI3D */
          70, /* wglGetGammaTableParametersI3D */
         118, /* wglSetGammaTableI3D */
         119  /* wglSetGammaTableParametersI3D */
    };
    uint32_t i;
    if(!context->I3D_gamma) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_genlock(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          43, /* wglDisableGenlockI3D */
          45, /* wglEnableGenlockI3D */
          53, /* wglGenlockSampleRateI3D */
          54, /* wglGenlockSourceDelayI3D */
          55, /* wglGenlockSourceEdgeI3D */
          56, /* wglGenlockSourceI3D */
          71, /* wglGetGenlockSampleRateI3D */
          72, /* wglGetGenlockSourceDelayI3D */
          73, /* wglGetGenlockSourceEdgeI3D */
          74, /* wglGetGenlockSourceI3D */
          88, /* wglIsEnabledGenlockI3D */
          99  /* wglQueryGenlockMaxSourceDelayI3D */
    };
    uint32_t i;
    if(!context->I3D_genlock) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_image_buffer(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           2, /* wglAssociateImageBufferEventsI3D */
          21, /* wglCreateImageBufferI3D */
          39, /* wglDestroyImageBufferI3D */
         106  /* wglReleaseImageBufferEventsI3D */
    };
    uint32_t i;
    if(!context->I3D_image_buffer) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_swap_frame_lock(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          42, /* wglDisableFrameLockI3D */
          44, /* wglEnableFrameLockI3D */
          87, /* wglIsEnabledFrameLockI3D */
          97  /* wglQueryFrameLockMasterI3D */
    };
    uint32_t i;
    if(!context->I3D_swap_frame_lock) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_swap_frame_usage(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           3, /* wglBeginFrameTrackingI3D */
          46, /* wglEndFrameTrackingI3D */
          66, /* wglGetFrameUsageI3D */
          98  /* wglQueryFrameTrackingI3D */
    };
    uint32_t i;
    if(!context->I3D_swap_frame_usage) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_DX_interop(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          25, /* wglDXCloseDeviceNV */
          26, /* wglDXLockObjectsNV */
          27, /* wglDXObjectAccessNV */
          28, /* wglDXOpenDeviceNV */
          29, /* wglDXRegisterObjectNV */
          30, /* wglDXSetResourceShareHandleNV */
          31, /* wglDXUnlockObjectsNV */
          32  /* wglDXUnregisterObjectNV */
    };
    uint32_t i;
    if(!context->NV_DX_interop) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_copy_image(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          14  /* wglCopyImageSubDataNV */
    };
    uint32_t i;
    if(!context->NV_copy_image) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_delay_before_swap(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          33  /* wglDelayBeforeSwapNV */
    };
    uint32_t i;
    if(!context->NV_delay_before_swap) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_gpu_affinity(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          15, /* wglCreateAffinityDCNV */
          36, /* wglDeleteDCNV */
          47, /* wglEnumGpuDevicesNV */
          48, /* wglEnumGpusFromAffinityDCNV */
          49  /* wglEnumGpusNV */
    };
    uint32_t i;
    if(!context->NV_gpu_affinity) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_present_video(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           8, /* wglBindVideoDeviceNV */
          51, /* wglEnumerateVideoDevicesNV */
          95  /* wglQueryCurrentContextNV */
    };
    uint32_t i;
    if(!context->NV_present_video) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_swap_group(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           5, /* wglBindSwapBarrierNV */
          89, /* wglJoinSwapGroupNV */
          96, /* wglQueryFrameCountNV */
         100, /* wglQueryMaxSwapGroupsNV */
         103, /* wglQuerySwapGroupNV */
         113  /* wglResetFrameCountNV */
    };
    uint32_t i;
    if(!context->NV_swap_group) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_vertex_array_range(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           1, /* wglAllocateMemoryNV */
          52  /* wglFreeMemoryNV */
    };
    uint32_t i;
    if(!context->NV_vertex_array_range) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_video_capture(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           7, /* wglBindVideoCaptureDeviceNV */
          50, /* wglEnumerateVideoCaptureDevicesNV */
          91, /* wglLockVideoCaptureDeviceNV */
         104, /* wglQueryVideoCaptureDeviceNV */
         110  /* wglReleaseVideoCaptureDeviceNV */
    };
    uint32_t i;
    if(!context->NV_video_capture) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_video_output(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           9, /* wglBindVideoImageNV */
          85, /* wglGetVideoDeviceNV */
          86, /* wglGetVideoInfoNV */
         111, /* wglReleaseVideoDeviceNV */
         112, /* wglReleaseVideoImageNV */
         116  /* wglSendPbufferToVideoNV */
    };
    uint32_t i;
    if(!context->NV_video_output) return;
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_OML_sync_control(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          76, /* wglGetMscRateOML */
          84, /* wglGetSyncValuesOML */
         124, /* wglSwapBuffersMscOML */
         127, /* wglSwapLayerBuffersMscOML */
         134, /* wglWaitForMscOML */
         135  /* wglWaitForSbcOML */
    };
    uint32_t i;
    if(!context->OML_sync_control) return;
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
