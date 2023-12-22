/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <glad/vulkan.h>

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
    "vkAcquireDrmDisplayEXT", // 0
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    "vkAcquireFullScreenExclusiveModeEXT", // 1
#else
    NULL, // 1
#endif
    "vkAcquireNextImage2KHR", // 2
    "vkAcquireNextImageKHR", // 3
    "vkAcquirePerformanceConfigurationINTEL", // 4
    "vkAcquireProfilingLockKHR", // 5
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    "vkAcquireWinrtDisplayNV", // 6
#else
    NULL, // 6
#endif
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    "vkAcquireXlibDisplayEXT", // 7
#else
    NULL, // 7
#endif
    "vkAllocateCommandBuffers", // 8
    "vkAllocateDescriptorSets", // 9
    "vkAllocateMemory", // 10
    "vkBeginCommandBuffer", // 11
    "vkBindAccelerationStructureMemoryNV", // 12
    "vkBindBufferMemory", // 13
    "vkBindBufferMemory2", // 14
    "vkBindBufferMemory2KHR", // 15
    "vkBindImageMemory", // 16
    "vkBindImageMemory2", // 17
    "vkBindImageMemory2KHR", // 18
    "vkBindOpticalFlowSessionImageNV", // 19
    "vkBindVideoSessionMemoryKHR", // 20
    "vkBuildAccelerationStructuresKHR", // 21
    "vkBuildMicromapsEXT", // 22
    "vkCmdBeginConditionalRenderingEXT", // 23
    "vkCmdBeginDebugUtilsLabelEXT", // 24
    "vkCmdBeginQuery", // 25
    "vkCmdBeginQueryIndexedEXT", // 26
    "vkCmdBeginRenderPass", // 27
    "vkCmdBeginRenderPass2", // 28
    "vkCmdBeginRenderPass2KHR", // 29
    "vkCmdBeginRendering", // 30
    "vkCmdBeginRenderingKHR", // 31
    "vkCmdBeginTransformFeedbackEXT", // 32
    "vkCmdBeginVideoCodingKHR", // 33
    "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT", // 34
    "vkCmdBindDescriptorBufferEmbeddedSamplersEXT", // 35
    "vkCmdBindDescriptorBuffersEXT", // 36
    "vkCmdBindDescriptorSets", // 37
    "vkCmdBindDescriptorSets2KHR", // 38
    "vkCmdBindIndexBuffer", // 39
    "vkCmdBindIndexBuffer2KHR", // 40
    "vkCmdBindInvocationMaskHUAWEI", // 41
    "vkCmdBindPipeline", // 42
    "vkCmdBindPipelineShaderGroupNV", // 43
    "vkCmdBindShadersEXT", // 44
    "vkCmdBindShadingRateImageNV", // 45
    "vkCmdBindTransformFeedbackBuffersEXT", // 46
    "vkCmdBindVertexBuffers", // 47
    "vkCmdBindVertexBuffers2", // 48
    "vkCmdBindVertexBuffers2EXT", // 49
    "vkCmdBlitImage", // 50
    "vkCmdBlitImage2", // 51
    "vkCmdBlitImage2KHR", // 52
    "vkCmdBuildAccelerationStructureNV", // 53
    "vkCmdBuildAccelerationStructuresIndirectKHR", // 54
    "vkCmdBuildAccelerationStructuresKHR", // 55
    "vkCmdBuildMicromapsEXT", // 56
    "vkCmdClearAttachments", // 57
    "vkCmdClearColorImage", // 58
    "vkCmdClearDepthStencilImage", // 59
    "vkCmdControlVideoCodingKHR", // 60
    "vkCmdCopyAccelerationStructureKHR", // 61
    "vkCmdCopyAccelerationStructureNV", // 62
    "vkCmdCopyAccelerationStructureToMemoryKHR", // 63
    "vkCmdCopyBuffer", // 64
    "vkCmdCopyBuffer2", // 65
    "vkCmdCopyBuffer2KHR", // 66
    "vkCmdCopyBufferToImage", // 67
    "vkCmdCopyBufferToImage2", // 68
    "vkCmdCopyBufferToImage2KHR", // 69
    "vkCmdCopyImage", // 70
    "vkCmdCopyImage2", // 71
    "vkCmdCopyImage2KHR", // 72
    "vkCmdCopyImageToBuffer", // 73
    "vkCmdCopyImageToBuffer2", // 74
    "vkCmdCopyImageToBuffer2KHR", // 75
    "vkCmdCopyMemoryIndirectNV", // 76
    "vkCmdCopyMemoryToAccelerationStructureKHR", // 77
    "vkCmdCopyMemoryToImageIndirectNV", // 78
    "vkCmdCopyMemoryToMicromapEXT", // 79
    "vkCmdCopyMicromapEXT", // 80
    "vkCmdCopyMicromapToMemoryEXT", // 81
    "vkCmdCopyQueryPoolResults", // 82
    "vkCmdCuLaunchKernelNVX", // 83
    "vkCmdCudaLaunchKernelNV", // 84
    "vkCmdDebugMarkerBeginEXT", // 85
    "vkCmdDebugMarkerEndEXT", // 86
    "vkCmdDebugMarkerInsertEXT", // 87
    "vkCmdDecodeVideoKHR", // 88
    "vkCmdDecompressMemoryIndirectCountNV", // 89
    "vkCmdDecompressMemoryNV", // 90
    "vkCmdDispatch", // 91
    "vkCmdDispatchBase", // 92
    "vkCmdDispatchBaseKHR", // 93
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    "vkCmdDispatchGraphAMDX", // 94
#else
    NULL, // 94
#endif
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    "vkCmdDispatchGraphIndirectAMDX", // 95
#else
    NULL, // 95
#endif
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    "vkCmdDispatchGraphIndirectCountAMDX", // 96
#else
    NULL, // 96
#endif
    "vkCmdDispatchIndirect", // 97
    "vkCmdDraw", // 98
    "vkCmdDrawClusterHUAWEI", // 99
    "vkCmdDrawClusterIndirectHUAWEI", // 100
    "vkCmdDrawIndexed", // 101
    "vkCmdDrawIndexedIndirect", // 102
    "vkCmdDrawIndexedIndirectCount", // 103
    "vkCmdDrawIndexedIndirectCountAMD", // 104
    "vkCmdDrawIndexedIndirectCountKHR", // 105
    "vkCmdDrawIndirect", // 106
    "vkCmdDrawIndirectByteCountEXT", // 107
    "vkCmdDrawIndirectCount", // 108
    "vkCmdDrawIndirectCountAMD", // 109
    "vkCmdDrawIndirectCountKHR", // 110
    "vkCmdDrawMeshTasksEXT", // 111
    "vkCmdDrawMeshTasksIndirectCountEXT", // 112
    "vkCmdDrawMeshTasksIndirectCountNV", // 113
    "vkCmdDrawMeshTasksIndirectEXT", // 114
    "vkCmdDrawMeshTasksIndirectNV", // 115
    "vkCmdDrawMeshTasksNV", // 116
    "vkCmdDrawMultiEXT", // 117
    "vkCmdDrawMultiIndexedEXT", // 118
    "vkCmdEncodeVideoKHR", // 119
    "vkCmdEndConditionalRenderingEXT", // 120
    "vkCmdEndDebugUtilsLabelEXT", // 121
    "vkCmdEndQuery", // 122
    "vkCmdEndQueryIndexedEXT", // 123
    "vkCmdEndRenderPass", // 124
    "vkCmdEndRenderPass2", // 125
    "vkCmdEndRenderPass2KHR", // 126
    "vkCmdEndRendering", // 127
    "vkCmdEndRenderingKHR", // 128
    "vkCmdEndTransformFeedbackEXT", // 129
    "vkCmdEndVideoCodingKHR", // 130
    "vkCmdExecuteCommands", // 131
    "vkCmdExecuteGeneratedCommandsNV", // 132
    "vkCmdFillBuffer", // 133
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    "vkCmdInitializeGraphScratchMemoryAMDX", // 134
#else
    NULL, // 134
#endif
    "vkCmdInsertDebugUtilsLabelEXT", // 135
    "vkCmdNextSubpass", // 136
    "vkCmdNextSubpass2", // 137
    "vkCmdNextSubpass2KHR", // 138
    "vkCmdOpticalFlowExecuteNV", // 139
    "vkCmdPipelineBarrier", // 140
    "vkCmdPipelineBarrier2", // 141
    "vkCmdPipelineBarrier2KHR", // 142
    "vkCmdPreprocessGeneratedCommandsNV", // 143
    "vkCmdPushConstants", // 144
    "vkCmdPushConstants2KHR", // 145
    "vkCmdPushDescriptorSet2KHR", // 146
    "vkCmdPushDescriptorSetKHR", // 147
    "vkCmdPushDescriptorSetWithTemplate2KHR", // 148
    "vkCmdPushDescriptorSetWithTemplateKHR", // 149
    "vkCmdResetEvent", // 150
    "vkCmdResetEvent2", // 151
    "vkCmdResetEvent2KHR", // 152
    "vkCmdResetQueryPool", // 153
    "vkCmdResolveImage", // 154
    "vkCmdResolveImage2", // 155
    "vkCmdResolveImage2KHR", // 156
    "vkCmdSetAlphaToCoverageEnableEXT", // 157
    "vkCmdSetAlphaToOneEnableEXT", // 158
    "vkCmdSetAttachmentFeedbackLoopEnableEXT", // 159
    "vkCmdSetBlendConstants", // 160
    "vkCmdSetCheckpointNV", // 161
    "vkCmdSetCoarseSampleOrderNV", // 162
    "vkCmdSetColorBlendAdvancedEXT", // 163
    "vkCmdSetColorBlendEnableEXT", // 164
    "vkCmdSetColorBlendEquationEXT", // 165
    "vkCmdSetColorWriteEnableEXT", // 166
    "vkCmdSetColorWriteMaskEXT", // 167
    "vkCmdSetConservativeRasterizationModeEXT", // 168
    "vkCmdSetCoverageModulationModeNV", // 169
    "vkCmdSetCoverageModulationTableEnableNV", // 170
    "vkCmdSetCoverageModulationTableNV", // 171
    "vkCmdSetCoverageReductionModeNV", // 172
    "vkCmdSetCoverageToColorEnableNV", // 173
    "vkCmdSetCoverageToColorLocationNV", // 174
    "vkCmdSetCullMode", // 175
    "vkCmdSetCullModeEXT", // 176
    "vkCmdSetDepthBias", // 177
    "vkCmdSetDepthBias2EXT", // 178
    "vkCmdSetDepthBiasEnable", // 179
    "vkCmdSetDepthBiasEnableEXT", // 180
    "vkCmdSetDepthBounds", // 181
    "vkCmdSetDepthBoundsTestEnable", // 182
    "vkCmdSetDepthBoundsTestEnableEXT", // 183
    "vkCmdSetDepthClampEnableEXT", // 184
    "vkCmdSetDepthClipEnableEXT", // 185
    "vkCmdSetDepthClipNegativeOneToOneEXT", // 186
    "vkCmdSetDepthCompareOp", // 187
    "vkCmdSetDepthCompareOpEXT", // 188
    "vkCmdSetDepthTestEnable", // 189
    "vkCmdSetDepthTestEnableEXT", // 190
    "vkCmdSetDepthWriteEnable", // 191
    "vkCmdSetDepthWriteEnableEXT", // 192
    "vkCmdSetDescriptorBufferOffsets2EXT", // 193
    "vkCmdSetDescriptorBufferOffsetsEXT", // 194
    "vkCmdSetDeviceMask", // 195
    "vkCmdSetDeviceMaskKHR", // 196
    "vkCmdSetDiscardRectangleEXT", // 197
    "vkCmdSetDiscardRectangleEnableEXT", // 198
    "vkCmdSetDiscardRectangleModeEXT", // 199
    "vkCmdSetEvent", // 200
    "vkCmdSetEvent2", // 201
    "vkCmdSetEvent2KHR", // 202
    "vkCmdSetExclusiveScissorEnableNV", // 203
    "vkCmdSetExclusiveScissorNV", // 204
    "vkCmdSetExtraPrimitiveOverestimationSizeEXT", // 205
    "vkCmdSetFragmentShadingRateEnumNV", // 206
    "vkCmdSetFragmentShadingRateKHR", // 207
    "vkCmdSetFrontFace", // 208
    "vkCmdSetFrontFaceEXT", // 209
    "vkCmdSetLineRasterizationModeEXT", // 210
    "vkCmdSetLineStippleEXT", // 211
    "vkCmdSetLineStippleEnableEXT", // 212
    "vkCmdSetLineWidth", // 213
    "vkCmdSetLogicOpEXT", // 214
    "vkCmdSetLogicOpEnableEXT", // 215
    "vkCmdSetPatchControlPointsEXT", // 216
    "vkCmdSetPerformanceMarkerINTEL", // 217
    "vkCmdSetPerformanceOverrideINTEL", // 218
    "vkCmdSetPerformanceStreamMarkerINTEL", // 219
    "vkCmdSetPolygonModeEXT", // 220
    "vkCmdSetPrimitiveRestartEnable", // 221
    "vkCmdSetPrimitiveRestartEnableEXT", // 222
    "vkCmdSetPrimitiveTopology", // 223
    "vkCmdSetPrimitiveTopologyEXT", // 224
    "vkCmdSetProvokingVertexModeEXT", // 225
    "vkCmdSetRasterizationSamplesEXT", // 226
    "vkCmdSetRasterizationStreamEXT", // 227
    "vkCmdSetRasterizerDiscardEnable", // 228
    "vkCmdSetRasterizerDiscardEnableEXT", // 229
    "vkCmdSetRayTracingPipelineStackSizeKHR", // 230
    "vkCmdSetRepresentativeFragmentTestEnableNV", // 231
    "vkCmdSetSampleLocationsEXT", // 232
    "vkCmdSetSampleLocationsEnableEXT", // 233
    "vkCmdSetSampleMaskEXT", // 234
    "vkCmdSetScissor", // 235
    "vkCmdSetScissorWithCount", // 236
    "vkCmdSetScissorWithCountEXT", // 237
    "vkCmdSetShadingRateImageEnableNV", // 238
    "vkCmdSetStencilCompareMask", // 239
    "vkCmdSetStencilOp", // 240
    "vkCmdSetStencilOpEXT", // 241
    "vkCmdSetStencilReference", // 242
    "vkCmdSetStencilTestEnable", // 243
    "vkCmdSetStencilTestEnableEXT", // 244
    "vkCmdSetStencilWriteMask", // 245
    "vkCmdSetTessellationDomainOriginEXT", // 246
    "vkCmdSetVertexInputEXT", // 247
    "vkCmdSetViewport", // 248
    "vkCmdSetViewportShadingRatePaletteNV", // 249
    "vkCmdSetViewportSwizzleNV", // 250
    "vkCmdSetViewportWScalingEnableNV", // 251
    "vkCmdSetViewportWScalingNV", // 252
    "vkCmdSetViewportWithCount", // 253
    "vkCmdSetViewportWithCountEXT", // 254
    "vkCmdSubpassShadingHUAWEI", // 255
    "vkCmdTraceRaysIndirect2KHR", // 256
    "vkCmdTraceRaysIndirectKHR", // 257
    "vkCmdTraceRaysKHR", // 258
    "vkCmdTraceRaysNV", // 259
    "vkCmdUpdateBuffer", // 260
    "vkCmdUpdatePipelineIndirectBufferNV", // 261
    "vkCmdWaitEvents", // 262
    "vkCmdWaitEvents2", // 263
    "vkCmdWaitEvents2KHR", // 264
    "vkCmdWriteAccelerationStructuresPropertiesKHR", // 265
    "vkCmdWriteAccelerationStructuresPropertiesNV", // 266
    "vkCmdWriteBufferMarker2AMD", // 267
    "vkCmdWriteBufferMarkerAMD", // 268
    "vkCmdWriteMicromapsPropertiesEXT", // 269
    "vkCmdWriteTimestamp", // 270
    "vkCmdWriteTimestamp2", // 271
    "vkCmdWriteTimestamp2KHR", // 272
    "vkCompileDeferredNV", // 273
    "vkCopyAccelerationStructureKHR", // 274
    "vkCopyAccelerationStructureToMemoryKHR", // 275
    "vkCopyImageToImageEXT", // 276
    "vkCopyImageToMemoryEXT", // 277
    "vkCopyMemoryToAccelerationStructureKHR", // 278
    "vkCopyMemoryToImageEXT", // 279
    "vkCopyMemoryToMicromapEXT", // 280
    "vkCopyMicromapEXT", // 281
    "vkCopyMicromapToMemoryEXT", // 282
    "vkCreateAccelerationStructureKHR", // 283
    "vkCreateAccelerationStructureNV", // 284
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    "vkCreateAndroidSurfaceKHR", // 285
#else
    NULL, // 285
#endif
    "vkCreateBuffer", // 286
#if defined(VK_USE_PLATFORM_FUCHSIA)
    "vkCreateBufferCollectionFUCHSIA", // 287
#else
    NULL, // 287
#endif
    "vkCreateBufferView", // 288
    "vkCreateCommandPool", // 289
    "vkCreateComputePipelines", // 290
    "vkCreateCuFunctionNVX", // 291
    "vkCreateCuModuleNVX", // 292
    "vkCreateCudaFunctionNV", // 293
    "vkCreateCudaModuleNV", // 294
    "vkCreateDebugReportCallbackEXT", // 295
    "vkCreateDebugUtilsMessengerEXT", // 296
    "vkCreateDeferredOperationKHR", // 297
    "vkCreateDescriptorPool", // 298
    "vkCreateDescriptorSetLayout", // 299
    "vkCreateDescriptorUpdateTemplate", // 300
    "vkCreateDescriptorUpdateTemplateKHR", // 301
    "vkCreateDevice", // 302
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    "vkCreateDirectFBSurfaceEXT", // 303
#else
    NULL, // 303
#endif
    "vkCreateDisplayModeKHR", // 304
    "vkCreateDisplayPlaneSurfaceKHR", // 305
    "vkCreateEvent", // 306
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    "vkCreateExecutionGraphPipelinesAMDX", // 307
#else
    NULL, // 307
#endif
    "vkCreateFence", // 308
    "vkCreateFramebuffer", // 309
    "vkCreateGraphicsPipelines", // 310
    "vkCreateHeadlessSurfaceEXT", // 311
#if defined(VK_USE_PLATFORM_IOS_MVK)
    "vkCreateIOSSurfaceMVK", // 312
#else
    NULL, // 312
#endif
    "vkCreateImage", // 313
#if defined(VK_USE_PLATFORM_FUCHSIA)
    "vkCreateImagePipeSurfaceFUCHSIA", // 314
#else
    NULL, // 314
#endif
    "vkCreateImageView", // 315
    "vkCreateIndirectCommandsLayoutNV", // 316
    "vkCreateInstance", // 317
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    "vkCreateMacOSSurfaceMVK", // 318
#else
    NULL, // 318
#endif
#if defined(VK_USE_PLATFORM_METAL_EXT)
    "vkCreateMetalSurfaceEXT", // 319
#else
    NULL, // 319
#endif
    "vkCreateMicromapEXT", // 320
    "vkCreateOpticalFlowSessionNV", // 321
    "vkCreatePipelineCache", // 322
    "vkCreatePipelineLayout", // 323
    "vkCreatePrivateDataSlot", // 324
    "vkCreatePrivateDataSlotEXT", // 325
    "vkCreateQueryPool", // 326
    "vkCreateRayTracingPipelinesKHR", // 327
    "vkCreateRayTracingPipelinesNV", // 328
    "vkCreateRenderPass", // 329
    "vkCreateRenderPass2", // 330
    "vkCreateRenderPass2KHR", // 331
    "vkCreateSampler", // 332
    "vkCreateSamplerYcbcrConversion", // 333
    "vkCreateSamplerYcbcrConversionKHR", // 334
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    "vkCreateScreenSurfaceQNX", // 335
#else
    NULL, // 335
#endif
    "vkCreateSemaphore", // 336
    "vkCreateShaderModule", // 337
    "vkCreateShadersEXT", // 338
    "vkCreateSharedSwapchainsKHR", // 339
#if defined(VK_USE_PLATFORM_GGP)
    "vkCreateStreamDescriptorSurfaceGGP", // 340
#else
    NULL, // 340
#endif
    "vkCreateSwapchainKHR", // 341
    "vkCreateValidationCacheEXT", // 342
#if defined(VK_USE_PLATFORM_VI_NN)
    "vkCreateViSurfaceNN", // 343
#else
    NULL, // 343
#endif
    "vkCreateVideoSessionKHR", // 344
    "vkCreateVideoSessionParametersKHR", // 345
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    "vkCreateWaylandSurfaceKHR", // 346
#else
    NULL, // 346
#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    "vkCreateWin32SurfaceKHR", // 347
#else
    NULL, // 347
#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
    "vkCreateXcbSurfaceKHR", // 348
#else
    NULL, // 348
#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    "vkCreateXlibSurfaceKHR", // 349
#else
    NULL, // 349
#endif
    "vkDebugMarkerSetObjectNameEXT", // 350
    "vkDebugMarkerSetObjectTagEXT", // 351
    "vkDebugReportMessageEXT", // 352
    "vkDeferredOperationJoinKHR", // 353
    "vkDestroyAccelerationStructureKHR", // 354
    "vkDestroyAccelerationStructureNV", // 355
    "vkDestroyBuffer", // 356
#if defined(VK_USE_PLATFORM_FUCHSIA)
    "vkDestroyBufferCollectionFUCHSIA", // 357
#else
    NULL, // 357
#endif
    "vkDestroyBufferView", // 358
    "vkDestroyCommandPool", // 359
    "vkDestroyCuFunctionNVX", // 360
    "vkDestroyCuModuleNVX", // 361
    "vkDestroyCudaFunctionNV", // 362
    "vkDestroyCudaModuleNV", // 363
    "vkDestroyDebugReportCallbackEXT", // 364
    "vkDestroyDebugUtilsMessengerEXT", // 365
    "vkDestroyDeferredOperationKHR", // 366
    "vkDestroyDescriptorPool", // 367
    "vkDestroyDescriptorSetLayout", // 368
    "vkDestroyDescriptorUpdateTemplate", // 369
    "vkDestroyDescriptorUpdateTemplateKHR", // 370
    "vkDestroyDevice", // 371
    "vkDestroyEvent", // 372
    "vkDestroyFence", // 373
    "vkDestroyFramebuffer", // 374
    "vkDestroyImage", // 375
    "vkDestroyImageView", // 376
    "vkDestroyIndirectCommandsLayoutNV", // 377
    "vkDestroyInstance", // 378
    "vkDestroyMicromapEXT", // 379
    "vkDestroyOpticalFlowSessionNV", // 380
    "vkDestroyPipeline", // 381
    "vkDestroyPipelineCache", // 382
    "vkDestroyPipelineLayout", // 383
    "vkDestroyPrivateDataSlot", // 384
    "vkDestroyPrivateDataSlotEXT", // 385
    "vkDestroyQueryPool", // 386
    "vkDestroyRenderPass", // 387
    "vkDestroySampler", // 388
    "vkDestroySamplerYcbcrConversion", // 389
    "vkDestroySamplerYcbcrConversionKHR", // 390
    "vkDestroySemaphore", // 391
    "vkDestroyShaderEXT", // 392
    "vkDestroyShaderModule", // 393
    "vkDestroySurfaceKHR", // 394
    "vkDestroySwapchainKHR", // 395
    "vkDestroyValidationCacheEXT", // 396
    "vkDestroyVideoSessionKHR", // 397
    "vkDestroyVideoSessionParametersKHR", // 398
    "vkDeviceWaitIdle", // 399
    "vkDisplayPowerControlEXT", // 400
    "vkEndCommandBuffer", // 401
    "vkEnumerateDeviceExtensionProperties", // 402
    "vkEnumerateDeviceLayerProperties", // 403
    "vkEnumerateInstanceExtensionProperties", // 404
    "vkEnumerateInstanceLayerProperties", // 405
    "vkEnumerateInstanceVersion", // 406
    "vkEnumeratePhysicalDeviceGroups", // 407
    "vkEnumeratePhysicalDeviceGroupsKHR", // 408
    "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR", // 409
    "vkEnumeratePhysicalDevices", // 410
