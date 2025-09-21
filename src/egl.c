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

#include <glad/egl.h>

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

GLAD_NO_INLINE static int compare_uint64(const void *pA, const void *pB)
{
    uint64_t a = *(const uint64_t *)pA;
    uint64_t b = *(const uint64_t *)pB;
    if (a > b)      return 1;
    else if (a < b) return -1;
    else            return 0;
}

GLAD_NO_INLINE static uint64_t glad_hash_string(const char *str, size_t length)
{
    return XXH3_64bits(str, length);
}

#endif /* GLAD_IMPL_HASHSEARCH_C_ */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
GladEGLContext glad_egl_context = {};
#else
GladEGLContext glad_egl_context = { 0 };
#endif

static const char *GLAD_EGL_fn_names[] = {
    /*    0 */ "eglChooseConfig",
    /*    1 */ "eglCopyBuffers",
    /*    2 */ "eglCreateContext",
    /*    3 */ "eglCreatePbufferSurface",
    /*    4 */ "eglCreatePixmapSurface",
    /*    5 */ "eglCreateWindowSurface",
    /*    6 */ "eglDestroyContext",
    /*    7 */ "eglDestroySurface",
    /*    8 */ "eglGetConfigAttrib",
    /*    9 */ "eglGetConfigs",
    /*   10 */ "eglGetCurrentDisplay",
    /*   11 */ "eglGetCurrentSurface",
    /*   12 */ "eglGetDisplay",
    /*   13 */ "eglGetError",
    /*   14 */ "eglGetProcAddress",
    /*   15 */ "eglInitialize",
    /*   16 */ "eglMakeCurrent",
    /*   17 */ "eglQueryContext",
    /*   18 */ "eglQueryString",
    /*   19 */ "eglQuerySurface",
    /*   20 */ "eglSwapBuffers",
    /*   21 */ "eglTerminate",
    /*   22 */ "eglWaitGL",
    /*   23 */ "eglWaitNative",
    /*   24 */ "eglBindTexImage",
    /*   25 */ "eglReleaseTexImage",
    /*   26 */ "eglSurfaceAttrib",
    /*   27 */ "eglSwapInterval",
    /*   28 */ "eglBindAPI",
    /*   29 */ "eglQueryAPI",
    /*   30 */ "eglCreatePbufferFromClientBuffer",
    /*   31 */ "eglReleaseThread",
    /*   32 */ "eglWaitClient",
    /*   33 */ "eglGetCurrentContext",
    /*   34 */ "eglCreateSync",
    /*   35 */ "eglDestroySync",
    /*   36 */ "eglClientWaitSync",
    /*   37 */ "eglGetSyncAttrib",
    /*   38 */ "eglCreateImage",
    /*   39 */ "eglDestroyImage",
    /*   40 */ "eglGetPlatformDisplay",
    /*   41 */ "eglCreatePlatformWindowSurface",
    /*   42 */ "eglCreatePlatformPixmapSurface",
    /*   43 */ "eglWaitSync",
    /*   44 */ "eglSetBlobCacheFuncsANDROID",
    /*   45 */ "eglCreateNativeClientBufferANDROID",
    /*   46 */ "eglGetNativeClientBufferANDROID",
    /*   47 */ "eglDupNativeFenceFDANDROID",
    /*   48 */ "eglPresentationTimeANDROID",
    /*   49 */ "eglGetCompositorTimingSupportedANDROID",
    /*   50 */ "eglGetCompositorTimingANDROID",
    /*   51 */ "eglGetNextFrameIdANDROID",
    /*   52 */ "eglGetFrameTimestampSupportedANDROID",
    /*   53 */ "eglGetFrameTimestampsANDROID",
    /*   54 */ "eglQuerySurfacePointerANGLE",
    /*   55 */ "eglGetMscRateANGLE",
    /*   56 */ "eglClientSignalSyncEXT",
    /*   57 */ "eglQueryDeviceAttribEXT",
    /*   58 */ "eglQueryDeviceStringEXT",
    /*   59 */ "eglQueryDevicesEXT",
    /*   60 */ "eglQueryDisplayAttribEXT",
    /*   61 */ "eglQueryDmaBufFormatsEXT",
    /*   62 */ "eglQueryDmaBufModifiersEXT",
    /*   63 */ "eglGetOutputLayersEXT",
    /*   64 */ "eglGetOutputPortsEXT",
    /*   65 */ "eglOutputLayerAttribEXT",
    /*   66 */ "eglQueryOutputLayerAttribEXT",
    /*   67 */ "eglQueryOutputLayerStringEXT",
    /*   68 */ "eglOutputPortAttribEXT",
    /*   69 */ "eglQueryOutputPortAttribEXT",
    /*   70 */ "eglQueryOutputPortStringEXT",
    /*   71 */ "eglGetPlatformDisplayEXT",
    /*   72 */ "eglCreatePlatformWindowSurfaceEXT",
    /*   73 */ "eglCreatePlatformPixmapSurfaceEXT",
    /*   74 */ "eglStreamConsumerOutputEXT",
    /*   75 */ "eglSwapBuffersWithDamageEXT",
    /*   76 */ "eglUnsignalSyncEXT",
    /*   77 */ "eglCreatePixmapSurfaceHI",
    /*   78 */ "eglCreateSync64KHR",
    /*   79 */ "eglDebugMessageControlKHR",
    /*   80 */ "eglQueryDebugKHR",
    /*   81 */ "eglLabelObjectKHR",
    /*   82 */ "eglQueryDisplayAttribKHR",
    /*   83 */ "eglCreateSyncKHR",
    /*   84 */ "eglDestroySyncKHR",
    /*   85 */ "eglClientWaitSyncKHR",
    /*   86 */ "eglGetSyncAttribKHR",
    /*   87 */ "eglCreateImageKHR",
    /*   88 */ "eglDestroyImageKHR",
    /*   89 */ "eglLockSurfaceKHR",
    /*   90 */ "eglUnlockSurfaceKHR",
    /*   91 */ "eglQuerySurface64KHR",
    /*   92 */ "eglSetDamageRegionKHR",
    /*   93 */ "eglSignalSyncKHR",
    /*   94 */ "eglCreateStreamKHR",
    /*   95 */ "eglDestroyStreamKHR",
    /*   96 */ "eglStreamAttribKHR",
    /*   97 */ "eglQueryStreamKHR",
    /*   98 */ "eglQueryStreamu64KHR",
    /*   99 */ "eglCreateStreamAttribKHR",
    /*  100 */ "eglSetStreamAttribKHR",
    /*  101 */ "eglQueryStreamAttribKHR",
    /*  102 */ "eglStreamConsumerAcquireAttribKHR",
    /*  103 */ "eglStreamConsumerReleaseAttribKHR",
    /*  104 */ "eglStreamConsumerGLTextureExternalKHR",
    /*  105 */ "eglStreamConsumerAcquireKHR",
    /*  106 */ "eglStreamConsumerReleaseKHR",
    /*  107 */ "eglGetStreamFileDescriptorKHR",
    /*  108 */ "eglCreateStreamFromFileDescriptorKHR",
    /*  109 */ "eglQueryStreamTimeKHR",
    /*  110 */ "eglCreateStreamProducerSurfaceKHR",
    /*  111 */ "eglSwapBuffersWithDamageKHR",
    /*  112 */ "eglWaitSyncKHR",
    /*  113 */ "eglCreateDRMImageMESA",
    /*  114 */ "eglExportDRMImageMESA",
    /*  115 */ "eglExportDMABUFImageQueryMESA",
    /*  116 */ "eglExportDMABUFImageMESA",
    /*  117 */ "eglGetDisplayDriverConfig",
    /*  118 */ "eglGetDisplayDriverName",
    /*  119 */ "eglSwapBuffersRegionNOK",
    /*  120 */ "eglSwapBuffersRegion2NOK",
    /*  121 */ "eglQueryNativeDisplayNV",
    /*  122 */ "eglQueryNativeWindowNV",
    /*  123 */ "eglQueryNativePixmapNV",
    /*  124 */ "eglPostSubBufferNV",
    /*  125 */ "eglStreamConsumerGLTextureExternalAttribsNV",
    /*  126 */ "eglStreamImageConsumerConnectNV",
    /*  127 */ "eglQueryStreamConsumerEventNV",
    /*  128 */ "eglStreamAcquireImageNV",
    /*  129 */ "eglStreamReleaseImageNV",
    /*  130 */ "eglStreamFlushNV",
    /*  131 */ "eglQueryDisplayAttribNV",
    /*  132 */ "eglSetStreamMetadataNV",
    /*  133 */ "eglQueryStreamMetadataNV",
    /*  134 */ "eglResetStreamNV",
    /*  135 */ "eglCreateStreamSyncNV",
    /*  136 */ "eglCreateFenceSyncNV",
    /*  137 */ "eglDestroySyncNV",
    /*  138 */ "eglFenceNV",
    /*  139 */ "eglClientWaitSyncNV",
    /*  140 */ "eglSignalSyncNV",
    /*  141 */ "eglGetSyncAttribNV",
    /*  142 */ "eglGetSystemTimeFrequencyNV",
    /*  143 */ "eglGetSystemTimeNV",
    /*  144 */ "eglCompositorSetContextListEXT",
    /*  145 */ "eglCompositorSetContextAttributesEXT",
    /*  146 */ "eglCompositorSetWindowListEXT",
    /*  147 */ "eglCompositorSetWindowAttributesEXT",
    /*  148 */ "eglCompositorBindTexWindowEXT",
    /*  149 */ "eglCompositorSetSizeEXT",
    /*  150 */ "eglCompositorSwapPolicyEXT",
    /*  151 */ "eglQuerySupportedCompressionRatesEXT",
    /*  152 */ "eglBindWaylandDisplayWL",
    /*  153 */ "eglUnbindWaylandDisplayWL",
    /*  154 */ "eglQueryWaylandBufferWL",
    /*  155 */ "eglCreateWaylandBufferFromImageWL",
    /*  156 */ "eglQueryDeviceBinaryEXT",
    /*  157 */ "eglDestroyDisplayEXT",
    /*  158 */ "eglCreateDeviceANGLE",
    /*  159 */ "eglReleaseDeviceANGLE",
    /*  160 */ "eglQueryStringiANGLE",
    /*  161 */ "eglQueryDisplayAttribANGLE",
    /*  162 */ "eglAcquireExternalContextANGLE",
    /*  163 */ "eglReleaseExternalContextANGLE",
    /*  164 */ "eglCreateStreamProducerD3DTextureANGLE",
    /*  165 */ "eglStreamPostD3DTextureANGLE",
    /*  166 */ "eglGetSyncValuesCHROMIUM",
    /*  167 */ "eglProgramCacheGetAttribANGLE",
    /*  168 */ "eglProgramCacheQueryANGLE",
    /*  169 */ "eglProgramCachePopulateANGLE",
    /*  170 */ "eglProgramCacheResizeANGLE",
    /*  171 */ "eglWaitUntilWorkScheduledANGLE",
    /*  172 */ "eglPrepareSwapBuffersANGLE",
    /*  173 */ "eglReleaseHighPowerGPUANGLE",
    /*  174 */ "eglReacquireHighPowerGPUANGLE",
    /*  175 */ "eglHandleGPUSwitchANGLE",
    /*  176 */ "eglForceGPUSwitchANGLE",
    /*  177 */ "eglExportVkImageANGLE",
    /*  178 */ "eglLockVulkanQueueANGLE",
    /*  179 */ "eglUnlockVulkanQueueANGLE",
    /*  180 */ "eglCopyMetalSharedEventANGLE",
    /*  181 */ "eglSetValidationEnabledANGLE"
};

