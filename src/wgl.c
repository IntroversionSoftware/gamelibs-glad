/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <glad/wgl.h>

#ifdef _WIN32
#ifndef GLAD_IMPL_UTIL_C_
#define GLAD_IMPL_UTIL_C_

#ifdef _MSC_VER
#define GLAD_IMPL_UTIL_SSCANF sscanf_s
#else
#define GLAD_IMPL_UTIL_SSCANF sscanf
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

static const char *glad_pfn_names[] = {
    "ChoosePixelFormat", // 0
    "DescribePixelFormat", // 1
    "GetEnhMetaFilePixelFormat", // 2
    "GetPixelFormat", // 3
    "SetPixelFormat", // 4
    "SwapBuffers", // 5
    "wglAllocateMemoryNV", // 6
    "wglAssociateImageBufferEventsI3D", // 7
    "wglBeginFrameTrackingI3D", // 8
    "wglBindDisplayColorTableEXT", // 9
    "wglBindSwapBarrierNV", // 10
    "wglBindTexImageARB", // 11
    "wglBindVideoCaptureDeviceNV", // 12
    "wglBindVideoDeviceNV", // 13
    "wglBindVideoImageNV", // 14
    "wglBlitContextFramebufferAMD", // 15
    "wglChoosePixelFormatARB", // 16
    "wglChoosePixelFormatEXT", // 17
    "wglCopyContext", // 18
    "wglCopyImageSubDataNV", // 19
    "wglCreateAffinityDCNV", // 20
    "wglCreateAssociatedContextAMD", // 21
    "wglCreateAssociatedContextAttribsAMD", // 22
    "wglCreateBufferRegionARB", // 23
    "wglCreateContext", // 24
    "wglCreateContextAttribsARB", // 25
    "wglCreateDisplayColorTableEXT", // 26
    "wglCreateImageBufferI3D", // 27
    "wglCreateLayerContext", // 28
    "wglCreatePbufferARB", // 29
    "wglCreatePbufferEXT", // 30
    "wglDXCloseDeviceNV", // 31
    "wglDXLockObjectsNV", // 32
    "wglDXObjectAccessNV", // 33
    "wglDXOpenDeviceNV", // 34
    "wglDXRegisterObjectNV", // 35
    "wglDXSetResourceShareHandleNV", // 36
    "wglDXUnlockObjectsNV", // 37
    "wglDXUnregisterObjectNV", // 38
    "wglDelayBeforeSwapNV", // 39
    "wglDeleteAssociatedContextAMD", // 40
    "wglDeleteBufferRegionARB", // 41
    "wglDeleteContext", // 42
    "wglDeleteDCNV", // 43
    "wglDescribeLayerPlane", // 44
    "wglDestroyDisplayColorTableEXT", // 45
    "wglDestroyImageBufferI3D", // 46
    "wglDestroyPbufferARB", // 47
    "wglDestroyPbufferEXT", // 48
    "wglDisableFrameLockI3D", // 49
    "wglDisableGenlockI3D", // 50
    "wglEnableFrameLockI3D", // 51
    "wglEnableGenlockI3D", // 52
    "wglEndFrameTrackingI3D", // 53
    "wglEnumGpuDevicesNV", // 54
    "wglEnumGpusFromAffinityDCNV", // 55
    "wglEnumGpusNV", // 56
    "wglEnumerateVideoCaptureDevicesNV", // 57
    "wglEnumerateVideoDevicesNV", // 58
    "wglFreeMemoryNV", // 59
    "wglGenlockSampleRateI3D", // 60
    "wglGenlockSourceDelayI3D", // 61
    "wglGenlockSourceEdgeI3D", // 62
    "wglGenlockSourceI3D", // 63
    "wglGetContextGPUIDAMD", // 64
    "wglGetCurrentAssociatedContextAMD", // 65
    "wglGetCurrentContext", // 66
    "wglGetCurrentDC", // 67
    "wglGetCurrentReadDCARB", // 68
    "wglGetCurrentReadDCEXT", // 69
    "wglGetDigitalVideoParametersI3D", // 70
    "wglGetExtensionsStringARB", // 71
    "wglGetExtensionsStringEXT", // 72
    "wglGetFrameUsageI3D", // 73
    "wglGetGPUIDsAMD", // 74
    "wglGetGPUInfoAMD", // 75
    "wglGetGammaTableI3D", // 76
    "wglGetGammaTableParametersI3D", // 77
    "wglGetGenlockSampleRateI3D", // 78
    "wglGetGenlockSourceDelayI3D", // 79
    "wglGetGenlockSourceEdgeI3D", // 80
    "wglGetGenlockSourceI3D", // 81
    "wglGetLayerPaletteEntries", // 82
    "wglGetMscRateOML", // 83
    "wglGetPbufferDCARB", // 84
    "wglGetPbufferDCEXT", // 85
    "wglGetPixelFormatAttribfvARB", // 86
    "wglGetPixelFormatAttribfvEXT", // 87
    "wglGetPixelFormatAttribivARB", // 88
    "wglGetPixelFormatAttribivEXT", // 89
    "wglGetProcAddress", // 90
    "wglGetSwapIntervalEXT", // 91
    "wglGetSyncValuesOML", // 92
    "wglGetVideoDeviceNV", // 93
    "wglGetVideoInfoNV", // 94
    "wglIsEnabledFrameLockI3D", // 95
    "wglIsEnabledGenlockI3D", // 96
    "wglJoinSwapGroupNV", // 97
    "wglLoadDisplayColorTableEXT", // 98
    "wglLockVideoCaptureDeviceNV", // 99
    "wglMakeAssociatedContextCurrentAMD", // 100
    "wglMakeContextCurrentARB", // 101
    "wglMakeContextCurrentEXT", // 102
    "wglMakeCurrent", // 103
    "wglQueryCurrentContextNV", // 104
    "wglQueryFrameCountNV", // 105
    "wglQueryFrameLockMasterI3D", // 106
    "wglQueryFrameTrackingI3D", // 107
    "wglQueryGenlockMaxSourceDelayI3D", // 108
    "wglQueryMaxSwapGroupsNV", // 109
    "wglQueryPbufferARB", // 110
    "wglQueryPbufferEXT", // 111
    "wglQuerySwapGroupNV", // 112
    "wglQueryVideoCaptureDeviceNV", // 113
    "wglRealizeLayerPalette", // 114
    "wglReleaseImageBufferEventsI3D", // 115
    "wglReleasePbufferDCARB", // 116
    "wglReleasePbufferDCEXT", // 117
    "wglReleaseTexImageARB", // 118
    "wglReleaseVideoCaptureDeviceNV", // 119
    "wglReleaseVideoDeviceNV", // 120
    "wglReleaseVideoImageNV", // 121
    "wglResetFrameCountNV", // 122
    "wglRestoreBufferRegionARB", // 123
    "wglSaveBufferRegionARB", // 124
    "wglSendPbufferToVideoNV", // 125
    "wglSetDigitalVideoParametersI3D", // 126
    "wglSetGammaTableI3D", // 127
    "wglSetGammaTableParametersI3D", // 128
    "wglSetLayerPaletteEntries", // 129
    "wglSetPbufferAttribARB", // 130
    "wglSetStereoEmitterState3DL", // 131
    "wglShareLists", // 132
    "wglSwapBuffersMscOML", // 133
    "wglSwapIntervalEXT", // 134
    "wglSwapLayerBuffers", // 135
    "wglSwapLayerBuffersMscOML", // 136
    "wglUseFontBitmaps", // 137
    "wglUseFontBitmapsA", // 138
    "wglUseFontBitmapsW", // 139
    "wglUseFontOutlines", // 140
    "wglUseFontOutlinesA", // 141
    "wglUseFontOutlinesW", // 142
    "wglWaitForMscOML", // 143
    "wglWaitForSbcOML" // 144
};

