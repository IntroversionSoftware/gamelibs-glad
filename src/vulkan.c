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

#include <glad/vulkan.h>

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

#ifdef __cplusplus
}
#endif

#endif /* GLAD_IMPL_HASHSEARCH_C_ */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
GladVulkanContext glad_vulkan_context = {};
#else
GladVulkanContext glad_vulkan_context = { 0 };
#endif

static const char * const GLAD_Vulkan_fn_names[] = {
    /*    0 */ "vkCreateInstance",
    /*    1 */ "vkDestroyInstance",
    /*    2 */ "vkEnumeratePhysicalDevices",
    /*    3 */ "vkGetPhysicalDeviceFeatures",
    /*    4 */ "vkGetPhysicalDeviceFormatProperties",
    /*    5 */ "vkGetPhysicalDeviceImageFormatProperties",
    /*    6 */ "vkGetPhysicalDeviceProperties",
    /*    7 */ "vkGetPhysicalDeviceQueueFamilyProperties",
    /*    8 */ "vkGetPhysicalDeviceMemoryProperties",
    /*    9 */ "vkGetInstanceProcAddr",
    /*   10 */ "vkGetDeviceProcAddr",
    /*   11 */ "vkCreateDevice",
    /*   12 */ "vkDestroyDevice",
    /*   13 */ "vkEnumerateInstanceExtensionProperties",
    /*   14 */ "vkEnumerateDeviceExtensionProperties",
    /*   15 */ "vkEnumerateInstanceLayerProperties",
    /*   16 */ "vkEnumerateDeviceLayerProperties",
    /*   17 */ "vkGetDeviceQueue",
    /*   18 */ "vkQueueSubmit",
    /*   19 */ "vkQueueWaitIdle",
    /*   20 */ "vkDeviceWaitIdle",
    /*   21 */ "vkAllocateMemory",
    /*   22 */ "vkFreeMemory",
    /*   23 */ "vkMapMemory",
    /*   24 */ "vkUnmapMemory",
    /*   25 */ "vkFlushMappedMemoryRanges",
    /*   26 */ "vkInvalidateMappedMemoryRanges",
    /*   27 */ "vkGetDeviceMemoryCommitment",
    /*   28 */ "vkBindBufferMemory",
    /*   29 */ "vkBindImageMemory",
    /*   30 */ "vkGetBufferMemoryRequirements",
    /*   31 */ "vkGetImageMemoryRequirements",
    /*   32 */ "vkGetImageSparseMemoryRequirements",
    /*   33 */ "vkGetPhysicalDeviceSparseImageFormatProperties",
    /*   34 */ "vkQueueBindSparse",
    /*   35 */ "vkCreateFence",
    /*   36 */ "vkDestroyFence",
    /*   37 */ "vkResetFences",
    /*   38 */ "vkGetFenceStatus",
    /*   39 */ "vkWaitForFences",
    /*   40 */ "vkCreateSemaphore",
    /*   41 */ "vkDestroySemaphore",
    /*   42 */ "vkCreateEvent",
    /*   43 */ "vkDestroyEvent",
    /*   44 */ "vkGetEventStatus",
    /*   45 */ "vkSetEvent",
    /*   46 */ "vkResetEvent",
    /*   47 */ "vkCreateQueryPool",
    /*   48 */ "vkDestroyQueryPool",
    /*   49 */ "vkGetQueryPoolResults",
    /*   50 */ "vkCreateBuffer",
    /*   51 */ "vkDestroyBuffer",
    /*   52 */ "vkCreateBufferView",
    /*   53 */ "vkDestroyBufferView",
    /*   54 */ "vkCreateImage",
    /*   55 */ "vkDestroyImage",
    /*   56 */ "vkGetImageSubresourceLayout",
    /*   57 */ "vkCreateImageView",
    /*   58 */ "vkDestroyImageView",
    /*   59 */ "vkCreateShaderModule",
    /*   60 */ "vkDestroyShaderModule",
    /*   61 */ "vkCreatePipelineCache",
    /*   62 */ "vkDestroyPipelineCache",
    /*   63 */ "vkGetPipelineCacheData",
    /*   64 */ "vkMergePipelineCaches",
    /*   65 */ "vkCreateGraphicsPipelines",
    /*   66 */ "vkCreateComputePipelines",
    /*   67 */ "vkDestroyPipeline",
    /*   68 */ "vkCreatePipelineLayout",
    /*   69 */ "vkDestroyPipelineLayout",
    /*   70 */ "vkCreateSampler",
    /*   71 */ "vkDestroySampler",
    /*   72 */ "vkCreateDescriptorSetLayout",
    /*   73 */ "vkDestroyDescriptorSetLayout",
    /*   74 */ "vkCreateDescriptorPool",
    /*   75 */ "vkDestroyDescriptorPool",
    /*   76 */ "vkResetDescriptorPool",
    /*   77 */ "vkAllocateDescriptorSets",
    /*   78 */ "vkFreeDescriptorSets",
    /*   79 */ "vkUpdateDescriptorSets",
    /*   80 */ "vkCreateFramebuffer",
    /*   81 */ "vkDestroyFramebuffer",
    /*   82 */ "vkCreateRenderPass",
    /*   83 */ "vkDestroyRenderPass",
    /*   84 */ "vkGetRenderAreaGranularity",
    /*   85 */ "vkCreateCommandPool",
    /*   86 */ "vkDestroyCommandPool",
    /*   87 */ "vkResetCommandPool",
    /*   88 */ "vkAllocateCommandBuffers",
    /*   89 */ "vkFreeCommandBuffers",
    /*   90 */ "vkBeginCommandBuffer",
    /*   91 */ "vkEndCommandBuffer",
    /*   92 */ "vkResetCommandBuffer",
    /*   93 */ "vkCmdBindPipeline",
    /*   94 */ "vkCmdSetViewport",
    /*   95 */ "vkCmdSetScissor",
    /*   96 */ "vkCmdSetLineWidth",
    /*   97 */ "vkCmdSetDepthBias",
    /*   98 */ "vkCmdSetBlendConstants",
    /*   99 */ "vkCmdSetDepthBounds",
    /*  100 */ "vkCmdSetStencilCompareMask",
    /*  101 */ "vkCmdSetStencilWriteMask",
    /*  102 */ "vkCmdSetStencilReference",
    /*  103 */ "vkCmdBindDescriptorSets",
    /*  104 */ "vkCmdBindIndexBuffer",
    /*  105 */ "vkCmdBindVertexBuffers",
    /*  106 */ "vkCmdDraw",
    /*  107 */ "vkCmdDrawIndexed",
    /*  108 */ "vkCmdDrawIndirect",
    /*  109 */ "vkCmdDrawIndexedIndirect",
    /*  110 */ "vkCmdDispatch",
    /*  111 */ "vkCmdDispatchIndirect",
    /*  112 */ "vkCmdCopyBuffer",
    /*  113 */ "vkCmdCopyImage",
    /*  114 */ "vkCmdBlitImage",
    /*  115 */ "vkCmdCopyBufferToImage",
    /*  116 */ "vkCmdCopyImageToBuffer",
    /*  117 */ "vkCmdUpdateBuffer",
    /*  118 */ "vkCmdFillBuffer",
    /*  119 */ "vkCmdClearColorImage",
    /*  120 */ "vkCmdClearDepthStencilImage",
    /*  121 */ "vkCmdClearAttachments",
    /*  122 */ "vkCmdResolveImage",
    /*  123 */ "vkCmdSetEvent",
    /*  124 */ "vkCmdResetEvent",
    /*  125 */ "vkCmdWaitEvents",
    /*  126 */ "vkCmdPipelineBarrier",
    /*  127 */ "vkCmdBeginQuery",
    /*  128 */ "vkCmdEndQuery",
    /*  129 */ "vkCmdResetQueryPool",
    /*  130 */ "vkCmdWriteTimestamp",
    /*  131 */ "vkCmdCopyQueryPoolResults",
    /*  132 */ "vkCmdPushConstants",
    /*  133 */ "vkCmdBeginRenderPass",
    /*  134 */ "vkCmdNextSubpass",
    /*  135 */ "vkCmdEndRenderPass",
    /*  136 */ "vkCmdExecuteCommands",
    /*  137 */ "vkEnumerateInstanceVersion",
    /*  138 */ "vkBindBufferMemory2",
    /*  139 */ "vkBindImageMemory2",
    /*  140 */ "vkGetDeviceGroupPeerMemoryFeatures",
    /*  141 */ "vkCmdSetDeviceMask",
    /*  142 */ "vkCmdDispatchBase",
    /*  143 */ "vkEnumeratePhysicalDeviceGroups",
    /*  144 */ "vkGetImageMemoryRequirements2",
    /*  145 */ "vkGetBufferMemoryRequirements2",
    /*  146 */ "vkGetImageSparseMemoryRequirements2",
    /*  147 */ "vkGetPhysicalDeviceFeatures2",
    /*  148 */ "vkGetPhysicalDeviceProperties2",
    /*  149 */ "vkGetPhysicalDeviceFormatProperties2",
    /*  150 */ "vkGetPhysicalDeviceImageFormatProperties2",
    /*  151 */ "vkGetPhysicalDeviceQueueFamilyProperties2",
    /*  152 */ "vkGetPhysicalDeviceMemoryProperties2",
    /*  153 */ "vkGetPhysicalDeviceSparseImageFormatProperties2",
    /*  154 */ "vkTrimCommandPool",
    /*  155 */ "vkGetDeviceQueue2",
    /*  156 */ "vkCreateSamplerYcbcrConversion",
    /*  157 */ "vkDestroySamplerYcbcrConversion",
    /*  158 */ "vkCreateDescriptorUpdateTemplate",
    /*  159 */ "vkDestroyDescriptorUpdateTemplate",
    /*  160 */ "vkUpdateDescriptorSetWithTemplate",
    /*  161 */ "vkGetPhysicalDeviceExternalBufferProperties",
    /*  162 */ "vkGetPhysicalDeviceExternalFenceProperties",
    /*  163 */ "vkGetPhysicalDeviceExternalSemaphoreProperties",
    /*  164 */ "vkGetDescriptorSetLayoutSupport",
    /*  165 */ "vkCmdDrawIndirectCount",
    /*  166 */ "vkCmdDrawIndexedIndirectCount",
    /*  167 */ "vkCreateRenderPass2",
    /*  168 */ "vkCmdBeginRenderPass2",
    /*  169 */ "vkCmdNextSubpass2",
    /*  170 */ "vkCmdEndRenderPass2",
    /*  171 */ "vkResetQueryPool",
    /*  172 */ "vkGetSemaphoreCounterValue",
    /*  173 */ "vkWaitSemaphores",
    /*  174 */ "vkSignalSemaphore",
    /*  175 */ "vkGetBufferDeviceAddress",
    /*  176 */ "vkGetBufferOpaqueCaptureAddress",
    /*  177 */ "vkGetDeviceMemoryOpaqueCaptureAddress",
    /*  178 */ "vkGetPhysicalDeviceToolProperties",
    /*  179 */ "vkCreatePrivateDataSlot",
    /*  180 */ "vkDestroyPrivateDataSlot",
    /*  181 */ "vkSetPrivateData",
    /*  182 */ "vkGetPrivateData",
    /*  183 */ "vkCmdSetEvent2",
    /*  184 */ "vkCmdResetEvent2",
    /*  185 */ "vkCmdWaitEvents2",
    /*  186 */ "vkCmdPipelineBarrier2",
    /*  187 */ "vkCmdWriteTimestamp2",
    /*  188 */ "vkQueueSubmit2",
    /*  189 */ "vkCmdCopyBuffer2",
    /*  190 */ "vkCmdCopyImage2",
    /*  191 */ "vkCmdCopyBufferToImage2",
    /*  192 */ "vkCmdCopyImageToBuffer2",
    /*  193 */ "vkCmdBlitImage2",
    /*  194 */ "vkCmdResolveImage2",
    /*  195 */ "vkCmdBeginRendering",
    /*  196 */ "vkCmdEndRendering",
    /*  197 */ "vkCmdSetCullMode",
    /*  198 */ "vkCmdSetFrontFace",
    /*  199 */ "vkCmdSetPrimitiveTopology",
    /*  200 */ "vkCmdSetViewportWithCount",
    /*  201 */ "vkCmdSetScissorWithCount",
    /*  202 */ "vkCmdBindVertexBuffers2",
    /*  203 */ "vkCmdSetDepthTestEnable",
    /*  204 */ "vkCmdSetDepthWriteEnable",
    /*  205 */ "vkCmdSetDepthCompareOp",
    /*  206 */ "vkCmdSetDepthBoundsTestEnable",
    /*  207 */ "vkCmdSetStencilTestEnable",
    /*  208 */ "vkCmdSetStencilOp",
    /*  209 */ "vkCmdSetRasterizerDiscardEnable",
    /*  210 */ "vkCmdSetDepthBiasEnable",
    /*  211 */ "vkCmdSetPrimitiveRestartEnable",
    /*  212 */ "vkGetDeviceBufferMemoryRequirements",
    /*  213 */ "vkGetDeviceImageMemoryRequirements",
    /*  214 */ "vkGetDeviceImageSparseMemoryRequirements",
    /*  215 */ "vkCmdSetLineStipple",
    /*  216 */ "vkMapMemory2",
    /*  217 */ "vkUnmapMemory2",
    /*  218 */ "vkCmdBindIndexBuffer2",
    /*  219 */ "vkGetRenderingAreaGranularity",
    /*  220 */ "vkGetDeviceImageSubresourceLayout",
    /*  221 */ "vkGetImageSubresourceLayout2",
    /*  222 */ "vkCmdPushDescriptorSet",
    /*  223 */ "vkCmdPushDescriptorSetWithTemplate",
    /*  224 */ "vkCmdSetRenderingAttachmentLocations",
    /*  225 */ "vkCmdSetRenderingInputAttachmentIndices",
    /*  226 */ "vkCmdBindDescriptorSets2",
    /*  227 */ "vkCmdPushConstants2",
    /*  228 */ "vkCmdPushDescriptorSet2",
    /*  229 */ "vkCmdPushDescriptorSetWithTemplate2",
    /*  230 */ "vkCopyMemoryToImage",
    /*  231 */ "vkCopyImageToMemory",
    /*  232 */ "vkCopyImageToImage",
    /*  233 */ "vkTransitionImageLayout",
    /*  234 */ "vkDestroySurfaceKHR",
    /*  235 */ "vkGetPhysicalDeviceSurfaceSupportKHR",
    /*  236 */ "vkGetPhysicalDeviceSurfaceCapabilitiesKHR",
    /*  237 */ "vkGetPhysicalDeviceSurfaceFormatsKHR",
    /*  238 */ "vkGetPhysicalDeviceSurfacePresentModesKHR",
    /*  239 */ "vkCreateSwapchainKHR",
    /*  240 */ "vkDestroySwapchainKHR",
    /*  241 */ "vkGetSwapchainImagesKHR",
    /*  242 */ "vkAcquireNextImageKHR",
    /*  243 */ "vkQueuePresentKHR",
    /*  244 */ "vkGetDeviceGroupPresentCapabilitiesKHR",
    /*  245 */ "vkGetDeviceGroupSurfacePresentModesKHR",
    /*  246 */ "vkGetPhysicalDevicePresentRectanglesKHR",
    /*  247 */ "vkAcquireNextImage2KHR",
    /*  248 */ "vkGetPhysicalDeviceDisplayPropertiesKHR",
    /*  249 */ "vkGetPhysicalDeviceDisplayPlanePropertiesKHR",
    /*  250 */ "vkGetDisplayPlaneSupportedDisplaysKHR",
    /*  251 */ "vkGetDisplayModePropertiesKHR",
    /*  252 */ "vkCreateDisplayModeKHR",
    /*  253 */ "vkGetDisplayPlaneCapabilitiesKHR",
    /*  254 */ "vkCreateDisplayPlaneSurfaceKHR",
    /*  255 */ "vkCreateSharedSwapchainsKHR",
    /*  256 */ "vkCreateXlibSurfaceKHR",
    /*  257 */ "vkGetPhysicalDeviceXlibPresentationSupportKHR",
    /*  258 */ "vkCreateXcbSurfaceKHR",
    /*  259 */ "vkGetPhysicalDeviceXcbPresentationSupportKHR",
    /*  260 */ "vkCreateWaylandSurfaceKHR",
    /*  261 */ "vkGetPhysicalDeviceWaylandPresentationSupportKHR",
    /*  262 */ "vkCreateAndroidSurfaceKHR",
    /*  263 */ "vkCreateWin32SurfaceKHR",
    /*  264 */ "vkGetPhysicalDeviceWin32PresentationSupportKHR",
    /*  265 */ "vkCreateDebugReportCallbackEXT",
    /*  266 */ "vkDestroyDebugReportCallbackEXT",
    /*  267 */ "vkDebugReportMessageEXT",
    /*  268 */ "vkDebugMarkerSetObjectTagEXT",
    /*  269 */ "vkDebugMarkerSetObjectNameEXT",
    /*  270 */ "vkCmdDebugMarkerBeginEXT",
    /*  271 */ "vkCmdDebugMarkerEndEXT",
    /*  272 */ "vkCmdDebugMarkerInsertEXT",
    /*  273 */ "vkGetPhysicalDeviceVideoCapabilitiesKHR",
    /*  274 */ "vkGetPhysicalDeviceVideoFormatPropertiesKHR",
    /*  275 */ "vkCreateVideoSessionKHR",
    /*  276 */ "vkDestroyVideoSessionKHR",
    /*  277 */ "vkGetVideoSessionMemoryRequirementsKHR",
    /*  278 */ "vkBindVideoSessionMemoryKHR",
    /*  279 */ "vkCreateVideoSessionParametersKHR",
    /*  280 */ "vkUpdateVideoSessionParametersKHR",
    /*  281 */ "vkDestroyVideoSessionParametersKHR",
    /*  282 */ "vkCmdBeginVideoCodingKHR",
    /*  283 */ "vkCmdEndVideoCodingKHR",
    /*  284 */ "vkCmdControlVideoCodingKHR",
    /*  285 */ "vkCmdDecodeVideoKHR",
    /*  286 */ "vkCmdBindTransformFeedbackBuffersEXT",
    /*  287 */ "vkCmdBeginTransformFeedbackEXT",
    /*  288 */ "vkCmdEndTransformFeedbackEXT",
    /*  289 */ "vkCmdBeginQueryIndexedEXT",
    /*  290 */ "vkCmdEndQueryIndexedEXT",
    /*  291 */ "vkCmdDrawIndirectByteCountEXT",
    /*  292 */ "vkCreateCuModuleNVX",
    /*  293 */ "vkCreateCuFunctionNVX",
    /*  294 */ "vkDestroyCuModuleNVX",
    /*  295 */ "vkDestroyCuFunctionNVX",
    /*  296 */ "vkCmdCuLaunchKernelNVX",
    /*  297 */ "vkGetImageViewHandleNVX",
    /*  298 */ "vkGetImageViewHandle64NVX",
    /*  299 */ "vkGetImageViewAddressNVX",
    /*  300 */ "vkCmdDrawIndirectCountAMD",
    /*  301 */ "vkCmdDrawIndexedIndirectCountAMD",
    /*  302 */ "vkGetShaderInfoAMD",
    /*  303 */ "vkCmdBeginRenderingKHR",
    /*  304 */ "vkCmdEndRenderingKHR",
    /*  305 */ "vkCreateStreamDescriptorSurfaceGGP",
    /*  306 */ "vkGetPhysicalDeviceExternalImageFormatPropertiesNV",
    /*  307 */ "vkGetMemoryWin32HandleNV",
    /*  308 */ "vkGetPhysicalDeviceFeatures2KHR",
    /*  309 */ "vkGetPhysicalDeviceProperties2KHR",
    /*  310 */ "vkGetPhysicalDeviceFormatProperties2KHR",
    /*  311 */ "vkGetPhysicalDeviceImageFormatProperties2KHR",
    /*  312 */ "vkGetPhysicalDeviceQueueFamilyProperties2KHR",
    /*  313 */ "vkGetPhysicalDeviceMemoryProperties2KHR",
    /*  314 */ "vkGetPhysicalDeviceSparseImageFormatProperties2KHR",
    /*  315 */ "vkGetDeviceGroupPeerMemoryFeaturesKHR",
    /*  316 */ "vkCmdSetDeviceMaskKHR",
    /*  317 */ "vkCmdDispatchBaseKHR",
    /*  318 */ "vkCreateViSurfaceNN",
    /*  319 */ "vkTrimCommandPoolKHR",
    /*  320 */ "vkEnumeratePhysicalDeviceGroupsKHR",
    /*  321 */ "vkGetPhysicalDeviceExternalBufferPropertiesKHR",
    /*  322 */ "vkGetMemoryWin32HandleKHR",
    /*  323 */ "vkGetMemoryWin32HandlePropertiesKHR",
    /*  324 */ "vkGetMemoryFdKHR",
    /*  325 */ "vkGetMemoryFdPropertiesKHR",
    /*  326 */ "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR",
    /*  327 */ "vkImportSemaphoreWin32HandleKHR",
    /*  328 */ "vkGetSemaphoreWin32HandleKHR",
    /*  329 */ "vkImportSemaphoreFdKHR",
    /*  330 */ "vkGetSemaphoreFdKHR",
    /*  331 */ "vkCmdPushDescriptorSetKHR",
    /*  332 */ "vkCmdPushDescriptorSetWithTemplateKHR",
    /*  333 */ "vkCmdBeginConditionalRenderingEXT",
    /*  334 */ "vkCmdEndConditionalRenderingEXT",
    /*  335 */ "vkCreateDescriptorUpdateTemplateKHR",
    /*  336 */ "vkDestroyDescriptorUpdateTemplateKHR",
    /*  337 */ "vkUpdateDescriptorSetWithTemplateKHR",
    /*  338 */ "vkCmdSetViewportWScalingNV",
    /*  339 */ "vkReleaseDisplayEXT",
    /*  340 */ "vkAcquireXlibDisplayEXT",
    /*  341 */ "vkGetRandROutputDisplayEXT",
    /*  342 */ "vkGetPhysicalDeviceSurfaceCapabilities2EXT",
    /*  343 */ "vkDisplayPowerControlEXT",
    /*  344 */ "vkRegisterDeviceEventEXT",
    /*  345 */ "vkRegisterDisplayEventEXT",
    /*  346 */ "vkGetSwapchainCounterEXT",
    /*  347 */ "vkGetRefreshCycleDurationGOOGLE",
    /*  348 */ "vkGetPastPresentationTimingGOOGLE",
    /*  349 */ "vkCmdSetDiscardRectangleEXT",
    /*  350 */ "vkCmdSetDiscardRectangleEnableEXT",
    /*  351 */ "vkCmdSetDiscardRectangleModeEXT",
    /*  352 */ "vkSetHdrMetadataEXT",
    /*  353 */ "vkCreateRenderPass2KHR",
    /*  354 */ "vkCmdBeginRenderPass2KHR",
    /*  355 */ "vkCmdNextSubpass2KHR",
    /*  356 */ "vkCmdEndRenderPass2KHR",
    /*  357 */ "vkGetSwapchainStatusKHR",
    /*  358 */ "vkGetPhysicalDeviceExternalFencePropertiesKHR",
    /*  359 */ "vkImportFenceWin32HandleKHR",
    /*  360 */ "vkGetFenceWin32HandleKHR",
    /*  361 */ "vkImportFenceFdKHR",
    /*  362 */ "vkGetFenceFdKHR",
    /*  363 */ "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR",
    /*  364 */ "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR",
    /*  365 */ "vkAcquireProfilingLockKHR",
    /*  366 */ "vkReleaseProfilingLockKHR",
    /*  367 */ "vkGetPhysicalDeviceSurfaceCapabilities2KHR",
    /*  368 */ "vkGetPhysicalDeviceSurfaceFormats2KHR",
    /*  369 */ "vkGetPhysicalDeviceDisplayProperties2KHR",
    /*  370 */ "vkGetPhysicalDeviceDisplayPlaneProperties2KHR",
    /*  371 */ "vkGetDisplayModeProperties2KHR",
    /*  372 */ "vkGetDisplayPlaneCapabilities2KHR",
    /*  373 */ "vkCreateIOSSurfaceMVK",
    /*  374 */ "vkCreateMacOSSurfaceMVK",
    /*  375 */ "vkSetDebugUtilsObjectNameEXT",
    /*  376 */ "vkSetDebugUtilsObjectTagEXT",
    /*  377 */ "vkQueueBeginDebugUtilsLabelEXT",
    /*  378 */ "vkQueueEndDebugUtilsLabelEXT",
    /*  379 */ "vkQueueInsertDebugUtilsLabelEXT",
    /*  380 */ "vkCmdBeginDebugUtilsLabelEXT",
    /*  381 */ "vkCmdEndDebugUtilsLabelEXT",
    /*  382 */ "vkCmdInsertDebugUtilsLabelEXT",
    /*  383 */ "vkCreateDebugUtilsMessengerEXT",
    /*  384 */ "vkDestroyDebugUtilsMessengerEXT",
    /*  385 */ "vkSubmitDebugUtilsMessageEXT",
    /*  386 */ "vkGetAndroidHardwareBufferPropertiesANDROID",
    /*  387 */ "vkGetMemoryAndroidHardwareBufferANDROID",
    /*  388 */ "vkCreateExecutionGraphPipelinesAMDX",
    /*  389 */ "vkGetExecutionGraphPipelineScratchSizeAMDX",
    /*  390 */ "vkGetExecutionGraphPipelineNodeIndexAMDX",
    /*  391 */ "vkCmdInitializeGraphScratchMemoryAMDX",
    /*  392 */ "vkCmdDispatchGraphAMDX",
    /*  393 */ "vkCmdDispatchGraphIndirectAMDX",
    /*  394 */ "vkCmdDispatchGraphIndirectCountAMDX",
    /*  395 */ "vkCmdSetSampleLocationsEXT",
    /*  396 */ "vkGetPhysicalDeviceMultisamplePropertiesEXT",
    /*  397 */ "vkGetImageMemoryRequirements2KHR",
    /*  398 */ "vkGetBufferMemoryRequirements2KHR",
    /*  399 */ "vkGetImageSparseMemoryRequirements2KHR",
    /*  400 */ "vkCreateAccelerationStructureKHR",
    /*  401 */ "vkDestroyAccelerationStructureKHR",
    /*  402 */ "vkCmdBuildAccelerationStructuresKHR",
    /*  403 */ "vkCmdBuildAccelerationStructuresIndirectKHR",
    /*  404 */ "vkBuildAccelerationStructuresKHR",
    /*  405 */ "vkCopyAccelerationStructureKHR",
    /*  406 */ "vkCopyAccelerationStructureToMemoryKHR",
    /*  407 */ "vkCopyMemoryToAccelerationStructureKHR",
    /*  408 */ "vkWriteAccelerationStructuresPropertiesKHR",
    /*  409 */ "vkCmdCopyAccelerationStructureKHR",
    /*  410 */ "vkCmdCopyAccelerationStructureToMemoryKHR",
    /*  411 */ "vkCmdCopyMemoryToAccelerationStructureKHR",
    /*  412 */ "vkGetAccelerationStructureDeviceAddressKHR",
    /*  413 */ "vkCmdWriteAccelerationStructuresPropertiesKHR",
    /*  414 */ "vkGetDeviceAccelerationStructureCompatibilityKHR",
    /*  415 */ "vkGetAccelerationStructureBuildSizesKHR",
    /*  416 */ "vkCmdTraceRaysKHR",
    /*  417 */ "vkCreateRayTracingPipelinesKHR",
    /*  418 */ "vkGetRayTracingShaderGroupHandlesKHR",
    /*  419 */ "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR",
    /*  420 */ "vkCmdTraceRaysIndirectKHR",
    /*  421 */ "vkGetRayTracingShaderGroupStackSizeKHR",
    /*  422 */ "vkCmdSetRayTracingPipelineStackSizeKHR",
    /*  423 */ "vkCreateSamplerYcbcrConversionKHR",
    /*  424 */ "vkDestroySamplerYcbcrConversionKHR",
    /*  425 */ "vkBindBufferMemory2KHR",
    /*  426 */ "vkBindImageMemory2KHR",
    /*  427 */ "vkGetImageDrmFormatModifierPropertiesEXT",
    /*  428 */ "vkCreateValidationCacheEXT",
    /*  429 */ "vkDestroyValidationCacheEXT",
    /*  430 */ "vkMergeValidationCachesEXT",
    /*  431 */ "vkGetValidationCacheDataEXT",
    /*  432 */ "vkCmdBindShadingRateImageNV",
    /*  433 */ "vkCmdSetViewportShadingRatePaletteNV",
    /*  434 */ "vkCmdSetCoarseSampleOrderNV",
    /*  435 */ "vkCreateAccelerationStructureNV",
    /*  436 */ "vkDestroyAccelerationStructureNV",
    /*  437 */ "vkGetAccelerationStructureMemoryRequirementsNV",
    /*  438 */ "vkBindAccelerationStructureMemoryNV",
    /*  439 */ "vkCmdBuildAccelerationStructureNV",
    /*  440 */ "vkCmdCopyAccelerationStructureNV",
    /*  441 */ "vkCmdTraceRaysNV",
    /*  442 */ "vkCreateRayTracingPipelinesNV",
    /*  443 */ "vkGetRayTracingShaderGroupHandlesNV",
    /*  444 */ "vkGetAccelerationStructureHandleNV",
    /*  445 */ "vkCmdWriteAccelerationStructuresPropertiesNV",
    /*  446 */ "vkCompileDeferredNV",
    /*  447 */ "vkGetDescriptorSetLayoutSupportKHR",
    /*  448 */ "vkCmdDrawIndirectCountKHR",
    /*  449 */ "vkCmdDrawIndexedIndirectCountKHR",
    /*  450 */ "vkGetMemoryHostPointerPropertiesEXT",
    /*  451 */ "vkCmdWriteBufferMarkerAMD",
    /*  452 */ "vkCmdWriteBufferMarker2AMD",
    /*  453 */ "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT",
    /*  454 */ "vkGetCalibratedTimestampsEXT",
    /*  455 */ "vkCmdDrawMeshTasksNV",
    /*  456 */ "vkCmdDrawMeshTasksIndirectNV",
    /*  457 */ "vkCmdDrawMeshTasksIndirectCountNV",
    /*  458 */ "vkCmdSetExclusiveScissorEnableNV",
    /*  459 */ "vkCmdSetExclusiveScissorNV",
    /*  460 */ "vkCmdSetCheckpointNV",
    /*  461 */ "vkGetQueueCheckpointDataNV",
    /*  462 */ "vkGetQueueCheckpointData2NV",
    /*  463 */ "vkGetSemaphoreCounterValueKHR",
    /*  464 */ "vkWaitSemaphoresKHR",
    /*  465 */ "vkSignalSemaphoreKHR",
    /*  466 */ "vkInitializePerformanceApiINTEL",
    /*  467 */ "vkUninitializePerformanceApiINTEL",
    /*  468 */ "vkCmdSetPerformanceMarkerINTEL",
    /*  469 */ "vkCmdSetPerformanceStreamMarkerINTEL",
    /*  470 */ "vkCmdSetPerformanceOverrideINTEL",
    /*  471 */ "vkAcquirePerformanceConfigurationINTEL",
    /*  472 */ "vkReleasePerformanceConfigurationINTEL",
    /*  473 */ "vkQueueSetPerformanceConfigurationINTEL",
    /*  474 */ "vkGetPerformanceParameterINTEL",
    /*  475 */ "vkSetLocalDimmingAMD",
    /*  476 */ "vkCreateImagePipeSurfaceFUCHSIA",
    /*  477 */ "vkCreateMetalSurfaceEXT",
    /*  478 */ "vkGetPhysicalDeviceFragmentShadingRatesKHR",
    /*  479 */ "vkCmdSetFragmentShadingRateKHR",
    /*  480 */ "vkCmdSetRenderingAttachmentLocationsKHR",
    /*  481 */ "vkCmdSetRenderingInputAttachmentIndicesKHR",
    /*  482 */ "vkGetBufferDeviceAddressEXT",
    /*  483 */ "vkGetPhysicalDeviceToolPropertiesEXT",
    /*  484 */ "vkWaitForPresentKHR",
    /*  485 */ "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV",
    /*  486 */ "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV",
    /*  487 */ "vkGetPhysicalDeviceSurfacePresentModes2EXT",
    /*  488 */ "vkAcquireFullScreenExclusiveModeEXT",
    /*  489 */ "vkReleaseFullScreenExclusiveModeEXT",
    /*  490 */ "vkGetDeviceGroupSurfacePresentModes2EXT",
    /*  491 */ "vkCreateHeadlessSurfaceEXT",
    /*  492 */ "vkGetBufferDeviceAddressKHR",
    /*  493 */ "vkGetBufferOpaqueCaptureAddressKHR",
    /*  494 */ "vkGetDeviceMemoryOpaqueCaptureAddressKHR",
    /*  495 */ "vkCmdSetLineStippleEXT",
    /*  496 */ "vkResetQueryPoolEXT",
    /*  497 */ "vkCmdSetCullModeEXT",
    /*  498 */ "vkCmdSetFrontFaceEXT",
    /*  499 */ "vkCmdSetPrimitiveTopologyEXT",
    /*  500 */ "vkCmdSetViewportWithCountEXT",
    /*  501 */ "vkCmdSetScissorWithCountEXT",
    /*  502 */ "vkCmdBindVertexBuffers2EXT",
    /*  503 */ "vkCmdSetDepthTestEnableEXT",
    /*  504 */ "vkCmdSetDepthWriteEnableEXT",
    /*  505 */ "vkCmdSetDepthCompareOpEXT",
    /*  506 */ "vkCmdSetDepthBoundsTestEnableEXT",
    /*  507 */ "vkCmdSetStencilTestEnableEXT",
    /*  508 */ "vkCmdSetStencilOpEXT",
    /*  509 */ "vkCreateDeferredOperationKHR",
    /*  510 */ "vkDestroyDeferredOperationKHR",
    /*  511 */ "vkGetDeferredOperationMaxConcurrencyKHR",
    /*  512 */ "vkGetDeferredOperationResultKHR",
    /*  513 */ "vkDeferredOperationJoinKHR",
    /*  514 */ "vkGetPipelineExecutablePropertiesKHR",
    /*  515 */ "vkGetPipelineExecutableStatisticsKHR",
    /*  516 */ "vkGetPipelineExecutableInternalRepresentationsKHR",
    /*  517 */ "vkCopyMemoryToImageEXT",
    /*  518 */ "vkCopyImageToMemoryEXT",
    /*  519 */ "vkCopyImageToImageEXT",
    /*  520 */ "vkTransitionImageLayoutEXT",
    /*  521 */ "vkGetImageSubresourceLayout2EXT",
    /*  522 */ "vkMapMemory2KHR",
    /*  523 */ "vkUnmapMemory2KHR",
    /*  524 */ "vkReleaseSwapchainImagesEXT",
    /*  525 */ "vkGetGeneratedCommandsMemoryRequirementsNV",
    /*  526 */ "vkCmdPreprocessGeneratedCommandsNV",
    /*  527 */ "vkCmdExecuteGeneratedCommandsNV",
    /*  528 */ "vkCmdBindPipelineShaderGroupNV",
    /*  529 */ "vkCreateIndirectCommandsLayoutNV",
    /*  530 */ "vkDestroyIndirectCommandsLayoutNV",
    /*  531 */ "vkCmdSetDepthBias2EXT",
    /*  532 */ "vkAcquireDrmDisplayEXT",
    /*  533 */ "vkGetDrmDisplayEXT",
    /*  534 */ "vkCreatePrivateDataSlotEXT",
    /*  535 */ "vkDestroyPrivateDataSlotEXT",
    /*  536 */ "vkSetPrivateDataEXT",
    /*  537 */ "vkGetPrivateDataEXT",
    /*  538 */ "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR",
    /*  539 */ "vkGetEncodedVideoSessionParametersKHR",
    /*  540 */ "vkCmdEncodeVideoKHR",
    /*  541 */ "vkCreateCudaModuleNV",
    /*  542 */ "vkGetCudaModuleCacheNV",
    /*  543 */ "vkCreateCudaFunctionNV",
    /*  544 */ "vkDestroyCudaModuleNV",
    /*  545 */ "vkDestroyCudaFunctionNV",
    /*  546 */ "vkCmdCudaLaunchKernelNV",
    /*  547 */ "vkCmdDispatchTileQCOM",
    /*  548 */ "vkCmdBeginPerTileExecutionQCOM",
    /*  549 */ "vkCmdEndPerTileExecutionQCOM",
    /*  550 */ "vkExportMetalObjectsEXT",
    /*  551 */ "vkCmdSetEvent2KHR",
    /*  552 */ "vkCmdResetEvent2KHR",
    /*  553 */ "vkCmdWaitEvents2KHR",
    /*  554 */ "vkCmdPipelineBarrier2KHR",
    /*  555 */ "vkCmdWriteTimestamp2KHR",
    /*  556 */ "vkQueueSubmit2KHR",
    /*  557 */ "vkGetDescriptorSetLayoutSizeEXT",
    /*  558 */ "vkGetDescriptorSetLayoutBindingOffsetEXT",
    /*  559 */ "vkGetDescriptorEXT",
    /*  560 */ "vkCmdBindDescriptorBuffersEXT",
    /*  561 */ "vkCmdSetDescriptorBufferOffsetsEXT",
    /*  562 */ "vkCmdBindDescriptorBufferEmbeddedSamplersEXT",
    /*  563 */ "vkGetBufferOpaqueCaptureDescriptorDataEXT",
    /*  564 */ "vkGetImageOpaqueCaptureDescriptorDataEXT",
    /*  565 */ "vkGetImageViewOpaqueCaptureDescriptorDataEXT",
    /*  566 */ "vkGetSamplerOpaqueCaptureDescriptorDataEXT",
    /*  567 */ "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT",
    /*  568 */ "vkCmdSetFragmentShadingRateEnumNV",
    /*  569 */ "vkCmdDrawMeshTasksEXT",
    /*  570 */ "vkCmdDrawMeshTasksIndirectEXT",
    /*  571 */ "vkCmdDrawMeshTasksIndirectCountEXT",
    /*  572 */ "vkCmdCopyBuffer2KHR",
    /*  573 */ "vkCmdCopyImage2KHR",
    /*  574 */ "vkCmdCopyBufferToImage2KHR",
    /*  575 */ "vkCmdCopyImageToBuffer2KHR",
    /*  576 */ "vkCmdBlitImage2KHR",
    /*  577 */ "vkCmdResolveImage2KHR",
    /*  578 */ "vkGetDeviceFaultInfoEXT",
    /*  579 */ "vkAcquireWinrtDisplayNV",
    /*  580 */ "vkGetWinrtDisplayNV",
    /*  581 */ "vkCreateDirectFBSurfaceEXT",
    /*  582 */ "vkGetPhysicalDeviceDirectFBPresentationSupportEXT",
    /*  583 */ "vkCmdSetVertexInputEXT",
    /*  584 */ "vkGetMemoryZirconHandleFUCHSIA",
    /*  585 */ "vkGetMemoryZirconHandlePropertiesFUCHSIA",
    /*  586 */ "vkImportSemaphoreZirconHandleFUCHSIA",
    /*  587 */ "vkGetSemaphoreZirconHandleFUCHSIA",
    /*  588 */ "vkCreateBufferCollectionFUCHSIA",
    /*  589 */ "vkSetBufferCollectionImageConstraintsFUCHSIA",
    /*  590 */ "vkSetBufferCollectionBufferConstraintsFUCHSIA",
    /*  591 */ "vkDestroyBufferCollectionFUCHSIA",
    /*  592 */ "vkGetBufferCollectionPropertiesFUCHSIA",
    /*  593 */ "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI",
    /*  594 */ "vkCmdSubpassShadingHUAWEI",
    /*  595 */ "vkCmdBindInvocationMaskHUAWEI",
    /*  596 */ "vkGetMemoryRemoteAddressNV",
    /*  597 */ "vkGetPipelinePropertiesEXT",
    /*  598 */ "vkCmdSetPatchControlPointsEXT",
    /*  599 */ "vkCmdSetRasterizerDiscardEnableEXT",
    /*  600 */ "vkCmdSetDepthBiasEnableEXT",
    /*  601 */ "vkCmdSetLogicOpEXT",
    /*  602 */ "vkCmdSetPrimitiveRestartEnableEXT",
    /*  603 */ "vkCreateScreenSurfaceQNX",
    /*  604 */ "vkGetPhysicalDeviceScreenPresentationSupportQNX",
    /*  605 */ "vkCmdSetColorWriteEnableEXT",
    /*  606 */ "vkCmdTraceRaysIndirect2KHR",
    /*  607 */ "vkCmdDrawMultiEXT",
    /*  608 */ "vkCmdDrawMultiIndexedEXT",
    /*  609 */ "vkCreateMicromapEXT",
    /*  610 */ "vkDestroyMicromapEXT",
    /*  611 */ "vkCmdBuildMicromapsEXT",
    /*  612 */ "vkBuildMicromapsEXT",
    /*  613 */ "vkCopyMicromapEXT",
    /*  614 */ "vkCopyMicromapToMemoryEXT",
    /*  615 */ "vkCopyMemoryToMicromapEXT",
    /*  616 */ "vkWriteMicromapsPropertiesEXT",
    /*  617 */ "vkCmdCopyMicromapEXT",
    /*  618 */ "vkCmdCopyMicromapToMemoryEXT",
    /*  619 */ "vkCmdCopyMemoryToMicromapEXT",
    /*  620 */ "vkCmdWriteMicromapsPropertiesEXT",
    /*  621 */ "vkGetDeviceMicromapCompatibilityEXT",
    /*  622 */ "vkGetMicromapBuildSizesEXT",
    /*  623 */ "vkCmdDrawClusterHUAWEI",
    /*  624 */ "vkCmdDrawClusterIndirectHUAWEI",
    /*  625 */ "vkSetDeviceMemoryPriorityEXT",
    /*  626 */ "vkGetDeviceBufferMemoryRequirementsKHR",
    /*  627 */ "vkGetDeviceImageMemoryRequirementsKHR",
    /*  628 */ "vkGetDeviceImageSparseMemoryRequirementsKHR",
    /*  629 */ "vkGetDescriptorSetLayoutHostMappingInfoVALVE",
    /*  630 */ "vkGetDescriptorSetHostMappingVALVE",
    /*  631 */ "vkCmdCopyMemoryIndirectNV",
    /*  632 */ "vkCmdCopyMemoryToImageIndirectNV",
    /*  633 */ "vkCmdDecompressMemoryNV",
    /*  634 */ "vkCmdDecompressMemoryIndirectCountNV",
    /*  635 */ "vkGetPipelineIndirectMemoryRequirementsNV",
    /*  636 */ "vkCmdUpdatePipelineIndirectBufferNV",
    /*  637 */ "vkGetPipelineIndirectDeviceAddressNV",
    /*  638 */ "vkCmdSetDepthClampEnableEXT",
    /*  639 */ "vkCmdSetPolygonModeEXT",
    /*  640 */ "vkCmdSetRasterizationSamplesEXT",
    /*  641 */ "vkCmdSetSampleMaskEXT",
    /*  642 */ "vkCmdSetAlphaToCoverageEnableEXT",
    /*  643 */ "vkCmdSetAlphaToOneEnableEXT",
    /*  644 */ "vkCmdSetLogicOpEnableEXT",
    /*  645 */ "vkCmdSetColorBlendEnableEXT",
    /*  646 */ "vkCmdSetColorBlendEquationEXT",
    /*  647 */ "vkCmdSetColorWriteMaskEXT",
    /*  648 */ "vkCmdSetTessellationDomainOriginEXT",
    /*  649 */ "vkCmdSetRasterizationStreamEXT",
    /*  650 */ "vkCmdSetConservativeRasterizationModeEXT",
    /*  651 */ "vkCmdSetExtraPrimitiveOverestimationSizeEXT",
    /*  652 */ "vkCmdSetDepthClipEnableEXT",
    /*  653 */ "vkCmdSetSampleLocationsEnableEXT",
    /*  654 */ "vkCmdSetColorBlendAdvancedEXT",
    /*  655 */ "vkCmdSetProvokingVertexModeEXT",
    /*  656 */ "vkCmdSetLineRasterizationModeEXT",
    /*  657 */ "vkCmdSetLineStippleEnableEXT",
    /*  658 */ "vkCmdSetDepthClipNegativeOneToOneEXT",
    /*  659 */ "vkCmdSetViewportWScalingEnableNV",
    /*  660 */ "vkCmdSetViewportSwizzleNV",
    /*  661 */ "vkCmdSetCoverageToColorEnableNV",
    /*  662 */ "vkCmdSetCoverageToColorLocationNV",
    /*  663 */ "vkCmdSetCoverageModulationModeNV",
    /*  664 */ "vkCmdSetCoverageModulationTableEnableNV",
    /*  665 */ "vkCmdSetCoverageModulationTableNV",
    /*  666 */ "vkCmdSetShadingRateImageEnableNV",
    /*  667 */ "vkCmdSetRepresentativeFragmentTestEnableNV",
    /*  668 */ "vkCmdSetCoverageReductionModeNV",
    /*  669 */ "vkCreateTensorARM",
    /*  670 */ "vkDestroyTensorARM",
    /*  671 */ "vkCreateTensorViewARM",
    /*  672 */ "vkDestroyTensorViewARM",
    /*  673 */ "vkGetTensorMemoryRequirementsARM",
    /*  674 */ "vkBindTensorMemoryARM",
    /*  675 */ "vkGetDeviceTensorMemoryRequirementsARM",
    /*  676 */ "vkCmdCopyTensorARM",
    /*  677 */ "vkGetPhysicalDeviceExternalTensorPropertiesARM",
    /*  678 */ "vkGetTensorOpaqueCaptureDescriptorDataARM",
    /*  679 */ "vkGetTensorViewOpaqueCaptureDescriptorDataARM",
    /*  680 */ "vkGetShaderModuleIdentifierEXT",
    /*  681 */ "vkGetShaderModuleCreateInfoIdentifierEXT",
    /*  682 */ "vkGetPhysicalDeviceOpticalFlowImageFormatsNV",
    /*  683 */ "vkCreateOpticalFlowSessionNV",
    /*  684 */ "vkDestroyOpticalFlowSessionNV",
    /*  685 */ "vkBindOpticalFlowSessionImageNV",
    /*  686 */ "vkCmdOpticalFlowExecuteNV",
    /*  687 */ "vkCmdBindIndexBuffer2KHR",
    /*  688 */ "vkGetRenderingAreaGranularityKHR",
    /*  689 */ "vkGetDeviceImageSubresourceLayoutKHR",
    /*  690 */ "vkGetImageSubresourceLayout2KHR",
    /*  691 */ "vkAntiLagUpdateAMD",
    /*  692 */ "vkWaitForPresent2KHR",
    /*  693 */ "vkCreateShadersEXT",
    /*  694 */ "vkDestroyShaderEXT",
    /*  695 */ "vkGetShaderBinaryDataEXT",
    /*  696 */ "vkCmdBindShadersEXT",
    /*  697 */ "vkCmdSetDepthClampRangeEXT",
    /*  698 */ "vkCreatePipelineBinariesKHR",
    /*  699 */ "vkDestroyPipelineBinaryKHR",
    /*  700 */ "vkGetPipelineKeyKHR",
    /*  701 */ "vkGetPipelineBinaryDataKHR",
    /*  702 */ "vkReleaseCapturedPipelineDataKHR",
    /*  703 */ "vkGetFramebufferTilePropertiesQCOM",
    /*  704 */ "vkGetDynamicRenderingTilePropertiesQCOM",
    /*  705 */ "vkReleaseSwapchainImagesKHR",
    /*  706 */ "vkGetPhysicalDeviceCooperativeVectorPropertiesNV",
    /*  707 */ "vkConvertCooperativeVectorMatrixNV",
    /*  708 */ "vkCmdConvertCooperativeVectorMatrixNV",
    /*  709 */ "vkSetLatencySleepModeNV",
    /*  710 */ "vkLatencySleepNV",
    /*  711 */ "vkSetLatencyMarkerNV",
    /*  712 */ "vkGetLatencyTimingsNV",
    /*  713 */ "vkQueueNotifyOutOfBandNV",
    /*  714 */ "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR",
    /*  715 */ "vkCreateDataGraphPipelinesARM",
    /*  716 */ "vkCreateDataGraphPipelineSessionARM",
    /*  717 */ "vkGetDataGraphPipelineSessionBindPointRequirementsARM",
    /*  718 */ "vkGetDataGraphPipelineSessionMemoryRequirementsARM",
    /*  719 */ "vkBindDataGraphPipelineSessionMemoryARM",
    /*  720 */ "vkDestroyDataGraphPipelineSessionARM",
    /*  721 */ "vkCmdDispatchDataGraphARM",
    /*  722 */ "vkGetDataGraphPipelineAvailablePropertiesARM",
    /*  723 */ "vkGetDataGraphPipelinePropertiesARM",
    /*  724 */ "vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM",
    /*  725 */ "vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM",
    /*  726 */ "vkCmdSetAttachmentFeedbackLoopEnableEXT",
    /*  727 */ "vkGetScreenBufferPropertiesQNX",
    /*  728 */ "vkCmdSetLineStippleKHR",
    /*  729 */ "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR",
    /*  730 */ "vkGetCalibratedTimestampsKHR",
    /*  731 */ "vkCmdBindDescriptorSets2KHR",
    /*  732 */ "vkCmdPushConstants2KHR",
    /*  733 */ "vkCmdPushDescriptorSet2KHR",
    /*  734 */ "vkCmdPushDescriptorSetWithTemplate2KHR",
    /*  735 */ "vkCmdSetDescriptorBufferOffsets2EXT",
    /*  736 */ "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT",
    /*  737 */ "vkCmdBindTileMemoryQCOM",
    /*  738 */ "vkCreateExternalComputeQueueNV",
    /*  739 */ "vkDestroyExternalComputeQueueNV",
    /*  740 */ "vkGetExternalComputeQueueDataNV",
    /*  741 */ "vkGetClusterAccelerationStructureBuildSizesNV",
    /*  742 */ "vkCmdBuildClusterAccelerationStructureIndirectNV",
    /*  743 */ "vkGetPartitionedAccelerationStructuresBuildSizesNV",
    /*  744 */ "vkCmdBuildPartitionedAccelerationStructuresNV",
    /*  745 */ "vkGetGeneratedCommandsMemoryRequirementsEXT",
    /*  746 */ "vkCmdPreprocessGeneratedCommandsEXT",
    /*  747 */ "vkCmdExecuteGeneratedCommandsEXT",
    /*  748 */ "vkCreateIndirectCommandsLayoutEXT",
    /*  749 */ "vkDestroyIndirectCommandsLayoutEXT",
    /*  750 */ "vkCreateIndirectExecutionSetEXT",
    /*  751 */ "vkDestroyIndirectExecutionSetEXT",
    /*  752 */ "vkUpdateIndirectExecutionSetPipelineEXT",
    /*  753 */ "vkUpdateIndirectExecutionSetShaderEXT",
    /*  754 */ "vkCreateSurfaceOHOS",
    /*  755 */ "vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV",
    /*  756 */ "vkGetMemoryMetalHandleEXT",
    /*  757 */ "vkGetMemoryMetalHandlePropertiesEXT",
    /*  758 */ "vkCmdEndRendering2EXT"
};

