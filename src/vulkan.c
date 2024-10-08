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
    /*   39 */ "vkCmdBindDescriptorSets2KHR",
    /*   40 */ "vkCmdBindIndexBuffer",
    /*   41 */ "vkCmdBindIndexBuffer2KHR",
    /*   42 */ "vkCmdBindInvocationMaskHUAWEI",
    /*   43 */ "vkCmdBindPipeline",
    /*   44 */ "vkCmdBindPipelineShaderGroupNV",
    /*   45 */ "vkCmdBindShadersEXT",
    /*   46 */ "vkCmdBindShadingRateImageNV",
    /*   47 */ "vkCmdBindTransformFeedbackBuffersEXT",
    /*   48 */ "vkCmdBindVertexBuffers",
    /*   49 */ "vkCmdBindVertexBuffers2",
    /*   50 */ "vkCmdBindVertexBuffers2EXT",
    /*   51 */ "vkCmdBlitImage",
    /*   52 */ "vkCmdBlitImage2",
    /*   53 */ "vkCmdBlitImage2KHR",
    /*   54 */ "vkCmdBuildAccelerationStructureNV",
    /*   55 */ "vkCmdBuildAccelerationStructuresIndirectKHR",
    /*   56 */ "vkCmdBuildAccelerationStructuresKHR",
    /*   57 */ "vkCmdBuildMicromapsEXT",
    /*   58 */ "vkCmdClearAttachments",
    /*   59 */ "vkCmdClearColorImage",
    /*   60 */ "vkCmdClearDepthStencilImage",
    /*   61 */ "vkCmdControlVideoCodingKHR",
    /*   62 */ "vkCmdCopyAccelerationStructureKHR",
    /*   63 */ "vkCmdCopyAccelerationStructureNV",
    /*   64 */ "vkCmdCopyAccelerationStructureToMemoryKHR",
    /*   65 */ "vkCmdCopyBuffer",
    /*   66 */ "vkCmdCopyBuffer2",
    /*   67 */ "vkCmdCopyBuffer2KHR",
    /*   68 */ "vkCmdCopyBufferToImage",
    /*   69 */ "vkCmdCopyBufferToImage2",
    /*   70 */ "vkCmdCopyBufferToImage2KHR",
    /*   71 */ "vkCmdCopyImage",
    /*   72 */ "vkCmdCopyImage2",
    /*   73 */ "vkCmdCopyImage2KHR",
    /*   74 */ "vkCmdCopyImageToBuffer",
    /*   75 */ "vkCmdCopyImageToBuffer2",
    /*   76 */ "vkCmdCopyImageToBuffer2KHR",
    /*   77 */ "vkCmdCopyMemoryIndirectNV",
    /*   78 */ "vkCmdCopyMemoryToAccelerationStructureKHR",
    /*   79 */ "vkCmdCopyMemoryToImageIndirectNV",
    /*   80 */ "vkCmdCopyMemoryToMicromapEXT",
    /*   81 */ "vkCmdCopyMicromapEXT",
    /*   82 */ "vkCmdCopyMicromapToMemoryEXT",
    /*   83 */ "vkCmdCopyQueryPoolResults",
    /*   84 */ "vkCmdCuLaunchKernelNVX",
    /*   85 */ "vkCmdCudaLaunchKernelNV",
    /*   86 */ "vkCmdDebugMarkerBeginEXT",
    /*   87 */ "vkCmdDebugMarkerEndEXT",
    /*   88 */ "vkCmdDebugMarkerInsertEXT",
    /*   89 */ "vkCmdDecodeVideoKHR",
    /*   90 */ "vkCmdDecompressMemoryIndirectCountNV",
    /*   91 */ "vkCmdDecompressMemoryNV",
    /*   92 */ "vkCmdDispatch",
    /*   93 */ "vkCmdDispatchBase",
    /*   94 */ "vkCmdDispatchBaseKHR",
    /*   95 */ "vkCmdDispatchGraphAMDX",
    /*   96 */ "vkCmdDispatchGraphIndirectAMDX",
    /*   97 */ "vkCmdDispatchGraphIndirectCountAMDX",
    /*   98 */ "vkCmdDispatchIndirect",
    /*   99 */ "vkCmdDraw",
    /*  100 */ "vkCmdDrawClusterHUAWEI",
    /*  101 */ "vkCmdDrawClusterIndirectHUAWEI",
    /*  102 */ "vkCmdDrawIndexed",
    /*  103 */ "vkCmdDrawIndexedIndirect",
    /*  104 */ "vkCmdDrawIndexedIndirectCount",
    /*  105 */ "vkCmdDrawIndexedIndirectCountAMD",
    /*  106 */ "vkCmdDrawIndexedIndirectCountKHR",
    /*  107 */ "vkCmdDrawIndirect",
    /*  108 */ "vkCmdDrawIndirectByteCountEXT",
    /*  109 */ "vkCmdDrawIndirectCount",
    /*  110 */ "vkCmdDrawIndirectCountAMD",
    /*  111 */ "vkCmdDrawIndirectCountKHR",
    /*  112 */ "vkCmdDrawMeshTasksEXT",
    /*  113 */ "vkCmdDrawMeshTasksIndirectCountEXT",
    /*  114 */ "vkCmdDrawMeshTasksIndirectCountNV",
    /*  115 */ "vkCmdDrawMeshTasksIndirectEXT",
    /*  116 */ "vkCmdDrawMeshTasksIndirectNV",
    /*  117 */ "vkCmdDrawMeshTasksNV",
    /*  118 */ "vkCmdDrawMultiEXT",
    /*  119 */ "vkCmdDrawMultiIndexedEXT",
    /*  120 */ "vkCmdEncodeVideoKHR",
    /*  121 */ "vkCmdEndConditionalRenderingEXT",
    /*  122 */ "vkCmdEndDebugUtilsLabelEXT",
    /*  123 */ "vkCmdEndQuery",
    /*  124 */ "vkCmdEndQueryIndexedEXT",
    /*  125 */ "vkCmdEndRenderPass",
    /*  126 */ "vkCmdEndRenderPass2",
    /*  127 */ "vkCmdEndRenderPass2KHR",
    /*  128 */ "vkCmdEndRendering",
    /*  129 */ "vkCmdEndRenderingKHR",
    /*  130 */ "vkCmdEndTransformFeedbackEXT",
    /*  131 */ "vkCmdEndVideoCodingKHR",
    /*  132 */ "vkCmdExecuteCommands",
    /*  133 */ "vkCmdExecuteGeneratedCommandsNV",
    /*  134 */ "vkCmdFillBuffer",
    /*  135 */ "vkCmdInitializeGraphScratchMemoryAMDX",
    /*  136 */ "vkCmdInsertDebugUtilsLabelEXT",
    /*  137 */ "vkCmdNextSubpass",
    /*  138 */ "vkCmdNextSubpass2",
    /*  139 */ "vkCmdNextSubpass2KHR",
    /*  140 */ "vkCmdOpticalFlowExecuteNV",
    /*  141 */ "vkCmdPipelineBarrier",
    /*  142 */ "vkCmdPipelineBarrier2",
    /*  143 */ "vkCmdPipelineBarrier2KHR",
    /*  144 */ "vkCmdPreprocessGeneratedCommandsNV",
    /*  145 */ "vkCmdPushConstants",
    /*  146 */ "vkCmdPushConstants2KHR",
    /*  147 */ "vkCmdPushDescriptorSet2KHR",
    /*  148 */ "vkCmdPushDescriptorSetKHR",
    /*  149 */ "vkCmdPushDescriptorSetWithTemplate2KHR",
    /*  150 */ "vkCmdPushDescriptorSetWithTemplateKHR",
    /*  151 */ "vkCmdResetEvent",
    /*  152 */ "vkCmdResetEvent2",
    /*  153 */ "vkCmdResetEvent2KHR",
    /*  154 */ "vkCmdResetQueryPool",
    /*  155 */ "vkCmdResolveImage",
    /*  156 */ "vkCmdResolveImage2",
    /*  157 */ "vkCmdResolveImage2KHR",
    /*  158 */ "vkCmdSetAlphaToCoverageEnableEXT",
    /*  159 */ "vkCmdSetAlphaToOneEnableEXT",
    /*  160 */ "vkCmdSetAttachmentFeedbackLoopEnableEXT",
    /*  161 */ "vkCmdSetBlendConstants",
    /*  162 */ "vkCmdSetCheckpointNV",
    /*  163 */ "vkCmdSetCoarseSampleOrderNV",
    /*  164 */ "vkCmdSetColorBlendAdvancedEXT",
    /*  165 */ "vkCmdSetColorBlendEnableEXT",
    /*  166 */ "vkCmdSetColorBlendEquationEXT",
    /*  167 */ "vkCmdSetColorWriteEnableEXT",
    /*  168 */ "vkCmdSetColorWriteMaskEXT",
    /*  169 */ "vkCmdSetConservativeRasterizationModeEXT",
    /*  170 */ "vkCmdSetCoverageModulationModeNV",
    /*  171 */ "vkCmdSetCoverageModulationTableEnableNV",
    /*  172 */ "vkCmdSetCoverageModulationTableNV",
    /*  173 */ "vkCmdSetCoverageReductionModeNV",
    /*  174 */ "vkCmdSetCoverageToColorEnableNV",
    /*  175 */ "vkCmdSetCoverageToColorLocationNV",
    /*  176 */ "vkCmdSetCullMode",
    /*  177 */ "vkCmdSetCullModeEXT",
    /*  178 */ "vkCmdSetDepthBias",
    /*  179 */ "vkCmdSetDepthBias2EXT",
    /*  180 */ "vkCmdSetDepthBiasEnable",
    /*  181 */ "vkCmdSetDepthBiasEnableEXT",
    /*  182 */ "vkCmdSetDepthBounds",
    /*  183 */ "vkCmdSetDepthBoundsTestEnable",
    /*  184 */ "vkCmdSetDepthBoundsTestEnableEXT",
    /*  185 */ "vkCmdSetDepthClampEnableEXT",
    /*  186 */ "vkCmdSetDepthClipEnableEXT",
    /*  187 */ "vkCmdSetDepthClipNegativeOneToOneEXT",
    /*  188 */ "vkCmdSetDepthCompareOp",
    /*  189 */ "vkCmdSetDepthCompareOpEXT",
    /*  190 */ "vkCmdSetDepthTestEnable",
    /*  191 */ "vkCmdSetDepthTestEnableEXT",
    /*  192 */ "vkCmdSetDepthWriteEnable",
    /*  193 */ "vkCmdSetDepthWriteEnableEXT",
    /*  194 */ "vkCmdSetDescriptorBufferOffsets2EXT",
    /*  195 */ "vkCmdSetDescriptorBufferOffsetsEXT",
    /*  196 */ "vkCmdSetDeviceMask",
    /*  197 */ "vkCmdSetDeviceMaskKHR",
    /*  198 */ "vkCmdSetDiscardRectangleEXT",
    /*  199 */ "vkCmdSetDiscardRectangleEnableEXT",
    /*  200 */ "vkCmdSetDiscardRectangleModeEXT",
    /*  201 */ "vkCmdSetEvent",
    /*  202 */ "vkCmdSetEvent2",
    /*  203 */ "vkCmdSetEvent2KHR",
    /*  204 */ "vkCmdSetExclusiveScissorEnableNV",
    /*  205 */ "vkCmdSetExclusiveScissorNV",
    /*  206 */ "vkCmdSetExtraPrimitiveOverestimationSizeEXT",
    /*  207 */ "vkCmdSetFragmentShadingRateEnumNV",
    /*  208 */ "vkCmdSetFragmentShadingRateKHR",
    /*  209 */ "vkCmdSetFrontFace",
    /*  210 */ "vkCmdSetFrontFaceEXT",
    /*  211 */ "vkCmdSetLineRasterizationModeEXT",
    /*  212 */ "vkCmdSetLineStippleEXT",
    /*  213 */ "vkCmdSetLineStippleEnableEXT",
    /*  214 */ "vkCmdSetLineStippleKHR",
    /*  215 */ "vkCmdSetLineWidth",
    /*  216 */ "vkCmdSetLogicOpEXT",
    /*  217 */ "vkCmdSetLogicOpEnableEXT",
    /*  218 */ "vkCmdSetPatchControlPointsEXT",
    /*  219 */ "vkCmdSetPerformanceMarkerINTEL",
    /*  220 */ "vkCmdSetPerformanceOverrideINTEL",
    /*  221 */ "vkCmdSetPerformanceStreamMarkerINTEL",
    /*  222 */ "vkCmdSetPolygonModeEXT",
    /*  223 */ "vkCmdSetPrimitiveRestartEnable",
    /*  224 */ "vkCmdSetPrimitiveRestartEnableEXT",
    /*  225 */ "vkCmdSetPrimitiveTopology",
    /*  226 */ "vkCmdSetPrimitiveTopologyEXT",
    /*  227 */ "vkCmdSetProvokingVertexModeEXT",
    /*  228 */ "vkCmdSetRasterizationSamplesEXT",
    /*  229 */ "vkCmdSetRasterizationStreamEXT",
    /*  230 */ "vkCmdSetRasterizerDiscardEnable",
    /*  231 */ "vkCmdSetRasterizerDiscardEnableEXT",
    /*  232 */ "vkCmdSetRayTracingPipelineStackSizeKHR",
    /*  233 */ "vkCmdSetRenderingAttachmentLocationsKHR",
    /*  234 */ "vkCmdSetRenderingInputAttachmentIndicesKHR",
    /*  235 */ "vkCmdSetRepresentativeFragmentTestEnableNV",
    /*  236 */ "vkCmdSetSampleLocationsEXT",
    /*  237 */ "vkCmdSetSampleLocationsEnableEXT",
    /*  238 */ "vkCmdSetSampleMaskEXT",
    /*  239 */ "vkCmdSetScissor",
    /*  240 */ "vkCmdSetScissorWithCount",
    /*  241 */ "vkCmdSetScissorWithCountEXT",
    /*  242 */ "vkCmdSetShadingRateImageEnableNV",
    /*  243 */ "vkCmdSetStencilCompareMask",
    /*  244 */ "vkCmdSetStencilOp",
    /*  245 */ "vkCmdSetStencilOpEXT",
    /*  246 */ "vkCmdSetStencilReference",
    /*  247 */ "vkCmdSetStencilTestEnable",
    /*  248 */ "vkCmdSetStencilTestEnableEXT",
    /*  249 */ "vkCmdSetStencilWriteMask",
    /*  250 */ "vkCmdSetTessellationDomainOriginEXT",
    /*  251 */ "vkCmdSetVertexInputEXT",
    /*  252 */ "vkCmdSetViewport",
    /*  253 */ "vkCmdSetViewportShadingRatePaletteNV",
    /*  254 */ "vkCmdSetViewportSwizzleNV",
    /*  255 */ "vkCmdSetViewportWScalingEnableNV",
    /*  256 */ "vkCmdSetViewportWScalingNV",
    /*  257 */ "vkCmdSetViewportWithCount",
    /*  258 */ "vkCmdSetViewportWithCountEXT",
    /*  259 */ "vkCmdSubpassShadingHUAWEI",
    /*  260 */ "vkCmdTraceRaysIndirect2KHR",
    /*  261 */ "vkCmdTraceRaysIndirectKHR",
    /*  262 */ "vkCmdTraceRaysKHR",
    /*  263 */ "vkCmdTraceRaysNV",
    /*  264 */ "vkCmdUpdateBuffer",
    /*  265 */ "vkCmdUpdatePipelineIndirectBufferNV",
    /*  266 */ "vkCmdWaitEvents",
    /*  267 */ "vkCmdWaitEvents2",
    /*  268 */ "vkCmdWaitEvents2KHR",
    /*  269 */ "vkCmdWriteAccelerationStructuresPropertiesKHR",
    /*  270 */ "vkCmdWriteAccelerationStructuresPropertiesNV",
    /*  271 */ "vkCmdWriteBufferMarker2AMD",
    /*  272 */ "vkCmdWriteBufferMarkerAMD",
    /*  273 */ "vkCmdWriteMicromapsPropertiesEXT",
    /*  274 */ "vkCmdWriteTimestamp",
    /*  275 */ "vkCmdWriteTimestamp2",
    /*  276 */ "vkCmdWriteTimestamp2KHR",
    /*  277 */ "vkCompileDeferredNV",
    /*  278 */ "vkCopyAccelerationStructureKHR",
    /*  279 */ "vkCopyAccelerationStructureToMemoryKHR",
    /*  280 */ "vkCopyImageToImageEXT",
    /*  281 */ "vkCopyImageToMemoryEXT",
    /*  282 */ "vkCopyMemoryToAccelerationStructureKHR",
    /*  283 */ "vkCopyMemoryToImageEXT",
    /*  284 */ "vkCopyMemoryToMicromapEXT",
    /*  285 */ "vkCopyMicromapEXT",
    /*  286 */ "vkCopyMicromapToMemoryEXT",
    /*  287 */ "vkCreateAccelerationStructureKHR",
    /*  288 */ "vkCreateAccelerationStructureNV",
    /*  289 */ "vkCreateAndroidSurfaceKHR",
    /*  290 */ "vkCreateBuffer",
    /*  291 */ "vkCreateBufferCollectionFUCHSIA",
    /*  292 */ "vkCreateBufferView",
    /*  293 */ "vkCreateCommandPool",
    /*  294 */ "vkCreateComputePipelines",
    /*  295 */ "vkCreateCuFunctionNVX",
    /*  296 */ "vkCreateCuModuleNVX",
    /*  297 */ "vkCreateCudaFunctionNV",
    /*  298 */ "vkCreateCudaModuleNV",
    /*  299 */ "vkCreateDebugReportCallbackEXT",
    /*  300 */ "vkCreateDebugUtilsMessengerEXT",
    /*  301 */ "vkCreateDeferredOperationKHR",
    /*  302 */ "vkCreateDescriptorPool",
    /*  303 */ "vkCreateDescriptorSetLayout",
    /*  304 */ "vkCreateDescriptorUpdateTemplate",
    /*  305 */ "vkCreateDescriptorUpdateTemplateKHR",
    /*  306 */ "vkCreateDevice",
    /*  307 */ "vkCreateDirectFBSurfaceEXT",
    /*  308 */ "vkCreateDisplayModeKHR",
    /*  309 */ "vkCreateDisplayPlaneSurfaceKHR",
    /*  310 */ "vkCreateEvent",
    /*  311 */ "vkCreateExecutionGraphPipelinesAMDX",
    /*  312 */ "vkCreateFence",
    /*  313 */ "vkCreateFramebuffer",
    /*  314 */ "vkCreateGraphicsPipelines",
    /*  315 */ "vkCreateHeadlessSurfaceEXT",
    /*  316 */ "vkCreateIOSSurfaceMVK",
    /*  317 */ "vkCreateImage",
    /*  318 */ "vkCreateImagePipeSurfaceFUCHSIA",
    /*  319 */ "vkCreateImageView",
    /*  320 */ "vkCreateIndirectCommandsLayoutNV",
    /*  321 */ "vkCreateInstance",
    /*  322 */ "vkCreateMacOSSurfaceMVK",
    /*  323 */ "vkCreateMetalSurfaceEXT",
    /*  324 */ "vkCreateMicromapEXT",
    /*  325 */ "vkCreateOpticalFlowSessionNV",
    /*  326 */ "vkCreatePipelineBinariesKHR",
    /*  327 */ "vkCreatePipelineCache",
    /*  328 */ "vkCreatePipelineLayout",
    /*  329 */ "vkCreatePrivateDataSlot",
    /*  330 */ "vkCreatePrivateDataSlotEXT",
    /*  331 */ "vkCreateQueryPool",
    /*  332 */ "vkCreateRayTracingPipelinesKHR",
    /*  333 */ "vkCreateRayTracingPipelinesNV",
    /*  334 */ "vkCreateRenderPass",
    /*  335 */ "vkCreateRenderPass2",
    /*  336 */ "vkCreateRenderPass2KHR",
    /*  337 */ "vkCreateSampler",
    /*  338 */ "vkCreateSamplerYcbcrConversion",
    /*  339 */ "vkCreateSamplerYcbcrConversionKHR",
    /*  340 */ "vkCreateScreenSurfaceQNX",
    /*  341 */ "vkCreateSemaphore",
    /*  342 */ "vkCreateShaderModule",
    /*  343 */ "vkCreateShadersEXT",
    /*  344 */ "vkCreateSharedSwapchainsKHR",
    /*  345 */ "vkCreateStreamDescriptorSurfaceGGP",
    /*  346 */ "vkCreateSwapchainKHR",
    /*  347 */ "vkCreateValidationCacheEXT",
    /*  348 */ "vkCreateViSurfaceNN",
    /*  349 */ "vkCreateVideoSessionKHR",
    /*  350 */ "vkCreateVideoSessionParametersKHR",
    /*  351 */ "vkCreateWaylandSurfaceKHR",
    /*  352 */ "vkCreateWin32SurfaceKHR",
    /*  353 */ "vkCreateXcbSurfaceKHR",
    /*  354 */ "vkCreateXlibSurfaceKHR",
    /*  355 */ "vkDebugMarkerSetObjectNameEXT",
    /*  356 */ "vkDebugMarkerSetObjectTagEXT",
    /*  357 */ "vkDebugReportMessageEXT",
    /*  358 */ "vkDeferredOperationJoinKHR",
    /*  359 */ "vkDestroyAccelerationStructureKHR",
    /*  360 */ "vkDestroyAccelerationStructureNV",
    /*  361 */ "vkDestroyBuffer",
    /*  362 */ "vkDestroyBufferCollectionFUCHSIA",
    /*  363 */ "vkDestroyBufferView",
    /*  364 */ "vkDestroyCommandPool",
    /*  365 */ "vkDestroyCuFunctionNVX",
    /*  366 */ "vkDestroyCuModuleNVX",
    /*  367 */ "vkDestroyCudaFunctionNV",
    /*  368 */ "vkDestroyCudaModuleNV",
    /*  369 */ "vkDestroyDebugReportCallbackEXT",
    /*  370 */ "vkDestroyDebugUtilsMessengerEXT",
    /*  371 */ "vkDestroyDeferredOperationKHR",
    /*  372 */ "vkDestroyDescriptorPool",
    /*  373 */ "vkDestroyDescriptorSetLayout",
    /*  374 */ "vkDestroyDescriptorUpdateTemplate",
    /*  375 */ "vkDestroyDescriptorUpdateTemplateKHR",
    /*  376 */ "vkDestroyDevice",
    /*  377 */ "vkDestroyEvent",
    /*  378 */ "vkDestroyFence",
    /*  379 */ "vkDestroyFramebuffer",
    /*  380 */ "vkDestroyImage",
    /*  381 */ "vkDestroyImageView",
    /*  382 */ "vkDestroyIndirectCommandsLayoutNV",
    /*  383 */ "vkDestroyInstance",
    /*  384 */ "vkDestroyMicromapEXT",
    /*  385 */ "vkDestroyOpticalFlowSessionNV",
    /*  386 */ "vkDestroyPipeline",
    /*  387 */ "vkDestroyPipelineBinaryKHR",
    /*  388 */ "vkDestroyPipelineCache",
    /*  389 */ "vkDestroyPipelineLayout",
    /*  390 */ "vkDestroyPrivateDataSlot",
    /*  391 */ "vkDestroyPrivateDataSlotEXT",
    /*  392 */ "vkDestroyQueryPool",
    /*  393 */ "vkDestroyRenderPass",
    /*  394 */ "vkDestroySampler",
    /*  395 */ "vkDestroySamplerYcbcrConversion",
    /*  396 */ "vkDestroySamplerYcbcrConversionKHR",
    /*  397 */ "vkDestroySemaphore",
    /*  398 */ "vkDestroyShaderEXT",
    /*  399 */ "vkDestroyShaderModule",
    /*  400 */ "vkDestroySurfaceKHR",
    /*  401 */ "vkDestroySwapchainKHR",
    /*  402 */ "vkDestroyValidationCacheEXT",
    /*  403 */ "vkDestroyVideoSessionKHR",
    /*  404 */ "vkDestroyVideoSessionParametersKHR",
    /*  405 */ "vkDeviceWaitIdle",
    /*  406 */ "vkDisplayPowerControlEXT",
    /*  407 */ "vkEndCommandBuffer",
    /*  408 */ "vkEnumerateDeviceExtensionProperties",
    /*  409 */ "vkEnumerateDeviceLayerProperties",
    /*  410 */ "vkEnumerateInstanceExtensionProperties",
    /*  411 */ "vkEnumerateInstanceLayerProperties",
    /*  412 */ "vkEnumerateInstanceVersion",
    /*  413 */ "vkEnumeratePhysicalDeviceGroups",
    /*  414 */ "vkEnumeratePhysicalDeviceGroupsKHR",
    /*  415 */ "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR",
    /*  416 */ "vkEnumeratePhysicalDevices",
    /*  417 */ "vkExportMetalObjectsEXT",
    /*  418 */ "vkFlushMappedMemoryRanges",
    /*  419 */ "vkFreeCommandBuffers",
    /*  420 */ "vkFreeDescriptorSets",
    /*  421 */ "vkFreeMemory",
    /*  422 */ "vkGetAccelerationStructureBuildSizesKHR",
    /*  423 */ "vkGetAccelerationStructureDeviceAddressKHR",
    /*  424 */ "vkGetAccelerationStructureHandleNV",
    /*  425 */ "vkGetAccelerationStructureMemoryRequirementsNV",
    /*  426 */ "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT",
    /*  427 */ "vkGetAndroidHardwareBufferPropertiesANDROID",
    /*  428 */ "vkGetBufferCollectionPropertiesFUCHSIA",
    /*  429 */ "vkGetBufferDeviceAddress",
    /*  430 */ "vkGetBufferDeviceAddressEXT",
    /*  431 */ "vkGetBufferDeviceAddressKHR",
    /*  432 */ "vkGetBufferMemoryRequirements",
    /*  433 */ "vkGetBufferMemoryRequirements2",
    /*  434 */ "vkGetBufferMemoryRequirements2KHR",
    /*  435 */ "vkGetBufferOpaqueCaptureAddress",
    /*  436 */ "vkGetBufferOpaqueCaptureAddressKHR",
    /*  437 */ "vkGetBufferOpaqueCaptureDescriptorDataEXT",
    /*  438 */ "vkGetCalibratedTimestampsEXT",
    /*  439 */ "vkGetCalibratedTimestampsKHR",
    /*  440 */ "vkGetCudaModuleCacheNV",
    /*  441 */ "vkGetDeferredOperationMaxConcurrencyKHR",
    /*  442 */ "vkGetDeferredOperationResultKHR",
    /*  443 */ "vkGetDescriptorEXT",
    /*  444 */ "vkGetDescriptorSetHostMappingVALVE",
    /*  445 */ "vkGetDescriptorSetLayoutBindingOffsetEXT",
    /*  446 */ "vkGetDescriptorSetLayoutHostMappingInfoVALVE",
    /*  447 */ "vkGetDescriptorSetLayoutSizeEXT",
    /*  448 */ "vkGetDescriptorSetLayoutSupport",
    /*  449 */ "vkGetDescriptorSetLayoutSupportKHR",
    /*  450 */ "vkGetDeviceAccelerationStructureCompatibilityKHR",
    /*  451 */ "vkGetDeviceBufferMemoryRequirements",
    /*  452 */ "vkGetDeviceBufferMemoryRequirementsKHR",
    /*  453 */ "vkGetDeviceFaultInfoEXT",
    /*  454 */ "vkGetDeviceGroupPeerMemoryFeatures",
    /*  455 */ "vkGetDeviceGroupPeerMemoryFeaturesKHR",
    /*  456 */ "vkGetDeviceGroupPresentCapabilitiesKHR",
    /*  457 */ "vkGetDeviceGroupSurfacePresentModes2EXT",
    /*  458 */ "vkGetDeviceGroupSurfacePresentModesKHR",
    /*  459 */ "vkGetDeviceImageMemoryRequirements",
    /*  460 */ "vkGetDeviceImageMemoryRequirementsKHR",
    /*  461 */ "vkGetDeviceImageSparseMemoryRequirements",
    /*  462 */ "vkGetDeviceImageSparseMemoryRequirementsKHR",
    /*  463 */ "vkGetDeviceImageSubresourceLayoutKHR",
    /*  464 */ "vkGetDeviceMemoryCommitment",
    /*  465 */ "vkGetDeviceMemoryOpaqueCaptureAddress",
    /*  466 */ "vkGetDeviceMemoryOpaqueCaptureAddressKHR",
    /*  467 */ "vkGetDeviceMicromapCompatibilityEXT",
    /*  468 */ "vkGetDeviceProcAddr",
    /*  469 */ "vkGetDeviceQueue",
    /*  470 */ "vkGetDeviceQueue2",
    /*  471 */ "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI",
    /*  472 */ "vkGetDisplayModeProperties2KHR",
    /*  473 */ "vkGetDisplayModePropertiesKHR",
    /*  474 */ "vkGetDisplayPlaneCapabilities2KHR",
    /*  475 */ "vkGetDisplayPlaneCapabilitiesKHR",
    /*  476 */ "vkGetDisplayPlaneSupportedDisplaysKHR",
    /*  477 */ "vkGetDrmDisplayEXT",
    /*  478 */ "vkGetDynamicRenderingTilePropertiesQCOM",
    /*  479 */ "vkGetEncodedVideoSessionParametersKHR",
    /*  480 */ "vkGetEventStatus",
    /*  481 */ "vkGetExecutionGraphPipelineNodeIndexAMDX",
    /*  482 */ "vkGetExecutionGraphPipelineScratchSizeAMDX",
    /*  483 */ "vkGetFenceFdKHR",
    /*  484 */ "vkGetFenceStatus",
    /*  485 */ "vkGetFenceWin32HandleKHR",
    /*  486 */ "vkGetFramebufferTilePropertiesQCOM",
    /*  487 */ "vkGetGeneratedCommandsMemoryRequirementsNV",
    /*  488 */ "vkGetImageDrmFormatModifierPropertiesEXT",
    /*  489 */ "vkGetImageMemoryRequirements",
    /*  490 */ "vkGetImageMemoryRequirements2",
    /*  491 */ "vkGetImageMemoryRequirements2KHR",
    /*  492 */ "vkGetImageOpaqueCaptureDescriptorDataEXT",
    /*  493 */ "vkGetImageSparseMemoryRequirements",
    /*  494 */ "vkGetImageSparseMemoryRequirements2",
    /*  495 */ "vkGetImageSparseMemoryRequirements2KHR",
    /*  496 */ "vkGetImageSubresourceLayout",
    /*  497 */ "vkGetImageSubresourceLayout2EXT",
    /*  498 */ "vkGetImageSubresourceLayout2KHR",
    /*  499 */ "vkGetImageViewAddressNVX",
    /*  500 */ "vkGetImageViewHandleNVX",
    /*  501 */ "vkGetImageViewOpaqueCaptureDescriptorDataEXT",
    /*  502 */ "vkGetInstanceProcAddr",
    /*  503 */ "vkGetLatencyTimingsNV",
    /*  504 */ "vkGetMemoryAndroidHardwareBufferANDROID",
    /*  505 */ "vkGetMemoryFdKHR",
    /*  506 */ "vkGetMemoryFdPropertiesKHR",
    /*  507 */ "vkGetMemoryHostPointerPropertiesEXT",
    /*  508 */ "vkGetMemoryRemoteAddressNV",
    /*  509 */ "vkGetMemoryWin32HandleKHR",
    /*  510 */ "vkGetMemoryWin32HandleNV",
    /*  511 */ "vkGetMemoryWin32HandlePropertiesKHR",
    /*  512 */ "vkGetMemoryZirconHandleFUCHSIA",
    /*  513 */ "vkGetMemoryZirconHandlePropertiesFUCHSIA",
    /*  514 */ "vkGetMicromapBuildSizesEXT",
    /*  515 */ "vkGetPastPresentationTimingGOOGLE",
    /*  516 */ "vkGetPerformanceParameterINTEL",
    /*  517 */ "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT",
    /*  518 */ "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR",
    /*  519 */ "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR",
    /*  520 */ "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV",
    /*  521 */ "vkGetPhysicalDeviceDirectFBPresentationSupportEXT",
    /*  522 */ "vkGetPhysicalDeviceDisplayPlaneProperties2KHR",
    /*  523 */ "vkGetPhysicalDeviceDisplayPlanePropertiesKHR",
    /*  524 */ "vkGetPhysicalDeviceDisplayProperties2KHR",
    /*  525 */ "vkGetPhysicalDeviceDisplayPropertiesKHR",
    /*  526 */ "vkGetPhysicalDeviceExternalBufferProperties",
    /*  527 */ "vkGetPhysicalDeviceExternalBufferPropertiesKHR",
    /*  528 */ "vkGetPhysicalDeviceExternalFenceProperties",
    /*  529 */ "vkGetPhysicalDeviceExternalFencePropertiesKHR",
    /*  530 */ "vkGetPhysicalDeviceExternalImageFormatPropertiesNV",
    /*  531 */ "vkGetPhysicalDeviceExternalSemaphoreProperties",
    /*  532 */ "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR",
    /*  533 */ "vkGetPhysicalDeviceFeatures",
    /*  534 */ "vkGetPhysicalDeviceFeatures2",
    /*  535 */ "vkGetPhysicalDeviceFeatures2KHR",
    /*  536 */ "vkGetPhysicalDeviceFormatProperties",
    /*  537 */ "vkGetPhysicalDeviceFormatProperties2",
    /*  538 */ "vkGetPhysicalDeviceFormatProperties2KHR",
    /*  539 */ "vkGetPhysicalDeviceFragmentShadingRatesKHR",
    /*  540 */ "vkGetPhysicalDeviceImageFormatProperties",
    /*  541 */ "vkGetPhysicalDeviceImageFormatProperties2",
    /*  542 */ "vkGetPhysicalDeviceImageFormatProperties2KHR",
    /*  543 */ "vkGetPhysicalDeviceMemoryProperties",
    /*  544 */ "vkGetPhysicalDeviceMemoryProperties2",
    /*  545 */ "vkGetPhysicalDeviceMemoryProperties2KHR",
    /*  546 */ "vkGetPhysicalDeviceMultisamplePropertiesEXT",
    /*  547 */ "vkGetPhysicalDeviceOpticalFlowImageFormatsNV",
    /*  548 */ "vkGetPhysicalDevicePresentRectanglesKHR",
    /*  549 */ "vkGetPhysicalDeviceProperties",
    /*  550 */ "vkGetPhysicalDeviceProperties2",
    /*  551 */ "vkGetPhysicalDeviceProperties2KHR",
    /*  552 */ "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR",
    /*  553 */ "vkGetPhysicalDeviceQueueFamilyProperties",
    /*  554 */ "vkGetPhysicalDeviceQueueFamilyProperties2",
    /*  555 */ "vkGetPhysicalDeviceQueueFamilyProperties2KHR",
    /*  556 */ "vkGetPhysicalDeviceScreenPresentationSupportQNX",
    /*  557 */ "vkGetPhysicalDeviceSparseImageFormatProperties",
    /*  558 */ "vkGetPhysicalDeviceSparseImageFormatProperties2",
    /*  559 */ "vkGetPhysicalDeviceSparseImageFormatProperties2KHR",
    /*  560 */ "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV",
    /*  561 */ "vkGetPhysicalDeviceSurfaceCapabilities2EXT",
    /*  562 */ "vkGetPhysicalDeviceSurfaceCapabilities2KHR",
    /*  563 */ "vkGetPhysicalDeviceSurfaceCapabilitiesKHR",
    /*  564 */ "vkGetPhysicalDeviceSurfaceFormats2KHR",
    /*  565 */ "vkGetPhysicalDeviceSurfaceFormatsKHR",
    /*  566 */ "vkGetPhysicalDeviceSurfacePresentModes2EXT",
    /*  567 */ "vkGetPhysicalDeviceSurfacePresentModesKHR",
    /*  568 */ "vkGetPhysicalDeviceSurfaceSupportKHR",
    /*  569 */ "vkGetPhysicalDeviceToolProperties",
    /*  570 */ "vkGetPhysicalDeviceToolPropertiesEXT",
    /*  571 */ "vkGetPhysicalDeviceVideoCapabilitiesKHR",
    /*  572 */ "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR",
    /*  573 */ "vkGetPhysicalDeviceVideoFormatPropertiesKHR",
    /*  574 */ "vkGetPhysicalDeviceWaylandPresentationSupportKHR",
    /*  575 */ "vkGetPhysicalDeviceWin32PresentationSupportKHR",
    /*  576 */ "vkGetPhysicalDeviceXcbPresentationSupportKHR",
    /*  577 */ "vkGetPhysicalDeviceXlibPresentationSupportKHR",
    /*  578 */ "vkGetPipelineBinaryDataKHR",
    /*  579 */ "vkGetPipelineCacheData",
    /*  580 */ "vkGetPipelineExecutableInternalRepresentationsKHR",
    /*  581 */ "vkGetPipelineExecutablePropertiesKHR",
    /*  582 */ "vkGetPipelineExecutableStatisticsKHR",
    /*  583 */ "vkGetPipelineIndirectDeviceAddressNV",
    /*  584 */ "vkGetPipelineIndirectMemoryRequirementsNV",
    /*  585 */ "vkGetPipelineKeyKHR",
    /*  586 */ "vkGetPipelinePropertiesEXT",
    /*  587 */ "vkGetPrivateData",
    /*  588 */ "vkGetPrivateDataEXT",
    /*  589 */ "vkGetQueryPoolResults",
    /*  590 */ "vkGetQueueCheckpointData2NV",
    /*  591 */ "vkGetQueueCheckpointDataNV",
    /*  592 */ "vkGetRandROutputDisplayEXT",
    /*  593 */ "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR",
    /*  594 */ "vkGetRayTracingShaderGroupHandlesKHR",
    /*  595 */ "vkGetRayTracingShaderGroupHandlesNV",
    /*  596 */ "vkGetRayTracingShaderGroupStackSizeKHR",
    /*  597 */ "vkGetRefreshCycleDurationGOOGLE",
    /*  598 */ "vkGetRenderAreaGranularity",
    /*  599 */ "vkGetRenderingAreaGranularityKHR",
    /*  600 */ "vkGetSamplerOpaqueCaptureDescriptorDataEXT",
    /*  601 */ "vkGetScreenBufferPropertiesQNX",
    /*  602 */ "vkGetSemaphoreCounterValue",
    /*  603 */ "vkGetSemaphoreCounterValueKHR",
    /*  604 */ "vkGetSemaphoreFdKHR",
    /*  605 */ "vkGetSemaphoreWin32HandleKHR",
    /*  606 */ "vkGetSemaphoreZirconHandleFUCHSIA",
    /*  607 */ "vkGetShaderBinaryDataEXT",
    /*  608 */ "vkGetShaderInfoAMD",
    /*  609 */ "vkGetShaderModuleCreateInfoIdentifierEXT",
    /*  610 */ "vkGetShaderModuleIdentifierEXT",
    /*  611 */ "vkGetSwapchainCounterEXT",
    /*  612 */ "vkGetSwapchainImagesKHR",
    /*  613 */ "vkGetSwapchainStatusKHR",
    /*  614 */ "vkGetValidationCacheDataEXT",
    /*  615 */ "vkGetVideoSessionMemoryRequirementsKHR",
    /*  616 */ "vkGetWinrtDisplayNV",
    /*  617 */ "vkImportFenceFdKHR",
    /*  618 */ "vkImportFenceWin32HandleKHR",
    /*  619 */ "vkImportSemaphoreFdKHR",
    /*  620 */ "vkImportSemaphoreWin32HandleKHR",
    /*  621 */ "vkImportSemaphoreZirconHandleFUCHSIA",
    /*  622 */ "vkInitializePerformanceApiINTEL",
    /*  623 */ "vkInvalidateMappedMemoryRanges",
    /*  624 */ "vkLatencySleepNV",
    /*  625 */ "vkMapMemory",
    /*  626 */ "vkMapMemory2KHR",
    /*  627 */ "vkMergePipelineCaches",
    /*  628 */ "vkMergeValidationCachesEXT",
    /*  629 */ "vkQueueBeginDebugUtilsLabelEXT",
    /*  630 */ "vkQueueBindSparse",
    /*  631 */ "vkQueueEndDebugUtilsLabelEXT",
    /*  632 */ "vkQueueInsertDebugUtilsLabelEXT",
    /*  633 */ "vkQueueNotifyOutOfBandNV",
    /*  634 */ "vkQueuePresentKHR",
    /*  635 */ "vkQueueSetPerformanceConfigurationINTEL",
    /*  636 */ "vkQueueSubmit",
    /*  637 */ "vkQueueSubmit2",
    /*  638 */ "vkQueueSubmit2KHR",
    /*  639 */ "vkQueueWaitIdle",
    /*  640 */ "vkRegisterDeviceEventEXT",
    /*  641 */ "vkRegisterDisplayEventEXT",
    /*  642 */ "vkReleaseCapturedPipelineDataKHR",
    /*  643 */ "vkReleaseDisplayEXT",
    /*  644 */ "vkReleaseFullScreenExclusiveModeEXT",
    /*  645 */ "vkReleasePerformanceConfigurationINTEL",
    /*  646 */ "vkReleaseProfilingLockKHR",
    /*  647 */ "vkReleaseSwapchainImagesEXT",
    /*  648 */ "vkResetCommandBuffer",
    /*  649 */ "vkResetCommandPool",
    /*  650 */ "vkResetDescriptorPool",
    /*  651 */ "vkResetEvent",
    /*  652 */ "vkResetFences",
    /*  653 */ "vkResetQueryPool",
    /*  654 */ "vkResetQueryPoolEXT",
    /*  655 */ "vkSetBufferCollectionBufferConstraintsFUCHSIA",
    /*  656 */ "vkSetBufferCollectionImageConstraintsFUCHSIA",
    /*  657 */ "vkSetDebugUtilsObjectNameEXT",
    /*  658 */ "vkSetDebugUtilsObjectTagEXT",
    /*  659 */ "vkSetDeviceMemoryPriorityEXT",
    /*  660 */ "vkSetEvent",
    /*  661 */ "vkSetHdrMetadataEXT",
    /*  662 */ "vkSetLatencyMarkerNV",
    /*  663 */ "vkSetLatencySleepModeNV",
    /*  664 */ "vkSetLocalDimmingAMD",
    /*  665 */ "vkSetPrivateData",
    /*  666 */ "vkSetPrivateDataEXT",
    /*  667 */ "vkSignalSemaphore",
    /*  668 */ "vkSignalSemaphoreKHR",
    /*  669 */ "vkSubmitDebugUtilsMessageEXT",
    /*  670 */ "vkTransitionImageLayoutEXT",
    /*  671 */ "vkTrimCommandPool",
    /*  672 */ "vkTrimCommandPoolKHR",
    /*  673 */ "vkUninitializePerformanceApiINTEL",
    /*  674 */ "vkUnmapMemory",
    /*  675 */ "vkUnmapMemory2KHR",
    /*  676 */ "vkUpdateDescriptorSetWithTemplate",
    /*  677 */ "vkUpdateDescriptorSetWithTemplateKHR",
    /*  678 */ "vkUpdateDescriptorSets",
    /*  679 */ "vkUpdateVideoSessionParametersKHR",
    /*  680 */ "vkWaitForFences",
    /*  681 */ "vkWaitForPresentKHR",
    /*  682 */ "vkWaitSemaphores",
    /*  683 */ "vkWaitSemaphoresKHR",
    /*  684 */ "vkWriteAccelerationStructuresPropertiesKHR",
    /*  685 */ "vkWriteMicromapsPropertiesEXT"
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
    /*   26 */ 0x0afcd59fd2af6286, /* VK_ARM_rasterization_order_attachment_access */
    /*   27 */ 0x099508890a72c586, /* VK_ARM_render_pass_striped */
    /*   28 */ 0xcb5ebd8b3c00874c, /* VK_ARM_scheduling_controls */
    /*   29 */ 0x6d66a5a00c62648d, /* VK_ARM_shader_core_builtins */
    /*   30 */ 0x42f58e0f0c034d62, /* VK_ARM_shader_core_properties */
    /*   31 */ 0x9452c6992583027b, /* VK_EXT_4444_formats */
    /*   32 */ 0xc78e4b8ee4076491, /* VK_EXT_acquire_drm_display */
    /*   33 */ 0xf320bc0da89095cc, /* VK_EXT_acquire_xlib_display */
    /*   34 */ 0x1f2679f2f103d431, /* VK_EXT_astc_decode_mode */
    /*   35 */ 0xf27c39b3a1b079ad, /* VK_EXT_attachment_feedback_loop_dynamic_state */
    /*   36 */ 0x74d9e22c0880d05b, /* VK_EXT_attachment_feedback_loop_layout */
    /*   37 */ 0xbf40b1c2e2a175ca, /* VK_EXT_blend_operation_advanced */
    /*   38 */ 0xa7ae01d75b03a5fa, /* VK_EXT_border_color_swizzle */
    /*   39 */ 0x8cadd6ee8baeb7b6, /* VK_EXT_buffer_device_address */
    /*   40 */ 0xe53030d618c508b9, /* VK_EXT_calibrated_timestamps */
    /*   41 */ 0x1821c534e43e8bc2, /* VK_EXT_color_write_enable */
    /*   42 */ 0x3acaa19dcdfa4838, /* VK_EXT_conditional_rendering */
    /*   43 */ 0xbc479489c58aba55, /* VK_EXT_conservative_rasterization */
    /*   44 */ 0xd41fdd03d1591c42, /* VK_EXT_custom_border_color */
    /*   45 */ 0x13dd727d73e5c438, /* VK_EXT_debug_marker */
    /*   46 */ 0xefc5d6f86f5274aa, /* VK_EXT_debug_report */
    /*   47 */ 0x1f4cc1384fdd3124, /* VK_EXT_debug_utils */
    /*   48 */ 0x4334a6b5b2a8bcdf, /* VK_EXT_depth_bias_control */
    /*   49 */ 0x42e03d02e07ee602, /* VK_EXT_depth_clamp_zero_one */
    /*   50 */ 0xc46ca287fec7bfa2, /* VK_EXT_depth_clip_control */
    /*   51 */ 0xb225ae836596c941, /* VK_EXT_depth_clip_enable */
    /*   52 */ 0x683e05b7c95cf871, /* VK_EXT_depth_range_unrestricted */
    /*   53 */ 0xff983b309bdf4f8f, /* VK_EXT_descriptor_buffer */
    /*   54 */ 0x8ed9a50d9652d13a, /* VK_EXT_descriptor_indexing */
    /*   55 */ 0x71042286279bf266, /* VK_EXT_device_address_binding_report */
    /*   56 */ 0x44712682d623c6ec, /* VK_EXT_device_fault */
    /*   57 */ 0xfc8708a7a55a3b72, /* VK_EXT_device_memory_report */
    /*   58 */ 0x3d21adc07dc92de9, /* VK_EXT_direct_mode_display */
    /*   59 */ 0x2f377620d96a0b95, /* VK_EXT_directfb_surface */
    /*   60 */ 0x6c4b18b294f729e9, /* VK_EXT_discard_rectangles */
    /*   61 */ 0x2bd79b14ec35b405, /* VK_EXT_display_control */
    /*   62 */ 0xf82da0558a082445, /* VK_EXT_display_surface_counter */
    /*   63 */ 0x6c84fccd28668412, /* VK_EXT_dynamic_rendering_unused_attachments */
    /*   64 */ 0x405b3a7704a014a0, /* VK_EXT_extended_dynamic_state */
    /*   65 */ 0x09050069bac4e50b, /* VK_EXT_extended_dynamic_state2 */
    /*   66 */ 0x3e6696389e531962, /* VK_EXT_extended_dynamic_state3 */
    /*   67 */ 0x204d4d8537dc240c, /* VK_EXT_external_memory_acquire_unmodified */
    /*   68 */ 0xfbe83be92d0dc3e1, /* VK_EXT_external_memory_dma_buf */
    /*   69 */ 0xe730e90349447245, /* VK_EXT_external_memory_host */
    /*   70 */ 0x2ff4c771bf02a660, /* VK_EXT_filter_cubic */
    /*   71 */ 0xdd63dbab93498a89, /* VK_EXT_fragment_density_map */
    /*   72 */ 0x639aaec72634d6cc, /* VK_EXT_fragment_density_map2 */
    /*   73 */ 0xec38db4912e9aa39, /* VK_EXT_fragment_shader_interlock */
    /*   74 */ 0x4bed293561f471c5, /* VK_EXT_frame_boundary */
    /*   75 */ 0xf888a39f24346db4, /* VK_EXT_full_screen_exclusive */
    /*   76 */ 0x026fba6d706537f5, /* VK_EXT_global_priority */
    /*   77 */ 0x49240b90779ad742, /* VK_EXT_global_priority_query */
    /*   78 */ 0xe612048b33a20737, /* VK_EXT_graphics_pipeline_library */
    /*   79 */ 0xd140703366300180, /* VK_EXT_hdr_metadata */
    /*   80 */ 0xfc97df8c7f5cb62e, /* VK_EXT_headless_surface */
    /*   81 */ 0x15c6d3b4db750060, /* VK_EXT_host_image_copy */
    /*   82 */ 0xcc9a1964d5f92ead, /* VK_EXT_host_query_reset */
    /*   83 */ 0x992053b93ca7369a, /* VK_EXT_image_2d_view_of_3d */
    /*   84 */ 0xac673544b231a330, /* VK_EXT_image_compression_control */
    /*   85 */ 0xfc267e5b08be3c88, /* VK_EXT_image_compression_control_swapchain */
    /*   86 */ 0x5d78e7153c62776c, /* VK_EXT_image_drm_format_modifier */
    /*   87 */ 0xe918548d9d09bdf5, /* VK_EXT_image_robustness */
    /*   88 */ 0x10ea5ce8b7b462c6, /* VK_EXT_image_sliced_view_of_3d */
    /*   89 */ 0x5d125c6144d30072, /* VK_EXT_image_view_min_lod */
    /*   90 */ 0x66bb737b7652d71d, /* VK_EXT_index_type_uint8 */
    /*   91 */ 0x59f61f1cc23145ee, /* VK_EXT_inline_uniform_block */
    /*   92 */ 0x9ba2edc52691fc07, /* VK_EXT_layer_settings */
    /*   93 */ 0xa45ec0ff789f2882, /* VK_EXT_legacy_dithering */
    /*   94 */ 0x93eebd73e097d983, /* VK_EXT_legacy_vertex_attributes */
    /*   95 */ 0x98daf38a4cd796bc, /* VK_EXT_line_rasterization */
    /*   96 */ 0xca3cb4186d57fa40, /* VK_EXT_load_store_op_none */
    /*   97 */ 0xc92882ba73a7ad8a, /* VK_EXT_map_memory_placed */
    /*   98 */ 0xa642b55c0f467f26, /* VK_EXT_memory_budget */
    /*   99 */ 0xdf03e1a0a38154d2, /* VK_EXT_memory_priority */
    /*  100 */ 0x38a2a90e0a820189, /* VK_EXT_mesh_shader */
    /*  101 */ 0x6bcff1cd8cf418f2, /* VK_EXT_metal_objects */
    /*  102 */ 0x60fc707b7c19679c, /* VK_EXT_metal_surface */
    /*  103 */ 0x60ca462964877ba5, /* VK_EXT_multi_draw */
    /*  104 */ 0x60c608294e99436f, /* VK_EXT_multisampled_render_to_single_sampled */
    /*  105 */ 0x333da01be07c65e4, /* VK_EXT_mutable_descriptor_type */
    /*  106 */ 0x4f43f294a30fc75d, /* VK_EXT_nested_command_buffer */
    /*  107 */ 0x6cf77b70db09b037, /* VK_EXT_non_seamless_cube_map */
    /*  108 */ 0xb5bdb97dc49555ef, /* VK_EXT_opacity_micromap */
    /*  109 */ 0x74062e5990db1eeb, /* VK_EXT_pageable_device_local_memory */
    /*  110 */ 0xe60ea5fa872ffa4b, /* VK_EXT_pci_bus_info */
    /*  111 */ 0x087b96c0fac7f2e9, /* VK_EXT_physical_device_drm */
    /*  112 */ 0xae186881e629f533, /* VK_EXT_pipeline_creation_cache_control */
    /*  113 */ 0xd5ed321620183ae4, /* VK_EXT_pipeline_creation_feedback */
    /*  114 */ 0xf2497807f1195d03, /* VK_EXT_pipeline_library_group_handles */
    /*  115 */ 0x97816799b0ea2a08, /* VK_EXT_pipeline_properties */
    /*  116 */ 0x0bec2c70abec6edf, /* VK_EXT_pipeline_protected_access */
    /*  117 */ 0x3726d3c286b23305, /* VK_EXT_pipeline_robustness */
    /*  118 */ 0x578e2a9cdc320baa, /* VK_EXT_post_depth_coverage */
    /*  119 */ 0x4792bf3539da07a0, /* VK_EXT_primitive_topology_list_restart */
    /*  120 */ 0x4de3fc9eb140d3c9, /* VK_EXT_primitives_generated_query */
    /*  121 */ 0x66832604ff1fb25a, /* VK_EXT_private_data */
    /*  122 */ 0x3632448643e01277, /* VK_EXT_provoking_vertex */
    /*  123 */ 0xc3a80f57bc34acf0, /* VK_EXT_queue_family_foreign */
    /*  124 */ 0x9c47749ad3103e99, /* VK_EXT_rasterization_order_attachment_access */
    /*  125 */ 0xe3b61ff718cac048, /* VK_EXT_rgba10x6_formats */
    /*  126 */ 0x267337703fbb9802, /* VK_EXT_robustness2 */
    /*  127 */ 0xa2f0c46d62bffbbd, /* VK_EXT_sample_locations */
    /*  128 */ 0x35bc8d45855c9ddd, /* VK_EXT_sampler_filter_minmax */
    /*  129 */ 0x0fe7c2504b67f76e, /* VK_EXT_scalar_block_layout */
    /*  130 */ 0x21c315365bdd91c1, /* VK_EXT_separate_stencil_usage */
    /*  131 */ 0x39152af17d406387, /* VK_EXT_shader_atomic_float */
    /*  132 */ 0xfa5bf73b09f1814a, /* VK_EXT_shader_atomic_float2 */
    /*  133 */ 0x1313743aff740ea6, /* VK_EXT_shader_demote_to_helper_invocation */
    /*  134 */ 0xdbd208469e466661, /* VK_EXT_shader_image_atomic_int64 */
    /*  135 */ 0x0fdb11284e798630, /* VK_EXT_shader_module_identifier */
    /*  136 */ 0x01d57626cc2cb88b, /* VK_EXT_shader_object */
    /*  137 */ 0xd98565c5e8cff707, /* VK_EXT_shader_replicated_composites */
    /*  138 */ 0x1d5f02c289908dc6, /* VK_EXT_shader_stencil_export */
    /*  139 */ 0x3434e0e3856c3974, /* VK_EXT_shader_subgroup_ballot */
    /*  140 */ 0x414fe291cad1b8c2, /* VK_EXT_shader_subgroup_vote */
    /*  141 */ 0x15c81e1e3330c87a, /* VK_EXT_shader_tile_image */
    /*  142 */ 0x3ab7ae29a67149aa, /* VK_EXT_shader_viewport_index_layer */
    /*  143 */ 0xf8847bcd6077bcfc, /* VK_EXT_subgroup_size_control */
    /*  144 */ 0xc0a98929a3b5a629, /* VK_EXT_subpass_merge_feedback */
    /*  145 */ 0x745c764090230a6a, /* VK_EXT_surface_maintenance1 */
    /*  146 */ 0xaf7db52f12522284, /* VK_EXT_swapchain_colorspace */
    /*  147 */ 0xb8a530fd9b6e7826, /* VK_EXT_swapchain_maintenance1 */
    /*  148 */ 0x93820a855076e9ba, /* VK_EXT_texel_buffer_alignment */
    /*  149 */ 0xd54a2906947894c3, /* VK_EXT_texture_compression_astc_hdr */
    /*  150 */ 0xa176a37fe21bf722, /* VK_EXT_tooling_info */
    /*  151 */ 0x2c77e64693cba64b, /* VK_EXT_transform_feedback */
    /*  152 */ 0xd43b5b3257938a0c, /* VK_EXT_validation_cache */
    /*  153 */ 0x32e3bcc79655ff35, /* VK_EXT_validation_features */
    /*  154 */ 0x5dbef52d8325ef00, /* VK_EXT_validation_flags */
    /*  155 */ 0x41bd31eed71de48d, /* VK_EXT_vertex_attribute_divisor */
    /*  156 */ 0xdba593667f2b15d8, /* VK_EXT_vertex_input_dynamic_state */
    /*  157 */ 0xdc68cb4b50c6a206, /* VK_EXT_ycbcr_2plane_444_formats */
    /*  158 */ 0x7f0e4b169ce6683e, /* VK_EXT_ycbcr_image_arrays */
    /*  159 */ 0x4ad21727cd459ae0, /* VK_FUCHSIA_buffer_collection */
    /*  160 */ 0x39a61a1dde950a7e, /* VK_FUCHSIA_external_memory */
    /*  161 */ 0xf64c61e8709735f7, /* VK_FUCHSIA_external_semaphore */
    /*  162 */ 0x78bbdf52d016b408, /* VK_FUCHSIA_imagepipe_surface */
    /*  163 */ 0x7f2da9be6e1b04db, /* VK_GGP_frame_token */
    /*  164 */ 0xcd04d110dd619891, /* VK_GGP_stream_descriptor_surface */
    /*  165 */ 0x66d124637ca67c9b, /* VK_GOOGLE_decorate_string */
    /*  166 */ 0xd317975f41d1a234, /* VK_GOOGLE_display_timing */
    /*  167 */ 0x434a8c02c305c9d2, /* VK_GOOGLE_hlsl_functionality1 */
    /*  168 */ 0xdb384c83fb23b324, /* VK_GOOGLE_surfaceless_query */
    /*  169 */ 0x8ea5be2adce92628, /* VK_GOOGLE_user_type */
    /*  170 */ 0x1251619c17f44f75, /* VK_HUAWEI_cluster_culling_shader */
    /*  171 */ 0x23cb6d9b631ae3de, /* VK_HUAWEI_invocation_mask */
    /*  172 */ 0x7a080c6eb36cfa62, /* VK_HUAWEI_subpass_shading */
    /*  173 */ 0xc831730562583c7f, /* VK_IMG_filter_cubic */
    /*  174 */ 0x2770027508eb9598, /* VK_IMG_format_pvrtc */
    /*  175 */ 0xb0257135e659f035, /* VK_IMG_relaxed_line_rasterization */
    /*  176 */ 0xde48a4b9c28f1a76, /* VK_INTEL_performance_query */
    /*  177 */ 0x1cdbef97960a8e84, /* VK_INTEL_shader_integer_functions2 */
    /*  178 */ 0x8febc131b31f03a7, /* VK_KHR_16bit_storage */
    /*  179 */ 0xfc675d0c9be11933, /* VK_KHR_8bit_storage */
    /*  180 */ 0xfd487833d05a912e, /* VK_KHR_acceleration_structure */
    /*  181 */ 0x29df4e2582c4e5eb, /* VK_KHR_android_surface */
    /*  182 */ 0xc441ac340c33f00e, /* VK_KHR_bind_memory2 */
    /*  183 */ 0xed3998734610578e, /* VK_KHR_buffer_device_address */
    /*  184 */ 0xf6b15d82867a4cc7, /* VK_KHR_calibrated_timestamps */
    /*  185 */ 0x0afe9b38bfc3ce2c, /* VK_KHR_compute_shader_derivatives */
    /*  186 */ 0x2349bf032cef96df, /* VK_KHR_cooperative_matrix */
    /*  187 */ 0x8037af99654ff021, /* VK_KHR_copy_commands2 */
    /*  188 */ 0x45e78547df004126, /* VK_KHR_create_renderpass2 */
    /*  189 */ 0x78b51eb267ba222a, /* VK_KHR_dedicated_allocation */
    /*  190 */ 0x94de08b35a6241ca, /* VK_KHR_deferred_host_operations */
    /*  191 */ 0x8c49a14f4e053827, /* VK_KHR_depth_stencil_resolve */
    /*  192 */ 0xd0e490f381b744be, /* VK_KHR_descriptor_update_template */
    /*  193 */ 0xc6ca78c5b314bc87, /* VK_KHR_device_group */
    /*  194 */ 0x8585cbd14f1c0cac, /* VK_KHR_device_group_creation */
    /*  195 */ 0x2859d74f3639d0b1, /* VK_KHR_display */
    /*  196 */ 0xe6851c4675917263, /* VK_KHR_display_swapchain */
    /*  197 */ 0x0337556153ae8299, /* VK_KHR_draw_indirect_count */
    /*  198 */ 0x2fa1beee71b55c4a, /* VK_KHR_driver_properties */
    /*  199 */ 0xcec518255e3db5bd, /* VK_KHR_dynamic_rendering */
    /*  200 */ 0x3aff0fddef25484a, /* VK_KHR_dynamic_rendering_local_read */
    /*  201 */ 0x042831872b90006c, /* VK_KHR_external_fence */
    /*  202 */ 0x5f78dae679457682, /* VK_KHR_external_fence_capabilities */
    /*  203 */ 0xcd3a8c2ddf5addf6, /* VK_KHR_external_fence_fd */
    /*  204 */ 0x4c03e948c552a900, /* VK_KHR_external_fence_win32 */
    /*  205 */ 0x87d94faee5024129, /* VK_KHR_external_memory */
    /*  206 */ 0x3f3f36a8f61bdd88, /* VK_KHR_external_memory_capabilities */
    /*  207 */ 0x552d385fc1022139, /* VK_KHR_external_memory_fd */
    /*  208 */ 0x92cd58bc47a696d9, /* VK_KHR_external_memory_win32 */
    /*  209 */ 0x7e7e947a025884c1, /* VK_KHR_external_semaphore */
    /*  210 */ 0xb7268870e382881b, /* VK_KHR_external_semaphore_capabilities */
    /*  211 */ 0x089c9b49df8b6f1e, /* VK_KHR_external_semaphore_fd */
    /*  212 */ 0x014c9621dbd33d31, /* VK_KHR_external_semaphore_win32 */
    /*  213 */ 0x9310a82971542c4a, /* VK_KHR_format_feature_flags2 */
    /*  214 */ 0x2aedf5bc87e7dd6d, /* VK_KHR_fragment_shader_barycentric */
    /*  215 */ 0x8496cee01f4fa6d5, /* VK_KHR_fragment_shading_rate */
    /*  216 */ 0x6c023bc9dc523d46, /* VK_KHR_get_display_properties2 */
    /*  217 */ 0x9eb7bb6c3705f946, /* VK_KHR_get_memory_requirements2 */
    /*  218 */ 0x7685eeed9cac9798, /* VK_KHR_get_physical_device_properties2 */
    /*  219 */ 0x9b0fbb8eeee0e74b, /* VK_KHR_get_surface_capabilities2 */
    /*  220 */ 0x0bb91b137617fbef, /* VK_KHR_global_priority */
    /*  221 */ 0xfb7c493b280e7035, /* VK_KHR_image_format_list */
    /*  222 */ 0x6ba09c8a87af68ce, /* VK_KHR_imageless_framebuffer */
    /*  223 */ 0x76a0d6d17ae91b81, /* VK_KHR_incremental_present */
    /*  224 */ 0x3dde8d8eb0b76315, /* VK_KHR_index_type_uint8 */
    /*  225 */ 0x7928ca2523362ef3, /* VK_KHR_line_rasterization */
    /*  226 */ 0xc8692b97cfbe45ad, /* VK_KHR_load_store_op_none */
    /*  227 */ 0xe3c8335cc1581a67, /* VK_KHR_maintenance1 */
    /*  228 */ 0x8ffe792f51cd1450, /* VK_KHR_maintenance2 */
    /*  229 */ 0xea219cc76502a8af, /* VK_KHR_maintenance3 */
    /*  230 */ 0xa66e463f036dae4a, /* VK_KHR_maintenance4 */
    /*  231 */ 0xc5e86b535cee6698, /* VK_KHR_maintenance5 */
    /*  232 */ 0xf60b7de240a15ab4, /* VK_KHR_maintenance6 */
    /*  233 */ 0x3d59040ce3c13f21, /* VK_KHR_maintenance7 */
    /*  234 */ 0x64d252cf56a64add, /* VK_KHR_map_memory2 */
    /*  235 */ 0x5af12378bc6d7169, /* VK_KHR_multiview */
    /*  236 */ 0x1bb74dfe8d7e0b31, /* VK_KHR_performance_query */
    /*  237 */ 0x935d834a6c18d3ed, /* VK_KHR_pipeline_binary */
    /*  238 */ 0x91248c6b162c4180, /* VK_KHR_pipeline_executable_properties */
    /*  239 */ 0x039c65d87fb09ca9, /* VK_KHR_pipeline_library */
    /*  240 */ 0x28644eeb112058b6, /* VK_KHR_portability_enumeration */
    /*  241 */ 0xac06576b97f9486a, /* VK_KHR_portability_subset */
    /*  242 */ 0xe82e301141092b1e, /* VK_KHR_present_id */
    /*  243 */ 0x47954f24ddf5185e, /* VK_KHR_present_wait */
    /*  244 */ 0x2123bacd888c07ec, /* VK_KHR_push_descriptor */
    /*  245 */ 0x8bf873804879f2cf, /* VK_KHR_ray_query */
    /*  246 */ 0x9df3df162357e4b0, /* VK_KHR_ray_tracing_maintenance1 */
    /*  247 */ 0xaef707cb154a81af, /* VK_KHR_ray_tracing_pipeline */
    /*  248 */ 0x697f77ef7ba14203, /* VK_KHR_ray_tracing_position_fetch */
    /*  249 */ 0x4b17e19fd947a1d3, /* VK_KHR_relaxed_block_layout */
    /*  250 */ 0x5d5e936103817cda, /* VK_KHR_sampler_mirror_clamp_to_edge */
    /*  251 */ 0x22004cfa79ba7177, /* VK_KHR_sampler_ycbcr_conversion */
    /*  252 */ 0xba2c0ae86fd11630, /* VK_KHR_separate_depth_stencil_layouts */
    /*  253 */ 0xb16f5fd69d97f3a1, /* VK_KHR_shader_atomic_int64 */
    /*  254 */ 0xeee9708671fa7c77, /* VK_KHR_shader_clock */
    /*  255 */ 0xb35fc4bdb32f3d81, /* VK_KHR_shader_draw_parameters */
    /*  256 */ 0xab0eda6676f1fd31, /* VK_KHR_shader_expect_assume */
    /*  257 */ 0x4dad563cb513c7c9, /* VK_KHR_shader_float16_int8 */
    /*  258 */ 0x548b20a76c855b46, /* VK_KHR_shader_float_controls */
    /*  259 */ 0xa1150eef92f851e8, /* VK_KHR_shader_float_controls2 */
    /*  260 */ 0x9d14cd5379daf7cb, /* VK_KHR_shader_integer_dot_product */
    /*  261 */ 0x42aefa5598fde4ab, /* VK_KHR_shader_maximal_reconvergence */
    /*  262 */ 0xb38332d7467f8474, /* VK_KHR_shader_non_semantic_info */
    /*  263 */ 0xab3f0af6d5504bf4, /* VK_KHR_shader_quad_control */
    /*  264 */ 0x1bdfe042874be24f, /* VK_KHR_shader_relaxed_extended_instruction */
    /*  265 */ 0xcda588b0d067d48f, /* VK_KHR_shader_subgroup_extended_types */
    /*  266 */ 0xd0836c7a4d04b579, /* VK_KHR_shader_subgroup_rotate */
    /*  267 */ 0x64fbf5bc74afe199, /* VK_KHR_shader_subgroup_uniform_control_flow */
    /*  268 */ 0x6e5fde40560b40a9, /* VK_KHR_shader_terminate_invocation */
    /*  269 */ 0x7e6871b03dee137b, /* VK_KHR_shared_presentable_image */
    /*  270 */ 0x06c03c1c3db9815d, /* VK_KHR_spirv_1_4 */
    /*  271 */ 0x743f86c26df32ea2, /* VK_KHR_storage_buffer_storage_class */
    /*  272 */ 0x2c4f009293a35548, /* VK_KHR_surface */
    /*  273 */ 0xa8506d9aef558591, /* VK_KHR_surface_protected_capabilities */
    /*  274 */ 0x6cefabf4c944ccec, /* VK_KHR_swapchain */
    /*  275 */ 0x2149e839e759e400, /* VK_KHR_swapchain_mutable_format */
    /*  276 */ 0xf1cfa2ea69e6ec0e, /* VK_KHR_synchronization2 */
    /*  277 */ 0x61ed378f50459bf2, /* VK_KHR_timeline_semaphore */
    /*  278 */ 0x3334ed809879d360, /* VK_KHR_uniform_buffer_standard_layout */
    /*  279 */ 0x6146df22dcb09470, /* VK_KHR_variable_pointers */
    /*  280 */ 0xcfd1e6704e4a4227, /* VK_KHR_vertex_attribute_divisor */
    /*  281 */ 0x4ccc16568a9a2944, /* VK_KHR_video_decode_av1 */
    /*  282 */ 0x0093b60d00888052, /* VK_KHR_video_decode_h264 */
    /*  283 */ 0x4116f6bec0017e79, /* VK_KHR_video_decode_h265 */
    /*  284 */ 0x363dac5e35a2f1ee, /* VK_KHR_video_decode_queue */
    /*  285 */ 0xa77247c5899dc785, /* VK_KHR_video_encode_h264 */
    /*  286 */ 0x8b86366e33c748ee, /* VK_KHR_video_encode_h265 */
    /*  287 */ 0xdda14264a3bda234, /* VK_KHR_video_encode_queue */
    /*  288 */ 0x9fb8181989e29256, /* VK_KHR_video_maintenance1 */
    /*  289 */ 0xc3d1c9b40515a6a4, /* VK_KHR_video_queue */
    /*  290 */ 0x34899ec7a7b17614, /* VK_KHR_vulkan_memory_model */
    /*  291 */ 0x906fcab3e0d202a5, /* VK_KHR_wayland_surface */
    /*  292 */ 0x19d48609837c8701, /* VK_KHR_win32_keyed_mutex */
    /*  293 */ 0xc93557e7cef43233, /* VK_KHR_win32_surface */
    /*  294 */ 0x75ee32f09cdd8db9, /* VK_KHR_workgroup_memory_explicit_layout */
    /*  295 */ 0x32a481baaa637e2c, /* VK_KHR_xcb_surface */
    /*  296 */ 0x863c0e309551346e, /* VK_KHR_xlib_surface */
    /*  297 */ 0x58d24a21f116065b, /* VK_KHR_zero_initialize_workgroup_memory */
    /*  298 */ 0x5615881540a7f6d8, /* VK_LUNARG_direct_driver_loading */
    /*  299 */ 0x6f8fb9c8b46fc189, /* VK_MESA_image_alignment_control */
    /*  300 */ 0xc1c930637836bf44, /* VK_MSFT_layered_driver */
    /*  301 */ 0x489cf2a16640d39e, /* VK_MVK_ios_surface */
    /*  302 */ 0x3274c65edf45286c, /* VK_MVK_macos_surface */
    /*  303 */ 0x53643314731ac57a, /* VK_NN_vi_surface */
    /*  304 */ 0x5bf53745255ccc0e, /* VK_NVX_binary_import */
    /*  305 */ 0x20b59934a97efd1c, /* VK_NVX_image_view_handle */
    /*  306 */ 0x112ee8733e2b22b3, /* VK_NVX_multiview_per_view_attributes */
    /*  307 */ 0x71fe862eee072b1e, /* VK_NV_acquire_winrt_display */
    /*  308 */ 0x9217a69de789d3fe, /* VK_NV_clip_space_w_scaling */
    /*  309 */ 0xad1ba91484f69ca3, /* VK_NV_command_buffer_inheritance */
    /*  310 */ 0x21d19e30b520bdd6, /* VK_NV_compute_shader_derivatives */
    /*  311 */ 0x069e842b3b51cefb, /* VK_NV_cooperative_matrix */
    /*  312 */ 0xce889f8d6b40e84f, /* VK_NV_copy_memory_indirect */
    /*  313 */ 0xed85b1ac0329a8cd, /* VK_NV_corner_sampled_image */
    /*  314 */ 0x81b617790445f852, /* VK_NV_coverage_reduction_mode */
    /*  315 */ 0x3644690c3bd14289, /* VK_NV_cuda_kernel_launch */
    /*  316 */ 0xbb81f8243fcc7db5, /* VK_NV_dedicated_allocation */
    /*  317 */ 0x00ce18bba106c2ad, /* VK_NV_dedicated_allocation_image_aliasing */
    /*  318 */ 0x23bcacd889bea60c, /* VK_NV_descriptor_pool_overallocation */
    /*  319 */ 0xf03dfd81ad17796f, /* VK_NV_device_diagnostic_checkpoints */
    /*  320 */ 0xc8050fbd31afc5b5, /* VK_NV_device_diagnostics_config */
    /*  321 */ 0xee7bfcd5523cff09, /* VK_NV_device_generated_commands */
    /*  322 */ 0x2ff0ded4f3f040e9, /* VK_NV_device_generated_commands_compute */
    /*  323 */ 0xc07b5e2a89ddc607, /* VK_NV_displacement_micromap */
    /*  324 */ 0xb2344e462fd9ef1b, /* VK_NV_extended_sparse_address_space */
    /*  325 */ 0xab0f59a00375b1ec, /* VK_NV_external_memory */
    /*  326 */ 0x518148eb9166b4b9, /* VK_NV_external_memory_capabilities */
    /*  327 */ 0x3c96386b301a3cdc, /* VK_NV_external_memory_rdma */
    /*  328 */ 0xcf69c3e7cbd068e4, /* VK_NV_external_memory_win32 */
    /*  329 */ 0xdf9a65a432a12606, /* VK_NV_fill_rectangle */
    /*  330 */ 0x9a6fda1e2f4f9096, /* VK_NV_fragment_coverage_to_color */
    /*  331 */ 0xc294d55a56858fb6, /* VK_NV_fragment_shader_barycentric */
    /*  332 */ 0x2ece12f465807058, /* VK_NV_fragment_shading_rate_enums */
    /*  333 */ 0x4caba51b111c61b9, /* VK_NV_framebuffer_mixed_samples */
    /*  334 */ 0xe0c4918343f3874c, /* VK_NV_geometry_shader_passthrough */
    /*  335 */ 0xd659873b3f6bc024, /* VK_NV_glsl_shader */
    /*  336 */ 0xe39346d87fc9aa45, /* VK_NV_inherited_viewport_scissor */
    /*  337 */ 0x52fcc4c2d713dad4, /* VK_NV_linear_color_attachment */
    /*  338 */ 0xb58daf9c015becf7, /* VK_NV_low_latency */
    /*  339 */ 0xa9eb852dfd7a1ece, /* VK_NV_low_latency2 */
    /*  340 */ 0x6c878fdbf1e4a7fb, /* VK_NV_memory_decompression */
    /*  341 */ 0x7401a89f84bc926b, /* VK_NV_mesh_shader */
    /*  342 */ 0x929112526891454e, /* VK_NV_optical_flow */
    /*  343 */ 0x5e0416a20f89c9f4, /* VK_NV_per_stage_descriptor_set */
    /*  344 */ 0x48102b2d563a8028, /* VK_NV_present_barrier */
    /*  345 */ 0xc20950e0cbc5bdc0, /* VK_NV_raw_access_chains */
    /*  346 */ 0x3d4e9e0bb54735fe, /* VK_NV_ray_tracing */
    /*  347 */ 0xe12f14699c6db9db, /* VK_NV_ray_tracing_invocation_reorder */
    /*  348 */ 0xba4184e5104338cb, /* VK_NV_ray_tracing_motion_blur */
    /*  349 */ 0x451532c42bd881b2, /* VK_NV_ray_tracing_validation */
    /*  350 */ 0x92ccabdfa0a3d6e4, /* VK_NV_representative_fragment_test */
    /*  351 */ 0xc4d99252b7b7843f, /* VK_NV_sample_mask_override_coverage */
    /*  352 */ 0xd4d2cda699fc74ae, /* VK_NV_scissor_exclusive */
    /*  353 */ 0xb8974b1af4c34b58, /* VK_NV_shader_atomic_float16_vector */
    /*  354 */ 0x52f9f98f09f18085, /* VK_NV_shader_image_footprint */
    /*  355 */ 0xc394473a75e21d7c, /* VK_NV_shader_sm_builtins */
    /*  356 */ 0x5b6c5e76d8a8364e, /* VK_NV_shader_subgroup_partitioned */
    /*  357 */ 0xcac204d487e563d3, /* VK_NV_shading_rate_image */
    /*  358 */ 0xfc6e35d06ddf634e, /* VK_NV_viewport_array2 */
    /*  359 */ 0x7748ea26eecd7e90, /* VK_NV_viewport_swizzle */
    /*  360 */ 0x7e4ac6b10102b887, /* VK_NV_win32_keyed_mutex */
    /*  361 */ 0x5c76ad884426c86c, /* VK_QCOM_filter_cubic_clamp */
    /*  362 */ 0xc7386bbfd1b9b423, /* VK_QCOM_filter_cubic_weights */
    /*  363 */ 0xff445069da66b635, /* VK_QCOM_fragment_density_map_offset */
    /*  364 */ 0xa6cab4106375cdfa, /* VK_QCOM_image_processing */
    /*  365 */ 0xa4a1ae34c2527a4a, /* VK_QCOM_image_processing2 */
    /*  366 */ 0xbff750af2234e2ce, /* VK_QCOM_multiview_per_view_render_areas */
    /*  367 */ 0x876a51c6df08420a, /* VK_QCOM_multiview_per_view_viewports */
    /*  368 */ 0xa3b4fc40f185c799, /* VK_QCOM_render_pass_shader_resolve */
    /*  369 */ 0x9b5c2a0bc41e00cd, /* VK_QCOM_render_pass_store_ops */
    /*  370 */ 0x8d33cd618c723019, /* VK_QCOM_render_pass_transform */
    /*  371 */ 0xd5a3f971e2e8b5c9, /* VK_QCOM_rotated_copy_commands */
    /*  372 */ 0xc37b456dbdf5565f, /* VK_QCOM_tile_properties */
    /*  373 */ 0x49bfbd9f92e0b029, /* VK_QCOM_ycbcr_degamma */
    /*  374 */ 0xc2e6f6dcc7614ace, /* VK_QNX_external_memory_screen_buffer */
    /*  375 */ 0x236bd86b3b17cf06, /* VK_QNX_screen_surface */
    /*  376 */ 0xe6fed416ddebf8d0, /* VK_SEC_amigo_profiling */
    /*  377 */ 0x45542cac22bd41a7, /* VK_VALVE_descriptor_set_host_mapping */
    /*  378 */ 0x38c73d4ab66a4942  /* VK_VALVE_mutable_descriptor_type */
};

