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
    /*   17 */ "vkBindDataGraphPipelineSessionMemoryARM",
    /*   18 */ "vkBindImageMemory",
    /*   19 */ "vkBindImageMemory2",
    /*   20 */ "vkBindImageMemory2KHR",
    /*   21 */ "vkBindOpticalFlowSessionImageNV",
    /*   22 */ "vkBindTensorMemoryARM",
    /*   23 */ "vkBindVideoSessionMemoryKHR",
    /*   24 */ "vkBuildAccelerationStructuresKHR",
    /*   25 */ "vkBuildMicromapsEXT",
    /*   26 */ "vkCmdBeginConditionalRenderingEXT",
    /*   27 */ "vkCmdBeginDebugUtilsLabelEXT",
    /*   28 */ "vkCmdBeginPerTileExecutionQCOM",
    /*   29 */ "vkCmdBeginQuery",
    /*   30 */ "vkCmdBeginQueryIndexedEXT",
    /*   31 */ "vkCmdBeginRenderPass",
    /*   32 */ "vkCmdBeginRenderPass2",
    /*   33 */ "vkCmdBeginRenderPass2KHR",
    /*   34 */ "vkCmdBeginRendering",
    /*   35 */ "vkCmdBeginRenderingKHR",
    /*   36 */ "vkCmdBeginTransformFeedbackEXT",
    /*   37 */ "vkCmdBeginVideoCodingKHR",
    /*   38 */ "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT",
    /*   39 */ "vkCmdBindDescriptorBufferEmbeddedSamplersEXT",
    /*   40 */ "vkCmdBindDescriptorBuffersEXT",
    /*   41 */ "vkCmdBindDescriptorSets",
    /*   42 */ "vkCmdBindDescriptorSets2",
    /*   43 */ "vkCmdBindDescriptorSets2KHR",
    /*   44 */ "vkCmdBindIndexBuffer",
    /*   45 */ "vkCmdBindIndexBuffer2",
    /*   46 */ "vkCmdBindIndexBuffer2KHR",
    /*   47 */ "vkCmdBindInvocationMaskHUAWEI",
    /*   48 */ "vkCmdBindPipeline",
    /*   49 */ "vkCmdBindPipelineShaderGroupNV",
    /*   50 */ "vkCmdBindShadersEXT",
    /*   51 */ "vkCmdBindShadingRateImageNV",
    /*   52 */ "vkCmdBindTileMemoryQCOM",
    /*   53 */ "vkCmdBindTransformFeedbackBuffersEXT",
    /*   54 */ "vkCmdBindVertexBuffers",
    /*   55 */ "vkCmdBindVertexBuffers2",
    /*   56 */ "vkCmdBindVertexBuffers2EXT",
    /*   57 */ "vkCmdBlitImage",
    /*   58 */ "vkCmdBlitImage2",
    /*   59 */ "vkCmdBlitImage2KHR",
    /*   60 */ "vkCmdBuildAccelerationStructureNV",
    /*   61 */ "vkCmdBuildAccelerationStructuresIndirectKHR",
    /*   62 */ "vkCmdBuildAccelerationStructuresKHR",
    /*   63 */ "vkCmdBuildClusterAccelerationStructureIndirectNV",
    /*   64 */ "vkCmdBuildMicromapsEXT",
    /*   65 */ "vkCmdBuildPartitionedAccelerationStructuresNV",
    /*   66 */ "vkCmdClearAttachments",
    /*   67 */ "vkCmdClearColorImage",
    /*   68 */ "vkCmdClearDepthStencilImage",
    /*   69 */ "vkCmdControlVideoCodingKHR",
    /*   70 */ "vkCmdConvertCooperativeVectorMatrixNV",
    /*   71 */ "vkCmdCopyAccelerationStructureKHR",
    /*   72 */ "vkCmdCopyAccelerationStructureNV",
    /*   73 */ "vkCmdCopyAccelerationStructureToMemoryKHR",
    /*   74 */ "vkCmdCopyBuffer",
    /*   75 */ "vkCmdCopyBuffer2",
    /*   76 */ "vkCmdCopyBuffer2KHR",
    /*   77 */ "vkCmdCopyBufferToImage",
    /*   78 */ "vkCmdCopyBufferToImage2",
    /*   79 */ "vkCmdCopyBufferToImage2KHR",
    /*   80 */ "vkCmdCopyImage",
    /*   81 */ "vkCmdCopyImage2",
    /*   82 */ "vkCmdCopyImage2KHR",
    /*   83 */ "vkCmdCopyImageToBuffer",
    /*   84 */ "vkCmdCopyImageToBuffer2",
    /*   85 */ "vkCmdCopyImageToBuffer2KHR",
    /*   86 */ "vkCmdCopyMemoryIndirectNV",
    /*   87 */ "vkCmdCopyMemoryToAccelerationStructureKHR",
    /*   88 */ "vkCmdCopyMemoryToImageIndirectNV",
    /*   89 */ "vkCmdCopyMemoryToMicromapEXT",
    /*   90 */ "vkCmdCopyMicromapEXT",
    /*   91 */ "vkCmdCopyMicromapToMemoryEXT",
    /*   92 */ "vkCmdCopyQueryPoolResults",
    /*   93 */ "vkCmdCopyTensorARM",
    /*   94 */ "vkCmdCuLaunchKernelNVX",
    /*   95 */ "vkCmdCudaLaunchKernelNV",
    /*   96 */ "vkCmdDebugMarkerBeginEXT",
    /*   97 */ "vkCmdDebugMarkerEndEXT",
    /*   98 */ "vkCmdDebugMarkerInsertEXT",
    /*   99 */ "vkCmdDecodeVideoKHR",
    /*  100 */ "vkCmdDecompressMemoryIndirectCountNV",
    /*  101 */ "vkCmdDecompressMemoryNV",
    /*  102 */ "vkCmdDispatch",
    /*  103 */ "vkCmdDispatchBase",
    /*  104 */ "vkCmdDispatchBaseKHR",
    /*  105 */ "vkCmdDispatchDataGraphARM",
    /*  106 */ "vkCmdDispatchGraphAMDX",
    /*  107 */ "vkCmdDispatchGraphIndirectAMDX",
    /*  108 */ "vkCmdDispatchGraphIndirectCountAMDX",
    /*  109 */ "vkCmdDispatchIndirect",
    /*  110 */ "vkCmdDispatchTileQCOM",
    /*  111 */ "vkCmdDraw",
    /*  112 */ "vkCmdDrawClusterHUAWEI",
    /*  113 */ "vkCmdDrawClusterIndirectHUAWEI",
    /*  114 */ "vkCmdDrawIndexed",
    /*  115 */ "vkCmdDrawIndexedIndirect",
    /*  116 */ "vkCmdDrawIndexedIndirectCount",
    /*  117 */ "vkCmdDrawIndexedIndirectCountAMD",
    /*  118 */ "vkCmdDrawIndexedIndirectCountKHR",
    /*  119 */ "vkCmdDrawIndirect",
    /*  120 */ "vkCmdDrawIndirectByteCountEXT",
    /*  121 */ "vkCmdDrawIndirectCount",
    /*  122 */ "vkCmdDrawIndirectCountAMD",
    /*  123 */ "vkCmdDrawIndirectCountKHR",
    /*  124 */ "vkCmdDrawMeshTasksEXT",
    /*  125 */ "vkCmdDrawMeshTasksIndirectCountEXT",
    /*  126 */ "vkCmdDrawMeshTasksIndirectCountNV",
    /*  127 */ "vkCmdDrawMeshTasksIndirectEXT",
    /*  128 */ "vkCmdDrawMeshTasksIndirectNV",
    /*  129 */ "vkCmdDrawMeshTasksNV",
    /*  130 */ "vkCmdDrawMultiEXT",
    /*  131 */ "vkCmdDrawMultiIndexedEXT",
    /*  132 */ "vkCmdEncodeVideoKHR",
    /*  133 */ "vkCmdEndConditionalRenderingEXT",
    /*  134 */ "vkCmdEndDebugUtilsLabelEXT",
    /*  135 */ "vkCmdEndPerTileExecutionQCOM",
    /*  136 */ "vkCmdEndQuery",
    /*  137 */ "vkCmdEndQueryIndexedEXT",
    /*  138 */ "vkCmdEndRenderPass",
    /*  139 */ "vkCmdEndRenderPass2",
    /*  140 */ "vkCmdEndRenderPass2KHR",
    /*  141 */ "vkCmdEndRendering",
    /*  142 */ "vkCmdEndRendering2EXT",
    /*  143 */ "vkCmdEndRenderingKHR",
    /*  144 */ "vkCmdEndTransformFeedbackEXT",
    /*  145 */ "vkCmdEndVideoCodingKHR",
    /*  146 */ "vkCmdExecuteCommands",
    /*  147 */ "vkCmdExecuteGeneratedCommandsEXT",
    /*  148 */ "vkCmdExecuteGeneratedCommandsNV",
    /*  149 */ "vkCmdFillBuffer",
    /*  150 */ "vkCmdInitializeGraphScratchMemoryAMDX",
    /*  151 */ "vkCmdInsertDebugUtilsLabelEXT",
    /*  152 */ "vkCmdNextSubpass",
    /*  153 */ "vkCmdNextSubpass2",
    /*  154 */ "vkCmdNextSubpass2KHR",
    /*  155 */ "vkCmdOpticalFlowExecuteNV",
    /*  156 */ "vkCmdPipelineBarrier",
    /*  157 */ "vkCmdPipelineBarrier2",
    /*  158 */ "vkCmdPipelineBarrier2KHR",
    /*  159 */ "vkCmdPreprocessGeneratedCommandsEXT",
    /*  160 */ "vkCmdPreprocessGeneratedCommandsNV",
    /*  161 */ "vkCmdPushConstants",
    /*  162 */ "vkCmdPushConstants2",
    /*  163 */ "vkCmdPushConstants2KHR",
    /*  164 */ "vkCmdPushDescriptorSet",
    /*  165 */ "vkCmdPushDescriptorSet2",
    /*  166 */ "vkCmdPushDescriptorSet2KHR",
    /*  167 */ "vkCmdPushDescriptorSetKHR",
    /*  168 */ "vkCmdPushDescriptorSetWithTemplate",
    /*  169 */ "vkCmdPushDescriptorSetWithTemplate2",
    /*  170 */ "vkCmdPushDescriptorSetWithTemplate2KHR",
    /*  171 */ "vkCmdPushDescriptorSetWithTemplateKHR",
    /*  172 */ "vkCmdResetEvent",
    /*  173 */ "vkCmdResetEvent2",
    /*  174 */ "vkCmdResetEvent2KHR",
    /*  175 */ "vkCmdResetQueryPool",
    /*  176 */ "vkCmdResolveImage",
    /*  177 */ "vkCmdResolveImage2",
    /*  178 */ "vkCmdResolveImage2KHR",
    /*  179 */ "vkCmdSetAlphaToCoverageEnableEXT",
    /*  180 */ "vkCmdSetAlphaToOneEnableEXT",
    /*  181 */ "vkCmdSetAttachmentFeedbackLoopEnableEXT",
    /*  182 */ "vkCmdSetBlendConstants",
    /*  183 */ "vkCmdSetCheckpointNV",
    /*  184 */ "vkCmdSetCoarseSampleOrderNV",
    /*  185 */ "vkCmdSetColorBlendAdvancedEXT",
    /*  186 */ "vkCmdSetColorBlendEnableEXT",
    /*  187 */ "vkCmdSetColorBlendEquationEXT",
    /*  188 */ "vkCmdSetColorWriteEnableEXT",
    /*  189 */ "vkCmdSetColorWriteMaskEXT",
    /*  190 */ "vkCmdSetConservativeRasterizationModeEXT",
    /*  191 */ "vkCmdSetCoverageModulationModeNV",
    /*  192 */ "vkCmdSetCoverageModulationTableEnableNV",
    /*  193 */ "vkCmdSetCoverageModulationTableNV",
    /*  194 */ "vkCmdSetCoverageReductionModeNV",
    /*  195 */ "vkCmdSetCoverageToColorEnableNV",
    /*  196 */ "vkCmdSetCoverageToColorLocationNV",
    /*  197 */ "vkCmdSetCullMode",
    /*  198 */ "vkCmdSetCullModeEXT",
    /*  199 */ "vkCmdSetDepthBias",
    /*  200 */ "vkCmdSetDepthBias2EXT",
    /*  201 */ "vkCmdSetDepthBiasEnable",
    /*  202 */ "vkCmdSetDepthBiasEnableEXT",
    /*  203 */ "vkCmdSetDepthBounds",
    /*  204 */ "vkCmdSetDepthBoundsTestEnable",
    /*  205 */ "vkCmdSetDepthBoundsTestEnableEXT",
    /*  206 */ "vkCmdSetDepthClampEnableEXT",
    /*  207 */ "vkCmdSetDepthClampRangeEXT",
    /*  208 */ "vkCmdSetDepthClipEnableEXT",
    /*  209 */ "vkCmdSetDepthClipNegativeOneToOneEXT",
    /*  210 */ "vkCmdSetDepthCompareOp",
    /*  211 */ "vkCmdSetDepthCompareOpEXT",
    /*  212 */ "vkCmdSetDepthTestEnable",
    /*  213 */ "vkCmdSetDepthTestEnableEXT",
    /*  214 */ "vkCmdSetDepthWriteEnable",
    /*  215 */ "vkCmdSetDepthWriteEnableEXT",
    /*  216 */ "vkCmdSetDescriptorBufferOffsets2EXT",
    /*  217 */ "vkCmdSetDescriptorBufferOffsetsEXT",
    /*  218 */ "vkCmdSetDeviceMask",
    /*  219 */ "vkCmdSetDeviceMaskKHR",
    /*  220 */ "vkCmdSetDiscardRectangleEXT",
    /*  221 */ "vkCmdSetDiscardRectangleEnableEXT",
    /*  222 */ "vkCmdSetDiscardRectangleModeEXT",
    /*  223 */ "vkCmdSetEvent",
    /*  224 */ "vkCmdSetEvent2",
    /*  225 */ "vkCmdSetEvent2KHR",
    /*  226 */ "vkCmdSetExclusiveScissorEnableNV",
    /*  227 */ "vkCmdSetExclusiveScissorNV",
    /*  228 */ "vkCmdSetExtraPrimitiveOverestimationSizeEXT",
    /*  229 */ "vkCmdSetFragmentShadingRateEnumNV",
    /*  230 */ "vkCmdSetFragmentShadingRateKHR",
    /*  231 */ "vkCmdSetFrontFace",
    /*  232 */ "vkCmdSetFrontFaceEXT",
    /*  233 */ "vkCmdSetLineRasterizationModeEXT",
    /*  234 */ "vkCmdSetLineStipple",
    /*  235 */ "vkCmdSetLineStippleEXT",
    /*  236 */ "vkCmdSetLineStippleEnableEXT",
    /*  237 */ "vkCmdSetLineStippleKHR",
    /*  238 */ "vkCmdSetLineWidth",
    /*  239 */ "vkCmdSetLogicOpEXT",
    /*  240 */ "vkCmdSetLogicOpEnableEXT",
    /*  241 */ "vkCmdSetPatchControlPointsEXT",
    /*  242 */ "vkCmdSetPerformanceMarkerINTEL",
    /*  243 */ "vkCmdSetPerformanceOverrideINTEL",
    /*  244 */ "vkCmdSetPerformanceStreamMarkerINTEL",
    /*  245 */ "vkCmdSetPolygonModeEXT",
    /*  246 */ "vkCmdSetPrimitiveRestartEnable",
    /*  247 */ "vkCmdSetPrimitiveRestartEnableEXT",
    /*  248 */ "vkCmdSetPrimitiveTopology",
    /*  249 */ "vkCmdSetPrimitiveTopologyEXT",
    /*  250 */ "vkCmdSetProvokingVertexModeEXT",
    /*  251 */ "vkCmdSetRasterizationSamplesEXT",
    /*  252 */ "vkCmdSetRasterizationStreamEXT",
    /*  253 */ "vkCmdSetRasterizerDiscardEnable",
    /*  254 */ "vkCmdSetRasterizerDiscardEnableEXT",
    /*  255 */ "vkCmdSetRayTracingPipelineStackSizeKHR",
    /*  256 */ "vkCmdSetRenderingAttachmentLocations",
    /*  257 */ "vkCmdSetRenderingAttachmentLocationsKHR",
    /*  258 */ "vkCmdSetRenderingInputAttachmentIndices",
    /*  259 */ "vkCmdSetRenderingInputAttachmentIndicesKHR",
    /*  260 */ "vkCmdSetRepresentativeFragmentTestEnableNV",
    /*  261 */ "vkCmdSetSampleLocationsEXT",
    /*  262 */ "vkCmdSetSampleLocationsEnableEXT",
    /*  263 */ "vkCmdSetSampleMaskEXT",
    /*  264 */ "vkCmdSetScissor",
    /*  265 */ "vkCmdSetScissorWithCount",
    /*  266 */ "vkCmdSetScissorWithCountEXT",
    /*  267 */ "vkCmdSetShadingRateImageEnableNV",
    /*  268 */ "vkCmdSetStencilCompareMask",
    /*  269 */ "vkCmdSetStencilOp",
    /*  270 */ "vkCmdSetStencilOpEXT",
    /*  271 */ "vkCmdSetStencilReference",
    /*  272 */ "vkCmdSetStencilTestEnable",
    /*  273 */ "vkCmdSetStencilTestEnableEXT",
    /*  274 */ "vkCmdSetStencilWriteMask",
    /*  275 */ "vkCmdSetTessellationDomainOriginEXT",
    /*  276 */ "vkCmdSetVertexInputEXT",
    /*  277 */ "vkCmdSetViewport",
    /*  278 */ "vkCmdSetViewportShadingRatePaletteNV",
    /*  279 */ "vkCmdSetViewportSwizzleNV",
    /*  280 */ "vkCmdSetViewportWScalingEnableNV",
    /*  281 */ "vkCmdSetViewportWScalingNV",
    /*  282 */ "vkCmdSetViewportWithCount",
    /*  283 */ "vkCmdSetViewportWithCountEXT",
    /*  284 */ "vkCmdSubpassShadingHUAWEI",
    /*  285 */ "vkCmdTraceRaysIndirect2KHR",
    /*  286 */ "vkCmdTraceRaysIndirectKHR",
    /*  287 */ "vkCmdTraceRaysKHR",
    /*  288 */ "vkCmdTraceRaysNV",
    /*  289 */ "vkCmdUpdateBuffer",
    /*  290 */ "vkCmdUpdatePipelineIndirectBufferNV",
    /*  291 */ "vkCmdWaitEvents",
    /*  292 */ "vkCmdWaitEvents2",
    /*  293 */ "vkCmdWaitEvents2KHR",
    /*  294 */ "vkCmdWriteAccelerationStructuresPropertiesKHR",
    /*  295 */ "vkCmdWriteAccelerationStructuresPropertiesNV",
    /*  296 */ "vkCmdWriteBufferMarker2AMD",
    /*  297 */ "vkCmdWriteBufferMarkerAMD",
    /*  298 */ "vkCmdWriteMicromapsPropertiesEXT",
    /*  299 */ "vkCmdWriteTimestamp",
    /*  300 */ "vkCmdWriteTimestamp2",
    /*  301 */ "vkCmdWriteTimestamp2KHR",
    /*  302 */ "vkCompileDeferredNV",
    /*  303 */ "vkConvertCooperativeVectorMatrixNV",
    /*  304 */ "vkCopyAccelerationStructureKHR",
    /*  305 */ "vkCopyAccelerationStructureToMemoryKHR",
    /*  306 */ "vkCopyImageToImage",
    /*  307 */ "vkCopyImageToImageEXT",
    /*  308 */ "vkCopyImageToMemory",
    /*  309 */ "vkCopyImageToMemoryEXT",
    /*  310 */ "vkCopyMemoryToAccelerationStructureKHR",
    /*  311 */ "vkCopyMemoryToImage",
    /*  312 */ "vkCopyMemoryToImageEXT",
    /*  313 */ "vkCopyMemoryToMicromapEXT",
    /*  314 */ "vkCopyMicromapEXT",
    /*  315 */ "vkCopyMicromapToMemoryEXT",
    /*  316 */ "vkCreateAccelerationStructureKHR",
    /*  317 */ "vkCreateAccelerationStructureNV",
    /*  318 */ "vkCreateAndroidSurfaceKHR",
    /*  319 */ "vkCreateBuffer",
    /*  320 */ "vkCreateBufferCollectionFUCHSIA",
    /*  321 */ "vkCreateBufferView",
    /*  322 */ "vkCreateCommandPool",
    /*  323 */ "vkCreateComputePipelines",
    /*  324 */ "vkCreateCuFunctionNVX",
    /*  325 */ "vkCreateCuModuleNVX",
    /*  326 */ "vkCreateCudaFunctionNV",
    /*  327 */ "vkCreateCudaModuleNV",
    /*  328 */ "vkCreateDataGraphPipelineSessionARM",
    /*  329 */ "vkCreateDataGraphPipelinesARM",
    /*  330 */ "vkCreateDebugReportCallbackEXT",
    /*  331 */ "vkCreateDebugUtilsMessengerEXT",
    /*  332 */ "vkCreateDeferredOperationKHR",
    /*  333 */ "vkCreateDescriptorPool",
    /*  334 */ "vkCreateDescriptorSetLayout",
    /*  335 */ "vkCreateDescriptorUpdateTemplate",
    /*  336 */ "vkCreateDescriptorUpdateTemplateKHR",
    /*  337 */ "vkCreateDevice",
    /*  338 */ "vkCreateDirectFBSurfaceEXT",
    /*  339 */ "vkCreateDisplayModeKHR",
    /*  340 */ "vkCreateDisplayPlaneSurfaceKHR",
    /*  341 */ "vkCreateEvent",
    /*  342 */ "vkCreateExecutionGraphPipelinesAMDX",
    /*  343 */ "vkCreateExternalComputeQueueNV",
    /*  344 */ "vkCreateFence",
    /*  345 */ "vkCreateFramebuffer",
    /*  346 */ "vkCreateGraphicsPipelines",
    /*  347 */ "vkCreateHeadlessSurfaceEXT",
    /*  348 */ "vkCreateIOSSurfaceMVK",
    /*  349 */ "vkCreateImage",
    /*  350 */ "vkCreateImagePipeSurfaceFUCHSIA",
    /*  351 */ "vkCreateImageView",
    /*  352 */ "vkCreateIndirectCommandsLayoutEXT",
    /*  353 */ "vkCreateIndirectCommandsLayoutNV",
    /*  354 */ "vkCreateIndirectExecutionSetEXT",
    /*  355 */ "vkCreateInstance",
    /*  356 */ "vkCreateMacOSSurfaceMVK",
    /*  357 */ "vkCreateMetalSurfaceEXT",
    /*  358 */ "vkCreateMicromapEXT",
    /*  359 */ "vkCreateOpticalFlowSessionNV",
    /*  360 */ "vkCreatePipelineBinariesKHR",
    /*  361 */ "vkCreatePipelineCache",
    /*  362 */ "vkCreatePipelineLayout",
    /*  363 */ "vkCreatePrivateDataSlot",
    /*  364 */ "vkCreatePrivateDataSlotEXT",
    /*  365 */ "vkCreateQueryPool",
    /*  366 */ "vkCreateRayTracingPipelinesKHR",
    /*  367 */ "vkCreateRayTracingPipelinesNV",
    /*  368 */ "vkCreateRenderPass",
    /*  369 */ "vkCreateRenderPass2",
    /*  370 */ "vkCreateRenderPass2KHR",
    /*  371 */ "vkCreateSampler",
    /*  372 */ "vkCreateSamplerYcbcrConversion",
    /*  373 */ "vkCreateSamplerYcbcrConversionKHR",
    /*  374 */ "vkCreateScreenSurfaceQNX",
    /*  375 */ "vkCreateSemaphore",
    /*  376 */ "vkCreateShaderModule",
    /*  377 */ "vkCreateShadersEXT",
    /*  378 */ "vkCreateSharedSwapchainsKHR",
    /*  379 */ "vkCreateStreamDescriptorSurfaceGGP",
    /*  380 */ "vkCreateSurfaceOHOS",
    /*  381 */ "vkCreateSwapchainKHR",
    /*  382 */ "vkCreateTensorARM",
    /*  383 */ "vkCreateTensorViewARM",
    /*  384 */ "vkCreateValidationCacheEXT",
    /*  385 */ "vkCreateViSurfaceNN",
    /*  386 */ "vkCreateVideoSessionKHR",
    /*  387 */ "vkCreateVideoSessionParametersKHR",
    /*  388 */ "vkCreateWaylandSurfaceKHR",
    /*  389 */ "vkCreateWin32SurfaceKHR",
    /*  390 */ "vkCreateXcbSurfaceKHR",
    /*  391 */ "vkCreateXlibSurfaceKHR",
    /*  392 */ "vkDebugMarkerSetObjectNameEXT",
    /*  393 */ "vkDebugMarkerSetObjectTagEXT",
    /*  394 */ "vkDebugReportMessageEXT",
    /*  395 */ "vkDeferredOperationJoinKHR",
    /*  396 */ "vkDestroyAccelerationStructureKHR",
    /*  397 */ "vkDestroyAccelerationStructureNV",
    /*  398 */ "vkDestroyBuffer",
    /*  399 */ "vkDestroyBufferCollectionFUCHSIA",
    /*  400 */ "vkDestroyBufferView",
    /*  401 */ "vkDestroyCommandPool",
    /*  402 */ "vkDestroyCuFunctionNVX",
    /*  403 */ "vkDestroyCuModuleNVX",
    /*  404 */ "vkDestroyCudaFunctionNV",
    /*  405 */ "vkDestroyCudaModuleNV",
    /*  406 */ "vkDestroyDataGraphPipelineSessionARM",
    /*  407 */ "vkDestroyDebugReportCallbackEXT",
    /*  408 */ "vkDestroyDebugUtilsMessengerEXT",
    /*  409 */ "vkDestroyDeferredOperationKHR",
    /*  410 */ "vkDestroyDescriptorPool",
    /*  411 */ "vkDestroyDescriptorSetLayout",
    /*  412 */ "vkDestroyDescriptorUpdateTemplate",
    /*  413 */ "vkDestroyDescriptorUpdateTemplateKHR",
    /*  414 */ "vkDestroyDevice",
    /*  415 */ "vkDestroyEvent",
    /*  416 */ "vkDestroyExternalComputeQueueNV",
    /*  417 */ "vkDestroyFence",
    /*  418 */ "vkDestroyFramebuffer",
    /*  419 */ "vkDestroyImage",
    /*  420 */ "vkDestroyImageView",
    /*  421 */ "vkDestroyIndirectCommandsLayoutEXT",
    /*  422 */ "vkDestroyIndirectCommandsLayoutNV",
    /*  423 */ "vkDestroyIndirectExecutionSetEXT",
    /*  424 */ "vkDestroyInstance",
    /*  425 */ "vkDestroyMicromapEXT",
    /*  426 */ "vkDestroyOpticalFlowSessionNV",
    /*  427 */ "vkDestroyPipeline",
    /*  428 */ "vkDestroyPipelineBinaryKHR",
    /*  429 */ "vkDestroyPipelineCache",
    /*  430 */ "vkDestroyPipelineLayout",
    /*  431 */ "vkDestroyPrivateDataSlot",
    /*  432 */ "vkDestroyPrivateDataSlotEXT",
    /*  433 */ "vkDestroyQueryPool",
    /*  434 */ "vkDestroyRenderPass",
    /*  435 */ "vkDestroySampler",
    /*  436 */ "vkDestroySamplerYcbcrConversion",
    /*  437 */ "vkDestroySamplerYcbcrConversionKHR",
    /*  438 */ "vkDestroySemaphore",
    /*  439 */ "vkDestroyShaderEXT",
    /*  440 */ "vkDestroyShaderModule",
    /*  441 */ "vkDestroySurfaceKHR",
    /*  442 */ "vkDestroySwapchainKHR",
    /*  443 */ "vkDestroyTensorARM",
    /*  444 */ "vkDestroyTensorViewARM",
    /*  445 */ "vkDestroyValidationCacheEXT",
    /*  446 */ "vkDestroyVideoSessionKHR",
    /*  447 */ "vkDestroyVideoSessionParametersKHR",
    /*  448 */ "vkDeviceWaitIdle",
    /*  449 */ "vkDisplayPowerControlEXT",
    /*  450 */ "vkEndCommandBuffer",
    /*  451 */ "vkEnumerateDeviceExtensionProperties",
    /*  452 */ "vkEnumerateDeviceLayerProperties",
    /*  453 */ "vkEnumerateInstanceExtensionProperties",
    /*  454 */ "vkEnumerateInstanceLayerProperties",
    /*  455 */ "vkEnumerateInstanceVersion",
    /*  456 */ "vkEnumeratePhysicalDeviceGroups",
    /*  457 */ "vkEnumeratePhysicalDeviceGroupsKHR",
    /*  458 */ "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR",
    /*  459 */ "vkEnumeratePhysicalDevices",
    /*  460 */ "vkExportMetalObjectsEXT",
    /*  461 */ "vkFlushMappedMemoryRanges",
    /*  462 */ "vkFreeCommandBuffers",
    /*  463 */ "vkFreeDescriptorSets",
    /*  464 */ "vkFreeMemory",
    /*  465 */ "vkGetAccelerationStructureBuildSizesKHR",
    /*  466 */ "vkGetAccelerationStructureDeviceAddressKHR",
    /*  467 */ "vkGetAccelerationStructureHandleNV",
    /*  468 */ "vkGetAccelerationStructureMemoryRequirementsNV",
    /*  469 */ "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT",
    /*  470 */ "vkGetAndroidHardwareBufferPropertiesANDROID",
    /*  471 */ "vkGetBufferCollectionPropertiesFUCHSIA",
    /*  472 */ "vkGetBufferDeviceAddress",
    /*  473 */ "vkGetBufferDeviceAddressEXT",
    /*  474 */ "vkGetBufferDeviceAddressKHR",
    /*  475 */ "vkGetBufferMemoryRequirements",
    /*  476 */ "vkGetBufferMemoryRequirements2",
    /*  477 */ "vkGetBufferMemoryRequirements2KHR",
    /*  478 */ "vkGetBufferOpaqueCaptureAddress",
    /*  479 */ "vkGetBufferOpaqueCaptureAddressKHR",
    /*  480 */ "vkGetBufferOpaqueCaptureDescriptorDataEXT",
    /*  481 */ "vkGetCalibratedTimestampsEXT",
    /*  482 */ "vkGetCalibratedTimestampsKHR",
    /*  483 */ "vkGetClusterAccelerationStructureBuildSizesNV",
    /*  484 */ "vkGetCudaModuleCacheNV",
    /*  485 */ "vkGetDataGraphPipelineAvailablePropertiesARM",
    /*  486 */ "vkGetDataGraphPipelinePropertiesARM",
    /*  487 */ "vkGetDataGraphPipelineSessionBindPointRequirementsARM",
    /*  488 */ "vkGetDataGraphPipelineSessionMemoryRequirementsARM",
    /*  489 */ "vkGetDeferredOperationMaxConcurrencyKHR",
    /*  490 */ "vkGetDeferredOperationResultKHR",
    /*  491 */ "vkGetDescriptorEXT",
    /*  492 */ "vkGetDescriptorSetHostMappingVALVE",
    /*  493 */ "vkGetDescriptorSetLayoutBindingOffsetEXT",
    /*  494 */ "vkGetDescriptorSetLayoutHostMappingInfoVALVE",
    /*  495 */ "vkGetDescriptorSetLayoutSizeEXT",
    /*  496 */ "vkGetDescriptorSetLayoutSupport",
    /*  497 */ "vkGetDescriptorSetLayoutSupportKHR",
    /*  498 */ "vkGetDeviceAccelerationStructureCompatibilityKHR",
    /*  499 */ "vkGetDeviceBufferMemoryRequirements",
    /*  500 */ "vkGetDeviceBufferMemoryRequirementsKHR",
    /*  501 */ "vkGetDeviceFaultInfoEXT",
    /*  502 */ "vkGetDeviceGroupPeerMemoryFeatures",
    /*  503 */ "vkGetDeviceGroupPeerMemoryFeaturesKHR",
    /*  504 */ "vkGetDeviceGroupPresentCapabilitiesKHR",
    /*  505 */ "vkGetDeviceGroupSurfacePresentModes2EXT",
    /*  506 */ "vkGetDeviceGroupSurfacePresentModesKHR",
    /*  507 */ "vkGetDeviceImageMemoryRequirements",
    /*  508 */ "vkGetDeviceImageMemoryRequirementsKHR",
    /*  509 */ "vkGetDeviceImageSparseMemoryRequirements",
    /*  510 */ "vkGetDeviceImageSparseMemoryRequirementsKHR",
    /*  511 */ "vkGetDeviceImageSubresourceLayout",
    /*  512 */ "vkGetDeviceImageSubresourceLayoutKHR",
    /*  513 */ "vkGetDeviceMemoryCommitment",
    /*  514 */ "vkGetDeviceMemoryOpaqueCaptureAddress",
    /*  515 */ "vkGetDeviceMemoryOpaqueCaptureAddressKHR",
    /*  516 */ "vkGetDeviceMicromapCompatibilityEXT",
    /*  517 */ "vkGetDeviceProcAddr",
    /*  518 */ "vkGetDeviceQueue",
    /*  519 */ "vkGetDeviceQueue2",
    /*  520 */ "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI",
    /*  521 */ "vkGetDeviceTensorMemoryRequirementsARM",
    /*  522 */ "vkGetDisplayModeProperties2KHR",
    /*  523 */ "vkGetDisplayModePropertiesKHR",
    /*  524 */ "vkGetDisplayPlaneCapabilities2KHR",
    /*  525 */ "vkGetDisplayPlaneCapabilitiesKHR",
    /*  526 */ "vkGetDisplayPlaneSupportedDisplaysKHR",
    /*  527 */ "vkGetDrmDisplayEXT",
    /*  528 */ "vkGetDynamicRenderingTilePropertiesQCOM",
    /*  529 */ "vkGetEncodedVideoSessionParametersKHR",
    /*  530 */ "vkGetEventStatus",
    /*  531 */ "vkGetExecutionGraphPipelineNodeIndexAMDX",
    /*  532 */ "vkGetExecutionGraphPipelineScratchSizeAMDX",
    /*  533 */ "vkGetExternalComputeQueueDataNV",
    /*  534 */ "vkGetFenceFdKHR",
    /*  535 */ "vkGetFenceStatus",
    /*  536 */ "vkGetFenceWin32HandleKHR",
    /*  537 */ "vkGetFramebufferTilePropertiesQCOM",
    /*  538 */ "vkGetGeneratedCommandsMemoryRequirementsEXT",
    /*  539 */ "vkGetGeneratedCommandsMemoryRequirementsNV",
    /*  540 */ "vkGetImageDrmFormatModifierPropertiesEXT",
    /*  541 */ "vkGetImageMemoryRequirements",
    /*  542 */ "vkGetImageMemoryRequirements2",
    /*  543 */ "vkGetImageMemoryRequirements2KHR",
    /*  544 */ "vkGetImageOpaqueCaptureDescriptorDataEXT",
    /*  545 */ "vkGetImageSparseMemoryRequirements",
    /*  546 */ "vkGetImageSparseMemoryRequirements2",
    /*  547 */ "vkGetImageSparseMemoryRequirements2KHR",
    /*  548 */ "vkGetImageSubresourceLayout",
    /*  549 */ "vkGetImageSubresourceLayout2",
    /*  550 */ "vkGetImageSubresourceLayout2EXT",
    /*  551 */ "vkGetImageSubresourceLayout2KHR",
    /*  552 */ "vkGetImageViewAddressNVX",
    /*  553 */ "vkGetImageViewHandle64NVX",
    /*  554 */ "vkGetImageViewHandleNVX",
    /*  555 */ "vkGetImageViewOpaqueCaptureDescriptorDataEXT",
    /*  556 */ "vkGetInstanceProcAddr",
    /*  557 */ "vkGetLatencyTimingsNV",
    /*  558 */ "vkGetMemoryAndroidHardwareBufferANDROID",
    /*  559 */ "vkGetMemoryFdKHR",
    /*  560 */ "vkGetMemoryFdPropertiesKHR",
    /*  561 */ "vkGetMemoryHostPointerPropertiesEXT",
    /*  562 */ "vkGetMemoryMetalHandleEXT",
    /*  563 */ "vkGetMemoryMetalHandlePropertiesEXT",
    /*  564 */ "vkGetMemoryRemoteAddressNV",
    /*  565 */ "vkGetMemoryWin32HandleKHR",
    /*  566 */ "vkGetMemoryWin32HandleNV",
    /*  567 */ "vkGetMemoryWin32HandlePropertiesKHR",
    /*  568 */ "vkGetMemoryZirconHandleFUCHSIA",
    /*  569 */ "vkGetMemoryZirconHandlePropertiesFUCHSIA",
    /*  570 */ "vkGetMicromapBuildSizesEXT",
    /*  571 */ "vkGetPartitionedAccelerationStructuresBuildSizesNV",
    /*  572 */ "vkGetPastPresentationTimingGOOGLE",
    /*  573 */ "vkGetPerformanceParameterINTEL",
    /*  574 */ "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT",
    /*  575 */ "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR",
    /*  576 */ "vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV",
    /*  577 */ "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR",
    /*  578 */ "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV",
    /*  579 */ "vkGetPhysicalDeviceCooperativeVectorPropertiesNV",
    /*  580 */ "vkGetPhysicalDeviceDirectFBPresentationSupportEXT",
    /*  581 */ "vkGetPhysicalDeviceDisplayPlaneProperties2KHR",
    /*  582 */ "vkGetPhysicalDeviceDisplayPlanePropertiesKHR",
    /*  583 */ "vkGetPhysicalDeviceDisplayProperties2KHR",
    /*  584 */ "vkGetPhysicalDeviceDisplayPropertiesKHR",
    /*  585 */ "vkGetPhysicalDeviceExternalBufferProperties",
    /*  586 */ "vkGetPhysicalDeviceExternalBufferPropertiesKHR",
    /*  587 */ "vkGetPhysicalDeviceExternalFenceProperties",
    /*  588 */ "vkGetPhysicalDeviceExternalFencePropertiesKHR",
    /*  589 */ "vkGetPhysicalDeviceExternalImageFormatPropertiesNV",
    /*  590 */ "vkGetPhysicalDeviceExternalSemaphoreProperties",
    /*  591 */ "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR",
    /*  592 */ "vkGetPhysicalDeviceExternalTensorPropertiesARM",
    /*  593 */ "vkGetPhysicalDeviceFeatures",
    /*  594 */ "vkGetPhysicalDeviceFeatures2",
    /*  595 */ "vkGetPhysicalDeviceFeatures2KHR",
    /*  596 */ "vkGetPhysicalDeviceFormatProperties",
    /*  597 */ "vkGetPhysicalDeviceFormatProperties2",
    /*  598 */ "vkGetPhysicalDeviceFormatProperties2KHR",
    /*  599 */ "vkGetPhysicalDeviceFragmentShadingRatesKHR",
    /*  600 */ "vkGetPhysicalDeviceImageFormatProperties",
    /*  601 */ "vkGetPhysicalDeviceImageFormatProperties2",
    /*  602 */ "vkGetPhysicalDeviceImageFormatProperties2KHR",
    /*  603 */ "vkGetPhysicalDeviceMemoryProperties",
    /*  604 */ "vkGetPhysicalDeviceMemoryProperties2",
    /*  605 */ "vkGetPhysicalDeviceMemoryProperties2KHR",
    /*  606 */ "vkGetPhysicalDeviceMultisamplePropertiesEXT",
    /*  607 */ "vkGetPhysicalDeviceOpticalFlowImageFormatsNV",
    /*  608 */ "vkGetPhysicalDevicePresentRectanglesKHR",
    /*  609 */ "vkGetPhysicalDeviceProperties",
    /*  610 */ "vkGetPhysicalDeviceProperties2",
    /*  611 */ "vkGetPhysicalDeviceProperties2KHR",
    /*  612 */ "vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM",
    /*  613 */ "vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM",
    /*  614 */ "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR",
    /*  615 */ "vkGetPhysicalDeviceQueueFamilyProperties",
    /*  616 */ "vkGetPhysicalDeviceQueueFamilyProperties2",
    /*  617 */ "vkGetPhysicalDeviceQueueFamilyProperties2KHR",
    /*  618 */ "vkGetPhysicalDeviceScreenPresentationSupportQNX",
    /*  619 */ "vkGetPhysicalDeviceSparseImageFormatProperties",
    /*  620 */ "vkGetPhysicalDeviceSparseImageFormatProperties2",
    /*  621 */ "vkGetPhysicalDeviceSparseImageFormatProperties2KHR",
    /*  622 */ "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV",
    /*  623 */ "vkGetPhysicalDeviceSurfaceCapabilities2EXT",
    /*  624 */ "vkGetPhysicalDeviceSurfaceCapabilities2KHR",
    /*  625 */ "vkGetPhysicalDeviceSurfaceCapabilitiesKHR",
    /*  626 */ "vkGetPhysicalDeviceSurfaceFormats2KHR",
    /*  627 */ "vkGetPhysicalDeviceSurfaceFormatsKHR",
    /*  628 */ "vkGetPhysicalDeviceSurfacePresentModes2EXT",
    /*  629 */ "vkGetPhysicalDeviceSurfacePresentModesKHR",
    /*  630 */ "vkGetPhysicalDeviceSurfaceSupportKHR",
    /*  631 */ "vkGetPhysicalDeviceToolProperties",
    /*  632 */ "vkGetPhysicalDeviceToolPropertiesEXT",
    /*  633 */ "vkGetPhysicalDeviceVideoCapabilitiesKHR",
    /*  634 */ "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR",
    /*  635 */ "vkGetPhysicalDeviceVideoFormatPropertiesKHR",
    /*  636 */ "vkGetPhysicalDeviceWaylandPresentationSupportKHR",
    /*  637 */ "vkGetPhysicalDeviceWin32PresentationSupportKHR",
    /*  638 */ "vkGetPhysicalDeviceXcbPresentationSupportKHR",
    /*  639 */ "vkGetPhysicalDeviceXlibPresentationSupportKHR",
    /*  640 */ "vkGetPipelineBinaryDataKHR",
    /*  641 */ "vkGetPipelineCacheData",
    /*  642 */ "vkGetPipelineExecutableInternalRepresentationsKHR",
    /*  643 */ "vkGetPipelineExecutablePropertiesKHR",
    /*  644 */ "vkGetPipelineExecutableStatisticsKHR",
    /*  645 */ "vkGetPipelineIndirectDeviceAddressNV",
    /*  646 */ "vkGetPipelineIndirectMemoryRequirementsNV",
    /*  647 */ "vkGetPipelineKeyKHR",
    /*  648 */ "vkGetPipelinePropertiesEXT",
    /*  649 */ "vkGetPrivateData",
    /*  650 */ "vkGetPrivateDataEXT",
    /*  651 */ "vkGetQueryPoolResults",
    /*  652 */ "vkGetQueueCheckpointData2NV",
    /*  653 */ "vkGetQueueCheckpointDataNV",
    /*  654 */ "vkGetRandROutputDisplayEXT",
    /*  655 */ "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR",
    /*  656 */ "vkGetRayTracingShaderGroupHandlesKHR",
    /*  657 */ "vkGetRayTracingShaderGroupHandlesNV",
    /*  658 */ "vkGetRayTracingShaderGroupStackSizeKHR",
    /*  659 */ "vkGetRefreshCycleDurationGOOGLE",
    /*  660 */ "vkGetRenderAreaGranularity",
    /*  661 */ "vkGetRenderingAreaGranularity",
    /*  662 */ "vkGetRenderingAreaGranularityKHR",
    /*  663 */ "vkGetSamplerOpaqueCaptureDescriptorDataEXT",
    /*  664 */ "vkGetScreenBufferPropertiesQNX",
    /*  665 */ "vkGetSemaphoreCounterValue",
    /*  666 */ "vkGetSemaphoreCounterValueKHR",
    /*  667 */ "vkGetSemaphoreFdKHR",
    /*  668 */ "vkGetSemaphoreWin32HandleKHR",
    /*  669 */ "vkGetSemaphoreZirconHandleFUCHSIA",
    /*  670 */ "vkGetShaderBinaryDataEXT",
    /*  671 */ "vkGetShaderInfoAMD",
    /*  672 */ "vkGetShaderModuleCreateInfoIdentifierEXT",
    /*  673 */ "vkGetShaderModuleIdentifierEXT",
    /*  674 */ "vkGetSwapchainCounterEXT",
    /*  675 */ "vkGetSwapchainImagesKHR",
    /*  676 */ "vkGetSwapchainStatusKHR",
    /*  677 */ "vkGetTensorMemoryRequirementsARM",
    /*  678 */ "vkGetTensorOpaqueCaptureDescriptorDataARM",
    /*  679 */ "vkGetTensorViewOpaqueCaptureDescriptorDataARM",
    /*  680 */ "vkGetValidationCacheDataEXT",
    /*  681 */ "vkGetVideoSessionMemoryRequirementsKHR",
    /*  682 */ "vkGetWinrtDisplayNV",
    /*  683 */ "vkImportFenceFdKHR",
    /*  684 */ "vkImportFenceWin32HandleKHR",
    /*  685 */ "vkImportSemaphoreFdKHR",
    /*  686 */ "vkImportSemaphoreWin32HandleKHR",
    /*  687 */ "vkImportSemaphoreZirconHandleFUCHSIA",
    /*  688 */ "vkInitializePerformanceApiINTEL",
    /*  689 */ "vkInvalidateMappedMemoryRanges",
    /*  690 */ "vkLatencySleepNV",
    /*  691 */ "vkMapMemory",
    /*  692 */ "vkMapMemory2",
    /*  693 */ "vkMapMemory2KHR",
    /*  694 */ "vkMergePipelineCaches",
    /*  695 */ "vkMergeValidationCachesEXT",
    /*  696 */ "vkQueueBeginDebugUtilsLabelEXT",
    /*  697 */ "vkQueueBindSparse",
    /*  698 */ "vkQueueEndDebugUtilsLabelEXT",
    /*  699 */ "vkQueueInsertDebugUtilsLabelEXT",
    /*  700 */ "vkQueueNotifyOutOfBandNV",
    /*  701 */ "vkQueuePresentKHR",
    /*  702 */ "vkQueueSetPerformanceConfigurationINTEL",
    /*  703 */ "vkQueueSubmit",
    /*  704 */ "vkQueueSubmit2",
    /*  705 */ "vkQueueSubmit2KHR",
    /*  706 */ "vkQueueWaitIdle",
    /*  707 */ "vkRegisterDeviceEventEXT",
    /*  708 */ "vkRegisterDisplayEventEXT",
    /*  709 */ "vkReleaseCapturedPipelineDataKHR",
    /*  710 */ "vkReleaseDisplayEXT",
    /*  711 */ "vkReleaseFullScreenExclusiveModeEXT",
    /*  712 */ "vkReleasePerformanceConfigurationINTEL",
    /*  713 */ "vkReleaseProfilingLockKHR",
    /*  714 */ "vkReleaseSwapchainImagesEXT",
    /*  715 */ "vkReleaseSwapchainImagesKHR",
    /*  716 */ "vkResetCommandBuffer",
    /*  717 */ "vkResetCommandPool",
    /*  718 */ "vkResetDescriptorPool",
    /*  719 */ "vkResetEvent",
    /*  720 */ "vkResetFences",
    /*  721 */ "vkResetQueryPool",
    /*  722 */ "vkResetQueryPoolEXT",
    /*  723 */ "vkSetBufferCollectionBufferConstraintsFUCHSIA",
    /*  724 */ "vkSetBufferCollectionImageConstraintsFUCHSIA",
    /*  725 */ "vkSetDebugUtilsObjectNameEXT",
    /*  726 */ "vkSetDebugUtilsObjectTagEXT",
    /*  727 */ "vkSetDeviceMemoryPriorityEXT",
    /*  728 */ "vkSetEvent",
    /*  729 */ "vkSetHdrMetadataEXT",
    /*  730 */ "vkSetLatencyMarkerNV",
    /*  731 */ "vkSetLatencySleepModeNV",
    /*  732 */ "vkSetLocalDimmingAMD",
    /*  733 */ "vkSetPrivateData",
    /*  734 */ "vkSetPrivateDataEXT",
    /*  735 */ "vkSignalSemaphore",
    /*  736 */ "vkSignalSemaphoreKHR",
    /*  737 */ "vkSubmitDebugUtilsMessageEXT",
    /*  738 */ "vkTransitionImageLayout",
    /*  739 */ "vkTransitionImageLayoutEXT",
    /*  740 */ "vkTrimCommandPool",
    /*  741 */ "vkTrimCommandPoolKHR",
    /*  742 */ "vkUninitializePerformanceApiINTEL",
    /*  743 */ "vkUnmapMemory",
    /*  744 */ "vkUnmapMemory2",
    /*  745 */ "vkUnmapMemory2KHR",
    /*  746 */ "vkUpdateDescriptorSetWithTemplate",
    /*  747 */ "vkUpdateDescriptorSetWithTemplateKHR",
    /*  748 */ "vkUpdateDescriptorSets",
    /*  749 */ "vkUpdateIndirectExecutionSetPipelineEXT",
    /*  750 */ "vkUpdateIndirectExecutionSetShaderEXT",
    /*  751 */ "vkUpdateVideoSessionParametersKHR",
    /*  752 */ "vkWaitForFences",
    /*  753 */ "vkWaitForPresent2KHR",
    /*  754 */ "vkWaitForPresentKHR",
    /*  755 */ "vkWaitSemaphores",
    /*  756 */ "vkWaitSemaphoresKHR",
    /*  757 */ "vkWriteAccelerationStructuresPropertiesKHR",
    /*  758 */ "vkWriteMicromapsPropertiesEXT"
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
    /*  422 */ 0x38c73d4ab66a4942  /* VK_VALVE_mutable_descriptor_type */
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
          18, /* vkBindImageMemory */
          29, /* vkCmdBeginQuery */
          31, /* vkCmdBeginRenderPass */
          41, /* vkCmdBindDescriptorSets */
          44, /* vkCmdBindIndexBuffer */
          48, /* vkCmdBindPipeline */
          54, /* vkCmdBindVertexBuffers */
          57, /* vkCmdBlitImage */
          66, /* vkCmdClearAttachments */
          67, /* vkCmdClearColorImage */
          68, /* vkCmdClearDepthStencilImage */
          74, /* vkCmdCopyBuffer */
          77, /* vkCmdCopyBufferToImage */
          80, /* vkCmdCopyImage */
          83, /* vkCmdCopyImageToBuffer */
          92, /* vkCmdCopyQueryPoolResults */
         102, /* vkCmdDispatch */
         109, /* vkCmdDispatchIndirect */
         111, /* vkCmdDraw */
         114, /* vkCmdDrawIndexed */
         115, /* vkCmdDrawIndexedIndirect */
         119, /* vkCmdDrawIndirect */
         136, /* vkCmdEndQuery */
         138, /* vkCmdEndRenderPass */
         146, /* vkCmdExecuteCommands */
         149, /* vkCmdFillBuffer */
         152, /* vkCmdNextSubpass */
         156, /* vkCmdPipelineBarrier */
         161, /* vkCmdPushConstants */
         172, /* vkCmdResetEvent */
         175, /* vkCmdResetQueryPool */
         176, /* vkCmdResolveImage */
         182, /* vkCmdSetBlendConstants */
         199, /* vkCmdSetDepthBias */
         203, /* vkCmdSetDepthBounds */
         223, /* vkCmdSetEvent */
         238, /* vkCmdSetLineWidth */
         264, /* vkCmdSetScissor */
         268, /* vkCmdSetStencilCompareMask */
         271, /* vkCmdSetStencilReference */
         274, /* vkCmdSetStencilWriteMask */
         277, /* vkCmdSetViewport */
         289, /* vkCmdUpdateBuffer */
         291, /* vkCmdWaitEvents */
         299, /* vkCmdWriteTimestamp */
         319, /* vkCreateBuffer */
         321, /* vkCreateBufferView */
         322, /* vkCreateCommandPool */
         323, /* vkCreateComputePipelines */
         333, /* vkCreateDescriptorPool */
         334, /* vkCreateDescriptorSetLayout */
         337, /* vkCreateDevice */
         341, /* vkCreateEvent */
         344, /* vkCreateFence */
         345, /* vkCreateFramebuffer */
         346, /* vkCreateGraphicsPipelines */
         349, /* vkCreateImage */
         351, /* vkCreateImageView */
         355, /* vkCreateInstance */
         361, /* vkCreatePipelineCache */
         362, /* vkCreatePipelineLayout */
         365, /* vkCreateQueryPool */
         368, /* vkCreateRenderPass */
         371, /* vkCreateSampler */
         375, /* vkCreateSemaphore */
         376, /* vkCreateShaderModule */
         398, /* vkDestroyBuffer */
         400, /* vkDestroyBufferView */
         401, /* vkDestroyCommandPool */
         410, /* vkDestroyDescriptorPool */
         411, /* vkDestroyDescriptorSetLayout */
         414, /* vkDestroyDevice */
         415, /* vkDestroyEvent */
         417, /* vkDestroyFence */
         418, /* vkDestroyFramebuffer */
         419, /* vkDestroyImage */
         420, /* vkDestroyImageView */
         424, /* vkDestroyInstance */
         427, /* vkDestroyPipeline */
         429, /* vkDestroyPipelineCache */
         430, /* vkDestroyPipelineLayout */
         433, /* vkDestroyQueryPool */
         434, /* vkDestroyRenderPass */
         435, /* vkDestroySampler */
         438, /* vkDestroySemaphore */
         440, /* vkDestroyShaderModule */
         448, /* vkDeviceWaitIdle */
         450, /* vkEndCommandBuffer */
         451, /* vkEnumerateDeviceExtensionProperties */
         452, /* vkEnumerateDeviceLayerProperties */
         453, /* vkEnumerateInstanceExtensionProperties */
         454, /* vkEnumerateInstanceLayerProperties */
         459, /* vkEnumeratePhysicalDevices */
         461, /* vkFlushMappedMemoryRanges */
         462, /* vkFreeCommandBuffers */
         463, /* vkFreeDescriptorSets */
         464, /* vkFreeMemory */
         475, /* vkGetBufferMemoryRequirements */
         513, /* vkGetDeviceMemoryCommitment */
         517, /* vkGetDeviceProcAddr */
         518, /* vkGetDeviceQueue */
         530, /* vkGetEventStatus */
         535, /* vkGetFenceStatus */
         541, /* vkGetImageMemoryRequirements */
         545, /* vkGetImageSparseMemoryRequirements */
         548, /* vkGetImageSubresourceLayout */
         556, /* vkGetInstanceProcAddr */
         593, /* vkGetPhysicalDeviceFeatures */
         596, /* vkGetPhysicalDeviceFormatProperties */
         600, /* vkGetPhysicalDeviceImageFormatProperties */
         603, /* vkGetPhysicalDeviceMemoryProperties */
         609, /* vkGetPhysicalDeviceProperties */
         615, /* vkGetPhysicalDeviceQueueFamilyProperties */
         619, /* vkGetPhysicalDeviceSparseImageFormatProperties */
         641, /* vkGetPipelineCacheData */
         651, /* vkGetQueryPoolResults */
         660, /* vkGetRenderAreaGranularity */
         689, /* vkInvalidateMappedMemoryRanges */
         691, /* vkMapMemory */
         694, /* vkMergePipelineCaches */
         697, /* vkQueueBindSparse */
         703, /* vkQueueSubmit */
         706, /* vkQueueWaitIdle */
         716, /* vkResetCommandBuffer */
         717, /* vkResetCommandPool */
         718, /* vkResetDescriptorPool */
         719, /* vkResetEvent */
         720, /* vkResetFences */
         728, /* vkSetEvent */
         743, /* vkUnmapMemory */
         748, /* vkUpdateDescriptorSets */
         752  /* vkWaitForFences */
    };
    if (!context->VERSION_1_0) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_VERSION_1_1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          15, /* vkBindBufferMemory2 */
          19, /* vkBindImageMemory2 */
         103, /* vkCmdDispatchBase */
         218, /* vkCmdSetDeviceMask */
         335, /* vkCreateDescriptorUpdateTemplate */
         372, /* vkCreateSamplerYcbcrConversion */
         412, /* vkDestroyDescriptorUpdateTemplate */
         436, /* vkDestroySamplerYcbcrConversion */
         455, /* vkEnumerateInstanceVersion */
         456, /* vkEnumeratePhysicalDeviceGroups */
         476, /* vkGetBufferMemoryRequirements2 */
         496, /* vkGetDescriptorSetLayoutSupport */
         502, /* vkGetDeviceGroupPeerMemoryFeatures */
         519, /* vkGetDeviceQueue2 */
         542, /* vkGetImageMemoryRequirements2 */
         546, /* vkGetImageSparseMemoryRequirements2 */
         585, /* vkGetPhysicalDeviceExternalBufferProperties */
         587, /* vkGetPhysicalDeviceExternalFenceProperties */
         590, /* vkGetPhysicalDeviceExternalSemaphoreProperties */
         594, /* vkGetPhysicalDeviceFeatures2 */
         597, /* vkGetPhysicalDeviceFormatProperties2 */
         601, /* vkGetPhysicalDeviceImageFormatProperties2 */
         604, /* vkGetPhysicalDeviceMemoryProperties2 */
         610, /* vkGetPhysicalDeviceProperties2 */
         616, /* vkGetPhysicalDeviceQueueFamilyProperties2 */
         620, /* vkGetPhysicalDeviceSparseImageFormatProperties2 */
         740, /* vkTrimCommandPool */
         746  /* vkUpdateDescriptorSetWithTemplate */
    };
    if (!context->VERSION_1_1) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_VERSION_1_2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          32, /* vkCmdBeginRenderPass2 */
         116, /* vkCmdDrawIndexedIndirectCount */
         121, /* vkCmdDrawIndirectCount */
         139, /* vkCmdEndRenderPass2 */
         153, /* vkCmdNextSubpass2 */
         369, /* vkCreateRenderPass2 */
         472, /* vkGetBufferDeviceAddress */
         478, /* vkGetBufferOpaqueCaptureAddress */
         514, /* vkGetDeviceMemoryOpaqueCaptureAddress */
         665, /* vkGetSemaphoreCounterValue */
         721, /* vkResetQueryPool */
         735, /* vkSignalSemaphore */
         755  /* vkWaitSemaphores */
    };
    if (!context->VERSION_1_2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_VERSION_1_3(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          34, /* vkCmdBeginRendering */
          55, /* vkCmdBindVertexBuffers2 */
          58, /* vkCmdBlitImage2 */
          75, /* vkCmdCopyBuffer2 */
          78, /* vkCmdCopyBufferToImage2 */
          81, /* vkCmdCopyImage2 */
          84, /* vkCmdCopyImageToBuffer2 */
         141, /* vkCmdEndRendering */
         157, /* vkCmdPipelineBarrier2 */
         173, /* vkCmdResetEvent2 */
         177, /* vkCmdResolveImage2 */
         197, /* vkCmdSetCullMode */
         201, /* vkCmdSetDepthBiasEnable */
         204, /* vkCmdSetDepthBoundsTestEnable */
         210, /* vkCmdSetDepthCompareOp */
         212, /* vkCmdSetDepthTestEnable */
         214, /* vkCmdSetDepthWriteEnable */
         224, /* vkCmdSetEvent2 */
         231, /* vkCmdSetFrontFace */
         246, /* vkCmdSetPrimitiveRestartEnable */
         248, /* vkCmdSetPrimitiveTopology */
         253, /* vkCmdSetRasterizerDiscardEnable */
         265, /* vkCmdSetScissorWithCount */
         269, /* vkCmdSetStencilOp */
         272, /* vkCmdSetStencilTestEnable */
         282, /* vkCmdSetViewportWithCount */
         292, /* vkCmdWaitEvents2 */
         300, /* vkCmdWriteTimestamp2 */
         363, /* vkCreatePrivateDataSlot */
         431, /* vkDestroyPrivateDataSlot */
         499, /* vkGetDeviceBufferMemoryRequirements */
         507, /* vkGetDeviceImageMemoryRequirements */
         509, /* vkGetDeviceImageSparseMemoryRequirements */
         631, /* vkGetPhysicalDeviceToolProperties */
         649, /* vkGetPrivateData */
         704, /* vkQueueSubmit2 */
         733  /* vkSetPrivateData */
    };
    if (!context->VERSION_1_3) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_VERSION_1_4(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          42, /* vkCmdBindDescriptorSets2 */
          45, /* vkCmdBindIndexBuffer2 */
         162, /* vkCmdPushConstants2 */
         164, /* vkCmdPushDescriptorSet */
         165, /* vkCmdPushDescriptorSet2 */
         168, /* vkCmdPushDescriptorSetWithTemplate */
         169, /* vkCmdPushDescriptorSetWithTemplate2 */
         234, /* vkCmdSetLineStipple */
         256, /* vkCmdSetRenderingAttachmentLocations */
         258, /* vkCmdSetRenderingInputAttachmentIndices */
         306, /* vkCopyImageToImage */
         308, /* vkCopyImageToMemory */
         311, /* vkCopyMemoryToImage */
         511, /* vkGetDeviceImageSubresourceLayout */
         549, /* vkGetImageSubresourceLayout2 */
         661, /* vkGetRenderingAreaGranularity */
         692, /* vkMapMemory2 */
         738, /* vkTransitionImageLayout */
         744  /* vkUnmapMemory2 */
    };
    if (!context->VERSION_1_4) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_ENABLE_BETA_EXTENSIONS)