static const char *glad_ext_names[] = {
    "WGL_3DFX_multisample", // 0
    "WGL_3DL_stereo_control", // 1
    "WGL_AMD_gpu_association", // 2
    "WGL_ARB_buffer_region", // 3
    "WGL_ARB_context_flush_control", // 4
    "WGL_ARB_create_context", // 5
    "WGL_ARB_create_context_no_error", // 6
    "WGL_ARB_create_context_profile", // 7
    "WGL_ARB_create_context_robustness", // 8
    "WGL_ARB_extensions_string", // 9
    "WGL_ARB_framebuffer_sRGB", // 10
    "WGL_ARB_make_current_read", // 11
    "WGL_ARB_multisample", // 12
    "WGL_ARB_pbuffer", // 13
    "WGL_ARB_pixel_format", // 14
    "WGL_ARB_pixel_format_float", // 15
    "WGL_ARB_render_texture", // 16
    "WGL_ARB_robustness_application_isolation", // 17
    "WGL_ARB_robustness_share_group_isolation", // 18
    "WGL_ATI_pixel_format_float", // 19
    "WGL_ATI_render_texture_rectangle", // 20
    "WGL_EXT_colorspace", // 21
    "WGL_EXT_create_context_es2_profile", // 22
    "WGL_EXT_create_context_es_profile", // 23
    "WGL_EXT_depth_float", // 24
    "WGL_EXT_display_color_table", // 25
    "WGL_EXT_extensions_string", // 26
    "WGL_EXT_framebuffer_sRGB", // 27
    "WGL_EXT_make_current_read", // 28
    "WGL_EXT_multisample", // 29
    "WGL_EXT_pbuffer", // 30
    "WGL_EXT_pixel_format", // 31
    "WGL_EXT_pixel_format_packed_float", // 32
    "WGL_EXT_swap_control", // 33
    "WGL_EXT_swap_control_tear", // 34
    "WGL_I3D_digital_video_control", // 35
    "WGL_I3D_gamma", // 36
    "WGL_I3D_genlock", // 37
    "WGL_I3D_image_buffer", // 38
    "WGL_I3D_swap_frame_lock", // 39
    "WGL_I3D_swap_frame_usage", // 40
    "WGL_NV_DX_interop", // 41
    "WGL_NV_DX_interop2", // 42
    "WGL_NV_copy_image", // 43
    "WGL_NV_delay_before_swap", // 44
    "WGL_NV_float_buffer", // 45
    "WGL_NV_gpu_affinity", // 46
    "WGL_NV_multigpu_context", // 47
    "WGL_NV_multisample_coverage", // 48
    "WGL_NV_present_video", // 49
    "WGL_NV_render_depth_texture", // 50
    "WGL_NV_render_texture_rectangle", // 51
    "WGL_NV_swap_group", // 52
    "WGL_NV_vertex_array_range", // 53
    "WGL_NV_video_capture", // 54
    "WGL_NV_video_output", // 55
    "WGL_OML_sync_control" // 56
};