static const GladPfnRange_t GLAD_EGL_feature_pfn_ranges[] = {
    /* EGL_VERSION_1_0 */
    {    0,    0,   24 },

    /* EGL_VERSION_1_1 */
    {    1,   24,    4 },

    /* EGL_VERSION_1_2 */
    {    2,   28,    5 },

    /* EGL_VERSION_1_4 */
    {    4,   33,    1 },

    /* EGL_VERSION_1_5 */
    {    5,   34,   10 },
};

static const GladPfnRange_t GLAD_EGL_ext_pfn_ranges[] = {
    /* EGL_ANDROID_blob_cache */
    {    1,   44,    1 },

    /* EGL_ANDROID_create_native_client_buffer */
    {    2,   45,    1 },

    /* EGL_ANDROID_get_frame_timestamps */
    {    5,   49,    5 },

    /* EGL_ANDROID_get_native_client_buffer */
    {    6,   46,    1 },

    /* EGL_ANDROID_native_fence_sync */
    {    8,   47,    1 },

    /* EGL_ANDROID_presentation_time */
    {    9,   48,    1 },

    /* EGL_ANGLE_device_creation */
    {   22,  158,    2 },

    /* EGL_ANGLE_device_vulkan */
    {   28,  178,    2 },

    /* EGL_ANGLE_external_context_and_surface */
    {   34,  162,    2 },

    /* EGL_ANGLE_feature_control */
    {   35,  160,    2 },

    /* EGL_ANGLE_metal_shared_event_sync */
    {   41,  180,    1 },

    /* EGL_ANGLE_no_error */
    {   43,  181,    1 },

    /* EGL_ANGLE_power_preference */
    {   59,  173,    4 },

    /* EGL_ANGLE_prepare_swap_buffers */
    {   60,  172,    1 },

    /* EGL_ANGLE_program_cache_control */
    {   61,  167,    4 },

    /* EGL_ANGLE_query_surface_pointer */
    {   62,   54,    1 },

    /* EGL_ANGLE_stream_producer_d3d_texture */
    {   64,  164,    2 },

    /* EGL_ANGLE_sync_control_rate */
    {   67,   55,    1 },

    /* EGL_ANGLE_vulkan_image */
    {   69,  177,    1 },

    /* EGL_ANGLE_wait_until_work_scheduled */
    {   70,  171,    1 },

    /* EGL_CHROMIUM_sync_control */
    {   76,  166,    1 },

    /* EGL_EXT_client_sync */
    {   80,   56,    1 },

    /* EGL_EXT_compositor */
    {   81,  144,    7 },

    /* EGL_EXT_device_base */
    {   84,   57,    4 },

    /* EGL_EXT_device_enumeration */
    {   87,   59,    1 },

    /* EGL_EXT_device_persistent_id */
    {   89,  156,    1 },

    /* EGL_EXT_device_query */
    {   90,   57,    2 },
    {   90,   60,    1 },

    /* EGL_EXT_display_alloc */
    {   92,  157,    1 },

    /* EGL_EXT_image_dma_buf_import_modifiers */
    {  103,   61,    2 },

    /* EGL_EXT_output_base */
    {  107,   63,    8 },

    /* EGL_EXT_platform_base */
    {  111,   71,    3 },

    /* EGL_EXT_stream_consumer_egloutput */
    {  120,   74,    1 },

    /* EGL_EXT_surface_compression */
    {  123,  151,    1 },

    /* EGL_EXT_swap_buffers_with_damage */
    {  124,   75,    1 },

    /* EGL_EXT_sync_reuse */
    {  125,   76,    1 },

    /* EGL_HI_clientpixmap */
    {  127,   77,    1 },

    /* EGL_KHR_cl_event2 */
    {  132,   78,    1 },

    /* EGL_KHR_debug */
    {  138,   79,    3 },

    /* EGL_KHR_display_reference */
    {  139,   82,    1 },

    /* EGL_KHR_fence_sync */
    {  140,   83,    4 },

    /* EGL_KHR_image */
    {  147,   87,    2 },

    /* EGL_KHR_image_base */
    {  148,   87,    2 },

    /* EGL_KHR_lock_surface */
    {  150,   89,    2 },

    /* EGL_KHR_lock_surface3 */
    {  152,   89,    3 },

    /* EGL_KHR_partial_update */
    {  155,   92,    1 },

    /* EGL_KHR_reusable_sync */
    {  160,   83,    4 },
    {  160,   93,    1 },

    /* EGL_KHR_stream */
    {  161,   94,    5 },

    /* EGL_KHR_stream_attrib */
    {  162,   99,    5 },

    /* EGL_KHR_stream_consumer_gltexture */
    {  163,  104,    3 },

    /* EGL_KHR_stream_cross_process_fd */
    {  164,  107,    2 },

    /* EGL_KHR_stream_fifo */
    {  165,  109,    1 },

    /* EGL_KHR_stream_producer_eglsurface */
    {  167,  110,    1 },

    /* EGL_KHR_swap_buffers_with_damage */
    {  169,  111,    1 },

    /* EGL_KHR_wait_sync */
    {  171,  112,    1 },

    /* EGL_MESA_drm_image */
    {  172,  113,    2 },

    /* EGL_MESA_image_dma_buf_export */
    {  173,  115,    2 },

    /* EGL_MESA_query_driver */
    {  176,  117,    2 },

    /* EGL_NOK_swap_region */
    {  177,  119,    1 },

    /* EGL_NOK_swap_region2 */
    {  178,  120,    1 },

    /* EGL_NV_native_query */
    {  187,  121,    3 },

    /* EGL_NV_post_sub_buffer */
    {  189,  124,    1 },

    /* EGL_NV_stream_consumer_eglimage */
    {  192,  126,    4 },

    /* EGL_NV_stream_consumer_gltexture_yuv */
    {  194,  125,    1 },

    /* EGL_NV_stream_flush */
    {  203,  130,    1 },

    /* EGL_NV_stream_metadata */
    {  205,  131,    3 },

    /* EGL_NV_stream_reset */
    {  208,  134,    1 },

    /* EGL_NV_stream_sync */
    {  212,  135,    1 },

    /* EGL_NV_sync */
    {  213,  136,    6 },

    /* EGL_NV_system_time */
    {  214,  142,    2 },

    /* EGL_WL_bind_wayland_display */
    {  220,  152,    3 },

    /* EGL_WL_create_wayland_buffer_from_image */
    {  221,  155,    1 },
};

