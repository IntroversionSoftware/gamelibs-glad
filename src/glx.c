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

#ifndef GLAD_EXTERNAL_XXHASH
#define XXH_INLINE_ALL
#define XXH_NO_STREAM
#endif
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

typedef struct {
    uint16_t extension;
    uint16_t start;
    uint16_t count;
} GladPfnRange_t;

#endif /* GLAD_IMPL_UTIL_C_ */

#ifndef GLAD_IMPL_UTIL_HASHSEARCH_C_
#define GLAD_IMPL_UTIL_HASHSEARCH_C_

#ifdef __cplusplus
extern "C" {
#endif

GLAD_NO_INLINE static bool glad_hash_search(const uint64_t *arr, uint32_t size, uint64_t target) {
    /* Binary search for matching hash */
    int32_t low = 0;
    int32_t high = (int32_t)size - 1;

    while (low <= high) {
        int32_t mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return true;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return false;
}

GLAD_NO_INLINE static void glad_sort_hashes(uint64_t *a, size_t n) {
    /* Ciura gap sequence; we’ll skip the big ones at runtime. */
    static const size_t gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};
    size_t gi = 0;

    if (!a || n < 2)
        return;

    while (gi < GLAD_ARRAYSIZE(gaps) && gaps[gi] >= n)
        gi++;

    for (; gi < GLAD_ARRAYSIZE(gaps); ++gi) {
        size_t gap = gaps[gi];
        for (size_t i = gap; i < n; ++i) {
            uint64_t v = a[i];
            size_t j = i;
            // gapped insertion sort
            while (j >= gap && a[j - gap] > v) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = v;
        }
    }
}

GLAD_NO_INLINE static uint64_t glad_hash_string(const char *str, size_t length)
{
    return XXH3_64bits(str, length);
}

#ifdef __cplusplus
}
#endif

#endif /* GLAD_IMPL_HASHSEARCH_C_ */

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

static const GladPfnRange_t GLAD_GLX_feature_pfn_ranges[] = {
    {    0,    0,   17 }, /* GLX_VERSION_1_0 */
    {    1,   17,    3 }, /* GLX_VERSION_1_1 */
    {    2,   20,    1 }, /* GLX_VERSION_1_2 */
    {    3,   21,   17 }, /* GLX_VERSION_1_3 */
    {    4,   38,    1 }, /* GLX_VERSION_1_4 */
};

static const GladPfnRange_t GLAD_glx_ext_pfn_ranges[] = {
    {    1,   39,    9 }, /* GLX_AMD_gpu_association */
    {    3,   48,    1 }, /* GLX_ARB_create_context */
    {    9,   49,    1 }, /* GLX_ARB_get_proc_address */
    {   21,   50,    5 }, /* GLX_EXT_import_context */
    {   25,   55,    1 }, /* GLX_EXT_swap_control */
    {   27,   56,    2 }, /* GLX_EXT_texture_from_pixmap */
    {   31,   58,    1 }, /* GLX_MESA_agp_offset */
    {   32,   59,    1 }, /* GLX_MESA_copy_sub_buffer */
    {   33,   60,    1 }, /* GLX_MESA_pixmap_colormap */
    {   34,   61,    4 }, /* GLX_MESA_query_renderer */
    {   35,   65,    1 }, /* GLX_MESA_release_buffers */
    {   36,   66,    1 }, /* GLX_MESA_set_3dfx_mode */
    {   37,   67,    2 }, /* GLX_MESA_swap_control */
    {   38,   69,    2 }, /* GLX_NV_copy_buffer */
    {   39,   71,    1 }, /* GLX_NV_copy_image */
    {   40,   72,    1 }, /* GLX_NV_delay_before_swap */
    {   44,   73,    2 }, /* GLX_NV_present_video */
    {   46,   75,    6 }, /* GLX_NV_swap_group */
    {   47,   81,    5 }, /* GLX_NV_video_capture */
    {   48,   86,    6 }, /* GLX_NV_video_out */
    {   50,   92,    5 }, /* GLX_OML_sync_control */
    {   54,  103,    6 }, /* GLX_SGIX_fbconfig */
    {   55,  109,    8 }, /* GLX_SGIX_hyperpipe */
    {   56,  117,    5 }, /* GLX_SGIX_pbuffer */
    {   57,  122,    2 }, /* GLX_SGIX_swap_barrier */
    {   58,  124,    1 }, /* GLX_SGIX_swap_group */
    {   59,  125,    5 }, /* GLX_SGIX_video_resize */
    {   61,   97,    1 }, /* GLX_SGI_cushion */
    {   62,   98,    2 }, /* GLX_SGI_make_current_read */
    {   63,  100,    1 }, /* GLX_SGI_swap_control */
    {   64,  101,    2 }, /* GLX_SGI_video_sync */
    {   65,  130,    1 }, /* GLX_SUN_get_transparent_index */
};

