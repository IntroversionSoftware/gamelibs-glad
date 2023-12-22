/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <glad/egl.h>

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
    "eglAcquireExternalContextANGLE", // 0
    "eglBindAPI", // 1
    "eglBindTexImage", // 2
    "eglBindWaylandDisplayWL", // 3
    "eglChooseConfig", // 4
    "eglClientSignalSyncEXT", // 5
    "eglClientWaitSync", // 6
    "eglClientWaitSyncKHR", // 7
    "eglClientWaitSyncNV", // 8
    "eglCompositorBindTexWindowEXT", // 9
    "eglCompositorSetContextAttributesEXT", // 10
    "eglCompositorSetContextListEXT", // 11
    "eglCompositorSetSizeEXT", // 12
    "eglCompositorSetWindowAttributesEXT", // 13
    "eglCompositorSetWindowListEXT", // 14
    "eglCompositorSwapPolicyEXT", // 15
    "eglCopyBuffers", // 16
    "eglCopyMetalSharedEventANGLE", // 17
    "eglCreateContext", // 18
    "eglCreateDRMImageMESA", // 19
    "eglCreateDeviceANGLE", // 20
    "eglCreateFenceSyncNV", // 21
    "eglCreateImage", // 22
    "eglCreateImageKHR", // 23
    "eglCreateNativeClientBufferANDROID", // 24
    "eglCreatePbufferFromClientBuffer", // 25
    "eglCreatePbufferSurface", // 26
    "eglCreatePixmapSurface", // 27
    "eglCreatePixmapSurfaceHI", // 28
    "eglCreatePlatformPixmapSurface", // 29
    "eglCreatePlatformPixmapSurfaceEXT", // 30
    "eglCreatePlatformWindowSurface", // 31
    "eglCreatePlatformWindowSurfaceEXT", // 32
    "eglCreateStreamAttribKHR", // 33
    "eglCreateStreamFromFileDescriptorKHR", // 34
    "eglCreateStreamKHR", // 35
    "eglCreateStreamProducerD3DTextureANGLE", // 36
    "eglCreateStreamProducerSurfaceKHR", // 37
    "eglCreateStreamSyncNV", // 38
    "eglCreateSync", // 39
    "eglCreateSync64KHR", // 40
    "eglCreateSyncKHR", // 41
    "eglCreateWaylandBufferFromImageWL", // 42
    "eglCreateWindowSurface", // 43
    "eglDebugMessageControlKHR", // 44
    "eglDestroyContext", // 45
    "eglDestroyImage", // 46
    "eglDestroyImageKHR", // 47
    "eglDestroyStreamKHR", // 48
    "eglDestroySurface", // 49
    "eglDestroySync", // 50
    "eglDestroySyncKHR", // 51
    "eglDestroySyncNV", // 52
    "eglDupNativeFenceFDANDROID", // 53
    "eglExportDMABUFImageMESA", // 54
    "eglExportDMABUFImageQueryMESA", // 55
    "eglExportDRMImageMESA", // 56
    "eglExportVkImageANGLE", // 57
    "eglFenceNV", // 58
    "eglForceGPUSwitchANGLE", // 59
    "eglGetCompositorTimingANDROID", // 60
    "eglGetCompositorTimingSupportedANDROID", // 61
    "eglGetConfigAttrib", // 62
    "eglGetConfigs", // 63
    "eglGetCurrentContext", // 64
    "eglGetCurrentDisplay", // 65
    "eglGetCurrentSurface", // 66
    "eglGetDisplay", // 67
    "eglGetDisplayDriverConfig", // 68
    "eglGetDisplayDriverName", // 69
    "eglGetError", // 70
    "eglGetFrameTimestampSupportedANDROID", // 71
    "eglGetFrameTimestampsANDROID", // 72
    "eglGetMscRateANGLE", // 73
    "eglGetNativeClientBufferANDROID", // 74
    "eglGetNextFrameIdANDROID", // 75
    "eglGetOutputLayersEXT", // 76
    "eglGetOutputPortsEXT", // 77
    "eglGetPlatformDisplay", // 78
    "eglGetPlatformDisplayEXT", // 79
    "eglGetProcAddress", // 80
    "eglGetStreamFileDescriptorKHR", // 81
    "eglGetSyncAttrib", // 82
    "eglGetSyncAttribKHR", // 83
    "eglGetSyncAttribNV", // 84
    "eglGetSyncValuesCHROMIUM", // 85
    "eglGetSystemTimeFrequencyNV", // 86
    "eglGetSystemTimeNV", // 87
    "eglHandleGPUSwitchANGLE", // 88
    "eglInitialize", // 89
    "eglLabelObjectKHR", // 90
    "eglLockSurfaceKHR", // 91
    "eglMakeCurrent", // 92
    "eglOutputLayerAttribEXT", // 93
    "eglOutputPortAttribEXT", // 94
    "eglPostSubBufferNV", // 95
    "eglPrepareSwapBuffersANGLE", // 96
    "eglPresentationTimeANDROID", // 97
    "eglProgramCacheGetAttribANGLE", // 98
    "eglProgramCachePopulateANGLE", // 99
    "eglProgramCacheQueryANGLE", // 100
    "eglProgramCacheResizeANGLE", // 101
    "eglQueryAPI", // 102
    "eglQueryContext", // 103
    "eglQueryDebugKHR", // 104
    "eglQueryDeviceAttribEXT", // 105
    "eglQueryDeviceBinaryEXT", // 106
    "eglQueryDeviceStringEXT", // 107
    "eglQueryDevicesEXT", // 108
    "eglQueryDisplayAttribANGLE", // 109
    "eglQueryDisplayAttribEXT", // 110
    "eglQueryDisplayAttribKHR", // 111
    "eglQueryDisplayAttribNV", // 112
    "eglQueryDmaBufFormatsEXT", // 113
    "eglQueryDmaBufModifiersEXT", // 114
    "eglQueryNativeDisplayNV", // 115
    "eglQueryNativePixmapNV", // 116
    "eglQueryNativeWindowNV", // 117
    "eglQueryOutputLayerAttribEXT", // 118
    "eglQueryOutputLayerStringEXT", // 119
    "eglQueryOutputPortAttribEXT", // 120
    "eglQueryOutputPortStringEXT", // 121
    "eglQueryStreamAttribKHR", // 122
    "eglQueryStreamConsumerEventNV", // 123
    "eglQueryStreamKHR", // 124
    "eglQueryStreamMetadataNV", // 125
    "eglQueryStreamTimeKHR", // 126
    "eglQueryStreamu64KHR", // 127
    "eglQueryString", // 128
    "eglQueryStringiANGLE", // 129
    "eglQuerySupportedCompressionRatesEXT", // 130
    "eglQuerySurface", // 131
    "eglQuerySurface64KHR", // 132
    "eglQuerySurfacePointerANGLE", // 133
    "eglQueryWaylandBufferWL", // 134
    "eglReacquireHighPowerGPUANGLE", // 135
    "eglReleaseDeviceANGLE", // 136
    "eglReleaseExternalContextANGLE", // 137
    "eglReleaseHighPowerGPUANGLE", // 138
    "eglReleaseTexImage", // 139
    "eglReleaseThread", // 140
    "eglResetStreamNV", // 141
    "eglSetBlobCacheFuncsANDROID", // 142
    "eglSetDamageRegionKHR", // 143
    "eglSetStreamAttribKHR", // 144
    "eglSetStreamMetadataNV", // 145
    "eglSignalSyncKHR", // 146
    "eglSignalSyncNV", // 147
    "eglStreamAcquireImageNV", // 148
    "eglStreamAttribKHR", // 149
    "eglStreamConsumerAcquireAttribKHR", // 150
    "eglStreamConsumerAcquireKHR", // 151
    "eglStreamConsumerGLTextureExternalAttribsNV", // 152
    "eglStreamConsumerGLTextureExternalKHR", // 153
    "eglStreamConsumerOutputEXT", // 154
    "eglStreamConsumerReleaseAttribKHR", // 155
    "eglStreamConsumerReleaseKHR", // 156
    "eglStreamFlushNV", // 157
    "eglStreamImageConsumerConnectNV", // 158
    "eglStreamPostD3DTextureANGLE", // 159
    "eglStreamReleaseImageNV", // 160
    "eglSurfaceAttrib", // 161
    "eglSwapBuffers", // 162
    "eglSwapBuffersRegion2NOK", // 163
    "eglSwapBuffersRegionNOK", // 164
    "eglSwapBuffersWithDamageEXT", // 165
    "eglSwapBuffersWithDamageKHR", // 166
    "eglSwapBuffersWithFrameTokenANGLE", // 167
    "eglSwapInterval", // 168
    "eglTerminate", // 169
    "eglUnbindWaylandDisplayWL", // 170
    "eglUnlockSurfaceKHR", // 171
    "eglUnsignalSyncEXT", // 172
    "eglWaitClient", // 173
    "eglWaitGL", // 174
    "eglWaitNative", // 175
    "eglWaitSync", // 176
    "eglWaitSyncKHR", // 177
    "eglWaitUntilWorkScheduledANGLE" // 178
};

