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
    /*   46 */ "eglDestroyImage",
    /*   47 */ "eglDestroyImageKHR",
    /*   48 */ "eglDestroyStreamKHR",
    /*   49 */ "eglDestroySurface",
    /*   50 */ "eglDestroySync",
    /*   51 */ "eglDestroySyncKHR",
    /*   52 */ "eglDestroySyncNV",
    /*   53 */ "eglDupNativeFenceFDANDROID",
    /*   54 */ "eglExportDMABUFImageMESA",
    /*   55 */ "eglExportDMABUFImageQueryMESA",
    /*   56 */ "eglExportDRMImageMESA",
    /*   57 */ "eglExportVkImageANGLE",
    /*   58 */ "eglFenceNV",
    /*   59 */ "eglForceGPUSwitchANGLE",
    /*   60 */ "eglGetCompositorTimingANDROID",
    /*   61 */ "eglGetCompositorTimingSupportedANDROID",
    /*   62 */ "eglGetConfigAttrib",
    /*   63 */ "eglGetConfigs",
    /*   64 */ "eglGetCurrentContext",
    /*   65 */ "eglGetCurrentDisplay",
    /*   66 */ "eglGetCurrentSurface",
    /*   67 */ "eglGetDisplay",
    /*   68 */ "eglGetDisplayDriverConfig",
    /*   69 */ "eglGetDisplayDriverName",
    /*   70 */ "eglGetError",
    /*   71 */ "eglGetFrameTimestampSupportedANDROID",
    /*   72 */ "eglGetFrameTimestampsANDROID",
    /*   73 */ "eglGetMscRateANGLE",
    /*   74 */ "eglGetNativeClientBufferANDROID",
    /*   75 */ "eglGetNextFrameIdANDROID",
    /*   76 */ "eglGetOutputLayersEXT",
    /*   77 */ "eglGetOutputPortsEXT",
    /*   78 */ "eglGetPlatformDisplay",
    /*   79 */ "eglGetPlatformDisplayEXT",
    /*   80 */ "eglGetProcAddress",
    /*   81 */ "eglGetStreamFileDescriptorKHR",
    /*   82 */ "eglGetSyncAttrib",
    /*   83 */ "eglGetSyncAttribKHR",
    /*   84 */ "eglGetSyncAttribNV",
    /*   85 */ "eglGetSyncValuesCHROMIUM",
    /*   86 */ "eglGetSystemTimeFrequencyNV",
    /*   87 */ "eglGetSystemTimeNV",
    /*   88 */ "eglHandleGPUSwitchANGLE",
    /*   89 */ "eglInitialize",
    /*   90 */ "eglLabelObjectKHR",
    /*   91 */ "eglLockSurfaceKHR",
    /*   92 */ "eglMakeCurrent",
    /*   93 */ "eglOutputLayerAttribEXT",
    /*   94 */ "eglOutputPortAttribEXT",
    /*   95 */ "eglPostSubBufferNV",
    /*   96 */ "eglPrepareSwapBuffersANGLE",
    /*   97 */ "eglPresentationTimeANDROID",
    /*   98 */ "eglProgramCacheGetAttribANGLE",
    /*   99 */ "eglProgramCachePopulateANGLE",
    /*  100 */ "eglProgramCacheQueryANGLE",
    /*  101 */ "eglProgramCacheResizeANGLE",
    /*  102 */ "eglQueryAPI",
    /*  103 */ "eglQueryContext",
    /*  104 */ "eglQueryDebugKHR",
    /*  105 */ "eglQueryDeviceAttribEXT",
    /*  106 */ "eglQueryDeviceBinaryEXT",
    /*  107 */ "eglQueryDeviceStringEXT",
    /*  108 */ "eglQueryDevicesEXT",
    /*  109 */ "eglQueryDisplayAttribANGLE",
    /*  110 */ "eglQueryDisplayAttribEXT",
    /*  111 */ "eglQueryDisplayAttribKHR",
    /*  112 */ "eglQueryDisplayAttribNV",
    /*  113 */ "eglQueryDmaBufFormatsEXT",
    /*  114 */ "eglQueryDmaBufModifiersEXT",
    /*  115 */ "eglQueryNativeDisplayNV",
    /*  116 */ "eglQueryNativePixmapNV",
    /*  117 */ "eglQueryNativeWindowNV",
    /*  118 */ "eglQueryOutputLayerAttribEXT",
    /*  119 */ "eglQueryOutputLayerStringEXT",
    /*  120 */ "eglQueryOutputPortAttribEXT",
    /*  121 */ "eglQueryOutputPortStringEXT",
    /*  122 */ "eglQueryStreamAttribKHR",
    /*  123 */ "eglQueryStreamConsumerEventNV",
    /*  124 */ "eglQueryStreamKHR",
    /*  125 */ "eglQueryStreamMetadataNV",
    /*  126 */ "eglQueryStreamTimeKHR",
    /*  127 */ "eglQueryStreamu64KHR",
    /*  128 */ "eglQueryString",
    /*  129 */ "eglQueryStringiANGLE",
    /*  130 */ "eglQuerySupportedCompressionRatesEXT",
    /*  131 */ "eglQuerySurface",
    /*  132 */ "eglQuerySurface64KHR",
    /*  133 */ "eglQuerySurfacePointerANGLE",
    /*  134 */ "eglQueryWaylandBufferWL",
    /*  135 */ "eglReacquireHighPowerGPUANGLE",
    /*  136 */ "eglReleaseDeviceANGLE",
    /*  137 */ "eglReleaseExternalContextANGLE",
    /*  138 */ "eglReleaseHighPowerGPUANGLE",
    /*  139 */ "eglReleaseTexImage",
    /*  140 */ "eglReleaseThread",
    /*  141 */ "eglResetStreamNV",
    /*  142 */ "eglSetBlobCacheFuncsANDROID",
    /*  143 */ "eglSetDamageRegionKHR",
    /*  144 */ "eglSetStreamAttribKHR",
    /*  145 */ "eglSetStreamMetadataNV",
    /*  146 */ "eglSetValidationEnabledANGLE",
    /*  147 */ "eglSignalSyncKHR",
    /*  148 */ "eglSignalSyncNV",
    /*  149 */ "eglStreamAcquireImageNV",
    /*  150 */ "eglStreamAttribKHR",
    /*  151 */ "eglStreamConsumerAcquireAttribKHR",
    /*  152 */ "eglStreamConsumerAcquireKHR",
    /*  153 */ "eglStreamConsumerGLTextureExternalAttribsNV",
    /*  154 */ "eglStreamConsumerGLTextureExternalKHR",
    /*  155 */ "eglStreamConsumerOutputEXT",
    /*  156 */ "eglStreamConsumerReleaseAttribKHR",
    /*  157 */ "eglStreamConsumerReleaseKHR",
    /*  158 */ "eglStreamFlushNV",
    /*  159 */ "eglStreamImageConsumerConnectNV",
    /*  160 */ "eglStreamPostD3DTextureANGLE",
    /*  161 */ "eglStreamReleaseImageNV",
    /*  162 */ "eglSurfaceAttrib",
    /*  163 */ "eglSwapBuffers",
    /*  164 */ "eglSwapBuffersRegion2NOK",
    /*  165 */ "eglSwapBuffersRegionNOK",
    /*  166 */ "eglSwapBuffersWithDamageEXT",
    /*  167 */ "eglSwapBuffersWithDamageKHR",
    /*  168 */ "eglSwapBuffersWithFrameTokenANGLE",
    /*  169 */ "eglSwapInterval",
    /*  170 */ "eglTerminate",
    /*  171 */ "eglUnbindWaylandDisplayWL",
    /*  172 */ "eglUnlockSurfaceKHR",
    /*  173 */ "eglUnsignalSyncEXT",
    /*  174 */ "eglWaitClient",
    /*  175 */ "eglWaitGL",
    /*  176 */ "eglWaitNative",
    /*  177 */ "eglWaitSync",
    /*  178 */ "eglWaitSyncKHR",
    /*  179 */ "eglWaitUntilWorkScheduledANGLE"
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
    /*   11 */ 0xd59b8dcdd4961074, /* EGL_ANGLE_colorspace_attribute_passthrough */
    /*   12 */ 0xe34ca55588e959e9, /* EGL_ANGLE_context_virtualization */
    /*   13 */ 0x5ee453db857b3c29, /* EGL_ANGLE_create_context_backwards_compatible */
    /*   14 */ 0xf2594fbcdfa3f545, /* EGL_ANGLE_create_context_client_arrays */
    /*   15 */ 0x5f5244f40c7ef900, /* EGL_ANGLE_create_context_extensions_enabled */
    /*   16 */ 0x4eac032f78eb1b97, /* EGL_ANGLE_create_context_webgl_compatibility */
    /*   17 */ 0x3db394a57b9600ed, /* EGL_ANGLE_create_surface_swap_interval */
    /*   18 */ 0x63dc3010a72f0f41, /* EGL_ANGLE_d3d_share_handle_client_buffer */
    /*   19 */ 0x008d04b1748738c1, /* EGL_ANGLE_d3d_texture_client_buffer */
    /*   20 */ 0xb9c6689d871a8219, /* EGL_ANGLE_device_cgl */
    /*   21 */ 0xe481bb03dc3ffd32, /* EGL_ANGLE_device_creation */
    /*   22 */ 0xa48498cc85257b13, /* EGL_ANGLE_device_d3d */
    /*   23 */ 0x22f96d8668d51351, /* EGL_ANGLE_device_eagl */
    /*   24 */ 0x00ba7a7f1c36e9e4, /* EGL_ANGLE_device_metal */
    /*   25 */ 0x6f356a60670d8e5a, /* EGL_ANGLE_device_vulkan */
    /*   26 */ 0xc9df550ac4a1ec30, /* EGL_ANGLE_direct_composition */
    /*   27 */ 0x00a9cc6756852346, /* EGL_ANGLE_display_power_preference */
    /*   28 */ 0xed1190e49710ebde, /* EGL_ANGLE_display_semaphore_share_group */
    /*   29 */ 0x2c22f1ea2f02edae, /* EGL_ANGLE_display_texture_share_group */
    /*   30 */ 0xc03ef8c49f8daf6e, /* EGL_ANGLE_experimental_present_path */
    /*   31 */ 0x1160c225fe2a6bf5, /* EGL_ANGLE_external_context_and_surface */
    /*   32 */ 0xf136655b938cfef7, /* EGL_ANGLE_feature_control */
    /*   33 */ 0x5bbfac7136801d8f, /* EGL_ANGLE_ggp_stream_descriptor */
    /*   34 */ 0x18d0970ca7b4c268, /* EGL_ANGLE_global_fence_sync */
    /*   35 */ 0x8247503770574a19, /* EGL_ANGLE_iosurface_client_buffer */
    /*   36 */ 0x2050b7157f814d10, /* EGL_ANGLE_keyed_mutex */
    /*   37 */ 0x5027858c4c30d226, /* EGL_ANGLE_metal_create_context_ownership_identity */
    /*   38 */ 0x6e333abff6cec928, /* EGL_ANGLE_metal_shared_event_sync */
    /*   39 */ 0xea85ee216b66aed6, /* EGL_ANGLE_metal_texture_client_buffer */
    /*   40 */ 0x69ec6f07eb567773, /* EGL_ANGLE_no_error */
    /*   41 */ 0x0e642f860b2670f4, /* EGL_ANGLE_platform_angle */
    /*   42 */ 0xb3c6378facb30b47, /* EGL_ANGLE_platform_angle_d3d */
    /*   43 */ 0x67363c4648bf01a6, /* EGL_ANGLE_platform_angle_d3d11on12 */
    /*   44 */ 0x7404e65415e0cf49, /* EGL_ANGLE_platform_angle_d3d_luid */
    /*   45 */ 0x5b49c1a91e2bcce3, /* EGL_ANGLE_platform_angle_device_context_volatile_cgl */
    /*   46 */ 0xf27d356bb04d147d, /* EGL_ANGLE_platform_angle_device_context_volatile_eagl */
    /*   47 */ 0x1d4a1428061a339a, /* EGL_ANGLE_platform_angle_device_id */
    /*   48 */ 0xbe47353c1f13390b, /* EGL_ANGLE_platform_angle_device_type_egl */
    /*   49 */ 0xe9d3e98ad0d51659, /* EGL_ANGLE_platform_angle_device_type_swiftshader */
    /*   50 */ 0x98c1482cf6675807, /* EGL_ANGLE_platform_angle_metal */
    /*   51 */ 0x6ab80514da15b6f9, /* EGL_ANGLE_platform_angle_null */
    /*   52 */ 0xb419931c39c7f38a, /* EGL_ANGLE_platform_angle_opengl */
    /*   53 */ 0xb2ad9cccda275eb4, /* EGL_ANGLE_platform_angle_vulkan */
    /*   54 */ 0x2d155ccb3d2e416d, /* EGL_ANGLE_platform_angle_webgpu */
    /*   55 */ 0xaf2ad94baa465742, /* EGL_ANGLE_power_preference */
    /*   56 */ 0x41534601630f79ce, /* EGL_ANGLE_prepare_swap_buffers */
    /*   57 */ 0x15c4d55f4f359f01, /* EGL_ANGLE_program_cache_control */
    /*   58 */ 0x655dcac0071412b7, /* EGL_ANGLE_query_surface_pointer */
    /*   59 */ 0xbec48c7959021479, /* EGL_ANGLE_robust_resource_initialization */
    /*   60 */ 0x9e02c97224491c29, /* EGL_ANGLE_stream_producer_d3d_texture */
    /*   61 */ 0x460ce0075e78a2bd, /* EGL_ANGLE_surface_d3d_texture_2d_share_handle */
    /*   62 */ 0xa388335593ecba25, /* EGL_ANGLE_surface_orientation */
    /*   63 */ 0x4ad02aaf45a755ab, /* EGL_ANGLE_swap_with_frame_token */
    /*   64 */ 0xcbc83f2fb8143390, /* EGL_ANGLE_sync_control_rate */
    /*   65 */ 0x9b7afb42d23ff24a, /* EGL_ANGLE_vulkan_display */
    /*   66 */ 0x3b9d20f1e7cea30c, /* EGL_ANGLE_vulkan_image */
    /*   67 */ 0x32f27a4c7977f1cc, /* EGL_ANGLE_wait_until_work_scheduled */
    /*   68 */ 0x584d724a2585416b, /* EGL_ANGLE_window_fixed_size */
    /*   69 */ 0x7fd85a1fe267fe03, /* EGL_ANGLE_x11_visual */
    /*   70 */ 0x79e92599e5906543, /* EGL_ARM_image_format */
    /*   71 */ 0xe6b4aba5bdfeb761, /* EGL_ARM_implicit_external_sync */
    /*   72 */ 0xae00b1c9df43676f, /* EGL_ARM_pixmap_multisample_discard */
    /*   73 */ 0xff8aede3988df0ec, /* EGL_CHROMIUM_sync_control */
    /*   74 */ 0x9c662d7d2c258a50, /* EGL_EXT_bind_to_front */
    /*   75 */ 0x2aa08328d074a816, /* EGL_EXT_buffer_age */
    /*   76 */ 0xa31e0274c2bcafb4, /* EGL_EXT_client_extensions */
    /*   77 */ 0x0391123aa67cc9fd, /* EGL_EXT_client_sync */
    /*   78 */ 0x7ad217dadabe87cc, /* EGL_EXT_compositor */
    /*   79 */ 0x7a089e984094346a, /* EGL_EXT_config_select_group */
    /*   80 */ 0x7150da6f49b30f3e, /* EGL_EXT_create_context_robustness */
    /*   81 */ 0x2f6c882c1eab9296, /* EGL_EXT_device_base */
    /*   82 */ 0x25ef29d5ba78dacb, /* EGL_EXT_device_drm */
    /*   83 */ 0x85d84ed980a0f6c3, /* EGL_EXT_device_drm_render_node */
    /*   84 */ 0xbf886c3682e570aa, /* EGL_EXT_device_enumeration */
    /*   85 */ 0xbb95b050ecd18b71, /* EGL_EXT_device_openwf */
    /*   86 */ 0x25e4685edc9371c5, /* EGL_EXT_device_persistent_id */
    /*   87 */ 0x4c3836479bf75ba3, /* EGL_EXT_device_query */
    /*   88 */ 0x0ec61ed2c29b6b7e, /* EGL_EXT_device_query_name */
    /*   89 */ 0x1a98bf220bf010e1, /* EGL_EXT_explicit_device */
    /*   90 */ 0x375b95889c713c9a, /* EGL_EXT_gl_colorspace_bt2020_hlg */
    /*   91 */ 0x5091e9def2327eea, /* EGL_EXT_gl_colorspace_bt2020_linear */
    /*   92 */ 0xfc5bf7ce45097f02, /* EGL_EXT_gl_colorspace_bt2020_pq */
    /*   93 */ 0xd63b77d8efe7c73e, /* EGL_EXT_gl_colorspace_display_p3 */
    /*   94 */ 0x24c124c0512e760a, /* EGL_EXT_gl_colorspace_display_p3_linear */
    /*   95 */ 0x46817a7a0934b21a, /* EGL_EXT_gl_colorspace_display_p3_passthrough */
    /*   96 */ 0x01e6ab8e204224c3, /* EGL_EXT_gl_colorspace_scrgb */
    /*   97 */ 0x9d59eeae4c92e9f7, /* EGL_EXT_gl_colorspace_scrgb_linear */
    /*   98 */ 0x0c3a9519d769be90, /* EGL_EXT_image_dma_buf_import */
    /*   99 */ 0xa09fd39f9f1158a7, /* EGL_EXT_image_dma_buf_import_modifiers */
    /*  100 */ 0x476226fa1413890a, /* EGL_EXT_image_gl_colorspace */
    /*  101 */ 0xa5c94b3fdd6261da, /* EGL_EXT_image_implicit_sync_control */
    /*  102 */ 0x9f0bdd4dde93e968, /* EGL_EXT_multiview_window */
    /*  103 */ 0xd324b54bf6a35048, /* EGL_EXT_output_base */
    /*  104 */ 0x0659adf490093fcb, /* EGL_EXT_output_drm */
    /*  105 */ 0x53a0e0b8eb5f3f00, /* EGL_EXT_output_openwf */
    /*  106 */ 0xefb059a6e6841776, /* EGL_EXT_pixel_format_float */
    /*  107 */ 0xa841b196d3768c24, /* EGL_EXT_platform_base */
    /*  108 */ 0x8df4a934a55860db, /* EGL_EXT_platform_device */
    /*  109 */ 0x27716290eb920120, /* EGL_EXT_platform_wayland */
    /*  110 */ 0xe548f3fc71409c63, /* EGL_EXT_platform_x11 */
    /*  111 */ 0x6b5d9de25dfe7eba, /* EGL_EXT_platform_xcb */
    /*  112 */ 0x5e7a56764d6c44b1, /* EGL_EXT_present_opaque */
    /*  113 */ 0x91cb4ebfba10a35f, /* EGL_EXT_protected_content */
    /*  114 */ 0x83f096c0f29ebb18, /* EGL_EXT_protected_surface */
    /*  115 */ 0xfd8d9ef9e9360c00, /* EGL_EXT_query_reset_notification_strategy */
    /*  116 */ 0xfbac73bd87a06d67, /* EGL_EXT_stream_consumer_egloutput */
    /*  117 */ 0x5654a8bc12eeebab, /* EGL_EXT_surface_CTA861_3_metadata */
    /*  118 */ 0x283ef3c9e93fa780, /* EGL_EXT_surface_SMPTE2086_metadata */
    /*  119 */ 0x46e2ba77cc14c6da, /* EGL_EXT_surface_compression */
    /*  120 */ 0xff56e7e2acee3106, /* EGL_EXT_swap_buffers_with_damage */
    /*  121 */ 0x42a3ca98a3fcecb6, /* EGL_EXT_sync_reuse */
    /*  122 */ 0x451b691d8d24df6c, /* EGL_EXT_yuv_surface */
    /*  123 */ 0xdaf189f7653009bf, /* EGL_HI_clientpixmap */
    /*  124 */ 0x066d89176cab3c2c, /* EGL_HI_colorformats */
    /*  125 */ 0x0a76d8252afa230a, /* EGL_IMG_context_priority */
    /*  126 */ 0x7084567bc80e8320, /* EGL_IMG_image_plane_attribs */
    /*  127 */ 0x0b5d7506753789de, /* EGL_KHR_cl_event */
    /*  128 */ 0x70fce70cba139c12, /* EGL_KHR_cl_event2 */
    /*  129 */ 0xef7264f8eef3335b, /* EGL_KHR_client_get_all_proc_addresses */
    /*  130 */ 0x270d8abedb2d3a6d, /* EGL_KHR_config_attribs */
    /*  131 */ 0xda20b827ff8ca001, /* EGL_KHR_context_flush_control */
    /*  132 */ 0x4e16c8c1f6a8131c, /* EGL_KHR_create_context */
    /*  133 */ 0x7b8ef4b379c8f0fd, /* EGL_KHR_create_context_no_error */
    /*  134 */ 0x5b61d2012f7861b3, /* EGL_KHR_debug */
    /*  135 */ 0xfb4d4422d07bc81c, /* EGL_KHR_display_reference */
    /*  136 */ 0x3fc685858cb02200, /* EGL_KHR_fence_sync */
    /*  137 */ 0xcc74201669ca5b5d, /* EGL_KHR_get_all_proc_addresses */
    /*  138 */ 0x0089c927779cc6ef, /* EGL_KHR_gl_colorspace */
    /*  139 */ 0xf2fdf97c1361d5d7, /* EGL_KHR_gl_renderbuffer_image */
    /*  140 */ 0x16756bf4b09c5e40, /* EGL_KHR_gl_texture_2D_image */
    /*  141 */ 0x38fe09b43c8ef819, /* EGL_KHR_gl_texture_3D_image */
    /*  142 */ 0x8da10d2afff88da2, /* EGL_KHR_gl_texture_cubemap_image */
    /*  143 */ 0x871bd75821391394, /* EGL_KHR_image */
    /*  144 */ 0xa2aecd33728540cb, /* EGL_KHR_image_base */
    /*  145 */ 0x6d3e7071805da5a8, /* EGL_KHR_image_pixmap */
    /*  146 */ 0xd1965fc59df1967c, /* EGL_KHR_lock_surface */
    /*  147 */ 0x607598bc0d7426f5, /* EGL_KHR_lock_surface2 */
    /*  148 */ 0xc5c0850bfdef920f, /* EGL_KHR_lock_surface3 */
    /*  149 */ 0xf2c65c6b58412a19, /* EGL_KHR_mutable_render_buffer */
    /*  150 */ 0xb04bf399be660bca, /* EGL_KHR_no_config_context */
    /*  151 */ 0xbf10c896f39ac381, /* EGL_KHR_partial_update */
    /*  152 */ 0x1b60d04af505e88c, /* EGL_KHR_platform_android */
    /*  153 */ 0x92732717613804d7, /* EGL_KHR_platform_gbm */
    /*  154 */ 0xa9c339bb0bd9f8ff, /* EGL_KHR_platform_wayland */
    /*  155 */ 0xb95b474e87d914c0, /* EGL_KHR_platform_x11 */
    /*  156 */ 0x3e707e46a988246f, /* EGL_KHR_reusable_sync */
    /*  157 */ 0x16184f4f924509ef, /* EGL_KHR_stream */
    /*  158 */ 0x9d0b59cf206f7842, /* EGL_KHR_stream_attrib */
    /*  159 */ 0xd9b572ac9eb89474, /* EGL_KHR_stream_consumer_gltexture */
    /*  160 */ 0x6e523fb6f05a3d29, /* EGL_KHR_stream_cross_process_fd */
    /*  161 */ 0x3114241b811aadf2, /* EGL_KHR_stream_fifo */
    /*  162 */ 0x4e02a91ae238a029, /* EGL_KHR_stream_producer_aldatalocator */
    /*  163 */ 0x75e923758d9b47fb, /* EGL_KHR_stream_producer_eglsurface */
    /*  164 */ 0x98778891a458759f, /* EGL_KHR_surfaceless_context */
    /*  165 */ 0x836da10ce92250ef, /* EGL_KHR_swap_buffers_with_damage */
    /*  166 */ 0xc795b75646aecc5b, /* EGL_KHR_vg_parent_image */
    /*  167 */ 0x76eb9817e8dc6c57, /* EGL_KHR_wait_sync */
    /*  168 */ 0x8a02851eceb4e60b, /* EGL_MESA_drm_image */
    /*  169 */ 0xff40140d7e6b5b22, /* EGL_MESA_image_dma_buf_export */
    /*  170 */ 0xcbf9865290d1d737, /* EGL_MESA_platform_gbm */
    /*  171 */ 0xa718f1a00dfc77b2, /* EGL_MESA_platform_surfaceless */
    /*  172 */ 0x205a0c44642ecfe4, /* EGL_MESA_query_driver */
    /*  173 */ 0xc6c6646757ff2eb0, /* EGL_NOK_swap_region */
    /*  174 */ 0xcacecd1071a7c53d, /* EGL_NOK_swap_region2 */
    /*  175 */ 0x140a1d4d56e89998, /* EGL_NOK_texture_from_pixmap */
    /*  176 */ 0x53d1f2866df11721, /* EGL_NV_3dvision_surface */
    /*  177 */ 0x87d534f485d23e03, /* EGL_NV_context_priority_realtime */
    /*  178 */ 0x29d02d6b41d01c44, /* EGL_NV_coverage_sample */
    /*  179 */ 0xbf4228511c15c43e, /* EGL_NV_coverage_sample_resolve */
    /*  180 */ 0xba24ab7c282aa98c, /* EGL_NV_cuda_event */
    /*  181 */ 0x4f20169819f31a19, /* EGL_NV_depth_nonlinear */
    /*  182 */ 0xb32a3dd6b03226f2, /* EGL_NV_device_cuda */
    /*  183 */ 0x797c903a522c4c75, /* EGL_NV_native_query */
    /*  184 */ 0xb151fe3f08ba15f6, /* EGL_NV_post_convert_rounding */
    /*  185 */ 0xaad3806034d0954d, /* EGL_NV_post_sub_buffer */
    /*  186 */ 0x37a228d0850f64a1, /* EGL_NV_quadruple_buffer */
    /*  187 */ 0x74855b1caf0bb727, /* EGL_NV_robustness_video_memory_purge */
    /*  188 */ 0x2db9bc2b87115201, /* EGL_NV_stream_consumer_eglimage */
    /*  189 */ 0xd01bc63b758f4cb9, /* EGL_NV_stream_consumer_eglimage_use_scanout_attrib */
    /*  190 */ 0x2baced719176deed, /* EGL_NV_stream_consumer_gltexture_yuv */
    /*  191 */ 0xfc105cd6c3f68dbe, /* EGL_NV_stream_cross_display */
    /*  192 */ 0x363e000d3383a473, /* EGL_NV_stream_cross_object */
    /*  193 */ 0xac63132cd757c637, /* EGL_NV_stream_cross_partition */
    /*  194 */ 0x2821ab7eeb491706, /* EGL_NV_stream_cross_process */
    /*  195 */ 0x97b15fd0e09adf80, /* EGL_NV_stream_cross_system */
    /*  196 */ 0x7ae84605ae3ae44a, /* EGL_NV_stream_dma */
    /*  197 */ 0x450721831a3bcf73, /* EGL_NV_stream_fifo_next */
    /*  198 */ 0x5dd63931ba6563fb, /* EGL_NV_stream_fifo_synchronous */
    /*  199 */ 0x33597e019cc7811d, /* EGL_NV_stream_flush */
    /*  200 */ 0x0c5d5d4b9e76b0d3, /* EGL_NV_stream_frame_limits */
    /*  201 */ 0xd899fb78ae205e27, /* EGL_NV_stream_metadata */
    /*  202 */ 0xcb6e884a7e412a07, /* EGL_NV_stream_origin */
    /*  203 */ 0x817f41736f96de51, /* EGL_NV_stream_remote */
    /*  204 */ 0x6ad8d08948340894, /* EGL_NV_stream_reset */
    /*  205 */ 0xb46eaf4ddee294f4, /* EGL_NV_stream_socket */
    /*  206 */ 0x7d669bb43a324d63, /* EGL_NV_stream_socket_inet */
    /*  207 */ 0x55bf7befb5997e09, /* EGL_NV_stream_socket_unix */
    /*  208 */ 0xdfb98789892372eb, /* EGL_NV_stream_sync */
    /*  209 */ 0x5557f40f2ef2066c, /* EGL_NV_sync */
    /*  210 */ 0xe1a6732356a0f69f, /* EGL_NV_system_time */
    /*  211 */ 0xf2ec54e65029ed17, /* EGL_NV_triple_buffer */
    /*  212 */ 0xaf15d314b7e55c0f, /* EGL_QNX_image_native_buffer */
    /*  213 */ 0x8efc13d2448ab5b1, /* EGL_QNX_platform_screen */
    /*  214 */ 0x71dbd1513b2ad7e5, /* EGL_TIZEN_image_native_buffer */
    /*  215 */ 0x6d7cb4f9ba09cb5d, /* EGL_TIZEN_image_native_surface */
    /*  216 */ 0xc81b6f913740e456, /* EGL_WL_bind_wayland_display */
    /*  217 */ 0xa3002402543e70a5  /* EGL_WL_create_wayland_buffer_from_image */
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
          49, /* eglDestroySurface */
          62, /* eglGetConfigAttrib */
          63, /* eglGetConfigs */
          65, /* eglGetCurrentDisplay */
          66, /* eglGetCurrentSurface */
          67, /* eglGetDisplay */
          70, /* eglGetError */
          80, /* eglGetProcAddress */
          89, /* eglInitialize */
          92, /* eglMakeCurrent */
         103, /* eglQueryContext */
         128, /* eglQueryString */
         131, /* eglQuerySurface */
         163, /* eglSwapBuffers */
         170, /* eglTerminate */
         175, /* eglWaitGL */
         176  /* eglWaitNative */
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
         139, /* eglReleaseTexImage */
         162, /* eglSurfaceAttrib */
         169  /* eglSwapInterval */
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
         102, /* eglQueryAPI */
         140, /* eglReleaseThread */
         174  /* eglWaitClient */
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
          64  /* eglGetCurrentContext */
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
          46, /* eglDestroyImage */
          50, /* eglDestroySync */
          78, /* eglGetPlatformDisplay */
          82, /* eglGetSyncAttrib */
         177  /* eglWaitSync */
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
         142  /* eglSetBlobCacheFuncsANDROID */
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
          60, /* eglGetCompositorTimingANDROID */
          61, /* eglGetCompositorTimingSupportedANDROID */
          71, /* eglGetFrameTimestampSupportedANDROID */
          72, /* eglGetFrameTimestampsANDROID */
          75  /* eglGetNextFrameIdANDROID */
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
          74  /* eglGetNativeClientBufferANDROID */
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
          53  /* eglDupNativeFenceFDANDROID */
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
          97  /* eglPresentationTimeANDROID */
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
         136  /* eglReleaseDeviceANGLE */
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
         137  /* eglReleaseExternalContextANGLE */
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
         109, /* eglQueryDisplayAttribANGLE */
         129  /* eglQueryStringiANGLE */
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
         146  /* eglSetValidationEnabledANGLE */
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
          59, /* eglForceGPUSwitchANGLE */
          88, /* eglHandleGPUSwitchANGLE */
         135, /* eglReacquireHighPowerGPUANGLE */
         138  /* eglReleaseHighPowerGPUANGLE */
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
          96  /* eglPrepareSwapBuffersANGLE */
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
          98, /* eglProgramCacheGetAttribANGLE */
          99, /* eglProgramCachePopulateANGLE */
         100, /* eglProgramCacheQueryANGLE */
         101  /* eglProgramCacheResizeANGLE */
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
         133  /* eglQuerySurfacePointerANGLE */
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
         160  /* eglStreamPostD3DTextureANGLE */
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
         168  /* eglSwapBuffersWithFrameTokenANGLE */
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
          73  /* eglGetMscRateANGLE */
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
          57  /* eglExportVkImageANGLE */
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
         179  /* eglWaitUntilWorkScheduledANGLE */
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
          85  /* eglGetSyncValuesCHROMIUM */
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
         105, /* eglQueryDeviceAttribEXT */
         107, /* eglQueryDeviceStringEXT */
         108, /* eglQueryDevicesEXT */
         110  /* eglQueryDisplayAttribEXT */
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
         108  /* eglQueryDevicesEXT */
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
         106  /* eglQueryDeviceBinaryEXT */
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
         105, /* eglQueryDeviceAttribEXT */
         107, /* eglQueryDeviceStringEXT */
         110  /* eglQueryDisplayAttribEXT */
    };
    uint32_t i;
    if(!context->EXT_device_query) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_EGL_fn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_image_dma_buf_import_modifiers(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         113, /* eglQueryDmaBufFormatsEXT */
         114  /* eglQueryDmaBufModifiersEXT */
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
          76, /* eglGetOutputLayersEXT */
          77, /* eglGetOutputPortsEXT */
          93, /* eglOutputLayerAttribEXT */
          94, /* eglOutputPortAttribEXT */
         118, /* eglQueryOutputLayerAttribEXT */
         119, /* eglQueryOutputLayerStringEXT */
         120, /* eglQueryOutputPortAttribEXT */
         121  /* eglQueryOutputPortStringEXT */
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
          79  /* eglGetPlatformDisplayEXT */
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
         155  /* eglStreamConsumerOutputEXT */
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
         130  /* eglQuerySupportedCompressionRatesEXT */
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
         166  /* eglSwapBuffersWithDamageEXT */
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
         173  /* eglUnsignalSyncEXT */
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
          90, /* eglLabelObjectKHR */
         104  /* eglQueryDebugKHR */
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
         111  /* eglQueryDisplayAttribKHR */
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
          51, /* eglDestroySyncKHR */
          83  /* eglGetSyncAttribKHR */
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
          47  /* eglDestroyImageKHR */
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
          47  /* eglDestroyImageKHR */
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
          91, /* eglLockSurfaceKHR */
         172  /* eglUnlockSurfaceKHR */
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
          91, /* eglLockSurfaceKHR */
         132, /* eglQuerySurface64KHR */
         172  /* eglUnlockSurfaceKHR */
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
         143  /* eglSetDamageRegionKHR */
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
          51, /* eglDestroySyncKHR */
          83, /* eglGetSyncAttribKHR */
         147  /* eglSignalSyncKHR */
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
          48, /* eglDestroyStreamKHR */
         124, /* eglQueryStreamKHR */
         127, /* eglQueryStreamu64KHR */
         150  /* eglStreamAttribKHR */
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
         122, /* eglQueryStreamAttribKHR */
         144, /* eglSetStreamAttribKHR */
         151, /* eglStreamConsumerAcquireAttribKHR */
         156  /* eglStreamConsumerReleaseAttribKHR */
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
         152, /* eglStreamConsumerAcquireKHR */
         154, /* eglStreamConsumerGLTextureExternalKHR */
         157  /* eglStreamConsumerReleaseKHR */
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
          81  /* eglGetStreamFileDescriptorKHR */
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
         126  /* eglQueryStreamTimeKHR */
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
         167  /* eglSwapBuffersWithDamageKHR */
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
         178  /* eglWaitSyncKHR */
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
          56  /* eglExportDRMImageMESA */
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
          54, /* eglExportDMABUFImageMESA */
          55  /* eglExportDMABUFImageQueryMESA */
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
          68, /* eglGetDisplayDriverConfig */
          69  /* eglGetDisplayDriverName */
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
         165  /* eglSwapBuffersRegionNOK */
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
         164  /* eglSwapBuffersRegion2NOK */
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
         115, /* eglQueryNativeDisplayNV */
         116, /* eglQueryNativePixmapNV */
         117  /* eglQueryNativeWindowNV */
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
          95  /* eglPostSubBufferNV */
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
         123, /* eglQueryStreamConsumerEventNV */
         149, /* eglStreamAcquireImageNV */
         159, /* eglStreamImageConsumerConnectNV */
         161  /* eglStreamReleaseImageNV */
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
         153  /* eglStreamConsumerGLTextureExternalAttribsNV */
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
         158  /* eglStreamFlushNV */
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
         112, /* eglQueryDisplayAttribNV */
         125, /* eglQueryStreamMetadataNV */
         145  /* eglSetStreamMetadataNV */
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
         141  /* eglResetStreamNV */
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
          52, /* eglDestroySyncNV */
          58, /* eglFenceNV */
          84, /* eglGetSyncAttribNV */
         148  /* eglSignalSyncNV */
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
          86, /* eglGetSystemTimeFrequencyNV */
          87  /* eglGetSystemTimeNV */
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
         134, /* eglQueryWaylandBufferWL */
         171  /* eglUnbindWaylandDisplayWL */
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
        {   46,   47 }, /* eglDestroyImage and eglDestroyImageKHR */
        {   47,   46 }, /* eglDestroyImageKHR and eglDestroyImage */
        {   50,   51 }, /* eglDestroySync and eglDestroySyncKHR */
        {   51,   50 }, /* eglDestroySyncKHR and eglDestroySync */
        {  110,  111 }, /* eglQueryDisplayAttribEXT and eglQueryDisplayAttribKHR */
        {  110,  112 }, /* eglQueryDisplayAttribEXT and eglQueryDisplayAttribNV */
        {  111,  110 }, /* eglQueryDisplayAttribKHR and eglQueryDisplayAttribEXT */
        {  111,  112 }, /* eglQueryDisplayAttribKHR and eglQueryDisplayAttribNV */
        {  112,  110 }, /* eglQueryDisplayAttribNV and eglQueryDisplayAttribEXT */
        {  112,  111 }, /* eglQueryDisplayAttribNV and eglQueryDisplayAttribKHR */
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
