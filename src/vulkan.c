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

static const char *GLAD_Vulkan_fn_names[] = {
    /*    0 */ "vkAcquireNextImage2KHR",
    /*    1 */ "vkAllocateCommandBuffers",
    /*    2 */ "vkAllocateDescriptorSets",
    /*    3 */ "vkAllocateMemory",
    /*    4 */ "vkBeginCommandBuffer",
    /*    5 */ "vkBindBufferMemory",
    /*    6 */ "vkBindBufferMemory2",
    /*    7 */ "vkBindBufferMemory2KHR",
    /*    8 */ "vkBindImageMemory",
    /*    9 */ "vkBindImageMemory2",
    /*   10 */ "vkBindImageMemory2KHR",
    /*   11 */ "vkCmdBeginQuery",
    /*   12 */ "vkCmdBeginRenderPass",
    /*   13 */ "vkCmdBeginRenderPass2",
    /*   14 */ "vkCmdBeginRenderPass2KHR",
    /*   15 */ "vkCmdBeginRendering",
    /*   16 */ "vkCmdBeginRenderingKHR",
    /*   17 */ "vkCmdBindDescriptorSets",
    /*   18 */ "vkCmdBindIndexBuffer",
    /*   19 */ "vkCmdBindPipeline",
    /*   20 */ "vkCmdBindShadersEXT",
    /*   21 */ "vkCmdBindVertexBuffers",
    /*   22 */ "vkCmdBindVertexBuffers2",
    /*   23 */ "vkCmdBindVertexBuffers2EXT",
    /*   24 */ "vkCmdBlitImage",
    /*   25 */ "vkCmdBlitImage2",
    /*   26 */ "vkCmdBlitImage2KHR",
    /*   27 */ "vkCmdClearAttachments",
    /*   28 */ "vkCmdClearColorImage",
    /*   29 */ "vkCmdClearDepthStencilImage",
    /*   30 */ "vkCmdCopyBuffer",
    /*   31 */ "vkCmdCopyBuffer2",
    /*   32 */ "vkCmdCopyBuffer2KHR",
    /*   33 */ "vkCmdCopyBufferToImage",
    /*   34 */ "vkCmdCopyBufferToImage2",
    /*   35 */ "vkCmdCopyBufferToImage2KHR",
    /*   36 */ "vkCmdCopyImage",
    /*   37 */ "vkCmdCopyImage2",
    /*   38 */ "vkCmdCopyImage2KHR",
    /*   39 */ "vkCmdCopyImageToBuffer",
    /*   40 */ "vkCmdCopyImageToBuffer2",
    /*   41 */ "vkCmdCopyImageToBuffer2KHR",
    /*   42 */ "vkCmdCopyQueryPoolResults",
    /*   43 */ "vkCmdDispatch",
    /*   44 */ "vkCmdDispatchBase",
    /*   45 */ "vkCmdDispatchBaseKHR",
    /*   46 */ "vkCmdDispatchIndirect",
    /*   47 */ "vkCmdDraw",
    /*   48 */ "vkCmdDrawIndexed",
    /*   49 */ "vkCmdDrawIndexedIndirect",
    /*   50 */ "vkCmdDrawIndexedIndirectCount",
    /*   51 */ "vkCmdDrawIndexedIndirectCountAMD",
    /*   52 */ "vkCmdDrawIndexedIndirectCountKHR",
    /*   53 */ "vkCmdDrawIndirect",
    /*   54 */ "vkCmdDrawIndirectCount",
    /*   55 */ "vkCmdDrawIndirectCountAMD",
    /*   56 */ "vkCmdDrawIndirectCountKHR",
    /*   57 */ "vkCmdEndQuery",
    /*   58 */ "vkCmdEndRenderPass",
    /*   59 */ "vkCmdEndRenderPass2",
    /*   60 */ "vkCmdEndRenderPass2KHR",
    /*   61 */ "vkCmdEndRendering",
    /*   62 */ "vkCmdEndRenderingKHR",
    /*   63 */ "vkCmdExecuteCommands",
    /*   64 */ "vkCmdFillBuffer",
    /*   65 */ "vkCmdNextSubpass",
    /*   66 */ "vkCmdNextSubpass2",
    /*   67 */ "vkCmdNextSubpass2KHR",
    /*   68 */ "vkCmdPipelineBarrier",
    /*   69 */ "vkCmdPipelineBarrier2",
    /*   70 */ "vkCmdPipelineBarrier2KHR",
    /*   71 */ "vkCmdPushConstants",
    /*   72 */ "vkCmdPushDescriptorSetWithTemplateKHR",
    /*   73 */ "vkCmdResetEvent",
    /*   74 */ "vkCmdResetEvent2",
    /*   75 */ "vkCmdResetEvent2KHR",
    /*   76 */ "vkCmdResetQueryPool",
    /*   77 */ "vkCmdResolveImage",
    /*   78 */ "vkCmdResolveImage2",
    /*   79 */ "vkCmdResolveImage2KHR",
    /*   80 */ "vkCmdSetAlphaToCoverageEnableEXT",
    /*   81 */ "vkCmdSetAlphaToOneEnableEXT",
    /*   82 */ "vkCmdSetBlendConstants",
    /*   83 */ "vkCmdSetColorBlendAdvancedEXT",
    /*   84 */ "vkCmdSetColorBlendEnableEXT",
    /*   85 */ "vkCmdSetColorBlendEquationEXT",
    /*   86 */ "vkCmdSetColorWriteMaskEXT",
    /*   87 */ "vkCmdSetConservativeRasterizationModeEXT",
    /*   88 */ "vkCmdSetCoverageModulationModeNV",
    /*   89 */ "vkCmdSetCoverageModulationTableEnableNV",
    /*   90 */ "vkCmdSetCoverageModulationTableNV",
    /*   91 */ "vkCmdSetCoverageReductionModeNV",
    /*   92 */ "vkCmdSetCoverageToColorEnableNV",
    /*   93 */ "vkCmdSetCoverageToColorLocationNV",
    /*   94 */ "vkCmdSetCullMode",
    /*   95 */ "vkCmdSetCullModeEXT",
    /*   96 */ "vkCmdSetDepthBias",
    /*   97 */ "vkCmdSetDepthBiasEnable",
    /*   98 */ "vkCmdSetDepthBiasEnableEXT",
    /*   99 */ "vkCmdSetDepthBounds",
    /*  100 */ "vkCmdSetDepthBoundsTestEnable",
    /*  101 */ "vkCmdSetDepthBoundsTestEnableEXT",
    /*  102 */ "vkCmdSetDepthClampEnableEXT",
    /*  103 */ "vkCmdSetDepthClipEnableEXT",
    /*  104 */ "vkCmdSetDepthClipNegativeOneToOneEXT",
    /*  105 */ "vkCmdSetDepthCompareOp",
    /*  106 */ "vkCmdSetDepthCompareOpEXT",
    /*  107 */ "vkCmdSetDepthTestEnable",
    /*  108 */ "vkCmdSetDepthTestEnableEXT",
    /*  109 */ "vkCmdSetDepthWriteEnable",
    /*  110 */ "vkCmdSetDepthWriteEnableEXT",
    /*  111 */ "vkCmdSetDeviceMask",
    /*  112 */ "vkCmdSetDeviceMaskKHR",
    /*  113 */ "vkCmdSetEvent",
    /*  114 */ "vkCmdSetEvent2",
    /*  115 */ "vkCmdSetEvent2KHR",
    /*  116 */ "vkCmdSetExtraPrimitiveOverestimationSizeEXT",
    /*  117 */ "vkCmdSetFrontFace",
    /*  118 */ "vkCmdSetFrontFaceEXT",
    /*  119 */ "vkCmdSetLineRasterizationModeEXT",
    /*  120 */ "vkCmdSetLineStippleEnableEXT",
    /*  121 */ "vkCmdSetLineWidth",
    /*  122 */ "vkCmdSetLogicOpEXT",
    /*  123 */ "vkCmdSetLogicOpEnableEXT",
    /*  124 */ "vkCmdSetPatchControlPointsEXT",
    /*  125 */ "vkCmdSetPolygonModeEXT",
    /*  126 */ "vkCmdSetPrimitiveRestartEnable",
    /*  127 */ "vkCmdSetPrimitiveRestartEnableEXT",
    /*  128 */ "vkCmdSetPrimitiveTopology",
    /*  129 */ "vkCmdSetPrimitiveTopologyEXT",
    /*  130 */ "vkCmdSetProvokingVertexModeEXT",
    /*  131 */ "vkCmdSetRasterizationSamplesEXT",
    /*  132 */ "vkCmdSetRasterizationStreamEXT",
    /*  133 */ "vkCmdSetRasterizerDiscardEnable",
    /*  134 */ "vkCmdSetRasterizerDiscardEnableEXT",
    /*  135 */ "vkCmdSetRepresentativeFragmentTestEnableNV",
    /*  136 */ "vkCmdSetSampleLocationsEnableEXT",
    /*  137 */ "vkCmdSetSampleMaskEXT",
    /*  138 */ "vkCmdSetScissor",
    /*  139 */ "vkCmdSetScissorWithCount",
    /*  140 */ "vkCmdSetScissorWithCountEXT",
    /*  141 */ "vkCmdSetShadingRateImageEnableNV",
    /*  142 */ "vkCmdSetStencilCompareMask",
    /*  143 */ "vkCmdSetStencilOp",
    /*  144 */ "vkCmdSetStencilOpEXT",
    /*  145 */ "vkCmdSetStencilReference",
    /*  146 */ "vkCmdSetStencilTestEnable",
    /*  147 */ "vkCmdSetStencilTestEnableEXT",
    /*  148 */ "vkCmdSetStencilWriteMask",
    /*  149 */ "vkCmdSetTessellationDomainOriginEXT",
    /*  150 */ "vkCmdSetVertexInputEXT",
    /*  151 */ "vkCmdSetViewport",
    /*  152 */ "vkCmdSetViewportSwizzleNV",
    /*  153 */ "vkCmdSetViewportWScalingEnableNV",
    /*  154 */ "vkCmdSetViewportWithCount",
    /*  155 */ "vkCmdSetViewportWithCountEXT",
    /*  156 */ "vkCmdUpdateBuffer",
    /*  157 */ "vkCmdWaitEvents",
    /*  158 */ "vkCmdWaitEvents2",
    /*  159 */ "vkCmdWaitEvents2KHR",
    /*  160 */ "vkCmdWriteBufferMarker2AMD",
    /*  161 */ "vkCmdWriteTimestamp",
    /*  162 */ "vkCmdWriteTimestamp2",
    /*  163 */ "vkCmdWriteTimestamp2KHR",
    /*  164 */ "vkCreateBuffer",
    /*  165 */ "vkCreateBufferView",
    /*  166 */ "vkCreateCommandPool",
    /*  167 */ "vkCreateComputePipelines",
    /*  168 */ "vkCreateDescriptorPool",
    /*  169 */ "vkCreateDescriptorSetLayout",
    /*  170 */ "vkCreateDescriptorUpdateTemplate",
    /*  171 */ "vkCreateDescriptorUpdateTemplateKHR",
    /*  172 */ "vkCreateDevice",
    /*  173 */ "vkCreateEvent",
    /*  174 */ "vkCreateFence",
    /*  175 */ "vkCreateFramebuffer",
    /*  176 */ "vkCreateGraphicsPipelines",
    /*  177 */ "vkCreateImage",
    /*  178 */ "vkCreateImageView",
    /*  179 */ "vkCreateInstance",
    /*  180 */ "vkCreatePipelineCache",
    /*  181 */ "vkCreatePipelineLayout",
    /*  182 */ "vkCreatePrivateDataSlot",
    /*  183 */ "vkCreatePrivateDataSlotEXT",
    /*  184 */ "vkCreateQueryPool",
    /*  185 */ "vkCreateRenderPass",
    /*  186 */ "vkCreateRenderPass2",
    /*  187 */ "vkCreateRenderPass2KHR",
    /*  188 */ "vkCreateSampler",
    /*  189 */ "vkCreateSamplerYcbcrConversion",
    /*  190 */ "vkCreateSamplerYcbcrConversionKHR",
    /*  191 */ "vkCreateSemaphore",
    /*  192 */ "vkCreateShaderModule",
    /*  193 */ "vkCreateShadersEXT",
    /*  194 */ "vkDestroyBuffer",
    /*  195 */ "vkDestroyBufferView",
    /*  196 */ "vkDestroyCommandPool",
    /*  197 */ "vkDestroyDescriptorPool",
    /*  198 */ "vkDestroyDescriptorSetLayout",
    /*  199 */ "vkDestroyDescriptorUpdateTemplate",
    /*  200 */ "vkDestroyDescriptorUpdateTemplateKHR",
    /*  201 */ "vkDestroyDevice",
    /*  202 */ "vkDestroyEvent",
    /*  203 */ "vkDestroyFence",
    /*  204 */ "vkDestroyFramebuffer",
    /*  205 */ "vkDestroyImage",
    /*  206 */ "vkDestroyImageView",
    /*  207 */ "vkDestroyInstance",
    /*  208 */ "vkDestroyPipeline",
    /*  209 */ "vkDestroyPipelineCache",
    /*  210 */ "vkDestroyPipelineLayout",
    /*  211 */ "vkDestroyPrivateDataSlot",
    /*  212 */ "vkDestroyPrivateDataSlotEXT",
    /*  213 */ "vkDestroyQueryPool",
    /*  214 */ "vkDestroyRenderPass",
    /*  215 */ "vkDestroySampler",
    /*  216 */ "vkDestroySamplerYcbcrConversion",
    /*  217 */ "vkDestroySamplerYcbcrConversionKHR",
    /*  218 */ "vkDestroySemaphore",
    /*  219 */ "vkDestroyShaderEXT",
    /*  220 */ "vkDestroyShaderModule",
    /*  221 */ "vkDeviceWaitIdle",
    /*  222 */ "vkEndCommandBuffer",
    /*  223 */ "vkEnumerateDeviceExtensionProperties",
    /*  224 */ "vkEnumerateDeviceLayerProperties",
    /*  225 */ "vkEnumerateInstanceExtensionProperties",
    /*  226 */ "vkEnumerateInstanceLayerProperties",
    /*  227 */ "vkEnumerateInstanceVersion",
    /*  228 */ "vkEnumeratePhysicalDeviceGroups",
    /*  229 */ "vkEnumeratePhysicalDeviceGroupsKHR",
    /*  230 */ "vkEnumeratePhysicalDevices",
    /*  231 */ "vkFlushMappedMemoryRanges",
    /*  232 */ "vkFreeCommandBuffers",
    /*  233 */ "vkFreeDescriptorSets",
    /*  234 */ "vkFreeMemory",
    /*  235 */ "vkGetBufferDeviceAddress",
    /*  236 */ "vkGetBufferDeviceAddressEXT",
    /*  237 */ "vkGetBufferDeviceAddressKHR",
    /*  238 */ "vkGetBufferMemoryRequirements",
    /*  239 */ "vkGetBufferMemoryRequirements2",
    /*  240 */ "vkGetBufferMemoryRequirements2KHR",
    /*  241 */ "vkGetBufferOpaqueCaptureAddress",
    /*  242 */ "vkGetBufferOpaqueCaptureAddressKHR",
    /*  243 */ "vkGetDescriptorSetLayoutSupport",
    /*  244 */ "vkGetDescriptorSetLayoutSupportKHR",
    /*  245 */ "vkGetDeviceBufferMemoryRequirements",
    /*  246 */ "vkGetDeviceBufferMemoryRequirementsKHR",
    /*  247 */ "vkGetDeviceGroupPeerMemoryFeatures",
    /*  248 */ "vkGetDeviceGroupPeerMemoryFeaturesKHR",
    /*  249 */ "vkGetDeviceGroupPresentCapabilitiesKHR",
    /*  250 */ "vkGetDeviceGroupSurfacePresentModesKHR",
    /*  251 */ "vkGetDeviceImageMemoryRequirements",
    /*  252 */ "vkGetDeviceImageMemoryRequirementsKHR",
    /*  253 */ "vkGetDeviceImageSparseMemoryRequirements",
    /*  254 */ "vkGetDeviceImageSparseMemoryRequirementsKHR",
    /*  255 */ "vkGetDeviceMemoryCommitment",
    /*  256 */ "vkGetDeviceMemoryOpaqueCaptureAddress",
    /*  257 */ "vkGetDeviceMemoryOpaqueCaptureAddressKHR",
    /*  258 */ "vkGetDeviceProcAddr",
    /*  259 */ "vkGetDeviceQueue",
    /*  260 */ "vkGetDeviceQueue2",
    /*  261 */ "vkGetEventStatus",
    /*  262 */ "vkGetFenceStatus",
    /*  263 */ "vkGetImageMemoryRequirements",
    /*  264 */ "vkGetImageMemoryRequirements2",
    /*  265 */ "vkGetImageMemoryRequirements2KHR",
    /*  266 */ "vkGetImageSparseMemoryRequirements",
    /*  267 */ "vkGetImageSparseMemoryRequirements2",
    /*  268 */ "vkGetImageSparseMemoryRequirements2KHR",
    /*  269 */ "vkGetImageSubresourceLayout",
    /*  270 */ "vkGetInstanceProcAddr",
    /*  271 */ "vkGetPhysicalDeviceExternalBufferProperties",
    /*  272 */ "vkGetPhysicalDeviceExternalBufferPropertiesKHR",
    /*  273 */ "vkGetPhysicalDeviceExternalFenceProperties",
    /*  274 */ "vkGetPhysicalDeviceExternalFencePropertiesKHR",
    /*  275 */ "vkGetPhysicalDeviceExternalSemaphoreProperties",
    /*  276 */ "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR",
    /*  277 */ "vkGetPhysicalDeviceFeatures",
    /*  278 */ "vkGetPhysicalDeviceFeatures2",
    /*  279 */ "vkGetPhysicalDeviceFeatures2KHR",
    /*  280 */ "vkGetPhysicalDeviceFormatProperties",
    /*  281 */ "vkGetPhysicalDeviceFormatProperties2",
    /*  282 */ "vkGetPhysicalDeviceFormatProperties2KHR",
    /*  283 */ "vkGetPhysicalDeviceImageFormatProperties",
    /*  284 */ "vkGetPhysicalDeviceImageFormatProperties2",
    /*  285 */ "vkGetPhysicalDeviceImageFormatProperties2KHR",
    /*  286 */ "vkGetPhysicalDeviceMemoryProperties",
    /*  287 */ "vkGetPhysicalDeviceMemoryProperties2",
    /*  288 */ "vkGetPhysicalDeviceMemoryProperties2KHR",
    /*  289 */ "vkGetPhysicalDevicePresentRectanglesKHR",
    /*  290 */ "vkGetPhysicalDeviceProperties",
    /*  291 */ "vkGetPhysicalDeviceProperties2",
    /*  292 */ "vkGetPhysicalDeviceProperties2KHR",
    /*  293 */ "vkGetPhysicalDeviceQueueFamilyProperties",
    /*  294 */ "vkGetPhysicalDeviceQueueFamilyProperties2",
    /*  295 */ "vkGetPhysicalDeviceQueueFamilyProperties2KHR",
    /*  296 */ "vkGetPhysicalDeviceSparseImageFormatProperties",
    /*  297 */ "vkGetPhysicalDeviceSparseImageFormatProperties2",
    /*  298 */ "vkGetPhysicalDeviceSparseImageFormatProperties2KHR",
    /*  299 */ "vkGetPhysicalDeviceToolProperties",
    /*  300 */ "vkGetPhysicalDeviceToolPropertiesEXT",
    /*  301 */ "vkGetPipelineCacheData",
    /*  302 */ "vkGetPrivateData",
    /*  303 */ "vkGetPrivateDataEXT",
    /*  304 */ "vkGetQueryPoolResults",
    /*  305 */ "vkGetQueueCheckpointData2NV",
    /*  306 */ "vkGetRenderAreaGranularity",
    /*  307 */ "vkGetSemaphoreCounterValue",
    /*  308 */ "vkGetSemaphoreCounterValueKHR",
    /*  309 */ "vkGetShaderBinaryDataEXT",
    /*  310 */ "vkInvalidateMappedMemoryRanges",
    /*  311 */ "vkMapMemory",
    /*  312 */ "vkMergePipelineCaches",
    /*  313 */ "vkQueueBindSparse",
    /*  314 */ "vkQueueSubmit",
    /*  315 */ "vkQueueSubmit2",
    /*  316 */ "vkQueueSubmit2KHR",
    /*  317 */ "vkQueueWaitIdle",
    /*  318 */ "vkResetCommandBuffer",
    /*  319 */ "vkResetCommandPool",
    /*  320 */ "vkResetDescriptorPool",
    /*  321 */ "vkResetEvent",
    /*  322 */ "vkResetFences",
    /*  323 */ "vkResetQueryPool",
    /*  324 */ "vkResetQueryPoolEXT",
    /*  325 */ "vkSetEvent",
    /*  326 */ "vkSetPrivateData",
    /*  327 */ "vkSetPrivateDataEXT",
    /*  328 */ "vkSignalSemaphore",
    /*  329 */ "vkSignalSemaphoreKHR",
    /*  330 */ "vkTrimCommandPool",
    /*  331 */ "vkTrimCommandPoolKHR",
    /*  332 */ "vkUnmapMemory",
    /*  333 */ "vkUpdateDescriptorSetWithTemplate",
    /*  334 */ "vkUpdateDescriptorSetWithTemplateKHR",
    /*  335 */ "vkUpdateDescriptorSets",
    /*  336 */ "vkWaitForFences",
    /*  337 */ "vkWaitSemaphores",
    /*  338 */ "vkWaitSemaphoresKHR"
};

