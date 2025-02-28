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
    /*    0 */ "vkAcquireDrmDisplayEXT",
    /*    1 */ "vkAcquireFullScreenExclusiveModeEXT",
    /*    2 */ "vkAcquireNextImage2KHR",
    /*    3 */ "vkAcquireNextImageKHR",
    /*    4 */ "vkAcquirePerformanceConfigurationINTEL",
    /*    5 */ "vkAcquireProfilingLockKHR",
    /*    6 */ "vkAcquireWinrtDisplayNV",
    /*    7 */ "vkAcquireXlibDisplayEXT",
    /*    8 */ "vkAllocateCommandBuffers",
    /*    9 */ "vkAllocateDescriptorSets",
    /*   10 */ "vkAllocateMemory",
    /*   11 */ "vkAntiLagUpdateAMD",
    /*   12 */ "vkBeginCommandBuffer",
    /*   13 */ "vkBindAccelerationStructureMemoryNV",
    /*   14 */ "vkBindBufferMemory",
    /*   15 */ "vkBindBufferMemory2",
    /*   16 */ "vkBindBufferMemory2KHR",
    /*   17 */ "vkBindImageMemory",
    /*   18 */ "vkBindImageMemory2",
    /*   19 */ "vkBindImageMemory2KHR",
    /*   20 */ "vkBindOpticalFlowSessionImageNV",
    /*   21 */ "vkBindVideoSessionMemoryKHR",
    /*   22 */ "vkBuildAccelerationStructuresKHR",
    /*   23 */ "vkBuildMicromapsEXT",
    /*   24 */ "vkCmdBeginConditionalRenderingEXT",
    /*   25 */ "vkCmdBeginDebugUtilsLabelEXT",
    /*   26 */ "vkCmdBeginQuery",
    /*   27 */ "vkCmdBeginQueryIndexedEXT",
    /*   28 */ "vkCmdBeginRenderPass",
    /*   29 */ "vkCmdBeginRenderPass2",
    /*   30 */ "vkCmdBeginRenderPass2KHR",
    /*   31 */ "vkCmdBeginRendering",
    /*   32 */ "vkCmdBeginRenderingKHR",
    /*   33 */ "vkCmdBeginTransformFeedbackEXT",
    /*   34 */ "vkCmdBeginVideoCodingKHR",
    /*   35 */ "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT",
    /*   36 */ "vkCmdBindDescriptorBufferEmbeddedSamplersEXT",
    /*   37 */ "vkCmdBindDescriptorBuffersEXT",
    /*   38 */ "vkCmdBindDescriptorSets",
    /*   39 */ "vkCmdBindDescriptorSets2",
    /*   40 */ "vkCmdBindDescriptorSets2KHR",
    /*   41 */ "vkCmdBindIndexBuffer",
    /*   42 */ "vkCmdBindIndexBuffer2",
    /*   43 */ "vkCmdBindIndexBuffer2KHR",
    /*   44 */ "vkCmdBindInvocationMaskHUAWEI",
    /*   45 */ "vkCmdBindPipeline",
    /*   46 */ "vkCmdBindPipelineShaderGroupNV",
    /*   47 */ "vkCmdBindShadersEXT",
    /*   48 */ "vkCmdBindShadingRateImageNV",
    /*   49 */ "vkCmdBindTransformFeedbackBuffersEXT",
    /*   50 */ "vkCmdBindVertexBuffers",
    /*   51 */ "vkCmdBindVertexBuffers2",
    /*   52 */ "vkCmdBindVertexBuffers2EXT",
    /*   53 */ "vkCmdBlitImage",
    /*   54 */ "vkCmdBlitImage2",
    /*   55 */ "vkCmdBlitImage2KHR",
    /*   56 */ "vkCmdBuildAccelerationStructureNV",
    /*   57 */ "vkCmdBuildAccelerationStructuresIndirectKHR",
    /*   58 */ "vkCmdBuildAccelerationStructuresKHR",
    /*   59 */ "vkCmdBuildClusterAccelerationStructureIndirectNV",
    /*   60 */ "vkCmdBuildMicromapsEXT",
    /*   61 */ "vkCmdBuildPartitionedAccelerationStructuresNV",
    /*   62 */ "vkCmdClearAttachments",
    /*   63 */ "vkCmdClearColorImage",
    /*   64 */ "vkCmdClearDepthStencilImage",
    /*   65 */ "vkCmdControlVideoCodingKHR",
    /*   66 */ "vkCmdConvertCooperativeVectorMatrixNV",
    /*   67 */ "vkCmdCopyAccelerationStructureKHR",
    /*   68 */ "vkCmdCopyAccelerationStructureNV",
    /*   69 */ "vkCmdCopyAccelerationStructureToMemoryKHR",
    /*   70 */ "vkCmdCopyBuffer",
    /*   71 */ "vkCmdCopyBuffer2",
    /*   72 */ "vkCmdCopyBuffer2KHR",
    /*   73 */ "vkCmdCopyBufferToImage",
    /*   74 */ "vkCmdCopyBufferToImage2",
    /*   75 */ "vkCmdCopyBufferToImage2KHR",
    /*   76 */ "vkCmdCopyImage",
    /*   77 */ "vkCmdCopyImage2",
    /*   78 */ "vkCmdCopyImage2KHR",
    /*   79 */ "vkCmdCopyImageToBuffer",
    /*   80 */ "vkCmdCopyImageToBuffer2",
    /*   81 */ "vkCmdCopyImageToBuffer2KHR",
    /*   82 */ "vkCmdCopyMemoryIndirectNV",
    /*   83 */ "vkCmdCopyMemoryToAccelerationStructureKHR",
    /*   84 */ "vkCmdCopyMemoryToImageIndirectNV",
    /*   85 */ "vkCmdCopyMemoryToMicromapEXT",
    /*   86 */ "vkCmdCopyMicromapEXT",
    /*   87 */ "vkCmdCopyMicromapToMemoryEXT",
    /*   88 */ "vkCmdCopyQueryPoolResults",
    /*   89 */ "vkCmdCuLaunchKernelNVX",
    /*   90 */ "vkCmdCudaLaunchKernelNV",
    /*   91 */ "vkCmdDebugMarkerBeginEXT",
    /*   92 */ "vkCmdDebugMarkerEndEXT",
    /*   93 */ "vkCmdDebugMarkerInsertEXT",
    /*   94 */ "vkCmdDecodeVideoKHR",
    /*   95 */ "vkCmdDecompressMemoryIndirectCountNV",
    /*   96 */ "vkCmdDecompressMemoryNV",
    /*   97 */ "vkCmdDispatch",
    /*   98 */ "vkCmdDispatchBase",
    /*   99 */ "vkCmdDispatchBaseKHR",
    /*  100 */ "vkCmdDispatchGraphAMDX",
    /*  101 */ "vkCmdDispatchGraphIndirectAMDX",
    /*  102 */ "vkCmdDispatchGraphIndirectCountAMDX",
    /*  103 */ "vkCmdDispatchIndirect",
    /*  104 */ "vkCmdDraw",
    /*  105 */ "vkCmdDrawClusterHUAWEI",
    /*  106 */ "vkCmdDrawClusterIndirectHUAWEI",
    /*  107 */ "vkCmdDrawIndexed",
    /*  108 */ "vkCmdDrawIndexedIndirect",
    /*  109 */ "vkCmdDrawIndexedIndirectCount",
    /*  110 */ "vkCmdDrawIndexedIndirectCountAMD",
    /*  111 */ "vkCmdDrawIndexedIndirectCountKHR",
    /*  112 */ "vkCmdDrawIndirect",
    /*  113 */ "vkCmdDrawIndirectByteCountEXT",
    /*  114 */ "vkCmdDrawIndirectCount",
    /*  115 */ "vkCmdDrawIndirectCountAMD",
    /*  116 */ "vkCmdDrawIndirectCountKHR",
    /*  117 */ "vkCmdDrawMeshTasksEXT",
    /*  118 */ "vkCmdDrawMeshTasksIndirectCountEXT",
    /*  119 */ "vkCmdDrawMeshTasksIndirectCountNV",
    /*  120 */ "vkCmdDrawMeshTasksIndirectEXT",
    /*  121 */ "vkCmdDrawMeshTasksIndirectNV",
    /*  122 */ "vkCmdDrawMeshTasksNV",
    /*  123 */ "vkCmdDrawMultiEXT",
    /*  124 */ "vkCmdDrawMultiIndexedEXT",
    /*  125 */ "vkCmdEncodeVideoKHR",
    /*  126 */ "vkCmdEndConditionalRenderingEXT",
    /*  127 */ "vkCmdEndDebugUtilsLabelEXT",
    /*  128 */ "vkCmdEndQuery",
    /*  129 */ "vkCmdEndQueryIndexedEXT",
    /*  130 */ "vkCmdEndRenderPass",
    /*  131 */ "vkCmdEndRenderPass2",
    /*  132 */ "vkCmdEndRenderPass2KHR",
    /*  133 */ "vkCmdEndRendering",
    /*  134 */ "vkCmdEndRenderingKHR",
    /*  135 */ "vkCmdEndTransformFeedbackEXT",
    /*  136 */ "vkCmdEndVideoCodingKHR",
    /*  137 */ "vkCmdExecuteCommands",
    /*  138 */ "vkCmdExecuteGeneratedCommandsEXT",
    /*  139 */ "vkCmdExecuteGeneratedCommandsNV",
    /*  140 */ "vkCmdFillBuffer",
    /*  141 */ "vkCmdInitializeGraphScratchMemoryAMDX",
    /*  142 */ "vkCmdInsertDebugUtilsLabelEXT",
    /*  143 */ "vkCmdNextSubpass",
    /*  144 */ "vkCmdNextSubpass2",
    /*  145 */ "vkCmdNextSubpass2KHR",
    /*  146 */ "vkCmdOpticalFlowExecuteNV",
    /*  147 */ "vkCmdPipelineBarrier",
    /*  148 */ "vkCmdPipelineBarrier2",
    /*  149 */ "vkCmdPipelineBarrier2KHR",
    /*  150 */ "vkCmdPreprocessGeneratedCommandsEXT",
    /*  151 */ "vkCmdPreprocessGeneratedCommandsNV",
    /*  152 */ "vkCmdPushConstants",
    /*  153 */ "vkCmdPushConstants2",
    /*  154 */ "vkCmdPushConstants2KHR",
    /*  155 */ "vkCmdPushDescriptorSet",
    /*  156 */ "vkCmdPushDescriptorSet2",
    /*  157 */ "vkCmdPushDescriptorSet2KHR",
    /*  158 */ "vkCmdPushDescriptorSetKHR",
    /*  159 */ "vkCmdPushDescriptorSetWithTemplate",
    /*  160 */ "vkCmdPushDescriptorSetWithTemplate2",
    /*  161 */ "vkCmdPushDescriptorSetWithTemplate2KHR",
    /*  162 */ "vkCmdPushDescriptorSetWithTemplateKHR",
    /*  163 */ "vkCmdResetEvent",
    /*  164 */ "vkCmdResetEvent2",
    /*  165 */ "vkCmdResetEvent2KHR",
    /*  166 */ "vkCmdResetQueryPool",
    /*  167 */ "vkCmdResolveImage",
    /*  168 */ "vkCmdResolveImage2",
    /*  169 */ "vkCmdResolveImage2KHR",
    /*  170 */ "vkCmdSetAlphaToCoverageEnableEXT",
    /*  171 */ "vkCmdSetAlphaToOneEnableEXT",
    /*  172 */ "vkCmdSetAttachmentFeedbackLoopEnableEXT",
    /*  173 */ "vkCmdSetBlendConstants",
    /*  174 */ "vkCmdSetCheckpointNV",
    /*  175 */ "vkCmdSetCoarseSampleOrderNV",
    /*  176 */ "vkCmdSetColorBlendAdvancedEXT",
    /*  177 */ "vkCmdSetColorBlendEnableEXT",
    /*  178 */ "vkCmdSetColorBlendEquationEXT",
    /*  179 */ "vkCmdSetColorWriteEnableEXT",
    /*  180 */ "vkCmdSetColorWriteMaskEXT",
    /*  181 */ "vkCmdSetConservativeRasterizationModeEXT",
    /*  182 */ "vkCmdSetCoverageModulationModeNV",
    /*  183 */ "vkCmdSetCoverageModulationTableEnableNV",
    /*  184 */ "vkCmdSetCoverageModulationTableNV",
    /*  185 */ "vkCmdSetCoverageReductionModeNV",
    /*  186 */ "vkCmdSetCoverageToColorEnableNV",
    /*  187 */ "vkCmdSetCoverageToColorLocationNV",
    /*  188 */ "vkCmdSetCullMode",
    /*  189 */ "vkCmdSetCullModeEXT",
    /*  190 */ "vkCmdSetDepthBias",
    /*  191 */ "vkCmdSetDepthBias2EXT",
    /*  192 */ "vkCmdSetDepthBiasEnable",
    /*  193 */ "vkCmdSetDepthBiasEnableEXT",
    /*  194 */ "vkCmdSetDepthBounds",
    /*  195 */ "vkCmdSetDepthBoundsTestEnable",
    /*  196 */ "vkCmdSetDepthBoundsTestEnableEXT",
    /*  197 */ "vkCmdSetDepthClampEnableEXT",
    /*  198 */ "vkCmdSetDepthClampRangeEXT",
    /*  199 */ "vkCmdSetDepthClipEnableEXT",
    /*  200 */ "vkCmdSetDepthClipNegativeOneToOneEXT",
    /*  201 */ "vkCmdSetDepthCompareOp",
    /*  202 */ "vkCmdSetDepthCompareOpEXT",
    /*  203 */ "vkCmdSetDepthTestEnable",
    /*  204 */ "vkCmdSetDepthTestEnableEXT",
    /*  205 */ "vkCmdSetDepthWriteEnable",
    /*  206 */ "vkCmdSetDepthWriteEnableEXT",
    /*  207 */ "vkCmdSetDescriptorBufferOffsets2EXT",
    /*  208 */ "vkCmdSetDescriptorBufferOffsetsEXT",
    /*  209 */ "vkCmdSetDeviceMask",
    /*  210 */ "vkCmdSetDeviceMaskKHR",
    /*  211 */ "vkCmdSetDiscardRectangleEXT",
    /*  212 */ "vkCmdSetDiscardRectangleEnableEXT",
    /*  213 */ "vkCmdSetDiscardRectangleModeEXT",
    /*  214 */ "vkCmdSetEvent",
    /*  215 */ "vkCmdSetEvent2",
    /*  216 */ "vkCmdSetEvent2KHR",
    /*  217 */ "vkCmdSetExclusiveScissorEnableNV",
    /*  218 */ "vkCmdSetExclusiveScissorNV",
    /*  219 */ "vkCmdSetExtraPrimitiveOverestimationSizeEXT",
    /*  220 */ "vkCmdSetFragmentShadingRateEnumNV",
    /*  221 */ "vkCmdSetFragmentShadingRateKHR",
    /*  222 */ "vkCmdSetFrontFace",
    /*  223 */ "vkCmdSetFrontFaceEXT",
    /*  224 */ "vkCmdSetLineRasterizationModeEXT",
    /*  225 */ "vkCmdSetLineStipple",
    /*  226 */ "vkCmdSetLineStippleEXT",
    /*  227 */ "vkCmdSetLineStippleEnableEXT",
    /*  228 */ "vkCmdSetLineStippleKHR",
    /*  229 */ "vkCmdSetLineWidth",
    /*  230 */ "vkCmdSetLogicOpEXT",
    /*  231 */ "vkCmdSetLogicOpEnableEXT",
    /*  232 */ "vkCmdSetPatchControlPointsEXT",
    /*  233 */ "vkCmdSetPerformanceMarkerINTEL",
    /*  234 */ "vkCmdSetPerformanceOverrideINTEL",
    /*  235 */ "vkCmdSetPerformanceStreamMarkerINTEL",
    /*  236 */ "vkCmdSetPolygonModeEXT",
    /*  237 */ "vkCmdSetPrimitiveRestartEnable",
    /*  238 */ "vkCmdSetPrimitiveRestartEnableEXT",
    /*  239 */ "vkCmdSetPrimitiveTopology",
    /*  240 */ "vkCmdSetPrimitiveTopologyEXT",
    /*  241 */ "vkCmdSetProvokingVertexModeEXT",
    /*  242 */ "vkCmdSetRasterizationSamplesEXT",
    /*  243 */ "vkCmdSetRasterizationStreamEXT",
    /*  244 */ "vkCmdSetRasterizerDiscardEnable",
    /*  245 */ "vkCmdSetRasterizerDiscardEnableEXT",
    /*  246 */ "vkCmdSetRayTracingPipelineStackSizeKHR",
    /*  247 */ "vkCmdSetRenderingAttachmentLocations",
    /*  248 */ "vkCmdSetRenderingAttachmentLocationsKHR",
    /*  249 */ "vkCmdSetRenderingInputAttachmentIndices",
    /*  250 */ "vkCmdSetRenderingInputAttachmentIndicesKHR",
    /*  251 */ "vkCmdSetRepresentativeFragmentTestEnableNV",
    /*  252 */ "vkCmdSetSampleLocationsEXT",
    /*  253 */ "vkCmdSetSampleLocationsEnableEXT",
    /*  254 */ "vkCmdSetSampleMaskEXT",
    /*  255 */ "vkCmdSetScissor",
    /*  256 */ "vkCmdSetScissorWithCount",
    /*  257 */ "vkCmdSetScissorWithCountEXT",
    /*  258 */ "vkCmdSetShadingRateImageEnableNV",
    /*  259 */ "vkCmdSetStencilCompareMask",
    /*  260 */ "vkCmdSetStencilOp",
    /*  261 */ "vkCmdSetStencilOpEXT",
    /*  262 */ "vkCmdSetStencilReference",
    /*  263 */ "vkCmdSetStencilTestEnable",
    /*  264 */ "vkCmdSetStencilTestEnableEXT",
    /*  265 */ "vkCmdSetStencilWriteMask",
    /*  266 */ "vkCmdSetTessellationDomainOriginEXT",
    /*  267 */ "vkCmdSetVertexInputEXT",
    /*  268 */ "vkCmdSetViewport",
    /*  269 */ "vkCmdSetViewportShadingRatePaletteNV",
    /*  270 */ "vkCmdSetViewportSwizzleNV",
    /*  271 */ "vkCmdSetViewportWScalingEnableNV",
    /*  272 */ "vkCmdSetViewportWScalingNV",
    /*  273 */ "vkCmdSetViewportWithCount",
    /*  274 */ "vkCmdSetViewportWithCountEXT",
    /*  275 */ "vkCmdSubpassShadingHUAWEI",
    /*  276 */ "vkCmdTraceRaysIndirect2KHR",
    /*  277 */ "vkCmdTraceRaysIndirectKHR",
    /*  278 */ "vkCmdTraceRaysKHR",
    /*  279 */ "vkCmdTraceRaysNV",
    /*  280 */ "vkCmdUpdateBuffer",
    /*  281 */ "vkCmdUpdatePipelineIndirectBufferNV",
    /*  282 */ "vkCmdWaitEvents",
    /*  283 */ "vkCmdWaitEvents2",
    /*  284 */ "vkCmdWaitEvents2KHR",
    /*  285 */ "vkCmdWriteAccelerationStructuresPropertiesKHR",
    /*  286 */ "vkCmdWriteAccelerationStructuresPropertiesNV",
    /*  287 */ "vkCmdWriteBufferMarker2AMD",
    /*  288 */ "vkCmdWriteBufferMarkerAMD",
    /*  289 */ "vkCmdWriteMicromapsPropertiesEXT",
    /*  290 */ "vkCmdWriteTimestamp",
    /*  291 */ "vkCmdWriteTimestamp2",
    /*  292 */ "vkCmdWriteTimestamp2KHR",
    /*  293 */ "vkCompileDeferredNV",
    /*  294 */ "vkConvertCooperativeVectorMatrixNV",
    /*  295 */ "vkCopyAccelerationStructureKHR",
    /*  296 */ "vkCopyAccelerationStructureToMemoryKHR",
    /*  297 */ "vkCopyImageToImage",
    /*  298 */ "vkCopyImageToImageEXT",
    /*  299 */ "vkCopyImageToMemory",
    /*  300 */ "vkCopyImageToMemoryEXT",
    /*  301 */ "vkCopyMemoryToAccelerationStructureKHR",
    /*  302 */ "vkCopyMemoryToImage",
    /*  303 */ "vkCopyMemoryToImageEXT",
    /*  304 */ "vkCopyMemoryToMicromapEXT",
    /*  305 */ "vkCopyMicromapEXT",
    /*  306 */ "vkCopyMicromapToMemoryEXT",
    /*  307 */ "vkCreateAccelerationStructureKHR",
    /*  308 */ "vkCreateAccelerationStructureNV",
    /*  309 */ "vkCreateAndroidSurfaceKHR",
    /*  310 */ "vkCreateBuffer",
    /*  311 */ "vkCreateBufferCollectionFUCHSIA",
    /*  312 */ "vkCreateBufferView",
    /*  313 */ "vkCreateCommandPool",
    /*  314 */ "vkCreateComputePipelines",
    /*  315 */ "vkCreateCuFunctionNVX",
    /*  316 */ "vkCreateCuModuleNVX",
    /*  317 */ "vkCreateCudaFunctionNV",
    /*  318 */ "vkCreateCudaModuleNV",
    /*  319 */ "vkCreateDebugReportCallbackEXT",
    /*  320 */ "vkCreateDebugUtilsMessengerEXT",
    /*  321 */ "vkCreateDeferredOperationKHR",
    /*  322 */ "vkCreateDescriptorPool",
    /*  323 */ "vkCreateDescriptorSetLayout",
    /*  324 */ "vkCreateDescriptorUpdateTemplate",
    /*  325 */ "vkCreateDescriptorUpdateTemplateKHR",
    /*  326 */ "vkCreateDevice",
    /*  327 */ "vkCreateDirectFBSurfaceEXT",
    /*  328 */ "vkCreateDisplayModeKHR",
    /*  329 */ "vkCreateDisplayPlaneSurfaceKHR",
    /*  330 */ "vkCreateEvent",
    /*  331 */ "vkCreateExecutionGraphPipelinesAMDX",
    /*  332 */ "vkCreateFence",
    /*  333 */ "vkCreateFramebuffer",
    /*  334 */ "vkCreateGraphicsPipelines",
    /*  335 */ "vkCreateHeadlessSurfaceEXT",
    /*  336 */ "vkCreateIOSSurfaceMVK",
    /*  337 */ "vkCreateImage",
    /*  338 */ "vkCreateImagePipeSurfaceFUCHSIA",
    /*  339 */ "vkCreateImageView",
    /*  340 */ "vkCreateIndirectCommandsLayoutEXT",
    /*  341 */ "vkCreateIndirectCommandsLayoutNV",
    /*  342 */ "vkCreateIndirectExecutionSetEXT",
    /*  343 */ "vkCreateInstance",
    /*  344 */ "vkCreateMacOSSurfaceMVK",
    /*  345 */ "vkCreateMetalSurfaceEXT",
    /*  346 */ "vkCreateMicromapEXT",
    /*  347 */ "vkCreateOpticalFlowSessionNV",
    /*  348 */ "vkCreatePipelineBinariesKHR",
    /*  349 */ "vkCreatePipelineCache",
    /*  350 */ "vkCreatePipelineLayout",
    /*  351 */ "vkCreatePrivateDataSlot",
    /*  352 */ "vkCreatePrivateDataSlotEXT",
    /*  353 */ "vkCreateQueryPool",
    /*  354 */ "vkCreateRayTracingPipelinesKHR",
    /*  355 */ "vkCreateRayTracingPipelinesNV",
    /*  356 */ "vkCreateRenderPass",
    /*  357 */ "vkCreateRenderPass2",
    /*  358 */ "vkCreateRenderPass2KHR",
    /*  359 */ "vkCreateSampler",
    /*  360 */ "vkCreateSamplerYcbcrConversion",
    /*  361 */ "vkCreateSamplerYcbcrConversionKHR",
    /*  362 */ "vkCreateScreenSurfaceQNX",
    /*  363 */ "vkCreateSemaphore",
    /*  364 */ "vkCreateShaderModule",
    /*  365 */ "vkCreateShadersEXT",
    /*  366 */ "vkCreateSharedSwapchainsKHR",
    /*  367 */ "vkCreateStreamDescriptorSurfaceGGP",
    /*  368 */ "vkCreateSwapchainKHR",
    /*  369 */ "vkCreateValidationCacheEXT",
    /*  370 */ "vkCreateViSurfaceNN",
    /*  371 */ "vkCreateVideoSessionKHR",
    /*  372 */ "vkCreateVideoSessionParametersKHR",
    /*  373 */ "vkCreateWaylandSurfaceKHR",
    /*  374 */ "vkCreateWin32SurfaceKHR",
    /*  375 */ "vkCreateXcbSurfaceKHR",
    /*  376 */ "vkCreateXlibSurfaceKHR",
    /*  377 */ "vkDebugMarkerSetObjectNameEXT",
    /*  378 */ "vkDebugMarkerSetObjectTagEXT",
    /*  379 */ "vkDebugReportMessageEXT",
    /*  380 */ "vkDeferredOperationJoinKHR",
    /*  381 */ "vkDestroyAccelerationStructureKHR",
    /*  382 */ "vkDestroyAccelerationStructureNV",
    /*  383 */ "vkDestroyBuffer",
    /*  384 */ "vkDestroyBufferCollectionFUCHSIA",
    /*  385 */ "vkDestroyBufferView",
    /*  386 */ "vkDestroyCommandPool",
    /*  387 */ "vkDestroyCuFunctionNVX",
    /*  388 */ "vkDestroyCuModuleNVX",
    /*  389 */ "vkDestroyCudaFunctionNV",
    /*  390 */ "vkDestroyCudaModuleNV",
    /*  391 */ "vkDestroyDebugReportCallbackEXT",
    /*  392 */ "vkDestroyDebugUtilsMessengerEXT",
    /*  393 */ "vkDestroyDeferredOperationKHR",
    /*  394 */ "vkDestroyDescriptorPool",
    /*  395 */ "vkDestroyDescriptorSetLayout",
    /*  396 */ "vkDestroyDescriptorUpdateTemplate",
    /*  397 */ "vkDestroyDescriptorUpdateTemplateKHR",
    /*  398 */ "vkDestroyDevice",
    /*  399 */ "vkDestroyEvent",
    /*  400 */ "vkDestroyFence",
    /*  401 */ "vkDestroyFramebuffer",
    /*  402 */ "vkDestroyImage",
    /*  403 */ "vkDestroyImageView",
    /*  404 */ "vkDestroyIndirectCommandsLayoutEXT",
    /*  405 */ "vkDestroyIndirectCommandsLayoutNV",
    /*  406 */ "vkDestroyIndirectExecutionSetEXT",
    /*  407 */ "vkDestroyInstance",
    /*  408 */ "vkDestroyMicromapEXT",
    /*  409 */ "vkDestroyOpticalFlowSessionNV",
    /*  410 */ "vkDestroyPipeline",
    /*  411 */ "vkDestroyPipelineBinaryKHR",
    /*  412 */ "vkDestroyPipelineCache",
    /*  413 */ "vkDestroyPipelineLayout",
    /*  414 */ "vkDestroyPrivateDataSlot",
    /*  415 */ "vkDestroyPrivateDataSlotEXT",
    /*  416 */ "vkDestroyQueryPool",
    /*  417 */ "vkDestroyRenderPass",
    /*  418 */ "vkDestroySampler",
    /*  419 */ "vkDestroySamplerYcbcrConversion",
    /*  420 */ "vkDestroySamplerYcbcrConversionKHR",
    /*  421 */ "vkDestroySemaphore",
    /*  422 */ "vkDestroyShaderEXT",
    /*  423 */ "vkDestroyShaderModule",
    /*  424 */ "vkDestroySurfaceKHR",
    /*  425 */ "vkDestroySwapchainKHR",
    /*  426 */ "vkDestroyValidationCacheEXT",
    /*  427 */ "vkDestroyVideoSessionKHR",
    /*  428 */ "vkDestroyVideoSessionParametersKHR",
    /*  429 */ "vkDeviceWaitIdle",
    /*  430 */ "vkDisplayPowerControlEXT",
    /*  431 */ "vkEndCommandBuffer",
    /*  432 */ "vkEnumerateDeviceExtensionProperties",
    /*  433 */ "vkEnumerateDeviceLayerProperties",
    /*  434 */ "vkEnumerateInstanceExtensionProperties",
    /*  435 */ "vkEnumerateInstanceLayerProperties",
    /*  436 */ "vkEnumerateInstanceVersion",
    /*  437 */ "vkEnumeratePhysicalDeviceGroups",
    /*  438 */ "vkEnumeratePhysicalDeviceGroupsKHR",
    /*  439 */ "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR",
    /*  440 */ "vkEnumeratePhysicalDevices",
    /*  441 */ "vkExportMetalObjectsEXT",
    /*  442 */ "vkFlushMappedMemoryRanges",
    /*  443 */ "vkFreeCommandBuffers",
    /*  444 */ "vkFreeDescriptorSets",
    /*  445 */ "vkFreeMemory",
    /*  446 */ "vkGetAccelerationStructureBuildSizesKHR",
    /*  447 */ "vkGetAccelerationStructureDeviceAddressKHR",
    /*  448 */ "vkGetAccelerationStructureHandleNV",
    /*  449 */ "vkGetAccelerationStructureMemoryRequirementsNV",
    /*  450 */ "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT",
    /*  451 */ "vkGetAndroidHardwareBufferPropertiesANDROID",
    /*  452 */ "vkGetBufferCollectionPropertiesFUCHSIA",
    /*  453 */ "vkGetBufferDeviceAddress",
    /*  454 */ "vkGetBufferDeviceAddressEXT",
    /*  455 */ "vkGetBufferDeviceAddressKHR",
    /*  456 */ "vkGetBufferMemoryRequirements",
    /*  457 */ "vkGetBufferMemoryRequirements2",
    /*  458 */ "vkGetBufferMemoryRequirements2KHR",
    /*  459 */ "vkGetBufferOpaqueCaptureAddress",
    /*  460 */ "vkGetBufferOpaqueCaptureAddressKHR",
    /*  461 */ "vkGetBufferOpaqueCaptureDescriptorDataEXT",
    /*  462 */ "vkGetCalibratedTimestampsEXT",
    /*  463 */ "vkGetCalibratedTimestampsKHR",
    /*  464 */ "vkGetClusterAccelerationStructureBuildSizesNV",
    /*  465 */ "vkGetCudaModuleCacheNV",
    /*  466 */ "vkGetDeferredOperationMaxConcurrencyKHR",
    /*  467 */ "vkGetDeferredOperationResultKHR",
    /*  468 */ "vkGetDescriptorEXT",
    /*  469 */ "vkGetDescriptorSetHostMappingVALVE",
    /*  470 */ "vkGetDescriptorSetLayoutBindingOffsetEXT",
    /*  471 */ "vkGetDescriptorSetLayoutHostMappingInfoVALVE",
    /*  472 */ "vkGetDescriptorSetLayoutSizeEXT",
    /*  473 */ "vkGetDescriptorSetLayoutSupport",
    /*  474 */ "vkGetDescriptorSetLayoutSupportKHR",
    /*  475 */ "vkGetDeviceAccelerationStructureCompatibilityKHR",
    /*  476 */ "vkGetDeviceBufferMemoryRequirements",
    /*  477 */ "vkGetDeviceBufferMemoryRequirementsKHR",
    /*  478 */ "vkGetDeviceFaultInfoEXT",
    /*  479 */ "vkGetDeviceGroupPeerMemoryFeatures",
    /*  480 */ "vkGetDeviceGroupPeerMemoryFeaturesKHR",
    /*  481 */ "vkGetDeviceGroupPresentCapabilitiesKHR",
    /*  482 */ "vkGetDeviceGroupSurfacePresentModes2EXT",
    /*  483 */ "vkGetDeviceGroupSurfacePresentModesKHR",
    /*  484 */ "vkGetDeviceImageMemoryRequirements",
    /*  485 */ "vkGetDeviceImageMemoryRequirementsKHR",
    /*  486 */ "vkGetDeviceImageSparseMemoryRequirements",
    /*  487 */ "vkGetDeviceImageSparseMemoryRequirementsKHR",
    /*  488 */ "vkGetDeviceImageSubresourceLayout",
    /*  489 */ "vkGetDeviceImageSubresourceLayoutKHR",
    /*  490 */ "vkGetDeviceMemoryCommitment",
    /*  491 */ "vkGetDeviceMemoryOpaqueCaptureAddress",
    /*  492 */ "vkGetDeviceMemoryOpaqueCaptureAddressKHR",
    /*  493 */ "vkGetDeviceMicromapCompatibilityEXT",
    /*  494 */ "vkGetDeviceProcAddr",
    /*  495 */ "vkGetDeviceQueue",
    /*  496 */ "vkGetDeviceQueue2",
    /*  497 */ "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI",
    /*  498 */ "vkGetDisplayModeProperties2KHR",
    /*  499 */ "vkGetDisplayModePropertiesKHR",
    /*  500 */ "vkGetDisplayPlaneCapabilities2KHR",
    /*  501 */ "vkGetDisplayPlaneCapabilitiesKHR",
    /*  502 */ "vkGetDisplayPlaneSupportedDisplaysKHR",
    /*  503 */ "vkGetDrmDisplayEXT",
    /*  504 */ "vkGetDynamicRenderingTilePropertiesQCOM",
    /*  505 */ "vkGetEncodedVideoSessionParametersKHR",
    /*  506 */ "vkGetEventStatus",
    /*  507 */ "vkGetExecutionGraphPipelineNodeIndexAMDX",
    /*  508 */ "vkGetExecutionGraphPipelineScratchSizeAMDX",
    /*  509 */ "vkGetFenceFdKHR",
    /*  510 */ "vkGetFenceStatus",
    /*  511 */ "vkGetFenceWin32HandleKHR",
    /*  512 */ "vkGetFramebufferTilePropertiesQCOM",
    /*  513 */ "vkGetGeneratedCommandsMemoryRequirementsEXT",
    /*  514 */ "vkGetGeneratedCommandsMemoryRequirementsNV",
    /*  515 */ "vkGetImageDrmFormatModifierPropertiesEXT",
    /*  516 */ "vkGetImageMemoryRequirements",
    /*  517 */ "vkGetImageMemoryRequirements2",
    /*  518 */ "vkGetImageMemoryRequirements2KHR",
    /*  519 */ "vkGetImageOpaqueCaptureDescriptorDataEXT",
    /*  520 */ "vkGetImageSparseMemoryRequirements",
    /*  521 */ "vkGetImageSparseMemoryRequirements2",
    /*  522 */ "vkGetImageSparseMemoryRequirements2KHR",
    /*  523 */ "vkGetImageSubresourceLayout",
    /*  524 */ "vkGetImageSubresourceLayout2",
    /*  525 */ "vkGetImageSubresourceLayout2EXT",
    /*  526 */ "vkGetImageSubresourceLayout2KHR",
    /*  527 */ "vkGetImageViewAddressNVX",
    /*  528 */ "vkGetImageViewHandle64NVX",
    /*  529 */ "vkGetImageViewHandleNVX",
    /*  530 */ "vkGetImageViewOpaqueCaptureDescriptorDataEXT",
    /*  531 */ "vkGetInstanceProcAddr",
    /*  532 */ "vkGetLatencyTimingsNV",
    /*  533 */ "vkGetMemoryAndroidHardwareBufferANDROID",
    /*  534 */ "vkGetMemoryFdKHR",
    /*  535 */ "vkGetMemoryFdPropertiesKHR",
    /*  536 */ "vkGetMemoryHostPointerPropertiesEXT",
    /*  537 */ "vkGetMemoryMetalHandleEXT",
    /*  538 */ "vkGetMemoryMetalHandlePropertiesEXT",
    /*  539 */ "vkGetMemoryRemoteAddressNV",
    /*  540 */ "vkGetMemoryWin32HandleKHR",
    /*  541 */ "vkGetMemoryWin32HandleNV",
    /*  542 */ "vkGetMemoryWin32HandlePropertiesKHR",
    /*  543 */ "vkGetMemoryZirconHandleFUCHSIA",
    /*  544 */ "vkGetMemoryZirconHandlePropertiesFUCHSIA",
    /*  545 */ "vkGetMicromapBuildSizesEXT",
    /*  546 */ "vkGetPartitionedAccelerationStructuresBuildSizesNV",
    /*  547 */ "vkGetPastPresentationTimingGOOGLE",
    /*  548 */ "vkGetPerformanceParameterINTEL",
    /*  549 */ "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT",
    /*  550 */ "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR",
    /*  551 */ "vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV",
    /*  552 */ "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR",
    /*  553 */ "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV",
    /*  554 */ "vkGetPhysicalDeviceCooperativeVectorPropertiesNV",
    /*  555 */ "vkGetPhysicalDeviceDirectFBPresentationSupportEXT",
    /*  556 */ "vkGetPhysicalDeviceDisplayPlaneProperties2KHR",
    /*  557 */ "vkGetPhysicalDeviceDisplayPlanePropertiesKHR",
    /*  558 */ "vkGetPhysicalDeviceDisplayProperties2KHR",
    /*  559 */ "vkGetPhysicalDeviceDisplayPropertiesKHR",
    /*  560 */ "vkGetPhysicalDeviceExternalBufferProperties",
    /*  561 */ "vkGetPhysicalDeviceExternalBufferPropertiesKHR",
    /*  562 */ "vkGetPhysicalDeviceExternalFenceProperties",
    /*  563 */ "vkGetPhysicalDeviceExternalFencePropertiesKHR",
    /*  564 */ "vkGetPhysicalDeviceExternalImageFormatPropertiesNV",
    /*  565 */ "vkGetPhysicalDeviceExternalSemaphoreProperties",
    /*  566 */ "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR",
    /*  567 */ "vkGetPhysicalDeviceFeatures",
    /*  568 */ "vkGetPhysicalDeviceFeatures2",
    /*  569 */ "vkGetPhysicalDeviceFeatures2KHR",
    /*  570 */ "vkGetPhysicalDeviceFormatProperties",
    /*  571 */ "vkGetPhysicalDeviceFormatProperties2",
    /*  572 */ "vkGetPhysicalDeviceFormatProperties2KHR",
    /*  573 */ "vkGetPhysicalDeviceFragmentShadingRatesKHR",
    /*  574 */ "vkGetPhysicalDeviceImageFormatProperties",
    /*  575 */ "vkGetPhysicalDeviceImageFormatProperties2",
    /*  576 */ "vkGetPhysicalDeviceImageFormatProperties2KHR",
    /*  577 */ "vkGetPhysicalDeviceMemoryProperties",
    /*  578 */ "vkGetPhysicalDeviceMemoryProperties2",
    /*  579 */ "vkGetPhysicalDeviceMemoryProperties2KHR",
    /*  580 */ "vkGetPhysicalDeviceMultisamplePropertiesEXT",
    /*  581 */ "vkGetPhysicalDeviceOpticalFlowImageFormatsNV",
    /*  582 */ "vkGetPhysicalDevicePresentRectanglesKHR",
    /*  583 */ "vkGetPhysicalDeviceProperties",
    /*  584 */ "vkGetPhysicalDeviceProperties2",
    /*  585 */ "vkGetPhysicalDeviceProperties2KHR",
    /*  586 */ "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR",
    /*  587 */ "vkGetPhysicalDeviceQueueFamilyProperties",
    /*  588 */ "vkGetPhysicalDeviceQueueFamilyProperties2",
    /*  589 */ "vkGetPhysicalDeviceQueueFamilyProperties2KHR",
    /*  590 */ "vkGetPhysicalDeviceScreenPresentationSupportQNX",
    /*  591 */ "vkGetPhysicalDeviceSparseImageFormatProperties",
    /*  592 */ "vkGetPhysicalDeviceSparseImageFormatProperties2",
    /*  593 */ "vkGetPhysicalDeviceSparseImageFormatProperties2KHR",
    /*  594 */ "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV",
    /*  595 */ "vkGetPhysicalDeviceSurfaceCapabilities2EXT",
    /*  596 */ "vkGetPhysicalDeviceSurfaceCapabilities2KHR",
    /*  597 */ "vkGetPhysicalDeviceSurfaceCapabilitiesKHR",
    /*  598 */ "vkGetPhysicalDeviceSurfaceFormats2KHR",
    /*  599 */ "vkGetPhysicalDeviceSurfaceFormatsKHR",
    /*  600 */ "vkGetPhysicalDeviceSurfacePresentModes2EXT",
    /*  601 */ "vkGetPhysicalDeviceSurfacePresentModesKHR",
    /*  602 */ "vkGetPhysicalDeviceSurfaceSupportKHR",
    /*  603 */ "vkGetPhysicalDeviceToolProperties",
    /*  604 */ "vkGetPhysicalDeviceToolPropertiesEXT",
    /*  605 */ "vkGetPhysicalDeviceVideoCapabilitiesKHR",
    /*  606 */ "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR",
    /*  607 */ "vkGetPhysicalDeviceVideoFormatPropertiesKHR",
    /*  608 */ "vkGetPhysicalDeviceWaylandPresentationSupportKHR",
    /*  609 */ "vkGetPhysicalDeviceWin32PresentationSupportKHR",
    /*  610 */ "vkGetPhysicalDeviceXcbPresentationSupportKHR",
    /*  611 */ "vkGetPhysicalDeviceXlibPresentationSupportKHR",
    /*  612 */ "vkGetPipelineBinaryDataKHR",
    /*  613 */ "vkGetPipelineCacheData",
    /*  614 */ "vkGetPipelineExecutableInternalRepresentationsKHR",
    /*  615 */ "vkGetPipelineExecutablePropertiesKHR",
    /*  616 */ "vkGetPipelineExecutableStatisticsKHR",
    /*  617 */ "vkGetPipelineIndirectDeviceAddressNV",
    /*  618 */ "vkGetPipelineIndirectMemoryRequirementsNV",
    /*  619 */ "vkGetPipelineKeyKHR",
    /*  620 */ "vkGetPipelinePropertiesEXT",
    /*  621 */ "vkGetPrivateData",
    /*  622 */ "vkGetPrivateDataEXT",
    /*  623 */ "vkGetQueryPoolResults",
    /*  624 */ "vkGetQueueCheckpointData2NV",
    /*  625 */ "vkGetQueueCheckpointDataNV",
    /*  626 */ "vkGetRandROutputDisplayEXT",
    /*  627 */ "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR",
    /*  628 */ "vkGetRayTracingShaderGroupHandlesKHR",
    /*  629 */ "vkGetRayTracingShaderGroupHandlesNV",
    /*  630 */ "vkGetRayTracingShaderGroupStackSizeKHR",
    /*  631 */ "vkGetRefreshCycleDurationGOOGLE",
    /*  632 */ "vkGetRenderAreaGranularity",
    /*  633 */ "vkGetRenderingAreaGranularity",
    /*  634 */ "vkGetRenderingAreaGranularityKHR",
    /*  635 */ "vkGetSamplerOpaqueCaptureDescriptorDataEXT",
    /*  636 */ "vkGetScreenBufferPropertiesQNX",
    /*  637 */ "vkGetSemaphoreCounterValue",
    /*  638 */ "vkGetSemaphoreCounterValueKHR",
    /*  639 */ "vkGetSemaphoreFdKHR",
    /*  640 */ "vkGetSemaphoreWin32HandleKHR",
    /*  641 */ "vkGetSemaphoreZirconHandleFUCHSIA",
    /*  642 */ "vkGetShaderBinaryDataEXT",
    /*  643 */ "vkGetShaderInfoAMD",
    /*  644 */ "vkGetShaderModuleCreateInfoIdentifierEXT",
    /*  645 */ "vkGetShaderModuleIdentifierEXT",
    /*  646 */ "vkGetSwapchainCounterEXT",
    /*  647 */ "vkGetSwapchainImagesKHR",
    /*  648 */ "vkGetSwapchainStatusKHR",
    /*  649 */ "vkGetValidationCacheDataEXT",
    /*  650 */ "vkGetVideoSessionMemoryRequirementsKHR",
    /*  651 */ "vkGetWinrtDisplayNV",
    /*  652 */ "vkImportFenceFdKHR",
    /*  653 */ "vkImportFenceWin32HandleKHR",
    /*  654 */ "vkImportSemaphoreFdKHR",
    /*  655 */ "vkImportSemaphoreWin32HandleKHR",
    /*  656 */ "vkImportSemaphoreZirconHandleFUCHSIA",
    /*  657 */ "vkInitializePerformanceApiINTEL",
    /*  658 */ "vkInvalidateMappedMemoryRanges",
    /*  659 */ "vkLatencySleepNV",
    /*  660 */ "vkMapMemory",
    /*  661 */ "vkMapMemory2",
    /*  662 */ "vkMapMemory2KHR",
    /*  663 */ "vkMergePipelineCaches",
    /*  664 */ "vkMergeValidationCachesEXT",
    /*  665 */ "vkQueueBeginDebugUtilsLabelEXT",
    /*  666 */ "vkQueueBindSparse",
    /*  667 */ "vkQueueEndDebugUtilsLabelEXT",
    /*  668 */ "vkQueueInsertDebugUtilsLabelEXT",
    /*  669 */ "vkQueueNotifyOutOfBandNV",
    /*  670 */ "vkQueuePresentKHR",
    /*  671 */ "vkQueueSetPerformanceConfigurationINTEL",
    /*  672 */ "vkQueueSubmit",
    /*  673 */ "vkQueueSubmit2",
    /*  674 */ "vkQueueSubmit2KHR",
    /*  675 */ "vkQueueWaitIdle",
    /*  676 */ "vkRegisterDeviceEventEXT",
    /*  677 */ "vkRegisterDisplayEventEXT",
    /*  678 */ "vkReleaseCapturedPipelineDataKHR",
    /*  679 */ "vkReleaseDisplayEXT",
    /*  680 */ "vkReleaseFullScreenExclusiveModeEXT",
    /*  681 */ "vkReleasePerformanceConfigurationINTEL",
    /*  682 */ "vkReleaseProfilingLockKHR",
    /*  683 */ "vkReleaseSwapchainImagesEXT",
    /*  684 */ "vkResetCommandBuffer",
    /*  685 */ "vkResetCommandPool",
    /*  686 */ "vkResetDescriptorPool",
    /*  687 */ "vkResetEvent",
    /*  688 */ "vkResetFences",
    /*  689 */ "vkResetQueryPool",
    /*  690 */ "vkResetQueryPoolEXT",
    /*  691 */ "vkSetBufferCollectionBufferConstraintsFUCHSIA",
    /*  692 */ "vkSetBufferCollectionImageConstraintsFUCHSIA",
    /*  693 */ "vkSetDebugUtilsObjectNameEXT",
    /*  694 */ "vkSetDebugUtilsObjectTagEXT",
    /*  695 */ "vkSetDeviceMemoryPriorityEXT",
    /*  696 */ "vkSetEvent",
    /*  697 */ "vkSetHdrMetadataEXT",
    /*  698 */ "vkSetLatencyMarkerNV",
    /*  699 */ "vkSetLatencySleepModeNV",
    /*  700 */ "vkSetLocalDimmingAMD",
    /*  701 */ "vkSetPrivateData",
    /*  702 */ "vkSetPrivateDataEXT",
    /*  703 */ "vkSignalSemaphore",
    /*  704 */ "vkSignalSemaphoreKHR",
    /*  705 */ "vkSubmitDebugUtilsMessageEXT",
    /*  706 */ "vkTransitionImageLayout",
    /*  707 */ "vkTransitionImageLayoutEXT",
    /*  708 */ "vkTrimCommandPool",
    /*  709 */ "vkTrimCommandPoolKHR",
    /*  710 */ "vkUninitializePerformanceApiINTEL",
    /*  711 */ "vkUnmapMemory",
    /*  712 */ "vkUnmapMemory2",
    /*  713 */ "vkUnmapMemory2KHR",
    /*  714 */ "vkUpdateDescriptorSetWithTemplate",
    /*  715 */ "vkUpdateDescriptorSetWithTemplateKHR",
    /*  716 */ "vkUpdateDescriptorSets",
    /*  717 */ "vkUpdateIndirectExecutionSetPipelineEXT",
    /*  718 */ "vkUpdateIndirectExecutionSetShaderEXT",
    /*  719 */ "vkUpdateVideoSessionParametersKHR",
    /*  720 */ "vkWaitForFences",
    /*  721 */ "vkWaitForPresentKHR",
    /*  722 */ "vkWaitSemaphores",
    /*  723 */ "vkWaitSemaphoresKHR",
    /*  724 */ "vkWriteAccelerationStructuresPropertiesKHR",
    /*  725 */ "vkWriteMicromapsPropertiesEXT"
};

