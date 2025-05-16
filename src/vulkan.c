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
    /*   26 */ "vkCmdBeginPerTileExecutionQCOM",
    /*   27 */ "vkCmdBeginQuery",
    /*   28 */ "vkCmdBeginQueryIndexedEXT",
    /*   29 */ "vkCmdBeginRenderPass",
    /*   30 */ "vkCmdBeginRenderPass2",
    /*   31 */ "vkCmdBeginRenderPass2KHR",
    /*   32 */ "vkCmdBeginRendering",
    /*   33 */ "vkCmdBeginRenderingKHR",
    /*   34 */ "vkCmdBeginTransformFeedbackEXT",
    /*   35 */ "vkCmdBeginVideoCodingKHR",
    /*   36 */ "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT",
    /*   37 */ "vkCmdBindDescriptorBufferEmbeddedSamplersEXT",
    /*   38 */ "vkCmdBindDescriptorBuffersEXT",
    /*   39 */ "vkCmdBindDescriptorSets",
    /*   40 */ "vkCmdBindDescriptorSets2",
    /*   41 */ "vkCmdBindDescriptorSets2KHR",
    /*   42 */ "vkCmdBindIndexBuffer",
    /*   43 */ "vkCmdBindIndexBuffer2",
    /*   44 */ "vkCmdBindIndexBuffer2KHR",
    /*   45 */ "vkCmdBindInvocationMaskHUAWEI",
    /*   46 */ "vkCmdBindPipeline",
    /*   47 */ "vkCmdBindPipelineShaderGroupNV",
    /*   48 */ "vkCmdBindShadersEXT",
    /*   49 */ "vkCmdBindShadingRateImageNV",
    /*   50 */ "vkCmdBindTileMemoryQCOM",
    /*   51 */ "vkCmdBindTransformFeedbackBuffersEXT",
    /*   52 */ "vkCmdBindVertexBuffers",
    /*   53 */ "vkCmdBindVertexBuffers2",
    /*   54 */ "vkCmdBindVertexBuffers2EXT",
    /*   55 */ "vkCmdBlitImage",
    /*   56 */ "vkCmdBlitImage2",
    /*   57 */ "vkCmdBlitImage2KHR",
    /*   58 */ "vkCmdBuildAccelerationStructureNV",
    /*   59 */ "vkCmdBuildAccelerationStructuresIndirectKHR",
    /*   60 */ "vkCmdBuildAccelerationStructuresKHR",
    /*   61 */ "vkCmdBuildClusterAccelerationStructureIndirectNV",
    /*   62 */ "vkCmdBuildMicromapsEXT",
    /*   63 */ "vkCmdBuildPartitionedAccelerationStructuresNV",
    /*   64 */ "vkCmdClearAttachments",
    /*   65 */ "vkCmdClearColorImage",
    /*   66 */ "vkCmdClearDepthStencilImage",
    /*   67 */ "vkCmdControlVideoCodingKHR",
    /*   68 */ "vkCmdConvertCooperativeVectorMatrixNV",
    /*   69 */ "vkCmdCopyAccelerationStructureKHR",
    /*   70 */ "vkCmdCopyAccelerationStructureNV",
    /*   71 */ "vkCmdCopyAccelerationStructureToMemoryKHR",
    /*   72 */ "vkCmdCopyBuffer",
    /*   73 */ "vkCmdCopyBuffer2",
    /*   74 */ "vkCmdCopyBuffer2KHR",
    /*   75 */ "vkCmdCopyBufferToImage",
    /*   76 */ "vkCmdCopyBufferToImage2",
    /*   77 */ "vkCmdCopyBufferToImage2KHR",
    /*   78 */ "vkCmdCopyImage",
    /*   79 */ "vkCmdCopyImage2",
    /*   80 */ "vkCmdCopyImage2KHR",
    /*   81 */ "vkCmdCopyImageToBuffer",
    /*   82 */ "vkCmdCopyImageToBuffer2",
    /*   83 */ "vkCmdCopyImageToBuffer2KHR",
    /*   84 */ "vkCmdCopyMemoryIndirectNV",
    /*   85 */ "vkCmdCopyMemoryToAccelerationStructureKHR",
    /*   86 */ "vkCmdCopyMemoryToImageIndirectNV",
    /*   87 */ "vkCmdCopyMemoryToMicromapEXT",
    /*   88 */ "vkCmdCopyMicromapEXT",
    /*   89 */ "vkCmdCopyMicromapToMemoryEXT",
    /*   90 */ "vkCmdCopyQueryPoolResults",
    /*   91 */ "vkCmdCuLaunchKernelNVX",
    /*   92 */ "vkCmdCudaLaunchKernelNV",
    /*   93 */ "vkCmdDebugMarkerBeginEXT",
    /*   94 */ "vkCmdDebugMarkerEndEXT",
    /*   95 */ "vkCmdDebugMarkerInsertEXT",
    /*   96 */ "vkCmdDecodeVideoKHR",
    /*   97 */ "vkCmdDecompressMemoryIndirectCountNV",
    /*   98 */ "vkCmdDecompressMemoryNV",
    /*   99 */ "vkCmdDispatch",
    /*  100 */ "vkCmdDispatchBase",
    /*  101 */ "vkCmdDispatchBaseKHR",
    /*  102 */ "vkCmdDispatchGraphAMDX",
    /*  103 */ "vkCmdDispatchGraphIndirectAMDX",
    /*  104 */ "vkCmdDispatchGraphIndirectCountAMDX",
    /*  105 */ "vkCmdDispatchIndirect",
    /*  106 */ "vkCmdDispatchTileQCOM",
    /*  107 */ "vkCmdDraw",
    /*  108 */ "vkCmdDrawClusterHUAWEI",
    /*  109 */ "vkCmdDrawClusterIndirectHUAWEI",
    /*  110 */ "vkCmdDrawIndexed",
    /*  111 */ "vkCmdDrawIndexedIndirect",
    /*  112 */ "vkCmdDrawIndexedIndirectCount",
    /*  113 */ "vkCmdDrawIndexedIndirectCountAMD",
    /*  114 */ "vkCmdDrawIndexedIndirectCountKHR",
    /*  115 */ "vkCmdDrawIndirect",
    /*  116 */ "vkCmdDrawIndirectByteCountEXT",
    /*  117 */ "vkCmdDrawIndirectCount",
    /*  118 */ "vkCmdDrawIndirectCountAMD",
    /*  119 */ "vkCmdDrawIndirectCountKHR",
    /*  120 */ "vkCmdDrawMeshTasksEXT",
    /*  121 */ "vkCmdDrawMeshTasksIndirectCountEXT",
    /*  122 */ "vkCmdDrawMeshTasksIndirectCountNV",
    /*  123 */ "vkCmdDrawMeshTasksIndirectEXT",
    /*  124 */ "vkCmdDrawMeshTasksIndirectNV",
    /*  125 */ "vkCmdDrawMeshTasksNV",
    /*  126 */ "vkCmdDrawMultiEXT",
    /*  127 */ "vkCmdDrawMultiIndexedEXT",
    /*  128 */ "vkCmdEncodeVideoKHR",
    /*  129 */ "vkCmdEndConditionalRenderingEXT",
    /*  130 */ "vkCmdEndDebugUtilsLabelEXT",
    /*  131 */ "vkCmdEndPerTileExecutionQCOM",
    /*  132 */ "vkCmdEndQuery",
    /*  133 */ "vkCmdEndQueryIndexedEXT",
    /*  134 */ "vkCmdEndRenderPass",
    /*  135 */ "vkCmdEndRenderPass2",
    /*  136 */ "vkCmdEndRenderPass2KHR",
    /*  137 */ "vkCmdEndRendering",
    /*  138 */ "vkCmdEndRendering2EXT",
    /*  139 */ "vkCmdEndRenderingKHR",
    /*  140 */ "vkCmdEndTransformFeedbackEXT",
    /*  141 */ "vkCmdEndVideoCodingKHR",
    /*  142 */ "vkCmdExecuteCommands",
    /*  143 */ "vkCmdExecuteGeneratedCommandsEXT",
    /*  144 */ "vkCmdExecuteGeneratedCommandsNV",
    /*  145 */ "vkCmdFillBuffer",
    /*  146 */ "vkCmdInitializeGraphScratchMemoryAMDX",
    /*  147 */ "vkCmdInsertDebugUtilsLabelEXT",
    /*  148 */ "vkCmdNextSubpass",
    /*  149 */ "vkCmdNextSubpass2",
    /*  150 */ "vkCmdNextSubpass2KHR",
    /*  151 */ "vkCmdOpticalFlowExecuteNV",
    /*  152 */ "vkCmdPipelineBarrier",
    /*  153 */ "vkCmdPipelineBarrier2",
    /*  154 */ "vkCmdPipelineBarrier2KHR",
    /*  155 */ "vkCmdPreprocessGeneratedCommandsEXT",
    /*  156 */ "vkCmdPreprocessGeneratedCommandsNV",
    /*  157 */ "vkCmdPushConstants",
    /*  158 */ "vkCmdPushConstants2",
    /*  159 */ "vkCmdPushConstants2KHR",
    /*  160 */ "vkCmdPushDescriptorSet",
    /*  161 */ "vkCmdPushDescriptorSet2",
    /*  162 */ "vkCmdPushDescriptorSet2KHR",
    /*  163 */ "vkCmdPushDescriptorSetKHR",
    /*  164 */ "vkCmdPushDescriptorSetWithTemplate",
    /*  165 */ "vkCmdPushDescriptorSetWithTemplate2",
    /*  166 */ "vkCmdPushDescriptorSetWithTemplate2KHR",
    /*  167 */ "vkCmdPushDescriptorSetWithTemplateKHR",
    /*  168 */ "vkCmdResetEvent",
    /*  169 */ "vkCmdResetEvent2",
    /*  170 */ "vkCmdResetEvent2KHR",
    /*  171 */ "vkCmdResetQueryPool",
    /*  172 */ "vkCmdResolveImage",
    /*  173 */ "vkCmdResolveImage2",
    /*  174 */ "vkCmdResolveImage2KHR",
    /*  175 */ "vkCmdSetAlphaToCoverageEnableEXT",
    /*  176 */ "vkCmdSetAlphaToOneEnableEXT",
    /*  177 */ "vkCmdSetAttachmentFeedbackLoopEnableEXT",
    /*  178 */ "vkCmdSetBlendConstants",
    /*  179 */ "vkCmdSetCheckpointNV",
    /*  180 */ "vkCmdSetCoarseSampleOrderNV",
    /*  181 */ "vkCmdSetColorBlendAdvancedEXT",
    /*  182 */ "vkCmdSetColorBlendEnableEXT",
    /*  183 */ "vkCmdSetColorBlendEquationEXT",
    /*  184 */ "vkCmdSetColorWriteEnableEXT",
    /*  185 */ "vkCmdSetColorWriteMaskEXT",
    /*  186 */ "vkCmdSetConservativeRasterizationModeEXT",
    /*  187 */ "vkCmdSetCoverageModulationModeNV",
    /*  188 */ "vkCmdSetCoverageModulationTableEnableNV",
    /*  189 */ "vkCmdSetCoverageModulationTableNV",
    /*  190 */ "vkCmdSetCoverageReductionModeNV",
    /*  191 */ "vkCmdSetCoverageToColorEnableNV",
    /*  192 */ "vkCmdSetCoverageToColorLocationNV",
    /*  193 */ "vkCmdSetCullMode",
    /*  194 */ "vkCmdSetCullModeEXT",
    /*  195 */ "vkCmdSetDepthBias",
    /*  196 */ "vkCmdSetDepthBias2EXT",
    /*  197 */ "vkCmdSetDepthBiasEnable",
    /*  198 */ "vkCmdSetDepthBiasEnableEXT",
    /*  199 */ "vkCmdSetDepthBounds",
    /*  200 */ "vkCmdSetDepthBoundsTestEnable",
    /*  201 */ "vkCmdSetDepthBoundsTestEnableEXT",
    /*  202 */ "vkCmdSetDepthClampEnableEXT",
    /*  203 */ "vkCmdSetDepthClampRangeEXT",
    /*  204 */ "vkCmdSetDepthClipEnableEXT",
    /*  205 */ "vkCmdSetDepthClipNegativeOneToOneEXT",
    /*  206 */ "vkCmdSetDepthCompareOp",
    /*  207 */ "vkCmdSetDepthCompareOpEXT",
    /*  208 */ "vkCmdSetDepthTestEnable",
    /*  209 */ "vkCmdSetDepthTestEnableEXT",
    /*  210 */ "vkCmdSetDepthWriteEnable",
    /*  211 */ "vkCmdSetDepthWriteEnableEXT",
    /*  212 */ "vkCmdSetDescriptorBufferOffsets2EXT",
    /*  213 */ "vkCmdSetDescriptorBufferOffsetsEXT",
    /*  214 */ "vkCmdSetDeviceMask",
    /*  215 */ "vkCmdSetDeviceMaskKHR",
    /*  216 */ "vkCmdSetDiscardRectangleEXT",
    /*  217 */ "vkCmdSetDiscardRectangleEnableEXT",
    /*  218 */ "vkCmdSetDiscardRectangleModeEXT",
    /*  219 */ "vkCmdSetEvent",
    /*  220 */ "vkCmdSetEvent2",
    /*  221 */ "vkCmdSetEvent2KHR",
    /*  222 */ "vkCmdSetExclusiveScissorEnableNV",
    /*  223 */ "vkCmdSetExclusiveScissorNV",
    /*  224 */ "vkCmdSetExtraPrimitiveOverestimationSizeEXT",
    /*  225 */ "vkCmdSetFragmentShadingRateEnumNV",
    /*  226 */ "vkCmdSetFragmentShadingRateKHR",
    /*  227 */ "vkCmdSetFrontFace",
    /*  228 */ "vkCmdSetFrontFaceEXT",
    /*  229 */ "vkCmdSetLineRasterizationModeEXT",
    /*  230 */ "vkCmdSetLineStipple",
    /*  231 */ "vkCmdSetLineStippleEXT",
    /*  232 */ "vkCmdSetLineStippleEnableEXT",
    /*  233 */ "vkCmdSetLineStippleKHR",
    /*  234 */ "vkCmdSetLineWidth",
    /*  235 */ "vkCmdSetLogicOpEXT",
    /*  236 */ "vkCmdSetLogicOpEnableEXT",
    /*  237 */ "vkCmdSetPatchControlPointsEXT",
    /*  238 */ "vkCmdSetPerformanceMarkerINTEL",
    /*  239 */ "vkCmdSetPerformanceOverrideINTEL",
    /*  240 */ "vkCmdSetPerformanceStreamMarkerINTEL",
    /*  241 */ "vkCmdSetPolygonModeEXT",
    /*  242 */ "vkCmdSetPrimitiveRestartEnable",
    /*  243 */ "vkCmdSetPrimitiveRestartEnableEXT",
    /*  244 */ "vkCmdSetPrimitiveTopology",
    /*  245 */ "vkCmdSetPrimitiveTopologyEXT",
    /*  246 */ "vkCmdSetProvokingVertexModeEXT",
    /*  247 */ "vkCmdSetRasterizationSamplesEXT",
    /*  248 */ "vkCmdSetRasterizationStreamEXT",
    /*  249 */ "vkCmdSetRasterizerDiscardEnable",
    /*  250 */ "vkCmdSetRasterizerDiscardEnableEXT",
    /*  251 */ "vkCmdSetRayTracingPipelineStackSizeKHR",
    /*  252 */ "vkCmdSetRenderingAttachmentLocations",
    /*  253 */ "vkCmdSetRenderingAttachmentLocationsKHR",
    /*  254 */ "vkCmdSetRenderingInputAttachmentIndices",
    /*  255 */ "vkCmdSetRenderingInputAttachmentIndicesKHR",
    /*  256 */ "vkCmdSetRepresentativeFragmentTestEnableNV",
    /*  257 */ "vkCmdSetSampleLocationsEXT",
    /*  258 */ "vkCmdSetSampleLocationsEnableEXT",
    /*  259 */ "vkCmdSetSampleMaskEXT",
    /*  260 */ "vkCmdSetScissor",
    /*  261 */ "vkCmdSetScissorWithCount",
    /*  262 */ "vkCmdSetScissorWithCountEXT",
    /*  263 */ "vkCmdSetShadingRateImageEnableNV",
    /*  264 */ "vkCmdSetStencilCompareMask",
    /*  265 */ "vkCmdSetStencilOp",
    /*  266 */ "vkCmdSetStencilOpEXT",
    /*  267 */ "vkCmdSetStencilReference",
    /*  268 */ "vkCmdSetStencilTestEnable",
    /*  269 */ "vkCmdSetStencilTestEnableEXT",
    /*  270 */ "vkCmdSetStencilWriteMask",
    /*  271 */ "vkCmdSetTessellationDomainOriginEXT",
    /*  272 */ "vkCmdSetVertexInputEXT",
    /*  273 */ "vkCmdSetViewport",
    /*  274 */ "vkCmdSetViewportShadingRatePaletteNV",
    /*  275 */ "vkCmdSetViewportSwizzleNV",
    /*  276 */ "vkCmdSetViewportWScalingEnableNV",
    /*  277 */ "vkCmdSetViewportWScalingNV",
    /*  278 */ "vkCmdSetViewportWithCount",
    /*  279 */ "vkCmdSetViewportWithCountEXT",
    /*  280 */ "vkCmdSubpassShadingHUAWEI",
    /*  281 */ "vkCmdTraceRaysIndirect2KHR",
    /*  282 */ "vkCmdTraceRaysIndirectKHR",
    /*  283 */ "vkCmdTraceRaysKHR",
    /*  284 */ "vkCmdTraceRaysNV",
    /*  285 */ "vkCmdUpdateBuffer",
    /*  286 */ "vkCmdUpdatePipelineIndirectBufferNV",
    /*  287 */ "vkCmdWaitEvents",
    /*  288 */ "vkCmdWaitEvents2",
    /*  289 */ "vkCmdWaitEvents2KHR",
    /*  290 */ "vkCmdWriteAccelerationStructuresPropertiesKHR",
    /*  291 */ "vkCmdWriteAccelerationStructuresPropertiesNV",
    /*  292 */ "vkCmdWriteBufferMarker2AMD",
    /*  293 */ "vkCmdWriteBufferMarkerAMD",
    /*  294 */ "vkCmdWriteMicromapsPropertiesEXT",
    /*  295 */ "vkCmdWriteTimestamp",
    /*  296 */ "vkCmdWriteTimestamp2",
    /*  297 */ "vkCmdWriteTimestamp2KHR",
    /*  298 */ "vkCompileDeferredNV",
    /*  299 */ "vkConvertCooperativeVectorMatrixNV",
    /*  300 */ "vkCopyAccelerationStructureKHR",
    /*  301 */ "vkCopyAccelerationStructureToMemoryKHR",
    /*  302 */ "vkCopyImageToImage",
    /*  303 */ "vkCopyImageToImageEXT",
    /*  304 */ "vkCopyImageToMemory",
    /*  305 */ "vkCopyImageToMemoryEXT",
    /*  306 */ "vkCopyMemoryToAccelerationStructureKHR",
    /*  307 */ "vkCopyMemoryToImage",
    /*  308 */ "vkCopyMemoryToImageEXT",
    /*  309 */ "vkCopyMemoryToMicromapEXT",
    /*  310 */ "vkCopyMicromapEXT",
    /*  311 */ "vkCopyMicromapToMemoryEXT",
    /*  312 */ "vkCreateAccelerationStructureKHR",
    /*  313 */ "vkCreateAccelerationStructureNV",
    /*  314 */ "vkCreateAndroidSurfaceKHR",
    /*  315 */ "vkCreateBuffer",
    /*  316 */ "vkCreateBufferCollectionFUCHSIA",
    /*  317 */ "vkCreateBufferView",
    /*  318 */ "vkCreateCommandPool",
    /*  319 */ "vkCreateComputePipelines",
    /*  320 */ "vkCreateCuFunctionNVX",
    /*  321 */ "vkCreateCuModuleNVX",
    /*  322 */ "vkCreateCudaFunctionNV",
    /*  323 */ "vkCreateCudaModuleNV",
    /*  324 */ "vkCreateDebugReportCallbackEXT",
    /*  325 */ "vkCreateDebugUtilsMessengerEXT",
    /*  326 */ "vkCreateDeferredOperationKHR",
    /*  327 */ "vkCreateDescriptorPool",
    /*  328 */ "vkCreateDescriptorSetLayout",
    /*  329 */ "vkCreateDescriptorUpdateTemplate",
    /*  330 */ "vkCreateDescriptorUpdateTemplateKHR",
    /*  331 */ "vkCreateDevice",
    /*  332 */ "vkCreateDirectFBSurfaceEXT",
    /*  333 */ "vkCreateDisplayModeKHR",
    /*  334 */ "vkCreateDisplayPlaneSurfaceKHR",
    /*  335 */ "vkCreateEvent",
    /*  336 */ "vkCreateExecutionGraphPipelinesAMDX",
    /*  337 */ "vkCreateExternalComputeQueueNV",
    /*  338 */ "vkCreateFence",
    /*  339 */ "vkCreateFramebuffer",
    /*  340 */ "vkCreateGraphicsPipelines",
    /*  341 */ "vkCreateHeadlessSurfaceEXT",
    /*  342 */ "vkCreateIOSSurfaceMVK",
    /*  343 */ "vkCreateImage",
    /*  344 */ "vkCreateImagePipeSurfaceFUCHSIA",
    /*  345 */ "vkCreateImageView",
    /*  346 */ "vkCreateIndirectCommandsLayoutEXT",
    /*  347 */ "vkCreateIndirectCommandsLayoutNV",
    /*  348 */ "vkCreateIndirectExecutionSetEXT",
    /*  349 */ "vkCreateInstance",
    /*  350 */ "vkCreateMacOSSurfaceMVK",
    /*  351 */ "vkCreateMetalSurfaceEXT",
    /*  352 */ "vkCreateMicromapEXT",
    /*  353 */ "vkCreateOpticalFlowSessionNV",
    /*  354 */ "vkCreatePipelineBinariesKHR",
    /*  355 */ "vkCreatePipelineCache",
    /*  356 */ "vkCreatePipelineLayout",
    /*  357 */ "vkCreatePrivateDataSlot",
    /*  358 */ "vkCreatePrivateDataSlotEXT",
    /*  359 */ "vkCreateQueryPool",
    /*  360 */ "vkCreateRayTracingPipelinesKHR",
    /*  361 */ "vkCreateRayTracingPipelinesNV",
    /*  362 */ "vkCreateRenderPass",
    /*  363 */ "vkCreateRenderPass2",
    /*  364 */ "vkCreateRenderPass2KHR",
    /*  365 */ "vkCreateSampler",
    /*  366 */ "vkCreateSamplerYcbcrConversion",
    /*  367 */ "vkCreateSamplerYcbcrConversionKHR",
    /*  368 */ "vkCreateScreenSurfaceQNX",
    /*  369 */ "vkCreateSemaphore",
    /*  370 */ "vkCreateShaderModule",
    /*  371 */ "vkCreateShadersEXT",
    /*  372 */ "vkCreateSharedSwapchainsKHR",
    /*  373 */ "vkCreateStreamDescriptorSurfaceGGP",
    /*  374 */ "vkCreateSwapchainKHR",
    /*  375 */ "vkCreateValidationCacheEXT",
    /*  376 */ "vkCreateViSurfaceNN",
    /*  377 */ "vkCreateVideoSessionKHR",
    /*  378 */ "vkCreateVideoSessionParametersKHR",
    /*  379 */ "vkCreateWaylandSurfaceKHR",
    /*  380 */ "vkCreateWin32SurfaceKHR",
    /*  381 */ "vkCreateXcbSurfaceKHR",
    /*  382 */ "vkCreateXlibSurfaceKHR",
    /*  383 */ "vkDebugMarkerSetObjectNameEXT",
    /*  384 */ "vkDebugMarkerSetObjectTagEXT",
    /*  385 */ "vkDebugReportMessageEXT",
    /*  386 */ "vkDeferredOperationJoinKHR",
    /*  387 */ "vkDestroyAccelerationStructureKHR",
    /*  388 */ "vkDestroyAccelerationStructureNV",
    /*  389 */ "vkDestroyBuffer",
    /*  390 */ "vkDestroyBufferCollectionFUCHSIA",
    /*  391 */ "vkDestroyBufferView",
    /*  392 */ "vkDestroyCommandPool",
    /*  393 */ "vkDestroyCuFunctionNVX",
    /*  394 */ "vkDestroyCuModuleNVX",
    /*  395 */ "vkDestroyCudaFunctionNV",
    /*  396 */ "vkDestroyCudaModuleNV",
    /*  397 */ "vkDestroyDebugReportCallbackEXT",
    /*  398 */ "vkDestroyDebugUtilsMessengerEXT",
    /*  399 */ "vkDestroyDeferredOperationKHR",
    /*  400 */ "vkDestroyDescriptorPool",
    /*  401 */ "vkDestroyDescriptorSetLayout",
    /*  402 */ "vkDestroyDescriptorUpdateTemplate",
    /*  403 */ "vkDestroyDescriptorUpdateTemplateKHR",
    /*  404 */ "vkDestroyDevice",
    /*  405 */ "vkDestroyEvent",
    /*  406 */ "vkDestroyExternalComputeQueueNV",
    /*  407 */ "vkDestroyFence",
    /*  408 */ "vkDestroyFramebuffer",
    /*  409 */ "vkDestroyImage",
    /*  410 */ "vkDestroyImageView",
    /*  411 */ "vkDestroyIndirectCommandsLayoutEXT",
    /*  412 */ "vkDestroyIndirectCommandsLayoutNV",
    /*  413 */ "vkDestroyIndirectExecutionSetEXT",
    /*  414 */ "vkDestroyInstance",
    /*  415 */ "vkDestroyMicromapEXT",
    /*  416 */ "vkDestroyOpticalFlowSessionNV",
    /*  417 */ "vkDestroyPipeline",
    /*  418 */ "vkDestroyPipelineBinaryKHR",
    /*  419 */ "vkDestroyPipelineCache",
    /*  420 */ "vkDestroyPipelineLayout",
    /*  421 */ "vkDestroyPrivateDataSlot",
    /*  422 */ "vkDestroyPrivateDataSlotEXT",
    /*  423 */ "vkDestroyQueryPool",
    /*  424 */ "vkDestroyRenderPass",
    /*  425 */ "vkDestroySampler",
    /*  426 */ "vkDestroySamplerYcbcrConversion",
    /*  427 */ "vkDestroySamplerYcbcrConversionKHR",
    /*  428 */ "vkDestroySemaphore",
    /*  429 */ "vkDestroyShaderEXT",
    /*  430 */ "vkDestroyShaderModule",
    /*  431 */ "vkDestroySurfaceKHR",
    /*  432 */ "vkDestroySwapchainKHR",
    /*  433 */ "vkDestroyValidationCacheEXT",
    /*  434 */ "vkDestroyVideoSessionKHR",
    /*  435 */ "vkDestroyVideoSessionParametersKHR",
    /*  436 */ "vkDeviceWaitIdle",
    /*  437 */ "vkDisplayPowerControlEXT",
    /*  438 */ "vkEndCommandBuffer",
    /*  439 */ "vkEnumerateDeviceExtensionProperties",
    /*  440 */ "vkEnumerateDeviceLayerProperties",
    /*  441 */ "vkEnumerateInstanceExtensionProperties",
    /*  442 */ "vkEnumerateInstanceLayerProperties",
    /*  443 */ "vkEnumerateInstanceVersion",
    /*  444 */ "vkEnumeratePhysicalDeviceGroups",
    /*  445 */ "vkEnumeratePhysicalDeviceGroupsKHR",
    /*  446 */ "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR",
    /*  447 */ "vkEnumeratePhysicalDevices",
    /*  448 */ "vkExportMetalObjectsEXT",
    /*  449 */ "vkFlushMappedMemoryRanges",
    /*  450 */ "vkFreeCommandBuffers",
    /*  451 */ "vkFreeDescriptorSets",
    /*  452 */ "vkFreeMemory",
    /*  453 */ "vkGetAccelerationStructureBuildSizesKHR",
    /*  454 */ "vkGetAccelerationStructureDeviceAddressKHR",
    /*  455 */ "vkGetAccelerationStructureHandleNV",
    /*  456 */ "vkGetAccelerationStructureMemoryRequirementsNV",
    /*  457 */ "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT",
    /*  458 */ "vkGetAndroidHardwareBufferPropertiesANDROID",
    /*  459 */ "vkGetBufferCollectionPropertiesFUCHSIA",
    /*  460 */ "vkGetBufferDeviceAddress",
    /*  461 */ "vkGetBufferDeviceAddressEXT",
    /*  462 */ "vkGetBufferDeviceAddressKHR",
    /*  463 */ "vkGetBufferMemoryRequirements",
    /*  464 */ "vkGetBufferMemoryRequirements2",
    /*  465 */ "vkGetBufferMemoryRequirements2KHR",
    /*  466 */ "vkGetBufferOpaqueCaptureAddress",
    /*  467 */ "vkGetBufferOpaqueCaptureAddressKHR",
    /*  468 */ "vkGetBufferOpaqueCaptureDescriptorDataEXT",
    /*  469 */ "vkGetCalibratedTimestampsEXT",
    /*  470 */ "vkGetCalibratedTimestampsKHR",
    /*  471 */ "vkGetClusterAccelerationStructureBuildSizesNV",
    /*  472 */ "vkGetCudaModuleCacheNV",
    /*  473 */ "vkGetDeferredOperationMaxConcurrencyKHR",
    /*  474 */ "vkGetDeferredOperationResultKHR",
    /*  475 */ "vkGetDescriptorEXT",
    /*  476 */ "vkGetDescriptorSetHostMappingVALVE",
    /*  477 */ "vkGetDescriptorSetLayoutBindingOffsetEXT",
    /*  478 */ "vkGetDescriptorSetLayoutHostMappingInfoVALVE",
    /*  479 */ "vkGetDescriptorSetLayoutSizeEXT",
    /*  480 */ "vkGetDescriptorSetLayoutSupport",
    /*  481 */ "vkGetDescriptorSetLayoutSupportKHR",
    /*  482 */ "vkGetDeviceAccelerationStructureCompatibilityKHR",
    /*  483 */ "vkGetDeviceBufferMemoryRequirements",
    /*  484 */ "vkGetDeviceBufferMemoryRequirementsKHR",
    /*  485 */ "vkGetDeviceFaultInfoEXT",
    /*  486 */ "vkGetDeviceGroupPeerMemoryFeatures",
    /*  487 */ "vkGetDeviceGroupPeerMemoryFeaturesKHR",
    /*  488 */ "vkGetDeviceGroupPresentCapabilitiesKHR",
    /*  489 */ "vkGetDeviceGroupSurfacePresentModes2EXT",
    /*  490 */ "vkGetDeviceGroupSurfacePresentModesKHR",
    /*  491 */ "vkGetDeviceImageMemoryRequirements",
    /*  492 */ "vkGetDeviceImageMemoryRequirementsKHR",
    /*  493 */ "vkGetDeviceImageSparseMemoryRequirements",
    /*  494 */ "vkGetDeviceImageSparseMemoryRequirementsKHR",
    /*  495 */ "vkGetDeviceImageSubresourceLayout",
    /*  496 */ "vkGetDeviceImageSubresourceLayoutKHR",
    /*  497 */ "vkGetDeviceMemoryCommitment",
    /*  498 */ "vkGetDeviceMemoryOpaqueCaptureAddress",
    /*  499 */ "vkGetDeviceMemoryOpaqueCaptureAddressKHR",
    /*  500 */ "vkGetDeviceMicromapCompatibilityEXT",
    /*  501 */ "vkGetDeviceProcAddr",
    /*  502 */ "vkGetDeviceQueue",
    /*  503 */ "vkGetDeviceQueue2",
    /*  504 */ "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI",
    /*  505 */ "vkGetDisplayModeProperties2KHR",
    /*  506 */ "vkGetDisplayModePropertiesKHR",
    /*  507 */ "vkGetDisplayPlaneCapabilities2KHR",
    /*  508 */ "vkGetDisplayPlaneCapabilitiesKHR",
    /*  509 */ "vkGetDisplayPlaneSupportedDisplaysKHR",
    /*  510 */ "vkGetDrmDisplayEXT",
    /*  511 */ "vkGetDynamicRenderingTilePropertiesQCOM",
    /*  512 */ "vkGetEncodedVideoSessionParametersKHR",
    /*  513 */ "vkGetEventStatus",
    /*  514 */ "vkGetExecutionGraphPipelineNodeIndexAMDX",
    /*  515 */ "vkGetExecutionGraphPipelineScratchSizeAMDX",
    /*  516 */ "vkGetExternalComputeQueueDataNV",
    /*  517 */ "vkGetFenceFdKHR",
    /*  518 */ "vkGetFenceStatus",
    /*  519 */ "vkGetFenceWin32HandleKHR",
    /*  520 */ "vkGetFramebufferTilePropertiesQCOM",
    /*  521 */ "vkGetGeneratedCommandsMemoryRequirementsEXT",
    /*  522 */ "vkGetGeneratedCommandsMemoryRequirementsNV",
    /*  523 */ "vkGetImageDrmFormatModifierPropertiesEXT",
    /*  524 */ "vkGetImageMemoryRequirements",
    /*  525 */ "vkGetImageMemoryRequirements2",
    /*  526 */ "vkGetImageMemoryRequirements2KHR",
    /*  527 */ "vkGetImageOpaqueCaptureDescriptorDataEXT",
    /*  528 */ "vkGetImageSparseMemoryRequirements",
    /*  529 */ "vkGetImageSparseMemoryRequirements2",
    /*  530 */ "vkGetImageSparseMemoryRequirements2KHR",
    /*  531 */ "vkGetImageSubresourceLayout",
    /*  532 */ "vkGetImageSubresourceLayout2",
    /*  533 */ "vkGetImageSubresourceLayout2EXT",
    /*  534 */ "vkGetImageSubresourceLayout2KHR",
    /*  535 */ "vkGetImageViewAddressNVX",
    /*  536 */ "vkGetImageViewHandle64NVX",
    /*  537 */ "vkGetImageViewHandleNVX",
    /*  538 */ "vkGetImageViewOpaqueCaptureDescriptorDataEXT",
    /*  539 */ "vkGetInstanceProcAddr",
    /*  540 */ "vkGetLatencyTimingsNV",
    /*  541 */ "vkGetMemoryAndroidHardwareBufferANDROID",
    /*  542 */ "vkGetMemoryFdKHR",
    /*  543 */ "vkGetMemoryFdPropertiesKHR",
    /*  544 */ "vkGetMemoryHostPointerPropertiesEXT",
    /*  545 */ "vkGetMemoryMetalHandleEXT",
    /*  546 */ "vkGetMemoryMetalHandlePropertiesEXT",
    /*  547 */ "vkGetMemoryRemoteAddressNV",
    /*  548 */ "vkGetMemoryWin32HandleKHR",
    /*  549 */ "vkGetMemoryWin32HandleNV",
    /*  550 */ "vkGetMemoryWin32HandlePropertiesKHR",
    /*  551 */ "vkGetMemoryZirconHandleFUCHSIA",
    /*  552 */ "vkGetMemoryZirconHandlePropertiesFUCHSIA",
    /*  553 */ "vkGetMicromapBuildSizesEXT",
    /*  554 */ "vkGetPartitionedAccelerationStructuresBuildSizesNV",
    /*  555 */ "vkGetPastPresentationTimingGOOGLE",
    /*  556 */ "vkGetPerformanceParameterINTEL",
    /*  557 */ "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT",
    /*  558 */ "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR",
    /*  559 */ "vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV",
    /*  560 */ "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR",
    /*  561 */ "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV",
    /*  562 */ "vkGetPhysicalDeviceCooperativeVectorPropertiesNV",
    /*  563 */ "vkGetPhysicalDeviceDirectFBPresentationSupportEXT",
    /*  564 */ "vkGetPhysicalDeviceDisplayPlaneProperties2KHR",
    /*  565 */ "vkGetPhysicalDeviceDisplayPlanePropertiesKHR",
    /*  566 */ "vkGetPhysicalDeviceDisplayProperties2KHR",
    /*  567 */ "vkGetPhysicalDeviceDisplayPropertiesKHR",
    /*  568 */ "vkGetPhysicalDeviceExternalBufferProperties",
    /*  569 */ "vkGetPhysicalDeviceExternalBufferPropertiesKHR",
    /*  570 */ "vkGetPhysicalDeviceExternalFenceProperties",
    /*  571 */ "vkGetPhysicalDeviceExternalFencePropertiesKHR",
    /*  572 */ "vkGetPhysicalDeviceExternalImageFormatPropertiesNV",
    /*  573 */ "vkGetPhysicalDeviceExternalSemaphoreProperties",
    /*  574 */ "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR",
    /*  575 */ "vkGetPhysicalDeviceFeatures",
    /*  576 */ "vkGetPhysicalDeviceFeatures2",
    /*  577 */ "vkGetPhysicalDeviceFeatures2KHR",
    /*  578 */ "vkGetPhysicalDeviceFormatProperties",
    /*  579 */ "vkGetPhysicalDeviceFormatProperties2",
    /*  580 */ "vkGetPhysicalDeviceFormatProperties2KHR",
    /*  581 */ "vkGetPhysicalDeviceFragmentShadingRatesKHR",
    /*  582 */ "vkGetPhysicalDeviceImageFormatProperties",
    /*  583 */ "vkGetPhysicalDeviceImageFormatProperties2",
    /*  584 */ "vkGetPhysicalDeviceImageFormatProperties2KHR",
    /*  585 */ "vkGetPhysicalDeviceMemoryProperties",
    /*  586 */ "vkGetPhysicalDeviceMemoryProperties2",
    /*  587 */ "vkGetPhysicalDeviceMemoryProperties2KHR",
    /*  588 */ "vkGetPhysicalDeviceMultisamplePropertiesEXT",
    /*  589 */ "vkGetPhysicalDeviceOpticalFlowImageFormatsNV",
    /*  590 */ "vkGetPhysicalDevicePresentRectanglesKHR",
    /*  591 */ "vkGetPhysicalDeviceProperties",
    /*  592 */ "vkGetPhysicalDeviceProperties2",
    /*  593 */ "vkGetPhysicalDeviceProperties2KHR",
    /*  594 */ "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR",
    /*  595 */ "vkGetPhysicalDeviceQueueFamilyProperties",
    /*  596 */ "vkGetPhysicalDeviceQueueFamilyProperties2",
    /*  597 */ "vkGetPhysicalDeviceQueueFamilyProperties2KHR",
    /*  598 */ "vkGetPhysicalDeviceScreenPresentationSupportQNX",
    /*  599 */ "vkGetPhysicalDeviceSparseImageFormatProperties",
    /*  600 */ "vkGetPhysicalDeviceSparseImageFormatProperties2",
    /*  601 */ "vkGetPhysicalDeviceSparseImageFormatProperties2KHR",
    /*  602 */ "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV",
    /*  603 */ "vkGetPhysicalDeviceSurfaceCapabilities2EXT",
    /*  604 */ "vkGetPhysicalDeviceSurfaceCapabilities2KHR",
    /*  605 */ "vkGetPhysicalDeviceSurfaceCapabilitiesKHR",
    /*  606 */ "vkGetPhysicalDeviceSurfaceFormats2KHR",
    /*  607 */ "vkGetPhysicalDeviceSurfaceFormatsKHR",
    /*  608 */ "vkGetPhysicalDeviceSurfacePresentModes2EXT",
    /*  609 */ "vkGetPhysicalDeviceSurfacePresentModesKHR",
    /*  610 */ "vkGetPhysicalDeviceSurfaceSupportKHR",
    /*  611 */ "vkGetPhysicalDeviceToolProperties",
    /*  612 */ "vkGetPhysicalDeviceToolPropertiesEXT",
    /*  613 */ "vkGetPhysicalDeviceVideoCapabilitiesKHR",
    /*  614 */ "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR",
    /*  615 */ "vkGetPhysicalDeviceVideoFormatPropertiesKHR",
    /*  616 */ "vkGetPhysicalDeviceWaylandPresentationSupportKHR",
    /*  617 */ "vkGetPhysicalDeviceWin32PresentationSupportKHR",
    /*  618 */ "vkGetPhysicalDeviceXcbPresentationSupportKHR",
    /*  619 */ "vkGetPhysicalDeviceXlibPresentationSupportKHR",
    /*  620 */ "vkGetPipelineBinaryDataKHR",
    /*  621 */ "vkGetPipelineCacheData",
    /*  622 */ "vkGetPipelineExecutableInternalRepresentationsKHR",
    /*  623 */ "vkGetPipelineExecutablePropertiesKHR",
    /*  624 */ "vkGetPipelineExecutableStatisticsKHR",
    /*  625 */ "vkGetPipelineIndirectDeviceAddressNV",
    /*  626 */ "vkGetPipelineIndirectMemoryRequirementsNV",
    /*  627 */ "vkGetPipelineKeyKHR",
    /*  628 */ "vkGetPipelinePropertiesEXT",
    /*  629 */ "vkGetPrivateData",
    /*  630 */ "vkGetPrivateDataEXT",
    /*  631 */ "vkGetQueryPoolResults",
    /*  632 */ "vkGetQueueCheckpointData2NV",
    /*  633 */ "vkGetQueueCheckpointDataNV",
    /*  634 */ "vkGetRandROutputDisplayEXT",
    /*  635 */ "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR",
    /*  636 */ "vkGetRayTracingShaderGroupHandlesKHR",
    /*  637 */ "vkGetRayTracingShaderGroupHandlesNV",
    /*  638 */ "vkGetRayTracingShaderGroupStackSizeKHR",
    /*  639 */ "vkGetRefreshCycleDurationGOOGLE",
    /*  640 */ "vkGetRenderAreaGranularity",
    /*  641 */ "vkGetRenderingAreaGranularity",
    /*  642 */ "vkGetRenderingAreaGranularityKHR",
    /*  643 */ "vkGetSamplerOpaqueCaptureDescriptorDataEXT",
    /*  644 */ "vkGetScreenBufferPropertiesQNX",
    /*  645 */ "vkGetSemaphoreCounterValue",
    /*  646 */ "vkGetSemaphoreCounterValueKHR",
    /*  647 */ "vkGetSemaphoreFdKHR",
    /*  648 */ "vkGetSemaphoreWin32HandleKHR",
    /*  649 */ "vkGetSemaphoreZirconHandleFUCHSIA",
    /*  650 */ "vkGetShaderBinaryDataEXT",
    /*  651 */ "vkGetShaderInfoAMD",
    /*  652 */ "vkGetShaderModuleCreateInfoIdentifierEXT",
    /*  653 */ "vkGetShaderModuleIdentifierEXT",
    /*  654 */ "vkGetSwapchainCounterEXT",
    /*  655 */ "vkGetSwapchainImagesKHR",
    /*  656 */ "vkGetSwapchainStatusKHR",
    /*  657 */ "vkGetValidationCacheDataEXT",
    /*  658 */ "vkGetVideoSessionMemoryRequirementsKHR",
    /*  659 */ "vkGetWinrtDisplayNV",
    /*  660 */ "vkImportFenceFdKHR",
    /*  661 */ "vkImportFenceWin32HandleKHR",
    /*  662 */ "vkImportSemaphoreFdKHR",
    /*  663 */ "vkImportSemaphoreWin32HandleKHR",
    /*  664 */ "vkImportSemaphoreZirconHandleFUCHSIA",
    /*  665 */ "vkInitializePerformanceApiINTEL",
    /*  666 */ "vkInvalidateMappedMemoryRanges",
    /*  667 */ "vkLatencySleepNV",
    /*  668 */ "vkMapMemory",
    /*  669 */ "vkMapMemory2",
    /*  670 */ "vkMapMemory2KHR",
    /*  671 */ "vkMergePipelineCaches",
    /*  672 */ "vkMergeValidationCachesEXT",
    /*  673 */ "vkQueueBeginDebugUtilsLabelEXT",
    /*  674 */ "vkQueueBindSparse",
    /*  675 */ "vkQueueEndDebugUtilsLabelEXT",
    /*  676 */ "vkQueueInsertDebugUtilsLabelEXT",
    /*  677 */ "vkQueueNotifyOutOfBandNV",
    /*  678 */ "vkQueuePresentKHR",
    /*  679 */ "vkQueueSetPerformanceConfigurationINTEL",
    /*  680 */ "vkQueueSubmit",
    /*  681 */ "vkQueueSubmit2",
    /*  682 */ "vkQueueSubmit2KHR",
    /*  683 */ "vkQueueWaitIdle",
    /*  684 */ "vkRegisterDeviceEventEXT",
    /*  685 */ "vkRegisterDisplayEventEXT",
    /*  686 */ "vkReleaseCapturedPipelineDataKHR",
    /*  687 */ "vkReleaseDisplayEXT",
    /*  688 */ "vkReleaseFullScreenExclusiveModeEXT",
    /*  689 */ "vkReleasePerformanceConfigurationINTEL",
    /*  690 */ "vkReleaseProfilingLockKHR",
    /*  691 */ "vkReleaseSwapchainImagesEXT",
    /*  692 */ "vkResetCommandBuffer",
    /*  693 */ "vkResetCommandPool",
    /*  694 */ "vkResetDescriptorPool",
    /*  695 */ "vkResetEvent",
    /*  696 */ "vkResetFences",
    /*  697 */ "vkResetQueryPool",
    /*  698 */ "vkResetQueryPoolEXT",
    /*  699 */ "vkSetBufferCollectionBufferConstraintsFUCHSIA",
    /*  700 */ "vkSetBufferCollectionImageConstraintsFUCHSIA",
    /*  701 */ "vkSetDebugUtilsObjectNameEXT",
    /*  702 */ "vkSetDebugUtilsObjectTagEXT",
    /*  703 */ "vkSetDeviceMemoryPriorityEXT",
    /*  704 */ "vkSetEvent",
    /*  705 */ "vkSetHdrMetadataEXT",
    /*  706 */ "vkSetLatencyMarkerNV",
    /*  707 */ "vkSetLatencySleepModeNV",
    /*  708 */ "vkSetLocalDimmingAMD",
    /*  709 */ "vkSetPrivateData",
    /*  710 */ "vkSetPrivateDataEXT",
    /*  711 */ "vkSignalSemaphore",
    /*  712 */ "vkSignalSemaphoreKHR",
    /*  713 */ "vkSubmitDebugUtilsMessageEXT",
    /*  714 */ "vkTransitionImageLayout",
    /*  715 */ "vkTransitionImageLayoutEXT",
    /*  716 */ "vkTrimCommandPool",
    /*  717 */ "vkTrimCommandPoolKHR",
    /*  718 */ "vkUninitializePerformanceApiINTEL",
    /*  719 */ "vkUnmapMemory",
    /*  720 */ "vkUnmapMemory2",
    /*  721 */ "vkUnmapMemory2KHR",
    /*  722 */ "vkUpdateDescriptorSetWithTemplate",
    /*  723 */ "vkUpdateDescriptorSetWithTemplateKHR",
    /*  724 */ "vkUpdateDescriptorSets",
    /*  725 */ "vkUpdateIndirectExecutionSetPipelineEXT",
    /*  726 */ "vkUpdateIndirectExecutionSetShaderEXT",
    /*  727 */ "vkUpdateVideoSessionParametersKHR",
    /*  728 */ "vkWaitForFences",
    /*  729 */ "vkWaitForPresentKHR",
    /*  730 */ "vkWaitSemaphores",
    /*  731 */ "vkWaitSemaphoresKHR",
    /*  732 */ "vkWriteAccelerationStructuresPropertiesKHR",
    /*  733 */ "vkWriteMicromapsPropertiesEXT"
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
    /*   77 */ 0x50ea79c84acba293, /* VK_EXT_fragment_density_map_offset */
    /*   78 */ 0xec38db4912e9aa39, /* VK_EXT_fragment_shader_interlock */
    /*   79 */ 0x4bed293561f471c5, /* VK_EXT_frame_boundary */
    /*   80 */ 0xf888a39f24346db4, /* VK_EXT_full_screen_exclusive */
    /*   81 */ 0x026fba6d706537f5, /* VK_EXT_global_priority */
    /*   82 */ 0x49240b90779ad742, /* VK_EXT_global_priority_query */
    /*   83 */ 0xe612048b33a20737, /* VK_EXT_graphics_pipeline_library */
    /*   84 */ 0xd140703366300180, /* VK_EXT_hdr_metadata */
    /*   85 */ 0xfc97df8c7f5cb62e, /* VK_EXT_headless_surface */
    /*   86 */ 0x15c6d3b4db750060, /* VK_EXT_host_image_copy */
    /*   87 */ 0xcc9a1964d5f92ead, /* VK_EXT_host_query_reset */
    /*   88 */ 0x992053b93ca7369a, /* VK_EXT_image_2d_view_of_3d */
    /*   89 */ 0xac673544b231a330, /* VK_EXT_image_compression_control */
    /*   90 */ 0xfc267e5b08be3c88, /* VK_EXT_image_compression_control_swapchain */
    /*   91 */ 0x5d78e7153c62776c, /* VK_EXT_image_drm_format_modifier */
    /*   92 */ 0xe918548d9d09bdf5, /* VK_EXT_image_robustness */
    /*   93 */ 0x10ea5ce8b7b462c6, /* VK_EXT_image_sliced_view_of_3d */
    /*   94 */ 0x5d125c6144d30072, /* VK_EXT_image_view_min_lod */
    /*   95 */ 0x66bb737b7652d71d, /* VK_EXT_index_type_uint8 */
    /*   96 */ 0x59f61f1cc23145ee, /* VK_EXT_inline_uniform_block */
    /*   97 */ 0x9ba2edc52691fc07, /* VK_EXT_layer_settings */
    /*   98 */ 0xa45ec0ff789f2882, /* VK_EXT_legacy_dithering */
    /*   99 */ 0x93eebd73e097d983, /* VK_EXT_legacy_vertex_attributes */
    /*  100 */ 0x98daf38a4cd796bc, /* VK_EXT_line_rasterization */
    /*  101 */ 0xca3cb4186d57fa40, /* VK_EXT_load_store_op_none */
    /*  102 */ 0xc92882ba73a7ad8a, /* VK_EXT_map_memory_placed */
    /*  103 */ 0xa642b55c0f467f26, /* VK_EXT_memory_budget */
    /*  104 */ 0xdf03e1a0a38154d2, /* VK_EXT_memory_priority */
    /*  105 */ 0x38a2a90e0a820189, /* VK_EXT_mesh_shader */
    /*  106 */ 0x6bcff1cd8cf418f2, /* VK_EXT_metal_objects */
    /*  107 */ 0x60fc707b7c19679c, /* VK_EXT_metal_surface */
    /*  108 */ 0x60ca462964877ba5, /* VK_EXT_multi_draw */
    /*  109 */ 0x60c608294e99436f, /* VK_EXT_multisampled_render_to_single_sampled */
    /*  110 */ 0x333da01be07c65e4, /* VK_EXT_mutable_descriptor_type */
    /*  111 */ 0x4f43f294a30fc75d, /* VK_EXT_nested_command_buffer */
    /*  112 */ 0x6cf77b70db09b037, /* VK_EXT_non_seamless_cube_map */
    /*  113 */ 0xb5bdb97dc49555ef, /* VK_EXT_opacity_micromap */
    /*  114 */ 0x74062e5990db1eeb, /* VK_EXT_pageable_device_local_memory */
    /*  115 */ 0xe60ea5fa872ffa4b, /* VK_EXT_pci_bus_info */
    /*  116 */ 0x087b96c0fac7f2e9, /* VK_EXT_physical_device_drm */
    /*  117 */ 0xae186881e629f533, /* VK_EXT_pipeline_creation_cache_control */
    /*  118 */ 0xd5ed321620183ae4, /* VK_EXT_pipeline_creation_feedback */
    /*  119 */ 0xf2497807f1195d03, /* VK_EXT_pipeline_library_group_handles */
    /*  120 */ 0x97816799b0ea2a08, /* VK_EXT_pipeline_properties */
    /*  121 */ 0x0bec2c70abec6edf, /* VK_EXT_pipeline_protected_access */
    /*  122 */ 0x3726d3c286b23305, /* VK_EXT_pipeline_robustness */
    /*  123 */ 0x578e2a9cdc320baa, /* VK_EXT_post_depth_coverage */
    /*  124 */ 0xdad3977856dd3ce4, /* VK_EXT_present_mode_fifo_latest_ready */
    /*  125 */ 0x4792bf3539da07a0, /* VK_EXT_primitive_topology_list_restart */
    /*  126 */ 0x4de3fc9eb140d3c9, /* VK_EXT_primitives_generated_query */
    /*  127 */ 0x66832604ff1fb25a, /* VK_EXT_private_data */
    /*  128 */ 0x3632448643e01277, /* VK_EXT_provoking_vertex */
    /*  129 */ 0xc3a80f57bc34acf0, /* VK_EXT_queue_family_foreign */
    /*  130 */ 0x9c47749ad3103e99, /* VK_EXT_rasterization_order_attachment_access */
    /*  131 */ 0xe3b61ff718cac048, /* VK_EXT_rgba10x6_formats */
    /*  132 */ 0x267337703fbb9802, /* VK_EXT_robustness2 */
    /*  133 */ 0xa2f0c46d62bffbbd, /* VK_EXT_sample_locations */
    /*  134 */ 0x35bc8d45855c9ddd, /* VK_EXT_sampler_filter_minmax */
    /*  135 */ 0x0fe7c2504b67f76e, /* VK_EXT_scalar_block_layout */
    /*  136 */ 0x21c315365bdd91c1, /* VK_EXT_separate_stencil_usage */
    /*  137 */ 0x39152af17d406387, /* VK_EXT_shader_atomic_float */
    /*  138 */ 0xfa5bf73b09f1814a, /* VK_EXT_shader_atomic_float2 */
    /*  139 */ 0x1313743aff740ea6, /* VK_EXT_shader_demote_to_helper_invocation */
    /*  140 */ 0xdbd208469e466661, /* VK_EXT_shader_image_atomic_int64 */
    /*  141 */ 0x0fdb11284e798630, /* VK_EXT_shader_module_identifier */
    /*  142 */ 0x01d57626cc2cb88b, /* VK_EXT_shader_object */
    /*  143 */ 0xd98565c5e8cff707, /* VK_EXT_shader_replicated_composites */
    /*  144 */ 0x1d5f02c289908dc6, /* VK_EXT_shader_stencil_export */
    /*  145 */ 0x3434e0e3856c3974, /* VK_EXT_shader_subgroup_ballot */
    /*  146 */ 0x414fe291cad1b8c2, /* VK_EXT_shader_subgroup_vote */
    /*  147 */ 0x15c81e1e3330c87a, /* VK_EXT_shader_tile_image */
    /*  148 */ 0x3ab7ae29a67149aa, /* VK_EXT_shader_viewport_index_layer */
    /*  149 */ 0xf8847bcd6077bcfc, /* VK_EXT_subgroup_size_control */
    /*  150 */ 0xc0a98929a3b5a629, /* VK_EXT_subpass_merge_feedback */
    /*  151 */ 0x745c764090230a6a, /* VK_EXT_surface_maintenance1 */
    /*  152 */ 0xaf7db52f12522284, /* VK_EXT_swapchain_colorspace */
    /*  153 */ 0xb8a530fd9b6e7826, /* VK_EXT_swapchain_maintenance1 */
    /*  154 */ 0x93820a855076e9ba, /* VK_EXT_texel_buffer_alignment */
    /*  155 */ 0xd54a2906947894c3, /* VK_EXT_texture_compression_astc_hdr */
    /*  156 */ 0xa176a37fe21bf722, /* VK_EXT_tooling_info */
    /*  157 */ 0x2c77e64693cba64b, /* VK_EXT_transform_feedback */
    /*  158 */ 0xd43b5b3257938a0c, /* VK_EXT_validation_cache */
    /*  159 */ 0x32e3bcc79655ff35, /* VK_EXT_validation_features */
    /*  160 */ 0x5dbef52d8325ef00, /* VK_EXT_validation_flags */
    /*  161 */ 0x41bd31eed71de48d, /* VK_EXT_vertex_attribute_divisor */
    /*  162 */ 0x384a29f8cf6d87bf, /* VK_EXT_vertex_attribute_robustness */
    /*  163 */ 0xdba593667f2b15d8, /* VK_EXT_vertex_input_dynamic_state */
    /*  164 */ 0xdc68cb4b50c6a206, /* VK_EXT_ycbcr_2plane_444_formats */
    /*  165 */ 0x7f0e4b169ce6683e, /* VK_EXT_ycbcr_image_arrays */
    /*  166 */ 0x1d23436dd19b0471, /* VK_EXT_zero_initialize_device_memory */
    /*  167 */ 0x4ad21727cd459ae0, /* VK_FUCHSIA_buffer_collection */
    /*  168 */ 0x39a61a1dde950a7e, /* VK_FUCHSIA_external_memory */
    /*  169 */ 0xf64c61e8709735f7, /* VK_FUCHSIA_external_semaphore */
    /*  170 */ 0x78bbdf52d016b408, /* VK_FUCHSIA_imagepipe_surface */
    /*  171 */ 0x7f2da9be6e1b04db, /* VK_GGP_frame_token */
    /*  172 */ 0xcd04d110dd619891, /* VK_GGP_stream_descriptor_surface */
    /*  173 */ 0x66d124637ca67c9b, /* VK_GOOGLE_decorate_string */
    /*  174 */ 0xd317975f41d1a234, /* VK_GOOGLE_display_timing */
    /*  175 */ 0x434a8c02c305c9d2, /* VK_GOOGLE_hlsl_functionality1 */
    /*  176 */ 0xdb384c83fb23b324, /* VK_GOOGLE_surfaceless_query */
    /*  177 */ 0x8ea5be2adce92628, /* VK_GOOGLE_user_type */
    /*  178 */ 0x1251619c17f44f75, /* VK_HUAWEI_cluster_culling_shader */
    /*  179 */ 0x734dc9a82ce2a812, /* VK_HUAWEI_hdr_vivid */
    /*  180 */ 0x23cb6d9b631ae3de, /* VK_HUAWEI_invocation_mask */
    /*  181 */ 0x7a080c6eb36cfa62, /* VK_HUAWEI_subpass_shading */
    /*  182 */ 0xc831730562583c7f, /* VK_IMG_filter_cubic */
    /*  183 */ 0x2770027508eb9598, /* VK_IMG_format_pvrtc */
    /*  184 */ 0xb0257135e659f035, /* VK_IMG_relaxed_line_rasterization */
    /*  185 */ 0xde48a4b9c28f1a76, /* VK_INTEL_performance_query */
    /*  186 */ 0x1cdbef97960a8e84, /* VK_INTEL_shader_integer_functions2 */
    /*  187 */ 0x8febc131b31f03a7, /* VK_KHR_16bit_storage */
    /*  188 */ 0xfc675d0c9be11933, /* VK_KHR_8bit_storage */
    /*  189 */ 0xfd487833d05a912e, /* VK_KHR_acceleration_structure */
    /*  190 */ 0x29df4e2582c4e5eb, /* VK_KHR_android_surface */
    /*  191 */ 0xc441ac340c33f00e, /* VK_KHR_bind_memory2 */
    /*  192 */ 0xed3998734610578e, /* VK_KHR_buffer_device_address */
    /*  193 */ 0xf6b15d82867a4cc7, /* VK_KHR_calibrated_timestamps */
    /*  194 */ 0x0afe9b38bfc3ce2c, /* VK_KHR_compute_shader_derivatives */
    /*  195 */ 0x2349bf032cef96df, /* VK_KHR_cooperative_matrix */
    /*  196 */ 0x8037af99654ff021, /* VK_KHR_copy_commands2 */
    /*  197 */ 0x45e78547df004126, /* VK_KHR_create_renderpass2 */
    /*  198 */ 0x78b51eb267ba222a, /* VK_KHR_dedicated_allocation */
    /*  199 */ 0x94de08b35a6241ca, /* VK_KHR_deferred_host_operations */
    /*  200 */ 0xc379ca87fcbfe646, /* VK_KHR_depth_clamp_zero_one */
    /*  201 */ 0x8c49a14f4e053827, /* VK_KHR_depth_stencil_resolve */
    /*  202 */ 0xd0e490f381b744be, /* VK_KHR_descriptor_update_template */
    /*  203 */ 0xc6ca78c5b314bc87, /* VK_KHR_device_group */
    /*  204 */ 0x8585cbd14f1c0cac, /* VK_KHR_device_group_creation */
    /*  205 */ 0x2859d74f3639d0b1, /* VK_KHR_display */
    /*  206 */ 0xe6851c4675917263, /* VK_KHR_display_swapchain */
    /*  207 */ 0x0337556153ae8299, /* VK_KHR_draw_indirect_count */
    /*  208 */ 0x2fa1beee71b55c4a, /* VK_KHR_driver_properties */
    /*  209 */ 0xcec518255e3db5bd, /* VK_KHR_dynamic_rendering */
    /*  210 */ 0x3aff0fddef25484a, /* VK_KHR_dynamic_rendering_local_read */
    /*  211 */ 0x042831872b90006c, /* VK_KHR_external_fence */
    /*  212 */ 0x5f78dae679457682, /* VK_KHR_external_fence_capabilities */
    /*  213 */ 0xcd3a8c2ddf5addf6, /* VK_KHR_external_fence_fd */
    /*  214 */ 0x4c03e948c552a900, /* VK_KHR_external_fence_win32 */
    /*  215 */ 0x87d94faee5024129, /* VK_KHR_external_memory */
    /*  216 */ 0x3f3f36a8f61bdd88, /* VK_KHR_external_memory_capabilities */
    /*  217 */ 0x552d385fc1022139, /* VK_KHR_external_memory_fd */
    /*  218 */ 0x92cd58bc47a696d9, /* VK_KHR_external_memory_win32 */
    /*  219 */ 0x7e7e947a025884c1, /* VK_KHR_external_semaphore */
    /*  220 */ 0xb7268870e382881b, /* VK_KHR_external_semaphore_capabilities */
    /*  221 */ 0x089c9b49df8b6f1e, /* VK_KHR_external_semaphore_fd */
    /*  222 */ 0x014c9621dbd33d31, /* VK_KHR_external_semaphore_win32 */
    /*  223 */ 0x9310a82971542c4a, /* VK_KHR_format_feature_flags2 */
    /*  224 */ 0x2aedf5bc87e7dd6d, /* VK_KHR_fragment_shader_barycentric */
    /*  225 */ 0x8496cee01f4fa6d5, /* VK_KHR_fragment_shading_rate */
    /*  226 */ 0x6c023bc9dc523d46, /* VK_KHR_get_display_properties2 */
    /*  227 */ 0x9eb7bb6c3705f946, /* VK_KHR_get_memory_requirements2 */
    /*  228 */ 0x7685eeed9cac9798, /* VK_KHR_get_physical_device_properties2 */
    /*  229 */ 0x9b0fbb8eeee0e74b, /* VK_KHR_get_surface_capabilities2 */
    /*  230 */ 0x0bb91b137617fbef, /* VK_KHR_global_priority */
    /*  231 */ 0xfb7c493b280e7035, /* VK_KHR_image_format_list */
    /*  232 */ 0x6ba09c8a87af68ce, /* VK_KHR_imageless_framebuffer */
    /*  233 */ 0x76a0d6d17ae91b81, /* VK_KHR_incremental_present */
    /*  234 */ 0x3dde8d8eb0b76315, /* VK_KHR_index_type_uint8 */
    /*  235 */ 0x7928ca2523362ef3, /* VK_KHR_line_rasterization */
    /*  236 */ 0xc8692b97cfbe45ad, /* VK_KHR_load_store_op_none */
    /*  237 */ 0xe3c8335cc1581a67, /* VK_KHR_maintenance1 */
    /*  238 */ 0x8ffe792f51cd1450, /* VK_KHR_maintenance2 */
    /*  239 */ 0xea219cc76502a8af, /* VK_KHR_maintenance3 */
    /*  240 */ 0xa66e463f036dae4a, /* VK_KHR_maintenance4 */
    /*  241 */ 0xc5e86b535cee6698, /* VK_KHR_maintenance5 */
    /*  242 */ 0xf60b7de240a15ab4, /* VK_KHR_maintenance6 */
    /*  243 */ 0x3d59040ce3c13f21, /* VK_KHR_maintenance7 */
    /*  244 */ 0xb6892d36c521b488, /* VK_KHR_maintenance8 */
    /*  245 */ 0x64d252cf56a64add, /* VK_KHR_map_memory2 */
    /*  246 */ 0x5af12378bc6d7169, /* VK_KHR_multiview */
    /*  247 */ 0x1bb74dfe8d7e0b31, /* VK_KHR_performance_query */
    /*  248 */ 0x935d834a6c18d3ed, /* VK_KHR_pipeline_binary */
    /*  249 */ 0x91248c6b162c4180, /* VK_KHR_pipeline_executable_properties */
    /*  250 */ 0x039c65d87fb09ca9, /* VK_KHR_pipeline_library */
    /*  251 */ 0x28644eeb112058b6, /* VK_KHR_portability_enumeration */
    /*  252 */ 0xac06576b97f9486a, /* VK_KHR_portability_subset */
    /*  253 */ 0xe82e301141092b1e, /* VK_KHR_present_id */
    /*  254 */ 0x47954f24ddf5185e, /* VK_KHR_present_wait */
    /*  255 */ 0x2123bacd888c07ec, /* VK_KHR_push_descriptor */
    /*  256 */ 0x8bf873804879f2cf, /* VK_KHR_ray_query */
    /*  257 */ 0x9df3df162357e4b0, /* VK_KHR_ray_tracing_maintenance1 */
    /*  258 */ 0xaef707cb154a81af, /* VK_KHR_ray_tracing_pipeline */
    /*  259 */ 0x697f77ef7ba14203, /* VK_KHR_ray_tracing_position_fetch */
    /*  260 */ 0x4b17e19fd947a1d3, /* VK_KHR_relaxed_block_layout */
    /*  261 */ 0xaab0786abb72567a, /* VK_KHR_robustness2 */
    /*  262 */ 0x5d5e936103817cda, /* VK_KHR_sampler_mirror_clamp_to_edge */
    /*  263 */ 0x22004cfa79ba7177, /* VK_KHR_sampler_ycbcr_conversion */
    /*  264 */ 0xba2c0ae86fd11630, /* VK_KHR_separate_depth_stencil_layouts */
    /*  265 */ 0xb16f5fd69d97f3a1, /* VK_KHR_shader_atomic_int64 */
    /*  266 */ 0xd49205e9c445114a, /* VK_KHR_shader_bfloat16 */
    /*  267 */ 0xeee9708671fa7c77, /* VK_KHR_shader_clock */
    /*  268 */ 0xb35fc4bdb32f3d81, /* VK_KHR_shader_draw_parameters */
    /*  269 */ 0xab0eda6676f1fd31, /* VK_KHR_shader_expect_assume */
    /*  270 */ 0x4dad563cb513c7c9, /* VK_KHR_shader_float16_int8 */
    /*  271 */ 0x548b20a76c855b46, /* VK_KHR_shader_float_controls */
    /*  272 */ 0xa1150eef92f851e8, /* VK_KHR_shader_float_controls2 */
    /*  273 */ 0x9d14cd5379daf7cb, /* VK_KHR_shader_integer_dot_product */
    /*  274 */ 0x42aefa5598fde4ab, /* VK_KHR_shader_maximal_reconvergence */
    /*  275 */ 0xb38332d7467f8474, /* VK_KHR_shader_non_semantic_info */
    /*  276 */ 0xab3f0af6d5504bf4, /* VK_KHR_shader_quad_control */
    /*  277 */ 0x1bdfe042874be24f, /* VK_KHR_shader_relaxed_extended_instruction */
    /*  278 */ 0xcda588b0d067d48f, /* VK_KHR_shader_subgroup_extended_types */
    /*  279 */ 0xd0836c7a4d04b579, /* VK_KHR_shader_subgroup_rotate */
    /*  280 */ 0x64fbf5bc74afe199, /* VK_KHR_shader_subgroup_uniform_control_flow */
    /*  281 */ 0x6e5fde40560b40a9, /* VK_KHR_shader_terminate_invocation */
    /*  282 */ 0x7e6871b03dee137b, /* VK_KHR_shared_presentable_image */
    /*  283 */ 0x06c03c1c3db9815d, /* VK_KHR_spirv_1_4 */
    /*  284 */ 0x743f86c26df32ea2, /* VK_KHR_storage_buffer_storage_class */
    /*  285 */ 0x2c4f009293a35548, /* VK_KHR_surface */
    /*  286 */ 0xa8506d9aef558591, /* VK_KHR_surface_protected_capabilities */
    /*  287 */ 0x6cefabf4c944ccec, /* VK_KHR_swapchain */
    /*  288 */ 0x2149e839e759e400, /* VK_KHR_swapchain_mutable_format */
    /*  289 */ 0xf1cfa2ea69e6ec0e, /* VK_KHR_synchronization2 */
    /*  290 */ 0x61ed378f50459bf2, /* VK_KHR_timeline_semaphore */
    /*  291 */ 0x3334ed809879d360, /* VK_KHR_uniform_buffer_standard_layout */
    /*  292 */ 0x6146df22dcb09470, /* VK_KHR_variable_pointers */
    /*  293 */ 0xcfd1e6704e4a4227, /* VK_KHR_vertex_attribute_divisor */
    /*  294 */ 0x4ccc16568a9a2944, /* VK_KHR_video_decode_av1 */
    /*  295 */ 0x0093b60d00888052, /* VK_KHR_video_decode_h264 */
    /*  296 */ 0x4116f6bec0017e79, /* VK_KHR_video_decode_h265 */
    /*  297 */ 0x363dac5e35a2f1ee, /* VK_KHR_video_decode_queue */
    /*  298 */ 0x35e683e888a7a54c, /* VK_KHR_video_encode_av1 */
    /*  299 */ 0xa77247c5899dc785, /* VK_KHR_video_encode_h264 */
    /*  300 */ 0x8b86366e33c748ee, /* VK_KHR_video_encode_h265 */
    /*  301 */ 0x3f1a8c895b8e8deb, /* VK_KHR_video_encode_quantization_map */
    /*  302 */ 0xdda14264a3bda234, /* VK_KHR_video_encode_queue */
    /*  303 */ 0x9fb8181989e29256, /* VK_KHR_video_maintenance1 */
    /*  304 */ 0xfd1949eb2a3c752b, /* VK_KHR_video_maintenance2 */
    /*  305 */ 0xc3d1c9b40515a6a4, /* VK_KHR_video_queue */
    /*  306 */ 0x34899ec7a7b17614, /* VK_KHR_vulkan_memory_model */
    /*  307 */ 0x906fcab3e0d202a5, /* VK_KHR_wayland_surface */
    /*  308 */ 0x19d48609837c8701, /* VK_KHR_win32_keyed_mutex */
    /*  309 */ 0xc93557e7cef43233, /* VK_KHR_win32_surface */
    /*  310 */ 0x75ee32f09cdd8db9, /* VK_KHR_workgroup_memory_explicit_layout */
    /*  311 */ 0x32a481baaa637e2c, /* VK_KHR_xcb_surface */
    /*  312 */ 0x863c0e309551346e, /* VK_KHR_xlib_surface */
    /*  313 */ 0x58d24a21f116065b, /* VK_KHR_zero_initialize_workgroup_memory */
    /*  314 */ 0x5615881540a7f6d8, /* VK_LUNARG_direct_driver_loading */
    /*  315 */ 0x6f8fb9c8b46fc189, /* VK_MESA_image_alignment_control */
    /*  316 */ 0xc1c930637836bf44, /* VK_MSFT_layered_driver */
    /*  317 */ 0x489cf2a16640d39e, /* VK_MVK_ios_surface */
    /*  318 */ 0x3274c65edf45286c, /* VK_MVK_macos_surface */
    /*  319 */ 0x53643314731ac57a, /* VK_NN_vi_surface */
    /*  320 */ 0x5bf53745255ccc0e, /* VK_NVX_binary_import */
    /*  321 */ 0x20b59934a97efd1c, /* VK_NVX_image_view_handle */
    /*  322 */ 0x112ee8733e2b22b3, /* VK_NVX_multiview_per_view_attributes */
    /*  323 */ 0x71fe862eee072b1e, /* VK_NV_acquire_winrt_display */
    /*  324 */ 0x9217a69de789d3fe, /* VK_NV_clip_space_w_scaling */
    /*  325 */ 0x5d2cfdaf5ecc308b, /* VK_NV_cluster_acceleration_structure */
    /*  326 */ 0xad1ba91484f69ca3, /* VK_NV_command_buffer_inheritance */
    /*  327 */ 0x21d19e30b520bdd6, /* VK_NV_compute_shader_derivatives */
    /*  328 */ 0x069e842b3b51cefb, /* VK_NV_cooperative_matrix */
    /*  329 */ 0xfecfd80519026209, /* VK_NV_cooperative_matrix2 */
    /*  330 */ 0x9b6d5b7725490586, /* VK_NV_cooperative_vector */
    /*  331 */ 0xce889f8d6b40e84f, /* VK_NV_copy_memory_indirect */
    /*  332 */ 0xed85b1ac0329a8cd, /* VK_NV_corner_sampled_image */
    /*  333 */ 0x81b617790445f852, /* VK_NV_coverage_reduction_mode */
    /*  334 */ 0x3644690c3bd14289, /* VK_NV_cuda_kernel_launch */
    /*  335 */ 0xbb81f8243fcc7db5, /* VK_NV_dedicated_allocation */
    /*  336 */ 0x00ce18bba106c2ad, /* VK_NV_dedicated_allocation_image_aliasing */
    /*  337 */ 0x23bcacd889bea60c, /* VK_NV_descriptor_pool_overallocation */
    /*  338 */ 0xf03dfd81ad17796f, /* VK_NV_device_diagnostic_checkpoints */
    /*  339 */ 0xc8050fbd31afc5b5, /* VK_NV_device_diagnostics_config */
    /*  340 */ 0xee7bfcd5523cff09, /* VK_NV_device_generated_commands */
    /*  341 */ 0x2ff0ded4f3f040e9, /* VK_NV_device_generated_commands_compute */
    /*  342 */ 0xc07b5e2a89ddc607, /* VK_NV_displacement_micromap */
    /*  343 */ 0x5138c2f68bcb3608, /* VK_NV_display_stereo */
    /*  344 */ 0xb2344e462fd9ef1b, /* VK_NV_extended_sparse_address_space */
    /*  345 */ 0xd15b433c649fb093, /* VK_NV_external_compute_queue */
    /*  346 */ 0xab0f59a00375b1ec, /* VK_NV_external_memory */
    /*  347 */ 0x518148eb9166b4b9, /* VK_NV_external_memory_capabilities */
    /*  348 */ 0x3c96386b301a3cdc, /* VK_NV_external_memory_rdma */
    /*  349 */ 0xcf69c3e7cbd068e4, /* VK_NV_external_memory_win32 */
    /*  350 */ 0xdf9a65a432a12606, /* VK_NV_fill_rectangle */
    /*  351 */ 0x9a6fda1e2f4f9096, /* VK_NV_fragment_coverage_to_color */
    /*  352 */ 0xc294d55a56858fb6, /* VK_NV_fragment_shader_barycentric */
    /*  353 */ 0x2ece12f465807058, /* VK_NV_fragment_shading_rate_enums */
    /*  354 */ 0x4caba51b111c61b9, /* VK_NV_framebuffer_mixed_samples */
    /*  355 */ 0xe0c4918343f3874c, /* VK_NV_geometry_shader_passthrough */
    /*  356 */ 0xd659873b3f6bc024, /* VK_NV_glsl_shader */
    /*  357 */ 0xe39346d87fc9aa45, /* VK_NV_inherited_viewport_scissor */
    /*  358 */ 0x52fcc4c2d713dad4, /* VK_NV_linear_color_attachment */
    /*  359 */ 0xb58daf9c015becf7, /* VK_NV_low_latency */
    /*  360 */ 0xa9eb852dfd7a1ece, /* VK_NV_low_latency2 */
    /*  361 */ 0x6c878fdbf1e4a7fb, /* VK_NV_memory_decompression */
    /*  362 */ 0x7401a89f84bc926b, /* VK_NV_mesh_shader */
    /*  363 */ 0x929112526891454e, /* VK_NV_optical_flow */
    /*  364 */ 0x6e9d1f60324c4761, /* VK_NV_partitioned_acceleration_structure */
    /*  365 */ 0x5e0416a20f89c9f4, /* VK_NV_per_stage_descriptor_set */
    /*  366 */ 0x48102b2d563a8028, /* VK_NV_present_barrier */
    /*  367 */ 0xe16f6927a8473cab, /* VK_NV_present_metering */
    /*  368 */ 0xc20950e0cbc5bdc0, /* VK_NV_raw_access_chains */
    /*  369 */ 0x3d4e9e0bb54735fe, /* VK_NV_ray_tracing */
    /*  370 */ 0xe12f14699c6db9db, /* VK_NV_ray_tracing_invocation_reorder */
    /*  371 */ 0x4157611d54ac1bc1, /* VK_NV_ray_tracing_linear_swept_spheres */
    /*  372 */ 0xba4184e5104338cb, /* VK_NV_ray_tracing_motion_blur */
    /*  373 */ 0x451532c42bd881b2, /* VK_NV_ray_tracing_validation */
    /*  374 */ 0x92ccabdfa0a3d6e4, /* VK_NV_representative_fragment_test */
    /*  375 */ 0xc4d99252b7b7843f, /* VK_NV_sample_mask_override_coverage */
    /*  376 */ 0xd4d2cda699fc74ae, /* VK_NV_scissor_exclusive */
    /*  377 */ 0xb8974b1af4c34b58, /* VK_NV_shader_atomic_float16_vector */
    /*  378 */ 0x52f9f98f09f18085, /* VK_NV_shader_image_footprint */
    /*  379 */ 0xc394473a75e21d7c, /* VK_NV_shader_sm_builtins */
    /*  380 */ 0x5b6c5e76d8a8364e, /* VK_NV_shader_subgroup_partitioned */
    /*  381 */ 0xcac204d487e563d3, /* VK_NV_shading_rate_image */
    /*  382 */ 0xfc6e35d06ddf634e, /* VK_NV_viewport_array2 */
    /*  383 */ 0x7748ea26eecd7e90, /* VK_NV_viewport_swizzle */
    /*  384 */ 0x7e4ac6b10102b887, /* VK_NV_win32_keyed_mutex */
    /*  385 */ 0x5c76ad884426c86c, /* VK_QCOM_filter_cubic_clamp */
    /*  386 */ 0xc7386bbfd1b9b423, /* VK_QCOM_filter_cubic_weights */
    /*  387 */ 0xff445069da66b635, /* VK_QCOM_fragment_density_map_offset */
    /*  388 */ 0xa6cab4106375cdfa, /* VK_QCOM_image_processing */
    /*  389 */ 0xa4a1ae34c2527a4a, /* VK_QCOM_image_processing2 */
    /*  390 */ 0xbff750af2234e2ce, /* VK_QCOM_multiview_per_view_render_areas */
    /*  391 */ 0x876a51c6df08420a, /* VK_QCOM_multiview_per_view_viewports */
    /*  392 */ 0xa3b4fc40f185c799, /* VK_QCOM_render_pass_shader_resolve */
    /*  393 */ 0x9b5c2a0bc41e00cd, /* VK_QCOM_render_pass_store_ops */
    /*  394 */ 0x8d33cd618c723019, /* VK_QCOM_render_pass_transform */
    /*  395 */ 0xd5a3f971e2e8b5c9, /* VK_QCOM_rotated_copy_commands */
    /*  396 */ 0x73244ac23f3ec04a, /* VK_QCOM_tile_memory_heap */
    /*  397 */ 0xc37b456dbdf5565f, /* VK_QCOM_tile_properties */
    /*  398 */ 0x80b039482dfe4631, /* VK_QCOM_tile_shading */
    /*  399 */ 0x49bfbd9f92e0b029, /* VK_QCOM_ycbcr_degamma */
    /*  400 */ 0xc2e6f6dcc7614ace, /* VK_QNX_external_memory_screen_buffer */
    /*  401 */ 0x236bd86b3b17cf06, /* VK_QNX_screen_surface */
    /*  402 */ 0xe6fed416ddebf8d0, /* VK_SEC_amigo_profiling */
    /*  403 */ 0x45542cac22bd41a7, /* VK_VALVE_descriptor_set_host_mapping */
    /*  404 */ 0x38c73d4ab66a4942  /* VK_VALVE_mutable_descriptor_type */
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
          27, /* vkCmdBeginQuery */
          29, /* vkCmdBeginRenderPass */
          39, /* vkCmdBindDescriptorSets */
          42, /* vkCmdBindIndexBuffer */
          46, /* vkCmdBindPipeline */
          52, /* vkCmdBindVertexBuffers */
          55, /* vkCmdBlitImage */
          64, /* vkCmdClearAttachments */
          65, /* vkCmdClearColorImage */
          66, /* vkCmdClearDepthStencilImage */
          72, /* vkCmdCopyBuffer */
          75, /* vkCmdCopyBufferToImage */
          78, /* vkCmdCopyImage */
          81, /* vkCmdCopyImageToBuffer */
          90, /* vkCmdCopyQueryPoolResults */
          99, /* vkCmdDispatch */
         105, /* vkCmdDispatchIndirect */
         107, /* vkCmdDraw */
         110, /* vkCmdDrawIndexed */
         111, /* vkCmdDrawIndexedIndirect */
         115, /* vkCmdDrawIndirect */
         132, /* vkCmdEndQuery */
         134, /* vkCmdEndRenderPass */
         142, /* vkCmdExecuteCommands */
         145, /* vkCmdFillBuffer */
         148, /* vkCmdNextSubpass */
         152, /* vkCmdPipelineBarrier */
         157, /* vkCmdPushConstants */
         168, /* vkCmdResetEvent */
         171, /* vkCmdResetQueryPool */
         172, /* vkCmdResolveImage */
         178, /* vkCmdSetBlendConstants */
         195, /* vkCmdSetDepthBias */
         199, /* vkCmdSetDepthBounds */
         219, /* vkCmdSetEvent */
         234, /* vkCmdSetLineWidth */
         260, /* vkCmdSetScissor */
         264, /* vkCmdSetStencilCompareMask */
         267, /* vkCmdSetStencilReference */
         270, /* vkCmdSetStencilWriteMask */
         273, /* vkCmdSetViewport */
         285, /* vkCmdUpdateBuffer */
         287, /* vkCmdWaitEvents */
         295, /* vkCmdWriteTimestamp */
         315, /* vkCreateBuffer */
         317, /* vkCreateBufferView */
         318, /* vkCreateCommandPool */
         319, /* vkCreateComputePipelines */
         327, /* vkCreateDescriptorPool */
         328, /* vkCreateDescriptorSetLayout */
         331, /* vkCreateDevice */
         335, /* vkCreateEvent */
         338, /* vkCreateFence */
         339, /* vkCreateFramebuffer */
         340, /* vkCreateGraphicsPipelines */
         343, /* vkCreateImage */
         345, /* vkCreateImageView */
         349, /* vkCreateInstance */
         355, /* vkCreatePipelineCache */
         356, /* vkCreatePipelineLayout */
         359, /* vkCreateQueryPool */
         362, /* vkCreateRenderPass */
         365, /* vkCreateSampler */
         369, /* vkCreateSemaphore */
         370, /* vkCreateShaderModule */
         389, /* vkDestroyBuffer */
         391, /* vkDestroyBufferView */
         392, /* vkDestroyCommandPool */
         400, /* vkDestroyDescriptorPool */
         401, /* vkDestroyDescriptorSetLayout */
         404, /* vkDestroyDevice */
         405, /* vkDestroyEvent */
         407, /* vkDestroyFence */
         408, /* vkDestroyFramebuffer */
         409, /* vkDestroyImage */
         410, /* vkDestroyImageView */
         414, /* vkDestroyInstance */
         417, /* vkDestroyPipeline */
         419, /* vkDestroyPipelineCache */
         420, /* vkDestroyPipelineLayout */
         423, /* vkDestroyQueryPool */
         424, /* vkDestroyRenderPass */
         425, /* vkDestroySampler */
         428, /* vkDestroySemaphore */
         430, /* vkDestroyShaderModule */
         436, /* vkDeviceWaitIdle */
         438, /* vkEndCommandBuffer */
         439, /* vkEnumerateDeviceExtensionProperties */
         440, /* vkEnumerateDeviceLayerProperties */
         441, /* vkEnumerateInstanceExtensionProperties */
         442, /* vkEnumerateInstanceLayerProperties */
         447, /* vkEnumeratePhysicalDevices */
         449, /* vkFlushMappedMemoryRanges */
         450, /* vkFreeCommandBuffers */
         451, /* vkFreeDescriptorSets */
         452, /* vkFreeMemory */
         463, /* vkGetBufferMemoryRequirements */
         497, /* vkGetDeviceMemoryCommitment */
         501, /* vkGetDeviceProcAddr */
         502, /* vkGetDeviceQueue */
         513, /* vkGetEventStatus */
         518, /* vkGetFenceStatus */
         524, /* vkGetImageMemoryRequirements */
         528, /* vkGetImageSparseMemoryRequirements */
         531, /* vkGetImageSubresourceLayout */
         539, /* vkGetInstanceProcAddr */
         575, /* vkGetPhysicalDeviceFeatures */
         578, /* vkGetPhysicalDeviceFormatProperties */
         582, /* vkGetPhysicalDeviceImageFormatProperties */
         585, /* vkGetPhysicalDeviceMemoryProperties */
         591, /* vkGetPhysicalDeviceProperties */
         595, /* vkGetPhysicalDeviceQueueFamilyProperties */
         599, /* vkGetPhysicalDeviceSparseImageFormatProperties */
         621, /* vkGetPipelineCacheData */
         631, /* vkGetQueryPoolResults */
         640, /* vkGetRenderAreaGranularity */
         666, /* vkInvalidateMappedMemoryRanges */
         668, /* vkMapMemory */
         671, /* vkMergePipelineCaches */
         674, /* vkQueueBindSparse */
         680, /* vkQueueSubmit */
         683, /* vkQueueWaitIdle */
         692, /* vkResetCommandBuffer */
         693, /* vkResetCommandPool */
         694, /* vkResetDescriptorPool */
         695, /* vkResetEvent */
         696, /* vkResetFences */
         704, /* vkSetEvent */
         719, /* vkUnmapMemory */
         724, /* vkUpdateDescriptorSets */
         728  /* vkWaitForFences */
    };
    if (!context->VERSION_1_0) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_VERSION_1_1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          15, /* vkBindBufferMemory2 */
          18, /* vkBindImageMemory2 */
         100, /* vkCmdDispatchBase */
         214, /* vkCmdSetDeviceMask */
         329, /* vkCreateDescriptorUpdateTemplate */
         366, /* vkCreateSamplerYcbcrConversion */
         402, /* vkDestroyDescriptorUpdateTemplate */
         426, /* vkDestroySamplerYcbcrConversion */
         443, /* vkEnumerateInstanceVersion */
         444, /* vkEnumeratePhysicalDeviceGroups */
         464, /* vkGetBufferMemoryRequirements2 */
         480, /* vkGetDescriptorSetLayoutSupport */
         486, /* vkGetDeviceGroupPeerMemoryFeatures */
         503, /* vkGetDeviceQueue2 */
         525, /* vkGetImageMemoryRequirements2 */
         529, /* vkGetImageSparseMemoryRequirements2 */
         568, /* vkGetPhysicalDeviceExternalBufferProperties */
         570, /* vkGetPhysicalDeviceExternalFenceProperties */
         573, /* vkGetPhysicalDeviceExternalSemaphoreProperties */
         576, /* vkGetPhysicalDeviceFeatures2 */
         579, /* vkGetPhysicalDeviceFormatProperties2 */
         583, /* vkGetPhysicalDeviceImageFormatProperties2 */
         586, /* vkGetPhysicalDeviceMemoryProperties2 */
         592, /* vkGetPhysicalDeviceProperties2 */
         596, /* vkGetPhysicalDeviceQueueFamilyProperties2 */
         600, /* vkGetPhysicalDeviceSparseImageFormatProperties2 */
         716, /* vkTrimCommandPool */
         722  /* vkUpdateDescriptorSetWithTemplate */
    };
    if (!context->VERSION_1_1) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_VERSION_1_2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          30, /* vkCmdBeginRenderPass2 */
         112, /* vkCmdDrawIndexedIndirectCount */
         117, /* vkCmdDrawIndirectCount */
         135, /* vkCmdEndRenderPass2 */
         149, /* vkCmdNextSubpass2 */
         363, /* vkCreateRenderPass2 */
         460, /* vkGetBufferDeviceAddress */
         466, /* vkGetBufferOpaqueCaptureAddress */
         498, /* vkGetDeviceMemoryOpaqueCaptureAddress */
         645, /* vkGetSemaphoreCounterValue */
         697, /* vkResetQueryPool */
         711, /* vkSignalSemaphore */
         730  /* vkWaitSemaphores */
    };
    if (!context->VERSION_1_2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_VERSION_1_3(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          32, /* vkCmdBeginRendering */
          53, /* vkCmdBindVertexBuffers2 */
          56, /* vkCmdBlitImage2 */
          73, /* vkCmdCopyBuffer2 */
          76, /* vkCmdCopyBufferToImage2 */
          79, /* vkCmdCopyImage2 */
          82, /* vkCmdCopyImageToBuffer2 */
         137, /* vkCmdEndRendering */
         153, /* vkCmdPipelineBarrier2 */
         169, /* vkCmdResetEvent2 */
         173, /* vkCmdResolveImage2 */
         193, /* vkCmdSetCullMode */
         197, /* vkCmdSetDepthBiasEnable */
         200, /* vkCmdSetDepthBoundsTestEnable */
         206, /* vkCmdSetDepthCompareOp */
         208, /* vkCmdSetDepthTestEnable */
         210, /* vkCmdSetDepthWriteEnable */
         220, /* vkCmdSetEvent2 */
         227, /* vkCmdSetFrontFace */
         242, /* vkCmdSetPrimitiveRestartEnable */
         244, /* vkCmdSetPrimitiveTopology */
         249, /* vkCmdSetRasterizerDiscardEnable */
         261, /* vkCmdSetScissorWithCount */
         265, /* vkCmdSetStencilOp */
         268, /* vkCmdSetStencilTestEnable */
         278, /* vkCmdSetViewportWithCount */
         288, /* vkCmdWaitEvents2 */
         296, /* vkCmdWriteTimestamp2 */
         357, /* vkCreatePrivateDataSlot */
         421, /* vkDestroyPrivateDataSlot */
         483, /* vkGetDeviceBufferMemoryRequirements */
         491, /* vkGetDeviceImageMemoryRequirements */
         493, /* vkGetDeviceImageSparseMemoryRequirements */
         611, /* vkGetPhysicalDeviceToolProperties */
         629, /* vkGetPrivateData */
         681, /* vkQueueSubmit2 */
         709  /* vkSetPrivateData */
    };
    if (!context->VERSION_1_3) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_VERSION_1_4(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          40, /* vkCmdBindDescriptorSets2 */
          43, /* vkCmdBindIndexBuffer2 */
         158, /* vkCmdPushConstants2 */
         160, /* vkCmdPushDescriptorSet */
         161, /* vkCmdPushDescriptorSet2 */
         164, /* vkCmdPushDescriptorSetWithTemplate */
         165, /* vkCmdPushDescriptorSetWithTemplate2 */
         230, /* vkCmdSetLineStipple */
         252, /* vkCmdSetRenderingAttachmentLocations */
         254, /* vkCmdSetRenderingInputAttachmentIndices */
         302, /* vkCopyImageToImage */
         304, /* vkCopyImageToMemory */
         307, /* vkCopyMemoryToImage */
         495, /* vkGetDeviceImageSubresourceLayout */
         532, /* vkGetImageSubresourceLayout2 */
         641, /* vkGetRenderingAreaGranularity */
         669, /* vkMapMemory2 */
         714, /* vkTransitionImageLayout */
         720  /* vkUnmapMemory2 */
    };
    if (!context->VERSION_1_4) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_ENABLE_BETA_EXTENSIONS)