static const uint8_t GLAD_Vulkan_fn_scopes[] = {
    /*    0 */ CommandScopeGlobal  , /* vkCreateInstance */
    /*    1 */ CommandScopeInstance, /* vkDestroyInstance */
    /*    2 */ CommandScopeInstance, /* vkEnumeratePhysicalDevices */
    /*    3 */ CommandScopeInstance, /* vkGetPhysicalDeviceFeatures */
    /*    4 */ CommandScopeInstance, /* vkGetPhysicalDeviceFormatProperties */
    /*    5 */ CommandScopeInstance, /* vkGetPhysicalDeviceImageFormatProperties */
    /*    6 */ CommandScopeInstance, /* vkGetPhysicalDeviceProperties */
    /*    7 */ CommandScopeInstance, /* vkGetPhysicalDeviceQueueFamilyProperties */
    /*    8 */ CommandScopeInstance, /* vkGetPhysicalDeviceMemoryProperties */
    /*    9 */ CommandScopeUnknown , /* vkGetInstanceProcAddr */
    /*   10 */ CommandScopeDevice  , /* vkGetDeviceProcAddr */
    /*   11 */ CommandScopeInstance, /* vkCreateDevice */
    /*   12 */ CommandScopeDevice  , /* vkDestroyDevice */
    /*   13 */ CommandScopeGlobal  , /* vkEnumerateInstanceExtensionProperties */
    /*   14 */ CommandScopeInstance, /* vkEnumerateDeviceExtensionProperties */
    /*   15 */ CommandScopeGlobal  , /* vkEnumerateInstanceLayerProperties */
    /*   16 */ CommandScopeInstance, /* vkEnumerateDeviceLayerProperties */
    /*   17 */ CommandScopeDevice  , /* vkGetDeviceQueue */
    /*   18 */ CommandScopeDevice  , /* vkQueueSubmit */
    /*   19 */ CommandScopeDevice  , /* vkQueueWaitIdle */
    /*   20 */ CommandScopeDevice  , /* vkDeviceWaitIdle */
    /*   21 */ CommandScopeDevice  , /* vkAllocateMemory */
    /*   22 */ CommandScopeDevice  , /* vkFreeMemory */
    /*   23 */ CommandScopeDevice  , /* vkMapMemory */
    /*   24 */ CommandScopeDevice  , /* vkUnmapMemory */
    /*   25 */ CommandScopeDevice  , /* vkFlushMappedMemoryRanges */
    /*   26 */ CommandScopeDevice  , /* vkInvalidateMappedMemoryRanges */
    /*   27 */ CommandScopeDevice  , /* vkGetDeviceMemoryCommitment */
    /*   28 */ CommandScopeDevice  , /* vkBindBufferMemory */
    /*   29 */ CommandScopeDevice  , /* vkBindImageMemory */
    /*   30 */ CommandScopeDevice  , /* vkGetBufferMemoryRequirements */
    /*   31 */ CommandScopeDevice  , /* vkGetImageMemoryRequirements */
    /*   32 */ CommandScopeDevice  , /* vkGetImageSparseMemoryRequirements */
    /*   33 */ CommandScopeInstance, /* vkGetPhysicalDeviceSparseImageFormatProperties */
    /*   34 */ CommandScopeDevice  , /* vkQueueBindSparse */
    /*   35 */ CommandScopeDevice  , /* vkCreateFence */
    /*   36 */ CommandScopeDevice  , /* vkDestroyFence */
    /*   37 */ CommandScopeDevice  , /* vkResetFences */
    /*   38 */ CommandScopeDevice  , /* vkGetFenceStatus */
    /*   39 */ CommandScopeDevice  , /* vkWaitForFences */
    /*   40 */ CommandScopeDevice  , /* vkCreateSemaphore */
    /*   41 */ CommandScopeDevice  , /* vkDestroySemaphore */
    /*   42 */ CommandScopeDevice  , /* vkCreateEvent */
    /*   43 */ CommandScopeDevice  , /* vkDestroyEvent */
    /*   44 */ CommandScopeDevice  , /* vkGetEventStatus */
    /*   45 */ CommandScopeDevice  , /* vkSetEvent */
    /*   46 */ CommandScopeDevice  , /* vkResetEvent */
    /*   47 */ CommandScopeDevice  , /* vkCreateQueryPool */
    /*   48 */ CommandScopeDevice  , /* vkDestroyQueryPool */
    /*   49 */ CommandScopeDevice  , /* vkGetQueryPoolResults */
    /*   50 */ CommandScopeDevice  , /* vkCreateBuffer */
    /*   51 */ CommandScopeDevice  , /* vkDestroyBuffer */
    /*   52 */ CommandScopeDevice  , /* vkCreateBufferView */
    /*   53 */ CommandScopeDevice  , /* vkDestroyBufferView */
    /*   54 */ CommandScopeDevice  , /* vkCreateImage */
    /*   55 */ CommandScopeDevice  , /* vkDestroyImage */
    /*   56 */ CommandScopeDevice  , /* vkGetImageSubresourceLayout */
    /*   57 */ CommandScopeDevice  , /* vkCreateImageView */
    /*   58 */ CommandScopeDevice  , /* vkDestroyImageView */
    /*   59 */ CommandScopeDevice  , /* vkCreateShaderModule */
    /*   60 */ CommandScopeDevice  , /* vkDestroyShaderModule */
    /*   61 */ CommandScopeDevice  , /* vkCreatePipelineCache */
    /*   62 */ CommandScopeDevice  , /* vkDestroyPipelineCache */
    /*   63 */ CommandScopeDevice  , /* vkGetPipelineCacheData */
    /*   64 */ CommandScopeDevice  , /* vkMergePipelineCaches */
    /*   65 */ CommandScopeDevice  , /* vkCreateGraphicsPipelines */
    /*   66 */ CommandScopeDevice  , /* vkCreateComputePipelines */
    /*   67 */ CommandScopeDevice  , /* vkDestroyPipeline */
    /*   68 */ CommandScopeDevice  , /* vkCreatePipelineLayout */
    /*   69 */ CommandScopeDevice  , /* vkDestroyPipelineLayout */
    /*   70 */ CommandScopeDevice  , /* vkCreateSampler */
    /*   71 */ CommandScopeDevice  , /* vkDestroySampler */
    /*   72 */ CommandScopeDevice  , /* vkCreateDescriptorSetLayout */
    /*   73 */ CommandScopeDevice  , /* vkDestroyDescriptorSetLayout */
    /*   74 */ CommandScopeDevice  , /* vkCreateDescriptorPool */
    /*   75 */ CommandScopeDevice  , /* vkDestroyDescriptorPool */
    /*   76 */ CommandScopeDevice  , /* vkResetDescriptorPool */
    /*   77 */ CommandScopeDevice  , /* vkAllocateDescriptorSets */
    /*   78 */ CommandScopeDevice  , /* vkFreeDescriptorSets */
    /*   79 */ CommandScopeDevice  , /* vkUpdateDescriptorSets */
    /*   80 */ CommandScopeDevice  , /* vkCreateFramebuffer */
    /*   81 */ CommandScopeDevice  , /* vkDestroyFramebuffer */
    /*   82 */ CommandScopeDevice  , /* vkCreateRenderPass */
    /*   83 */ CommandScopeDevice  , /* vkDestroyRenderPass */
    /*   84 */ CommandScopeDevice  , /* vkGetRenderAreaGranularity */
    /*   85 */ CommandScopeDevice  , /* vkCreateCommandPool */
    /*   86 */ CommandScopeDevice  , /* vkDestroyCommandPool */
    /*   87 */ CommandScopeDevice  , /* vkResetCommandPool */
    /*   88 */ CommandScopeDevice  , /* vkAllocateCommandBuffers */
    /*   89 */ CommandScopeDevice  , /* vkFreeCommandBuffers */
    /*   90 */ CommandScopeDevice  , /* vkBeginCommandBuffer */
    /*   91 */ CommandScopeDevice  , /* vkEndCommandBuffer */
    /*   92 */ CommandScopeDevice  , /* vkResetCommandBuffer */
    /*   93 */ CommandScopeDevice  , /* vkCmdBindPipeline */
    /*   94 */ CommandScopeDevice  , /* vkCmdSetViewport */
    /*   95 */ CommandScopeDevice  , /* vkCmdSetScissor */
    /*   96 */ CommandScopeDevice  , /* vkCmdSetLineWidth */
    /*   97 */ CommandScopeDevice  , /* vkCmdSetDepthBias */
    /*   98 */ CommandScopeDevice  , /* vkCmdSetBlendConstants */
    /*   99 */ CommandScopeDevice  , /* vkCmdSetDepthBounds */
    /*  100 */ CommandScopeDevice  , /* vkCmdSetStencilCompareMask */
    /*  101 */ CommandScopeDevice  , /* vkCmdSetStencilWriteMask */
    /*  102 */ CommandScopeDevice  , /* vkCmdSetStencilReference */
    /*  103 */ CommandScopeDevice  , /* vkCmdBindDescriptorSets */
    /*  104 */ CommandScopeDevice  , /* vkCmdBindIndexBuffer */
    /*  105 */ CommandScopeDevice  , /* vkCmdBindVertexBuffers */
    /*  106 */ CommandScopeDevice  , /* vkCmdDraw */
    /*  107 */ CommandScopeDevice  , /* vkCmdDrawIndexed */
    /*  108 */ CommandScopeDevice  , /* vkCmdDrawIndirect */
    /*  109 */ CommandScopeDevice  , /* vkCmdDrawIndexedIndirect */
    /*  110 */ CommandScopeDevice  , /* vkCmdDispatch */
    /*  111 */ CommandScopeDevice  , /* vkCmdDispatchIndirect */
    /*  112 */ CommandScopeDevice  , /* vkCmdCopyBuffer */
    /*  113 */ CommandScopeDevice  , /* vkCmdCopyImage */
    /*  114 */ CommandScopeDevice  , /* vkCmdBlitImage */
    /*  115 */ CommandScopeDevice  , /* vkCmdCopyBufferToImage */
    /*  116 */ CommandScopeDevice  , /* vkCmdCopyImageToBuffer */
    /*  117 */ CommandScopeDevice  , /* vkCmdUpdateBuffer */
    /*  118 */ CommandScopeDevice  , /* vkCmdFillBuffer */
    /*  119 */ CommandScopeDevice  , /* vkCmdClearColorImage */
    /*  120 */ CommandScopeDevice  , /* vkCmdClearDepthStencilImage */
    /*  121 */ CommandScopeDevice  , /* vkCmdClearAttachments */
    /*  122 */ CommandScopeDevice  , /* vkCmdResolveImage */
    /*  123 */ CommandScopeDevice  , /* vkCmdSetEvent */
    /*  124 */ CommandScopeDevice  , /* vkCmdResetEvent */
    /*  125 */ CommandScopeDevice  , /* vkCmdWaitEvents */
    /*  126 */ CommandScopeDevice  , /* vkCmdPipelineBarrier */
    /*  127 */ CommandScopeDevice  , /* vkCmdBeginQuery */
    /*  128 */ CommandScopeDevice  , /* vkCmdEndQuery */
    /*  129 */ CommandScopeDevice  , /* vkCmdResetQueryPool */
    /*  130 */ CommandScopeDevice  , /* vkCmdWriteTimestamp */
    /*  131 */ CommandScopeDevice  , /* vkCmdCopyQueryPoolResults */
    /*  132 */ CommandScopeDevice  , /* vkCmdPushConstants */
    /*  133 */ CommandScopeDevice  , /* vkCmdBeginRenderPass */
    /*  134 */ CommandScopeDevice  , /* vkCmdNextSubpass */
    /*  135 */ CommandScopeDevice  , /* vkCmdEndRenderPass */
    /*  136 */ CommandScopeDevice  , /* vkCmdExecuteCommands */
    /*  137 */ CommandScopeGlobal  , /* vkEnumerateInstanceVersion */
    /*  138 */ CommandScopeDevice  , /* vkBindBufferMemory2 */
    /*  139 */ CommandScopeDevice  , /* vkBindImageMemory2 */
    /*  140 */ CommandScopeDevice  , /* vkGetDeviceGroupPeerMemoryFeatures */
    /*  141 */ CommandScopeDevice  , /* vkCmdSetDeviceMask */
    /*  142 */ CommandScopeDevice  , /* vkCmdDispatchBase */
    /*  143 */ CommandScopeInstance, /* vkEnumeratePhysicalDeviceGroups */
    /*  144 */ CommandScopeDevice  , /* vkGetImageMemoryRequirements2 */
    /*  145 */ CommandScopeDevice  , /* vkGetBufferMemoryRequirements2 */
    /*  146 */ CommandScopeDevice  , /* vkGetImageSparseMemoryRequirements2 */
    /*  147 */ CommandScopeInstance, /* vkGetPhysicalDeviceFeatures2 */
    /*  148 */ CommandScopeInstance, /* vkGetPhysicalDeviceProperties2 */
    /*  149 */ CommandScopeInstance, /* vkGetPhysicalDeviceFormatProperties2 */
    /*  150 */ CommandScopeInstance, /* vkGetPhysicalDeviceImageFormatProperties2 */
    /*  151 */ CommandScopeInstance, /* vkGetPhysicalDeviceQueueFamilyProperties2 */
    /*  152 */ CommandScopeInstance, /* vkGetPhysicalDeviceMemoryProperties2 */
    /*  153 */ CommandScopeInstance, /* vkGetPhysicalDeviceSparseImageFormatProperties2 */
    /*  154 */ CommandScopeDevice  , /* vkTrimCommandPool */
    /*  155 */ CommandScopeDevice  , /* vkGetDeviceQueue2 */
    /*  156 */ CommandScopeDevice  , /* vkCreateSamplerYcbcrConversion */
    /*  157 */ CommandScopeDevice  , /* vkDestroySamplerYcbcrConversion */
    /*  158 */ CommandScopeDevice  , /* vkCreateDescriptorUpdateTemplate */
    /*  159 */ CommandScopeDevice  , /* vkDestroyDescriptorUpdateTemplate */
    /*  160 */ CommandScopeDevice  , /* vkUpdateDescriptorSetWithTemplate */
    /*  161 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalBufferProperties */
    /*  162 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalFenceProperties */
    /*  163 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalSemaphoreProperties */
    /*  164 */ CommandScopeDevice  , /* vkGetDescriptorSetLayoutSupport */
    /*  165 */ CommandScopeDevice  , /* vkCmdDrawIndirectCount */
    /*  166 */ CommandScopeDevice  , /* vkCmdDrawIndexedIndirectCount */
    /*  167 */ CommandScopeDevice  , /* vkCreateRenderPass2 */
    /*  168 */ CommandScopeDevice  , /* vkCmdBeginRenderPass2 */
    /*  169 */ CommandScopeDevice  , /* vkCmdNextSubpass2 */
    /*  170 */ CommandScopeDevice  , /* vkCmdEndRenderPass2 */
    /*  171 */ CommandScopeDevice  , /* vkResetQueryPool */
    /*  172 */ CommandScopeDevice  , /* vkGetSemaphoreCounterValue */
    /*  173 */ CommandScopeDevice  , /* vkWaitSemaphores */
    /*  174 */ CommandScopeDevice  , /* vkSignalSemaphore */
    /*  175 */ CommandScopeDevice  , /* vkGetBufferDeviceAddress */
    /*  176 */ CommandScopeDevice  , /* vkGetBufferOpaqueCaptureAddress */
    /*  177 */ CommandScopeDevice  , /* vkGetDeviceMemoryOpaqueCaptureAddress */
    /*  178 */ CommandScopeInstance, /* vkGetPhysicalDeviceToolProperties */
    /*  179 */ CommandScopeDevice  , /* vkCreatePrivateDataSlot */
    /*  180 */ CommandScopeDevice  , /* vkDestroyPrivateDataSlot */
    /*  181 */ CommandScopeDevice  , /* vkSetPrivateData */
    /*  182 */ CommandScopeDevice  , /* vkGetPrivateData */
    /*  183 */ CommandScopeDevice  , /* vkCmdSetEvent2 */
    /*  184 */ CommandScopeDevice  , /* vkCmdResetEvent2 */
    /*  185 */ CommandScopeDevice  , /* vkCmdWaitEvents2 */
    /*  186 */ CommandScopeDevice  , /* vkCmdPipelineBarrier2 */
    /*  187 */ CommandScopeDevice  , /* vkCmdWriteTimestamp2 */
    /*  188 */ CommandScopeDevice  , /* vkQueueSubmit2 */
    /*  189 */ CommandScopeDevice  , /* vkCmdCopyBuffer2 */
    /*  190 */ CommandScopeDevice  , /* vkCmdCopyImage2 */
    /*  191 */ CommandScopeDevice  , /* vkCmdCopyBufferToImage2 */
    /*  192 */ CommandScopeDevice  , /* vkCmdCopyImageToBuffer2 */
    /*  193 */ CommandScopeDevice  , /* vkCmdBlitImage2 */
    /*  194 */ CommandScopeDevice  , /* vkCmdResolveImage2 */
    /*  195 */ CommandScopeDevice  , /* vkCmdBeginRendering */
    /*  196 */ CommandScopeDevice  , /* vkCmdEndRendering */
    /*  197 */ CommandScopeDevice  , /* vkCmdSetCullMode */
    /*  198 */ CommandScopeDevice  , /* vkCmdSetFrontFace */
    /*  199 */ CommandScopeDevice  , /* vkCmdSetPrimitiveTopology */
    /*  200 */ CommandScopeDevice  , /* vkCmdSetViewportWithCount */
    /*  201 */ CommandScopeDevice  , /* vkCmdSetScissorWithCount */
    /*  202 */ CommandScopeDevice  , /* vkCmdBindVertexBuffers2 */
    /*  203 */ CommandScopeDevice  , /* vkCmdSetDepthTestEnable */
    /*  204 */ CommandScopeDevice  , /* vkCmdSetDepthWriteEnable */
    /*  205 */ CommandScopeDevice  , /* vkCmdSetDepthCompareOp */
    /*  206 */ CommandScopeDevice  , /* vkCmdSetDepthBoundsTestEnable */
    /*  207 */ CommandScopeDevice  , /* vkCmdSetStencilTestEnable */
    /*  208 */ CommandScopeDevice  , /* vkCmdSetStencilOp */
    /*  209 */ CommandScopeDevice  , /* vkCmdSetRasterizerDiscardEnable */
    /*  210 */ CommandScopeDevice  , /* vkCmdSetDepthBiasEnable */
    /*  211 */ CommandScopeDevice  , /* vkCmdSetPrimitiveRestartEnable */
    /*  212 */ CommandScopeDevice  , /* vkGetDeviceBufferMemoryRequirements */
    /*  213 */ CommandScopeDevice  , /* vkGetDeviceImageMemoryRequirements */
    /*  214 */ CommandScopeDevice  , /* vkGetDeviceImageSparseMemoryRequirements */
    /*  215 */ CommandScopeDevice  , /* vkCmdSetLineStipple */
    /*  216 */ CommandScopeDevice  , /* vkMapMemory2 */
    /*  217 */ CommandScopeDevice  , /* vkUnmapMemory2 */
    /*  218 */ CommandScopeDevice  , /* vkCmdBindIndexBuffer2 */
    /*  219 */ CommandScopeDevice  , /* vkGetRenderingAreaGranularity */
    /*  220 */ CommandScopeDevice  , /* vkGetDeviceImageSubresourceLayout */
    /*  221 */ CommandScopeDevice  , /* vkGetImageSubresourceLayout2 */
    /*  222 */ CommandScopeDevice  , /* vkCmdPushDescriptorSet */
    /*  223 */ CommandScopeDevice  , /* vkCmdPushDescriptorSetWithTemplate */
    /*  224 */ CommandScopeDevice  , /* vkCmdSetRenderingAttachmentLocations */
    /*  225 */ CommandScopeDevice  , /* vkCmdSetRenderingInputAttachmentIndices */
    /*  226 */ CommandScopeDevice  , /* vkCmdBindDescriptorSets2 */
    /*  227 */ CommandScopeDevice  , /* vkCmdPushConstants2 */
    /*  228 */ CommandScopeDevice  , /* vkCmdPushDescriptorSet2 */
    /*  229 */ CommandScopeDevice  , /* vkCmdPushDescriptorSetWithTemplate2 */
    /*  230 */ CommandScopeDevice  , /* vkCopyMemoryToImage */
    /*  231 */ CommandScopeDevice  , /* vkCopyImageToMemory */
    /*  232 */ CommandScopeDevice  , /* vkCopyImageToImage */
    /*  233 */ CommandScopeDevice  , /* vkTransitionImageLayout */
    /*  234 */ CommandScopeInstance, /* vkDestroySurfaceKHR */
    /*  235 */ CommandScopeInstance, /* vkGetPhysicalDeviceSurfaceSupportKHR */
    /*  236 */ CommandScopeInstance, /* vkGetPhysicalDeviceSurfaceCapabilitiesKHR */
    /*  237 */ CommandScopeInstance, /* vkGetPhysicalDeviceSurfaceFormatsKHR */
    /*  238 */ CommandScopeInstance, /* vkGetPhysicalDeviceSurfacePresentModesKHR */
    /*  239 */ CommandScopeDevice  , /* vkCreateSwapchainKHR */
    /*  240 */ CommandScopeDevice  , /* vkDestroySwapchainKHR */
    /*  241 */ CommandScopeDevice  , /* vkGetSwapchainImagesKHR */
    /*  242 */ CommandScopeDevice  , /* vkAcquireNextImageKHR */
    /*  243 */ CommandScopeDevice  , /* vkQueuePresentKHR */
    /*  244 */ CommandScopeDevice  , /* vkGetDeviceGroupPresentCapabilitiesKHR */
    /*  245 */ CommandScopeDevice  , /* vkGetDeviceGroupSurfacePresentModesKHR */
    /*  246 */ CommandScopeInstance, /* vkGetPhysicalDevicePresentRectanglesKHR */
    /*  247 */ CommandScopeDevice  , /* vkAcquireNextImage2KHR */
    /*  248 */ CommandScopeInstance, /* vkGetPhysicalDeviceDisplayPropertiesKHR */
    /*  249 */ CommandScopeInstance, /* vkGetPhysicalDeviceDisplayPlanePropertiesKHR */
    /*  250 */ CommandScopeInstance, /* vkGetDisplayPlaneSupportedDisplaysKHR */
    /*  251 */ CommandScopeInstance, /* vkGetDisplayModePropertiesKHR */
    /*  252 */ CommandScopeInstance, /* vkCreateDisplayModeKHR */
    /*  253 */ CommandScopeInstance, /* vkGetDisplayPlaneCapabilitiesKHR */
    /*  254 */ CommandScopeInstance, /* vkCreateDisplayPlaneSurfaceKHR */
    /*  255 */ CommandScopeDevice  , /* vkCreateSharedSwapchainsKHR */
    /*  256 */ CommandScopeInstance, /* vkCreateXlibSurfaceKHR */
    /*  257 */ CommandScopeInstance, /* vkGetPhysicalDeviceXlibPresentationSupportKHR */
    /*  258 */ CommandScopeInstance, /* vkCreateXcbSurfaceKHR */
    /*  259 */ CommandScopeInstance, /* vkGetPhysicalDeviceXcbPresentationSupportKHR */
    /*  260 */ CommandScopeInstance, /* vkCreateWaylandSurfaceKHR */
    /*  261 */ CommandScopeInstance, /* vkGetPhysicalDeviceWaylandPresentationSupportKHR */
    /*  262 */ CommandScopeInstance, /* vkCreateAndroidSurfaceKHR */
    /*  263 */ CommandScopeInstance, /* vkCreateWin32SurfaceKHR */
    /*  264 */ CommandScopeInstance, /* vkGetPhysicalDeviceWin32PresentationSupportKHR */
    /*  265 */ CommandScopeInstance, /* vkCreateDebugReportCallbackEXT */
    /*  266 */ CommandScopeInstance, /* vkDestroyDebugReportCallbackEXT */
    /*  267 */ CommandScopeInstance, /* vkDebugReportMessageEXT */
    /*  268 */ CommandScopeDevice  , /* vkDebugMarkerSetObjectTagEXT */
    /*  269 */ CommandScopeDevice  , /* vkDebugMarkerSetObjectNameEXT */
    /*  270 */ CommandScopeDevice  , /* vkCmdDebugMarkerBeginEXT */
    /*  271 */ CommandScopeDevice  , /* vkCmdDebugMarkerEndEXT */
    /*  272 */ CommandScopeDevice  , /* vkCmdDebugMarkerInsertEXT */
    /*  273 */ CommandScopeInstance, /* vkGetPhysicalDeviceVideoCapabilitiesKHR */
    /*  274 */ CommandScopeInstance, /* vkGetPhysicalDeviceVideoFormatPropertiesKHR */
    /*  275 */ CommandScopeDevice  , /* vkCreateVideoSessionKHR */
    /*  276 */ CommandScopeDevice  , /* vkDestroyVideoSessionKHR */
    /*  277 */ CommandScopeDevice  , /* vkGetVideoSessionMemoryRequirementsKHR */
    /*  278 */ CommandScopeDevice  , /* vkBindVideoSessionMemoryKHR */
    /*  279 */ CommandScopeDevice  , /* vkCreateVideoSessionParametersKHR */
    /*  280 */ CommandScopeDevice  , /* vkUpdateVideoSessionParametersKHR */
    /*  281 */ CommandScopeDevice  , /* vkDestroyVideoSessionParametersKHR */
    /*  282 */ CommandScopeDevice  , /* vkCmdBeginVideoCodingKHR */
    /*  283 */ CommandScopeDevice  , /* vkCmdEndVideoCodingKHR */
    /*  284 */ CommandScopeDevice  , /* vkCmdControlVideoCodingKHR */
    /*  285 */ CommandScopeDevice  , /* vkCmdDecodeVideoKHR */
    /*  286 */ CommandScopeDevice  , /* vkCmdBindTransformFeedbackBuffersEXT */
    /*  287 */ CommandScopeDevice  , /* vkCmdBeginTransformFeedbackEXT */
    /*  288 */ CommandScopeDevice  , /* vkCmdEndTransformFeedbackEXT */
    /*  289 */ CommandScopeDevice  , /* vkCmdBeginQueryIndexedEXT */
    /*  290 */ CommandScopeDevice  , /* vkCmdEndQueryIndexedEXT */
    /*  291 */ CommandScopeDevice  , /* vkCmdDrawIndirectByteCountEXT */
    /*  292 */ CommandScopeDevice  , /* vkCreateCuModuleNVX */
    /*  293 */ CommandScopeDevice  , /* vkCreateCuFunctionNVX */
    /*  294 */ CommandScopeDevice  , /* vkDestroyCuModuleNVX */
    /*  295 */ CommandScopeDevice  , /* vkDestroyCuFunctionNVX */
    /*  296 */ CommandScopeDevice  , /* vkCmdCuLaunchKernelNVX */
    /*  297 */ CommandScopeDevice  , /* vkGetImageViewHandleNVX */
    /*  298 */ CommandScopeDevice  , /* vkGetImageViewHandle64NVX */
    /*  299 */ CommandScopeDevice  , /* vkGetImageViewAddressNVX */
    /*  300 */ CommandScopeDevice  , /* vkCmdDrawIndirectCountAMD */
    /*  301 */ CommandScopeDevice  , /* vkCmdDrawIndexedIndirectCountAMD */
    /*  302 */ CommandScopeDevice  , /* vkGetShaderInfoAMD */
    /*  303 */ CommandScopeDevice  , /* vkCmdBeginRenderingKHR */
    /*  304 */ CommandScopeDevice  , /* vkCmdEndRenderingKHR */
    /*  305 */ CommandScopeInstance, /* vkCreateStreamDescriptorSurfaceGGP */
    /*  306 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalImageFormatPropertiesNV */
    /*  307 */ CommandScopeDevice  , /* vkGetMemoryWin32HandleNV */
    /*  308 */ CommandScopeInstance, /* vkGetPhysicalDeviceFeatures2KHR */
    /*  309 */ CommandScopeInstance, /* vkGetPhysicalDeviceProperties2KHR */
    /*  310 */ CommandScopeInstance, /* vkGetPhysicalDeviceFormatProperties2KHR */
    /*  311 */ CommandScopeInstance, /* vkGetPhysicalDeviceImageFormatProperties2KHR */
    /*  312 */ CommandScopeInstance, /* vkGetPhysicalDeviceQueueFamilyProperties2KHR */
    /*  313 */ CommandScopeInstance, /* vkGetPhysicalDeviceMemoryProperties2KHR */
    /*  314 */ CommandScopeInstance, /* vkGetPhysicalDeviceSparseImageFormatProperties2KHR */
    /*  315 */ CommandScopeDevice  , /* vkGetDeviceGroupPeerMemoryFeaturesKHR */
    /*  316 */ CommandScopeDevice  , /* vkCmdSetDeviceMaskKHR */
    /*  317 */ CommandScopeDevice  , /* vkCmdDispatchBaseKHR */
    /*  318 */ CommandScopeInstance, /* vkCreateViSurfaceNN */
    /*  319 */ CommandScopeDevice  , /* vkTrimCommandPoolKHR */
    /*  320 */ CommandScopeInstance, /* vkEnumeratePhysicalDeviceGroupsKHR */
    /*  321 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalBufferPropertiesKHR */
    /*  322 */ CommandScopeDevice  , /* vkGetMemoryWin32HandleKHR */
    /*  323 */ CommandScopeDevice  , /* vkGetMemoryWin32HandlePropertiesKHR */
    /*  324 */ CommandScopeDevice  , /* vkGetMemoryFdKHR */
    /*  325 */ CommandScopeDevice  , /* vkGetMemoryFdPropertiesKHR */
    /*  326 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalSemaphorePropertiesKHR */
    /*  327 */ CommandScopeDevice  , /* vkImportSemaphoreWin32HandleKHR */
    /*  328 */ CommandScopeDevice  , /* vkGetSemaphoreWin32HandleKHR */
    /*  329 */ CommandScopeDevice  , /* vkImportSemaphoreFdKHR */
    /*  330 */ CommandScopeDevice  , /* vkGetSemaphoreFdKHR */
    /*  331 */ CommandScopeDevice  , /* vkCmdPushDescriptorSetKHR */
    /*  332 */ CommandScopeDevice  , /* vkCmdPushDescriptorSetWithTemplateKHR */
    /*  333 */ CommandScopeDevice  , /* vkCmdBeginConditionalRenderingEXT */
    /*  334 */ CommandScopeDevice  , /* vkCmdEndConditionalRenderingEXT */
    /*  335 */ CommandScopeDevice  , /* vkCreateDescriptorUpdateTemplateKHR */
    /*  336 */ CommandScopeDevice  , /* vkDestroyDescriptorUpdateTemplateKHR */
    /*  337 */ CommandScopeDevice  , /* vkUpdateDescriptorSetWithTemplateKHR */
    /*  338 */ CommandScopeDevice  , /* vkCmdSetViewportWScalingNV */
    /*  339 */ CommandScopeInstance, /* vkReleaseDisplayEXT */
    /*  340 */ CommandScopeInstance, /* vkAcquireXlibDisplayEXT */
    /*  341 */ CommandScopeInstance, /* vkGetRandROutputDisplayEXT */
    /*  342 */ CommandScopeInstance, /* vkGetPhysicalDeviceSurfaceCapabilities2EXT */
    /*  343 */ CommandScopeDevice  , /* vkDisplayPowerControlEXT */
    /*  344 */ CommandScopeDevice  , /* vkRegisterDeviceEventEXT */
    /*  345 */ CommandScopeDevice  , /* vkRegisterDisplayEventEXT */
    /*  346 */ CommandScopeDevice  , /* vkGetSwapchainCounterEXT */
    /*  347 */ CommandScopeDevice  , /* vkGetRefreshCycleDurationGOOGLE */
    /*  348 */ CommandScopeDevice  , /* vkGetPastPresentationTimingGOOGLE */
    /*  349 */ CommandScopeDevice  , /* vkCmdSetDiscardRectangleEXT */
    /*  350 */ CommandScopeDevice  , /* vkCmdSetDiscardRectangleEnableEXT */
    /*  351 */ CommandScopeDevice  , /* vkCmdSetDiscardRectangleModeEXT */
    /*  352 */ CommandScopeDevice  , /* vkSetHdrMetadataEXT */
    /*  353 */ CommandScopeDevice  , /* vkCreateRenderPass2KHR */
    /*  354 */ CommandScopeDevice  , /* vkCmdBeginRenderPass2KHR */
    /*  355 */ CommandScopeDevice  , /* vkCmdNextSubpass2KHR */
    /*  356 */ CommandScopeDevice  , /* vkCmdEndRenderPass2KHR */
    /*  357 */ CommandScopeDevice  , /* vkGetSwapchainStatusKHR */
    /*  358 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalFencePropertiesKHR */
    /*  359 */ CommandScopeDevice  , /* vkImportFenceWin32HandleKHR */
    /*  360 */ CommandScopeDevice  , /* vkGetFenceWin32HandleKHR */
    /*  361 */ CommandScopeDevice  , /* vkImportFenceFdKHR */
    /*  362 */ CommandScopeDevice  , /* vkGetFenceFdKHR */
    /*  363 */ CommandScopeInstance, /* vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR */
    /*  364 */ CommandScopeInstance, /* vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR */
    /*  365 */ CommandScopeDevice  , /* vkAcquireProfilingLockKHR */
    /*  366 */ CommandScopeDevice  , /* vkReleaseProfilingLockKHR */
    /*  367 */ CommandScopeInstance, /* vkGetPhysicalDeviceSurfaceCapabilities2KHR */
    /*  368 */ CommandScopeInstance, /* vkGetPhysicalDeviceSurfaceFormats2KHR */
    /*  369 */ CommandScopeInstance, /* vkGetPhysicalDeviceDisplayProperties2KHR */
    /*  370 */ CommandScopeInstance, /* vkGetPhysicalDeviceDisplayPlaneProperties2KHR */
    /*  371 */ CommandScopeInstance, /* vkGetDisplayModeProperties2KHR */
    /*  372 */ CommandScopeInstance, /* vkGetDisplayPlaneCapabilities2KHR */
    /*  373 */ CommandScopeInstance, /* vkCreateIOSSurfaceMVK */
    /*  374 */ CommandScopeInstance, /* vkCreateMacOSSurfaceMVK */
    /*  375 */ CommandScopeDevice  , /* vkSetDebugUtilsObjectNameEXT */
    /*  376 */ CommandScopeDevice  , /* vkSetDebugUtilsObjectTagEXT */
    /*  377 */ CommandScopeDevice  , /* vkQueueBeginDebugUtilsLabelEXT */
    /*  378 */ CommandScopeDevice  , /* vkQueueEndDebugUtilsLabelEXT */
    /*  379 */ CommandScopeDevice  , /* vkQueueInsertDebugUtilsLabelEXT */
    /*  380 */ CommandScopeDevice  , /* vkCmdBeginDebugUtilsLabelEXT */
    /*  381 */ CommandScopeDevice  , /* vkCmdEndDebugUtilsLabelEXT */
    /*  382 */ CommandScopeDevice  , /* vkCmdInsertDebugUtilsLabelEXT */
    /*  383 */ CommandScopeInstance, /* vkCreateDebugUtilsMessengerEXT */
    /*  384 */ CommandScopeInstance, /* vkDestroyDebugUtilsMessengerEXT */
    /*  385 */ CommandScopeInstance, /* vkSubmitDebugUtilsMessageEXT */
    /*  386 */ CommandScopeDevice  , /* vkGetAndroidHardwareBufferPropertiesANDROID */
    /*  387 */ CommandScopeDevice  , /* vkGetMemoryAndroidHardwareBufferANDROID */
    /*  388 */ CommandScopeDevice  , /* vkCreateExecutionGraphPipelinesAMDX */
    /*  389 */ CommandScopeDevice  , /* vkGetExecutionGraphPipelineScratchSizeAMDX */
    /*  390 */ CommandScopeDevice  , /* vkGetExecutionGraphPipelineNodeIndexAMDX */
    /*  391 */ CommandScopeDevice  , /* vkCmdInitializeGraphScratchMemoryAMDX */
    /*  392 */ CommandScopeDevice  , /* vkCmdDispatchGraphAMDX */
    /*  393 */ CommandScopeDevice  , /* vkCmdDispatchGraphIndirectAMDX */
    /*  394 */ CommandScopeDevice  , /* vkCmdDispatchGraphIndirectCountAMDX */
    /*  395 */ CommandScopeDevice  , /* vkCmdSetSampleLocationsEXT */
    /*  396 */ CommandScopeInstance, /* vkGetPhysicalDeviceMultisamplePropertiesEXT */
    /*  397 */ CommandScopeDevice  , /* vkGetImageMemoryRequirements2KHR */
    /*  398 */ CommandScopeDevice  , /* vkGetBufferMemoryRequirements2KHR */
    /*  399 */ CommandScopeDevice  , /* vkGetImageSparseMemoryRequirements2KHR */
    /*  400 */ CommandScopeDevice  , /* vkCreateAccelerationStructureKHR */
    /*  401 */ CommandScopeDevice  , /* vkDestroyAccelerationStructureKHR */
    /*  402 */ CommandScopeDevice  , /* vkCmdBuildAccelerationStructuresKHR */
    /*  403 */ CommandScopeDevice  , /* vkCmdBuildAccelerationStructuresIndirectKHR */
    /*  404 */ CommandScopeDevice  , /* vkBuildAccelerationStructuresKHR */
    /*  405 */ CommandScopeDevice  , /* vkCopyAccelerationStructureKHR */
    /*  406 */ CommandScopeDevice  , /* vkCopyAccelerationStructureToMemoryKHR */
    /*  407 */ CommandScopeDevice  , /* vkCopyMemoryToAccelerationStructureKHR */
    /*  408 */ CommandScopeDevice  , /* vkWriteAccelerationStructuresPropertiesKHR */
    /*  409 */ CommandScopeDevice  , /* vkCmdCopyAccelerationStructureKHR */
    /*  410 */ CommandScopeDevice  , /* vkCmdCopyAccelerationStructureToMemoryKHR */
    /*  411 */ CommandScopeDevice  , /* vkCmdCopyMemoryToAccelerationStructureKHR */
    /*  412 */ CommandScopeDevice  , /* vkGetAccelerationStructureDeviceAddressKHR */
    /*  413 */ CommandScopeDevice  , /* vkCmdWriteAccelerationStructuresPropertiesKHR */
    /*  414 */ CommandScopeDevice  , /* vkGetDeviceAccelerationStructureCompatibilityKHR */
    /*  415 */ CommandScopeDevice  , /* vkGetAccelerationStructureBuildSizesKHR */
    /*  416 */ CommandScopeDevice  , /* vkCmdTraceRaysKHR */
    /*  417 */ CommandScopeDevice  , /* vkCreateRayTracingPipelinesKHR */
    /*  418 */ CommandScopeDevice  , /* vkGetRayTracingShaderGroupHandlesKHR */
    /*  419 */ CommandScopeDevice  , /* vkGetRayTracingCaptureReplayShaderGroupHandlesKHR */
    /*  420 */ CommandScopeDevice  , /* vkCmdTraceRaysIndirectKHR */
    /*  421 */ CommandScopeDevice  , /* vkGetRayTracingShaderGroupStackSizeKHR */
    /*  422 */ CommandScopeDevice  , /* vkCmdSetRayTracingPipelineStackSizeKHR */
    /*  423 */ CommandScopeDevice  , /* vkCreateSamplerYcbcrConversionKHR */
    /*  424 */ CommandScopeDevice  , /* vkDestroySamplerYcbcrConversionKHR */
    /*  425 */ CommandScopeDevice  , /* vkBindBufferMemory2KHR */
    /*  426 */ CommandScopeDevice  , /* vkBindImageMemory2KHR */
    /*  427 */ CommandScopeDevice  , /* vkGetImageDrmFormatModifierPropertiesEXT */
    /*  428 */ CommandScopeDevice  , /* vkCreateValidationCacheEXT */
    /*  429 */ CommandScopeDevice  , /* vkDestroyValidationCacheEXT */
    /*  430 */ CommandScopeDevice  , /* vkMergeValidationCachesEXT */
    /*  431 */ CommandScopeDevice  , /* vkGetValidationCacheDataEXT */
    /*  432 */ CommandScopeDevice  , /* vkCmdBindShadingRateImageNV */
    /*  433 */ CommandScopeDevice  , /* vkCmdSetViewportShadingRatePaletteNV */
    /*  434 */ CommandScopeDevice  , /* vkCmdSetCoarseSampleOrderNV */
    /*  435 */ CommandScopeDevice  , /* vkCreateAccelerationStructureNV */
    /*  436 */ CommandScopeDevice  , /* vkDestroyAccelerationStructureNV */
    /*  437 */ CommandScopeDevice  , /* vkGetAccelerationStructureMemoryRequirementsNV */
    /*  438 */ CommandScopeDevice  , /* vkBindAccelerationStructureMemoryNV */
    /*  439 */ CommandScopeDevice  , /* vkCmdBuildAccelerationStructureNV */
    /*  440 */ CommandScopeDevice  , /* vkCmdCopyAccelerationStructureNV */
    /*  441 */ CommandScopeDevice  , /* vkCmdTraceRaysNV */
    /*  442 */ CommandScopeDevice  , /* vkCreateRayTracingPipelinesNV */
    /*  443 */ CommandScopeDevice  , /* vkGetRayTracingShaderGroupHandlesNV */
    /*  444 */ CommandScopeDevice  , /* vkGetAccelerationStructureHandleNV */
    /*  445 */ CommandScopeDevice  , /* vkCmdWriteAccelerationStructuresPropertiesNV */
    /*  446 */ CommandScopeDevice  , /* vkCompileDeferredNV */
    /*  447 */ CommandScopeDevice  , /* vkGetDescriptorSetLayoutSupportKHR */
    /*  448 */ CommandScopeDevice  , /* vkCmdDrawIndirectCountKHR */
    /*  449 */ CommandScopeDevice  , /* vkCmdDrawIndexedIndirectCountKHR */
    /*  450 */ CommandScopeDevice  , /* vkGetMemoryHostPointerPropertiesEXT */
    /*  451 */ CommandScopeDevice  , /* vkCmdWriteBufferMarkerAMD */
    /*  452 */ CommandScopeDevice  , /* vkCmdWriteBufferMarker2AMD */
    /*  453 */ CommandScopeInstance, /* vkGetPhysicalDeviceCalibrateableTimeDomainsEXT */
    /*  454 */ CommandScopeDevice  , /* vkGetCalibratedTimestampsEXT */
    /*  455 */ CommandScopeDevice  , /* vkCmdDrawMeshTasksNV */
    /*  456 */ CommandScopeDevice  , /* vkCmdDrawMeshTasksIndirectNV */
    /*  457 */ CommandScopeDevice  , /* vkCmdDrawMeshTasksIndirectCountNV */
    /*  458 */ CommandScopeDevice  , /* vkCmdSetExclusiveScissorEnableNV */
    /*  459 */ CommandScopeDevice  , /* vkCmdSetExclusiveScissorNV */
    /*  460 */ CommandScopeDevice  , /* vkCmdSetCheckpointNV */
    /*  461 */ CommandScopeDevice  , /* vkGetQueueCheckpointDataNV */
    /*  462 */ CommandScopeDevice  , /* vkGetQueueCheckpointData2NV */
    /*  463 */ CommandScopeDevice  , /* vkGetSemaphoreCounterValueKHR */
    /*  464 */ CommandScopeDevice  , /* vkWaitSemaphoresKHR */
    /*  465 */ CommandScopeDevice  , /* vkSignalSemaphoreKHR */
    /*  466 */ CommandScopeDevice  , /* vkInitializePerformanceApiINTEL */
    /*  467 */ CommandScopeDevice  , /* vkUninitializePerformanceApiINTEL */
    /*  468 */ CommandScopeDevice  , /* vkCmdSetPerformanceMarkerINTEL */
    /*  469 */ CommandScopeDevice  , /* vkCmdSetPerformanceStreamMarkerINTEL */
    /*  470 */ CommandScopeDevice  , /* vkCmdSetPerformanceOverrideINTEL */
    /*  471 */ CommandScopeDevice  , /* vkAcquirePerformanceConfigurationINTEL */
    /*  472 */ CommandScopeDevice  , /* vkReleasePerformanceConfigurationINTEL */
    /*  473 */ CommandScopeDevice  , /* vkQueueSetPerformanceConfigurationINTEL */
    /*  474 */ CommandScopeDevice  , /* vkGetPerformanceParameterINTEL */
    /*  475 */ CommandScopeDevice  , /* vkSetLocalDimmingAMD */
    /*  476 */ CommandScopeInstance, /* vkCreateImagePipeSurfaceFUCHSIA */
    /*  477 */ CommandScopeInstance, /* vkCreateMetalSurfaceEXT */
    /*  478 */ CommandScopeInstance, /* vkGetPhysicalDeviceFragmentShadingRatesKHR */
    /*  479 */ CommandScopeDevice  , /* vkCmdSetFragmentShadingRateKHR */
    /*  480 */ CommandScopeDevice  , /* vkCmdSetRenderingAttachmentLocationsKHR */
    /*  481 */ CommandScopeDevice  , /* vkCmdSetRenderingInputAttachmentIndicesKHR */
    /*  482 */ CommandScopeDevice  , /* vkGetBufferDeviceAddressEXT */
    /*  483 */ CommandScopeInstance, /* vkGetPhysicalDeviceToolPropertiesEXT */
    /*  484 */ CommandScopeDevice  , /* vkWaitForPresentKHR */
    /*  485 */ CommandScopeInstance, /* vkGetPhysicalDeviceCooperativeMatrixPropertiesNV */
    /*  486 */ CommandScopeInstance, /* vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV */
    /*  487 */ CommandScopeInstance, /* vkGetPhysicalDeviceSurfacePresentModes2EXT */
    /*  488 */ CommandScopeDevice  , /* vkAcquireFullScreenExclusiveModeEXT */
    /*  489 */ CommandScopeDevice  , /* vkReleaseFullScreenExclusiveModeEXT */
    /*  490 */ CommandScopeDevice  , /* vkGetDeviceGroupSurfacePresentModes2EXT */
    /*  491 */ CommandScopeInstance, /* vkCreateHeadlessSurfaceEXT */
    /*  492 */ CommandScopeDevice  , /* vkGetBufferDeviceAddressKHR */
    /*  493 */ CommandScopeDevice  , /* vkGetBufferOpaqueCaptureAddressKHR */
    /*  494 */ CommandScopeDevice  , /* vkGetDeviceMemoryOpaqueCaptureAddressKHR */
    /*  495 */ CommandScopeDevice  , /* vkCmdSetLineStippleEXT */
    /*  496 */ CommandScopeDevice  , /* vkResetQueryPoolEXT */
    /*  497 */ CommandScopeDevice  , /* vkCmdSetCullModeEXT */
    /*  498 */ CommandScopeDevice  , /* vkCmdSetFrontFaceEXT */
    /*  499 */ CommandScopeDevice  , /* vkCmdSetPrimitiveTopologyEXT */
    /*  500 */ CommandScopeDevice  , /* vkCmdSetViewportWithCountEXT */
    /*  501 */ CommandScopeDevice  , /* vkCmdSetScissorWithCountEXT */
    /*  502 */ CommandScopeDevice  , /* vkCmdBindVertexBuffers2EXT */
    /*  503 */ CommandScopeDevice  , /* vkCmdSetDepthTestEnableEXT */
    /*  504 */ CommandScopeDevice  , /* vkCmdSetDepthWriteEnableEXT */
    /*  505 */ CommandScopeDevice  , /* vkCmdSetDepthCompareOpEXT */
    /*  506 */ CommandScopeDevice  , /* vkCmdSetDepthBoundsTestEnableEXT */
    /*  507 */ CommandScopeDevice  , /* vkCmdSetStencilTestEnableEXT */
    /*  508 */ CommandScopeDevice  , /* vkCmdSetStencilOpEXT */
    /*  509 */ CommandScopeDevice  , /* vkCreateDeferredOperationKHR */
    /*  510 */ CommandScopeDevice  , /* vkDestroyDeferredOperationKHR */
    /*  511 */ CommandScopeDevice  , /* vkGetDeferredOperationMaxConcurrencyKHR */
    /*  512 */ CommandScopeDevice  , /* vkGetDeferredOperationResultKHR */
    /*  513 */ CommandScopeDevice  , /* vkDeferredOperationJoinKHR */
    /*  514 */ CommandScopeDevice  , /* vkGetPipelineExecutablePropertiesKHR */
    /*  515 */ CommandScopeDevice  , /* vkGetPipelineExecutableStatisticsKHR */
    /*  516 */ CommandScopeDevice  , /* vkGetPipelineExecutableInternalRepresentationsKHR */
    /*  517 */ CommandScopeDevice  , /* vkCopyMemoryToImageEXT */
    /*  518 */ CommandScopeDevice  , /* vkCopyImageToMemoryEXT */
    /*  519 */ CommandScopeDevice  , /* vkCopyImageToImageEXT */
    /*  520 */ CommandScopeDevice  , /* vkTransitionImageLayoutEXT */
    /*  521 */ CommandScopeDevice  , /* vkGetImageSubresourceLayout2EXT */
    /*  522 */ CommandScopeDevice  , /* vkMapMemory2KHR */
    /*  523 */ CommandScopeDevice  , /* vkUnmapMemory2KHR */
    /*  524 */ CommandScopeDevice  , /* vkReleaseSwapchainImagesEXT */
    /*  525 */ CommandScopeDevice  , /* vkGetGeneratedCommandsMemoryRequirementsNV */
    /*  526 */ CommandScopeDevice  , /* vkCmdPreprocessGeneratedCommandsNV */
    /*  527 */ CommandScopeDevice  , /* vkCmdExecuteGeneratedCommandsNV */
    /*  528 */ CommandScopeDevice  , /* vkCmdBindPipelineShaderGroupNV */
    /*  529 */ CommandScopeDevice  , /* vkCreateIndirectCommandsLayoutNV */
    /*  530 */ CommandScopeDevice  , /* vkDestroyIndirectCommandsLayoutNV */
    /*  531 */ CommandScopeDevice  , /* vkCmdSetDepthBias2EXT */
    /*  532 */ CommandScopeInstance, /* vkAcquireDrmDisplayEXT */
    /*  533 */ CommandScopeInstance, /* vkGetDrmDisplayEXT */
    /*  534 */ CommandScopeDevice  , /* vkCreatePrivateDataSlotEXT */
    /*  535 */ CommandScopeDevice  , /* vkDestroyPrivateDataSlotEXT */
    /*  536 */ CommandScopeDevice  , /* vkSetPrivateDataEXT */
    /*  537 */ CommandScopeDevice  , /* vkGetPrivateDataEXT */
    /*  538 */ CommandScopeInstance, /* vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR */
    /*  539 */ CommandScopeDevice  , /* vkGetEncodedVideoSessionParametersKHR */
    /*  540 */ CommandScopeDevice  , /* vkCmdEncodeVideoKHR */
    /*  541 */ CommandScopeDevice  , /* vkCreateCudaModuleNV */
    /*  542 */ CommandScopeDevice  , /* vkGetCudaModuleCacheNV */
    /*  543 */ CommandScopeDevice  , /* vkCreateCudaFunctionNV */
    /*  544 */ CommandScopeDevice  , /* vkDestroyCudaModuleNV */
    /*  545 */ CommandScopeDevice  , /* vkDestroyCudaFunctionNV */
    /*  546 */ CommandScopeDevice  , /* vkCmdCudaLaunchKernelNV */
    /*  547 */ CommandScopeDevice  , /* vkCmdDispatchTileQCOM */
    /*  548 */ CommandScopeDevice  , /* vkCmdBeginPerTileExecutionQCOM */
    /*  549 */ CommandScopeDevice  , /* vkCmdEndPerTileExecutionQCOM */
    /*  550 */ CommandScopeDevice  , /* vkExportMetalObjectsEXT */
    /*  551 */ CommandScopeDevice  , /* vkCmdSetEvent2KHR */
    /*  552 */ CommandScopeDevice  , /* vkCmdResetEvent2KHR */
    /*  553 */ CommandScopeDevice  , /* vkCmdWaitEvents2KHR */
    /*  554 */ CommandScopeDevice  , /* vkCmdPipelineBarrier2KHR */
    /*  555 */ CommandScopeDevice  , /* vkCmdWriteTimestamp2KHR */
    /*  556 */ CommandScopeDevice  , /* vkQueueSubmit2KHR */
    /*  557 */ CommandScopeDevice  , /* vkGetDescriptorSetLayoutSizeEXT */
    /*  558 */ CommandScopeDevice  , /* vkGetDescriptorSetLayoutBindingOffsetEXT */
    /*  559 */ CommandScopeDevice  , /* vkGetDescriptorEXT */
    /*  560 */ CommandScopeDevice  , /* vkCmdBindDescriptorBuffersEXT */
    /*  561 */ CommandScopeDevice  , /* vkCmdSetDescriptorBufferOffsetsEXT */
    /*  562 */ CommandScopeDevice  , /* vkCmdBindDescriptorBufferEmbeddedSamplersEXT */
    /*  563 */ CommandScopeDevice  , /* vkGetBufferOpaqueCaptureDescriptorDataEXT */
    /*  564 */ CommandScopeDevice  , /* vkGetImageOpaqueCaptureDescriptorDataEXT */
    /*  565 */ CommandScopeDevice  , /* vkGetImageViewOpaqueCaptureDescriptorDataEXT */
    /*  566 */ CommandScopeDevice  , /* vkGetSamplerOpaqueCaptureDescriptorDataEXT */
    /*  567 */ CommandScopeDevice  , /* vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT */
    /*  568 */ CommandScopeDevice  , /* vkCmdSetFragmentShadingRateEnumNV */
    /*  569 */ CommandScopeDevice  , /* vkCmdDrawMeshTasksEXT */
    /*  570 */ CommandScopeDevice  , /* vkCmdDrawMeshTasksIndirectEXT */
    /*  571 */ CommandScopeDevice  , /* vkCmdDrawMeshTasksIndirectCountEXT */
    /*  572 */ CommandScopeDevice  , /* vkCmdCopyBuffer2KHR */
    /*  573 */ CommandScopeDevice  , /* vkCmdCopyImage2KHR */
    /*  574 */ CommandScopeDevice  , /* vkCmdCopyBufferToImage2KHR */
    /*  575 */ CommandScopeDevice  , /* vkCmdCopyImageToBuffer2KHR */
    /*  576 */ CommandScopeDevice  , /* vkCmdBlitImage2KHR */
    /*  577 */ CommandScopeDevice  , /* vkCmdResolveImage2KHR */
    /*  578 */ CommandScopeDevice  , /* vkGetDeviceFaultInfoEXT */
    /*  579 */ CommandScopeInstance, /* vkAcquireWinrtDisplayNV */
    /*  580 */ CommandScopeInstance, /* vkGetWinrtDisplayNV */
    /*  581 */ CommandScopeInstance, /* vkCreateDirectFBSurfaceEXT */
    /*  582 */ CommandScopeInstance, /* vkGetPhysicalDeviceDirectFBPresentationSupportEXT */
    /*  583 */ CommandScopeDevice  , /* vkCmdSetVertexInputEXT */
    /*  584 */ CommandScopeDevice  , /* vkGetMemoryZirconHandleFUCHSIA */
    /*  585 */ CommandScopeDevice  , /* vkGetMemoryZirconHandlePropertiesFUCHSIA */
    /*  586 */ CommandScopeDevice  , /* vkImportSemaphoreZirconHandleFUCHSIA */
    /*  587 */ CommandScopeDevice  , /* vkGetSemaphoreZirconHandleFUCHSIA */
    /*  588 */ CommandScopeDevice  , /* vkCreateBufferCollectionFUCHSIA */
    /*  589 */ CommandScopeDevice  , /* vkSetBufferCollectionImageConstraintsFUCHSIA */
    /*  590 */ CommandScopeDevice  , /* vkSetBufferCollectionBufferConstraintsFUCHSIA */
    /*  591 */ CommandScopeDevice  , /* vkDestroyBufferCollectionFUCHSIA */
    /*  592 */ CommandScopeDevice  , /* vkGetBufferCollectionPropertiesFUCHSIA */
    /*  593 */ CommandScopeDevice  , /* vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI */
    /*  594 */ CommandScopeDevice  , /* vkCmdSubpassShadingHUAWEI */
    /*  595 */ CommandScopeDevice  , /* vkCmdBindInvocationMaskHUAWEI */
    /*  596 */ CommandScopeDevice  , /* vkGetMemoryRemoteAddressNV */
    /*  597 */ CommandScopeDevice  , /* vkGetPipelinePropertiesEXT */
    /*  598 */ CommandScopeDevice  , /* vkCmdSetPatchControlPointsEXT */
    /*  599 */ CommandScopeDevice  , /* vkCmdSetRasterizerDiscardEnableEXT */
    /*  600 */ CommandScopeDevice  , /* vkCmdSetDepthBiasEnableEXT */
    /*  601 */ CommandScopeDevice  , /* vkCmdSetLogicOpEXT */
    /*  602 */ CommandScopeDevice  , /* vkCmdSetPrimitiveRestartEnableEXT */
    /*  603 */ CommandScopeInstance, /* vkCreateScreenSurfaceQNX */
    /*  604 */ CommandScopeInstance, /* vkGetPhysicalDeviceScreenPresentationSupportQNX */
    /*  605 */ CommandScopeDevice  , /* vkCmdSetColorWriteEnableEXT */
    /*  606 */ CommandScopeDevice  , /* vkCmdTraceRaysIndirect2KHR */
    /*  607 */ CommandScopeDevice  , /* vkCmdDrawMultiEXT */
    /*  608 */ CommandScopeDevice  , /* vkCmdDrawMultiIndexedEXT */
    /*  609 */ CommandScopeDevice  , /* vkCreateMicromapEXT */
    /*  610 */ CommandScopeDevice  , /* vkDestroyMicromapEXT */
    /*  611 */ CommandScopeDevice  , /* vkCmdBuildMicromapsEXT */
    /*  612 */ CommandScopeDevice  , /* vkBuildMicromapsEXT */
    /*  613 */ CommandScopeDevice  , /* vkCopyMicromapEXT */
    /*  614 */ CommandScopeDevice  , /* vkCopyMicromapToMemoryEXT */
    /*  615 */ CommandScopeDevice  , /* vkCopyMemoryToMicromapEXT */
    /*  616 */ CommandScopeDevice  , /* vkWriteMicromapsPropertiesEXT */
    /*  617 */ CommandScopeDevice  , /* vkCmdCopyMicromapEXT */
    /*  618 */ CommandScopeDevice  , /* vkCmdCopyMicromapToMemoryEXT */
    /*  619 */ CommandScopeDevice  , /* vkCmdCopyMemoryToMicromapEXT */
    /*  620 */ CommandScopeDevice  , /* vkCmdWriteMicromapsPropertiesEXT */
    /*  621 */ CommandScopeDevice  , /* vkGetDeviceMicromapCompatibilityEXT */
    /*  622 */ CommandScopeDevice  , /* vkGetMicromapBuildSizesEXT */
    /*  623 */ CommandScopeDevice  , /* vkCmdDrawClusterHUAWEI */
    /*  624 */ CommandScopeDevice  , /* vkCmdDrawClusterIndirectHUAWEI */
    /*  625 */ CommandScopeDevice  , /* vkSetDeviceMemoryPriorityEXT */
    /*  626 */ CommandScopeDevice  , /* vkGetDeviceBufferMemoryRequirementsKHR */
    /*  627 */ CommandScopeDevice  , /* vkGetDeviceImageMemoryRequirementsKHR */
    /*  628 */ CommandScopeDevice  , /* vkGetDeviceImageSparseMemoryRequirementsKHR */
    /*  629 */ CommandScopeDevice  , /* vkGetDescriptorSetLayoutHostMappingInfoVALVE */
    /*  630 */ CommandScopeDevice  , /* vkGetDescriptorSetHostMappingVALVE */
    /*  631 */ CommandScopeDevice  , /* vkCmdCopyMemoryIndirectNV */
    /*  632 */ CommandScopeDevice  , /* vkCmdCopyMemoryToImageIndirectNV */
    /*  633 */ CommandScopeDevice  , /* vkCmdDecompressMemoryNV */
    /*  634 */ CommandScopeDevice  , /* vkCmdDecompressMemoryIndirectCountNV */
    /*  635 */ CommandScopeDevice  , /* vkGetPipelineIndirectMemoryRequirementsNV */
    /*  636 */ CommandScopeDevice  , /* vkCmdUpdatePipelineIndirectBufferNV */
    /*  637 */ CommandScopeDevice  , /* vkGetPipelineIndirectDeviceAddressNV */
    /*  638 */ CommandScopeDevice  , /* vkCmdSetDepthClampEnableEXT */
    /*  639 */ CommandScopeDevice  , /* vkCmdSetPolygonModeEXT */
    /*  640 */ CommandScopeDevice  , /* vkCmdSetRasterizationSamplesEXT */
    /*  641 */ CommandScopeDevice  , /* vkCmdSetSampleMaskEXT */
    /*  642 */ CommandScopeDevice  , /* vkCmdSetAlphaToCoverageEnableEXT */
    /*  643 */ CommandScopeDevice  , /* vkCmdSetAlphaToOneEnableEXT */
    /*  644 */ CommandScopeDevice  , /* vkCmdSetLogicOpEnableEXT */
    /*  645 */ CommandScopeDevice  , /* vkCmdSetColorBlendEnableEXT */
    /*  646 */ CommandScopeDevice  , /* vkCmdSetColorBlendEquationEXT */
    /*  647 */ CommandScopeDevice  , /* vkCmdSetColorWriteMaskEXT */
    /*  648 */ CommandScopeDevice  , /* vkCmdSetTessellationDomainOriginEXT */
    /*  649 */ CommandScopeDevice  , /* vkCmdSetRasterizationStreamEXT */
    /*  650 */ CommandScopeDevice  , /* vkCmdSetConservativeRasterizationModeEXT */
    /*  651 */ CommandScopeDevice  , /* vkCmdSetExtraPrimitiveOverestimationSizeEXT */
    /*  652 */ CommandScopeDevice  , /* vkCmdSetDepthClipEnableEXT */
    /*  653 */ CommandScopeDevice  , /* vkCmdSetSampleLocationsEnableEXT */
    /*  654 */ CommandScopeDevice  , /* vkCmdSetColorBlendAdvancedEXT */
    /*  655 */ CommandScopeDevice  , /* vkCmdSetProvokingVertexModeEXT */
    /*  656 */ CommandScopeDevice  , /* vkCmdSetLineRasterizationModeEXT */
    /*  657 */ CommandScopeDevice  , /* vkCmdSetLineStippleEnableEXT */
    /*  658 */ CommandScopeDevice  , /* vkCmdSetDepthClipNegativeOneToOneEXT */
    /*  659 */ CommandScopeDevice  , /* vkCmdSetViewportWScalingEnableNV */
    /*  660 */ CommandScopeDevice  , /* vkCmdSetViewportSwizzleNV */
    /*  661 */ CommandScopeDevice  , /* vkCmdSetCoverageToColorEnableNV */
    /*  662 */ CommandScopeDevice  , /* vkCmdSetCoverageToColorLocationNV */
    /*  663 */ CommandScopeDevice  , /* vkCmdSetCoverageModulationModeNV */
    /*  664 */ CommandScopeDevice  , /* vkCmdSetCoverageModulationTableEnableNV */
    /*  665 */ CommandScopeDevice  , /* vkCmdSetCoverageModulationTableNV */
    /*  666 */ CommandScopeDevice  , /* vkCmdSetShadingRateImageEnableNV */
    /*  667 */ CommandScopeDevice  , /* vkCmdSetRepresentativeFragmentTestEnableNV */
    /*  668 */ CommandScopeDevice  , /* vkCmdSetCoverageReductionModeNV */
    /*  669 */ CommandScopeDevice  , /* vkCreateTensorARM */
    /*  670 */ CommandScopeDevice  , /* vkDestroyTensorARM */
    /*  671 */ CommandScopeDevice  , /* vkCreateTensorViewARM */
    /*  672 */ CommandScopeDevice  , /* vkDestroyTensorViewARM */
    /*  673 */ CommandScopeDevice  , /* vkGetTensorMemoryRequirementsARM */
    /*  674 */ CommandScopeDevice  , /* vkBindTensorMemoryARM */
    /*  675 */ CommandScopeDevice  , /* vkGetDeviceTensorMemoryRequirementsARM */
    /*  676 */ CommandScopeDevice  , /* vkCmdCopyTensorARM */
    /*  677 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalTensorPropertiesARM */
    /*  678 */ CommandScopeDevice  , /* vkGetTensorOpaqueCaptureDescriptorDataARM */
    /*  679 */ CommandScopeDevice  , /* vkGetTensorViewOpaqueCaptureDescriptorDataARM */
    /*  680 */ CommandScopeDevice  , /* vkGetShaderModuleIdentifierEXT */
    /*  681 */ CommandScopeDevice  , /* vkGetShaderModuleCreateInfoIdentifierEXT */
    /*  682 */ CommandScopeInstance, /* vkGetPhysicalDeviceOpticalFlowImageFormatsNV */
    /*  683 */ CommandScopeDevice  , /* vkCreateOpticalFlowSessionNV */
    /*  684 */ CommandScopeDevice  , /* vkDestroyOpticalFlowSessionNV */
    /*  685 */ CommandScopeDevice  , /* vkBindOpticalFlowSessionImageNV */
    /*  686 */ CommandScopeDevice  , /* vkCmdOpticalFlowExecuteNV */
    /*  687 */ CommandScopeDevice  , /* vkCmdBindIndexBuffer2KHR */
    /*  688 */ CommandScopeDevice  , /* vkGetRenderingAreaGranularityKHR */
    /*  689 */ CommandScopeDevice  , /* vkGetDeviceImageSubresourceLayoutKHR */
    /*  690 */ CommandScopeDevice  , /* vkGetImageSubresourceLayout2KHR */
    /*  691 */ CommandScopeDevice  , /* vkAntiLagUpdateAMD */
    /*  692 */ CommandScopeDevice  , /* vkWaitForPresent2KHR */
    /*  693 */ CommandScopeDevice  , /* vkCreateShadersEXT */
    /*  694 */ CommandScopeDevice  , /* vkDestroyShaderEXT */
    /*  695 */ CommandScopeDevice  , /* vkGetShaderBinaryDataEXT */
    /*  696 */ CommandScopeDevice  , /* vkCmdBindShadersEXT */
    /*  697 */ CommandScopeDevice  , /* vkCmdSetDepthClampRangeEXT */
    /*  698 */ CommandScopeDevice  , /* vkCreatePipelineBinariesKHR */
    /*  699 */ CommandScopeDevice  , /* vkDestroyPipelineBinaryKHR */
    /*  700 */ CommandScopeDevice  , /* vkGetPipelineKeyKHR */
    /*  701 */ CommandScopeDevice  , /* vkGetPipelineBinaryDataKHR */
    /*  702 */ CommandScopeDevice  , /* vkReleaseCapturedPipelineDataKHR */
    /*  703 */ CommandScopeDevice  , /* vkGetFramebufferTilePropertiesQCOM */
    /*  704 */ CommandScopeDevice  , /* vkGetDynamicRenderingTilePropertiesQCOM */
    /*  705 */ CommandScopeDevice  , /* vkReleaseSwapchainImagesKHR */
    /*  706 */ CommandScopeInstance, /* vkGetPhysicalDeviceCooperativeVectorPropertiesNV */
    /*  707 */ CommandScopeDevice  , /* vkConvertCooperativeVectorMatrixNV */
    /*  708 */ CommandScopeDevice  , /* vkCmdConvertCooperativeVectorMatrixNV */
    /*  709 */ CommandScopeDevice  , /* vkSetLatencySleepModeNV */
    /*  710 */ CommandScopeDevice  , /* vkLatencySleepNV */
    /*  711 */ CommandScopeDevice  , /* vkSetLatencyMarkerNV */
    /*  712 */ CommandScopeDevice  , /* vkGetLatencyTimingsNV */
    /*  713 */ CommandScopeDevice  , /* vkQueueNotifyOutOfBandNV */
    /*  714 */ CommandScopeInstance, /* vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR */
    /*  715 */ CommandScopeDevice  , /* vkCreateDataGraphPipelinesARM */
    /*  716 */ CommandScopeDevice  , /* vkCreateDataGraphPipelineSessionARM */
    /*  717 */ CommandScopeDevice  , /* vkGetDataGraphPipelineSessionBindPointRequirementsARM */
    /*  718 */ CommandScopeDevice  , /* vkGetDataGraphPipelineSessionMemoryRequirementsARM */
    /*  719 */ CommandScopeDevice  , /* vkBindDataGraphPipelineSessionMemoryARM */
    /*  720 */ CommandScopeDevice  , /* vkDestroyDataGraphPipelineSessionARM */
    /*  721 */ CommandScopeDevice  , /* vkCmdDispatchDataGraphARM */
    /*  722 */ CommandScopeDevice  , /* vkGetDataGraphPipelineAvailablePropertiesARM */
    /*  723 */ CommandScopeDevice  , /* vkGetDataGraphPipelinePropertiesARM */
    /*  724 */ CommandScopeInstance, /* vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM */
    /*  725 */ CommandScopeInstance, /* vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM */
    /*  726 */ CommandScopeDevice  , /* vkCmdSetAttachmentFeedbackLoopEnableEXT */
    /*  727 */ CommandScopeDevice  , /* vkGetScreenBufferPropertiesQNX */
    /*  728 */ CommandScopeDevice  , /* vkCmdSetLineStippleKHR */
    /*  729 */ CommandScopeInstance, /* vkGetPhysicalDeviceCalibrateableTimeDomainsKHR */
    /*  730 */ CommandScopeDevice  , /* vkGetCalibratedTimestampsKHR */
    /*  731 */ CommandScopeDevice  , /* vkCmdBindDescriptorSets2KHR */
    /*  732 */ CommandScopeDevice  , /* vkCmdPushConstants2KHR */
    /*  733 */ CommandScopeDevice  , /* vkCmdPushDescriptorSet2KHR */
    /*  734 */ CommandScopeDevice  , /* vkCmdPushDescriptorSetWithTemplate2KHR */
    /*  735 */ CommandScopeDevice  , /* vkCmdSetDescriptorBufferOffsets2EXT */
    /*  736 */ CommandScopeDevice  , /* vkCmdBindDescriptorBufferEmbeddedSamplers2EXT */
    /*  737 */ CommandScopeDevice  , /* vkCmdBindTileMemoryQCOM */
    /*  738 */ CommandScopeDevice  , /* vkCreateExternalComputeQueueNV */
    /*  739 */ CommandScopeDevice  , /* vkDestroyExternalComputeQueueNV */
    /*  740 */ CommandScopeInstance, /* vkGetExternalComputeQueueDataNV */
    /*  741 */ CommandScopeDevice  , /* vkGetClusterAccelerationStructureBuildSizesNV */
    /*  742 */ CommandScopeDevice  , /* vkCmdBuildClusterAccelerationStructureIndirectNV */
    /*  743 */ CommandScopeDevice  , /* vkGetPartitionedAccelerationStructuresBuildSizesNV */
    /*  744 */ CommandScopeDevice  , /* vkCmdBuildPartitionedAccelerationStructuresNV */
    /*  745 */ CommandScopeDevice  , /* vkGetGeneratedCommandsMemoryRequirementsEXT */
    /*  746 */ CommandScopeDevice  , /* vkCmdPreprocessGeneratedCommandsEXT */
    /*  747 */ CommandScopeDevice  , /* vkCmdExecuteGeneratedCommandsEXT */
    /*  748 */ CommandScopeDevice  , /* vkCreateIndirectCommandsLayoutEXT */
    /*  749 */ CommandScopeDevice  , /* vkDestroyIndirectCommandsLayoutEXT */
    /*  750 */ CommandScopeDevice  , /* vkCreateIndirectExecutionSetEXT */
    /*  751 */ CommandScopeDevice  , /* vkDestroyIndirectExecutionSetEXT */
    /*  752 */ CommandScopeDevice  , /* vkUpdateIndirectExecutionSetPipelineEXT */
    /*  753 */ CommandScopeDevice  , /* vkUpdateIndirectExecutionSetShaderEXT */
    /*  754 */ CommandScopeInstance, /* vkCreateSurfaceOHOS */
    /*  755 */ CommandScopeInstance, /* vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV */
    /*  756 */ CommandScopeDevice  , /* vkGetMemoryMetalHandleEXT */
    /*  757 */ CommandScopeDevice  , /* vkGetMemoryMetalHandlePropertiesEXT */
    /*  758 */ CommandScopeDevice  , /* vkCmdEndRendering2EXT */
};