static uint64_t GLAD_Vulkan_ext_hashes[] = {
    /*    0 */ 0x6ae42d438bb0484c, /* VK_AMDX_shader_enqueue */
    /*    1 */ 0x141bdaf54e241180, /* VK_AMD_anti_lag */
    /*    2 */ 0x65ac43ace7243e04, /* VK_AMD_buffer_marker */
    /*    3 */ 0x8353850f5238ee1d, /* VK_AMD_device_coherent_memory */
    /*    4 */ 0x7f6d3eb981ed905a, /* VK_AMD_display_native_hdr */
    /*    5 */ 0x0b55dbb0df76886c, /* VK_AMD_draw_indirect_count */
    /*    6 */ 0xf3c87297143cbd5a, /* VK_AMD_gcn_shader */
    /*    7 */ 0xd16896d602d6c016, /* VK_AMD_gpu_shader_half_float */
    /*    8 */ 0x80dbf6d9994a8486, /* VK_AMD_gpu_shader_int16 */
    /*    9 */ 0x777abeda8eb885f2, /* VK_AMD_memory_overallocation_behavior */
    /*   10 */ 0x09abd53b962f7221, /* VK_AMD_mixed_attachment_samples */
    /*   11 */ 0x9f9cc0f84d49fc24, /* VK_AMD_negative_viewport_height */
    /*   12 */ 0xc4fcbc5045e4b55d, /* VK_AMD_pipeline_compiler_control */
    /*   13 */ 0x2b4b03257b517fe7, /* VK_AMD_rasterization_order */
    /*   14 */ 0x253e959bcd5e01e9, /* VK_AMD_shader_ballot */
    /*   15 */ 0x4cb3d15508759039, /* VK_AMD_shader_core_properties */
    /*   16 */ 0xe9de3bafe3e1e19a, /* VK_AMD_shader_core_properties2 */
    /*   17 */ 0xb9e9755d0b011c3f, /* VK_AMD_shader_early_and_late_fragment_tests */
    /*   18 */ 0x9564cc2b0038b597, /* VK_AMD_shader_explicit_vertex_parameter */
    /*   19 */ 0x2d734d0c4158eb7e, /* VK_AMD_shader_fragment_mask */
    /*   20 */ 0x1fd2270dcd52ad73, /* VK_AMD_shader_image_load_store_lod */
    /*   21 */ 0x62011d43d2d97594, /* VK_AMD_shader_info */
    /*   22 */ 0x48ef51e9f522215b, /* VK_AMD_shader_trinary_minmax */
    /*   23 */ 0x7e011534e1db7838, /* VK_AMD_texture_gather_bias_lod */
    /*   24 */ 0xee13e9584a79a866, /* VK_ANDROID_external_format_resolve */
    /*   25 */ 0x0efa9218af4eedaa, /* VK_ANDROID_external_memory_android_hardware_buffer */
    /*   26 */ 0x0f753497d22c514b, /* VK_ARM_pipeline_opacity_micromap */
    /*   27 */ 0x0afcd59fd2af6286, /* VK_ARM_rasterization_order_attachment_access */
    /*   28 */ 0x099508890a72c586, /* VK_ARM_render_pass_striped */
    /*   29 */ 0xcb5ebd8b3c00874c, /* VK_ARM_scheduling_controls */
    /*   30 */ 0x6d66a5a00c62648d, /* VK_ARM_shader_core_builtins */
    /*   31 */ 0x42f58e0f0c034d62, /* VK_ARM_shader_core_properties */
    /*   32 */ 0x9452c6992583027b, /* VK_EXT_4444_formats */
    /*   33 */ 0xc78e4b8ee4076491, /* VK_EXT_acquire_drm_display */
    /*   34 */ 0xf320bc0da89095cc, /* VK_EXT_acquire_xlib_display */
    /*   35 */ 0x1f2679f2f103d431, /* VK_EXT_astc_decode_mode */
    /*   36 */ 0xf27c39b3a1b079ad, /* VK_EXT_attachment_feedback_loop_dynamic_state */
    /*   37 */ 0x74d9e22c0880d05b, /* VK_EXT_attachment_feedback_loop_layout */
    /*   38 */ 0xbf40b1c2e2a175ca, /* VK_EXT_blend_operation_advanced */
    /*   39 */ 0xa7ae01d75b03a5fa, /* VK_EXT_border_color_swizzle */
    /*   40 */ 0x8cadd6ee8baeb7b6, /* VK_EXT_buffer_device_address */
    /*   41 */ 0xe53030d618c508b9, /* VK_EXT_calibrated_timestamps */
    /*   42 */ 0x1821c534e43e8bc2, /* VK_EXT_color_write_enable */
    /*   43 */ 0x3acaa19dcdfa4838, /* VK_EXT_conditional_rendering */
    /*   44 */ 0xbc479489c58aba55, /* VK_EXT_conservative_rasterization */
    /*   45 */ 0xd41fdd03d1591c42, /* VK_EXT_custom_border_color */
    /*   46 */ 0x13dd727d73e5c438, /* VK_EXT_debug_marker */
    /*   47 */ 0xefc5d6f86f5274aa, /* VK_EXT_debug_report */
    /*   48 */ 0x1f4cc1384fdd3124, /* VK_EXT_debug_utils */
    /*   49 */ 0x4334a6b5b2a8bcdf, /* VK_EXT_depth_bias_control */
    /*   50 */ 0x20b2ee75c46fae3b, /* VK_EXT_depth_clamp_control */
    /*   51 */ 0x42e03d02e07ee602, /* VK_EXT_depth_clamp_zero_one */
    /*   52 */ 0xc46ca287fec7bfa2, /* VK_EXT_depth_clip_control */
    /*   53 */ 0xb225ae836596c941, /* VK_EXT_depth_clip_enable */
    /*   54 */ 0x683e05b7c95cf871, /* VK_EXT_depth_range_unrestricted */
    /*   55 */ 0xff983b309bdf4f8f, /* VK_EXT_descriptor_buffer */
    /*   56 */ 0x8ed9a50d9652d13a, /* VK_EXT_descriptor_indexing */
    /*   57 */ 0x71042286279bf266, /* VK_EXT_device_address_binding_report */
    /*   58 */ 0x44712682d623c6ec, /* VK_EXT_device_fault */
    /*   59 */ 0x6c42eb1e4c30ed48, /* VK_EXT_device_generated_commands */
    /*   60 */ 0xfc8708a7a55a3b72, /* VK_EXT_device_memory_report */
    /*   61 */ 0x3d21adc07dc92de9, /* VK_EXT_direct_mode_display */
    /*   62 */ 0x2f377620d96a0b95, /* VK_EXT_directfb_surface */
    /*   63 */ 0x6c4b18b294f729e9, /* VK_EXT_discard_rectangles */
    /*   64 */ 0x2bd79b14ec35b405, /* VK_EXT_display_control */
    /*   65 */ 0xf82da0558a082445, /* VK_EXT_display_surface_counter */
    /*   66 */ 0x6c84fccd28668412, /* VK_EXT_dynamic_rendering_unused_attachments */
    /*   67 */ 0x405b3a7704a014a0, /* VK_EXT_extended_dynamic_state */
    /*   68 */ 0x09050069bac4e50b, /* VK_EXT_extended_dynamic_state2 */
    /*   69 */ 0x3e6696389e531962, /* VK_EXT_extended_dynamic_state3 */
    /*   70 */ 0x204d4d8537dc240c, /* VK_EXT_external_memory_acquire_unmodified */
    /*   71 */ 0xfbe83be92d0dc3e1, /* VK_EXT_external_memory_dma_buf */
    /*   72 */ 0xe730e90349447245, /* VK_EXT_external_memory_host */
    /*   73 */ 0xbb6a5bdb9f4339b2, /* VK_EXT_external_memory_metal */
    /*   74 */ 0x2ff4c771bf02a660, /* VK_EXT_filter_cubic */
    /*   75 */ 0xdd63dbab93498a89, /* VK_EXT_fragment_density_map */
    /*   76 */ 0x639aaec72634d6cc, /* VK_EXT_fragment_density_map2 */
    /*   77 */ 0xec38db4912e9aa39, /* VK_EXT_fragment_shader_interlock */
    /*   78 */ 0x4bed293561f471c5, /* VK_EXT_frame_boundary */
    /*   79 */ 0xf888a39f24346db4, /* VK_EXT_full_screen_exclusive */
    /*   80 */ 0x026fba6d706537f5, /* VK_EXT_global_priority */
    /*   81 */ 0x49240b90779ad742, /* VK_EXT_global_priority_query */
    /*   82 */ 0xe612048b33a20737, /* VK_EXT_graphics_pipeline_library */
    /*   83 */ 0xd140703366300180, /* VK_EXT_hdr_metadata */
    /*   84 */ 0xfc97df8c7f5cb62e, /* VK_EXT_headless_surface */
    /*   85 */ 0x15c6d3b4db750060, /* VK_EXT_host_image_copy */
    /*   86 */ 0xcc9a1964d5f92ead, /* VK_EXT_host_query_reset */
    /*   87 */ 0x992053b93ca7369a, /* VK_EXT_image_2d_view_of_3d */
    /*   88 */ 0xac673544b231a330, /* VK_EXT_image_compression_control */
    /*   89 */ 0xfc267e5b08be3c88, /* VK_EXT_image_compression_control_swapchain */
    /*   90 */ 0x5d78e7153c62776c, /* VK_EXT_image_drm_format_modifier */
    /*   91 */ 0xe918548d9d09bdf5, /* VK_EXT_image_robustness */
    /*   92 */ 0x10ea5ce8b7b462c6, /* VK_EXT_image_sliced_view_of_3d */
    /*   93 */ 0x5d125c6144d30072, /* VK_EXT_image_view_min_lod */
    /*   94 */ 0x66bb737b7652d71d, /* VK_EXT_index_type_uint8 */
    /*   95 */ 0x59f61f1cc23145ee, /* VK_EXT_inline_uniform_block */
    /*   96 */ 0x9ba2edc52691fc07, /* VK_EXT_layer_settings */
    /*   97 */ 0xa45ec0ff789f2882, /* VK_EXT_legacy_dithering */
    /*   98 */ 0x93eebd73e097d983, /* VK_EXT_legacy_vertex_attributes */
    /*   99 */ 0x98daf38a4cd796bc, /* VK_EXT_line_rasterization */
    /*  100 */ 0xca3cb4186d57fa40, /* VK_EXT_load_store_op_none */
    /*  101 */ 0xc92882ba73a7ad8a, /* VK_EXT_map_memory_placed */
    /*  102 */ 0xa642b55c0f467f26, /* VK_EXT_memory_budget */
    /*  103 */ 0xdf03e1a0a38154d2, /* VK_EXT_memory_priority */
    /*  104 */ 0x38a2a90e0a820189, /* VK_EXT_mesh_shader */
    /*  105 */ 0x6bcff1cd8cf418f2, /* VK_EXT_metal_objects */
    /*  106 */ 0x60fc707b7c19679c, /* VK_EXT_metal_surface */
    /*  107 */ 0x60ca462964877ba5, /* VK_EXT_multi_draw */
    /*  108 */ 0x60c608294e99436f, /* VK_EXT_multisampled_render_to_single_sampled */
    /*  109 */ 0x333da01be07c65e4, /* VK_EXT_mutable_descriptor_type */
    /*  110 */ 0x4f43f294a30fc75d, /* VK_EXT_nested_command_buffer */
    /*  111 */ 0x6cf77b70db09b037, /* VK_EXT_non_seamless_cube_map */
    /*  112 */ 0xb5bdb97dc49555ef, /* VK_EXT_opacity_micromap */
    /*  113 */ 0x74062e5990db1eeb, /* VK_EXT_pageable_device_local_memory */
    /*  114 */ 0xe60ea5fa872ffa4b, /* VK_EXT_pci_bus_info */
    /*  115 */ 0x087b96c0fac7f2e9, /* VK_EXT_physical_device_drm */
    /*  116 */ 0xae186881e629f533, /* VK_EXT_pipeline_creation_cache_control */
    /*  117 */ 0xd5ed321620183ae4, /* VK_EXT_pipeline_creation_feedback */
    /*  118 */ 0xf2497807f1195d03, /* VK_EXT_pipeline_library_group_handles */
    /*  119 */ 0x97816799b0ea2a08, /* VK_EXT_pipeline_properties */
    /*  120 */ 0x0bec2c70abec6edf, /* VK_EXT_pipeline_protected_access */
    /*  121 */ 0x3726d3c286b23305, /* VK_EXT_pipeline_robustness */
    /*  122 */ 0x578e2a9cdc320baa, /* VK_EXT_post_depth_coverage */
    /*  123 */ 0xdad3977856dd3ce4, /* VK_EXT_present_mode_fifo_latest_ready */
    /*  124 */ 0x4792bf3539da07a0, /* VK_EXT_primitive_topology_list_restart */
    /*  125 */ 0x4de3fc9eb140d3c9, /* VK_EXT_primitives_generated_query */
    /*  126 */ 0x66832604ff1fb25a, /* VK_EXT_private_data */
    /*  127 */ 0x3632448643e01277, /* VK_EXT_provoking_vertex */
    /*  128 */ 0xc3a80f57bc34acf0, /* VK_EXT_queue_family_foreign */
    /*  129 */ 0x9c47749ad3103e99, /* VK_EXT_rasterization_order_attachment_access */
    /*  130 */ 0xe3b61ff718cac048, /* VK_EXT_rgba10x6_formats */
    /*  131 */ 0x267337703fbb9802, /* VK_EXT_robustness2 */
    /*  132 */ 0xa2f0c46d62bffbbd, /* VK_EXT_sample_locations */
    /*  133 */ 0x35bc8d45855c9ddd, /* VK_EXT_sampler_filter_minmax */
    /*  134 */ 0x0fe7c2504b67f76e, /* VK_EXT_scalar_block_layout */
    /*  135 */ 0x21c315365bdd91c1, /* VK_EXT_separate_stencil_usage */
    /*  136 */ 0x39152af17d406387, /* VK_EXT_shader_atomic_float */
    /*  137 */ 0xfa5bf73b09f1814a, /* VK_EXT_shader_atomic_float2 */
    /*  138 */ 0x1313743aff740ea6, /* VK_EXT_shader_demote_to_helper_invocation */
    /*  139 */ 0xdbd208469e466661, /* VK_EXT_shader_image_atomic_int64 */
    /*  140 */ 0x0fdb11284e798630, /* VK_EXT_shader_module_identifier */
    /*  141 */ 0x01d57626cc2cb88b, /* VK_EXT_shader_object */
    /*  142 */ 0xd98565c5e8cff707, /* VK_EXT_shader_replicated_composites */
    /*  143 */ 0x1d5f02c289908dc6, /* VK_EXT_shader_stencil_export */
    /*  144 */ 0x3434e0e3856c3974, /* VK_EXT_shader_subgroup_ballot */
    /*  145 */ 0x414fe291cad1b8c2, /* VK_EXT_shader_subgroup_vote */
    /*  146 */ 0x15c81e1e3330c87a, /* VK_EXT_shader_tile_image */
    /*  147 */ 0x3ab7ae29a67149aa, /* VK_EXT_shader_viewport_index_layer */
    /*  148 */ 0xf8847bcd6077bcfc, /* VK_EXT_subgroup_size_control */
    /*  149 */ 0xc0a98929a3b5a629, /* VK_EXT_subpass_merge_feedback */
    /*  150 */ 0x745c764090230a6a, /* VK_EXT_surface_maintenance1 */
    /*  151 */ 0xaf7db52f12522284, /* VK_EXT_swapchain_colorspace */
    /*  152 */ 0xb8a530fd9b6e7826, /* VK_EXT_swapchain_maintenance1 */
    /*  153 */ 0x93820a855076e9ba, /* VK_EXT_texel_buffer_alignment */
    /*  154 */ 0xd54a2906947894c3, /* VK_EXT_texture_compression_astc_hdr */
    /*  155 */ 0xa176a37fe21bf722, /* VK_EXT_tooling_info */
    /*  156 */ 0x2c77e64693cba64b, /* VK_EXT_transform_feedback */
    /*  157 */ 0xd43b5b3257938a0c, /* VK_EXT_validation_cache */
    /*  158 */ 0x32e3bcc79655ff35, /* VK_EXT_validation_features */
    /*  159 */ 0x5dbef52d8325ef00, /* VK_EXT_validation_flags */
    /*  160 */ 0x41bd31eed71de48d, /* VK_EXT_vertex_attribute_divisor */
    /*  161 */ 0x384a29f8cf6d87bf, /* VK_EXT_vertex_attribute_robustness */
    /*  162 */ 0xdba593667f2b15d8, /* VK_EXT_vertex_input_dynamic_state */
    /*  163 */ 0xdc68cb4b50c6a206, /* VK_EXT_ycbcr_2plane_444_formats */
    /*  164 */ 0x7f0e4b169ce6683e, /* VK_EXT_ycbcr_image_arrays */
    /*  165 */ 0x4ad21727cd459ae0, /* VK_FUCHSIA_buffer_collection */
    /*  166 */ 0x39a61a1dde950a7e, /* VK_FUCHSIA_external_memory */
    /*  167 */ 0xf64c61e8709735f7, /* VK_FUCHSIA_external_semaphore */
    /*  168 */ 0x78bbdf52d016b408, /* VK_FUCHSIA_imagepipe_surface */
    /*  169 */ 0x7f2da9be6e1b04db, /* VK_GGP_frame_token */
    /*  170 */ 0xcd04d110dd619891, /* VK_GGP_stream_descriptor_surface */
    /*  171 */ 0x66d124637ca67c9b, /* VK_GOOGLE_decorate_string */
    /*  172 */ 0xd317975f41d1a234, /* VK_GOOGLE_display_timing */
    /*  173 */ 0x434a8c02c305c9d2, /* VK_GOOGLE_hlsl_functionality1 */
    /*  174 */ 0xdb384c83fb23b324, /* VK_GOOGLE_surfaceless_query */
    /*  175 */ 0x8ea5be2adce92628, /* VK_GOOGLE_user_type */
    /*  176 */ 0x1251619c17f44f75, /* VK_HUAWEI_cluster_culling_shader */
    /*  177 */ 0x734dc9a82ce2a812, /* VK_HUAWEI_hdr_vivid */
    /*  178 */ 0x23cb6d9b631ae3de, /* VK_HUAWEI_invocation_mask */
    /*  179 */ 0x7a080c6eb36cfa62, /* VK_HUAWEI_subpass_shading */
    /*  180 */ 0xc831730562583c7f, /* VK_IMG_filter_cubic */
    /*  181 */ 0x2770027508eb9598, /* VK_IMG_format_pvrtc */
    /*  182 */ 0xb0257135e659f035, /* VK_IMG_relaxed_line_rasterization */
    /*  183 */ 0xde48a4b9c28f1a76, /* VK_INTEL_performance_query */
    /*  184 */ 0x1cdbef97960a8e84, /* VK_INTEL_shader_integer_functions2 */
    /*  185 */ 0x8febc131b31f03a7, /* VK_KHR_16bit_storage */
    /*  186 */ 0xfc675d0c9be11933, /* VK_KHR_8bit_storage */
    /*  187 */ 0xfd487833d05a912e, /* VK_KHR_acceleration_structure */
    /*  188 */ 0x29df4e2582c4e5eb, /* VK_KHR_android_surface */
    /*  189 */ 0xc441ac340c33f00e, /* VK_KHR_bind_memory2 */
    /*  190 */ 0xed3998734610578e, /* VK_KHR_buffer_device_address */
    /*  191 */ 0xf6b15d82867a4cc7, /* VK_KHR_calibrated_timestamps */
    /*  192 */ 0x0afe9b38bfc3ce2c, /* VK_KHR_compute_shader_derivatives */
    /*  193 */ 0x2349bf032cef96df, /* VK_KHR_cooperative_matrix */
    /*  194 */ 0x8037af99654ff021, /* VK_KHR_copy_commands2 */
    /*  195 */ 0x45e78547df004126, /* VK_KHR_create_renderpass2 */
    /*  196 */ 0x78b51eb267ba222a, /* VK_KHR_dedicated_allocation */
    /*  197 */ 0x94de08b35a6241ca, /* VK_KHR_deferred_host_operations */
    /*  198 */ 0xc379ca87fcbfe646, /* VK_KHR_depth_clamp_zero_one */
    /*  199 */ 0x8c49a14f4e053827, /* VK_KHR_depth_stencil_resolve */
    /*  200 */ 0xd0e490f381b744be, /* VK_KHR_descriptor_update_template */
    /*  201 */ 0xc6ca78c5b314bc87, /* VK_KHR_device_group */
    /*  202 */ 0x8585cbd14f1c0cac, /* VK_KHR_device_group_creation */
    /*  203 */ 0x2859d74f3639d0b1, /* VK_KHR_display */
    /*  204 */ 0xe6851c4675917263, /* VK_KHR_display_swapchain */
    /*  205 */ 0x0337556153ae8299, /* VK_KHR_draw_indirect_count */
    /*  206 */ 0x2fa1beee71b55c4a, /* VK_KHR_driver_properties */
    /*  207 */ 0xcec518255e3db5bd, /* VK_KHR_dynamic_rendering */
    /*  208 */ 0x3aff0fddef25484a, /* VK_KHR_dynamic_rendering_local_read */
    /*  209 */ 0x042831872b90006c, /* VK_KHR_external_fence */
    /*  210 */ 0x5f78dae679457682, /* VK_KHR_external_fence_capabilities */
    /*  211 */ 0xcd3a8c2ddf5addf6, /* VK_KHR_external_fence_fd */
    /*  212 */ 0x4c03e948c552a900, /* VK_KHR_external_fence_win32 */
    /*  213 */ 0x87d94faee5024129, /* VK_KHR_external_memory */
    /*  214 */ 0x3f3f36a8f61bdd88, /* VK_KHR_external_memory_capabilities */
    /*  215 */ 0x552d385fc1022139, /* VK_KHR_external_memory_fd */
    /*  216 */ 0x92cd58bc47a696d9, /* VK_KHR_external_memory_win32 */
    /*  217 */ 0x7e7e947a025884c1, /* VK_KHR_external_semaphore */
    /*  218 */ 0xb7268870e382881b, /* VK_KHR_external_semaphore_capabilities */
    /*  219 */ 0x089c9b49df8b6f1e, /* VK_KHR_external_semaphore_fd */
    /*  220 */ 0x014c9621dbd33d31, /* VK_KHR_external_semaphore_win32 */
    /*  221 */ 0x9310a82971542c4a, /* VK_KHR_format_feature_flags2 */
    /*  222 */ 0x2aedf5bc87e7dd6d, /* VK_KHR_fragment_shader_barycentric */
    /*  223 */ 0x8496cee01f4fa6d5, /* VK_KHR_fragment_shading_rate */
    /*  224 */ 0x6c023bc9dc523d46, /* VK_KHR_get_display_properties2 */
    /*  225 */ 0x9eb7bb6c3705f946, /* VK_KHR_get_memory_requirements2 */
    /*  226 */ 0x7685eeed9cac9798, /* VK_KHR_get_physical_device_properties2 */
    /*  227 */ 0x9b0fbb8eeee0e74b, /* VK_KHR_get_surface_capabilities2 */
    /*  228 */ 0x0bb91b137617fbef, /* VK_KHR_global_priority */
    /*  229 */ 0xfb7c493b280e7035, /* VK_KHR_image_format_list */
    /*  230 */ 0x6ba09c8a87af68ce, /* VK_KHR_imageless_framebuffer */
    /*  231 */ 0x76a0d6d17ae91b81, /* VK_KHR_incremental_present */
    /*  232 */ 0x3dde8d8eb0b76315, /* VK_KHR_index_type_uint8 */
    /*  233 */ 0x7928ca2523362ef3, /* VK_KHR_line_rasterization */
    /*  234 */ 0xc8692b97cfbe45ad, /* VK_KHR_load_store_op_none */
    /*  235 */ 0xe3c8335cc1581a67, /* VK_KHR_maintenance1 */
    /*  236 */ 0x8ffe792f51cd1450, /* VK_KHR_maintenance2 */
    /*  237 */ 0xea219cc76502a8af, /* VK_KHR_maintenance3 */
    /*  238 */ 0xa66e463f036dae4a, /* VK_KHR_maintenance4 */
    /*  239 */ 0xc5e86b535cee6698, /* VK_KHR_maintenance5 */
    /*  240 */ 0xf60b7de240a15ab4, /* VK_KHR_maintenance6 */
    /*  241 */ 0x3d59040ce3c13f21, /* VK_KHR_maintenance7 */
    /*  242 */ 0xb6892d36c521b488, /* VK_KHR_maintenance8 */
    /*  243 */ 0x64d252cf56a64add, /* VK_KHR_map_memory2 */
    /*  244 */ 0x5af12378bc6d7169, /* VK_KHR_multiview */
    /*  245 */ 0x1bb74dfe8d7e0b31, /* VK_KHR_performance_query */
    /*  246 */ 0x935d834a6c18d3ed, /* VK_KHR_pipeline_binary */
    /*  247 */ 0x91248c6b162c4180, /* VK_KHR_pipeline_executable_properties */
    /*  248 */ 0x039c65d87fb09ca9, /* VK_KHR_pipeline_library */
    /*  249 */ 0x28644eeb112058b6, /* VK_KHR_portability_enumeration */
    /*  250 */ 0xac06576b97f9486a, /* VK_KHR_portability_subset */
    /*  251 */ 0xe82e301141092b1e, /* VK_KHR_present_id */
    /*  252 */ 0x47954f24ddf5185e, /* VK_KHR_present_wait */
    /*  253 */ 0x2123bacd888c07ec, /* VK_KHR_push_descriptor */
    /*  254 */ 0x8bf873804879f2cf, /* VK_KHR_ray_query */
    /*  255 */ 0x9df3df162357e4b0, /* VK_KHR_ray_tracing_maintenance1 */
    /*  256 */ 0xaef707cb154a81af, /* VK_KHR_ray_tracing_pipeline */
    /*  257 */ 0x697f77ef7ba14203, /* VK_KHR_ray_tracing_position_fetch */
    /*  258 */ 0x4b17e19fd947a1d3, /* VK_KHR_relaxed_block_layout */
    /*  259 */ 0x5d5e936103817cda, /* VK_KHR_sampler_mirror_clamp_to_edge */
    /*  260 */ 0x22004cfa79ba7177, /* VK_KHR_sampler_ycbcr_conversion */
    /*  261 */ 0xba2c0ae86fd11630, /* VK_KHR_separate_depth_stencil_layouts */
    /*  262 */ 0xb16f5fd69d97f3a1, /* VK_KHR_shader_atomic_int64 */
    /*  263 */ 0xeee9708671fa7c77, /* VK_KHR_shader_clock */
    /*  264 */ 0xb35fc4bdb32f3d81, /* VK_KHR_shader_draw_parameters */
    /*  265 */ 0xab0eda6676f1fd31, /* VK_KHR_shader_expect_assume */
    /*  266 */ 0x4dad563cb513c7c9, /* VK_KHR_shader_float16_int8 */
    /*  267 */ 0x548b20a76c855b46, /* VK_KHR_shader_float_controls */
    /*  268 */ 0xa1150eef92f851e8, /* VK_KHR_shader_float_controls2 */
    /*  269 */ 0x9d14cd5379daf7cb, /* VK_KHR_shader_integer_dot_product */
    /*  270 */ 0x42aefa5598fde4ab, /* VK_KHR_shader_maximal_reconvergence */
    /*  271 */ 0xb38332d7467f8474, /* VK_KHR_shader_non_semantic_info */
    /*  272 */ 0xab3f0af6d5504bf4, /* VK_KHR_shader_quad_control */
    /*  273 */ 0x1bdfe042874be24f, /* VK_KHR_shader_relaxed_extended_instruction */
    /*  274 */ 0xcda588b0d067d48f, /* VK_KHR_shader_subgroup_extended_types */
    /*  275 */ 0xd0836c7a4d04b579, /* VK_KHR_shader_subgroup_rotate */
    /*  276 */ 0x64fbf5bc74afe199, /* VK_KHR_shader_subgroup_uniform_control_flow */
    /*  277 */ 0x6e5fde40560b40a9, /* VK_KHR_shader_terminate_invocation */
    /*  278 */ 0x7e6871b03dee137b, /* VK_KHR_shared_presentable_image */
    /*  279 */ 0x06c03c1c3db9815d, /* VK_KHR_spirv_1_4 */
    /*  280 */ 0x743f86c26df32ea2, /* VK_KHR_storage_buffer_storage_class */
    /*  281 */ 0x2c4f009293a35548, /* VK_KHR_surface */
    /*  282 */ 0xa8506d9aef558591, /* VK_KHR_surface_protected_capabilities */
    /*  283 */ 0x6cefabf4c944ccec, /* VK_KHR_swapchain */
    /*  284 */ 0x2149e839e759e400, /* VK_KHR_swapchain_mutable_format */
    /*  285 */ 0xf1cfa2ea69e6ec0e, /* VK_KHR_synchronization2 */
    /*  286 */ 0x61ed378f50459bf2, /* VK_KHR_timeline_semaphore */
    /*  287 */ 0x3334ed809879d360, /* VK_KHR_uniform_buffer_standard_layout */
    /*  288 */ 0x6146df22dcb09470, /* VK_KHR_variable_pointers */
    /*  289 */ 0xcfd1e6704e4a4227, /* VK_KHR_vertex_attribute_divisor */
    /*  290 */ 0x4ccc16568a9a2944, /* VK_KHR_video_decode_av1 */
    /*  291 */ 0x0093b60d00888052, /* VK_KHR_video_decode_h264 */
    /*  292 */ 0x4116f6bec0017e79, /* VK_KHR_video_decode_h265 */
    /*  293 */ 0x363dac5e35a2f1ee, /* VK_KHR_video_decode_queue */
    /*  294 */ 0x35e683e888a7a54c, /* VK_KHR_video_encode_av1 */
    /*  295 */ 0xa77247c5899dc785, /* VK_KHR_video_encode_h264 */
    /*  296 */ 0x8b86366e33c748ee, /* VK_KHR_video_encode_h265 */
    /*  297 */ 0x3f1a8c895b8e8deb, /* VK_KHR_video_encode_quantization_map */
    /*  298 */ 0xdda14264a3bda234, /* VK_KHR_video_encode_queue */
    /*  299 */ 0x9fb8181989e29256, /* VK_KHR_video_maintenance1 */
    /*  300 */ 0xfd1949eb2a3c752b, /* VK_KHR_video_maintenance2 */
    /*  301 */ 0xc3d1c9b40515a6a4, /* VK_KHR_video_queue */
    /*  302 */ 0x34899ec7a7b17614, /* VK_KHR_vulkan_memory_model */
    /*  303 */ 0x906fcab3e0d202a5, /* VK_KHR_wayland_surface */
    /*  304 */ 0x19d48609837c8701, /* VK_KHR_win32_keyed_mutex */
    /*  305 */ 0xc93557e7cef43233, /* VK_KHR_win32_surface */
    /*  306 */ 0x75ee32f09cdd8db9, /* VK_KHR_workgroup_memory_explicit_layout */
    /*  307 */ 0x32a481baaa637e2c, /* VK_KHR_xcb_surface */
    /*  308 */ 0x863c0e309551346e, /* VK_KHR_xlib_surface */
    /*  309 */ 0x58d24a21f116065b, /* VK_KHR_zero_initialize_workgroup_memory */
    /*  310 */ 0x5615881540a7f6d8, /* VK_LUNARG_direct_driver_loading */
    /*  311 */ 0x6f8fb9c8b46fc189, /* VK_MESA_image_alignment_control */
    /*  312 */ 0xc1c930637836bf44, /* VK_MSFT_layered_driver */
    /*  313 */ 0x489cf2a16640d39e, /* VK_MVK_ios_surface */
    /*  314 */ 0x3274c65edf45286c, /* VK_MVK_macos_surface */
    /*  315 */ 0x53643314731ac57a, /* VK_NN_vi_surface */
    /*  316 */ 0x5bf53745255ccc0e, /* VK_NVX_binary_import */
    /*  317 */ 0x20b59934a97efd1c, /* VK_NVX_image_view_handle */
    /*  318 */ 0x112ee8733e2b22b3, /* VK_NVX_multiview_per_view_attributes */
    /*  319 */ 0x71fe862eee072b1e, /* VK_NV_acquire_winrt_display */
    /*  320 */ 0x9217a69de789d3fe, /* VK_NV_clip_space_w_scaling */
    /*  321 */ 0x5d2cfdaf5ecc308b, /* VK_NV_cluster_acceleration_structure */
    /*  322 */ 0xad1ba91484f69ca3, /* VK_NV_command_buffer_inheritance */
    /*  323 */ 0x21d19e30b520bdd6, /* VK_NV_compute_shader_derivatives */
    /*  324 */ 0x069e842b3b51cefb, /* VK_NV_cooperative_matrix */
    /*  325 */ 0xfecfd80519026209, /* VK_NV_cooperative_matrix2 */
    /*  326 */ 0x9b6d5b7725490586, /* VK_NV_cooperative_vector */
    /*  327 */ 0xce889f8d6b40e84f, /* VK_NV_copy_memory_indirect */
    /*  328 */ 0xed85b1ac0329a8cd, /* VK_NV_corner_sampled_image */
    /*  329 */ 0x81b617790445f852, /* VK_NV_coverage_reduction_mode */
    /*  330 */ 0x3644690c3bd14289, /* VK_NV_cuda_kernel_launch */
    /*  331 */ 0xbb81f8243fcc7db5, /* VK_NV_dedicated_allocation */
    /*  332 */ 0x00ce18bba106c2ad, /* VK_NV_dedicated_allocation_image_aliasing */
    /*  333 */ 0x23bcacd889bea60c, /* VK_NV_descriptor_pool_overallocation */
    /*  334 */ 0xf03dfd81ad17796f, /* VK_NV_device_diagnostic_checkpoints */
    /*  335 */ 0xc8050fbd31afc5b5, /* VK_NV_device_diagnostics_config */
    /*  336 */ 0xee7bfcd5523cff09, /* VK_NV_device_generated_commands */
    /*  337 */ 0x2ff0ded4f3f040e9, /* VK_NV_device_generated_commands_compute */
    /*  338 */ 0xc07b5e2a89ddc607, /* VK_NV_displacement_micromap */
    /*  339 */ 0x5138c2f68bcb3608, /* VK_NV_display_stereo */
    /*  340 */ 0xb2344e462fd9ef1b, /* VK_NV_extended_sparse_address_space */
    /*  341 */ 0xab0f59a00375b1ec, /* VK_NV_external_memory */
    /*  342 */ 0x518148eb9166b4b9, /* VK_NV_external_memory_capabilities */
    /*  343 */ 0x3c96386b301a3cdc, /* VK_NV_external_memory_rdma */
    /*  344 */ 0xcf69c3e7cbd068e4, /* VK_NV_external_memory_win32 */
    /*  345 */ 0xdf9a65a432a12606, /* VK_NV_fill_rectangle */
    /*  346 */ 0x9a6fda1e2f4f9096, /* VK_NV_fragment_coverage_to_color */
    /*  347 */ 0xc294d55a56858fb6, /* VK_NV_fragment_shader_barycentric */
    /*  348 */ 0x2ece12f465807058, /* VK_NV_fragment_shading_rate_enums */
    /*  349 */ 0x4caba51b111c61b9, /* VK_NV_framebuffer_mixed_samples */
    /*  350 */ 0xe0c4918343f3874c, /* VK_NV_geometry_shader_passthrough */
    /*  351 */ 0xd659873b3f6bc024, /* VK_NV_glsl_shader */
    /*  352 */ 0xe39346d87fc9aa45, /* VK_NV_inherited_viewport_scissor */
    /*  353 */ 0x52fcc4c2d713dad4, /* VK_NV_linear_color_attachment */
    /*  354 */ 0xb58daf9c015becf7, /* VK_NV_low_latency */
    /*  355 */ 0xa9eb852dfd7a1ece, /* VK_NV_low_latency2 */
    /*  356 */ 0x6c878fdbf1e4a7fb, /* VK_NV_memory_decompression */
    /*  357 */ 0x7401a89f84bc926b, /* VK_NV_mesh_shader */
    /*  358 */ 0x929112526891454e, /* VK_NV_optical_flow */
    /*  359 */ 0x6e9d1f60324c4761, /* VK_NV_partitioned_acceleration_structure */
    /*  360 */ 0x5e0416a20f89c9f4, /* VK_NV_per_stage_descriptor_set */
    /*  361 */ 0x48102b2d563a8028, /* VK_NV_present_barrier */
    /*  362 */ 0xe16f6927a8473cab, /* VK_NV_present_metering */
    /*  363 */ 0xc20950e0cbc5bdc0, /* VK_NV_raw_access_chains */
    /*  364 */ 0x3d4e9e0bb54735fe, /* VK_NV_ray_tracing */
    /*  365 */ 0xe12f14699c6db9db, /* VK_NV_ray_tracing_invocation_reorder */
    /*  366 */ 0x4157611d54ac1bc1, /* VK_NV_ray_tracing_linear_swept_spheres */
    /*  367 */ 0xba4184e5104338cb, /* VK_NV_ray_tracing_motion_blur */
    /*  368 */ 0x451532c42bd881b2, /* VK_NV_ray_tracing_validation */
    /*  369 */ 0x92ccabdfa0a3d6e4, /* VK_NV_representative_fragment_test */
    /*  370 */ 0xc4d99252b7b7843f, /* VK_NV_sample_mask_override_coverage */
    /*  371 */ 0xd4d2cda699fc74ae, /* VK_NV_scissor_exclusive */
    /*  372 */ 0xb8974b1af4c34b58, /* VK_NV_shader_atomic_float16_vector */
    /*  373 */ 0x52f9f98f09f18085, /* VK_NV_shader_image_footprint */
    /*  374 */ 0xc394473a75e21d7c, /* VK_NV_shader_sm_builtins */
    /*  375 */ 0x5b6c5e76d8a8364e, /* VK_NV_shader_subgroup_partitioned */
    /*  376 */ 0xcac204d487e563d3, /* VK_NV_shading_rate_image */
    /*  377 */ 0xfc6e35d06ddf634e, /* VK_NV_viewport_array2 */
    /*  378 */ 0x7748ea26eecd7e90, /* VK_NV_viewport_swizzle */
    /*  379 */ 0x7e4ac6b10102b887, /* VK_NV_win32_keyed_mutex */
    /*  380 */ 0x5c76ad884426c86c, /* VK_QCOM_filter_cubic_clamp */
    /*  381 */ 0xc7386bbfd1b9b423, /* VK_QCOM_filter_cubic_weights */
    /*  382 */ 0xff445069da66b635, /* VK_QCOM_fragment_density_map_offset */
    /*  383 */ 0xa6cab4106375cdfa, /* VK_QCOM_image_processing */
    /*  384 */ 0xa4a1ae34c2527a4a, /* VK_QCOM_image_processing2 */
    /*  385 */ 0xbff750af2234e2ce, /* VK_QCOM_multiview_per_view_render_areas */
    /*  386 */ 0x876a51c6df08420a, /* VK_QCOM_multiview_per_view_viewports */
    /*  387 */ 0xa3b4fc40f185c799, /* VK_QCOM_render_pass_shader_resolve */
    /*  388 */ 0x9b5c2a0bc41e00cd, /* VK_QCOM_render_pass_store_ops */
    /*  389 */ 0x8d33cd618c723019, /* VK_QCOM_render_pass_transform */
    /*  390 */ 0xd5a3f971e2e8b5c9, /* VK_QCOM_rotated_copy_commands */
    /*  391 */ 0xc37b456dbdf5565f, /* VK_QCOM_tile_properties */
    /*  392 */ 0x49bfbd9f92e0b029, /* VK_QCOM_ycbcr_degamma */
    /*  393 */ 0xc2e6f6dcc7614ace, /* VK_QNX_external_memory_screen_buffer */
    /*  394 */ 0x236bd86b3b17cf06, /* VK_QNX_screen_surface */
    /*  395 */ 0xe6fed416ddebf8d0, /* VK_SEC_amigo_profiling */
    /*  396 */ 0x45542cac22bd41a7, /* VK_VALVE_descriptor_set_host_mapping */
    /*  397 */ 0x38c73d4ab66a4942  /* VK_VALVE_mutable_descriptor_type */
};