#ifdef __cplusplus
GladWGLContext glad_wgl_context = {};
#else
GladWGLContext glad_wgl_context = { 0 };
#endif

static void glad_wgl_load_WGL_VERSION_1_0(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_0) return;
    static const uint16_t s_pfnIdx[] = {
            0, // ChoosePixelFormat
            1, // DescribePixelFormat
            2, // GetEnhMetaFilePixelFormat
            3, // GetPixelFormat
            4, // SetPixelFormat
            5, // SwapBuffers
           18, // wglCopyContext
           24, // wglCreateContext
           28, // wglCreateLayerContext
           42, // wglDeleteContext
           44, // wglDescribeLayerPlane
           66, // wglGetCurrentContext
           67, // wglGetCurrentDC
           82, // wglGetLayerPaletteEntries
           90, // wglGetProcAddress
          103, // wglMakeCurrent
          114, // wglRealizeLayerPalette
          129, // wglSetLayerPaletteEntries
          132, // wglShareLists
          135, // wglSwapLayerBuffers
          137, // wglUseFontBitmaps
          138, // wglUseFontBitmapsA
          139, // wglUseFontBitmapsW
          140, // wglUseFontOutlines
          141, // wglUseFontOutlinesA
          142  // wglUseFontOutlinesW
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_3DL_stereo_control(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->_3DL_stereo_control) return;
    static const uint16_t s_pfnIdx[] = {
          131  // wglSetStereoEmitterState3DL
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_AMD_gpu_association(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_gpu_association) return;
    static const uint16_t s_pfnIdx[] = {
           15, // wglBlitContextFramebufferAMD
           21, // wglCreateAssociatedContextAMD
           22, // wglCreateAssociatedContextAttribsAMD
           40, // wglDeleteAssociatedContextAMD
           64, // wglGetContextGPUIDAMD
           65, // wglGetCurrentAssociatedContextAMD
           74, // wglGetGPUIDsAMD
           75, // wglGetGPUInfoAMD
          100  // wglMakeAssociatedContextCurrentAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_buffer_region(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_buffer_region) return;
    static const uint16_t s_pfnIdx[] = {
           23, // wglCreateBufferRegionARB
           41, // wglDeleteBufferRegionARB
          123, // wglRestoreBufferRegionARB
          124  // wglSaveBufferRegionARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_create_context(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_create_context) return;
    static const uint16_t s_pfnIdx[] = {
           25  // wglCreateContextAttribsARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_extensions_string(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_extensions_string) return;
    static const uint16_t s_pfnIdx[] = {
           71  // wglGetExtensionsStringARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_make_current_read(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_make_current_read) return;
    static const uint16_t s_pfnIdx[] = {
           68, // wglGetCurrentReadDCARB
          101  // wglMakeContextCurrentARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_pbuffer(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_pbuffer) return;
    static const uint16_t s_pfnIdx[] = {
           29, // wglCreatePbufferARB
           47, // wglDestroyPbufferARB
           84, // wglGetPbufferDCARB
          110, // wglQueryPbufferARB
          116  // wglReleasePbufferDCARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_pixel_format(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_pixel_format) return;
    static const uint16_t s_pfnIdx[] = {
           16, // wglChoosePixelFormatARB
           86, // wglGetPixelFormatAttribfvARB
           88  // wglGetPixelFormatAttribivARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_ARB_render_texture(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_render_texture) return;
    static const uint16_t s_pfnIdx[] = {
           11, // wglBindTexImageARB
          118, // wglReleaseTexImageARB
          130  // wglSetPbufferAttribARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_display_color_table(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_display_color_table) return;
    static const uint16_t s_pfnIdx[] = {
            9, // wglBindDisplayColorTableEXT
           26, // wglCreateDisplayColorTableEXT
           45, // wglDestroyDisplayColorTableEXT
           98  // wglLoadDisplayColorTableEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_extensions_string(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_extensions_string) return;
    static const uint16_t s_pfnIdx[] = {
           72  // wglGetExtensionsStringEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_make_current_read(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_make_current_read) return;
    static const uint16_t s_pfnIdx[] = {
           69, // wglGetCurrentReadDCEXT
          102  // wglMakeContextCurrentEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_pbuffer(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_pbuffer) return;
    static const uint16_t s_pfnIdx[] = {
           30, // wglCreatePbufferEXT
           48, // wglDestroyPbufferEXT
           85, // wglGetPbufferDCEXT
          111, // wglQueryPbufferEXT
          117  // wglReleasePbufferDCEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_pixel_format(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_pixel_format) return;
    static const uint16_t s_pfnIdx[] = {
           17, // wglChoosePixelFormatEXT
           87, // wglGetPixelFormatAttribfvEXT
           89  // wglGetPixelFormatAttribivEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_EXT_swap_control(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_swap_control) return;
    static const uint16_t s_pfnIdx[] = {
           91, // wglGetSwapIntervalEXT
          134  // wglSwapIntervalEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_digital_video_control(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->I3D_digital_video_control) return;
    static const uint16_t s_pfnIdx[] = {
           70, // wglGetDigitalVideoParametersI3D
          126  // wglSetDigitalVideoParametersI3D
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_gamma(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->I3D_gamma) return;
    static const uint16_t s_pfnIdx[] = {
           76, // wglGetGammaTableI3D
           77, // wglGetGammaTableParametersI3D
          127, // wglSetGammaTableI3D
          128  // wglSetGammaTableParametersI3D
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_genlock(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->I3D_genlock) return;
    static const uint16_t s_pfnIdx[] = {
           50, // wglDisableGenlockI3D
           52, // wglEnableGenlockI3D
           60, // wglGenlockSampleRateI3D
           61, // wglGenlockSourceDelayI3D
           62, // wglGenlockSourceEdgeI3D
           63, // wglGenlockSourceI3D
           78, // wglGetGenlockSampleRateI3D
           79, // wglGetGenlockSourceDelayI3D
           80, // wglGetGenlockSourceEdgeI3D
           81, // wglGetGenlockSourceI3D
           96, // wglIsEnabledGenlockI3D
          108  // wglQueryGenlockMaxSourceDelayI3D
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_image_buffer(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->I3D_image_buffer) return;
    static const uint16_t s_pfnIdx[] = {
            7, // wglAssociateImageBufferEventsI3D
           27, // wglCreateImageBufferI3D
           46, // wglDestroyImageBufferI3D
          115  // wglReleaseImageBufferEventsI3D
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_swap_frame_lock(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->I3D_swap_frame_lock) return;
    static const uint16_t s_pfnIdx[] = {
           49, // wglDisableFrameLockI3D
           51, // wglEnableFrameLockI3D
           95, // wglIsEnabledFrameLockI3D
          106  // wglQueryFrameLockMasterI3D
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_I3D_swap_frame_usage(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->I3D_swap_frame_usage) return;
    static const uint16_t s_pfnIdx[] = {
            8, // wglBeginFrameTrackingI3D
           53, // wglEndFrameTrackingI3D
           73, // wglGetFrameUsageI3D
          107  // wglQueryFrameTrackingI3D
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_DX_interop(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_DX_interop) return;
    static const uint16_t s_pfnIdx[] = {
           31, // wglDXCloseDeviceNV
           32, // wglDXLockObjectsNV
           33, // wglDXObjectAccessNV
           34, // wglDXOpenDeviceNV
           35, // wglDXRegisterObjectNV
           36, // wglDXSetResourceShareHandleNV
           37, // wglDXUnlockObjectsNV
           38  // wglDXUnregisterObjectNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_copy_image(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_copy_image) return;
    static const uint16_t s_pfnIdx[] = {
           19  // wglCopyImageSubDataNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_delay_before_swap(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_delay_before_swap) return;
    static const uint16_t s_pfnIdx[] = {
           39  // wglDelayBeforeSwapNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_gpu_affinity(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_gpu_affinity) return;
    static const uint16_t s_pfnIdx[] = {
           20, // wglCreateAffinityDCNV
           43, // wglDeleteDCNV
           54, // wglEnumGpuDevicesNV
           55, // wglEnumGpusFromAffinityDCNV
           56  // wglEnumGpusNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_present_video(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_present_video) return;
    static const uint16_t s_pfnIdx[] = {
           13, // wglBindVideoDeviceNV
           58, // wglEnumerateVideoDevicesNV
          104  // wglQueryCurrentContextNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_swap_group(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_swap_group) return;
    static const uint16_t s_pfnIdx[] = {
           10, // wglBindSwapBarrierNV
           97, // wglJoinSwapGroupNV
          105, // wglQueryFrameCountNV
          109, // wglQueryMaxSwapGroupsNV
          112, // wglQuerySwapGroupNV
          122  // wglResetFrameCountNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_vertex_array_range(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_vertex_array_range) return;
    static const uint16_t s_pfnIdx[] = {
            6, // wglAllocateMemoryNV
           59  // wglFreeMemoryNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_video_capture(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_video_capture) return;
    static const uint16_t s_pfnIdx[] = {
           12, // wglBindVideoCaptureDeviceNV
           57, // wglEnumerateVideoCaptureDevicesNV
           99, // wglLockVideoCaptureDeviceNV
          113, // wglQueryVideoCaptureDeviceNV
          119  // wglReleaseVideoCaptureDeviceNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_NV_video_output(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_video_output) return;
    static const uint16_t s_pfnIdx[] = {
           14, // wglBindVideoImageNV
           93, // wglGetVideoDeviceNV
           94, // wglGetVideoInfoNV
          120, // wglReleaseVideoDeviceNV
          121, // wglReleaseVideoImageNV
          125  // wglSendPbufferToVideoNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_load_WGL_OML_sync_control(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OML_sync_control) return;
    static const uint16_t s_pfnIdx[] = {
           83, // wglGetMscRateOML
           92, // wglGetSyncValuesOML
          133, // wglSwapBuffersMscOML
          136, // wglSwapLayerBuffersMscOML
          143, // wglWaitForMscOML
          144  // wglWaitForSbcOML
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_wgl_resolve_aliases(GladWGLContext *context) {
    static const GladAliasPair_t s_aliases[] = {
        { 0xFFFF, 0xFFFF }
    };

    void **pfnArray = context->pfnArray;

    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_aliases) - 1; ++i) {
        const GladAliasPair_t *pAlias = &s_aliases[i];
        if (pfnArray[pAlias->first] == NULL && pfnArray[pAlias->second] != NULL) {
            pfnArray[pAlias->first] = pfnArray[pAlias->second];
        } else if (pfnArray[pAlias->second] == NULL && pfnArray[pAlias->first] != NULL) {
            pfnArray[pAlias->second] = pfnArray[pAlias->first];
        }
    }
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
    static uint16_t extIdx[] = {
             0, // WGL_3DFX_multisample
             1, // WGL_3DL_stereo_control
             2, // WGL_AMD_gpu_association
             3, // WGL_ARB_buffer_region
             4, // WGL_ARB_context_flush_control
             5, // WGL_ARB_create_context
             6, // WGL_ARB_create_context_no_error
             7, // WGL_ARB_create_context_profile
             8, // WGL_ARB_create_context_robustness
             9, // WGL_ARB_extensions_string
            10, // WGL_ARB_framebuffer_sRGB
            11, // WGL_ARB_make_current_read
            12, // WGL_ARB_multisample
            13, // WGL_ARB_pbuffer
            14, // WGL_ARB_pixel_format
            15, // WGL_ARB_pixel_format_float
            16, // WGL_ARB_render_texture
            17, // WGL_ARB_robustness_application_isolation
            18, // WGL_ARB_robustness_share_group_isolation
            19, // WGL_ATI_pixel_format_float
            20, // WGL_ATI_render_texture_rectangle
            21, // WGL_EXT_colorspace
            22, // WGL_EXT_create_context_es2_profile
            23, // WGL_EXT_create_context_es_profile
            24, // WGL_EXT_depth_float
            25, // WGL_EXT_display_color_table
            26, // WGL_EXT_extensions_string
            27, // WGL_EXT_framebuffer_sRGB
            28, // WGL_EXT_make_current_read
            29, // WGL_EXT_multisample
            30, // WGL_EXT_pbuffer
            31, // WGL_EXT_pixel_format
            32, // WGL_EXT_pixel_format_packed_float
            33, // WGL_EXT_swap_control
            34, // WGL_EXT_swap_control_tear
            35, // WGL_I3D_digital_video_control
            36, // WGL_I3D_gamma
            37, // WGL_I3D_genlock
            38, // WGL_I3D_image_buffer
            39, // WGL_I3D_swap_frame_lock
            40, // WGL_I3D_swap_frame_usage
            41, // WGL_NV_DX_interop
            42, // WGL_NV_DX_interop2
            43, // WGL_NV_copy_image
            44, // WGL_NV_delay_before_swap
            45, // WGL_NV_float_buffer
            46, // WGL_NV_gpu_affinity
            47, // WGL_NV_multigpu_context
            48, // WGL_NV_multisample_coverage
            49, // WGL_NV_present_video
            50, // WGL_NV_render_depth_texture
            51, // WGL_NV_render_texture_rectangle
            52, // WGL_NV_swap_group
            53, // WGL_NV_vertex_array_range
            54, // WGL_NV_video_capture
            55, // WGL_NV_video_output
            56, // WGL_OML_sync_control
        0xFFFF
    };
    const char *extensions;

    if(context->GetExtensionsStringEXT == NULL && context->GetExtensionsStringARB == NULL)
        return 0;

    if(context->GetExtensionsStringARB == NULL || hdc == INVALID_HANDLE_VALUE)
        extensions = context->GetExtensionsStringEXT();
    else
        extensions = context->GetExtensionsStringARB(hdc);

    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(extIdx) - 1; ++i)
        context->extArray[extIdx[i]] = glad_wgl_has_extension(extensions, glad_ext_names[extIdx[i]]);

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