static const GladPfnRange_t GLAD_Vulkan_feature_pfn_ranges[] = {
    /* VK_VERSION_1_0 */
    {    0,    0,  137 },

    /* VK_VERSION_1_1 */
    {    1,  137,   28 },

    /* VK_VERSION_1_2 */
    {    2,  165,   13 },

    /* VK_VERSION_1_3 */
    {    3,  178,   37 },

    /* VK_VERSION_1_4 */
    {    4,  215,   19 },
};

static const GladPfnRange_t GLAD_Vulkan_ext_pfn_ranges[] = {
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    /* VK_AMDX_shader_enqueue */
    {    1,  388,    7 },

#endif
    /* VK_AMD_anti_lag */
    {    2,  691,    1 },

    /* VK_AMD_buffer_marker */
    {    3,  451,    2 },

    /* VK_AMD_display_native_hdr */
    {    5,  475,    1 },

    /* VK_AMD_draw_indirect_count */
    {    6,  300,    2 },

    /* VK_AMD_shader_info */
    {   22,  302,    1 },

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    /* VK_ANDROID_external_memory_android_hardware_buffer */
    {   26,  386,    2 },

#endif
    /* VK_ARM_data_graph */
    {   27,  715,   11 },

    /* VK_ARM_tensors */
    {   35,  669,   11 },

    /* VK_EXT_acquire_drm_display */
    {   37,  532,    2 },

#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    /* VK_EXT_acquire_xlib_display */
    {   38,  340,    2 },

#endif
    /* VK_EXT_attachment_feedback_loop_dynamic_state */
    {   40,  726,    1 },

    /* VK_EXT_buffer_device_address */
    {   44,  482,    1 },

    /* VK_EXT_calibrated_timestamps */
    {   45,  453,    2 },

    /* VK_EXT_color_write_enable */
    {   46,  605,    1 },

    /* VK_EXT_conditional_rendering */
    {   47,  333,    2 },

    /* VK_EXT_debug_marker */
    {   50,  268,    5 },

    /* VK_EXT_debug_report */
    {   51,  265,    3 },

    /* VK_EXT_debug_utils */
    {   52,  375,   11 },

    /* VK_EXT_depth_bias_control */
    {   53,  531,    1 },

    /* VK_EXT_depth_clamp_control */
    {   54,  697,    1 },

    /* VK_EXT_descriptor_buffer */
    {   59,  557,   11 },

    /* VK_EXT_device_fault */
    {   62,  578,    1 },

    /* VK_EXT_device_generated_commands */
    {   63,  745,    9 },

    /* VK_EXT_direct_mode_display */
    {   65,  339,    1 },

#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    /* VK_EXT_directfb_surface */
    {   66,  581,    2 },

#endif
    /* VK_EXT_discard_rectangles */
    {   67,  349,    3 },

    /* VK_EXT_display_control */
    {   68,  343,    4 },

    /* VK_EXT_display_surface_counter */
    {   69,  342,    1 },

    /* VK_EXT_extended_dynamic_state */
    {   71,  497,   12 },

    /* VK_EXT_extended_dynamic_state2 */
    {   72,  598,    5 },

    /* VK_EXT_extended_dynamic_state3 */
    {   73,  638,   31 },

    /* VK_EXT_external_memory_host */
    {   76,  450,    1 },

#if defined(VK_USE_PLATFORM_METAL_EXT)
    /* VK_EXT_external_memory_metal */
    {   77,  756,    2 },

#endif
    /* VK_EXT_fragment_density_map_offset */
    {   81,  758,    1 },

#if defined(VK_USE_PLATFORM_WIN32_KHR)
    /* VK_EXT_full_screen_exclusive */
    {   84,  487,    4 },

#endif
    /* VK_EXT_hdr_metadata */
    {   88,  352,    1 },

    /* VK_EXT_headless_surface */
    {   89,  491,    1 },

    /* VK_EXT_host_image_copy */
    {   90,  517,    5 },

    /* VK_EXT_host_query_reset */
    {   91,  496,    1 },

    /* VK_EXT_image_compression_control */
    {   93,  521,    1 },

    /* VK_EXT_image_drm_format_modifier */
    {   95,  427,    1 },

    /* VK_EXT_line_rasterization */
    {  104,  495,    1 },

    /* VK_EXT_mesh_shader */
    {  109,  569,    3 },

#if defined(VK_USE_PLATFORM_METAL_EXT)
    /* VK_EXT_metal_objects */
    {  110,  550,    1 },

#endif
#if defined(VK_USE_PLATFORM_METAL_EXT)
    /* VK_EXT_metal_surface */
    {  111,  477,    1 },

#endif
    /* VK_EXT_multi_draw */
    {  112,  607,    2 },

    /* VK_EXT_opacity_micromap */
    {  117,  609,   14 },

    /* VK_EXT_pageable_device_local_memory */
    {  118,  625,    1 },

    /* VK_EXT_pipeline_properties */
    {  124,  597,    1 },

    /* VK_EXT_private_data */
    {  131,  534,    4 },

    /* VK_EXT_sample_locations */
    {  137,  395,    2 },

    /* VK_EXT_shader_module_identifier */
    {  146,  680,    2 },

    /* VK_EXT_shader_object */
    {  147,  497,   12 },
    {  147,  583,    1 },
    {  147,  598,    5 },
    {  147,  638,   31 },
    {  147,  693,    5 },

    /* VK_EXT_swapchain_maintenance1 */
    {  158,  524,    1 },

    /* VK_EXT_tooling_info */
    {  161,  483,    1 },

    /* VK_EXT_transform_feedback */
    {  162,  286,    6 },

    /* VK_EXT_validation_cache */
    {  163,  428,    4 },

    /* VK_EXT_vertex_input_dynamic_state */
    {  168,  583,    1 },

#if defined(VK_USE_PLATFORM_FUCHSIA)
    /* VK_FUCHSIA_buffer_collection */
    {  172,  588,    5 },

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
    /* VK_FUCHSIA_external_memory */
    {  173,  584,    2 },

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
    /* VK_FUCHSIA_external_semaphore */
    {  174,  586,    2 },

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
    /* VK_FUCHSIA_imagepipe_surface */
    {  175,  476,    1 },

#endif
#if defined(VK_USE_PLATFORM_GGP)
    /* VK_GGP_stream_descriptor_surface */
    {  177,  305,    1 },

#endif
    /* VK_GOOGLE_display_timing */
    {  179,  347,    2 },

    /* VK_HUAWEI_cluster_culling_shader */
    {  183,  623,    2 },

    /* VK_HUAWEI_invocation_mask */
    {  185,  595,    1 },

    /* VK_HUAWEI_subpass_shading */
    {  186,  593,    2 },

    /* VK_INTEL_performance_query */
    {  190,  466,    9 },

    /* VK_KHR_acceleration_structure */
    {  194,  400,   16 },

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    /* VK_KHR_android_surface */
    {  195,  262,    1 },

#endif
    /* VK_KHR_bind_memory2 */
    {  196,  425,    2 },

    /* VK_KHR_buffer_device_address */
    {  197,  492,    3 },

    /* VK_KHR_calibrated_timestamps */
    {  198,  729,    2 },

    /* VK_KHR_cooperative_matrix */
    {  200,  714,    1 },

    /* VK_KHR_copy_commands2 */
    {  201,  572,    6 },

    /* VK_KHR_create_renderpass2 */
    {  202,  353,    4 },

    /* VK_KHR_deferred_host_operations */
    {  204,  509,    5 },

    /* VK_KHR_descriptor_update_template */
    {  207,  332,    1 },
    {  207,  335,    3 },

    /* VK_KHR_device_group */
    {  208,  244,    4 },
    {  208,  315,    3 },

    /* VK_KHR_device_group_creation */
    {  209,  320,    1 },

    /* VK_KHR_display */
    {  210,  248,    7 },

    /* VK_KHR_display_swapchain */
    {  211,  255,    1 },

    /* VK_KHR_draw_indirect_count */
    {  212,  448,    2 },

    /* VK_KHR_dynamic_rendering */
    {  214,  303,    2 },

    /* VK_KHR_dynamic_rendering_local_read */
    {  215,  480,    2 },

    /* VK_KHR_external_fence_capabilities */
    {  217,  358,    1 },

    /* VK_KHR_external_fence_fd */
    {  218,  361,    2 },

#if defined(VK_USE_PLATFORM_WIN32_KHR)
    /* VK_KHR_external_fence_win32 */
    {  219,  359,    2 },

#endif
    /* VK_KHR_external_memory_capabilities */
    {  221,  321,    1 },

    /* VK_KHR_external_memory_fd */
    {  222,  324,    2 },

#if defined(VK_USE_PLATFORM_WIN32_KHR)
    /* VK_KHR_external_memory_win32 */
    {  223,  322,    2 },

#endif
    /* VK_KHR_external_semaphore_capabilities */
    {  225,  326,    1 },

    /* VK_KHR_external_semaphore_fd */
    {  226,  329,    2 },

#if defined(VK_USE_PLATFORM_WIN32_KHR)
    /* VK_KHR_external_semaphore_win32 */
    {  227,  327,    2 },

#endif
    /* VK_KHR_fragment_shading_rate */
    {  230,  478,    2 },

    /* VK_KHR_get_display_properties2 */
    {  231,  369,    4 },

    /* VK_KHR_get_memory_requirements2 */
    {  232,  397,    3 },

    /* VK_KHR_get_physical_device_properties2 */
    {  233,  308,    7 },

    /* VK_KHR_get_surface_capabilities2 */
    {  234,  367,    2 },

    /* VK_KHR_line_rasterization */
    {  240,  728,    1 },

    /* VK_KHR_maintenance1 */
    {  242,  319,    1 },

    /* VK_KHR_maintenance3 */
    {  244,  447,    1 },

    /* VK_KHR_maintenance4 */
    {  245,  626,    3 },

    /* VK_KHR_maintenance5 */
    {  246,  687,    4 },

    /* VK_KHR_maintenance6 */
    {  247,  731,    6 },

    /* VK_KHR_map_memory2 */
    {  251,  522,    2 },

    /* VK_KHR_performance_query */
    {  253,  363,    4 },

    /* VK_KHR_pipeline_binary */
    {  254,  698,    5 },

    /* VK_KHR_pipeline_executable_properties */
    {  255,  514,    3 },

    /* VK_KHR_present_wait */
    {  262,  484,    1 },

    /* VK_KHR_present_wait2 */
    {  263,  692,    1 },

    /* VK_KHR_push_descriptor */
    {  264,  331,    2 },

    /* VK_KHR_ray_tracing_maintenance1 */
    {  266,  606,    1 },

    /* VK_KHR_ray_tracing_pipeline */
    {  267,  416,    7 },

    /* VK_KHR_sampler_ycbcr_conversion */
    {  272,  423,    2 },

    /* VK_KHR_shared_presentable_image */
    {  292,  357,    1 },

    /* VK_KHR_surface */
    {  295,  234,    5 },

    /* VK_KHR_swapchain */
    {  298,  239,    9 },

    /* VK_KHR_swapchain_maintenance1 */
    {  299,  705,    1 },

    /* VK_KHR_synchronization2 */
    {  301,  551,    6 },

    /* VK_KHR_timeline_semaphore */
    {  302,  463,    3 },

    /* VK_KHR_video_decode_queue */
    {  310,  285,    1 },

    /* VK_KHR_video_encode_queue */
    {  317,  538,    3 },

    /* VK_KHR_video_queue */
    {  320,  273,   12 },

#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    /* VK_KHR_wayland_surface */
    {  322,  260,    2 },

#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    /* VK_KHR_win32_surface */
    {  324,  263,    2 },

#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
    /* VK_KHR_xcb_surface */
    {  326,  258,    2 },

#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    /* VK_KHR_xlib_surface */
    {  327,  256,    2 },

#endif
#if defined(VK_USE_PLATFORM_IOS_MVK)
    /* VK_MVK_ios_surface */
    {  332,  373,    1 },

#endif
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    /* VK_MVK_macos_surface */
    {  333,  374,    1 },

#endif
#if defined(VK_USE_PLATFORM_VI_NN)
    /* VK_NN_vi_surface */
    {  334,  318,    1 },

#endif
    /* VK_NVX_binary_import */
    {  335,  292,    5 },

    /* VK_NVX_image_view_handle */
    {  336,  297,    3 },

#if defined(VK_USE_PLATFORM_WIN32_KHR)
    /* VK_NV_acquire_winrt_display */
    {  338,  579,    2 },

#endif
    /* VK_NV_clip_space_w_scaling */
    {  339,  338,    1 },

    /* VK_NV_cluster_acceleration_structure */
    {  340,  741,    2 },

    /* VK_NV_cooperative_matrix */
    {  343,  485,    1 },

    /* VK_NV_cooperative_matrix2 */
    {  344,  755,    1 },

    /* VK_NV_cooperative_vector */
    {  345,  706,    3 },

    /* VK_NV_copy_memory_indirect */
    {  346,  631,    2 },

    /* VK_NV_coverage_reduction_mode */
    {  348,  486,    1 },

#if defined(VK_ENABLE_BETA_EXTENSIONS)
    /* VK_NV_cuda_kernel_launch */
    {  349,  541,    6 },

#endif
    /* VK_NV_device_diagnostic_checkpoints */
    {  353,  460,    3 },

    /* VK_NV_device_generated_commands */
    {  355,  525,    6 },

    /* VK_NV_device_generated_commands_compute */
    {  356,  635,    3 },

    /* VK_NV_external_compute_queue */
    {  360,  738,    3 },

    /* VK_NV_external_memory_capabilities */
    {  362,  306,    1 },

    /* VK_NV_external_memory_rdma */
    {  363,  596,    1 },

#if defined(VK_USE_PLATFORM_WIN32_KHR)
    /* VK_NV_external_memory_win32 */
    {  364,  307,    1 },

#endif
    /* VK_NV_fragment_shading_rate_enums */
    {  368,  568,    1 },

    /* VK_NV_low_latency2 */
    {  375,  709,    5 },

    /* VK_NV_memory_decompression */
    {  376,  633,    2 },

    /* VK_NV_mesh_shader */
    {  377,  455,    3 },

    /* VK_NV_optical_flow */
    {  378,  682,    5 },

    /* VK_NV_partitioned_acceleration_structure */
    {  379,  743,    2 },

    /* VK_NV_ray_tracing */
    {  384,  435,   12 },

    /* VK_NV_scissor_exclusive */
    {  391,  458,    2 },

    /* VK_NV_shading_rate_image */
    {  396,  432,    3 },

#if defined(VK_USE_PLATFORM_OHOS)
    /* VK_OHOS_surface */
    {  400,  754,    1 },

#endif
    /* VK_QCOM_tile_memory_heap */
    {  412,  737,    1 },

    /* VK_QCOM_tile_properties */
    {  413,  703,    2 },

    /* VK_QCOM_tile_shading */
    {  414,  547,    3 },

#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    /* VK_QNX_external_memory_screen_buffer */
    {  416,  727,    1 },

#endif
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    /* VK_QNX_screen_surface */
    {  417,  603,    2 },

#endif
    /* VK_VALVE_descriptor_set_host_mapping */
    {  420,  629,    2 },
};