static const uint64_t GLAD_GLX_ext_hashes[] = {
    /*    0 */ 0xc090be22f50edf0fULL, /* GLX_3DFX_multisample */
    /*    1 */ 0x072d0fa7672bf59aULL, /* GLX_AMD_gpu_association */
    /*    2 */ 0x048a82b333a65f74ULL, /* GLX_ARB_context_flush_control */
    /*    3 */ 0x3f4d9cd2b079e931ULL, /* GLX_ARB_create_context */
    /*    4 */ 0xbd7c0e0c70fd916bULL, /* GLX_ARB_create_context_no_error */
    /*    5 */ 0x8690d94d5a4ce24dULL, /* GLX_ARB_create_context_profile */
    /*    6 */ 0x047a6e2eedd3d3d3ULL, /* GLX_ARB_create_context_robustness */
    /*    7 */ 0xa07f3edb8ce15ce0ULL, /* GLX_ARB_fbconfig_float */
    /*    8 */ 0xd5e2cc7383f82f45ULL, /* GLX_ARB_framebuffer_sRGB */
    /*    9 */ 0x6fad53b639e2a390ULL, /* GLX_ARB_get_proc_address */
    /*   10 */ 0x7dd3a391032250e3ULL, /* GLX_ARB_multisample */
    /*   11 */ 0xdba9a6195cec812fULL, /* GLX_ARB_robustness_application_isolation */
    /*   12 */ 0x081dfaeea13e2411ULL, /* GLX_ARB_robustness_share_group_isolation */
    /*   13 */ 0x2e804f63a6dcd082ULL, /* GLX_ARB_vertex_buffer_object */
    /*   14 */ 0xe7306595f98ee4e1ULL, /* GLX_EXT_buffer_age */
    /*   15 */ 0x1b481fa7315ee5b6ULL, /* GLX_EXT_context_priority */
    /*   16 */ 0xaec606cc661980b4ULL, /* GLX_EXT_create_context_es2_profile */
    /*   17 */ 0xf1d970eb90dd86a0ULL, /* GLX_EXT_create_context_es_profile */
    /*   18 */ 0x346e291f40286e34ULL, /* GLX_EXT_fbconfig_packed_float */
    /*   19 */ 0xd153ec8aa16793b3ULL, /* GLX_EXT_framebuffer_sRGB */
    /*   20 */ 0x83387f3dfb09e41fULL, /* GLX_EXT_get_drawable_type */
    /*   21 */ 0x03bcfc5a3cae3c31ULL, /* GLX_EXT_import_context */
    /*   22 */ 0x6f6d381e8ae478f2ULL, /* GLX_EXT_libglvnd */
    /*   23 */ 0x12a9351ba20ce5a3ULL, /* GLX_EXT_no_config_context */
    /*   24 */ 0x7cef1b9da97fd70eULL, /* GLX_EXT_stereo_tree */
    /*   25 */ 0xb279c1493993d32dULL, /* GLX_EXT_swap_control */
    /*   26 */ 0x81782a45ccd71ff8ULL, /* GLX_EXT_swap_control_tear */
    /*   27 */ 0xcd4daa50b9e2718aULL, /* GLX_EXT_texture_from_pixmap */
    /*   28 */ 0xb747ecf03b25c5b0ULL, /* GLX_EXT_visual_info */
    /*   29 */ 0x6c1fc772574daedcULL, /* GLX_EXT_visual_rating */
    /*   30 */ 0x90a93448eb7baa50ULL, /* GLX_INTEL_swap_event */
    /*   31 */ 0xce0282d625639b9bULL, /* GLX_MESA_agp_offset */
    /*   32 */ 0x910ff30a1deb6b79ULL, /* GLX_MESA_copy_sub_buffer */
    /*   33 */ 0xdab23c1e71961e55ULL, /* GLX_MESA_pixmap_colormap */
    /*   34 */ 0x29596e504e9a6a25ULL, /* GLX_MESA_query_renderer */
    /*   35 */ 0x0e4e87fbd85b8f81ULL, /* GLX_MESA_release_buffers */
    /*   36 */ 0x29561836651d917aULL, /* GLX_MESA_set_3dfx_mode */
    /*   37 */ 0xd32cf4de2880d29fULL, /* GLX_MESA_swap_control */
    /*   38 */ 0xc6df36e9a84a750eULL, /* GLX_NV_copy_buffer */
    /*   39 */ 0x939dc7e8d56cb021ULL, /* GLX_NV_copy_image */
    /*   40 */ 0xdae9b56ed6046e29ULL, /* GLX_NV_delay_before_swap */
    /*   41 */ 0x4e3ccfe50be2411dULL, /* GLX_NV_float_buffer */
    /*   42 */ 0xc52be3ef322db374ULL, /* GLX_NV_multigpu_context */
    /*   43 */ 0x6073c41473e50bfaULL, /* GLX_NV_multisample_coverage */
    /*   44 */ 0x871aa145ea386a73ULL, /* GLX_NV_present_video */
    /*   45 */ 0xdb0def6df3a16d6cULL, /* GLX_NV_robustness_video_memory_purge */
    /*   46 */ 0x2f414e4fcd131e32ULL, /* GLX_NV_swap_group */
    /*   47 */ 0xefa7c60274d87055ULL, /* GLX_NV_video_capture */
    /*   48 */ 0x963ec6ee3eb6b7fcULL, /* GLX_NV_video_out */
    /*   49 */ 0x139db0a508493724ULL, /* GLX_OML_swap_method */
    /*   50 */ 0xffaa3afdd9aa1090ULL, /* GLX_OML_sync_control */
    /*   51 */ 0xe386bd135a6e5f2cULL, /* GLX_SGIS_blended_overlay */
    /*   52 */ 0x900c6b39bcf9e3aeULL, /* GLX_SGIS_multisample */
    /*   53 */ 0x5c16b82b4300c08cULL, /* GLX_SGIS_shared_multisample */
    /*   54 */ 0x6dadb65d0ec947c2ULL, /* GLX_SGIX_fbconfig */
    /*   55 */ 0x341bcc9d120c6f49ULL, /* GLX_SGIX_hyperpipe */
    /*   56 */ 0x09ddc4c71d7734d0ULL, /* GLX_SGIX_pbuffer */
    /*   57 */ 0xaf8c148fdb3c3939ULL, /* GLX_SGIX_swap_barrier */
    /*   58 */ 0x4cab82df7b1591eeULL, /* GLX_SGIX_swap_group */
    /*   59 */ 0xadbdc7e24c604283ULL, /* GLX_SGIX_video_resize */
    /*   60 */ 0x07a1d27a401cc274ULL, /* GLX_SGIX_visual_select_group */
    /*   61 */ 0xb54066e1e7b44f60ULL, /* GLX_SGI_cushion */
    /*   62 */ 0xb01c250c6b9a122aULL, /* GLX_SGI_make_current_read */
    /*   63 */ 0xad9c9c9f23007dd1ULL, /* GLX_SGI_swap_control */
    /*   64 */ 0x0d617d9b2139534bULL, /* GLX_SGI_video_sync */
    /*   65 */ 0xa1de47dd92ad3d02ULL  /* GLX_SUN_get_transparent_index */
};
static void glad_glx_load_pfn_range(GladGLXContext *context, GLADuserptrloadfunc load, void* userptr, uint16_t pfnStart, uint32_t numPfns)
{
    uint32_t pfnIdx;

    for (pfnIdx = pfnStart; pfnIdx < pfnStart + numPfns; ++pfnIdx) {
        context->pfnArray[pfnIdx] = (void *)load(userptr, GLAD_GLX_fn_names[pfnIdx]);
    }
}