static void glad_vk_load_VK_AMDX_shader_enqueue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         102, /* vkCmdDispatchGraphAMDX */
         103, /* vkCmdDispatchGraphIndirectAMDX */
         104, /* vkCmdDispatchGraphIndirectCountAMDX */
         146, /* vkCmdInitializeGraphScratchMemoryAMDX */
         336, /* vkCreateExecutionGraphPipelinesAMDX */
         514, /* vkGetExecutionGraphPipelineNodeIndexAMDX */
         515  /* vkGetExecutionGraphPipelineScratchSizeAMDX */
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
         292, /* vkCmdWriteBufferMarker2AMD */
         293  /* vkCmdWriteBufferMarkerAMD */
    };
    if (!context->AMD_buffer_marker) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_AMD_display_native_hdr(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         708  /* vkSetLocalDimmingAMD */
    };
    if (!context->AMD_display_native_hdr) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_AMD_draw_indirect_count(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         113, /* vkCmdDrawIndexedIndirectCountAMD */
         118  /* vkCmdDrawIndirectCountAMD */
    };
    if (!context->AMD_draw_indirect_count) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_AMD_shader_info(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         651  /* vkGetShaderInfoAMD */
    };
    if (!context->AMD_shader_info) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
static void glad_vk_load_VK_ANDROID_external_memory_android_hardware_buffer(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         458, /* vkGetAndroidHardwareBufferPropertiesANDROID */
         541  /* vkGetMemoryAndroidHardwareBufferANDROID */
    };
    if (!context->ANDROID_external_memory_android_hardware_buffer) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_acquire_drm_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           0, /* vkAcquireDrmDisplayEXT */
         510  /* vkGetDrmDisplayEXT */
    };
    if (!context->EXT_acquire_drm_display) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