static const uint64_t GLAD_Vulkan_ext_hashes[] = {
    /*    0 */ 0x6aba9e60325e43c3ULL, /* VK_AMDX_dense_geometry_format */
    /*    1 */ 0x6ae42d438bb0484cULL, /* VK_AMDX_shader_enqueue */
    /*    2 */ 0x141bdaf54e241180ULL, /* VK_AMD_anti_lag */
    /*    3 */ 0x65ac43ace7243e04ULL, /* VK_AMD_buffer_marker */
    /*    4 */ 0x8353850f5238ee1dULL, /* VK_AMD_device_coherent_memory */
    /*    5 */ 0x7f6d3eb981ed905aULL, /* VK_AMD_display_native_hdr */
    /*    6 */ 0x0b55dbb0df76886cULL, /* VK_AMD_draw_indirect_count */
    /*    7 */ 0xf3c87297143cbd5aULL, /* VK_AMD_gcn_shader */
    /*    8 */ 0xd16896d602d6c016ULL, /* VK_AMD_gpu_shader_half_float */
    /*    9 */ 0x80dbf6d9994a8486ULL, /* VK_AMD_gpu_shader_int16 */
    /*   10 */ 0x777abeda8eb885f2ULL, /* VK_AMD_memory_overallocation_behavior */
    /*   11 */ 0x09abd53b962f7221ULL, /* VK_AMD_mixed_attachment_samples */
    /*   12 */ 0x9f9cc0f84d49fc24ULL, /* VK_AMD_negative_viewport_height */
    /*   13 */ 0xc4fcbc5045e4b55dULL, /* VK_AMD_pipeline_compiler_control */
    /*   14 */ 0x2b4b03257b517fe7ULL, /* VK_AMD_rasterization_order */
    /*   15 */ 0x253e959bcd5e01e9ULL, /* VK_AMD_shader_ballot */
    /*   16 */ 0x4cb3d15508759039ULL, /* VK_AMD_shader_core_properties */
    /*   17 */ 0xe9de3bafe3e1e19aULL, /* VK_AMD_shader_core_properties2 */
    /*   18 */ 0xb9e9755d0b011c3fULL, /* VK_AMD_shader_early_and_late_fragment_tests */
    /*   19 */ 0x9564cc2b0038b597ULL, /* VK_AMD_shader_explicit_vertex_parameter */
    /*   20 */ 0x2d734d0c4158eb7eULL, /* VK_AMD_shader_fragment_mask */
    /*   21 */ 0x1fd2270dcd52ad73ULL, /* VK_AMD_shader_image_load_store_lod */
    /*   22 */ 0x62011d43d2d97594ULL, /* VK_AMD_shader_info */
    /*   23 */ 0x48ef51e9f522215bULL, /* VK_AMD_shader_trinary_minmax */
    /*   24 */ 0x7e011534e1db7838ULL, /* VK_AMD_texture_gather_bias_lod */
    /*   25 */ 0xee13e9584a79a866ULL, /* VK_ANDROID_external_format_resolve */
    /*   26 */ 0x0efa9218af4eedaaULL, /* VK_ANDROID_external_memory_android_hardware_buffer */
    /*   27 */ 0x74a1ed3ccf91f30bULL, /* VK_ARM_data_graph */
    /*   28 */ 0x06411aa4c0bddda8ULL, /* VK_ARM_format_pack */
    /*   29 */ 0x0f753497d22c514bULL, /* VK_ARM_pipeline_opacity_micromap */
    /*   30 */ 0x0afcd59fd2af6286ULL, /* VK_ARM_rasterization_order_attachment_access */
    /*   31 */ 0x099508890a72c586ULL, /* VK_ARM_render_pass_striped */
    /*   32 */ 0xcb5ebd8b3c00874cULL, /* VK_ARM_scheduling_controls */
    /*   33 */ 0x6d66a5a00c62648dULL, /* VK_ARM_shader_core_builtins */
    /*   34 */ 0x42f58e0f0c034d62ULL, /* VK_ARM_shader_core_properties */
    /*   35 */ 0xdda32da4e6cb55beULL, /* VK_ARM_tensors */
    /*   36 */ 0x9452c6992583027bULL, /* VK_EXT_4444_formats */
    /*   37 */ 0xc78e4b8ee4076491ULL, /* VK_EXT_acquire_drm_display */
    /*   38 */ 0xf320bc0da89095ccULL, /* VK_EXT_acquire_xlib_display */
    /*   39 */ 0x1f2679f2f103d431ULL, /* VK_EXT_astc_decode_mode */
    /*   40 */ 0xf27c39b3a1b079adULL, /* VK_EXT_attachment_feedback_loop_dynamic_state */
    /*   41 */ 0x74d9e22c0880d05bULL, /* VK_EXT_attachment_feedback_loop_layout */
    /*   42 */ 0xbf40b1c2e2a175caULL, /* VK_EXT_blend_operation_advanced */
    /*   43 */ 0xa7ae01d75b03a5faULL, /* VK_EXT_border_color_swizzle */
    /*   44 */ 0x8cadd6ee8baeb7b6ULL, /* VK_EXT_buffer_device_address */
    /*   45 */ 0xe53030d618c508b9ULL, /* VK_EXT_calibrated_timestamps */
    /*   46 */ 0x1821c534e43e8bc2ULL, /* VK_EXT_color_write_enable */
    /*   47 */ 0x3acaa19dcdfa4838ULL, /* VK_EXT_conditional_rendering */
    /*   48 */ 0xbc479489c58aba55ULL, /* VK_EXT_conservative_rasterization */
    /*   49 */ 0xd41fdd03d1591c42ULL, /* VK_EXT_custom_border_color */
    /*   50 */ 0x13dd727d73e5c438ULL, /* VK_EXT_debug_marker */
    /*   51 */ 0xefc5d6f86f5274aaULL, /* VK_EXT_debug_report */
    /*   52 */ 0x1f4cc1384fdd3124ULL, /* VK_EXT_debug_utils */
    /*   53 */ 0x4334a6b5b2a8bcdfULL, /* VK_EXT_depth_bias_control */
    /*   54 */ 0x20b2ee75c46fae3bULL, /* VK_EXT_depth_clamp_control */
    /*   55 */ 0x42e03d02e07ee602ULL, /* VK_EXT_depth_clamp_zero_one */
    /*   56 */ 0xc46ca287fec7bfa2ULL, /* VK_EXT_depth_clip_control */
    /*   57 */ 0xb225ae836596c941ULL, /* VK_EXT_depth_clip_enable */
    /*   58 */ 0x683e05b7c95cf871ULL, /* VK_EXT_depth_range_unrestricted */
    /*   59 */ 0xff983b309bdf4f8fULL, /* VK_EXT_descriptor_buffer */
    /*   60 */ 0x8ed9a50d9652d13aULL, /* VK_EXT_descriptor_indexing */
    /*   61 */ 0x71042286279bf266ULL, /* VK_EXT_device_address_binding_report */
    /*   62 */ 0x44712682d623c6ecULL, /* VK_EXT_device_fault */
    /*   63 */ 0x6c42eb1e4c30ed48ULL, /* VK_EXT_device_generated_commands */
    /*   64 */ 0xfc8708a7a55a3b72ULL, /* VK_EXT_device_memory_report */
    /*   65 */ 0x3d21adc07dc92de9ULL, /* VK_EXT_direct_mode_display */
    /*   66 */ 0x2f377620d96a0b95ULL, /* VK_EXT_directfb_surface */
    /*   67 */ 0x6c4b18b294f729e9ULL, /* VK_EXT_discard_rectangles */
    /*   68 */ 0x2bd79b14ec35b405ULL, /* VK_EXT_display_control */
    /*   69 */ 0xf82da0558a082445ULL, /* VK_EXT_display_surface_counter */
    /*   70 */ 0x6c84fccd28668412ULL, /* VK_EXT_dynamic_rendering_unused_attachments */
    /*   71 */ 0x405b3a7704a014a0ULL, /* VK_EXT_extended_dynamic_state */
    /*   72 */ 0x09050069bac4e50bULL, /* VK_EXT_extended_dynamic_state2 */
    /*   73 */ 0x3e6696389e531962ULL, /* VK_EXT_extended_dynamic_state3 */
    /*   74 */ 0x204d4d8537dc240cULL, /* VK_EXT_external_memory_acquire_unmodified */
    /*   75 */ 0xfbe83be92d0dc3e1ULL, /* VK_EXT_external_memory_dma_buf */
    /*   76 */ 0xe730e90349447245ULL, /* VK_EXT_external_memory_host */
    /*   77 */ 0xbb6a5bdb9f4339b2ULL, /* VK_EXT_external_memory_metal */
    /*   78 */ 0x2ff4c771bf02a660ULL, /* VK_EXT_filter_cubic */
    /*   79 */ 0xdd63dbab93498a89ULL, /* VK_EXT_fragment_density_map */
    /*   80 */ 0x639aaec72634d6ccULL, /* VK_EXT_fragment_density_map2 */
    /*   81 */ 0x50ea79c84acba293ULL, /* VK_EXT_fragment_density_map_offset */
    /*   82 */ 0xec38db4912e9aa39ULL, /* VK_EXT_fragment_shader_interlock */
    /*   83 */ 0x4bed293561f471c5ULL, /* VK_EXT_frame_boundary */
    /*   84 */ 0xf888a39f24346db4ULL, /* VK_EXT_full_screen_exclusive */
    /*   85 */ 0x026fba6d706537f5ULL, /* VK_EXT_global_priority */
    /*   86 */ 0x49240b90779ad742ULL, /* VK_EXT_global_priority_query */
    /*   87 */ 0xe612048b33a20737ULL, /* VK_EXT_graphics_pipeline_library */
    /*   88 */ 0xd140703366300180ULL, /* VK_EXT_hdr_metadata */
    /*   89 */ 0xfc97df8c7f5cb62eULL, /* VK_EXT_headless_surface */
    /*   90 */ 0x15c6d3b4db750060ULL, /* VK_EXT_host_image_copy */
    /*   91 */ 0xcc9a1964d5f92eadULL, /* VK_EXT_host_query_reset */
    /*   92 */ 0x992053b93ca7369aULL, /* VK_EXT_image_2d_view_of_3d */
    /*   93 */ 0xac673544b231a330ULL, /* VK_EXT_image_compression_control */
    /*   94 */ 0xfc267e5b08be3c88ULL, /* VK_EXT_image_compression_control_swapchain */
    /*   95 */ 0x5d78e7153c62776cULL, /* VK_EXT_image_drm_format_modifier */
    /*   96 */ 0xe918548d9d09bdf5ULL, /* VK_EXT_image_robustness */
    /*   97 */ 0x10ea5ce8b7b462c6ULL, /* VK_EXT_image_sliced_view_of_3d */
    /*   98 */ 0x5d125c6144d30072ULL, /* VK_EXT_image_view_min_lod */
    /*   99 */ 0x66bb737b7652d71dULL, /* VK_EXT_index_type_uint8 */
    /*  100 */ 0x59f61f1cc23145eeULL, /* VK_EXT_inline_uniform_block */
    /*  101 */ 0x9ba2edc52691fc07ULL, /* VK_EXT_layer_settings */
    /*  102 */ 0xa45ec0ff789f2882ULL, /* VK_EXT_legacy_dithering */
    /*  103 */ 0x93eebd73e097d983ULL, /* VK_EXT_legacy_vertex_attributes */
    /*  104 */ 0x98daf38a4cd796bcULL, /* VK_EXT_line_rasterization */
    /*  105 */ 0xca3cb4186d57fa40ULL, /* VK_EXT_load_store_op_none */
    /*  106 */ 0xc92882ba73a7ad8aULL, /* VK_EXT_map_memory_placed */
    /*  107 */ 0xa642b55c0f467f26ULL, /* VK_EXT_memory_budget */
    /*  108 */ 0xdf03e1a0a38154d2ULL, /* VK_EXT_memory_priority */
    /*  109 */ 0x38a2a90e0a820189ULL, /* VK_EXT_mesh_shader */
    /*  110 */ 0x6bcff1cd8cf418f2ULL, /* VK_EXT_metal_objects */
    /*  111 */ 0x60fc707b7c19679cULL, /* VK_EXT_metal_surface */
    /*  112 */ 0x60ca462964877ba5ULL, /* VK_EXT_multi_draw */
    /*  113 */ 0x60c608294e99436fULL, /* VK_EXT_multisampled_render_to_single_sampled */
    /*  114 */ 0x333da01be07c65e4ULL, /* VK_EXT_mutable_descriptor_type */
    /*  115 */ 0x4f43f294a30fc75dULL, /* VK_EXT_nested_command_buffer */
    /*  116 */ 0x6cf77b70db09b037ULL, /* VK_EXT_non_seamless_cube_map */
    /*  117 */ 0xb5bdb97dc49555efULL, /* VK_EXT_opacity_micromap */
    /*  118 */ 0x74062e5990db1eebULL, /* VK_EXT_pageable_device_local_memory */
    /*  119 */ 0xe60ea5fa872ffa4bULL, /* VK_EXT_pci_bus_info */
    /*  120 */ 0x087b96c0fac7f2e9ULL, /* VK_EXT_physical_device_drm */
    /*  121 */ 0xae186881e629f533ULL, /* VK_EXT_pipeline_creation_cache_control */
    /*  122 */ 0xd5ed321620183ae4ULL, /* VK_EXT_pipeline_creation_feedback */
    /*  123 */ 0xf2497807f1195d03ULL, /* VK_EXT_pipeline_library_group_handles */
    /*  124 */ 0x97816799b0ea2a08ULL, /* VK_EXT_pipeline_properties */
    /*  125 */ 0x0bec2c70abec6edfULL, /* VK_EXT_pipeline_protected_access */
    /*  126 */ 0x3726d3c286b23305ULL, /* VK_EXT_pipeline_robustness */
    /*  127 */ 0x578e2a9cdc320baaULL, /* VK_EXT_post_depth_coverage */
    /*  128 */ 0xdad3977856dd3ce4ULL, /* VK_EXT_present_mode_fifo_latest_ready */
    /*  129 */ 0x4792bf3539da07a0ULL, /* VK_EXT_primitive_topology_list_restart */
    /*  130 */ 0x4de3fc9eb140d3c9ULL, /* VK_EXT_primitives_generated_query */
    /*  131 */ 0x66832604ff1fb25aULL, /* VK_EXT_private_data */
    /*  132 */ 0x3632448643e01277ULL, /* VK_EXT_provoking_vertex */
    /*  133 */ 0xc3a80f57bc34acf0ULL, /* VK_EXT_queue_family_foreign */
    /*  134 */ 0x9c47749ad3103e99ULL, /* VK_EXT_rasterization_order_attachment_access */
    /*  135 */ 0xe3b61ff718cac048ULL, /* VK_EXT_rgba10x6_formats */
    /*  136 */ 0x267337703fbb9802ULL, /* VK_EXT_robustness2 */
    /*  137 */ 0xa2f0c46d62bffbbdULL, /* VK_EXT_sample_locations */
    /*  138 */ 0x35bc8d45855c9dddULL, /* VK_EXT_sampler_filter_minmax */
    /*  139 */ 0x0fe7c2504b67f76eULL, /* VK_EXT_scalar_block_layout */
    /*  140 */ 0x21c315365bdd91c1ULL, /* VK_EXT_separate_stencil_usage */
    /*  141 */ 0x39152af17d406387ULL, /* VK_EXT_shader_atomic_float */
    /*  142 */ 0xfa5bf73b09f1814aULL, /* VK_EXT_shader_atomic_float2 */
    /*  143 */ 0x1313743aff740ea6ULL, /* VK_EXT_shader_demote_to_helper_invocation */
    /*  144 */ 0xf791a964511a9452ULL, /* VK_EXT_shader_float8 */
    /*  145 */ 0xdbd208469e466661ULL, /* VK_EXT_shader_image_atomic_int64 */
    /*  146 */ 0x0fdb11284e798630ULL, /* VK_EXT_shader_module_identifier */
    /*  147 */ 0x01d57626cc2cb88bULL, /* VK_EXT_shader_object */
    /*  148 */ 0xd98565c5e8cff707ULL, /* VK_EXT_shader_replicated_composites */
    /*  149 */ 0x1d5f02c289908dc6ULL, /* VK_EXT_shader_stencil_export */
    /*  150 */ 0x3434e0e3856c3974ULL, /* VK_EXT_shader_subgroup_ballot */
    /*  151 */ 0x414fe291cad1b8c2ULL, /* VK_EXT_shader_subgroup_vote */
    /*  152 */ 0x15c81e1e3330c87aULL, /* VK_EXT_shader_tile_image */
    /*  153 */ 0x3ab7ae29a67149aaULL, /* VK_EXT_shader_viewport_index_layer */
    /*  154 */ 0xf8847bcd6077bcfcULL, /* VK_EXT_subgroup_size_control */
    /*  155 */ 0xc0a98929a3b5a629ULL, /* VK_EXT_subpass_merge_feedback */
    /*  156 */ 0x745c764090230a6aULL, /* VK_EXT_surface_maintenance1 */
    /*  157 */ 0xaf7db52f12522284ULL, /* VK_EXT_swapchain_colorspace */
    /*  158 */ 0xb8a530fd9b6e7826ULL, /* VK_EXT_swapchain_maintenance1 */
    /*  159 */ 0x93820a855076e9baULL, /* VK_EXT_texel_buffer_alignment */
    /*  160 */ 0xd54a2906947894c3ULL, /* VK_EXT_texture_compression_astc_hdr */
    /*  161 */ 0xa176a37fe21bf722ULL, /* VK_EXT_tooling_info */
    /*  162 */ 0x2c77e64693cba64bULL, /* VK_EXT_transform_feedback */
    /*  163 */ 0xd43b5b3257938a0cULL, /* VK_EXT_validation_cache */
    /*  164 */ 0x32e3bcc79655ff35ULL, /* VK_EXT_validation_features */
    /*  165 */ 0x5dbef52d8325ef00ULL, /* VK_EXT_validation_flags */
    /*  166 */ 0x41bd31eed71de48dULL, /* VK_EXT_vertex_attribute_divisor */
    /*  167 */ 0x384a29f8cf6d87bfULL, /* VK_EXT_vertex_attribute_robustness */
    /*  168 */ 0xdba593667f2b15d8ULL, /* VK_EXT_vertex_input_dynamic_state */
    /*  169 */ 0xdc68cb4b50c6a206ULL, /* VK_EXT_ycbcr_2plane_444_formats */
    /*  170 */ 0x7f0e4b169ce6683eULL, /* VK_EXT_ycbcr_image_arrays */
    /*  171 */ 0x1d23436dd19b0471ULL, /* VK_EXT_zero_initialize_device_memory */
    /*  172 */ 0x4ad21727cd459ae0ULL, /* VK_FUCHSIA_buffer_collection */
    /*  173 */ 0x39a61a1dde950a7eULL, /* VK_FUCHSIA_external_memory */
    /*  174 */ 0xf64c61e8709735f7ULL, /* VK_FUCHSIA_external_semaphore */
    /*  175 */ 0x78bbdf52d016b408ULL, /* VK_FUCHSIA_imagepipe_surface */
    /*  176 */ 0x7f2da9be6e1b04dbULL, /* VK_GGP_frame_token */
    /*  177 */ 0xcd04d110dd619891ULL, /* VK_GGP_stream_descriptor_surface */
    /*  178 */ 0x66d124637ca67c9bULL, /* VK_GOOGLE_decorate_string */
    /*  179 */ 0xd317975f41d1a234ULL, /* VK_GOOGLE_display_timing */
    /*  180 */ 0x434a8c02c305c9d2ULL, /* VK_GOOGLE_hlsl_functionality1 */
    /*  181 */ 0xdb384c83fb23b324ULL, /* VK_GOOGLE_surfaceless_query */
    /*  182 */ 0x8ea5be2adce92628ULL, /* VK_GOOGLE_user_type */
    /*  183 */ 0x1251619c17f44f75ULL, /* VK_HUAWEI_cluster_culling_shader */
    /*  184 */ 0x734dc9a82ce2a812ULL, /* VK_HUAWEI_hdr_vivid */
    /*  185 */ 0x23cb6d9b631ae3deULL, /* VK_HUAWEI_invocation_mask */
    /*  186 */ 0x7a080c6eb36cfa62ULL, /* VK_HUAWEI_subpass_shading */
    /*  187 */ 0xc831730562583c7fULL, /* VK_IMG_filter_cubic */
    /*  188 */ 0x2770027508eb9598ULL, /* VK_IMG_format_pvrtc */
    /*  189 */ 0xb0257135e659f035ULL, /* VK_IMG_relaxed_line_rasterization */
    /*  190 */ 0xde48a4b9c28f1a76ULL, /* VK_INTEL_performance_query */
    /*  191 */ 0x1cdbef97960a8e84ULL, /* VK_INTEL_shader_integer_functions2 */
    /*  192 */ 0x8febc131b31f03a7ULL, /* VK_KHR_16bit_storage */
    /*  193 */ 0xfc675d0c9be11933ULL, /* VK_KHR_8bit_storage */
    /*  194 */ 0xfd487833d05a912eULL, /* VK_KHR_acceleration_structure */
    /*  195 */ 0x29df4e2582c4e5ebULL, /* VK_KHR_android_surface */
    /*  196 */ 0xc441ac340c33f00eULL, /* VK_KHR_bind_memory2 */
    /*  197 */ 0xed3998734610578eULL, /* VK_KHR_buffer_device_address */
    /*  198 */ 0xf6b15d82867a4cc7ULL, /* VK_KHR_calibrated_timestamps */
    /*  199 */ 0x0afe9b38bfc3ce2cULL, /* VK_KHR_compute_shader_derivatives */
    /*  200 */ 0x2349bf032cef96dfULL, /* VK_KHR_cooperative_matrix */
    /*  201 */ 0x8037af99654ff021ULL, /* VK_KHR_copy_commands2 */
    /*  202 */ 0x45e78547df004126ULL, /* VK_KHR_create_renderpass2 */
    /*  203 */ 0x78b51eb267ba222aULL, /* VK_KHR_dedicated_allocation */
    /*  204 */ 0x94de08b35a6241caULL, /* VK_KHR_deferred_host_operations */
    /*  205 */ 0xc379ca87fcbfe646ULL, /* VK_KHR_depth_clamp_zero_one */
    /*  206 */ 0x8c49a14f4e053827ULL, /* VK_KHR_depth_stencil_resolve */
    /*  207 */ 0xd0e490f381b744beULL, /* VK_KHR_descriptor_update_template */
    /*  208 */ 0xc6ca78c5b314bc87ULL, /* VK_KHR_device_group */
    /*  209 */ 0x8585cbd14f1c0cacULL, /* VK_KHR_device_group_creation */
    /*  210 */ 0x2859d74f3639d0b1ULL, /* VK_KHR_display */
    /*  211 */ 0xe6851c4675917263ULL, /* VK_KHR_display_swapchain */
    /*  212 */ 0x0337556153ae8299ULL, /* VK_KHR_draw_indirect_count */
    /*  213 */ 0x2fa1beee71b55c4aULL, /* VK_KHR_driver_properties */
    /*  214 */ 0xcec518255e3db5bdULL, /* VK_KHR_dynamic_rendering */
    /*  215 */ 0x3aff0fddef25484aULL, /* VK_KHR_dynamic_rendering_local_read */
    /*  216 */ 0x042831872b90006cULL, /* VK_KHR_external_fence */
    /*  217 */ 0x5f78dae679457682ULL, /* VK_KHR_external_fence_capabilities */
    /*  218 */ 0xcd3a8c2ddf5addf6ULL, /* VK_KHR_external_fence_fd */
    /*  219 */ 0x4c03e948c552a900ULL, /* VK_KHR_external_fence_win32 */
    /*  220 */ 0x87d94faee5024129ULL, /* VK_KHR_external_memory */
    /*  221 */ 0x3f3f36a8f61bdd88ULL, /* VK_KHR_external_memory_capabilities */
    /*  222 */ 0x552d385fc1022139ULL, /* VK_KHR_external_memory_fd */
    /*  223 */ 0x92cd58bc47a696d9ULL, /* VK_KHR_external_memory_win32 */
    /*  224 */ 0x7e7e947a025884c1ULL, /* VK_KHR_external_semaphore */
    /*  225 */ 0xb7268870e382881bULL, /* VK_KHR_external_semaphore_capabilities */
    /*  226 */ 0x089c9b49df8b6f1eULL, /* VK_KHR_external_semaphore_fd */
    /*  227 */ 0x014c9621dbd33d31ULL, /* VK_KHR_external_semaphore_win32 */
    /*  228 */ 0x9310a82971542c4aULL, /* VK_KHR_format_feature_flags2 */
    /*  229 */ 0x2aedf5bc87e7dd6dULL, /* VK_KHR_fragment_shader_barycentric */
    /*  230 */ 0x8496cee01f4fa6d5ULL, /* VK_KHR_fragment_shading_rate */
    /*  231 */ 0x6c023bc9dc523d46ULL, /* VK_KHR_get_display_properties2 */
    /*  232 */ 0x9eb7bb6c3705f946ULL, /* VK_KHR_get_memory_requirements2 */
    /*  233 */ 0x7685eeed9cac9798ULL, /* VK_KHR_get_physical_device_properties2 */
    /*  234 */ 0x9b0fbb8eeee0e74bULL, /* VK_KHR_get_surface_capabilities2 */
    /*  235 */ 0x0bb91b137617fbefULL, /* VK_KHR_global_priority */
    /*  236 */ 0xfb7c493b280e7035ULL, /* VK_KHR_image_format_list */
    /*  237 */ 0x6ba09c8a87af68ceULL, /* VK_KHR_imageless_framebuffer */
    /*  238 */ 0x76a0d6d17ae91b81ULL, /* VK_KHR_incremental_present */
    /*  239 */ 0x3dde8d8eb0b76315ULL, /* VK_KHR_index_type_uint8 */
    /*  240 */ 0x7928ca2523362ef3ULL, /* VK_KHR_line_rasterization */
    /*  241 */ 0xc8692b97cfbe45adULL, /* VK_KHR_load_store_op_none */
    /*  242 */ 0xe3c8335cc1581a67ULL, /* VK_KHR_maintenance1 */
    /*  243 */ 0x8ffe792f51cd1450ULL, /* VK_KHR_maintenance2 */
    /*  244 */ 0xea219cc76502a8afULL, /* VK_KHR_maintenance3 */
    /*  245 */ 0xa66e463f036dae4aULL, /* VK_KHR_maintenance4 */
    /*  246 */ 0xc5e86b535cee6698ULL, /* VK_KHR_maintenance5 */
    /*  247 */ 0xf60b7de240a15ab4ULL, /* VK_KHR_maintenance6 */
    /*  248 */ 0x3d59040ce3c13f21ULL, /* VK_KHR_maintenance7 */
    /*  249 */ 0xb6892d36c521b488ULL, /* VK_KHR_maintenance8 */
    /*  250 */ 0xbc9d8954b3903237ULL, /* VK_KHR_maintenance9 */
    /*  251 */ 0x64d252cf56a64addULL, /* VK_KHR_map_memory2 */
    /*  252 */ 0x5af12378bc6d7169ULL, /* VK_KHR_multiview */
    /*  253 */ 0x1bb74dfe8d7e0b31ULL, /* VK_KHR_performance_query */
    /*  254 */ 0x935d834a6c18d3edULL, /* VK_KHR_pipeline_binary */
    /*  255 */ 0x91248c6b162c4180ULL, /* VK_KHR_pipeline_executable_properties */
    /*  256 */ 0x039c65d87fb09ca9ULL, /* VK_KHR_pipeline_library */
    /*  257 */ 0x28644eeb112058b6ULL, /* VK_KHR_portability_enumeration */
    /*  258 */ 0xac06576b97f9486aULL, /* VK_KHR_portability_subset */
    /*  259 */ 0xe82e301141092b1eULL, /* VK_KHR_present_id */
    /*  260 */ 0x209717f94a827c5fULL, /* VK_KHR_present_id2 */
    /*  261 */ 0x9ebcb805ef6af243ULL, /* VK_KHR_present_mode_fifo_latest_ready */
    /*  262 */ 0x47954f24ddf5185eULL, /* VK_KHR_present_wait */
    /*  263 */ 0x2822277cba1268a0ULL, /* VK_KHR_present_wait2 */
    /*  264 */ 0x2123bacd888c07ecULL, /* VK_KHR_push_descriptor */
    /*  265 */ 0x8bf873804879f2cfULL, /* VK_KHR_ray_query */
    /*  266 */ 0x9df3df162357e4b0ULL, /* VK_KHR_ray_tracing_maintenance1 */
    /*  267 */ 0xaef707cb154a81afULL, /* VK_KHR_ray_tracing_pipeline */
    /*  268 */ 0x697f77ef7ba14203ULL, /* VK_KHR_ray_tracing_position_fetch */
    /*  269 */ 0x4b17e19fd947a1d3ULL, /* VK_KHR_relaxed_block_layout */
    /*  270 */ 0xaab0786abb72567aULL, /* VK_KHR_robustness2 */
    /*  271 */ 0x5d5e936103817cdaULL, /* VK_KHR_sampler_mirror_clamp_to_edge */
    /*  272 */ 0x22004cfa79ba7177ULL, /* VK_KHR_sampler_ycbcr_conversion */
    /*  273 */ 0xba2c0ae86fd11630ULL, /* VK_KHR_separate_depth_stencil_layouts */
    /*  274 */ 0xb16f5fd69d97f3a1ULL, /* VK_KHR_shader_atomic_int64 */
    /*  275 */ 0xd49205e9c445114aULL, /* VK_KHR_shader_bfloat16 */
    /*  276 */ 0xeee9708671fa7c77ULL, /* VK_KHR_shader_clock */
    /*  277 */ 0xb35fc4bdb32f3d81ULL, /* VK_KHR_shader_draw_parameters */
    /*  278 */ 0xab0eda6676f1fd31ULL, /* VK_KHR_shader_expect_assume */
    /*  279 */ 0x4dad563cb513c7c9ULL, /* VK_KHR_shader_float16_int8 */
    /*  280 */ 0x548b20a76c855b46ULL, /* VK_KHR_shader_float_controls */
    /*  281 */ 0xa1150eef92f851e8ULL, /* VK_KHR_shader_float_controls2 */
    /*  282 */ 0x9d14cd5379daf7cbULL, /* VK_KHR_shader_integer_dot_product */
    /*  283 */ 0x42aefa5598fde4abULL, /* VK_KHR_shader_maximal_reconvergence */
    /*  284 */ 0xb38332d7467f8474ULL, /* VK_KHR_shader_non_semantic_info */
    /*  285 */ 0xab3f0af6d5504bf4ULL, /* VK_KHR_shader_quad_control */
    /*  286 */ 0x1bdfe042874be24fULL, /* VK_KHR_shader_relaxed_extended_instruction */
    /*  287 */ 0xcda588b0d067d48fULL, /* VK_KHR_shader_subgroup_extended_types */
    /*  288 */ 0xd0836c7a4d04b579ULL, /* VK_KHR_shader_subgroup_rotate */
    /*  289 */ 0x64fbf5bc74afe199ULL, /* VK_KHR_shader_subgroup_uniform_control_flow */
    /*  290 */ 0x6e5fde40560b40a9ULL, /* VK_KHR_shader_terminate_invocation */
    /*  291 */ 0x9264c3e61ed27e2fULL, /* VK_KHR_shader_untyped_pointers */
    /*  292 */ 0x7e6871b03dee137bULL, /* VK_KHR_shared_presentable_image */
    /*  293 */ 0x06c03c1c3db9815dULL, /* VK_KHR_spirv_1_4 */
    /*  294 */ 0x743f86c26df32ea2ULL, /* VK_KHR_storage_buffer_storage_class */
    /*  295 */ 0x2c4f009293a35548ULL, /* VK_KHR_surface */
    /*  296 */ 0x2447a025c1b4d0ffULL, /* VK_KHR_surface_maintenance1 */
    /*  297 */ 0xa8506d9aef558591ULL, /* VK_KHR_surface_protected_capabilities */
    /*  298 */ 0x6cefabf4c944ccecULL, /* VK_KHR_swapchain */
    /*  299 */ 0x8d650abfe09cadb2ULL, /* VK_KHR_swapchain_maintenance1 */
    /*  300 */ 0x2149e839e759e400ULL, /* VK_KHR_swapchain_mutable_format */
    /*  301 */ 0xf1cfa2ea69e6ec0eULL, /* VK_KHR_synchronization2 */
    /*  302 */ 0x61ed378f50459bf2ULL, /* VK_KHR_timeline_semaphore */
    /*  303 */ 0xfbb615f2cdb7e18fULL, /* VK_KHR_unified_image_layouts */
    /*  304 */ 0x3334ed809879d360ULL, /* VK_KHR_uniform_buffer_standard_layout */
    /*  305 */ 0x6146df22dcb09470ULL, /* VK_KHR_variable_pointers */
    /*  306 */ 0xcfd1e6704e4a4227ULL, /* VK_KHR_vertex_attribute_divisor */
    /*  307 */ 0x4ccc16568a9a2944ULL, /* VK_KHR_video_decode_av1 */
    /*  308 */ 0x0093b60d00888052ULL, /* VK_KHR_video_decode_h264 */
    /*  309 */ 0x4116f6bec0017e79ULL, /* VK_KHR_video_decode_h265 */
    /*  310 */ 0x363dac5e35a2f1eeULL, /* VK_KHR_video_decode_queue */
    /*  311 */ 0xc656a5824a51a00eULL, /* VK_KHR_video_decode_vp9 */
    /*  312 */ 0x35e683e888a7a54cULL, /* VK_KHR_video_encode_av1 */
    /*  313 */ 0xa77247c5899dc785ULL, /* VK_KHR_video_encode_h264 */
    /*  314 */ 0x8b86366e33c748eeULL, /* VK_KHR_video_encode_h265 */
    /*  315 */ 0x02882dc081b4a9a3ULL, /* VK_KHR_video_encode_intra_refresh */
    /*  316 */ 0x3f1a8c895b8e8debULL, /* VK_KHR_video_encode_quantization_map */
    /*  317 */ 0xdda14264a3bda234ULL, /* VK_KHR_video_encode_queue */
    /*  318 */ 0x9fb8181989e29256ULL, /* VK_KHR_video_maintenance1 */
    /*  319 */ 0xfd1949eb2a3c752bULL, /* VK_KHR_video_maintenance2 */
    /*  320 */ 0xc3d1c9b40515a6a4ULL, /* VK_KHR_video_queue */
    /*  321 */ 0x34899ec7a7b17614ULL, /* VK_KHR_vulkan_memory_model */
    /*  322 */ 0x906fcab3e0d202a5ULL, /* VK_KHR_wayland_surface */
    /*  323 */ 0x19d48609837c8701ULL, /* VK_KHR_win32_keyed_mutex */
    /*  324 */ 0xc93557e7cef43233ULL, /* VK_KHR_win32_surface */
    /*  325 */ 0x75ee32f09cdd8db9ULL, /* VK_KHR_workgroup_memory_explicit_layout */
    /*  326 */ 0x32a481baaa637e2cULL, /* VK_KHR_xcb_surface */
    /*  327 */ 0x863c0e309551346eULL, /* VK_KHR_xlib_surface */
    /*  328 */ 0x58d24a21f116065bULL, /* VK_KHR_zero_initialize_workgroup_memory */
    /*  329 */ 0x5615881540a7f6d8ULL, /* VK_LUNARG_direct_driver_loading */
    /*  330 */ 0x6f8fb9c8b46fc189ULL, /* VK_MESA_image_alignment_control */
    /*  331 */ 0xc1c930637836bf44ULL, /* VK_MSFT_layered_driver */
    /*  332 */ 0x489cf2a16640d39eULL, /* VK_MVK_ios_surface */
    /*  333 */ 0x3274c65edf45286cULL, /* VK_MVK_macos_surface */
    /*  334 */ 0x53643314731ac57aULL, /* VK_NN_vi_surface */
    /*  335 */ 0x5bf53745255ccc0eULL, /* VK_NVX_binary_import */
    /*  336 */ 0x20b59934a97efd1cULL, /* VK_NVX_image_view_handle */
    /*  337 */ 0x112ee8733e2b22b3ULL, /* VK_NVX_multiview_per_view_attributes */
    /*  338 */ 0x71fe862eee072b1eULL, /* VK_NV_acquire_winrt_display */
    /*  339 */ 0x9217a69de789d3feULL, /* VK_NV_clip_space_w_scaling */
    /*  340 */ 0x5d2cfdaf5ecc308bULL, /* VK_NV_cluster_acceleration_structure */
    /*  341 */ 0xad1ba91484f69ca3ULL, /* VK_NV_command_buffer_inheritance */
    /*  342 */ 0x21d19e30b520bdd6ULL, /* VK_NV_compute_shader_derivatives */
    /*  343 */ 0x069e842b3b51cefbULL, /* VK_NV_cooperative_matrix */
    /*  344 */ 0xfecfd80519026209ULL, /* VK_NV_cooperative_matrix2 */
    /*  345 */ 0x9b6d5b7725490586ULL, /* VK_NV_cooperative_vector */
    /*  346 */ 0xce889f8d6b40e84fULL, /* VK_NV_copy_memory_indirect */
    /*  347 */ 0xed85b1ac0329a8cdULL, /* VK_NV_corner_sampled_image */
    /*  348 */ 0x81b617790445f852ULL, /* VK_NV_coverage_reduction_mode */
    /*  349 */ 0x3644690c3bd14289ULL, /* VK_NV_cuda_kernel_launch */
    /*  350 */ 0xbb81f8243fcc7db5ULL, /* VK_NV_dedicated_allocation */
    /*  351 */ 0x00ce18bba106c2adULL, /* VK_NV_dedicated_allocation_image_aliasing */
    /*  352 */ 0x23bcacd889bea60cULL, /* VK_NV_descriptor_pool_overallocation */
    /*  353 */ 0xf03dfd81ad17796fULL, /* VK_NV_device_diagnostic_checkpoints */
    /*  354 */ 0xc8050fbd31afc5b5ULL, /* VK_NV_device_diagnostics_config */
    /*  355 */ 0xee7bfcd5523cff09ULL, /* VK_NV_device_generated_commands */
    /*  356 */ 0x2ff0ded4f3f040e9ULL, /* VK_NV_device_generated_commands_compute */
    /*  357 */ 0xc07b5e2a89ddc607ULL, /* VK_NV_displacement_micromap */
    /*  358 */ 0x5138c2f68bcb3608ULL, /* VK_NV_display_stereo */
    /*  359 */ 0xb2344e462fd9ef1bULL, /* VK_NV_extended_sparse_address_space */
    /*  360 */ 0xd15b433c649fb093ULL, /* VK_NV_external_compute_queue */
    /*  361 */ 0xab0f59a00375b1ecULL, /* VK_NV_external_memory */
    /*  362 */ 0x518148eb9166b4b9ULL, /* VK_NV_external_memory_capabilities */
    /*  363 */ 0x3c96386b301a3cdcULL, /* VK_NV_external_memory_rdma */
    /*  364 */ 0xcf69c3e7cbd068e4ULL, /* VK_NV_external_memory_win32 */
    /*  365 */ 0xdf9a65a432a12606ULL, /* VK_NV_fill_rectangle */
    /*  366 */ 0x9a6fda1e2f4f9096ULL, /* VK_NV_fragment_coverage_to_color */
    /*  367 */ 0xc294d55a56858fb6ULL, /* VK_NV_fragment_shader_barycentric */
    /*  368 */ 0x2ece12f465807058ULL, /* VK_NV_fragment_shading_rate_enums */
    /*  369 */ 0x4caba51b111c61b9ULL, /* VK_NV_framebuffer_mixed_samples */
    /*  370 */ 0xe0c4918343f3874cULL, /* VK_NV_geometry_shader_passthrough */
    /*  371 */ 0xd659873b3f6bc024ULL, /* VK_NV_glsl_shader */
    /*  372 */ 0xe39346d87fc9aa45ULL, /* VK_NV_inherited_viewport_scissor */
    /*  373 */ 0x52fcc4c2d713dad4ULL, /* VK_NV_linear_color_attachment */
    /*  374 */ 0xb58daf9c015becf7ULL, /* VK_NV_low_latency */
    /*  375 */ 0xa9eb852dfd7a1eceULL, /* VK_NV_low_latency2 */
    /*  376 */ 0x6c878fdbf1e4a7fbULL, /* VK_NV_memory_decompression */
    /*  377 */ 0x7401a89f84bc926bULL, /* VK_NV_mesh_shader */
    /*  378 */ 0x929112526891454eULL, /* VK_NV_optical_flow */
    /*  379 */ 0x6e9d1f60324c4761ULL, /* VK_NV_partitioned_acceleration_structure */
    /*  380 */ 0x5e0416a20f89c9f4ULL, /* VK_NV_per_stage_descriptor_set */
    /*  381 */ 0x48102b2d563a8028ULL, /* VK_NV_present_barrier */
    /*  382 */ 0xe16f6927a8473cabULL, /* VK_NV_present_metering */
    /*  383 */ 0xc20950e0cbc5bdc0ULL, /* VK_NV_raw_access_chains */
    /*  384 */ 0x3d4e9e0bb54735feULL, /* VK_NV_ray_tracing */
    /*  385 */ 0xe12f14699c6db9dbULL, /* VK_NV_ray_tracing_invocation_reorder */
    /*  386 */ 0x4157611d54ac1bc1ULL, /* VK_NV_ray_tracing_linear_swept_spheres */
    /*  387 */ 0xba4184e5104338cbULL, /* VK_NV_ray_tracing_motion_blur */
    /*  388 */ 0x451532c42bd881b2ULL, /* VK_NV_ray_tracing_validation */
    /*  389 */ 0x92ccabdfa0a3d6e4ULL, /* VK_NV_representative_fragment_test */
    /*  390 */ 0xc4d99252b7b7843fULL, /* VK_NV_sample_mask_override_coverage */
    /*  391 */ 0xd4d2cda699fc74aeULL, /* VK_NV_scissor_exclusive */
    /*  392 */ 0xb8974b1af4c34b58ULL, /* VK_NV_shader_atomic_float16_vector */
    /*  393 */ 0x52f9f98f09f18085ULL, /* VK_NV_shader_image_footprint */
    /*  394 */ 0xc394473a75e21d7cULL, /* VK_NV_shader_sm_builtins */
    /*  395 */ 0x5b6c5e76d8a8364eULL, /* VK_NV_shader_subgroup_partitioned */
    /*  396 */ 0xcac204d487e563d3ULL, /* VK_NV_shading_rate_image */
    /*  397 */ 0xfc6e35d06ddf634eULL, /* VK_NV_viewport_array2 */
    /*  398 */ 0x7748ea26eecd7e90ULL, /* VK_NV_viewport_swizzle */
    /*  399 */ 0x7e4ac6b10102b887ULL, /* VK_NV_win32_keyed_mutex */
    /*  400 */ 0xfb89dacebce47785ULL, /* VK_OHOS_surface */
    /*  401 */ 0x5c76ad884426c86cULL, /* VK_QCOM_filter_cubic_clamp */
    /*  402 */ 0xc7386bbfd1b9b423ULL, /* VK_QCOM_filter_cubic_weights */
    /*  403 */ 0xff445069da66b635ULL, /* VK_QCOM_fragment_density_map_offset */
    /*  404 */ 0xa6cab4106375cdfaULL, /* VK_QCOM_image_processing */
    /*  405 */ 0xa4a1ae34c2527a4aULL, /* VK_QCOM_image_processing2 */
    /*  406 */ 0xbff750af2234e2ceULL, /* VK_QCOM_multiview_per_view_render_areas */
    /*  407 */ 0x876a51c6df08420aULL, /* VK_QCOM_multiview_per_view_viewports */
    /*  408 */ 0xa3b4fc40f185c799ULL, /* VK_QCOM_render_pass_shader_resolve */
    /*  409 */ 0x9b5c2a0bc41e00cdULL, /* VK_QCOM_render_pass_store_ops */
    /*  410 */ 0x8d33cd618c723019ULL, /* VK_QCOM_render_pass_transform */
    /*  411 */ 0xd5a3f971e2e8b5c9ULL, /* VK_QCOM_rotated_copy_commands */
    /*  412 */ 0x73244ac23f3ec04aULL, /* VK_QCOM_tile_memory_heap */
    /*  413 */ 0xc37b456dbdf5565fULL, /* VK_QCOM_tile_properties */
    /*  414 */ 0x80b039482dfe4631ULL, /* VK_QCOM_tile_shading */
    /*  415 */ 0x49bfbd9f92e0b029ULL, /* VK_QCOM_ycbcr_degamma */
    /*  416 */ 0xc2e6f6dcc7614aceULL, /* VK_QNX_external_memory_screen_buffer */
    /*  417 */ 0x236bd86b3b17cf06ULL, /* VK_QNX_screen_surface */
    /*  418 */ 0xe6fed416ddebf8d0ULL, /* VK_SEC_amigo_profiling */
    /*  419 */ 0x8501d958b34af871ULL, /* VK_SEC_pipeline_cache_incremental_mode */
    /*  420 */ 0x45542cac22bd41a7ULL, /* VK_VALVE_descriptor_set_host_mapping */
    /*  421 */ 0x7aab48db428bd31bULL, /* VK_VALVE_fragment_density_map_layered */
    /*  422 */ 0x38c73d4ab66a4942ULL, /* VK_VALVE_mutable_descriptor_type */
    /*  423 */ 0x5674ed8bc838fecbULL  /* VK_VALVE_video_encode_rgb_conversion */
};