static void glad_vk_load_VK_AMDX_shader_enqueue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         106, /* vkCmdDispatchGraphAMDX */
         107, /* vkCmdDispatchGraphIndirectAMDX */
         108, /* vkCmdDispatchGraphIndirectCountAMDX */
         150, /* vkCmdInitializeGraphScratchMemoryAMDX */
         342, /* vkCreateExecutionGraphPipelinesAMDX */
         531, /* vkGetExecutionGraphPipelineNodeIndexAMDX */
         532  /* vkGetExecutionGraphPipelineScratchSizeAMDX */
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
         296, /* vkCmdWriteBufferMarker2AMD */
         297  /* vkCmdWriteBufferMarkerAMD */
    };
    if (!context->AMD_buffer_marker) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_AMD_display_native_hdr(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         732  /* vkSetLocalDimmingAMD */
    };
    if (!context->AMD_display_native_hdr) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_AMD_draw_indirect_count(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         117, /* vkCmdDrawIndexedIndirectCountAMD */
         122  /* vkCmdDrawIndirectCountAMD */
    };
    if (!context->AMD_draw_indirect_count) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_AMD_shader_info(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         671  /* vkGetShaderInfoAMD */
    };
    if (!context->AMD_shader_info) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
static void glad_vk_load_VK_ANDROID_external_memory_android_hardware_buffer(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         470, /* vkGetAndroidHardwareBufferPropertiesANDROID */
         558  /* vkGetMemoryAndroidHardwareBufferANDROID */
    };
    if (!context->ANDROID_external_memory_android_hardware_buffer) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_ARM_data_graph(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          17, /* vkBindDataGraphPipelineSessionMemoryARM */
         105, /* vkCmdDispatchDataGraphARM */
         328, /* vkCreateDataGraphPipelineSessionARM */
         329, /* vkCreateDataGraphPipelinesARM */
         406, /* vkDestroyDataGraphPipelineSessionARM */
         485, /* vkGetDataGraphPipelineAvailablePropertiesARM */
         486, /* vkGetDataGraphPipelinePropertiesARM */
         487, /* vkGetDataGraphPipelineSessionBindPointRequirementsARM */
         488, /* vkGetDataGraphPipelineSessionMemoryRequirementsARM */
         612, /* vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM */
         613  /* vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM */
    };
    if (!context->ARM_data_graph) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_ARM_tensors(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          22, /* vkBindTensorMemoryARM */
          93, /* vkCmdCopyTensorARM */
         382, /* vkCreateTensorARM */
         383, /* vkCreateTensorViewARM */
         443, /* vkDestroyTensorARM */
         444, /* vkDestroyTensorViewARM */
         521, /* vkGetDeviceTensorMemoryRequirementsARM */
         592, /* vkGetPhysicalDeviceExternalTensorPropertiesARM */
         677, /* vkGetTensorMemoryRequirementsARM */
         678, /* vkGetTensorOpaqueCaptureDescriptorDataARM */
         679  /* vkGetTensorViewOpaqueCaptureDescriptorDataARM */
    };
    if (!context->ARM_tensors) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_acquire_drm_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           0, /* vkAcquireDrmDisplayEXT */
         527  /* vkGetDrmDisplayEXT */
    };
    if (!context->EXT_acquire_drm_display) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