static void glad_vk_load_VK_EXT_acquire_xlib_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           7, /* vkAcquireXlibDisplayEXT */
         634  /* vkGetRandROutputDisplayEXT */
    };
    if (!context->EXT_acquire_xlib_display) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_attachment_feedback_loop_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         177  /* vkCmdSetAttachmentFeedbackLoopEnableEXT */
    };
    if (!context->EXT_attachment_feedback_loop_dynamic_state) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_buffer_device_address(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         461  /* vkGetBufferDeviceAddressEXT */
    };
    if (!context->EXT_buffer_device_address) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_calibrated_timestamps(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         469, /* vkGetCalibratedTimestampsEXT */
         557  /* vkGetPhysicalDeviceCalibrateableTimeDomainsEXT */
    };
    if (!context->EXT_calibrated_timestamps) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_color_write_enable(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         184  /* vkCmdSetColorWriteEnableEXT */
    };
    if (!context->EXT_color_write_enable) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_conditional_rendering(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          24, /* vkCmdBeginConditionalRenderingEXT */
         129  /* vkCmdEndConditionalRenderingEXT */
    };
    if (!context->EXT_conditional_rendering) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_debug_marker(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          93, /* vkCmdDebugMarkerBeginEXT */
          94, /* vkCmdDebugMarkerEndEXT */
          95, /* vkCmdDebugMarkerInsertEXT */
         383, /* vkDebugMarkerSetObjectNameEXT */
         384  /* vkDebugMarkerSetObjectTagEXT */
    };
    if (!context->EXT_debug_marker) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_debug_report(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         324, /* vkCreateDebugReportCallbackEXT */
         385, /* vkDebugReportMessageEXT */
         397  /* vkDestroyDebugReportCallbackEXT */
    };
    if (!context->EXT_debug_report) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_debug_utils(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          25, /* vkCmdBeginDebugUtilsLabelEXT */
         130, /* vkCmdEndDebugUtilsLabelEXT */
         147, /* vkCmdInsertDebugUtilsLabelEXT */
         325, /* vkCreateDebugUtilsMessengerEXT */
         398, /* vkDestroyDebugUtilsMessengerEXT */
         673, /* vkQueueBeginDebugUtilsLabelEXT */
         675, /* vkQueueEndDebugUtilsLabelEXT */
         676, /* vkQueueInsertDebugUtilsLabelEXT */
         701, /* vkSetDebugUtilsObjectNameEXT */
         702, /* vkSetDebugUtilsObjectTagEXT */
         713  /* vkSubmitDebugUtilsMessageEXT */
    };
    if (!context->EXT_debug_utils) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_depth_bias_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         196  /* vkCmdSetDepthBias2EXT */
    };
    if (!context->EXT_depth_bias_control) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_depth_clamp_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         203  /* vkCmdSetDepthClampRangeEXT */
    };
    if (!context->EXT_depth_clamp_control) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_descriptor_buffer(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          37, /* vkCmdBindDescriptorBufferEmbeddedSamplersEXT */
          38, /* vkCmdBindDescriptorBuffersEXT */
         213, /* vkCmdSetDescriptorBufferOffsetsEXT */
         457, /* vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT */
         468, /* vkGetBufferOpaqueCaptureDescriptorDataEXT */
         475, /* vkGetDescriptorEXT */
         477, /* vkGetDescriptorSetLayoutBindingOffsetEXT */
         479, /* vkGetDescriptorSetLayoutSizeEXT */
         527, /* vkGetImageOpaqueCaptureDescriptorDataEXT */
         538, /* vkGetImageViewOpaqueCaptureDescriptorDataEXT */
         643  /* vkGetSamplerOpaqueCaptureDescriptorDataEXT */
    };
    if (!context->EXT_descriptor_buffer) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_device_fault(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         485  /* vkGetDeviceFaultInfoEXT */
    };
    if (!context->EXT_device_fault) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_device_generated_commands(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         143, /* vkCmdExecuteGeneratedCommandsEXT */
         155, /* vkCmdPreprocessGeneratedCommandsEXT */
         346, /* vkCreateIndirectCommandsLayoutEXT */
         348, /* vkCreateIndirectExecutionSetEXT */
         411, /* vkDestroyIndirectCommandsLayoutEXT */
         413, /* vkDestroyIndirectExecutionSetEXT */
         521, /* vkGetGeneratedCommandsMemoryRequirementsEXT */
         725, /* vkUpdateIndirectExecutionSetPipelineEXT */
         726  /* vkUpdateIndirectExecutionSetShaderEXT */
    };
    if (!context->EXT_device_generated_commands) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_direct_mode_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         687  /* vkReleaseDisplayEXT */
    };
    if (!context->EXT_direct_mode_display) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