static uint64_t GLAD_EGL_ext_hashes[] = {
    /*    0 */ 0x2253fd149000c540, /* EGL_ANDROID_GLES_layers */
    /*    1 */ 0xb309a80c1c4fc565, /* EGL_ANDROID_blob_cache */
    /*    2 */ 0x88e2a3925c1f8e55, /* EGL_ANDROID_create_native_client_buffer */
    /*    3 */ 0xe9b9bdc50ba8347c, /* EGL_ANDROID_framebuffer_target */
    /*    4 */ 0xd7ca0046d8e351bd, /* EGL_ANDROID_front_buffer_auto_refresh */
    /*    5 */ 0x16293db95b2e6807, /* EGL_ANDROID_get_frame_timestamps */
    /*    6 */ 0x1d1cb192f9421f4c, /* EGL_ANDROID_get_native_client_buffer */
    /*    7 */ 0xd2d9e8394e86467a, /* EGL_ANDROID_image_native_buffer */
    /*    8 */ 0x7e099daa98cd547e, /* EGL_ANDROID_native_fence_sync */
    /*    9 */ 0xe3ea63f73a400476, /* EGL_ANDROID_presentation_time */
    /*   10 */ 0x3cc398fae4c2292e, /* EGL_ANDROID_recordable */
    /*   11 */ 0xd798697a922f4f6f, /* EGL_ANDROID_telemetry_hint */
    /*   12 */ 0xd59b8dcdd4961074, /* EGL_ANGLE_colorspace_attribute_passthrough */
    /*   13 */ 0xe34ca55588e959e9, /* EGL_ANGLE_context_virtualization */
    /*   14 */ 0x5ee453db857b3c29, /* EGL_ANGLE_create_context_backwards_compatible */
    /*   15 */ 0xf2594fbcdfa3f545, /* EGL_ANGLE_create_context_client_arrays */
    /*   16 */ 0x5f5244f40c7ef900, /* EGL_ANGLE_create_context_extensions_enabled */
    /*   17 */ 0x4eac032f78eb1b97, /* EGL_ANGLE_create_context_webgl_compatibility */
    /*   18 */ 0x3db394a57b9600ed, /* EGL_ANGLE_create_surface_swap_interval */
    /*   19 */ 0x63dc3010a72f0f41, /* EGL_ANGLE_d3d_share_handle_client_buffer */
    /*   20 */ 0x008d04b1748738c1, /* EGL_ANGLE_d3d_texture_client_buffer */
    /*   21 */ 0xb9c6689d871a8219, /* EGL_ANGLE_device_cgl */
    /*   22 */ 0xe481bb03dc3ffd32, /* EGL_ANGLE_device_creation */
    /*   23 */ 0xa48498cc85257b13, /* EGL_ANGLE_device_d3d */
    /*   24 */ 0xd669f40f3670027e, /* EGL_ANGLE_device_d3d11 */
    /*   25 */ 0x03032fed28369f5f, /* EGL_ANGLE_device_d3d9 */
    /*   26 */ 0x22f96d8668d51351, /* EGL_ANGLE_device_eagl */
    /*   27 */ 0x00ba7a7f1c36e9e4, /* EGL_ANGLE_device_metal */
    /*   28 */ 0x6f356a60670d8e5a, /* EGL_ANGLE_device_vulkan */
    /*   29 */ 0xc9df550ac4a1ec30, /* EGL_ANGLE_direct_composition */
    /*   30 */ 0x00a9cc6756852346, /* EGL_ANGLE_display_power_preference */
    /*   31 */ 0xed1190e49710ebde, /* EGL_ANGLE_display_semaphore_share_group */
    /*   32 */ 0x2c22f1ea2f02edae, /* EGL_ANGLE_display_texture_share_group */
    /*   33 */ 0xc03ef8c49f8daf6e, /* EGL_ANGLE_experimental_present_path */
    /*   34 */ 0x1160c225fe2a6bf5, /* EGL_ANGLE_external_context_and_surface */
    /*   35 */ 0xf136655b938cfef7, /* EGL_ANGLE_feature_control */
    /*   36 */ 0x18d0970ca7b4c268, /* EGL_ANGLE_global_fence_sync */
    /*   37 */ 0x8247503770574a19, /* EGL_ANGLE_iosurface_client_buffer */
    /*   38 */ 0x2050b7157f814d10, /* EGL_ANGLE_keyed_mutex */
    /*   39 */ 0x3385337af72503e9, /* EGL_ANGLE_memory_usage_report */
    /*   40 */ 0x5027858c4c30d226, /* EGL_ANGLE_metal_create_context_ownership_identity */
    /*   41 */ 0x6e333abff6cec928, /* EGL_ANGLE_metal_shared_event_sync */
    /*   42 */ 0xea85ee216b66aed6, /* EGL_ANGLE_metal_texture_client_buffer */
    /*   43 */ 0x69ec6f07eb567773, /* EGL_ANGLE_no_error */
    /*   44 */ 0x0e642f860b2670f4, /* EGL_ANGLE_platform_angle */
    /*   45 */ 0xb3c6378facb30b47, /* EGL_ANGLE_platform_angle_d3d */
    /*   46 */ 0x67363c4648bf01a6, /* EGL_ANGLE_platform_angle_d3d11on12 */
    /*   47 */ 0x7404e65415e0cf49, /* EGL_ANGLE_platform_angle_d3d_luid */
    /*   48 */ 0x5b49c1a91e2bcce3, /* EGL_ANGLE_platform_angle_device_context_volatile_cgl */
    /*   49 */ 0xf27d356bb04d147d, /* EGL_ANGLE_platform_angle_device_context_volatile_eagl */
    /*   50 */ 0x1d4a1428061a339a, /* EGL_ANGLE_platform_angle_device_id */
    /*   51 */ 0xbe47353c1f13390b, /* EGL_ANGLE_platform_angle_device_type_egl */
    /*   52 */ 0xe9d3e98ad0d51659, /* EGL_ANGLE_platform_angle_device_type_swiftshader */
    /*   53 */ 0x98c1482cf6675807, /* EGL_ANGLE_platform_angle_metal */
    /*   54 */ 0x6ab80514da15b6f9, /* EGL_ANGLE_platform_angle_null */
    /*   55 */ 0xb419931c39c7f38a, /* EGL_ANGLE_platform_angle_opengl */
    /*   56 */ 0xb2ad9cccda275eb4, /* EGL_ANGLE_platform_angle_vulkan */
    /*   57 */ 0x76ecae883c1293e2, /* EGL_ANGLE_platform_angle_vulkan_device_uuid */
    /*   58 */ 0x2d155ccb3d2e416d, /* EGL_ANGLE_platform_angle_webgpu */
    /*   59 */ 0xaf2ad94baa465742, /* EGL_ANGLE_power_preference */
    /*   60 */ 0x41534601630f79ce, /* EGL_ANGLE_prepare_swap_buffers */
    /*   61 */ 0x15c4d55f4f359f01, /* EGL_ANGLE_program_cache_control */
    /*   62 */ 0x655dcac0071412b7, /* EGL_ANGLE_query_surface_pointer */
    /*   63 */ 0xbec48c7959021479, /* EGL_ANGLE_robust_resource_initialization */
    /*   64 */ 0x9e02c97224491c29, /* EGL_ANGLE_stream_producer_d3d_texture */
    /*   65 */ 0x460ce0075e78a2bd, /* EGL_ANGLE_surface_d3d_texture_2d_share_handle */
    /*   66 */ 0xa388335593ecba25, /* EGL_ANGLE_surface_orientation */
    /*   67 */ 0xcbc83f2fb8143390, /* EGL_ANGLE_sync_control_rate */
    /*   68 */ 0x9b7afb42d23ff24a, /* EGL_ANGLE_vulkan_display */
    /*   69 */ 0x3b9d20f1e7cea30c, /* EGL_ANGLE_vulkan_image */
    /*   70 */ 0x32f27a4c7977f1cc, /* EGL_ANGLE_wait_until_work_scheduled */
    /*   71 */ 0x584d724a2585416b, /* EGL_ANGLE_window_fixed_size */
    /*   72 */ 0x7fd85a1fe267fe03, /* EGL_ANGLE_x11_visual */
    /*   73 */ 0x79e92599e5906543, /* EGL_ARM_image_format */
    /*   74 */ 0xe6b4aba5bdfeb761, /* EGL_ARM_implicit_external_sync */
    /*   75 */ 0xae00b1c9df43676f, /* EGL_ARM_pixmap_multisample_discard */
    /*   76 */ 0xff8aede3988df0ec, /* EGL_CHROMIUM_sync_control */
    /*   77 */ 0x9c662d7d2c258a50, /* EGL_EXT_bind_to_front */
    /*   78 */ 0x2aa08328d074a816, /* EGL_EXT_buffer_age */
    /*   79 */ 0xa31e0274c2bcafb4, /* EGL_EXT_client_extensions */
    /*   80 */ 0x0391123aa67cc9fd, /* EGL_EXT_client_sync */
    /*   81 */ 0x7ad217dadabe87cc, /* EGL_EXT_compositor */
    /*   82 */ 0x7a089e984094346a, /* EGL_EXT_config_select_group */
    /*   83 */ 0x7150da6f49b30f3e, /* EGL_EXT_create_context_robustness */
    /*   84 */ 0x2f6c882c1eab9296, /* EGL_EXT_device_base */
    /*   85 */ 0x25ef29d5ba78dacb, /* EGL_EXT_device_drm */
    /*   86 */ 0x85d84ed980a0f6c3, /* EGL_EXT_device_drm_render_node */
    /*   87 */ 0xbf886c3682e570aa, /* EGL_EXT_device_enumeration */
    /*   88 */ 0xbb95b050ecd18b71, /* EGL_EXT_device_openwf */
    /*   89 */ 0x25e4685edc9371c5, /* EGL_EXT_device_persistent_id */
    /*   90 */ 0x4c3836479bf75ba3, /* EGL_EXT_device_query */
    /*   91 */ 0x0ec61ed2c29b6b7e, /* EGL_EXT_device_query_name */
    /*   92 */ 0xdbf00a0a59a03004, /* EGL_EXT_display_alloc */
    /*   93 */ 0x1a98bf220bf010e1, /* EGL_EXT_explicit_device */
    /*   94 */ 0x375b95889c713c9a, /* EGL_EXT_gl_colorspace_bt2020_hlg */
    /*   95 */ 0x5091e9def2327eea, /* EGL_EXT_gl_colorspace_bt2020_linear */
    /*   96 */ 0xfc5bf7ce45097f02, /* EGL_EXT_gl_colorspace_bt2020_pq */
    /*   97 */ 0xd63b77d8efe7c73e, /* EGL_EXT_gl_colorspace_display_p3 */
    /*   98 */ 0x24c124c0512e760a, /* EGL_EXT_gl_colorspace_display_p3_linear */
    /*   99 */ 0x46817a7a0934b21a, /* EGL_EXT_gl_colorspace_display_p3_passthrough */
    /*  100 */ 0x01e6ab8e204224c3, /* EGL_EXT_gl_colorspace_scrgb */
    /*  101 */ 0x9d59eeae4c92e9f7, /* EGL_EXT_gl_colorspace_scrgb_linear */
    /*  102 */ 0x0c3a9519d769be90, /* EGL_EXT_image_dma_buf_import */
    /*  103 */ 0xa09fd39f9f1158a7, /* EGL_EXT_image_dma_buf_import_modifiers */
    /*  104 */ 0x476226fa1413890a, /* EGL_EXT_image_gl_colorspace */
    /*  105 */ 0xa5c94b3fdd6261da, /* EGL_EXT_image_implicit_sync_control */
    /*  106 */ 0x9f0bdd4dde93e968, /* EGL_EXT_multiview_window */
    /*  107 */ 0xd324b54bf6a35048, /* EGL_EXT_output_base */
    /*  108 */ 0x0659adf490093fcb, /* EGL_EXT_output_drm */
    /*  109 */ 0x53a0e0b8eb5f3f00, /* EGL_EXT_output_openwf */
    /*  110 */ 0xefb059a6e6841776, /* EGL_EXT_pixel_format_float */
    /*  111 */ 0xa841b196d3768c24, /* EGL_EXT_platform_base */
    /*  112 */ 0x8df4a934a55860db, /* EGL_EXT_platform_device */
    /*  113 */ 0x27716290eb920120, /* EGL_EXT_platform_wayland */
    /*  114 */ 0xe548f3fc71409c63, /* EGL_EXT_platform_x11 */
    /*  115 */ 0x6b5d9de25dfe7eba, /* EGL_EXT_platform_xcb */
    /*  116 */ 0x5e7a56764d6c44b1, /* EGL_EXT_present_opaque */
    /*  117 */ 0x91cb4ebfba10a35f, /* EGL_EXT_protected_content */
    /*  118 */ 0x83f096c0f29ebb18, /* EGL_EXT_protected_surface */
    /*  119 */ 0xfd8d9ef9e9360c00, /* EGL_EXT_query_reset_notification_strategy */
    /*  120 */ 0xfbac73bd87a06d67, /* EGL_EXT_stream_consumer_egloutput */
    /*  121 */ 0x5654a8bc12eeebab, /* EGL_EXT_surface_CTA861_3_metadata */
    /*  122 */ 0x283ef3c9e93fa780, /* EGL_EXT_surface_SMPTE2086_metadata */
    /*  123 */ 0x46e2ba77cc14c6da, /* EGL_EXT_surface_compression */
    /*  124 */ 0xff56e7e2acee3106, /* EGL_EXT_swap_buffers_with_damage */
    /*  125 */ 0x42a3ca98a3fcecb6, /* EGL_EXT_sync_reuse */
    /*  126 */ 0x451b691d8d24df6c, /* EGL_EXT_yuv_surface */
    /*  127 */ 0xdaf189f7653009bf, /* EGL_HI_clientpixmap */
    /*  128 */ 0x066d89176cab3c2c, /* EGL_HI_colorformats */
    /*  129 */ 0x0a76d8252afa230a, /* EGL_IMG_context_priority */
    /*  130 */ 0x7084567bc80e8320, /* EGL_IMG_image_plane_attribs */
    /*  131 */ 0x0b5d7506753789de, /* EGL_KHR_cl_event */
    /*  132 */ 0x70fce70cba139c12, /* EGL_KHR_cl_event2 */
    /*  133 */ 0xef7264f8eef3335b, /* EGL_KHR_client_get_all_proc_addresses */
    /*  134 */ 0x270d8abedb2d3a6d, /* EGL_KHR_config_attribs */
    /*  135 */ 0xda20b827ff8ca001, /* EGL_KHR_context_flush_control */
    /*  136 */ 0x4e16c8c1f6a8131c, /* EGL_KHR_create_context */
    /*  137 */ 0x7b8ef4b379c8f0fd, /* EGL_KHR_create_context_no_error */
    /*  138 */ 0x5b61d2012f7861b3, /* EGL_KHR_debug */
    /*  139 */ 0xfb4d4422d07bc81c, /* EGL_KHR_display_reference */
    /*  140 */ 0x3fc685858cb02200, /* EGL_KHR_fence_sync */
    /*  141 */ 0xcc74201669ca5b5d, /* EGL_KHR_get_all_proc_addresses */
    /*  142 */ 0x0089c927779cc6ef, /* EGL_KHR_gl_colorspace */
    /*  143 */ 0xf2fdf97c1361d5d7, /* EGL_KHR_gl_renderbuffer_image */
    /*  144 */ 0x16756bf4b09c5e40, /* EGL_KHR_gl_texture_2D_image */
    /*  145 */ 0x38fe09b43c8ef819, /* EGL_KHR_gl_texture_3D_image */
    /*  146 */ 0x8da10d2afff88da2, /* EGL_KHR_gl_texture_cubemap_image */
    /*  147 */ 0x871bd75821391394, /* EGL_KHR_image */
    /*  148 */ 0xa2aecd33728540cb, /* EGL_KHR_image_base */
    /*  149 */ 0x6d3e7071805da5a8, /* EGL_KHR_image_pixmap */
    /*  150 */ 0xd1965fc59df1967c, /* EGL_KHR_lock_surface */
    /*  151 */ 0x607598bc0d7426f5, /* EGL_KHR_lock_surface2 */
    /*  152 */ 0xc5c0850bfdef920f, /* EGL_KHR_lock_surface3 */
    /*  153 */ 0xf2c65c6b58412a19, /* EGL_KHR_mutable_render_buffer */
    /*  154 */ 0xb04bf399be660bca, /* EGL_KHR_no_config_context */
    /*  155 */ 0xbf10c896f39ac381, /* EGL_KHR_partial_update */
    /*  156 */ 0x1b60d04af505e88c, /* EGL_KHR_platform_android */
    /*  157 */ 0x92732717613804d7, /* EGL_KHR_platform_gbm */
    /*  158 */ 0xa9c339bb0bd9f8ff, /* EGL_KHR_platform_wayland */
    /*  159 */ 0xb95b474e87d914c0, /* EGL_KHR_platform_x11 */
    /*  160 */ 0x3e707e46a988246f, /* EGL_KHR_reusable_sync */
    /*  161 */ 0x16184f4f924509ef, /* EGL_KHR_stream */
    /*  162 */ 0x9d0b59cf206f7842, /* EGL_KHR_stream_attrib */
    /*  163 */ 0xd9b572ac9eb89474, /* EGL_KHR_stream_consumer_gltexture */
    /*  164 */ 0x6e523fb6f05a3d29, /* EGL_KHR_stream_cross_process_fd */
    /*  165 */ 0x3114241b811aadf2, /* EGL_KHR_stream_fifo */
    /*  166 */ 0x4e02a91ae238a029, /* EGL_KHR_stream_producer_aldatalocator */
    /*  167 */ 0x75e923758d9b47fb, /* EGL_KHR_stream_producer_eglsurface */
    /*  168 */ 0x98778891a458759f, /* EGL_KHR_surfaceless_context */
    /*  169 */ 0x836da10ce92250ef, /* EGL_KHR_swap_buffers_with_damage */
    /*  170 */ 0xc795b75646aecc5b, /* EGL_KHR_vg_parent_image */
    /*  171 */ 0x76eb9817e8dc6c57, /* EGL_KHR_wait_sync */
    /*  172 */ 0x8a02851eceb4e60b, /* EGL_MESA_drm_image */
    /*  173 */ 0xff40140d7e6b5b22, /* EGL_MESA_image_dma_buf_export */
    /*  174 */ 0xcbf9865290d1d737, /* EGL_MESA_platform_gbm */
    /*  175 */ 0xa718f1a00dfc77b2, /* EGL_MESA_platform_surfaceless */
    /*  176 */ 0x205a0c44642ecfe4, /* EGL_MESA_query_driver */
    /*  177 */ 0xc6c6646757ff2eb0, /* EGL_NOK_swap_region */
    /*  178 */ 0xcacecd1071a7c53d, /* EGL_NOK_swap_region2 */
    /*  179 */ 0x140a1d4d56e89998, /* EGL_NOK_texture_from_pixmap */
    /*  180 */ 0x53d1f2866df11721, /* EGL_NV_3dvision_surface */
    /*  181 */ 0x87d534f485d23e03, /* EGL_NV_context_priority_realtime */
    /*  182 */ 0x29d02d6b41d01c44, /* EGL_NV_coverage_sample */
    /*  183 */ 0xbf4228511c15c43e, /* EGL_NV_coverage_sample_resolve */
    /*  184 */ 0xba24ab7c282aa98c, /* EGL_NV_cuda_event */
    /*  185 */ 0x4f20169819f31a19, /* EGL_NV_depth_nonlinear */
    /*  186 */ 0xb32a3dd6b03226f2, /* EGL_NV_device_cuda */
    /*  187 */ 0x797c903a522c4c75, /* EGL_NV_native_query */
    /*  188 */ 0xb151fe3f08ba15f6, /* EGL_NV_post_convert_rounding */
    /*  189 */ 0xaad3806034d0954d, /* EGL_NV_post_sub_buffer */
    /*  190 */ 0x37a228d0850f64a1, /* EGL_NV_quadruple_buffer */
    /*  191 */ 0x74855b1caf0bb727, /* EGL_NV_robustness_video_memory_purge */
    /*  192 */ 0x2db9bc2b87115201, /* EGL_NV_stream_consumer_eglimage */
    /*  193 */ 0xd01bc63b758f4cb9, /* EGL_NV_stream_consumer_eglimage_use_scanout_attrib */
    /*  194 */ 0x2baced719176deed, /* EGL_NV_stream_consumer_gltexture_yuv */
    /*  195 */ 0xfc105cd6c3f68dbe, /* EGL_NV_stream_cross_display */
    /*  196 */ 0x363e000d3383a473, /* EGL_NV_stream_cross_object */
    /*  197 */ 0xac63132cd757c637, /* EGL_NV_stream_cross_partition */
    /*  198 */ 0x2821ab7eeb491706, /* EGL_NV_stream_cross_process */
    /*  199 */ 0x97b15fd0e09adf80, /* EGL_NV_stream_cross_system */
    /*  200 */ 0x7ae84605ae3ae44a, /* EGL_NV_stream_dma */
    /*  201 */ 0x450721831a3bcf73, /* EGL_NV_stream_fifo_next */
    /*  202 */ 0x5dd63931ba6563fb, /* EGL_NV_stream_fifo_synchronous */
    /*  203 */ 0x33597e019cc7811d, /* EGL_NV_stream_flush */
    /*  204 */ 0x0c5d5d4b9e76b0d3, /* EGL_NV_stream_frame_limits */
    /*  205 */ 0xd899fb78ae205e27, /* EGL_NV_stream_metadata */
    /*  206 */ 0xcb6e884a7e412a07, /* EGL_NV_stream_origin */
    /*  207 */ 0x817f41736f96de51, /* EGL_NV_stream_remote */
    /*  208 */ 0x6ad8d08948340894, /* EGL_NV_stream_reset */
    /*  209 */ 0xb46eaf4ddee294f4, /* EGL_NV_stream_socket */
    /*  210 */ 0x7d669bb43a324d63, /* EGL_NV_stream_socket_inet */
    /*  211 */ 0x55bf7befb5997e09, /* EGL_NV_stream_socket_unix */
    /*  212 */ 0xdfb98789892372eb, /* EGL_NV_stream_sync */
    /*  213 */ 0x5557f40f2ef2066c, /* EGL_NV_sync */
    /*  214 */ 0xe1a6732356a0f69f, /* EGL_NV_system_time */
    /*  215 */ 0xf2ec54e65029ed17, /* EGL_NV_triple_buffer */
    /*  216 */ 0xaf15d314b7e55c0f, /* EGL_QNX_image_native_buffer */
    /*  217 */ 0x8efc13d2448ab5b1, /* EGL_QNX_platform_screen */
    /*  218 */ 0x71dbd1513b2ad7e5, /* EGL_TIZEN_image_native_buffer */
    /*  219 */ 0x6d7cb4f9ba09cb5d, /* EGL_TIZEN_image_native_surface */
    /*  220 */ 0xc81b6f913740e456, /* EGL_WL_bind_wayland_display */
    /*  221 */ 0xa3002402543e70a5  /* EGL_WL_create_wayland_buffer_from_image */
};

