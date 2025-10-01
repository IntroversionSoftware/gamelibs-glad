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
GladWGLContext glad_wgl_context = {};
#else
GladWGLContext glad_wgl_context = { 0 };
#endif

static const char * const GLAD_WGL_fn_names[] = {
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

static const GladPfnRange_t GLAD_WGL_feature_pfn_ranges[] = {
    {    0,    0,   26 }, /* WGL_VERSION_1_0 */
};

static const GladPfnRange_t GLAD_wgl_ext_pfn_ranges[] = {
    {    1,   26,    1 }, /* WGL_3DL_stereo_control */
    {    2,   27,    9 }, /* WGL_AMD_gpu_association */
    {    3,   36,    4 }, /* WGL_ARB_buffer_region */
    {    5,   40,    1 }, /* WGL_ARB_create_context */
    {    9,   41,    1 }, /* WGL_ARB_extensions_string */
    {   11,   42,    2 }, /* WGL_ARB_make_current_read */
    {   13,   44,    5 }, /* WGL_ARB_pbuffer */
    {   14,   49,    3 }, /* WGL_ARB_pixel_format */
    {   16,   52,    3 }, /* WGL_ARB_render_texture */
    {   25,   55,    4 }, /* WGL_EXT_display_color_table */
    {   26,   59,    1 }, /* WGL_EXT_extensions_string */
    {   28,   60,    2 }, /* WGL_EXT_make_current_read */
    {   30,   62,    5 }, /* WGL_EXT_pbuffer */
    {   31,   67,    3 }, /* WGL_EXT_pixel_format */
    {   33,   70,    2 }, /* WGL_EXT_swap_control */
    {   35,   72,    2 }, /* WGL_I3D_digital_video_control */
    {   36,   74,    4 }, /* WGL_I3D_gamma */
    {   37,   78,   12 }, /* WGL_I3D_genlock */
    {   38,   90,    4 }, /* WGL_I3D_image_buffer */
    {   39,   94,    4 }, /* WGL_I3D_swap_frame_lock */
    {   40,   98,    4 }, /* WGL_I3D_swap_frame_usage */
    {   41,  104,    8 }, /* WGL_NV_DX_interop */
    {   43,  102,    1 }, /* WGL_NV_copy_image */
    {   44,  103,    1 }, /* WGL_NV_delay_before_swap */
    {   46,  112,    5 }, /* WGL_NV_gpu_affinity */
    {   49,  117,    3 }, /* WGL_NV_present_video */
    {   52,  120,    6 }, /* WGL_NV_swap_group */
    {   53,  137,    2 }, /* WGL_NV_vertex_array_range */
    {   54,  126,    5 }, /* WGL_NV_video_capture */
    {   55,  131,    6 }, /* WGL_NV_video_output */
    {   56,  139,    6 }, /* WGL_OML_sync_control */
};

static const uint64_t GLAD_WGL_ext_hashes[] = {
    /*    0 */ 0x0bec45d23000040cULL, /* WGL_3DFX_multisample */
    /*    1 */ 0xa544e2233909cd6cULL, /* WGL_3DL_stereo_control */
    /*    2 */ 0x3444be63e457de0aULL, /* WGL_AMD_gpu_association */
    /*    3 */ 0x23735e3ef94191dfULL, /* WGL_ARB_buffer_region */
    /*    4 */ 0xcba9d91bf8152127ULL, /* WGL_ARB_context_flush_control */
    /*    5 */ 0x93b339a9e2cbe314ULL, /* WGL_ARB_create_context */
    /*    6 */ 0x4d3ff082cec434daULL, /* WGL_ARB_create_context_no_error */
    /*    7 */ 0x6879670f69d523e8ULL, /* WGL_ARB_create_context_profile */
    /*    8 */ 0x24a0369001a0d30dULL, /* WGL_ARB_create_context_robustness */
    /*    9 */ 0xd6afdfe5c6fa3614ULL, /* WGL_ARB_extensions_string */
    /*   10 */ 0x2b2322e59fb5083bULL, /* WGL_ARB_framebuffer_sRGB */
    /*   11 */ 0xffb3e932bb0ccdd5ULL, /* WGL_ARB_make_current_read */
    /*   12 */ 0xad82eec327c2f1d8ULL, /* WGL_ARB_multisample */
    /*   13 */ 0xf6b9458b542c30dcULL, /* WGL_ARB_pbuffer */
    /*   14 */ 0xe73be941e5f7916bULL, /* WGL_ARB_pixel_format */
    /*   15 */ 0x0bed92c76c78efffULL, /* WGL_ARB_pixel_format_float */
    /*   16 */ 0xf0753dc5c832f146ULL, /* WGL_ARB_render_texture */
    /*   17 */ 0x6c50f503bc89115eULL, /* WGL_ARB_robustness_application_isolation */
    /*   18 */ 0x944ee36787077ccfULL, /* WGL_ARB_robustness_share_group_isolation */
    /*   19 */ 0x40521e21b96727d5ULL, /* WGL_ATI_pixel_format_float */
    /*   20 */ 0x6a042befb2e60d17ULL, /* WGL_ATI_render_texture_rectangle */
    /*   21 */ 0x344eee0b6820af34ULL, /* WGL_EXT_colorspace */
    /*   22 */ 0xdea75ca5e2edbb10ULL, /* WGL_EXT_create_context_es2_profile */
    /*   23 */ 0x7e5f58022569e61eULL, /* WGL_EXT_create_context_es_profile */
    /*   24 */ 0x3404dab980e61ca2ULL, /* WGL_EXT_depth_float */
    /*   25 */ 0x2d0e6cfb46a0106fULL, /* WGL_EXT_display_color_table */
    /*   26 */ 0x675d378710334a65ULL, /* WGL_EXT_extensions_string */
    /*   27 */ 0x1f5a579fdea0f148ULL, /* WGL_EXT_framebuffer_sRGB */
    /*   28 */ 0x6d4cef39fc681fb3ULL, /* WGL_EXT_make_current_read */
    /*   29 */ 0x712af2217200a415ULL, /* WGL_EXT_multisample */
    /*   30 */ 0x51b3a5602fa896a1ULL, /* WGL_EXT_pbuffer */
    /*   31 */ 0xf09d08e1c43f564eULL, /* WGL_EXT_pixel_format */
    /*   32 */ 0x61cb3bc9968979c9ULL, /* WGL_EXT_pixel_format_packed_float */
    /*   33 */ 0x212a6bdfca219506ULL, /* WGL_EXT_swap_control */
    /*   34 */ 0x97c79eb8ab4c254aULL, /* WGL_EXT_swap_control_tear */
    /*   35 */ 0x93c433aa5564a48dULL, /* WGL_I3D_digital_video_control */
    /*   36 */ 0x50b4447ba45d250eULL, /* WGL_I3D_gamma */
    /*   37 */ 0x13f677cdbcea2701ULL, /* WGL_I3D_genlock */
    /*   38 */ 0x7030d8df95640f74ULL, /* WGL_I3D_image_buffer */
    /*   39 */ 0xf89e0e880fa2991dULL, /* WGL_I3D_swap_frame_lock */
    /*   40 */ 0xe483d21a182c9656ULL, /* WGL_I3D_swap_frame_usage */
    /*   41 */ 0xa54b9b658ac06b9aULL, /* WGL_NV_DX_interop */
    /*   42 */ 0x1187bf238685f6baULL, /* WGL_NV_DX_interop2 */
    /*   43 */ 0xafab55f5e37bcb25ULL, /* WGL_NV_copy_image */
    /*   44 */ 0x3e1dd8f8bde73422ULL, /* WGL_NV_delay_before_swap */
    /*   45 */ 0xdad29f54a41cb160ULL, /* WGL_NV_float_buffer */
    /*   46 */ 0x83ba23356bc5c9c7ULL, /* WGL_NV_gpu_affinity */
    /*   47 */ 0x045e190c435b4d35ULL, /* WGL_NV_multigpu_context */
    /*   48 */ 0x7d7c383b450b63afULL, /* WGL_NV_multisample_coverage */
    /*   49 */ 0x5f2a9df50cf1003aULL, /* WGL_NV_present_video */
    /*   50 */ 0x2ac871c1f2dbac4dULL, /* WGL_NV_render_depth_texture */
    /*   51 */ 0x275c113e57078fccULL, /* WGL_NV_render_texture_rectangle */
    /*   52 */ 0xd91b7247d42d3ba5ULL, /* WGL_NV_swap_group */
    /*   53 */ 0x293670a02363360bULL, /* WGL_NV_vertex_array_range */
    /*   54 */ 0x8cf54648141ca138ULL, /* WGL_NV_video_capture */
    /*   55 */ 0xeab153b5cac91b24ULL, /* WGL_NV_video_output */
    /*   56 */ 0x3c2462ed17d12185ULL  /* WGL_OML_sync_control */
};
static void glad_wgl_load_pfn_range(GladWGLContext *context, GLADuserptrloadfunc load, void* userptr, uint16_t pfnStart, uint32_t numPfns)
{
    uint32_t pfnIdx;

    for (pfnIdx = pfnStart; pfnIdx < pfnStart + numPfns; ++pfnIdx) {
        context->pfnArray[pfnIdx] = (void *)load(userptr, GLAD_WGL_fn_names[pfnIdx]);
    }
}

GLAD_NO_INLINE static void glad_wgl_resolve_aliases(GladWGLContext *context) {
    GLAD_UNUSED(context);
}

static GLADapiproc glad_wgl_get_proc_from_userptr(void *userptr, const char* name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_wgl_get_extensions(GladWGLContext *context, HDC hdc, uint64_t **out_exts, uint32_t *out_num_exts) {
    uint32_t num_exts = 0;
    uint64_t *exts = NULL;
    const char *exts_str = NULL;
    const char *cur = NULL;
    const char *next = NULL;
    uint32_t len = 0, j = 0;

    if(context->GetExtensionsStringEXT == NULL && context->GetExtensionsStringARB == NULL)
        return 0;

    if(context->GetExtensionsStringARB == NULL || hdc == INVALID_HANDLE_VALUE)
        exts_str = context->GetExtensionsStringEXT();
    else
        exts_str = context->GetExtensionsStringARB(hdc);

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

static void glad_wgl_free_extensions(uint64_t *exts) {
    free(exts);
}

static int glad_wgl_has_extension(uint64_t *exts, uint32_t num_exts, uint64_t ext) {
    return glad_hash_search(exts, num_exts, ext);
}

static int glad_wgl_find_extensions_wgl(GladWGLContext *context, HDC hdc) {
    uint64_t *exts = NULL;
    uint32_t num_exts = 0;
    uint32_t i;
    if (!glad_wgl_get_extensions(context, hdc, &exts, &num_exts)) return 0;

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_WGL_ext_hashes); ++i)
        context->extArray[i] = glad_wgl_has_extension(exts, num_exts, GLAD_WGL_ext_hashes[i]);

    glad_wgl_free_extensions(exts);

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

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_wgl_ext_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_wgl_ext_pfn_ranges[i];
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