static void glad_vk_load_VK_EXT_directfb_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         332, /* vkCreateDirectFBSurfaceEXT */
         563  /* vkGetPhysicalDeviceDirectFBPresentationSupportEXT */
    };
    if (!context->EXT_directfb_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_discard_rectangles(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         216, /* vkCmdSetDiscardRectangleEXT */
         217, /* vkCmdSetDiscardRectangleEnableEXT */
         218  /* vkCmdSetDiscardRectangleModeEXT */
    };
    if (!context->EXT_discard_rectangles) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_display_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         437, /* vkDisplayPowerControlEXT */
         654, /* vkGetSwapchainCounterEXT */
         684, /* vkRegisterDeviceEventEXT */
         685  /* vkRegisterDisplayEventEXT */
    };
    if (!context->EXT_display_control) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_display_surface_counter(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         603  /* vkGetPhysicalDeviceSurfaceCapabilities2EXT */
    };
    if (!context->EXT_display_surface_counter) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_extended_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          54, /* vkCmdBindVertexBuffers2EXT */
         194, /* vkCmdSetCullModeEXT */
         201, /* vkCmdSetDepthBoundsTestEnableEXT */
         207, /* vkCmdSetDepthCompareOpEXT */
         209, /* vkCmdSetDepthTestEnableEXT */
         211, /* vkCmdSetDepthWriteEnableEXT */
         228, /* vkCmdSetFrontFaceEXT */
         245, /* vkCmdSetPrimitiveTopologyEXT */
         262, /* vkCmdSetScissorWithCountEXT */
         266, /* vkCmdSetStencilOpEXT */
         269, /* vkCmdSetStencilTestEnableEXT */
         279  /* vkCmdSetViewportWithCountEXT */
    };
    if (!context->EXT_extended_dynamic_state) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_extended_dynamic_state2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         198, /* vkCmdSetDepthBiasEnableEXT */
         235, /* vkCmdSetLogicOpEXT */
         237, /* vkCmdSetPatchControlPointsEXT */
         243, /* vkCmdSetPrimitiveRestartEnableEXT */
         250  /* vkCmdSetRasterizerDiscardEnableEXT */
    };
    if (!context->EXT_extended_dynamic_state2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_extended_dynamic_state3(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         175, /* vkCmdSetAlphaToCoverageEnableEXT */
         176, /* vkCmdSetAlphaToOneEnableEXT */
         181, /* vkCmdSetColorBlendAdvancedEXT */
         182, /* vkCmdSetColorBlendEnableEXT */
         183, /* vkCmdSetColorBlendEquationEXT */
         185, /* vkCmdSetColorWriteMaskEXT */
         186, /* vkCmdSetConservativeRasterizationModeEXT */
         187, /* vkCmdSetCoverageModulationModeNV */
         188, /* vkCmdSetCoverageModulationTableEnableNV */
         189, /* vkCmdSetCoverageModulationTableNV */
         190, /* vkCmdSetCoverageReductionModeNV */
         191, /* vkCmdSetCoverageToColorEnableNV */
         192, /* vkCmdSetCoverageToColorLocationNV */
         202, /* vkCmdSetDepthClampEnableEXT */
         204, /* vkCmdSetDepthClipEnableEXT */
         205, /* vkCmdSetDepthClipNegativeOneToOneEXT */
         224, /* vkCmdSetExtraPrimitiveOverestimationSizeEXT */
         229, /* vkCmdSetLineRasterizationModeEXT */
         232, /* vkCmdSetLineStippleEnableEXT */
         236, /* vkCmdSetLogicOpEnableEXT */
         241, /* vkCmdSetPolygonModeEXT */
         246, /* vkCmdSetProvokingVertexModeEXT */
         247, /* vkCmdSetRasterizationSamplesEXT */
         248, /* vkCmdSetRasterizationStreamEXT */
         256, /* vkCmdSetRepresentativeFragmentTestEnableNV */
         258, /* vkCmdSetSampleLocationsEnableEXT */
         259, /* vkCmdSetSampleMaskEXT */
         263, /* vkCmdSetShadingRateImageEnableNV */
         271, /* vkCmdSetTessellationDomainOriginEXT */
         275, /* vkCmdSetViewportSwizzleNV */
         276  /* vkCmdSetViewportWScalingEnableNV */
    };
    if (!context->EXT_extended_dynamic_state3) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_external_memory_host(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         544  /* vkGetMemoryHostPointerPropertiesEXT */
    };
    if (!context->EXT_external_memory_host) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_METAL_EXT)