static void glad_vk_load_pfns(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr, const uint16_t *pPfnIdx, uint32_t numPfns)
{
    uint32_t i;

    #ifdef __clang__
    #pragma nounroll
    #endif
    for (i = 0; i < numPfns; ++i) {
        const uint16_t pfnIdx = pPfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_VERSION_1_0(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           8, /* vkAllocateCommandBuffers */
           9, /* vkAllocateDescriptorSets */
          10, /* vkAllocateMemory */
          12, /* vkBeginCommandBuffer */
          14, /* vkBindBufferMemory */
          17, /* vkBindImageMemory */
          26, /* vkCmdBeginQuery */
          28, /* vkCmdBeginRenderPass */
          38, /* vkCmdBindDescriptorSets */
          41, /* vkCmdBindIndexBuffer */
          45, /* vkCmdBindPipeline */
          50, /* vkCmdBindVertexBuffers */
          53, /* vkCmdBlitImage */
          62, /* vkCmdClearAttachments */
          63, /* vkCmdClearColorImage */
          64, /* vkCmdClearDepthStencilImage */
          70, /* vkCmdCopyBuffer */
          73, /* vkCmdCopyBufferToImage */
          76, /* vkCmdCopyImage */
          79, /* vkCmdCopyImageToBuffer */
          88, /* vkCmdCopyQueryPoolResults */
          97, /* vkCmdDispatch */
         103, /* vkCmdDispatchIndirect */
         104, /* vkCmdDraw */
         107, /* vkCmdDrawIndexed */
         108, /* vkCmdDrawIndexedIndirect */
         112, /* vkCmdDrawIndirect */
         128, /* vkCmdEndQuery */
         130, /* vkCmdEndRenderPass */
         137, /* vkCmdExecuteCommands */
         140, /* vkCmdFillBuffer */
         143, /* vkCmdNextSubpass */
         147, /* vkCmdPipelineBarrier */
         152, /* vkCmdPushConstants */
         163, /* vkCmdResetEvent */
         166, /* vkCmdResetQueryPool */
         167, /* vkCmdResolveImage */
         173, /* vkCmdSetBlendConstants */
         190, /* vkCmdSetDepthBias */
         194, /* vkCmdSetDepthBounds */
         214, /* vkCmdSetEvent */
         229, /* vkCmdSetLineWidth */
         255, /* vkCmdSetScissor */
         259, /* vkCmdSetStencilCompareMask */
         262, /* vkCmdSetStencilReference */
         265, /* vkCmdSetStencilWriteMask */
         268, /* vkCmdSetViewport */
         280, /* vkCmdUpdateBuffer */
         282, /* vkCmdWaitEvents */
         290, /* vkCmdWriteTimestamp */
         310, /* vkCreateBuffer */
         312, /* vkCreateBufferView */
         313, /* vkCreateCommandPool */
         314, /* vkCreateComputePipelines */
         322, /* vkCreateDescriptorPool */
         323, /* vkCreateDescriptorSetLayout */
         326, /* vkCreateDevice */
         330, /* vkCreateEvent */
         332, /* vkCreateFence */
         333, /* vkCreateFramebuffer */
         334, /* vkCreateGraphicsPipelines */
         337, /* vkCreateImage */
         339, /* vkCreateImageView */
         343, /* vkCreateInstance */
         349, /* vkCreatePipelineCache */
         350, /* vkCreatePipelineLayout */
         353, /* vkCreateQueryPool */
         356, /* vkCreateRenderPass */
         359, /* vkCreateSampler */
         363, /* vkCreateSemaphore */
         364, /* vkCreateShaderModule */
         383, /* vkDestroyBuffer */
         385, /* vkDestroyBufferView */
         386, /* vkDestroyCommandPool */
         394, /* vkDestroyDescriptorPool */
         395, /* vkDestroyDescriptorSetLayout */
         398, /* vkDestroyDevice */
         399, /* vkDestroyEvent */
         400, /* vkDestroyFence */
         401, /* vkDestroyFramebuffer */
         402, /* vkDestroyImage */
         403, /* vkDestroyImageView */
         407, /* vkDestroyInstance */
         410, /* vkDestroyPipeline */
         412, /* vkDestroyPipelineCache */
         413, /* vkDestroyPipelineLayout */
         416, /* vkDestroyQueryPool */
         417, /* vkDestroyRenderPass */
         418, /* vkDestroySampler */
         421, /* vkDestroySemaphore */
         423, /* vkDestroyShaderModule */
         429, /* vkDeviceWaitIdle */
         431, /* vkEndCommandBuffer */
         432, /* vkEnumerateDeviceExtensionProperties */
         433, /* vkEnumerateDeviceLayerProperties */
         434, /* vkEnumerateInstanceExtensionProperties */
         435, /* vkEnumerateInstanceLayerProperties */
         440, /* vkEnumeratePhysicalDevices */
         442, /* vkFlushMappedMemoryRanges */
         443, /* vkFreeCommandBuffers */
         444, /* vkFreeDescriptorSets */
         445, /* vkFreeMemory */
         456, /* vkGetBufferMemoryRequirements */
         490, /* vkGetDeviceMemoryCommitment */
         494, /* vkGetDeviceProcAddr */
         495, /* vkGetDeviceQueue */
         506, /* vkGetEventStatus */
         510, /* vkGetFenceStatus */
         516, /* vkGetImageMemoryRequirements */
         520, /* vkGetImageSparseMemoryRequirements */
         523, /* vkGetImageSubresourceLayout */
         531, /* vkGetInstanceProcAddr */
         567, /* vkGetPhysicalDeviceFeatures */
         570, /* vkGetPhysicalDeviceFormatProperties */
         574, /* vkGetPhysicalDeviceImageFormatProperties */
         577, /* vkGetPhysicalDeviceMemoryProperties */
         583, /* vkGetPhysicalDeviceProperties */
         587, /* vkGetPhysicalDeviceQueueFamilyProperties */
         591, /* vkGetPhysicalDeviceSparseImageFormatProperties */
         613, /* vkGetPipelineCacheData */
         623, /* vkGetQueryPoolResults */
         632, /* vkGetRenderAreaGranularity */
         658, /* vkInvalidateMappedMemoryRanges */
         660, /* vkMapMemory */
         663, /* vkMergePipelineCaches */
         666, /* vkQueueBindSparse */
         672, /* vkQueueSubmit */
         675, /* vkQueueWaitIdle */
         684, /* vkResetCommandBuffer */
         685, /* vkResetCommandPool */
         686, /* vkResetDescriptorPool */
         687, /* vkResetEvent */
         688, /* vkResetFences */
         696, /* vkSetEvent */
         711, /* vkUnmapMemory */
         716, /* vkUpdateDescriptorSets */
         720  /* vkWaitForFences */
    };
    if (!context->VERSION_1_0) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_VERSION_1_1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          15, /* vkBindBufferMemory2 */
          18, /* vkBindImageMemory2 */
          98, /* vkCmdDispatchBase */
         209, /* vkCmdSetDeviceMask */
         324, /* vkCreateDescriptorUpdateTemplate */
         360, /* vkCreateSamplerYcbcrConversion */
         396, /* vkDestroyDescriptorUpdateTemplate */
         419, /* vkDestroySamplerYcbcrConversion */
         436, /* vkEnumerateInstanceVersion */
         437, /* vkEnumeratePhysicalDeviceGroups */
         457, /* vkGetBufferMemoryRequirements2 */
         473, /* vkGetDescriptorSetLayoutSupport */
         479, /* vkGetDeviceGroupPeerMemoryFeatures */
         496, /* vkGetDeviceQueue2 */
         517, /* vkGetImageMemoryRequirements2 */
         521, /* vkGetImageSparseMemoryRequirements2 */
         560, /* vkGetPhysicalDeviceExternalBufferProperties */
         562, /* vkGetPhysicalDeviceExternalFenceProperties */
         565, /* vkGetPhysicalDeviceExternalSemaphoreProperties */
         568, /* vkGetPhysicalDeviceFeatures2 */
         571, /* vkGetPhysicalDeviceFormatProperties2 */
         575, /* vkGetPhysicalDeviceImageFormatProperties2 */
         578, /* vkGetPhysicalDeviceMemoryProperties2 */
         584, /* vkGetPhysicalDeviceProperties2 */
         588, /* vkGetPhysicalDeviceQueueFamilyProperties2 */
         592, /* vkGetPhysicalDeviceSparseImageFormatProperties2 */
         708, /* vkTrimCommandPool */
         714  /* vkUpdateDescriptorSetWithTemplate */
    };
    if (!context->VERSION_1_1) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_VERSION_1_2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          29, /* vkCmdBeginRenderPass2 */
         109, /* vkCmdDrawIndexedIndirectCount */
         114, /* vkCmdDrawIndirectCount */
         131, /* vkCmdEndRenderPass2 */
         144, /* vkCmdNextSubpass2 */
         357, /* vkCreateRenderPass2 */
         453, /* vkGetBufferDeviceAddress */
         459, /* vkGetBufferOpaqueCaptureAddress */
         491, /* vkGetDeviceMemoryOpaqueCaptureAddress */
         637, /* vkGetSemaphoreCounterValue */
         689, /* vkResetQueryPool */
         703, /* vkSignalSemaphore */
         722  /* vkWaitSemaphores */
    };
    if (!context->VERSION_1_2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_VERSION_1_3(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          31, /* vkCmdBeginRendering */
          51, /* vkCmdBindVertexBuffers2 */
          54, /* vkCmdBlitImage2 */
          71, /* vkCmdCopyBuffer2 */
          74, /* vkCmdCopyBufferToImage2 */
          77, /* vkCmdCopyImage2 */
          80, /* vkCmdCopyImageToBuffer2 */
         133, /* vkCmdEndRendering */
         148, /* vkCmdPipelineBarrier2 */
         164, /* vkCmdResetEvent2 */
         168, /* vkCmdResolveImage2 */
         188, /* vkCmdSetCullMode */
         192, /* vkCmdSetDepthBiasEnable */
         195, /* vkCmdSetDepthBoundsTestEnable */
         201, /* vkCmdSetDepthCompareOp */
         203, /* vkCmdSetDepthTestEnable */
         205, /* vkCmdSetDepthWriteEnable */
         215, /* vkCmdSetEvent2 */
         222, /* vkCmdSetFrontFace */
         237, /* vkCmdSetPrimitiveRestartEnable */
         239, /* vkCmdSetPrimitiveTopology */
         244, /* vkCmdSetRasterizerDiscardEnable */
         256, /* vkCmdSetScissorWithCount */
         260, /* vkCmdSetStencilOp */
         263, /* vkCmdSetStencilTestEnable */
         273, /* vkCmdSetViewportWithCount */
         283, /* vkCmdWaitEvents2 */
         291, /* vkCmdWriteTimestamp2 */
         351, /* vkCreatePrivateDataSlot */
         414, /* vkDestroyPrivateDataSlot */
         476, /* vkGetDeviceBufferMemoryRequirements */
         484, /* vkGetDeviceImageMemoryRequirements */
         486, /* vkGetDeviceImageSparseMemoryRequirements */
         603, /* vkGetPhysicalDeviceToolProperties */
         621, /* vkGetPrivateData */
         673, /* vkQueueSubmit2 */
         701  /* vkSetPrivateData */
    };
    if (!context->VERSION_1_3) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_VERSION_1_4(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          39, /* vkCmdBindDescriptorSets2 */
          42, /* vkCmdBindIndexBuffer2 */
         153, /* vkCmdPushConstants2 */
         155, /* vkCmdPushDescriptorSet */
         156, /* vkCmdPushDescriptorSet2 */
         159, /* vkCmdPushDescriptorSetWithTemplate */
         160, /* vkCmdPushDescriptorSetWithTemplate2 */
         225, /* vkCmdSetLineStipple */
         247, /* vkCmdSetRenderingAttachmentLocations */
         249, /* vkCmdSetRenderingInputAttachmentIndices */
         297, /* vkCopyImageToImage */
         299, /* vkCopyImageToMemory */
         302, /* vkCopyMemoryToImage */
         488, /* vkGetDeviceImageSubresourceLayout */
         524, /* vkGetImageSubresourceLayout2 */
         633, /* vkGetRenderingAreaGranularity */
         661, /* vkMapMemory2 */
         706, /* vkTransitionImageLayout */
         712  /* vkUnmapMemory2 */
    };
    if (!context->VERSION_1_4) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_ENABLE_BETA_EXTENSIONS)
