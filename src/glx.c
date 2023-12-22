/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glx.h>

#ifdef __linux__
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
    "glXBindChannelToWindowSGIX", // 0
    "glXBindHyperpipeSGIX", // 1
    "glXBindSwapBarrierNV", // 2
    "glXBindSwapBarrierSGIX", // 3
    "glXBindTexImageEXT", // 4
    "glXBindVideoCaptureDeviceNV", // 5
    "glXBindVideoDeviceNV", // 6
    "glXBindVideoImageNV", // 7
    "glXBlitContextFramebufferAMD", // 8
    "glXChannelRectSGIX", // 9
    "glXChannelRectSyncSGIX", // 10
    "glXChooseFBConfig", // 11
    "glXChooseFBConfigSGIX", // 12
    "glXChooseVisual", // 13
    "glXCopyBufferSubDataNV", // 14
    "glXCopyContext", // 15
    "glXCopyImageSubDataNV", // 16
    "glXCopySubBufferMESA", // 17
    "glXCreateAssociatedContextAMD", // 18
    "glXCreateAssociatedContextAttribsAMD", // 19
    "glXCreateContext", // 20
    "glXCreateContextAttribsARB", // 21
    "glXCreateContextWithConfigSGIX", // 22
    "glXCreateGLXPbufferSGIX", // 23
    "glXCreateGLXPixmap", // 24
    "glXCreateGLXPixmapMESA", // 25
    "glXCreateGLXPixmapWithConfigSGIX", // 26
    "glXCreateNewContext", // 27
    "glXCreatePbuffer", // 28
    "glXCreatePixmap", // 29
    "glXCreateWindow", // 30
    "glXCushionSGI", // 31
    "glXDelayBeforeSwapNV", // 32
    "glXDeleteAssociatedContextAMD", // 33
    "glXDestroyContext", // 34
    "glXDestroyGLXPbufferSGIX", // 35
    "glXDestroyGLXPixmap", // 36
    "glXDestroyHyperpipeConfigSGIX", // 37
    "glXDestroyPbuffer", // 38
    "glXDestroyPixmap", // 39
    "glXDestroyWindow", // 40
    "glXEnumerateVideoCaptureDevicesNV", // 41
    "glXEnumerateVideoDevicesNV", // 42
    "glXFreeContextEXT", // 43
    "glXGetAGPOffsetMESA", // 44
    "glXGetClientString", // 45
    "glXGetConfig", // 46
    "glXGetContextGPUIDAMD", // 47
    "glXGetContextIDEXT", // 48
    "glXGetCurrentAssociatedContextAMD", // 49
    "glXGetCurrentContext", // 50
    "glXGetCurrentDisplay", // 51
    "glXGetCurrentDisplayEXT", // 52
    "glXGetCurrentDrawable", // 53
    "glXGetCurrentReadDrawable", // 54
    "glXGetCurrentReadDrawableSGI", // 55
    "glXGetFBConfigAttrib", // 56
    "glXGetFBConfigAttribSGIX", // 57
    "glXGetFBConfigFromVisualSGIX", // 58
    "glXGetFBConfigs", // 59
    "glXGetGPUIDsAMD", // 60
    "glXGetGPUInfoAMD", // 61
    "glXGetMscRateOML", // 62
    "glXGetProcAddress", // 63
    "glXGetProcAddressARB", // 64
    "glXGetSelectedEvent", // 65
    "glXGetSelectedEventSGIX", // 66
    "glXGetSwapIntervalMESA", // 67
    "glXGetSyncValuesOML", // 68
    "glXGetTransparentIndexSUN", // 69
    "glXGetVideoDeviceNV", // 70
    "glXGetVideoInfoNV", // 71
    "glXGetVideoSyncSGI", // 72
    "glXGetVisualFromFBConfig", // 73
    "glXGetVisualFromFBConfigSGIX", // 74
    "glXHyperpipeAttribSGIX", // 75
    "glXHyperpipeConfigSGIX", // 76
    "glXImportContextEXT", // 77
    "glXIsDirect", // 78
    "glXJoinSwapGroupNV", // 79
    "glXJoinSwapGroupSGIX", // 80
    "glXLockVideoCaptureDeviceNV", // 81
    "glXMakeAssociatedContextCurrentAMD", // 82
    "glXMakeContextCurrent", // 83
    "glXMakeCurrent", // 84
    "glXMakeCurrentReadSGI", // 85
    "glXNamedCopyBufferSubDataNV", // 86
    "glXQueryChannelDeltasSGIX", // 87
    "glXQueryChannelRectSGIX", // 88
    "glXQueryContext", // 89
    "glXQueryContextInfoEXT", // 90
    "glXQueryCurrentRendererIntegerMESA", // 91
    "glXQueryCurrentRendererStringMESA", // 92
    "glXQueryDrawable", // 93
    "glXQueryExtension", // 94
    "glXQueryExtensionsString", // 95
    "glXQueryFrameCountNV", // 96
    "glXQueryGLXPbufferSGIX", // 97
    "glXQueryHyperpipeAttribSGIX", // 98
    "glXQueryHyperpipeBestAttribSGIX", // 99
    "glXQueryHyperpipeConfigSGIX", // 100
    "glXQueryHyperpipeNetworkSGIX", // 101
    "glXQueryMaxSwapBarriersSGIX", // 102
    "glXQueryMaxSwapGroupsNV", // 103
    "glXQueryRendererIntegerMESA", // 104
    "glXQueryRendererStringMESA", // 105
    "glXQueryServerString", // 106
    "glXQuerySwapGroupNV", // 107
    "glXQueryVersion", // 108
    "glXQueryVideoCaptureDeviceNV", // 109
    "glXReleaseBuffersMESA", // 110
    "glXReleaseTexImageEXT", // 111
    "glXReleaseVideoCaptureDeviceNV", // 112
    "glXReleaseVideoDeviceNV", // 113
    "glXReleaseVideoImageNV", // 114
    "glXResetFrameCountNV", // 115
    "glXSelectEvent", // 116
    "glXSelectEventSGIX", // 117
    "glXSendPbufferToVideoNV", // 118
    "glXSet3DfxModeMESA", // 119
    "glXSwapBuffers", // 120
    "glXSwapBuffersMscOML", // 121
    "glXSwapIntervalEXT", // 122
    "glXSwapIntervalMESA", // 123
    "glXSwapIntervalSGI", // 124
    "glXUseXFont", // 125
    "glXWaitForMscOML", // 126
    "glXWaitForSbcOML", // 127
    "glXWaitGL", // 128
    "glXWaitVideoSyncSGI", // 129
    "glXWaitX" // 130
};