#ifdef __cplusplus
GladVulkanContext glad_vulkan_context = {};
#else
GladVulkanContext glad_vulkan_context = { 0 };
#endif

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
          40, /* vkCmdBindIndexBuffer */
          43, /* vkCmdBindPipeline */
          48, /* vkCmdBindVertexBuffers */
          51, /* vkCmdBlitImage */
          58, /* vkCmdClearAttachments */
          59, /* vkCmdClearColorImage */
          60, /* vkCmdClearDepthStencilImage */
          65, /* vkCmdCopyBuffer */
          68, /* vkCmdCopyBufferToImage */
          71, /* vkCmdCopyImage */
          74, /* vkCmdCopyImageToBuffer */
          83, /* vkCmdCopyQueryPoolResults */
          92, /* vkCmdDispatch */
          98, /* vkCmdDispatchIndirect */
          99, /* vkCmdDraw */
         102, /* vkCmdDrawIndexed */
         103, /* vkCmdDrawIndexedIndirect */
         107, /* vkCmdDrawIndirect */
         123, /* vkCmdEndQuery */
         125, /* vkCmdEndRenderPass */
         132, /* vkCmdExecuteCommands */
         134, /* vkCmdFillBuffer */
         137, /* vkCmdNextSubpass */
         141, /* vkCmdPipelineBarrier */
         145, /* vkCmdPushConstants */
         151, /* vkCmdResetEvent */
         154, /* vkCmdResetQueryPool */
         155, /* vkCmdResolveImage */
         161, /* vkCmdSetBlendConstants */
         178, /* vkCmdSetDepthBias */
         182, /* vkCmdSetDepthBounds */
         201, /* vkCmdSetEvent */
         215, /* vkCmdSetLineWidth */
         239, /* vkCmdSetScissor */
         243, /* vkCmdSetStencilCompareMask */
         246, /* vkCmdSetStencilReference */
         249, /* vkCmdSetStencilWriteMask */
         252, /* vkCmdSetViewport */
         264, /* vkCmdUpdateBuffer */
         266, /* vkCmdWaitEvents */
         274, /* vkCmdWriteTimestamp */
         290, /* vkCreateBuffer */
         292, /* vkCreateBufferView */
         293, /* vkCreateCommandPool */
         294, /* vkCreateComputePipelines */
         302, /* vkCreateDescriptorPool */
         303, /* vkCreateDescriptorSetLayout */
         306, /* vkCreateDevice */
         310, /* vkCreateEvent */
         312, /* vkCreateFence */
         313, /* vkCreateFramebuffer */
         314, /* vkCreateGraphicsPipelines */
         317, /* vkCreateImage */
         319, /* vkCreateImageView */
         321, /* vkCreateInstance */
         327, /* vkCreatePipelineCache */
         328, /* vkCreatePipelineLayout */
         331, /* vkCreateQueryPool */
         334, /* vkCreateRenderPass */
         337, /* vkCreateSampler */
         341, /* vkCreateSemaphore */
         342, /* vkCreateShaderModule */
         361, /* vkDestroyBuffer */
         363, /* vkDestroyBufferView */
         364, /* vkDestroyCommandPool */
         372, /* vkDestroyDescriptorPool */
         373, /* vkDestroyDescriptorSetLayout */
         376, /* vkDestroyDevice */
         377, /* vkDestroyEvent */
         378, /* vkDestroyFence */
         379, /* vkDestroyFramebuffer */
         380, /* vkDestroyImage */
         381, /* vkDestroyImageView */
         383, /* vkDestroyInstance */
         386, /* vkDestroyPipeline */
         388, /* vkDestroyPipelineCache */
         389, /* vkDestroyPipelineLayout */
         392, /* vkDestroyQueryPool */
         393, /* vkDestroyRenderPass */
         394, /* vkDestroySampler */
         397, /* vkDestroySemaphore */
         399, /* vkDestroyShaderModule */
         405, /* vkDeviceWaitIdle */
         407, /* vkEndCommandBuffer */
         408, /* vkEnumerateDeviceExtensionProperties */
         409, /* vkEnumerateDeviceLayerProperties */
         410, /* vkEnumerateInstanceExtensionProperties */
         411, /* vkEnumerateInstanceLayerProperties */
         416, /* vkEnumeratePhysicalDevices */
         418, /* vkFlushMappedMemoryRanges */
         419, /* vkFreeCommandBuffers */
         420, /* vkFreeDescriptorSets */
         421, /* vkFreeMemory */
         432, /* vkGetBufferMemoryRequirements */
         464, /* vkGetDeviceMemoryCommitment */
         468, /* vkGetDeviceProcAddr */
         469, /* vkGetDeviceQueue */
         480, /* vkGetEventStatus */
         484, /* vkGetFenceStatus */
         489, /* vkGetImageMemoryRequirements */
         493, /* vkGetImageSparseMemoryRequirements */
         496, /* vkGetImageSubresourceLayout */
         502, /* vkGetInstanceProcAddr */
         533, /* vkGetPhysicalDeviceFeatures */
         536, /* vkGetPhysicalDeviceFormatProperties */
         540, /* vkGetPhysicalDeviceImageFormatProperties */
         543, /* vkGetPhysicalDeviceMemoryProperties */
         549, /* vkGetPhysicalDeviceProperties */
         553, /* vkGetPhysicalDeviceQueueFamilyProperties */
         557, /* vkGetPhysicalDeviceSparseImageFormatProperties */
         579, /* vkGetPipelineCacheData */
         589, /* vkGetQueryPoolResults */
         598, /* vkGetRenderAreaGranularity */
         623, /* vkInvalidateMappedMemoryRanges */
         625, /* vkMapMemory */
         627, /* vkMergePipelineCaches */
         630, /* vkQueueBindSparse */
         636, /* vkQueueSubmit */
         639, /* vkQueueWaitIdle */
         648, /* vkResetCommandBuffer */
         649, /* vkResetCommandPool */
         650, /* vkResetDescriptorPool */
         651, /* vkResetEvent */
         652, /* vkResetFences */
         660, /* vkSetEvent */
         674, /* vkUnmapMemory */
         678, /* vkUpdateDescriptorSets */
         680  /* vkWaitForFences */
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
          15, /* vkBindBufferMemory2 */
          18, /* vkBindImageMemory2 */
          93, /* vkCmdDispatchBase */
         196, /* vkCmdSetDeviceMask */
         304, /* vkCreateDescriptorUpdateTemplate */
         338, /* vkCreateSamplerYcbcrConversion */
         374, /* vkDestroyDescriptorUpdateTemplate */
         395, /* vkDestroySamplerYcbcrConversion */
         412, /* vkEnumerateInstanceVersion */
         413, /* vkEnumeratePhysicalDeviceGroups */
         433, /* vkGetBufferMemoryRequirements2 */
         448, /* vkGetDescriptorSetLayoutSupport */
         454, /* vkGetDeviceGroupPeerMemoryFeatures */
         470, /* vkGetDeviceQueue2 */
         490, /* vkGetImageMemoryRequirements2 */
         494, /* vkGetImageSparseMemoryRequirements2 */
         526, /* vkGetPhysicalDeviceExternalBufferProperties */
         528, /* vkGetPhysicalDeviceExternalFenceProperties */
         531, /* vkGetPhysicalDeviceExternalSemaphoreProperties */
         534, /* vkGetPhysicalDeviceFeatures2 */
         537, /* vkGetPhysicalDeviceFormatProperties2 */
         541, /* vkGetPhysicalDeviceImageFormatProperties2 */
         544, /* vkGetPhysicalDeviceMemoryProperties2 */
         550, /* vkGetPhysicalDeviceProperties2 */
         554, /* vkGetPhysicalDeviceQueueFamilyProperties2 */
         558, /* vkGetPhysicalDeviceSparseImageFormatProperties2 */
         671, /* vkTrimCommandPool */
         676  /* vkUpdateDescriptorSetWithTemplate */
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
          29, /* vkCmdBeginRenderPass2 */
         104, /* vkCmdDrawIndexedIndirectCount */
         109, /* vkCmdDrawIndirectCount */
         126, /* vkCmdEndRenderPass2 */
         138, /* vkCmdNextSubpass2 */
         335, /* vkCreateRenderPass2 */
         429, /* vkGetBufferDeviceAddress */
         435, /* vkGetBufferOpaqueCaptureAddress */
         465, /* vkGetDeviceMemoryOpaqueCaptureAddress */
         602, /* vkGetSemaphoreCounterValue */
         653, /* vkResetQueryPool */
         667, /* vkSignalSemaphore */
         682  /* vkWaitSemaphores */
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
          31, /* vkCmdBeginRendering */
          49, /* vkCmdBindVertexBuffers2 */
          52, /* vkCmdBlitImage2 */
          66, /* vkCmdCopyBuffer2 */
          69, /* vkCmdCopyBufferToImage2 */
          72, /* vkCmdCopyImage2 */
          75, /* vkCmdCopyImageToBuffer2 */
         128, /* vkCmdEndRendering */
         142, /* vkCmdPipelineBarrier2 */
         152, /* vkCmdResetEvent2 */
         156, /* vkCmdResolveImage2 */
         176, /* vkCmdSetCullMode */
         180, /* vkCmdSetDepthBiasEnable */
         183, /* vkCmdSetDepthBoundsTestEnable */
         188, /* vkCmdSetDepthCompareOp */
         190, /* vkCmdSetDepthTestEnable */
         192, /* vkCmdSetDepthWriteEnable */
         202, /* vkCmdSetEvent2 */
         209, /* vkCmdSetFrontFace */
         223, /* vkCmdSetPrimitiveRestartEnable */
         225, /* vkCmdSetPrimitiveTopology */
         230, /* vkCmdSetRasterizerDiscardEnable */
         240, /* vkCmdSetScissorWithCount */
         244, /* vkCmdSetStencilOp */
         247, /* vkCmdSetStencilTestEnable */
         257, /* vkCmdSetViewportWithCount */
         267, /* vkCmdWaitEvents2 */
         275, /* vkCmdWriteTimestamp2 */
         329, /* vkCreatePrivateDataSlot */
         390, /* vkDestroyPrivateDataSlot */
         451, /* vkGetDeviceBufferMemoryRequirements */
         459, /* vkGetDeviceImageMemoryRequirements */
         461, /* vkGetDeviceImageSparseMemoryRequirements */
         569, /* vkGetPhysicalDeviceToolProperties */
         587, /* vkGetPrivateData */
         637, /* vkQueueSubmit2 */
         665  /* vkSetPrivateData */
    };
    uint32_t i;
    if(!context->VERSION_1_3) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