static void glad_vk_load_VK_AMDX_shader_enqueue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         100, /* vkCmdDispatchGraphAMDX */
         101, /* vkCmdDispatchGraphIndirectAMDX */
         102, /* vkCmdDispatchGraphIndirectCountAMDX */
         141, /* vkCmdInitializeGraphScratchMemoryAMDX */
         331, /* vkCreateExecutionGraphPipelinesAMDX */
         507, /* vkGetExecutionGraphPipelineNodeIndexAMDX */
         508  /* vkGetExecutionGraphPipelineScratchSizeAMDX */
    };
    if (!context->AMDX_shader_enqueue) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_AMD_anti_lag(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          11  /* vkAntiLagUpdateAMD */
    };
    if (!context->AMD_anti_lag) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_AMD_buffer_marker(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         287, /* vkCmdWriteBufferMarker2AMD */
         288  /* vkCmdWriteBufferMarkerAMD */
    };
    if (!context->AMD_buffer_marker) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_AMD_display_native_hdr(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         700  /* vkSetLocalDimmingAMD */
    };
    if (!context->AMD_display_native_hdr) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_AMD_draw_indirect_count(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         110, /* vkCmdDrawIndexedIndirectCountAMD */
         115  /* vkCmdDrawIndirectCountAMD */
    };
    if (!context->AMD_draw_indirect_count) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_AMD_shader_info(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         643  /* vkGetShaderInfoAMD */
    };
    if (!context->AMD_shader_info) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
