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
GladVulkanContext glad_vulkan_context = {};
#else
GladVulkanContext glad_vulkan_context = { 0 };
#endif

static const char *GLAD_Vulkan_fn_names[] = {
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

static uint64_t GLAD_Vulkan_ext_hashes[] = {
    /*    0 */ 0x6aba9e60325e43c3, /* VK_AMDX_dense_geometry_format */
    /*    1 */ 0x6ae42d438bb0484c, /* VK_AMDX_shader_enqueue */
    /*    2 */ 0x141bdaf54e241180, /* VK_AMD_anti_lag */
    /*    3 */ 0x65ac43ace7243e04, /* VK_AMD_buffer_marker */
    /*    4 */ 0x8353850f5238ee1d, /* VK_AMD_device_coherent_memory */
    /*    5 */ 0x7f6d3eb981ed905a, /* VK_AMD_display_native_hdr */
    /*    6 */ 0x0b55dbb0df76886c, /* VK_AMD_draw_indirect_count */
    /*    7 */ 0xf3c87297143cbd5a, /* VK_AMD_gcn_shader */
    /*    8 */ 0xd16896d602d6c016, /* VK_AMD_gpu_shader_half_float */
    /*    9 */ 0x80dbf6d9994a8486, /* VK_AMD_gpu_shader_int16 */
    /*   10 */ 0x777abeda8eb885f2, /* VK_AMD_memory_overallocation_behavior */
    /*   11 */ 0x09abd53b962f7221, /* VK_AMD_mixed_attachment_samples */
    /*   12 */ 0x9f9cc0f84d49fc24, /* VK_AMD_negative_viewport_height */
    /*   13 */ 0xc4fcbc5045e4b55d, /* VK_AMD_pipeline_compiler_control */
    /*   14 */ 0x2b4b03257b517fe7, /* VK_AMD_rasterization_order */
    /*   15 */ 0x253e959bcd5e01e9, /* VK_AMD_shader_ballot */
    /*   16 */ 0x4cb3d15508759039, /* VK_AMD_shader_core_properties */
    /*   17 */ 0xe9de3bafe3e1e19a, /* VK_AMD_shader_core_properties2 */
    /*   18 */ 0xb9e9755d0b011c3f, /* VK_AMD_shader_early_and_late_fragment_tests */
    /*   19 */ 0x9564cc2b0038b597, /* VK_AMD_shader_explicit_vertex_parameter */
    /*   20 */ 0x2d734d0c4158eb7e, /* VK_AMD_shader_fragment_mask */
    /*   21 */ 0x1fd2270dcd52ad73, /* VK_AMD_shader_image_load_store_lod */
    /*   22 */ 0x62011d43d2d97594, /* VK_AMD_shader_info */
    /*   23 */ 0x48ef51e9f522215b, /* VK_AMD_shader_trinary_minmax */
    /*   24 */ 0x7e011534e1db7838, /* VK_AMD_texture_gather_bias_lod */
    /*   25 */ 0xee13e9584a79a866, /* VK_ANDROID_external_format_resolve */
    /*   26 */ 0x0efa9218af4eedaa, /* VK_ANDROID_external_memory_android_hardware_buffer */
    /*   27 */ 0x74a1ed3ccf91f30b, /* VK_ARM_data_graph */
    /*   28 */ 0x06411aa4c0bddda8, /* VK_ARM_format_pack */
    /*   29 */ 0x0f753497d22c514b, /* VK_ARM_pipeline_opacity_micromap */
    /*   30 */ 0x0afcd59fd2af6286, /* VK_ARM_rasterization_order_attachment_access */
    /*   31 */ 0x099508890a72c586, /* VK_ARM_render_pass_striped */
    /*   32 */ 0xcb5ebd8b3c00874c, /* VK_ARM_scheduling_controls */
    /*   33 */ 0x6d66a5a00c62648d, /* VK_ARM_shader_core_builtins */
    /*   34 */ 0x42f58e0f0c034d62, /* VK_ARM_shader_core_properties */
    /*   35 */ 0xdda32da4e6cb55be, /* VK_ARM_tensors */
    /*   36 */ 0x9452c6992583027b, /* VK_EXT_4444_formats */
    /*   37 */ 0xc78e4b8ee4076491, /* VK_EXT_acquire_drm_display */
    /*   38 */ 0xf320bc0da89095cc, /* VK_EXT_acquire_xlib_display */
    /*   39 */ 0x1f2679f2f103d431, /* VK_EXT_astc_decode_mode */
    /*   40 */ 0xf27c39b3a1b079ad, /* VK_EXT_attachment_feedback_loop_dynamic_state */
    /*   41 */ 0x74d9e22c0880d05b, /* VK_EXT_attachment_feedback_loop_layout */
    /*   42 */ 0xbf40b1c2e2a175ca, /* VK_EXT_blend_operation_advanced */
    /*   43 */ 0xa7ae01d75b03a5fa, /* VK_EXT_border_color_swizzle */
    /*   44 */ 0x8cadd6ee8baeb7b6, /* VK_EXT_buffer_device_address */
    /*   45 */ 0xe53030d618c508b9, /* VK_EXT_calibrated_timestamps */
    /*   46 */ 0x1821c534e43e8bc2, /* VK_EXT_color_write_enable */
    /*   47 */ 0x3acaa19dcdfa4838, /* VK_EXT_conditional_rendering */
    /*   48 */ 0xbc479489c58aba55, /* VK_EXT_conservative_rasterization */
    /*   49 */ 0xd41fdd03d1591c42, /* VK_EXT_custom_border_color */
    /*   50 */ 0x13dd727d73e5c438, /* VK_EXT_debug_marker */
    /*   51 */ 0xefc5d6f86f5274aa, /* VK_EXT_debug_report */
    /*   52 */ 0x1f4cc1384fdd3124, /* VK_EXT_debug_utils */
    /*   53 */ 0x4334a6b5b2a8bcdf, /* VK_EXT_depth_bias_control */
    /*   54 */ 0x20b2ee75c46fae3b, /* VK_EXT_depth_clamp_control */
    /*   55 */ 0x42e03d02e07ee602, /* VK_EXT_depth_clamp_zero_one */
    /*   56 */ 0xc46ca287fec7bfa2, /* VK_EXT_depth_clip_control */
    /*   57 */ 0xb225ae836596c941, /* VK_EXT_depth_clip_enable */
    /*   58 */ 0x683e05b7c95cf871, /* VK_EXT_depth_range_unrestricted */
    /*   59 */ 0xff983b309bdf4f8f, /* VK_EXT_descriptor_buffer */
    /*   60 */ 0x8ed9a50d9652d13a, /* VK_EXT_descriptor_indexing */
    /*   61 */ 0x71042286279bf266, /* VK_EXT_device_address_binding_report */
    /*   62 */ 0x44712682d623c6ec, /* VK_EXT_device_fault */
    /*   63 */ 0x6c42eb1e4c30ed48, /* VK_EXT_device_generated_commands */
    /*   64 */ 0xfc8708a7a55a3b72, /* VK_EXT_device_memory_report */
    /*   65 */ 0x3d21adc07dc92de9, /* VK_EXT_direct_mode_display */
    /*   66 */ 0x2f377620d96a0b95, /* VK_EXT_directfb_surface */
    /*   67 */ 0x6c4b18b294f729e9, /* VK_EXT_discard_rectangles */
    /*   68 */ 0x2bd79b14ec35b405, /* VK_EXT_display_control */
    /*   69 */ 0xf82da0558a082445, /* VK_EXT_display_surface_counter */
    /*   70 */ 0x6c84fccd28668412, /* VK_EXT_dynamic_rendering_unused_attachments */
    /*   71 */ 0x405b3a7704a014a0, /* VK_EXT_extended_dynamic_state */
    /*   72 */ 0x09050069bac4e50b, /* VK_EXT_extended_dynamic_state2 */
    /*   73 */ 0x3e6696389e531962, /* VK_EXT_extended_dynamic_state3 */
    /*   74 */ 0x204d4d8537dc240c, /* VK_EXT_external_memory_acquire_unmodified */
    /*   75 */ 0xfbe83be92d0dc3e1, /* VK_EXT_external_memory_dma_buf */
    /*   76 */ 0xe730e90349447245, /* VK_EXT_external_memory_host */
    /*   77 */ 0xbb6a5bdb9f4339b2, /* VK_EXT_external_memory_metal */
    /*   78 */ 0x2ff4c771bf02a660, /* VK_EXT_filter_cubic */
    /*   79 */ 0xdd63dbab93498a89, /* VK_EXT_fragment_density_map */
    /*   80 */ 0x639aaec72634d6cc, /* VK_EXT_fragment_density_map2 */
    /*   81 */ 0x50ea79c84acba293, /* VK_EXT_fragment_density_map_offset */
    /*   82 */ 0xec38db4912e9aa39, /* VK_EXT_fragment_shader_interlock */
    /*   83 */ 0x4bed293561f471c5, /* VK_EXT_frame_boundary */
    /*   84 */ 0xf888a39f24346db4, /* VK_EXT_full_screen_exclusive */
    /*   85 */ 0x026fba6d706537f5, /* VK_EXT_global_priority */
    /*   86 */ 0x49240b90779ad742, /* VK_EXT_global_priority_query */
    /*   87 */ 0xe612048b33a20737, /* VK_EXT_graphics_pipeline_library */
    /*   88 */ 0xd140703366300180, /* VK_EXT_hdr_metadata */
    /*   89 */ 0xfc97df8c7f5cb62e, /* VK_EXT_headless_surface */
    /*   90 */ 0x15c6d3b4db750060, /* VK_EXT_host_image_copy */
    /*   91 */ 0xcc9a1964d5f92ead, /* VK_EXT_host_query_reset */
    /*   92 */ 0x992053b93ca7369a, /* VK_EXT_image_2d_view_of_3d */
    /*   93 */ 0xac673544b231a330, /* VK_EXT_image_compression_control */
    /*   94 */ 0xfc267e5b08be3c88, /* VK_EXT_image_compression_control_swapchain */
    /*   95 */ 0x5d78e7153c62776c, /* VK_EXT_image_drm_format_modifier */
    /*   96 */ 0xe918548d9d09bdf5, /* VK_EXT_image_robustness */
    /*   97 */ 0x10ea5ce8b7b462c6, /* VK_EXT_image_sliced_view_of_3d */
    /*   98 */ 0x5d125c6144d30072, /* VK_EXT_image_view_min_lod */
    /*   99 */ 0x66bb737b7652d71d, /* VK_EXT_index_type_uint8 */
    /*  100 */ 0x59f61f1cc23145ee, /* VK_EXT_inline_uniform_block */
    /*  101 */ 0x9ba2edc52691fc07, /* VK_EXT_layer_settings */
    /*  102 */ 0xa45ec0ff789f2882, /* VK_EXT_legacy_dithering */
    /*  103 */ 0x93eebd73e097d983, /* VK_EXT_legacy_vertex_attributes */
    /*  104 */ 0x98daf38a4cd796bc, /* VK_EXT_line_rasterization */
    /*  105 */ 0xca3cb4186d57fa40, /* VK_EXT_load_store_op_none */
    /*  106 */ 0xc92882ba73a7ad8a, /* VK_EXT_map_memory_placed */
    /*  107 */ 0xa642b55c0f467f26, /* VK_EXT_memory_budget */
    /*  108 */ 0xdf03e1a0a38154d2, /* VK_EXT_memory_priority */
    /*  109 */ 0x38a2a90e0a820189, /* VK_EXT_mesh_shader */
    /*  110 */ 0x6bcff1cd8cf418f2, /* VK_EXT_metal_objects */
    /*  111 */ 0x60fc707b7c19679c, /* VK_EXT_metal_surface */
    /*  112 */ 0x60ca462964877ba5, /* VK_EXT_multi_draw */
    /*  113 */ 0x60c608294e99436f, /* VK_EXT_multisampled_render_to_single_sampled */
    /*  114 */ 0x333da01be07c65e4, /* VK_EXT_mutable_descriptor_type */
    /*  115 */ 0x4f43f294a30fc75d, /* VK_EXT_nested_command_buffer */
    /*  116 */ 0x6cf77b70db09b037, /* VK_EXT_non_seamless_cube_map */
    /*  117 */ 0xb5bdb97dc49555ef, /* VK_EXT_opacity_micromap */
    /*  118 */ 0x74062e5990db1eeb, /* VK_EXT_pageable_device_local_memory */
    /*  119 */ 0xe60ea5fa872ffa4b, /* VK_EXT_pci_bus_info */
    /*  120 */ 0x087b96c0fac7f2e9, /* VK_EXT_physical_device_drm */
    /*  121 */ 0xae186881e629f533, /* VK_EXT_pipeline_creation_cache_control */
    /*  122 */ 0xd5ed321620183ae4, /* VK_EXT_pipeline_creation_feedback */
    /*  123 */ 0xf2497807f1195d03, /* VK_EXT_pipeline_library_group_handles */
    /*  124 */ 0x97816799b0ea2a08, /* VK_EXT_pipeline_properties */
    /*  125 */ 0x0bec2c70abec6edf, /* VK_EXT_pipeline_protected_access */
    /*  126 */ 0x3726d3c286b23305, /* VK_EXT_pipeline_robustness */
    /*  127 */ 0x578e2a9cdc320baa, /* VK_EXT_post_depth_coverage */
    /*  128 */ 0xdad3977856dd3ce4, /* VK_EXT_present_mode_fifo_latest_ready */
    /*  129 */ 0x4792bf3539da07a0, /* VK_EXT_primitive_topology_list_restart */
    /*  130 */ 0x4de3fc9eb140d3c9, /* VK_EXT_primitives_generated_query */
    /*  131 */ 0x66832604ff1fb25a, /* VK_EXT_private_data */
    /*  132 */ 0x3632448643e01277, /* VK_EXT_provoking_vertex */
    /*  133 */ 0xc3a80f57bc34acf0, /* VK_EXT_queue_family_foreign */
    /*  134 */ 0x9c47749ad3103e99, /* VK_EXT_rasterization_order_attachment_access */
    /*  135 */ 0xe3b61ff718cac048, /* VK_EXT_rgba10x6_formats */
    /*  136 */ 0x267337703fbb9802, /* VK_EXT_robustness2 */
    /*  137 */ 0xa2f0c46d62bffbbd, /* VK_EXT_sample_locations */
    /*  138 */ 0x35bc8d45855c9ddd, /* VK_EXT_sampler_filter_minmax */
    /*  139 */ 0x0fe7c2504b67f76e, /* VK_EXT_scalar_block_layout */
    /*  140 */ 0x21c315365bdd91c1, /* VK_EXT_separate_stencil_usage */
    /*  141 */ 0x39152af17d406387, /* VK_EXT_shader_atomic_float */
    /*  142 */ 0xfa5bf73b09f1814a, /* VK_EXT_shader_atomic_float2 */
    /*  143 */ 0x1313743aff740ea6, /* VK_EXT_shader_demote_to_helper_invocation */
    /*  144 */ 0xf791a964511a9452, /* VK_EXT_shader_float8 */
    /*  145 */ 0xdbd208469e466661, /* VK_EXT_shader_image_atomic_int64 */
    /*  146 */ 0x0fdb11284e798630, /* VK_EXT_shader_module_identifier */
    /*  147 */ 0x01d57626cc2cb88b, /* VK_EXT_shader_object */
    /*  148 */ 0xd98565c5e8cff707, /* VK_EXT_shader_replicated_composites */
    /*  149 */ 0x1d5f02c289908dc6, /* VK_EXT_shader_stencil_export */
    /*  150 */ 0x3434e0e3856c3974, /* VK_EXT_shader_subgroup_ballot */
    /*  151 */ 0x414fe291cad1b8c2, /* VK_EXT_shader_subgroup_vote */
    /*  152 */ 0x15c81e1e3330c87a, /* VK_EXT_shader_tile_image */
    /*  153 */ 0x3ab7ae29a67149aa, /* VK_EXT_shader_viewport_index_layer */
    /*  154 */ 0xf8847bcd6077bcfc, /* VK_EXT_subgroup_size_control */
    /*  155 */ 0xc0a98929a3b5a629, /* VK_EXT_subpass_merge_feedback */
    /*  156 */ 0x745c764090230a6a, /* VK_EXT_surface_maintenance1 */
    /*  157 */ 0xaf7db52f12522284, /* VK_EXT_swapchain_colorspace */
    /*  158 */ 0xb8a530fd9b6e7826, /* VK_EXT_swapchain_maintenance1 */
    /*  159 */ 0x93820a855076e9ba, /* VK_EXT_texel_buffer_alignment */
    /*  160 */ 0xd54a2906947894c3, /* VK_EXT_texture_compression_astc_hdr */
    /*  161 */ 0xa176a37fe21bf722, /* VK_EXT_tooling_info */
    /*  162 */ 0x2c77e64693cba64b, /* VK_EXT_transform_feedback */
    /*  163 */ 0xd43b5b3257938a0c, /* VK_EXT_validation_cache */
    /*  164 */ 0x32e3bcc79655ff35, /* VK_EXT_validation_features */
    /*  165 */ 0x5dbef52d8325ef00, /* VK_EXT_validation_flags */
    /*  166 */ 0x41bd31eed71de48d, /* VK_EXT_vertex_attribute_divisor */
    /*  167 */ 0x384a29f8cf6d87bf, /* VK_EXT_vertex_attribute_robustness */
    /*  168 */ 0xdba593667f2b15d8, /* VK_EXT_vertex_input_dynamic_state */
    /*  169 */ 0xdc68cb4b50c6a206, /* VK_EXT_ycbcr_2plane_444_formats */
    /*  170 */ 0x7f0e4b169ce6683e, /* VK_EXT_ycbcr_image_arrays */
    /*  171 */ 0x1d23436dd19b0471, /* VK_EXT_zero_initialize_device_memory */
    /*  172 */ 0x4ad21727cd459ae0, /* VK_FUCHSIA_buffer_collection */
    /*  173 */ 0x39a61a1dde950a7e, /* VK_FUCHSIA_external_memory */
    /*  174 */ 0xf64c61e8709735f7, /* VK_FUCHSIA_external_semaphore */
    /*  175 */ 0x78bbdf52d016b408, /* VK_FUCHSIA_imagepipe_surface */
    /*  176 */ 0x7f2da9be6e1b04db, /* VK_GGP_frame_token */
    /*  177 */ 0xcd04d110dd619891, /* VK_GGP_stream_descriptor_surface */
    /*  178 */ 0x66d124637ca67c9b, /* VK_GOOGLE_decorate_string */
    /*  179 */ 0xd317975f41d1a234, /* VK_GOOGLE_display_timing */
    /*  180 */ 0x434a8c02c305c9d2, /* VK_GOOGLE_hlsl_functionality1 */
    /*  181 */ 0xdb384c83fb23b324, /* VK_GOOGLE_surfaceless_query */
    /*  182 */ 0x8ea5be2adce92628, /* VK_GOOGLE_user_type */
    /*  183 */ 0x1251619c17f44f75, /* VK_HUAWEI_cluster_culling_shader */
    /*  184 */ 0x734dc9a82ce2a812, /* VK_HUAWEI_hdr_vivid */
    /*  185 */ 0x23cb6d9b631ae3de, /* VK_HUAWEI_invocation_mask */
    /*  186 */ 0x7a080c6eb36cfa62, /* VK_HUAWEI_subpass_shading */
    /*  187 */ 0xc831730562583c7f, /* VK_IMG_filter_cubic */
    /*  188 */ 0x2770027508eb9598, /* VK_IMG_format_pvrtc */
    /*  189 */ 0xb0257135e659f035, /* VK_IMG_relaxed_line_rasterization */
    /*  190 */ 0xde48a4b9c28f1a76, /* VK_INTEL_performance_query */
    /*  191 */ 0x1cdbef97960a8e84, /* VK_INTEL_shader_integer_functions2 */
    /*  192 */ 0x8febc131b31f03a7, /* VK_KHR_16bit_storage */
    /*  193 */ 0xfc675d0c9be11933, /* VK_KHR_8bit_storage */
    /*  194 */ 0xfd487833d05a912e, /* VK_KHR_acceleration_structure */
    /*  195 */ 0x29df4e2582c4e5eb, /* VK_KHR_android_surface */
    /*  196 */ 0xc441ac340c33f00e, /* VK_KHR_bind_memory2 */
    /*  197 */ 0xed3998734610578e, /* VK_KHR_buffer_device_address */
    /*  198 */ 0xf6b15d82867a4cc7, /* VK_KHR_calibrated_timestamps */
    /*  199 */ 0x0afe9b38bfc3ce2c, /* VK_KHR_compute_shader_derivatives */
    /*  200 */ 0x2349bf032cef96df, /* VK_KHR_cooperative_matrix */
    /*  201 */ 0x8037af99654ff021, /* VK_KHR_copy_commands2 */
    /*  202 */ 0x45e78547df004126, /* VK_KHR_create_renderpass2 */
    /*  203 */ 0x78b51eb267ba222a, /* VK_KHR_dedicated_allocation */
    /*  204 */ 0x94de08b35a6241ca, /* VK_KHR_deferred_host_operations */
    /*  205 */ 0xc379ca87fcbfe646, /* VK_KHR_depth_clamp_zero_one */
    /*  206 */ 0x8c49a14f4e053827, /* VK_KHR_depth_stencil_resolve */
    /*  207 */ 0xd0e490f381b744be, /* VK_KHR_descriptor_update_template */
    /*  208 */ 0xc6ca78c5b314bc87, /* VK_KHR_device_group */
    /*  209 */ 0x8585cbd14f1c0cac, /* VK_KHR_device_group_creation */
    /*  210 */ 0x2859d74f3639d0b1, /* VK_KHR_display */
    /*  211 */ 0xe6851c4675917263, /* VK_KHR_display_swapchain */
    /*  212 */ 0x0337556153ae8299, /* VK_KHR_draw_indirect_count */
    /*  213 */ 0x2fa1beee71b55c4a, /* VK_KHR_driver_properties */
    /*  214 */ 0xcec518255e3db5bd, /* VK_KHR_dynamic_rendering */
    /*  215 */ 0x3aff0fddef25484a, /* VK_KHR_dynamic_rendering_local_read */
    /*  216 */ 0x042831872b90006c, /* VK_KHR_external_fence */
    /*  217 */ 0x5f78dae679457682, /* VK_KHR_external_fence_capabilities */
    /*  218 */ 0xcd3a8c2ddf5addf6, /* VK_KHR_external_fence_fd */
    /*  219 */ 0x4c03e948c552a900, /* VK_KHR_external_fence_win32 */
    /*  220 */ 0x87d94faee5024129, /* VK_KHR_external_memory */
    /*  221 */ 0x3f3f36a8f61bdd88, /* VK_KHR_external_memory_capabilities */
    /*  222 */ 0x552d385fc1022139, /* VK_KHR_external_memory_fd */
    /*  223 */ 0x92cd58bc47a696d9, /* VK_KHR_external_memory_win32 */
    /*  224 */ 0x7e7e947a025884c1, /* VK_KHR_external_semaphore */
    /*  225 */ 0xb7268870e382881b, /* VK_KHR_external_semaphore_capabilities */
    /*  226 */ 0x089c9b49df8b6f1e, /* VK_KHR_external_semaphore_fd */
    /*  227 */ 0x014c9621dbd33d31, /* VK_KHR_external_semaphore_win32 */
    /*  228 */ 0x9310a82971542c4a, /* VK_KHR_format_feature_flags2 */
    /*  229 */ 0x2aedf5bc87e7dd6d, /* VK_KHR_fragment_shader_barycentric */
    /*  230 */ 0x8496cee01f4fa6d5, /* VK_KHR_fragment_shading_rate */
    /*  231 */ 0x6c023bc9dc523d46, /* VK_KHR_get_display_properties2 */
    /*  232 */ 0x9eb7bb6c3705f946, /* VK_KHR_get_memory_requirements2 */
    /*  233 */ 0x7685eeed9cac9798, /* VK_KHR_get_physical_device_properties2 */
    /*  234 */ 0x9b0fbb8eeee0e74b, /* VK_KHR_get_surface_capabilities2 */
    /*  235 */ 0x0bb91b137617fbef, /* VK_KHR_global_priority */
    /*  236 */ 0xfb7c493b280e7035, /* VK_KHR_image_format_list */
    /*  237 */ 0x6ba09c8a87af68ce, /* VK_KHR_imageless_framebuffer */
    /*  238 */ 0x76a0d6d17ae91b81, /* VK_KHR_incremental_present */
    /*  239 */ 0x3dde8d8eb0b76315, /* VK_KHR_index_type_uint8 */
    /*  240 */ 0x7928ca2523362ef3, /* VK_KHR_line_rasterization */
    /*  241 */ 0xc8692b97cfbe45ad, /* VK_KHR_load_store_op_none */
    /*  242 */ 0xe3c8335cc1581a67, /* VK_KHR_maintenance1 */
    /*  243 */ 0x8ffe792f51cd1450, /* VK_KHR_maintenance2 */
    /*  244 */ 0xea219cc76502a8af, /* VK_KHR_maintenance3 */
    /*  245 */ 0xa66e463f036dae4a, /* VK_KHR_maintenance4 */
    /*  246 */ 0xc5e86b535cee6698, /* VK_KHR_maintenance5 */
    /*  247 */ 0xf60b7de240a15ab4, /* VK_KHR_maintenance6 */
    /*  248 */ 0x3d59040ce3c13f21, /* VK_KHR_maintenance7 */
    /*  249 */ 0xb6892d36c521b488, /* VK_KHR_maintenance8 */
    /*  250 */ 0xbc9d8954b3903237, /* VK_KHR_maintenance9 */
    /*  251 */ 0x64d252cf56a64add, /* VK_KHR_map_memory2 */
    /*  252 */ 0x5af12378bc6d7169, /* VK_KHR_multiview */
    /*  253 */ 0x1bb74dfe8d7e0b31, /* VK_KHR_performance_query */
    /*  254 */ 0x935d834a6c18d3ed, /* VK_KHR_pipeline_binary */
    /*  255 */ 0x91248c6b162c4180, /* VK_KHR_pipeline_executable_properties */
    /*  256 */ 0x039c65d87fb09ca9, /* VK_KHR_pipeline_library */
    /*  257 */ 0x28644eeb112058b6, /* VK_KHR_portability_enumeration */
    /*  258 */ 0xac06576b97f9486a, /* VK_KHR_portability_subset */
    /*  259 */ 0xe82e301141092b1e, /* VK_KHR_present_id */
    /*  260 */ 0x209717f94a827c5f, /* VK_KHR_present_id2 */
    /*  261 */ 0x9ebcb805ef6af243, /* VK_KHR_present_mode_fifo_latest_ready */
    /*  262 */ 0x47954f24ddf5185e, /* VK_KHR_present_wait */
    /*  263 */ 0x2822277cba1268a0, /* VK_KHR_present_wait2 */
    /*  264 */ 0x2123bacd888c07ec, /* VK_KHR_push_descriptor */
    /*  265 */ 0x8bf873804879f2cf, /* VK_KHR_ray_query */
    /*  266 */ 0x9df3df162357e4b0, /* VK_KHR_ray_tracing_maintenance1 */
    /*  267 */ 0xaef707cb154a81af, /* VK_KHR_ray_tracing_pipeline */
    /*  268 */ 0x697f77ef7ba14203, /* VK_KHR_ray_tracing_position_fetch */
    /*  269 */ 0x4b17e19fd947a1d3, /* VK_KHR_relaxed_block_layout */
    /*  270 */ 0xaab0786abb72567a, /* VK_KHR_robustness2 */
    /*  271 */ 0x5d5e936103817cda, /* VK_KHR_sampler_mirror_clamp_to_edge */
    /*  272 */ 0x22004cfa79ba7177, /* VK_KHR_sampler_ycbcr_conversion */
    /*  273 */ 0xba2c0ae86fd11630, /* VK_KHR_separate_depth_stencil_layouts */
    /*  274 */ 0xb16f5fd69d97f3a1, /* VK_KHR_shader_atomic_int64 */
    /*  275 */ 0xd49205e9c445114a, /* VK_KHR_shader_bfloat16 */
    /*  276 */ 0xeee9708671fa7c77, /* VK_KHR_shader_clock */
    /*  277 */ 0xb35fc4bdb32f3d81, /* VK_KHR_shader_draw_parameters */
    /*  278 */ 0xab0eda6676f1fd31, /* VK_KHR_shader_expect_assume */
    /*  279 */ 0x4dad563cb513c7c9, /* VK_KHR_shader_float16_int8 */
    /*  280 */ 0x548b20a76c855b46, /* VK_KHR_shader_float_controls */
    /*  281 */ 0xa1150eef92f851e8, /* VK_KHR_shader_float_controls2 */
    /*  282 */ 0x9d14cd5379daf7cb, /* VK_KHR_shader_integer_dot_product */
    /*  283 */ 0x42aefa5598fde4ab, /* VK_KHR_shader_maximal_reconvergence */
    /*  284 */ 0xb38332d7467f8474, /* VK_KHR_shader_non_semantic_info */
    /*  285 */ 0xab3f0af6d5504bf4, /* VK_KHR_shader_quad_control */
    /*  286 */ 0x1bdfe042874be24f, /* VK_KHR_shader_relaxed_extended_instruction */
    /*  287 */ 0xcda588b0d067d48f, /* VK_KHR_shader_subgroup_extended_types */
    /*  288 */ 0xd0836c7a4d04b579, /* VK_KHR_shader_subgroup_rotate */
    /*  289 */ 0x64fbf5bc74afe199, /* VK_KHR_shader_subgroup_uniform_control_flow */
    /*  290 */ 0x6e5fde40560b40a9, /* VK_KHR_shader_terminate_invocation */
    /*  291 */ 0x9264c3e61ed27e2f, /* VK_KHR_shader_untyped_pointers */
    /*  292 */ 0x7e6871b03dee137b, /* VK_KHR_shared_presentable_image */
    /*  293 */ 0x06c03c1c3db9815d, /* VK_KHR_spirv_1_4 */
    /*  294 */ 0x743f86c26df32ea2, /* VK_KHR_storage_buffer_storage_class */
    /*  295 */ 0x2c4f009293a35548, /* VK_KHR_surface */
    /*  296 */ 0x2447a025c1b4d0ff, /* VK_KHR_surface_maintenance1 */
    /*  297 */ 0xa8506d9aef558591, /* VK_KHR_surface_protected_capabilities */
    /*  298 */ 0x6cefabf4c944ccec, /* VK_KHR_swapchain */
    /*  299 */ 0x8d650abfe09cadb2, /* VK_KHR_swapchain_maintenance1 */
    /*  300 */ 0x2149e839e759e400, /* VK_KHR_swapchain_mutable_format */
    /*  301 */ 0xf1cfa2ea69e6ec0e, /* VK_KHR_synchronization2 */
    /*  302 */ 0x61ed378f50459bf2, /* VK_KHR_timeline_semaphore */
    /*  303 */ 0xfbb615f2cdb7e18f, /* VK_KHR_unified_image_layouts */
    /*  304 */ 0x3334ed809879d360, /* VK_KHR_uniform_buffer_standard_layout */
    /*  305 */ 0x6146df22dcb09470, /* VK_KHR_variable_pointers */
    /*  306 */ 0xcfd1e6704e4a4227, /* VK_KHR_vertex_attribute_divisor */
    /*  307 */ 0x4ccc16568a9a2944, /* VK_KHR_video_decode_av1 */
    /*  308 */ 0x0093b60d00888052, /* VK_KHR_video_decode_h264 */
    /*  309 */ 0x4116f6bec0017e79, /* VK_KHR_video_decode_h265 */
    /*  310 */ 0x363dac5e35a2f1ee, /* VK_KHR_video_decode_queue */
    /*  311 */ 0xc656a5824a51a00e, /* VK_KHR_video_decode_vp9 */
    /*  312 */ 0x35e683e888a7a54c, /* VK_KHR_video_encode_av1 */
    /*  313 */ 0xa77247c5899dc785, /* VK_KHR_video_encode_h264 */
    /*  314 */ 0x8b86366e33c748ee, /* VK_KHR_video_encode_h265 */
    /*  315 */ 0x02882dc081b4a9a3, /* VK_KHR_video_encode_intra_refresh */
    /*  316 */ 0x3f1a8c895b8e8deb, /* VK_KHR_video_encode_quantization_map */
    /*  317 */ 0xdda14264a3bda234, /* VK_KHR_video_encode_queue */
    /*  318 */ 0x9fb8181989e29256, /* VK_KHR_video_maintenance1 */
    /*  319 */ 0xfd1949eb2a3c752b, /* VK_KHR_video_maintenance2 */
    /*  320 */ 0xc3d1c9b40515a6a4, /* VK_KHR_video_queue */
    /*  321 */ 0x34899ec7a7b17614, /* VK_KHR_vulkan_memory_model */
    /*  322 */ 0x906fcab3e0d202a5, /* VK_KHR_wayland_surface */
    /*  323 */ 0x19d48609837c8701, /* VK_KHR_win32_keyed_mutex */
    /*  324 */ 0xc93557e7cef43233, /* VK_KHR_win32_surface */
    /*  325 */ 0x75ee32f09cdd8db9, /* VK_KHR_workgroup_memory_explicit_layout */
    /*  326 */ 0x32a481baaa637e2c, /* VK_KHR_xcb_surface */
    /*  327 */ 0x863c0e309551346e, /* VK_KHR_xlib_surface */
    /*  328 */ 0x58d24a21f116065b, /* VK_KHR_zero_initialize_workgroup_memory */
    /*  329 */ 0x5615881540a7f6d8, /* VK_LUNARG_direct_driver_loading */
    /*  330 */ 0x6f8fb9c8b46fc189, /* VK_MESA_image_alignment_control */
    /*  331 */ 0xc1c930637836bf44, /* VK_MSFT_layered_driver */
    /*  332 */ 0x489cf2a16640d39e, /* VK_MVK_ios_surface */
    /*  333 */ 0x3274c65edf45286c, /* VK_MVK_macos_surface */
    /*  334 */ 0x53643314731ac57a, /* VK_NN_vi_surface */
    /*  335 */ 0x5bf53745255ccc0e, /* VK_NVX_binary_import */
    /*  336 */ 0x20b59934a97efd1c, /* VK_NVX_image_view_handle */
    /*  337 */ 0x112ee8733e2b22b3, /* VK_NVX_multiview_per_view_attributes */
    /*  338 */ 0x71fe862eee072b1e, /* VK_NV_acquire_winrt_display */
    /*  339 */ 0x9217a69de789d3fe, /* VK_NV_clip_space_w_scaling */
    /*  340 */ 0x5d2cfdaf5ecc308b, /* VK_NV_cluster_acceleration_structure */
    /*  341 */ 0xad1ba91484f69ca3, /* VK_NV_command_buffer_inheritance */
    /*  342 */ 0x21d19e30b520bdd6, /* VK_NV_compute_shader_derivatives */
    /*  343 */ 0x069e842b3b51cefb, /* VK_NV_cooperative_matrix */
    /*  344 */ 0xfecfd80519026209, /* VK_NV_cooperative_matrix2 */
    /*  345 */ 0x9b6d5b7725490586, /* VK_NV_cooperative_vector */
    /*  346 */ 0xce889f8d6b40e84f, /* VK_NV_copy_memory_indirect */
    /*  347 */ 0xed85b1ac0329a8cd, /* VK_NV_corner_sampled_image */
    /*  348 */ 0x81b617790445f852, /* VK_NV_coverage_reduction_mode */
    /*  349 */ 0x3644690c3bd14289, /* VK_NV_cuda_kernel_launch */
    /*  350 */ 0xbb81f8243fcc7db5, /* VK_NV_dedicated_allocation */
    /*  351 */ 0x00ce18bba106c2ad, /* VK_NV_dedicated_allocation_image_aliasing */
    /*  352 */ 0x23bcacd889bea60c, /* VK_NV_descriptor_pool_overallocation */
    /*  353 */ 0xf03dfd81ad17796f, /* VK_NV_device_diagnostic_checkpoints */
    /*  354 */ 0xc8050fbd31afc5b5, /* VK_NV_device_diagnostics_config */
    /*  355 */ 0xee7bfcd5523cff09, /* VK_NV_device_generated_commands */
    /*  356 */ 0x2ff0ded4f3f040e9, /* VK_NV_device_generated_commands_compute */
    /*  357 */ 0xc07b5e2a89ddc607, /* VK_NV_displacement_micromap */
    /*  358 */ 0x5138c2f68bcb3608, /* VK_NV_display_stereo */
    /*  359 */ 0xb2344e462fd9ef1b, /* VK_NV_extended_sparse_address_space */
    /*  360 */ 0xd15b433c649fb093, /* VK_NV_external_compute_queue */
    /*  361 */ 0xab0f59a00375b1ec, /* VK_NV_external_memory */
    /*  362 */ 0x518148eb9166b4b9, /* VK_NV_external_memory_capabilities */
    /*  363 */ 0x3c96386b301a3cdc, /* VK_NV_external_memory_rdma */
    /*  364 */ 0xcf69c3e7cbd068e4, /* VK_NV_external_memory_win32 */
    /*  365 */ 0xdf9a65a432a12606, /* VK_NV_fill_rectangle */
    /*  366 */ 0x9a6fda1e2f4f9096, /* VK_NV_fragment_coverage_to_color */
    /*  367 */ 0xc294d55a56858fb6, /* VK_NV_fragment_shader_barycentric */
    /*  368 */ 0x2ece12f465807058, /* VK_NV_fragment_shading_rate_enums */
    /*  369 */ 0x4caba51b111c61b9, /* VK_NV_framebuffer_mixed_samples */
    /*  370 */ 0xe0c4918343f3874c, /* VK_NV_geometry_shader_passthrough */
    /*  371 */ 0xd659873b3f6bc024, /* VK_NV_glsl_shader */
    /*  372 */ 0xe39346d87fc9aa45, /* VK_NV_inherited_viewport_scissor */
    /*  373 */ 0x52fcc4c2d713dad4, /* VK_NV_linear_color_attachment */
    /*  374 */ 0xb58daf9c015becf7, /* VK_NV_low_latency */
    /*  375 */ 0xa9eb852dfd7a1ece, /* VK_NV_low_latency2 */
    /*  376 */ 0x6c878fdbf1e4a7fb, /* VK_NV_memory_decompression */
    /*  377 */ 0x7401a89f84bc926b, /* VK_NV_mesh_shader */
    /*  378 */ 0x929112526891454e, /* VK_NV_optical_flow */
    /*  379 */ 0x6e9d1f60324c4761, /* VK_NV_partitioned_acceleration_structure */
    /*  380 */ 0x5e0416a20f89c9f4, /* VK_NV_per_stage_descriptor_set */
    /*  381 */ 0x48102b2d563a8028, /* VK_NV_present_barrier */
    /*  382 */ 0xe16f6927a8473cab, /* VK_NV_present_metering */
    /*  383 */ 0xc20950e0cbc5bdc0, /* VK_NV_raw_access_chains */
    /*  384 */ 0x3d4e9e0bb54735fe, /* VK_NV_ray_tracing */
    /*  385 */ 0xe12f14699c6db9db, /* VK_NV_ray_tracing_invocation_reorder */
    /*  386 */ 0x4157611d54ac1bc1, /* VK_NV_ray_tracing_linear_swept_spheres */
    /*  387 */ 0xba4184e5104338cb, /* VK_NV_ray_tracing_motion_blur */
    /*  388 */ 0x451532c42bd881b2, /* VK_NV_ray_tracing_validation */
    /*  389 */ 0x92ccabdfa0a3d6e4, /* VK_NV_representative_fragment_test */
    /*  390 */ 0xc4d99252b7b7843f, /* VK_NV_sample_mask_override_coverage */
    /*  391 */ 0xd4d2cda699fc74ae, /* VK_NV_scissor_exclusive */
    /*  392 */ 0xb8974b1af4c34b58, /* VK_NV_shader_atomic_float16_vector */
    /*  393 */ 0x52f9f98f09f18085, /* VK_NV_shader_image_footprint */
    /*  394 */ 0xc394473a75e21d7c, /* VK_NV_shader_sm_builtins */
    /*  395 */ 0x5b6c5e76d8a8364e, /* VK_NV_shader_subgroup_partitioned */
    /*  396 */ 0xcac204d487e563d3, /* VK_NV_shading_rate_image */
    /*  397 */ 0xfc6e35d06ddf634e, /* VK_NV_viewport_array2 */
    /*  398 */ 0x7748ea26eecd7e90, /* VK_NV_viewport_swizzle */
    /*  399 */ 0x7e4ac6b10102b887, /* VK_NV_win32_keyed_mutex */
    /*  400 */ 0xfb89dacebce47785, /* VK_OHOS_surface */
    /*  401 */ 0x5c76ad884426c86c, /* VK_QCOM_filter_cubic_clamp */
    /*  402 */ 0xc7386bbfd1b9b423, /* VK_QCOM_filter_cubic_weights */
    /*  403 */ 0xff445069da66b635, /* VK_QCOM_fragment_density_map_offset */
    /*  404 */ 0xa6cab4106375cdfa, /* VK_QCOM_image_processing */
    /*  405 */ 0xa4a1ae34c2527a4a, /* VK_QCOM_image_processing2 */
    /*  406 */ 0xbff750af2234e2ce, /* VK_QCOM_multiview_per_view_render_areas */
    /*  407 */ 0x876a51c6df08420a, /* VK_QCOM_multiview_per_view_viewports */
    /*  408 */ 0xa3b4fc40f185c799, /* VK_QCOM_render_pass_shader_resolve */
    /*  409 */ 0x9b5c2a0bc41e00cd, /* VK_QCOM_render_pass_store_ops */
    /*  410 */ 0x8d33cd618c723019, /* VK_QCOM_render_pass_transform */
    /*  411 */ 0xd5a3f971e2e8b5c9, /* VK_QCOM_rotated_copy_commands */
    /*  412 */ 0x73244ac23f3ec04a, /* VK_QCOM_tile_memory_heap */
    /*  413 */ 0xc37b456dbdf5565f, /* VK_QCOM_tile_properties */
    /*  414 */ 0x80b039482dfe4631, /* VK_QCOM_tile_shading */
    /*  415 */ 0x49bfbd9f92e0b029, /* VK_QCOM_ycbcr_degamma */
    /*  416 */ 0xc2e6f6dcc7614ace, /* VK_QNX_external_memory_screen_buffer */
    /*  417 */ 0x236bd86b3b17cf06, /* VK_QNX_screen_surface */
    /*  418 */ 0xe6fed416ddebf8d0, /* VK_SEC_amigo_profiling */
    /*  419 */ 0x8501d958b34af871, /* VK_SEC_pipeline_cache_incremental_mode */
    /*  420 */ 0x45542cac22bd41a7, /* VK_VALVE_descriptor_set_host_mapping */
    /*  421 */ 0x7aab48db428bd31b, /* VK_VALVE_fragment_density_map_layered */
    /*  422 */ 0x38c73d4ab66a4942, /* VK_VALVE_mutable_descriptor_type */
    /*  423 */ 0x5674ed8bc838fecb  /* VK_VALVE_video_encode_rgb_conversion */
};

static void glad_vk_load_pfn_range(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr, uint16_t pfnStart, uint32_t numPfns)
{
    uint32_t pfnIdx;

    #ifdef __clang__
    #pragma nounroll
    #endif
    for (pfnIdx = pfnStart; pfnIdx < pfnStart + numPfns; ++pfnIdx) {
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static uint32_t glad_vk_resolve_alias_group(GladVulkanContext *context, const GladAliasPair_t *pairs, uint32_t start_idx, uint32_t total_count) {
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

static void glad_vk_resolve_aliases(GladVulkanContext *context) {
    static const GladAliasPair_t s_aliases[] = {
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
    uint32_t i;

    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < GLAD_ARRAYSIZE(s_aliases); ++i) {
        i = glad_vk_resolve_alias_group(context, s_aliases, i, GLAD_ARRAYSIZE(s_aliases));
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

static GLADapiproc glad_vk_get_proc_from_userptr(void *userptr, const char* name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
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

    #ifdef __clang__
    #pragma nounroll
    #endif
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

GLAD_NO_INLINE int gladLoadVulkanContextUserPtr(GladVulkanContext *context, VkInstance instance, VkPhysicalDevice physical_device, VkDevice device, GLADuserptrloadfunc load, void *userptr) {
    int version;
    uint32_t i;

    (void)instance;
    (void)device;

#ifdef VK_VERSION_1_1
    context->EnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion)load(userptr, "vkEnumerateInstanceVersion");
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

int gladLoadVulkanUserPtr(VkInstance instance, VkPhysicalDevice physical_device, VkDevice device, GLADuserptrloadfunc load, void *userptr) {
    return gladLoadVulkanContextUserPtr(gladGetVulkanContext(), instance, physical_device, device, load, userptr);
}

int gladLoadVulkanContext(GladVulkanContext *context, VkInstance instance, VkPhysicalDevice physical_device, VkDevice device, GLADloadfunc load) {
    return gladLoadVulkanContextUserPtr(context, instance, physical_device, device, glad_vk_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}

int gladLoadVulkan(VkInstance instance, VkPhysicalDevice physical_device, VkDevice device, GLADloadfunc load) {
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

static uint64_t GLAD_Vulkan_device_commands[] = {
    0x003f01982149c676, /* vkQueuePresentKHR */
    0x0198a65d97d8c9de, /* vkCmdSetViewportWithCount */
    0x02eb4358362cbe5f, /* vkCmdCopyImageToBuffer2KHR */
    0x03c070149bc4adcf, /* vkAllocateCommandBuffers */
    0x03e8b953ae4cc537, /* vkCmdEndRenderPass */
    0x04134f0c5694394f, /* vkGetSwapchainCounterEXT */
    0x0602c29db03eb8ab, /* vkGetShaderModuleIdentifierEXT */
    0x076d9ee8752c3cd2, /* vkGetPipelineIndirectDeviceAddressNV */
    0x07982f27d5cc9e3d, /* vkCmdCopyMicromapEXT */
    0x07b8ecf11f0a147a, /* vkCmdCopyImageToBuffer2 */
    0x0802604e7494d3a4, /* vkGetRayTracingShaderGroupHandlesKHR */
    0x085d172fa3bb5527, /* vkCmdSetExclusiveScissorEnableNV */
    0x093d8596adfdb576, /* vkCmdBindPipeline */
    0x09bcf6218bf7a7cc, /* vkCmdCopyMemoryToMicromapEXT */
    0x09d5feddc371e187, /* vkCmdNextSubpass2 */
    0x09da53bc6b918573, /* vkCmdDebugMarkerInsertEXT */
    0x09e9bc32d119dd75, /* vkReleaseSwapchainImagesEXT */
    0x09f73ab4947aa834, /* vkCmdSetDepthBoundsTestEnableEXT */
    0x0a9e4edad7617bf4, /* vkReleaseProfilingLockKHR */
    0x0b4161174ca14c67, /* vkCopyMicromapToMemoryEXT */
    0x0b635494ffc80076, /* vkCmdSetDeviceMask */
    0x0baf9d7df0a788b5, /* vkUpdateVideoSessionParametersKHR */
    0x0c3e489641018fd0, /* vkQueueSubmit */
    0x0c4f4995392e50ab, /* vkGetCalibratedTimestampsKHR */
    0x0c7a936d63d4b37e, /* vkCmdSetStencilOpEXT */
    0x0c92251840d35fc4, /* vkDestroyTensorARM */
    0x0d4c393e3bfb6e8f, /* vkGetGeneratedCommandsMemoryRequirementsEXT */
    0x0e2e5dfee87cb6bc, /* vkGetAndroidHardwareBufferPropertiesANDROID */
    0x0e4eac678a76ed33, /* vkGetDeviceBufferMemoryRequirementsKHR */
    0x0f70146a40b73eaf, /* vkCmdInsertDebugUtilsLabelEXT */
    0x0f7af59845222e9d, /* vkGetDescriptorSetLayoutSupportKHR */
    0x1028e41b255d6802, /* vkCmdDrawIndirectByteCountEXT */
    0x10635a7a4fcc2c76, /* vkGetValidationCacheDataEXT */
    0x10cb3a8400778673, /* vkCmdSetLineStippleEXT */
    0x110bf15d39ef5684, /* vkCmdResolveImage2 */
    0x1173dfede1e58b0e, /* vkAcquirePerformanceConfigurationINTEL */
    0x11a78b6266b8d57c, /* vkWriteMicromapsPropertiesEXT */
    0x126d3121c5d14c5f, /* vkCreatePrivateDataSlot */
    0x12ca3f3ec96315f3, /* vkCmdSetCoarseSampleOrderNV */
    0x12e6b027ea2149c2, /* vkGetMemoryFdPropertiesKHR */
    0x13672ea08d07fa9d, /* vkCmdDrawMultiEXT */
    0x140ab11fc9190c09, /* vkGetSemaphoreFdKHR */
    0x1441dbc95c1af085, /* vkCmdWaitEvents */
    0x146940f88e38657b, /* vkGetBufferMemoryRequirements2 */
    0x149123ece151c923, /* vkCmdSubpassShadingHUAWEI */
    0x15aae27a7223ea5e, /* vkGetDeviceBufferMemoryRequirements */
    0x15b0ebcd4268ceb0, /* vkCmdDrawMultiIndexedEXT */
    0x1660d6d65602a1e2, /* vkCmdDrawMeshTasksEXT */
    0x166f6358bfe0fce0, /* vkGetDeviceFaultInfoEXT */
    0x16a20753b1174318, /* vkCreateImage */
    0x172c55dd5dc1bc3a, /* vkCmdSetDepthClipEnableEXT */
    0x17bb294acabe6a88, /* vkGetPipelineCacheData */
    0x17f9a371c7111a63, /* vkCmdSetColorBlendEnableEXT */
    0x1812390287e35f0c, /* vkCmdEndConditionalRenderingEXT */
    0x1965935ee47e88e6, /* vkCmdResetQueryPool */
    0x19f19eb801eb4fea, /* vkCopyMemoryToMicromapEXT */
    0x1ae7324660591b8f, /* vkDestroyPipelineCache */
    0x1b250d8529b8c649, /* vkGetImageViewHandleNVX */
    0x1b435983eb84abaa, /* vkCmdDrawIndirectCount */
    0x1b8ec29acf8f9c34, /* vkCmdWaitEvents2KHR */
    0x1be0142d7b82c8c3, /* vkCreateRayTracingPipelinesKHR */
    0x1c4feae5ecde76d9, /* vkCmdDecompressMemoryNV */
    0x1c9c24ff8ad40bf7, /* vkDestroySampler */
    0x1ce083dfe13eae46, /* vkCmdExecuteCommands */
    0x1ce7a67a576268eb, /* vkCmdSetStencilOp */
    0x1d4114fa0cce1718, /* vkCmdDrawIndexedIndirectCount */
    0x1d7e628cb67db142, /* vkCmdCopyAccelerationStructureNV */
    0x1d81583e5255fa64, /* vkCmdBindDescriptorSets2 */
    0x1de7b0458bd04513, /* vkCmdSetDepthBiasEnable */
    0x1de9fd31feb0f22f, /* vkDeviceWaitIdle */
    0x1def9e89a041b817, /* vkCmdSetDepthClipNegativeOneToOneEXT */
    0x1e001d1f829f257b, /* vkBindBufferMemory2 */
    0x1e31e79e5158a92a, /* vkCmdSetCoverageModulationModeNV */
    0x1e931402fc057014, /* vkResetCommandPool */
    0x1ebd0c97c69da82b, /* vkUpdateDescriptorSetWithTemplate */
    0x1fce1bdecaf06b52, /* vkQueueWaitIdle */
    0x203c934aa0f948fc, /* vkCmdFillBuffer */
    0x204df3e556149586, /* vkCmdCopyBuffer */
    0x20681e0c6bf30380, /* vkCmdEndTransformFeedbackEXT */
    0x20a57b855bed16ad, /* vkCmdEndRenderingKHR */
    0x20e1f9030911f404, /* vkCmdSetRayTracingPipelineStackSizeKHR */
    0x20e538050b42f767, /* vkCmdSetRasterizerDiscardEnableEXT */
    0x2123cc5e1c438312, /* vkCmdPushDescriptorSetKHR */
    0x213f8b33c25f4ec9, /* vkCmdBindShadersEXT */
    0x21e4a7d810574ab7, /* vkGetImageSparseMemoryRequirements */
    0x21f4e40d1b10ea20, /* vkRegisterDisplayEventEXT */
    0x22466386cc1398b8, /* vkDestroySwapchainKHR */
    0x22611ab44638175f, /* vkQueueSetPerformanceConfigurationINTEL */
    0x22aa0793e66f037d, /* vkCmdResolveImage */
    0x233da64d987f39c6, /* vkTransitionImageLayoutEXT */
    0x234a880591facce1, /* vkResetFences */
    0x2384403e82f430b9, /* vkSetPrivateData */
    0x238991922eb2dc5f, /* vkCopyImageToImageEXT */
    0x2391b4f29bdf37b3, /* vkGetMemoryMetalHandleEXT */
    0x23d7885b70c5f681, /* vkGetImageSubresourceLayout */
    0x24683f73b0e5e597, /* vkGetDeviceQueue */
    0x24975600fb49fd73, /* vkCmdBindTransformFeedbackBuffersEXT */
    0x24f886fa5cebd7ed, /* vkCmdSetLineStippleKHR */
    0x25cbce2cf01ae221, /* vkCopyImageToMemory */
    0x25e2c1a1ae2efd24, /* vkCmdSetDepthWriteEnableEXT */
    0x25f6d470c53abf71, /* vkGetDescriptorSetLayoutSupport */
    0x26037ce5b636f47f, /* vkGetImageViewOpaqueCaptureDescriptorDataEXT */
    0x269c5788bd9937d1, /* vkAcquireFullScreenExclusiveModeEXT */
    0x26c37395ff9739bc, /* vkCmdSetViewportShadingRatePaletteNV */
    0x271a389035d7932e, /* vkCmdBindTileMemoryQCOM */
    0x272dc15f9cab3de4, /* vkGetExecutionGraphPipelineScratchSizeAMDX */
    0x2959ea9ac9517bb5, /* vkCreateCudaFunctionNV */
    0x2ad0e3cb5f37720f, /* vkGetShaderModuleCreateInfoIdentifierEXT */
    0x2b78093ae32cb916, /* vkCmdSetRepresentativeFragmentTestEnableNV */
    0x2bd217fc8713bb23, /* vkDisplayPowerControlEXT */
    0x2c457bf2268490e8, /* vkGetBufferCollectionPropertiesFUCHSIA */
    0x2c685c0a5e9fbef2, /* vkDestroySamplerYcbcrConversion */
    0x2c6e7da8d69f6259, /* vkGetImageViewAddressNVX */
    0x2ca882d31d4721ba, /* vkCmdSetShadingRateImageEnableNV */
    0x2d831a042e0d1b62, /* vkBuildAccelerationStructuresKHR */
    0x2e0b5702efb33535, /* vkResetEvent */
    0x2e9f27714c27c160, /* vkCmdWriteTimestamp2KHR */
    0x2ed27a2c09707e8c, /* vkCopyMemoryToAccelerationStructureKHR */
    0x2ed749f13375a993, /* vkGetMemoryFdKHR */
    0x2f2449681e594992, /* vkGetBufferOpaqueCaptureDescriptorDataEXT */
    0x31070cdf29394f00, /* vkBuildMicromapsEXT */
    0x31241535b9bc3b52, /* vkCmdCopyMicromapToMemoryEXT */
    0x315127945d495884, /* vkCmdDispatchBaseKHR */
    0x316bebcfe32855b8, /* vkGetDeviceMemoryOpaqueCaptureAddressKHR */
    0x31f122b7cfd4bda7, /* vkGetImageMemoryRequirements */
    0x32e6d8b01681a0b2, /* vkGetDeviceGroupSurfacePresentModesKHR */
    0x3339f46d399c78c5, /* vkAllocateMemory */
    0x333e4270d99c5326, /* vkCmdPushDescriptorSetWithTemplate2 */
    0x334314efb11c7144, /* vkImportSemaphoreZirconHandleFUCHSIA */
    0x335573b897d8b48c, /* vkCmdSetFrontFaceEXT */
    0x338a1ed4b2ca0c7a, /* vkCmdCopyAccelerationStructureKHR */
    0x33f6b7087e67dab4, /* vkCmdSetViewport */
    0x34455b16a968d1f7, /* vkTransitionImageLayout */
    0x3446c4b0e0ed13c7, /* vkGetPipelineBinaryDataKHR */
    0x345a6d44742dd550, /* vkUnmapMemory2KHR */
    0x34bfbbd6c34bac46, /* vkMapMemory2KHR */
    0x34c3a6eee5758a70, /* vkGetVideoSessionMemoryRequirementsKHR */
    0x352e0ca38b5e29c0, /* vkDestroyQueryPool */
    0x355f705d4d835c02, /* vkCmdControlVideoCodingKHR */
    0x358c26001c7dea62, /* vkCmdSetEvent2 */
    0x35a324447b0101e4, /* vkSetHdrMetadataEXT */
    0x35ddb5f0819f35bf, /* vkCmdSetCheckpointNV */
    0x36135fe5c54d3b34, /* vkCmdBindShadingRateImageNV */
    0x3683952ff1e39c69, /* vkGetMicromapBuildSizesEXT */
    0x36d94ea1570378f7, /* vkSetBufferCollectionBufferConstraintsFUCHSIA */
    0x36da6959c46b24dd, /* vkDestroyDescriptorUpdateTemplateKHR */
    0x371cc0f681367e4d, /* vkCmdSetStencilCompareMask */
    0x37569a6dd4dad322, /* vkCmdPreprocessGeneratedCommandsEXT */
    0x37cec3d3b8dc3838, /* vkGetDeviceQueue2 */
    0x38512bbacb368b24, /* vkCreateFramebuffer */
    0x387f685e13e513fa, /* vkCmdClearDepthStencilImage */
    0x38f59a81a499abec, /* vkCmdBlitImage */
    0x3934d6b188f309ea, /* vkCreateTensorARM */
    0x39595c56305c625a, /* vkGetDeviceProcAddr */
    0x399268bd1fae323b, /* vkGetBufferDeviceAddressEXT */
    0x3a0a07834723853e, /* vkInvalidateMappedMemoryRanges */
    0x3a28620bd767d9f5, /* vkCmdSetRenderingAttachmentLocations */
    0x3a88835e421d53cd, /* vkDestroyMicromapEXT */
    0x3ac504ab87b15a1d, /* vkCmdDrawMeshTasksIndirectCountEXT */
    0x3cb127add67d0963, /* vkCmdSetDescriptorBufferOffsetsEXT */
    0x3ce0faf5d18dc25b, /* vkCreateAccelerationStructureNV */
    0x3d1c41fb25426f73, /* vkCmdBeginPerTileExecutionQCOM */
    0x3d8f82b873097a02, /* vkGetQueueCheckpointDataNV */
    0x3e094de8a08c3145, /* vkGetImageMemoryRequirements2KHR */
    0x3e52d6e9d1662eb2, /* vkEndCommandBuffer */
    0x3e53232e3bd1b97c, /* vkDestroyExternalComputeQueueNV */
    0x3f4274cc71793a20, /* vkGetDeviceImageMemoryRequirements */
    0x3fab09299e5024e6, /* vkBindImageMemory */
    0x40648ed2af7eecdd, /* vkResetQueryPoolEXT */
    0x4067528a7c46d3d1, /* vkGetDeviceMicromapCompatibilityEXT */
    0x4092cc86b9e7806e, /* vkCmdBuildAccelerationStructureNV */
    0x40db28be40a6f866, /* vkCmdTraceRaysIndirect2KHR */
    0x40f65d68942eb094, /* vkGetDeviceMemoryCommitment */
    0x410043fbd97c4c0d, /* vkDestroyDescriptorUpdateTemplate */
    0x41319d7151e3be68, /* vkGetMemoryMetalHandlePropertiesEXT */
    0x41a01ed27bc041f2, /* vkCmdCopyMemoryToImageIndirectNV */
    0x423629691279d2c9, /* vkGetDeviceImageSparseMemoryRequirementsKHR */
    0x429417467467b909, /* vkCmdSetExclusiveScissorNV */
    0x438e5b6a754df791, /* vkCmdCopyImage */
    0x43962ea5cc322bab, /* vkQueueNotifyOutOfBandNV */
    0x44fbf4ea4b060b61, /* vkGetBufferDeviceAddress */
    0x44fcf619d29aa8fa, /* vkDestroyDescriptorSetLayout */
    0x452970172a23c174, /* vkCreateAccelerationStructureKHR */
    0x45568382cd976a58, /* vkGetGeneratedCommandsMemoryRequirementsNV */
    0x45e8058b548405ce, /* vkGetImageViewHandle64NVX */
    0x4633e10f15501242, /* vkGetPartitionedAccelerationStructuresBuildSizesNV */
    0x464cdf5591d873eb, /* vkWaitSemaphores */
    0x46bd70f746f4073f, /* vkDestroyCudaModuleNV */
    0x47176b0b432286d1, /* vkCreateBuffer */
    0x47b5e34bc173355d, /* vkCmdPipelineBarrier2KHR */
    0x47d826cf3a236677, /* vkBeginCommandBuffer */
    0x480770881849ff9e, /* vkReleasePerformanceConfigurationINTEL */
    0x482cb3433b920f78, /* vkGetPipelineExecutableInternalRepresentationsKHR */
    0x483734fdc78b4c60, /* vkCmdEndPerTileExecutionQCOM */
    0x484c4c652a1f9c0e, /* vkCmdClearAttachments */
    0x4852117a823da29e, /* vkGetImageOpaqueCaptureDescriptorDataEXT */
    0x4888445b33d1d1a9, /* vkCmdSetPerformanceMarkerINTEL */
    0x48e9ce5a58c1c252, /* vkCmdSetPolygonModeEXT */
    0x49a74d66be4fce8b, /* vkGetCalibratedTimestampsEXT */
    0x49bda364217fc34a, /* vkGetPerformanceParameterINTEL */
    0x4afe44fc10e34214, /* vkCmdCopyBufferToImage */
    0x4b8501185d9a396d, /* vkCreateDataGraphPipelinesARM */
    0x4b963cb16d7a5ad8, /* vkCmdSetTessellationDomainOriginEXT */
    0x4bfeea912504df47, /* vkDestroyVideoSessionKHR */
    0x4c2e756549427154, /* vkCmdPushDescriptorSet2 */
    0x4c351cfa990e9dce, /* vkCmdSetAlphaToCoverageEnableEXT */
    0x4d0e89b321a6faef, /* vkCreateRayTracingPipelinesNV */
    0x4d3f08ecfb5c4893, /* vkCmdCopyBuffer2KHR */
    0x4d5e5f4d1d17b29c, /* vkCreateDataGraphPipelineSessionARM */
    0x4e7d037aae3a3033, /* vkCmdDispatchGraphIndirectAMDX */
    0x4e9ad990677f931c, /* vkGetEventStatus */
    0x4f323238bf52cee6, /* vkGetSemaphoreCounterValueKHR */
    0x4fdb2f0ce0346b73, /* vkCmdSetLogicOpEXT */
    0x5001dcd798e4f3a8, /* vkGetPipelineExecutableStatisticsKHR */
    0x509b9755d54a9a1e, /* vkCreateQueryPool */
    0x52bc0c7023b88e90, /* vkCmdSetDepthClampEnableEXT */
    0x5365aba2c3922f6a, /* vkCmdPipelineBarrier2 */
    0x536ddebd6b81d90a, /* vkCreateSwapchainKHR */
    0x538223e2090de1df, /* vkCmdSetExtraPrimitiveOverestimationSizeEXT */
    0x540370e7058dd6ac, /* vkCmdBindIndexBuffer2 */
    0x54f4e0d0a5c3dbbf, /* vkCmdSetVertexInputEXT */
    0x5639c874fc9132f4, /* vkGetBufferOpaqueCaptureAddress */
    0x56698661adbb7534, /* vkCmdDrawMeshTasksIndirectNV */
    0x568b92e4b678bc0d, /* vkGetCudaModuleCacheNV */
    0x56e0a0791533454f, /* vkCmdBuildAccelerationStructuresKHR */
    0x5736d06f9f7521f5, /* vkCreateShadersEXT */
    0x599380d76631dbc9, /* vkCmdNextSubpass2KHR */
    0x59e3b39cfad2a148, /* vkCmdUpdatePipelineIndirectBufferNV */
    0x5a4a030363a95dd6, /* vkCreateGraphicsPipelines */
    0x5a7b2addceb670c9, /* vkCmdSetPrimitiveRestartEnable */
    0x5ad7e13a5109c73a, /* vkCopyAccelerationStructureKHR */
    0x5c738ec563b80923, /* vkCmdSetEvent */
    0x5c965829c780d9f3, /* vkGetAccelerationStructureMemoryRequirementsNV */
    0x5ca8d012ffb54c19, /* vkGetTensorViewOpaqueCaptureDescriptorDataARM */
    0x5d404fade6187f05, /* vkCmdSetDescriptorBufferOffsets2EXT */
    0x5d99174ab12822bd, /* vkGetSamplerOpaqueCaptureDescriptorDataEXT */
    0x5dcda38c668184b8, /* vkGetPastPresentationTimingGOOGLE */
    0x5dd077e15ef82882, /* vkCmdBindInvocationMaskHUAWEI */
    0x5de8076ffb7af976, /* vkGetBufferOpaqueCaptureAddressKHR */
    0x5df941fbd5ee53ed, /* vkGetSwapchainStatusKHR */
    0x5e156baf498f5138, /* vkDestroyPipelineBinaryKHR */
    0x5e82c425367c6366, /* vkSetLatencyMarkerNV */
    0x5ee0b29b506c2241, /* vkCmdSetRasterizerDiscardEnable */
    0x5ee3413a16ecc62a, /* vkGetMemoryRemoteAddressNV */
    0x5f79fd00863c735c, /* vkCreateCudaModuleNV */
    0x60464991fe32093e, /* vkQueueSubmit2 */
    0x611ba0d146ed962c, /* vkBindOpticalFlowSessionImageNV */
    0x6124012503a7634c, /* vkSetDeviceMemoryPriorityEXT */
    0x6172f26a7ff5e461, /* vkCmdWriteTimestamp2 */
    0x620e4a899bc7e882, /* vkTrimCommandPool */
    0x625a40f7eba64825, /* vkGetDataGraphPipelineSessionMemoryRequirementsARM */
    0x62692fbaea06e05d, /* vkGetBufferDeviceAddressKHR */
    0x6333940945f764eb, /* vkCopyMemoryToImage */
    0x6400678c24bf7d34, /* vkDestroyEvent */
    0x6474b3f3a4539ee3, /* vkCreatePipelineCache */
    0x656d8617bf4a33fc, /* vkGetImageSubresourceLayout2 */
    0x658b77dd8968ff3b, /* vkCmdDrawIndirectCountAMD */
    0x659cd4a0990430f6, /* vkCmdSetConservativeRasterizationModeEXT */
    0x666e9050d505a21c, /* vkCmdBuildClusterAccelerationStructureIndirectNV */
    0x6688394878be035e, /* vkGetDescriptorSetLayoutBindingOffsetEXT */
    0x668f24a3147926db, /* vkCmdBindIndexBuffer */
    0x66d07f2af74e8d8b, /* vkGetQueueCheckpointData2NV */
    0x6756af5e610d6533, /* vkQueueEndDebugUtilsLabelEXT */
    0x67d5c823a6e5f838, /* vkDestroyIndirectCommandsLayoutNV */
    0x68a8fbded268189e, /* vkCmdEncodeVideoKHR */
    0x6987d1107990db8b, /* vkGetPipelinePropertiesEXT */
    0x6a0ad52ae1fd239d, /* vkSignalSemaphore */
    0x6a987f9eb7d4a557, /* vkCmdSetDeviceMaskKHR */
    0x6aa7b18e001aa3e3, /* vkCmdSetScissorWithCountEXT */
    0x6ac16d77f8579056, /* vkCmdResetEvent */
    0x6af432892c9a71c2, /* vkCmdCopyBuffer2 */
    0x6b0e217ae8f0f1ac, /* vkCmdDraw */
    0x6b902433192f7f5d, /* vkGetQueryPoolResults */
    0x6c52ced389956a1d, /* vkGetAccelerationStructureBuildSizesKHR */
    0x6cd2fae1ab9c9a75, /* vkCmdPushDescriptorSetWithTemplate */
    0x6d4934759c97e7a4, /* vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT */
    0x6e0d98ae9ace40d5, /* vkBindAccelerationStructureMemoryNV */
    0x6f91a0562614466e, /* vkAllocateDescriptorSets */
    0x6fde01fd66c6087a, /* vkCmdBindIndexBuffer2KHR */
    0x70cfd8006341080a, /* vkGetMemoryHostPointerPropertiesEXT */
    0x70f16cd080e5a1e1, /* vkCreateCuModuleNVX */
    0x714129686c9da431, /* vkCreateExecutionGraphPipelinesAMDX */
    0x71b8cb2fd8159c3d, /* vkUpdateDescriptorSetWithTemplateKHR */
    0x71bb8068c1edf85e, /* vkDestroyDeferredOperationKHR */
    0x71d79d686f22d526, /* vkCmdTraceRaysKHR */
    0x724faacf94fc9fe1, /* vkGetImageSubresourceLayout2EXT */
    0x7282c5dadf99206c, /* vkCreateRenderPass2KHR */
    0x73239ae79c84cd85, /* vkCreateSharedSwapchainsKHR */
    0x735a3459f80339e7, /* vkCmdSetLogicOpEnableEXT */
    0x7379abd10f3bfb5d, /* vkDeferredOperationJoinKHR */
    0x73bc2739d085085f, /* vkCmdBeginConditionalRenderingEXT */
    0x73f1f198f822a45e, /* vkTrimCommandPoolKHR */
    0x74655211ce6abb4b, /* vkCmdSetDepthBias */
    0x753af4a2035f5325, /* vkCmdDrawClusterIndirectHUAWEI */
    0x75dc79c2cde7708a, /* vkBindBufferMemory */
    0x75e32a36acf72579, /* vkCmdWriteBufferMarkerAMD */
    0x75fdc7101f295d5d, /* vkCmdResetEvent2 */
    0x75ffe5f7fd486bdd, /* vkCmdDrawIndexedIndirect */
    0x76251e96c107a873, /* vkDestroyDataGraphPipelineSessionARM */
    0x7629dff55e4d0af3, /* vkSetLocalDimmingAMD */
    0x76b72b76ccef2958, /* vkDestroyImageView */
    0x76e7d06d87565b38, /* vkCreatePipelineLayout */
    0x77298a207cf7470a, /* vkCmdSetPatchControlPointsEXT */
    0x77ac813268762693, /* vkGetBufferMemoryRequirements2KHR */
    0x7937cbd95db509a9, /* vkCmdSetDepthClampRangeEXT */
    0x79bbe5a8a2c19b65, /* vkCmdSetSampleMaskEXT */
    0x79cca6cf07ff9d67, /* vkCmdSetDepthBounds */
    0x7a423d05d8869f5e, /* vkCmdCopyTensorARM */
    0x7b3f73b0c28b9ac0, /* vkCmdSetRasterizationStreamEXT */
    0x7b5bca3ce9a7ccca, /* vkCmdPushConstants2 */
    0x7b8f5cb6ad62ff2c, /* vkCreatePipelineBinariesKHR */
    0x7c1238295eaa98e9, /* vkWaitForFences */
    0x7cb7f1711b397e5f, /* vkDestroyShaderModule */
    0x7ce4de962da7bc16, /* vkCmdSetStencilWriteMask */
    0x7d12fe073f7c9462, /* vkCmdSetStencilTestEnable */
    0x7ecb7451a7e045ed, /* vkFreeCommandBuffers */
    0x7eff5818fce6b445, /* vkQueueSubmit2KHR */
    0x7f028870dfbbd7cd, /* vkGetFenceFdKHR */
    0x7f231d810d3308b5, /* vkLatencySleepNV */
    0x7fd35824391d47a4, /* vkSetDebugUtilsObjectTagEXT */
    0x7fd56c16def98a17, /* vkGetTensorOpaqueCaptureDescriptorDataARM */
    0x8055346a0f097869, /* vkCmdDispatchTileQCOM */
    0x808f7434b0596604, /* vkMapMemory */
    0x80ad81694be917a9, /* vkCreateValidationCacheEXT */
    0x80bb22834c81711a, /* vkFreeDescriptorSets */
    0x8130a83ccd423f02, /* vkCreateIndirectCommandsLayoutEXT */
    0x814945b3834b2f13, /* vkQueueBindSparse */
    0x81a2503b2e89f09e, /* vkCmdSetPerformanceOverrideINTEL */
    0x81a460bb5df2fb6c, /* vkCmdSetEvent2KHR */
    0x81f991d1ab0bc5ce, /* vkAcquireNextImage2KHR */
    0x821ae6559b48f066, /* vkGetMemoryAndroidHardwareBufferANDROID */
    0x8284d04d0f439b7f, /* vkCmdSetRenderingInputAttachmentIndicesKHR */
    0x82aa0c1dfdcefd1f, /* vkGetTensorMemoryRequirementsARM */
    0x844e6fc97d32338d, /* vkCmdPushConstants2KHR */
    0x85a37e4af2a5d369, /* vkGetAccelerationStructureDeviceAddressKHR */
    0x85f72ff33d09f9fc, /* vkGetImageDrmFormatModifierPropertiesEXT */
    0x860a89bcaf7d40af, /* vkGetRayTracingCaptureReplayShaderGroupHandlesKHR */
    0x865bc9e531e492a5, /* vkDestroyFence */
    0x86a35fcb0cd25838, /* vkCmdSetFragmentShadingRateEnumNV */
    0x877be98356e2a511, /* vkCmdTraceRaysNV */
    0x87a7866d1df23f2b, /* vkDestroyRenderPass */
    0x88c098a6d45aa827, /* vkCmdCopyImageToBuffer */
    0x8977eb367d2cc188, /* vkCreateIndirectCommandsLayoutNV */
    0x899487a9c9bfa851, /* vkGetShaderInfoAMD */
    0x8a4301ac1aeca958, /* vkRegisterDeviceEventEXT */
    0x8a862e62841ec082, /* vkCmdResetEvent2KHR */
    0x8aa9a6ca90bcc785, /* vkImportFenceWin32HandleKHR */
    0x8ad52c133e5fcc89, /* vkCmdSetCullModeEXT */
    0x8ada4cd22e8a735c, /* vkCmdSetColorBlendEquationEXT */
    0x8b087bf937ffd567, /* vkGetShaderBinaryDataEXT */
    0x8b778f59be50c419, /* vkCreateRenderPass */
    0x8bd0b4949f3f2aa3, /* vkGetRayTracingShaderGroupHandlesNV */
    0x8da528a7d8e71c4a, /* vkGetPrivateDataEXT */
    0x8db47b7cc78dbf21, /* vkAcquireNextImageKHR */
    0x8ddf999c6ee753db, /* vkDestroyCommandPool */
    0x8debabeca0bc6dd7, /* vkCmdSetPrimitiveRestartEnableEXT */
    0x8eaf0b3e0a85d3bc, /* vkDestroyOpticalFlowSessionNV */
    0x8ed6523506902ceb, /* vkCmdSetFragmentShadingRateKHR */
    0x8f433193cdb26798, /* vkReleaseCapturedPipelineDataKHR */
    0x8f737985d0de322a, /* vkCmdBuildPartitionedAccelerationStructuresNV */
    0x8ffccda86549f286, /* vkDestroyBuffer */
    0x900de63b0b6f0ca2, /* vkCmdClearColorImage */
    0x9022d31d32c4a419, /* vkDestroyPipelineLayout */
    0x90311ab1031c3341, /* vkGetDeviceTensorMemoryRequirementsARM */
    0x908be4be59b54bee, /* vkCmdBindDescriptorBufferEmbeddedSamplers2EXT */
    0x90b98ea73daf2fc7, /* vkWaitSemaphoresKHR */
    0x914ccba5ef3134d3, /* vkCreatePrivateDataSlotEXT */
    0x9166d9b745afd8af, /* vkGetDeviceGroupSurfacePresentModes2EXT */
    0x91b293db19f39ca5, /* vkMergeValidationCachesEXT */
    0x928a039a45864345, /* vkDestroyDescriptorPool */
    0x92bb34229e07c467, /* vkCmdSetDiscardRectangleEXT */
    0x9303bbd56b6cd187, /* vkCmdDispatch */
    0x94400ae778a5a963, /* vkCmdDrawMeshTasksIndirectEXT */
    0x95035412cfab2a57, /* vkCmdExecuteGeneratedCommandsEXT */
    0x9508bfb817e18156, /* vkCmdCudaLaunchKernelNV */
    0x950906daed043635, /* vkCmdBeginRendering */
    0x953dd320a2f19033, /* vkCmdBeginRenderPass2KHR */
    0x958f70568135c547, /* vkWaitForPresentKHR */
    0x95a0cae5a6723961, /* vkCopyMemoryToImageEXT */
    0x95e478a17bd017c9, /* vkCmdDrawIndexedIndirectCountAMD */
    0x95e7e04ef3cf5655, /* vkCmdBindVertexBuffers2EXT */
    0x95fd48feaefe8c46, /* vkBindVideoSessionMemoryKHR */
    0x9666a70591f64892, /* vkGetDeviceMemoryOpaqueCaptureAddress */
    0x967cb9c4a8000c04, /* vkWaitForPresent2KHR */
    0x96d500101d2c0cfc, /* vkCmdDebugMarkerEndEXT */
    0x97fb69a7181762a0, /* vkCmdSetDepthCompareOp */
    0x983f1d9254a0a363, /* vkCmdSetAlphaToOneEnableEXT */
    0x987ef1c05cbaa5d8, /* vkGetDeviceImageSparseMemoryRequirements */
    0x990606475b0662c9, /* vkCreateOpticalFlowSessionNV */
    0x996b8928f4147a24, /* vkDestroyVideoSessionParametersKHR */
    0x997ea78db49c8c69, /* vkCmdBeginQuery */
    0x99d50d423e66f60a, /* vkCmdEndQuery */
    0x99dfcdbeb70620f3, /* vkGetDescriptorEXT */
    0x9b6913d4f956684e, /* vkCmdSetBlendConstants */
    0x9b7c9ebe9b147cf1, /* vkCmdSetCoverageModulationTableEnableNV */
    0x9beb233b5b7ad768, /* vkCmdBindVertexBuffers */
    0x9c10b26ceb8d7cd4, /* vkGetExecutionGraphPipelineNodeIndexAMDX */
    0x9cbf04885cb0f4c1, /* vkDestroyIndirectExecutionSetEXT */
    0x9cc130ca400434b7, /* vkGetImageSparseMemoryRequirements2KHR */
    0x9d134d5d5df51d6b, /* vkGetDescriptorSetHostMappingVALVE */
    0x9df40d3bb19dc7f0, /* vkCreateCuFunctionNVX */
    0x9e1cf02c5780b2d6, /* vkGetAccelerationStructureHandleNV */
    0x9ef6b4cec6a221f8, /* vkDestroyDevice */
    0x9f690b963d6e97a7, /* vkCmdWriteAccelerationStructuresPropertiesNV */
    0x9fd2d4176909d303, /* vkGetRefreshCycleDurationGOOGLE */
    0xa0e05031ca80b190, /* vkCopyImageToImage */
    0xa0f10e474c7a0e0d, /* vkCmdSetColorBlendAdvancedEXT */
    0xa143601d567d78a8, /* vkCmdInitializeGraphScratchMemoryAMDX */
    0xa17b9f5a286650f5, /* vkBindImageMemory2KHR */
    0xa1ba141ce2a9627b, /* vkCreateSamplerYcbcrConversion */
    0xa1e0bb08c1850958, /* vkCmdUpdateBuffer */
    0xa343558c3889eb3b, /* vkCmdDrawIndexedIndirectCountKHR */
    0xa34e1bfd05275463, /* vkCmdSetCoverageModulationTableNV */
    0xa3c120c4c081785a, /* vkCmdBeginQueryIndexedEXT */
    0xa3fdcfe5e638f01f, /* vkCreateShaderModule */
    0xa43291af959e4044, /* vkGetImageSparseMemoryRequirements2 */
    0xa47abcf416f45e13, /* vkDestroyCuModuleNVX */
    0xa52ec7d995ba8bd0, /* vkCmdSetDepthWriteEnable */
    0xa53a9028f9deee27, /* vkCmdBeginDebugUtilsLabelEXT */
    0xa5bd2226d386dd02, /* vkCmdDecodeVideoKHR */
    0xa6007e58158aed7d, /* vkResetDescriptorPool */
    0xa664321f63cd904a, /* vkCmdSetLineStippleEnableEXT */
    0xa739034f864fc640, /* vkDebugMarkerSetObjectTagEXT */
    0xa8ab2a7a72d37501, /* vkCreateComputePipelines */
    0xa90d9c4553e96cbe, /* vkDestroySemaphore */
    0xa966bf46df7237f0, /* vkCmdWriteMicromapsPropertiesEXT */
    0xa99627a28d359157, /* vkCmdBuildAccelerationStructuresIndirectKHR */
    0xa9a55fd0d9b55eda, /* vkCmdDecompressMemoryIndirectCountNV */
    0xaa1696745b9d6280, /* vkCmdDispatchDataGraphARM */
    0xaa4956312cfc8f69, /* vkAcquireProfilingLockKHR */
    0xaa6c800d6f3a85cf, /* vkGetClusterAccelerationStructureBuildSizesNV */
    0xaac33dd01204ea6d, /* vkUpdateDescriptorSets */
    0xaae6e3e723f39a93, /* vkCmdCopyBufferToImage2KHR */
    0xaaee8606a2f000f3, /* vkInitializePerformanceApiINTEL */
    0xabb4da3669fa0607, /* vkCmdSetRenderingAttachmentLocationsKHR */
    0xabbbfebcb5e50ddf, /* vkCreateDescriptorSetLayout */
    0xada92dcad41eaf98, /* vkCmdBindDescriptorSets */
    0xadc8c5c7b58db7da, /* vkDestroyTensorViewARM */
    0xadd175019f7d316f, /* vkCmdSetProvokingVertexModeEXT */
    0xae000b2715cd085c, /* vkCmdBeginTransformFeedbackEXT */
    0xae196725993a5773, /* vkCreateDescriptorUpdateTemplateKHR */
    0xae68bbafa60e1bfd, /* vkCmdDrawMeshTasksIndirectCountNV */
    0xae74bca0714f1b3b, /* vkCmdSetDiscardRectangleEnableEXT */
    0xae8baaf2908ad9f8, /* vkCmdSetDepthTestEnableEXT */
    0xaf2b917e19ff90c6, /* vkMapMemory2 */
    0xaf494d1294356cc7, /* vkGetDeviceGroupPeerMemoryFeatures */
    0xafe12b5c094c8aeb, /* vkCmdSetDepthBiasEnableEXT */
    0xb055e21eec61f87e, /* vkDestroyBufferCollectionFUCHSIA */
    0xb0aeacfa9fc521aa, /* vkCmdDrawMeshTasksNV */
    0xb172c9f4537a3da8, /* vkCmdCopyImage2KHR */
    0xb1c51323a9aecd49, /* vkDebugMarkerSetObjectNameEXT */
    0xb1f1669ee2dd4847, /* vkCopyImageToMemoryEXT */
    0xb2063ddd597a6ad7, /* vkCmdPipelineBarrier */
    0xb23c3f52093e01ee, /* vkCreateSemaphore */
    0xb2f2d8afec7a88a4, /* vkCreateImageView */
    0xb300f7cc2bbb1fdd, /* vkReleaseSwapchainImagesKHR */
    0xb32de6d8d29abe22, /* vkDestroyShaderEXT */
    0xb3fc6ad1eebe5d90, /* vkGetSemaphoreZirconHandleFUCHSIA */
    0xb449b51a1fdae15f, /* vkCmdSetViewportSwizzleNV */
    0xb51bc46c54af21f6, /* vkCreateFence */
    0xb523ea07e8e7d77f, /* vkCmdWriteBufferMarker2AMD */
    0xb57d926305bc8ed4, /* vkCreateIndirectExecutionSetEXT */
    0xb615047d05c91282, /* vkGetDescriptorSetLayoutSizeEXT */
    0xb67ff6e303d3c4fb, /* vkCmdSetViewportWScalingNV */
    0xb69a959653538c19, /* vkGetImageMemoryRequirements2 */
    0xb6e8dcebebd08436, /* vkCreateMicromapEXT */
    0xb70a1f7b0d640472, /* vkCmdEndDebugUtilsLabelEXT */
    0xb7d326eaca38da93, /* vkDestroySamplerYcbcrConversionKHR */
    0xb7ddef653b0f7932, /* vkCmdSetLineWidth */
    0xb811d13ae8ba8698, /* vkDestroyCudaFunctionNV */
    0xb8f7f65305fa9c04, /* vkSignalSemaphoreKHR */
    0xb90a1a834aa8c307, /* vkCmdSetFrontFace */
    0xb914845a146232bd, /* vkGetDeviceImageMemoryRequirementsKHR */
    0xb9dc146482b98eab, /* vkCmdSetScissorWithCount */
    0xba764f7da1952e81, /* vkCmdWaitEvents2 */
    0xba7d020dda50aee4, /* vkCmdDebugMarkerBeginEXT */
    0xbaa71789dfb073b1, /* vkCreateSamplerYcbcrConversionKHR */
    0xbb471ca7efa2efd6, /* vkGetFramebufferTilePropertiesQCOM */
    0xbb625b5594f09b62, /* vkCmdBindDescriptorSets2KHR */
    0xbbb204c332bf3b26, /* vkCmdPreprocessGeneratedCommandsNV */
    0xbde4c14636640d82, /* vkGetMemoryZirconHandleFUCHSIA */
    0xbe6ba58fe9b83a9f, /* vkWriteAccelerationStructuresPropertiesKHR */
    0xbf39cf164d4f3b71, /* vkCmdSetDepthCompareOpEXT */
    0xc0130a682397781c, /* vkCmdOpticalFlowExecuteNV */
    0xc013f1850e57943a, /* vkGetDataGraphPipelinePropertiesARM */
    0xc0b67df33e46a5f0, /* vkCmdSetPerformanceStreamMarkerINTEL */
    0xc0e77996431e14e7, /* vkCmdPushDescriptorSetWithTemplateKHR */
    0xc0faf7a0688b9961, /* vkDestroyFramebuffer */
    0xc1239f4d94d0ccd5, /* vkCmdTraceRaysIndirectKHR */
    0xc18ca303430c5030, /* vkGetBufferMemoryRequirements */
    0xc1fb12d42b3f2d2c, /* vkCmdSetCoverageReductionModeNV */
    0xc20b7cd3cdb4895d, /* vkBindBufferMemory2KHR */
    0xc21c28ddac3fbec3, /* vkGetMemoryWin32HandleNV */
    0xc24235cf58916cb3, /* vkCmdCopyMemoryToAccelerationStructureKHR */
    0xc261491c6f3eb73a, /* vkCmdEndRendering */
    0xc282ec2fb0ff4a7f, /* vkCmdSetDepthBoundsTestEnable */
    0xc2b3ba3e0620f227, /* vkCreateTensorViewARM */
    0xc2f02663a1a88208, /* vkSetPrivateDataEXT */
    0xc3167c9cdfe12247, /* vkSetLatencySleepModeNV */
    0xc3b0dc0e29037a73, /* vkCmdSetRenderingInputAttachmentIndices */
    0xc3d161a58a0be001, /* vkGetDynamicRenderingTilePropertiesQCOM */
    0xc4a32c157b57c919, /* vkCmdSetPrimitiveTopology */
    0xc522092927d98161, /* vkDestroyValidationCacheEXT */
    0xc53d00dd120cc028, /* vkCreateDeferredOperationKHR */
    0xc5d77b727d806ce6, /* vkCmdBindDescriptorBufferEmbeddedSamplersEXT */
    0xc6158137c93c542a, /* vkDestroyPipeline */
    0xc6fee3fca12fb11e, /* vkResetCommandBuffer */
    0xc73b61c79b859a21, /* vkCmdCopyAccelerationStructureToMemoryKHR */
    0xc746d971c6158609, /* vkCmdSetScissor */
    0xc77b0aec1b685e42, /* vkGetMemoryZirconHandlePropertiesFUCHSIA */
    0xc7d428e344b14ca8, /* vkDestroyImage */
    0xc7e4fe21b7623076, /* vkCmdExecuteGeneratedCommandsNV */
    0xc7fb7a8e9fc178bf, /* vkCreateCommandPool */
    0xc8c90b647a8c1688, /* vkCmdBeginRenderPass */
    0xc8ce9307051f9bc4, /* vkCmdCuLaunchKernelNVX */
    0xcb5126a43f13e1de, /* vkCmdEndQueryIndexedEXT */
    0xcb818f46817e8697, /* vkCmdSetStencilTestEnableEXT */
    0xcc38e899cdc6433c, /* vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI */
    0xcc661f1aee937b88, /* vkCmdSetSampleLocationsEnableEXT */
    0xcce224e583312a27, /* vkCreateSampler */
    0xcd3579faa9244fe8, /* vkCmdDrawClusterHUAWEI */
    0xcda4a94d2c8596f7, /* vkGetMemoryWin32HandleKHR */
    0xcdd7843304775055, /* vkFlushMappedMemoryRanges */
    0xcdda04206e1c1dfe, /* vkCmdBlitImage2KHR */
    0xce5d77a823daf981, /* vkGetMemoryWin32HandlePropertiesKHR */
    0xce653760953e9106, /* vkCreateBufferCollectionFUCHSIA */
    0xcf18436e233f62fe, /* vkExportMetalObjectsEXT */
    0xcf86c42d2695983a, /* vkCmdEndRenderPass2KHR */
    0xcfa13bad1a984ba3, /* vkCmdBeginVideoCodingKHR */
    0xcfbd6aad8345b609, /* vkMergePipelineCaches */
    0xcfd90dd84e50b6e2, /* vkGetRenderAreaGranularity */
    0xcff95583fb6ffa3f, /* vkCmdDispatchBase */
    0xd0df5f67ee24e975, /* vkSetEvent */
    0xd10afc8461e339f2, /* vkSetBufferCollectionImageConstraintsFUCHSIA */
    0xd1bfa4d3176b81a7, /* vkGetDeviceImageSubresourceLayoutKHR */
    0xd271ad249d3a5d1d, /* vkCmdEndRenderPass2 */
    0xd2ada1f0fce0ebc9, /* vkCmdDrawIndirectCountKHR */
    0xd31d2bb517a75484, /* vkCmdSetAttachmentFeedbackLoopEnableEXT */
    0xd34524d6520a5733, /* vkResetQueryPool */
    0xd35e353760f41c6f, /* vkCmdSetViewportWScalingEnableNV */
    0xd3d8cd8814a0cdd8, /* vkCmdBindDescriptorBuffersEXT */
    0xd536d860a73cf116, /* vkDestroyAccelerationStructureKHR */
    0xd537fdf3c85210f2, /* vkGetDeviceGroupPresentCapabilitiesKHR */
    0xd60719bface6199d, /* vkGetDataGraphPipelineSessionBindPointRequirementsARM */
    0xd60ca89f1c84b347, /* vkGetSemaphoreCounterValue */
    0xd620ed53628cc23d, /* vkGetEncodedVideoSessionParametersKHR */
    0xd70928b0b99ddf51, /* vkGetFenceWin32HandleKHR */
    0xd74792cfb5d068ce, /* vkUpdateIndirectExecutionSetPipelineEXT */
    0xd75ed866d33442a9, /* vkUnmapMemory2 */
    0xd88e4fe9c0329771, /* vkQueueBeginDebugUtilsLabelEXT */
    0xd8b91a19d2c84eba, /* vkGetPipelineIndirectMemoryRequirementsNV */
    0xd8c4bb7f3586d513, /* vkCmdDispatchGraphIndirectCountAMDX */
    0xda6d56b119c97568, /* vkCmdResolveImage2KHR */
    0xda9d391d34dd9078, /* vkCmdPushDescriptorSet2KHR */
    0xdab35189cc70375d, /* vkCmdCopyBufferToImage2 */
    0xdac55f445397e484, /* vkCmdDispatchIndirect */
    0xdad4b40f2b59becc, /* vkReleaseFullScreenExclusiveModeEXT */
    0xdad7d425257f2349, /* vkCmdBuildMicromapsEXT */
    0xdb365928cfa4eba1, /* vkConvertCooperativeVectorMatrixNV */
    0xdc65534119ad5fa9, /* vkCmdEndRendering2EXT */
    0xdce67e01cb34aa72, /* vkDestroyPrivateDataSlotEXT */
    0xdd609c8b8fed0093, /* vkGetRayTracingShaderGroupStackSizeKHR */
    0xddc1b3a9e007be5a, /* vkGetFenceStatus */
    0xe06aa3b9e8eeba91, /* vkAntiLagUpdateAMD */
    0xe0f1d5482a04901c, /* vkCmdSetCoverageToColorEnableNV */
    0xe133357d099609f5, /* vkCmdCopyQueryPoolResults */
    0xe2152f86c3e27268, /* vkGetScreenBufferPropertiesQNX */
    0xe2b6c462d682d0aa, /* vkQueueInsertDebugUtilsLabelEXT */
    0xe3e71921cd13bc5f, /* vkGetSwapchainImagesKHR */
    0xe43a4f01acf5a1b6, /* vkGetPrivateData */
    0xe43e1298ce6a3bfe, /* vkCopyAccelerationStructureToMemoryKHR */
    0xe47d87648c47352c, /* vkGetDeviceImageSubresourceLayout */
    0xe5686168ac2e1c2a, /* vkCmdSetDiscardRectangleModeEXT */
    0xe62b971ae0a68532, /* vkGetDeviceGroupPeerMemoryFeaturesKHR */
    0xe66bc79887578e01, /* vkImportSemaphoreWin32HandleKHR */
    0xe67ea7bf4305edd8, /* vkGetDescriptorSetLayoutHostMappingInfoVALVE */
    0xe6b91e7965ee4a9f, /* vkCmdSetColorWriteMaskEXT */
    0xe753bab9908ecda8, /* vkImportFenceFdKHR */
    0xe77fae71b009ad05, /* vkCreateDescriptorUpdateTemplate */
    0xe7b1ed7ad6f748f7, /* vkCompileDeferredNV */
    0xe7ba2bcf3218ef91, /* vkGetPipelineKeyKHR */
    0xe7cfb8155a9ec7f4, /* vkGetSemaphoreWin32HandleKHR */
    0xe7e550b2969ceb79, /* vkCmdConvertCooperativeVectorMatrixNV */
    0xe86e1a671a40b3b7, /* vkCmdSetLineRasterizationModeEXT */
    0xe89bda66824b7d7d, /* vkCreateVideoSessionParametersKHR */
    0xe8ddcebfb8abfe62, /* vkGetDeferredOperationMaxConcurrencyKHR */
    0xe8fbd5bb4e925208, /* vkDestroyPrivateDataSlot */
    0xe9321def2e9912ac, /* vkDestroyCuFunctionNVX */
    0xe9afc748cd05801d, /* vkCmdWriteAccelerationStructuresPropertiesKHR */
    0xea1cabf280ef8b04, /* vkCmdCopyMemoryIndirectNV */
    0xeb42e2a34feca3d7, /* vkBindDataGraphPipelineSessionMemoryARM */
    0xebc09d555d9390f1, /* vkImportSemaphoreFdKHR */
    0xee0c987fe12167e5, /* vkCmdSetColorWriteEnableEXT */
    0xee397d978e3960d4, /* vkCmdWriteTimestamp */
    0xef3c02c6a6557f67, /* vkCmdSetCullMode */
    0xef99360f052b923d, /* vkUninitializePerformanceApiINTEL */
    0xefff832805016a4e, /* vkCmdSetDepthTestEnable */
    0xf02843786e3933f8, /* vkCmdSetRasterizationSamplesEXT */
    0xf0560464399d1a5d, /* vkCmdPushDescriptorSet */
    0xf0bf149eb20282af, /* vkCmdPushConstants */
    0xf1159d930e7b7f9b, /* vkCmdSetDepthBias2EXT */
    0xf1696abc2816c1f0, /* vkGetLatencyTimingsNV */
    0xf2c5ad0d9aa4acf3, /* vkFreeMemory */
    0xf2fafc3e54bde6da, /* vkCreateBufferView */
    0xf31eeaf76f0b6dca, /* vkCmdDispatchGraphAMDX */
    0xf325f660479c7872, /* vkGetDeferredOperationResultKHR */
    0xf39873088d0d505a, /* vkCopyMicromapEXT */
    0xf42ac32ac7eb727c, /* vkCmdPushDescriptorSetWithTemplate2KHR */
    0xf51a3c7f77277e37, /* vkUnmapMemory */
    0xf5243f8ebe970031, /* vkCmdEndVideoCodingKHR */
    0xf525fcfca497ad4d, /* vkCmdBeginRenderingKHR */
    0xf56a44bbdebd81c5, /* vkDestroyBufferView */
    0xf5dd10901cd99b7e, /* vkCmdBindVertexBuffers2 */
    0xf6a1a179eb200ea3, /* vkCmdSetStencilReference */
    0xf7190fead13f236c, /* vkGetRenderingAreaGranularity */
    0xf738ab31f5c4808a, /* vkCmdSetLineStipple */
    0xf763fd5a051145b3, /* vkCmdBeginRenderPass2 */
    0xf8010e878fa40163, /* vkGetPipelineExecutablePropertiesKHR */
    0xf88aec90a89de0da, /* vkGetDeviceAccelerationStructureCompatibilityKHR */
    0xf8a5e079575f045d, /* vkCmdNextSubpass */
    0xf8d70781ac92a1cf, /* vkCreateVideoSessionKHR */
    0xf991ab3939955de5, /* vkCmdSetPrimitiveTopologyEXT */
    0xf9a65ae9b4a10e79, /* vkDestroyIndirectCommandsLayoutEXT */
    0xf9b2570c3144fc75, /* vkCmdDrawIndexed */
    0xf9cc9eb6cea6c9cb, /* vkCmdDrawIndirect */
    0xf9df59021b7985d5, /* vkUpdateIndirectExecutionSetShaderEXT */
    0xfa53afc7b202a4cc, /* vkCreateDescriptorPool */
    0xfa5d78b1a973792e, /* vkCmdSetSampleLocationsEXT */
    0xfa88974bd2f1055c, /* vkGetImageSubresourceLayout2KHR */
    0xfb6168e88a9522ee, /* vkCmdBindPipelineShaderGroupNV */
    0xfb75695f0deb8eb6, /* vkCmdBlitImage2 */
    0xfbe9454065432dfa, /* vkCmdCopyImage2 */
    0xfc14ed2f19a09e14, /* vkBindTensorMemoryARM */
    0xfc27ea97ed553e3f, /* vkCreateExternalComputeQueueNV */
    0xfc42afaa1bbc54a8, /* vkCreateEvent */
    0xfccd697bc5cf4494, /* vkSetDebugUtilsObjectNameEXT */
    0xfd2a746603a13f60, /* vkCreateRenderPass2 */
    0xfd4ef6a737d2546d, /* vkBindImageMemory2 */
    0xfe4be9de353f2023, /* vkDestroyAccelerationStructureNV */
    0xfe8be5739d1d70ae, /* vkCmdSetCoverageToColorLocationNV */
    0xfeb9ee575b9d3ace, /* vkGetDataGraphPipelineAvailablePropertiesARM */
    0xff17500f60079a4b, /* vkGetRenderingAreaGranularityKHR */
    0xffa40d4e01bf3cc0, /* vkCmdSetViewportWithCountEXT */
};

static uint64_t GLAD_Vulkan_global_commands[] = {
    0x293f4d0e3d436dce, /* vkEnumerateInstanceExtensionProperties */
    0xc930c283b60dafd0, /* vkEnumerateInstanceLayerProperties */
    0xed8a6efd46f4e052, /* vkCreateInstance */
    0xf79cbf7989a3746e, /* vkEnumerateInstanceVersion */
};

static int glad_vulkan_is_device_command(uint64_t nameHash) {
    /* Exists as a workaround for:
     * https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/issues/2323
     *
     * `vkGetDeviceProcAddr` does not return NULL for non-device functions.
     */
    return glad_hash_search(GLAD_Vulkan_device_commands, GLAD_ARRAYSIZE(GLAD_Vulkan_device_commands), nameHash);
}

static int glad_vulkan_is_global_command(uint64_t nameHash) {
    return glad_hash_search(GLAD_Vulkan_global_commands, GLAD_ARRAYSIZE(GLAD_Vulkan_global_commands), nameHash);
}

struct _glad_vulkan_userptr {
    void *vk_handle;
    VkInstance vk_instance;
    VkDevice vk_device;
    PFN_vkGetInstanceProcAddr get_instance_proc_addr;
    PFN_vkGetDeviceProcAddr get_device_proc_addr;
};

static GLADapiproc glad_vulkan_get_proc(void *vuserptr, const char *name) {
    struct _glad_vulkan_userptr userptr = *(struct _glad_vulkan_userptr*) vuserptr;
    uint64_t nameHash = glad_hash_string(name, strlen(name));
    PFN_vkVoidFunction result = NULL;

    if (userptr.vk_device != NULL && glad_vulkan_is_device_command(nameHash)) {
        result = userptr.get_device_proc_addr(userptr.vk_device, name);
    } else {
        bool is_global_command = glad_vulkan_is_global_command(nameHash);
        if (is_global_command) {
            result = userptr.get_instance_proc_addr(NULL, name);
        } else if (userptr.vk_instance != NULL) {
            result = userptr.get_instance_proc_addr(userptr.vk_instance, name);
        }
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