static void glad_vk_load_VK_EXT_acquire_xlib_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           7, /* vkAcquireXlibDisplayEXT */
         654  /* vkGetRandROutputDisplayEXT */
    };
    if (!context->EXT_acquire_xlib_display) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_attachment_feedback_loop_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         181  /* vkCmdSetAttachmentFeedbackLoopEnableEXT */
    };
    if (!context->EXT_attachment_feedback_loop_dynamic_state) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_buffer_device_address(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         473  /* vkGetBufferDeviceAddressEXT */
    };
    if (!context->EXT_buffer_device_address) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_calibrated_timestamps(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         481, /* vkGetCalibratedTimestampsEXT */
         574  /* vkGetPhysicalDeviceCalibrateableTimeDomainsEXT */
    };
    if (!context->EXT_calibrated_timestamps) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_color_write_enable(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         188  /* vkCmdSetColorWriteEnableEXT */
    };
    if (!context->EXT_color_write_enable) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_conditional_rendering(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          26, /* vkCmdBeginConditionalRenderingEXT */
         133  /* vkCmdEndConditionalRenderingEXT */
    };
    if (!context->EXT_conditional_rendering) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_debug_marker(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          96, /* vkCmdDebugMarkerBeginEXT */
          97, /* vkCmdDebugMarkerEndEXT */
          98, /* vkCmdDebugMarkerInsertEXT */
         392, /* vkDebugMarkerSetObjectNameEXT */
         393  /* vkDebugMarkerSetObjectTagEXT */
    };
    if (!context->EXT_debug_marker) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_debug_report(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         330, /* vkCreateDebugReportCallbackEXT */
         394, /* vkDebugReportMessageEXT */
         407  /* vkDestroyDebugReportCallbackEXT */
    };
    if (!context->EXT_debug_report) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_debug_utils(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          27, /* vkCmdBeginDebugUtilsLabelEXT */
         134, /* vkCmdEndDebugUtilsLabelEXT */
         151, /* vkCmdInsertDebugUtilsLabelEXT */
         331, /* vkCreateDebugUtilsMessengerEXT */
         408, /* vkDestroyDebugUtilsMessengerEXT */
         696, /* vkQueueBeginDebugUtilsLabelEXT */
         698, /* vkQueueEndDebugUtilsLabelEXT */
         699, /* vkQueueInsertDebugUtilsLabelEXT */
         725, /* vkSetDebugUtilsObjectNameEXT */
         726, /* vkSetDebugUtilsObjectTagEXT */
         737  /* vkSubmitDebugUtilsMessageEXT */
    };
    if (!context->EXT_debug_utils) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_depth_bias_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         200  /* vkCmdSetDepthBias2EXT */
    };
    if (!context->EXT_depth_bias_control) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_depth_clamp_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         207  /* vkCmdSetDepthClampRangeEXT */
    };
    if (!context->EXT_depth_clamp_control) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_descriptor_buffer(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          39, /* vkCmdBindDescriptorBufferEmbeddedSamplersEXT */
          40, /* vkCmdBindDescriptorBuffersEXT */
         217, /* vkCmdSetDescriptorBufferOffsetsEXT */
         469, /* vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT */
         480, /* vkGetBufferOpaqueCaptureDescriptorDataEXT */
         491, /* vkGetDescriptorEXT */
         493, /* vkGetDescriptorSetLayoutBindingOffsetEXT */
         495, /* vkGetDescriptorSetLayoutSizeEXT */
         544, /* vkGetImageOpaqueCaptureDescriptorDataEXT */
         555, /* vkGetImageViewOpaqueCaptureDescriptorDataEXT */
         663  /* vkGetSamplerOpaqueCaptureDescriptorDataEXT */
    };
    if (!context->EXT_descriptor_buffer) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_device_fault(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         501  /* vkGetDeviceFaultInfoEXT */
    };
    if (!context->EXT_device_fault) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_device_generated_commands(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         147, /* vkCmdExecuteGeneratedCommandsEXT */
         159, /* vkCmdPreprocessGeneratedCommandsEXT */
         352, /* vkCreateIndirectCommandsLayoutEXT */
         354, /* vkCreateIndirectExecutionSetEXT */
         421, /* vkDestroyIndirectCommandsLayoutEXT */
         423, /* vkDestroyIndirectExecutionSetEXT */
         538, /* vkGetGeneratedCommandsMemoryRequirementsEXT */
         749, /* vkUpdateIndirectExecutionSetPipelineEXT */
         750  /* vkUpdateIndirectExecutionSetShaderEXT */
    };
    if (!context->EXT_device_generated_commands) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_direct_mode_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         710  /* vkReleaseDisplayEXT */
    };
    if (!context->EXT_direct_mode_display) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
