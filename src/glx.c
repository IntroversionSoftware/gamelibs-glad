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
    /*    0 */ "glXBindChannelToWindowSGIX",
    /*    1 */ "glXBindHyperpipeSGIX",
    /*    2 */ "glXBindSwapBarrierNV",
    /*    3 */ "glXBindSwapBarrierSGIX",
    /*    4 */ "glXBindTexImageEXT",
    /*    5 */ "glXBindVideoCaptureDeviceNV",
    /*    6 */ "glXBindVideoDeviceNV",
    /*    7 */ "glXBindVideoImageNV",
    /*    8 */ "glXBlitContextFramebufferAMD",
    /*    9 */ "glXChannelRectSGIX",
    /*   10 */ "glXChannelRectSyncSGIX",
    /*   11 */ "glXChooseFBConfig",
    /*   12 */ "glXChooseFBConfigSGIX",
    /*   13 */ "glXChooseVisual",
    /*   14 */ "glXCopyBufferSubDataNV",
    /*   15 */ "glXCopyContext",
    /*   16 */ "glXCopyImageSubDataNV",
    /*   17 */ "glXCopySubBufferMESA",
    /*   18 */ "glXCreateAssociatedContextAMD",
    /*   19 */ "glXCreateAssociatedContextAttribsAMD",
    /*   20 */ "glXCreateContext",
    /*   21 */ "glXCreateContextAttribsARB",
    /*   22 */ "glXCreateContextWithConfigSGIX",
    /*   23 */ "glXCreateGLXPbufferSGIX",
    /*   24 */ "glXCreateGLXPixmap",
    /*   25 */ "glXCreateGLXPixmapMESA",
    /*   26 */ "glXCreateGLXPixmapWithConfigSGIX",
    /*   27 */ "glXCreateNewContext",
    /*   28 */ "glXCreatePbuffer",
    /*   29 */ "glXCreatePixmap",
    /*   30 */ "glXCreateWindow",
    /*   31 */ "glXCushionSGI",
    /*   32 */ "glXDelayBeforeSwapNV",
    /*   33 */ "glXDeleteAssociatedContextAMD",
    /*   34 */ "glXDestroyContext",
    /*   35 */ "glXDestroyGLXPbufferSGIX",
    /*   36 */ "glXDestroyGLXPixmap",
    /*   37 */ "glXDestroyHyperpipeConfigSGIX",
    /*   38 */ "glXDestroyPbuffer",
    /*   39 */ "glXDestroyPixmap",
    /*   40 */ "glXDestroyWindow",
    /*   41 */ "glXEnumerateVideoCaptureDevicesNV",
    /*   42 */ "glXEnumerateVideoDevicesNV",
    /*   43 */ "glXFreeContextEXT",
    /*   44 */ "glXGetAGPOffsetMESA",
    /*   45 */ "glXGetClientString",
    /*   46 */ "glXGetConfig",
    /*   47 */ "glXGetContextGPUIDAMD",
    /*   48 */ "glXGetContextIDEXT",
    /*   49 */ "glXGetCurrentAssociatedContextAMD",
    /*   50 */ "glXGetCurrentContext",
    /*   51 */ "glXGetCurrentDisplay",
    /*   52 */ "glXGetCurrentDisplayEXT",
    /*   53 */ "glXGetCurrentDrawable",
    /*   54 */ "glXGetCurrentReadDrawable",
    /*   55 */ "glXGetCurrentReadDrawableSGI",
    /*   56 */ "glXGetFBConfigAttrib",
    /*   57 */ "glXGetFBConfigAttribSGIX",
    /*   58 */ "glXGetFBConfigFromVisualSGIX",
    /*   59 */ "glXGetFBConfigs",
    /*   60 */ "glXGetGPUIDsAMD",
    /*   61 */ "glXGetGPUInfoAMD",
    /*   62 */ "glXGetMscRateOML",
    /*   63 */ "glXGetProcAddress",
    /*   64 */ "glXGetProcAddressARB",
    /*   65 */ "glXGetSelectedEvent",
    /*   66 */ "glXGetSelectedEventSGIX",
    /*   67 */ "glXGetSwapIntervalMESA",
    /*   68 */ "glXGetSyncValuesOML",
    /*   69 */ "glXGetTransparentIndexSUN",
    /*   70 */ "glXGetVideoDeviceNV",
    /*   71 */ "glXGetVideoInfoNV",
    /*   72 */ "glXGetVideoSyncSGI",
    /*   73 */ "glXGetVisualFromFBConfig",
    /*   74 */ "glXGetVisualFromFBConfigSGIX",
    /*   75 */ "glXHyperpipeAttribSGIX",
    /*   76 */ "glXHyperpipeConfigSGIX",
    /*   77 */ "glXImportContextEXT",
    /*   78 */ "glXIsDirect",
    /*   79 */ "glXJoinSwapGroupNV",
    /*   80 */ "glXJoinSwapGroupSGIX",
    /*   81 */ "glXLockVideoCaptureDeviceNV",
    /*   82 */ "glXMakeAssociatedContextCurrentAMD",
    /*   83 */ "glXMakeContextCurrent",
    /*   84 */ "glXMakeCurrent",
    /*   85 */ "glXMakeCurrentReadSGI",
    /*   86 */ "glXNamedCopyBufferSubDataNV",
    /*   87 */ "glXQueryChannelDeltasSGIX",
    /*   88 */ "glXQueryChannelRectSGIX",
    /*   89 */ "glXQueryContext",
    /*   90 */ "glXQueryContextInfoEXT",
    /*   91 */ "glXQueryCurrentRendererIntegerMESA",
    /*   92 */ "glXQueryCurrentRendererStringMESA",
    /*   93 */ "glXQueryDrawable",
    /*   94 */ "glXQueryExtension",
    /*   95 */ "glXQueryExtensionsString",
    /*   96 */ "glXQueryFrameCountNV",
    /*   97 */ "glXQueryGLXPbufferSGIX",
    /*   98 */ "glXQueryHyperpipeAttribSGIX",
    /*   99 */ "glXQueryHyperpipeBestAttribSGIX",
    /*  100 */ "glXQueryHyperpipeConfigSGIX",
    /*  101 */ "glXQueryHyperpipeNetworkSGIX",
    /*  102 */ "glXQueryMaxSwapBarriersSGIX",
    /*  103 */ "glXQueryMaxSwapGroupsNV",
    /*  104 */ "glXQueryRendererIntegerMESA",
    /*  105 */ "glXQueryRendererStringMESA",
    /*  106 */ "glXQueryServerString",
    /*  107 */ "glXQuerySwapGroupNV",
    /*  108 */ "glXQueryVersion",
    /*  109 */ "glXQueryVideoCaptureDeviceNV",
    /*  110 */ "glXReleaseBuffersMESA",
    /*  111 */ "glXReleaseTexImageEXT",
    /*  112 */ "glXReleaseVideoCaptureDeviceNV",
    /*  113 */ "glXReleaseVideoDeviceNV",
    /*  114 */ "glXReleaseVideoImageNV",
    /*  115 */ "glXResetFrameCountNV",
    /*  116 */ "glXSelectEvent",
    /*  117 */ "glXSelectEventSGIX",
    /*  118 */ "glXSendPbufferToVideoNV",
    /*  119 */ "glXSet3DfxModeMESA",
    /*  120 */ "glXSwapBuffers",
    /*  121 */ "glXSwapBuffersMscOML",
    /*  122 */ "glXSwapIntervalEXT",
    /*  123 */ "glXSwapIntervalMESA",
    /*  124 */ "glXSwapIntervalSGI",
    /*  125 */ "glXUseXFont",
    /*  126 */ "glXWaitForMscOML",
    /*  127 */ "glXWaitForSbcOML",
    /*  128 */ "glXWaitGL",
    /*  129 */ "glXWaitVideoSyncSGI",
    /*  130 */ "glXWaitX"
};