static const char *glad_ext_names[] = {
    "EGL_ANDROID_GLES_layers", // 0
    "EGL_ANDROID_blob_cache", // 1
    "EGL_ANDROID_create_native_client_buffer", // 2
    "EGL_ANDROID_framebuffer_target", // 3
    "EGL_ANDROID_front_buffer_auto_refresh", // 4
    "EGL_ANDROID_get_frame_timestamps", // 5
    "EGL_ANDROID_get_native_client_buffer", // 6
    "EGL_ANDROID_image_native_buffer", // 7
    "EGL_ANDROID_native_fence_sync", // 8
    "EGL_ANDROID_presentation_time", // 9
    "EGL_ANDROID_recordable", // 10
    "EGL_ANGLE_colorspace_attribute_passthrough", // 11
    "EGL_ANGLE_context_virtualization", // 12
    "EGL_ANGLE_create_context_backwards_compatible", // 13
    "EGL_ANGLE_create_context_client_arrays", // 14
    "EGL_ANGLE_create_context_extensions_enabled", // 15
    "EGL_ANGLE_create_context_webgl_compatibility", // 16
    "EGL_ANGLE_create_surface_swap_interval", // 17
    "EGL_ANGLE_d3d_share_handle_client_buffer", // 18
    "EGL_ANGLE_d3d_texture_client_buffer", // 19
    "EGL_ANGLE_device_cgl", // 20
    "EGL_ANGLE_device_creation", // 21
    "EGL_ANGLE_device_d3d", // 22
    "EGL_ANGLE_device_eagl", // 23
    "EGL_ANGLE_device_metal", // 24
    "EGL_ANGLE_device_vulkan", // 25
    "EGL_ANGLE_direct_composition", // 26
    "EGL_ANGLE_display_power_preference", // 27
    "EGL_ANGLE_display_semaphore_share_group", // 28
    "EGL_ANGLE_display_texture_share_group", // 29
    "EGL_ANGLE_experimental_present_path", // 30
    "EGL_ANGLE_external_context_and_surface", // 31
    "EGL_ANGLE_feature_control", // 32
    "EGL_ANGLE_ggp_stream_descriptor", // 33
    "EGL_ANGLE_iosurface_client_buffer", // 34
    "EGL_ANGLE_keyed_mutex", // 35
    "EGL_ANGLE_metal_create_context_ownership_identity", // 36
    "EGL_ANGLE_metal_shared_event_sync", // 37
    "EGL_ANGLE_metal_texture_client_buffer", // 38
    "EGL_ANGLE_platform_angle", // 39
    "EGL_ANGLE_platform_angle_d3d", // 40
    "EGL_ANGLE_platform_angle_d3d11on12", // 41
    "EGL_ANGLE_platform_angle_d3d_luid", // 42
    "EGL_ANGLE_platform_angle_device_context_volatile_cgl", // 43
    "EGL_ANGLE_platform_angle_device_context_volatile_eagl", // 44
    "EGL_ANGLE_platform_angle_device_id", // 45
    "EGL_ANGLE_platform_angle_device_type_egl", // 46
    "EGL_ANGLE_platform_angle_device_type_swiftshader", // 47
    "EGL_ANGLE_platform_angle_metal", // 48
    "EGL_ANGLE_platform_angle_null", // 49
    "EGL_ANGLE_platform_angle_opengl", // 50
    "EGL_ANGLE_platform_angle_vulkan", // 51
    "EGL_ANGLE_power_preference", // 52
    "EGL_ANGLE_prepare_swap_buffers", // 53
    "EGL_ANGLE_program_cache_control", // 54
    "EGL_ANGLE_query_surface_pointer", // 55
    "EGL_ANGLE_robust_resource_initialization", // 56
    "EGL_ANGLE_stream_producer_d3d_texture", // 57
    "EGL_ANGLE_surface_d3d_texture_2d_share_handle", // 58
    "EGL_ANGLE_surface_orientation", // 59
    "EGL_ANGLE_swap_with_frame_token", // 60
    "EGL_ANGLE_sync_control_rate", // 61
    "EGL_ANGLE_vulkan_display", // 62
    "EGL_ANGLE_vulkan_image", // 63
    "EGL_ANGLE_wait_until_work_scheduled", // 64
    "EGL_ANGLE_window_fixed_size", // 65
    "EGL_ANGLE_x11_visual", // 66
    "EGL_ARM_image_format", // 67
    "EGL_ARM_implicit_external_sync", // 68
    "EGL_ARM_pixmap_multisample_discard", // 69
    "EGL_CHROMIUM_sync_control", // 70
    "EGL_EXT_bind_to_front", // 71
    "EGL_EXT_buffer_age", // 72
    "EGL_EXT_client_extensions", // 73
    "EGL_EXT_client_sync", // 74
    "EGL_EXT_compositor", // 75
    "EGL_EXT_config_select_group", // 76
    "EGL_EXT_create_context_robustness", // 77
    "EGL_EXT_device_base", // 78
    "EGL_EXT_device_drm", // 79
    "EGL_EXT_device_drm_render_node", // 80
    "EGL_EXT_device_enumeration", // 81
    "EGL_EXT_device_openwf", // 82
    "EGL_EXT_device_persistent_id", // 83
    "EGL_EXT_device_query", // 84
    "EGL_EXT_device_query_name", // 85
    "EGL_EXT_explicit_device", // 86
    "EGL_EXT_gl_colorspace_bt2020_hlg", // 87
    "EGL_EXT_gl_colorspace_bt2020_linear", // 88
    "EGL_EXT_gl_colorspace_bt2020_pq", // 89
    "EGL_EXT_gl_colorspace_display_p3", // 90
    "EGL_EXT_gl_colorspace_display_p3_linear", // 91
    "EGL_EXT_gl_colorspace_display_p3_passthrough", // 92
    "EGL_EXT_gl_colorspace_scrgb", // 93
    "EGL_EXT_gl_colorspace_scrgb_linear", // 94
    "EGL_EXT_image_dma_buf_import", // 95
    "EGL_EXT_image_dma_buf_import_modifiers", // 96
    "EGL_EXT_image_gl_colorspace", // 97
    "EGL_EXT_image_implicit_sync_control", // 98
    "EGL_EXT_multiview_window", // 99
    "EGL_EXT_output_base", // 100
    "EGL_EXT_output_drm", // 101
    "EGL_EXT_output_openwf", // 102
    "EGL_EXT_pixel_format_float", // 103
    "EGL_EXT_platform_base", // 104
    "EGL_EXT_platform_device", // 105
    "EGL_EXT_platform_wayland", // 106
    "EGL_EXT_platform_x11", // 107
    "EGL_EXT_platform_xcb", // 108
    "EGL_EXT_present_opaque", // 109
    "EGL_EXT_protected_content", // 110
    "EGL_EXT_protected_surface", // 111
    "EGL_EXT_query_reset_notification_strategy", // 112
    "EGL_EXT_stream_consumer_egloutput", // 113
    "EGL_EXT_surface_CTA861_3_metadata", // 114
    "EGL_EXT_surface_SMPTE2086_metadata", // 115
    "EGL_EXT_surface_compression", // 116
    "EGL_EXT_swap_buffers_with_damage", // 117
    "EGL_EXT_sync_reuse", // 118
    "EGL_EXT_yuv_surface", // 119
    "EGL_HI_clientpixmap", // 120
    "EGL_HI_colorformats", // 121
    "EGL_IMG_context_priority", // 122
    "EGL_IMG_image_plane_attribs", // 123
    "EGL_KHR_cl_event", // 124
    "EGL_KHR_cl_event2", // 125
    "EGL_KHR_client_get_all_proc_addresses", // 126
    "EGL_KHR_config_attribs", // 127
    "EGL_KHR_context_flush_control", // 128
    "EGL_KHR_create_context", // 129
    "EGL_KHR_create_context_no_error", // 130
    "EGL_KHR_debug", // 131
    "EGL_KHR_display_reference", // 132
    "EGL_KHR_fence_sync", // 133
    "EGL_KHR_get_all_proc_addresses", // 134
    "EGL_KHR_gl_colorspace", // 135
    "EGL_KHR_gl_renderbuffer_image", // 136
    "EGL_KHR_gl_texture_2D_image", // 137
    "EGL_KHR_gl_texture_3D_image", // 138
    "EGL_KHR_gl_texture_cubemap_image", // 139
    "EGL_KHR_image", // 140
    "EGL_KHR_image_base", // 141
    "EGL_KHR_image_pixmap", // 142
    "EGL_KHR_lock_surface", // 143
    "EGL_KHR_lock_surface2", // 144
    "EGL_KHR_lock_surface3", // 145
    "EGL_KHR_mutable_render_buffer", // 146
    "EGL_KHR_no_config_context", // 147
    "EGL_KHR_partial_update", // 148
    "EGL_KHR_platform_android", // 149
    "EGL_KHR_platform_gbm", // 150
    "EGL_KHR_platform_wayland", // 151
    "EGL_KHR_platform_x11", // 152
    "EGL_KHR_reusable_sync", // 153
    "EGL_KHR_stream", // 154
    "EGL_KHR_stream_attrib", // 155
    "EGL_KHR_stream_consumer_gltexture", // 156
    "EGL_KHR_stream_cross_process_fd", // 157
    "EGL_KHR_stream_fifo", // 158
    "EGL_KHR_stream_producer_aldatalocator", // 159
    "EGL_KHR_stream_producer_eglsurface", // 160
    "EGL_KHR_surfaceless_context", // 161
    "EGL_KHR_swap_buffers_with_damage", // 162
    "EGL_KHR_vg_parent_image", // 163
    "EGL_KHR_wait_sync", // 164
    "EGL_MESA_drm_image", // 165
    "EGL_MESA_image_dma_buf_export", // 166
    "EGL_MESA_platform_gbm", // 167
    "EGL_MESA_platform_surfaceless", // 168
    "EGL_MESA_query_driver", // 169
    "EGL_NOK_swap_region", // 170
    "EGL_NOK_swap_region2", // 171
    "EGL_NOK_texture_from_pixmap", // 172
    "EGL_NV_3dvision_surface", // 173
    "EGL_NV_context_priority_realtime", // 174
    "EGL_NV_coverage_sample", // 175
    "EGL_NV_coverage_sample_resolve", // 176
    "EGL_NV_cuda_event", // 177
    "EGL_NV_depth_nonlinear", // 178
    "EGL_NV_device_cuda", // 179
    "EGL_NV_native_query", // 180
    "EGL_NV_post_convert_rounding", // 181
    "EGL_NV_post_sub_buffer", // 182
    "EGL_NV_quadruple_buffer", // 183
    "EGL_NV_robustness_video_memory_purge", // 184
    "EGL_NV_stream_consumer_eglimage", // 185
    "EGL_NV_stream_consumer_eglimage_use_scanout_attrib", // 186
    "EGL_NV_stream_consumer_gltexture_yuv", // 187
    "EGL_NV_stream_cross_display", // 188
    "EGL_NV_stream_cross_object", // 189
    "EGL_NV_stream_cross_partition", // 190
    "EGL_NV_stream_cross_process", // 191
    "EGL_NV_stream_cross_system", // 192
    "EGL_NV_stream_dma", // 193
    "EGL_NV_stream_fifo_next", // 194
    "EGL_NV_stream_fifo_synchronous", // 195
    "EGL_NV_stream_flush", // 196
    "EGL_NV_stream_frame_limits", // 197
    "EGL_NV_stream_metadata", // 198
    "EGL_NV_stream_origin", // 199
    "EGL_NV_stream_remote", // 200
    "EGL_NV_stream_reset", // 201
    "EGL_NV_stream_socket", // 202
    "EGL_NV_stream_socket_inet", // 203
    "EGL_NV_stream_socket_unix", // 204
    "EGL_NV_stream_sync", // 205
    "EGL_NV_sync", // 206
    "EGL_NV_system_time", // 207
    "EGL_NV_triple_buffer", // 208
    "EGL_QNX_image_native_buffer", // 209
    "EGL_QNX_platform_screen", // 210
    "EGL_TIZEN_image_native_buffer", // 211
    "EGL_TIZEN_image_native_surface", // 212
    "EGL_WL_bind_wayland_display", // 213
    "EGL_WL_create_wayland_buffer_from_image" // 214
};