static void glad_vk_load_pfn_range(GladVulkanContext *context, GLADvkuserptrloadfunc load, void* userptr, uint16_t pfnStart, uint32_t numPfns)
{
    uint32_t pfnIdx;

    for (pfnIdx = pfnStart; pfnIdx < pfnStart + numPfns; ++pfnIdx) {
        const char *name = GLAD_Vulkan_fn_names[pfnIdx];
        const enum GLADcommandscope scope = (enum GLADcommandscope)GLAD_Vulkan_fn_scopes[pfnIdx];
        context->pfnArray[pfnIdx] = (void *)load(userptr, name, scope);
    }
}
static uint32_t glad_vk_resolve_alias_group(GladVulkanContext *context, const GladAliasPair_t *pairs, uint32_t start_idx, uint32_t total_count) {
    void **pfnArray = context->pfnArray;
    void *canonical_ptr;
    uint16_t canonical_idx = pairs[start_idx].first;
    uint32_t i, end_idx = start_idx;

    /* Find the end of this group (consecutive pairs with same canonical index) */
    while (end_idx < total_count && pairs[end_idx].first == canonical_idx) {
        end_idx++;
    }

    /* Pass 1: Find any loaded secondary for this canonical */
    canonical_ptr = pfnArray[canonical_idx];
    if (canonical_ptr == NULL) {
        for (i = start_idx; i < end_idx; ++i) {
            if (pfnArray[pairs[i].second] != NULL) {
                canonical_ptr = pfnArray[pairs[i].second];
                pfnArray[canonical_idx] = canonical_ptr;
                break;
            }
        }
    }

    /* Pass 2: Populate unloaded secondaries */
    if (canonical_ptr != NULL) {
        for (i = start_idx; i < end_idx; ++i) {
            if (pfnArray[pairs[i].second] == NULL) {
                pfnArray[pairs[i].second] = canonical_ptr;
            }
        }
    }

    return end_idx - 1;  /* Return index of last processed pair */
}

