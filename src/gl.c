/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <glad/gl.h>

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
    "glAccumxOES", // 0
    "glAcquireKeyedMutexWin32EXT", // 1
    "glActiveProgramEXT", // 2
    "glActiveShaderProgram", // 3
    "glActiveStencilFaceEXT", // 4
    "glActiveTexture", // 5
    "glActiveTextureARB", // 6
    "glActiveVaryingNV", // 7
    "glAlphaFragmentOp1ATI", // 8
    "glAlphaFragmentOp2ATI", // 9
    "glAlphaFragmentOp3ATI", // 10
    "glAlphaFuncxOES", // 11
    "glAlphaToCoverageDitherControlNV", // 12
    "glApplyFramebufferAttachmentCMAAINTEL", // 13
    "glApplyTextureEXT", // 14
    "glAreProgramsResidentNV", // 15
    "glAreTexturesResidentEXT", // 16
    "glArrayElementEXT", // 17
    "glArrayObjectATI", // 18
    "glAsyncCopyBufferSubDataNVX", // 19
    "glAsyncCopyImageSubDataNVX", // 20
    "glAsyncMarkerSGIX", // 21
    "glAttachObjectARB", // 22
    "glAttachShader", // 23
    "glBeginConditionalRender", // 24
    "glBeginConditionalRenderNV", // 25
    "glBeginConditionalRenderNVX", // 26
    "glBeginFragmentShaderATI", // 27
    "glBeginOcclusionQueryNV", // 28
    "glBeginPerfMonitorAMD", // 29
    "glBeginPerfQueryINTEL", // 30
    "glBeginQuery", // 31
    "glBeginQueryARB", // 32
    "glBeginQueryIndexed", // 33
    "glBeginTransformFeedback", // 34
    "glBeginTransformFeedbackEXT", // 35
    "glBeginTransformFeedbackNV", // 36
    "glBeginVertexShaderEXT", // 37
    "glBeginVideoCaptureNV", // 38
    "glBindAttribLocation", // 39
    "glBindAttribLocationARB", // 40
    "glBindBuffer", // 41
    "glBindBufferARB", // 42
    "glBindBufferBase", // 43
    "glBindBufferBaseEXT", // 44
    "glBindBufferBaseNV", // 45
    "glBindBufferOffsetEXT", // 46
    "glBindBufferOffsetNV", // 47
    "glBindBufferRange", // 48
    "glBindBufferRangeEXT", // 49
    "glBindBufferRangeNV", // 50
    "glBindBuffersBase", // 51
    "glBindBuffersRange", // 52
    "glBindFragDataLocation", // 53
    "glBindFragDataLocationEXT", // 54
    "glBindFragDataLocationIndexed", // 55
    "glBindFragmentShaderATI", // 56
    "glBindFramebuffer", // 57
    "glBindFramebufferEXT", // 58
    "glBindImageTexture", // 59
    "glBindImageTextureEXT", // 60
    "glBindImageTextures", // 61
    "glBindLightParameterEXT", // 62
    "glBindMaterialParameterEXT", // 63
    "glBindMultiTextureEXT", // 64
    "glBindParameterEXT", // 65
    "glBindProgramARB", // 66
    "glBindProgramNV", // 67
    "glBindProgramPipeline", // 68
    "glBindRenderbuffer", // 69
    "glBindRenderbufferEXT", // 70
    "glBindSampler", // 71
    "glBindSamplers", // 72
    "glBindShadingRateImageNV", // 73
    "glBindTexGenParameterEXT", // 74
    "glBindTexture", // 75
    "glBindTextureEXT", // 76
    "glBindTextureUnit", // 77
    "glBindTextureUnitParameterEXT", // 78
    "glBindTextures", // 79
    "glBindTransformFeedback", // 80
    "glBindTransformFeedbackNV", // 81
    "glBindVertexArray", // 82
    "glBindVertexArrayAPPLE", // 83
    "glBindVertexBuffer", // 84
    "glBindVertexBuffers", // 85
    "glBindVertexShaderEXT", // 86
    "glBindVideoCaptureStreamBufferNV", // 87
    "glBindVideoCaptureStreamTextureNV", // 88
    "glBinormal3bEXT", // 89
    "glBinormal3bvEXT", // 90
    "glBinormal3dEXT", // 91
    "glBinormal3dvEXT", // 92
    "glBinormal3fEXT", // 93
    "glBinormal3fvEXT", // 94
    "glBinormal3iEXT", // 95
    "glBinormal3ivEXT", // 96
    "glBinormal3sEXT", // 97
    "glBinormal3svEXT", // 98
    "glBinormalPointerEXT", // 99
    "glBitmapxOES", // 100
    "glBlendBarrierKHR", // 101
    "glBlendBarrierNV", // 102
    "glBlendColor", // 103
    "glBlendColorEXT", // 104
    "glBlendColorxOES", // 105
    "glBlendEquation", // 106
    "glBlendEquationEXT", // 107
    "glBlendEquationIndexedAMD", // 108
    "glBlendEquationSeparate", // 109
    "glBlendEquationSeparateEXT", // 110
    "glBlendEquationSeparateIndexedAMD", // 111
    "glBlendEquationSeparatei", // 112
    "glBlendEquationSeparateiARB", // 113
    "glBlendEquationi", // 114
    "glBlendEquationiARB", // 115
    "glBlendFunc", // 116
    "glBlendFuncIndexedAMD", // 117
    "glBlendFuncSeparate", // 118
    "glBlendFuncSeparateEXT", // 119
    "glBlendFuncSeparateINGR", // 120
    "glBlendFuncSeparateIndexedAMD", // 121
    "glBlendFuncSeparatei", // 122
    "glBlendFuncSeparateiARB", // 123
    "glBlendFunci", // 124
    "glBlendFunciARB", // 125
    "glBlendParameteriNV", // 126
    "glBlitFramebuffer", // 127
    "glBlitFramebufferEXT", // 128
    "glBlitFramebufferLayerEXT", // 129
    "glBlitFramebufferLayersEXT", // 130
    "glBlitNamedFramebuffer", // 131
    "glBufferAddressRangeNV", // 132
    "glBufferAttachMemoryNV", // 133
    "glBufferData", // 134
    "glBufferDataARB", // 135
    "glBufferPageCommitmentARB", // 136
    "glBufferPageCommitmentMemNV", // 137
    "glBufferParameteriAPPLE", // 138
    "glBufferStorage", // 139
    "glBufferStorageExternalEXT", // 140
    "glBufferStorageMemEXT", // 141
    "glBufferSubData", // 142
    "glBufferSubDataARB", // 143
    "glCallCommandListNV", // 144
    "glCheckFramebufferStatus", // 145
    "glCheckFramebufferStatusEXT", // 146
    "glCheckNamedFramebufferStatus", // 147
    "glCheckNamedFramebufferStatusEXT", // 148
    "glClampColor", // 149
    "glClampColorARB", // 150
    "glClear", // 151
    "glClearAccumxOES", // 152
    "glClearBufferData", // 153
    "glClearBufferSubData", // 154
    "glClearBufferfi", // 155
    "glClearBufferfv", // 156
    "glClearBufferiv", // 157
    "glClearBufferuiv", // 158
    "glClearColor", // 159
    "glClearColorIiEXT", // 160
    "glClearColorIuiEXT", // 161
    "glClearColorxOES", // 162
    "glClearDepth", // 163
    "glClearDepthdNV", // 164
    "glClearDepthf", // 165
    "glClearDepthfOES", // 166
    "glClearDepthxOES", // 167
    "glClearNamedBufferData", // 168
    "glClearNamedBufferDataEXT", // 169
    "glClearNamedBufferSubData", // 170
    "glClearNamedBufferSubDataEXT", // 171
    "glClearNamedFramebufferfi", // 172
    "glClearNamedFramebufferfv", // 173
    "glClearNamedFramebufferiv", // 174
    "glClearNamedFramebufferuiv", // 175
    "glClearStencil", // 176
    "glClearTexImage", // 177
    "glClearTexSubImage", // 178
    "glClientActiveTextureARB", // 179
    "glClientActiveVertexStreamATI", // 180
    "glClientAttribDefaultEXT", // 181
    "glClientWaitSemaphoreui64NVX", // 182
    "glClientWaitSync", // 183
    "glClipControl", // 184
    "glClipPlanefOES", // 185
    "glClipPlanexOES", // 186
    "glColor3fVertex3fSUN", // 187
    "glColor3fVertex3fvSUN", // 188
    "glColor3hNV", // 189
    "glColor3hvNV", // 190
    "glColor3xOES", // 191
    "glColor3xvOES", // 192
    "glColor4fNormal3fVertex3fSUN", // 193
    "glColor4fNormal3fVertex3fvSUN", // 194
    "glColor4hNV", // 195
    "glColor4hvNV", // 196
    "glColor4ubVertex2fSUN", // 197
    "glColor4ubVertex2fvSUN", // 198
    "glColor4ubVertex3fSUN", // 199
    "glColor4ubVertex3fvSUN", // 200
    "glColor4xOES", // 201
    "glColor4xvOES", // 202
    "glColorFormatNV", // 203
    "glColorFragmentOp1ATI", // 204
    "glColorFragmentOp2ATI", // 205
    "glColorFragmentOp3ATI", // 206
    "glColorMask", // 207
    "glColorMaskIndexedEXT", // 208
    "glColorMaski", // 209
    "glColorPointerEXT", // 210
    "glColorPointerListIBM", // 211
    "glColorPointervINTEL", // 212
    "glColorSubTableEXT", // 213
    "glColorTableEXT", // 214
    "glColorTableParameterfvSGI", // 215
    "glColorTableParameterivSGI", // 216
    "glColorTableSGI", // 217
    "glCombinerInputNV", // 218
    "glCombinerOutputNV", // 219
    "glCombinerParameterfNV", // 220
    "glCombinerParameterfvNV", // 221
    "glCombinerParameteriNV", // 222
    "glCombinerParameterivNV", // 223
    "glCombinerStageParameterfvNV", // 224
    "glCommandListSegmentsNV", // 225
    "glCompileCommandListNV", // 226
    "glCompileShader", // 227
    "glCompileShaderARB", // 228
    "glCompileShaderIncludeARB", // 229
    "glCompressedMultiTexImage1DEXT", // 230
    "glCompressedMultiTexImage2DEXT", // 231
    "glCompressedMultiTexImage3DEXT", // 232
    "glCompressedMultiTexSubImage1DEXT", // 233
    "glCompressedMultiTexSubImage2DEXT", // 234
    "glCompressedMultiTexSubImage3DEXT", // 235
    "glCompressedTexImage1D", // 236
    "glCompressedTexImage1DARB", // 237
    "glCompressedTexImage2D", // 238
    "glCompressedTexImage2DARB", // 239
    "glCompressedTexImage3D", // 240
    "glCompressedTexImage3DARB", // 241
    "glCompressedTexSubImage1D", // 242
    "glCompressedTexSubImage1DARB", // 243
    "glCompressedTexSubImage2D", // 244
    "glCompressedTexSubImage2DARB", // 245
    "glCompressedTexSubImage3D", // 246
    "glCompressedTexSubImage3DARB", // 247
    "glCompressedTextureImage1DEXT", // 248
    "glCompressedTextureImage2DEXT", // 249
    "glCompressedTextureImage3DEXT", // 250
    "glCompressedTextureSubImage1D", // 251
    "glCompressedTextureSubImage1DEXT", // 252
    "glCompressedTextureSubImage2D", // 253
    "glCompressedTextureSubImage2DEXT", // 254
    "glCompressedTextureSubImage3D", // 255
    "glCompressedTextureSubImage3DEXT", // 256
    "glConservativeRasterParameterfNV", // 257
    "glConservativeRasterParameteriNV", // 258
    "glConvolutionFilter1DEXT", // 259
    "glConvolutionFilter2DEXT", // 260
    "glConvolutionParameterfEXT", // 261
    "glConvolutionParameterfvEXT", // 262
    "glConvolutionParameteriEXT", // 263
    "glConvolutionParameterivEXT", // 264
    "glConvolutionParameterxOES", // 265
    "glConvolutionParameterxvOES", // 266
    "glCopyBufferSubData", // 267
    "glCopyColorSubTableEXT", // 268
    "glCopyColorTableSGI", // 269
    "glCopyConvolutionFilter1DEXT", // 270
    "glCopyConvolutionFilter2DEXT", // 271
    "glCopyImageSubData", // 272
    "glCopyImageSubDataNV", // 273
    "glCopyMultiTexImage1DEXT", // 274
    "glCopyMultiTexImage2DEXT", // 275
    "glCopyMultiTexSubImage1DEXT", // 276
    "glCopyMultiTexSubImage2DEXT", // 277
    "glCopyMultiTexSubImage3DEXT", // 278
    "glCopyNamedBufferSubData", // 279
    "glCopyPathNV", // 280
    "glCopyTexImage1D", // 281
    "glCopyTexImage1DEXT", // 282
    "glCopyTexImage2D", // 283
    "glCopyTexImage2DEXT", // 284
    "glCopyTexSubImage1D", // 285
    "glCopyTexSubImage1DEXT", // 286
    "glCopyTexSubImage2D", // 287
    "glCopyTexSubImage2DEXT", // 288
    "glCopyTexSubImage3D", // 289
    "glCopyTexSubImage3DEXT", // 290
    "glCopyTextureImage1DEXT", // 291
    "glCopyTextureImage2DEXT", // 292
    "glCopyTextureSubImage1D", // 293
    "glCopyTextureSubImage1DEXT", // 294
    "glCopyTextureSubImage2D", // 295
    "glCopyTextureSubImage2DEXT", // 296
    "glCopyTextureSubImage3D", // 297
    "glCopyTextureSubImage3DEXT", // 298
    "glCoverFillPathInstancedNV", // 299
    "glCoverFillPathNV", // 300
    "glCoverStrokePathInstancedNV", // 301
    "glCoverStrokePathNV", // 302
    "glCoverageModulationNV", // 303
    "glCoverageModulationTableNV", // 304
    "glCreateBuffers", // 305
    "glCreateCommandListsNV", // 306
    "glCreateFramebuffers", // 307
    "glCreateMemoryObjectsEXT", // 308
    "glCreatePerfQueryINTEL", // 309
    "glCreateProgram", // 310
    "glCreateProgramObjectARB", // 311
    "glCreateProgramPipelines", // 312
    "glCreateProgressFenceNVX", // 313
    "glCreateQueries", // 314
    "glCreateRenderbuffers", // 315
    "glCreateSamplers", // 316
    "glCreateSemaphoresNV", // 317
    "glCreateShader", // 318
    "glCreateShaderObjectARB", // 319
    "glCreateShaderProgramEXT", // 320
    "glCreateShaderProgramv", // 321
    "glCreateStatesNV", // 322
    "glCreateSyncFromCLeventARB", // 323
    "glCreateTextures", // 324
    "glCreateTransformFeedbacks", // 325
    "glCreateVertexArrays", // 326
    "glCullFace", // 327
    "glCullParameterdvEXT", // 328
    "glCullParameterfvEXT", // 329
    "glCurrentPaletteMatrixARB", // 330
    "glDebugMessageCallback", // 331
    "glDebugMessageCallbackAMD", // 332
    "glDebugMessageCallbackARB", // 333
    "glDebugMessageControl", // 334
    "glDebugMessageControlARB", // 335
    "glDebugMessageEnableAMD", // 336
    "glDebugMessageInsert", // 337
    "glDebugMessageInsertAMD", // 338
    "glDebugMessageInsertARB", // 339
    "glDeformSGIX", // 340
    "glDeformationMap3dSGIX", // 341
    "glDeformationMap3fSGIX", // 342
    "glDeleteAsyncMarkersSGIX", // 343
    "glDeleteBuffers", // 344
    "glDeleteBuffersARB", // 345
    "glDeleteCommandListsNV", // 346
    "glDeleteFencesAPPLE", // 347
    "glDeleteFencesNV", // 348
    "glDeleteFragmentShaderATI", // 349
    "glDeleteFramebuffers", // 350
    "glDeleteFramebuffersEXT", // 351
    "glDeleteMemoryObjectsEXT", // 352
    "glDeleteNamedStringARB", // 353
    "glDeleteNamesAMD", // 354
    "glDeleteObjectARB", // 355
    "glDeleteOcclusionQueriesNV", // 356
    "glDeletePathsNV", // 357
    "glDeletePerfMonitorsAMD", // 358
    "glDeletePerfQueryINTEL", // 359
    "glDeleteProgram", // 360
    "glDeleteProgramPipelines", // 361
    "glDeleteProgramsARB", // 362
    "glDeleteProgramsNV", // 363
    "glDeleteQueries", // 364
    "glDeleteQueriesARB", // 365
    "glDeleteQueryResourceTagNV", // 366
    "glDeleteRenderbuffers", // 367
    "glDeleteRenderbuffersEXT", // 368
    "glDeleteSamplers", // 369
    "glDeleteSemaphoresEXT", // 370
    "glDeleteShader", // 371
    "glDeleteStatesNV", // 372
    "glDeleteSync", // 373
    "glDeleteTextures", // 374
    "glDeleteTexturesEXT", // 375
    "glDeleteTransformFeedbacks", // 376
    "glDeleteTransformFeedbacksNV", // 377
    "glDeleteVertexArrays", // 378
    "glDeleteVertexArraysAPPLE", // 379
    "glDeleteVertexShaderEXT", // 380
    "glDepthBoundsEXT", // 381
    "glDepthBoundsdNV", // 382
    "glDepthFunc", // 383
    "glDepthMask", // 384
    "glDepthRange", // 385
    "glDepthRangeArraydvNV", // 386
    "glDepthRangeArrayv", // 387
    "glDepthRangeIndexed", // 388
    "glDepthRangeIndexeddNV", // 389
    "glDepthRangedNV", // 390
    "glDepthRangef", // 391
    "glDepthRangefOES", // 392
    "glDepthRangexOES", // 393
    "glDetachObjectARB", // 394
    "glDetachShader", // 395
    "glDetailTexFuncSGIS", // 396
    "glDisable", // 397
    "glDisableClientStateIndexedEXT", // 398
    "glDisableClientStateiEXT", // 399
    "glDisableIndexedEXT", // 400
    "glDisableVariantClientStateEXT", // 401
    "glDisableVertexArrayAttrib", // 402
    "glDisableVertexArrayAttribEXT", // 403
    "glDisableVertexArrayEXT", // 404
    "glDisableVertexAttribAPPLE", // 405
    "glDisableVertexAttribArray", // 406
    "glDisableVertexAttribArrayARB", // 407
    "glDisablei", // 408
    "glDispatchCompute", // 409
    "glDispatchComputeGroupSizeARB", // 410
    "glDispatchComputeIndirect", // 411
    "glDrawArrays", // 412
    "glDrawArraysEXT", // 413
    "glDrawArraysIndirect", // 414
    "glDrawArraysInstanced", // 415
    "glDrawArraysInstancedARB", // 416
    "glDrawArraysInstancedBaseInstance", // 417
    "glDrawArraysInstancedEXT", // 418
    "glDrawBuffer", // 419
    "glDrawBuffers", // 420
    "glDrawBuffersARB", // 421
    "glDrawBuffersATI", // 422
    "glDrawCommandsAddressNV", // 423
    "glDrawCommandsNV", // 424
    "glDrawCommandsStatesAddressNV", // 425
    "glDrawCommandsStatesNV", // 426
    "glDrawElementArrayAPPLE", // 427
    "glDrawElementArrayATI", // 428
    "glDrawElements", // 429
    "glDrawElementsBaseVertex", // 430
    "glDrawElementsIndirect", // 431
    "glDrawElementsInstanced", // 432
    "glDrawElementsInstancedARB", // 433
    "glDrawElementsInstancedBaseInstance", // 434
    "glDrawElementsInstancedBaseVertex", // 435
    "glDrawElementsInstancedBaseVertexBaseInstance", // 436
    "glDrawElementsInstancedEXT", // 437
    "glDrawMeshArraysSUN", // 438
    "glDrawMeshTasksIndirectNV", // 439
    "glDrawMeshTasksNV", // 440
    "glDrawRangeElementArrayAPPLE", // 441
    "glDrawRangeElementArrayATI", // 442
    "glDrawRangeElements", // 443
    "glDrawRangeElementsBaseVertex", // 444
    "glDrawRangeElementsEXT", // 445
    "glDrawTextureNV", // 446
    "glDrawTransformFeedback", // 447
    "glDrawTransformFeedbackInstanced", // 448
    "glDrawTransformFeedbackNV", // 449
    "glDrawTransformFeedbackStream", // 450
    "glDrawTransformFeedbackStreamInstanced", // 451
    "glDrawVkImageNV", // 452
    "glEGLImageTargetTexStorageEXT", // 453
    "glEGLImageTargetTextureStorageEXT", // 454
    "glEdgeFlagFormatNV", // 455
    "glEdgeFlagPointerEXT", // 456
    "glEdgeFlagPointerListIBM", // 457
    "glElementPointerAPPLE", // 458
    "glElementPointerATI", // 459
    "glEnable", // 460
    "glEnableClientStateIndexedEXT", // 461
    "glEnableClientStateiEXT", // 462
    "glEnableIndexedEXT", // 463
    "glEnableVariantClientStateEXT", // 464
    "glEnableVertexArrayAttrib", // 465
    "glEnableVertexArrayAttribEXT", // 466
    "glEnableVertexArrayEXT", // 467
    "glEnableVertexAttribAPPLE", // 468
    "glEnableVertexAttribArray", // 469
    "glEnableVertexAttribArrayARB", // 470
    "glEnablei", // 471
    "glEndConditionalRender", // 472
    "glEndConditionalRenderNV", // 473
    "glEndConditionalRenderNVX", // 474
    "glEndFragmentShaderATI", // 475
    "glEndOcclusionQueryNV", // 476
    "glEndPerfMonitorAMD", // 477
    "glEndPerfQueryINTEL", // 478
    "glEndQuery", // 479
    "glEndQueryARB", // 480
    "glEndQueryIndexed", // 481
    "glEndTransformFeedback", // 482
    "glEndTransformFeedbackEXT", // 483
    "glEndTransformFeedbackNV", // 484
    "glEndVertexShaderEXT", // 485
    "glEndVideoCaptureNV", // 486
    "glEvalCoord1xOES", // 487
    "glEvalCoord1xvOES", // 488
    "glEvalCoord2xOES", // 489
    "glEvalCoord2xvOES", // 490
    "glEvalMapsNV", // 491
    "glEvaluateDepthValuesARB", // 492
    "glExecuteProgramNV", // 493
    "glExtractComponentEXT", // 494
    "glFeedbackBufferxOES", // 495
    "glFenceSync", // 496
    "glFinalCombinerInputNV", // 497
    "glFinish", // 498
    "glFinishAsyncSGIX", // 499
    "glFinishFenceAPPLE", // 500
    "glFinishFenceNV", // 501
    "glFinishObjectAPPLE", // 502
    "glFinishTextureSUNX", // 503
    "glFlush", // 504
    "glFlushMappedBufferRange", // 505
    "glFlushMappedBufferRangeAPPLE", // 506
    "glFlushMappedNamedBufferRange", // 507
    "glFlushMappedNamedBufferRangeEXT", // 508
    "glFlushPixelDataRangeNV", // 509
    "glFlushRasterSGIX", // 510
    "glFlushStaticDataIBM", // 511
    "glFlushVertexArrayRangeAPPLE", // 512
    "glFlushVertexArrayRangeNV", // 513
    "glFogCoordFormatNV", // 514
    "glFogCoordPointerEXT", // 515
    "glFogCoordPointerListIBM", // 516
    "glFogCoorddEXT", // 517
    "glFogCoorddvEXT", // 518
    "glFogCoordfEXT", // 519
    "glFogCoordfvEXT", // 520
    "glFogCoordhNV", // 521
    "glFogCoordhvNV", // 522
    "glFogFuncSGIS", // 523
    "glFogxOES", // 524
    "glFogxvOES", // 525
    "glFragmentColorMaterialSGIX", // 526
    "glFragmentCoverageColorNV", // 527
    "glFragmentLightModelfSGIX", // 528
    "glFragmentLightModelfvSGIX", // 529
    "glFragmentLightModeliSGIX", // 530
    "glFragmentLightModelivSGIX", // 531
    "glFragmentLightfSGIX", // 532
    "glFragmentLightfvSGIX", // 533
    "glFragmentLightiSGIX", // 534
    "glFragmentLightivSGIX", // 535
    "glFragmentMaterialfSGIX", // 536
    "glFragmentMaterialfvSGIX", // 537
    "glFragmentMaterialiSGIX", // 538
    "glFragmentMaterialivSGIX", // 539
    "glFrameTerminatorGREMEDY", // 540
    "glFrameZoomSGIX", // 541
    "glFramebufferDrawBufferEXT", // 542
    "glFramebufferDrawBuffersEXT", // 543
    "glFramebufferFetchBarrierEXT", // 544
    "glFramebufferParameteri", // 545
    "glFramebufferParameteriMESA", // 546
    "glFramebufferReadBufferEXT", // 547
    "glFramebufferRenderbuffer", // 548
    "glFramebufferRenderbufferEXT", // 549
    "glFramebufferSampleLocationsfvARB", // 550
    "glFramebufferSampleLocationsfvNV", // 551
    "glFramebufferSamplePositionsfvAMD", // 552
    "glFramebufferTexture", // 553
    "glFramebufferTexture1D", // 554
    "glFramebufferTexture1DEXT", // 555
    "glFramebufferTexture2D", // 556
    "glFramebufferTexture2DEXT", // 557
    "glFramebufferTexture3D", // 558
    "glFramebufferTexture3DEXT", // 559
    "glFramebufferTextureARB", // 560
    "glFramebufferTextureEXT", // 561
    "glFramebufferTextureFaceARB", // 562
    "glFramebufferTextureFaceEXT", // 563
    "glFramebufferTextureLayer", // 564
    "glFramebufferTextureLayerARB", // 565
    "glFramebufferTextureLayerEXT", // 566
    "glFramebufferTextureMultiviewOVR", // 567
    "glFreeObjectBufferATI", // 568
    "glFrontFace", // 569
    "glFrustumfOES", // 570
    "glFrustumxOES", // 571
    "glGenAsyncMarkersSGIX", // 572
    "glGenBuffers", // 573
    "glGenBuffersARB", // 574
    "glGenFencesAPPLE", // 575
    "glGenFencesNV", // 576
    "glGenFragmentShadersATI", // 577
    "glGenFramebuffers", // 578
    "glGenFramebuffersEXT", // 579
    "glGenNamesAMD", // 580
    "glGenOcclusionQueriesNV", // 581
    "glGenPathsNV", // 582
    "glGenPerfMonitorsAMD", // 583
    "glGenProgramPipelines", // 584
    "glGenProgramsARB", // 585
    "glGenProgramsNV", // 586
    "glGenQueries", // 587
    "glGenQueriesARB", // 588
    "glGenQueryResourceTagNV", // 589
    "glGenRenderbuffers", // 590
    "glGenRenderbuffersEXT", // 591
    "glGenSamplers", // 592
    "glGenSemaphoresEXT", // 593
    "glGenSymbolsEXT", // 594
    "glGenTextures", // 595
    "glGenTexturesEXT", // 596
    "glGenTransformFeedbacks", // 597
    "glGenTransformFeedbacksNV", // 598
    "glGenVertexArrays", // 599
    "glGenVertexArraysAPPLE", // 600
    "glGenVertexShadersEXT", // 601
    "glGenerateMipmap", // 602
    "glGenerateMipmapEXT", // 603
    "glGenerateMultiTexMipmapEXT", // 604
    "glGenerateTextureMipmap", // 605
    "glGenerateTextureMipmapEXT", // 606
    "glGetActiveAtomicCounterBufferiv", // 607
    "glGetActiveAttrib", // 608
    "glGetActiveAttribARB", // 609
    "glGetActiveSubroutineName", // 610
    "glGetActiveSubroutineUniformName", // 611
    "glGetActiveSubroutineUniformiv", // 612
    "glGetActiveUniform", // 613
    "glGetActiveUniformARB", // 614
    "glGetActiveUniformBlockName", // 615
    "glGetActiveUniformBlockiv", // 616
    "glGetActiveUniformName", // 617
    "glGetActiveUniformsiv", // 618
    "glGetActiveVaryingNV", // 619
    "glGetArrayObjectfvATI", // 620
    "glGetArrayObjectivATI", // 621
    "glGetAttachedObjectsARB", // 622
    "glGetAttachedShaders", // 623
    "glGetAttribLocation", // 624
    "glGetAttribLocationARB", // 625
    "glGetBooleanIndexedvEXT", // 626
    "glGetBooleani_v", // 627
    "glGetBooleanv", // 628
    "glGetBufferParameteri64v", // 629
    "glGetBufferParameteriv", // 630
    "glGetBufferParameterivARB", // 631
    "glGetBufferParameterui64vNV", // 632
    "glGetBufferPointerv", // 633
    "glGetBufferPointervARB", // 634
    "glGetBufferSubData", // 635
    "glGetBufferSubDataARB", // 636
    "glGetClipPlanefOES", // 637
    "glGetClipPlanexOES", // 638
    "glGetColorTableEXT", // 639
    "glGetColorTableParameterfvEXT", // 640
    "glGetColorTableParameterfvSGI", // 641
    "glGetColorTableParameterivEXT", // 642
    "glGetColorTableParameterivSGI", // 643
    "glGetColorTableSGI", // 644
    "glGetCombinerInputParameterfvNV", // 645
    "glGetCombinerInputParameterivNV", // 646
    "glGetCombinerOutputParameterfvNV", // 647
    "glGetCombinerOutputParameterivNV", // 648
    "glGetCombinerStageParameterfvNV", // 649
    "glGetCommandHeaderNV", // 650
    "glGetCompressedMultiTexImageEXT", // 651
    "glGetCompressedTexImage", // 652
    "glGetCompressedTexImageARB", // 653
    "glGetCompressedTextureImage", // 654
    "glGetCompressedTextureImageEXT", // 655
    "glGetCompressedTextureSubImage", // 656
    "glGetConvolutionFilterEXT", // 657
    "glGetConvolutionParameterfvEXT", // 658
    "glGetConvolutionParameterivEXT", // 659
    "glGetConvolutionParameterxvOES", // 660
    "glGetCoverageModulationTableNV", // 661
    "glGetDebugMessageLog", // 662
    "glGetDebugMessageLogAMD", // 663
    "glGetDebugMessageLogARB", // 664
    "glGetDetailTexFuncSGIS", // 665
    "glGetDoubleIndexedvEXT", // 666
    "glGetDoublei_v", // 667
    "glGetDoublei_vEXT", // 668
    "glGetDoublev", // 669
    "glGetError", // 670
    "glGetFenceivNV", // 671
    "glGetFinalCombinerInputParameterfvNV", // 672
    "glGetFinalCombinerInputParameterivNV", // 673
    "glGetFirstPerfQueryIdINTEL", // 674
    "glGetFixedvOES", // 675
    "glGetFloatIndexedvEXT", // 676
    "glGetFloati_v", // 677
    "glGetFloati_vEXT", // 678
    "glGetFloatv", // 679
    "glGetFogFuncSGIS", // 680
    "glGetFragDataIndex", // 681
    "glGetFragDataLocation", // 682
    "glGetFragDataLocationEXT", // 683
    "glGetFragmentLightfvSGIX", // 684
    "glGetFragmentLightivSGIX", // 685
    "glGetFragmentMaterialfvSGIX", // 686
    "glGetFragmentMaterialivSGIX", // 687
    "glGetFramebufferAttachmentParameteriv", // 688
    "glGetFramebufferAttachmentParameterivEXT", // 689
    "glGetFramebufferParameterfvAMD", // 690
    "glGetFramebufferParameteriv", // 691
    "glGetFramebufferParameterivEXT", // 692
    "glGetFramebufferParameterivMESA", // 693
    "glGetGraphicsResetStatus", // 694
    "glGetGraphicsResetStatusARB", // 695
    "glGetHandleARB", // 696
    "glGetHistogramEXT", // 697
    "glGetHistogramParameterfvEXT", // 698
    "glGetHistogramParameterivEXT", // 699
    "glGetHistogramParameterxvOES", // 700
    "glGetImageHandleARB", // 701
    "glGetImageHandleNV", // 702
    "glGetImageTransformParameterfvHP", // 703
    "glGetImageTransformParameterivHP", // 704
    "glGetInfoLogARB", // 705
    "glGetInstrumentsSGIX", // 706
    "glGetInteger64i_v", // 707
    "glGetInteger64v", // 708
    "glGetIntegerIndexedvEXT", // 709
    "glGetIntegeri_v", // 710
    "glGetIntegerui64i_vNV", // 711
    "glGetIntegerui64vNV", // 712
    "glGetIntegerv", // 713
    "glGetInternalformatSampleivNV", // 714
    "glGetInternalformati64v", // 715
    "glGetInternalformativ", // 716
    "glGetInvariantBooleanvEXT", // 717
    "glGetInvariantFloatvEXT", // 718
    "glGetInvariantIntegervEXT", // 719
    "glGetLightxOES", // 720
    "glGetListParameterfvSGIX", // 721
    "glGetListParameterivSGIX", // 722
    "glGetLocalConstantBooleanvEXT", // 723
    "glGetLocalConstantFloatvEXT", // 724
    "glGetLocalConstantIntegervEXT", // 725
    "glGetMapAttribParameterfvNV", // 726
    "glGetMapAttribParameterivNV", // 727
    "glGetMapControlPointsNV", // 728
    "glGetMapParameterfvNV", // 729
    "glGetMapParameterivNV", // 730
    "glGetMapxvOES", // 731
    "glGetMaterialxOES", // 732
    "glGetMemoryObjectDetachedResourcesuivNV", // 733
    "glGetMemoryObjectParameterivEXT", // 734
    "glGetMinmaxEXT", // 735
    "glGetMinmaxParameterfvEXT", // 736
    "glGetMinmaxParameterivEXT", // 737
    "glGetMultiTexEnvfvEXT", // 738
    "glGetMultiTexEnvivEXT", // 739
    "glGetMultiTexGendvEXT", // 740
    "glGetMultiTexGenfvEXT", // 741
    "glGetMultiTexGenivEXT", // 742
    "glGetMultiTexImageEXT", // 743
    "glGetMultiTexLevelParameterfvEXT", // 744
    "glGetMultiTexLevelParameterivEXT", // 745
    "glGetMultiTexParameterIivEXT", // 746
    "glGetMultiTexParameterIuivEXT", // 747
    "glGetMultiTexParameterfvEXT", // 748
    "glGetMultiTexParameterivEXT", // 749
    "glGetMultisamplefv", // 750
    "glGetMultisamplefvNV", // 751
    "glGetNamedBufferParameteri64v", // 752
    "glGetNamedBufferParameteriv", // 753
    "glGetNamedBufferParameterivEXT", // 754
    "glGetNamedBufferParameterui64vNV", // 755
    "glGetNamedBufferPointerv", // 756
    "glGetNamedBufferPointervEXT", // 757
    "glGetNamedBufferSubData", // 758
    "glGetNamedBufferSubDataEXT", // 759
    "glGetNamedFramebufferAttachmentParameteriv", // 760
    "glGetNamedFramebufferAttachmentParameterivEXT", // 761
    "glGetNamedFramebufferParameterfvAMD", // 762
    "glGetNamedFramebufferParameteriv", // 763
    "glGetNamedFramebufferParameterivEXT", // 764
    "glGetNamedProgramLocalParameterIivEXT", // 765
    "glGetNamedProgramLocalParameterIuivEXT", // 766
    "glGetNamedProgramLocalParameterdvEXT", // 767
    "glGetNamedProgramLocalParameterfvEXT", // 768
    "glGetNamedProgramStringEXT", // 769
    "glGetNamedProgramivEXT", // 770
    "glGetNamedRenderbufferParameteriv", // 771
    "glGetNamedRenderbufferParameterivEXT", // 772
    "glGetNamedStringARB", // 773
    "glGetNamedStringivARB", // 774
    "glGetNextPerfQueryIdINTEL", // 775
    "glGetObjectBufferfvATI", // 776
    "glGetObjectBufferivATI", // 777
    "glGetObjectLabel", // 778
    "glGetObjectLabelEXT", // 779
    "glGetObjectParameterfvARB", // 780
    "glGetObjectParameterivAPPLE", // 781
    "glGetObjectParameterivARB", // 782
    "glGetObjectPtrLabel", // 783
    "glGetOcclusionQueryivNV", // 784
    "glGetOcclusionQueryuivNV", // 785
    "glGetPathCommandsNV", // 786
    "glGetPathCoordsNV", // 787
    "glGetPathDashArrayNV", // 788
    "glGetPathLengthNV", // 789
    "glGetPathMetricRangeNV", // 790
    "glGetPathMetricsNV", // 791
    "glGetPathParameterfvNV", // 792
    "glGetPathParameterivNV", // 793
    "glGetPathSpacingNV", // 794
    "glGetPerfCounterInfoINTEL", // 795
    "glGetPerfMonitorCounterDataAMD", // 796
    "glGetPerfMonitorCounterInfoAMD", // 797
    "glGetPerfMonitorCounterStringAMD", // 798
    "glGetPerfMonitorCountersAMD", // 799
    "glGetPerfMonitorGroupStringAMD", // 800
    "glGetPerfMonitorGroupsAMD", // 801
    "glGetPerfQueryDataINTEL", // 802
    "glGetPerfQueryIdByNameINTEL", // 803
    "glGetPerfQueryInfoINTEL", // 804
    "glGetPixelMapxv", // 805
    "glGetPixelTexGenParameterfvSGIS", // 806
    "glGetPixelTexGenParameterivSGIS", // 807
    "glGetPixelTransformParameterfvEXT", // 808
    "glGetPixelTransformParameterivEXT", // 809
    "glGetPointerIndexedvEXT", // 810
    "glGetPointeri_vEXT", // 811
    "glGetPointerv", // 812
    "glGetPointervEXT", // 813
    "glGetProgramBinary", // 814
    "glGetProgramEnvParameterIivNV", // 815
    "glGetProgramEnvParameterIuivNV", // 816
    "glGetProgramEnvParameterdvARB", // 817
    "glGetProgramEnvParameterfvARB", // 818
    "glGetProgramInfoLog", // 819
    "glGetProgramInterfaceiv", // 820
    "glGetProgramLocalParameterIivNV", // 821
    "glGetProgramLocalParameterIuivNV", // 822
    "glGetProgramLocalParameterdvARB", // 823
    "glGetProgramLocalParameterfvARB", // 824
    "glGetProgramNamedParameterdvNV", // 825
    "glGetProgramNamedParameterfvNV", // 826
    "glGetProgramParameterdvNV", // 827
    "glGetProgramParameterfvNV", // 828
    "glGetProgramPipelineInfoLog", // 829
    "glGetProgramPipelineiv", // 830
    "glGetProgramResourceIndex", // 831
    "glGetProgramResourceLocation", // 832
    "glGetProgramResourceLocationIndex", // 833
    "glGetProgramResourceName", // 834
    "glGetProgramResourcefvNV", // 835
    "glGetProgramResourceiv", // 836
    "glGetProgramStageiv", // 837
    "glGetProgramStringARB", // 838
    "glGetProgramStringNV", // 839
    "glGetProgramSubroutineParameteruivNV", // 840
    "glGetProgramiv", // 841
    "glGetProgramivARB", // 842
    "glGetProgramivNV", // 843
    "glGetQueryBufferObjecti64v", // 844
    "glGetQueryBufferObjectiv", // 845
    "glGetQueryBufferObjectui64v", // 846
    "glGetQueryBufferObjectuiv", // 847
    "glGetQueryIndexediv", // 848
    "glGetQueryObjecti64v", // 849
    "glGetQueryObjecti64vEXT", // 850
    "glGetQueryObjectiv", // 851
    "glGetQueryObjectivARB", // 852
    "glGetQueryObjectui64v", // 853
    "glGetQueryObjectui64vEXT", // 854
    "glGetQueryObjectuiv", // 855
    "glGetQueryObjectuivARB", // 856
    "glGetQueryiv", // 857
    "glGetQueryivARB", // 858
    "glGetRenderbufferParameteriv", // 859
    "glGetRenderbufferParameterivEXT", // 860
    "glGetSamplerParameterIiv", // 861
    "glGetSamplerParameterIuiv", // 862
    "glGetSamplerParameterfv", // 863
    "glGetSamplerParameteriv", // 864
    "glGetSemaphoreParameterivNV", // 865
    "glGetSemaphoreParameterui64vEXT", // 866
    "glGetSeparableFilterEXT", // 867
    "glGetShaderInfoLog", // 868
    "glGetShaderPrecisionFormat", // 869
    "glGetShaderSource", // 870
    "glGetShaderSourceARB", // 871
    "glGetShaderiv", // 872
    "glGetShadingRateImagePaletteNV", // 873
    "glGetShadingRateSampleLocationivNV", // 874
    "glGetSharpenTexFuncSGIS", // 875
    "glGetStageIndexNV", // 876
    "glGetString", // 877
    "glGetStringi", // 878
    "glGetSubroutineIndex", // 879
    "glGetSubroutineUniformLocation", // 880
    "glGetSynciv", // 881
    "glGetTexBumpParameterfvATI", // 882
    "glGetTexBumpParameterivATI", // 883
    "glGetTexEnvxvOES", // 884
    "glGetTexFilterFuncSGIS", // 885
    "glGetTexGenxvOES", // 886
    "glGetTexImage", // 887
    "glGetTexLevelParameterfv", // 888
    "glGetTexLevelParameteriv", // 889
    "glGetTexLevelParameterxvOES", // 890
    "glGetTexParameterIiv", // 891
    "glGetTexParameterIivEXT", // 892
    "glGetTexParameterIuiv", // 893
    "glGetTexParameterIuivEXT", // 894
    "glGetTexParameterPointervAPPLE", // 895
    "glGetTexParameterfv", // 896
    "glGetTexParameteriv", // 897
    "glGetTexParameterxvOES", // 898
    "glGetTextureHandleARB", // 899
    "glGetTextureHandleNV", // 900
    "glGetTextureImage", // 901
    "glGetTextureImageEXT", // 902
    "glGetTextureLevelParameterfv", // 903
    "glGetTextureLevelParameterfvEXT", // 904
    "glGetTextureLevelParameteriv", // 905
    "glGetTextureLevelParameterivEXT", // 906
    "glGetTextureParameterIiv", // 907
    "glGetTextureParameterIivEXT", // 908
    "glGetTextureParameterIuiv", // 909
    "glGetTextureParameterIuivEXT", // 910
    "glGetTextureParameterfv", // 911
    "glGetTextureParameterfvEXT", // 912
    "glGetTextureParameteriv", // 913
    "glGetTextureParameterivEXT", // 914
    "glGetTextureSamplerHandleARB", // 915
    "glGetTextureSamplerHandleNV", // 916
    "glGetTextureSubImage", // 917
    "glGetTrackMatrixivNV", // 918
    "glGetTransformFeedbackVarying", // 919
    "glGetTransformFeedbackVaryingEXT", // 920
    "glGetTransformFeedbackVaryingNV", // 921
    "glGetTransformFeedbacki64_v", // 922
    "glGetTransformFeedbacki_v", // 923
    "glGetTransformFeedbackiv", // 924
    "glGetUniformBlockIndex", // 925
    "glGetUniformBufferSizeEXT", // 926
    "glGetUniformIndices", // 927
    "glGetUniformLocation", // 928
    "glGetUniformLocationARB", // 929
    "glGetUniformOffsetEXT", // 930
    "glGetUniformSubroutineuiv", // 931
    "glGetUniformdv", // 932
    "glGetUniformfv", // 933
    "glGetUniformfvARB", // 934
    "glGetUniformi64vARB", // 935
    "glGetUniformi64vNV", // 936
    "glGetUniformiv", // 937
    "glGetUniformivARB", // 938
    "glGetUniformui64vARB", // 939
    "glGetUniformui64vNV", // 940
    "glGetUniformuiv", // 941
    "glGetUniformuivEXT", // 942
    "glGetUnsignedBytei_vEXT", // 943
    "glGetUnsignedBytevEXT", // 944
    "glGetVariantArrayObjectfvATI", // 945
    "glGetVariantArrayObjectivATI", // 946
    "glGetVariantBooleanvEXT", // 947
    "glGetVariantFloatvEXT", // 948
    "glGetVariantIntegervEXT", // 949
    "glGetVariantPointervEXT", // 950
    "glGetVaryingLocationNV", // 951
    "glGetVertexArrayIndexed64iv", // 952
    "glGetVertexArrayIndexediv", // 953
    "glGetVertexArrayIntegeri_vEXT", // 954
    "glGetVertexArrayIntegervEXT", // 955
    "glGetVertexArrayPointeri_vEXT", // 956
    "glGetVertexArrayPointervEXT", // 957
    "glGetVertexArrayiv", // 958
    "glGetVertexAttribArrayObjectfvATI", // 959
    "glGetVertexAttribArrayObjectivATI", // 960
    "glGetVertexAttribIiv", // 961
    "glGetVertexAttribIivEXT", // 962
    "glGetVertexAttribIuiv", // 963
    "glGetVertexAttribIuivEXT", // 964
    "glGetVertexAttribLdv", // 965
    "glGetVertexAttribLdvEXT", // 966
    "glGetVertexAttribLi64vNV", // 967
    "glGetVertexAttribLui64vARB", // 968
    "glGetVertexAttribLui64vNV", // 969
    "glGetVertexAttribPointerv", // 970
    "glGetVertexAttribPointervARB", // 971
    "glGetVertexAttribPointervNV", // 972
    "glGetVertexAttribdv", // 973
    "glGetVertexAttribdvARB", // 974
    "glGetVertexAttribdvNV", // 975
    "glGetVertexAttribfv", // 976
    "glGetVertexAttribfvARB", // 977
    "glGetVertexAttribfvNV", // 978
    "glGetVertexAttribiv", // 979
    "glGetVertexAttribivARB", // 980
    "glGetVertexAttribivNV", // 981
    "glGetVideoCaptureStreamdvNV", // 982
    "glGetVideoCaptureStreamfvNV", // 983
    "glGetVideoCaptureStreamivNV", // 984
    "glGetVideoCaptureivNV", // 985
    "glGetVideoi64vNV", // 986
    "glGetVideoivNV", // 987
    "glGetVideoui64vNV", // 988
    "glGetVideouivNV", // 989
    "glGetVkProcAddrNV", // 990
    "glGetnCompressedTexImage", // 991
    "glGetnCompressedTexImageARB", // 992
    "glGetnTexImage", // 993
    "glGetnTexImageARB", // 994
    "glGetnUniformdv", // 995
    "glGetnUniformdvARB", // 996
    "glGetnUniformfv", // 997
    "glGetnUniformfvARB", // 998
    "glGetnUniformi64vARB", // 999
    "glGetnUniformiv", // 1000
    "glGetnUniformivARB", // 1001
    "glGetnUniformui64vARB", // 1002
    "glGetnUniformuiv", // 1003
    "glGetnUniformuivARB", // 1004
    "glGlobalAlphaFactorbSUN", // 1005
    "glGlobalAlphaFactordSUN", // 1006
    "glGlobalAlphaFactorfSUN", // 1007
    "glGlobalAlphaFactoriSUN", // 1008
    "glGlobalAlphaFactorsSUN", // 1009
    "glGlobalAlphaFactorubSUN", // 1010
    "glGlobalAlphaFactoruiSUN", // 1011
    "glGlobalAlphaFactorusSUN", // 1012
    "glHint", // 1013
    "glHintPGI", // 1014
    "glHistogramEXT", // 1015
    "glIglooInterfaceSGIX", // 1016
    "glImageTransformParameterfHP", // 1017
    "glImageTransformParameterfvHP", // 1018
    "glImageTransformParameteriHP", // 1019
    "glImageTransformParameterivHP", // 1020
    "glImportMemoryFdEXT", // 1021
    "glImportMemoryWin32HandleEXT", // 1022
    "glImportMemoryWin32NameEXT", // 1023
    "glImportMemoryZirconHandleANGLE", // 1024
    "glImportSemaphoreFdEXT", // 1025
    "glImportSemaphoreWin32HandleEXT", // 1026
    "glImportSemaphoreWin32NameEXT", // 1027
    "glImportSemaphoreZirconHandleANGLE", // 1028
    "glImportSyncEXT", // 1029
    "glIndexFormatNV", // 1030
    "glIndexFuncEXT", // 1031
    "glIndexMaterialEXT", // 1032
    "glIndexPointerEXT", // 1033
    "glIndexPointerListIBM", // 1034
    "glIndexxOES", // 1035
    "glIndexxvOES", // 1036
    "glInsertComponentEXT", // 1037
    "glInsertEventMarkerEXT", // 1038
    "glInstrumentsBufferSGIX", // 1039
    "glInterpolatePathsNV", // 1040
    "glInvalidateBufferData", // 1041
    "glInvalidateBufferSubData", // 1042
    "glInvalidateFramebuffer", // 1043
    "glInvalidateNamedFramebufferData", // 1044
    "glInvalidateNamedFramebufferSubData", // 1045
    "glInvalidateSubFramebuffer", // 1046
    "glInvalidateTexImage", // 1047
    "glInvalidateTexSubImage", // 1048
    "glInvalidateTextureANGLE", // 1049
    "glIsAsyncMarkerSGIX", // 1050
    "glIsBuffer", // 1051
    "glIsBufferARB", // 1052
    "glIsBufferResidentNV", // 1053
    "glIsCommandListNV", // 1054
    "glIsEnabled", // 1055
    "glIsEnabledIndexedEXT", // 1056
    "glIsEnabledi", // 1057
    "glIsFenceAPPLE", // 1058
    "glIsFenceNV", // 1059
    "glIsFramebuffer", // 1060
    "glIsFramebufferEXT", // 1061
    "glIsImageHandleResidentARB", // 1062
    "glIsImageHandleResidentNV", // 1063
    "glIsMemoryObjectEXT", // 1064
    "glIsNameAMD", // 1065
    "glIsNamedBufferResidentNV", // 1066
    "glIsNamedStringARB", // 1067
    "glIsObjectBufferATI", // 1068
    "glIsOcclusionQueryNV", // 1069
    "glIsPathNV", // 1070
    "glIsPointInFillPathNV", // 1071
    "glIsPointInStrokePathNV", // 1072
    "glIsProgram", // 1073
    "glIsProgramARB", // 1074
    "glIsProgramNV", // 1075
    "glIsProgramPipeline", // 1076
    "glIsQuery", // 1077
    "glIsQueryARB", // 1078
    "glIsRenderbuffer", // 1079
    "glIsRenderbufferEXT", // 1080
    "glIsSampler", // 1081
    "glIsSemaphoreEXT", // 1082
    "glIsShader", // 1083
    "glIsStateNV", // 1084
    "glIsSync", // 1085
    "glIsTexture", // 1086
    "glIsTextureEXT", // 1087
    "glIsTextureHandleResidentARB", // 1088
    "glIsTextureHandleResidentNV", // 1089
    "glIsTransformFeedback", // 1090
    "glIsTransformFeedbackNV", // 1091
    "glIsVariantEnabledEXT", // 1092
    "glIsVertexArray", // 1093
    "glIsVertexArrayAPPLE", // 1094
    "glIsVertexAttribEnabledAPPLE", // 1095
    "glLGPUCopyImageSubDataNVX", // 1096
    "glLGPUInterlockNVX", // 1097
    "glLGPUNamedBufferSubDataNVX", // 1098
    "glLabelObjectEXT", // 1099
    "glLightEnviSGIX", // 1100
    "glLightModelxOES", // 1101
    "glLightModelxvOES", // 1102
    "glLightxOES", // 1103
    "glLightxvOES", // 1104
    "glLineWidth", // 1105
    "glLineWidthxOES", // 1106
    "glLinkProgram", // 1107
    "glLinkProgramARB", // 1108
    "glListDrawCommandsStatesClientNV", // 1109
    "glListParameterfSGIX", // 1110
    "glListParameterfvSGIX", // 1111
    "glListParameteriSGIX", // 1112
    "glListParameterivSGIX", // 1113
    "glLoadIdentityDeformationMapSGIX", // 1114
    "glLoadMatrixxOES", // 1115
    "glLoadProgramNV", // 1116
    "glLoadTransposeMatrixdARB", // 1117
    "glLoadTransposeMatrixfARB", // 1118
    "glLoadTransposeMatrixxOES", // 1119
    "glLockArraysEXT", // 1120
    "glLogicOp", // 1121
    "glMakeBufferNonResidentNV", // 1122
    "glMakeBufferResidentNV", // 1123
    "glMakeImageHandleNonResidentARB", // 1124
    "glMakeImageHandleNonResidentNV", // 1125
    "glMakeImageHandleResidentARB", // 1126
    "glMakeImageHandleResidentNV", // 1127
    "glMakeNamedBufferNonResidentNV", // 1128
    "glMakeNamedBufferResidentNV", // 1129
    "glMakeTextureHandleNonResidentARB", // 1130
    "glMakeTextureHandleNonResidentNV", // 1131
    "glMakeTextureHandleResidentARB", // 1132
    "glMakeTextureHandleResidentNV", // 1133
    "glMap1xOES", // 1134
    "glMap2xOES", // 1135
    "glMapBuffer", // 1136
    "glMapBufferARB", // 1137
    "glMapBufferRange", // 1138
    "glMapControlPointsNV", // 1139
    "glMapGrid1xOES", // 1140
    "glMapGrid2xOES", // 1141
    "glMapNamedBuffer", // 1142
    "glMapNamedBufferEXT", // 1143
    "glMapNamedBufferRange", // 1144
    "glMapNamedBufferRangeEXT", // 1145
    "glMapObjectBufferATI", // 1146
    "glMapParameterfvNV", // 1147
    "glMapParameterivNV", // 1148
    "glMapTexture2DINTEL", // 1149
    "glMapVertexAttrib1dAPPLE", // 1150
    "glMapVertexAttrib1fAPPLE", // 1151
    "glMapVertexAttrib2dAPPLE", // 1152
    "glMapVertexAttrib2fAPPLE", // 1153
    "glMaterialxOES", // 1154
    "glMaterialxvOES", // 1155
    "glMatrixFrustumEXT", // 1156
    "glMatrixIndexPointerARB", // 1157
    "glMatrixIndexubvARB", // 1158
    "glMatrixIndexuivARB", // 1159
    "glMatrixIndexusvARB", // 1160
    "glMatrixLoad3x2fNV", // 1161
    "glMatrixLoad3x3fNV", // 1162
    "glMatrixLoadIdentityEXT", // 1163
    "glMatrixLoadTranspose3x3fNV", // 1164
    "glMatrixLoadTransposedEXT", // 1165
    "glMatrixLoadTransposefEXT", // 1166
    "glMatrixLoaddEXT", // 1167
    "glMatrixLoadfEXT", // 1168
    "glMatrixMult3x2fNV", // 1169
    "glMatrixMult3x3fNV", // 1170
    "glMatrixMultTranspose3x3fNV", // 1171
    "glMatrixMultTransposedEXT", // 1172
    "glMatrixMultTransposefEXT", // 1173
    "glMatrixMultdEXT", // 1174
    "glMatrixMultfEXT", // 1175
    "glMatrixOrthoEXT", // 1176
    "glMatrixPopEXT", // 1177
    "glMatrixPushEXT", // 1178
    "glMatrixRotatedEXT", // 1179
    "glMatrixRotatefEXT", // 1180
    "glMatrixScaledEXT", // 1181
    "glMatrixScalefEXT", // 1182
    "glMatrixTranslatedEXT", // 1183
    "glMatrixTranslatefEXT", // 1184
    "glMaxShaderCompilerThreadsARB", // 1185
    "glMaxShaderCompilerThreadsKHR", // 1186
    "glMemoryBarrier", // 1187
    "glMemoryBarrierByRegion", // 1188
    "glMemoryBarrierEXT", // 1189
    "glMemoryObjectParameterivEXT", // 1190
    "glMinSampleShading", // 1191
    "glMinSampleShadingARB", // 1192
    "glMinmaxEXT", // 1193
    "glMultMatrixxOES", // 1194
    "glMultTransposeMatrixdARB", // 1195
    "glMultTransposeMatrixfARB", // 1196
    "glMultTransposeMatrixxOES", // 1197
    "glMultiDrawArrays", // 1198
    "glMultiDrawArraysEXT", // 1199
    "glMultiDrawArraysIndirect", // 1200
    "glMultiDrawArraysIndirectAMD", // 1201
    "glMultiDrawArraysIndirectBindlessCountNV", // 1202
    "glMultiDrawArraysIndirectBindlessNV", // 1203
    "glMultiDrawArraysIndirectCount", // 1204
    "glMultiDrawArraysIndirectCountARB", // 1205
    "glMultiDrawElementArrayAPPLE", // 1206
    "glMultiDrawElements", // 1207
    "glMultiDrawElementsBaseVertex", // 1208
    "glMultiDrawElementsEXT", // 1209
    "glMultiDrawElementsIndirect", // 1210
    "glMultiDrawElementsIndirectAMD", // 1211
    "glMultiDrawElementsIndirectBindlessCountNV", // 1212
    "glMultiDrawElementsIndirectBindlessNV", // 1213
    "glMultiDrawElementsIndirectCount", // 1214
    "glMultiDrawElementsIndirectCountARB", // 1215
    "glMultiDrawMeshTasksIndirectCountNV", // 1216
    "glMultiDrawMeshTasksIndirectNV", // 1217
    "glMultiDrawRangeElementArrayAPPLE", // 1218
    "glMultiModeDrawArraysIBM", // 1219
    "glMultiModeDrawElementsIBM", // 1220
    "glMultiTexBufferEXT", // 1221
    "glMultiTexCoord1bOES", // 1222
    "glMultiTexCoord1bvOES", // 1223
    "glMultiTexCoord1dARB", // 1224
    "glMultiTexCoord1dvARB", // 1225
    "glMultiTexCoord1fARB", // 1226
    "glMultiTexCoord1fvARB", // 1227
    "glMultiTexCoord1hNV", // 1228
    "glMultiTexCoord1hvNV", // 1229
    "glMultiTexCoord1iARB", // 1230
    "glMultiTexCoord1ivARB", // 1231
    "glMultiTexCoord1sARB", // 1232
    "glMultiTexCoord1svARB", // 1233
    "glMultiTexCoord1xOES", // 1234
    "glMultiTexCoord1xvOES", // 1235
    "glMultiTexCoord2bOES", // 1236
    "glMultiTexCoord2bvOES", // 1237
    "glMultiTexCoord2dARB", // 1238
    "glMultiTexCoord2dvARB", // 1239
    "glMultiTexCoord2fARB", // 1240
    "glMultiTexCoord2fvARB", // 1241
    "glMultiTexCoord2hNV", // 1242
    "glMultiTexCoord2hvNV", // 1243
    "glMultiTexCoord2iARB", // 1244
    "glMultiTexCoord2ivARB", // 1245
    "glMultiTexCoord2sARB", // 1246
    "glMultiTexCoord2svARB", // 1247
    "glMultiTexCoord2xOES", // 1248
    "glMultiTexCoord2xvOES", // 1249
    "glMultiTexCoord3bOES", // 1250
    "glMultiTexCoord3bvOES", // 1251
    "glMultiTexCoord3dARB", // 1252
    "glMultiTexCoord3dvARB", // 1253
    "glMultiTexCoord3fARB", // 1254
    "glMultiTexCoord3fvARB", // 1255
    "glMultiTexCoord3hNV", // 1256
    "glMultiTexCoord3hvNV", // 1257
    "glMultiTexCoord3iARB", // 1258
    "glMultiTexCoord3ivARB", // 1259
    "glMultiTexCoord3sARB", // 1260
    "glMultiTexCoord3svARB", // 1261
    "glMultiTexCoord3xOES", // 1262
    "glMultiTexCoord3xvOES", // 1263
    "glMultiTexCoord4bOES", // 1264
    "glMultiTexCoord4bvOES", // 1265
    "glMultiTexCoord4dARB", // 1266
    "glMultiTexCoord4dvARB", // 1267
    "glMultiTexCoord4fARB", // 1268
    "glMultiTexCoord4fvARB", // 1269
    "glMultiTexCoord4hNV", // 1270
    "glMultiTexCoord4hvNV", // 1271
    "glMultiTexCoord4iARB", // 1272
    "glMultiTexCoord4ivARB", // 1273
    "glMultiTexCoord4sARB", // 1274
    "glMultiTexCoord4svARB", // 1275
    "glMultiTexCoord4xOES", // 1276
    "glMultiTexCoord4xvOES", // 1277
    "glMultiTexCoordPointerEXT", // 1278
    "glMultiTexEnvfEXT", // 1279
    "glMultiTexEnvfvEXT", // 1280
    "glMultiTexEnviEXT", // 1281
    "glMultiTexEnvivEXT", // 1282
    "glMultiTexGendEXT", // 1283
    "glMultiTexGendvEXT", // 1284
    "glMultiTexGenfEXT", // 1285
    "glMultiTexGenfvEXT", // 1286
    "glMultiTexGeniEXT", // 1287
    "glMultiTexGenivEXT", // 1288
    "glMultiTexImage1DEXT", // 1289
    "glMultiTexImage2DEXT", // 1290
    "glMultiTexImage3DEXT", // 1291
    "glMultiTexParameterIivEXT", // 1292
    "glMultiTexParameterIuivEXT", // 1293
    "glMultiTexParameterfEXT", // 1294
    "glMultiTexParameterfvEXT", // 1295
    "glMultiTexParameteriEXT", // 1296
    "glMultiTexParameterivEXT", // 1297
    "glMultiTexRenderbufferEXT", // 1298
    "glMultiTexSubImage1DEXT", // 1299
    "glMultiTexSubImage2DEXT", // 1300
    "glMultiTexSubImage3DEXT", // 1301
    "glMulticastBarrierNV", // 1302
    "glMulticastBlitFramebufferNV", // 1303
    "glMulticastBufferSubDataNV", // 1304
    "glMulticastCopyBufferSubDataNV", // 1305
    "glMulticastCopyImageSubDataNV", // 1306
    "glMulticastFramebufferSampleLocationsfvNV", // 1307
    "glMulticastGetQueryObjecti64vNV", // 1308
    "glMulticastGetQueryObjectivNV", // 1309
    "glMulticastGetQueryObjectui64vNV", // 1310
    "glMulticastGetQueryObjectuivNV", // 1311
    "glMulticastScissorArrayvNVX", // 1312
    "glMulticastViewportArrayvNVX", // 1313
    "glMulticastViewportPositionWScaleNVX", // 1314
    "glMulticastWaitSyncNV", // 1315
    "glNamedBufferAttachMemoryNV", // 1316
    "glNamedBufferData", // 1317
    "glNamedBufferDataEXT", // 1318
    "glNamedBufferPageCommitmentARB", // 1319
    "glNamedBufferPageCommitmentEXT", // 1320
    "glNamedBufferPageCommitmentMemNV", // 1321
    "glNamedBufferStorage", // 1322
    "glNamedBufferStorageEXT", // 1323
    "glNamedBufferStorageExternalEXT", // 1324
    "glNamedBufferStorageMemEXT", // 1325
    "glNamedBufferSubData", // 1326
    "glNamedBufferSubDataEXT", // 1327
    "glNamedCopyBufferSubDataEXT", // 1328
    "glNamedFramebufferDrawBuffer", // 1329
    "glNamedFramebufferDrawBuffers", // 1330
    "glNamedFramebufferParameteri", // 1331
    "glNamedFramebufferParameteriEXT", // 1332
    "glNamedFramebufferReadBuffer", // 1333
    "glNamedFramebufferRenderbuffer", // 1334
    "glNamedFramebufferRenderbufferEXT", // 1335
    "glNamedFramebufferSampleLocationsfvARB", // 1336
    "glNamedFramebufferSampleLocationsfvNV", // 1337
    "glNamedFramebufferSamplePositionsfvAMD", // 1338
    "glNamedFramebufferTexture", // 1339
    "glNamedFramebufferTexture1DEXT", // 1340
    "glNamedFramebufferTexture2DEXT", // 1341
    "glNamedFramebufferTexture3DEXT", // 1342
    "glNamedFramebufferTextureEXT", // 1343
    "glNamedFramebufferTextureFaceEXT", // 1344
    "glNamedFramebufferTextureLayer", // 1345
    "glNamedFramebufferTextureLayerEXT", // 1346
    "glNamedProgramLocalParameter4dEXT", // 1347
    "glNamedProgramLocalParameter4dvEXT", // 1348
    "glNamedProgramLocalParameter4fEXT", // 1349
    "glNamedProgramLocalParameter4fvEXT", // 1350
    "glNamedProgramLocalParameterI4iEXT", // 1351
    "glNamedProgramLocalParameterI4ivEXT", // 1352
    "glNamedProgramLocalParameterI4uiEXT", // 1353
    "glNamedProgramLocalParameterI4uivEXT", // 1354
    "glNamedProgramLocalParameters4fvEXT", // 1355
    "glNamedProgramLocalParametersI4ivEXT", // 1356
    "glNamedProgramLocalParametersI4uivEXT", // 1357
    "glNamedProgramStringEXT", // 1358
    "glNamedRenderbufferStorage", // 1359
    "glNamedRenderbufferStorageEXT", // 1360
    "glNamedRenderbufferStorageMultisample", // 1361
    "glNamedRenderbufferStorageMultisampleAdvancedAMD", // 1362
    "glNamedRenderbufferStorageMultisampleCoverageEXT", // 1363
    "glNamedRenderbufferStorageMultisampleEXT", // 1364
    "glNamedStringARB", // 1365
    "glNewObjectBufferATI", // 1366
    "glNormal3fVertex3fSUN", // 1367
    "glNormal3fVertex3fvSUN", // 1368
    "glNormal3hNV", // 1369
    "glNormal3hvNV", // 1370
    "glNormal3xOES", // 1371
    "glNormal3xvOES", // 1372
    "glNormalFormatNV", // 1373
    "glNormalPointerEXT", // 1374
    "glNormalPointerListIBM", // 1375
    "glNormalPointervINTEL", // 1376
    "glNormalStream3bATI", // 1377
    "glNormalStream3bvATI", // 1378
    "glNormalStream3dATI", // 1379
    "glNormalStream3dvATI", // 1380
    "glNormalStream3fATI", // 1381
    "glNormalStream3fvATI", // 1382
    "glNormalStream3iATI", // 1383
    "glNormalStream3ivATI", // 1384
    "glNormalStream3sATI", // 1385
    "glNormalStream3svATI", // 1386
    "glObjectLabel", // 1387
    "glObjectPtrLabel", // 1388
    "glObjectPurgeableAPPLE", // 1389
    "glObjectUnpurgeableAPPLE", // 1390
    "glOrthofOES", // 1391
    "glOrthoxOES", // 1392
    "glPNTrianglesfATI", // 1393
    "glPNTrianglesiATI", // 1394
    "glPassTexCoordATI", // 1395
    "glPassThroughxOES", // 1396
    "glPatchParameterfv", // 1397
    "glPatchParameteri", // 1398
    "glPathCommandsNV", // 1399
    "glPathCoordsNV", // 1400
    "glPathCoverDepthFuncNV", // 1401
    "glPathDashArrayNV", // 1402
    "glPathGlyphIndexArrayNV", // 1403
    "glPathGlyphIndexRangeNV", // 1404
    "glPathGlyphRangeNV", // 1405
    "glPathGlyphsNV", // 1406
    "glPathMemoryGlyphIndexArrayNV", // 1407
    "glPathParameterfNV", // 1408
    "glPathParameterfvNV", // 1409
    "glPathParameteriNV", // 1410
    "glPathParameterivNV", // 1411
    "glPathStencilDepthOffsetNV", // 1412
    "glPathStencilFuncNV", // 1413
    "glPathStringNV", // 1414
    "glPathSubCommandsNV", // 1415
    "glPathSubCoordsNV", // 1416
    "glPauseTransformFeedback", // 1417
    "glPauseTransformFeedbackNV", // 1418
    "glPixelDataRangeNV", // 1419
    "glPixelMapx", // 1420
    "glPixelStoref", // 1421
    "glPixelStorei", // 1422
    "glPixelStorex", // 1423
    "glPixelTexGenParameterfSGIS", // 1424
    "glPixelTexGenParameterfvSGIS", // 1425
    "glPixelTexGenParameteriSGIS", // 1426
    "glPixelTexGenParameterivSGIS", // 1427
    "glPixelTexGenSGIX", // 1428
    "glPixelTransferxOES", // 1429
    "glPixelTransformParameterfEXT", // 1430
    "glPixelTransformParameterfvEXT", // 1431
    "glPixelTransformParameteriEXT", // 1432
    "glPixelTransformParameterivEXT", // 1433
    "glPixelZoomxOES", // 1434
    "glPointAlongPathNV", // 1435
    "glPointParameterf", // 1436
    "glPointParameterfARB", // 1437
    "glPointParameterfEXT", // 1438
    "glPointParameterfSGIS", // 1439
    "glPointParameterfv", // 1440
    "glPointParameterfvARB", // 1441
    "glPointParameterfvEXT", // 1442
    "glPointParameterfvSGIS", // 1443
    "glPointParameteri", // 1444
    "glPointParameteriNV", // 1445
    "glPointParameteriv", // 1446
    "glPointParameterivNV", // 1447
    "glPointParameterxvOES", // 1448
    "glPointSize", // 1449
    "glPointSizexOES", // 1450
    "glPollAsyncSGIX", // 1451
    "glPollInstrumentsSGIX", // 1452
    "glPolygonMode", // 1453
    "glPolygonOffset", // 1454
    "glPolygonOffsetClamp", // 1455
    "glPolygonOffsetClampEXT", // 1456
    "glPolygonOffsetEXT", // 1457
    "glPolygonOffsetxOES", // 1458
    "glPopDebugGroup", // 1459
    "glPopGroupMarkerEXT", // 1460
    "glPresentFrameDualFillNV", // 1461
    "glPresentFrameKeyedNV", // 1462
    "glPrimitiveBoundingBoxARB", // 1463
    "glPrimitiveRestartIndex", // 1464
    "glPrimitiveRestartIndexNV", // 1465
    "glPrimitiveRestartNV", // 1466
    "glPrioritizeTexturesEXT", // 1467
    "glPrioritizeTexturesxOES", // 1468
    "glProgramBinary", // 1469
    "glProgramBufferParametersIivNV", // 1470
    "glProgramBufferParametersIuivNV", // 1471
    "glProgramBufferParametersfvNV", // 1472
    "glProgramEnvParameter4dARB", // 1473
    "glProgramEnvParameter4dvARB", // 1474
    "glProgramEnvParameter4fARB", // 1475
    "glProgramEnvParameter4fvARB", // 1476
    "glProgramEnvParameterI4iNV", // 1477
    "glProgramEnvParameterI4ivNV", // 1478
    "glProgramEnvParameterI4uiNV", // 1479
    "glProgramEnvParameterI4uivNV", // 1480
    "glProgramEnvParameters4fvEXT", // 1481
    "glProgramEnvParametersI4ivNV", // 1482
    "glProgramEnvParametersI4uivNV", // 1483
    "glProgramLocalParameter4dARB", // 1484
    "glProgramLocalParameter4dvARB", // 1485
    "glProgramLocalParameter4fARB", // 1486
    "glProgramLocalParameter4fvARB", // 1487
    "glProgramLocalParameterI4iNV", // 1488
    "glProgramLocalParameterI4ivNV", // 1489
    "glProgramLocalParameterI4uiNV", // 1490
    "glProgramLocalParameterI4uivNV", // 1491
    "glProgramLocalParameters4fvEXT", // 1492
    "glProgramLocalParametersI4ivNV", // 1493
    "glProgramLocalParametersI4uivNV", // 1494
    "glProgramNamedParameter4dNV", // 1495
    "glProgramNamedParameter4dvNV", // 1496
    "glProgramNamedParameter4fNV", // 1497
    "glProgramNamedParameter4fvNV", // 1498
    "glProgramParameter4dNV", // 1499
    "glProgramParameter4dvNV", // 1500
    "glProgramParameter4fNV", // 1501
    "glProgramParameter4fvNV", // 1502
    "glProgramParameteri", // 1503
    "glProgramParameteriARB", // 1504
    "glProgramParameteriEXT", // 1505
    "glProgramParameters4dvNV", // 1506
    "glProgramParameters4fvNV", // 1507
    "glProgramPathFragmentInputGenNV", // 1508
    "glProgramStringARB", // 1509
    "glProgramSubroutineParametersuivNV", // 1510
    "glProgramUniform1d", // 1511
    "glProgramUniform1dEXT", // 1512
    "glProgramUniform1dv", // 1513
    "glProgramUniform1dvEXT", // 1514
    "glProgramUniform1f", // 1515
    "glProgramUniform1fEXT", // 1516
    "glProgramUniform1fv", // 1517
    "glProgramUniform1fvEXT", // 1518
    "glProgramUniform1i", // 1519
    "glProgramUniform1i64ARB", // 1520
    "glProgramUniform1i64NV", // 1521
    "glProgramUniform1i64vARB", // 1522
    "glProgramUniform1i64vNV", // 1523
    "glProgramUniform1iEXT", // 1524
    "glProgramUniform1iv", // 1525
    "glProgramUniform1ivEXT", // 1526
    "glProgramUniform1ui", // 1527
    "glProgramUniform1ui64ARB", // 1528
    "glProgramUniform1ui64NV", // 1529
    "glProgramUniform1ui64vARB", // 1530
    "glProgramUniform1ui64vNV", // 1531
    "glProgramUniform1uiEXT", // 1532
    "glProgramUniform1uiv", // 1533
    "glProgramUniform1uivEXT", // 1534
    "glProgramUniform2d", // 1535
    "glProgramUniform2dEXT", // 1536
    "glProgramUniform2dv", // 1537
    "glProgramUniform2dvEXT", // 1538
    "glProgramUniform2f", // 1539
    "glProgramUniform2fEXT", // 1540
    "glProgramUniform2fv", // 1541
    "glProgramUniform2fvEXT", // 1542
    "glProgramUniform2i", // 1543
    "glProgramUniform2i64ARB", // 1544
    "glProgramUniform2i64NV", // 1545
    "glProgramUniform2i64vARB", // 1546
    "glProgramUniform2i64vNV", // 1547
    "glProgramUniform2iEXT", // 1548
    "glProgramUniform2iv", // 1549
    "glProgramUniform2ivEXT", // 1550
    "glProgramUniform2ui", // 1551
    "glProgramUniform2ui64ARB", // 1552
    "glProgramUniform2ui64NV", // 1553
    "glProgramUniform2ui64vARB", // 1554
    "glProgramUniform2ui64vNV", // 1555
    "glProgramUniform2uiEXT", // 1556
    "glProgramUniform2uiv", // 1557
    "glProgramUniform2uivEXT", // 1558
    "glProgramUniform3d", // 1559
    "glProgramUniform3dEXT", // 1560
    "glProgramUniform3dv", // 1561
    "glProgramUniform3dvEXT", // 1562
    "glProgramUniform3f", // 1563
    "glProgramUniform3fEXT", // 1564
    "glProgramUniform3fv", // 1565
    "glProgramUniform3fvEXT", // 1566
    "glProgramUniform3i", // 1567
    "glProgramUniform3i64ARB", // 1568
    "glProgramUniform3i64NV", // 1569
    "glProgramUniform3i64vARB", // 1570
    "glProgramUniform3i64vNV", // 1571
    "glProgramUniform3iEXT", // 1572
    "glProgramUniform3iv", // 1573
    "glProgramUniform3ivEXT", // 1574
    "glProgramUniform3ui", // 1575
    "glProgramUniform3ui64ARB", // 1576
    "glProgramUniform3ui64NV", // 1577
    "glProgramUniform3ui64vARB", // 1578
    "glProgramUniform3ui64vNV", // 1579
    "glProgramUniform3uiEXT", // 1580
    "glProgramUniform3uiv", // 1581
    "glProgramUniform3uivEXT", // 1582
    "glProgramUniform4d", // 1583
    "glProgramUniform4dEXT", // 1584
    "glProgramUniform4dv", // 1585
    "glProgramUniform4dvEXT", // 1586
    "glProgramUniform4f", // 1587
    "glProgramUniform4fEXT", // 1588
    "glProgramUniform4fv", // 1589
    "glProgramUniform4fvEXT", // 1590
    "glProgramUniform4i", // 1591
    "glProgramUniform4i64ARB", // 1592
    "glProgramUniform4i64NV", // 1593
    "glProgramUniform4i64vARB", // 1594
    "glProgramUniform4i64vNV", // 1595
    "glProgramUniform4iEXT", // 1596
    "glProgramUniform4iv", // 1597
    "glProgramUniform4ivEXT", // 1598
    "glProgramUniform4ui", // 1599
    "glProgramUniform4ui64ARB", // 1600
    "glProgramUniform4ui64NV", // 1601
    "glProgramUniform4ui64vARB", // 1602
    "glProgramUniform4ui64vNV", // 1603
    "glProgramUniform4uiEXT", // 1604
    "glProgramUniform4uiv", // 1605
    "glProgramUniform4uivEXT", // 1606
    "glProgramUniformHandleui64ARB", // 1607
    "glProgramUniformHandleui64NV", // 1608
    "glProgramUniformHandleui64vARB", // 1609
    "glProgramUniformHandleui64vNV", // 1610
    "glProgramUniformMatrix2dv", // 1611
    "glProgramUniformMatrix2dvEXT", // 1612
    "glProgramUniformMatrix2fv", // 1613
    "glProgramUniformMatrix2fvEXT", // 1614
    "glProgramUniformMatrix2x3dv", // 1615
    "glProgramUniformMatrix2x3dvEXT", // 1616
    "glProgramUniformMatrix2x3fv", // 1617
    "glProgramUniformMatrix2x3fvEXT", // 1618
    "glProgramUniformMatrix2x4dv", // 1619
    "glProgramUniformMatrix2x4dvEXT", // 1620
    "glProgramUniformMatrix2x4fv", // 1621
    "glProgramUniformMatrix2x4fvEXT", // 1622
    "glProgramUniformMatrix3dv", // 1623
    "glProgramUniformMatrix3dvEXT", // 1624
    "glProgramUniformMatrix3fv", // 1625
    "glProgramUniformMatrix3fvEXT", // 1626
    "glProgramUniformMatrix3x2dv", // 1627
    "glProgramUniformMatrix3x2dvEXT", // 1628
    "glProgramUniformMatrix3x2fv", // 1629
    "glProgramUniformMatrix3x2fvEXT", // 1630
    "glProgramUniformMatrix3x4dv", // 1631
    "glProgramUniformMatrix3x4dvEXT", // 1632
    "glProgramUniformMatrix3x4fv", // 1633
    "glProgramUniformMatrix3x4fvEXT", // 1634
    "glProgramUniformMatrix4dv", // 1635
    "glProgramUniformMatrix4dvEXT", // 1636
    "glProgramUniformMatrix4fv", // 1637
    "glProgramUniformMatrix4fvEXT", // 1638
    "glProgramUniformMatrix4x2dv", // 1639
    "glProgramUniformMatrix4x2dvEXT", // 1640
    "glProgramUniformMatrix4x2fv", // 1641
    "glProgramUniformMatrix4x2fvEXT", // 1642
    "glProgramUniformMatrix4x3dv", // 1643
    "glProgramUniformMatrix4x3dvEXT", // 1644
    "glProgramUniformMatrix4x3fv", // 1645
    "glProgramUniformMatrix4x3fvEXT", // 1646
    "glProgramUniformui64NV", // 1647
    "glProgramUniformui64vNV", // 1648
    "glProgramVertexLimitNV", // 1649
    "glProvokingVertex", // 1650
    "glProvokingVertexEXT", // 1651
    "glPushClientAttribDefaultEXT", // 1652
    "glPushDebugGroup", // 1653
    "glPushGroupMarkerEXT", // 1654
    "glQueryCounter", // 1655
    "glQueryMatrixxOES", // 1656
    "glQueryObjectParameteruiAMD", // 1657
    "glQueryResourceNV", // 1658
    "glQueryResourceTagNV", // 1659
    "glRasterPos2xOES", // 1660
    "glRasterPos2xvOES", // 1661
    "glRasterPos3xOES", // 1662
    "glRasterPos3xvOES", // 1663
    "glRasterPos4xOES", // 1664
    "glRasterPos4xvOES", // 1665
    "glRasterSamplesEXT", // 1666
    "glReadBuffer", // 1667
    "glReadInstrumentsSGIX", // 1668
    "glReadPixels", // 1669
    "glReadnPixels", // 1670
    "glReadnPixelsARB", // 1671
    "glRectxOES", // 1672
    "glRectxvOES", // 1673
    "glReferencePlaneSGIX", // 1674
    "glReleaseKeyedMutexWin32EXT", // 1675
    "glReleaseShaderCompiler", // 1676
    "glRenderGpuMaskNV", // 1677
    "glRenderbufferStorage", // 1678
    "glRenderbufferStorageEXT", // 1679
    "glRenderbufferStorageMultisample", // 1680
    "glRenderbufferStorageMultisampleAdvancedAMD", // 1681
    "glRenderbufferStorageMultisampleCoverageNV", // 1682
    "glRenderbufferStorageMultisampleEXT", // 1683
    "glReplacementCodePointerSUN", // 1684
    "glReplacementCodeubSUN", // 1685
    "glReplacementCodeubvSUN", // 1686
    "glReplacementCodeuiColor3fVertex3fSUN", // 1687
    "glReplacementCodeuiColor3fVertex3fvSUN", // 1688
    "glReplacementCodeuiColor4fNormal3fVertex3fSUN", // 1689
    "glReplacementCodeuiColor4fNormal3fVertex3fvSUN", // 1690
    "glReplacementCodeuiColor4ubVertex3fSUN", // 1691
    "glReplacementCodeuiColor4ubVertex3fvSUN", // 1692
    "glReplacementCodeuiNormal3fVertex3fSUN", // 1693
    "glReplacementCodeuiNormal3fVertex3fvSUN", // 1694
    "glReplacementCodeuiSUN", // 1695
    "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN", // 1696
    "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN", // 1697
    "glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN", // 1698
    "glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN", // 1699
    "glReplacementCodeuiTexCoord2fVertex3fSUN", // 1700
    "glReplacementCodeuiTexCoord2fVertex3fvSUN", // 1701
    "glReplacementCodeuiVertex3fSUN", // 1702
    "glReplacementCodeuiVertex3fvSUN", // 1703
    "glReplacementCodeuivSUN", // 1704
    "glReplacementCodeusSUN", // 1705
    "glReplacementCodeusvSUN", // 1706
    "glRequestResidentProgramsNV", // 1707
    "glResetHistogramEXT", // 1708
    "glResetMemoryObjectParameterNV", // 1709
    "glResetMinmaxEXT", // 1710
    "glResizeBuffersMESA", // 1711
    "glResolveDepthValuesNV", // 1712
    "glResumeTransformFeedback", // 1713
    "glResumeTransformFeedbackNV", // 1714
    "glRotatexOES", // 1715
    "glSampleCoverage", // 1716
    "glSampleCoverageARB", // 1717
    "glSampleMapATI", // 1718
    "glSampleMaskEXT", // 1719
    "glSampleMaskIndexedNV", // 1720
    "glSampleMaskSGIS", // 1721
    "glSampleMaski", // 1722
    "glSamplePatternEXT", // 1723
    "glSamplePatternSGIS", // 1724
    "glSamplerParameterIiv", // 1725
    "glSamplerParameterIuiv", // 1726
    "glSamplerParameterf", // 1727
    "glSamplerParameterfv", // 1728
    "glSamplerParameteri", // 1729
    "glSamplerParameteriv", // 1730
    "glScalexOES", // 1731
    "glScissor", // 1732
    "glScissorArrayv", // 1733
    "glScissorExclusiveArrayvNV", // 1734
    "glScissorExclusiveNV", // 1735
    "glScissorIndexed", // 1736
    "glScissorIndexedv", // 1737
    "glSecondaryColor3bEXT", // 1738
    "glSecondaryColor3bvEXT", // 1739
    "glSecondaryColor3dEXT", // 1740
    "glSecondaryColor3dvEXT", // 1741
    "glSecondaryColor3fEXT", // 1742
    "glSecondaryColor3fvEXT", // 1743
    "glSecondaryColor3hNV", // 1744
    "glSecondaryColor3hvNV", // 1745
    "glSecondaryColor3iEXT", // 1746
    "glSecondaryColor3ivEXT", // 1747
    "glSecondaryColor3sEXT", // 1748
    "glSecondaryColor3svEXT", // 1749
    "glSecondaryColor3ubEXT", // 1750
    "glSecondaryColor3ubvEXT", // 1751
    "glSecondaryColor3uiEXT", // 1752
    "glSecondaryColor3uivEXT", // 1753
    "glSecondaryColor3usEXT", // 1754
    "glSecondaryColor3usvEXT", // 1755
    "glSecondaryColorFormatNV", // 1756
    "glSecondaryColorPointerEXT", // 1757
    "glSecondaryColorPointerListIBM", // 1758
    "glSelectPerfMonitorCountersAMD", // 1759
    "glSemaphoreParameterivNV", // 1760
    "glSemaphoreParameterui64vEXT", // 1761
    "glSeparableFilter2DEXT", // 1762
    "glSetFenceAPPLE", // 1763
    "glSetFenceNV", // 1764
    "glSetFragmentShaderConstantATI", // 1765
    "glSetInvariantEXT", // 1766
    "glSetLocalConstantEXT", // 1767
    "glSetMultisamplefvAMD", // 1768
    "glShaderBinary", // 1769
    "glShaderOp1EXT", // 1770
    "glShaderOp2EXT", // 1771
    "glShaderOp3EXT", // 1772
    "glShaderSource", // 1773
    "glShaderSourceARB", // 1774
    "glShaderStorageBlockBinding", // 1775
    "glShadingRateImageBarrierNV", // 1776
    "glShadingRateImagePaletteNV", // 1777
    "glShadingRateSampleOrderCustomNV", // 1778
    "glShadingRateSampleOrderNV", // 1779
    "glSharpenTexFuncSGIS", // 1780
    "glSignalSemaphoreEXT", // 1781
    "glSignalSemaphoreui64NVX", // 1782
    "glSignalVkFenceNV", // 1783
    "glSignalVkSemaphoreNV", // 1784
    "glSpecializeShader", // 1785
    "glSpecializeShaderARB", // 1786
    "glSpriteParameterfSGIX", // 1787
    "glSpriteParameterfvSGIX", // 1788
    "glSpriteParameteriSGIX", // 1789
    "glSpriteParameterivSGIX", // 1790
    "glStartInstrumentsSGIX", // 1791
    "glStateCaptureNV", // 1792
    "glStencilClearTagEXT", // 1793
    "glStencilFillPathInstancedNV", // 1794
    "glStencilFillPathNV", // 1795
    "glStencilFunc", // 1796
    "glStencilFuncSeparate", // 1797
    "glStencilFuncSeparateATI", // 1798
    "glStencilMask", // 1799
    "glStencilMaskSeparate", // 1800
    "glStencilOp", // 1801
    "glStencilOpSeparate", // 1802
    "glStencilOpSeparateATI", // 1803
    "glStencilOpValueAMD", // 1804
    "glStencilStrokePathInstancedNV", // 1805
    "glStencilStrokePathNV", // 1806
    "glStencilThenCoverFillPathInstancedNV", // 1807
    "glStencilThenCoverFillPathNV", // 1808
    "glStencilThenCoverStrokePathInstancedNV", // 1809
    "glStencilThenCoverStrokePathNV", // 1810
    "glStopInstrumentsSGIX", // 1811
    "glStringMarkerGREMEDY", // 1812
    "glSubpixelPrecisionBiasNV", // 1813
    "glSwizzleEXT", // 1814
    "glSyncTextureINTEL", // 1815
    "glTagSampleBufferSGIX", // 1816
    "glTangent3bEXT", // 1817
    "glTangent3bvEXT", // 1818
    "glTangent3dEXT", // 1819
    "glTangent3dvEXT", // 1820
    "glTangent3fEXT", // 1821
    "glTangent3fvEXT", // 1822
    "glTangent3iEXT", // 1823
    "glTangent3ivEXT", // 1824
    "glTangent3sEXT", // 1825
    "glTangent3svEXT", // 1826
    "glTangentPointerEXT", // 1827
    "glTbufferMask3DFX", // 1828
    "glTessellationFactorAMD", // 1829
    "glTessellationModeAMD", // 1830
    "glTestFenceAPPLE", // 1831
    "glTestFenceNV", // 1832
    "glTestObjectAPPLE", // 1833
    "glTexAttachMemoryNV", // 1834
    "glTexBuffer", // 1835
    "glTexBufferARB", // 1836
    "glTexBufferEXT", // 1837
    "glTexBufferRange", // 1838
    "glTexBumpParameterfvATI", // 1839
    "glTexBumpParameterivATI", // 1840
    "glTexCoord1bOES", // 1841
    "glTexCoord1bvOES", // 1842
    "glTexCoord1hNV", // 1843
    "glTexCoord1hvNV", // 1844
    "glTexCoord1xOES", // 1845
    "glTexCoord1xvOES", // 1846
    "glTexCoord2bOES", // 1847
    "glTexCoord2bvOES", // 1848
    "glTexCoord2fColor3fVertex3fSUN", // 1849
    "glTexCoord2fColor3fVertex3fvSUN", // 1850
    "glTexCoord2fColor4fNormal3fVertex3fSUN", // 1851
    "glTexCoord2fColor4fNormal3fVertex3fvSUN", // 1852
    "glTexCoord2fColor4ubVertex3fSUN", // 1853
    "glTexCoord2fColor4ubVertex3fvSUN", // 1854
    "glTexCoord2fNormal3fVertex3fSUN", // 1855
    "glTexCoord2fNormal3fVertex3fvSUN", // 1856
    "glTexCoord2fVertex3fSUN", // 1857
    "glTexCoord2fVertex3fvSUN", // 1858
    "glTexCoord2hNV", // 1859
    "glTexCoord2hvNV", // 1860
    "glTexCoord2xOES", // 1861
    "glTexCoord2xvOES", // 1862
    "glTexCoord3bOES", // 1863
    "glTexCoord3bvOES", // 1864
    "glTexCoord3hNV", // 1865
    "glTexCoord3hvNV", // 1866
    "glTexCoord3xOES", // 1867
    "glTexCoord3xvOES", // 1868
    "glTexCoord4bOES", // 1869
    "glTexCoord4bvOES", // 1870
    "glTexCoord4fColor4fNormal3fVertex4fSUN", // 1871
    "glTexCoord4fColor4fNormal3fVertex4fvSUN", // 1872
    "glTexCoord4fVertex4fSUN", // 1873
    "glTexCoord4fVertex4fvSUN", // 1874
    "glTexCoord4hNV", // 1875
    "glTexCoord4hvNV", // 1876
    "glTexCoord4xOES", // 1877
    "glTexCoord4xvOES", // 1878
    "glTexCoordFormatNV", // 1879
    "glTexCoordPointerEXT", // 1880
    "glTexCoordPointerListIBM", // 1881
    "glTexCoordPointervINTEL", // 1882
    "glTexEnvxOES", // 1883
    "glTexEnvxvOES", // 1884
    "glTexFilterFuncSGIS", // 1885
    "glTexGenxOES", // 1886
    "glTexGenxvOES", // 1887
    "glTexImage1D", // 1888
    "glTexImage2D", // 1889
    "glTexImage2DExternalANGLE", // 1890
    "glTexImage2DMultisample", // 1891
    "glTexImage2DMultisampleCoverageNV", // 1892
    "glTexImage3D", // 1893
    "glTexImage3DEXT", // 1894
    "glTexImage3DMultisample", // 1895
    "glTexImage3DMultisampleCoverageNV", // 1896
    "glTexImage4DSGIS", // 1897
    "glTexPageCommitmentARB", // 1898
    "glTexPageCommitmentMemNV", // 1899
    "glTexParameterIiv", // 1900
    "glTexParameterIivEXT", // 1901
    "glTexParameterIuiv", // 1902
    "glTexParameterIuivEXT", // 1903
    "glTexParameterf", // 1904
    "glTexParameterfv", // 1905
    "glTexParameteri", // 1906
    "glTexParameteriv", // 1907
    "glTexParameterxOES", // 1908
    "glTexParameterxvOES", // 1909
    "glTexRenderbufferNV", // 1910
    "glTexStorage1D", // 1911
    "glTexStorage1DEXT", // 1912
    "glTexStorage2D", // 1913
    "glTexStorage2DEXT", // 1914
    "glTexStorage2DMultisample", // 1915
    "glTexStorage3D", // 1916
    "glTexStorage3DEXT", // 1917
    "glTexStorage3DMultisample", // 1918
    "glTexStorageMem1DEXT", // 1919
    "glTexStorageMem2DEXT", // 1920
    "glTexStorageMem2DMultisampleEXT", // 1921
    "glTexStorageMem3DEXT", // 1922
    "glTexStorageMem3DMultisampleEXT", // 1923
    "glTexStorageMemFlags2DANGLE", // 1924
    "glTexStorageMemFlags2DMultisampleANGLE", // 1925
    "glTexStorageMemFlags3DANGLE", // 1926
    "glTexStorageMemFlags3DMultisampleANGLE", // 1927
    "glTexStorageSparseAMD", // 1928
    "glTexSubImage1D", // 1929
    "glTexSubImage1DEXT", // 1930
    "glTexSubImage2D", // 1931
    "glTexSubImage2DEXT", // 1932
    "glTexSubImage3D", // 1933
    "glTexSubImage3DEXT", // 1934
    "glTexSubImage4DSGIS", // 1935
    "glTextureAttachMemoryNV", // 1936
    "glTextureBarrier", // 1937
    "glTextureBarrierNV", // 1938
    "glTextureBuffer", // 1939
    "glTextureBufferEXT", // 1940
    "glTextureBufferRange", // 1941
    "glTextureBufferRangeEXT", // 1942
    "glTextureColorMaskSGIS", // 1943
    "glTextureImage1DEXT", // 1944
    "glTextureImage2DEXT", // 1945
    "glTextureImage2DMultisampleCoverageNV", // 1946
    "glTextureImage2DMultisampleNV", // 1947
    "glTextureImage3DEXT", // 1948
    "glTextureImage3DMultisampleCoverageNV", // 1949
    "glTextureImage3DMultisampleNV", // 1950
    "glTextureLightEXT", // 1951
    "glTextureMaterialEXT", // 1952
    "glTextureNormalEXT", // 1953
    "glTexturePageCommitmentEXT", // 1954
    "glTexturePageCommitmentMemNV", // 1955
    "glTextureParameterIiv", // 1956
    "glTextureParameterIivEXT", // 1957
    "glTextureParameterIuiv", // 1958
    "glTextureParameterIuivEXT", // 1959
    "glTextureParameterf", // 1960
    "glTextureParameterfEXT", // 1961
    "glTextureParameterfv", // 1962
    "glTextureParameterfvEXT", // 1963
    "glTextureParameteri", // 1964
    "glTextureParameteriEXT", // 1965
    "glTextureParameteriv", // 1966
    "glTextureParameterivEXT", // 1967
    "glTextureRangeAPPLE", // 1968
    "glTextureRenderbufferEXT", // 1969
    "glTextureStorage1D", // 1970
    "glTextureStorage1DEXT", // 1971
    "glTextureStorage2D", // 1972
    "glTextureStorage2DEXT", // 1973
    "glTextureStorage2DMultisample", // 1974
    "glTextureStorage2DMultisampleEXT", // 1975
    "glTextureStorage3D", // 1976
    "glTextureStorage3DEXT", // 1977
    "glTextureStorage3DMultisample", // 1978
    "glTextureStorage3DMultisampleEXT", // 1979
    "glTextureStorageMem1DEXT", // 1980
    "glTextureStorageMem2DEXT", // 1981
    "glTextureStorageMem2DMultisampleEXT", // 1982
    "glTextureStorageMem3DEXT", // 1983
    "glTextureStorageMem3DMultisampleEXT", // 1984
    "glTextureStorageSparseAMD", // 1985
    "glTextureSubImage1D", // 1986
    "glTextureSubImage1DEXT", // 1987
    "glTextureSubImage2D", // 1988
    "glTextureSubImage2DEXT", // 1989
    "glTextureSubImage3D", // 1990
    "glTextureSubImage3DEXT", // 1991
    "glTextureView", // 1992
    "glTrackMatrixNV", // 1993
    "glTransformFeedbackAttribsNV", // 1994
    "glTransformFeedbackBufferBase", // 1995
    "glTransformFeedbackBufferRange", // 1996
    "glTransformFeedbackStreamAttribsNV", // 1997
    "glTransformFeedbackVaryings", // 1998
    "glTransformFeedbackVaryingsEXT", // 1999
    "glTransformFeedbackVaryingsNV", // 2000
    "glTransformPathNV", // 2001
    "glTranslatexOES", // 2002
    "glUniform1d", // 2003
    "glUniform1dv", // 2004
    "glUniform1f", // 2005
    "glUniform1fARB", // 2006
    "glUniform1fv", // 2007
    "glUniform1fvARB", // 2008
    "glUniform1i", // 2009
    "glUniform1i64ARB", // 2010
    "glUniform1i64NV", // 2011
    "glUniform1i64vARB", // 2012
    "glUniform1i64vNV", // 2013
    "glUniform1iARB", // 2014
    "glUniform1iv", // 2015
    "glUniform1ivARB", // 2016
    "glUniform1ui", // 2017
    "glUniform1ui64ARB", // 2018
    "glUniform1ui64NV", // 2019
    "glUniform1ui64vARB", // 2020
    "glUniform1ui64vNV", // 2021
    "glUniform1uiEXT", // 2022
    "glUniform1uiv", // 2023
    "glUniform1uivEXT", // 2024
    "glUniform2d", // 2025
    "glUniform2dv", // 2026
    "glUniform2f", // 2027
    "glUniform2fARB", // 2028
    "glUniform2fv", // 2029
    "glUniform2fvARB", // 2030
    "glUniform2i", // 2031
    "glUniform2i64ARB", // 2032
    "glUniform2i64NV", // 2033
    "glUniform2i64vARB", // 2034
    "glUniform2i64vNV", // 2035
    "glUniform2iARB", // 2036
    "glUniform2iv", // 2037
    "glUniform2ivARB", // 2038
    "glUniform2ui", // 2039
    "glUniform2ui64ARB", // 2040
    "glUniform2ui64NV", // 2041
    "glUniform2ui64vARB", // 2042
    "glUniform2ui64vNV", // 2043
    "glUniform2uiEXT", // 2044
    "glUniform2uiv", // 2045
    "glUniform2uivEXT", // 2046
    "glUniform3d", // 2047
    "glUniform3dv", // 2048
    "glUniform3f", // 2049
    "glUniform3fARB", // 2050
    "glUniform3fv", // 2051
    "glUniform3fvARB", // 2052
    "glUniform3i", // 2053
    "glUniform3i64ARB", // 2054
    "glUniform3i64NV", // 2055
    "glUniform3i64vARB", // 2056
    "glUniform3i64vNV", // 2057
    "glUniform3iARB", // 2058
    "glUniform3iv", // 2059
    "glUniform3ivARB", // 2060
    "glUniform3ui", // 2061
    "glUniform3ui64ARB", // 2062
    "glUniform3ui64NV", // 2063
    "glUniform3ui64vARB", // 2064
    "glUniform3ui64vNV", // 2065
    "glUniform3uiEXT", // 2066
    "glUniform3uiv", // 2067
    "glUniform3uivEXT", // 2068
    "glUniform4d", // 2069
    "glUniform4dv", // 2070
    "glUniform4f", // 2071
    "glUniform4fARB", // 2072
    "glUniform4fv", // 2073
    "glUniform4fvARB", // 2074
    "glUniform4i", // 2075
    "glUniform4i64ARB", // 2076
    "glUniform4i64NV", // 2077
    "glUniform4i64vARB", // 2078
    "glUniform4i64vNV", // 2079
    "glUniform4iARB", // 2080
    "glUniform4iv", // 2081
    "glUniform4ivARB", // 2082
    "glUniform4ui", // 2083
    "glUniform4ui64ARB", // 2084
    "glUniform4ui64NV", // 2085
    "glUniform4ui64vARB", // 2086
    "glUniform4ui64vNV", // 2087
    "glUniform4uiEXT", // 2088
    "glUniform4uiv", // 2089
    "glUniform4uivEXT", // 2090
    "glUniformBlockBinding", // 2091
    "glUniformBufferEXT", // 2092
    "glUniformHandleui64ARB", // 2093
    "glUniformHandleui64NV", // 2094
    "glUniformHandleui64vARB", // 2095
    "glUniformHandleui64vNV", // 2096
    "glUniformMatrix2dv", // 2097
    "glUniformMatrix2fv", // 2098
    "glUniformMatrix2fvARB", // 2099
    "glUniformMatrix2x3dv", // 2100
    "glUniformMatrix2x3fv", // 2101
    "glUniformMatrix2x4dv", // 2102
    "glUniformMatrix2x4fv", // 2103
    "glUniformMatrix3dv", // 2104
    "glUniformMatrix3fv", // 2105
    "glUniformMatrix3fvARB", // 2106
    "glUniformMatrix3x2dv", // 2107
    "glUniformMatrix3x2fv", // 2108
    "glUniformMatrix3x4dv", // 2109
    "glUniformMatrix3x4fv", // 2110
    "glUniformMatrix4dv", // 2111
    "glUniformMatrix4fv", // 2112
    "glUniformMatrix4fvARB", // 2113
    "glUniformMatrix4x2dv", // 2114
    "glUniformMatrix4x2fv", // 2115
    "glUniformMatrix4x3dv", // 2116
    "glUniformMatrix4x3fv", // 2117
    "glUniformSubroutinesuiv", // 2118
    "glUniformui64NV", // 2119
    "glUniformui64vNV", // 2120
    "glUnlockArraysEXT", // 2121
    "glUnmapBuffer", // 2122
    "glUnmapBufferARB", // 2123
    "glUnmapNamedBuffer", // 2124
    "glUnmapNamedBufferEXT", // 2125
    "glUnmapObjectBufferATI", // 2126
    "glUnmapTexture2DINTEL", // 2127
    "glUpdateObjectBufferATI", // 2128
    "glUploadGpuMaskNVX", // 2129
    "glUseProgram", // 2130
    "glUseProgramObjectARB", // 2131
    "glUseProgramStages", // 2132
    "glUseShaderProgramEXT", // 2133
    "glVDPAUFiniNV", // 2134
    "glVDPAUGetSurfaceivNV", // 2135
    "glVDPAUInitNV", // 2136
    "glVDPAUIsSurfaceNV", // 2137
    "glVDPAUMapSurfacesNV", // 2138
    "glVDPAURegisterOutputSurfaceNV", // 2139
    "glVDPAURegisterVideoSurfaceNV", // 2140
    "glVDPAURegisterVideoSurfaceWithPictureStructureNV", // 2141
    "glVDPAUSurfaceAccessNV", // 2142
    "glVDPAUUnmapSurfacesNV", // 2143
    "glVDPAUUnregisterSurfaceNV", // 2144
    "glValidateProgram", // 2145
    "glValidateProgramARB", // 2146
    "glValidateProgramPipeline", // 2147
    "glVariantArrayObjectATI", // 2148
    "glVariantPointerEXT", // 2149
    "glVariantbvEXT", // 2150
    "glVariantdvEXT", // 2151
    "glVariantfvEXT", // 2152
    "glVariantivEXT", // 2153
    "glVariantsvEXT", // 2154
    "glVariantubvEXT", // 2155
    "glVariantuivEXT", // 2156
    "glVariantusvEXT", // 2157
    "glVertex2bOES", // 2158
    "glVertex2bvOES", // 2159
    "glVertex2hNV", // 2160
    "glVertex2hvNV", // 2161
    "glVertex2xOES", // 2162
    "glVertex2xvOES", // 2163
    "glVertex3bOES", // 2164
    "glVertex3bvOES", // 2165
    "glVertex3hNV", // 2166
    "glVertex3hvNV", // 2167
    "glVertex3xOES", // 2168
    "glVertex3xvOES", // 2169
    "glVertex4bOES", // 2170
    "glVertex4bvOES", // 2171
    "glVertex4hNV", // 2172
    "glVertex4hvNV", // 2173
    "glVertex4xOES", // 2174
    "glVertex4xvOES", // 2175
    "glVertexArrayAttribBinding", // 2176
    "glVertexArrayAttribFormat", // 2177
    "glVertexArrayAttribIFormat", // 2178
    "glVertexArrayAttribLFormat", // 2179
    "glVertexArrayBindVertexBufferEXT", // 2180
    "glVertexArrayBindingDivisor", // 2181
    "glVertexArrayColorOffsetEXT", // 2182
    "glVertexArrayEdgeFlagOffsetEXT", // 2183
    "glVertexArrayElementBuffer", // 2184
    "glVertexArrayFogCoordOffsetEXT", // 2185
    "glVertexArrayIndexOffsetEXT", // 2186
    "glVertexArrayMultiTexCoordOffsetEXT", // 2187
    "glVertexArrayNormalOffsetEXT", // 2188
    "glVertexArrayParameteriAPPLE", // 2189
    "glVertexArrayRangeAPPLE", // 2190
    "glVertexArrayRangeNV", // 2191
    "glVertexArraySecondaryColorOffsetEXT", // 2192
    "glVertexArrayTexCoordOffsetEXT", // 2193
    "glVertexArrayVertexAttribBindingEXT", // 2194
    "glVertexArrayVertexAttribDivisorEXT", // 2195
    "glVertexArrayVertexAttribFormatEXT", // 2196
    "glVertexArrayVertexAttribIFormatEXT", // 2197
    "glVertexArrayVertexAttribIOffsetEXT", // 2198
    "glVertexArrayVertexAttribLFormatEXT", // 2199
    "glVertexArrayVertexAttribLOffsetEXT", // 2200
    "glVertexArrayVertexAttribOffsetEXT", // 2201
    "glVertexArrayVertexBindingDivisorEXT", // 2202
    "glVertexArrayVertexBuffer", // 2203
    "glVertexArrayVertexBuffers", // 2204
    "glVertexArrayVertexOffsetEXT", // 2205
    "glVertexAttrib1d", // 2206
    "glVertexAttrib1dARB", // 2207
    "glVertexAttrib1dNV", // 2208
    "glVertexAttrib1dv", // 2209
    "glVertexAttrib1dvARB", // 2210
    "glVertexAttrib1dvNV", // 2211
    "glVertexAttrib1f", // 2212
    "glVertexAttrib1fARB", // 2213
    "glVertexAttrib1fNV", // 2214
    "glVertexAttrib1fv", // 2215
    "glVertexAttrib1fvARB", // 2216
    "glVertexAttrib1fvNV", // 2217
    "glVertexAttrib1hNV", // 2218
    "glVertexAttrib1hvNV", // 2219
    "glVertexAttrib1s", // 2220
    "glVertexAttrib1sARB", // 2221
    "glVertexAttrib1sNV", // 2222
    "glVertexAttrib1sv", // 2223
    "glVertexAttrib1svARB", // 2224
    "glVertexAttrib1svNV", // 2225
    "glVertexAttrib2d", // 2226
    "glVertexAttrib2dARB", // 2227
    "glVertexAttrib2dNV", // 2228
    "glVertexAttrib2dv", // 2229
    "glVertexAttrib2dvARB", // 2230
    "glVertexAttrib2dvNV", // 2231
    "glVertexAttrib2f", // 2232
    "glVertexAttrib2fARB", // 2233
    "glVertexAttrib2fNV", // 2234
    "glVertexAttrib2fv", // 2235
    "glVertexAttrib2fvARB", // 2236
    "glVertexAttrib2fvNV", // 2237
    "glVertexAttrib2hNV", // 2238
    "glVertexAttrib2hvNV", // 2239
    "glVertexAttrib2s", // 2240
    "glVertexAttrib2sARB", // 2241
    "glVertexAttrib2sNV", // 2242
    "glVertexAttrib2sv", // 2243
    "glVertexAttrib2svARB", // 2244
    "glVertexAttrib2svNV", // 2245
    "glVertexAttrib3d", // 2246
    "glVertexAttrib3dARB", // 2247
    "glVertexAttrib3dNV", // 2248
    "glVertexAttrib3dv", // 2249
    "glVertexAttrib3dvARB", // 2250
    "glVertexAttrib3dvNV", // 2251
    "glVertexAttrib3f", // 2252
    "glVertexAttrib3fARB", // 2253
    "glVertexAttrib3fNV", // 2254
    "glVertexAttrib3fv", // 2255
    "glVertexAttrib3fvARB", // 2256
    "glVertexAttrib3fvNV", // 2257
    "glVertexAttrib3hNV", // 2258
    "glVertexAttrib3hvNV", // 2259
    "glVertexAttrib3s", // 2260
    "glVertexAttrib3sARB", // 2261
    "glVertexAttrib3sNV", // 2262
    "glVertexAttrib3sv", // 2263
    "glVertexAttrib3svARB", // 2264
    "glVertexAttrib3svNV", // 2265
    "glVertexAttrib4Nbv", // 2266
    "glVertexAttrib4NbvARB", // 2267
    "glVertexAttrib4Niv", // 2268
    "glVertexAttrib4NivARB", // 2269
    "glVertexAttrib4Nsv", // 2270
    "glVertexAttrib4NsvARB", // 2271
    "glVertexAttrib4Nub", // 2272
    "glVertexAttrib4NubARB", // 2273
    "glVertexAttrib4Nubv", // 2274
    "glVertexAttrib4NubvARB", // 2275
    "glVertexAttrib4Nuiv", // 2276
    "glVertexAttrib4NuivARB", // 2277
    "glVertexAttrib4Nusv", // 2278
    "glVertexAttrib4NusvARB", // 2279
    "glVertexAttrib4bv", // 2280
    "glVertexAttrib4bvARB", // 2281
    "glVertexAttrib4d", // 2282
    "glVertexAttrib4dARB", // 2283
    "glVertexAttrib4dNV", // 2284
    "glVertexAttrib4dv", // 2285
    "glVertexAttrib4dvARB", // 2286
    "glVertexAttrib4dvNV", // 2287
    "glVertexAttrib4f", // 2288
    "glVertexAttrib4fARB", // 2289
    "glVertexAttrib4fNV", // 2290
    "glVertexAttrib4fv", // 2291
    "glVertexAttrib4fvARB", // 2292
    "glVertexAttrib4fvNV", // 2293
    "glVertexAttrib4hNV", // 2294
    "glVertexAttrib4hvNV", // 2295
    "glVertexAttrib4iv", // 2296
    "glVertexAttrib4ivARB", // 2297
    "glVertexAttrib4s", // 2298
    "glVertexAttrib4sARB", // 2299
    "glVertexAttrib4sNV", // 2300
    "glVertexAttrib4sv", // 2301
    "glVertexAttrib4svARB", // 2302
    "glVertexAttrib4svNV", // 2303
    "glVertexAttrib4ubNV", // 2304
    "glVertexAttrib4ubv", // 2305
    "glVertexAttrib4ubvARB", // 2306
    "glVertexAttrib4ubvNV", // 2307
    "glVertexAttrib4uiv", // 2308
    "glVertexAttrib4uivARB", // 2309
    "glVertexAttrib4usv", // 2310
    "glVertexAttrib4usvARB", // 2311
    "glVertexAttribArrayObjectATI", // 2312
    "glVertexAttribBinding", // 2313
    "glVertexAttribDivisor", // 2314
    "glVertexAttribDivisorARB", // 2315
    "glVertexAttribFormat", // 2316
    "glVertexAttribFormatNV", // 2317
    "glVertexAttribI1i", // 2318
    "glVertexAttribI1iEXT", // 2319
    "glVertexAttribI1iv", // 2320
    "glVertexAttribI1ivEXT", // 2321
    "glVertexAttribI1ui", // 2322
    "glVertexAttribI1uiEXT", // 2323
    "glVertexAttribI1uiv", // 2324
    "glVertexAttribI1uivEXT", // 2325
    "glVertexAttribI2i", // 2326
    "glVertexAttribI2iEXT", // 2327
    "glVertexAttribI2iv", // 2328
    "glVertexAttribI2ivEXT", // 2329
    "glVertexAttribI2ui", // 2330
    "glVertexAttribI2uiEXT", // 2331
    "glVertexAttribI2uiv", // 2332
    "glVertexAttribI2uivEXT", // 2333
    "glVertexAttribI3i", // 2334
    "glVertexAttribI3iEXT", // 2335
    "glVertexAttribI3iv", // 2336
    "glVertexAttribI3ivEXT", // 2337
    "glVertexAttribI3ui", // 2338
    "glVertexAttribI3uiEXT", // 2339
    "glVertexAttribI3uiv", // 2340
    "glVertexAttribI3uivEXT", // 2341
    "glVertexAttribI4bv", // 2342
    "glVertexAttribI4bvEXT", // 2343
    "glVertexAttribI4i", // 2344
    "glVertexAttribI4iEXT", // 2345
    "glVertexAttribI4iv", // 2346
    "glVertexAttribI4ivEXT", // 2347
    "glVertexAttribI4sv", // 2348
    "glVertexAttribI4svEXT", // 2349
    "glVertexAttribI4ubv", // 2350
    "glVertexAttribI4ubvEXT", // 2351
    "glVertexAttribI4ui", // 2352
    "glVertexAttribI4uiEXT", // 2353
    "glVertexAttribI4uiv", // 2354
    "glVertexAttribI4uivEXT", // 2355
    "glVertexAttribI4usv", // 2356
    "glVertexAttribI4usvEXT", // 2357
    "glVertexAttribIFormat", // 2358
    "glVertexAttribIFormatNV", // 2359
    "glVertexAttribIPointer", // 2360
    "glVertexAttribIPointerEXT", // 2361
    "glVertexAttribL1d", // 2362
    "glVertexAttribL1dEXT", // 2363
    "glVertexAttribL1dv", // 2364
    "glVertexAttribL1dvEXT", // 2365
    "glVertexAttribL1i64NV", // 2366
    "glVertexAttribL1i64vNV", // 2367
    "glVertexAttribL1ui64ARB", // 2368
    "glVertexAttribL1ui64NV", // 2369
    "glVertexAttribL1ui64vARB", // 2370
    "glVertexAttribL1ui64vNV", // 2371
    "glVertexAttribL2d", // 2372
    "glVertexAttribL2dEXT", // 2373
    "glVertexAttribL2dv", // 2374
    "glVertexAttribL2dvEXT", // 2375
    "glVertexAttribL2i64NV", // 2376
    "glVertexAttribL2i64vNV", // 2377
    "glVertexAttribL2ui64NV", // 2378
    "glVertexAttribL2ui64vNV", // 2379
    "glVertexAttribL3d", // 2380
    "glVertexAttribL3dEXT", // 2381
    "glVertexAttribL3dv", // 2382
    "glVertexAttribL3dvEXT", // 2383
    "glVertexAttribL3i64NV", // 2384
    "glVertexAttribL3i64vNV", // 2385
    "glVertexAttribL3ui64NV", // 2386
    "glVertexAttribL3ui64vNV", // 2387
    "glVertexAttribL4d", // 2388
    "glVertexAttribL4dEXT", // 2389
    "glVertexAttribL4dv", // 2390
    "glVertexAttribL4dvEXT", // 2391
    "glVertexAttribL4i64NV", // 2392
    "glVertexAttribL4i64vNV", // 2393
    "glVertexAttribL4ui64NV", // 2394
    "glVertexAttribL4ui64vNV", // 2395
    "glVertexAttribLFormat", // 2396
    "glVertexAttribLFormatNV", // 2397
    "glVertexAttribLPointer", // 2398
    "glVertexAttribLPointerEXT", // 2399
    "glVertexAttribP1ui", // 2400
    "glVertexAttribP1uiv", // 2401
    "glVertexAttribP2ui", // 2402
    "glVertexAttribP2uiv", // 2403
    "glVertexAttribP3ui", // 2404
    "glVertexAttribP3uiv", // 2405
    "glVertexAttribP4ui", // 2406
    "glVertexAttribP4uiv", // 2407
    "glVertexAttribParameteriAMD", // 2408
    "glVertexAttribPointer", // 2409
    "glVertexAttribPointerARB", // 2410
    "glVertexAttribPointerNV", // 2411
    "glVertexAttribs1dvNV", // 2412
    "glVertexAttribs1fvNV", // 2413
    "glVertexAttribs1hvNV", // 2414
    "glVertexAttribs1svNV", // 2415
    "glVertexAttribs2dvNV", // 2416
    "glVertexAttribs2fvNV", // 2417
    "glVertexAttribs2hvNV", // 2418
    "glVertexAttribs2svNV", // 2419
    "glVertexAttribs3dvNV", // 2420
    "glVertexAttribs3fvNV", // 2421
    "glVertexAttribs3hvNV", // 2422
    "glVertexAttribs3svNV", // 2423
    "glVertexAttribs4dvNV", // 2424
    "glVertexAttribs4fvNV", // 2425
    "glVertexAttribs4hvNV", // 2426
    "glVertexAttribs4svNV", // 2427
    "glVertexAttribs4ubvNV", // 2428
    "glVertexBindingDivisor", // 2429
    "glVertexBlendARB", // 2430
    "glVertexBlendEnvfATI", // 2431
    "glVertexBlendEnviATI", // 2432
    "glVertexFormatNV", // 2433
    "glVertexPointerEXT", // 2434
    "glVertexPointerListIBM", // 2435
    "glVertexPointervINTEL", // 2436
    "glVertexStream1dATI", // 2437
    "glVertexStream1dvATI", // 2438
    "glVertexStream1fATI", // 2439
    "glVertexStream1fvATI", // 2440
    "glVertexStream1iATI", // 2441
    "glVertexStream1ivATI", // 2442
    "glVertexStream1sATI", // 2443
    "glVertexStream1svATI", // 2444
    "glVertexStream2dATI", // 2445
    "glVertexStream2dvATI", // 2446
    "glVertexStream2fATI", // 2447
    "glVertexStream2fvATI", // 2448
    "glVertexStream2iATI", // 2449
    "glVertexStream2ivATI", // 2450
    "glVertexStream2sATI", // 2451
    "glVertexStream2svATI", // 2452
    "glVertexStream3dATI", // 2453
    "glVertexStream3dvATI", // 2454
    "glVertexStream3fATI", // 2455
    "glVertexStream3fvATI", // 2456
    "glVertexStream3iATI", // 2457
    "glVertexStream3ivATI", // 2458
    "glVertexStream3sATI", // 2459
    "glVertexStream3svATI", // 2460
    "glVertexStream4dATI", // 2461
    "glVertexStream4dvATI", // 2462
    "glVertexStream4fATI", // 2463
    "glVertexStream4fvATI", // 2464
    "glVertexStream4iATI", // 2465
    "glVertexStream4ivATI", // 2466
    "glVertexStream4sATI", // 2467
    "glVertexStream4svATI", // 2468
    "glVertexWeightPointerEXT", // 2469
    "glVertexWeightfEXT", // 2470
    "glVertexWeightfvEXT", // 2471
    "glVertexWeighthNV", // 2472
    "glVertexWeighthvNV", // 2473
    "glVideoCaptureNV", // 2474
    "glVideoCaptureStreamParameterdvNV", // 2475
    "glVideoCaptureStreamParameterfvNV", // 2476
    "glVideoCaptureStreamParameterivNV", // 2477
    "glViewport", // 2478
    "glViewportArrayv", // 2479
    "glViewportIndexedf", // 2480
    "glViewportIndexedfv", // 2481
    "glViewportPositionWScaleNV", // 2482
    "glViewportSwizzleNV", // 2483
    "glWaitSemaphoreEXT", // 2484
    "glWaitSemaphoreui64NVX", // 2485
    "glWaitSync", // 2486
    "glWaitVkSemaphoreNV", // 2487
    "glWeightPathsNV", // 2488
    "glWeightPointerARB", // 2489
    "glWeightbvARB", // 2490
    "glWeightdvARB", // 2491
    "glWeightfvARB", // 2492
    "glWeightivARB", // 2493
    "glWeightsvARB", // 2494
    "glWeightubvARB", // 2495
    "glWeightuivARB", // 2496
    "glWeightusvARB", // 2497
    "glWindowPos2dARB", // 2498
    "glWindowPos2dMESA", // 2499
    "glWindowPos2dvARB", // 2500
    "glWindowPos2dvMESA", // 2501
    "glWindowPos2fARB", // 2502
    "glWindowPos2fMESA", // 2503
    "glWindowPos2fvARB", // 2504
    "glWindowPos2fvMESA", // 2505
    "glWindowPos2iARB", // 2506
    "glWindowPos2iMESA", // 2507
    "glWindowPos2ivARB", // 2508
    "glWindowPos2ivMESA", // 2509
    "glWindowPos2sARB", // 2510
    "glWindowPos2sMESA", // 2511
    "glWindowPos2svARB", // 2512
    "glWindowPos2svMESA", // 2513
    "glWindowPos3dARB", // 2514
    "glWindowPos3dMESA", // 2515
    "glWindowPos3dvARB", // 2516
    "glWindowPos3dvMESA", // 2517
    "glWindowPos3fARB", // 2518
    "glWindowPos3fMESA", // 2519
    "glWindowPos3fvARB", // 2520
    "glWindowPos3fvMESA", // 2521
    "glWindowPos3iARB", // 2522
    "glWindowPos3iMESA", // 2523
    "glWindowPos3ivARB", // 2524
    "glWindowPos3ivMESA", // 2525
    "glWindowPos3sARB", // 2526
    "glWindowPos3sMESA", // 2527
    "glWindowPos3svARB", // 2528
    "glWindowPos3svMESA", // 2529
    "glWindowPos4dMESA", // 2530
    "glWindowPos4dvMESA", // 2531
    "glWindowPos4fMESA", // 2532
    "glWindowPos4fvMESA", // 2533
    "glWindowPos4iMESA", // 2534
    "glWindowPos4ivMESA", // 2535
    "glWindowPos4sMESA", // 2536
    "glWindowPos4svMESA", // 2537
    "glWindowRectanglesEXT", // 2538
    "glWriteMaskEXT", // 2539
    "glAcquireTexturesANGLE", // 2540
    "glActiveShaderProgramEXT", // 2541
    "glAlphaFuncQCOM", // 2542
    "glBeginPixelLocalStorageANGLE", // 2543
    "glBeginQueryEXT", // 2544
    "glBindFragDataLocationIndexedEXT", // 2545
    "glBindProgramPipelineEXT", // 2546
    "glBindUniformLocationCHROMIUM", // 2547
    "glBindVertexArrayOES", // 2548
    "glBlendBarrier", // 2549
    "glBlendEquationSeparateiEXT", // 2550
    "glBlendEquationSeparateiOES", // 2551
    "glBlendEquationiEXT", // 2552
    "glBlendEquationiOES", // 2553
    "glBlendFuncSeparateiEXT", // 2554
    "glBlendFuncSeparateiOES", // 2555
    "glBlendFunciEXT", // 2556
    "glBlendFunciOES", // 2557
    "glBlitFramebufferANGLE", // 2558
    "glBlitFramebufferNV", // 2559
    "glBufferStorageEXT", // 2560
    "glClearPixelLocalStorageuiEXT", // 2561
    "glClearTexImageEXT", // 2562
    "glClearTexSubImageEXT", // 2563
    "glClientWaitSyncAPPLE", // 2564
    "glClipControlEXT", // 2565
    "glColorMaskiEXT", // 2566
    "glColorMaskiOES", // 2567
    "glCompressedCopyTextureCHROMIUM", // 2568
    "glCompressedTexImage2DRobustANGLE", // 2569
    "glCompressedTexImage3DOES", // 2570
    "glCompressedTexImage3DRobustANGLE", // 2571
    "glCompressedTexSubImage2DRobustANGLE", // 2572
    "glCompressedTexSubImage3DOES", // 2573
    "glCompressedTexSubImage3DRobustANGLE", // 2574
    "glCopyBufferSubDataNV", // 2575
    "glCopyImageSubDataEXT", // 2576
    "glCopyImageSubDataOES", // 2577
    "glCopySubTexture3DANGLE", // 2578
    "glCopySubTextureCHROMIUM", // 2579
    "glCopyTexSubImage3DOES", // 2580
    "glCopyTexture3DANGLE", // 2581
    "glCopyTextureCHROMIUM", // 2582
    "glCopyTextureLevelsAPPLE", // 2583
    "glCoverageMaskNV", // 2584
    "glCoverageModulationCHROMIUM", // 2585
    "glCoverageOperationNV", // 2586
    "glCreateShaderProgramvEXT", // 2587
    "glDebugMessageCallbackKHR", // 2588
    "glDebugMessageControlKHR", // 2589
    "glDebugMessageInsertKHR", // 2590
    "glDeleteProgramPipelinesEXT", // 2591
    "glDeleteQueriesEXT", // 2592
    "glDeleteSyncAPPLE", // 2593
    "glDeleteVertexArraysOES", // 2594
    "glDepthRangeArrayfvNV", // 2595
    "glDepthRangeArrayfvOES", // 2596
    "glDepthRangeIndexedfNV", // 2597
    "glDepthRangeIndexedfOES", // 2598
    "glDisableDriverControlQCOM", // 2599
    "glDisableExtensionANGLE", // 2600
    "glDisableiEXT", // 2601
    "glDisableiNV", // 2602
    "glDisableiOES", // 2603
    "glDiscardFramebufferEXT", // 2604
    "glDrawArraysInstancedANGLE", // 2605
    "glDrawArraysInstancedBaseInstanceANGLE", // 2606
    "glDrawArraysInstancedBaseInstanceEXT", // 2607
    "glDrawArraysInstancedNV", // 2608
    "glDrawBuffersEXT", // 2609
    "glDrawBuffersIndexedEXT", // 2610
    "glDrawBuffersNV", // 2611
    "glDrawElementsBaseVertexEXT", // 2612
    "glDrawElementsBaseVertexOES", // 2613
    "glDrawElementsInstancedANGLE", // 2614
    "glDrawElementsInstancedBaseInstanceEXT", // 2615
    "glDrawElementsInstancedBaseVertexBaseInstanceANGLE", // 2616
    "glDrawElementsInstancedBaseVertexBaseInstanceEXT", // 2617
    "glDrawElementsInstancedBaseVertexEXT", // 2618
    "glDrawElementsInstancedBaseVertexOES", // 2619
    "glDrawElementsInstancedNV", // 2620
    "glDrawRangeElementsBaseVertexEXT", // 2621
    "glDrawRangeElementsBaseVertexOES", // 2622
    "glDrawTransformFeedbackEXT", // 2623
    "glDrawTransformFeedbackInstancedEXT", // 2624
    "glEGLImageTargetRenderbufferStorageOES", // 2625
    "glEGLImageTargetTexture2DOES", // 2626
    "glEnableDriverControlQCOM", // 2627
    "glEnableiEXT", // 2628
    "glEnableiNV", // 2629
    "glEnableiOES", // 2630
    "glEndPixelLocalStorageANGLE", // 2631
    "glEndQueryEXT", // 2632
    "glEndTilingQCOM", // 2633
    "glExtGetBufferPointervQCOM", // 2634
    "glExtGetBuffersQCOM", // 2635
    "glExtGetFramebuffersQCOM", // 2636
    "glExtGetProgramBinarySourceQCOM", // 2637
    "glExtGetProgramsQCOM", // 2638
    "glExtGetRenderbuffersQCOM", // 2639
    "glExtGetShadersQCOM", // 2640
    "glExtGetTexLevelParameterivQCOM", // 2641
    "glExtGetTexSubImageQCOM", // 2642
    "glExtGetTexturesQCOM", // 2643
    "glExtIsProgramBinaryQCOM", // 2644
    "glExtTexObjectStateOverrideiQCOM", // 2645
    "glExtrapolateTex2DQCOM", // 2646
    "glFenceSyncAPPLE", // 2647
    "glFlushMappedBufferRangeEXT", // 2648
    "glFramebufferFetchBarrierQCOM", // 2649
    "glFramebufferFoveationConfigQCOM", // 2650
    "glFramebufferFoveationParametersQCOM", // 2651
    "glFramebufferMemorylessPixelLocalStorageANGLE", // 2652
    "glFramebufferPixelLocalClearValuefvANGLE", // 2653
    "glFramebufferPixelLocalClearValueivANGLE", // 2654
    "glFramebufferPixelLocalClearValueuivANGLE", // 2655
    "glFramebufferPixelLocalStorageInterruptANGLE", // 2656
    "glFramebufferPixelLocalStorageRestoreANGLE", // 2657
    "glFramebufferPixelLocalStorageSizeEXT", // 2658
    "glFramebufferShadingRateEXT", // 2659
    "glFramebufferTexture2DDownsampleIMG", // 2660
    "glFramebufferTexture2DMultisampleEXT", // 2661
    "glFramebufferTexture2DMultisampleIMG", // 2662
    "glFramebufferTexture3DOES", // 2663
    "glFramebufferTextureLayerDownsampleIMG", // 2664
    "glFramebufferTextureMultisampleMultiviewOVR", // 2665
    "glFramebufferTextureOES", // 2666
    "glFramebufferTexturePixelLocalStorageANGLE", // 2667
    "glGenProgramPipelinesEXT", // 2668
    "glGenQueriesEXT", // 2669
    "glGenVertexArraysOES", // 2670
    "glGetActiveUniformBlockivRobustANGLE", // 2671
    "glGetBooleani_vRobustANGLE", // 2672
    "glGetBooleanvRobustANGLE", // 2673
    "glGetBufferParameteri64vRobustANGLE", // 2674
    "glGetBufferParameterivRobustANGLE", // 2675
    "glGetBufferPointervOES", // 2676
    "glGetBufferPointervRobustANGLE", // 2677
    "glGetCompressedTexImageANGLE", // 2678
    "glGetDebugMessageLogKHR", // 2679
    "glGetDriverControlStringQCOM", // 2680
    "glGetDriverControlsQCOM", // 2681
    "glGetFloati_vNV", // 2682
    "glGetFloati_vOES", // 2683
    "glGetFloatvRobustANGLE", // 2684
    "glGetFragDataIndexEXT", // 2685
    "glGetFragmentShadingRatesEXT", // 2686
    "glGetFramebufferAttachmentParameterivRobustANGLE", // 2687
    "glGetFramebufferParameterivRobustANGLE", // 2688
    "glGetFramebufferPixelLocalStorageParameterfvANGLE", // 2689
    "glGetFramebufferPixelLocalStorageParameterfvRobustANGLE", // 2690
    "glGetFramebufferPixelLocalStorageParameterivANGLE", // 2691
    "glGetFramebufferPixelLocalStorageParameterivRobustANGLE", // 2692
    "glGetFramebufferPixelLocalStorageSizeEXT", // 2693
    "glGetGraphicsResetStatusEXT", // 2694
    "glGetGraphicsResetStatusKHR", // 2695
    "glGetInteger64i_vRobustANGLE", // 2696
    "glGetInteger64vAPPLE", // 2697
    "glGetInteger64vEXT", // 2698
    "glGetInteger64vRobustANGLE", // 2699
    "glGetIntegeri_vEXT", // 2700
    "glGetIntegeri_vRobustANGLE", // 2701
    "glGetIntegervRobustANGLE", // 2702
    "glGetInternalformativRobustANGLE", // 2703
    "glGetMultisamplefvANGLE", // 2704
    "glGetMultisamplefvRobustANGLE", // 2705
    "glGetObjectLabelKHR", // 2706
    "glGetObjectPtrLabelKHR", // 2707
    "glGetPointervKHR", // 2708
    "glGetPointervRobustANGLERobustANGLE", // 2709
    "glGetProgramBinaryOES", // 2710
    "glGetProgramInterfaceivRobustANGLE", // 2711
    "glGetProgramPipelineInfoLogEXT", // 2712
    "glGetProgramPipelineivEXT", // 2713
    "glGetProgramResourceLocationIndexEXT", // 2714
    "glGetProgramivRobustANGLE", // 2715
    "glGetQueryObjecti64vRobustANGLE", // 2716
    "glGetQueryObjectivEXT", // 2717
    "glGetQueryObjectivRobustANGLE", // 2718
    "glGetQueryObjectui64vRobustANGLE", // 2719
    "glGetQueryObjectuivEXT", // 2720
    "glGetQueryObjectuivRobustANGLE", // 2721
    "glGetQueryivEXT", // 2722
    "glGetQueryivRobustANGLE", // 2723
    "glGetRenderbufferImageANGLE", // 2724
    "glGetRenderbufferParameterivRobustANGLE", // 2725
    "glGetSamplerParameterIivEXT", // 2726
    "glGetSamplerParameterIivOES", // 2727
    "glGetSamplerParameterIivRobustANGLE", // 2728
    "glGetSamplerParameterIuivEXT", // 2729
    "glGetSamplerParameterIuivOES", // 2730
    "glGetSamplerParameterIuivRobustANGLE", // 2731
    "glGetSamplerParameterfvRobustANGLE", // 2732
    "glGetSamplerParameterivRobustANGLE", // 2733
    "glGetShaderivRobustANGLE", // 2734
    "glGetSyncivAPPLE", // 2735
    "glGetTexImageANGLE", // 2736
    "glGetTexLevelParameterfvANGLE", // 2737
    "glGetTexLevelParameterfvRobustANGLE", // 2738
    "glGetTexLevelParameterivANGLE", // 2739
    "glGetTexLevelParameterivRobustANGLE", // 2740
    "glGetTexParameterIivOES", // 2741
    "glGetTexParameterIivRobustANGLE", // 2742
    "glGetTexParameterIuivOES", // 2743
    "glGetTexParameterIuivRobustANGLE", // 2744
    "glGetTexParameterfvRobustANGLE", // 2745
    "glGetTexParameterivRobustANGLE", // 2746
    "glGetTextureHandleIMG", // 2747
    "glGetTextureSamplerHandleIMG", // 2748
    "glGetTranslatedShaderSourceANGLE", // 2749
    "glGetUniformfvRobustANGLE", // 2750
    "glGetUniformivRobustANGLE", // 2751
    "glGetUniformuivRobustANGLE", // 2752
    "glGetVertexAttribIivRobustANGLE", // 2753
    "glGetVertexAttribIuivRobustANGLE", // 2754
    "glGetVertexAttribPointervRobustANGLE", // 2755
    "glGetVertexAttribfvRobustANGLE", // 2756
    "glGetVertexAttribivRobustANGLE", // 2757
    "glGetnUniformfvEXT", // 2758
    "glGetnUniformfvKHR", // 2759
    "glGetnUniformfvRobustANGLE", // 2760
    "glGetnUniformivEXT", // 2761
    "glGetnUniformivKHR", // 2762
    "glGetnUniformivRobustANGLE", // 2763
    "glGetnUniformuivKHR", // 2764
    "glGetnUniformuivRobustANGLE", // 2765
    "glIsEnablediEXT", // 2766
    "glIsEnablediNV", // 2767
    "glIsEnablediOES", // 2768
    "glIsProgramPipelineEXT", // 2769
    "glIsQueryEXT", // 2770
    "glIsSyncAPPLE", // 2771
    "glIsVertexArrayOES", // 2772
    "glLogicOpANGLE", // 2773
    "glLoseContextCHROMIUM", // 2774
    "glMapBufferOES", // 2775
    "glMapBufferRangeEXT", // 2776
    "glMaxActiveShaderCoresARM", // 2777
    "glMinSampleShadingOES", // 2778
    "glMultiDrawArraysANGLE", // 2779
    "glMultiDrawArraysIndirectEXT", // 2780
    "glMultiDrawArraysInstancedANGLE", // 2781
    "glMultiDrawArraysInstancedBaseInstanceANGLE", // 2782
    "glMultiDrawElementsANGLE", // 2783
    "glMultiDrawElementsBaseVertexEXT", // 2784
    "glMultiDrawElementsIndirectEXT", // 2785
    "glMultiDrawElementsInstancedANGLE", // 2786
    "glMultiDrawElementsInstancedBaseVertexBaseInstanceANGLE", // 2787
    "glObjectLabelKHR", // 2788
    "glObjectPtrLabelKHR", // 2789
    "glPatchParameteriEXT", // 2790
    "glPatchParameteriOES", // 2791
    "glPixelLocalStorageBarrierANGLE", // 2792
    "glPolygonModeANGLE", // 2793
    "glPolygonModeNV", // 2794
    "glPopDebugGroupKHR", // 2795
    "glPrimitiveBoundingBox", // 2796
    "glPrimitiveBoundingBoxEXT", // 2797
    "glPrimitiveBoundingBoxOES", // 2798
    "glProgramBinaryOES", // 2799
    "glProgramUniformHandleui64IMG", // 2800
    "glProgramUniformHandleui64vIMG", // 2801
    "glProvokingVertexANGLE", // 2802
    "glPushDebugGroupKHR", // 2803
    "glQueryCounterEXT", // 2804
    "glReadBufferIndexedEXT", // 2805
    "glReadBufferNV", // 2806
    "glReadPixelsRobustANGLE", // 2807
    "glReadnPixelsEXT", // 2808
    "glReadnPixelsKHR", // 2809
    "glReadnPixelsRobustANGLE", // 2810
    "glReleaseTexturesANGLE", // 2811
    "glRenderbufferStorageMultisampleANGLE", // 2812
    "glRenderbufferStorageMultisampleAPPLE", // 2813
    "glRenderbufferStorageMultisampleIMG", // 2814
    "glRenderbufferStorageMultisampleNV", // 2815
    "glRequestExtensionANGLE", // 2816
    "glResolveMultisampleFramebufferAPPLE", // 2817
    "glSampleMaskiANGLE", // 2818
    "glSamplerParameterIivEXT", // 2819
    "glSamplerParameterIivOES", // 2820
    "glSamplerParameterIivRobustANGLE", // 2821
    "glSamplerParameterIuivEXT", // 2822
    "glSamplerParameterIuivOES", // 2823
    "glSamplerParameterIuivRobustANGLE", // 2824
    "glSamplerParameterfvRobustANGLE", // 2825
    "glSamplerParameterivRobustANGLE", // 2826
    "glScissorArrayvNV", // 2827
    "glScissorArrayvOES", // 2828
    "glScissorIndexedNV", // 2829
    "glScissorIndexedOES", // 2830
    "glScissorIndexedvNV", // 2831
    "glScissorIndexedvOES", // 2832
    "glShadingRateCombinerOpsEXT", // 2833
    "glShadingRateEXT", // 2834
    "glShadingRateQCOM", // 2835
    "glStartTilingQCOM", // 2836
    "glTexBufferOES", // 2837
    "glTexBufferRangeEXT", // 2838
    "glTexBufferRangeOES", // 2839
    "glTexEstimateMotionQCOM", // 2840
    "glTexEstimateMotionRegionsQCOM", // 2841
    "glTexImage2DRobustANGLE", // 2842
    "glTexImage3DOES", // 2843
    "glTexImage3DRobustANGLE", // 2844
    "glTexPageCommitmentEXT", // 2845
    "glTexParameterIivOES", // 2846
    "glTexParameterIivRobustANGLE", // 2847
    "glTexParameterIuivOES", // 2848
    "glTexParameterIuivRobustANGLE", // 2849
    "glTexParameterfvRobustANGLE", // 2850
    "glTexParameterivRobustANGLE", // 2851
    "glTexStorage2DMultisampleANGLE", // 2852
    "glTexStorage3DMultisampleOES", // 2853
    "glTexStorageAttribs2DEXT", // 2854
    "glTexStorageAttribs3DEXT", // 2855
    "glTexSubImage2DRobustANGLE", // 2856
    "glTexSubImage3DOES", // 2857
    "glTexSubImage3DRobustANGLE", // 2858
    "glTextureFoveationParametersQCOM", // 2859
    "glTextureViewEXT", // 2860
    "glTextureViewOES", // 2861
    "glUniformHandleui64IMG", // 2862
    "glUniformHandleui64vIMG", // 2863
    "glUniformMatrix2x3fvNV", // 2864
    "glUniformMatrix2x4fvNV", // 2865
    "glUniformMatrix3x2fvNV", // 2866
    "glUniformMatrix3x4fvNV", // 2867
    "glUniformMatrix4x2fvNV", // 2868
    "glUniformMatrix4x3fvNV", // 2869
    "glUnmapBufferOES", // 2870
    "glUseProgramStagesEXT", // 2871
    "glValidateProgramPipelineEXT", // 2872
    "glVertexAttribDivisorANGLE", // 2873
    "glVertexAttribDivisorEXT", // 2874
    "glVertexAttribDivisorNV", // 2875
    "glViewportArrayvNV", // 2876
    "glViewportArrayvOES", // 2877
    "glViewportIndexedfNV", // 2878
    "glViewportIndexedfOES", // 2879
    "glViewportIndexedfvNV", // 2880
    "glViewportIndexedfvOES", // 2881
    "glWaitSyncAPPLE" // 2882
};

static const char *glad_ext_names[] = {
    "GL_3DFX_multisample", // 0
    "GL_3DFX_tbuffer", // 1
    "GL_3DFX_texture_compression_FXT1", // 2
    "GL_AMD_blend_minmax_factor", // 3
    "GL_AMD_conservative_depth", // 4
    "GL_AMD_debug_output", // 5
    "GL_AMD_depth_clamp_separate", // 6
    "GL_AMD_draw_buffers_blend", // 7
    "GL_AMD_framebuffer_multisample_advanced", // 8
    "GL_AMD_framebuffer_sample_positions", // 9
    "GL_AMD_gcn_shader", // 10
    "GL_AMD_gpu_shader_half_float", // 11
    "GL_AMD_gpu_shader_int16", // 12
    "GL_AMD_gpu_shader_int64", // 13
    "GL_AMD_interleaved_elements", // 14
    "GL_AMD_multi_draw_indirect", // 15
    "GL_AMD_name_gen_delete", // 16
    "GL_AMD_occlusion_query_event", // 17
    "GL_AMD_performance_monitor", // 18
    "GL_AMD_pinned_memory", // 19
    "GL_AMD_query_buffer_object", // 20
    "GL_AMD_sample_positions", // 21
    "GL_AMD_seamless_cubemap_per_texture", // 22
    "GL_AMD_shader_atomic_counter_ops", // 23
    "GL_AMD_shader_ballot", // 24
    "GL_AMD_shader_explicit_vertex_parameter", // 25
    "GL_AMD_shader_fragment_mask", // 26
    "GL_AMD_shader_gpu_shader_half_float_fetch", // 27
    "GL_AMD_shader_image_load_store_lod", // 28
    "GL_AMD_shader_stencil_export", // 29
    "GL_AMD_shader_trinary_minmax", // 30
    "GL_AMD_sparse_texture", // 31
    "GL_AMD_stencil_operation_extended", // 32
    "GL_AMD_texture_gather_bias_lod", // 33
    "GL_AMD_texture_texture4", // 34
    "GL_AMD_transform_feedback3_lines_triangles", // 35
    "GL_AMD_transform_feedback4", // 36
    "GL_AMD_vertex_shader_layer", // 37
    "GL_AMD_vertex_shader_tessellator", // 38
    "GL_AMD_vertex_shader_viewport_index", // 39
    "GL_ANGLE_memory_object_flags", // 40
    "GL_ANGLE_memory_object_fuchsia", // 41
    "GL_ANGLE_semaphore_fuchsia", // 42
    "GL_ANGLE_texture_compression_dxt", // 43
    "GL_ANGLE_texture_external_update", // 44
    "GL_APPLE_aux_depth_stencil", // 45
    "GL_APPLE_client_storage", // 46
    "GL_APPLE_element_array", // 47
    "GL_APPLE_fence", // 48
    "GL_APPLE_float_pixels", // 49
    "GL_APPLE_flush_buffer_range", // 50
    "GL_APPLE_object_purgeable", // 51
    "GL_APPLE_rgb_422", // 52
    "GL_APPLE_row_bytes", // 53
    "GL_APPLE_specular_vector", // 54
    "GL_APPLE_texture_range", // 55
    "GL_APPLE_transform_hint", // 56
    "GL_APPLE_vertex_array_object", // 57
    "GL_APPLE_vertex_array_range", // 58
    "GL_APPLE_vertex_program_evaluators", // 59
    "GL_APPLE_ycbcr_422", // 60
    "GL_ARB_ES2_compatibility", // 61
    "GL_ARB_ES3_1_compatibility", // 62
    "GL_ARB_ES3_2_compatibility", // 63
    "GL_ARB_ES3_compatibility", // 64
    "GL_ARB_arrays_of_arrays", // 65
    "GL_ARB_base_instance", // 66
    "GL_ARB_bindless_texture", // 67
    "GL_ARB_blend_func_extended", // 68
    "GL_ARB_buffer_storage", // 69
    "GL_ARB_cl_event", // 70
    "GL_ARB_clear_buffer_object", // 71
    "GL_ARB_clear_texture", // 72
    "GL_ARB_clip_control", // 73
    "GL_ARB_color_buffer_float", // 74
    "GL_ARB_compatibility", // 75
    "GL_ARB_compressed_texture_pixel_storage", // 76
    "GL_ARB_compute_shader", // 77
    "GL_ARB_compute_variable_group_size", // 78
    "GL_ARB_conditional_render_inverted", // 79
    "GL_ARB_conservative_depth", // 80
    "GL_ARB_copy_buffer", // 81
    "GL_ARB_copy_image", // 82
    "GL_ARB_cull_distance", // 83
    "GL_ARB_debug_output", // 84
    "GL_ARB_depth_buffer_float", // 85
    "GL_ARB_depth_clamp", // 86
    "GL_ARB_depth_texture", // 87
    "GL_ARB_derivative_control", // 88
    "GL_ARB_direct_state_access", // 89
    "GL_ARB_draw_buffers", // 90
    "GL_ARB_draw_buffers_blend", // 91
    "GL_ARB_draw_elements_base_vertex", // 92
    "GL_ARB_draw_indirect", // 93
    "GL_ARB_draw_instanced", // 94
    "GL_ARB_enhanced_layouts", // 95
    "GL_ARB_explicit_attrib_location", // 96
    "GL_ARB_explicit_uniform_location", // 97
    "GL_ARB_fragment_coord_conventions", // 98
    "GL_ARB_fragment_layer_viewport", // 99
    "GL_ARB_fragment_program", // 100
    "GL_ARB_fragment_program_shadow", // 101
    "GL_ARB_fragment_shader", // 102
    "GL_ARB_fragment_shader_interlock", // 103
    "GL_ARB_framebuffer_no_attachments", // 104
    "GL_ARB_framebuffer_object", // 105
    "GL_ARB_framebuffer_sRGB", // 106
    "GL_ARB_geometry_shader4", // 107
    "GL_ARB_get_program_binary", // 108
    "GL_ARB_get_texture_sub_image", // 109
    "GL_ARB_gl_spirv", // 110
    "GL_ARB_gpu_shader5", // 111
    "GL_ARB_gpu_shader_fp64", // 112
    "GL_ARB_gpu_shader_int64", // 113
    "GL_ARB_half_float_pixel", // 114
    "GL_ARB_half_float_vertex", // 115
    "GL_ARB_imaging", // 116
    "GL_ARB_indirect_parameters", // 117
    "GL_ARB_instanced_arrays", // 118
    "GL_ARB_internalformat_query", // 119
    "GL_ARB_internalformat_query2", // 120
    "GL_ARB_invalidate_subdata", // 121
    "GL_ARB_map_buffer_alignment", // 122
    "GL_ARB_map_buffer_range", // 123
    "GL_ARB_matrix_palette", // 124
    "GL_ARB_multi_bind", // 125
    "GL_ARB_multi_draw_indirect", // 126
    "GL_ARB_multisample", // 127
    "GL_ARB_multitexture", // 128
    "GL_ARB_occlusion_query", // 129
    "GL_ARB_occlusion_query2", // 130
    "GL_ARB_parallel_shader_compile", // 131
    "GL_ARB_pipeline_statistics_query", // 132
    "GL_ARB_pixel_buffer_object", // 133
    "GL_ARB_point_parameters", // 134
    "GL_ARB_point_sprite", // 135
    "GL_ARB_polygon_offset_clamp", // 136
    "GL_ARB_post_depth_coverage", // 137
    "GL_ARB_program_interface_query", // 138
    "GL_ARB_provoking_vertex", // 139
    "GL_ARB_query_buffer_object", // 140
    "GL_ARB_robust_buffer_access_behavior", // 141
    "GL_ARB_robustness", // 142
    "GL_ARB_robustness_isolation", // 143
    "GL_ARB_sample_locations", // 144
    "GL_ARB_sample_shading", // 145
    "GL_ARB_sampler_objects", // 146
    "GL_ARB_seamless_cube_map", // 147
    "GL_ARB_seamless_cubemap_per_texture", // 148
    "GL_ARB_separate_shader_objects", // 149
    "GL_ARB_shader_atomic_counter_ops", // 150
    "GL_ARB_shader_atomic_counters", // 151
    "GL_ARB_shader_ballot", // 152
    "GL_ARB_shader_bit_encoding", // 153
    "GL_ARB_shader_clock", // 154
    "GL_ARB_shader_draw_parameters", // 155
    "GL_ARB_shader_group_vote", // 156
    "GL_ARB_shader_image_load_store", // 157
    "GL_ARB_shader_image_size", // 158
    "GL_ARB_shader_objects", // 159
    "GL_ARB_shader_precision", // 160
    "GL_ARB_shader_stencil_export", // 161
    "GL_ARB_shader_storage_buffer_object", // 162
    "GL_ARB_shader_subroutine", // 163
    "GL_ARB_shader_texture_image_samples", // 164
    "GL_ARB_shader_texture_lod", // 165
    "GL_ARB_shader_viewport_layer_array", // 166
    "GL_ARB_shading_language_100", // 167
    "GL_ARB_shading_language_420pack", // 168
    "GL_ARB_shading_language_include", // 169
    "GL_ARB_shading_language_packing", // 170
    "GL_ARB_shadow", // 171
    "GL_ARB_shadow_ambient", // 172
    "GL_ARB_sparse_buffer", // 173
    "GL_ARB_sparse_texture", // 174
    "GL_ARB_sparse_texture2", // 175
    "GL_ARB_sparse_texture_clamp", // 176
    "GL_ARB_spirv_extensions", // 177
    "GL_ARB_stencil_texturing", // 178
    "GL_ARB_sync", // 179
    "GL_ARB_tessellation_shader", // 180
    "GL_ARB_texture_barrier", // 181
    "GL_ARB_texture_border_clamp", // 182
    "GL_ARB_texture_buffer_object", // 183
    "GL_ARB_texture_buffer_object_rgb32", // 184
    "GL_ARB_texture_buffer_range", // 185
    "GL_ARB_texture_compression", // 186
    "GL_ARB_texture_compression_bptc", // 187
    "GL_ARB_texture_compression_rgtc", // 188
    "GL_ARB_texture_cube_map", // 189
    "GL_ARB_texture_cube_map_array", // 190
    "GL_ARB_texture_env_add", // 191
    "GL_ARB_texture_env_combine", // 192
    "GL_ARB_texture_env_crossbar", // 193
    "GL_ARB_texture_env_dot3", // 194
    "GL_ARB_texture_filter_anisotropic", // 195
    "GL_ARB_texture_filter_minmax", // 196
    "GL_ARB_texture_float", // 197
    "GL_ARB_texture_gather", // 198
    "GL_ARB_texture_mirror_clamp_to_edge", // 199
    "GL_ARB_texture_mirrored_repeat", // 200
    "GL_ARB_texture_multisample", // 201
    "GL_ARB_texture_non_power_of_two", // 202
    "GL_ARB_texture_query_levels", // 203
    "GL_ARB_texture_query_lod", // 204
    "GL_ARB_texture_rectangle", // 205
    "GL_ARB_texture_rg", // 206
    "GL_ARB_texture_rgb10_a2ui", // 207
    "GL_ARB_texture_stencil8", // 208
    "GL_ARB_texture_storage", // 209
    "GL_ARB_texture_storage_multisample", // 210
    "GL_ARB_texture_swizzle", // 211
    "GL_ARB_texture_view", // 212
    "GL_ARB_timer_query", // 213
    "GL_ARB_transform_feedback2", // 214
    "GL_ARB_transform_feedback3", // 215
    "GL_ARB_transform_feedback_instanced", // 216
    "GL_ARB_transform_feedback_overflow_query", // 217
    "GL_ARB_transpose_matrix", // 218
    "GL_ARB_uniform_buffer_object", // 219
    "GL_ARB_vertex_array_bgra", // 220
    "GL_ARB_vertex_array_object", // 221
    "GL_ARB_vertex_attrib_64bit", // 222
    "GL_ARB_vertex_attrib_binding", // 223
    "GL_ARB_vertex_blend", // 224
    "GL_ARB_vertex_buffer_object", // 225
    "GL_ARB_vertex_program", // 226
    "GL_ARB_vertex_shader", // 227
    "GL_ARB_vertex_type_10f_11f_11f_rev", // 228
    "GL_ARB_vertex_type_2_10_10_10_rev", // 229
    "GL_ARB_viewport_array", // 230
    "GL_ARB_window_pos", // 231
    "GL_ATI_draw_buffers", // 232
    "GL_ATI_element_array", // 233
    "GL_ATI_envmap_bumpmap", // 234
    "GL_ATI_fragment_shader", // 235
    "GL_ATI_map_object_buffer", // 236
    "GL_ATI_meminfo", // 237
    "GL_ATI_pixel_format_float", // 238
    "GL_ATI_pn_triangles", // 239
    "GL_ATI_separate_stencil", // 240
    "GL_ATI_text_fragment_shader", // 241
    "GL_ATI_texture_env_combine3", // 242
    "GL_ATI_texture_float", // 243
    "GL_ATI_texture_mirror_once", // 244
    "GL_ATI_vertex_array_object", // 245
    "GL_ATI_vertex_attrib_array_object", // 246
    "GL_ATI_vertex_streams", // 247
    "GL_EXT_422_pixels", // 248
    "GL_EXT_EGL_image_storage", // 249
    "GL_EXT_EGL_sync", // 250
    "GL_EXT_abgr", // 251
    "GL_EXT_bgra", // 252
    "GL_EXT_bindable_uniform", // 253
    "GL_EXT_blend_color", // 254
    "GL_EXT_blend_equation_separate", // 255
    "GL_EXT_blend_func_separate", // 256
    "GL_EXT_blend_logic_op", // 257
    "GL_EXT_blend_minmax", // 258
    "GL_EXT_blend_subtract", // 259
    "GL_EXT_buffer_reference", // 260
    "GL_EXT_buffer_reference2", // 261
    "GL_EXT_clip_volume_hint", // 262
    "GL_EXT_cmyka", // 263
    "GL_EXT_color_subtable", // 264
    "GL_EXT_compiled_vertex_array", // 265
    "GL_EXT_control_flow_attributes", // 266
    "GL_EXT_convolution", // 267
    "GL_EXT_coordinate_frame", // 268
    "GL_EXT_copy_texture", // 269
    "GL_EXT_cull_vertex", // 270
    "GL_EXT_debug_label", // 271
    "GL_EXT_debug_marker", // 272
    "GL_EXT_debug_printf", // 273
    "GL_EXT_demote_to_helper_invocation", // 274
    "GL_EXT_depth_bounds_test", // 275
    "GL_EXT_device_group", // 276
    "GL_EXT_direct_state_access", // 277
    "GL_EXT_draw_buffers2", // 278
    "GL_EXT_draw_instanced", // 279
    "GL_EXT_draw_range_elements", // 280
    "GL_EXT_external_buffer", // 281
    "GL_EXT_fog_coord", // 282
    "GL_EXT_fragment_invocation_density", // 283
    "GL_EXT_fragment_shader_barycentric", // 284
    "GL_EXT_framebuffer_blit", // 285
    "GL_EXT_framebuffer_blit_layers", // 286
    "GL_EXT_framebuffer_multisample", // 287
    "GL_EXT_framebuffer_multisample_blit_scaled", // 288
    "GL_EXT_framebuffer_object", // 289
    "GL_EXT_framebuffer_sRGB", // 290
    "GL_EXT_geometry_shader4", // 291
    "GL_EXT_gpu_program_parameters", // 292
    "GL_EXT_gpu_shader4", // 293
    "GL_EXT_histogram", // 294
    "GL_EXT_index_array_formats", // 295
    "GL_EXT_index_func", // 296
    "GL_EXT_index_material", // 297
    "GL_EXT_index_texture", // 298
    "GL_EXT_light_texture", // 299
    "GL_EXT_memory_object", // 300
    "GL_EXT_memory_object_fd", // 301
    "GL_EXT_memory_object_win32", // 302
    "GL_EXT_misc_attribute", // 303
    "GL_EXT_multi_draw_arrays", // 304
    "GL_EXT_multisample", // 305
    "GL_EXT_multiview_tessellation_geometry_shader", // 306
    "GL_EXT_multiview_texture_multisample", // 307
    "GL_EXT_multiview_timer_query", // 308
    "GL_EXT_nonuniform_qualifier", // 309
    "GL_EXT_packed_depth_stencil", // 310
    "GL_EXT_packed_float", // 311
    "GL_EXT_packed_pixels", // 312
    "GL_EXT_paletted_texture", // 313
    "GL_EXT_pixel_buffer_object", // 314
    "GL_EXT_pixel_transform", // 315
    "GL_EXT_pixel_transform_color_table", // 316
    "GL_EXT_point_parameters", // 317
    "GL_EXT_polygon_offset", // 318
    "GL_EXT_polygon_offset_clamp", // 319
    "GL_EXT_post_depth_coverage", // 320
    "GL_EXT_provoking_vertex", // 321
    "GL_EXT_raster_multisample", // 322
    "GL_EXT_ray_cull_mask", // 323
    "GL_EXT_ray_flags_primitive_culling", // 324
    "GL_EXT_ray_query", // 325
    "GL_EXT_ray_tracing", // 326
    "GL_EXT_rescale_normal", // 327
    "GL_EXT_samplerless_texture_functions", // 328
    "GL_EXT_scalar_block_layout", // 329
    "GL_EXT_secondary_color", // 330
    "GL_EXT_semaphore", // 331
    "GL_EXT_semaphore_fd", // 332
    "GL_EXT_semaphore_win32", // 333
    "GL_EXT_separate_shader_objects", // 334
    "GL_EXT_separate_specular_color", // 335
    "GL_EXT_shader_16bit_storage", // 336
    "GL_EXT_shader_atomic_float", // 337
    "GL_EXT_shader_explicit_arithmetic_types", // 338
    "GL_EXT_shader_framebuffer_fetch", // 339
    "GL_EXT_shader_framebuffer_fetch_non_coherent", // 340
    "GL_EXT_shader_image_int64", // 341
    "GL_EXT_shader_image_load_formatted", // 342
    "GL_EXT_shader_image_load_store", // 343
    "GL_EXT_shader_integer_mix", // 344
    "GL_EXT_shader_realtime_clock", // 345
    "GL_EXT_shader_samples_identical", // 346
    "GL_EXT_shader_subgroup_extended_types", // 347
    "GL_EXT_shadow_funcs", // 348
    "GL_EXT_shared_memory_block", // 349
    "GL_EXT_shared_texture_palette", // 350
    "GL_EXT_sparse_texture2", // 351
    "GL_EXT_stencil_clear_tag", // 352
    "GL_EXT_stencil_two_side", // 353
    "GL_EXT_stencil_wrap", // 354
    "GL_EXT_subgroup_uniform_control_flow", // 355
    "GL_EXT_subgroupuniform_qualifier", // 356
    "GL_EXT_subtexture", // 357
    "GL_EXT_texture", // 358
    "GL_EXT_texture3D", // 359
    "GL_EXT_texture_array", // 360
    "GL_EXT_texture_buffer_object", // 361
    "GL_EXT_texture_compression_latc", // 362
    "GL_EXT_texture_compression_rgtc", // 363
    "GL_EXT_texture_compression_s3tc", // 364
    "GL_EXT_texture_cube_map", // 365
    "GL_EXT_texture_env_add", // 366
    "GL_EXT_texture_env_combine", // 367
    "GL_EXT_texture_env_dot3", // 368
    "GL_EXT_texture_filter_anisotropic", // 369
    "GL_EXT_texture_filter_minmax", // 370
    "GL_EXT_texture_integer", // 371
    "GL_EXT_texture_lod_bias", // 372
    "GL_EXT_texture_mirror_clamp", // 373
    "GL_EXT_texture_object", // 374
    "GL_EXT_texture_perturb_normal", // 375
    "GL_EXT_texture_sRGB", // 376
    "GL_EXT_texture_sRGB_R8", // 377
    "GL_EXT_texture_sRGB_RG8", // 378
    "GL_EXT_texture_sRGB_decode", // 379
    "GL_EXT_texture_shadow_lod", // 380
    "GL_EXT_texture_shared_exponent", // 381
    "GL_EXT_texture_snorm", // 382
    "GL_EXT_texture_storage", // 383
    "GL_EXT_texture_swizzle", // 384
    "GL_EXT_timer_query", // 385
    "GL_EXT_transform_feedback", // 386
    "GL_EXT_vertex_array", // 387
    "GL_EXT_vertex_array_bgra", // 388
    "GL_EXT_vertex_attrib_64bit", // 389
    "GL_EXT_vertex_shader", // 390
    "GL_EXT_vertex_weighting", // 391
    "GL_EXT_vulkan_glsl_relaxed", // 392
    "GL_EXT_win32_keyed_mutex", // 393
    "GL_EXT_window_rectangles", // 394
    "GL_EXT_x11_sync_object", // 395
    "GL_GREMEDY_frame_terminator", // 396
    "GL_GREMEDY_string_marker", // 397
    "GL_HP_convolution_border_modes", // 398
    "GL_HP_image_transform", // 399
    "GL_HP_occlusion_test", // 400
    "GL_HP_texture_lighting", // 401
    "GL_HUAWEI_subpass_shading", // 402
    "GL_IBM_cull_vertex", // 403
    "GL_IBM_multimode_draw_arrays", // 404
    "GL_IBM_rasterpos_clip", // 405
    "GL_IBM_static_data", // 406
    "GL_IBM_texture_mirrored_repeat", // 407
    "GL_IBM_vertex_array_lists", // 408
    "GL_INGR_blend_func_separate", // 409
    "GL_INGR_color_clamp", // 410
    "GL_INGR_interlace_read", // 411
    "GL_INTEL_blackhole_render", // 412
    "GL_INTEL_conservative_rasterization", // 413
    "GL_INTEL_fragment_shader_ordering", // 414
    "GL_INTEL_framebuffer_CMAA", // 415
    "GL_INTEL_map_texture", // 416
    "GL_INTEL_parallel_arrays", // 417
    "GL_INTEL_performance_query", // 418
    "GL_KHR_blend_equation_advanced", // 419
    "GL_KHR_blend_equation_advanced_coherent", // 420
    "GL_KHR_context_flush_control", // 421
    "GL_KHR_debug", // 422
    "GL_KHR_memory_scope_semantics", // 423
    "GL_KHR_no_error", // 424
    "GL_KHR_parallel_shader_compile", // 425
    "GL_KHR_robust_buffer_access_behavior", // 426
    "GL_KHR_robustness", // 427
    "GL_KHR_shader_subgroup", // 428
    "GL_KHR_texture_compression_astc_hdr", // 429
    "GL_KHR_texture_compression_astc_ldr", // 430
    "GL_KHR_texture_compression_astc_sliced_3d", // 431
    "GL_KHR_vulkan_glsl", // 432
    "GL_MESAX_texture_stack", // 433
    "GL_MESA_framebuffer_flip_x", // 434
    "GL_MESA_framebuffer_flip_y", // 435
    "GL_MESA_framebuffer_swap_xy", // 436
    "GL_MESA_pack_invert", // 437
    "GL_MESA_program_binary_formats", // 438
    "GL_MESA_resize_buffers", // 439
    "GL_MESA_shader_integer_functions", // 440
    "GL_MESA_tile_raster_order", // 441
    "GL_MESA_window_pos", // 442
    "GL_MESA_ycbcr_texture", // 443
    "GL_NVX_blend_equation_advanced_multi_draw_buffers", // 444
    "GL_NVX_conditional_render", // 445
    "GL_NVX_gpu_memory_info", // 446
    "GL_NVX_gpu_multicast2", // 447
    "GL_NVX_linked_gpu_multicast", // 448
    "GL_NVX_multiview_per_view_attributes", // 449
    "GL_NVX_progress_fence", // 450
    "GL_NV_alpha_to_coverage_dither_control", // 451
    "GL_NV_bindless_multi_draw_indirect", // 452
    "GL_NV_bindless_multi_draw_indirect_count", // 453
    "GL_NV_bindless_texture", // 454
    "GL_NV_blend_equation_advanced", // 455
    "GL_NV_blend_equation_advanced_coherent", // 456
    "GL_NV_blend_minmax_factor", // 457
    "GL_NV_blend_square", // 458
    "GL_NV_clip_space_w_scaling", // 459
    "GL_NV_command_list", // 460
    "GL_NV_compute_program5", // 461
    "GL_NV_compute_shader_derivatives", // 462
    "GL_NV_conditional_render", // 463
    "GL_NV_conservative_raster", // 464
    "GL_NV_conservative_raster_dilate", // 465
    "GL_NV_conservative_raster_pre_snap", // 466
    "GL_NV_conservative_raster_pre_snap_triangles", // 467
    "GL_NV_conservative_raster_underestimation", // 468
    "GL_NV_cooperative_matrix", // 469
    "GL_NV_copy_depth_to_color", // 470
    "GL_NV_copy_image", // 471
    "GL_NV_deep_texture3D", // 472
    "GL_NV_depth_buffer_float", // 473
    "GL_NV_depth_clamp", // 474
    "GL_NV_draw_texture", // 475
    "GL_NV_draw_vulkan_image", // 476
    "GL_NV_evaluators", // 477
    "GL_NV_explicit_multisample", // 478
    "GL_NV_fence", // 479
    "GL_NV_fill_rectangle", // 480
    "GL_NV_float_buffer", // 481
    "GL_NV_fog_distance", // 482
    "GL_NV_fragment_coverage_to_color", // 483
    "GL_NV_fragment_program", // 484
    "GL_NV_fragment_program2", // 485
    "GL_NV_fragment_program4", // 486
    "GL_NV_fragment_program_option", // 487
    "GL_NV_fragment_shader_barycentric", // 488
    "GL_NV_fragment_shader_interlock", // 489
    "GL_NV_framebuffer_mixed_samples", // 490
    "GL_NV_framebuffer_multisample_coverage", // 491
    "GL_NV_geometry_program4", // 492
    "GL_NV_geometry_shader4", // 493
    "GL_NV_geometry_shader_passthrough", // 494
    "GL_NV_gpu_multicast", // 495
    "GL_NV_gpu_program4", // 496
    "GL_NV_gpu_program5", // 497
    "GL_NV_gpu_program5_mem_extended", // 498
    "GL_NV_gpu_shader5", // 499
    "GL_NV_half_float", // 500
    "GL_NV_internalformat_sample_query", // 501
    "GL_NV_light_max_exponent", // 502
    "GL_NV_memory_attachment", // 503
    "GL_NV_memory_object_sparse", // 504
    "GL_NV_mesh_shader", // 505
    "GL_NV_multisample_coverage", // 506
    "GL_NV_multisample_filter_hint", // 507
    "GL_NV_occlusion_query", // 508
    "GL_NV_packed_depth_stencil", // 509
    "GL_NV_parameter_buffer_object", // 510
    "GL_NV_parameter_buffer_object2", // 511
    "GL_NV_path_rendering", // 512
    "GL_NV_path_rendering_shared_edge", // 513
    "GL_NV_pixel_data_range", // 514
    "GL_NV_point_sprite", // 515
    "GL_NV_present_video", // 516
    "GL_NV_primitive_restart", // 517
    "GL_NV_primitive_shading_rate", // 518
    "GL_NV_query_resource", // 519
    "GL_NV_query_resource_tag", // 520
    "GL_NV_ray_tracing", // 521
    "GL_NV_ray_tracing_motion_blur", // 522
    "GL_NV_register_combiners", // 523
    "GL_NV_register_combiners2", // 524
    "GL_NV_representative_fragment_test", // 525
    "GL_NV_robustness_video_memory_purge", // 526
    "GL_NV_sample_locations", // 527
    "GL_NV_sample_mask_override_coverage", // 528
    "GL_NV_scissor_exclusive", // 529
    "GL_NV_shader_atomic_counters", // 530
    "GL_NV_shader_atomic_float", // 531
    "GL_NV_shader_atomic_float64", // 532
    "GL_NV_shader_atomic_fp16_vector", // 533
    "GL_NV_shader_atomic_int64", // 534
    "GL_NV_shader_buffer_load", // 535
    "GL_NV_shader_buffer_store", // 536
    "GL_NV_shader_sm_builtins", // 537
    "GL_NV_shader_storage_buffer_object", // 538
    "GL_NV_shader_subgroup_partitioned", // 539
    "GL_NV_shader_texture_footprint", // 540
    "GL_NV_shader_thread_group", // 541
    "GL_NV_shader_thread_shuffle", // 542
    "GL_NV_shading_rate_image", // 543
    "GL_NV_stereo_view_rendering", // 544
    "GL_NV_tessellation_program5", // 545
    "GL_NV_texgen_emboss", // 546
    "GL_NV_texgen_reflection", // 547
    "GL_NV_texture_barrier", // 548
    "GL_NV_texture_compression_vtc", // 549
    "GL_NV_texture_env_combine4", // 550
    "GL_NV_texture_expand_normal", // 551
    "GL_NV_texture_multisample", // 552
    "GL_NV_texture_rectangle", // 553
    "GL_NV_texture_rectangle_compressed", // 554
    "GL_NV_texture_shader", // 555
    "GL_NV_texture_shader2", // 556
    "GL_NV_texture_shader3", // 557
    "GL_NV_timeline_semaphore", // 558
    "GL_NV_transform_feedback", // 559
    "GL_NV_transform_feedback2", // 560
    "GL_NV_uniform_buffer_std430_layout", // 561
    "GL_NV_uniform_buffer_unified_memory", // 562
    "GL_NV_vdpau_interop", // 563
    "GL_NV_vdpau_interop2", // 564
    "GL_NV_vertex_array_range", // 565
    "GL_NV_vertex_array_range2", // 566
    "GL_NV_vertex_attrib_integer_64bit", // 567
    "GL_NV_vertex_buffer_unified_memory", // 568
    "GL_NV_vertex_program", // 569
    "GL_NV_vertex_program1_1", // 570
    "GL_NV_vertex_program2", // 571
    "GL_NV_vertex_program2_option", // 572
    "GL_NV_vertex_program3", // 573
    "GL_NV_vertex_program4", // 574
    "GL_NV_video_capture", // 575
    "GL_NV_viewport_array2", // 576
    "GL_NV_viewport_swizzle", // 577
    "GL_OES_byte_coordinates", // 578
    "GL_OES_compressed_paletted_texture", // 579
    "GL_OES_fixed_point", // 580
    "GL_OES_query_matrix", // 581
    "GL_OES_read_format", // 582
    "GL_OES_single_precision", // 583
    "GL_OML_interlace", // 584
    "GL_OML_resample", // 585
    "GL_OML_subsample", // 586
    "GL_OVR_multiview", // 587
    "GL_OVR_multiview2", // 588
    "GL_PGI_misc_hints", // 589
    "GL_PGI_vertex_hints", // 590
    "GL_REND_screen_coordinates", // 591
    "GL_S3_s3tc", // 592
    "GL_SGIS_detail_texture", // 593
    "GL_SGIS_fog_function", // 594
    "GL_SGIS_generate_mipmap", // 595
    "GL_SGIS_multisample", // 596
    "GL_SGIS_pixel_texture", // 597
    "GL_SGIS_point_line_texgen", // 598
    "GL_SGIS_point_parameters", // 599
    "GL_SGIS_sharpen_texture", // 600
    "GL_SGIS_texture4D", // 601
    "GL_SGIS_texture_border_clamp", // 602
    "GL_SGIS_texture_color_mask", // 603
    "GL_SGIS_texture_edge_clamp", // 604
    "GL_SGIS_texture_filter4", // 605
    "GL_SGIS_texture_lod", // 606
    "GL_SGIS_texture_select", // 607
    "GL_SGIX_async", // 608
    "GL_SGIX_async_histogram", // 609
    "GL_SGIX_async_pixel", // 610
    "GL_SGIX_blend_alpha_minmax", // 611
    "GL_SGIX_calligraphic_fragment", // 612
    "GL_SGIX_clipmap", // 613
    "GL_SGIX_convolution_accuracy", // 614
    "GL_SGIX_depth_pass_instrument", // 615
    "GL_SGIX_depth_texture", // 616
    "GL_SGIX_flush_raster", // 617
    "GL_SGIX_fog_offset", // 618
    "GL_SGIX_fragment_lighting", // 619
    "GL_SGIX_framezoom", // 620
    "GL_SGIX_igloo_interface", // 621
    "GL_SGIX_instruments", // 622
    "GL_SGIX_interlace", // 623
    "GL_SGIX_ir_instrument1", // 624
    "GL_SGIX_list_priority", // 625
    "GL_SGIX_pixel_texture", // 626
    "GL_SGIX_pixel_tiles", // 627
    "GL_SGIX_polynomial_ffd", // 628
    "GL_SGIX_reference_plane", // 629
    "GL_SGIX_resample", // 630
    "GL_SGIX_scalebias_hint", // 631
    "GL_SGIX_shadow", // 632
    "GL_SGIX_shadow_ambient", // 633
    "GL_SGIX_sprite", // 634
    "GL_SGIX_subsample", // 635
    "GL_SGIX_tag_sample_buffer", // 636
    "GL_SGIX_texture_add_env", // 637
    "GL_SGIX_texture_coordinate_clamp", // 638
    "GL_SGIX_texture_lod_bias", // 639
    "GL_SGIX_texture_multi_buffer", // 640
    "GL_SGIX_texture_scale_bias", // 641
    "GL_SGIX_vertex_preclip", // 642
    "GL_SGIX_ycrcb", // 643
    "GL_SGIX_ycrcb_subsample", // 644
    "GL_SGIX_ycrcba", // 645
    "GL_SGI_color_matrix", // 646
    "GL_SGI_color_table", // 647
    "GL_SGI_texture_color_table", // 648
    "GL_SUNX_constant_data", // 649
    "GL_SUN_convolution_border_modes", // 650
    "GL_SUN_global_alpha", // 651
    "GL_SUN_mesh_array", // 652
    "GL_SUN_slice_accum", // 653
    "GL_SUN_triangle_list", // 654
    "GL_SUN_vertex", // 655
    "GL_WIN_phong_shading", // 656
    "GL_WIN_specular_fog", // 657
    "GL_AMD_compressed_3DC_texture", // 658
    "GL_AMD_compressed_ATC_texture", // 659
    "GL_AMD_program_binary_Z400", // 660
    "GL_ANDROID_extension_pack_es31a", // 661
    "GL_ANGLE_base_vertex_base_instance", // 662
    "GL_ANGLE_client_arrays", // 663
    "GL_ANGLE_clip_cull_distance", // 664
    "GL_ANGLE_copy_texture_3d", // 665
    "GL_ANGLE_depth_texture", // 666
    "GL_ANGLE_framebuffer_blit", // 667
    "GL_ANGLE_framebuffer_multisample", // 668
    "GL_ANGLE_get_image", // 669
    "GL_ANGLE_get_serialized_context_string", // 670
    "GL_ANGLE_get_tex_level_parameter", // 671
    "GL_ANGLE_instanced_arrays", // 672
    "GL_ANGLE_logic_op", // 673
    "GL_ANGLE_lossy_etc_decode", // 674
    "GL_ANGLE_memory_size", // 675
    "GL_ANGLE_multi_draw", // 676
    "GL_ANGLE_pack_reverse_row_order", // 677
    "GL_ANGLE_polygon_mode", // 678
    "GL_ANGLE_program_binary", // 679
    "GL_ANGLE_program_cache_control", // 680
    "GL_ANGLE_provoking_vertex", // 681
    "GL_ANGLE_renderability_validation", // 682
    "GL_ANGLE_request_extension", // 683
    "GL_ANGLE_rgbx_internal_format", // 684
    "GL_ANGLE_robust_client_memory", // 685
    "GL_ANGLE_robust_fragment_shader_output", // 686
    "GL_ANGLE_robust_resource_initialization", // 687
    "GL_ANGLE_shader_pixel_local_storage", // 688
    "GL_ANGLE_stencil_texturing", // 689
    "GL_ANGLE_texture_compression_dxt3", // 690
    "GL_ANGLE_texture_compression_dxt5", // 691
    "GL_ANGLE_texture_multisample", // 692
    "GL_ANGLE_texture_usage", // 693
    "GL_ANGLE_timer_query", // 694
    "GL_ANGLE_translated_shader_source", // 695
    "GL_ANGLE_vulkan_image", // 696
    "GL_ANGLE_yuv_internal_format", // 697
    "GL_APPLE_clip_distance", // 698
    "GL_APPLE_color_buffer_packed_float", // 699
    "GL_APPLE_copy_texture_levels", // 700
    "GL_APPLE_framebuffer_multisample", // 701
    "GL_APPLE_sync", // 702
    "GL_APPLE_texture_format_BGRA8888", // 703
    "GL_APPLE_texture_max_level", // 704
    "GL_APPLE_texture_packed_float", // 705
    "GL_ARM_mali_program_binary", // 706
    "GL_ARM_mali_shader_binary", // 707
    "GL_ARM_rgba8", // 708
    "GL_ARM_shader_core_properties", // 709
    "GL_ARM_shader_framebuffer_fetch", // 710
    "GL_ARM_shader_framebuffer_fetch_depth_stencil", // 711
    "GL_ARM_texture_unnormalized_coordinates", // 712
    "GL_CHROMIUM_bind_uniform_location", // 713
    "GL_CHROMIUM_copy_compressed_texture", // 714
    "GL_CHROMIUM_copy_texture", // 715
    "GL_CHROMIUM_framebuffer_mixed_samples", // 716
    "GL_CHROMIUM_lose_context", // 717
    "GL_DMP_program_binary", // 718
    "GL_DMP_shader_binary", // 719
    "GL_EXT_EGL_image_array", // 720
    "GL_EXT_EGL_image_storage_compression", // 721
    "GL_EXT_YUV_target", // 722
    "GL_EXT_base_instance", // 723
    "GL_EXT_blend_func_extended", // 724
    "GL_EXT_buffer_storage", // 725
    "GL_EXT_clear_texture", // 726
    "GL_EXT_clip_control", // 727
    "GL_EXT_clip_cull_distance", // 728
    "GL_EXT_color_buffer_float", // 729
    "GL_EXT_color_buffer_half_float", // 730
    "GL_EXT_conservative_depth", // 731
    "GL_EXT_copy_image", // 732
    "GL_EXT_depth_clamp", // 733
    "GL_EXT_discard_framebuffer", // 734
    "GL_EXT_disjoint_timer_query", // 735
    "GL_EXT_draw_buffers", // 736
    "GL_EXT_draw_buffers_indexed", // 737
    "GL_EXT_draw_elements_base_vertex", // 738
    "GL_EXT_draw_transform_feedback", // 739
    "GL_EXT_float_blend", // 740
    "GL_EXT_fragment_shading_rate", // 741
    "GL_EXT_geometry_point_size", // 742
    "GL_EXT_geometry_shader", // 743
    "GL_EXT_gpu_shader5", // 744
    "GL_EXT_instanced_arrays", // 745
    "GL_EXT_map_buffer_range", // 746
    "GL_EXT_multi_draw_indirect", // 747
    "GL_EXT_multisampled_compatibility", // 748
    "GL_EXT_multisampled_render_to_texture", // 749
    "GL_EXT_multisampled_render_to_texture2", // 750
    "GL_EXT_multiview_draw_buffers", // 751
    "GL_EXT_occlusion_query_boolean", // 752
    "GL_EXT_primitive_bounding_box", // 753
    "GL_EXT_protected_textures", // 754
    "GL_EXT_pvrtc_sRGB", // 755
    "GL_EXT_read_format_bgra", // 756
    "GL_EXT_render_snorm", // 757
    "GL_EXT_robustness", // 758
    "GL_EXT_sRGB", // 759
    "GL_EXT_sRGB_write_control", // 760
    "GL_EXT_separate_depth_stencil", // 761
    "GL_EXT_shader_group_vote", // 762
    "GL_EXT_shader_implicit_conversions", // 763
    "GL_EXT_shader_io_blocks", // 764
    "GL_EXT_shader_non_constant_global_initializers", // 765
    "GL_EXT_shader_pixel_local_storage", // 766
    "GL_EXT_shader_pixel_local_storage2", // 767
    "GL_EXT_shader_texture_lod", // 768
    "GL_EXT_shadow_samplers", // 769
    "GL_EXT_sparse_texture", // 770
    "GL_EXT_tessellation_point_size", // 771
    "GL_EXT_tessellation_shader", // 772
    "GL_EXT_texture_border_clamp", // 773
    "GL_EXT_texture_buffer", // 774
    "GL_EXT_texture_compression_astc_decode_mode", // 775
    "GL_EXT_texture_compression_bptc", // 776
    "GL_EXT_texture_compression_dxt1", // 777
    "GL_EXT_texture_compression_s3tc_srgb", // 778
    "GL_EXT_texture_cube_map_array", // 779
    "GL_EXT_texture_format_BGRA8888", // 780
    "GL_EXT_texture_format_sRGB_override", // 781
    "GL_EXT_texture_mirror_clamp_to_edge", // 782
    "GL_EXT_texture_norm16", // 783
    "GL_EXT_texture_query_lod", // 784
    "GL_EXT_texture_rg", // 785
    "GL_EXT_texture_storage_compression", // 786
    "GL_EXT_texture_type_2_10_10_10_REV", // 787
    "GL_EXT_texture_view", // 788
    "GL_EXT_unpack_subimage", // 789
    "GL_FJ_shader_binary_GCCSO", // 790
    "GL_IMG_bindless_texture", // 791
    "GL_IMG_framebuffer_downsample", // 792
    "GL_IMG_multisampled_render_to_texture", // 793
    "GL_IMG_program_binary", // 794
    "GL_IMG_read_format", // 795
    "GL_IMG_shader_binary", // 796
    "GL_IMG_texture_compression_pvrtc", // 797
    "GL_IMG_texture_compression_pvrtc2", // 798
    "GL_IMG_texture_filter_cubic", // 799
    "GL_MESA_bgra", // 800
    "GL_MESA_sampler_objects", // 801
    "GL_NV_copy_buffer", // 802
    "GL_NV_coverage_sample", // 803
    "GL_NV_depth_nonlinear", // 804
    "GL_NV_draw_buffers", // 805
    "GL_NV_draw_instanced", // 806
    "GL_NV_explicit_attrib_location", // 807
    "GL_NV_fbo_color_attachments", // 808
    "GL_NV_framebuffer_blit", // 809
    "GL_NV_framebuffer_multisample", // 810
    "GL_NV_generate_mipmap_sRGB", // 811
    "GL_NV_image_formats", // 812
    "GL_NV_instanced_arrays", // 813
    "GL_NV_non_square_matrices", // 814
    "GL_NV_pack_subimage", // 815
    "GL_NV_pixel_buffer_object", // 816
    "GL_NV_polygon_mode", // 817
    "GL_NV_read_buffer", // 818
    "GL_NV_read_buffer_front", // 819
    "GL_NV_read_depth", // 820
    "GL_NV_read_depth_stencil", // 821
    "GL_NV_read_stencil", // 822
    "GL_NV_sRGB_formats", // 823
    "GL_NV_shader_noperspective_interpolation", // 824
    "GL_NV_shadow_samplers_array", // 825
    "GL_NV_shadow_samplers_cube", // 826
    "GL_NV_texture_border_clamp", // 827
    "GL_NV_texture_compression_s3tc_update", // 828
    "GL_NV_texture_npot_2D_mipmap", // 829
    "GL_NV_viewport_array", // 830
    "GL_OES_EGL_image", // 831
    "GL_OES_EGL_image_external", // 832
    "GL_OES_EGL_image_external_essl3", // 833
    "GL_OES_compressed_ETC1_RGB8_sub_texture", // 834
    "GL_OES_compressed_ETC1_RGB8_texture", // 835
    "GL_OES_copy_image", // 836
    "GL_OES_depth24", // 837
    "GL_OES_depth32", // 838
    "GL_OES_depth_texture", // 839
    "GL_OES_draw_buffers_indexed", // 840
    "GL_OES_draw_elements_base_vertex", // 841
    "GL_OES_element_index_uint", // 842
    "GL_OES_fbo_render_mipmap", // 843
    "GL_OES_fragment_precision_high", // 844
    "GL_OES_geometry_point_size", // 845
    "GL_OES_geometry_shader", // 846
    "GL_OES_get_program_binary", // 847
    "GL_OES_gpu_shader5", // 848
    "GL_OES_mapbuffer", // 849
    "GL_OES_packed_depth_stencil", // 850
    "GL_OES_primitive_bounding_box", // 851
    "GL_OES_required_internalformat", // 852
    "GL_OES_rgb8_rgba8", // 853
    "GL_OES_sample_shading", // 854
    "GL_OES_sample_variables", // 855
    "GL_OES_shader_image_atomic", // 856
    "GL_OES_shader_io_blocks", // 857
    "GL_OES_shader_multisample_interpolation", // 858
    "GL_OES_standard_derivatives", // 859
    "GL_OES_stencil1", // 860
    "GL_OES_stencil4", // 861
    "GL_OES_surfaceless_context", // 862
    "GL_OES_tessellation_point_size", // 863
    "GL_OES_tessellation_shader", // 864
    "GL_OES_texture_3D", // 865
    "GL_OES_texture_border_clamp", // 866
    "GL_OES_texture_buffer", // 867
    "GL_OES_texture_compression_astc", // 868
    "GL_OES_texture_cube_map_array", // 869
    "GL_OES_texture_float", // 870
    "GL_OES_texture_float_linear", // 871
    "GL_OES_texture_half_float", // 872
    "GL_OES_texture_half_float_linear", // 873
    "GL_OES_texture_npot", // 874
    "GL_OES_texture_stencil8", // 875
    "GL_OES_texture_storage_multisample_2d_array", // 876
    "GL_OES_texture_view", // 877
    "GL_OES_vertex_array_object", // 878
    "GL_OES_vertex_half_float", // 879
    "GL_OES_vertex_type_10_10_10_2", // 880
    "GL_OES_viewport_array", // 881
    "GL_OVR_multiview_multisampled_render_to_texture", // 882
    "GL_QCOM_YUV_texture_gather", // 883
    "GL_QCOM_alpha_test", // 884
    "GL_QCOM_binning_control", // 885
    "GL_QCOM_driver_control", // 886
    "GL_QCOM_extended_get", // 887
    "GL_QCOM_extended_get2", // 888
    "GL_QCOM_frame_extrapolation", // 889
    "GL_QCOM_framebuffer_foveated", // 890
    "GL_QCOM_motion_estimation", // 891
    "GL_QCOM_perfmon_global_mode", // 892
    "GL_QCOM_render_sRGB_R8_RG8", // 893
    "GL_QCOM_render_shared_exponent", // 894
    "GL_QCOM_shader_framebuffer_fetch_noncoherent", // 895
    "GL_QCOM_shader_framebuffer_fetch_rate", // 896
    "GL_QCOM_shading_rate", // 897
    "GL_QCOM_texture_foveated", // 898
    "GL_QCOM_texture_foveated2", // 899
    "GL_QCOM_texture_foveated_subsampled_layout", // 900
    "GL_QCOM_texture_lod_bias", // 901
    "GL_QCOM_tiled_rendering", // 902
    "GL_QCOM_writeonly_rendering", // 903
    "GL_VIV_shader_binary" // 904
};

#ifdef __cplusplus
GladGLContext glad_gl_context = {};
#else
GladGLContext glad_gl_context = { 0 };
#endif

static void glad_gl_load_GL_VERSION_1_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_0) return;
    static const uint16_t s_pfnIdx[] = {
          116, // glBlendFunc
          151, // glClear
          159, // glClearColor
          163, // glClearDepth
          176, // glClearStencil
          207, // glColorMask
          327, // glCullFace
          383, // glDepthFunc
          384, // glDepthMask
          385, // glDepthRange
          397, // glDisable
          419, // glDrawBuffer
          460, // glEnable
          498, // glFinish
          504, // glFlush
          569, // glFrontFace
          628, // glGetBooleanv
          669, // glGetDoublev
          670, // glGetError
          679, // glGetFloatv
          713, // glGetIntegerv
          877, // glGetString
          887, // glGetTexImage
          888, // glGetTexLevelParameterfv
          889, // glGetTexLevelParameteriv
          896, // glGetTexParameterfv
          897, // glGetTexParameteriv
         1013, // glHint
         1055, // glIsEnabled
         1105, // glLineWidth
         1121, // glLogicOp
         1421, // glPixelStoref
         1422, // glPixelStorei
         1449, // glPointSize
         1453, // glPolygonMode
         1667, // glReadBuffer
         1669, // glReadPixels
         1732, // glScissor
         1796, // glStencilFunc
         1799, // glStencilMask
         1801, // glStencilOp
         1888, // glTexImage1D
         1889, // glTexImage2D
         1904, // glTexParameterf
         1905, // glTexParameterfv
         1906, // glTexParameteri
         1907, // glTexParameteriv
         2478  // glViewport
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_1_1(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_1) return;
    static const uint16_t s_pfnIdx[] = {
           75, // glBindTexture
          281, // glCopyTexImage1D
          283, // glCopyTexImage2D
          285, // glCopyTexSubImage1D
          287, // glCopyTexSubImage2D
          374, // glDeleteTextures
          412, // glDrawArrays
          429, // glDrawElements
          595, // glGenTextures
          812, // glGetPointerv
         1086, // glIsTexture
         1454, // glPolygonOffset
         1929, // glTexSubImage1D
         1931  // glTexSubImage2D
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_1_2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_2) return;
    static const uint16_t s_pfnIdx[] = {
          289, // glCopyTexSubImage3D
          443, // glDrawRangeElements
         1893, // glTexImage3D
         1933  // glTexSubImage3D
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_1_3(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_3) return;
    static const uint16_t s_pfnIdx[] = {
            5, // glActiveTexture
          236, // glCompressedTexImage1D
          238, // glCompressedTexImage2D
          240, // glCompressedTexImage3D
          242, // glCompressedTexSubImage1D
          244, // glCompressedTexSubImage2D
          246, // glCompressedTexSubImage3D
          652, // glGetCompressedTexImage
         1716  // glSampleCoverage
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_1_4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_4) return;
    static const uint16_t s_pfnIdx[] = {
          103, // glBlendColor
          106, // glBlendEquation
          118, // glBlendFuncSeparate
         1198, // glMultiDrawArrays
         1207, // glMultiDrawElements
         1436, // glPointParameterf
         1440, // glPointParameterfv
         1444, // glPointParameteri
         1446  // glPointParameteriv
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_1_5(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_1_5) return;
    static const uint16_t s_pfnIdx[] = {
           31, // glBeginQuery
           41, // glBindBuffer
          134, // glBufferData
          142, // glBufferSubData
          344, // glDeleteBuffers
          364, // glDeleteQueries
          479, // glEndQuery
          573, // glGenBuffers
          587, // glGenQueries
          630, // glGetBufferParameteriv
          633, // glGetBufferPointerv
          635, // glGetBufferSubData
          851, // glGetQueryObjectiv
          855, // glGetQueryObjectuiv
          857, // glGetQueryiv
         1051, // glIsBuffer
         1077, // glIsQuery
         1136, // glMapBuffer
         2122  // glUnmapBuffer
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_2_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_2_0) return;
    static const uint16_t s_pfnIdx[] = {
           23, // glAttachShader
           39, // glBindAttribLocation
          109, // glBlendEquationSeparate
          227, // glCompileShader
          310, // glCreateProgram
          318, // glCreateShader
          360, // glDeleteProgram
          371, // glDeleteShader
          395, // glDetachShader
          406, // glDisableVertexAttribArray
          420, // glDrawBuffers
          469, // glEnableVertexAttribArray
          608, // glGetActiveAttrib
          613, // glGetActiveUniform
          623, // glGetAttachedShaders
          624, // glGetAttribLocation
          819, // glGetProgramInfoLog
          841, // glGetProgramiv
          868, // glGetShaderInfoLog
          870, // glGetShaderSource
          872, // glGetShaderiv
          928, // glGetUniformLocation
          933, // glGetUniformfv
          937, // glGetUniformiv
          970, // glGetVertexAttribPointerv
          973, // glGetVertexAttribdv
          976, // glGetVertexAttribfv
          979, // glGetVertexAttribiv
         1073, // glIsProgram
         1083, // glIsShader
         1107, // glLinkProgram
         1773, // glShaderSource
         1797, // glStencilFuncSeparate
         1800, // glStencilMaskSeparate
         1802, // glStencilOpSeparate
         2005, // glUniform1f
         2007, // glUniform1fv
         2009, // glUniform1i
         2015, // glUniform1iv
         2027, // glUniform2f
         2029, // glUniform2fv
         2031, // glUniform2i
         2037, // glUniform2iv
         2049, // glUniform3f
         2051, // glUniform3fv
         2053, // glUniform3i
         2059, // glUniform3iv
         2071, // glUniform4f
         2073, // glUniform4fv
         2075, // glUniform4i
         2081, // glUniform4iv
         2098, // glUniformMatrix2fv
         2105, // glUniformMatrix3fv
         2112, // glUniformMatrix4fv
         2130, // glUseProgram
         2145, // glValidateProgram
         2206, // glVertexAttrib1d
         2209, // glVertexAttrib1dv
         2212, // glVertexAttrib1f
         2215, // glVertexAttrib1fv
         2220, // glVertexAttrib1s
         2223, // glVertexAttrib1sv
         2226, // glVertexAttrib2d
         2229, // glVertexAttrib2dv
         2232, // glVertexAttrib2f
         2235, // glVertexAttrib2fv
         2240, // glVertexAttrib2s
         2243, // glVertexAttrib2sv
         2246, // glVertexAttrib3d
         2249, // glVertexAttrib3dv
         2252, // glVertexAttrib3f
         2255, // glVertexAttrib3fv
         2260, // glVertexAttrib3s
         2263, // glVertexAttrib3sv
         2266, // glVertexAttrib4Nbv
         2268, // glVertexAttrib4Niv
         2270, // glVertexAttrib4Nsv
         2272, // glVertexAttrib4Nub
         2274, // glVertexAttrib4Nubv
         2276, // glVertexAttrib4Nuiv
         2278, // glVertexAttrib4Nusv
         2280, // glVertexAttrib4bv
         2282, // glVertexAttrib4d
         2285, // glVertexAttrib4dv
         2288, // glVertexAttrib4f
         2291, // glVertexAttrib4fv
         2296, // glVertexAttrib4iv
         2298, // glVertexAttrib4s
         2301, // glVertexAttrib4sv
         2305, // glVertexAttrib4ubv
         2308, // glVertexAttrib4uiv
         2310, // glVertexAttrib4usv
         2409  // glVertexAttribPointer
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_2_1(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_2_1) return;
    static const uint16_t s_pfnIdx[] = {
         2101, // glUniformMatrix2x3fv
         2103, // glUniformMatrix2x4fv
         2108, // glUniformMatrix3x2fv
         2110, // glUniformMatrix3x4fv
         2115, // glUniformMatrix4x2fv
         2117  // glUniformMatrix4x3fv
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_3_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_3_0) return;
    static const uint16_t s_pfnIdx[] = {
           24, // glBeginConditionalRender
           34, // glBeginTransformFeedback
           43, // glBindBufferBase
           48, // glBindBufferRange
           53, // glBindFragDataLocation
           57, // glBindFramebuffer
           69, // glBindRenderbuffer
           82, // glBindVertexArray
          127, // glBlitFramebuffer
          145, // glCheckFramebufferStatus
          149, // glClampColor
          155, // glClearBufferfi
          156, // glClearBufferfv
          157, // glClearBufferiv
          158, // glClearBufferuiv
          209, // glColorMaski
          350, // glDeleteFramebuffers
          367, // glDeleteRenderbuffers
          378, // glDeleteVertexArrays
          408, // glDisablei
          471, // glEnablei
          472, // glEndConditionalRender
          482, // glEndTransformFeedback
          505, // glFlushMappedBufferRange
          548, // glFramebufferRenderbuffer
          554, // glFramebufferTexture1D
          556, // glFramebufferTexture2D
          558, // glFramebufferTexture3D
          564, // glFramebufferTextureLayer
          578, // glGenFramebuffers
          590, // glGenRenderbuffers
          599, // glGenVertexArrays
          602, // glGenerateMipmap
          627, // glGetBooleani_v
          682, // glGetFragDataLocation
          688, // glGetFramebufferAttachmentParameteriv
          710, // glGetIntegeri_v
          859, // glGetRenderbufferParameteriv
          878, // glGetStringi
          891, // glGetTexParameterIiv
          893, // glGetTexParameterIuiv
          919, // glGetTransformFeedbackVarying
          941, // glGetUniformuiv
          961, // glGetVertexAttribIiv
          963, // glGetVertexAttribIuiv
         1057, // glIsEnabledi
         1060, // glIsFramebuffer
         1079, // glIsRenderbuffer
         1093, // glIsVertexArray
         1138, // glMapBufferRange
         1678, // glRenderbufferStorage
         1680, // glRenderbufferStorageMultisample
         1900, // glTexParameterIiv
         1902, // glTexParameterIuiv
         1998, // glTransformFeedbackVaryings
         2017, // glUniform1ui
         2023, // glUniform1uiv
         2039, // glUniform2ui
         2045, // glUniform2uiv
         2061, // glUniform3ui
         2067, // glUniform3uiv
         2083, // glUniform4ui
         2089, // glUniform4uiv
         2318, // glVertexAttribI1i
         2320, // glVertexAttribI1iv
         2322, // glVertexAttribI1ui
         2324, // glVertexAttribI1uiv
         2326, // glVertexAttribI2i
         2328, // glVertexAttribI2iv
         2330, // glVertexAttribI2ui
         2332, // glVertexAttribI2uiv
         2334, // glVertexAttribI3i
         2336, // glVertexAttribI3iv
         2338, // glVertexAttribI3ui
         2340, // glVertexAttribI3uiv
         2342, // glVertexAttribI4bv
         2344, // glVertexAttribI4i
         2346, // glVertexAttribI4iv
         2348, // glVertexAttribI4sv
         2350, // glVertexAttribI4ubv
         2352, // glVertexAttribI4ui
         2354, // glVertexAttribI4uiv
         2356, // glVertexAttribI4usv
         2360  // glVertexAttribIPointer
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_3_1(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_3_1) return;
    static const uint16_t s_pfnIdx[] = {
           43, // glBindBufferBase
           48, // glBindBufferRange
          267, // glCopyBufferSubData
          415, // glDrawArraysInstanced
          432, // glDrawElementsInstanced
          615, // glGetActiveUniformBlockName
          616, // glGetActiveUniformBlockiv
          617, // glGetActiveUniformName
          618, // glGetActiveUniformsiv
          710, // glGetIntegeri_v
          925, // glGetUniformBlockIndex
          927, // glGetUniformIndices
         1464, // glPrimitiveRestartIndex
         1835, // glTexBuffer
         2091  // glUniformBlockBinding
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_3_2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_3_2) return;
    static const uint16_t s_pfnIdx[] = {
          183, // glClientWaitSync
          373, // glDeleteSync
          430, // glDrawElementsBaseVertex
          435, // glDrawElementsInstancedBaseVertex
          444, // glDrawRangeElementsBaseVertex
          496, // glFenceSync
          553, // glFramebufferTexture
          629, // glGetBufferParameteri64v
          707, // glGetInteger64i_v
          708, // glGetInteger64v
          750, // glGetMultisamplefv
          881, // glGetSynciv
         1085, // glIsSync
         1208, // glMultiDrawElementsBaseVertex
         1650, // glProvokingVertex
         1722, // glSampleMaski
         1891, // glTexImage2DMultisample
         1895, // glTexImage3DMultisample
         2486  // glWaitSync
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_3_3(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_3_3) return;
    static const uint16_t s_pfnIdx[] = {
           55, // glBindFragDataLocationIndexed
           71, // glBindSampler
          369, // glDeleteSamplers
          592, // glGenSamplers
          681, // glGetFragDataIndex
          849, // glGetQueryObjecti64v
          853, // glGetQueryObjectui64v
          861, // glGetSamplerParameterIiv
          862, // glGetSamplerParameterIuiv
          863, // glGetSamplerParameterfv
          864, // glGetSamplerParameteriv
         1081, // glIsSampler
         1655, // glQueryCounter
         1725, // glSamplerParameterIiv
         1726, // glSamplerParameterIuiv
         1727, // glSamplerParameterf
         1728, // glSamplerParameterfv
         1729, // glSamplerParameteri
         1730, // glSamplerParameteriv
         2314, // glVertexAttribDivisor
         2400, // glVertexAttribP1ui
         2401, // glVertexAttribP1uiv
         2402, // glVertexAttribP2ui
         2403, // glVertexAttribP2uiv
         2404, // glVertexAttribP3ui
         2405, // glVertexAttribP3uiv
         2406, // glVertexAttribP4ui
         2407  // glVertexAttribP4uiv
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_4_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_4_0) return;
    static const uint16_t s_pfnIdx[] = {
           33, // glBeginQueryIndexed
           80, // glBindTransformFeedback
          112, // glBlendEquationSeparatei
          114, // glBlendEquationi
          122, // glBlendFuncSeparatei
          124, // glBlendFunci
          376, // glDeleteTransformFeedbacks
          414, // glDrawArraysIndirect
          431, // glDrawElementsIndirect
          447, // glDrawTransformFeedback
          450, // glDrawTransformFeedbackStream
          481, // glEndQueryIndexed
          597, // glGenTransformFeedbacks
          610, // glGetActiveSubroutineName
          611, // glGetActiveSubroutineUniformName
          612, // glGetActiveSubroutineUniformiv
          837, // glGetProgramStageiv
          848, // glGetQueryIndexediv
          879, // glGetSubroutineIndex
          880, // glGetSubroutineUniformLocation
          931, // glGetUniformSubroutineuiv
          932, // glGetUniformdv
         1090, // glIsTransformFeedback
         1191, // glMinSampleShading
         1397, // glPatchParameterfv
         1398, // glPatchParameteri
         1417, // glPauseTransformFeedback
         1713, // glResumeTransformFeedback
         2003, // glUniform1d
         2004, // glUniform1dv
         2025, // glUniform2d
         2026, // glUniform2dv
         2047, // glUniform3d
         2048, // glUniform3dv
         2069, // glUniform4d
         2070, // glUniform4dv
         2097, // glUniformMatrix2dv
         2100, // glUniformMatrix2x3dv
         2102, // glUniformMatrix2x4dv
         2104, // glUniformMatrix3dv
         2107, // glUniformMatrix3x2dv
         2109, // glUniformMatrix3x4dv
         2111, // glUniformMatrix4dv
         2114, // glUniformMatrix4x2dv
         2116, // glUniformMatrix4x3dv
         2118  // glUniformSubroutinesuiv
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_4_1(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_4_1) return;
    static const uint16_t s_pfnIdx[] = {
            3, // glActiveShaderProgram
           68, // glBindProgramPipeline
          165, // glClearDepthf
          321, // glCreateShaderProgramv
          361, // glDeleteProgramPipelines
          387, // glDepthRangeArrayv
          388, // glDepthRangeIndexed
          391, // glDepthRangef
          584, // glGenProgramPipelines
          667, // glGetDoublei_v
          677, // glGetFloati_v
          814, // glGetProgramBinary
          829, // glGetProgramPipelineInfoLog
          830, // glGetProgramPipelineiv
          869, // glGetShaderPrecisionFormat
          965, // glGetVertexAttribLdv
         1076, // glIsProgramPipeline
         1469, // glProgramBinary
         1503, // glProgramParameteri
         1511, // glProgramUniform1d
         1513, // glProgramUniform1dv
         1515, // glProgramUniform1f
         1517, // glProgramUniform1fv
         1519, // glProgramUniform1i
         1525, // glProgramUniform1iv
         1527, // glProgramUniform1ui
         1533, // glProgramUniform1uiv
         1535, // glProgramUniform2d
         1537, // glProgramUniform2dv
         1539, // glProgramUniform2f
         1541, // glProgramUniform2fv
         1543, // glProgramUniform2i
         1549, // glProgramUniform2iv
         1551, // glProgramUniform2ui
         1557, // glProgramUniform2uiv
         1559, // glProgramUniform3d
         1561, // glProgramUniform3dv
         1563, // glProgramUniform3f
         1565, // glProgramUniform3fv
         1567, // glProgramUniform3i
         1573, // glProgramUniform3iv
         1575, // glProgramUniform3ui
         1581, // glProgramUniform3uiv
         1583, // glProgramUniform4d
         1585, // glProgramUniform4dv
         1587, // glProgramUniform4f
         1589, // glProgramUniform4fv
         1591, // glProgramUniform4i
         1597, // glProgramUniform4iv
         1599, // glProgramUniform4ui
         1605, // glProgramUniform4uiv
         1611, // glProgramUniformMatrix2dv
         1613, // glProgramUniformMatrix2fv
         1615, // glProgramUniformMatrix2x3dv
         1617, // glProgramUniformMatrix2x3fv
         1619, // glProgramUniformMatrix2x4dv
         1621, // glProgramUniformMatrix2x4fv
         1623, // glProgramUniformMatrix3dv
         1625, // glProgramUniformMatrix3fv
         1627, // glProgramUniformMatrix3x2dv
         1629, // glProgramUniformMatrix3x2fv
         1631, // glProgramUniformMatrix3x4dv
         1633, // glProgramUniformMatrix3x4fv
         1635, // glProgramUniformMatrix4dv
         1637, // glProgramUniformMatrix4fv
         1639, // glProgramUniformMatrix4x2dv
         1641, // glProgramUniformMatrix4x2fv
         1643, // glProgramUniformMatrix4x3dv
         1645, // glProgramUniformMatrix4x3fv
         1676, // glReleaseShaderCompiler
         1733, // glScissorArrayv
         1736, // glScissorIndexed
         1737, // glScissorIndexedv
         1769, // glShaderBinary
         2132, // glUseProgramStages
         2147, // glValidateProgramPipeline
         2362, // glVertexAttribL1d
         2364, // glVertexAttribL1dv
         2372, // glVertexAttribL2d
         2374, // glVertexAttribL2dv
         2380, // glVertexAttribL3d
         2382, // glVertexAttribL3dv
         2388, // glVertexAttribL4d
         2390, // glVertexAttribL4dv
         2398, // glVertexAttribLPointer
         2479, // glViewportArrayv
         2480, // glViewportIndexedf
         2481  // glViewportIndexedfv
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_4_2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_4_2) return;
    static const uint16_t s_pfnIdx[] = {
           59, // glBindImageTexture
          417, // glDrawArraysInstancedBaseInstance
          434, // glDrawElementsInstancedBaseInstance
          436, // glDrawElementsInstancedBaseVertexBaseInstance
          448, // glDrawTransformFeedbackInstanced
          451, // glDrawTransformFeedbackStreamInstanced
          607, // glGetActiveAtomicCounterBufferiv
          716, // glGetInternalformativ
         1187, // glMemoryBarrier
         1911, // glTexStorage1D
         1913, // glTexStorage2D
         1916  // glTexStorage3D
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_4_3(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_4_3) return;
    static const uint16_t s_pfnIdx[] = {
           84, // glBindVertexBuffer
          153, // glClearBufferData
          154, // glClearBufferSubData
          272, // glCopyImageSubData
          331, // glDebugMessageCallback
          334, // glDebugMessageControl
          337, // glDebugMessageInsert
          409, // glDispatchCompute
          411, // glDispatchComputeIndirect
          545, // glFramebufferParameteri
          662, // glGetDebugMessageLog
          691, // glGetFramebufferParameteriv
          715, // glGetInternalformati64v
          778, // glGetObjectLabel
          783, // glGetObjectPtrLabel
          812, // glGetPointerv
          820, // glGetProgramInterfaceiv
          831, // glGetProgramResourceIndex
          832, // glGetProgramResourceLocation
          833, // glGetProgramResourceLocationIndex
          834, // glGetProgramResourceName
          836, // glGetProgramResourceiv
         1041, // glInvalidateBufferData
         1042, // glInvalidateBufferSubData
         1043, // glInvalidateFramebuffer
         1046, // glInvalidateSubFramebuffer
         1047, // glInvalidateTexImage
         1048, // glInvalidateTexSubImage
         1200, // glMultiDrawArraysIndirect
         1210, // glMultiDrawElementsIndirect
         1387, // glObjectLabel
         1388, // glObjectPtrLabel
         1459, // glPopDebugGroup
         1653, // glPushDebugGroup
         1775, // glShaderStorageBlockBinding
         1838, // glTexBufferRange
         1915, // glTexStorage2DMultisample
         1918, // glTexStorage3DMultisample
         1992, // glTextureView
         2313, // glVertexAttribBinding
         2316, // glVertexAttribFormat
         2358, // glVertexAttribIFormat
         2396, // glVertexAttribLFormat
         2429  // glVertexBindingDivisor
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_4_4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_4_4) return;
    static const uint16_t s_pfnIdx[] = {
           51, // glBindBuffersBase
           52, // glBindBuffersRange
           61, // glBindImageTextures
           72, // glBindSamplers
           79, // glBindTextures
           85, // glBindVertexBuffers
          139, // glBufferStorage
          177, // glClearTexImage
          178  // glClearTexSubImage
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_4_5(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_4_5) return;
    static const uint16_t s_pfnIdx[] = {
           77, // glBindTextureUnit
          131, // glBlitNamedFramebuffer
          147, // glCheckNamedFramebufferStatus
          168, // glClearNamedBufferData
          170, // glClearNamedBufferSubData
          172, // glClearNamedFramebufferfi
          173, // glClearNamedFramebufferfv
          174, // glClearNamedFramebufferiv
          175, // glClearNamedFramebufferuiv
          184, // glClipControl
          251, // glCompressedTextureSubImage1D
          253, // glCompressedTextureSubImage2D
          255, // glCompressedTextureSubImage3D
          279, // glCopyNamedBufferSubData
          293, // glCopyTextureSubImage1D
          295, // glCopyTextureSubImage2D
          297, // glCopyTextureSubImage3D
          305, // glCreateBuffers
          307, // glCreateFramebuffers
          312, // glCreateProgramPipelines
          314, // glCreateQueries
          315, // glCreateRenderbuffers
          316, // glCreateSamplers
          324, // glCreateTextures
          325, // glCreateTransformFeedbacks
          326, // glCreateVertexArrays
          402, // glDisableVertexArrayAttrib
          465, // glEnableVertexArrayAttrib
          507, // glFlushMappedNamedBufferRange
          605, // glGenerateTextureMipmap
          654, // glGetCompressedTextureImage
          656, // glGetCompressedTextureSubImage
          694, // glGetGraphicsResetStatus
          752, // glGetNamedBufferParameteri64v
          753, // glGetNamedBufferParameteriv
          756, // glGetNamedBufferPointerv
          758, // glGetNamedBufferSubData
          760, // glGetNamedFramebufferAttachmentParameteriv
          763, // glGetNamedFramebufferParameteriv
          771, // glGetNamedRenderbufferParameteriv
          844, // glGetQueryBufferObjecti64v
          845, // glGetQueryBufferObjectiv
          846, // glGetQueryBufferObjectui64v
          847, // glGetQueryBufferObjectuiv
          901, // glGetTextureImage
          903, // glGetTextureLevelParameterfv
          905, // glGetTextureLevelParameteriv
          907, // glGetTextureParameterIiv
          909, // glGetTextureParameterIuiv
          911, // glGetTextureParameterfv
          913, // glGetTextureParameteriv
          917, // glGetTextureSubImage
          922, // glGetTransformFeedbacki64_v
          923, // glGetTransformFeedbacki_v
          924, // glGetTransformFeedbackiv
          952, // glGetVertexArrayIndexed64iv
          953, // glGetVertexArrayIndexediv
          958, // glGetVertexArrayiv
          991, // glGetnCompressedTexImage
          993, // glGetnTexImage
          995, // glGetnUniformdv
          997, // glGetnUniformfv
         1000, // glGetnUniformiv
         1003, // glGetnUniformuiv
         1044, // glInvalidateNamedFramebufferData
         1045, // glInvalidateNamedFramebufferSubData
         1142, // glMapNamedBuffer
         1144, // glMapNamedBufferRange
         1188, // glMemoryBarrierByRegion
         1317, // glNamedBufferData
         1322, // glNamedBufferStorage
         1326, // glNamedBufferSubData
         1329, // glNamedFramebufferDrawBuffer
         1330, // glNamedFramebufferDrawBuffers
         1331, // glNamedFramebufferParameteri
         1333, // glNamedFramebufferReadBuffer
         1334, // glNamedFramebufferRenderbuffer
         1339, // glNamedFramebufferTexture
         1345, // glNamedFramebufferTextureLayer
         1359, // glNamedRenderbufferStorage
         1361, // glNamedRenderbufferStorageMultisample
         1670, // glReadnPixels
         1937, // glTextureBarrier
         1939, // glTextureBuffer
         1941, // glTextureBufferRange
         1956, // glTextureParameterIiv
         1958, // glTextureParameterIuiv
         1960, // glTextureParameterf
         1962, // glTextureParameterfv
         1964, // glTextureParameteri
         1966, // glTextureParameteriv
         1970, // glTextureStorage1D
         1972, // glTextureStorage2D
         1974, // glTextureStorage2DMultisample
         1976, // glTextureStorage3D
         1978, // glTextureStorage3DMultisample
         1986, // glTextureSubImage1D
         1988, // glTextureSubImage2D
         1990, // glTextureSubImage3D
         1995, // glTransformFeedbackBufferBase
         1996, // glTransformFeedbackBufferRange
         2124, // glUnmapNamedBuffer
         2176, // glVertexArrayAttribBinding
         2177, // glVertexArrayAttribFormat
         2178, // glVertexArrayAttribIFormat
         2179, // glVertexArrayAttribLFormat
         2181, // glVertexArrayBindingDivisor
         2184, // glVertexArrayElementBuffer
         2203, // glVertexArrayVertexBuffer
         2204  // glVertexArrayVertexBuffers
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_4_6(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->VERSION_4_6) return;
    static const uint16_t s_pfnIdx[] = {
         1204, // glMultiDrawArraysIndirectCount
         1214, // glMultiDrawElementsIndirectCount
         1455, // glPolygonOffsetClamp
         1785  // glSpecializeShader
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ES_VERSION_2_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ES_VERSION_2_0) return;
    static const uint16_t s_pfnIdx[] = {
            5, // glActiveTexture
           23, // glAttachShader
           39, // glBindAttribLocation
           41, // glBindBuffer
           57, // glBindFramebuffer
           69, // glBindRenderbuffer
           75, // glBindTexture
          103, // glBlendColor
          106, // glBlendEquation
          109, // glBlendEquationSeparate
          116, // glBlendFunc
          118, // glBlendFuncSeparate
          134, // glBufferData
          142, // glBufferSubData
          145, // glCheckFramebufferStatus
          151, // glClear
          159, // glClearColor
          165, // glClearDepthf
          176, // glClearStencil
          207, // glColorMask
          227, // glCompileShader
          238, // glCompressedTexImage2D
          244, // glCompressedTexSubImage2D
          283, // glCopyTexImage2D
          287, // glCopyTexSubImage2D
          310, // glCreateProgram
          318, // glCreateShader
          327, // glCullFace
          344, // glDeleteBuffers
          350, // glDeleteFramebuffers
          360, // glDeleteProgram
          367, // glDeleteRenderbuffers
          371, // glDeleteShader
          374, // glDeleteTextures
          383, // glDepthFunc
          384, // glDepthMask
          391, // glDepthRangef
          395, // glDetachShader
          397, // glDisable
          406, // glDisableVertexAttribArray
          412, // glDrawArrays
          429, // glDrawElements
          460, // glEnable
          469, // glEnableVertexAttribArray
          498, // glFinish
          504, // glFlush
          548, // glFramebufferRenderbuffer
          556, // glFramebufferTexture2D
          569, // glFrontFace
          573, // glGenBuffers
          578, // glGenFramebuffers
          590, // glGenRenderbuffers
          595, // glGenTextures
          602, // glGenerateMipmap
          608, // glGetActiveAttrib
          613, // glGetActiveUniform
          623, // glGetAttachedShaders
          624, // glGetAttribLocation
          628, // glGetBooleanv
          630, // glGetBufferParameteriv
          670, // glGetError
          679, // glGetFloatv
          688, // glGetFramebufferAttachmentParameteriv
          713, // glGetIntegerv
          819, // glGetProgramInfoLog
          841, // glGetProgramiv
          859, // glGetRenderbufferParameteriv
          868, // glGetShaderInfoLog
          869, // glGetShaderPrecisionFormat
          870, // glGetShaderSource
          872, // glGetShaderiv
          877, // glGetString
          896, // glGetTexParameterfv
          897, // glGetTexParameteriv
          928, // glGetUniformLocation
          933, // glGetUniformfv
          937, // glGetUniformiv
          970, // glGetVertexAttribPointerv
          976, // glGetVertexAttribfv
          979, // glGetVertexAttribiv
         1013, // glHint
         1051, // glIsBuffer
         1055, // glIsEnabled
         1060, // glIsFramebuffer
         1073, // glIsProgram
         1079, // glIsRenderbuffer
         1083, // glIsShader
         1086, // glIsTexture
         1105, // glLineWidth
         1107, // glLinkProgram
         1422, // glPixelStorei
         1454, // glPolygonOffset
         1669, // glReadPixels
         1676, // glReleaseShaderCompiler
         1678, // glRenderbufferStorage
         1716, // glSampleCoverage
         1732, // glScissor
         1769, // glShaderBinary
         1773, // glShaderSource
         1796, // glStencilFunc
         1797, // glStencilFuncSeparate
         1799, // glStencilMask
         1800, // glStencilMaskSeparate
         1801, // glStencilOp
         1802, // glStencilOpSeparate
         1889, // glTexImage2D
         1904, // glTexParameterf
         1905, // glTexParameterfv
         1906, // glTexParameteri
         1907, // glTexParameteriv
         1931, // glTexSubImage2D
         2005, // glUniform1f
         2007, // glUniform1fv
         2009, // glUniform1i
         2015, // glUniform1iv
         2027, // glUniform2f
         2029, // glUniform2fv
         2031, // glUniform2i
         2037, // glUniform2iv
         2049, // glUniform3f
         2051, // glUniform3fv
         2053, // glUniform3i
         2059, // glUniform3iv
         2071, // glUniform4f
         2073, // glUniform4fv
         2075, // glUniform4i
         2081, // glUniform4iv
         2098, // glUniformMatrix2fv
         2105, // glUniformMatrix3fv
         2112, // glUniformMatrix4fv
         2130, // glUseProgram
         2145, // glValidateProgram
         2212, // glVertexAttrib1f
         2215, // glVertexAttrib1fv
         2232, // glVertexAttrib2f
         2235, // glVertexAttrib2fv
         2252, // glVertexAttrib3f
         2255, // glVertexAttrib3fv
         2288, // glVertexAttrib4f
         2291, // glVertexAttrib4fv
         2409, // glVertexAttribPointer
         2478  // glViewport
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ES_VERSION_3_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ES_VERSION_3_0) return;
    static const uint16_t s_pfnIdx[] = {
           31, // glBeginQuery
           34, // glBeginTransformFeedback
           43, // glBindBufferBase
           48, // glBindBufferRange
           71, // glBindSampler
           80, // glBindTransformFeedback
           82, // glBindVertexArray
          127, // glBlitFramebuffer
          155, // glClearBufferfi
          156, // glClearBufferfv
          157, // glClearBufferiv
          158, // glClearBufferuiv
          183, // glClientWaitSync
          240, // glCompressedTexImage3D
          246, // glCompressedTexSubImage3D
          267, // glCopyBufferSubData
          289, // glCopyTexSubImage3D
          364, // glDeleteQueries
          369, // glDeleteSamplers
          373, // glDeleteSync
          376, // glDeleteTransformFeedbacks
          378, // glDeleteVertexArrays
          415, // glDrawArraysInstanced
          420, // glDrawBuffers
          432, // glDrawElementsInstanced
          443, // glDrawRangeElements
          479, // glEndQuery
          482, // glEndTransformFeedback
          496, // glFenceSync
          505, // glFlushMappedBufferRange
          564, // glFramebufferTextureLayer
          587, // glGenQueries
          592, // glGenSamplers
          597, // glGenTransformFeedbacks
          599, // glGenVertexArrays
          615, // glGetActiveUniformBlockName
          616, // glGetActiveUniformBlockiv
          618, // glGetActiveUniformsiv
          629, // glGetBufferParameteri64v
          633, // glGetBufferPointerv
          682, // glGetFragDataLocation
          707, // glGetInteger64i_v
          708, // glGetInteger64v
          710, // glGetIntegeri_v
          716, // glGetInternalformativ
          814, // glGetProgramBinary
          855, // glGetQueryObjectuiv
          857, // glGetQueryiv
          863, // glGetSamplerParameterfv
          864, // glGetSamplerParameteriv
          878, // glGetStringi
          881, // glGetSynciv
          919, // glGetTransformFeedbackVarying
          925, // glGetUniformBlockIndex
          927, // glGetUniformIndices
          941, // glGetUniformuiv
          961, // glGetVertexAttribIiv
          963, // glGetVertexAttribIuiv
         1043, // glInvalidateFramebuffer
         1046, // glInvalidateSubFramebuffer
         1077, // glIsQuery
         1081, // glIsSampler
         1085, // glIsSync
         1090, // glIsTransformFeedback
         1093, // glIsVertexArray
         1138, // glMapBufferRange
         1417, // glPauseTransformFeedback
         1469, // glProgramBinary
         1503, // glProgramParameteri
         1667, // glReadBuffer
         1680, // glRenderbufferStorageMultisample
         1713, // glResumeTransformFeedback
         1727, // glSamplerParameterf
         1728, // glSamplerParameterfv
         1729, // glSamplerParameteri
         1730, // glSamplerParameteriv
         1893, // glTexImage3D
         1913, // glTexStorage2D
         1916, // glTexStorage3D
         1933, // glTexSubImage3D
         1998, // glTransformFeedbackVaryings
         2017, // glUniform1ui
         2023, // glUniform1uiv
         2039, // glUniform2ui
         2045, // glUniform2uiv
         2061, // glUniform3ui
         2067, // glUniform3uiv
         2083, // glUniform4ui
         2089, // glUniform4uiv
         2091, // glUniformBlockBinding
         2101, // glUniformMatrix2x3fv
         2103, // glUniformMatrix2x4fv
         2108, // glUniformMatrix3x2fv
         2110, // glUniformMatrix3x4fv
         2115, // glUniformMatrix4x2fv
         2117, // glUniformMatrix4x3fv
         2122, // glUnmapBuffer
         2314, // glVertexAttribDivisor
         2344, // glVertexAttribI4i
         2346, // glVertexAttribI4iv
         2352, // glVertexAttribI4ui
         2354, // glVertexAttribI4uiv
         2360, // glVertexAttribIPointer
         2486  // glWaitSync
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ES_VERSION_3_1(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ES_VERSION_3_1) return;
    static const uint16_t s_pfnIdx[] = {
            3, // glActiveShaderProgram
           59, // glBindImageTexture
           68, // glBindProgramPipeline
           84, // glBindVertexBuffer
          321, // glCreateShaderProgramv
          361, // glDeleteProgramPipelines
          409, // glDispatchCompute
          411, // glDispatchComputeIndirect
          414, // glDrawArraysIndirect
          431, // glDrawElementsIndirect
          545, // glFramebufferParameteri
          584, // glGenProgramPipelines
          627, // glGetBooleani_v
          691, // glGetFramebufferParameteriv
          750, // glGetMultisamplefv
          820, // glGetProgramInterfaceiv
          829, // glGetProgramPipelineInfoLog
          830, // glGetProgramPipelineiv
          831, // glGetProgramResourceIndex
          832, // glGetProgramResourceLocation
          834, // glGetProgramResourceName
          836, // glGetProgramResourceiv
          888, // glGetTexLevelParameterfv
          889, // glGetTexLevelParameteriv
         1076, // glIsProgramPipeline
         1187, // glMemoryBarrier
         1188, // glMemoryBarrierByRegion
         1515, // glProgramUniform1f
         1517, // glProgramUniform1fv
         1519, // glProgramUniform1i
         1525, // glProgramUniform1iv
         1527, // glProgramUniform1ui
         1533, // glProgramUniform1uiv
         1539, // glProgramUniform2f
         1541, // glProgramUniform2fv
         1543, // glProgramUniform2i
         1549, // glProgramUniform2iv
         1551, // glProgramUniform2ui
         1557, // glProgramUniform2uiv
         1563, // glProgramUniform3f
         1565, // glProgramUniform3fv
         1567, // glProgramUniform3i
         1573, // glProgramUniform3iv
         1575, // glProgramUniform3ui
         1581, // glProgramUniform3uiv
         1587, // glProgramUniform4f
         1589, // glProgramUniform4fv
         1591, // glProgramUniform4i
         1597, // glProgramUniform4iv
         1599, // glProgramUniform4ui
         1605, // glProgramUniform4uiv
         1613, // glProgramUniformMatrix2fv
         1617, // glProgramUniformMatrix2x3fv
         1621, // glProgramUniformMatrix2x4fv
         1625, // glProgramUniformMatrix3fv
         1629, // glProgramUniformMatrix3x2fv
         1633, // glProgramUniformMatrix3x4fv
         1637, // glProgramUniformMatrix4fv
         1641, // glProgramUniformMatrix4x2fv
         1645, // glProgramUniformMatrix4x3fv
         1722, // glSampleMaski
         1915, // glTexStorage2DMultisample
         2132, // glUseProgramStages
         2147, // glValidateProgramPipeline
         2313, // glVertexAttribBinding
         2316, // glVertexAttribFormat
         2358, // glVertexAttribIFormat
         2429  // glVertexBindingDivisor
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ES_VERSION_3_2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ES_VERSION_3_2) return;
    static const uint16_t s_pfnIdx[] = {
         2549, // glBlendBarrier
          112, // glBlendEquationSeparatei
          114, // glBlendEquationi
          122, // glBlendFuncSeparatei
          124, // glBlendFunci
          209, // glColorMaski
          272, // glCopyImageSubData
          331, // glDebugMessageCallback
          334, // glDebugMessageControl
          337, // glDebugMessageInsert
          408, // glDisablei
          430, // glDrawElementsBaseVertex
          435, // glDrawElementsInstancedBaseVertex
          444, // glDrawRangeElementsBaseVertex
          471, // glEnablei
          553, // glFramebufferTexture
          662, // glGetDebugMessageLog
          694, // glGetGraphicsResetStatus
          778, // glGetObjectLabel
          783, // glGetObjectPtrLabel
          812, // glGetPointerv
          861, // glGetSamplerParameterIiv
          862, // glGetSamplerParameterIuiv
          891, // glGetTexParameterIiv
          893, // glGetTexParameterIuiv
          997, // glGetnUniformfv
         1000, // glGetnUniformiv
         1003, // glGetnUniformuiv
         1057, // glIsEnabledi
         1191, // glMinSampleShading
         1387, // glObjectLabel
         1388, // glObjectPtrLabel
         1398, // glPatchParameteri
         1459, // glPopDebugGroup
         2796, // glPrimitiveBoundingBox
         1653, // glPushDebugGroup
         1670, // glReadnPixels
         1725, // glSamplerParameterIiv
         1726, // glSamplerParameterIuiv
         1835, // glTexBuffer
         1838, // glTexBufferRange
         1900, // glTexParameterIiv
         1902, // glTexParameterIuiv
         1918  // glTexStorage3DMultisample
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_3DFX_tbuffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->_3DFX_tbuffer) return;
    static const uint16_t s_pfnIdx[] = {
         1828  // glTbufferMask3DFX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_debug_output(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_debug_output) return;
    static const uint16_t s_pfnIdx[] = {
          332, // glDebugMessageCallbackAMD
          336, // glDebugMessageEnableAMD
          338, // glDebugMessageInsertAMD
          663  // glGetDebugMessageLogAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_draw_buffers_blend(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_draw_buffers_blend) return;
    static const uint16_t s_pfnIdx[] = {
          108, // glBlendEquationIndexedAMD
          111, // glBlendEquationSeparateIndexedAMD
          117, // glBlendFuncIndexedAMD
          121  // glBlendFuncSeparateIndexedAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_framebuffer_multisample_advanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_framebuffer_multisample_advanced) return;
    static const uint16_t s_pfnIdx[] = {
         1362, // glNamedRenderbufferStorageMultisampleAdvancedAMD
         1681  // glRenderbufferStorageMultisampleAdvancedAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_framebuffer_sample_positions(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_framebuffer_sample_positions) return;
    static const uint16_t s_pfnIdx[] = {
          552, // glFramebufferSamplePositionsfvAMD
          690, // glGetFramebufferParameterfvAMD
          762, // glGetNamedFramebufferParameterfvAMD
         1338  // glNamedFramebufferSamplePositionsfvAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_gpu_shader_int64(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_gpu_shader_int64) return;
    static const uint16_t s_pfnIdx[] = {
          936, // glGetUniformi64vNV
          940, // glGetUniformui64vNV
         1521, // glProgramUniform1i64NV
         1523, // glProgramUniform1i64vNV
         1529, // glProgramUniform1ui64NV
         1531, // glProgramUniform1ui64vNV
         1545, // glProgramUniform2i64NV
         1547, // glProgramUniform2i64vNV
         1553, // glProgramUniform2ui64NV
         1555, // glProgramUniform2ui64vNV
         1569, // glProgramUniform3i64NV
         1571, // glProgramUniform3i64vNV
         1577, // glProgramUniform3ui64NV
         1579, // glProgramUniform3ui64vNV
         1593, // glProgramUniform4i64NV
         1595, // glProgramUniform4i64vNV
         1601, // glProgramUniform4ui64NV
         1603, // glProgramUniform4ui64vNV
         2011, // glUniform1i64NV
         2013, // glUniform1i64vNV
         2019, // glUniform1ui64NV
         2021, // glUniform1ui64vNV
         2033, // glUniform2i64NV
         2035, // glUniform2i64vNV
         2041, // glUniform2ui64NV
         2043, // glUniform2ui64vNV
         2055, // glUniform3i64NV
         2057, // glUniform3i64vNV
         2063, // glUniform3ui64NV
         2065, // glUniform3ui64vNV
         2077, // glUniform4i64NV
         2079, // glUniform4i64vNV
         2085, // glUniform4ui64NV
         2087  // glUniform4ui64vNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_interleaved_elements(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_interleaved_elements) return;
    static const uint16_t s_pfnIdx[] = {
         2408  // glVertexAttribParameteriAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_multi_draw_indirect(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_multi_draw_indirect) return;
    static const uint16_t s_pfnIdx[] = {
         1201, // glMultiDrawArraysIndirectAMD
         1211  // glMultiDrawElementsIndirectAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_name_gen_delete(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_name_gen_delete) return;
    static const uint16_t s_pfnIdx[] = {
          354, // glDeleteNamesAMD
          580, // glGenNamesAMD
         1065  // glIsNameAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_occlusion_query_event(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_occlusion_query_event) return;
    static const uint16_t s_pfnIdx[] = {
         1657  // glQueryObjectParameteruiAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_performance_monitor(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_performance_monitor) return;
    static const uint16_t s_pfnIdx[] = {
           29, // glBeginPerfMonitorAMD
          358, // glDeletePerfMonitorsAMD
          477, // glEndPerfMonitorAMD
          583, // glGenPerfMonitorsAMD
          796, // glGetPerfMonitorCounterDataAMD
          797, // glGetPerfMonitorCounterInfoAMD
          798, // glGetPerfMonitorCounterStringAMD
          799, // glGetPerfMonitorCountersAMD
          800, // glGetPerfMonitorGroupStringAMD
          801, // glGetPerfMonitorGroupsAMD
         1759  // glSelectPerfMonitorCountersAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_sample_positions(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_sample_positions) return;
    static const uint16_t s_pfnIdx[] = {
         1768  // glSetMultisamplefvAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_sparse_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_sparse_texture) return;
    static const uint16_t s_pfnIdx[] = {
         1928, // glTexStorageSparseAMD
         1985  // glTextureStorageSparseAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_stencil_operation_extended(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_stencil_operation_extended) return;
    static const uint16_t s_pfnIdx[] = {
         1804  // glStencilOpValueAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_vertex_shader_tessellator(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->AMD_vertex_shader_tessellator) return;
    static const uint16_t s_pfnIdx[] = {
         1829, // glTessellationFactorAMD
         1830  // glTessellationModeAMD
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_memory_object_flags(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_memory_object_flags) return;
    static const uint16_t s_pfnIdx[] = {
         1924, // glTexStorageMemFlags2DANGLE
         1925, // glTexStorageMemFlags2DMultisampleANGLE
         1926, // glTexStorageMemFlags3DANGLE
         1927  // glTexStorageMemFlags3DMultisampleANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_memory_object_fuchsia(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_memory_object_fuchsia) return;
    static const uint16_t s_pfnIdx[] = {
         1024  // glImportMemoryZirconHandleANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_semaphore_fuchsia(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_semaphore_fuchsia) return;
    static const uint16_t s_pfnIdx[] = {
         1028  // glImportSemaphoreZirconHandleANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_texture_external_update(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_texture_external_update) return;
    static const uint16_t s_pfnIdx[] = {
         1049, // glInvalidateTextureANGLE
         1890  // glTexImage2DExternalANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_element_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->APPLE_element_array) return;
    static const uint16_t s_pfnIdx[] = {
          427, // glDrawElementArrayAPPLE
          441, // glDrawRangeElementArrayAPPLE
          458, // glElementPointerAPPLE
         1206, // glMultiDrawElementArrayAPPLE
         1218  // glMultiDrawRangeElementArrayAPPLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_fence(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->APPLE_fence) return;
    static const uint16_t s_pfnIdx[] = {
          347, // glDeleteFencesAPPLE
          500, // glFinishFenceAPPLE
          502, // glFinishObjectAPPLE
          575, // glGenFencesAPPLE
         1058, // glIsFenceAPPLE
         1763, // glSetFenceAPPLE
         1831, // glTestFenceAPPLE
         1833  // glTestObjectAPPLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_flush_buffer_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->APPLE_flush_buffer_range) return;
    static const uint16_t s_pfnIdx[] = {
          138, // glBufferParameteriAPPLE
          506  // glFlushMappedBufferRangeAPPLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_object_purgeable(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->APPLE_object_purgeable) return;
    static const uint16_t s_pfnIdx[] = {
          781, // glGetObjectParameterivAPPLE
         1389, // glObjectPurgeableAPPLE
         1390  // glObjectUnpurgeableAPPLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_texture_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->APPLE_texture_range) return;
    static const uint16_t s_pfnIdx[] = {
          895, // glGetTexParameterPointervAPPLE
         1968  // glTextureRangeAPPLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_vertex_array_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->APPLE_vertex_array_object) return;
    static const uint16_t s_pfnIdx[] = {
           83, // glBindVertexArrayAPPLE
          379, // glDeleteVertexArraysAPPLE
          600, // glGenVertexArraysAPPLE
         1094  // glIsVertexArrayAPPLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_vertex_array_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->APPLE_vertex_array_range) return;
    static const uint16_t s_pfnIdx[] = {
          512, // glFlushVertexArrayRangeAPPLE
         2189, // glVertexArrayParameteriAPPLE
         2190  // glVertexArrayRangeAPPLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_vertex_program_evaluators(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->APPLE_vertex_program_evaluators) return;
    static const uint16_t s_pfnIdx[] = {
          405, // glDisableVertexAttribAPPLE
          468, // glEnableVertexAttribAPPLE
         1095, // glIsVertexAttribEnabledAPPLE
         1150, // glMapVertexAttrib1dAPPLE
         1151, // glMapVertexAttrib1fAPPLE
         1152, // glMapVertexAttrib2dAPPLE
         1153  // glMapVertexAttrib2fAPPLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_ES2_compatibility(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_ES2_compatibility) return;
    static const uint16_t s_pfnIdx[] = {
          165, // glClearDepthf
          391, // glDepthRangef
          869, // glGetShaderPrecisionFormat
         1676, // glReleaseShaderCompiler
         1769  // glShaderBinary
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_ES3_1_compatibility(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_ES3_1_compatibility) return;
    static const uint16_t s_pfnIdx[] = {
         1188  // glMemoryBarrierByRegion
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_ES3_2_compatibility(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_ES3_2_compatibility) return;
    static const uint16_t s_pfnIdx[] = {
         1463  // glPrimitiveBoundingBoxARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_base_instance(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_base_instance) return;
    static const uint16_t s_pfnIdx[] = {
          417, // glDrawArraysInstancedBaseInstance
          434, // glDrawElementsInstancedBaseInstance
          436  // glDrawElementsInstancedBaseVertexBaseInstance
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_bindless_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_bindless_texture) return;
    static const uint16_t s_pfnIdx[] = {
          701, // glGetImageHandleARB
          899, // glGetTextureHandleARB
          915, // glGetTextureSamplerHandleARB
          968, // glGetVertexAttribLui64vARB
         1062, // glIsImageHandleResidentARB
         1088, // glIsTextureHandleResidentARB
         1124, // glMakeImageHandleNonResidentARB
         1126, // glMakeImageHandleResidentARB
         1130, // glMakeTextureHandleNonResidentARB
         1132, // glMakeTextureHandleResidentARB
         1607, // glProgramUniformHandleui64ARB
         1609, // glProgramUniformHandleui64vARB
         2093, // glUniformHandleui64ARB
         2095, // glUniformHandleui64vARB
         2368, // glVertexAttribL1ui64ARB
         2370  // glVertexAttribL1ui64vARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_blend_func_extended(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_blend_func_extended) return;
    static const uint16_t s_pfnIdx[] = {
           55, // glBindFragDataLocationIndexed
          681  // glGetFragDataIndex
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_buffer_storage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_buffer_storage) return;
    static const uint16_t s_pfnIdx[] = {
          139  // glBufferStorage
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_cl_event(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_cl_event) return;
    static const uint16_t s_pfnIdx[] = {
          323  // glCreateSyncFromCLeventARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_clear_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_clear_buffer_object) return;
    static const uint16_t s_pfnIdx[] = {
          153, // glClearBufferData
          154  // glClearBufferSubData
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_clear_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_clear_texture) return;
    static const uint16_t s_pfnIdx[] = {
          177, // glClearTexImage
          178  // glClearTexSubImage
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_clip_control(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_clip_control) return;
    static const uint16_t s_pfnIdx[] = {
          184  // glClipControl
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_color_buffer_float(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_color_buffer_float) return;
    static const uint16_t s_pfnIdx[] = {
          150  // glClampColorARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_compute_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_compute_shader) return;
    static const uint16_t s_pfnIdx[] = {
          409, // glDispatchCompute
          411  // glDispatchComputeIndirect
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_compute_variable_group_size(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_compute_variable_group_size) return;
    static const uint16_t s_pfnIdx[] = {
          410  // glDispatchComputeGroupSizeARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_copy_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_copy_buffer) return;
    static const uint16_t s_pfnIdx[] = {
          267  // glCopyBufferSubData
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_copy_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_copy_image) return;
    static const uint16_t s_pfnIdx[] = {
          272  // glCopyImageSubData
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_debug_output(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_debug_output) return;
    static const uint16_t s_pfnIdx[] = {
          333, // glDebugMessageCallbackARB
          335, // glDebugMessageControlARB
          339, // glDebugMessageInsertARB
          664  // glGetDebugMessageLogARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_direct_state_access(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_direct_state_access) return;
    static const uint16_t s_pfnIdx[] = {
           77, // glBindTextureUnit
          131, // glBlitNamedFramebuffer
          147, // glCheckNamedFramebufferStatus
          168, // glClearNamedBufferData
          170, // glClearNamedBufferSubData
          172, // glClearNamedFramebufferfi
          173, // glClearNamedFramebufferfv
          174, // glClearNamedFramebufferiv
          175, // glClearNamedFramebufferuiv
          251, // glCompressedTextureSubImage1D
          253, // glCompressedTextureSubImage2D
          255, // glCompressedTextureSubImage3D
          279, // glCopyNamedBufferSubData
          293, // glCopyTextureSubImage1D
          295, // glCopyTextureSubImage2D
          297, // glCopyTextureSubImage3D
          305, // glCreateBuffers
          307, // glCreateFramebuffers
          312, // glCreateProgramPipelines
          314, // glCreateQueries
          315, // glCreateRenderbuffers
          316, // glCreateSamplers
          324, // glCreateTextures
          325, // glCreateTransformFeedbacks
          326, // glCreateVertexArrays
          402, // glDisableVertexArrayAttrib
          465, // glEnableVertexArrayAttrib
          507, // glFlushMappedNamedBufferRange
          605, // glGenerateTextureMipmap
          654, // glGetCompressedTextureImage
          752, // glGetNamedBufferParameteri64v
          753, // glGetNamedBufferParameteriv
          756, // glGetNamedBufferPointerv
          758, // glGetNamedBufferSubData
          760, // glGetNamedFramebufferAttachmentParameteriv
          763, // glGetNamedFramebufferParameteriv
          771, // glGetNamedRenderbufferParameteriv
          844, // glGetQueryBufferObjecti64v
          845, // glGetQueryBufferObjectiv
          846, // glGetQueryBufferObjectui64v
          847, // glGetQueryBufferObjectuiv
          901, // glGetTextureImage
          903, // glGetTextureLevelParameterfv
          905, // glGetTextureLevelParameteriv
          907, // glGetTextureParameterIiv
          909, // glGetTextureParameterIuiv
          911, // glGetTextureParameterfv
          913, // glGetTextureParameteriv
          922, // glGetTransformFeedbacki64_v
          923, // glGetTransformFeedbacki_v
          924, // glGetTransformFeedbackiv
          952, // glGetVertexArrayIndexed64iv
          953, // glGetVertexArrayIndexediv
          958, // glGetVertexArrayiv
         1044, // glInvalidateNamedFramebufferData
         1045, // glInvalidateNamedFramebufferSubData
         1142, // glMapNamedBuffer
         1144, // glMapNamedBufferRange
         1317, // glNamedBufferData
         1322, // glNamedBufferStorage
         1326, // glNamedBufferSubData
         1329, // glNamedFramebufferDrawBuffer
         1330, // glNamedFramebufferDrawBuffers
         1331, // glNamedFramebufferParameteri
         1333, // glNamedFramebufferReadBuffer
         1334, // glNamedFramebufferRenderbuffer
         1339, // glNamedFramebufferTexture
         1345, // glNamedFramebufferTextureLayer
         1359, // glNamedRenderbufferStorage
         1361, // glNamedRenderbufferStorageMultisample
         1939, // glTextureBuffer
         1941, // glTextureBufferRange
         1956, // glTextureParameterIiv
         1958, // glTextureParameterIuiv
         1960, // glTextureParameterf
         1962, // glTextureParameterfv
         1964, // glTextureParameteri
         1966, // glTextureParameteriv
         1970, // glTextureStorage1D
         1972, // glTextureStorage2D
         1974, // glTextureStorage2DMultisample
         1976, // glTextureStorage3D
         1978, // glTextureStorage3DMultisample
         1986, // glTextureSubImage1D
         1988, // glTextureSubImage2D
         1990, // glTextureSubImage3D
         1995, // glTransformFeedbackBufferBase
         1996, // glTransformFeedbackBufferRange
         2124, // glUnmapNamedBuffer
         2176, // glVertexArrayAttribBinding
         2177, // glVertexArrayAttribFormat
         2178, // glVertexArrayAttribIFormat
         2179, // glVertexArrayAttribLFormat
         2181, // glVertexArrayBindingDivisor
         2184, // glVertexArrayElementBuffer
         2203, // glVertexArrayVertexBuffer
         2204  // glVertexArrayVertexBuffers
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_draw_buffers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_draw_buffers) return;
    static const uint16_t s_pfnIdx[] = {
          421  // glDrawBuffersARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_draw_buffers_blend(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_draw_buffers_blend) return;
    static const uint16_t s_pfnIdx[] = {
          113, // glBlendEquationSeparateiARB
          115, // glBlendEquationiARB
          123, // glBlendFuncSeparateiARB
          125  // glBlendFunciARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_draw_elements_base_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_draw_elements_base_vertex) return;
    static const uint16_t s_pfnIdx[] = {
          430, // glDrawElementsBaseVertex
          435, // glDrawElementsInstancedBaseVertex
          444, // glDrawRangeElementsBaseVertex
         1208  // glMultiDrawElementsBaseVertex
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_draw_indirect(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_draw_indirect) return;
    static const uint16_t s_pfnIdx[] = {
          414, // glDrawArraysIndirect
          431  // glDrawElementsIndirect
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_draw_instanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_draw_instanced) return;
    static const uint16_t s_pfnIdx[] = {
          416, // glDrawArraysInstancedARB
          433  // glDrawElementsInstancedARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_fragment_program(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_fragment_program) return;
    static const uint16_t s_pfnIdx[] = {
           66, // glBindProgramARB
          362, // glDeleteProgramsARB
          585, // glGenProgramsARB
          817, // glGetProgramEnvParameterdvARB
          818, // glGetProgramEnvParameterfvARB
          823, // glGetProgramLocalParameterdvARB
          824, // glGetProgramLocalParameterfvARB
          838, // glGetProgramStringARB
          842, // glGetProgramivARB
         1074, // glIsProgramARB
         1473, // glProgramEnvParameter4dARB
         1474, // glProgramEnvParameter4dvARB
         1475, // glProgramEnvParameter4fARB
         1476, // glProgramEnvParameter4fvARB
         1484, // glProgramLocalParameter4dARB
         1485, // glProgramLocalParameter4dvARB
         1486, // glProgramLocalParameter4fARB
         1487, // glProgramLocalParameter4fvARB
         1509  // glProgramStringARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_framebuffer_no_attachments(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_framebuffer_no_attachments) return;
    static const uint16_t s_pfnIdx[] = {
          545, // glFramebufferParameteri
          691  // glGetFramebufferParameteriv
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_framebuffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_framebuffer_object) return;
    static const uint16_t s_pfnIdx[] = {
           57, // glBindFramebuffer
           69, // glBindRenderbuffer
          127, // glBlitFramebuffer
          145, // glCheckFramebufferStatus
          350, // glDeleteFramebuffers
          367, // glDeleteRenderbuffers
          548, // glFramebufferRenderbuffer
          554, // glFramebufferTexture1D
          556, // glFramebufferTexture2D
          558, // glFramebufferTexture3D
          564, // glFramebufferTextureLayer
          578, // glGenFramebuffers
          590, // glGenRenderbuffers
          602, // glGenerateMipmap
          688, // glGetFramebufferAttachmentParameteriv
          859, // glGetRenderbufferParameteriv
         1060, // glIsFramebuffer
         1079, // glIsRenderbuffer
         1678, // glRenderbufferStorage
         1680  // glRenderbufferStorageMultisample
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_geometry_shader4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_geometry_shader4) return;
    static const uint16_t s_pfnIdx[] = {
          560, // glFramebufferTextureARB
          562, // glFramebufferTextureFaceARB
          565, // glFramebufferTextureLayerARB
         1504  // glProgramParameteriARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_get_program_binary(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_get_program_binary) return;
    static const uint16_t s_pfnIdx[] = {
          814, // glGetProgramBinary
         1469, // glProgramBinary
         1503  // glProgramParameteri
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_get_texture_sub_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_get_texture_sub_image) return;
    static const uint16_t s_pfnIdx[] = {
          656, // glGetCompressedTextureSubImage
          917  // glGetTextureSubImage
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_gl_spirv(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_gl_spirv) return;
    static const uint16_t s_pfnIdx[] = {
         1786  // glSpecializeShaderARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_gpu_shader_fp64(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_gpu_shader_fp64) return;
    static const uint16_t s_pfnIdx[] = {
          932, // glGetUniformdv
         2003, // glUniform1d
         2004, // glUniform1dv
         2025, // glUniform2d
         2026, // glUniform2dv
         2047, // glUniform3d
         2048, // glUniform3dv
         2069, // glUniform4d
         2070, // glUniform4dv
         2097, // glUniformMatrix2dv
         2100, // glUniformMatrix2x3dv
         2102, // glUniformMatrix2x4dv
         2104, // glUniformMatrix3dv
         2107, // glUniformMatrix3x2dv
         2109, // glUniformMatrix3x4dv
         2111, // glUniformMatrix4dv
         2114, // glUniformMatrix4x2dv
         2116  // glUniformMatrix4x3dv
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_gpu_shader_int64(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_gpu_shader_int64) return;
    static const uint16_t s_pfnIdx[] = {
          935, // glGetUniformi64vARB
          939, // glGetUniformui64vARB
          999, // glGetnUniformi64vARB
         1002, // glGetnUniformui64vARB
         1520, // glProgramUniform1i64ARB
         1522, // glProgramUniform1i64vARB
         1528, // glProgramUniform1ui64ARB
         1530, // glProgramUniform1ui64vARB
         1544, // glProgramUniform2i64ARB
         1546, // glProgramUniform2i64vARB
         1552, // glProgramUniform2ui64ARB
         1554, // glProgramUniform2ui64vARB
         1568, // glProgramUniform3i64ARB
         1570, // glProgramUniform3i64vARB
         1576, // glProgramUniform3ui64ARB
         1578, // glProgramUniform3ui64vARB
         1592, // glProgramUniform4i64ARB
         1594, // glProgramUniform4i64vARB
         1600, // glProgramUniform4ui64ARB
         1602, // glProgramUniform4ui64vARB
         2010, // glUniform1i64ARB
         2012, // glUniform1i64vARB
         2018, // glUniform1ui64ARB
         2020, // glUniform1ui64vARB
         2032, // glUniform2i64ARB
         2034, // glUniform2i64vARB
         2040, // glUniform2ui64ARB
         2042, // glUniform2ui64vARB
         2054, // glUniform3i64ARB
         2056, // glUniform3i64vARB
         2062, // glUniform3ui64ARB
         2064, // glUniform3ui64vARB
         2076, // glUniform4i64ARB
         2078, // glUniform4i64vARB
         2084, // glUniform4ui64ARB
         2086  // glUniform4ui64vARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_imaging(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_imaging) return;
    static const uint16_t s_pfnIdx[] = {
          103, // glBlendColor
          106  // glBlendEquation
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_indirect_parameters(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_indirect_parameters) return;
    static const uint16_t s_pfnIdx[] = {
         1205, // glMultiDrawArraysIndirectCountARB
         1215  // glMultiDrawElementsIndirectCountARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_instanced_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_instanced_arrays) return;
    static const uint16_t s_pfnIdx[] = {
         2315  // glVertexAttribDivisorARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_internalformat_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_internalformat_query) return;
    static const uint16_t s_pfnIdx[] = {
          716  // glGetInternalformativ
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_internalformat_query2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_internalformat_query2) return;
    static const uint16_t s_pfnIdx[] = {
          715  // glGetInternalformati64v
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_invalidate_subdata(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_invalidate_subdata) return;
    static const uint16_t s_pfnIdx[] = {
         1041, // glInvalidateBufferData
         1042, // glInvalidateBufferSubData
         1043, // glInvalidateFramebuffer
         1046, // glInvalidateSubFramebuffer
         1047, // glInvalidateTexImage
         1048  // glInvalidateTexSubImage
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_map_buffer_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_map_buffer_range) return;
    static const uint16_t s_pfnIdx[] = {
          505, // glFlushMappedBufferRange
         1138  // glMapBufferRange
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_matrix_palette(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_matrix_palette) return;
    static const uint16_t s_pfnIdx[] = {
          330, // glCurrentPaletteMatrixARB
         1157, // glMatrixIndexPointerARB
         1158, // glMatrixIndexubvARB
         1159, // glMatrixIndexuivARB
         1160  // glMatrixIndexusvARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_multi_bind(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_multi_bind) return;
    static const uint16_t s_pfnIdx[] = {
           51, // glBindBuffersBase
           52, // glBindBuffersRange
           61, // glBindImageTextures
           72, // glBindSamplers
           79, // glBindTextures
           85  // glBindVertexBuffers
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_multi_draw_indirect(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_multi_draw_indirect) return;
    static const uint16_t s_pfnIdx[] = {
         1200, // glMultiDrawArraysIndirect
         1210  // glMultiDrawElementsIndirect
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_multisample) return;
    static const uint16_t s_pfnIdx[] = {
         1717  // glSampleCoverageARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_multitexture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_multitexture) return;
    static const uint16_t s_pfnIdx[] = {
            6, // glActiveTextureARB
          179, // glClientActiveTextureARB
         1224, // glMultiTexCoord1dARB
         1225, // glMultiTexCoord1dvARB
         1226, // glMultiTexCoord1fARB
         1227, // glMultiTexCoord1fvARB
         1230, // glMultiTexCoord1iARB
         1231, // glMultiTexCoord1ivARB
         1232, // glMultiTexCoord1sARB
         1233, // glMultiTexCoord1svARB
         1238, // glMultiTexCoord2dARB
         1239, // glMultiTexCoord2dvARB
         1240, // glMultiTexCoord2fARB
         1241, // glMultiTexCoord2fvARB
         1244, // glMultiTexCoord2iARB
         1245, // glMultiTexCoord2ivARB
         1246, // glMultiTexCoord2sARB
         1247, // glMultiTexCoord2svARB
         1252, // glMultiTexCoord3dARB
         1253, // glMultiTexCoord3dvARB
         1254, // glMultiTexCoord3fARB
         1255, // glMultiTexCoord3fvARB
         1258, // glMultiTexCoord3iARB
         1259, // glMultiTexCoord3ivARB
         1260, // glMultiTexCoord3sARB
         1261, // glMultiTexCoord3svARB
         1266, // glMultiTexCoord4dARB
         1267, // glMultiTexCoord4dvARB
         1268, // glMultiTexCoord4fARB
         1269, // glMultiTexCoord4fvARB
         1272, // glMultiTexCoord4iARB
         1273, // glMultiTexCoord4ivARB
         1274, // glMultiTexCoord4sARB
         1275  // glMultiTexCoord4svARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_occlusion_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_occlusion_query) return;
    static const uint16_t s_pfnIdx[] = {
           32, // glBeginQueryARB
          365, // glDeleteQueriesARB
          480, // glEndQueryARB
          588, // glGenQueriesARB
          852, // glGetQueryObjectivARB
          856, // glGetQueryObjectuivARB
          858, // glGetQueryivARB
         1078  // glIsQueryARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_parallel_shader_compile(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_parallel_shader_compile) return;
    static const uint16_t s_pfnIdx[] = {
         1185  // glMaxShaderCompilerThreadsARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_point_parameters(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_point_parameters) return;
    static const uint16_t s_pfnIdx[] = {
         1437, // glPointParameterfARB
         1441  // glPointParameterfvARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_polygon_offset_clamp(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_polygon_offset_clamp) return;
    static const uint16_t s_pfnIdx[] = {
         1455  // glPolygonOffsetClamp
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_program_interface_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_program_interface_query) return;
    static const uint16_t s_pfnIdx[] = {
          820, // glGetProgramInterfaceiv
          831, // glGetProgramResourceIndex
          832, // glGetProgramResourceLocation
          833, // glGetProgramResourceLocationIndex
          834, // glGetProgramResourceName
          836  // glGetProgramResourceiv
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_provoking_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_provoking_vertex) return;
    static const uint16_t s_pfnIdx[] = {
         1650  // glProvokingVertex
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_robustness(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_robustness) return;
    static const uint16_t s_pfnIdx[] = {
          695, // glGetGraphicsResetStatusARB
          992, // glGetnCompressedTexImageARB
          994, // glGetnTexImageARB
          996, // glGetnUniformdvARB
          998, // glGetnUniformfvARB
         1001, // glGetnUniformivARB
         1004, // glGetnUniformuivARB
         1671  // glReadnPixelsARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_sample_locations(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_sample_locations) return;
    static const uint16_t s_pfnIdx[] = {
          492, // glEvaluateDepthValuesARB
          550, // glFramebufferSampleLocationsfvARB
         1336  // glNamedFramebufferSampleLocationsfvARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_sample_shading(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_sample_shading) return;
    static const uint16_t s_pfnIdx[] = {
         1192  // glMinSampleShadingARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_sampler_objects(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_sampler_objects) return;
    static const uint16_t s_pfnIdx[] = {
           71, // glBindSampler
          369, // glDeleteSamplers
          592, // glGenSamplers
          861, // glGetSamplerParameterIiv
          862, // glGetSamplerParameterIuiv
          863, // glGetSamplerParameterfv
          864, // glGetSamplerParameteriv
         1081, // glIsSampler
         1725, // glSamplerParameterIiv
         1726, // glSamplerParameterIuiv
         1727, // glSamplerParameterf
         1728, // glSamplerParameterfv
         1729, // glSamplerParameteri
         1730  // glSamplerParameteriv
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_separate_shader_objects(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_separate_shader_objects) return;
    static const uint16_t s_pfnIdx[] = {
            3, // glActiveShaderProgram
           68, // glBindProgramPipeline
          321, // glCreateShaderProgramv
          361, // glDeleteProgramPipelines
          584, // glGenProgramPipelines
          829, // glGetProgramPipelineInfoLog
          830, // glGetProgramPipelineiv
         1076, // glIsProgramPipeline
         1503, // glProgramParameteri
         1511, // glProgramUniform1d
         1513, // glProgramUniform1dv
         1515, // glProgramUniform1f
         1517, // glProgramUniform1fv
         1519, // glProgramUniform1i
         1525, // glProgramUniform1iv
         1527, // glProgramUniform1ui
         1533, // glProgramUniform1uiv
         1535, // glProgramUniform2d
         1537, // glProgramUniform2dv
         1539, // glProgramUniform2f
         1541, // glProgramUniform2fv
         1543, // glProgramUniform2i
         1549, // glProgramUniform2iv
         1551, // glProgramUniform2ui
         1557, // glProgramUniform2uiv
         1559, // glProgramUniform3d
         1561, // glProgramUniform3dv
         1563, // glProgramUniform3f
         1565, // glProgramUniform3fv
         1567, // glProgramUniform3i
         1573, // glProgramUniform3iv
         1575, // glProgramUniform3ui
         1581, // glProgramUniform3uiv
         1583, // glProgramUniform4d
         1585, // glProgramUniform4dv
         1587, // glProgramUniform4f
         1589, // glProgramUniform4fv
         1591, // glProgramUniform4i
         1597, // glProgramUniform4iv
         1599, // glProgramUniform4ui
         1605, // glProgramUniform4uiv
         1611, // glProgramUniformMatrix2dv
         1613, // glProgramUniformMatrix2fv
         1615, // glProgramUniformMatrix2x3dv
         1617, // glProgramUniformMatrix2x3fv
         1619, // glProgramUniformMatrix2x4dv
         1621, // glProgramUniformMatrix2x4fv
         1623, // glProgramUniformMatrix3dv
         1625, // glProgramUniformMatrix3fv
         1627, // glProgramUniformMatrix3x2dv
         1629, // glProgramUniformMatrix3x2fv
         1631, // glProgramUniformMatrix3x4dv
         1633, // glProgramUniformMatrix3x4fv
         1635, // glProgramUniformMatrix4dv
         1637, // glProgramUniformMatrix4fv
         1639, // glProgramUniformMatrix4x2dv
         1641, // glProgramUniformMatrix4x2fv
         1643, // glProgramUniformMatrix4x3dv
         1645, // glProgramUniformMatrix4x3fv
         2132, // glUseProgramStages
         2147  // glValidateProgramPipeline
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_shader_atomic_counters(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_shader_atomic_counters) return;
    static const uint16_t s_pfnIdx[] = {
          607  // glGetActiveAtomicCounterBufferiv
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_shader_image_load_store(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_shader_image_load_store) return;
    static const uint16_t s_pfnIdx[] = {
           59, // glBindImageTexture
         1187  // glMemoryBarrier
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_shader_objects(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_shader_objects) return;
    static const uint16_t s_pfnIdx[] = {
           22, // glAttachObjectARB
          228, // glCompileShaderARB
          311, // glCreateProgramObjectARB
          319, // glCreateShaderObjectARB
          355, // glDeleteObjectARB
          394, // glDetachObjectARB
          614, // glGetActiveUniformARB
          622, // glGetAttachedObjectsARB
          696, // glGetHandleARB
          705, // glGetInfoLogARB
          780, // glGetObjectParameterfvARB
          782, // glGetObjectParameterivARB
          871, // glGetShaderSourceARB
          929, // glGetUniformLocationARB
          934, // glGetUniformfvARB
          938, // glGetUniformivARB
         1108, // glLinkProgramARB
         1774, // glShaderSourceARB
         2006, // glUniform1fARB
         2008, // glUniform1fvARB
         2014, // glUniform1iARB
         2016, // glUniform1ivARB
         2028, // glUniform2fARB
         2030, // glUniform2fvARB
         2036, // glUniform2iARB
         2038, // glUniform2ivARB
         2050, // glUniform3fARB
         2052, // glUniform3fvARB
         2058, // glUniform3iARB
         2060, // glUniform3ivARB
         2072, // glUniform4fARB
         2074, // glUniform4fvARB
         2080, // glUniform4iARB
         2082, // glUniform4ivARB
         2099, // glUniformMatrix2fvARB
         2106, // glUniformMatrix3fvARB
         2113, // glUniformMatrix4fvARB
         2131, // glUseProgramObjectARB
         2146  // glValidateProgramARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_shader_storage_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_shader_storage_buffer_object) return;
    static const uint16_t s_pfnIdx[] = {
         1775  // glShaderStorageBlockBinding
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_shader_subroutine(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_shader_subroutine) return;
    static const uint16_t s_pfnIdx[] = {
          610, // glGetActiveSubroutineName
          611, // glGetActiveSubroutineUniformName
          612, // glGetActiveSubroutineUniformiv
          837, // glGetProgramStageiv
          879, // glGetSubroutineIndex
          880, // glGetSubroutineUniformLocation
          931, // glGetUniformSubroutineuiv
         2118  // glUniformSubroutinesuiv
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_shading_language_include(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_shading_language_include) return;
    static const uint16_t s_pfnIdx[] = {
          229, // glCompileShaderIncludeARB
          353, // glDeleteNamedStringARB
          773, // glGetNamedStringARB
          774, // glGetNamedStringivARB
         1067, // glIsNamedStringARB
         1365  // glNamedStringARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_sparse_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_sparse_buffer) return;
    static const uint16_t s_pfnIdx[] = {
          136, // glBufferPageCommitmentARB
         1319, // glNamedBufferPageCommitmentARB
         1320  // glNamedBufferPageCommitmentEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_sparse_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_sparse_texture) return;
    static const uint16_t s_pfnIdx[] = {
         1898  // glTexPageCommitmentARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_sync(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_sync) return;
    static const uint16_t s_pfnIdx[] = {
          183, // glClientWaitSync
          373, // glDeleteSync
          496, // glFenceSync
          708, // glGetInteger64v
          881, // glGetSynciv
         1085, // glIsSync
         2486  // glWaitSync
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_tessellation_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_tessellation_shader) return;
    static const uint16_t s_pfnIdx[] = {
         1397, // glPatchParameterfv
         1398  // glPatchParameteri
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_barrier(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_texture_barrier) return;
    static const uint16_t s_pfnIdx[] = {
         1937  // glTextureBarrier
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_texture_buffer_object) return;
    static const uint16_t s_pfnIdx[] = {
         1836  // glTexBufferARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_buffer_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_texture_buffer_range) return;
    static const uint16_t s_pfnIdx[] = {
         1838  // glTexBufferRange
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_compression(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_texture_compression) return;
    static const uint16_t s_pfnIdx[] = {
          237, // glCompressedTexImage1DARB
          239, // glCompressedTexImage2DARB
          241, // glCompressedTexImage3DARB
          243, // glCompressedTexSubImage1DARB
          245, // glCompressedTexSubImage2DARB
          247, // glCompressedTexSubImage3DARB
          653  // glGetCompressedTexImageARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_texture_multisample) return;
    static const uint16_t s_pfnIdx[] = {
          750, // glGetMultisamplefv
         1722, // glSampleMaski
         1891, // glTexImage2DMultisample
         1895  // glTexImage3DMultisample
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_storage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_texture_storage) return;
    static const uint16_t s_pfnIdx[] = {
         1911, // glTexStorage1D
         1913, // glTexStorage2D
         1916  // glTexStorage3D
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_storage_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_texture_storage_multisample) return;
    static const uint16_t s_pfnIdx[] = {
         1915, // glTexStorage2DMultisample
         1918  // glTexStorage3DMultisample
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_view(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_texture_view) return;
    static const uint16_t s_pfnIdx[] = {
         1992  // glTextureView
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_timer_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_timer_query) return;
    static const uint16_t s_pfnIdx[] = {
          849, // glGetQueryObjecti64v
          853, // glGetQueryObjectui64v
         1655  // glQueryCounter
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_transform_feedback2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_transform_feedback2) return;
    static const uint16_t s_pfnIdx[] = {
           80, // glBindTransformFeedback
          376, // glDeleteTransformFeedbacks
          447, // glDrawTransformFeedback
          597, // glGenTransformFeedbacks
         1090, // glIsTransformFeedback
         1417, // glPauseTransformFeedback
         1713  // glResumeTransformFeedback
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_transform_feedback3(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_transform_feedback3) return;
    static const uint16_t s_pfnIdx[] = {
           33, // glBeginQueryIndexed
          450, // glDrawTransformFeedbackStream
          481, // glEndQueryIndexed
          848  // glGetQueryIndexediv
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_transform_feedback_instanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_transform_feedback_instanced) return;
    static const uint16_t s_pfnIdx[] = {
          448, // glDrawTransformFeedbackInstanced
          451  // glDrawTransformFeedbackStreamInstanced
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_transpose_matrix(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_transpose_matrix) return;
    static const uint16_t s_pfnIdx[] = {
         1117, // glLoadTransposeMatrixdARB
         1118, // glLoadTransposeMatrixfARB
         1195, // glMultTransposeMatrixdARB
         1196  // glMultTransposeMatrixfARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_uniform_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_uniform_buffer_object) return;
    static const uint16_t s_pfnIdx[] = {
           43, // glBindBufferBase
           48, // glBindBufferRange
          615, // glGetActiveUniformBlockName
          616, // glGetActiveUniformBlockiv
          617, // glGetActiveUniformName
          618, // glGetActiveUniformsiv
          710, // glGetIntegeri_v
          925, // glGetUniformBlockIndex
          927, // glGetUniformIndices
         2091  // glUniformBlockBinding
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_array_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_vertex_array_object) return;
    static const uint16_t s_pfnIdx[] = {
           82, // glBindVertexArray
          378, // glDeleteVertexArrays
          599, // glGenVertexArrays
         1093  // glIsVertexArray
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_attrib_64bit(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_vertex_attrib_64bit) return;
    static const uint16_t s_pfnIdx[] = {
          965, // glGetVertexAttribLdv
         2362, // glVertexAttribL1d
         2364, // glVertexAttribL1dv
         2372, // glVertexAttribL2d
         2374, // glVertexAttribL2dv
         2380, // glVertexAttribL3d
         2382, // glVertexAttribL3dv
         2388, // glVertexAttribL4d
         2390, // glVertexAttribL4dv
         2398  // glVertexAttribLPointer
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_attrib_binding(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_vertex_attrib_binding) return;
    static const uint16_t s_pfnIdx[] = {
           84, // glBindVertexBuffer
         2313, // glVertexAttribBinding
         2316, // glVertexAttribFormat
         2358, // glVertexAttribIFormat
         2396, // glVertexAttribLFormat
         2429  // glVertexBindingDivisor
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_blend(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_vertex_blend) return;
    static const uint16_t s_pfnIdx[] = {
         2430, // glVertexBlendARB
         2489, // glWeightPointerARB
         2490, // glWeightbvARB
         2491, // glWeightdvARB
         2492, // glWeightfvARB
         2493, // glWeightivARB
         2494, // glWeightsvARB
         2495, // glWeightubvARB
         2496, // glWeightuivARB
         2497  // glWeightusvARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_vertex_buffer_object) return;
    static const uint16_t s_pfnIdx[] = {
           42, // glBindBufferARB
          135, // glBufferDataARB
          143, // glBufferSubDataARB
          345, // glDeleteBuffersARB
          574, // glGenBuffersARB
          631, // glGetBufferParameterivARB
          634, // glGetBufferPointervARB
          636, // glGetBufferSubDataARB
         1052, // glIsBufferARB
         1137, // glMapBufferARB
         2123  // glUnmapBufferARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_program(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_vertex_program) return;
    static const uint16_t s_pfnIdx[] = {
           66, // glBindProgramARB
          362, // glDeleteProgramsARB
          407, // glDisableVertexAttribArrayARB
          470, // glEnableVertexAttribArrayARB
          585, // glGenProgramsARB
          817, // glGetProgramEnvParameterdvARB
          818, // glGetProgramEnvParameterfvARB
          823, // glGetProgramLocalParameterdvARB
          824, // glGetProgramLocalParameterfvARB
          838, // glGetProgramStringARB
          842, // glGetProgramivARB
          971, // glGetVertexAttribPointervARB
          974, // glGetVertexAttribdvARB
          977, // glGetVertexAttribfvARB
          980, // glGetVertexAttribivARB
         1074, // glIsProgramARB
         1473, // glProgramEnvParameter4dARB
         1474, // glProgramEnvParameter4dvARB
         1475, // glProgramEnvParameter4fARB
         1476, // glProgramEnvParameter4fvARB
         1484, // glProgramLocalParameter4dARB
         1485, // glProgramLocalParameter4dvARB
         1486, // glProgramLocalParameter4fARB
         1487, // glProgramLocalParameter4fvARB
         1509, // glProgramStringARB
         2207, // glVertexAttrib1dARB
         2210, // glVertexAttrib1dvARB
         2213, // glVertexAttrib1fARB
         2216, // glVertexAttrib1fvARB
         2221, // glVertexAttrib1sARB
         2224, // glVertexAttrib1svARB
         2227, // glVertexAttrib2dARB
         2230, // glVertexAttrib2dvARB
         2233, // glVertexAttrib2fARB
         2236, // glVertexAttrib2fvARB
         2241, // glVertexAttrib2sARB
         2244, // glVertexAttrib2svARB
         2247, // glVertexAttrib3dARB
         2250, // glVertexAttrib3dvARB
         2253, // glVertexAttrib3fARB
         2256, // glVertexAttrib3fvARB
         2261, // glVertexAttrib3sARB
         2264, // glVertexAttrib3svARB
         2267, // glVertexAttrib4NbvARB
         2269, // glVertexAttrib4NivARB
         2271, // glVertexAttrib4NsvARB
         2273, // glVertexAttrib4NubARB
         2275, // glVertexAttrib4NubvARB
         2277, // glVertexAttrib4NuivARB
         2279, // glVertexAttrib4NusvARB
         2281, // glVertexAttrib4bvARB
         2283, // glVertexAttrib4dARB
         2286, // glVertexAttrib4dvARB
         2289, // glVertexAttrib4fARB
         2292, // glVertexAttrib4fvARB
         2297, // glVertexAttrib4ivARB
         2299, // glVertexAttrib4sARB
         2302, // glVertexAttrib4svARB
         2306, // glVertexAttrib4ubvARB
         2309, // glVertexAttrib4uivARB
         2311, // glVertexAttrib4usvARB
         2410  // glVertexAttribPointerARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_vertex_shader) return;
    static const uint16_t s_pfnIdx[] = {
           40, // glBindAttribLocationARB
          407, // glDisableVertexAttribArrayARB
          470, // glEnableVertexAttribArrayARB
          609, // glGetActiveAttribARB
          625, // glGetAttribLocationARB
          971, // glGetVertexAttribPointervARB
          974, // glGetVertexAttribdvARB
          977, // glGetVertexAttribfvARB
          980, // glGetVertexAttribivARB
         2207, // glVertexAttrib1dARB
         2210, // glVertexAttrib1dvARB
         2213, // glVertexAttrib1fARB
         2216, // glVertexAttrib1fvARB
         2221, // glVertexAttrib1sARB
         2224, // glVertexAttrib1svARB
         2227, // glVertexAttrib2dARB
         2230, // glVertexAttrib2dvARB
         2233, // glVertexAttrib2fARB
         2236, // glVertexAttrib2fvARB
         2241, // glVertexAttrib2sARB
         2244, // glVertexAttrib2svARB
         2247, // glVertexAttrib3dARB
         2250, // glVertexAttrib3dvARB
         2253, // glVertexAttrib3fARB
         2256, // glVertexAttrib3fvARB
         2261, // glVertexAttrib3sARB
         2264, // glVertexAttrib3svARB
         2267, // glVertexAttrib4NbvARB
         2269, // glVertexAttrib4NivARB
         2271, // glVertexAttrib4NsvARB
         2273, // glVertexAttrib4NubARB
         2275, // glVertexAttrib4NubvARB
         2277, // glVertexAttrib4NuivARB
         2279, // glVertexAttrib4NusvARB
         2281, // glVertexAttrib4bvARB
         2283, // glVertexAttrib4dARB
         2286, // glVertexAttrib4dvARB
         2289, // glVertexAttrib4fARB
         2292, // glVertexAttrib4fvARB
         2297, // glVertexAttrib4ivARB
         2299, // glVertexAttrib4sARB
         2302, // glVertexAttrib4svARB
         2306, // glVertexAttrib4ubvARB
         2309, // glVertexAttrib4uivARB
         2311, // glVertexAttrib4usvARB
         2410  // glVertexAttribPointerARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_type_2_10_10_10_rev(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_vertex_type_2_10_10_10_rev) return;
    static const uint16_t s_pfnIdx[] = {
         2400, // glVertexAttribP1ui
         2401, // glVertexAttribP1uiv
         2402, // glVertexAttribP2ui
         2403, // glVertexAttribP2uiv
         2404, // glVertexAttribP3ui
         2405, // glVertexAttribP3uiv
         2406, // glVertexAttribP4ui
         2407  // glVertexAttribP4uiv
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_viewport_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_viewport_array) return;
    static const uint16_t s_pfnIdx[] = {
          386, // glDepthRangeArraydvNV
          387, // glDepthRangeArrayv
          388, // glDepthRangeIndexed
          389, // glDepthRangeIndexeddNV
          667, // glGetDoublei_v
          677, // glGetFloati_v
         1733, // glScissorArrayv
         1736, // glScissorIndexed
         1737, // glScissorIndexedv
         2479, // glViewportArrayv
         2480, // glViewportIndexedf
         2481  // glViewportIndexedfv
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_window_pos(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARB_window_pos) return;
    static const uint16_t s_pfnIdx[] = {
         2498, // glWindowPos2dARB
         2500, // glWindowPos2dvARB
         2502, // glWindowPos2fARB
         2504, // glWindowPos2fvARB
         2506, // glWindowPos2iARB
         2508, // glWindowPos2ivARB
         2510, // glWindowPos2sARB
         2512, // glWindowPos2svARB
         2514, // glWindowPos3dARB
         2516, // glWindowPos3dvARB
         2518, // glWindowPos3fARB
         2520, // glWindowPos3fvARB
         2522, // glWindowPos3iARB
         2524, // glWindowPos3ivARB
         2526, // glWindowPos3sARB
         2528  // glWindowPos3svARB
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_draw_buffers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ATI_draw_buffers) return;
    static const uint16_t s_pfnIdx[] = {
          422  // glDrawBuffersATI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_element_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ATI_element_array) return;
    static const uint16_t s_pfnIdx[] = {
          428, // glDrawElementArrayATI
          442, // glDrawRangeElementArrayATI
          459  // glElementPointerATI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_envmap_bumpmap(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ATI_envmap_bumpmap) return;
    static const uint16_t s_pfnIdx[] = {
          882, // glGetTexBumpParameterfvATI
          883, // glGetTexBumpParameterivATI
         1839, // glTexBumpParameterfvATI
         1840  // glTexBumpParameterivATI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_fragment_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ATI_fragment_shader) return;
    static const uint16_t s_pfnIdx[] = {
            8, // glAlphaFragmentOp1ATI
            9, // glAlphaFragmentOp2ATI
           10, // glAlphaFragmentOp3ATI
           27, // glBeginFragmentShaderATI
           56, // glBindFragmentShaderATI
          204, // glColorFragmentOp1ATI
          205, // glColorFragmentOp2ATI
          206, // glColorFragmentOp3ATI
          349, // glDeleteFragmentShaderATI
          475, // glEndFragmentShaderATI
          577, // glGenFragmentShadersATI
         1395, // glPassTexCoordATI
         1718, // glSampleMapATI
         1765  // glSetFragmentShaderConstantATI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_map_object_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ATI_map_object_buffer) return;
    static const uint16_t s_pfnIdx[] = {
         1146, // glMapObjectBufferATI
         2126  // glUnmapObjectBufferATI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_pn_triangles(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ATI_pn_triangles) return;
    static const uint16_t s_pfnIdx[] = {
         1393, // glPNTrianglesfATI
         1394  // glPNTrianglesiATI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_separate_stencil(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ATI_separate_stencil) return;
    static const uint16_t s_pfnIdx[] = {
         1798, // glStencilFuncSeparateATI
         1803  // glStencilOpSeparateATI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_vertex_array_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ATI_vertex_array_object) return;
    static const uint16_t s_pfnIdx[] = {
           18, // glArrayObjectATI
          568, // glFreeObjectBufferATI
          620, // glGetArrayObjectfvATI
          621, // glGetArrayObjectivATI
          776, // glGetObjectBufferfvATI
          777, // glGetObjectBufferivATI
          945, // glGetVariantArrayObjectfvATI
          946, // glGetVariantArrayObjectivATI
         1068, // glIsObjectBufferATI
         1366, // glNewObjectBufferATI
         2128, // glUpdateObjectBufferATI
         2148  // glVariantArrayObjectATI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_vertex_attrib_array_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ATI_vertex_attrib_array_object) return;
    static const uint16_t s_pfnIdx[] = {
          959, // glGetVertexAttribArrayObjectfvATI
          960, // glGetVertexAttribArrayObjectivATI
         2312  // glVertexAttribArrayObjectATI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_vertex_streams(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ATI_vertex_streams) return;
    static const uint16_t s_pfnIdx[] = {
          180, // glClientActiveVertexStreamATI
         1377, // glNormalStream3bATI
         1378, // glNormalStream3bvATI
         1379, // glNormalStream3dATI
         1380, // glNormalStream3dvATI
         1381, // glNormalStream3fATI
         1382, // glNormalStream3fvATI
         1383, // glNormalStream3iATI
         1384, // glNormalStream3ivATI
         1385, // glNormalStream3sATI
         1386, // glNormalStream3svATI
         2431, // glVertexBlendEnvfATI
         2432, // glVertexBlendEnviATI
         2437, // glVertexStream1dATI
         2438, // glVertexStream1dvATI
         2439, // glVertexStream1fATI
         2440, // glVertexStream1fvATI
         2441, // glVertexStream1iATI
         2442, // glVertexStream1ivATI
         2443, // glVertexStream1sATI
         2444, // glVertexStream1svATI
         2445, // glVertexStream2dATI
         2446, // glVertexStream2dvATI
         2447, // glVertexStream2fATI
         2448, // glVertexStream2fvATI
         2449, // glVertexStream2iATI
         2450, // glVertexStream2ivATI
         2451, // glVertexStream2sATI
         2452, // glVertexStream2svATI
         2453, // glVertexStream3dATI
         2454, // glVertexStream3dvATI
         2455, // glVertexStream3fATI
         2456, // glVertexStream3fvATI
         2457, // glVertexStream3iATI
         2458, // glVertexStream3ivATI
         2459, // glVertexStream3sATI
         2460, // glVertexStream3svATI
         2461, // glVertexStream4dATI
         2462, // glVertexStream4dvATI
         2463, // glVertexStream4fATI
         2464, // glVertexStream4fvATI
         2465, // glVertexStream4iATI
         2466, // glVertexStream4ivATI
         2467, // glVertexStream4sATI
         2468  // glVertexStream4svATI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_EGL_image_storage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_EGL_image_storage) return;
    static const uint16_t s_pfnIdx[] = {
          453, // glEGLImageTargetTexStorageEXT
          454  // glEGLImageTargetTextureStorageEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_bindable_uniform(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_bindable_uniform) return;
    static const uint16_t s_pfnIdx[] = {
          926, // glGetUniformBufferSizeEXT
          930, // glGetUniformOffsetEXT
         2092  // glUniformBufferEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_blend_color(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_blend_color) return;
    static const uint16_t s_pfnIdx[] = {
          104  // glBlendColorEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_blend_equation_separate(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_blend_equation_separate) return;
    static const uint16_t s_pfnIdx[] = {
          110  // glBlendEquationSeparateEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_blend_func_separate(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_blend_func_separate) return;
    static const uint16_t s_pfnIdx[] = {
          119  // glBlendFuncSeparateEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_blend_minmax(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_blend_minmax) return;
    static const uint16_t s_pfnIdx[] = {
          107  // glBlendEquationEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_color_subtable(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_color_subtable) return;
    static const uint16_t s_pfnIdx[] = {
          213, // glColorSubTableEXT
          268  // glCopyColorSubTableEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_compiled_vertex_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_compiled_vertex_array) return;
    static const uint16_t s_pfnIdx[] = {
         1120, // glLockArraysEXT
         2121  // glUnlockArraysEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_convolution(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_convolution) return;
    static const uint16_t s_pfnIdx[] = {
          259, // glConvolutionFilter1DEXT
          260, // glConvolutionFilter2DEXT
          261, // glConvolutionParameterfEXT
          262, // glConvolutionParameterfvEXT
          263, // glConvolutionParameteriEXT
          264, // glConvolutionParameterivEXT
          270, // glCopyConvolutionFilter1DEXT
          271, // glCopyConvolutionFilter2DEXT
          657, // glGetConvolutionFilterEXT
          658, // glGetConvolutionParameterfvEXT
          659, // glGetConvolutionParameterivEXT
          867, // glGetSeparableFilterEXT
         1762  // glSeparableFilter2DEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_coordinate_frame(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_coordinate_frame) return;
    static const uint16_t s_pfnIdx[] = {
           89, // glBinormal3bEXT
           90, // glBinormal3bvEXT
           91, // glBinormal3dEXT
           92, // glBinormal3dvEXT
           93, // glBinormal3fEXT
           94, // glBinormal3fvEXT
           95, // glBinormal3iEXT
           96, // glBinormal3ivEXT
           97, // glBinormal3sEXT
           98, // glBinormal3svEXT
           99, // glBinormalPointerEXT
         1817, // glTangent3bEXT
         1818, // glTangent3bvEXT
         1819, // glTangent3dEXT
         1820, // glTangent3dvEXT
         1821, // glTangent3fEXT
         1822, // glTangent3fvEXT
         1823, // glTangent3iEXT
         1824, // glTangent3ivEXT
         1825, // glTangent3sEXT
         1826, // glTangent3svEXT
         1827  // glTangentPointerEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_copy_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_copy_texture) return;
    static const uint16_t s_pfnIdx[] = {
          282, // glCopyTexImage1DEXT
          284, // glCopyTexImage2DEXT
          286, // glCopyTexSubImage1DEXT
          288, // glCopyTexSubImage2DEXT
          290  // glCopyTexSubImage3DEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_cull_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_cull_vertex) return;
    static const uint16_t s_pfnIdx[] = {
          328, // glCullParameterdvEXT
          329  // glCullParameterfvEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_debug_label(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_debug_label) return;
    static const uint16_t s_pfnIdx[] = {
          779, // glGetObjectLabelEXT
         1099  // glLabelObjectEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_debug_marker(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_debug_marker) return;
    static const uint16_t s_pfnIdx[] = {
         1038, // glInsertEventMarkerEXT
         1460, // glPopGroupMarkerEXT
         1654  // glPushGroupMarkerEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_depth_bounds_test(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_depth_bounds_test) return;
    static const uint16_t s_pfnIdx[] = {
          381  // glDepthBoundsEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_direct_state_access(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_direct_state_access) return;
    static const uint16_t s_pfnIdx[] = {
           64, // glBindMultiTextureEXT
          148, // glCheckNamedFramebufferStatusEXT
          169, // glClearNamedBufferDataEXT
          171, // glClearNamedBufferSubDataEXT
          181, // glClientAttribDefaultEXT
          230, // glCompressedMultiTexImage1DEXT
          231, // glCompressedMultiTexImage2DEXT
          232, // glCompressedMultiTexImage3DEXT
          233, // glCompressedMultiTexSubImage1DEXT
          234, // glCompressedMultiTexSubImage2DEXT
          235, // glCompressedMultiTexSubImage3DEXT
          248, // glCompressedTextureImage1DEXT
          249, // glCompressedTextureImage2DEXT
          250, // glCompressedTextureImage3DEXT
          252, // glCompressedTextureSubImage1DEXT
          254, // glCompressedTextureSubImage2DEXT
          256, // glCompressedTextureSubImage3DEXT
          274, // glCopyMultiTexImage1DEXT
          275, // glCopyMultiTexImage2DEXT
          276, // glCopyMultiTexSubImage1DEXT
          277, // glCopyMultiTexSubImage2DEXT
          278, // glCopyMultiTexSubImage3DEXT
          291, // glCopyTextureImage1DEXT
          292, // glCopyTextureImage2DEXT
          294, // glCopyTextureSubImage1DEXT
          296, // glCopyTextureSubImage2DEXT
          298, // glCopyTextureSubImage3DEXT
          398, // glDisableClientStateIndexedEXT
          399, // glDisableClientStateiEXT
          400, // glDisableIndexedEXT
          403, // glDisableVertexArrayAttribEXT
          404, // glDisableVertexArrayEXT
          461, // glEnableClientStateIndexedEXT
          462, // glEnableClientStateiEXT
          463, // glEnableIndexedEXT
          466, // glEnableVertexArrayAttribEXT
          467, // glEnableVertexArrayEXT
          508, // glFlushMappedNamedBufferRangeEXT
          542, // glFramebufferDrawBufferEXT
          543, // glFramebufferDrawBuffersEXT
          547, // glFramebufferReadBufferEXT
          604, // glGenerateMultiTexMipmapEXT
          606, // glGenerateTextureMipmapEXT
          626, // glGetBooleanIndexedvEXT
          651, // glGetCompressedMultiTexImageEXT
          655, // glGetCompressedTextureImageEXT
          666, // glGetDoubleIndexedvEXT
          668, // glGetDoublei_vEXT
          676, // glGetFloatIndexedvEXT
          678, // glGetFloati_vEXT
          692, // glGetFramebufferParameterivEXT
          709, // glGetIntegerIndexedvEXT
          738, // glGetMultiTexEnvfvEXT
          739, // glGetMultiTexEnvivEXT
          740, // glGetMultiTexGendvEXT
          741, // glGetMultiTexGenfvEXT
          742, // glGetMultiTexGenivEXT
          743, // glGetMultiTexImageEXT
          744, // glGetMultiTexLevelParameterfvEXT
          745, // glGetMultiTexLevelParameterivEXT
          746, // glGetMultiTexParameterIivEXT
          747, // glGetMultiTexParameterIuivEXT
          748, // glGetMultiTexParameterfvEXT
          749, // glGetMultiTexParameterivEXT
          754, // glGetNamedBufferParameterivEXT
          757, // glGetNamedBufferPointervEXT
          759, // glGetNamedBufferSubDataEXT
          761, // glGetNamedFramebufferAttachmentParameterivEXT
          764, // glGetNamedFramebufferParameterivEXT
          765, // glGetNamedProgramLocalParameterIivEXT
          766, // glGetNamedProgramLocalParameterIuivEXT
          767, // glGetNamedProgramLocalParameterdvEXT
          768, // glGetNamedProgramLocalParameterfvEXT
          769, // glGetNamedProgramStringEXT
          770, // glGetNamedProgramivEXT
          772, // glGetNamedRenderbufferParameterivEXT
          810, // glGetPointerIndexedvEXT
          811, // glGetPointeri_vEXT
          902, // glGetTextureImageEXT
          904, // glGetTextureLevelParameterfvEXT
          906, // glGetTextureLevelParameterivEXT
          908, // glGetTextureParameterIivEXT
          910, // glGetTextureParameterIuivEXT
          912, // glGetTextureParameterfvEXT
          914, // glGetTextureParameterivEXT
          954, // glGetVertexArrayIntegeri_vEXT
          955, // glGetVertexArrayIntegervEXT
          956, // glGetVertexArrayPointeri_vEXT
          957, // glGetVertexArrayPointervEXT
         1056, // glIsEnabledIndexedEXT
         1143, // glMapNamedBufferEXT
         1145, // glMapNamedBufferRangeEXT
         1156, // glMatrixFrustumEXT
         1163, // glMatrixLoadIdentityEXT
         1165, // glMatrixLoadTransposedEXT
         1166, // glMatrixLoadTransposefEXT
         1167, // glMatrixLoaddEXT
         1168, // glMatrixLoadfEXT
         1172, // glMatrixMultTransposedEXT
         1173, // glMatrixMultTransposefEXT
         1174, // glMatrixMultdEXT
         1175, // glMatrixMultfEXT
         1176, // glMatrixOrthoEXT
         1177, // glMatrixPopEXT
         1178, // glMatrixPushEXT
         1179, // glMatrixRotatedEXT
         1180, // glMatrixRotatefEXT
         1181, // glMatrixScaledEXT
         1182, // glMatrixScalefEXT
         1183, // glMatrixTranslatedEXT
         1184, // glMatrixTranslatefEXT
         1221, // glMultiTexBufferEXT
         1278, // glMultiTexCoordPointerEXT
         1279, // glMultiTexEnvfEXT
         1280, // glMultiTexEnvfvEXT
         1281, // glMultiTexEnviEXT
         1282, // glMultiTexEnvivEXT
         1283, // glMultiTexGendEXT
         1284, // glMultiTexGendvEXT
         1285, // glMultiTexGenfEXT
         1286, // glMultiTexGenfvEXT
         1287, // glMultiTexGeniEXT
         1288, // glMultiTexGenivEXT
         1289, // glMultiTexImage1DEXT
         1290, // glMultiTexImage2DEXT
         1291, // glMultiTexImage3DEXT
         1292, // glMultiTexParameterIivEXT
         1293, // glMultiTexParameterIuivEXT
         1294, // glMultiTexParameterfEXT
         1295, // glMultiTexParameterfvEXT
         1296, // glMultiTexParameteriEXT
         1297, // glMultiTexParameterivEXT
         1298, // glMultiTexRenderbufferEXT
         1299, // glMultiTexSubImage1DEXT
         1300, // glMultiTexSubImage2DEXT
         1301, // glMultiTexSubImage3DEXT
         1318, // glNamedBufferDataEXT
         1323, // glNamedBufferStorageEXT
         1327, // glNamedBufferSubDataEXT
         1328, // glNamedCopyBufferSubDataEXT
         1332, // glNamedFramebufferParameteriEXT
         1335, // glNamedFramebufferRenderbufferEXT
         1340, // glNamedFramebufferTexture1DEXT
         1341, // glNamedFramebufferTexture2DEXT
         1342, // glNamedFramebufferTexture3DEXT
         1343, // glNamedFramebufferTextureEXT
         1344, // glNamedFramebufferTextureFaceEXT
         1346, // glNamedFramebufferTextureLayerEXT
         1347, // glNamedProgramLocalParameter4dEXT
         1348, // glNamedProgramLocalParameter4dvEXT
         1349, // glNamedProgramLocalParameter4fEXT
         1350, // glNamedProgramLocalParameter4fvEXT
         1351, // glNamedProgramLocalParameterI4iEXT
         1352, // glNamedProgramLocalParameterI4ivEXT
         1353, // glNamedProgramLocalParameterI4uiEXT
         1354, // glNamedProgramLocalParameterI4uivEXT
         1355, // glNamedProgramLocalParameters4fvEXT
         1356, // glNamedProgramLocalParametersI4ivEXT
         1357, // glNamedProgramLocalParametersI4uivEXT
         1358, // glNamedProgramStringEXT
         1360, // glNamedRenderbufferStorageEXT
         1363, // glNamedRenderbufferStorageMultisampleCoverageEXT
         1364, // glNamedRenderbufferStorageMultisampleEXT
         1512, // glProgramUniform1dEXT
         1514, // glProgramUniform1dvEXT
         1516, // glProgramUniform1fEXT
         1518, // glProgramUniform1fvEXT
         1524, // glProgramUniform1iEXT
         1526, // glProgramUniform1ivEXT
         1532, // glProgramUniform1uiEXT
         1534, // glProgramUniform1uivEXT
         1536, // glProgramUniform2dEXT
         1538, // glProgramUniform2dvEXT
         1540, // glProgramUniform2fEXT
         1542, // glProgramUniform2fvEXT
         1548, // glProgramUniform2iEXT
         1550, // glProgramUniform2ivEXT
         1556, // glProgramUniform2uiEXT
         1558, // glProgramUniform2uivEXT
         1560, // glProgramUniform3dEXT
         1562, // glProgramUniform3dvEXT
         1564, // glProgramUniform3fEXT
         1566, // glProgramUniform3fvEXT
         1572, // glProgramUniform3iEXT
         1574, // glProgramUniform3ivEXT
         1580, // glProgramUniform3uiEXT
         1582, // glProgramUniform3uivEXT
         1584, // glProgramUniform4dEXT
         1586, // glProgramUniform4dvEXT
         1588, // glProgramUniform4fEXT
         1590, // glProgramUniform4fvEXT
         1596, // glProgramUniform4iEXT
         1598, // glProgramUniform4ivEXT
         1604, // glProgramUniform4uiEXT
         1606, // glProgramUniform4uivEXT
         1612, // glProgramUniformMatrix2dvEXT
         1614, // glProgramUniformMatrix2fvEXT
         1616, // glProgramUniformMatrix2x3dvEXT
         1618, // glProgramUniformMatrix2x3fvEXT
         1620, // glProgramUniformMatrix2x4dvEXT
         1622, // glProgramUniformMatrix2x4fvEXT
         1624, // glProgramUniformMatrix3dvEXT
         1626, // glProgramUniformMatrix3fvEXT
         1628, // glProgramUniformMatrix3x2dvEXT
         1630, // glProgramUniformMatrix3x2fvEXT
         1632, // glProgramUniformMatrix3x4dvEXT
         1634, // glProgramUniformMatrix3x4fvEXT
         1636, // glProgramUniformMatrix4dvEXT
         1638, // glProgramUniformMatrix4fvEXT
         1640, // glProgramUniformMatrix4x2dvEXT
         1642, // glProgramUniformMatrix4x2fvEXT
         1644, // glProgramUniformMatrix4x3dvEXT
         1646, // glProgramUniformMatrix4x3fvEXT
         1652, // glPushClientAttribDefaultEXT
         1940, // glTextureBufferEXT
         1942, // glTextureBufferRangeEXT
         1944, // glTextureImage1DEXT
         1945, // glTextureImage2DEXT
         1948, // glTextureImage3DEXT
         1954, // glTexturePageCommitmentEXT
         1957, // glTextureParameterIivEXT
         1959, // glTextureParameterIuivEXT
         1961, // glTextureParameterfEXT
         1963, // glTextureParameterfvEXT
         1965, // glTextureParameteriEXT
         1967, // glTextureParameterivEXT
         1969, // glTextureRenderbufferEXT
         1971, // glTextureStorage1DEXT
         1973, // glTextureStorage2DEXT
         1975, // glTextureStorage2DMultisampleEXT
         1977, // glTextureStorage3DEXT
         1979, // glTextureStorage3DMultisampleEXT
         1987, // glTextureSubImage1DEXT
         1989, // glTextureSubImage2DEXT
         1991, // glTextureSubImage3DEXT
         2125, // glUnmapNamedBufferEXT
         2180, // glVertexArrayBindVertexBufferEXT
         2182, // glVertexArrayColorOffsetEXT
         2183, // glVertexArrayEdgeFlagOffsetEXT
         2185, // glVertexArrayFogCoordOffsetEXT
         2186, // glVertexArrayIndexOffsetEXT
         2187, // glVertexArrayMultiTexCoordOffsetEXT
         2188, // glVertexArrayNormalOffsetEXT
         2192, // glVertexArraySecondaryColorOffsetEXT
         2193, // glVertexArrayTexCoordOffsetEXT
         2194, // glVertexArrayVertexAttribBindingEXT
         2195, // glVertexArrayVertexAttribDivisorEXT
         2196, // glVertexArrayVertexAttribFormatEXT
         2197, // glVertexArrayVertexAttribIFormatEXT
         2198, // glVertexArrayVertexAttribIOffsetEXT
         2199, // glVertexArrayVertexAttribLFormatEXT
         2200, // glVertexArrayVertexAttribLOffsetEXT
         2201, // glVertexArrayVertexAttribOffsetEXT
         2202, // glVertexArrayVertexBindingDivisorEXT
         2205  // glVertexArrayVertexOffsetEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_draw_buffers2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_draw_buffers2) return;
    static const uint16_t s_pfnIdx[] = {
          208, // glColorMaskIndexedEXT
          400, // glDisableIndexedEXT
          463, // glEnableIndexedEXT
          626, // glGetBooleanIndexedvEXT
          709, // glGetIntegerIndexedvEXT
         1056  // glIsEnabledIndexedEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_draw_instanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_draw_instanced) return;
    static const uint16_t s_pfnIdx[] = {
          418, // glDrawArraysInstancedEXT
          437  // glDrawElementsInstancedEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_draw_range_elements(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_draw_range_elements) return;
    static const uint16_t s_pfnIdx[] = {
          445  // glDrawRangeElementsEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_external_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_external_buffer) return;
    static const uint16_t s_pfnIdx[] = {
          140, // glBufferStorageExternalEXT
         1324  // glNamedBufferStorageExternalEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_fog_coord(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_fog_coord) return;
    static const uint16_t s_pfnIdx[] = {
          515, // glFogCoordPointerEXT
          517, // glFogCoorddEXT
          518, // glFogCoorddvEXT
          519, // glFogCoordfEXT
          520  // glFogCoordfvEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_framebuffer_blit(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_framebuffer_blit) return;
    static const uint16_t s_pfnIdx[] = {
          128  // glBlitFramebufferEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_framebuffer_blit_layers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_framebuffer_blit_layers) return;
    static const uint16_t s_pfnIdx[] = {
          129, // glBlitFramebufferLayerEXT
          130  // glBlitFramebufferLayersEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_framebuffer_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_framebuffer_multisample) return;
    static const uint16_t s_pfnIdx[] = {
         1683  // glRenderbufferStorageMultisampleEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_framebuffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_framebuffer_object) return;
    static const uint16_t s_pfnIdx[] = {
           58, // glBindFramebufferEXT
           70, // glBindRenderbufferEXT
          146, // glCheckFramebufferStatusEXT
          351, // glDeleteFramebuffersEXT
          368, // glDeleteRenderbuffersEXT
          549, // glFramebufferRenderbufferEXT
          555, // glFramebufferTexture1DEXT
          557, // glFramebufferTexture2DEXT
          559, // glFramebufferTexture3DEXT
          579, // glGenFramebuffersEXT
          591, // glGenRenderbuffersEXT
          603, // glGenerateMipmapEXT
          689, // glGetFramebufferAttachmentParameterivEXT
          860, // glGetRenderbufferParameterivEXT
         1061, // glIsFramebufferEXT
         1080, // glIsRenderbufferEXT
         1679  // glRenderbufferStorageEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_geometry_shader4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_geometry_shader4) return;
    static const uint16_t s_pfnIdx[] = {
         1505  // glProgramParameteriEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_gpu_program_parameters(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_gpu_program_parameters) return;
    static const uint16_t s_pfnIdx[] = {
         1481, // glProgramEnvParameters4fvEXT
         1492  // glProgramLocalParameters4fvEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_gpu_shader4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_gpu_shader4) return;
    static const uint16_t s_pfnIdx[] = {
           54, // glBindFragDataLocationEXT
          683, // glGetFragDataLocationEXT
          942, // glGetUniformuivEXT
          962, // glGetVertexAttribIivEXT
          964, // glGetVertexAttribIuivEXT
         2022, // glUniform1uiEXT
         2024, // glUniform1uivEXT
         2044, // glUniform2uiEXT
         2046, // glUniform2uivEXT
         2066, // glUniform3uiEXT
         2068, // glUniform3uivEXT
         2088, // glUniform4uiEXT
         2090, // glUniform4uivEXT
         2319, // glVertexAttribI1iEXT
         2321, // glVertexAttribI1ivEXT
         2323, // glVertexAttribI1uiEXT
         2325, // glVertexAttribI1uivEXT
         2327, // glVertexAttribI2iEXT
         2329, // glVertexAttribI2ivEXT
         2331, // glVertexAttribI2uiEXT
         2333, // glVertexAttribI2uivEXT
         2335, // glVertexAttribI3iEXT
         2337, // glVertexAttribI3ivEXT
         2339, // glVertexAttribI3uiEXT
         2341, // glVertexAttribI3uivEXT
         2343, // glVertexAttribI4bvEXT
         2345, // glVertexAttribI4iEXT
         2347, // glVertexAttribI4ivEXT
         2349, // glVertexAttribI4svEXT
         2351, // glVertexAttribI4ubvEXT
         2353, // glVertexAttribI4uiEXT
         2355, // glVertexAttribI4uivEXT
         2357, // glVertexAttribI4usvEXT
         2361  // glVertexAttribIPointerEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_histogram(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_histogram) return;
    static const uint16_t s_pfnIdx[] = {
          697, // glGetHistogramEXT
          698, // glGetHistogramParameterfvEXT
          699, // glGetHistogramParameterivEXT
          735, // glGetMinmaxEXT
          736, // glGetMinmaxParameterfvEXT
          737, // glGetMinmaxParameterivEXT
         1015, // glHistogramEXT
         1193, // glMinmaxEXT
         1708, // glResetHistogramEXT
         1710  // glResetMinmaxEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_index_func(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_index_func) return;
    static const uint16_t s_pfnIdx[] = {
         1031  // glIndexFuncEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_index_material(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_index_material) return;
    static const uint16_t s_pfnIdx[] = {
         1032  // glIndexMaterialEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_light_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_light_texture) return;
    static const uint16_t s_pfnIdx[] = {
           14, // glApplyTextureEXT
         1951, // glTextureLightEXT
         1952  // glTextureMaterialEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_memory_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_memory_object) return;
    static const uint16_t s_pfnIdx[] = {
          141, // glBufferStorageMemEXT
          308, // glCreateMemoryObjectsEXT
          352, // glDeleteMemoryObjectsEXT
          734, // glGetMemoryObjectParameterivEXT
          943, // glGetUnsignedBytei_vEXT
          944, // glGetUnsignedBytevEXT
         1064, // glIsMemoryObjectEXT
         1190, // glMemoryObjectParameterivEXT
         1325, // glNamedBufferStorageMemEXT
         1919, // glTexStorageMem1DEXT
         1920, // glTexStorageMem2DEXT
         1921, // glTexStorageMem2DMultisampleEXT
         1922, // glTexStorageMem3DEXT
         1923, // glTexStorageMem3DMultisampleEXT
         1980, // glTextureStorageMem1DEXT
         1981, // glTextureStorageMem2DEXT
         1982, // glTextureStorageMem2DMultisampleEXT
         1983, // glTextureStorageMem3DEXT
         1984  // glTextureStorageMem3DMultisampleEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_memory_object_fd(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_memory_object_fd) return;
    static const uint16_t s_pfnIdx[] = {
         1021  // glImportMemoryFdEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_memory_object_win32(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_memory_object_win32) return;
    static const uint16_t s_pfnIdx[] = {
         1022, // glImportMemoryWin32HandleEXT
         1023  // glImportMemoryWin32NameEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_multi_draw_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_multi_draw_arrays) return;
    static const uint16_t s_pfnIdx[] = {
         1199, // glMultiDrawArraysEXT
         1209  // glMultiDrawElementsEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_multisample) return;
    static const uint16_t s_pfnIdx[] = {
         1719, // glSampleMaskEXT
         1723  // glSamplePatternEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_paletted_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_paletted_texture) return;
    static const uint16_t s_pfnIdx[] = {
          214, // glColorTableEXT
          639, // glGetColorTableEXT
          640, // glGetColorTableParameterfvEXT
          642  // glGetColorTableParameterivEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_pixel_transform(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_pixel_transform) return;
    static const uint16_t s_pfnIdx[] = {
          808, // glGetPixelTransformParameterfvEXT
          809, // glGetPixelTransformParameterivEXT
         1430, // glPixelTransformParameterfEXT
         1431, // glPixelTransformParameterfvEXT
         1432, // glPixelTransformParameteriEXT
         1433  // glPixelTransformParameterivEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_point_parameters(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_point_parameters) return;
    static const uint16_t s_pfnIdx[] = {
         1438, // glPointParameterfEXT
         1442  // glPointParameterfvEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_polygon_offset(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_polygon_offset) return;
    static const uint16_t s_pfnIdx[] = {
         1457  // glPolygonOffsetEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_polygon_offset_clamp(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_polygon_offset_clamp) return;
    static const uint16_t s_pfnIdx[] = {
         1456  // glPolygonOffsetClampEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_provoking_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_provoking_vertex) return;
    static const uint16_t s_pfnIdx[] = {
         1651  // glProvokingVertexEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_raster_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_raster_multisample) return;
    static const uint16_t s_pfnIdx[] = {
         1666  // glRasterSamplesEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_secondary_color(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_secondary_color) return;
    static const uint16_t s_pfnIdx[] = {
         1738, // glSecondaryColor3bEXT
         1739, // glSecondaryColor3bvEXT
         1740, // glSecondaryColor3dEXT
         1741, // glSecondaryColor3dvEXT
         1742, // glSecondaryColor3fEXT
         1743, // glSecondaryColor3fvEXT
         1746, // glSecondaryColor3iEXT
         1747, // glSecondaryColor3ivEXT
         1748, // glSecondaryColor3sEXT
         1749, // glSecondaryColor3svEXT
         1750, // glSecondaryColor3ubEXT
         1751, // glSecondaryColor3ubvEXT
         1752, // glSecondaryColor3uiEXT
         1753, // glSecondaryColor3uivEXT
         1754, // glSecondaryColor3usEXT
         1755, // glSecondaryColor3usvEXT
         1757  // glSecondaryColorPointerEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_semaphore(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_semaphore) return;
    static const uint16_t s_pfnIdx[] = {
          370, // glDeleteSemaphoresEXT
          593, // glGenSemaphoresEXT
          866, // glGetSemaphoreParameterui64vEXT
          943, // glGetUnsignedBytei_vEXT
          944, // glGetUnsignedBytevEXT
         1082, // glIsSemaphoreEXT
         1761, // glSemaphoreParameterui64vEXT
         1781, // glSignalSemaphoreEXT
         2484  // glWaitSemaphoreEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_semaphore_fd(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_semaphore_fd) return;
    static const uint16_t s_pfnIdx[] = {
         1025  // glImportSemaphoreFdEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_semaphore_win32(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_semaphore_win32) return;
    static const uint16_t s_pfnIdx[] = {
         1026, // glImportSemaphoreWin32HandleEXT
         1027  // glImportSemaphoreWin32NameEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_separate_shader_objects(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_separate_shader_objects) return;
    static const uint16_t s_pfnIdx[] = {
            2, // glActiveProgramEXT
         2541, // glActiveShaderProgramEXT
         2546, // glBindProgramPipelineEXT
          320, // glCreateShaderProgramEXT
         2587, // glCreateShaderProgramvEXT
         2591, // glDeleteProgramPipelinesEXT
         2668, // glGenProgramPipelinesEXT
         2712, // glGetProgramPipelineInfoLogEXT
         2713, // glGetProgramPipelineivEXT
         2769, // glIsProgramPipelineEXT
         1505, // glProgramParameteriEXT
         1516, // glProgramUniform1fEXT
         1518, // glProgramUniform1fvEXT
         1524, // glProgramUniform1iEXT
         1526, // glProgramUniform1ivEXT
         1532, // glProgramUniform1uiEXT
         1534, // glProgramUniform1uivEXT
         1540, // glProgramUniform2fEXT
         1542, // glProgramUniform2fvEXT
         1548, // glProgramUniform2iEXT
         1550, // glProgramUniform2ivEXT
         1556, // glProgramUniform2uiEXT
         1558, // glProgramUniform2uivEXT
         1564, // glProgramUniform3fEXT
         1566, // glProgramUniform3fvEXT
         1572, // glProgramUniform3iEXT
         1574, // glProgramUniform3ivEXT
         1580, // glProgramUniform3uiEXT
         1582, // glProgramUniform3uivEXT
         1588, // glProgramUniform4fEXT
         1590, // glProgramUniform4fvEXT
         1596, // glProgramUniform4iEXT
         1598, // glProgramUniform4ivEXT
         1604, // glProgramUniform4uiEXT
         1606, // glProgramUniform4uivEXT
         1614, // glProgramUniformMatrix2fvEXT
         1618, // glProgramUniformMatrix2x3fvEXT
         1622, // glProgramUniformMatrix2x4fvEXT
         1626, // glProgramUniformMatrix3fvEXT
         1630, // glProgramUniformMatrix3x2fvEXT
         1634, // glProgramUniformMatrix3x4fvEXT
         1638, // glProgramUniformMatrix4fvEXT
         1642, // glProgramUniformMatrix4x2fvEXT
         1646, // glProgramUniformMatrix4x3fvEXT
         2871, // glUseProgramStagesEXT
         2133, // glUseShaderProgramEXT
         2872  // glValidateProgramPipelineEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_shader_framebuffer_fetch_non_coherent(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_shader_framebuffer_fetch_non_coherent) return;
    static const uint16_t s_pfnIdx[] = {
          544  // glFramebufferFetchBarrierEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_shader_image_load_store(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_shader_image_load_store) return;
    static const uint16_t s_pfnIdx[] = {
           60, // glBindImageTextureEXT
         1189  // glMemoryBarrierEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_stencil_clear_tag(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_stencil_clear_tag) return;
    static const uint16_t s_pfnIdx[] = {
         1793  // glStencilClearTagEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_stencil_two_side(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_stencil_two_side) return;
    static const uint16_t s_pfnIdx[] = {
            4  // glActiveStencilFaceEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_subtexture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_subtexture) return;
    static const uint16_t s_pfnIdx[] = {
         1930, // glTexSubImage1DEXT
         1932  // glTexSubImage2DEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture3D(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_texture3D) return;
    static const uint16_t s_pfnIdx[] = {
         1894, // glTexImage3DEXT
         1934  // glTexSubImage3DEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_texture_array) return;
    static const uint16_t s_pfnIdx[] = {
          566  // glFramebufferTextureLayerEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_texture_buffer_object) return;
    static const uint16_t s_pfnIdx[] = {
         1837  // glTexBufferEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_integer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_texture_integer) return;
    static const uint16_t s_pfnIdx[] = {
          160, // glClearColorIiEXT
          161, // glClearColorIuiEXT
          892, // glGetTexParameterIivEXT
          894, // glGetTexParameterIuivEXT
         1901, // glTexParameterIivEXT
         1903  // glTexParameterIuivEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_texture_object) return;
    static const uint16_t s_pfnIdx[] = {
           16, // glAreTexturesResidentEXT
           76, // glBindTextureEXT
          375, // glDeleteTexturesEXT
          596, // glGenTexturesEXT
         1087, // glIsTextureEXT
         1467  // glPrioritizeTexturesEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_perturb_normal(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_texture_perturb_normal) return;
    static const uint16_t s_pfnIdx[] = {
         1953  // glTextureNormalEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_storage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_texture_storage) return;
    static const uint16_t s_pfnIdx[] = {
         1912, // glTexStorage1DEXT
         1914, // glTexStorage2DEXT
         1917, // glTexStorage3DEXT
         1971, // glTextureStorage1DEXT
         1973, // glTextureStorage2DEXT
         1977  // glTextureStorage3DEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_timer_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_timer_query) return;
    static const uint16_t s_pfnIdx[] = {
          850, // glGetQueryObjecti64vEXT
          854  // glGetQueryObjectui64vEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_transform_feedback(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_transform_feedback) return;
    static const uint16_t s_pfnIdx[] = {
           35, // glBeginTransformFeedbackEXT
           44, // glBindBufferBaseEXT
           46, // glBindBufferOffsetEXT
           49, // glBindBufferRangeEXT
          483, // glEndTransformFeedbackEXT
          920, // glGetTransformFeedbackVaryingEXT
         1999  // glTransformFeedbackVaryingsEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_vertex_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_vertex_array) return;
    static const uint16_t s_pfnIdx[] = {
           17, // glArrayElementEXT
          210, // glColorPointerEXT
          413, // glDrawArraysEXT
          456, // glEdgeFlagPointerEXT
          813, // glGetPointervEXT
         1033, // glIndexPointerEXT
         1374, // glNormalPointerEXT
         1880, // glTexCoordPointerEXT
         2434  // glVertexPointerEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_vertex_attrib_64bit(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_vertex_attrib_64bit) return;
    static const uint16_t s_pfnIdx[] = {
          966, // glGetVertexAttribLdvEXT
         2363, // glVertexAttribL1dEXT
         2365, // glVertexAttribL1dvEXT
         2373, // glVertexAttribL2dEXT
         2375, // glVertexAttribL2dvEXT
         2381, // glVertexAttribL3dEXT
         2383, // glVertexAttribL3dvEXT
         2389, // glVertexAttribL4dEXT
         2391, // glVertexAttribL4dvEXT
         2399  // glVertexAttribLPointerEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_vertex_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_vertex_shader) return;
    static const uint16_t s_pfnIdx[] = {
           37, // glBeginVertexShaderEXT
           62, // glBindLightParameterEXT
           63, // glBindMaterialParameterEXT
           65, // glBindParameterEXT
           74, // glBindTexGenParameterEXT
           78, // glBindTextureUnitParameterEXT
           86, // glBindVertexShaderEXT
          380, // glDeleteVertexShaderEXT
          401, // glDisableVariantClientStateEXT
          464, // glEnableVariantClientStateEXT
          485, // glEndVertexShaderEXT
          494, // glExtractComponentEXT
          594, // glGenSymbolsEXT
          601, // glGenVertexShadersEXT
          717, // glGetInvariantBooleanvEXT
          718, // glGetInvariantFloatvEXT
          719, // glGetInvariantIntegervEXT
          723, // glGetLocalConstantBooleanvEXT
          724, // glGetLocalConstantFloatvEXT
          725, // glGetLocalConstantIntegervEXT
          947, // glGetVariantBooleanvEXT
          948, // glGetVariantFloatvEXT
          949, // glGetVariantIntegervEXT
          950, // glGetVariantPointervEXT
         1037, // glInsertComponentEXT
         1092, // glIsVariantEnabledEXT
         1766, // glSetInvariantEXT
         1767, // glSetLocalConstantEXT
         1770, // glShaderOp1EXT
         1771, // glShaderOp2EXT
         1772, // glShaderOp3EXT
         1814, // glSwizzleEXT
         2149, // glVariantPointerEXT
         2150, // glVariantbvEXT
         2151, // glVariantdvEXT
         2152, // glVariantfvEXT
         2153, // glVariantivEXT
         2154, // glVariantsvEXT
         2155, // glVariantubvEXT
         2156, // glVariantuivEXT
         2157, // glVariantusvEXT
         2539  // glWriteMaskEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_vertex_weighting(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_vertex_weighting) return;
    static const uint16_t s_pfnIdx[] = {
         2469, // glVertexWeightPointerEXT
         2470, // glVertexWeightfEXT
         2471  // glVertexWeightfvEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_win32_keyed_mutex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_win32_keyed_mutex) return;
    static const uint16_t s_pfnIdx[] = {
            1, // glAcquireKeyedMutexWin32EXT
         1675  // glReleaseKeyedMutexWin32EXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_window_rectangles(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_window_rectangles) return;
    static const uint16_t s_pfnIdx[] = {
         2538  // glWindowRectanglesEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_x11_sync_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_x11_sync_object) return;
    static const uint16_t s_pfnIdx[] = {
         1029  // glImportSyncEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_GREMEDY_frame_terminator(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->GREMEDY_frame_terminator) return;
    static const uint16_t s_pfnIdx[] = {
          540  // glFrameTerminatorGREMEDY
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_GREMEDY_string_marker(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->GREMEDY_string_marker) return;
    static const uint16_t s_pfnIdx[] = {
         1812  // glStringMarkerGREMEDY
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_HP_image_transform(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->HP_image_transform) return;
    static const uint16_t s_pfnIdx[] = {
          703, // glGetImageTransformParameterfvHP
          704, // glGetImageTransformParameterivHP
         1017, // glImageTransformParameterfHP
         1018, // glImageTransformParameterfvHP
         1019, // glImageTransformParameteriHP
         1020  // glImageTransformParameterivHP
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_IBM_multimode_draw_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->IBM_multimode_draw_arrays) return;
    static const uint16_t s_pfnIdx[] = {
         1219, // glMultiModeDrawArraysIBM
         1220  // glMultiModeDrawElementsIBM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_IBM_static_data(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->IBM_static_data) return;
    static const uint16_t s_pfnIdx[] = {
          511  // glFlushStaticDataIBM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_IBM_vertex_array_lists(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->IBM_vertex_array_lists) return;
    static const uint16_t s_pfnIdx[] = {
          211, // glColorPointerListIBM
          457, // glEdgeFlagPointerListIBM
          516, // glFogCoordPointerListIBM
         1034, // glIndexPointerListIBM
         1375, // glNormalPointerListIBM
         1758, // glSecondaryColorPointerListIBM
         1881, // glTexCoordPointerListIBM
         2435  // glVertexPointerListIBM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_INGR_blend_func_separate(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->INGR_blend_func_separate) return;
    static const uint16_t s_pfnIdx[] = {
          120  // glBlendFuncSeparateINGR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_INTEL_framebuffer_CMAA(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->INTEL_framebuffer_CMAA) return;
    static const uint16_t s_pfnIdx[] = {
           13  // glApplyFramebufferAttachmentCMAAINTEL
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_INTEL_map_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->INTEL_map_texture) return;
    static const uint16_t s_pfnIdx[] = {
         1149, // glMapTexture2DINTEL
         1815, // glSyncTextureINTEL
         2127  // glUnmapTexture2DINTEL
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_INTEL_parallel_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->INTEL_parallel_arrays) return;
    static const uint16_t s_pfnIdx[] = {
          212, // glColorPointervINTEL
         1376, // glNormalPointervINTEL
         1882, // glTexCoordPointervINTEL
         2436  // glVertexPointervINTEL
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_INTEL_performance_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->INTEL_performance_query) return;
    static const uint16_t s_pfnIdx[] = {
           30, // glBeginPerfQueryINTEL
          309, // glCreatePerfQueryINTEL
          359, // glDeletePerfQueryINTEL
          478, // glEndPerfQueryINTEL
          674, // glGetFirstPerfQueryIdINTEL
          775, // glGetNextPerfQueryIdINTEL
          795, // glGetPerfCounterInfoINTEL
          802, // glGetPerfQueryDataINTEL
          803, // glGetPerfQueryIdByNameINTEL
          804  // glGetPerfQueryInfoINTEL
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_KHR_blend_equation_advanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_blend_equation_advanced) return;
    static const uint16_t s_pfnIdx[] = {
          101  // glBlendBarrierKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_KHR_debug(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_debug) return;
    static const uint16_t s_pfnIdx[] = {
          331, // glDebugMessageCallback
         2588, // glDebugMessageCallbackKHR
          334, // glDebugMessageControl
         2589, // glDebugMessageControlKHR
          337, // glDebugMessageInsert
         2590, // glDebugMessageInsertKHR
          662, // glGetDebugMessageLog
         2679, // glGetDebugMessageLogKHR
          778, // glGetObjectLabel
         2706, // glGetObjectLabelKHR
          783, // glGetObjectPtrLabel
         2707, // glGetObjectPtrLabelKHR
          812, // glGetPointerv
         2708, // glGetPointervKHR
         1387, // glObjectLabel
         2788, // glObjectLabelKHR
         1388, // glObjectPtrLabel
         2789, // glObjectPtrLabelKHR
         1459, // glPopDebugGroup
         2795, // glPopDebugGroupKHR
         1653, // glPushDebugGroup
         2803  // glPushDebugGroupKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_KHR_parallel_shader_compile(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_parallel_shader_compile) return;
    static const uint16_t s_pfnIdx[] = {
         1186  // glMaxShaderCompilerThreadsKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_KHR_robustness(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->KHR_robustness) return;
    static const uint16_t s_pfnIdx[] = {
          694, // glGetGraphicsResetStatus
         2695, // glGetGraphicsResetStatusKHR
          997, // glGetnUniformfv
         2759, // glGetnUniformfvKHR
         1000, // glGetnUniformiv
         2762, // glGetnUniformivKHR
         1003, // glGetnUniformuiv
         2764, // glGetnUniformuivKHR
         1670, // glReadnPixels
         2809  // glReadnPixelsKHR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_MESA_framebuffer_flip_y(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_framebuffer_flip_y) return;
    static const uint16_t s_pfnIdx[] = {
          546, // glFramebufferParameteriMESA
          693  // glGetFramebufferParameterivMESA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_MESA_resize_buffers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_resize_buffers) return;
    static const uint16_t s_pfnIdx[] = {
         1711  // glResizeBuffersMESA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_MESA_window_pos(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_window_pos) return;
    static const uint16_t s_pfnIdx[] = {
         2499, // glWindowPos2dMESA
         2501, // glWindowPos2dvMESA
         2503, // glWindowPos2fMESA
         2505, // glWindowPos2fvMESA
         2507, // glWindowPos2iMESA
         2509, // glWindowPos2ivMESA
         2511, // glWindowPos2sMESA
         2513, // glWindowPos2svMESA
         2515, // glWindowPos3dMESA
         2517, // glWindowPos3dvMESA
         2519, // glWindowPos3fMESA
         2521, // glWindowPos3fvMESA
         2523, // glWindowPos3iMESA
         2525, // glWindowPos3ivMESA
         2527, // glWindowPos3sMESA
         2529, // glWindowPos3svMESA
         2530, // glWindowPos4dMESA
         2531, // glWindowPos4dvMESA
         2532, // glWindowPos4fMESA
         2533, // glWindowPos4fvMESA
         2534, // glWindowPos4iMESA
         2535, // glWindowPos4ivMESA
         2536, // glWindowPos4sMESA
         2537  // glWindowPos4svMESA
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NVX_conditional_render(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NVX_conditional_render) return;
    static const uint16_t s_pfnIdx[] = {
           26, // glBeginConditionalRenderNVX
          474  // glEndConditionalRenderNVX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NVX_gpu_multicast2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NVX_gpu_multicast2) return;
    static const uint16_t s_pfnIdx[] = {
           19, // glAsyncCopyBufferSubDataNVX
           20, // glAsyncCopyImageSubDataNVX
         1312, // glMulticastScissorArrayvNVX
         1313, // glMulticastViewportArrayvNVX
         1314, // glMulticastViewportPositionWScaleNVX
         2129  // glUploadGpuMaskNVX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NVX_linked_gpu_multicast(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NVX_linked_gpu_multicast) return;
    static const uint16_t s_pfnIdx[] = {
         1096, // glLGPUCopyImageSubDataNVX
         1097, // glLGPUInterlockNVX
         1098  // glLGPUNamedBufferSubDataNVX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NVX_progress_fence(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NVX_progress_fence) return;
    static const uint16_t s_pfnIdx[] = {
          182, // glClientWaitSemaphoreui64NVX
          313, // glCreateProgressFenceNVX
         1782, // glSignalSemaphoreui64NVX
         2485  // glWaitSemaphoreui64NVX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_alpha_to_coverage_dither_control(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_alpha_to_coverage_dither_control) return;
    static const uint16_t s_pfnIdx[] = {
           12  // glAlphaToCoverageDitherControlNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_bindless_multi_draw_indirect(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_bindless_multi_draw_indirect) return;
    static const uint16_t s_pfnIdx[] = {
         1203, // glMultiDrawArraysIndirectBindlessNV
         1213  // glMultiDrawElementsIndirectBindlessNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_bindless_multi_draw_indirect_count(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_bindless_multi_draw_indirect_count) return;
    static const uint16_t s_pfnIdx[] = {
         1202, // glMultiDrawArraysIndirectBindlessCountNV
         1212  // glMultiDrawElementsIndirectBindlessCountNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_bindless_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_bindless_texture) return;
    static const uint16_t s_pfnIdx[] = {
          702, // glGetImageHandleNV
          900, // glGetTextureHandleNV
          916, // glGetTextureSamplerHandleNV
         1063, // glIsImageHandleResidentNV
         1089, // glIsTextureHandleResidentNV
         1125, // glMakeImageHandleNonResidentNV
         1127, // glMakeImageHandleResidentNV
         1131, // glMakeTextureHandleNonResidentNV
         1133, // glMakeTextureHandleResidentNV
         1608, // glProgramUniformHandleui64NV
         1610, // glProgramUniformHandleui64vNV
         2094, // glUniformHandleui64NV
         2096  // glUniformHandleui64vNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_blend_equation_advanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_blend_equation_advanced) return;
    static const uint16_t s_pfnIdx[] = {
          102, // glBlendBarrierNV
          126  // glBlendParameteriNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_clip_space_w_scaling(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_clip_space_w_scaling) return;
    static const uint16_t s_pfnIdx[] = {
         2482  // glViewportPositionWScaleNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_command_list(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_command_list) return;
    static const uint16_t s_pfnIdx[] = {
          144, // glCallCommandListNV
          225, // glCommandListSegmentsNV
          226, // glCompileCommandListNV
          306, // glCreateCommandListsNV
          322, // glCreateStatesNV
          346, // glDeleteCommandListsNV
          372, // glDeleteStatesNV
          423, // glDrawCommandsAddressNV
          424, // glDrawCommandsNV
          425, // glDrawCommandsStatesAddressNV
          426, // glDrawCommandsStatesNV
          650, // glGetCommandHeaderNV
          876, // glGetStageIndexNV
         1054, // glIsCommandListNV
         1084, // glIsStateNV
         1109, // glListDrawCommandsStatesClientNV
         1792  // glStateCaptureNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_conditional_render(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_conditional_render) return;
    static const uint16_t s_pfnIdx[] = {
           25, // glBeginConditionalRenderNV
          473  // glEndConditionalRenderNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_conservative_raster(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_conservative_raster) return;
    static const uint16_t s_pfnIdx[] = {
         1813  // glSubpixelPrecisionBiasNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_conservative_raster_dilate(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_conservative_raster_dilate) return;
    static const uint16_t s_pfnIdx[] = {
          257  // glConservativeRasterParameterfNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_conservative_raster_pre_snap_triangles(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_conservative_raster_pre_snap_triangles) return;
    static const uint16_t s_pfnIdx[] = {
          258  // glConservativeRasterParameteriNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_copy_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_copy_image) return;
    static const uint16_t s_pfnIdx[] = {
          273  // glCopyImageSubDataNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_depth_buffer_float(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_depth_buffer_float) return;
    static const uint16_t s_pfnIdx[] = {
          164, // glClearDepthdNV
          382, // glDepthBoundsdNV
          390  // glDepthRangedNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_draw_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_draw_texture) return;
    static const uint16_t s_pfnIdx[] = {
          446  // glDrawTextureNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_draw_vulkan_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_draw_vulkan_image) return;
    static const uint16_t s_pfnIdx[] = {
          452, // glDrawVkImageNV
          990, // glGetVkProcAddrNV
         1783, // glSignalVkFenceNV
         1784, // glSignalVkSemaphoreNV
         2487  // glWaitVkSemaphoreNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_evaluators(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_evaluators) return;
    static const uint16_t s_pfnIdx[] = {
          491, // glEvalMapsNV
          726, // glGetMapAttribParameterfvNV
          727, // glGetMapAttribParameterivNV
          728, // glGetMapControlPointsNV
          729, // glGetMapParameterfvNV
          730, // glGetMapParameterivNV
         1139, // glMapControlPointsNV
         1147, // glMapParameterfvNV
         1148  // glMapParameterivNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_explicit_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_explicit_multisample) return;
    static const uint16_t s_pfnIdx[] = {
          751, // glGetMultisamplefvNV
         1720, // glSampleMaskIndexedNV
         1910  // glTexRenderbufferNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_fence(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_fence) return;
    static const uint16_t s_pfnIdx[] = {
          348, // glDeleteFencesNV
          501, // glFinishFenceNV
          576, // glGenFencesNV
          671, // glGetFenceivNV
         1059, // glIsFenceNV
         1764, // glSetFenceNV
         1832  // glTestFenceNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_fragment_coverage_to_color(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_fragment_coverage_to_color) return;
    static const uint16_t s_pfnIdx[] = {
          527  // glFragmentCoverageColorNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_fragment_program(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_fragment_program) return;
    static const uint16_t s_pfnIdx[] = {
          825, // glGetProgramNamedParameterdvNV
          826, // glGetProgramNamedParameterfvNV
         1495, // glProgramNamedParameter4dNV
         1496, // glProgramNamedParameter4dvNV
         1497, // glProgramNamedParameter4fNV
         1498  // glProgramNamedParameter4fvNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_framebuffer_mixed_samples(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_framebuffer_mixed_samples) return;
    static const uint16_t s_pfnIdx[] = {
          303, // glCoverageModulationNV
          304, // glCoverageModulationTableNV
          661, // glGetCoverageModulationTableNV
         1666  // glRasterSamplesEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_framebuffer_multisample_coverage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_framebuffer_multisample_coverage) return;
    static const uint16_t s_pfnIdx[] = {
         1682  // glRenderbufferStorageMultisampleCoverageNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_geometry_program4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_geometry_program4) return;
    static const uint16_t s_pfnIdx[] = {
          561, // glFramebufferTextureEXT
          563, // glFramebufferTextureFaceEXT
          566, // glFramebufferTextureLayerEXT
         1649  // glProgramVertexLimitNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_gpu_multicast(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_gpu_multicast) return;
    static const uint16_t s_pfnIdx[] = {
         1302, // glMulticastBarrierNV
         1303, // glMulticastBlitFramebufferNV
         1304, // glMulticastBufferSubDataNV
         1305, // glMulticastCopyBufferSubDataNV
         1306, // glMulticastCopyImageSubDataNV
         1307, // glMulticastFramebufferSampleLocationsfvNV
         1308, // glMulticastGetQueryObjecti64vNV
         1309, // glMulticastGetQueryObjectivNV
         1310, // glMulticastGetQueryObjectui64vNV
         1311, // glMulticastGetQueryObjectuivNV
         1315, // glMulticastWaitSyncNV
         1677  // glRenderGpuMaskNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_gpu_program4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_gpu_program4) return;
    static const uint16_t s_pfnIdx[] = {
          815, // glGetProgramEnvParameterIivNV
          816, // glGetProgramEnvParameterIuivNV
          821, // glGetProgramLocalParameterIivNV
          822, // glGetProgramLocalParameterIuivNV
         1477, // glProgramEnvParameterI4iNV
         1478, // glProgramEnvParameterI4ivNV
         1479, // glProgramEnvParameterI4uiNV
         1480, // glProgramEnvParameterI4uivNV
         1482, // glProgramEnvParametersI4ivNV
         1483, // glProgramEnvParametersI4uivNV
         1488, // glProgramLocalParameterI4iNV
         1489, // glProgramLocalParameterI4ivNV
         1490, // glProgramLocalParameterI4uiNV
         1491, // glProgramLocalParameterI4uivNV
         1493, // glProgramLocalParametersI4ivNV
         1494  // glProgramLocalParametersI4uivNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_gpu_program5(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_gpu_program5) return;
    static const uint16_t s_pfnIdx[] = {
          840, // glGetProgramSubroutineParameteruivNV
         1510  // glProgramSubroutineParametersuivNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_gpu_shader5(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_gpu_shader5) return;
    static const uint16_t s_pfnIdx[] = {
          936, // glGetUniformi64vNV
         1521, // glProgramUniform1i64NV
         1523, // glProgramUniform1i64vNV
         1529, // glProgramUniform1ui64NV
         1531, // glProgramUniform1ui64vNV
         1545, // glProgramUniform2i64NV
         1547, // glProgramUniform2i64vNV
         1553, // glProgramUniform2ui64NV
         1555, // glProgramUniform2ui64vNV
         1569, // glProgramUniform3i64NV
         1571, // glProgramUniform3i64vNV
         1577, // glProgramUniform3ui64NV
         1579, // glProgramUniform3ui64vNV
         1593, // glProgramUniform4i64NV
         1595, // glProgramUniform4i64vNV
         1601, // glProgramUniform4ui64NV
         1603, // glProgramUniform4ui64vNV
         2011, // glUniform1i64NV
         2013, // glUniform1i64vNV
         2019, // glUniform1ui64NV
         2021, // glUniform1ui64vNV
         2033, // glUniform2i64NV
         2035, // glUniform2i64vNV
         2041, // glUniform2ui64NV
         2043, // glUniform2ui64vNV
         2055, // glUniform3i64NV
         2057, // glUniform3i64vNV
         2063, // glUniform3ui64NV
         2065, // glUniform3ui64vNV
         2077, // glUniform4i64NV
         2079, // glUniform4i64vNV
         2085, // glUniform4ui64NV
         2087  // glUniform4ui64vNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_half_float(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_half_float) return;
    static const uint16_t s_pfnIdx[] = {
          189, // glColor3hNV
          190, // glColor3hvNV
          195, // glColor4hNV
          196, // glColor4hvNV
          521, // glFogCoordhNV
          522, // glFogCoordhvNV
         1228, // glMultiTexCoord1hNV
         1229, // glMultiTexCoord1hvNV
         1242, // glMultiTexCoord2hNV
         1243, // glMultiTexCoord2hvNV
         1256, // glMultiTexCoord3hNV
         1257, // glMultiTexCoord3hvNV
         1270, // glMultiTexCoord4hNV
         1271, // glMultiTexCoord4hvNV
         1369, // glNormal3hNV
         1370, // glNormal3hvNV
         1744, // glSecondaryColor3hNV
         1745, // glSecondaryColor3hvNV
         1843, // glTexCoord1hNV
         1844, // glTexCoord1hvNV
         1859, // glTexCoord2hNV
         1860, // glTexCoord2hvNV
         1865, // glTexCoord3hNV
         1866, // glTexCoord3hvNV
         1875, // glTexCoord4hNV
         1876, // glTexCoord4hvNV
         2160, // glVertex2hNV
         2161, // glVertex2hvNV
         2166, // glVertex3hNV
         2167, // glVertex3hvNV
         2172, // glVertex4hNV
         2173, // glVertex4hvNV
         2218, // glVertexAttrib1hNV
         2219, // glVertexAttrib1hvNV
         2238, // glVertexAttrib2hNV
         2239, // glVertexAttrib2hvNV
         2258, // glVertexAttrib3hNV
         2259, // glVertexAttrib3hvNV
         2294, // glVertexAttrib4hNV
         2295, // glVertexAttrib4hvNV
         2414, // glVertexAttribs1hvNV
         2418, // glVertexAttribs2hvNV
         2422, // glVertexAttribs3hvNV
         2426, // glVertexAttribs4hvNV
         2472, // glVertexWeighthNV
         2473  // glVertexWeighthvNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_internalformat_sample_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_internalformat_sample_query) return;
    static const uint16_t s_pfnIdx[] = {
          714  // glGetInternalformatSampleivNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_memory_attachment(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_memory_attachment) return;
    static const uint16_t s_pfnIdx[] = {
          133, // glBufferAttachMemoryNV
          733, // glGetMemoryObjectDetachedResourcesuivNV
         1316, // glNamedBufferAttachMemoryNV
         1709, // glResetMemoryObjectParameterNV
         1834, // glTexAttachMemoryNV
         1936  // glTextureAttachMemoryNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_memory_object_sparse(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_memory_object_sparse) return;
    static const uint16_t s_pfnIdx[] = {
          137, // glBufferPageCommitmentMemNV
         1321, // glNamedBufferPageCommitmentMemNV
         1899, // glTexPageCommitmentMemNV
         1955  // glTexturePageCommitmentMemNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_mesh_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_mesh_shader) return;
    static const uint16_t s_pfnIdx[] = {
          439, // glDrawMeshTasksIndirectNV
          440, // glDrawMeshTasksNV
         1216, // glMultiDrawMeshTasksIndirectCountNV
         1217  // glMultiDrawMeshTasksIndirectNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_occlusion_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_occlusion_query) return;
    static const uint16_t s_pfnIdx[] = {
           28, // glBeginOcclusionQueryNV
          356, // glDeleteOcclusionQueriesNV
          476, // glEndOcclusionQueryNV
          581, // glGenOcclusionQueriesNV
          784, // glGetOcclusionQueryivNV
          785, // glGetOcclusionQueryuivNV
         1069  // glIsOcclusionQueryNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_parameter_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_parameter_buffer_object) return;
    static const uint16_t s_pfnIdx[] = {
         1470, // glProgramBufferParametersIivNV
         1471, // glProgramBufferParametersIuivNV
         1472  // glProgramBufferParametersfvNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_path_rendering(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_path_rendering) return;
    static const uint16_t s_pfnIdx[] = {
          280, // glCopyPathNV
          299, // glCoverFillPathInstancedNV
          300, // glCoverFillPathNV
          301, // glCoverStrokePathInstancedNV
          302, // glCoverStrokePathNV
          357, // glDeletePathsNV
          582, // glGenPathsNV
          786, // glGetPathCommandsNV
          787, // glGetPathCoordsNV
          788, // glGetPathDashArrayNV
          789, // glGetPathLengthNV
          790, // glGetPathMetricRangeNV
          791, // glGetPathMetricsNV
          792, // glGetPathParameterfvNV
          793, // glGetPathParameterivNV
          794, // glGetPathSpacingNV
          835, // glGetProgramResourcefvNV
         1040, // glInterpolatePathsNV
         1070, // glIsPathNV
         1071, // glIsPointInFillPathNV
         1072, // glIsPointInStrokePathNV
         1156, // glMatrixFrustumEXT
         1161, // glMatrixLoad3x2fNV
         1162, // glMatrixLoad3x3fNV
         1163, // glMatrixLoadIdentityEXT
         1164, // glMatrixLoadTranspose3x3fNV
         1165, // glMatrixLoadTransposedEXT
         1166, // glMatrixLoadTransposefEXT
         1167, // glMatrixLoaddEXT
         1168, // glMatrixLoadfEXT
         1169, // glMatrixMult3x2fNV
         1170, // glMatrixMult3x3fNV
         1171, // glMatrixMultTranspose3x3fNV
         1172, // glMatrixMultTransposedEXT
         1173, // glMatrixMultTransposefEXT
         1174, // glMatrixMultdEXT
         1175, // glMatrixMultfEXT
         1176, // glMatrixOrthoEXT
         1177, // glMatrixPopEXT
         1178, // glMatrixPushEXT
         1179, // glMatrixRotatedEXT
         1180, // glMatrixRotatefEXT
         1181, // glMatrixScaledEXT
         1182, // glMatrixScalefEXT
         1183, // glMatrixTranslatedEXT
         1184, // glMatrixTranslatefEXT
         1399, // glPathCommandsNV
         1400, // glPathCoordsNV
         1401, // glPathCoverDepthFuncNV
         1402, // glPathDashArrayNV
         1403, // glPathGlyphIndexArrayNV
         1404, // glPathGlyphIndexRangeNV
         1405, // glPathGlyphRangeNV
         1406, // glPathGlyphsNV
         1407, // glPathMemoryGlyphIndexArrayNV
         1408, // glPathParameterfNV
         1409, // glPathParameterfvNV
         1410, // glPathParameteriNV
         1411, // glPathParameterivNV
         1412, // glPathStencilDepthOffsetNV
         1413, // glPathStencilFuncNV
         1414, // glPathStringNV
         1415, // glPathSubCommandsNV
         1416, // glPathSubCoordsNV
         1435, // glPointAlongPathNV
         1508, // glProgramPathFragmentInputGenNV
         1794, // glStencilFillPathInstancedNV
         1795, // glStencilFillPathNV
         1805, // glStencilStrokePathInstancedNV
         1806, // glStencilStrokePathNV
         1807, // glStencilThenCoverFillPathInstancedNV
         1808, // glStencilThenCoverFillPathNV
         1809, // glStencilThenCoverStrokePathInstancedNV
         1810, // glStencilThenCoverStrokePathNV
         2001, // glTransformPathNV
         2488  // glWeightPathsNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_pixel_data_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_pixel_data_range) return;
    static const uint16_t s_pfnIdx[] = {
          509, // glFlushPixelDataRangeNV
         1419  // glPixelDataRangeNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_point_sprite(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_point_sprite) return;
    static const uint16_t s_pfnIdx[] = {
         1445, // glPointParameteriNV
         1447  // glPointParameterivNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_present_video(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_present_video) return;
    static const uint16_t s_pfnIdx[] = {
          986, // glGetVideoi64vNV
          987, // glGetVideoivNV
          988, // glGetVideoui64vNV
          989, // glGetVideouivNV
         1461, // glPresentFrameDualFillNV
         1462  // glPresentFrameKeyedNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_primitive_restart(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_primitive_restart) return;
    static const uint16_t s_pfnIdx[] = {
         1465, // glPrimitiveRestartIndexNV
         1466  // glPrimitiveRestartNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_query_resource(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_query_resource) return;
    static const uint16_t s_pfnIdx[] = {
         1658  // glQueryResourceNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_query_resource_tag(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_query_resource_tag) return;
    static const uint16_t s_pfnIdx[] = {
          366, // glDeleteQueryResourceTagNV
          589, // glGenQueryResourceTagNV
         1659  // glQueryResourceTagNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_register_combiners(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_register_combiners) return;
    static const uint16_t s_pfnIdx[] = {
          218, // glCombinerInputNV
          219, // glCombinerOutputNV
          220, // glCombinerParameterfNV
          221, // glCombinerParameterfvNV
          222, // glCombinerParameteriNV
          223, // glCombinerParameterivNV
          497, // glFinalCombinerInputNV
          645, // glGetCombinerInputParameterfvNV
          646, // glGetCombinerInputParameterivNV
          647, // glGetCombinerOutputParameterfvNV
          648, // glGetCombinerOutputParameterivNV
          672, // glGetFinalCombinerInputParameterfvNV
          673  // glGetFinalCombinerInputParameterivNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_register_combiners2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_register_combiners2) return;
    static const uint16_t s_pfnIdx[] = {
          224, // glCombinerStageParameterfvNV
          649  // glGetCombinerStageParameterfvNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_sample_locations(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_sample_locations) return;
    static const uint16_t s_pfnIdx[] = {
          551, // glFramebufferSampleLocationsfvNV
         1337, // glNamedFramebufferSampleLocationsfvNV
         1712  // glResolveDepthValuesNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_scissor_exclusive(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_scissor_exclusive) return;
    static const uint16_t s_pfnIdx[] = {
         1734, // glScissorExclusiveArrayvNV
         1735  // glScissorExclusiveNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_shader_buffer_load(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_shader_buffer_load) return;
    static const uint16_t s_pfnIdx[] = {
          632, // glGetBufferParameterui64vNV
          712, // glGetIntegerui64vNV
          755, // glGetNamedBufferParameterui64vNV
          940, // glGetUniformui64vNV
         1053, // glIsBufferResidentNV
         1066, // glIsNamedBufferResidentNV
         1122, // glMakeBufferNonResidentNV
         1123, // glMakeBufferResidentNV
         1128, // glMakeNamedBufferNonResidentNV
         1129, // glMakeNamedBufferResidentNV
         1647, // glProgramUniformui64NV
         1648, // glProgramUniformui64vNV
         2119, // glUniformui64NV
         2120  // glUniformui64vNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_shading_rate_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_shading_rate_image) return;
    static const uint16_t s_pfnIdx[] = {
           73, // glBindShadingRateImageNV
          873, // glGetShadingRateImagePaletteNV
          874, // glGetShadingRateSampleLocationivNV
         1776, // glShadingRateImageBarrierNV
         1777, // glShadingRateImagePaletteNV
         1778, // glShadingRateSampleOrderCustomNV
         1779  // glShadingRateSampleOrderNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_texture_barrier(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_texture_barrier) return;
    static const uint16_t s_pfnIdx[] = {
         1938  // glTextureBarrierNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_texture_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_texture_multisample) return;
    static const uint16_t s_pfnIdx[] = {
         1892, // glTexImage2DMultisampleCoverageNV
         1896, // glTexImage3DMultisampleCoverageNV
         1946, // glTextureImage2DMultisampleCoverageNV
         1947, // glTextureImage2DMultisampleNV
         1949, // glTextureImage3DMultisampleCoverageNV
         1950  // glTextureImage3DMultisampleNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_timeline_semaphore(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_timeline_semaphore) return;
    static const uint16_t s_pfnIdx[] = {
          317, // glCreateSemaphoresNV
          865, // glGetSemaphoreParameterivNV
         1760  // glSemaphoreParameterivNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_transform_feedback(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_transform_feedback) return;
    static const uint16_t s_pfnIdx[] = {
            7, // glActiveVaryingNV
           36, // glBeginTransformFeedbackNV
           45, // glBindBufferBaseNV
           47, // glBindBufferOffsetNV
           50, // glBindBufferRangeNV
          484, // glEndTransformFeedbackNV
          619, // glGetActiveVaryingNV
          921, // glGetTransformFeedbackVaryingNV
          951, // glGetVaryingLocationNV
         1994, // glTransformFeedbackAttribsNV
         1997, // glTransformFeedbackStreamAttribsNV
         2000  // glTransformFeedbackVaryingsNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_transform_feedback2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_transform_feedback2) return;
    static const uint16_t s_pfnIdx[] = {
           81, // glBindTransformFeedbackNV
          377, // glDeleteTransformFeedbacksNV
          449, // glDrawTransformFeedbackNV
          598, // glGenTransformFeedbacksNV
         1091, // glIsTransformFeedbackNV
         1418, // glPauseTransformFeedbackNV
         1714  // glResumeTransformFeedbackNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_vdpau_interop(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_vdpau_interop) return;
    static const uint16_t s_pfnIdx[] = {
         2134, // glVDPAUFiniNV
         2135, // glVDPAUGetSurfaceivNV
         2136, // glVDPAUInitNV
         2137, // glVDPAUIsSurfaceNV
         2138, // glVDPAUMapSurfacesNV
         2139, // glVDPAURegisterOutputSurfaceNV
         2140, // glVDPAURegisterVideoSurfaceNV
         2142, // glVDPAUSurfaceAccessNV
         2143, // glVDPAUUnmapSurfacesNV
         2144  // glVDPAUUnregisterSurfaceNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_vdpau_interop2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_vdpau_interop2) return;
    static const uint16_t s_pfnIdx[] = {
         2141  // glVDPAURegisterVideoSurfaceWithPictureStructureNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_vertex_array_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_vertex_array_range) return;
    static const uint16_t s_pfnIdx[] = {
          513, // glFlushVertexArrayRangeNV
         2191  // glVertexArrayRangeNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_vertex_attrib_integer_64bit(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_vertex_attrib_integer_64bit) return;
    static const uint16_t s_pfnIdx[] = {
          967, // glGetVertexAttribLi64vNV
          969, // glGetVertexAttribLui64vNV
         2366, // glVertexAttribL1i64NV
         2367, // glVertexAttribL1i64vNV
         2369, // glVertexAttribL1ui64NV
         2371, // glVertexAttribL1ui64vNV
         2376, // glVertexAttribL2i64NV
         2377, // glVertexAttribL2i64vNV
         2378, // glVertexAttribL2ui64NV
         2379, // glVertexAttribL2ui64vNV
         2384, // glVertexAttribL3i64NV
         2385, // glVertexAttribL3i64vNV
         2386, // glVertexAttribL3ui64NV
         2387, // glVertexAttribL3ui64vNV
         2392, // glVertexAttribL4i64NV
         2393, // glVertexAttribL4i64vNV
         2394, // glVertexAttribL4ui64NV
         2395, // glVertexAttribL4ui64vNV
         2397  // glVertexAttribLFormatNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_vertex_buffer_unified_memory(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_vertex_buffer_unified_memory) return;
    static const uint16_t s_pfnIdx[] = {
          132, // glBufferAddressRangeNV
          203, // glColorFormatNV
          455, // glEdgeFlagFormatNV
          514, // glFogCoordFormatNV
          711, // glGetIntegerui64i_vNV
         1030, // glIndexFormatNV
         1373, // glNormalFormatNV
         1756, // glSecondaryColorFormatNV
         1879, // glTexCoordFormatNV
         2317, // glVertexAttribFormatNV
         2359, // glVertexAttribIFormatNV
         2433  // glVertexFormatNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_vertex_program(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_vertex_program) return;
    static const uint16_t s_pfnIdx[] = {
           15, // glAreProgramsResidentNV
           67, // glBindProgramNV
          363, // glDeleteProgramsNV
          493, // glExecuteProgramNV
          586, // glGenProgramsNV
          827, // glGetProgramParameterdvNV
          828, // glGetProgramParameterfvNV
          839, // glGetProgramStringNV
          843, // glGetProgramivNV
          918, // glGetTrackMatrixivNV
          972, // glGetVertexAttribPointervNV
          975, // glGetVertexAttribdvNV
          978, // glGetVertexAttribfvNV
          981, // glGetVertexAttribivNV
         1075, // glIsProgramNV
         1116, // glLoadProgramNV
         1499, // glProgramParameter4dNV
         1500, // glProgramParameter4dvNV
         1501, // glProgramParameter4fNV
         1502, // glProgramParameter4fvNV
         1506, // glProgramParameters4dvNV
         1507, // glProgramParameters4fvNV
         1707, // glRequestResidentProgramsNV
         1993, // glTrackMatrixNV
         2208, // glVertexAttrib1dNV
         2211, // glVertexAttrib1dvNV
         2214, // glVertexAttrib1fNV
         2217, // glVertexAttrib1fvNV
         2222, // glVertexAttrib1sNV
         2225, // glVertexAttrib1svNV
         2228, // glVertexAttrib2dNV
         2231, // glVertexAttrib2dvNV
         2234, // glVertexAttrib2fNV
         2237, // glVertexAttrib2fvNV
         2242, // glVertexAttrib2sNV
         2245, // glVertexAttrib2svNV
         2248, // glVertexAttrib3dNV
         2251, // glVertexAttrib3dvNV
         2254, // glVertexAttrib3fNV
         2257, // glVertexAttrib3fvNV
         2262, // glVertexAttrib3sNV
         2265, // glVertexAttrib3svNV
         2284, // glVertexAttrib4dNV
         2287, // glVertexAttrib4dvNV
         2290, // glVertexAttrib4fNV
         2293, // glVertexAttrib4fvNV
         2300, // glVertexAttrib4sNV
         2303, // glVertexAttrib4svNV
         2304, // glVertexAttrib4ubNV
         2307, // glVertexAttrib4ubvNV
         2411, // glVertexAttribPointerNV
         2412, // glVertexAttribs1dvNV
         2413, // glVertexAttribs1fvNV
         2415, // glVertexAttribs1svNV
         2416, // glVertexAttribs2dvNV
         2417, // glVertexAttribs2fvNV
         2419, // glVertexAttribs2svNV
         2420, // glVertexAttribs3dvNV
         2421, // glVertexAttribs3fvNV
         2423, // glVertexAttribs3svNV
         2424, // glVertexAttribs4dvNV
         2425, // glVertexAttribs4fvNV
         2427, // glVertexAttribs4svNV
         2428  // glVertexAttribs4ubvNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_vertex_program4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_vertex_program4) return;
    static const uint16_t s_pfnIdx[] = {
          962, // glGetVertexAttribIivEXT
          964, // glGetVertexAttribIuivEXT
         2319, // glVertexAttribI1iEXT
         2321, // glVertexAttribI1ivEXT
         2323, // glVertexAttribI1uiEXT
         2325, // glVertexAttribI1uivEXT
         2327, // glVertexAttribI2iEXT
         2329, // glVertexAttribI2ivEXT
         2331, // glVertexAttribI2uiEXT
         2333, // glVertexAttribI2uivEXT
         2335, // glVertexAttribI3iEXT
         2337, // glVertexAttribI3ivEXT
         2339, // glVertexAttribI3uiEXT
         2341, // glVertexAttribI3uivEXT
         2343, // glVertexAttribI4bvEXT
         2345, // glVertexAttribI4iEXT
         2347, // glVertexAttribI4ivEXT
         2349, // glVertexAttribI4svEXT
         2351, // glVertexAttribI4ubvEXT
         2353, // glVertexAttribI4uiEXT
         2355, // glVertexAttribI4uivEXT
         2357, // glVertexAttribI4usvEXT
         2361  // glVertexAttribIPointerEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_video_capture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_video_capture) return;
    static const uint16_t s_pfnIdx[] = {
           38, // glBeginVideoCaptureNV
           87, // glBindVideoCaptureStreamBufferNV
           88, // glBindVideoCaptureStreamTextureNV
          486, // glEndVideoCaptureNV
          982, // glGetVideoCaptureStreamdvNV
          983, // glGetVideoCaptureStreamfvNV
          984, // glGetVideoCaptureStreamivNV
          985, // glGetVideoCaptureivNV
         2474, // glVideoCaptureNV
         2475, // glVideoCaptureStreamParameterdvNV
         2476, // glVideoCaptureStreamParameterfvNV
         2477  // glVideoCaptureStreamParameterivNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_viewport_swizzle(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_viewport_swizzle) return;
    static const uint16_t s_pfnIdx[] = {
         2483  // glViewportSwizzleNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_byte_coordinates(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_byte_coordinates) return;
    static const uint16_t s_pfnIdx[] = {
         1222, // glMultiTexCoord1bOES
         1223, // glMultiTexCoord1bvOES
         1236, // glMultiTexCoord2bOES
         1237, // glMultiTexCoord2bvOES
         1250, // glMultiTexCoord3bOES
         1251, // glMultiTexCoord3bvOES
         1264, // glMultiTexCoord4bOES
         1265, // glMultiTexCoord4bvOES
         1841, // glTexCoord1bOES
         1842, // glTexCoord1bvOES
         1847, // glTexCoord2bOES
         1848, // glTexCoord2bvOES
         1863, // glTexCoord3bOES
         1864, // glTexCoord3bvOES
         1869, // glTexCoord4bOES
         1870, // glTexCoord4bvOES
         2158, // glVertex2bOES
         2159, // glVertex2bvOES
         2164, // glVertex3bOES
         2165, // glVertex3bvOES
         2170, // glVertex4bOES
         2171  // glVertex4bvOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_fixed_point(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_fixed_point) return;
    static const uint16_t s_pfnIdx[] = {
            0, // glAccumxOES
           11, // glAlphaFuncxOES
          100, // glBitmapxOES
          105, // glBlendColorxOES
          152, // glClearAccumxOES
          162, // glClearColorxOES
          167, // glClearDepthxOES
          186, // glClipPlanexOES
          191, // glColor3xOES
          192, // glColor3xvOES
          201, // glColor4xOES
          202, // glColor4xvOES
          265, // glConvolutionParameterxOES
          266, // glConvolutionParameterxvOES
          393, // glDepthRangexOES
          487, // glEvalCoord1xOES
          488, // glEvalCoord1xvOES
          489, // glEvalCoord2xOES
          490, // glEvalCoord2xvOES
          495, // glFeedbackBufferxOES
          524, // glFogxOES
          525, // glFogxvOES
          571, // glFrustumxOES
          638, // glGetClipPlanexOES
          660, // glGetConvolutionParameterxvOES
          675, // glGetFixedvOES
          700, // glGetHistogramParameterxvOES
          720, // glGetLightxOES
          731, // glGetMapxvOES
          732, // glGetMaterialxOES
          805, // glGetPixelMapxv
          884, // glGetTexEnvxvOES
          886, // glGetTexGenxvOES
          890, // glGetTexLevelParameterxvOES
          898, // glGetTexParameterxvOES
         1035, // glIndexxOES
         1036, // glIndexxvOES
         1101, // glLightModelxOES
         1102, // glLightModelxvOES
         1103, // glLightxOES
         1104, // glLightxvOES
         1106, // glLineWidthxOES
         1115, // glLoadMatrixxOES
         1119, // glLoadTransposeMatrixxOES
         1134, // glMap1xOES
         1135, // glMap2xOES
         1140, // glMapGrid1xOES
         1141, // glMapGrid2xOES
         1154, // glMaterialxOES
         1155, // glMaterialxvOES
         1194, // glMultMatrixxOES
         1197, // glMultTransposeMatrixxOES
         1234, // glMultiTexCoord1xOES
         1235, // glMultiTexCoord1xvOES
         1248, // glMultiTexCoord2xOES
         1249, // glMultiTexCoord2xvOES
         1262, // glMultiTexCoord3xOES
         1263, // glMultiTexCoord3xvOES
         1276, // glMultiTexCoord4xOES
         1277, // glMultiTexCoord4xvOES
         1371, // glNormal3xOES
         1372, // glNormal3xvOES
         1392, // glOrthoxOES
         1396, // glPassThroughxOES
         1420, // glPixelMapx
         1423, // glPixelStorex
         1429, // glPixelTransferxOES
         1434, // glPixelZoomxOES
         1448, // glPointParameterxvOES
         1450, // glPointSizexOES
         1458, // glPolygonOffsetxOES
         1468, // glPrioritizeTexturesxOES
         1660, // glRasterPos2xOES
         1661, // glRasterPos2xvOES
         1662, // glRasterPos3xOES
         1663, // glRasterPos3xvOES
         1664, // glRasterPos4xOES
         1665, // glRasterPos4xvOES
         1672, // glRectxOES
         1673, // glRectxvOES
         1715, // glRotatexOES
         1731, // glScalexOES
         1845, // glTexCoord1xOES
         1846, // glTexCoord1xvOES
         1861, // glTexCoord2xOES
         1862, // glTexCoord2xvOES
         1867, // glTexCoord3xOES
         1868, // glTexCoord3xvOES
         1877, // glTexCoord4xOES
         1878, // glTexCoord4xvOES
         1883, // glTexEnvxOES
         1884, // glTexEnvxvOES
         1886, // glTexGenxOES
         1887, // glTexGenxvOES
         1908, // glTexParameterxOES
         1909, // glTexParameterxvOES
         2002, // glTranslatexOES
         2162, // glVertex2xOES
         2163, // glVertex2xvOES
         2168, // glVertex3xOES
         2169, // glVertex3xvOES
         2174, // glVertex4xOES
         2175  // glVertex4xvOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_query_matrix(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_query_matrix) return;
    static const uint16_t s_pfnIdx[] = {
         1656  // glQueryMatrixxOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_single_precision(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_single_precision) return;
    static const uint16_t s_pfnIdx[] = {
          166, // glClearDepthfOES
          185, // glClipPlanefOES
          392, // glDepthRangefOES
          570, // glFrustumfOES
          637, // glGetClipPlanefOES
         1391  // glOrthofOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OVR_multiview(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OVR_multiview) return;
    static const uint16_t s_pfnIdx[] = {
          567  // glFramebufferTextureMultiviewOVR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_PGI_misc_hints(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->PGI_misc_hints) return;
    static const uint16_t s_pfnIdx[] = {
         1014  // glHintPGI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_detail_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIS_detail_texture) return;
    static const uint16_t s_pfnIdx[] = {
          396, // glDetailTexFuncSGIS
          665  // glGetDetailTexFuncSGIS
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_fog_function(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIS_fog_function) return;
    static const uint16_t s_pfnIdx[] = {
          523, // glFogFuncSGIS
          680  // glGetFogFuncSGIS
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIS_multisample) return;
    static const uint16_t s_pfnIdx[] = {
         1721, // glSampleMaskSGIS
         1724  // glSamplePatternSGIS
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_pixel_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIS_pixel_texture) return;
    static const uint16_t s_pfnIdx[] = {
          806, // glGetPixelTexGenParameterfvSGIS
          807, // glGetPixelTexGenParameterivSGIS
         1424, // glPixelTexGenParameterfSGIS
         1425, // glPixelTexGenParameterfvSGIS
         1426, // glPixelTexGenParameteriSGIS
         1427  // glPixelTexGenParameterivSGIS
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_point_parameters(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIS_point_parameters) return;
    static const uint16_t s_pfnIdx[] = {
         1439, // glPointParameterfSGIS
         1443  // glPointParameterfvSGIS
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_sharpen_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIS_sharpen_texture) return;
    static const uint16_t s_pfnIdx[] = {
          875, // glGetSharpenTexFuncSGIS
         1780  // glSharpenTexFuncSGIS
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_texture4D(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIS_texture4D) return;
    static const uint16_t s_pfnIdx[] = {
         1897, // glTexImage4DSGIS
         1935  // glTexSubImage4DSGIS
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_texture_color_mask(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIS_texture_color_mask) return;
    static const uint16_t s_pfnIdx[] = {
         1943  // glTextureColorMaskSGIS
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_texture_filter4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIS_texture_filter4) return;
    static const uint16_t s_pfnIdx[] = {
          885, // glGetTexFilterFuncSGIS
         1885  // glTexFilterFuncSGIS
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_async(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_async) return;
    static const uint16_t s_pfnIdx[] = {
           21, // glAsyncMarkerSGIX
          343, // glDeleteAsyncMarkersSGIX
          499, // glFinishAsyncSGIX
          572, // glGenAsyncMarkersSGIX
         1050, // glIsAsyncMarkerSGIX
         1451  // glPollAsyncSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_flush_raster(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_flush_raster) return;
    static const uint16_t s_pfnIdx[] = {
          510  // glFlushRasterSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_fragment_lighting(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_fragment_lighting) return;
    static const uint16_t s_pfnIdx[] = {
          526, // glFragmentColorMaterialSGIX
          528, // glFragmentLightModelfSGIX
          529, // glFragmentLightModelfvSGIX
          530, // glFragmentLightModeliSGIX
          531, // glFragmentLightModelivSGIX
          532, // glFragmentLightfSGIX
          533, // glFragmentLightfvSGIX
          534, // glFragmentLightiSGIX
          535, // glFragmentLightivSGIX
          536, // glFragmentMaterialfSGIX
          537, // glFragmentMaterialfvSGIX
          538, // glFragmentMaterialiSGIX
          539, // glFragmentMaterialivSGIX
          684, // glGetFragmentLightfvSGIX
          685, // glGetFragmentLightivSGIX
          686, // glGetFragmentMaterialfvSGIX
          687, // glGetFragmentMaterialivSGIX
         1100  // glLightEnviSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_framezoom(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_framezoom) return;
    static const uint16_t s_pfnIdx[] = {
          541  // glFrameZoomSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_igloo_interface(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_igloo_interface) return;
    static const uint16_t s_pfnIdx[] = {
         1016  // glIglooInterfaceSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_instruments(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_instruments) return;
    static const uint16_t s_pfnIdx[] = {
          706, // glGetInstrumentsSGIX
         1039, // glInstrumentsBufferSGIX
         1452, // glPollInstrumentsSGIX
         1668, // glReadInstrumentsSGIX
         1791, // glStartInstrumentsSGIX
         1811  // glStopInstrumentsSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_list_priority(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_list_priority) return;
    static const uint16_t s_pfnIdx[] = {
          721, // glGetListParameterfvSGIX
          722, // glGetListParameterivSGIX
         1110, // glListParameterfSGIX
         1111, // glListParameterfvSGIX
         1112, // glListParameteriSGIX
         1113  // glListParameterivSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_pixel_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_pixel_texture) return;
    static const uint16_t s_pfnIdx[] = {
         1428  // glPixelTexGenSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_polynomial_ffd(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_polynomial_ffd) return;
    static const uint16_t s_pfnIdx[] = {
          340, // glDeformSGIX
          341, // glDeformationMap3dSGIX
          342, // glDeformationMap3fSGIX
         1114  // glLoadIdentityDeformationMapSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_reference_plane(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_reference_plane) return;
    static const uint16_t s_pfnIdx[] = {
         1674  // glReferencePlaneSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_sprite(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_sprite) return;
    static const uint16_t s_pfnIdx[] = {
         1787, // glSpriteParameterfSGIX
         1788, // glSpriteParameterfvSGIX
         1789, // glSpriteParameteriSGIX
         1790  // glSpriteParameterivSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_tag_sample_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGIX_tag_sample_buffer) return;
    static const uint16_t s_pfnIdx[] = {
         1816  // glTagSampleBufferSGIX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGI_color_table(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SGI_color_table) return;
    static const uint16_t s_pfnIdx[] = {
          215, // glColorTableParameterfvSGI
          216, // glColorTableParameterivSGI
          217, // glColorTableSGI
          269, // glCopyColorTableSGI
          641, // glGetColorTableParameterfvSGI
          643, // glGetColorTableParameterivSGI
          644  // glGetColorTableSGI
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SUNX_constant_data(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SUNX_constant_data) return;
    static const uint16_t s_pfnIdx[] = {
          503  // glFinishTextureSUNX
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SUN_global_alpha(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SUN_global_alpha) return;
    static const uint16_t s_pfnIdx[] = {
         1005, // glGlobalAlphaFactorbSUN
         1006, // glGlobalAlphaFactordSUN
         1007, // glGlobalAlphaFactorfSUN
         1008, // glGlobalAlphaFactoriSUN
         1009, // glGlobalAlphaFactorsSUN
         1010, // glGlobalAlphaFactorubSUN
         1011, // glGlobalAlphaFactoruiSUN
         1012  // glGlobalAlphaFactorusSUN
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SUN_mesh_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SUN_mesh_array) return;
    static const uint16_t s_pfnIdx[] = {
          438  // glDrawMeshArraysSUN
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SUN_triangle_list(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SUN_triangle_list) return;
    static const uint16_t s_pfnIdx[] = {
         1684, // glReplacementCodePointerSUN
         1685, // glReplacementCodeubSUN
         1686, // glReplacementCodeubvSUN
         1695, // glReplacementCodeuiSUN
         1704, // glReplacementCodeuivSUN
         1705, // glReplacementCodeusSUN
         1706  // glReplacementCodeusvSUN
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SUN_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->SUN_vertex) return;
    static const uint16_t s_pfnIdx[] = {
          187, // glColor3fVertex3fSUN
          188, // glColor3fVertex3fvSUN
          193, // glColor4fNormal3fVertex3fSUN
          194, // glColor4fNormal3fVertex3fvSUN
          197, // glColor4ubVertex2fSUN
          198, // glColor4ubVertex2fvSUN
          199, // glColor4ubVertex3fSUN
          200, // glColor4ubVertex3fvSUN
         1367, // glNormal3fVertex3fSUN
         1368, // glNormal3fVertex3fvSUN
         1687, // glReplacementCodeuiColor3fVertex3fSUN
         1688, // glReplacementCodeuiColor3fVertex3fvSUN
         1689, // glReplacementCodeuiColor4fNormal3fVertex3fSUN
         1690, // glReplacementCodeuiColor4fNormal3fVertex3fvSUN
         1691, // glReplacementCodeuiColor4ubVertex3fSUN
         1692, // glReplacementCodeuiColor4ubVertex3fvSUN
         1693, // glReplacementCodeuiNormal3fVertex3fSUN
         1694, // glReplacementCodeuiNormal3fVertex3fvSUN
         1696, // glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN
         1697, // glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN
         1698, // glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN
         1699, // glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN
         1700, // glReplacementCodeuiTexCoord2fVertex3fSUN
         1701, // glReplacementCodeuiTexCoord2fVertex3fvSUN
         1702, // glReplacementCodeuiVertex3fSUN
         1703, // glReplacementCodeuiVertex3fvSUN
         1849, // glTexCoord2fColor3fVertex3fSUN
         1850, // glTexCoord2fColor3fVertex3fvSUN
         1851, // glTexCoord2fColor4fNormal3fVertex3fSUN
         1852, // glTexCoord2fColor4fNormal3fVertex3fvSUN
         1853, // glTexCoord2fColor4ubVertex3fSUN
         1854, // glTexCoord2fColor4ubVertex3fvSUN
         1855, // glTexCoord2fNormal3fVertex3fSUN
         1856, // glTexCoord2fNormal3fVertex3fvSUN
         1857, // glTexCoord2fVertex3fSUN
         1858, // glTexCoord2fVertex3fvSUN
         1871, // glTexCoord4fColor4fNormal3fVertex4fSUN
         1872, // glTexCoord4fColor4fNormal3fVertex4fvSUN
         1873, // glTexCoord4fVertex4fSUN
         1874  // glTexCoord4fVertex4fvSUN
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_base_vertex_base_instance(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_base_vertex_base_instance) return;
    static const uint16_t s_pfnIdx[] = {
         2606, // glDrawArraysInstancedBaseInstanceANGLE
         2616, // glDrawElementsInstancedBaseVertexBaseInstanceANGLE
         2782, // glMultiDrawArraysInstancedBaseInstanceANGLE
         2787  // glMultiDrawElementsInstancedBaseVertexBaseInstanceANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_copy_texture_3d(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_copy_texture_3d) return;
    static const uint16_t s_pfnIdx[] = {
         2578, // glCopySubTexture3DANGLE
         2581  // glCopyTexture3DANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_framebuffer_blit(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_framebuffer_blit) return;
    static const uint16_t s_pfnIdx[] = {
         2558  // glBlitFramebufferANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_framebuffer_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_framebuffer_multisample) return;
    static const uint16_t s_pfnIdx[] = {
         2812  // glRenderbufferStorageMultisampleANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_get_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_get_image) return;
    static const uint16_t s_pfnIdx[] = {
         2678, // glGetCompressedTexImageANGLE
         2724, // glGetRenderbufferImageANGLE
         2736  // glGetTexImageANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_get_tex_level_parameter(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_get_tex_level_parameter) return;
    static const uint16_t s_pfnIdx[] = {
         2737, // glGetTexLevelParameterfvANGLE
         2739  // glGetTexLevelParameterivANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_instanced_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_instanced_arrays) return;
    static const uint16_t s_pfnIdx[] = {
         2605, // glDrawArraysInstancedANGLE
         2614, // glDrawElementsInstancedANGLE
         2873  // glVertexAttribDivisorANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_logic_op(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_logic_op) return;
    static const uint16_t s_pfnIdx[] = {
         2773  // glLogicOpANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_multi_draw(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_multi_draw) return;
    static const uint16_t s_pfnIdx[] = {
         2779, // glMultiDrawArraysANGLE
         2781, // glMultiDrawArraysInstancedANGLE
         2783, // glMultiDrawElementsANGLE
         2786  // glMultiDrawElementsInstancedANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_polygon_mode(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_polygon_mode) return;
    static const uint16_t s_pfnIdx[] = {
         2793  // glPolygonModeANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_provoking_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_provoking_vertex) return;
    static const uint16_t s_pfnIdx[] = {
         2802  // glProvokingVertexANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_request_extension(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_request_extension) return;
    static const uint16_t s_pfnIdx[] = {
         2600, // glDisableExtensionANGLE
         2816  // glRequestExtensionANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_robust_client_memory(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_robust_client_memory) return;
    static const uint16_t s_pfnIdx[] = {
         2569, // glCompressedTexImage2DRobustANGLE
         2571, // glCompressedTexImage3DRobustANGLE
         2572, // glCompressedTexSubImage2DRobustANGLE
         2574, // glCompressedTexSubImage3DRobustANGLE
         2671, // glGetActiveUniformBlockivRobustANGLE
         2672, // glGetBooleani_vRobustANGLE
         2673, // glGetBooleanvRobustANGLE
         2674, // glGetBufferParameteri64vRobustANGLE
         2675, // glGetBufferParameterivRobustANGLE
         2677, // glGetBufferPointervRobustANGLE
         2684, // glGetFloatvRobustANGLE
         2687, // glGetFramebufferAttachmentParameterivRobustANGLE
         2688, // glGetFramebufferParameterivRobustANGLE
         2696, // glGetInteger64i_vRobustANGLE
         2699, // glGetInteger64vRobustANGLE
         2701, // glGetIntegeri_vRobustANGLE
         2702, // glGetIntegervRobustANGLE
         2703, // glGetInternalformativRobustANGLE
         2705, // glGetMultisamplefvRobustANGLE
         2709, // glGetPointervRobustANGLERobustANGLE
         2711, // glGetProgramInterfaceivRobustANGLE
         2715, // glGetProgramivRobustANGLE
         2716, // glGetQueryObjecti64vRobustANGLE
         2718, // glGetQueryObjectivRobustANGLE
         2719, // glGetQueryObjectui64vRobustANGLE
         2721, // glGetQueryObjectuivRobustANGLE
         2723, // glGetQueryivRobustANGLE
         2725, // glGetRenderbufferParameterivRobustANGLE
         2728, // glGetSamplerParameterIivRobustANGLE
         2731, // glGetSamplerParameterIuivRobustANGLE
         2732, // glGetSamplerParameterfvRobustANGLE
         2733, // glGetSamplerParameterivRobustANGLE
         2734, // glGetShaderivRobustANGLE
         2738, // glGetTexLevelParameterfvRobustANGLE
         2740, // glGetTexLevelParameterivRobustANGLE
         2742, // glGetTexParameterIivRobustANGLE
         2744, // glGetTexParameterIuivRobustANGLE
         2745, // glGetTexParameterfvRobustANGLE
         2746, // glGetTexParameterivRobustANGLE
         2750, // glGetUniformfvRobustANGLE
         2751, // glGetUniformivRobustANGLE
         2752, // glGetUniformuivRobustANGLE
         2753, // glGetVertexAttribIivRobustANGLE
         2754, // glGetVertexAttribIuivRobustANGLE
         2755, // glGetVertexAttribPointervRobustANGLE
         2756, // glGetVertexAttribfvRobustANGLE
         2757, // glGetVertexAttribivRobustANGLE
         2760, // glGetnUniformfvRobustANGLE
         2763, // glGetnUniformivRobustANGLE
         2765, // glGetnUniformuivRobustANGLE
         2807, // glReadPixelsRobustANGLE
         2810, // glReadnPixelsRobustANGLE
         2821, // glSamplerParameterIivRobustANGLE
         2824, // glSamplerParameterIuivRobustANGLE
         2825, // glSamplerParameterfvRobustANGLE
         2826, // glSamplerParameterivRobustANGLE
         2842, // glTexImage2DRobustANGLE
         2844, // glTexImage3DRobustANGLE
         2847, // glTexParameterIivRobustANGLE
         2849, // glTexParameterIuivRobustANGLE
         2850, // glTexParameterfvRobustANGLE
         2851, // glTexParameterivRobustANGLE
         2856, // glTexSubImage2DRobustANGLE
         2858  // glTexSubImage3DRobustANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_shader_pixel_local_storage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_shader_pixel_local_storage) return;
    static const uint16_t s_pfnIdx[] = {
         2543, // glBeginPixelLocalStorageANGLE
         2631, // glEndPixelLocalStorageANGLE
         2652, // glFramebufferMemorylessPixelLocalStorageANGLE
         2653, // glFramebufferPixelLocalClearValuefvANGLE
         2654, // glFramebufferPixelLocalClearValueivANGLE
         2655, // glFramebufferPixelLocalClearValueuivANGLE
         2656, // glFramebufferPixelLocalStorageInterruptANGLE
         2657, // glFramebufferPixelLocalStorageRestoreANGLE
         2667, // glFramebufferTexturePixelLocalStorageANGLE
         2689, // glGetFramebufferPixelLocalStorageParameterfvANGLE
         2690, // glGetFramebufferPixelLocalStorageParameterfvRobustANGLE
         2691, // glGetFramebufferPixelLocalStorageParameterivANGLE
         2692, // glGetFramebufferPixelLocalStorageParameterivRobustANGLE
         2792  // glPixelLocalStorageBarrierANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_texture_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_texture_multisample) return;
    static const uint16_t s_pfnIdx[] = {
         2704, // glGetMultisamplefvANGLE
         2737, // glGetTexLevelParameterfvANGLE
         2739, // glGetTexLevelParameterivANGLE
         2818, // glSampleMaskiANGLE
         2852  // glTexStorage2DMultisampleANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_translated_shader_source(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_translated_shader_source) return;
    static const uint16_t s_pfnIdx[] = {
         2749  // glGetTranslatedShaderSourceANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_vulkan_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ANGLE_vulkan_image) return;
    static const uint16_t s_pfnIdx[] = {
         2540, // glAcquireTexturesANGLE
         2811  // glReleaseTexturesANGLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_copy_texture_levels(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->APPLE_copy_texture_levels) return;
    static const uint16_t s_pfnIdx[] = {
         2583  // glCopyTextureLevelsAPPLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_framebuffer_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->APPLE_framebuffer_multisample) return;
    static const uint16_t s_pfnIdx[] = {
         2813, // glRenderbufferStorageMultisampleAPPLE
         2817  // glResolveMultisampleFramebufferAPPLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_sync(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->APPLE_sync) return;
    static const uint16_t s_pfnIdx[] = {
         2564, // glClientWaitSyncAPPLE
         2593, // glDeleteSyncAPPLE
         2647, // glFenceSyncAPPLE
         2697, // glGetInteger64vAPPLE
         2735, // glGetSyncivAPPLE
         2771, // glIsSyncAPPLE
         2882  // glWaitSyncAPPLE
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARM_shader_core_properties(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->ARM_shader_core_properties) return;
    static const uint16_t s_pfnIdx[] = {
         2777  // glMaxActiveShaderCoresARM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_CHROMIUM_bind_uniform_location(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->CHROMIUM_bind_uniform_location) return;
    static const uint16_t s_pfnIdx[] = {
         2547  // glBindUniformLocationCHROMIUM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_CHROMIUM_copy_compressed_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->CHROMIUM_copy_compressed_texture) return;
    static const uint16_t s_pfnIdx[] = {
         2568  // glCompressedCopyTextureCHROMIUM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_CHROMIUM_copy_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->CHROMIUM_copy_texture) return;
    static const uint16_t s_pfnIdx[] = {
         2579, // glCopySubTextureCHROMIUM
         2582  // glCopyTextureCHROMIUM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_CHROMIUM_framebuffer_mixed_samples(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->CHROMIUM_framebuffer_mixed_samples) return;
    static const uint16_t s_pfnIdx[] = {
         2585  // glCoverageModulationCHROMIUM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_CHROMIUM_lose_context(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->CHROMIUM_lose_context) return;
    static const uint16_t s_pfnIdx[] = {
         2774  // glLoseContextCHROMIUM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_base_instance(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_base_instance) return;
    static const uint16_t s_pfnIdx[] = {
         2607, // glDrawArraysInstancedBaseInstanceEXT
         2615, // glDrawElementsInstancedBaseInstanceEXT
         2617  // glDrawElementsInstancedBaseVertexBaseInstanceEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_blend_func_extended(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_blend_func_extended) return;
    static const uint16_t s_pfnIdx[] = {
           54, // glBindFragDataLocationEXT
         2545, // glBindFragDataLocationIndexedEXT
         2685, // glGetFragDataIndexEXT
         2714  // glGetProgramResourceLocationIndexEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_buffer_storage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_buffer_storage) return;
    static const uint16_t s_pfnIdx[] = {
         2560  // glBufferStorageEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_clear_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_clear_texture) return;
    static const uint16_t s_pfnIdx[] = {
         2562, // glClearTexImageEXT
         2563  // glClearTexSubImageEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_clip_control(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_clip_control) return;
    static const uint16_t s_pfnIdx[] = {
         2565  // glClipControlEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_copy_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_copy_image) return;
    static const uint16_t s_pfnIdx[] = {
         2576  // glCopyImageSubDataEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_discard_framebuffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_discard_framebuffer) return;
    static const uint16_t s_pfnIdx[] = {
         2604  // glDiscardFramebufferEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_disjoint_timer_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_disjoint_timer_query) return;
    static const uint16_t s_pfnIdx[] = {
         2544, // glBeginQueryEXT
         2592, // glDeleteQueriesEXT
         2632, // glEndQueryEXT
         2669, // glGenQueriesEXT
         2698, // glGetInteger64vEXT
          850, // glGetQueryObjecti64vEXT
         2717, // glGetQueryObjectivEXT
          854, // glGetQueryObjectui64vEXT
         2720, // glGetQueryObjectuivEXT
         2722, // glGetQueryivEXT
         2770, // glIsQueryEXT
         2804  // glQueryCounterEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_draw_buffers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_draw_buffers) return;
    static const uint16_t s_pfnIdx[] = {
         2609  // glDrawBuffersEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_draw_buffers_indexed(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_draw_buffers_indexed) return;
    static const uint16_t s_pfnIdx[] = {
         2550, // glBlendEquationSeparateiEXT
         2552, // glBlendEquationiEXT
         2554, // glBlendFuncSeparateiEXT
         2556, // glBlendFunciEXT
         2566, // glColorMaskiEXT
         2601, // glDisableiEXT
         2628, // glEnableiEXT
         2766  // glIsEnablediEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_draw_elements_base_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_draw_elements_base_vertex) return;
    static const uint16_t s_pfnIdx[] = {
         2612, // glDrawElementsBaseVertexEXT
         2618, // glDrawElementsInstancedBaseVertexEXT
         2621, // glDrawRangeElementsBaseVertexEXT
         2784  // glMultiDrawElementsBaseVertexEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_draw_transform_feedback(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_draw_transform_feedback) return;
    static const uint16_t s_pfnIdx[] = {
         2623, // glDrawTransformFeedbackEXT
         2624  // glDrawTransformFeedbackInstancedEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_fragment_shading_rate(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_fragment_shading_rate) return;
    static const uint16_t s_pfnIdx[] = {
         2659, // glFramebufferShadingRateEXT
         2686, // glGetFragmentShadingRatesEXT
         2833, // glShadingRateCombinerOpsEXT
         2834  // glShadingRateEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_geometry_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_geometry_shader) return;
    static const uint16_t s_pfnIdx[] = {
          561  // glFramebufferTextureEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_instanced_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_instanced_arrays) return;
    static const uint16_t s_pfnIdx[] = {
          418, // glDrawArraysInstancedEXT
          437, // glDrawElementsInstancedEXT
         2874  // glVertexAttribDivisorEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_map_buffer_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_map_buffer_range) return;
    static const uint16_t s_pfnIdx[] = {
         2648, // glFlushMappedBufferRangeEXT
         2776  // glMapBufferRangeEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_multi_draw_indirect(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_multi_draw_indirect) return;
    static const uint16_t s_pfnIdx[] = {
         2780, // glMultiDrawArraysIndirectEXT
         2785  // glMultiDrawElementsIndirectEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_multisampled_render_to_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_multisampled_render_to_texture) return;
    static const uint16_t s_pfnIdx[] = {
         2661, // glFramebufferTexture2DMultisampleEXT
         1683  // glRenderbufferStorageMultisampleEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_multiview_draw_buffers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_multiview_draw_buffers) return;
    static const uint16_t s_pfnIdx[] = {
         2610, // glDrawBuffersIndexedEXT
         2700, // glGetIntegeri_vEXT
         2805  // glReadBufferIndexedEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_occlusion_query_boolean(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_occlusion_query_boolean) return;
    static const uint16_t s_pfnIdx[] = {
         2544, // glBeginQueryEXT
         2592, // glDeleteQueriesEXT
         2632, // glEndQueryEXT
         2669, // glGenQueriesEXT
         2720, // glGetQueryObjectuivEXT
         2722, // glGetQueryivEXT
         2770  // glIsQueryEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_primitive_bounding_box(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_primitive_bounding_box) return;
    static const uint16_t s_pfnIdx[] = {
         2797  // glPrimitiveBoundingBoxEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_robustness(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_robustness) return;
    static const uint16_t s_pfnIdx[] = {
         2694, // glGetGraphicsResetStatusEXT
         2758, // glGetnUniformfvEXT
         2761, // glGetnUniformivEXT
         2808  // glReadnPixelsEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_shader_pixel_local_storage2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_shader_pixel_local_storage2) return;
    static const uint16_t s_pfnIdx[] = {
         2561, // glClearPixelLocalStorageuiEXT
         2658, // glFramebufferPixelLocalStorageSizeEXT
         2693  // glGetFramebufferPixelLocalStorageSizeEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_sparse_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_sparse_texture) return;
    static const uint16_t s_pfnIdx[] = {
         2845  // glTexPageCommitmentEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_tessellation_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_tessellation_shader) return;
    static const uint16_t s_pfnIdx[] = {
         2790  // glPatchParameteriEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_border_clamp(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_texture_border_clamp) return;
    static const uint16_t s_pfnIdx[] = {
         2726, // glGetSamplerParameterIivEXT
         2729, // glGetSamplerParameterIuivEXT
          892, // glGetTexParameterIivEXT
          894, // glGetTexParameterIuivEXT
         2819, // glSamplerParameterIivEXT
         2822, // glSamplerParameterIuivEXT
         1901, // glTexParameterIivEXT
         1903  // glTexParameterIuivEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_texture_buffer) return;
    static const uint16_t s_pfnIdx[] = {
         1837, // glTexBufferEXT
         2838  // glTexBufferRangeEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_storage_compression(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_texture_storage_compression) return;
    static const uint16_t s_pfnIdx[] = {
         2854, // glTexStorageAttribs2DEXT
         2855  // glTexStorageAttribs3DEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_view(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->EXT_texture_view) return;
    static const uint16_t s_pfnIdx[] = {
         2860  // glTextureViewEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_IMG_bindless_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->IMG_bindless_texture) return;
    static const uint16_t s_pfnIdx[] = {
         2747, // glGetTextureHandleIMG
         2748, // glGetTextureSamplerHandleIMG
         2800, // glProgramUniformHandleui64IMG
         2801, // glProgramUniformHandleui64vIMG
         2862, // glUniformHandleui64IMG
         2863  // glUniformHandleui64vIMG
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_IMG_framebuffer_downsample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->IMG_framebuffer_downsample) return;
    static const uint16_t s_pfnIdx[] = {
         2660, // glFramebufferTexture2DDownsampleIMG
         2664  // glFramebufferTextureLayerDownsampleIMG
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_IMG_multisampled_render_to_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->IMG_multisampled_render_to_texture) return;
    static const uint16_t s_pfnIdx[] = {
         2662, // glFramebufferTexture2DMultisampleIMG
         2814  // glRenderbufferStorageMultisampleIMG
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_MESA_sampler_objects(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->MESA_sampler_objects) return;
    static const uint16_t s_pfnIdx[] = {
           71, // glBindSampler
          369, // glDeleteSamplers
          592, // glGenSamplers
          863, // glGetSamplerParameterfv
          864, // glGetSamplerParameteriv
         1081, // glIsSampler
         1727, // glSamplerParameterf
         1728, // glSamplerParameterfv
         1729, // glSamplerParameteri
         1730  // glSamplerParameteriv
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_copy_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_copy_buffer) return;
    static const uint16_t s_pfnIdx[] = {
         2575  // glCopyBufferSubDataNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_coverage_sample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_coverage_sample) return;
    static const uint16_t s_pfnIdx[] = {
         2584, // glCoverageMaskNV
         2586  // glCoverageOperationNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_draw_buffers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_draw_buffers) return;
    static const uint16_t s_pfnIdx[] = {
         2611  // glDrawBuffersNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_draw_instanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_draw_instanced) return;
    static const uint16_t s_pfnIdx[] = {
         2608, // glDrawArraysInstancedNV
         2620  // glDrawElementsInstancedNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_framebuffer_blit(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_framebuffer_blit) return;
    static const uint16_t s_pfnIdx[] = {
         2559  // glBlitFramebufferNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_framebuffer_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_framebuffer_multisample) return;
    static const uint16_t s_pfnIdx[] = {
         2815  // glRenderbufferStorageMultisampleNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_instanced_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_instanced_arrays) return;
    static const uint16_t s_pfnIdx[] = {
         2875  // glVertexAttribDivisorNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_non_square_matrices(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_non_square_matrices) return;
    static const uint16_t s_pfnIdx[] = {
         2864, // glUniformMatrix2x3fvNV
         2865, // glUniformMatrix2x4fvNV
         2866, // glUniformMatrix3x2fvNV
         2867, // glUniformMatrix3x4fvNV
         2868, // glUniformMatrix4x2fvNV
         2869  // glUniformMatrix4x3fvNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_polygon_mode(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_polygon_mode) return;
    static const uint16_t s_pfnIdx[] = {
         2794  // glPolygonModeNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_read_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_read_buffer) return;
    static const uint16_t s_pfnIdx[] = {
         2806  // glReadBufferNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_viewport_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->NV_viewport_array) return;
    static const uint16_t s_pfnIdx[] = {
         2595, // glDepthRangeArrayfvNV
         2597, // glDepthRangeIndexedfNV
         2602, // glDisableiNV
         2629, // glEnableiNV
         2682, // glGetFloati_vNV
         2767, // glIsEnablediNV
         2827, // glScissorArrayvNV
         2829, // glScissorIndexedNV
         2831, // glScissorIndexedvNV
         2876, // glViewportArrayvNV
         2878, // glViewportIndexedfNV
         2880  // glViewportIndexedfvNV
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_EGL_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_EGL_image) return;
    static const uint16_t s_pfnIdx[] = {
         2625, // glEGLImageTargetRenderbufferStorageOES
         2626  // glEGLImageTargetTexture2DOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_copy_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_copy_image) return;
    static const uint16_t s_pfnIdx[] = {
         2577  // glCopyImageSubDataOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_draw_buffers_indexed(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_draw_buffers_indexed) return;
    static const uint16_t s_pfnIdx[] = {
         2551, // glBlendEquationSeparateiOES
         2553, // glBlendEquationiOES
         2555, // glBlendFuncSeparateiOES
         2557, // glBlendFunciOES
         2567, // glColorMaskiOES
         2603, // glDisableiOES
         2630, // glEnableiOES
         2768  // glIsEnablediOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_draw_elements_base_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_draw_elements_base_vertex) return;
    static const uint16_t s_pfnIdx[] = {
         2613, // glDrawElementsBaseVertexOES
         2619, // glDrawElementsInstancedBaseVertexOES
         2622, // glDrawRangeElementsBaseVertexOES
         2784  // glMultiDrawElementsBaseVertexEXT
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_geometry_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_geometry_shader) return;
    static const uint16_t s_pfnIdx[] = {
         2666  // glFramebufferTextureOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_get_program_binary(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_get_program_binary) return;
    static const uint16_t s_pfnIdx[] = {
         2710, // glGetProgramBinaryOES
         2799  // glProgramBinaryOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_mapbuffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_mapbuffer) return;
    static const uint16_t s_pfnIdx[] = {
         2676, // glGetBufferPointervOES
         2775, // glMapBufferOES
         2870  // glUnmapBufferOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_primitive_bounding_box(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_primitive_bounding_box) return;
    static const uint16_t s_pfnIdx[] = {
         2798  // glPrimitiveBoundingBoxOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_sample_shading(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_sample_shading) return;
    static const uint16_t s_pfnIdx[] = {
         2778  // glMinSampleShadingOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_tessellation_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_tessellation_shader) return;
    static const uint16_t s_pfnIdx[] = {
         2791  // glPatchParameteriOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_texture_3D(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_texture_3D) return;
    static const uint16_t s_pfnIdx[] = {
         2570, // glCompressedTexImage3DOES
         2573, // glCompressedTexSubImage3DOES
         2580, // glCopyTexSubImage3DOES
         2663, // glFramebufferTexture3DOES
         2843, // glTexImage3DOES
         2857  // glTexSubImage3DOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_texture_border_clamp(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_texture_border_clamp) return;
    static const uint16_t s_pfnIdx[] = {
         2727, // glGetSamplerParameterIivOES
         2730, // glGetSamplerParameterIuivOES
         2741, // glGetTexParameterIivOES
         2743, // glGetTexParameterIuivOES
         2820, // glSamplerParameterIivOES
         2823, // glSamplerParameterIuivOES
         2846, // glTexParameterIivOES
         2848  // glTexParameterIuivOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_texture_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_texture_buffer) return;
    static const uint16_t s_pfnIdx[] = {
         2837, // glTexBufferOES
         2839  // glTexBufferRangeOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_texture_storage_multisample_2d_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_texture_storage_multisample_2d_array) return;
    static const uint16_t s_pfnIdx[] = {
         2853  // glTexStorage3DMultisampleOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_texture_view(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_texture_view) return;
    static const uint16_t s_pfnIdx[] = {
         2861  // glTextureViewOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_vertex_array_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_vertex_array_object) return;
    static const uint16_t s_pfnIdx[] = {
         2548, // glBindVertexArrayOES
         2594, // glDeleteVertexArraysOES
         2670, // glGenVertexArraysOES
         2772  // glIsVertexArrayOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_viewport_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OES_viewport_array) return;
    static const uint16_t s_pfnIdx[] = {
         2596, // glDepthRangeArrayfvOES
         2598, // glDepthRangeIndexedfOES
         2603, // glDisableiOES
         2630, // glEnableiOES
         2683, // glGetFloati_vOES
         2768, // glIsEnablediOES
         2828, // glScissorArrayvOES
         2830, // glScissorIndexedOES
         2832, // glScissorIndexedvOES
         2877, // glViewportArrayvOES
         2879, // glViewportIndexedfOES
         2881  // glViewportIndexedfvOES
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OVR_multiview_multisampled_render_to_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->OVR_multiview_multisampled_render_to_texture) return;
    static const uint16_t s_pfnIdx[] = {
         2665  // glFramebufferTextureMultisampleMultiviewOVR
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_alpha_test(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_alpha_test) return;
    static const uint16_t s_pfnIdx[] = {
         2542  // glAlphaFuncQCOM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_driver_control(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_driver_control) return;
    static const uint16_t s_pfnIdx[] = {
         2599, // glDisableDriverControlQCOM
         2627, // glEnableDriverControlQCOM
         2680, // glGetDriverControlStringQCOM
         2681  // glGetDriverControlsQCOM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_extended_get(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_extended_get) return;
    static const uint16_t s_pfnIdx[] = {
         2634, // glExtGetBufferPointervQCOM
         2635, // glExtGetBuffersQCOM
         2636, // glExtGetFramebuffersQCOM
         2639, // glExtGetRenderbuffersQCOM
         2641, // glExtGetTexLevelParameterivQCOM
         2642, // glExtGetTexSubImageQCOM
         2643, // glExtGetTexturesQCOM
         2645  // glExtTexObjectStateOverrideiQCOM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_extended_get2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_extended_get2) return;
    static const uint16_t s_pfnIdx[] = {
         2637, // glExtGetProgramBinarySourceQCOM
         2638, // glExtGetProgramsQCOM
         2640, // glExtGetShadersQCOM
         2644  // glExtIsProgramBinaryQCOM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_frame_extrapolation(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_frame_extrapolation) return;
    static const uint16_t s_pfnIdx[] = {
         2646  // glExtrapolateTex2DQCOM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_framebuffer_foveated(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_framebuffer_foveated) return;
    static const uint16_t s_pfnIdx[] = {
         2650, // glFramebufferFoveationConfigQCOM
         2651  // glFramebufferFoveationParametersQCOM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_motion_estimation(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_motion_estimation) return;
    static const uint16_t s_pfnIdx[] = {
         2840, // glTexEstimateMotionQCOM
         2841  // glTexEstimateMotionRegionsQCOM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_shader_framebuffer_fetch_noncoherent(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_shader_framebuffer_fetch_noncoherent) return;
    static const uint16_t s_pfnIdx[] = {
         2649  // glFramebufferFetchBarrierQCOM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_shading_rate(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_shading_rate) return;
    static const uint16_t s_pfnIdx[] = {
         2835  // glShadingRateQCOM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_texture_foveated(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_texture_foveated) return;
    static const uint16_t s_pfnIdx[] = {
         2859  // glTextureFoveationParametersQCOM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_tiled_rendering(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    if(!context->QCOM_tiled_rendering) return;
    static const uint16_t s_pfnIdx[] = {
         2633, // glEndTilingQCOM
         2836  // glStartTilingQCOM
    };
    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, glad_pfn_names[pfnIdx]);
    }
}

static void glad_gl_resolve_aliases(GladGLContext *context) {
    static const GladAliasPair_t s_aliases[] = {
        {    5,     6 }, // glActiveTexture and glActiveTextureARB
        {    6,     5 }, // glActiveTextureARB and glActiveTexture
        {   22,    23 }, // glAttachObjectARB and glAttachShader
        {   23,    22 }, // glAttachShader and glAttachObjectARB
        {   24,    25 }, // glBeginConditionalRender and glBeginConditionalRenderNV
        {   25,    24 }, // glBeginConditionalRenderNV and glBeginConditionalRender
        {   31,    32 }, // glBeginQuery and glBeginQueryARB
        {   32,    31 }, // glBeginQueryARB and glBeginQuery
        {   34,    35 }, // glBeginTransformFeedback and glBeginTransformFeedbackEXT
        {   34,    36 }, // glBeginTransformFeedback and glBeginTransformFeedbackNV
        {   35,    34 }, // glBeginTransformFeedbackEXT and glBeginTransformFeedback
        {   35,    36 }, // glBeginTransformFeedbackEXT and glBeginTransformFeedbackNV
        {   36,    34 }, // glBeginTransformFeedbackNV and glBeginTransformFeedback
        {   36,    35 }, // glBeginTransformFeedbackNV and glBeginTransformFeedbackEXT
        {   39,    40 }, // glBindAttribLocation and glBindAttribLocationARB
        {   40,    39 }, // glBindAttribLocationARB and glBindAttribLocation
        {   41,    42 }, // glBindBuffer and glBindBufferARB
        {   42,    41 }, // glBindBufferARB and glBindBuffer
        {   43,    44 }, // glBindBufferBase and glBindBufferBaseEXT
        {   43,    45 }, // glBindBufferBase and glBindBufferBaseNV
        {   44,    43 }, // glBindBufferBaseEXT and glBindBufferBase
        {   44,    45 }, // glBindBufferBaseEXT and glBindBufferBaseNV
        {   45,    43 }, // glBindBufferBaseNV and glBindBufferBase
        {   45,    44 }, // glBindBufferBaseNV and glBindBufferBaseEXT
        {   46,    47 }, // glBindBufferOffsetEXT and glBindBufferOffsetNV
        {   47,    46 }, // glBindBufferOffsetNV and glBindBufferOffsetEXT
        {   48,    49 }, // glBindBufferRange and glBindBufferRangeEXT
        {   48,    50 }, // glBindBufferRange and glBindBufferRangeNV
        {   49,    48 }, // glBindBufferRangeEXT and glBindBufferRange
        {   49,    50 }, // glBindBufferRangeEXT and glBindBufferRangeNV
        {   50,    48 }, // glBindBufferRangeNV and glBindBufferRange
        {   50,    49 }, // glBindBufferRangeNV and glBindBufferRangeEXT
        {   53,    54 }, // glBindFragDataLocation and glBindFragDataLocationEXT
        {   54,    53 }, // glBindFragDataLocationEXT and glBindFragDataLocation
        {   55,  2545 }, // glBindFragDataLocationIndexed and glBindFragDataLocationIndexedEXT
        { 2545,    55 }, // glBindFragDataLocationIndexedEXT and glBindFragDataLocationIndexed
        {   66,    67 }, // glBindProgramARB and glBindProgramNV
        {   67,    66 }, // glBindProgramNV and glBindProgramARB
        {   75,    76 }, // glBindTexture and glBindTextureEXT
        {   76,    75 }, // glBindTextureEXT and glBindTexture
        {   82,  2548 }, // glBindVertexArray and glBindVertexArrayOES
        { 2548,    82 }, // glBindVertexArrayOES and glBindVertexArray
        { 2549,   101 }, // glBlendBarrier and glBlendBarrierKHR
        { 2549,   102 }, // glBlendBarrier and glBlendBarrierNV
        {  101,  2549 }, // glBlendBarrierKHR and glBlendBarrier
        {  101,   102 }, // glBlendBarrierKHR and glBlendBarrierNV
        {  102,  2549 }, // glBlendBarrierNV and glBlendBarrier
        {  102,   101 }, // glBlendBarrierNV and glBlendBarrierKHR
        {  103,   104 }, // glBlendColor and glBlendColorEXT
        {  104,   103 }, // glBlendColorEXT and glBlendColor
        {  106,   107 }, // glBlendEquation and glBlendEquationEXT
        {  107,   106 }, // glBlendEquationEXT and glBlendEquation
        {  114,   108 }, // glBlendEquationi and glBlendEquationIndexedAMD
        {  114,   115 }, // glBlendEquationi and glBlendEquationiARB
        {  114,  2552 }, // glBlendEquationi and glBlendEquationiEXT
        {  114,  2553 }, // glBlendEquationi and glBlendEquationiOES
        {  115,   108 }, // glBlendEquationiARB and glBlendEquationIndexedAMD
        {  115,   114 }, // glBlendEquationiARB and glBlendEquationi
        {  115,  2552 }, // glBlendEquationiARB and glBlendEquationiEXT
        {  115,  2553 }, // glBlendEquationiARB and glBlendEquationiOES
        { 2552,   108 }, // glBlendEquationiEXT and glBlendEquationIndexedAMD
        { 2552,   114 }, // glBlendEquationiEXT and glBlendEquationi
        { 2552,   115 }, // glBlendEquationiEXT and glBlendEquationiARB
        { 2552,  2553 }, // glBlendEquationiEXT and glBlendEquationiOES
        {  108,   114 }, // glBlendEquationIndexedAMD and glBlendEquationi
        {  108,   115 }, // glBlendEquationIndexedAMD and glBlendEquationiARB
        {  108,  2552 }, // glBlendEquationIndexedAMD and glBlendEquationiEXT
        {  108,  2553 }, // glBlendEquationIndexedAMD and glBlendEquationiOES
        { 2553,   108 }, // glBlendEquationiOES and glBlendEquationIndexedAMD
        { 2553,   114 }, // glBlendEquationiOES and glBlendEquationi
        { 2553,   115 }, // glBlendEquationiOES and glBlendEquationiARB
        { 2553,  2552 }, // glBlendEquationiOES and glBlendEquationiEXT
        {  109,   110 }, // glBlendEquationSeparate and glBlendEquationSeparateEXT
        {  110,   109 }, // glBlendEquationSeparateEXT and glBlendEquationSeparate
        {  112,   111 }, // glBlendEquationSeparatei and glBlendEquationSeparateIndexedAMD
        {  112,   113 }, // glBlendEquationSeparatei and glBlendEquationSeparateiARB
        {  112,  2550 }, // glBlendEquationSeparatei and glBlendEquationSeparateiEXT
        {  112,  2551 }, // glBlendEquationSeparatei and glBlendEquationSeparateiOES
        {  113,   111 }, // glBlendEquationSeparateiARB and glBlendEquationSeparateIndexedAMD
        {  113,   112 }, // glBlendEquationSeparateiARB and glBlendEquationSeparatei
        {  113,  2550 }, // glBlendEquationSeparateiARB and glBlendEquationSeparateiEXT
        {  113,  2551 }, // glBlendEquationSeparateiARB and glBlendEquationSeparateiOES
        { 2550,   111 }, // glBlendEquationSeparateiEXT and glBlendEquationSeparateIndexedAMD
        { 2550,   112 }, // glBlendEquationSeparateiEXT and glBlendEquationSeparatei
        { 2550,   113 }, // glBlendEquationSeparateiEXT and glBlendEquationSeparateiARB
        { 2550,  2551 }, // glBlendEquationSeparateiEXT and glBlendEquationSeparateiOES
        {  111,   112 }, // glBlendEquationSeparateIndexedAMD and glBlendEquationSeparatei
        {  111,   113 }, // glBlendEquationSeparateIndexedAMD and glBlendEquationSeparateiARB
        {  111,  2550 }, // glBlendEquationSeparateIndexedAMD and glBlendEquationSeparateiEXT
        {  111,  2551 }, // glBlendEquationSeparateIndexedAMD and glBlendEquationSeparateiOES
        { 2551,   111 }, // glBlendEquationSeparateiOES and glBlendEquationSeparateIndexedAMD
        { 2551,   112 }, // glBlendEquationSeparateiOES and glBlendEquationSeparatei
        { 2551,   113 }, // glBlendEquationSeparateiOES and glBlendEquationSeparateiARB
        { 2551,  2550 }, // glBlendEquationSeparateiOES and glBlendEquationSeparateiEXT
        {  124,   117 }, // glBlendFunci and glBlendFuncIndexedAMD
        {  124,   125 }, // glBlendFunci and glBlendFunciARB
        {  124,  2556 }, // glBlendFunci and glBlendFunciEXT
        {  124,  2557 }, // glBlendFunci and glBlendFunciOES
        {  125,   117 }, // glBlendFunciARB and glBlendFuncIndexedAMD
        {  125,   124 }, // glBlendFunciARB and glBlendFunci
        {  125,  2556 }, // glBlendFunciARB and glBlendFunciEXT
        {  125,  2557 }, // glBlendFunciARB and glBlendFunciOES
        { 2556,   117 }, // glBlendFunciEXT and glBlendFuncIndexedAMD
        { 2556,   124 }, // glBlendFunciEXT and glBlendFunci
        { 2556,   125 }, // glBlendFunciEXT and glBlendFunciARB
        { 2556,  2557 }, // glBlendFunciEXT and glBlendFunciOES
        {  117,   124 }, // glBlendFuncIndexedAMD and glBlendFunci
        {  117,   125 }, // glBlendFuncIndexedAMD and glBlendFunciARB
        {  117,  2556 }, // glBlendFuncIndexedAMD and glBlendFunciEXT
        {  117,  2557 }, // glBlendFuncIndexedAMD and glBlendFunciOES
        { 2557,   117 }, // glBlendFunciOES and glBlendFuncIndexedAMD
        { 2557,   124 }, // glBlendFunciOES and glBlendFunci
        { 2557,   125 }, // glBlendFunciOES and glBlendFunciARB
        { 2557,  2556 }, // glBlendFunciOES and glBlendFunciEXT
        {  118,   119 }, // glBlendFuncSeparate and glBlendFuncSeparateEXT
        {  118,   120 }, // glBlendFuncSeparate and glBlendFuncSeparateINGR
        {  119,   118 }, // glBlendFuncSeparateEXT and glBlendFuncSeparate
        {  119,   120 }, // glBlendFuncSeparateEXT and glBlendFuncSeparateINGR
        {  122,   121 }, // glBlendFuncSeparatei and glBlendFuncSeparateIndexedAMD
        {  122,   123 }, // glBlendFuncSeparatei and glBlendFuncSeparateiARB
        {  122,  2554 }, // glBlendFuncSeparatei and glBlendFuncSeparateiEXT
        {  122,  2555 }, // glBlendFuncSeparatei and glBlendFuncSeparateiOES
        {  123,   121 }, // glBlendFuncSeparateiARB and glBlendFuncSeparateIndexedAMD
        {  123,   122 }, // glBlendFuncSeparateiARB and glBlendFuncSeparatei
        {  123,  2554 }, // glBlendFuncSeparateiARB and glBlendFuncSeparateiEXT
        {  123,  2555 }, // glBlendFuncSeparateiARB and glBlendFuncSeparateiOES
        { 2554,   121 }, // glBlendFuncSeparateiEXT and glBlendFuncSeparateIndexedAMD
        { 2554,   122 }, // glBlendFuncSeparateiEXT and glBlendFuncSeparatei
        { 2554,   123 }, // glBlendFuncSeparateiEXT and glBlendFuncSeparateiARB
        { 2554,  2555 }, // glBlendFuncSeparateiEXT and glBlendFuncSeparateiOES
        {  121,   122 }, // glBlendFuncSeparateIndexedAMD and glBlendFuncSeparatei
        {  121,   123 }, // glBlendFuncSeparateIndexedAMD and glBlendFuncSeparateiARB
        {  121,  2554 }, // glBlendFuncSeparateIndexedAMD and glBlendFuncSeparateiEXT
        {  121,  2555 }, // glBlendFuncSeparateIndexedAMD and glBlendFuncSeparateiOES
        {  120,   118 }, // glBlendFuncSeparateINGR and glBlendFuncSeparate
        {  120,   119 }, // glBlendFuncSeparateINGR and glBlendFuncSeparateEXT
        { 2555,   121 }, // glBlendFuncSeparateiOES and glBlendFuncSeparateIndexedAMD
        { 2555,   122 }, // glBlendFuncSeparateiOES and glBlendFuncSeparatei
        { 2555,   123 }, // glBlendFuncSeparateiOES and glBlendFuncSeparateiARB
        { 2555,  2554 }, // glBlendFuncSeparateiOES and glBlendFuncSeparateiEXT
        {  127,   128 }, // glBlitFramebuffer and glBlitFramebufferEXT
        {  127,  2559 }, // glBlitFramebuffer and glBlitFramebufferNV
        {  128,   127 }, // glBlitFramebufferEXT and glBlitFramebuffer
        {  128,  2559 }, // glBlitFramebufferEXT and glBlitFramebufferNV
        { 2559,   127 }, // glBlitFramebufferNV and glBlitFramebuffer
        { 2559,   128 }, // glBlitFramebufferNV and glBlitFramebufferEXT
        {  134,   135 }, // glBufferData and glBufferDataARB
        {  135,   134 }, // glBufferDataARB and glBufferData
        {  139,  2560 }, // glBufferStorage and glBufferStorageEXT
        { 2560,   139 }, // glBufferStorageEXT and glBufferStorage
        {  142,   143 }, // glBufferSubData and glBufferSubDataARB
        {  143,   142 }, // glBufferSubDataARB and glBufferSubData
        {  145,   146 }, // glCheckFramebufferStatus and glCheckFramebufferStatusEXT
        {  146,   145 }, // glCheckFramebufferStatusEXT and glCheckFramebufferStatus
        {  149,   150 }, // glClampColor and glClampColorARB
        {  150,   149 }, // glClampColorARB and glClampColor
        {  165,   166 }, // glClearDepthf and glClearDepthfOES
        {  166,   165 }, // glClearDepthfOES and glClearDepthf
        {  177,  2562 }, // glClearTexImage and glClearTexImageEXT
        { 2562,   177 }, // glClearTexImageEXT and glClearTexImage
        {  178,  2563 }, // glClearTexSubImage and glClearTexSubImageEXT
        { 2563,   178 }, // glClearTexSubImageEXT and glClearTexSubImage
        {  183,  2564 }, // glClientWaitSync and glClientWaitSyncAPPLE
        { 2564,   183 }, // glClientWaitSyncAPPLE and glClientWaitSync
        {  184,  2565 }, // glClipControl and glClipControlEXT
        { 2565,   184 }, // glClipControlEXT and glClipControl
        {  209,   208 }, // glColorMaski and glColorMaskIndexedEXT
        {  209,  2566 }, // glColorMaski and glColorMaskiEXT
        {  209,  2567 }, // glColorMaski and glColorMaskiOES
        { 2566,   208 }, // glColorMaskiEXT and glColorMaskIndexedEXT
        { 2566,   209 }, // glColorMaskiEXT and glColorMaski
        { 2566,  2567 }, // glColorMaskiEXT and glColorMaskiOES
        {  208,   209 }, // glColorMaskIndexedEXT and glColorMaski
        {  208,  2566 }, // glColorMaskIndexedEXT and glColorMaskiEXT
        {  208,  2567 }, // glColorMaskIndexedEXT and glColorMaskiOES
        { 2567,   208 }, // glColorMaskiOES and glColorMaskIndexedEXT
        { 2567,   209 }, // glColorMaskiOES and glColorMaski
        { 2567,  2566 }, // glColorMaskiOES and glColorMaskiEXT
        {  227,   228 }, // glCompileShader and glCompileShaderARB
        {  228,   227 }, // glCompileShaderARB and glCompileShader
        {  236,   237 }, // glCompressedTexImage1D and glCompressedTexImage1DARB
        {  237,   236 }, // glCompressedTexImage1DARB and glCompressedTexImage1D
        {  238,   239 }, // glCompressedTexImage2D and glCompressedTexImage2DARB
        {  239,   238 }, // glCompressedTexImage2DARB and glCompressedTexImage2D
        {  240,   241 }, // glCompressedTexImage3D and glCompressedTexImage3DARB
        {  241,   240 }, // glCompressedTexImage3DARB and glCompressedTexImage3D
        {  242,   243 }, // glCompressedTexSubImage1D and glCompressedTexSubImage1DARB
        {  243,   242 }, // glCompressedTexSubImage1DARB and glCompressedTexSubImage1D
        {  244,   245 }, // glCompressedTexSubImage2D and glCompressedTexSubImage2DARB
        {  245,   244 }, // glCompressedTexSubImage2DARB and glCompressedTexSubImage2D
        {  246,   247 }, // glCompressedTexSubImage3D and glCompressedTexSubImage3DARB
        {  247,   246 }, // glCompressedTexSubImage3DARB and glCompressedTexSubImage3D
        {  267,  2575 }, // glCopyBufferSubData and glCopyBufferSubDataNV
        { 2575,   267 }, // glCopyBufferSubDataNV and glCopyBufferSubData
        {  272,  2576 }, // glCopyImageSubData and glCopyImageSubDataEXT
        {  272,  2577 }, // glCopyImageSubData and glCopyImageSubDataOES
        { 2576,   272 }, // glCopyImageSubDataEXT and glCopyImageSubData
        { 2576,  2577 }, // glCopyImageSubDataEXT and glCopyImageSubDataOES
        { 2577,   272 }, // glCopyImageSubDataOES and glCopyImageSubData
        { 2577,  2576 }, // glCopyImageSubDataOES and glCopyImageSubDataEXT
        {  281,   282 }, // glCopyTexImage1D and glCopyTexImage1DEXT
        {  282,   281 }, // glCopyTexImage1DEXT and glCopyTexImage1D
        {  283,   284 }, // glCopyTexImage2D and glCopyTexImage2DEXT
        {  284,   283 }, // glCopyTexImage2DEXT and glCopyTexImage2D
        {  285,   286 }, // glCopyTexSubImage1D and glCopyTexSubImage1DEXT
        {  286,   285 }, // glCopyTexSubImage1DEXT and glCopyTexSubImage1D
        {  287,   288 }, // glCopyTexSubImage2D and glCopyTexSubImage2DEXT
        {  288,   287 }, // glCopyTexSubImage2DEXT and glCopyTexSubImage2D
        {  289,   290 }, // glCopyTexSubImage3D and glCopyTexSubImage3DEXT
        {  290,   289 }, // glCopyTexSubImage3DEXT and glCopyTexSubImage3D
        {  310,   311 }, // glCreateProgram and glCreateProgramObjectARB
        {  311,   310 }, // glCreateProgramObjectARB and glCreateProgram
        {  318,   319 }, // glCreateShader and glCreateShaderObjectARB
        {  319,   318 }, // glCreateShaderObjectARB and glCreateShader
        {  331,   333 }, // glDebugMessageCallback and glDebugMessageCallbackARB
        {  331,  2588 }, // glDebugMessageCallback and glDebugMessageCallbackKHR
        {  333,   331 }, // glDebugMessageCallbackARB and glDebugMessageCallback
        {  333,  2588 }, // glDebugMessageCallbackARB and glDebugMessageCallbackKHR
        { 2588,   331 }, // glDebugMessageCallbackKHR and glDebugMessageCallback
        { 2588,   333 }, // glDebugMessageCallbackKHR and glDebugMessageCallbackARB
        {  334,   335 }, // glDebugMessageControl and glDebugMessageControlARB
        {  334,  2589 }, // glDebugMessageControl and glDebugMessageControlKHR
        {  335,   334 }, // glDebugMessageControlARB and glDebugMessageControl
        {  335,  2589 }, // glDebugMessageControlARB and glDebugMessageControlKHR
        { 2589,   334 }, // glDebugMessageControlKHR and glDebugMessageControl
        { 2589,   335 }, // glDebugMessageControlKHR and glDebugMessageControlARB
        {  337,   339 }, // glDebugMessageInsert and glDebugMessageInsertARB
        {  337,  2590 }, // glDebugMessageInsert and glDebugMessageInsertKHR
        {  339,   337 }, // glDebugMessageInsertARB and glDebugMessageInsert
        {  339,  2590 }, // glDebugMessageInsertARB and glDebugMessageInsertKHR
        { 2590,   337 }, // glDebugMessageInsertKHR and glDebugMessageInsert
        { 2590,   339 }, // glDebugMessageInsertKHR and glDebugMessageInsertARB
        {  344,   345 }, // glDeleteBuffers and glDeleteBuffersARB
        {  345,   344 }, // glDeleteBuffersARB and glDeleteBuffers
        {  350,   351 }, // glDeleteFramebuffers and glDeleteFramebuffersEXT
        {  351,   350 }, // glDeleteFramebuffersEXT and glDeleteFramebuffers
        {  362,   363 }, // glDeleteProgramsARB and glDeleteProgramsNV
        {  363,   362 }, // glDeleteProgramsNV and glDeleteProgramsARB
        {  364,   365 }, // glDeleteQueries and glDeleteQueriesARB
        {  365,   364 }, // glDeleteQueriesARB and glDeleteQueries
        {  367,   368 }, // glDeleteRenderbuffers and glDeleteRenderbuffersEXT
        {  368,   367 }, // glDeleteRenderbuffersEXT and glDeleteRenderbuffers
        {  373,  2593 }, // glDeleteSync and glDeleteSyncAPPLE
        { 2593,   373 }, // glDeleteSyncAPPLE and glDeleteSync
        {  376,   377 }, // glDeleteTransformFeedbacks and glDeleteTransformFeedbacksNV
        {  377,   376 }, // glDeleteTransformFeedbacksNV and glDeleteTransformFeedbacks
        {  378,   379 }, // glDeleteVertexArrays and glDeleteVertexArraysAPPLE
        {  378,  2594 }, // glDeleteVertexArrays and glDeleteVertexArraysOES
        {  379,   378 }, // glDeleteVertexArraysAPPLE and glDeleteVertexArrays
        {  379,  2594 }, // glDeleteVertexArraysAPPLE and glDeleteVertexArraysOES
        { 2594,   378 }, // glDeleteVertexArraysOES and glDeleteVertexArrays
        { 2594,   379 }, // glDeleteVertexArraysOES and glDeleteVertexArraysAPPLE
        {  391,   392 }, // glDepthRangef and glDepthRangefOES
        {  392,   391 }, // glDepthRangefOES and glDepthRangef
        {  394,   395 }, // glDetachObjectARB and glDetachShader
        {  395,   394 }, // glDetachShader and glDetachObjectARB
        {  408,   400 }, // glDisablei and glDisableIndexedEXT
        {  408,  2601 }, // glDisablei and glDisableiEXT
        {  408,  2602 }, // glDisablei and glDisableiNV
        {  408,  2603 }, // glDisablei and glDisableiOES
        { 2601,   400 }, // glDisableiEXT and glDisableIndexedEXT
        { 2601,   408 }, // glDisableiEXT and glDisablei
        { 2601,  2602 }, // glDisableiEXT and glDisableiNV
        { 2601,  2603 }, // glDisableiEXT and glDisableiOES
        {  400,   408 }, // glDisableIndexedEXT and glDisablei
        {  400,  2601 }, // glDisableIndexedEXT and glDisableiEXT
        {  400,  2602 }, // glDisableIndexedEXT and glDisableiNV
        {  400,  2603 }, // glDisableIndexedEXT and glDisableiOES
        { 2602,   400 }, // glDisableiNV and glDisableIndexedEXT
        { 2602,   408 }, // glDisableiNV and glDisablei
        { 2602,  2601 }, // glDisableiNV and glDisableiEXT
        { 2602,  2603 }, // glDisableiNV and glDisableiOES
        { 2603,   400 }, // glDisableiOES and glDisableIndexedEXT
        { 2603,   408 }, // glDisableiOES and glDisablei
        { 2603,  2601 }, // glDisableiOES and glDisableiEXT
        { 2603,  2602 }, // glDisableiOES and glDisableiNV
        {  406,   407 }, // glDisableVertexAttribArray and glDisableVertexAttribArrayARB
        {  407,   406 }, // glDisableVertexAttribArrayARB and glDisableVertexAttribArray
        {  412,   413 }, // glDrawArrays and glDrawArraysEXT
        {  413,   412 }, // glDrawArraysEXT and glDrawArrays
        {  415,  2605 }, // glDrawArraysInstanced and glDrawArraysInstancedANGLE
        {  415,   416 }, // glDrawArraysInstanced and glDrawArraysInstancedARB
        {  415,   418 }, // glDrawArraysInstanced and glDrawArraysInstancedEXT
        {  415,  2608 }, // glDrawArraysInstanced and glDrawArraysInstancedNV
        { 2605,   415 }, // glDrawArraysInstancedANGLE and glDrawArraysInstanced
        { 2605,   416 }, // glDrawArraysInstancedANGLE and glDrawArraysInstancedARB
        { 2605,   418 }, // glDrawArraysInstancedANGLE and glDrawArraysInstancedEXT
        { 2605,  2608 }, // glDrawArraysInstancedANGLE and glDrawArraysInstancedNV
        {  416,   415 }, // glDrawArraysInstancedARB and glDrawArraysInstanced
        {  416,  2605 }, // glDrawArraysInstancedARB and glDrawArraysInstancedANGLE
        {  416,   418 }, // glDrawArraysInstancedARB and glDrawArraysInstancedEXT
        {  416,  2608 }, // glDrawArraysInstancedARB and glDrawArraysInstancedNV
        {  417,  2607 }, // glDrawArraysInstancedBaseInstance and glDrawArraysInstancedBaseInstanceEXT
        { 2607,   417 }, // glDrawArraysInstancedBaseInstanceEXT and glDrawArraysInstancedBaseInstance
        {  418,   415 }, // glDrawArraysInstancedEXT and glDrawArraysInstanced
        {  418,  2605 }, // glDrawArraysInstancedEXT and glDrawArraysInstancedANGLE
        {  418,   416 }, // glDrawArraysInstancedEXT and glDrawArraysInstancedARB
        {  418,  2608 }, // glDrawArraysInstancedEXT and glDrawArraysInstancedNV
        { 2608,   415 }, // glDrawArraysInstancedNV and glDrawArraysInstanced
        { 2608,  2605 }, // glDrawArraysInstancedNV and glDrawArraysInstancedANGLE
        { 2608,   416 }, // glDrawArraysInstancedNV and glDrawArraysInstancedARB
        { 2608,   418 }, // glDrawArraysInstancedNV and glDrawArraysInstancedEXT
        {  420,   421 }, // glDrawBuffers and glDrawBuffersARB
        {  420,   422 }, // glDrawBuffers and glDrawBuffersATI
        {  420,  2609 }, // glDrawBuffers and glDrawBuffersEXT
        {  421,   420 }, // glDrawBuffersARB and glDrawBuffers
        {  421,   422 }, // glDrawBuffersARB and glDrawBuffersATI
        {  421,  2609 }, // glDrawBuffersARB and glDrawBuffersEXT
        {  422,   420 }, // glDrawBuffersATI and glDrawBuffers
        {  422,   421 }, // glDrawBuffersATI and glDrawBuffersARB
        {  422,  2609 }, // glDrawBuffersATI and glDrawBuffersEXT
        { 2609,   420 }, // glDrawBuffersEXT and glDrawBuffers
        { 2609,   421 }, // glDrawBuffersEXT and glDrawBuffersARB
        { 2609,   422 }, // glDrawBuffersEXT and glDrawBuffersATI
        {  430,  2612 }, // glDrawElementsBaseVertex and glDrawElementsBaseVertexEXT
        {  430,  2613 }, // glDrawElementsBaseVertex and glDrawElementsBaseVertexOES
        { 2612,   430 }, // glDrawElementsBaseVertexEXT and glDrawElementsBaseVertex
        { 2612,  2613 }, // glDrawElementsBaseVertexEXT and glDrawElementsBaseVertexOES
        { 2613,   430 }, // glDrawElementsBaseVertexOES and glDrawElementsBaseVertex
        { 2613,  2612 }, // glDrawElementsBaseVertexOES and glDrawElementsBaseVertexEXT
        {  432,  2614 }, // glDrawElementsInstanced and glDrawElementsInstancedANGLE
        {  432,   433 }, // glDrawElementsInstanced and glDrawElementsInstancedARB
        {  432,   437 }, // glDrawElementsInstanced and glDrawElementsInstancedEXT
        {  432,  2620 }, // glDrawElementsInstanced and glDrawElementsInstancedNV
        { 2614,   432 }, // glDrawElementsInstancedANGLE and glDrawElementsInstanced
        { 2614,   433 }, // glDrawElementsInstancedANGLE and glDrawElementsInstancedARB
        { 2614,   437 }, // glDrawElementsInstancedANGLE and glDrawElementsInstancedEXT
        { 2614,  2620 }, // glDrawElementsInstancedANGLE and glDrawElementsInstancedNV
        {  433,   432 }, // glDrawElementsInstancedARB and glDrawElementsInstanced
        {  433,  2614 }, // glDrawElementsInstancedARB and glDrawElementsInstancedANGLE
        {  433,   437 }, // glDrawElementsInstancedARB and glDrawElementsInstancedEXT
        {  433,  2620 }, // glDrawElementsInstancedARB and glDrawElementsInstancedNV
        {  434,  2615 }, // glDrawElementsInstancedBaseInstance and glDrawElementsInstancedBaseInstanceEXT
        { 2615,   434 }, // glDrawElementsInstancedBaseInstanceEXT and glDrawElementsInstancedBaseInstance
        {  435,  2618 }, // glDrawElementsInstancedBaseVertex and glDrawElementsInstancedBaseVertexEXT
        {  435,  2619 }, // glDrawElementsInstancedBaseVertex and glDrawElementsInstancedBaseVertexOES
        {  436,  2617 }, // glDrawElementsInstancedBaseVertexBaseInstance and glDrawElementsInstancedBaseVertexBaseInstanceEXT
        { 2617,   436 }, // glDrawElementsInstancedBaseVertexBaseInstanceEXT and glDrawElementsInstancedBaseVertexBaseInstance
        { 2618,   435 }, // glDrawElementsInstancedBaseVertexEXT and glDrawElementsInstancedBaseVertex
        { 2618,  2619 }, // glDrawElementsInstancedBaseVertexEXT and glDrawElementsInstancedBaseVertexOES
        { 2619,   435 }, // glDrawElementsInstancedBaseVertexOES and glDrawElementsInstancedBaseVertex
        { 2619,  2618 }, // glDrawElementsInstancedBaseVertexOES and glDrawElementsInstancedBaseVertexEXT
        {  437,   432 }, // glDrawElementsInstancedEXT and glDrawElementsInstanced
        {  437,  2614 }, // glDrawElementsInstancedEXT and glDrawElementsInstancedANGLE
        {  437,   433 }, // glDrawElementsInstancedEXT and glDrawElementsInstancedARB
        {  437,  2620 }, // glDrawElementsInstancedEXT and glDrawElementsInstancedNV
        { 2620,   432 }, // glDrawElementsInstancedNV and glDrawElementsInstanced
        { 2620,  2614 }, // glDrawElementsInstancedNV and glDrawElementsInstancedANGLE
        { 2620,   433 }, // glDrawElementsInstancedNV and glDrawElementsInstancedARB
        { 2620,   437 }, // glDrawElementsInstancedNV and glDrawElementsInstancedEXT
        {  443,   445 }, // glDrawRangeElements and glDrawRangeElementsEXT
        {  444,  2621 }, // glDrawRangeElementsBaseVertex and glDrawRangeElementsBaseVertexEXT
        {  444,  2622 }, // glDrawRangeElementsBaseVertex and glDrawRangeElementsBaseVertexOES
        { 2621,   444 }, // glDrawRangeElementsBaseVertexEXT and glDrawRangeElementsBaseVertex
        { 2621,  2622 }, // glDrawRangeElementsBaseVertexEXT and glDrawRangeElementsBaseVertexOES
        { 2622,   444 }, // glDrawRangeElementsBaseVertexOES and glDrawRangeElementsBaseVertex
        { 2622,  2621 }, // glDrawRangeElementsBaseVertexOES and glDrawRangeElementsBaseVertexEXT
        {  445,   443 }, // glDrawRangeElementsEXT and glDrawRangeElements
        {  447,  2623 }, // glDrawTransformFeedback and glDrawTransformFeedbackEXT
        {  447,   449 }, // glDrawTransformFeedback and glDrawTransformFeedbackNV
        { 2623,   447 }, // glDrawTransformFeedbackEXT and glDrawTransformFeedback
        { 2623,   449 }, // glDrawTransformFeedbackEXT and glDrawTransformFeedbackNV
        {  448,  2624 }, // glDrawTransformFeedbackInstanced and glDrawTransformFeedbackInstancedEXT
        { 2624,   448 }, // glDrawTransformFeedbackInstancedEXT and glDrawTransformFeedbackInstanced
        {  449,   447 }, // glDrawTransformFeedbackNV and glDrawTransformFeedback
        {  449,  2623 }, // glDrawTransformFeedbackNV and glDrawTransformFeedbackEXT
        {  471,   463 }, // glEnablei and glEnableIndexedEXT
        {  471,  2628 }, // glEnablei and glEnableiEXT
        {  471,  2629 }, // glEnablei and glEnableiNV
        {  471,  2630 }, // glEnablei and glEnableiOES
        { 2628,   463 }, // glEnableiEXT and glEnableIndexedEXT
        { 2628,   471 }, // glEnableiEXT and glEnablei
        { 2628,  2629 }, // glEnableiEXT and glEnableiNV
        { 2628,  2630 }, // glEnableiEXT and glEnableiOES
        {  463,   471 }, // glEnableIndexedEXT and glEnablei
        {  463,  2628 }, // glEnableIndexedEXT and glEnableiEXT
        {  463,  2629 }, // glEnableIndexedEXT and glEnableiNV
        {  463,  2630 }, // glEnableIndexedEXT and glEnableiOES
        { 2629,   463 }, // glEnableiNV and glEnableIndexedEXT
        { 2629,   471 }, // glEnableiNV and glEnablei
        { 2629,  2628 }, // glEnableiNV and glEnableiEXT
        { 2629,  2630 }, // glEnableiNV and glEnableiOES
        { 2630,   463 }, // glEnableiOES and glEnableIndexedEXT
        { 2630,   471 }, // glEnableiOES and glEnablei
        { 2630,  2628 }, // glEnableiOES and glEnableiEXT
        { 2630,  2629 }, // glEnableiOES and glEnableiNV
        {  469,   470 }, // glEnableVertexAttribArray and glEnableVertexAttribArrayARB
        {  470,   469 }, // glEnableVertexAttribArrayARB and glEnableVertexAttribArray
        {  472,   473 }, // glEndConditionalRender and glEndConditionalRenderNV
        {  472,   474 }, // glEndConditionalRender and glEndConditionalRenderNVX
        {  473,   472 }, // glEndConditionalRenderNV and glEndConditionalRender
        {  473,   474 }, // glEndConditionalRenderNV and glEndConditionalRenderNVX
        {  474,   472 }, // glEndConditionalRenderNVX and glEndConditionalRender
        {  474,   473 }, // glEndConditionalRenderNVX and glEndConditionalRenderNV
        {  479,   480 }, // glEndQuery and glEndQueryARB
        {  480,   479 }, // glEndQueryARB and glEndQuery
        {  482,   483 }, // glEndTransformFeedback and glEndTransformFeedbackEXT
        {  482,   484 }, // glEndTransformFeedback and glEndTransformFeedbackNV
        {  483,   482 }, // glEndTransformFeedbackEXT and glEndTransformFeedback
        {  483,   484 }, // glEndTransformFeedbackEXT and glEndTransformFeedbackNV
        {  484,   482 }, // glEndTransformFeedbackNV and glEndTransformFeedback
        {  484,   483 }, // glEndTransformFeedbackNV and glEndTransformFeedbackEXT
        {  496,  2647 }, // glFenceSync and glFenceSyncAPPLE
        { 2647,   496 }, // glFenceSyncAPPLE and glFenceSync
        {  505,   506 }, // glFlushMappedBufferRange and glFlushMappedBufferRangeAPPLE
        {  505,  2648 }, // glFlushMappedBufferRange and glFlushMappedBufferRangeEXT
        {  506,   505 }, // glFlushMappedBufferRangeAPPLE and glFlushMappedBufferRange
        {  506,  2648 }, // glFlushMappedBufferRangeAPPLE and glFlushMappedBufferRangeEXT
        { 2648,   505 }, // glFlushMappedBufferRangeEXT and glFlushMappedBufferRange
        { 2648,   506 }, // glFlushMappedBufferRangeEXT and glFlushMappedBufferRangeAPPLE
        {  548,   549 }, // glFramebufferRenderbuffer and glFramebufferRenderbufferEXT
        {  549,   548 }, // glFramebufferRenderbufferEXT and glFramebufferRenderbuffer
        {  553,   560 }, // glFramebufferTexture and glFramebufferTextureARB
        {  553,   561 }, // glFramebufferTexture and glFramebufferTextureEXT
        {  553,  2666 }, // glFramebufferTexture and glFramebufferTextureOES
        {  554,   555 }, // glFramebufferTexture1D and glFramebufferTexture1DEXT
        {  555,   554 }, // glFramebufferTexture1DEXT and glFramebufferTexture1D
        {  556,   557 }, // glFramebufferTexture2D and glFramebufferTexture2DEXT
        {  557,   556 }, // glFramebufferTexture2DEXT and glFramebufferTexture2D
        {  558,   559 }, // glFramebufferTexture3D and glFramebufferTexture3DEXT
        {  559,   558 }, // glFramebufferTexture3DEXT and glFramebufferTexture3D
        {  560,   553 }, // glFramebufferTextureARB and glFramebufferTexture
        {  560,   561 }, // glFramebufferTextureARB and glFramebufferTextureEXT
        {  560,  2666 }, // glFramebufferTextureARB and glFramebufferTextureOES
        {  561,   553 }, // glFramebufferTextureEXT and glFramebufferTexture
        {  561,   560 }, // glFramebufferTextureEXT and glFramebufferTextureARB
        {  561,  2666 }, // glFramebufferTextureEXT and glFramebufferTextureOES
        {  562,   563 }, // glFramebufferTextureFaceARB and glFramebufferTextureFaceEXT
        {  563,   562 }, // glFramebufferTextureFaceEXT and glFramebufferTextureFaceARB
        {  564,   565 }, // glFramebufferTextureLayer and glFramebufferTextureLayerARB
        {  564,   566 }, // glFramebufferTextureLayer and glFramebufferTextureLayerEXT
        {  565,   564 }, // glFramebufferTextureLayerARB and glFramebufferTextureLayer
        {  565,   566 }, // glFramebufferTextureLayerARB and glFramebufferTextureLayerEXT
        {  566,   564 }, // glFramebufferTextureLayerEXT and glFramebufferTextureLayer
        {  566,   565 }, // glFramebufferTextureLayerEXT and glFramebufferTextureLayerARB
        { 2666,   553 }, // glFramebufferTextureOES and glFramebufferTexture
        { 2666,   560 }, // glFramebufferTextureOES and glFramebufferTextureARB
        { 2666,   561 }, // glFramebufferTextureOES and glFramebufferTextureEXT
        {  573,   574 }, // glGenBuffers and glGenBuffersARB
        {  574,   573 }, // glGenBuffersARB and glGenBuffers
        {  602,   603 }, // glGenerateMipmap and glGenerateMipmapEXT
        {  603,   602 }, // glGenerateMipmapEXT and glGenerateMipmap
        {  578,   579 }, // glGenFramebuffers and glGenFramebuffersEXT
        {  579,   578 }, // glGenFramebuffersEXT and glGenFramebuffers
        {  585,   586 }, // glGenProgramsARB and glGenProgramsNV
        {  586,   585 }, // glGenProgramsNV and glGenProgramsARB
        {  587,   588 }, // glGenQueries and glGenQueriesARB
        {  588,   587 }, // glGenQueriesARB and glGenQueries
        {  590,   591 }, // glGenRenderbuffers and glGenRenderbuffersEXT
        {  591,   590 }, // glGenRenderbuffersEXT and glGenRenderbuffers
        {  597,   598 }, // glGenTransformFeedbacks and glGenTransformFeedbacksNV
        {  598,   597 }, // glGenTransformFeedbacksNV and glGenTransformFeedbacks
        {  599,   600 }, // glGenVertexArrays and glGenVertexArraysAPPLE
        {  599,  2670 }, // glGenVertexArrays and glGenVertexArraysOES
        {  600,   599 }, // glGenVertexArraysAPPLE and glGenVertexArrays
        {  600,  2670 }, // glGenVertexArraysAPPLE and glGenVertexArraysOES
        { 2670,   599 }, // glGenVertexArraysOES and glGenVertexArrays
        { 2670,   600 }, // glGenVertexArraysOES and glGenVertexArraysAPPLE
        {  608,   609 }, // glGetActiveAttrib and glGetActiveAttribARB
        {  609,   608 }, // glGetActiveAttribARB and glGetActiveAttrib
        {  613,   614 }, // glGetActiveUniform and glGetActiveUniformARB
        {  614,   613 }, // glGetActiveUniformARB and glGetActiveUniform
        {  624,   625 }, // glGetAttribLocation and glGetAttribLocationARB
        {  625,   624 }, // glGetAttribLocationARB and glGetAttribLocation
        {  627,   626 }, // glGetBooleani_v and glGetBooleanIndexedvEXT
        {  626,   627 }, // glGetBooleanIndexedvEXT and glGetBooleani_v
        {  630,   631 }, // glGetBufferParameteriv and glGetBufferParameterivARB
        {  631,   630 }, // glGetBufferParameterivARB and glGetBufferParameteriv
        {  633,   634 }, // glGetBufferPointerv and glGetBufferPointervARB
        {  633,  2676 }, // glGetBufferPointerv and glGetBufferPointervOES
        {  634,   633 }, // glGetBufferPointervARB and glGetBufferPointerv
        {  634,  2676 }, // glGetBufferPointervARB and glGetBufferPointervOES
        { 2676,   633 }, // glGetBufferPointervOES and glGetBufferPointerv
        { 2676,   634 }, // glGetBufferPointervOES and glGetBufferPointervARB
        {  635,   636 }, // glGetBufferSubData and glGetBufferSubDataARB
        {  636,   635 }, // glGetBufferSubDataARB and glGetBufferSubData
        {  652,   653 }, // glGetCompressedTexImage and glGetCompressedTexImageARB
        {  653,   652 }, // glGetCompressedTexImageARB and glGetCompressedTexImage
        {  662,   664 }, // glGetDebugMessageLog and glGetDebugMessageLogARB
        {  662,  2679 }, // glGetDebugMessageLog and glGetDebugMessageLogKHR
        {  664,   662 }, // glGetDebugMessageLogARB and glGetDebugMessageLog
        {  664,  2679 }, // glGetDebugMessageLogARB and glGetDebugMessageLogKHR
        { 2679,   662 }, // glGetDebugMessageLogKHR and glGetDebugMessageLog
        { 2679,   664 }, // glGetDebugMessageLogKHR and glGetDebugMessageLogARB
        {  667,   666 }, // glGetDoublei_v and glGetDoubleIndexedvEXT
        {  667,   668 }, // glGetDoublei_v and glGetDoublei_vEXT
        {  668,   666 }, // glGetDoublei_vEXT and glGetDoubleIndexedvEXT
        {  668,   667 }, // glGetDoublei_vEXT and glGetDoublei_v
        {  666,   667 }, // glGetDoubleIndexedvEXT and glGetDoublei_v
        {  666,   668 }, // glGetDoubleIndexedvEXT and glGetDoublei_vEXT
        {  677,   676 }, // glGetFloati_v and glGetFloatIndexedvEXT
        {  677,   678 }, // glGetFloati_v and glGetFloati_vEXT
        {  677,  2682 }, // glGetFloati_v and glGetFloati_vNV
        {  677,  2683 }, // glGetFloati_v and glGetFloati_vOES
        {  678,   676 }, // glGetFloati_vEXT and glGetFloatIndexedvEXT
        {  678,   677 }, // glGetFloati_vEXT and glGetFloati_v
        {  678,  2682 }, // glGetFloati_vEXT and glGetFloati_vNV
        {  678,  2683 }, // glGetFloati_vEXT and glGetFloati_vOES
        { 2682,   676 }, // glGetFloati_vNV and glGetFloatIndexedvEXT
        { 2682,   677 }, // glGetFloati_vNV and glGetFloati_v
        { 2682,   678 }, // glGetFloati_vNV and glGetFloati_vEXT
        { 2682,  2683 }, // glGetFloati_vNV and glGetFloati_vOES
        { 2683,   676 }, // glGetFloati_vOES and glGetFloatIndexedvEXT
        { 2683,   677 }, // glGetFloati_vOES and glGetFloati_v
        { 2683,   678 }, // glGetFloati_vOES and glGetFloati_vEXT
        { 2683,  2682 }, // glGetFloati_vOES and glGetFloati_vNV
        {  676,   677 }, // glGetFloatIndexedvEXT and glGetFloati_v
        {  676,   678 }, // glGetFloatIndexedvEXT and glGetFloati_vEXT
        {  676,  2682 }, // glGetFloatIndexedvEXT and glGetFloati_vNV
        {  676,  2683 }, // glGetFloatIndexedvEXT and glGetFloati_vOES
        {  681,  2685 }, // glGetFragDataIndex and glGetFragDataIndexEXT
        { 2685,   681 }, // glGetFragDataIndexEXT and glGetFragDataIndex
        {  682,   683 }, // glGetFragDataLocation and glGetFragDataLocationEXT
        {  683,   682 }, // glGetFragDataLocationEXT and glGetFragDataLocation
        {  688,   689 }, // glGetFramebufferAttachmentParameteriv and glGetFramebufferAttachmentParameterivEXT
        {  689,   688 }, // glGetFramebufferAttachmentParameterivEXT and glGetFramebufferAttachmentParameteriv
        {  694,  2694 }, // glGetGraphicsResetStatus and glGetGraphicsResetStatusEXT
        {  694,  2695 }, // glGetGraphicsResetStatus and glGetGraphicsResetStatusKHR
        { 2694,   694 }, // glGetGraphicsResetStatusEXT and glGetGraphicsResetStatus
        { 2694,  2695 }, // glGetGraphicsResetStatusEXT and glGetGraphicsResetStatusKHR
        { 2695,   694 }, // glGetGraphicsResetStatusKHR and glGetGraphicsResetStatus
        { 2695,  2694 }, // glGetGraphicsResetStatusKHR and glGetGraphicsResetStatusEXT
        {  708,  2697 }, // glGetInteger64v and glGetInteger64vAPPLE
        {  708,  2698 }, // glGetInteger64v and glGetInteger64vEXT
        { 2697,   708 }, // glGetInteger64vAPPLE and glGetInteger64v
        { 2697,  2698 }, // glGetInteger64vAPPLE and glGetInteger64vEXT
        { 2698,   708 }, // glGetInteger64vEXT and glGetInteger64v
        { 2698,  2697 }, // glGetInteger64vEXT and glGetInteger64vAPPLE
        {  710,   709 }, // glGetIntegeri_v and glGetIntegerIndexedvEXT
        {  709,   710 }, // glGetIntegerIndexedvEXT and glGetIntegeri_v
        {  750,   751 }, // glGetMultisamplefv and glGetMultisamplefvNV
        {  751,   750 }, // glGetMultisamplefvNV and glGetMultisamplefv
        {  997,  2758 }, // glGetnUniformfv and glGetnUniformfvEXT
        {  997,  2759 }, // glGetnUniformfv and glGetnUniformfvKHR
        { 2758,   997 }, // glGetnUniformfvEXT and glGetnUniformfv
        { 2758,  2759 }, // glGetnUniformfvEXT and glGetnUniformfvKHR
        { 2759,   997 }, // glGetnUniformfvKHR and glGetnUniformfv
        { 2759,  2758 }, // glGetnUniformfvKHR and glGetnUniformfvEXT
        { 1000,  2761 }, // glGetnUniformiv and glGetnUniformivEXT
        { 1000,  2762 }, // glGetnUniformiv and glGetnUniformivKHR
        { 2761,  1000 }, // glGetnUniformivEXT and glGetnUniformiv
        { 2761,  2762 }, // glGetnUniformivEXT and glGetnUniformivKHR
        { 2762,  1000 }, // glGetnUniformivKHR and glGetnUniformiv
        { 2762,  2761 }, // glGetnUniformivKHR and glGetnUniformivEXT
        { 1003,  2764 }, // glGetnUniformuiv and glGetnUniformuivKHR
        { 2764,  1003 }, // glGetnUniformuivKHR and glGetnUniformuiv
        {  778,  2706 }, // glGetObjectLabel and glGetObjectLabelKHR
        { 2706,   778 }, // glGetObjectLabelKHR and glGetObjectLabel
        {  783,  2707 }, // glGetObjectPtrLabel and glGetObjectPtrLabelKHR
        { 2707,   783 }, // glGetObjectPtrLabelKHR and glGetObjectPtrLabel
        {  812,   813 }, // glGetPointerv and glGetPointervEXT
        {  812,  2708 }, // glGetPointerv and glGetPointervKHR
        {  813,   812 }, // glGetPointervEXT and glGetPointerv
        {  813,  2708 }, // glGetPointervEXT and glGetPointervKHR
        { 2708,   812 }, // glGetPointervKHR and glGetPointerv
        { 2708,   813 }, // glGetPointervKHR and glGetPointervEXT
        {  814,  2710 }, // glGetProgramBinary and glGetProgramBinaryOES
        { 2710,   814 }, // glGetProgramBinaryOES and glGetProgramBinary
        {  857,   858 }, // glGetQueryiv and glGetQueryivARB
        {  858,   857 }, // glGetQueryivARB and glGetQueryiv
        {  849,   850 }, // glGetQueryObjecti64v and glGetQueryObjecti64vEXT
        {  850,   849 }, // glGetQueryObjecti64vEXT and glGetQueryObjecti64v
        {  851,   852 }, // glGetQueryObjectiv and glGetQueryObjectivARB
        {  851,  2717 }, // glGetQueryObjectiv and glGetQueryObjectivEXT
        {  852,   851 }, // glGetQueryObjectivARB and glGetQueryObjectiv
        {  852,  2717 }, // glGetQueryObjectivARB and glGetQueryObjectivEXT
        { 2717,   851 }, // glGetQueryObjectivEXT and glGetQueryObjectiv
        { 2717,   852 }, // glGetQueryObjectivEXT and glGetQueryObjectivARB
        {  853,   854 }, // glGetQueryObjectui64v and glGetQueryObjectui64vEXT
        {  854,   853 }, // glGetQueryObjectui64vEXT and glGetQueryObjectui64v
        {  855,   856 }, // glGetQueryObjectuiv and glGetQueryObjectuivARB
        {  856,   855 }, // glGetQueryObjectuivARB and glGetQueryObjectuiv
        {  859,   860 }, // glGetRenderbufferParameteriv and glGetRenderbufferParameterivEXT
        {  860,   859 }, // glGetRenderbufferParameterivEXT and glGetRenderbufferParameteriv
        {  861,  2726 }, // glGetSamplerParameterIiv and glGetSamplerParameterIivEXT
        {  861,  2727 }, // glGetSamplerParameterIiv and glGetSamplerParameterIivOES
        { 2726,   861 }, // glGetSamplerParameterIivEXT and glGetSamplerParameterIiv
        { 2726,  2727 }, // glGetSamplerParameterIivEXT and glGetSamplerParameterIivOES
        { 2727,   861 }, // glGetSamplerParameterIivOES and glGetSamplerParameterIiv
        { 2727,  2726 }, // glGetSamplerParameterIivOES and glGetSamplerParameterIivEXT
        {  862,  2729 }, // glGetSamplerParameterIuiv and glGetSamplerParameterIuivEXT
        {  862,  2730 }, // glGetSamplerParameterIuiv and glGetSamplerParameterIuivOES
        { 2729,   862 }, // glGetSamplerParameterIuivEXT and glGetSamplerParameterIuiv
        { 2729,  2730 }, // glGetSamplerParameterIuivEXT and glGetSamplerParameterIuivOES
        { 2730,   862 }, // glGetSamplerParameterIuivOES and glGetSamplerParameterIuiv
        { 2730,  2729 }, // glGetSamplerParameterIuivOES and glGetSamplerParameterIuivEXT
        {  870,   871 }, // glGetShaderSource and glGetShaderSourceARB
        {  871,   870 }, // glGetShaderSourceARB and glGetShaderSource
        {  881,  2735 }, // glGetSynciv and glGetSyncivAPPLE
        { 2735,   881 }, // glGetSyncivAPPLE and glGetSynciv
        {  891,   892 }, // glGetTexParameterIiv and glGetTexParameterIivEXT
        {  891,  2741 }, // glGetTexParameterIiv and glGetTexParameterIivOES
        {  892,   891 }, // glGetTexParameterIivEXT and glGetTexParameterIiv
        {  892,  2741 }, // glGetTexParameterIivEXT and glGetTexParameterIivOES
        { 2741,   891 }, // glGetTexParameterIivOES and glGetTexParameterIiv
        { 2741,   892 }, // glGetTexParameterIivOES and glGetTexParameterIivEXT
        {  893,   894 }, // glGetTexParameterIuiv and glGetTexParameterIuivEXT
        {  893,  2743 }, // glGetTexParameterIuiv and glGetTexParameterIuivOES
        {  894,   893 }, // glGetTexParameterIuivEXT and glGetTexParameterIuiv
        {  894,  2743 }, // glGetTexParameterIuivEXT and glGetTexParameterIuivOES
        { 2743,   893 }, // glGetTexParameterIuivOES and glGetTexParameterIuiv
        { 2743,   894 }, // glGetTexParameterIuivOES and glGetTexParameterIuivEXT
        {  899,  2747 }, // glGetTextureHandleARB and glGetTextureHandleIMG
        { 2747,   899 }, // glGetTextureHandleIMG and glGetTextureHandleARB
        {  915,  2748 }, // glGetTextureSamplerHandleARB and glGetTextureSamplerHandleIMG
        { 2748,   915 }, // glGetTextureSamplerHandleIMG and glGetTextureSamplerHandleARB
        {  919,   920 }, // glGetTransformFeedbackVarying and glGetTransformFeedbackVaryingEXT
        {  920,   919 }, // glGetTransformFeedbackVaryingEXT and glGetTransformFeedbackVarying
        {  933,   934 }, // glGetUniformfv and glGetUniformfvARB
        {  934,   933 }, // glGetUniformfvARB and glGetUniformfv
        {  937,   938 }, // glGetUniformiv and glGetUniformivARB
        {  938,   937 }, // glGetUniformivARB and glGetUniformiv
        {  928,   929 }, // glGetUniformLocation and glGetUniformLocationARB
        {  929,   928 }, // glGetUniformLocationARB and glGetUniformLocation
        {  941,   942 }, // glGetUniformuiv and glGetUniformuivEXT
        {  942,   941 }, // glGetUniformuivEXT and glGetUniformuiv
        {  973,   974 }, // glGetVertexAttribdv and glGetVertexAttribdvARB
        {  973,   975 }, // glGetVertexAttribdv and glGetVertexAttribdvNV
        {  974,   973 }, // glGetVertexAttribdvARB and glGetVertexAttribdv
        {  974,   975 }, // glGetVertexAttribdvARB and glGetVertexAttribdvNV
        {  975,   973 }, // glGetVertexAttribdvNV and glGetVertexAttribdv
        {  975,   974 }, // glGetVertexAttribdvNV and glGetVertexAttribdvARB
        {  976,   977 }, // glGetVertexAttribfv and glGetVertexAttribfvARB
        {  976,   978 }, // glGetVertexAttribfv and glGetVertexAttribfvNV
        {  977,   976 }, // glGetVertexAttribfvARB and glGetVertexAttribfv
        {  977,   978 }, // glGetVertexAttribfvARB and glGetVertexAttribfvNV
        {  978,   976 }, // glGetVertexAttribfvNV and glGetVertexAttribfv
        {  978,   977 }, // glGetVertexAttribfvNV and glGetVertexAttribfvARB
        {  961,   962 }, // glGetVertexAttribIiv and glGetVertexAttribIivEXT
        {  962,   961 }, // glGetVertexAttribIivEXT and glGetVertexAttribIiv
        {  963,   964 }, // glGetVertexAttribIuiv and glGetVertexAttribIuivEXT
        {  964,   963 }, // glGetVertexAttribIuivEXT and glGetVertexAttribIuiv
        {  979,   980 }, // glGetVertexAttribiv and glGetVertexAttribivARB
        {  979,   981 }, // glGetVertexAttribiv and glGetVertexAttribivNV
        {  980,   979 }, // glGetVertexAttribivARB and glGetVertexAttribiv
        {  980,   981 }, // glGetVertexAttribivARB and glGetVertexAttribivNV
        {  981,   979 }, // glGetVertexAttribivNV and glGetVertexAttribiv
        {  981,   980 }, // glGetVertexAttribivNV and glGetVertexAttribivARB
        {  965,   966 }, // glGetVertexAttribLdv and glGetVertexAttribLdvEXT
        {  966,   965 }, // glGetVertexAttribLdvEXT and glGetVertexAttribLdv
        {  970,   971 }, // glGetVertexAttribPointerv and glGetVertexAttribPointervARB
        {  970,   972 }, // glGetVertexAttribPointerv and glGetVertexAttribPointervNV
        {  971,   970 }, // glGetVertexAttribPointervARB and glGetVertexAttribPointerv
        {  971,   972 }, // glGetVertexAttribPointervARB and glGetVertexAttribPointervNV
        {  972,   970 }, // glGetVertexAttribPointervNV and glGetVertexAttribPointerv
        {  972,   971 }, // glGetVertexAttribPointervNV and glGetVertexAttribPointervARB
        { 1051,  1052 }, // glIsBuffer and glIsBufferARB
        { 1052,  1051 }, // glIsBufferARB and glIsBuffer
        { 1057,  1056 }, // glIsEnabledi and glIsEnabledIndexedEXT
        { 1057,  2766 }, // glIsEnabledi and glIsEnablediEXT
        { 1057,  2767 }, // glIsEnabledi and glIsEnablediNV
        { 1057,  2768 }, // glIsEnabledi and glIsEnablediOES
        { 2766,  1056 }, // glIsEnablediEXT and glIsEnabledIndexedEXT
        { 2766,  1057 }, // glIsEnablediEXT and glIsEnabledi
        { 2766,  2767 }, // glIsEnablediEXT and glIsEnablediNV
        { 2766,  2768 }, // glIsEnablediEXT and glIsEnablediOES
        { 1056,  1057 }, // glIsEnabledIndexedEXT and glIsEnabledi
        { 1056,  2766 }, // glIsEnabledIndexedEXT and glIsEnablediEXT
        { 1056,  2767 }, // glIsEnabledIndexedEXT and glIsEnablediNV
        { 1056,  2768 }, // glIsEnabledIndexedEXT and glIsEnablediOES
        { 2767,  1056 }, // glIsEnablediNV and glIsEnabledIndexedEXT
        { 2767,  1057 }, // glIsEnablediNV and glIsEnabledi
        { 2767,  2766 }, // glIsEnablediNV and glIsEnablediEXT
        { 2767,  2768 }, // glIsEnablediNV and glIsEnablediOES
        { 2768,  1056 }, // glIsEnablediOES and glIsEnabledIndexedEXT
        { 2768,  1057 }, // glIsEnablediOES and glIsEnabledi
        { 2768,  2766 }, // glIsEnablediOES and glIsEnablediEXT
        { 2768,  2767 }, // glIsEnablediOES and glIsEnablediNV
        { 1060,  1061 }, // glIsFramebuffer and glIsFramebufferEXT
        { 1061,  1060 }, // glIsFramebufferEXT and glIsFramebuffer
        { 1074,  1075 }, // glIsProgramARB and glIsProgramNV
        { 1075,  1074 }, // glIsProgramNV and glIsProgramARB
        { 1077,  1078 }, // glIsQuery and glIsQueryARB
        { 1078,  1077 }, // glIsQueryARB and glIsQuery
        { 1079,  1080 }, // glIsRenderbuffer and glIsRenderbufferEXT
        { 1080,  1079 }, // glIsRenderbufferEXT and glIsRenderbuffer
        { 1085,  2771 }, // glIsSync and glIsSyncAPPLE
        { 2771,  1085 }, // glIsSyncAPPLE and glIsSync
        { 1090,  1091 }, // glIsTransformFeedback and glIsTransformFeedbackNV
        { 1091,  1090 }, // glIsTransformFeedbackNV and glIsTransformFeedback
        { 1093,  1094 }, // glIsVertexArray and glIsVertexArrayAPPLE
        { 1093,  2772 }, // glIsVertexArray and glIsVertexArrayOES
        { 1094,  1093 }, // glIsVertexArrayAPPLE and glIsVertexArray
        { 1094,  2772 }, // glIsVertexArrayAPPLE and glIsVertexArrayOES
        { 2772,  1093 }, // glIsVertexArrayOES and glIsVertexArray
        { 2772,  1094 }, // glIsVertexArrayOES and glIsVertexArrayAPPLE
        { 1107,  1108 }, // glLinkProgram and glLinkProgramARB
        { 1108,  1107 }, // glLinkProgramARB and glLinkProgram
        { 1136,  1137 }, // glMapBuffer and glMapBufferARB
        { 1136,  2775 }, // glMapBuffer and glMapBufferOES
        { 1137,  1136 }, // glMapBufferARB and glMapBuffer
        { 1137,  2775 }, // glMapBufferARB and glMapBufferOES
        { 2775,  1136 }, // glMapBufferOES and glMapBuffer
        { 2775,  1137 }, // glMapBufferOES and glMapBufferARB
        { 1138,  2776 }, // glMapBufferRange and glMapBufferRangeEXT
        { 2776,  1138 }, // glMapBufferRangeEXT and glMapBufferRange
        { 1185,  1186 }, // glMaxShaderCompilerThreadsARB and glMaxShaderCompilerThreadsKHR
        { 1186,  1185 }, // glMaxShaderCompilerThreadsKHR and glMaxShaderCompilerThreadsARB
        { 1187,  1189 }, // glMemoryBarrier and glMemoryBarrierEXT
        { 1189,  1187 }, // glMemoryBarrierEXT and glMemoryBarrier
        { 1191,  1192 }, // glMinSampleShading and glMinSampleShadingARB
        { 1191,  2778 }, // glMinSampleShading and glMinSampleShadingOES
        { 1192,  1191 }, // glMinSampleShadingARB and glMinSampleShading
        { 1192,  2778 }, // glMinSampleShadingARB and glMinSampleShadingOES
        { 2778,  1191 }, // glMinSampleShadingOES and glMinSampleShading
        { 2778,  1192 }, // glMinSampleShadingOES and glMinSampleShadingARB
        { 1198,  1199 }, // glMultiDrawArrays and glMultiDrawArraysEXT
        { 1199,  1198 }, // glMultiDrawArraysEXT and glMultiDrawArrays
        { 1200,  1201 }, // glMultiDrawArraysIndirect and glMultiDrawArraysIndirectAMD
        { 1200,  2780 }, // glMultiDrawArraysIndirect and glMultiDrawArraysIndirectEXT
        { 1201,  1200 }, // glMultiDrawArraysIndirectAMD and glMultiDrawArraysIndirect
        { 1201,  2780 }, // glMultiDrawArraysIndirectAMD and glMultiDrawArraysIndirectEXT
        { 1204,  1205 }, // glMultiDrawArraysIndirectCount and glMultiDrawArraysIndirectCountARB
        { 1205,  1204 }, // glMultiDrawArraysIndirectCountARB and glMultiDrawArraysIndirectCount
        { 2780,  1200 }, // glMultiDrawArraysIndirectEXT and glMultiDrawArraysIndirect
        { 2780,  1201 }, // glMultiDrawArraysIndirectEXT and glMultiDrawArraysIndirectAMD
        { 1207,  1209 }, // glMultiDrawElements and glMultiDrawElementsEXT
        { 1208,  2784 }, // glMultiDrawElementsBaseVertex and glMultiDrawElementsBaseVertexEXT
        { 2784,  1208 }, // glMultiDrawElementsBaseVertexEXT and glMultiDrawElementsBaseVertex
        { 1209,  1207 }, // glMultiDrawElementsEXT and glMultiDrawElements
        { 1210,  1211 }, // glMultiDrawElementsIndirect and glMultiDrawElementsIndirectAMD
        { 1210,  2785 }, // glMultiDrawElementsIndirect and glMultiDrawElementsIndirectEXT
        { 1211,  1210 }, // glMultiDrawElementsIndirectAMD and glMultiDrawElementsIndirect
        { 1211,  2785 }, // glMultiDrawElementsIndirectAMD and glMultiDrawElementsIndirectEXT
        { 1214,  1215 }, // glMultiDrawElementsIndirectCount and glMultiDrawElementsIndirectCountARB
        { 1215,  1214 }, // glMultiDrawElementsIndirectCountARB and glMultiDrawElementsIndirectCount
        { 2785,  1210 }, // glMultiDrawElementsIndirectEXT and glMultiDrawElementsIndirect
        { 2785,  1211 }, // glMultiDrawElementsIndirectEXT and glMultiDrawElementsIndirectAMD
        { 1322,  1323 }, // glNamedBufferStorage and glNamedBufferStorageEXT
        { 1323,  1322 }, // glNamedBufferStorageEXT and glNamedBufferStorage
        { 1326,  1327 }, // glNamedBufferSubData and glNamedBufferSubDataEXT
        { 1327,  1326 }, // glNamedBufferSubDataEXT and glNamedBufferSubData
        { 1387,  2788 }, // glObjectLabel and glObjectLabelKHR
        { 2788,  1387 }, // glObjectLabelKHR and glObjectLabel
        { 1388,  2789 }, // glObjectPtrLabel and glObjectPtrLabelKHR
        { 2789,  1388 }, // glObjectPtrLabelKHR and glObjectPtrLabel
        { 1398,  2790 }, // glPatchParameteri and glPatchParameteriEXT
        { 1398,  2791 }, // glPatchParameteri and glPatchParameteriOES
        { 2790,  1398 }, // glPatchParameteriEXT and glPatchParameteri
        { 2790,  2791 }, // glPatchParameteriEXT and glPatchParameteriOES
        { 2791,  1398 }, // glPatchParameteriOES and glPatchParameteri
        { 2791,  2790 }, // glPatchParameteriOES and glPatchParameteriEXT
        { 1417,  1418 }, // glPauseTransformFeedback and glPauseTransformFeedbackNV
        { 1418,  1417 }, // glPauseTransformFeedbackNV and glPauseTransformFeedback
        { 1436,  1437 }, // glPointParameterf and glPointParameterfARB
        { 1436,  1438 }, // glPointParameterf and glPointParameterfEXT
        { 1436,  1439 }, // glPointParameterf and glPointParameterfSGIS
        { 1437,  1436 }, // glPointParameterfARB and glPointParameterf
        { 1437,  1438 }, // glPointParameterfARB and glPointParameterfEXT
        { 1437,  1439 }, // glPointParameterfARB and glPointParameterfSGIS
        { 1438,  1436 }, // glPointParameterfEXT and glPointParameterf
        { 1438,  1437 }, // glPointParameterfEXT and glPointParameterfARB
        { 1438,  1439 }, // glPointParameterfEXT and glPointParameterfSGIS
        { 1439,  1436 }, // glPointParameterfSGIS and glPointParameterf
        { 1439,  1437 }, // glPointParameterfSGIS and glPointParameterfARB
        { 1439,  1438 }, // glPointParameterfSGIS and glPointParameterfEXT
        { 1440,  1441 }, // glPointParameterfv and glPointParameterfvARB
        { 1440,  1442 }, // glPointParameterfv and glPointParameterfvEXT
        { 1440,  1443 }, // glPointParameterfv and glPointParameterfvSGIS
        { 1441,  1440 }, // glPointParameterfvARB and glPointParameterfv
        { 1441,  1442 }, // glPointParameterfvARB and glPointParameterfvEXT
        { 1441,  1443 }, // glPointParameterfvARB and glPointParameterfvSGIS
        { 1442,  1440 }, // glPointParameterfvEXT and glPointParameterfv
        { 1442,  1441 }, // glPointParameterfvEXT and glPointParameterfvARB
        { 1442,  1443 }, // glPointParameterfvEXT and glPointParameterfvSGIS
        { 1443,  1440 }, // glPointParameterfvSGIS and glPointParameterfv
        { 1443,  1441 }, // glPointParameterfvSGIS and glPointParameterfvARB
        { 1443,  1442 }, // glPointParameterfvSGIS and glPointParameterfvEXT
        { 1444,  1445 }, // glPointParameteri and glPointParameteriNV
        { 1445,  1444 }, // glPointParameteriNV and glPointParameteri
        { 1446,  1447 }, // glPointParameteriv and glPointParameterivNV
        { 1447,  1446 }, // glPointParameterivNV and glPointParameteriv
        { 1453,  2794 }, // glPolygonMode and glPolygonModeNV
        { 2794,  1453 }, // glPolygonModeNV and glPolygonMode
        { 1455,  1456 }, // glPolygonOffsetClamp and glPolygonOffsetClampEXT
        { 1456,  1455 }, // glPolygonOffsetClampEXT and glPolygonOffsetClamp
        { 1459,  2795 }, // glPopDebugGroup and glPopDebugGroupKHR
        { 2795,  1459 }, // glPopDebugGroupKHR and glPopDebugGroup
        { 2796,  1463 }, // glPrimitiveBoundingBox and glPrimitiveBoundingBoxARB
        { 2796,  2797 }, // glPrimitiveBoundingBox and glPrimitiveBoundingBoxEXT
        { 2796,  2798 }, // glPrimitiveBoundingBox and glPrimitiveBoundingBoxOES
        { 1463,  2796 }, // glPrimitiveBoundingBoxARB and glPrimitiveBoundingBox
        { 1463,  2797 }, // glPrimitiveBoundingBoxARB and glPrimitiveBoundingBoxEXT
        { 1463,  2798 }, // glPrimitiveBoundingBoxARB and glPrimitiveBoundingBoxOES
        { 2797,  2796 }, // glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBox
        { 2797,  1463 }, // glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBoxARB
        { 2797,  2798 }, // glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBoxOES
        { 2798,  2796 }, // glPrimitiveBoundingBoxOES and glPrimitiveBoundingBox
        { 2798,  1463 }, // glPrimitiveBoundingBoxOES and glPrimitiveBoundingBoxARB
        { 2798,  2797 }, // glPrimitiveBoundingBoxOES and glPrimitiveBoundingBoxEXT
        { 1469,  2799 }, // glProgramBinary and glProgramBinaryOES
        { 2799,  1469 }, // glProgramBinaryOES and glProgramBinary
        { 1503,  1504 }, // glProgramParameteri and glProgramParameteriARB
        { 1503,  1505 }, // glProgramParameteri and glProgramParameteriEXT
        { 1504,  1503 }, // glProgramParameteriARB and glProgramParameteri
        { 1504,  1505 }, // glProgramParameteriARB and glProgramParameteriEXT
        { 1505,  1503 }, // glProgramParameteriEXT and glProgramParameteri
        { 1505,  1504 }, // glProgramParameteriEXT and glProgramParameteriARB
        { 1515,  1516 }, // glProgramUniform1f and glProgramUniform1fEXT
        { 1516,  1515 }, // glProgramUniform1fEXT and glProgramUniform1f
        { 1517,  1518 }, // glProgramUniform1fv and glProgramUniform1fvEXT
        { 1518,  1517 }, // glProgramUniform1fvEXT and glProgramUniform1fv
        { 1519,  1524 }, // glProgramUniform1i and glProgramUniform1iEXT
        { 1524,  1519 }, // glProgramUniform1iEXT and glProgramUniform1i
        { 1525,  1526 }, // glProgramUniform1iv and glProgramUniform1ivEXT
        { 1526,  1525 }, // glProgramUniform1ivEXT and glProgramUniform1iv
        { 1527,  1532 }, // glProgramUniform1ui and glProgramUniform1uiEXT
        { 1532,  1527 }, // glProgramUniform1uiEXT and glProgramUniform1ui
        { 1533,  1534 }, // glProgramUniform1uiv and glProgramUniform1uivEXT
        { 1534,  1533 }, // glProgramUniform1uivEXT and glProgramUniform1uiv
        { 1539,  1540 }, // glProgramUniform2f and glProgramUniform2fEXT
        { 1540,  1539 }, // glProgramUniform2fEXT and glProgramUniform2f
        { 1541,  1542 }, // glProgramUniform2fv and glProgramUniform2fvEXT
        { 1542,  1541 }, // glProgramUniform2fvEXT and glProgramUniform2fv
        { 1543,  1548 }, // glProgramUniform2i and glProgramUniform2iEXT
        { 1548,  1543 }, // glProgramUniform2iEXT and glProgramUniform2i
        { 1549,  1550 }, // glProgramUniform2iv and glProgramUniform2ivEXT
        { 1550,  1549 }, // glProgramUniform2ivEXT and glProgramUniform2iv
        { 1551,  1556 }, // glProgramUniform2ui and glProgramUniform2uiEXT
        { 1556,  1551 }, // glProgramUniform2uiEXT and glProgramUniform2ui
        { 1557,  1558 }, // glProgramUniform2uiv and glProgramUniform2uivEXT
        { 1558,  1557 }, // glProgramUniform2uivEXT and glProgramUniform2uiv
        { 1563,  1564 }, // glProgramUniform3f and glProgramUniform3fEXT
        { 1564,  1563 }, // glProgramUniform3fEXT and glProgramUniform3f
        { 1565,  1566 }, // glProgramUniform3fv and glProgramUniform3fvEXT
        { 1566,  1565 }, // glProgramUniform3fvEXT and glProgramUniform3fv
        { 1567,  1572 }, // glProgramUniform3i and glProgramUniform3iEXT
        { 1572,  1567 }, // glProgramUniform3iEXT and glProgramUniform3i
        { 1573,  1574 }, // glProgramUniform3iv and glProgramUniform3ivEXT
        { 1574,  1573 }, // glProgramUniform3ivEXT and glProgramUniform3iv
        { 1575,  1580 }, // glProgramUniform3ui and glProgramUniform3uiEXT
        { 1580,  1575 }, // glProgramUniform3uiEXT and glProgramUniform3ui
        { 1581,  1582 }, // glProgramUniform3uiv and glProgramUniform3uivEXT
        { 1582,  1581 }, // glProgramUniform3uivEXT and glProgramUniform3uiv
        { 1587,  1588 }, // glProgramUniform4f and glProgramUniform4fEXT
        { 1588,  1587 }, // glProgramUniform4fEXT and glProgramUniform4f
        { 1589,  1590 }, // glProgramUniform4fv and glProgramUniform4fvEXT
        { 1590,  1589 }, // glProgramUniform4fvEXT and glProgramUniform4fv
        { 1591,  1596 }, // glProgramUniform4i and glProgramUniform4iEXT
        { 1596,  1591 }, // glProgramUniform4iEXT and glProgramUniform4i
        { 1597,  1598 }, // glProgramUniform4iv and glProgramUniform4ivEXT
        { 1598,  1597 }, // glProgramUniform4ivEXT and glProgramUniform4iv
        { 1599,  1604 }, // glProgramUniform4ui and glProgramUniform4uiEXT
        { 1604,  1599 }, // glProgramUniform4uiEXT and glProgramUniform4ui
        { 1605,  1606 }, // glProgramUniform4uiv and glProgramUniform4uivEXT
        { 1606,  1605 }, // glProgramUniform4uivEXT and glProgramUniform4uiv
        { 1607,  2800 }, // glProgramUniformHandleui64ARB and glProgramUniformHandleui64IMG
        { 2800,  1607 }, // glProgramUniformHandleui64IMG and glProgramUniformHandleui64ARB
        { 1609,  2801 }, // glProgramUniformHandleui64vARB and glProgramUniformHandleui64vIMG
        { 2801,  1609 }, // glProgramUniformHandleui64vIMG and glProgramUniformHandleui64vARB
        { 1613,  1614 }, // glProgramUniformMatrix2fv and glProgramUniformMatrix2fvEXT
        { 1614,  1613 }, // glProgramUniformMatrix2fvEXT and glProgramUniformMatrix2fv
        { 1617,  1618 }, // glProgramUniformMatrix2x3fv and glProgramUniformMatrix2x3fvEXT
        { 1618,  1617 }, // glProgramUniformMatrix2x3fvEXT and glProgramUniformMatrix2x3fv
        { 1621,  1622 }, // glProgramUniformMatrix2x4fv and glProgramUniformMatrix2x4fvEXT
        { 1622,  1621 }, // glProgramUniformMatrix2x4fvEXT and glProgramUniformMatrix2x4fv
        { 1625,  1626 }, // glProgramUniformMatrix3fv and glProgramUniformMatrix3fvEXT
        { 1626,  1625 }, // glProgramUniformMatrix3fvEXT and glProgramUniformMatrix3fv
        { 1629,  1630 }, // glProgramUniformMatrix3x2fv and glProgramUniformMatrix3x2fvEXT
        { 1630,  1629 }, // glProgramUniformMatrix3x2fvEXT and glProgramUniformMatrix3x2fv
        { 1633,  1634 }, // glProgramUniformMatrix3x4fv and glProgramUniformMatrix3x4fvEXT
        { 1634,  1633 }, // glProgramUniformMatrix3x4fvEXT and glProgramUniformMatrix3x4fv
        { 1637,  1638 }, // glProgramUniformMatrix4fv and glProgramUniformMatrix4fvEXT
        { 1638,  1637 }, // glProgramUniformMatrix4fvEXT and glProgramUniformMatrix4fv
        { 1641,  1642 }, // glProgramUniformMatrix4x2fv and glProgramUniformMatrix4x2fvEXT
        { 1642,  1641 }, // glProgramUniformMatrix4x2fvEXT and glProgramUniformMatrix4x2fv
        { 1645,  1646 }, // glProgramUniformMatrix4x3fv and glProgramUniformMatrix4x3fvEXT
        { 1646,  1645 }, // glProgramUniformMatrix4x3fvEXT and glProgramUniformMatrix4x3fv
        { 1650,  2802 }, // glProvokingVertex and glProvokingVertexANGLE
        { 1650,  1651 }, // glProvokingVertex and glProvokingVertexEXT
        { 2802,  1650 }, // glProvokingVertexANGLE and glProvokingVertex
        { 2802,  1651 }, // glProvokingVertexANGLE and glProvokingVertexEXT
        { 1651,  1650 }, // glProvokingVertexEXT and glProvokingVertex
        { 1651,  2802 }, // glProvokingVertexEXT and glProvokingVertexANGLE
        { 1653,  2803 }, // glPushDebugGroup and glPushDebugGroupKHR
        { 2803,  1653 }, // glPushDebugGroupKHR and glPushDebugGroup
        { 1655,  2804 }, // glQueryCounter and glQueryCounterEXT
        { 2804,  1655 }, // glQueryCounterEXT and glQueryCounter
        { 1670,  1671 }, // glReadnPixels and glReadnPixelsARB
        { 1670,  2808 }, // glReadnPixels and glReadnPixelsEXT
        { 1670,  2809 }, // glReadnPixels and glReadnPixelsKHR
        { 1671,  1670 }, // glReadnPixelsARB and glReadnPixels
        { 1671,  2808 }, // glReadnPixelsARB and glReadnPixelsEXT
        { 1671,  2809 }, // glReadnPixelsARB and glReadnPixelsKHR
        { 2808,  1670 }, // glReadnPixelsEXT and glReadnPixels
        { 2808,  1671 }, // glReadnPixelsEXT and glReadnPixelsARB
        { 2808,  2809 }, // glReadnPixelsEXT and glReadnPixelsKHR
        { 2809,  1670 }, // glReadnPixelsKHR and glReadnPixels
        { 2809,  1671 }, // glReadnPixelsKHR and glReadnPixelsARB
        { 2809,  2808 }, // glReadnPixelsKHR and glReadnPixelsEXT
        { 1678,  1679 }, // glRenderbufferStorage and glRenderbufferStorageEXT
        { 1679,  1678 }, // glRenderbufferStorageEXT and glRenderbufferStorage
        { 1680,  1683 }, // glRenderbufferStorageMultisample and glRenderbufferStorageMultisampleEXT
        { 1680,  2815 }, // glRenderbufferStorageMultisample and glRenderbufferStorageMultisampleNV
        { 1683,  1680 }, // glRenderbufferStorageMultisampleEXT and glRenderbufferStorageMultisample
        { 1683,  2815 }, // glRenderbufferStorageMultisampleEXT and glRenderbufferStorageMultisampleNV
        { 2815,  1680 }, // glRenderbufferStorageMultisampleNV and glRenderbufferStorageMultisample
        { 2815,  1683 }, // glRenderbufferStorageMultisampleNV and glRenderbufferStorageMultisampleEXT
        { 1713,  1714 }, // glResumeTransformFeedback and glResumeTransformFeedbackNV
        { 1714,  1713 }, // glResumeTransformFeedbackNV and glResumeTransformFeedback
        { 1716,  1717 }, // glSampleCoverage and glSampleCoverageARB
        { 1717,  1716 }, // glSampleCoverageARB and glSampleCoverage
        { 1719,  1721 }, // glSampleMaskEXT and glSampleMaskSGIS
        { 1721,  1719 }, // glSampleMaskSGIS and glSampleMaskEXT
        { 1723,  1724 }, // glSamplePatternEXT and glSamplePatternSGIS
        { 1724,  1723 }, // glSamplePatternSGIS and glSamplePatternEXT
        { 1725,  2819 }, // glSamplerParameterIiv and glSamplerParameterIivEXT
        { 1725,  2820 }, // glSamplerParameterIiv and glSamplerParameterIivOES
        { 2819,  1725 }, // glSamplerParameterIivEXT and glSamplerParameterIiv
        { 2819,  2820 }, // glSamplerParameterIivEXT and glSamplerParameterIivOES
        { 2820,  1725 }, // glSamplerParameterIivOES and glSamplerParameterIiv
        { 2820,  2819 }, // glSamplerParameterIivOES and glSamplerParameterIivEXT
        { 1726,  2822 }, // glSamplerParameterIuiv and glSamplerParameterIuivEXT
        { 1726,  2823 }, // glSamplerParameterIuiv and glSamplerParameterIuivOES
        { 2822,  1726 }, // glSamplerParameterIuivEXT and glSamplerParameterIuiv
        { 2822,  2823 }, // glSamplerParameterIuivEXT and glSamplerParameterIuivOES
        { 2823,  1726 }, // glSamplerParameterIuivOES and glSamplerParameterIuiv
        { 2823,  2822 }, // glSamplerParameterIuivOES and glSamplerParameterIuivEXT
        { 1733,  2827 }, // glScissorArrayv and glScissorArrayvNV
        { 1733,  2828 }, // glScissorArrayv and glScissorArrayvOES
        { 2827,  1733 }, // glScissorArrayvNV and glScissorArrayv
        { 2827,  2828 }, // glScissorArrayvNV and glScissorArrayvOES
        { 2828,  1733 }, // glScissorArrayvOES and glScissorArrayv
        { 2828,  2827 }, // glScissorArrayvOES and glScissorArrayvNV
        { 1736,  2829 }, // glScissorIndexed and glScissorIndexedNV
        { 1736,  2830 }, // glScissorIndexed and glScissorIndexedOES
        { 2829,  1736 }, // glScissorIndexedNV and glScissorIndexed
        { 2829,  2830 }, // glScissorIndexedNV and glScissorIndexedOES
        { 2830,  1736 }, // glScissorIndexedOES and glScissorIndexed
        { 2830,  2829 }, // glScissorIndexedOES and glScissorIndexedNV
        { 1737,  2831 }, // glScissorIndexedv and glScissorIndexedvNV
        { 1737,  2832 }, // glScissorIndexedv and glScissorIndexedvOES
        { 2831,  1737 }, // glScissorIndexedvNV and glScissorIndexedv
        { 2831,  2832 }, // glScissorIndexedvNV and glScissorIndexedvOES
        { 2832,  1737 }, // glScissorIndexedvOES and glScissorIndexedv
        { 2832,  2831 }, // glScissorIndexedvOES and glScissorIndexedvNV
        { 1773,  1774 }, // glShaderSource and glShaderSourceARB
        { 1774,  1773 }, // glShaderSourceARB and glShaderSource
        { 1785,  1786 }, // glSpecializeShader and glSpecializeShaderARB
        { 1786,  1785 }, // glSpecializeShaderARB and glSpecializeShader
        { 1802,  1803 }, // glStencilOpSeparate and glStencilOpSeparateATI
        { 1803,  1802 }, // glStencilOpSeparateATI and glStencilOpSeparate
        { 1835,  1836 }, // glTexBuffer and glTexBufferARB
        { 1835,  1837 }, // glTexBuffer and glTexBufferEXT
        { 1835,  2837 }, // glTexBuffer and glTexBufferOES
        { 1836,  1835 }, // glTexBufferARB and glTexBuffer
        { 1836,  1837 }, // glTexBufferARB and glTexBufferEXT
        { 1836,  2837 }, // glTexBufferARB and glTexBufferOES
        { 1837,  1835 }, // glTexBufferEXT and glTexBuffer
        { 1837,  1836 }, // glTexBufferEXT and glTexBufferARB
        { 1837,  2837 }, // glTexBufferEXT and glTexBufferOES
        { 2837,  1835 }, // glTexBufferOES and glTexBuffer
        { 2837,  1836 }, // glTexBufferOES and glTexBufferARB
        { 2837,  1837 }, // glTexBufferOES and glTexBufferEXT
        { 1838,  2838 }, // glTexBufferRange and glTexBufferRangeEXT
        { 1838,  2839 }, // glTexBufferRange and glTexBufferRangeOES
        { 2838,  1838 }, // glTexBufferRangeEXT and glTexBufferRange
        { 2838,  2839 }, // glTexBufferRangeEXT and glTexBufferRangeOES
        { 2839,  1838 }, // glTexBufferRangeOES and glTexBufferRange
        { 2839,  2838 }, // glTexBufferRangeOES and glTexBufferRangeEXT
        { 1893,  1894 }, // glTexImage3D and glTexImage3DEXT
        { 1894,  1893 }, // glTexImage3DEXT and glTexImage3D
        { 1898,  2845 }, // glTexPageCommitmentARB and glTexPageCommitmentEXT
        { 2845,  1898 }, // glTexPageCommitmentEXT and glTexPageCommitmentARB
        { 1900,  1901 }, // glTexParameterIiv and glTexParameterIivEXT
        { 1900,  2846 }, // glTexParameterIiv and glTexParameterIivOES
        { 1901,  1900 }, // glTexParameterIivEXT and glTexParameterIiv
        { 1901,  2846 }, // glTexParameterIivEXT and glTexParameterIivOES
        { 2846,  1900 }, // glTexParameterIivOES and glTexParameterIiv
        { 2846,  1901 }, // glTexParameterIivOES and glTexParameterIivEXT
        { 1902,  1903 }, // glTexParameterIuiv and glTexParameterIuivEXT
        { 1902,  2848 }, // glTexParameterIuiv and glTexParameterIuivOES
        { 1903,  1902 }, // glTexParameterIuivEXT and glTexParameterIuiv
        { 1903,  2848 }, // glTexParameterIuivEXT and glTexParameterIuivOES
        { 2848,  1902 }, // glTexParameterIuivOES and glTexParameterIuiv
        { 2848,  1903 }, // glTexParameterIuivOES and glTexParameterIuivEXT
        { 1911,  1912 }, // glTexStorage1D and glTexStorage1DEXT
        { 1912,  1911 }, // glTexStorage1DEXT and glTexStorage1D
        { 1913,  1914 }, // glTexStorage2D and glTexStorage2DEXT
        { 1914,  1913 }, // glTexStorage2DEXT and glTexStorage2D
        { 1916,  1917 }, // glTexStorage3D and glTexStorage3DEXT
        { 1917,  1916 }, // glTexStorage3DEXT and glTexStorage3D
        { 1918,  2853 }, // glTexStorage3DMultisample and glTexStorage3DMultisampleOES
        { 2853,  1918 }, // glTexStorage3DMultisampleOES and glTexStorage3DMultisample
        { 1929,  1930 }, // glTexSubImage1D and glTexSubImage1DEXT
        { 1930,  1929 }, // glTexSubImage1DEXT and glTexSubImage1D
        { 1931,  1932 }, // glTexSubImage2D and glTexSubImage2DEXT
        { 1932,  1931 }, // glTexSubImage2DEXT and glTexSubImage2D
        { 1933,  1934 }, // glTexSubImage3D and glTexSubImage3DEXT
        { 1934,  1933 }, // glTexSubImage3DEXT and glTexSubImage3D
        { 1992,  2860 }, // glTextureView and glTextureViewEXT
        { 1992,  2861 }, // glTextureView and glTextureViewOES
        { 2860,  1992 }, // glTextureViewEXT and glTextureView
        { 2860,  2861 }, // glTextureViewEXT and glTextureViewOES
        { 2861,  1992 }, // glTextureViewOES and glTextureView
        { 2861,  2860 }, // glTextureViewOES and glTextureViewEXT
        { 1998,  1999 }, // glTransformFeedbackVaryings and glTransformFeedbackVaryingsEXT
        { 1999,  1998 }, // glTransformFeedbackVaryingsEXT and glTransformFeedbackVaryings
        { 2005,  2006 }, // glUniform1f and glUniform1fARB
        { 2006,  2005 }, // glUniform1fARB and glUniform1f
        { 2007,  2008 }, // glUniform1fv and glUniform1fvARB
        { 2008,  2007 }, // glUniform1fvARB and glUniform1fv
        { 2009,  2014 }, // glUniform1i and glUniform1iARB
        { 2014,  2009 }, // glUniform1iARB and glUniform1i
        { 2015,  2016 }, // glUniform1iv and glUniform1ivARB
        { 2016,  2015 }, // glUniform1ivARB and glUniform1iv
        { 2017,  2022 }, // glUniform1ui and glUniform1uiEXT
        { 2022,  2017 }, // glUniform1uiEXT and glUniform1ui
        { 2023,  2024 }, // glUniform1uiv and glUniform1uivEXT
        { 2024,  2023 }, // glUniform1uivEXT and glUniform1uiv
        { 2027,  2028 }, // glUniform2f and glUniform2fARB
        { 2028,  2027 }, // glUniform2fARB and glUniform2f
        { 2029,  2030 }, // glUniform2fv and glUniform2fvARB
        { 2030,  2029 }, // glUniform2fvARB and glUniform2fv
        { 2031,  2036 }, // glUniform2i and glUniform2iARB
        { 2036,  2031 }, // glUniform2iARB and glUniform2i
        { 2037,  2038 }, // glUniform2iv and glUniform2ivARB
        { 2038,  2037 }, // glUniform2ivARB and glUniform2iv
        { 2039,  2044 }, // glUniform2ui and glUniform2uiEXT
        { 2044,  2039 }, // glUniform2uiEXT and glUniform2ui
        { 2045,  2046 }, // glUniform2uiv and glUniform2uivEXT
        { 2046,  2045 }, // glUniform2uivEXT and glUniform2uiv
        { 2049,  2050 }, // glUniform3f and glUniform3fARB
        { 2050,  2049 }, // glUniform3fARB and glUniform3f
        { 2051,  2052 }, // glUniform3fv and glUniform3fvARB
        { 2052,  2051 }, // glUniform3fvARB and glUniform3fv
        { 2053,  2058 }, // glUniform3i and glUniform3iARB
        { 2058,  2053 }, // glUniform3iARB and glUniform3i
        { 2059,  2060 }, // glUniform3iv and glUniform3ivARB
        { 2060,  2059 }, // glUniform3ivARB and glUniform3iv
        { 2061,  2066 }, // glUniform3ui and glUniform3uiEXT
        { 2066,  2061 }, // glUniform3uiEXT and glUniform3ui
        { 2067,  2068 }, // glUniform3uiv and glUniform3uivEXT
        { 2068,  2067 }, // glUniform3uivEXT and glUniform3uiv
        { 2071,  2072 }, // glUniform4f and glUniform4fARB
        { 2072,  2071 }, // glUniform4fARB and glUniform4f
        { 2073,  2074 }, // glUniform4fv and glUniform4fvARB
        { 2074,  2073 }, // glUniform4fvARB and glUniform4fv
        { 2075,  2080 }, // glUniform4i and glUniform4iARB
        { 2080,  2075 }, // glUniform4iARB and glUniform4i
        { 2081,  2082 }, // glUniform4iv and glUniform4ivARB
        { 2082,  2081 }, // glUniform4ivARB and glUniform4iv
        { 2083,  2088 }, // glUniform4ui and glUniform4uiEXT
        { 2088,  2083 }, // glUniform4uiEXT and glUniform4ui
        { 2089,  2090 }, // glUniform4uiv and glUniform4uivEXT
        { 2090,  2089 }, // glUniform4uivEXT and glUniform4uiv
        { 2093,  2862 }, // glUniformHandleui64ARB and glUniformHandleui64IMG
        { 2862,  2093 }, // glUniformHandleui64IMG and glUniformHandleui64ARB
        { 2095,  2863 }, // glUniformHandleui64vARB and glUniformHandleui64vIMG
        { 2863,  2095 }, // glUniformHandleui64vIMG and glUniformHandleui64vARB
        { 2098,  2099 }, // glUniformMatrix2fv and glUniformMatrix2fvARB
        { 2099,  2098 }, // glUniformMatrix2fvARB and glUniformMatrix2fv
        { 2101,  2864 }, // glUniformMatrix2x3fv and glUniformMatrix2x3fvNV
        { 2864,  2101 }, // glUniformMatrix2x3fvNV and glUniformMatrix2x3fv
        { 2103,  2865 }, // glUniformMatrix2x4fv and glUniformMatrix2x4fvNV
        { 2865,  2103 }, // glUniformMatrix2x4fvNV and glUniformMatrix2x4fv
        { 2105,  2106 }, // glUniformMatrix3fv and glUniformMatrix3fvARB
        { 2106,  2105 }, // glUniformMatrix3fvARB and glUniformMatrix3fv
        { 2108,  2866 }, // glUniformMatrix3x2fv and glUniformMatrix3x2fvNV
        { 2866,  2108 }, // glUniformMatrix3x2fvNV and glUniformMatrix3x2fv
        { 2110,  2867 }, // glUniformMatrix3x4fv and glUniformMatrix3x4fvNV
        { 2867,  2110 }, // glUniformMatrix3x4fvNV and glUniformMatrix3x4fv
        { 2112,  2113 }, // glUniformMatrix4fv and glUniformMatrix4fvARB
        { 2113,  2112 }, // glUniformMatrix4fvARB and glUniformMatrix4fv
        { 2115,  2868 }, // glUniformMatrix4x2fv and glUniformMatrix4x2fvNV
        { 2868,  2115 }, // glUniformMatrix4x2fvNV and glUniformMatrix4x2fv
        { 2117,  2869 }, // glUniformMatrix4x3fv and glUniformMatrix4x3fvNV
        { 2869,  2117 }, // glUniformMatrix4x3fvNV and glUniformMatrix4x3fv
        { 2122,  2123 }, // glUnmapBuffer and glUnmapBufferARB
        { 2122,  2870 }, // glUnmapBuffer and glUnmapBufferOES
        { 2123,  2122 }, // glUnmapBufferARB and glUnmapBuffer
        { 2123,  2870 }, // glUnmapBufferARB and glUnmapBufferOES
        { 2870,  2122 }, // glUnmapBufferOES and glUnmapBuffer
        { 2870,  2123 }, // glUnmapBufferOES and glUnmapBufferARB
        { 2130,  2131 }, // glUseProgram and glUseProgramObjectARB
        { 2131,  2130 }, // glUseProgramObjectARB and glUseProgram
        { 2145,  2146 }, // glValidateProgram and glValidateProgramARB
        { 2146,  2145 }, // glValidateProgramARB and glValidateProgram
        { 2206,  2207 }, // glVertexAttrib1d and glVertexAttrib1dARB
        { 2206,  2208 }, // glVertexAttrib1d and glVertexAttrib1dNV
        { 2207,  2206 }, // glVertexAttrib1dARB and glVertexAttrib1d
        { 2207,  2208 }, // glVertexAttrib1dARB and glVertexAttrib1dNV
        { 2208,  2206 }, // glVertexAttrib1dNV and glVertexAttrib1d
        { 2208,  2207 }, // glVertexAttrib1dNV and glVertexAttrib1dARB
        { 2209,  2210 }, // glVertexAttrib1dv and glVertexAttrib1dvARB
        { 2209,  2211 }, // glVertexAttrib1dv and glVertexAttrib1dvNV
        { 2210,  2209 }, // glVertexAttrib1dvARB and glVertexAttrib1dv
        { 2210,  2211 }, // glVertexAttrib1dvARB and glVertexAttrib1dvNV
        { 2211,  2209 }, // glVertexAttrib1dvNV and glVertexAttrib1dv
        { 2211,  2210 }, // glVertexAttrib1dvNV and glVertexAttrib1dvARB
        { 2212,  2213 }, // glVertexAttrib1f and glVertexAttrib1fARB
        { 2212,  2214 }, // glVertexAttrib1f and glVertexAttrib1fNV
        { 2213,  2212 }, // glVertexAttrib1fARB and glVertexAttrib1f
        { 2213,  2214 }, // glVertexAttrib1fARB and glVertexAttrib1fNV
        { 2214,  2212 }, // glVertexAttrib1fNV and glVertexAttrib1f
        { 2214,  2213 }, // glVertexAttrib1fNV and glVertexAttrib1fARB
        { 2215,  2216 }, // glVertexAttrib1fv and glVertexAttrib1fvARB
        { 2215,  2217 }, // glVertexAttrib1fv and glVertexAttrib1fvNV
        { 2216,  2215 }, // glVertexAttrib1fvARB and glVertexAttrib1fv
        { 2216,  2217 }, // glVertexAttrib1fvARB and glVertexAttrib1fvNV
        { 2217,  2215 }, // glVertexAttrib1fvNV and glVertexAttrib1fv
        { 2217,  2216 }, // glVertexAttrib1fvNV and glVertexAttrib1fvARB
        { 2220,  2221 }, // glVertexAttrib1s and glVertexAttrib1sARB
        { 2220,  2222 }, // glVertexAttrib1s and glVertexAttrib1sNV
        { 2221,  2220 }, // glVertexAttrib1sARB and glVertexAttrib1s
        { 2221,  2222 }, // glVertexAttrib1sARB and glVertexAttrib1sNV
        { 2222,  2220 }, // glVertexAttrib1sNV and glVertexAttrib1s
        { 2222,  2221 }, // glVertexAttrib1sNV and glVertexAttrib1sARB
        { 2223,  2224 }, // glVertexAttrib1sv and glVertexAttrib1svARB
        { 2223,  2225 }, // glVertexAttrib1sv and glVertexAttrib1svNV
        { 2224,  2223 }, // glVertexAttrib1svARB and glVertexAttrib1sv
        { 2224,  2225 }, // glVertexAttrib1svARB and glVertexAttrib1svNV
        { 2225,  2223 }, // glVertexAttrib1svNV and glVertexAttrib1sv
        { 2225,  2224 }, // glVertexAttrib1svNV and glVertexAttrib1svARB
        { 2226,  2227 }, // glVertexAttrib2d and glVertexAttrib2dARB
        { 2226,  2228 }, // glVertexAttrib2d and glVertexAttrib2dNV
        { 2227,  2226 }, // glVertexAttrib2dARB and glVertexAttrib2d
        { 2227,  2228 }, // glVertexAttrib2dARB and glVertexAttrib2dNV
        { 2228,  2226 }, // glVertexAttrib2dNV and glVertexAttrib2d
        { 2228,  2227 }, // glVertexAttrib2dNV and glVertexAttrib2dARB
        { 2229,  2230 }, // glVertexAttrib2dv and glVertexAttrib2dvARB
        { 2229,  2231 }, // glVertexAttrib2dv and glVertexAttrib2dvNV
        { 2230,  2229 }, // glVertexAttrib2dvARB and glVertexAttrib2dv
        { 2230,  2231 }, // glVertexAttrib2dvARB and glVertexAttrib2dvNV
        { 2231,  2229 }, // glVertexAttrib2dvNV and glVertexAttrib2dv
        { 2231,  2230 }, // glVertexAttrib2dvNV and glVertexAttrib2dvARB
        { 2232,  2233 }, // glVertexAttrib2f and glVertexAttrib2fARB
        { 2232,  2234 }, // glVertexAttrib2f and glVertexAttrib2fNV
        { 2233,  2232 }, // glVertexAttrib2fARB and glVertexAttrib2f
        { 2233,  2234 }, // glVertexAttrib2fARB and glVertexAttrib2fNV
        { 2234,  2232 }, // glVertexAttrib2fNV and glVertexAttrib2f
        { 2234,  2233 }, // glVertexAttrib2fNV and glVertexAttrib2fARB
        { 2235,  2236 }, // glVertexAttrib2fv and glVertexAttrib2fvARB
        { 2235,  2237 }, // glVertexAttrib2fv and glVertexAttrib2fvNV
        { 2236,  2235 }, // glVertexAttrib2fvARB and glVertexAttrib2fv
        { 2236,  2237 }, // glVertexAttrib2fvARB and glVertexAttrib2fvNV
        { 2237,  2235 }, // glVertexAttrib2fvNV and glVertexAttrib2fv
        { 2237,  2236 }, // glVertexAttrib2fvNV and glVertexAttrib2fvARB
        { 2240,  2241 }, // glVertexAttrib2s and glVertexAttrib2sARB
        { 2240,  2242 }, // glVertexAttrib2s and glVertexAttrib2sNV
        { 2241,  2240 }, // glVertexAttrib2sARB and glVertexAttrib2s
        { 2241,  2242 }, // glVertexAttrib2sARB and glVertexAttrib2sNV
        { 2242,  2240 }, // glVertexAttrib2sNV and glVertexAttrib2s
        { 2242,  2241 }, // glVertexAttrib2sNV and glVertexAttrib2sARB
        { 2243,  2244 }, // glVertexAttrib2sv and glVertexAttrib2svARB
        { 2243,  2245 }, // glVertexAttrib2sv and glVertexAttrib2svNV
        { 2244,  2243 }, // glVertexAttrib2svARB and glVertexAttrib2sv
        { 2244,  2245 }, // glVertexAttrib2svARB and glVertexAttrib2svNV
        { 2245,  2243 }, // glVertexAttrib2svNV and glVertexAttrib2sv
        { 2245,  2244 }, // glVertexAttrib2svNV and glVertexAttrib2svARB
        { 2246,  2247 }, // glVertexAttrib3d and glVertexAttrib3dARB
        { 2246,  2248 }, // glVertexAttrib3d and glVertexAttrib3dNV
        { 2247,  2246 }, // glVertexAttrib3dARB and glVertexAttrib3d
        { 2247,  2248 }, // glVertexAttrib3dARB and glVertexAttrib3dNV
        { 2248,  2246 }, // glVertexAttrib3dNV and glVertexAttrib3d
        { 2248,  2247 }, // glVertexAttrib3dNV and glVertexAttrib3dARB
        { 2249,  2250 }, // glVertexAttrib3dv and glVertexAttrib3dvARB
        { 2249,  2251 }, // glVertexAttrib3dv and glVertexAttrib3dvNV
        { 2250,  2249 }, // glVertexAttrib3dvARB and glVertexAttrib3dv
        { 2250,  2251 }, // glVertexAttrib3dvARB and glVertexAttrib3dvNV
        { 2251,  2249 }, // glVertexAttrib3dvNV and glVertexAttrib3dv
        { 2251,  2250 }, // glVertexAttrib3dvNV and glVertexAttrib3dvARB
        { 2252,  2253 }, // glVertexAttrib3f and glVertexAttrib3fARB
        { 2252,  2254 }, // glVertexAttrib3f and glVertexAttrib3fNV
        { 2253,  2252 }, // glVertexAttrib3fARB and glVertexAttrib3f
        { 2253,  2254 }, // glVertexAttrib3fARB and glVertexAttrib3fNV
        { 2254,  2252 }, // glVertexAttrib3fNV and glVertexAttrib3f
        { 2254,  2253 }, // glVertexAttrib3fNV and glVertexAttrib3fARB
        { 2255,  2256 }, // glVertexAttrib3fv and glVertexAttrib3fvARB
        { 2255,  2257 }, // glVertexAttrib3fv and glVertexAttrib3fvNV
        { 2256,  2255 }, // glVertexAttrib3fvARB and glVertexAttrib3fv
        { 2256,  2257 }, // glVertexAttrib3fvARB and glVertexAttrib3fvNV
        { 2257,  2255 }, // glVertexAttrib3fvNV and glVertexAttrib3fv
        { 2257,  2256 }, // glVertexAttrib3fvNV and glVertexAttrib3fvARB
        { 2260,  2261 }, // glVertexAttrib3s and glVertexAttrib3sARB
        { 2260,  2262 }, // glVertexAttrib3s and glVertexAttrib3sNV
        { 2261,  2260 }, // glVertexAttrib3sARB and glVertexAttrib3s
        { 2261,  2262 }, // glVertexAttrib3sARB and glVertexAttrib3sNV
        { 2262,  2260 }, // glVertexAttrib3sNV and glVertexAttrib3s
        { 2262,  2261 }, // glVertexAttrib3sNV and glVertexAttrib3sARB
        { 2263,  2264 }, // glVertexAttrib3sv and glVertexAttrib3svARB
        { 2263,  2265 }, // glVertexAttrib3sv and glVertexAttrib3svNV
        { 2264,  2263 }, // glVertexAttrib3svARB and glVertexAttrib3sv
        { 2264,  2265 }, // glVertexAttrib3svARB and glVertexAttrib3svNV
        { 2265,  2263 }, // glVertexAttrib3svNV and glVertexAttrib3sv
        { 2265,  2264 }, // glVertexAttrib3svNV and glVertexAttrib3svARB
        { 2280,  2281 }, // glVertexAttrib4bv and glVertexAttrib4bvARB
        { 2281,  2280 }, // glVertexAttrib4bvARB and glVertexAttrib4bv
        { 2282,  2283 }, // glVertexAttrib4d and glVertexAttrib4dARB
        { 2282,  2284 }, // glVertexAttrib4d and glVertexAttrib4dNV
        { 2283,  2282 }, // glVertexAttrib4dARB and glVertexAttrib4d
        { 2283,  2284 }, // glVertexAttrib4dARB and glVertexAttrib4dNV
        { 2284,  2282 }, // glVertexAttrib4dNV and glVertexAttrib4d
        { 2284,  2283 }, // glVertexAttrib4dNV and glVertexAttrib4dARB
        { 2285,  2286 }, // glVertexAttrib4dv and glVertexAttrib4dvARB
        { 2285,  2287 }, // glVertexAttrib4dv and glVertexAttrib4dvNV
        { 2286,  2285 }, // glVertexAttrib4dvARB and glVertexAttrib4dv
        { 2286,  2287 }, // glVertexAttrib4dvARB and glVertexAttrib4dvNV
        { 2287,  2285 }, // glVertexAttrib4dvNV and glVertexAttrib4dv
        { 2287,  2286 }, // glVertexAttrib4dvNV and glVertexAttrib4dvARB
        { 2288,  2289 }, // glVertexAttrib4f and glVertexAttrib4fARB
        { 2288,  2290 }, // glVertexAttrib4f and glVertexAttrib4fNV
        { 2289,  2288 }, // glVertexAttrib4fARB and glVertexAttrib4f
        { 2289,  2290 }, // glVertexAttrib4fARB and glVertexAttrib4fNV
        { 2290,  2288 }, // glVertexAttrib4fNV and glVertexAttrib4f
        { 2290,  2289 }, // glVertexAttrib4fNV and glVertexAttrib4fARB
        { 2291,  2292 }, // glVertexAttrib4fv and glVertexAttrib4fvARB
        { 2291,  2293 }, // glVertexAttrib4fv and glVertexAttrib4fvNV
        { 2292,  2291 }, // glVertexAttrib4fvARB and glVertexAttrib4fv
        { 2292,  2293 }, // glVertexAttrib4fvARB and glVertexAttrib4fvNV
        { 2293,  2291 }, // glVertexAttrib4fvNV and glVertexAttrib4fv
        { 2293,  2292 }, // glVertexAttrib4fvNV and glVertexAttrib4fvARB
        { 2296,  2297 }, // glVertexAttrib4iv and glVertexAttrib4ivARB
        { 2297,  2296 }, // glVertexAttrib4ivARB and glVertexAttrib4iv
        { 2266,  2267 }, // glVertexAttrib4Nbv and glVertexAttrib4NbvARB
        { 2267,  2266 }, // glVertexAttrib4NbvARB and glVertexAttrib4Nbv
        { 2268,  2269 }, // glVertexAttrib4Niv and glVertexAttrib4NivARB
        { 2269,  2268 }, // glVertexAttrib4NivARB and glVertexAttrib4Niv
        { 2270,  2271 }, // glVertexAttrib4Nsv and glVertexAttrib4NsvARB
        { 2271,  2270 }, // glVertexAttrib4NsvARB and glVertexAttrib4Nsv
        { 2272,  2273 }, // glVertexAttrib4Nub and glVertexAttrib4NubARB
        { 2272,  2304 }, // glVertexAttrib4Nub and glVertexAttrib4ubNV
        { 2273,  2272 }, // glVertexAttrib4NubARB and glVertexAttrib4Nub
        { 2273,  2304 }, // glVertexAttrib4NubARB and glVertexAttrib4ubNV
        { 2274,  2275 }, // glVertexAttrib4Nubv and glVertexAttrib4NubvARB
        { 2274,  2307 }, // glVertexAttrib4Nubv and glVertexAttrib4ubvNV
        { 2275,  2274 }, // glVertexAttrib4NubvARB and glVertexAttrib4Nubv
        { 2275,  2307 }, // glVertexAttrib4NubvARB and glVertexAttrib4ubvNV
        { 2276,  2277 }, // glVertexAttrib4Nuiv and glVertexAttrib4NuivARB
        { 2277,  2276 }, // glVertexAttrib4NuivARB and glVertexAttrib4Nuiv
        { 2278,  2279 }, // glVertexAttrib4Nusv and glVertexAttrib4NusvARB
        { 2279,  2278 }, // glVertexAttrib4NusvARB and glVertexAttrib4Nusv
        { 2298,  2299 }, // glVertexAttrib4s and glVertexAttrib4sARB
        { 2298,  2300 }, // glVertexAttrib4s and glVertexAttrib4sNV
        { 2299,  2298 }, // glVertexAttrib4sARB and glVertexAttrib4s
        { 2299,  2300 }, // glVertexAttrib4sARB and glVertexAttrib4sNV
        { 2300,  2298 }, // glVertexAttrib4sNV and glVertexAttrib4s
        { 2300,  2299 }, // glVertexAttrib4sNV and glVertexAttrib4sARB
        { 2301,  2302 }, // glVertexAttrib4sv and glVertexAttrib4svARB
        { 2301,  2303 }, // glVertexAttrib4sv and glVertexAttrib4svNV
        { 2302,  2301 }, // glVertexAttrib4svARB and glVertexAttrib4sv
        { 2302,  2303 }, // glVertexAttrib4svARB and glVertexAttrib4svNV
        { 2303,  2301 }, // glVertexAttrib4svNV and glVertexAttrib4sv
        { 2303,  2302 }, // glVertexAttrib4svNV and glVertexAttrib4svARB
        { 2304,  2272 }, // glVertexAttrib4ubNV and glVertexAttrib4Nub
        { 2304,  2273 }, // glVertexAttrib4ubNV and glVertexAttrib4NubARB
        { 2305,  2306 }, // glVertexAttrib4ubv and glVertexAttrib4ubvARB
        { 2306,  2305 }, // glVertexAttrib4ubvARB and glVertexAttrib4ubv
        { 2307,  2274 }, // glVertexAttrib4ubvNV and glVertexAttrib4Nubv
        { 2307,  2275 }, // glVertexAttrib4ubvNV and glVertexAttrib4NubvARB
        { 2308,  2309 }, // glVertexAttrib4uiv and glVertexAttrib4uivARB
        { 2309,  2308 }, // glVertexAttrib4uivARB and glVertexAttrib4uiv
        { 2310,  2311 }, // glVertexAttrib4usv and glVertexAttrib4usvARB
        { 2311,  2310 }, // glVertexAttrib4usvARB and glVertexAttrib4usv
        { 2314,  2873 }, // glVertexAttribDivisor and glVertexAttribDivisorANGLE
        { 2314,  2315 }, // glVertexAttribDivisor and glVertexAttribDivisorARB
        { 2314,  2874 }, // glVertexAttribDivisor and glVertexAttribDivisorEXT
        { 2314,  2875 }, // glVertexAttribDivisor and glVertexAttribDivisorNV
        { 2873,  2314 }, // glVertexAttribDivisorANGLE and glVertexAttribDivisor
        { 2873,  2315 }, // glVertexAttribDivisorANGLE and glVertexAttribDivisorARB
        { 2873,  2874 }, // glVertexAttribDivisorANGLE and glVertexAttribDivisorEXT
        { 2873,  2875 }, // glVertexAttribDivisorANGLE and glVertexAttribDivisorNV
        { 2315,  2314 }, // glVertexAttribDivisorARB and glVertexAttribDivisor
        { 2315,  2873 }, // glVertexAttribDivisorARB and glVertexAttribDivisorANGLE
        { 2315,  2874 }, // glVertexAttribDivisorARB and glVertexAttribDivisorEXT
        { 2315,  2875 }, // glVertexAttribDivisorARB and glVertexAttribDivisorNV
        { 2874,  2314 }, // glVertexAttribDivisorEXT and glVertexAttribDivisor
        { 2874,  2873 }, // glVertexAttribDivisorEXT and glVertexAttribDivisorANGLE
        { 2874,  2315 }, // glVertexAttribDivisorEXT and glVertexAttribDivisorARB
        { 2874,  2875 }, // glVertexAttribDivisorEXT and glVertexAttribDivisorNV
        { 2875,  2314 }, // glVertexAttribDivisorNV and glVertexAttribDivisor
        { 2875,  2873 }, // glVertexAttribDivisorNV and glVertexAttribDivisorANGLE
        { 2875,  2315 }, // glVertexAttribDivisorNV and glVertexAttribDivisorARB
        { 2875,  2874 }, // glVertexAttribDivisorNV and glVertexAttribDivisorEXT
        { 2318,  2319 }, // glVertexAttribI1i and glVertexAttribI1iEXT
        { 2319,  2318 }, // glVertexAttribI1iEXT and glVertexAttribI1i
        { 2320,  2321 }, // glVertexAttribI1iv and glVertexAttribI1ivEXT
        { 2321,  2320 }, // glVertexAttribI1ivEXT and glVertexAttribI1iv
        { 2322,  2323 }, // glVertexAttribI1ui and glVertexAttribI1uiEXT
        { 2323,  2322 }, // glVertexAttribI1uiEXT and glVertexAttribI1ui
        { 2324,  2325 }, // glVertexAttribI1uiv and glVertexAttribI1uivEXT
        { 2325,  2324 }, // glVertexAttribI1uivEXT and glVertexAttribI1uiv
        { 2326,  2327 }, // glVertexAttribI2i and glVertexAttribI2iEXT
        { 2327,  2326 }, // glVertexAttribI2iEXT and glVertexAttribI2i
        { 2328,  2329 }, // glVertexAttribI2iv and glVertexAttribI2ivEXT
        { 2329,  2328 }, // glVertexAttribI2ivEXT and glVertexAttribI2iv
        { 2330,  2331 }, // glVertexAttribI2ui and glVertexAttribI2uiEXT
        { 2331,  2330 }, // glVertexAttribI2uiEXT and glVertexAttribI2ui
        { 2332,  2333 }, // glVertexAttribI2uiv and glVertexAttribI2uivEXT
        { 2333,  2332 }, // glVertexAttribI2uivEXT and glVertexAttribI2uiv
        { 2334,  2335 }, // glVertexAttribI3i and glVertexAttribI3iEXT
        { 2335,  2334 }, // glVertexAttribI3iEXT and glVertexAttribI3i
        { 2336,  2337 }, // glVertexAttribI3iv and glVertexAttribI3ivEXT
        { 2337,  2336 }, // glVertexAttribI3ivEXT and glVertexAttribI3iv
        { 2338,  2339 }, // glVertexAttribI3ui and glVertexAttribI3uiEXT
        { 2339,  2338 }, // glVertexAttribI3uiEXT and glVertexAttribI3ui
        { 2340,  2341 }, // glVertexAttribI3uiv and glVertexAttribI3uivEXT
        { 2341,  2340 }, // glVertexAttribI3uivEXT and glVertexAttribI3uiv
        { 2342,  2343 }, // glVertexAttribI4bv and glVertexAttribI4bvEXT
        { 2343,  2342 }, // glVertexAttribI4bvEXT and glVertexAttribI4bv
        { 2344,  2345 }, // glVertexAttribI4i and glVertexAttribI4iEXT
        { 2345,  2344 }, // glVertexAttribI4iEXT and glVertexAttribI4i
        { 2346,  2347 }, // glVertexAttribI4iv and glVertexAttribI4ivEXT
        { 2347,  2346 }, // glVertexAttribI4ivEXT and glVertexAttribI4iv
        { 2348,  2349 }, // glVertexAttribI4sv and glVertexAttribI4svEXT
        { 2349,  2348 }, // glVertexAttribI4svEXT and glVertexAttribI4sv
        { 2350,  2351 }, // glVertexAttribI4ubv and glVertexAttribI4ubvEXT
        { 2351,  2350 }, // glVertexAttribI4ubvEXT and glVertexAttribI4ubv
        { 2352,  2353 }, // glVertexAttribI4ui and glVertexAttribI4uiEXT
        { 2353,  2352 }, // glVertexAttribI4uiEXT and glVertexAttribI4ui
        { 2354,  2355 }, // glVertexAttribI4uiv and glVertexAttribI4uivEXT
        { 2355,  2354 }, // glVertexAttribI4uivEXT and glVertexAttribI4uiv
        { 2356,  2357 }, // glVertexAttribI4usv and glVertexAttribI4usvEXT
        { 2357,  2356 }, // glVertexAttribI4usvEXT and glVertexAttribI4usv
        { 2360,  2361 }, // glVertexAttribIPointer and glVertexAttribIPointerEXT
        { 2361,  2360 }, // glVertexAttribIPointerEXT and glVertexAttribIPointer
        { 2362,  2363 }, // glVertexAttribL1d and glVertexAttribL1dEXT
        { 2363,  2362 }, // glVertexAttribL1dEXT and glVertexAttribL1d
        { 2364,  2365 }, // glVertexAttribL1dv and glVertexAttribL1dvEXT
        { 2365,  2364 }, // glVertexAttribL1dvEXT and glVertexAttribL1dv
        { 2372,  2373 }, // glVertexAttribL2d and glVertexAttribL2dEXT
        { 2373,  2372 }, // glVertexAttribL2dEXT and glVertexAttribL2d
        { 2374,  2375 }, // glVertexAttribL2dv and glVertexAttribL2dvEXT
        { 2375,  2374 }, // glVertexAttribL2dvEXT and glVertexAttribL2dv
        { 2380,  2381 }, // glVertexAttribL3d and glVertexAttribL3dEXT
        { 2381,  2380 }, // glVertexAttribL3dEXT and glVertexAttribL3d
        { 2382,  2383 }, // glVertexAttribL3dv and glVertexAttribL3dvEXT
        { 2383,  2382 }, // glVertexAttribL3dvEXT and glVertexAttribL3dv
        { 2388,  2389 }, // glVertexAttribL4d and glVertexAttribL4dEXT
        { 2389,  2388 }, // glVertexAttribL4dEXT and glVertexAttribL4d
        { 2390,  2391 }, // glVertexAttribL4dv and glVertexAttribL4dvEXT
        { 2391,  2390 }, // glVertexAttribL4dvEXT and glVertexAttribL4dv
        { 2398,  2399 }, // glVertexAttribLPointer and glVertexAttribLPointerEXT
        { 2399,  2398 }, // glVertexAttribLPointerEXT and glVertexAttribLPointer
        { 2409,  2410 }, // glVertexAttribPointer and glVertexAttribPointerARB
        { 2410,  2409 }, // glVertexAttribPointerARB and glVertexAttribPointer
        { 2479,  2876 }, // glViewportArrayv and glViewportArrayvNV
        { 2479,  2877 }, // glViewportArrayv and glViewportArrayvOES
        { 2876,  2479 }, // glViewportArrayvNV and glViewportArrayv
        { 2876,  2877 }, // glViewportArrayvNV and glViewportArrayvOES
        { 2877,  2479 }, // glViewportArrayvOES and glViewportArrayv
        { 2877,  2876 }, // glViewportArrayvOES and glViewportArrayvNV
        { 2480,  2878 }, // glViewportIndexedf and glViewportIndexedfNV
        { 2480,  2879 }, // glViewportIndexedf and glViewportIndexedfOES
        { 2878,  2480 }, // glViewportIndexedfNV and glViewportIndexedf
        { 2878,  2879 }, // glViewportIndexedfNV and glViewportIndexedfOES
        { 2879,  2480 }, // glViewportIndexedfOES and glViewportIndexedf
        { 2879,  2878 }, // glViewportIndexedfOES and glViewportIndexedfNV
        { 2481,  2880 }, // glViewportIndexedfv and glViewportIndexedfvNV
        { 2481,  2881 }, // glViewportIndexedfv and glViewportIndexedfvOES
        { 2880,  2481 }, // glViewportIndexedfvNV and glViewportIndexedfv
        { 2880,  2881 }, // glViewportIndexedfvNV and glViewportIndexedfvOES
        { 2881,  2481 }, // glViewportIndexedfvOES and glViewportIndexedfv
        { 2881,  2880 }, // glViewportIndexedfvOES and glViewportIndexedfvNV
        { 2486,  2882 }, // glWaitSync and glWaitSyncAPPLE
        { 2882,  2486 }, // glWaitSyncAPPLE and glWaitSync
        { 0xFFFF, 0xFFFF }
    };

    void **pfnArray = context->pfnArray;

    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(s_aliases) - 1; ++i) {
        const GladAliasPair_t *pAlias = &s_aliases[i];
        if (pfnArray[pAlias->first] == NULL && pfnArray[pAlias->second] != NULL) {
            pfnArray[pAlias->first] = pfnArray[pAlias->second];
        } else if (pfnArray[pAlias->second] == NULL && pfnArray[pAlias->first] != NULL) {
            pfnArray[pAlias->second] = pfnArray[pAlias->first];
        }
    }
}

#if defined(GL_ES_VERSION_3_0) || defined(GL_VERSION_3_0)
#define GLAD_GL_IS_SOME_NEW_VERSION 1
#else
#define GLAD_GL_IS_SOME_NEW_VERSION 0
#endif

static int glad_gl_get_extensions(GladGLContext *context, int version, const char **out_exts, unsigned int *out_num_exts_i, char ***out_exts_i) {
#if GLAD_GL_IS_SOME_NEW_VERSION
    if(GLAD_VERSION_MAJOR(version) < 3) {
#else
    GLAD_UNUSED(version);
    GLAD_UNUSED(out_num_exts_i);
    GLAD_UNUSED(out_exts_i);
#endif
        if (context->GetString == NULL) {
            return 0;
        }
        *out_exts = (const char *)context->GetString(GL_EXTENSIONS);
#if GLAD_GL_IS_SOME_NEW_VERSION
    } else {
        unsigned int index = 0;
        unsigned int num_exts_i = 0;
        char **exts_i = NULL;
        if (context->GetStringi == NULL || context->GetIntegerv == NULL) {
            return 0;
        }
        context->GetIntegerv(GL_NUM_EXTENSIONS, (int*) &num_exts_i);
        if (num_exts_i > 0) {
            exts_i = (char **) malloc(num_exts_i * (sizeof *exts_i));
        }
        if (exts_i == NULL) {
            return 0;
        }
        for(index = 0; index < num_exts_i; index++) {
            const char *gl_str_tmp = (const char*) context->GetStringi(GL_EXTENSIONS, index);
            size_t len = strlen(gl_str_tmp) + 1;

            char *local_str = (char*) malloc(len * sizeof(char));
            if(local_str != NULL) {
                memcpy(local_str, gl_str_tmp, len * sizeof(char));
            }

            exts_i[index] = local_str;
        }

        *out_num_exts_i = num_exts_i;
        *out_exts_i = exts_i;
    }
#endif
    return 1;
}
static void glad_gl_free_extensions(char **exts_i, unsigned int num_exts_i) {
    if (exts_i != NULL) {
        unsigned int index;
        for(index = 0; index < num_exts_i; index++) {
            free((void *) (exts_i[index]));
        }
        free((void *)exts_i);
        exts_i = NULL;
    }
}
static int glad_gl_has_extension(int version, const char *exts, unsigned int num_exts_i, char **exts_i, const char *ext) {
    if(GLAD_VERSION_MAJOR(version) < 3 || !GLAD_GL_IS_SOME_NEW_VERSION) {
        const char *extensions;
        const char *loc;
        const char *terminator;
        extensions = exts;
        if(extensions == NULL || ext == NULL) {
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
    } else {
        unsigned int index;
        for(index = 0; index < num_exts_i; index++) {
            const char *e = exts_i[index];
            if(strcmp(e, ext) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

static GLADapiproc glad_gl_get_proc_from_userptr(void *userptr, const char* name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_gl_find_extensions_gl(GladGLContext *context, int version) {
    const char *exts = NULL;
    unsigned int num_exts_i = 0;
    char **exts_i = NULL;
    if (!glad_gl_get_extensions(context, version, &exts, &num_exts_i, &exts_i)) return 0;

    static uint16_t extIdx[] = {
             1, // GL_3DFX_tbuffer
             5, // GL_AMD_debug_output
             7, // GL_AMD_draw_buffers_blend
             8, // GL_AMD_framebuffer_multisample_advanced
             9, // GL_AMD_framebuffer_sample_positions
            13, // GL_AMD_gpu_shader_int64
            14, // GL_AMD_interleaved_elements
            15, // GL_AMD_multi_draw_indirect
            16, // GL_AMD_name_gen_delete
            17, // GL_AMD_occlusion_query_event
            18, // GL_AMD_performance_monitor
            21, // GL_AMD_sample_positions
            31, // GL_AMD_sparse_texture
            32, // GL_AMD_stencil_operation_extended
            38, // GL_AMD_vertex_shader_tessellator
            40, // GL_ANGLE_memory_object_flags
            41, // GL_ANGLE_memory_object_fuchsia
            42, // GL_ANGLE_semaphore_fuchsia
            44, // GL_ANGLE_texture_external_update
            47, // GL_APPLE_element_array
            48, // GL_APPLE_fence
            50, // GL_APPLE_flush_buffer_range
            51, // GL_APPLE_object_purgeable
            55, // GL_APPLE_texture_range
            57, // GL_APPLE_vertex_array_object
            58, // GL_APPLE_vertex_array_range
            59, // GL_APPLE_vertex_program_evaluators
            61, // GL_ARB_ES2_compatibility
            62, // GL_ARB_ES3_1_compatibility
            63, // GL_ARB_ES3_2_compatibility
            66, // GL_ARB_base_instance
            67, // GL_ARB_bindless_texture
            68, // GL_ARB_blend_func_extended
            69, // GL_ARB_buffer_storage
            70, // GL_ARB_cl_event
            71, // GL_ARB_clear_buffer_object
            72, // GL_ARB_clear_texture
            73, // GL_ARB_clip_control
            74, // GL_ARB_color_buffer_float
            77, // GL_ARB_compute_shader
            78, // GL_ARB_compute_variable_group_size
            81, // GL_ARB_copy_buffer
            82, // GL_ARB_copy_image
            84, // GL_ARB_debug_output
            89, // GL_ARB_direct_state_access
            90, // GL_ARB_draw_buffers
            91, // GL_ARB_draw_buffers_blend
            92, // GL_ARB_draw_elements_base_vertex
            93, // GL_ARB_draw_indirect
            94, // GL_ARB_draw_instanced
           100, // GL_ARB_fragment_program
           104, // GL_ARB_framebuffer_no_attachments
           105, // GL_ARB_framebuffer_object
           107, // GL_ARB_geometry_shader4
           108, // GL_ARB_get_program_binary
           109, // GL_ARB_get_texture_sub_image
           110, // GL_ARB_gl_spirv
           112, // GL_ARB_gpu_shader_fp64
           113, // GL_ARB_gpu_shader_int64
           116, // GL_ARB_imaging
           117, // GL_ARB_indirect_parameters
           118, // GL_ARB_instanced_arrays
           119, // GL_ARB_internalformat_query
           120, // GL_ARB_internalformat_query2
           121, // GL_ARB_invalidate_subdata
           123, // GL_ARB_map_buffer_range
           124, // GL_ARB_matrix_palette
           125, // GL_ARB_multi_bind
           126, // GL_ARB_multi_draw_indirect
           127, // GL_ARB_multisample
           128, // GL_ARB_multitexture
           129, // GL_ARB_occlusion_query
           131, // GL_ARB_parallel_shader_compile
           134, // GL_ARB_point_parameters
           136, // GL_ARB_polygon_offset_clamp
           138, // GL_ARB_program_interface_query
           139, // GL_ARB_provoking_vertex
           142, // GL_ARB_robustness
           144, // GL_ARB_sample_locations
           145, // GL_ARB_sample_shading
           146, // GL_ARB_sampler_objects
           149, // GL_ARB_separate_shader_objects
           151, // GL_ARB_shader_atomic_counters
           157, // GL_ARB_shader_image_load_store
           159, // GL_ARB_shader_objects
           162, // GL_ARB_shader_storage_buffer_object
           163, // GL_ARB_shader_subroutine
           169, // GL_ARB_shading_language_include
           173, // GL_ARB_sparse_buffer
           174, // GL_ARB_sparse_texture
           179, // GL_ARB_sync
           180, // GL_ARB_tessellation_shader
           181, // GL_ARB_texture_barrier
           183, // GL_ARB_texture_buffer_object
           185, // GL_ARB_texture_buffer_range
           186, // GL_ARB_texture_compression
           201, // GL_ARB_texture_multisample
           209, // GL_ARB_texture_storage
           210, // GL_ARB_texture_storage_multisample
           212, // GL_ARB_texture_view
           213, // GL_ARB_timer_query
           214, // GL_ARB_transform_feedback2
           215, // GL_ARB_transform_feedback3
           216, // GL_ARB_transform_feedback_instanced
           218, // GL_ARB_transpose_matrix
           219, // GL_ARB_uniform_buffer_object
           221, // GL_ARB_vertex_array_object
           222, // GL_ARB_vertex_attrib_64bit
           223, // GL_ARB_vertex_attrib_binding
           224, // GL_ARB_vertex_blend
           225, // GL_ARB_vertex_buffer_object
           226, // GL_ARB_vertex_program
           227, // GL_ARB_vertex_shader
           229, // GL_ARB_vertex_type_2_10_10_10_rev
           230, // GL_ARB_viewport_array
           231, // GL_ARB_window_pos
           232, // GL_ATI_draw_buffers
           233, // GL_ATI_element_array
           234, // GL_ATI_envmap_bumpmap
           235, // GL_ATI_fragment_shader
           236, // GL_ATI_map_object_buffer
           239, // GL_ATI_pn_triangles
           240, // GL_ATI_separate_stencil
           245, // GL_ATI_vertex_array_object
           246, // GL_ATI_vertex_attrib_array_object
           247, // GL_ATI_vertex_streams
           249, // GL_EXT_EGL_image_storage
           253, // GL_EXT_bindable_uniform
           254, // GL_EXT_blend_color
           255, // GL_EXT_blend_equation_separate
           256, // GL_EXT_blend_func_separate
           258, // GL_EXT_blend_minmax
           264, // GL_EXT_color_subtable
           265, // GL_EXT_compiled_vertex_array
           267, // GL_EXT_convolution
           268, // GL_EXT_coordinate_frame
           269, // GL_EXT_copy_texture
           270, // GL_EXT_cull_vertex
           271, // GL_EXT_debug_label
           272, // GL_EXT_debug_marker
           275, // GL_EXT_depth_bounds_test
           277, // GL_EXT_direct_state_access
           278, // GL_EXT_draw_buffers2
           279, // GL_EXT_draw_instanced
           280, // GL_EXT_draw_range_elements
           281, // GL_EXT_external_buffer
           282, // GL_EXT_fog_coord
           285, // GL_EXT_framebuffer_blit
           286, // GL_EXT_framebuffer_blit_layers
           287, // GL_EXT_framebuffer_multisample
           289, // GL_EXT_framebuffer_object
           291, // GL_EXT_geometry_shader4
           292, // GL_EXT_gpu_program_parameters
           293, // GL_EXT_gpu_shader4
           294, // GL_EXT_histogram
           296, // GL_EXT_index_func
           297, // GL_EXT_index_material
           299, // GL_EXT_light_texture
           300, // GL_EXT_memory_object
           301, // GL_EXT_memory_object_fd
           302, // GL_EXT_memory_object_win32
           304, // GL_EXT_multi_draw_arrays
           305, // GL_EXT_multisample
           313, // GL_EXT_paletted_texture
           315, // GL_EXT_pixel_transform
           317, // GL_EXT_point_parameters
           318, // GL_EXT_polygon_offset
           319, // GL_EXT_polygon_offset_clamp
           321, // GL_EXT_provoking_vertex
           322, // GL_EXT_raster_multisample
           330, // GL_EXT_secondary_color
           331, // GL_EXT_semaphore
           332, // GL_EXT_semaphore_fd
           333, // GL_EXT_semaphore_win32
           334, // GL_EXT_separate_shader_objects
           340, // GL_EXT_shader_framebuffer_fetch_non_coherent
           343, // GL_EXT_shader_image_load_store
           352, // GL_EXT_stencil_clear_tag
           353, // GL_EXT_stencil_two_side
           357, // GL_EXT_subtexture
           359, // GL_EXT_texture3D
           360, // GL_EXT_texture_array
           361, // GL_EXT_texture_buffer_object
           371, // GL_EXT_texture_integer
           374, // GL_EXT_texture_object
           375, // GL_EXT_texture_perturb_normal
           383, // GL_EXT_texture_storage
           385, // GL_EXT_timer_query
           386, // GL_EXT_transform_feedback
           387, // GL_EXT_vertex_array
           389, // GL_EXT_vertex_attrib_64bit
           390, // GL_EXT_vertex_shader
           391, // GL_EXT_vertex_weighting
           393, // GL_EXT_win32_keyed_mutex
           394, // GL_EXT_window_rectangles
           395, // GL_EXT_x11_sync_object
           396, // GL_GREMEDY_frame_terminator
           397, // GL_GREMEDY_string_marker
           399, // GL_HP_image_transform
           404, // GL_IBM_multimode_draw_arrays
           406, // GL_IBM_static_data
           408, // GL_IBM_vertex_array_lists
           409, // GL_INGR_blend_func_separate
           415, // GL_INTEL_framebuffer_CMAA
           416, // GL_INTEL_map_texture
           417, // GL_INTEL_parallel_arrays
           418, // GL_INTEL_performance_query
           419, // GL_KHR_blend_equation_advanced
           422, // GL_KHR_debug
           425, // GL_KHR_parallel_shader_compile
           427, // GL_KHR_robustness
           435, // GL_MESA_framebuffer_flip_y
           439, // GL_MESA_resize_buffers
           442, // GL_MESA_window_pos
           445, // GL_NVX_conditional_render
           447, // GL_NVX_gpu_multicast2
           448, // GL_NVX_linked_gpu_multicast
           450, // GL_NVX_progress_fence
           451, // GL_NV_alpha_to_coverage_dither_control
           452, // GL_NV_bindless_multi_draw_indirect
           453, // GL_NV_bindless_multi_draw_indirect_count
           454, // GL_NV_bindless_texture
           455, // GL_NV_blend_equation_advanced
           459, // GL_NV_clip_space_w_scaling
           460, // GL_NV_command_list
           463, // GL_NV_conditional_render
           464, // GL_NV_conservative_raster
           465, // GL_NV_conservative_raster_dilate
           467, // GL_NV_conservative_raster_pre_snap_triangles
           471, // GL_NV_copy_image
           473, // GL_NV_depth_buffer_float
           475, // GL_NV_draw_texture
           476, // GL_NV_draw_vulkan_image
           477, // GL_NV_evaluators
           478, // GL_NV_explicit_multisample
           479, // GL_NV_fence
           483, // GL_NV_fragment_coverage_to_color
           484, // GL_NV_fragment_program
           490, // GL_NV_framebuffer_mixed_samples
           491, // GL_NV_framebuffer_multisample_coverage
           492, // GL_NV_geometry_program4
           495, // GL_NV_gpu_multicast
           496, // GL_NV_gpu_program4
           497, // GL_NV_gpu_program5
           499, // GL_NV_gpu_shader5
           500, // GL_NV_half_float
           501, // GL_NV_internalformat_sample_query
           503, // GL_NV_memory_attachment
           504, // GL_NV_memory_object_sparse
           505, // GL_NV_mesh_shader
           508, // GL_NV_occlusion_query
           510, // GL_NV_parameter_buffer_object
           512, // GL_NV_path_rendering
           514, // GL_NV_pixel_data_range
           515, // GL_NV_point_sprite
           516, // GL_NV_present_video
           517, // GL_NV_primitive_restart
           519, // GL_NV_query_resource
           520, // GL_NV_query_resource_tag
           523, // GL_NV_register_combiners
           524, // GL_NV_register_combiners2
           527, // GL_NV_sample_locations
           529, // GL_NV_scissor_exclusive
           535, // GL_NV_shader_buffer_load
           543, // GL_NV_shading_rate_image
           548, // GL_NV_texture_barrier
           552, // GL_NV_texture_multisample
           558, // GL_NV_timeline_semaphore
           559, // GL_NV_transform_feedback
           560, // GL_NV_transform_feedback2
           563, // GL_NV_vdpau_interop
           564, // GL_NV_vdpau_interop2
           565, // GL_NV_vertex_array_range
           567, // GL_NV_vertex_attrib_integer_64bit
           568, // GL_NV_vertex_buffer_unified_memory
           569, // GL_NV_vertex_program
           574, // GL_NV_vertex_program4
           575, // GL_NV_video_capture
           577, // GL_NV_viewport_swizzle
           578, // GL_OES_byte_coordinates
           580, // GL_OES_fixed_point
           581, // GL_OES_query_matrix
           583, // GL_OES_single_precision
           587, // GL_OVR_multiview
           589, // GL_PGI_misc_hints
           593, // GL_SGIS_detail_texture
           594, // GL_SGIS_fog_function
           596, // GL_SGIS_multisample
           597, // GL_SGIS_pixel_texture
           599, // GL_SGIS_point_parameters
           600, // GL_SGIS_sharpen_texture
           601, // GL_SGIS_texture4D
           603, // GL_SGIS_texture_color_mask
           605, // GL_SGIS_texture_filter4
           608, // GL_SGIX_async
           617, // GL_SGIX_flush_raster
           619, // GL_SGIX_fragment_lighting
           620, // GL_SGIX_framezoom
           621, // GL_SGIX_igloo_interface
           622, // GL_SGIX_instruments
           625, // GL_SGIX_list_priority
           626, // GL_SGIX_pixel_texture
           628, // GL_SGIX_polynomial_ffd
           629, // GL_SGIX_reference_plane
           634, // GL_SGIX_sprite
           636, // GL_SGIX_tag_sample_buffer
           647, // GL_SGI_color_table
           649, // GL_SUNX_constant_data
           651, // GL_SUN_global_alpha
           652, // GL_SUN_mesh_array
           654, // GL_SUN_triangle_list
           655, // GL_SUN_vertex
        0xFFFF
    };

    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(extIdx) - 1; ++i)
        context->extArray[extIdx[i]] = glad_gl_has_extension(version, exts, num_exts_i, exts_i, glad_ext_names[extIdx[i]]);

    glad_gl_free_extensions(exts_i, num_exts_i);

    return 1;
}

static int glad_gl_find_core_gl(GladGLContext *context) {
    int i;
    const char* version;
    const char* prefixes[] = {
        "OpenGL ES-CM ",
        "OpenGL ES-CL ",
        "OpenGL ES ",
        "OpenGL SC ",
        NULL
    };
    int major = 0;
    int minor = 0;
    version = (const char*) context->GetString(GL_VERSION);
    if (!version) return 0;
    for (i = 0;  prefixes[i];  i++) {
        const size_t length = strlen(prefixes[i]);
        if (strncmp(version, prefixes[i], length) == 0) {
            version += length;
            break;
        }
    }

    GLAD_IMPL_UTIL_SSCANF(version, "%d.%d", &major, &minor);

    context->VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
    context->VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
    context->VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
    context->VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;
    context->VERSION_1_4 = (major == 1 && minor >= 4) || major > 1;
    context->VERSION_1_5 = (major == 1 && minor >= 5) || major > 1;
    context->VERSION_2_0 = (major == 2 && minor >= 0) || major > 2;
    context->VERSION_2_1 = (major == 2 && minor >= 1) || major > 2;
    context->VERSION_3_0 = (major == 3 && minor >= 0) || major > 3;
    context->VERSION_3_1 = (major == 3 && minor >= 1) || major > 3;
    context->VERSION_3_2 = (major == 3 && minor >= 2) || major > 3;
    context->VERSION_3_3 = (major == 3 && minor >= 3) || major > 3;
    context->VERSION_4_0 = (major == 4 && minor >= 0) || major > 4;
    context->VERSION_4_1 = (major == 4 && minor >= 1) || major > 4;
    context->VERSION_4_2 = (major == 4 && minor >= 2) || major > 4;
    context->VERSION_4_3 = (major == 4 && minor >= 3) || major > 4;
    context->VERSION_4_4 = (major == 4 && minor >= 4) || major > 4;
    context->VERSION_4_5 = (major == 4 && minor >= 5) || major > 4;
    context->VERSION_4_6 = (major == 4 && minor >= 6) || major > 4;

    return GLAD_MAKE_VERSION(major, minor);
}

int gladLoadGLContextUserPtr(GladGLContext *context, GLADuserptrloadfunc load, void *userptr) {
    int version;

    context->GetString = (PFNGLGETSTRINGPROC) load(userptr, "glGetString");
    if(context->GetString == NULL) return 0;
    if(context->GetString(GL_VERSION) == NULL) return 0;
    version = glad_gl_find_core_gl(context);

    glad_gl_load_GL_VERSION_1_0(context, load, userptr);
    glad_gl_load_GL_VERSION_1_1(context, load, userptr);
    glad_gl_load_GL_VERSION_1_2(context, load, userptr);
    glad_gl_load_GL_VERSION_1_3(context, load, userptr);
    glad_gl_load_GL_VERSION_1_4(context, load, userptr);
    glad_gl_load_GL_VERSION_1_5(context, load, userptr);
    glad_gl_load_GL_VERSION_2_0(context, load, userptr);
    glad_gl_load_GL_VERSION_2_1(context, load, userptr);
    glad_gl_load_GL_VERSION_3_0(context, load, userptr);
    glad_gl_load_GL_VERSION_3_1(context, load, userptr);
    glad_gl_load_GL_VERSION_3_2(context, load, userptr);
    glad_gl_load_GL_VERSION_3_3(context, load, userptr);
    glad_gl_load_GL_VERSION_4_0(context, load, userptr);
    glad_gl_load_GL_VERSION_4_1(context, load, userptr);
    glad_gl_load_GL_VERSION_4_2(context, load, userptr);
    glad_gl_load_GL_VERSION_4_3(context, load, userptr);
    glad_gl_load_GL_VERSION_4_4(context, load, userptr);
    glad_gl_load_GL_VERSION_4_5(context, load, userptr);
    glad_gl_load_GL_VERSION_4_6(context, load, userptr);

    if (!glad_gl_find_extensions_gl(context, version)) return 0;
    glad_gl_load_GL_3DFX_tbuffer(context, load, userptr);
    glad_gl_load_GL_AMD_debug_output(context, load, userptr);
    glad_gl_load_GL_AMD_draw_buffers_blend(context, load, userptr);
    glad_gl_load_GL_AMD_framebuffer_multisample_advanced(context, load, userptr);
    glad_gl_load_GL_AMD_framebuffer_sample_positions(context, load, userptr);
    glad_gl_load_GL_AMD_gpu_shader_int64(context, load, userptr);
    glad_gl_load_GL_AMD_interleaved_elements(context, load, userptr);
    glad_gl_load_GL_AMD_multi_draw_indirect(context, load, userptr);
    glad_gl_load_GL_AMD_name_gen_delete(context, load, userptr);
    glad_gl_load_GL_AMD_occlusion_query_event(context, load, userptr);
    glad_gl_load_GL_AMD_performance_monitor(context, load, userptr);
    glad_gl_load_GL_AMD_sample_positions(context, load, userptr);
    glad_gl_load_GL_AMD_sparse_texture(context, load, userptr);
    glad_gl_load_GL_AMD_stencil_operation_extended(context, load, userptr);
    glad_gl_load_GL_AMD_vertex_shader_tessellator(context, load, userptr);
    glad_gl_load_GL_ANGLE_memory_object_flags(context, load, userptr);
    glad_gl_load_GL_ANGLE_memory_object_fuchsia(context, load, userptr);
    glad_gl_load_GL_ANGLE_semaphore_fuchsia(context, load, userptr);
    glad_gl_load_GL_ANGLE_texture_external_update(context, load, userptr);
    glad_gl_load_GL_APPLE_element_array(context, load, userptr);
    glad_gl_load_GL_APPLE_fence(context, load, userptr);
    glad_gl_load_GL_APPLE_flush_buffer_range(context, load, userptr);
    glad_gl_load_GL_APPLE_object_purgeable(context, load, userptr);
    glad_gl_load_GL_APPLE_texture_range(context, load, userptr);
    glad_gl_load_GL_APPLE_vertex_array_object(context, load, userptr);
    glad_gl_load_GL_APPLE_vertex_array_range(context, load, userptr);
    glad_gl_load_GL_APPLE_vertex_program_evaluators(context, load, userptr);
    glad_gl_load_GL_ARB_ES2_compatibility(context, load, userptr);
    glad_gl_load_GL_ARB_ES3_1_compatibility(context, load, userptr);
    glad_gl_load_GL_ARB_ES3_2_compatibility(context, load, userptr);
    glad_gl_load_GL_ARB_base_instance(context, load, userptr);
    glad_gl_load_GL_ARB_bindless_texture(context, load, userptr);
    glad_gl_load_GL_ARB_blend_func_extended(context, load, userptr);
    glad_gl_load_GL_ARB_buffer_storage(context, load, userptr);
    glad_gl_load_GL_ARB_cl_event(context, load, userptr);
    glad_gl_load_GL_ARB_clear_buffer_object(context, load, userptr);
    glad_gl_load_GL_ARB_clear_texture(context, load, userptr);
    glad_gl_load_GL_ARB_clip_control(context, load, userptr);
    glad_gl_load_GL_ARB_color_buffer_float(context, load, userptr);
    glad_gl_load_GL_ARB_compute_shader(context, load, userptr);
    glad_gl_load_GL_ARB_compute_variable_group_size(context, load, userptr);
    glad_gl_load_GL_ARB_copy_buffer(context, load, userptr);
    glad_gl_load_GL_ARB_copy_image(context, load, userptr);
    glad_gl_load_GL_ARB_debug_output(context, load, userptr);
    glad_gl_load_GL_ARB_direct_state_access(context, load, userptr);
    glad_gl_load_GL_ARB_draw_buffers(context, load, userptr);
    glad_gl_load_GL_ARB_draw_buffers_blend(context, load, userptr);
    glad_gl_load_GL_ARB_draw_elements_base_vertex(context, load, userptr);
    glad_gl_load_GL_ARB_draw_indirect(context, load, userptr);
    glad_gl_load_GL_ARB_draw_instanced(context, load, userptr);
    glad_gl_load_GL_ARB_fragment_program(context, load, userptr);
    glad_gl_load_GL_ARB_framebuffer_no_attachments(context, load, userptr);
    glad_gl_load_GL_ARB_framebuffer_object(context, load, userptr);
    glad_gl_load_GL_ARB_geometry_shader4(context, load, userptr);
    glad_gl_load_GL_ARB_get_program_binary(context, load, userptr);
    glad_gl_load_GL_ARB_get_texture_sub_image(context, load, userptr);
    glad_gl_load_GL_ARB_gl_spirv(context, load, userptr);
    glad_gl_load_GL_ARB_gpu_shader_fp64(context, load, userptr);
    glad_gl_load_GL_ARB_gpu_shader_int64(context, load, userptr);
    glad_gl_load_GL_ARB_imaging(context, load, userptr);
    glad_gl_load_GL_ARB_indirect_parameters(context, load, userptr);
    glad_gl_load_GL_ARB_instanced_arrays(context, load, userptr);
    glad_gl_load_GL_ARB_internalformat_query(context, load, userptr);
    glad_gl_load_GL_ARB_internalformat_query2(context, load, userptr);
    glad_gl_load_GL_ARB_invalidate_subdata(context, load, userptr);
    glad_gl_load_GL_ARB_map_buffer_range(context, load, userptr);
    glad_gl_load_GL_ARB_matrix_palette(context, load, userptr);
    glad_gl_load_GL_ARB_multi_bind(context, load, userptr);
    glad_gl_load_GL_ARB_multi_draw_indirect(context, load, userptr);
    glad_gl_load_GL_ARB_multisample(context, load, userptr);
    glad_gl_load_GL_ARB_multitexture(context, load, userptr);
    glad_gl_load_GL_ARB_occlusion_query(context, load, userptr);
    glad_gl_load_GL_ARB_parallel_shader_compile(context, load, userptr);
    glad_gl_load_GL_ARB_point_parameters(context, load, userptr);
    glad_gl_load_GL_ARB_polygon_offset_clamp(context, load, userptr);
    glad_gl_load_GL_ARB_program_interface_query(context, load, userptr);
    glad_gl_load_GL_ARB_provoking_vertex(context, load, userptr);
    glad_gl_load_GL_ARB_robustness(context, load, userptr);
    glad_gl_load_GL_ARB_sample_locations(context, load, userptr);
    glad_gl_load_GL_ARB_sample_shading(context, load, userptr);
    glad_gl_load_GL_ARB_sampler_objects(context, load, userptr);
    glad_gl_load_GL_ARB_separate_shader_objects(context, load, userptr);
    glad_gl_load_GL_ARB_shader_atomic_counters(context, load, userptr);
    glad_gl_load_GL_ARB_shader_image_load_store(context, load, userptr);
    glad_gl_load_GL_ARB_shader_objects(context, load, userptr);
    glad_gl_load_GL_ARB_shader_storage_buffer_object(context, load, userptr);
    glad_gl_load_GL_ARB_shader_subroutine(context, load, userptr);
    glad_gl_load_GL_ARB_shading_language_include(context, load, userptr);
    glad_gl_load_GL_ARB_sparse_buffer(context, load, userptr);
    glad_gl_load_GL_ARB_sparse_texture(context, load, userptr);
    glad_gl_load_GL_ARB_sync(context, load, userptr);
    glad_gl_load_GL_ARB_tessellation_shader(context, load, userptr);
    glad_gl_load_GL_ARB_texture_barrier(context, load, userptr);
    glad_gl_load_GL_ARB_texture_buffer_object(context, load, userptr);
    glad_gl_load_GL_ARB_texture_buffer_range(context, load, userptr);
    glad_gl_load_GL_ARB_texture_compression(context, load, userptr);
    glad_gl_load_GL_ARB_texture_multisample(context, load, userptr);
    glad_gl_load_GL_ARB_texture_storage(context, load, userptr);
    glad_gl_load_GL_ARB_texture_storage_multisample(context, load, userptr);
    glad_gl_load_GL_ARB_texture_view(context, load, userptr);
    glad_gl_load_GL_ARB_timer_query(context, load, userptr);
    glad_gl_load_GL_ARB_transform_feedback2(context, load, userptr);
    glad_gl_load_GL_ARB_transform_feedback3(context, load, userptr);
    glad_gl_load_GL_ARB_transform_feedback_instanced(context, load, userptr);
    glad_gl_load_GL_ARB_transpose_matrix(context, load, userptr);
    glad_gl_load_GL_ARB_uniform_buffer_object(context, load, userptr);
    glad_gl_load_GL_ARB_vertex_array_object(context, load, userptr);
    glad_gl_load_GL_ARB_vertex_attrib_64bit(context, load, userptr);
    glad_gl_load_GL_ARB_vertex_attrib_binding(context, load, userptr);
    glad_gl_load_GL_ARB_vertex_blend(context, load, userptr);
    glad_gl_load_GL_ARB_vertex_buffer_object(context, load, userptr);
    glad_gl_load_GL_ARB_vertex_program(context, load, userptr);
    glad_gl_load_GL_ARB_vertex_shader(context, load, userptr);
    glad_gl_load_GL_ARB_vertex_type_2_10_10_10_rev(context, load, userptr);
    glad_gl_load_GL_ARB_viewport_array(context, load, userptr);
    glad_gl_load_GL_ARB_window_pos(context, load, userptr);
    glad_gl_load_GL_ATI_draw_buffers(context, load, userptr);
    glad_gl_load_GL_ATI_element_array(context, load, userptr);
    glad_gl_load_GL_ATI_envmap_bumpmap(context, load, userptr);
    glad_gl_load_GL_ATI_fragment_shader(context, load, userptr);
    glad_gl_load_GL_ATI_map_object_buffer(context, load, userptr);
    glad_gl_load_GL_ATI_pn_triangles(context, load, userptr);
    glad_gl_load_GL_ATI_separate_stencil(context, load, userptr);
    glad_gl_load_GL_ATI_vertex_array_object(context, load, userptr);
    glad_gl_load_GL_ATI_vertex_attrib_array_object(context, load, userptr);
    glad_gl_load_GL_ATI_vertex_streams(context, load, userptr);
    glad_gl_load_GL_EXT_EGL_image_storage(context, load, userptr);
    glad_gl_load_GL_EXT_bindable_uniform(context, load, userptr);
    glad_gl_load_GL_EXT_blend_color(context, load, userptr);
    glad_gl_load_GL_EXT_blend_equation_separate(context, load, userptr);
    glad_gl_load_GL_EXT_blend_func_separate(context, load, userptr);
    glad_gl_load_GL_EXT_blend_minmax(context, load, userptr);
    glad_gl_load_GL_EXT_color_subtable(context, load, userptr);
    glad_gl_load_GL_EXT_compiled_vertex_array(context, load, userptr);
    glad_gl_load_GL_EXT_convolution(context, load, userptr);
    glad_gl_load_GL_EXT_coordinate_frame(context, load, userptr);
    glad_gl_load_GL_EXT_copy_texture(context, load, userptr);
    glad_gl_load_GL_EXT_cull_vertex(context, load, userptr);
    glad_gl_load_GL_EXT_debug_label(context, load, userptr);
    glad_gl_load_GL_EXT_debug_marker(context, load, userptr);
    glad_gl_load_GL_EXT_depth_bounds_test(context, load, userptr);
    glad_gl_load_GL_EXT_direct_state_access(context, load, userptr);
    glad_gl_load_GL_EXT_draw_buffers2(context, load, userptr);
    glad_gl_load_GL_EXT_draw_instanced(context, load, userptr);
    glad_gl_load_GL_EXT_draw_range_elements(context, load, userptr);
    glad_gl_load_GL_EXT_external_buffer(context, load, userptr);
    glad_gl_load_GL_EXT_fog_coord(context, load, userptr);
    glad_gl_load_GL_EXT_framebuffer_blit(context, load, userptr);
    glad_gl_load_GL_EXT_framebuffer_blit_layers(context, load, userptr);
    glad_gl_load_GL_EXT_framebuffer_multisample(context, load, userptr);
    glad_gl_load_GL_EXT_framebuffer_object(context, load, userptr);
    glad_gl_load_GL_EXT_geometry_shader4(context, load, userptr);
    glad_gl_load_GL_EXT_gpu_program_parameters(context, load, userptr);
    glad_gl_load_GL_EXT_gpu_shader4(context, load, userptr);
    glad_gl_load_GL_EXT_histogram(context, load, userptr);
    glad_gl_load_GL_EXT_index_func(context, load, userptr);
    glad_gl_load_GL_EXT_index_material(context, load, userptr);
    glad_gl_load_GL_EXT_light_texture(context, load, userptr);
    glad_gl_load_GL_EXT_memory_object(context, load, userptr);
    glad_gl_load_GL_EXT_memory_object_fd(context, load, userptr);
    glad_gl_load_GL_EXT_memory_object_win32(context, load, userptr);
    glad_gl_load_GL_EXT_multi_draw_arrays(context, load, userptr);
    glad_gl_load_GL_EXT_multisample(context, load, userptr);
    glad_gl_load_GL_EXT_paletted_texture(context, load, userptr);
    glad_gl_load_GL_EXT_pixel_transform(context, load, userptr);
    glad_gl_load_GL_EXT_point_parameters(context, load, userptr);
    glad_gl_load_GL_EXT_polygon_offset(context, load, userptr);
    glad_gl_load_GL_EXT_polygon_offset_clamp(context, load, userptr);
    glad_gl_load_GL_EXT_provoking_vertex(context, load, userptr);
    glad_gl_load_GL_EXT_raster_multisample(context, load, userptr);
    glad_gl_load_GL_EXT_secondary_color(context, load, userptr);
    glad_gl_load_GL_EXT_semaphore(context, load, userptr);
    glad_gl_load_GL_EXT_semaphore_fd(context, load, userptr);
    glad_gl_load_GL_EXT_semaphore_win32(context, load, userptr);
    glad_gl_load_GL_EXT_separate_shader_objects(context, load, userptr);
    glad_gl_load_GL_EXT_shader_framebuffer_fetch_non_coherent(context, load, userptr);
    glad_gl_load_GL_EXT_shader_image_load_store(context, load, userptr);
    glad_gl_load_GL_EXT_stencil_clear_tag(context, load, userptr);
    glad_gl_load_GL_EXT_stencil_two_side(context, load, userptr);
    glad_gl_load_GL_EXT_subtexture(context, load, userptr);
    glad_gl_load_GL_EXT_texture3D(context, load, userptr);
    glad_gl_load_GL_EXT_texture_array(context, load, userptr);
    glad_gl_load_GL_EXT_texture_buffer_object(context, load, userptr);
    glad_gl_load_GL_EXT_texture_integer(context, load, userptr);
    glad_gl_load_GL_EXT_texture_object(context, load, userptr);
    glad_gl_load_GL_EXT_texture_perturb_normal(context, load, userptr);
    glad_gl_load_GL_EXT_texture_storage(context, load, userptr);
    glad_gl_load_GL_EXT_timer_query(context, load, userptr);
    glad_gl_load_GL_EXT_transform_feedback(context, load, userptr);
    glad_gl_load_GL_EXT_vertex_array(context, load, userptr);
    glad_gl_load_GL_EXT_vertex_attrib_64bit(context, load, userptr);
    glad_gl_load_GL_EXT_vertex_shader(context, load, userptr);
    glad_gl_load_GL_EXT_vertex_weighting(context, load, userptr);
    glad_gl_load_GL_EXT_win32_keyed_mutex(context, load, userptr);
    glad_gl_load_GL_EXT_window_rectangles(context, load, userptr);
    glad_gl_load_GL_EXT_x11_sync_object(context, load, userptr);
    glad_gl_load_GL_GREMEDY_frame_terminator(context, load, userptr);
    glad_gl_load_GL_GREMEDY_string_marker(context, load, userptr);
    glad_gl_load_GL_HP_image_transform(context, load, userptr);
    glad_gl_load_GL_IBM_multimode_draw_arrays(context, load, userptr);
    glad_gl_load_GL_IBM_static_data(context, load, userptr);
    glad_gl_load_GL_IBM_vertex_array_lists(context, load, userptr);
    glad_gl_load_GL_INGR_blend_func_separate(context, load, userptr);
    glad_gl_load_GL_INTEL_framebuffer_CMAA(context, load, userptr);
    glad_gl_load_GL_INTEL_map_texture(context, load, userptr);
    glad_gl_load_GL_INTEL_parallel_arrays(context, load, userptr);
    glad_gl_load_GL_INTEL_performance_query(context, load, userptr);
    glad_gl_load_GL_KHR_blend_equation_advanced(context, load, userptr);
    glad_gl_load_GL_KHR_debug(context, load, userptr);
    glad_gl_load_GL_KHR_parallel_shader_compile(context, load, userptr);
    glad_gl_load_GL_KHR_robustness(context, load, userptr);
    glad_gl_load_GL_MESA_framebuffer_flip_y(context, load, userptr);
    glad_gl_load_GL_MESA_resize_buffers(context, load, userptr);
    glad_gl_load_GL_MESA_window_pos(context, load, userptr);
    glad_gl_load_GL_NVX_conditional_render(context, load, userptr);
    glad_gl_load_GL_NVX_gpu_multicast2(context, load, userptr);
    glad_gl_load_GL_NVX_linked_gpu_multicast(context, load, userptr);
    glad_gl_load_GL_NVX_progress_fence(context, load, userptr);
    glad_gl_load_GL_NV_alpha_to_coverage_dither_control(context, load, userptr);
    glad_gl_load_GL_NV_bindless_multi_draw_indirect(context, load, userptr);
    glad_gl_load_GL_NV_bindless_multi_draw_indirect_count(context, load, userptr);
    glad_gl_load_GL_NV_bindless_texture(context, load, userptr);
    glad_gl_load_GL_NV_blend_equation_advanced(context, load, userptr);
    glad_gl_load_GL_NV_clip_space_w_scaling(context, load, userptr);
    glad_gl_load_GL_NV_command_list(context, load, userptr);
    glad_gl_load_GL_NV_conditional_render(context, load, userptr);
    glad_gl_load_GL_NV_conservative_raster(context, load, userptr);
    glad_gl_load_GL_NV_conservative_raster_dilate(context, load, userptr);
    glad_gl_load_GL_NV_conservative_raster_pre_snap_triangles(context, load, userptr);
    glad_gl_load_GL_NV_copy_image(context, load, userptr);
    glad_gl_load_GL_NV_depth_buffer_float(context, load, userptr);
    glad_gl_load_GL_NV_draw_texture(context, load, userptr);
    glad_gl_load_GL_NV_draw_vulkan_image(context, load, userptr);
    glad_gl_load_GL_NV_evaluators(context, load, userptr);
    glad_gl_load_GL_NV_explicit_multisample(context, load, userptr);
    glad_gl_load_GL_NV_fence(context, load, userptr);
    glad_gl_load_GL_NV_fragment_coverage_to_color(context, load, userptr);
    glad_gl_load_GL_NV_fragment_program(context, load, userptr);
    glad_gl_load_GL_NV_framebuffer_mixed_samples(context, load, userptr);
    glad_gl_load_GL_NV_framebuffer_multisample_coverage(context, load, userptr);
    glad_gl_load_GL_NV_geometry_program4(context, load, userptr);
    glad_gl_load_GL_NV_gpu_multicast(context, load, userptr);
    glad_gl_load_GL_NV_gpu_program4(context, load, userptr);
    glad_gl_load_GL_NV_gpu_program5(context, load, userptr);
    glad_gl_load_GL_NV_gpu_shader5(context, load, userptr);
    glad_gl_load_GL_NV_half_float(context, load, userptr);
    glad_gl_load_GL_NV_internalformat_sample_query(context, load, userptr);
    glad_gl_load_GL_NV_memory_attachment(context, load, userptr);
    glad_gl_load_GL_NV_memory_object_sparse(context, load, userptr);
    glad_gl_load_GL_NV_mesh_shader(context, load, userptr);
    glad_gl_load_GL_NV_occlusion_query(context, load, userptr);
    glad_gl_load_GL_NV_parameter_buffer_object(context, load, userptr);
    glad_gl_load_GL_NV_path_rendering(context, load, userptr);
    glad_gl_load_GL_NV_pixel_data_range(context, load, userptr);
    glad_gl_load_GL_NV_point_sprite(context, load, userptr);
    glad_gl_load_GL_NV_present_video(context, load, userptr);
    glad_gl_load_GL_NV_primitive_restart(context, load, userptr);
    glad_gl_load_GL_NV_query_resource(context, load, userptr);
    glad_gl_load_GL_NV_query_resource_tag(context, load, userptr);
    glad_gl_load_GL_NV_register_combiners(context, load, userptr);
    glad_gl_load_GL_NV_register_combiners2(context, load, userptr);
    glad_gl_load_GL_NV_sample_locations(context, load, userptr);
    glad_gl_load_GL_NV_scissor_exclusive(context, load, userptr);
    glad_gl_load_GL_NV_shader_buffer_load(context, load, userptr);
    glad_gl_load_GL_NV_shading_rate_image(context, load, userptr);
    glad_gl_load_GL_NV_texture_barrier(context, load, userptr);
    glad_gl_load_GL_NV_texture_multisample(context, load, userptr);
    glad_gl_load_GL_NV_timeline_semaphore(context, load, userptr);
    glad_gl_load_GL_NV_transform_feedback(context, load, userptr);
    glad_gl_load_GL_NV_transform_feedback2(context, load, userptr);
    glad_gl_load_GL_NV_vdpau_interop(context, load, userptr);
    glad_gl_load_GL_NV_vdpau_interop2(context, load, userptr);
    glad_gl_load_GL_NV_vertex_array_range(context, load, userptr);
    glad_gl_load_GL_NV_vertex_attrib_integer_64bit(context, load, userptr);
    glad_gl_load_GL_NV_vertex_buffer_unified_memory(context, load, userptr);
    glad_gl_load_GL_NV_vertex_program(context, load, userptr);
    glad_gl_load_GL_NV_vertex_program4(context, load, userptr);
    glad_gl_load_GL_NV_video_capture(context, load, userptr);
    glad_gl_load_GL_NV_viewport_swizzle(context, load, userptr);
    glad_gl_load_GL_OES_byte_coordinates(context, load, userptr);
    glad_gl_load_GL_OES_fixed_point(context, load, userptr);
    glad_gl_load_GL_OES_query_matrix(context, load, userptr);
    glad_gl_load_GL_OES_single_precision(context, load, userptr);
    glad_gl_load_GL_OVR_multiview(context, load, userptr);
    glad_gl_load_GL_PGI_misc_hints(context, load, userptr);
    glad_gl_load_GL_SGIS_detail_texture(context, load, userptr);
    glad_gl_load_GL_SGIS_fog_function(context, load, userptr);
    glad_gl_load_GL_SGIS_multisample(context, load, userptr);
    glad_gl_load_GL_SGIS_pixel_texture(context, load, userptr);
    glad_gl_load_GL_SGIS_point_parameters(context, load, userptr);
    glad_gl_load_GL_SGIS_sharpen_texture(context, load, userptr);
    glad_gl_load_GL_SGIS_texture4D(context, load, userptr);
    glad_gl_load_GL_SGIS_texture_color_mask(context, load, userptr);
    glad_gl_load_GL_SGIS_texture_filter4(context, load, userptr);
    glad_gl_load_GL_SGIX_async(context, load, userptr);
    glad_gl_load_GL_SGIX_flush_raster(context, load, userptr);
    glad_gl_load_GL_SGIX_fragment_lighting(context, load, userptr);
    glad_gl_load_GL_SGIX_framezoom(context, load, userptr);
    glad_gl_load_GL_SGIX_igloo_interface(context, load, userptr);
    glad_gl_load_GL_SGIX_instruments(context, load, userptr);
    glad_gl_load_GL_SGIX_list_priority(context, load, userptr);
    glad_gl_load_GL_SGIX_pixel_texture(context, load, userptr);
    glad_gl_load_GL_SGIX_polynomial_ffd(context, load, userptr);
    glad_gl_load_GL_SGIX_reference_plane(context, load, userptr);
    glad_gl_load_GL_SGIX_sprite(context, load, userptr);
    glad_gl_load_GL_SGIX_tag_sample_buffer(context, load, userptr);
    glad_gl_load_GL_SGI_color_table(context, load, userptr);
    glad_gl_load_GL_SUNX_constant_data(context, load, userptr);
    glad_gl_load_GL_SUN_global_alpha(context, load, userptr);
    glad_gl_load_GL_SUN_mesh_array(context, load, userptr);
    glad_gl_load_GL_SUN_triangle_list(context, load, userptr);
    glad_gl_load_GL_SUN_vertex(context, load, userptr);

    gladSetGLContext(context);

    glad_gl_resolve_aliases(context);

    return version;
}

int gladLoadGLUserPtr(GLADuserptrloadfunc load, void *userptr) {
    return gladLoadGLContextUserPtr(gladGetGLContext(), load, userptr);
}

int gladLoadGLContext(GladGLContext *context, GLADloadfunc load) {
    return gladLoadGLContextUserPtr(context, glad_gl_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}

int gladLoadGL(GLADloadfunc load) {
    return gladLoadGLContext(gladGetGLContext(), load);
}

static int glad_gl_find_extensions_gles2(GladGLContext *context, int version) {
    const char *exts = NULL;
    unsigned int num_exts_i = 0;
    char **exts_i = NULL;
    if (!glad_gl_get_extensions(context, version, &exts, &num_exts_i, &exts_i)) return 0;

    static uint16_t extIdx[] = {
             8, // GL_AMD_framebuffer_multisample_advanced
            18, // GL_AMD_performance_monitor
            40, // GL_ANGLE_memory_object_flags
            41, // GL_ANGLE_memory_object_fuchsia
            42, // GL_ANGLE_semaphore_fuchsia
            44, // GL_ANGLE_texture_external_update
           249, // GL_EXT_EGL_image_storage
           258, // GL_EXT_blend_minmax
           271, // GL_EXT_debug_label
           272, // GL_EXT_debug_marker
           279, // GL_EXT_draw_instanced
           281, // GL_EXT_external_buffer
           286, // GL_EXT_framebuffer_blit_layers
           300, // GL_EXT_memory_object
           301, // GL_EXT_memory_object_fd
           302, // GL_EXT_memory_object_win32
           304, // GL_EXT_multi_draw_arrays
           319, // GL_EXT_polygon_offset_clamp
           322, // GL_EXT_raster_multisample
           331, // GL_EXT_semaphore
           332, // GL_EXT_semaphore_fd
           333, // GL_EXT_semaphore_win32
           334, // GL_EXT_separate_shader_objects
           340, // GL_EXT_shader_framebuffer_fetch_non_coherent
           383, // GL_EXT_texture_storage
           393, // GL_EXT_win32_keyed_mutex
           394, // GL_EXT_window_rectangles
           415, // GL_INTEL_framebuffer_CMAA
           418, // GL_INTEL_performance_query
           419, // GL_KHR_blend_equation_advanced
           422, // GL_KHR_debug
           425, // GL_KHR_parallel_shader_compile
           427, // GL_KHR_robustness
           435, // GL_MESA_framebuffer_flip_y
           454, // GL_NV_bindless_texture
           455, // GL_NV_blend_equation_advanced
           459, // GL_NV_clip_space_w_scaling
           463, // GL_NV_conditional_render
           464, // GL_NV_conservative_raster
           467, // GL_NV_conservative_raster_pre_snap_triangles
           476, // GL_NV_draw_vulkan_image
           479, // GL_NV_fence
           483, // GL_NV_fragment_coverage_to_color
           490, // GL_NV_framebuffer_mixed_samples
           499, // GL_NV_gpu_shader5
           501, // GL_NV_internalformat_sample_query
           503, // GL_NV_memory_attachment
           504, // GL_NV_memory_object_sparse
           505, // GL_NV_mesh_shader
           512, // GL_NV_path_rendering
           527, // GL_NV_sample_locations
           529, // GL_NV_scissor_exclusive
           543, // GL_NV_shading_rate_image
           558, // GL_NV_timeline_semaphore
           577, // GL_NV_viewport_swizzle
           587, // GL_OVR_multiview
           662, // GL_ANGLE_base_vertex_base_instance
           665, // GL_ANGLE_copy_texture_3d
           667, // GL_ANGLE_framebuffer_blit
           668, // GL_ANGLE_framebuffer_multisample
           669, // GL_ANGLE_get_image
           671, // GL_ANGLE_get_tex_level_parameter
           672, // GL_ANGLE_instanced_arrays
           673, // GL_ANGLE_logic_op
           676, // GL_ANGLE_multi_draw
           678, // GL_ANGLE_polygon_mode
           681, // GL_ANGLE_provoking_vertex
           683, // GL_ANGLE_request_extension
           685, // GL_ANGLE_robust_client_memory
           688, // GL_ANGLE_shader_pixel_local_storage
           692, // GL_ANGLE_texture_multisample
           695, // GL_ANGLE_translated_shader_source
           696, // GL_ANGLE_vulkan_image
           700, // GL_APPLE_copy_texture_levels
           701, // GL_APPLE_framebuffer_multisample
           702, // GL_APPLE_sync
           709, // GL_ARM_shader_core_properties
           713, // GL_CHROMIUM_bind_uniform_location
           714, // GL_CHROMIUM_copy_compressed_texture
           715, // GL_CHROMIUM_copy_texture
           716, // GL_CHROMIUM_framebuffer_mixed_samples
           717, // GL_CHROMIUM_lose_context
           723, // GL_EXT_base_instance
           724, // GL_EXT_blend_func_extended
           725, // GL_EXT_buffer_storage
           726, // GL_EXT_clear_texture
           727, // GL_EXT_clip_control
           732, // GL_EXT_copy_image
           734, // GL_EXT_discard_framebuffer
           735, // GL_EXT_disjoint_timer_query
           736, // GL_EXT_draw_buffers
           737, // GL_EXT_draw_buffers_indexed
           738, // GL_EXT_draw_elements_base_vertex
           739, // GL_EXT_draw_transform_feedback
           741, // GL_EXT_fragment_shading_rate
           743, // GL_EXT_geometry_shader
           745, // GL_EXT_instanced_arrays
           746, // GL_EXT_map_buffer_range
           747, // GL_EXT_multi_draw_indirect
           749, // GL_EXT_multisampled_render_to_texture
           751, // GL_EXT_multiview_draw_buffers
           752, // GL_EXT_occlusion_query_boolean
           753, // GL_EXT_primitive_bounding_box
           758, // GL_EXT_robustness
           767, // GL_EXT_shader_pixel_local_storage2
           770, // GL_EXT_sparse_texture
           772, // GL_EXT_tessellation_shader
           773, // GL_EXT_texture_border_clamp
           774, // GL_EXT_texture_buffer
           786, // GL_EXT_texture_storage_compression
           788, // GL_EXT_texture_view
           791, // GL_IMG_bindless_texture
           792, // GL_IMG_framebuffer_downsample
           793, // GL_IMG_multisampled_render_to_texture
           801, // GL_MESA_sampler_objects
           802, // GL_NV_copy_buffer
           803, // GL_NV_coverage_sample
           805, // GL_NV_draw_buffers
           806, // GL_NV_draw_instanced
           809, // GL_NV_framebuffer_blit
           810, // GL_NV_framebuffer_multisample
           813, // GL_NV_instanced_arrays
           814, // GL_NV_non_square_matrices
           817, // GL_NV_polygon_mode
           818, // GL_NV_read_buffer
           830, // GL_NV_viewport_array
           831, // GL_OES_EGL_image
           836, // GL_OES_copy_image
           840, // GL_OES_draw_buffers_indexed
           841, // GL_OES_draw_elements_base_vertex
           846, // GL_OES_geometry_shader
           847, // GL_OES_get_program_binary
           849, // GL_OES_mapbuffer
           851, // GL_OES_primitive_bounding_box
           854, // GL_OES_sample_shading
           864, // GL_OES_tessellation_shader
           865, // GL_OES_texture_3D
           866, // GL_OES_texture_border_clamp
           867, // GL_OES_texture_buffer
           876, // GL_OES_texture_storage_multisample_2d_array
           877, // GL_OES_texture_view
           878, // GL_OES_vertex_array_object
           881, // GL_OES_viewport_array
           882, // GL_OVR_multiview_multisampled_render_to_texture
           884, // GL_QCOM_alpha_test
           886, // GL_QCOM_driver_control
           887, // GL_QCOM_extended_get
           888, // GL_QCOM_extended_get2
           889, // GL_QCOM_frame_extrapolation
           890, // GL_QCOM_framebuffer_foveated
           891, // GL_QCOM_motion_estimation
           895, // GL_QCOM_shader_framebuffer_fetch_noncoherent
           897, // GL_QCOM_shading_rate
           898, // GL_QCOM_texture_foveated
           902, // GL_QCOM_tiled_rendering
        0xFFFF
    };

    for (uint32_t i = 0; i < GLAD_ARRAYSIZE(extIdx) - 1; ++i)
        context->extArray[extIdx[i]] = glad_gl_has_extension(version, exts, num_exts_i, exts_i, glad_ext_names[extIdx[i]]);

    glad_gl_free_extensions(exts_i, num_exts_i);

    return 1;
}

static int glad_gl_find_core_gles2(GladGLContext *context) {
    int i;
    const char* version;
    const char* prefixes[] = {
        "OpenGL ES-CM ",
        "OpenGL ES-CL ",
        "OpenGL ES ",
        "OpenGL SC ",
        NULL
    };
    int major = 0;
    int minor = 0;
    version = (const char*) context->GetString(GL_VERSION);
    if (!version) return 0;
    for (i = 0;  prefixes[i];  i++) {
        const size_t length = strlen(prefixes[i]);
        if (strncmp(version, prefixes[i], length) == 0) {
            version += length;
            break;
        }
    }

    GLAD_IMPL_UTIL_SSCANF(version, "%d.%d", &major, &minor);

    context->ES_VERSION_2_0 = (major == 2 && minor >= 0) || major > 2;
    context->ES_VERSION_3_0 = (major == 3 && minor >= 0) || major > 3;
    context->ES_VERSION_3_1 = (major == 3 && minor >= 1) || major > 3;
    context->ES_VERSION_3_2 = (major == 3 && minor >= 2) || major > 3;

    return GLAD_MAKE_VERSION(major, minor);
}

int gladLoadGLES2ContextUserPtr(GladGLContext *context, GLADuserptrloadfunc load, void *userptr) {
    int version;

    context->GetString = (PFNGLGETSTRINGPROC) load(userptr, "glGetString");
    if(context->GetString == NULL) return 0;
    if(context->GetString(GL_VERSION) == NULL) return 0;
    version = glad_gl_find_core_gles2(context);

    glad_gl_load_GL_ES_VERSION_2_0(context, load, userptr);
    glad_gl_load_GL_ES_VERSION_3_0(context, load, userptr);
    glad_gl_load_GL_ES_VERSION_3_1(context, load, userptr);
    glad_gl_load_GL_ES_VERSION_3_2(context, load, userptr);

    if (!glad_gl_find_extensions_gles2(context, version)) return 0;
    glad_gl_load_GL_AMD_framebuffer_multisample_advanced(context, load, userptr);
    glad_gl_load_GL_AMD_performance_monitor(context, load, userptr);
    glad_gl_load_GL_ANGLE_memory_object_flags(context, load, userptr);
    glad_gl_load_GL_ANGLE_memory_object_fuchsia(context, load, userptr);
    glad_gl_load_GL_ANGLE_semaphore_fuchsia(context, load, userptr);
    glad_gl_load_GL_ANGLE_texture_external_update(context, load, userptr);
    glad_gl_load_GL_EXT_EGL_image_storage(context, load, userptr);
    glad_gl_load_GL_EXT_blend_minmax(context, load, userptr);
    glad_gl_load_GL_EXT_debug_label(context, load, userptr);
    glad_gl_load_GL_EXT_debug_marker(context, load, userptr);
    glad_gl_load_GL_EXT_draw_instanced(context, load, userptr);
    glad_gl_load_GL_EXT_external_buffer(context, load, userptr);
    glad_gl_load_GL_EXT_framebuffer_blit_layers(context, load, userptr);
    glad_gl_load_GL_EXT_memory_object(context, load, userptr);
    glad_gl_load_GL_EXT_memory_object_fd(context, load, userptr);
    glad_gl_load_GL_EXT_memory_object_win32(context, load, userptr);
    glad_gl_load_GL_EXT_multi_draw_arrays(context, load, userptr);
    glad_gl_load_GL_EXT_polygon_offset_clamp(context, load, userptr);
    glad_gl_load_GL_EXT_raster_multisample(context, load, userptr);
    glad_gl_load_GL_EXT_semaphore(context, load, userptr);
    glad_gl_load_GL_EXT_semaphore_fd(context, load, userptr);
    glad_gl_load_GL_EXT_semaphore_win32(context, load, userptr);
    glad_gl_load_GL_EXT_separate_shader_objects(context, load, userptr);
    glad_gl_load_GL_EXT_shader_framebuffer_fetch_non_coherent(context, load, userptr);
    glad_gl_load_GL_EXT_texture_storage(context, load, userptr);
    glad_gl_load_GL_EXT_win32_keyed_mutex(context, load, userptr);
    glad_gl_load_GL_EXT_window_rectangles(context, load, userptr);
    glad_gl_load_GL_INTEL_framebuffer_CMAA(context, load, userptr);
    glad_gl_load_GL_INTEL_performance_query(context, load, userptr);
    glad_gl_load_GL_KHR_blend_equation_advanced(context, load, userptr);
    glad_gl_load_GL_KHR_debug(context, load, userptr);
    glad_gl_load_GL_KHR_parallel_shader_compile(context, load, userptr);
    glad_gl_load_GL_KHR_robustness(context, load, userptr);
    glad_gl_load_GL_MESA_framebuffer_flip_y(context, load, userptr);
    glad_gl_load_GL_NV_bindless_texture(context, load, userptr);
    glad_gl_load_GL_NV_blend_equation_advanced(context, load, userptr);
    glad_gl_load_GL_NV_clip_space_w_scaling(context, load, userptr);
    glad_gl_load_GL_NV_conditional_render(context, load, userptr);
    glad_gl_load_GL_NV_conservative_raster(context, load, userptr);
    glad_gl_load_GL_NV_conservative_raster_pre_snap_triangles(context, load, userptr);
    glad_gl_load_GL_NV_draw_vulkan_image(context, load, userptr);
    glad_gl_load_GL_NV_fence(context, load, userptr);
    glad_gl_load_GL_NV_fragment_coverage_to_color(context, load, userptr);
    glad_gl_load_GL_NV_framebuffer_mixed_samples(context, load, userptr);
    glad_gl_load_GL_NV_gpu_shader5(context, load, userptr);
    glad_gl_load_GL_NV_internalformat_sample_query(context, load, userptr);
    glad_gl_load_GL_NV_memory_attachment(context, load, userptr);
    glad_gl_load_GL_NV_memory_object_sparse(context, load, userptr);
    glad_gl_load_GL_NV_mesh_shader(context, load, userptr);
    glad_gl_load_GL_NV_path_rendering(context, load, userptr);
    glad_gl_load_GL_NV_sample_locations(context, load, userptr);
    glad_gl_load_GL_NV_scissor_exclusive(context, load, userptr);
    glad_gl_load_GL_NV_shading_rate_image(context, load, userptr);
    glad_gl_load_GL_NV_timeline_semaphore(context, load, userptr);
    glad_gl_load_GL_NV_viewport_swizzle(context, load, userptr);
    glad_gl_load_GL_OVR_multiview(context, load, userptr);
    glad_gl_load_GL_ANGLE_base_vertex_base_instance(context, load, userptr);
    glad_gl_load_GL_ANGLE_copy_texture_3d(context, load, userptr);
    glad_gl_load_GL_ANGLE_framebuffer_blit(context, load, userptr);
    glad_gl_load_GL_ANGLE_framebuffer_multisample(context, load, userptr);
    glad_gl_load_GL_ANGLE_get_image(context, load, userptr);
    glad_gl_load_GL_ANGLE_get_tex_level_parameter(context, load, userptr);
    glad_gl_load_GL_ANGLE_instanced_arrays(context, load, userptr);
    glad_gl_load_GL_ANGLE_logic_op(context, load, userptr);
    glad_gl_load_GL_ANGLE_multi_draw(context, load, userptr);
    glad_gl_load_GL_ANGLE_polygon_mode(context, load, userptr);
    glad_gl_load_GL_ANGLE_provoking_vertex(context, load, userptr);
    glad_gl_load_GL_ANGLE_request_extension(context, load, userptr);
    glad_gl_load_GL_ANGLE_robust_client_memory(context, load, userptr);
    glad_gl_load_GL_ANGLE_shader_pixel_local_storage(context, load, userptr);
    glad_gl_load_GL_ANGLE_texture_multisample(context, load, userptr);
    glad_gl_load_GL_ANGLE_translated_shader_source(context, load, userptr);
    glad_gl_load_GL_ANGLE_vulkan_image(context, load, userptr);
    glad_gl_load_GL_APPLE_copy_texture_levels(context, load, userptr);
    glad_gl_load_GL_APPLE_framebuffer_multisample(context, load, userptr);
    glad_gl_load_GL_APPLE_sync(context, load, userptr);
    glad_gl_load_GL_ARM_shader_core_properties(context, load, userptr);
    glad_gl_load_GL_CHROMIUM_bind_uniform_location(context, load, userptr);
    glad_gl_load_GL_CHROMIUM_copy_compressed_texture(context, load, userptr);
    glad_gl_load_GL_CHROMIUM_copy_texture(context, load, userptr);
    glad_gl_load_GL_CHROMIUM_framebuffer_mixed_samples(context, load, userptr);
    glad_gl_load_GL_CHROMIUM_lose_context(context, load, userptr);
    glad_gl_load_GL_EXT_base_instance(context, load, userptr);
    glad_gl_load_GL_EXT_blend_func_extended(context, load, userptr);
    glad_gl_load_GL_EXT_buffer_storage(context, load, userptr);
    glad_gl_load_GL_EXT_clear_texture(context, load, userptr);
    glad_gl_load_GL_EXT_clip_control(context, load, userptr);
    glad_gl_load_GL_EXT_copy_image(context, load, userptr);
    glad_gl_load_GL_EXT_discard_framebuffer(context, load, userptr);
    glad_gl_load_GL_EXT_disjoint_timer_query(context, load, userptr);
    glad_gl_load_GL_EXT_draw_buffers(context, load, userptr);
    glad_gl_load_GL_EXT_draw_buffers_indexed(context, load, userptr);
    glad_gl_load_GL_EXT_draw_elements_base_vertex(context, load, userptr);
    glad_gl_load_GL_EXT_draw_transform_feedback(context, load, userptr);
    glad_gl_load_GL_EXT_fragment_shading_rate(context, load, userptr);
    glad_gl_load_GL_EXT_geometry_shader(context, load, userptr);
    glad_gl_load_GL_EXT_instanced_arrays(context, load, userptr);
    glad_gl_load_GL_EXT_map_buffer_range(context, load, userptr);
    glad_gl_load_GL_EXT_multi_draw_indirect(context, load, userptr);
    glad_gl_load_GL_EXT_multisampled_render_to_texture(context, load, userptr);
    glad_gl_load_GL_EXT_multiview_draw_buffers(context, load, userptr);
    glad_gl_load_GL_EXT_occlusion_query_boolean(context, load, userptr);
    glad_gl_load_GL_EXT_primitive_bounding_box(context, load, userptr);
    glad_gl_load_GL_EXT_robustness(context, load, userptr);
    glad_gl_load_GL_EXT_shader_pixel_local_storage2(context, load, userptr);
    glad_gl_load_GL_EXT_sparse_texture(context, load, userptr);
    glad_gl_load_GL_EXT_tessellation_shader(context, load, userptr);
    glad_gl_load_GL_EXT_texture_border_clamp(context, load, userptr);
    glad_gl_load_GL_EXT_texture_buffer(context, load, userptr);
    glad_gl_load_GL_EXT_texture_storage_compression(context, load, userptr);
    glad_gl_load_GL_EXT_texture_view(context, load, userptr);
    glad_gl_load_GL_IMG_bindless_texture(context, load, userptr);
    glad_gl_load_GL_IMG_framebuffer_downsample(context, load, userptr);
    glad_gl_load_GL_IMG_multisampled_render_to_texture(context, load, userptr);
    glad_gl_load_GL_MESA_sampler_objects(context, load, userptr);
    glad_gl_load_GL_NV_copy_buffer(context, load, userptr);
    glad_gl_load_GL_NV_coverage_sample(context, load, userptr);
    glad_gl_load_GL_NV_draw_buffers(context, load, userptr);
    glad_gl_load_GL_NV_draw_instanced(context, load, userptr);
    glad_gl_load_GL_NV_framebuffer_blit(context, load, userptr);
    glad_gl_load_GL_NV_framebuffer_multisample(context, load, userptr);
    glad_gl_load_GL_NV_instanced_arrays(context, load, userptr);
    glad_gl_load_GL_NV_non_square_matrices(context, load, userptr);
    glad_gl_load_GL_NV_polygon_mode(context, load, userptr);
    glad_gl_load_GL_NV_read_buffer(context, load, userptr);
    glad_gl_load_GL_NV_viewport_array(context, load, userptr);
    glad_gl_load_GL_OES_EGL_image(context, load, userptr);
    glad_gl_load_GL_OES_copy_image(context, load, userptr);
    glad_gl_load_GL_OES_draw_buffers_indexed(context, load, userptr);
    glad_gl_load_GL_OES_draw_elements_base_vertex(context, load, userptr);
    glad_gl_load_GL_OES_geometry_shader(context, load, userptr);
    glad_gl_load_GL_OES_get_program_binary(context, load, userptr);
    glad_gl_load_GL_OES_mapbuffer(context, load, userptr);
    glad_gl_load_GL_OES_primitive_bounding_box(context, load, userptr);
    glad_gl_load_GL_OES_sample_shading(context, load, userptr);
    glad_gl_load_GL_OES_tessellation_shader(context, load, userptr);
    glad_gl_load_GL_OES_texture_3D(context, load, userptr);
    glad_gl_load_GL_OES_texture_border_clamp(context, load, userptr);
    glad_gl_load_GL_OES_texture_buffer(context, load, userptr);
    glad_gl_load_GL_OES_texture_storage_multisample_2d_array(context, load, userptr);
    glad_gl_load_GL_OES_texture_view(context, load, userptr);
    glad_gl_load_GL_OES_vertex_array_object(context, load, userptr);
    glad_gl_load_GL_OES_viewport_array(context, load, userptr);
    glad_gl_load_GL_OVR_multiview_multisampled_render_to_texture(context, load, userptr);
    glad_gl_load_GL_QCOM_alpha_test(context, load, userptr);
    glad_gl_load_GL_QCOM_driver_control(context, load, userptr);
    glad_gl_load_GL_QCOM_extended_get(context, load, userptr);
    glad_gl_load_GL_QCOM_extended_get2(context, load, userptr);
    glad_gl_load_GL_QCOM_frame_extrapolation(context, load, userptr);
    glad_gl_load_GL_QCOM_framebuffer_foveated(context, load, userptr);
    glad_gl_load_GL_QCOM_motion_estimation(context, load, userptr);
    glad_gl_load_GL_QCOM_shader_framebuffer_fetch_noncoherent(context, load, userptr);
    glad_gl_load_GL_QCOM_shading_rate(context, load, userptr);
    glad_gl_load_GL_QCOM_texture_foveated(context, load, userptr);
    glad_gl_load_GL_QCOM_tiled_rendering(context, load, userptr);

    gladSetGLContext(context);

    glad_gl_resolve_aliases(context);

    return version;
}

int gladLoadGLES2UserPtr(GLADuserptrloadfunc load, void *userptr) {
    return gladLoadGLES2ContextUserPtr(gladGetGLContext(), load, userptr);
}

int gladLoadGLES2Context(GladGLContext *context, GLADloadfunc load) {
    return gladLoadGLES2ContextUserPtr(context, glad_gl_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}

int gladLoadGLES2(GLADloadfunc load) {
    return gladLoadGLES2Context(gladGetGLContext(), load);
}


GladGLContext* gladGetGLContext() {
    return &glad_gl_context;
}

void gladSetGLContext(GladGLContext *context) {
    if (!context) return;
    if (&glad_gl_context == context) return;
    glad_gl_context = *context;
}

 

#ifdef GLAD_GL

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

typedef void* (GLAD_API_PTR *GLADglprocaddrfunc)(const char*);
struct _glad_gl_userptr {
    void *handle;
    GLADglprocaddrfunc gl_get_proc_address_ptr;
};

static GLADapiproc glad_gl_get_proc(void *vuserptr, const char *name) {
    struct _glad_gl_userptr userptr = *(struct _glad_gl_userptr*) vuserptr;
    GLADapiproc result = NULL;

    if(userptr.gl_get_proc_address_ptr != NULL) {
        result = GLAD_GNUC_EXTENSION (GLADapiproc) userptr.gl_get_proc_address_ptr(name);
    }
    if(result == NULL) {
        result = glad_dlsym_handle(userptr.handle, name);
    }

    return result;
}


static void* glad_gl_dlopen_handle(GladGLContext *context) {
#if GLAD_PLATFORM_APPLE
    static const char *NAMES[] = {
        "../Frameworks/OpenGL.framework/OpenGL",
        "/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
    };
#elif GLAD_PLATFORM_WIN32
    static const char *NAMES[] = {"opengl32.dll"};
#else
    static const char *NAMES[] = {
  #if defined(__CYGWIN__)
        "libGL-1.so",
  #endif
        "libGL.so.1",
        "libGL.so"
    };
#endif

    if (context->glad_loader_handle == NULL) {
        context->glad_loader_handle = glad_get_dlopen_handle(NAMES, GLAD_ARRAYSIZE(NAMES));
    }

    return context->glad_loader_handle;
}

static struct _glad_gl_userptr glad_gl_build_userptr(void *handle) {
    struct _glad_gl_userptr userptr;

    userptr.handle = handle;
#if GLAD_PLATFORM_APPLE || defined(__HAIKU__)
    userptr.gl_get_proc_address_ptr = NULL;
#elif GLAD_PLATFORM_WIN32
    userptr.gl_get_proc_address_ptr =
        (GLADglprocaddrfunc) glad_dlsym_handle(handle, "wglGetProcAddress");
#else
    userptr.gl_get_proc_address_ptr =
        (GLADglprocaddrfunc) glad_dlsym_handle(handle, "glXGetProcAddressARB");
#endif

    return userptr;
}

int gladLoaderLoadGLContext(GladGLContext *context) {
    int version = 0;
    void *handle;
    int did_load = 0;
    struct _glad_gl_userptr userptr;

    did_load = context->glad_loader_handle == NULL;
    handle = glad_gl_dlopen_handle(context);
    if (handle) {
        userptr = glad_gl_build_userptr(handle);

        version = gladLoadGLContextUserPtr(context,glad_gl_get_proc, &userptr);

        if (!version && did_load) {
            gladLoaderUnloadGLContext(context);
        }
    }

    return version;
}

void gladLoaderResetGLContext(GladGLContext *context) {
    memset(context, 0, sizeof(GladGLContext));
}

void gladLoaderResetGL(void) {
    gladLoaderResetGLContext(gladGetGLContext());
}


int gladLoaderLoadGL(void) {
    return gladLoaderLoadGLContext(gladGetGLContext());
}

void gladLoaderUnloadGLContext(GladGLContext *context) {
    if (context->glad_loader_handle != NULL) {
        glad_close_dlopen_handle(context->glad_loader_handle);
        context->glad_loader_handle = NULL;
    }

    gladLoaderResetGLContext(context);
}

void gladLoaderUnloadGL(void) {
    gladLoaderUnloadGLContext(gladGetGLContext());
}

#endif /* GLAD_GL */
#ifdef GLAD_GLES2

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

#if GLAD_PLATFORM_EMSCRIPTEN
#ifndef GLAD_EGL_H_
  typedef void (*__eglMustCastToProperFunctionPointerType)(void);
  typedef __eglMustCastToProperFunctionPointerType (GLAD_API_PTR *PFNEGLGETPROCADDRESSPROC)(const char *name);
#endif
  extern __eglMustCastToProperFunctionPointerType emscripten_GetProcAddress(const char *name);
#else
  #include <glad/egl.h>
#endif


struct _glad_gles2_userptr {
    void *handle;
    PFNEGLGETPROCADDRESSPROC get_proc_address_ptr;
};


static GLADapiproc glad_gles2_get_proc(void *vuserptr, const char* name) {
    struct _glad_gles2_userptr userptr = *(struct _glad_gles2_userptr*) vuserptr;
    GLADapiproc result = NULL;

#if GLAD_PLATFORM_EMSCRIPTEN
    GLAD_UNUSED(glad_dlsym_handle);
#else
    result = glad_dlsym_handle(userptr.handle, name);
#endif
    if (result == NULL) {
        result = userptr.get_proc_address_ptr(name);
    }

    return result;
}


static void* glad_gles2_dlopen_handle(GladGLContext *context) {
#if GLAD_PLATFORM_EMSCRIPTEN
#elif GLAD_PLATFORM_APPLE
    static const char *NAMES[] = {"libGLESv2.dylib"};
#elif GLAD_PLATFORM_WIN32
    static const char *NAMES[] = {"GLESv2.dll", "libGLESv2.dll"};
#else
    static const char *NAMES[] = {"libGLESv2.so.2", "libGLESv2.so"};
#endif

#if GLAD_PLATFORM_EMSCRIPTEN
    GLAD_UNUSED(glad_get_dlopen_handle);
    return NULL;
#else
    if (context->glad_loader_handle == NULL) {
        context->glad_loader_handle = glad_get_dlopen_handle(NAMES, GLAD_ARRAYSIZE(NAMES));
    }

    return context->glad_loader_handle;
#endif
}

static struct _glad_gles2_userptr glad_gles2_build_userptr(void *handle) {
    struct _glad_gles2_userptr userptr;
#if GLAD_PLATFORM_EMSCRIPTEN
    GLAD_UNUSED(handle);
    userptr.get_proc_address_ptr = emscripten_GetProcAddress;
#else
    userptr.handle = handle;
    userptr.get_proc_address_ptr = eglGetProcAddress;
#endif
    return userptr;
}

int gladLoaderLoadGLES2Context(GladGLContext *context) {
    int version = 0;
    void *handle = NULL;
    int did_load = 0;
    struct _glad_gles2_userptr userptr;

#if GLAD_PLATFORM_EMSCRIPTEN
    GLAD_UNUSED(handle);
    GLAD_UNUSED(did_load);
    GLAD_UNUSED(glad_gles2_dlopen_handle);
    GLAD_UNUSED(glad_gles2_build_userptr);
    userptr.get_proc_address_ptr = emscripten_GetProcAddress;
    version = gladLoadGLES2ContextUserPtr(context, glad_gles2_get_proc, &userptr);
#else
    if (eglGetProcAddress == NULL) {
        return 0;
    }

    did_load = context->glad_loader_handle == NULL;
    handle = glad_gles2_dlopen_handle(context);
    if (handle != NULL) {
        userptr = glad_gles2_build_userptr(handle);

        version = gladLoadGLES2ContextUserPtr(context, glad_gles2_get_proc, &userptr);

        if (!version && did_load) {
            gladLoaderUnloadGLES2Context(context);
        }
    }
#endif

    return version;
}

void gladLoaderResetGLES2Context(GladGLContext *context) {
    memset(context, 0, sizeof(GladGLContext));
}

void gladLoaderResetGLES2(void) {
    gladLoaderResetGLES2Context(gladGetGLContext());
}


int gladLoaderLoadGLES2(void) {
    return gladLoaderLoadGLES2Context(gladGetGLContext());
}

void gladLoaderUnloadGLES2Context(GladGLContext *context) {
    if (context->glad_loader_handle != NULL) {
        glad_close_dlopen_handle(context->glad_loader_handle);
        context->glad_loader_handle = NULL;
    }

    gladLoaderResetGLES2Context(context);
}

void gladLoaderUnloadGLES2(void) {
    gladLoaderUnloadGLES2Context(gladGetGLContext());
}

#endif /* GLAD_GLES2 */

#ifdef __cplusplus
}
#endif