static void glad_vk_load_VK_EXT_directfb_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         338, /* vkCreateDirectFBSurfaceEXT */
         580  /* vkGetPhysicalDeviceDirectFBPresentationSupportEXT */
    };
    if (!context->EXT_directfb_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_discard_rectangles(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         220, /* vkCmdSetDiscardRectangleEXT */
         221, /* vkCmdSetDiscardRectangleEnableEXT */
         222  /* vkCmdSetDiscardRectangleModeEXT */
    };
    if (!context->EXT_discard_rectangles) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_display_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         449, /* vkDisplayPowerControlEXT */
         674, /* vkGetSwapchainCounterEXT */
         707, /* vkRegisterDeviceEventEXT */
         708  /* vkRegisterDisplayEventEXT */
    };
    if (!context->EXT_display_control) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_display_surface_counter(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         623  /* vkGetPhysicalDeviceSurfaceCapabilities2EXT */
    };
    if (!context->EXT_display_surface_counter) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_extended_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          56, /* vkCmdBindVertexBuffers2EXT */
         198, /* vkCmdSetCullModeEXT */
         205, /* vkCmdSetDepthBoundsTestEnableEXT */
         211, /* vkCmdSetDepthCompareOpEXT */
         213, /* vkCmdSetDepthTestEnableEXT */
         215, /* vkCmdSetDepthWriteEnableEXT */
         232, /* vkCmdSetFrontFaceEXT */
         249, /* vkCmdSetPrimitiveTopologyEXT */
         266, /* vkCmdSetScissorWithCountEXT */
         270, /* vkCmdSetStencilOpEXT */
         273, /* vkCmdSetStencilTestEnableEXT */
         283  /* vkCmdSetViewportWithCountEXT */
    };
    if (!context->EXT_extended_dynamic_state) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_extended_dynamic_state2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         202, /* vkCmdSetDepthBiasEnableEXT */
         239, /* vkCmdSetLogicOpEXT */
         241, /* vkCmdSetPatchControlPointsEXT */
         247, /* vkCmdSetPrimitiveRestartEnableEXT */
         254  /* vkCmdSetRasterizerDiscardEnableEXT */
    };
    if (!context->EXT_extended_dynamic_state2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_extended_dynamic_state3(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         179, /* vkCmdSetAlphaToCoverageEnableEXT */
         180, /* vkCmdSetAlphaToOneEnableEXT */
         185, /* vkCmdSetColorBlendAdvancedEXT */
         186, /* vkCmdSetColorBlendEnableEXT */
         187, /* vkCmdSetColorBlendEquationEXT */
         189, /* vkCmdSetColorWriteMaskEXT */
         190, /* vkCmdSetConservativeRasterizationModeEXT */
         191, /* vkCmdSetCoverageModulationModeNV */
         192, /* vkCmdSetCoverageModulationTableEnableNV */
         193, /* vkCmdSetCoverageModulationTableNV */
         194, /* vkCmdSetCoverageReductionModeNV */
         195, /* vkCmdSetCoverageToColorEnableNV */
         196, /* vkCmdSetCoverageToColorLocationNV */
         206, /* vkCmdSetDepthClampEnableEXT */
         208, /* vkCmdSetDepthClipEnableEXT */
         209, /* vkCmdSetDepthClipNegativeOneToOneEXT */
         228, /* vkCmdSetExtraPrimitiveOverestimationSizeEXT */
         233, /* vkCmdSetLineRasterizationModeEXT */
         236, /* vkCmdSetLineStippleEnableEXT */
         240, /* vkCmdSetLogicOpEnableEXT */
         245, /* vkCmdSetPolygonModeEXT */
         250, /* vkCmdSetProvokingVertexModeEXT */
         251, /* vkCmdSetRasterizationSamplesEXT */
         252, /* vkCmdSetRasterizationStreamEXT */
         260, /* vkCmdSetRepresentativeFragmentTestEnableNV */
         262, /* vkCmdSetSampleLocationsEnableEXT */
         263, /* vkCmdSetSampleMaskEXT */
         267, /* vkCmdSetShadingRateImageEnableNV */
         275, /* vkCmdSetTessellationDomainOriginEXT */
         279, /* vkCmdSetViewportSwizzleNV */
         280  /* vkCmdSetViewportWScalingEnableNV */
    };
    if (!context->EXT_extended_dynamic_state3) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_external_memory_host(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         561  /* vkGetMemoryHostPointerPropertiesEXT */
    };
    if (!context->EXT_external_memory_host) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_METAL_EXT)