static uint64_t GLAD_Vulkan_ext_hashes[] = {
    /*    0 */ 0x0b55dbb0df76886c, /* VK_AMD_draw_indirect_count */
    /*    1 */ 0x8cadd6ee8baeb7b6, /* VK_EXT_buffer_device_address */
    /*    2 */ 0x405b3a7704a014a0, /* VK_EXT_extended_dynamic_state */
    /*    3 */ 0x09050069bac4e50b, /* VK_EXT_extended_dynamic_state2 */
    /*    4 */ 0xcc9a1964d5f92ead, /* VK_EXT_host_query_reset */
    /*    5 */ 0x66832604ff1fb25a, /* VK_EXT_private_data */
    /*    6 */ 0x01d57626cc2cb88b, /* VK_EXT_shader_object */
    /*    7 */ 0xa176a37fe21bf722, /* VK_EXT_tooling_info */
    /*    8 */ 0xc441ac340c33f00e, /* VK_KHR_bind_memory2 */
    /*    9 */ 0xed3998734610578e, /* VK_KHR_buffer_device_address */
    /*   10 */ 0x8037af99654ff021, /* VK_KHR_copy_commands2 */
    /*   11 */ 0x45e78547df004126, /* VK_KHR_create_renderpass2 */
    /*   12 */ 0xd0e490f381b744be, /* VK_KHR_descriptor_update_template */
    /*   13 */ 0xc6ca78c5b314bc87, /* VK_KHR_device_group */
    /*   14 */ 0x8585cbd14f1c0cac, /* VK_KHR_device_group_creation */
    /*   15 */ 0x0337556153ae8299, /* VK_KHR_draw_indirect_count */
    /*   16 */ 0xcec518255e3db5bd, /* VK_KHR_dynamic_rendering */
    /*   17 */ 0x5f78dae679457682, /* VK_KHR_external_fence_capabilities */
    /*   18 */ 0x3f3f36a8f61bdd88, /* VK_KHR_external_memory_capabilities */
    /*   19 */ 0xb7268870e382881b, /* VK_KHR_external_semaphore_capabilities */
    /*   20 */ 0x9eb7bb6c3705f946, /* VK_KHR_get_memory_requirements2 */
    /*   21 */ 0x7685eeed9cac9798, /* VK_KHR_get_physical_device_properties2 */
    /*   22 */ 0xe3c8335cc1581a67, /* VK_KHR_maintenance1 */
    /*   23 */ 0xea219cc76502a8af, /* VK_KHR_maintenance3 */
    /*   24 */ 0xa66e463f036dae4a, /* VK_KHR_maintenance4 */
    /*   25 */ 0x22004cfa79ba7177, /* VK_KHR_sampler_ycbcr_conversion */
    /*   26 */ 0xf1cfa2ea69e6ec0e, /* VK_KHR_synchronization2 */
    /*   27 */ 0x61ed378f50459bf2  /* VK_KHR_timeline_semaphore */
};