static void glad_vk_load_VK_EXT_external_memory_metal(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         545, /* vkGetMemoryMetalHandleEXT */
         546  /* vkGetMemoryMetalHandlePropertiesEXT */
    };
    if (!context->EXT_external_memory_metal) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_fragment_density_map_offset(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         138  /* vkCmdEndRendering2EXT */
    };
    if (!context->EXT_fragment_density_map_offset) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_EXT_full_screen_exclusive(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           1, /* vkAcquireFullScreenExclusiveModeEXT */
         489, /* vkGetDeviceGroupSurfacePresentModes2EXT */
         608, /* vkGetPhysicalDeviceSurfacePresentModes2EXT */
         688  /* vkReleaseFullScreenExclusiveModeEXT */
    };
    if (!context->EXT_full_screen_exclusive) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_hdr_metadata(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         705  /* vkSetHdrMetadataEXT */
    };
    if (!context->EXT_hdr_metadata) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_headless_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         341  /* vkCreateHeadlessSurfaceEXT */
    };
    if (!context->EXT_headless_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_host_image_copy(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         303, /* vkCopyImageToImageEXT */
         305, /* vkCopyImageToMemoryEXT */
         308, /* vkCopyMemoryToImageEXT */
         533, /* vkGetImageSubresourceLayout2EXT */
         715  /* vkTransitionImageLayoutEXT */
    };
    if (!context->EXT_host_image_copy) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_host_query_reset(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         698  /* vkResetQueryPoolEXT */
    };
    if (!context->EXT_host_query_reset) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_image_compression_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         533  /* vkGetImageSubresourceLayout2EXT */
    };
    if (!context->EXT_image_compression_control) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_image_drm_format_modifier(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         523  /* vkGetImageDrmFormatModifierPropertiesEXT */
    };
    if (!context->EXT_image_drm_format_modifier) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_line_rasterization(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         231  /* vkCmdSetLineStippleEXT */
    };
    if (!context->EXT_line_rasterization) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_mesh_shader(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         120, /* vkCmdDrawMeshTasksEXT */
         121, /* vkCmdDrawMeshTasksIndirectCountEXT */
         123  /* vkCmdDrawMeshTasksIndirectEXT */
    };
    if (!context->EXT_mesh_shader) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_METAL_EXT)