static void glad_vk_load_VK_ANDROID_external_memory_android_hardware_buffer(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         451, /* vkGetAndroidHardwareBufferPropertiesANDROID */
         533  /* vkGetMemoryAndroidHardwareBufferANDROID */
    };
    if (!context->ANDROID_external_memory_android_hardware_buffer) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_acquire_drm_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           0, /* vkAcquireDrmDisplayEXT */
         503  /* vkGetDrmDisplayEXT */
    };
    if (!context->EXT_acquire_drm_display) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
static void glad_vk_load_VK_EXT_acquire_xlib_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           7, /* vkAcquireXlibDisplayEXT */
         626  /* vkGetRandROutputDisplayEXT */
    };
    if (!context->EXT_acquire_xlib_display) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_attachment_feedback_loop_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         172  /* vkCmdSetAttachmentFeedbackLoopEnableEXT */
    };
    if (!context->EXT_attachment_feedback_loop_dynamic_state) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_buffer_device_address(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         454  /* vkGetBufferDeviceAddressEXT */
    };
    if (!context->EXT_buffer_device_address) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_calibrated_timestamps(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         462, /* vkGetCalibratedTimestampsEXT */
         549  /* vkGetPhysicalDeviceCalibrateableTimeDomainsEXT */
    };
    if (!context->EXT_calibrated_timestamps) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_color_write_enable(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         179  /* vkCmdSetColorWriteEnableEXT */
    };
    if (!context->EXT_color_write_enable) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_conditional_rendering(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          24, /* vkCmdBeginConditionalRenderingEXT */
         126  /* vkCmdEndConditionalRenderingEXT */
    };
    if (!context->EXT_conditional_rendering) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_debug_marker(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          91, /* vkCmdDebugMarkerBeginEXT */
          92, /* vkCmdDebugMarkerEndEXT */
          93, /* vkCmdDebugMarkerInsertEXT */
         377, /* vkDebugMarkerSetObjectNameEXT */
         378  /* vkDebugMarkerSetObjectTagEXT */
    };
    if (!context->EXT_debug_marker) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_debug_report(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         319, /* vkCreateDebugReportCallbackEXT */
         379, /* vkDebugReportMessageEXT */
         391  /* vkDestroyDebugReportCallbackEXT */
    };
    if (!context->EXT_debug_report) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_debug_utils(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          25, /* vkCmdBeginDebugUtilsLabelEXT */
         127, /* vkCmdEndDebugUtilsLabelEXT */
         142, /* vkCmdInsertDebugUtilsLabelEXT */
         320, /* vkCreateDebugUtilsMessengerEXT */
         392, /* vkDestroyDebugUtilsMessengerEXT */
         665, /* vkQueueBeginDebugUtilsLabelEXT */
         667, /* vkQueueEndDebugUtilsLabelEXT */
         668, /* vkQueueInsertDebugUtilsLabelEXT */
         693, /* vkSetDebugUtilsObjectNameEXT */
         694, /* vkSetDebugUtilsObjectTagEXT */
         705  /* vkSubmitDebugUtilsMessageEXT */
    };
    if (!context->EXT_debug_utils) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_depth_bias_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         191  /* vkCmdSetDepthBias2EXT */
    };
    if (!context->EXT_depth_bias_control) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_depth_clamp_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         198  /* vkCmdSetDepthClampRangeEXT */
    };
    if (!context->EXT_depth_clamp_control) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_descriptor_buffer(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          36, /* vkCmdBindDescriptorBufferEmbeddedSamplersEXT */
          37, /* vkCmdBindDescriptorBuffersEXT */
         208, /* vkCmdSetDescriptorBufferOffsetsEXT */
         450, /* vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT */
         461, /* vkGetBufferOpaqueCaptureDescriptorDataEXT */
         468, /* vkGetDescriptorEXT */
         470, /* vkGetDescriptorSetLayoutBindingOffsetEXT */
         472, /* vkGetDescriptorSetLayoutSizeEXT */
         519, /* vkGetImageOpaqueCaptureDescriptorDataEXT */
         530, /* vkGetImageViewOpaqueCaptureDescriptorDataEXT */
         635  /* vkGetSamplerOpaqueCaptureDescriptorDataEXT */
    };
    if (!context->EXT_descriptor_buffer) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_device_fault(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         478  /* vkGetDeviceFaultInfoEXT */
    };
    if (!context->EXT_device_fault) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_device_generated_commands(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         138, /* vkCmdExecuteGeneratedCommandsEXT */
         150, /* vkCmdPreprocessGeneratedCommandsEXT */
         340, /* vkCreateIndirectCommandsLayoutEXT */
         342, /* vkCreateIndirectExecutionSetEXT */
         404, /* vkDestroyIndirectCommandsLayoutEXT */
         406, /* vkDestroyIndirectExecutionSetEXT */
         513, /* vkGetGeneratedCommandsMemoryRequirementsEXT */
         717, /* vkUpdateIndirectExecutionSetPipelineEXT */
         718  /* vkUpdateIndirectExecutionSetShaderEXT */
    };
    if (!context->EXT_device_generated_commands) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_direct_mode_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         679  /* vkReleaseDisplayEXT */
    };
    if (!context->EXT_direct_mode_display) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
static void glad_vk_load_VK_EXT_directfb_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         327, /* vkCreateDirectFBSurfaceEXT */
         555  /* vkGetPhysicalDeviceDirectFBPresentationSupportEXT */
    };
    if (!context->EXT_directfb_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_discard_rectangles(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         211, /* vkCmdSetDiscardRectangleEXT */
         212, /* vkCmdSetDiscardRectangleEnableEXT */
         213  /* vkCmdSetDiscardRectangleModeEXT */
    };
    if (!context->EXT_discard_rectangles) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_display_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         430, /* vkDisplayPowerControlEXT */
         646, /* vkGetSwapchainCounterEXT */
         676, /* vkRegisterDeviceEventEXT */
         677  /* vkRegisterDisplayEventEXT */
    };
    if (!context->EXT_display_control) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_display_surface_counter(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         595  /* vkGetPhysicalDeviceSurfaceCapabilities2EXT */
    };
    if (!context->EXT_display_surface_counter) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_extended_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          52, /* vkCmdBindVertexBuffers2EXT */
         189, /* vkCmdSetCullModeEXT */
         196, /* vkCmdSetDepthBoundsTestEnableEXT */
         202, /* vkCmdSetDepthCompareOpEXT */
         204, /* vkCmdSetDepthTestEnableEXT */
         206, /* vkCmdSetDepthWriteEnableEXT */
         223, /* vkCmdSetFrontFaceEXT */
         240, /* vkCmdSetPrimitiveTopologyEXT */
         257, /* vkCmdSetScissorWithCountEXT */
         261, /* vkCmdSetStencilOpEXT */
         264, /* vkCmdSetStencilTestEnableEXT */
         274  /* vkCmdSetViewportWithCountEXT */
    };
    if (!context->EXT_extended_dynamic_state) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_extended_dynamic_state2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         193, /* vkCmdSetDepthBiasEnableEXT */
         230, /* vkCmdSetLogicOpEXT */
         232, /* vkCmdSetPatchControlPointsEXT */
         238, /* vkCmdSetPrimitiveRestartEnableEXT */
         245  /* vkCmdSetRasterizerDiscardEnableEXT */
    };
    if (!context->EXT_extended_dynamic_state2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_extended_dynamic_state3(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         170, /* vkCmdSetAlphaToCoverageEnableEXT */
         171, /* vkCmdSetAlphaToOneEnableEXT */
         176, /* vkCmdSetColorBlendAdvancedEXT */
         177, /* vkCmdSetColorBlendEnableEXT */
         178, /* vkCmdSetColorBlendEquationEXT */
         180, /* vkCmdSetColorWriteMaskEXT */
         181, /* vkCmdSetConservativeRasterizationModeEXT */
         182, /* vkCmdSetCoverageModulationModeNV */
         183, /* vkCmdSetCoverageModulationTableEnableNV */
         184, /* vkCmdSetCoverageModulationTableNV */
         185, /* vkCmdSetCoverageReductionModeNV */
         186, /* vkCmdSetCoverageToColorEnableNV */
         187, /* vkCmdSetCoverageToColorLocationNV */
         197, /* vkCmdSetDepthClampEnableEXT */
         199, /* vkCmdSetDepthClipEnableEXT */
         200, /* vkCmdSetDepthClipNegativeOneToOneEXT */
         219, /* vkCmdSetExtraPrimitiveOverestimationSizeEXT */
         224, /* vkCmdSetLineRasterizationModeEXT */
         227, /* vkCmdSetLineStippleEnableEXT */
         231, /* vkCmdSetLogicOpEnableEXT */
         236, /* vkCmdSetPolygonModeEXT */
         241, /* vkCmdSetProvokingVertexModeEXT */
         242, /* vkCmdSetRasterizationSamplesEXT */
         243, /* vkCmdSetRasterizationStreamEXT */
         251, /* vkCmdSetRepresentativeFragmentTestEnableNV */
         253, /* vkCmdSetSampleLocationsEnableEXT */
         254, /* vkCmdSetSampleMaskEXT */
         258, /* vkCmdSetShadingRateImageEnableNV */
         266, /* vkCmdSetTessellationDomainOriginEXT */
         270, /* vkCmdSetViewportSwizzleNV */
         271  /* vkCmdSetViewportWScalingEnableNV */
    };
    if (!context->EXT_extended_dynamic_state3) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_external_memory_host(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         536  /* vkGetMemoryHostPointerPropertiesEXT */
    };
    if (!context->EXT_external_memory_host) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_METAL_EXT)
static void glad_vk_load_VK_EXT_external_memory_metal(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         537, /* vkGetMemoryMetalHandleEXT */
         538  /* vkGetMemoryMetalHandlePropertiesEXT */
    };
    if (!context->EXT_external_memory_metal) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_EXT_full_screen_exclusive(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           1, /* vkAcquireFullScreenExclusiveModeEXT */
         482, /* vkGetDeviceGroupSurfacePresentModes2EXT */
         600, /* vkGetPhysicalDeviceSurfacePresentModes2EXT */
         680  /* vkReleaseFullScreenExclusiveModeEXT */
    };
    if (!context->EXT_full_screen_exclusive) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_hdr_metadata(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         697  /* vkSetHdrMetadataEXT */
    };
    if (!context->EXT_hdr_metadata) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_headless_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         335  /* vkCreateHeadlessSurfaceEXT */
    };
    if (!context->EXT_headless_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_host_image_copy(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         298, /* vkCopyImageToImageEXT */
         300, /* vkCopyImageToMemoryEXT */
         303, /* vkCopyMemoryToImageEXT */
         525, /* vkGetImageSubresourceLayout2EXT */
         707  /* vkTransitionImageLayoutEXT */
    };
    if (!context->EXT_host_image_copy) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_host_query_reset(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         690  /* vkResetQueryPoolEXT */
    };
    if (!context->EXT_host_query_reset) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_image_compression_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         525  /* vkGetImageSubresourceLayout2EXT */
    };
    if (!context->EXT_image_compression_control) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_image_drm_format_modifier(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         515  /* vkGetImageDrmFormatModifierPropertiesEXT */
    };
    if (!context->EXT_image_drm_format_modifier) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_line_rasterization(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         226  /* vkCmdSetLineStippleEXT */
    };
    if (!context->EXT_line_rasterization) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_mesh_shader(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         117, /* vkCmdDrawMeshTasksEXT */
         118, /* vkCmdDrawMeshTasksIndirectCountEXT */
         120  /* vkCmdDrawMeshTasksIndirectEXT */
    };
    if (!context->EXT_mesh_shader) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_METAL_EXT)
static void glad_vk_load_VK_EXT_metal_objects(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         441  /* vkExportMetalObjectsEXT */
    };
    if (!context->EXT_metal_objects) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_METAL_EXT)
static void glad_vk_load_VK_EXT_metal_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         345  /* vkCreateMetalSurfaceEXT */
    };
    if (!context->EXT_metal_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_multi_draw(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         123, /* vkCmdDrawMultiEXT */
         124  /* vkCmdDrawMultiIndexedEXT */
    };
    if (!context->EXT_multi_draw) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_opacity_micromap(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          23, /* vkBuildMicromapsEXT */
          60, /* vkCmdBuildMicromapsEXT */
          85, /* vkCmdCopyMemoryToMicromapEXT */
          86, /* vkCmdCopyMicromapEXT */
          87, /* vkCmdCopyMicromapToMemoryEXT */
         289, /* vkCmdWriteMicromapsPropertiesEXT */
         304, /* vkCopyMemoryToMicromapEXT */
         305, /* vkCopyMicromapEXT */
         306, /* vkCopyMicromapToMemoryEXT */
         346, /* vkCreateMicromapEXT */
         408, /* vkDestroyMicromapEXT */
         493, /* vkGetDeviceMicromapCompatibilityEXT */
         545, /* vkGetMicromapBuildSizesEXT */
         725  /* vkWriteMicromapsPropertiesEXT */
    };
    if (!context->EXT_opacity_micromap) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_pageable_device_local_memory(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         695  /* vkSetDeviceMemoryPriorityEXT */
    };
    if (!context->EXT_pageable_device_local_memory) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_pipeline_properties(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         620  /* vkGetPipelinePropertiesEXT */
    };
    if (!context->EXT_pipeline_properties) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_private_data(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         352, /* vkCreatePrivateDataSlotEXT */
         415, /* vkDestroyPrivateDataSlotEXT */
         622, /* vkGetPrivateDataEXT */
         702  /* vkSetPrivateDataEXT */
    };
    if (!context->EXT_private_data) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_sample_locations(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         252, /* vkCmdSetSampleLocationsEXT */
         580  /* vkGetPhysicalDeviceMultisamplePropertiesEXT */
    };
    if (!context->EXT_sample_locations) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_shader_module_identifier(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         644, /* vkGetShaderModuleCreateInfoIdentifierEXT */
         645  /* vkGetShaderModuleIdentifierEXT */
    };
    if (!context->EXT_shader_module_identifier) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_shader_object(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          47, /* vkCmdBindShadersEXT */
          52, /* vkCmdBindVertexBuffers2EXT */
         170, /* vkCmdSetAlphaToCoverageEnableEXT */
         171, /* vkCmdSetAlphaToOneEnableEXT */
         176, /* vkCmdSetColorBlendAdvancedEXT */
         177, /* vkCmdSetColorBlendEnableEXT */
         178, /* vkCmdSetColorBlendEquationEXT */
         180, /* vkCmdSetColorWriteMaskEXT */
         181, /* vkCmdSetConservativeRasterizationModeEXT */
         182, /* vkCmdSetCoverageModulationModeNV */
         183, /* vkCmdSetCoverageModulationTableEnableNV */
         184, /* vkCmdSetCoverageModulationTableNV */
         185, /* vkCmdSetCoverageReductionModeNV */
         186, /* vkCmdSetCoverageToColorEnableNV */
         187, /* vkCmdSetCoverageToColorLocationNV */
         189, /* vkCmdSetCullModeEXT */
         193, /* vkCmdSetDepthBiasEnableEXT */
         196, /* vkCmdSetDepthBoundsTestEnableEXT */
         197, /* vkCmdSetDepthClampEnableEXT */
         198, /* vkCmdSetDepthClampRangeEXT */
         199, /* vkCmdSetDepthClipEnableEXT */
         200, /* vkCmdSetDepthClipNegativeOneToOneEXT */
         202, /* vkCmdSetDepthCompareOpEXT */
         204, /* vkCmdSetDepthTestEnableEXT */
         206, /* vkCmdSetDepthWriteEnableEXT */
         219, /* vkCmdSetExtraPrimitiveOverestimationSizeEXT */
         223, /* vkCmdSetFrontFaceEXT */
         224, /* vkCmdSetLineRasterizationModeEXT */
         227, /* vkCmdSetLineStippleEnableEXT */
         230, /* vkCmdSetLogicOpEXT */
         231, /* vkCmdSetLogicOpEnableEXT */
         232, /* vkCmdSetPatchControlPointsEXT */
         236, /* vkCmdSetPolygonModeEXT */
         238, /* vkCmdSetPrimitiveRestartEnableEXT */
         240, /* vkCmdSetPrimitiveTopologyEXT */
         241, /* vkCmdSetProvokingVertexModeEXT */
         242, /* vkCmdSetRasterizationSamplesEXT */
         243, /* vkCmdSetRasterizationStreamEXT */
         245, /* vkCmdSetRasterizerDiscardEnableEXT */
         251, /* vkCmdSetRepresentativeFragmentTestEnableNV */
         253, /* vkCmdSetSampleLocationsEnableEXT */
         254, /* vkCmdSetSampleMaskEXT */
         257, /* vkCmdSetScissorWithCountEXT */
         258, /* vkCmdSetShadingRateImageEnableNV */
         261, /* vkCmdSetStencilOpEXT */
         264, /* vkCmdSetStencilTestEnableEXT */
         266, /* vkCmdSetTessellationDomainOriginEXT */
         267, /* vkCmdSetVertexInputEXT */
         270, /* vkCmdSetViewportSwizzleNV */
         271, /* vkCmdSetViewportWScalingEnableNV */
         274, /* vkCmdSetViewportWithCountEXT */
         365, /* vkCreateShadersEXT */
         422, /* vkDestroyShaderEXT */
         642  /* vkGetShaderBinaryDataEXT */
    };
    if (!context->EXT_shader_object) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_swapchain_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         683  /* vkReleaseSwapchainImagesEXT */
    };
    if (!context->EXT_swapchain_maintenance1) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_tooling_info(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         604  /* vkGetPhysicalDeviceToolPropertiesEXT */
    };
    if (!context->EXT_tooling_info) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_transform_feedback(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          27, /* vkCmdBeginQueryIndexedEXT */
          33, /* vkCmdBeginTransformFeedbackEXT */
          49, /* vkCmdBindTransformFeedbackBuffersEXT */
         113, /* vkCmdDrawIndirectByteCountEXT */
         129, /* vkCmdEndQueryIndexedEXT */
         135  /* vkCmdEndTransformFeedbackEXT */
    };
    if (!context->EXT_transform_feedback) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_validation_cache(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         369, /* vkCreateValidationCacheEXT */
         426, /* vkDestroyValidationCacheEXT */
         649, /* vkGetValidationCacheDataEXT */
         664  /* vkMergeValidationCachesEXT */
    };
    if (!context->EXT_validation_cache) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_vertex_input_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         267  /* vkCmdSetVertexInputEXT */
    };
    if (!context->EXT_vertex_input_dynamic_state) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_buffer_collection(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         311, /* vkCreateBufferCollectionFUCHSIA */
         384, /* vkDestroyBufferCollectionFUCHSIA */
         452, /* vkGetBufferCollectionPropertiesFUCHSIA */
         691, /* vkSetBufferCollectionBufferConstraintsFUCHSIA */
         692  /* vkSetBufferCollectionImageConstraintsFUCHSIA */
    };
    if (!context->FUCHSIA_buffer_collection) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_external_memory(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         543, /* vkGetMemoryZirconHandleFUCHSIA */
         544  /* vkGetMemoryZirconHandlePropertiesFUCHSIA */
    };
    if (!context->FUCHSIA_external_memory) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_external_semaphore(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         641, /* vkGetSemaphoreZirconHandleFUCHSIA */
         656  /* vkImportSemaphoreZirconHandleFUCHSIA */
    };
    if (!context->FUCHSIA_external_semaphore) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_imagepipe_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         338  /* vkCreateImagePipeSurfaceFUCHSIA */
    };
    if (!context->FUCHSIA_imagepipe_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_GGP)
