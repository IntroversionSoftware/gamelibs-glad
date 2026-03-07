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

GLAD_NO_INLINE static void glad_sort_hashes(uint64_t *a, size_t n) {
    /* Ciura gap sequence; we’ll skip the big ones at runtime. */
    static const size_t gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};
    size_t gi = 0;

    if (!a || n < 2)
        return;

    while (gi < GLAD_ARRAYSIZE(gaps) && gaps[gi] >= n)
        gi++;

    for (; gi < GLAD_ARRAYSIZE(gaps); ++gi) {
        size_t gap = gaps[gi], i;
        for (i = gap; i < n; ++i) {
            uint64_t v = a[i];
            size_t j = i;
            /* gapped insertion sort */
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
    /*   42 */ "vkCreateQueryPool",
    /*   43 */ "vkDestroyQueryPool",
    /*   44 */ "vkGetQueryPoolResults",
    /*   45 */ "vkCreateBuffer",
    /*   46 */ "vkDestroyBuffer",
    /*   47 */ "vkCreateImage",
    /*   48 */ "vkDestroyImage",
    /*   49 */ "vkGetImageSubresourceLayout",
    /*   50 */ "vkCreateImageView",
    /*   51 */ "vkDestroyImageView",
    /*   52 */ "vkCreateCommandPool",
    /*   53 */ "vkDestroyCommandPool",
    /*   54 */ "vkResetCommandPool",
    /*   55 */ "vkAllocateCommandBuffers",
    /*   56 */ "vkFreeCommandBuffers",
    /*   57 */ "vkBeginCommandBuffer",
    /*   58 */ "vkEndCommandBuffer",
    /*   59 */ "vkResetCommandBuffer",
    /*   60 */ "vkCmdCopyBuffer",
    /*   61 */ "vkCmdCopyImage",
    /*   62 */ "vkCmdCopyBufferToImage",
    /*   63 */ "vkCmdCopyImageToBuffer",
    /*   64 */ "vkCmdUpdateBuffer",
    /*   65 */ "vkCmdFillBuffer",
    /*   66 */ "vkCmdPipelineBarrier",
    /*   67 */ "vkCmdBeginQuery",
    /*   68 */ "vkCmdEndQuery",
    /*   69 */ "vkCmdResetQueryPool",
    /*   70 */ "vkCmdWriteTimestamp",
    /*   71 */ "vkCmdCopyQueryPoolResults",
    /*   72 */ "vkCmdExecuteCommands",
    /*   73 */ "vkCreateEvent",
    /*   74 */ "vkDestroyEvent",
    /*   75 */ "vkGetEventStatus",
    /*   76 */ "vkSetEvent",
    /*   77 */ "vkResetEvent",
    /*   78 */ "vkCreateBufferView",
    /*   79 */ "vkDestroyBufferView",
    /*   80 */ "vkCreateShaderModule",
    /*   81 */ "vkDestroyShaderModule",
    /*   82 */ "vkCreatePipelineCache",
    /*   83 */ "vkDestroyPipelineCache",
    /*   84 */ "vkGetPipelineCacheData",
    /*   85 */ "vkMergePipelineCaches",
    /*   86 */ "vkCreateComputePipelines",
    /*   87 */ "vkDestroyPipeline",
    /*   88 */ "vkCreatePipelineLayout",
    /*   89 */ "vkDestroyPipelineLayout",
    /*   90 */ "vkCreateSampler",
    /*   91 */ "vkDestroySampler",
    /*   92 */ "vkCreateDescriptorSetLayout",
    /*   93 */ "vkDestroyDescriptorSetLayout",
    /*   94 */ "vkCreateDescriptorPool",
    /*   95 */ "vkDestroyDescriptorPool",
    /*   96 */ "vkResetDescriptorPool",
    /*   97 */ "vkAllocateDescriptorSets",
    /*   98 */ "vkFreeDescriptorSets",
    /*   99 */ "vkUpdateDescriptorSets",
    /*  100 */ "vkCmdBindPipeline",
    /*  101 */ "vkCmdBindDescriptorSets",
    /*  102 */ "vkCmdClearColorImage",
    /*  103 */ "vkCmdDispatch",
    /*  104 */ "vkCmdDispatchIndirect",
    /*  105 */ "vkCmdSetEvent",
    /*  106 */ "vkCmdResetEvent",
    /*  107 */ "vkCmdWaitEvents",
    /*  108 */ "vkCmdPushConstants",
    /*  109 */ "vkCreateGraphicsPipelines",
    /*  110 */ "vkCreateFramebuffer",
    /*  111 */ "vkDestroyFramebuffer",
    /*  112 */ "vkCreateRenderPass",
    /*  113 */ "vkDestroyRenderPass",
    /*  114 */ "vkGetRenderAreaGranularity",
    /*  115 */ "vkCmdSetViewport",
    /*  116 */ "vkCmdSetScissor",
    /*  117 */ "vkCmdSetLineWidth",
    /*  118 */ "vkCmdSetDepthBias",
    /*  119 */ "vkCmdSetBlendConstants",
    /*  120 */ "vkCmdSetDepthBounds",
    /*  121 */ "vkCmdSetStencilCompareMask",
    /*  122 */ "vkCmdSetStencilWriteMask",
    /*  123 */ "vkCmdSetStencilReference",
    /*  124 */ "vkCmdBindIndexBuffer",
    /*  125 */ "vkCmdBindVertexBuffers",
    /*  126 */ "vkCmdDraw",
    /*  127 */ "vkCmdDrawIndexed",
    /*  128 */ "vkCmdDrawIndirect",
    /*  129 */ "vkCmdDrawIndexedIndirect",
    /*  130 */ "vkCmdBlitImage",
    /*  131 */ "vkCmdClearDepthStencilImage",
    /*  132 */ "vkCmdClearAttachments",
    /*  133 */ "vkCmdResolveImage",
    /*  134 */ "vkCmdBeginRenderPass",
    /*  135 */ "vkCmdNextSubpass",
    /*  136 */ "vkCmdEndRenderPass",
    /*  137 */ "vkEnumerateInstanceVersion",
    /*  138 */ "vkBindBufferMemory2",
    /*  139 */ "vkBindImageMemory2",
    /*  140 */ "vkGetDeviceGroupPeerMemoryFeatures",
    /*  141 */ "vkCmdSetDeviceMask",
    /*  142 */ "vkEnumeratePhysicalDeviceGroups",
    /*  143 */ "vkGetImageMemoryRequirements2",
    /*  144 */ "vkGetBufferMemoryRequirements2",
    /*  145 */ "vkGetImageSparseMemoryRequirements2",
    /*  146 */ "vkGetPhysicalDeviceFeatures2",
    /*  147 */ "vkGetPhysicalDeviceProperties2",
    /*  148 */ "vkGetPhysicalDeviceFormatProperties2",
    /*  149 */ "vkGetPhysicalDeviceImageFormatProperties2",
    /*  150 */ "vkGetPhysicalDeviceQueueFamilyProperties2",
    /*  151 */ "vkGetPhysicalDeviceMemoryProperties2",
    /*  152 */ "vkGetPhysicalDeviceSparseImageFormatProperties2",
    /*  153 */ "vkTrimCommandPool",
    /*  154 */ "vkGetDeviceQueue2",
    /*  155 */ "vkGetPhysicalDeviceExternalBufferProperties",
    /*  156 */ "vkGetPhysicalDeviceExternalFenceProperties",
    /*  157 */ "vkGetPhysicalDeviceExternalSemaphoreProperties",
    /*  158 */ "vkCmdDispatchBase",
    /*  159 */ "vkCreateDescriptorUpdateTemplate",
    /*  160 */ "vkDestroyDescriptorUpdateTemplate",
    /*  161 */ "vkUpdateDescriptorSetWithTemplate",
    /*  162 */ "vkGetDescriptorSetLayoutSupport",
    /*  163 */ "vkCreateSamplerYcbcrConversion",
    /*  164 */ "vkDestroySamplerYcbcrConversion",
    /*  165 */ "vkResetQueryPool",
    /*  166 */ "vkGetSemaphoreCounterValue",
    /*  167 */ "vkWaitSemaphores",
    /*  168 */ "vkSignalSemaphore",
    /*  169 */ "vkGetBufferDeviceAddress",
    /*  170 */ "vkGetBufferOpaqueCaptureAddress",
    /*  171 */ "vkGetDeviceMemoryOpaqueCaptureAddress",
    /*  172 */ "vkCmdDrawIndirectCount",
    /*  173 */ "vkCmdDrawIndexedIndirectCount",
    /*  174 */ "vkCreateRenderPass2",
    /*  175 */ "vkCmdBeginRenderPass2",
    /*  176 */ "vkCmdNextSubpass2",
    /*  177 */ "vkCmdEndRenderPass2",
    /*  178 */ "vkGetPhysicalDeviceToolProperties",
    /*  179 */ "vkCreatePrivateDataSlot",
    /*  180 */ "vkDestroyPrivateDataSlot",
    /*  181 */ "vkSetPrivateData",
    /*  182 */ "vkGetPrivateData",
    /*  183 */ "vkCmdPipelineBarrier2",
    /*  184 */ "vkCmdWriteTimestamp2",
    /*  185 */ "vkQueueSubmit2",
    /*  186 */ "vkCmdCopyBuffer2",
    /*  187 */ "vkCmdCopyImage2",
    /*  188 */ "vkCmdCopyBufferToImage2",
    /*  189 */ "vkCmdCopyImageToBuffer2",
    /*  190 */ "vkGetDeviceBufferMemoryRequirements",
    /*  191 */ "vkGetDeviceImageMemoryRequirements",
    /*  192 */ "vkGetDeviceImageSparseMemoryRequirements",
    /*  193 */ "vkCmdSetEvent2",
    /*  194 */ "vkCmdResetEvent2",
    /*  195 */ "vkCmdWaitEvents2",
    /*  196 */ "vkCmdBlitImage2",
    /*  197 */ "vkCmdResolveImage2",
    /*  198 */ "vkCmdBeginRendering",
    /*  199 */ "vkCmdEndRendering",
    /*  200 */ "vkCmdSetCullMode",
    /*  201 */ "vkCmdSetFrontFace",
    /*  202 */ "vkCmdSetPrimitiveTopology",
    /*  203 */ "vkCmdSetViewportWithCount",
    /*  204 */ "vkCmdSetScissorWithCount",
    /*  205 */ "vkCmdBindVertexBuffers2",
    /*  206 */ "vkCmdSetDepthTestEnable",
    /*  207 */ "vkCmdSetDepthWriteEnable",
    /*  208 */ "vkCmdSetDepthCompareOp",
    /*  209 */ "vkCmdSetDepthBoundsTestEnable",
    /*  210 */ "vkCmdSetStencilTestEnable",
    /*  211 */ "vkCmdSetStencilOp",
    /*  212 */ "vkCmdSetRasterizerDiscardEnable",
    /*  213 */ "vkCmdSetDepthBiasEnable",
    /*  214 */ "vkCmdSetPrimitiveRestartEnable",
    /*  215 */ "vkMapMemory2",
    /*  216 */ "vkUnmapMemory2",
    /*  217 */ "vkGetDeviceImageSubresourceLayout",
    /*  218 */ "vkGetImageSubresourceLayout2",
    /*  219 */ "vkCopyMemoryToImage",
    /*  220 */ "vkCopyImageToMemory",
    /*  221 */ "vkCopyImageToImage",
    /*  222 */ "vkTransitionImageLayout",
    /*  223 */ "vkCmdPushDescriptorSet",
    /*  224 */ "vkCmdPushDescriptorSetWithTemplate",
    /*  225 */ "vkCmdBindDescriptorSets2",
    /*  226 */ "vkCmdPushConstants2",
    /*  227 */ "vkCmdPushDescriptorSet2",
    /*  228 */ "vkCmdPushDescriptorSetWithTemplate2",
    /*  229 */ "vkCmdSetLineStipple",
    /*  230 */ "vkCmdBindIndexBuffer2",
    /*  231 */ "vkGetRenderingAreaGranularity",
    /*  232 */ "vkCmdSetRenderingAttachmentLocations",
    /*  233 */ "vkCmdSetRenderingInputAttachmentIndices",
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
    /*  300 */ "vkGetDeviceCombinedImageSamplerIndexNVX",
    /*  301 */ "vkCmdDrawIndirectCountAMD",
    /*  302 */ "vkCmdDrawIndexedIndirectCountAMD",
    /*  303 */ "vkGetShaderInfoAMD",
    /*  304 */ "vkCmdBeginRenderingKHR",
    /*  305 */ "vkCmdEndRenderingKHR",
    /*  306 */ "vkCreateStreamDescriptorSurfaceGGP",
    /*  307 */ "vkGetPhysicalDeviceExternalImageFormatPropertiesNV",
    /*  308 */ "vkGetMemoryWin32HandleNV",
    /*  309 */ "vkGetPhysicalDeviceFeatures2KHR",
    /*  310 */ "vkGetPhysicalDeviceProperties2KHR",
    /*  311 */ "vkGetPhysicalDeviceFormatProperties2KHR",
    /*  312 */ "vkGetPhysicalDeviceImageFormatProperties2KHR",
    /*  313 */ "vkGetPhysicalDeviceQueueFamilyProperties2KHR",
    /*  314 */ "vkGetPhysicalDeviceMemoryProperties2KHR",
    /*  315 */ "vkGetPhysicalDeviceSparseImageFormatProperties2KHR",
    /*  316 */ "vkGetDeviceGroupPeerMemoryFeaturesKHR",
    /*  317 */ "vkCmdSetDeviceMaskKHR",
    /*  318 */ "vkCmdDispatchBaseKHR",
    /*  319 */ "vkCreateViSurfaceNN",
    /*  320 */ "vkTrimCommandPoolKHR",
    /*  321 */ "vkEnumeratePhysicalDeviceGroupsKHR",
    /*  322 */ "vkGetPhysicalDeviceExternalBufferPropertiesKHR",
    /*  323 */ "vkGetMemoryWin32HandleKHR",
    /*  324 */ "vkGetMemoryWin32HandlePropertiesKHR",
    /*  325 */ "vkGetMemoryFdKHR",
    /*  326 */ "vkGetMemoryFdPropertiesKHR",
    /*  327 */ "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR",
    /*  328 */ "vkImportSemaphoreWin32HandleKHR",
    /*  329 */ "vkGetSemaphoreWin32HandleKHR",
    /*  330 */ "vkImportSemaphoreFdKHR",
    /*  331 */ "vkGetSemaphoreFdKHR",
    /*  332 */ "vkCmdPushDescriptorSetKHR",
    /*  333 */ "vkCmdPushDescriptorSetWithTemplateKHR",
    /*  334 */ "vkCmdBeginConditionalRenderingEXT",
    /*  335 */ "vkCmdEndConditionalRenderingEXT",
    /*  336 */ "vkCreateDescriptorUpdateTemplateKHR",
    /*  337 */ "vkDestroyDescriptorUpdateTemplateKHR",
    /*  338 */ "vkUpdateDescriptorSetWithTemplateKHR",
    /*  339 */ "vkCmdSetViewportWScalingNV",
    /*  340 */ "vkReleaseDisplayEXT",
    /*  341 */ "vkAcquireXlibDisplayEXT",
    /*  342 */ "vkGetRandROutputDisplayEXT",
    /*  343 */ "vkGetPhysicalDeviceSurfaceCapabilities2EXT",
    /*  344 */ "vkDisplayPowerControlEXT",
    /*  345 */ "vkRegisterDeviceEventEXT",
    /*  346 */ "vkRegisterDisplayEventEXT",
    /*  347 */ "vkGetSwapchainCounterEXT",
    /*  348 */ "vkGetRefreshCycleDurationGOOGLE",
    /*  349 */ "vkGetPastPresentationTimingGOOGLE",
    /*  350 */ "vkCmdSetDiscardRectangleEXT",
    /*  351 */ "vkCmdSetDiscardRectangleEnableEXT",
    /*  352 */ "vkCmdSetDiscardRectangleModeEXT",
    /*  353 */ "vkSetHdrMetadataEXT",
    /*  354 */ "vkCreateRenderPass2KHR",
    /*  355 */ "vkCmdBeginRenderPass2KHR",
    /*  356 */ "vkCmdNextSubpass2KHR",
    /*  357 */ "vkCmdEndRenderPass2KHR",
    /*  358 */ "vkGetSwapchainStatusKHR",
    /*  359 */ "vkGetPhysicalDeviceExternalFencePropertiesKHR",
    /*  360 */ "vkImportFenceWin32HandleKHR",
    /*  361 */ "vkGetFenceWin32HandleKHR",
    /*  362 */ "vkImportFenceFdKHR",
    /*  363 */ "vkGetFenceFdKHR",
    /*  364 */ "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR",
    /*  365 */ "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR",
    /*  366 */ "vkAcquireProfilingLockKHR",
    /*  367 */ "vkReleaseProfilingLockKHR",
    /*  368 */ "vkGetPhysicalDeviceSurfaceCapabilities2KHR",
    /*  369 */ "vkGetPhysicalDeviceSurfaceFormats2KHR",
    /*  370 */ "vkGetPhysicalDeviceDisplayProperties2KHR",
    /*  371 */ "vkGetPhysicalDeviceDisplayPlaneProperties2KHR",
    /*  372 */ "vkGetDisplayModeProperties2KHR",
    /*  373 */ "vkGetDisplayPlaneCapabilities2KHR",
    /*  374 */ "vkCreateIOSSurfaceMVK",
    /*  375 */ "vkCreateMacOSSurfaceMVK",
    /*  376 */ "vkSetDebugUtilsObjectNameEXT",
    /*  377 */ "vkSetDebugUtilsObjectTagEXT",
    /*  378 */ "vkQueueBeginDebugUtilsLabelEXT",
    /*  379 */ "vkQueueEndDebugUtilsLabelEXT",
    /*  380 */ "vkQueueInsertDebugUtilsLabelEXT",
    /*  381 */ "vkCmdBeginDebugUtilsLabelEXT",
    /*  382 */ "vkCmdEndDebugUtilsLabelEXT",
    /*  383 */ "vkCmdInsertDebugUtilsLabelEXT",
    /*  384 */ "vkCreateDebugUtilsMessengerEXT",
    /*  385 */ "vkDestroyDebugUtilsMessengerEXT",
    /*  386 */ "vkSubmitDebugUtilsMessageEXT",
    /*  387 */ "vkGetAndroidHardwareBufferPropertiesANDROID",
    /*  388 */ "vkGetMemoryAndroidHardwareBufferANDROID",
    /*  389 */ "vkCreateExecutionGraphPipelinesAMDX",
    /*  390 */ "vkGetExecutionGraphPipelineScratchSizeAMDX",
    /*  391 */ "vkGetExecutionGraphPipelineNodeIndexAMDX",
    /*  392 */ "vkCmdInitializeGraphScratchMemoryAMDX",
    /*  393 */ "vkCmdDispatchGraphAMDX",
    /*  394 */ "vkCmdDispatchGraphIndirectAMDX",
    /*  395 */ "vkCmdDispatchGraphIndirectCountAMDX",
    /*  396 */ "vkWriteSamplerDescriptorsEXT",
    /*  397 */ "vkWriteResourceDescriptorsEXT",
    /*  398 */ "vkCmdBindSamplerHeapEXT",
    /*  399 */ "vkCmdBindResourceHeapEXT",
    /*  400 */ "vkCmdPushDataEXT",
    /*  401 */ "vkGetImageOpaqueCaptureDataEXT",
    /*  402 */ "vkGetPhysicalDeviceDescriptorSizeEXT",
    /*  403 */ "vkRegisterCustomBorderColorEXT",
    /*  404 */ "vkUnregisterCustomBorderColorEXT",
    /*  405 */ "vkGetTensorOpaqueCaptureDataARM",
    /*  406 */ "vkCmdSetSampleLocationsEXT",
    /*  407 */ "vkGetPhysicalDeviceMultisamplePropertiesEXT",
    /*  408 */ "vkGetImageMemoryRequirements2KHR",
    /*  409 */ "vkGetBufferMemoryRequirements2KHR",
    /*  410 */ "vkGetImageSparseMemoryRequirements2KHR",
    /*  411 */ "vkCreateAccelerationStructureKHR",
    /*  412 */ "vkDestroyAccelerationStructureKHR",
    /*  413 */ "vkCmdBuildAccelerationStructuresKHR",
    /*  414 */ "vkCmdBuildAccelerationStructuresIndirectKHR",
    /*  415 */ "vkBuildAccelerationStructuresKHR",
    /*  416 */ "vkCopyAccelerationStructureKHR",
    /*  417 */ "vkCopyAccelerationStructureToMemoryKHR",
    /*  418 */ "vkCopyMemoryToAccelerationStructureKHR",
    /*  419 */ "vkWriteAccelerationStructuresPropertiesKHR",
    /*  420 */ "vkCmdCopyAccelerationStructureKHR",
    /*  421 */ "vkCmdCopyAccelerationStructureToMemoryKHR",
    /*  422 */ "vkCmdCopyMemoryToAccelerationStructureKHR",
    /*  423 */ "vkGetAccelerationStructureDeviceAddressKHR",
    /*  424 */ "vkCmdWriteAccelerationStructuresPropertiesKHR",
    /*  425 */ "vkGetDeviceAccelerationStructureCompatibilityKHR",
    /*  426 */ "vkGetAccelerationStructureBuildSizesKHR",
    /*  427 */ "vkCmdTraceRaysKHR",
    /*  428 */ "vkCreateRayTracingPipelinesKHR",
    /*  429 */ "vkGetRayTracingShaderGroupHandlesKHR",
    /*  430 */ "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR",
    /*  431 */ "vkCmdTraceRaysIndirectKHR",
    /*  432 */ "vkGetRayTracingShaderGroupStackSizeKHR",
    /*  433 */ "vkCmdSetRayTracingPipelineStackSizeKHR",
    /*  434 */ "vkCreateSamplerYcbcrConversionKHR",
    /*  435 */ "vkDestroySamplerYcbcrConversionKHR",
    /*  436 */ "vkBindBufferMemory2KHR",
    /*  437 */ "vkBindImageMemory2KHR",
    /*  438 */ "vkGetImageDrmFormatModifierPropertiesEXT",
    /*  439 */ "vkCreateValidationCacheEXT",
    /*  440 */ "vkDestroyValidationCacheEXT",
    /*  441 */ "vkMergeValidationCachesEXT",
    /*  442 */ "vkGetValidationCacheDataEXT",
    /*  443 */ "vkCmdBindShadingRateImageNV",
    /*  444 */ "vkCmdSetViewportShadingRatePaletteNV",
    /*  445 */ "vkCmdSetCoarseSampleOrderNV",
    /*  446 */ "vkCreateAccelerationStructureNV",
    /*  447 */ "vkDestroyAccelerationStructureNV",
    /*  448 */ "vkGetAccelerationStructureMemoryRequirementsNV",
    /*  449 */ "vkBindAccelerationStructureMemoryNV",
    /*  450 */ "vkCmdBuildAccelerationStructureNV",
    /*  451 */ "vkCmdCopyAccelerationStructureNV",
    /*  452 */ "vkCmdTraceRaysNV",
    /*  453 */ "vkCreateRayTracingPipelinesNV",
    /*  454 */ "vkGetRayTracingShaderGroupHandlesNV",
    /*  455 */ "vkGetAccelerationStructureHandleNV",
    /*  456 */ "vkCmdWriteAccelerationStructuresPropertiesNV",
    /*  457 */ "vkCompileDeferredNV",
    /*  458 */ "vkGetDescriptorSetLayoutSupportKHR",
    /*  459 */ "vkCmdDrawIndirectCountKHR",
    /*  460 */ "vkCmdDrawIndexedIndirectCountKHR",
    /*  461 */ "vkGetMemoryHostPointerPropertiesEXT",
    /*  462 */ "vkCmdWriteBufferMarkerAMD",
    /*  463 */ "vkCmdWriteBufferMarker2AMD",
    /*  464 */ "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT",
    /*  465 */ "vkGetCalibratedTimestampsEXT",
    /*  466 */ "vkCmdDrawMeshTasksNV",
    /*  467 */ "vkCmdDrawMeshTasksIndirectNV",
    /*  468 */ "vkCmdDrawMeshTasksIndirectCountNV",
    /*  469 */ "vkCmdSetExclusiveScissorEnableNV",
    /*  470 */ "vkCmdSetExclusiveScissorNV",
    /*  471 */ "vkCmdSetCheckpointNV",
    /*  472 */ "vkGetQueueCheckpointDataNV",
    /*  473 */ "vkGetQueueCheckpointData2NV",
    /*  474 */ "vkGetSemaphoreCounterValueKHR",
    /*  475 */ "vkWaitSemaphoresKHR",
    /*  476 */ "vkSignalSemaphoreKHR",
    /*  477 */ "vkSetSwapchainPresentTimingQueueSizeEXT",
    /*  478 */ "vkGetSwapchainTimingPropertiesEXT",
    /*  479 */ "vkGetSwapchainTimeDomainPropertiesEXT",
    /*  480 */ "vkGetPastPresentationTimingEXT",
    /*  481 */ "vkInitializePerformanceApiINTEL",
    /*  482 */ "vkUninitializePerformanceApiINTEL",
    /*  483 */ "vkCmdSetPerformanceMarkerINTEL",
    /*  484 */ "vkCmdSetPerformanceStreamMarkerINTEL",
    /*  485 */ "vkCmdSetPerformanceOverrideINTEL",
    /*  486 */ "vkAcquirePerformanceConfigurationINTEL",
    /*  487 */ "vkReleasePerformanceConfigurationINTEL",
    /*  488 */ "vkQueueSetPerformanceConfigurationINTEL",
    /*  489 */ "vkGetPerformanceParameterINTEL",
    /*  490 */ "vkSetLocalDimmingAMD",
    /*  491 */ "vkCreateImagePipeSurfaceFUCHSIA",
    /*  492 */ "vkCreateMetalSurfaceEXT",
    /*  493 */ "vkGetPhysicalDeviceFragmentShadingRatesKHR",
    /*  494 */ "vkCmdSetFragmentShadingRateKHR",
    /*  495 */ "vkCmdSetRenderingAttachmentLocationsKHR",
    /*  496 */ "vkCmdSetRenderingInputAttachmentIndicesKHR",
    /*  497 */ "vkGetBufferDeviceAddressEXT",
    /*  498 */ "vkGetPhysicalDeviceToolPropertiesEXT",
    /*  499 */ "vkWaitForPresentKHR",
    /*  500 */ "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV",
    /*  501 */ "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV",
    /*  502 */ "vkGetPhysicalDeviceSurfacePresentModes2EXT",
    /*  503 */ "vkAcquireFullScreenExclusiveModeEXT",
    /*  504 */ "vkReleaseFullScreenExclusiveModeEXT",
    /*  505 */ "vkGetDeviceGroupSurfacePresentModes2EXT",
    /*  506 */ "vkCreateHeadlessSurfaceEXT",
    /*  507 */ "vkGetBufferDeviceAddressKHR",
    /*  508 */ "vkGetBufferOpaqueCaptureAddressKHR",
    /*  509 */ "vkGetDeviceMemoryOpaqueCaptureAddressKHR",
    /*  510 */ "vkCmdSetLineStippleEXT",
    /*  511 */ "vkResetQueryPoolEXT",
    /*  512 */ "vkCmdSetCullModeEXT",
    /*  513 */ "vkCmdSetFrontFaceEXT",
    /*  514 */ "vkCmdSetPrimitiveTopologyEXT",
    /*  515 */ "vkCmdSetViewportWithCountEXT",
    /*  516 */ "vkCmdSetScissorWithCountEXT",
    /*  517 */ "vkCmdBindVertexBuffers2EXT",
    /*  518 */ "vkCmdSetDepthTestEnableEXT",
    /*  519 */ "vkCmdSetDepthWriteEnableEXT",
    /*  520 */ "vkCmdSetDepthCompareOpEXT",
    /*  521 */ "vkCmdSetDepthBoundsTestEnableEXT",
    /*  522 */ "vkCmdSetStencilTestEnableEXT",
    /*  523 */ "vkCmdSetStencilOpEXT",
    /*  524 */ "vkCreateDeferredOperationKHR",
    /*  525 */ "vkDestroyDeferredOperationKHR",
    /*  526 */ "vkGetDeferredOperationMaxConcurrencyKHR",
    /*  527 */ "vkGetDeferredOperationResultKHR",
    /*  528 */ "vkDeferredOperationJoinKHR",
    /*  529 */ "vkGetPipelineExecutablePropertiesKHR",
    /*  530 */ "vkGetPipelineExecutableStatisticsKHR",
    /*  531 */ "vkGetPipelineExecutableInternalRepresentationsKHR",
    /*  532 */ "vkCopyMemoryToImageEXT",
    /*  533 */ "vkCopyImageToMemoryEXT",
    /*  534 */ "vkCopyImageToImageEXT",
    /*  535 */ "vkTransitionImageLayoutEXT",
    /*  536 */ "vkGetImageSubresourceLayout2EXT",
    /*  537 */ "vkMapMemory2KHR",
    /*  538 */ "vkUnmapMemory2KHR",
    /*  539 */ "vkReleaseSwapchainImagesEXT",
    /*  540 */ "vkGetGeneratedCommandsMemoryRequirementsNV",
    /*  541 */ "vkCmdPreprocessGeneratedCommandsNV",
    /*  542 */ "vkCmdExecuteGeneratedCommandsNV",
    /*  543 */ "vkCmdBindPipelineShaderGroupNV",
    /*  544 */ "vkCreateIndirectCommandsLayoutNV",
    /*  545 */ "vkDestroyIndirectCommandsLayoutNV",
    /*  546 */ "vkCmdSetDepthBias2EXT",
    /*  547 */ "vkAcquireDrmDisplayEXT",
    /*  548 */ "vkGetDrmDisplayEXT",
    /*  549 */ "vkCreatePrivateDataSlotEXT",
    /*  550 */ "vkDestroyPrivateDataSlotEXT",
    /*  551 */ "vkSetPrivateDataEXT",
    /*  552 */ "vkGetPrivateDataEXT",
    /*  553 */ "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR",
    /*  554 */ "vkGetEncodedVideoSessionParametersKHR",
    /*  555 */ "vkCmdEncodeVideoKHR",
    /*  556 */ "vkCreateCudaModuleNV",
    /*  557 */ "vkGetCudaModuleCacheNV",
    /*  558 */ "vkCreateCudaFunctionNV",
    /*  559 */ "vkDestroyCudaModuleNV",
    /*  560 */ "vkDestroyCudaFunctionNV",
    /*  561 */ "vkCmdCudaLaunchKernelNV",
    /*  562 */ "vkCmdDispatchTileQCOM",
    /*  563 */ "vkCmdBeginPerTileExecutionQCOM",
    /*  564 */ "vkCmdEndPerTileExecutionQCOM",
    /*  565 */ "vkExportMetalObjectsEXT",
    /*  566 */ "vkCmdSetEvent2KHR",
    /*  567 */ "vkCmdResetEvent2KHR",
    /*  568 */ "vkCmdWaitEvents2KHR",
    /*  569 */ "vkCmdPipelineBarrier2KHR",
    /*  570 */ "vkCmdWriteTimestamp2KHR",
    /*  571 */ "vkQueueSubmit2KHR",
    /*  572 */ "vkGetDescriptorSetLayoutSizeEXT",
    /*  573 */ "vkGetDescriptorSetLayoutBindingOffsetEXT",
    /*  574 */ "vkGetDescriptorEXT",
    /*  575 */ "vkCmdBindDescriptorBuffersEXT",
    /*  576 */ "vkCmdSetDescriptorBufferOffsetsEXT",
    /*  577 */ "vkCmdBindDescriptorBufferEmbeddedSamplersEXT",
    /*  578 */ "vkGetBufferOpaqueCaptureDescriptorDataEXT",
    /*  579 */ "vkGetImageOpaqueCaptureDescriptorDataEXT",
    /*  580 */ "vkGetImageViewOpaqueCaptureDescriptorDataEXT",
    /*  581 */ "vkGetSamplerOpaqueCaptureDescriptorDataEXT",
    /*  582 */ "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT",
    /*  583 */ "vkCmdSetFragmentShadingRateEnumNV",
    /*  584 */ "vkCmdDrawMeshTasksEXT",
    /*  585 */ "vkCmdDrawMeshTasksIndirectEXT",
    /*  586 */ "vkCmdDrawMeshTasksIndirectCountEXT",
    /*  587 */ "vkCmdCopyBuffer2KHR",
    /*  588 */ "vkCmdCopyImage2KHR",
    /*  589 */ "vkCmdCopyBufferToImage2KHR",
    /*  590 */ "vkCmdCopyImageToBuffer2KHR",
    /*  591 */ "vkCmdBlitImage2KHR",
    /*  592 */ "vkCmdResolveImage2KHR",
    /*  593 */ "vkGetDeviceFaultInfoEXT",
    /*  594 */ "vkAcquireWinrtDisplayNV",
    /*  595 */ "vkGetWinrtDisplayNV",
    /*  596 */ "vkCreateDirectFBSurfaceEXT",
    /*  597 */ "vkGetPhysicalDeviceDirectFBPresentationSupportEXT",
    /*  598 */ "vkCmdSetVertexInputEXT",
    /*  599 */ "vkGetMemoryZirconHandleFUCHSIA",
    /*  600 */ "vkGetMemoryZirconHandlePropertiesFUCHSIA",
    /*  601 */ "vkImportSemaphoreZirconHandleFUCHSIA",
    /*  602 */ "vkGetSemaphoreZirconHandleFUCHSIA",
    /*  603 */ "vkCreateBufferCollectionFUCHSIA",
    /*  604 */ "vkSetBufferCollectionImageConstraintsFUCHSIA",
    /*  605 */ "vkSetBufferCollectionBufferConstraintsFUCHSIA",
    /*  606 */ "vkDestroyBufferCollectionFUCHSIA",
    /*  607 */ "vkGetBufferCollectionPropertiesFUCHSIA",
    /*  608 */ "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI",
    /*  609 */ "vkCmdSubpassShadingHUAWEI",
    /*  610 */ "vkCmdBindInvocationMaskHUAWEI",
    /*  611 */ "vkGetMemoryRemoteAddressNV",
    /*  612 */ "vkGetPipelinePropertiesEXT",
    /*  613 */ "vkCmdSetPatchControlPointsEXT",
    /*  614 */ "vkCmdSetRasterizerDiscardEnableEXT",
    /*  615 */ "vkCmdSetDepthBiasEnableEXT",
    /*  616 */ "vkCmdSetLogicOpEXT",
    /*  617 */ "vkCmdSetPrimitiveRestartEnableEXT",
    /*  618 */ "vkCreateScreenSurfaceQNX",
    /*  619 */ "vkGetPhysicalDeviceScreenPresentationSupportQNX",
    /*  620 */ "vkCmdSetColorWriteEnableEXT",
    /*  621 */ "vkCmdTraceRaysIndirect2KHR",
    /*  622 */ "vkCmdDrawMultiEXT",
    /*  623 */ "vkCmdDrawMultiIndexedEXT",
    /*  624 */ "vkCreateMicromapEXT",
    /*  625 */ "vkDestroyMicromapEXT",
    /*  626 */ "vkCmdBuildMicromapsEXT",
    /*  627 */ "vkBuildMicromapsEXT",
    /*  628 */ "vkCopyMicromapEXT",
    /*  629 */ "vkCopyMicromapToMemoryEXT",
    /*  630 */ "vkCopyMemoryToMicromapEXT",
    /*  631 */ "vkWriteMicromapsPropertiesEXT",
    /*  632 */ "vkCmdCopyMicromapEXT",
    /*  633 */ "vkCmdCopyMicromapToMemoryEXT",
    /*  634 */ "vkCmdCopyMemoryToMicromapEXT",
    /*  635 */ "vkCmdWriteMicromapsPropertiesEXT",
    /*  636 */ "vkGetDeviceMicromapCompatibilityEXT",
    /*  637 */ "vkGetMicromapBuildSizesEXT",
    /*  638 */ "vkCmdDrawClusterHUAWEI",
    /*  639 */ "vkCmdDrawClusterIndirectHUAWEI",
    /*  640 */ "vkSetDeviceMemoryPriorityEXT",
    /*  641 */ "vkGetDeviceBufferMemoryRequirementsKHR",
    /*  642 */ "vkGetDeviceImageMemoryRequirementsKHR",
    /*  643 */ "vkGetDeviceImageSparseMemoryRequirementsKHR",
    /*  644 */ "vkGetDescriptorSetLayoutHostMappingInfoVALVE",
    /*  645 */ "vkGetDescriptorSetHostMappingVALVE",
    /*  646 */ "vkCmdCopyMemoryIndirectNV",
    /*  647 */ "vkCmdCopyMemoryToImageIndirectNV",
    /*  648 */ "vkCmdDecompressMemoryNV",
    /*  649 */ "vkCmdDecompressMemoryIndirectCountNV",
    /*  650 */ "vkGetPipelineIndirectMemoryRequirementsNV",
    /*  651 */ "vkCmdUpdatePipelineIndirectBufferNV",
    /*  652 */ "vkGetPipelineIndirectDeviceAddressNV",
    /*  653 */ "vkGetNativeBufferPropertiesOHOS",
    /*  654 */ "vkGetMemoryNativeBufferOHOS",
    /*  655 */ "vkCmdSetDepthClampEnableEXT",
    /*  656 */ "vkCmdSetPolygonModeEXT",
    /*  657 */ "vkCmdSetRasterizationSamplesEXT",
    /*  658 */ "vkCmdSetSampleMaskEXT",
    /*  659 */ "vkCmdSetAlphaToCoverageEnableEXT",
    /*  660 */ "vkCmdSetAlphaToOneEnableEXT",
    /*  661 */ "vkCmdSetLogicOpEnableEXT",
    /*  662 */ "vkCmdSetColorBlendEnableEXT",
    /*  663 */ "vkCmdSetColorBlendEquationEXT",
    /*  664 */ "vkCmdSetColorWriteMaskEXT",
    /*  665 */ "vkCmdSetTessellationDomainOriginEXT",
    /*  666 */ "vkCmdSetRasterizationStreamEXT",
    /*  667 */ "vkCmdSetConservativeRasterizationModeEXT",
    /*  668 */ "vkCmdSetExtraPrimitiveOverestimationSizeEXT",
    /*  669 */ "vkCmdSetDepthClipEnableEXT",
    /*  670 */ "vkCmdSetSampleLocationsEnableEXT",
    /*  671 */ "vkCmdSetColorBlendAdvancedEXT",
    /*  672 */ "vkCmdSetProvokingVertexModeEXT",
    /*  673 */ "vkCmdSetLineRasterizationModeEXT",
    /*  674 */ "vkCmdSetLineStippleEnableEXT",
    /*  675 */ "vkCmdSetDepthClipNegativeOneToOneEXT",
    /*  676 */ "vkCmdSetViewportWScalingEnableNV",
    /*  677 */ "vkCmdSetViewportSwizzleNV",
    /*  678 */ "vkCmdSetCoverageToColorEnableNV",
    /*  679 */ "vkCmdSetCoverageToColorLocationNV",
    /*  680 */ "vkCmdSetCoverageModulationModeNV",
    /*  681 */ "vkCmdSetCoverageModulationTableEnableNV",
    /*  682 */ "vkCmdSetCoverageModulationTableNV",
    /*  683 */ "vkCmdSetShadingRateImageEnableNV",
    /*  684 */ "vkCmdSetRepresentativeFragmentTestEnableNV",
    /*  685 */ "vkCmdSetCoverageReductionModeNV",
    /*  686 */ "vkCreateTensorARM",
    /*  687 */ "vkDestroyTensorARM",
    /*  688 */ "vkCreateTensorViewARM",
    /*  689 */ "vkDestroyTensorViewARM",
    /*  690 */ "vkGetTensorMemoryRequirementsARM",
    /*  691 */ "vkBindTensorMemoryARM",
    /*  692 */ "vkGetDeviceTensorMemoryRequirementsARM",
    /*  693 */ "vkCmdCopyTensorARM",
    /*  694 */ "vkGetPhysicalDeviceExternalTensorPropertiesARM",
    /*  695 */ "vkGetTensorOpaqueCaptureDescriptorDataARM",
    /*  696 */ "vkGetTensorViewOpaqueCaptureDescriptorDataARM",
    /*  697 */ "vkGetShaderModuleIdentifierEXT",
    /*  698 */ "vkGetShaderModuleCreateInfoIdentifierEXT",
    /*  699 */ "vkGetPhysicalDeviceOpticalFlowImageFormatsNV",
    /*  700 */ "vkCreateOpticalFlowSessionNV",
    /*  701 */ "vkDestroyOpticalFlowSessionNV",
    /*  702 */ "vkBindOpticalFlowSessionImageNV",
    /*  703 */ "vkCmdOpticalFlowExecuteNV",
    /*  704 */ "vkCmdBindIndexBuffer2KHR",
    /*  705 */ "vkGetRenderingAreaGranularityKHR",
    /*  706 */ "vkGetDeviceImageSubresourceLayoutKHR",
    /*  707 */ "vkGetImageSubresourceLayout2KHR",
    /*  708 */ "vkAntiLagUpdateAMD",
    /*  709 */ "vkWaitForPresent2KHR",
    /*  710 */ "vkCreateShadersEXT",
    /*  711 */ "vkDestroyShaderEXT",
    /*  712 */ "vkGetShaderBinaryDataEXT",
    /*  713 */ "vkCmdBindShadersEXT",
    /*  714 */ "vkCmdSetDepthClampRangeEXT",
    /*  715 */ "vkCreatePipelineBinariesKHR",
    /*  716 */ "vkDestroyPipelineBinaryKHR",
    /*  717 */ "vkGetPipelineKeyKHR",
    /*  718 */ "vkGetPipelineBinaryDataKHR",
    /*  719 */ "vkReleaseCapturedPipelineDataKHR",
    /*  720 */ "vkGetFramebufferTilePropertiesQCOM",
    /*  721 */ "vkGetDynamicRenderingTilePropertiesQCOM",
    /*  722 */ "vkReleaseSwapchainImagesKHR",
    /*  723 */ "vkGetPhysicalDeviceCooperativeVectorPropertiesNV",
    /*  724 */ "vkConvertCooperativeVectorMatrixNV",
    /*  725 */ "vkCmdConvertCooperativeVectorMatrixNV",
    /*  726 */ "vkSetLatencySleepModeNV",
    /*  727 */ "vkLatencySleepNV",
    /*  728 */ "vkSetLatencyMarkerNV",
    /*  729 */ "vkGetLatencyTimingsNV",
    /*  730 */ "vkQueueNotifyOutOfBandNV",
    /*  731 */ "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR",
    /*  732 */ "vkCreateDataGraphPipelinesARM",
    /*  733 */ "vkCreateDataGraphPipelineSessionARM",
    /*  734 */ "vkGetDataGraphPipelineSessionBindPointRequirementsARM",
    /*  735 */ "vkGetDataGraphPipelineSessionMemoryRequirementsARM",
    /*  736 */ "vkBindDataGraphPipelineSessionMemoryARM",
    /*  737 */ "vkDestroyDataGraphPipelineSessionARM",
    /*  738 */ "vkCmdDispatchDataGraphARM",
    /*  739 */ "vkGetDataGraphPipelineAvailablePropertiesARM",
    /*  740 */ "vkGetDataGraphPipelinePropertiesARM",
    /*  741 */ "vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM",
    /*  742 */ "vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM",
    /*  743 */ "vkCmdSetAttachmentFeedbackLoopEnableEXT",
    /*  744 */ "vkGetScreenBufferPropertiesQNX",
    /*  745 */ "vkCmdSetLineStippleKHR",
    /*  746 */ "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR",
    /*  747 */ "vkGetCalibratedTimestampsKHR",
    /*  748 */ "vkCmdBindDescriptorSets2KHR",
    /*  749 */ "vkCmdPushConstants2KHR",
    /*  750 */ "vkCmdPushDescriptorSet2KHR",
    /*  751 */ "vkCmdPushDescriptorSetWithTemplate2KHR",
    /*  752 */ "vkCmdSetDescriptorBufferOffsets2EXT",
    /*  753 */ "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT",
    /*  754 */ "vkCmdBindTileMemoryQCOM",
    /*  755 */ "vkCmdCopyMemoryIndirectKHR",
    /*  756 */ "vkCmdCopyMemoryToImageIndirectKHR",
    /*  757 */ "vkCmdDecompressMemoryEXT",
    /*  758 */ "vkCmdDecompressMemoryIndirectCountEXT",
    /*  759 */ "vkCreateExternalComputeQueueNV",
    /*  760 */ "vkDestroyExternalComputeQueueNV",
    /*  761 */ "vkGetExternalComputeQueueDataNV",
    /*  762 */ "vkGetClusterAccelerationStructureBuildSizesNV",
    /*  763 */ "vkCmdBuildClusterAccelerationStructureIndirectNV",
    /*  764 */ "vkGetPartitionedAccelerationStructuresBuildSizesNV",
    /*  765 */ "vkCmdBuildPartitionedAccelerationStructuresNV",
    /*  766 */ "vkGetGeneratedCommandsMemoryRequirementsEXT",
    /*  767 */ "vkCmdPreprocessGeneratedCommandsEXT",
    /*  768 */ "vkCmdExecuteGeneratedCommandsEXT",
    /*  769 */ "vkCreateIndirectCommandsLayoutEXT",
    /*  770 */ "vkDestroyIndirectCommandsLayoutEXT",
    /*  771 */ "vkCreateIndirectExecutionSetEXT",
    /*  772 */ "vkDestroyIndirectExecutionSetEXT",
    /*  773 */ "vkUpdateIndirectExecutionSetPipelineEXT",
    /*  774 */ "vkUpdateIndirectExecutionSetShaderEXT",
    /*  775 */ "vkCreateSurfaceOHOS",
    /*  776 */ "vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV",
    /*  777 */ "vkGetMemoryMetalHandleEXT",
    /*  778 */ "vkGetMemoryMetalHandlePropertiesEXT",
    /*  779 */ "vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM",
    /*  780 */ "vkEnumeratePhysicalDeviceShaderInstrumentationMetricsARM",
    /*  781 */ "vkCreateShaderInstrumentationARM",
    /*  782 */ "vkDestroyShaderInstrumentationARM",
    /*  783 */ "vkCmdBeginShaderInstrumentationARM",
    /*  784 */ "vkCmdEndShaderInstrumentationARM",
    /*  785 */ "vkGetShaderInstrumentationValuesARM",
    /*  786 */ "vkClearShaderInstrumentationMetricsARM",
    /*  787 */ "vkCmdEndRendering2EXT",
    /*  788 */ "vkCmdBeginCustomResolveEXT",
    /*  789 */ "vkCmdEndRendering2KHR",
    /*  790 */ "vkCmdSetComputeOccupancyPriorityNV",
    /*  791 */ "vkCreateUbmSurfaceSEC",
    /*  792 */ "vkGetPhysicalDeviceUbmPresentationSupportSEC"
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
    /*   42 */ CommandScopeDevice  , /* vkCreateQueryPool */
    /*   43 */ CommandScopeDevice  , /* vkDestroyQueryPool */
    /*   44 */ CommandScopeDevice  , /* vkGetQueryPoolResults */
    /*   45 */ CommandScopeDevice  , /* vkCreateBuffer */
    /*   46 */ CommandScopeDevice  , /* vkDestroyBuffer */
    /*   47 */ CommandScopeDevice  , /* vkCreateImage */
    /*   48 */ CommandScopeDevice  , /* vkDestroyImage */
    /*   49 */ CommandScopeDevice  , /* vkGetImageSubresourceLayout */
    /*   50 */ CommandScopeDevice  , /* vkCreateImageView */
    /*   51 */ CommandScopeDevice  , /* vkDestroyImageView */
    /*   52 */ CommandScopeDevice  , /* vkCreateCommandPool */
    /*   53 */ CommandScopeDevice  , /* vkDestroyCommandPool */
    /*   54 */ CommandScopeDevice  , /* vkResetCommandPool */
    /*   55 */ CommandScopeDevice  , /* vkAllocateCommandBuffers */
    /*   56 */ CommandScopeDevice  , /* vkFreeCommandBuffers */
    /*   57 */ CommandScopeDevice  , /* vkBeginCommandBuffer */
    /*   58 */ CommandScopeDevice  , /* vkEndCommandBuffer */
    /*   59 */ CommandScopeDevice  , /* vkResetCommandBuffer */
    /*   60 */ CommandScopeDevice  , /* vkCmdCopyBuffer */
    /*   61 */ CommandScopeDevice  , /* vkCmdCopyImage */
    /*   62 */ CommandScopeDevice  , /* vkCmdCopyBufferToImage */
    /*   63 */ CommandScopeDevice  , /* vkCmdCopyImageToBuffer */
    /*   64 */ CommandScopeDevice  , /* vkCmdUpdateBuffer */
    /*   65 */ CommandScopeDevice  , /* vkCmdFillBuffer */
    /*   66 */ CommandScopeDevice  , /* vkCmdPipelineBarrier */
    /*   67 */ CommandScopeDevice  , /* vkCmdBeginQuery */
    /*   68 */ CommandScopeDevice  , /* vkCmdEndQuery */
    /*   69 */ CommandScopeDevice  , /* vkCmdResetQueryPool */
    /*   70 */ CommandScopeDevice  , /* vkCmdWriteTimestamp */
    /*   71 */ CommandScopeDevice  , /* vkCmdCopyQueryPoolResults */
    /*   72 */ CommandScopeDevice  , /* vkCmdExecuteCommands */
    /*   73 */ CommandScopeDevice  , /* vkCreateEvent */
    /*   74 */ CommandScopeDevice  , /* vkDestroyEvent */
    /*   75 */ CommandScopeDevice  , /* vkGetEventStatus */
    /*   76 */ CommandScopeDevice  , /* vkSetEvent */
    /*   77 */ CommandScopeDevice  , /* vkResetEvent */
    /*   78 */ CommandScopeDevice  , /* vkCreateBufferView */
    /*   79 */ CommandScopeDevice  , /* vkDestroyBufferView */
    /*   80 */ CommandScopeDevice  , /* vkCreateShaderModule */
    /*   81 */ CommandScopeDevice  , /* vkDestroyShaderModule */
    /*   82 */ CommandScopeDevice  , /* vkCreatePipelineCache */
    /*   83 */ CommandScopeDevice  , /* vkDestroyPipelineCache */
    /*   84 */ CommandScopeDevice  , /* vkGetPipelineCacheData */
    /*   85 */ CommandScopeDevice  , /* vkMergePipelineCaches */
    /*   86 */ CommandScopeDevice  , /* vkCreateComputePipelines */
    /*   87 */ CommandScopeDevice  , /* vkDestroyPipeline */
    /*   88 */ CommandScopeDevice  , /* vkCreatePipelineLayout */
    /*   89 */ CommandScopeDevice  , /* vkDestroyPipelineLayout */
    /*   90 */ CommandScopeDevice  , /* vkCreateSampler */
    /*   91 */ CommandScopeDevice  , /* vkDestroySampler */
    /*   92 */ CommandScopeDevice  , /* vkCreateDescriptorSetLayout */
    /*   93 */ CommandScopeDevice  , /* vkDestroyDescriptorSetLayout */
    /*   94 */ CommandScopeDevice  , /* vkCreateDescriptorPool */
    /*   95 */ CommandScopeDevice  , /* vkDestroyDescriptorPool */
    /*   96 */ CommandScopeDevice  , /* vkResetDescriptorPool */
    /*   97 */ CommandScopeDevice  , /* vkAllocateDescriptorSets */
    /*   98 */ CommandScopeDevice  , /* vkFreeDescriptorSets */
    /*   99 */ CommandScopeDevice  , /* vkUpdateDescriptorSets */
    /*  100 */ CommandScopeDevice  , /* vkCmdBindPipeline */
    /*  101 */ CommandScopeDevice  , /* vkCmdBindDescriptorSets */
    /*  102 */ CommandScopeDevice  , /* vkCmdClearColorImage */
    /*  103 */ CommandScopeDevice  , /* vkCmdDispatch */
    /*  104 */ CommandScopeDevice  , /* vkCmdDispatchIndirect */
    /*  105 */ CommandScopeDevice  , /* vkCmdSetEvent */
    /*  106 */ CommandScopeDevice  , /* vkCmdResetEvent */
    /*  107 */ CommandScopeDevice  , /* vkCmdWaitEvents */
    /*  108 */ CommandScopeDevice  , /* vkCmdPushConstants */
    /*  109 */ CommandScopeDevice  , /* vkCreateGraphicsPipelines */
    /*  110 */ CommandScopeDevice  , /* vkCreateFramebuffer */
    /*  111 */ CommandScopeDevice  , /* vkDestroyFramebuffer */
    /*  112 */ CommandScopeDevice  , /* vkCreateRenderPass */
    /*  113 */ CommandScopeDevice  , /* vkDestroyRenderPass */
    /*  114 */ CommandScopeDevice  , /* vkGetRenderAreaGranularity */
    /*  115 */ CommandScopeDevice  , /* vkCmdSetViewport */
    /*  116 */ CommandScopeDevice  , /* vkCmdSetScissor */
    /*  117 */ CommandScopeDevice  , /* vkCmdSetLineWidth */
    /*  118 */ CommandScopeDevice  , /* vkCmdSetDepthBias */
    /*  119 */ CommandScopeDevice  , /* vkCmdSetBlendConstants */
    /*  120 */ CommandScopeDevice  , /* vkCmdSetDepthBounds */
    /*  121 */ CommandScopeDevice  , /* vkCmdSetStencilCompareMask */
    /*  122 */ CommandScopeDevice  , /* vkCmdSetStencilWriteMask */
    /*  123 */ CommandScopeDevice  , /* vkCmdSetStencilReference */
    /*  124 */ CommandScopeDevice  , /* vkCmdBindIndexBuffer */
    /*  125 */ CommandScopeDevice  , /* vkCmdBindVertexBuffers */
    /*  126 */ CommandScopeDevice  , /* vkCmdDraw */
    /*  127 */ CommandScopeDevice  , /* vkCmdDrawIndexed */
    /*  128 */ CommandScopeDevice  , /* vkCmdDrawIndirect */
    /*  129 */ CommandScopeDevice  , /* vkCmdDrawIndexedIndirect */
    /*  130 */ CommandScopeDevice  , /* vkCmdBlitImage */
    /*  131 */ CommandScopeDevice  , /* vkCmdClearDepthStencilImage */
    /*  132 */ CommandScopeDevice  , /* vkCmdClearAttachments */
    /*  133 */ CommandScopeDevice  , /* vkCmdResolveImage */
    /*  134 */ CommandScopeDevice  , /* vkCmdBeginRenderPass */
    /*  135 */ CommandScopeDevice  , /* vkCmdNextSubpass */
    /*  136 */ CommandScopeDevice  , /* vkCmdEndRenderPass */
    /*  137 */ CommandScopeGlobal  , /* vkEnumerateInstanceVersion */
    /*  138 */ CommandScopeDevice  , /* vkBindBufferMemory2 */
    /*  139 */ CommandScopeDevice  , /* vkBindImageMemory2 */
    /*  140 */ CommandScopeDevice  , /* vkGetDeviceGroupPeerMemoryFeatures */
    /*  141 */ CommandScopeDevice  , /* vkCmdSetDeviceMask */
    /*  142 */ CommandScopeInstance, /* vkEnumeratePhysicalDeviceGroups */
    /*  143 */ CommandScopeDevice  , /* vkGetImageMemoryRequirements2 */
    /*  144 */ CommandScopeDevice  , /* vkGetBufferMemoryRequirements2 */
    /*  145 */ CommandScopeDevice  , /* vkGetImageSparseMemoryRequirements2 */
    /*  146 */ CommandScopeInstance, /* vkGetPhysicalDeviceFeatures2 */
    /*  147 */ CommandScopeInstance, /* vkGetPhysicalDeviceProperties2 */
    /*  148 */ CommandScopeInstance, /* vkGetPhysicalDeviceFormatProperties2 */
    /*  149 */ CommandScopeInstance, /* vkGetPhysicalDeviceImageFormatProperties2 */
    /*  150 */ CommandScopeInstance, /* vkGetPhysicalDeviceQueueFamilyProperties2 */
    /*  151 */ CommandScopeInstance, /* vkGetPhysicalDeviceMemoryProperties2 */
    /*  152 */ CommandScopeInstance, /* vkGetPhysicalDeviceSparseImageFormatProperties2 */
    /*  153 */ CommandScopeDevice  , /* vkTrimCommandPool */
    /*  154 */ CommandScopeDevice  , /* vkGetDeviceQueue2 */
    /*  155 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalBufferProperties */
    /*  156 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalFenceProperties */
    /*  157 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalSemaphoreProperties */
    /*  158 */ CommandScopeDevice  , /* vkCmdDispatchBase */
    /*  159 */ CommandScopeDevice  , /* vkCreateDescriptorUpdateTemplate */
    /*  160 */ CommandScopeDevice  , /* vkDestroyDescriptorUpdateTemplate */
    /*  161 */ CommandScopeDevice  , /* vkUpdateDescriptorSetWithTemplate */
    /*  162 */ CommandScopeDevice  , /* vkGetDescriptorSetLayoutSupport */
    /*  163 */ CommandScopeDevice  , /* vkCreateSamplerYcbcrConversion */
    /*  164 */ CommandScopeDevice  , /* vkDestroySamplerYcbcrConversion */
    /*  165 */ CommandScopeDevice  , /* vkResetQueryPool */
    /*  166 */ CommandScopeDevice  , /* vkGetSemaphoreCounterValue */
    /*  167 */ CommandScopeDevice  , /* vkWaitSemaphores */
    /*  168 */ CommandScopeDevice  , /* vkSignalSemaphore */
    /*  169 */ CommandScopeDevice  , /* vkGetBufferDeviceAddress */
    /*  170 */ CommandScopeDevice  , /* vkGetBufferOpaqueCaptureAddress */
    /*  171 */ CommandScopeDevice  , /* vkGetDeviceMemoryOpaqueCaptureAddress */
    /*  172 */ CommandScopeDevice  , /* vkCmdDrawIndirectCount */
    /*  173 */ CommandScopeDevice  , /* vkCmdDrawIndexedIndirectCount */
    /*  174 */ CommandScopeDevice  , /* vkCreateRenderPass2 */
    /*  175 */ CommandScopeDevice  , /* vkCmdBeginRenderPass2 */
    /*  176 */ CommandScopeDevice  , /* vkCmdNextSubpass2 */
    /*  177 */ CommandScopeDevice  , /* vkCmdEndRenderPass2 */
    /*  178 */ CommandScopeInstance, /* vkGetPhysicalDeviceToolProperties */
    /*  179 */ CommandScopeDevice  , /* vkCreatePrivateDataSlot */
    /*  180 */ CommandScopeDevice  , /* vkDestroyPrivateDataSlot */
    /*  181 */ CommandScopeDevice  , /* vkSetPrivateData */
    /*  182 */ CommandScopeDevice  , /* vkGetPrivateData */
    /*  183 */ CommandScopeDevice  , /* vkCmdPipelineBarrier2 */
    /*  184 */ CommandScopeDevice  , /* vkCmdWriteTimestamp2 */
    /*  185 */ CommandScopeDevice  , /* vkQueueSubmit2 */
    /*  186 */ CommandScopeDevice  , /* vkCmdCopyBuffer2 */
    /*  187 */ CommandScopeDevice  , /* vkCmdCopyImage2 */
    /*  188 */ CommandScopeDevice  , /* vkCmdCopyBufferToImage2 */
    /*  189 */ CommandScopeDevice  , /* vkCmdCopyImageToBuffer2 */
    /*  190 */ CommandScopeDevice  , /* vkGetDeviceBufferMemoryRequirements */
    /*  191 */ CommandScopeDevice  , /* vkGetDeviceImageMemoryRequirements */
    /*  192 */ CommandScopeDevice  , /* vkGetDeviceImageSparseMemoryRequirements */
    /*  193 */ CommandScopeDevice  , /* vkCmdSetEvent2 */
    /*  194 */ CommandScopeDevice  , /* vkCmdResetEvent2 */
    /*  195 */ CommandScopeDevice  , /* vkCmdWaitEvents2 */
    /*  196 */ CommandScopeDevice  , /* vkCmdBlitImage2 */
    /*  197 */ CommandScopeDevice  , /* vkCmdResolveImage2 */
    /*  198 */ CommandScopeDevice  , /* vkCmdBeginRendering */
    /*  199 */ CommandScopeDevice  , /* vkCmdEndRendering */
    /*  200 */ CommandScopeDevice  , /* vkCmdSetCullMode */
    /*  201 */ CommandScopeDevice  , /* vkCmdSetFrontFace */
    /*  202 */ CommandScopeDevice  , /* vkCmdSetPrimitiveTopology */
    /*  203 */ CommandScopeDevice  , /* vkCmdSetViewportWithCount */
    /*  204 */ CommandScopeDevice  , /* vkCmdSetScissorWithCount */
    /*  205 */ CommandScopeDevice  , /* vkCmdBindVertexBuffers2 */
    /*  206 */ CommandScopeDevice  , /* vkCmdSetDepthTestEnable */
    /*  207 */ CommandScopeDevice  , /* vkCmdSetDepthWriteEnable */
    /*  208 */ CommandScopeDevice  , /* vkCmdSetDepthCompareOp */
    /*  209 */ CommandScopeDevice  , /* vkCmdSetDepthBoundsTestEnable */
    /*  210 */ CommandScopeDevice  , /* vkCmdSetStencilTestEnable */
    /*  211 */ CommandScopeDevice  , /* vkCmdSetStencilOp */
    /*  212 */ CommandScopeDevice  , /* vkCmdSetRasterizerDiscardEnable */
    /*  213 */ CommandScopeDevice  , /* vkCmdSetDepthBiasEnable */
    /*  214 */ CommandScopeDevice  , /* vkCmdSetPrimitiveRestartEnable */
    /*  215 */ CommandScopeDevice  , /* vkMapMemory2 */
    /*  216 */ CommandScopeDevice  , /* vkUnmapMemory2 */
    /*  217 */ CommandScopeDevice  , /* vkGetDeviceImageSubresourceLayout */
    /*  218 */ CommandScopeDevice  , /* vkGetImageSubresourceLayout2 */
    /*  219 */ CommandScopeDevice  , /* vkCopyMemoryToImage */
    /*  220 */ CommandScopeDevice  , /* vkCopyImageToMemory */
    /*  221 */ CommandScopeDevice  , /* vkCopyImageToImage */
    /*  222 */ CommandScopeDevice  , /* vkTransitionImageLayout */
    /*  223 */ CommandScopeDevice  , /* vkCmdPushDescriptorSet */
    /*  224 */ CommandScopeDevice  , /* vkCmdPushDescriptorSetWithTemplate */
    /*  225 */ CommandScopeDevice  , /* vkCmdBindDescriptorSets2 */
    /*  226 */ CommandScopeDevice  , /* vkCmdPushConstants2 */
    /*  227 */ CommandScopeDevice  , /* vkCmdPushDescriptorSet2 */
    /*  228 */ CommandScopeDevice  , /* vkCmdPushDescriptorSetWithTemplate2 */
    /*  229 */ CommandScopeDevice  , /* vkCmdSetLineStipple */
    /*  230 */ CommandScopeDevice  , /* vkCmdBindIndexBuffer2 */
    /*  231 */ CommandScopeDevice  , /* vkGetRenderingAreaGranularity */
    /*  232 */ CommandScopeDevice  , /* vkCmdSetRenderingAttachmentLocations */
    /*  233 */ CommandScopeDevice  , /* vkCmdSetRenderingInputAttachmentIndices */
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
    /*  300 */ CommandScopeDevice  , /* vkGetDeviceCombinedImageSamplerIndexNVX */
    /*  301 */ CommandScopeDevice  , /* vkCmdDrawIndirectCountAMD */
    /*  302 */ CommandScopeDevice  , /* vkCmdDrawIndexedIndirectCountAMD */
    /*  303 */ CommandScopeDevice  , /* vkGetShaderInfoAMD */
    /*  304 */ CommandScopeDevice  , /* vkCmdBeginRenderingKHR */
    /*  305 */ CommandScopeDevice  , /* vkCmdEndRenderingKHR */
    /*  306 */ CommandScopeInstance, /* vkCreateStreamDescriptorSurfaceGGP */
    /*  307 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalImageFormatPropertiesNV */
    /*  308 */ CommandScopeDevice  , /* vkGetMemoryWin32HandleNV */
    /*  309 */ CommandScopeInstance, /* vkGetPhysicalDeviceFeatures2KHR */
    /*  310 */ CommandScopeInstance, /* vkGetPhysicalDeviceProperties2KHR */
    /*  311 */ CommandScopeInstance, /* vkGetPhysicalDeviceFormatProperties2KHR */
    /*  312 */ CommandScopeInstance, /* vkGetPhysicalDeviceImageFormatProperties2KHR */
    /*  313 */ CommandScopeInstance, /* vkGetPhysicalDeviceQueueFamilyProperties2KHR */
    /*  314 */ CommandScopeInstance, /* vkGetPhysicalDeviceMemoryProperties2KHR */
    /*  315 */ CommandScopeInstance, /* vkGetPhysicalDeviceSparseImageFormatProperties2KHR */
    /*  316 */ CommandScopeDevice  , /* vkGetDeviceGroupPeerMemoryFeaturesKHR */
    /*  317 */ CommandScopeDevice  , /* vkCmdSetDeviceMaskKHR */
    /*  318 */ CommandScopeDevice  , /* vkCmdDispatchBaseKHR */
    /*  319 */ CommandScopeInstance, /* vkCreateViSurfaceNN */
    /*  320 */ CommandScopeDevice  , /* vkTrimCommandPoolKHR */
    /*  321 */ CommandScopeInstance, /* vkEnumeratePhysicalDeviceGroupsKHR */
    /*  322 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalBufferPropertiesKHR */
    /*  323 */ CommandScopeDevice  , /* vkGetMemoryWin32HandleKHR */
    /*  324 */ CommandScopeDevice  , /* vkGetMemoryWin32HandlePropertiesKHR */
    /*  325 */ CommandScopeDevice  , /* vkGetMemoryFdKHR */
    /*  326 */ CommandScopeDevice  , /* vkGetMemoryFdPropertiesKHR */
    /*  327 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalSemaphorePropertiesKHR */
    /*  328 */ CommandScopeDevice  , /* vkImportSemaphoreWin32HandleKHR */
    /*  329 */ CommandScopeDevice  , /* vkGetSemaphoreWin32HandleKHR */
    /*  330 */ CommandScopeDevice  , /* vkImportSemaphoreFdKHR */
    /*  331 */ CommandScopeDevice  , /* vkGetSemaphoreFdKHR */
    /*  332 */ CommandScopeDevice  , /* vkCmdPushDescriptorSetKHR */
    /*  333 */ CommandScopeDevice  , /* vkCmdPushDescriptorSetWithTemplateKHR */
    /*  334 */ CommandScopeDevice  , /* vkCmdBeginConditionalRenderingEXT */
    /*  335 */ CommandScopeDevice  , /* vkCmdEndConditionalRenderingEXT */
    /*  336 */ CommandScopeDevice  , /* vkCreateDescriptorUpdateTemplateKHR */
    /*  337 */ CommandScopeDevice  , /* vkDestroyDescriptorUpdateTemplateKHR */
    /*  338 */ CommandScopeDevice  , /* vkUpdateDescriptorSetWithTemplateKHR */
    /*  339 */ CommandScopeDevice  , /* vkCmdSetViewportWScalingNV */
    /*  340 */ CommandScopeInstance, /* vkReleaseDisplayEXT */
    /*  341 */ CommandScopeInstance, /* vkAcquireXlibDisplayEXT */
    /*  342 */ CommandScopeInstance, /* vkGetRandROutputDisplayEXT */
    /*  343 */ CommandScopeInstance, /* vkGetPhysicalDeviceSurfaceCapabilities2EXT */
    /*  344 */ CommandScopeDevice  , /* vkDisplayPowerControlEXT */
    /*  345 */ CommandScopeDevice  , /* vkRegisterDeviceEventEXT */
    /*  346 */ CommandScopeDevice  , /* vkRegisterDisplayEventEXT */
    /*  347 */ CommandScopeDevice  , /* vkGetSwapchainCounterEXT */
    /*  348 */ CommandScopeDevice  , /* vkGetRefreshCycleDurationGOOGLE */
    /*  349 */ CommandScopeDevice  , /* vkGetPastPresentationTimingGOOGLE */
    /*  350 */ CommandScopeDevice  , /* vkCmdSetDiscardRectangleEXT */
    /*  351 */ CommandScopeDevice  , /* vkCmdSetDiscardRectangleEnableEXT */
    /*  352 */ CommandScopeDevice  , /* vkCmdSetDiscardRectangleModeEXT */
    /*  353 */ CommandScopeDevice  , /* vkSetHdrMetadataEXT */
    /*  354 */ CommandScopeDevice  , /* vkCreateRenderPass2KHR */
    /*  355 */ CommandScopeDevice  , /* vkCmdBeginRenderPass2KHR */
    /*  356 */ CommandScopeDevice  , /* vkCmdNextSubpass2KHR */
    /*  357 */ CommandScopeDevice  , /* vkCmdEndRenderPass2KHR */
    /*  358 */ CommandScopeDevice  , /* vkGetSwapchainStatusKHR */
    /*  359 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalFencePropertiesKHR */
    /*  360 */ CommandScopeDevice  , /* vkImportFenceWin32HandleKHR */
    /*  361 */ CommandScopeDevice  , /* vkGetFenceWin32HandleKHR */
    /*  362 */ CommandScopeDevice  , /* vkImportFenceFdKHR */
    /*  363 */ CommandScopeDevice  , /* vkGetFenceFdKHR */
    /*  364 */ CommandScopeInstance, /* vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR */
    /*  365 */ CommandScopeInstance, /* vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR */
    /*  366 */ CommandScopeDevice  , /* vkAcquireProfilingLockKHR */
    /*  367 */ CommandScopeDevice  , /* vkReleaseProfilingLockKHR */
    /*  368 */ CommandScopeInstance, /* vkGetPhysicalDeviceSurfaceCapabilities2KHR */
    /*  369 */ CommandScopeInstance, /* vkGetPhysicalDeviceSurfaceFormats2KHR */
    /*  370 */ CommandScopeInstance, /* vkGetPhysicalDeviceDisplayProperties2KHR */
    /*  371 */ CommandScopeInstance, /* vkGetPhysicalDeviceDisplayPlaneProperties2KHR */
    /*  372 */ CommandScopeInstance, /* vkGetDisplayModeProperties2KHR */
    /*  373 */ CommandScopeInstance, /* vkGetDisplayPlaneCapabilities2KHR */
    /*  374 */ CommandScopeInstance, /* vkCreateIOSSurfaceMVK */
    /*  375 */ CommandScopeInstance, /* vkCreateMacOSSurfaceMVK */
    /*  376 */ CommandScopeDevice  , /* vkSetDebugUtilsObjectNameEXT */
    /*  377 */ CommandScopeDevice  , /* vkSetDebugUtilsObjectTagEXT */
    /*  378 */ CommandScopeDevice  , /* vkQueueBeginDebugUtilsLabelEXT */
    /*  379 */ CommandScopeDevice  , /* vkQueueEndDebugUtilsLabelEXT */
    /*  380 */ CommandScopeDevice  , /* vkQueueInsertDebugUtilsLabelEXT */
    /*  381 */ CommandScopeDevice  , /* vkCmdBeginDebugUtilsLabelEXT */
    /*  382 */ CommandScopeDevice  , /* vkCmdEndDebugUtilsLabelEXT */
    /*  383 */ CommandScopeDevice  , /* vkCmdInsertDebugUtilsLabelEXT */
    /*  384 */ CommandScopeInstance, /* vkCreateDebugUtilsMessengerEXT */
    /*  385 */ CommandScopeInstance, /* vkDestroyDebugUtilsMessengerEXT */
    /*  386 */ CommandScopeInstance, /* vkSubmitDebugUtilsMessageEXT */
    /*  387 */ CommandScopeDevice  , /* vkGetAndroidHardwareBufferPropertiesANDROID */
    /*  388 */ CommandScopeDevice  , /* vkGetMemoryAndroidHardwareBufferANDROID */
    /*  389 */ CommandScopeDevice  , /* vkCreateExecutionGraphPipelinesAMDX */
    /*  390 */ CommandScopeDevice  , /* vkGetExecutionGraphPipelineScratchSizeAMDX */
    /*  391 */ CommandScopeDevice  , /* vkGetExecutionGraphPipelineNodeIndexAMDX */
    /*  392 */ CommandScopeDevice  , /* vkCmdInitializeGraphScratchMemoryAMDX */
    /*  393 */ CommandScopeDevice  , /* vkCmdDispatchGraphAMDX */
    /*  394 */ CommandScopeDevice  , /* vkCmdDispatchGraphIndirectAMDX */
    /*  395 */ CommandScopeDevice  , /* vkCmdDispatchGraphIndirectCountAMDX */
    /*  396 */ CommandScopeDevice  , /* vkWriteSamplerDescriptorsEXT */
    /*  397 */ CommandScopeDevice  , /* vkWriteResourceDescriptorsEXT */
    /*  398 */ CommandScopeDevice  , /* vkCmdBindSamplerHeapEXT */
    /*  399 */ CommandScopeDevice  , /* vkCmdBindResourceHeapEXT */
    /*  400 */ CommandScopeDevice  , /* vkCmdPushDataEXT */
    /*  401 */ CommandScopeDevice  , /* vkGetImageOpaqueCaptureDataEXT */
    /*  402 */ CommandScopeInstance, /* vkGetPhysicalDeviceDescriptorSizeEXT */
    /*  403 */ CommandScopeDevice  , /* vkRegisterCustomBorderColorEXT */
    /*  404 */ CommandScopeDevice  , /* vkUnregisterCustomBorderColorEXT */
    /*  405 */ CommandScopeDevice  , /* vkGetTensorOpaqueCaptureDataARM */
    /*  406 */ CommandScopeDevice  , /* vkCmdSetSampleLocationsEXT */
    /*  407 */ CommandScopeInstance, /* vkGetPhysicalDeviceMultisamplePropertiesEXT */
    /*  408 */ CommandScopeDevice  , /* vkGetImageMemoryRequirements2KHR */
    /*  409 */ CommandScopeDevice  , /* vkGetBufferMemoryRequirements2KHR */
    /*  410 */ CommandScopeDevice  , /* vkGetImageSparseMemoryRequirements2KHR */
    /*  411 */ CommandScopeDevice  , /* vkCreateAccelerationStructureKHR */
    /*  412 */ CommandScopeDevice  , /* vkDestroyAccelerationStructureKHR */
    /*  413 */ CommandScopeDevice  , /* vkCmdBuildAccelerationStructuresKHR */
    /*  414 */ CommandScopeDevice  , /* vkCmdBuildAccelerationStructuresIndirectKHR */
    /*  415 */ CommandScopeDevice  , /* vkBuildAccelerationStructuresKHR */
    /*  416 */ CommandScopeDevice  , /* vkCopyAccelerationStructureKHR */
    /*  417 */ CommandScopeDevice  , /* vkCopyAccelerationStructureToMemoryKHR */
    /*  418 */ CommandScopeDevice  , /* vkCopyMemoryToAccelerationStructureKHR */
    /*  419 */ CommandScopeDevice  , /* vkWriteAccelerationStructuresPropertiesKHR */
    /*  420 */ CommandScopeDevice  , /* vkCmdCopyAccelerationStructureKHR */
    /*  421 */ CommandScopeDevice  , /* vkCmdCopyAccelerationStructureToMemoryKHR */
    /*  422 */ CommandScopeDevice  , /* vkCmdCopyMemoryToAccelerationStructureKHR */
    /*  423 */ CommandScopeDevice  , /* vkGetAccelerationStructureDeviceAddressKHR */
    /*  424 */ CommandScopeDevice  , /* vkCmdWriteAccelerationStructuresPropertiesKHR */
    /*  425 */ CommandScopeDevice  , /* vkGetDeviceAccelerationStructureCompatibilityKHR */
    /*  426 */ CommandScopeDevice  , /* vkGetAccelerationStructureBuildSizesKHR */
    /*  427 */ CommandScopeDevice  , /* vkCmdTraceRaysKHR */
    /*  428 */ CommandScopeDevice  , /* vkCreateRayTracingPipelinesKHR */
    /*  429 */ CommandScopeDevice  , /* vkGetRayTracingShaderGroupHandlesKHR */
    /*  430 */ CommandScopeDevice  , /* vkGetRayTracingCaptureReplayShaderGroupHandlesKHR */
    /*  431 */ CommandScopeDevice  , /* vkCmdTraceRaysIndirectKHR */
    /*  432 */ CommandScopeDevice  , /* vkGetRayTracingShaderGroupStackSizeKHR */
    /*  433 */ CommandScopeDevice  , /* vkCmdSetRayTracingPipelineStackSizeKHR */
    /*  434 */ CommandScopeDevice  , /* vkCreateSamplerYcbcrConversionKHR */
    /*  435 */ CommandScopeDevice  , /* vkDestroySamplerYcbcrConversionKHR */
    /*  436 */ CommandScopeDevice  , /* vkBindBufferMemory2KHR */
    /*  437 */ CommandScopeDevice  , /* vkBindImageMemory2KHR */
    /*  438 */ CommandScopeDevice  , /* vkGetImageDrmFormatModifierPropertiesEXT */
    /*  439 */ CommandScopeDevice  , /* vkCreateValidationCacheEXT */
    /*  440 */ CommandScopeDevice  , /* vkDestroyValidationCacheEXT */
    /*  441 */ CommandScopeDevice  , /* vkMergeValidationCachesEXT */
    /*  442 */ CommandScopeDevice  , /* vkGetValidationCacheDataEXT */
    /*  443 */ CommandScopeDevice  , /* vkCmdBindShadingRateImageNV */
    /*  444 */ CommandScopeDevice  , /* vkCmdSetViewportShadingRatePaletteNV */
    /*  445 */ CommandScopeDevice  , /* vkCmdSetCoarseSampleOrderNV */
    /*  446 */ CommandScopeDevice  , /* vkCreateAccelerationStructureNV */
    /*  447 */ CommandScopeDevice  , /* vkDestroyAccelerationStructureNV */
    /*  448 */ CommandScopeDevice  , /* vkGetAccelerationStructureMemoryRequirementsNV */
    /*  449 */ CommandScopeDevice  , /* vkBindAccelerationStructureMemoryNV */
    /*  450 */ CommandScopeDevice  , /* vkCmdBuildAccelerationStructureNV */
    /*  451 */ CommandScopeDevice  , /* vkCmdCopyAccelerationStructureNV */
    /*  452 */ CommandScopeDevice  , /* vkCmdTraceRaysNV */
    /*  453 */ CommandScopeDevice  , /* vkCreateRayTracingPipelinesNV */
    /*  454 */ CommandScopeDevice  , /* vkGetRayTracingShaderGroupHandlesNV */
    /*  455 */ CommandScopeDevice  , /* vkGetAccelerationStructureHandleNV */
    /*  456 */ CommandScopeDevice  , /* vkCmdWriteAccelerationStructuresPropertiesNV */
    /*  457 */ CommandScopeDevice  , /* vkCompileDeferredNV */
    /*  458 */ CommandScopeDevice  , /* vkGetDescriptorSetLayoutSupportKHR */
    /*  459 */ CommandScopeDevice  , /* vkCmdDrawIndirectCountKHR */
    /*  460 */ CommandScopeDevice  , /* vkCmdDrawIndexedIndirectCountKHR */
    /*  461 */ CommandScopeDevice  , /* vkGetMemoryHostPointerPropertiesEXT */
    /*  462 */ CommandScopeDevice  , /* vkCmdWriteBufferMarkerAMD */
    /*  463 */ CommandScopeDevice  , /* vkCmdWriteBufferMarker2AMD */
    /*  464 */ CommandScopeInstance, /* vkGetPhysicalDeviceCalibrateableTimeDomainsEXT */
    /*  465 */ CommandScopeDevice  , /* vkGetCalibratedTimestampsEXT */
    /*  466 */ CommandScopeDevice  , /* vkCmdDrawMeshTasksNV */
    /*  467 */ CommandScopeDevice  , /* vkCmdDrawMeshTasksIndirectNV */
    /*  468 */ CommandScopeDevice  , /* vkCmdDrawMeshTasksIndirectCountNV */
    /*  469 */ CommandScopeDevice  , /* vkCmdSetExclusiveScissorEnableNV */
    /*  470 */ CommandScopeDevice  , /* vkCmdSetExclusiveScissorNV */
    /*  471 */ CommandScopeDevice  , /* vkCmdSetCheckpointNV */
    /*  472 */ CommandScopeDevice  , /* vkGetQueueCheckpointDataNV */
    /*  473 */ CommandScopeDevice  , /* vkGetQueueCheckpointData2NV */
    /*  474 */ CommandScopeDevice  , /* vkGetSemaphoreCounterValueKHR */
    /*  475 */ CommandScopeDevice  , /* vkWaitSemaphoresKHR */
    /*  476 */ CommandScopeDevice  , /* vkSignalSemaphoreKHR */
    /*  477 */ CommandScopeDevice  , /* vkSetSwapchainPresentTimingQueueSizeEXT */
    /*  478 */ CommandScopeDevice  , /* vkGetSwapchainTimingPropertiesEXT */
    /*  479 */ CommandScopeDevice  , /* vkGetSwapchainTimeDomainPropertiesEXT */
    /*  480 */ CommandScopeDevice  , /* vkGetPastPresentationTimingEXT */
    /*  481 */ CommandScopeDevice  , /* vkInitializePerformanceApiINTEL */
    /*  482 */ CommandScopeDevice  , /* vkUninitializePerformanceApiINTEL */
    /*  483 */ CommandScopeDevice  , /* vkCmdSetPerformanceMarkerINTEL */
    /*  484 */ CommandScopeDevice  , /* vkCmdSetPerformanceStreamMarkerINTEL */
    /*  485 */ CommandScopeDevice  , /* vkCmdSetPerformanceOverrideINTEL */
    /*  486 */ CommandScopeDevice  , /* vkAcquirePerformanceConfigurationINTEL */
    /*  487 */ CommandScopeDevice  , /* vkReleasePerformanceConfigurationINTEL */
    /*  488 */ CommandScopeDevice  , /* vkQueueSetPerformanceConfigurationINTEL */
    /*  489 */ CommandScopeDevice  , /* vkGetPerformanceParameterINTEL */
    /*  490 */ CommandScopeDevice  , /* vkSetLocalDimmingAMD */
    /*  491 */ CommandScopeInstance, /* vkCreateImagePipeSurfaceFUCHSIA */
    /*  492 */ CommandScopeInstance, /* vkCreateMetalSurfaceEXT */
    /*  493 */ CommandScopeInstance, /* vkGetPhysicalDeviceFragmentShadingRatesKHR */
    /*  494 */ CommandScopeDevice  , /* vkCmdSetFragmentShadingRateKHR */
    /*  495 */ CommandScopeDevice  , /* vkCmdSetRenderingAttachmentLocationsKHR */
    /*  496 */ CommandScopeDevice  , /* vkCmdSetRenderingInputAttachmentIndicesKHR */
    /*  497 */ CommandScopeDevice  , /* vkGetBufferDeviceAddressEXT */
    /*  498 */ CommandScopeInstance, /* vkGetPhysicalDeviceToolPropertiesEXT */
    /*  499 */ CommandScopeDevice  , /* vkWaitForPresentKHR */
    /*  500 */ CommandScopeInstance, /* vkGetPhysicalDeviceCooperativeMatrixPropertiesNV */
    /*  501 */ CommandScopeInstance, /* vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV */
    /*  502 */ CommandScopeInstance, /* vkGetPhysicalDeviceSurfacePresentModes2EXT */
    /*  503 */ CommandScopeDevice  , /* vkAcquireFullScreenExclusiveModeEXT */
    /*  504 */ CommandScopeDevice  , /* vkReleaseFullScreenExclusiveModeEXT */
    /*  505 */ CommandScopeDevice  , /* vkGetDeviceGroupSurfacePresentModes2EXT */
    /*  506 */ CommandScopeInstance, /* vkCreateHeadlessSurfaceEXT */
    /*  507 */ CommandScopeDevice  , /* vkGetBufferDeviceAddressKHR */
    /*  508 */ CommandScopeDevice  , /* vkGetBufferOpaqueCaptureAddressKHR */
    /*  509 */ CommandScopeDevice  , /* vkGetDeviceMemoryOpaqueCaptureAddressKHR */
    /*  510 */ CommandScopeDevice  , /* vkCmdSetLineStippleEXT */
    /*  511 */ CommandScopeDevice  , /* vkResetQueryPoolEXT */
    /*  512 */ CommandScopeDevice  , /* vkCmdSetCullModeEXT */
    /*  513 */ CommandScopeDevice  , /* vkCmdSetFrontFaceEXT */
    /*  514 */ CommandScopeDevice  , /* vkCmdSetPrimitiveTopologyEXT */
    /*  515 */ CommandScopeDevice  , /* vkCmdSetViewportWithCountEXT */
    /*  516 */ CommandScopeDevice  , /* vkCmdSetScissorWithCountEXT */
    /*  517 */ CommandScopeDevice  , /* vkCmdBindVertexBuffers2EXT */
    /*  518 */ CommandScopeDevice  , /* vkCmdSetDepthTestEnableEXT */
    /*  519 */ CommandScopeDevice  , /* vkCmdSetDepthWriteEnableEXT */
    /*  520 */ CommandScopeDevice  , /* vkCmdSetDepthCompareOpEXT */
    /*  521 */ CommandScopeDevice  , /* vkCmdSetDepthBoundsTestEnableEXT */
    /*  522 */ CommandScopeDevice  , /* vkCmdSetStencilTestEnableEXT */
    /*  523 */ CommandScopeDevice  , /* vkCmdSetStencilOpEXT */
    /*  524 */ CommandScopeDevice  , /* vkCreateDeferredOperationKHR */
    /*  525 */ CommandScopeDevice  , /* vkDestroyDeferredOperationKHR */
    /*  526 */ CommandScopeDevice  , /* vkGetDeferredOperationMaxConcurrencyKHR */
    /*  527 */ CommandScopeDevice  , /* vkGetDeferredOperationResultKHR */
    /*  528 */ CommandScopeDevice  , /* vkDeferredOperationJoinKHR */
    /*  529 */ CommandScopeDevice  , /* vkGetPipelineExecutablePropertiesKHR */
    /*  530 */ CommandScopeDevice  , /* vkGetPipelineExecutableStatisticsKHR */
    /*  531 */ CommandScopeDevice  , /* vkGetPipelineExecutableInternalRepresentationsKHR */
    /*  532 */ CommandScopeDevice  , /* vkCopyMemoryToImageEXT */
    /*  533 */ CommandScopeDevice  , /* vkCopyImageToMemoryEXT */
    /*  534 */ CommandScopeDevice  , /* vkCopyImageToImageEXT */
    /*  535 */ CommandScopeDevice  , /* vkTransitionImageLayoutEXT */
    /*  536 */ CommandScopeDevice  , /* vkGetImageSubresourceLayout2EXT */
    /*  537 */ CommandScopeDevice  , /* vkMapMemory2KHR */
    /*  538 */ CommandScopeDevice  , /* vkUnmapMemory2KHR */
    /*  539 */ CommandScopeDevice  , /* vkReleaseSwapchainImagesEXT */
    /*  540 */ CommandScopeDevice  , /* vkGetGeneratedCommandsMemoryRequirementsNV */
    /*  541 */ CommandScopeDevice  , /* vkCmdPreprocessGeneratedCommandsNV */
    /*  542 */ CommandScopeDevice  , /* vkCmdExecuteGeneratedCommandsNV */
    /*  543 */ CommandScopeDevice  , /* vkCmdBindPipelineShaderGroupNV */
    /*  544 */ CommandScopeDevice  , /* vkCreateIndirectCommandsLayoutNV */
    /*  545 */ CommandScopeDevice  , /* vkDestroyIndirectCommandsLayoutNV */
    /*  546 */ CommandScopeDevice  , /* vkCmdSetDepthBias2EXT */
    /*  547 */ CommandScopeInstance, /* vkAcquireDrmDisplayEXT */
    /*  548 */ CommandScopeInstance, /* vkGetDrmDisplayEXT */
    /*  549 */ CommandScopeDevice  , /* vkCreatePrivateDataSlotEXT */
    /*  550 */ CommandScopeDevice  , /* vkDestroyPrivateDataSlotEXT */
    /*  551 */ CommandScopeDevice  , /* vkSetPrivateDataEXT */
    /*  552 */ CommandScopeDevice  , /* vkGetPrivateDataEXT */
    /*  553 */ CommandScopeInstance, /* vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR */
    /*  554 */ CommandScopeDevice  , /* vkGetEncodedVideoSessionParametersKHR */
    /*  555 */ CommandScopeDevice  , /* vkCmdEncodeVideoKHR */
    /*  556 */ CommandScopeDevice  , /* vkCreateCudaModuleNV */
    /*  557 */ CommandScopeDevice  , /* vkGetCudaModuleCacheNV */
    /*  558 */ CommandScopeDevice  , /* vkCreateCudaFunctionNV */
    /*  559 */ CommandScopeDevice  , /* vkDestroyCudaModuleNV */
    /*  560 */ CommandScopeDevice  , /* vkDestroyCudaFunctionNV */
    /*  561 */ CommandScopeDevice  , /* vkCmdCudaLaunchKernelNV */
    /*  562 */ CommandScopeDevice  , /* vkCmdDispatchTileQCOM */
    /*  563 */ CommandScopeDevice  , /* vkCmdBeginPerTileExecutionQCOM */
    /*  564 */ CommandScopeDevice  , /* vkCmdEndPerTileExecutionQCOM */
    /*  565 */ CommandScopeDevice  , /* vkExportMetalObjectsEXT */
    /*  566 */ CommandScopeDevice  , /* vkCmdSetEvent2KHR */
    /*  567 */ CommandScopeDevice  , /* vkCmdResetEvent2KHR */
    /*  568 */ CommandScopeDevice  , /* vkCmdWaitEvents2KHR */
    /*  569 */ CommandScopeDevice  , /* vkCmdPipelineBarrier2KHR */
    /*  570 */ CommandScopeDevice  , /* vkCmdWriteTimestamp2KHR */
    /*  571 */ CommandScopeDevice  , /* vkQueueSubmit2KHR */
    /*  572 */ CommandScopeDevice  , /* vkGetDescriptorSetLayoutSizeEXT */
    /*  573 */ CommandScopeDevice  , /* vkGetDescriptorSetLayoutBindingOffsetEXT */
    /*  574 */ CommandScopeDevice  , /* vkGetDescriptorEXT */
    /*  575 */ CommandScopeDevice  , /* vkCmdBindDescriptorBuffersEXT */
    /*  576 */ CommandScopeDevice  , /* vkCmdSetDescriptorBufferOffsetsEXT */
    /*  577 */ CommandScopeDevice  , /* vkCmdBindDescriptorBufferEmbeddedSamplersEXT */
    /*  578 */ CommandScopeDevice  , /* vkGetBufferOpaqueCaptureDescriptorDataEXT */
    /*  579 */ CommandScopeDevice  , /* vkGetImageOpaqueCaptureDescriptorDataEXT */
    /*  580 */ CommandScopeDevice  , /* vkGetImageViewOpaqueCaptureDescriptorDataEXT */
    /*  581 */ CommandScopeDevice  , /* vkGetSamplerOpaqueCaptureDescriptorDataEXT */
    /*  582 */ CommandScopeDevice  , /* vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT */
    /*  583 */ CommandScopeDevice  , /* vkCmdSetFragmentShadingRateEnumNV */
    /*  584 */ CommandScopeDevice  , /* vkCmdDrawMeshTasksEXT */
    /*  585 */ CommandScopeDevice  , /* vkCmdDrawMeshTasksIndirectEXT */
    /*  586 */ CommandScopeDevice  , /* vkCmdDrawMeshTasksIndirectCountEXT */
    /*  587 */ CommandScopeDevice  , /* vkCmdCopyBuffer2KHR */
    /*  588 */ CommandScopeDevice  , /* vkCmdCopyImage2KHR */
    /*  589 */ CommandScopeDevice  , /* vkCmdCopyBufferToImage2KHR */
    /*  590 */ CommandScopeDevice  , /* vkCmdCopyImageToBuffer2KHR */
    /*  591 */ CommandScopeDevice  , /* vkCmdBlitImage2KHR */
    /*  592 */ CommandScopeDevice  , /* vkCmdResolveImage2KHR */
    /*  593 */ CommandScopeDevice  , /* vkGetDeviceFaultInfoEXT */
    /*  594 */ CommandScopeInstance, /* vkAcquireWinrtDisplayNV */
    /*  595 */ CommandScopeInstance, /* vkGetWinrtDisplayNV */
    /*  596 */ CommandScopeInstance, /* vkCreateDirectFBSurfaceEXT */
    /*  597 */ CommandScopeInstance, /* vkGetPhysicalDeviceDirectFBPresentationSupportEXT */
    /*  598 */ CommandScopeDevice  , /* vkCmdSetVertexInputEXT */
    /*  599 */ CommandScopeDevice  , /* vkGetMemoryZirconHandleFUCHSIA */
    /*  600 */ CommandScopeDevice  , /* vkGetMemoryZirconHandlePropertiesFUCHSIA */
    /*  601 */ CommandScopeDevice  , /* vkImportSemaphoreZirconHandleFUCHSIA */
    /*  602 */ CommandScopeDevice  , /* vkGetSemaphoreZirconHandleFUCHSIA */
    /*  603 */ CommandScopeDevice  , /* vkCreateBufferCollectionFUCHSIA */
    /*  604 */ CommandScopeDevice  , /* vkSetBufferCollectionImageConstraintsFUCHSIA */
    /*  605 */ CommandScopeDevice  , /* vkSetBufferCollectionBufferConstraintsFUCHSIA */
    /*  606 */ CommandScopeDevice  , /* vkDestroyBufferCollectionFUCHSIA */
    /*  607 */ CommandScopeDevice  , /* vkGetBufferCollectionPropertiesFUCHSIA */
    /*  608 */ CommandScopeDevice  , /* vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI */
    /*  609 */ CommandScopeDevice  , /* vkCmdSubpassShadingHUAWEI */
    /*  610 */ CommandScopeDevice  , /* vkCmdBindInvocationMaskHUAWEI */
    /*  611 */ CommandScopeDevice  , /* vkGetMemoryRemoteAddressNV */
    /*  612 */ CommandScopeDevice  , /* vkGetPipelinePropertiesEXT */
    /*  613 */ CommandScopeDevice  , /* vkCmdSetPatchControlPointsEXT */
    /*  614 */ CommandScopeDevice  , /* vkCmdSetRasterizerDiscardEnableEXT */
    /*  615 */ CommandScopeDevice  , /* vkCmdSetDepthBiasEnableEXT */
    /*  616 */ CommandScopeDevice  , /* vkCmdSetLogicOpEXT */
    /*  617 */ CommandScopeDevice  , /* vkCmdSetPrimitiveRestartEnableEXT */
    /*  618 */ CommandScopeInstance, /* vkCreateScreenSurfaceQNX */
    /*  619 */ CommandScopeInstance, /* vkGetPhysicalDeviceScreenPresentationSupportQNX */
    /*  620 */ CommandScopeDevice  , /* vkCmdSetColorWriteEnableEXT */
    /*  621 */ CommandScopeDevice  , /* vkCmdTraceRaysIndirect2KHR */
    /*  622 */ CommandScopeDevice  , /* vkCmdDrawMultiEXT */
    /*  623 */ CommandScopeDevice  , /* vkCmdDrawMultiIndexedEXT */
    /*  624 */ CommandScopeDevice  , /* vkCreateMicromapEXT */
    /*  625 */ CommandScopeDevice  , /* vkDestroyMicromapEXT */
    /*  626 */ CommandScopeDevice  , /* vkCmdBuildMicromapsEXT */
    /*  627 */ CommandScopeDevice  , /* vkBuildMicromapsEXT */
    /*  628 */ CommandScopeDevice  , /* vkCopyMicromapEXT */
    /*  629 */ CommandScopeDevice  , /* vkCopyMicromapToMemoryEXT */
    /*  630 */ CommandScopeDevice  , /* vkCopyMemoryToMicromapEXT */
    /*  631 */ CommandScopeDevice  , /* vkWriteMicromapsPropertiesEXT */
    /*  632 */ CommandScopeDevice  , /* vkCmdCopyMicromapEXT */
    /*  633 */ CommandScopeDevice  , /* vkCmdCopyMicromapToMemoryEXT */
    /*  634 */ CommandScopeDevice  , /* vkCmdCopyMemoryToMicromapEXT */
    /*  635 */ CommandScopeDevice  , /* vkCmdWriteMicromapsPropertiesEXT */
    /*  636 */ CommandScopeDevice  , /* vkGetDeviceMicromapCompatibilityEXT */
    /*  637 */ CommandScopeDevice  , /* vkGetMicromapBuildSizesEXT */
    /*  638 */ CommandScopeDevice  , /* vkCmdDrawClusterHUAWEI */
    /*  639 */ CommandScopeDevice  , /* vkCmdDrawClusterIndirectHUAWEI */
    /*  640 */ CommandScopeDevice  , /* vkSetDeviceMemoryPriorityEXT */
    /*  641 */ CommandScopeDevice  , /* vkGetDeviceBufferMemoryRequirementsKHR */
    /*  642 */ CommandScopeDevice  , /* vkGetDeviceImageMemoryRequirementsKHR */
    /*  643 */ CommandScopeDevice  , /* vkGetDeviceImageSparseMemoryRequirementsKHR */
    /*  644 */ CommandScopeDevice  , /* vkGetDescriptorSetLayoutHostMappingInfoVALVE */
    /*  645 */ CommandScopeDevice  , /* vkGetDescriptorSetHostMappingVALVE */
    /*  646 */ CommandScopeDevice  , /* vkCmdCopyMemoryIndirectNV */
    /*  647 */ CommandScopeDevice  , /* vkCmdCopyMemoryToImageIndirectNV */
    /*  648 */ CommandScopeDevice  , /* vkCmdDecompressMemoryNV */
    /*  649 */ CommandScopeDevice  , /* vkCmdDecompressMemoryIndirectCountNV */
    /*  650 */ CommandScopeDevice  , /* vkGetPipelineIndirectMemoryRequirementsNV */
    /*  651 */ CommandScopeDevice  , /* vkCmdUpdatePipelineIndirectBufferNV */
    /*  652 */ CommandScopeDevice  , /* vkGetPipelineIndirectDeviceAddressNV */
    /*  653 */ CommandScopeDevice  , /* vkGetNativeBufferPropertiesOHOS */
    /*  654 */ CommandScopeDevice  , /* vkGetMemoryNativeBufferOHOS */
    /*  655 */ CommandScopeDevice  , /* vkCmdSetDepthClampEnableEXT */
    /*  656 */ CommandScopeDevice  , /* vkCmdSetPolygonModeEXT */
    /*  657 */ CommandScopeDevice  , /* vkCmdSetRasterizationSamplesEXT */
    /*  658 */ CommandScopeDevice  , /* vkCmdSetSampleMaskEXT */
    /*  659 */ CommandScopeDevice  , /* vkCmdSetAlphaToCoverageEnableEXT */
    /*  660 */ CommandScopeDevice  , /* vkCmdSetAlphaToOneEnableEXT */
    /*  661 */ CommandScopeDevice  , /* vkCmdSetLogicOpEnableEXT */
    /*  662 */ CommandScopeDevice  , /* vkCmdSetColorBlendEnableEXT */
    /*  663 */ CommandScopeDevice  , /* vkCmdSetColorBlendEquationEXT */
    /*  664 */ CommandScopeDevice  , /* vkCmdSetColorWriteMaskEXT */
    /*  665 */ CommandScopeDevice  , /* vkCmdSetTessellationDomainOriginEXT */
    /*  666 */ CommandScopeDevice  , /* vkCmdSetRasterizationStreamEXT */
    /*  667 */ CommandScopeDevice  , /* vkCmdSetConservativeRasterizationModeEXT */
    /*  668 */ CommandScopeDevice  , /* vkCmdSetExtraPrimitiveOverestimationSizeEXT */
    /*  669 */ CommandScopeDevice  , /* vkCmdSetDepthClipEnableEXT */
    /*  670 */ CommandScopeDevice  , /* vkCmdSetSampleLocationsEnableEXT */
    /*  671 */ CommandScopeDevice  , /* vkCmdSetColorBlendAdvancedEXT */
    /*  672 */ CommandScopeDevice  , /* vkCmdSetProvokingVertexModeEXT */
    /*  673 */ CommandScopeDevice  , /* vkCmdSetLineRasterizationModeEXT */
    /*  674 */ CommandScopeDevice  , /* vkCmdSetLineStippleEnableEXT */
    /*  675 */ CommandScopeDevice  , /* vkCmdSetDepthClipNegativeOneToOneEXT */
    /*  676 */ CommandScopeDevice  , /* vkCmdSetViewportWScalingEnableNV */
    /*  677 */ CommandScopeDevice  , /* vkCmdSetViewportSwizzleNV */
    /*  678 */ CommandScopeDevice  , /* vkCmdSetCoverageToColorEnableNV */
    /*  679 */ CommandScopeDevice  , /* vkCmdSetCoverageToColorLocationNV */
    /*  680 */ CommandScopeDevice  , /* vkCmdSetCoverageModulationModeNV */
    /*  681 */ CommandScopeDevice  , /* vkCmdSetCoverageModulationTableEnableNV */
    /*  682 */ CommandScopeDevice  , /* vkCmdSetCoverageModulationTableNV */
    /*  683 */ CommandScopeDevice  , /* vkCmdSetShadingRateImageEnableNV */
    /*  684 */ CommandScopeDevice  , /* vkCmdSetRepresentativeFragmentTestEnableNV */
    /*  685 */ CommandScopeDevice  , /* vkCmdSetCoverageReductionModeNV */
    /*  686 */ CommandScopeDevice  , /* vkCreateTensorARM */
    /*  687 */ CommandScopeDevice  , /* vkDestroyTensorARM */
    /*  688 */ CommandScopeDevice  , /* vkCreateTensorViewARM */
    /*  689 */ CommandScopeDevice  , /* vkDestroyTensorViewARM */
    /*  690 */ CommandScopeDevice  , /* vkGetTensorMemoryRequirementsARM */
    /*  691 */ CommandScopeDevice  , /* vkBindTensorMemoryARM */
    /*  692 */ CommandScopeDevice  , /* vkGetDeviceTensorMemoryRequirementsARM */
    /*  693 */ CommandScopeDevice  , /* vkCmdCopyTensorARM */
    /*  694 */ CommandScopeInstance, /* vkGetPhysicalDeviceExternalTensorPropertiesARM */
    /*  695 */ CommandScopeDevice  , /* vkGetTensorOpaqueCaptureDescriptorDataARM */
    /*  696 */ CommandScopeDevice  , /* vkGetTensorViewOpaqueCaptureDescriptorDataARM */
    /*  697 */ CommandScopeDevice  , /* vkGetShaderModuleIdentifierEXT */
    /*  698 */ CommandScopeDevice  , /* vkGetShaderModuleCreateInfoIdentifierEXT */
    /*  699 */ CommandScopeInstance, /* vkGetPhysicalDeviceOpticalFlowImageFormatsNV */
    /*  700 */ CommandScopeDevice  , /* vkCreateOpticalFlowSessionNV */
    /*  701 */ CommandScopeDevice  , /* vkDestroyOpticalFlowSessionNV */
    /*  702 */ CommandScopeDevice  , /* vkBindOpticalFlowSessionImageNV */
    /*  703 */ CommandScopeDevice  , /* vkCmdOpticalFlowExecuteNV */
    /*  704 */ CommandScopeDevice  , /* vkCmdBindIndexBuffer2KHR */
    /*  705 */ CommandScopeDevice  , /* vkGetRenderingAreaGranularityKHR */
    /*  706 */ CommandScopeDevice  , /* vkGetDeviceImageSubresourceLayoutKHR */
    /*  707 */ CommandScopeDevice  , /* vkGetImageSubresourceLayout2KHR */
    /*  708 */ CommandScopeDevice  , /* vkAntiLagUpdateAMD */
    /*  709 */ CommandScopeDevice  , /* vkWaitForPresent2KHR */
    /*  710 */ CommandScopeDevice  , /* vkCreateShadersEXT */
    /*  711 */ CommandScopeDevice  , /* vkDestroyShaderEXT */
    /*  712 */ CommandScopeDevice  , /* vkGetShaderBinaryDataEXT */
    /*  713 */ CommandScopeDevice  , /* vkCmdBindShadersEXT */
    /*  714 */ CommandScopeDevice  , /* vkCmdSetDepthClampRangeEXT */
    /*  715 */ CommandScopeDevice  , /* vkCreatePipelineBinariesKHR */
    /*  716 */ CommandScopeDevice  , /* vkDestroyPipelineBinaryKHR */
    /*  717 */ CommandScopeDevice  , /* vkGetPipelineKeyKHR */
    /*  718 */ CommandScopeDevice  , /* vkGetPipelineBinaryDataKHR */
    /*  719 */ CommandScopeDevice  , /* vkReleaseCapturedPipelineDataKHR */
    /*  720 */ CommandScopeDevice  , /* vkGetFramebufferTilePropertiesQCOM */
    /*  721 */ CommandScopeDevice  , /* vkGetDynamicRenderingTilePropertiesQCOM */
    /*  722 */ CommandScopeDevice  , /* vkReleaseSwapchainImagesKHR */
    /*  723 */ CommandScopeInstance, /* vkGetPhysicalDeviceCooperativeVectorPropertiesNV */
    /*  724 */ CommandScopeDevice  , /* vkConvertCooperativeVectorMatrixNV */
    /*  725 */ CommandScopeDevice  , /* vkCmdConvertCooperativeVectorMatrixNV */
    /*  726 */ CommandScopeDevice  , /* vkSetLatencySleepModeNV */
    /*  727 */ CommandScopeDevice  , /* vkLatencySleepNV */
    /*  728 */ CommandScopeDevice  , /* vkSetLatencyMarkerNV */
    /*  729 */ CommandScopeDevice  , /* vkGetLatencyTimingsNV */
    /*  730 */ CommandScopeDevice  , /* vkQueueNotifyOutOfBandNV */
    /*  731 */ CommandScopeInstance, /* vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR */
    /*  732 */ CommandScopeDevice  , /* vkCreateDataGraphPipelinesARM */
    /*  733 */ CommandScopeDevice  , /* vkCreateDataGraphPipelineSessionARM */
    /*  734 */ CommandScopeDevice  , /* vkGetDataGraphPipelineSessionBindPointRequirementsARM */
    /*  735 */ CommandScopeDevice  , /* vkGetDataGraphPipelineSessionMemoryRequirementsARM */
    /*  736 */ CommandScopeDevice  , /* vkBindDataGraphPipelineSessionMemoryARM */
    /*  737 */ CommandScopeDevice  , /* vkDestroyDataGraphPipelineSessionARM */
    /*  738 */ CommandScopeDevice  , /* vkCmdDispatchDataGraphARM */
    /*  739 */ CommandScopeDevice  , /* vkGetDataGraphPipelineAvailablePropertiesARM */
    /*  740 */ CommandScopeDevice  , /* vkGetDataGraphPipelinePropertiesARM */
    /*  741 */ CommandScopeInstance, /* vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM */
    /*  742 */ CommandScopeInstance, /* vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM */
    /*  743 */ CommandScopeDevice  , /* vkCmdSetAttachmentFeedbackLoopEnableEXT */
    /*  744 */ CommandScopeDevice  , /* vkGetScreenBufferPropertiesQNX */
    /*  745 */ CommandScopeDevice  , /* vkCmdSetLineStippleKHR */
    /*  746 */ CommandScopeInstance, /* vkGetPhysicalDeviceCalibrateableTimeDomainsKHR */
    /*  747 */ CommandScopeDevice  , /* vkGetCalibratedTimestampsKHR */
    /*  748 */ CommandScopeDevice  , /* vkCmdBindDescriptorSets2KHR */
    /*  749 */ CommandScopeDevice  , /* vkCmdPushConstants2KHR */
    /*  750 */ CommandScopeDevice  , /* vkCmdPushDescriptorSet2KHR */
    /*  751 */ CommandScopeDevice  , /* vkCmdPushDescriptorSetWithTemplate2KHR */
    /*  752 */ CommandScopeDevice  , /* vkCmdSetDescriptorBufferOffsets2EXT */
    /*  753 */ CommandScopeDevice  , /* vkCmdBindDescriptorBufferEmbeddedSamplers2EXT */
    /*  754 */ CommandScopeDevice  , /* vkCmdBindTileMemoryQCOM */
    /*  755 */ CommandScopeDevice  , /* vkCmdCopyMemoryIndirectKHR */
    /*  756 */ CommandScopeDevice  , /* vkCmdCopyMemoryToImageIndirectKHR */
    /*  757 */ CommandScopeDevice  , /* vkCmdDecompressMemoryEXT */
    /*  758 */ CommandScopeDevice  , /* vkCmdDecompressMemoryIndirectCountEXT */
    /*  759 */ CommandScopeDevice  , /* vkCreateExternalComputeQueueNV */
    /*  760 */ CommandScopeDevice  , /* vkDestroyExternalComputeQueueNV */
    /*  761 */ CommandScopeInstance, /* vkGetExternalComputeQueueDataNV */
    /*  762 */ CommandScopeDevice  , /* vkGetClusterAccelerationStructureBuildSizesNV */
    /*  763 */ CommandScopeDevice  , /* vkCmdBuildClusterAccelerationStructureIndirectNV */
    /*  764 */ CommandScopeDevice  , /* vkGetPartitionedAccelerationStructuresBuildSizesNV */
    /*  765 */ CommandScopeDevice  , /* vkCmdBuildPartitionedAccelerationStructuresNV */
    /*  766 */ CommandScopeDevice  , /* vkGetGeneratedCommandsMemoryRequirementsEXT */
    /*  767 */ CommandScopeDevice  , /* vkCmdPreprocessGeneratedCommandsEXT */
    /*  768 */ CommandScopeDevice  , /* vkCmdExecuteGeneratedCommandsEXT */
    /*  769 */ CommandScopeDevice  , /* vkCreateIndirectCommandsLayoutEXT */
    /*  770 */ CommandScopeDevice  , /* vkDestroyIndirectCommandsLayoutEXT */
    /*  771 */ CommandScopeDevice  , /* vkCreateIndirectExecutionSetEXT */
    /*  772 */ CommandScopeDevice  , /* vkDestroyIndirectExecutionSetEXT */
    /*  773 */ CommandScopeDevice  , /* vkUpdateIndirectExecutionSetPipelineEXT */
    /*  774 */ CommandScopeDevice  , /* vkUpdateIndirectExecutionSetShaderEXT */
    /*  775 */ CommandScopeInstance, /* vkCreateSurfaceOHOS */
    /*  776 */ CommandScopeInstance, /* vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV */
    /*  777 */ CommandScopeDevice  , /* vkGetMemoryMetalHandleEXT */
    /*  778 */ CommandScopeDevice  , /* vkGetMemoryMetalHandlePropertiesEXT */
    /*  779 */ CommandScopeInstance, /* vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM */
    /*  780 */ CommandScopeInstance, /* vkEnumeratePhysicalDeviceShaderInstrumentationMetricsARM */
    /*  781 */ CommandScopeDevice  , /* vkCreateShaderInstrumentationARM */
    /*  782 */ CommandScopeDevice  , /* vkDestroyShaderInstrumentationARM */
    /*  783 */ CommandScopeDevice  , /* vkCmdBeginShaderInstrumentationARM */
    /*  784 */ CommandScopeDevice  , /* vkCmdEndShaderInstrumentationARM */
    /*  785 */ CommandScopeDevice  , /* vkGetShaderInstrumentationValuesARM */
    /*  786 */ CommandScopeDevice  , /* vkClearShaderInstrumentationMetricsARM */
    /*  787 */ CommandScopeDevice  , /* vkCmdEndRendering2EXT */
    /*  788 */ CommandScopeDevice  , /* vkCmdBeginCustomResolveEXT */
    /*  789 */ CommandScopeDevice  , /* vkCmdEndRendering2KHR */
    /*  790 */ CommandScopeDevice  , /* vkCmdSetComputeOccupancyPriorityNV */
    /*  791 */ CommandScopeInstance, /* vkCreateUbmSurfaceSEC */
    /*  792 */ CommandScopeInstance, /* vkGetPhysicalDeviceUbmPresentationSupportSEC */
};

static const GladPfnRange_t GLAD_Vulkan_feature_pfn_ranges[] = {
    {    0,    0,  137 }, /* VK_VERSION_1_0 */
    {    1,  137,   28 }, /* VK_VERSION_1_1 */
    {    2,  165,   13 }, /* VK_VERSION_1_2 */
    {    3,  178,   37 }, /* VK_VERSION_1_3 */
    {    4,  215,   19 }, /* VK_VERSION_1_4 */
};

static const GladPfnRange_t GLAD_vulkan_ext_pfn_ranges[] = {
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    {    1,  389,    7 }, /* VK_AMDX_shader_enqueue */
#endif
    {    2,  708,    1 }, /* VK_AMD_anti_lag */
    {    3,  462,    2 }, /* VK_AMD_buffer_marker */
    {    5,  490,    1 }, /* VK_AMD_display_native_hdr */
    {    6,  301,    2 }, /* VK_AMD_draw_indirect_count */
    {   22,  303,    1 }, /* VK_AMD_shader_info */
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    {   26,  387,    2 }, /* VK_ANDROID_external_memory_android_hardware_buffer */
#endif
    {   27,  732,   11 }, /* VK_ARM_data_graph */
    {   29,  779,    1 }, /* VK_ARM_performance_counters_by_region */
    {   36,  780,    7 }, /* VK_ARM_shader_instrumentation */
    {   37,  686,   11 }, /* VK_ARM_tensors */
    {   39,  547,    2 }, /* VK_EXT_acquire_drm_display */
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    {   40,  341,    2 }, /* VK_EXT_acquire_xlib_display */
#endif
    {   42,  743,    1 }, /* VK_EXT_attachment_feedback_loop_dynamic_state */
    {   46,  497,    1 }, /* VK_EXT_buffer_device_address */
    {   47,  464,    2 }, /* VK_EXT_calibrated_timestamps */
    {   48,  620,    1 }, /* VK_EXT_color_write_enable */
    {   49,  334,    2 }, /* VK_EXT_conditional_rendering */
    {   52,  788,    1 }, /* VK_EXT_custom_resolve */
    {   53,  268,    5 }, /* VK_EXT_debug_marker */
    {   54,  265,    3 }, /* VK_EXT_debug_report */
    {   55,  376,   11 }, /* VK_EXT_debug_utils */
    {   56,  546,    1 }, /* VK_EXT_depth_bias_control */
    {   57,  714,    1 }, /* VK_EXT_depth_clamp_control */
    {   62,  572,   11 }, /* VK_EXT_descriptor_buffer */
    {   63,  396,   10 }, /* VK_EXT_descriptor_heap */
    {   66,  593,    1 }, /* VK_EXT_device_fault */
    {   67,  766,    9 }, /* VK_EXT_device_generated_commands */
    {   69,  340,    1 }, /* VK_EXT_direct_mode_display */
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    {   70,  596,    2 }, /* VK_EXT_directfb_surface */
#endif
    {   71,  350,    3 }, /* VK_EXT_discard_rectangles */
    {   72,  344,    4 }, /* VK_EXT_display_control */
    {   73,  343,    1 }, /* VK_EXT_display_surface_counter */
    {   75,  512,   12 }, /* VK_EXT_extended_dynamic_state */
    {   76,  613,    5 }, /* VK_EXT_extended_dynamic_state2 */
    {   77,  655,   31 }, /* VK_EXT_extended_dynamic_state3 */
    {   80,  461,    1 }, /* VK_EXT_external_memory_host */
#if defined(VK_USE_PLATFORM_METAL_EXT)
    {   81,  777,    2 }, /* VK_EXT_external_memory_metal */
#endif
    {   85,  787,    1 }, /* VK_EXT_fragment_density_map_offset */
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    {   88,  502,    4 }, /* VK_EXT_full_screen_exclusive */
#endif
    {   92,  353,    1 }, /* VK_EXT_hdr_metadata */
    {   93,  506,    1 }, /* VK_EXT_headless_surface */
    {   94,  532,    5 }, /* VK_EXT_host_image_copy */
    {   95,  511,    1 }, /* VK_EXT_host_query_reset */
    {   97,  536,    1 }, /* VK_EXT_image_compression_control */
    {   99,  438,    1 }, /* VK_EXT_image_drm_format_modifier */
    {  108,  510,    1 }, /* VK_EXT_line_rasterization */
    {  112,  757,    2 }, /* VK_EXT_memory_decompression */
    {  114,  584,    3 }, /* VK_EXT_mesh_shader */
#if defined(VK_USE_PLATFORM_METAL_EXT)
    {  115,  565,    1 }, /* VK_EXT_metal_objects */
#endif
#if defined(VK_USE_PLATFORM_METAL_EXT)
    {  116,  492,    1 }, /* VK_EXT_metal_surface */
#endif
    {  117,  622,    2 }, /* VK_EXT_multi_draw */
    {  122,  624,   14 }, /* VK_EXT_opacity_micromap */
    {  123,  640,    1 }, /* VK_EXT_pageable_device_local_memory */
    {  129,  612,    1 }, /* VK_EXT_pipeline_properties */
    {  134,  477,    4 }, /* VK_EXT_present_timing */
    {  137,  549,    4 }, /* VK_EXT_private_data */
    {  144,  406,    2 }, /* VK_EXT_sample_locations */
    {  155,  697,    2 }, /* VK_EXT_shader_module_identifier */
    {  156,  512,   12 }, /* VK_EXT_shader_object */
    {  156,  598,    1 }, /* VK_EXT_shader_object */
    {  156,  613,    5 }, /* VK_EXT_shader_object */
    {  156,  655,   31 }, /* VK_EXT_shader_object */
    {  156,  710,    5 }, /* VK_EXT_shader_object */
    {  169,  539,    1 }, /* VK_EXT_swapchain_maintenance1 */
    {  173,  498,    1 }, /* VK_EXT_tooling_info */
    {  174,  286,    6 }, /* VK_EXT_transform_feedback */
    {  175,  439,    4 }, /* VK_EXT_validation_cache */
    {  180,  598,    1 }, /* VK_EXT_vertex_input_dynamic_state */
#if defined(VK_USE_PLATFORM_FUCHSIA)
    {  184,  603,    5 }, /* VK_FUCHSIA_buffer_collection */
#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
    {  185,  599,    2 }, /* VK_FUCHSIA_external_memory */
#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
    {  186,  601,    2 }, /* VK_FUCHSIA_external_semaphore */
#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
    {  187,  491,    1 }, /* VK_FUCHSIA_imagepipe_surface */
#endif
#if defined(VK_USE_PLATFORM_GGP)
    {  189,  306,    1 }, /* VK_GGP_stream_descriptor_surface */
#endif
    {  191,  348,    2 }, /* VK_GOOGLE_display_timing */
    {  195,  638,    2 }, /* VK_HUAWEI_cluster_culling_shader */
    {  197,  610,    1 }, /* VK_HUAWEI_invocation_mask */
    {  198,  608,    2 }, /* VK_HUAWEI_subpass_shading */
    {  202,  481,    9 }, /* VK_INTEL_performance_query */
    {  206,  411,   16 }, /* VK_KHR_acceleration_structure */
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    {  207,  262,    1 }, /* VK_KHR_android_surface */
#endif
    {  208,  436,    2 }, /* VK_KHR_bind_memory2 */
    {  209,  507,    3 }, /* VK_KHR_buffer_device_address */
    {  210,  746,    2 }, /* VK_KHR_calibrated_timestamps */
    {  212,  731,    1 }, /* VK_KHR_cooperative_matrix */
    {  213,  587,    6 }, /* VK_KHR_copy_commands2 */
    {  214,  755,    2 }, /* VK_KHR_copy_memory_indirect */
    {  215,  354,    4 }, /* VK_KHR_create_renderpass2 */
    {  217,  524,    5 }, /* VK_KHR_deferred_host_operations */
    {  220,  333,    1 }, /* VK_KHR_descriptor_update_template */
    {  220,  336,    3 }, /* VK_KHR_descriptor_update_template */
    {  221,  244,    4 }, /* VK_KHR_device_group */
    {  221,  316,    3 }, /* VK_KHR_device_group */
    {  222,  321,    1 }, /* VK_KHR_device_group_creation */
    {  223,  248,    7 }, /* VK_KHR_display */
    {  224,  255,    1 }, /* VK_KHR_display_swapchain */
    {  225,  459,    2 }, /* VK_KHR_draw_indirect_count */
    {  227,  304,    2 }, /* VK_KHR_dynamic_rendering */
    {  228,  495,    2 }, /* VK_KHR_dynamic_rendering_local_read */
    {  230,  359,    1 }, /* VK_KHR_external_fence_capabilities */
    {  231,  362,    2 }, /* VK_KHR_external_fence_fd */
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    {  232,  360,    2 }, /* VK_KHR_external_fence_win32 */
#endif
    {  234,  322,    1 }, /* VK_KHR_external_memory_capabilities */
    {  235,  325,    2 }, /* VK_KHR_external_memory_fd */
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    {  236,  323,    2 }, /* VK_KHR_external_memory_win32 */
#endif
    {  238,  327,    1 }, /* VK_KHR_external_semaphore_capabilities */
    {  239,  330,    2 }, /* VK_KHR_external_semaphore_fd */
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    {  240,  328,    2 }, /* VK_KHR_external_semaphore_win32 */
#endif
    {  243,  493,    2 }, /* VK_KHR_fragment_shading_rate */
    {  244,  370,    4 }, /* VK_KHR_get_display_properties2 */
    {  245,  408,    3 }, /* VK_KHR_get_memory_requirements2 */
    {  246,  309,    7 }, /* VK_KHR_get_physical_device_properties2 */
    {  247,  368,    2 }, /* VK_KHR_get_surface_capabilities2 */
    {  254,  745,    1 }, /* VK_KHR_line_rasterization */
    {  256,  320,    1 }, /* VK_KHR_maintenance1 */
    {  257,  789,    1 }, /* VK_KHR_maintenance10 */
    {  259,  458,    1 }, /* VK_KHR_maintenance3 */
    {  260,  641,    3 }, /* VK_KHR_maintenance4 */
    {  261,  704,    4 }, /* VK_KHR_maintenance5 */
    {  262,  748,    6 }, /* VK_KHR_maintenance6 */
    {  266,  537,    2 }, /* VK_KHR_map_memory2 */
    {  268,  364,    4 }, /* VK_KHR_performance_query */
    {  269,  715,    5 }, /* VK_KHR_pipeline_binary */
    {  270,  529,    3 }, /* VK_KHR_pipeline_executable_properties */
    {  277,  499,    1 }, /* VK_KHR_present_wait */
    {  278,  709,    1 }, /* VK_KHR_present_wait2 */
    {  279,  332,    2 }, /* VK_KHR_push_descriptor */
    {  281,  621,    1 }, /* VK_KHR_ray_tracing_maintenance1 */
    {  282,  427,    7 }, /* VK_KHR_ray_tracing_pipeline */
    {  287,  434,    2 }, /* VK_KHR_sampler_ycbcr_conversion */
    {  308,  358,    1 }, /* VK_KHR_shared_presentable_image */
    {  311,  234,    5 }, /* VK_KHR_surface */
    {  314,  239,    9 }, /* VK_KHR_swapchain */
    {  315,  722,    1 }, /* VK_KHR_swapchain_maintenance1 */
    {  317,  566,    6 }, /* VK_KHR_synchronization2 */
    {  318,  474,    3 }, /* VK_KHR_timeline_semaphore */
    {  326,  285,    1 }, /* VK_KHR_video_decode_queue */
    {  333,  553,    3 }, /* VK_KHR_video_encode_queue */
    {  336,  273,   12 }, /* VK_KHR_video_queue */
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    {  338,  260,    2 }, /* VK_KHR_wayland_surface */
#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    {  340,  263,    2 }, /* VK_KHR_win32_surface */
#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
    {  342,  258,    2 }, /* VK_KHR_xcb_surface */
#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    {  343,  256,    2 }, /* VK_KHR_xlib_surface */
#endif
#if defined(VK_USE_PLATFORM_IOS_MVK)
    {  348,  374,    1 }, /* VK_MVK_ios_surface */
#endif
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    {  349,  375,    1 }, /* VK_MVK_macos_surface */
#endif
#if defined(VK_USE_PLATFORM_VI_NN)
    {  350,  319,    1 }, /* VK_NN_vi_surface */
#endif
    {  351,  292,    5 }, /* VK_NVX_binary_import */
    {  352,  297,    4 }, /* VK_NVX_image_view_handle */
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    {  354,  594,    2 }, /* VK_NV_acquire_winrt_display */
#endif
    {  355,  339,    1 }, /* VK_NV_clip_space_w_scaling */
    {  356,  762,    2 }, /* VK_NV_cluster_acceleration_structure */
    {  358,  790,    1 }, /* VK_NV_compute_occupancy_priority */
    {  360,  500,    1 }, /* VK_NV_cooperative_matrix */
    {  361,  776,    1 }, /* VK_NV_cooperative_matrix2 */
    {  362,  723,    3 }, /* VK_NV_cooperative_vector */
    {  363,  646,    2 }, /* VK_NV_copy_memory_indirect */
    {  365,  501,    1 }, /* VK_NV_coverage_reduction_mode */
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    {  366,  556,    6 }, /* VK_NV_cuda_kernel_launch */
#endif
    {  370,  471,    3 }, /* VK_NV_device_diagnostic_checkpoints */
    {  372,  540,    6 }, /* VK_NV_device_generated_commands */
    {  373,  650,    3 }, /* VK_NV_device_generated_commands_compute */
    {  377,  759,    3 }, /* VK_NV_external_compute_queue */
    {  379,  307,    1 }, /* VK_NV_external_memory_capabilities */
    {  380,  611,    1 }, /* VK_NV_external_memory_rdma */
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    {  381,  308,    1 }, /* VK_NV_external_memory_win32 */
#endif
    {  385,  583,    1 }, /* VK_NV_fragment_shading_rate_enums */
    {  392,  726,    5 }, /* VK_NV_low_latency2 */
    {  393,  648,    2 }, /* VK_NV_memory_decompression */
    {  394,  466,    3 }, /* VK_NV_mesh_shader */
    {  395,  699,    5 }, /* VK_NV_optical_flow */
    {  396,  764,    2 }, /* VK_NV_partitioned_acceleration_structure */
    {  402,  446,   12 }, /* VK_NV_ray_tracing */
    {  409,  469,    2 }, /* VK_NV_scissor_exclusive */
    {  414,  443,    3 }, /* VK_NV_shading_rate_image */
#if defined(VK_USE_PLATFORM_OHOS)
    {  418,  653,    2 }, /* VK_OHOS_external_memory */
#endif
#if defined(VK_USE_PLATFORM_OHOS)
    {  419,  775,    1 }, /* VK_OHOS_surface */
#endif
    {  433,  754,    1 }, /* VK_QCOM_tile_memory_heap */
    {  434,  720,    2 }, /* VK_QCOM_tile_properties */
    {  435,  562,    3 }, /* VK_QCOM_tile_shading */
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    {  437,  744,    1 }, /* VK_QNX_external_memory_screen_buffer */
#endif
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    {  438,  618,    2 }, /* VK_QNX_screen_surface */
#endif
#if defined(VK_USE_PLATFORM_UBM_SEC)
    {  441,  791,    2 }, /* VK_SEC_ubm_surface */
#endif
    {  442,  644,    2 }, /* VK_VALVE_descriptor_set_host_mapping */
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
    /*   29 */ 0x27679fcdc1ce1fb1ULL, /* VK_ARM_performance_counters_by_region */
    /*   30 */ 0x0f753497d22c514bULL, /* VK_ARM_pipeline_opacity_micromap */
    /*   31 */ 0x0afcd59fd2af6286ULL, /* VK_ARM_rasterization_order_attachment_access */
    /*   32 */ 0x099508890a72c586ULL, /* VK_ARM_render_pass_striped */
    /*   33 */ 0xcb5ebd8b3c00874cULL, /* VK_ARM_scheduling_controls */
    /*   34 */ 0x6d66a5a00c62648dULL, /* VK_ARM_shader_core_builtins */
    /*   35 */ 0x42f58e0f0c034d62ULL, /* VK_ARM_shader_core_properties */
    /*   36 */ 0x37e4a31f9038d98eULL, /* VK_ARM_shader_instrumentation */
    /*   37 */ 0xdda32da4e6cb55beULL, /* VK_ARM_tensors */
    /*   38 */ 0x9452c6992583027bULL, /* VK_EXT_4444_formats */
    /*   39 */ 0xc78e4b8ee4076491ULL, /* VK_EXT_acquire_drm_display */
    /*   40 */ 0xf320bc0da89095ccULL, /* VK_EXT_acquire_xlib_display */
    /*   41 */ 0x1f2679f2f103d431ULL, /* VK_EXT_astc_decode_mode */
    /*   42 */ 0xf27c39b3a1b079adULL, /* VK_EXT_attachment_feedback_loop_dynamic_state */
    /*   43 */ 0x74d9e22c0880d05bULL, /* VK_EXT_attachment_feedback_loop_layout */
    /*   44 */ 0xbf40b1c2e2a175caULL, /* VK_EXT_blend_operation_advanced */
    /*   45 */ 0xa7ae01d75b03a5faULL, /* VK_EXT_border_color_swizzle */
    /*   46 */ 0x8cadd6ee8baeb7b6ULL, /* VK_EXT_buffer_device_address */
    /*   47 */ 0xe53030d618c508b9ULL, /* VK_EXT_calibrated_timestamps */
    /*   48 */ 0x1821c534e43e8bc2ULL, /* VK_EXT_color_write_enable */
    /*   49 */ 0x3acaa19dcdfa4838ULL, /* VK_EXT_conditional_rendering */
    /*   50 */ 0xbc479489c58aba55ULL, /* VK_EXT_conservative_rasterization */
    /*   51 */ 0xd41fdd03d1591c42ULL, /* VK_EXT_custom_border_color */
    /*   52 */ 0xc3a47238c6108e78ULL, /* VK_EXT_custom_resolve */
    /*   53 */ 0x13dd727d73e5c438ULL, /* VK_EXT_debug_marker */
    /*   54 */ 0xefc5d6f86f5274aaULL, /* VK_EXT_debug_report */
    /*   55 */ 0x1f4cc1384fdd3124ULL, /* VK_EXT_debug_utils */
    /*   56 */ 0x4334a6b5b2a8bcdfULL, /* VK_EXT_depth_bias_control */
    /*   57 */ 0x20b2ee75c46fae3bULL, /* VK_EXT_depth_clamp_control */
    /*   58 */ 0x42e03d02e07ee602ULL, /* VK_EXT_depth_clamp_zero_one */
    /*   59 */ 0xc46ca287fec7bfa2ULL, /* VK_EXT_depth_clip_control */
    /*   60 */ 0xb225ae836596c941ULL, /* VK_EXT_depth_clip_enable */
    /*   61 */ 0x683e05b7c95cf871ULL, /* VK_EXT_depth_range_unrestricted */
    /*   62 */ 0xff983b309bdf4f8fULL, /* VK_EXT_descriptor_buffer */
    /*   63 */ 0x8db8b73fde833a18ULL, /* VK_EXT_descriptor_heap */
    /*   64 */ 0x8ed9a50d9652d13aULL, /* VK_EXT_descriptor_indexing */
    /*   65 */ 0x71042286279bf266ULL, /* VK_EXT_device_address_binding_report */
    /*   66 */ 0x44712682d623c6ecULL, /* VK_EXT_device_fault */
    /*   67 */ 0x6c42eb1e4c30ed48ULL, /* VK_EXT_device_generated_commands */
    /*   68 */ 0xfc8708a7a55a3b72ULL, /* VK_EXT_device_memory_report */
    /*   69 */ 0x3d21adc07dc92de9ULL, /* VK_EXT_direct_mode_display */
    /*   70 */ 0x2f377620d96a0b95ULL, /* VK_EXT_directfb_surface */
    /*   71 */ 0x6c4b18b294f729e9ULL, /* VK_EXT_discard_rectangles */
    /*   72 */ 0x2bd79b14ec35b405ULL, /* VK_EXT_display_control */
    /*   73 */ 0xf82da0558a082445ULL, /* VK_EXT_display_surface_counter */
    /*   74 */ 0x6c84fccd28668412ULL, /* VK_EXT_dynamic_rendering_unused_attachments */
    /*   75 */ 0x405b3a7704a014a0ULL, /* VK_EXT_extended_dynamic_state */
    /*   76 */ 0x09050069bac4e50bULL, /* VK_EXT_extended_dynamic_state2 */
    /*   77 */ 0x3e6696389e531962ULL, /* VK_EXT_extended_dynamic_state3 */
    /*   78 */ 0x204d4d8537dc240cULL, /* VK_EXT_external_memory_acquire_unmodified */
    /*   79 */ 0xfbe83be92d0dc3e1ULL, /* VK_EXT_external_memory_dma_buf */
    /*   80 */ 0xe730e90349447245ULL, /* VK_EXT_external_memory_host */
    /*   81 */ 0xbb6a5bdb9f4339b2ULL, /* VK_EXT_external_memory_metal */
    /*   82 */ 0x2ff4c771bf02a660ULL, /* VK_EXT_filter_cubic */
    /*   83 */ 0xdd63dbab93498a89ULL, /* VK_EXT_fragment_density_map */
    /*   84 */ 0x639aaec72634d6ccULL, /* VK_EXT_fragment_density_map2 */
    /*   85 */ 0x50ea79c84acba293ULL, /* VK_EXT_fragment_density_map_offset */
    /*   86 */ 0xec38db4912e9aa39ULL, /* VK_EXT_fragment_shader_interlock */
    /*   87 */ 0x4bed293561f471c5ULL, /* VK_EXT_frame_boundary */
    /*   88 */ 0xf888a39f24346db4ULL, /* VK_EXT_full_screen_exclusive */
    /*   89 */ 0x026fba6d706537f5ULL, /* VK_EXT_global_priority */
    /*   90 */ 0x49240b90779ad742ULL, /* VK_EXT_global_priority_query */
    /*   91 */ 0xe612048b33a20737ULL, /* VK_EXT_graphics_pipeline_library */
    /*   92 */ 0xd140703366300180ULL, /* VK_EXT_hdr_metadata */
    /*   93 */ 0xfc97df8c7f5cb62eULL, /* VK_EXT_headless_surface */
    /*   94 */ 0x15c6d3b4db750060ULL, /* VK_EXT_host_image_copy */
    /*   95 */ 0xcc9a1964d5f92eadULL, /* VK_EXT_host_query_reset */
    /*   96 */ 0x992053b93ca7369aULL, /* VK_EXT_image_2d_view_of_3d */
    /*   97 */ 0xac673544b231a330ULL, /* VK_EXT_image_compression_control */
    /*   98 */ 0xfc267e5b08be3c88ULL, /* VK_EXT_image_compression_control_swapchain */
    /*   99 */ 0x5d78e7153c62776cULL, /* VK_EXT_image_drm_format_modifier */
    /*  100 */ 0xe918548d9d09bdf5ULL, /* VK_EXT_image_robustness */
    /*  101 */ 0x10ea5ce8b7b462c6ULL, /* VK_EXT_image_sliced_view_of_3d */
    /*  102 */ 0x5d125c6144d30072ULL, /* VK_EXT_image_view_min_lod */
    /*  103 */ 0x66bb737b7652d71dULL, /* VK_EXT_index_type_uint8 */
    /*  104 */ 0x59f61f1cc23145eeULL, /* VK_EXT_inline_uniform_block */
    /*  105 */ 0x9ba2edc52691fc07ULL, /* VK_EXT_layer_settings */
    /*  106 */ 0xa45ec0ff789f2882ULL, /* VK_EXT_legacy_dithering */
    /*  107 */ 0x93eebd73e097d983ULL, /* VK_EXT_legacy_vertex_attributes */
    /*  108 */ 0x98daf38a4cd796bcULL, /* VK_EXT_line_rasterization */
    /*  109 */ 0xca3cb4186d57fa40ULL, /* VK_EXT_load_store_op_none */
    /*  110 */ 0xc92882ba73a7ad8aULL, /* VK_EXT_map_memory_placed */
    /*  111 */ 0xa642b55c0f467f26ULL, /* VK_EXT_memory_budget */
    /*  112 */ 0x4792efaf1e0441d0ULL, /* VK_EXT_memory_decompression */
    /*  113 */ 0xdf03e1a0a38154d2ULL, /* VK_EXT_memory_priority */
    /*  114 */ 0x38a2a90e0a820189ULL, /* VK_EXT_mesh_shader */
    /*  115 */ 0x6bcff1cd8cf418f2ULL, /* VK_EXT_metal_objects */
    /*  116 */ 0x60fc707b7c19679cULL, /* VK_EXT_metal_surface */
    /*  117 */ 0x60ca462964877ba5ULL, /* VK_EXT_multi_draw */
    /*  118 */ 0x60c608294e99436fULL, /* VK_EXT_multisampled_render_to_single_sampled */
    /*  119 */ 0x333da01be07c65e4ULL, /* VK_EXT_mutable_descriptor_type */
    /*  120 */ 0x4f43f294a30fc75dULL, /* VK_EXT_nested_command_buffer */
    /*  121 */ 0x6cf77b70db09b037ULL, /* VK_EXT_non_seamless_cube_map */
    /*  122 */ 0xb5bdb97dc49555efULL, /* VK_EXT_opacity_micromap */
    /*  123 */ 0x74062e5990db1eebULL, /* VK_EXT_pageable_device_local_memory */
    /*  124 */ 0xe60ea5fa872ffa4bULL, /* VK_EXT_pci_bus_info */
    /*  125 */ 0x087b96c0fac7f2e9ULL, /* VK_EXT_physical_device_drm */
    /*  126 */ 0xae186881e629f533ULL, /* VK_EXT_pipeline_creation_cache_control */
    /*  127 */ 0xd5ed321620183ae4ULL, /* VK_EXT_pipeline_creation_feedback */
    /*  128 */ 0xf2497807f1195d03ULL, /* VK_EXT_pipeline_library_group_handles */
    /*  129 */ 0x97816799b0ea2a08ULL, /* VK_EXT_pipeline_properties */
    /*  130 */ 0x0bec2c70abec6edfULL, /* VK_EXT_pipeline_protected_access */
    /*  131 */ 0x3726d3c286b23305ULL, /* VK_EXT_pipeline_robustness */
    /*  132 */ 0x578e2a9cdc320baaULL, /* VK_EXT_post_depth_coverage */
    /*  133 */ 0xdad3977856dd3ce4ULL, /* VK_EXT_present_mode_fifo_latest_ready */
    /*  134 */ 0x18fd07c7236cc794ULL, /* VK_EXT_present_timing */
    /*  135 */ 0x4792bf3539da07a0ULL, /* VK_EXT_primitive_topology_list_restart */
    /*  136 */ 0x4de3fc9eb140d3c9ULL, /* VK_EXT_primitives_generated_query */
    /*  137 */ 0x66832604ff1fb25aULL, /* VK_EXT_private_data */
    /*  138 */ 0x3632448643e01277ULL, /* VK_EXT_provoking_vertex */
    /*  139 */ 0xc3a80f57bc34acf0ULL, /* VK_EXT_queue_family_foreign */
    /*  140 */ 0x9c47749ad3103e99ULL, /* VK_EXT_rasterization_order_attachment_access */
    /*  141 */ 0xc1e2ee36a5230c6cULL, /* VK_EXT_ray_tracing_invocation_reorder */
    /*  142 */ 0xe3b61ff718cac048ULL, /* VK_EXT_rgba10x6_formats */
    /*  143 */ 0x267337703fbb9802ULL, /* VK_EXT_robustness2 */
    /*  144 */ 0xa2f0c46d62bffbbdULL, /* VK_EXT_sample_locations */
    /*  145 */ 0x35bc8d45855c9dddULL, /* VK_EXT_sampler_filter_minmax */
    /*  146 */ 0x0fe7c2504b67f76eULL, /* VK_EXT_scalar_block_layout */
    /*  147 */ 0x21c315365bdd91c1ULL, /* VK_EXT_separate_stencil_usage */
    /*  148 */ 0x68667a1b3ddc8c10ULL, /* VK_EXT_shader_64bit_indexing */
    /*  149 */ 0x39152af17d406387ULL, /* VK_EXT_shader_atomic_float */
    /*  150 */ 0xfa5bf73b09f1814aULL, /* VK_EXT_shader_atomic_float2 */
    /*  151 */ 0x1313743aff740ea6ULL, /* VK_EXT_shader_demote_to_helper_invocation */
    /*  152 */ 0xf791a964511a9452ULL, /* VK_EXT_shader_float8 */
    /*  153 */ 0xdbd208469e466661ULL, /* VK_EXT_shader_image_atomic_int64 */
    /*  154 */ 0x18cdfe2b616c8e84ULL, /* VK_EXT_shader_long_vector */
    /*  155 */ 0x0fdb11284e798630ULL, /* VK_EXT_shader_module_identifier */
    /*  156 */ 0x01d57626cc2cb88bULL, /* VK_EXT_shader_object */
    /*  157 */ 0xd98565c5e8cff707ULL, /* VK_EXT_shader_replicated_composites */
    /*  158 */ 0x1d5f02c289908dc6ULL, /* VK_EXT_shader_stencil_export */
    /*  159 */ 0x3434e0e3856c3974ULL, /* VK_EXT_shader_subgroup_ballot */
    /*  160 */ 0x526a32ce4d99060fULL, /* VK_EXT_shader_subgroup_partitioned */
    /*  161 */ 0x414fe291cad1b8c2ULL, /* VK_EXT_shader_subgroup_vote */
    /*  162 */ 0x15c81e1e3330c87aULL, /* VK_EXT_shader_tile_image */
    /*  163 */ 0xc91380d922f2bf3bULL, /* VK_EXT_shader_uniform_buffer_unsized_array */
    /*  164 */ 0x3ab7ae29a67149aaULL, /* VK_EXT_shader_viewport_index_layer */
    /*  165 */ 0xf8847bcd6077bcfcULL, /* VK_EXT_subgroup_size_control */
    /*  166 */ 0xc0a98929a3b5a629ULL, /* VK_EXT_subpass_merge_feedback */
    /*  167 */ 0x745c764090230a6aULL, /* VK_EXT_surface_maintenance1 */
    /*  168 */ 0xaf7db52f12522284ULL, /* VK_EXT_swapchain_colorspace */
    /*  169 */ 0xb8a530fd9b6e7826ULL, /* VK_EXT_swapchain_maintenance1 */
    /*  170 */ 0x93820a855076e9baULL, /* VK_EXT_texel_buffer_alignment */
    /*  171 */ 0x0e6243f460b4e447ULL, /* VK_EXT_texture_compression_astc_3d */
    /*  172 */ 0xd54a2906947894c3ULL, /* VK_EXT_texture_compression_astc_hdr */
    /*  173 */ 0xa176a37fe21bf722ULL, /* VK_EXT_tooling_info */
    /*  174 */ 0x2c77e64693cba64bULL, /* VK_EXT_transform_feedback */
    /*  175 */ 0xd43b5b3257938a0cULL, /* VK_EXT_validation_cache */
    /*  176 */ 0x32e3bcc79655ff35ULL, /* VK_EXT_validation_features */
    /*  177 */ 0x5dbef52d8325ef00ULL, /* VK_EXT_validation_flags */
    /*  178 */ 0x41bd31eed71de48dULL, /* VK_EXT_vertex_attribute_divisor */
    /*  179 */ 0x384a29f8cf6d87bfULL, /* VK_EXT_vertex_attribute_robustness */
    /*  180 */ 0xdba593667f2b15d8ULL, /* VK_EXT_vertex_input_dynamic_state */
    /*  181 */ 0xdc68cb4b50c6a206ULL, /* VK_EXT_ycbcr_2plane_444_formats */
    /*  182 */ 0x7f0e4b169ce6683eULL, /* VK_EXT_ycbcr_image_arrays */
    /*  183 */ 0x1d23436dd19b0471ULL, /* VK_EXT_zero_initialize_device_memory */
    /*  184 */ 0x4ad21727cd459ae0ULL, /* VK_FUCHSIA_buffer_collection */
    /*  185 */ 0x39a61a1dde950a7eULL, /* VK_FUCHSIA_external_memory */
    /*  186 */ 0xf64c61e8709735f7ULL, /* VK_FUCHSIA_external_semaphore */
    /*  187 */ 0x78bbdf52d016b408ULL, /* VK_FUCHSIA_imagepipe_surface */
    /*  188 */ 0x7f2da9be6e1b04dbULL, /* VK_GGP_frame_token */
    /*  189 */ 0xcd04d110dd619891ULL, /* VK_GGP_stream_descriptor_surface */
    /*  190 */ 0x66d124637ca67c9bULL, /* VK_GOOGLE_decorate_string */
    /*  191 */ 0xd317975f41d1a234ULL, /* VK_GOOGLE_display_timing */
    /*  192 */ 0x434a8c02c305c9d2ULL, /* VK_GOOGLE_hlsl_functionality1 */
    /*  193 */ 0xdb384c83fb23b324ULL, /* VK_GOOGLE_surfaceless_query */
    /*  194 */ 0x8ea5be2adce92628ULL, /* VK_GOOGLE_user_type */
    /*  195 */ 0x1251619c17f44f75ULL, /* VK_HUAWEI_cluster_culling_shader */
    /*  196 */ 0x734dc9a82ce2a812ULL, /* VK_HUAWEI_hdr_vivid */
    /*  197 */ 0x23cb6d9b631ae3deULL, /* VK_HUAWEI_invocation_mask */
    /*  198 */ 0x7a080c6eb36cfa62ULL, /* VK_HUAWEI_subpass_shading */
    /*  199 */ 0xc831730562583c7fULL, /* VK_IMG_filter_cubic */
    /*  200 */ 0x2770027508eb9598ULL, /* VK_IMG_format_pvrtc */
    /*  201 */ 0xb0257135e659f035ULL, /* VK_IMG_relaxed_line_rasterization */
    /*  202 */ 0xde48a4b9c28f1a76ULL, /* VK_INTEL_performance_query */
    /*  203 */ 0x1cdbef97960a8e84ULL, /* VK_INTEL_shader_integer_functions2 */
    /*  204 */ 0x8febc131b31f03a7ULL, /* VK_KHR_16bit_storage */
    /*  205 */ 0xfc675d0c9be11933ULL, /* VK_KHR_8bit_storage */
    /*  206 */ 0xfd487833d05a912eULL, /* VK_KHR_acceleration_structure */
    /*  207 */ 0x29df4e2582c4e5ebULL, /* VK_KHR_android_surface */
    /*  208 */ 0xc441ac340c33f00eULL, /* VK_KHR_bind_memory2 */
    /*  209 */ 0xed3998734610578eULL, /* VK_KHR_buffer_device_address */
    /*  210 */ 0xf6b15d82867a4cc7ULL, /* VK_KHR_calibrated_timestamps */
    /*  211 */ 0x0afe9b38bfc3ce2cULL, /* VK_KHR_compute_shader_derivatives */
    /*  212 */ 0x2349bf032cef96dfULL, /* VK_KHR_cooperative_matrix */
    /*  213 */ 0x8037af99654ff021ULL, /* VK_KHR_copy_commands2 */
    /*  214 */ 0x45827ba02aefd51cULL, /* VK_KHR_copy_memory_indirect */
    /*  215 */ 0x45e78547df004126ULL, /* VK_KHR_create_renderpass2 */
    /*  216 */ 0x78b51eb267ba222aULL, /* VK_KHR_dedicated_allocation */
    /*  217 */ 0x94de08b35a6241caULL, /* VK_KHR_deferred_host_operations */
    /*  218 */ 0xc379ca87fcbfe646ULL, /* VK_KHR_depth_clamp_zero_one */
    /*  219 */ 0x8c49a14f4e053827ULL, /* VK_KHR_depth_stencil_resolve */
    /*  220 */ 0xd0e490f381b744beULL, /* VK_KHR_descriptor_update_template */
    /*  221 */ 0xc6ca78c5b314bc87ULL, /* VK_KHR_device_group */
    /*  222 */ 0x8585cbd14f1c0cacULL, /* VK_KHR_device_group_creation */
    /*  223 */ 0x2859d74f3639d0b1ULL, /* VK_KHR_display */
    /*  224 */ 0xe6851c4675917263ULL, /* VK_KHR_display_swapchain */
    /*  225 */ 0x0337556153ae8299ULL, /* VK_KHR_draw_indirect_count */
    /*  226 */ 0x2fa1beee71b55c4aULL, /* VK_KHR_driver_properties */
    /*  227 */ 0xcec518255e3db5bdULL, /* VK_KHR_dynamic_rendering */
    /*  228 */ 0x3aff0fddef25484aULL, /* VK_KHR_dynamic_rendering_local_read */
    /*  229 */ 0x042831872b90006cULL, /* VK_KHR_external_fence */
    /*  230 */ 0x5f78dae679457682ULL, /* VK_KHR_external_fence_capabilities */
    /*  231 */ 0xcd3a8c2ddf5addf6ULL, /* VK_KHR_external_fence_fd */
    /*  232 */ 0x4c03e948c552a900ULL, /* VK_KHR_external_fence_win32 */
    /*  233 */ 0x87d94faee5024129ULL, /* VK_KHR_external_memory */
    /*  234 */ 0x3f3f36a8f61bdd88ULL, /* VK_KHR_external_memory_capabilities */
    /*  235 */ 0x552d385fc1022139ULL, /* VK_KHR_external_memory_fd */
    /*  236 */ 0x92cd58bc47a696d9ULL, /* VK_KHR_external_memory_win32 */
    /*  237 */ 0x7e7e947a025884c1ULL, /* VK_KHR_external_semaphore */
    /*  238 */ 0xb7268870e382881bULL, /* VK_KHR_external_semaphore_capabilities */
    /*  239 */ 0x089c9b49df8b6f1eULL, /* VK_KHR_external_semaphore_fd */
    /*  240 */ 0x014c9621dbd33d31ULL, /* VK_KHR_external_semaphore_win32 */
    /*  241 */ 0x9310a82971542c4aULL, /* VK_KHR_format_feature_flags2 */
    /*  242 */ 0x2aedf5bc87e7dd6dULL, /* VK_KHR_fragment_shader_barycentric */
    /*  243 */ 0x8496cee01f4fa6d5ULL, /* VK_KHR_fragment_shading_rate */
    /*  244 */ 0x6c023bc9dc523d46ULL, /* VK_KHR_get_display_properties2 */
    /*  245 */ 0x9eb7bb6c3705f946ULL, /* VK_KHR_get_memory_requirements2 */
    /*  246 */ 0x7685eeed9cac9798ULL, /* VK_KHR_get_physical_device_properties2 */
    /*  247 */ 0x9b0fbb8eeee0e74bULL, /* VK_KHR_get_surface_capabilities2 */
    /*  248 */ 0x0bb91b137617fbefULL, /* VK_KHR_global_priority */
    /*  249 */ 0xfb7c493b280e7035ULL, /* VK_KHR_image_format_list */
    /*  250 */ 0x6ba09c8a87af68ceULL, /* VK_KHR_imageless_framebuffer */
    /*  251 */ 0x76a0d6d17ae91b81ULL, /* VK_KHR_incremental_present */
    /*  252 */ 0x3dde8d8eb0b76315ULL, /* VK_KHR_index_type_uint8 */
    /*  253 */ 0xe7bbe125386c2beaULL, /* VK_KHR_internally_synchronized_queues */
    /*  254 */ 0x7928ca2523362ef3ULL, /* VK_KHR_line_rasterization */
    /*  255 */ 0xc8692b97cfbe45adULL, /* VK_KHR_load_store_op_none */
    /*  256 */ 0xe3c8335cc1581a67ULL, /* VK_KHR_maintenance1 */
    /*  257 */ 0xfc226b9c5b522a9eULL, /* VK_KHR_maintenance10 */
    /*  258 */ 0x8ffe792f51cd1450ULL, /* VK_KHR_maintenance2 */
    /*  259 */ 0xea219cc76502a8afULL, /* VK_KHR_maintenance3 */
    /*  260 */ 0xa66e463f036dae4aULL, /* VK_KHR_maintenance4 */
    /*  261 */ 0xc5e86b535cee6698ULL, /* VK_KHR_maintenance5 */
    /*  262 */ 0xf60b7de240a15ab4ULL, /* VK_KHR_maintenance6 */
    /*  263 */ 0x3d59040ce3c13f21ULL, /* VK_KHR_maintenance7 */
    /*  264 */ 0xb6892d36c521b488ULL, /* VK_KHR_maintenance8 */
    /*  265 */ 0xbc9d8954b3903237ULL, /* VK_KHR_maintenance9 */
    /*  266 */ 0x64d252cf56a64addULL, /* VK_KHR_map_memory2 */
    /*  267 */ 0x5af12378bc6d7169ULL, /* VK_KHR_multiview */
    /*  268 */ 0x1bb74dfe8d7e0b31ULL, /* VK_KHR_performance_query */
    /*  269 */ 0x935d834a6c18d3edULL, /* VK_KHR_pipeline_binary */
    /*  270 */ 0x91248c6b162c4180ULL, /* VK_KHR_pipeline_executable_properties */
    /*  271 */ 0x039c65d87fb09ca9ULL, /* VK_KHR_pipeline_library */
    /*  272 */ 0x28644eeb112058b6ULL, /* VK_KHR_portability_enumeration */
    /*  273 */ 0xac06576b97f9486aULL, /* VK_KHR_portability_subset */
    /*  274 */ 0xe82e301141092b1eULL, /* VK_KHR_present_id */
    /*  275 */ 0x209717f94a827c5fULL, /* VK_KHR_present_id2 */
    /*  276 */ 0x9ebcb805ef6af243ULL, /* VK_KHR_present_mode_fifo_latest_ready */
    /*  277 */ 0x47954f24ddf5185eULL, /* VK_KHR_present_wait */
    /*  278 */ 0x2822277cba1268a0ULL, /* VK_KHR_present_wait2 */
    /*  279 */ 0x2123bacd888c07ecULL, /* VK_KHR_push_descriptor */
    /*  280 */ 0x8bf873804879f2cfULL, /* VK_KHR_ray_query */
    /*  281 */ 0x9df3df162357e4b0ULL, /* VK_KHR_ray_tracing_maintenance1 */
    /*  282 */ 0xaef707cb154a81afULL, /* VK_KHR_ray_tracing_pipeline */
    /*  283 */ 0x697f77ef7ba14203ULL, /* VK_KHR_ray_tracing_position_fetch */
    /*  284 */ 0x4b17e19fd947a1d3ULL, /* VK_KHR_relaxed_block_layout */
    /*  285 */ 0xaab0786abb72567aULL, /* VK_KHR_robustness2 */
    /*  286 */ 0x5d5e936103817cdaULL, /* VK_KHR_sampler_mirror_clamp_to_edge */
    /*  287 */ 0x22004cfa79ba7177ULL, /* VK_KHR_sampler_ycbcr_conversion */
    /*  288 */ 0xba2c0ae86fd11630ULL, /* VK_KHR_separate_depth_stencil_layouts */
    /*  289 */ 0xb16f5fd69d97f3a1ULL, /* VK_KHR_shader_atomic_int64 */
    /*  290 */ 0xd49205e9c445114aULL, /* VK_KHR_shader_bfloat16 */
    /*  291 */ 0xeee9708671fa7c77ULL, /* VK_KHR_shader_clock */
    /*  292 */ 0xb35fc4bdb32f3d81ULL, /* VK_KHR_shader_draw_parameters */
    /*  293 */ 0xab0eda6676f1fd31ULL, /* VK_KHR_shader_expect_assume */
    /*  294 */ 0x4dad563cb513c7c9ULL, /* VK_KHR_shader_float16_int8 */
    /*  295 */ 0x548b20a76c855b46ULL, /* VK_KHR_shader_float_controls */
    /*  296 */ 0xa1150eef92f851e8ULL, /* VK_KHR_shader_float_controls2 */
    /*  297 */ 0x725086eb3e9d141fULL, /* VK_KHR_shader_fma */
    /*  298 */ 0x9d14cd5379daf7cbULL, /* VK_KHR_shader_integer_dot_product */
    /*  299 */ 0x42aefa5598fde4abULL, /* VK_KHR_shader_maximal_reconvergence */
    /*  300 */ 0xb38332d7467f8474ULL, /* VK_KHR_shader_non_semantic_info */
    /*  301 */ 0xab3f0af6d5504bf4ULL, /* VK_KHR_shader_quad_control */
    /*  302 */ 0x1bdfe042874be24fULL, /* VK_KHR_shader_relaxed_extended_instruction */
    /*  303 */ 0xcda588b0d067d48fULL, /* VK_KHR_shader_subgroup_extended_types */
    /*  304 */ 0xd0836c7a4d04b579ULL, /* VK_KHR_shader_subgroup_rotate */
    /*  305 */ 0x64fbf5bc74afe199ULL, /* VK_KHR_shader_subgroup_uniform_control_flow */
    /*  306 */ 0x6e5fde40560b40a9ULL, /* VK_KHR_shader_terminate_invocation */
    /*  307 */ 0x9264c3e61ed27e2fULL, /* VK_KHR_shader_untyped_pointers */
    /*  308 */ 0x7e6871b03dee137bULL, /* VK_KHR_shared_presentable_image */
    /*  309 */ 0x06c03c1c3db9815dULL, /* VK_KHR_spirv_1_4 */
    /*  310 */ 0x743f86c26df32ea2ULL, /* VK_KHR_storage_buffer_storage_class */
    /*  311 */ 0x2c4f009293a35548ULL, /* VK_KHR_surface */
    /*  312 */ 0x2447a025c1b4d0ffULL, /* VK_KHR_surface_maintenance1 */
    /*  313 */ 0xa8506d9aef558591ULL, /* VK_KHR_surface_protected_capabilities */
    /*  314 */ 0x6cefabf4c944ccecULL, /* VK_KHR_swapchain */
    /*  315 */ 0x8d650abfe09cadb2ULL, /* VK_KHR_swapchain_maintenance1 */
    /*  316 */ 0x2149e839e759e400ULL, /* VK_KHR_swapchain_mutable_format */
    /*  317 */ 0xf1cfa2ea69e6ec0eULL, /* VK_KHR_synchronization2 */
    /*  318 */ 0x61ed378f50459bf2ULL, /* VK_KHR_timeline_semaphore */
    /*  319 */ 0xfbb615f2cdb7e18fULL, /* VK_KHR_unified_image_layouts */
    /*  320 */ 0x3334ed809879d360ULL, /* VK_KHR_uniform_buffer_standard_layout */
    /*  321 */ 0x6146df22dcb09470ULL, /* VK_KHR_variable_pointers */
    /*  322 */ 0xcfd1e6704e4a4227ULL, /* VK_KHR_vertex_attribute_divisor */
    /*  323 */ 0x4ccc16568a9a2944ULL, /* VK_KHR_video_decode_av1 */
    /*  324 */ 0x0093b60d00888052ULL, /* VK_KHR_video_decode_h264 */
    /*  325 */ 0x4116f6bec0017e79ULL, /* VK_KHR_video_decode_h265 */
    /*  326 */ 0x363dac5e35a2f1eeULL, /* VK_KHR_video_decode_queue */
    /*  327 */ 0xc656a5824a51a00eULL, /* VK_KHR_video_decode_vp9 */
    /*  328 */ 0x35e683e888a7a54cULL, /* VK_KHR_video_encode_av1 */
    /*  329 */ 0xa77247c5899dc785ULL, /* VK_KHR_video_encode_h264 */
    /*  330 */ 0x8b86366e33c748eeULL, /* VK_KHR_video_encode_h265 */
    /*  331 */ 0x02882dc081b4a9a3ULL, /* VK_KHR_video_encode_intra_refresh */
    /*  332 */ 0x3f1a8c895b8e8debULL, /* VK_KHR_video_encode_quantization_map */
    /*  333 */ 0xdda14264a3bda234ULL, /* VK_KHR_video_encode_queue */
    /*  334 */ 0x9fb8181989e29256ULL, /* VK_KHR_video_maintenance1 */
    /*  335 */ 0xfd1949eb2a3c752bULL, /* VK_KHR_video_maintenance2 */
    /*  336 */ 0xc3d1c9b40515a6a4ULL, /* VK_KHR_video_queue */
    /*  337 */ 0x34899ec7a7b17614ULL, /* VK_KHR_vulkan_memory_model */
    /*  338 */ 0x906fcab3e0d202a5ULL, /* VK_KHR_wayland_surface */
    /*  339 */ 0x19d48609837c8701ULL, /* VK_KHR_win32_keyed_mutex */
    /*  340 */ 0xc93557e7cef43233ULL, /* VK_KHR_win32_surface */
    /*  341 */ 0x75ee32f09cdd8db9ULL, /* VK_KHR_workgroup_memory_explicit_layout */
    /*  342 */ 0x32a481baaa637e2cULL, /* VK_KHR_xcb_surface */
    /*  343 */ 0x863c0e309551346eULL, /* VK_KHR_xlib_surface */
    /*  344 */ 0x58d24a21f116065bULL, /* VK_KHR_zero_initialize_workgroup_memory */
    /*  345 */ 0x5615881540a7f6d8ULL, /* VK_LUNARG_direct_driver_loading */
    /*  346 */ 0x6f8fb9c8b46fc189ULL, /* VK_MESA_image_alignment_control */
    /*  347 */ 0xc1c930637836bf44ULL, /* VK_MSFT_layered_driver */
    /*  348 */ 0x489cf2a16640d39eULL, /* VK_MVK_ios_surface */
    /*  349 */ 0x3274c65edf45286cULL, /* VK_MVK_macos_surface */
    /*  350 */ 0x53643314731ac57aULL, /* VK_NN_vi_surface */
    /*  351 */ 0x5bf53745255ccc0eULL, /* VK_NVX_binary_import */
    /*  352 */ 0x20b59934a97efd1cULL, /* VK_NVX_image_view_handle */
    /*  353 */ 0x112ee8733e2b22b3ULL, /* VK_NVX_multiview_per_view_attributes */
    /*  354 */ 0x71fe862eee072b1eULL, /* VK_NV_acquire_winrt_display */
    /*  355 */ 0x9217a69de789d3feULL, /* VK_NV_clip_space_w_scaling */
    /*  356 */ 0x5d2cfdaf5ecc308bULL, /* VK_NV_cluster_acceleration_structure */
    /*  357 */ 0xad1ba91484f69ca3ULL, /* VK_NV_command_buffer_inheritance */
    /*  358 */ 0x9e21a0bcf274063aULL, /* VK_NV_compute_occupancy_priority */
    /*  359 */ 0x21d19e30b520bdd6ULL, /* VK_NV_compute_shader_derivatives */
    /*  360 */ 0x069e842b3b51cefbULL, /* VK_NV_cooperative_matrix */
    /*  361 */ 0xfecfd80519026209ULL, /* VK_NV_cooperative_matrix2 */
    /*  362 */ 0x9b6d5b7725490586ULL, /* VK_NV_cooperative_vector */
    /*  363 */ 0xce889f8d6b40e84fULL, /* VK_NV_copy_memory_indirect */
    /*  364 */ 0xed85b1ac0329a8cdULL, /* VK_NV_corner_sampled_image */
    /*  365 */ 0x81b617790445f852ULL, /* VK_NV_coverage_reduction_mode */
    /*  366 */ 0x3644690c3bd14289ULL, /* VK_NV_cuda_kernel_launch */
    /*  367 */ 0xbb81f8243fcc7db5ULL, /* VK_NV_dedicated_allocation */
    /*  368 */ 0x00ce18bba106c2adULL, /* VK_NV_dedicated_allocation_image_aliasing */
    /*  369 */ 0x23bcacd889bea60cULL, /* VK_NV_descriptor_pool_overallocation */
    /*  370 */ 0xf03dfd81ad17796fULL, /* VK_NV_device_diagnostic_checkpoints */
    /*  371 */ 0xc8050fbd31afc5b5ULL, /* VK_NV_device_diagnostics_config */
    /*  372 */ 0xee7bfcd5523cff09ULL, /* VK_NV_device_generated_commands */
    /*  373 */ 0x2ff0ded4f3f040e9ULL, /* VK_NV_device_generated_commands_compute */
    /*  374 */ 0xc07b5e2a89ddc607ULL, /* VK_NV_displacement_micromap */
    /*  375 */ 0x5138c2f68bcb3608ULL, /* VK_NV_display_stereo */
    /*  376 */ 0xb2344e462fd9ef1bULL, /* VK_NV_extended_sparse_address_space */
    /*  377 */ 0xd15b433c649fb093ULL, /* VK_NV_external_compute_queue */
    /*  378 */ 0xab0f59a00375b1ecULL, /* VK_NV_external_memory */
    /*  379 */ 0x518148eb9166b4b9ULL, /* VK_NV_external_memory_capabilities */
    /*  380 */ 0x3c96386b301a3cdcULL, /* VK_NV_external_memory_rdma */
    /*  381 */ 0xcf69c3e7cbd068e4ULL, /* VK_NV_external_memory_win32 */
    /*  382 */ 0xdf9a65a432a12606ULL, /* VK_NV_fill_rectangle */
    /*  383 */ 0x9a6fda1e2f4f9096ULL, /* VK_NV_fragment_coverage_to_color */
    /*  384 */ 0xc294d55a56858fb6ULL, /* VK_NV_fragment_shader_barycentric */
    /*  385 */ 0x2ece12f465807058ULL, /* VK_NV_fragment_shading_rate_enums */
    /*  386 */ 0x4caba51b111c61b9ULL, /* VK_NV_framebuffer_mixed_samples */
    /*  387 */ 0xe0c4918343f3874cULL, /* VK_NV_geometry_shader_passthrough */
    /*  388 */ 0xd659873b3f6bc024ULL, /* VK_NV_glsl_shader */
    /*  389 */ 0xe39346d87fc9aa45ULL, /* VK_NV_inherited_viewport_scissor */
    /*  390 */ 0x52fcc4c2d713dad4ULL, /* VK_NV_linear_color_attachment */
    /*  391 */ 0xb58daf9c015becf7ULL, /* VK_NV_low_latency */
    /*  392 */ 0xa9eb852dfd7a1eceULL, /* VK_NV_low_latency2 */
    /*  393 */ 0x6c878fdbf1e4a7fbULL, /* VK_NV_memory_decompression */
    /*  394 */ 0x7401a89f84bc926bULL, /* VK_NV_mesh_shader */
    /*  395 */ 0x929112526891454eULL, /* VK_NV_optical_flow */
    /*  396 */ 0x6e9d1f60324c4761ULL, /* VK_NV_partitioned_acceleration_structure */
    /*  397 */ 0x5e0416a20f89c9f4ULL, /* VK_NV_per_stage_descriptor_set */
    /*  398 */ 0x48102b2d563a8028ULL, /* VK_NV_present_barrier */
    /*  399 */ 0xe16f6927a8473cabULL, /* VK_NV_present_metering */
    /*  400 */ 0x8a4300fc934ecbe8ULL, /* VK_NV_push_constant_bank */
    /*  401 */ 0xc20950e0cbc5bdc0ULL, /* VK_NV_raw_access_chains */
    /*  402 */ 0x3d4e9e0bb54735feULL, /* VK_NV_ray_tracing */
    /*  403 */ 0xe12f14699c6db9dbULL, /* VK_NV_ray_tracing_invocation_reorder */
    /*  404 */ 0x4157611d54ac1bc1ULL, /* VK_NV_ray_tracing_linear_swept_spheres */
    /*  405 */ 0xba4184e5104338cbULL, /* VK_NV_ray_tracing_motion_blur */
    /*  406 */ 0x451532c42bd881b2ULL, /* VK_NV_ray_tracing_validation */
    /*  407 */ 0x92ccabdfa0a3d6e4ULL, /* VK_NV_representative_fragment_test */
    /*  408 */ 0xc4d99252b7b7843fULL, /* VK_NV_sample_mask_override_coverage */
    /*  409 */ 0xd4d2cda699fc74aeULL, /* VK_NV_scissor_exclusive */
    /*  410 */ 0xb8974b1af4c34b58ULL, /* VK_NV_shader_atomic_float16_vector */
    /*  411 */ 0x52f9f98f09f18085ULL, /* VK_NV_shader_image_footprint */
    /*  412 */ 0xc394473a75e21d7cULL, /* VK_NV_shader_sm_builtins */
    /*  413 */ 0x5b6c5e76d8a8364eULL, /* VK_NV_shader_subgroup_partitioned */
    /*  414 */ 0xcac204d487e563d3ULL, /* VK_NV_shading_rate_image */
    /*  415 */ 0xfc6e35d06ddf634eULL, /* VK_NV_viewport_array2 */
    /*  416 */ 0x7748ea26eecd7e90ULL, /* VK_NV_viewport_swizzle */
    /*  417 */ 0x7e4ac6b10102b887ULL, /* VK_NV_win32_keyed_mutex */
    /*  418 */ 0xc6aa2bfbecbd52c7ULL, /* VK_OHOS_external_memory */
    /*  419 */ 0xfb89dacebce47785ULL, /* VK_OHOS_surface */
    /*  420 */ 0x6e25495f0f9c0331ULL, /* VK_QCOM_cooperative_matrix_conversion */
    /*  421 */ 0x401c0cb6fb4e6f91ULL, /* VK_QCOM_data_graph_model */
    /*  422 */ 0x5c76ad884426c86cULL, /* VK_QCOM_filter_cubic_clamp */
    /*  423 */ 0xc7386bbfd1b9b423ULL, /* VK_QCOM_filter_cubic_weights */
    /*  424 */ 0xff445069da66b635ULL, /* VK_QCOM_fragment_density_map_offset */
    /*  425 */ 0xa6cab4106375cdfaULL, /* VK_QCOM_image_processing */
    /*  426 */ 0xa4a1ae34c2527a4aULL, /* VK_QCOM_image_processing2 */
    /*  427 */ 0xbff750af2234e2ceULL, /* VK_QCOM_multiview_per_view_render_areas */
    /*  428 */ 0x876a51c6df08420aULL, /* VK_QCOM_multiview_per_view_viewports */
    /*  429 */ 0xa3b4fc40f185c799ULL, /* VK_QCOM_render_pass_shader_resolve */
    /*  430 */ 0x9b5c2a0bc41e00cdULL, /* VK_QCOM_render_pass_store_ops */
    /*  431 */ 0x8d33cd618c723019ULL, /* VK_QCOM_render_pass_transform */
    /*  432 */ 0xd5a3f971e2e8b5c9ULL, /* VK_QCOM_rotated_copy_commands */
    /*  433 */ 0x73244ac23f3ec04aULL, /* VK_QCOM_tile_memory_heap */
    /*  434 */ 0xc37b456dbdf5565fULL, /* VK_QCOM_tile_properties */
    /*  435 */ 0x80b039482dfe4631ULL, /* VK_QCOM_tile_shading */
    /*  436 */ 0x49bfbd9f92e0b029ULL, /* VK_QCOM_ycbcr_degamma */
    /*  437 */ 0xc2e6f6dcc7614aceULL, /* VK_QNX_external_memory_screen_buffer */
    /*  438 */ 0x236bd86b3b17cf06ULL, /* VK_QNX_screen_surface */
    /*  439 */ 0xe6fed416ddebf8d0ULL, /* VK_SEC_amigo_profiling */
    /*  440 */ 0x8501d958b34af871ULL, /* VK_SEC_pipeline_cache_incremental_mode */
    /*  441 */ 0xf2db0e65fc3b0eafULL, /* VK_SEC_ubm_surface */
    /*  442 */ 0x45542cac22bd41a7ULL, /* VK_VALVE_descriptor_set_host_mapping */
    /*  443 */ 0x7aab48db428bd31bULL, /* VK_VALVE_fragment_density_map_layered */
    /*  444 */ 0x38c73d4ab66a4942ULL, /* VK_VALVE_mutable_descriptor_type */
    /*  445 */ 0x9d00e44ab9b69551ULL, /* VK_VALVE_shader_mixed_float_dot_product */
    /*  446 */ 0x5674ed8bc838fecbULL  /* VK_VALVE_video_encode_rgb_conversion */
};

static const GladAliasPair_t GLAD_Vulkan_command_aliases[] = {
    {  138,  436 }, /* vkBindBufferMemory2 and vkBindBufferMemory2KHR */
    {  139,  437 }, /* vkBindImageMemory2 and vkBindImageMemory2KHR */
    {  198,  304 }, /* vkCmdBeginRendering and vkCmdBeginRenderingKHR */
    {  175,  355 }, /* vkCmdBeginRenderPass2 and vkCmdBeginRenderPass2KHR */
    {  225,  748 }, /* vkCmdBindDescriptorSets2 and vkCmdBindDescriptorSets2KHR */
    {  230,  704 }, /* vkCmdBindIndexBuffer2 and vkCmdBindIndexBuffer2KHR */
    {  205,  517 }, /* vkCmdBindVertexBuffers2 and vkCmdBindVertexBuffers2EXT */
    {  196,  591 }, /* vkCmdBlitImage2 and vkCmdBlitImage2KHR */
    {  186,  587 }, /* vkCmdCopyBuffer2 and vkCmdCopyBuffer2KHR */
    {  188,  589 }, /* vkCmdCopyBufferToImage2 and vkCmdCopyBufferToImage2KHR */
    {  187,  588 }, /* vkCmdCopyImage2 and vkCmdCopyImage2KHR */
    {  189,  590 }, /* vkCmdCopyImageToBuffer2 and vkCmdCopyImageToBuffer2KHR */
    {  158,  318 }, /* vkCmdDispatchBase and vkCmdDispatchBaseKHR */
    {  173,  302 }, /* vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountAMD */
    {  173,  460 }, /* vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountKHR */
    {  172,  301 }, /* vkCmdDrawIndirectCount and vkCmdDrawIndirectCountAMD */
    {  172,  459 }, /* vkCmdDrawIndirectCount and vkCmdDrawIndirectCountKHR */
    {  199,  305 }, /* vkCmdEndRendering and vkCmdEndRenderingKHR */
    {  787,  789 }, /* vkCmdEndRendering2EXT and vkCmdEndRendering2KHR */
    {  177,  357 }, /* vkCmdEndRenderPass2 and vkCmdEndRenderPass2KHR */
    {  176,  356 }, /* vkCmdNextSubpass2 and vkCmdNextSubpass2KHR */
    {  183,  569 }, /* vkCmdPipelineBarrier2 and vkCmdPipelineBarrier2KHR */
    {  226,  749 }, /* vkCmdPushConstants2 and vkCmdPushConstants2KHR */
    {  223,  332 }, /* vkCmdPushDescriptorSet and vkCmdPushDescriptorSetKHR */
    {  227,  750 }, /* vkCmdPushDescriptorSet2 and vkCmdPushDescriptorSet2KHR */
    {  224,  333 }, /* vkCmdPushDescriptorSetWithTemplate and vkCmdPushDescriptorSetWithTemplateKHR */
    {  228,  751 }, /* vkCmdPushDescriptorSetWithTemplate2 and vkCmdPushDescriptorSetWithTemplate2KHR */
    {  194,  567 }, /* vkCmdResetEvent2 and vkCmdResetEvent2KHR */
    {  197,  592 }, /* vkCmdResolveImage2 and vkCmdResolveImage2KHR */
    {  200,  512 }, /* vkCmdSetCullMode and vkCmdSetCullModeEXT */
    {  213,  615 }, /* vkCmdSetDepthBiasEnable and vkCmdSetDepthBiasEnableEXT */
    {  209,  521 }, /* vkCmdSetDepthBoundsTestEnable and vkCmdSetDepthBoundsTestEnableEXT */
    {  208,  520 }, /* vkCmdSetDepthCompareOp and vkCmdSetDepthCompareOpEXT */
    {  206,  518 }, /* vkCmdSetDepthTestEnable and vkCmdSetDepthTestEnableEXT */
    {  207,  519 }, /* vkCmdSetDepthWriteEnable and vkCmdSetDepthWriteEnableEXT */
    {  141,  317 }, /* vkCmdSetDeviceMask and vkCmdSetDeviceMaskKHR */
    {  193,  566 }, /* vkCmdSetEvent2 and vkCmdSetEvent2KHR */
    {  201,  513 }, /* vkCmdSetFrontFace and vkCmdSetFrontFaceEXT */
    {  229,  510 }, /* vkCmdSetLineStipple and vkCmdSetLineStippleEXT */
    {  229,  745 }, /* vkCmdSetLineStipple and vkCmdSetLineStippleKHR */
    {  214,  617 }, /* vkCmdSetPrimitiveRestartEnable and vkCmdSetPrimitiveRestartEnableEXT */
    {  202,  514 }, /* vkCmdSetPrimitiveTopology and vkCmdSetPrimitiveTopologyEXT */
    {  212,  614 }, /* vkCmdSetRasterizerDiscardEnable and vkCmdSetRasterizerDiscardEnableEXT */
    {  232,  495 }, /* vkCmdSetRenderingAttachmentLocations and vkCmdSetRenderingAttachmentLocationsKHR */
    {  233,  496 }, /* vkCmdSetRenderingInputAttachmentIndices and vkCmdSetRenderingInputAttachmentIndicesKHR */
    {  204,  516 }, /* vkCmdSetScissorWithCount and vkCmdSetScissorWithCountEXT */
    {  211,  523 }, /* vkCmdSetStencilOp and vkCmdSetStencilOpEXT */
    {  210,  522 }, /* vkCmdSetStencilTestEnable and vkCmdSetStencilTestEnableEXT */
    {  203,  515 }, /* vkCmdSetViewportWithCount and vkCmdSetViewportWithCountEXT */
    {  195,  568 }, /* vkCmdWaitEvents2 and vkCmdWaitEvents2KHR */
    {  184,  570 }, /* vkCmdWriteTimestamp2 and vkCmdWriteTimestamp2KHR */
    {  221,  534 }, /* vkCopyImageToImage and vkCopyImageToImageEXT */
    {  220,  533 }, /* vkCopyImageToMemory and vkCopyImageToMemoryEXT */
    {  219,  532 }, /* vkCopyMemoryToImage and vkCopyMemoryToImageEXT */
    {  159,  336 }, /* vkCreateDescriptorUpdateTemplate and vkCreateDescriptorUpdateTemplateKHR */
    {  179,  549 }, /* vkCreatePrivateDataSlot and vkCreatePrivateDataSlotEXT */
    {  174,  354 }, /* vkCreateRenderPass2 and vkCreateRenderPass2KHR */
    {  163,  434 }, /* vkCreateSamplerYcbcrConversion and vkCreateSamplerYcbcrConversionKHR */
    {  160,  337 }, /* vkDestroyDescriptorUpdateTemplate and vkDestroyDescriptorUpdateTemplateKHR */
    {  180,  550 }, /* vkDestroyPrivateDataSlot and vkDestroyPrivateDataSlotEXT */
    {  164,  435 }, /* vkDestroySamplerYcbcrConversion and vkDestroySamplerYcbcrConversionKHR */
    {  142,  321 }, /* vkEnumeratePhysicalDeviceGroups and vkEnumeratePhysicalDeviceGroupsKHR */
    {  169,  497 }, /* vkGetBufferDeviceAddress and vkGetBufferDeviceAddressEXT */
    {  169,  507 }, /* vkGetBufferDeviceAddress and vkGetBufferDeviceAddressKHR */
    {  144,  409 }, /* vkGetBufferMemoryRequirements2 and vkGetBufferMemoryRequirements2KHR */
    {  170,  508 }, /* vkGetBufferOpaqueCaptureAddress and vkGetBufferOpaqueCaptureAddressKHR */
    {  465,  747 }, /* vkGetCalibratedTimestampsEXT and vkGetCalibratedTimestampsKHR */
    {  162,  458 }, /* vkGetDescriptorSetLayoutSupport and vkGetDescriptorSetLayoutSupportKHR */
    {  190,  641 }, /* vkGetDeviceBufferMemoryRequirements and vkGetDeviceBufferMemoryRequirementsKHR */
    {  140,  316 }, /* vkGetDeviceGroupPeerMemoryFeatures and vkGetDeviceGroupPeerMemoryFeaturesKHR */
    {  191,  642 }, /* vkGetDeviceImageMemoryRequirements and vkGetDeviceImageMemoryRequirementsKHR */
    {  192,  643 }, /* vkGetDeviceImageSparseMemoryRequirements and vkGetDeviceImageSparseMemoryRequirementsKHR */
    {  217,  706 }, /* vkGetDeviceImageSubresourceLayout and vkGetDeviceImageSubresourceLayoutKHR */
    {  171,  509 }, /* vkGetDeviceMemoryOpaqueCaptureAddress and vkGetDeviceMemoryOpaqueCaptureAddressKHR */
    {  143,  408 }, /* vkGetImageMemoryRequirements2 and vkGetImageMemoryRequirements2KHR */
    {  145,  410 }, /* vkGetImageSparseMemoryRequirements2 and vkGetImageSparseMemoryRequirements2KHR */
    {  218,  536 }, /* vkGetImageSubresourceLayout2 and vkGetImageSubresourceLayout2EXT */
    {  218,  707 }, /* vkGetImageSubresourceLayout2 and vkGetImageSubresourceLayout2KHR */
    {  464,  746 }, /* vkGetPhysicalDeviceCalibrateableTimeDomainsEXT and vkGetPhysicalDeviceCalibrateableTimeDomainsKHR */
    {  155,  322 }, /* vkGetPhysicalDeviceExternalBufferProperties and vkGetPhysicalDeviceExternalBufferPropertiesKHR */
    {  156,  359 }, /* vkGetPhysicalDeviceExternalFenceProperties and vkGetPhysicalDeviceExternalFencePropertiesKHR */
    {  157,  327 }, /* vkGetPhysicalDeviceExternalSemaphoreProperties and vkGetPhysicalDeviceExternalSemaphorePropertiesKHR */
    {  146,  309 }, /* vkGetPhysicalDeviceFeatures2 and vkGetPhysicalDeviceFeatures2KHR */
    {  148,  311 }, /* vkGetPhysicalDeviceFormatProperties2 and vkGetPhysicalDeviceFormatProperties2KHR */
    {  149,  312 }, /* vkGetPhysicalDeviceImageFormatProperties2 and vkGetPhysicalDeviceImageFormatProperties2KHR */
    {  151,  314 }, /* vkGetPhysicalDeviceMemoryProperties2 and vkGetPhysicalDeviceMemoryProperties2KHR */
    {  147,  310 }, /* vkGetPhysicalDeviceProperties2 and vkGetPhysicalDeviceProperties2KHR */
    {  150,  313 }, /* vkGetPhysicalDeviceQueueFamilyProperties2 and vkGetPhysicalDeviceQueueFamilyProperties2KHR */
    {  152,  315 }, /* vkGetPhysicalDeviceSparseImageFormatProperties2 and vkGetPhysicalDeviceSparseImageFormatProperties2KHR */
    {  178,  498 }, /* vkGetPhysicalDeviceToolProperties and vkGetPhysicalDeviceToolPropertiesEXT */
    {  182,  552 }, /* vkGetPrivateData and vkGetPrivateDataEXT */
    {  454,  429 }, /* vkGetRayTracingShaderGroupHandlesNV and vkGetRayTracingShaderGroupHandlesKHR */
    {  231,  705 }, /* vkGetRenderingAreaGranularity and vkGetRenderingAreaGranularityKHR */
    {  166,  474 }, /* vkGetSemaphoreCounterValue and vkGetSemaphoreCounterValueKHR */
    {  215,  537 }, /* vkMapMemory2 and vkMapMemory2KHR */
    {  185,  571 }, /* vkQueueSubmit2 and vkQueueSubmit2KHR */
    {  539,  722 }, /* vkReleaseSwapchainImagesEXT and vkReleaseSwapchainImagesKHR */
    {  165,  511 }, /* vkResetQueryPool and vkResetQueryPoolEXT */
    {  181,  551 }, /* vkSetPrivateData and vkSetPrivateDataEXT */
    {  168,  476 }, /* vkSignalSemaphore and vkSignalSemaphoreKHR */
    {  222,  535 }, /* vkTransitionImageLayout and vkTransitionImageLayoutEXT */
    {  153,  320 }, /* vkTrimCommandPool and vkTrimCommandPoolKHR */
    {  216,  538 }, /* vkUnmapMemory2 and vkUnmapMemory2KHR */
    {  161,  338 }, /* vkUpdateDescriptorSetWithTemplate and vkUpdateDescriptorSetWithTemplateKHR */
    {  167,  475 }, /* vkWaitSemaphores and vkWaitSemaphoresKHR */
};

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

GLAD_NO_INLINE static void glad_vk_resolve_aliases(GladVulkanContext *context) {
    uint32_t i;

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_Vulkan_command_aliases); ++i) {
        i = glad_vk_resolve_alias_group(context, GLAD_Vulkan_command_aliases, i, GLAD_ARRAYSIZE(GLAD_Vulkan_command_aliases));
    }
}

static void glad_vk_load_pfn_range(GladVulkanContext *context, GLADvkuserptrloadfunc load, void* userptr, uint16_t pfnStart, uint32_t numPfns)
{
    uint32_t pfnIdx;

    for (pfnIdx = pfnStart; pfnIdx < pfnStart + numPfns; ++pfnIdx) {
        const char *name = GLAD_Vulkan_fn_names[pfnIdx];
        const enum GLADcommandscope scope = (enum GLADcommandscope)GLAD_Vulkan_fn_scopes[pfnIdx];
        context->pfnArray[pfnIdx] = (void *)load(userptr, name, scope);
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

    /* Sort extension list for binary search */
    glad_sort_hashes(extensions, total_extension_count);

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

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_vulkan_ext_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_vulkan_ext_pfn_ranges[i];
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