#if defined(VK_ENABLE_BETA_EXTENSIONS)
static void glad_vk_load_VK_AMDX_shader_enqueue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          95, /* vkCmdDispatchGraphAMDX */
          96, /* vkCmdDispatchGraphIndirectAMDX */
          97, /* vkCmdDispatchGraphIndirectCountAMDX */
         135, /* vkCmdInitializeGraphScratchMemoryAMDX */
         311, /* vkCreateExecutionGraphPipelinesAMDX */
         481, /* vkGetExecutionGraphPipelineNodeIndexAMDX */
         482  /* vkGetExecutionGraphPipelineScratchSizeAMDX */
    };
    uint32_t i;
    if(!context->AMDX_shader_enqueue) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
static void glad_vk_load_VK_AMD_anti_lag(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          11  /* vkAntiLagUpdateAMD */
    };
    uint32_t i;
    if(!context->AMD_anti_lag) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_AMD_buffer_marker(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         272  /* vkCmdWriteBufferMarkerAMD */
    };
    uint32_t i;
    if(!context->AMD_buffer_marker) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_AMD_display_native_hdr(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         664  /* vkSetLocalDimmingAMD */
    };
    uint32_t i;
    if(!context->AMD_display_native_hdr) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_AMD_draw_indirect_count(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         105, /* vkCmdDrawIndexedIndirectCountAMD */
         110  /* vkCmdDrawIndirectCountAMD */
    };
    uint32_t i;
    if(!context->AMD_draw_indirect_count) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_AMD_shader_info(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         608  /* vkGetShaderInfoAMD */
    };
    uint32_t i;
    if(!context->AMD_shader_info) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