static void glad_vk_load_VK_GGP_stream_descriptor_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         367  /* vkCreateStreamDescriptorSurfaceGGP */
    };
    if (!context->GGP_stream_descriptor_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_GOOGLE_display_timing(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         547, /* vkGetPastPresentationTimingGOOGLE */
         631  /* vkGetRefreshCycleDurationGOOGLE */
    };
    if (!context->GOOGLE_display_timing) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_HUAWEI_cluster_culling_shader(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         105, /* vkCmdDrawClusterHUAWEI */
         106  /* vkCmdDrawClusterIndirectHUAWEI */
    };
    if (!context->HUAWEI_cluster_culling_shader) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_HUAWEI_invocation_mask(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          44  /* vkCmdBindInvocationMaskHUAWEI */
    };
    if (!context->HUAWEI_invocation_mask) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_HUAWEI_subpass_shading(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         275, /* vkCmdSubpassShadingHUAWEI */
         497  /* vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI */
    };
    if (!context->HUAWEI_subpass_shading) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_INTEL_performance_query(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           4, /* vkAcquirePerformanceConfigurationINTEL */
         233, /* vkCmdSetPerformanceMarkerINTEL */
         234, /* vkCmdSetPerformanceOverrideINTEL */
         235, /* vkCmdSetPerformanceStreamMarkerINTEL */
         548, /* vkGetPerformanceParameterINTEL */
         657, /* vkInitializePerformanceApiINTEL */
         671, /* vkQueueSetPerformanceConfigurationINTEL */
         681, /* vkReleasePerformanceConfigurationINTEL */
         710  /* vkUninitializePerformanceApiINTEL */
    };
    if (!context->INTEL_performance_query) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_acceleration_structure(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          22, /* vkBuildAccelerationStructuresKHR */
          57, /* vkCmdBuildAccelerationStructuresIndirectKHR */
          58, /* vkCmdBuildAccelerationStructuresKHR */
          67, /* vkCmdCopyAccelerationStructureKHR */
          69, /* vkCmdCopyAccelerationStructureToMemoryKHR */
          83, /* vkCmdCopyMemoryToAccelerationStructureKHR */
         285, /* vkCmdWriteAccelerationStructuresPropertiesKHR */
         295, /* vkCopyAccelerationStructureKHR */
         296, /* vkCopyAccelerationStructureToMemoryKHR */
         301, /* vkCopyMemoryToAccelerationStructureKHR */
         307, /* vkCreateAccelerationStructureKHR */
         381, /* vkDestroyAccelerationStructureKHR */
         446, /* vkGetAccelerationStructureBuildSizesKHR */
         447, /* vkGetAccelerationStructureDeviceAddressKHR */
         475, /* vkGetDeviceAccelerationStructureCompatibilityKHR */
         724  /* vkWriteAccelerationStructuresPropertiesKHR */
    };
    if (!context->KHR_acceleration_structure) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
static void glad_vk_load_VK_KHR_android_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         309  /* vkCreateAndroidSurfaceKHR */
    };
    if (!context->KHR_android_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_KHR_bind_memory2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          16, /* vkBindBufferMemory2KHR */
          19  /* vkBindImageMemory2KHR */
    };
    if (!context->KHR_bind_memory2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_buffer_device_address(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         455, /* vkGetBufferDeviceAddressKHR */
         460, /* vkGetBufferOpaqueCaptureAddressKHR */
         492  /* vkGetDeviceMemoryOpaqueCaptureAddressKHR */
    };
    if (!context->KHR_buffer_device_address) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_calibrated_timestamps(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         463, /* vkGetCalibratedTimestampsKHR */
         550  /* vkGetPhysicalDeviceCalibrateableTimeDomainsKHR */
    };
    if (!context->KHR_calibrated_timestamps) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_cooperative_matrix(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         552  /* vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR */
    };
    if (!context->KHR_cooperative_matrix) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_copy_commands2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          55, /* vkCmdBlitImage2KHR */
          72, /* vkCmdCopyBuffer2KHR */
          75, /* vkCmdCopyBufferToImage2KHR */
          78, /* vkCmdCopyImage2KHR */
          81, /* vkCmdCopyImageToBuffer2KHR */
         169  /* vkCmdResolveImage2KHR */
    };
    if (!context->KHR_copy_commands2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_create_renderpass2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          30, /* vkCmdBeginRenderPass2KHR */
         132, /* vkCmdEndRenderPass2KHR */
         145, /* vkCmdNextSubpass2KHR */
         358  /* vkCreateRenderPass2KHR */
    };
    if (!context->KHR_create_renderpass2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_deferred_host_operations(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         321, /* vkCreateDeferredOperationKHR */
         380, /* vkDeferredOperationJoinKHR */
         393, /* vkDestroyDeferredOperationKHR */
         466, /* vkGetDeferredOperationMaxConcurrencyKHR */
         467  /* vkGetDeferredOperationResultKHR */
    };
    if (!context->KHR_deferred_host_operations) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_descriptor_update_template(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         162, /* vkCmdPushDescriptorSetWithTemplateKHR */
         325, /* vkCreateDescriptorUpdateTemplateKHR */
         397, /* vkDestroyDescriptorUpdateTemplateKHR */
         715  /* vkUpdateDescriptorSetWithTemplateKHR */
    };
    if (!context->KHR_descriptor_update_template) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_device_group(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           2, /* vkAcquireNextImage2KHR */
          99, /* vkCmdDispatchBaseKHR */
         210, /* vkCmdSetDeviceMaskKHR */
         480, /* vkGetDeviceGroupPeerMemoryFeaturesKHR */
         481, /* vkGetDeviceGroupPresentCapabilitiesKHR */
         483, /* vkGetDeviceGroupSurfacePresentModesKHR */
         582  /* vkGetPhysicalDevicePresentRectanglesKHR */
    };
    if (!context->KHR_device_group) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_device_group_creation(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         438  /* vkEnumeratePhysicalDeviceGroupsKHR */
    };
    if (!context->KHR_device_group_creation) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         328, /* vkCreateDisplayModeKHR */
         329, /* vkCreateDisplayPlaneSurfaceKHR */
         499, /* vkGetDisplayModePropertiesKHR */
         501, /* vkGetDisplayPlaneCapabilitiesKHR */
         502, /* vkGetDisplayPlaneSupportedDisplaysKHR */
         557, /* vkGetPhysicalDeviceDisplayPlanePropertiesKHR */
         559  /* vkGetPhysicalDeviceDisplayPropertiesKHR */
    };
    if (!context->KHR_display) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_display_swapchain(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         366  /* vkCreateSharedSwapchainsKHR */
    };
    if (!context->KHR_display_swapchain) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_draw_indirect_count(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         111, /* vkCmdDrawIndexedIndirectCountKHR */
         116  /* vkCmdDrawIndirectCountKHR */
    };
    if (!context->KHR_draw_indirect_count) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_dynamic_rendering(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          32, /* vkCmdBeginRenderingKHR */
         134  /* vkCmdEndRenderingKHR */
    };
    if (!context->KHR_dynamic_rendering) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_dynamic_rendering_local_read(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         248, /* vkCmdSetRenderingAttachmentLocationsKHR */
         250  /* vkCmdSetRenderingInputAttachmentIndicesKHR */
    };
    if (!context->KHR_dynamic_rendering_local_read) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_external_fence_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         563  /* vkGetPhysicalDeviceExternalFencePropertiesKHR */
    };
    if (!context->KHR_external_fence_capabilities) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_external_fence_fd(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         509, /* vkGetFenceFdKHR */
         652  /* vkImportFenceFdKHR */
    };
    if (!context->KHR_external_fence_fd) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_external_fence_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         511, /* vkGetFenceWin32HandleKHR */
         653  /* vkImportFenceWin32HandleKHR */
    };
    if (!context->KHR_external_fence_win32) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_KHR_external_memory_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         561  /* vkGetPhysicalDeviceExternalBufferPropertiesKHR */
    };
    if (!context->KHR_external_memory_capabilities) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_external_memory_fd(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         534, /* vkGetMemoryFdKHR */
         535  /* vkGetMemoryFdPropertiesKHR */
    };
    if (!context->KHR_external_memory_fd) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_external_memory_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         540, /* vkGetMemoryWin32HandleKHR */
         542  /* vkGetMemoryWin32HandlePropertiesKHR */
    };
    if (!context->KHR_external_memory_win32) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_KHR_external_semaphore_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         566  /* vkGetPhysicalDeviceExternalSemaphorePropertiesKHR */
    };
    if (!context->KHR_external_semaphore_capabilities) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_external_semaphore_fd(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         639, /* vkGetSemaphoreFdKHR */
         654  /* vkImportSemaphoreFdKHR */
    };
    if (!context->KHR_external_semaphore_fd) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_external_semaphore_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         640, /* vkGetSemaphoreWin32HandleKHR */
         655  /* vkImportSemaphoreWin32HandleKHR */
    };
    if (!context->KHR_external_semaphore_win32) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_KHR_fragment_shading_rate(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         221, /* vkCmdSetFragmentShadingRateKHR */
         573  /* vkGetPhysicalDeviceFragmentShadingRatesKHR */
    };
    if (!context->KHR_fragment_shading_rate) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_get_display_properties2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         498, /* vkGetDisplayModeProperties2KHR */
         500, /* vkGetDisplayPlaneCapabilities2KHR */
         556, /* vkGetPhysicalDeviceDisplayPlaneProperties2KHR */
         558  /* vkGetPhysicalDeviceDisplayProperties2KHR */
    };
    if (!context->KHR_get_display_properties2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_get_memory_requirements2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         458, /* vkGetBufferMemoryRequirements2KHR */
         518, /* vkGetImageMemoryRequirements2KHR */
         522  /* vkGetImageSparseMemoryRequirements2KHR */
    };
    if (!context->KHR_get_memory_requirements2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_get_physical_device_properties2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         569, /* vkGetPhysicalDeviceFeatures2KHR */
         572, /* vkGetPhysicalDeviceFormatProperties2KHR */
         576, /* vkGetPhysicalDeviceImageFormatProperties2KHR */
         579, /* vkGetPhysicalDeviceMemoryProperties2KHR */
         585, /* vkGetPhysicalDeviceProperties2KHR */
         589, /* vkGetPhysicalDeviceQueueFamilyProperties2KHR */
         593  /* vkGetPhysicalDeviceSparseImageFormatProperties2KHR */
    };
    if (!context->KHR_get_physical_device_properties2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_get_surface_capabilities2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         596, /* vkGetPhysicalDeviceSurfaceCapabilities2KHR */
         598  /* vkGetPhysicalDeviceSurfaceFormats2KHR */
    };
    if (!context->KHR_get_surface_capabilities2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_line_rasterization(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         228  /* vkCmdSetLineStippleKHR */
    };
    if (!context->KHR_line_rasterization) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         709  /* vkTrimCommandPoolKHR */
    };
    if (!context->KHR_maintenance1) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_maintenance3(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         474  /* vkGetDescriptorSetLayoutSupportKHR */
    };
    if (!context->KHR_maintenance3) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_maintenance4(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         477, /* vkGetDeviceBufferMemoryRequirementsKHR */
         485, /* vkGetDeviceImageMemoryRequirementsKHR */
         487  /* vkGetDeviceImageSparseMemoryRequirementsKHR */
    };
    if (!context->KHR_maintenance4) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_maintenance5(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          43, /* vkCmdBindIndexBuffer2KHR */
         489, /* vkGetDeviceImageSubresourceLayoutKHR */
         526, /* vkGetImageSubresourceLayout2KHR */
         634  /* vkGetRenderingAreaGranularityKHR */
    };
    if (!context->KHR_maintenance5) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_maintenance6(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          35, /* vkCmdBindDescriptorBufferEmbeddedSamplers2EXT */
          40, /* vkCmdBindDescriptorSets2KHR */
         154, /* vkCmdPushConstants2KHR */
         157, /* vkCmdPushDescriptorSet2KHR */
         161, /* vkCmdPushDescriptorSetWithTemplate2KHR */
         207  /* vkCmdSetDescriptorBufferOffsets2EXT */
    };
    if (!context->KHR_maintenance6) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_map_memory2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         662, /* vkMapMemory2KHR */
         713  /* vkUnmapMemory2KHR */
    };
    if (!context->KHR_map_memory2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_performance_query(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           5, /* vkAcquireProfilingLockKHR */
         439, /* vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR */
         586, /* vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR */
         682  /* vkReleaseProfilingLockKHR */
    };
    if (!context->KHR_performance_query) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_pipeline_binary(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         348, /* vkCreatePipelineBinariesKHR */
         411, /* vkDestroyPipelineBinaryKHR */
         612, /* vkGetPipelineBinaryDataKHR */
         619, /* vkGetPipelineKeyKHR */
         678  /* vkReleaseCapturedPipelineDataKHR */
    };
    if (!context->KHR_pipeline_binary) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_pipeline_executable_properties(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         614, /* vkGetPipelineExecutableInternalRepresentationsKHR */
         615, /* vkGetPipelineExecutablePropertiesKHR */
         616  /* vkGetPipelineExecutableStatisticsKHR */
    };
    if (!context->KHR_pipeline_executable_properties) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_present_wait(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         721  /* vkWaitForPresentKHR */
    };
    if (!context->KHR_present_wait) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_push_descriptor(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         158, /* vkCmdPushDescriptorSetKHR */
         162  /* vkCmdPushDescriptorSetWithTemplateKHR */
    };
    if (!context->KHR_push_descriptor) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_ray_tracing_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         276  /* vkCmdTraceRaysIndirect2KHR */
    };
    if (!context->KHR_ray_tracing_maintenance1) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_ray_tracing_pipeline(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         246, /* vkCmdSetRayTracingPipelineStackSizeKHR */
         277, /* vkCmdTraceRaysIndirectKHR */
         278, /* vkCmdTraceRaysKHR */
         354, /* vkCreateRayTracingPipelinesKHR */
         627, /* vkGetRayTracingCaptureReplayShaderGroupHandlesKHR */
         628, /* vkGetRayTracingShaderGroupHandlesKHR */
         630  /* vkGetRayTracingShaderGroupStackSizeKHR */
    };
    if (!context->KHR_ray_tracing_pipeline) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_sampler_ycbcr_conversion(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         361, /* vkCreateSamplerYcbcrConversionKHR */
         420  /* vkDestroySamplerYcbcrConversionKHR */
    };
    if (!context->KHR_sampler_ycbcr_conversion) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_shared_presentable_image(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         648  /* vkGetSwapchainStatusKHR */
    };
    if (!context->KHR_shared_presentable_image) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         424, /* vkDestroySurfaceKHR */
         597, /* vkGetPhysicalDeviceSurfaceCapabilitiesKHR */
         599, /* vkGetPhysicalDeviceSurfaceFormatsKHR */
         601, /* vkGetPhysicalDeviceSurfacePresentModesKHR */
         602  /* vkGetPhysicalDeviceSurfaceSupportKHR */
    };
    if (!context->KHR_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_swapchain(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           2, /* vkAcquireNextImage2KHR */
           3, /* vkAcquireNextImageKHR */
         368, /* vkCreateSwapchainKHR */
         425, /* vkDestroySwapchainKHR */
         481, /* vkGetDeviceGroupPresentCapabilitiesKHR */
         483, /* vkGetDeviceGroupSurfacePresentModesKHR */
         582, /* vkGetPhysicalDevicePresentRectanglesKHR */
         647, /* vkGetSwapchainImagesKHR */
         670  /* vkQueuePresentKHR */
    };
    if (!context->KHR_swapchain) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_synchronization2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         149, /* vkCmdPipelineBarrier2KHR */
         165, /* vkCmdResetEvent2KHR */
         216, /* vkCmdSetEvent2KHR */
         284, /* vkCmdWaitEvents2KHR */
         292, /* vkCmdWriteTimestamp2KHR */
         674  /* vkQueueSubmit2KHR */
    };
    if (!context->KHR_synchronization2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_timeline_semaphore(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         638, /* vkGetSemaphoreCounterValueKHR */
         704, /* vkSignalSemaphoreKHR */
         723  /* vkWaitSemaphoresKHR */
    };
    if (!context->KHR_timeline_semaphore) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_video_decode_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          94  /* vkCmdDecodeVideoKHR */
    };
    if (!context->KHR_video_decode_queue) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_video_encode_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         125, /* vkCmdEncodeVideoKHR */
         505, /* vkGetEncodedVideoSessionParametersKHR */
         606  /* vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR */
    };
    if (!context->KHR_video_encode_queue) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_video_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          21, /* vkBindVideoSessionMemoryKHR */
          34, /* vkCmdBeginVideoCodingKHR */
          65, /* vkCmdControlVideoCodingKHR */
         136, /* vkCmdEndVideoCodingKHR */
         371, /* vkCreateVideoSessionKHR */
         372, /* vkCreateVideoSessionParametersKHR */
         427, /* vkDestroyVideoSessionKHR */
         428, /* vkDestroyVideoSessionParametersKHR */
         605, /* vkGetPhysicalDeviceVideoCapabilitiesKHR */
         607, /* vkGetPhysicalDeviceVideoFormatPropertiesKHR */
         650, /* vkGetVideoSessionMemoryRequirementsKHR */
         719  /* vkUpdateVideoSessionParametersKHR */
    };
    if (!context->KHR_video_queue) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
static void glad_vk_load_VK_KHR_wayland_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         373, /* vkCreateWaylandSurfaceKHR */
         608  /* vkGetPhysicalDeviceWaylandPresentationSupportKHR */
    };
    if (!context->KHR_wayland_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_win32_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         374, /* vkCreateWin32SurfaceKHR */
         609  /* vkGetPhysicalDeviceWin32PresentationSupportKHR */
    };
    if (!context->KHR_win32_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
static void glad_vk_load_VK_KHR_xcb_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         375, /* vkCreateXcbSurfaceKHR */
         610  /* vkGetPhysicalDeviceXcbPresentationSupportKHR */
    };
    if (!context->KHR_xcb_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)
static void glad_vk_load_VK_KHR_xlib_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         376, /* vkCreateXlibSurfaceKHR */
         611  /* vkGetPhysicalDeviceXlibPresentationSupportKHR */
    };
    if (!context->KHR_xlib_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_IOS_MVK)
static void glad_vk_load_VK_MVK_ios_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         336  /* vkCreateIOSSurfaceMVK */
    };
    if (!context->MVK_ios_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_MACOS_MVK)
static void glad_vk_load_VK_MVK_macos_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         344  /* vkCreateMacOSSurfaceMVK */
    };
    if (!context->MVK_macos_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_VI_NN)
static void glad_vk_load_VK_NN_vi_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         370  /* vkCreateViSurfaceNN */
    };
    if (!context->NN_vi_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_NVX_binary_import(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          89, /* vkCmdCuLaunchKernelNVX */
         315, /* vkCreateCuFunctionNVX */
         316, /* vkCreateCuModuleNVX */
         387, /* vkDestroyCuFunctionNVX */
         388  /* vkDestroyCuModuleNVX */
    };
    if (!context->NVX_binary_import) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NVX_image_view_handle(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         527, /* vkGetImageViewAddressNVX */
         528, /* vkGetImageViewHandle64NVX */
         529  /* vkGetImageViewHandleNVX */
    };
    if (!context->NVX_image_view_handle) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_NV_acquire_winrt_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           6, /* vkAcquireWinrtDisplayNV */
         651  /* vkGetWinrtDisplayNV */
    };
    if (!context->NV_acquire_winrt_display) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_NV_clip_space_w_scaling(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         272  /* vkCmdSetViewportWScalingNV */
    };
    if (!context->NV_clip_space_w_scaling) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_cluster_acceleration_structure(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          59, /* vkCmdBuildClusterAccelerationStructureIndirectNV */
         464  /* vkGetClusterAccelerationStructureBuildSizesNV */
    };
    if (!context->NV_cluster_acceleration_structure) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_cooperative_matrix(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         553  /* vkGetPhysicalDeviceCooperativeMatrixPropertiesNV */
    };
    if (!context->NV_cooperative_matrix) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_cooperative_matrix2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         551  /* vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV */
    };
    if (!context->NV_cooperative_matrix2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_cooperative_vector(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          66, /* vkCmdConvertCooperativeVectorMatrixNV */
         294, /* vkConvertCooperativeVectorMatrixNV */
         554  /* vkGetPhysicalDeviceCooperativeVectorPropertiesNV */
    };
    if (!context->NV_cooperative_vector) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_copy_memory_indirect(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          82, /* vkCmdCopyMemoryIndirectNV */
          84  /* vkCmdCopyMemoryToImageIndirectNV */
    };
    if (!context->NV_copy_memory_indirect) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_coverage_reduction_mode(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         594  /* vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV */
    };
    if (!context->NV_coverage_reduction_mode) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_cuda_kernel_launch(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          90, /* vkCmdCudaLaunchKernelNV */
         317, /* vkCreateCudaFunctionNV */
         318, /* vkCreateCudaModuleNV */
         389, /* vkDestroyCudaFunctionNV */
         390, /* vkDestroyCudaModuleNV */
         465  /* vkGetCudaModuleCacheNV */
    };
    if (!context->NV_cuda_kernel_launch) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_device_diagnostic_checkpoints(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         174, /* vkCmdSetCheckpointNV */
         624, /* vkGetQueueCheckpointData2NV */
         625  /* vkGetQueueCheckpointDataNV */
    };
    if (!context->NV_device_diagnostic_checkpoints) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_device_generated_commands(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          46, /* vkCmdBindPipelineShaderGroupNV */
         139, /* vkCmdExecuteGeneratedCommandsNV */
         151, /* vkCmdPreprocessGeneratedCommandsNV */
         341, /* vkCreateIndirectCommandsLayoutNV */
         405, /* vkDestroyIndirectCommandsLayoutNV */
         514  /* vkGetGeneratedCommandsMemoryRequirementsNV */
    };
    if (!context->NV_device_generated_commands) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_device_generated_commands_compute(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         281, /* vkCmdUpdatePipelineIndirectBufferNV */
         617, /* vkGetPipelineIndirectDeviceAddressNV */
         618  /* vkGetPipelineIndirectMemoryRequirementsNV */
    };
    if (!context->NV_device_generated_commands_compute) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_external_memory_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         564  /* vkGetPhysicalDeviceExternalImageFormatPropertiesNV */
    };
    if (!context->NV_external_memory_capabilities) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_external_memory_rdma(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         539  /* vkGetMemoryRemoteAddressNV */
    };
    if (!context->NV_external_memory_rdma) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_NV_external_memory_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         541  /* vkGetMemoryWin32HandleNV */
    };
    if (!context->NV_external_memory_win32) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_NV_fragment_shading_rate_enums(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         220  /* vkCmdSetFragmentShadingRateEnumNV */
    };
    if (!context->NV_fragment_shading_rate_enums) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_low_latency2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         532, /* vkGetLatencyTimingsNV */
         659, /* vkLatencySleepNV */
         669, /* vkQueueNotifyOutOfBandNV */
         698, /* vkSetLatencyMarkerNV */
         699  /* vkSetLatencySleepModeNV */
    };
    if (!context->NV_low_latency2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_memory_decompression(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          95, /* vkCmdDecompressMemoryIndirectCountNV */
          96  /* vkCmdDecompressMemoryNV */
    };
    if (!context->NV_memory_decompression) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_mesh_shader(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         119, /* vkCmdDrawMeshTasksIndirectCountNV */
         121, /* vkCmdDrawMeshTasksIndirectNV */
         122  /* vkCmdDrawMeshTasksNV */
    };
    if (!context->NV_mesh_shader) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_optical_flow(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          20, /* vkBindOpticalFlowSessionImageNV */
         146, /* vkCmdOpticalFlowExecuteNV */
         347, /* vkCreateOpticalFlowSessionNV */
         409, /* vkDestroyOpticalFlowSessionNV */
         581  /* vkGetPhysicalDeviceOpticalFlowImageFormatsNV */
    };
    if (!context->NV_optical_flow) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_partitioned_acceleration_structure(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          61, /* vkCmdBuildPartitionedAccelerationStructuresNV */
         546  /* vkGetPartitionedAccelerationStructuresBuildSizesNV */
    };
    if (!context->NV_partitioned_acceleration_structure) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_ray_tracing(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          13, /* vkBindAccelerationStructureMemoryNV */
          56, /* vkCmdBuildAccelerationStructureNV */
          68, /* vkCmdCopyAccelerationStructureNV */
         279, /* vkCmdTraceRaysNV */
         286, /* vkCmdWriteAccelerationStructuresPropertiesNV */
         293, /* vkCompileDeferredNV */
         308, /* vkCreateAccelerationStructureNV */
         355, /* vkCreateRayTracingPipelinesNV */
         382, /* vkDestroyAccelerationStructureNV */
         448, /* vkGetAccelerationStructureHandleNV */
         449, /* vkGetAccelerationStructureMemoryRequirementsNV */
         629  /* vkGetRayTracingShaderGroupHandlesNV */
    };
    if (!context->NV_ray_tracing) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_scissor_exclusive(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         217, /* vkCmdSetExclusiveScissorEnableNV */
         218  /* vkCmdSetExclusiveScissorNV */
    };
    if (!context->NV_scissor_exclusive) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_shading_rate_image(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          48, /* vkCmdBindShadingRateImageNV */
         175, /* vkCmdSetCoarseSampleOrderNV */
         269  /* vkCmdSetViewportShadingRatePaletteNV */
    };
    if (!context->NV_shading_rate_image) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_QCOM_tile_properties(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         504, /* vkGetDynamicRenderingTilePropertiesQCOM */
         512  /* vkGetFramebufferTilePropertiesQCOM */
    };
    if (!context->QCOM_tile_properties) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_SCREEN_QNX)