static const char *glad_ext_names[] = {
    "GLX_3DFX_multisample", // 0
    "GLX_AMD_gpu_association", // 1
    "GLX_ARB_context_flush_control", // 2
    "GLX_ARB_create_context", // 3
    "GLX_ARB_create_context_no_error", // 4
    "GLX_ARB_create_context_profile", // 5
    "GLX_ARB_create_context_robustness", // 6
    "GLX_ARB_fbconfig_float", // 7
    "GLX_ARB_framebuffer_sRGB", // 8
    "GLX_ARB_get_proc_address", // 9
    "GLX_ARB_multisample", // 10
    "GLX_ARB_robustness_application_isolation", // 11
    "GLX_ARB_robustness_share_group_isolation", // 12
    "GLX_ARB_vertex_buffer_object", // 13
    "GLX_EXT_buffer_age", // 14
    "GLX_EXT_context_priority", // 15
    "GLX_EXT_create_context_es2_profile", // 16
    "GLX_EXT_create_context_es_profile", // 17
    "GLX_EXT_fbconfig_packed_float", // 18
    "GLX_EXT_framebuffer_sRGB", // 19
    "GLX_EXT_get_drawable_type", // 20
    "GLX_EXT_import_context", // 21
    "GLX_EXT_libglvnd", // 22
    "GLX_EXT_no_config_context", // 23
    "GLX_EXT_stereo_tree", // 24
    "GLX_EXT_swap_control", // 25
    "GLX_EXT_swap_control_tear", // 26
    "GLX_EXT_texture_from_pixmap", // 27
    "GLX_EXT_visual_info", // 28
    "GLX_EXT_visual_rating", // 29
    "GLX_INTEL_swap_event", // 30
    "GLX_MESA_agp_offset", // 31
    "GLX_MESA_copy_sub_buffer", // 32
    "GLX_MESA_pixmap_colormap", // 33
    "GLX_MESA_query_renderer", // 34
    "GLX_MESA_release_buffers", // 35
    "GLX_MESA_set_3dfx_mode", // 36
    "GLX_MESA_swap_control", // 37
    "GLX_NV_copy_buffer", // 38
    "GLX_NV_copy_image", // 39
    "GLX_NV_delay_before_swap", // 40
    "GLX_NV_float_buffer", // 41
    "GLX_NV_multigpu_context", // 42
    "GLX_NV_multisample_coverage", // 43
    "GLX_NV_present_video", // 44
    "GLX_NV_robustness_video_memory_purge", // 45
    "GLX_NV_swap_group", // 46
    "GLX_NV_video_capture", // 47
    "GLX_NV_video_out", // 48
    "GLX_OML_swap_method", // 49
    "GLX_OML_sync_control", // 50
    "GLX_SGIS_blended_overlay", // 51
    "GLX_SGIS_multisample", // 52
    "GLX_SGIS_shared_multisample", // 53
    "GLX_SGIX_fbconfig", // 54
    "GLX_SGIX_hyperpipe", // 55
    "GLX_SGIX_pbuffer", // 56
    "GLX_SGIX_swap_barrier", // 57
    "GLX_SGIX_swap_group", // 58
    "GLX_SGIX_video_resize", // 59
    "GLX_SGIX_visual_select_group", // 60
    "GLX_SGI_cushion", // 61
    "GLX_SGI_make_current_read", // 62
    "GLX_SGI_swap_control", // 63
    "GLX_SGI_video_sync", // 64
    "GLX_SUN_get_transparent_index" // 65
};