static void glad_vk_load_VK_EXT_external_memory_metal(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         562, /* vkGetMemoryMetalHandleEXT */
         563  /* vkGetMemoryMetalHandlePropertiesEXT */
    };
    if (!context->EXT_external_memory_metal) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_fragment_density_map_offset(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         142  /* vkCmdEndRendering2EXT */
    };
    if (!context->EXT_fragment_density_map_offset) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_EXT_full_screen_exclusive(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           1, /* vkAcquireFullScreenExclusiveModeEXT */
         505, /* vkGetDeviceGroupSurfacePresentModes2EXT */
         628, /* vkGetPhysicalDeviceSurfacePresentModes2EXT */
         711  /* vkReleaseFullScreenExclusiveModeEXT */
    };
    if (!context->EXT_full_screen_exclusive) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_hdr_metadata(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         729  /* vkSetHdrMetadataEXT */
    };
    if (!context->EXT_hdr_metadata) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_headless_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         347  /* vkCreateHeadlessSurfaceEXT */
    };
    if (!context->EXT_headless_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_host_image_copy(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         307, /* vkCopyImageToImageEXT */
         309, /* vkCopyImageToMemoryEXT */
         312, /* vkCopyMemoryToImageEXT */
         550, /* vkGetImageSubresourceLayout2EXT */
         739  /* vkTransitionImageLayoutEXT */
    };
    if (!context->EXT_host_image_copy) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_host_query_reset(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         722  /* vkResetQueryPoolEXT */
    };
    if (!context->EXT_host_query_reset) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_image_compression_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         550  /* vkGetImageSubresourceLayout2EXT */
    };
    if (!context->EXT_image_compression_control) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_image_drm_format_modifier(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         540  /* vkGetImageDrmFormatModifierPropertiesEXT */
    };
    if (!context->EXT_image_drm_format_modifier) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_line_rasterization(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         235  /* vkCmdSetLineStippleEXT */
    };
    if (!context->EXT_line_rasterization) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_mesh_shader(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         124, /* vkCmdDrawMeshTasksEXT */
         125, /* vkCmdDrawMeshTasksIndirectCountEXT */
         127  /* vkCmdDrawMeshTasksIndirectEXT */
    };
    if (!context->EXT_mesh_shader) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_METAL_EXT)
static void glad_vk_load_VK_EXT_metal_objects(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         460  /* vkExportMetalObjectsEXT */
    };
    if (!context->EXT_metal_objects) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_METAL_EXT)
static void glad_vk_load_VK_EXT_metal_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         357  /* vkCreateMetalSurfaceEXT */
    };
    if (!context->EXT_metal_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_EXT_multi_draw(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         130, /* vkCmdDrawMultiEXT */
         131  /* vkCmdDrawMultiIndexedEXT */
    };
    if (!context->EXT_multi_draw) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_opacity_micromap(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          25, /* vkBuildMicromapsEXT */
          64, /* vkCmdBuildMicromapsEXT */
          89, /* vkCmdCopyMemoryToMicromapEXT */
          90, /* vkCmdCopyMicromapEXT */
          91, /* vkCmdCopyMicromapToMemoryEXT */
         298, /* vkCmdWriteMicromapsPropertiesEXT */
         313, /* vkCopyMemoryToMicromapEXT */
         314, /* vkCopyMicromapEXT */
         315, /* vkCopyMicromapToMemoryEXT */
         358, /* vkCreateMicromapEXT */
         425, /* vkDestroyMicromapEXT */
         516, /* vkGetDeviceMicromapCompatibilityEXT */
         570, /* vkGetMicromapBuildSizesEXT */
         758  /* vkWriteMicromapsPropertiesEXT */
    };
    if (!context->EXT_opacity_micromap) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_pageable_device_local_memory(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         727  /* vkSetDeviceMemoryPriorityEXT */
    };
    if (!context->EXT_pageable_device_local_memory) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_pipeline_properties(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         648  /* vkGetPipelinePropertiesEXT */
    };
    if (!context->EXT_pipeline_properties) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_private_data(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         364, /* vkCreatePrivateDataSlotEXT */
         432, /* vkDestroyPrivateDataSlotEXT */
         650, /* vkGetPrivateDataEXT */
         734  /* vkSetPrivateDataEXT */
    };
    if (!context->EXT_private_data) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_sample_locations(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         261, /* vkCmdSetSampleLocationsEXT */
         606  /* vkGetPhysicalDeviceMultisamplePropertiesEXT */
    };
    if (!context->EXT_sample_locations) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_shader_module_identifier(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         672, /* vkGetShaderModuleCreateInfoIdentifierEXT */
         673  /* vkGetShaderModuleIdentifierEXT */
    };
    if (!context->EXT_shader_module_identifier) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_shader_object(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          50, /* vkCmdBindShadersEXT */
          56, /* vkCmdBindVertexBuffers2EXT */
         179, /* vkCmdSetAlphaToCoverageEnableEXT */
         180, /* vkCmdSetAlphaToOneEnableEXT */
         185, /* vkCmdSetColorBlendAdvancedEXT */
         186, /* vkCmdSetColorBlendEnableEXT */
         187, /* vkCmdSetColorBlendEquationEXT */
         189, /* vkCmdSetColorWriteMaskEXT */
         190, /* vkCmdSetConservativeRasterizationModeEXT */
         191, /* vkCmdSetCoverageModulationModeNV */
         192, /* vkCmdSetCoverageModulationTableEnableNV */
         193, /* vkCmdSetCoverageModulationTableNV */
         194, /* vkCmdSetCoverageReductionModeNV */
         195, /* vkCmdSetCoverageToColorEnableNV */
         196, /* vkCmdSetCoverageToColorLocationNV */
         198, /* vkCmdSetCullModeEXT */
         202, /* vkCmdSetDepthBiasEnableEXT */
         205, /* vkCmdSetDepthBoundsTestEnableEXT */
         206, /* vkCmdSetDepthClampEnableEXT */
         207, /* vkCmdSetDepthClampRangeEXT */
         208, /* vkCmdSetDepthClipEnableEXT */
         209, /* vkCmdSetDepthClipNegativeOneToOneEXT */
         211, /* vkCmdSetDepthCompareOpEXT */
         213, /* vkCmdSetDepthTestEnableEXT */
         215, /* vkCmdSetDepthWriteEnableEXT */
         228, /* vkCmdSetExtraPrimitiveOverestimationSizeEXT */
         232, /* vkCmdSetFrontFaceEXT */
         233, /* vkCmdSetLineRasterizationModeEXT */
         236, /* vkCmdSetLineStippleEnableEXT */
         239, /* vkCmdSetLogicOpEXT */
         240, /* vkCmdSetLogicOpEnableEXT */
         241, /* vkCmdSetPatchControlPointsEXT */
         245, /* vkCmdSetPolygonModeEXT */
         247, /* vkCmdSetPrimitiveRestartEnableEXT */
         249, /* vkCmdSetPrimitiveTopologyEXT */
         250, /* vkCmdSetProvokingVertexModeEXT */
         251, /* vkCmdSetRasterizationSamplesEXT */
         252, /* vkCmdSetRasterizationStreamEXT */
         254, /* vkCmdSetRasterizerDiscardEnableEXT */
         260, /* vkCmdSetRepresentativeFragmentTestEnableNV */
         262, /* vkCmdSetSampleLocationsEnableEXT */
         263, /* vkCmdSetSampleMaskEXT */
         266, /* vkCmdSetScissorWithCountEXT */
         267, /* vkCmdSetShadingRateImageEnableNV */
         270, /* vkCmdSetStencilOpEXT */
         273, /* vkCmdSetStencilTestEnableEXT */
         275, /* vkCmdSetTessellationDomainOriginEXT */
         276, /* vkCmdSetVertexInputEXT */
         279, /* vkCmdSetViewportSwizzleNV */
         280, /* vkCmdSetViewportWScalingEnableNV */
         283, /* vkCmdSetViewportWithCountEXT */
         377, /* vkCreateShadersEXT */
         439, /* vkDestroyShaderEXT */
         670  /* vkGetShaderBinaryDataEXT */
    };
    if (!context->EXT_shader_object) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_swapchain_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         714  /* vkReleaseSwapchainImagesEXT */
    };
    if (!context->EXT_swapchain_maintenance1) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_tooling_info(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         632  /* vkGetPhysicalDeviceToolPropertiesEXT */
    };
    if (!context->EXT_tooling_info) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_transform_feedback(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          30, /* vkCmdBeginQueryIndexedEXT */
          36, /* vkCmdBeginTransformFeedbackEXT */
          53, /* vkCmdBindTransformFeedbackBuffersEXT */
         120, /* vkCmdDrawIndirectByteCountEXT */
         137, /* vkCmdEndQueryIndexedEXT */
         144  /* vkCmdEndTransformFeedbackEXT */
    };
    if (!context->EXT_transform_feedback) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_validation_cache(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         384, /* vkCreateValidationCacheEXT */
         445, /* vkDestroyValidationCacheEXT */
         680, /* vkGetValidationCacheDataEXT */
         695  /* vkMergeValidationCachesEXT */
    };
    if (!context->EXT_validation_cache) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_EXT_vertex_input_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         276  /* vkCmdSetVertexInputEXT */
    };
    if (!context->EXT_vertex_input_dynamic_state) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_buffer_collection(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         320, /* vkCreateBufferCollectionFUCHSIA */
         399, /* vkDestroyBufferCollectionFUCHSIA */
         471, /* vkGetBufferCollectionPropertiesFUCHSIA */
         723, /* vkSetBufferCollectionBufferConstraintsFUCHSIA */
         724  /* vkSetBufferCollectionImageConstraintsFUCHSIA */
    };
    if (!context->FUCHSIA_buffer_collection) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_external_memory(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         568, /* vkGetMemoryZirconHandleFUCHSIA */
         569  /* vkGetMemoryZirconHandlePropertiesFUCHSIA */
    };
    if (!context->FUCHSIA_external_memory) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_external_semaphore(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         669, /* vkGetSemaphoreZirconHandleFUCHSIA */
         687  /* vkImportSemaphoreZirconHandleFUCHSIA */
    };
    if (!context->FUCHSIA_external_semaphore) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_imagepipe_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         350  /* vkCreateImagePipeSurfaceFUCHSIA */
    };
    if (!context->FUCHSIA_imagepipe_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_GGP)