static void glad_egl_load_pfn_range(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr, uint16_t pfnStart, uint32_t numPfns)
{
    uint32_t pfnIdx;

    #ifdef __clang__
    #pragma nounroll
    #endif
    for (pfnIdx = pfnStart; pfnIdx < pfnStart + numPfns; ++pfnIdx) {
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static uint32_t glad_egl_resolve_alias_group(GladEGLContext *context, const GladAliasPair_t *pairs, uint32_t start_idx, uint32_t total_count) {
    void **pfnArray = context->pfnArray;
    uint16_t canonical_idx = pairs[start_idx].first;

    /* Find the end of this group (consecutive pairs with same canonical index) */
    uint32_t end_idx = start_idx;
    while (end_idx < total_count && pairs[end_idx].first == canonical_idx) {
        end_idx++;
    }

    /* Pass 1: Find any loaded secondary for this canonical */
    void *canonical_ptr = pfnArray[canonical_idx];
    if (canonical_ptr == NULL) {
        for (uint32_t i = start_idx; i < end_idx; ++i) {
            if (pfnArray[pairs[i].second] != NULL) {
                canonical_ptr = pfnArray[pairs[i].second];
                pfnArray[canonical_idx] = canonical_ptr;
                break;
            }
        }
    }

    /* Pass 2: Populate unloaded secondaries */
    if (canonical_ptr != NULL) {
        for (uint32_t i = start_idx; i < end_idx; ++i) {
            if (pfnArray[pairs[i].second] == NULL) {
                pfnArray[pairs[i].second] = canonical_ptr;
            }
        }
    }

    return end_idx - 1;  /* Return index of last processed pair */
}

static void glad_egl_resolve_aliases(GladEGLContext *context) {
    static const GladAliasPair_t s_aliases[] = {
        {   36,   85 }, /* eglClientWaitSync and eglClientWaitSyncKHR */
        {   34,   78 }, /* eglCreateSync and eglCreateSync64KHR */
        {   39,   88 }, /* eglDestroyImage and eglDestroyImageKHR */
        {   35,   84 }, /* eglDestroySync and eglDestroySyncKHR */
        {  131,   60 }, /* eglQueryDisplayAttribNV and eglQueryDisplayAttribEXT */
        {  131,   82 }, /* eglQueryDisplayAttribNV and eglQueryDisplayAttribKHR */
    };
    uint32_t i;

    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_aliases); ++i) {
        i = glad_egl_resolve_alias_group(context, s_aliases, i, GLAD_ARRAYSIZE(s_aliases));
    }
}