static const GladAliasPair_t GLAD_Vulkan_command_aliases[] = {
    {  138,  425 }, /* vkBindBufferMemory2 and vkBindBufferMemory2KHR */
    {  139,  426 }, /* vkBindImageMemory2 and vkBindImageMemory2KHR */
    {  195,  303 }, /* vkCmdBeginRendering and vkCmdBeginRenderingKHR */
    {  168,  354 }, /* vkCmdBeginRenderPass2 and vkCmdBeginRenderPass2KHR */
    {  226,  731 }, /* vkCmdBindDescriptorSets2 and vkCmdBindDescriptorSets2KHR */
    {  218,  687 }, /* vkCmdBindIndexBuffer2 and vkCmdBindIndexBuffer2KHR */
    {  202,  502 }, /* vkCmdBindVertexBuffers2 and vkCmdBindVertexBuffers2EXT */
    {  193,  576 }, /* vkCmdBlitImage2 and vkCmdBlitImage2KHR */
    {  189,  572 }, /* vkCmdCopyBuffer2 and vkCmdCopyBuffer2KHR */
    {  191,  574 }, /* vkCmdCopyBufferToImage2 and vkCmdCopyBufferToImage2KHR */
    {  190,  573 }, /* vkCmdCopyImage2 and vkCmdCopyImage2KHR */
    {  192,  575 }, /* vkCmdCopyImageToBuffer2 and vkCmdCopyImageToBuffer2KHR */
    {  142,  317 }, /* vkCmdDispatchBase and vkCmdDispatchBaseKHR */
    {  166,  301 }, /* vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountAMD */
    {  166,  449 }, /* vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountKHR */
    {  165,  300 }, /* vkCmdDrawIndirectCount and vkCmdDrawIndirectCountAMD */
    {  165,  448 }, /* vkCmdDrawIndirectCount and vkCmdDrawIndirectCountKHR */
    {  196,  304 }, /* vkCmdEndRendering and vkCmdEndRenderingKHR */
    {  170,  356 }, /* vkCmdEndRenderPass2 and vkCmdEndRenderPass2KHR */
    {  169,  355 }, /* vkCmdNextSubpass2 and vkCmdNextSubpass2KHR */
    {  186,  554 }, /* vkCmdPipelineBarrier2 and vkCmdPipelineBarrier2KHR */
    {  227,  732 }, /* vkCmdPushConstants2 and vkCmdPushConstants2KHR */
    {  222,  331 }, /* vkCmdPushDescriptorSet and vkCmdPushDescriptorSetKHR */
    {  228,  733 }, /* vkCmdPushDescriptorSet2 and vkCmdPushDescriptorSet2KHR */
    {  223,  332 }, /* vkCmdPushDescriptorSetWithTemplate and vkCmdPushDescriptorSetWithTemplateKHR */
    {  229,  734 }, /* vkCmdPushDescriptorSetWithTemplate2 and vkCmdPushDescriptorSetWithTemplate2KHR */
    {  184,  552 }, /* vkCmdResetEvent2 and vkCmdResetEvent2KHR */
    {  194,  577 }, /* vkCmdResolveImage2 and vkCmdResolveImage2KHR */
    {  197,  497 }, /* vkCmdSetCullMode and vkCmdSetCullModeEXT */
    {  210,  600 }, /* vkCmdSetDepthBiasEnable and vkCmdSetDepthBiasEnableEXT */
    {  206,  506 }, /* vkCmdSetDepthBoundsTestEnable and vkCmdSetDepthBoundsTestEnableEXT */
    {  205,  505 }, /* vkCmdSetDepthCompareOp and vkCmdSetDepthCompareOpEXT */
    {  203,  503 }, /* vkCmdSetDepthTestEnable and vkCmdSetDepthTestEnableEXT */
    {  204,  504 }, /* vkCmdSetDepthWriteEnable and vkCmdSetDepthWriteEnableEXT */
    {  141,  316 }, /* vkCmdSetDeviceMask and vkCmdSetDeviceMaskKHR */
    {  183,  551 }, /* vkCmdSetEvent2 and vkCmdSetEvent2KHR */
    {  198,  498 }, /* vkCmdSetFrontFace and vkCmdSetFrontFaceEXT */
    {  215,  495 }, /* vkCmdSetLineStipple and vkCmdSetLineStippleEXT */
    {  215,  728 }, /* vkCmdSetLineStipple and vkCmdSetLineStippleKHR */
    {  211,  602 }, /* vkCmdSetPrimitiveRestartEnable and vkCmdSetPrimitiveRestartEnableEXT */
    {  199,  499 }, /* vkCmdSetPrimitiveTopology and vkCmdSetPrimitiveTopologyEXT */
    {  209,  599 }, /* vkCmdSetRasterizerDiscardEnable and vkCmdSetRasterizerDiscardEnableEXT */
    {  224,  480 }, /* vkCmdSetRenderingAttachmentLocations and vkCmdSetRenderingAttachmentLocationsKHR */
    {  225,  481 }, /* vkCmdSetRenderingInputAttachmentIndices and vkCmdSetRenderingInputAttachmentIndicesKHR */
    {  201,  501 }, /* vkCmdSetScissorWithCount and vkCmdSetScissorWithCountEXT */
    {  208,  508 }, /* vkCmdSetStencilOp and vkCmdSetStencilOpEXT */
    {  207,  507 }, /* vkCmdSetStencilTestEnable and vkCmdSetStencilTestEnableEXT */
    {  200,  500 }, /* vkCmdSetViewportWithCount and vkCmdSetViewportWithCountEXT */
    {  185,  553 }, /* vkCmdWaitEvents2 and vkCmdWaitEvents2KHR */
    {  187,  555 }, /* vkCmdWriteTimestamp2 and vkCmdWriteTimestamp2KHR */
    {  232,  519 }, /* vkCopyImageToImage and vkCopyImageToImageEXT */
    {  231,  518 }, /* vkCopyImageToMemory and vkCopyImageToMemoryEXT */
    {  230,  517 }, /* vkCopyMemoryToImage and vkCopyMemoryToImageEXT */
    {  158,  335 }, /* vkCreateDescriptorUpdateTemplate and vkCreateDescriptorUpdateTemplateKHR */
    {  179,  534 }, /* vkCreatePrivateDataSlot and vkCreatePrivateDataSlotEXT */
    {  167,  353 }, /* vkCreateRenderPass2 and vkCreateRenderPass2KHR */
    {  156,  423 }, /* vkCreateSamplerYcbcrConversion and vkCreateSamplerYcbcrConversionKHR */
    {  159,  336 }, /* vkDestroyDescriptorUpdateTemplate and vkDestroyDescriptorUpdateTemplateKHR */
    {  180,  535 }, /* vkDestroyPrivateDataSlot and vkDestroyPrivateDataSlotEXT */
    {  157,  424 }, /* vkDestroySamplerYcbcrConversion and vkDestroySamplerYcbcrConversionKHR */
    {  143,  320 }, /* vkEnumeratePhysicalDeviceGroups and vkEnumeratePhysicalDeviceGroupsKHR */
    {  175,  482 }, /* vkGetBufferDeviceAddress and vkGetBufferDeviceAddressEXT */
    {  175,  492 }, /* vkGetBufferDeviceAddress and vkGetBufferDeviceAddressKHR */
    {  145,  398 }, /* vkGetBufferMemoryRequirements2 and vkGetBufferMemoryRequirements2KHR */
    {  176,  493 }, /* vkGetBufferOpaqueCaptureAddress and vkGetBufferOpaqueCaptureAddressKHR */
    {  454,  730 }, /* vkGetCalibratedTimestampsEXT and vkGetCalibratedTimestampsKHR */
    {  164,  447 }, /* vkGetDescriptorSetLayoutSupport and vkGetDescriptorSetLayoutSupportKHR */
    {  212,  626 }, /* vkGetDeviceBufferMemoryRequirements and vkGetDeviceBufferMemoryRequirementsKHR */
    {  140,  315 }, /* vkGetDeviceGroupPeerMemoryFeatures and vkGetDeviceGroupPeerMemoryFeaturesKHR */
    {  213,  627 }, /* vkGetDeviceImageMemoryRequirements and vkGetDeviceImageMemoryRequirementsKHR */
    {  214,  628 }, /* vkGetDeviceImageSparseMemoryRequirements and vkGetDeviceImageSparseMemoryRequirementsKHR */
    {  220,  689 }, /* vkGetDeviceImageSubresourceLayout and vkGetDeviceImageSubresourceLayoutKHR */
    {  177,  494 }, /* vkGetDeviceMemoryOpaqueCaptureAddress and vkGetDeviceMemoryOpaqueCaptureAddressKHR */
    {  144,  397 }, /* vkGetImageMemoryRequirements2 and vkGetImageMemoryRequirements2KHR */
    {  146,  399 }, /* vkGetImageSparseMemoryRequirements2 and vkGetImageSparseMemoryRequirements2KHR */
    {  221,  521 }, /* vkGetImageSubresourceLayout2 and vkGetImageSubresourceLayout2EXT */
    {  221,  690 }, /* vkGetImageSubresourceLayout2 and vkGetImageSubresourceLayout2KHR */
    {  453,  729 }, /* vkGetPhysicalDeviceCalibrateableTimeDomainsEXT and vkGetPhysicalDeviceCalibrateableTimeDomainsKHR */
    {  161,  321 }, /* vkGetPhysicalDeviceExternalBufferProperties and vkGetPhysicalDeviceExternalBufferPropertiesKHR */
    {  162,  358 }, /* vkGetPhysicalDeviceExternalFenceProperties and vkGetPhysicalDeviceExternalFencePropertiesKHR */
    {  163,  326 }, /* vkGetPhysicalDeviceExternalSemaphoreProperties and vkGetPhysicalDeviceExternalSemaphorePropertiesKHR */
    {  147,  308 }, /* vkGetPhysicalDeviceFeatures2 and vkGetPhysicalDeviceFeatures2KHR */
    {  149,  310 }, /* vkGetPhysicalDeviceFormatProperties2 and vkGetPhysicalDeviceFormatProperties2KHR */
    {  150,  311 }, /* vkGetPhysicalDeviceImageFormatProperties2 and vkGetPhysicalDeviceImageFormatProperties2KHR */
    {  152,  313 }, /* vkGetPhysicalDeviceMemoryProperties2 and vkGetPhysicalDeviceMemoryProperties2KHR */
    {  148,  309 }, /* vkGetPhysicalDeviceProperties2 and vkGetPhysicalDeviceProperties2KHR */
    {  151,  312 }, /* vkGetPhysicalDeviceQueueFamilyProperties2 and vkGetPhysicalDeviceQueueFamilyProperties2KHR */
    {  153,  314 }, /* vkGetPhysicalDeviceSparseImageFormatProperties2 and vkGetPhysicalDeviceSparseImageFormatProperties2KHR */
    {  178,  483 }, /* vkGetPhysicalDeviceToolProperties and vkGetPhysicalDeviceToolPropertiesEXT */
    {  182,  537 }, /* vkGetPrivateData and vkGetPrivateDataEXT */
    {  443,  418 }, /* vkGetRayTracingShaderGroupHandlesNV and vkGetRayTracingShaderGroupHandlesKHR */
    {  219,  688 }, /* vkGetRenderingAreaGranularity and vkGetRenderingAreaGranularityKHR */
    {  172,  463 }, /* vkGetSemaphoreCounterValue and vkGetSemaphoreCounterValueKHR */
    {  216,  522 }, /* vkMapMemory2 and vkMapMemory2KHR */
    {  188,  556 }, /* vkQueueSubmit2 and vkQueueSubmit2KHR */
    {  524,  705 }, /* vkReleaseSwapchainImagesEXT and vkReleaseSwapchainImagesKHR */
    {  171,  496 }, /* vkResetQueryPool and vkResetQueryPoolEXT */
    {  181,  536 }, /* vkSetPrivateData and vkSetPrivateDataEXT */
    {  174,  465 }, /* vkSignalSemaphore and vkSignalSemaphoreKHR */
    {  233,  520 }, /* vkTransitionImageLayout and vkTransitionImageLayoutEXT */
    {  154,  319 }, /* vkTrimCommandPool and vkTrimCommandPoolKHR */
    {  217,  523 }, /* vkUnmapMemory2 and vkUnmapMemory2KHR */
    {  160,  337 }, /* vkUpdateDescriptorSetWithTemplate and vkUpdateDescriptorSetWithTemplateKHR */
    {  173,  464 }, /* vkWaitSemaphores and vkWaitSemaphoresKHR */
};