static void glad_vk_load_VK_GGP_stream_descriptor_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         379  /* vkCreateStreamDescriptorSurfaceGGP */
    };
    if (!context->GGP_stream_descriptor_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_GOOGLE_display_timing(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         572, /* vkGetPastPresentationTimingGOOGLE */
         659  /* vkGetRefreshCycleDurationGOOGLE */
    };
    if (!context->GOOGLE_display_timing) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_HUAWEI_cluster_culling_shader(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         112, /* vkCmdDrawClusterHUAWEI */
         113  /* vkCmdDrawClusterIndirectHUAWEI */
    };
    if (!context->HUAWEI_cluster_culling_shader) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_HUAWEI_invocation_mask(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          47  /* vkCmdBindInvocationMaskHUAWEI */
    };
    if (!context->HUAWEI_invocation_mask) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_HUAWEI_subpass_shading(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         284, /* vkCmdSubpassShadingHUAWEI */
         520  /* vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI */
    };
    if (!context->HUAWEI_subpass_shading) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_INTEL_performance_query(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           4, /* vkAcquirePerformanceConfigurationINTEL */
         242, /* vkCmdSetPerformanceMarkerINTEL */
         243, /* vkCmdSetPerformanceOverrideINTEL */
         244, /* vkCmdSetPerformanceStreamMarkerINTEL */
         573, /* vkGetPerformanceParameterINTEL */
         688, /* vkInitializePerformanceApiINTEL */
         702, /* vkQueueSetPerformanceConfigurationINTEL */
         712, /* vkReleasePerformanceConfigurationINTEL */
         742  /* vkUninitializePerformanceApiINTEL */
    };
    if (!context->INTEL_performance_query) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_acceleration_structure(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          24, /* vkBuildAccelerationStructuresKHR */
          61, /* vkCmdBuildAccelerationStructuresIndirectKHR */
          62, /* vkCmdBuildAccelerationStructuresKHR */
          71, /* vkCmdCopyAccelerationStructureKHR */
          73, /* vkCmdCopyAccelerationStructureToMemoryKHR */
          87, /* vkCmdCopyMemoryToAccelerationStructureKHR */
         294, /* vkCmdWriteAccelerationStructuresPropertiesKHR */
         304, /* vkCopyAccelerationStructureKHR */
         305, /* vkCopyAccelerationStructureToMemoryKHR */
         310, /* vkCopyMemoryToAccelerationStructureKHR */
         316, /* vkCreateAccelerationStructureKHR */
         396, /* vkDestroyAccelerationStructureKHR */
         465, /* vkGetAccelerationStructureBuildSizesKHR */
         466, /* vkGetAccelerationStructureDeviceAddressKHR */
         498, /* vkGetDeviceAccelerationStructureCompatibilityKHR */
         757  /* vkWriteAccelerationStructuresPropertiesKHR */
    };
    if (!context->KHR_acceleration_structure) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
static void glad_vk_load_VK_KHR_android_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         318  /* vkCreateAndroidSurfaceKHR */
    };
    if (!context->KHR_android_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_KHR_bind_memory2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          16, /* vkBindBufferMemory2KHR */
          20  /* vkBindImageMemory2KHR */
    };
    if (!context->KHR_bind_memory2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_buffer_device_address(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         474, /* vkGetBufferDeviceAddressKHR */
         479, /* vkGetBufferOpaqueCaptureAddressKHR */
         515  /* vkGetDeviceMemoryOpaqueCaptureAddressKHR */
    };
    if (!context->KHR_buffer_device_address) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_calibrated_timestamps(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         482, /* vkGetCalibratedTimestampsKHR */
         575  /* vkGetPhysicalDeviceCalibrateableTimeDomainsKHR */
    };
    if (!context->KHR_calibrated_timestamps) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_cooperative_matrix(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         577  /* vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR */
    };
    if (!context->KHR_cooperative_matrix) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_copy_commands2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          59, /* vkCmdBlitImage2KHR */
          76, /* vkCmdCopyBuffer2KHR */
          79, /* vkCmdCopyBufferToImage2KHR */
          82, /* vkCmdCopyImage2KHR */
          85, /* vkCmdCopyImageToBuffer2KHR */
         178  /* vkCmdResolveImage2KHR */
    };
    if (!context->KHR_copy_commands2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_create_renderpass2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          33, /* vkCmdBeginRenderPass2KHR */
         140, /* vkCmdEndRenderPass2KHR */
         154, /* vkCmdNextSubpass2KHR */
         370  /* vkCreateRenderPass2KHR */
    };
    if (!context->KHR_create_renderpass2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_deferred_host_operations(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         332, /* vkCreateDeferredOperationKHR */
         395, /* vkDeferredOperationJoinKHR */
         409, /* vkDestroyDeferredOperationKHR */
         489, /* vkGetDeferredOperationMaxConcurrencyKHR */
         490  /* vkGetDeferredOperationResultKHR */
    };
    if (!context->KHR_deferred_host_operations) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_descriptor_update_template(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         171, /* vkCmdPushDescriptorSetWithTemplateKHR */
         336, /* vkCreateDescriptorUpdateTemplateKHR */
         413, /* vkDestroyDescriptorUpdateTemplateKHR */
         747  /* vkUpdateDescriptorSetWithTemplateKHR */
    };
    if (!context->KHR_descriptor_update_template) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_device_group(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           2, /* vkAcquireNextImage2KHR */
         104, /* vkCmdDispatchBaseKHR */
         219, /* vkCmdSetDeviceMaskKHR */
         503, /* vkGetDeviceGroupPeerMemoryFeaturesKHR */
         504, /* vkGetDeviceGroupPresentCapabilitiesKHR */
         506, /* vkGetDeviceGroupSurfacePresentModesKHR */
         608  /* vkGetPhysicalDevicePresentRectanglesKHR */
    };
    if (!context->KHR_device_group) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_device_group_creation(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         457  /* vkEnumeratePhysicalDeviceGroupsKHR */
    };
    if (!context->KHR_device_group_creation) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         339, /* vkCreateDisplayModeKHR */
         340, /* vkCreateDisplayPlaneSurfaceKHR */
         523, /* vkGetDisplayModePropertiesKHR */
         525, /* vkGetDisplayPlaneCapabilitiesKHR */
         526, /* vkGetDisplayPlaneSupportedDisplaysKHR */
         582, /* vkGetPhysicalDeviceDisplayPlanePropertiesKHR */
         584  /* vkGetPhysicalDeviceDisplayPropertiesKHR */
    };
    if (!context->KHR_display) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_display_swapchain(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         378  /* vkCreateSharedSwapchainsKHR */
    };
    if (!context->KHR_display_swapchain) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_draw_indirect_count(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         118, /* vkCmdDrawIndexedIndirectCountKHR */
         123  /* vkCmdDrawIndirectCountKHR */
    };
    if (!context->KHR_draw_indirect_count) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_dynamic_rendering(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          35, /* vkCmdBeginRenderingKHR */
         143  /* vkCmdEndRenderingKHR */
    };
    if (!context->KHR_dynamic_rendering) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_dynamic_rendering_local_read(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         257, /* vkCmdSetRenderingAttachmentLocationsKHR */
         259  /* vkCmdSetRenderingInputAttachmentIndicesKHR */
    };
    if (!context->KHR_dynamic_rendering_local_read) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_external_fence_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         588  /* vkGetPhysicalDeviceExternalFencePropertiesKHR */
    };
    if (!context->KHR_external_fence_capabilities) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_external_fence_fd(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         534, /* vkGetFenceFdKHR */
         683  /* vkImportFenceFdKHR */
    };
    if (!context->KHR_external_fence_fd) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_external_fence_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         536, /* vkGetFenceWin32HandleKHR */
         684  /* vkImportFenceWin32HandleKHR */
    };
    if (!context->KHR_external_fence_win32) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_KHR_external_memory_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         586  /* vkGetPhysicalDeviceExternalBufferPropertiesKHR */
    };
    if (!context->KHR_external_memory_capabilities) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_external_memory_fd(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         559, /* vkGetMemoryFdKHR */
         560  /* vkGetMemoryFdPropertiesKHR */
    };
    if (!context->KHR_external_memory_fd) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_external_memory_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         565, /* vkGetMemoryWin32HandleKHR */
         567  /* vkGetMemoryWin32HandlePropertiesKHR */
    };
    if (!context->KHR_external_memory_win32) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_KHR_external_semaphore_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         591  /* vkGetPhysicalDeviceExternalSemaphorePropertiesKHR */
    };
    if (!context->KHR_external_semaphore_capabilities) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_external_semaphore_fd(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         667, /* vkGetSemaphoreFdKHR */
         685  /* vkImportSemaphoreFdKHR */
    };
    if (!context->KHR_external_semaphore_fd) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_external_semaphore_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         668, /* vkGetSemaphoreWin32HandleKHR */
         686  /* vkImportSemaphoreWin32HandleKHR */
    };
    if (!context->KHR_external_semaphore_win32) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_KHR_fragment_shading_rate(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         230, /* vkCmdSetFragmentShadingRateKHR */
         599  /* vkGetPhysicalDeviceFragmentShadingRatesKHR */
    };
    if (!context->KHR_fragment_shading_rate) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_get_display_properties2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         522, /* vkGetDisplayModeProperties2KHR */
         524, /* vkGetDisplayPlaneCapabilities2KHR */
         581, /* vkGetPhysicalDeviceDisplayPlaneProperties2KHR */
         583  /* vkGetPhysicalDeviceDisplayProperties2KHR */
    };
    if (!context->KHR_get_display_properties2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_get_memory_requirements2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         477, /* vkGetBufferMemoryRequirements2KHR */
         543, /* vkGetImageMemoryRequirements2KHR */
         547  /* vkGetImageSparseMemoryRequirements2KHR */
    };
    if (!context->KHR_get_memory_requirements2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_get_physical_device_properties2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         595, /* vkGetPhysicalDeviceFeatures2KHR */
         598, /* vkGetPhysicalDeviceFormatProperties2KHR */
         602, /* vkGetPhysicalDeviceImageFormatProperties2KHR */
         605, /* vkGetPhysicalDeviceMemoryProperties2KHR */
         611, /* vkGetPhysicalDeviceProperties2KHR */
         617, /* vkGetPhysicalDeviceQueueFamilyProperties2KHR */
         621  /* vkGetPhysicalDeviceSparseImageFormatProperties2KHR */
    };
    if (!context->KHR_get_physical_device_properties2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_get_surface_capabilities2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         624, /* vkGetPhysicalDeviceSurfaceCapabilities2KHR */
         626  /* vkGetPhysicalDeviceSurfaceFormats2KHR */
    };
    if (!context->KHR_get_surface_capabilities2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_line_rasterization(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         237  /* vkCmdSetLineStippleKHR */
    };
    if (!context->KHR_line_rasterization) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         741  /* vkTrimCommandPoolKHR */
    };
    if (!context->KHR_maintenance1) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_maintenance3(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         497  /* vkGetDescriptorSetLayoutSupportKHR */
    };
    if (!context->KHR_maintenance3) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_maintenance4(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         500, /* vkGetDeviceBufferMemoryRequirementsKHR */
         508, /* vkGetDeviceImageMemoryRequirementsKHR */
         510  /* vkGetDeviceImageSparseMemoryRequirementsKHR */
    };
    if (!context->KHR_maintenance4) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_maintenance5(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          46, /* vkCmdBindIndexBuffer2KHR */
         512, /* vkGetDeviceImageSubresourceLayoutKHR */
         551, /* vkGetImageSubresourceLayout2KHR */
         662  /* vkGetRenderingAreaGranularityKHR */
    };
    if (!context->KHR_maintenance5) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_maintenance6(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          38, /* vkCmdBindDescriptorBufferEmbeddedSamplers2EXT */
          43, /* vkCmdBindDescriptorSets2KHR */
         163, /* vkCmdPushConstants2KHR */
         166, /* vkCmdPushDescriptorSet2KHR */
         170, /* vkCmdPushDescriptorSetWithTemplate2KHR */
         216  /* vkCmdSetDescriptorBufferOffsets2EXT */
    };
    if (!context->KHR_maintenance6) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_map_memory2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         693, /* vkMapMemory2KHR */
         745  /* vkUnmapMemory2KHR */
    };
    if (!context->KHR_map_memory2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_performance_query(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           5, /* vkAcquireProfilingLockKHR */
         458, /* vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR */
         614, /* vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR */
         713  /* vkReleaseProfilingLockKHR */
    };
    if (!context->KHR_performance_query) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_pipeline_binary(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         360, /* vkCreatePipelineBinariesKHR */
         428, /* vkDestroyPipelineBinaryKHR */
         640, /* vkGetPipelineBinaryDataKHR */
         647, /* vkGetPipelineKeyKHR */
         709  /* vkReleaseCapturedPipelineDataKHR */
    };
    if (!context->KHR_pipeline_binary) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_pipeline_executable_properties(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         642, /* vkGetPipelineExecutableInternalRepresentationsKHR */
         643, /* vkGetPipelineExecutablePropertiesKHR */
         644  /* vkGetPipelineExecutableStatisticsKHR */
    };
    if (!context->KHR_pipeline_executable_properties) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_present_wait(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         754  /* vkWaitForPresentKHR */
    };
    if (!context->KHR_present_wait) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_present_wait2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         753  /* vkWaitForPresent2KHR */
    };
    if (!context->KHR_present_wait2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_push_descriptor(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         167, /* vkCmdPushDescriptorSetKHR */
         171  /* vkCmdPushDescriptorSetWithTemplateKHR */
    };
    if (!context->KHR_push_descriptor) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_ray_tracing_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         285  /* vkCmdTraceRaysIndirect2KHR */
    };
    if (!context->KHR_ray_tracing_maintenance1) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_ray_tracing_pipeline(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         255, /* vkCmdSetRayTracingPipelineStackSizeKHR */
         286, /* vkCmdTraceRaysIndirectKHR */
         287, /* vkCmdTraceRaysKHR */
         366, /* vkCreateRayTracingPipelinesKHR */
         655, /* vkGetRayTracingCaptureReplayShaderGroupHandlesKHR */
         656, /* vkGetRayTracingShaderGroupHandlesKHR */
         658  /* vkGetRayTracingShaderGroupStackSizeKHR */
    };
    if (!context->KHR_ray_tracing_pipeline) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_sampler_ycbcr_conversion(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         373, /* vkCreateSamplerYcbcrConversionKHR */
         437  /* vkDestroySamplerYcbcrConversionKHR */
    };
    if (!context->KHR_sampler_ycbcr_conversion) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_shared_presentable_image(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         676  /* vkGetSwapchainStatusKHR */
    };
    if (!context->KHR_shared_presentable_image) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         441, /* vkDestroySurfaceKHR */
         625, /* vkGetPhysicalDeviceSurfaceCapabilitiesKHR */
         627, /* vkGetPhysicalDeviceSurfaceFormatsKHR */
         629, /* vkGetPhysicalDeviceSurfacePresentModesKHR */
         630  /* vkGetPhysicalDeviceSurfaceSupportKHR */
    };
    if (!context->KHR_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_swapchain(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           2, /* vkAcquireNextImage2KHR */
           3, /* vkAcquireNextImageKHR */
         381, /* vkCreateSwapchainKHR */
         442, /* vkDestroySwapchainKHR */
         504, /* vkGetDeviceGroupPresentCapabilitiesKHR */
         506, /* vkGetDeviceGroupSurfacePresentModesKHR */
         608, /* vkGetPhysicalDevicePresentRectanglesKHR */
         675, /* vkGetSwapchainImagesKHR */
         701  /* vkQueuePresentKHR */
    };
    if (!context->KHR_swapchain) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_swapchain_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         715  /* vkReleaseSwapchainImagesKHR */
    };
    if (!context->KHR_swapchain_maintenance1) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_synchronization2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         158, /* vkCmdPipelineBarrier2KHR */
         174, /* vkCmdResetEvent2KHR */
         225, /* vkCmdSetEvent2KHR */
         293, /* vkCmdWaitEvents2KHR */
         301, /* vkCmdWriteTimestamp2KHR */
         705  /* vkQueueSubmit2KHR */
    };
    if (!context->KHR_synchronization2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_timeline_semaphore(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         666, /* vkGetSemaphoreCounterValueKHR */
         736, /* vkSignalSemaphoreKHR */
         756  /* vkWaitSemaphoresKHR */
    };
    if (!context->KHR_timeline_semaphore) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_video_decode_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          99  /* vkCmdDecodeVideoKHR */
    };
    if (!context->KHR_video_decode_queue) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_video_encode_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         132, /* vkCmdEncodeVideoKHR */
         529, /* vkGetEncodedVideoSessionParametersKHR */
         634  /* vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR */
    };
    if (!context->KHR_video_encode_queue) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_KHR_video_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          23, /* vkBindVideoSessionMemoryKHR */
          37, /* vkCmdBeginVideoCodingKHR */
          69, /* vkCmdControlVideoCodingKHR */
         145, /* vkCmdEndVideoCodingKHR */
         386, /* vkCreateVideoSessionKHR */
         387, /* vkCreateVideoSessionParametersKHR */
         446, /* vkDestroyVideoSessionKHR */
         447, /* vkDestroyVideoSessionParametersKHR */
         633, /* vkGetPhysicalDeviceVideoCapabilitiesKHR */
         635, /* vkGetPhysicalDeviceVideoFormatPropertiesKHR */
         681, /* vkGetVideoSessionMemoryRequirementsKHR */
         751  /* vkUpdateVideoSessionParametersKHR */
    };
    if (!context->KHR_video_queue) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
static void glad_vk_load_VK_KHR_wayland_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         388, /* vkCreateWaylandSurfaceKHR */
         636  /* vkGetPhysicalDeviceWaylandPresentationSupportKHR */
    };
    if (!context->KHR_wayland_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_win32_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         389, /* vkCreateWin32SurfaceKHR */
         637  /* vkGetPhysicalDeviceWin32PresentationSupportKHR */
    };
    if (!context->KHR_win32_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
static void glad_vk_load_VK_KHR_xcb_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         390, /* vkCreateXcbSurfaceKHR */
         638  /* vkGetPhysicalDeviceXcbPresentationSupportKHR */
    };
    if (!context->KHR_xcb_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)
static void glad_vk_load_VK_KHR_xlib_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         391, /* vkCreateXlibSurfaceKHR */
         639  /* vkGetPhysicalDeviceXlibPresentationSupportKHR */
    };
    if (!context->KHR_xlib_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_IOS_MVK)
static void glad_vk_load_VK_MVK_ios_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         348  /* vkCreateIOSSurfaceMVK */
    };
    if (!context->MVK_ios_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_MACOS_MVK)
static void glad_vk_load_VK_MVK_macos_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         356  /* vkCreateMacOSSurfaceMVK */
    };
    if (!context->MVK_macos_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_VI_NN)
static void glad_vk_load_VK_NN_vi_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         385  /* vkCreateViSurfaceNN */
    };
    if (!context->NN_vi_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_NVX_binary_import(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          94, /* vkCmdCuLaunchKernelNVX */
         324, /* vkCreateCuFunctionNVX */
         325, /* vkCreateCuModuleNVX */
         402, /* vkDestroyCuFunctionNVX */
         403  /* vkDestroyCuModuleNVX */
    };
    if (!context->NVX_binary_import) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NVX_image_view_handle(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         552, /* vkGetImageViewAddressNVX */
         553, /* vkGetImageViewHandle64NVX */
         554  /* vkGetImageViewHandleNVX */
    };
    if (!context->NVX_image_view_handle) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_NV_acquire_winrt_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           6, /* vkAcquireWinrtDisplayNV */
         682  /* vkGetWinrtDisplayNV */
    };
    if (!context->NV_acquire_winrt_display) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_NV_clip_space_w_scaling(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         281  /* vkCmdSetViewportWScalingNV */
    };
    if (!context->NV_clip_space_w_scaling) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_cluster_acceleration_structure(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          63, /* vkCmdBuildClusterAccelerationStructureIndirectNV */
         483  /* vkGetClusterAccelerationStructureBuildSizesNV */
    };
    if (!context->NV_cluster_acceleration_structure) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_cooperative_matrix(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         578  /* vkGetPhysicalDeviceCooperativeMatrixPropertiesNV */
    };
    if (!context->NV_cooperative_matrix) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_cooperative_matrix2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         576  /* vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV */
    };
    if (!context->NV_cooperative_matrix2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_cooperative_vector(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          70, /* vkCmdConvertCooperativeVectorMatrixNV */
         303, /* vkConvertCooperativeVectorMatrixNV */
         579  /* vkGetPhysicalDeviceCooperativeVectorPropertiesNV */
    };
    if (!context->NV_cooperative_vector) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_copy_memory_indirect(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          86, /* vkCmdCopyMemoryIndirectNV */
          88  /* vkCmdCopyMemoryToImageIndirectNV */
    };
    if (!context->NV_copy_memory_indirect) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_coverage_reduction_mode(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         622  /* vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV */
    };
    if (!context->NV_coverage_reduction_mode) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_ENABLE_BETA_EXTENSIONS)