static int glad_egl_get_extensions(GladEGLContext *context, EGLDisplay display, uint64_t **out_exts, uint32_t *out_num_exts) {
    size_t clientLen, displayLen;
    char *concat;
    uint32_t num_exts = 0, j = 0, len = 0;
    uint64_t *exts = NULL;
    const char *cur = NULL;
    const char *next = NULL;

    const char *clientExtensions = context->QueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
    const char *displayExtensions = (display == EGL_NO_DISPLAY) ? "" : context->QueryString(display, EGL_EXTENSIONS);

    if (!clientExtensions) return 0;
    if (!displayExtensions) return 0;

    clientLen = strlen(clientExtensions);
    displayLen = strlen(displayExtensions);

    concat = (char *)malloc(clientLen + displayLen + 2);
    if (!concat) return 0;

    concat[0] = 0;
    strcat(concat, clientExtensions);
    if (displayLen) {
        if (concat[clientLen - 1] != ' ')
            strcat(concat, " ");
        strcat(concat, displayExtensions);
    }

    /* This is done in two passes. The first pass counts up the number of
    * extensions. The second pass copies them into an allocated block of memory. */
    for (j = 0; j < 2; ++j) {
        num_exts = 0;
        cur = concat;
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

    free(concat);

    qsort(exts, num_exts, sizeof(uint64_t), compare_uint64);

    *out_exts = exts;
    *out_num_exts = num_exts;

    return 1;
}

static int glad_egl_has_extension(uint64_t *exts, uint32_t num_exts, uint64_t extension) {
    return glad_hash_search(exts, num_exts, extension);
}

static GLADapiproc glad_egl_get_proc_from_userptr(void *userptr, const char *name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_egl_find_extensions_egl(GladEGLContext *context, EGLDisplay display) {
    uint64_t *exts = NULL;
    uint32_t num_exts = 0;
    uint32_t i;

    if (!glad_egl_get_extensions(context, display, &exts, &num_exts)) return 0;

    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_EGL_ext_hashes); ++i)
        context->extArray[i] = glad_egl_has_extension(exts, num_exts, GLAD_EGL_ext_hashes[i]);

    free(exts);
    return 1;
}