GLAD_NO_INLINE static void glad_vk_resolve_aliases(GladVulkanContext *context) {
    uint32_t i;

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_Vulkan_command_aliases); ++i) {
        i = glad_vk_resolve_alias_group(context, GLAD_Vulkan_command_aliases, i, GLAD_ARRAYSIZE(GLAD_Vulkan_command_aliases));
    }
}

static int glad_vk_get_extensions(GladVulkanContext *context, VkPhysicalDevice physical_device, uint32_t *out_extension_count, uint64_t **out_extensions) {
    uint32_t i;
    uint32_t instance_extension_count = 0;
    uint32_t device_extension_count = 0;
    uint32_t max_extension_count = 0;
    uint32_t total_extension_count = 0;
    uint64_t *extensions = NULL;
    VkExtensionProperties *ext_properties = NULL;
    VkResult result;

    if (context->EnumerateInstanceExtensionProperties == NULL || (physical_device != NULL && context->EnumerateDeviceExtensionProperties == NULL)) {
        return 0;
    }

    result = context->EnumerateInstanceExtensionProperties(NULL, &instance_extension_count, NULL);
    if (result != VK_SUCCESS) {
        return 0;
    }

    if (physical_device != NULL) {
        result = context->EnumerateDeviceExtensionProperties(physical_device, NULL, &device_extension_count, NULL);
        if (result != VK_SUCCESS) {
            return 0;
        }
    }

    total_extension_count = instance_extension_count + device_extension_count;
    if (total_extension_count <= 0) {
        return 0;
    }

    max_extension_count = instance_extension_count > device_extension_count
        ? instance_extension_count : device_extension_count;

    ext_properties = (VkExtensionProperties*) malloc(max_extension_count * sizeof(VkExtensionProperties));
    if (ext_properties == NULL) {
        goto glad_vk_get_extensions_error;
    }

    result = context->EnumerateInstanceExtensionProperties(NULL, &instance_extension_count, ext_properties);
    if (result != VK_SUCCESS) {
        goto glad_vk_get_extensions_error;
    }

    extensions = (uint64_t *)calloc(total_extension_count, sizeof(uint64_t));
    if (extensions == NULL) {
        goto glad_vk_get_extensions_error;
    }

    for (i = 0; i < instance_extension_count; ++i) {
        VkExtensionProperties ext = ext_properties[i];
        size_t extension_name_length = strlen(ext.extensionName);
        extensions[i] = glad_hash_string(ext.extensionName, extension_name_length * sizeof(char));
    }

    if (physical_device != NULL) {
        result = context->EnumerateDeviceExtensionProperties(physical_device, NULL, &device_extension_count, ext_properties);
        if (result != VK_SUCCESS) {
            goto glad_vk_get_extensions_error;
        }

        for (i = 0; i < device_extension_count; ++i) {
            VkExtensionProperties ext = ext_properties[i];
            size_t extension_name_length = strlen(ext.extensionName);
            extensions[instance_extension_count + i] = glad_hash_string(ext.extensionName, extension_name_length * sizeof(char));
        }
    }

    qsort(extensions, total_extension_count, sizeof(uint64_t), compare_uint64);

    if (instance_extension_count)
        context->glad_found_instance_exts = 1;
    if (device_extension_count)
        context->glad_found_device_exts = 1;

    free((void*) ext_properties);

    *out_extension_count = total_extension_count;
    *out_extensions = extensions;

    return 1;

glad_vk_get_extensions_error:
    free((void*) ext_properties);
    free(extensions);
    return 0;
}