static void glad_vk_load_VK_NV_cuda_kernel_launch(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          95, /* vkCmdCudaLaunchKernelNV */
         326, /* vkCreateCudaFunctionNV */
         327, /* vkCreateCudaModuleNV */
         404, /* vkDestroyCudaFunctionNV */
         405, /* vkDestroyCudaModuleNV */
         484  /* vkGetCudaModuleCacheNV */
    };
    if (!context->NV_cuda_kernel_launch) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_NV_device_diagnostic_checkpoints(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         183, /* vkCmdSetCheckpointNV */
         652, /* vkGetQueueCheckpointData2NV */
         653  /* vkGetQueueCheckpointDataNV */
    };
    if (!context->NV_device_diagnostic_checkpoints) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_device_generated_commands(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          49, /* vkCmdBindPipelineShaderGroupNV */
         148, /* vkCmdExecuteGeneratedCommandsNV */
         160, /* vkCmdPreprocessGeneratedCommandsNV */
         353, /* vkCreateIndirectCommandsLayoutNV */
         422, /* vkDestroyIndirectCommandsLayoutNV */
         539  /* vkGetGeneratedCommandsMemoryRequirementsNV */
    };
    if (!context->NV_device_generated_commands) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_device_generated_commands_compute(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         290, /* vkCmdUpdatePipelineIndirectBufferNV */
         645, /* vkGetPipelineIndirectDeviceAddressNV */
         646  /* vkGetPipelineIndirectMemoryRequirementsNV */
    };
    if (!context->NV_device_generated_commands_compute) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_external_compute_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         343, /* vkCreateExternalComputeQueueNV */
         416, /* vkDestroyExternalComputeQueueNV */
         533  /* vkGetExternalComputeQueueDataNV */
    };
    if (!context->NV_external_compute_queue) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_external_memory_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         589  /* vkGetPhysicalDeviceExternalImageFormatPropertiesNV */
    };
    if (!context->NV_external_memory_capabilities) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_external_memory_rdma(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         564  /* vkGetMemoryRemoteAddressNV */
    };
    if (!context->NV_external_memory_rdma) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_NV_external_memory_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         566  /* vkGetMemoryWin32HandleNV */
    };
    if (!context->NV_external_memory_win32) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_NV_fragment_shading_rate_enums(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         229  /* vkCmdSetFragmentShadingRateEnumNV */
    };
    if (!context->NV_fragment_shading_rate_enums) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_low_latency2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         557, /* vkGetLatencyTimingsNV */
         690, /* vkLatencySleepNV */
         700, /* vkQueueNotifyOutOfBandNV */
         730, /* vkSetLatencyMarkerNV */
         731  /* vkSetLatencySleepModeNV */
    };
    if (!context->NV_low_latency2) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_memory_decompression(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         100, /* vkCmdDecompressMemoryIndirectCountNV */
         101  /* vkCmdDecompressMemoryNV */
    };
    if (!context->NV_memory_decompression) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_mesh_shader(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         126, /* vkCmdDrawMeshTasksIndirectCountNV */
         128, /* vkCmdDrawMeshTasksIndirectNV */
         129  /* vkCmdDrawMeshTasksNV */
    };
    if (!context->NV_mesh_shader) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_optical_flow(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          21, /* vkBindOpticalFlowSessionImageNV */
         155, /* vkCmdOpticalFlowExecuteNV */
         359, /* vkCreateOpticalFlowSessionNV */
         426, /* vkDestroyOpticalFlowSessionNV */
         607  /* vkGetPhysicalDeviceOpticalFlowImageFormatsNV */
    };
    if (!context->NV_optical_flow) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_partitioned_acceleration_structure(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          65, /* vkCmdBuildPartitionedAccelerationStructuresNV */
         571  /* vkGetPartitionedAccelerationStructuresBuildSizesNV */
    };
    if (!context->NV_partitioned_acceleration_structure) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_ray_tracing(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          13, /* vkBindAccelerationStructureMemoryNV */
          60, /* vkCmdBuildAccelerationStructureNV */
          72, /* vkCmdCopyAccelerationStructureNV */
         288, /* vkCmdTraceRaysNV */
         295, /* vkCmdWriteAccelerationStructuresPropertiesNV */
         302, /* vkCompileDeferredNV */
         317, /* vkCreateAccelerationStructureNV */
         367, /* vkCreateRayTracingPipelinesNV */
         397, /* vkDestroyAccelerationStructureNV */
         467, /* vkGetAccelerationStructureHandleNV */
         468, /* vkGetAccelerationStructureMemoryRequirementsNV */
         657  /* vkGetRayTracingShaderGroupHandlesNV */
    };
    if (!context->NV_ray_tracing) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_scissor_exclusive(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         226, /* vkCmdSetExclusiveScissorEnableNV */
         227  /* vkCmdSetExclusiveScissorNV */
    };
    if (!context->NV_scissor_exclusive) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_NV_shading_rate_image(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          51, /* vkCmdBindShadingRateImageNV */
         184, /* vkCmdSetCoarseSampleOrderNV */
         278  /* vkCmdSetViewportShadingRatePaletteNV */
    };
    if (!context->NV_shading_rate_image) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_OHOS)
static void glad_vk_load_VK_OHOS_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         380  /* vkCreateSurfaceOHOS */
    };
    if (!context->OHOS_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_QCOM_tile_memory_heap(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          52  /* vkCmdBindTileMemoryQCOM */
    };
    if (!context->QCOM_tile_memory_heap) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_QCOM_tile_properties(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         528, /* vkGetDynamicRenderingTilePropertiesQCOM */
         537  /* vkGetFramebufferTilePropertiesQCOM */
    };
    if (!context->QCOM_tile_properties) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_load_VK_QCOM_tile_shading(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          28, /* vkCmdBeginPerTileExecutionQCOM */
         110, /* vkCmdDispatchTileQCOM */
         135  /* vkCmdEndPerTileExecutionQCOM */
    };
    if (!context->QCOM_tile_shading) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#if defined(VK_USE_PLATFORM_SCREEN_QNX)
static void glad_vk_load_VK_QNX_external_memory_screen_buffer(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         664  /* vkGetScreenBufferPropertiesQNX */
    };
    if (!context->QNX_external_memory_screen_buffer) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
static void glad_vk_load_VK_QNX_screen_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         374, /* vkCreateScreenSurfaceQNX */
         618  /* vkGetPhysicalDeviceScreenPresentationSupportQNX */
    };
    if (!context->QNX_screen_surface) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

#endif
static void glad_vk_load_VK_VALVE_descriptor_set_host_mapping(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         492, /* vkGetDescriptorSetHostMappingVALVE */
         494  /* vkGetDescriptorSetLayoutHostMappingInfoVALVE */
    };
    if (!context->VALVE_descriptor_set_host_mapping) return;
    glad_vk_load_pfns(context, load, userptr, s_pfnIdx, GLAD_ARRAYSIZE(s_pfnIdx));
}

