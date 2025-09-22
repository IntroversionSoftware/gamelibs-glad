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

#ifdef __cplusplus
GladGLXContext glad_glx_context = {};
#else
GladGLXContext glad_glx_context = { 0 };
#endif

static const char * const GLAD_GLX_fn_names[] = {
    /*    0 */ "glXChooseVisual",
    /*    1 */ "glXCreateContext",
    /*    2 */ "glXDestroyContext",
    /*    3 */ "glXMakeCurrent",
    /*    4 */ "glXCopyContext",
    /*    5 */ "glXSwapBuffers",
    /*    6 */ "glXCreateGLXPixmap",
    /*    7 */ "glXDestroyGLXPixmap",
    /*    8 */ "glXQueryExtension",
    /*    9 */ "glXQueryVersion",
    /*   10 */ "glXIsDirect",
    /*   11 */ "glXGetConfig",
    /*   12 */ "glXGetCurrentContext",
    /*   13 */ "glXGetCurrentDrawable",
    /*   14 */ "glXWaitGL",
    /*   15 */ "glXWaitX",
    /*   16 */ "glXUseXFont",
    /*   17 */ "glXQueryExtensionsString",
    /*   18 */ "glXQueryServerString",
    /*   19 */ "glXGetClientString",
    /*   20 */ "glXGetCurrentDisplay",
    /*   21 */ "glXGetFBConfigs",
    /*   22 */ "glXChooseFBConfig",
    /*   23 */ "glXGetFBConfigAttrib",
    /*   24 */ "glXGetVisualFromFBConfig",
    /*   25 */ "glXCreateWindow",
    /*   26 */ "glXDestroyWindow",
    /*   27 */ "glXCreatePixmap",
    /*   28 */ "glXDestroyPixmap",
    /*   29 */ "glXCreatePbuffer",
    /*   30 */ "glXDestroyPbuffer",
    /*   31 */ "glXQueryDrawable",
    /*   32 */ "glXCreateNewContext",
    /*   33 */ "glXMakeContextCurrent",
    /*   34 */ "glXGetCurrentReadDrawable",
    /*   35 */ "glXQueryContext",
    /*   36 */ "glXSelectEvent",
    /*   37 */ "glXGetSelectedEvent",
    /*   38 */ "glXGetProcAddress",
    /*   39 */ "glXGetGPUIDsAMD",
    /*   40 */ "glXGetGPUInfoAMD",
    /*   41 */ "glXGetContextGPUIDAMD",
    /*   42 */ "glXCreateAssociatedContextAMD",
    /*   43 */ "glXCreateAssociatedContextAttribsAMD",
    /*   44 */ "glXDeleteAssociatedContextAMD",
    /*   45 */ "glXMakeAssociatedContextCurrentAMD",
    /*   46 */ "glXGetCurrentAssociatedContextAMD",
    /*   47 */ "glXBlitContextFramebufferAMD",
    /*   48 */ "glXCreateContextAttribsARB",
    /*   49 */ "glXGetProcAddressARB",
    /*   50 */ "glXGetCurrentDisplayEXT",
    /*   51 */ "glXQueryContextInfoEXT",
    /*   52 */ "glXGetContextIDEXT",
    /*   53 */ "glXImportContextEXT",
    /*   54 */ "glXFreeContextEXT",
    /*   55 */ "glXSwapIntervalEXT",
    /*   56 */ "glXBindTexImageEXT",
    /*   57 */ "glXReleaseTexImageEXT",
    /*   58 */ "glXGetAGPOffsetMESA",
    /*   59 */ "glXCopySubBufferMESA",
    /*   60 */ "glXCreateGLXPixmapMESA",
    /*   61 */ "glXQueryCurrentRendererIntegerMESA",
    /*   62 */ "glXQueryCurrentRendererStringMESA",
    /*   63 */ "glXQueryRendererIntegerMESA",
    /*   64 */ "glXQueryRendererStringMESA",
    /*   65 */ "glXReleaseBuffersMESA",
    /*   66 */ "glXSet3DfxModeMESA",
    /*   67 */ "glXGetSwapIntervalMESA",
    /*   68 */ "glXSwapIntervalMESA",
    /*   69 */ "glXCopyBufferSubDataNV",
    /*   70 */ "glXNamedCopyBufferSubDataNV",
    /*   71 */ "glXCopyImageSubDataNV",
    /*   72 */ "glXDelayBeforeSwapNV",
    /*   73 */ "glXEnumerateVideoDevicesNV",
    /*   74 */ "glXBindVideoDeviceNV",
    /*   75 */ "glXJoinSwapGroupNV",
    /*   76 */ "glXBindSwapBarrierNV",
    /*   77 */ "glXQuerySwapGroupNV",
    /*   78 */ "glXQueryMaxSwapGroupsNV",
    /*   79 */ "glXQueryFrameCountNV",
    /*   80 */ "glXResetFrameCountNV",
    /*   81 */ "glXBindVideoCaptureDeviceNV",
    /*   82 */ "glXEnumerateVideoCaptureDevicesNV",
    /*   83 */ "glXLockVideoCaptureDeviceNV",
    /*   84 */ "glXQueryVideoCaptureDeviceNV",
    /*   85 */ "glXReleaseVideoCaptureDeviceNV",
    /*   86 */ "glXGetVideoDeviceNV",
    /*   87 */ "glXReleaseVideoDeviceNV",
    /*   88 */ "glXBindVideoImageNV",
    /*   89 */ "glXReleaseVideoImageNV",
    /*   90 */ "glXSendPbufferToVideoNV",
    /*   91 */ "glXGetVideoInfoNV",
    /*   92 */ "glXGetSyncValuesOML",
    /*   93 */ "glXGetMscRateOML",
    /*   94 */ "glXSwapBuffersMscOML",
    /*   95 */ "glXWaitForMscOML",
    /*   96 */ "glXWaitForSbcOML",
    /*   97 */ "glXCushionSGI",
    /*   98 */ "glXMakeCurrentReadSGI",
    /*   99 */ "glXGetCurrentReadDrawableSGI",
    /*  100 */ "glXSwapIntervalSGI",
    /*  101 */ "glXGetVideoSyncSGI",
    /*  102 */ "glXWaitVideoSyncSGI",
    /*  103 */ "glXGetFBConfigAttribSGIX",
    /*  104 */ "glXChooseFBConfigSGIX",
    /*  105 */ "glXCreateGLXPixmapWithConfigSGIX",
    /*  106 */ "glXCreateContextWithConfigSGIX",
    /*  107 */ "glXGetVisualFromFBConfigSGIX",
    /*  108 */ "glXGetFBConfigFromVisualSGIX",
    /*  109 */ "glXQueryHyperpipeNetworkSGIX",
    /*  110 */ "glXHyperpipeConfigSGIX",
    /*  111 */ "glXQueryHyperpipeConfigSGIX",
    /*  112 */ "glXDestroyHyperpipeConfigSGIX",
    /*  113 */ "glXBindHyperpipeSGIX",
    /*  114 */ "glXQueryHyperpipeBestAttribSGIX",
    /*  115 */ "glXHyperpipeAttribSGIX",
    /*  116 */ "glXQueryHyperpipeAttribSGIX",
    /*  117 */ "glXCreateGLXPbufferSGIX",
    /*  118 */ "glXDestroyGLXPbufferSGIX",
    /*  119 */ "glXQueryGLXPbufferSGIX",
    /*  120 */ "glXSelectEventSGIX",
    /*  121 */ "glXGetSelectedEventSGIX",
    /*  122 */ "glXBindSwapBarrierSGIX",
    /*  123 */ "glXQueryMaxSwapBarriersSGIX",
    /*  124 */ "glXJoinSwapGroupSGIX",
    /*  125 */ "glXBindChannelToWindowSGIX",
    /*  126 */ "glXChannelRectSGIX",
    /*  127 */ "glXQueryChannelRectSGIX",
    /*  128 */ "glXQueryChannelDeltasSGIX",
    /*  129 */ "glXChannelRectSyncSGIX",
    /*  130 */ "glXGetTransparentIndexSUN"
};