#if defined(VK_USE_PLATFORM_METAL_EXT)
    "vkExportMetalObjectsEXT", // 411
#else
    NULL, // 411
#endif
    "vkFlushMappedMemoryRanges", // 412
    "vkFreeCommandBuffers", // 413
    "vkFreeDescriptorSets", // 414
    "vkFreeMemory", // 415
    "vkGetAccelerationStructureBuildSizesKHR", // 416
    "vkGetAccelerationStructureDeviceAddressKHR", // 417
    "vkGetAccelerationStructureHandleNV", // 418
    "vkGetAccelerationStructureMemoryRequirementsNV", // 419
    "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT", // 420
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    "vkGetAndroidHardwareBufferPropertiesANDROID", // 421
#else
    NULL, // 421
#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
    "vkGetBufferCollectionPropertiesFUCHSIA", // 422
#else
    NULL, // 422
#endif
    "vkGetBufferDeviceAddress", // 423
    "vkGetBufferDeviceAddressEXT", // 424
    "vkGetBufferDeviceAddressKHR", // 425
    "vkGetBufferMemoryRequirements", // 426
    "vkGetBufferMemoryRequirements2", // 427
    "vkGetBufferMemoryRequirements2KHR", // 428
    "vkGetBufferOpaqueCaptureAddress", // 429
    "vkGetBufferOpaqueCaptureAddressKHR", // 430
    "vkGetBufferOpaqueCaptureDescriptorDataEXT", // 431
    "vkGetCalibratedTimestampsEXT", // 432
    "vkGetCalibratedTimestampsKHR", // 433
    "vkGetCudaModuleCacheNV", // 434
    "vkGetDeferredOperationMaxConcurrencyKHR", // 435
    "vkGetDeferredOperationResultKHR", // 436
    "vkGetDescriptorEXT", // 437
    "vkGetDescriptorSetHostMappingVALVE", // 438
    "vkGetDescriptorSetLayoutBindingOffsetEXT", // 439
    "vkGetDescriptorSetLayoutHostMappingInfoVALVE", // 440
    "vkGetDescriptorSetLayoutSizeEXT", // 441
    "vkGetDescriptorSetLayoutSupport", // 442
    "vkGetDescriptorSetLayoutSupportKHR", // 443
    "vkGetDeviceAccelerationStructureCompatibilityKHR", // 444
    "vkGetDeviceBufferMemoryRequirements", // 445
    "vkGetDeviceBufferMemoryRequirementsKHR", // 446
    "vkGetDeviceFaultInfoEXT", // 447
    "vkGetDeviceGroupPeerMemoryFeatures", // 448
    "vkGetDeviceGroupPeerMemoryFeaturesKHR", // 449
    "vkGetDeviceGroupPresentCapabilitiesKHR", // 450
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    "vkGetDeviceGroupSurfacePresentModes2EXT", // 451
#else
    NULL, // 451
#endif
    "vkGetDeviceGroupSurfacePresentModesKHR", // 452
    "vkGetDeviceImageMemoryRequirements", // 453
    "vkGetDeviceImageMemoryRequirementsKHR", // 454
    "vkGetDeviceImageSparseMemoryRequirements", // 455
    "vkGetDeviceImageSparseMemoryRequirementsKHR", // 456
    "vkGetDeviceImageSubresourceLayoutKHR", // 457
    "vkGetDeviceMemoryCommitment", // 458
    "vkGetDeviceMemoryOpaqueCaptureAddress", // 459
    "vkGetDeviceMemoryOpaqueCaptureAddressKHR", // 460
    "vkGetDeviceMicromapCompatibilityEXT", // 461
    "vkGetDeviceProcAddr", // 462
    "vkGetDeviceQueue", // 463
    "vkGetDeviceQueue2", // 464
    "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI", // 465
    "vkGetDisplayModeProperties2KHR", // 466
    "vkGetDisplayModePropertiesKHR", // 467
    "vkGetDisplayPlaneCapabilities2KHR", // 468
    "vkGetDisplayPlaneCapabilitiesKHR", // 469
    "vkGetDisplayPlaneSupportedDisplaysKHR", // 470
    "vkGetDrmDisplayEXT", // 471
    "vkGetDynamicRenderingTilePropertiesQCOM", // 472
    "vkGetEncodedVideoSessionParametersKHR", // 473
    "vkGetEventStatus", // 474
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    "vkGetExecutionGraphPipelineNodeIndexAMDX", // 475
#else
    NULL, // 475
#endif
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    "vkGetExecutionGraphPipelineScratchSizeAMDX", // 476
#else
    NULL, // 476
#endif
    "vkGetFenceFdKHR", // 477
    "vkGetFenceStatus", // 478
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    "vkGetFenceWin32HandleKHR", // 479
#else
    NULL, // 479
#endif
    "vkGetFramebufferTilePropertiesQCOM", // 480
    "vkGetGeneratedCommandsMemoryRequirementsNV", // 481
    "vkGetImageDrmFormatModifierPropertiesEXT", // 482
    "vkGetImageMemoryRequirements", // 483
    "vkGetImageMemoryRequirements2", // 484
    "vkGetImageMemoryRequirements2KHR", // 485
    "vkGetImageOpaqueCaptureDescriptorDataEXT", // 486
    "vkGetImageSparseMemoryRequirements", // 487
    "vkGetImageSparseMemoryRequirements2", // 488
    "vkGetImageSparseMemoryRequirements2KHR", // 489
    "vkGetImageSubresourceLayout", // 490
    "vkGetImageSubresourceLayout2EXT", // 491
    "vkGetImageSubresourceLayout2KHR", // 492
    "vkGetImageViewAddressNVX", // 493
    "vkGetImageViewHandleNVX", // 494
    "vkGetImageViewOpaqueCaptureDescriptorDataEXT", // 495
    "vkGetInstanceProcAddr", // 496
    "vkGetLatencyTimingsNV", // 497
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    "vkGetMemoryAndroidHardwareBufferANDROID", // 498
#else
    NULL, // 498
#endif
    "vkGetMemoryFdKHR", // 499
    "vkGetMemoryFdPropertiesKHR", // 500
    "vkGetMemoryHostPointerPropertiesEXT", // 501
    "vkGetMemoryRemoteAddressNV", // 502
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    "vkGetMemoryWin32HandleKHR", // 503
#else
    NULL, // 503
#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    "vkGetMemoryWin32HandleNV", // 504
#else
    NULL, // 504
#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    "vkGetMemoryWin32HandlePropertiesKHR", // 505
#else
    NULL, // 505
#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
    "vkGetMemoryZirconHandleFUCHSIA", // 506
#else
    NULL, // 506
#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
    "vkGetMemoryZirconHandlePropertiesFUCHSIA", // 507
#else
    NULL, // 507
#endif
    "vkGetMicromapBuildSizesEXT", // 508
    "vkGetPastPresentationTimingGOOGLE", // 509
    "vkGetPerformanceParameterINTEL", // 510
    "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT", // 511
    "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR", // 512
    "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR", // 513
    "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV", // 514
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    "vkGetPhysicalDeviceDirectFBPresentationSupportEXT", // 515
#else
    NULL, // 515
#endif
    "vkGetPhysicalDeviceDisplayPlaneProperties2KHR", // 516
    "vkGetPhysicalDeviceDisplayPlanePropertiesKHR", // 517
    "vkGetPhysicalDeviceDisplayProperties2KHR", // 518
    "vkGetPhysicalDeviceDisplayPropertiesKHR", // 519
    "vkGetPhysicalDeviceExternalBufferProperties", // 520
    "vkGetPhysicalDeviceExternalBufferPropertiesKHR", // 521
    "vkGetPhysicalDeviceExternalFenceProperties", // 522
    "vkGetPhysicalDeviceExternalFencePropertiesKHR", // 523
    "vkGetPhysicalDeviceExternalImageFormatPropertiesNV", // 524
    "vkGetPhysicalDeviceExternalSemaphoreProperties", // 525
    "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR", // 526
    "vkGetPhysicalDeviceFeatures", // 527
    "vkGetPhysicalDeviceFeatures2", // 528
    "vkGetPhysicalDeviceFeatures2KHR", // 529
    "vkGetPhysicalDeviceFormatProperties", // 530
    "vkGetPhysicalDeviceFormatProperties2", // 531
    "vkGetPhysicalDeviceFormatProperties2KHR", // 532
    "vkGetPhysicalDeviceFragmentShadingRatesKHR", // 533
    "vkGetPhysicalDeviceImageFormatProperties", // 534
    "vkGetPhysicalDeviceImageFormatProperties2", // 535
    "vkGetPhysicalDeviceImageFormatProperties2KHR", // 536
    "vkGetPhysicalDeviceMemoryProperties", // 537
    "vkGetPhysicalDeviceMemoryProperties2", // 538
    "vkGetPhysicalDeviceMemoryProperties2KHR", // 539
    "vkGetPhysicalDeviceMultisamplePropertiesEXT", // 540
    "vkGetPhysicalDeviceOpticalFlowImageFormatsNV", // 541
    "vkGetPhysicalDevicePresentRectanglesKHR", // 542
    "vkGetPhysicalDeviceProperties", // 543
    "vkGetPhysicalDeviceProperties2", // 544
    "vkGetPhysicalDeviceProperties2KHR", // 545
    "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR", // 546
    "vkGetPhysicalDeviceQueueFamilyProperties", // 547
    "vkGetPhysicalDeviceQueueFamilyProperties2", // 548
    "vkGetPhysicalDeviceQueueFamilyProperties2KHR", // 549
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    "vkGetPhysicalDeviceScreenPresentationSupportQNX", // 550
#else
    NULL, // 550
#endif
    "vkGetPhysicalDeviceSparseImageFormatProperties", // 551
    "vkGetPhysicalDeviceSparseImageFormatProperties2", // 552
    "vkGetPhysicalDeviceSparseImageFormatProperties2KHR", // 553
    "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV", // 554
    "vkGetPhysicalDeviceSurfaceCapabilities2EXT", // 555
    "vkGetPhysicalDeviceSurfaceCapabilities2KHR", // 556
    "vkGetPhysicalDeviceSurfaceCapabilitiesKHR", // 557
    "vkGetPhysicalDeviceSurfaceFormats2KHR", // 558
    "vkGetPhysicalDeviceSurfaceFormatsKHR", // 559
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    "vkGetPhysicalDeviceSurfacePresentModes2EXT", // 560
#else
    NULL, // 560
#endif
    "vkGetPhysicalDeviceSurfacePresentModesKHR", // 561
    "vkGetPhysicalDeviceSurfaceSupportKHR", // 562
    "vkGetPhysicalDeviceToolProperties", // 563
    "vkGetPhysicalDeviceToolPropertiesEXT", // 564
    "vkGetPhysicalDeviceVideoCapabilitiesKHR", // 565
    "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR", // 566
    "vkGetPhysicalDeviceVideoFormatPropertiesKHR", // 567
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    "vkGetPhysicalDeviceWaylandPresentationSupportKHR", // 568
#else
    NULL, // 568
#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    "vkGetPhysicalDeviceWin32PresentationSupportKHR", // 569
#else
    NULL, // 569
#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
    "vkGetPhysicalDeviceXcbPresentationSupportKHR", // 570
#else
    NULL, // 570
#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    "vkGetPhysicalDeviceXlibPresentationSupportKHR", // 571
#else
    NULL, // 571
#endif
    "vkGetPipelineCacheData", // 572
    "vkGetPipelineExecutableInternalRepresentationsKHR", // 573
    "vkGetPipelineExecutablePropertiesKHR", // 574
    "vkGetPipelineExecutableStatisticsKHR", // 575
    "vkGetPipelineIndirectDeviceAddressNV", // 576
    "vkGetPipelineIndirectMemoryRequirementsNV", // 577
    "vkGetPipelinePropertiesEXT", // 578
    "vkGetPrivateData", // 579
    "vkGetPrivateDataEXT", // 580
    "vkGetQueryPoolResults", // 581
    "vkGetQueueCheckpointData2NV", // 582
    "vkGetQueueCheckpointDataNV", // 583
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    "vkGetRandROutputDisplayEXT", // 584
#else
    NULL, // 584
#endif
    "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR", // 585
    "vkGetRayTracingShaderGroupHandlesKHR", // 586
    "vkGetRayTracingShaderGroupHandlesNV", // 587
    "vkGetRayTracingShaderGroupStackSizeKHR", // 588
    "vkGetRefreshCycleDurationGOOGLE", // 589
    "vkGetRenderAreaGranularity", // 590
    "vkGetRenderingAreaGranularityKHR", // 591
    "vkGetSamplerOpaqueCaptureDescriptorDataEXT", // 592
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    "vkGetScreenBufferPropertiesQNX", // 593
#else
    NULL, // 593
#endif
    "vkGetSemaphoreCounterValue", // 594
    "vkGetSemaphoreCounterValueKHR", // 595
    "vkGetSemaphoreFdKHR", // 596
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    "vkGetSemaphoreWin32HandleKHR", // 597
#else
    NULL, // 597
#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
    "vkGetSemaphoreZirconHandleFUCHSIA", // 598
#else
    NULL, // 598
#endif
    "vkGetShaderBinaryDataEXT", // 599
    "vkGetShaderInfoAMD", // 600
    "vkGetShaderModuleCreateInfoIdentifierEXT", // 601
    "vkGetShaderModuleIdentifierEXT", // 602
    "vkGetSwapchainCounterEXT", // 603
    "vkGetSwapchainImagesKHR", // 604
    "vkGetSwapchainStatusKHR", // 605
    "vkGetValidationCacheDataEXT", // 606
    "vkGetVideoSessionMemoryRequirementsKHR", // 607
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    "vkGetWinrtDisplayNV", // 608
#else
    NULL, // 608
#endif
    "vkImportFenceFdKHR", // 609
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    "vkImportFenceWin32HandleKHR", // 610
#else
    NULL, // 610
#endif
    "vkImportSemaphoreFdKHR", // 611
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    "vkImportSemaphoreWin32HandleKHR", // 612
#else
    NULL, // 612
#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
    "vkImportSemaphoreZirconHandleFUCHSIA", // 613
#else
    NULL, // 613
#endif
    "vkInitializePerformanceApiINTEL", // 614
    "vkInvalidateMappedMemoryRanges", // 615
    "vkLatencySleepNV", // 616
    "vkMapMemory", // 617
    "vkMapMemory2KHR", // 618
    "vkMergePipelineCaches", // 619
    "vkMergeValidationCachesEXT", // 620
    "vkQueueBeginDebugUtilsLabelEXT", // 621
    "vkQueueBindSparse", // 622
    "vkQueueEndDebugUtilsLabelEXT", // 623
    "vkQueueInsertDebugUtilsLabelEXT", // 624
    "vkQueueNotifyOutOfBandNV", // 625
    "vkQueuePresentKHR", // 626
    "vkQueueSetPerformanceConfigurationINTEL", // 627
    "vkQueueSubmit", // 628
    "vkQueueSubmit2", // 629
    "vkQueueSubmit2KHR", // 630
    "vkQueueWaitIdle", // 631
    "vkRegisterDeviceEventEXT", // 632
    "vkRegisterDisplayEventEXT", // 633
    "vkReleaseDisplayEXT", // 634
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    "vkReleaseFullScreenExclusiveModeEXT", // 635
#else
    NULL, // 635
#endif
    "vkReleasePerformanceConfigurationINTEL", // 636
    "vkReleaseProfilingLockKHR", // 637
    "vkReleaseSwapchainImagesEXT", // 638
    "vkResetCommandBuffer", // 639
    "vkResetCommandPool", // 640
    "vkResetDescriptorPool", // 641
    "vkResetEvent", // 642
    "vkResetFences", // 643
    "vkResetQueryPool", // 644
    "vkResetQueryPoolEXT", // 645
#if defined(VK_USE_PLATFORM_FUCHSIA)
    "vkSetBufferCollectionBufferConstraintsFUCHSIA", // 646
#else
    NULL, // 646
#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
    "vkSetBufferCollectionImageConstraintsFUCHSIA", // 647
#else
    NULL, // 647
#endif
    "vkSetDebugUtilsObjectNameEXT", // 648
    "vkSetDebugUtilsObjectTagEXT", // 649
    "vkSetDeviceMemoryPriorityEXT", // 650
    "vkSetEvent", // 651
    "vkSetHdrMetadataEXT", // 652
    "vkSetLatencyMarkerNV", // 653
    "vkSetLatencySleepModeNV", // 654
    "vkSetLocalDimmingAMD", // 655
    "vkSetPrivateData", // 656
    "vkSetPrivateDataEXT", // 657
    "vkSignalSemaphore", // 658
    "vkSignalSemaphoreKHR", // 659
    "vkSubmitDebugUtilsMessageEXT", // 660
    "vkTransitionImageLayoutEXT", // 661
    "vkTrimCommandPool", // 662
    "vkTrimCommandPoolKHR", // 663
    "vkUninitializePerformanceApiINTEL", // 664
    "vkUnmapMemory", // 665
    "vkUnmapMemory2KHR", // 666
    "vkUpdateDescriptorSetWithTemplate", // 667
    "vkUpdateDescriptorSetWithTemplateKHR", // 668
    "vkUpdateDescriptorSets", // 669
    "vkUpdateVideoSessionParametersKHR", // 670
    "vkWaitForFences", // 671
    "vkWaitForPresentKHR", // 672
    "vkWaitSemaphores", // 673
    "vkWaitSemaphoresKHR", // 674
    "vkWriteAccelerationStructuresPropertiesKHR", // 675
    "vkWriteMicromapsPropertiesEXT" // 676
};