GLAD_NO_INLINE static void glad_glx_resolve_aliases(GladGLXContext *context) {
    GLAD_UNUSED(context);
}

static GLADapiproc glad_glx_get_proc_from_userptr(void *userptr, const char* name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_glx_get_extensions(GladGLXContext *context, Display *display, int screen, uint64_t **out_exts, uint32_t *out_num_exts) {
    uint32_t num_exts = 0;
    uint64_t *exts = NULL;
    const char *exts_str = NULL;
    const char *cur = NULL;
    const char *next = NULL;
    uint32_t len = 0, j = 0;

    if (context->QueryExtensionsString == NULL) {
        return -2;
    }

    exts_str = context->QueryExtensionsString(display, screen);

    /* This is done in two passes. The first pass counts up the number of
     * extensions. The second pass hashes their names and stores them in
     * a heap-allocated uint64 array for searching.
     */
    for (j = 0; j < 2; ++j) {
        num_exts = 0;
        cur = exts_str;
        next = cur + strcspn(cur, " ");
        while (1) {
            cur += strspn(cur, " ");

            if (!cur[0])
                break;

            len = next - cur;

            if (exts != NULL) {
                exts[num_exts++] = glad_hash_string(cur, len);
            } else {
                num_exts++;
            }

            cur = next + strspn(next, " ");
            next = cur + strcspn(cur, " ");
        }

        if (!exts)
            exts = (uint64_t *)calloc(num_exts, sizeof(uint64_t));
    }

    /* Sort extension list for binary search */
    glad_sort_hashes(exts, num_exts);

    *out_num_exts = num_exts;
    *out_exts = exts;
    return 1;
}

static void glad_glx_free_extensions(uint64_t *exts) {
    free(exts);
}

static int glad_glx_has_extension(uint64_t *exts, uint32_t num_exts, uint64_t ext) {
    return glad_hash_search(exts, num_exts, ext);
}

static int glad_glx_find_extensions(GladGLXContext *context, Display *display, int screen) {
    uint64_t *exts = NULL;
    uint32_t num_exts = 0;
    uint32_t i;
    if (!glad_glx_get_extensions(context, display, screen, &exts, &num_exts)) return 0;

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_GLX_ext_hashes); ++i)
        context->extArray[i] = glad_glx_has_extension(exts, num_exts, GLAD_GLX_ext_hashes[i]);

    glad_glx_free_extensions(exts);

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
    uint32_t i;

    context->QueryVersion = (PFNGLXQUERYVERSIONPROC) load(userptr, "glXQueryVersion");
    if(context->QueryVersion == NULL) return 0;
    version = glad_glx_find_core_glx(context, &display, &screen);

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_GLX_feature_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_GLX_feature_pfn_ranges[i];
        if (context->featArray[range->extension]) {
            glad_glx_load_pfn_range(context, load, userptr, range->start, range->count);
        }
    }

    if (!glad_glx_find_extensions(context, display, screen)) return 0;

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_glx_ext_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_glx_ext_pfn_ranges[i];
        if (context->extArray[range->extension]) {
            glad_glx_load_pfn_range(context, load, userptr, range->start, range->count);
        }
    }

    gladSetGLXContext(context);

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
struct _glad_glx_userptr {
    void *handle;
    GLADglxprocaddrfunc glx_get_proc_address_ptr;
};