static void glad_vk_load_VK_EXT_metal_objects(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         448  /* vkExportMetalObjectsEXT */
    };
    if (!context->EXT_metal_objects) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_METAL_EXT)
static void glad_vk_load_VK_EXT_metal_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         351  /* vkCreateMetalSurfaceEXT */
    };
    if (!context->EXT_metal_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_multi_draw(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         126, /* vkCmdDrawMultiEXT */
         127  /* vkCmdDrawMultiIndexedEXT */
    };
    if (!context->EXT_multi_draw) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_opacity_micromap(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          23, /* vkBuildMicromapsEXT */
          62, /* vkCmdBuildMicromapsEXT */
          87, /* vkCmdCopyMemoryToMicromapEXT */
          88, /* vkCmdCopyMicromapEXT */
          89, /* vkCmdCopyMicromapToMemoryEXT */
         294, /* vkCmdWriteMicromapsPropertiesEXT */
         309, /* vkCopyMemoryToMicromapEXT */
         310, /* vkCopyMicromapEXT */
         311, /* vkCopyMicromapToMemoryEXT */
         352, /* vkCreateMicromapEXT */
         415, /* vkDestroyMicromapEXT */
         500, /* vkGetDeviceMicromapCompatibilityEXT */
         553, /* vkGetMicromapBuildSizesEXT */
         733  /* vkWriteMicromapsPropertiesEXT */
    };
    if (!context->EXT_opacity_micromap) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_pageable_device_local_memory(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         703  /* vkSetDeviceMemoryPriorityEXT */
    };
    if (!context->EXT_pageable_device_local_memory) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_pipeline_properties(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         628  /* vkGetPipelinePropertiesEXT */
    };
    if (!context->EXT_pipeline_properties) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_private_data(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         358, /* vkCreatePrivateDataSlotEXT */
         422, /* vkDestroyPrivateDataSlotEXT */
         630, /* vkGetPrivateDataEXT */
         710  /* vkSetPrivateDataEXT */
    };
    if (!context->EXT_private_data) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_sample_locations(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         257, /* vkCmdSetSampleLocationsEXT */
         588  /* vkGetPhysicalDeviceMultisamplePropertiesEXT */
    };
    if (!context->EXT_sample_locations) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_shader_module_identifier(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         652, /* vkGetShaderModuleCreateInfoIdentifierEXT */
         653  /* vkGetShaderModuleIdentifierEXT */
    };
    if (!context->EXT_shader_module_identifier) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_shader_object(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          48, /* vkCmdBindShadersEXT */
          54, /* vkCmdBindVertexBuffers2EXT */
         175, /* vkCmdSetAlphaToCoverageEnableEXT */
         176, /* vkCmdSetAlphaToOneEnableEXT */
         181, /* vkCmdSetColorBlendAdvancedEXT */
         182, /* vkCmdSetColorBlendEnableEXT */
         183, /* vkCmdSetColorBlendEquationEXT */
         185, /* vkCmdSetColorWriteMaskEXT */
         186, /* vkCmdSetConservativeRasterizationModeEXT */
         187, /* vkCmdSetCoverageModulationModeNV */
         188, /* vkCmdSetCoverageModulationTableEnableNV */
         189, /* vkCmdSetCoverageModulationTableNV */
         190, /* vkCmdSetCoverageReductionModeNV */
         191, /* vkCmdSetCoverageToColorEnableNV */
         192, /* vkCmdSetCoverageToColorLocationNV */
         194, /* vkCmdSetCullModeEXT */
         198, /* vkCmdSetDepthBiasEnableEXT */
         201, /* vkCmdSetDepthBoundsTestEnableEXT */
         202, /* vkCmdSetDepthClampEnableEXT */
         203, /* vkCmdSetDepthClampRangeEXT */
         204, /* vkCmdSetDepthClipEnableEXT */
         205, /* vkCmdSetDepthClipNegativeOneToOneEXT */
         207, /* vkCmdSetDepthCompareOpEXT */
         209, /* vkCmdSetDepthTestEnableEXT */
         211, /* vkCmdSetDepthWriteEnableEXT */
         224, /* vkCmdSetExtraPrimitiveOverestimationSizeEXT */
         228, /* vkCmdSetFrontFaceEXT */
         229, /* vkCmdSetLineRasterizationModeEXT */
         232, /* vkCmdSetLineStippleEnableEXT */
         235, /* vkCmdSetLogicOpEXT */
         236, /* vkCmdSetLogicOpEnableEXT */
         237, /* vkCmdSetPatchControlPointsEXT */
         241, /* vkCmdSetPolygonModeEXT */
         243, /* vkCmdSetPrimitiveRestartEnableEXT */
         245, /* vkCmdSetPrimitiveTopologyEXT */
         246, /* vkCmdSetProvokingVertexModeEXT */
         247, /* vkCmdSetRasterizationSamplesEXT */
         248, /* vkCmdSetRasterizationStreamEXT */
         250, /* vkCmdSetRasterizerDiscardEnableEXT */
         256, /* vkCmdSetRepresentativeFragmentTestEnableNV */
         258, /* vkCmdSetSampleLocationsEnableEXT */
         259, /* vkCmdSetSampleMaskEXT */
         262, /* vkCmdSetScissorWithCountEXT */
         263, /* vkCmdSetShadingRateImageEnableNV */
         266, /* vkCmdSetStencilOpEXT */
         269, /* vkCmdSetStencilTestEnableEXT */
         271, /* vkCmdSetTessellationDomainOriginEXT */
         272, /* vkCmdSetVertexInputEXT */
         275, /* vkCmdSetViewportSwizzleNV */
         276, /* vkCmdSetViewportWScalingEnableNV */
         279, /* vkCmdSetViewportWithCountEXT */
         371, /* vkCreateShadersEXT */
         429, /* vkDestroyShaderEXT */
         650  /* vkGetShaderBinaryDataEXT */
    };
    if (!context->EXT_shader_object) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_swapchain_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         691  /* vkReleaseSwapchainImagesEXT */
    };
    if (!context->EXT_swapchain_maintenance1) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_tooling_info(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         612  /* vkGetPhysicalDeviceToolPropertiesEXT */
    };
    if (!context->EXT_tooling_info) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_transform_feedback(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          28, /* vkCmdBeginQueryIndexedEXT */
          34, /* vkCmdBeginTransformFeedbackEXT */
          51, /* vkCmdBindTransformFeedbackBuffersEXT */
         116, /* vkCmdDrawIndirectByteCountEXT */
         133, /* vkCmdEndQueryIndexedEXT */
         140  /* vkCmdEndTransformFeedbackEXT */
    };
    if (!context->EXT_transform_feedback) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_validation_cache(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         375, /* vkCreateValidationCacheEXT */
         433, /* vkDestroyValidationCacheEXT */
         657, /* vkGetValidationCacheDataEXT */
         672  /* vkMergeValidationCachesEXT */
    };
    if (!context->EXT_validation_cache) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_vertex_input_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         272  /* vkCmdSetVertexInputEXT */
    };
    if (!context->EXT_vertex_input_dynamic_state) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_buffer_collection(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         316, /* vkCreateBufferCollectionFUCHSIA */
         390, /* vkDestroyBufferCollectionFUCHSIA */
         459, /* vkGetBufferCollectionPropertiesFUCHSIA */
         699, /* vkSetBufferCollectionBufferConstraintsFUCHSIA */
         700  /* vkSetBufferCollectionImageConstraintsFUCHSIA */
    };
    if (!context->FUCHSIA_buffer_collection) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_external_memory(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         551, /* vkGetMemoryZirconHandleFUCHSIA */
         552  /* vkGetMemoryZirconHandlePropertiesFUCHSIA */
    };
    if (!context->FUCHSIA_external_memory) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_external_semaphore(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         649, /* vkGetSemaphoreZirconHandleFUCHSIA */
         664  /* vkImportSemaphoreZirconHandleFUCHSIA */
    };
    if (!context->FUCHSIA_external_semaphore) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_imagepipe_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         344  /* vkCreateImagePipeSurfaceFUCHSIA */
    };
    if (!context->FUCHSIA_imagepipe_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_GGP)
static void glad_vk_load_VK_GGP_stream_descriptor_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         373  /* vkCreateStreamDescriptorSurfaceGGP */
    };
    if (!context->GGP_stream_descriptor_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_GOOGLE_display_timing(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         555, /* vkGetPastPresentationTimingGOOGLE */
         639  /* vkGetRefreshCycleDurationGOOGLE */
    };
    if (!context->GOOGLE_display_timing) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_HUAWEI_cluster_culling_shader(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         108, /* vkCmdDrawClusterHUAWEI */
         109  /* vkCmdDrawClusterIndirectHUAWEI */
    };
    if (!context->HUAWEI_cluster_culling_shader) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_HUAWEI_invocation_mask(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          45  /* vkCmdBindInvocationMaskHUAWEI */
    };
    if (!context->HUAWEI_invocation_mask) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_HUAWEI_subpass_shading(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         280, /* vkCmdSubpassShadingHUAWEI */
         504  /* vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI */
    };
    if (!context->HUAWEI_subpass_shading) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_INTEL_performance_query(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           4, /* vkAcquirePerformanceConfigurationINTEL */
         238, /* vkCmdSetPerformanceMarkerINTEL */
         239, /* vkCmdSetPerformanceOverrideINTEL */
         240, /* vkCmdSetPerformanceStreamMarkerINTEL */
         556, /* vkGetPerformanceParameterINTEL */
         665, /* vkInitializePerformanceApiINTEL */
         679, /* vkQueueSetPerformanceConfigurationINTEL */
         689, /* vkReleasePerformanceConfigurationINTEL */
         718  /* vkUninitializePerformanceApiINTEL */
    };
    if (!context->INTEL_performance_query) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_acceleration_structure(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          22, /* vkBuildAccelerationStructuresKHR */
          59, /* vkCmdBuildAccelerationStructuresIndirectKHR */
          60, /* vkCmdBuildAccelerationStructuresKHR */
          69, /* vkCmdCopyAccelerationStructureKHR */
          71, /* vkCmdCopyAccelerationStructureToMemoryKHR */
          85, /* vkCmdCopyMemoryToAccelerationStructureKHR */
         290, /* vkCmdWriteAccelerationStructuresPropertiesKHR */
         300, /* vkCopyAccelerationStructureKHR */
         301, /* vkCopyAccelerationStructureToMemoryKHR */
         306, /* vkCopyMemoryToAccelerationStructureKHR */
         312, /* vkCreateAccelerationStructureKHR */
         387, /* vkDestroyAccelerationStructureKHR */
         453, /* vkGetAccelerationStructureBuildSizesKHR */
         454, /* vkGetAccelerationStructureDeviceAddressKHR */
         482, /* vkGetDeviceAccelerationStructureCompatibilityKHR */
         732  /* vkWriteAccelerationStructuresPropertiesKHR */
    };
    if (!context->KHR_acceleration_structure) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
static void glad_vk_load_VK_KHR_android_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         314  /* vkCreateAndroidSurfaceKHR */
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
         462, /* vkGetBufferDeviceAddressKHR */
         467, /* vkGetBufferOpaqueCaptureAddressKHR */
         499  /* vkGetDeviceMemoryOpaqueCaptureAddressKHR */
    };
    if (!context->KHR_buffer_device_address) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_calibrated_timestamps(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         470, /* vkGetCalibratedTimestampsKHR */
         558  /* vkGetPhysicalDeviceCalibrateableTimeDomainsKHR */
    };
    if (!context->KHR_calibrated_timestamps) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_cooperative_matrix(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         560  /* vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR */
    };
    if (!context->KHR_cooperative_matrix) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_copy_commands2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          57, /* vkCmdBlitImage2KHR */
          74, /* vkCmdCopyBuffer2KHR */
          77, /* vkCmdCopyBufferToImage2KHR */
          80, /* vkCmdCopyImage2KHR */
          83, /* vkCmdCopyImageToBuffer2KHR */
         174  /* vkCmdResolveImage2KHR */
    };
    if (!context->KHR_copy_commands2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_create_renderpass2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          31, /* vkCmdBeginRenderPass2KHR */
         136, /* vkCmdEndRenderPass2KHR */
         150, /* vkCmdNextSubpass2KHR */
         364  /* vkCreateRenderPass2KHR */
    };
    if (!context->KHR_create_renderpass2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_deferred_host_operations(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         326, /* vkCreateDeferredOperationKHR */
         386, /* vkDeferredOperationJoinKHR */
         399, /* vkDestroyDeferredOperationKHR */
         473, /* vkGetDeferredOperationMaxConcurrencyKHR */
         474  /* vkGetDeferredOperationResultKHR */
    };
    if (!context->KHR_deferred_host_operations) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_descriptor_update_template(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         167, /* vkCmdPushDescriptorSetWithTemplateKHR */
         330, /* vkCreateDescriptorUpdateTemplateKHR */
         403, /* vkDestroyDescriptorUpdateTemplateKHR */
         723  /* vkUpdateDescriptorSetWithTemplateKHR */
    };
    if (!context->KHR_descriptor_update_template) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_device_group(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           2, /* vkAcquireNextImage2KHR */
         101, /* vkCmdDispatchBaseKHR */
         215, /* vkCmdSetDeviceMaskKHR */
         487, /* vkGetDeviceGroupPeerMemoryFeaturesKHR */
         488, /* vkGetDeviceGroupPresentCapabilitiesKHR */
         490, /* vkGetDeviceGroupSurfacePresentModesKHR */
         590  /* vkGetPhysicalDevicePresentRectanglesKHR */
    };
    if (!context->KHR_device_group) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_device_group_creation(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         445  /* vkEnumeratePhysicalDeviceGroupsKHR */
    };
    if (!context->KHR_device_group_creation) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         333, /* vkCreateDisplayModeKHR */
         334, /* vkCreateDisplayPlaneSurfaceKHR */
         506, /* vkGetDisplayModePropertiesKHR */
         508, /* vkGetDisplayPlaneCapabilitiesKHR */
         509, /* vkGetDisplayPlaneSupportedDisplaysKHR */
         565, /* vkGetPhysicalDeviceDisplayPlanePropertiesKHR */
         567  /* vkGetPhysicalDeviceDisplayPropertiesKHR */
    };
    if (!context->KHR_display) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_display_swapchain(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         372  /* vkCreateSharedSwapchainsKHR */
    };
    if (!context->KHR_display_swapchain) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_draw_indirect_count(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         114, /* vkCmdDrawIndexedIndirectCountKHR */
         119  /* vkCmdDrawIndirectCountKHR */
    };
    if (!context->KHR_draw_indirect_count) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_dynamic_rendering(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          33, /* vkCmdBeginRenderingKHR */
         139  /* vkCmdEndRenderingKHR */
    };
    if (!context->KHR_dynamic_rendering) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_dynamic_rendering_local_read(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         253, /* vkCmdSetRenderingAttachmentLocationsKHR */
         255  /* vkCmdSetRenderingInputAttachmentIndicesKHR */
    };
    if (!context->KHR_dynamic_rendering_local_read) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_external_fence_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         571  /* vkGetPhysicalDeviceExternalFencePropertiesKHR */
    };
    if (!context->KHR_external_fence_capabilities) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_external_fence_fd(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         517, /* vkGetFenceFdKHR */
         660  /* vkImportFenceFdKHR */
    };
    if (!context->KHR_external_fence_fd) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_external_fence_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         519, /* vkGetFenceWin32HandleKHR */
         661  /* vkImportFenceWin32HandleKHR */
    };
    if (!context->KHR_external_fence_win32) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_KHR_external_memory_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         569  /* vkGetPhysicalDeviceExternalBufferPropertiesKHR */
    };
    if (!context->KHR_external_memory_capabilities) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_external_memory_fd(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         542, /* vkGetMemoryFdKHR */
         543  /* vkGetMemoryFdPropertiesKHR */
    };
    if (!context->KHR_external_memory_fd) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_external_memory_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         548, /* vkGetMemoryWin32HandleKHR */
         550  /* vkGetMemoryWin32HandlePropertiesKHR */
    };
    if (!context->KHR_external_memory_win32) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_KHR_external_semaphore_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         574  /* vkGetPhysicalDeviceExternalSemaphorePropertiesKHR */
    };
    if (!context->KHR_external_semaphore_capabilities) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_external_semaphore_fd(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         647, /* vkGetSemaphoreFdKHR */
         662  /* vkImportSemaphoreFdKHR */
    };
    if (!context->KHR_external_semaphore_fd) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_external_semaphore_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         648, /* vkGetSemaphoreWin32HandleKHR */
         663  /* vkImportSemaphoreWin32HandleKHR */
    };
    if (!context->KHR_external_semaphore_win32) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_KHR_fragment_shading_rate(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         226, /* vkCmdSetFragmentShadingRateKHR */
         581  /* vkGetPhysicalDeviceFragmentShadingRatesKHR */
    };
    if (!context->KHR_fragment_shading_rate) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_get_display_properties2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         505, /* vkGetDisplayModeProperties2KHR */
         507, /* vkGetDisplayPlaneCapabilities2KHR */
         564, /* vkGetPhysicalDeviceDisplayPlaneProperties2KHR */
         566  /* vkGetPhysicalDeviceDisplayProperties2KHR */
    };
    if (!context->KHR_get_display_properties2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_get_memory_requirements2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         465, /* vkGetBufferMemoryRequirements2KHR */
         526, /* vkGetImageMemoryRequirements2KHR */
         530  /* vkGetImageSparseMemoryRequirements2KHR */
    };
    if (!context->KHR_get_memory_requirements2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_get_physical_device_properties2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         577, /* vkGetPhysicalDeviceFeatures2KHR */
         580, /* vkGetPhysicalDeviceFormatProperties2KHR */
         584, /* vkGetPhysicalDeviceImageFormatProperties2KHR */
         587, /* vkGetPhysicalDeviceMemoryProperties2KHR */
         593, /* vkGetPhysicalDeviceProperties2KHR */
         597, /* vkGetPhysicalDeviceQueueFamilyProperties2KHR */
         601  /* vkGetPhysicalDeviceSparseImageFormatProperties2KHR */
    };
    if (!context->KHR_get_physical_device_properties2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_get_surface_capabilities2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         604, /* vkGetPhysicalDeviceSurfaceCapabilities2KHR */
         606  /* vkGetPhysicalDeviceSurfaceFormats2KHR */
    };
    if (!context->KHR_get_surface_capabilities2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_line_rasterization(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         233  /* vkCmdSetLineStippleKHR */
    };
    if (!context->KHR_line_rasterization) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         717  /* vkTrimCommandPoolKHR */
    };
    if (!context->KHR_maintenance1) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_maintenance3(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         481  /* vkGetDescriptorSetLayoutSupportKHR */
    };
    if (!context->KHR_maintenance3) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_maintenance4(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         484, /* vkGetDeviceBufferMemoryRequirementsKHR */
         492, /* vkGetDeviceImageMemoryRequirementsKHR */
         494  /* vkGetDeviceImageSparseMemoryRequirementsKHR */
    };
    if (!context->KHR_maintenance4) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_maintenance5(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          44, /* vkCmdBindIndexBuffer2KHR */
         496, /* vkGetDeviceImageSubresourceLayoutKHR */
         534, /* vkGetImageSubresourceLayout2KHR */
         642  /* vkGetRenderingAreaGranularityKHR */
    };
    if (!context->KHR_maintenance5) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_maintenance6(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          36, /* vkCmdBindDescriptorBufferEmbeddedSamplers2EXT */
          41, /* vkCmdBindDescriptorSets2KHR */
         159, /* vkCmdPushConstants2KHR */
         162, /* vkCmdPushDescriptorSet2KHR */
         166, /* vkCmdPushDescriptorSetWithTemplate2KHR */
         212  /* vkCmdSetDescriptorBufferOffsets2EXT */
    };
    if (!context->KHR_maintenance6) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_map_memory2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         670, /* vkMapMemory2KHR */
         721  /* vkUnmapMemory2KHR */
    };
    if (!context->KHR_map_memory2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_performance_query(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           5, /* vkAcquireProfilingLockKHR */
         446, /* vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR */
         594, /* vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR */
         690  /* vkReleaseProfilingLockKHR */
    };
    if (!context->KHR_performance_query) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_pipeline_binary(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         354, /* vkCreatePipelineBinariesKHR */
         418, /* vkDestroyPipelineBinaryKHR */
         620, /* vkGetPipelineBinaryDataKHR */
         627, /* vkGetPipelineKeyKHR */
         686  /* vkReleaseCapturedPipelineDataKHR */
    };
    if (!context->KHR_pipeline_binary) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_pipeline_executable_properties(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         622, /* vkGetPipelineExecutableInternalRepresentationsKHR */
         623, /* vkGetPipelineExecutablePropertiesKHR */
         624  /* vkGetPipelineExecutableStatisticsKHR */
    };
    if (!context->KHR_pipeline_executable_properties) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_present_wait(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         729  /* vkWaitForPresentKHR */
    };
    if (!context->KHR_present_wait) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_push_descriptor(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         163, /* vkCmdPushDescriptorSetKHR */
         167  /* vkCmdPushDescriptorSetWithTemplateKHR */
    };
    if (!context->KHR_push_descriptor) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_ray_tracing_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         281  /* vkCmdTraceRaysIndirect2KHR */
    };
    if (!context->KHR_ray_tracing_maintenance1) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_ray_tracing_pipeline(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         251, /* vkCmdSetRayTracingPipelineStackSizeKHR */
         282, /* vkCmdTraceRaysIndirectKHR */
         283, /* vkCmdTraceRaysKHR */
         360, /* vkCreateRayTracingPipelinesKHR */
         635, /* vkGetRayTracingCaptureReplayShaderGroupHandlesKHR */
         636, /* vkGetRayTracingShaderGroupHandlesKHR */
         638  /* vkGetRayTracingShaderGroupStackSizeKHR */
    };
    if (!context->KHR_ray_tracing_pipeline) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_sampler_ycbcr_conversion(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         367, /* vkCreateSamplerYcbcrConversionKHR */
         427  /* vkDestroySamplerYcbcrConversionKHR */
    };
    if (!context->KHR_sampler_ycbcr_conversion) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_shared_presentable_image(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         656  /* vkGetSwapchainStatusKHR */
    };
    if (!context->KHR_shared_presentable_image) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         431, /* vkDestroySurfaceKHR */
         605, /* vkGetPhysicalDeviceSurfaceCapabilitiesKHR */
         607, /* vkGetPhysicalDeviceSurfaceFormatsKHR */
         609, /* vkGetPhysicalDeviceSurfacePresentModesKHR */
         610  /* vkGetPhysicalDeviceSurfaceSupportKHR */
    };
    if (!context->KHR_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_swapchain(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           2, /* vkAcquireNextImage2KHR */
           3, /* vkAcquireNextImageKHR */
         374, /* vkCreateSwapchainKHR */
         432, /* vkDestroySwapchainKHR */
         488, /* vkGetDeviceGroupPresentCapabilitiesKHR */
         490, /* vkGetDeviceGroupSurfacePresentModesKHR */
         590, /* vkGetPhysicalDevicePresentRectanglesKHR */
         655, /* vkGetSwapchainImagesKHR */
         678  /* vkQueuePresentKHR */
    };
    if (!context->KHR_swapchain) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_synchronization2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         154, /* vkCmdPipelineBarrier2KHR */
         170, /* vkCmdResetEvent2KHR */
         221, /* vkCmdSetEvent2KHR */
         289, /* vkCmdWaitEvents2KHR */
         297, /* vkCmdWriteTimestamp2KHR */
         682  /* vkQueueSubmit2KHR */
    };
    if (!context->KHR_synchronization2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_timeline_semaphore(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         646, /* vkGetSemaphoreCounterValueKHR */
         712, /* vkSignalSemaphoreKHR */
         731  /* vkWaitSemaphoresKHR */
    };
    if (!context->KHR_timeline_semaphore) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_video_decode_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          96  /* vkCmdDecodeVideoKHR */
    };
    if (!context->KHR_video_decode_queue) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_video_encode_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         128, /* vkCmdEncodeVideoKHR */
         512, /* vkGetEncodedVideoSessionParametersKHR */
         614  /* vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR */
    };
    if (!context->KHR_video_encode_queue) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_video_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          21, /* vkBindVideoSessionMemoryKHR */
          35, /* vkCmdBeginVideoCodingKHR */
          67, /* vkCmdControlVideoCodingKHR */
         141, /* vkCmdEndVideoCodingKHR */
         377, /* vkCreateVideoSessionKHR */
         378, /* vkCreateVideoSessionParametersKHR */
         434, /* vkDestroyVideoSessionKHR */
         435, /* vkDestroyVideoSessionParametersKHR */
         613, /* vkGetPhysicalDeviceVideoCapabilitiesKHR */
         615, /* vkGetPhysicalDeviceVideoFormatPropertiesKHR */
         658, /* vkGetVideoSessionMemoryRequirementsKHR */
         727  /* vkUpdateVideoSessionParametersKHR */
    };
    if (!context->KHR_video_queue) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