static void glad_vk_resolve_aliases(GladVulkanContext *context) {
    static const GladAliasPair_t s_aliases[] = {
        {   15,   16 }, /* vkBindBufferMemory2 and vkBindBufferMemory2KHR */
        {   16,   15 }, /* vkBindBufferMemory2KHR and vkBindBufferMemory2 */
        {   19,   20 }, /* vkBindImageMemory2 and vkBindImageMemory2KHR */
        {   20,   19 }, /* vkBindImageMemory2KHR and vkBindImageMemory2 */
        {   34,   35 }, /* vkCmdBeginRendering and vkCmdBeginRenderingKHR */
        {   35,   34 }, /* vkCmdBeginRenderingKHR and vkCmdBeginRendering */
        {   32,   33 }, /* vkCmdBeginRenderPass2 and vkCmdBeginRenderPass2KHR */
        {   33,   32 }, /* vkCmdBeginRenderPass2KHR and vkCmdBeginRenderPass2 */
        {   42,   43 }, /* vkCmdBindDescriptorSets2 and vkCmdBindDescriptorSets2KHR */
        {   43,   42 }, /* vkCmdBindDescriptorSets2KHR and vkCmdBindDescriptorSets2 */
        {   45,   46 }, /* vkCmdBindIndexBuffer2 and vkCmdBindIndexBuffer2KHR */
        {   46,   45 }, /* vkCmdBindIndexBuffer2KHR and vkCmdBindIndexBuffer2 */
        {   55,   56 }, /* vkCmdBindVertexBuffers2 and vkCmdBindVertexBuffers2EXT */
        {   56,   55 }, /* vkCmdBindVertexBuffers2EXT and vkCmdBindVertexBuffers2 */
        {   58,   59 }, /* vkCmdBlitImage2 and vkCmdBlitImage2KHR */
        {   59,   58 }, /* vkCmdBlitImage2KHR and vkCmdBlitImage2 */
        {   75,   76 }, /* vkCmdCopyBuffer2 and vkCmdCopyBuffer2KHR */
        {   76,   75 }, /* vkCmdCopyBuffer2KHR and vkCmdCopyBuffer2 */
        {   78,   79 }, /* vkCmdCopyBufferToImage2 and vkCmdCopyBufferToImage2KHR */
        {   79,   78 }, /* vkCmdCopyBufferToImage2KHR and vkCmdCopyBufferToImage2 */
        {   81,   82 }, /* vkCmdCopyImage2 and vkCmdCopyImage2KHR */
        {   82,   81 }, /* vkCmdCopyImage2KHR and vkCmdCopyImage2 */
        {   84,   85 }, /* vkCmdCopyImageToBuffer2 and vkCmdCopyImageToBuffer2KHR */
        {   85,   84 }, /* vkCmdCopyImageToBuffer2KHR and vkCmdCopyImageToBuffer2 */
        {  103,  104 }, /* vkCmdDispatchBase and vkCmdDispatchBaseKHR */
        {  104,  103 }, /* vkCmdDispatchBaseKHR and vkCmdDispatchBase */
        {  116,  117 }, /* vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountAMD */
        {  116,  118 }, /* vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountKHR */
        {  117,  116 }, /* vkCmdDrawIndexedIndirectCountAMD and vkCmdDrawIndexedIndirectCount */
        {  117,  118 }, /* vkCmdDrawIndexedIndirectCountAMD and vkCmdDrawIndexedIndirectCountKHR */
        {  118,  116 }, /* vkCmdDrawIndexedIndirectCountKHR and vkCmdDrawIndexedIndirectCount */
        {  118,  117 }, /* vkCmdDrawIndexedIndirectCountKHR and vkCmdDrawIndexedIndirectCountAMD */
        {  121,  122 }, /* vkCmdDrawIndirectCount and vkCmdDrawIndirectCountAMD */
        {  121,  123 }, /* vkCmdDrawIndirectCount and vkCmdDrawIndirectCountKHR */
        {  122,  121 }, /* vkCmdDrawIndirectCountAMD and vkCmdDrawIndirectCount */
        {  122,  123 }, /* vkCmdDrawIndirectCountAMD and vkCmdDrawIndirectCountKHR */
        {  123,  121 }, /* vkCmdDrawIndirectCountKHR and vkCmdDrawIndirectCount */
        {  123,  122 }, /* vkCmdDrawIndirectCountKHR and vkCmdDrawIndirectCountAMD */
        {  141,  143 }, /* vkCmdEndRendering and vkCmdEndRenderingKHR */
        {  143,  141 }, /* vkCmdEndRenderingKHR and vkCmdEndRendering */
        {  139,  140 }, /* vkCmdEndRenderPass2 and vkCmdEndRenderPass2KHR */
        {  140,  139 }, /* vkCmdEndRenderPass2KHR and vkCmdEndRenderPass2 */
        {  153,  154 }, /* vkCmdNextSubpass2 and vkCmdNextSubpass2KHR */
        {  154,  153 }, /* vkCmdNextSubpass2KHR and vkCmdNextSubpass2 */
        {  157,  158 }, /* vkCmdPipelineBarrier2 and vkCmdPipelineBarrier2KHR */
        {  158,  157 }, /* vkCmdPipelineBarrier2KHR and vkCmdPipelineBarrier2 */
        {  162,  163 }, /* vkCmdPushConstants2 and vkCmdPushConstants2KHR */
        {  163,  162 }, /* vkCmdPushConstants2KHR and vkCmdPushConstants2 */
        {  164,  167 }, /* vkCmdPushDescriptorSet and vkCmdPushDescriptorSetKHR */
        {  165,  166 }, /* vkCmdPushDescriptorSet2 and vkCmdPushDescriptorSet2KHR */
        {  166,  165 }, /* vkCmdPushDescriptorSet2KHR and vkCmdPushDescriptorSet2 */
        {  167,  164 }, /* vkCmdPushDescriptorSetKHR and vkCmdPushDescriptorSet */
        {  168,  171 }, /* vkCmdPushDescriptorSetWithTemplate and vkCmdPushDescriptorSetWithTemplateKHR */
        {  169,  170 }, /* vkCmdPushDescriptorSetWithTemplate2 and vkCmdPushDescriptorSetWithTemplate2KHR */
        {  170,  169 }, /* vkCmdPushDescriptorSetWithTemplate2KHR and vkCmdPushDescriptorSetWithTemplate2 */
        {  171,  168 }, /* vkCmdPushDescriptorSetWithTemplateKHR and vkCmdPushDescriptorSetWithTemplate */
        {  173,  174 }, /* vkCmdResetEvent2 and vkCmdResetEvent2KHR */
        {  174,  173 }, /* vkCmdResetEvent2KHR and vkCmdResetEvent2 */
        {  177,  178 }, /* vkCmdResolveImage2 and vkCmdResolveImage2KHR */
        {  178,  177 }, /* vkCmdResolveImage2KHR and vkCmdResolveImage2 */
        {  197,  198 }, /* vkCmdSetCullMode and vkCmdSetCullModeEXT */
        {  198,  197 }, /* vkCmdSetCullModeEXT and vkCmdSetCullMode */
        {  201,  202 }, /* vkCmdSetDepthBiasEnable and vkCmdSetDepthBiasEnableEXT */
        {  202,  201 }, /* vkCmdSetDepthBiasEnableEXT and vkCmdSetDepthBiasEnable */
        {  204,  205 }, /* vkCmdSetDepthBoundsTestEnable and vkCmdSetDepthBoundsTestEnableEXT */
        {  205,  204 }, /* vkCmdSetDepthBoundsTestEnableEXT and vkCmdSetDepthBoundsTestEnable */
        {  210,  211 }, /* vkCmdSetDepthCompareOp and vkCmdSetDepthCompareOpEXT */
        {  211,  210 }, /* vkCmdSetDepthCompareOpEXT and vkCmdSetDepthCompareOp */
        {  212,  213 }, /* vkCmdSetDepthTestEnable and vkCmdSetDepthTestEnableEXT */
        {  213,  212 }, /* vkCmdSetDepthTestEnableEXT and vkCmdSetDepthTestEnable */
        {  214,  215 }, /* vkCmdSetDepthWriteEnable and vkCmdSetDepthWriteEnableEXT */
        {  215,  214 }, /* vkCmdSetDepthWriteEnableEXT and vkCmdSetDepthWriteEnable */
        {  218,  219 }, /* vkCmdSetDeviceMask and vkCmdSetDeviceMaskKHR */
        {  219,  218 }, /* vkCmdSetDeviceMaskKHR and vkCmdSetDeviceMask */
        {  224,  225 }, /* vkCmdSetEvent2 and vkCmdSetEvent2KHR */
        {  225,  224 }, /* vkCmdSetEvent2KHR and vkCmdSetEvent2 */
        {  231,  232 }, /* vkCmdSetFrontFace and vkCmdSetFrontFaceEXT */
        {  232,  231 }, /* vkCmdSetFrontFaceEXT and vkCmdSetFrontFace */
        {  234,  235 }, /* vkCmdSetLineStipple and vkCmdSetLineStippleEXT */
        {  234,  237 }, /* vkCmdSetLineStipple and vkCmdSetLineStippleKHR */
        {  235,  234 }, /* vkCmdSetLineStippleEXT and vkCmdSetLineStipple */
        {  235,  237 }, /* vkCmdSetLineStippleEXT and vkCmdSetLineStippleKHR */
        {  237,  234 }, /* vkCmdSetLineStippleKHR and vkCmdSetLineStipple */
        {  237,  235 }, /* vkCmdSetLineStippleKHR and vkCmdSetLineStippleEXT */
        {  246,  247 }, /* vkCmdSetPrimitiveRestartEnable and vkCmdSetPrimitiveRestartEnableEXT */
        {  247,  246 }, /* vkCmdSetPrimitiveRestartEnableEXT and vkCmdSetPrimitiveRestartEnable */
        {  248,  249 }, /* vkCmdSetPrimitiveTopology and vkCmdSetPrimitiveTopologyEXT */
        {  249,  248 }, /* vkCmdSetPrimitiveTopologyEXT and vkCmdSetPrimitiveTopology */
        {  253,  254 }, /* vkCmdSetRasterizerDiscardEnable and vkCmdSetRasterizerDiscardEnableEXT */
        {  254,  253 }, /* vkCmdSetRasterizerDiscardEnableEXT and vkCmdSetRasterizerDiscardEnable */
        {  256,  257 }, /* vkCmdSetRenderingAttachmentLocations and vkCmdSetRenderingAttachmentLocationsKHR */
        {  257,  256 }, /* vkCmdSetRenderingAttachmentLocationsKHR and vkCmdSetRenderingAttachmentLocations */
        {  258,  259 }, /* vkCmdSetRenderingInputAttachmentIndices and vkCmdSetRenderingInputAttachmentIndicesKHR */
        {  259,  258 }, /* vkCmdSetRenderingInputAttachmentIndicesKHR and vkCmdSetRenderingInputAttachmentIndices */
        {  265,  266 }, /* vkCmdSetScissorWithCount and vkCmdSetScissorWithCountEXT */
        {  266,  265 }, /* vkCmdSetScissorWithCountEXT and vkCmdSetScissorWithCount */
        {  269,  270 }, /* vkCmdSetStencilOp and vkCmdSetStencilOpEXT */
        {  270,  269 }, /* vkCmdSetStencilOpEXT and vkCmdSetStencilOp */
        {  272,  273 }, /* vkCmdSetStencilTestEnable and vkCmdSetStencilTestEnableEXT */
        {  273,  272 }, /* vkCmdSetStencilTestEnableEXT and vkCmdSetStencilTestEnable */
        {  282,  283 }, /* vkCmdSetViewportWithCount and vkCmdSetViewportWithCountEXT */
        {  283,  282 }, /* vkCmdSetViewportWithCountEXT and vkCmdSetViewportWithCount */
        {  292,  293 }, /* vkCmdWaitEvents2 and vkCmdWaitEvents2KHR */
        {  293,  292 }, /* vkCmdWaitEvents2KHR and vkCmdWaitEvents2 */
        {  300,  301 }, /* vkCmdWriteTimestamp2 and vkCmdWriteTimestamp2KHR */
        {  301,  300 }, /* vkCmdWriteTimestamp2KHR and vkCmdWriteTimestamp2 */
        {  306,  307 }, /* vkCopyImageToImage and vkCopyImageToImageEXT */
        {  307,  306 }, /* vkCopyImageToImageEXT and vkCopyImageToImage */
        {  308,  309 }, /* vkCopyImageToMemory and vkCopyImageToMemoryEXT */
        {  309,  308 }, /* vkCopyImageToMemoryEXT and vkCopyImageToMemory */
        {  311,  312 }, /* vkCopyMemoryToImage and vkCopyMemoryToImageEXT */
        {  312,  311 }, /* vkCopyMemoryToImageEXT and vkCopyMemoryToImage */
        {  335,  336 }, /* vkCreateDescriptorUpdateTemplate and vkCreateDescriptorUpdateTemplateKHR */
        {  336,  335 }, /* vkCreateDescriptorUpdateTemplateKHR and vkCreateDescriptorUpdateTemplate */
        {  363,  364 }, /* vkCreatePrivateDataSlot and vkCreatePrivateDataSlotEXT */
        {  364,  363 }, /* vkCreatePrivateDataSlotEXT and vkCreatePrivateDataSlot */
        {  369,  370 }, /* vkCreateRenderPass2 and vkCreateRenderPass2KHR */
        {  370,  369 }, /* vkCreateRenderPass2KHR and vkCreateRenderPass2 */
        {  372,  373 }, /* vkCreateSamplerYcbcrConversion and vkCreateSamplerYcbcrConversionKHR */
        {  373,  372 }, /* vkCreateSamplerYcbcrConversionKHR and vkCreateSamplerYcbcrConversion */
        {  412,  413 }, /* vkDestroyDescriptorUpdateTemplate and vkDestroyDescriptorUpdateTemplateKHR */
        {  413,  412 }, /* vkDestroyDescriptorUpdateTemplateKHR and vkDestroyDescriptorUpdateTemplate */
        {  431,  432 }, /* vkDestroyPrivateDataSlot and vkDestroyPrivateDataSlotEXT */
        {  432,  431 }, /* vkDestroyPrivateDataSlotEXT and vkDestroyPrivateDataSlot */
        {  436,  437 }, /* vkDestroySamplerYcbcrConversion and vkDestroySamplerYcbcrConversionKHR */
        {  437,  436 }, /* vkDestroySamplerYcbcrConversionKHR and vkDestroySamplerYcbcrConversion */
        {  456,  457 }, /* vkEnumeratePhysicalDeviceGroups and vkEnumeratePhysicalDeviceGroupsKHR */
        {  457,  456 }, /* vkEnumeratePhysicalDeviceGroupsKHR and vkEnumeratePhysicalDeviceGroups */
        {  472,  473 }, /* vkGetBufferDeviceAddress and vkGetBufferDeviceAddressEXT */
        {  472,  474 }, /* vkGetBufferDeviceAddress and vkGetBufferDeviceAddressKHR */
        {  473,  472 }, /* vkGetBufferDeviceAddressEXT and vkGetBufferDeviceAddress */
        {  473,  474 }, /* vkGetBufferDeviceAddressEXT and vkGetBufferDeviceAddressKHR */
        {  474,  472 }, /* vkGetBufferDeviceAddressKHR and vkGetBufferDeviceAddress */
        {  474,  473 }, /* vkGetBufferDeviceAddressKHR and vkGetBufferDeviceAddressEXT */
        {  476,  477 }, /* vkGetBufferMemoryRequirements2 and vkGetBufferMemoryRequirements2KHR */
        {  477,  476 }, /* vkGetBufferMemoryRequirements2KHR and vkGetBufferMemoryRequirements2 */
        {  478,  479 }, /* vkGetBufferOpaqueCaptureAddress and vkGetBufferOpaqueCaptureAddressKHR */
        {  479,  478 }, /* vkGetBufferOpaqueCaptureAddressKHR and vkGetBufferOpaqueCaptureAddress */
        {  481,  482 }, /* vkGetCalibratedTimestampsEXT and vkGetCalibratedTimestampsKHR */
        {  482,  481 }, /* vkGetCalibratedTimestampsKHR and vkGetCalibratedTimestampsEXT */
        {  496,  497 }, /* vkGetDescriptorSetLayoutSupport and vkGetDescriptorSetLayoutSupportKHR */
        {  497,  496 }, /* vkGetDescriptorSetLayoutSupportKHR and vkGetDescriptorSetLayoutSupport */
        {  499,  500 }, /* vkGetDeviceBufferMemoryRequirements and vkGetDeviceBufferMemoryRequirementsKHR */
        {  500,  499 }, /* vkGetDeviceBufferMemoryRequirementsKHR and vkGetDeviceBufferMemoryRequirements */
        {  502,  503 }, /* vkGetDeviceGroupPeerMemoryFeatures and vkGetDeviceGroupPeerMemoryFeaturesKHR */
        {  503,  502 }, /* vkGetDeviceGroupPeerMemoryFeaturesKHR and vkGetDeviceGroupPeerMemoryFeatures */
        {  507,  508 }, /* vkGetDeviceImageMemoryRequirements and vkGetDeviceImageMemoryRequirementsKHR */
        {  508,  507 }, /* vkGetDeviceImageMemoryRequirementsKHR and vkGetDeviceImageMemoryRequirements */
        {  509,  510 }, /* vkGetDeviceImageSparseMemoryRequirements and vkGetDeviceImageSparseMemoryRequirementsKHR */
        {  510,  509 }, /* vkGetDeviceImageSparseMemoryRequirementsKHR and vkGetDeviceImageSparseMemoryRequirements */
        {  511,  512 }, /* vkGetDeviceImageSubresourceLayout and vkGetDeviceImageSubresourceLayoutKHR */
        {  512,  511 }, /* vkGetDeviceImageSubresourceLayoutKHR and vkGetDeviceImageSubresourceLayout */
        {  514,  515 }, /* vkGetDeviceMemoryOpaqueCaptureAddress and vkGetDeviceMemoryOpaqueCaptureAddressKHR */
        {  515,  514 }, /* vkGetDeviceMemoryOpaqueCaptureAddressKHR and vkGetDeviceMemoryOpaqueCaptureAddress */
        {  542,  543 }, /* vkGetImageMemoryRequirements2 and vkGetImageMemoryRequirements2KHR */
        {  543,  542 }, /* vkGetImageMemoryRequirements2KHR and vkGetImageMemoryRequirements2 */
        {  546,  547 }, /* vkGetImageSparseMemoryRequirements2 and vkGetImageSparseMemoryRequirements2KHR */
        {  547,  546 }, /* vkGetImageSparseMemoryRequirements2KHR and vkGetImageSparseMemoryRequirements2 */
        {  549,  550 }, /* vkGetImageSubresourceLayout2 and vkGetImageSubresourceLayout2EXT */
        {  549,  551 }, /* vkGetImageSubresourceLayout2 and vkGetImageSubresourceLayout2KHR */
        {  550,  549 }, /* vkGetImageSubresourceLayout2EXT and vkGetImageSubresourceLayout2 */
        {  550,  551 }, /* vkGetImageSubresourceLayout2EXT and vkGetImageSubresourceLayout2KHR */
        {  551,  549 }, /* vkGetImageSubresourceLayout2KHR and vkGetImageSubresourceLayout2 */
        {  551,  550 }, /* vkGetImageSubresourceLayout2KHR and vkGetImageSubresourceLayout2EXT */
        {  574,  575 }, /* vkGetPhysicalDeviceCalibrateableTimeDomainsEXT and vkGetPhysicalDeviceCalibrateableTimeDomainsKHR */
        {  575,  574 }, /* vkGetPhysicalDeviceCalibrateableTimeDomainsKHR and vkGetPhysicalDeviceCalibrateableTimeDomainsEXT */
        {  585,  586 }, /* vkGetPhysicalDeviceExternalBufferProperties and vkGetPhysicalDeviceExternalBufferPropertiesKHR */
        {  586,  585 }, /* vkGetPhysicalDeviceExternalBufferPropertiesKHR and vkGetPhysicalDeviceExternalBufferProperties */
        {  587,  588 }, /* vkGetPhysicalDeviceExternalFenceProperties and vkGetPhysicalDeviceExternalFencePropertiesKHR */
        {  588,  587 }, /* vkGetPhysicalDeviceExternalFencePropertiesKHR and vkGetPhysicalDeviceExternalFenceProperties */
        {  590,  591 }, /* vkGetPhysicalDeviceExternalSemaphoreProperties and vkGetPhysicalDeviceExternalSemaphorePropertiesKHR */
        {  591,  590 }, /* vkGetPhysicalDeviceExternalSemaphorePropertiesKHR and vkGetPhysicalDeviceExternalSemaphoreProperties */
        {  594,  595 }, /* vkGetPhysicalDeviceFeatures2 and vkGetPhysicalDeviceFeatures2KHR */
        {  595,  594 }, /* vkGetPhysicalDeviceFeatures2KHR and vkGetPhysicalDeviceFeatures2 */
        {  597,  598 }, /* vkGetPhysicalDeviceFormatProperties2 and vkGetPhysicalDeviceFormatProperties2KHR */
        {  598,  597 }, /* vkGetPhysicalDeviceFormatProperties2KHR and vkGetPhysicalDeviceFormatProperties2 */
        {  601,  602 }, /* vkGetPhysicalDeviceImageFormatProperties2 and vkGetPhysicalDeviceImageFormatProperties2KHR */
        {  602,  601 }, /* vkGetPhysicalDeviceImageFormatProperties2KHR and vkGetPhysicalDeviceImageFormatProperties2 */
        {  604,  605 }, /* vkGetPhysicalDeviceMemoryProperties2 and vkGetPhysicalDeviceMemoryProperties2KHR */
        {  605,  604 }, /* vkGetPhysicalDeviceMemoryProperties2KHR and vkGetPhysicalDeviceMemoryProperties2 */
        {  610,  611 }, /* vkGetPhysicalDeviceProperties2 and vkGetPhysicalDeviceProperties2KHR */
        {  611,  610 }, /* vkGetPhysicalDeviceProperties2KHR and vkGetPhysicalDeviceProperties2 */
        {  616,  617 }, /* vkGetPhysicalDeviceQueueFamilyProperties2 and vkGetPhysicalDeviceQueueFamilyProperties2KHR */
        {  617,  616 }, /* vkGetPhysicalDeviceQueueFamilyProperties2KHR and vkGetPhysicalDeviceQueueFamilyProperties2 */
        {  620,  621 }, /* vkGetPhysicalDeviceSparseImageFormatProperties2 and vkGetPhysicalDeviceSparseImageFormatProperties2KHR */
        {  621,  620 }, /* vkGetPhysicalDeviceSparseImageFormatProperties2KHR and vkGetPhysicalDeviceSparseImageFormatProperties2 */
        {  631,  632 }, /* vkGetPhysicalDeviceToolProperties and vkGetPhysicalDeviceToolPropertiesEXT */
        {  632,  631 }, /* vkGetPhysicalDeviceToolPropertiesEXT and vkGetPhysicalDeviceToolProperties */
        {  649,  650 }, /* vkGetPrivateData and vkGetPrivateDataEXT */
        {  650,  649 }, /* vkGetPrivateDataEXT and vkGetPrivateData */
        {  656,  657 }, /* vkGetRayTracingShaderGroupHandlesKHR and vkGetRayTracingShaderGroupHandlesNV */
        {  657,  656 }, /* vkGetRayTracingShaderGroupHandlesNV and vkGetRayTracingShaderGroupHandlesKHR */
        {  661,  662 }, /* vkGetRenderingAreaGranularity and vkGetRenderingAreaGranularityKHR */
        {  662,  661 }, /* vkGetRenderingAreaGranularityKHR and vkGetRenderingAreaGranularity */
        {  665,  666 }, /* vkGetSemaphoreCounterValue and vkGetSemaphoreCounterValueKHR */
        {  666,  665 }, /* vkGetSemaphoreCounterValueKHR and vkGetSemaphoreCounterValue */
        {  692,  693 }, /* vkMapMemory2 and vkMapMemory2KHR */
        {  693,  692 }, /* vkMapMemory2KHR and vkMapMemory2 */
        {  704,  705 }, /* vkQueueSubmit2 and vkQueueSubmit2KHR */
        {  705,  704 }, /* vkQueueSubmit2KHR and vkQueueSubmit2 */
        {  714,  715 }, /* vkReleaseSwapchainImagesEXT and vkReleaseSwapchainImagesKHR */
        {  715,  714 }, /* vkReleaseSwapchainImagesKHR and vkReleaseSwapchainImagesEXT */
        {  721,  722 }, /* vkResetQueryPool and vkResetQueryPoolEXT */
        {  722,  721 }, /* vkResetQueryPoolEXT and vkResetQueryPool */
        {  733,  734 }, /* vkSetPrivateData and vkSetPrivateDataEXT */
        {  734,  733 }, /* vkSetPrivateDataEXT and vkSetPrivateData */
        {  735,  736 }, /* vkSignalSemaphore and vkSignalSemaphoreKHR */
        {  736,  735 }, /* vkSignalSemaphoreKHR and vkSignalSemaphore */
        {  738,  739 }, /* vkTransitionImageLayout and vkTransitionImageLayoutEXT */
        {  739,  738 }, /* vkTransitionImageLayoutEXT and vkTransitionImageLayout */
        {  740,  741 }, /* vkTrimCommandPool and vkTrimCommandPoolKHR */
        {  741,  740 }, /* vkTrimCommandPoolKHR and vkTrimCommandPool */
        {  744,  745 }, /* vkUnmapMemory2 and vkUnmapMemory2KHR */
        {  745,  744 }, /* vkUnmapMemory2KHR and vkUnmapMemory2 */
        {  746,  747 }, /* vkUpdateDescriptorSetWithTemplate and vkUpdateDescriptorSetWithTemplateKHR */
        {  747,  746 }, /* vkUpdateDescriptorSetWithTemplateKHR and vkUpdateDescriptorSetWithTemplate */
        {  755,  756 }, /* vkWaitSemaphores and vkWaitSemaphoresKHR */
        {  756,  755 }, /* vkWaitSemaphoresKHR and vkWaitSemaphores */
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
    glad_vk_load_VK_ARM_data_graph(context, load, userptr);
    glad_vk_load_VK_ARM_tensors(context, load, userptr);
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
    glad_vk_load_VK_KHR_present_wait2(context, load, userptr);
    glad_vk_load_VK_KHR_push_descriptor(context, load, userptr);
    glad_vk_load_VK_KHR_ray_tracing_maintenance1(context, load, userptr);
    glad_vk_load_VK_KHR_ray_tracing_pipeline(context, load, userptr);
    glad_vk_load_VK_KHR_sampler_ycbcr_conversion(context, load, userptr);
    glad_vk_load_VK_KHR_shared_presentable_image(context, load, userptr);
    glad_vk_load_VK_KHR_surface(context, load, userptr);
    glad_vk_load_VK_KHR_swapchain(context, load, userptr);
    glad_vk_load_VK_KHR_swapchain_maintenance1(context, load, userptr);
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
#if defined(VK_USE_PLATFORM_OHOS)
    glad_vk_load_VK_OHOS_surface(context, load, userptr);
#endif
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