static void glad_vk_load_VK_ANDROID_external_memory_android_hardware_buffer(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         427, /* vkGetAndroidHardwareBufferPropertiesANDROID */
         504  /* vkGetMemoryAndroidHardwareBufferANDROID */
    };
    uint32_t i;
    if(!context->ANDROID_external_memory_android_hardware_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
static void glad_vk_load_VK_EXT_acquire_drm_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           0, /* vkAcquireDrmDisplayEXT */
         477  /* vkGetDrmDisplayEXT */
    };
    uint32_t i;
    if(!context->EXT_acquire_drm_display) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
static void glad_vk_load_VK_EXT_acquire_xlib_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           7, /* vkAcquireXlibDisplayEXT */
         592  /* vkGetRandROutputDisplayEXT */
    };
    uint32_t i;
    if(!context->EXT_acquire_xlib_display) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
static void glad_vk_load_VK_EXT_attachment_feedback_loop_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         160  /* vkCmdSetAttachmentFeedbackLoopEnableEXT */
    };
    uint32_t i;
    if(!context->EXT_attachment_feedback_loop_dynamic_state) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_buffer_device_address(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         430  /* vkGetBufferDeviceAddressEXT */
    };
    uint32_t i;
    if(!context->EXT_buffer_device_address) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_calibrated_timestamps(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         438, /* vkGetCalibratedTimestampsEXT */
         517  /* vkGetPhysicalDeviceCalibrateableTimeDomainsEXT */
    };
    uint32_t i;
    if(!context->EXT_calibrated_timestamps) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_color_write_enable(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         167  /* vkCmdSetColorWriteEnableEXT */
    };
    uint32_t i;
    if(!context->EXT_color_write_enable) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_conditional_rendering(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          24, /* vkCmdBeginConditionalRenderingEXT */
         121  /* vkCmdEndConditionalRenderingEXT */
    };
    uint32_t i;
    if(!context->EXT_conditional_rendering) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_debug_marker(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          86, /* vkCmdDebugMarkerBeginEXT */
          87, /* vkCmdDebugMarkerEndEXT */
          88, /* vkCmdDebugMarkerInsertEXT */
         355, /* vkDebugMarkerSetObjectNameEXT */
         356  /* vkDebugMarkerSetObjectTagEXT */
    };
    uint32_t i;
    if(!context->EXT_debug_marker) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_debug_report(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         299, /* vkCreateDebugReportCallbackEXT */
         357, /* vkDebugReportMessageEXT */
         369  /* vkDestroyDebugReportCallbackEXT */
    };
    uint32_t i;
    if(!context->EXT_debug_report) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_debug_utils(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          25, /* vkCmdBeginDebugUtilsLabelEXT */
         122, /* vkCmdEndDebugUtilsLabelEXT */
         136, /* vkCmdInsertDebugUtilsLabelEXT */
         300, /* vkCreateDebugUtilsMessengerEXT */
         370, /* vkDestroyDebugUtilsMessengerEXT */
         629, /* vkQueueBeginDebugUtilsLabelEXT */
         631, /* vkQueueEndDebugUtilsLabelEXT */
         632, /* vkQueueInsertDebugUtilsLabelEXT */
         657, /* vkSetDebugUtilsObjectNameEXT */
         658, /* vkSetDebugUtilsObjectTagEXT */
         669  /* vkSubmitDebugUtilsMessageEXT */
    };
    uint32_t i;
    if(!context->EXT_debug_utils) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_depth_bias_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         179  /* vkCmdSetDepthBias2EXT */
    };
    uint32_t i;
    if(!context->EXT_depth_bias_control) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_descriptor_buffer(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          36, /* vkCmdBindDescriptorBufferEmbeddedSamplersEXT */
          37, /* vkCmdBindDescriptorBuffersEXT */
         195, /* vkCmdSetDescriptorBufferOffsetsEXT */
         426, /* vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT */
         437, /* vkGetBufferOpaqueCaptureDescriptorDataEXT */
         443, /* vkGetDescriptorEXT */
         445, /* vkGetDescriptorSetLayoutBindingOffsetEXT */
         447, /* vkGetDescriptorSetLayoutSizeEXT */
         492, /* vkGetImageOpaqueCaptureDescriptorDataEXT */
         501, /* vkGetImageViewOpaqueCaptureDescriptorDataEXT */
         600  /* vkGetSamplerOpaqueCaptureDescriptorDataEXT */
    };
    uint32_t i;
    if(!context->EXT_descriptor_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_device_fault(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         453  /* vkGetDeviceFaultInfoEXT */
    };
    uint32_t i;
    if(!context->EXT_device_fault) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_direct_mode_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         643  /* vkReleaseDisplayEXT */
    };
    uint32_t i;
    if(!context->EXT_direct_mode_display) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