#ifdef __cplusplus
GladVulkanContext glad_vulkan_context = {};
#else
GladVulkanContext glad_vulkan_context = { 0 };
#endif

static void glad_vk_load_VK_VERSION_1_0(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           1, /* vkAllocateCommandBuffers */
           2, /* vkAllocateDescriptorSets */
           3, /* vkAllocateMemory */
           4, /* vkBeginCommandBuffer */
           5, /* vkBindBufferMemory */
           8, /* vkBindImageMemory */
          11, /* vkCmdBeginQuery */
          12, /* vkCmdBeginRenderPass */
          17, /* vkCmdBindDescriptorSets */
          18, /* vkCmdBindIndexBuffer */
          19, /* vkCmdBindPipeline */
          21, /* vkCmdBindVertexBuffers */
          24, /* vkCmdBlitImage */
          27, /* vkCmdClearAttachments */
          28, /* vkCmdClearColorImage */
          29, /* vkCmdClearDepthStencilImage */
          30, /* vkCmdCopyBuffer */
          33, /* vkCmdCopyBufferToImage */
          36, /* vkCmdCopyImage */
          39, /* vkCmdCopyImageToBuffer */
          42, /* vkCmdCopyQueryPoolResults */
          43, /* vkCmdDispatch */
          46, /* vkCmdDispatchIndirect */
          47, /* vkCmdDraw */
          48, /* vkCmdDrawIndexed */
          49, /* vkCmdDrawIndexedIndirect */
          53, /* vkCmdDrawIndirect */
          57, /* vkCmdEndQuery */
          58, /* vkCmdEndRenderPass */
          63, /* vkCmdExecuteCommands */
          64, /* vkCmdFillBuffer */
          65, /* vkCmdNextSubpass */
          68, /* vkCmdPipelineBarrier */
          71, /* vkCmdPushConstants */
          73, /* vkCmdResetEvent */
          76, /* vkCmdResetQueryPool */
          77, /* vkCmdResolveImage */
          82, /* vkCmdSetBlendConstants */
          96, /* vkCmdSetDepthBias */
          99, /* vkCmdSetDepthBounds */
         113, /* vkCmdSetEvent */
         121, /* vkCmdSetLineWidth */
         138, /* vkCmdSetScissor */
         142, /* vkCmdSetStencilCompareMask */
         145, /* vkCmdSetStencilReference */
         148, /* vkCmdSetStencilWriteMask */
         151, /* vkCmdSetViewport */
         156, /* vkCmdUpdateBuffer */
         157, /* vkCmdWaitEvents */
         161, /* vkCmdWriteTimestamp */
         164, /* vkCreateBuffer */
         165, /* vkCreateBufferView */
         166, /* vkCreateCommandPool */
         167, /* vkCreateComputePipelines */
         168, /* vkCreateDescriptorPool */
         169, /* vkCreateDescriptorSetLayout */
         172, /* vkCreateDevice */
         173, /* vkCreateEvent */
         174, /* vkCreateFence */
         175, /* vkCreateFramebuffer */
         176, /* vkCreateGraphicsPipelines */
         177, /* vkCreateImage */
         178, /* vkCreateImageView */
         179, /* vkCreateInstance */
         180, /* vkCreatePipelineCache */
         181, /* vkCreatePipelineLayout */
         184, /* vkCreateQueryPool */
         185, /* vkCreateRenderPass */
         188, /* vkCreateSampler */
         191, /* vkCreateSemaphore */
         192, /* vkCreateShaderModule */
         194, /* vkDestroyBuffer */
         195, /* vkDestroyBufferView */
         196, /* vkDestroyCommandPool */
         197, /* vkDestroyDescriptorPool */
         198, /* vkDestroyDescriptorSetLayout */
         201, /* vkDestroyDevice */
         202, /* vkDestroyEvent */
         203, /* vkDestroyFence */
         204, /* vkDestroyFramebuffer */
         205, /* vkDestroyImage */
         206, /* vkDestroyImageView */
         207, /* vkDestroyInstance */
         208, /* vkDestroyPipeline */
         209, /* vkDestroyPipelineCache */
         210, /* vkDestroyPipelineLayout */
         213, /* vkDestroyQueryPool */
         214, /* vkDestroyRenderPass */
         215, /* vkDestroySampler */
         218, /* vkDestroySemaphore */
         220, /* vkDestroyShaderModule */
         221, /* vkDeviceWaitIdle */
         222, /* vkEndCommandBuffer */
         223, /* vkEnumerateDeviceExtensionProperties */
         224, /* vkEnumerateDeviceLayerProperties */
         225, /* vkEnumerateInstanceExtensionProperties */
         226, /* vkEnumerateInstanceLayerProperties */
         230, /* vkEnumeratePhysicalDevices */
         231, /* vkFlushMappedMemoryRanges */
         232, /* vkFreeCommandBuffers */
         233, /* vkFreeDescriptorSets */
         234, /* vkFreeMemory */
         238, /* vkGetBufferMemoryRequirements */
         255, /* vkGetDeviceMemoryCommitment */
         258, /* vkGetDeviceProcAddr */
         259, /* vkGetDeviceQueue */
         261, /* vkGetEventStatus */
         262, /* vkGetFenceStatus */
         263, /* vkGetImageMemoryRequirements */
         266, /* vkGetImageSparseMemoryRequirements */
         269, /* vkGetImageSubresourceLayout */
         270, /* vkGetInstanceProcAddr */
         277, /* vkGetPhysicalDeviceFeatures */
         280, /* vkGetPhysicalDeviceFormatProperties */
         283, /* vkGetPhysicalDeviceImageFormatProperties */
         286, /* vkGetPhysicalDeviceMemoryProperties */
         290, /* vkGetPhysicalDeviceProperties */
         293, /* vkGetPhysicalDeviceQueueFamilyProperties */
         296, /* vkGetPhysicalDeviceSparseImageFormatProperties */
         301, /* vkGetPipelineCacheData */
         304, /* vkGetQueryPoolResults */
         306, /* vkGetRenderAreaGranularity */
         310, /* vkInvalidateMappedMemoryRanges */
         311, /* vkMapMemory */
         312, /* vkMergePipelineCaches */
         313, /* vkQueueBindSparse */
         314, /* vkQueueSubmit */
         317, /* vkQueueWaitIdle */
         318, /* vkResetCommandBuffer */
         319, /* vkResetCommandPool */
         320, /* vkResetDescriptorPool */
         321, /* vkResetEvent */
         322, /* vkResetFences */
         325, /* vkSetEvent */
         332, /* vkUnmapMemory */
         335, /* vkUpdateDescriptorSets */
         336  /* vkWaitForFences */
    };
    uint32_t i;
    if(!context->VERSION_1_0) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_VERSION_1_1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           6, /* vkBindBufferMemory2 */
           9, /* vkBindImageMemory2 */
          44, /* vkCmdDispatchBase */
         111, /* vkCmdSetDeviceMask */
         170, /* vkCreateDescriptorUpdateTemplate */
         189, /* vkCreateSamplerYcbcrConversion */
         199, /* vkDestroyDescriptorUpdateTemplate */
         216, /* vkDestroySamplerYcbcrConversion */
         227, /* vkEnumerateInstanceVersion */
         228, /* vkEnumeratePhysicalDeviceGroups */
         239, /* vkGetBufferMemoryRequirements2 */
         243, /* vkGetDescriptorSetLayoutSupport */
         247, /* vkGetDeviceGroupPeerMemoryFeatures */
         260, /* vkGetDeviceQueue2 */
         264, /* vkGetImageMemoryRequirements2 */
         267, /* vkGetImageSparseMemoryRequirements2 */
         271, /* vkGetPhysicalDeviceExternalBufferProperties */
         273, /* vkGetPhysicalDeviceExternalFenceProperties */
         275, /* vkGetPhysicalDeviceExternalSemaphoreProperties */
         278, /* vkGetPhysicalDeviceFeatures2 */
         281, /* vkGetPhysicalDeviceFormatProperties2 */
         284, /* vkGetPhysicalDeviceImageFormatProperties2 */
         287, /* vkGetPhysicalDeviceMemoryProperties2 */
         291, /* vkGetPhysicalDeviceProperties2 */
         294, /* vkGetPhysicalDeviceQueueFamilyProperties2 */
         297, /* vkGetPhysicalDeviceSparseImageFormatProperties2 */
         330, /* vkTrimCommandPool */
         333  /* vkUpdateDescriptorSetWithTemplate */
    };
    uint32_t i;
    if(!context->VERSION_1_1) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_VERSION_1_2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          13, /* vkCmdBeginRenderPass2 */
          50, /* vkCmdDrawIndexedIndirectCount */
          54, /* vkCmdDrawIndirectCount */
          59, /* vkCmdEndRenderPass2 */
          66, /* vkCmdNextSubpass2 */
         186, /* vkCreateRenderPass2 */
         235, /* vkGetBufferDeviceAddress */
         241, /* vkGetBufferOpaqueCaptureAddress */
         256, /* vkGetDeviceMemoryOpaqueCaptureAddress */
         307, /* vkGetSemaphoreCounterValue */
         323, /* vkResetQueryPool */
         328, /* vkSignalSemaphore */
         337  /* vkWaitSemaphores */
    };
    uint32_t i;
    if(!context->VERSION_1_2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_VERSION_1_3(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          15, /* vkCmdBeginRendering */
          22, /* vkCmdBindVertexBuffers2 */
          25, /* vkCmdBlitImage2 */
          31, /* vkCmdCopyBuffer2 */
          34, /* vkCmdCopyBufferToImage2 */
          37, /* vkCmdCopyImage2 */
          40, /* vkCmdCopyImageToBuffer2 */
          61, /* vkCmdEndRendering */
          69, /* vkCmdPipelineBarrier2 */
          74, /* vkCmdResetEvent2 */
          78, /* vkCmdResolveImage2 */
          94, /* vkCmdSetCullMode */
          97, /* vkCmdSetDepthBiasEnable */
         100, /* vkCmdSetDepthBoundsTestEnable */
         105, /* vkCmdSetDepthCompareOp */
         107, /* vkCmdSetDepthTestEnable */
         109, /* vkCmdSetDepthWriteEnable */
         114, /* vkCmdSetEvent2 */
         117, /* vkCmdSetFrontFace */
         126, /* vkCmdSetPrimitiveRestartEnable */
         128, /* vkCmdSetPrimitiveTopology */
         133, /* vkCmdSetRasterizerDiscardEnable */
         139, /* vkCmdSetScissorWithCount */
         143, /* vkCmdSetStencilOp */
         146, /* vkCmdSetStencilTestEnable */
         154, /* vkCmdSetViewportWithCount */
         158, /* vkCmdWaitEvents2 */
         162, /* vkCmdWriteTimestamp2 */
         182, /* vkCreatePrivateDataSlot */
         211, /* vkDestroyPrivateDataSlot */
         245, /* vkGetDeviceBufferMemoryRequirements */
         251, /* vkGetDeviceImageMemoryRequirements */
         253, /* vkGetDeviceImageSparseMemoryRequirements */
         299, /* vkGetPhysicalDeviceToolProperties */
         302, /* vkGetPrivateData */
         315, /* vkQueueSubmit2 */
         326  /* vkSetPrivateData */
    };
    uint32_t i;
    if(!context->VERSION_1_3) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_AMD_draw_indirect_count(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          51, /* vkCmdDrawIndexedIndirectCountAMD */
          55  /* vkCmdDrawIndirectCountAMD */
    };
    uint32_t i;
    if(!context->AMD_draw_indirect_count) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_buffer_device_address(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         236  /* vkGetBufferDeviceAddressEXT */
    };
    uint32_t i;
    if(!context->EXT_buffer_device_address) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_extended_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          23, /* vkCmdBindVertexBuffers2EXT */
          95, /* vkCmdSetCullModeEXT */
         101, /* vkCmdSetDepthBoundsTestEnableEXT */
         106, /* vkCmdSetDepthCompareOpEXT */
         108, /* vkCmdSetDepthTestEnableEXT */
         110, /* vkCmdSetDepthWriteEnableEXT */
         118, /* vkCmdSetFrontFaceEXT */
         129, /* vkCmdSetPrimitiveTopologyEXT */
         140, /* vkCmdSetScissorWithCountEXT */
         144, /* vkCmdSetStencilOpEXT */
         147, /* vkCmdSetStencilTestEnableEXT */
         155  /* vkCmdSetViewportWithCountEXT */
    };
    uint32_t i;
    if(!context->EXT_extended_dynamic_state) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_extended_dynamic_state2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          98, /* vkCmdSetDepthBiasEnableEXT */
         122, /* vkCmdSetLogicOpEXT */
         124, /* vkCmdSetPatchControlPointsEXT */
         127, /* vkCmdSetPrimitiveRestartEnableEXT */
         134  /* vkCmdSetRasterizerDiscardEnableEXT */
    };
    uint32_t i;
    if(!context->EXT_extended_dynamic_state2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_host_query_reset(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         324  /* vkResetQueryPoolEXT */
    };
    uint32_t i;
    if(!context->EXT_host_query_reset) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_private_data(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         183, /* vkCreatePrivateDataSlotEXT */
         212, /* vkDestroyPrivateDataSlotEXT */
         303, /* vkGetPrivateDataEXT */
         327  /* vkSetPrivateDataEXT */
    };
    uint32_t i;
    if(!context->EXT_private_data) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_shader_object(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          20, /* vkCmdBindShadersEXT */
          23, /* vkCmdBindVertexBuffers2EXT */
          80, /* vkCmdSetAlphaToCoverageEnableEXT */
          81, /* vkCmdSetAlphaToOneEnableEXT */
          83, /* vkCmdSetColorBlendAdvancedEXT */
          84, /* vkCmdSetColorBlendEnableEXT */
          85, /* vkCmdSetColorBlendEquationEXT */
          86, /* vkCmdSetColorWriteMaskEXT */
          87, /* vkCmdSetConservativeRasterizationModeEXT */
          88, /* vkCmdSetCoverageModulationModeNV */
          89, /* vkCmdSetCoverageModulationTableEnableNV */
          90, /* vkCmdSetCoverageModulationTableNV */
          91, /* vkCmdSetCoverageReductionModeNV */
          92, /* vkCmdSetCoverageToColorEnableNV */
          93, /* vkCmdSetCoverageToColorLocationNV */
          95, /* vkCmdSetCullModeEXT */
          98, /* vkCmdSetDepthBiasEnableEXT */
         101, /* vkCmdSetDepthBoundsTestEnableEXT */
         102, /* vkCmdSetDepthClampEnableEXT */
         103, /* vkCmdSetDepthClipEnableEXT */
         104, /* vkCmdSetDepthClipNegativeOneToOneEXT */
         106, /* vkCmdSetDepthCompareOpEXT */
         108, /* vkCmdSetDepthTestEnableEXT */
         110, /* vkCmdSetDepthWriteEnableEXT */
         116, /* vkCmdSetExtraPrimitiveOverestimationSizeEXT */
         118, /* vkCmdSetFrontFaceEXT */
         119, /* vkCmdSetLineRasterizationModeEXT */
         120, /* vkCmdSetLineStippleEnableEXT */
         122, /* vkCmdSetLogicOpEXT */
         123, /* vkCmdSetLogicOpEnableEXT */
         124, /* vkCmdSetPatchControlPointsEXT */
         125, /* vkCmdSetPolygonModeEXT */
         127, /* vkCmdSetPrimitiveRestartEnableEXT */
         129, /* vkCmdSetPrimitiveTopologyEXT */
         130, /* vkCmdSetProvokingVertexModeEXT */
         131, /* vkCmdSetRasterizationSamplesEXT */
         132, /* vkCmdSetRasterizationStreamEXT */
         134, /* vkCmdSetRasterizerDiscardEnableEXT */
         135, /* vkCmdSetRepresentativeFragmentTestEnableNV */
         136, /* vkCmdSetSampleLocationsEnableEXT */
         137, /* vkCmdSetSampleMaskEXT */
         140, /* vkCmdSetScissorWithCountEXT */
         141, /* vkCmdSetShadingRateImageEnableNV */
         144, /* vkCmdSetStencilOpEXT */
         147, /* vkCmdSetStencilTestEnableEXT */
         149, /* vkCmdSetTessellationDomainOriginEXT */
         150, /* vkCmdSetVertexInputEXT */
         152, /* vkCmdSetViewportSwizzleNV */
         153, /* vkCmdSetViewportWScalingEnableNV */
         155, /* vkCmdSetViewportWithCountEXT */
         193, /* vkCreateShadersEXT */
         219, /* vkDestroyShaderEXT */
         309  /* vkGetShaderBinaryDataEXT */
    };
    uint32_t i;
    if(!context->EXT_shader_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_tooling_info(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         300  /* vkGetPhysicalDeviceToolPropertiesEXT */
    };
    uint32_t i;
    if(!context->EXT_tooling_info) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_bind_memory2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           7, /* vkBindBufferMemory2KHR */
          10  /* vkBindImageMemory2KHR */
    };
    uint32_t i;
    if(!context->KHR_bind_memory2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_buffer_device_address(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         237, /* vkGetBufferDeviceAddressKHR */
         242, /* vkGetBufferOpaqueCaptureAddressKHR */
         257  /* vkGetDeviceMemoryOpaqueCaptureAddressKHR */
    };
    uint32_t i;
    if(!context->KHR_buffer_device_address) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_copy_commands2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          26, /* vkCmdBlitImage2KHR */
          32, /* vkCmdCopyBuffer2KHR */
          35, /* vkCmdCopyBufferToImage2KHR */
          38, /* vkCmdCopyImage2KHR */
          41, /* vkCmdCopyImageToBuffer2KHR */
          79  /* vkCmdResolveImage2KHR */
    };
    uint32_t i;
    if(!context->KHR_copy_commands2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_create_renderpass2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          14, /* vkCmdBeginRenderPass2KHR */
          60, /* vkCmdEndRenderPass2KHR */
          67, /* vkCmdNextSubpass2KHR */
         187  /* vkCreateRenderPass2KHR */
    };
    uint32_t i;
    if(!context->KHR_create_renderpass2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_descriptor_update_template(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          72, /* vkCmdPushDescriptorSetWithTemplateKHR */
         171, /* vkCreateDescriptorUpdateTemplateKHR */
         200, /* vkDestroyDescriptorUpdateTemplateKHR */
         334  /* vkUpdateDescriptorSetWithTemplateKHR */
    };
    uint32_t i;
    if(!context->KHR_descriptor_update_template) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_device_group(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           0, /* vkAcquireNextImage2KHR */
          45, /* vkCmdDispatchBaseKHR */
         112, /* vkCmdSetDeviceMaskKHR */
         248, /* vkGetDeviceGroupPeerMemoryFeaturesKHR */
         249, /* vkGetDeviceGroupPresentCapabilitiesKHR */
         250, /* vkGetDeviceGroupSurfacePresentModesKHR */
         289  /* vkGetPhysicalDevicePresentRectanglesKHR */
    };
    uint32_t i;
    if(!context->KHR_device_group) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_device_group_creation(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         229  /* vkEnumeratePhysicalDeviceGroupsKHR */
    };
    uint32_t i;
    if(!context->KHR_device_group_creation) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_draw_indirect_count(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          52, /* vkCmdDrawIndexedIndirectCountKHR */
          56  /* vkCmdDrawIndirectCountKHR */
    };
    uint32_t i;
    if(!context->KHR_draw_indirect_count) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_dynamic_rendering(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          16, /* vkCmdBeginRenderingKHR */
          62  /* vkCmdEndRenderingKHR */
    };
    uint32_t i;
    if(!context->KHR_dynamic_rendering) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_external_fence_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         274  /* vkGetPhysicalDeviceExternalFencePropertiesKHR */
    };
    uint32_t i;
    if(!context->KHR_external_fence_capabilities) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_external_memory_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         272  /* vkGetPhysicalDeviceExternalBufferPropertiesKHR */
    };
    uint32_t i;
    if(!context->KHR_external_memory_capabilities) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_external_semaphore_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         276  /* vkGetPhysicalDeviceExternalSemaphorePropertiesKHR */
    };
    uint32_t i;
    if(!context->KHR_external_semaphore_capabilities) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_get_memory_requirements2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         240, /* vkGetBufferMemoryRequirements2KHR */
         265, /* vkGetImageMemoryRequirements2KHR */
         268  /* vkGetImageSparseMemoryRequirements2KHR */
    };
    uint32_t i;
    if(!context->KHR_get_memory_requirements2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_get_physical_device_properties2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         279, /* vkGetPhysicalDeviceFeatures2KHR */
         282, /* vkGetPhysicalDeviceFormatProperties2KHR */
         285, /* vkGetPhysicalDeviceImageFormatProperties2KHR */
         288, /* vkGetPhysicalDeviceMemoryProperties2KHR */
         292, /* vkGetPhysicalDeviceProperties2KHR */
         295, /* vkGetPhysicalDeviceQueueFamilyProperties2KHR */
         298  /* vkGetPhysicalDeviceSparseImageFormatProperties2KHR */
    };
    uint32_t i;
    if(!context->KHR_get_physical_device_properties2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         331  /* vkTrimCommandPoolKHR */
    };
    uint32_t i;
    if(!context->KHR_maintenance1) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_maintenance3(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         244  /* vkGetDescriptorSetLayoutSupportKHR */
    };
    uint32_t i;
    if(!context->KHR_maintenance3) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_maintenance4(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         246, /* vkGetDeviceBufferMemoryRequirementsKHR */
         252, /* vkGetDeviceImageMemoryRequirementsKHR */
         254  /* vkGetDeviceImageSparseMemoryRequirementsKHR */
    };
    uint32_t i;
    if(!context->KHR_maintenance4) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_sampler_ycbcr_conversion(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         190, /* vkCreateSamplerYcbcrConversionKHR */
         217  /* vkDestroySamplerYcbcrConversionKHR */
    };
    uint32_t i;
    if(!context->KHR_sampler_ycbcr_conversion) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_synchronization2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          70, /* vkCmdPipelineBarrier2KHR */
          75, /* vkCmdResetEvent2KHR */
         115, /* vkCmdSetEvent2KHR */
         159, /* vkCmdWaitEvents2KHR */
         160, /* vkCmdWriteBufferMarker2AMD */
         163, /* vkCmdWriteTimestamp2KHR */
         305, /* vkGetQueueCheckpointData2NV */
         316  /* vkQueueSubmit2KHR */
    };
    uint32_t i;
    if(!context->KHR_synchronization2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_timeline_semaphore(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         308, /* vkGetSemaphoreCounterValueKHR */
         329, /* vkSignalSemaphoreKHR */
         338  /* vkWaitSemaphoresKHR */
    };
    uint32_t i;
    if(!context->KHR_timeline_semaphore) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_resolve_aliases(GladVulkanContext *context) {
    static const GladAliasPair_t s_aliases[] = {
        {    6,    7 }, /* vkBindBufferMemory2 and vkBindBufferMemory2KHR */
        {    7,    6 }, /* vkBindBufferMemory2KHR and vkBindBufferMemory2 */
        {    9,   10 }, /* vkBindImageMemory2 and vkBindImageMemory2KHR */
        {   10,    9 }, /* vkBindImageMemory2KHR and vkBindImageMemory2 */
        {   15,   16 }, /* vkCmdBeginRendering and vkCmdBeginRenderingKHR */
        {   16,   15 }, /* vkCmdBeginRenderingKHR and vkCmdBeginRendering */
        {   13,   14 }, /* vkCmdBeginRenderPass2 and vkCmdBeginRenderPass2KHR */
        {   14,   13 }, /* vkCmdBeginRenderPass2KHR and vkCmdBeginRenderPass2 */
        {   22,   23 }, /* vkCmdBindVertexBuffers2 and vkCmdBindVertexBuffers2EXT */
        {   23,   22 }, /* vkCmdBindVertexBuffers2EXT and vkCmdBindVertexBuffers2 */
        {   25,   26 }, /* vkCmdBlitImage2 and vkCmdBlitImage2KHR */
        {   26,   25 }, /* vkCmdBlitImage2KHR and vkCmdBlitImage2 */
        {   31,   32 }, /* vkCmdCopyBuffer2 and vkCmdCopyBuffer2KHR */
        {   32,   31 }, /* vkCmdCopyBuffer2KHR and vkCmdCopyBuffer2 */
        {   34,   35 }, /* vkCmdCopyBufferToImage2 and vkCmdCopyBufferToImage2KHR */
        {   35,   34 }, /* vkCmdCopyBufferToImage2KHR and vkCmdCopyBufferToImage2 */
        {   37,   38 }, /* vkCmdCopyImage2 and vkCmdCopyImage2KHR */
        {   38,   37 }, /* vkCmdCopyImage2KHR and vkCmdCopyImage2 */
        {   40,   41 }, /* vkCmdCopyImageToBuffer2 and vkCmdCopyImageToBuffer2KHR */
        {   41,   40 }, /* vkCmdCopyImageToBuffer2KHR and vkCmdCopyImageToBuffer2 */
        {   44,   45 }, /* vkCmdDispatchBase and vkCmdDispatchBaseKHR */
        {   45,   44 }, /* vkCmdDispatchBaseKHR and vkCmdDispatchBase */
        {   50,   51 }, /* vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountAMD */
        {   50,   52 }, /* vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountKHR */
        {   51,   50 }, /* vkCmdDrawIndexedIndirectCountAMD and vkCmdDrawIndexedIndirectCount */
        {   51,   52 }, /* vkCmdDrawIndexedIndirectCountAMD and vkCmdDrawIndexedIndirectCountKHR */
        {   52,   50 }, /* vkCmdDrawIndexedIndirectCountKHR and vkCmdDrawIndexedIndirectCount */
        {   52,   51 }, /* vkCmdDrawIndexedIndirectCountKHR and vkCmdDrawIndexedIndirectCountAMD */
        {   54,   55 }, /* vkCmdDrawIndirectCount and vkCmdDrawIndirectCountAMD */
        {   54,   56 }, /* vkCmdDrawIndirectCount and vkCmdDrawIndirectCountKHR */
        {   55,   54 }, /* vkCmdDrawIndirectCountAMD and vkCmdDrawIndirectCount */
        {   55,   56 }, /* vkCmdDrawIndirectCountAMD and vkCmdDrawIndirectCountKHR */
        {   56,   54 }, /* vkCmdDrawIndirectCountKHR and vkCmdDrawIndirectCount */
        {   56,   55 }, /* vkCmdDrawIndirectCountKHR and vkCmdDrawIndirectCountAMD */
        {   61,   62 }, /* vkCmdEndRendering and vkCmdEndRenderingKHR */
        {   62,   61 }, /* vkCmdEndRenderingKHR and vkCmdEndRendering */
        {   59,   60 }, /* vkCmdEndRenderPass2 and vkCmdEndRenderPass2KHR */
        {   60,   59 }, /* vkCmdEndRenderPass2KHR and vkCmdEndRenderPass2 */
        {   66,   67 }, /* vkCmdNextSubpass2 and vkCmdNextSubpass2KHR */
        {   67,   66 }, /* vkCmdNextSubpass2KHR and vkCmdNextSubpass2 */
        {   69,   70 }, /* vkCmdPipelineBarrier2 and vkCmdPipelineBarrier2KHR */
        {   70,   69 }, /* vkCmdPipelineBarrier2KHR and vkCmdPipelineBarrier2 */
        {   74,   75 }, /* vkCmdResetEvent2 and vkCmdResetEvent2KHR */
        {   75,   74 }, /* vkCmdResetEvent2KHR and vkCmdResetEvent2 */
        {   78,   79 }, /* vkCmdResolveImage2 and vkCmdResolveImage2KHR */
        {   79,   78 }, /* vkCmdResolveImage2KHR and vkCmdResolveImage2 */
        {   94,   95 }, /* vkCmdSetCullMode and vkCmdSetCullModeEXT */
        {   95,   94 }, /* vkCmdSetCullModeEXT and vkCmdSetCullMode */
        {   97,   98 }, /* vkCmdSetDepthBiasEnable and vkCmdSetDepthBiasEnableEXT */
        {   98,   97 }, /* vkCmdSetDepthBiasEnableEXT and vkCmdSetDepthBiasEnable */
        {  100,  101 }, /* vkCmdSetDepthBoundsTestEnable and vkCmdSetDepthBoundsTestEnableEXT */
        {  101,  100 }, /* vkCmdSetDepthBoundsTestEnableEXT and vkCmdSetDepthBoundsTestEnable */
        {  105,  106 }, /* vkCmdSetDepthCompareOp and vkCmdSetDepthCompareOpEXT */
        {  106,  105 }, /* vkCmdSetDepthCompareOpEXT and vkCmdSetDepthCompareOp */
        {  107,  108 }, /* vkCmdSetDepthTestEnable and vkCmdSetDepthTestEnableEXT */
        {  108,  107 }, /* vkCmdSetDepthTestEnableEXT and vkCmdSetDepthTestEnable */
        {  109,  110 }, /* vkCmdSetDepthWriteEnable and vkCmdSetDepthWriteEnableEXT */
        {  110,  109 }, /* vkCmdSetDepthWriteEnableEXT and vkCmdSetDepthWriteEnable */
        {  111,  112 }, /* vkCmdSetDeviceMask and vkCmdSetDeviceMaskKHR */
        {  112,  111 }, /* vkCmdSetDeviceMaskKHR and vkCmdSetDeviceMask */
        {  114,  115 }, /* vkCmdSetEvent2 and vkCmdSetEvent2KHR */
        {  115,  114 }, /* vkCmdSetEvent2KHR and vkCmdSetEvent2 */
        {  117,  118 }, /* vkCmdSetFrontFace and vkCmdSetFrontFaceEXT */
        {  118,  117 }, /* vkCmdSetFrontFaceEXT and vkCmdSetFrontFace */
        {  126,  127 }, /* vkCmdSetPrimitiveRestartEnable and vkCmdSetPrimitiveRestartEnableEXT */
        {  127,  126 }, /* vkCmdSetPrimitiveRestartEnableEXT and vkCmdSetPrimitiveRestartEnable */
        {  128,  129 }, /* vkCmdSetPrimitiveTopology and vkCmdSetPrimitiveTopologyEXT */
        {  129,  128 }, /* vkCmdSetPrimitiveTopologyEXT and vkCmdSetPrimitiveTopology */
        {  133,  134 }, /* vkCmdSetRasterizerDiscardEnable and vkCmdSetRasterizerDiscardEnableEXT */
        {  134,  133 }, /* vkCmdSetRasterizerDiscardEnableEXT and vkCmdSetRasterizerDiscardEnable */
        {  139,  140 }, /* vkCmdSetScissorWithCount and vkCmdSetScissorWithCountEXT */
        {  140,  139 }, /* vkCmdSetScissorWithCountEXT and vkCmdSetScissorWithCount */
        {  143,  144 }, /* vkCmdSetStencilOp and vkCmdSetStencilOpEXT */
        {  144,  143 }, /* vkCmdSetStencilOpEXT and vkCmdSetStencilOp */
        {  146,  147 }, /* vkCmdSetStencilTestEnable and vkCmdSetStencilTestEnableEXT */
        {  147,  146 }, /* vkCmdSetStencilTestEnableEXT and vkCmdSetStencilTestEnable */
        {  154,  155 }, /* vkCmdSetViewportWithCount and vkCmdSetViewportWithCountEXT */
        {  155,  154 }, /* vkCmdSetViewportWithCountEXT and vkCmdSetViewportWithCount */
        {  158,  159 }, /* vkCmdWaitEvents2 and vkCmdWaitEvents2KHR */
        {  159,  158 }, /* vkCmdWaitEvents2KHR and vkCmdWaitEvents2 */
        {  162,  163 }, /* vkCmdWriteTimestamp2 and vkCmdWriteTimestamp2KHR */
        {  163,  162 }, /* vkCmdWriteTimestamp2KHR and vkCmdWriteTimestamp2 */
        {  170,  171 }, /* vkCreateDescriptorUpdateTemplate and vkCreateDescriptorUpdateTemplateKHR */
        {  171,  170 }, /* vkCreateDescriptorUpdateTemplateKHR and vkCreateDescriptorUpdateTemplate */
        {  182,  183 }, /* vkCreatePrivateDataSlot and vkCreatePrivateDataSlotEXT */
        {  183,  182 }, /* vkCreatePrivateDataSlotEXT and vkCreatePrivateDataSlot */
        {  186,  187 }, /* vkCreateRenderPass2 and vkCreateRenderPass2KHR */
        {  187,  186 }, /* vkCreateRenderPass2KHR and vkCreateRenderPass2 */
        {  189,  190 }, /* vkCreateSamplerYcbcrConversion and vkCreateSamplerYcbcrConversionKHR */
        {  190,  189 }, /* vkCreateSamplerYcbcrConversionKHR and vkCreateSamplerYcbcrConversion */
        {  199,  200 }, /* vkDestroyDescriptorUpdateTemplate and vkDestroyDescriptorUpdateTemplateKHR */
        {  200,  199 }, /* vkDestroyDescriptorUpdateTemplateKHR and vkDestroyDescriptorUpdateTemplate */
        {  211,  212 }, /* vkDestroyPrivateDataSlot and vkDestroyPrivateDataSlotEXT */
        {  212,  211 }, /* vkDestroyPrivateDataSlotEXT and vkDestroyPrivateDataSlot */
        {  216,  217 }, /* vkDestroySamplerYcbcrConversion and vkDestroySamplerYcbcrConversionKHR */
        {  217,  216 }, /* vkDestroySamplerYcbcrConversionKHR and vkDestroySamplerYcbcrConversion */
        {  228,  229 }, /* vkEnumeratePhysicalDeviceGroups and vkEnumeratePhysicalDeviceGroupsKHR */
        {  229,  228 }, /* vkEnumeratePhysicalDeviceGroupsKHR and vkEnumeratePhysicalDeviceGroups */
        {  235,  236 }, /* vkGetBufferDeviceAddress and vkGetBufferDeviceAddressEXT */
        {  235,  237 }, /* vkGetBufferDeviceAddress and vkGetBufferDeviceAddressKHR */
        {  236,  235 }, /* vkGetBufferDeviceAddressEXT and vkGetBufferDeviceAddress */
        {  236,  237 }, /* vkGetBufferDeviceAddressEXT and vkGetBufferDeviceAddressKHR */
        {  237,  235 }, /* vkGetBufferDeviceAddressKHR and vkGetBufferDeviceAddress */
        {  237,  236 }, /* vkGetBufferDeviceAddressKHR and vkGetBufferDeviceAddressEXT */
        {  239,  240 }, /* vkGetBufferMemoryRequirements2 and vkGetBufferMemoryRequirements2KHR */
        {  240,  239 }, /* vkGetBufferMemoryRequirements2KHR and vkGetBufferMemoryRequirements2 */
        {  241,  242 }, /* vkGetBufferOpaqueCaptureAddress and vkGetBufferOpaqueCaptureAddressKHR */
        {  242,  241 }, /* vkGetBufferOpaqueCaptureAddressKHR and vkGetBufferOpaqueCaptureAddress */
        {  243,  244 }, /* vkGetDescriptorSetLayoutSupport and vkGetDescriptorSetLayoutSupportKHR */
        {  244,  243 }, /* vkGetDescriptorSetLayoutSupportKHR and vkGetDescriptorSetLayoutSupport */
        {  245,  246 }, /* vkGetDeviceBufferMemoryRequirements and vkGetDeviceBufferMemoryRequirementsKHR */
        {  246,  245 }, /* vkGetDeviceBufferMemoryRequirementsKHR and vkGetDeviceBufferMemoryRequirements */
        {  247,  248 }, /* vkGetDeviceGroupPeerMemoryFeatures and vkGetDeviceGroupPeerMemoryFeaturesKHR */
        {  248,  247 }, /* vkGetDeviceGroupPeerMemoryFeaturesKHR and vkGetDeviceGroupPeerMemoryFeatures */
        {  251,  252 }, /* vkGetDeviceImageMemoryRequirements and vkGetDeviceImageMemoryRequirementsKHR */
        {  252,  251 }, /* vkGetDeviceImageMemoryRequirementsKHR and vkGetDeviceImageMemoryRequirements */
        {  253,  254 }, /* vkGetDeviceImageSparseMemoryRequirements and vkGetDeviceImageSparseMemoryRequirementsKHR */
        {  254,  253 }, /* vkGetDeviceImageSparseMemoryRequirementsKHR and vkGetDeviceImageSparseMemoryRequirements */
        {  256,  257 }, /* vkGetDeviceMemoryOpaqueCaptureAddress and vkGetDeviceMemoryOpaqueCaptureAddressKHR */
        {  257,  256 }, /* vkGetDeviceMemoryOpaqueCaptureAddressKHR and vkGetDeviceMemoryOpaqueCaptureAddress */
        {  264,  265 }, /* vkGetImageMemoryRequirements2 and vkGetImageMemoryRequirements2KHR */
        {  265,  264 }, /* vkGetImageMemoryRequirements2KHR and vkGetImageMemoryRequirements2 */
        {  267,  268 }, /* vkGetImageSparseMemoryRequirements2 and vkGetImageSparseMemoryRequirements2KHR */
        {  268,  267 }, /* vkGetImageSparseMemoryRequirements2KHR and vkGetImageSparseMemoryRequirements2 */
        {  271,  272 }, /* vkGetPhysicalDeviceExternalBufferProperties and vkGetPhysicalDeviceExternalBufferPropertiesKHR */
        {  272,  271 }, /* vkGetPhysicalDeviceExternalBufferPropertiesKHR and vkGetPhysicalDeviceExternalBufferProperties */
        {  273,  274 }, /* vkGetPhysicalDeviceExternalFenceProperties and vkGetPhysicalDeviceExternalFencePropertiesKHR */
        {  274,  273 }, /* vkGetPhysicalDeviceExternalFencePropertiesKHR and vkGetPhysicalDeviceExternalFenceProperties */
        {  275,  276 }, /* vkGetPhysicalDeviceExternalSemaphoreProperties and vkGetPhysicalDeviceExternalSemaphorePropertiesKHR */
        {  276,  275 }, /* vkGetPhysicalDeviceExternalSemaphorePropertiesKHR and vkGetPhysicalDeviceExternalSemaphoreProperties */
        {  278,  279 }, /* vkGetPhysicalDeviceFeatures2 and vkGetPhysicalDeviceFeatures2KHR */
        {  279,  278 }, /* vkGetPhysicalDeviceFeatures2KHR and vkGetPhysicalDeviceFeatures2 */
        {  281,  282 }, /* vkGetPhysicalDeviceFormatProperties2 and vkGetPhysicalDeviceFormatProperties2KHR */
        {  282,  281 }, /* vkGetPhysicalDeviceFormatProperties2KHR and vkGetPhysicalDeviceFormatProperties2 */
        {  284,  285 }, /* vkGetPhysicalDeviceImageFormatProperties2 and vkGetPhysicalDeviceImageFormatProperties2KHR */
        {  285,  284 }, /* vkGetPhysicalDeviceImageFormatProperties2KHR and vkGetPhysicalDeviceImageFormatProperties2 */
        {  287,  288 }, /* vkGetPhysicalDeviceMemoryProperties2 and vkGetPhysicalDeviceMemoryProperties2KHR */
        {  288,  287 }, /* vkGetPhysicalDeviceMemoryProperties2KHR and vkGetPhysicalDeviceMemoryProperties2 */
        {  291,  292 }, /* vkGetPhysicalDeviceProperties2 and vkGetPhysicalDeviceProperties2KHR */
        {  292,  291 }, /* vkGetPhysicalDeviceProperties2KHR and vkGetPhysicalDeviceProperties2 */
        {  294,  295 }, /* vkGetPhysicalDeviceQueueFamilyProperties2 and vkGetPhysicalDeviceQueueFamilyProperties2KHR */
        {  295,  294 }, /* vkGetPhysicalDeviceQueueFamilyProperties2KHR and vkGetPhysicalDeviceQueueFamilyProperties2 */
        {  297,  298 }, /* vkGetPhysicalDeviceSparseImageFormatProperties2 and vkGetPhysicalDeviceSparseImageFormatProperties2KHR */
        {  298,  297 }, /* vkGetPhysicalDeviceSparseImageFormatProperties2KHR and vkGetPhysicalDeviceSparseImageFormatProperties2 */
        {  299,  300 }, /* vkGetPhysicalDeviceToolProperties and vkGetPhysicalDeviceToolPropertiesEXT */
        {  300,  299 }, /* vkGetPhysicalDeviceToolPropertiesEXT and vkGetPhysicalDeviceToolProperties */
        {  302,  303 }, /* vkGetPrivateData and vkGetPrivateDataEXT */
        {  303,  302 }, /* vkGetPrivateDataEXT and vkGetPrivateData */
        {  307,  308 }, /* vkGetSemaphoreCounterValue and vkGetSemaphoreCounterValueKHR */
        {  308,  307 }, /* vkGetSemaphoreCounterValueKHR and vkGetSemaphoreCounterValue */
        {  315,  316 }, /* vkQueueSubmit2 and vkQueueSubmit2KHR */
        {  316,  315 }, /* vkQueueSubmit2KHR and vkQueueSubmit2 */
        {  323,  324 }, /* vkResetQueryPool and vkResetQueryPoolEXT */
        {  324,  323 }, /* vkResetQueryPoolEXT and vkResetQueryPool */
        {  326,  327 }, /* vkSetPrivateData and vkSetPrivateDataEXT */
        {  327,  326 }, /* vkSetPrivateDataEXT and vkSetPrivateData */
        {  328,  329 }, /* vkSignalSemaphore and vkSignalSemaphoreKHR */
        {  329,  328 }, /* vkSignalSemaphoreKHR and vkSignalSemaphore */
        {  330,  331 }, /* vkTrimCommandPool and vkTrimCommandPoolKHR */
        {  331,  330 }, /* vkTrimCommandPoolKHR and vkTrimCommandPool */
        {  333,  334 }, /* vkUpdateDescriptorSetWithTemplate and vkUpdateDescriptorSetWithTemplateKHR */
        {  334,  333 }, /* vkUpdateDescriptorSetWithTemplateKHR and vkUpdateDescriptorSetWithTemplate */
        {  337,  338 }, /* vkWaitSemaphores and vkWaitSemaphoresKHR */
        {  338,  337 }, /* vkWaitSemaphoresKHR and vkWaitSemaphores */
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

static int glad_vk_has_extension(uint64_t name, uint32_t extension_count, uint64_t *extensions) {
    return glad_hash_search(extensions, extension_count, name);
}

static GLADapiproc glad_vk_get_proc_from_userptr(void *userptr, const char* name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_vk_find_extensions_vulkan(GladVulkanContext *context, VkPhysicalDevice physical_device) {
    uint32_t extension_count = 0;
    uint32_t i;
    uint64_t *extensions = NULL;
    if (!glad_vk_get_extensions(context, physical_device, &extension_count, &extensions)) return 0;

    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_Vulkan_ext_hashes); ++i)
        context->extArray[i] = glad_vk_has_extension(GLAD_Vulkan_ext_hashes[i], extension_count, extensions);

    GLAD_UNUSED(glad_vk_has_extension);

    glad_vk_free_extensions(extensions);
    return 1;
}

static int glad_vk_find_core_vulkan(GladVulkanContext *context, VkPhysicalDevice physical_device) {
    int major = 1;
    int minor = 0;

#ifdef VK_VERSION_1_1
    if (context->EnumerateInstanceVersion != NULL) {
        uint32_t version;
        VkResult result;

        result = context->EnumerateInstanceVersion(&version);
        if (result == VK_SUCCESS) {
            major = (int) VK_VERSION_MAJOR(version);
            minor = (int) VK_VERSION_MINOR(version);
        }
    }
#endif

    if (physical_device != NULL && context->GetPhysicalDeviceProperties != NULL) {
        VkPhysicalDeviceProperties properties;
        context->GetPhysicalDeviceProperties(physical_device, &properties);

        major = (int) VK_VERSION_MAJOR(properties.apiVersion);
        minor = (int) VK_VERSION_MINOR(properties.apiVersion);
    }

    context->VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
    context->VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
    context->VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
    context->VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;

    return GLAD_MAKE_VERSION(major, minor);
}

GLAD_NO_INLINE int gladLoadVulkanContextUserPtr(GladVulkanContext *context, VkPhysicalDevice physical_device, GLADuserptrloadfunc load, void *userptr) {
    int version;

#ifdef VK_VERSION_1_1
    context->EnumerateInstanceVersion  = (PFN_vkEnumerateInstanceVersion) load(userptr, "vkEnumerateInstanceVersion");
#endif
    version = glad_vk_find_core_vulkan(context, physical_device);
    if (!version) {
        return 0;
    }

    glad_vk_load_VK_VERSION_1_0(context, load, userptr);
    glad_vk_load_VK_VERSION_1_1(context, load, userptr);
    glad_vk_load_VK_VERSION_1_2(context, load, userptr);
    glad_vk_load_VK_VERSION_1_3(context, load, userptr);

    if (!glad_vk_find_extensions_vulkan(context, physical_device)) return 0;
    glad_vk_load_VK_AMD_draw_indirect_count(context, load, userptr);
    glad_vk_load_VK_EXT_buffer_device_address(context, load, userptr);
    glad_vk_load_VK_EXT_extended_dynamic_state(context, load, userptr);
    glad_vk_load_VK_EXT_extended_dynamic_state2(context, load, userptr);
    glad_vk_load_VK_EXT_host_query_reset(context, load, userptr);
    glad_vk_load_VK_EXT_private_data(context, load, userptr);
    glad_vk_load_VK_EXT_shader_object(context, load, userptr);
    glad_vk_load_VK_EXT_tooling_info(context, load, userptr);
    glad_vk_load_VK_KHR_bind_memory2(context, load, userptr);
    glad_vk_load_VK_KHR_buffer_device_address(context, load, userptr);
    glad_vk_load_VK_KHR_copy_commands2(context, load, userptr);
    glad_vk_load_VK_KHR_create_renderpass2(context, load, userptr);
    glad_vk_load_VK_KHR_descriptor_update_template(context, load, userptr);
    glad_vk_load_VK_KHR_device_group(context, load, userptr);
    glad_vk_load_VK_KHR_device_group_creation(context, load, userptr);
    glad_vk_load_VK_KHR_draw_indirect_count(context, load, userptr);
    glad_vk_load_VK_KHR_dynamic_rendering(context, load, userptr);
    glad_vk_load_VK_KHR_external_fence_capabilities(context, load, userptr);
    glad_vk_load_VK_KHR_external_memory_capabilities(context, load, userptr);
    glad_vk_load_VK_KHR_external_semaphore_capabilities(context, load, userptr);
    glad_vk_load_VK_KHR_get_memory_requirements2(context, load, userptr);
    glad_vk_load_VK_KHR_get_physical_device_properties2(context, load, userptr);
    glad_vk_load_VK_KHR_maintenance1(context, load, userptr);
    glad_vk_load_VK_KHR_maintenance3(context, load, userptr);
    glad_vk_load_VK_KHR_maintenance4(context, load, userptr);
    glad_vk_load_VK_KHR_sampler_ycbcr_conversion(context, load, userptr);
    glad_vk_load_VK_KHR_synchronization2(context, load, userptr);
    glad_vk_load_VK_KHR_timeline_semaphore(context, load, userptr);

    gladSetVulkanContext(context);
    glad_vk_resolve_aliases(context);

    return version;
}

int gladLoadVulkanUserPtr(VkPhysicalDevice physical_device, GLADuserptrloadfunc load, void *userptr) {
    return gladLoadVulkanContextUserPtr(gladGetVulkanContext(), physical_device, load, userptr);
}

int gladLoadVulkanContext(GladVulkanContext *context, VkPhysicalDevice physical_device, GLADloadfunc load) {
    return gladLoadVulkanContextUserPtr(context, physical_device, glad_vk_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}

int gladLoadVulkan(VkPhysicalDevice physical_device, GLADloadfunc load) {
    return gladLoadVulkanContext(gladGetVulkanContext(), physical_device, load);
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


static uint64_t DEVICE_FUNCTIONS[] = {
    0x81f991d1ab0bc5ce, /* vkAcquireNextImage2KHR */
    0x03c070149bc4adcf, /* vkAllocateCommandBuffers */
    0x6f91a0562614466e, /* vkAllocateDescriptorSets */
    0x3339f46d399c78c5, /* vkAllocateMemory */
    0x47d826cf3a236677, /* vkBeginCommandBuffer */
    0x75dc79c2cde7708a, /* vkBindBufferMemory */
    0x1e001d1f829f257b, /* vkBindBufferMemory2 */
    0xc20b7cd3cdb4895d, /* vkBindBufferMemory2KHR */
    0x3fab09299e5024e6, /* vkBindImageMemory */
    0xfd4ef6a737d2546d, /* vkBindImageMemory2 */
    0xa17b9f5a286650f5, /* vkBindImageMemory2KHR */
    0x997ea78db49c8c69, /* vkCmdBeginQuery */
    0xc8c90b647a8c1688, /* vkCmdBeginRenderPass */
    0xf763fd5a051145b3, /* vkCmdBeginRenderPass2 */
    0x953dd320a2f19033, /* vkCmdBeginRenderPass2KHR */
    0x950906daed043635, /* vkCmdBeginRendering */
    0xf525fcfca497ad4d, /* vkCmdBeginRenderingKHR */
    0xada92dcad41eaf98, /* vkCmdBindDescriptorSets */
    0x668f24a3147926db, /* vkCmdBindIndexBuffer */
    0x093d8596adfdb576, /* vkCmdBindPipeline */
    0x213f8b33c25f4ec9, /* vkCmdBindShadersEXT */
    0x9beb233b5b7ad768, /* vkCmdBindVertexBuffers */
    0xf5dd10901cd99b7e, /* vkCmdBindVertexBuffers2 */
    0x95e7e04ef3cf5655, /* vkCmdBindVertexBuffers2EXT */
    0x38f59a81a499abec, /* vkCmdBlitImage */
    0xfb75695f0deb8eb6, /* vkCmdBlitImage2 */
    0xcdda04206e1c1dfe, /* vkCmdBlitImage2KHR */
    0x484c4c652a1f9c0e, /* vkCmdClearAttachments */
    0x900de63b0b6f0ca2, /* vkCmdClearColorImage */
    0x387f685e13e513fa, /* vkCmdClearDepthStencilImage */
    0x204df3e556149586, /* vkCmdCopyBuffer */
    0x6af432892c9a71c2, /* vkCmdCopyBuffer2 */
    0x4d3f08ecfb5c4893, /* vkCmdCopyBuffer2KHR */
    0x4afe44fc10e34214, /* vkCmdCopyBufferToImage */
    0xdab35189cc70375d, /* vkCmdCopyBufferToImage2 */
    0xaae6e3e723f39a93, /* vkCmdCopyBufferToImage2KHR */
    0x438e5b6a754df791, /* vkCmdCopyImage */
    0xfbe9454065432dfa, /* vkCmdCopyImage2 */
    0xb172c9f4537a3da8, /* vkCmdCopyImage2KHR */
    0x88c098a6d45aa827, /* vkCmdCopyImageToBuffer */
    0x07b8ecf11f0a147a, /* vkCmdCopyImageToBuffer2 */
    0x02eb4358362cbe5f, /* vkCmdCopyImageToBuffer2KHR */
    0xe133357d099609f5, /* vkCmdCopyQueryPoolResults */
    0x9303bbd56b6cd187, /* vkCmdDispatch */
    0xcff95583fb6ffa3f, /* vkCmdDispatchBase */
    0x315127945d495884, /* vkCmdDispatchBaseKHR */
    0xdac55f445397e484, /* vkCmdDispatchIndirect */
    0x6b0e217ae8f0f1ac, /* vkCmdDraw */
    0xf9b2570c3144fc75, /* vkCmdDrawIndexed */
    0x75ffe5f7fd486bdd, /* vkCmdDrawIndexedIndirect */
    0x1d4114fa0cce1718, /* vkCmdDrawIndexedIndirectCount */
    0x95e478a17bd017c9, /* vkCmdDrawIndexedIndirectCountAMD */
    0xa343558c3889eb3b, /* vkCmdDrawIndexedIndirectCountKHR */
    0xf9cc9eb6cea6c9cb, /* vkCmdDrawIndirect */
    0x1b435983eb84abaa, /* vkCmdDrawIndirectCount */
    0x658b77dd8968ff3b, /* vkCmdDrawIndirectCountAMD */
    0xd2ada1f0fce0ebc9, /* vkCmdDrawIndirectCountKHR */
    0x99d50d423e66f60a, /* vkCmdEndQuery */
    0x03e8b953ae4cc537, /* vkCmdEndRenderPass */
    0xd271ad249d3a5d1d, /* vkCmdEndRenderPass2 */
    0xcf86c42d2695983a, /* vkCmdEndRenderPass2KHR */
    0xc261491c6f3eb73a, /* vkCmdEndRendering */
    0x20a57b855bed16ad, /* vkCmdEndRenderingKHR */
    0x1ce083dfe13eae46, /* vkCmdExecuteCommands */
    0x203c934aa0f948fc, /* vkCmdFillBuffer */
    0xf8a5e079575f045d, /* vkCmdNextSubpass */
    0x09d5feddc371e187, /* vkCmdNextSubpass2 */
    0x599380d76631dbc9, /* vkCmdNextSubpass2KHR */
    0xb2063ddd597a6ad7, /* vkCmdPipelineBarrier */
    0x5365aba2c3922f6a, /* vkCmdPipelineBarrier2 */
    0x47b5e34bc173355d, /* vkCmdPipelineBarrier2KHR */
    0xf0bf149eb20282af, /* vkCmdPushConstants */
    0xc0e77996431e14e7, /* vkCmdPushDescriptorSetWithTemplateKHR */
    0x6ac16d77f8579056, /* vkCmdResetEvent */
    0x75fdc7101f295d5d, /* vkCmdResetEvent2 */
    0x8a862e62841ec082, /* vkCmdResetEvent2KHR */
    0x1965935ee47e88e6, /* vkCmdResetQueryPool */
    0x22aa0793e66f037d, /* vkCmdResolveImage */
    0x110bf15d39ef5684, /* vkCmdResolveImage2 */
    0xda6d56b119c97568, /* vkCmdResolveImage2KHR */
    0x4c351cfa990e9dce, /* vkCmdSetAlphaToCoverageEnableEXT */
    0x983f1d9254a0a363, /* vkCmdSetAlphaToOneEnableEXT */
    0x9b6913d4f956684e, /* vkCmdSetBlendConstants */
    0xa0f10e474c7a0e0d, /* vkCmdSetColorBlendAdvancedEXT */
    0x17f9a371c7111a63, /* vkCmdSetColorBlendEnableEXT */
    0x8ada4cd22e8a735c, /* vkCmdSetColorBlendEquationEXT */
    0xe6b91e7965ee4a9f, /* vkCmdSetColorWriteMaskEXT */
    0x659cd4a0990430f6, /* vkCmdSetConservativeRasterizationModeEXT */
    0x1e31e79e5158a92a, /* vkCmdSetCoverageModulationModeNV */
    0x9b7c9ebe9b147cf1, /* vkCmdSetCoverageModulationTableEnableNV */
    0xa34e1bfd05275463, /* vkCmdSetCoverageModulationTableNV */
    0xc1fb12d42b3f2d2c, /* vkCmdSetCoverageReductionModeNV */
    0xe0f1d5482a04901c, /* vkCmdSetCoverageToColorEnableNV */
    0xfe8be5739d1d70ae, /* vkCmdSetCoverageToColorLocationNV */
    0xef3c02c6a6557f67, /* vkCmdSetCullMode */
    0x8ad52c133e5fcc89, /* vkCmdSetCullModeEXT */
    0x74655211ce6abb4b, /* vkCmdSetDepthBias */
    0x1de7b0458bd04513, /* vkCmdSetDepthBiasEnable */
    0xafe12b5c094c8aeb, /* vkCmdSetDepthBiasEnableEXT */
    0x79cca6cf07ff9d67, /* vkCmdSetDepthBounds */
    0xc282ec2fb0ff4a7f, /* vkCmdSetDepthBoundsTestEnable */
    0x09f73ab4947aa834, /* vkCmdSetDepthBoundsTestEnableEXT */
    0x52bc0c7023b88e90, /* vkCmdSetDepthClampEnableEXT */
    0x172c55dd5dc1bc3a, /* vkCmdSetDepthClipEnableEXT */
    0x1def9e89a041b817, /* vkCmdSetDepthClipNegativeOneToOneEXT */
    0x97fb69a7181762a0, /* vkCmdSetDepthCompareOp */
    0xbf39cf164d4f3b71, /* vkCmdSetDepthCompareOpEXT */
    0xefff832805016a4e, /* vkCmdSetDepthTestEnable */
    0xae8baaf2908ad9f8, /* vkCmdSetDepthTestEnableEXT */
    0xa52ec7d995ba8bd0, /* vkCmdSetDepthWriteEnable */
    0x25e2c1a1ae2efd24, /* vkCmdSetDepthWriteEnableEXT */
    0x0b635494ffc80076, /* vkCmdSetDeviceMask */
    0x6a987f9eb7d4a557, /* vkCmdSetDeviceMaskKHR */
    0x5c738ec563b80923, /* vkCmdSetEvent */
    0x358c26001c7dea62, /* vkCmdSetEvent2 */
    0x81a460bb5df2fb6c, /* vkCmdSetEvent2KHR */
    0x538223e2090de1df, /* vkCmdSetExtraPrimitiveOverestimationSizeEXT */
    0xb90a1a834aa8c307, /* vkCmdSetFrontFace */
    0x335573b897d8b48c, /* vkCmdSetFrontFaceEXT */
    0xe86e1a671a40b3b7, /* vkCmdSetLineRasterizationModeEXT */
    0xa664321f63cd904a, /* vkCmdSetLineStippleEnableEXT */
    0xb7ddef653b0f7932, /* vkCmdSetLineWidth */
    0x4fdb2f0ce0346b73, /* vkCmdSetLogicOpEXT */
    0x735a3459f80339e7, /* vkCmdSetLogicOpEnableEXT */
    0x77298a207cf7470a, /* vkCmdSetPatchControlPointsEXT */
    0x48e9ce5a58c1c252, /* vkCmdSetPolygonModeEXT */
    0x5a7b2addceb670c9, /* vkCmdSetPrimitiveRestartEnable */
    0x8debabeca0bc6dd7, /* vkCmdSetPrimitiveRestartEnableEXT */
    0xc4a32c157b57c919, /* vkCmdSetPrimitiveTopology */
    0xf991ab3939955de5, /* vkCmdSetPrimitiveTopologyEXT */
    0xadd175019f7d316f, /* vkCmdSetProvokingVertexModeEXT */
    0xf02843786e3933f8, /* vkCmdSetRasterizationSamplesEXT */
    0x7b3f73b0c28b9ac0, /* vkCmdSetRasterizationStreamEXT */
    0x5ee0b29b506c2241, /* vkCmdSetRasterizerDiscardEnable */
    0x20e538050b42f767, /* vkCmdSetRasterizerDiscardEnableEXT */
    0x2b78093ae32cb916, /* vkCmdSetRepresentativeFragmentTestEnableNV */
    0xcc661f1aee937b88, /* vkCmdSetSampleLocationsEnableEXT */
    0x79bbe5a8a2c19b65, /* vkCmdSetSampleMaskEXT */
    0xc746d971c6158609, /* vkCmdSetScissor */
    0xb9dc146482b98eab, /* vkCmdSetScissorWithCount */
    0x6aa7b18e001aa3e3, /* vkCmdSetScissorWithCountEXT */
    0x2ca882d31d4721ba, /* vkCmdSetShadingRateImageEnableNV */
    0x371cc0f681367e4d, /* vkCmdSetStencilCompareMask */
    0x1ce7a67a576268eb, /* vkCmdSetStencilOp */
    0x0c7a936d63d4b37e, /* vkCmdSetStencilOpEXT */
    0xf6a1a179eb200ea3, /* vkCmdSetStencilReference */
    0x7d12fe073f7c9462, /* vkCmdSetStencilTestEnable */
    0xcb818f46817e8697, /* vkCmdSetStencilTestEnableEXT */
    0x7ce4de962da7bc16, /* vkCmdSetStencilWriteMask */
    0x4b963cb16d7a5ad8, /* vkCmdSetTessellationDomainOriginEXT */
    0x54f4e0d0a5c3dbbf, /* vkCmdSetVertexInputEXT */
    0x33f6b7087e67dab4, /* vkCmdSetViewport */
    0xb449b51a1fdae15f, /* vkCmdSetViewportSwizzleNV */
    0xd35e353760f41c6f, /* vkCmdSetViewportWScalingEnableNV */
    0x0198a65d97d8c9de, /* vkCmdSetViewportWithCount */
    0xffa40d4e01bf3cc0, /* vkCmdSetViewportWithCountEXT */
    0xa1e0bb08c1850958, /* vkCmdUpdateBuffer */
    0x1441dbc95c1af085, /* vkCmdWaitEvents */
    0xba764f7da1952e81, /* vkCmdWaitEvents2 */
    0x1b8ec29acf8f9c34, /* vkCmdWaitEvents2KHR */
    0xb523ea07e8e7d77f, /* vkCmdWriteBufferMarker2AMD */
    0xee397d978e3960d4, /* vkCmdWriteTimestamp */
    0x6172f26a7ff5e461, /* vkCmdWriteTimestamp2 */
    0x2e9f27714c27c160, /* vkCmdWriteTimestamp2KHR */
    0x47176b0b432286d1, /* vkCreateBuffer */
    0xf2fafc3e54bde6da, /* vkCreateBufferView */
    0xc7fb7a8e9fc178bf, /* vkCreateCommandPool */
    0xa8ab2a7a72d37501, /* vkCreateComputePipelines */
    0xfa53afc7b202a4cc, /* vkCreateDescriptorPool */
    0xabbbfebcb5e50ddf, /* vkCreateDescriptorSetLayout */
    0xe77fae71b009ad05, /* vkCreateDescriptorUpdateTemplate */
    0xae196725993a5773, /* vkCreateDescriptorUpdateTemplateKHR */
    0xfc42afaa1bbc54a8, /* vkCreateEvent */
    0xb51bc46c54af21f6, /* vkCreateFence */
    0x38512bbacb368b24, /* vkCreateFramebuffer */
    0x5a4a030363a95dd6, /* vkCreateGraphicsPipelines */
    0x16a20753b1174318, /* vkCreateImage */
    0xb2f2d8afec7a88a4, /* vkCreateImageView */
    0x6474b3f3a4539ee3, /* vkCreatePipelineCache */
    0x76e7d06d87565b38, /* vkCreatePipelineLayout */
    0x126d3121c5d14c5f, /* vkCreatePrivateDataSlot */
    0x914ccba5ef3134d3, /* vkCreatePrivateDataSlotEXT */
    0x509b9755d54a9a1e, /* vkCreateQueryPool */
    0x8b778f59be50c419, /* vkCreateRenderPass */
    0xfd2a746603a13f60, /* vkCreateRenderPass2 */
    0x7282c5dadf99206c, /* vkCreateRenderPass2KHR */
    0xcce224e583312a27, /* vkCreateSampler */
    0xa1ba141ce2a9627b, /* vkCreateSamplerYcbcrConversion */
    0xbaa71789dfb073b1, /* vkCreateSamplerYcbcrConversionKHR */
    0xb23c3f52093e01ee, /* vkCreateSemaphore */
    0xa3fdcfe5e638f01f, /* vkCreateShaderModule */
    0x5736d06f9f7521f5, /* vkCreateShadersEXT */
    0x8ffccda86549f286, /* vkDestroyBuffer */
    0xf56a44bbdebd81c5, /* vkDestroyBufferView */
    0x8ddf999c6ee753db, /* vkDestroyCommandPool */
    0x928a039a45864345, /* vkDestroyDescriptorPool */
    0x44fcf619d29aa8fa, /* vkDestroyDescriptorSetLayout */
    0x410043fbd97c4c0d, /* vkDestroyDescriptorUpdateTemplate */
    0x36da6959c46b24dd, /* vkDestroyDescriptorUpdateTemplateKHR */
    0x9ef6b4cec6a221f8, /* vkDestroyDevice */
    0x6400678c24bf7d34, /* vkDestroyEvent */
    0x865bc9e531e492a5, /* vkDestroyFence */
    0xc0faf7a0688b9961, /* vkDestroyFramebuffer */
    0xc7d428e344b14ca8, /* vkDestroyImage */
    0x76b72b76ccef2958, /* vkDestroyImageView */
    0xc6158137c93c542a, /* vkDestroyPipeline */
    0x1ae7324660591b8f, /* vkDestroyPipelineCache */
    0x9022d31d32c4a419, /* vkDestroyPipelineLayout */
    0xe8fbd5bb4e925208, /* vkDestroyPrivateDataSlot */
    0xdce67e01cb34aa72, /* vkDestroyPrivateDataSlotEXT */
    0x352e0ca38b5e29c0, /* vkDestroyQueryPool */
    0x87a7866d1df23f2b, /* vkDestroyRenderPass */
    0x1c9c24ff8ad40bf7, /* vkDestroySampler */
    0x2c685c0a5e9fbef2, /* vkDestroySamplerYcbcrConversion */
    0xb7d326eaca38da93, /* vkDestroySamplerYcbcrConversionKHR */
    0xa90d9c4553e96cbe, /* vkDestroySemaphore */
    0xb32de6d8d29abe22, /* vkDestroyShaderEXT */
    0x7cb7f1711b397e5f, /* vkDestroyShaderModule */
    0x1de9fd31feb0f22f, /* vkDeviceWaitIdle */
    0x3e52d6e9d1662eb2, /* vkEndCommandBuffer */
    0xcdd7843304775055, /* vkFlushMappedMemoryRanges */
    0x7ecb7451a7e045ed, /* vkFreeCommandBuffers */
    0x80bb22834c81711a, /* vkFreeDescriptorSets */
    0xf2c5ad0d9aa4acf3, /* vkFreeMemory */
    0x44fbf4ea4b060b61, /* vkGetBufferDeviceAddress */
    0x399268bd1fae323b, /* vkGetBufferDeviceAddressEXT */
    0x62692fbaea06e05d, /* vkGetBufferDeviceAddressKHR */
    0xc18ca303430c5030, /* vkGetBufferMemoryRequirements */
    0x146940f88e38657b, /* vkGetBufferMemoryRequirements2 */
    0x77ac813268762693, /* vkGetBufferMemoryRequirements2KHR */
    0x5639c874fc9132f4, /* vkGetBufferOpaqueCaptureAddress */
    0x5de8076ffb7af976, /* vkGetBufferOpaqueCaptureAddressKHR */
    0x25f6d470c53abf71, /* vkGetDescriptorSetLayoutSupport */
    0x0f7af59845222e9d, /* vkGetDescriptorSetLayoutSupportKHR */
    0x15aae27a7223ea5e, /* vkGetDeviceBufferMemoryRequirements */
    0x0e4eac678a76ed33, /* vkGetDeviceBufferMemoryRequirementsKHR */
    0xaf494d1294356cc7, /* vkGetDeviceGroupPeerMemoryFeatures */
    0xe62b971ae0a68532, /* vkGetDeviceGroupPeerMemoryFeaturesKHR */
    0xd537fdf3c85210f2, /* vkGetDeviceGroupPresentCapabilitiesKHR */
    0x32e6d8b01681a0b2, /* vkGetDeviceGroupSurfacePresentModesKHR */
    0x3f4274cc71793a20, /* vkGetDeviceImageMemoryRequirements */
    0xb914845a146232bd, /* vkGetDeviceImageMemoryRequirementsKHR */
    0x987ef1c05cbaa5d8, /* vkGetDeviceImageSparseMemoryRequirements */
    0x423629691279d2c9, /* vkGetDeviceImageSparseMemoryRequirementsKHR */
    0x40f65d68942eb094, /* vkGetDeviceMemoryCommitment */
    0x9666a70591f64892, /* vkGetDeviceMemoryOpaqueCaptureAddress */
    0x316bebcfe32855b8, /* vkGetDeviceMemoryOpaqueCaptureAddressKHR */
    0x39595c56305c625a, /* vkGetDeviceProcAddr */
    0x24683f73b0e5e597, /* vkGetDeviceQueue */
    0x37cec3d3b8dc3838, /* vkGetDeviceQueue2 */
    0x4e9ad990677f931c, /* vkGetEventStatus */
    0xddc1b3a9e007be5a, /* vkGetFenceStatus */
    0x31f122b7cfd4bda7, /* vkGetImageMemoryRequirements */
    0xb69a959653538c19, /* vkGetImageMemoryRequirements2 */
    0x3e094de8a08c3145, /* vkGetImageMemoryRequirements2KHR */
    0x21e4a7d810574ab7, /* vkGetImageSparseMemoryRequirements */
    0xa43291af959e4044, /* vkGetImageSparseMemoryRequirements2 */
    0x9cc130ca400434b7, /* vkGetImageSparseMemoryRequirements2KHR */
    0x23d7885b70c5f681, /* vkGetImageSubresourceLayout */
    0x17bb294acabe6a88, /* vkGetPipelineCacheData */
    0xe43a4f01acf5a1b6, /* vkGetPrivateData */
    0x8da528a7d8e71c4a, /* vkGetPrivateDataEXT */
    0x6b902433192f7f5d, /* vkGetQueryPoolResults */
    0x66d07f2af74e8d8b, /* vkGetQueueCheckpointData2NV */
    0xcfd90dd84e50b6e2, /* vkGetRenderAreaGranularity */
    0xd60ca89f1c84b347, /* vkGetSemaphoreCounterValue */
    0x4f323238bf52cee6, /* vkGetSemaphoreCounterValueKHR */
    0x8b087bf937ffd567, /* vkGetShaderBinaryDataEXT */
    0x3a0a07834723853e, /* vkInvalidateMappedMemoryRanges */
    0x808f7434b0596604, /* vkMapMemory */
    0xcfbd6aad8345b609, /* vkMergePipelineCaches */
    0x814945b3834b2f13, /* vkQueueBindSparse */
    0x0c3e489641018fd0, /* vkQueueSubmit */
    0x60464991fe32093e, /* vkQueueSubmit2 */
    0x7eff5818fce6b445, /* vkQueueSubmit2KHR */
    0x1fce1bdecaf06b52, /* vkQueueWaitIdle */
    0xc6fee3fca12fb11e, /* vkResetCommandBuffer */
    0x1e931402fc057014, /* vkResetCommandPool */
    0xa6007e58158aed7d, /* vkResetDescriptorPool */
    0x2e0b5702efb33535, /* vkResetEvent */
    0x234a880591facce1, /* vkResetFences */
    0xd34524d6520a5733, /* vkResetQueryPool */
    0x40648ed2af7eecdd, /* vkResetQueryPoolEXT */
    0xd0df5f67ee24e975, /* vkSetEvent */
    0x2384403e82f430b9, /* vkSetPrivateData */
    0xc2f02663a1a88208, /* vkSetPrivateDataEXT */
    0x6a0ad52ae1fd239d, /* vkSignalSemaphore */
    0xb8f7f65305fa9c04, /* vkSignalSemaphoreKHR */
    0x620e4a899bc7e882, /* vkTrimCommandPool */
    0x73f1f198f822a45e, /* vkTrimCommandPoolKHR */
    0xf51a3c7f77277e37, /* vkUnmapMemory */
    0x1ebd0c97c69da82b, /* vkUpdateDescriptorSetWithTemplate */
    0x71b8cb2fd8159c3d, /* vkUpdateDescriptorSetWithTemplateKHR */
    0xaac33dd01204ea6d, /* vkUpdateDescriptorSets */
    0x7c1238295eaa98e9, /* vkWaitForFences */
    0x464cdf5591d873eb, /* vkWaitSemaphores */
    0x90b98ea73daf2fc7, /* vkWaitSemaphoresKHR */
};

static int glad_vulkan_is_device_function(const char *name) {
    /* Exists as a workaround for:
     * https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/issues/2323
     *
     * `vkGetDeviceProcAddr` does not return NULL for non-device functions.
     */
    return glad_hash_search(DEVICE_FUNCTIONS, GLAD_ARRAYSIZE(DEVICE_FUNCTIONS), glad_hash_string(name, strlen(name)));
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
    PFN_vkVoidFunction result = NULL;

    if (userptr.vk_device != NULL && glad_vulkan_is_device_function(name)) {
        result = userptr.get_device_proc_addr(userptr.vk_device, name);
    }

    if (result == NULL && userptr.vk_instance != NULL) {
        result = userptr.get_instance_proc_addr(userptr.vk_instance, name);
    }

    if(result == NULL) {
        result = (PFN_vkVoidFunction) glad_dlsym_handle(userptr.vk_handle, name);
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

        if (userptr.get_instance_proc_addr != NULL && userptr.get_device_proc_addr != NULL) {
            version = gladLoadVulkanContextUserPtr(context, physical_device, glad_vulkan_get_proc, &userptr);
        }

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