static int glad_egl_find_core_egl(GladEGLContext *context, EGLDisplay display) {
    int major, minor;
    unsigned short version_value;
    const char *version;

    if (display == NULL) {
        display = EGL_NO_DISPLAY; /* this is usually NULL, better safe than sorry */
    }

    version = context->QueryString(display, EGL_VERSION);
    (void) context->GetError();

    if (version == NULL) {
        major = 1;
        minor = 0;
    } else {
        GLAD_IMPL_UTIL_SSCANF(version, "%d.%d", &major, &minor);
    }

    version_value = (major << 8U) | minor;

    context->VERSION_1_0 = version_value >= 0x0100;
    context->VERSION_1_1 = version_value >= 0x0101;
    context->VERSION_1_2 = version_value >= 0x0102;
    context->VERSION_1_3 = version_value >= 0x0103;
    context->VERSION_1_4 = version_value >= 0x0104;
    context->VERSION_1_5 = version_value >= 0x0105;

    return GLAD_MAKE_VERSION(major, minor);
}

GLAD_NO_INLINE int gladLoadEGLContextUserPtr(GladEGLContext *context, EGLDisplay display, GLADuserptrloadfunc load, void *userptr) {
    int version;
    uint32_t i;

    context->GetDisplay = (PFNEGLGETDISPLAYPROC) load(userptr, "eglGetDisplay");
    context->GetCurrentDisplay = (PFNEGLGETCURRENTDISPLAYPROC) load(userptr, "eglGetCurrentDisplay");
    context->QueryString = (PFNEGLQUERYSTRINGPROC) load(userptr, "eglQueryString");
    context->GetError = (PFNEGLGETERRORPROC) load(userptr, "eglGetError");
    if (context->GetDisplay == NULL || context->GetCurrentDisplay == NULL || context->QueryString == NULL || context->GetError == NULL) return 0;

    version = glad_egl_find_core_egl(context, display);
    if (!version) return 0;

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_EGL_feature_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_EGL_feature_pfn_ranges[i];
        if (context->featArray[range->extension]) {
            glad_egl_load_pfn_range(context, load, userptr, range->start, range->count);
        }
    }

    if (!glad_egl_find_extensions_egl(context, display)) return 0;

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_EGL_ext_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_EGL_ext_pfn_ranges[i];
        if (context->extArray[range->extension]) {
            glad_egl_load_pfn_range(context, load, userptr, range->start, range->count);
        }
    }

    gladSetEGLContext(context);

    glad_egl_resolve_aliases(context);

    return version;
}