static void glad_vk_load_VK_QNX_external_memory_screen_buffer(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         636  /* vkGetScreenBufferPropertiesQNX */
    };
    if (!context->QNX_external_memory_screen_buffer) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
static void glad_vk_load_VK_QNX_screen_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         362, /* vkCreateScreenSurfaceQNX */
         590  /* vkGetPhysicalDeviceScreenPresentationSupportQNX */
    };
    if (!context->QNX_screen_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_VALVE_descriptor_set_host_mapping(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         469, /* vkGetDescriptorSetHostMappingVALVE */
         471  /* vkGetDescriptorSetLayoutHostMappingInfoVALVE */
    };
    if (!context->VALVE_descriptor_set_host_mapping) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_resolve_aliases(GladVulkanContext *context) {
    static const GladAliasPair_t s_aliases[] = {
        {   15,   16 }, /* vkBindBufferMemory2 and vkBindBufferMemory2KHR */
        {   16,   15 }, /* vkBindBufferMemory2KHR and vkBindBufferMemory2 */
        {   18,   19 }, /* vkBindImageMemory2 and vkBindImageMemory2KHR */
        {   19,   18 }, /* vkBindImageMemory2KHR and vkBindImageMemory2 */
        {   31,   32 }, /* vkCmdBeginRendering and vkCmdBeginRenderingKHR */
        {   32,   31 }, /* vkCmdBeginRenderingKHR and vkCmdBeginRendering */
        {   29,   30 }, /* vkCmdBeginRenderPass2 and vkCmdBeginRenderPass2KHR */
        {   30,   29 }, /* vkCmdBeginRenderPass2KHR and vkCmdBeginRenderPass2 */
        {   39,   40 }, /* vkCmdBindDescriptorSets2 and vkCmdBindDescriptorSets2KHR */
        {   40,   39 }, /* vkCmdBindDescriptorSets2KHR and vkCmdBindDescriptorSets2 */
        {   42,   43 }, /* vkCmdBindIndexBuffer2 and vkCmdBindIndexBuffer2KHR */
        {   43,   42 }, /* vkCmdBindIndexBuffer2KHR and vkCmdBindIndexBuffer2 */
        {   51,   52 }, /* vkCmdBindVertexBuffers2 and vkCmdBindVertexBuffers2EXT */
        {   52,   51 }, /* vkCmdBindVertexBuffers2EXT and vkCmdBindVertexBuffers2 */
        {   54,   55 }, /* vkCmdBlitImage2 and vkCmdBlitImage2KHR */
        {   55,   54 }, /* vkCmdBlitImage2KHR and vkCmdBlitImage2 */
        {   71,   72 }, /* vkCmdCopyBuffer2 and vkCmdCopyBuffer2KHR */
        {   72,   71 }, /* vkCmdCopyBuffer2KHR and vkCmdCopyBuffer2 */
        {   74,   75 }, /* vkCmdCopyBufferToImage2 and vkCmdCopyBufferToImage2KHR */
        {   75,   74 }, /* vkCmdCopyBufferToImage2KHR and vkCmdCopyBufferToImage2 */
        {   77,   78 }, /* vkCmdCopyImage2 and vkCmdCopyImage2KHR */
        {   78,   77 }, /* vkCmdCopyImage2KHR and vkCmdCopyImage2 */
        {   80,   81 }, /* vkCmdCopyImageToBuffer2 and vkCmdCopyImageToBuffer2KHR */
        {   81,   80 }, /* vkCmdCopyImageToBuffer2KHR and vkCmdCopyImageToBuffer2 */
        {   98,   99 }, /* vkCmdDispatchBase and vkCmdDispatchBaseKHR */
        {   99,   98 }, /* vkCmdDispatchBaseKHR and vkCmdDispatchBase */
        {  109,  110 }, /* vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountAMD */
        {  109,  111 }, /* vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountKHR */
        {  110,  109 }, /* vkCmdDrawIndexedIndirectCountAMD and vkCmdDrawIndexedIndirectCount */
        {  110,  111 }, /* vkCmdDrawIndexedIndirectCountAMD and vkCmdDrawIndexedIndirectCountKHR */
        {  111,  109 }, /* vkCmdDrawIndexedIndirectCountKHR and vkCmdDrawIndexedIndirectCount */
        {  111,  110 }, /* vkCmdDrawIndexedIndirectCountKHR and vkCmdDrawIndexedIndirectCountAMD */
        {  114,  115 }, /* vkCmdDrawIndirectCount and vkCmdDrawIndirectCountAMD */
        {  114,  116 }, /* vkCmdDrawIndirectCount and vkCmdDrawIndirectCountKHR */
        {  115,  114 }, /* vkCmdDrawIndirectCountAMD and vkCmdDrawIndirectCount */
        {  115,  116 }, /* vkCmdDrawIndirectCountAMD and vkCmdDrawIndirectCountKHR */
        {  116,  114 }, /* vkCmdDrawIndirectCountKHR and vkCmdDrawIndirectCount */
        {  116,  115 }, /* vkCmdDrawIndirectCountKHR and vkCmdDrawIndirectCountAMD */
        {  133,  134 }, /* vkCmdEndRendering and vkCmdEndRenderingKHR */
        {  134,  133 }, /* vkCmdEndRenderingKHR and vkCmdEndRendering */
        {  131,  132 }, /* vkCmdEndRenderPass2 and vkCmdEndRenderPass2KHR */
        {  132,  131 }, /* vkCmdEndRenderPass2KHR and vkCmdEndRenderPass2 */
        {  144,  145 }, /* vkCmdNextSubpass2 and vkCmdNextSubpass2KHR */
        {  145,  144 }, /* vkCmdNextSubpass2KHR and vkCmdNextSubpass2 */
        {  148,  149 }, /* vkCmdPipelineBarrier2 and vkCmdPipelineBarrier2KHR */
        {  149,  148 }, /* vkCmdPipelineBarrier2KHR and vkCmdPipelineBarrier2 */
        {  153,  154 }, /* vkCmdPushConstants2 and vkCmdPushConstants2KHR */
        {  154,  153 }, /* vkCmdPushConstants2KHR and vkCmdPushConstants2 */
        {  155,  158 }, /* vkCmdPushDescriptorSet and vkCmdPushDescriptorSetKHR */
        {  156,  157 }, /* vkCmdPushDescriptorSet2 and vkCmdPushDescriptorSet2KHR */
        {  157,  156 }, /* vkCmdPushDescriptorSet2KHR and vkCmdPushDescriptorSet2 */
        {  158,  155 }, /* vkCmdPushDescriptorSetKHR and vkCmdPushDescriptorSet */
        {  159,  162 }, /* vkCmdPushDescriptorSetWithTemplate and vkCmdPushDescriptorSetWithTemplateKHR */
        {  160,  161 }, /* vkCmdPushDescriptorSetWithTemplate2 and vkCmdPushDescriptorSetWithTemplate2KHR */
        {  161,  160 }, /* vkCmdPushDescriptorSetWithTemplate2KHR and vkCmdPushDescriptorSetWithTemplate2 */
        {  162,  159 }, /* vkCmdPushDescriptorSetWithTemplateKHR and vkCmdPushDescriptorSetWithTemplate */
        {  164,  165 }, /* vkCmdResetEvent2 and vkCmdResetEvent2KHR */
        {  165,  164 }, /* vkCmdResetEvent2KHR and vkCmdResetEvent2 */
        {  168,  169 }, /* vkCmdResolveImage2 and vkCmdResolveImage2KHR */
        {  169,  168 }, /* vkCmdResolveImage2KHR and vkCmdResolveImage2 */
        {  188,  189 }, /* vkCmdSetCullMode and vkCmdSetCullModeEXT */
        {  189,  188 }, /* vkCmdSetCullModeEXT and vkCmdSetCullMode */
        {  192,  193 }, /* vkCmdSetDepthBiasEnable and vkCmdSetDepthBiasEnableEXT */
        {  193,  192 }, /* vkCmdSetDepthBiasEnableEXT and vkCmdSetDepthBiasEnable */
        {  195,  196 }, /* vkCmdSetDepthBoundsTestEnable and vkCmdSetDepthBoundsTestEnableEXT */
        {  196,  195 }, /* vkCmdSetDepthBoundsTestEnableEXT and vkCmdSetDepthBoundsTestEnable */
        {  201,  202 }, /* vkCmdSetDepthCompareOp and vkCmdSetDepthCompareOpEXT */
        {  202,  201 }, /* vkCmdSetDepthCompareOpEXT and vkCmdSetDepthCompareOp */
        {  203,  204 }, /* vkCmdSetDepthTestEnable and vkCmdSetDepthTestEnableEXT */
        {  204,  203 }, /* vkCmdSetDepthTestEnableEXT and vkCmdSetDepthTestEnable */
        {  205,  206 }, /* vkCmdSetDepthWriteEnable and vkCmdSetDepthWriteEnableEXT */
        {  206,  205 }, /* vkCmdSetDepthWriteEnableEXT and vkCmdSetDepthWriteEnable */
        {  209,  210 }, /* vkCmdSetDeviceMask and vkCmdSetDeviceMaskKHR */
        {  210,  209 }, /* vkCmdSetDeviceMaskKHR and vkCmdSetDeviceMask */
        {  215,  216 }, /* vkCmdSetEvent2 and vkCmdSetEvent2KHR */
        {  216,  215 }, /* vkCmdSetEvent2KHR and vkCmdSetEvent2 */
        {  222,  223 }, /* vkCmdSetFrontFace and vkCmdSetFrontFaceEXT */
        {  223,  222 }, /* vkCmdSetFrontFaceEXT and vkCmdSetFrontFace */
        {  225,  226 }, /* vkCmdSetLineStipple and vkCmdSetLineStippleEXT */
        {  225,  228 }, /* vkCmdSetLineStipple and vkCmdSetLineStippleKHR */
        {  226,  225 }, /* vkCmdSetLineStippleEXT and vkCmdSetLineStipple */
        {  226,  228 }, /* vkCmdSetLineStippleEXT and vkCmdSetLineStippleKHR */
        {  228,  225 }, /* vkCmdSetLineStippleKHR and vkCmdSetLineStipple */
        {  228,  226 }, /* vkCmdSetLineStippleKHR and vkCmdSetLineStippleEXT */
        {  237,  238 }, /* vkCmdSetPrimitiveRestartEnable and vkCmdSetPrimitiveRestartEnableEXT */
        {  238,  237 }, /* vkCmdSetPrimitiveRestartEnableEXT and vkCmdSetPrimitiveRestartEnable */
        {  239,  240 }, /* vkCmdSetPrimitiveTopology and vkCmdSetPrimitiveTopologyEXT */
        {  240,  239 }, /* vkCmdSetPrimitiveTopologyEXT and vkCmdSetPrimitiveTopology */
        {  244,  245 }, /* vkCmdSetRasterizerDiscardEnable and vkCmdSetRasterizerDiscardEnableEXT */
        {  245,  244 }, /* vkCmdSetRasterizerDiscardEnableEXT and vkCmdSetRasterizerDiscardEnable */
        {  247,  248 }, /* vkCmdSetRenderingAttachmentLocations and vkCmdSetRenderingAttachmentLocationsKHR */
        {  248,  247 }, /* vkCmdSetRenderingAttachmentLocationsKHR and vkCmdSetRenderingAttachmentLocations */
        {  249,  250 }, /* vkCmdSetRenderingInputAttachmentIndices and vkCmdSetRenderingInputAttachmentIndicesKHR */
        {  250,  249 }, /* vkCmdSetRenderingInputAttachmentIndicesKHR and vkCmdSetRenderingInputAttachmentIndices */
        {  256,  257 }, /* vkCmdSetScissorWithCount and vkCmdSetScissorWithCountEXT */
        {  257,  256 }, /* vkCmdSetScissorWithCountEXT and vkCmdSetScissorWithCount */
        {  260,  261 }, /* vkCmdSetStencilOp and vkCmdSetStencilOpEXT */
        {  261,  260 }, /* vkCmdSetStencilOpEXT and vkCmdSetStencilOp */
        {  263,  264 }, /* vkCmdSetStencilTestEnable and vkCmdSetStencilTestEnableEXT */
        {  264,  263 }, /* vkCmdSetStencilTestEnableEXT and vkCmdSetStencilTestEnable */
        {  273,  274 }, /* vkCmdSetViewportWithCount and vkCmdSetViewportWithCountEXT */
        {  274,  273 }, /* vkCmdSetViewportWithCountEXT and vkCmdSetViewportWithCount */
        {  283,  284 }, /* vkCmdWaitEvents2 and vkCmdWaitEvents2KHR */
        {  284,  283 }, /* vkCmdWaitEvents2KHR and vkCmdWaitEvents2 */
        {  291,  292 }, /* vkCmdWriteTimestamp2 and vkCmdWriteTimestamp2KHR */
        {  292,  291 }, /* vkCmdWriteTimestamp2KHR and vkCmdWriteTimestamp2 */
        {  297,  298 }, /* vkCopyImageToImage and vkCopyImageToImageEXT */
        {  298,  297 }, /* vkCopyImageToImageEXT and vkCopyImageToImage */
        {  299,  300 }, /* vkCopyImageToMemory and vkCopyImageToMemoryEXT */
        {  300,  299 }, /* vkCopyImageToMemoryEXT and vkCopyImageToMemory */
        {  302,  303 }, /* vkCopyMemoryToImage and vkCopyMemoryToImageEXT */
        {  303,  302 }, /* vkCopyMemoryToImageEXT and vkCopyMemoryToImage */
        {  324,  325 }, /* vkCreateDescriptorUpdateTemplate and vkCreateDescriptorUpdateTemplateKHR */
        {  325,  324 }, /* vkCreateDescriptorUpdateTemplateKHR and vkCreateDescriptorUpdateTemplate */
        {  351,  352 }, /* vkCreatePrivateDataSlot and vkCreatePrivateDataSlotEXT */
        {  352,  351 }, /* vkCreatePrivateDataSlotEXT and vkCreatePrivateDataSlot */
        {  357,  358 }, /* vkCreateRenderPass2 and vkCreateRenderPass2KHR */
        {  358,  357 }, /* vkCreateRenderPass2KHR and vkCreateRenderPass2 */
        {  360,  361 }, /* vkCreateSamplerYcbcrConversion and vkCreateSamplerYcbcrConversionKHR */
        {  361,  360 }, /* vkCreateSamplerYcbcrConversionKHR and vkCreateSamplerYcbcrConversion */
        {  396,  397 }, /* vkDestroyDescriptorUpdateTemplate and vkDestroyDescriptorUpdateTemplateKHR */
        {  397,  396 }, /* vkDestroyDescriptorUpdateTemplateKHR and vkDestroyDescriptorUpdateTemplate */
        {  414,  415 }, /* vkDestroyPrivateDataSlot and vkDestroyPrivateDataSlotEXT */
        {  415,  414 }, /* vkDestroyPrivateDataSlotEXT and vkDestroyPrivateDataSlot */
        {  419,  420 }, /* vkDestroySamplerYcbcrConversion and vkDestroySamplerYcbcrConversionKHR */
        {  420,  419 }, /* vkDestroySamplerYcbcrConversionKHR and vkDestroySamplerYcbcrConversion */
        {  437,  438 }, /* vkEnumeratePhysicalDeviceGroups and vkEnumeratePhysicalDeviceGroupsKHR */
        {  438,  437 }, /* vkEnumeratePhysicalDeviceGroupsKHR and vkEnumeratePhysicalDeviceGroups */
        {  453,  454 }, /* vkGetBufferDeviceAddress and vkGetBufferDeviceAddressEXT */
        {  453,  455 }, /* vkGetBufferDeviceAddress and vkGetBufferDeviceAddressKHR */
        {  454,  453 }, /* vkGetBufferDeviceAddressEXT and vkGetBufferDeviceAddress */
        {  454,  455 }, /* vkGetBufferDeviceAddressEXT and vkGetBufferDeviceAddressKHR */
        {  455,  453 }, /* vkGetBufferDeviceAddressKHR and vkGetBufferDeviceAddress */
        {  455,  454 }, /* vkGetBufferDeviceAddressKHR and vkGetBufferDeviceAddressEXT */
        {  457,  458 }, /* vkGetBufferMemoryRequirements2 and vkGetBufferMemoryRequirements2KHR */
        {  458,  457 }, /* vkGetBufferMemoryRequirements2KHR and vkGetBufferMemoryRequirements2 */
        {  459,  460 }, /* vkGetBufferOpaqueCaptureAddress and vkGetBufferOpaqueCaptureAddressKHR */
        {  460,  459 }, /* vkGetBufferOpaqueCaptureAddressKHR and vkGetBufferOpaqueCaptureAddress */
        {  462,  463 }, /* vkGetCalibratedTimestampsEXT and vkGetCalibratedTimestampsKHR */
        {  463,  462 }, /* vkGetCalibratedTimestampsKHR and vkGetCalibratedTimestampsEXT */
        {  473,  474 }, /* vkGetDescriptorSetLayoutSupport and vkGetDescriptorSetLayoutSupportKHR */
        {  474,  473 }, /* vkGetDescriptorSetLayoutSupportKHR and vkGetDescriptorSetLayoutSupport */
        {  476,  477 }, /* vkGetDeviceBufferMemoryRequirements and vkGetDeviceBufferMemoryRequirementsKHR */
        {  477,  476 }, /* vkGetDeviceBufferMemoryRequirementsKHR and vkGetDeviceBufferMemoryRequirements */
        {  479,  480 }, /* vkGetDeviceGroupPeerMemoryFeatures and vkGetDeviceGroupPeerMemoryFeaturesKHR */
        {  480,  479 }, /* vkGetDeviceGroupPeerMemoryFeaturesKHR and vkGetDeviceGroupPeerMemoryFeatures */
        {  484,  485 }, /* vkGetDeviceImageMemoryRequirements and vkGetDeviceImageMemoryRequirementsKHR */
        {  485,  484 }, /* vkGetDeviceImageMemoryRequirementsKHR and vkGetDeviceImageMemoryRequirements */
        {  486,  487 }, /* vkGetDeviceImageSparseMemoryRequirements and vkGetDeviceImageSparseMemoryRequirementsKHR */
        {  487,  486 }, /* vkGetDeviceImageSparseMemoryRequirementsKHR and vkGetDeviceImageSparseMemoryRequirements */
        {  488,  489 }, /* vkGetDeviceImageSubresourceLayout and vkGetDeviceImageSubresourceLayoutKHR */
        {  489,  488 }, /* vkGetDeviceImageSubresourceLayoutKHR and vkGetDeviceImageSubresourceLayout */
        {  491,  492 }, /* vkGetDeviceMemoryOpaqueCaptureAddress and vkGetDeviceMemoryOpaqueCaptureAddressKHR */
        {  492,  491 }, /* vkGetDeviceMemoryOpaqueCaptureAddressKHR and vkGetDeviceMemoryOpaqueCaptureAddress */
        {  517,  518 }, /* vkGetImageMemoryRequirements2 and vkGetImageMemoryRequirements2KHR */
        {  518,  517 }, /* vkGetImageMemoryRequirements2KHR and vkGetImageMemoryRequirements2 */
        {  521,  522 }, /* vkGetImageSparseMemoryRequirements2 and vkGetImageSparseMemoryRequirements2KHR */
        {  522,  521 }, /* vkGetImageSparseMemoryRequirements2KHR and vkGetImageSparseMemoryRequirements2 */
        {  524,  525 }, /* vkGetImageSubresourceLayout2 and vkGetImageSubresourceLayout2EXT */
        {  524,  526 }, /* vkGetImageSubresourceLayout2 and vkGetImageSubresourceLayout2KHR */
        {  525,  524 }, /* vkGetImageSubresourceLayout2EXT and vkGetImageSubresourceLayout2 */
        {  525,  526 }, /* vkGetImageSubresourceLayout2EXT and vkGetImageSubresourceLayout2KHR */
        {  526,  524 }, /* vkGetImageSubresourceLayout2KHR and vkGetImageSubresourceLayout2 */
        {  526,  525 }, /* vkGetImageSubresourceLayout2KHR and vkGetImageSubresourceLayout2EXT */
        {  549,  550 }, /* vkGetPhysicalDeviceCalibrateableTimeDomainsEXT and vkGetPhysicalDeviceCalibrateableTimeDomainsKHR */
        {  550,  549 }, /* vkGetPhysicalDeviceCalibrateableTimeDomainsKHR and vkGetPhysicalDeviceCalibrateableTimeDomainsEXT */
        {  560,  561 }, /* vkGetPhysicalDeviceExternalBufferProperties and vkGetPhysicalDeviceExternalBufferPropertiesKHR */
        {  561,  560 }, /* vkGetPhysicalDeviceExternalBufferPropertiesKHR and vkGetPhysicalDeviceExternalBufferProperties */
        {  562,  563 }, /* vkGetPhysicalDeviceExternalFenceProperties and vkGetPhysicalDeviceExternalFencePropertiesKHR */
        {  563,  562 }, /* vkGetPhysicalDeviceExternalFencePropertiesKHR and vkGetPhysicalDeviceExternalFenceProperties */
        {  565,  566 }, /* vkGetPhysicalDeviceExternalSemaphoreProperties and vkGetPhysicalDeviceExternalSemaphorePropertiesKHR */
        {  566,  565 }, /* vkGetPhysicalDeviceExternalSemaphorePropertiesKHR and vkGetPhysicalDeviceExternalSemaphoreProperties */
        {  568,  569 }, /* vkGetPhysicalDeviceFeatures2 and vkGetPhysicalDeviceFeatures2KHR */
        {  569,  568 }, /* vkGetPhysicalDeviceFeatures2KHR and vkGetPhysicalDeviceFeatures2 */
        {  571,  572 }, /* vkGetPhysicalDeviceFormatProperties2 and vkGetPhysicalDeviceFormatProperties2KHR */
        {  572,  571 }, /* vkGetPhysicalDeviceFormatProperties2KHR and vkGetPhysicalDeviceFormatProperties2 */
        {  575,  576 }, /* vkGetPhysicalDeviceImageFormatProperties2 and vkGetPhysicalDeviceImageFormatProperties2KHR */
        {  576,  575 }, /* vkGetPhysicalDeviceImageFormatProperties2KHR and vkGetPhysicalDeviceImageFormatProperties2 */
        {  578,  579 }, /* vkGetPhysicalDeviceMemoryProperties2 and vkGetPhysicalDeviceMemoryProperties2KHR */
        {  579,  578 }, /* vkGetPhysicalDeviceMemoryProperties2KHR and vkGetPhysicalDeviceMemoryProperties2 */
        {  584,  585 }, /* vkGetPhysicalDeviceProperties2 and vkGetPhysicalDeviceProperties2KHR */
        {  585,  584 }, /* vkGetPhysicalDeviceProperties2KHR and vkGetPhysicalDeviceProperties2 */
        {  588,  589 }, /* vkGetPhysicalDeviceQueueFamilyProperties2 and vkGetPhysicalDeviceQueueFamilyProperties2KHR */
        {  589,  588 }, /* vkGetPhysicalDeviceQueueFamilyProperties2KHR and vkGetPhysicalDeviceQueueFamilyProperties2 */
        {  592,  593 }, /* vkGetPhysicalDeviceSparseImageFormatProperties2 and vkGetPhysicalDeviceSparseImageFormatProperties2KHR */
        {  593,  592 }, /* vkGetPhysicalDeviceSparseImageFormatProperties2KHR and vkGetPhysicalDeviceSparseImageFormatProperties2 */
        {  603,  604 }, /* vkGetPhysicalDeviceToolProperties and vkGetPhysicalDeviceToolPropertiesEXT */
        {  604,  603 }, /* vkGetPhysicalDeviceToolPropertiesEXT and vkGetPhysicalDeviceToolProperties */
        {  621,  622 }, /* vkGetPrivateData and vkGetPrivateDataEXT */
        {  622,  621 }, /* vkGetPrivateDataEXT and vkGetPrivateData */
        {  628,  629 }, /* vkGetRayTracingShaderGroupHandlesKHR and vkGetRayTracingShaderGroupHandlesNV */
        {  629,  628 }, /* vkGetRayTracingShaderGroupHandlesNV and vkGetRayTracingShaderGroupHandlesKHR */
        {  633,  634 }, /* vkGetRenderingAreaGranularity and vkGetRenderingAreaGranularityKHR */
        {  634,  633 }, /* vkGetRenderingAreaGranularityKHR and vkGetRenderingAreaGranularity */
        {  637,  638 }, /* vkGetSemaphoreCounterValue and vkGetSemaphoreCounterValueKHR */
        {  638,  637 }, /* vkGetSemaphoreCounterValueKHR and vkGetSemaphoreCounterValue */
        {  661,  662 }, /* vkMapMemory2 and vkMapMemory2KHR */
        {  662,  661 }, /* vkMapMemory2KHR and vkMapMemory2 */
        {  673,  674 }, /* vkQueueSubmit2 and vkQueueSubmit2KHR */
        {  674,  673 }, /* vkQueueSubmit2KHR and vkQueueSubmit2 */
        {  689,  690 }, /* vkResetQueryPool and vkResetQueryPoolEXT */
        {  690,  689 }, /* vkResetQueryPoolEXT and vkResetQueryPool */
        {  701,  702 }, /* vkSetPrivateData and vkSetPrivateDataEXT */
        {  702,  701 }, /* vkSetPrivateDataEXT and vkSetPrivateData */
        {  703,  704 }, /* vkSignalSemaphore and vkSignalSemaphoreKHR */
        {  704,  703 }, /* vkSignalSemaphoreKHR and vkSignalSemaphore */
        {  706,  707 }, /* vkTransitionImageLayout and vkTransitionImageLayoutEXT */
        {  707,  706 }, /* vkTransitionImageLayoutEXT and vkTransitionImageLayout */
        {  708,  709 }, /* vkTrimCommandPool and vkTrimCommandPoolKHR */
        {  709,  708 }, /* vkTrimCommandPoolKHR and vkTrimCommandPool */
        {  712,  713 }, /* vkUnmapMemory2 and vkUnmapMemory2KHR */
        {  713,  712 }, /* vkUnmapMemory2KHR and vkUnmapMemory2 */
        {  714,  715 }, /* vkUpdateDescriptorSetWithTemplate and vkUpdateDescriptorSetWithTemplateKHR */
        {  715,  714 }, /* vkUpdateDescriptorSetWithTemplateKHR and vkUpdateDescriptorSetWithTemplate */
        {  722,  723 }, /* vkWaitSemaphores and vkWaitSemaphoresKHR */
        {  723,  722 }, /* vkWaitSemaphoresKHR and vkWaitSemaphores */
    };
    void **pfnArray = context->pfnArray;
    uint32_t i;

    #ifdef __clang__
    #pragma nounroll
    #endif
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
    int major = 1;
    int minor = 0;

#ifdef VK_VERSION_1_1
    if (!context->glad_vk_instance_version && context->EnumerateInstanceVersion != NULL) {
        VkResult result;

        result = context->EnumerateInstanceVersion(&context->glad_vk_instance_version);
        if (result != VK_SUCCESS)
            context->glad_vk_instance_version = 0;
    }
    major = (int) VK_VERSION_MAJOR(context->glad_vk_instance_version);
    minor = (int) VK_VERSION_MINOR(context->glad_vk_instance_version);
#endif

    if (!context->glad_vk_device_version) {
        if (physical_device != NULL && context->GetPhysicalDeviceProperties != NULL) {
            VkPhysicalDeviceProperties properties;
            context->GetPhysicalDeviceProperties(physical_device, &properties);
            context->glad_vk_device_version = properties.apiVersion;
        }
    }
    if (context->glad_vk_device_version) {
        major = (int) VK_VERSION_MAJOR(context->glad_vk_device_version);
        minor = (int) VK_VERSION_MINOR(context->glad_vk_device_version);
    }

    context->VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
    context->VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
    context->VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
    context->VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;
    context->VERSION_1_4 = (major == 1 && minor >= 4) || major > 1;

    return GLAD_MAKE_VERSION(major, minor);
}

GLAD_NO_INLINE int gladLoadVulkanContextUserPtr(GladVulkanContext *context, VkInstance instance, VkPhysicalDevice physical_device, VkDevice device, GLADuserptrloadfunc load, void *userptr) {
    int version;

    (void)instance;
    (void)device;

#ifdef VK_VERSION_1_1
    context->EnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion)load(userptr, "vkEnumerateInstanceVersion");
#endif

    version = glad_vk_find_core_vulkan(context, physical_device);
    if (!version) {
        return 0;
    }

    glad_vk_load_VK_VERSION_1_0(context, load, userptr);
    glad_vk_load_VK_VERSION_1_1(context, load, userptr);
    glad_vk_load_VK_VERSION_1_2(context, load, userptr);
    glad_vk_load_VK_VERSION_1_3(context, load, userptr);
    glad_vk_load_VK_VERSION_1_4(context, load, userptr);

    if (!glad_vk_find_extensions_vulkan(context, physical_device)) return 0;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    glad_vk_load_VK_AMDX_shader_enqueue(context, load, userptr);
#endif
    glad_vk_load_VK_AMD_anti_lag(context, load, userptr);
    glad_vk_load_VK_AMD_buffer_marker(context, load, userptr);
    glad_vk_load_VK_AMD_display_native_hdr(context, load, userptr);
    glad_vk_load_VK_AMD_draw_indirect_count(context, load, userptr);
    glad_vk_load_VK_AMD_shader_info(context, load, userptr);
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    glad_vk_load_VK_ANDROID_external_memory_android_hardware_buffer(context, load, userptr);
#endif
    glad_vk_load_VK_EXT_acquire_drm_display(context, load, userptr);
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    glad_vk_load_VK_EXT_acquire_xlib_display(context, load, userptr);
#endif
    glad_vk_load_VK_EXT_attachment_feedback_loop_dynamic_state(context, load, userptr);
    glad_vk_load_VK_EXT_buffer_device_address(context, load, userptr);
    glad_vk_load_VK_EXT_calibrated_timestamps(context, load, userptr);
    glad_vk_load_VK_EXT_color_write_enable(context, load, userptr);
    glad_vk_load_VK_EXT_conditional_rendering(context, load, userptr);
    glad_vk_load_VK_EXT_debug_marker(context, load, userptr);
    glad_vk_load_VK_EXT_debug_report(context, load, userptr);
    glad_vk_load_VK_EXT_debug_utils(context, load, userptr);
    glad_vk_load_VK_EXT_depth_bias_control(context, load, userptr);
    glad_vk_load_VK_EXT_depth_clamp_control(context, load, userptr);
    glad_vk_load_VK_EXT_descriptor_buffer(context, load, userptr);
    glad_vk_load_VK_EXT_device_fault(context, load, userptr);
    glad_vk_load_VK_EXT_device_generated_commands(context, load, userptr);
    glad_vk_load_VK_EXT_direct_mode_display(context, load, userptr);
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    glad_vk_load_VK_EXT_directfb_surface(context, load, userptr);
#endif
    glad_vk_load_VK_EXT_discard_rectangles(context, load, userptr);
    glad_vk_load_VK_EXT_display_control(context, load, userptr);
    glad_vk_load_VK_EXT_display_surface_counter(context, load, userptr);
    glad_vk_load_VK_EXT_extended_dynamic_state(context, load, userptr);
    glad_vk_load_VK_EXT_extended_dynamic_state2(context, load, userptr);
    glad_vk_load_VK_EXT_extended_dynamic_state3(context, load, userptr);
    glad_vk_load_VK_EXT_external_memory_host(context, load, userptr);
#if defined(VK_USE_PLATFORM_METAL_EXT)
    glad_vk_load_VK_EXT_external_memory_metal(context, load, userptr);
#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    glad_vk_load_VK_EXT_full_screen_exclusive(context, load, userptr);
#endif
    glad_vk_load_VK_EXT_hdr_metadata(context, load, userptr);
    glad_vk_load_VK_EXT_headless_surface(context, load, userptr);
    glad_vk_load_VK_EXT_host_image_copy(context, load, userptr);
    glad_vk_load_VK_EXT_host_query_reset(context, load, userptr);
    glad_vk_load_VK_EXT_image_compression_control(context, load, userptr);
    glad_vk_load_VK_EXT_image_drm_format_modifier(context, load, userptr);
    glad_vk_load_VK_EXT_line_rasterization(context, load, userptr);
    glad_vk_load_VK_EXT_mesh_shader(context, load, userptr);
#if defined(VK_USE_PLATFORM_METAL_EXT)
    glad_vk_load_VK_EXT_metal_objects(context, load, userptr);
#endif
#if defined(VK_USE_PLATFORM_METAL_EXT)
    glad_vk_load_VK_EXT_metal_surface(context, load, userptr);
#endif
    glad_vk_load_VK_EXT_multi_draw(context, load, userptr);
    glad_vk_load_VK_EXT_opacity_micromap(context, load, userptr);
    glad_vk_load_VK_EXT_pageable_device_local_memory(context, load, userptr);
    glad_vk_load_VK_EXT_pipeline_properties(context, load, userptr);
    glad_vk_load_VK_EXT_private_data(context, load, userptr);
    glad_vk_load_VK_EXT_sample_locations(context, load, userptr);
    glad_vk_load_VK_EXT_shader_module_identifier(context, load, userptr);
    glad_vk_load_VK_EXT_shader_object(context, load, userptr);
    glad_vk_load_VK_EXT_swapchain_maintenance1(context, load, userptr);
    glad_vk_load_VK_EXT_tooling_info(context, load, userptr);
    glad_vk_load_VK_EXT_transform_feedback(context, load, userptr);
    glad_vk_load_VK_EXT_validation_cache(context, load, userptr);
    glad_vk_load_VK_EXT_vertex_input_dynamic_state(context, load, userptr);
#if defined(VK_USE_PLATFORM_FUCHSIA)
    glad_vk_load_VK_FUCHSIA_buffer_collection(context, load, userptr);
#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
    glad_vk_load_VK_FUCHSIA_external_memory(context, load, userptr);
#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
    glad_vk_load_VK_FUCHSIA_external_semaphore(context, load, userptr);
#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
    glad_vk_load_VK_FUCHSIA_imagepipe_surface(context, load, userptr);
#endif
#if defined(VK_USE_PLATFORM_GGP)
    glad_vk_load_VK_GGP_stream_descriptor_surface(context, load, userptr);
#endif
    glad_vk_load_VK_GOOGLE_display_timing(context, load, userptr);
    glad_vk_load_VK_HUAWEI_cluster_culling_shader(context, load, userptr);
    glad_vk_load_VK_HUAWEI_invocation_mask(context, load, userptr);
    glad_vk_load_VK_HUAWEI_subpass_shading(context, load, userptr);
    glad_vk_load_VK_INTEL_performance_query(context, load, userptr);
    glad_vk_load_VK_KHR_acceleration_structure(context, load, userptr);
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    glad_vk_load_VK_KHR_android_surface(context, load, userptr);
#endif
    glad_vk_load_VK_KHR_bind_memory2(context, load, userptr);
    glad_vk_load_VK_KHR_buffer_device_address(context, load, userptr);
    glad_vk_load_VK_KHR_calibrated_timestamps(context, load, userptr);
    glad_vk_load_VK_KHR_cooperative_matrix(context, load, userptr);
    glad_vk_load_VK_KHR_copy_commands2(context, load, userptr);
    glad_vk_load_VK_KHR_create_renderpass2(context, load, userptr);
    glad_vk_load_VK_KHR_deferred_host_operations(context, load, userptr);
    glad_vk_load_VK_KHR_descriptor_update_template(context, load, userptr);
    glad_vk_load_VK_KHR_device_group(context, load, userptr);
    glad_vk_load_VK_KHR_device_group_creation(context, load, userptr);
    glad_vk_load_VK_KHR_display(context, load, userptr);
    glad_vk_load_VK_KHR_display_swapchain(context, load, userptr);
    glad_vk_load_VK_KHR_draw_indirect_count(context, load, userptr);
    glad_vk_load_VK_KHR_dynamic_rendering(context, load, userptr);
    glad_vk_load_VK_KHR_dynamic_rendering_local_read(context, load, userptr);
    glad_vk_load_VK_KHR_external_fence_capabilities(context, load, userptr);
    glad_vk_load_VK_KHR_external_fence_fd(context, load, userptr);
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    glad_vk_load_VK_KHR_external_fence_win32(context, load, userptr);
#endif
    glad_vk_load_VK_KHR_external_memory_capabilities(context, load, userptr);
    glad_vk_load_VK_KHR_external_memory_fd(context, load, userptr);
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    glad_vk_load_VK_KHR_external_memory_win32(context, load, userptr);
#endif
    glad_vk_load_VK_KHR_external_semaphore_capabilities(context, load, userptr);
    glad_vk_load_VK_KHR_external_semaphore_fd(context, load, userptr);
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    glad_vk_load_VK_KHR_external_semaphore_win32(context, load, userptr);
#endif
    glad_vk_load_VK_KHR_fragment_shading_rate(context, load, userptr);
    glad_vk_load_VK_KHR_get_display_properties2(context, load, userptr);
    glad_vk_load_VK_KHR_get_memory_requirements2(context, load, userptr);
    glad_vk_load_VK_KHR_get_physical_device_properties2(context, load, userptr);
    glad_vk_load_VK_KHR_get_surface_capabilities2(context, load, userptr);
    glad_vk_load_VK_KHR_line_rasterization(context, load, userptr);
    glad_vk_load_VK_KHR_maintenance1(context, load, userptr);
    glad_vk_load_VK_KHR_maintenance3(context, load, userptr);
    glad_vk_load_VK_KHR_maintenance4(context, load, userptr);
    glad_vk_load_VK_KHR_maintenance5(context, load, userptr);
    glad_vk_load_VK_KHR_maintenance6(context, load, userptr);
    glad_vk_load_VK_KHR_map_memory2(context, load, userptr);
    glad_vk_load_VK_KHR_performance_query(context, load, userptr);
    glad_vk_load_VK_KHR_pipeline_binary(context, load, userptr);
    glad_vk_load_VK_KHR_pipeline_executable_properties(context, load, userptr);
    glad_vk_load_VK_KHR_present_wait(context, load, userptr);
    glad_vk_load_VK_KHR_push_descriptor(context, load, userptr);
    glad_vk_load_VK_KHR_ray_tracing_maintenance1(context, load, userptr);
    glad_vk_load_VK_KHR_ray_tracing_pipeline(context, load, userptr);
    glad_vk_load_VK_KHR_sampler_ycbcr_conversion(context, load, userptr);
    glad_vk_load_VK_KHR_shared_presentable_image(context, load, userptr);
    glad_vk_load_VK_KHR_surface(context, load, userptr);
    glad_vk_load_VK_KHR_swapchain(context, load, userptr);
    glad_vk_load_VK_KHR_synchronization2(context, load, userptr);
    glad_vk_load_VK_KHR_timeline_semaphore(context, load, userptr);
    glad_vk_load_VK_KHR_video_decode_queue(context, load, userptr);
    glad_vk_load_VK_KHR_video_encode_queue(context, load, userptr);
    glad_vk_load_VK_KHR_video_queue(context, load, userptr);
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    glad_vk_load_VK_KHR_wayland_surface(context, load, userptr);
#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    glad_vk_load_VK_KHR_win32_surface(context, load, userptr);
#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
    glad_vk_load_VK_KHR_xcb_surface(context, load, userptr);
#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    glad_vk_load_VK_KHR_xlib_surface(context, load, userptr);
#endif
#if defined(VK_USE_PLATFORM_IOS_MVK)
    glad_vk_load_VK_MVK_ios_surface(context, load, userptr);
#endif
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    glad_vk_load_VK_MVK_macos_surface(context, load, userptr);
#endif
#if defined(VK_USE_PLATFORM_VI_NN)
    glad_vk_load_VK_NN_vi_surface(context, load, userptr);
#endif
    glad_vk_load_VK_NVX_binary_import(context, load, userptr);
    glad_vk_load_VK_NVX_image_view_handle(context, load, userptr);
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    glad_vk_load_VK_NV_acquire_winrt_display(context, load, userptr);
#endif
    glad_vk_load_VK_NV_clip_space_w_scaling(context, load, userptr);
    glad_vk_load_VK_NV_cluster_acceleration_structure(context, load, userptr);
    glad_vk_load_VK_NV_cooperative_matrix(context, load, userptr);
    glad_vk_load_VK_NV_cooperative_matrix2(context, load, userptr);
    glad_vk_load_VK_NV_cooperative_vector(context, load, userptr);
    glad_vk_load_VK_NV_copy_memory_indirect(context, load, userptr);
    glad_vk_load_VK_NV_coverage_reduction_mode(context, load, userptr);
    glad_vk_load_VK_NV_cuda_kernel_launch(context, load, userptr);
    glad_vk_load_VK_NV_device_diagnostic_checkpoints(context, load, userptr);
    glad_vk_load_VK_NV_device_generated_commands(context, load, userptr);
    glad_vk_load_VK_NV_device_generated_commands_compute(context, load, userptr);
    glad_vk_load_VK_NV_external_memory_capabilities(context, load, userptr);
    glad_vk_load_VK_NV_external_memory_rdma(context, load, userptr);
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    glad_vk_load_VK_NV_external_memory_win32(context, load, userptr);
#endif
    glad_vk_load_VK_NV_fragment_shading_rate_enums(context, load, userptr);
    glad_vk_load_VK_NV_low_latency2(context, load, userptr);
    glad_vk_load_VK_NV_memory_decompression(context, load, userptr);
    glad_vk_load_VK_NV_mesh_shader(context, load, userptr);
    glad_vk_load_VK_NV_optical_flow(context, load, userptr);
    glad_vk_load_VK_NV_partitioned_acceleration_structure(context, load, userptr);
    glad_vk_load_VK_NV_ray_tracing(context, load, userptr);
    glad_vk_load_VK_NV_scissor_exclusive(context, load, userptr);
    glad_vk_load_VK_NV_shading_rate_image(context, load, userptr);
    glad_vk_load_VK_QCOM_tile_properties(context, load, userptr);
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    glad_vk_load_VK_QNX_external_memory_screen_buffer(context, load, userptr);
#endif
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    glad_vk_load_VK_QNX_screen_surface(context, load, userptr);
#endif
    glad_vk_load_VK_VALVE_descriptor_set_host_mapping(context, load, userptr);

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


static uint64_t DEVICE_COMMANDS[] = {
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
    0x39595c56305c625a, /* vkGetDeviceProcAddr */
    0x399268bd1fae323b, /* vkGetBufferDeviceAddressEXT */
    0x3a0a07834723853e, /* vkInvalidateMappedMemoryRanges */
    0x3a28620bd767d9f5, /* vkCmdSetRenderingAttachmentLocations */
    0x3a88835e421d53cd, /* vkDestroyMicromapEXT */
    0x3ac504ab87b15a1d, /* vkCmdDrawMeshTasksIndirectCountEXT */
    0x3cb127add67d0963, /* vkCmdSetDescriptorBufferOffsetsEXT */
    0x3ce0faf5d18dc25b, /* vkCreateAccelerationStructureNV */
    0x3d8f82b873097a02, /* vkGetQueueCheckpointDataNV */
    0x3e094de8a08c3145, /* vkGetImageMemoryRequirements2KHR */
    0x3e52d6e9d1662eb2, /* vkEndCommandBuffer */
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
    0x484c4c652a1f9c0e, /* vkCmdClearAttachments */
    0x4852117a823da29e, /* vkGetImageOpaqueCaptureDescriptorDataEXT */
    0x4888445b33d1d1a9, /* vkCmdSetPerformanceMarkerINTEL */
    0x48e9ce5a58c1c252, /* vkCmdSetPolygonModeEXT */
    0x49a74d66be4fce8b, /* vkGetCalibratedTimestampsEXT */
    0x49bda364217fc34a, /* vkGetPerformanceParameterINTEL */
    0x4afe44fc10e34214, /* vkCmdCopyBufferToImage */
    0x4b963cb16d7a5ad8, /* vkCmdSetTessellationDomainOriginEXT */
    0x4bfeea912504df47, /* vkDestroyVideoSessionKHR */
    0x4c2e756549427154, /* vkCmdPushDescriptorSet2 */
    0x4c351cfa990e9dce, /* vkCmdSetAlphaToCoverageEnableEXT */
    0x4d0e89b321a6faef, /* vkCreateRayTracingPipelinesNV */
    0x4d3f08ecfb5c4893, /* vkCmdCopyBuffer2KHR */
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
    0x7629dff55e4d0af3, /* vkSetLocalDimmingAMD */
    0x76b72b76ccef2958, /* vkDestroyImageView */
    0x76e7d06d87565b38, /* vkCreatePipelineLayout */
    0x77298a207cf7470a, /* vkCmdSetPatchControlPointsEXT */
    0x77ac813268762693, /* vkGetBufferMemoryRequirements2KHR */
    0x7937cbd95db509a9, /* vkCmdSetDepthClampRangeEXT */
    0x79bbe5a8a2c19b65, /* vkCmdSetSampleMaskEXT */
    0x79cca6cf07ff9d67, /* vkCmdSetDepthBounds */
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
    0xaa4956312cfc8f69, /* vkAcquireProfilingLockKHR */
    0xaa6c800d6f3a85cf, /* vkGetClusterAccelerationStructureBuildSizesNV */
    0xaac33dd01204ea6d, /* vkUpdateDescriptorSets */
    0xaae6e3e723f39a93, /* vkCmdCopyBufferToImage2KHR */
    0xaaee8606a2f000f3, /* vkInitializePerformanceApiINTEL */
    0xabb4da3669fa0607, /* vkCmdSetRenderingAttachmentLocationsKHR */
    0xabbbfebcb5e50ddf, /* vkCreateDescriptorSetLayout */
    0xada92dcad41eaf98, /* vkCmdBindDescriptorSets */
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
    0xfc42afaa1bbc54a8, /* vkCreateEvent */
    0xfccd697bc5cf4494, /* vkSetDebugUtilsObjectNameEXT */
    0xfd2a746603a13f60, /* vkCreateRenderPass2 */
    0xfd4ef6a737d2546d, /* vkBindImageMemory2 */
    0xfe4be9de353f2023, /* vkDestroyAccelerationStructureNV */
    0xfe8be5739d1d70ae, /* vkCmdSetCoverageToColorLocationNV */
    0xff17500f60079a4b, /* vkGetRenderingAreaGranularityKHR */
    0xffa40d4e01bf3cc0, /* vkCmdSetViewportWithCountEXT */
};

static int glad_vulkan_is_device_command(uint64_t nameHash) {
    /* Exists as a workaround for:
     * https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/issues/2323
     *
     * `vkGetDeviceProcAddr` does not return NULL for non-device functions.
     */
    return glad_hash_search(DEVICE_COMMANDS, GLAD_ARRAYSIZE(DEVICE_COMMANDS), nameHash);
}

static uint64_t GLOBAL_COMMANDS[] = {
    0x293f4d0e3d436dce, /* vkEnumerateInstanceExtensionProperties */
    0xc930c283b60dafd0, /* vkEnumerateInstanceLayerProperties */
    0xed8a6efd46f4e052, /* vkCreateInstance */
    0xf79cbf7989a3746e, /* vkEnumerateInstanceVersion */
};

static int glad_vulkan_is_global_command(uint64_t nameHash) {
    return glad_hash_search(GLOBAL_COMMANDS, GLAD_ARRAYSIZE(GLOBAL_COMMANDS), nameHash);
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
