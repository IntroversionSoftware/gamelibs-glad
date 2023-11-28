/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdio.h>
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

#ifdef __cplusplus
GladEGLContext glad_egl_context = {};
#else
GladEGLContext glad_egl_context = { 0 };
#endif







static void glad_egl_load_EGL_VERSION_1_0(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_0) return;
    context->ChooseConfig = (PFNEGLCHOOSECONFIGPROC) load(userptr, "eglChooseConfig");
    context->CopyBuffers = (PFNEGLCOPYBUFFERSPROC) load(userptr, "eglCopyBuffers");
    context->CreateContext = (PFNEGLCREATECONTEXTPROC) load(userptr, "eglCreateContext");
    context->CreatePbufferSurface = (PFNEGLCREATEPBUFFERSURFACEPROC) load(userptr, "eglCreatePbufferSurface");
    context->CreatePixmapSurface = (PFNEGLCREATEPIXMAPSURFACEPROC) load(userptr, "eglCreatePixmapSurface");
    context->CreateWindowSurface = (PFNEGLCREATEWINDOWSURFACEPROC) load(userptr, "eglCreateWindowSurface");
    context->DestroyContext = (PFNEGLDESTROYCONTEXTPROC) load(userptr, "eglDestroyContext");
    context->DestroySurface = (PFNEGLDESTROYSURFACEPROC) load(userptr, "eglDestroySurface");
    context->GetConfigAttrib = (PFNEGLGETCONFIGATTRIBPROC) load(userptr, "eglGetConfigAttrib");
    context->GetConfigs = (PFNEGLGETCONFIGSPROC) load(userptr, "eglGetConfigs");
    context->GetCurrentDisplay = (PFNEGLGETCURRENTDISPLAYPROC) load(userptr, "eglGetCurrentDisplay");
    context->GetCurrentSurface = (PFNEGLGETCURRENTSURFACEPROC) load(userptr, "eglGetCurrentSurface");
    context->GetDisplay = (PFNEGLGETDISPLAYPROC) load(userptr, "eglGetDisplay");
    context->GetError = (PFNEGLGETERRORPROC) load(userptr, "eglGetError");
    context->GetProcAddress = (PFNEGLGETPROCADDRESSPROC) load(userptr, "eglGetProcAddress");
    context->Initialize = (PFNEGLINITIALIZEPROC) load(userptr, "eglInitialize");
    context->MakeCurrent = (PFNEGLMAKECURRENTPROC) load(userptr, "eglMakeCurrent");
    context->QueryContext = (PFNEGLQUERYCONTEXTPROC) load(userptr, "eglQueryContext");
    context->QueryString = (PFNEGLQUERYSTRINGPROC) load(userptr, "eglQueryString");
    context->QuerySurface = (PFNEGLQUERYSURFACEPROC) load(userptr, "eglQuerySurface");
    context->SwapBuffers = (PFNEGLSWAPBUFFERSPROC) load(userptr, "eglSwapBuffers");
    context->Terminate = (PFNEGLTERMINATEPROC) load(userptr, "eglTerminate");
    context->WaitGL = (PFNEGLWAITGLPROC) load(userptr, "eglWaitGL");
    context->WaitNative = (PFNEGLWAITNATIVEPROC) load(userptr, "eglWaitNative");
}
static void glad_egl_load_EGL_VERSION_1_1(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_1) return;
    context->BindTexImage = (PFNEGLBINDTEXIMAGEPROC) load(userptr, "eglBindTexImage");
    context->ReleaseTexImage = (PFNEGLRELEASETEXIMAGEPROC) load(userptr, "eglReleaseTexImage");
    context->SurfaceAttrib = (PFNEGLSURFACEATTRIBPROC) load(userptr, "eglSurfaceAttrib");
    context->SwapInterval = (PFNEGLSWAPINTERVALPROC) load(userptr, "eglSwapInterval");
}
static void glad_egl_load_EGL_VERSION_1_2(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_2) return;
    context->BindAPI = (PFNEGLBINDAPIPROC) load(userptr, "eglBindAPI");
    context->CreatePbufferFromClientBuffer = (PFNEGLCREATEPBUFFERFROMCLIENTBUFFERPROC) load(userptr, "eglCreatePbufferFromClientBuffer");
    context->QueryAPI = (PFNEGLQUERYAPIPROC) load(userptr, "eglQueryAPI");
    context->ReleaseThread = (PFNEGLRELEASETHREADPROC) load(userptr, "eglReleaseThread");
    context->WaitClient = (PFNEGLWAITCLIENTPROC) load(userptr, "eglWaitClient");
}
static void glad_egl_load_EGL_VERSION_1_4(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_4) return;
    context->GetCurrentContext = (PFNEGLGETCURRENTCONTEXTPROC) load(userptr, "eglGetCurrentContext");
}
static void glad_egl_load_EGL_VERSION_1_5(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_5) return;
    context->ClientWaitSync = (PFNEGLCLIENTWAITSYNCPROC) load(userptr, "eglClientWaitSync");
    context->CreateImage = (PFNEGLCREATEIMAGEPROC) load(userptr, "eglCreateImage");
    context->CreatePlatformPixmapSurface = (PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC) load(userptr, "eglCreatePlatformPixmapSurface");
    context->CreatePlatformWindowSurface = (PFNEGLCREATEPLATFORMWINDOWSURFACEPROC) load(userptr, "eglCreatePlatformWindowSurface");
    context->CreateSync = (PFNEGLCREATESYNCPROC) load(userptr, "eglCreateSync");
    context->DestroyImage = (PFNEGLDESTROYIMAGEPROC) load(userptr, "eglDestroyImage");
    context->DestroySync = (PFNEGLDESTROYSYNCPROC) load(userptr, "eglDestroySync");
    context->GetPlatformDisplay = (PFNEGLGETPLATFORMDISPLAYPROC) load(userptr, "eglGetPlatformDisplay");
    context->GetSyncAttrib = (PFNEGLGETSYNCATTRIBPROC) load(userptr, "eglGetSyncAttrib");
    context->WaitSync = (PFNEGLWAITSYNCPROC) load(userptr, "eglWaitSync");
}
static void glad_egl_load_EGL_ANDROID_blob_cache(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANDROID_blob_cache) return;
    context->SetBlobCacheFuncsANDROID = (PFNEGLSETBLOBCACHEFUNCSANDROIDPROC) load(userptr, "eglSetBlobCacheFuncsANDROID");
}
static void glad_egl_load_EGL_ANDROID_create_native_client_buffer(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANDROID_create_native_client_buffer) return;
    context->CreateNativeClientBufferANDROID = (PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC) load(userptr, "eglCreateNativeClientBufferANDROID");
}
static void glad_egl_load_EGL_ANDROID_get_frame_timestamps(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANDROID_get_frame_timestamps) return;
    context->GetCompositorTimingANDROID = (PFNEGLGETCOMPOSITORTIMINGANDROIDPROC) load(userptr, "eglGetCompositorTimingANDROID");
    context->GetCompositorTimingSupportedANDROID = (PFNEGLGETCOMPOSITORTIMINGSUPPORTEDANDROIDPROC) load(userptr, "eglGetCompositorTimingSupportedANDROID");
    context->GetFrameTimestampSupportedANDROID = (PFNEGLGETFRAMETIMESTAMPSUPPORTEDANDROIDPROC) load(userptr, "eglGetFrameTimestampSupportedANDROID");
    context->GetFrameTimestampsANDROID = (PFNEGLGETFRAMETIMESTAMPSANDROIDPROC) load(userptr, "eglGetFrameTimestampsANDROID");
    context->GetNextFrameIdANDROID = (PFNEGLGETNEXTFRAMEIDANDROIDPROC) load(userptr, "eglGetNextFrameIdANDROID");
}
static void glad_egl_load_EGL_ANDROID_get_native_client_buffer(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANDROID_get_native_client_buffer) return;
    context->GetNativeClientBufferANDROID = (PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC) load(userptr, "eglGetNativeClientBufferANDROID");
}
static void glad_egl_load_EGL_ANDROID_native_fence_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANDROID_native_fence_sync) return;
    context->DupNativeFenceFDANDROID = (PFNEGLDUPNATIVEFENCEFDANDROIDPROC) load(userptr, "eglDupNativeFenceFDANDROID");
}
static void glad_egl_load_EGL_ANDROID_presentation_time(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANDROID_presentation_time) return;
    context->PresentationTimeANDROID = (PFNEGLPRESENTATIONTIMEANDROIDPROC) load(userptr, "eglPresentationTimeANDROID");
}
static void glad_egl_load_EGL_ANGLE_device_creation(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_device_creation) return;
    context->CreateDeviceANGLE = (PFNEGLCREATEDEVICEANGLEPROC) load(userptr, "eglCreateDeviceANGLE");
    context->ReleaseDeviceANGLE = (PFNEGLRELEASEDEVICEANGLEPROC) load(userptr, "eglReleaseDeviceANGLE");
}
static void glad_egl_load_EGL_ANGLE_external_context_and_surface(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_external_context_and_surface) return;
    context->AcquireExternalContextANGLE = (PFNEGLACQUIREEXTERNALCONTEXTANGLEPROC) load(userptr, "eglAcquireExternalContextANGLE");
    context->ReleaseExternalContextANGLE = (PFNEGLRELEASEEXTERNALCONTEXTANGLEPROC) load(userptr, "eglReleaseExternalContextANGLE");
}
static void glad_egl_load_EGL_ANGLE_feature_control(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_feature_control) return;
    context->QueryDisplayAttribANGLE = (PFNEGLQUERYDISPLAYATTRIBANGLEPROC) load(userptr, "eglQueryDisplayAttribANGLE");
    context->QueryStringiANGLE = (PFNEGLQUERYSTRINGIANGLEPROC) load(userptr, "eglQueryStringiANGLE");
}
static void glad_egl_load_EGL_ANGLE_metal_shared_event_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_metal_shared_event_sync) return;
    context->CopyMetalSharedEventANGLE = (PFNEGLCOPYMETALSHAREDEVENTANGLEPROC) load(userptr, "eglCopyMetalSharedEventANGLE");
}
static void glad_egl_load_EGL_ANGLE_power_preference(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_power_preference) return;
    context->ForceGPUSwitchANGLE = (PFNEGLFORCEGPUSWITCHANGLEPROC) load(userptr, "eglForceGPUSwitchANGLE");
    context->HandleGPUSwitchANGLE = (PFNEGLHANDLEGPUSWITCHANGLEPROC) load(userptr, "eglHandleGPUSwitchANGLE");
    context->ReacquireHighPowerGPUANGLE = (PFNEGLREACQUIREHIGHPOWERGPUANGLEPROC) load(userptr, "eglReacquireHighPowerGPUANGLE");
    context->ReleaseHighPowerGPUANGLE = (PFNEGLRELEASEHIGHPOWERGPUANGLEPROC) load(userptr, "eglReleaseHighPowerGPUANGLE");
}
static void glad_egl_load_EGL_ANGLE_prepare_swap_buffers(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_prepare_swap_buffers) return;
    context->PrepareSwapBuffersANGLE = (PFNEGLPREPARESWAPBUFFERSANGLEPROC) load(userptr, "eglPrepareSwapBuffersANGLE");
}
static void glad_egl_load_EGL_ANGLE_program_cache_control(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_program_cache_control) return;
    context->ProgramCacheGetAttribANGLE = (PFNEGLPROGRAMCACHEGETATTRIBANGLEPROC) load(userptr, "eglProgramCacheGetAttribANGLE");
    context->ProgramCachePopulateANGLE = (PFNEGLPROGRAMCACHEPOPULATEANGLEPROC) load(userptr, "eglProgramCachePopulateANGLE");
    context->ProgramCacheQueryANGLE = (PFNEGLPROGRAMCACHEQUERYANGLEPROC) load(userptr, "eglProgramCacheQueryANGLE");
    context->ProgramCacheResizeANGLE = (PFNEGLPROGRAMCACHERESIZEANGLEPROC) load(userptr, "eglProgramCacheResizeANGLE");
}
static void glad_egl_load_EGL_ANGLE_query_surface_pointer(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_query_surface_pointer) return;
    context->QuerySurfacePointerANGLE = (PFNEGLQUERYSURFACEPOINTERANGLEPROC) load(userptr, "eglQuerySurfacePointerANGLE");
}
static void glad_egl_load_EGL_ANGLE_stream_producer_d3d_texture(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_stream_producer_d3d_texture) return;
    context->CreateStreamProducerD3DTextureANGLE = (PFNEGLCREATESTREAMPRODUCERD3DTEXTUREANGLEPROC) load(userptr, "eglCreateStreamProducerD3DTextureANGLE");
    context->StreamPostD3DTextureANGLE = (PFNEGLSTREAMPOSTD3DTEXTUREANGLEPROC) load(userptr, "eglStreamPostD3DTextureANGLE");
}
static void glad_egl_load_EGL_ANGLE_swap_with_frame_token(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_swap_with_frame_token) return;
    context->SwapBuffersWithFrameTokenANGLE = (PFNEGLSWAPBUFFERSWITHFRAMETOKENANGLEPROC) load(userptr, "eglSwapBuffersWithFrameTokenANGLE");
}
static void glad_egl_load_EGL_ANGLE_sync_control_rate(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_sync_control_rate) return;
    context->GetMscRateANGLE = (PFNEGLGETMSCRATEANGLEPROC) load(userptr, "eglGetMscRateANGLE");
}
static void glad_egl_load_EGL_ANGLE_vulkan_image(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_vulkan_image) return;
    context->ExportVkImageANGLE = (PFNEGLEXPORTVKIMAGEANGLEPROC) load(userptr, "eglExportVkImageANGLE");
}
static void glad_egl_load_EGL_ANGLE_wait_until_work_scheduled(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_wait_until_work_scheduled) return;
    context->WaitUntilWorkScheduledANGLE = (PFNEGLWAITUNTILWORKSCHEDULEDANGLEPROC) load(userptr, "eglWaitUntilWorkScheduledANGLE");
}
static void glad_egl_load_EGL_CHROMIUM_sync_control(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->CHROMIUM_sync_control) return;
    context->GetSyncValuesCHROMIUM = (PFNEGLGETSYNCVALUESCHROMIUMPROC) load(userptr, "eglGetSyncValuesCHROMIUM");
}
static void glad_egl_load_EGL_EXT_client_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_client_sync) return;
    context->ClientSignalSyncEXT = (PFNEGLCLIENTSIGNALSYNCEXTPROC) load(userptr, "eglClientSignalSyncEXT");
}
static void glad_egl_load_EGL_EXT_compositor(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_compositor) return;
    context->CompositorBindTexWindowEXT = (PFNEGLCOMPOSITORBINDTEXWINDOWEXTPROC) load(userptr, "eglCompositorBindTexWindowEXT");
    context->CompositorSetContextAttributesEXT = (PFNEGLCOMPOSITORSETCONTEXTATTRIBUTESEXTPROC) load(userptr, "eglCompositorSetContextAttributesEXT");
    context->CompositorSetContextListEXT = (PFNEGLCOMPOSITORSETCONTEXTLISTEXTPROC) load(userptr, "eglCompositorSetContextListEXT");
    context->CompositorSetSizeEXT = (PFNEGLCOMPOSITORSETSIZEEXTPROC) load(userptr, "eglCompositorSetSizeEXT");
    context->CompositorSetWindowAttributesEXT = (PFNEGLCOMPOSITORSETWINDOWATTRIBUTESEXTPROC) load(userptr, "eglCompositorSetWindowAttributesEXT");
    context->CompositorSetWindowListEXT = (PFNEGLCOMPOSITORSETWINDOWLISTEXTPROC) load(userptr, "eglCompositorSetWindowListEXT");
    context->CompositorSwapPolicyEXT = (PFNEGLCOMPOSITORSWAPPOLICYEXTPROC) load(userptr, "eglCompositorSwapPolicyEXT");
}
static void glad_egl_load_EGL_EXT_device_base(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_device_base) return;
    context->QueryDeviceAttribEXT = (PFNEGLQUERYDEVICEATTRIBEXTPROC) load(userptr, "eglQueryDeviceAttribEXT");
    context->QueryDeviceStringEXT = (PFNEGLQUERYDEVICESTRINGEXTPROC) load(userptr, "eglQueryDeviceStringEXT");
    context->QueryDevicesEXT = (PFNEGLQUERYDEVICESEXTPROC) load(userptr, "eglQueryDevicesEXT");
    context->QueryDisplayAttribEXT = (PFNEGLQUERYDISPLAYATTRIBEXTPROC) load(userptr, "eglQueryDisplayAttribEXT");
}
static void glad_egl_load_EGL_EXT_device_enumeration(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_device_enumeration) return;
    context->QueryDevicesEXT = (PFNEGLQUERYDEVICESEXTPROC) load(userptr, "eglQueryDevicesEXT");
}
static void glad_egl_load_EGL_EXT_device_persistent_id(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_device_persistent_id) return;
    context->QueryDeviceBinaryEXT = (PFNEGLQUERYDEVICEBINARYEXTPROC) load(userptr, "eglQueryDeviceBinaryEXT");
}
static void glad_egl_load_EGL_EXT_device_query(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_device_query) return;
    context->QueryDeviceAttribEXT = (PFNEGLQUERYDEVICEATTRIBEXTPROC) load(userptr, "eglQueryDeviceAttribEXT");
    context->QueryDeviceStringEXT = (PFNEGLQUERYDEVICESTRINGEXTPROC) load(userptr, "eglQueryDeviceStringEXT");
    context->QueryDisplayAttribEXT = (PFNEGLQUERYDISPLAYATTRIBEXTPROC) load(userptr, "eglQueryDisplayAttribEXT");
}
static void glad_egl_load_EGL_EXT_image_dma_buf_import_modifiers(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_image_dma_buf_import_modifiers) return;
    context->QueryDmaBufFormatsEXT = (PFNEGLQUERYDMABUFFORMATSEXTPROC) load(userptr, "eglQueryDmaBufFormatsEXT");
    context->QueryDmaBufModifiersEXT = (PFNEGLQUERYDMABUFMODIFIERSEXTPROC) load(userptr, "eglQueryDmaBufModifiersEXT");
}
static void glad_egl_load_EGL_EXT_output_base(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_output_base) return;
    context->GetOutputLayersEXT = (PFNEGLGETOUTPUTLAYERSEXTPROC) load(userptr, "eglGetOutputLayersEXT");
    context->GetOutputPortsEXT = (PFNEGLGETOUTPUTPORTSEXTPROC) load(userptr, "eglGetOutputPortsEXT");
    context->OutputLayerAttribEXT = (PFNEGLOUTPUTLAYERATTRIBEXTPROC) load(userptr, "eglOutputLayerAttribEXT");
    context->OutputPortAttribEXT = (PFNEGLOUTPUTPORTATTRIBEXTPROC) load(userptr, "eglOutputPortAttribEXT");
    context->QueryOutputLayerAttribEXT = (PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC) load(userptr, "eglQueryOutputLayerAttribEXT");
    context->QueryOutputLayerStringEXT = (PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC) load(userptr, "eglQueryOutputLayerStringEXT");
    context->QueryOutputPortAttribEXT = (PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC) load(userptr, "eglQueryOutputPortAttribEXT");
    context->QueryOutputPortStringEXT = (PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC) load(userptr, "eglQueryOutputPortStringEXT");
}
static void glad_egl_load_EGL_EXT_platform_base(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_platform_base) return;
    context->CreatePlatformPixmapSurfaceEXT = (PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC) load(userptr, "eglCreatePlatformPixmapSurfaceEXT");
    context->CreatePlatformWindowSurfaceEXT = (PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC) load(userptr, "eglCreatePlatformWindowSurfaceEXT");
    context->GetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYEXTPROC) load(userptr, "eglGetPlatformDisplayEXT");
}
static void glad_egl_load_EGL_EXT_stream_consumer_egloutput(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_stream_consumer_egloutput) return;
    context->StreamConsumerOutputEXT = (PFNEGLSTREAMCONSUMEROUTPUTEXTPROC) load(userptr, "eglStreamConsumerOutputEXT");
}
static void glad_egl_load_EGL_EXT_surface_compression(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_surface_compression) return;
    context->QuerySupportedCompressionRatesEXT = (PFNEGLQUERYSUPPORTEDCOMPRESSIONRATESEXTPROC) load(userptr, "eglQuerySupportedCompressionRatesEXT");
}
static void glad_egl_load_EGL_EXT_swap_buffers_with_damage(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_swap_buffers_with_damage) return;
    context->SwapBuffersWithDamageEXT = (PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC) load(userptr, "eglSwapBuffersWithDamageEXT");
}
static void glad_egl_load_EGL_EXT_sync_reuse(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_sync_reuse) return;
    context->UnsignalSyncEXT = (PFNEGLUNSIGNALSYNCEXTPROC) load(userptr, "eglUnsignalSyncEXT");
}
static void glad_egl_load_EGL_HI_clientpixmap(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->HI_clientpixmap) return;
    context->CreatePixmapSurfaceHI = (PFNEGLCREATEPIXMAPSURFACEHIPROC) load(userptr, "eglCreatePixmapSurfaceHI");
}
static void glad_egl_load_EGL_KHR_cl_event2(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_cl_event2) return;
    context->CreateSync64KHR = (PFNEGLCREATESYNC64KHRPROC) load(userptr, "eglCreateSync64KHR");
}
static void glad_egl_load_EGL_KHR_debug(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_debug) return;
    context->DebugMessageControlKHR = (PFNEGLDEBUGMESSAGECONTROLKHRPROC) load(userptr, "eglDebugMessageControlKHR");
    context->LabelObjectKHR = (PFNEGLLABELOBJECTKHRPROC) load(userptr, "eglLabelObjectKHR");
    context->QueryDebugKHR = (PFNEGLQUERYDEBUGKHRPROC) load(userptr, "eglQueryDebugKHR");
}
static void glad_egl_load_EGL_KHR_display_reference(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_display_reference) return;
    context->QueryDisplayAttribKHR = (PFNEGLQUERYDISPLAYATTRIBKHRPROC) load(userptr, "eglQueryDisplayAttribKHR");
}
static void glad_egl_load_EGL_KHR_fence_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_fence_sync) return;
    context->ClientWaitSyncKHR = (PFNEGLCLIENTWAITSYNCKHRPROC) load(userptr, "eglClientWaitSyncKHR");
    context->CreateSyncKHR = (PFNEGLCREATESYNCKHRPROC) load(userptr, "eglCreateSyncKHR");
    context->DestroySyncKHR = (PFNEGLDESTROYSYNCKHRPROC) load(userptr, "eglDestroySyncKHR");
    context->GetSyncAttribKHR = (PFNEGLGETSYNCATTRIBKHRPROC) load(userptr, "eglGetSyncAttribKHR");
}
static void glad_egl_load_EGL_KHR_image(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_image) return;
    context->CreateImageKHR = (PFNEGLCREATEIMAGEKHRPROC) load(userptr, "eglCreateImageKHR");
    context->DestroyImageKHR = (PFNEGLDESTROYIMAGEKHRPROC) load(userptr, "eglDestroyImageKHR");
}
static void glad_egl_load_EGL_KHR_image_base(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_image_base) return;
    context->CreateImageKHR = (PFNEGLCREATEIMAGEKHRPROC) load(userptr, "eglCreateImageKHR");
    context->DestroyImageKHR = (PFNEGLDESTROYIMAGEKHRPROC) load(userptr, "eglDestroyImageKHR");
}
static void glad_egl_load_EGL_KHR_lock_surface(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_lock_surface) return;
    context->LockSurfaceKHR = (PFNEGLLOCKSURFACEKHRPROC) load(userptr, "eglLockSurfaceKHR");
    context->UnlockSurfaceKHR = (PFNEGLUNLOCKSURFACEKHRPROC) load(userptr, "eglUnlockSurfaceKHR");
}
static void glad_egl_load_EGL_KHR_lock_surface3(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_lock_surface3) return;
    context->LockSurfaceKHR = (PFNEGLLOCKSURFACEKHRPROC) load(userptr, "eglLockSurfaceKHR");
    context->QuerySurface64KHR = (PFNEGLQUERYSURFACE64KHRPROC) load(userptr, "eglQuerySurface64KHR");
    context->UnlockSurfaceKHR = (PFNEGLUNLOCKSURFACEKHRPROC) load(userptr, "eglUnlockSurfaceKHR");
}
static void glad_egl_load_EGL_KHR_partial_update(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_partial_update) return;
    context->SetDamageRegionKHR = (PFNEGLSETDAMAGEREGIONKHRPROC) load(userptr, "eglSetDamageRegionKHR");
}
static void glad_egl_load_EGL_KHR_reusable_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_reusable_sync) return;
    context->ClientWaitSyncKHR = (PFNEGLCLIENTWAITSYNCKHRPROC) load(userptr, "eglClientWaitSyncKHR");
    context->CreateSyncKHR = (PFNEGLCREATESYNCKHRPROC) load(userptr, "eglCreateSyncKHR");
    context->DestroySyncKHR = (PFNEGLDESTROYSYNCKHRPROC) load(userptr, "eglDestroySyncKHR");
    context->GetSyncAttribKHR = (PFNEGLGETSYNCATTRIBKHRPROC) load(userptr, "eglGetSyncAttribKHR");
    context->SignalSyncKHR = (PFNEGLSIGNALSYNCKHRPROC) load(userptr, "eglSignalSyncKHR");
}
static void glad_egl_load_EGL_KHR_stream(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_stream) return;
    context->CreateStreamKHR = (PFNEGLCREATESTREAMKHRPROC) load(userptr, "eglCreateStreamKHR");
    context->DestroyStreamKHR = (PFNEGLDESTROYSTREAMKHRPROC) load(userptr, "eglDestroyStreamKHR");
    context->QueryStreamKHR = (PFNEGLQUERYSTREAMKHRPROC) load(userptr, "eglQueryStreamKHR");
    context->QueryStreamu64KHR = (PFNEGLQUERYSTREAMU64KHRPROC) load(userptr, "eglQueryStreamu64KHR");
    context->StreamAttribKHR = (PFNEGLSTREAMATTRIBKHRPROC) load(userptr, "eglStreamAttribKHR");
}
static void glad_egl_load_EGL_KHR_stream_attrib(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_stream_attrib) return;
    context->CreateStreamAttribKHR = (PFNEGLCREATESTREAMATTRIBKHRPROC) load(userptr, "eglCreateStreamAttribKHR");
    context->QueryStreamAttribKHR = (PFNEGLQUERYSTREAMATTRIBKHRPROC) load(userptr, "eglQueryStreamAttribKHR");
    context->SetStreamAttribKHR = (PFNEGLSETSTREAMATTRIBKHRPROC) load(userptr, "eglSetStreamAttribKHR");
    context->StreamConsumerAcquireAttribKHR = (PFNEGLSTREAMCONSUMERACQUIREATTRIBKHRPROC) load(userptr, "eglStreamConsumerAcquireAttribKHR");
    context->StreamConsumerReleaseAttribKHR = (PFNEGLSTREAMCONSUMERRELEASEATTRIBKHRPROC) load(userptr, "eglStreamConsumerReleaseAttribKHR");
}
static void glad_egl_load_EGL_KHR_stream_consumer_gltexture(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_stream_consumer_gltexture) return;
    context->StreamConsumerAcquireKHR = (PFNEGLSTREAMCONSUMERACQUIREKHRPROC) load(userptr, "eglStreamConsumerAcquireKHR");
    context->StreamConsumerGLTextureExternalKHR = (PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC) load(userptr, "eglStreamConsumerGLTextureExternalKHR");
    context->StreamConsumerReleaseKHR = (PFNEGLSTREAMCONSUMERRELEASEKHRPROC) load(userptr, "eglStreamConsumerReleaseKHR");
}
static void glad_egl_load_EGL_KHR_stream_cross_process_fd(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_stream_cross_process_fd) return;
    context->CreateStreamFromFileDescriptorKHR = (PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC) load(userptr, "eglCreateStreamFromFileDescriptorKHR");
    context->GetStreamFileDescriptorKHR = (PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC) load(userptr, "eglGetStreamFileDescriptorKHR");
}
static void glad_egl_load_EGL_KHR_stream_fifo(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_stream_fifo) return;
    context->QueryStreamTimeKHR = (PFNEGLQUERYSTREAMTIMEKHRPROC) load(userptr, "eglQueryStreamTimeKHR");
}
static void glad_egl_load_EGL_KHR_stream_producer_eglsurface(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_stream_producer_eglsurface) return;
    context->CreateStreamProducerSurfaceKHR = (PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC) load(userptr, "eglCreateStreamProducerSurfaceKHR");
}
static void glad_egl_load_EGL_KHR_swap_buffers_with_damage(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_swap_buffers_with_damage) return;
    context->SwapBuffersWithDamageKHR = (PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC) load(userptr, "eglSwapBuffersWithDamageKHR");
}
static void glad_egl_load_EGL_KHR_wait_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_wait_sync) return;
    context->WaitSyncKHR = (PFNEGLWAITSYNCKHRPROC) load(userptr, "eglWaitSyncKHR");
}
static void glad_egl_load_EGL_MESA_drm_image(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_drm_image) return;
    context->CreateDRMImageMESA = (PFNEGLCREATEDRMIMAGEMESAPROC) load(userptr, "eglCreateDRMImageMESA");
    context->ExportDRMImageMESA = (PFNEGLEXPORTDRMIMAGEMESAPROC) load(userptr, "eglExportDRMImageMESA");
}
static void glad_egl_load_EGL_MESA_image_dma_buf_export(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_image_dma_buf_export) return;
    context->ExportDMABUFImageMESA = (PFNEGLEXPORTDMABUFIMAGEMESAPROC) load(userptr, "eglExportDMABUFImageMESA");
    context->ExportDMABUFImageQueryMESA = (PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC) load(userptr, "eglExportDMABUFImageQueryMESA");
}
static void glad_egl_load_EGL_MESA_query_driver(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_query_driver) return;
    context->GetDisplayDriverConfig = (PFNEGLGETDISPLAYDRIVERCONFIGPROC) load(userptr, "eglGetDisplayDriverConfig");
    context->GetDisplayDriverName = (PFNEGLGETDISPLAYDRIVERNAMEPROC) load(userptr, "eglGetDisplayDriverName");
}
static void glad_egl_load_EGL_NOK_swap_region(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NOK_swap_region) return;
    context->SwapBuffersRegionNOK = (PFNEGLSWAPBUFFERSREGIONNOKPROC) load(userptr, "eglSwapBuffersRegionNOK");
}
static void glad_egl_load_EGL_NOK_swap_region2(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NOK_swap_region2) return;
    context->SwapBuffersRegion2NOK = (PFNEGLSWAPBUFFERSREGION2NOKPROC) load(userptr, "eglSwapBuffersRegion2NOK");
}
static void glad_egl_load_EGL_NV_native_query(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_native_query) return;
    context->QueryNativeDisplayNV = (PFNEGLQUERYNATIVEDISPLAYNVPROC) load(userptr, "eglQueryNativeDisplayNV");
    context->QueryNativePixmapNV = (PFNEGLQUERYNATIVEPIXMAPNVPROC) load(userptr, "eglQueryNativePixmapNV");
    context->QueryNativeWindowNV = (PFNEGLQUERYNATIVEWINDOWNVPROC) load(userptr, "eglQueryNativeWindowNV");
}
static void glad_egl_load_EGL_NV_post_sub_buffer(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_post_sub_buffer) return;
    context->PostSubBufferNV = (PFNEGLPOSTSUBBUFFERNVPROC) load(userptr, "eglPostSubBufferNV");
}
static void glad_egl_load_EGL_NV_stream_consumer_eglimage(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_stream_consumer_eglimage) return;
    context->QueryStreamConsumerEventNV = (PFNEGLQUERYSTREAMCONSUMEREVENTNVPROC) load(userptr, "eglQueryStreamConsumerEventNV");
    context->StreamAcquireImageNV = (PFNEGLSTREAMACQUIREIMAGENVPROC) load(userptr, "eglStreamAcquireImageNV");
    context->StreamImageConsumerConnectNV = (PFNEGLSTREAMIMAGECONSUMERCONNECTNVPROC) load(userptr, "eglStreamImageConsumerConnectNV");
    context->StreamReleaseImageNV = (PFNEGLSTREAMRELEASEIMAGENVPROC) load(userptr, "eglStreamReleaseImageNV");
}
static void glad_egl_load_EGL_NV_stream_consumer_gltexture_yuv(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_stream_consumer_gltexture_yuv) return;
    context->StreamConsumerGLTextureExternalAttribsNV = (PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC) load(userptr, "eglStreamConsumerGLTextureExternalAttribsNV");
}
static void glad_egl_load_EGL_NV_stream_flush(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_stream_flush) return;
    context->StreamFlushNV = (PFNEGLSTREAMFLUSHNVPROC) load(userptr, "eglStreamFlushNV");
}
static void glad_egl_load_EGL_NV_stream_metadata(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_stream_metadata) return;
    context->QueryDisplayAttribNV = (PFNEGLQUERYDISPLAYATTRIBNVPROC) load(userptr, "eglQueryDisplayAttribNV");
    context->QueryStreamMetadataNV = (PFNEGLQUERYSTREAMMETADATANVPROC) load(userptr, "eglQueryStreamMetadataNV");
    context->SetStreamMetadataNV = (PFNEGLSETSTREAMMETADATANVPROC) load(userptr, "eglSetStreamMetadataNV");
}
static void glad_egl_load_EGL_NV_stream_reset(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_stream_reset) return;
    context->ResetStreamNV = (PFNEGLRESETSTREAMNVPROC) load(userptr, "eglResetStreamNV");
}
static void glad_egl_load_EGL_NV_stream_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_stream_sync) return;
    context->CreateStreamSyncNV = (PFNEGLCREATESTREAMSYNCNVPROC) load(userptr, "eglCreateStreamSyncNV");
}
static void glad_egl_load_EGL_NV_sync(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_sync) return;
    context->ClientWaitSyncNV = (PFNEGLCLIENTWAITSYNCNVPROC) load(userptr, "eglClientWaitSyncNV");
    context->CreateFenceSyncNV = (PFNEGLCREATEFENCESYNCNVPROC) load(userptr, "eglCreateFenceSyncNV");
    context->DestroySyncNV = (PFNEGLDESTROYSYNCNVPROC) load(userptr, "eglDestroySyncNV");
    context->FenceNV = (PFNEGLFENCENVPROC) load(userptr, "eglFenceNV");
    context->GetSyncAttribNV = (PFNEGLGETSYNCATTRIBNVPROC) load(userptr, "eglGetSyncAttribNV");
    context->SignalSyncNV = (PFNEGLSIGNALSYNCNVPROC) load(userptr, "eglSignalSyncNV");
}
static void glad_egl_load_EGL_NV_system_time(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_system_time) return;
    context->GetSystemTimeFrequencyNV = (PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC) load(userptr, "eglGetSystemTimeFrequencyNV");
    context->GetSystemTimeNV = (PFNEGLGETSYSTEMTIMENVPROC) load(userptr, "eglGetSystemTimeNV");
}
static void glad_egl_load_EGL_WL_bind_wayland_display(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->WL_bind_wayland_display) return;
    context->BindWaylandDisplayWL = (PFNEGLBINDWAYLANDDISPLAYWLPROC) load(userptr, "eglBindWaylandDisplayWL");
    context->QueryWaylandBufferWL = (PFNEGLQUERYWAYLANDBUFFERWLPROC) load(userptr, "eglQueryWaylandBufferWL");
    context->UnbindWaylandDisplayWL = (PFNEGLUNBINDWAYLANDDISPLAYWLPROC) load(userptr, "eglUnbindWaylandDisplayWL");
}
static void glad_egl_load_EGL_WL_create_wayland_buffer_from_image(GladEGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->WL_create_wayland_buffer_from_image) return;
    context->CreateWaylandBufferFromImageWL = (PFNEGLCREATEWAYLANDBUFFERFROMIMAGEWLPROC) load(userptr, "eglCreateWaylandBufferFromImageWL");
}