#ifdef __cplusplus
GladGLXContext glad_glx_context = {};
#else
GladGLXContext glad_glx_context = { 0 };
#endif

static void glad_glx_load_GLX_VERSION_1_0(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_0) return;
    static const uint16_t s_pfnIdx[] = {
           13, // glXChooseVisual
           15, // glXCopyContext
           20, // glXCreateContext
           24, // glXCreateGLXPixmap
           34, // glXDestroyContext
           36, // glXDestroyGLXPixmap
           46, // glXGetConfig
           50, // glXGetCurrentContext
           53, // glXGetCurrentDrawable
           78, // glXIsDirect
           84, // glXMakeCurrent
           94, // glXQueryExtension
          108, // glXQueryVersion
          120, // glXSwapBuffers
          125, // glXUseXFont
          128, // glXWaitGL
          130  // glXWaitX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_VERSION_1_1(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_1) return;
    static const uint16_t s_pfnIdx[] = {
           45, // glXGetClientString
           95, // glXQueryExtensionsString
          106  // glXQueryServerString
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_VERSION_1_2(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_2) return;
    static const uint16_t s_pfnIdx[] = {
           51  // glXGetCurrentDisplay
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_VERSION_1_3(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_3) return;
    static const uint16_t s_pfnIdx[] = {
           11, // glXChooseFBConfig
           27, // glXCreateNewContext
           28, // glXCreatePbuffer
           29, // glXCreatePixmap
           30, // glXCreateWindow
           38, // glXDestroyPbuffer
           39, // glXDestroyPixmap
           40, // glXDestroyWindow
           54, // glXGetCurrentReadDrawable
           56, // glXGetFBConfigAttrib
           59, // glXGetFBConfigs
           65, // glXGetSelectedEvent
           73, // glXGetVisualFromFBConfig
           83, // glXMakeContextCurrent
           89, // glXQueryContext
           93, // glXQueryDrawable
          116  // glXSelectEvent
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_VERSION_1_4(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_4) return;
    static const uint16_t s_pfnIdx[] = {
           63  // glXGetProcAddress
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_AMD_gpu_association(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_gpu_association) return;
    static const uint16_t s_pfnIdx[] = {
            8, // glXBlitContextFramebufferAMD
           18, // glXCreateAssociatedContextAMD
           19, // glXCreateAssociatedContextAttribsAMD
           33, // glXDeleteAssociatedContextAMD
           47, // glXGetContextGPUIDAMD
           49, // glXGetCurrentAssociatedContextAMD
           60, // glXGetGPUIDsAMD
           61, // glXGetGPUInfoAMD
           82  // glXMakeAssociatedContextCurrentAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_ARB_create_context(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_create_context) return;
    static const uint16_t s_pfnIdx[] = {
           21  // glXCreateContextAttribsARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_ARB_get_proc_address(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_get_proc_address) return;
    static const uint16_t s_pfnIdx[] = {
           64  // glXGetProcAddressARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_EXT_import_context(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_import_context) return;
    static const uint16_t s_pfnIdx[] = {
           43, // glXFreeContextEXT
           48, // glXGetContextIDEXT
           52, // glXGetCurrentDisplayEXT
           77, // glXImportContextEXT
           90  // glXQueryContextInfoEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_EXT_swap_control(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_swap_control) return;
    static const uint16_t s_pfnIdx[] = {
          122  // glXSwapIntervalEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_EXT_texture_from_pixmap(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_texture_from_pixmap) return;
    static const uint16_t s_pfnIdx[] = {
            4, // glXBindTexImageEXT
          111  // glXReleaseTexImageEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_MESA_agp_offset(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_agp_offset) return;
    static const uint16_t s_pfnIdx[] = {
           44  // glXGetAGPOffsetMESA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_MESA_copy_sub_buffer(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_copy_sub_buffer) return;
    static const uint16_t s_pfnIdx[] = {
           17  // glXCopySubBufferMESA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_MESA_pixmap_colormap(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_pixmap_colormap) return;
    static const uint16_t s_pfnIdx[] = {
           25  // glXCreateGLXPixmapMESA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_MESA_query_renderer(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_query_renderer) return;
    static const uint16_t s_pfnIdx[] = {
           91, // glXQueryCurrentRendererIntegerMESA
           92, // glXQueryCurrentRendererStringMESA
          104, // glXQueryRendererIntegerMESA
          105  // glXQueryRendererStringMESA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_MESA_release_buffers(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_release_buffers) return;
    static const uint16_t s_pfnIdx[] = {
          110  // glXReleaseBuffersMESA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_MESA_set_3dfx_mode(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_set_3dfx_mode) return;
    static const uint16_t s_pfnIdx[] = {
          119  // glXSet3DfxModeMESA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_MESA_swap_control(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_swap_control) return;
    static const uint16_t s_pfnIdx[] = {
           67, // glXGetSwapIntervalMESA
          123  // glXSwapIntervalMESA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_NV_copy_buffer(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_copy_buffer) return;
    static const uint16_t s_pfnIdx[] = {
           14, // glXCopyBufferSubDataNV
           86  // glXNamedCopyBufferSubDataNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_NV_copy_image(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_copy_image) return;
    static const uint16_t s_pfnIdx[] = {
           16  // glXCopyImageSubDataNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_NV_delay_before_swap(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_delay_before_swap) return;
    static const uint16_t s_pfnIdx[] = {
           32  // glXDelayBeforeSwapNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_NV_present_video(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_present_video) return;
    static const uint16_t s_pfnIdx[] = {
            6, // glXBindVideoDeviceNV
           42  // glXEnumerateVideoDevicesNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_NV_swap_group(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_swap_group) return;
    static const uint16_t s_pfnIdx[] = {
            2, // glXBindSwapBarrierNV
           79, // glXJoinSwapGroupNV
           96, // glXQueryFrameCountNV
          103, // glXQueryMaxSwapGroupsNV
          107, // glXQuerySwapGroupNV
          115  // glXResetFrameCountNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_NV_video_capture(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_video_capture) return;
    static const uint16_t s_pfnIdx[] = {
            5, // glXBindVideoCaptureDeviceNV
           41, // glXEnumerateVideoCaptureDevicesNV
           81, // glXLockVideoCaptureDeviceNV
          109, // glXQueryVideoCaptureDeviceNV
          112  // glXReleaseVideoCaptureDeviceNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_NV_video_out(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_video_out) return;
    static const uint16_t s_pfnIdx[] = {
            7, // glXBindVideoImageNV
           70, // glXGetVideoDeviceNV
           71, // glXGetVideoInfoNV
          113, // glXReleaseVideoDeviceNV
          114, // glXReleaseVideoImageNV
          118  // glXSendPbufferToVideoNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_OML_sync_control(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OML_sync_control) return;
    static const uint16_t s_pfnIdx[] = {
           62, // glXGetMscRateOML
           68, // glXGetSyncValuesOML
          121, // glXSwapBuffersMscOML
          126, // glXWaitForMscOML
          127  // glXWaitForSbcOML
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_SGIX_fbconfig(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_fbconfig) return;
    static const uint16_t s_pfnIdx[] = {
           12, // glXChooseFBConfigSGIX
           22, // glXCreateContextWithConfigSGIX
           26, // glXCreateGLXPixmapWithConfigSGIX
           57, // glXGetFBConfigAttribSGIX
           58, // glXGetFBConfigFromVisualSGIX
           74  // glXGetVisualFromFBConfigSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_SGIX_hyperpipe(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_hyperpipe) return;
    static const uint16_t s_pfnIdx[] = {
            1, // glXBindHyperpipeSGIX
           37, // glXDestroyHyperpipeConfigSGIX
           75, // glXHyperpipeAttribSGIX
           76, // glXHyperpipeConfigSGIX
           98, // glXQueryHyperpipeAttribSGIX
           99, // glXQueryHyperpipeBestAttribSGIX
          100, // glXQueryHyperpipeConfigSGIX
          101  // glXQueryHyperpipeNetworkSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_SGIX_pbuffer(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_pbuffer) return;
    static const uint16_t s_pfnIdx[] = {
           23, // glXCreateGLXPbufferSGIX
           35, // glXDestroyGLXPbufferSGIX
           66, // glXGetSelectedEventSGIX
           97, // glXQueryGLXPbufferSGIX
          117  // glXSelectEventSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_SGIX_swap_barrier(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_swap_barrier) return;
    static const uint16_t s_pfnIdx[] = {
            3, // glXBindSwapBarrierSGIX
          102  // glXQueryMaxSwapBarriersSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_SGIX_swap_group(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_swap_group) return;
    static const uint16_t s_pfnIdx[] = {
           80  // glXJoinSwapGroupSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_SGIX_video_resize(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_video_resize) return;
    static const uint16_t s_pfnIdx[] = {
            0, // glXBindChannelToWindowSGIX
            9, // glXChannelRectSGIX
           10, // glXChannelRectSyncSGIX
           87, // glXQueryChannelDeltasSGIX
           88  // glXQueryChannelRectSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_SGI_cushion(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGI_cushion) return;
    static const uint16_t s_pfnIdx[] = {
           31  // glXCushionSGI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_SGI_make_current_read(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGI_make_current_read) return;
    static const uint16_t s_pfnIdx[] = {
           55, // glXGetCurrentReadDrawableSGI
           85  // glXMakeCurrentReadSGI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_SGI_swap_control(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGI_swap_control) return;
    static const uint16_t s_pfnIdx[] = {
          124  // glXSwapIntervalSGI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_SGI_video_sync(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGI_video_sync) return;
    static const uint16_t s_pfnIdx[] = {
           72, // glXGetVideoSyncSGI
          129  // glXWaitVideoSyncSGI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_load_GLX_SUN_get_transparent_index(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SUN_get_transparent_index) return;
    static const uint16_t s_pfnIdx[] = {
           69  // glXGetTransparentIndexSUN
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_glx_resolve_aliases(GladGLXContext *context) {
    static const GladAliasPair_t s_aliases[] = {
        { 0xFFFF, 0xFFFF }
    };

    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_aliases) - 1; ++i) {
        const GladAliasPair_t *pAlias = &s_aliases[i];
        if (context->pfnArray[pAlias->first] == NULL && context->pfnArray[pAlias->second] != NULL) {
            context->pfnArray[pAlias->first] = context->pfnArray[pAlias->second];
        }
    }
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
#ifdef GLX_VERSION_1_1
    static uint16_t extIdx[] = {
             0, // GLX_3DFX_multisample
             1, // GLX_AMD_gpu_association
             2, // GLX_ARB_context_flush_control
             3, // GLX_ARB_create_context
             4, // GLX_ARB_create_context_no_error
             5, // GLX_ARB_create_context_profile
             6, // GLX_ARB_create_context_robustness
             7, // GLX_ARB_fbconfig_float
             8, // GLX_ARB_framebuffer_sRGB
             9, // GLX_ARB_get_proc_address
            10, // GLX_ARB_multisample
            11, // GLX_ARB_robustness_application_isolation
            12, // GLX_ARB_robustness_share_group_isolation
            13, // GLX_ARB_vertex_buffer_object
            14, // GLX_EXT_buffer_age
            15, // GLX_EXT_context_priority
            16, // GLX_EXT_create_context_es2_profile
            17, // GLX_EXT_create_context_es_profile
            18, // GLX_EXT_fbconfig_packed_float
            19, // GLX_EXT_framebuffer_sRGB
            20, // GLX_EXT_get_drawable_type
            21, // GLX_EXT_import_context
            22, // GLX_EXT_libglvnd
            23, // GLX_EXT_no_config_context
            24, // GLX_EXT_stereo_tree
            25, // GLX_EXT_swap_control
            26, // GLX_EXT_swap_control_tear
            27, // GLX_EXT_texture_from_pixmap
            28, // GLX_EXT_visual_info
            29, // GLX_EXT_visual_rating
            30, // GLX_INTEL_swap_event
            31, // GLX_MESA_agp_offset
            32, // GLX_MESA_copy_sub_buffer
            33, // GLX_MESA_pixmap_colormap
            34, // GLX_MESA_query_renderer
            35, // GLX_MESA_release_buffers
            36, // GLX_MESA_set_3dfx_mode
            37, // GLX_MESA_swap_control
            38, // GLX_NV_copy_buffer
            39, // GLX_NV_copy_image
            40, // GLX_NV_delay_before_swap
            41, // GLX_NV_float_buffer
            42, // GLX_NV_multigpu_context
            43, // GLX_NV_multisample_coverage
            44, // GLX_NV_present_video
            45, // GLX_NV_robustness_video_memory_purge
            46, // GLX_NV_swap_group
            47, // GLX_NV_video_capture
            48, // GLX_NV_video_out
            49, // GLX_OML_swap_method
            50, // GLX_OML_sync_control
            51, // GLX_SGIS_blended_overlay
            52, // GLX_SGIS_multisample
            53, // GLX_SGIS_shared_multisample
            54, // GLX_SGIX_fbconfig
            55, // GLX_SGIX_hyperpipe
            56, // GLX_SGIX_pbuffer
            57, // GLX_SGIX_swap_barrier
            58, // GLX_SGIX_swap_group
            59, // GLX_SGIX_video_resize
            60, // GLX_SGIX_visual_select_group
            61, // GLX_SGI_cushion
            62, // GLX_SGI_make_current_read
            63, // GLX_SGI_swap_control
            64, // GLX_SGI_video_sync
            65, // GLX_SUN_get_transparent_index
        0xFFFF
    };
    const char *extensions;

    if (context->QueryExtensionsString == NULL) {
        return -2;
    }

    extensions = context->QueryExtensionsString(display, screen);

    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(extIdx) - 1; ++i)
        context->extArray[extIdx[i]] = glad_glx_has_extension(extensions, glad_ext_names[extIdx[i]]);
#endif
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

int gladLoadGLXContextUserPtr(GladGLXContext *context, Display *display, int screen, GLADuserptrloadfunc load, void *userptr) {
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
    glad_glx_load_GLX_AMD_gpu_association(context, load, userptr);
    glad_glx_load_GLX_ARB_create_context(context, load, userptr);
    glad_glx_load_GLX_ARB_get_proc_address(context, load, userptr);
    glad_glx_load_GLX_EXT_import_context(context, load, userptr);
    glad_glx_load_GLX_EXT_swap_control(context, load, userptr);
    glad_glx_load_GLX_EXT_texture_from_pixmap(context, load, userptr);
    glad_glx_load_GLX_MESA_agp_offset(context, load, userptr);
    glad_glx_load_GLX_MESA_copy_sub_buffer(context, load, userptr);
    glad_glx_load_GLX_MESA_pixmap_colormap(context, load, userptr);
    glad_glx_load_GLX_MESA_query_renderer(context, load, userptr);
    glad_glx_load_GLX_MESA_release_buffers(context, load, userptr);
    glad_glx_load_GLX_MESA_set_3dfx_mode(context, load, userptr);
    glad_glx_load_GLX_MESA_swap_control(context, load, userptr);
    glad_glx_load_GLX_NV_copy_buffer(context, load, userptr);
    glad_glx_load_GLX_NV_copy_image(context, load, userptr);
    glad_glx_load_GLX_NV_delay_before_swap(context, load, userptr);
    glad_glx_load_GLX_NV_present_video(context, load, userptr);
    glad_glx_load_GLX_NV_swap_group(context, load, userptr);
    glad_glx_load_GLX_NV_video_capture(context, load, userptr);
    glad_glx_load_GLX_NV_video_out(context, load, userptr);
    glad_glx_load_GLX_OML_sync_control(context, load, userptr);
    glad_glx_load_GLX_SGIX_fbconfig(context, load, userptr);
    glad_glx_load_GLX_SGIX_hyperpipe(context, load, userptr);
    glad_glx_load_GLX_SGIX_pbuffer(context, load, userptr);
    glad_glx_load_GLX_SGIX_swap_barrier(context, load, userptr);
    glad_glx_load_GLX_SGIX_swap_group(context, load, userptr);
    glad_glx_load_GLX_SGIX_video_resize(context, load, userptr);
    glad_glx_load_GLX_SGI_cushion(context, load, userptr);
    glad_glx_load_GLX_SGI_make_current_read(context, load, userptr);
    glad_glx_load_GLX_SGI_swap_control(context, load, userptr);
    glad_glx_load_GLX_SGI_video_sync(context, load, userptr);
    glad_glx_load_GLX_SUN_get_transparent_index(context, load, userptr);

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