static void glad_vk_free_extensions(uint64_t *extensions) {
    free((void*) extensions);
}

static int glad_vk_has_extension(uint64_t *extensions, uint64_t extension_count, uint64_t name) {
    return glad_hash_search(extensions, extension_count, name);
}

static GLADapiproc glad_vk_get_proc_from_userptr(void *userptr, const char* name, enum GLADcommandscope scope) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *, enum GLADcommandscope)) userptr)(name, scope);
}

static int glad_vk_find_extensions_vulkan(GladVulkanContext *context, VkPhysicalDevice physical_device) {
    uint32_t extension_count = 0;
    uint32_t i;
    uint64_t *extensions = NULL;

    if (physical_device && context->glad_found_device_exts)
        return 1;
    if (!physical_device && context->glad_found_instance_exts)
        return 1;

    if (!glad_vk_get_extensions(context, physical_device, &extension_count, &extensions)) return 0;

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_Vulkan_ext_hashes); ++i)
        context->extArray[i] = glad_vk_has_extension(extensions, extension_count, GLAD_Vulkan_ext_hashes[i]);

    GLAD_UNUSED(glad_vk_has_extension);

    glad_vk_free_extensions(extensions);
    return 1;
}

static int glad_vk_find_core_vulkan(GladVulkanContext *context, VkPhysicalDevice physical_device) {
    const uint32_t API_VARIANT_MASK = 0xe0000000;
    int major = 1;
    int minor = 0;
    uint16_t version_value;

#ifdef VK_VERSION_1_1
    if (!context->glad_vk_instance_version && context->EnumerateInstanceVersion != NULL) {
        VkResult result;

        result = context->EnumerateInstanceVersion(&context->glad_vk_instance_version);
        if (result != VK_SUCCESS)
            context->glad_vk_instance_version = 0;
        context->glad_vk_instance_version &= ~API_VARIANT_MASK;
    }
    major = (int) VK_VERSION_MAJOR(context->glad_vk_instance_version);
    minor = (int) VK_VERSION_MINOR(context->glad_vk_instance_version);
#endif

    if (!context->glad_vk_device_version) {
        if (physical_device != NULL && context->GetPhysicalDeviceProperties != NULL) {
            VkPhysicalDeviceProperties properties;
            context->GetPhysicalDeviceProperties(physical_device, &properties);
            context->glad_vk_device_version = properties.apiVersion;
            context->glad_vk_device_version &= ~API_VARIANT_MASK;
        }
    }
    if (context->glad_vk_device_version) {
        major = (int) VK_VERSION_MAJOR(context->glad_vk_device_version);
        minor = (int) VK_VERSION_MINOR(context->glad_vk_device_version);
    }

    version_value = (major << 8U) | minor;

    context->VERSION_1_0 = version_value >= 0x0100;
    context->VERSION_1_1 = version_value >= 0x0101;
    context->VERSION_1_2 = version_value >= 0x0102;
    context->VERSION_1_3 = version_value >= 0x0103;
    context->VERSION_1_4 = version_value >= 0x0104;

    return GLAD_MAKE_VERSION(major, minor);
}

GLAD_NO_INLINE int gladLoadVulkanContextUserPtr(GladVulkanContext *context, VkInstance instance, VkPhysicalDevice physical_device, VkDevice device, GLADvkuserptrloadfunc load, void *userptr) {
    int version;
    uint32_t i;

    (void)instance;
    (void)device;

#ifdef VK_VERSION_1_1
    context->EnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion)load(userptr, "vkEnumerateInstanceVersion", CommandScopeGlobal);
#endif

    version = glad_vk_find_core_vulkan(context, physical_device);
    if (!version) {
        return 0;
    }

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_Vulkan_feature_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_Vulkan_feature_pfn_ranges[i];
        if (context->featArray[range->extension]) {
            glad_vk_load_pfn_range(context, load, userptr, range->start, range->count);
        }
    }

    if (!glad_vk_find_extensions_vulkan(context, physical_device)) return 0;

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_Vulkan_ext_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_Vulkan_ext_pfn_ranges[i];
        if (context->extArray[range->extension]) {
            glad_vk_load_pfn_range(context, load, userptr, range->start, range->count);
        }
    }

    gladSetVulkanContext(context);
    glad_vk_resolve_aliases(context);

    return version;
}

int gladLoadVulkanUserPtr(VkInstance instance, VkPhysicalDevice physical_device, VkDevice device, GLADvkuserptrloadfunc load, void *userptr) {
    return gladLoadVulkanContextUserPtr(gladGetVulkanContext(), instance, physical_device, device, load, userptr);
}

int gladLoadVulkanContext(GladVulkanContext *context, VkInstance instance, VkPhysicalDevice physical_device, VkDevice device, GLADvkloadfunc load) {
    return gladLoadVulkanContextUserPtr(context, instance, physical_device, device, glad_vk_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}

int gladLoadVulkan(VkInstance instance, VkPhysicalDevice physical_device, VkDevice device, GLADvkloadfunc load) {
    return gladLoadVulkanContext(gladGetVulkanContext(), instance, physical_device, device, load);
}

GladVulkanContext* gladGetVulkanContext() {
    return &glad_vulkan_context;
}

void gladSetVulkanContext(GladVulkanContext *context) {
    if (!context) return;
    if (&glad_vulkan_context == context) return;
    glad_vulkan_context = *context;
}


#ifdef GLAD_VULKAN

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

struct _glad_vulkan_userptr {
    void *vk_handle;
    VkInstance vk_instance;
    VkDevice vk_device;
    PFN_vkGetInstanceProcAddr get_instance_proc_addr;
    PFN_vkGetDeviceProcAddr get_device_proc_addr;
};

static GLADapiproc glad_vulkan_get_proc(void *vuserptr, const char *name, enum GLADcommandscope scope ) {
    struct _glad_vulkan_userptr userptr = *(struct _glad_vulkan_userptr*) vuserptr;
    PFN_vkVoidFunction result = NULL;

    switch (scope) {
    case CommandScopeUnknown:
        result = (PFN_vkVoidFunction)glad_dlsym_handle(userptr.vk_handle, name);
        break;
    case CommandScopeGlobal:
        result = userptr.get_instance_proc_addr(NULL, name);
        break;
    case CommandScopeDevice:
        if (userptr.vk_device != NULL)
            result = userptr.get_device_proc_addr(userptr.vk_device, name);
        break;
    case CommandScopeInstance:
        if (userptr.vk_instance != NULL)
            result = userptr.get_instance_proc_addr(userptr.vk_instance, name);
        break;
    }

    return (GLADapiproc) result;
}

static void* glad_vulkan_dlopen_handle(GladVulkanContext *context) {
    static const char *NAMES[] = {
#if GLAD_PLATFORM_APPLE
        "libvulkan.dylib",
        "libvulkan.1.dylib",
        "libMoltenVK.dylib",
#elif GLAD_PLATFORM_WIN32
        "vulkan-1.dll",
#else
        "libvulkan.so.1",
        "libvulkan.so",
#endif
    };

    if (context->glad_loader_handle == NULL) {
        context->glad_loader_handle = glad_get_dlopen_handle(NAMES, GLAD_ARRAYSIZE(NAMES));
    }

    return context->glad_loader_handle;
}

static struct _glad_vulkan_userptr glad_vulkan_build_userptr(void *handle, VkInstance instance, VkDevice device) {
    struct _glad_vulkan_userptr userptr;
    userptr.vk_handle = handle;
    userptr.vk_instance = instance;
    userptr.vk_device = device;
    userptr.get_instance_proc_addr = (PFN_vkGetInstanceProcAddr) glad_dlsym_handle(handle, "vkGetInstanceProcAddr");
    userptr.get_device_proc_addr = (PFN_vkGetDeviceProcAddr) glad_dlsym_handle(handle, "vkGetDeviceProcAddr");
    return userptr;
}

int gladLoaderLoadVulkanContext(GladVulkanContext *context, VkInstance instance, VkPhysicalDevice physical_device, VkDevice device) {
    int version = 0;
    void *handle = NULL;
    int did_load = 0;
    struct _glad_vulkan_userptr userptr;

    did_load = context->glad_loader_handle == NULL;
    handle = glad_vulkan_dlopen_handle(context);
    if (handle != NULL) {
        userptr = glad_vulkan_build_userptr(handle, instance, device);

        version = gladLoadVulkanContextUserPtr(context,instance, physical_device, device, glad_vulkan_get_proc, &userptr);

        if (!version && did_load) {
            gladLoaderUnloadVulkanContext(context);
        }
    }

    return version;
}

void gladLoaderResetVulkanContext(GladVulkanContext *context) {
    memset(context, 0, sizeof(GladVulkanContext));
}

void gladLoaderResetVulkan(void) {
    gladLoaderResetVulkanContext(gladGetVulkanContext());
}

int gladLoaderLoadVulkan(VkInstance instance, VkPhysicalDevice physical_device, VkDevice device) {
    return gladLoaderLoadVulkanContext(gladGetVulkanContext(), instance, physical_device, device);
}

void gladLoaderUnloadVulkanContext(GladVulkanContext *context) {
    if (context->glad_loader_handle != NULL) {
        glad_close_dlopen_handle(context->glad_loader_handle);
        context->glad_loader_handle = NULL;
    }

    gladLoaderResetVulkanContext(context);
}

void gladLoaderUnloadVulkan(void) {
    gladLoaderUnloadVulkanContext(gladGetVulkanContext());
}

#endif /* GLAD_VULKAN */

#ifdef __cplusplus
}
#endif