static const char *glad_ext_names[] = {
    "VK_AMDX_shader_enqueue", // 0
    "VK_AMD_buffer_marker", // 1
    "VK_AMD_device_coherent_memory", // 2
    "VK_AMD_display_native_hdr", // 3
    "VK_AMD_draw_indirect_count", // 4
    "VK_AMD_gcn_shader", // 5
    "VK_AMD_gpu_shader_half_float", // 6
    "VK_AMD_gpu_shader_int16", // 7
    "VK_AMD_memory_overallocation_behavior", // 8
    "VK_AMD_mixed_attachment_samples", // 9
    "VK_AMD_negative_viewport_height", // 10
    "VK_AMD_pipeline_compiler_control", // 11
    "VK_AMD_rasterization_order", // 12
    "VK_AMD_shader_ballot", // 13
    "VK_AMD_shader_core_properties", // 14
    "VK_AMD_shader_core_properties2", // 15
    "VK_AMD_shader_early_and_late_fragment_tests", // 16
    "VK_AMD_shader_explicit_vertex_parameter", // 17
    "VK_AMD_shader_fragment_mask", // 18
    "VK_AMD_shader_image_load_store_lod", // 19
    "VK_AMD_shader_info", // 20
    "VK_AMD_shader_trinary_minmax", // 21
    "VK_AMD_texture_gather_bias_lod", // 22
    "VK_ANDROID_external_format_resolve", // 23
    "VK_ANDROID_external_memory_android_hardware_buffer", // 24
    "VK_ARM_rasterization_order_attachment_access", // 25
    "VK_ARM_render_pass_striped", // 26
    "VK_ARM_scheduling_controls", // 27
    "VK_ARM_shader_core_builtins", // 28
    "VK_ARM_shader_core_properties", // 29
    "VK_EXT_4444_formats", // 30
    "VK_EXT_acquire_drm_display", // 31
    "VK_EXT_acquire_xlib_display", // 32
    "VK_EXT_astc_decode_mode", // 33
    "VK_EXT_attachment_feedback_loop_dynamic_state", // 34
    "VK_EXT_attachment_feedback_loop_layout", // 35
    "VK_EXT_blend_operation_advanced", // 36
    "VK_EXT_border_color_swizzle", // 37
    "VK_EXT_buffer_device_address", // 38
    "VK_EXT_calibrated_timestamps", // 39
    "VK_EXT_color_write_enable", // 40
    "VK_EXT_conditional_rendering", // 41
    "VK_EXT_conservative_rasterization", // 42
    "VK_EXT_custom_border_color", // 43
    "VK_EXT_debug_marker", // 44
    "VK_EXT_debug_report", // 45
    "VK_EXT_debug_utils", // 46
    "VK_EXT_depth_bias_control", // 47
    "VK_EXT_depth_clamp_zero_one", // 48
    "VK_EXT_depth_clip_control", // 49
    "VK_EXT_depth_clip_enable", // 50
    "VK_EXT_depth_range_unrestricted", // 51
    "VK_EXT_descriptor_buffer", // 52
    "VK_EXT_descriptor_indexing", // 53
    "VK_EXT_device_address_binding_report", // 54
    "VK_EXT_device_fault", // 55
    "VK_EXT_device_memory_report", // 56
    "VK_EXT_direct_mode_display", // 57
    "VK_EXT_directfb_surface", // 58
    "VK_EXT_discard_rectangles", // 59
    "VK_EXT_display_control", // 60
    "VK_EXT_display_surface_counter", // 61
    "VK_EXT_dynamic_rendering_unused_attachments", // 62
    "VK_EXT_extended_dynamic_state", // 63
    "VK_EXT_extended_dynamic_state2", // 64
    "VK_EXT_extended_dynamic_state3", // 65
    "VK_EXT_external_memory_acquire_unmodified", // 66
    "VK_EXT_external_memory_dma_buf", // 67
    "VK_EXT_external_memory_host", // 68
    "VK_EXT_filter_cubic", // 69
    "VK_EXT_fragment_density_map", // 70
    "VK_EXT_fragment_density_map2", // 71
    "VK_EXT_fragment_shader_interlock", // 72
    "VK_EXT_frame_boundary", // 73
    "VK_EXT_full_screen_exclusive", // 74
    "VK_EXT_global_priority", // 75
    "VK_EXT_global_priority_query", // 76
    "VK_EXT_graphics_pipeline_library", // 77
    "VK_EXT_hdr_metadata", // 78
    "VK_EXT_headless_surface", // 79
    "VK_EXT_host_image_copy", // 80
    "VK_EXT_host_query_reset", // 81
    "VK_EXT_image_2d_view_of_3d", // 82
    "VK_EXT_image_compression_control", // 83
    "VK_EXT_image_compression_control_swapchain", // 84
    "VK_EXT_image_drm_format_modifier", // 85
    "VK_EXT_image_robustness", // 86
    "VK_EXT_image_sliced_view_of_3d", // 87
    "VK_EXT_image_view_min_lod", // 88
    "VK_EXT_index_type_uint8", // 89
    "VK_EXT_inline_uniform_block", // 90
    "VK_EXT_layer_settings", // 91
    "VK_EXT_legacy_dithering", // 92
    "VK_EXT_line_rasterization", // 93
    "VK_EXT_load_store_op_none", // 94
    "VK_EXT_memory_budget", // 95
    "VK_EXT_memory_priority", // 96
    "VK_EXT_mesh_shader", // 97
    "VK_EXT_metal_objects", // 98
    "VK_EXT_metal_surface", // 99
    "VK_EXT_multi_draw", // 100
    "VK_EXT_multisampled_render_to_single_sampled", // 101
    "VK_EXT_mutable_descriptor_type", // 102
    "VK_EXT_nested_command_buffer", // 103
    "VK_EXT_non_seamless_cube_map", // 104
    "VK_EXT_opacity_micromap", // 105
    "VK_EXT_pageable_device_local_memory", // 106
    "VK_EXT_pci_bus_info", // 107
    "VK_EXT_physical_device_drm", // 108
    "VK_EXT_pipeline_creation_cache_control", // 109
    "VK_EXT_pipeline_creation_feedback", // 110
    "VK_EXT_pipeline_library_group_handles", // 111
    "VK_EXT_pipeline_properties", // 112
    "VK_EXT_pipeline_protected_access", // 113
    "VK_EXT_pipeline_robustness", // 114
    "VK_EXT_post_depth_coverage", // 115
    "VK_EXT_primitive_topology_list_restart", // 116
    "VK_EXT_primitives_generated_query", // 117
    "VK_EXT_private_data", // 118
    "VK_EXT_provoking_vertex", // 119
    "VK_EXT_queue_family_foreign", // 120
    "VK_EXT_rasterization_order_attachment_access", // 121
    "VK_EXT_rgba10x6_formats", // 122
    "VK_EXT_robustness2", // 123
    "VK_EXT_sample_locations", // 124
    "VK_EXT_sampler_filter_minmax", // 125
    "VK_EXT_scalar_block_layout", // 126
    "VK_EXT_separate_stencil_usage", // 127
    "VK_EXT_shader_atomic_float", // 128
    "VK_EXT_shader_atomic_float2", // 129
    "VK_EXT_shader_demote_to_helper_invocation", // 130
    "VK_EXT_shader_image_atomic_int64", // 131
    "VK_EXT_shader_module_identifier", // 132
    "VK_EXT_shader_object", // 133
    "VK_EXT_shader_stencil_export", // 134
    "VK_EXT_shader_subgroup_ballot", // 135
    "VK_EXT_shader_subgroup_vote", // 136
    "VK_EXT_shader_tile_image", // 137
    "VK_EXT_shader_viewport_index_layer", // 138
    "VK_EXT_subgroup_size_control", // 139
    "VK_EXT_subpass_merge_feedback", // 140
    "VK_EXT_surface_maintenance1", // 141
    "VK_EXT_swapchain_colorspace", // 142
    "VK_EXT_swapchain_maintenance1", // 143
    "VK_EXT_texel_buffer_alignment", // 144
    "VK_EXT_texture_compression_astc_hdr", // 145
    "VK_EXT_tooling_info", // 146
    "VK_EXT_transform_feedback", // 147
    "VK_EXT_validation_cache", // 148
    "VK_EXT_validation_features", // 149
    "VK_EXT_validation_flags", // 150
    "VK_EXT_vertex_attribute_divisor", // 151
    "VK_EXT_vertex_input_dynamic_state", // 152
    "VK_EXT_ycbcr_2plane_444_formats", // 153
    "VK_EXT_ycbcr_image_arrays", // 154
    "VK_FUCHSIA_buffer_collection", // 155
    "VK_FUCHSIA_external_memory", // 156
    "VK_FUCHSIA_external_semaphore", // 157
    "VK_FUCHSIA_imagepipe_surface", // 158
    "VK_GGP_frame_token", // 159
    "VK_GGP_stream_descriptor_surface", // 160
    "VK_GOOGLE_decorate_string", // 161
    "VK_GOOGLE_display_timing", // 162
    "VK_GOOGLE_hlsl_functionality1", // 163
    "VK_GOOGLE_surfaceless_query", // 164
    "VK_GOOGLE_user_type", // 165
    "VK_HUAWEI_cluster_culling_shader", // 166
    "VK_HUAWEI_invocation_mask", // 167
    "VK_HUAWEI_subpass_shading", // 168
    "VK_IMG_filter_cubic", // 169
    "VK_IMG_format_pvrtc", // 170
    "VK_IMG_relaxed_line_rasterization", // 171
    "VK_INTEL_performance_query", // 172
    "VK_INTEL_shader_integer_functions2", // 173
    "VK_KHR_16bit_storage", // 174
    "VK_KHR_8bit_storage", // 175
    "VK_KHR_acceleration_structure", // 176
    "VK_KHR_android_surface", // 177
    "VK_KHR_bind_memory2", // 178
    "VK_KHR_buffer_device_address", // 179
    "VK_KHR_calibrated_timestamps", // 180
    "VK_KHR_cooperative_matrix", // 181
    "VK_KHR_copy_commands2", // 182
    "VK_KHR_create_renderpass2", // 183
    "VK_KHR_dedicated_allocation", // 184
    "VK_KHR_deferred_host_operations", // 185
    "VK_KHR_depth_stencil_resolve", // 186
    "VK_KHR_descriptor_update_template", // 187
    "VK_KHR_device_group", // 188
    "VK_KHR_device_group_creation", // 189
    "VK_KHR_display", // 190
    "VK_KHR_display_swapchain", // 191
    "VK_KHR_draw_indirect_count", // 192
    "VK_KHR_driver_properties", // 193
    "VK_KHR_dynamic_rendering", // 194
    "VK_KHR_external_fence", // 195
    "VK_KHR_external_fence_capabilities", // 196
    "VK_KHR_external_fence_fd", // 197
    "VK_KHR_external_fence_win32", // 198
    "VK_KHR_external_memory", // 199
    "VK_KHR_external_memory_capabilities", // 200
    "VK_KHR_external_memory_fd", // 201
    "VK_KHR_external_memory_win32", // 202
    "VK_KHR_external_semaphore", // 203
    "VK_KHR_external_semaphore_capabilities", // 204
    "VK_KHR_external_semaphore_fd", // 205
    "VK_KHR_external_semaphore_win32", // 206
    "VK_KHR_format_feature_flags2", // 207
    "VK_KHR_fragment_shader_barycentric", // 208
    "VK_KHR_fragment_shading_rate", // 209
    "VK_KHR_get_display_properties2", // 210
    "VK_KHR_get_memory_requirements2", // 211
    "VK_KHR_get_physical_device_properties2", // 212
    "VK_KHR_get_surface_capabilities2", // 213
    "VK_KHR_global_priority", // 214
    "VK_KHR_image_format_list", // 215
    "VK_KHR_imageless_framebuffer", // 216
    "VK_KHR_incremental_present", // 217
    "VK_KHR_maintenance1", // 218
    "VK_KHR_maintenance2", // 219
    "VK_KHR_maintenance3", // 220
    "VK_KHR_maintenance4", // 221
    "VK_KHR_maintenance5", // 222
    "VK_KHR_maintenance6", // 223
    "VK_KHR_map_memory2", // 224
    "VK_KHR_multiview", // 225
    "VK_KHR_performance_query", // 226
    "VK_KHR_pipeline_executable_properties", // 227
    "VK_KHR_pipeline_library", // 228
    "VK_KHR_portability_enumeration", // 229
    "VK_KHR_portability_subset", // 230
    "VK_KHR_present_id", // 231
    "VK_KHR_present_wait", // 232
    "VK_KHR_push_descriptor", // 233
    "VK_KHR_ray_query", // 234
    "VK_KHR_ray_tracing_maintenance1", // 235
    "VK_KHR_ray_tracing_pipeline", // 236
    "VK_KHR_ray_tracing_position_fetch", // 237
    "VK_KHR_relaxed_block_layout", // 238
    "VK_KHR_sampler_mirror_clamp_to_edge", // 239
    "VK_KHR_sampler_ycbcr_conversion", // 240
    "VK_KHR_separate_depth_stencil_layouts", // 241
    "VK_KHR_shader_atomic_int64", // 242
    "VK_KHR_shader_clock", // 243
    "VK_KHR_shader_draw_parameters", // 244
    "VK_KHR_shader_float16_int8", // 245
    "VK_KHR_shader_float_controls", // 246
    "VK_KHR_shader_integer_dot_product", // 247
    "VK_KHR_shader_non_semantic_info", // 248
    "VK_KHR_shader_subgroup_extended_types", // 249
    "VK_KHR_shader_subgroup_uniform_control_flow", // 250
    "VK_KHR_shader_terminate_invocation", // 251
    "VK_KHR_shared_presentable_image", // 252
    "VK_KHR_spirv_1_4", // 253
    "VK_KHR_storage_buffer_storage_class", // 254
    "VK_KHR_surface", // 255
    "VK_KHR_surface_protected_capabilities", // 256
    "VK_KHR_swapchain", // 257
    "VK_KHR_swapchain_mutable_format", // 258
    "VK_KHR_synchronization2", // 259
    "VK_KHR_timeline_semaphore", // 260
    "VK_KHR_uniform_buffer_standard_layout", // 261
    "VK_KHR_variable_pointers", // 262
    "VK_KHR_vertex_attribute_divisor", // 263
    "VK_KHR_video_decode_h264", // 264
    "VK_KHR_video_decode_h265", // 265
    "VK_KHR_video_decode_queue", // 266
    "VK_KHR_video_encode_h264", // 267
    "VK_KHR_video_encode_h265", // 268
    "VK_KHR_video_encode_queue", // 269
    "VK_KHR_video_maintenance1", // 270
    "VK_KHR_video_queue", // 271
    "VK_KHR_vulkan_memory_model", // 272
    "VK_KHR_wayland_surface", // 273
    "VK_KHR_win32_keyed_mutex", // 274
    "VK_KHR_win32_surface", // 275
    "VK_KHR_workgroup_memory_explicit_layout", // 276
    "VK_KHR_xcb_surface", // 277
    "VK_KHR_xlib_surface", // 278
    "VK_KHR_zero_initialize_workgroup_memory", // 279
    "VK_LUNARG_direct_driver_loading", // 280
    "VK_MSFT_layered_driver", // 281
    "VK_MVK_ios_surface", // 282
    "VK_MVK_macos_surface", // 283
    "VK_NN_vi_surface", // 284
    "VK_NVX_binary_import", // 285
    "VK_NVX_image_view_handle", // 286
    "VK_NVX_multiview_per_view_attributes", // 287
    "VK_NV_acquire_winrt_display", // 288
    "VK_NV_clip_space_w_scaling", // 289
    "VK_NV_compute_shader_derivatives", // 290
    "VK_NV_cooperative_matrix", // 291
    "VK_NV_copy_memory_indirect", // 292
    "VK_NV_corner_sampled_image", // 293
    "VK_NV_coverage_reduction_mode", // 294
    "VK_NV_cuda_kernel_launch", // 295
    "VK_NV_dedicated_allocation", // 296
    "VK_NV_dedicated_allocation_image_aliasing", // 297
    "VK_NV_descriptor_pool_overallocation", // 298
    "VK_NV_device_diagnostic_checkpoints", // 299
    "VK_NV_device_diagnostics_config", // 300
    "VK_NV_device_generated_commands", // 301
    "VK_NV_device_generated_commands_compute", // 302
    "VK_NV_displacement_micromap", // 303
    "VK_NV_extended_sparse_address_space", // 304
    "VK_NV_external_memory", // 305
    "VK_NV_external_memory_capabilities", // 306
    "VK_NV_external_memory_rdma", // 307
    "VK_NV_external_memory_win32", // 308
    "VK_NV_fill_rectangle", // 309
    "VK_NV_fragment_coverage_to_color", // 310
    "VK_NV_fragment_shader_barycentric", // 311
    "VK_NV_fragment_shading_rate_enums", // 312
    "VK_NV_framebuffer_mixed_samples", // 313
    "VK_NV_geometry_shader_passthrough", // 314
    "VK_NV_glsl_shader", // 315
    "VK_NV_inherited_viewport_scissor", // 316
    "VK_NV_linear_color_attachment", // 317
    "VK_NV_low_latency", // 318
    "VK_NV_low_latency2", // 319
    "VK_NV_memory_decompression", // 320
    "VK_NV_mesh_shader", // 321
    "VK_NV_optical_flow", // 322
    "VK_NV_per_stage_descriptor_set", // 323
    "VK_NV_present_barrier", // 324
    "VK_NV_ray_tracing", // 325
    "VK_NV_ray_tracing_invocation_reorder", // 326
    "VK_NV_ray_tracing_motion_blur", // 327
    "VK_NV_representative_fragment_test", // 328
    "VK_NV_sample_mask_override_coverage", // 329
    "VK_NV_scissor_exclusive", // 330
    "VK_NV_shader_image_footprint", // 331
    "VK_NV_shader_sm_builtins", // 332
    "VK_NV_shader_subgroup_partitioned", // 333
    "VK_NV_shading_rate_image", // 334
    "VK_NV_viewport_array2", // 335
    "VK_NV_viewport_swizzle", // 336
    "VK_NV_win32_keyed_mutex", // 337
    "VK_QCOM_filter_cubic_clamp", // 338
    "VK_QCOM_filter_cubic_weights", // 339
    "VK_QCOM_fragment_density_map_offset", // 340
    "VK_QCOM_image_processing", // 341
    "VK_QCOM_image_processing2", // 342
    "VK_QCOM_multiview_per_view_render_areas", // 343
    "VK_QCOM_multiview_per_view_viewports", // 344
    "VK_QCOM_render_pass_shader_resolve", // 345
    "VK_QCOM_render_pass_store_ops", // 346
    "VK_QCOM_render_pass_transform", // 347
    "VK_QCOM_rotated_copy_commands", // 348
    "VK_QCOM_tile_properties", // 349
    "VK_QCOM_ycbcr_degamma", // 350
    "VK_QNX_external_memory_screen_buffer", // 351
    "VK_QNX_screen_surface", // 352
    "VK_SEC_amigo_profiling", // 353
    "VK_VALVE_descriptor_set_host_mapping", // 354
    "VK_VALVE_mutable_descriptor_type" // 355
};

#ifdef __cplusplus
GladVulkanContext glad_vulkan_context = {};
#else
GladVulkanContext glad_vulkan_context = { 0 };
#endif