static const char * const GLAD_GLX_ext_names[] = {
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


static void glad_glx_load_pfns(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr, const uint16_t *pPfnIdx, uint32_t numPfns)
{
    uint32_t i;

    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < numPfns; ++i) {
        const uint16_t pfnIdx = pPfnIdx[i];
        context->pfnArray[pfnIdx] = (void *)load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

static void glad_glx_load_GLX_VERSION_1_0(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           0, /* glXChooseVisual */
           1, /* glXCreateContext */
           2, /* glXDestroyContext */
           3, /* glXMakeCurrent */
           4, /* glXCopyContext */
           5, /* glXSwapBuffers */
           6, /* glXCreateGLXPixmap */
           7, /* glXDestroyGLXPixmap */
           8, /* glXQueryExtension */
           9, /* glXQueryVersion */
          10, /* glXIsDirect */
          11, /* glXGetConfig */
          12, /* glXGetCurrentContext */
          13, /* glXGetCurrentDrawable */
          14, /* glXWaitGL */
          15, /* glXWaitX */
          16  /* glXUseXFont */
    };
    if (!context->VERSION_1_0) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_VERSION_1_1(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          17, /* glXQueryExtensionsString */
          18, /* glXQueryServerString */
          19  /* glXGetClientString */
    };
    if (!context->VERSION_1_1) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_VERSION_1_2(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          20  /* glXGetCurrentDisplay */
    };
    if (!context->VERSION_1_2) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_VERSION_1_3(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          21, /* glXGetFBConfigs */
          22, /* glXChooseFBConfig */
          23, /* glXGetFBConfigAttrib */
          24, /* glXGetVisualFromFBConfig */
          25, /* glXCreateWindow */
          26, /* glXDestroyWindow */
          27, /* glXCreatePixmap */
          28, /* glXDestroyPixmap */
          29, /* glXCreatePbuffer */
          30, /* glXDestroyPbuffer */
          31, /* glXQueryDrawable */
          32, /* glXCreateNewContext */
          33, /* glXMakeContextCurrent */
          34, /* glXGetCurrentReadDrawable */
          35, /* glXQueryContext */
          36, /* glXSelectEvent */
          37  /* glXGetSelectedEvent */
    };
    if (!context->VERSION_1_3) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_VERSION_1_4(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          38  /* glXGetProcAddress */
    };
    if (!context->VERSION_1_4) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_AMD_gpu_association(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          39, /* glXGetGPUIDsAMD */
          40, /* glXGetGPUInfoAMD */
          41, /* glXGetContextGPUIDAMD */
          42, /* glXCreateAssociatedContextAMD */
          43, /* glXCreateAssociatedContextAttribsAMD */
          44, /* glXDeleteAssociatedContextAMD */
          45, /* glXMakeAssociatedContextCurrentAMD */
          46, /* glXGetCurrentAssociatedContextAMD */
          47  /* glXBlitContextFramebufferAMD */
    };
    if (!context->AMD_gpu_association) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_ARB_create_context(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          48  /* glXCreateContextAttribsARB */
    };
    if (!context->ARB_create_context) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_ARB_get_proc_address(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          49  /* glXGetProcAddressARB */
    };
    if (!context->ARB_get_proc_address) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_EXT_import_context(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          50, /* glXGetCurrentDisplayEXT */
          51, /* glXQueryContextInfoEXT */
          52, /* glXGetContextIDEXT */
          53, /* glXImportContextEXT */
          54  /* glXFreeContextEXT */
    };
    if (!context->EXT_import_context) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_EXT_swap_control(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          55  /* glXSwapIntervalEXT */
    };
    if (!context->EXT_swap_control) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_EXT_texture_from_pixmap(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          56, /* glXBindTexImageEXT */
          57  /* glXReleaseTexImageEXT */
    };
    if (!context->EXT_texture_from_pixmap) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_MESA_agp_offset(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          58  /* glXGetAGPOffsetMESA */
    };
    if (!context->MESA_agp_offset) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_MESA_copy_sub_buffer(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          59  /* glXCopySubBufferMESA */
    };
    if (!context->MESA_copy_sub_buffer) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_MESA_pixmap_colormap(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          60  /* glXCreateGLXPixmapMESA */
    };
    if (!context->MESA_pixmap_colormap) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_MESA_query_renderer(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          61, /* glXQueryCurrentRendererIntegerMESA */
          62, /* glXQueryCurrentRendererStringMESA */
          63, /* glXQueryRendererIntegerMESA */
          64  /* glXQueryRendererStringMESA */
    };
    if (!context->MESA_query_renderer) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_MESA_release_buffers(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          65  /* glXReleaseBuffersMESA */
    };
    if (!context->MESA_release_buffers) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_MESA_set_3dfx_mode(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          66  /* glXSet3DfxModeMESA */
    };
    if (!context->MESA_set_3dfx_mode) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_MESA_swap_control(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          67, /* glXGetSwapIntervalMESA */
          68  /* glXSwapIntervalMESA */
    };
    if (!context->MESA_swap_control) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_NV_copy_buffer(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          69, /* glXCopyBufferSubDataNV */
          70  /* glXNamedCopyBufferSubDataNV */
    };
    if (!context->NV_copy_buffer) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_NV_copy_image(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          71  /* glXCopyImageSubDataNV */
    };
    if (!context->NV_copy_image) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_NV_delay_before_swap(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          72  /* glXDelayBeforeSwapNV */
    };
    if (!context->NV_delay_before_swap) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_NV_present_video(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          73, /* glXEnumerateVideoDevicesNV */
          74  /* glXBindVideoDeviceNV */
    };
    if (!context->NV_present_video) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_NV_swap_group(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          75, /* glXJoinSwapGroupNV */
          76, /* glXBindSwapBarrierNV */
          77, /* glXQuerySwapGroupNV */
          78, /* glXQueryMaxSwapGroupsNV */
          79, /* glXQueryFrameCountNV */
          80  /* glXResetFrameCountNV */
    };
    if (!context->NV_swap_group) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_NV_video_capture(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          81, /* glXBindVideoCaptureDeviceNV */
          82, /* glXEnumerateVideoCaptureDevicesNV */
          83, /* glXLockVideoCaptureDeviceNV */
          84, /* glXQueryVideoCaptureDeviceNV */
          85  /* glXReleaseVideoCaptureDeviceNV */
    };
    if (!context->NV_video_capture) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_NV_video_out(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          86, /* glXGetVideoDeviceNV */
          87, /* glXReleaseVideoDeviceNV */
          88, /* glXBindVideoImageNV */
          89, /* glXReleaseVideoImageNV */
          90, /* glXSendPbufferToVideoNV */
          91  /* glXGetVideoInfoNV */
    };
    if (!context->NV_video_out) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_OML_sync_control(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          92, /* glXGetSyncValuesOML */
          93, /* glXGetMscRateOML */
          94, /* glXSwapBuffersMscOML */
          95, /* glXWaitForMscOML */
          96  /* glXWaitForSbcOML */
    };
    if (!context->OML_sync_control) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_SGIX_fbconfig(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         103, /* glXGetFBConfigAttribSGIX */
         104, /* glXChooseFBConfigSGIX */
         105, /* glXCreateGLXPixmapWithConfigSGIX */
         106, /* glXCreateContextWithConfigSGIX */
         107, /* glXGetVisualFromFBConfigSGIX */
         108  /* glXGetFBConfigFromVisualSGIX */
    };
    if (!context->SGIX_fbconfig) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_SGIX_hyperpipe(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         109, /* glXQueryHyperpipeNetworkSGIX */
         110, /* glXHyperpipeConfigSGIX */
         111, /* glXQueryHyperpipeConfigSGIX */
         112, /* glXDestroyHyperpipeConfigSGIX */
         113, /* glXBindHyperpipeSGIX */
         114, /* glXQueryHyperpipeBestAttribSGIX */
         115, /* glXHyperpipeAttribSGIX */
         116  /* glXQueryHyperpipeAttribSGIX */
    };
    if (!context->SGIX_hyperpipe) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_SGIX_pbuffer(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         117, /* glXCreateGLXPbufferSGIX */
         118, /* glXDestroyGLXPbufferSGIX */
         119, /* glXQueryGLXPbufferSGIX */
         120, /* glXSelectEventSGIX */
         121  /* glXGetSelectedEventSGIX */
    };
    if (!context->SGIX_pbuffer) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_SGIX_swap_barrier(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         122, /* glXBindSwapBarrierSGIX */
         123  /* glXQueryMaxSwapBarriersSGIX */
    };
    if (!context->SGIX_swap_barrier) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_SGIX_swap_group(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         124  /* glXJoinSwapGroupSGIX */
    };
    if (!context->SGIX_swap_group) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_SGIX_video_resize(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         125, /* glXBindChannelToWindowSGIX */
         126, /* glXChannelRectSGIX */
         127, /* glXQueryChannelRectSGIX */
         128, /* glXQueryChannelDeltasSGIX */
         129  /* glXChannelRectSyncSGIX */
    };
    if (!context->SGIX_video_resize) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_SGI_cushion(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          97  /* glXCushionSGI */
    };
    if (!context->SGI_cushion) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_SGI_make_current_read(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          98, /* glXMakeCurrentReadSGI */
          99  /* glXGetCurrentReadDrawableSGI */
    };
    if (!context->SGI_make_current_read) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_SGI_swap_control(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         100  /* glXSwapIntervalSGI */
    };
    if (!context->SGI_swap_control) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_SGI_video_sync(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         101, /* glXGetVideoSyncSGI */
         102  /* glXWaitVideoSyncSGI */
    };
    if (!context->SGI_video_sync) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_glx_load_GLX_SUN_get_transparent_index(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         130  /* glXGetTransparentIndexSUN */
    };
    if (!context->SUN_get_transparent_index) return;
    glad_glx_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

GLAD_NO_INLINE static void glad_glx_resolve_aliases(GladGLXContext *context) {
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
    unsigned short version_value;
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
    version_value = (major << 8U) | minor;
    context->VERSION_1_0 = version_value >= 0x0100;
    context->VERSION_1_1 = version_value >= 0x0101;
    context->VERSION_1_2 = version_value >= 0x0102;
    context->VERSION_1_3 = version_value >= 0x0103;
    context->VERSION_1_4 = version_value >= 0x0104;
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