static void glad_vk_load_VK_EXT_directfb_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         307, /* vkCreateDirectFBSurfaceEXT */
         521  /* vkGetPhysicalDeviceDirectFBPresentationSupportEXT */
    };
    uint32_t i;
    if(!context->EXT_directfb_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
static void glad_vk_load_VK_EXT_discard_rectangles(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         198, /* vkCmdSetDiscardRectangleEXT */
         199, /* vkCmdSetDiscardRectangleEnableEXT */
         200  /* vkCmdSetDiscardRectangleModeEXT */
    };
    uint32_t i;
    if(!context->EXT_discard_rectangles) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_display_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         406, /* vkDisplayPowerControlEXT */
         611, /* vkGetSwapchainCounterEXT */
         640, /* vkRegisterDeviceEventEXT */
         641  /* vkRegisterDisplayEventEXT */
    };
    uint32_t i;
    if(!context->EXT_display_control) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_display_surface_counter(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         561  /* vkGetPhysicalDeviceSurfaceCapabilities2EXT */
    };
    uint32_t i;
    if(!context->EXT_display_surface_counter) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_extended_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          50, /* vkCmdBindVertexBuffers2EXT */
         177, /* vkCmdSetCullModeEXT */
         184, /* vkCmdSetDepthBoundsTestEnableEXT */
         189, /* vkCmdSetDepthCompareOpEXT */
         191, /* vkCmdSetDepthTestEnableEXT */
         193, /* vkCmdSetDepthWriteEnableEXT */
         210, /* vkCmdSetFrontFaceEXT */
         226, /* vkCmdSetPrimitiveTopologyEXT */
         241, /* vkCmdSetScissorWithCountEXT */
         245, /* vkCmdSetStencilOpEXT */
         248, /* vkCmdSetStencilTestEnableEXT */
         258  /* vkCmdSetViewportWithCountEXT */
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
         181, /* vkCmdSetDepthBiasEnableEXT */
         216, /* vkCmdSetLogicOpEXT */
         218, /* vkCmdSetPatchControlPointsEXT */
         224, /* vkCmdSetPrimitiveRestartEnableEXT */
         231  /* vkCmdSetRasterizerDiscardEnableEXT */
    };
    uint32_t i;
    if(!context->EXT_extended_dynamic_state2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_extended_dynamic_state3(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         158, /* vkCmdSetAlphaToCoverageEnableEXT */
         159, /* vkCmdSetAlphaToOneEnableEXT */
         164, /* vkCmdSetColorBlendAdvancedEXT */
         165, /* vkCmdSetColorBlendEnableEXT */
         166, /* vkCmdSetColorBlendEquationEXT */
         168, /* vkCmdSetColorWriteMaskEXT */
         169, /* vkCmdSetConservativeRasterizationModeEXT */
         170, /* vkCmdSetCoverageModulationModeNV */
         171, /* vkCmdSetCoverageModulationTableEnableNV */
         172, /* vkCmdSetCoverageModulationTableNV */
         173, /* vkCmdSetCoverageReductionModeNV */
         174, /* vkCmdSetCoverageToColorEnableNV */
         175, /* vkCmdSetCoverageToColorLocationNV */
         185, /* vkCmdSetDepthClampEnableEXT */
         186, /* vkCmdSetDepthClipEnableEXT */
         187, /* vkCmdSetDepthClipNegativeOneToOneEXT */
         206, /* vkCmdSetExtraPrimitiveOverestimationSizeEXT */
         211, /* vkCmdSetLineRasterizationModeEXT */
         213, /* vkCmdSetLineStippleEnableEXT */
         217, /* vkCmdSetLogicOpEnableEXT */
         222, /* vkCmdSetPolygonModeEXT */
         227, /* vkCmdSetProvokingVertexModeEXT */
         228, /* vkCmdSetRasterizationSamplesEXT */
         229, /* vkCmdSetRasterizationStreamEXT */
         235, /* vkCmdSetRepresentativeFragmentTestEnableNV */
         237, /* vkCmdSetSampleLocationsEnableEXT */
         238, /* vkCmdSetSampleMaskEXT */
         242, /* vkCmdSetShadingRateImageEnableNV */
         250, /* vkCmdSetTessellationDomainOriginEXT */
         254, /* vkCmdSetViewportSwizzleNV */
         255  /* vkCmdSetViewportWScalingEnableNV */
    };
    uint32_t i;
    if(!context->EXT_extended_dynamic_state3) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_external_memory_host(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         507  /* vkGetMemoryHostPointerPropertiesEXT */
    };
    uint32_t i;
    if(!context->EXT_external_memory_host) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_EXT_full_screen_exclusive(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           1, /* vkAcquireFullScreenExclusiveModeEXT */
         457, /* vkGetDeviceGroupSurfacePresentModes2EXT */
         566, /* vkGetPhysicalDeviceSurfacePresentModes2EXT */
         644  /* vkReleaseFullScreenExclusiveModeEXT */
    };
    uint32_t i;
    if(!context->EXT_full_screen_exclusive) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
static void glad_vk_load_VK_EXT_hdr_metadata(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         661  /* vkSetHdrMetadataEXT */
    };
    uint32_t i;
    if(!context->EXT_hdr_metadata) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_headless_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         315  /* vkCreateHeadlessSurfaceEXT */
    };
    uint32_t i;
    if(!context->EXT_headless_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_host_image_copy(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         280, /* vkCopyImageToImageEXT */
         281, /* vkCopyImageToMemoryEXT */
         283, /* vkCopyMemoryToImageEXT */
         497, /* vkGetImageSubresourceLayout2EXT */
         670  /* vkTransitionImageLayoutEXT */
    };
    uint32_t i;
    if(!context->EXT_host_image_copy) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_host_query_reset(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         654  /* vkResetQueryPoolEXT */
    };
    uint32_t i;
    if(!context->EXT_host_query_reset) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_image_compression_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         497  /* vkGetImageSubresourceLayout2EXT */
    };
    uint32_t i;
    if(!context->EXT_image_compression_control) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_image_drm_format_modifier(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         488  /* vkGetImageDrmFormatModifierPropertiesEXT */
    };
    uint32_t i;
    if(!context->EXT_image_drm_format_modifier) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_line_rasterization(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         212  /* vkCmdSetLineStippleEXT */
    };
    uint32_t i;
    if(!context->EXT_line_rasterization) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_mesh_shader(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         112, /* vkCmdDrawMeshTasksEXT */
         113, /* vkCmdDrawMeshTasksIndirectCountEXT */
         115  /* vkCmdDrawMeshTasksIndirectEXT */
    };
    uint32_t i;
    if(!context->EXT_mesh_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

#if defined(VK_USE_PLATFORM_METAL_EXT)
static void glad_vk_load_VK_EXT_metal_objects(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         417  /* vkExportMetalObjectsEXT */
    };
    uint32_t i;
    if(!context->EXT_metal_objects) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
#if defined(VK_USE_PLATFORM_METAL_EXT)
static void glad_vk_load_VK_EXT_metal_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         323  /* vkCreateMetalSurfaceEXT */
    };
    uint32_t i;
    if(!context->EXT_metal_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
static void glad_vk_load_VK_EXT_multi_draw(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         118, /* vkCmdDrawMultiEXT */
         119  /* vkCmdDrawMultiIndexedEXT */
    };
    uint32_t i;
    if(!context->EXT_multi_draw) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_opacity_micromap(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          23, /* vkBuildMicromapsEXT */
          57, /* vkCmdBuildMicromapsEXT */
          80, /* vkCmdCopyMemoryToMicromapEXT */
          81, /* vkCmdCopyMicromapEXT */
          82, /* vkCmdCopyMicromapToMemoryEXT */
         273, /* vkCmdWriteMicromapsPropertiesEXT */
         284, /* vkCopyMemoryToMicromapEXT */
         285, /* vkCopyMicromapEXT */
         286, /* vkCopyMicromapToMemoryEXT */
         324, /* vkCreateMicromapEXT */
         384, /* vkDestroyMicromapEXT */
         467, /* vkGetDeviceMicromapCompatibilityEXT */
         514, /* vkGetMicromapBuildSizesEXT */
         685  /* vkWriteMicromapsPropertiesEXT */
    };
    uint32_t i;
    if(!context->EXT_opacity_micromap) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_pageable_device_local_memory(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         659  /* vkSetDeviceMemoryPriorityEXT */
    };
    uint32_t i;
    if(!context->EXT_pageable_device_local_memory) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_pipeline_properties(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         586  /* vkGetPipelinePropertiesEXT */
    };
    uint32_t i;
    if(!context->EXT_pipeline_properties) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_private_data(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         330, /* vkCreatePrivateDataSlotEXT */
         391, /* vkDestroyPrivateDataSlotEXT */
         588, /* vkGetPrivateDataEXT */
         666  /* vkSetPrivateDataEXT */
    };
    uint32_t i;
    if(!context->EXT_private_data) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_sample_locations(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         236, /* vkCmdSetSampleLocationsEXT */
         546  /* vkGetPhysicalDeviceMultisamplePropertiesEXT */
    };
    uint32_t i;
    if(!context->EXT_sample_locations) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_shader_module_identifier(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         609, /* vkGetShaderModuleCreateInfoIdentifierEXT */
         610  /* vkGetShaderModuleIdentifierEXT */
    };
    uint32_t i;
    if(!context->EXT_shader_module_identifier) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_shader_object(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          45, /* vkCmdBindShadersEXT */
          50, /* vkCmdBindVertexBuffers2EXT */
         158, /* vkCmdSetAlphaToCoverageEnableEXT */
         159, /* vkCmdSetAlphaToOneEnableEXT */
         164, /* vkCmdSetColorBlendAdvancedEXT */
         165, /* vkCmdSetColorBlendEnableEXT */
         166, /* vkCmdSetColorBlendEquationEXT */
         168, /* vkCmdSetColorWriteMaskEXT */
         169, /* vkCmdSetConservativeRasterizationModeEXT */
         170, /* vkCmdSetCoverageModulationModeNV */
         171, /* vkCmdSetCoverageModulationTableEnableNV */
         172, /* vkCmdSetCoverageModulationTableNV */
         173, /* vkCmdSetCoverageReductionModeNV */
         174, /* vkCmdSetCoverageToColorEnableNV */
         175, /* vkCmdSetCoverageToColorLocationNV */
         177, /* vkCmdSetCullModeEXT */
         181, /* vkCmdSetDepthBiasEnableEXT */
         184, /* vkCmdSetDepthBoundsTestEnableEXT */
         185, /* vkCmdSetDepthClampEnableEXT */
         186, /* vkCmdSetDepthClipEnableEXT */
         187, /* vkCmdSetDepthClipNegativeOneToOneEXT */
         189, /* vkCmdSetDepthCompareOpEXT */
         191, /* vkCmdSetDepthTestEnableEXT */
         193, /* vkCmdSetDepthWriteEnableEXT */
         206, /* vkCmdSetExtraPrimitiveOverestimationSizeEXT */
         210, /* vkCmdSetFrontFaceEXT */
         211, /* vkCmdSetLineRasterizationModeEXT */
         213, /* vkCmdSetLineStippleEnableEXT */
         216, /* vkCmdSetLogicOpEXT */
         217, /* vkCmdSetLogicOpEnableEXT */
         218, /* vkCmdSetPatchControlPointsEXT */
         222, /* vkCmdSetPolygonModeEXT */
         224, /* vkCmdSetPrimitiveRestartEnableEXT */
         226, /* vkCmdSetPrimitiveTopologyEXT */
         227, /* vkCmdSetProvokingVertexModeEXT */
         228, /* vkCmdSetRasterizationSamplesEXT */
         229, /* vkCmdSetRasterizationStreamEXT */
         231, /* vkCmdSetRasterizerDiscardEnableEXT */
         235, /* vkCmdSetRepresentativeFragmentTestEnableNV */
         237, /* vkCmdSetSampleLocationsEnableEXT */
         238, /* vkCmdSetSampleMaskEXT */
         241, /* vkCmdSetScissorWithCountEXT */
         242, /* vkCmdSetShadingRateImageEnableNV */
         245, /* vkCmdSetStencilOpEXT */
         248, /* vkCmdSetStencilTestEnableEXT */
         250, /* vkCmdSetTessellationDomainOriginEXT */
         251, /* vkCmdSetVertexInputEXT */
         254, /* vkCmdSetViewportSwizzleNV */
         255, /* vkCmdSetViewportWScalingEnableNV */
         258, /* vkCmdSetViewportWithCountEXT */
         343, /* vkCreateShadersEXT */
         398, /* vkDestroyShaderEXT */
         607  /* vkGetShaderBinaryDataEXT */
    };
    uint32_t i;
    if(!context->EXT_shader_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_swapchain_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         647  /* vkReleaseSwapchainImagesEXT */
    };
    uint32_t i;
    if(!context->EXT_swapchain_maintenance1) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_tooling_info(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         570  /* vkGetPhysicalDeviceToolPropertiesEXT */
    };
    uint32_t i;
    if(!context->EXT_tooling_info) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_transform_feedback(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          27, /* vkCmdBeginQueryIndexedEXT */
          33, /* vkCmdBeginTransformFeedbackEXT */
          47, /* vkCmdBindTransformFeedbackBuffersEXT */
         108, /* vkCmdDrawIndirectByteCountEXT */
         124, /* vkCmdEndQueryIndexedEXT */
         130  /* vkCmdEndTransformFeedbackEXT */
    };
    uint32_t i;
    if(!context->EXT_transform_feedback) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_validation_cache(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         347, /* vkCreateValidationCacheEXT */
         402, /* vkDestroyValidationCacheEXT */
         614, /* vkGetValidationCacheDataEXT */
         628  /* vkMergeValidationCachesEXT */
    };
    uint32_t i;
    if(!context->EXT_validation_cache) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_EXT_vertex_input_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         251  /* vkCmdSetVertexInputEXT */
    };
    uint32_t i;
    if(!context->EXT_vertex_input_dynamic_state) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_buffer_collection(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         291, /* vkCreateBufferCollectionFUCHSIA */
         362, /* vkDestroyBufferCollectionFUCHSIA */
         428, /* vkGetBufferCollectionPropertiesFUCHSIA */
         655, /* vkSetBufferCollectionBufferConstraintsFUCHSIA */
         656  /* vkSetBufferCollectionImageConstraintsFUCHSIA */
    };
    uint32_t i;
    if(!context->FUCHSIA_buffer_collection) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_external_memory(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         512, /* vkGetMemoryZirconHandleFUCHSIA */
         513  /* vkGetMemoryZirconHandlePropertiesFUCHSIA */
    };
    uint32_t i;
    if(!context->FUCHSIA_external_memory) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_external_semaphore(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         606, /* vkGetSemaphoreZirconHandleFUCHSIA */
         621  /* vkImportSemaphoreZirconHandleFUCHSIA */
    };
    uint32_t i;
    if(!context->FUCHSIA_external_semaphore) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_imagepipe_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         318  /* vkCreateImagePipeSurfaceFUCHSIA */
    };
    uint32_t i;
    if(!context->FUCHSIA_imagepipe_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
#if defined(VK_USE_PLATFORM_GGP)
static void glad_vk_load_VK_GGP_stream_descriptor_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         345  /* vkCreateStreamDescriptorSurfaceGGP */
    };
    uint32_t i;
    if(!context->GGP_stream_descriptor_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
static void glad_vk_load_VK_GOOGLE_display_timing(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         515, /* vkGetPastPresentationTimingGOOGLE */
         597  /* vkGetRefreshCycleDurationGOOGLE */
    };
    uint32_t i;
    if(!context->GOOGLE_display_timing) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_HUAWEI_cluster_culling_shader(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         100, /* vkCmdDrawClusterHUAWEI */
         101  /* vkCmdDrawClusterIndirectHUAWEI */
    };
    uint32_t i;
    if(!context->HUAWEI_cluster_culling_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_HUAWEI_invocation_mask(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          42  /* vkCmdBindInvocationMaskHUAWEI */
    };
    uint32_t i;
    if(!context->HUAWEI_invocation_mask) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_HUAWEI_subpass_shading(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         259, /* vkCmdSubpassShadingHUAWEI */
         471  /* vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI */
    };
    uint32_t i;
    if(!context->HUAWEI_subpass_shading) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_INTEL_performance_query(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           4, /* vkAcquirePerformanceConfigurationINTEL */
         219, /* vkCmdSetPerformanceMarkerINTEL */
         220, /* vkCmdSetPerformanceOverrideINTEL */
         221, /* vkCmdSetPerformanceStreamMarkerINTEL */
         516, /* vkGetPerformanceParameterINTEL */
         622, /* vkInitializePerformanceApiINTEL */
         635, /* vkQueueSetPerformanceConfigurationINTEL */
         645, /* vkReleasePerformanceConfigurationINTEL */
         673  /* vkUninitializePerformanceApiINTEL */
    };
    uint32_t i;
    if(!context->INTEL_performance_query) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_acceleration_structure(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          22, /* vkBuildAccelerationStructuresKHR */
          55, /* vkCmdBuildAccelerationStructuresIndirectKHR */
          56, /* vkCmdBuildAccelerationStructuresKHR */
          62, /* vkCmdCopyAccelerationStructureKHR */
          64, /* vkCmdCopyAccelerationStructureToMemoryKHR */
          78, /* vkCmdCopyMemoryToAccelerationStructureKHR */
         269, /* vkCmdWriteAccelerationStructuresPropertiesKHR */
         278, /* vkCopyAccelerationStructureKHR */
         279, /* vkCopyAccelerationStructureToMemoryKHR */
         282, /* vkCopyMemoryToAccelerationStructureKHR */
         287, /* vkCreateAccelerationStructureKHR */
         359, /* vkDestroyAccelerationStructureKHR */
         422, /* vkGetAccelerationStructureBuildSizesKHR */
         423, /* vkGetAccelerationStructureDeviceAddressKHR */
         450, /* vkGetDeviceAccelerationStructureCompatibilityKHR */
         684  /* vkWriteAccelerationStructuresPropertiesKHR */
    };
    uint32_t i;
    if(!context->KHR_acceleration_structure) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
static void glad_vk_load_VK_KHR_android_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         289  /* vkCreateAndroidSurfaceKHR */
    };
    uint32_t i;
    if(!context->KHR_android_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
static void glad_vk_load_VK_KHR_bind_memory2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          16, /* vkBindBufferMemory2KHR */
          19  /* vkBindImageMemory2KHR */
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
         431, /* vkGetBufferDeviceAddressKHR */
         436, /* vkGetBufferOpaqueCaptureAddressKHR */
         466  /* vkGetDeviceMemoryOpaqueCaptureAddressKHR */
    };
    uint32_t i;
    if(!context->KHR_buffer_device_address) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_calibrated_timestamps(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         439, /* vkGetCalibratedTimestampsKHR */
         518  /* vkGetPhysicalDeviceCalibrateableTimeDomainsKHR */
    };
    uint32_t i;
    if(!context->KHR_calibrated_timestamps) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_cooperative_matrix(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         519  /* vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR */
    };
    uint32_t i;
    if(!context->KHR_cooperative_matrix) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_copy_commands2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          53, /* vkCmdBlitImage2KHR */
          67, /* vkCmdCopyBuffer2KHR */
          70, /* vkCmdCopyBufferToImage2KHR */
          73, /* vkCmdCopyImage2KHR */
          76, /* vkCmdCopyImageToBuffer2KHR */
         157  /* vkCmdResolveImage2KHR */
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
          30, /* vkCmdBeginRenderPass2KHR */
         127, /* vkCmdEndRenderPass2KHR */
         139, /* vkCmdNextSubpass2KHR */
         336  /* vkCreateRenderPass2KHR */
    };
    uint32_t i;
    if(!context->KHR_create_renderpass2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_deferred_host_operations(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         301, /* vkCreateDeferredOperationKHR */
         358, /* vkDeferredOperationJoinKHR */
         371, /* vkDestroyDeferredOperationKHR */
         441, /* vkGetDeferredOperationMaxConcurrencyKHR */
         442  /* vkGetDeferredOperationResultKHR */
    };
    uint32_t i;
    if(!context->KHR_deferred_host_operations) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_descriptor_update_template(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         150, /* vkCmdPushDescriptorSetWithTemplateKHR */
         305, /* vkCreateDescriptorUpdateTemplateKHR */
         375, /* vkDestroyDescriptorUpdateTemplateKHR */
         677  /* vkUpdateDescriptorSetWithTemplateKHR */
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
           2, /* vkAcquireNextImage2KHR */
          94, /* vkCmdDispatchBaseKHR */
         197, /* vkCmdSetDeviceMaskKHR */
         455, /* vkGetDeviceGroupPeerMemoryFeaturesKHR */
         456, /* vkGetDeviceGroupPresentCapabilitiesKHR */
         458, /* vkGetDeviceGroupSurfacePresentModesKHR */
         548  /* vkGetPhysicalDevicePresentRectanglesKHR */
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
         414  /* vkEnumeratePhysicalDeviceGroupsKHR */
    };
    uint32_t i;
    if(!context->KHR_device_group_creation) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         308, /* vkCreateDisplayModeKHR */
         309, /* vkCreateDisplayPlaneSurfaceKHR */
         473, /* vkGetDisplayModePropertiesKHR */
         475, /* vkGetDisplayPlaneCapabilitiesKHR */
         476, /* vkGetDisplayPlaneSupportedDisplaysKHR */
         523, /* vkGetPhysicalDeviceDisplayPlanePropertiesKHR */
         525  /* vkGetPhysicalDeviceDisplayPropertiesKHR */
    };
    uint32_t i;
    if(!context->KHR_display) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_display_swapchain(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         344  /* vkCreateSharedSwapchainsKHR */
    };
    uint32_t i;
    if(!context->KHR_display_swapchain) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_draw_indirect_count(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         106, /* vkCmdDrawIndexedIndirectCountKHR */
         111  /* vkCmdDrawIndirectCountKHR */
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
          32, /* vkCmdBeginRenderingKHR */
         129  /* vkCmdEndRenderingKHR */
    };
    uint32_t i;
    if(!context->KHR_dynamic_rendering) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_dynamic_rendering_local_read(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         233, /* vkCmdSetRenderingAttachmentLocationsKHR */
         234  /* vkCmdSetRenderingInputAttachmentIndicesKHR */
    };
    uint32_t i;
    if(!context->KHR_dynamic_rendering_local_read) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_external_fence_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         529  /* vkGetPhysicalDeviceExternalFencePropertiesKHR */
    };
    uint32_t i;
    if(!context->KHR_external_fence_capabilities) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_external_fence_fd(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         483, /* vkGetFenceFdKHR */
         617  /* vkImportFenceFdKHR */
    };
    uint32_t i;
    if(!context->KHR_external_fence_fd) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_external_fence_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         485, /* vkGetFenceWin32HandleKHR */
         618  /* vkImportFenceWin32HandleKHR */
    };
    uint32_t i;
    if(!context->KHR_external_fence_win32) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
static void glad_vk_load_VK_KHR_external_memory_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         527  /* vkGetPhysicalDeviceExternalBufferPropertiesKHR */
    };
    uint32_t i;
    if(!context->KHR_external_memory_capabilities) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_external_memory_fd(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         505, /* vkGetMemoryFdKHR */
         506  /* vkGetMemoryFdPropertiesKHR */
    };
    uint32_t i;
    if(!context->KHR_external_memory_fd) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_external_memory_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         509, /* vkGetMemoryWin32HandleKHR */
         511  /* vkGetMemoryWin32HandlePropertiesKHR */
    };
    uint32_t i;
    if(!context->KHR_external_memory_win32) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
static void glad_vk_load_VK_KHR_external_semaphore_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         532  /* vkGetPhysicalDeviceExternalSemaphorePropertiesKHR */
    };
    uint32_t i;
    if(!context->KHR_external_semaphore_capabilities) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_external_semaphore_fd(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         604, /* vkGetSemaphoreFdKHR */
         619  /* vkImportSemaphoreFdKHR */
    };
    uint32_t i;
    if(!context->KHR_external_semaphore_fd) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_external_semaphore_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         605, /* vkGetSemaphoreWin32HandleKHR */
         620  /* vkImportSemaphoreWin32HandleKHR */
    };
    uint32_t i;
    if(!context->KHR_external_semaphore_win32) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
static void glad_vk_load_VK_KHR_fragment_shading_rate(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         208, /* vkCmdSetFragmentShadingRateKHR */
         539  /* vkGetPhysicalDeviceFragmentShadingRatesKHR */
    };
    uint32_t i;
    if(!context->KHR_fragment_shading_rate) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_get_display_properties2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         472, /* vkGetDisplayModeProperties2KHR */
         474, /* vkGetDisplayPlaneCapabilities2KHR */
         522, /* vkGetPhysicalDeviceDisplayPlaneProperties2KHR */
         524  /* vkGetPhysicalDeviceDisplayProperties2KHR */
    };
    uint32_t i;
    if(!context->KHR_get_display_properties2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_get_memory_requirements2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         434, /* vkGetBufferMemoryRequirements2KHR */
         491, /* vkGetImageMemoryRequirements2KHR */
         495  /* vkGetImageSparseMemoryRequirements2KHR */
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
         535, /* vkGetPhysicalDeviceFeatures2KHR */
         538, /* vkGetPhysicalDeviceFormatProperties2KHR */
         542, /* vkGetPhysicalDeviceImageFormatProperties2KHR */
         545, /* vkGetPhysicalDeviceMemoryProperties2KHR */
         551, /* vkGetPhysicalDeviceProperties2KHR */
         555, /* vkGetPhysicalDeviceQueueFamilyProperties2KHR */
         559  /* vkGetPhysicalDeviceSparseImageFormatProperties2KHR */
    };
    uint32_t i;
    if(!context->KHR_get_physical_device_properties2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_get_surface_capabilities2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         562, /* vkGetPhysicalDeviceSurfaceCapabilities2KHR */
         564  /* vkGetPhysicalDeviceSurfaceFormats2KHR */
    };
    uint32_t i;
    if(!context->KHR_get_surface_capabilities2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_line_rasterization(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         214  /* vkCmdSetLineStippleKHR */
    };
    uint32_t i;
    if(!context->KHR_line_rasterization) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         672  /* vkTrimCommandPoolKHR */
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
         449  /* vkGetDescriptorSetLayoutSupportKHR */
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
         452, /* vkGetDeviceBufferMemoryRequirementsKHR */
         460, /* vkGetDeviceImageMemoryRequirementsKHR */
         462  /* vkGetDeviceImageSparseMemoryRequirementsKHR */
    };
    uint32_t i;
    if(!context->KHR_maintenance4) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_maintenance5(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          41, /* vkCmdBindIndexBuffer2KHR */
         463, /* vkGetDeviceImageSubresourceLayoutKHR */
         498, /* vkGetImageSubresourceLayout2KHR */
         599  /* vkGetRenderingAreaGranularityKHR */
    };
    uint32_t i;
    if(!context->KHR_maintenance5) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_maintenance6(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          35, /* vkCmdBindDescriptorBufferEmbeddedSamplers2EXT */
          39, /* vkCmdBindDescriptorSets2KHR */
         146, /* vkCmdPushConstants2KHR */
         147, /* vkCmdPushDescriptorSet2KHR */
         149, /* vkCmdPushDescriptorSetWithTemplate2KHR */
         194  /* vkCmdSetDescriptorBufferOffsets2EXT */
    };
    uint32_t i;
    if(!context->KHR_maintenance6) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_map_memory2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         626, /* vkMapMemory2KHR */
         675  /* vkUnmapMemory2KHR */
    };
    uint32_t i;
    if(!context->KHR_map_memory2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_performance_query(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           5, /* vkAcquireProfilingLockKHR */
         415, /* vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR */
         552, /* vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR */
         646  /* vkReleaseProfilingLockKHR */
    };
    uint32_t i;
    if(!context->KHR_performance_query) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_pipeline_binary(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         326, /* vkCreatePipelineBinariesKHR */
         387, /* vkDestroyPipelineBinaryKHR */
         578, /* vkGetPipelineBinaryDataKHR */
         585, /* vkGetPipelineKeyKHR */
         642  /* vkReleaseCapturedPipelineDataKHR */
    };
    uint32_t i;
    if(!context->KHR_pipeline_binary) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_pipeline_executable_properties(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         580, /* vkGetPipelineExecutableInternalRepresentationsKHR */
         581, /* vkGetPipelineExecutablePropertiesKHR */
         582  /* vkGetPipelineExecutableStatisticsKHR */
    };
    uint32_t i;
    if(!context->KHR_pipeline_executable_properties) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_present_wait(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         681  /* vkWaitForPresentKHR */
    };
    uint32_t i;
    if(!context->KHR_present_wait) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_push_descriptor(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         148, /* vkCmdPushDescriptorSetKHR */
         150  /* vkCmdPushDescriptorSetWithTemplateKHR */
    };
    uint32_t i;
    if(!context->KHR_push_descriptor) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_ray_tracing_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         260  /* vkCmdTraceRaysIndirect2KHR */
    };
    uint32_t i;
    if(!context->KHR_ray_tracing_maintenance1) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_ray_tracing_pipeline(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         232, /* vkCmdSetRayTracingPipelineStackSizeKHR */
         261, /* vkCmdTraceRaysIndirectKHR */
         262, /* vkCmdTraceRaysKHR */
         332, /* vkCreateRayTracingPipelinesKHR */
         593, /* vkGetRayTracingCaptureReplayShaderGroupHandlesKHR */
         594, /* vkGetRayTracingShaderGroupHandlesKHR */
         596  /* vkGetRayTracingShaderGroupStackSizeKHR */
    };
    uint32_t i;
    if(!context->KHR_ray_tracing_pipeline) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_sampler_ycbcr_conversion(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         339, /* vkCreateSamplerYcbcrConversionKHR */
         396  /* vkDestroySamplerYcbcrConversionKHR */
    };
    uint32_t i;
    if(!context->KHR_sampler_ycbcr_conversion) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_shared_presentable_image(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         613  /* vkGetSwapchainStatusKHR */
    };
    uint32_t i;
    if(!context->KHR_shared_presentable_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         400, /* vkDestroySurfaceKHR */
         563, /* vkGetPhysicalDeviceSurfaceCapabilitiesKHR */
         565, /* vkGetPhysicalDeviceSurfaceFormatsKHR */
         567, /* vkGetPhysicalDeviceSurfacePresentModesKHR */
         568  /* vkGetPhysicalDeviceSurfaceSupportKHR */
    };
    uint32_t i;
    if(!context->KHR_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_swapchain(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           2, /* vkAcquireNextImage2KHR */
           3, /* vkAcquireNextImageKHR */
         346, /* vkCreateSwapchainKHR */
         401, /* vkDestroySwapchainKHR */
         456, /* vkGetDeviceGroupPresentCapabilitiesKHR */
         458, /* vkGetDeviceGroupSurfacePresentModesKHR */
         548, /* vkGetPhysicalDevicePresentRectanglesKHR */
         612, /* vkGetSwapchainImagesKHR */
         634  /* vkQueuePresentKHR */
    };
    uint32_t i;
    if(!context->KHR_swapchain) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_synchronization2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         143, /* vkCmdPipelineBarrier2KHR */
         153, /* vkCmdResetEvent2KHR */
         203, /* vkCmdSetEvent2KHR */
         268, /* vkCmdWaitEvents2KHR */
         271, /* vkCmdWriteBufferMarker2AMD */
         276, /* vkCmdWriteTimestamp2KHR */
         590, /* vkGetQueueCheckpointData2NV */
         638  /* vkQueueSubmit2KHR */
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
         603, /* vkGetSemaphoreCounterValueKHR */
         668, /* vkSignalSemaphoreKHR */
         683  /* vkWaitSemaphoresKHR */
    };
    uint32_t i;
    if(!context->KHR_timeline_semaphore) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_video_decode_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          89  /* vkCmdDecodeVideoKHR */
    };
    uint32_t i;
    if(!context->KHR_video_decode_queue) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_video_encode_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         120, /* vkCmdEncodeVideoKHR */
         479, /* vkGetEncodedVideoSessionParametersKHR */
         572  /* vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR */
    };
    uint32_t i;
    if(!context->KHR_video_encode_queue) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_KHR_video_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          21, /* vkBindVideoSessionMemoryKHR */
          34, /* vkCmdBeginVideoCodingKHR */
          61, /* vkCmdControlVideoCodingKHR */
         131, /* vkCmdEndVideoCodingKHR */
         349, /* vkCreateVideoSessionKHR */
         350, /* vkCreateVideoSessionParametersKHR */
         403, /* vkDestroyVideoSessionKHR */
         404, /* vkDestroyVideoSessionParametersKHR */
         571, /* vkGetPhysicalDeviceVideoCapabilitiesKHR */
         573, /* vkGetPhysicalDeviceVideoFormatPropertiesKHR */
         615, /* vkGetVideoSessionMemoryRequirementsKHR */
         679  /* vkUpdateVideoSessionParametersKHR */
    };
    uint32_t i;
    if(!context->KHR_video_queue) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