static void glad_vk_load_VK_KHR_wayland_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         379, /* vkCreateWaylandSurfaceKHR */
         616  /* vkGetPhysicalDeviceWaylandPresentationSupportKHR */
    };
    if (!context->KHR_wayland_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_win32_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         380, /* vkCreateWin32SurfaceKHR */
         617  /* vkGetPhysicalDeviceWin32PresentationSupportKHR */
    };
    if (!context->KHR_win32_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
static void glad_vk_load_VK_KHR_xcb_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         381, /* vkCreateXcbSurfaceKHR */
         618  /* vkGetPhysicalDeviceXcbPresentationSupportKHR */
    };
    if (!context->KHR_xcb_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)
static void glad_vk_load_VK_KHR_xlib_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         382, /* vkCreateXlibSurfaceKHR */
         619  /* vkGetPhysicalDeviceXlibPresentationSupportKHR */
    };
    if (!context->KHR_xlib_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_IOS_MVK)
static void glad_vk_load_VK_MVK_ios_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         342  /* vkCreateIOSSurfaceMVK */
    };
    if (!context->MVK_ios_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_MACOS_MVK)
static void glad_vk_load_VK_MVK_macos_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         350  /* vkCreateMacOSSurfaceMVK */
    };
    if (!context->MVK_macos_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_VI_NN)
static void glad_vk_load_VK_NN_vi_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         376  /* vkCreateViSurfaceNN */
    };
    if (!context->NN_vi_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_NVX_binary_import(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          91, /* vkCmdCuLaunchKernelNVX */
         320, /* vkCreateCuFunctionNVX */
         321, /* vkCreateCuModuleNVX */
         393, /* vkDestroyCuFunctionNVX */
         394  /* vkDestroyCuModuleNVX */
    };
    if (!context->NVX_binary_import) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NVX_image_view_handle(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         535, /* vkGetImageViewAddressNVX */
         536, /* vkGetImageViewHandle64NVX */
         537  /* vkGetImageViewHandleNVX */
    };
    if (!context->NVX_image_view_handle) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_NV_acquire_winrt_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           6, /* vkAcquireWinrtDisplayNV */
         659  /* vkGetWinrtDisplayNV */
    };
    if (!context->NV_acquire_winrt_display) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_NV_clip_space_w_scaling(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         277  /* vkCmdSetViewportWScalingNV */
    };
    if (!context->NV_clip_space_w_scaling) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_cluster_acceleration_structure(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          61, /* vkCmdBuildClusterAccelerationStructureIndirectNV */
         471  /* vkGetClusterAccelerationStructureBuildSizesNV */
    };
    if (!context->NV_cluster_acceleration_structure) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_cooperative_matrix(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         561  /* vkGetPhysicalDeviceCooperativeMatrixPropertiesNV */
    };
    if (!context->NV_cooperative_matrix) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_cooperative_matrix2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         559  /* vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV */
    };
    if (!context->NV_cooperative_matrix2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_cooperative_vector(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          68, /* vkCmdConvertCooperativeVectorMatrixNV */
         299, /* vkConvertCooperativeVectorMatrixNV */
         562  /* vkGetPhysicalDeviceCooperativeVectorPropertiesNV */
    };
    if (!context->NV_cooperative_vector) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_copy_memory_indirect(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          84, /* vkCmdCopyMemoryIndirectNV */
          86  /* vkCmdCopyMemoryToImageIndirectNV */
    };
    if (!context->NV_copy_memory_indirect) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_coverage_reduction_mode(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         602  /* vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV */
    };
    if (!context->NV_coverage_reduction_mode) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_ENABLE_BETA_EXTENSIONS)
static void glad_vk_load_VK_NV_cuda_kernel_launch(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          92, /* vkCmdCudaLaunchKernelNV */
         322, /* vkCreateCudaFunctionNV */
         323, /* vkCreateCudaModuleNV */
         395, /* vkDestroyCudaFunctionNV */
         396, /* vkDestroyCudaModuleNV */
         472  /* vkGetCudaModuleCacheNV */
    };
    if (!context->NV_cuda_kernel_launch) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_NV_device_diagnostic_checkpoints(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         179, /* vkCmdSetCheckpointNV */
         632, /* vkGetQueueCheckpointData2NV */
         633  /* vkGetQueueCheckpointDataNV */
    };
    if (!context->NV_device_diagnostic_checkpoints) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_device_generated_commands(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          47, /* vkCmdBindPipelineShaderGroupNV */
         144, /* vkCmdExecuteGeneratedCommandsNV */
         156, /* vkCmdPreprocessGeneratedCommandsNV */
         347, /* vkCreateIndirectCommandsLayoutNV */
         412, /* vkDestroyIndirectCommandsLayoutNV */
         522  /* vkGetGeneratedCommandsMemoryRequirementsNV */
    };
    if (!context->NV_device_generated_commands) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_device_generated_commands_compute(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         286, /* vkCmdUpdatePipelineIndirectBufferNV */
         625, /* vkGetPipelineIndirectDeviceAddressNV */
         626  /* vkGetPipelineIndirectMemoryRequirementsNV */
    };
    if (!context->NV_device_generated_commands_compute) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_external_compute_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         337, /* vkCreateExternalComputeQueueNV */
         406, /* vkDestroyExternalComputeQueueNV */
         516  /* vkGetExternalComputeQueueDataNV */
    };
    if (!context->NV_external_compute_queue) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_external_memory_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         572  /* vkGetPhysicalDeviceExternalImageFormatPropertiesNV */
    };
    if (!context->NV_external_memory_capabilities) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_external_memory_rdma(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         547  /* vkGetMemoryRemoteAddressNV */
    };
    if (!context->NV_external_memory_rdma) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_NV_external_memory_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         549  /* vkGetMemoryWin32HandleNV */
    };
    if (!context->NV_external_memory_win32) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_NV_fragment_shading_rate_enums(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         225  /* vkCmdSetFragmentShadingRateEnumNV */
    };
    if (!context->NV_fragment_shading_rate_enums) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_low_latency2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         540, /* vkGetLatencyTimingsNV */
         667, /* vkLatencySleepNV */
         677, /* vkQueueNotifyOutOfBandNV */
         706, /* vkSetLatencyMarkerNV */
         707  /* vkSetLatencySleepModeNV */
    };
    if (!context->NV_low_latency2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_memory_decompression(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          97, /* vkCmdDecompressMemoryIndirectCountNV */
          98  /* vkCmdDecompressMemoryNV */
    };
    if (!context->NV_memory_decompression) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_mesh_shader(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         122, /* vkCmdDrawMeshTasksIndirectCountNV */
         124, /* vkCmdDrawMeshTasksIndirectNV */
         125  /* vkCmdDrawMeshTasksNV */
    };
    if (!context->NV_mesh_shader) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_optical_flow(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          20, /* vkBindOpticalFlowSessionImageNV */
         151, /* vkCmdOpticalFlowExecuteNV */
         353, /* vkCreateOpticalFlowSessionNV */
         416, /* vkDestroyOpticalFlowSessionNV */
         589  /* vkGetPhysicalDeviceOpticalFlowImageFormatsNV */
    };
    if (!context->NV_optical_flow) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_partitioned_acceleration_structure(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          63, /* vkCmdBuildPartitionedAccelerationStructuresNV */
         554  /* vkGetPartitionedAccelerationStructuresBuildSizesNV */
    };
    if (!context->NV_partitioned_acceleration_structure) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_ray_tracing(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          13, /* vkBindAccelerationStructureMemoryNV */
          58, /* vkCmdBuildAccelerationStructureNV */
          70, /* vkCmdCopyAccelerationStructureNV */
         284, /* vkCmdTraceRaysNV */
         291, /* vkCmdWriteAccelerationStructuresPropertiesNV */
         298, /* vkCompileDeferredNV */
         313, /* vkCreateAccelerationStructureNV */
         361, /* vkCreateRayTracingPipelinesNV */
         388, /* vkDestroyAccelerationStructureNV */
         455, /* vkGetAccelerationStructureHandleNV */
         456, /* vkGetAccelerationStructureMemoryRequirementsNV */
         637  /* vkGetRayTracingShaderGroupHandlesNV */
    };
    if (!context->NV_ray_tracing) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_scissor_exclusive(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         222, /* vkCmdSetExclusiveScissorEnableNV */
         223  /* vkCmdSetExclusiveScissorNV */
    };
    if (!context->NV_scissor_exclusive) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_shading_rate_image(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          49, /* vkCmdBindShadingRateImageNV */
         180, /* vkCmdSetCoarseSampleOrderNV */
         274  /* vkCmdSetViewportShadingRatePaletteNV */
    };
    if (!context->NV_shading_rate_image) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_QCOM_tile_memory_heap(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          50  /* vkCmdBindTileMemoryQCOM */
    };
    if (!context->QCOM_tile_memory_heap) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_QCOM_tile_properties(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         511, /* vkGetDynamicRenderingTilePropertiesQCOM */
         520  /* vkGetFramebufferTilePropertiesQCOM */
    };
    if (!context->QCOM_tile_properties) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_QCOM_tile_shading(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          26, /* vkCmdBeginPerTileExecutionQCOM */
         106, /* vkCmdDispatchTileQCOM */
         131  /* vkCmdEndPerTileExecutionQCOM */
    };
    if (!context->QCOM_tile_shading) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_SCREEN_QNX)
static void glad_vk_load_VK_QNX_external_memory_screen_buffer(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         644  /* vkGetScreenBufferPropertiesQNX */
    };
    if (!context->QNX_external_memory_screen_buffer) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