static const char *GLAD_GLX_ext_names[] = {
    /*    0 */ "GLX_3DFX_multisample",
    /*    1 */ "GLX_AMD_gpu_association",
    /*    2 */ "GLX_ARB_context_flush_control",
    /*    3 */ "GLX_ARB_create_context",
    /*    4 */ "GLX_ARB_create_context_no_error",
    /*    5 */ "GLX_ARB_create_context_profile",
    /*    6 */ "GLX_ARB_create_context_robustness",
    /*    7 */ "GLX_ARB_fbconfig_float",
    /*    8 */ "GLX_ARB_framebuffer_sRGB",
    /*    9 */ "GLX_ARB_get_proc_address",
    /*   10 */ "GLX_ARB_multisample",
    /*   11 */ "GLX_ARB_robustness_application_isolation",
    /*   12 */ "GLX_ARB_robustness_share_group_isolation",
    /*   13 */ "GLX_ARB_vertex_buffer_object",
    /*   14 */ "GLX_EXT_buffer_age",
    /*   15 */ "GLX_EXT_context_priority",
    /*   16 */ "GLX_EXT_create_context_es2_profile",
    /*   17 */ "GLX_EXT_create_context_es_profile",
    /*   18 */ "GLX_EXT_fbconfig_packed_float",
    /*   19 */ "GLX_EXT_framebuffer_sRGB",
    /*   20 */ "GLX_EXT_get_drawable_type",
    /*   21 */ "GLX_EXT_import_context",
    /*   22 */ "GLX_EXT_libglvnd",
    /*   23 */ "GLX_EXT_no_config_context",
    /*   24 */ "GLX_EXT_stereo_tree",
    /*   25 */ "GLX_EXT_swap_control",
    /*   26 */ "GLX_EXT_swap_control_tear",
    /*   27 */ "GLX_EXT_texture_from_pixmap",
    /*   28 */ "GLX_EXT_visual_info",
    /*   29 */ "GLX_EXT_visual_rating",
    /*   30 */ "GLX_INTEL_swap_event",
    /*   31 */ "GLX_MESA_agp_offset",
    /*   32 */ "GLX_MESA_copy_sub_buffer",
    /*   33 */ "GLX_MESA_pixmap_colormap",
    /*   34 */ "GLX_MESA_query_renderer",
    /*   35 */ "GLX_MESA_release_buffers",
    /*   36 */ "GLX_MESA_set_3dfx_mode",
    /*   37 */ "GLX_MESA_swap_control",
    /*   38 */ "GLX_NV_copy_buffer",
    /*   39 */ "GLX_NV_copy_image",
    /*   40 */ "GLX_NV_delay_before_swap",
    /*   41 */ "GLX_NV_float_buffer",
    /*   42 */ "GLX_NV_multigpu_context",
    /*   43 */ "GLX_NV_multisample_coverage",
    /*   44 */ "GLX_NV_present_video",
    /*   45 */ "GLX_NV_robustness_video_memory_purge",
    /*   46 */ "GLX_NV_swap_group",
    /*   47 */ "GLX_NV_video_capture",
    /*   48 */ "GLX_NV_video_out",
    /*   49 */ "GLX_OML_swap_method",
    /*   50 */ "GLX_OML_sync_control",
    /*   51 */ "GLX_SGIS_blended_overlay",
    /*   52 */ "GLX_SGIS_multisample",
    /*   53 */ "GLX_SGIS_shared_multisample",
    /*   54 */ "GLX_SGIX_fbconfig",
    /*   55 */ "GLX_SGIX_hyperpipe",
    /*   56 */ "GLX_SGIX_pbuffer",
    /*   57 */ "GLX_SGIX_swap_barrier",
    /*   58 */ "GLX_SGIX_swap_group",
    /*   59 */ "GLX_SGIX_video_resize",
    /*   60 */ "GLX_SGIX_visual_select_group",
    /*   61 */ "GLX_SGI_cushion",
    /*   62 */ "GLX_SGI_make_current_read",
    /*   63 */ "GLX_SGI_swap_control",
    /*   64 */ "GLX_SGI_video_sync",
    /*   65 */ "GLX_SUN_get_transparent_index"
};