static void glad_egl_resolve_aliases(GladEGLContext *context) {
    if (context->ClientWaitSync == NULL && context->ClientWaitSyncKHR != NULL) context->ClientWaitSync = (PFNEGLCLIENTWAITSYNCPROC)context->ClientWaitSyncKHR;
    if (context->ClientWaitSyncKHR == NULL && context->ClientWaitSync != NULL) context->ClientWaitSyncKHR = (PFNEGLCLIENTWAITSYNCKHRPROC)context->ClientWaitSync;
    if (context->CreateSync == NULL && context->CreateSync64KHR != NULL) context->CreateSync = (PFNEGLCREATESYNCPROC)context->CreateSync64KHR;
    if (context->CreateSync64KHR == NULL && context->CreateSync != NULL) context->CreateSync64KHR = (PFNEGLCREATESYNC64KHRPROC)context->CreateSync;
    if (context->DestroyImage == NULL && context->DestroyImageKHR != NULL) context->DestroyImage = (PFNEGLDESTROYIMAGEPROC)context->DestroyImageKHR;
    if (context->DestroyImageKHR == NULL && context->DestroyImage != NULL) context->DestroyImageKHR = (PFNEGLDESTROYIMAGEKHRPROC)context->DestroyImage;
    if (context->DestroySync == NULL && context->DestroySyncKHR != NULL) context->DestroySync = (PFNEGLDESTROYSYNCPROC)context->DestroySyncKHR;
    if (context->DestroySyncKHR == NULL && context->DestroySync != NULL) context->DestroySyncKHR = (PFNEGLDESTROYSYNCKHRPROC)context->DestroySync;
    if (context->QueryDisplayAttribEXT == NULL && context->QueryDisplayAttribKHR != NULL) context->QueryDisplayAttribEXT = (PFNEGLQUERYDISPLAYATTRIBEXTPROC)context->QueryDisplayAttribKHR;
    if (context->QueryDisplayAttribEXT == NULL && context->QueryDisplayAttribNV != NULL) context->QueryDisplayAttribEXT = (PFNEGLQUERYDISPLAYATTRIBEXTPROC)context->QueryDisplayAttribNV;
    if (context->QueryDisplayAttribKHR == NULL && context->QueryDisplayAttribEXT != NULL) context->QueryDisplayAttribKHR = (PFNEGLQUERYDISPLAYATTRIBKHRPROC)context->QueryDisplayAttribEXT;
    if (context->QueryDisplayAttribKHR == NULL && context->QueryDisplayAttribNV != NULL) context->QueryDisplayAttribKHR = (PFNEGLQUERYDISPLAYATTRIBKHRPROC)context->QueryDisplayAttribNV;
    if (context->QueryDisplayAttribNV == NULL && context->QueryDisplayAttribEXT != NULL) context->QueryDisplayAttribNV = (PFNEGLQUERYDISPLAYATTRIBNVPROC)context->QueryDisplayAttribEXT;
    if (context->QueryDisplayAttribNV == NULL && context->QueryDisplayAttribKHR != NULL) context->QueryDisplayAttribNV = (PFNEGLQUERYDISPLAYATTRIBNVPROC)context->QueryDisplayAttribKHR;
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

    context->ANDROID_GLES_layers = glad_egl_has_extension(extensions, "EGL_ANDROID_GLES_layers");
    context->ANDROID_blob_cache = glad_egl_has_extension(extensions, "EGL_ANDROID_blob_cache");
    context->ANDROID_create_native_client_buffer = glad_egl_has_extension(extensions, "EGL_ANDROID_create_native_client_buffer");
    context->ANDROID_framebuffer_target = glad_egl_has_extension(extensions, "EGL_ANDROID_framebuffer_target");
    context->ANDROID_front_buffer_auto_refresh = glad_egl_has_extension(extensions, "EGL_ANDROID_front_buffer_auto_refresh");
    context->ANDROID_get_frame_timestamps = glad_egl_has_extension(extensions, "EGL_ANDROID_get_frame_timestamps");
    context->ANDROID_get_native_client_buffer = glad_egl_has_extension(extensions, "EGL_ANDROID_get_native_client_buffer");
    context->ANDROID_image_native_buffer = glad_egl_has_extension(extensions, "EGL_ANDROID_image_native_buffer");
    context->ANDROID_native_fence_sync = glad_egl_has_extension(extensions, "EGL_ANDROID_native_fence_sync");
    context->ANDROID_presentation_time = glad_egl_has_extension(extensions, "EGL_ANDROID_presentation_time");
    context->ANDROID_recordable = glad_egl_has_extension(extensions, "EGL_ANDROID_recordable");
    context->ANGLE_colorspace_attribute_passthrough = glad_egl_has_extension(extensions, "EGL_ANGLE_colorspace_attribute_passthrough");
    context->ANGLE_context_virtualization = glad_egl_has_extension(extensions, "EGL_ANGLE_context_virtualization");
    context->ANGLE_create_context_backwards_compatible = glad_egl_has_extension(extensions, "EGL_ANGLE_create_context_backwards_compatible");
    context->ANGLE_create_context_client_arrays = glad_egl_has_extension(extensions, "EGL_ANGLE_create_context_client_arrays");
    context->ANGLE_create_context_extensions_enabled = glad_egl_has_extension(extensions, "EGL_ANGLE_create_context_extensions_enabled");
    context->ANGLE_create_context_webgl_compatibility = glad_egl_has_extension(extensions, "EGL_ANGLE_create_context_webgl_compatibility");
    context->ANGLE_create_surface_swap_interval = glad_egl_has_extension(extensions, "EGL_ANGLE_create_surface_swap_interval");
    context->ANGLE_d3d_share_handle_client_buffer = glad_egl_has_extension(extensions, "EGL_ANGLE_d3d_share_handle_client_buffer");
    context->ANGLE_d3d_texture_client_buffer = glad_egl_has_extension(extensions, "EGL_ANGLE_d3d_texture_client_buffer");
    context->ANGLE_device_cgl = glad_egl_has_extension(extensions, "EGL_ANGLE_device_cgl");
    context->ANGLE_device_creation = glad_egl_has_extension(extensions, "EGL_ANGLE_device_creation");
    context->ANGLE_device_d3d = glad_egl_has_extension(extensions, "EGL_ANGLE_device_d3d");
    context->ANGLE_device_eagl = glad_egl_has_extension(extensions, "EGL_ANGLE_device_eagl");
    context->ANGLE_device_metal = glad_egl_has_extension(extensions, "EGL_ANGLE_device_metal");
    context->ANGLE_device_vulkan = glad_egl_has_extension(extensions, "EGL_ANGLE_device_vulkan");
    context->ANGLE_direct_composition = glad_egl_has_extension(extensions, "EGL_ANGLE_direct_composition");
    context->ANGLE_display_power_preference = glad_egl_has_extension(extensions, "EGL_ANGLE_display_power_preference");
    context->ANGLE_display_semaphore_share_group = glad_egl_has_extension(extensions, "EGL_ANGLE_display_semaphore_share_group");
    context->ANGLE_display_texture_share_group = glad_egl_has_extension(extensions, "EGL_ANGLE_display_texture_share_group");
    context->ANGLE_experimental_present_path = glad_egl_has_extension(extensions, "EGL_ANGLE_experimental_present_path");
    context->ANGLE_external_context_and_surface = glad_egl_has_extension(extensions, "EGL_ANGLE_external_context_and_surface");
    context->ANGLE_feature_control = glad_egl_has_extension(extensions, "EGL_ANGLE_feature_control");
    context->ANGLE_ggp_stream_descriptor = glad_egl_has_extension(extensions, "EGL_ANGLE_ggp_stream_descriptor");
    context->ANGLE_iosurface_client_buffer = glad_egl_has_extension(extensions, "EGL_ANGLE_iosurface_client_buffer");
    context->ANGLE_keyed_mutex = glad_egl_has_extension(extensions, "EGL_ANGLE_keyed_mutex");
    context->ANGLE_metal_create_context_ownership_identity = glad_egl_has_extension(extensions, "EGL_ANGLE_metal_create_context_ownership_identity");
    context->ANGLE_metal_shared_event_sync = glad_egl_has_extension(extensions, "EGL_ANGLE_metal_shared_event_sync");
    context->ANGLE_metal_texture_client_buffer = glad_egl_has_extension(extensions, "EGL_ANGLE_metal_texture_client_buffer");
    context->ANGLE_platform_angle = glad_egl_has_extension(extensions, "EGL_ANGLE_platform_angle");
    context->ANGLE_platform_angle_d3d = glad_egl_has_extension(extensions, "EGL_ANGLE_platform_angle_d3d");
    context->ANGLE_platform_angle_d3d11on12 = glad_egl_has_extension(extensions, "EGL_ANGLE_platform_angle_d3d11on12");
    context->ANGLE_platform_angle_d3d_luid = glad_egl_has_extension(extensions, "EGL_ANGLE_platform_angle_d3d_luid");
    context->ANGLE_platform_angle_device_context_volatile_cgl = glad_egl_has_extension(extensions, "EGL_ANGLE_platform_angle_device_context_volatile_cgl");
    context->ANGLE_platform_angle_device_context_volatile_eagl = glad_egl_has_extension(extensions, "EGL_ANGLE_platform_angle_device_context_volatile_eagl");
    context->ANGLE_platform_angle_device_id = glad_egl_has_extension(extensions, "EGL_ANGLE_platform_angle_device_id");
    context->ANGLE_platform_angle_device_type_egl = glad_egl_has_extension(extensions, "EGL_ANGLE_platform_angle_device_type_egl");
    context->ANGLE_platform_angle_device_type_swiftshader = glad_egl_has_extension(extensions, "EGL_ANGLE_platform_angle_device_type_swiftshader");
    context->ANGLE_platform_angle_metal = glad_egl_has_extension(extensions, "EGL_ANGLE_platform_angle_metal");
    context->ANGLE_platform_angle_null = glad_egl_has_extension(extensions, "EGL_ANGLE_platform_angle_null");
    context->ANGLE_platform_angle_opengl = glad_egl_has_extension(extensions, "EGL_ANGLE_platform_angle_opengl");
    context->ANGLE_platform_angle_vulkan = glad_egl_has_extension(extensions, "EGL_ANGLE_platform_angle_vulkan");
    context->ANGLE_power_preference = glad_egl_has_extension(extensions, "EGL_ANGLE_power_preference");
    context->ANGLE_prepare_swap_buffers = glad_egl_has_extension(extensions, "EGL_ANGLE_prepare_swap_buffers");
    context->ANGLE_program_cache_control = glad_egl_has_extension(extensions, "EGL_ANGLE_program_cache_control");
    context->ANGLE_query_surface_pointer = glad_egl_has_extension(extensions, "EGL_ANGLE_query_surface_pointer");
    context->ANGLE_robust_resource_initialization = glad_egl_has_extension(extensions, "EGL_ANGLE_robust_resource_initialization");
    context->ANGLE_stream_producer_d3d_texture = glad_egl_has_extension(extensions, "EGL_ANGLE_stream_producer_d3d_texture");
    context->ANGLE_surface_d3d_texture_2d_share_handle = glad_egl_has_extension(extensions, "EGL_ANGLE_surface_d3d_texture_2d_share_handle");
    context->ANGLE_surface_orientation = glad_egl_has_extension(extensions, "EGL_ANGLE_surface_orientation");
    context->ANGLE_swap_with_frame_token = glad_egl_has_extension(extensions, "EGL_ANGLE_swap_with_frame_token");
    context->ANGLE_sync_control_rate = glad_egl_has_extension(extensions, "EGL_ANGLE_sync_control_rate");
    context->ANGLE_vulkan_display = glad_egl_has_extension(extensions, "EGL_ANGLE_vulkan_display");
    context->ANGLE_vulkan_image = glad_egl_has_extension(extensions, "EGL_ANGLE_vulkan_image");
    context->ANGLE_wait_until_work_scheduled = glad_egl_has_extension(extensions, "EGL_ANGLE_wait_until_work_scheduled");
    context->ANGLE_window_fixed_size = glad_egl_has_extension(extensions, "EGL_ANGLE_window_fixed_size");
    context->ANGLE_x11_visual = glad_egl_has_extension(extensions, "EGL_ANGLE_x11_visual");
    context->ARM_image_format = glad_egl_has_extension(extensions, "EGL_ARM_image_format");
    context->ARM_implicit_external_sync = glad_egl_has_extension(extensions, "EGL_ARM_implicit_external_sync");
    context->ARM_pixmap_multisample_discard = glad_egl_has_extension(extensions, "EGL_ARM_pixmap_multisample_discard");
    context->CHROMIUM_sync_control = glad_egl_has_extension(extensions, "EGL_CHROMIUM_sync_control");
    context->EXT_bind_to_front = glad_egl_has_extension(extensions, "EGL_EXT_bind_to_front");
    context->EXT_buffer_age = glad_egl_has_extension(extensions, "EGL_EXT_buffer_age");
    context->EXT_client_extensions = glad_egl_has_extension(extensions, "EGL_EXT_client_extensions");
    context->EXT_client_sync = glad_egl_has_extension(extensions, "EGL_EXT_client_sync");
    context->EXT_compositor = glad_egl_has_extension(extensions, "EGL_EXT_compositor");
    context->EXT_config_select_group = glad_egl_has_extension(extensions, "EGL_EXT_config_select_group");
    context->EXT_create_context_robustness = glad_egl_has_extension(extensions, "EGL_EXT_create_context_robustness");
    context->EXT_device_base = glad_egl_has_extension(extensions, "EGL_EXT_device_base");
    context->EXT_device_drm = glad_egl_has_extension(extensions, "EGL_EXT_device_drm");
    context->EXT_device_drm_render_node = glad_egl_has_extension(extensions, "EGL_EXT_device_drm_render_node");
    context->EXT_device_enumeration = glad_egl_has_extension(extensions, "EGL_EXT_device_enumeration");
    context->EXT_device_openwf = glad_egl_has_extension(extensions, "EGL_EXT_device_openwf");
    context->EXT_device_persistent_id = glad_egl_has_extension(extensions, "EGL_EXT_device_persistent_id");
    context->EXT_device_query = glad_egl_has_extension(extensions, "EGL_EXT_device_query");
    context->EXT_device_query_name = glad_egl_has_extension(extensions, "EGL_EXT_device_query_name");
    context->EXT_explicit_device = glad_egl_has_extension(extensions, "EGL_EXT_explicit_device");
    context->EXT_gl_colorspace_bt2020_hlg = glad_egl_has_extension(extensions, "EGL_EXT_gl_colorspace_bt2020_hlg");
    context->EXT_gl_colorspace_bt2020_linear = glad_egl_has_extension(extensions, "EGL_EXT_gl_colorspace_bt2020_linear");
    context->EXT_gl_colorspace_bt2020_pq = glad_egl_has_extension(extensions, "EGL_EXT_gl_colorspace_bt2020_pq");
    context->EXT_gl_colorspace_display_p3 = glad_egl_has_extension(extensions, "EGL_EXT_gl_colorspace_display_p3");
    context->EXT_gl_colorspace_display_p3_linear = glad_egl_has_extension(extensions, "EGL_EXT_gl_colorspace_display_p3_linear");
    context->EXT_gl_colorspace_display_p3_passthrough = glad_egl_has_extension(extensions, "EGL_EXT_gl_colorspace_display_p3_passthrough");
    context->EXT_gl_colorspace_scrgb = glad_egl_has_extension(extensions, "EGL_EXT_gl_colorspace_scrgb");
    context->EXT_gl_colorspace_scrgb_linear = glad_egl_has_extension(extensions, "EGL_EXT_gl_colorspace_scrgb_linear");
    context->EXT_image_dma_buf_import = glad_egl_has_extension(extensions, "EGL_EXT_image_dma_buf_import");
    context->EXT_image_dma_buf_import_modifiers = glad_egl_has_extension(extensions, "EGL_EXT_image_dma_buf_import_modifiers");
    context->EXT_image_gl_colorspace = glad_egl_has_extension(extensions, "EGL_EXT_image_gl_colorspace");
    context->EXT_image_implicit_sync_control = glad_egl_has_extension(extensions, "EGL_EXT_image_implicit_sync_control");
    context->EXT_multiview_window = glad_egl_has_extension(extensions, "EGL_EXT_multiview_window");
    context->EXT_output_base = glad_egl_has_extension(extensions, "EGL_EXT_output_base");
    context->EXT_output_drm = glad_egl_has_extension(extensions, "EGL_EXT_output_drm");
    context->EXT_output_openwf = glad_egl_has_extension(extensions, "EGL_EXT_output_openwf");
    context->EXT_pixel_format_float = glad_egl_has_extension(extensions, "EGL_EXT_pixel_format_float");
    context->EXT_platform_base = glad_egl_has_extension(extensions, "EGL_EXT_platform_base");
    context->EXT_platform_device = glad_egl_has_extension(extensions, "EGL_EXT_platform_device");
    context->EXT_platform_wayland = glad_egl_has_extension(extensions, "EGL_EXT_platform_wayland");
    context->EXT_platform_x11 = glad_egl_has_extension(extensions, "EGL_EXT_platform_x11");
    context->EXT_platform_xcb = glad_egl_has_extension(extensions, "EGL_EXT_platform_xcb");
    context->EXT_present_opaque = glad_egl_has_extension(extensions, "EGL_EXT_present_opaque");
    context->EXT_protected_content = glad_egl_has_extension(extensions, "EGL_EXT_protected_content");
    context->EXT_protected_surface = glad_egl_has_extension(extensions, "EGL_EXT_protected_surface");
    context->EXT_stream_consumer_egloutput = glad_egl_has_extension(extensions, "EGL_EXT_stream_consumer_egloutput");
    context->EXT_surface_CTA861_3_metadata = glad_egl_has_extension(extensions, "EGL_EXT_surface_CTA861_3_metadata");
    context->EXT_surface_SMPTE2086_metadata = glad_egl_has_extension(extensions, "EGL_EXT_surface_SMPTE2086_metadata");
    context->EXT_surface_compression = glad_egl_has_extension(extensions, "EGL_EXT_surface_compression");
    context->EXT_swap_buffers_with_damage = glad_egl_has_extension(extensions, "EGL_EXT_swap_buffers_with_damage");
    context->EXT_sync_reuse = glad_egl_has_extension(extensions, "EGL_EXT_sync_reuse");
    context->EXT_yuv_surface = glad_egl_has_extension(extensions, "EGL_EXT_yuv_surface");
    context->HI_clientpixmap = glad_egl_has_extension(extensions, "EGL_HI_clientpixmap");
    context->HI_colorformats = glad_egl_has_extension(extensions, "EGL_HI_colorformats");
    context->IMG_context_priority = glad_egl_has_extension(extensions, "EGL_IMG_context_priority");
    context->IMG_image_plane_attribs = glad_egl_has_extension(extensions, "EGL_IMG_image_plane_attribs");
    context->KHR_cl_event = glad_egl_has_extension(extensions, "EGL_KHR_cl_event");
    context->KHR_cl_event2 = glad_egl_has_extension(extensions, "EGL_KHR_cl_event2");
    context->KHR_client_get_all_proc_addresses = glad_egl_has_extension(extensions, "EGL_KHR_client_get_all_proc_addresses");
    context->KHR_config_attribs = glad_egl_has_extension(extensions, "EGL_KHR_config_attribs");
    context->KHR_context_flush_control = glad_egl_has_extension(extensions, "EGL_KHR_context_flush_control");
    context->KHR_create_context = glad_egl_has_extension(extensions, "EGL_KHR_create_context");
    context->KHR_create_context_no_error = glad_egl_has_extension(extensions, "EGL_KHR_create_context_no_error");
    context->KHR_debug = glad_egl_has_extension(extensions, "EGL_KHR_debug");
    context->KHR_display_reference = glad_egl_has_extension(extensions, "EGL_KHR_display_reference");
    context->KHR_fence_sync = glad_egl_has_extension(extensions, "EGL_KHR_fence_sync");
    context->KHR_get_all_proc_addresses = glad_egl_has_extension(extensions, "EGL_KHR_get_all_proc_addresses");
    context->KHR_gl_colorspace = glad_egl_has_extension(extensions, "EGL_KHR_gl_colorspace");
    context->KHR_gl_renderbuffer_image = glad_egl_has_extension(extensions, "EGL_KHR_gl_renderbuffer_image");
    context->KHR_gl_texture_2D_image = glad_egl_has_extension(extensions, "EGL_KHR_gl_texture_2D_image");
    context->KHR_gl_texture_3D_image = glad_egl_has_extension(extensions, "EGL_KHR_gl_texture_3D_image");
    context->KHR_gl_texture_cubemap_image = glad_egl_has_extension(extensions, "EGL_KHR_gl_texture_cubemap_image");
    context->KHR_image = glad_egl_has_extension(extensions, "EGL_KHR_image");
    context->KHR_image_base = glad_egl_has_extension(extensions, "EGL_KHR_image_base");
    context->KHR_image_pixmap = glad_egl_has_extension(extensions, "EGL_KHR_image_pixmap");
    context->KHR_lock_surface = glad_egl_has_extension(extensions, "EGL_KHR_lock_surface");
    context->KHR_lock_surface2 = glad_egl_has_extension(extensions, "EGL_KHR_lock_surface2");
    context->KHR_lock_surface3 = glad_egl_has_extension(extensions, "EGL_KHR_lock_surface3");
    context->KHR_mutable_render_buffer = glad_egl_has_extension(extensions, "EGL_KHR_mutable_render_buffer");
    context->KHR_no_config_context = glad_egl_has_extension(extensions, "EGL_KHR_no_config_context");
    context->KHR_partial_update = glad_egl_has_extension(extensions, "EGL_KHR_partial_update");
    context->KHR_platform_android = glad_egl_has_extension(extensions, "EGL_KHR_platform_android");
    context->KHR_platform_gbm = glad_egl_has_extension(extensions, "EGL_KHR_platform_gbm");
    context->KHR_platform_wayland = glad_egl_has_extension(extensions, "EGL_KHR_platform_wayland");
    context->KHR_platform_x11 = glad_egl_has_extension(extensions, "EGL_KHR_platform_x11");
    context->KHR_reusable_sync = glad_egl_has_extension(extensions, "EGL_KHR_reusable_sync");
    context->KHR_stream = glad_egl_has_extension(extensions, "EGL_KHR_stream");
    context->KHR_stream_attrib = glad_egl_has_extension(extensions, "EGL_KHR_stream_attrib");
    context->KHR_stream_consumer_gltexture = glad_egl_has_extension(extensions, "EGL_KHR_stream_consumer_gltexture");
    context->KHR_stream_cross_process_fd = glad_egl_has_extension(extensions, "EGL_KHR_stream_cross_process_fd");
    context->KHR_stream_fifo = glad_egl_has_extension(extensions, "EGL_KHR_stream_fifo");
    context->KHR_stream_producer_aldatalocator = glad_egl_has_extension(extensions, "EGL_KHR_stream_producer_aldatalocator");
    context->KHR_stream_producer_eglsurface = glad_egl_has_extension(extensions, "EGL_KHR_stream_producer_eglsurface");
    context->KHR_surfaceless_context = glad_egl_has_extension(extensions, "EGL_KHR_surfaceless_context");
    context->KHR_swap_buffers_with_damage = glad_egl_has_extension(extensions, "EGL_KHR_swap_buffers_with_damage");
    context->KHR_vg_parent_image = glad_egl_has_extension(extensions, "EGL_KHR_vg_parent_image");
    context->KHR_wait_sync = glad_egl_has_extension(extensions, "EGL_KHR_wait_sync");
    context->MESA_drm_image = glad_egl_has_extension(extensions, "EGL_MESA_drm_image");
    context->MESA_image_dma_buf_export = glad_egl_has_extension(extensions, "EGL_MESA_image_dma_buf_export");
    context->MESA_platform_gbm = glad_egl_has_extension(extensions, "EGL_MESA_platform_gbm");
    context->MESA_platform_surfaceless = glad_egl_has_extension(extensions, "EGL_MESA_platform_surfaceless");
    context->MESA_query_driver = glad_egl_has_extension(extensions, "EGL_MESA_query_driver");
    context->NOK_swap_region = glad_egl_has_extension(extensions, "EGL_NOK_swap_region");
    context->NOK_swap_region2 = glad_egl_has_extension(extensions, "EGL_NOK_swap_region2");
    context->NOK_texture_from_pixmap = glad_egl_has_extension(extensions, "EGL_NOK_texture_from_pixmap");
    context->NV_3dvision_surface = glad_egl_has_extension(extensions, "EGL_NV_3dvision_surface");
    context->NV_context_priority_realtime = glad_egl_has_extension(extensions, "EGL_NV_context_priority_realtime");
    context->NV_coverage_sample = glad_egl_has_extension(extensions, "EGL_NV_coverage_sample");
    context->NV_coverage_sample_resolve = glad_egl_has_extension(extensions, "EGL_NV_coverage_sample_resolve");
    context->NV_cuda_event = glad_egl_has_extension(extensions, "EGL_NV_cuda_event");
    context->NV_depth_nonlinear = glad_egl_has_extension(extensions, "EGL_NV_depth_nonlinear");
    context->NV_device_cuda = glad_egl_has_extension(extensions, "EGL_NV_device_cuda");
    context->NV_native_query = glad_egl_has_extension(extensions, "EGL_NV_native_query");
    context->NV_post_convert_rounding = glad_egl_has_extension(extensions, "EGL_NV_post_convert_rounding");
    context->NV_post_sub_buffer = glad_egl_has_extension(extensions, "EGL_NV_post_sub_buffer");
    context->NV_quadruple_buffer = glad_egl_has_extension(extensions, "EGL_NV_quadruple_buffer");
    context->NV_robustness_video_memory_purge = glad_egl_has_extension(extensions, "EGL_NV_robustness_video_memory_purge");
    context->NV_stream_consumer_eglimage = glad_egl_has_extension(extensions, "EGL_NV_stream_consumer_eglimage");
    context->NV_stream_consumer_eglimage_use_scanout_attrib = glad_egl_has_extension(extensions, "EGL_NV_stream_consumer_eglimage_use_scanout_attrib");
    context->NV_stream_consumer_gltexture_yuv = glad_egl_has_extension(extensions, "EGL_NV_stream_consumer_gltexture_yuv");
    context->NV_stream_cross_display = glad_egl_has_extension(extensions, "EGL_NV_stream_cross_display");
    context->NV_stream_cross_object = glad_egl_has_extension(extensions, "EGL_NV_stream_cross_object");
    context->NV_stream_cross_partition = glad_egl_has_extension(extensions, "EGL_NV_stream_cross_partition");
    context->NV_stream_cross_process = glad_egl_has_extension(extensions, "EGL_NV_stream_cross_process");
    context->NV_stream_cross_system = glad_egl_has_extension(extensions, "EGL_NV_stream_cross_system");
    context->NV_stream_dma = glad_egl_has_extension(extensions, "EGL_NV_stream_dma");
    context->NV_stream_fifo_next = glad_egl_has_extension(extensions, "EGL_NV_stream_fifo_next");
    context->NV_stream_fifo_synchronous = glad_egl_has_extension(extensions, "EGL_NV_stream_fifo_synchronous");
    context->NV_stream_flush = glad_egl_has_extension(extensions, "EGL_NV_stream_flush");
    context->NV_stream_frame_limits = glad_egl_has_extension(extensions, "EGL_NV_stream_frame_limits");
    context->NV_stream_metadata = glad_egl_has_extension(extensions, "EGL_NV_stream_metadata");
    context->NV_stream_origin = glad_egl_has_extension(extensions, "EGL_NV_stream_origin");
    context->NV_stream_remote = glad_egl_has_extension(extensions, "EGL_NV_stream_remote");
    context->NV_stream_reset = glad_egl_has_extension(extensions, "EGL_NV_stream_reset");
    context->NV_stream_socket = glad_egl_has_extension(extensions, "EGL_NV_stream_socket");
    context->NV_stream_socket_inet = glad_egl_has_extension(extensions, "EGL_NV_stream_socket_inet");
    context->NV_stream_socket_unix = glad_egl_has_extension(extensions, "EGL_NV_stream_socket_unix");
    context->NV_stream_sync = glad_egl_has_extension(extensions, "EGL_NV_stream_sync");
    context->NV_sync = glad_egl_has_extension(extensions, "EGL_NV_sync");
    context->NV_system_time = glad_egl_has_extension(extensions, "EGL_NV_system_time");
    context->NV_triple_buffer = glad_egl_has_extension(extensions, "EGL_NV_triple_buffer");
    context->QNX_image_native_buffer = glad_egl_has_extension(extensions, "EGL_QNX_image_native_buffer");
    context->QNX_platform_screen = glad_egl_has_extension(extensions, "EGL_QNX_platform_screen");
    context->TIZEN_image_native_buffer = glad_egl_has_extension(extensions, "EGL_TIZEN_image_native_buffer");
    context->TIZEN_image_native_surface = glad_egl_has_extension(extensions, "EGL_TIZEN_image_native_surface");
    context->WL_bind_wayland_display = glad_egl_has_extension(extensions, "EGL_WL_bind_wayland_display");
    context->WL_create_wayland_buffer_from_image = glad_egl_has_extension(extensions, "EGL_WL_create_wayland_buffer_from_image");

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
        context->glad_loader_handle = glad_get_dlopen_handle(NAMES, sizeof(NAMES) / sizeof(NAMES[0]));
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