static void glad_vk_load_VK_KHR_wayland_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         351, /* vkCreateWaylandSurfaceKHR */
         574  /* vkGetPhysicalDeviceWaylandPresentationSupportKHR */
    };
    uint32_t i;
    if(!context->KHR_wayland_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_win32_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         352, /* vkCreateWin32SurfaceKHR */
         575  /* vkGetPhysicalDeviceWin32PresentationSupportKHR */
    };
    uint32_t i;
    if(!context->KHR_win32_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
static void glad_vk_load_VK_KHR_xcb_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         353, /* vkCreateXcbSurfaceKHR */
         576  /* vkGetPhysicalDeviceXcbPresentationSupportKHR */
    };
    uint32_t i;
    if(!context->KHR_xcb_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)
static void glad_vk_load_VK_KHR_xlib_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         354, /* vkCreateXlibSurfaceKHR */
         577  /* vkGetPhysicalDeviceXlibPresentationSupportKHR */
    };
    uint32_t i;
    if(!context->KHR_xlib_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
#if defined(VK_USE_PLATFORM_IOS_MVK)
static void glad_vk_load_VK_MVK_ios_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         316  /* vkCreateIOSSurfaceMVK */
    };
    uint32_t i;
    if(!context->MVK_ios_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
#if defined(VK_USE_PLATFORM_MACOS_MVK)
static void glad_vk_load_VK_MVK_macos_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         322  /* vkCreateMacOSSurfaceMVK */
    };
    uint32_t i;
    if(!context->MVK_macos_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
#if defined(VK_USE_PLATFORM_VI_NN)
static void glad_vk_load_VK_NN_vi_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         348  /* vkCreateViSurfaceNN */
    };
    uint32_t i;
    if(!context->NN_vi_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
static void glad_vk_load_VK_NVX_binary_import(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          84, /* vkCmdCuLaunchKernelNVX */
         295, /* vkCreateCuFunctionNVX */
         296, /* vkCreateCuModuleNVX */
         365, /* vkDestroyCuFunctionNVX */
         366  /* vkDestroyCuModuleNVX */
    };
    uint32_t i;
    if(!context->NVX_binary_import) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NVX_image_view_handle(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         499, /* vkGetImageViewAddressNVX */
         500  /* vkGetImageViewHandleNVX */
    };
    uint32_t i;
    if(!context->NVX_image_view_handle) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_NV_acquire_winrt_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           6, /* vkAcquireWinrtDisplayNV */
         616  /* vkGetWinrtDisplayNV */
    };
    uint32_t i;
    if(!context->NV_acquire_winrt_display) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
static void glad_vk_load_VK_NV_clip_space_w_scaling(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         256  /* vkCmdSetViewportWScalingNV */
    };
    uint32_t i;
    if(!context->NV_clip_space_w_scaling) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_cooperative_matrix(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         520  /* vkGetPhysicalDeviceCooperativeMatrixPropertiesNV */
    };
    uint32_t i;
    if(!context->NV_cooperative_matrix) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_copy_memory_indirect(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          77, /* vkCmdCopyMemoryIndirectNV */
          79  /* vkCmdCopyMemoryToImageIndirectNV */
    };
    uint32_t i;
    if(!context->NV_copy_memory_indirect) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_coverage_reduction_mode(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         560  /* vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV */
    };
    uint32_t i;
    if(!context->NV_coverage_reduction_mode) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_cuda_kernel_launch(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          85, /* vkCmdCudaLaunchKernelNV */
         297, /* vkCreateCudaFunctionNV */
         298, /* vkCreateCudaModuleNV */
         367, /* vkDestroyCudaFunctionNV */
         368, /* vkDestroyCudaModuleNV */
         440  /* vkGetCudaModuleCacheNV */
    };
    uint32_t i;
    if(!context->NV_cuda_kernel_launch) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_device_diagnostic_checkpoints(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         162, /* vkCmdSetCheckpointNV */
         591  /* vkGetQueueCheckpointDataNV */
    };
    uint32_t i;
    if(!context->NV_device_diagnostic_checkpoints) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_device_generated_commands(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          44, /* vkCmdBindPipelineShaderGroupNV */
         133, /* vkCmdExecuteGeneratedCommandsNV */
         144, /* vkCmdPreprocessGeneratedCommandsNV */
         320, /* vkCreateIndirectCommandsLayoutNV */
         382, /* vkDestroyIndirectCommandsLayoutNV */
         487  /* vkGetGeneratedCommandsMemoryRequirementsNV */
    };
    uint32_t i;
    if(!context->NV_device_generated_commands) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_device_generated_commands_compute(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         265, /* vkCmdUpdatePipelineIndirectBufferNV */
         583, /* vkGetPipelineIndirectDeviceAddressNV */
         584  /* vkGetPipelineIndirectMemoryRequirementsNV */
    };
    uint32_t i;
    if(!context->NV_device_generated_commands_compute) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_external_memory_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         530  /* vkGetPhysicalDeviceExternalImageFormatPropertiesNV */
    };
    uint32_t i;
    if(!context->NV_external_memory_capabilities) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_external_memory_rdma(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         508  /* vkGetMemoryRemoteAddressNV */
    };
    uint32_t i;
    if(!context->NV_external_memory_rdma) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_NV_external_memory_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         510  /* vkGetMemoryWin32HandleNV */
    };
    uint32_t i;
    if(!context->NV_external_memory_win32) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