#ifdef __cplusplus
GladGLXContext glad_glx_context = {};
#else
GladGLXContext glad_glx_context = { 0 };
#endif

static void glad_glx_load_GLX_VERSION_1_0(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          13, /* glXChooseVisual */
          15, /* glXCopyContext */
          20, /* glXCreateContext */
          24, /* glXCreateGLXPixmap */
          34, /* glXDestroyContext */
          36, /* glXDestroyGLXPixmap */
          46, /* glXGetConfig */
          50, /* glXGetCurrentContext */
          53, /* glXGetCurrentDrawable */
          78, /* glXIsDirect */
          84, /* glXMakeCurrent */
          94, /* glXQueryExtension */
         108, /* glXQueryVersion */
         120, /* glXSwapBuffers */
         125, /* glXUseXFont */
         128, /* glXWaitGL */
         130  /* glXWaitX */
    };
    uint32_t i;
    if(!context->VERSION_1_0) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_VERSION_1_1(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          45, /* glXGetClientString */
          95, /* glXQueryExtensionsString */
         106  /* glXQueryServerString */
    };
    uint32_t i;
    if(!context->VERSION_1_1) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_VERSION_1_2(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          51  /* glXGetCurrentDisplay */
    };
    uint32_t i;
    if(!context->VERSION_1_2) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_VERSION_1_3(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          11, /* glXChooseFBConfig */
          27, /* glXCreateNewContext */
          28, /* glXCreatePbuffer */
          29, /* glXCreatePixmap */
          30, /* glXCreateWindow */
          38, /* glXDestroyPbuffer */
          39, /* glXDestroyPixmap */
          40, /* glXDestroyWindow */
          54, /* glXGetCurrentReadDrawable */
          56, /* glXGetFBConfigAttrib */
          59, /* glXGetFBConfigs */
          65, /* glXGetSelectedEvent */
          73, /* glXGetVisualFromFBConfig */
          83, /* glXMakeContextCurrent */
          89, /* glXQueryContext */
          93, /* glXQueryDrawable */
         116  /* glXSelectEvent */
    };
    uint32_t i;
    if(!context->VERSION_1_3) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_VERSION_1_4(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          63  /* glXGetProcAddress */
    };
    uint32_t i;
    if(!context->VERSION_1_4) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_AMD_gpu_association(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           8, /* glXBlitContextFramebufferAMD */
          18, /* glXCreateAssociatedContextAMD */
          19, /* glXCreateAssociatedContextAttribsAMD */
          33, /* glXDeleteAssociatedContextAMD */
          47, /* glXGetContextGPUIDAMD */
          49, /* glXGetCurrentAssociatedContextAMD */
          60, /* glXGetGPUIDsAMD */
          61, /* glXGetGPUInfoAMD */
          82  /* glXMakeAssociatedContextCurrentAMD */
    };
    uint32_t i;
    if(!context->AMD_gpu_association) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_ARB_create_context(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          21  /* glXCreateContextAttribsARB */
    };
    uint32_t i;
    if(!context->ARB_create_context) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_ARB_get_proc_address(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          64  /* glXGetProcAddressARB */
    };
    uint32_t i;
    if(!context->ARB_get_proc_address) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_EXT_import_context(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          43, /* glXFreeContextEXT */
          48, /* glXGetContextIDEXT */
          52, /* glXGetCurrentDisplayEXT */
          77, /* glXImportContextEXT */
          90  /* glXQueryContextInfoEXT */
    };
    uint32_t i;
    if(!context->EXT_import_context) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_EXT_swap_control(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         122  /* glXSwapIntervalEXT */
    };
    uint32_t i;
    if(!context->EXT_swap_control) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_EXT_texture_from_pixmap(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           4, /* glXBindTexImageEXT */
         111  /* glXReleaseTexImageEXT */
    };
    uint32_t i;
    if(!context->EXT_texture_from_pixmap) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_MESA_agp_offset(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          44  /* glXGetAGPOffsetMESA */
    };
    uint32_t i;
    if(!context->MESA_agp_offset) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_MESA_copy_sub_buffer(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          17  /* glXCopySubBufferMESA */
    };
    uint32_t i;
    if(!context->MESA_copy_sub_buffer) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_MESA_pixmap_colormap(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          25  /* glXCreateGLXPixmapMESA */
    };
    uint32_t i;
    if(!context->MESA_pixmap_colormap) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_MESA_query_renderer(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          91, /* glXQueryCurrentRendererIntegerMESA */
          92, /* glXQueryCurrentRendererStringMESA */
         104, /* glXQueryRendererIntegerMESA */
         105  /* glXQueryRendererStringMESA */
    };
    uint32_t i;
    if(!context->MESA_query_renderer) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_MESA_release_buffers(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         110  /* glXReleaseBuffersMESA */
    };
    uint32_t i;
    if(!context->MESA_release_buffers) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_MESA_set_3dfx_mode(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         119  /* glXSet3DfxModeMESA */
    };
    uint32_t i;
    if(!context->MESA_set_3dfx_mode) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_MESA_swap_control(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          67, /* glXGetSwapIntervalMESA */
         123  /* glXSwapIntervalMESA */
    };
    uint32_t i;
    if(!context->MESA_swap_control) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_NV_copy_buffer(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          14, /* glXCopyBufferSubDataNV */
          86  /* glXNamedCopyBufferSubDataNV */
    };
    uint32_t i;
    if(!context->NV_copy_buffer) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_NV_copy_image(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          16  /* glXCopyImageSubDataNV */
    };
    uint32_t i;
    if(!context->NV_copy_image) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_NV_delay_before_swap(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          32  /* glXDelayBeforeSwapNV */
    };
    uint32_t i;
    if(!context->NV_delay_before_swap) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_NV_present_video(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           6, /* glXBindVideoDeviceNV */
          42  /* glXEnumerateVideoDevicesNV */
    };
    uint32_t i;
    if(!context->NV_present_video) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_NV_swap_group(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           2, /* glXBindSwapBarrierNV */
          79, /* glXJoinSwapGroupNV */
          96, /* glXQueryFrameCountNV */
         103, /* glXQueryMaxSwapGroupsNV */
         107, /* glXQuerySwapGroupNV */
         115  /* glXResetFrameCountNV */
    };
    uint32_t i;
    if(!context->NV_swap_group) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_NV_video_capture(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           5, /* glXBindVideoCaptureDeviceNV */
          41, /* glXEnumerateVideoCaptureDevicesNV */
          81, /* glXLockVideoCaptureDeviceNV */
         109, /* glXQueryVideoCaptureDeviceNV */
         112  /* glXReleaseVideoCaptureDeviceNV */
    };
    uint32_t i;
    if(!context->NV_video_capture) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_NV_video_out(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           7, /* glXBindVideoImageNV */
          70, /* glXGetVideoDeviceNV */
          71, /* glXGetVideoInfoNV */
         113, /* glXReleaseVideoDeviceNV */
         114, /* glXReleaseVideoImageNV */
         118  /* glXSendPbufferToVideoNV */
    };
    uint32_t i;
    if(!context->NV_video_out) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_OML_sync_control(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          62, /* glXGetMscRateOML */
          68, /* glXGetSyncValuesOML */
         121, /* glXSwapBuffersMscOML */
         126, /* glXWaitForMscOML */
         127  /* glXWaitForSbcOML */
    };
    uint32_t i;
    if(!context->OML_sync_control) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_SGIX_fbconfig(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          12, /* glXChooseFBConfigSGIX */
          22, /* glXCreateContextWithConfigSGIX */
          26, /* glXCreateGLXPixmapWithConfigSGIX */
          57, /* glXGetFBConfigAttribSGIX */
          58, /* glXGetFBConfigFromVisualSGIX */
          74  /* glXGetVisualFromFBConfigSGIX */
    };
    uint32_t i;
    if(!context->SGIX_fbconfig) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_SGIX_hyperpipe(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           1, /* glXBindHyperpipeSGIX */
          37, /* glXDestroyHyperpipeConfigSGIX */
          75, /* glXHyperpipeAttribSGIX */
          76, /* glXHyperpipeConfigSGIX */
          98, /* glXQueryHyperpipeAttribSGIX */
          99, /* glXQueryHyperpipeBestAttribSGIX */
         100, /* glXQueryHyperpipeConfigSGIX */
         101  /* glXQueryHyperpipeNetworkSGIX */
    };
    uint32_t i;
    if(!context->SGIX_hyperpipe) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_SGIX_pbuffer(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          23, /* glXCreateGLXPbufferSGIX */
          35, /* glXDestroyGLXPbufferSGIX */
          66, /* glXGetSelectedEventSGIX */
          97, /* glXQueryGLXPbufferSGIX */
         117  /* glXSelectEventSGIX */
    };
    uint32_t i;
    if(!context->SGIX_pbuffer) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_SGIX_swap_barrier(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           3, /* glXBindSwapBarrierSGIX */
         102  /* glXQueryMaxSwapBarriersSGIX */
    };
    uint32_t i;
    if(!context->SGIX_swap_barrier) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_SGIX_swap_group(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          80  /* glXJoinSwapGroupSGIX */
    };
    uint32_t i;
    if(!context->SGIX_swap_group) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_SGIX_video_resize(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           0, /* glXBindChannelToWindowSGIX */
           9, /* glXChannelRectSGIX */
          10, /* glXChannelRectSyncSGIX */
          87, /* glXQueryChannelDeltasSGIX */
          88  /* glXQueryChannelRectSGIX */
    };
    uint32_t i;
    if(!context->SGIX_video_resize) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_SGI_cushion(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          31  /* glXCushionSGI */
    };
    uint32_t i;
    if(!context->SGI_cushion) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_SGI_make_current_read(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          55, /* glXGetCurrentReadDrawableSGI */
          85  /* glXMakeCurrentReadSGI */
    };
    uint32_t i;
    if(!context->SGI_make_current_read) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_SGI_swap_control(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         124  /* glXSwapIntervalSGI */
    };
    uint32_t i;
    if(!context->SGI_swap_control) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_SGI_video_sync(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          72, /* glXGetVideoSyncSGI */
         129  /* glXWaitVideoSyncSGI */
    };
    uint32_t i;
    if(!context->SGI_video_sync) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_SUN_get_transparent_index(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          69  /* glXGetTransparentIndexSUN */
    };
    uint32_t i;
    if(!context->SUN_get_transparent_index) return;
    #ifdef __clang__
    #pragma nounroll
    #endif
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
#ifdef GLX_VERSION_1_1
    const char *extensions;
    uint32_t i;

    if (context->QueryExtensionsString == NULL) {
        return -2;
    }

    extensions = context->QueryExtensionsString(display, screen);

    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_GLX_ext_names); ++i)
        context->extArray[i] = glad_glx_has_extension(extensions, GLAD_GLX_ext_names[i]);
#else
    GLAD_UNUSED(context);
    GLAD_UNUSED(display);
    GLAD_UNUSED(screen);
    GLAD_UNUSED(GLAD_GLX_ext_names);
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
