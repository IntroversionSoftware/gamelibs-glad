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

#endif /* GLAD_IMPL_UTIL_C_ */

#ifndef GLAD_IMPL_UTIL_HASHSEARCH_C_
#define GLAD_IMPL_UTIL_HASHSEARCH_C_

GLAD_NO_INLINE static bool glad_hash_search(const uint64_t *arr, uint32_t size, uint64_t target) {
    /* This linear search works well with auto-vectorization, but it will scan
     * the entire array and not stop early on a match */
    uint32_t i;
    bool found = false;
    for (i = 0; i < size; ++i) {
        if (arr[i] == target)
            found = true;
    }
    return found;
}

GLAD_NO_INLINE static uint64_t glad_hash_string(const char *str, size_t length)
{
    return XXH3_64bits(str, length);
}

#endif /* GLAD_IMPL_HASHSEARCH_C_ */

#ifdef __cplusplus
extern "C" {
#endif

static const char *GLAD_EGL_fn_names[] = {
    /*    0 */ "eglAcquireExternalContextANGLE",
    /*    1 */ "eglBindAPI",
    /*    2 */ "eglBindTexImage",
    /*    3 */ "eglBindWaylandDisplayWL",
    /*    4 */ "eglChooseConfig",
    /*    5 */ "eglClientSignalSyncEXT",
    /*    6 */ "eglClientWaitSync",
    /*    7 */ "eglClientWaitSyncKHR",
    /*    8 */ "eglClientWaitSyncNV",
    /*    9 */ "eglCompositorBindTexWindowEXT",
    /*   10 */ "eglCompositorSetContextAttributesEXT",
    /*   11 */ "eglCompositorSetContextListEXT",
    /*   12 */ "eglCompositorSetSizeEXT",
    /*   13 */ "eglCompositorSetWindowAttributesEXT",
    /*   14 */ "eglCompositorSetWindowListEXT",
    /*   15 */ "eglCompositorSwapPolicyEXT",
    /*   16 */ "eglCopyBuffers",
    /*   17 */ "eglCopyMetalSharedEventANGLE",
    /*   18 */ "eglCreateContext",
    /*   19 */ "eglCreateDRMImageMESA",
    /*   20 */ "eglCreateDeviceANGLE",
    /*   21 */ "eglCreateFenceSyncNV",
    /*   22 */ "eglCreateImage",
    /*   23 */ "eglCreateImageKHR",
    /*   24 */ "eglCreateNativeClientBufferANDROID",
    /*   25 */ "eglCreatePbufferFromClientBuffer",
    /*   26 */ "eglCreatePbufferSurface",
    /*   27 */ "eglCreatePixmapSurface",
    /*   28 */ "eglCreatePixmapSurfaceHI",
    /*   29 */ "eglCreatePlatformPixmapSurface",
    /*   30 */ "eglCreatePlatformPixmapSurfaceEXT",
    /*   31 */ "eglCreatePlatformWindowSurface",
    /*   32 */ "eglCreatePlatformWindowSurfaceEXT",
    /*   33 */ "eglCreateStreamAttribKHR",
    /*   34 */ "eglCreateStreamFromFileDescriptorKHR",
    /*   35 */ "eglCreateStreamKHR",
    /*   36 */ "eglCreateStreamProducerD3DTextureANGLE",
    /*   37 */ "eglCreateStreamProducerSurfaceKHR",
    /*   38 */ "eglCreateStreamSyncNV",
    /*   39 */ "eglCreateSync",
    /*   40 */ "eglCreateSync64KHR",
    /*   41 */ "eglCreateSyncKHR",
    /*   42 */ "eglCreateWaylandBufferFromImageWL",
    /*   43 */ "eglCreateWindowSurface",
    /*   44 */ "eglDebugMessageControlKHR",
    /*   45 */ "eglDestroyContext",
    /*   46 */ "eglDestroyDisplayEXT",
    /*   47 */ "eglDestroyImage",
    /*   48 */ "eglDestroyImageKHR",
    /*   49 */ "eglDestroyStreamKHR",
    /*   50 */ "eglDestroySurface",
    /*   51 */ "eglDestroySync",
    /*   52 */ "eglDestroySyncKHR",
    /*   53 */ "eglDestroySyncNV",
    /*   54 */ "eglDupNativeFenceFDANDROID",
    /*   55 */ "eglExportDMABUFImageMESA",
    /*   56 */ "eglExportDMABUFImageQueryMESA",
    /*   57 */ "eglExportDRMImageMESA",
    /*   58 */ "eglExportVkImageANGLE",
    /*   59 */ "eglFenceNV",
    /*   60 */ "eglForceGPUSwitchANGLE",
    /*   61 */ "eglGetCompositorTimingANDROID",
    /*   62 */ "eglGetCompositorTimingSupportedANDROID",
    /*   63 */ "eglGetConfigAttrib",
    /*   64 */ "eglGetConfigs",
    /*   65 */ "eglGetCurrentContext",
    /*   66 */ "eglGetCurrentDisplay",
    /*   67 */ "eglGetCurrentSurface",
    /*   68 */ "eglGetDisplay",
    /*   69 */ "eglGetDisplayDriverConfig",
    /*   70 */ "eglGetDisplayDriverName",
    /*   71 */ "eglGetError",
    /*   72 */ "eglGetFrameTimestampSupportedANDROID",
    /*   73 */ "eglGetFrameTimestampsANDROID",
    /*   74 */ "eglGetMscRateANGLE",
    /*   75 */ "eglGetNativeClientBufferANDROID",
    /*   76 */ "eglGetNextFrameIdANDROID",
    /*   77 */ "eglGetOutputLayersEXT",
    /*   78 */ "eglGetOutputPortsEXT",
    /*   79 */ "eglGetPlatformDisplay",
    /*   80 */ "eglGetPlatformDisplayEXT",
    /*   81 */ "eglGetProcAddress",
    /*   82 */ "eglGetStreamFileDescriptorKHR",
    /*   83 */ "eglGetSyncAttrib",
    /*   84 */ "eglGetSyncAttribKHR",
    /*   85 */ "eglGetSyncAttribNV",
    /*   86 */ "eglGetSyncValuesCHROMIUM",
    /*   87 */ "eglGetSystemTimeFrequencyNV",
    /*   88 */ "eglGetSystemTimeNV",
    /*   89 */ "eglHandleGPUSwitchANGLE",
    /*   90 */ "eglInitialize",
    /*   91 */ "eglLabelObjectKHR",
    /*   92 */ "eglLockSurfaceKHR",
    /*   93 */ "eglMakeCurrent",
    /*   94 */ "eglOutputLayerAttribEXT",
    /*   95 */ "eglOutputPortAttribEXT",
    /*   96 */ "eglPostSubBufferNV",
    /*   97 */ "eglPrepareSwapBuffersANGLE",
    /*   98 */ "eglPresentationTimeANDROID",
    /*   99 */ "eglProgramCacheGetAttribANGLE",
    /*  100 */ "eglProgramCachePopulateANGLE",
    /*  101 */ "eglProgramCacheQueryANGLE",
    /*  102 */ "eglProgramCacheResizeANGLE",
    /*  103 */ "eglQueryAPI",
    /*  104 */ "eglQueryContext",
    /*  105 */ "eglQueryDebugKHR",
    /*  106 */ "eglQueryDeviceAttribEXT",
    /*  107 */ "eglQueryDeviceBinaryEXT",
    /*  108 */ "eglQueryDeviceStringEXT",
    /*  109 */ "eglQueryDevicesEXT",
    /*  110 */ "eglQueryDisplayAttribANGLE",
    /*  111 */ "eglQueryDisplayAttribEXT",
    /*  112 */ "eglQueryDisplayAttribKHR",
    /*  113 */ "eglQueryDisplayAttribNV",
    /*  114 */ "eglQueryDmaBufFormatsEXT",
    /*  115 */ "eglQueryDmaBufModifiersEXT",
    /*  116 */ "eglQueryNativeDisplayNV",
    /*  117 */ "eglQueryNativePixmapNV",
    /*  118 */ "eglQueryNativeWindowNV",
    /*  119 */ "eglQueryOutputLayerAttribEXT",
    /*  120 */ "eglQueryOutputLayerStringEXT",
    /*  121 */ "eglQueryOutputPortAttribEXT",
    /*  122 */ "eglQueryOutputPortStringEXT",
    /*  123 */ "eglQueryStreamAttribKHR",
    /*  124 */ "eglQueryStreamConsumerEventNV",
    /*  125 */ "eglQueryStreamKHR",
    /*  126 */ "eglQueryStreamMetadataNV",
    /*  127 */ "eglQueryStreamTimeKHR",
    /*  128 */ "eglQueryStreamu64KHR",
    /*  129 */ "eglQueryString",
    /*  130 */ "eglQueryStringiANGLE",
    /*  131 */ "eglQuerySupportedCompressionRatesEXT",
    /*  132 */ "eglQuerySurface",
    /*  133 */ "eglQuerySurface64KHR",
    /*  134 */ "eglQuerySurfacePointerANGLE",
    /*  135 */ "eglQueryWaylandBufferWL",
    /*  136 */ "eglReacquireHighPowerGPUANGLE",
    /*  137 */ "eglReleaseDeviceANGLE",
    /*  138 */ "eglReleaseExternalContextANGLE",
    /*  139 */ "eglReleaseHighPowerGPUANGLE",
    /*  140 */ "eglReleaseTexImage",
    /*  141 */ "eglReleaseThread",
    /*  142 */ "eglResetStreamNV",
    /*  143 */ "eglSetBlobCacheFuncsANDROID",
    /*  144 */ "eglSetDamageRegionKHR",
    /*  145 */ "eglSetStreamAttribKHR",
    /*  146 */ "eglSetStreamMetadataNV",
    /*  147 */ "eglSetValidationEnabledANGLE",
    /*  148 */ "eglSignalSyncKHR",
    /*  149 */ "eglSignalSyncNV",
    /*  150 */ "eglStreamAcquireImageNV",
    /*  151 */ "eglStreamAttribKHR",
    /*  152 */ "eglStreamConsumerAcquireAttribKHR",
    /*  153 */ "eglStreamConsumerAcquireKHR",
    /*  154 */ "eglStreamConsumerGLTextureExternalAttribsNV",
    /*  155 */ "eglStreamConsumerGLTextureExternalKHR",
    /*  156 */ "eglStreamConsumerOutputEXT",
    /*  157 */ "eglStreamConsumerReleaseAttribKHR",
    /*  158 */ "eglStreamConsumerReleaseKHR",
    /*  159 */ "eglStreamFlushNV",
    /*  160 */ "eglStreamImageConsumerConnectNV",
    /*  161 */ "eglStreamPostD3DTextureANGLE",
    /*  162 */ "eglStreamReleaseImageNV",
    /*  163 */ "eglSurfaceAttrib",
    /*  164 */ "eglSwapBuffers",
    /*  165 */ "eglSwapBuffersRegion2NOK",
    /*  166 */ "eglSwapBuffersRegionNOK",
    /*  167 */ "eglSwapBuffersWithDamageEXT",
    /*  168 */ "eglSwapBuffersWithDamageKHR",
    /*  169 */ "eglSwapBuffersWithFrameTokenANGLE",
    /*  170 */ "eglSwapInterval",
    /*  171 */ "eglTerminate",
    /*  172 */ "eglUnbindWaylandDisplayWL",
    /*  173 */ "eglUnlockSurfaceKHR",
    /*  174 */ "eglUnsignalSyncEXT",
    /*  175 */ "eglWaitClient",
    /*  176 */ "eglWaitGL",
    /*  177 */ "eglWaitNative",
    /*  178 */ "eglWaitSync",
    /*  179 */ "eglWaitSyncKHR",
    /*  180 */ "eglWaitUntilWorkScheduledANGLE"
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
    /*   36 */ 0x5bbfac7136801d8f, /* EGL_ANGLE_ggp_stream_descriptor */
    /*   37 */ 0x18d0970ca7b4c268, /* EGL_ANGLE_global_fence_sync */
    /*   38 */ 0x8247503770574a19, /* EGL_ANGLE_iosurface_client_buffer */
    /*   39 */ 0x2050b7157f814d10, /* EGL_ANGLE_keyed_mutex */
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
    /*   67 */ 0x4ad02aaf45a755ab, /* EGL_ANGLE_swap_with_frame_token */
    /*   68 */ 0xcbc83f2fb8143390, /* EGL_ANGLE_sync_control_rate */
    /*   69 */ 0x9b7afb42d23ff24a, /* EGL_ANGLE_vulkan_display */
    /*   70 */ 0x3b9d20f1e7cea30c, /* EGL_ANGLE_vulkan_image */
    /*   71 */ 0x32f27a4c7977f1cc, /* EGL_ANGLE_wait_until_work_scheduled */
    /*   72 */ 0x584d724a2585416b, /* EGL_ANGLE_window_fixed_size */
    /*   73 */ 0x7fd85a1fe267fe03, /* EGL_ANGLE_x11_visual */
    /*   74 */ 0x79e92599e5906543, /* EGL_ARM_image_format */
    /*   75 */ 0xe6b4aba5bdfeb761, /* EGL_ARM_implicit_external_sync */
    /*   76 */ 0xae00b1c9df43676f, /* EGL_ARM_pixmap_multisample_discard */
    /*   77 */ 0xff8aede3988df0ec, /* EGL_CHROMIUM_sync_control */
    /*   78 */ 0x9c662d7d2c258a50, /* EGL_EXT_bind_to_front */
    /*   79 */ 0x2aa08328d074a816, /* EGL_EXT_buffer_age */
    /*   80 */ 0xa31e0274c2bcafb4, /* EGL_EXT_client_extensions */
    /*   81 */ 0x0391123aa67cc9fd, /* EGL_EXT_client_sync */
    /*   82 */ 0x7ad217dadabe87cc, /* EGL_EXT_compositor */
    /*   83 */ 0x7a089e984094346a, /* EGL_EXT_config_select_group */
    /*   84 */ 0x7150da6f49b30f3e, /* EGL_EXT_create_context_robustness */
    /*   85 */ 0x2f6c882c1eab9296, /* EGL_EXT_device_base */
    /*   86 */ 0x25ef29d5ba78dacb, /* EGL_EXT_device_drm */
    /*   87 */ 0x85d84ed980a0f6c3, /* EGL_EXT_device_drm_render_node */
    /*   88 */ 0xbf886c3682e570aa, /* EGL_EXT_device_enumeration */
    /*   89 */ 0xbb95b050ecd18b71, /* EGL_EXT_device_openwf */
    /*   90 */ 0x25e4685edc9371c5, /* EGL_EXT_device_persistent_id */
    /*   91 */ 0x4c3836479bf75ba3, /* EGL_EXT_device_query */
    /*   92 */ 0x0ec61ed2c29b6b7e, /* EGL_EXT_device_query_name */
    /*   93 */ 0xdbf00a0a59a03004, /* EGL_EXT_display_alloc */
    /*   94 */ 0x1a98bf220bf010e1, /* EGL_EXT_explicit_device */
    /*   95 */ 0x375b95889c713c9a, /* EGL_EXT_gl_colorspace_bt2020_hlg */
    /*   96 */ 0x5091e9def2327eea, /* EGL_EXT_gl_colorspace_bt2020_linear */
    /*   97 */ 0xfc5bf7ce45097f02, /* EGL_EXT_gl_colorspace_bt2020_pq */
    /*   98 */ 0xd63b77d8efe7c73e, /* EGL_EXT_gl_colorspace_display_p3 */
    /*   99 */ 0x24c124c0512e760a, /* EGL_EXT_gl_colorspace_display_p3_linear */
    /*  100 */ 0x46817a7a0934b21a, /* EGL_EXT_gl_colorspace_display_p3_passthrough */
    /*  101 */ 0x01e6ab8e204224c3, /* EGL_EXT_gl_colorspace_scrgb */
    /*  102 */ 0x9d59eeae4c92e9f7, /* EGL_EXT_gl_colorspace_scrgb_linear */
    /*  103 */ 0x0c3a9519d769be90, /* EGL_EXT_image_dma_buf_import */
    /*  104 */ 0xa09fd39f9f1158a7, /* EGL_EXT_image_dma_buf_import_modifiers */
    /*  105 */ 0x476226fa1413890a, /* EGL_EXT_image_gl_colorspace */
    /*  106 */ 0xa5c94b3fdd6261da, /* EGL_EXT_image_implicit_sync_control */
    /*  107 */ 0x9f0bdd4dde93e968, /* EGL_EXT_multiview_window */
    /*  108 */ 0xd324b54bf6a35048, /* EGL_EXT_output_base */
    /*  109 */ 0x0659adf490093fcb, /* EGL_EXT_output_drm */
    /*  110 */ 0x53a0e0b8eb5f3f00, /* EGL_EXT_output_openwf */
    /*  111 */ 0xefb059a6e6841776, /* EGL_EXT_pixel_format_float */
    /*  112 */ 0xa841b196d3768c24, /* EGL_EXT_platform_base */
    /*  113 */ 0x8df4a934a55860db, /* EGL_EXT_platform_device */
    /*  114 */ 0x27716290eb920120, /* EGL_EXT_platform_wayland */
    /*  115 */ 0xe548f3fc71409c63, /* EGL_EXT_platform_x11 */
    /*  116 */ 0x6b5d9de25dfe7eba, /* EGL_EXT_platform_xcb */
    /*  117 */ 0x5e7a56764d6c44b1, /* EGL_EXT_present_opaque */
    /*  118 */ 0x91cb4ebfba10a35f, /* EGL_EXT_protected_content */
    /*  119 */ 0x83f096c0f29ebb18, /* EGL_EXT_protected_surface */
    /*  120 */ 0xfd8d9ef9e9360c00, /* EGL_EXT_query_reset_notification_strategy */
    /*  121 */ 0xfbac73bd87a06d67, /* EGL_EXT_stream_consumer_egloutput */
    /*  122 */ 0x5654a8bc12eeebab, /* EGL_EXT_surface_CTA861_3_metadata */
    /*  123 */ 0x283ef3c9e93fa780, /* EGL_EXT_surface_SMPTE2086_metadata */
    /*  124 */ 0x46e2ba77cc14c6da, /* EGL_EXT_surface_compression */
    /*  125 */ 0xff56e7e2acee3106, /* EGL_EXT_swap_buffers_with_damage */
    /*  126 */ 0x42a3ca98a3fcecb6, /* EGL_EXT_sync_reuse */
    /*  127 */ 0x451b691d8d24df6c, /* EGL_EXT_yuv_surface */
    /*  128 */ 0xdaf189f7653009bf, /* EGL_HI_clientpixmap */
    /*  129 */ 0x066d89176cab3c2c, /* EGL_HI_colorformats */
    /*  130 */ 0x0a76d8252afa230a, /* EGL_IMG_context_priority */
    /*  131 */ 0x7084567bc80e8320, /* EGL_IMG_image_plane_attribs */
    /*  132 */ 0x0b5d7506753789de, /* EGL_KHR_cl_event */
    /*  133 */ 0x70fce70cba139c12, /* EGL_KHR_cl_event2 */
    /*  134 */ 0xef7264f8eef3335b, /* EGL_KHR_client_get_all_proc_addresses */
    /*  135 */ 0x270d8abedb2d3a6d, /* EGL_KHR_config_attribs */
    /*  136 */ 0xda20b827ff8ca001, /* EGL_KHR_context_flush_control */
    /*  137 */ 0x4e16c8c1f6a8131c, /* EGL_KHR_create_context */
    /*  138 */ 0x7b8ef4b379c8f0fd, /* EGL_KHR_create_context_no_error */
    /*  139 */ 0x5b61d2012f7861b3, /* EGL_KHR_debug */
    /*  140 */ 0xfb4d4422d07bc81c, /* EGL_KHR_display_reference */
    /*  141 */ 0x3fc685858cb02200, /* EGL_KHR_fence_sync */
    /*  142 */ 0xcc74201669ca5b5d, /* EGL_KHR_get_all_proc_addresses */
    /*  143 */ 0x0089c927779cc6ef, /* EGL_KHR_gl_colorspace */
    /*  144 */ 0xf2fdf97c1361d5d7, /* EGL_KHR_gl_renderbuffer_image */
    /*  145 */ 0x16756bf4b09c5e40, /* EGL_KHR_gl_texture_2D_image */
    /*  146 */ 0x38fe09b43c8ef819, /* EGL_KHR_gl_texture_3D_image */
    /*  147 */ 0x8da10d2afff88da2, /* EGL_KHR_gl_texture_cubemap_image */
    /*  148 */ 0x871bd75821391394, /* EGL_KHR_image */
    /*  149 */ 0xa2aecd33728540cb, /* EGL_KHR_image_base */
    /*  150 */ 0x6d3e7071805da5a8, /* EGL_KHR_image_pixmap */
    /*  151 */ 0xd1965fc59df1967c, /* EGL_KHR_lock_surface */
    /*  152 */ 0x607598bc0d7426f5, /* EGL_KHR_lock_surface2 */
    /*  153 */ 0xc5c0850bfdef920f, /* EGL_KHR_lock_surface3 */
    /*  154 */ 0xf2c65c6b58412a19, /* EGL_KHR_mutable_render_buffer */
    /*  155 */ 0xb04bf399be660bca, /* EGL_KHR_no_config_context */
    /*  156 */ 0xbf10c896f39ac381, /* EGL_KHR_partial_update */
    /*  157 */ 0x1b60d04af505e88c, /* EGL_KHR_platform_android */
    /*  158 */ 0x92732717613804d7, /* EGL_KHR_platform_gbm */
    /*  159 */ 0xa9c339bb0bd9f8ff, /* EGL_KHR_platform_wayland */
    /*  160 */ 0xb95b474e87d914c0, /* EGL_KHR_platform_x11 */
    /*  161 */ 0x3e707e46a988246f, /* EGL_KHR_reusable_sync */
    /*  162 */ 0x16184f4f924509ef, /* EGL_KHR_stream */
    /*  163 */ 0x9d0b59cf206f7842, /* EGL_KHR_stream_attrib */
    /*  164 */ 0xd9b572ac9eb89474, /* EGL_KHR_stream_consumer_gltexture */
    /*  165 */ 0x6e523fb6f05a3d29, /* EGL_KHR_stream_cross_process_fd */
    /*  166 */ 0x3114241b811aadf2, /* EGL_KHR_stream_fifo */
    /*  167 */ 0x4e02a91ae238a029, /* EGL_KHR_stream_producer_aldatalocator */
    /*  168 */ 0x75e923758d9b47fb, /* EGL_KHR_stream_producer_eglsurface */
    /*  169 */ 0x98778891a458759f, /* EGL_KHR_surfaceless_context */
    /*  170 */ 0x836da10ce92250ef, /* EGL_KHR_swap_buffers_with_damage */
    /*  171 */ 0xc795b75646aecc5b, /* EGL_KHR_vg_parent_image */
    /*  172 */ 0x76eb9817e8dc6c57, /* EGL_KHR_wait_sync */
    /*  173 */ 0x8a02851eceb4e60b, /* EGL_MESA_drm_image */
    /*  174 */ 0xff40140d7e6b5b22, /* EGL_MESA_image_dma_buf_export */
    /*  175 */ 0xcbf9865290d1d737, /* EGL_MESA_platform_gbm */
    /*  176 */ 0xa718f1a00dfc77b2, /* EGL_MESA_platform_surfaceless */
    /*  177 */ 0x205a0c44642ecfe4, /* EGL_MESA_query_driver */
    /*  178 */ 0xc6c6646757ff2eb0, /* EGL_NOK_swap_region */
    /*  179 */ 0xcacecd1071a7c53d, /* EGL_NOK_swap_region2 */
    /*  180 */ 0x140a1d4d56e89998, /* EGL_NOK_texture_from_pixmap */
    /*  181 */ 0x53d1f2866df11721, /* EGL_NV_3dvision_surface */
    /*  182 */ 0x87d534f485d23e03, /* EGL_NV_context_priority_realtime */
    /*  183 */ 0x29d02d6b41d01c44, /* EGL_NV_coverage_sample */
    /*  184 */ 0xbf4228511c15c43e, /* EGL_NV_coverage_sample_resolve */
    /*  185 */ 0xba24ab7c282aa98c, /* EGL_NV_cuda_event */
    /*  186 */ 0x4f20169819f31a19, /* EGL_NV_depth_nonlinear */
    /*  187 */ 0xb32a3dd6b03226f2, /* EGL_NV_device_cuda */
    /*  188 */ 0x797c903a522c4c75, /* EGL_NV_native_query */
    /*  189 */ 0xb151fe3f08ba15f6, /* EGL_NV_post_convert_rounding */
    /*  190 */ 0xaad3806034d0954d, /* EGL_NV_post_sub_buffer */
    /*  191 */ 0x37a228d0850f64a1, /* EGL_NV_quadruple_buffer */
    /*  192 */ 0x74855b1caf0bb727, /* EGL_NV_robustness_video_memory_purge */
    /*  193 */ 0x2db9bc2b87115201, /* EGL_NV_stream_consumer_eglimage */
    /*  194 */ 0xd01bc63b758f4cb9, /* EGL_NV_stream_consumer_eglimage_use_scanout_attrib */
    /*  195 */ 0x2baced719176deed, /* EGL_NV_stream_consumer_gltexture_yuv */
    /*  196 */ 0xfc105cd6c3f68dbe, /* EGL_NV_stream_cross_display */
    /*  197 */ 0x363e000d3383a473, /* EGL_NV_stream_cross_object */
    /*  198 */ 0xac63132cd757c637, /* EGL_NV_stream_cross_partition */
    /*  199 */ 0x2821ab7eeb491706, /* EGL_NV_stream_cross_process */
    /*  200 */ 0x97b15fd0e09adf80, /* EGL_NV_stream_cross_system */
    /*  201 */ 0x7ae84605ae3ae44a, /* EGL_NV_stream_dma */
    /*  202 */ 0x450721831a3bcf73, /* EGL_NV_stream_fifo_next */
    /*  203 */ 0x5dd63931ba6563fb, /* EGL_NV_stream_fifo_synchronous */
    /*  204 */ 0x33597e019cc7811d, /* EGL_NV_stream_flush */
    /*  205 */ 0x0c5d5d4b9e76b0d3, /* EGL_NV_stream_frame_limits */
    /*  206 */ 0xd899fb78ae205e27, /* EGL_NV_stream_metadata */
    /*  207 */ 0xcb6e884a7e412a07, /* EGL_NV_stream_origin */
    /*  208 */ 0x817f41736f96de51, /* EGL_NV_stream_remote */
    /*  209 */ 0x6ad8d08948340894, /* EGL_NV_stream_reset */
    /*  210 */ 0xb46eaf4ddee294f4, /* EGL_NV_stream_socket */
    /*  211 */ 0x7d669bb43a324d63, /* EGL_NV_stream_socket_inet */
    /*  212 */ 0x55bf7befb5997e09, /* EGL_NV_stream_socket_unix */
    /*  213 */ 0xdfb98789892372eb, /* EGL_NV_stream_sync */
    /*  214 */ 0x5557f40f2ef2066c, /* EGL_NV_sync */
    /*  215 */ 0xe1a6732356a0f69f, /* EGL_NV_system_time */
    /*  216 */ 0xf2ec54e65029ed17, /* EGL_NV_triple_buffer */
    /*  217 */ 0xaf15d314b7e55c0f, /* EGL_QNX_image_native_buffer */
    /*  218 */ 0x8efc13d2448ab5b1, /* EGL_QNX_platform_screen */
    /*  219 */ 0x71dbd1513b2ad7e5, /* EGL_TIZEN_image_native_buffer */
    /*  220 */ 0x6d7cb4f9ba09cb5d, /* EGL_TIZEN_image_native_surface */
    /*  221 */ 0xc81b6f913740e456, /* EGL_WL_bind_wayland_display */
    /*  222 */ 0xa3002402543e70a5  /* EGL_WL_create_wayland_buffer_from_image */
};

#ifdef __cplusplus
GladEGLContext glad_egl_context = {};
#else
GladEGLContext glad_egl_context = { 0 };
#endif

static void glad_egl_load_EGL_VERSION_1_0(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           4, /* eglChooseConfig */
          16, /* eglCopyBuffers */
          18, /* eglCreateContext */
          26, /* eglCreatePbufferSurface */
          27, /* eglCreatePixmapSurface */
          43, /* eglCreateWindowSurface */
          45, /* eglDestroyContext */
          50, /* eglDestroySurface */
          63, /* eglGetConfigAttrib */
          64, /* eglGetConfigs */
          66, /* eglGetCurrentDisplay */
          67, /* eglGetCurrentSurface */
          68, /* eglGetDisplay */
          71, /* eglGetError */
          81, /* eglGetProcAddress */
          90, /* eglInitialize */
          93, /* eglMakeCurrent */
         104, /* eglQueryContext */
         129, /* eglQueryString */
         132, /* eglQuerySurface */
         164, /* eglSwapBuffers */
         171, /* eglTerminate */
         176, /* eglWaitGL */
         177  /* eglWaitNative */
    };
    uint32_t i;
    if(!context->VERSION_1_0) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_VERSION_1_1(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           2, /* eglBindTexImage */
         140, /* eglReleaseTexImage */
         163, /* eglSurfaceAttrib */
         170  /* eglSwapInterval */
    };
    uint32_t i;
    if(!context->VERSION_1_1) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_VERSION_1_2(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           1, /* eglBindAPI */
          25, /* eglCreatePbufferFromClientBuffer */
         103, /* eglQueryAPI */
         141, /* eglReleaseThread */
         175  /* eglWaitClient */
    };
    uint32_t i;
    if(!context->VERSION_1_2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_VERSION_1_4(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          65  /* eglGetCurrentContext */
    };
    uint32_t i;
    if(!context->VERSION_1_4) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_VERSION_1_5(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           6, /* eglClientWaitSync */
          22, /* eglCreateImage */
          29, /* eglCreatePlatformPixmapSurface */
          31, /* eglCreatePlatformWindowSurface */
          39, /* eglCreateSync */
          47, /* eglDestroyImage */
          51, /* eglDestroySync */
          79, /* eglGetPlatformDisplay */
          83, /* eglGetSyncAttrib */
         178  /* eglWaitSync */
    };
    uint32_t i;
    if(!context->VERSION_1_5) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANDROID_blob_cache(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         143  /* eglSetBlobCacheFuncsANDROID */
    };
    uint32_t i;
    if(!context->ANDROID_blob_cache) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANDROID_create_native_client_buffer(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          24  /* eglCreateNativeClientBufferANDROID */
    };
    uint32_t i;
    if(!context->ANDROID_create_native_client_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANDROID_get_frame_timestamps(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          61, /* eglGetCompositorTimingANDROID */
          62, /* eglGetCompositorTimingSupportedANDROID */
          72, /* eglGetFrameTimestampSupportedANDROID */
          73, /* eglGetFrameTimestampsANDROID */
          76  /* eglGetNextFrameIdANDROID */
    };
    uint32_t i;
    if(!context->ANDROID_get_frame_timestamps) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANDROID_get_native_client_buffer(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          75  /* eglGetNativeClientBufferANDROID */
    };
    uint32_t i;
    if(!context->ANDROID_get_native_client_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANDROID_native_fence_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          54  /* eglDupNativeFenceFDANDROID */
    };
    uint32_t i;
    if(!context->ANDROID_native_fence_sync) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANDROID_presentation_time(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          98  /* eglPresentationTimeANDROID */
    };
    uint32_t i;
    if(!context->ANDROID_presentation_time) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_device_creation(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          20, /* eglCreateDeviceANGLE */
         137  /* eglReleaseDeviceANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_device_creation) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_external_context_and_surface(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           0, /* eglAcquireExternalContextANGLE */
         138  /* eglReleaseExternalContextANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_external_context_and_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_feature_control(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         110, /* eglQueryDisplayAttribANGLE */
         130  /* eglQueryStringiANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_feature_control) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_metal_shared_event_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          17  /* eglCopyMetalSharedEventANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_metal_shared_event_sync) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_no_error(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         147  /* eglSetValidationEnabledANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_no_error) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_power_preference(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          60, /* eglForceGPUSwitchANGLE */
          89, /* eglHandleGPUSwitchANGLE */
         136, /* eglReacquireHighPowerGPUANGLE */
         139  /* eglReleaseHighPowerGPUANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_power_preference) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_prepare_swap_buffers(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          97  /* eglPrepareSwapBuffersANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_prepare_swap_buffers) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_program_cache_control(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          99, /* eglProgramCacheGetAttribANGLE */
         100, /* eglProgramCachePopulateANGLE */
         101, /* eglProgramCacheQueryANGLE */
         102  /* eglProgramCacheResizeANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_program_cache_control) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_query_surface_pointer(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         134  /* eglQuerySurfacePointerANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_query_surface_pointer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_stream_producer_d3d_texture(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          36, /* eglCreateStreamProducerD3DTextureANGLE */
         161  /* eglStreamPostD3DTextureANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_stream_producer_d3d_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_swap_with_frame_token(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         169  /* eglSwapBuffersWithFrameTokenANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_swap_with_frame_token) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_sync_control_rate(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          74  /* eglGetMscRateANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_sync_control_rate) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_vulkan_image(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          58  /* eglExportVkImageANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_vulkan_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_wait_until_work_scheduled(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         180  /* eglWaitUntilWorkScheduledANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_wait_until_work_scheduled) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_CHROMIUM_sync_control(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          86  /* eglGetSyncValuesCHROMIUM */
    };
    uint32_t i;
    if(!context->CHROMIUM_sync_control) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_client_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           5  /* eglClientSignalSyncEXT */
    };
    uint32_t i;
    if(!context->EXT_client_sync) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_compositor(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           9, /* eglCompositorBindTexWindowEXT */
          10, /* eglCompositorSetContextAttributesEXT */
          11, /* eglCompositorSetContextListEXT */
          12, /* eglCompositorSetSizeEXT */
          13, /* eglCompositorSetWindowAttributesEXT */
          14, /* eglCompositorSetWindowListEXT */
          15  /* eglCompositorSwapPolicyEXT */
    };
    uint32_t i;
    if(!context->EXT_compositor) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_device_base(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         106, /* eglQueryDeviceAttribEXT */
         108, /* eglQueryDeviceStringEXT */
         109, /* eglQueryDevicesEXT */
         111  /* eglQueryDisplayAttribEXT */
    };
    uint32_t i;
    if(!context->EXT_device_base) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_device_enumeration(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         109  /* eglQueryDevicesEXT */
    };
    uint32_t i;
    if(!context->EXT_device_enumeration) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_device_persistent_id(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         107  /* eglQueryDeviceBinaryEXT */
    };
    uint32_t i;
    if(!context->EXT_device_persistent_id) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_device_query(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         106, /* eglQueryDeviceAttribEXT */
         108, /* eglQueryDeviceStringEXT */
         111  /* eglQueryDisplayAttribEXT */
    };
    uint32_t i;
    if(!context->EXT_device_query) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_display_alloc(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          46  /* eglDestroyDisplayEXT */
    };
    uint32_t i;
    if(!context->EXT_display_alloc) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_image_dma_buf_import_modifiers(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         114, /* eglQueryDmaBufFormatsEXT */
         115  /* eglQueryDmaBufModifiersEXT */
    };
    uint32_t i;
    if(!context->EXT_image_dma_buf_import_modifiers) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_output_base(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          77, /* eglGetOutputLayersEXT */
          78, /* eglGetOutputPortsEXT */
          94, /* eglOutputLayerAttribEXT */
          95, /* eglOutputPortAttribEXT */
         119, /* eglQueryOutputLayerAttribEXT */
         120, /* eglQueryOutputLayerStringEXT */
         121, /* eglQueryOutputPortAttribEXT */
         122  /* eglQueryOutputPortStringEXT */
    };
    uint32_t i;
    if(!context->EXT_output_base) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_platform_base(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          30, /* eglCreatePlatformPixmapSurfaceEXT */
          32, /* eglCreatePlatformWindowSurfaceEXT */
          80  /* eglGetPlatformDisplayEXT */
    };
    uint32_t i;
    if(!context->EXT_platform_base) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_stream_consumer_egloutput(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         156  /* eglStreamConsumerOutputEXT */
    };
    uint32_t i;
    if(!context->EXT_stream_consumer_egloutput) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_surface_compression(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         131  /* eglQuerySupportedCompressionRatesEXT */
    };
    uint32_t i;
    if(!context->EXT_surface_compression) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_swap_buffers_with_damage(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         167  /* eglSwapBuffersWithDamageEXT */
    };
    uint32_t i;
    if(!context->EXT_swap_buffers_with_damage) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_sync_reuse(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         174  /* eglUnsignalSyncEXT */
    };
    uint32_t i;
    if(!context->EXT_sync_reuse) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_HI_clientpixmap(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          28  /* eglCreatePixmapSurfaceHI */
    };
    uint32_t i;
    if(!context->HI_clientpixmap) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_cl_event2(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          40  /* eglCreateSync64KHR */
    };
    uint32_t i;
    if(!context->KHR_cl_event2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_debug(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          44, /* eglDebugMessageControlKHR */
          91, /* eglLabelObjectKHR */
         105  /* eglQueryDebugKHR */
    };
    uint32_t i;
    if(!context->KHR_debug) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_display_reference(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         112  /* eglQueryDisplayAttribKHR */
    };
    uint32_t i;
    if(!context->KHR_display_reference) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_fence_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           7, /* eglClientWaitSyncKHR */
          41, /* eglCreateSyncKHR */
          52, /* eglDestroySyncKHR */
          84  /* eglGetSyncAttribKHR */
    };
    uint32_t i;
    if(!context->KHR_fence_sync) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_image(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          23, /* eglCreateImageKHR */
          48  /* eglDestroyImageKHR */
    };
    uint32_t i;
    if(!context->KHR_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_image_base(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          23, /* eglCreateImageKHR */
          48  /* eglDestroyImageKHR */
    };
    uint32_t i;
    if(!context->KHR_image_base) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_lock_surface(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          92, /* eglLockSurfaceKHR */
         173  /* eglUnlockSurfaceKHR */
    };
    uint32_t i;
    if(!context->KHR_lock_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_lock_surface3(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          92, /* eglLockSurfaceKHR */
         133, /* eglQuerySurface64KHR */
         173  /* eglUnlockSurfaceKHR */
    };
    uint32_t i;
    if(!context->KHR_lock_surface3) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_partial_update(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         144  /* eglSetDamageRegionKHR */
    };
    uint32_t i;
    if(!context->KHR_partial_update) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_reusable_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           7, /* eglClientWaitSyncKHR */
          41, /* eglCreateSyncKHR */
          52, /* eglDestroySyncKHR */
          84, /* eglGetSyncAttribKHR */
         148  /* eglSignalSyncKHR */
    };
    uint32_t i;
    if(!context->KHR_reusable_sync) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_stream(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          35, /* eglCreateStreamKHR */
          49, /* eglDestroyStreamKHR */
         125, /* eglQueryStreamKHR */
         128, /* eglQueryStreamu64KHR */
         151  /* eglStreamAttribKHR */
    };
    uint32_t i;
    if(!context->KHR_stream) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_stream_attrib(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          33, /* eglCreateStreamAttribKHR */
         123, /* eglQueryStreamAttribKHR */
         145, /* eglSetStreamAttribKHR */
         152, /* eglStreamConsumerAcquireAttribKHR */
         157  /* eglStreamConsumerReleaseAttribKHR */
    };
    uint32_t i;
    if(!context->KHR_stream_attrib) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_stream_consumer_gltexture(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         153, /* eglStreamConsumerAcquireKHR */
         155, /* eglStreamConsumerGLTextureExternalKHR */
         158  /* eglStreamConsumerReleaseKHR */
    };
    uint32_t i;
    if(!context->KHR_stream_consumer_gltexture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_stream_cross_process_fd(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          34, /* eglCreateStreamFromFileDescriptorKHR */
          82  /* eglGetStreamFileDescriptorKHR */
    };
    uint32_t i;
    if(!context->KHR_stream_cross_process_fd) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_stream_fifo(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         127  /* eglQueryStreamTimeKHR */
    };
    uint32_t i;
    if(!context->KHR_stream_fifo) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_stream_producer_eglsurface(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          37  /* eglCreateStreamProducerSurfaceKHR */
    };
    uint32_t i;
    if(!context->KHR_stream_producer_eglsurface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_swap_buffers_with_damage(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         168  /* eglSwapBuffersWithDamageKHR */
    };
    uint32_t i;
    if(!context->KHR_swap_buffers_with_damage) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_wait_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         179  /* eglWaitSyncKHR */
    };
    uint32_t i;
    if(!context->KHR_wait_sync) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_MESA_drm_image(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          19, /* eglCreateDRMImageMESA */
          57  /* eglExportDRMImageMESA */
    };
    uint32_t i;
    if(!context->MESA_drm_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_MESA_image_dma_buf_export(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          55, /* eglExportDMABUFImageMESA */
          56  /* eglExportDMABUFImageQueryMESA */
    };
    uint32_t i;
    if(!context->MESA_image_dma_buf_export) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_MESA_query_driver(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          69, /* eglGetDisplayDriverConfig */
          70  /* eglGetDisplayDriverName */
    };
    uint32_t i;
    if(!context->MESA_query_driver) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NOK_swap_region(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         166  /* eglSwapBuffersRegionNOK */
    };
    uint32_t i;
    if(!context->NOK_swap_region) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NOK_swap_region2(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         165  /* eglSwapBuffersRegion2NOK */
    };
    uint32_t i;
    if(!context->NOK_swap_region2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_native_query(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         116, /* eglQueryNativeDisplayNV */
         117, /* eglQueryNativePixmapNV */
         118  /* eglQueryNativeWindowNV */
    };
    uint32_t i;
    if(!context->NV_native_query) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_post_sub_buffer(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          96  /* eglPostSubBufferNV */
    };
    uint32_t i;
    if(!context->NV_post_sub_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_stream_consumer_eglimage(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         124, /* eglQueryStreamConsumerEventNV */
         150, /* eglStreamAcquireImageNV */
         160, /* eglStreamImageConsumerConnectNV */
         162  /* eglStreamReleaseImageNV */
    };
    uint32_t i;
    if(!context->NV_stream_consumer_eglimage) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_stream_consumer_gltexture_yuv(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         154  /* eglStreamConsumerGLTextureExternalAttribsNV */
    };
    uint32_t i;
    if(!context->NV_stream_consumer_gltexture_yuv) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_stream_flush(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         159  /* eglStreamFlushNV */
    };
    uint32_t i;
    if(!context->NV_stream_flush) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_stream_metadata(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         113, /* eglQueryDisplayAttribNV */
         126, /* eglQueryStreamMetadataNV */
         146  /* eglSetStreamMetadataNV */
    };
    uint32_t i;
    if(!context->NV_stream_metadata) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_stream_reset(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         142  /* eglResetStreamNV */
    };
    uint32_t i;
    if(!context->NV_stream_reset) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_stream_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          38  /* eglCreateStreamSyncNV */
    };
    uint32_t i;
    if(!context->NV_stream_sync) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           8, /* eglClientWaitSyncNV */
          21, /* eglCreateFenceSyncNV */
          53, /* eglDestroySyncNV */
          59, /* eglFenceNV */
          85, /* eglGetSyncAttribNV */
         149  /* eglSignalSyncNV */
    };
    uint32_t i;
    if(!context->NV_sync) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_system_time(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          87, /* eglGetSystemTimeFrequencyNV */
          88  /* eglGetSystemTimeNV */
    };
    uint32_t i;
    if(!context->NV_system_time) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_WL_bind_wayland_display(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           3, /* eglBindWaylandDisplayWL */
         135, /* eglQueryWaylandBufferWL */
         172  /* eglUnbindWaylandDisplayWL */
    };
    uint32_t i;
    if(!context->WL_bind_wayland_display) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_WL_create_wayland_buffer_from_image(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          42  /* eglCreateWaylandBufferFromImageWL */
    };
    uint32_t i;
    if(!context->WL_create_wayland_buffer_from_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_resolve_aliases(GladEGLContext *context) {
    static const GladAliasPair_t s_aliases[] = {
        {    6,    7 }, /* eglClientWaitSync and eglClientWaitSyncKHR */
        {    7,    6 }, /* eglClientWaitSyncKHR and eglClientWaitSync */
        {   39,   40 }, /* eglCreateSync and eglCreateSync64KHR */
        {   40,   39 }, /* eglCreateSync64KHR and eglCreateSync */
        {   47,   48 }, /* eglDestroyImage and eglDestroyImageKHR */
        {   48,   47 }, /* eglDestroyImageKHR and eglDestroyImage */
        {   51,   52 }, /* eglDestroySync and eglDestroySyncKHR */
        {   52,   51 }, /* eglDestroySyncKHR and eglDestroySync */
        {  111,  112 }, /* eglQueryDisplayAttribEXT and eglQueryDisplayAttribKHR */
        {  111,  113 }, /* eglQueryDisplayAttribEXT and eglQueryDisplayAttribNV */
        {  112,  111 }, /* eglQueryDisplayAttribKHR and eglQueryDisplayAttribEXT */
        {  112,  113 }, /* eglQueryDisplayAttribKHR and eglQueryDisplayAttribNV */
        {  113,  111 }, /* eglQueryDisplayAttribNV and eglQueryDisplayAttribEXT */
        {  113,  112 }, /* eglQueryDisplayAttribNV and eglQueryDisplayAttribKHR */
    };
    void **pfnArray = context->pfnArray;
    uint32_t i;

    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_aliases); ++i) {
        const GladAliasPair_t *pAlias = &s_aliases[i];
        if (pfnArray[pAlias->first] == NULL && pfnArray[pAlias->second] != NULL) {
            pfnArray[pAlias->first] = pfnArray[pAlias->second];
        }
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

    context->VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
    context->VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
    context->VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
    context->VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;
    context->VERSION_1_4 = (major == 1 && minor >= 4) || major > 1;
    context->VERSION_1_5 = (major == 1 && minor >= 5) || major > 1;

    return GLAD_MAKE_VERSION(major, minor);
}

GLAD_NO_INLINE int gladLoadEGLContextUserPtr(GladEGLContext *context, EGLDisplay display, GLADuserptrloadfunc load, void *userptr) {
    int version;
    context->GetDisplay = (PFNEGLGETDISPLAYPROC) load(userptr, "eglGetDisplay");
    context->GetCurrentDisplay = (PFNEGLGETCURRENTDISPLAYPROC) load(userptr, "eglGetCurrentDisplay");
    context->QueryString = (PFNEGLQUERYSTRINGPROC) load(userptr, "eglQueryString");
    context->GetError = (PFNEGLGETERRORPROC) load(userptr, "eglGetError");
    if (context->GetDisplay == NULL || context->GetCurrentDisplay == NULL || context->QueryString == NULL || context->GetError == NULL) return 0;

    version = glad_egl_find_core_egl(context, display);
    if (!version) return 0;
    glad_egl_load_EGL_VERSION_1_0(context, load, userptr);
    glad_egl_load_EGL_VERSION_1_1(context, load, userptr);
    glad_egl_load_EGL_VERSION_1_2(context, load, userptr);
    glad_egl_load_EGL_VERSION_1_4(context, load, userptr);
    glad_egl_load_EGL_VERSION_1_5(context, load, userptr);

    if (!glad_egl_find_extensions_egl(context, display)) return 0;
    glad_egl_load_EGL_ANDROID_blob_cache(context, load, userptr);
    glad_egl_load_EGL_ANDROID_create_native_client_buffer(context, load, userptr);
    glad_egl_load_EGL_ANDROID_get_frame_timestamps(context, load, userptr);
    glad_egl_load_EGL_ANDROID_get_native_client_buffer(context, load, userptr);
    glad_egl_load_EGL_ANDROID_native_fence_sync(context, load, userptr);
    glad_egl_load_EGL_ANDROID_presentation_time(context, load, userptr);
    glad_egl_load_EGL_ANGLE_device_creation(context, load, userptr);
    glad_egl_load_EGL_ANGLE_external_context_and_surface(context, load, userptr);
    glad_egl_load_EGL_ANGLE_feature_control(context, load, userptr);
    glad_egl_load_EGL_ANGLE_metal_shared_event_sync(context, load, userptr);
    glad_egl_load_EGL_ANGLE_no_error(context, load, userptr);
    glad_egl_load_EGL_ANGLE_power_preference(context, load, userptr);
    glad_egl_load_EGL_ANGLE_prepare_swap_buffers(context, load, userptr);
    glad_egl_load_EGL_ANGLE_program_cache_control(context, load, userptr);
    glad_egl_load_EGL_ANGLE_query_surface_pointer(context, load, userptr);
    glad_egl_load_EGL_ANGLE_stream_producer_d3d_texture(context, load, userptr);
    glad_egl_load_EGL_ANGLE_swap_with_frame_token(context, load, userptr);
    glad_egl_load_EGL_ANGLE_sync_control_rate(context, load, userptr);
    glad_egl_load_EGL_ANGLE_vulkan_image(context, load, userptr);
    glad_egl_load_EGL_ANGLE_wait_until_work_scheduled(context, load, userptr);
    glad_egl_load_EGL_CHROMIUM_sync_control(context, load, userptr);
    glad_egl_load_EGL_EXT_client_sync(context, load, userptr);
    glad_egl_load_EGL_EXT_compositor(context, load, userptr);
    glad_egl_load_EGL_EXT_device_base(context, load, userptr);
    glad_egl_load_EGL_EXT_device_enumeration(context, load, userptr);
    glad_egl_load_EGL_EXT_device_persistent_id(context, load, userptr);
    glad_egl_load_EGL_EXT_device_query(context, load, userptr);
    glad_egl_load_EGL_EXT_display_alloc(context, load, userptr);
    glad_egl_load_EGL_EXT_image_dma_buf_import_modifiers(context, load, userptr);
    glad_egl_load_EGL_EXT_output_base(context, load, userptr);
    glad_egl_load_EGL_EXT_platform_base(context, load, userptr);
    glad_egl_load_EGL_EXT_stream_consumer_egloutput(context, load, userptr);
    glad_egl_load_EGL_EXT_surface_compression(context, load, userptr);
    glad_egl_load_EGL_EXT_swap_buffers_with_damage(context, load, userptr);
    glad_egl_load_EGL_EXT_sync_reuse(context, load, userptr);
    glad_egl_load_EGL_HI_clientpixmap(context, load, userptr);
    glad_egl_load_EGL_KHR_cl_event2(context, load, userptr);
    glad_egl_load_EGL_KHR_debug(context, load, userptr);
    glad_egl_load_EGL_KHR_display_reference(context, load, userptr);
    glad_egl_load_EGL_KHR_fence_sync(context, load, userptr);
    glad_egl_load_EGL_KHR_image(context, load, userptr);
    glad_egl_load_EGL_KHR_image_base(context, load, userptr);
    glad_egl_load_EGL_KHR_lock_surface(context, load, userptr);
    glad_egl_load_EGL_KHR_lock_surface3(context, load, userptr);
    glad_egl_load_EGL_KHR_partial_update(context, load, userptr);
    glad_egl_load_EGL_KHR_reusable_sync(context, load, userptr);
    glad_egl_load_EGL_KHR_stream(context, load, userptr);
    glad_egl_load_EGL_KHR_stream_attrib(context, load, userptr);
    glad_egl_load_EGL_KHR_stream_consumer_gltexture(context, load, userptr);
    glad_egl_load_EGL_KHR_stream_cross_process_fd(context, load, userptr);
    glad_egl_load_EGL_KHR_stream_fifo(context, load, userptr);
    glad_egl_load_EGL_KHR_stream_producer_eglsurface(context, load, userptr);
    glad_egl_load_EGL_KHR_swap_buffers_with_damage(context, load, userptr);
    glad_egl_load_EGL_KHR_wait_sync(context, load, userptr);
    glad_egl_load_EGL_MESA_drm_image(context, load, userptr);
    glad_egl_load_EGL_MESA_image_dma_buf_export(context, load, userptr);
    glad_egl_load_EGL_MESA_query_driver(context, load, userptr);
    glad_egl_load_EGL_NOK_swap_region(context, load, userptr);
    glad_egl_load_EGL_NOK_swap_region2(context, load, userptr);
    glad_egl_load_EGL_NV_native_query(context, load, userptr);
    glad_egl_load_EGL_NV_post_sub_buffer(context, load, userptr);
    glad_egl_load_EGL_NV_stream_consumer_eglimage(context, load, userptr);
    glad_egl_load_EGL_NV_stream_consumer_gltexture_yuv(context, load, userptr);
    glad_egl_load_EGL_NV_stream_flush(context, load, userptr);
    glad_egl_load_EGL_NV_stream_metadata(context, load, userptr);
    glad_egl_load_EGL_NV_stream_reset(context, load, userptr);
    glad_egl_load_EGL_NV_stream_sync(context, load, userptr);
    glad_egl_load_EGL_NV_sync(context, load, userptr);
    glad_egl_load_EGL_NV_system_time(context, load, userptr);
    glad_egl_load_EGL_WL_bind_wayland_display(context, load, userptr);
    glad_egl_load_EGL_WL_create_wayland_buffer_from_image(context, load, userptr);

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