static void glad_vk_load_VK_NV_fragment_shading_rate_enums(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         207  /* vkCmdSetFragmentShadingRateEnumNV */
    };
    uint32_t i;
    if(!context->NV_fragment_shading_rate_enums) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_low_latency2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         503, /* vkGetLatencyTimingsNV */
         624, /* vkLatencySleepNV */
         633, /* vkQueueNotifyOutOfBandNV */
         662, /* vkSetLatencyMarkerNV */
         663  /* vkSetLatencySleepModeNV */
    };
    uint32_t i;
    if(!context->NV_low_latency2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_memory_decompression(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          90, /* vkCmdDecompressMemoryIndirectCountNV */
          91  /* vkCmdDecompressMemoryNV */
    };
    uint32_t i;
    if(!context->NV_memory_decompression) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_mesh_shader(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         114, /* vkCmdDrawMeshTasksIndirectCountNV */
         116, /* vkCmdDrawMeshTasksIndirectNV */
         117  /* vkCmdDrawMeshTasksNV */
    };
    uint32_t i;
    if(!context->NV_mesh_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_optical_flow(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          20, /* vkBindOpticalFlowSessionImageNV */
         140, /* vkCmdOpticalFlowExecuteNV */
         325, /* vkCreateOpticalFlowSessionNV */
         385, /* vkDestroyOpticalFlowSessionNV */
         547  /* vkGetPhysicalDeviceOpticalFlowImageFormatsNV */
    };
    uint32_t i;
    if(!context->NV_optical_flow) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_ray_tracing(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          13, /* vkBindAccelerationStructureMemoryNV */
          54, /* vkCmdBuildAccelerationStructureNV */
          63, /* vkCmdCopyAccelerationStructureNV */
         263, /* vkCmdTraceRaysNV */
         270, /* vkCmdWriteAccelerationStructuresPropertiesNV */
         277, /* vkCompileDeferredNV */
         288, /* vkCreateAccelerationStructureNV */
         333, /* vkCreateRayTracingPipelinesNV */
         360, /* vkDestroyAccelerationStructureNV */
         424, /* vkGetAccelerationStructureHandleNV */
         425, /* vkGetAccelerationStructureMemoryRequirementsNV */
         595  /* vkGetRayTracingShaderGroupHandlesNV */
    };
    uint32_t i;
    if(!context->NV_ray_tracing) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_scissor_exclusive(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         204, /* vkCmdSetExclusiveScissorEnableNV */
         205  /* vkCmdSetExclusiveScissorNV */
    };
    uint32_t i;
    if(!context->NV_scissor_exclusive) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_NV_shading_rate_image(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          46, /* vkCmdBindShadingRateImageNV */
         163, /* vkCmdSetCoarseSampleOrderNV */
         253  /* vkCmdSetViewportShadingRatePaletteNV */
    };
    uint32_t i;
    if(!context->NV_shading_rate_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

static void glad_vk_load_VK_QCOM_tile_properties(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         478, /* vkGetDynamicRenderingTilePropertiesQCOM */
         486  /* vkGetFramebufferTilePropertiesQCOM */
    };
    uint32_t i;
    if(!context->QCOM_tile_properties) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}

#if defined(VK_USE_PLATFORM_SCREEN_QNX)
static void glad_vk_load_VK_QNX_external_memory_screen_buffer(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         601  /* vkGetScreenBufferPropertiesQNX */
    };
    uint32_t i;
    if(!context->QNX_external_memory_screen_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
static void glad_vk_load_VK_QNX_screen_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         340, /* vkCreateScreenSurfaceQNX */
         556  /* vkGetPhysicalDeviceScreenPresentationSupportQNX */
    };
    uint32_t i;
    if(!context->QNX_screen_surface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
}


#endif
static void glad_vk_load_VK_VALVE_descriptor_set_host_mapping(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         444, /* vkGetDescriptorSetHostMappingVALVE */
         446  /* vkGetDescriptorSetLayoutHostMappingInfoVALVE */
    };
    uint32_t i;
    if(!context->VALVE_descriptor_set_host_mapping) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_Vulkan_fn_names[pfnIdx]);
    }
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
        {   49,   50 }, /* vkCmdBindVertexBuffers2 and vkCmdBindVertexBuffers2EXT */
        {   50,   49 }, /* vkCmdBindVertexBuffers2EXT and vkCmdBindVertexBuffers2 */
        {   52,   53 }, /* vkCmdBlitImage2 and vkCmdBlitImage2KHR */
        {   53,   52 }, /* vkCmdBlitImage2KHR and vkCmdBlitImage2 */
        {   66,   67 }, /* vkCmdCopyBuffer2 and vkCmdCopyBuffer2KHR */
        {   67,   66 }, /* vkCmdCopyBuffer2KHR and vkCmdCopyBuffer2 */
        {   69,   70 }, /* vkCmdCopyBufferToImage2 and vkCmdCopyBufferToImage2KHR */
        {   70,   69 }, /* vkCmdCopyBufferToImage2KHR and vkCmdCopyBufferToImage2 */
        {   72,   73 }, /* vkCmdCopyImage2 and vkCmdCopyImage2KHR */
        {   73,   72 }, /* vkCmdCopyImage2KHR and vkCmdCopyImage2 */
        {   75,   76 }, /* vkCmdCopyImageToBuffer2 and vkCmdCopyImageToBuffer2KHR */
        {   76,   75 }, /* vkCmdCopyImageToBuffer2KHR and vkCmdCopyImageToBuffer2 */
        {   93,   94 }, /* vkCmdDispatchBase and vkCmdDispatchBaseKHR */
        {   94,   93 }, /* vkCmdDispatchBaseKHR and vkCmdDispatchBase */
        {  104,  105 }, /* vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountAMD */
        {  104,  106 }, /* vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountKHR */
        {  105,  104 }, /* vkCmdDrawIndexedIndirectCountAMD and vkCmdDrawIndexedIndirectCount */
        {  105,  106 }, /* vkCmdDrawIndexedIndirectCountAMD and vkCmdDrawIndexedIndirectCountKHR */
        {  106,  104 }, /* vkCmdDrawIndexedIndirectCountKHR and vkCmdDrawIndexedIndirectCount */
        {  106,  105 }, /* vkCmdDrawIndexedIndirectCountKHR and vkCmdDrawIndexedIndirectCountAMD */
        {  109,  110 }, /* vkCmdDrawIndirectCount and vkCmdDrawIndirectCountAMD */
        {  109,  111 }, /* vkCmdDrawIndirectCount and vkCmdDrawIndirectCountKHR */
        {  110,  109 }, /* vkCmdDrawIndirectCountAMD and vkCmdDrawIndirectCount */
        {  110,  111 }, /* vkCmdDrawIndirectCountAMD and vkCmdDrawIndirectCountKHR */
        {  111,  109 }, /* vkCmdDrawIndirectCountKHR and vkCmdDrawIndirectCount */
        {  111,  110 }, /* vkCmdDrawIndirectCountKHR and vkCmdDrawIndirectCountAMD */
        {  128,  129 }, /* vkCmdEndRendering and vkCmdEndRenderingKHR */
        {  129,  128 }, /* vkCmdEndRenderingKHR and vkCmdEndRendering */
        {  126,  127 }, /* vkCmdEndRenderPass2 and vkCmdEndRenderPass2KHR */
        {  127,  126 }, /* vkCmdEndRenderPass2KHR and vkCmdEndRenderPass2 */
        {  138,  139 }, /* vkCmdNextSubpass2 and vkCmdNextSubpass2KHR */
        {  139,  138 }, /* vkCmdNextSubpass2KHR and vkCmdNextSubpass2 */
        {  142,  143 }, /* vkCmdPipelineBarrier2 and vkCmdPipelineBarrier2KHR */
        {  143,  142 }, /* vkCmdPipelineBarrier2KHR and vkCmdPipelineBarrier2 */
        {  152,  153 }, /* vkCmdResetEvent2 and vkCmdResetEvent2KHR */
        {  153,  152 }, /* vkCmdResetEvent2KHR and vkCmdResetEvent2 */
        {  156,  157 }, /* vkCmdResolveImage2 and vkCmdResolveImage2KHR */
        {  157,  156 }, /* vkCmdResolveImage2KHR and vkCmdResolveImage2 */
        {  176,  177 }, /* vkCmdSetCullMode and vkCmdSetCullModeEXT */
        {  177,  176 }, /* vkCmdSetCullModeEXT and vkCmdSetCullMode */
        {  180,  181 }, /* vkCmdSetDepthBiasEnable and vkCmdSetDepthBiasEnableEXT */
        {  181,  180 }, /* vkCmdSetDepthBiasEnableEXT and vkCmdSetDepthBiasEnable */
        {  183,  184 }, /* vkCmdSetDepthBoundsTestEnable and vkCmdSetDepthBoundsTestEnableEXT */
        {  184,  183 }, /* vkCmdSetDepthBoundsTestEnableEXT and vkCmdSetDepthBoundsTestEnable */
        {  188,  189 }, /* vkCmdSetDepthCompareOp and vkCmdSetDepthCompareOpEXT */
        {  189,  188 }, /* vkCmdSetDepthCompareOpEXT and vkCmdSetDepthCompareOp */
        {  190,  191 }, /* vkCmdSetDepthTestEnable and vkCmdSetDepthTestEnableEXT */
        {  191,  190 }, /* vkCmdSetDepthTestEnableEXT and vkCmdSetDepthTestEnable */
        {  192,  193 }, /* vkCmdSetDepthWriteEnable and vkCmdSetDepthWriteEnableEXT */
        {  193,  192 }, /* vkCmdSetDepthWriteEnableEXT and vkCmdSetDepthWriteEnable */
        {  196,  197 }, /* vkCmdSetDeviceMask and vkCmdSetDeviceMaskKHR */
        {  197,  196 }, /* vkCmdSetDeviceMaskKHR and vkCmdSetDeviceMask */
        {  202,  203 }, /* vkCmdSetEvent2 and vkCmdSetEvent2KHR */
        {  203,  202 }, /* vkCmdSetEvent2KHR and vkCmdSetEvent2 */
        {  209,  210 }, /* vkCmdSetFrontFace and vkCmdSetFrontFaceEXT */
        {  210,  209 }, /* vkCmdSetFrontFaceEXT and vkCmdSetFrontFace */
        {  212,  214 }, /* vkCmdSetLineStippleEXT and vkCmdSetLineStippleKHR */
        {  214,  212 }, /* vkCmdSetLineStippleKHR and vkCmdSetLineStippleEXT */
        {  223,  224 }, /* vkCmdSetPrimitiveRestartEnable and vkCmdSetPrimitiveRestartEnableEXT */
        {  224,  223 }, /* vkCmdSetPrimitiveRestartEnableEXT and vkCmdSetPrimitiveRestartEnable */
        {  225,  226 }, /* vkCmdSetPrimitiveTopology and vkCmdSetPrimitiveTopologyEXT */
        {  226,  225 }, /* vkCmdSetPrimitiveTopologyEXT and vkCmdSetPrimitiveTopology */
        {  230,  231 }, /* vkCmdSetRasterizerDiscardEnable and vkCmdSetRasterizerDiscardEnableEXT */
        {  231,  230 }, /* vkCmdSetRasterizerDiscardEnableEXT and vkCmdSetRasterizerDiscardEnable */
        {  240,  241 }, /* vkCmdSetScissorWithCount and vkCmdSetScissorWithCountEXT */
        {  241,  240 }, /* vkCmdSetScissorWithCountEXT and vkCmdSetScissorWithCount */
        {  244,  245 }, /* vkCmdSetStencilOp and vkCmdSetStencilOpEXT */
        {  245,  244 }, /* vkCmdSetStencilOpEXT and vkCmdSetStencilOp */
        {  247,  248 }, /* vkCmdSetStencilTestEnable and vkCmdSetStencilTestEnableEXT */
        {  248,  247 }, /* vkCmdSetStencilTestEnableEXT and vkCmdSetStencilTestEnable */
        {  257,  258 }, /* vkCmdSetViewportWithCount and vkCmdSetViewportWithCountEXT */
        {  258,  257 }, /* vkCmdSetViewportWithCountEXT and vkCmdSetViewportWithCount */
        {  267,  268 }, /* vkCmdWaitEvents2 and vkCmdWaitEvents2KHR */
        {  268,  267 }, /* vkCmdWaitEvents2KHR and vkCmdWaitEvents2 */
        {  275,  276 }, /* vkCmdWriteTimestamp2 and vkCmdWriteTimestamp2KHR */
        {  276,  275 }, /* vkCmdWriteTimestamp2KHR and vkCmdWriteTimestamp2 */
        {  304,  305 }, /* vkCreateDescriptorUpdateTemplate and vkCreateDescriptorUpdateTemplateKHR */
        {  305,  304 }, /* vkCreateDescriptorUpdateTemplateKHR and vkCreateDescriptorUpdateTemplate */
        {  329,  330 }, /* vkCreatePrivateDataSlot and vkCreatePrivateDataSlotEXT */
        {  330,  329 }, /* vkCreatePrivateDataSlotEXT and vkCreatePrivateDataSlot */
        {  335,  336 }, /* vkCreateRenderPass2 and vkCreateRenderPass2KHR */
        {  336,  335 }, /* vkCreateRenderPass2KHR and vkCreateRenderPass2 */
        {  338,  339 }, /* vkCreateSamplerYcbcrConversion and vkCreateSamplerYcbcrConversionKHR */
        {  339,  338 }, /* vkCreateSamplerYcbcrConversionKHR and vkCreateSamplerYcbcrConversion */
        {  374,  375 }, /* vkDestroyDescriptorUpdateTemplate and vkDestroyDescriptorUpdateTemplateKHR */
        {  375,  374 }, /* vkDestroyDescriptorUpdateTemplateKHR and vkDestroyDescriptorUpdateTemplate */
        {  390,  391 }, /* vkDestroyPrivateDataSlot and vkDestroyPrivateDataSlotEXT */
        {  391,  390 }, /* vkDestroyPrivateDataSlotEXT and vkDestroyPrivateDataSlot */
        {  395,  396 }, /* vkDestroySamplerYcbcrConversion and vkDestroySamplerYcbcrConversionKHR */
        {  396,  395 }, /* vkDestroySamplerYcbcrConversionKHR and vkDestroySamplerYcbcrConversion */
        {  413,  414 }, /* vkEnumeratePhysicalDeviceGroups and vkEnumeratePhysicalDeviceGroupsKHR */
        {  414,  413 }, /* vkEnumeratePhysicalDeviceGroupsKHR and vkEnumeratePhysicalDeviceGroups */
        {  429,  430 }, /* vkGetBufferDeviceAddress and vkGetBufferDeviceAddressEXT */
        {  429,  431 }, /* vkGetBufferDeviceAddress and vkGetBufferDeviceAddressKHR */
        {  430,  429 }, /* vkGetBufferDeviceAddressEXT and vkGetBufferDeviceAddress */
        {  430,  431 }, /* vkGetBufferDeviceAddressEXT and vkGetBufferDeviceAddressKHR */
        {  431,  429 }, /* vkGetBufferDeviceAddressKHR and vkGetBufferDeviceAddress */
        {  431,  430 }, /* vkGetBufferDeviceAddressKHR and vkGetBufferDeviceAddressEXT */
        {  433,  434 }, /* vkGetBufferMemoryRequirements2 and vkGetBufferMemoryRequirements2KHR */
        {  434,  433 }, /* vkGetBufferMemoryRequirements2KHR and vkGetBufferMemoryRequirements2 */
        {  435,  436 }, /* vkGetBufferOpaqueCaptureAddress and vkGetBufferOpaqueCaptureAddressKHR */
        {  436,  435 }, /* vkGetBufferOpaqueCaptureAddressKHR and vkGetBufferOpaqueCaptureAddress */
        {  438,  439 }, /* vkGetCalibratedTimestampsEXT and vkGetCalibratedTimestampsKHR */
        {  439,  438 }, /* vkGetCalibratedTimestampsKHR and vkGetCalibratedTimestampsEXT */
        {  448,  449 }, /* vkGetDescriptorSetLayoutSupport and vkGetDescriptorSetLayoutSupportKHR */
        {  449,  448 }, /* vkGetDescriptorSetLayoutSupportKHR and vkGetDescriptorSetLayoutSupport */
        {  451,  452 }, /* vkGetDeviceBufferMemoryRequirements and vkGetDeviceBufferMemoryRequirementsKHR */
        {  452,  451 }, /* vkGetDeviceBufferMemoryRequirementsKHR and vkGetDeviceBufferMemoryRequirements */
        {  454,  455 }, /* vkGetDeviceGroupPeerMemoryFeatures and vkGetDeviceGroupPeerMemoryFeaturesKHR */
        {  455,  454 }, /* vkGetDeviceGroupPeerMemoryFeaturesKHR and vkGetDeviceGroupPeerMemoryFeatures */
        {  459,  460 }, /* vkGetDeviceImageMemoryRequirements and vkGetDeviceImageMemoryRequirementsKHR */
        {  460,  459 }, /* vkGetDeviceImageMemoryRequirementsKHR and vkGetDeviceImageMemoryRequirements */
        {  461,  462 }, /* vkGetDeviceImageSparseMemoryRequirements and vkGetDeviceImageSparseMemoryRequirementsKHR */
        {  462,  461 }, /* vkGetDeviceImageSparseMemoryRequirementsKHR and vkGetDeviceImageSparseMemoryRequirements */
        {  465,  466 }, /* vkGetDeviceMemoryOpaqueCaptureAddress and vkGetDeviceMemoryOpaqueCaptureAddressKHR */
        {  466,  465 }, /* vkGetDeviceMemoryOpaqueCaptureAddressKHR and vkGetDeviceMemoryOpaqueCaptureAddress */
        {  490,  491 }, /* vkGetImageMemoryRequirements2 and vkGetImageMemoryRequirements2KHR */
        {  491,  490 }, /* vkGetImageMemoryRequirements2KHR and vkGetImageMemoryRequirements2 */
        {  494,  495 }, /* vkGetImageSparseMemoryRequirements2 and vkGetImageSparseMemoryRequirements2KHR */
        {  495,  494 }, /* vkGetImageSparseMemoryRequirements2KHR and vkGetImageSparseMemoryRequirements2 */
        {  497,  498 }, /* vkGetImageSubresourceLayout2EXT and vkGetImageSubresourceLayout2KHR */
        {  498,  497 }, /* vkGetImageSubresourceLayout2KHR and vkGetImageSubresourceLayout2EXT */
        {  517,  518 }, /* vkGetPhysicalDeviceCalibrateableTimeDomainsEXT and vkGetPhysicalDeviceCalibrateableTimeDomainsKHR */
        {  518,  517 }, /* vkGetPhysicalDeviceCalibrateableTimeDomainsKHR and vkGetPhysicalDeviceCalibrateableTimeDomainsEXT */
        {  526,  527 }, /* vkGetPhysicalDeviceExternalBufferProperties and vkGetPhysicalDeviceExternalBufferPropertiesKHR */
        {  527,  526 }, /* vkGetPhysicalDeviceExternalBufferPropertiesKHR and vkGetPhysicalDeviceExternalBufferProperties */
        {  528,  529 }, /* vkGetPhysicalDeviceExternalFenceProperties and vkGetPhysicalDeviceExternalFencePropertiesKHR */
        {  529,  528 }, /* vkGetPhysicalDeviceExternalFencePropertiesKHR and vkGetPhysicalDeviceExternalFenceProperties */
        {  531,  532 }, /* vkGetPhysicalDeviceExternalSemaphoreProperties and vkGetPhysicalDeviceExternalSemaphorePropertiesKHR */
        {  532,  531 }, /* vkGetPhysicalDeviceExternalSemaphorePropertiesKHR and vkGetPhysicalDeviceExternalSemaphoreProperties */
        {  534,  535 }, /* vkGetPhysicalDeviceFeatures2 and vkGetPhysicalDeviceFeatures2KHR */
        {  535,  534 }, /* vkGetPhysicalDeviceFeatures2KHR and vkGetPhysicalDeviceFeatures2 */
        {  537,  538 }, /* vkGetPhysicalDeviceFormatProperties2 and vkGetPhysicalDeviceFormatProperties2KHR */
        {  538,  537 }, /* vkGetPhysicalDeviceFormatProperties2KHR and vkGetPhysicalDeviceFormatProperties2 */
        {  541,  542 }, /* vkGetPhysicalDeviceImageFormatProperties2 and vkGetPhysicalDeviceImageFormatProperties2KHR */
        {  542,  541 }, /* vkGetPhysicalDeviceImageFormatProperties2KHR and vkGetPhysicalDeviceImageFormatProperties2 */
        {  544,  545 }, /* vkGetPhysicalDeviceMemoryProperties2 and vkGetPhysicalDeviceMemoryProperties2KHR */
        {  545,  544 }, /* vkGetPhysicalDeviceMemoryProperties2KHR and vkGetPhysicalDeviceMemoryProperties2 */
        {  550,  551 }, /* vkGetPhysicalDeviceProperties2 and vkGetPhysicalDeviceProperties2KHR */
        {  551,  550 }, /* vkGetPhysicalDeviceProperties2KHR and vkGetPhysicalDeviceProperties2 */
        {  554,  555 }, /* vkGetPhysicalDeviceQueueFamilyProperties2 and vkGetPhysicalDeviceQueueFamilyProperties2KHR */
        {  555,  554 }, /* vkGetPhysicalDeviceQueueFamilyProperties2KHR and vkGetPhysicalDeviceQueueFamilyProperties2 */
        {  558,  559 }, /* vkGetPhysicalDeviceSparseImageFormatProperties2 and vkGetPhysicalDeviceSparseImageFormatProperties2KHR */
        {  559,  558 }, /* vkGetPhysicalDeviceSparseImageFormatProperties2KHR and vkGetPhysicalDeviceSparseImageFormatProperties2 */
        {  569,  570 }, /* vkGetPhysicalDeviceToolProperties and vkGetPhysicalDeviceToolPropertiesEXT */
        {  570,  569 }, /* vkGetPhysicalDeviceToolPropertiesEXT and vkGetPhysicalDeviceToolProperties */
        {  587,  588 }, /* vkGetPrivateData and vkGetPrivateDataEXT */
        {  588,  587 }, /* vkGetPrivateDataEXT and vkGetPrivateData */
        {  594,  595 }, /* vkGetRayTracingShaderGroupHandlesKHR and vkGetRayTracingShaderGroupHandlesNV */
        {  595,  594 }, /* vkGetRayTracingShaderGroupHandlesNV and vkGetRayTracingShaderGroupHandlesKHR */
        {  602,  603 }, /* vkGetSemaphoreCounterValue and vkGetSemaphoreCounterValueKHR */
        {  603,  602 }, /* vkGetSemaphoreCounterValueKHR and vkGetSemaphoreCounterValue */
        {  637,  638 }, /* vkQueueSubmit2 and vkQueueSubmit2KHR */
        {  638,  637 }, /* vkQueueSubmit2KHR and vkQueueSubmit2 */
        {  653,  654 }, /* vkResetQueryPool and vkResetQueryPoolEXT */
        {  654,  653 }, /* vkResetQueryPoolEXT and vkResetQueryPool */
        {  665,  666 }, /* vkSetPrivateData and vkSetPrivateDataEXT */
        {  666,  665 }, /* vkSetPrivateDataEXT and vkSetPrivateData */
        {  667,  668 }, /* vkSignalSemaphore and vkSignalSemaphoreKHR */
        {  668,  667 }, /* vkSignalSemaphoreKHR and vkSignalSemaphore */
        {  671,  672 }, /* vkTrimCommandPool and vkTrimCommandPoolKHR */
        {  672,  671 }, /* vkTrimCommandPoolKHR and vkTrimCommandPool */
        {  676,  677 }, /* vkUpdateDescriptorSetWithTemplate and vkUpdateDescriptorSetWithTemplateKHR */
        {  677,  676 }, /* vkUpdateDescriptorSetWithTemplateKHR and vkUpdateDescriptorSetWithTemplate */
        {  682,  683 }, /* vkWaitSemaphores and vkWaitSemaphoresKHR */
        {  683,  682 }, /* vkWaitSemaphoresKHR and vkWaitSemaphores */
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
    glad_vk_load_VK_EXT_descriptor_buffer(context, load, userptr);
    glad_vk_load_VK_EXT_device_fault(context, load, userptr);
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
    glad_vk_load_VK_NV_cooperative_matrix(context, load, userptr);
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
    0x269c5788bd9937d1, /* vkAcquireFullScreenExclusiveModeEXT */
    0x81f991d1ab0bc5ce, /* vkAcquireNextImage2KHR */
    0x8db47b7cc78dbf21, /* vkAcquireNextImageKHR */
    0x1173dfede1e58b0e, /* vkAcquirePerformanceConfigurationINTEL */
    0xaa4956312cfc8f69, /* vkAcquireProfilingLockKHR */
    0x03c070149bc4adcf, /* vkAllocateCommandBuffers */
    0x6f91a0562614466e, /* vkAllocateDescriptorSets */
    0x3339f46d399c78c5, /* vkAllocateMemory */
    0xe06aa3b9e8eeba91, /* vkAntiLagUpdateAMD */
    0x47d826cf3a236677, /* vkBeginCommandBuffer */
    0x6e0d98ae9ace40d5, /* vkBindAccelerationStructureMemoryNV */
    0x75dc79c2cde7708a, /* vkBindBufferMemory */
    0x1e001d1f829f257b, /* vkBindBufferMemory2 */
    0xc20b7cd3cdb4895d, /* vkBindBufferMemory2KHR */
    0x3fab09299e5024e6, /* vkBindImageMemory */
    0xfd4ef6a737d2546d, /* vkBindImageMemory2 */
    0xa17b9f5a286650f5, /* vkBindImageMemory2KHR */
    0x611ba0d146ed962c, /* vkBindOpticalFlowSessionImageNV */
    0x95fd48feaefe8c46, /* vkBindVideoSessionMemoryKHR */
    0x2d831a042e0d1b62, /* vkBuildAccelerationStructuresKHR */
    0x31070cdf29394f00, /* vkBuildMicromapsEXT */
    0x73bc2739d085085f, /* vkCmdBeginConditionalRenderingEXT */
    0xa53a9028f9deee27, /* vkCmdBeginDebugUtilsLabelEXT */
    0x997ea78db49c8c69, /* vkCmdBeginQuery */
    0xa3c120c4c081785a, /* vkCmdBeginQueryIndexedEXT */
    0xc8c90b647a8c1688, /* vkCmdBeginRenderPass */
    0xf763fd5a051145b3, /* vkCmdBeginRenderPass2 */
    0x953dd320a2f19033, /* vkCmdBeginRenderPass2KHR */
    0x950906daed043635, /* vkCmdBeginRendering */
    0xf525fcfca497ad4d, /* vkCmdBeginRenderingKHR */
    0xae000b2715cd085c, /* vkCmdBeginTransformFeedbackEXT */
    0xcfa13bad1a984ba3, /* vkCmdBeginVideoCodingKHR */
    0x908be4be59b54bee, /* vkCmdBindDescriptorBufferEmbeddedSamplers2EXT */
    0xc5d77b727d806ce6, /* vkCmdBindDescriptorBufferEmbeddedSamplersEXT */
    0xd3d8cd8814a0cdd8, /* vkCmdBindDescriptorBuffersEXT */
    0xada92dcad41eaf98, /* vkCmdBindDescriptorSets */
    0xbb625b5594f09b62, /* vkCmdBindDescriptorSets2KHR */
    0x668f24a3147926db, /* vkCmdBindIndexBuffer */
    0x6fde01fd66c6087a, /* vkCmdBindIndexBuffer2KHR */
    0x5dd077e15ef82882, /* vkCmdBindInvocationMaskHUAWEI */
    0x093d8596adfdb576, /* vkCmdBindPipeline */
    0xfb6168e88a9522ee, /* vkCmdBindPipelineShaderGroupNV */
    0x213f8b33c25f4ec9, /* vkCmdBindShadersEXT */
    0x36135fe5c54d3b34, /* vkCmdBindShadingRateImageNV */
    0x24975600fb49fd73, /* vkCmdBindTransformFeedbackBuffersEXT */
    0x9beb233b5b7ad768, /* vkCmdBindVertexBuffers */
    0xf5dd10901cd99b7e, /* vkCmdBindVertexBuffers2 */
    0x95e7e04ef3cf5655, /* vkCmdBindVertexBuffers2EXT */
    0x38f59a81a499abec, /* vkCmdBlitImage */
    0xfb75695f0deb8eb6, /* vkCmdBlitImage2 */
    0xcdda04206e1c1dfe, /* vkCmdBlitImage2KHR */
    0x4092cc86b9e7806e, /* vkCmdBuildAccelerationStructureNV */
    0xa99627a28d359157, /* vkCmdBuildAccelerationStructuresIndirectKHR */
    0x56e0a0791533454f, /* vkCmdBuildAccelerationStructuresKHR */
    0xdad7d425257f2349, /* vkCmdBuildMicromapsEXT */
    0x484c4c652a1f9c0e, /* vkCmdClearAttachments */
    0x900de63b0b6f0ca2, /* vkCmdClearColorImage */
    0x387f685e13e513fa, /* vkCmdClearDepthStencilImage */
    0x355f705d4d835c02, /* vkCmdControlVideoCodingKHR */
    0x338a1ed4b2ca0c7a, /* vkCmdCopyAccelerationStructureKHR */
    0x1d7e628cb67db142, /* vkCmdCopyAccelerationStructureNV */
    0xc73b61c79b859a21, /* vkCmdCopyAccelerationStructureToMemoryKHR */
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
    0xea1cabf280ef8b04, /* vkCmdCopyMemoryIndirectNV */
    0xc24235cf58916cb3, /* vkCmdCopyMemoryToAccelerationStructureKHR */
    0x41a01ed27bc041f2, /* vkCmdCopyMemoryToImageIndirectNV */
    0x09bcf6218bf7a7cc, /* vkCmdCopyMemoryToMicromapEXT */
    0x07982f27d5cc9e3d, /* vkCmdCopyMicromapEXT */
    0x31241535b9bc3b52, /* vkCmdCopyMicromapToMemoryEXT */
    0xe133357d099609f5, /* vkCmdCopyQueryPoolResults */
    0xc8ce9307051f9bc4, /* vkCmdCuLaunchKernelNVX */
    0x9508bfb817e18156, /* vkCmdCudaLaunchKernelNV */
    0xba7d020dda50aee4, /* vkCmdDebugMarkerBeginEXT */
    0x96d500101d2c0cfc, /* vkCmdDebugMarkerEndEXT */
    0x09da53bc6b918573, /* vkCmdDebugMarkerInsertEXT */
    0xa5bd2226d386dd02, /* vkCmdDecodeVideoKHR */
    0xa9a55fd0d9b55eda, /* vkCmdDecompressMemoryIndirectCountNV */
    0x1c4feae5ecde76d9, /* vkCmdDecompressMemoryNV */
    0x9303bbd56b6cd187, /* vkCmdDispatch */
    0xcff95583fb6ffa3f, /* vkCmdDispatchBase */
    0x315127945d495884, /* vkCmdDispatchBaseKHR */
    0xf31eeaf76f0b6dca, /* vkCmdDispatchGraphAMDX */
    0x4e7d037aae3a3033, /* vkCmdDispatchGraphIndirectAMDX */
    0xd8c4bb7f3586d513, /* vkCmdDispatchGraphIndirectCountAMDX */
    0xdac55f445397e484, /* vkCmdDispatchIndirect */
    0x6b0e217ae8f0f1ac, /* vkCmdDraw */
    0xcd3579faa9244fe8, /* vkCmdDrawClusterHUAWEI */
    0x753af4a2035f5325, /* vkCmdDrawClusterIndirectHUAWEI */
    0xf9b2570c3144fc75, /* vkCmdDrawIndexed */
    0x75ffe5f7fd486bdd, /* vkCmdDrawIndexedIndirect */
    0x1d4114fa0cce1718, /* vkCmdDrawIndexedIndirectCount */
    0x95e478a17bd017c9, /* vkCmdDrawIndexedIndirectCountAMD */
    0xa343558c3889eb3b, /* vkCmdDrawIndexedIndirectCountKHR */
    0xf9cc9eb6cea6c9cb, /* vkCmdDrawIndirect */
    0x1028e41b255d6802, /* vkCmdDrawIndirectByteCountEXT */
    0x1b435983eb84abaa, /* vkCmdDrawIndirectCount */
    0x658b77dd8968ff3b, /* vkCmdDrawIndirectCountAMD */
    0xd2ada1f0fce0ebc9, /* vkCmdDrawIndirectCountKHR */
    0x1660d6d65602a1e2, /* vkCmdDrawMeshTasksEXT */
    0x3ac504ab87b15a1d, /* vkCmdDrawMeshTasksIndirectCountEXT */
    0xae68bbafa60e1bfd, /* vkCmdDrawMeshTasksIndirectCountNV */
    0x94400ae778a5a963, /* vkCmdDrawMeshTasksIndirectEXT */
    0x56698661adbb7534, /* vkCmdDrawMeshTasksIndirectNV */
    0xb0aeacfa9fc521aa, /* vkCmdDrawMeshTasksNV */
    0x13672ea08d07fa9d, /* vkCmdDrawMultiEXT */
    0x15b0ebcd4268ceb0, /* vkCmdDrawMultiIndexedEXT */
    0x68a8fbded268189e, /* vkCmdEncodeVideoKHR */
    0x1812390287e35f0c, /* vkCmdEndConditionalRenderingEXT */
    0xb70a1f7b0d640472, /* vkCmdEndDebugUtilsLabelEXT */
    0x99d50d423e66f60a, /* vkCmdEndQuery */
    0xcb5126a43f13e1de, /* vkCmdEndQueryIndexedEXT */
    0x03e8b953ae4cc537, /* vkCmdEndRenderPass */
    0xd271ad249d3a5d1d, /* vkCmdEndRenderPass2 */
    0xcf86c42d2695983a, /* vkCmdEndRenderPass2KHR */
    0xc261491c6f3eb73a, /* vkCmdEndRendering */
    0x20a57b855bed16ad, /* vkCmdEndRenderingKHR */
    0x20681e0c6bf30380, /* vkCmdEndTransformFeedbackEXT */
    0xf5243f8ebe970031, /* vkCmdEndVideoCodingKHR */
    0x1ce083dfe13eae46, /* vkCmdExecuteCommands */
    0xc7e4fe21b7623076, /* vkCmdExecuteGeneratedCommandsNV */
    0x203c934aa0f948fc, /* vkCmdFillBuffer */
    0xa143601d567d78a8, /* vkCmdInitializeGraphScratchMemoryAMDX */
    0x0f70146a40b73eaf, /* vkCmdInsertDebugUtilsLabelEXT */
    0xf8a5e079575f045d, /* vkCmdNextSubpass */
    0x09d5feddc371e187, /* vkCmdNextSubpass2 */
    0x599380d76631dbc9, /* vkCmdNextSubpass2KHR */
    0xc0130a682397781c, /* vkCmdOpticalFlowExecuteNV */
    0xb2063ddd597a6ad7, /* vkCmdPipelineBarrier */
    0x5365aba2c3922f6a, /* vkCmdPipelineBarrier2 */
    0x47b5e34bc173355d, /* vkCmdPipelineBarrier2KHR */
    0xbbb204c332bf3b26, /* vkCmdPreprocessGeneratedCommandsNV */
    0xf0bf149eb20282af, /* vkCmdPushConstants */
    0x844e6fc97d32338d, /* vkCmdPushConstants2KHR */
    0xda9d391d34dd9078, /* vkCmdPushDescriptorSet2KHR */
    0x2123cc5e1c438312, /* vkCmdPushDescriptorSetKHR */
    0xf42ac32ac7eb727c, /* vkCmdPushDescriptorSetWithTemplate2KHR */
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
    0xd31d2bb517a75484, /* vkCmdSetAttachmentFeedbackLoopEnableEXT */
    0x9b6913d4f956684e, /* vkCmdSetBlendConstants */
    0x35ddb5f0819f35bf, /* vkCmdSetCheckpointNV */
    0x12ca3f3ec96315f3, /* vkCmdSetCoarseSampleOrderNV */
    0xa0f10e474c7a0e0d, /* vkCmdSetColorBlendAdvancedEXT */
    0x17f9a371c7111a63, /* vkCmdSetColorBlendEnableEXT */
    0x8ada4cd22e8a735c, /* vkCmdSetColorBlendEquationEXT */
    0xee0c987fe12167e5, /* vkCmdSetColorWriteEnableEXT */
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
    0xf1159d930e7b7f9b, /* vkCmdSetDepthBias2EXT */
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
    0x5d404fade6187f05, /* vkCmdSetDescriptorBufferOffsets2EXT */
    0x3cb127add67d0963, /* vkCmdSetDescriptorBufferOffsetsEXT */
    0x0b635494ffc80076, /* vkCmdSetDeviceMask */
    0x6a987f9eb7d4a557, /* vkCmdSetDeviceMaskKHR */
    0x92bb34229e07c467, /* vkCmdSetDiscardRectangleEXT */
    0xae74bca0714f1b3b, /* vkCmdSetDiscardRectangleEnableEXT */
    0xe5686168ac2e1c2a, /* vkCmdSetDiscardRectangleModeEXT */
    0x5c738ec563b80923, /* vkCmdSetEvent */
    0x358c26001c7dea62, /* vkCmdSetEvent2 */
    0x81a460bb5df2fb6c, /* vkCmdSetEvent2KHR */
    0x085d172fa3bb5527, /* vkCmdSetExclusiveScissorEnableNV */
    0x429417467467b909, /* vkCmdSetExclusiveScissorNV */
    0x538223e2090de1df, /* vkCmdSetExtraPrimitiveOverestimationSizeEXT */
    0x86a35fcb0cd25838, /* vkCmdSetFragmentShadingRateEnumNV */
    0x8ed6523506902ceb, /* vkCmdSetFragmentShadingRateKHR */
    0xb90a1a834aa8c307, /* vkCmdSetFrontFace */
    0x335573b897d8b48c, /* vkCmdSetFrontFaceEXT */
    0xe86e1a671a40b3b7, /* vkCmdSetLineRasterizationModeEXT */
    0x10cb3a8400778673, /* vkCmdSetLineStippleEXT */
    0xa664321f63cd904a, /* vkCmdSetLineStippleEnableEXT */
    0x24f886fa5cebd7ed, /* vkCmdSetLineStippleKHR */
    0xb7ddef653b0f7932, /* vkCmdSetLineWidth */
    0x4fdb2f0ce0346b73, /* vkCmdSetLogicOpEXT */
    0x735a3459f80339e7, /* vkCmdSetLogicOpEnableEXT */
    0x77298a207cf7470a, /* vkCmdSetPatchControlPointsEXT */
    0x4888445b33d1d1a9, /* vkCmdSetPerformanceMarkerINTEL */
    0x81a2503b2e89f09e, /* vkCmdSetPerformanceOverrideINTEL */
    0xc0b67df33e46a5f0, /* vkCmdSetPerformanceStreamMarkerINTEL */
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
    0x20e1f9030911f404, /* vkCmdSetRayTracingPipelineStackSizeKHR */
    0xabb4da3669fa0607, /* vkCmdSetRenderingAttachmentLocationsKHR */
    0x8284d04d0f439b7f, /* vkCmdSetRenderingInputAttachmentIndicesKHR */
    0x2b78093ae32cb916, /* vkCmdSetRepresentativeFragmentTestEnableNV */
    0xfa5d78b1a973792e, /* vkCmdSetSampleLocationsEXT */
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
    0x26c37395ff9739bc, /* vkCmdSetViewportShadingRatePaletteNV */
    0xb449b51a1fdae15f, /* vkCmdSetViewportSwizzleNV */
    0xd35e353760f41c6f, /* vkCmdSetViewportWScalingEnableNV */
    0xb67ff6e303d3c4fb, /* vkCmdSetViewportWScalingNV */
    0x0198a65d97d8c9de, /* vkCmdSetViewportWithCount */
    0xffa40d4e01bf3cc0, /* vkCmdSetViewportWithCountEXT */
    0x149123ece151c923, /* vkCmdSubpassShadingHUAWEI */
    0x40db28be40a6f866, /* vkCmdTraceRaysIndirect2KHR */
    0xc1239f4d94d0ccd5, /* vkCmdTraceRaysIndirectKHR */
    0x71d79d686f22d526, /* vkCmdTraceRaysKHR */
    0x877be98356e2a511, /* vkCmdTraceRaysNV */
    0xa1e0bb08c1850958, /* vkCmdUpdateBuffer */
    0x59e3b39cfad2a148, /* vkCmdUpdatePipelineIndirectBufferNV */
    0x1441dbc95c1af085, /* vkCmdWaitEvents */
    0xba764f7da1952e81, /* vkCmdWaitEvents2 */
    0x1b8ec29acf8f9c34, /* vkCmdWaitEvents2KHR */
    0xe9afc748cd05801d, /* vkCmdWriteAccelerationStructuresPropertiesKHR */
    0x9f690b963d6e97a7, /* vkCmdWriteAccelerationStructuresPropertiesNV */
    0xb523ea07e8e7d77f, /* vkCmdWriteBufferMarker2AMD */
    0x75e32a36acf72579, /* vkCmdWriteBufferMarkerAMD */
    0xa966bf46df7237f0, /* vkCmdWriteMicromapsPropertiesEXT */
    0xee397d978e3960d4, /* vkCmdWriteTimestamp */
    0x6172f26a7ff5e461, /* vkCmdWriteTimestamp2 */
    0x2e9f27714c27c160, /* vkCmdWriteTimestamp2KHR */
    0xe7b1ed7ad6f748f7, /* vkCompileDeferredNV */
    0x5ad7e13a5109c73a, /* vkCopyAccelerationStructureKHR */
    0xe43e1298ce6a3bfe, /* vkCopyAccelerationStructureToMemoryKHR */
    0x238991922eb2dc5f, /* vkCopyImageToImageEXT */
    0xb1f1669ee2dd4847, /* vkCopyImageToMemoryEXT */
    0x2ed27a2c09707e8c, /* vkCopyMemoryToAccelerationStructureKHR */
    0x95a0cae5a6723961, /* vkCopyMemoryToImageEXT */
    0x19f19eb801eb4fea, /* vkCopyMemoryToMicromapEXT */
    0xf39873088d0d505a, /* vkCopyMicromapEXT */
    0x0b4161174ca14c67, /* vkCopyMicromapToMemoryEXT */
    0x452970172a23c174, /* vkCreateAccelerationStructureKHR */
    0x3ce0faf5d18dc25b, /* vkCreateAccelerationStructureNV */
    0x47176b0b432286d1, /* vkCreateBuffer */
    0xce653760953e9106, /* vkCreateBufferCollectionFUCHSIA */
    0xf2fafc3e54bde6da, /* vkCreateBufferView */
    0xc7fb7a8e9fc178bf, /* vkCreateCommandPool */
    0xa8ab2a7a72d37501, /* vkCreateComputePipelines */
    0x9df40d3bb19dc7f0, /* vkCreateCuFunctionNVX */
    0x70f16cd080e5a1e1, /* vkCreateCuModuleNVX */
    0x2959ea9ac9517bb5, /* vkCreateCudaFunctionNV */
    0x5f79fd00863c735c, /* vkCreateCudaModuleNV */
    0xc53d00dd120cc028, /* vkCreateDeferredOperationKHR */
    0xfa53afc7b202a4cc, /* vkCreateDescriptorPool */
    0xabbbfebcb5e50ddf, /* vkCreateDescriptorSetLayout */
    0xe77fae71b009ad05, /* vkCreateDescriptorUpdateTemplate */
    0xae196725993a5773, /* vkCreateDescriptorUpdateTemplateKHR */
    0xfc42afaa1bbc54a8, /* vkCreateEvent */
    0x714129686c9da431, /* vkCreateExecutionGraphPipelinesAMDX */
    0xb51bc46c54af21f6, /* vkCreateFence */
    0x38512bbacb368b24, /* vkCreateFramebuffer */
    0x5a4a030363a95dd6, /* vkCreateGraphicsPipelines */
    0x16a20753b1174318, /* vkCreateImage */
    0xb2f2d8afec7a88a4, /* vkCreateImageView */
    0x8977eb367d2cc188, /* vkCreateIndirectCommandsLayoutNV */
    0xb6e8dcebebd08436, /* vkCreateMicromapEXT */
    0x990606475b0662c9, /* vkCreateOpticalFlowSessionNV */
    0x7b8f5cb6ad62ff2c, /* vkCreatePipelineBinariesKHR */
    0x6474b3f3a4539ee3, /* vkCreatePipelineCache */
    0x76e7d06d87565b38, /* vkCreatePipelineLayout */
    0x126d3121c5d14c5f, /* vkCreatePrivateDataSlot */
    0x914ccba5ef3134d3, /* vkCreatePrivateDataSlotEXT */
    0x509b9755d54a9a1e, /* vkCreateQueryPool */
    0x1be0142d7b82c8c3, /* vkCreateRayTracingPipelinesKHR */
    0x4d0e89b321a6faef, /* vkCreateRayTracingPipelinesNV */
    0x8b778f59be50c419, /* vkCreateRenderPass */
    0xfd2a746603a13f60, /* vkCreateRenderPass2 */
    0x7282c5dadf99206c, /* vkCreateRenderPass2KHR */
    0xcce224e583312a27, /* vkCreateSampler */
    0xa1ba141ce2a9627b, /* vkCreateSamplerYcbcrConversion */
    0xbaa71789dfb073b1, /* vkCreateSamplerYcbcrConversionKHR */
    0xb23c3f52093e01ee, /* vkCreateSemaphore */
    0xa3fdcfe5e638f01f, /* vkCreateShaderModule */
    0x5736d06f9f7521f5, /* vkCreateShadersEXT */
    0x73239ae79c84cd85, /* vkCreateSharedSwapchainsKHR */
    0x536ddebd6b81d90a, /* vkCreateSwapchainKHR */
    0x80ad81694be917a9, /* vkCreateValidationCacheEXT */
    0xf8d70781ac92a1cf, /* vkCreateVideoSessionKHR */
    0xe89bda66824b7d7d, /* vkCreateVideoSessionParametersKHR */
    0xb1c51323a9aecd49, /* vkDebugMarkerSetObjectNameEXT */
    0xa739034f864fc640, /* vkDebugMarkerSetObjectTagEXT */
    0x7379abd10f3bfb5d, /* vkDeferredOperationJoinKHR */
    0xd536d860a73cf116, /* vkDestroyAccelerationStructureKHR */
    0xfe4be9de353f2023, /* vkDestroyAccelerationStructureNV */
    0x8ffccda86549f286, /* vkDestroyBuffer */
    0xb055e21eec61f87e, /* vkDestroyBufferCollectionFUCHSIA */
    0xf56a44bbdebd81c5, /* vkDestroyBufferView */
    0x8ddf999c6ee753db, /* vkDestroyCommandPool */
    0xe9321def2e9912ac, /* vkDestroyCuFunctionNVX */
    0xa47abcf416f45e13, /* vkDestroyCuModuleNVX */
    0xb811d13ae8ba8698, /* vkDestroyCudaFunctionNV */
    0x46bd70f746f4073f, /* vkDestroyCudaModuleNV */
    0x71bb8068c1edf85e, /* vkDestroyDeferredOperationKHR */
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
    0x67d5c823a6e5f838, /* vkDestroyIndirectCommandsLayoutNV */
    0x3a88835e421d53cd, /* vkDestroyMicromapEXT */
    0x8eaf0b3e0a85d3bc, /* vkDestroyOpticalFlowSessionNV */
    0xc6158137c93c542a, /* vkDestroyPipeline */
    0x5e156baf498f5138, /* vkDestroyPipelineBinaryKHR */
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
    0x22466386cc1398b8, /* vkDestroySwapchainKHR */
    0xc522092927d98161, /* vkDestroyValidationCacheEXT */
    0x4bfeea912504df47, /* vkDestroyVideoSessionKHR */
    0x996b8928f4147a24, /* vkDestroyVideoSessionParametersKHR */
    0x1de9fd31feb0f22f, /* vkDeviceWaitIdle */
    0x2bd217fc8713bb23, /* vkDisplayPowerControlEXT */
    0x3e52d6e9d1662eb2, /* vkEndCommandBuffer */
    0xcf18436e233f62fe, /* vkExportMetalObjectsEXT */
    0xcdd7843304775055, /* vkFlushMappedMemoryRanges */
    0x7ecb7451a7e045ed, /* vkFreeCommandBuffers */
    0x80bb22834c81711a, /* vkFreeDescriptorSets */
    0xf2c5ad0d9aa4acf3, /* vkFreeMemory */
    0x6c52ced389956a1d, /* vkGetAccelerationStructureBuildSizesKHR */
    0x85a37e4af2a5d369, /* vkGetAccelerationStructureDeviceAddressKHR */
    0x9e1cf02c5780b2d6, /* vkGetAccelerationStructureHandleNV */
    0x5c965829c780d9f3, /* vkGetAccelerationStructureMemoryRequirementsNV */
    0x6d4934759c97e7a4, /* vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT */
    0x0e2e5dfee87cb6bc, /* vkGetAndroidHardwareBufferPropertiesANDROID */
    0x2c457bf2268490e8, /* vkGetBufferCollectionPropertiesFUCHSIA */
    0x44fbf4ea4b060b61, /* vkGetBufferDeviceAddress */
    0x399268bd1fae323b, /* vkGetBufferDeviceAddressEXT */
    0x62692fbaea06e05d, /* vkGetBufferDeviceAddressKHR */
    0xc18ca303430c5030, /* vkGetBufferMemoryRequirements */
    0x146940f88e38657b, /* vkGetBufferMemoryRequirements2 */
    0x77ac813268762693, /* vkGetBufferMemoryRequirements2KHR */
    0x5639c874fc9132f4, /* vkGetBufferOpaqueCaptureAddress */
    0x5de8076ffb7af976, /* vkGetBufferOpaqueCaptureAddressKHR */
    0x2f2449681e594992, /* vkGetBufferOpaqueCaptureDescriptorDataEXT */
    0x49a74d66be4fce8b, /* vkGetCalibratedTimestampsEXT */
    0x0c4f4995392e50ab, /* vkGetCalibratedTimestampsKHR */
    0x568b92e4b678bc0d, /* vkGetCudaModuleCacheNV */
    0xe8ddcebfb8abfe62, /* vkGetDeferredOperationMaxConcurrencyKHR */
    0xf325f660479c7872, /* vkGetDeferredOperationResultKHR */
    0x99dfcdbeb70620f3, /* vkGetDescriptorEXT */
    0x9d134d5d5df51d6b, /* vkGetDescriptorSetHostMappingVALVE */
    0x6688394878be035e, /* vkGetDescriptorSetLayoutBindingOffsetEXT */
    0xe67ea7bf4305edd8, /* vkGetDescriptorSetLayoutHostMappingInfoVALVE */
    0xb615047d05c91282, /* vkGetDescriptorSetLayoutSizeEXT */
    0x25f6d470c53abf71, /* vkGetDescriptorSetLayoutSupport */
    0x0f7af59845222e9d, /* vkGetDescriptorSetLayoutSupportKHR */
    0xf88aec90a89de0da, /* vkGetDeviceAccelerationStructureCompatibilityKHR */
    0x15aae27a7223ea5e, /* vkGetDeviceBufferMemoryRequirements */
    0x0e4eac678a76ed33, /* vkGetDeviceBufferMemoryRequirementsKHR */
    0x166f6358bfe0fce0, /* vkGetDeviceFaultInfoEXT */
    0xaf494d1294356cc7, /* vkGetDeviceGroupPeerMemoryFeatures */
    0xe62b971ae0a68532, /* vkGetDeviceGroupPeerMemoryFeaturesKHR */
    0xd537fdf3c85210f2, /* vkGetDeviceGroupPresentCapabilitiesKHR */
    0x9166d9b745afd8af, /* vkGetDeviceGroupSurfacePresentModes2EXT */
    0x32e6d8b01681a0b2, /* vkGetDeviceGroupSurfacePresentModesKHR */
    0x3f4274cc71793a20, /* vkGetDeviceImageMemoryRequirements */
    0xb914845a146232bd, /* vkGetDeviceImageMemoryRequirementsKHR */
    0x987ef1c05cbaa5d8, /* vkGetDeviceImageSparseMemoryRequirements */
    0x423629691279d2c9, /* vkGetDeviceImageSparseMemoryRequirementsKHR */
    0xd1bfa4d3176b81a7, /* vkGetDeviceImageSubresourceLayoutKHR */
    0x40f65d68942eb094, /* vkGetDeviceMemoryCommitment */
    0x9666a70591f64892, /* vkGetDeviceMemoryOpaqueCaptureAddress */
    0x316bebcfe32855b8, /* vkGetDeviceMemoryOpaqueCaptureAddressKHR */
    0x4067528a7c46d3d1, /* vkGetDeviceMicromapCompatibilityEXT */
    0x39595c56305c625a, /* vkGetDeviceProcAddr */
    0x24683f73b0e5e597, /* vkGetDeviceQueue */
    0x37cec3d3b8dc3838, /* vkGetDeviceQueue2 */
    0xcc38e899cdc6433c, /* vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI */
    0xc3d161a58a0be001, /* vkGetDynamicRenderingTilePropertiesQCOM */
    0xd620ed53628cc23d, /* vkGetEncodedVideoSessionParametersKHR */
    0x4e9ad990677f931c, /* vkGetEventStatus */
    0x9c10b26ceb8d7cd4, /* vkGetExecutionGraphPipelineNodeIndexAMDX */
    0x272dc15f9cab3de4, /* vkGetExecutionGraphPipelineScratchSizeAMDX */
    0x7f028870dfbbd7cd, /* vkGetFenceFdKHR */
    0xddc1b3a9e007be5a, /* vkGetFenceStatus */
    0xd70928b0b99ddf51, /* vkGetFenceWin32HandleKHR */
    0xbb471ca7efa2efd6, /* vkGetFramebufferTilePropertiesQCOM */
    0x45568382cd976a58, /* vkGetGeneratedCommandsMemoryRequirementsNV */
    0x85f72ff33d09f9fc, /* vkGetImageDrmFormatModifierPropertiesEXT */
    0x31f122b7cfd4bda7, /* vkGetImageMemoryRequirements */
    0xb69a959653538c19, /* vkGetImageMemoryRequirements2 */
    0x3e094de8a08c3145, /* vkGetImageMemoryRequirements2KHR */
    0x4852117a823da29e, /* vkGetImageOpaqueCaptureDescriptorDataEXT */
    0x21e4a7d810574ab7, /* vkGetImageSparseMemoryRequirements */
    0xa43291af959e4044, /* vkGetImageSparseMemoryRequirements2 */
    0x9cc130ca400434b7, /* vkGetImageSparseMemoryRequirements2KHR */
    0x23d7885b70c5f681, /* vkGetImageSubresourceLayout */
    0x724faacf94fc9fe1, /* vkGetImageSubresourceLayout2EXT */
    0xfa88974bd2f1055c, /* vkGetImageSubresourceLayout2KHR */
    0x2c6e7da8d69f6259, /* vkGetImageViewAddressNVX */
    0x1b250d8529b8c649, /* vkGetImageViewHandleNVX */
    0x26037ce5b636f47f, /* vkGetImageViewOpaqueCaptureDescriptorDataEXT */
    0xf1696abc2816c1f0, /* vkGetLatencyTimingsNV */
    0x821ae6559b48f066, /* vkGetMemoryAndroidHardwareBufferANDROID */
    0x2ed749f13375a993, /* vkGetMemoryFdKHR */
    0x12e6b027ea2149c2, /* vkGetMemoryFdPropertiesKHR */
    0x70cfd8006341080a, /* vkGetMemoryHostPointerPropertiesEXT */
    0x5ee3413a16ecc62a, /* vkGetMemoryRemoteAddressNV */
    0xcda4a94d2c8596f7, /* vkGetMemoryWin32HandleKHR */
    0xc21c28ddac3fbec3, /* vkGetMemoryWin32HandleNV */
    0xce5d77a823daf981, /* vkGetMemoryWin32HandlePropertiesKHR */
    0xbde4c14636640d82, /* vkGetMemoryZirconHandleFUCHSIA */
    0xc77b0aec1b685e42, /* vkGetMemoryZirconHandlePropertiesFUCHSIA */
    0x3683952ff1e39c69, /* vkGetMicromapBuildSizesEXT */
    0x5dcda38c668184b8, /* vkGetPastPresentationTimingGOOGLE */
    0x49bda364217fc34a, /* vkGetPerformanceParameterINTEL */
    0x3446c4b0e0ed13c7, /* vkGetPipelineBinaryDataKHR */
    0x17bb294acabe6a88, /* vkGetPipelineCacheData */
    0x482cb3433b920f78, /* vkGetPipelineExecutableInternalRepresentationsKHR */
    0xf8010e878fa40163, /* vkGetPipelineExecutablePropertiesKHR */
    0x5001dcd798e4f3a8, /* vkGetPipelineExecutableStatisticsKHR */
    0x076d9ee8752c3cd2, /* vkGetPipelineIndirectDeviceAddressNV */
    0xd8b91a19d2c84eba, /* vkGetPipelineIndirectMemoryRequirementsNV */
    0xe7ba2bcf3218ef91, /* vkGetPipelineKeyKHR */
    0x6987d1107990db8b, /* vkGetPipelinePropertiesEXT */
    0xe43a4f01acf5a1b6, /* vkGetPrivateData */
    0x8da528a7d8e71c4a, /* vkGetPrivateDataEXT */
    0x6b902433192f7f5d, /* vkGetQueryPoolResults */
    0x66d07f2af74e8d8b, /* vkGetQueueCheckpointData2NV */
    0x3d8f82b873097a02, /* vkGetQueueCheckpointDataNV */
    0x860a89bcaf7d40af, /* vkGetRayTracingCaptureReplayShaderGroupHandlesKHR */
    0x0802604e7494d3a4, /* vkGetRayTracingShaderGroupHandlesKHR */
    0x8bd0b4949f3f2aa3, /* vkGetRayTracingShaderGroupHandlesNV */
    0xdd609c8b8fed0093, /* vkGetRayTracingShaderGroupStackSizeKHR */
    0x9fd2d4176909d303, /* vkGetRefreshCycleDurationGOOGLE */
    0xcfd90dd84e50b6e2, /* vkGetRenderAreaGranularity */
    0xff17500f60079a4b, /* vkGetRenderingAreaGranularityKHR */
    0x5d99174ab12822bd, /* vkGetSamplerOpaqueCaptureDescriptorDataEXT */
    0xe2152f86c3e27268, /* vkGetScreenBufferPropertiesQNX */
    0xd60ca89f1c84b347, /* vkGetSemaphoreCounterValue */
    0x4f323238bf52cee6, /* vkGetSemaphoreCounterValueKHR */
    0x140ab11fc9190c09, /* vkGetSemaphoreFdKHR */
    0xe7cfb8155a9ec7f4, /* vkGetSemaphoreWin32HandleKHR */
    0xb3fc6ad1eebe5d90, /* vkGetSemaphoreZirconHandleFUCHSIA */
    0x8b087bf937ffd567, /* vkGetShaderBinaryDataEXT */
    0x899487a9c9bfa851, /* vkGetShaderInfoAMD */
    0x2ad0e3cb5f37720f, /* vkGetShaderModuleCreateInfoIdentifierEXT */
    0x0602c29db03eb8ab, /* vkGetShaderModuleIdentifierEXT */
    0x04134f0c5694394f, /* vkGetSwapchainCounterEXT */
    0xe3e71921cd13bc5f, /* vkGetSwapchainImagesKHR */
    0x5df941fbd5ee53ed, /* vkGetSwapchainStatusKHR */
    0x10635a7a4fcc2c76, /* vkGetValidationCacheDataEXT */
    0x34c3a6eee5758a70, /* vkGetVideoSessionMemoryRequirementsKHR */
    0xe753bab9908ecda8, /* vkImportFenceFdKHR */
    0x8aa9a6ca90bcc785, /* vkImportFenceWin32HandleKHR */
    0xebc09d555d9390f1, /* vkImportSemaphoreFdKHR */
    0xe66bc79887578e01, /* vkImportSemaphoreWin32HandleKHR */
    0x334314efb11c7144, /* vkImportSemaphoreZirconHandleFUCHSIA */
    0xaaee8606a2f000f3, /* vkInitializePerformanceApiINTEL */
    0x3a0a07834723853e, /* vkInvalidateMappedMemoryRanges */
    0x7f231d810d3308b5, /* vkLatencySleepNV */
    0x808f7434b0596604, /* vkMapMemory */
    0x34bfbbd6c34bac46, /* vkMapMemory2KHR */
    0xcfbd6aad8345b609, /* vkMergePipelineCaches */
    0x91b293db19f39ca5, /* vkMergeValidationCachesEXT */
    0xd88e4fe9c0329771, /* vkQueueBeginDebugUtilsLabelEXT */
    0x814945b3834b2f13, /* vkQueueBindSparse */
    0x6756af5e610d6533, /* vkQueueEndDebugUtilsLabelEXT */
    0xe2b6c462d682d0aa, /* vkQueueInsertDebugUtilsLabelEXT */
    0x43962ea5cc322bab, /* vkQueueNotifyOutOfBandNV */
    0x003f01982149c676, /* vkQueuePresentKHR */
    0x22611ab44638175f, /* vkQueueSetPerformanceConfigurationINTEL */
    0x0c3e489641018fd0, /* vkQueueSubmit */
    0x60464991fe32093e, /* vkQueueSubmit2 */
    0x7eff5818fce6b445, /* vkQueueSubmit2KHR */
    0x1fce1bdecaf06b52, /* vkQueueWaitIdle */
    0x8a4301ac1aeca958, /* vkRegisterDeviceEventEXT */
    0x21f4e40d1b10ea20, /* vkRegisterDisplayEventEXT */
    0x8f433193cdb26798, /* vkReleaseCapturedPipelineDataKHR */
    0xdad4b40f2b59becc, /* vkReleaseFullScreenExclusiveModeEXT */
    0x480770881849ff9e, /* vkReleasePerformanceConfigurationINTEL */
    0x0a9e4edad7617bf4, /* vkReleaseProfilingLockKHR */
    0x09e9bc32d119dd75, /* vkReleaseSwapchainImagesEXT */
    0xc6fee3fca12fb11e, /* vkResetCommandBuffer */
    0x1e931402fc057014, /* vkResetCommandPool */
    0xa6007e58158aed7d, /* vkResetDescriptorPool */
    0x2e0b5702efb33535, /* vkResetEvent */
    0x234a880591facce1, /* vkResetFences */
    0xd34524d6520a5733, /* vkResetQueryPool */
    0x40648ed2af7eecdd, /* vkResetQueryPoolEXT */
    0x36d94ea1570378f7, /* vkSetBufferCollectionBufferConstraintsFUCHSIA */
    0xd10afc8461e339f2, /* vkSetBufferCollectionImageConstraintsFUCHSIA */
    0xfccd697bc5cf4494, /* vkSetDebugUtilsObjectNameEXT */
    0x7fd35824391d47a4, /* vkSetDebugUtilsObjectTagEXT */
    0x6124012503a7634c, /* vkSetDeviceMemoryPriorityEXT */
    0xd0df5f67ee24e975, /* vkSetEvent */
    0x35a324447b0101e4, /* vkSetHdrMetadataEXT */
    0x5e82c425367c6366, /* vkSetLatencyMarkerNV */
    0xc3167c9cdfe12247, /* vkSetLatencySleepModeNV */
    0x7629dff55e4d0af3, /* vkSetLocalDimmingAMD */
    0x2384403e82f430b9, /* vkSetPrivateData */
    0xc2f02663a1a88208, /* vkSetPrivateDataEXT */
    0x6a0ad52ae1fd239d, /* vkSignalSemaphore */
    0xb8f7f65305fa9c04, /* vkSignalSemaphoreKHR */
    0x233da64d987f39c6, /* vkTransitionImageLayoutEXT */
    0x620e4a899bc7e882, /* vkTrimCommandPool */
    0x73f1f198f822a45e, /* vkTrimCommandPoolKHR */
    0xef99360f052b923d, /* vkUninitializePerformanceApiINTEL */
    0xf51a3c7f77277e37, /* vkUnmapMemory */
    0x345a6d44742dd550, /* vkUnmapMemory2KHR */
    0x1ebd0c97c69da82b, /* vkUpdateDescriptorSetWithTemplate */
    0x71b8cb2fd8159c3d, /* vkUpdateDescriptorSetWithTemplateKHR */
    0xaac33dd01204ea6d, /* vkUpdateDescriptorSets */
    0x0baf9d7df0a788b5, /* vkUpdateVideoSessionParametersKHR */
    0x7c1238295eaa98e9, /* vkWaitForFences */
    0x958f70568135c547, /* vkWaitForPresentKHR */
    0x464cdf5591d873eb, /* vkWaitSemaphores */
    0x90b98ea73daf2fc7, /* vkWaitSemaphoresKHR */
    0xbe6ba58fe9b83a9f, /* vkWriteAccelerationStructuresPropertiesKHR */
    0x11a78b6266b8d57c, /* vkWriteMicromapsPropertiesEXT */
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