static void glad_vk_load_VK_VERSION_1_0(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_0) return;
    static const uint16_t s_pfnIdx[] = {
            8, // vkAllocateCommandBuffers
            9, // vkAllocateDescriptorSets
           10, // vkAllocateMemory
           11, // vkBeginCommandBuffer
           13, // vkBindBufferMemory
           16, // vkBindImageMemory
           25, // vkCmdBeginQuery
           27, // vkCmdBeginRenderPass
           37, // vkCmdBindDescriptorSets
           39, // vkCmdBindIndexBuffer
           42, // vkCmdBindPipeline
           47, // vkCmdBindVertexBuffers
           50, // vkCmdBlitImage
           57, // vkCmdClearAttachments
           58, // vkCmdClearColorImage
           59, // vkCmdClearDepthStencilImage
           64, // vkCmdCopyBuffer
           67, // vkCmdCopyBufferToImage
           70, // vkCmdCopyImage
           73, // vkCmdCopyImageToBuffer
           82, // vkCmdCopyQueryPoolResults
           91, // vkCmdDispatch
           97, // vkCmdDispatchIndirect
           98, // vkCmdDraw
          101, // vkCmdDrawIndexed
          102, // vkCmdDrawIndexedIndirect
          106, // vkCmdDrawIndirect
          122, // vkCmdEndQuery
          124, // vkCmdEndRenderPass
          131, // vkCmdExecuteCommands
          133, // vkCmdFillBuffer
          136, // vkCmdNextSubpass
          140, // vkCmdPipelineBarrier
          144, // vkCmdPushConstants
          150, // vkCmdResetEvent
          153, // vkCmdResetQueryPool
          154, // vkCmdResolveImage
          160, // vkCmdSetBlendConstants
          177, // vkCmdSetDepthBias
          181, // vkCmdSetDepthBounds
          200, // vkCmdSetEvent
          213, // vkCmdSetLineWidth
          235, // vkCmdSetScissor
          239, // vkCmdSetStencilCompareMask
          242, // vkCmdSetStencilReference
          245, // vkCmdSetStencilWriteMask
          248, // vkCmdSetViewport
          260, // vkCmdUpdateBuffer
          262, // vkCmdWaitEvents
          270, // vkCmdWriteTimestamp
          286, // vkCreateBuffer
          288, // vkCreateBufferView
          289, // vkCreateCommandPool
          290, // vkCreateComputePipelines
          298, // vkCreateDescriptorPool
          299, // vkCreateDescriptorSetLayout
          302, // vkCreateDevice
          306, // vkCreateEvent
          308, // vkCreateFence
          309, // vkCreateFramebuffer
          310, // vkCreateGraphicsPipelines
          313, // vkCreateImage
          315, // vkCreateImageView
          317, // vkCreateInstance
          322, // vkCreatePipelineCache
          323, // vkCreatePipelineLayout
          326, // vkCreateQueryPool
          329, // vkCreateRenderPass
          332, // vkCreateSampler
          336, // vkCreateSemaphore
          337, // vkCreateShaderModule
          356, // vkDestroyBuffer
          358, // vkDestroyBufferView
          359, // vkDestroyCommandPool
          367, // vkDestroyDescriptorPool
          368, // vkDestroyDescriptorSetLayout
          371, // vkDestroyDevice
          372, // vkDestroyEvent
          373, // vkDestroyFence
          374, // vkDestroyFramebuffer
          375, // vkDestroyImage
          376, // vkDestroyImageView
          378, // vkDestroyInstance
          381, // vkDestroyPipeline
          382, // vkDestroyPipelineCache
          383, // vkDestroyPipelineLayout
          386, // vkDestroyQueryPool
          387, // vkDestroyRenderPass
          388, // vkDestroySampler
          391, // vkDestroySemaphore
          393, // vkDestroyShaderModule
          399, // vkDeviceWaitIdle
          401, // vkEndCommandBuffer
          402, // vkEnumerateDeviceExtensionProperties
          403, // vkEnumerateDeviceLayerProperties
          404, // vkEnumerateInstanceExtensionProperties
          405, // vkEnumerateInstanceLayerProperties
          410, // vkEnumeratePhysicalDevices
          412, // vkFlushMappedMemoryRanges
          413, // vkFreeCommandBuffers
          414, // vkFreeDescriptorSets
          415, // vkFreeMemory
          426, // vkGetBufferMemoryRequirements
          458, // vkGetDeviceMemoryCommitment
          462, // vkGetDeviceProcAddr
          463, // vkGetDeviceQueue
          474, // vkGetEventStatus
          478, // vkGetFenceStatus
          483, // vkGetImageMemoryRequirements
          487, // vkGetImageSparseMemoryRequirements
          490, // vkGetImageSubresourceLayout
          496, // vkGetInstanceProcAddr
          527, // vkGetPhysicalDeviceFeatures
          530, // vkGetPhysicalDeviceFormatProperties
          534, // vkGetPhysicalDeviceImageFormatProperties
          537, // vkGetPhysicalDeviceMemoryProperties
          543, // vkGetPhysicalDeviceProperties
          547, // vkGetPhysicalDeviceQueueFamilyProperties
          551, // vkGetPhysicalDeviceSparseImageFormatProperties
          572, // vkGetPipelineCacheData
          581, // vkGetQueryPoolResults
          590, // vkGetRenderAreaGranularity
          615, // vkInvalidateMappedMemoryRanges
          617, // vkMapMemory
          619, // vkMergePipelineCaches
          622, // vkQueueBindSparse
          628, // vkQueueSubmit
          631, // vkQueueWaitIdle
          639, // vkResetCommandBuffer
          640, // vkResetCommandPool
          641, // vkResetDescriptorPool
          642, // vkResetEvent
          643, // vkResetFences
          651, // vkSetEvent
          665, // vkUnmapMemory
          669, // vkUpdateDescriptorSets
          671  // vkWaitForFences
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_VERSION_1_1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_1) return;
    static const uint16_t s_pfnIdx[] = {
           14, // vkBindBufferMemory2
           17, // vkBindImageMemory2
           92, // vkCmdDispatchBase
          195, // vkCmdSetDeviceMask
          300, // vkCreateDescriptorUpdateTemplate
          333, // vkCreateSamplerYcbcrConversion
          369, // vkDestroyDescriptorUpdateTemplate
          389, // vkDestroySamplerYcbcrConversion
          406, // vkEnumerateInstanceVersion
          407, // vkEnumeratePhysicalDeviceGroups
          427, // vkGetBufferMemoryRequirements2
          442, // vkGetDescriptorSetLayoutSupport
          448, // vkGetDeviceGroupPeerMemoryFeatures
          464, // vkGetDeviceQueue2
          484, // vkGetImageMemoryRequirements2
          488, // vkGetImageSparseMemoryRequirements2
          520, // vkGetPhysicalDeviceExternalBufferProperties
          522, // vkGetPhysicalDeviceExternalFenceProperties
          525, // vkGetPhysicalDeviceExternalSemaphoreProperties
          528, // vkGetPhysicalDeviceFeatures2
          531, // vkGetPhysicalDeviceFormatProperties2
          535, // vkGetPhysicalDeviceImageFormatProperties2
          538, // vkGetPhysicalDeviceMemoryProperties2
          544, // vkGetPhysicalDeviceProperties2
          548, // vkGetPhysicalDeviceQueueFamilyProperties2
          552, // vkGetPhysicalDeviceSparseImageFormatProperties2
          662, // vkTrimCommandPool
          667  // vkUpdateDescriptorSetWithTemplate
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_VERSION_1_2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_2) return;
    static const uint16_t s_pfnIdx[] = {
           28, // vkCmdBeginRenderPass2
          103, // vkCmdDrawIndexedIndirectCount
          108, // vkCmdDrawIndirectCount
          125, // vkCmdEndRenderPass2
          137, // vkCmdNextSubpass2
          330, // vkCreateRenderPass2
          423, // vkGetBufferDeviceAddress
          429, // vkGetBufferOpaqueCaptureAddress
          459, // vkGetDeviceMemoryOpaqueCaptureAddress
          594, // vkGetSemaphoreCounterValue
          644, // vkResetQueryPool
          658, // vkSignalSemaphore
          673  // vkWaitSemaphores
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_VERSION_1_3(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_3) return;
    static const uint16_t s_pfnIdx[] = {
           30, // vkCmdBeginRendering
           48, // vkCmdBindVertexBuffers2
           51, // vkCmdBlitImage2
           65, // vkCmdCopyBuffer2
           68, // vkCmdCopyBufferToImage2
           71, // vkCmdCopyImage2
           74, // vkCmdCopyImageToBuffer2
          127, // vkCmdEndRendering
          141, // vkCmdPipelineBarrier2
          151, // vkCmdResetEvent2
          155, // vkCmdResolveImage2
          175, // vkCmdSetCullMode
          179, // vkCmdSetDepthBiasEnable
          182, // vkCmdSetDepthBoundsTestEnable
          187, // vkCmdSetDepthCompareOp
          189, // vkCmdSetDepthTestEnable
          191, // vkCmdSetDepthWriteEnable
          201, // vkCmdSetEvent2
          208, // vkCmdSetFrontFace
          221, // vkCmdSetPrimitiveRestartEnable
          223, // vkCmdSetPrimitiveTopology
          228, // vkCmdSetRasterizerDiscardEnable
          236, // vkCmdSetScissorWithCount
          240, // vkCmdSetStencilOp
          243, // vkCmdSetStencilTestEnable
          253, // vkCmdSetViewportWithCount
          263, // vkCmdWaitEvents2
          271, // vkCmdWriteTimestamp2
          324, // vkCreatePrivateDataSlot
          384, // vkDestroyPrivateDataSlot
          445, // vkGetDeviceBufferMemoryRequirements
          453, // vkGetDeviceImageMemoryRequirements
          455, // vkGetDeviceImageSparseMemoryRequirements
          563, // vkGetPhysicalDeviceToolProperties
          579, // vkGetPrivateData
          629, // vkQueueSubmit2
          656  // vkSetPrivateData
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

#if defined(VK_ENABLE_BETA_EXTENSIONS)
static void glad_vk_load_VK_AMDX_shader_enqueue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMDX_shader_enqueue) return;
    static const uint16_t s_pfnIdx[] = {
           94, // vkCmdDispatchGraphAMDX
           95, // vkCmdDispatchGraphIndirectAMDX
           96, // vkCmdDispatchGraphIndirectCountAMDX
          134, // vkCmdInitializeGraphScratchMemoryAMDX
          307, // vkCreateExecutionGraphPipelinesAMDX
          475, // vkGetExecutionGraphPipelineNodeIndexAMDX
          476  // vkGetExecutionGraphPipelineScratchSizeAMDX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
static void glad_vk_load_VK_AMD_buffer_marker(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_buffer_marker) return;
    static const uint16_t s_pfnIdx[] = {
          268  // vkCmdWriteBufferMarkerAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_AMD_display_native_hdr(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_display_native_hdr) return;
    static const uint16_t s_pfnIdx[] = {
          655  // vkSetLocalDimmingAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_AMD_draw_indirect_count(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_draw_indirect_count) return;
    static const uint16_t s_pfnIdx[] = {
          104, // vkCmdDrawIndexedIndirectCountAMD
          109  // vkCmdDrawIndirectCountAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_AMD_shader_info(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_shader_info) return;
    static const uint16_t s_pfnIdx[] = {
          600  // vkGetShaderInfoAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
static void glad_vk_load_VK_ANDROID_external_memory_android_hardware_buffer(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANDROID_external_memory_android_hardware_buffer) return;
    static const uint16_t s_pfnIdx[] = {
          421, // vkGetAndroidHardwareBufferPropertiesANDROID
          498  // vkGetMemoryAndroidHardwareBufferANDROID
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
static void glad_vk_load_VK_EXT_acquire_drm_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_acquire_drm_display) return;
    static const uint16_t s_pfnIdx[] = {
            0, // vkAcquireDrmDisplayEXT
          471  // vkGetDrmDisplayEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
static void glad_vk_load_VK_EXT_acquire_xlib_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_acquire_xlib_display) return;
    static const uint16_t s_pfnIdx[] = {
            7, // vkAcquireXlibDisplayEXT
          584  // vkGetRandROutputDisplayEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
static void glad_vk_load_VK_EXT_attachment_feedback_loop_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_attachment_feedback_loop_dynamic_state) return;
    static const uint16_t s_pfnIdx[] = {
          159  // vkCmdSetAttachmentFeedbackLoopEnableEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_buffer_device_address(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_buffer_device_address) return;
    static const uint16_t s_pfnIdx[] = {
          424  // vkGetBufferDeviceAddressEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_calibrated_timestamps(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_calibrated_timestamps) return;
    static const uint16_t s_pfnIdx[] = {
          432, // vkGetCalibratedTimestampsEXT
          511  // vkGetPhysicalDeviceCalibrateableTimeDomainsEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_color_write_enable(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_color_write_enable) return;
    static const uint16_t s_pfnIdx[] = {
          166  // vkCmdSetColorWriteEnableEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_conditional_rendering(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_conditional_rendering) return;
    static const uint16_t s_pfnIdx[] = {
           23, // vkCmdBeginConditionalRenderingEXT
          120  // vkCmdEndConditionalRenderingEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_debug_marker(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_debug_marker) return;
    static const uint16_t s_pfnIdx[] = {
           85, // vkCmdDebugMarkerBeginEXT
           86, // vkCmdDebugMarkerEndEXT
           87, // vkCmdDebugMarkerInsertEXT
          350, // vkDebugMarkerSetObjectNameEXT
          351  // vkDebugMarkerSetObjectTagEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_debug_report(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_debug_report) return;
    static const uint16_t s_pfnIdx[] = {
          295, // vkCreateDebugReportCallbackEXT
          352, // vkDebugReportMessageEXT
          364  // vkDestroyDebugReportCallbackEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_debug_utils(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_debug_utils) return;
    static const uint16_t s_pfnIdx[] = {
           24, // vkCmdBeginDebugUtilsLabelEXT
          121, // vkCmdEndDebugUtilsLabelEXT
          135, // vkCmdInsertDebugUtilsLabelEXT
          296, // vkCreateDebugUtilsMessengerEXT
          365, // vkDestroyDebugUtilsMessengerEXT
          621, // vkQueueBeginDebugUtilsLabelEXT
          623, // vkQueueEndDebugUtilsLabelEXT
          624, // vkQueueInsertDebugUtilsLabelEXT
          648, // vkSetDebugUtilsObjectNameEXT
          649, // vkSetDebugUtilsObjectTagEXT
          660  // vkSubmitDebugUtilsMessageEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_depth_bias_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_depth_bias_control) return;
    static const uint16_t s_pfnIdx[] = {
          178  // vkCmdSetDepthBias2EXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_descriptor_buffer(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_descriptor_buffer) return;
    static const uint16_t s_pfnIdx[] = {
           35, // vkCmdBindDescriptorBufferEmbeddedSamplersEXT
           36, // vkCmdBindDescriptorBuffersEXT
          194, // vkCmdSetDescriptorBufferOffsetsEXT
          420, // vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT
          431, // vkGetBufferOpaqueCaptureDescriptorDataEXT
          437, // vkGetDescriptorEXT
          439, // vkGetDescriptorSetLayoutBindingOffsetEXT
          441, // vkGetDescriptorSetLayoutSizeEXT
          486, // vkGetImageOpaqueCaptureDescriptorDataEXT
          495, // vkGetImageViewOpaqueCaptureDescriptorDataEXT
          592  // vkGetSamplerOpaqueCaptureDescriptorDataEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_device_fault(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_device_fault) return;
    static const uint16_t s_pfnIdx[] = {
          447  // vkGetDeviceFaultInfoEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_direct_mode_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_direct_mode_display) return;
    static const uint16_t s_pfnIdx[] = {
          634  // vkReleaseDisplayEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
static void glad_vk_load_VK_EXT_directfb_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_directfb_surface) return;
    static const uint16_t s_pfnIdx[] = {
          303, // vkCreateDirectFBSurfaceEXT
          515  // vkGetPhysicalDeviceDirectFBPresentationSupportEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
static void glad_vk_load_VK_EXT_discard_rectangles(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_discard_rectangles) return;
    static const uint16_t s_pfnIdx[] = {
          197, // vkCmdSetDiscardRectangleEXT
          198, // vkCmdSetDiscardRectangleEnableEXT
          199  // vkCmdSetDiscardRectangleModeEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_display_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_display_control) return;
    static const uint16_t s_pfnIdx[] = {
          400, // vkDisplayPowerControlEXT
          603, // vkGetSwapchainCounterEXT
          632, // vkRegisterDeviceEventEXT
          633  // vkRegisterDisplayEventEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_display_surface_counter(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_display_surface_counter) return;
    static const uint16_t s_pfnIdx[] = {
          555  // vkGetPhysicalDeviceSurfaceCapabilities2EXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_extended_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_extended_dynamic_state) return;
    static const uint16_t s_pfnIdx[] = {
           49, // vkCmdBindVertexBuffers2EXT
          176, // vkCmdSetCullModeEXT
          183, // vkCmdSetDepthBoundsTestEnableEXT
          188, // vkCmdSetDepthCompareOpEXT
          190, // vkCmdSetDepthTestEnableEXT
          192, // vkCmdSetDepthWriteEnableEXT
          209, // vkCmdSetFrontFaceEXT
          224, // vkCmdSetPrimitiveTopologyEXT
          237, // vkCmdSetScissorWithCountEXT
          241, // vkCmdSetStencilOpEXT
          244, // vkCmdSetStencilTestEnableEXT
          254  // vkCmdSetViewportWithCountEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_extended_dynamic_state2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_extended_dynamic_state2) return;
    static const uint16_t s_pfnIdx[] = {
          180, // vkCmdSetDepthBiasEnableEXT
          214, // vkCmdSetLogicOpEXT
          216, // vkCmdSetPatchControlPointsEXT
          222, // vkCmdSetPrimitiveRestartEnableEXT
          229  // vkCmdSetRasterizerDiscardEnableEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_extended_dynamic_state3(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_extended_dynamic_state3) return;
    static const uint16_t s_pfnIdx[] = {
          157, // vkCmdSetAlphaToCoverageEnableEXT
          158, // vkCmdSetAlphaToOneEnableEXT
          163, // vkCmdSetColorBlendAdvancedEXT
          164, // vkCmdSetColorBlendEnableEXT
          165, // vkCmdSetColorBlendEquationEXT
          167, // vkCmdSetColorWriteMaskEXT
          168, // vkCmdSetConservativeRasterizationModeEXT
          169, // vkCmdSetCoverageModulationModeNV
          170, // vkCmdSetCoverageModulationTableEnableNV
          171, // vkCmdSetCoverageModulationTableNV
          172, // vkCmdSetCoverageReductionModeNV
          173, // vkCmdSetCoverageToColorEnableNV
          174, // vkCmdSetCoverageToColorLocationNV
          184, // vkCmdSetDepthClampEnableEXT
          185, // vkCmdSetDepthClipEnableEXT
          186, // vkCmdSetDepthClipNegativeOneToOneEXT
          205, // vkCmdSetExtraPrimitiveOverestimationSizeEXT
          210, // vkCmdSetLineRasterizationModeEXT
          212, // vkCmdSetLineStippleEnableEXT
          215, // vkCmdSetLogicOpEnableEXT
          220, // vkCmdSetPolygonModeEXT
          225, // vkCmdSetProvokingVertexModeEXT
          226, // vkCmdSetRasterizationSamplesEXT
          227, // vkCmdSetRasterizationStreamEXT
          231, // vkCmdSetRepresentativeFragmentTestEnableNV
          233, // vkCmdSetSampleLocationsEnableEXT
          234, // vkCmdSetSampleMaskEXT
          238, // vkCmdSetShadingRateImageEnableNV
          246, // vkCmdSetTessellationDomainOriginEXT
          250, // vkCmdSetViewportSwizzleNV
          251  // vkCmdSetViewportWScalingEnableNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_external_memory_host(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_external_memory_host) return;
    static const uint16_t s_pfnIdx[] = {
          501  // vkGetMemoryHostPointerPropertiesEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_EXT_full_screen_exclusive(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_full_screen_exclusive) return;
    static const uint16_t s_pfnIdx[] = {
            1, // vkAcquireFullScreenExclusiveModeEXT
          451, // vkGetDeviceGroupSurfacePresentModes2EXT
          560, // vkGetPhysicalDeviceSurfacePresentModes2EXT
          635  // vkReleaseFullScreenExclusiveModeEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
static void glad_vk_load_VK_EXT_hdr_metadata(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_hdr_metadata) return;
    static const uint16_t s_pfnIdx[] = {
          652  // vkSetHdrMetadataEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_headless_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_headless_surface) return;
    static const uint16_t s_pfnIdx[] = {
          311  // vkCreateHeadlessSurfaceEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_host_image_copy(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_host_image_copy) return;
    static const uint16_t s_pfnIdx[] = {
          276, // vkCopyImageToImageEXT
          277, // vkCopyImageToMemoryEXT
          279, // vkCopyMemoryToImageEXT
          491, // vkGetImageSubresourceLayout2EXT
          661  // vkTransitionImageLayoutEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_host_query_reset(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_host_query_reset) return;
    static const uint16_t s_pfnIdx[] = {
          645  // vkResetQueryPoolEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_image_compression_control(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_image_compression_control) return;
    static const uint16_t s_pfnIdx[] = {
          491  // vkGetImageSubresourceLayout2EXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_image_drm_format_modifier(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_image_drm_format_modifier) return;
    static const uint16_t s_pfnIdx[] = {
          482  // vkGetImageDrmFormatModifierPropertiesEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_line_rasterization(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_line_rasterization) return;
    static const uint16_t s_pfnIdx[] = {
          211  // vkCmdSetLineStippleEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_mesh_shader(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_mesh_shader) return;
    static const uint16_t s_pfnIdx[] = {
          111, // vkCmdDrawMeshTasksEXT
          112, // vkCmdDrawMeshTasksIndirectCountEXT
          114  // vkCmdDrawMeshTasksIndirectEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

#if defined(VK_USE_PLATFORM_METAL_EXT)
static void glad_vk_load_VK_EXT_metal_objects(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_metal_objects) return;
    static const uint16_t s_pfnIdx[] = {
          411  // vkExportMetalObjectsEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
#if defined(VK_USE_PLATFORM_METAL_EXT)
static void glad_vk_load_VK_EXT_metal_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_metal_surface) return;
    static const uint16_t s_pfnIdx[] = {
          319  // vkCreateMetalSurfaceEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
static void glad_vk_load_VK_EXT_multi_draw(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_multi_draw) return;
    static const uint16_t s_pfnIdx[] = {
          117, // vkCmdDrawMultiEXT
          118  // vkCmdDrawMultiIndexedEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_opacity_micromap(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_opacity_micromap) return;
    static const uint16_t s_pfnIdx[] = {
           22, // vkBuildMicromapsEXT
           56, // vkCmdBuildMicromapsEXT
           79, // vkCmdCopyMemoryToMicromapEXT
           80, // vkCmdCopyMicromapEXT
           81, // vkCmdCopyMicromapToMemoryEXT
          269, // vkCmdWriteMicromapsPropertiesEXT
          280, // vkCopyMemoryToMicromapEXT
          281, // vkCopyMicromapEXT
          282, // vkCopyMicromapToMemoryEXT
          320, // vkCreateMicromapEXT
          379, // vkDestroyMicromapEXT
          461, // vkGetDeviceMicromapCompatibilityEXT
          508, // vkGetMicromapBuildSizesEXT
          676  // vkWriteMicromapsPropertiesEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_pageable_device_local_memory(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_pageable_device_local_memory) return;
    static const uint16_t s_pfnIdx[] = {
          650  // vkSetDeviceMemoryPriorityEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_pipeline_properties(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_pipeline_properties) return;
    static const uint16_t s_pfnIdx[] = {
          578  // vkGetPipelinePropertiesEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_private_data(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_private_data) return;
    static const uint16_t s_pfnIdx[] = {
          325, // vkCreatePrivateDataSlotEXT
          385, // vkDestroyPrivateDataSlotEXT
          580, // vkGetPrivateDataEXT
          657  // vkSetPrivateDataEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_sample_locations(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_sample_locations) return;
    static const uint16_t s_pfnIdx[] = {
          232, // vkCmdSetSampleLocationsEXT
          540  // vkGetPhysicalDeviceMultisamplePropertiesEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_shader_module_identifier(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_shader_module_identifier) return;
    static const uint16_t s_pfnIdx[] = {
          601, // vkGetShaderModuleCreateInfoIdentifierEXT
          602  // vkGetShaderModuleIdentifierEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_shader_object(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_shader_object) return;
    static const uint16_t s_pfnIdx[] = {
           44, // vkCmdBindShadersEXT
           49, // vkCmdBindVertexBuffers2EXT
          157, // vkCmdSetAlphaToCoverageEnableEXT
          158, // vkCmdSetAlphaToOneEnableEXT
          163, // vkCmdSetColorBlendAdvancedEXT
          164, // vkCmdSetColorBlendEnableEXT
          165, // vkCmdSetColorBlendEquationEXT
          167, // vkCmdSetColorWriteMaskEXT
          168, // vkCmdSetConservativeRasterizationModeEXT
          169, // vkCmdSetCoverageModulationModeNV
          170, // vkCmdSetCoverageModulationTableEnableNV
          171, // vkCmdSetCoverageModulationTableNV
          172, // vkCmdSetCoverageReductionModeNV
          173, // vkCmdSetCoverageToColorEnableNV
          174, // vkCmdSetCoverageToColorLocationNV
          176, // vkCmdSetCullModeEXT
          180, // vkCmdSetDepthBiasEnableEXT
          183, // vkCmdSetDepthBoundsTestEnableEXT
          184, // vkCmdSetDepthClampEnableEXT
          185, // vkCmdSetDepthClipEnableEXT
          186, // vkCmdSetDepthClipNegativeOneToOneEXT
          188, // vkCmdSetDepthCompareOpEXT
          190, // vkCmdSetDepthTestEnableEXT
          192, // vkCmdSetDepthWriteEnableEXT
          205, // vkCmdSetExtraPrimitiveOverestimationSizeEXT
          209, // vkCmdSetFrontFaceEXT
          210, // vkCmdSetLineRasterizationModeEXT
          212, // vkCmdSetLineStippleEnableEXT
          214, // vkCmdSetLogicOpEXT
          215, // vkCmdSetLogicOpEnableEXT
          216, // vkCmdSetPatchControlPointsEXT
          220, // vkCmdSetPolygonModeEXT
          222, // vkCmdSetPrimitiveRestartEnableEXT
          224, // vkCmdSetPrimitiveTopologyEXT
          225, // vkCmdSetProvokingVertexModeEXT
          226, // vkCmdSetRasterizationSamplesEXT
          227, // vkCmdSetRasterizationStreamEXT
          229, // vkCmdSetRasterizerDiscardEnableEXT
          231, // vkCmdSetRepresentativeFragmentTestEnableNV
          233, // vkCmdSetSampleLocationsEnableEXT
          234, // vkCmdSetSampleMaskEXT
          237, // vkCmdSetScissorWithCountEXT
          238, // vkCmdSetShadingRateImageEnableNV
          241, // vkCmdSetStencilOpEXT
          244, // vkCmdSetStencilTestEnableEXT
          246, // vkCmdSetTessellationDomainOriginEXT
          247, // vkCmdSetVertexInputEXT
          250, // vkCmdSetViewportSwizzleNV
          251, // vkCmdSetViewportWScalingEnableNV
          254, // vkCmdSetViewportWithCountEXT
          338, // vkCreateShadersEXT
          392, // vkDestroyShaderEXT
          599  // vkGetShaderBinaryDataEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_swapchain_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_swapchain_maintenance1) return;
    static const uint16_t s_pfnIdx[] = {
          638  // vkReleaseSwapchainImagesEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_tooling_info(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_tooling_info) return;
    static const uint16_t s_pfnIdx[] = {
          564  // vkGetPhysicalDeviceToolPropertiesEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_transform_feedback(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_transform_feedback) return;
    static const uint16_t s_pfnIdx[] = {
           26, // vkCmdBeginQueryIndexedEXT
           32, // vkCmdBeginTransformFeedbackEXT
           46, // vkCmdBindTransformFeedbackBuffersEXT
          107, // vkCmdDrawIndirectByteCountEXT
          123, // vkCmdEndQueryIndexedEXT
          129  // vkCmdEndTransformFeedbackEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_validation_cache(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_validation_cache) return;
    static const uint16_t s_pfnIdx[] = {
          342, // vkCreateValidationCacheEXT
          396, // vkDestroyValidationCacheEXT
          606, // vkGetValidationCacheDataEXT
          620  // vkMergeValidationCachesEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_EXT_vertex_input_dynamic_state(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_vertex_input_dynamic_state) return;
    static const uint16_t s_pfnIdx[] = {
          247  // vkCmdSetVertexInputEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_buffer_collection(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->FUCHSIA_buffer_collection) return;
    static const uint16_t s_pfnIdx[] = {
          287, // vkCreateBufferCollectionFUCHSIA
          357, // vkDestroyBufferCollectionFUCHSIA
          422, // vkGetBufferCollectionPropertiesFUCHSIA
          646, // vkSetBufferCollectionBufferConstraintsFUCHSIA
          647  // vkSetBufferCollectionImageConstraintsFUCHSIA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_external_memory(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->FUCHSIA_external_memory) return;
    static const uint16_t s_pfnIdx[] = {
          506, // vkGetMemoryZirconHandleFUCHSIA
          507  // vkGetMemoryZirconHandlePropertiesFUCHSIA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_external_semaphore(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->FUCHSIA_external_semaphore) return;
    static const uint16_t s_pfnIdx[] = {
          598, // vkGetSemaphoreZirconHandleFUCHSIA
          613  // vkImportSemaphoreZirconHandleFUCHSIA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)
static void glad_vk_load_VK_FUCHSIA_imagepipe_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->FUCHSIA_imagepipe_surface) return;
    static const uint16_t s_pfnIdx[] = {
          314  // vkCreateImagePipeSurfaceFUCHSIA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
#if defined(VK_USE_PLATFORM_GGP)
static void glad_vk_load_VK_GGP_stream_descriptor_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->GGP_stream_descriptor_surface) return;
    static const uint16_t s_pfnIdx[] = {
          340  // vkCreateStreamDescriptorSurfaceGGP
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
static void glad_vk_load_VK_GOOGLE_display_timing(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->GOOGLE_display_timing) return;
    static const uint16_t s_pfnIdx[] = {
          509, // vkGetPastPresentationTimingGOOGLE
          589  // vkGetRefreshCycleDurationGOOGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_HUAWEI_cluster_culling_shader(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->HUAWEI_cluster_culling_shader) return;
    static const uint16_t s_pfnIdx[] = {
           99, // vkCmdDrawClusterHUAWEI
          100  // vkCmdDrawClusterIndirectHUAWEI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_HUAWEI_invocation_mask(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->HUAWEI_invocation_mask) return;
    static const uint16_t s_pfnIdx[] = {
           41  // vkCmdBindInvocationMaskHUAWEI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_HUAWEI_subpass_shading(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->HUAWEI_subpass_shading) return;
    static const uint16_t s_pfnIdx[] = {
          255, // vkCmdSubpassShadingHUAWEI
          465  // vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_INTEL_performance_query(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->INTEL_performance_query) return;
    static const uint16_t s_pfnIdx[] = {
            4, // vkAcquirePerformanceConfigurationINTEL
          217, // vkCmdSetPerformanceMarkerINTEL
          218, // vkCmdSetPerformanceOverrideINTEL
          219, // vkCmdSetPerformanceStreamMarkerINTEL
          510, // vkGetPerformanceParameterINTEL
          614, // vkInitializePerformanceApiINTEL
          627, // vkQueueSetPerformanceConfigurationINTEL
          636, // vkReleasePerformanceConfigurationINTEL
          664  // vkUninitializePerformanceApiINTEL
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_acceleration_structure(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_acceleration_structure) return;
    static const uint16_t s_pfnIdx[] = {
           21, // vkBuildAccelerationStructuresKHR
           54, // vkCmdBuildAccelerationStructuresIndirectKHR
           55, // vkCmdBuildAccelerationStructuresKHR
           61, // vkCmdCopyAccelerationStructureKHR
           63, // vkCmdCopyAccelerationStructureToMemoryKHR
           77, // vkCmdCopyMemoryToAccelerationStructureKHR
          265, // vkCmdWriteAccelerationStructuresPropertiesKHR
          274, // vkCopyAccelerationStructureKHR
          275, // vkCopyAccelerationStructureToMemoryKHR
          278, // vkCopyMemoryToAccelerationStructureKHR
          283, // vkCreateAccelerationStructureKHR
          354, // vkDestroyAccelerationStructureKHR
          416, // vkGetAccelerationStructureBuildSizesKHR
          417, // vkGetAccelerationStructureDeviceAddressKHR
          444, // vkGetDeviceAccelerationStructureCompatibilityKHR
          675  // vkWriteAccelerationStructuresPropertiesKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
static void glad_vk_load_VK_KHR_android_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_android_surface) return;
    static const uint16_t s_pfnIdx[] = {
          285  // vkCreateAndroidSurfaceKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
static void glad_vk_load_VK_KHR_bind_memory2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_bind_memory2) return;
    static const uint16_t s_pfnIdx[] = {
           15, // vkBindBufferMemory2KHR
           18  // vkBindImageMemory2KHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_buffer_device_address(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_buffer_device_address) return;
    static const uint16_t s_pfnIdx[] = {
          425, // vkGetBufferDeviceAddressKHR
          430, // vkGetBufferOpaqueCaptureAddressKHR
          460  // vkGetDeviceMemoryOpaqueCaptureAddressKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_calibrated_timestamps(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_calibrated_timestamps) return;
    static const uint16_t s_pfnIdx[] = {
          433, // vkGetCalibratedTimestampsKHR
          512  // vkGetPhysicalDeviceCalibrateableTimeDomainsKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_cooperative_matrix(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_cooperative_matrix) return;
    static const uint16_t s_pfnIdx[] = {
          513  // vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_copy_commands2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_copy_commands2) return;
    static const uint16_t s_pfnIdx[] = {
           52, // vkCmdBlitImage2KHR
           66, // vkCmdCopyBuffer2KHR
           69, // vkCmdCopyBufferToImage2KHR
           72, // vkCmdCopyImage2KHR
           75, // vkCmdCopyImageToBuffer2KHR
          156  // vkCmdResolveImage2KHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_create_renderpass2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_create_renderpass2) return;
    static const uint16_t s_pfnIdx[] = {
           29, // vkCmdBeginRenderPass2KHR
          126, // vkCmdEndRenderPass2KHR
          138, // vkCmdNextSubpass2KHR
          331  // vkCreateRenderPass2KHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_deferred_host_operations(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_deferred_host_operations) return;
    static const uint16_t s_pfnIdx[] = {
          297, // vkCreateDeferredOperationKHR
          353, // vkDeferredOperationJoinKHR
          366, // vkDestroyDeferredOperationKHR
          435, // vkGetDeferredOperationMaxConcurrencyKHR
          436  // vkGetDeferredOperationResultKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_descriptor_update_template(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_descriptor_update_template) return;
    static const uint16_t s_pfnIdx[] = {
          149, // vkCmdPushDescriptorSetWithTemplateKHR
          301, // vkCreateDescriptorUpdateTemplateKHR
          370, // vkDestroyDescriptorUpdateTemplateKHR
          668  // vkUpdateDescriptorSetWithTemplateKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_device_group(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_device_group) return;
    static const uint16_t s_pfnIdx[] = {
            2, // vkAcquireNextImage2KHR
           93, // vkCmdDispatchBaseKHR
          196, // vkCmdSetDeviceMaskKHR
          449, // vkGetDeviceGroupPeerMemoryFeaturesKHR
          450, // vkGetDeviceGroupPresentCapabilitiesKHR
          452, // vkGetDeviceGroupSurfacePresentModesKHR
          542  // vkGetPhysicalDevicePresentRectanglesKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_device_group_creation(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_device_group_creation) return;
    static const uint16_t s_pfnIdx[] = {
          408  // vkEnumeratePhysicalDeviceGroupsKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_display) return;
    static const uint16_t s_pfnIdx[] = {
          304, // vkCreateDisplayModeKHR
          305, // vkCreateDisplayPlaneSurfaceKHR
          467, // vkGetDisplayModePropertiesKHR
          469, // vkGetDisplayPlaneCapabilitiesKHR
          470, // vkGetDisplayPlaneSupportedDisplaysKHR
          517, // vkGetPhysicalDeviceDisplayPlanePropertiesKHR
          519  // vkGetPhysicalDeviceDisplayPropertiesKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_display_swapchain(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_display_swapchain) return;
    static const uint16_t s_pfnIdx[] = {
          339  // vkCreateSharedSwapchainsKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_draw_indirect_count(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_draw_indirect_count) return;
    static const uint16_t s_pfnIdx[] = {
          105, // vkCmdDrawIndexedIndirectCountKHR
          110  // vkCmdDrawIndirectCountKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_dynamic_rendering(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_dynamic_rendering) return;
    static const uint16_t s_pfnIdx[] = {
           31, // vkCmdBeginRenderingKHR
          128  // vkCmdEndRenderingKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_external_fence_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_external_fence_capabilities) return;
    static const uint16_t s_pfnIdx[] = {
          523  // vkGetPhysicalDeviceExternalFencePropertiesKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_external_fence_fd(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_external_fence_fd) return;
    static const uint16_t s_pfnIdx[] = {
          477, // vkGetFenceFdKHR
          609  // vkImportFenceFdKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_external_fence_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_external_fence_win32) return;
    static const uint16_t s_pfnIdx[] = {
          479, // vkGetFenceWin32HandleKHR
          610  // vkImportFenceWin32HandleKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
static void glad_vk_load_VK_KHR_external_memory_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_external_memory_capabilities) return;
    static const uint16_t s_pfnIdx[] = {
          521  // vkGetPhysicalDeviceExternalBufferPropertiesKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_external_memory_fd(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_external_memory_fd) return;
    static const uint16_t s_pfnIdx[] = {
          499, // vkGetMemoryFdKHR
          500  // vkGetMemoryFdPropertiesKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_external_memory_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_external_memory_win32) return;
    static const uint16_t s_pfnIdx[] = {
          503, // vkGetMemoryWin32HandleKHR
          505  // vkGetMemoryWin32HandlePropertiesKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
static void glad_vk_load_VK_KHR_external_semaphore_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_external_semaphore_capabilities) return;
    static const uint16_t s_pfnIdx[] = {
          526  // vkGetPhysicalDeviceExternalSemaphorePropertiesKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_external_semaphore_fd(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_external_semaphore_fd) return;
    static const uint16_t s_pfnIdx[] = {
          596, // vkGetSemaphoreFdKHR
          611  // vkImportSemaphoreFdKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_external_semaphore_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_external_semaphore_win32) return;
    static const uint16_t s_pfnIdx[] = {
          597, // vkGetSemaphoreWin32HandleKHR
          612  // vkImportSemaphoreWin32HandleKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
static void glad_vk_load_VK_KHR_fragment_shading_rate(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_fragment_shading_rate) return;
    static const uint16_t s_pfnIdx[] = {
          207, // vkCmdSetFragmentShadingRateKHR
          533  // vkGetPhysicalDeviceFragmentShadingRatesKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_get_display_properties2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_get_display_properties2) return;
    static const uint16_t s_pfnIdx[] = {
          466, // vkGetDisplayModeProperties2KHR
          468, // vkGetDisplayPlaneCapabilities2KHR
          516, // vkGetPhysicalDeviceDisplayPlaneProperties2KHR
          518  // vkGetPhysicalDeviceDisplayProperties2KHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_get_memory_requirements2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_get_memory_requirements2) return;
    static const uint16_t s_pfnIdx[] = {
          428, // vkGetBufferMemoryRequirements2KHR
          485, // vkGetImageMemoryRequirements2KHR
          489  // vkGetImageSparseMemoryRequirements2KHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_get_physical_device_properties2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_get_physical_device_properties2) return;
    static const uint16_t s_pfnIdx[] = {
          529, // vkGetPhysicalDeviceFeatures2KHR
          532, // vkGetPhysicalDeviceFormatProperties2KHR
          536, // vkGetPhysicalDeviceImageFormatProperties2KHR
          539, // vkGetPhysicalDeviceMemoryProperties2KHR
          545, // vkGetPhysicalDeviceProperties2KHR
          549, // vkGetPhysicalDeviceQueueFamilyProperties2KHR
          553  // vkGetPhysicalDeviceSparseImageFormatProperties2KHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_get_surface_capabilities2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_get_surface_capabilities2) return;
    static const uint16_t s_pfnIdx[] = {
          556, // vkGetPhysicalDeviceSurfaceCapabilities2KHR
          558  // vkGetPhysicalDeviceSurfaceFormats2KHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_maintenance1) return;
    static const uint16_t s_pfnIdx[] = {
          663  // vkTrimCommandPoolKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_maintenance3(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_maintenance3) return;
    static const uint16_t s_pfnIdx[] = {
          443  // vkGetDescriptorSetLayoutSupportKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_maintenance4(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_maintenance4) return;
    static const uint16_t s_pfnIdx[] = {
          446, // vkGetDeviceBufferMemoryRequirementsKHR
          454, // vkGetDeviceImageMemoryRequirementsKHR
          456  // vkGetDeviceImageSparseMemoryRequirementsKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_maintenance5(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_maintenance5) return;
    static const uint16_t s_pfnIdx[] = {
           40, // vkCmdBindIndexBuffer2KHR
          457, // vkGetDeviceImageSubresourceLayoutKHR
          492, // vkGetImageSubresourceLayout2KHR
          591  // vkGetRenderingAreaGranularityKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_maintenance6(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_maintenance6) return;
    static const uint16_t s_pfnIdx[] = {
           34, // vkCmdBindDescriptorBufferEmbeddedSamplers2EXT
           38, // vkCmdBindDescriptorSets2KHR
          145, // vkCmdPushConstants2KHR
          146, // vkCmdPushDescriptorSet2KHR
          148, // vkCmdPushDescriptorSetWithTemplate2KHR
          193  // vkCmdSetDescriptorBufferOffsets2EXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_map_memory2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_map_memory2) return;
    static const uint16_t s_pfnIdx[] = {
          618, // vkMapMemory2KHR
          666  // vkUnmapMemory2KHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_performance_query(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_performance_query) return;
    static const uint16_t s_pfnIdx[] = {
            5, // vkAcquireProfilingLockKHR
          409, // vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR
          546, // vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR
          637  // vkReleaseProfilingLockKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_pipeline_executable_properties(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_pipeline_executable_properties) return;
    static const uint16_t s_pfnIdx[] = {
          573, // vkGetPipelineExecutableInternalRepresentationsKHR
          574, // vkGetPipelineExecutablePropertiesKHR
          575  // vkGetPipelineExecutableStatisticsKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_present_wait(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_present_wait) return;
    static const uint16_t s_pfnIdx[] = {
          672  // vkWaitForPresentKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_push_descriptor(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_push_descriptor) return;
    static const uint16_t s_pfnIdx[] = {
          147, // vkCmdPushDescriptorSetKHR
          149  // vkCmdPushDescriptorSetWithTemplateKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_ray_tracing_maintenance1(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_ray_tracing_maintenance1) return;
    static const uint16_t s_pfnIdx[] = {
          256  // vkCmdTraceRaysIndirect2KHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_ray_tracing_pipeline(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_ray_tracing_pipeline) return;
    static const uint16_t s_pfnIdx[] = {
          230, // vkCmdSetRayTracingPipelineStackSizeKHR
          257, // vkCmdTraceRaysIndirectKHR
          258, // vkCmdTraceRaysKHR
          327, // vkCreateRayTracingPipelinesKHR
          585, // vkGetRayTracingCaptureReplayShaderGroupHandlesKHR
          586, // vkGetRayTracingShaderGroupHandlesKHR
          588  // vkGetRayTracingShaderGroupStackSizeKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_sampler_ycbcr_conversion(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_sampler_ycbcr_conversion) return;
    static const uint16_t s_pfnIdx[] = {
          334, // vkCreateSamplerYcbcrConversionKHR
          390  // vkDestroySamplerYcbcrConversionKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_shared_presentable_image(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_shared_presentable_image) return;
    static const uint16_t s_pfnIdx[] = {
          605  // vkGetSwapchainStatusKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_surface) return;
    static const uint16_t s_pfnIdx[] = {
          394, // vkDestroySurfaceKHR
          557, // vkGetPhysicalDeviceSurfaceCapabilitiesKHR
          559, // vkGetPhysicalDeviceSurfaceFormatsKHR
          561, // vkGetPhysicalDeviceSurfacePresentModesKHR
          562  // vkGetPhysicalDeviceSurfaceSupportKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_swapchain(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_swapchain) return;
    static const uint16_t s_pfnIdx[] = {
            2, // vkAcquireNextImage2KHR
            3, // vkAcquireNextImageKHR
          341, // vkCreateSwapchainKHR
          395, // vkDestroySwapchainKHR
          450, // vkGetDeviceGroupPresentCapabilitiesKHR
          452, // vkGetDeviceGroupSurfacePresentModesKHR
          542, // vkGetPhysicalDevicePresentRectanglesKHR
          604, // vkGetSwapchainImagesKHR
          626  // vkQueuePresentKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_synchronization2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_synchronization2) return;
    static const uint16_t s_pfnIdx[] = {
          142, // vkCmdPipelineBarrier2KHR
          152, // vkCmdResetEvent2KHR
          202, // vkCmdSetEvent2KHR
          264, // vkCmdWaitEvents2KHR
          267, // vkCmdWriteBufferMarker2AMD
          272, // vkCmdWriteTimestamp2KHR
          582, // vkGetQueueCheckpointData2NV
          630  // vkQueueSubmit2KHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_timeline_semaphore(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_timeline_semaphore) return;
    static const uint16_t s_pfnIdx[] = {
          595, // vkGetSemaphoreCounterValueKHR
          659, // vkSignalSemaphoreKHR
          674  // vkWaitSemaphoresKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_video_decode_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_video_decode_queue) return;
    static const uint16_t s_pfnIdx[] = {
           88  // vkCmdDecodeVideoKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_video_encode_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_video_encode_queue) return;
    static const uint16_t s_pfnIdx[] = {
          119, // vkCmdEncodeVideoKHR
          473, // vkGetEncodedVideoSessionParametersKHR
          566  // vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_KHR_video_queue(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_video_queue) return;
    static const uint16_t s_pfnIdx[] = {
           20, // vkBindVideoSessionMemoryKHR
           33, // vkCmdBeginVideoCodingKHR
           60, // vkCmdControlVideoCodingKHR
          130, // vkCmdEndVideoCodingKHR
          344, // vkCreateVideoSessionKHR
          345, // vkCreateVideoSessionParametersKHR
          397, // vkDestroyVideoSessionKHR
          398, // vkDestroyVideoSessionParametersKHR
          565, // vkGetPhysicalDeviceVideoCapabilitiesKHR
          567, // vkGetPhysicalDeviceVideoFormatPropertiesKHR
          607, // vkGetVideoSessionMemoryRequirementsKHR
          670  // vkUpdateVideoSessionParametersKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
static void glad_vk_load_VK_KHR_wayland_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_wayland_surface) return;
    static const uint16_t s_pfnIdx[] = {
          346, // vkCreateWaylandSurfaceKHR
          568  // vkGetPhysicalDeviceWaylandPresentationSupportKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_KHR_win32_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_win32_surface) return;
    static const uint16_t s_pfnIdx[] = {
          347, // vkCreateWin32SurfaceKHR
          569  // vkGetPhysicalDeviceWin32PresentationSupportKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
static void glad_vk_load_VK_KHR_xcb_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_xcb_surface) return;
    static const uint16_t s_pfnIdx[] = {
          348, // vkCreateXcbSurfaceKHR
          570  // vkGetPhysicalDeviceXcbPresentationSupportKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)
static void glad_vk_load_VK_KHR_xlib_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_xlib_surface) return;
    static const uint16_t s_pfnIdx[] = {
          349, // vkCreateXlibSurfaceKHR
          571  // vkGetPhysicalDeviceXlibPresentationSupportKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
#if defined(VK_USE_PLATFORM_IOS_MVK)
static void glad_vk_load_VK_MVK_ios_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MVK_ios_surface) return;
    static const uint16_t s_pfnIdx[] = {
          312  // vkCreateIOSSurfaceMVK
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
#if defined(VK_USE_PLATFORM_MACOS_MVK)
static void glad_vk_load_VK_MVK_macos_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MVK_macos_surface) return;
    static const uint16_t s_pfnIdx[] = {
          318  // vkCreateMacOSSurfaceMVK
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
#if defined(VK_USE_PLATFORM_VI_NN)
static void glad_vk_load_VK_NN_vi_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NN_vi_surface) return;
    static const uint16_t s_pfnIdx[] = {
          343  // vkCreateViSurfaceNN
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
static void glad_vk_load_VK_NVX_binary_import(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NVX_binary_import) return;
    static const uint16_t s_pfnIdx[] = {
           83, // vkCmdCuLaunchKernelNVX
          291, // vkCreateCuFunctionNVX
          292, // vkCreateCuModuleNVX
          360, // vkDestroyCuFunctionNVX
          361  // vkDestroyCuModuleNVX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NVX_image_view_handle(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NVX_image_view_handle) return;
    static const uint16_t s_pfnIdx[] = {
          493, // vkGetImageViewAddressNVX
          494  // vkGetImageViewHandleNVX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_NV_acquire_winrt_display(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_acquire_winrt_display) return;
    static const uint16_t s_pfnIdx[] = {
            6, // vkAcquireWinrtDisplayNV
          608  // vkGetWinrtDisplayNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
static void glad_vk_load_VK_NV_clip_space_w_scaling(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_clip_space_w_scaling) return;
    static const uint16_t s_pfnIdx[] = {
          252  // vkCmdSetViewportWScalingNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_cooperative_matrix(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_cooperative_matrix) return;
    static const uint16_t s_pfnIdx[] = {
          514  // vkGetPhysicalDeviceCooperativeMatrixPropertiesNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_copy_memory_indirect(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_copy_memory_indirect) return;
    static const uint16_t s_pfnIdx[] = {
           76, // vkCmdCopyMemoryIndirectNV
           78  // vkCmdCopyMemoryToImageIndirectNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_coverage_reduction_mode(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_coverage_reduction_mode) return;
    static const uint16_t s_pfnIdx[] = {
          554  // vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_cuda_kernel_launch(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_cuda_kernel_launch) return;
    static const uint16_t s_pfnIdx[] = {
           84, // vkCmdCudaLaunchKernelNV
          293, // vkCreateCudaFunctionNV
          294, // vkCreateCudaModuleNV
          362, // vkDestroyCudaFunctionNV
          363, // vkDestroyCudaModuleNV
          434  // vkGetCudaModuleCacheNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_device_diagnostic_checkpoints(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_device_diagnostic_checkpoints) return;
    static const uint16_t s_pfnIdx[] = {
          161, // vkCmdSetCheckpointNV
          583  // vkGetQueueCheckpointDataNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_device_generated_commands(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_device_generated_commands) return;
    static const uint16_t s_pfnIdx[] = {
           43, // vkCmdBindPipelineShaderGroupNV
          132, // vkCmdExecuteGeneratedCommandsNV
          143, // vkCmdPreprocessGeneratedCommandsNV
          316, // vkCreateIndirectCommandsLayoutNV
          377, // vkDestroyIndirectCommandsLayoutNV
          481  // vkGetGeneratedCommandsMemoryRequirementsNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_device_generated_commands_compute(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_device_generated_commands_compute) return;
    static const uint16_t s_pfnIdx[] = {
          261, // vkCmdUpdatePipelineIndirectBufferNV
          576, // vkGetPipelineIndirectDeviceAddressNV
          577  // vkGetPipelineIndirectMemoryRequirementsNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_external_memory_capabilities(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_external_memory_capabilities) return;
    static const uint16_t s_pfnIdx[] = {
          524  // vkGetPhysicalDeviceExternalImageFormatPropertiesNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_external_memory_rdma(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_external_memory_rdma) return;
    static const uint16_t s_pfnIdx[] = {
          502  // vkGetMemoryRemoteAddressNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

#if defined(VK_USE_PLATFORM_WIN32_KHR)
static void glad_vk_load_VK_NV_external_memory_win32(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_external_memory_win32) return;
    static const uint16_t s_pfnIdx[] = {
          504  // vkGetMemoryWin32HandleNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
static void glad_vk_load_VK_NV_fragment_shading_rate_enums(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_fragment_shading_rate_enums) return;
    static const uint16_t s_pfnIdx[] = {
          206  // vkCmdSetFragmentShadingRateEnumNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_low_latency2(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_low_latency2) return;
    static const uint16_t s_pfnIdx[] = {
          497, // vkGetLatencyTimingsNV
          616, // vkLatencySleepNV
          625, // vkQueueNotifyOutOfBandNV
          653, // vkSetLatencyMarkerNV
          654  // vkSetLatencySleepModeNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_memory_decompression(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_memory_decompression) return;
    static const uint16_t s_pfnIdx[] = {
           89, // vkCmdDecompressMemoryIndirectCountNV
           90  // vkCmdDecompressMemoryNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_mesh_shader(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_mesh_shader) return;
    static const uint16_t s_pfnIdx[] = {
          113, // vkCmdDrawMeshTasksIndirectCountNV
          115, // vkCmdDrawMeshTasksIndirectNV
          116  // vkCmdDrawMeshTasksNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_optical_flow(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_optical_flow) return;
    static const uint16_t s_pfnIdx[] = {
           19, // vkBindOpticalFlowSessionImageNV
          139, // vkCmdOpticalFlowExecuteNV
          321, // vkCreateOpticalFlowSessionNV
          380, // vkDestroyOpticalFlowSessionNV
          541  // vkGetPhysicalDeviceOpticalFlowImageFormatsNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_ray_tracing(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_ray_tracing) return;
    static const uint16_t s_pfnIdx[] = {
           12, // vkBindAccelerationStructureMemoryNV
           53, // vkCmdBuildAccelerationStructureNV
           62, // vkCmdCopyAccelerationStructureNV
          259, // vkCmdTraceRaysNV
          266, // vkCmdWriteAccelerationStructuresPropertiesNV
          273, // vkCompileDeferredNV
          284, // vkCreateAccelerationStructureNV
          328, // vkCreateRayTracingPipelinesNV
          355, // vkDestroyAccelerationStructureNV
          418, // vkGetAccelerationStructureHandleNV
          419, // vkGetAccelerationStructureMemoryRequirementsNV
          587  // vkGetRayTracingShaderGroupHandlesNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_scissor_exclusive(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_scissor_exclusive) return;
    static const uint16_t s_pfnIdx[] = {
          203, // vkCmdSetExclusiveScissorEnableNV
          204  // vkCmdSetExclusiveScissorNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_NV_shading_rate_image(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_shading_rate_image) return;
    static const uint16_t s_pfnIdx[] = {
           45, // vkCmdBindShadingRateImageNV
          162, // vkCmdSetCoarseSampleOrderNV
          249  // vkCmdSetViewportShadingRatePaletteNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_load_VK_QCOM_tile_properties(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_tile_properties) return;
    static const uint16_t s_pfnIdx[] = {
          472, // vkGetDynamicRenderingTilePropertiesQCOM
          480  // vkGetFramebufferTilePropertiesQCOM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

#if defined(VK_USE_PLATFORM_SCREEN_QNX)
static void glad_vk_load_VK_QNX_external_memory_screen_buffer(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QNX_external_memory_screen_buffer) return;
    static const uint16_t s_pfnIdx[] = {
          593  // vkGetScreenBufferPropertiesQNX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
static void glad_vk_load_VK_QNX_screen_surface(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QNX_screen_surface) return;
    static const uint16_t s_pfnIdx[] = {
          335, // vkCreateScreenSurfaceQNX
          550  // vkGetPhysicalDeviceScreenPresentationSupportQNX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}


#endif
static void glad_vk_load_VK_VALVE_descriptor_set_host_mapping(GladVulkanContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VALVE_descriptor_set_host_mapping) return;
    static const uint16_t s_pfnIdx[] = {
          438, // vkGetDescriptorSetHostMappingVALVE
          440  // vkGetDescriptorSetLayoutHostMappingInfoVALVE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i)
        context->pfnArray[s_pfnIdx[i]] = load(userptr, glad_pfn_names[s_pfnIdx[i]]);
}

static void glad_vk_resolve_aliases(GladVulkanContext *context) {
    static const GladAliasPair_t s_aliases[] = {
#if defined(VK_USE_PLATFORM_WIN32_KHR)

#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)

#endif
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)

#endif
        {   14,    15 }, // vkBindBufferMemory2 and vkBindBufferMemory2KHR
        {   15,    14 }, // vkBindBufferMemory2KHR and vkBindBufferMemory2
        {   17,    18 }, // vkBindImageMemory2 and vkBindImageMemory2KHR
        {   18,    17 }, // vkBindImageMemory2KHR and vkBindImageMemory2
        {   30,    31 }, // vkCmdBeginRendering and vkCmdBeginRenderingKHR
        {   31,    30 }, // vkCmdBeginRenderingKHR and vkCmdBeginRendering
        {   28,    29 }, // vkCmdBeginRenderPass2 and vkCmdBeginRenderPass2KHR
        {   29,    28 }, // vkCmdBeginRenderPass2KHR and vkCmdBeginRenderPass2
        {   48,    49 }, // vkCmdBindVertexBuffers2 and vkCmdBindVertexBuffers2EXT
        {   49,    48 }, // vkCmdBindVertexBuffers2EXT and vkCmdBindVertexBuffers2
        {   51,    52 }, // vkCmdBlitImage2 and vkCmdBlitImage2KHR
        {   52,    51 }, // vkCmdBlitImage2KHR and vkCmdBlitImage2
        {   65,    66 }, // vkCmdCopyBuffer2 and vkCmdCopyBuffer2KHR
        {   66,    65 }, // vkCmdCopyBuffer2KHR and vkCmdCopyBuffer2
        {   68,    69 }, // vkCmdCopyBufferToImage2 and vkCmdCopyBufferToImage2KHR
        {   69,    68 }, // vkCmdCopyBufferToImage2KHR and vkCmdCopyBufferToImage2
        {   71,    72 }, // vkCmdCopyImage2 and vkCmdCopyImage2KHR
        {   72,    71 }, // vkCmdCopyImage2KHR and vkCmdCopyImage2
        {   74,    75 }, // vkCmdCopyImageToBuffer2 and vkCmdCopyImageToBuffer2KHR
        {   75,    74 }, // vkCmdCopyImageToBuffer2KHR and vkCmdCopyImageToBuffer2
        {   92,    93 }, // vkCmdDispatchBase and vkCmdDispatchBaseKHR
        {   93,    92 }, // vkCmdDispatchBaseKHR and vkCmdDispatchBase
#if defined(VK_ENABLE_BETA_EXTENSIONS)

#endif
#if defined(VK_ENABLE_BETA_EXTENSIONS)

#endif
#if defined(VK_ENABLE_BETA_EXTENSIONS)

#endif
        {  103,   104 }, // vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountAMD
        {  103,   105 }, // vkCmdDrawIndexedIndirectCount and vkCmdDrawIndexedIndirectCountKHR
        {  104,   103 }, // vkCmdDrawIndexedIndirectCountAMD and vkCmdDrawIndexedIndirectCount
        {  104,   105 }, // vkCmdDrawIndexedIndirectCountAMD and vkCmdDrawIndexedIndirectCountKHR
        {  105,   103 }, // vkCmdDrawIndexedIndirectCountKHR and vkCmdDrawIndexedIndirectCount
        {  105,   104 }, // vkCmdDrawIndexedIndirectCountKHR and vkCmdDrawIndexedIndirectCountAMD
        {  108,   109 }, // vkCmdDrawIndirectCount and vkCmdDrawIndirectCountAMD
        {  108,   110 }, // vkCmdDrawIndirectCount and vkCmdDrawIndirectCountKHR
        {  109,   108 }, // vkCmdDrawIndirectCountAMD and vkCmdDrawIndirectCount
        {  109,   110 }, // vkCmdDrawIndirectCountAMD and vkCmdDrawIndirectCountKHR
        {  110,   108 }, // vkCmdDrawIndirectCountKHR and vkCmdDrawIndirectCount
        {  110,   109 }, // vkCmdDrawIndirectCountKHR and vkCmdDrawIndirectCountAMD
        {  127,   128 }, // vkCmdEndRendering and vkCmdEndRenderingKHR
        {  128,   127 }, // vkCmdEndRenderingKHR and vkCmdEndRendering
        {  125,   126 }, // vkCmdEndRenderPass2 and vkCmdEndRenderPass2KHR
        {  126,   125 }, // vkCmdEndRenderPass2KHR and vkCmdEndRenderPass2
#if defined(VK_ENABLE_BETA_EXTENSIONS)

#endif
        {  137,   138 }, // vkCmdNextSubpass2 and vkCmdNextSubpass2KHR
        {  138,   137 }, // vkCmdNextSubpass2KHR and vkCmdNextSubpass2
        {  141,   142 }, // vkCmdPipelineBarrier2 and vkCmdPipelineBarrier2KHR
        {  142,   141 }, // vkCmdPipelineBarrier2KHR and vkCmdPipelineBarrier2
        {  151,   152 }, // vkCmdResetEvent2 and vkCmdResetEvent2KHR
        {  152,   151 }, // vkCmdResetEvent2KHR and vkCmdResetEvent2
        {  155,   156 }, // vkCmdResolveImage2 and vkCmdResolveImage2KHR
        {  156,   155 }, // vkCmdResolveImage2KHR and vkCmdResolveImage2
        {  175,   176 }, // vkCmdSetCullMode and vkCmdSetCullModeEXT
        {  176,   175 }, // vkCmdSetCullModeEXT and vkCmdSetCullMode
        {  179,   180 }, // vkCmdSetDepthBiasEnable and vkCmdSetDepthBiasEnableEXT
        {  180,   179 }, // vkCmdSetDepthBiasEnableEXT and vkCmdSetDepthBiasEnable
        {  182,   183 }, // vkCmdSetDepthBoundsTestEnable and vkCmdSetDepthBoundsTestEnableEXT
        {  183,   182 }, // vkCmdSetDepthBoundsTestEnableEXT and vkCmdSetDepthBoundsTestEnable
        {  187,   188 }, // vkCmdSetDepthCompareOp and vkCmdSetDepthCompareOpEXT
        {  188,   187 }, // vkCmdSetDepthCompareOpEXT and vkCmdSetDepthCompareOp
        {  189,   190 }, // vkCmdSetDepthTestEnable and vkCmdSetDepthTestEnableEXT
        {  190,   189 }, // vkCmdSetDepthTestEnableEXT and vkCmdSetDepthTestEnable
        {  191,   192 }, // vkCmdSetDepthWriteEnable and vkCmdSetDepthWriteEnableEXT
        {  192,   191 }, // vkCmdSetDepthWriteEnableEXT and vkCmdSetDepthWriteEnable
        {  195,   196 }, // vkCmdSetDeviceMask and vkCmdSetDeviceMaskKHR
        {  196,   195 }, // vkCmdSetDeviceMaskKHR and vkCmdSetDeviceMask
        {  201,   202 }, // vkCmdSetEvent2 and vkCmdSetEvent2KHR
        {  202,   201 }, // vkCmdSetEvent2KHR and vkCmdSetEvent2
        {  208,   209 }, // vkCmdSetFrontFace and vkCmdSetFrontFaceEXT
        {  209,   208 }, // vkCmdSetFrontFaceEXT and vkCmdSetFrontFace
        {  221,   222 }, // vkCmdSetPrimitiveRestartEnable and vkCmdSetPrimitiveRestartEnableEXT
        {  222,   221 }, // vkCmdSetPrimitiveRestartEnableEXT and vkCmdSetPrimitiveRestartEnable
        {  223,   224 }, // vkCmdSetPrimitiveTopology and vkCmdSetPrimitiveTopologyEXT
        {  224,   223 }, // vkCmdSetPrimitiveTopologyEXT and vkCmdSetPrimitiveTopology
        {  228,   229 }, // vkCmdSetRasterizerDiscardEnable and vkCmdSetRasterizerDiscardEnableEXT
        {  229,   228 }, // vkCmdSetRasterizerDiscardEnableEXT and vkCmdSetRasterizerDiscardEnable
        {  236,   237 }, // vkCmdSetScissorWithCount and vkCmdSetScissorWithCountEXT
        {  237,   236 }, // vkCmdSetScissorWithCountEXT and vkCmdSetScissorWithCount
        {  240,   241 }, // vkCmdSetStencilOp and vkCmdSetStencilOpEXT
        {  241,   240 }, // vkCmdSetStencilOpEXT and vkCmdSetStencilOp
        {  243,   244 }, // vkCmdSetStencilTestEnable and vkCmdSetStencilTestEnableEXT
        {  244,   243 }, // vkCmdSetStencilTestEnableEXT and vkCmdSetStencilTestEnable
        {  253,   254 }, // vkCmdSetViewportWithCount and vkCmdSetViewportWithCountEXT
        {  254,   253 }, // vkCmdSetViewportWithCountEXT and vkCmdSetViewportWithCount
        {  263,   264 }, // vkCmdWaitEvents2 and vkCmdWaitEvents2KHR
        {  264,   263 }, // vkCmdWaitEvents2KHR and vkCmdWaitEvents2
        {  271,   272 }, // vkCmdWriteTimestamp2 and vkCmdWriteTimestamp2KHR
        {  272,   271 }, // vkCmdWriteTimestamp2KHR and vkCmdWriteTimestamp2
#if defined(VK_USE_PLATFORM_ANDROID_KHR)

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)

#endif
        {  300,   301 }, // vkCreateDescriptorUpdateTemplate and vkCreateDescriptorUpdateTemplateKHR
        {  301,   300 }, // vkCreateDescriptorUpdateTemplateKHR and vkCreateDescriptorUpdateTemplate
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)

#endif
#if defined(VK_ENABLE_BETA_EXTENSIONS)

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)

#endif
#if defined(VK_USE_PLATFORM_IOS_MVK)

#endif
#if defined(VK_USE_PLATFORM_MACOS_MVK)

#endif
#if defined(VK_USE_PLATFORM_METAL_EXT)

#endif
        {  324,   325 }, // vkCreatePrivateDataSlot and vkCreatePrivateDataSlotEXT
        {  325,   324 }, // vkCreatePrivateDataSlotEXT and vkCreatePrivateDataSlot
        {  330,   331 }, // vkCreateRenderPass2 and vkCreateRenderPass2KHR
        {  331,   330 }, // vkCreateRenderPass2KHR and vkCreateRenderPass2
        {  333,   334 }, // vkCreateSamplerYcbcrConversion and vkCreateSamplerYcbcrConversionKHR
        {  334,   333 }, // vkCreateSamplerYcbcrConversionKHR and vkCreateSamplerYcbcrConversion
#if defined(VK_USE_PLATFORM_SCREEN_QNX)

#endif
#if defined(VK_USE_PLATFORM_GGP)

#endif
#if defined(VK_USE_PLATFORM_VI_NN)

#endif
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)

#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)

#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)

#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)

#endif
        {  369,   370 }, // vkDestroyDescriptorUpdateTemplate and vkDestroyDescriptorUpdateTemplateKHR
        {  370,   369 }, // vkDestroyDescriptorUpdateTemplateKHR and vkDestroyDescriptorUpdateTemplate
        {  384,   385 }, // vkDestroyPrivateDataSlot and vkDestroyPrivateDataSlotEXT
        {  385,   384 }, // vkDestroyPrivateDataSlotEXT and vkDestroyPrivateDataSlot
        {  389,   390 }, // vkDestroySamplerYcbcrConversion and vkDestroySamplerYcbcrConversionKHR
        {  390,   389 }, // vkDestroySamplerYcbcrConversionKHR and vkDestroySamplerYcbcrConversion
        {  407,   408 }, // vkEnumeratePhysicalDeviceGroups and vkEnumeratePhysicalDeviceGroupsKHR
        {  408,   407 }, // vkEnumeratePhysicalDeviceGroupsKHR and vkEnumeratePhysicalDeviceGroups
#if defined(VK_USE_PLATFORM_METAL_EXT)

#endif
#if defined(VK_USE_PLATFORM_ANDROID_KHR)

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)

#endif
        {  423,   424 }, // vkGetBufferDeviceAddress and vkGetBufferDeviceAddressEXT
        {  423,   425 }, // vkGetBufferDeviceAddress and vkGetBufferDeviceAddressKHR
        {  424,   423 }, // vkGetBufferDeviceAddressEXT and vkGetBufferDeviceAddress
        {  424,   425 }, // vkGetBufferDeviceAddressEXT and vkGetBufferDeviceAddressKHR
        {  425,   423 }, // vkGetBufferDeviceAddressKHR and vkGetBufferDeviceAddress
        {  425,   424 }, // vkGetBufferDeviceAddressKHR and vkGetBufferDeviceAddressEXT
        {  427,   428 }, // vkGetBufferMemoryRequirements2 and vkGetBufferMemoryRequirements2KHR
        {  428,   427 }, // vkGetBufferMemoryRequirements2KHR and vkGetBufferMemoryRequirements2
        {  429,   430 }, // vkGetBufferOpaqueCaptureAddress and vkGetBufferOpaqueCaptureAddressKHR
        {  430,   429 }, // vkGetBufferOpaqueCaptureAddressKHR and vkGetBufferOpaqueCaptureAddress
        {  432,   433 }, // vkGetCalibratedTimestampsEXT and vkGetCalibratedTimestampsKHR
        {  433,   432 }, // vkGetCalibratedTimestampsKHR and vkGetCalibratedTimestampsEXT
        {  442,   443 }, // vkGetDescriptorSetLayoutSupport and vkGetDescriptorSetLayoutSupportKHR
        {  443,   442 }, // vkGetDescriptorSetLayoutSupportKHR and vkGetDescriptorSetLayoutSupport
        {  445,   446 }, // vkGetDeviceBufferMemoryRequirements and vkGetDeviceBufferMemoryRequirementsKHR
        {  446,   445 }, // vkGetDeviceBufferMemoryRequirementsKHR and vkGetDeviceBufferMemoryRequirements
        {  448,   449 }, // vkGetDeviceGroupPeerMemoryFeatures and vkGetDeviceGroupPeerMemoryFeaturesKHR
        {  449,   448 }, // vkGetDeviceGroupPeerMemoryFeaturesKHR and vkGetDeviceGroupPeerMemoryFeatures
#if defined(VK_USE_PLATFORM_WIN32_KHR)

#endif
        {  453,   454 }, // vkGetDeviceImageMemoryRequirements and vkGetDeviceImageMemoryRequirementsKHR
        {  454,   453 }, // vkGetDeviceImageMemoryRequirementsKHR and vkGetDeviceImageMemoryRequirements
        {  455,   456 }, // vkGetDeviceImageSparseMemoryRequirements and vkGetDeviceImageSparseMemoryRequirementsKHR
        {  456,   455 }, // vkGetDeviceImageSparseMemoryRequirementsKHR and vkGetDeviceImageSparseMemoryRequirements
        {  459,   460 }, // vkGetDeviceMemoryOpaqueCaptureAddress and vkGetDeviceMemoryOpaqueCaptureAddressKHR
        {  460,   459 }, // vkGetDeviceMemoryOpaqueCaptureAddressKHR and vkGetDeviceMemoryOpaqueCaptureAddress
#if defined(VK_ENABLE_BETA_EXTENSIONS)

#endif
#if defined(VK_ENABLE_BETA_EXTENSIONS)

#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)

#endif
        {  484,   485 }, // vkGetImageMemoryRequirements2 and vkGetImageMemoryRequirements2KHR
        {  485,   484 }, // vkGetImageMemoryRequirements2KHR and vkGetImageMemoryRequirements2
        {  488,   489 }, // vkGetImageSparseMemoryRequirements2 and vkGetImageSparseMemoryRequirements2KHR
        {  489,   488 }, // vkGetImageSparseMemoryRequirements2KHR and vkGetImageSparseMemoryRequirements2
        {  491,   492 }, // vkGetImageSubresourceLayout2EXT and vkGetImageSubresourceLayout2KHR
        {  492,   491 }, // vkGetImageSubresourceLayout2KHR and vkGetImageSubresourceLayout2EXT
#if defined(VK_USE_PLATFORM_ANDROID_KHR)

#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)

#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)

#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)

#endif
        {  511,   512 }, // vkGetPhysicalDeviceCalibrateableTimeDomainsEXT and vkGetPhysicalDeviceCalibrateableTimeDomainsKHR
        {  512,   511 }, // vkGetPhysicalDeviceCalibrateableTimeDomainsKHR and vkGetPhysicalDeviceCalibrateableTimeDomainsEXT
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)

#endif
        {  520,   521 }, // vkGetPhysicalDeviceExternalBufferProperties and vkGetPhysicalDeviceExternalBufferPropertiesKHR
        {  521,   520 }, // vkGetPhysicalDeviceExternalBufferPropertiesKHR and vkGetPhysicalDeviceExternalBufferProperties
        {  522,   523 }, // vkGetPhysicalDeviceExternalFenceProperties and vkGetPhysicalDeviceExternalFencePropertiesKHR
        {  523,   522 }, // vkGetPhysicalDeviceExternalFencePropertiesKHR and vkGetPhysicalDeviceExternalFenceProperties
        {  525,   526 }, // vkGetPhysicalDeviceExternalSemaphoreProperties and vkGetPhysicalDeviceExternalSemaphorePropertiesKHR
        {  526,   525 }, // vkGetPhysicalDeviceExternalSemaphorePropertiesKHR and vkGetPhysicalDeviceExternalSemaphoreProperties
        {  528,   529 }, // vkGetPhysicalDeviceFeatures2 and vkGetPhysicalDeviceFeatures2KHR
        {  529,   528 }, // vkGetPhysicalDeviceFeatures2KHR and vkGetPhysicalDeviceFeatures2
        {  531,   532 }, // vkGetPhysicalDeviceFormatProperties2 and vkGetPhysicalDeviceFormatProperties2KHR
        {  532,   531 }, // vkGetPhysicalDeviceFormatProperties2KHR and vkGetPhysicalDeviceFormatProperties2
        {  535,   536 }, // vkGetPhysicalDeviceImageFormatProperties2 and vkGetPhysicalDeviceImageFormatProperties2KHR
        {  536,   535 }, // vkGetPhysicalDeviceImageFormatProperties2KHR and vkGetPhysicalDeviceImageFormatProperties2
        {  538,   539 }, // vkGetPhysicalDeviceMemoryProperties2 and vkGetPhysicalDeviceMemoryProperties2KHR
        {  539,   538 }, // vkGetPhysicalDeviceMemoryProperties2KHR and vkGetPhysicalDeviceMemoryProperties2
        {  544,   545 }, // vkGetPhysicalDeviceProperties2 and vkGetPhysicalDeviceProperties2KHR
        {  545,   544 }, // vkGetPhysicalDeviceProperties2KHR and vkGetPhysicalDeviceProperties2
        {  548,   549 }, // vkGetPhysicalDeviceQueueFamilyProperties2 and vkGetPhysicalDeviceQueueFamilyProperties2KHR
        {  549,   548 }, // vkGetPhysicalDeviceQueueFamilyProperties2KHR and vkGetPhysicalDeviceQueueFamilyProperties2
#if defined(VK_USE_PLATFORM_SCREEN_QNX)

#endif
        {  552,   553 }, // vkGetPhysicalDeviceSparseImageFormatProperties2 and vkGetPhysicalDeviceSparseImageFormatProperties2KHR
        {  553,   552 }, // vkGetPhysicalDeviceSparseImageFormatProperties2KHR and vkGetPhysicalDeviceSparseImageFormatProperties2
#if defined(VK_USE_PLATFORM_WIN32_KHR)

#endif
        {  563,   564 }, // vkGetPhysicalDeviceToolProperties and vkGetPhysicalDeviceToolPropertiesEXT
        {  564,   563 }, // vkGetPhysicalDeviceToolPropertiesEXT and vkGetPhysicalDeviceToolProperties
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)

#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)

#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)

#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)

#endif
        {  579,   580 }, // vkGetPrivateData and vkGetPrivateDataEXT
        {  580,   579 }, // vkGetPrivateDataEXT and vkGetPrivateData
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)

#endif
        {  586,   587 }, // vkGetRayTracingShaderGroupHandlesKHR and vkGetRayTracingShaderGroupHandlesNV
        {  587,   586 }, // vkGetRayTracingShaderGroupHandlesNV and vkGetRayTracingShaderGroupHandlesKHR
#if defined(VK_USE_PLATFORM_SCREEN_QNX)

#endif
        {  594,   595 }, // vkGetSemaphoreCounterValue and vkGetSemaphoreCounterValueKHR
        {  595,   594 }, // vkGetSemaphoreCounterValueKHR and vkGetSemaphoreCounterValue
#if defined(VK_USE_PLATFORM_WIN32_KHR)

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)

#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)

#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)

#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)

#endif
        {  629,   630 }, // vkQueueSubmit2 and vkQueueSubmit2KHR
        {  630,   629 }, // vkQueueSubmit2KHR and vkQueueSubmit2
#if defined(VK_USE_PLATFORM_WIN32_KHR)

#endif
        {  644,   645 }, // vkResetQueryPool and vkResetQueryPoolEXT
        {  645,   644 }, // vkResetQueryPoolEXT and vkResetQueryPool
#if defined(VK_USE_PLATFORM_FUCHSIA)

#endif
#if defined(VK_USE_PLATFORM_FUCHSIA)

#endif
        {  656,   657 }, // vkSetPrivateData and vkSetPrivateDataEXT
        {  657,   656 }, // vkSetPrivateDataEXT and vkSetPrivateData
        {  658,   659 }, // vkSignalSemaphore and vkSignalSemaphoreKHR
        {  659,   658 }, // vkSignalSemaphoreKHR and vkSignalSemaphore
        {  662,   663 }, // vkTrimCommandPool and vkTrimCommandPoolKHR
        {  663,   662 }, // vkTrimCommandPoolKHR and vkTrimCommandPool
        {  667,   668 }, // vkUpdateDescriptorSetWithTemplate and vkUpdateDescriptorSetWithTemplateKHR
        {  668,   667 }, // vkUpdateDescriptorSetWithTemplateKHR and vkUpdateDescriptorSetWithTemplate
        {  673,   674 }, // vkWaitSemaphores and vkWaitSemaphoresKHR
        {  674,   673 }, // vkWaitSemaphoresKHR and vkWaitSemaphores
        { 0xFFFF, 0xFFFF }
    };

    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_aliases) - 1; ++i) {
        const GladAliasPair_t *pAlias = &s_aliases[i];
        if (context->pfnArray[pAlias->first] == NULL && context->pfnArray[pAlias->second] != NULL) {
            context->pfnArray[pAlias->first] = context->pfnArray[pAlias->second];
        }
    }
}

static int glad_vk_get_extensions(GladVulkanContext *context, VkPhysicalDevice physical_device, uint32_t *out_extension_count, char ***out_extensions) {
    uint32_t i;
    uint32_t instance_extension_count = 0;
    uint32_t device_extension_count = 0;
    uint32_t max_extension_count = 0;
    uint32_t total_extension_count = 0;
    char **extensions = NULL;
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

    extensions = (char**) calloc(total_extension_count, sizeof(char*));
    if (extensions == NULL) {
        goto glad_vk_get_extensions_error;
    }

    for (i = 0; i < instance_extension_count; ++i) {
        VkExtensionProperties ext = ext_properties[i];

        size_t extension_name_length = strlen(ext.extensionName) + 1;
        extensions[i] = (char*) malloc(extension_name_length * sizeof(char));
        if (extensions[i] == NULL) {
            goto glad_vk_get_extensions_error;
        }
        memcpy(extensions[i], ext.extensionName, extension_name_length * sizeof(char));
    }

    if (physical_device != NULL) {
        result = context->EnumerateDeviceExtensionProperties(physical_device, NULL, &device_extension_count, ext_properties);
        if (result != VK_SUCCESS) {
            goto glad_vk_get_extensions_error;
        }

        for (i = 0; i < device_extension_count; ++i) {
            VkExtensionProperties ext = ext_properties[i];

            size_t extension_name_length = strlen(ext.extensionName) + 1;
            extensions[instance_extension_count + i] = (char*) malloc(extension_name_length * sizeof(char));
            if (extensions[instance_extension_count + i] == NULL) {
                goto glad_vk_get_extensions_error;
            }
            memcpy(extensions[instance_extension_count + i], ext.extensionName, extension_name_length * sizeof(char));
        }
    }

    free((void*) ext_properties);

    *out_extension_count = total_extension_count;
    *out_extensions = extensions;

    return 1;

glad_vk_get_extensions_error:
    free((void*) ext_properties);
    if (extensions != NULL) {
        for (i = 0; i < total_extension_count; ++i) {
            free((void*) extensions[i]);
        }
        free(extensions);
    }
    return 0;
}

static void glad_vk_free_extensions(uint32_t extension_count, char **extensions) {
    uint32_t i;

    for(i = 0; i < extension_count ; ++i) {
        free((void*) (extensions[i]));
    }

    free((void*) extensions);
}

static int glad_vk_has_extension(const char *name, uint32_t extension_count, char **extensions) {
    uint32_t i;

    for (i = 0; i < extension_count; ++i) {
        if(extensions[i] != NULL && strcmp(name, extensions[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

static GLADapiproc glad_vk_get_proc_from_userptr(void *userptr, const char* name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_vk_find_extensions_vulkan(GladVulkanContext *context, VkPhysicalDevice physical_device) {
    uint32_t extension_count = 0;
    char **extensions = NULL;
    if (!glad_vk_get_extensions(context, physical_device, &extension_count, &extensions)) return 0;

    static uint16_t extIdx[] = {
             0, // VK_AMDX_shader_enqueue
             1, // VK_AMD_buffer_marker
             2, // VK_AMD_device_coherent_memory
             3, // VK_AMD_display_native_hdr
             4, // VK_AMD_draw_indirect_count
             5, // VK_AMD_gcn_shader
             6, // VK_AMD_gpu_shader_half_float
             7, // VK_AMD_gpu_shader_int16
             8, // VK_AMD_memory_overallocation_behavior
             9, // VK_AMD_mixed_attachment_samples
            10, // VK_AMD_negative_viewport_height
            11, // VK_AMD_pipeline_compiler_control
            12, // VK_AMD_rasterization_order
            13, // VK_AMD_shader_ballot
            14, // VK_AMD_shader_core_properties
            15, // VK_AMD_shader_core_properties2
            16, // VK_AMD_shader_early_and_late_fragment_tests
            17, // VK_AMD_shader_explicit_vertex_parameter
            18, // VK_AMD_shader_fragment_mask
            19, // VK_AMD_shader_image_load_store_lod
            20, // VK_AMD_shader_info
            21, // VK_AMD_shader_trinary_minmax
            22, // VK_AMD_texture_gather_bias_lod
            23, // VK_ANDROID_external_format_resolve
            24, // VK_ANDROID_external_memory_android_hardware_buffer
            25, // VK_ARM_rasterization_order_attachment_access
            26, // VK_ARM_render_pass_striped
            27, // VK_ARM_scheduling_controls
            28, // VK_ARM_shader_core_builtins
            29, // VK_ARM_shader_core_properties
            30, // VK_EXT_4444_formats
            31, // VK_EXT_acquire_drm_display
            32, // VK_EXT_acquire_xlib_display
            33, // VK_EXT_astc_decode_mode
            34, // VK_EXT_attachment_feedback_loop_dynamic_state
            35, // VK_EXT_attachment_feedback_loop_layout
            36, // VK_EXT_blend_operation_advanced
            37, // VK_EXT_border_color_swizzle
            38, // VK_EXT_buffer_device_address
            39, // VK_EXT_calibrated_timestamps
            40, // VK_EXT_color_write_enable
            41, // VK_EXT_conditional_rendering
            42, // VK_EXT_conservative_rasterization
            43, // VK_EXT_custom_border_color
            44, // VK_EXT_debug_marker
            45, // VK_EXT_debug_report
            46, // VK_EXT_debug_utils
            47, // VK_EXT_depth_bias_control
            48, // VK_EXT_depth_clamp_zero_one
            49, // VK_EXT_depth_clip_control
            50, // VK_EXT_depth_clip_enable
            51, // VK_EXT_depth_range_unrestricted
            52, // VK_EXT_descriptor_buffer
            53, // VK_EXT_descriptor_indexing
            54, // VK_EXT_device_address_binding_report
            55, // VK_EXT_device_fault
            56, // VK_EXT_device_memory_report
            57, // VK_EXT_direct_mode_display
            58, // VK_EXT_directfb_surface
            59, // VK_EXT_discard_rectangles
            60, // VK_EXT_display_control
            61, // VK_EXT_display_surface_counter
            62, // VK_EXT_dynamic_rendering_unused_attachments
            63, // VK_EXT_extended_dynamic_state
            64, // VK_EXT_extended_dynamic_state2
            65, // VK_EXT_extended_dynamic_state3
            66, // VK_EXT_external_memory_acquire_unmodified
            67, // VK_EXT_external_memory_dma_buf
            68, // VK_EXT_external_memory_host
            69, // VK_EXT_filter_cubic
            70, // VK_EXT_fragment_density_map
            71, // VK_EXT_fragment_density_map2
            72, // VK_EXT_fragment_shader_interlock
            73, // VK_EXT_frame_boundary
            74, // VK_EXT_full_screen_exclusive
            75, // VK_EXT_global_priority
            76, // VK_EXT_global_priority_query
            77, // VK_EXT_graphics_pipeline_library
            78, // VK_EXT_hdr_metadata
            79, // VK_EXT_headless_surface
            80, // VK_EXT_host_image_copy
            81, // VK_EXT_host_query_reset
            82, // VK_EXT_image_2d_view_of_3d
            83, // VK_EXT_image_compression_control
            84, // VK_EXT_image_compression_control_swapchain
            85, // VK_EXT_image_drm_format_modifier
            86, // VK_EXT_image_robustness
            87, // VK_EXT_image_sliced_view_of_3d
            88, // VK_EXT_image_view_min_lod
            89, // VK_EXT_index_type_uint8
            90, // VK_EXT_inline_uniform_block
            91, // VK_EXT_layer_settings
            92, // VK_EXT_legacy_dithering
            93, // VK_EXT_line_rasterization
            94, // VK_EXT_load_store_op_none
            95, // VK_EXT_memory_budget
            96, // VK_EXT_memory_priority
            97, // VK_EXT_mesh_shader
            98, // VK_EXT_metal_objects
            99, // VK_EXT_metal_surface
           100, // VK_EXT_multi_draw
           101, // VK_EXT_multisampled_render_to_single_sampled
           102, // VK_EXT_mutable_descriptor_type
           103, // VK_EXT_nested_command_buffer
           104, // VK_EXT_non_seamless_cube_map
           105, // VK_EXT_opacity_micromap
           106, // VK_EXT_pageable_device_local_memory
           107, // VK_EXT_pci_bus_info
           108, // VK_EXT_physical_device_drm
           109, // VK_EXT_pipeline_creation_cache_control
           110, // VK_EXT_pipeline_creation_feedback
           111, // VK_EXT_pipeline_library_group_handles
           112, // VK_EXT_pipeline_properties
           113, // VK_EXT_pipeline_protected_access
           114, // VK_EXT_pipeline_robustness
           115, // VK_EXT_post_depth_coverage
           116, // VK_EXT_primitive_topology_list_restart
           117, // VK_EXT_primitives_generated_query
           118, // VK_EXT_private_data
           119, // VK_EXT_provoking_vertex
           120, // VK_EXT_queue_family_foreign
           121, // VK_EXT_rasterization_order_attachment_access
           122, // VK_EXT_rgba10x6_formats
           123, // VK_EXT_robustness2
           124, // VK_EXT_sample_locations
           125, // VK_EXT_sampler_filter_minmax
           126, // VK_EXT_scalar_block_layout
           127, // VK_EXT_separate_stencil_usage
           128, // VK_EXT_shader_atomic_float
           129, // VK_EXT_shader_atomic_float2
           130, // VK_EXT_shader_demote_to_helper_invocation
           131, // VK_EXT_shader_image_atomic_int64
           132, // VK_EXT_shader_module_identifier
           133, // VK_EXT_shader_object
           134, // VK_EXT_shader_stencil_export
           135, // VK_EXT_shader_subgroup_ballot
           136, // VK_EXT_shader_subgroup_vote
           137, // VK_EXT_shader_tile_image
           138, // VK_EXT_shader_viewport_index_layer
           139, // VK_EXT_subgroup_size_control
           140, // VK_EXT_subpass_merge_feedback
           141, // VK_EXT_surface_maintenance1
           142, // VK_EXT_swapchain_colorspace
           143, // VK_EXT_swapchain_maintenance1
           144, // VK_EXT_texel_buffer_alignment
           145, // VK_EXT_texture_compression_astc_hdr
           146, // VK_EXT_tooling_info
           147, // VK_EXT_transform_feedback
           148, // VK_EXT_validation_cache
           149, // VK_EXT_validation_features
           150, // VK_EXT_validation_flags
           151, // VK_EXT_vertex_attribute_divisor
           152, // VK_EXT_vertex_input_dynamic_state
           153, // VK_EXT_ycbcr_2plane_444_formats
           154, // VK_EXT_ycbcr_image_arrays
           155, // VK_FUCHSIA_buffer_collection
           156, // VK_FUCHSIA_external_memory
           157, // VK_FUCHSIA_external_semaphore
           158, // VK_FUCHSIA_imagepipe_surface
           159, // VK_GGP_frame_token
           160, // VK_GGP_stream_descriptor_surface
           161, // VK_GOOGLE_decorate_string
           162, // VK_GOOGLE_display_timing
           163, // VK_GOOGLE_hlsl_functionality1
           164, // VK_GOOGLE_surfaceless_query
           165, // VK_GOOGLE_user_type
           166, // VK_HUAWEI_cluster_culling_shader
           167, // VK_HUAWEI_invocation_mask
           168, // VK_HUAWEI_subpass_shading
           169, // VK_IMG_filter_cubic
           170, // VK_IMG_format_pvrtc
           171, // VK_IMG_relaxed_line_rasterization
           172, // VK_INTEL_performance_query
           173, // VK_INTEL_shader_integer_functions2
           174, // VK_KHR_16bit_storage
           175, // VK_KHR_8bit_storage
           176, // VK_KHR_acceleration_structure
           177, // VK_KHR_android_surface
           178, // VK_KHR_bind_memory2
           179, // VK_KHR_buffer_device_address
           180, // VK_KHR_calibrated_timestamps
           181, // VK_KHR_cooperative_matrix
           182, // VK_KHR_copy_commands2
           183, // VK_KHR_create_renderpass2
           184, // VK_KHR_dedicated_allocation
           185, // VK_KHR_deferred_host_operations
           186, // VK_KHR_depth_stencil_resolve
           187, // VK_KHR_descriptor_update_template
           188, // VK_KHR_device_group
           189, // VK_KHR_device_group_creation
           190, // VK_KHR_display
           191, // VK_KHR_display_swapchain
           192, // VK_KHR_draw_indirect_count
           193, // VK_KHR_driver_properties
           194, // VK_KHR_dynamic_rendering
           195, // VK_KHR_external_fence
           196, // VK_KHR_external_fence_capabilities
           197, // VK_KHR_external_fence_fd
           198, // VK_KHR_external_fence_win32
           199, // VK_KHR_external_memory
           200, // VK_KHR_external_memory_capabilities
           201, // VK_KHR_external_memory_fd
           202, // VK_KHR_external_memory_win32
           203, // VK_KHR_external_semaphore
           204, // VK_KHR_external_semaphore_capabilities
           205, // VK_KHR_external_semaphore_fd
           206, // VK_KHR_external_semaphore_win32
           207, // VK_KHR_format_feature_flags2
           208, // VK_KHR_fragment_shader_barycentric
           209, // VK_KHR_fragment_shading_rate
           210, // VK_KHR_get_display_properties2
           211, // VK_KHR_get_memory_requirements2
           212, // VK_KHR_get_physical_device_properties2
           213, // VK_KHR_get_surface_capabilities2
           214, // VK_KHR_global_priority
           215, // VK_KHR_image_format_list
           216, // VK_KHR_imageless_framebuffer
           217, // VK_KHR_incremental_present
           218, // VK_KHR_maintenance1
           219, // VK_KHR_maintenance2
           220, // VK_KHR_maintenance3
           221, // VK_KHR_maintenance4
           222, // VK_KHR_maintenance5
           223, // VK_KHR_maintenance6
           224, // VK_KHR_map_memory2
           225, // VK_KHR_multiview
           226, // VK_KHR_performance_query
           227, // VK_KHR_pipeline_executable_properties
           228, // VK_KHR_pipeline_library
           229, // VK_KHR_portability_enumeration
           230, // VK_KHR_portability_subset
           231, // VK_KHR_present_id
           232, // VK_KHR_present_wait
           233, // VK_KHR_push_descriptor
           234, // VK_KHR_ray_query
           235, // VK_KHR_ray_tracing_maintenance1
           236, // VK_KHR_ray_tracing_pipeline
           237, // VK_KHR_ray_tracing_position_fetch
           238, // VK_KHR_relaxed_block_layout
           239, // VK_KHR_sampler_mirror_clamp_to_edge
           240, // VK_KHR_sampler_ycbcr_conversion
           241, // VK_KHR_separate_depth_stencil_layouts
           242, // VK_KHR_shader_atomic_int64
           243, // VK_KHR_shader_clock
           244, // VK_KHR_shader_draw_parameters
           245, // VK_KHR_shader_float16_int8
           246, // VK_KHR_shader_float_controls
           247, // VK_KHR_shader_integer_dot_product
           248, // VK_KHR_shader_non_semantic_info
           249, // VK_KHR_shader_subgroup_extended_types
           250, // VK_KHR_shader_subgroup_uniform_control_flow
           251, // VK_KHR_shader_terminate_invocation
           252, // VK_KHR_shared_presentable_image
           253, // VK_KHR_spirv_1_4
           254, // VK_KHR_storage_buffer_storage_class
           255, // VK_KHR_surface
           256, // VK_KHR_surface_protected_capabilities
           257, // VK_KHR_swapchain
           258, // VK_KHR_swapchain_mutable_format
           259, // VK_KHR_synchronization2
           260, // VK_KHR_timeline_semaphore
           261, // VK_KHR_uniform_buffer_standard_layout
           262, // VK_KHR_variable_pointers
           263, // VK_KHR_vertex_attribute_divisor
           264, // VK_KHR_video_decode_h264
           265, // VK_KHR_video_decode_h265
           266, // VK_KHR_video_decode_queue
           267, // VK_KHR_video_encode_h264
           268, // VK_KHR_video_encode_h265
           269, // VK_KHR_video_encode_queue
           270, // VK_KHR_video_maintenance1
           271, // VK_KHR_video_queue
           272, // VK_KHR_vulkan_memory_model
           273, // VK_KHR_wayland_surface
           274, // VK_KHR_win32_keyed_mutex
           275, // VK_KHR_win32_surface
           276, // VK_KHR_workgroup_memory_explicit_layout
           277, // VK_KHR_xcb_surface
           278, // VK_KHR_xlib_surface
           279, // VK_KHR_zero_initialize_workgroup_memory
           280, // VK_LUNARG_direct_driver_loading
           281, // VK_MSFT_layered_driver
           282, // VK_MVK_ios_surface
           283, // VK_MVK_macos_surface
           284, // VK_NN_vi_surface
           285, // VK_NVX_binary_import
           286, // VK_NVX_image_view_handle
           287, // VK_NVX_multiview_per_view_attributes
           288, // VK_NV_acquire_winrt_display
           289, // VK_NV_clip_space_w_scaling
           290, // VK_NV_compute_shader_derivatives
           291, // VK_NV_cooperative_matrix
           292, // VK_NV_copy_memory_indirect
           293, // VK_NV_corner_sampled_image
           294, // VK_NV_coverage_reduction_mode
           295, // VK_NV_cuda_kernel_launch
           296, // VK_NV_dedicated_allocation
           297, // VK_NV_dedicated_allocation_image_aliasing
           298, // VK_NV_descriptor_pool_overallocation
           299, // VK_NV_device_diagnostic_checkpoints
           300, // VK_NV_device_diagnostics_config
           301, // VK_NV_device_generated_commands
           302, // VK_NV_device_generated_commands_compute
           303, // VK_NV_displacement_micromap
           304, // VK_NV_extended_sparse_address_space
           305, // VK_NV_external_memory
           306, // VK_NV_external_memory_capabilities
           307, // VK_NV_external_memory_rdma
           308, // VK_NV_external_memory_win32
           309, // VK_NV_fill_rectangle
           310, // VK_NV_fragment_coverage_to_color
           311, // VK_NV_fragment_shader_barycentric
           312, // VK_NV_fragment_shading_rate_enums
           313, // VK_NV_framebuffer_mixed_samples
           314, // VK_NV_geometry_shader_passthrough
           315, // VK_NV_glsl_shader
           316, // VK_NV_inherited_viewport_scissor
           317, // VK_NV_linear_color_attachment
           318, // VK_NV_low_latency
           319, // VK_NV_low_latency2
           320, // VK_NV_memory_decompression
           321, // VK_NV_mesh_shader
           322, // VK_NV_optical_flow
           323, // VK_NV_per_stage_descriptor_set
           324, // VK_NV_present_barrier
           325, // VK_NV_ray_tracing
           326, // VK_NV_ray_tracing_invocation_reorder
           327, // VK_NV_ray_tracing_motion_blur
           328, // VK_NV_representative_fragment_test
           329, // VK_NV_sample_mask_override_coverage
           330, // VK_NV_scissor_exclusive
           331, // VK_NV_shader_image_footprint
           332, // VK_NV_shader_sm_builtins
           333, // VK_NV_shader_subgroup_partitioned
           334, // VK_NV_shading_rate_image
           335, // VK_NV_viewport_array2
           336, // VK_NV_viewport_swizzle
           337, // VK_NV_win32_keyed_mutex
           338, // VK_QCOM_filter_cubic_clamp
           339, // VK_QCOM_filter_cubic_weights
           340, // VK_QCOM_fragment_density_map_offset
           341, // VK_QCOM_image_processing
           342, // VK_QCOM_image_processing2
           343, // VK_QCOM_multiview_per_view_render_areas
           344, // VK_QCOM_multiview_per_view_viewports
           345, // VK_QCOM_render_pass_shader_resolve
           346, // VK_QCOM_render_pass_store_ops
           347, // VK_QCOM_render_pass_transform
           348, // VK_QCOM_rotated_copy_commands
           349, // VK_QCOM_tile_properties
           350, // VK_QCOM_ycbcr_degamma
           351, // VK_QNX_external_memory_screen_buffer
           352, // VK_QNX_screen_surface
           353, // VK_SEC_amigo_profiling
           354, // VK_VALVE_descriptor_set_host_mapping
           355, // VK_VALVE_mutable_descriptor_type
        0xFFFF
    };

    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(extIdx) - 1; ++i)
        context->extArray[extIdx[i]] = glad_vk_has_extension(glad_ext_names[extIdx[i]], extension_count, extensions);

    GLAD_UNUSED(glad_vk_has_extension);

    glad_vk_free_extensions(extension_count, extensions);

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

int gladLoadVulkanContextUserPtr(GladVulkanContext *context, VkPhysicalDevice physical_device, GLADuserptrloadfunc load, void *userptr) {
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
    glad_vk_load_VK_KHR_maintenance1(context, load, userptr);
    glad_vk_load_VK_KHR_maintenance3(context, load, userptr);
    glad_vk_load_VK_KHR_maintenance4(context, load, userptr);
    glad_vk_load_VK_KHR_maintenance5(context, load, userptr);
    glad_vk_load_VK_KHR_maintenance6(context, load, userptr);
    glad_vk_load_VK_KHR_map_memory2(context, load, userptr);
    glad_vk_load_VK_KHR_performance_query(context, load, userptr);
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


static const char* DEVICE_FUNCTIONS[] = {
    "vkAcquireFullScreenExclusiveModeEXT",
    "vkAcquireNextImage2KHR",
    "vkAcquireNextImageKHR",
    "vkAcquirePerformanceConfigurationINTEL",
    "vkAcquireProfilingLockKHR",
    "vkAllocateCommandBuffers",
    "vkAllocateDescriptorSets",
    "vkAllocateMemory",
    "vkBeginCommandBuffer",
    "vkBindAccelerationStructureMemoryNV",
    "vkBindBufferMemory",
    "vkBindBufferMemory2",
    "vkBindBufferMemory2KHR",
    "vkBindImageMemory",
    "vkBindImageMemory2",
    "vkBindImageMemory2KHR",
    "vkBindOpticalFlowSessionImageNV",
    "vkBindVideoSessionMemoryKHR",
    "vkBuildAccelerationStructuresKHR",
    "vkBuildMicromapsEXT",
    "vkCmdBeginConditionalRenderingEXT",
    "vkCmdBeginDebugUtilsLabelEXT",
    "vkCmdBeginQuery",
    "vkCmdBeginQueryIndexedEXT",
    "vkCmdBeginRenderPass",
    "vkCmdBeginRenderPass2",
    "vkCmdBeginRenderPass2KHR",
    "vkCmdBeginRendering",
    "vkCmdBeginRenderingKHR",
    "vkCmdBeginTransformFeedbackEXT",
    "vkCmdBeginVideoCodingKHR",
    "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT",
    "vkCmdBindDescriptorBufferEmbeddedSamplersEXT",
    "vkCmdBindDescriptorBuffersEXT",
    "vkCmdBindDescriptorSets",
    "vkCmdBindDescriptorSets2KHR",
    "vkCmdBindIndexBuffer",
    "vkCmdBindIndexBuffer2KHR",
    "vkCmdBindInvocationMaskHUAWEI",
    "vkCmdBindPipeline",
    "vkCmdBindPipelineShaderGroupNV",
    "vkCmdBindShadersEXT",
    "vkCmdBindShadingRateImageNV",
    "vkCmdBindTransformFeedbackBuffersEXT",
    "vkCmdBindVertexBuffers",
    "vkCmdBindVertexBuffers2",
    "vkCmdBindVertexBuffers2EXT",
    "vkCmdBlitImage",
    "vkCmdBlitImage2",
    "vkCmdBlitImage2KHR",
    "vkCmdBuildAccelerationStructureNV",
    "vkCmdBuildAccelerationStructuresIndirectKHR",
    "vkCmdBuildAccelerationStructuresKHR",
    "vkCmdBuildMicromapsEXT",
    "vkCmdClearAttachments",
    "vkCmdClearColorImage",
    "vkCmdClearDepthStencilImage",
    "vkCmdControlVideoCodingKHR",
    "vkCmdCopyAccelerationStructureKHR",
    "vkCmdCopyAccelerationStructureNV",
    "vkCmdCopyAccelerationStructureToMemoryKHR",
    "vkCmdCopyBuffer",
    "vkCmdCopyBuffer2",
    "vkCmdCopyBuffer2KHR",
    "vkCmdCopyBufferToImage",
    "vkCmdCopyBufferToImage2",
    "vkCmdCopyBufferToImage2KHR",
    "vkCmdCopyImage",
    "vkCmdCopyImage2",
    "vkCmdCopyImage2KHR",
    "vkCmdCopyImageToBuffer",
    "vkCmdCopyImageToBuffer2",
    "vkCmdCopyImageToBuffer2KHR",
    "vkCmdCopyMemoryIndirectNV",
    "vkCmdCopyMemoryToAccelerationStructureKHR",
    "vkCmdCopyMemoryToImageIndirectNV",
    "vkCmdCopyMemoryToMicromapEXT",
    "vkCmdCopyMicromapEXT",
    "vkCmdCopyMicromapToMemoryEXT",
    "vkCmdCopyQueryPoolResults",
    "vkCmdCuLaunchKernelNVX",
    "vkCmdCudaLaunchKernelNV",
    "vkCmdDebugMarkerBeginEXT",
    "vkCmdDebugMarkerEndEXT",
    "vkCmdDebugMarkerInsertEXT",
    "vkCmdDecodeVideoKHR",
    "vkCmdDecompressMemoryIndirectCountNV",
    "vkCmdDecompressMemoryNV",
    "vkCmdDispatch",
    "vkCmdDispatchBase",
    "vkCmdDispatchBaseKHR",
    "vkCmdDispatchGraphAMDX",
    "vkCmdDispatchGraphIndirectAMDX",
    "vkCmdDispatchGraphIndirectCountAMDX",
    "vkCmdDispatchIndirect",
    "vkCmdDraw",
    "vkCmdDrawClusterHUAWEI",
    "vkCmdDrawClusterIndirectHUAWEI",
    "vkCmdDrawIndexed",
    "vkCmdDrawIndexedIndirect",
    "vkCmdDrawIndexedIndirectCount",
    "vkCmdDrawIndexedIndirectCountAMD",
    "vkCmdDrawIndexedIndirectCountKHR",
    "vkCmdDrawIndirect",
    "vkCmdDrawIndirectByteCountEXT",
    "vkCmdDrawIndirectCount",
    "vkCmdDrawIndirectCountAMD",
    "vkCmdDrawIndirectCountKHR",
    "vkCmdDrawMeshTasksEXT",
    "vkCmdDrawMeshTasksIndirectCountEXT",
    "vkCmdDrawMeshTasksIndirectCountNV",
    "vkCmdDrawMeshTasksIndirectEXT",
    "vkCmdDrawMeshTasksIndirectNV",
    "vkCmdDrawMeshTasksNV",
    "vkCmdDrawMultiEXT",
    "vkCmdDrawMultiIndexedEXT",
    "vkCmdEncodeVideoKHR",
    "vkCmdEndConditionalRenderingEXT",
    "vkCmdEndDebugUtilsLabelEXT",
    "vkCmdEndQuery",
    "vkCmdEndQueryIndexedEXT",
    "vkCmdEndRenderPass",
    "vkCmdEndRenderPass2",
    "vkCmdEndRenderPass2KHR",
    "vkCmdEndRendering",
    "vkCmdEndRenderingKHR",
    "vkCmdEndTransformFeedbackEXT",
    "vkCmdEndVideoCodingKHR",
    "vkCmdExecuteCommands",
    "vkCmdExecuteGeneratedCommandsNV",
    "vkCmdFillBuffer",
    "vkCmdInitializeGraphScratchMemoryAMDX",
    "vkCmdInsertDebugUtilsLabelEXT",
    "vkCmdNextSubpass",
    "vkCmdNextSubpass2",
    "vkCmdNextSubpass2KHR",
    "vkCmdOpticalFlowExecuteNV",
    "vkCmdPipelineBarrier",
    "vkCmdPipelineBarrier2",
    "vkCmdPipelineBarrier2KHR",
    "vkCmdPreprocessGeneratedCommandsNV",
    "vkCmdPushConstants",
    "vkCmdPushConstants2KHR",
    "vkCmdPushDescriptorSet2KHR",
    "vkCmdPushDescriptorSetKHR",
    "vkCmdPushDescriptorSetWithTemplate2KHR",
    "vkCmdPushDescriptorSetWithTemplateKHR",
    "vkCmdResetEvent",
    "vkCmdResetEvent2",
    "vkCmdResetEvent2KHR",
    "vkCmdResetQueryPool",
    "vkCmdResolveImage",
    "vkCmdResolveImage2",
    "vkCmdResolveImage2KHR",
    "vkCmdSetAlphaToCoverageEnableEXT",
    "vkCmdSetAlphaToOneEnableEXT",
    "vkCmdSetAttachmentFeedbackLoopEnableEXT",
    "vkCmdSetBlendConstants",
    "vkCmdSetCheckpointNV",
    "vkCmdSetCoarseSampleOrderNV",
    "vkCmdSetColorBlendAdvancedEXT",
    "vkCmdSetColorBlendEnableEXT",
    "vkCmdSetColorBlendEquationEXT",
    "vkCmdSetColorWriteEnableEXT",
    "vkCmdSetColorWriteMaskEXT",
    "vkCmdSetConservativeRasterizationModeEXT",
    "vkCmdSetCoverageModulationModeNV",
    "vkCmdSetCoverageModulationTableEnableNV",
    "vkCmdSetCoverageModulationTableNV",
    "vkCmdSetCoverageReductionModeNV",
    "vkCmdSetCoverageToColorEnableNV",
    "vkCmdSetCoverageToColorLocationNV",
    "vkCmdSetCullMode",
    "vkCmdSetCullModeEXT",
    "vkCmdSetDepthBias",
    "vkCmdSetDepthBias2EXT",
    "vkCmdSetDepthBiasEnable",
    "vkCmdSetDepthBiasEnableEXT",
    "vkCmdSetDepthBounds",
    "vkCmdSetDepthBoundsTestEnable",
    "vkCmdSetDepthBoundsTestEnableEXT",
    "vkCmdSetDepthClampEnableEXT",
    "vkCmdSetDepthClipEnableEXT",
    "vkCmdSetDepthClipNegativeOneToOneEXT",
    "vkCmdSetDepthCompareOp",
    "vkCmdSetDepthCompareOpEXT",
    "vkCmdSetDepthTestEnable",
    "vkCmdSetDepthTestEnableEXT",
    "vkCmdSetDepthWriteEnable",
    "vkCmdSetDepthWriteEnableEXT",
    "vkCmdSetDescriptorBufferOffsets2EXT",
    "vkCmdSetDescriptorBufferOffsetsEXT",
    "vkCmdSetDeviceMask",
    "vkCmdSetDeviceMaskKHR",
    "vkCmdSetDiscardRectangleEXT",
    "vkCmdSetDiscardRectangleEnableEXT",
    "vkCmdSetDiscardRectangleModeEXT",
    "vkCmdSetEvent",
    "vkCmdSetEvent2",
    "vkCmdSetEvent2KHR",
    "vkCmdSetExclusiveScissorEnableNV",
    "vkCmdSetExclusiveScissorNV",
    "vkCmdSetExtraPrimitiveOverestimationSizeEXT",
    "vkCmdSetFragmentShadingRateEnumNV",
    "vkCmdSetFragmentShadingRateKHR",
    "vkCmdSetFrontFace",
    "vkCmdSetFrontFaceEXT",
    "vkCmdSetLineRasterizationModeEXT",
    "vkCmdSetLineStippleEXT",
    "vkCmdSetLineStippleEnableEXT",
    "vkCmdSetLineWidth",
    "vkCmdSetLogicOpEXT",
    "vkCmdSetLogicOpEnableEXT",
    "vkCmdSetPatchControlPointsEXT",
    "vkCmdSetPerformanceMarkerINTEL",
    "vkCmdSetPerformanceOverrideINTEL",
    "vkCmdSetPerformanceStreamMarkerINTEL",
    "vkCmdSetPolygonModeEXT",
    "vkCmdSetPrimitiveRestartEnable",
    "vkCmdSetPrimitiveRestartEnableEXT",
    "vkCmdSetPrimitiveTopology",
    "vkCmdSetPrimitiveTopologyEXT",
    "vkCmdSetProvokingVertexModeEXT",
    "vkCmdSetRasterizationSamplesEXT",
    "vkCmdSetRasterizationStreamEXT",
    "vkCmdSetRasterizerDiscardEnable",
    "vkCmdSetRasterizerDiscardEnableEXT",
    "vkCmdSetRayTracingPipelineStackSizeKHR",
    "vkCmdSetRepresentativeFragmentTestEnableNV",
    "vkCmdSetSampleLocationsEXT",
    "vkCmdSetSampleLocationsEnableEXT",
    "vkCmdSetSampleMaskEXT",
    "vkCmdSetScissor",
    "vkCmdSetScissorWithCount",
    "vkCmdSetScissorWithCountEXT",
    "vkCmdSetShadingRateImageEnableNV",
    "vkCmdSetStencilCompareMask",
    "vkCmdSetStencilOp",
    "vkCmdSetStencilOpEXT",
    "vkCmdSetStencilReference",
    "vkCmdSetStencilTestEnable",
    "vkCmdSetStencilTestEnableEXT",
    "vkCmdSetStencilWriteMask",
    "vkCmdSetTessellationDomainOriginEXT",
    "vkCmdSetVertexInputEXT",
    "vkCmdSetViewport",
    "vkCmdSetViewportShadingRatePaletteNV",
    "vkCmdSetViewportSwizzleNV",
    "vkCmdSetViewportWScalingEnableNV",
    "vkCmdSetViewportWScalingNV",
    "vkCmdSetViewportWithCount",
    "vkCmdSetViewportWithCountEXT",
    "vkCmdSubpassShadingHUAWEI",
    "vkCmdTraceRaysIndirect2KHR",
    "vkCmdTraceRaysIndirectKHR",
    "vkCmdTraceRaysKHR",
    "vkCmdTraceRaysNV",
    "vkCmdUpdateBuffer",
    "vkCmdUpdatePipelineIndirectBufferNV",
    "vkCmdWaitEvents",
    "vkCmdWaitEvents2",
    "vkCmdWaitEvents2KHR",
    "vkCmdWriteAccelerationStructuresPropertiesKHR",
    "vkCmdWriteAccelerationStructuresPropertiesNV",
    "vkCmdWriteBufferMarker2AMD",
    "vkCmdWriteBufferMarkerAMD",
    "vkCmdWriteMicromapsPropertiesEXT",
    "vkCmdWriteTimestamp",
    "vkCmdWriteTimestamp2",
    "vkCmdWriteTimestamp2KHR",
    "vkCompileDeferredNV",
    "vkCopyAccelerationStructureKHR",
    "vkCopyAccelerationStructureToMemoryKHR",
    "vkCopyImageToImageEXT",
    "vkCopyImageToMemoryEXT",
    "vkCopyMemoryToAccelerationStructureKHR",
    "vkCopyMemoryToImageEXT",
    "vkCopyMemoryToMicromapEXT",
    "vkCopyMicromapEXT",
    "vkCopyMicromapToMemoryEXT",
    "vkCreateAccelerationStructureKHR",
    "vkCreateAccelerationStructureNV",
    "vkCreateBuffer",
    "vkCreateBufferCollectionFUCHSIA",
    "vkCreateBufferView",
    "vkCreateCommandPool",
    "vkCreateComputePipelines",
    "vkCreateCuFunctionNVX",
    "vkCreateCuModuleNVX",
    "vkCreateCudaFunctionNV",
    "vkCreateCudaModuleNV",
    "vkCreateDeferredOperationKHR",
    "vkCreateDescriptorPool",
    "vkCreateDescriptorSetLayout",
    "vkCreateDescriptorUpdateTemplate",
    "vkCreateDescriptorUpdateTemplateKHR",
    "vkCreateEvent",
    "vkCreateExecutionGraphPipelinesAMDX",
    "vkCreateFence",
    "vkCreateFramebuffer",
    "vkCreateGraphicsPipelines",
    "vkCreateImage",
    "vkCreateImageView",
    "vkCreateIndirectCommandsLayoutNV",
    "vkCreateMicromapEXT",
    "vkCreateOpticalFlowSessionNV",
    "vkCreatePipelineCache",
    "vkCreatePipelineLayout",
    "vkCreatePrivateDataSlot",
    "vkCreatePrivateDataSlotEXT",
    "vkCreateQueryPool",
    "vkCreateRayTracingPipelinesKHR",
    "vkCreateRayTracingPipelinesNV",
    "vkCreateRenderPass",
    "vkCreateRenderPass2",
    "vkCreateRenderPass2KHR",
    "vkCreateSampler",
    "vkCreateSamplerYcbcrConversion",
    "vkCreateSamplerYcbcrConversionKHR",
    "vkCreateSemaphore",
    "vkCreateShaderModule",
    "vkCreateShadersEXT",
    "vkCreateSharedSwapchainsKHR",
    "vkCreateSwapchainKHR",
    "vkCreateValidationCacheEXT",
    "vkCreateVideoSessionKHR",
    "vkCreateVideoSessionParametersKHR",
    "vkDebugMarkerSetObjectNameEXT",
    "vkDebugMarkerSetObjectTagEXT",
    "vkDeferredOperationJoinKHR",
    "vkDestroyAccelerationStructureKHR",
    "vkDestroyAccelerationStructureNV",
    "vkDestroyBuffer",
    "vkDestroyBufferCollectionFUCHSIA",
    "vkDestroyBufferView",
    "vkDestroyCommandPool",
    "vkDestroyCuFunctionNVX",
    "vkDestroyCuModuleNVX",
    "vkDestroyCudaFunctionNV",
    "vkDestroyCudaModuleNV",
    "vkDestroyDeferredOperationKHR",
    "vkDestroyDescriptorPool",
    "vkDestroyDescriptorSetLayout",
    "vkDestroyDescriptorUpdateTemplate",
    "vkDestroyDescriptorUpdateTemplateKHR",
    "vkDestroyDevice",
    "vkDestroyEvent",
    "vkDestroyFence",
    "vkDestroyFramebuffer",
    "vkDestroyImage",
    "vkDestroyImageView",
    "vkDestroyIndirectCommandsLayoutNV",
    "vkDestroyMicromapEXT",
    "vkDestroyOpticalFlowSessionNV",
    "vkDestroyPipeline",
    "vkDestroyPipelineCache",
    "vkDestroyPipelineLayout",
    "vkDestroyPrivateDataSlot",
    "vkDestroyPrivateDataSlotEXT",
    "vkDestroyQueryPool",
    "vkDestroyRenderPass",
    "vkDestroySampler",
    "vkDestroySamplerYcbcrConversion",
    "vkDestroySamplerYcbcrConversionKHR",
    "vkDestroySemaphore",
    "vkDestroyShaderEXT",
    "vkDestroyShaderModule",
    "vkDestroySwapchainKHR",
    "vkDestroyValidationCacheEXT",
    "vkDestroyVideoSessionKHR",
    "vkDestroyVideoSessionParametersKHR",
    "vkDeviceWaitIdle",
    "vkDisplayPowerControlEXT",
    "vkEndCommandBuffer",
    "vkExportMetalObjectsEXT",
    "vkFlushMappedMemoryRanges",
    "vkFreeCommandBuffers",
    "vkFreeDescriptorSets",
    "vkFreeMemory",
    "vkGetAccelerationStructureBuildSizesKHR",
    "vkGetAccelerationStructureDeviceAddressKHR",
    "vkGetAccelerationStructureHandleNV",
    "vkGetAccelerationStructureMemoryRequirementsNV",
    "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT",
    "vkGetAndroidHardwareBufferPropertiesANDROID",
    "vkGetBufferCollectionPropertiesFUCHSIA",
    "vkGetBufferDeviceAddress",
    "vkGetBufferDeviceAddressEXT",
    "vkGetBufferDeviceAddressKHR",
    "vkGetBufferMemoryRequirements",
    "vkGetBufferMemoryRequirements2",
    "vkGetBufferMemoryRequirements2KHR",
    "vkGetBufferOpaqueCaptureAddress",
    "vkGetBufferOpaqueCaptureAddressKHR",
    "vkGetBufferOpaqueCaptureDescriptorDataEXT",
    "vkGetCalibratedTimestampsEXT",
    "vkGetCalibratedTimestampsKHR",
    "vkGetCudaModuleCacheNV",
    "vkGetDeferredOperationMaxConcurrencyKHR",
    "vkGetDeferredOperationResultKHR",
    "vkGetDescriptorEXT",
    "vkGetDescriptorSetHostMappingVALVE",
    "vkGetDescriptorSetLayoutBindingOffsetEXT",
    "vkGetDescriptorSetLayoutHostMappingInfoVALVE",
    "vkGetDescriptorSetLayoutSizeEXT",
    "vkGetDescriptorSetLayoutSupport",
    "vkGetDescriptorSetLayoutSupportKHR",
    "vkGetDeviceAccelerationStructureCompatibilityKHR",
    "vkGetDeviceBufferMemoryRequirements",
    "vkGetDeviceBufferMemoryRequirementsKHR",
    "vkGetDeviceFaultInfoEXT",
    "vkGetDeviceGroupPeerMemoryFeatures",
    "vkGetDeviceGroupPeerMemoryFeaturesKHR",
    "vkGetDeviceGroupPresentCapabilitiesKHR",
    "vkGetDeviceGroupSurfacePresentModes2EXT",
    "vkGetDeviceGroupSurfacePresentModesKHR",
    "vkGetDeviceImageMemoryRequirements",
    "vkGetDeviceImageMemoryRequirementsKHR",
    "vkGetDeviceImageSparseMemoryRequirements",
    "vkGetDeviceImageSparseMemoryRequirementsKHR",
    "vkGetDeviceImageSubresourceLayoutKHR",
    "vkGetDeviceMemoryCommitment",
    "vkGetDeviceMemoryOpaqueCaptureAddress",
    "vkGetDeviceMemoryOpaqueCaptureAddressKHR",
    "vkGetDeviceMicromapCompatibilityEXT",
    "vkGetDeviceProcAddr",
    "vkGetDeviceQueue",
    "vkGetDeviceQueue2",
    "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI",
    "vkGetDynamicRenderingTilePropertiesQCOM",
    "vkGetEncodedVideoSessionParametersKHR",
    "vkGetEventStatus",
    "vkGetExecutionGraphPipelineNodeIndexAMDX",
    "vkGetExecutionGraphPipelineScratchSizeAMDX",
    "vkGetFenceFdKHR",
    "vkGetFenceStatus",
    "vkGetFenceWin32HandleKHR",
    "vkGetFramebufferTilePropertiesQCOM",
    "vkGetGeneratedCommandsMemoryRequirementsNV",
    "vkGetImageDrmFormatModifierPropertiesEXT",
    "vkGetImageMemoryRequirements",
    "vkGetImageMemoryRequirements2",
    "vkGetImageMemoryRequirements2KHR",
    "vkGetImageOpaqueCaptureDescriptorDataEXT",
    "vkGetImageSparseMemoryRequirements",
    "vkGetImageSparseMemoryRequirements2",
    "vkGetImageSparseMemoryRequirements2KHR",
    "vkGetImageSubresourceLayout",
    "vkGetImageSubresourceLayout2EXT",
    "vkGetImageSubresourceLayout2KHR",
    "vkGetImageViewAddressNVX",
    "vkGetImageViewHandleNVX",
    "vkGetImageViewOpaqueCaptureDescriptorDataEXT",
    "vkGetLatencyTimingsNV",
    "vkGetMemoryAndroidHardwareBufferANDROID",
    "vkGetMemoryFdKHR",
    "vkGetMemoryFdPropertiesKHR",
    "vkGetMemoryHostPointerPropertiesEXT",
    "vkGetMemoryRemoteAddressNV",
    "vkGetMemoryWin32HandleKHR",
    "vkGetMemoryWin32HandleNV",
    "vkGetMemoryWin32HandlePropertiesKHR",
    "vkGetMemoryZirconHandleFUCHSIA",
    "vkGetMemoryZirconHandlePropertiesFUCHSIA",
    "vkGetMicromapBuildSizesEXT",
    "vkGetPastPresentationTimingGOOGLE",
    "vkGetPerformanceParameterINTEL",
    "vkGetPipelineCacheData",
    "vkGetPipelineExecutableInternalRepresentationsKHR",
    "vkGetPipelineExecutablePropertiesKHR",
    "vkGetPipelineExecutableStatisticsKHR",
    "vkGetPipelineIndirectDeviceAddressNV",
    "vkGetPipelineIndirectMemoryRequirementsNV",
    "vkGetPipelinePropertiesEXT",
    "vkGetPrivateData",
    "vkGetPrivateDataEXT",
    "vkGetQueryPoolResults",
    "vkGetQueueCheckpointData2NV",
    "vkGetQueueCheckpointDataNV",
    "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR",
    "vkGetRayTracingShaderGroupHandlesKHR",
    "vkGetRayTracingShaderGroupHandlesNV",
    "vkGetRayTracingShaderGroupStackSizeKHR",
    "vkGetRefreshCycleDurationGOOGLE",
    "vkGetRenderAreaGranularity",
    "vkGetRenderingAreaGranularityKHR",
    "vkGetSamplerOpaqueCaptureDescriptorDataEXT",
    "vkGetScreenBufferPropertiesQNX",
    "vkGetSemaphoreCounterValue",
    "vkGetSemaphoreCounterValueKHR",
    "vkGetSemaphoreFdKHR",
    "vkGetSemaphoreWin32HandleKHR",
    "vkGetSemaphoreZirconHandleFUCHSIA",
    "vkGetShaderBinaryDataEXT",
    "vkGetShaderInfoAMD",
    "vkGetShaderModuleCreateInfoIdentifierEXT",
    "vkGetShaderModuleIdentifierEXT",
    "vkGetSwapchainCounterEXT",
    "vkGetSwapchainImagesKHR",
    "vkGetSwapchainStatusKHR",
    "vkGetValidationCacheDataEXT",
    "vkGetVideoSessionMemoryRequirementsKHR",
    "vkImportFenceFdKHR",
    "vkImportFenceWin32HandleKHR",
    "vkImportSemaphoreFdKHR",
    "vkImportSemaphoreWin32HandleKHR",
    "vkImportSemaphoreZirconHandleFUCHSIA",
    "vkInitializePerformanceApiINTEL",
    "vkInvalidateMappedMemoryRanges",
    "vkLatencySleepNV",
    "vkMapMemory",
    "vkMapMemory2KHR",
    "vkMergePipelineCaches",
    "vkMergeValidationCachesEXT",
    "vkQueueBeginDebugUtilsLabelEXT",
    "vkQueueBindSparse",
    "vkQueueEndDebugUtilsLabelEXT",
    "vkQueueInsertDebugUtilsLabelEXT",
    "vkQueueNotifyOutOfBandNV",
    "vkQueuePresentKHR",
    "vkQueueSetPerformanceConfigurationINTEL",
    "vkQueueSubmit",
    "vkQueueSubmit2",
    "vkQueueSubmit2KHR",
    "vkQueueWaitIdle",
    "vkRegisterDeviceEventEXT",
    "vkRegisterDisplayEventEXT",
    "vkReleaseFullScreenExclusiveModeEXT",
    "vkReleasePerformanceConfigurationINTEL",
    "vkReleaseProfilingLockKHR",
    "vkReleaseSwapchainImagesEXT",
    "vkResetCommandBuffer",
    "vkResetCommandPool",
    "vkResetDescriptorPool",
    "vkResetEvent",
    "vkResetFences",
    "vkResetQueryPool",
    "vkResetQueryPoolEXT",
    "vkSetBufferCollectionBufferConstraintsFUCHSIA",
    "vkSetBufferCollectionImageConstraintsFUCHSIA",
    "vkSetDebugUtilsObjectNameEXT",
    "vkSetDebugUtilsObjectTagEXT",
    "vkSetDeviceMemoryPriorityEXT",
    "vkSetEvent",
    "vkSetHdrMetadataEXT",
    "vkSetLatencyMarkerNV",
    "vkSetLatencySleepModeNV",
    "vkSetLocalDimmingAMD",
    "vkSetPrivateData",
    "vkSetPrivateDataEXT",
    "vkSignalSemaphore",
    "vkSignalSemaphoreKHR",
    "vkTransitionImageLayoutEXT",
    "vkTrimCommandPool",
    "vkTrimCommandPoolKHR",
    "vkUninitializePerformanceApiINTEL",
    "vkUnmapMemory",
    "vkUnmapMemory2KHR",
    "vkUpdateDescriptorSetWithTemplate",
    "vkUpdateDescriptorSetWithTemplateKHR",
    "vkUpdateDescriptorSets",
    "vkUpdateVideoSessionParametersKHR",
    "vkWaitForFences",
    "vkWaitForPresentKHR",
    "vkWaitSemaphores",
    "vkWaitSemaphoresKHR",
    "vkWriteAccelerationStructuresPropertiesKHR",
    "vkWriteMicromapsPropertiesEXT",
};

static int glad_vulkan_is_device_function(const char *name) {
    /* Exists as a workaround for:
     * https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/issues/2323
     *
     * `vkGetDeviceProcAddr` does not return NULL for non-device functions.
     */
    int i;
    int length = GLAD_ARRAYSIZE(DEVICE_FUNCTIONS);

    for (i=0; i < length; ++i) {
        if (strcmp(DEVICE_FUNCTIONS[i], name) == 0) {
            return 1;
        }
    }

    return 0;
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