static void glad_vk_load_VK_QNX_screen_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         368, /* vkCreateScreenSurfaceQNX */
         598  /* vkGetPhysicalDeviceScreenPresentationSupportQNX */
    };
    if (!context->QNX_screen_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_VALVE_descriptor_set_host_mapping(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         476, /* vkGetDescriptorSetHostMappingVALVE */
         478  /* vkGetDescriptorSetLayoutHostMappingInfoVALVE */
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
        {   32,   33 }, /* vkCmdBeginRendering and vkCmdBeginRenderingKHR */
        {   33,   32 }, /* vkCmdBeginRenderingKHR and vkCmdBeginRendering */
        {   30,   31 }, /* vkCmdBeginRenderPass2 and vkCmdBeginRenderPass2KHR */
        {   31,   30 }, /* vkCmdBeginRenderPass2KHR and vkCmdBeginRenderPass2 */
        {   40,   41 }, /* vkCmdBindDescriptorSets2 and vkCmdBindDescriptorSets2KHR */
        {   41,   40 }, /* vkCmdBindDescriptorSets2KHR and vkCmdBindDescriptorSets2 */
        {   43,   44 }, /* vkCmdBindIndexBuffer2 and vkCmdBindIndexBuffer2KHR */
        {   44,   43 }, /* vkCmdBindIndexBuffer2KHR and vkCmdBindIndexBuffer2 */
        {   53,   54 }, /* vkCmdBindVertexBuffers2 and vkCmdBindVertexBuffers2EXT */
        {   54,   53 }, /* vkCmdBindVertexBuffers2EXT and vkCmdBindVertexBuffers2 */
        {   56,   57 }, /* vkCmdBlitImage2 and vkCmdBlitImage2KHR */
        {   57,   56 }, /* vkCmdBlitImage2KHR and vkCmdBlitImage2 */
        {   73,   74 }, /* vkCmdCopyBuffer2 and vkCmdCopyBuffer2KHR */
        {   74,   73 }, /* vkCmdCopyBuffer2KHR and vkCmdCopyBuffer2 */
        {   76,   77 }, /* vkCmdCopyBufferToImage2 and vkCmdCopyBufferToImage2KHR */
        {   77,   76 }, /* vkCmdCopyBufferToImage2KHR and vkCmdCopyBufferToImage2 */
        {   79,   80 }, /* vkCmdCopyImage2 and vkCmdCopyImage2KHR */
        {   80,   79 }, /* vkCmdCopyImage2KHR and vkCmdCopyImage2 */
        {   82,   83 }, /* vkCmdCopyImageToBuffer2 and vkCmdCopyImageToBuffer2KHR */
        {   83,   82 }, /* vkCmdCopyImageToBuffer2KHR and vkCmdCopyImageToBuffer2 */
        {  100,  101 }, /* vkCmdDispatchBase and vkCmdDispatchBaseKHR */
        {  101,  100 }, /* vkCmdDispatchBaseKHR and vkCmdDispatchBase */
        {  112,  113 }, /* vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountAMD */
        {  112,  114 }, /* vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountKHR */
        {  113,  112 }, /* vkCmdDrawIndexedIndirectCountAMD and vkCmdDrawIndexedIndirectCount */
        {  113,  114 }, /* vkCmdDrawIndexedIndirectCountAMD and vkCmdDrawIndexedIndirectCountKHR */
        {  114,  112 }, /* vkCmdDrawIndexedIndirectCountKHR and vkCmdDrawIndexedIndirectCount */
        {  114,  113 }, /* vkCmdDrawIndexedIndirectCountKHR and vkCmdDrawIndexedIndirectCountAMD */
        {  117,  118 }, /* vkCmdDrawIndirectCount and vkCmdDrawIndirectCountAMD */
        {  117,  119 }, /* vkCmdDrawIndirectCount and vkCmdDrawIndirectCountKHR */
        {  118,  117 }, /* vkCmdDrawIndirectCountAMD and vkCmdDrawIndirectCount */
        {  118,  119 }, /* vkCmdDrawIndirectCountAMD and vkCmdDrawIndirectCountKHR */
        {  119,  117 }, /* vkCmdDrawIndirectCountKHR and vkCmdDrawIndirectCount */
        {  119,  118 }, /* vkCmdDrawIndirectCountKHR and vkCmdDrawIndirectCountAMD */
        {  137,  139 }, /* vkCmdEndRendering and vkCmdEndRenderingKHR */
        {  139,  137 }, /* vkCmdEndRenderingKHR and vkCmdEndRendering */
        {  135,  136 }, /* vkCmdEndRenderPass2 and vkCmdEndRenderPass2KHR */
        {  136,  135 }, /* vkCmdEndRenderPass2KHR and vkCmdEndRenderPass2 */
        {  149,  150 }, /* vkCmdNextSubpass2 and vkCmdNextSubpass2KHR */
        {  150,  149 }, /* vkCmdNextSubpass2KHR and vkCmdNextSubpass2 */
        {  153,  154 }, /* vkCmdPipelineBarrier2 and vkCmdPipelineBarrier2KHR */
        {  154,  153 }, /* vkCmdPipelineBarrier2KHR and vkCmdPipelineBarrier2 */
        {  158,  159 }, /* vkCmdPushConstants2 and vkCmdPushConstants2KHR */
        {  159,  158 }, /* vkCmdPushConstants2KHR and vkCmdPushConstants2 */
        {  160,  163 }, /* vkCmdPushDescriptorSet and vkCmdPushDescriptorSetKHR */
        {  161,  162 }, /* vkCmdPushDescriptorSet2 and vkCmdPushDescriptorSet2KHR */
        {  162,  161 }, /* vkCmdPushDescriptorSet2KHR and vkCmdPushDescriptorSet2 */
        {  163,  160 }, /* vkCmdPushDescriptorSetKHR and vkCmdPushDescriptorSet */
        {  164,  167 }, /* vkCmdPushDescriptorSetWithTemplate and vkCmdPushDescriptorSetWithTemplateKHR */
        {  165,  166 }, /* vkCmdPushDescriptorSetWithTemplate2 and vkCmdPushDescriptorSetWithTemplate2KHR */
        {  166,  165 }, /* vkCmdPushDescriptorSetWithTemplate2KHR and vkCmdPushDescriptorSetWithTemplate2 */
        {  167,  164 }, /* vkCmdPushDescriptorSetWithTemplateKHR and vkCmdPushDescriptorSetWithTemplate */
        {  169,  170 }, /* vkCmdResetEvent2 and vkCmdResetEvent2KHR */
        {  170,  169 }, /* vkCmdResetEvent2KHR and vkCmdResetEvent2 */
        {  173,  174 }, /* vkCmdResolveImage2 and vkCmdResolveImage2KHR */
        {  174,  173 }, /* vkCmdResolveImage2KHR and vkCmdResolveImage2 */
        {  193,  194 }, /* vkCmdSetCullMode and vkCmdSetCullModeEXT */
        {  194,  193 }, /* vkCmdSetCullModeEXT and vkCmdSetCullMode */
        {  197,  198 }, /* vkCmdSetDepthBiasEnable and vkCmdSetDepthBiasEnableEXT */
        {  198,  197 }, /* vkCmdSetDepthBiasEnableEXT and vkCmdSetDepthBiasEnable */
        {  200,  201 }, /* vkCmdSetDepthBoundsTestEnable and vkCmdSetDepthBoundsTestEnableEXT */
        {  201,  200 }, /* vkCmdSetDepthBoundsTestEnableEXT and vkCmdSetDepthBoundsTestEnable */
        {  206,  207 }, /* vkCmdSetDepthCompareOp and vkCmdSetDepthCompareOpEXT */
        {  207,  206 }, /* vkCmdSetDepthCompareOpEXT and vkCmdSetDepthCompareOp */
        {  208,  209 }, /* vkCmdSetDepthTestEnable and vkCmdSetDepthTestEnableEXT */
        {  209,  208 }, /* vkCmdSetDepthTestEnableEXT and vkCmdSetDepthTestEnable */
        {  210,  211 }, /* vkCmdSetDepthWriteEnable and vkCmdSetDepthWriteEnableEXT */
        {  211,  210 }, /* vkCmdSetDepthWriteEnableEXT and vkCmdSetDepthWriteEnable */
        {  214,  215 }, /* vkCmdSetDeviceMask and vkCmdSetDeviceMaskKHR */
        {  215,  214 }, /* vkCmdSetDeviceMaskKHR and vkCmdSetDeviceMask */
        {  220,  221 }, /* vkCmdSetEvent2 and vkCmdSetEvent2KHR */
        {  221,  220 }, /* vkCmdSetEvent2KHR and vkCmdSetEvent2 */
        {  227,  228 }, /* vkCmdSetFrontFace and vkCmdSetFrontFaceEXT */
        {  228,  227 }, /* vkCmdSetFrontFaceEXT and vkCmdSetFrontFace */
        {  230,  231 }, /* vkCmdSetLineStipple and vkCmdSetLineStippleEXT */
        {  230,  233 }, /* vkCmdSetLineStipple and vkCmdSetLineStippleKHR */
        {  231,  230 }, /* vkCmdSetLineStippleEXT and vkCmdSetLineStipple */
        {  231,  233 }, /* vkCmdSetLineStippleEXT and vkCmdSetLineStippleKHR */
        {  233,  230 }, /* vkCmdSetLineStippleKHR and vkCmdSetLineStipple */
        {  233,  231 }, /* vkCmdSetLineStippleKHR and vkCmdSetLineStippleEXT */
        {  242,  243 }, /* vkCmdSetPrimitiveRestartEnable and vkCmdSetPrimitiveRestartEnableEXT */
        {  243,  242 }, /* vkCmdSetPrimitiveRestartEnableEXT and vkCmdSetPrimitiveRestartEnable */
        {  244,  245 }, /* vkCmdSetPrimitiveTopology and vkCmdSetPrimitiveTopologyEXT */
        {  245,  244 }, /* vkCmdSetPrimitiveTopologyEXT and vkCmdSetPrimitiveTopology */
        {  249,  250 }, /* vkCmdSetRasterizerDiscardEnable and vkCmdSetRasterizerDiscardEnableEXT */
        {  250,  249 }, /* vkCmdSetRasterizerDiscardEnableEXT and vkCmdSetRasterizerDiscardEnable */
        {  252,  253 }, /* vkCmdSetRenderingAttachmentLocations and vkCmdSetRenderingAttachmentLocationsKHR */
        {  253,  252 }, /* vkCmdSetRenderingAttachmentLocationsKHR and vkCmdSetRenderingAttachmentLocations */
        {  254,  255 }, /* vkCmdSetRenderingInputAttachmentIndices and vkCmdSetRenderingInputAttachmentIndicesKHR */
        {  255,  254 }, /* vkCmdSetRenderingInputAttachmentIndicesKHR and vkCmdSetRenderingInputAttachmentIndices */
        {  261,  262 }, /* vkCmdSetScissorWithCount and vkCmdSetScissorWithCountEXT */
        {  262,  261 }, /* vkCmdSetScissorWithCountEXT and vkCmdSetScissorWithCount */
        {  265,  266 }, /* vkCmdSetStencilOp and vkCmdSetStencilOpEXT */
        {  266,  265 }, /* vkCmdSetStencilOpEXT and vkCmdSetStencilOp */
        {  268,  269 }, /* vkCmdSetStencilTestEnable and vkCmdSetStencilTestEnableEXT */
        {  269,  268 }, /* vkCmdSetStencilTestEnableEXT and vkCmdSetStencilTestEnable */
        {  278,  279 }, /* vkCmdSetViewportWithCount and vkCmdSetViewportWithCountEXT */
        {  279,  278 }, /* vkCmdSetViewportWithCountEXT and vkCmdSetViewportWithCount */
        {  288,  289 }, /* vkCmdWaitEvents2 and vkCmdWaitEvents2KHR */
        {  289,  288 }, /* vkCmdWaitEvents2KHR and vkCmdWaitEvents2 */
        {  296,  297 }, /* vkCmdWriteTimestamp2 and vkCmdWriteTimestamp2KHR */
        {  297,  296 }, /* vkCmdWriteTimestamp2KHR and vkCmdWriteTimestamp2 */
        {  302,  303 }, /* vkCopyImageToImage and vkCopyImageToImageEXT */
        {  303,  302 }, /* vkCopyImageToImageEXT and vkCopyImageToImage */
        {  304,  305 }, /* vkCopyImageToMemory and vkCopyImageToMemoryEXT */
        {  305,  304 }, /* vkCopyImageToMemoryEXT and vkCopyImageToMemory */
        {  307,  308 }, /* vkCopyMemoryToImage and vkCopyMemoryToImageEXT */
        {  308,  307 }, /* vkCopyMemoryToImageEXT and vkCopyMemoryToImage */
        {  329,  330 }, /* vkCreateDescriptorUpdateTemplate and vkCreateDescriptorUpdateTemplateKHR */
        {  330,  329 }, /* vkCreateDescriptorUpdateTemplateKHR and vkCreateDescriptorUpdateTemplate */
        {  357,  358 }, /* vkCreatePrivateDataSlot and vkCreatePrivateDataSlotEXT */
        {  358,  357 }, /* vkCreatePrivateDataSlotEXT and vkCreatePrivateDataSlot */
        {  363,  364 }, /* vkCreateRenderPass2 and vkCreateRenderPass2KHR */
        {  364,  363 }, /* vkCreateRenderPass2KHR and vkCreateRenderPass2 */
        {  366,  367 }, /* vkCreateSamplerYcbcrConversion and vkCreateSamplerYcbcrConversionKHR */
        {  367,  366 }, /* vkCreateSamplerYcbcrConversionKHR and vkCreateSamplerYcbcrConversion */
        {  402,  403 }, /* vkDestroyDescriptorUpdateTemplate and vkDestroyDescriptorUpdateTemplateKHR */
        {  403,  402 }, /* vkDestroyDescriptorUpdateTemplateKHR and vkDestroyDescriptorUpdateTemplate */
        {  421,  422 }, /* vkDestroyPrivateDataSlot and vkDestroyPrivateDataSlotEXT */
        {  422,  421 }, /* vkDestroyPrivateDataSlotEXT and vkDestroyPrivateDataSlot */
        {  426,  427 }, /* vkDestroySamplerYcbcrConversion and vkDestroySamplerYcbcrConversionKHR */
        {  427,  426 }, /* vkDestroySamplerYcbcrConversionKHR and vkDestroySamplerYcbcrConversion */
        {  444,  445 }, /* vkEnumeratePhysicalDeviceGroups and vkEnumeratePhysicalDeviceGroupsKHR */
        {  445,  444 }, /* vkEnumeratePhysicalDeviceGroupsKHR and vkEnumeratePhysicalDeviceGroups */
        {  460,  461 }, /* vkGetBufferDeviceAddress and vkGetBufferDeviceAddressEXT */
        {  460,  462 }, /* vkGetBufferDeviceAddress and vkGetBufferDeviceAddressKHR */
        {  461,  460 }, /* vkGetBufferDeviceAddressEXT and vkGetBufferDeviceAddress */
        {  461,  462 }, /* vkGetBufferDeviceAddressEXT and vkGetBufferDeviceAddressKHR */
        {  462,  460 }, /* vkGetBufferDeviceAddressKHR and vkGetBufferDeviceAddress */
        {  462,  461 }, /* vkGetBufferDeviceAddressKHR and vkGetBufferDeviceAddressEXT */
        {  464,  465 }, /* vkGetBufferMemoryRequirements2 and vkGetBufferMemoryRequirements2KHR */
        {  465,  464 }, /* vkGetBufferMemoryRequirements2KHR and vkGetBufferMemoryRequirements2 */
        {  466,  467 }, /* vkGetBufferOpaqueCaptureAddress and vkGetBufferOpaqueCaptureAddressKHR */
        {  467,  466 }, /* vkGetBufferOpaqueCaptureAddressKHR and vkGetBufferOpaqueCaptureAddress */
        {  469,  470 }, /* vkGetCalibratedTimestampsEXT and vkGetCalibratedTimestampsKHR */
        {  470,  469 }, /* vkGetCalibratedTimestampsKHR and vkGetCalibratedTimestampsEXT */
        {  480,  481 }, /* vkGetDescriptorSetLayoutSupport and vkGetDescriptorSetLayoutSupportKHR */
        {  481,  480 }, /* vkGetDescriptorSetLayoutSupportKHR and vkGetDescriptorSetLayoutSupport */
        {  483,  484 }, /* vkGetDeviceBufferMemoryRequirements and vkGetDeviceBufferMemoryRequirementsKHR */
        {  484,  483 }, /* vkGetDeviceBufferMemoryRequirementsKHR and vkGetDeviceBufferMemoryRequirements */
        {  486,  487 }, /* vkGetDeviceGroupPeerMemoryFeatures and vkGetDeviceGroupPeerMemoryFeaturesKHR */
        {  487,  486 }, /* vkGetDeviceGroupPeerMemoryFeaturesKHR and vkGetDeviceGroupPeerMemoryFeatures */
        {  491,  492 }, /* vkGetDeviceImageMemoryRequirements and vkGetDeviceImageMemoryRequirementsKHR */
        {  492,  491 }, /* vkGetDeviceImageMemoryRequirementsKHR and vkGetDeviceImageMemoryRequirements */
        {  493,  494 }, /* vkGetDeviceImageSparseMemoryRequirements and vkGetDeviceImageSparseMemoryRequirementsKHR */
        {  494,  493 }, /* vkGetDeviceImageSparseMemoryRequirementsKHR and vkGetDeviceImageSparseMemoryRequirements */
        {  495,  496 }, /* vkGetDeviceImageSubresourceLayout and vkGetDeviceImageSubresourceLayoutKHR */
        {  496,  495 }, /* vkGetDeviceImageSubresourceLayoutKHR and vkGetDeviceImageSubresourceLayout */
        {  498,  499 }, /* vkGetDeviceMemoryOpaqueCaptureAddress and vkGetDeviceMemoryOpaqueCaptureAddressKHR */
        {  499,  498 }, /* vkGetDeviceMemoryOpaqueCaptureAddressKHR and vkGetDeviceMemoryOpaqueCaptureAddress */
        {  525,  526 }, /* vkGetImageMemoryRequirements2 and vkGetImageMemoryRequirements2KHR */
        {  526,  525 }, /* vkGetImageMemoryRequirements2KHR and vkGetImageMemoryRequirements2 */
        {  529,  530 }, /* vkGetImageSparseMemoryRequirements2 and vkGetImageSparseMemoryRequirements2KHR */
        {  530,  529 }, /* vkGetImageSparseMemoryRequirements2KHR and vkGetImageSparseMemoryRequirements2 */
        {  532,  533 }, /* vkGetImageSubresourceLayout2 and vkGetImageSubresourceLayout2EXT */
        {  532,  534 }, /* vkGetImageSubresourceLayout2 and vkGetImageSubresourceLayout2KHR */
        {  533,  532 }, /* vkGetImageSubresourceLayout2EXT and vkGetImageSubresourceLayout2 */
        {  533,  534 }, /* vkGetImageSubresourceLayout2EXT and vkGetImageSubresourceLayout2KHR */
        {  534,  532 }, /* vkGetImageSubresourceLayout2KHR and vkGetImageSubresourceLayout2 */
        {  534,  533 }, /* vkGetImageSubresourceLayout2KHR and vkGetImageSubresourceLayout2EXT */
        {  557,  558 }, /* vkGetPhysicalDeviceCalibrateableTimeDomainsEXT and vkGetPhysicalDeviceCalibrateableTimeDomainsKHR */
        {  558,  557 }, /* vkGetPhysicalDeviceCalibrateableTimeDomainsKHR and vkGetPhysicalDeviceCalibrateableTimeDomainsEXT */
        {  568,  569 }, /* vkGetPhysicalDeviceExternalBufferProperties and vkGetPhysicalDeviceExternalBufferPropertiesKHR */
        {  569,  568 }, /* vkGetPhysicalDeviceExternalBufferPropertiesKHR and vkGetPhysicalDeviceExternalBufferProperties */
        {  570,  571 }, /* vkGetPhysicalDeviceExternalFenceProperties and vkGetPhysicalDeviceExternalFencePropertiesKHR */
        {  571,  570 }, /* vkGetPhysicalDeviceExternalFencePropertiesKHR and vkGetPhysicalDeviceExternalFenceProperties */
        {  573,  574 }, /* vkGetPhysicalDeviceExternalSemaphoreProperties and vkGetPhysicalDeviceExternalSemaphorePropertiesKHR */
        {  574,  573 }, /* vkGetPhysicalDeviceExternalSemaphorePropertiesKHR and vkGetPhysicalDeviceExternalSemaphoreProperties */
        {  576,  577 }, /* vkGetPhysicalDeviceFeatures2 and vkGetPhysicalDeviceFeatures2KHR */
        {  577,  576 }, /* vkGetPhysicalDeviceFeatures2KHR and vkGetPhysicalDeviceFeatures2 */
        {  579,  580 }, /* vkGetPhysicalDeviceFormatProperties2 and vkGetPhysicalDeviceFormatProperties2KHR */
        {  580,  579 }, /* vkGetPhysicalDeviceFormatProperties2KHR and vkGetPhysicalDeviceFormatProperties2 */
        {  583,  584 }, /* vkGetPhysicalDeviceImageFormatProperties2 and vkGetPhysicalDeviceImageFormatProperties2KHR */
        {  584,  583 }, /* vkGetPhysicalDeviceImageFormatProperties2KHR and vkGetPhysicalDeviceImageFormatProperties2 */
        {  586,  587 }, /* vkGetPhysicalDeviceMemoryProperties2 and vkGetPhysicalDeviceMemoryProperties2KHR */
        {  587,  586 }, /* vkGetPhysicalDeviceMemoryProperties2KHR and vkGetPhysicalDeviceMemoryProperties2 */
        {  592,  593 }, /* vkGetPhysicalDeviceProperties2 and vkGetPhysicalDeviceProperties2KHR */
        {  593,  592 }, /* vkGetPhysicalDeviceProperties2KHR and vkGetPhysicalDeviceProperties2 */
        {  596,  597 }, /* vkGetPhysicalDeviceQueueFamilyProperties2 and vkGetPhysicalDeviceQueueFamilyProperties2KHR */
        {  597,  596 }, /* vkGetPhysicalDeviceQueueFamilyProperties2KHR and vkGetPhysicalDeviceQueueFamilyProperties2 */
        {  600,  601 }, /* vkGetPhysicalDeviceSparseImageFormatProperties2 and vkGetPhysicalDeviceSparseImageFormatProperties2KHR */
        {  601,  600 }, /* vkGetPhysicalDeviceSparseImageFormatProperties2KHR and vkGetPhysicalDeviceSparseImageFormatProperties2 */
        {  611,  612 }, /* vkGetPhysicalDeviceToolProperties and vkGetPhysicalDeviceToolPropertiesEXT */
        {  612,  611 }, /* vkGetPhysicalDeviceToolPropertiesEXT and vkGetPhysicalDeviceToolProperties */
        {  629,  630 }, /* vkGetPrivateData and vkGetPrivateDataEXT */
        {  630,  629 }, /* vkGetPrivateDataEXT and vkGetPrivateData */
        {  636,  637 }, /* vkGetRayTracingShaderGroupHandlesKHR and vkGetRayTracingShaderGroupHandlesNV */
        {  637,  636 }, /* vkGetRayTracingShaderGroupHandlesNV and vkGetRayTracingShaderGroupHandlesKHR */
        {  641,  642 }, /* vkGetRenderingAreaGranularity and vkGetRenderingAreaGranularityKHR */
        {  642,  641 }, /* vkGetRenderingAreaGranularityKHR and vkGetRenderingAreaGranularity */
        {  645,  646 }, /* vkGetSemaphoreCounterValue and vkGetSemaphoreCounterValueKHR */
        {  646,  645 }, /* vkGetSemaphoreCounterValueKHR and vkGetSemaphoreCounterValue */
        {  669,  670 }, /* vkMapMemory2 and vkMapMemory2KHR */
        {  670,  669 }, /* vkMapMemory2KHR and vkMapMemory2 */
        {  681,  682 }, /* vkQueueSubmit2 and vkQueueSubmit2KHR */
        {  682,  681 }, /* vkQueueSubmit2KHR and vkQueueSubmit2 */
        {  697,  698 }, /* vkResetQueryPool and vkResetQueryPoolEXT */
        {  698,  697 }, /* vkResetQueryPoolEXT and vkResetQueryPool */
        {  709,  710 }, /* vkSetPrivateData and vkSetPrivateDataEXT */
        {  710,  709 }, /* vkSetPrivateDataEXT and vkSetPrivateData */
        {  711,  712 }, /* vkSignalSemaphore and vkSignalSemaphoreKHR */
        {  712,  711 }, /* vkSignalSemaphoreKHR and vkSignalSemaphore */
        {  714,  715 }, /* vkTransitionImageLayout and vkTransitionImageLayoutEXT */
        {  715,  714 }, /* vkTransitionImageLayoutEXT and vkTransitionImageLayout */
        {  716,  717 }, /* vkTrimCommandPool and vkTrimCommandPoolKHR */
        {  717,  716 }, /* vkTrimCommandPoolKHR and vkTrimCommandPool */
        {  720,  721 }, /* vkUnmapMemory2 and vkUnmapMemory2KHR */
        {  721,  720 }, /* vkUnmapMemory2KHR and vkUnmapMemory2 */
        {  722,  723 }, /* vkUpdateDescriptorSetWithTemplate and vkUpdateDescriptorSetWithTemplateKHR */
        {  723,  722 }, /* vkUpdateDescriptorSetWithTemplateKHR and vkUpdateDescriptorSetWithTemplate */
        {  730,  731 }, /* vkWaitSemaphores and vkWaitSemaphoresKHR */
        {  731,  730 }, /* vkWaitSemaphoresKHR and vkWaitSemaphores */
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
    glad_vk_load_VK_EXT_fragment_density_map_offset(context, load, userptr);
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
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    glad_vk_load_VK_NV_cuda_kernel_launch(context, load, userptr);
#endif
    glad_vk_load_VK_NV_device_diagnostic_checkpoints(context, load, userptr);
    glad_vk_load_VK_NV_device_generated_commands(context, load, userptr);
    glad_vk_load_VK_NV_device_generated_commands_compute(context, load, userptr);
    glad_vk_load_VK_NV_external_compute_queue(context, load, userptr);
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
    glad_vk_load_VK_QCOM_tile_memory_heap(context, load, userptr);
    glad_vk_load_VK_QCOM_tile_properties(context, load, userptr);
    glad_vk_load_VK_QCOM_tile_shading(context, load, userptr);
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
    0xfc27ea97ed553e3f, /* vkCreateExternalComputeQueueNV */
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