static GLADapiproc glad_glx_get_proc(void *vuserptr, const char *name) {
    struct _glad_glx_userptr userptr = *(struct _glad_glx_userptr*) vuserptr;
    GLADapiproc result = NULL;

    if(userptr.glx_get_proc_address_ptr != NULL) {
        result = GLAD_GNUC_EXTENSION (GLADapiproc) userptr.glx_get_proc_address_ptr(name);
    }
    if(result == NULL) {
        result = glad_dlsym_handle(userptr.handle, name);
    }

    return result;
}

static void* glad_glx_dlopen_handle(GladGLXContext *context) {
    static const char *NAMES[] = {
#if defined __CYGWIN__
        "libGL-1.so",
#endif
        "libGL.so.1",
        "libGL.so"
    };

    if (context->glad_loader_handle == NULL) {
        context->glad_loader_handle = glad_get_dlopen_handle(NAMES, GLAD_ARRAYSIZE(NAMES));
    }

    return context->glad_loader_handle;
}

static struct _glad_glx_userptr glad_glx_build_userptr(void *handle) {
    struct _glad_glx_userptr userptr;

    userptr.handle = handle;
    userptr.glx_get_proc_address_ptr =
        (GLADglxprocaddrfunc) glad_dlsym_handle(handle, "glXGetProcAddressARB");

    return userptr;
}

int gladLoaderLoadGLXContext(GladGLXContext *context, Display *display, int screen) {
    int version = 0;
    void *handle;
    int did_load = 0;
    struct _glad_glx_userptr userptr;

    did_load = context->glad_loader_handle == NULL;
    handle = glad_glx_dlopen_handle(context);
    if (handle) {
        userptr = glad_glx_build_userptr(handle);

        version = gladLoadGLXContextUserPtr(context, display, screen, glad_glx_get_proc, &userptr);

        if (!version && did_load) {
            gladLoaderUnloadGLXContext(context);
        }
    }
    return version;
}

int gladLoaderLoadGLX(Display *display, int screen) {
    return gladLoaderLoadGLXContext(gladGetGLXContext(), display, screen);
}

void gladLoaderUnloadGLXContext(GladGLXContext *context) {
    if (context->glad_loader_handle != NULL) {
        glad_close_dlopen_handle(context->glad_loader_handle);
        context->glad_loader_handle = NULL;
    }

    gladLoaderResetGLXContext(context);
}

void gladLoaderUnloadGLX() {
    gladLoaderUnloadGLXContext(gladGetGLXContext());
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