int gladLoadEGLUserPtr(EGLDisplay display, GLADuserptrloadfunc load, void *userptr) {
    return gladLoadEGLContextUserPtr(gladGetEGLContext(), display, load, userptr);
}

int gladLoadEGLContext(GladEGLContext *context, EGLDisplay display, GLADloadfunc load) {
    return gladLoadEGLContextUserPtr(context, display, glad_egl_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}

int gladLoadEGL(EGLDisplay display, GLADloadfunc load) {
    return gladLoadEGLContext(gladGetEGLContext(), display, load);
}

GladEGLContext* gladGetEGLContext() {
    return &glad_egl_context;
}

void gladSetEGLContext(GladEGLContext *context) {
    if (!context) return;
    if (&glad_egl_context == context) return;
    glad_egl_context = *context;
}


#ifdef GLAD_EGL

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

struct _glad_egl_userptr {
    void *handle;
    PFNEGLGETPROCADDRESSPROC get_proc_address_ptr;
};

static GLADapiproc glad_egl_get_proc(void *vuserptr, const char* name) {
    struct _glad_egl_userptr userptr = *(struct _glad_egl_userptr*) vuserptr;
    GLADapiproc result = NULL;

    result = glad_dlsym_handle(userptr.handle, name);
    if (result == NULL) {
        result = GLAD_GNUC_EXTENSION (GLADapiproc) userptr.get_proc_address_ptr(name);
    }

    return result;
}


static void* glad_egl_dlopen_handle(GladEGLContext *context) {
#if GLAD_PLATFORM_APPLE
    static const char *NAMES[] = {"libEGL.dylib"};
#elif GLAD_PLATFORM_WIN32
    static const char *NAMES[] = {"libEGL.dll", "EGL.dll"};
#else
    static const char *NAMES[] = {"libEGL.so.1", "libEGL.so"};
#endif

    if (context->glad_loader_handle == NULL) {
        context->glad_loader_handle = glad_get_dlopen_handle(NAMES, GLAD_ARRAYSIZE(NAMES));
    }

    return context->glad_loader_handle;
}

static struct _glad_egl_userptr glad_egl_build_userptr(void *handle) {
    struct _glad_egl_userptr userptr;
    userptr.handle = handle;
    userptr.get_proc_address_ptr = (PFNEGLGETPROCADDRESSPROC) glad_dlsym_handle(handle, "eglGetProcAddress");
    return userptr;
}

int gladLoaderLoadEGLContext(GladEGLContext *context, EGLDisplay display) {
    int version = 0;
    void *handle;
    int did_load = 0;
    struct _glad_egl_userptr userptr;

    did_load = context->glad_loader_handle == NULL;
    handle = glad_egl_dlopen_handle(context);
    if (handle) {
        userptr = glad_egl_build_userptr(handle);

        version = gladLoadEGLContextUserPtr(context, display, glad_egl_get_proc, &userptr);

        if (!version && did_load) {
            gladLoaderUnloadEGLContext(context);
        }
    }

    return version;
}

int gladLoaderLoadEGL(EGLDisplay display) {
    return gladLoaderLoadEGLContext(gladGetEGLContext(), display);
}

void gladLoaderResetEGL(void) {
    gladLoaderResetEGLContext(gladGetEGLContext());
}

void gladLoaderUnloadEGLContext(GladEGLContext *context) {
    if (context->glad_loader_handle != NULL) {
        glad_close_dlopen_handle(context->glad_loader_handle);
        context->glad_loader_handle = NULL;
    }

    gladLoaderResetEGLContext(context);
}

void gladLoaderUnloadEGL(void) {
    gladLoaderUnloadEGLContext(gladGetEGLContext());
}

void gladLoaderResetEGLContext(GladEGLContext *context) {
    memset(context, 0, sizeof(GladEGLContext));
}

#endif /* GLAD_EGL */

#ifdef __cplusplus
}
#endif