#ifdef __cplusplus
GladEGLContext glad_egl_context = {};
#else
GladEGLContext glad_egl_context = { 0 };
#endif

static void glad_egl_load_EGL_VERSION_1_0(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_0) return;
    static const uint16_t s_pfnIdx[] = {
            4, // eglChooseConfig
           16, // eglCopyBuffers
           18, // eglCreateContext
           26, // eglCreatePbufferSurface
           27, // eglCreatePixmapSurface
           43, // eglCreateWindowSurface
           45, // eglDestroyContext
           49, // eglDestroySurface
           62, // eglGetConfigAttrib
           63, // eglGetConfigs
           65, // eglGetCurrentDisplay
           66, // eglGetCurrentSurface
           67, // eglGetDisplay
           70, // eglGetError
           80, // eglGetProcAddress
           89, // eglInitialize
           92, // eglMakeCurrent
          103, // eglQueryContext
          128, // eglQueryString
          131, // eglQuerySurface
          162, // eglSwapBuffers
          169, // eglTerminate
          174, // eglWaitGL
          175  // eglWaitNative
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_VERSION_1_1(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_1) return;
    static const uint16_t s_pfnIdx[] = {
            2, // eglBindTexImage
          139, // eglReleaseTexImage
          161, // eglSurfaceAttrib
          168  // eglSwapInterval
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_VERSION_1_2(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_2) return;
    static const uint16_t s_pfnIdx[] = {
            1, // eglBindAPI
           25, // eglCreatePbufferFromClientBuffer
          102, // eglQueryAPI
          140, // eglReleaseThread
          173  // eglWaitClient
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_VERSION_1_4(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_4) return;
    static const uint16_t s_pfnIdx[] = {
           64  // eglGetCurrentContext
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_VERSION_1_5(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_5) return;
    static const uint16_t s_pfnIdx[] = {
            6, // eglClientWaitSync
           22, // eglCreateImage
           29, // eglCreatePlatformPixmapSurface
           31, // eglCreatePlatformWindowSurface
           39, // eglCreateSync
           46, // eglDestroyImage
           50, // eglDestroySync
           78, // eglGetPlatformDisplay
           82, // eglGetSyncAttrib
          176  // eglWaitSync
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANDROID_blob_cache(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANDROID_blob_cache) return;
    static const uint16_t s_pfnIdx[] = {
          142  // eglSetBlobCacheFuncsANDROID
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANDROID_create_native_client_buffer(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANDROID_create_native_client_buffer) return;
    static const uint16_t s_pfnIdx[] = {
           24  // eglCreateNativeClientBufferANDROID
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANDROID_get_frame_timestamps(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANDROID_get_frame_timestamps) return;
    static const uint16_t s_pfnIdx[] = {
           60, // eglGetCompositorTimingANDROID
           61, // eglGetCompositorTimingSupportedANDROID
           71, // eglGetFrameTimestampSupportedANDROID
           72, // eglGetFrameTimestampsANDROID
           75  // eglGetNextFrameIdANDROID
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANDROID_get_native_client_buffer(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANDROID_get_native_client_buffer) return;
    static const uint16_t s_pfnIdx[] = {
           74  // eglGetNativeClientBufferANDROID
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANDROID_native_fence_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANDROID_native_fence_sync) return;
    static const uint16_t s_pfnIdx[] = {
           53  // eglDupNativeFenceFDANDROID
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANDROID_presentation_time(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANDROID_presentation_time) return;
    static const uint16_t s_pfnIdx[] = {
           97  // eglPresentationTimeANDROID
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_device_creation(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_device_creation) return;
    static const uint16_t s_pfnIdx[] = {
           20, // eglCreateDeviceANGLE
          136  // eglReleaseDeviceANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_external_context_and_surface(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_external_context_and_surface) return;
    static const uint16_t s_pfnIdx[] = {
            0, // eglAcquireExternalContextANGLE
          137  // eglReleaseExternalContextANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_feature_control(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_feature_control) return;
    static const uint16_t s_pfnIdx[] = {
          109, // eglQueryDisplayAttribANGLE
          129  // eglQueryStringiANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_metal_shared_event_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_metal_shared_event_sync) return;
    static const uint16_t s_pfnIdx[] = {
           17  // eglCopyMetalSharedEventANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_power_preference(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_power_preference) return;
    static const uint16_t s_pfnIdx[] = {
           59, // eglForceGPUSwitchANGLE
           88, // eglHandleGPUSwitchANGLE
          135, // eglReacquireHighPowerGPUANGLE
          138  // eglReleaseHighPowerGPUANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_prepare_swap_buffers(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_prepare_swap_buffers) return;
    static const uint16_t s_pfnIdx[] = {
           96  // eglPrepareSwapBuffersANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_program_cache_control(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_program_cache_control) return;
    static const uint16_t s_pfnIdx[] = {
           98, // eglProgramCacheGetAttribANGLE
           99, // eglProgramCachePopulateANGLE
          100, // eglProgramCacheQueryANGLE
          101  // eglProgramCacheResizeANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_query_surface_pointer(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_query_surface_pointer) return;
    static const uint16_t s_pfnIdx[] = {
          133  // eglQuerySurfacePointerANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_stream_producer_d3d_texture(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_stream_producer_d3d_texture) return;
    static const uint16_t s_pfnIdx[] = {
           36, // eglCreateStreamProducerD3DTextureANGLE
          159  // eglStreamPostD3DTextureANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_swap_with_frame_token(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_swap_with_frame_token) return;
    static const uint16_t s_pfnIdx[] = {
          167  // eglSwapBuffersWithFrameTokenANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_sync_control_rate(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_sync_control_rate) return;
    static const uint16_t s_pfnIdx[] = {
           73  // eglGetMscRateANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_vulkan_image(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_vulkan_image) return;
    static const uint16_t s_pfnIdx[] = {
           57  // eglExportVkImageANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_ANGLE_wait_until_work_scheduled(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_wait_until_work_scheduled) return;
    static const uint16_t s_pfnIdx[] = {
          178  // eglWaitUntilWorkScheduledANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_CHROMIUM_sync_control(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->CHROMIUM_sync_control) return;
    static const uint16_t s_pfnIdx[] = {
           85  // eglGetSyncValuesCHROMIUM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_client_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_client_sync) return;
    static const uint16_t s_pfnIdx[] = {
            5  // eglClientSignalSyncEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_compositor(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_compositor) return;
    static const uint16_t s_pfnIdx[] = {
            9, // eglCompositorBindTexWindowEXT
           10, // eglCompositorSetContextAttributesEXT
           11, // eglCompositorSetContextListEXT
           12, // eglCompositorSetSizeEXT
           13, // eglCompositorSetWindowAttributesEXT
           14, // eglCompositorSetWindowListEXT
           15  // eglCompositorSwapPolicyEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_device_base(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_device_base) return;
    static const uint16_t s_pfnIdx[] = {
          105, // eglQueryDeviceAttribEXT
          107, // eglQueryDeviceStringEXT
          108, // eglQueryDevicesEXT
          110  // eglQueryDisplayAttribEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_device_enumeration(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_device_enumeration) return;
    static const uint16_t s_pfnIdx[] = {
          108  // eglQueryDevicesEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_device_persistent_id(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_device_persistent_id) return;
    static const uint16_t s_pfnIdx[] = {
          106  // eglQueryDeviceBinaryEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_device_query(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_device_query) return;
    static const uint16_t s_pfnIdx[] = {
          105, // eglQueryDeviceAttribEXT
          107, // eglQueryDeviceStringEXT
          110  // eglQueryDisplayAttribEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_image_dma_buf_import_modifiers(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_image_dma_buf_import_modifiers) return;
    static const uint16_t s_pfnIdx[] = {
          113, // eglQueryDmaBufFormatsEXT
          114  // eglQueryDmaBufModifiersEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_output_base(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_output_base) return;
    static const uint16_t s_pfnIdx[] = {
           76, // eglGetOutputLayersEXT
           77, // eglGetOutputPortsEXT
           93, // eglOutputLayerAttribEXT
           94, // eglOutputPortAttribEXT
          118, // eglQueryOutputLayerAttribEXT
          119, // eglQueryOutputLayerStringEXT
          120, // eglQueryOutputPortAttribEXT
          121  // eglQueryOutputPortStringEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_platform_base(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_platform_base) return;
    static const uint16_t s_pfnIdx[] = {
           30, // eglCreatePlatformPixmapSurfaceEXT
           32, // eglCreatePlatformWindowSurfaceEXT
           79  // eglGetPlatformDisplayEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_stream_consumer_egloutput(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_stream_consumer_egloutput) return;
    static const uint16_t s_pfnIdx[] = {
          154  // eglStreamConsumerOutputEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_surface_compression(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_surface_compression) return;
    static const uint16_t s_pfnIdx[] = {
          130  // eglQuerySupportedCompressionRatesEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_swap_buffers_with_damage(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_swap_buffers_with_damage) return;
    static const uint16_t s_pfnIdx[] = {
          165  // eglSwapBuffersWithDamageEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_EXT_sync_reuse(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_sync_reuse) return;
    static const uint16_t s_pfnIdx[] = {
          172  // eglUnsignalSyncEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_HI_clientpixmap(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->HI_clientpixmap) return;
    static const uint16_t s_pfnIdx[] = {
           28  // eglCreatePixmapSurfaceHI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_cl_event2(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_cl_event2) return;
    static const uint16_t s_pfnIdx[] = {
           40  // eglCreateSync64KHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_debug(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_debug) return;
    static const uint16_t s_pfnIdx[] = {
           44, // eglDebugMessageControlKHR
           90, // eglLabelObjectKHR
          104  // eglQueryDebugKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_display_reference(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_display_reference) return;
    static const uint16_t s_pfnIdx[] = {
          111  // eglQueryDisplayAttribKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_fence_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_fence_sync) return;
    static const uint16_t s_pfnIdx[] = {
            7, // eglClientWaitSyncKHR
           41, // eglCreateSyncKHR
           51, // eglDestroySyncKHR
           83  // eglGetSyncAttribKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_image(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_image) return;
    static const uint16_t s_pfnIdx[] = {
           23, // eglCreateImageKHR
           47  // eglDestroyImageKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_image_base(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_image_base) return;
    static const uint16_t s_pfnIdx[] = {
           23, // eglCreateImageKHR
           47  // eglDestroyImageKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_lock_surface(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_lock_surface) return;
    static const uint16_t s_pfnIdx[] = {
           91, // eglLockSurfaceKHR
          171  // eglUnlockSurfaceKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_lock_surface3(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_lock_surface3) return;
    static const uint16_t s_pfnIdx[] = {
           91, // eglLockSurfaceKHR
          132, // eglQuerySurface64KHR
          171  // eglUnlockSurfaceKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_partial_update(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_partial_update) return;
    static const uint16_t s_pfnIdx[] = {
          143  // eglSetDamageRegionKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_reusable_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_reusable_sync) return;
    static const uint16_t s_pfnIdx[] = {
            7, // eglClientWaitSyncKHR
           41, // eglCreateSyncKHR
           51, // eglDestroySyncKHR
           83, // eglGetSyncAttribKHR
          146  // eglSignalSyncKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_stream(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_stream) return;
    static const uint16_t s_pfnIdx[] = {
           35, // eglCreateStreamKHR
           48, // eglDestroyStreamKHR
          124, // eglQueryStreamKHR
          127, // eglQueryStreamu64KHR
          149  // eglStreamAttribKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_stream_attrib(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_stream_attrib) return;
    static const uint16_t s_pfnIdx[] = {
           33, // eglCreateStreamAttribKHR
          122, // eglQueryStreamAttribKHR
          144, // eglSetStreamAttribKHR
          150, // eglStreamConsumerAcquireAttribKHR
          155  // eglStreamConsumerReleaseAttribKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_stream_consumer_gltexture(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_stream_consumer_gltexture) return;
    static const uint16_t s_pfnIdx[] = {
          151, // eglStreamConsumerAcquireKHR
          153, // eglStreamConsumerGLTextureExternalKHR
          156  // eglStreamConsumerReleaseKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_stream_cross_process_fd(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_stream_cross_process_fd) return;
    static const uint16_t s_pfnIdx[] = {
           34, // eglCreateStreamFromFileDescriptorKHR
           81  // eglGetStreamFileDescriptorKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_stream_fifo(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_stream_fifo) return;
    static const uint16_t s_pfnIdx[] = {
          126  // eglQueryStreamTimeKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_stream_producer_eglsurface(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_stream_producer_eglsurface) return;
    static const uint16_t s_pfnIdx[] = {
           37  // eglCreateStreamProducerSurfaceKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_swap_buffers_with_damage(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_swap_buffers_with_damage) return;
    static const uint16_t s_pfnIdx[] = {
          166  // eglSwapBuffersWithDamageKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_KHR_wait_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_wait_sync) return;
    static const uint16_t s_pfnIdx[] = {
          177  // eglWaitSyncKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_MESA_drm_image(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_drm_image) return;
    static const uint16_t s_pfnIdx[] = {
           19, // eglCreateDRMImageMESA
           56  // eglExportDRMImageMESA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_MESA_image_dma_buf_export(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_image_dma_buf_export) return;
    static const uint16_t s_pfnIdx[] = {
           54, // eglExportDMABUFImageMESA
           55  // eglExportDMABUFImageQueryMESA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_MESA_query_driver(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_query_driver) return;
    static const uint16_t s_pfnIdx[] = {
           68, // eglGetDisplayDriverConfig
           69  // eglGetDisplayDriverName
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NOK_swap_region(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NOK_swap_region) return;
    static const uint16_t s_pfnIdx[] = {
          164  // eglSwapBuffersRegionNOK
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NOK_swap_region2(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NOK_swap_region2) return;
    static const uint16_t s_pfnIdx[] = {
          163  // eglSwapBuffersRegion2NOK
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_native_query(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_native_query) return;
    static const uint16_t s_pfnIdx[] = {
          115, // eglQueryNativeDisplayNV
          116, // eglQueryNativePixmapNV
          117  // eglQueryNativeWindowNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_post_sub_buffer(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_post_sub_buffer) return;
    static const uint16_t s_pfnIdx[] = {
           95  // eglPostSubBufferNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_stream_consumer_eglimage(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_stream_consumer_eglimage) return;
    static const uint16_t s_pfnIdx[] = {
          123, // eglQueryStreamConsumerEventNV
          148, // eglStreamAcquireImageNV
          158, // eglStreamImageConsumerConnectNV
          160  // eglStreamReleaseImageNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_stream_consumer_gltexture_yuv(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_stream_consumer_gltexture_yuv) return;
    static const uint16_t s_pfnIdx[] = {
          152  // eglStreamConsumerGLTextureExternalAttribsNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_stream_flush(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_stream_flush) return;
    static const uint16_t s_pfnIdx[] = {
          157  // eglStreamFlushNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_stream_metadata(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_stream_metadata) return;
    static const uint16_t s_pfnIdx[] = {
          112, // eglQueryDisplayAttribNV
          125, // eglQueryStreamMetadataNV
          145  // eglSetStreamMetadataNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_stream_reset(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_stream_reset) return;
    static const uint16_t s_pfnIdx[] = {
          141  // eglResetStreamNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_stream_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_stream_sync) return;
    static const uint16_t s_pfnIdx[] = {
           38  // eglCreateStreamSyncNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_sync) return;
    static const uint16_t s_pfnIdx[] = {
            8, // eglClientWaitSyncNV
           21, // eglCreateFenceSyncNV
           52, // eglDestroySyncNV
           58, // eglFenceNV
           84, // eglGetSyncAttribNV
          147  // eglSignalSyncNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_NV_system_time(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_system_time) return;
    static const uint16_t s_pfnIdx[] = {
           86, // eglGetSystemTimeFrequencyNV
           87  // eglGetSystemTimeNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_WL_bind_wayland_display(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->WL_bind_wayland_display) return;
    static const uint16_t s_pfnIdx[] = {
            3, // eglBindWaylandDisplayWL
          134, // eglQueryWaylandBufferWL
          170  // eglUnbindWaylandDisplayWL
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_load_EGL_WL_create_wayland_buffer_from_image(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->WL_create_wayland_buffer_from_image) return;
    static const uint16_t s_pfnIdx[] = {
           42  // eglCreateWaylandBufferFromImageWL
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_egl_resolve_aliases(GladEGLContext *context) {
    static const GladAliasPair_t s_aliases[] = {
        {    6,     7 }, // eglClientWaitSync and eglClientWaitSyncKHR
        {    7,     6 }, // eglClientWaitSyncKHR and eglClientWaitSync
        {   39,    40 }, // eglCreateSync and eglCreateSync64KHR
        {   40,    39 }, // eglCreateSync64KHR and eglCreateSync
        {   46,    47 }, // eglDestroyImage and eglDestroyImageKHR
        {   47,    46 }, // eglDestroyImageKHR and eglDestroyImage
        {   50,    51 }, // eglDestroySync and eglDestroySyncKHR
        {   51,    50 }, // eglDestroySyncKHR and eglDestroySync
        {  110,   111 }, // eglQueryDisplayAttribEXT and eglQueryDisplayAttribKHR
        {  110,   112 }, // eglQueryDisplayAttribEXT and eglQueryDisplayAttribNV
        {  111,   110 }, // eglQueryDisplayAttribKHR and eglQueryDisplayAttribEXT
        {  111,   112 }, // eglQueryDisplayAttribKHR and eglQueryDisplayAttribNV
        {  112,   110 }, // eglQueryDisplayAttribNV and eglQueryDisplayAttribEXT
        {  112,   111 }, // eglQueryDisplayAttribNV and eglQueryDisplayAttribKHR
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

static int glad_egl_get_extensions(GladEGLContext *context, EGLDisplay display, char **extensions) {
    size_t clientLen, displayLen;
    char *concat;
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

    *extensions = concat;

    return 1;
}

static int glad_egl_has_extension(const char *extensions, const char *ext) {
    const char *loc;
    const char *terminator;
    if(extensions == NULL) {
        return 0;
    }
    while(1) {
        loc = strstr(extensions, ext);
        if(loc == NULL) {
            return 0;
        }
        terminator = loc + strlen(ext);
        if((loc == extensions || *(loc - 1) == ' ') &&
            (*terminator == ' ' || *terminator == '\0')) {
            return 1;
        }
        extensions = terminator;
    }
}

static GLADapiproc glad_egl_get_proc_from_userptr(void *userptr, const char *name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_egl_find_extensions_egl(GladEGLContext *context, EGLDisplay display) {
    char *extensions;
    if (!glad_egl_get_extensions(context, display, &extensions)) return 0;

    static uint16_t extIdx[] = {
             0, // EGL_ANDROID_GLES_layers
             1, // EGL_ANDROID_blob_cache
             2, // EGL_ANDROID_create_native_client_buffer
             3, // EGL_ANDROID_framebuffer_target
             4, // EGL_ANDROID_front_buffer_auto_refresh
             5, // EGL_ANDROID_get_frame_timestamps
             6, // EGL_ANDROID_get_native_client_buffer
             7, // EGL_ANDROID_image_native_buffer
             8, // EGL_ANDROID_native_fence_sync
             9, // EGL_ANDROID_presentation_time
            10, // EGL_ANDROID_recordable
            11, // EGL_ANGLE_colorspace_attribute_passthrough
            12, // EGL_ANGLE_context_virtualization
            13, // EGL_ANGLE_create_context_backwards_compatible
            14, // EGL_ANGLE_create_context_client_arrays
            15, // EGL_ANGLE_create_context_extensions_enabled
            16, // EGL_ANGLE_create_context_webgl_compatibility
            17, // EGL_ANGLE_create_surface_swap_interval
            18, // EGL_ANGLE_d3d_share_handle_client_buffer
            19, // EGL_ANGLE_d3d_texture_client_buffer
            20, // EGL_ANGLE_device_cgl
            21, // EGL_ANGLE_device_creation
            22, // EGL_ANGLE_device_d3d
            23, // EGL_ANGLE_device_eagl
            24, // EGL_ANGLE_device_metal
            25, // EGL_ANGLE_device_vulkan
            26, // EGL_ANGLE_direct_composition
            27, // EGL_ANGLE_display_power_preference
            28, // EGL_ANGLE_display_semaphore_share_group
            29, // EGL_ANGLE_display_texture_share_group
            30, // EGL_ANGLE_experimental_present_path
            31, // EGL_ANGLE_external_context_and_surface
            32, // EGL_ANGLE_feature_control
            33, // EGL_ANGLE_ggp_stream_descriptor
            34, // EGL_ANGLE_iosurface_client_buffer
            35, // EGL_ANGLE_keyed_mutex
            36, // EGL_ANGLE_metal_create_context_ownership_identity
            37, // EGL_ANGLE_metal_shared_event_sync
            38, // EGL_ANGLE_metal_texture_client_buffer
            39, // EGL_ANGLE_platform_angle
            40, // EGL_ANGLE_platform_angle_d3d
            41, // EGL_ANGLE_platform_angle_d3d11on12
            42, // EGL_ANGLE_platform_angle_d3d_luid
            43, // EGL_ANGLE_platform_angle_device_context_volatile_cgl
            44, // EGL_ANGLE_platform_angle_device_context_volatile_eagl
            45, // EGL_ANGLE_platform_angle_device_id
            46, // EGL_ANGLE_platform_angle_device_type_egl
            47, // EGL_ANGLE_platform_angle_device_type_swiftshader
            48, // EGL_ANGLE_platform_angle_metal
            49, // EGL_ANGLE_platform_angle_null
            50, // EGL_ANGLE_platform_angle_opengl
            51, // EGL_ANGLE_platform_angle_vulkan
            52, // EGL_ANGLE_power_preference
            53, // EGL_ANGLE_prepare_swap_buffers
            54, // EGL_ANGLE_program_cache_control
            55, // EGL_ANGLE_query_surface_pointer
            56, // EGL_ANGLE_robust_resource_initialization
            57, // EGL_ANGLE_stream_producer_d3d_texture
            58, // EGL_ANGLE_surface_d3d_texture_2d_share_handle
            59, // EGL_ANGLE_surface_orientation
            60, // EGL_ANGLE_swap_with_frame_token
            61, // EGL_ANGLE_sync_control_rate
            62, // EGL_ANGLE_vulkan_display
            63, // EGL_ANGLE_vulkan_image
            64, // EGL_ANGLE_wait_until_work_scheduled
            65, // EGL_ANGLE_window_fixed_size
            66, // EGL_ANGLE_x11_visual
            67, // EGL_ARM_image_format
            68, // EGL_ARM_implicit_external_sync
            69, // EGL_ARM_pixmap_multisample_discard
            70, // EGL_CHROMIUM_sync_control
            71, // EGL_EXT_bind_to_front
            72, // EGL_EXT_buffer_age
            73, // EGL_EXT_client_extensions
            74, // EGL_EXT_client_sync
            75, // EGL_EXT_compositor
            76, // EGL_EXT_config_select_group
            77, // EGL_EXT_create_context_robustness
            78, // EGL_EXT_device_base
            79, // EGL_EXT_device_drm
            80, // EGL_EXT_device_drm_render_node
            81, // EGL_EXT_device_enumeration
            82, // EGL_EXT_device_openwf
            83, // EGL_EXT_device_persistent_id
            84, // EGL_EXT_device_query
            85, // EGL_EXT_device_query_name
            86, // EGL_EXT_explicit_device
            87, // EGL_EXT_gl_colorspace_bt2020_hlg
            88, // EGL_EXT_gl_colorspace_bt2020_linear
            89, // EGL_EXT_gl_colorspace_bt2020_pq
            90, // EGL_EXT_gl_colorspace_display_p3
            91, // EGL_EXT_gl_colorspace_display_p3_linear
            92, // EGL_EXT_gl_colorspace_display_p3_passthrough
            93, // EGL_EXT_gl_colorspace_scrgb
            94, // EGL_EXT_gl_colorspace_scrgb_linear
            95, // EGL_EXT_image_dma_buf_import
            96, // EGL_EXT_image_dma_buf_import_modifiers
            97, // EGL_EXT_image_gl_colorspace
            98, // EGL_EXT_image_implicit_sync_control
            99, // EGL_EXT_multiview_window
           100, // EGL_EXT_output_base
           101, // EGL_EXT_output_drm
           102, // EGL_EXT_output_openwf
           103, // EGL_EXT_pixel_format_float
           104, // EGL_EXT_platform_base
           105, // EGL_EXT_platform_device
           106, // EGL_EXT_platform_wayland
           107, // EGL_EXT_platform_x11
           108, // EGL_EXT_platform_xcb
           109, // EGL_EXT_present_opaque
           110, // EGL_EXT_protected_content
           111, // EGL_EXT_protected_surface
           112, // EGL_EXT_query_reset_notification_strategy
           113, // EGL_EXT_stream_consumer_egloutput
           114, // EGL_EXT_surface_CTA861_3_metadata
           115, // EGL_EXT_surface_SMPTE2086_metadata
           116, // EGL_EXT_surface_compression
           117, // EGL_EXT_swap_buffers_with_damage
           118, // EGL_EXT_sync_reuse
           119, // EGL_EXT_yuv_surface
           120, // EGL_HI_clientpixmap
           121, // EGL_HI_colorformats
           122, // EGL_IMG_context_priority
           123, // EGL_IMG_image_plane_attribs
           124, // EGL_KHR_cl_event
           125, // EGL_KHR_cl_event2
           126, // EGL_KHR_client_get_all_proc_addresses
           127, // EGL_KHR_config_attribs
           128, // EGL_KHR_context_flush_control
           129, // EGL_KHR_create_context
           130, // EGL_KHR_create_context_no_error
           131, // EGL_KHR_debug
           132, // EGL_KHR_display_reference
           133, // EGL_KHR_fence_sync
           134, // EGL_KHR_get_all_proc_addresses
           135, // EGL_KHR_gl_colorspace
           136, // EGL_KHR_gl_renderbuffer_image
           137, // EGL_KHR_gl_texture_2D_image
           138, // EGL_KHR_gl_texture_3D_image
           139, // EGL_KHR_gl_texture_cubemap_image
           140, // EGL_KHR_image
           141, // EGL_KHR_image_base
           142, // EGL_KHR_image_pixmap
           143, // EGL_KHR_lock_surface
           144, // EGL_KHR_lock_surface2
           145, // EGL_KHR_lock_surface3
           146, // EGL_KHR_mutable_render_buffer
           147, // EGL_KHR_no_config_context
           148, // EGL_KHR_partial_update
           149, // EGL_KHR_platform_android
           150, // EGL_KHR_platform_gbm
           151, // EGL_KHR_platform_wayland
           152, // EGL_KHR_platform_x11
           153, // EGL_KHR_reusable_sync
           154, // EGL_KHR_stream
           155, // EGL_KHR_stream_attrib
           156, // EGL_KHR_stream_consumer_gltexture
           157, // EGL_KHR_stream_cross_process_fd
           158, // EGL_KHR_stream_fifo
           159, // EGL_KHR_stream_producer_aldatalocator
           160, // EGL_KHR_stream_producer_eglsurface
           161, // EGL_KHR_surfaceless_context
           162, // EGL_KHR_swap_buffers_with_damage
           163, // EGL_KHR_vg_parent_image
           164, // EGL_KHR_wait_sync
           165, // EGL_MESA_drm_image
           166, // EGL_MESA_image_dma_buf_export
           167, // EGL_MESA_platform_gbm
           168, // EGL_MESA_platform_surfaceless
           169, // EGL_MESA_query_driver
           170, // EGL_NOK_swap_region
           171, // EGL_NOK_swap_region2
           172, // EGL_NOK_texture_from_pixmap
           173, // EGL_NV_3dvision_surface
           174, // EGL_NV_context_priority_realtime
           175, // EGL_NV_coverage_sample
           176, // EGL_NV_coverage_sample_resolve
           177, // EGL_NV_cuda_event
           178, // EGL_NV_depth_nonlinear
           179, // EGL_NV_device_cuda
           180, // EGL_NV_native_query
           181, // EGL_NV_post_convert_rounding
           182, // EGL_NV_post_sub_buffer
           183, // EGL_NV_quadruple_buffer
           184, // EGL_NV_robustness_video_memory_purge
           185, // EGL_NV_stream_consumer_eglimage
           186, // EGL_NV_stream_consumer_eglimage_use_scanout_attrib
           187, // EGL_NV_stream_consumer_gltexture_yuv
           188, // EGL_NV_stream_cross_display
           189, // EGL_NV_stream_cross_object
           190, // EGL_NV_stream_cross_partition
           191, // EGL_NV_stream_cross_process
           192, // EGL_NV_stream_cross_system
           193, // EGL_NV_stream_dma
           194, // EGL_NV_stream_fifo_next
           195, // EGL_NV_stream_fifo_synchronous
           196, // EGL_NV_stream_flush
           197, // EGL_NV_stream_frame_limits
           198, // EGL_NV_stream_metadata
           199, // EGL_NV_stream_origin
           200, // EGL_NV_stream_remote
           201, // EGL_NV_stream_reset
           202, // EGL_NV_stream_socket
           203, // EGL_NV_stream_socket_inet
           204, // EGL_NV_stream_socket_unix
           205, // EGL_NV_stream_sync
           206, // EGL_NV_sync
           207, // EGL_NV_system_time
           208, // EGL_NV_triple_buffer
           209, // EGL_QNX_image_native_buffer
           210, // EGL_QNX_platform_screen
           211, // EGL_TIZEN_image_native_buffer
           212, // EGL_TIZEN_image_native_surface
           213, // EGL_WL_bind_wayland_display
           214, // EGL_WL_create_wayland_buffer_from_image
        0xFFFF
    };

    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(extIdx) - 1; ++i)
        context->extArray[extIdx[i]] = glad_egl_has_extension(extensions, glad_ext_names[extIdx[i]]);

    free(extensions);

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

int gladLoadEGLContextUserPtr(GladEGLContext *context, EGLDisplay display, GLADuserptrloadfunc load, void *userptr) {
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
