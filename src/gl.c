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

#include <glad/gl.h>

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

static const char *GLAD_GL_fn_names[] = {
    /*    0 */ "glAccumxOES",
    /*    1 */ "glAcquireKeyedMutexWin32EXT",
    /*    2 */ "glActiveProgramEXT",
    /*    3 */ "glActiveShaderProgram",
    /*    4 */ "glActiveStencilFaceEXT",
    /*    5 */ "glActiveTexture",
    /*    6 */ "glActiveTextureARB",
    /*    7 */ "glActiveVaryingNV",
    /*    8 */ "glAlphaFragmentOp1ATI",
    /*    9 */ "glAlphaFragmentOp2ATI",
    /*   10 */ "glAlphaFragmentOp3ATI",
    /*   11 */ "glAlphaFuncxOES",
    /*   12 */ "glAlphaToCoverageDitherControlNV",
    /*   13 */ "glApplyFramebufferAttachmentCMAAINTEL",
    /*   14 */ "glApplyTextureEXT",
    /*   15 */ "glAreProgramsResidentNV",
    /*   16 */ "glAreTexturesResidentEXT",
    /*   17 */ "glArrayElementEXT",
    /*   18 */ "glArrayObjectATI",
    /*   19 */ "glAsyncCopyBufferSubDataNVX",
    /*   20 */ "glAsyncCopyImageSubDataNVX",
    /*   21 */ "glAsyncMarkerSGIX",
    /*   22 */ "glAttachObjectARB",
    /*   23 */ "glAttachShader",
    /*   24 */ "glBeginConditionalRender",
    /*   25 */ "glBeginConditionalRenderNV",
    /*   26 */ "glBeginConditionalRenderNVX",
    /*   27 */ "glBeginFragmentShaderATI",
    /*   28 */ "glBeginOcclusionQueryNV",
    /*   29 */ "glBeginPerfMonitorAMD",
    /*   30 */ "glBeginPerfQueryINTEL",
    /*   31 */ "glBeginQuery",
    /*   32 */ "glBeginQueryARB",
    /*   33 */ "glBeginQueryIndexed",
    /*   34 */ "glBeginTransformFeedback",
    /*   35 */ "glBeginTransformFeedbackEXT",
    /*   36 */ "glBeginTransformFeedbackNV",
    /*   37 */ "glBeginVertexShaderEXT",
    /*   38 */ "glBeginVideoCaptureNV",
    /*   39 */ "glBindAttribLocation",
    /*   40 */ "glBindAttribLocationARB",
    /*   41 */ "glBindBuffer",
    /*   42 */ "glBindBufferARB",
    /*   43 */ "glBindBufferBase",
    /*   44 */ "glBindBufferBaseEXT",
    /*   45 */ "glBindBufferBaseNV",
    /*   46 */ "glBindBufferOffsetEXT",
    /*   47 */ "glBindBufferOffsetNV",
    /*   48 */ "glBindBufferRange",
    /*   49 */ "glBindBufferRangeEXT",
    /*   50 */ "glBindBufferRangeNV",
    /*   51 */ "glBindBuffersBase",
    /*   52 */ "glBindBuffersRange",
    /*   53 */ "glBindFragDataLocation",
    /*   54 */ "glBindFragDataLocationEXT",
    /*   55 */ "glBindFragDataLocationIndexed",
    /*   56 */ "glBindFragmentShaderATI",
    /*   57 */ "glBindFramebuffer",
    /*   58 */ "glBindFramebufferEXT",
    /*   59 */ "glBindImageTexture",
    /*   60 */ "glBindImageTextureEXT",
    /*   61 */ "glBindImageTextures",
    /*   62 */ "glBindLightParameterEXT",
    /*   63 */ "glBindMaterialParameterEXT",
    /*   64 */ "glBindMultiTextureEXT",
    /*   65 */ "glBindParameterEXT",
    /*   66 */ "glBindProgramARB",
    /*   67 */ "glBindProgramNV",
    /*   68 */ "glBindProgramPipeline",
    /*   69 */ "glBindRenderbuffer",
    /*   70 */ "glBindRenderbufferEXT",
    /*   71 */ "glBindSampler",
    /*   72 */ "glBindSamplers",
    /*   73 */ "glBindShadingRateImageNV",
    /*   74 */ "glBindTexGenParameterEXT",
    /*   75 */ "glBindTexture",
    /*   76 */ "glBindTextureEXT",
    /*   77 */ "glBindTextureUnit",
    /*   78 */ "glBindTextureUnitParameterEXT",
    /*   79 */ "glBindTextures",
    /*   80 */ "glBindTransformFeedback",
    /*   81 */ "glBindTransformFeedbackNV",
    /*   82 */ "glBindVertexArray",
    /*   83 */ "glBindVertexArrayAPPLE",
    /*   84 */ "glBindVertexBuffer",
    /*   85 */ "glBindVertexBuffers",
    /*   86 */ "glBindVertexShaderEXT",
    /*   87 */ "glBindVideoCaptureStreamBufferNV",
    /*   88 */ "glBindVideoCaptureStreamTextureNV",
    /*   89 */ "glBinormal3bEXT",
    /*   90 */ "glBinormal3bvEXT",
    /*   91 */ "glBinormal3dEXT",
    /*   92 */ "glBinormal3dvEXT",
    /*   93 */ "glBinormal3fEXT",
    /*   94 */ "glBinormal3fvEXT",
    /*   95 */ "glBinormal3iEXT",
    /*   96 */ "glBinormal3ivEXT",
    /*   97 */ "glBinormal3sEXT",
    /*   98 */ "glBinormal3svEXT",
    /*   99 */ "glBinormalPointerEXT",
    /*  100 */ "glBitmapxOES",
    /*  101 */ "glBlendBarrierKHR",
    /*  102 */ "glBlendBarrierNV",
    /*  103 */ "glBlendColor",
    /*  104 */ "glBlendColorEXT",
    /*  105 */ "glBlendColorxOES",
    /*  106 */ "glBlendEquation",
    /*  107 */ "glBlendEquationEXT",
    /*  108 */ "glBlendEquationIndexedAMD",
    /*  109 */ "glBlendEquationSeparate",
    /*  110 */ "glBlendEquationSeparateEXT",
    /*  111 */ "glBlendEquationSeparateIndexedAMD",
    /*  112 */ "glBlendEquationSeparatei",
    /*  113 */ "glBlendEquationSeparateiARB",
    /*  114 */ "glBlendEquationi",
    /*  115 */ "glBlendEquationiARB",
    /*  116 */ "glBlendFunc",
    /*  117 */ "glBlendFuncIndexedAMD",
    /*  118 */ "glBlendFuncSeparate",
    /*  119 */ "glBlendFuncSeparateEXT",
    /*  120 */ "glBlendFuncSeparateINGR",
    /*  121 */ "glBlendFuncSeparateIndexedAMD",
    /*  122 */ "glBlendFuncSeparatei",
    /*  123 */ "glBlendFuncSeparateiARB",
    /*  124 */ "glBlendFunci",
    /*  125 */ "glBlendFunciARB",
    /*  126 */ "glBlendParameteriNV",
    /*  127 */ "glBlitFramebuffer",
    /*  128 */ "glBlitFramebufferEXT",
    /*  129 */ "glBlitFramebufferLayerEXT",
    /*  130 */ "glBlitFramebufferLayersEXT",
    /*  131 */ "glBlitNamedFramebuffer",
    /*  132 */ "glBufferAddressRangeNV",
    /*  133 */ "glBufferAttachMemoryNV",
    /*  134 */ "glBufferData",
    /*  135 */ "glBufferDataARB",
    /*  136 */ "glBufferPageCommitmentARB",
    /*  137 */ "glBufferPageCommitmentMemNV",
    /*  138 */ "glBufferParameteriAPPLE",
    /*  139 */ "glBufferStorage",
    /*  140 */ "glBufferStorageExternalEXT",
    /*  141 */ "glBufferStorageMemEXT",
    /*  142 */ "glBufferSubData",
    /*  143 */ "glBufferSubDataARB",
    /*  144 */ "glCallCommandListNV",
    /*  145 */ "glCheckFramebufferStatus",
    /*  146 */ "glCheckFramebufferStatusEXT",
    /*  147 */ "glCheckNamedFramebufferStatus",
    /*  148 */ "glCheckNamedFramebufferStatusEXT",
    /*  149 */ "glClampColor",
    /*  150 */ "glClampColorARB",
    /*  151 */ "glClear",
    /*  152 */ "glClearAccumxOES",
    /*  153 */ "glClearBufferData",
    /*  154 */ "glClearBufferSubData",
    /*  155 */ "glClearBufferfi",
    /*  156 */ "glClearBufferfv",
    /*  157 */ "glClearBufferiv",
    /*  158 */ "glClearBufferuiv",
    /*  159 */ "glClearColor",
    /*  160 */ "glClearColorIiEXT",
    /*  161 */ "glClearColorIuiEXT",
    /*  162 */ "glClearColorxOES",
    /*  163 */ "glClearDepth",
    /*  164 */ "glClearDepthdNV",
    /*  165 */ "glClearDepthf",
    /*  166 */ "glClearDepthfOES",
    /*  167 */ "glClearDepthxOES",
    /*  168 */ "glClearNamedBufferData",
    /*  169 */ "glClearNamedBufferDataEXT",
    /*  170 */ "glClearNamedBufferSubData",
    /*  171 */ "glClearNamedBufferSubDataEXT",
    /*  172 */ "glClearNamedFramebufferfi",
    /*  173 */ "glClearNamedFramebufferfv",
    /*  174 */ "glClearNamedFramebufferiv",
    /*  175 */ "glClearNamedFramebufferuiv",
    /*  176 */ "glClearStencil",
    /*  177 */ "glClearTexImage",
    /*  178 */ "glClearTexSubImage",
    /*  179 */ "glClientActiveTextureARB",
    /*  180 */ "glClientActiveVertexStreamATI",
    /*  181 */ "glClientAttribDefaultEXT",
    /*  182 */ "glClientWaitSemaphoreui64NVX",
    /*  183 */ "glClientWaitSync",
    /*  184 */ "glClipControl",
    /*  185 */ "glClipPlanefOES",
    /*  186 */ "glClipPlanexOES",
    /*  187 */ "glColor3fVertex3fSUN",
    /*  188 */ "glColor3fVertex3fvSUN",
    /*  189 */ "glColor3hNV",
    /*  190 */ "glColor3hvNV",
    /*  191 */ "glColor3xOES",
    /*  192 */ "glColor3xvOES",
    /*  193 */ "glColor4fNormal3fVertex3fSUN",
    /*  194 */ "glColor4fNormal3fVertex3fvSUN",
    /*  195 */ "glColor4hNV",
    /*  196 */ "glColor4hvNV",
    /*  197 */ "glColor4ubVertex2fSUN",
    /*  198 */ "glColor4ubVertex2fvSUN",
    /*  199 */ "glColor4ubVertex3fSUN",
    /*  200 */ "glColor4ubVertex3fvSUN",
    /*  201 */ "glColor4xOES",
    /*  202 */ "glColor4xvOES",
    /*  203 */ "glColorFormatNV",
    /*  204 */ "glColorFragmentOp1ATI",
    /*  205 */ "glColorFragmentOp2ATI",
    /*  206 */ "glColorFragmentOp3ATI",
    /*  207 */ "glColorMask",
    /*  208 */ "glColorMaskIndexedEXT",
    /*  209 */ "glColorMaski",
    /*  210 */ "glColorPointerEXT",
    /*  211 */ "glColorPointerListIBM",
    /*  212 */ "glColorPointervINTEL",
    /*  213 */ "glColorSubTableEXT",
    /*  214 */ "glColorTableEXT",
    /*  215 */ "glColorTableParameterfvSGI",
    /*  216 */ "glColorTableParameterivSGI",
    /*  217 */ "glColorTableSGI",
    /*  218 */ "glCombinerInputNV",
    /*  219 */ "glCombinerOutputNV",
    /*  220 */ "glCombinerParameterfNV",
    /*  221 */ "glCombinerParameterfvNV",
    /*  222 */ "glCombinerParameteriNV",
    /*  223 */ "glCombinerParameterivNV",
    /*  224 */ "glCombinerStageParameterfvNV",
    /*  225 */ "glCommandListSegmentsNV",
    /*  226 */ "glCompileCommandListNV",
    /*  227 */ "glCompileShader",
    /*  228 */ "glCompileShaderARB",
    /*  229 */ "glCompileShaderIncludeARB",
    /*  230 */ "glCompressedMultiTexImage1DEXT",
    /*  231 */ "glCompressedMultiTexImage2DEXT",
    /*  232 */ "glCompressedMultiTexImage3DEXT",
    /*  233 */ "glCompressedMultiTexSubImage1DEXT",
    /*  234 */ "glCompressedMultiTexSubImage2DEXT",
    /*  235 */ "glCompressedMultiTexSubImage3DEXT",
    /*  236 */ "glCompressedTexImage1D",
    /*  237 */ "glCompressedTexImage1DARB",
    /*  238 */ "glCompressedTexImage2D",
    /*  239 */ "glCompressedTexImage2DARB",
    /*  240 */ "glCompressedTexImage3D",
    /*  241 */ "glCompressedTexImage3DARB",
    /*  242 */ "glCompressedTexSubImage1D",
    /*  243 */ "glCompressedTexSubImage1DARB",
    /*  244 */ "glCompressedTexSubImage2D",
    /*  245 */ "glCompressedTexSubImage2DARB",
    /*  246 */ "glCompressedTexSubImage3D",
    /*  247 */ "glCompressedTexSubImage3DARB",
    /*  248 */ "glCompressedTextureImage1DEXT",
    /*  249 */ "glCompressedTextureImage2DEXT",
    /*  250 */ "glCompressedTextureImage3DEXT",
    /*  251 */ "glCompressedTextureSubImage1D",
    /*  252 */ "glCompressedTextureSubImage1DEXT",
    /*  253 */ "glCompressedTextureSubImage2D",
    /*  254 */ "glCompressedTextureSubImage2DEXT",
    /*  255 */ "glCompressedTextureSubImage3D",
    /*  256 */ "glCompressedTextureSubImage3DEXT",
    /*  257 */ "glConservativeRasterParameterfNV",
    /*  258 */ "glConservativeRasterParameteriNV",
    /*  259 */ "glConvolutionFilter1DEXT",
    /*  260 */ "glConvolutionFilter2DEXT",
    /*  261 */ "glConvolutionParameterfEXT",
    /*  262 */ "glConvolutionParameterfvEXT",
    /*  263 */ "glConvolutionParameteriEXT",
    /*  264 */ "glConvolutionParameterivEXT",
    /*  265 */ "glConvolutionParameterxOES",
    /*  266 */ "glConvolutionParameterxvOES",
    /*  267 */ "glCopyBufferSubData",
    /*  268 */ "glCopyColorSubTableEXT",
    /*  269 */ "glCopyColorTableSGI",
    /*  270 */ "glCopyConvolutionFilter1DEXT",
    /*  271 */ "glCopyConvolutionFilter2DEXT",
    /*  272 */ "glCopyImageSubData",
    /*  273 */ "glCopyImageSubDataNV",
    /*  274 */ "glCopyMultiTexImage1DEXT",
    /*  275 */ "glCopyMultiTexImage2DEXT",
    /*  276 */ "glCopyMultiTexSubImage1DEXT",
    /*  277 */ "glCopyMultiTexSubImage2DEXT",
    /*  278 */ "glCopyMultiTexSubImage3DEXT",
    /*  279 */ "glCopyNamedBufferSubData",
    /*  280 */ "glCopyPathNV",
    /*  281 */ "glCopyTexImage1D",
    /*  282 */ "glCopyTexImage1DEXT",
    /*  283 */ "glCopyTexImage2D",
    /*  284 */ "glCopyTexImage2DEXT",
    /*  285 */ "glCopyTexSubImage1D",
    /*  286 */ "glCopyTexSubImage1DEXT",
    /*  287 */ "glCopyTexSubImage2D",
    /*  288 */ "glCopyTexSubImage2DEXT",
    /*  289 */ "glCopyTexSubImage3D",
    /*  290 */ "glCopyTexSubImage3DEXT",
    /*  291 */ "glCopyTextureImage1DEXT",
    /*  292 */ "glCopyTextureImage2DEXT",
    /*  293 */ "glCopyTextureSubImage1D",
    /*  294 */ "glCopyTextureSubImage1DEXT",
    /*  295 */ "glCopyTextureSubImage2D",
    /*  296 */ "glCopyTextureSubImage2DEXT",
    /*  297 */ "glCopyTextureSubImage3D",
    /*  298 */ "glCopyTextureSubImage3DEXT",
    /*  299 */ "glCoverFillPathInstancedNV",
    /*  300 */ "glCoverFillPathNV",
    /*  301 */ "glCoverStrokePathInstancedNV",
    /*  302 */ "glCoverStrokePathNV",
    /*  303 */ "glCoverageModulationNV",
    /*  304 */ "glCoverageModulationTableNV",
    /*  305 */ "glCreateBuffers",
    /*  306 */ "glCreateCommandListsNV",
    /*  307 */ "glCreateFramebuffers",
    /*  308 */ "glCreateMemoryObjectsEXT",
    /*  309 */ "glCreatePerfQueryINTEL",
    /*  310 */ "glCreateProgram",
    /*  311 */ "glCreateProgramObjectARB",
    /*  312 */ "glCreateProgramPipelines",
    /*  313 */ "glCreateProgressFenceNVX",
    /*  314 */ "glCreateQueries",
    /*  315 */ "glCreateRenderbuffers",
    /*  316 */ "glCreateSamplers",
    /*  317 */ "glCreateSemaphoresNV",
    /*  318 */ "glCreateShader",
    /*  319 */ "glCreateShaderObjectARB",
    /*  320 */ "glCreateShaderProgramEXT",
    /*  321 */ "glCreateShaderProgramv",
    /*  322 */ "glCreateStatesNV",
    /*  323 */ "glCreateSyncFromCLeventARB",
    /*  324 */ "glCreateTextures",
    /*  325 */ "glCreateTransformFeedbacks",
    /*  326 */ "glCreateVertexArrays",
    /*  327 */ "glCullFace",
    /*  328 */ "glCullParameterdvEXT",
    /*  329 */ "glCullParameterfvEXT",
    /*  330 */ "glCurrentPaletteMatrixARB",
    /*  331 */ "glDebugMessageCallback",
    /*  332 */ "glDebugMessageCallbackAMD",
    /*  333 */ "glDebugMessageCallbackARB",
    /*  334 */ "glDebugMessageControl",
    /*  335 */ "glDebugMessageControlARB",
    /*  336 */ "glDebugMessageEnableAMD",
    /*  337 */ "glDebugMessageInsert",
    /*  338 */ "glDebugMessageInsertAMD",
    /*  339 */ "glDebugMessageInsertARB",
    /*  340 */ "glDeformSGIX",
    /*  341 */ "glDeformationMap3dSGIX",
    /*  342 */ "glDeformationMap3fSGIX",
    /*  343 */ "glDeleteAsyncMarkersSGIX",
    /*  344 */ "glDeleteBuffers",
    /*  345 */ "glDeleteBuffersARB",
    /*  346 */ "glDeleteCommandListsNV",
    /*  347 */ "glDeleteFencesAPPLE",
    /*  348 */ "glDeleteFencesNV",
    /*  349 */ "glDeleteFragmentShaderATI",
    /*  350 */ "glDeleteFramebuffers",
    /*  351 */ "glDeleteFramebuffersEXT",
    /*  352 */ "glDeleteMemoryObjectsEXT",
    /*  353 */ "glDeleteNamedStringARB",
    /*  354 */ "glDeleteNamesAMD",
    /*  355 */ "glDeleteObjectARB",
    /*  356 */ "glDeleteOcclusionQueriesNV",
    /*  357 */ "glDeletePathsNV",
    /*  358 */ "glDeletePerfMonitorsAMD",
    /*  359 */ "glDeletePerfQueryINTEL",
    /*  360 */ "glDeleteProgram",
    /*  361 */ "glDeleteProgramPipelines",
    /*  362 */ "glDeleteProgramsARB",
    /*  363 */ "glDeleteProgramsNV",
    /*  364 */ "glDeleteQueries",
    /*  365 */ "glDeleteQueriesARB",
    /*  366 */ "glDeleteQueryResourceTagNV",
    /*  367 */ "glDeleteRenderbuffers",
    /*  368 */ "glDeleteRenderbuffersEXT",
    /*  369 */ "glDeleteSamplers",
    /*  370 */ "glDeleteSemaphoresEXT",
    /*  371 */ "glDeleteShader",
    /*  372 */ "glDeleteStatesNV",
    /*  373 */ "glDeleteSync",
    /*  374 */ "glDeleteTextures",
    /*  375 */ "glDeleteTexturesEXT",
    /*  376 */ "glDeleteTransformFeedbacks",
    /*  377 */ "glDeleteTransformFeedbacksNV",
    /*  378 */ "glDeleteVertexArrays",
    /*  379 */ "glDeleteVertexArraysAPPLE",
    /*  380 */ "glDeleteVertexShaderEXT",
    /*  381 */ "glDepthBoundsEXT",
    /*  382 */ "glDepthBoundsdNV",
    /*  383 */ "glDepthFunc",
    /*  384 */ "glDepthMask",
    /*  385 */ "glDepthRange",
    /*  386 */ "glDepthRangeArraydvNV",
    /*  387 */ "glDepthRangeArrayv",
    /*  388 */ "glDepthRangeIndexed",
    /*  389 */ "glDepthRangeIndexeddNV",
    /*  390 */ "glDepthRangedNV",
    /*  391 */ "glDepthRangef",
    /*  392 */ "glDepthRangefOES",
    /*  393 */ "glDepthRangexOES",
    /*  394 */ "glDetachObjectARB",
    /*  395 */ "glDetachShader",
    /*  396 */ "glDetailTexFuncSGIS",
    /*  397 */ "glDisable",
    /*  398 */ "glDisableClientStateIndexedEXT",
    /*  399 */ "glDisableClientStateiEXT",
    /*  400 */ "glDisableIndexedEXT",
    /*  401 */ "glDisableVariantClientStateEXT",
    /*  402 */ "glDisableVertexArrayAttrib",
    /*  403 */ "glDisableVertexArrayAttribEXT",
    /*  404 */ "glDisableVertexArrayEXT",
    /*  405 */ "glDisableVertexAttribAPPLE",
    /*  406 */ "glDisableVertexAttribArray",
    /*  407 */ "glDisableVertexAttribArrayARB",
    /*  408 */ "glDisablei",
    /*  409 */ "glDispatchCompute",
    /*  410 */ "glDispatchComputeGroupSizeARB",
    /*  411 */ "glDispatchComputeIndirect",
    /*  412 */ "glDrawArrays",
    /*  413 */ "glDrawArraysEXT",
    /*  414 */ "glDrawArraysIndirect",
    /*  415 */ "glDrawArraysInstanced",
    /*  416 */ "glDrawArraysInstancedARB",
    /*  417 */ "glDrawArraysInstancedBaseInstance",
    /*  418 */ "glDrawArraysInstancedEXT",
    /*  419 */ "glDrawBuffer",
    /*  420 */ "glDrawBuffers",
    /*  421 */ "glDrawBuffersARB",
    /*  422 */ "glDrawBuffersATI",
    /*  423 */ "glDrawCommandsAddressNV",
    /*  424 */ "glDrawCommandsNV",
    /*  425 */ "glDrawCommandsStatesAddressNV",
    /*  426 */ "glDrawCommandsStatesNV",
    /*  427 */ "glDrawElementArrayAPPLE",
    /*  428 */ "glDrawElementArrayATI",
    /*  429 */ "glDrawElements",
    /*  430 */ "glDrawElementsBaseVertex",
    /*  431 */ "glDrawElementsIndirect",
    /*  432 */ "glDrawElementsInstanced",
    /*  433 */ "glDrawElementsInstancedARB",
    /*  434 */ "glDrawElementsInstancedBaseInstance",
    /*  435 */ "glDrawElementsInstancedBaseVertex",
    /*  436 */ "glDrawElementsInstancedBaseVertexBaseInstance",
    /*  437 */ "glDrawElementsInstancedEXT",
    /*  438 */ "glDrawMeshArraysSUN",
    /*  439 */ "glDrawMeshTasksIndirectNV",
    /*  440 */ "glDrawMeshTasksNV",
    /*  441 */ "glDrawRangeElementArrayAPPLE",
    /*  442 */ "glDrawRangeElementArrayATI",
    /*  443 */ "glDrawRangeElements",
    /*  444 */ "glDrawRangeElementsBaseVertex",
    /*  445 */ "glDrawRangeElementsEXT",
    /*  446 */ "glDrawTextureNV",
    /*  447 */ "glDrawTransformFeedback",
    /*  448 */ "glDrawTransformFeedbackInstanced",
    /*  449 */ "glDrawTransformFeedbackNV",
    /*  450 */ "glDrawTransformFeedbackStream",
    /*  451 */ "glDrawTransformFeedbackStreamInstanced",
    /*  452 */ "glDrawVkImageNV",
    /*  453 */ "glEGLImageTargetTexStorageEXT",
    /*  454 */ "glEGLImageTargetTextureStorageEXT",
    /*  455 */ "glEdgeFlagFormatNV",
    /*  456 */ "glEdgeFlagPointerEXT",
    /*  457 */ "glEdgeFlagPointerListIBM",
    /*  458 */ "glElementPointerAPPLE",
    /*  459 */ "glElementPointerATI",
    /*  460 */ "glEnable",
    /*  461 */ "glEnableClientStateIndexedEXT",
    /*  462 */ "glEnableClientStateiEXT",
    /*  463 */ "glEnableIndexedEXT",
    /*  464 */ "glEnableVariantClientStateEXT",
    /*  465 */ "glEnableVertexArrayAttrib",
    /*  466 */ "glEnableVertexArrayAttribEXT",
    /*  467 */ "glEnableVertexArrayEXT",
    /*  468 */ "glEnableVertexAttribAPPLE",
    /*  469 */ "glEnableVertexAttribArray",
    /*  470 */ "glEnableVertexAttribArrayARB",
    /*  471 */ "glEnablei",
    /*  472 */ "glEndConditionalRender",
    /*  473 */ "glEndConditionalRenderNV",
    /*  474 */ "glEndConditionalRenderNVX",
    /*  475 */ "glEndFragmentShaderATI",
    /*  476 */ "glEndOcclusionQueryNV",
    /*  477 */ "glEndPerfMonitorAMD",
    /*  478 */ "glEndPerfQueryINTEL",
    /*  479 */ "glEndQuery",
    /*  480 */ "glEndQueryARB",
    /*  481 */ "glEndQueryIndexed",
    /*  482 */ "glEndTransformFeedback",
    /*  483 */ "glEndTransformFeedbackEXT",
    /*  484 */ "glEndTransformFeedbackNV",
    /*  485 */ "glEndVertexShaderEXT",
    /*  486 */ "glEndVideoCaptureNV",
    /*  487 */ "glEvalCoord1xOES",
    /*  488 */ "glEvalCoord1xvOES",
    /*  489 */ "glEvalCoord2xOES",
    /*  490 */ "glEvalCoord2xvOES",
    /*  491 */ "glEvalMapsNV",
    /*  492 */ "glEvaluateDepthValuesARB",
    /*  493 */ "glExecuteProgramNV",
    /*  494 */ "glExtractComponentEXT",
    /*  495 */ "glFeedbackBufferxOES",
    /*  496 */ "glFenceSync",
    /*  497 */ "glFinalCombinerInputNV",
    /*  498 */ "glFinish",
    /*  499 */ "glFinishAsyncSGIX",
    /*  500 */ "glFinishFenceAPPLE",
    /*  501 */ "glFinishFenceNV",
    /*  502 */ "glFinishObjectAPPLE",
    /*  503 */ "glFinishTextureSUNX",
    /*  504 */ "glFlush",
    /*  505 */ "glFlushMappedBufferRange",
    /*  506 */ "glFlushMappedBufferRangeAPPLE",
    /*  507 */ "glFlushMappedNamedBufferRange",
    /*  508 */ "glFlushMappedNamedBufferRangeEXT",
    /*  509 */ "glFlushPixelDataRangeNV",
    /*  510 */ "glFlushRasterSGIX",
    /*  511 */ "glFlushStaticDataIBM",
    /*  512 */ "glFlushVertexArrayRangeAPPLE",
    /*  513 */ "glFlushVertexArrayRangeNV",
    /*  514 */ "glFogCoordFormatNV",
    /*  515 */ "glFogCoordPointerEXT",
    /*  516 */ "glFogCoordPointerListIBM",
    /*  517 */ "glFogCoorddEXT",
    /*  518 */ "glFogCoorddvEXT",
    /*  519 */ "glFogCoordfEXT",
    /*  520 */ "glFogCoordfvEXT",
    /*  521 */ "glFogCoordhNV",
    /*  522 */ "glFogCoordhvNV",
    /*  523 */ "glFogFuncSGIS",
    /*  524 */ "glFogxOES",
    /*  525 */ "glFogxvOES",
    /*  526 */ "glFragmentColorMaterialSGIX",
    /*  527 */ "glFragmentCoverageColorNV",
    /*  528 */ "glFragmentLightModelfSGIX",
    /*  529 */ "glFragmentLightModelfvSGIX",
    /*  530 */ "glFragmentLightModeliSGIX",
    /*  531 */ "glFragmentLightModelivSGIX",
    /*  532 */ "glFragmentLightfSGIX",
    /*  533 */ "glFragmentLightfvSGIX",
    /*  534 */ "glFragmentLightiSGIX",
    /*  535 */ "glFragmentLightivSGIX",
    /*  536 */ "glFragmentMaterialfSGIX",
    /*  537 */ "glFragmentMaterialfvSGIX",
    /*  538 */ "glFragmentMaterialiSGIX",
    /*  539 */ "glFragmentMaterialivSGIX",
    /*  540 */ "glFrameTerminatorGREMEDY",
    /*  541 */ "glFrameZoomSGIX",
    /*  542 */ "glFramebufferDrawBufferEXT",
    /*  543 */ "glFramebufferDrawBuffersEXT",
    /*  544 */ "glFramebufferFetchBarrierEXT",
    /*  545 */ "glFramebufferParameteri",
    /*  546 */ "glFramebufferParameteriMESA",
    /*  547 */ "glFramebufferReadBufferEXT",
    /*  548 */ "glFramebufferRenderbuffer",
    /*  549 */ "glFramebufferRenderbufferEXT",
    /*  550 */ "glFramebufferSampleLocationsfvARB",
    /*  551 */ "glFramebufferSampleLocationsfvNV",
    /*  552 */ "glFramebufferSamplePositionsfvAMD",
    /*  553 */ "glFramebufferTexture",
    /*  554 */ "glFramebufferTexture1D",
    /*  555 */ "glFramebufferTexture1DEXT",
    /*  556 */ "glFramebufferTexture2D",
    /*  557 */ "glFramebufferTexture2DEXT",
    /*  558 */ "glFramebufferTexture3D",
    /*  559 */ "glFramebufferTexture3DEXT",
    /*  560 */ "glFramebufferTextureARB",
    /*  561 */ "glFramebufferTextureEXT",
    /*  562 */ "glFramebufferTextureFaceARB",
    /*  563 */ "glFramebufferTextureFaceEXT",
    /*  564 */ "glFramebufferTextureLayer",
    /*  565 */ "glFramebufferTextureLayerARB",
    /*  566 */ "glFramebufferTextureLayerEXT",
    /*  567 */ "glFramebufferTextureMultiviewOVR",
    /*  568 */ "glFreeObjectBufferATI",
    /*  569 */ "glFrontFace",
    /*  570 */ "glFrustumfOES",
    /*  571 */ "glFrustumxOES",
    /*  572 */ "glGenAsyncMarkersSGIX",
    /*  573 */ "glGenBuffers",
    /*  574 */ "glGenBuffersARB",
    /*  575 */ "glGenFencesAPPLE",
    /*  576 */ "glGenFencesNV",
    /*  577 */ "glGenFragmentShadersATI",
    /*  578 */ "glGenFramebuffers",
    /*  579 */ "glGenFramebuffersEXT",
    /*  580 */ "glGenNamesAMD",
    /*  581 */ "glGenOcclusionQueriesNV",
    /*  582 */ "glGenPathsNV",
    /*  583 */ "glGenPerfMonitorsAMD",
    /*  584 */ "glGenProgramPipelines",
    /*  585 */ "glGenProgramsARB",
    /*  586 */ "glGenProgramsNV",
    /*  587 */ "glGenQueries",
    /*  588 */ "glGenQueriesARB",
    /*  589 */ "glGenQueryResourceTagNV",
    /*  590 */ "glGenRenderbuffers",
    /*  591 */ "glGenRenderbuffersEXT",
    /*  592 */ "glGenSamplers",
    /*  593 */ "glGenSemaphoresEXT",
    /*  594 */ "glGenSymbolsEXT",
    /*  595 */ "glGenTextures",
    /*  596 */ "glGenTexturesEXT",
    /*  597 */ "glGenTransformFeedbacks",
    /*  598 */ "glGenTransformFeedbacksNV",
    /*  599 */ "glGenVertexArrays",
    /*  600 */ "glGenVertexArraysAPPLE",
    /*  601 */ "glGenVertexShadersEXT",
    /*  602 */ "glGenerateMipmap",
    /*  603 */ "glGenerateMipmapEXT",
    /*  604 */ "glGenerateMultiTexMipmapEXT",
    /*  605 */ "glGenerateTextureMipmap",
    /*  606 */ "glGenerateTextureMipmapEXT",
    /*  607 */ "glGetActiveAtomicCounterBufferiv",
    /*  608 */ "glGetActiveAttrib",
    /*  609 */ "glGetActiveAttribARB",
    /*  610 */ "glGetActiveSubroutineName",
    /*  611 */ "glGetActiveSubroutineUniformName",
    /*  612 */ "glGetActiveSubroutineUniformiv",
    /*  613 */ "glGetActiveUniform",
    /*  614 */ "glGetActiveUniformARB",
    /*  615 */ "glGetActiveUniformBlockName",
    /*  616 */ "glGetActiveUniformBlockiv",
    /*  617 */ "glGetActiveUniformName",
    /*  618 */ "glGetActiveUniformsiv",
    /*  619 */ "glGetActiveVaryingNV",
    /*  620 */ "glGetArrayObjectfvATI",
    /*  621 */ "glGetArrayObjectivATI",
    /*  622 */ "glGetAttachedObjectsARB",
    /*  623 */ "glGetAttachedShaders",
    /*  624 */ "glGetAttribLocation",
    /*  625 */ "glGetAttribLocationARB",
    /*  626 */ "glGetBooleanIndexedvEXT",
    /*  627 */ "glGetBooleani_v",
    /*  628 */ "glGetBooleanv",
    /*  629 */ "glGetBufferParameteri64v",
    /*  630 */ "glGetBufferParameteriv",
    /*  631 */ "glGetBufferParameterivARB",
    /*  632 */ "glGetBufferParameterui64vNV",
    /*  633 */ "glGetBufferPointerv",
    /*  634 */ "glGetBufferPointervARB",
    /*  635 */ "glGetBufferSubData",
    /*  636 */ "glGetBufferSubDataARB",
    /*  637 */ "glGetClipPlanefOES",
    /*  638 */ "glGetClipPlanexOES",
    /*  639 */ "glGetColorTableEXT",
    /*  640 */ "glGetColorTableParameterfvEXT",
    /*  641 */ "glGetColorTableParameterfvSGI",
    /*  642 */ "glGetColorTableParameterivEXT",
    /*  643 */ "glGetColorTableParameterivSGI",
    /*  644 */ "glGetColorTableSGI",
    /*  645 */ "glGetCombinerInputParameterfvNV",
    /*  646 */ "glGetCombinerInputParameterivNV",
    /*  647 */ "glGetCombinerOutputParameterfvNV",
    /*  648 */ "glGetCombinerOutputParameterivNV",
    /*  649 */ "glGetCombinerStageParameterfvNV",
    /*  650 */ "glGetCommandHeaderNV",
    /*  651 */ "glGetCompressedMultiTexImageEXT",
    /*  652 */ "glGetCompressedTexImage",
    /*  653 */ "glGetCompressedTexImageARB",
    /*  654 */ "glGetCompressedTextureImage",
    /*  655 */ "glGetCompressedTextureImageEXT",
    /*  656 */ "glGetCompressedTextureSubImage",
    /*  657 */ "glGetConvolutionFilterEXT",
    /*  658 */ "glGetConvolutionParameterfvEXT",
    /*  659 */ "glGetConvolutionParameterivEXT",
    /*  660 */ "glGetConvolutionParameterxvOES",
    /*  661 */ "glGetCoverageModulationTableNV",
    /*  662 */ "glGetDebugMessageLog",
    /*  663 */ "glGetDebugMessageLogAMD",
    /*  664 */ "glGetDebugMessageLogARB",
    /*  665 */ "glGetDetailTexFuncSGIS",
    /*  666 */ "glGetDoubleIndexedvEXT",
    /*  667 */ "glGetDoublei_v",
    /*  668 */ "glGetDoublei_vEXT",
    /*  669 */ "glGetDoublev",
    /*  670 */ "glGetError",
    /*  671 */ "glGetFenceivNV",
    /*  672 */ "glGetFinalCombinerInputParameterfvNV",
    /*  673 */ "glGetFinalCombinerInputParameterivNV",
    /*  674 */ "glGetFirstPerfQueryIdINTEL",
    /*  675 */ "glGetFixedvOES",
    /*  676 */ "glGetFloatIndexedvEXT",
    /*  677 */ "glGetFloati_v",
    /*  678 */ "glGetFloati_vEXT",
    /*  679 */ "glGetFloatv",
    /*  680 */ "glGetFogFuncSGIS",
    /*  681 */ "glGetFragDataIndex",
    /*  682 */ "glGetFragDataLocation",
    /*  683 */ "glGetFragDataLocationEXT",
    /*  684 */ "glGetFragmentLightfvSGIX",
    /*  685 */ "glGetFragmentLightivSGIX",
    /*  686 */ "glGetFragmentMaterialfvSGIX",
    /*  687 */ "glGetFragmentMaterialivSGIX",
    /*  688 */ "glGetFramebufferAttachmentParameteriv",
    /*  689 */ "glGetFramebufferAttachmentParameterivEXT",
    /*  690 */ "glGetFramebufferParameterfvAMD",
    /*  691 */ "glGetFramebufferParameteriv",
    /*  692 */ "glGetFramebufferParameterivEXT",
    /*  693 */ "glGetFramebufferParameterivMESA",
    /*  694 */ "glGetGraphicsResetStatus",
    /*  695 */ "glGetGraphicsResetStatusARB",
    /*  696 */ "glGetHandleARB",
    /*  697 */ "glGetHistogramEXT",
    /*  698 */ "glGetHistogramParameterfvEXT",
    /*  699 */ "glGetHistogramParameterivEXT",
    /*  700 */ "glGetHistogramParameterxvOES",
    /*  701 */ "glGetImageHandleARB",
    /*  702 */ "glGetImageHandleNV",
    /*  703 */ "glGetImageTransformParameterfvHP",
    /*  704 */ "glGetImageTransformParameterivHP",
    /*  705 */ "glGetInfoLogARB",
    /*  706 */ "glGetInstrumentsSGIX",
    /*  707 */ "glGetInteger64i_v",
    /*  708 */ "glGetInteger64v",
    /*  709 */ "glGetIntegerIndexedvEXT",
    /*  710 */ "glGetIntegeri_v",
    /*  711 */ "glGetIntegerui64i_vNV",
    /*  712 */ "glGetIntegerui64vNV",
    /*  713 */ "glGetIntegerv",
    /*  714 */ "glGetInternalformatSampleivNV",
    /*  715 */ "glGetInternalformati64v",
    /*  716 */ "glGetInternalformativ",
    /*  717 */ "glGetInvariantBooleanvEXT",
    /*  718 */ "glGetInvariantFloatvEXT",
    /*  719 */ "glGetInvariantIntegervEXT",
    /*  720 */ "glGetLightxOES",
    /*  721 */ "glGetListParameterfvSGIX",
    /*  722 */ "glGetListParameterivSGIX",
    /*  723 */ "glGetLocalConstantBooleanvEXT",
    /*  724 */ "glGetLocalConstantFloatvEXT",
    /*  725 */ "glGetLocalConstantIntegervEXT",
    /*  726 */ "glGetMapAttribParameterfvNV",
    /*  727 */ "glGetMapAttribParameterivNV",
    /*  728 */ "glGetMapControlPointsNV",
    /*  729 */ "glGetMapParameterfvNV",
    /*  730 */ "glGetMapParameterivNV",
    /*  731 */ "glGetMapxvOES",
    /*  732 */ "glGetMaterialxOES",
    /*  733 */ "glGetMemoryObjectDetachedResourcesuivNV",
    /*  734 */ "glGetMemoryObjectParameterivEXT",
    /*  735 */ "glGetMinmaxEXT",
    /*  736 */ "glGetMinmaxParameterfvEXT",
    /*  737 */ "glGetMinmaxParameterivEXT",
    /*  738 */ "glGetMultiTexEnvfvEXT",
    /*  739 */ "glGetMultiTexEnvivEXT",
    /*  740 */ "glGetMultiTexGendvEXT",
    /*  741 */ "glGetMultiTexGenfvEXT",
    /*  742 */ "glGetMultiTexGenivEXT",
    /*  743 */ "glGetMultiTexImageEXT",
    /*  744 */ "glGetMultiTexLevelParameterfvEXT",
    /*  745 */ "glGetMultiTexLevelParameterivEXT",
    /*  746 */ "glGetMultiTexParameterIivEXT",
    /*  747 */ "glGetMultiTexParameterIuivEXT",
    /*  748 */ "glGetMultiTexParameterfvEXT",
    /*  749 */ "glGetMultiTexParameterivEXT",
    /*  750 */ "glGetMultisamplefv",
    /*  751 */ "glGetMultisamplefvNV",
    /*  752 */ "glGetNamedBufferParameteri64v",
    /*  753 */ "glGetNamedBufferParameteriv",
    /*  754 */ "glGetNamedBufferParameterivEXT",
    /*  755 */ "glGetNamedBufferParameterui64vNV",
    /*  756 */ "glGetNamedBufferPointerv",
    /*  757 */ "glGetNamedBufferPointervEXT",
    /*  758 */ "glGetNamedBufferSubData",
    /*  759 */ "glGetNamedBufferSubDataEXT",
    /*  760 */ "glGetNamedFramebufferAttachmentParameteriv",
    /*  761 */ "glGetNamedFramebufferAttachmentParameterivEXT",
    /*  762 */ "glGetNamedFramebufferParameterfvAMD",
    /*  763 */ "glGetNamedFramebufferParameteriv",
    /*  764 */ "glGetNamedFramebufferParameterivEXT",
    /*  765 */ "glGetNamedProgramLocalParameterIivEXT",
    /*  766 */ "glGetNamedProgramLocalParameterIuivEXT",
    /*  767 */ "glGetNamedProgramLocalParameterdvEXT",
    /*  768 */ "glGetNamedProgramLocalParameterfvEXT",
    /*  769 */ "glGetNamedProgramStringEXT",
    /*  770 */ "glGetNamedProgramivEXT",
    /*  771 */ "glGetNamedRenderbufferParameteriv",
    /*  772 */ "glGetNamedRenderbufferParameterivEXT",
    /*  773 */ "glGetNamedStringARB",
    /*  774 */ "glGetNamedStringivARB",
    /*  775 */ "glGetNextPerfQueryIdINTEL",
    /*  776 */ "glGetObjectBufferfvATI",
    /*  777 */ "glGetObjectBufferivATI",
    /*  778 */ "glGetObjectLabel",
    /*  779 */ "glGetObjectLabelEXT",
    /*  780 */ "glGetObjectParameterfvARB",
    /*  781 */ "glGetObjectParameterivAPPLE",
    /*  782 */ "glGetObjectParameterivARB",
    /*  783 */ "glGetObjectPtrLabel",
    /*  784 */ "glGetOcclusionQueryivNV",
    /*  785 */ "glGetOcclusionQueryuivNV",
    /*  786 */ "glGetPathCommandsNV",
    /*  787 */ "glGetPathCoordsNV",
    /*  788 */ "glGetPathDashArrayNV",
    /*  789 */ "glGetPathLengthNV",
    /*  790 */ "glGetPathMetricRangeNV",
    /*  791 */ "glGetPathMetricsNV",
    /*  792 */ "glGetPathParameterfvNV",
    /*  793 */ "glGetPathParameterivNV",
    /*  794 */ "glGetPathSpacingNV",
    /*  795 */ "glGetPerfCounterInfoINTEL",
    /*  796 */ "glGetPerfMonitorCounterDataAMD",
    /*  797 */ "glGetPerfMonitorCounterInfoAMD",
    /*  798 */ "glGetPerfMonitorCounterStringAMD",
    /*  799 */ "glGetPerfMonitorCountersAMD",
    /*  800 */ "glGetPerfMonitorGroupStringAMD",
    /*  801 */ "glGetPerfMonitorGroupsAMD",
    /*  802 */ "glGetPerfQueryDataINTEL",
    /*  803 */ "glGetPerfQueryIdByNameINTEL",
    /*  804 */ "glGetPerfQueryInfoINTEL",
    /*  805 */ "glGetPixelMapxv",
    /*  806 */ "glGetPixelTexGenParameterfvSGIS",
    /*  807 */ "glGetPixelTexGenParameterivSGIS",
    /*  808 */ "glGetPixelTransformParameterfvEXT",
    /*  809 */ "glGetPixelTransformParameterivEXT",
    /*  810 */ "glGetPointerIndexedvEXT",
    /*  811 */ "glGetPointeri_vEXT",
    /*  812 */ "glGetPointerv",
    /*  813 */ "glGetPointervEXT",
    /*  814 */ "glGetProgramBinary",
    /*  815 */ "glGetProgramEnvParameterIivNV",
    /*  816 */ "glGetProgramEnvParameterIuivNV",
    /*  817 */ "glGetProgramEnvParameterdvARB",
    /*  818 */ "glGetProgramEnvParameterfvARB",
    /*  819 */ "glGetProgramInfoLog",
    /*  820 */ "glGetProgramInterfaceiv",
    /*  821 */ "glGetProgramLocalParameterIivNV",
    /*  822 */ "glGetProgramLocalParameterIuivNV",
    /*  823 */ "glGetProgramLocalParameterdvARB",
    /*  824 */ "glGetProgramLocalParameterfvARB",
    /*  825 */ "glGetProgramNamedParameterdvNV",
    /*  826 */ "glGetProgramNamedParameterfvNV",
    /*  827 */ "glGetProgramParameterdvNV",
    /*  828 */ "glGetProgramParameterfvNV",
    /*  829 */ "glGetProgramPipelineInfoLog",
    /*  830 */ "glGetProgramPipelineiv",
    /*  831 */ "glGetProgramResourceIndex",
    /*  832 */ "glGetProgramResourceLocation",
    /*  833 */ "glGetProgramResourceLocationIndex",
    /*  834 */ "glGetProgramResourceName",
    /*  835 */ "glGetProgramResourcefvNV",
    /*  836 */ "glGetProgramResourceiv",
    /*  837 */ "glGetProgramStageiv",
    /*  838 */ "glGetProgramStringARB",
    /*  839 */ "glGetProgramStringNV",
    /*  840 */ "glGetProgramSubroutineParameteruivNV",
    /*  841 */ "glGetProgramiv",
    /*  842 */ "glGetProgramivARB",
    /*  843 */ "glGetProgramivNV",
    /*  844 */ "glGetQueryBufferObjecti64v",
    /*  845 */ "glGetQueryBufferObjectiv",
    /*  846 */ "glGetQueryBufferObjectui64v",
    /*  847 */ "glGetQueryBufferObjectuiv",
    /*  848 */ "glGetQueryIndexediv",
    /*  849 */ "glGetQueryObjecti64v",
    /*  850 */ "glGetQueryObjecti64vEXT",
    /*  851 */ "glGetQueryObjectiv",
    /*  852 */ "glGetQueryObjectivARB",
    /*  853 */ "glGetQueryObjectui64v",
    /*  854 */ "glGetQueryObjectui64vEXT",
    /*  855 */ "glGetQueryObjectuiv",
    /*  856 */ "glGetQueryObjectuivARB",
    /*  857 */ "glGetQueryiv",
    /*  858 */ "glGetQueryivARB",
    /*  859 */ "glGetRenderbufferParameteriv",
    /*  860 */ "glGetRenderbufferParameterivEXT",
    /*  861 */ "glGetSamplerParameterIiv",
    /*  862 */ "glGetSamplerParameterIuiv",
    /*  863 */ "glGetSamplerParameterfv",
    /*  864 */ "glGetSamplerParameteriv",
    /*  865 */ "glGetSemaphoreParameterivNV",
    /*  866 */ "glGetSemaphoreParameterui64vEXT",
    /*  867 */ "glGetSeparableFilterEXT",
    /*  868 */ "glGetShaderInfoLog",
    /*  869 */ "glGetShaderPrecisionFormat",
    /*  870 */ "glGetShaderSource",
    /*  871 */ "glGetShaderSourceARB",
    /*  872 */ "glGetShaderiv",
    /*  873 */ "glGetShadingRateImagePaletteNV",
    /*  874 */ "glGetShadingRateSampleLocationivNV",
    /*  875 */ "glGetSharpenTexFuncSGIS",
    /*  876 */ "glGetStageIndexNV",
    /*  877 */ "glGetString",
    /*  878 */ "glGetStringi",
    /*  879 */ "glGetSubroutineIndex",
    /*  880 */ "glGetSubroutineUniformLocation",
    /*  881 */ "glGetSynciv",
    /*  882 */ "glGetTexBumpParameterfvATI",
    /*  883 */ "glGetTexBumpParameterivATI",
    /*  884 */ "glGetTexEnvxvOES",
    /*  885 */ "glGetTexFilterFuncSGIS",
    /*  886 */ "glGetTexGenxvOES",
    /*  887 */ "glGetTexImage",
    /*  888 */ "glGetTexLevelParameterfv",
    /*  889 */ "glGetTexLevelParameteriv",
    /*  890 */ "glGetTexLevelParameterxvOES",
    /*  891 */ "glGetTexParameterIiv",
    /*  892 */ "glGetTexParameterIivEXT",
    /*  893 */ "glGetTexParameterIuiv",
    /*  894 */ "glGetTexParameterIuivEXT",
    /*  895 */ "glGetTexParameterPointervAPPLE",
    /*  896 */ "glGetTexParameterfv",
    /*  897 */ "glGetTexParameteriv",
    /*  898 */ "glGetTexParameterxvOES",
    /*  899 */ "glGetTextureHandleARB",
    /*  900 */ "glGetTextureHandleNV",
    /*  901 */ "glGetTextureImage",
    /*  902 */ "glGetTextureImageEXT",
    /*  903 */ "glGetTextureLevelParameterfv",
    /*  904 */ "glGetTextureLevelParameterfvEXT",
    /*  905 */ "glGetTextureLevelParameteriv",
    /*  906 */ "glGetTextureLevelParameterivEXT",
    /*  907 */ "glGetTextureParameterIiv",
    /*  908 */ "glGetTextureParameterIivEXT",
    /*  909 */ "glGetTextureParameterIuiv",
    /*  910 */ "glGetTextureParameterIuivEXT",
    /*  911 */ "glGetTextureParameterfv",
    /*  912 */ "glGetTextureParameterfvEXT",
    /*  913 */ "glGetTextureParameteriv",
    /*  914 */ "glGetTextureParameterivEXT",
    /*  915 */ "glGetTextureSamplerHandleARB",
    /*  916 */ "glGetTextureSamplerHandleNV",
    /*  917 */ "glGetTextureSubImage",
    /*  918 */ "glGetTrackMatrixivNV",
    /*  919 */ "glGetTransformFeedbackVarying",
    /*  920 */ "glGetTransformFeedbackVaryingEXT",
    /*  921 */ "glGetTransformFeedbackVaryingNV",
    /*  922 */ "glGetTransformFeedbacki64_v",
    /*  923 */ "glGetTransformFeedbacki_v",
    /*  924 */ "glGetTransformFeedbackiv",
    /*  925 */ "glGetUniformBlockIndex",
    /*  926 */ "glGetUniformBufferSizeEXT",
    /*  927 */ "glGetUniformIndices",
    /*  928 */ "glGetUniformLocation",
    /*  929 */ "glGetUniformLocationARB",
    /*  930 */ "glGetUniformOffsetEXT",
    /*  931 */ "glGetUniformSubroutineuiv",
    /*  932 */ "glGetUniformdv",
    /*  933 */ "glGetUniformfv",
    /*  934 */ "glGetUniformfvARB",
    /*  935 */ "glGetUniformi64vARB",
    /*  936 */ "glGetUniformi64vNV",
    /*  937 */ "glGetUniformiv",
    /*  938 */ "glGetUniformivARB",
    /*  939 */ "glGetUniformui64vARB",
    /*  940 */ "glGetUniformui64vNV",
    /*  941 */ "glGetUniformuiv",
    /*  942 */ "glGetUniformuivEXT",
    /*  943 */ "glGetUnsignedBytei_vEXT",
    /*  944 */ "glGetUnsignedBytevEXT",
    /*  945 */ "glGetVariantArrayObjectfvATI",
    /*  946 */ "glGetVariantArrayObjectivATI",
    /*  947 */ "glGetVariantBooleanvEXT",
    /*  948 */ "glGetVariantFloatvEXT",
    /*  949 */ "glGetVariantIntegervEXT",
    /*  950 */ "glGetVariantPointervEXT",
    /*  951 */ "glGetVaryingLocationNV",
    /*  952 */ "glGetVertexArrayIndexed64iv",
    /*  953 */ "glGetVertexArrayIndexediv",
    /*  954 */ "glGetVertexArrayIntegeri_vEXT",
    /*  955 */ "glGetVertexArrayIntegervEXT",
    /*  956 */ "glGetVertexArrayPointeri_vEXT",
    /*  957 */ "glGetVertexArrayPointervEXT",
    /*  958 */ "glGetVertexArrayiv",
    /*  959 */ "glGetVertexAttribArrayObjectfvATI",
    /*  960 */ "glGetVertexAttribArrayObjectivATI",
    /*  961 */ "glGetVertexAttribIiv",
    /*  962 */ "glGetVertexAttribIivEXT",
    /*  963 */ "glGetVertexAttribIuiv",
    /*  964 */ "glGetVertexAttribIuivEXT",
    /*  965 */ "glGetVertexAttribLdv",
    /*  966 */ "glGetVertexAttribLdvEXT",
    /*  967 */ "glGetVertexAttribLi64vNV",
    /*  968 */ "glGetVertexAttribLui64vARB",
    /*  969 */ "glGetVertexAttribLui64vNV",
    /*  970 */ "glGetVertexAttribPointerv",
    /*  971 */ "glGetVertexAttribPointervARB",
    /*  972 */ "glGetVertexAttribPointervNV",
    /*  973 */ "glGetVertexAttribdv",
    /*  974 */ "glGetVertexAttribdvARB",
    /*  975 */ "glGetVertexAttribdvNV",
    /*  976 */ "glGetVertexAttribfv",
    /*  977 */ "glGetVertexAttribfvARB",
    /*  978 */ "glGetVertexAttribfvNV",
    /*  979 */ "glGetVertexAttribiv",
    /*  980 */ "glGetVertexAttribivARB",
    /*  981 */ "glGetVertexAttribivNV",
    /*  982 */ "glGetVideoCaptureStreamdvNV",
    /*  983 */ "glGetVideoCaptureStreamfvNV",
    /*  984 */ "glGetVideoCaptureStreamivNV",
    /*  985 */ "glGetVideoCaptureivNV",
    /*  986 */ "glGetVideoi64vNV",
    /*  987 */ "glGetVideoivNV",
    /*  988 */ "glGetVideoui64vNV",
    /*  989 */ "glGetVideouivNV",
    /*  990 */ "glGetVkProcAddrNV",
    /*  991 */ "glGetnCompressedTexImage",
    /*  992 */ "glGetnCompressedTexImageARB",
    /*  993 */ "glGetnTexImage",
    /*  994 */ "glGetnTexImageARB",
    /*  995 */ "glGetnUniformdv",
    /*  996 */ "glGetnUniformdvARB",
    /*  997 */ "glGetnUniformfv",
    /*  998 */ "glGetnUniformfvARB",
    /*  999 */ "glGetnUniformi64vARB",
    /* 1000 */ "glGetnUniformiv",
    /* 1001 */ "glGetnUniformivARB",
    /* 1002 */ "glGetnUniformui64vARB",
    /* 1003 */ "glGetnUniformuiv",
    /* 1004 */ "glGetnUniformuivARB",
    /* 1005 */ "glGlobalAlphaFactorbSUN",
    /* 1006 */ "glGlobalAlphaFactordSUN",
    /* 1007 */ "glGlobalAlphaFactorfSUN",
    /* 1008 */ "glGlobalAlphaFactoriSUN",
    /* 1009 */ "glGlobalAlphaFactorsSUN",
    /* 1010 */ "glGlobalAlphaFactorubSUN",
    /* 1011 */ "glGlobalAlphaFactoruiSUN",
    /* 1012 */ "glGlobalAlphaFactorusSUN",
    /* 1013 */ "glHint",
    /* 1014 */ "glHintPGI",
    /* 1015 */ "glHistogramEXT",
    /* 1016 */ "glIglooInterfaceSGIX",
    /* 1017 */ "glImageTransformParameterfHP",
    /* 1018 */ "glImageTransformParameterfvHP",
    /* 1019 */ "glImageTransformParameteriHP",
    /* 1020 */ "glImageTransformParameterivHP",
    /* 1021 */ "glImportMemoryFdEXT",
    /* 1022 */ "glImportMemoryWin32HandleEXT",
    /* 1023 */ "glImportMemoryWin32NameEXT",
    /* 1024 */ "glImportMemoryZirconHandleANGLE",
    /* 1025 */ "glImportSemaphoreFdEXT",
    /* 1026 */ "glImportSemaphoreWin32HandleEXT",
    /* 1027 */ "glImportSemaphoreWin32NameEXT",
    /* 1028 */ "glImportSemaphoreZirconHandleANGLE",
    /* 1029 */ "glImportSyncEXT",
    /* 1030 */ "glIndexFormatNV",
    /* 1031 */ "glIndexFuncEXT",
    /* 1032 */ "glIndexMaterialEXT",
    /* 1033 */ "glIndexPointerEXT",
    /* 1034 */ "glIndexPointerListIBM",
    /* 1035 */ "glIndexxOES",
    /* 1036 */ "glIndexxvOES",
    /* 1037 */ "glInsertComponentEXT",
    /* 1038 */ "glInsertEventMarkerEXT",
    /* 1039 */ "glInstrumentsBufferSGIX",
    /* 1040 */ "glInterpolatePathsNV",
    /* 1041 */ "glInvalidateBufferData",
    /* 1042 */ "glInvalidateBufferSubData",
    /* 1043 */ "glInvalidateFramebuffer",
    /* 1044 */ "glInvalidateNamedFramebufferData",
    /* 1045 */ "glInvalidateNamedFramebufferSubData",
    /* 1046 */ "glInvalidateSubFramebuffer",
    /* 1047 */ "glInvalidateTexImage",
    /* 1048 */ "glInvalidateTexSubImage",
    /* 1049 */ "glInvalidateTextureANGLE",
    /* 1050 */ "glIsAsyncMarkerSGIX",
    /* 1051 */ "glIsBuffer",
    /* 1052 */ "glIsBufferARB",
    /* 1053 */ "glIsBufferResidentNV",
    /* 1054 */ "glIsCommandListNV",
    /* 1055 */ "glIsEnabled",
    /* 1056 */ "glIsEnabledIndexedEXT",
    /* 1057 */ "glIsEnabledi",
    /* 1058 */ "glIsFenceAPPLE",
    /* 1059 */ "glIsFenceNV",
    /* 1060 */ "glIsFramebuffer",
    /* 1061 */ "glIsFramebufferEXT",
    /* 1062 */ "glIsImageHandleResidentARB",
    /* 1063 */ "glIsImageHandleResidentNV",
    /* 1064 */ "glIsMemoryObjectEXT",
    /* 1065 */ "glIsNameAMD",
    /* 1066 */ "glIsNamedBufferResidentNV",
    /* 1067 */ "glIsNamedStringARB",
    /* 1068 */ "glIsObjectBufferATI",
    /* 1069 */ "glIsOcclusionQueryNV",
    /* 1070 */ "glIsPathNV",
    /* 1071 */ "glIsPointInFillPathNV",
    /* 1072 */ "glIsPointInStrokePathNV",
    /* 1073 */ "glIsProgram",
    /* 1074 */ "glIsProgramARB",
    /* 1075 */ "glIsProgramNV",
    /* 1076 */ "glIsProgramPipeline",
    /* 1077 */ "glIsQuery",
    /* 1078 */ "glIsQueryARB",
    /* 1079 */ "glIsRenderbuffer",
    /* 1080 */ "glIsRenderbufferEXT",
    /* 1081 */ "glIsSampler",
    /* 1082 */ "glIsSemaphoreEXT",
    /* 1083 */ "glIsShader",
    /* 1084 */ "glIsStateNV",
    /* 1085 */ "glIsSync",
    /* 1086 */ "glIsTexture",
    /* 1087 */ "glIsTextureEXT",
    /* 1088 */ "glIsTextureHandleResidentARB",
    /* 1089 */ "glIsTextureHandleResidentNV",
    /* 1090 */ "glIsTransformFeedback",
    /* 1091 */ "glIsTransformFeedbackNV",
    /* 1092 */ "glIsVariantEnabledEXT",
    /* 1093 */ "glIsVertexArray",
    /* 1094 */ "glIsVertexArrayAPPLE",
    /* 1095 */ "glIsVertexAttribEnabledAPPLE",
    /* 1096 */ "glLGPUCopyImageSubDataNVX",
    /* 1097 */ "glLGPUInterlockNVX",
    /* 1098 */ "glLGPUNamedBufferSubDataNVX",
    /* 1099 */ "glLabelObjectEXT",
    /* 1100 */ "glLightEnviSGIX",
    /* 1101 */ "glLightModelxOES",
    /* 1102 */ "glLightModelxvOES",
    /* 1103 */ "glLightxOES",
    /* 1104 */ "glLightxvOES",
    /* 1105 */ "glLineWidth",
    /* 1106 */ "glLineWidthxOES",
    /* 1107 */ "glLinkProgram",
    /* 1108 */ "glLinkProgramARB",
    /* 1109 */ "glListDrawCommandsStatesClientNV",
    /* 1110 */ "glListParameterfSGIX",
    /* 1111 */ "glListParameterfvSGIX",
    /* 1112 */ "glListParameteriSGIX",
    /* 1113 */ "glListParameterivSGIX",
    /* 1114 */ "glLoadIdentityDeformationMapSGIX",
    /* 1115 */ "glLoadMatrixxOES",
    /* 1116 */ "glLoadProgramNV",
    /* 1117 */ "glLoadTransposeMatrixdARB",
    /* 1118 */ "glLoadTransposeMatrixfARB",
    /* 1119 */ "glLoadTransposeMatrixxOES",
    /* 1120 */ "glLockArraysEXT",
    /* 1121 */ "glLogicOp",
    /* 1122 */ "glMakeBufferNonResidentNV",
    /* 1123 */ "glMakeBufferResidentNV",
    /* 1124 */ "glMakeImageHandleNonResidentARB",
    /* 1125 */ "glMakeImageHandleNonResidentNV",
    /* 1126 */ "glMakeImageHandleResidentARB",
    /* 1127 */ "glMakeImageHandleResidentNV",
    /* 1128 */ "glMakeNamedBufferNonResidentNV",
    /* 1129 */ "glMakeNamedBufferResidentNV",
    /* 1130 */ "glMakeTextureHandleNonResidentARB",
    /* 1131 */ "glMakeTextureHandleNonResidentNV",
    /* 1132 */ "glMakeTextureHandleResidentARB",
    /* 1133 */ "glMakeTextureHandleResidentNV",
    /* 1134 */ "glMap1xOES",
    /* 1135 */ "glMap2xOES",
    /* 1136 */ "glMapBuffer",
    /* 1137 */ "glMapBufferARB",
    /* 1138 */ "glMapBufferRange",
    /* 1139 */ "glMapControlPointsNV",
    /* 1140 */ "glMapGrid1xOES",
    /* 1141 */ "glMapGrid2xOES",
    /* 1142 */ "glMapNamedBuffer",
    /* 1143 */ "glMapNamedBufferEXT",
    /* 1144 */ "glMapNamedBufferRange",
    /* 1145 */ "glMapNamedBufferRangeEXT",
    /* 1146 */ "glMapObjectBufferATI",
    /* 1147 */ "glMapParameterfvNV",
    /* 1148 */ "glMapParameterivNV",
    /* 1149 */ "glMapTexture2DINTEL",
    /* 1150 */ "glMapVertexAttrib1dAPPLE",
    /* 1151 */ "glMapVertexAttrib1fAPPLE",
    /* 1152 */ "glMapVertexAttrib2dAPPLE",
    /* 1153 */ "glMapVertexAttrib2fAPPLE",
    /* 1154 */ "glMaterialxOES",
    /* 1155 */ "glMaterialxvOES",
    /* 1156 */ "glMatrixFrustumEXT",
    /* 1157 */ "glMatrixIndexPointerARB",
    /* 1158 */ "glMatrixIndexubvARB",
    /* 1159 */ "glMatrixIndexuivARB",
    /* 1160 */ "glMatrixIndexusvARB",
    /* 1161 */ "glMatrixLoad3x2fNV",
    /* 1162 */ "glMatrixLoad3x3fNV",
    /* 1163 */ "glMatrixLoadIdentityEXT",
    /* 1164 */ "glMatrixLoadTranspose3x3fNV",
    /* 1165 */ "glMatrixLoadTransposedEXT",
    /* 1166 */ "glMatrixLoadTransposefEXT",
    /* 1167 */ "glMatrixLoaddEXT",
    /* 1168 */ "glMatrixLoadfEXT",
    /* 1169 */ "glMatrixMult3x2fNV",
    /* 1170 */ "glMatrixMult3x3fNV",
    /* 1171 */ "glMatrixMultTranspose3x3fNV",
    /* 1172 */ "glMatrixMultTransposedEXT",
    /* 1173 */ "glMatrixMultTransposefEXT",
    /* 1174 */ "glMatrixMultdEXT",
    /* 1175 */ "glMatrixMultfEXT",
    /* 1176 */ "glMatrixOrthoEXT",
    /* 1177 */ "glMatrixPopEXT",
    /* 1178 */ "glMatrixPushEXT",
    /* 1179 */ "glMatrixRotatedEXT",
    /* 1180 */ "glMatrixRotatefEXT",
    /* 1181 */ "glMatrixScaledEXT",
    /* 1182 */ "glMatrixScalefEXT",
    /* 1183 */ "glMatrixTranslatedEXT",
    /* 1184 */ "glMatrixTranslatefEXT",
    /* 1185 */ "glMaxShaderCompilerThreadsARB",
    /* 1186 */ "glMaxShaderCompilerThreadsKHR",
    /* 1187 */ "glMemoryBarrier",
    /* 1188 */ "glMemoryBarrierByRegion",
    /* 1189 */ "glMemoryBarrierEXT",
    /* 1190 */ "glMemoryObjectParameterivEXT",
    /* 1191 */ "glMinSampleShading",
    /* 1192 */ "glMinSampleShadingARB",
    /* 1193 */ "glMinmaxEXT",
    /* 1194 */ "glMultMatrixxOES",
    /* 1195 */ "glMultTransposeMatrixdARB",
    /* 1196 */ "glMultTransposeMatrixfARB",
    /* 1197 */ "glMultTransposeMatrixxOES",
    /* 1198 */ "glMultiDrawArrays",
    /* 1199 */ "glMultiDrawArraysEXT",
    /* 1200 */ "glMultiDrawArraysIndirect",
    /* 1201 */ "glMultiDrawArraysIndirectAMD",
    /* 1202 */ "glMultiDrawArraysIndirectBindlessCountNV",
    /* 1203 */ "glMultiDrawArraysIndirectBindlessNV",
    /* 1204 */ "glMultiDrawArraysIndirectCount",
    /* 1205 */ "glMultiDrawArraysIndirectCountARB",
    /* 1206 */ "glMultiDrawElementArrayAPPLE",
    /* 1207 */ "glMultiDrawElements",
    /* 1208 */ "glMultiDrawElementsBaseVertex",
    /* 1209 */ "glMultiDrawElementsEXT",
    /* 1210 */ "glMultiDrawElementsIndirect",
    /* 1211 */ "glMultiDrawElementsIndirectAMD",
    /* 1212 */ "glMultiDrawElementsIndirectBindlessCountNV",
    /* 1213 */ "glMultiDrawElementsIndirectBindlessNV",
    /* 1214 */ "glMultiDrawElementsIndirectCount",
    /* 1215 */ "glMultiDrawElementsIndirectCountARB",
    /* 1216 */ "glMultiDrawMeshTasksIndirectCountNV",
    /* 1217 */ "glMultiDrawMeshTasksIndirectNV",
    /* 1218 */ "glMultiDrawRangeElementArrayAPPLE",
    /* 1219 */ "glMultiModeDrawArraysIBM",
    /* 1220 */ "glMultiModeDrawElementsIBM",
    /* 1221 */ "glMultiTexBufferEXT",
    /* 1222 */ "glMultiTexCoord1bOES",
    /* 1223 */ "glMultiTexCoord1bvOES",
    /* 1224 */ "glMultiTexCoord1dARB",
    /* 1225 */ "glMultiTexCoord1dvARB",
    /* 1226 */ "glMultiTexCoord1fARB",
    /* 1227 */ "glMultiTexCoord1fvARB",
    /* 1228 */ "glMultiTexCoord1hNV",
    /* 1229 */ "glMultiTexCoord1hvNV",
    /* 1230 */ "glMultiTexCoord1iARB",
    /* 1231 */ "glMultiTexCoord1ivARB",
    /* 1232 */ "glMultiTexCoord1sARB",
    /* 1233 */ "glMultiTexCoord1svARB",
    /* 1234 */ "glMultiTexCoord1xOES",
    /* 1235 */ "glMultiTexCoord1xvOES",
    /* 1236 */ "glMultiTexCoord2bOES",
    /* 1237 */ "glMultiTexCoord2bvOES",
    /* 1238 */ "glMultiTexCoord2dARB",
    /* 1239 */ "glMultiTexCoord2dvARB",
    /* 1240 */ "glMultiTexCoord2fARB",
    /* 1241 */ "glMultiTexCoord2fvARB",
    /* 1242 */ "glMultiTexCoord2hNV",
    /* 1243 */ "glMultiTexCoord2hvNV",
    /* 1244 */ "glMultiTexCoord2iARB",
    /* 1245 */ "glMultiTexCoord2ivARB",
    /* 1246 */ "glMultiTexCoord2sARB",
    /* 1247 */ "glMultiTexCoord2svARB",
    /* 1248 */ "glMultiTexCoord2xOES",
    /* 1249 */ "glMultiTexCoord2xvOES",
    /* 1250 */ "glMultiTexCoord3bOES",
    /* 1251 */ "glMultiTexCoord3bvOES",
    /* 1252 */ "glMultiTexCoord3dARB",
    /* 1253 */ "glMultiTexCoord3dvARB",
    /* 1254 */ "glMultiTexCoord3fARB",
    /* 1255 */ "glMultiTexCoord3fvARB",
    /* 1256 */ "glMultiTexCoord3hNV",
    /* 1257 */ "glMultiTexCoord3hvNV",
    /* 1258 */ "glMultiTexCoord3iARB",
    /* 1259 */ "glMultiTexCoord3ivARB",
    /* 1260 */ "glMultiTexCoord3sARB",
    /* 1261 */ "glMultiTexCoord3svARB",
    /* 1262 */ "glMultiTexCoord3xOES",
    /* 1263 */ "glMultiTexCoord3xvOES",
    /* 1264 */ "glMultiTexCoord4bOES",
    /* 1265 */ "glMultiTexCoord4bvOES",
    /* 1266 */ "glMultiTexCoord4dARB",
    /* 1267 */ "glMultiTexCoord4dvARB",
    /* 1268 */ "glMultiTexCoord4fARB",
    /* 1269 */ "glMultiTexCoord4fvARB",
    /* 1270 */ "glMultiTexCoord4hNV",
    /* 1271 */ "glMultiTexCoord4hvNV",
    /* 1272 */ "glMultiTexCoord4iARB",
    /* 1273 */ "glMultiTexCoord4ivARB",
    /* 1274 */ "glMultiTexCoord4sARB",
    /* 1275 */ "glMultiTexCoord4svARB",
    /* 1276 */ "glMultiTexCoord4xOES",
    /* 1277 */ "glMultiTexCoord4xvOES",
    /* 1278 */ "glMultiTexCoordPointerEXT",
    /* 1279 */ "glMultiTexEnvfEXT",
    /* 1280 */ "glMultiTexEnvfvEXT",
    /* 1281 */ "glMultiTexEnviEXT",
    /* 1282 */ "glMultiTexEnvivEXT",
    /* 1283 */ "glMultiTexGendEXT",
    /* 1284 */ "glMultiTexGendvEXT",
    /* 1285 */ "glMultiTexGenfEXT",
    /* 1286 */ "glMultiTexGenfvEXT",
    /* 1287 */ "glMultiTexGeniEXT",
    /* 1288 */ "glMultiTexGenivEXT",
    /* 1289 */ "glMultiTexImage1DEXT",
    /* 1290 */ "glMultiTexImage2DEXT",
    /* 1291 */ "glMultiTexImage3DEXT",
    /* 1292 */ "glMultiTexParameterIivEXT",
    /* 1293 */ "glMultiTexParameterIuivEXT",
    /* 1294 */ "glMultiTexParameterfEXT",
    /* 1295 */ "glMultiTexParameterfvEXT",
    /* 1296 */ "glMultiTexParameteriEXT",
    /* 1297 */ "glMultiTexParameterivEXT",
    /* 1298 */ "glMultiTexRenderbufferEXT",
    /* 1299 */ "glMultiTexSubImage1DEXT",
    /* 1300 */ "glMultiTexSubImage2DEXT",
    /* 1301 */ "glMultiTexSubImage3DEXT",
    /* 1302 */ "glMulticastBarrierNV",
    /* 1303 */ "glMulticastBlitFramebufferNV",
    /* 1304 */ "glMulticastBufferSubDataNV",
    /* 1305 */ "glMulticastCopyBufferSubDataNV",
    /* 1306 */ "glMulticastCopyImageSubDataNV",
    /* 1307 */ "glMulticastFramebufferSampleLocationsfvNV",
    /* 1308 */ "glMulticastGetQueryObjecti64vNV",
    /* 1309 */ "glMulticastGetQueryObjectivNV",
    /* 1310 */ "glMulticastGetQueryObjectui64vNV",
    /* 1311 */ "glMulticastGetQueryObjectuivNV",
    /* 1312 */ "glMulticastScissorArrayvNVX",
    /* 1313 */ "glMulticastViewportArrayvNVX",
    /* 1314 */ "glMulticastViewportPositionWScaleNVX",
    /* 1315 */ "glMulticastWaitSyncNV",
    /* 1316 */ "glNamedBufferAttachMemoryNV",
    /* 1317 */ "glNamedBufferData",
    /* 1318 */ "glNamedBufferDataEXT",
    /* 1319 */ "glNamedBufferPageCommitmentARB",
    /* 1320 */ "glNamedBufferPageCommitmentEXT",
    /* 1321 */ "glNamedBufferPageCommitmentMemNV",
    /* 1322 */ "glNamedBufferStorage",
    /* 1323 */ "glNamedBufferStorageEXT",
    /* 1324 */ "glNamedBufferStorageExternalEXT",
    /* 1325 */ "glNamedBufferStorageMemEXT",
    /* 1326 */ "glNamedBufferSubData",
    /* 1327 */ "glNamedBufferSubDataEXT",
    /* 1328 */ "glNamedCopyBufferSubDataEXT",
    /* 1329 */ "glNamedFramebufferDrawBuffer",
    /* 1330 */ "glNamedFramebufferDrawBuffers",
    /* 1331 */ "glNamedFramebufferParameteri",
    /* 1332 */ "glNamedFramebufferParameteriEXT",
    /* 1333 */ "glNamedFramebufferReadBuffer",
    /* 1334 */ "glNamedFramebufferRenderbuffer",
    /* 1335 */ "glNamedFramebufferRenderbufferEXT",
    /* 1336 */ "glNamedFramebufferSampleLocationsfvARB",
    /* 1337 */ "glNamedFramebufferSampleLocationsfvNV",
    /* 1338 */ "glNamedFramebufferSamplePositionsfvAMD",
    /* 1339 */ "glNamedFramebufferTexture",
    /* 1340 */ "glNamedFramebufferTexture1DEXT",
    /* 1341 */ "glNamedFramebufferTexture2DEXT",
    /* 1342 */ "glNamedFramebufferTexture3DEXT",
    /* 1343 */ "glNamedFramebufferTextureEXT",
    /* 1344 */ "glNamedFramebufferTextureFaceEXT",
    /* 1345 */ "glNamedFramebufferTextureLayer",
    /* 1346 */ "glNamedFramebufferTextureLayerEXT",
    /* 1347 */ "glNamedFramebufferTextureMultiviewOVR",
    /* 1348 */ "glNamedProgramLocalParameter4dEXT",
    /* 1349 */ "glNamedProgramLocalParameter4dvEXT",
    /* 1350 */ "glNamedProgramLocalParameter4fEXT",
    /* 1351 */ "glNamedProgramLocalParameter4fvEXT",
    /* 1352 */ "glNamedProgramLocalParameterI4iEXT",
    /* 1353 */ "glNamedProgramLocalParameterI4ivEXT",
    /* 1354 */ "glNamedProgramLocalParameterI4uiEXT",
    /* 1355 */ "glNamedProgramLocalParameterI4uivEXT",
    /* 1356 */ "glNamedProgramLocalParameters4fvEXT",
    /* 1357 */ "glNamedProgramLocalParametersI4ivEXT",
    /* 1358 */ "glNamedProgramLocalParametersI4uivEXT",
    /* 1359 */ "glNamedProgramStringEXT",
    /* 1360 */ "glNamedRenderbufferStorage",
    /* 1361 */ "glNamedRenderbufferStorageEXT",
    /* 1362 */ "glNamedRenderbufferStorageMultisample",
    /* 1363 */ "glNamedRenderbufferStorageMultisampleAdvancedAMD",
    /* 1364 */ "glNamedRenderbufferStorageMultisampleCoverageEXT",
    /* 1365 */ "glNamedRenderbufferStorageMultisampleEXT",
    /* 1366 */ "glNamedStringARB",
    /* 1367 */ "glNewObjectBufferATI",
    /* 1368 */ "glNormal3fVertex3fSUN",
    /* 1369 */ "glNormal3fVertex3fvSUN",
    /* 1370 */ "glNormal3hNV",
    /* 1371 */ "glNormal3hvNV",
    /* 1372 */ "glNormal3xOES",
    /* 1373 */ "glNormal3xvOES",
    /* 1374 */ "glNormalFormatNV",
    /* 1375 */ "glNormalPointerEXT",
    /* 1376 */ "glNormalPointerListIBM",
    /* 1377 */ "glNormalPointervINTEL",
    /* 1378 */ "glNormalStream3bATI",
    /* 1379 */ "glNormalStream3bvATI",
    /* 1380 */ "glNormalStream3dATI",
    /* 1381 */ "glNormalStream3dvATI",
    /* 1382 */ "glNormalStream3fATI",
    /* 1383 */ "glNormalStream3fvATI",
    /* 1384 */ "glNormalStream3iATI",
    /* 1385 */ "glNormalStream3ivATI",
    /* 1386 */ "glNormalStream3sATI",
    /* 1387 */ "glNormalStream3svATI",
    /* 1388 */ "glObjectLabel",
    /* 1389 */ "glObjectPtrLabel",
    /* 1390 */ "glObjectPurgeableAPPLE",
    /* 1391 */ "glObjectUnpurgeableAPPLE",
    /* 1392 */ "glOrthofOES",
    /* 1393 */ "glOrthoxOES",
    /* 1394 */ "glPNTrianglesfATI",
    /* 1395 */ "glPNTrianglesiATI",
    /* 1396 */ "glPassTexCoordATI",
    /* 1397 */ "glPassThroughxOES",
    /* 1398 */ "glPatchParameterfv",
    /* 1399 */ "glPatchParameteri",
    /* 1400 */ "glPathCommandsNV",
    /* 1401 */ "glPathCoordsNV",
    /* 1402 */ "glPathCoverDepthFuncNV",
    /* 1403 */ "glPathDashArrayNV",
    /* 1404 */ "glPathGlyphIndexArrayNV",
    /* 1405 */ "glPathGlyphIndexRangeNV",
    /* 1406 */ "glPathGlyphRangeNV",
    /* 1407 */ "glPathGlyphsNV",
    /* 1408 */ "glPathMemoryGlyphIndexArrayNV",
    /* 1409 */ "glPathParameterfNV",
    /* 1410 */ "glPathParameterfvNV",
    /* 1411 */ "glPathParameteriNV",
    /* 1412 */ "glPathParameterivNV",
    /* 1413 */ "glPathStencilDepthOffsetNV",
    /* 1414 */ "glPathStencilFuncNV",
    /* 1415 */ "glPathStringNV",
    /* 1416 */ "glPathSubCommandsNV",
    /* 1417 */ "glPathSubCoordsNV",
    /* 1418 */ "glPauseTransformFeedback",
    /* 1419 */ "glPauseTransformFeedbackNV",
    /* 1420 */ "glPixelDataRangeNV",
    /* 1421 */ "glPixelMapx",
    /* 1422 */ "glPixelStoref",
    /* 1423 */ "glPixelStorei",
    /* 1424 */ "glPixelStorex",
    /* 1425 */ "glPixelTexGenParameterfSGIS",
    /* 1426 */ "glPixelTexGenParameterfvSGIS",
    /* 1427 */ "glPixelTexGenParameteriSGIS",
    /* 1428 */ "glPixelTexGenParameterivSGIS",
    /* 1429 */ "glPixelTexGenSGIX",
    /* 1430 */ "glPixelTransferxOES",
    /* 1431 */ "glPixelTransformParameterfEXT",
    /* 1432 */ "glPixelTransformParameterfvEXT",
    /* 1433 */ "glPixelTransformParameteriEXT",
    /* 1434 */ "glPixelTransformParameterivEXT",
    /* 1435 */ "glPixelZoomxOES",
    /* 1436 */ "glPointAlongPathNV",
    /* 1437 */ "glPointParameterf",
    /* 1438 */ "glPointParameterfARB",
    /* 1439 */ "glPointParameterfEXT",
    /* 1440 */ "glPointParameterfSGIS",
    /* 1441 */ "glPointParameterfv",
    /* 1442 */ "glPointParameterfvARB",
    /* 1443 */ "glPointParameterfvEXT",
    /* 1444 */ "glPointParameterfvSGIS",
    /* 1445 */ "glPointParameteri",
    /* 1446 */ "glPointParameteriNV",
    /* 1447 */ "glPointParameteriv",
    /* 1448 */ "glPointParameterivNV",
    /* 1449 */ "glPointParameterxvOES",
    /* 1450 */ "glPointSize",
    /* 1451 */ "glPointSizexOES",
    /* 1452 */ "glPollAsyncSGIX",
    /* 1453 */ "glPollInstrumentsSGIX",
    /* 1454 */ "glPolygonMode",
    /* 1455 */ "glPolygonOffset",
    /* 1456 */ "glPolygonOffsetClamp",
    /* 1457 */ "glPolygonOffsetClampEXT",
    /* 1458 */ "glPolygonOffsetEXT",
    /* 1459 */ "glPolygonOffsetxOES",
    /* 1460 */ "glPopDebugGroup",
    /* 1461 */ "glPopGroupMarkerEXT",
    /* 1462 */ "glPresentFrameDualFillNV",
    /* 1463 */ "glPresentFrameKeyedNV",
    /* 1464 */ "glPrimitiveBoundingBoxARB",
    /* 1465 */ "glPrimitiveRestartIndex",
    /* 1466 */ "glPrimitiveRestartIndexNV",
    /* 1467 */ "glPrimitiveRestartNV",
    /* 1468 */ "glPrioritizeTexturesEXT",
    /* 1469 */ "glPrioritizeTexturesxOES",
    /* 1470 */ "glProgramBinary",
    /* 1471 */ "glProgramBufferParametersIivNV",
    /* 1472 */ "glProgramBufferParametersIuivNV",
    /* 1473 */ "glProgramBufferParametersfvNV",
    /* 1474 */ "glProgramEnvParameter4dARB",
    /* 1475 */ "glProgramEnvParameter4dvARB",
    /* 1476 */ "glProgramEnvParameter4fARB",
    /* 1477 */ "glProgramEnvParameter4fvARB",
    /* 1478 */ "glProgramEnvParameterI4iNV",
    /* 1479 */ "glProgramEnvParameterI4ivNV",
    /* 1480 */ "glProgramEnvParameterI4uiNV",
    /* 1481 */ "glProgramEnvParameterI4uivNV",
    /* 1482 */ "glProgramEnvParameters4fvEXT",
    /* 1483 */ "glProgramEnvParametersI4ivNV",
    /* 1484 */ "glProgramEnvParametersI4uivNV",
    /* 1485 */ "glProgramLocalParameter4dARB",
    /* 1486 */ "glProgramLocalParameter4dvARB",
    /* 1487 */ "glProgramLocalParameter4fARB",
    /* 1488 */ "glProgramLocalParameter4fvARB",
    /* 1489 */ "glProgramLocalParameterI4iNV",
    /* 1490 */ "glProgramLocalParameterI4ivNV",
    /* 1491 */ "glProgramLocalParameterI4uiNV",
    /* 1492 */ "glProgramLocalParameterI4uivNV",
    /* 1493 */ "glProgramLocalParameters4fvEXT",
    /* 1494 */ "glProgramLocalParametersI4ivNV",
    /* 1495 */ "glProgramLocalParametersI4uivNV",
    /* 1496 */ "glProgramNamedParameter4dNV",
    /* 1497 */ "glProgramNamedParameter4dvNV",
    /* 1498 */ "glProgramNamedParameter4fNV",
    /* 1499 */ "glProgramNamedParameter4fvNV",
    /* 1500 */ "glProgramParameter4dNV",
    /* 1501 */ "glProgramParameter4dvNV",
    /* 1502 */ "glProgramParameter4fNV",
    /* 1503 */ "glProgramParameter4fvNV",
    /* 1504 */ "glProgramParameteri",
    /* 1505 */ "glProgramParameteriARB",
    /* 1506 */ "glProgramParameteriEXT",
    /* 1507 */ "glProgramParameters4dvNV",
    /* 1508 */ "glProgramParameters4fvNV",
    /* 1509 */ "glProgramPathFragmentInputGenNV",
    /* 1510 */ "glProgramStringARB",
    /* 1511 */ "glProgramSubroutineParametersuivNV",
    /* 1512 */ "glProgramUniform1d",
    /* 1513 */ "glProgramUniform1dEXT",
    /* 1514 */ "glProgramUniform1dv",
    /* 1515 */ "glProgramUniform1dvEXT",
    /* 1516 */ "glProgramUniform1f",
    /* 1517 */ "glProgramUniform1fEXT",
    /* 1518 */ "glProgramUniform1fv",
    /* 1519 */ "glProgramUniform1fvEXT",
    /* 1520 */ "glProgramUniform1i",
    /* 1521 */ "glProgramUniform1i64ARB",
    /* 1522 */ "glProgramUniform1i64NV",
    /* 1523 */ "glProgramUniform1i64vARB",
    /* 1524 */ "glProgramUniform1i64vNV",
    /* 1525 */ "glProgramUniform1iEXT",
    /* 1526 */ "glProgramUniform1iv",
    /* 1527 */ "glProgramUniform1ivEXT",
    /* 1528 */ "glProgramUniform1ui",
    /* 1529 */ "glProgramUniform1ui64ARB",
    /* 1530 */ "glProgramUniform1ui64NV",
    /* 1531 */ "glProgramUniform1ui64vARB",
    /* 1532 */ "glProgramUniform1ui64vNV",
    /* 1533 */ "glProgramUniform1uiEXT",
    /* 1534 */ "glProgramUniform1uiv",
    /* 1535 */ "glProgramUniform1uivEXT",
    /* 1536 */ "glProgramUniform2d",
    /* 1537 */ "glProgramUniform2dEXT",
    /* 1538 */ "glProgramUniform2dv",
    /* 1539 */ "glProgramUniform2dvEXT",
    /* 1540 */ "glProgramUniform2f",
    /* 1541 */ "glProgramUniform2fEXT",
    /* 1542 */ "glProgramUniform2fv",
    /* 1543 */ "glProgramUniform2fvEXT",
    /* 1544 */ "glProgramUniform2i",
    /* 1545 */ "glProgramUniform2i64ARB",
    /* 1546 */ "glProgramUniform2i64NV",
    /* 1547 */ "glProgramUniform2i64vARB",
    /* 1548 */ "glProgramUniform2i64vNV",
    /* 1549 */ "glProgramUniform2iEXT",
    /* 1550 */ "glProgramUniform2iv",
    /* 1551 */ "glProgramUniform2ivEXT",
    /* 1552 */ "glProgramUniform2ui",
    /* 1553 */ "glProgramUniform2ui64ARB",
    /* 1554 */ "glProgramUniform2ui64NV",
    /* 1555 */ "glProgramUniform2ui64vARB",
    /* 1556 */ "glProgramUniform2ui64vNV",
    /* 1557 */ "glProgramUniform2uiEXT",
    /* 1558 */ "glProgramUniform2uiv",
    /* 1559 */ "glProgramUniform2uivEXT",
    /* 1560 */ "glProgramUniform3d",
    /* 1561 */ "glProgramUniform3dEXT",
    /* 1562 */ "glProgramUniform3dv",
    /* 1563 */ "glProgramUniform3dvEXT",
    /* 1564 */ "glProgramUniform3f",
    /* 1565 */ "glProgramUniform3fEXT",
    /* 1566 */ "glProgramUniform3fv",
    /* 1567 */ "glProgramUniform3fvEXT",
    /* 1568 */ "glProgramUniform3i",
    /* 1569 */ "glProgramUniform3i64ARB",
    /* 1570 */ "glProgramUniform3i64NV",
    /* 1571 */ "glProgramUniform3i64vARB",
    /* 1572 */ "glProgramUniform3i64vNV",
    /* 1573 */ "glProgramUniform3iEXT",
    /* 1574 */ "glProgramUniform3iv",
    /* 1575 */ "glProgramUniform3ivEXT",
    /* 1576 */ "glProgramUniform3ui",
    /* 1577 */ "glProgramUniform3ui64ARB",
    /* 1578 */ "glProgramUniform3ui64NV",
    /* 1579 */ "glProgramUniform3ui64vARB",
    /* 1580 */ "glProgramUniform3ui64vNV",
    /* 1581 */ "glProgramUniform3uiEXT",
    /* 1582 */ "glProgramUniform3uiv",
    /* 1583 */ "glProgramUniform3uivEXT",
    /* 1584 */ "glProgramUniform4d",
    /* 1585 */ "glProgramUniform4dEXT",
    /* 1586 */ "glProgramUniform4dv",
    /* 1587 */ "glProgramUniform4dvEXT",
    /* 1588 */ "glProgramUniform4f",
    /* 1589 */ "glProgramUniform4fEXT",
    /* 1590 */ "glProgramUniform4fv",
    /* 1591 */ "glProgramUniform4fvEXT",
    /* 1592 */ "glProgramUniform4i",
    /* 1593 */ "glProgramUniform4i64ARB",
    /* 1594 */ "glProgramUniform4i64NV",
    /* 1595 */ "glProgramUniform4i64vARB",
    /* 1596 */ "glProgramUniform4i64vNV",
    /* 1597 */ "glProgramUniform4iEXT",
    /* 1598 */ "glProgramUniform4iv",
    /* 1599 */ "glProgramUniform4ivEXT",
    /* 1600 */ "glProgramUniform4ui",
    /* 1601 */ "glProgramUniform4ui64ARB",
    /* 1602 */ "glProgramUniform4ui64NV",
    /* 1603 */ "glProgramUniform4ui64vARB",
    /* 1604 */ "glProgramUniform4ui64vNV",
    /* 1605 */ "glProgramUniform4uiEXT",
    /* 1606 */ "glProgramUniform4uiv",
    /* 1607 */ "glProgramUniform4uivEXT",
    /* 1608 */ "glProgramUniformHandleui64ARB",
    /* 1609 */ "glProgramUniformHandleui64NV",
    /* 1610 */ "glProgramUniformHandleui64vARB",
    /* 1611 */ "glProgramUniformHandleui64vNV",
    /* 1612 */ "glProgramUniformMatrix2dv",
    /* 1613 */ "glProgramUniformMatrix2dvEXT",
    /* 1614 */ "glProgramUniformMatrix2fv",
    /* 1615 */ "glProgramUniformMatrix2fvEXT",
    /* 1616 */ "glProgramUniformMatrix2x3dv",
    /* 1617 */ "glProgramUniformMatrix2x3dvEXT",
    /* 1618 */ "glProgramUniformMatrix2x3fv",
    /* 1619 */ "glProgramUniformMatrix2x3fvEXT",
    /* 1620 */ "glProgramUniformMatrix2x4dv",
    /* 1621 */ "glProgramUniformMatrix2x4dvEXT",
    /* 1622 */ "glProgramUniformMatrix2x4fv",
    /* 1623 */ "glProgramUniformMatrix2x4fvEXT",
    /* 1624 */ "glProgramUniformMatrix3dv",
    /* 1625 */ "glProgramUniformMatrix3dvEXT",
    /* 1626 */ "glProgramUniformMatrix3fv",
    /* 1627 */ "glProgramUniformMatrix3fvEXT",
    /* 1628 */ "glProgramUniformMatrix3x2dv",
    /* 1629 */ "glProgramUniformMatrix3x2dvEXT",
    /* 1630 */ "glProgramUniformMatrix3x2fv",
    /* 1631 */ "glProgramUniformMatrix3x2fvEXT",
    /* 1632 */ "glProgramUniformMatrix3x4dv",
    /* 1633 */ "glProgramUniformMatrix3x4dvEXT",
    /* 1634 */ "glProgramUniformMatrix3x4fv",
    /* 1635 */ "glProgramUniformMatrix3x4fvEXT",
    /* 1636 */ "glProgramUniformMatrix4dv",
    /* 1637 */ "glProgramUniformMatrix4dvEXT",
    /* 1638 */ "glProgramUniformMatrix4fv",
    /* 1639 */ "glProgramUniformMatrix4fvEXT",
    /* 1640 */ "glProgramUniformMatrix4x2dv",
    /* 1641 */ "glProgramUniformMatrix4x2dvEXT",
    /* 1642 */ "glProgramUniformMatrix4x2fv",
    /* 1643 */ "glProgramUniformMatrix4x2fvEXT",
    /* 1644 */ "glProgramUniformMatrix4x3dv",
    /* 1645 */ "glProgramUniformMatrix4x3dvEXT",
    /* 1646 */ "glProgramUniformMatrix4x3fv",
    /* 1647 */ "glProgramUniformMatrix4x3fvEXT",
    /* 1648 */ "glProgramUniformui64NV",
    /* 1649 */ "glProgramUniformui64vNV",
    /* 1650 */ "glProgramVertexLimitNV",
    /* 1651 */ "glProvokingVertex",
    /* 1652 */ "glProvokingVertexEXT",
    /* 1653 */ "glPushClientAttribDefaultEXT",
    /* 1654 */ "glPushDebugGroup",
    /* 1655 */ "glPushGroupMarkerEXT",
    /* 1656 */ "glQueryCounter",
    /* 1657 */ "glQueryMatrixxOES",
    /* 1658 */ "glQueryObjectParameteruiAMD",
    /* 1659 */ "glQueryResourceNV",
    /* 1660 */ "glQueryResourceTagNV",
    /* 1661 */ "glRasterPos2xOES",
    /* 1662 */ "glRasterPos2xvOES",
    /* 1663 */ "glRasterPos3xOES",
    /* 1664 */ "glRasterPos3xvOES",
    /* 1665 */ "glRasterPos4xOES",
    /* 1666 */ "glRasterPos4xvOES",
    /* 1667 */ "glRasterSamplesEXT",
    /* 1668 */ "glReadBuffer",
    /* 1669 */ "glReadInstrumentsSGIX",
    /* 1670 */ "glReadPixels",
    /* 1671 */ "glReadnPixels",
    /* 1672 */ "glReadnPixelsARB",
    /* 1673 */ "glRectxOES",
    /* 1674 */ "glRectxvOES",
    /* 1675 */ "glReferencePlaneSGIX",
    /* 1676 */ "glReleaseKeyedMutexWin32EXT",
    /* 1677 */ "glReleaseShaderCompiler",
    /* 1678 */ "glRenderGpuMaskNV",
    /* 1679 */ "glRenderbufferStorage",
    /* 1680 */ "glRenderbufferStorageEXT",
    /* 1681 */ "glRenderbufferStorageMultisample",
    /* 1682 */ "glRenderbufferStorageMultisampleAdvancedAMD",
    /* 1683 */ "glRenderbufferStorageMultisampleCoverageNV",
    /* 1684 */ "glRenderbufferStorageMultisampleEXT",
    /* 1685 */ "glReplacementCodePointerSUN",
    /* 1686 */ "glReplacementCodeubSUN",
    /* 1687 */ "glReplacementCodeubvSUN",
    /* 1688 */ "glReplacementCodeuiColor3fVertex3fSUN",
    /* 1689 */ "glReplacementCodeuiColor3fVertex3fvSUN",
    /* 1690 */ "glReplacementCodeuiColor4fNormal3fVertex3fSUN",
    /* 1691 */ "glReplacementCodeuiColor4fNormal3fVertex3fvSUN",
    /* 1692 */ "glReplacementCodeuiColor4ubVertex3fSUN",
    /* 1693 */ "glReplacementCodeuiColor4ubVertex3fvSUN",
    /* 1694 */ "glReplacementCodeuiNormal3fVertex3fSUN",
    /* 1695 */ "glReplacementCodeuiNormal3fVertex3fvSUN",
    /* 1696 */ "glReplacementCodeuiSUN",
    /* 1697 */ "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN",
    /* 1698 */ "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN",
    /* 1699 */ "glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN",
    /* 1700 */ "glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN",
    /* 1701 */ "glReplacementCodeuiTexCoord2fVertex3fSUN",
    /* 1702 */ "glReplacementCodeuiTexCoord2fVertex3fvSUN",
    /* 1703 */ "glReplacementCodeuiVertex3fSUN",
    /* 1704 */ "glReplacementCodeuiVertex3fvSUN",
    /* 1705 */ "glReplacementCodeuivSUN",
    /* 1706 */ "glReplacementCodeusSUN",
    /* 1707 */ "glReplacementCodeusvSUN",
    /* 1708 */ "glRequestResidentProgramsNV",
    /* 1709 */ "glResetHistogramEXT",
    /* 1710 */ "glResetMemoryObjectParameterNV",
    /* 1711 */ "glResetMinmaxEXT",
    /* 1712 */ "glResizeBuffersMESA",
    /* 1713 */ "glResolveDepthValuesNV",
    /* 1714 */ "glResumeTransformFeedback",
    /* 1715 */ "glResumeTransformFeedbackNV",
    /* 1716 */ "glRotatexOES",
    /* 1717 */ "glSampleCoverage",
    /* 1718 */ "glSampleCoverageARB",
    /* 1719 */ "glSampleMapATI",
    /* 1720 */ "glSampleMaskEXT",
    /* 1721 */ "glSampleMaskIndexedNV",
    /* 1722 */ "glSampleMaskSGIS",
    /* 1723 */ "glSampleMaski",
    /* 1724 */ "glSamplePatternEXT",
    /* 1725 */ "glSamplePatternSGIS",
    /* 1726 */ "glSamplerParameterIiv",
    /* 1727 */ "glSamplerParameterIuiv",
    /* 1728 */ "glSamplerParameterf",
    /* 1729 */ "glSamplerParameterfv",
    /* 1730 */ "glSamplerParameteri",
    /* 1731 */ "glSamplerParameteriv",
    /* 1732 */ "glScalexOES",
    /* 1733 */ "glScissor",
    /* 1734 */ "glScissorArrayv",
    /* 1735 */ "glScissorExclusiveArrayvNV",
    /* 1736 */ "glScissorExclusiveNV",
    /* 1737 */ "glScissorIndexed",
    /* 1738 */ "glScissorIndexedv",
    /* 1739 */ "glSecondaryColor3bEXT",
    /* 1740 */ "glSecondaryColor3bvEXT",
    /* 1741 */ "glSecondaryColor3dEXT",
    /* 1742 */ "glSecondaryColor3dvEXT",
    /* 1743 */ "glSecondaryColor3fEXT",
    /* 1744 */ "glSecondaryColor3fvEXT",
    /* 1745 */ "glSecondaryColor3hNV",
    /* 1746 */ "glSecondaryColor3hvNV",
    /* 1747 */ "glSecondaryColor3iEXT",
    /* 1748 */ "glSecondaryColor3ivEXT",
    /* 1749 */ "glSecondaryColor3sEXT",
    /* 1750 */ "glSecondaryColor3svEXT",
    /* 1751 */ "glSecondaryColor3ubEXT",
    /* 1752 */ "glSecondaryColor3ubvEXT",
    /* 1753 */ "glSecondaryColor3uiEXT",
    /* 1754 */ "glSecondaryColor3uivEXT",
    /* 1755 */ "glSecondaryColor3usEXT",
    /* 1756 */ "glSecondaryColor3usvEXT",
    /* 1757 */ "glSecondaryColorFormatNV",
    /* 1758 */ "glSecondaryColorPointerEXT",
    /* 1759 */ "glSecondaryColorPointerListIBM",
    /* 1760 */ "glSelectPerfMonitorCountersAMD",
    /* 1761 */ "glSemaphoreParameterivNV",
    /* 1762 */ "glSemaphoreParameterui64vEXT",
    /* 1763 */ "glSeparableFilter2DEXT",
    /* 1764 */ "glSetFenceAPPLE",
    /* 1765 */ "glSetFenceNV",
    /* 1766 */ "glSetFragmentShaderConstantATI",
    /* 1767 */ "glSetInvariantEXT",
    /* 1768 */ "glSetLocalConstantEXT",
    /* 1769 */ "glSetMultisamplefvAMD",
    /* 1770 */ "glShaderBinary",
    /* 1771 */ "glShaderOp1EXT",
    /* 1772 */ "glShaderOp2EXT",
    /* 1773 */ "glShaderOp3EXT",
    /* 1774 */ "glShaderSource",
    /* 1775 */ "glShaderSourceARB",
    /* 1776 */ "glShaderStorageBlockBinding",
    /* 1777 */ "glShadingRateImageBarrierNV",
    /* 1778 */ "glShadingRateImagePaletteNV",
    /* 1779 */ "glShadingRateSampleOrderCustomNV",
    /* 1780 */ "glShadingRateSampleOrderNV",
    /* 1781 */ "glSharpenTexFuncSGIS",
    /* 1782 */ "glSignalSemaphoreEXT",
    /* 1783 */ "glSignalSemaphoreui64NVX",
    /* 1784 */ "glSignalVkFenceNV",
    /* 1785 */ "glSignalVkSemaphoreNV",
    /* 1786 */ "glSpecializeShader",
    /* 1787 */ "glSpecializeShaderARB",
    /* 1788 */ "glSpriteParameterfSGIX",
    /* 1789 */ "glSpriteParameterfvSGIX",
    /* 1790 */ "glSpriteParameteriSGIX",
    /* 1791 */ "glSpriteParameterivSGIX",
    /* 1792 */ "glStartInstrumentsSGIX",
    /* 1793 */ "glStateCaptureNV",
    /* 1794 */ "glStencilClearTagEXT",
    /* 1795 */ "glStencilFillPathInstancedNV",
    /* 1796 */ "glStencilFillPathNV",
    /* 1797 */ "glStencilFunc",
    /* 1798 */ "glStencilFuncSeparate",
    /* 1799 */ "glStencilFuncSeparateATI",
    /* 1800 */ "glStencilMask",
    /* 1801 */ "glStencilMaskSeparate",
    /* 1802 */ "glStencilOp",
    /* 1803 */ "glStencilOpSeparate",
    /* 1804 */ "glStencilOpSeparateATI",
    /* 1805 */ "glStencilOpValueAMD",
    /* 1806 */ "glStencilStrokePathInstancedNV",
    /* 1807 */ "glStencilStrokePathNV",
    /* 1808 */ "glStencilThenCoverFillPathInstancedNV",
    /* 1809 */ "glStencilThenCoverFillPathNV",
    /* 1810 */ "glStencilThenCoverStrokePathInstancedNV",
    /* 1811 */ "glStencilThenCoverStrokePathNV",
    /* 1812 */ "glStopInstrumentsSGIX",
    /* 1813 */ "glStringMarkerGREMEDY",
    /* 1814 */ "glSubpixelPrecisionBiasNV",
    /* 1815 */ "glSwizzleEXT",
    /* 1816 */ "glSyncTextureINTEL",
    /* 1817 */ "glTagSampleBufferSGIX",
    /* 1818 */ "glTangent3bEXT",
    /* 1819 */ "glTangent3bvEXT",
    /* 1820 */ "glTangent3dEXT",
    /* 1821 */ "glTangent3dvEXT",
    /* 1822 */ "glTangent3fEXT",
    /* 1823 */ "glTangent3fvEXT",
    /* 1824 */ "glTangent3iEXT",
    /* 1825 */ "glTangent3ivEXT",
    /* 1826 */ "glTangent3sEXT",
    /* 1827 */ "glTangent3svEXT",
    /* 1828 */ "glTangentPointerEXT",
    /* 1829 */ "glTbufferMask3DFX",
    /* 1830 */ "glTessellationFactorAMD",
    /* 1831 */ "glTessellationModeAMD",
    /* 1832 */ "glTestFenceAPPLE",
    /* 1833 */ "glTestFenceNV",
    /* 1834 */ "glTestObjectAPPLE",
    /* 1835 */ "glTexAttachMemoryNV",
    /* 1836 */ "glTexBuffer",
    /* 1837 */ "glTexBufferARB",
    /* 1838 */ "glTexBufferEXT",
    /* 1839 */ "glTexBufferRange",
    /* 1840 */ "glTexBumpParameterfvATI",
    /* 1841 */ "glTexBumpParameterivATI",
    /* 1842 */ "glTexCoord1bOES",
    /* 1843 */ "glTexCoord1bvOES",
    /* 1844 */ "glTexCoord1hNV",
    /* 1845 */ "glTexCoord1hvNV",
    /* 1846 */ "glTexCoord1xOES",
    /* 1847 */ "glTexCoord1xvOES",
    /* 1848 */ "glTexCoord2bOES",
    /* 1849 */ "glTexCoord2bvOES",
    /* 1850 */ "glTexCoord2fColor3fVertex3fSUN",
    /* 1851 */ "glTexCoord2fColor3fVertex3fvSUN",
    /* 1852 */ "glTexCoord2fColor4fNormal3fVertex3fSUN",
    /* 1853 */ "glTexCoord2fColor4fNormal3fVertex3fvSUN",
    /* 1854 */ "glTexCoord2fColor4ubVertex3fSUN",
    /* 1855 */ "glTexCoord2fColor4ubVertex3fvSUN",
    /* 1856 */ "glTexCoord2fNormal3fVertex3fSUN",
    /* 1857 */ "glTexCoord2fNormal3fVertex3fvSUN",
    /* 1858 */ "glTexCoord2fVertex3fSUN",
    /* 1859 */ "glTexCoord2fVertex3fvSUN",
    /* 1860 */ "glTexCoord2hNV",
    /* 1861 */ "glTexCoord2hvNV",
    /* 1862 */ "glTexCoord2xOES",
    /* 1863 */ "glTexCoord2xvOES",
    /* 1864 */ "glTexCoord3bOES",
    /* 1865 */ "glTexCoord3bvOES",
    /* 1866 */ "glTexCoord3hNV",
    /* 1867 */ "glTexCoord3hvNV",
    /* 1868 */ "glTexCoord3xOES",
    /* 1869 */ "glTexCoord3xvOES",
    /* 1870 */ "glTexCoord4bOES",
    /* 1871 */ "glTexCoord4bvOES",
    /* 1872 */ "glTexCoord4fColor4fNormal3fVertex4fSUN",
    /* 1873 */ "glTexCoord4fColor4fNormal3fVertex4fvSUN",
    /* 1874 */ "glTexCoord4fVertex4fSUN",
    /* 1875 */ "glTexCoord4fVertex4fvSUN",
    /* 1876 */ "glTexCoord4hNV",
    /* 1877 */ "glTexCoord4hvNV",
    /* 1878 */ "glTexCoord4xOES",
    /* 1879 */ "glTexCoord4xvOES",
    /* 1880 */ "glTexCoordFormatNV",
    /* 1881 */ "glTexCoordPointerEXT",
    /* 1882 */ "glTexCoordPointerListIBM",
    /* 1883 */ "glTexCoordPointervINTEL",
    /* 1884 */ "glTexEnvxOES",
    /* 1885 */ "glTexEnvxvOES",
    /* 1886 */ "glTexFilterFuncSGIS",
    /* 1887 */ "glTexGenxOES",
    /* 1888 */ "glTexGenxvOES",
    /* 1889 */ "glTexImage1D",
    /* 1890 */ "glTexImage2D",
    /* 1891 */ "glTexImage2DExternalANGLE",
    /* 1892 */ "glTexImage2DMultisample",
    /* 1893 */ "glTexImage2DMultisampleCoverageNV",
    /* 1894 */ "glTexImage3D",
    /* 1895 */ "glTexImage3DEXT",
    /* 1896 */ "glTexImage3DMultisample",
    /* 1897 */ "glTexImage3DMultisampleCoverageNV",
    /* 1898 */ "glTexImage4DSGIS",
    /* 1899 */ "glTexPageCommitmentARB",
    /* 1900 */ "glTexPageCommitmentMemNV",
    /* 1901 */ "glTexParameterIiv",
    /* 1902 */ "glTexParameterIivEXT",
    /* 1903 */ "glTexParameterIuiv",
    /* 1904 */ "glTexParameterIuivEXT",
    /* 1905 */ "glTexParameterf",
    /* 1906 */ "glTexParameterfv",
    /* 1907 */ "glTexParameteri",
    /* 1908 */ "glTexParameteriv",
    /* 1909 */ "glTexParameterxOES",
    /* 1910 */ "glTexParameterxvOES",
    /* 1911 */ "glTexRenderbufferNV",
    /* 1912 */ "glTexStorage1D",
    /* 1913 */ "glTexStorage1DEXT",
    /* 1914 */ "glTexStorage2D",
    /* 1915 */ "glTexStorage2DEXT",
    /* 1916 */ "glTexStorage2DMultisample",
    /* 1917 */ "glTexStorage3D",
    /* 1918 */ "glTexStorage3DEXT",
    /* 1919 */ "glTexStorage3DMultisample",
    /* 1920 */ "glTexStorageMem1DEXT",
    /* 1921 */ "glTexStorageMem2DEXT",
    /* 1922 */ "glTexStorageMem2DMultisampleEXT",
    /* 1923 */ "glTexStorageMem3DEXT",
    /* 1924 */ "glTexStorageMem3DMultisampleEXT",
    /* 1925 */ "glTexStorageMemFlags2DANGLE",
    /* 1926 */ "glTexStorageMemFlags2DMultisampleANGLE",
    /* 1927 */ "glTexStorageMemFlags3DANGLE",
    /* 1928 */ "glTexStorageMemFlags3DMultisampleANGLE",
    /* 1929 */ "glTexStorageSparseAMD",
    /* 1930 */ "glTexSubImage1D",
    /* 1931 */ "glTexSubImage1DEXT",
    /* 1932 */ "glTexSubImage2D",
    /* 1933 */ "glTexSubImage2DEXT",
    /* 1934 */ "glTexSubImage3D",
    /* 1935 */ "glTexSubImage3DEXT",
    /* 1936 */ "glTexSubImage4DSGIS",
    /* 1937 */ "glTextureAttachMemoryNV",
    /* 1938 */ "glTextureBarrier",
    /* 1939 */ "glTextureBarrierNV",
    /* 1940 */ "glTextureBuffer",
    /* 1941 */ "glTextureBufferEXT",
    /* 1942 */ "glTextureBufferRange",
    /* 1943 */ "glTextureBufferRangeEXT",
    /* 1944 */ "glTextureColorMaskSGIS",
    /* 1945 */ "glTextureImage1DEXT",
    /* 1946 */ "glTextureImage2DEXT",
    /* 1947 */ "glTextureImage2DMultisampleCoverageNV",
    /* 1948 */ "glTextureImage2DMultisampleNV",
    /* 1949 */ "glTextureImage3DEXT",
    /* 1950 */ "glTextureImage3DMultisampleCoverageNV",
    /* 1951 */ "glTextureImage3DMultisampleNV",
    /* 1952 */ "glTextureLightEXT",
    /* 1953 */ "glTextureMaterialEXT",
    /* 1954 */ "glTextureNormalEXT",
    /* 1955 */ "glTexturePageCommitmentEXT",
    /* 1956 */ "glTexturePageCommitmentMemNV",
    /* 1957 */ "glTextureParameterIiv",
    /* 1958 */ "glTextureParameterIivEXT",
    /* 1959 */ "glTextureParameterIuiv",
    /* 1960 */ "glTextureParameterIuivEXT",
    /* 1961 */ "glTextureParameterf",
    /* 1962 */ "glTextureParameterfEXT",
    /* 1963 */ "glTextureParameterfv",
    /* 1964 */ "glTextureParameterfvEXT",
    /* 1965 */ "glTextureParameteri",
    /* 1966 */ "glTextureParameteriEXT",
    /* 1967 */ "glTextureParameteriv",
    /* 1968 */ "glTextureParameterivEXT",
    /* 1969 */ "glTextureRangeAPPLE",
    /* 1970 */ "glTextureRenderbufferEXT",
    /* 1971 */ "glTextureStorage1D",
    /* 1972 */ "glTextureStorage1DEXT",
    /* 1973 */ "glTextureStorage2D",
    /* 1974 */ "glTextureStorage2DEXT",
    /* 1975 */ "glTextureStorage2DMultisample",
    /* 1976 */ "glTextureStorage2DMultisampleEXT",
    /* 1977 */ "glTextureStorage3D",
    /* 1978 */ "glTextureStorage3DEXT",
    /* 1979 */ "glTextureStorage3DMultisample",
    /* 1980 */ "glTextureStorage3DMultisampleEXT",
    /* 1981 */ "glTextureStorageMem1DEXT",
    /* 1982 */ "glTextureStorageMem2DEXT",
    /* 1983 */ "glTextureStorageMem2DMultisampleEXT",
    /* 1984 */ "glTextureStorageMem3DEXT",
    /* 1985 */ "glTextureStorageMem3DMultisampleEXT",
    /* 1986 */ "glTextureStorageSparseAMD",
    /* 1987 */ "glTextureSubImage1D",
    /* 1988 */ "glTextureSubImage1DEXT",
    /* 1989 */ "glTextureSubImage2D",
    /* 1990 */ "glTextureSubImage2DEXT",
    /* 1991 */ "glTextureSubImage3D",
    /* 1992 */ "glTextureSubImage3DEXT",
    /* 1993 */ "glTextureView",
    /* 1994 */ "glTrackMatrixNV",
    /* 1995 */ "glTransformFeedbackAttribsNV",
    /* 1996 */ "glTransformFeedbackBufferBase",
    /* 1997 */ "glTransformFeedbackBufferRange",
    /* 1998 */ "glTransformFeedbackStreamAttribsNV",
    /* 1999 */ "glTransformFeedbackVaryings",
    /* 2000 */ "glTransformFeedbackVaryingsEXT",
    /* 2001 */ "glTransformFeedbackVaryingsNV",
    /* 2002 */ "glTransformPathNV",
    /* 2003 */ "glTranslatexOES",
    /* 2004 */ "glUniform1d",
    /* 2005 */ "glUniform1dv",
    /* 2006 */ "glUniform1f",
    /* 2007 */ "glUniform1fARB",
    /* 2008 */ "glUniform1fv",
    /* 2009 */ "glUniform1fvARB",
    /* 2010 */ "glUniform1i",
    /* 2011 */ "glUniform1i64ARB",
    /* 2012 */ "glUniform1i64NV",
    /* 2013 */ "glUniform1i64vARB",
    /* 2014 */ "glUniform1i64vNV",
    /* 2015 */ "glUniform1iARB",
    /* 2016 */ "glUniform1iv",
    /* 2017 */ "glUniform1ivARB",
    /* 2018 */ "glUniform1ui",
    /* 2019 */ "glUniform1ui64ARB",
    /* 2020 */ "glUniform1ui64NV",
    /* 2021 */ "glUniform1ui64vARB",
    /* 2022 */ "glUniform1ui64vNV",
    /* 2023 */ "glUniform1uiEXT",
    /* 2024 */ "glUniform1uiv",
    /* 2025 */ "glUniform1uivEXT",
    /* 2026 */ "glUniform2d",
    /* 2027 */ "glUniform2dv",
    /* 2028 */ "glUniform2f",
    /* 2029 */ "glUniform2fARB",
    /* 2030 */ "glUniform2fv",
    /* 2031 */ "glUniform2fvARB",
    /* 2032 */ "glUniform2i",
    /* 2033 */ "glUniform2i64ARB",
    /* 2034 */ "glUniform2i64NV",
    /* 2035 */ "glUniform2i64vARB",
    /* 2036 */ "glUniform2i64vNV",
    /* 2037 */ "glUniform2iARB",
    /* 2038 */ "glUniform2iv",
    /* 2039 */ "glUniform2ivARB",
    /* 2040 */ "glUniform2ui",
    /* 2041 */ "glUniform2ui64ARB",
    /* 2042 */ "glUniform2ui64NV",
    /* 2043 */ "glUniform2ui64vARB",
    /* 2044 */ "glUniform2ui64vNV",
    /* 2045 */ "glUniform2uiEXT",
    /* 2046 */ "glUniform2uiv",
    /* 2047 */ "glUniform2uivEXT",
    /* 2048 */ "glUniform3d",
    /* 2049 */ "glUniform3dv",
    /* 2050 */ "glUniform3f",
    /* 2051 */ "glUniform3fARB",
    /* 2052 */ "glUniform3fv",
    /* 2053 */ "glUniform3fvARB",
    /* 2054 */ "glUniform3i",
    /* 2055 */ "glUniform3i64ARB",
    /* 2056 */ "glUniform3i64NV",
    /* 2057 */ "glUniform3i64vARB",
    /* 2058 */ "glUniform3i64vNV",
    /* 2059 */ "glUniform3iARB",
    /* 2060 */ "glUniform3iv",
    /* 2061 */ "glUniform3ivARB",
    /* 2062 */ "glUniform3ui",
    /* 2063 */ "glUniform3ui64ARB",
    /* 2064 */ "glUniform3ui64NV",
    /* 2065 */ "glUniform3ui64vARB",
    /* 2066 */ "glUniform3ui64vNV",
    /* 2067 */ "glUniform3uiEXT",
    /* 2068 */ "glUniform3uiv",
    /* 2069 */ "glUniform3uivEXT",
    /* 2070 */ "glUniform4d",
    /* 2071 */ "glUniform4dv",
    /* 2072 */ "glUniform4f",
    /* 2073 */ "glUniform4fARB",
    /* 2074 */ "glUniform4fv",
    /* 2075 */ "glUniform4fvARB",
    /* 2076 */ "glUniform4i",
    /* 2077 */ "glUniform4i64ARB",
    /* 2078 */ "glUniform4i64NV",
    /* 2079 */ "glUniform4i64vARB",
    /* 2080 */ "glUniform4i64vNV",
    /* 2081 */ "glUniform4iARB",
    /* 2082 */ "glUniform4iv",
    /* 2083 */ "glUniform4ivARB",
    /* 2084 */ "glUniform4ui",
    /* 2085 */ "glUniform4ui64ARB",
    /* 2086 */ "glUniform4ui64NV",
    /* 2087 */ "glUniform4ui64vARB",
    /* 2088 */ "glUniform4ui64vNV",
    /* 2089 */ "glUniform4uiEXT",
    /* 2090 */ "glUniform4uiv",
    /* 2091 */ "glUniform4uivEXT",
    /* 2092 */ "glUniformBlockBinding",
    /* 2093 */ "glUniformBufferEXT",
    /* 2094 */ "glUniformHandleui64ARB",
    /* 2095 */ "glUniformHandleui64NV",
    /* 2096 */ "glUniformHandleui64vARB",
    /* 2097 */ "glUniformHandleui64vNV",
    /* 2098 */ "glUniformMatrix2dv",
    /* 2099 */ "glUniformMatrix2fv",
    /* 2100 */ "glUniformMatrix2fvARB",
    /* 2101 */ "glUniformMatrix2x3dv",
    /* 2102 */ "glUniformMatrix2x3fv",
    /* 2103 */ "glUniformMatrix2x4dv",
    /* 2104 */ "glUniformMatrix2x4fv",
    /* 2105 */ "glUniformMatrix3dv",
    /* 2106 */ "glUniformMatrix3fv",
    /* 2107 */ "glUniformMatrix3fvARB",
    /* 2108 */ "glUniformMatrix3x2dv",
    /* 2109 */ "glUniformMatrix3x2fv",
    /* 2110 */ "glUniformMatrix3x4dv",
    /* 2111 */ "glUniformMatrix3x4fv",
    /* 2112 */ "glUniformMatrix4dv",
    /* 2113 */ "glUniformMatrix4fv",
    /* 2114 */ "glUniformMatrix4fvARB",
    /* 2115 */ "glUniformMatrix4x2dv",
    /* 2116 */ "glUniformMatrix4x2fv",
    /* 2117 */ "glUniformMatrix4x3dv",
    /* 2118 */ "glUniformMatrix4x3fv",
    /* 2119 */ "glUniformSubroutinesuiv",
    /* 2120 */ "glUniformui64NV",
    /* 2121 */ "glUniformui64vNV",
    /* 2122 */ "glUnlockArraysEXT",
    /* 2123 */ "glUnmapBuffer",
    /* 2124 */ "glUnmapBufferARB",
    /* 2125 */ "glUnmapNamedBuffer",
    /* 2126 */ "glUnmapNamedBufferEXT",
    /* 2127 */ "glUnmapObjectBufferATI",
    /* 2128 */ "glUnmapTexture2DINTEL",
    /* 2129 */ "glUpdateObjectBufferATI",
    /* 2130 */ "glUploadGpuMaskNVX",
    /* 2131 */ "glUseProgram",
    /* 2132 */ "glUseProgramObjectARB",
    /* 2133 */ "glUseProgramStages",
    /* 2134 */ "glUseShaderProgramEXT",
    /* 2135 */ "glVDPAUFiniNV",
    /* 2136 */ "glVDPAUGetSurfaceivNV",
    /* 2137 */ "glVDPAUInitNV",
    /* 2138 */ "glVDPAUIsSurfaceNV",
    /* 2139 */ "glVDPAUMapSurfacesNV",
    /* 2140 */ "glVDPAURegisterOutputSurfaceNV",
    /* 2141 */ "glVDPAURegisterVideoSurfaceNV",
    /* 2142 */ "glVDPAURegisterVideoSurfaceWithPictureStructureNV",
    /* 2143 */ "glVDPAUSurfaceAccessNV",
    /* 2144 */ "glVDPAUUnmapSurfacesNV",
    /* 2145 */ "glVDPAUUnregisterSurfaceNV",
    /* 2146 */ "glValidateProgram",
    /* 2147 */ "glValidateProgramARB",
    /* 2148 */ "glValidateProgramPipeline",
    /* 2149 */ "glVariantArrayObjectATI",
    /* 2150 */ "glVariantPointerEXT",
    /* 2151 */ "glVariantbvEXT",
    /* 2152 */ "glVariantdvEXT",
    /* 2153 */ "glVariantfvEXT",
    /* 2154 */ "glVariantivEXT",
    /* 2155 */ "glVariantsvEXT",
    /* 2156 */ "glVariantubvEXT",
    /* 2157 */ "glVariantuivEXT",
    /* 2158 */ "glVariantusvEXT",
    /* 2159 */ "glVertex2bOES",
    /* 2160 */ "glVertex2bvOES",
    /* 2161 */ "glVertex2hNV",
    /* 2162 */ "glVertex2hvNV",
    /* 2163 */ "glVertex2xOES",
    /* 2164 */ "glVertex2xvOES",
    /* 2165 */ "glVertex3bOES",
    /* 2166 */ "glVertex3bvOES",
    /* 2167 */ "glVertex3hNV",
    /* 2168 */ "glVertex3hvNV",
    /* 2169 */ "glVertex3xOES",
    /* 2170 */ "glVertex3xvOES",
    /* 2171 */ "glVertex4bOES",
    /* 2172 */ "glVertex4bvOES",
    /* 2173 */ "glVertex4hNV",
    /* 2174 */ "glVertex4hvNV",
    /* 2175 */ "glVertex4xOES",
    /* 2176 */ "glVertex4xvOES",
    /* 2177 */ "glVertexArrayAttribBinding",
    /* 2178 */ "glVertexArrayAttribFormat",
    /* 2179 */ "glVertexArrayAttribIFormat",
    /* 2180 */ "glVertexArrayAttribLFormat",
    /* 2181 */ "glVertexArrayBindVertexBufferEXT",
    /* 2182 */ "glVertexArrayBindingDivisor",
    /* 2183 */ "glVertexArrayColorOffsetEXT",
    /* 2184 */ "glVertexArrayEdgeFlagOffsetEXT",
    /* 2185 */ "glVertexArrayElementBuffer",
    /* 2186 */ "glVertexArrayFogCoordOffsetEXT",
    /* 2187 */ "glVertexArrayIndexOffsetEXT",
    /* 2188 */ "glVertexArrayMultiTexCoordOffsetEXT",
    /* 2189 */ "glVertexArrayNormalOffsetEXT",
    /* 2190 */ "glVertexArrayParameteriAPPLE",
    /* 2191 */ "glVertexArrayRangeAPPLE",
    /* 2192 */ "glVertexArrayRangeNV",
    /* 2193 */ "glVertexArraySecondaryColorOffsetEXT",
    /* 2194 */ "glVertexArrayTexCoordOffsetEXT",
    /* 2195 */ "glVertexArrayVertexAttribBindingEXT",
    /* 2196 */ "glVertexArrayVertexAttribDivisorEXT",
    /* 2197 */ "glVertexArrayVertexAttribFormatEXT",
    /* 2198 */ "glVertexArrayVertexAttribIFormatEXT",
    /* 2199 */ "glVertexArrayVertexAttribIOffsetEXT",
    /* 2200 */ "glVertexArrayVertexAttribLFormatEXT",
    /* 2201 */ "glVertexArrayVertexAttribLOffsetEXT",
    /* 2202 */ "glVertexArrayVertexAttribOffsetEXT",
    /* 2203 */ "glVertexArrayVertexBindingDivisorEXT",
    /* 2204 */ "glVertexArrayVertexBuffer",
    /* 2205 */ "glVertexArrayVertexBuffers",
    /* 2206 */ "glVertexArrayVertexOffsetEXT",
    /* 2207 */ "glVertexAttrib1d",
    /* 2208 */ "glVertexAttrib1dARB",
    /* 2209 */ "glVertexAttrib1dNV",
    /* 2210 */ "glVertexAttrib1dv",
    /* 2211 */ "glVertexAttrib1dvARB",
    /* 2212 */ "glVertexAttrib1dvNV",
    /* 2213 */ "glVertexAttrib1f",
    /* 2214 */ "glVertexAttrib1fARB",
    /* 2215 */ "glVertexAttrib1fNV",
    /* 2216 */ "glVertexAttrib1fv",
    /* 2217 */ "glVertexAttrib1fvARB",
    /* 2218 */ "glVertexAttrib1fvNV",
    /* 2219 */ "glVertexAttrib1hNV",
    /* 2220 */ "glVertexAttrib1hvNV",
    /* 2221 */ "glVertexAttrib1s",
    /* 2222 */ "glVertexAttrib1sARB",
    /* 2223 */ "glVertexAttrib1sNV",
    /* 2224 */ "glVertexAttrib1sv",
    /* 2225 */ "glVertexAttrib1svARB",
    /* 2226 */ "glVertexAttrib1svNV",
    /* 2227 */ "glVertexAttrib2d",
    /* 2228 */ "glVertexAttrib2dARB",
    /* 2229 */ "glVertexAttrib2dNV",
    /* 2230 */ "glVertexAttrib2dv",
    /* 2231 */ "glVertexAttrib2dvARB",
    /* 2232 */ "glVertexAttrib2dvNV",
    /* 2233 */ "glVertexAttrib2f",
    /* 2234 */ "glVertexAttrib2fARB",
    /* 2235 */ "glVertexAttrib2fNV",
    /* 2236 */ "glVertexAttrib2fv",
    /* 2237 */ "glVertexAttrib2fvARB",
    /* 2238 */ "glVertexAttrib2fvNV",
    /* 2239 */ "glVertexAttrib2hNV",
    /* 2240 */ "glVertexAttrib2hvNV",
    /* 2241 */ "glVertexAttrib2s",
    /* 2242 */ "glVertexAttrib2sARB",
    /* 2243 */ "glVertexAttrib2sNV",
    /* 2244 */ "glVertexAttrib2sv",
    /* 2245 */ "glVertexAttrib2svARB",
    /* 2246 */ "glVertexAttrib2svNV",
    /* 2247 */ "glVertexAttrib3d",
    /* 2248 */ "glVertexAttrib3dARB",
    /* 2249 */ "glVertexAttrib3dNV",
    /* 2250 */ "glVertexAttrib3dv",
    /* 2251 */ "glVertexAttrib3dvARB",
    /* 2252 */ "glVertexAttrib3dvNV",
    /* 2253 */ "glVertexAttrib3f",
    /* 2254 */ "glVertexAttrib3fARB",
    /* 2255 */ "glVertexAttrib3fNV",
    /* 2256 */ "glVertexAttrib3fv",
    /* 2257 */ "glVertexAttrib3fvARB",
    /* 2258 */ "glVertexAttrib3fvNV",
    /* 2259 */ "glVertexAttrib3hNV",
    /* 2260 */ "glVertexAttrib3hvNV",
    /* 2261 */ "glVertexAttrib3s",
    /* 2262 */ "glVertexAttrib3sARB",
    /* 2263 */ "glVertexAttrib3sNV",
    /* 2264 */ "glVertexAttrib3sv",
    /* 2265 */ "glVertexAttrib3svARB",
    /* 2266 */ "glVertexAttrib3svNV",
    /* 2267 */ "glVertexAttrib4Nbv",
    /* 2268 */ "glVertexAttrib4NbvARB",
    /* 2269 */ "glVertexAttrib4Niv",
    /* 2270 */ "glVertexAttrib4NivARB",
    /* 2271 */ "glVertexAttrib4Nsv",
    /* 2272 */ "glVertexAttrib4NsvARB",
    /* 2273 */ "glVertexAttrib4Nub",
    /* 2274 */ "glVertexAttrib4NubARB",
    /* 2275 */ "glVertexAttrib4Nubv",
    /* 2276 */ "glVertexAttrib4NubvARB",
    /* 2277 */ "glVertexAttrib4Nuiv",
    /* 2278 */ "glVertexAttrib4NuivARB",
    /* 2279 */ "glVertexAttrib4Nusv",
    /* 2280 */ "glVertexAttrib4NusvARB",
    /* 2281 */ "glVertexAttrib4bv",
    /* 2282 */ "glVertexAttrib4bvARB",
    /* 2283 */ "glVertexAttrib4d",
    /* 2284 */ "glVertexAttrib4dARB",
    /* 2285 */ "glVertexAttrib4dNV",
    /* 2286 */ "glVertexAttrib4dv",
    /* 2287 */ "glVertexAttrib4dvARB",
    /* 2288 */ "glVertexAttrib4dvNV",
    /* 2289 */ "glVertexAttrib4f",
    /* 2290 */ "glVertexAttrib4fARB",
    /* 2291 */ "glVertexAttrib4fNV",
    /* 2292 */ "glVertexAttrib4fv",
    /* 2293 */ "glVertexAttrib4fvARB",
    /* 2294 */ "glVertexAttrib4fvNV",
    /* 2295 */ "glVertexAttrib4hNV",
    /* 2296 */ "glVertexAttrib4hvNV",
    /* 2297 */ "glVertexAttrib4iv",
    /* 2298 */ "glVertexAttrib4ivARB",
    /* 2299 */ "glVertexAttrib4s",
    /* 2300 */ "glVertexAttrib4sARB",
    /* 2301 */ "glVertexAttrib4sNV",
    /* 2302 */ "glVertexAttrib4sv",
    /* 2303 */ "glVertexAttrib4svARB",
    /* 2304 */ "glVertexAttrib4svNV",
    /* 2305 */ "glVertexAttrib4ubNV",
    /* 2306 */ "glVertexAttrib4ubv",
    /* 2307 */ "glVertexAttrib4ubvARB",
    /* 2308 */ "glVertexAttrib4ubvNV",
    /* 2309 */ "glVertexAttrib4uiv",
    /* 2310 */ "glVertexAttrib4uivARB",
    /* 2311 */ "glVertexAttrib4usv",
    /* 2312 */ "glVertexAttrib4usvARB",
    /* 2313 */ "glVertexAttribArrayObjectATI",
    /* 2314 */ "glVertexAttribBinding",
    /* 2315 */ "glVertexAttribDivisor",
    /* 2316 */ "glVertexAttribDivisorARB",
    /* 2317 */ "glVertexAttribFormat",
    /* 2318 */ "glVertexAttribFormatNV",
    /* 2319 */ "glVertexAttribI1i",
    /* 2320 */ "glVertexAttribI1iEXT",
    /* 2321 */ "glVertexAttribI1iv",
    /* 2322 */ "glVertexAttribI1ivEXT",
    /* 2323 */ "glVertexAttribI1ui",
    /* 2324 */ "glVertexAttribI1uiEXT",
    /* 2325 */ "glVertexAttribI1uiv",
    /* 2326 */ "glVertexAttribI1uivEXT",
    /* 2327 */ "glVertexAttribI2i",
    /* 2328 */ "glVertexAttribI2iEXT",
    /* 2329 */ "glVertexAttribI2iv",
    /* 2330 */ "glVertexAttribI2ivEXT",
    /* 2331 */ "glVertexAttribI2ui",
    /* 2332 */ "glVertexAttribI2uiEXT",
    /* 2333 */ "glVertexAttribI2uiv",
    /* 2334 */ "glVertexAttribI2uivEXT",
    /* 2335 */ "glVertexAttribI3i",
    /* 2336 */ "glVertexAttribI3iEXT",
    /* 2337 */ "glVertexAttribI3iv",
    /* 2338 */ "glVertexAttribI3ivEXT",
    /* 2339 */ "glVertexAttribI3ui",
    /* 2340 */ "glVertexAttribI3uiEXT",
    /* 2341 */ "glVertexAttribI3uiv",
    /* 2342 */ "glVertexAttribI3uivEXT",
    /* 2343 */ "glVertexAttribI4bv",
    /* 2344 */ "glVertexAttribI4bvEXT",
    /* 2345 */ "glVertexAttribI4i",
    /* 2346 */ "glVertexAttribI4iEXT",
    /* 2347 */ "glVertexAttribI4iv",
    /* 2348 */ "glVertexAttribI4ivEXT",
    /* 2349 */ "glVertexAttribI4sv",
    /* 2350 */ "glVertexAttribI4svEXT",
    /* 2351 */ "glVertexAttribI4ubv",
    /* 2352 */ "glVertexAttribI4ubvEXT",
    /* 2353 */ "glVertexAttribI4ui",
    /* 2354 */ "glVertexAttribI4uiEXT",
    /* 2355 */ "glVertexAttribI4uiv",
    /* 2356 */ "glVertexAttribI4uivEXT",
    /* 2357 */ "glVertexAttribI4usv",
    /* 2358 */ "glVertexAttribI4usvEXT",
    /* 2359 */ "glVertexAttribIFormat",
    /* 2360 */ "glVertexAttribIFormatNV",
    /* 2361 */ "glVertexAttribIPointer",
    /* 2362 */ "glVertexAttribIPointerEXT",
    /* 2363 */ "glVertexAttribL1d",
    /* 2364 */ "glVertexAttribL1dEXT",
    /* 2365 */ "glVertexAttribL1dv",
    /* 2366 */ "glVertexAttribL1dvEXT",
    /* 2367 */ "glVertexAttribL1i64NV",
    /* 2368 */ "glVertexAttribL1i64vNV",
    /* 2369 */ "glVertexAttribL1ui64ARB",
    /* 2370 */ "glVertexAttribL1ui64NV",
    /* 2371 */ "glVertexAttribL1ui64vARB",
    /* 2372 */ "glVertexAttribL1ui64vNV",
    /* 2373 */ "glVertexAttribL2d",
    /* 2374 */ "glVertexAttribL2dEXT",
    /* 2375 */ "glVertexAttribL2dv",
    /* 2376 */ "glVertexAttribL2dvEXT",
    /* 2377 */ "glVertexAttribL2i64NV",
    /* 2378 */ "glVertexAttribL2i64vNV",
    /* 2379 */ "glVertexAttribL2ui64NV",
    /* 2380 */ "glVertexAttribL2ui64vNV",
    /* 2381 */ "glVertexAttribL3d",
    /* 2382 */ "glVertexAttribL3dEXT",
    /* 2383 */ "glVertexAttribL3dv",
    /* 2384 */ "glVertexAttribL3dvEXT",
    /* 2385 */ "glVertexAttribL3i64NV",
    /* 2386 */ "glVertexAttribL3i64vNV",
    /* 2387 */ "glVertexAttribL3ui64NV",
    /* 2388 */ "glVertexAttribL3ui64vNV",
    /* 2389 */ "glVertexAttribL4d",
    /* 2390 */ "glVertexAttribL4dEXT",
    /* 2391 */ "glVertexAttribL4dv",
    /* 2392 */ "glVertexAttribL4dvEXT",
    /* 2393 */ "glVertexAttribL4i64NV",
    /* 2394 */ "glVertexAttribL4i64vNV",
    /* 2395 */ "glVertexAttribL4ui64NV",
    /* 2396 */ "glVertexAttribL4ui64vNV",
    /* 2397 */ "glVertexAttribLFormat",
    /* 2398 */ "glVertexAttribLFormatNV",
    /* 2399 */ "glVertexAttribLPointer",
    /* 2400 */ "glVertexAttribLPointerEXT",
    /* 2401 */ "glVertexAttribP1ui",
    /* 2402 */ "glVertexAttribP1uiv",
    /* 2403 */ "glVertexAttribP2ui",
    /* 2404 */ "glVertexAttribP2uiv",
    /* 2405 */ "glVertexAttribP3ui",
    /* 2406 */ "glVertexAttribP3uiv",
    /* 2407 */ "glVertexAttribP4ui",
    /* 2408 */ "glVertexAttribP4uiv",
    /* 2409 */ "glVertexAttribParameteriAMD",
    /* 2410 */ "glVertexAttribPointer",
    /* 2411 */ "glVertexAttribPointerARB",
    /* 2412 */ "glVertexAttribPointerNV",
    /* 2413 */ "glVertexAttribs1dvNV",
    /* 2414 */ "glVertexAttribs1fvNV",
    /* 2415 */ "glVertexAttribs1hvNV",
    /* 2416 */ "glVertexAttribs1svNV",
    /* 2417 */ "glVertexAttribs2dvNV",
    /* 2418 */ "glVertexAttribs2fvNV",
    /* 2419 */ "glVertexAttribs2hvNV",
    /* 2420 */ "glVertexAttribs2svNV",
    /* 2421 */ "glVertexAttribs3dvNV",
    /* 2422 */ "glVertexAttribs3fvNV",
    /* 2423 */ "glVertexAttribs3hvNV",
    /* 2424 */ "glVertexAttribs3svNV",
    /* 2425 */ "glVertexAttribs4dvNV",
    /* 2426 */ "glVertexAttribs4fvNV",
    /* 2427 */ "glVertexAttribs4hvNV",
    /* 2428 */ "glVertexAttribs4svNV",
    /* 2429 */ "glVertexAttribs4ubvNV",
    /* 2430 */ "glVertexBindingDivisor",
    /* 2431 */ "glVertexBlendARB",
    /* 2432 */ "glVertexBlendEnvfATI",
    /* 2433 */ "glVertexBlendEnviATI",
    /* 2434 */ "glVertexFormatNV",
    /* 2435 */ "glVertexPointerEXT",
    /* 2436 */ "glVertexPointerListIBM",
    /* 2437 */ "glVertexPointervINTEL",
    /* 2438 */ "glVertexStream1dATI",
    /* 2439 */ "glVertexStream1dvATI",
    /* 2440 */ "glVertexStream1fATI",
    /* 2441 */ "glVertexStream1fvATI",
    /* 2442 */ "glVertexStream1iATI",
    /* 2443 */ "glVertexStream1ivATI",
    /* 2444 */ "glVertexStream1sATI",
    /* 2445 */ "glVertexStream1svATI",
    /* 2446 */ "glVertexStream2dATI",
    /* 2447 */ "glVertexStream2dvATI",
    /* 2448 */ "glVertexStream2fATI",
    /* 2449 */ "glVertexStream2fvATI",
    /* 2450 */ "glVertexStream2iATI",
    /* 2451 */ "glVertexStream2ivATI",
    /* 2452 */ "glVertexStream2sATI",
    /* 2453 */ "glVertexStream2svATI",
    /* 2454 */ "glVertexStream3dATI",
    /* 2455 */ "glVertexStream3dvATI",
    /* 2456 */ "glVertexStream3fATI",
    /* 2457 */ "glVertexStream3fvATI",
    /* 2458 */ "glVertexStream3iATI",
    /* 2459 */ "glVertexStream3ivATI",
    /* 2460 */ "glVertexStream3sATI",
    /* 2461 */ "glVertexStream3svATI",
    /* 2462 */ "glVertexStream4dATI",
    /* 2463 */ "glVertexStream4dvATI",
    /* 2464 */ "glVertexStream4fATI",
    /* 2465 */ "glVertexStream4fvATI",
    /* 2466 */ "glVertexStream4iATI",
    /* 2467 */ "glVertexStream4ivATI",
    /* 2468 */ "glVertexStream4sATI",
    /* 2469 */ "glVertexStream4svATI",
    /* 2470 */ "glVertexWeightPointerEXT",
    /* 2471 */ "glVertexWeightfEXT",
    /* 2472 */ "glVertexWeightfvEXT",
    /* 2473 */ "glVertexWeighthNV",
    /* 2474 */ "glVertexWeighthvNV",
    /* 2475 */ "glVideoCaptureNV",
    /* 2476 */ "glVideoCaptureStreamParameterdvNV",
    /* 2477 */ "glVideoCaptureStreamParameterfvNV",
    /* 2478 */ "glVideoCaptureStreamParameterivNV",
    /* 2479 */ "glViewport",
    /* 2480 */ "glViewportArrayv",
    /* 2481 */ "glViewportIndexedf",
    /* 2482 */ "glViewportIndexedfv",
    /* 2483 */ "glViewportPositionWScaleNV",
    /* 2484 */ "glViewportSwizzleNV",
    /* 2485 */ "glWaitSemaphoreEXT",
    /* 2486 */ "glWaitSemaphoreui64NVX",
    /* 2487 */ "glWaitSync",
    /* 2488 */ "glWaitVkSemaphoreNV",
    /* 2489 */ "glWeightPathsNV",
    /* 2490 */ "glWeightPointerARB",
    /* 2491 */ "glWeightbvARB",
    /* 2492 */ "glWeightdvARB",
    /* 2493 */ "glWeightfvARB",
    /* 2494 */ "glWeightivARB",
    /* 2495 */ "glWeightsvARB",
    /* 2496 */ "glWeightubvARB",
    /* 2497 */ "glWeightuivARB",
    /* 2498 */ "glWeightusvARB",
    /* 2499 */ "glWindowPos2dARB",
    /* 2500 */ "glWindowPos2dMESA",
    /* 2501 */ "glWindowPos2dvARB",
    /* 2502 */ "glWindowPos2dvMESA",
    /* 2503 */ "glWindowPos2fARB",
    /* 2504 */ "glWindowPos2fMESA",
    /* 2505 */ "glWindowPos2fvARB",
    /* 2506 */ "glWindowPos2fvMESA",
    /* 2507 */ "glWindowPos2iARB",
    /* 2508 */ "glWindowPos2iMESA",
    /* 2509 */ "glWindowPos2ivARB",
    /* 2510 */ "glWindowPos2ivMESA",
    /* 2511 */ "glWindowPos2sARB",
    /* 2512 */ "glWindowPos2sMESA",
    /* 2513 */ "glWindowPos2svARB",
    /* 2514 */ "glWindowPos2svMESA",
    /* 2515 */ "glWindowPos3dARB",
    /* 2516 */ "glWindowPos3dMESA",
    /* 2517 */ "glWindowPos3dvARB",
    /* 2518 */ "glWindowPos3dvMESA",
    /* 2519 */ "glWindowPos3fARB",
    /* 2520 */ "glWindowPos3fMESA",
    /* 2521 */ "glWindowPos3fvARB",
    /* 2522 */ "glWindowPos3fvMESA",
    /* 2523 */ "glWindowPos3iARB",
    /* 2524 */ "glWindowPos3iMESA",
    /* 2525 */ "glWindowPos3ivARB",
    /* 2526 */ "glWindowPos3ivMESA",
    /* 2527 */ "glWindowPos3sARB",
    /* 2528 */ "glWindowPos3sMESA",
    /* 2529 */ "glWindowPos3svARB",
    /* 2530 */ "glWindowPos3svMESA",
    /* 2531 */ "glWindowPos4dMESA",
    /* 2532 */ "glWindowPos4dvMESA",
    /* 2533 */ "glWindowPos4fMESA",
    /* 2534 */ "glWindowPos4fvMESA",
    /* 2535 */ "glWindowPos4iMESA",
    /* 2536 */ "glWindowPos4ivMESA",
    /* 2537 */ "glWindowPos4sMESA",
    /* 2538 */ "glWindowPos4svMESA",
    /* 2539 */ "glWindowRectanglesEXT",
    /* 2540 */ "glWriteMaskEXT",
    /* 2541 */ "glAcquireTexturesANGLE",
    /* 2542 */ "glActiveShaderProgramEXT",
    /* 2543 */ "glAlphaFuncQCOM",
    /* 2544 */ "glBeginPixelLocalStorageANGLE",
    /* 2545 */ "glBeginQueryEXT",
    /* 2546 */ "glBindFragDataLocationIndexedEXT",
    /* 2547 */ "glBindProgramPipelineEXT",
    /* 2548 */ "glBindUniformLocationCHROMIUM",
    /* 2549 */ "glBindVertexArrayOES",
    /* 2550 */ "glBlendBarrier",
    /* 2551 */ "glBlendEquationSeparateiEXT",
    /* 2552 */ "glBlendEquationSeparateiOES",
    /* 2553 */ "glBlendEquationiEXT",
    /* 2554 */ "glBlendEquationiOES",
    /* 2555 */ "glBlendFuncSeparateiEXT",
    /* 2556 */ "glBlendFuncSeparateiOES",
    /* 2557 */ "glBlendFunciEXT",
    /* 2558 */ "glBlendFunciOES",
    /* 2559 */ "glBlitFramebufferANGLE",
    /* 2560 */ "glBlitFramebufferNV",
    /* 2561 */ "glBufferStorageEXT",
    /* 2562 */ "glClearPixelLocalStorageuiEXT",
    /* 2563 */ "glClearTexImageEXT",
    /* 2564 */ "glClearTexSubImageEXT",
    /* 2565 */ "glClientWaitSyncAPPLE",
    /* 2566 */ "glClipControlEXT",
    /* 2567 */ "glColorMaskiEXT",
    /* 2568 */ "glColorMaskiOES",
    /* 2569 */ "glCompressedCopyTextureCHROMIUM",
    /* 2570 */ "glCompressedTexImage2DRobustANGLE",
    /* 2571 */ "glCompressedTexImage3DOES",
    /* 2572 */ "glCompressedTexImage3DRobustANGLE",
    /* 2573 */ "glCompressedTexSubImage2DRobustANGLE",
    /* 2574 */ "glCompressedTexSubImage3DOES",
    /* 2575 */ "glCompressedTexSubImage3DRobustANGLE",
    /* 2576 */ "glCopyBufferSubDataNV",
    /* 2577 */ "glCopyImageSubDataEXT",
    /* 2578 */ "glCopyImageSubDataOES",
    /* 2579 */ "glCopySubTexture3DANGLE",
    /* 2580 */ "glCopySubTextureCHROMIUM",
    /* 2581 */ "glCopyTexSubImage3DOES",
    /* 2582 */ "glCopyTexture3DANGLE",
    /* 2583 */ "glCopyTextureCHROMIUM",
    /* 2584 */ "glCopyTextureLevelsAPPLE",
    /* 2585 */ "glCoverageMaskNV",
    /* 2586 */ "glCoverageModulationCHROMIUM",
    /* 2587 */ "glCoverageOperationNV",
    /* 2588 */ "glCreateShaderProgramvEXT",
    /* 2589 */ "glDebugMessageCallbackKHR",
    /* 2590 */ "glDebugMessageControlKHR",
    /* 2591 */ "glDebugMessageInsertKHR",
    /* 2592 */ "glDeleteProgramPipelinesEXT",
    /* 2593 */ "glDeleteQueriesEXT",
    /* 2594 */ "glDeleteSyncAPPLE",
    /* 2595 */ "glDeleteVertexArraysOES",
    /* 2596 */ "glDepthRangeArrayfvNV",
    /* 2597 */ "glDepthRangeArrayfvOES",
    /* 2598 */ "glDepthRangeIndexedfNV",
    /* 2599 */ "glDepthRangeIndexedfOES",
    /* 2600 */ "glDisableDriverControlQCOM",
    /* 2601 */ "glDisableExtensionANGLE",
    /* 2602 */ "glDisableiEXT",
    /* 2603 */ "glDisableiNV",
    /* 2604 */ "glDisableiOES",
    /* 2605 */ "glDiscardFramebufferEXT",
    /* 2606 */ "glDrawArraysInstancedANGLE",
    /* 2607 */ "glDrawArraysInstancedBaseInstanceANGLE",
    /* 2608 */ "glDrawArraysInstancedBaseInstanceEXT",
    /* 2609 */ "glDrawArraysInstancedNV",
    /* 2610 */ "glDrawBuffersEXT",
    /* 2611 */ "glDrawBuffersIndexedEXT",
    /* 2612 */ "glDrawBuffersNV",
    /* 2613 */ "glDrawElementsBaseVertexEXT",
    /* 2614 */ "glDrawElementsBaseVertexOES",
    /* 2615 */ "glDrawElementsInstancedANGLE",
    /* 2616 */ "glDrawElementsInstancedBaseInstanceEXT",
    /* 2617 */ "glDrawElementsInstancedBaseVertexBaseInstanceANGLE",
    /* 2618 */ "glDrawElementsInstancedBaseVertexBaseInstanceEXT",
    /* 2619 */ "glDrawElementsInstancedBaseVertexEXT",
    /* 2620 */ "glDrawElementsInstancedBaseVertexOES",
    /* 2621 */ "glDrawElementsInstancedNV",
    /* 2622 */ "glDrawRangeElementsBaseVertexEXT",
    /* 2623 */ "glDrawRangeElementsBaseVertexOES",
    /* 2624 */ "glDrawTransformFeedbackEXT",
    /* 2625 */ "glDrawTransformFeedbackInstancedEXT",
    /* 2626 */ "glEGLImageTargetRenderbufferStorageOES",
    /* 2627 */ "glEGLImageTargetTexture2DOES",
    /* 2628 */ "glEnableDriverControlQCOM",
    /* 2629 */ "glEnableiEXT",
    /* 2630 */ "glEnableiNV",
    /* 2631 */ "glEnableiOES",
    /* 2632 */ "glEndPixelLocalStorageANGLE",
    /* 2633 */ "glEndQueryEXT",
    /* 2634 */ "glEndTilingQCOM",
    /* 2635 */ "glExtGetBufferPointervQCOM",
    /* 2636 */ "glExtGetBuffersQCOM",
    /* 2637 */ "glExtGetFramebuffersQCOM",
    /* 2638 */ "glExtGetProgramBinarySourceQCOM",
    /* 2639 */ "glExtGetProgramsQCOM",
    /* 2640 */ "glExtGetRenderbuffersQCOM",
    /* 2641 */ "glExtGetShadersQCOM",
    /* 2642 */ "glExtGetTexLevelParameterivQCOM",
    /* 2643 */ "glExtGetTexSubImageQCOM",
    /* 2644 */ "glExtGetTexturesQCOM",
    /* 2645 */ "glExtIsProgramBinaryQCOM",
    /* 2646 */ "glExtTexObjectStateOverrideiQCOM",
    /* 2647 */ "glExtrapolateTex2DQCOM",
    /* 2648 */ "glFenceSyncAPPLE",
    /* 2649 */ "glFlushMappedBufferRangeEXT",
    /* 2650 */ "glFramebufferFetchBarrierQCOM",
    /* 2651 */ "glFramebufferFoveationConfigQCOM",
    /* 2652 */ "glFramebufferFoveationParametersQCOM",
    /* 2653 */ "glFramebufferMemorylessPixelLocalStorageANGLE",
    /* 2654 */ "glFramebufferPixelLocalClearValuefvANGLE",
    /* 2655 */ "glFramebufferPixelLocalClearValueivANGLE",
    /* 2656 */ "glFramebufferPixelLocalClearValueuivANGLE",
    /* 2657 */ "glFramebufferPixelLocalStorageInterruptANGLE",
    /* 2658 */ "glFramebufferPixelLocalStorageRestoreANGLE",
    /* 2659 */ "glFramebufferPixelLocalStorageSizeEXT",
    /* 2660 */ "glFramebufferShadingRateEXT",
    /* 2661 */ "glFramebufferTexture2DDownsampleIMG",
    /* 2662 */ "glFramebufferTexture2DMultisampleEXT",
    /* 2663 */ "glFramebufferTexture2DMultisampleIMG",
    /* 2664 */ "glFramebufferTexture3DOES",
    /* 2665 */ "glFramebufferTextureLayerDownsampleIMG",
    /* 2666 */ "glFramebufferTextureMultisampleMultiviewOVR",
    /* 2667 */ "glFramebufferTextureOES",
    /* 2668 */ "glFramebufferTexturePixelLocalStorageANGLE",
    /* 2669 */ "glGenProgramPipelinesEXT",
    /* 2670 */ "glGenQueriesEXT",
    /* 2671 */ "glGenVertexArraysOES",
    /* 2672 */ "glGetActiveUniformBlockivRobustANGLE",
    /* 2673 */ "glGetBooleani_vRobustANGLE",
    /* 2674 */ "glGetBooleanvRobustANGLE",
    /* 2675 */ "glGetBufferParameteri64vRobustANGLE",
    /* 2676 */ "glGetBufferParameterivRobustANGLE",
    /* 2677 */ "glGetBufferPointervOES",
    /* 2678 */ "glGetBufferPointervRobustANGLE",
    /* 2679 */ "glGetCompressedTexImageANGLE",
    /* 2680 */ "glGetDebugMessageLogKHR",
    /* 2681 */ "glGetDriverControlStringQCOM",
    /* 2682 */ "glGetDriverControlsQCOM",
    /* 2683 */ "glGetFloati_vNV",
    /* 2684 */ "glGetFloati_vOES",
    /* 2685 */ "glGetFloatvRobustANGLE",
    /* 2686 */ "glGetFragDataIndexEXT",
    /* 2687 */ "glGetFragmentShadingRatesEXT",
    /* 2688 */ "glGetFramebufferAttachmentParameterivRobustANGLE",
    /* 2689 */ "glGetFramebufferParameterivRobustANGLE",
    /* 2690 */ "glGetFramebufferPixelLocalStorageParameterfvANGLE",
    /* 2691 */ "glGetFramebufferPixelLocalStorageParameterfvRobustANGLE",
    /* 2692 */ "glGetFramebufferPixelLocalStorageParameterivANGLE",
    /* 2693 */ "glGetFramebufferPixelLocalStorageParameterivRobustANGLE",
    /* 2694 */ "glGetFramebufferPixelLocalStorageSizeEXT",
    /* 2695 */ "glGetGraphicsResetStatusEXT",
    /* 2696 */ "glGetGraphicsResetStatusKHR",
    /* 2697 */ "glGetInteger64i_vRobustANGLE",
    /* 2698 */ "glGetInteger64vAPPLE",
    /* 2699 */ "glGetInteger64vEXT",
    /* 2700 */ "glGetInteger64vRobustANGLE",
    /* 2701 */ "glGetIntegeri_vEXT",
    /* 2702 */ "glGetIntegeri_vRobustANGLE",
    /* 2703 */ "glGetIntegervRobustANGLE",
    /* 2704 */ "glGetInternalformativRobustANGLE",
    /* 2705 */ "glGetMultisamplefvANGLE",
    /* 2706 */ "glGetMultisamplefvRobustANGLE",
    /* 2707 */ "glGetObjectLabelKHR",
    /* 2708 */ "glGetObjectPtrLabelKHR",
    /* 2709 */ "glGetPointervKHR",
    /* 2710 */ "glGetPointervRobustANGLERobustANGLE",
    /* 2711 */ "glGetProgramBinaryOES",
    /* 2712 */ "glGetProgramInterfaceivRobustANGLE",
    /* 2713 */ "glGetProgramPipelineInfoLogEXT",
    /* 2714 */ "glGetProgramPipelineivEXT",
    /* 2715 */ "glGetProgramResourceLocationIndexEXT",
    /* 2716 */ "glGetProgramivRobustANGLE",
    /* 2717 */ "glGetQueryObjecti64vRobustANGLE",
    /* 2718 */ "glGetQueryObjectivEXT",
    /* 2719 */ "glGetQueryObjectivRobustANGLE",
    /* 2720 */ "glGetQueryObjectui64vRobustANGLE",
    /* 2721 */ "glGetQueryObjectuivEXT",
    /* 2722 */ "glGetQueryObjectuivRobustANGLE",
    /* 2723 */ "glGetQueryivEXT",
    /* 2724 */ "glGetQueryivRobustANGLE",
    /* 2725 */ "glGetRenderbufferImageANGLE",
    /* 2726 */ "glGetRenderbufferParameterivRobustANGLE",
    /* 2727 */ "glGetSamplerParameterIivEXT",
    /* 2728 */ "glGetSamplerParameterIivOES",
    /* 2729 */ "glGetSamplerParameterIivRobustANGLE",
    /* 2730 */ "glGetSamplerParameterIuivEXT",
    /* 2731 */ "glGetSamplerParameterIuivOES",
    /* 2732 */ "glGetSamplerParameterIuivRobustANGLE",
    /* 2733 */ "glGetSamplerParameterfvRobustANGLE",
    /* 2734 */ "glGetSamplerParameterivRobustANGLE",
    /* 2735 */ "glGetShaderivRobustANGLE",
    /* 2736 */ "glGetSyncivAPPLE",
    /* 2737 */ "glGetTexImageANGLE",
    /* 2738 */ "glGetTexLevelParameterfvANGLE",
    /* 2739 */ "glGetTexLevelParameterfvRobustANGLE",
    /* 2740 */ "glGetTexLevelParameterivANGLE",
    /* 2741 */ "glGetTexLevelParameterivRobustANGLE",
    /* 2742 */ "glGetTexParameterIivOES",
    /* 2743 */ "glGetTexParameterIivRobustANGLE",
    /* 2744 */ "glGetTexParameterIuivOES",
    /* 2745 */ "glGetTexParameterIuivRobustANGLE",
    /* 2746 */ "glGetTexParameterfvRobustANGLE",
    /* 2747 */ "glGetTexParameterivRobustANGLE",
    /* 2748 */ "glGetTextureHandleIMG",
    /* 2749 */ "glGetTextureSamplerHandleIMG",
    /* 2750 */ "glGetTranslatedShaderSourceANGLE",
    /* 2751 */ "glGetUniformfvRobustANGLE",
    /* 2752 */ "glGetUniformivRobustANGLE",
    /* 2753 */ "glGetUniformuivRobustANGLE",
    /* 2754 */ "glGetVertexAttribIivRobustANGLE",
    /* 2755 */ "glGetVertexAttribIuivRobustANGLE",
    /* 2756 */ "glGetVertexAttribPointervRobustANGLE",
    /* 2757 */ "glGetVertexAttribfvRobustANGLE",
    /* 2758 */ "glGetVertexAttribivRobustANGLE",
    /* 2759 */ "glGetnUniformfvEXT",
    /* 2760 */ "glGetnUniformfvKHR",
    /* 2761 */ "glGetnUniformfvRobustANGLE",
    /* 2762 */ "glGetnUniformivEXT",
    /* 2763 */ "glGetnUniformivKHR",
    /* 2764 */ "glGetnUniformivRobustANGLE",
    /* 2765 */ "glGetnUniformuivKHR",
    /* 2766 */ "glGetnUniformuivRobustANGLE",
    /* 2767 */ "glIsEnablediEXT",
    /* 2768 */ "glIsEnablediNV",
    /* 2769 */ "glIsEnablediOES",
    /* 2770 */ "glIsProgramPipelineEXT",
    /* 2771 */ "glIsQueryEXT",
    /* 2772 */ "glIsSyncAPPLE",
    /* 2773 */ "glIsVertexArrayOES",
    /* 2774 */ "glLatencyMarkerANGLE",
    /* 2775 */ "glLogicOpANGLE",
    /* 2776 */ "glLoseContextCHROMIUM",
    /* 2777 */ "glLowLatencyModeANGLE",
    /* 2778 */ "glLowLatencyWaitANGLE",
    /* 2779 */ "glMapBufferOES",
    /* 2780 */ "glMapBufferRangeEXT",
    /* 2781 */ "glMaxActiveShaderCoresARM",
    /* 2782 */ "glMinSampleShadingOES",
    /* 2783 */ "glMultiDrawArraysANGLE",
    /* 2784 */ "glMultiDrawArraysIndirectEXT",
    /* 2785 */ "glMultiDrawArraysInstancedANGLE",
    /* 2786 */ "glMultiDrawArraysInstancedBaseInstanceANGLE",
    /* 2787 */ "glMultiDrawElementsANGLE",
    /* 2788 */ "glMultiDrawElementsBaseVertexEXT",
    /* 2789 */ "glMultiDrawElementsIndirectEXT",
    /* 2790 */ "glMultiDrawElementsInstancedANGLE",
    /* 2791 */ "glMultiDrawElementsInstancedBaseVertexBaseInstanceANGLE",
    /* 2792 */ "glObjectLabelKHR",
    /* 2793 */ "glObjectPtrLabelKHR",
    /* 2794 */ "glPatchParameteriEXT",
    /* 2795 */ "glPatchParameteriOES",
    /* 2796 */ "glPixelLocalStorageBarrierANGLE",
    /* 2797 */ "glPolygonModeANGLE",
    /* 2798 */ "glPolygonModeNV",
    /* 2799 */ "glPopDebugGroupKHR",
    /* 2800 */ "glPrimitiveBoundingBox",
    /* 2801 */ "glPrimitiveBoundingBoxEXT",
    /* 2802 */ "glPrimitiveBoundingBoxOES",
    /* 2803 */ "glProgramBinaryOES",
    /* 2804 */ "glProgramUniformHandleui64IMG",
    /* 2805 */ "glProgramUniformHandleui64vIMG",
    /* 2806 */ "glProvokingVertexANGLE",
    /* 2807 */ "glPushDebugGroupKHR",
    /* 2808 */ "glQueryCounterEXT",
    /* 2809 */ "glReadBufferIndexedEXT",
    /* 2810 */ "glReadBufferNV",
    /* 2811 */ "glReadPixelsRobustANGLE",
    /* 2812 */ "glReadnPixelsEXT",
    /* 2813 */ "glReadnPixelsKHR",
    /* 2814 */ "glReadnPixelsRobustANGLE",
    /* 2815 */ "glReleaseTexturesANGLE",
    /* 2816 */ "glRenderbufferStorageMultisampleANGLE",
    /* 2817 */ "glRenderbufferStorageMultisampleAPPLE",
    /* 2818 */ "glRenderbufferStorageMultisampleIMG",
    /* 2819 */ "glRenderbufferStorageMultisampleNV",
    /* 2820 */ "glRequestExtensionANGLE",
    /* 2821 */ "glResolveMultisampleFramebufferAPPLE",
    /* 2822 */ "glSampleMaskiANGLE",
    /* 2823 */ "glSamplerParameterIivEXT",
    /* 2824 */ "glSamplerParameterIivOES",
    /* 2825 */ "glSamplerParameterIivRobustANGLE",
    /* 2826 */ "glSamplerParameterIuivEXT",
    /* 2827 */ "glSamplerParameterIuivOES",
    /* 2828 */ "glSamplerParameterIuivRobustANGLE",
    /* 2829 */ "glSamplerParameterfvRobustANGLE",
    /* 2830 */ "glSamplerParameterivRobustANGLE",
    /* 2831 */ "glScissorArrayvNV",
    /* 2832 */ "glScissorArrayvOES",
    /* 2833 */ "glScissorIndexedNV",
    /* 2834 */ "glScissorIndexedOES",
    /* 2835 */ "glScissorIndexedvNV",
    /* 2836 */ "glScissorIndexedvOES",
    /* 2837 */ "glShadingRateCombinerOpsEXT",
    /* 2838 */ "glShadingRateEXT",
    /* 2839 */ "glShadingRateQCOM",
    /* 2840 */ "glStartTilingQCOM",
    /* 2841 */ "glTexBufferOES",
    /* 2842 */ "glTexBufferRangeEXT",
    /* 2843 */ "glTexBufferRangeOES",
    /* 2844 */ "glTexEstimateMotionQCOM",
    /* 2845 */ "glTexEstimateMotionRegionsQCOM",
    /* 2846 */ "glTexImage2DRobustANGLE",
    /* 2847 */ "glTexImage3DOES",
    /* 2848 */ "glTexImage3DRobustANGLE",
    /* 2849 */ "glTexPageCommitmentEXT",
    /* 2850 */ "glTexParameterIivOES",
    /* 2851 */ "glTexParameterIivRobustANGLE",
    /* 2852 */ "glTexParameterIuivOES",
    /* 2853 */ "glTexParameterIuivRobustANGLE",
    /* 2854 */ "glTexParameterfvRobustANGLE",
    /* 2855 */ "glTexParameterivRobustANGLE",
    /* 2856 */ "glTexStorage2DMultisampleANGLE",
    /* 2857 */ "glTexStorage3DMultisampleOES",
    /* 2858 */ "glTexStorageAttribs2DEXT",
    /* 2859 */ "glTexStorageAttribs3DEXT",
    /* 2860 */ "glTexSubImage2DRobustANGLE",
    /* 2861 */ "glTexSubImage3DOES",
    /* 2862 */ "glTexSubImage3DRobustANGLE",
    /* 2863 */ "glTextureFoveationParametersQCOM",
    /* 2864 */ "glTextureViewEXT",
    /* 2865 */ "glTextureViewOES",
    /* 2866 */ "glUniformHandleui64IMG",
    /* 2867 */ "glUniformHandleui64vIMG",
    /* 2868 */ "glUniformMatrix2x3fvNV",
    /* 2869 */ "glUniformMatrix2x4fvNV",
    /* 2870 */ "glUniformMatrix3x2fvNV",
    /* 2871 */ "glUniformMatrix3x4fvNV",
    /* 2872 */ "glUniformMatrix4x2fvNV",
    /* 2873 */ "glUniformMatrix4x3fvNV",
    /* 2874 */ "glUnmapBufferOES",
    /* 2875 */ "glUseProgramStagesEXT",
    /* 2876 */ "glValidateProgramPipelineEXT",
    /* 2877 */ "glVertexAttribDivisorANGLE",
    /* 2878 */ "glVertexAttribDivisorEXT",
    /* 2879 */ "glVertexAttribDivisorNV",
    /* 2880 */ "glViewportArrayvNV",
    /* 2881 */ "glViewportArrayvOES",
    /* 2882 */ "glViewportIndexedfNV",
    /* 2883 */ "glViewportIndexedfOES",
    /* 2884 */ "glViewportIndexedfvNV",
    /* 2885 */ "glViewportIndexedfvOES",
    /* 2886 */ "glWaitSyncAPPLE"
};

static uint64_t GLAD_GL_ext_hashes[] = {
    /*    0 */ 0xa3f15a4859642e24, /* GL_3DFX_multisample */
    /*    1 */ 0x4cf5d1995a66a5fe, /* GL_3DFX_tbuffer */
    /*    2 */ 0x389939b5cbd91a14, /* GL_3DFX_texture_compression_FXT1 */
    /*    3 */ 0xbf938a3109ec723d, /* GL_AMD_blend_minmax_factor */
    /*    4 */ 0xfbca194ce346f79d, /* GL_AMD_compressed_3DC_texture */
    /*    5 */ 0xb60a0647d19ecd25, /* GL_AMD_compressed_ATC_texture */
    /*    6 */ 0x3a0fcb022a0e918a, /* GL_AMD_conservative_depth */
    /*    7 */ 0x2bbc0581a1b2b142, /* GL_AMD_debug_output */
    /*    8 */ 0x8528a16a1fdb6d51, /* GL_AMD_depth_clamp_separate */
    /*    9 */ 0x746cf03f26c4858a, /* GL_AMD_draw_buffers_blend */
    /*   10 */ 0xfaa176d058525abf, /* GL_AMD_framebuffer_multisample_advanced */
    /*   11 */ 0xb81865d628d4822e, /* GL_AMD_framebuffer_sample_positions */
    /*   12 */ 0x54b9b5e1e15805ff, /* GL_AMD_gcn_shader */
    /*   13 */ 0xf2b3ada35ec86ece, /* GL_AMD_gpu_shader_half_float */
    /*   14 */ 0x58e280e4b7565424, /* GL_AMD_gpu_shader_int16 */
    /*   15 */ 0xa314f8e9473e8e89, /* GL_AMD_gpu_shader_int64 */
    /*   16 */ 0x601bad09d1d7fc1e, /* GL_AMD_interleaved_elements */
    /*   17 */ 0x173d9b4be210ea12, /* GL_AMD_multi_draw_indirect */
    /*   18 */ 0x3e05101dd76b1e5c, /* GL_AMD_name_gen_delete */
    /*   19 */ 0xd587d820af131b88, /* GL_AMD_occlusion_query_event */
    /*   20 */ 0xf677c0636b66a6a3, /* GL_AMD_performance_monitor */
    /*   21 */ 0xb735d6755296c48c, /* GL_AMD_pinned_memory */
    /*   22 */ 0xb965a8b418ce69c6, /* GL_AMD_program_binary_Z400 */
    /*   23 */ 0xb3185e56ea54b6fd, /* GL_AMD_query_buffer_object */
    /*   24 */ 0x5b0c6a562ce2569d, /* GL_AMD_sample_positions */
    /*   25 */ 0x3ff7cc5aa13067f5, /* GL_AMD_seamless_cubemap_per_texture */
    /*   26 */ 0x49e444d707242c80, /* GL_AMD_shader_atomic_counter_ops */
    /*   27 */ 0xf504ee512dc7b00c, /* GL_AMD_shader_ballot */
    /*   28 */ 0xcd0e9d8a9f876dd2, /* GL_AMD_shader_explicit_vertex_parameter */
    /*   29 */ 0xdcf2ddfe44d1fe83, /* GL_AMD_shader_fragment_mask */
    /*   30 */ 0x336dfdc747f76e82, /* GL_AMD_shader_gpu_shader_half_float_fetch */
    /*   31 */ 0x96b07741ca00233d, /* GL_AMD_shader_image_load_store_lod */
    /*   32 */ 0xc126db7d83e09283, /* GL_AMD_shader_stencil_export */
    /*   33 */ 0x177b92b7cd669d32, /* GL_AMD_shader_trinary_minmax */
    /*   34 */ 0x68c5d21c9c5abe68, /* GL_AMD_sparse_texture */
    /*   35 */ 0xd7a31898c597c5c3, /* GL_AMD_stencil_operation_extended */
    /*   36 */ 0xb50e97696e955bbe, /* GL_AMD_texture_gather_bias_lod */
    /*   37 */ 0x013afe81eb3c2e0a, /* GL_AMD_texture_texture4 */
    /*   38 */ 0x4c4606ee62053585, /* GL_AMD_transform_feedback3_lines_triangles */
    /*   39 */ 0x164bc52d21b26a0d, /* GL_AMD_transform_feedback4 */
    /*   40 */ 0x34b4364b37b53b68, /* GL_AMD_vertex_shader_layer */
    /*   41 */ 0xfcd565a5b4211b86, /* GL_AMD_vertex_shader_tessellator */
    /*   42 */ 0xcff6900b34a57200, /* GL_AMD_vertex_shader_viewport_index */
    /*   43 */ 0xc41066419a80a1a5, /* GL_ANDROID_extension_pack_es31a */
    /*   44 */ 0x269b1b3d43f0044b, /* GL_ANGLE_base_vertex_base_instance */
    /*   45 */ 0x482ab3c6619af337, /* GL_ANGLE_client_arrays */
    /*   46 */ 0x41739af4618fe843, /* GL_ANGLE_clip_cull_distance */
    /*   47 */ 0xa1378a5ab6903c05, /* GL_ANGLE_copy_texture_3d */
    /*   48 */ 0xaa8f55d75eb1ea08, /* GL_ANGLE_depth_texture */
    /*   49 */ 0xeb72d824895faa8c, /* GL_ANGLE_framebuffer_blit */
    /*   50 */ 0x45e7dae6cdab912b, /* GL_ANGLE_framebuffer_multisample */
    /*   51 */ 0x352e547dc4c723c9, /* GL_ANGLE_get_image */
    /*   52 */ 0x3b399821bf301295, /* GL_ANGLE_get_serialized_context_string */
    /*   53 */ 0xa8bc2a751596a8c9, /* GL_ANGLE_get_tex_level_parameter */
    /*   54 */ 0xf21d57ef70efa97f, /* GL_ANGLE_instanced_arrays */
    /*   55 */ 0x611ffec7970d55f4, /* GL_ANGLE_logic_op */
    /*   56 */ 0xce13622f2ae81cf6, /* GL_ANGLE_lossy_etc_decode */
    /*   57 */ 0x74d6aabd49ce7fe8, /* GL_ANGLE_low_latency */
    /*   58 */ 0xf1c5c3418f5bfbbc, /* GL_ANGLE_memory_object_flags */
    /*   59 */ 0x2655c424cb0e67d6, /* GL_ANGLE_memory_object_fuchsia */
    /*   60 */ 0x29c14753da729d8b, /* GL_ANGLE_memory_size */
    /*   61 */ 0x96c6dc8ae13a863f, /* GL_ANGLE_multi_draw */
    /*   62 */ 0x5648b6070cf43450, /* GL_ANGLE_pack_reverse_row_order */
    /*   63 */ 0xf830ca37ce4d57e9, /* GL_ANGLE_polygon_mode */
    /*   64 */ 0x7e99ccc7605afe66, /* GL_ANGLE_program_binary */
    /*   65 */ 0x66f0ab28691d8be7, /* GL_ANGLE_program_binary_readiness_query */
    /*   66 */ 0x75815242daf456c4, /* GL_ANGLE_program_cache_control */
    /*   67 */ 0x636fa9fe6b321bd4, /* GL_ANGLE_provoking_vertex */
    /*   68 */ 0xecb6507e3e1d02f8, /* GL_ANGLE_renderability_validation */
    /*   69 */ 0xe81bb93ca0cf6f2a, /* GL_ANGLE_request_extension */
    /*   70 */ 0x25833e2905e922d8, /* GL_ANGLE_rgbx_internal_format */
    /*   71 */ 0xe20f551fc33bd429, /* GL_ANGLE_robust_client_memory */
    /*   72 */ 0xf0b98d581ffeb5e0, /* GL_ANGLE_robust_fragment_shader_output */
    /*   73 */ 0x5d895fe77bc5a43f, /* GL_ANGLE_robust_resource_initialization */
    /*   74 */ 0xd4ba1c0aafe5b41f, /* GL_ANGLE_semaphore_fuchsia */
    /*   75 */ 0x2c1380c8a72e821a, /* GL_ANGLE_shader_binary */
    /*   76 */ 0x69a67f8bce5ed738, /* GL_ANGLE_shader_pixel_local_storage */
    /*   77 */ 0x1cdf91894ef6922d, /* GL_ANGLE_stencil_texturing */
    /*   78 */ 0xe4c777c3da15fb5d, /* GL_ANGLE_texture_compression_dxt1 */
    /*   79 */ 0x3ced8289e55b381f, /* GL_ANGLE_texture_compression_dxt3 */
    /*   80 */ 0xe031d89a47ab0e88, /* GL_ANGLE_texture_compression_dxt5 */
    /*   81 */ 0x261f90903ebb2b21, /* GL_ANGLE_texture_external_update */
    /*   82 */ 0xbae723a89da1bdfd, /* GL_ANGLE_texture_multisample */
    /*   83 */ 0x2164a76cb4716269, /* GL_ANGLE_texture_usage */
    /*   84 */ 0x210dd20de1d385d7, /* GL_ANGLE_translated_shader_source */
    /*   85 */ 0x186b1da5d851bbec, /* GL_ANGLE_vulkan_image */
    /*   86 */ 0xf870cb9d6ba30da8, /* GL_ANGLE_yuv_internal_format */
    /*   87 */ 0xedd8d13a9eab22a7, /* GL_APPLE_aux_depth_stencil */
    /*   88 */ 0x9cb930c662d0cbc5, /* GL_APPLE_client_storage */
    /*   89 */ 0xca00966a7d53874d, /* GL_APPLE_clip_distance */
    /*   90 */ 0x8b12f4834ed80365, /* GL_APPLE_color_buffer_packed_float */
    /*   91 */ 0x3b1ff61d2ca7ebef, /* GL_APPLE_copy_texture_levels */
    /*   92 */ 0x393954d6a157dc34, /* GL_APPLE_element_array */
    /*   93 */ 0x248c97fa0866c224, /* GL_APPLE_fence */
    /*   94 */ 0x4b598c5361e19ad0, /* GL_APPLE_float_pixels */
    /*   95 */ 0x90a2f67506c1c227, /* GL_APPLE_flush_buffer_range */
    /*   96 */ 0x349436461b4902f0, /* GL_APPLE_framebuffer_multisample */
    /*   97 */ 0x41f28225bfe72cb5, /* GL_APPLE_object_purgeable */
    /*   98 */ 0xc380c84097cc2eaa, /* GL_APPLE_rgb_422 */
    /*   99 */ 0x65041d91620fe255, /* GL_APPLE_row_bytes */
    /*  100 */ 0xe73b092a3adf8b6f, /* GL_APPLE_specular_vector */
    /*  101 */ 0x965df8be0c61c5ef, /* GL_APPLE_sync */
    /*  102 */ 0xd46cf8fd7182caf2, /* GL_APPLE_texture_format_BGRA8888 */
    /*  103 */ 0x45f22d7fbb944c1a, /* GL_APPLE_texture_max_level */
    /*  104 */ 0x9d3d6479810f97ac, /* GL_APPLE_texture_packed_float */
    /*  105 */ 0x9ab7d0b3c514d378, /* GL_APPLE_texture_range */
    /*  106 */ 0x5d3f53e18fb3ff55, /* GL_APPLE_transform_hint */
    /*  107 */ 0xb0874f6446afabce, /* GL_APPLE_vertex_array_object */
    /*  108 */ 0xd3da8f94dff875f1, /* GL_APPLE_vertex_array_range */
    /*  109 */ 0x9bf0cbe91e220c86, /* GL_APPLE_vertex_program_evaluators */
    /*  110 */ 0xe908f191198042d8, /* GL_APPLE_ycbcr_422 */
    /*  111 */ 0x1f6122983853ff45, /* GL_ARB_ES2_compatibility */
    /*  112 */ 0xa9d98ac21fcaf80b, /* GL_ARB_ES3_1_compatibility */
    /*  113 */ 0x8945b05fdf09b074, /* GL_ARB_ES3_2_compatibility */
    /*  114 */ 0xea26087e653cab2b, /* GL_ARB_ES3_compatibility */
    /*  115 */ 0x08410053810ead05, /* GL_ARB_arrays_of_arrays */
    /*  116 */ 0x40b475be6ab996bb, /* GL_ARB_base_instance */
    /*  117 */ 0xb2e0c01fbc4a0d90, /* GL_ARB_bindless_texture */
    /*  118 */ 0x98330877cd269847, /* GL_ARB_blend_func_extended */
    /*  119 */ 0x2aa09aeb0f69408b, /* GL_ARB_buffer_storage */
    /*  120 */ 0xf1d364213ef0dd70, /* GL_ARB_cl_event */
    /*  121 */ 0x68a226aab21d4c06, /* GL_ARB_clear_buffer_object */
    /*  122 */ 0xb9bb33941fa4b35f, /* GL_ARB_clear_texture */
    /*  123 */ 0x0062a8cb7bae8d41, /* GL_ARB_clip_control */
    /*  124 */ 0x9ab3cde2bbe8e41c, /* GL_ARB_color_buffer_float */
    /*  125 */ 0xe421f74d58d12f0f, /* GL_ARB_compatibility */
    /*  126 */ 0xfcfdeecd633ecd3f, /* GL_ARB_compressed_texture_pixel_storage */
    /*  127 */ 0xd9df667054f06223, /* GL_ARB_compute_shader */
    /*  128 */ 0xc49c40e9865275e6, /* GL_ARB_compute_variable_group_size */
    /*  129 */ 0x6bf8cd6035aef76c, /* GL_ARB_conditional_render_inverted */
    /*  130 */ 0xcc005319118f39bb, /* GL_ARB_conservative_depth */
    /*  131 */ 0x66bffd41bcf61546, /* GL_ARB_copy_buffer */
    /*  132 */ 0x66cd5d5964674061, /* GL_ARB_copy_image */
    /*  133 */ 0x59cf6e44c2fc962a, /* GL_ARB_cull_distance */
    /*  134 */ 0x2b16e3dcc2f78c79, /* GL_ARB_debug_output */
    /*  135 */ 0x3f93699d406e0f0e, /* GL_ARB_depth_buffer_float */
    /*  136 */ 0x53b30bc0d3be88f6, /* GL_ARB_depth_clamp */
    /*  137 */ 0xd0e68b1ed9117edf, /* GL_ARB_depth_texture */
    /*  138 */ 0x34fe88e233827c23, /* GL_ARB_derivative_control */
    /*  139 */ 0x8e24d5c3614e8aa2, /* GL_ARB_direct_state_access */
    /*  140 */ 0xe11ab2833ee38b1a, /* GL_ARB_draw_buffers */
    /*  141 */ 0xae64ff49ea7e95af, /* GL_ARB_draw_buffers_blend */
    /*  142 */ 0xe8f87e4358abe5ad, /* GL_ARB_draw_elements_base_vertex */
    /*  143 */ 0x115e5b64ca1e3904, /* GL_ARB_draw_indirect */
    /*  144 */ 0x1b97c8e7f6e23b1d, /* GL_ARB_draw_instanced */
    /*  145 */ 0x43e30679379342ce, /* GL_ARB_enhanced_layouts */
    /*  146 */ 0xae63483486dde7ca, /* GL_ARB_explicit_attrib_location */
    /*  147 */ 0x2024ab894c4d472e, /* GL_ARB_explicit_uniform_location */
    /*  148 */ 0x5f268b1f7c820480, /* GL_ARB_fragment_coord_conventions */
    /*  149 */ 0x737ecdaaf0007deb, /* GL_ARB_fragment_layer_viewport */
    /*  150 */ 0x73c41f19063c2fe6, /* GL_ARB_fragment_program */
    /*  151 */ 0xefae304da60b251d, /* GL_ARB_fragment_program_shadow */
    /*  152 */ 0x52146e3d84c4168c, /* GL_ARB_fragment_shader */
    /*  153 */ 0x0c70408f81c04928, /* GL_ARB_fragment_shader_interlock */
    /*  154 */ 0x2448dc255a192f81, /* GL_ARB_framebuffer_no_attachments */
    /*  155 */ 0x1fbce4d5ca5a1f15, /* GL_ARB_framebuffer_object */
    /*  156 */ 0x7423a1c932459cca, /* GL_ARB_framebuffer_sRGB */
    /*  157 */ 0xf680b4cebba73b4e, /* GL_ARB_geometry_shader4 */
    /*  158 */ 0xa3d697b5a581321a, /* GL_ARB_get_program_binary */
    /*  159 */ 0xeff63c42ef3b05e6, /* GL_ARB_get_texture_sub_image */
    /*  160 */ 0xea214db7cd5e19d1, /* GL_ARB_gl_spirv */
    /*  161 */ 0x2c7de1df96f6285a, /* GL_ARB_gpu_shader5 */
    /*  162 */ 0x19c411e568c50761, /* GL_ARB_gpu_shader_fp64 */
    /*  163 */ 0xbed2c39a8ee82e31, /* GL_ARB_gpu_shader_int64 */
    /*  164 */ 0x54e0f735df67d1a9, /* GL_ARB_half_float_pixel */
    /*  165 */ 0x49a053607b3fe223, /* GL_ARB_half_float_vertex */
    /*  166 */ 0x4569da13c0840fbe, /* GL_ARB_imaging */
    /*  167 */ 0x3b7fae1bd2e0c889, /* GL_ARB_indirect_parameters */
    /*  168 */ 0x3b10779fb6b7fcbb, /* GL_ARB_instanced_arrays */
    /*  169 */ 0xf96f1159070d5ce7, /* GL_ARB_internalformat_query */
    /*  170 */ 0x80a297f08b3101df, /* GL_ARB_internalformat_query2 */
    /*  171 */ 0x6a0e063354f3a32c, /* GL_ARB_invalidate_subdata */
    /*  172 */ 0x70a2bf7a3574e20f, /* GL_ARB_map_buffer_alignment */
    /*  173 */ 0xbf533265f999152c, /* GL_ARB_map_buffer_range */
    /*  174 */ 0xfbe76f26f72891f3, /* GL_ARB_matrix_palette */
    /*  175 */ 0xc2eb1cf0ae1fb90b, /* GL_ARB_multi_bind */
    /*  176 */ 0x05681bd649da4453, /* GL_ARB_multi_draw_indirect */
    /*  177 */ 0x494b5f42fc0a83e4, /* GL_ARB_multisample */
    /*  178 */ 0x4a56c37f2c0b7aad, /* GL_ARB_multitexture */
    /*  179 */ 0xe8818f3733977678, /* GL_ARB_occlusion_query */
    /*  180 */ 0x06e18ccc664317eb, /* GL_ARB_occlusion_query2 */
    /*  181 */ 0x5d7b0c48219844f4, /* GL_ARB_parallel_shader_compile */
    /*  182 */ 0x6399433cf89bb920, /* GL_ARB_pipeline_statistics_query */
    /*  183 */ 0xac3ec29ab5db4b9e, /* GL_ARB_pixel_buffer_object */
    /*  184 */ 0xffe8ee561ae2346c, /* GL_ARB_point_parameters */
    /*  185 */ 0xb48886ec024907bb, /* GL_ARB_point_sprite */
    /*  186 */ 0x0c2f051e773ac84a, /* GL_ARB_polygon_offset_clamp */
    /*  187 */ 0x94125022598b506e, /* GL_ARB_post_depth_coverage */
    /*  188 */ 0x680e7d29d6b97883, /* GL_ARB_program_interface_query */
    /*  189 */ 0x028da0039f30b414, /* GL_ARB_provoking_vertex */
    /*  190 */ 0x76c8a711474dcb0e, /* GL_ARB_query_buffer_object */
    /*  191 */ 0x4b042cda7a10234c, /* GL_ARB_robust_buffer_access_behavior */
    /*  192 */ 0x321298a6a261de34, /* GL_ARB_robustness */
    /*  193 */ 0x945bce717134d350, /* GL_ARB_robustness_isolation */
    /*  194 */ 0x94596e17ac6ec3c8, /* GL_ARB_sample_locations */
    /*  195 */ 0x7870651576fc1ccd, /* GL_ARB_sample_shading */
    /*  196 */ 0x1db0e3c87246c7f7, /* GL_ARB_sampler_objects */
    /*  197 */ 0x6d414fea6b2a0b05, /* GL_ARB_seamless_cube_map */
    /*  198 */ 0xbe6ffda1c253ce69, /* GL_ARB_seamless_cubemap_per_texture */
    /*  199 */ 0xf39b353f6c8d6795, /* GL_ARB_separate_shader_objects */
    /*  200 */ 0x2c6b3e0ac4318eac, /* GL_ARB_shader_atomic_counter_ops */
    /*  201 */ 0x4d13222ef8dc85a8, /* GL_ARB_shader_atomic_counters */
    /*  202 */ 0xb7f68cebd72707b2, /* GL_ARB_shader_ballot */
    /*  203 */ 0x6157ef1dc9a5ec6a, /* GL_ARB_shader_bit_encoding */
    /*  204 */ 0x604fb19fc38ead7b, /* GL_ARB_shader_clock */
    /*  205 */ 0x44796ed6cecb76dd, /* GL_ARB_shader_draw_parameters */
    /*  206 */ 0x24f42ed6fd7e1224, /* GL_ARB_shader_group_vote */
    /*  207 */ 0x8e1d8ffee2ffc980, /* GL_ARB_shader_image_load_store */
    /*  208 */ 0x3c986ee0af879682, /* GL_ARB_shader_image_size */
    /*  209 */ 0xd8de76a336031ff0, /* GL_ARB_shader_objects */
    /*  210 */ 0x06bce3aace8af5a7, /* GL_ARB_shader_precision */
    /*  211 */ 0x10bfd775e284ac36, /* GL_ARB_shader_stencil_export */
    /*  212 */ 0x191e16f9c16a5423, /* GL_ARB_shader_storage_buffer_object */
    /*  213 */ 0x9f832fb5b2517157, /* GL_ARB_shader_subroutine */
    /*  214 */ 0xa53df22a8387d8c0, /* GL_ARB_shader_texture_image_samples */
    /*  215 */ 0xfd460b3ffea5238e, /* GL_ARB_shader_texture_lod */
    /*  216 */ 0x3b0ccc78e1ae6cce, /* GL_ARB_shader_viewport_layer_array */
    /*  217 */ 0xf2d5eb1652b5c218, /* GL_ARB_shading_language_100 */
    /*  218 */ 0x566b1b0b87fe805d, /* GL_ARB_shading_language_420pack */
    /*  219 */ 0x2f59115a058a0c1a, /* GL_ARB_shading_language_include */
    /*  220 */ 0x6c8387915ce0e735, /* GL_ARB_shading_language_packing */
    /*  221 */ 0xd6597e1597f4f3cf, /* GL_ARB_shadow */
    /*  222 */ 0xecdc51a7a12e0820, /* GL_ARB_shadow_ambient */
    /*  223 */ 0xcc6098f61c4e626a, /* GL_ARB_sparse_buffer */
    /*  224 */ 0xb8b8ba783156beb9, /* GL_ARB_sparse_texture */
    /*  225 */ 0xa11019635b421922, /* GL_ARB_sparse_texture2 */
    /*  226 */ 0x7dc85bdb35fadb35, /* GL_ARB_sparse_texture_clamp */
    /*  227 */ 0xcf62e2741dd9a807, /* GL_ARB_spirv_extensions */
    /*  228 */ 0xa56221685de2b254, /* GL_ARB_stencil_texturing */
    /*  229 */ 0x0d3c113e7ffc3be4, /* GL_ARB_sync */
    /*  230 */ 0xaefddf2f9dcfa46a, /* GL_ARB_tessellation_shader */
    /*  231 */ 0x9d0747678a9d3fdf, /* GL_ARB_texture_barrier */
    /*  232 */ 0xb4a8554df00d4ede, /* GL_ARB_texture_border_clamp */
    /*  233 */ 0xc59d9bef1f9b2de9, /* GL_ARB_texture_buffer_object */
    /*  234 */ 0xbab79763204b079a, /* GL_ARB_texture_buffer_object_rgb32 */
    /*  235 */ 0x843bbbf9107595d8, /* GL_ARB_texture_buffer_range */
    /*  236 */ 0x582477dc03c7221c, /* GL_ARB_texture_compression */
    /*  237 */ 0x83bfab2872b14819, /* GL_ARB_texture_compression_bptc */
    /*  238 */ 0x5e62ceda4eb9b901, /* GL_ARB_texture_compression_rgtc */
    /*  239 */ 0xac7bb6c963c7dd4c, /* GL_ARB_texture_cube_map */
    /*  240 */ 0x68d233a2df517789, /* GL_ARB_texture_cube_map_array */
    /*  241 */ 0x9061271ef3971e4d, /* GL_ARB_texture_env_add */
    /*  242 */ 0x729ad094490ac067, /* GL_ARB_texture_env_combine */
    /*  243 */ 0xc258a95e80a7ac1d, /* GL_ARB_texture_env_crossbar */
    /*  244 */ 0x87e8597c801caffb, /* GL_ARB_texture_env_dot3 */
    /*  245 */ 0xf8867e9b2392c62c, /* GL_ARB_texture_filter_anisotropic */
    /*  246 */ 0x9a2662f4f2a023fc, /* GL_ARB_texture_filter_minmax */
    /*  247 */ 0x6f4b69f418935051, /* GL_ARB_texture_float */
    /*  248 */ 0xa57e1ab78c203089, /* GL_ARB_texture_gather */
    /*  249 */ 0x7c5b8fd73b8f1d2a, /* GL_ARB_texture_mirror_clamp_to_edge */
    /*  250 */ 0x7f8109dad2ae72ac, /* GL_ARB_texture_mirrored_repeat */
    /*  251 */ 0xce2742707049542e, /* GL_ARB_texture_multisample */
    /*  252 */ 0x39526d131df64c59, /* GL_ARB_texture_non_power_of_two */
    /*  253 */ 0x46b457622b5dab21, /* GL_ARB_texture_query_levels */
    /*  254 */ 0x0c5b6193b98fc63b, /* GL_ARB_texture_query_lod */
    /*  255 */ 0x5d6d6585c47fc200, /* GL_ARB_texture_rectangle */
    /*  256 */ 0xb7acf24a6eb5a7f4, /* GL_ARB_texture_rg */
    /*  257 */ 0x97b3807033cf6f62, /* GL_ARB_texture_rgb10_a2ui */
    /*  258 */ 0x12a12b44ee899f08, /* GL_ARB_texture_stencil8 */
    /*  259 */ 0x2bb0e7be62c590f8, /* GL_ARB_texture_storage */
    /*  260 */ 0xeacfe755a96db7a7, /* GL_ARB_texture_storage_multisample */
    /*  261 */ 0x421bedbb68fd4661, /* GL_ARB_texture_swizzle */
    /*  262 */ 0x5b877369a37b65e6, /* GL_ARB_texture_view */
    /*  263 */ 0x0d8a574b96669a1b, /* GL_ARB_timer_query */
    /*  264 */ 0xeaa1709ae2b12764, /* GL_ARB_transform_feedback2 */
    /*  265 */ 0xfbc74ea814b15d2f, /* GL_ARB_transform_feedback3 */
    /*  266 */ 0x3f96154fd49046f3, /* GL_ARB_transform_feedback_instanced */
    /*  267 */ 0xf54fc92b7e8ec635, /* GL_ARB_transform_feedback_overflow_query */
    /*  268 */ 0x77013d69fddefe87, /* GL_ARB_transpose_matrix */
    /*  269 */ 0x7f397ae5fad4b735, /* GL_ARB_uniform_buffer_object */
    /*  270 */ 0x502a9d2c5469c136, /* GL_ARB_vertex_array_bgra */
    /*  271 */ 0x1a1e2d3306313eb9, /* GL_ARB_vertex_array_object */
    /*  272 */ 0x7b47ed54530d0661, /* GL_ARB_vertex_attrib_64bit */
    /*  273 */ 0xe394a5028a00c565, /* GL_ARB_vertex_attrib_binding */
    /*  274 */ 0xbe2f3323a7af4844, /* GL_ARB_vertex_blend */
    /*  275 */ 0xab4f226cf8bf14b2, /* GL_ARB_vertex_buffer_object */
    /*  276 */ 0x2b91406e8801f26d, /* GL_ARB_vertex_program */
    /*  277 */ 0xb74f5593e3c89e02, /* GL_ARB_vertex_shader */
    /*  278 */ 0x5adbfa9b8494c869, /* GL_ARB_vertex_type_10f_11f_11f_rev */
    /*  279 */ 0x70aa23c3893ff4f7, /* GL_ARB_vertex_type_2_10_10_10_rev */
    /*  280 */ 0x11f657f3da3dbeb7, /* GL_ARB_viewport_array */
    /*  281 */ 0x8fd0fb55626075a1, /* GL_ARB_window_pos */
    /*  282 */ 0x2fbeb7cb81220b5e, /* GL_ARM_mali_program_binary */
    /*  283 */ 0x174de60965d38c78, /* GL_ARM_mali_shader_binary */
    /*  284 */ 0x0770bcbef6d87ecc, /* GL_ARM_rgba8 */
    /*  285 */ 0xc97fd975c7c94d78, /* GL_ARM_shader_core_builtins */
    /*  286 */ 0xd022cfc81a420445, /* GL_ARM_shader_core_properties */
    /*  287 */ 0xf0d2f4cff333f04e, /* GL_ARM_shader_framebuffer_fetch */
    /*  288 */ 0xbfa10a2d7557623f, /* GL_ARM_shader_framebuffer_fetch_depth_stencil */
    /*  289 */ 0x8a7a1adbc8af57ff, /* GL_ARM_texture_unnormalized_coordinates */
    /*  290 */ 0xc43e90f15fb8db01, /* GL_ATI_draw_buffers */
    /*  291 */ 0x237ddecca4711d26, /* GL_ATI_element_array */
    /*  292 */ 0x8465366774288b57, /* GL_ATI_envmap_bumpmap */
    /*  293 */ 0x7eace62f803a3a1d, /* GL_ATI_fragment_shader */
    /*  294 */ 0x601618adc78f06ed, /* GL_ATI_map_object_buffer */
    /*  295 */ 0xc2367d65629265d3, /* GL_ATI_meminfo */
    /*  296 */ 0x3ed6aa98977b6026, /* GL_ATI_pixel_format_float */
    /*  297 */ 0xecc62354179a5498, /* GL_ATI_pn_triangles */
    /*  298 */ 0xc9e128c539750596, /* GL_ATI_separate_stencil */
    /*  299 */ 0xf8002b1602911364, /* GL_ATI_text_fragment_shader */
    /*  300 */ 0x8f696d877000fa6a, /* GL_ATI_texture_env_combine3 */
    /*  301 */ 0x72137067e0c140bc, /* GL_ATI_texture_float */
    /*  302 */ 0x184114955f32fded, /* GL_ATI_texture_mirror_once */
    /*  303 */ 0x99180d4f8d9c5d52, /* GL_ATI_vertex_array_object */
    /*  304 */ 0x4bedffd7142a0313, /* GL_ATI_vertex_attrib_array_object */
    /*  305 */ 0xf2a1201512faef81, /* GL_ATI_vertex_streams */
    /*  306 */ 0x9a85b4342c34b2f8, /* GL_CHROMIUM_bind_uniform_location */
    /*  307 */ 0x0dd808babc9daaab, /* GL_CHROMIUM_copy_compressed_texture */
    /*  308 */ 0xe6bdf6222c3733ef, /* GL_CHROMIUM_copy_texture */
    /*  309 */ 0x0bd5e31cc0c829e7, /* GL_CHROMIUM_framebuffer_mixed_samples */
    /*  310 */ 0x04af64470030272e, /* GL_CHROMIUM_lose_context */
    /*  311 */ 0x2b55ba018525895b, /* GL_DMP_program_binary */
    /*  312 */ 0x8e5f4ce24de544d5, /* GL_DMP_shader_binary */
    /*  313 */ 0x0cf95c40c08a43a8, /* GL_EXT_422_pixels */
    /*  314 */ 0x2a61d7b733e75c77, /* GL_EXT_EGL_image_array */
    /*  315 */ 0x35b7bb88d6ff4a1e, /* GL_EXT_EGL_image_storage */
    /*  316 */ 0xfe8066998f34da8e, /* GL_EXT_EGL_image_storage_compression */
    /*  317 */ 0xb8221664855c83bd, /* GL_EXT_EGL_sync */
    /*  318 */ 0x6fac3cb4234e6c59, /* GL_EXT_YUV_target */
    /*  319 */ 0xc118d96a66b6bea3, /* GL_EXT_abgr */
    /*  320 */ 0x6b5e9b6cfbdc3dc0, /* GL_EXT_base_instance */
    /*  321 */ 0x2c343f7622589325, /* GL_EXT_bgra */
    /*  322 */ 0x9d83c1e02304fb00, /* GL_EXT_bindable_uniform */
    /*  323 */ 0x1cafcd91efe0e1d6, /* GL_EXT_blend_color */
    /*  324 */ 0x3510ec477f22f7e7, /* GL_EXT_blend_equation_separate */
    /*  325 */ 0x888e740cefe39cc4, /* GL_EXT_blend_func_extended */
    /*  326 */ 0x97c1a7c0b569dfb8, /* GL_EXT_blend_func_separate */
    /*  327 */ 0x709f5d763ef0911f, /* GL_EXT_blend_logic_op */
    /*  328 */ 0x1163ab5d43e9b052, /* GL_EXT_blend_minmax */
    /*  329 */ 0x2c5c11d0c1161814, /* GL_EXT_blend_subtract */
    /*  330 */ 0x8a59c192ebd08825, /* GL_EXT_buffer_reference */
    /*  331 */ 0x1fe18a884a2d4d2a, /* GL_EXT_buffer_reference2 */
    /*  332 */ 0xb839402fc769c51e, /* GL_EXT_buffer_reference_uvec2 */
    /*  333 */ 0xf57e9c9fe9c776cd, /* GL_EXT_buffer_storage */
    /*  334 */ 0xaafb791a26428890, /* GL_EXT_clear_texture */
    /*  335 */ 0x9452d292aa14805e, /* GL_EXT_clip_control */
    /*  336 */ 0x5737e20452f91527, /* GL_EXT_clip_cull_distance */
    /*  337 */ 0x56a5c2f21e51bb5a, /* GL_EXT_clip_volume_hint */
    /*  338 */ 0x82b62c808e4abb64, /* GL_EXT_cmyka */
    /*  339 */ 0xa297c2c3a49a99be, /* GL_EXT_color_buffer_float */
    /*  340 */ 0xf9449646b78eab54, /* GL_EXT_color_buffer_half_float */
    /*  341 */ 0x6d76340b1318b839, /* GL_EXT_color_subtable */
    /*  342 */ 0xf1bda7fa0a83d383, /* GL_EXT_compiled_vertex_array */
    /*  343 */ 0x9ddf99bdc50f4149, /* GL_EXT_conservative_depth */
    /*  344 */ 0x354415fe7a6e013e, /* GL_EXT_control_flow_attributes */
    /*  345 */ 0x04f0f0ce501bd29d, /* GL_EXT_control_flow_attributes2 */
    /*  346 */ 0xe9260724f594f80b, /* GL_EXT_convolution */
    /*  347 */ 0xf9792a196e0ab7c9, /* GL_EXT_coordinate_frame */
    /*  348 */ 0xa26b121ae33c3436, /* GL_EXT_copy_image */
    /*  349 */ 0x2611c2618f21aa2f, /* GL_EXT_copy_texture */
    /*  350 */ 0xddfc92096368bfbb, /* GL_EXT_cull_vertex */
    /*  351 */ 0xed15a3d914865c56, /* GL_EXT_debug_label */
    /*  352 */ 0x84891a2031a0f162, /* GL_EXT_debug_marker */
    /*  353 */ 0x3d46dbc8319361c9, /* GL_EXT_debug_printf */
    /*  354 */ 0x2a423943f8be1307, /* GL_EXT_demote_to_helper_invocation */
    /*  355 */ 0xe21a2b607eb5c6bb, /* GL_EXT_depth_bounds_test */
    /*  356 */ 0xdc5fb3a8d43d753e, /* GL_EXT_depth_clamp */
    /*  357 */ 0xee026f0d1b48c324, /* GL_EXT_device_group */
    /*  358 */ 0xff4a74da40c62745, /* GL_EXT_direct_state_access */
    /*  359 */ 0x3287a129fb1e11c1, /* GL_EXT_discard_framebuffer */
    /*  360 */ 0x3d06b0f91612d10d, /* GL_EXT_disjoint_timer_query */
    /*  361 */ 0xd3ac9ca278a62f1a, /* GL_EXT_draw_buffers */
    /*  362 */ 0x5d6aa36dbdce372d, /* GL_EXT_draw_buffers2 */
    /*  363 */ 0x997893a6ac44f7fe, /* GL_EXT_draw_buffers_indexed */
    /*  364 */ 0x548657f15226635b, /* GL_EXT_draw_elements_base_vertex */
    /*  365 */ 0xeb1b622faf7697c7, /* GL_EXT_draw_instanced */
    /*  366 */ 0xbb5e6eb0e1559ef1, /* GL_EXT_draw_range_elements */
    /*  367 */ 0x0ccbfada83c13182, /* GL_EXT_draw_transform_feedback */
    /*  368 */ 0x5e1ad5852ce64f31, /* GL_EXT_external_buffer */
    /*  369 */ 0x18d7b8f80d477ce9, /* GL_EXT_float_blend */
    /*  370 */ 0xe09e32cd1ae79288, /* GL_EXT_fog_coord */
    /*  371 */ 0xc117232bce18d68e, /* GL_EXT_fragment_invocation_density */
    /*  372 */ 0x2f9b21678a5e0043, /* GL_EXT_fragment_shader_barycentric */
    /*  373 */ 0xde0a545f611c91b2, /* GL_EXT_fragment_shading_rate */
    /*  374 */ 0xdefc19d979b2e3e2, /* GL_EXT_framebuffer_blit */
    /*  375 */ 0x616048bcd1aa9223, /* GL_EXT_framebuffer_blit_layers */
    /*  376 */ 0x8cbb2537704d8953, /* GL_EXT_framebuffer_multisample */
    /*  377 */ 0x5634f30b2756d601, /* GL_EXT_framebuffer_multisample_blit_scaled */
    /*  378 */ 0x8350f19ac13e7c07, /* GL_EXT_framebuffer_object */
    /*  379 */ 0xa45a63878264c1e5, /* GL_EXT_framebuffer_sRGB */
    /*  380 */ 0x30d017755de50dd9, /* GL_EXT_geometry_point_size */
    /*  381 */ 0xfa22129bb4d04128, /* GL_EXT_geometry_shader */
    /*  382 */ 0x5370f0fbdd1b1f1d, /* GL_EXT_geometry_shader4 */
    /*  383 */ 0x3604f5b2b65016b2, /* GL_EXT_gpu_program_parameters */
    /*  384 */ 0x020c60828c37ce5d, /* GL_EXT_gpu_shader4 */
    /*  385 */ 0x53dbe9871073dca3, /* GL_EXT_gpu_shader5 */
    /*  386 */ 0xcebb9285fc482cfd, /* GL_EXT_histogram */
    /*  387 */ 0x64ea7e43377361ff, /* GL_EXT_index_array_formats */
    /*  388 */ 0xecf771ddabe3f8ed, /* GL_EXT_index_func */
    /*  389 */ 0x649623e695acbfb0, /* GL_EXT_index_material */
    /*  390 */ 0x43fd3f035960e92c, /* GL_EXT_index_texture */
    /*  391 */ 0x9c3c026caab1aaf7, /* GL_EXT_instanced_arrays */
    /*  392 */ 0x6b0a475df16ae9f2, /* GL_EXT_light_texture */
    /*  393 */ 0xf41152d50d03cc16, /* GL_EXT_map_buffer_range */
    /*  394 */ 0xdea398d907b668d0, /* GL_EXT_maximal_reconvergence */
    /*  395 */ 0xebb55934637c6ab7, /* GL_EXT_memory_object */
    /*  396 */ 0x7e941665b79d31c4, /* GL_EXT_memory_object_fd */
    /*  397 */ 0x6bf3a6b6ec24354b, /* GL_EXT_memory_object_win32 */
    /*  398 */ 0x67079bf943104541, /* GL_EXT_mesh_shader */
    /*  399 */ 0xda6fb882011aa28e, /* GL_EXT_misc_attribute */
    /*  400 */ 0x6077bed8aa109362, /* GL_EXT_multi_draw_arrays */
    /*  401 */ 0x55b4806b38f2b08e, /* GL_EXT_multi_draw_indirect */
    /*  402 */ 0x872a66595e5024ca, /* GL_EXT_multisample */
    /*  403 */ 0x3e4a3b0ff8584927, /* GL_EXT_multisampled_compatibility */
    /*  404 */ 0x33b89ab037aed106, /* GL_EXT_multisampled_render_to_texture */
    /*  405 */ 0x39f0379607d459f0, /* GL_EXT_multisampled_render_to_texture2 */
    /*  406 */ 0x49f63d58daabfccb, /* GL_EXT_multiview_draw_buffers */
    /*  407 */ 0x5b7a6a36ed0fe897, /* GL_EXT_multiview_tessellation_geometry_shader */
    /*  408 */ 0x3679a0ac14e16e97, /* GL_EXT_multiview_texture_multisample */
    /*  409 */ 0x39d0f3848228d38f, /* GL_EXT_multiview_timer_query */
    /*  410 */ 0x0d7bdf1d96e54238, /* GL_EXT_nonuniform_qualifier */
    /*  411 */ 0xff653ce0c16c5c81, /* GL_EXT_null_initializer */
    /*  412 */ 0xbf12db2b88c87ccf, /* GL_EXT_occlusion_query_boolean */
    /*  413 */ 0x927980c53f038149, /* GL_EXT_opacity_micromap */
    /*  414 */ 0x757af2451eae9d25, /* GL_EXT_packed_depth_stencil */
    /*  415 */ 0x2ace1d8656332b56, /* GL_EXT_packed_float */
    /*  416 */ 0x248d529c3993285c, /* GL_EXT_packed_pixels */
    /*  417 */ 0xecd5d2503b35bb13, /* GL_EXT_paletted_texture */
    /*  418 */ 0xc7f3ad7137661622, /* GL_EXT_pixel_buffer_object */
    /*  419 */ 0x59d7be95f9b27b9a, /* GL_EXT_pixel_transform */
    /*  420 */ 0xd7024b008ea1463b, /* GL_EXT_pixel_transform_color_table */
    /*  421 */ 0x14eaf45986c9bfa1, /* GL_EXT_point_parameters */
    /*  422 */ 0x5640aa3e3a0202cb, /* GL_EXT_polygon_offset */
    /*  423 */ 0xd55f7ac9bd1eba74, /* GL_EXT_polygon_offset_clamp */
    /*  424 */ 0x55695328ecdeb972, /* GL_EXT_post_depth_coverage */
    /*  425 */ 0x849565c10789238e, /* GL_EXT_primitive_bounding_box */
    /*  426 */ 0x638afa82b47ca539, /* GL_EXT_protected_textures */
    /*  427 */ 0xfc1cd6391217f09e, /* GL_EXT_provoking_vertex */
    /*  428 */ 0xc36c4a5ae294a717, /* GL_EXT_pvrtc_sRGB */
    /*  429 */ 0x864a43fa5616bb8c, /* GL_EXT_raster_multisample */
    /*  430 */ 0xb0b19c0e9f3b0f5c, /* GL_EXT_ray_cull_mask */
    /*  431 */ 0xd982b05f307f6fcd, /* GL_EXT_ray_flags_primitive_culling */
    /*  432 */ 0xbf4a58353f9a7a75, /* GL_EXT_ray_query */
    /*  433 */ 0x5d7ccf8ac93b7140, /* GL_EXT_ray_tracing */
    /*  434 */ 0x98b5a9c9f9d792dd, /* GL_EXT_ray_tracing_position_fetch */
    /*  435 */ 0x1b664521b8e7cedd, /* GL_EXT_read_format_bgra */
    /*  436 */ 0x461ed0af7d9ee57e, /* GL_EXT_render_snorm */
    /*  437 */ 0xc99a47326d03fd17, /* GL_EXT_rescale_normal */
    /*  438 */ 0x04aaf7c50fd23609, /* GL_EXT_robustness */
    /*  439 */ 0x72a714dfac11ff63, /* GL_EXT_sRGB */
    /*  440 */ 0xa329e9d07bf41faa, /* GL_EXT_sRGB_write_control */
    /*  441 */ 0x6c203c99634fa814, /* GL_EXT_samplerless_texture_functions */
    /*  442 */ 0xe045958c8c43c35f, /* GL_EXT_scalar_block_layout */
    /*  443 */ 0x5da9f01e568b2e0b, /* GL_EXT_secondary_color */
    /*  444 */ 0x40ea8dbcbb4d106f, /* GL_EXT_semaphore */
    /*  445 */ 0xb3de6f78cadcbed7, /* GL_EXT_semaphore_fd */
    /*  446 */ 0xd80cf52931619f45, /* GL_EXT_semaphore_win32 */
    /*  447 */ 0xde7c2e65ed21d1e7, /* GL_EXT_separate_depth_stencil */
    /*  448 */ 0xb207ff65f8bf495d, /* GL_EXT_separate_shader_objects */
    /*  449 */ 0xeb07329b2f67d2ec, /* GL_EXT_separate_specular_color */
    /*  450 */ 0x49d751ecfad21a12, /* GL_EXT_shader_16bit_storage */
    /*  451 */ 0x71c6281257d16bdf, /* GL_EXT_shader_atomic_float */
    /*  452 */ 0x3b6516e3dbabfb91, /* GL_EXT_shader_atomic_float2 */
    /*  453 */ 0x59bd13c26a6e0f68, /* GL_EXT_shader_atomic_int64 */
    /*  454 */ 0x6e599868ea3a939f, /* GL_EXT_shader_explicit_arithmetic_types */
    /*  455 */ 0x86da0f80c54cef33, /* GL_EXT_shader_framebuffer_fetch */
    /*  456 */ 0xcd3c990c9f8c0a64, /* GL_EXT_shader_framebuffer_fetch_non_coherent */
    /*  457 */ 0x17434ddfdf3a5893, /* GL_EXT_shader_group_vote */
    /*  458 */ 0xeab14f8fb076d3f3, /* GL_EXT_shader_image_int64 */
    /*  459 */ 0xc1de48ba5bbf7b01, /* GL_EXT_shader_image_load_formatted */
    /*  460 */ 0x6ab82341e3e65156, /* GL_EXT_shader_image_load_store */
    /*  461 */ 0xe19d3a68c60c0ef4, /* GL_EXT_shader_implicit_conversions */
    /*  462 */ 0x033287cccf9a6962, /* GL_EXT_shader_integer_mix */
    /*  463 */ 0xd055bdf912abe3b0, /* GL_EXT_shader_io_blocks */
    /*  464 */ 0x07975202b868bf83, /* GL_EXT_shader_non_constant_global_initializers */
    /*  465 */ 0x49f7e4529e189129, /* GL_EXT_shader_pixel_local_storage */
    /*  466 */ 0x28720bf0be8ab661, /* GL_EXT_shader_pixel_local_storage2 */
    /*  467 */ 0x28c00ec379a98b9d, /* GL_EXT_shader_realtime_clock */
    /*  468 */ 0x3ef958340d410019, /* GL_EXT_shader_samples_identical */
    /*  469 */ 0xa3a7633df81fa8b1, /* GL_EXT_shader_subgroup_extended_types */
    /*  470 */ 0x0fbf30e41210d727, /* GL_EXT_shader_texture_lod */
    /*  471 */ 0x0e7ba3c5e5be8403, /* GL_EXT_shader_tile_image */
    /*  472 */ 0xe504594d7646deb5, /* GL_EXT_shadow_funcs */
    /*  473 */ 0x7c7d332de021da36, /* GL_EXT_shadow_samplers */
    /*  474 */ 0x4851b197319900c7, /* GL_EXT_shared_memory_block */
    /*  475 */ 0xa39da1f69d0cad57, /* GL_EXT_shared_texture_palette */
    /*  476 */ 0x86ac1bf74755a73b, /* GL_EXT_sparse_texture */
    /*  477 */ 0x81ed537411dae865, /* GL_EXT_sparse_texture2 */
    /*  478 */ 0xe20fb1c3faf6f7d8, /* GL_EXT_stencil_clear_tag */
    /*  479 */ 0x629c334d67e5c718, /* GL_EXT_stencil_two_side */
    /*  480 */ 0x961b80206055e672, /* GL_EXT_stencil_wrap */
    /*  481 */ 0x8a56add0af10cbb6, /* GL_EXT_subgroup_uniform_control_flow */
    /*  482 */ 0xf85c8111e381b059, /* GL_EXT_subgroupuniform_qualifier */
    /*  483 */ 0xe101571ccdddbe44, /* GL_EXT_subtexture */
    /*  484 */ 0x80fb7149e30bd23a, /* GL_EXT_terminate_invocation */
    /*  485 */ 0x9e9a449841a4392b, /* GL_EXT_tessellation_point_size */
    /*  486 */ 0xa694e21c70c92ac7, /* GL_EXT_tessellation_shader */
    /*  487 */ 0x7893ebdfb50f10a6, /* GL_EXT_texture */
    /*  488 */ 0x3c1975837c97841b, /* GL_EXT_texture3D */
    /*  489 */ 0x2e4c3fc71fe20a24, /* GL_EXT_texture_array */
    /*  490 */ 0xf02848fc36653917, /* GL_EXT_texture_border_clamp */
    /*  491 */ 0x990b742e339cfdab, /* GL_EXT_texture_buffer */
    /*  492 */ 0xe30b1bf963964b94, /* GL_EXT_texture_buffer_object */
    /*  493 */ 0x7c8af8bc6e29a35b, /* GL_EXT_texture_compression_astc_decode_mode */
    /*  494 */ 0x8c12f4a29dd9872d, /* GL_EXT_texture_compression_bptc */
    /*  495 */ 0x42f4b0934de6c2dc, /* GL_EXT_texture_compression_dxt1 */
    /*  496 */ 0x789187ec36c3334e, /* GL_EXT_texture_compression_latc */
    /*  497 */ 0x6d7076425ffdf707, /* GL_EXT_texture_compression_rgtc */
    /*  498 */ 0x675e8f3271d1d5ca, /* GL_EXT_texture_compression_s3tc */
    /*  499 */ 0x747ed54119078205, /* GL_EXT_texture_compression_s3tc_srgb */
    /*  500 */ 0x511d1308a8dfc13f, /* GL_EXT_texture_cube_map */
    /*  501 */ 0x143e4c21a6ff53cc, /* GL_EXT_texture_cube_map_array */
    /*  502 */ 0xd7d84a9c353851fd, /* GL_EXT_texture_env_add */
    /*  503 */ 0x9d216b7a877bbcfb, /* GL_EXT_texture_env_combine */
    /*  504 */ 0x4bacf852b1cc1a43, /* GL_EXT_texture_env_dot3 */
    /*  505 */ 0xeafde92a9cccc4ed, /* GL_EXT_texture_filter_anisotropic */
    /*  506 */ 0x7738fa89f1d13a13, /* GL_EXT_texture_filter_minmax */
    /*  507 */ 0x39751dec512ae77c, /* GL_EXT_texture_format_BGRA8888 */
    /*  508 */ 0xeb53a2bedf43571d, /* GL_EXT_texture_format_sRGB_override */
    /*  509 */ 0xaf09c3ff42c89eb5, /* GL_EXT_texture_integer */
    /*  510 */ 0x41cf52695838c61c, /* GL_EXT_texture_lod_bias */
    /*  511 */ 0x17fb25156306ea61, /* GL_EXT_texture_mirror_clamp */
    /*  512 */ 0x9a5a807af7e26b3f, /* GL_EXT_texture_mirror_clamp_to_edge */
    /*  513 */ 0x94b22c00bec3e518, /* GL_EXT_texture_norm16 */
    /*  514 */ 0x10827f593acd1ba7, /* GL_EXT_texture_object */
    /*  515 */ 0x971e595b62f38066, /* GL_EXT_texture_perturb_normal */
    /*  516 */ 0x1e6eaad4a57ca1b5, /* GL_EXT_texture_query_lod */
    /*  517 */ 0x95f0b0bc421f25d3, /* GL_EXT_texture_rg */
    /*  518 */ 0xd43be8ff9c7c7ada, /* GL_EXT_texture_sRGB */
    /*  519 */ 0xfe62dc3d8ab9f10b, /* GL_EXT_texture_sRGB_R8 */
    /*  520 */ 0xcb6984e200d35ff9, /* GL_EXT_texture_sRGB_RG8 */
    /*  521 */ 0x2b44a8b2473d6e5f, /* GL_EXT_texture_sRGB_decode */
    /*  522 */ 0x127856e58a250c1b, /* GL_EXT_texture_shadow_lod */
    /*  523 */ 0x30a7dd27a9ac5760, /* GL_EXT_texture_shared_exponent */
    /*  524 */ 0xa2f8f4e45d997df3, /* GL_EXT_texture_snorm */
    /*  525 */ 0x154c4c8b80533dc0, /* GL_EXT_texture_storage */
    /*  526 */ 0x8768e67dadd2a7fd, /* GL_EXT_texture_storage_compression */
    /*  527 */ 0x183ae240682f4ad7, /* GL_EXT_texture_swizzle */
    /*  528 */ 0x4a802d8de71af8e9, /* GL_EXT_texture_type_2_10_10_10_REV */
    /*  529 */ 0x19afe800141638dc, /* GL_EXT_texture_view */
    /*  530 */ 0x4ab0caa70a996495, /* GL_EXT_timer_query */
    /*  531 */ 0x471536c0a27f5c81, /* GL_EXT_transform_feedback */
    /*  532 */ 0x1675c7c13b385f42, /* GL_EXT_unpack_subimage */
    /*  533 */ 0x2347ebc551d02975, /* GL_EXT_vertex_array */
    /*  534 */ 0xc5160cefc841200d, /* GL_EXT_vertex_array_bgra */
    /*  535 */ 0xfe8f41c3d0888d86, /* GL_EXT_vertex_attrib_64bit */
    /*  536 */ 0x10ce9358a245f782, /* GL_EXT_vertex_shader */
    /*  537 */ 0x80e4c2ee68e62a5f, /* GL_EXT_vertex_weighting */
    /*  538 */ 0x71431741b9e82753, /* GL_EXT_vulkan_glsl_relaxed */
    /*  539 */ 0xb7046ff80ce07f1a, /* GL_EXT_win32_keyed_mutex */
    /*  540 */ 0x225b607d5cdf07d5, /* GL_EXT_window_rectangles */
    /*  541 */ 0x80306c2b70f53ada, /* GL_EXT_x11_sync_object */
    /*  542 */ 0xaf38ae454737b45a, /* GL_FJ_shader_binary_GCCSO */
    /*  543 */ 0x776d5f9ce5dc30ad, /* GL_GREMEDY_frame_terminator */
    /*  544 */ 0x2b64919ae0d632d6, /* GL_GREMEDY_string_marker */
    /*  545 */ 0x4ba0a53809cd8e1c, /* GL_HP_convolution_border_modes */
    /*  546 */ 0x175101ef679b74d1, /* GL_HP_image_transform */
    /*  547 */ 0x21db09dff47e8865, /* GL_HP_occlusion_test */
    /*  548 */ 0xbccb311192bef9fc, /* GL_HP_texture_lighting */
    /*  549 */ 0x3f692d999fbf45a2, /* GL_HUAWEI_cluster_culling_shader */
    /*  550 */ 0x01088281231ac4b3, /* GL_HUAWEI_subpass_shading */
    /*  551 */ 0x052c78ec9092b2bc, /* GL_IBM_cull_vertex */
    /*  552 */ 0xbed7db565a3dcdb1, /* GL_IBM_multimode_draw_arrays */
    /*  553 */ 0xb0a341b3ba34bde7, /* GL_IBM_rasterpos_clip */
    /*  554 */ 0xe5d4e67e743793af, /* GL_IBM_static_data */
    /*  555 */ 0x42e7c1e06f5230cb, /* GL_IBM_texture_mirrored_repeat */
    /*  556 */ 0x3801878506a0d3e5, /* GL_IBM_vertex_array_lists */
    /*  557 */ 0xe966fe12585d0ee3, /* GL_IMG_bindless_texture */
    /*  558 */ 0xee05cb0623b18588, /* GL_IMG_framebuffer_downsample */
    /*  559 */ 0x6cd4bff21f14cba9, /* GL_IMG_multisampled_render_to_texture */
    /*  560 */ 0x10eae89c21411416, /* GL_IMG_program_binary */
    /*  561 */ 0xe1d246c5f2217570, /* GL_IMG_read_format */
    /*  562 */ 0x631524850de59ddd, /* GL_IMG_shader_binary */
    /*  563 */ 0x26bbd5573ad61282, /* GL_IMG_texture_compression_pvrtc */
    /*  564 */ 0x46869091dbce71a6, /* GL_IMG_texture_compression_pvrtc2 */
    /*  565 */ 0xd44d6d9763e6fd68, /* GL_IMG_texture_filter_cubic */
    /*  566 */ 0xf8c1cfe37858c556, /* GL_INGR_blend_func_separate */
    /*  567 */ 0x9d3ca51fe0f2a837, /* GL_INGR_color_clamp */
    /*  568 */ 0x231c00090b681c01, /* GL_INGR_interlace_read */
    /*  569 */ 0xc0f54564fa652eba, /* GL_INTEL_blackhole_render */
    /*  570 */ 0x8cfa061f6a006e62, /* GL_INTEL_conservative_rasterization */
    /*  571 */ 0x693a15be925d42bb, /* GL_INTEL_fragment_shader_ordering */
    /*  572 */ 0x14386616e0282da8, /* GL_INTEL_framebuffer_CMAA */
    /*  573 */ 0xfe0a30102b2b7f11, /* GL_INTEL_map_texture */
    /*  574 */ 0x6d9138f92a97a9b2, /* GL_INTEL_parallel_arrays */
    /*  575 */ 0x331d1b2f1d575bd8, /* GL_INTEL_performance_query */
    /*  576 */ 0x898f16e7a19612fe, /* GL_KHR_blend_equation_advanced */
    /*  577 */ 0xa66b25957f58c923, /* GL_KHR_blend_equation_advanced_coherent */
    /*  578 */ 0x0956a658c75ab600, /* GL_KHR_context_flush_control */
    /*  579 */ 0x836eea06917bcccb, /* GL_KHR_cooperative_matrix */
    /*  580 */ 0x5e0c5b9607ac8784, /* GL_KHR_debug */
    /*  581 */ 0x08ce79df715e69dc, /* GL_KHR_memory_scope_semantics */
    /*  582 */ 0x12316ddfcc85238e, /* GL_KHR_no_error */
    /*  583 */ 0x3406b66e92343753, /* GL_KHR_parallel_shader_compile */
    /*  584 */ 0xfa6bb57654b50c92, /* GL_KHR_robust_buffer_access_behavior */
    /*  585 */ 0x474beac5f6910636, /* GL_KHR_robustness */
    /*  586 */ 0x65263f2081d063e7, /* GL_KHR_shader_subgroup */
    /*  587 */ 0x24c80aab81e859b3, /* GL_KHR_texture_compression_astc_hdr */
    /*  588 */ 0x16f59295398b9d0a, /* GL_KHR_texture_compression_astc_ldr */
    /*  589 */ 0xa4a29c6f56f2023e, /* GL_KHR_texture_compression_astc_sliced_3d */
    /*  590 */ 0xcbbacf3d7c96adcc, /* GL_KHR_vulkan_glsl */
    /*  591 */ 0x70bbb44bbc67a914, /* GL_MESAX_texture_stack */
    /*  592 */ 0x4b833beb1f90e758, /* GL_MESA_bgra */
    /*  593 */ 0xf9cfb61b2f897c12, /* GL_MESA_framebuffer_flip_x */
    /*  594 */ 0xdf842b85f40b8f2d, /* GL_MESA_framebuffer_flip_y */
    /*  595 */ 0xc735e4d56089513e, /* GL_MESA_framebuffer_swap_xy */
    /*  596 */ 0xac7eeedfea22e53d, /* GL_MESA_pack_invert */
    /*  597 */ 0xe164dc7b3064a548, /* GL_MESA_program_binary_formats */
    /*  598 */ 0x39376b06206502d6, /* GL_MESA_resize_buffers */
    /*  599 */ 0xa14ebc048c19e849, /* GL_MESA_sampler_objects */
    /*  600 */ 0x58e3c24874e50b2f, /* GL_MESA_shader_integer_functions */
    /*  601 */ 0x8ee739e5f4f16337, /* GL_MESA_tile_raster_order */
    /*  602 */ 0x00063de42ab739f6, /* GL_MESA_window_pos */
    /*  603 */ 0x05840d0e5ebfdb5d, /* GL_MESA_ycbcr_texture */
    /*  604 */ 0x210f54fb5023bd27, /* GL_NVX_blend_equation_advanced_multi_draw_buffers */
    /*  605 */ 0xdb3d40c973a8401d, /* GL_NVX_conditional_render */
    /*  606 */ 0xdba64e974cfda98b, /* GL_NVX_gpu_memory_info */
    /*  607 */ 0xfadb1fc8cec16ab6, /* GL_NVX_gpu_multicast2 */
    /*  608 */ 0xcd2e0dc9329fd277, /* GL_NVX_linked_gpu_multicast */
    /*  609 */ 0xd9dac6ae420f2bc1, /* GL_NVX_multiview_per_view_attributes */
    /*  610 */ 0xd0ab24d9b21b5714, /* GL_NVX_progress_fence */
    /*  611 */ 0xf60ebf70e765dade, /* GL_NV_alpha_to_coverage_dither_control */
    /*  612 */ 0x0125c6b149dc763d, /* GL_NV_bindless_multi_draw_indirect */
    /*  613 */ 0xbf25dd3d5b684860, /* GL_NV_bindless_multi_draw_indirect_count */
    /*  614 */ 0xfe0701cf0661b283, /* GL_NV_bindless_texture */
    /*  615 */ 0xdfb2fe6dc8d05e7b, /* GL_NV_blend_equation_advanced */
    /*  616 */ 0x93143e8adaf57589, /* GL_NV_blend_equation_advanced_coherent */
    /*  617 */ 0xea9c32d0ef37492e, /* GL_NV_blend_minmax_factor */
    /*  618 */ 0xcfb887fc69ba21e3, /* GL_NV_blend_square */
    /*  619 */ 0xa4c52c3b41a4fcad, /* GL_NV_clip_space_w_scaling */
    /*  620 */ 0x86fd725bf0f0d470, /* GL_NV_command_list */
    /*  621 */ 0x909a590b136b2993, /* GL_NV_compute_program5 */
    /*  622 */ 0x6e8fcfc637ce5f42, /* GL_NV_compute_shader_derivatives */
    /*  623 */ 0x30dc18387f98fe17, /* GL_NV_conditional_render */
    /*  624 */ 0xe3492208f94da35f, /* GL_NV_conservative_raster */
    /*  625 */ 0xd3d407b80b1805ae, /* GL_NV_conservative_raster_dilate */
    /*  626 */ 0x10c99e7e01aae44f, /* GL_NV_conservative_raster_pre_snap */
    /*  627 */ 0xf4ef9c1caf911a2c, /* GL_NV_conservative_raster_pre_snap_triangles */
    /*  628 */ 0x9a8099482ede4695, /* GL_NV_conservative_raster_underestimation */
    /*  629 */ 0x82f2d3fffe63ccba, /* GL_NV_cooperative_matrix */
    /*  630 */ 0x1250d4e984fabb8a, /* GL_NV_copy_buffer */
    /*  631 */ 0xddf225eb383a722a, /* GL_NV_copy_depth_to_color */
    /*  632 */ 0x542626fd538a9ee0, /* GL_NV_copy_image */
    /*  633 */ 0x1f3cf0884049a65c, /* GL_NV_coverage_sample */
    /*  634 */ 0xa115ed21a9ad2718, /* GL_NV_deep_texture3D */
    /*  635 */ 0x11d0e662e981dd10, /* GL_NV_depth_buffer_float */
    /*  636 */ 0x25caf626c8dc4876, /* GL_NV_depth_clamp */
    /*  637 */ 0x23fb225c6189b719, /* GL_NV_depth_nonlinear */
    /*  638 */ 0xc7c2a14929f83872, /* GL_NV_displacement_micromap */
    /*  639 */ 0xe30effdb6e04aad2, /* GL_NV_draw_buffers */
    /*  640 */ 0x5cef483902a0a7d1, /* GL_NV_draw_instanced */
    /*  641 */ 0x0ac29b41db04db89, /* GL_NV_draw_texture */
    /*  642 */ 0x0c3ad3a0bb6ea832, /* GL_NV_draw_vulkan_image */
    /*  643 */ 0x86aaaa35812cc6e4, /* GL_NV_evaluators */
    /*  644 */ 0x0d0ad1150bf11b93, /* GL_NV_explicit_attrib_location */
    /*  645 */ 0xb1fb52088193eb75, /* GL_NV_explicit_multisample */
    /*  646 */ 0xf69d212a36261f45, /* GL_NV_fbo_color_attachments */
    /*  647 */ 0x9f9d6242407aaa0d, /* GL_NV_fence */
    /*  648 */ 0x574a28d0edc9eb1f, /* GL_NV_fill_rectangle */
    /*  649 */ 0x60178d619bd63acd, /* GL_NV_float_buffer */
    /*  650 */ 0x3a25bd3423152eb5, /* GL_NV_fog_distance */
    /*  651 */ 0xbd0368ffaa60b1e1, /* GL_NV_fragment_coverage_to_color */
    /*  652 */ 0xd63f48ff142e3931, /* GL_NV_fragment_program */
    /*  653 */ 0x9607f3b2549a29c3, /* GL_NV_fragment_program2 */
    /*  654 */ 0x3fc3c14225294207, /* GL_NV_fragment_program4 */
    /*  655 */ 0x7e38a803870eb005, /* GL_NV_fragment_program_option */
    /*  656 */ 0x63f3491b75562351, /* GL_NV_fragment_shader_barycentric */
    /*  657 */ 0xf907528dfaacf5d1, /* GL_NV_fragment_shader_interlock */
    /*  658 */ 0xc7b0688e759eacca, /* GL_NV_framebuffer_blit */
    /*  659 */ 0x7690d69739f37d49, /* GL_NV_framebuffer_mixed_samples */
    /*  660 */ 0xd333a1d53faf1645, /* GL_NV_framebuffer_multisample */
    /*  661 */ 0xb7e1d7ede28f1eb6, /* GL_NV_framebuffer_multisample_coverage */
    /*  662 */ 0x42fb5b03beace82d, /* GL_NV_generate_mipmap_sRGB */
    /*  663 */ 0xd649529b8b1dc13f, /* GL_NV_geometry_program4 */
    /*  664 */ 0x85be2495755b8912, /* GL_NV_geometry_shader4 */
    /*  665 */ 0x2650d5fc619ace25, /* GL_NV_geometry_shader_passthrough */
    /*  666 */ 0x0f309973ce34369d, /* GL_NV_gpu_multicast */
    /*  667 */ 0xb97d5c93298f0cd0, /* GL_NV_gpu_program4 */
    /*  668 */ 0xfee0597c2b98bd5a, /* GL_NV_gpu_program5 */
    /*  669 */ 0x76ac1ada5bbc4ea2, /* GL_NV_gpu_program5_mem_extended */
    /*  670 */ 0x9ca801fbedd18a78, /* GL_NV_gpu_shader5 */
    /*  671 */ 0x185a8632c27d17b4, /* GL_NV_half_float */
    /*  672 */ 0xe34c3aba26b785e0, /* GL_NV_image_formats */
    /*  673 */ 0xc2e8b0284eeb3343, /* GL_NV_instanced_arrays */
    /*  674 */ 0xa5628152267b8db5, /* GL_NV_internalformat_sample_query */
    /*  675 */ 0x4514ca3e8473d61d, /* GL_NV_light_max_exponent */
    /*  676 */ 0xe91f9b1323143013, /* GL_NV_memory_attachment */
    /*  677 */ 0x529b823de64f6ca0, /* GL_NV_memory_object_sparse */
    /*  678 */ 0x2793373463edd95b, /* GL_NV_mesh_shader */
    /*  679 */ 0x8d5187c2fb3e3879, /* GL_NV_multisample_coverage */
    /*  680 */ 0x92f77a4cfb0d4df3, /* GL_NV_multisample_filter_hint */
    /*  681 */ 0x5b891d5155380820, /* GL_NV_non_square_matrices */
    /*  682 */ 0xdff6cf35e1df2d8d, /* GL_NV_occlusion_query */
    /*  683 */ 0xda29f4099a052321, /* GL_NV_pack_subimage */
    /*  684 */ 0x1a5932681cefa5eb, /* GL_NV_packed_depth_stencil */
    /*  685 */ 0xbffccb846b13070a, /* GL_NV_parameter_buffer_object */
    /*  686 */ 0xb153f109324c418b, /* GL_NV_parameter_buffer_object2 */
    /*  687 */ 0x77bc468b065f8fdb, /* GL_NV_path_rendering */
    /*  688 */ 0x2f70022ecb786aed, /* GL_NV_path_rendering_shared_edge */
    /*  689 */ 0x0b44f2e633646ab5, /* GL_NV_pixel_buffer_object */
    /*  690 */ 0x43d8732157b4106d, /* GL_NV_pixel_data_range */
    /*  691 */ 0x839efae2d0736a4c, /* GL_NV_point_sprite */
    /*  692 */ 0x3330eb9a4ceb6c0c, /* GL_NV_polygon_mode */
    /*  693 */ 0x6512c3d1922a98db, /* GL_NV_present_video */
    /*  694 */ 0x8c542b195b5b3c94, /* GL_NV_primitive_restart */
    /*  695 */ 0x0cacb49d8f1c105a, /* GL_NV_primitive_shading_rate */
    /*  696 */ 0x9b1b0441d8d19911, /* GL_NV_query_resource */
    /*  697 */ 0x15f0661a8638b338, /* GL_NV_query_resource_tag */
    /*  698 */ 0xdd74002f450fb368, /* GL_NV_ray_tracing */
    /*  699 */ 0x182d9aed7af08983, /* GL_NV_ray_tracing_motion_blur */
    /*  700 */ 0xb51b7c433236bd06, /* GL_NV_read_buffer */
    /*  701 */ 0xc91023f37354df43, /* GL_NV_read_buffer_front */
    /*  702 */ 0x3dfff3ed25362196, /* GL_NV_read_depth */
    /*  703 */ 0x55261906f55bb17a, /* GL_NV_read_depth_stencil */
    /*  704 */ 0x7bab8fd7e4a04ee8, /* GL_NV_read_stencil */
    /*  705 */ 0xd791c5687139b905, /* GL_NV_register_combiners */
    /*  706 */ 0x8814ab530e95a798, /* GL_NV_register_combiners2 */
    /*  707 */ 0xb46bd57f88e91d64, /* GL_NV_representative_fragment_test */
    /*  708 */ 0xc4eada8b9cbe17c0, /* GL_NV_robustness_video_memory_purge */
    /*  709 */ 0x2c2775936dc2a882, /* GL_NV_sRGB_formats */
    /*  710 */ 0xc50ae467eedfefde, /* GL_NV_sample_locations */
    /*  711 */ 0x446a05466a6d6429, /* GL_NV_sample_mask_override_coverage */
    /*  712 */ 0x4247a4acbfcdb098, /* GL_NV_scissor_exclusive */
    /*  713 */ 0x0383e334dd39d9a0, /* GL_NV_shader_atomic_counters */
    /*  714 */ 0x02399be47930fbf4, /* GL_NV_shader_atomic_float */
    /*  715 */ 0x8c8c8962eadf1230, /* GL_NV_shader_atomic_float64 */
    /*  716 */ 0x4c3311286ab16152, /* GL_NV_shader_atomic_fp16_vector */
    /*  717 */ 0xb14dbc3c64a1326f, /* GL_NV_shader_atomic_int64 */
    /*  718 */ 0x3ae6fc5c42bab2c2, /* GL_NV_shader_buffer_load */
    /*  719 */ 0x1c05604500113691, /* GL_NV_shader_buffer_store */
    /*  720 */ 0x22e85dcf4a44b2f7, /* GL_NV_shader_invocation_reorder */
    /*  721 */ 0xbb5c10f38325fdf8, /* GL_NV_shader_noperspective_interpolation */
    /*  722 */ 0x6d97890637a77774, /* GL_NV_shader_sm_builtins */
    /*  723 */ 0xaf5c0eb5c483eb28, /* GL_NV_shader_storage_buffer_object */
    /*  724 */ 0x826afa0d2f696f22, /* GL_NV_shader_subgroup_partitioned */
    /*  725 */ 0x7b3f8fad48cfd967, /* GL_NV_shader_texture_footprint */
    /*  726 */ 0xfd2aa76218c9354e, /* GL_NV_shader_thread_group */
    /*  727 */ 0x74a053165bf8ada4, /* GL_NV_shader_thread_shuffle */
    /*  728 */ 0xf9355d5174ef4c70, /* GL_NV_shading_rate_image */
    /*  729 */ 0x28944cfc0cca07ec, /* GL_NV_shadow_samplers_array */
    /*  730 */ 0xfdbd6232791ce36f, /* GL_NV_shadow_samplers_cube */
    /*  731 */ 0x56dc6bb2a7d8736f, /* GL_NV_stereo_view_rendering */
    /*  732 */ 0x2410081ec485d619, /* GL_NV_tessellation_program5 */
    /*  733 */ 0x6a6887942da6a4c4, /* GL_NV_texgen_emboss */
    /*  734 */ 0x35865e06d7292c9b, /* GL_NV_texgen_reflection */
    /*  735 */ 0x282f885e0bfd25de, /* GL_NV_texture_barrier */
    /*  736 */ 0x373989acbf486191, /* GL_NV_texture_border_clamp */
    /*  737 */ 0x4d5276bd5a1f04ce, /* GL_NV_texture_compression_s3tc_update */
    /*  738 */ 0x25b70b1f5bbed713, /* GL_NV_texture_compression_vtc */
    /*  739 */ 0x84b70fe53fcdcde1, /* GL_NV_texture_env_combine4 */
    /*  740 */ 0x07e650e01fee3678, /* GL_NV_texture_expand_normal */
    /*  741 */ 0x4679eee96470073f, /* GL_NV_texture_multisample */
    /*  742 */ 0xcba499c04274ad25, /* GL_NV_texture_npot_2D_mipmap */
    /*  743 */ 0xccbc8154a70c3605, /* GL_NV_texture_rectangle */
    /*  744 */ 0x5da6e59a7e51bc40, /* GL_NV_texture_rectangle_compressed */
    /*  745 */ 0x8a67a1269b408254, /* GL_NV_texture_shader */
    /*  746 */ 0x816b354fd0cd9228, /* GL_NV_texture_shader2 */
    /*  747 */ 0x5526327fa18acdde, /* GL_NV_texture_shader3 */
    /*  748 */ 0x39f7dcc9a62c5153, /* GL_NV_timeline_semaphore */
    /*  749 */ 0xf09b77c741443fcb, /* GL_NV_transform_feedback */
    /*  750 */ 0x32519ec17990e826, /* GL_NV_transform_feedback2 */
    /*  751 */ 0x5600eb6f04e474ee, /* GL_NV_uniform_buffer_std430_layout */
    /*  752 */ 0x5a3050e67df48f2c, /* GL_NV_uniform_buffer_unified_memory */
    /*  753 */ 0xc270d7ffe7e44b23, /* GL_NV_vdpau_interop */
    /*  754 */ 0x613710111a2944f7, /* GL_NV_vdpau_interop2 */
    /*  755 */ 0x2670ae7bcc80188e, /* GL_NV_vertex_array_range */
    /*  756 */ 0x79ae834a103024c5, /* GL_NV_vertex_array_range2 */
    /*  757 */ 0xe688c60fe2e62039, /* GL_NV_vertex_attrib_integer_64bit */
    /*  758 */ 0x7e2fb60c66658e57, /* GL_NV_vertex_buffer_unified_memory */
    /*  759 */ 0x527413b984649803, /* GL_NV_vertex_program */
    /*  760 */ 0x7d2fc2b85898af18, /* GL_NV_vertex_program1_1 */
    /*  761 */ 0x2d5a70a0a1d00d78, /* GL_NV_vertex_program2 */
    /*  762 */ 0x747ed48148981054, /* GL_NV_vertex_program2_option */
    /*  763 */ 0xc13798df29c369e2, /* GL_NV_vertex_program3 */
    /*  764 */ 0xa796194638bbdc74, /* GL_NV_vertex_program4 */
    /*  765 */ 0x89ae752e4cfcfae8, /* GL_NV_video_capture */
    /*  766 */ 0x1b9db3e10e73323b, /* GL_NV_viewport_array */
    /*  767 */ 0x4e9c3fc0856350f9, /* GL_NV_viewport_array2 */
    /*  768 */ 0xdf18b1c27e48f432, /* GL_NV_viewport_swizzle */
    /*  769 */ 0xc05411382c7e9b6f, /* GL_OES_EGL_image */
    /*  770 */ 0xb3f47895b1c4d5f8, /* GL_OES_EGL_image_external */
    /*  771 */ 0xbbae531ab8d7e16f, /* GL_OES_EGL_image_external_essl3 */
    /*  772 */ 0x55f4d891b16ad96c, /* GL_OES_byte_coordinates */
    /*  773 */ 0x866125fa75aab774, /* GL_OES_compressed_ETC1_RGB8_sub_texture */
    /*  774 */ 0x5b4df7888b81a92b, /* GL_OES_compressed_ETC1_RGB8_texture */
    /*  775 */ 0xd1ae5222afe37da5, /* GL_OES_compressed_paletted_texture */
    /*  776 */ 0xc5e1ddc1ea43276e, /* GL_OES_copy_image */
    /*  777 */ 0xa3f0bbbc7660d96c, /* GL_OES_depth24 */
    /*  778 */ 0xb8b2dd3478f1ec83, /* GL_OES_depth32 */
    /*  779 */ 0x67516f69dbc843f6, /* GL_OES_depth_texture */
    /*  780 */ 0x012b99c59ced284f, /* GL_OES_draw_buffers_indexed */
    /*  781 */ 0x4638dd889d2b7eab, /* GL_OES_draw_elements_base_vertex */
    /*  782 */ 0x29e68bee4a9705f1, /* GL_OES_element_index_uint */
    /*  783 */ 0xe0b0d82d6dc31dae, /* GL_OES_fbo_render_mipmap */
    /*  784 */ 0x9f59932407436633, /* GL_OES_fixed_point */
    /*  785 */ 0x116a77aa55534c76, /* GL_OES_fragment_precision_high */
    /*  786 */ 0x5e6f26587d551ffc, /* GL_OES_geometry_point_size */
    /*  787 */ 0xaa384a84e450d595, /* GL_OES_geometry_shader */
    /*  788 */ 0x503ad238c5e97931, /* GL_OES_get_program_binary */
    /*  789 */ 0x77f35c2a7a2bd390, /* GL_OES_gpu_shader5 */
    /*  790 */ 0x22e521fe25c89a3b, /* GL_OES_mapbuffer */
    /*  791 */ 0xb124b23bca92b355, /* GL_OES_packed_depth_stencil */
    /*  792 */ 0x303e15e4f8fb9ee6, /* GL_OES_primitive_bounding_box */
    /*  793 */ 0xc8d3d0277204ac3d, /* GL_OES_query_matrix */
    /*  794 */ 0xca46680e5cfc3e18, /* GL_OES_read_format */
    /*  795 */ 0xd6c9bec1dd5d5b89, /* GL_OES_required_internalformat */
    /*  796 */ 0xccb18f4e376e6c74, /* GL_OES_rgb8_rgba8 */
    /*  797 */ 0xcb740362814f4ca0, /* GL_OES_sample_shading */
    /*  798 */ 0x8f4eb2b127c21f67, /* GL_OES_sample_variables */
    /*  799 */ 0xa023718702859970, /* GL_OES_shader_image_atomic */
    /*  800 */ 0x8cc1262bb8c2d393, /* GL_OES_shader_io_blocks */
    /*  801 */ 0xc772b78382e1a793, /* GL_OES_shader_multisample_interpolation */
    /*  802 */ 0xbcbfeb8171756944, /* GL_OES_single_precision */
    /*  803 */ 0x4e9710576f516b4e, /* GL_OES_standard_derivatives */
    /*  804 */ 0x79f1937e076eb6e0, /* GL_OES_stencil1 */
    /*  805 */ 0x7361db1a08c53c55, /* GL_OES_stencil4 */
    /*  806 */ 0x6df979b4adc4989b, /* GL_OES_surfaceless_context */
    /*  807 */ 0xdc7532bffc48cb01, /* GL_OES_tessellation_point_size */
    /*  808 */ 0x8bbb4c0c94dc1415, /* GL_OES_tessellation_shader */
    /*  809 */ 0xccac53b0ed36c73c, /* GL_OES_texture_3D */
    /*  810 */ 0xedc39fcb928c7be5, /* GL_OES_texture_border_clamp */
    /*  811 */ 0xc7d6a2d8a596bf50, /* GL_OES_texture_buffer */
    /*  812 */ 0x552cece98cadbaa6, /* GL_OES_texture_compression_astc */
    /*  813 */ 0xfad8c3de7cf9ffc4, /* GL_OES_texture_cube_map_array */
    /*  814 */ 0x32ed502b39dd1594, /* GL_OES_texture_float */
    /*  815 */ 0x5afe2be3731190e1, /* GL_OES_texture_float_linear */
    /*  816 */ 0xa9fdcf0e5b6803dd, /* GL_OES_texture_half_float */
    /*  817 */ 0x0011e43010189be7, /* GL_OES_texture_half_float_linear */
    /*  818 */ 0xe706ff7638659b7e, /* GL_OES_texture_npot */
    /*  819 */ 0xdfa8a0ccd9d60d53, /* GL_OES_texture_stencil8 */
    /*  820 */ 0xbc655ee4febdcfca, /* GL_OES_texture_storage_multisample_2d_array */
    /*  821 */ 0x8fc2a146f6290d39, /* GL_OES_texture_view */
    /*  822 */ 0x7cd6041965da7d3c, /* GL_OES_vertex_array_object */
    /*  823 */ 0x8d77aa22bdd641e8, /* GL_OES_vertex_half_float */
    /*  824 */ 0x244e9e511573b959, /* GL_OES_vertex_type_10_10_10_2 */
    /*  825 */ 0x2e0ac92809baabbd, /* GL_OES_viewport_array */
    /*  826 */ 0xe4756190e24cfae1, /* GL_OML_interlace */
    /*  827 */ 0xf00e1502b0d1f5d7, /* GL_OML_resample */
    /*  828 */ 0xee17f2c40613fa28, /* GL_OML_subsample */
    /*  829 */ 0x462789e64be7acd7, /* GL_OVR_multiview */
    /*  830 */ 0x4d3b083404c10e3f, /* GL_OVR_multiview2 */
    /*  831 */ 0xdd9450d3b97e069b, /* GL_OVR_multiview_multisampled_render_to_texture */
    /*  832 */ 0xb1df54452698a7be, /* GL_PGI_misc_hints */
    /*  833 */ 0x830c412288059800, /* GL_PGI_vertex_hints */
    /*  834 */ 0x03b99dd37fd50188, /* GL_QCOM_YUV_texture_gather */
    /*  835 */ 0x3aa5ff0497f38e96, /* GL_QCOM_alpha_test */
    /*  836 */ 0x8b6f2c405eed8fc9, /* GL_QCOM_binning_control */
    /*  837 */ 0xd69ddd5074f27947, /* GL_QCOM_driver_control */
    /*  838 */ 0x2cfff6c37fa549bc, /* GL_QCOM_extended_get */
    /*  839 */ 0xa36cbb8c3a77c3a1, /* GL_QCOM_extended_get2 */
    /*  840 */ 0x1359ba3cc79be309, /* GL_QCOM_frame_extrapolation */
    /*  841 */ 0xa96b1c721f28a1c2, /* GL_QCOM_framebuffer_foveated */
    /*  842 */ 0xaa7b8918e97b02c0, /* GL_QCOM_image_processing */
    /*  843 */ 0x822886625bd76c4a, /* GL_QCOM_motion_estimation */
    /*  844 */ 0x62c4f9e3d0cf2728, /* GL_QCOM_perfmon_global_mode */
    /*  845 */ 0x6667e13047800b18, /* GL_QCOM_render_sRGB_R8_RG8 */
    /*  846 */ 0x005a335cb406a184, /* GL_QCOM_render_shared_exponent */
    /*  847 */ 0x0668ea2d27f4b9c7, /* GL_QCOM_shader_framebuffer_fetch_noncoherent */
    /*  848 */ 0x2f8fba53941074de, /* GL_QCOM_shader_framebuffer_fetch_rate */
    /*  849 */ 0x360f4bc982306308, /* GL_QCOM_shading_rate */
    /*  850 */ 0xa23647ccb657fc93, /* GL_QCOM_texture_foveated */
    /*  851 */ 0xac6fb0841696dc5f, /* GL_QCOM_texture_foveated2 */
    /*  852 */ 0xb7f306a63180d3df, /* GL_QCOM_texture_foveated_subsampled_layout */
    /*  853 */ 0x70d9c41ab20f93f9, /* GL_QCOM_texture_lod_bias */
    /*  854 */ 0x288ca2e6c7c5c86d, /* GL_QCOM_tiled_rendering */
    /*  855 */ 0x28eabd27e2f106a8, /* GL_QCOM_writeonly_rendering */
    /*  856 */ 0xafb9cdf7b9a2826a, /* GL_QCOM_ycbcr_degamma */
    /*  857 */ 0x14dac5dff736a3df, /* GL_REND_screen_coordinates */
    /*  858 */ 0x93469fe128fc0919, /* GL_S3_s3tc */
    /*  859 */ 0x8c7ee523e6ed026a, /* GL_SGIS_detail_texture */
    /*  860 */ 0xe54deb13059b8c4c, /* GL_SGIS_fog_function */
    /*  861 */ 0xb1b31f0af9b1e3c1, /* GL_SGIS_generate_mipmap */
    /*  862 */ 0x39568b3690efef18, /* GL_SGIS_multisample */
    /*  863 */ 0xf250c15acefa1ac9, /* GL_SGIS_pixel_texture */
    /*  864 */ 0x9b7bb525c279e853, /* GL_SGIS_point_line_texgen */
    /*  865 */ 0x4e3e0fa2dfafd5b4, /* GL_SGIS_point_parameters */
    /*  866 */ 0x4a4aa0671eb15c9f, /* GL_SGIS_sharpen_texture */
    /*  867 */ 0xe3880e70b14a01ef, /* GL_SGIS_texture4D */
    /*  868 */ 0x70c7cab7e228743c, /* GL_SGIS_texture_border_clamp */
    /*  869 */ 0x04eb37e0f3c4686a, /* GL_SGIS_texture_color_mask */
    /*  870 */ 0xb6400bcd7a346c99, /* GL_SGIS_texture_edge_clamp */
    /*  871 */ 0xd79b6287779eca3f, /* GL_SGIS_texture_filter4 */
    /*  872 */ 0xf25eb0173c775af1, /* GL_SGIS_texture_lod */
    /*  873 */ 0x4b818d48997acf33, /* GL_SGIS_texture_select */
    /*  874 */ 0x42053ed5c2789d8a, /* GL_SGIX_async */
    /*  875 */ 0x9baec4623ae00aa8, /* GL_SGIX_async_histogram */
    /*  876 */ 0xbed04383395711b9, /* GL_SGIX_async_pixel */
    /*  877 */ 0xd3cc8d1ef603a7f6, /* GL_SGIX_blend_alpha_minmax */
    /*  878 */ 0xe60980f13acb1fe8, /* GL_SGIX_calligraphic_fragment */
    /*  879 */ 0x5d613989907c2996, /* GL_SGIX_clipmap */
    /*  880 */ 0x8fa248e9981db96e, /* GL_SGIX_convolution_accuracy */
    /*  881 */ 0x47ef8f4254eec5a0, /* GL_SGIX_depth_pass_instrument */
    /*  882 */ 0x3489d57ce09fdb5e, /* GL_SGIX_depth_texture */
    /*  883 */ 0x37a8cdae9276920f, /* GL_SGIX_flush_raster */
    /*  884 */ 0x21b4c2f4db4fb980, /* GL_SGIX_fog_offset */
    /*  885 */ 0x5379c01e285814d7, /* GL_SGIX_fragment_lighting */
    /*  886 */ 0xbc4f1c742be26f3f, /* GL_SGIX_framezoom */
    /*  887 */ 0xd8ea1ff9ab303390, /* GL_SGIX_igloo_interface */
    /*  888 */ 0x828685155c316d20, /* GL_SGIX_instruments */
    /*  889 */ 0xaf75b3c8a321fd9b, /* GL_SGIX_interlace */
    /*  890 */ 0xac3c1477e6f161ef, /* GL_SGIX_ir_instrument1 */
    /*  891 */ 0xe6f72d5da01567e9, /* GL_SGIX_list_priority */
    /*  892 */ 0x945b05eefbbaf60c, /* GL_SGIX_pixel_texture */
    /*  893 */ 0x3c667c7037c70246, /* GL_SGIX_pixel_tiles */
    /*  894 */ 0x17349f9e9a6e5976, /* GL_SGIX_polynomial_ffd */
    /*  895 */ 0xe64b4cbd5d5fe178, /* GL_SGIX_reference_plane */
    /*  896 */ 0x007a4678f7628880, /* GL_SGIX_resample */
    /*  897 */ 0xfc833b6c6a1f8cc1, /* GL_SGIX_scalebias_hint */
    /*  898 */ 0xfe04490bc9621226, /* GL_SGIX_shadow */
    /*  899 */ 0xa1f64483e1ed6c09, /* GL_SGIX_shadow_ambient */
    /*  900 */ 0x1b1eb2d33e2626cb, /* GL_SGIX_sprite */
    /*  901 */ 0xab712623aed89578, /* GL_SGIX_subsample */
    /*  902 */ 0xf6707a8df70625ff, /* GL_SGIX_tag_sample_buffer */
    /*  903 */ 0xb31cc86db966473b, /* GL_SGIX_texture_add_env */
    /*  904 */ 0x8b7acea8e9290fae, /* GL_SGIX_texture_coordinate_clamp */
    /*  905 */ 0xb5df7fecc6d921f7, /* GL_SGIX_texture_lod_bias */
    /*  906 */ 0xb819f1015daf16c4, /* GL_SGIX_texture_multi_buffer */
    /*  907 */ 0x3c9d7b66aea3cba1, /* GL_SGIX_texture_scale_bias */
    /*  908 */ 0xe9afc853af27422d, /* GL_SGIX_vertex_preclip */
    /*  909 */ 0x3bb1183ffedb9c68, /* GL_SGIX_ycrcb */
    /*  910 */ 0x004ffc30998c20db, /* GL_SGIX_ycrcb_subsample */
    /*  911 */ 0x7ab4a4b4639c69df, /* GL_SGIX_ycrcba */
    /*  912 */ 0x014fc2d56670cd5a, /* GL_SGI_color_matrix */
    /*  913 */ 0x5f28de108b449e5d, /* GL_SGI_color_table */
    /*  914 */ 0xa03c2d1d2eeb1bd2, /* GL_SGI_texture_color_table */
    /*  915 */ 0xd3460591a825bcf6, /* GL_SUNX_constant_data */
    /*  916 */ 0x4e5296cda0471f61, /* GL_SUN_convolution_border_modes */
    /*  917 */ 0xe19c670da3369515, /* GL_SUN_global_alpha */
    /*  918 */ 0xbd8a54b9db901974, /* GL_SUN_mesh_array */
    /*  919 */ 0xa52af6dd6a5fb2d3, /* GL_SUN_slice_accum */
    /*  920 */ 0xbeb30cddf53ae288, /* GL_SUN_triangle_list */
    /*  921 */ 0xd0bf54f2a8798b55, /* GL_SUN_vertex */
    /*  922 */ 0x156892df7146814d, /* GL_VIV_shader_binary */
    /*  923 */ 0xf09a257256bde8f6, /* GL_WIN_phong_shading */
    /*  924 */ 0x5a3e106713a38cff  /* GL_WIN_specular_fog */
};

#ifdef __cplusplus
GladGLContext glad_gl_context = {};
#else
GladGLContext glad_gl_context = { 0 };
#endif

static void glad_gl_load_GL_VERSION_1_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         116, /* glBlendFunc */
         151, /* glClear */
         159, /* glClearColor */
         163, /* glClearDepth */
         176, /* glClearStencil */
         207, /* glColorMask */
         327, /* glCullFace */
         383, /* glDepthFunc */
         384, /* glDepthMask */
         385, /* glDepthRange */
         397, /* glDisable */
         419, /* glDrawBuffer */
         460, /* glEnable */
         498, /* glFinish */
         504, /* glFlush */
         569, /* glFrontFace */
         628, /* glGetBooleanv */
         669, /* glGetDoublev */
         670, /* glGetError */
         679, /* glGetFloatv */
         713, /* glGetIntegerv */
         877, /* glGetString */
         887, /* glGetTexImage */
         888, /* glGetTexLevelParameterfv */
         889, /* glGetTexLevelParameteriv */
         896, /* glGetTexParameterfv */
         897, /* glGetTexParameteriv */
        1013, /* glHint */
        1055, /* glIsEnabled */
        1105, /* glLineWidth */
        1121, /* glLogicOp */
        1422, /* glPixelStoref */
        1423, /* glPixelStorei */
        1450, /* glPointSize */
        1454, /* glPolygonMode */
        1668, /* glReadBuffer */
        1670, /* glReadPixels */
        1733, /* glScissor */
        1797, /* glStencilFunc */
        1800, /* glStencilMask */
        1802, /* glStencilOp */
        1889, /* glTexImage1D */
        1890, /* glTexImage2D */
        1905, /* glTexParameterf */
        1906, /* glTexParameterfv */
        1907, /* glTexParameteri */
        1908, /* glTexParameteriv */
        2479  /* glViewport */
    };
    uint32_t i;
    if(!context->VERSION_1_0) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_1_1(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          75, /* glBindTexture */
         281, /* glCopyTexImage1D */
         283, /* glCopyTexImage2D */
         285, /* glCopyTexSubImage1D */
         287, /* glCopyTexSubImage2D */
         374, /* glDeleteTextures */
         412, /* glDrawArrays */
         429, /* glDrawElements */
         595, /* glGenTextures */
         812, /* glGetPointerv */
        1086, /* glIsTexture */
        1455, /* glPolygonOffset */
        1930, /* glTexSubImage1D */
        1932  /* glTexSubImage2D */
    };
    uint32_t i;
    if(!context->VERSION_1_1) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_1_2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         289, /* glCopyTexSubImage3D */
         443, /* glDrawRangeElements */
        1894, /* glTexImage3D */
        1934  /* glTexSubImage3D */
    };
    uint32_t i;
    if(!context->VERSION_1_2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_1_3(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           5, /* glActiveTexture */
         236, /* glCompressedTexImage1D */
         238, /* glCompressedTexImage2D */
         240, /* glCompressedTexImage3D */
         242, /* glCompressedTexSubImage1D */
         244, /* glCompressedTexSubImage2D */
         246, /* glCompressedTexSubImage3D */
         652, /* glGetCompressedTexImage */
        1717  /* glSampleCoverage */
    };
    uint32_t i;
    if(!context->VERSION_1_3) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_1_4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         103, /* glBlendColor */
         106, /* glBlendEquation */
         118, /* glBlendFuncSeparate */
        1198, /* glMultiDrawArrays */
        1207, /* glMultiDrawElements */
        1437, /* glPointParameterf */
        1441, /* glPointParameterfv */
        1445, /* glPointParameteri */
        1447  /* glPointParameteriv */
    };
    uint32_t i;
    if(!context->VERSION_1_4) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_1_5(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          31, /* glBeginQuery */
          41, /* glBindBuffer */
         134, /* glBufferData */
         142, /* glBufferSubData */
         344, /* glDeleteBuffers */
         364, /* glDeleteQueries */
         479, /* glEndQuery */
         573, /* glGenBuffers */
         587, /* glGenQueries */
         630, /* glGetBufferParameteriv */
         633, /* glGetBufferPointerv */
         635, /* glGetBufferSubData */
         851, /* glGetQueryObjectiv */
         855, /* glGetQueryObjectuiv */
         857, /* glGetQueryiv */
        1051, /* glIsBuffer */
        1077, /* glIsQuery */
        1136, /* glMapBuffer */
        2123  /* glUnmapBuffer */
    };
    uint32_t i;
    if(!context->VERSION_1_5) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_2_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          23, /* glAttachShader */
          39, /* glBindAttribLocation */
         109, /* glBlendEquationSeparate */
         227, /* glCompileShader */
         310, /* glCreateProgram */
         318, /* glCreateShader */
         360, /* glDeleteProgram */
         371, /* glDeleteShader */
         395, /* glDetachShader */
         406, /* glDisableVertexAttribArray */
         420, /* glDrawBuffers */
         469, /* glEnableVertexAttribArray */
         608, /* glGetActiveAttrib */
         613, /* glGetActiveUniform */
         623, /* glGetAttachedShaders */
         624, /* glGetAttribLocation */
         819, /* glGetProgramInfoLog */
         841, /* glGetProgramiv */
         868, /* glGetShaderInfoLog */
         870, /* glGetShaderSource */
         872, /* glGetShaderiv */
         928, /* glGetUniformLocation */
         933, /* glGetUniformfv */
         937, /* glGetUniformiv */
         970, /* glGetVertexAttribPointerv */
         973, /* glGetVertexAttribdv */
         976, /* glGetVertexAttribfv */
         979, /* glGetVertexAttribiv */
        1073, /* glIsProgram */
        1083, /* glIsShader */
        1107, /* glLinkProgram */
        1774, /* glShaderSource */
        1798, /* glStencilFuncSeparate */
        1801, /* glStencilMaskSeparate */
        1803, /* glStencilOpSeparate */
        2006, /* glUniform1f */
        2008, /* glUniform1fv */
        2010, /* glUniform1i */
        2016, /* glUniform1iv */
        2028, /* glUniform2f */
        2030, /* glUniform2fv */
        2032, /* glUniform2i */
        2038, /* glUniform2iv */
        2050, /* glUniform3f */
        2052, /* glUniform3fv */
        2054, /* glUniform3i */
        2060, /* glUniform3iv */
        2072, /* glUniform4f */
        2074, /* glUniform4fv */
        2076, /* glUniform4i */
        2082, /* glUniform4iv */
        2099, /* glUniformMatrix2fv */
        2106, /* glUniformMatrix3fv */
        2113, /* glUniformMatrix4fv */
        2131, /* glUseProgram */
        2146, /* glValidateProgram */
        2207, /* glVertexAttrib1d */
        2210, /* glVertexAttrib1dv */
        2213, /* glVertexAttrib1f */
        2216, /* glVertexAttrib1fv */
        2221, /* glVertexAttrib1s */
        2224, /* glVertexAttrib1sv */
        2227, /* glVertexAttrib2d */
        2230, /* glVertexAttrib2dv */
        2233, /* glVertexAttrib2f */
        2236, /* glVertexAttrib2fv */
        2241, /* glVertexAttrib2s */
        2244, /* glVertexAttrib2sv */
        2247, /* glVertexAttrib3d */
        2250, /* glVertexAttrib3dv */
        2253, /* glVertexAttrib3f */
        2256, /* glVertexAttrib3fv */
        2261, /* glVertexAttrib3s */
        2264, /* glVertexAttrib3sv */
        2267, /* glVertexAttrib4Nbv */
        2269, /* glVertexAttrib4Niv */
        2271, /* glVertexAttrib4Nsv */
        2273, /* glVertexAttrib4Nub */
        2275, /* glVertexAttrib4Nubv */
        2277, /* glVertexAttrib4Nuiv */
        2279, /* glVertexAttrib4Nusv */
        2281, /* glVertexAttrib4bv */
        2283, /* glVertexAttrib4d */
        2286, /* glVertexAttrib4dv */
        2289, /* glVertexAttrib4f */
        2292, /* glVertexAttrib4fv */
        2297, /* glVertexAttrib4iv */
        2299, /* glVertexAttrib4s */
        2302, /* glVertexAttrib4sv */
        2306, /* glVertexAttrib4ubv */
        2309, /* glVertexAttrib4uiv */
        2311, /* glVertexAttrib4usv */
        2410  /* glVertexAttribPointer */
    };
    uint32_t i;
    if(!context->VERSION_2_0) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_2_1(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2102, /* glUniformMatrix2x3fv */
        2104, /* glUniformMatrix2x4fv */
        2109, /* glUniformMatrix3x2fv */
        2111, /* glUniformMatrix3x4fv */
        2116, /* glUniformMatrix4x2fv */
        2118  /* glUniformMatrix4x3fv */
    };
    uint32_t i;
    if(!context->VERSION_2_1) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_3_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          24, /* glBeginConditionalRender */
          34, /* glBeginTransformFeedback */
          43, /* glBindBufferBase */
          48, /* glBindBufferRange */
          53, /* glBindFragDataLocation */
          57, /* glBindFramebuffer */
          69, /* glBindRenderbuffer */
          82, /* glBindVertexArray */
         127, /* glBlitFramebuffer */
         145, /* glCheckFramebufferStatus */
         149, /* glClampColor */
         155, /* glClearBufferfi */
         156, /* glClearBufferfv */
         157, /* glClearBufferiv */
         158, /* glClearBufferuiv */
         209, /* glColorMaski */
         350, /* glDeleteFramebuffers */
         367, /* glDeleteRenderbuffers */
         378, /* glDeleteVertexArrays */
         408, /* glDisablei */
         471, /* glEnablei */
         472, /* glEndConditionalRender */
         482, /* glEndTransformFeedback */
         505, /* glFlushMappedBufferRange */
         548, /* glFramebufferRenderbuffer */
         554, /* glFramebufferTexture1D */
         556, /* glFramebufferTexture2D */
         558, /* glFramebufferTexture3D */
         564, /* glFramebufferTextureLayer */
         578, /* glGenFramebuffers */
         590, /* glGenRenderbuffers */
         599, /* glGenVertexArrays */
         602, /* glGenerateMipmap */
         627, /* glGetBooleani_v */
         682, /* glGetFragDataLocation */
         688, /* glGetFramebufferAttachmentParameteriv */
         710, /* glGetIntegeri_v */
         859, /* glGetRenderbufferParameteriv */
         878, /* glGetStringi */
         891, /* glGetTexParameterIiv */
         893, /* glGetTexParameterIuiv */
         919, /* glGetTransformFeedbackVarying */
         941, /* glGetUniformuiv */
         961, /* glGetVertexAttribIiv */
         963, /* glGetVertexAttribIuiv */
        1057, /* glIsEnabledi */
        1060, /* glIsFramebuffer */
        1079, /* glIsRenderbuffer */
        1093, /* glIsVertexArray */
        1138, /* glMapBufferRange */
        1679, /* glRenderbufferStorage */
        1681, /* glRenderbufferStorageMultisample */
        1901, /* glTexParameterIiv */
        1903, /* glTexParameterIuiv */
        1999, /* glTransformFeedbackVaryings */
        2018, /* glUniform1ui */
        2024, /* glUniform1uiv */
        2040, /* glUniform2ui */
        2046, /* glUniform2uiv */
        2062, /* glUniform3ui */
        2068, /* glUniform3uiv */
        2084, /* glUniform4ui */
        2090, /* glUniform4uiv */
        2319, /* glVertexAttribI1i */
        2321, /* glVertexAttribI1iv */
        2323, /* glVertexAttribI1ui */
        2325, /* glVertexAttribI1uiv */
        2327, /* glVertexAttribI2i */
        2329, /* glVertexAttribI2iv */
        2331, /* glVertexAttribI2ui */
        2333, /* glVertexAttribI2uiv */
        2335, /* glVertexAttribI3i */
        2337, /* glVertexAttribI3iv */
        2339, /* glVertexAttribI3ui */
        2341, /* glVertexAttribI3uiv */
        2343, /* glVertexAttribI4bv */
        2345, /* glVertexAttribI4i */
        2347, /* glVertexAttribI4iv */
        2349, /* glVertexAttribI4sv */
        2351, /* glVertexAttribI4ubv */
        2353, /* glVertexAttribI4ui */
        2355, /* glVertexAttribI4uiv */
        2357, /* glVertexAttribI4usv */
        2361  /* glVertexAttribIPointer */
    };
    uint32_t i;
    if(!context->VERSION_3_0) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_3_1(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          43, /* glBindBufferBase */
          48, /* glBindBufferRange */
         267, /* glCopyBufferSubData */
         415, /* glDrawArraysInstanced */
         432, /* glDrawElementsInstanced */
         615, /* glGetActiveUniformBlockName */
         616, /* glGetActiveUniformBlockiv */
         617, /* glGetActiveUniformName */
         618, /* glGetActiveUniformsiv */
         710, /* glGetIntegeri_v */
         925, /* glGetUniformBlockIndex */
         927, /* glGetUniformIndices */
        1465, /* glPrimitiveRestartIndex */
        1836, /* glTexBuffer */
        2092  /* glUniformBlockBinding */
    };
    uint32_t i;
    if(!context->VERSION_3_1) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_3_2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         183, /* glClientWaitSync */
         373, /* glDeleteSync */
         430, /* glDrawElementsBaseVertex */
         435, /* glDrawElementsInstancedBaseVertex */
         444, /* glDrawRangeElementsBaseVertex */
         496, /* glFenceSync */
         553, /* glFramebufferTexture */
         629, /* glGetBufferParameteri64v */
         707, /* glGetInteger64i_v */
         708, /* glGetInteger64v */
         750, /* glGetMultisamplefv */
         881, /* glGetSynciv */
        1085, /* glIsSync */
        1208, /* glMultiDrawElementsBaseVertex */
        1651, /* glProvokingVertex */
        1723, /* glSampleMaski */
        1892, /* glTexImage2DMultisample */
        1896, /* glTexImage3DMultisample */
        2487  /* glWaitSync */
    };
    uint32_t i;
    if(!context->VERSION_3_2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_3_3(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          55, /* glBindFragDataLocationIndexed */
          71, /* glBindSampler */
         369, /* glDeleteSamplers */
         592, /* glGenSamplers */
         681, /* glGetFragDataIndex */
         849, /* glGetQueryObjecti64v */
         853, /* glGetQueryObjectui64v */
         861, /* glGetSamplerParameterIiv */
         862, /* glGetSamplerParameterIuiv */
         863, /* glGetSamplerParameterfv */
         864, /* glGetSamplerParameteriv */
        1081, /* glIsSampler */
        1656, /* glQueryCounter */
        1726, /* glSamplerParameterIiv */
        1727, /* glSamplerParameterIuiv */
        1728, /* glSamplerParameterf */
        1729, /* glSamplerParameterfv */
        1730, /* glSamplerParameteri */
        1731, /* glSamplerParameteriv */
        2315, /* glVertexAttribDivisor */
        2401, /* glVertexAttribP1ui */
        2402, /* glVertexAttribP1uiv */
        2403, /* glVertexAttribP2ui */
        2404, /* glVertexAttribP2uiv */
        2405, /* glVertexAttribP3ui */
        2406, /* glVertexAttribP3uiv */
        2407, /* glVertexAttribP4ui */
        2408  /* glVertexAttribP4uiv */
    };
    uint32_t i;
    if(!context->VERSION_3_3) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_4_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          33, /* glBeginQueryIndexed */
          80, /* glBindTransformFeedback */
         112, /* glBlendEquationSeparatei */
         114, /* glBlendEquationi */
         122, /* glBlendFuncSeparatei */
         124, /* glBlendFunci */
         376, /* glDeleteTransformFeedbacks */
         414, /* glDrawArraysIndirect */
         431, /* glDrawElementsIndirect */
         447, /* glDrawTransformFeedback */
         450, /* glDrawTransformFeedbackStream */
         481, /* glEndQueryIndexed */
         597, /* glGenTransformFeedbacks */
         610, /* glGetActiveSubroutineName */
         611, /* glGetActiveSubroutineUniformName */
         612, /* glGetActiveSubroutineUniformiv */
         837, /* glGetProgramStageiv */
         848, /* glGetQueryIndexediv */
         879, /* glGetSubroutineIndex */
         880, /* glGetSubroutineUniformLocation */
         931, /* glGetUniformSubroutineuiv */
         932, /* glGetUniformdv */
        1090, /* glIsTransformFeedback */
        1191, /* glMinSampleShading */
        1398, /* glPatchParameterfv */
        1399, /* glPatchParameteri */
        1418, /* glPauseTransformFeedback */
        1714, /* glResumeTransformFeedback */
        2004, /* glUniform1d */
        2005, /* glUniform1dv */
        2026, /* glUniform2d */
        2027, /* glUniform2dv */
        2048, /* glUniform3d */
        2049, /* glUniform3dv */
        2070, /* glUniform4d */
        2071, /* glUniform4dv */
        2098, /* glUniformMatrix2dv */
        2101, /* glUniformMatrix2x3dv */
        2103, /* glUniformMatrix2x4dv */
        2105, /* glUniformMatrix3dv */
        2108, /* glUniformMatrix3x2dv */
        2110, /* glUniformMatrix3x4dv */
        2112, /* glUniformMatrix4dv */
        2115, /* glUniformMatrix4x2dv */
        2117, /* glUniformMatrix4x3dv */
        2119  /* glUniformSubroutinesuiv */
    };
    uint32_t i;
    if(!context->VERSION_4_0) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_4_1(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           3, /* glActiveShaderProgram */
          68, /* glBindProgramPipeline */
         165, /* glClearDepthf */
         321, /* glCreateShaderProgramv */
         361, /* glDeleteProgramPipelines */
         387, /* glDepthRangeArrayv */
         388, /* glDepthRangeIndexed */
         391, /* glDepthRangef */
         584, /* glGenProgramPipelines */
         667, /* glGetDoublei_v */
         677, /* glGetFloati_v */
         814, /* glGetProgramBinary */
         829, /* glGetProgramPipelineInfoLog */
         830, /* glGetProgramPipelineiv */
         869, /* glGetShaderPrecisionFormat */
         965, /* glGetVertexAttribLdv */
        1076, /* glIsProgramPipeline */
        1470, /* glProgramBinary */
        1504, /* glProgramParameteri */
        1512, /* glProgramUniform1d */
        1514, /* glProgramUniform1dv */
        1516, /* glProgramUniform1f */
        1518, /* glProgramUniform1fv */
        1520, /* glProgramUniform1i */
        1526, /* glProgramUniform1iv */
        1528, /* glProgramUniform1ui */
        1534, /* glProgramUniform1uiv */
        1536, /* glProgramUniform2d */
        1538, /* glProgramUniform2dv */
        1540, /* glProgramUniform2f */
        1542, /* glProgramUniform2fv */
        1544, /* glProgramUniform2i */
        1550, /* glProgramUniform2iv */
        1552, /* glProgramUniform2ui */
        1558, /* glProgramUniform2uiv */
        1560, /* glProgramUniform3d */
        1562, /* glProgramUniform3dv */
        1564, /* glProgramUniform3f */
        1566, /* glProgramUniform3fv */
        1568, /* glProgramUniform3i */
        1574, /* glProgramUniform3iv */
        1576, /* glProgramUniform3ui */
        1582, /* glProgramUniform3uiv */
        1584, /* glProgramUniform4d */
        1586, /* glProgramUniform4dv */
        1588, /* glProgramUniform4f */
        1590, /* glProgramUniform4fv */
        1592, /* glProgramUniform4i */
        1598, /* glProgramUniform4iv */
        1600, /* glProgramUniform4ui */
        1606, /* glProgramUniform4uiv */
        1612, /* glProgramUniformMatrix2dv */
        1614, /* glProgramUniformMatrix2fv */
        1616, /* glProgramUniformMatrix2x3dv */
        1618, /* glProgramUniformMatrix2x3fv */
        1620, /* glProgramUniformMatrix2x4dv */
        1622, /* glProgramUniformMatrix2x4fv */
        1624, /* glProgramUniformMatrix3dv */
        1626, /* glProgramUniformMatrix3fv */
        1628, /* glProgramUniformMatrix3x2dv */
        1630, /* glProgramUniformMatrix3x2fv */
        1632, /* glProgramUniformMatrix3x4dv */
        1634, /* glProgramUniformMatrix3x4fv */
        1636, /* glProgramUniformMatrix4dv */
        1638, /* glProgramUniformMatrix4fv */
        1640, /* glProgramUniformMatrix4x2dv */
        1642, /* glProgramUniformMatrix4x2fv */
        1644, /* glProgramUniformMatrix4x3dv */
        1646, /* glProgramUniformMatrix4x3fv */
        1677, /* glReleaseShaderCompiler */
        1734, /* glScissorArrayv */
        1737, /* glScissorIndexed */
        1738, /* glScissorIndexedv */
        1770, /* glShaderBinary */
        2133, /* glUseProgramStages */
        2148, /* glValidateProgramPipeline */
        2363, /* glVertexAttribL1d */
        2365, /* glVertexAttribL1dv */
        2373, /* glVertexAttribL2d */
        2375, /* glVertexAttribL2dv */
        2381, /* glVertexAttribL3d */
        2383, /* glVertexAttribL3dv */
        2389, /* glVertexAttribL4d */
        2391, /* glVertexAttribL4dv */
        2399, /* glVertexAttribLPointer */
        2480, /* glViewportArrayv */
        2481, /* glViewportIndexedf */
        2482  /* glViewportIndexedfv */
    };
    uint32_t i;
    if(!context->VERSION_4_1) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_4_2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          59, /* glBindImageTexture */
         417, /* glDrawArraysInstancedBaseInstance */
         434, /* glDrawElementsInstancedBaseInstance */
         436, /* glDrawElementsInstancedBaseVertexBaseInstance */
         448, /* glDrawTransformFeedbackInstanced */
         451, /* glDrawTransformFeedbackStreamInstanced */
         607, /* glGetActiveAtomicCounterBufferiv */
         716, /* glGetInternalformativ */
        1187, /* glMemoryBarrier */
        1912, /* glTexStorage1D */
        1914, /* glTexStorage2D */
        1917  /* glTexStorage3D */
    };
    uint32_t i;
    if(!context->VERSION_4_2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_4_3(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          84, /* glBindVertexBuffer */
         153, /* glClearBufferData */
         154, /* glClearBufferSubData */
         272, /* glCopyImageSubData */
         331, /* glDebugMessageCallback */
         334, /* glDebugMessageControl */
         337, /* glDebugMessageInsert */
         409, /* glDispatchCompute */
         411, /* glDispatchComputeIndirect */
         545, /* glFramebufferParameteri */
         662, /* glGetDebugMessageLog */
         691, /* glGetFramebufferParameteriv */
         715, /* glGetInternalformati64v */
         778, /* glGetObjectLabel */
         783, /* glGetObjectPtrLabel */
         812, /* glGetPointerv */
         820, /* glGetProgramInterfaceiv */
         831, /* glGetProgramResourceIndex */
         832, /* glGetProgramResourceLocation */
         833, /* glGetProgramResourceLocationIndex */
         834, /* glGetProgramResourceName */
         836, /* glGetProgramResourceiv */
        1041, /* glInvalidateBufferData */
        1042, /* glInvalidateBufferSubData */
        1043, /* glInvalidateFramebuffer */
        1046, /* glInvalidateSubFramebuffer */
        1047, /* glInvalidateTexImage */
        1048, /* glInvalidateTexSubImage */
        1200, /* glMultiDrawArraysIndirect */
        1210, /* glMultiDrawElementsIndirect */
        1388, /* glObjectLabel */
        1389, /* glObjectPtrLabel */
        1460, /* glPopDebugGroup */
        1654, /* glPushDebugGroup */
        1776, /* glShaderStorageBlockBinding */
        1839, /* glTexBufferRange */
        1916, /* glTexStorage2DMultisample */
        1919, /* glTexStorage3DMultisample */
        1993, /* glTextureView */
        2314, /* glVertexAttribBinding */
        2317, /* glVertexAttribFormat */
        2359, /* glVertexAttribIFormat */
        2397, /* glVertexAttribLFormat */
        2430  /* glVertexBindingDivisor */
    };
    uint32_t i;
    if(!context->VERSION_4_3) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_4_4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          51, /* glBindBuffersBase */
          52, /* glBindBuffersRange */
          61, /* glBindImageTextures */
          72, /* glBindSamplers */
          79, /* glBindTextures */
          85, /* glBindVertexBuffers */
         139, /* glBufferStorage */
         177, /* glClearTexImage */
         178  /* glClearTexSubImage */
    };
    uint32_t i;
    if(!context->VERSION_4_4) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_4_5(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          77, /* glBindTextureUnit */
         131, /* glBlitNamedFramebuffer */
         147, /* glCheckNamedFramebufferStatus */
         168, /* glClearNamedBufferData */
         170, /* glClearNamedBufferSubData */
         172, /* glClearNamedFramebufferfi */
         173, /* glClearNamedFramebufferfv */
         174, /* glClearNamedFramebufferiv */
         175, /* glClearNamedFramebufferuiv */
         184, /* glClipControl */
         251, /* glCompressedTextureSubImage1D */
         253, /* glCompressedTextureSubImage2D */
         255, /* glCompressedTextureSubImage3D */
         279, /* glCopyNamedBufferSubData */
         293, /* glCopyTextureSubImage1D */
         295, /* glCopyTextureSubImage2D */
         297, /* glCopyTextureSubImage3D */
         305, /* glCreateBuffers */
         307, /* glCreateFramebuffers */
         312, /* glCreateProgramPipelines */
         314, /* glCreateQueries */
         315, /* glCreateRenderbuffers */
         316, /* glCreateSamplers */
         324, /* glCreateTextures */
         325, /* glCreateTransformFeedbacks */
         326, /* glCreateVertexArrays */
         402, /* glDisableVertexArrayAttrib */
         465, /* glEnableVertexArrayAttrib */
         507, /* glFlushMappedNamedBufferRange */
         605, /* glGenerateTextureMipmap */
         654, /* glGetCompressedTextureImage */
         656, /* glGetCompressedTextureSubImage */
         694, /* glGetGraphicsResetStatus */
         752, /* glGetNamedBufferParameteri64v */
         753, /* glGetNamedBufferParameteriv */
         756, /* glGetNamedBufferPointerv */
         758, /* glGetNamedBufferSubData */
         760, /* glGetNamedFramebufferAttachmentParameteriv */
         763, /* glGetNamedFramebufferParameteriv */
         771, /* glGetNamedRenderbufferParameteriv */
         844, /* glGetQueryBufferObjecti64v */
         845, /* glGetQueryBufferObjectiv */
         846, /* glGetQueryBufferObjectui64v */
         847, /* glGetQueryBufferObjectuiv */
         901, /* glGetTextureImage */
         903, /* glGetTextureLevelParameterfv */
         905, /* glGetTextureLevelParameteriv */
         907, /* glGetTextureParameterIiv */
         909, /* glGetTextureParameterIuiv */
         911, /* glGetTextureParameterfv */
         913, /* glGetTextureParameteriv */
         917, /* glGetTextureSubImage */
         922, /* glGetTransformFeedbacki64_v */
         923, /* glGetTransformFeedbacki_v */
         924, /* glGetTransformFeedbackiv */
         952, /* glGetVertexArrayIndexed64iv */
         953, /* glGetVertexArrayIndexediv */
         958, /* glGetVertexArrayiv */
         991, /* glGetnCompressedTexImage */
         993, /* glGetnTexImage */
         995, /* glGetnUniformdv */
         997, /* glGetnUniformfv */
        1000, /* glGetnUniformiv */
        1003, /* glGetnUniformuiv */
        1044, /* glInvalidateNamedFramebufferData */
        1045, /* glInvalidateNamedFramebufferSubData */
        1142, /* glMapNamedBuffer */
        1144, /* glMapNamedBufferRange */
        1188, /* glMemoryBarrierByRegion */
        1317, /* glNamedBufferData */
        1322, /* glNamedBufferStorage */
        1326, /* glNamedBufferSubData */
        1329, /* glNamedFramebufferDrawBuffer */
        1330, /* glNamedFramebufferDrawBuffers */
        1331, /* glNamedFramebufferParameteri */
        1333, /* glNamedFramebufferReadBuffer */
        1334, /* glNamedFramebufferRenderbuffer */
        1339, /* glNamedFramebufferTexture */
        1345, /* glNamedFramebufferTextureLayer */
        1360, /* glNamedRenderbufferStorage */
        1362, /* glNamedRenderbufferStorageMultisample */
        1671, /* glReadnPixels */
        1938, /* glTextureBarrier */
        1940, /* glTextureBuffer */
        1942, /* glTextureBufferRange */
        1957, /* glTextureParameterIiv */
        1959, /* glTextureParameterIuiv */
        1961, /* glTextureParameterf */
        1963, /* glTextureParameterfv */
        1965, /* glTextureParameteri */
        1967, /* glTextureParameteriv */
        1971, /* glTextureStorage1D */
        1973, /* glTextureStorage2D */
        1975, /* glTextureStorage2DMultisample */
        1977, /* glTextureStorage3D */
        1979, /* glTextureStorage3DMultisample */
        1987, /* glTextureSubImage1D */
        1989, /* glTextureSubImage2D */
        1991, /* glTextureSubImage3D */
        1996, /* glTransformFeedbackBufferBase */
        1997, /* glTransformFeedbackBufferRange */
        2125, /* glUnmapNamedBuffer */
        2177, /* glVertexArrayAttribBinding */
        2178, /* glVertexArrayAttribFormat */
        2179, /* glVertexArrayAttribIFormat */
        2180, /* glVertexArrayAttribLFormat */
        2182, /* glVertexArrayBindingDivisor */
        2185, /* glVertexArrayElementBuffer */
        2204, /* glVertexArrayVertexBuffer */
        2205  /* glVertexArrayVertexBuffers */
    };
    uint32_t i;
    if(!context->VERSION_4_5) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_VERSION_4_6(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1204, /* glMultiDrawArraysIndirectCount */
        1214, /* glMultiDrawElementsIndirectCount */
        1456, /* glPolygonOffsetClamp */
        1786  /* glSpecializeShader */
    };
    uint32_t i;
    if(!context->VERSION_4_6) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ES_VERSION_2_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           5, /* glActiveTexture */
          23, /* glAttachShader */
          39, /* glBindAttribLocation */
          41, /* glBindBuffer */
          57, /* glBindFramebuffer */
          69, /* glBindRenderbuffer */
          75, /* glBindTexture */
         103, /* glBlendColor */
         106, /* glBlendEquation */
         109, /* glBlendEquationSeparate */
         116, /* glBlendFunc */
         118, /* glBlendFuncSeparate */
         134, /* glBufferData */
         142, /* glBufferSubData */
         145, /* glCheckFramebufferStatus */
         151, /* glClear */
         159, /* glClearColor */
         165, /* glClearDepthf */
         176, /* glClearStencil */
         207, /* glColorMask */
         227, /* glCompileShader */
         238, /* glCompressedTexImage2D */
         244, /* glCompressedTexSubImage2D */
         283, /* glCopyTexImage2D */
         287, /* glCopyTexSubImage2D */
         310, /* glCreateProgram */
         318, /* glCreateShader */
         327, /* glCullFace */
         344, /* glDeleteBuffers */
         350, /* glDeleteFramebuffers */
         360, /* glDeleteProgram */
         367, /* glDeleteRenderbuffers */
         371, /* glDeleteShader */
         374, /* glDeleteTextures */
         383, /* glDepthFunc */
         384, /* glDepthMask */
         391, /* glDepthRangef */
         395, /* glDetachShader */
         397, /* glDisable */
         406, /* glDisableVertexAttribArray */
         412, /* glDrawArrays */
         429, /* glDrawElements */
         460, /* glEnable */
         469, /* glEnableVertexAttribArray */
         498, /* glFinish */
         504, /* glFlush */
         548, /* glFramebufferRenderbuffer */
         556, /* glFramebufferTexture2D */
         569, /* glFrontFace */
         573, /* glGenBuffers */
         578, /* glGenFramebuffers */
         590, /* glGenRenderbuffers */
         595, /* glGenTextures */
         602, /* glGenerateMipmap */
         608, /* glGetActiveAttrib */
         613, /* glGetActiveUniform */
         623, /* glGetAttachedShaders */
         624, /* glGetAttribLocation */
         628, /* glGetBooleanv */
         630, /* glGetBufferParameteriv */
         670, /* glGetError */
         679, /* glGetFloatv */
         688, /* glGetFramebufferAttachmentParameteriv */
         713, /* glGetIntegerv */
         819, /* glGetProgramInfoLog */
         841, /* glGetProgramiv */
         859, /* glGetRenderbufferParameteriv */
         868, /* glGetShaderInfoLog */
         869, /* glGetShaderPrecisionFormat */
         870, /* glGetShaderSource */
         872, /* glGetShaderiv */
         877, /* glGetString */
         896, /* glGetTexParameterfv */
         897, /* glGetTexParameteriv */
         928, /* glGetUniformLocation */
         933, /* glGetUniformfv */
         937, /* glGetUniformiv */
         970, /* glGetVertexAttribPointerv */
         976, /* glGetVertexAttribfv */
         979, /* glGetVertexAttribiv */
        1013, /* glHint */
        1051, /* glIsBuffer */
        1055, /* glIsEnabled */
        1060, /* glIsFramebuffer */
        1073, /* glIsProgram */
        1079, /* glIsRenderbuffer */
        1083, /* glIsShader */
        1086, /* glIsTexture */
        1105, /* glLineWidth */
        1107, /* glLinkProgram */
        1423, /* glPixelStorei */
        1455, /* glPolygonOffset */
        1670, /* glReadPixels */
        1677, /* glReleaseShaderCompiler */
        1679, /* glRenderbufferStorage */
        1717, /* glSampleCoverage */
        1733, /* glScissor */
        1770, /* glShaderBinary */
        1774, /* glShaderSource */
        1797, /* glStencilFunc */
        1798, /* glStencilFuncSeparate */
        1800, /* glStencilMask */
        1801, /* glStencilMaskSeparate */
        1802, /* glStencilOp */
        1803, /* glStencilOpSeparate */
        1890, /* glTexImage2D */
        1905, /* glTexParameterf */
        1906, /* glTexParameterfv */
        1907, /* glTexParameteri */
        1908, /* glTexParameteriv */
        1932, /* glTexSubImage2D */
        2006, /* glUniform1f */
        2008, /* glUniform1fv */
        2010, /* glUniform1i */
        2016, /* glUniform1iv */
        2028, /* glUniform2f */
        2030, /* glUniform2fv */
        2032, /* glUniform2i */
        2038, /* glUniform2iv */
        2050, /* glUniform3f */
        2052, /* glUniform3fv */
        2054, /* glUniform3i */
        2060, /* glUniform3iv */
        2072, /* glUniform4f */
        2074, /* glUniform4fv */
        2076, /* glUniform4i */
        2082, /* glUniform4iv */
        2099, /* glUniformMatrix2fv */
        2106, /* glUniformMatrix3fv */
        2113, /* glUniformMatrix4fv */
        2131, /* glUseProgram */
        2146, /* glValidateProgram */
        2213, /* glVertexAttrib1f */
        2216, /* glVertexAttrib1fv */
        2233, /* glVertexAttrib2f */
        2236, /* glVertexAttrib2fv */
        2253, /* glVertexAttrib3f */
        2256, /* glVertexAttrib3fv */
        2289, /* glVertexAttrib4f */
        2292, /* glVertexAttrib4fv */
        2410, /* glVertexAttribPointer */
        2479  /* glViewport */
    };
    uint32_t i;
    if(!context->ES_VERSION_2_0) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ES_VERSION_3_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          31, /* glBeginQuery */
          34, /* glBeginTransformFeedback */
          43, /* glBindBufferBase */
          48, /* glBindBufferRange */
          71, /* glBindSampler */
          80, /* glBindTransformFeedback */
          82, /* glBindVertexArray */
         127, /* glBlitFramebuffer */
         155, /* glClearBufferfi */
         156, /* glClearBufferfv */
         157, /* glClearBufferiv */
         158, /* glClearBufferuiv */
         183, /* glClientWaitSync */
         240, /* glCompressedTexImage3D */
         246, /* glCompressedTexSubImage3D */
         267, /* glCopyBufferSubData */
         289, /* glCopyTexSubImage3D */
         364, /* glDeleteQueries */
         369, /* glDeleteSamplers */
         373, /* glDeleteSync */
         376, /* glDeleteTransformFeedbacks */
         378, /* glDeleteVertexArrays */
         415, /* glDrawArraysInstanced */
         420, /* glDrawBuffers */
         432, /* glDrawElementsInstanced */
         443, /* glDrawRangeElements */
         479, /* glEndQuery */
         482, /* glEndTransformFeedback */
         496, /* glFenceSync */
         505, /* glFlushMappedBufferRange */
         564, /* glFramebufferTextureLayer */
         587, /* glGenQueries */
         592, /* glGenSamplers */
         597, /* glGenTransformFeedbacks */
         599, /* glGenVertexArrays */
         615, /* glGetActiveUniformBlockName */
         616, /* glGetActiveUniformBlockiv */
         618, /* glGetActiveUniformsiv */
         629, /* glGetBufferParameteri64v */
         633, /* glGetBufferPointerv */
         682, /* glGetFragDataLocation */
         707, /* glGetInteger64i_v */
         708, /* glGetInteger64v */
         710, /* glGetIntegeri_v */
         716, /* glGetInternalformativ */
         814, /* glGetProgramBinary */
         855, /* glGetQueryObjectuiv */
         857, /* glGetQueryiv */
         863, /* glGetSamplerParameterfv */
         864, /* glGetSamplerParameteriv */
         878, /* glGetStringi */
         881, /* glGetSynciv */
         919, /* glGetTransformFeedbackVarying */
         925, /* glGetUniformBlockIndex */
         927, /* glGetUniformIndices */
         941, /* glGetUniformuiv */
         961, /* glGetVertexAttribIiv */
         963, /* glGetVertexAttribIuiv */
        1043, /* glInvalidateFramebuffer */
        1046, /* glInvalidateSubFramebuffer */
        1077, /* glIsQuery */
        1081, /* glIsSampler */
        1085, /* glIsSync */
        1090, /* glIsTransformFeedback */
        1093, /* glIsVertexArray */
        1138, /* glMapBufferRange */
        1418, /* glPauseTransformFeedback */
        1470, /* glProgramBinary */
        1504, /* glProgramParameteri */
        1668, /* glReadBuffer */
        1681, /* glRenderbufferStorageMultisample */
        1714, /* glResumeTransformFeedback */
        1728, /* glSamplerParameterf */
        1729, /* glSamplerParameterfv */
        1730, /* glSamplerParameteri */
        1731, /* glSamplerParameteriv */
        1894, /* glTexImage3D */
        1914, /* glTexStorage2D */
        1917, /* glTexStorage3D */
        1934, /* glTexSubImage3D */
        1999, /* glTransformFeedbackVaryings */
        2018, /* glUniform1ui */
        2024, /* glUniform1uiv */
        2040, /* glUniform2ui */
        2046, /* glUniform2uiv */
        2062, /* glUniform3ui */
        2068, /* glUniform3uiv */
        2084, /* glUniform4ui */
        2090, /* glUniform4uiv */
        2092, /* glUniformBlockBinding */
        2102, /* glUniformMatrix2x3fv */
        2104, /* glUniformMatrix2x4fv */
        2109, /* glUniformMatrix3x2fv */
        2111, /* glUniformMatrix3x4fv */
        2116, /* glUniformMatrix4x2fv */
        2118, /* glUniformMatrix4x3fv */
        2123, /* glUnmapBuffer */
        2315, /* glVertexAttribDivisor */
        2345, /* glVertexAttribI4i */
        2347, /* glVertexAttribI4iv */
        2353, /* glVertexAttribI4ui */
        2355, /* glVertexAttribI4uiv */
        2361, /* glVertexAttribIPointer */
        2487  /* glWaitSync */
    };
    uint32_t i;
    if(!context->ES_VERSION_3_0) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ES_VERSION_3_1(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           3, /* glActiveShaderProgram */
          59, /* glBindImageTexture */
          68, /* glBindProgramPipeline */
          84, /* glBindVertexBuffer */
         321, /* glCreateShaderProgramv */
         361, /* glDeleteProgramPipelines */
         409, /* glDispatchCompute */
         411, /* glDispatchComputeIndirect */
         414, /* glDrawArraysIndirect */
         431, /* glDrawElementsIndirect */
         545, /* glFramebufferParameteri */
         584, /* glGenProgramPipelines */
         627, /* glGetBooleani_v */
         691, /* glGetFramebufferParameteriv */
         750, /* glGetMultisamplefv */
         820, /* glGetProgramInterfaceiv */
         829, /* glGetProgramPipelineInfoLog */
         830, /* glGetProgramPipelineiv */
         831, /* glGetProgramResourceIndex */
         832, /* glGetProgramResourceLocation */
         834, /* glGetProgramResourceName */
         836, /* glGetProgramResourceiv */
         888, /* glGetTexLevelParameterfv */
         889, /* glGetTexLevelParameteriv */
        1076, /* glIsProgramPipeline */
        1187, /* glMemoryBarrier */
        1188, /* glMemoryBarrierByRegion */
        1516, /* glProgramUniform1f */
        1518, /* glProgramUniform1fv */
        1520, /* glProgramUniform1i */
        1526, /* glProgramUniform1iv */
        1528, /* glProgramUniform1ui */
        1534, /* glProgramUniform1uiv */
        1540, /* glProgramUniform2f */
        1542, /* glProgramUniform2fv */
        1544, /* glProgramUniform2i */
        1550, /* glProgramUniform2iv */
        1552, /* glProgramUniform2ui */
        1558, /* glProgramUniform2uiv */
        1564, /* glProgramUniform3f */
        1566, /* glProgramUniform3fv */
        1568, /* glProgramUniform3i */
        1574, /* glProgramUniform3iv */
        1576, /* glProgramUniform3ui */
        1582, /* glProgramUniform3uiv */
        1588, /* glProgramUniform4f */
        1590, /* glProgramUniform4fv */
        1592, /* glProgramUniform4i */
        1598, /* glProgramUniform4iv */
        1600, /* glProgramUniform4ui */
        1606, /* glProgramUniform4uiv */
        1614, /* glProgramUniformMatrix2fv */
        1618, /* glProgramUniformMatrix2x3fv */
        1622, /* glProgramUniformMatrix2x4fv */
        1626, /* glProgramUniformMatrix3fv */
        1630, /* glProgramUniformMatrix3x2fv */
        1634, /* glProgramUniformMatrix3x4fv */
        1638, /* glProgramUniformMatrix4fv */
        1642, /* glProgramUniformMatrix4x2fv */
        1646, /* glProgramUniformMatrix4x3fv */
        1723, /* glSampleMaski */
        1916, /* glTexStorage2DMultisample */
        2133, /* glUseProgramStages */
        2148, /* glValidateProgramPipeline */
        2314, /* glVertexAttribBinding */
        2317, /* glVertexAttribFormat */
        2359, /* glVertexAttribIFormat */
        2430  /* glVertexBindingDivisor */
    };
    uint32_t i;
    if(!context->ES_VERSION_3_1) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ES_VERSION_3_2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2550, /* glBlendBarrier */
         112, /* glBlendEquationSeparatei */
         114, /* glBlendEquationi */
         122, /* glBlendFuncSeparatei */
         124, /* glBlendFunci */
         209, /* glColorMaski */
         272, /* glCopyImageSubData */
         331, /* glDebugMessageCallback */
         334, /* glDebugMessageControl */
         337, /* glDebugMessageInsert */
         408, /* glDisablei */
         430, /* glDrawElementsBaseVertex */
         435, /* glDrawElementsInstancedBaseVertex */
         444, /* glDrawRangeElementsBaseVertex */
         471, /* glEnablei */
         553, /* glFramebufferTexture */
         662, /* glGetDebugMessageLog */
         694, /* glGetGraphicsResetStatus */
         778, /* glGetObjectLabel */
         783, /* glGetObjectPtrLabel */
         812, /* glGetPointerv */
         861, /* glGetSamplerParameterIiv */
         862, /* glGetSamplerParameterIuiv */
         891, /* glGetTexParameterIiv */
         893, /* glGetTexParameterIuiv */
         997, /* glGetnUniformfv */
        1000, /* glGetnUniformiv */
        1003, /* glGetnUniformuiv */
        1057, /* glIsEnabledi */
        1191, /* glMinSampleShading */
        1388, /* glObjectLabel */
        1389, /* glObjectPtrLabel */
        1399, /* glPatchParameteri */
        1460, /* glPopDebugGroup */
        2800, /* glPrimitiveBoundingBox */
        1654, /* glPushDebugGroup */
        1671, /* glReadnPixels */
        1726, /* glSamplerParameterIiv */
        1727, /* glSamplerParameterIuiv */
        1836, /* glTexBuffer */
        1839, /* glTexBufferRange */
        1901, /* glTexParameterIiv */
        1903, /* glTexParameterIuiv */
        1919  /* glTexStorage3DMultisample */
    };
    uint32_t i;
    if(!context->ES_VERSION_3_2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_3DFX_tbuffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1829  /* glTbufferMask3DFX */
    };
    uint32_t i;
    if(!context->_3DFX_tbuffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_debug_output(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         332, /* glDebugMessageCallbackAMD */
         336, /* glDebugMessageEnableAMD */
         338, /* glDebugMessageInsertAMD */
         663  /* glGetDebugMessageLogAMD */
    };
    uint32_t i;
    if(!context->AMD_debug_output) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_draw_buffers_blend(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         108, /* glBlendEquationIndexedAMD */
         111, /* glBlendEquationSeparateIndexedAMD */
         117, /* glBlendFuncIndexedAMD */
         121  /* glBlendFuncSeparateIndexedAMD */
    };
    uint32_t i;
    if(!context->AMD_draw_buffers_blend) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_framebuffer_multisample_advanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1363, /* glNamedRenderbufferStorageMultisampleAdvancedAMD */
        1682  /* glRenderbufferStorageMultisampleAdvancedAMD */
    };
    uint32_t i;
    if(!context->AMD_framebuffer_multisample_advanced) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_framebuffer_sample_positions(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         552, /* glFramebufferSamplePositionsfvAMD */
         690, /* glGetFramebufferParameterfvAMD */
         762, /* glGetNamedFramebufferParameterfvAMD */
        1338  /* glNamedFramebufferSamplePositionsfvAMD */
    };
    uint32_t i;
    if(!context->AMD_framebuffer_sample_positions) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_gpu_shader_int64(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         936, /* glGetUniformi64vNV */
         940, /* glGetUniformui64vNV */
        1522, /* glProgramUniform1i64NV */
        1524, /* glProgramUniform1i64vNV */
        1530, /* glProgramUniform1ui64NV */
        1532, /* glProgramUniform1ui64vNV */
        1546, /* glProgramUniform2i64NV */
        1548, /* glProgramUniform2i64vNV */
        1554, /* glProgramUniform2ui64NV */
        1556, /* glProgramUniform2ui64vNV */
        1570, /* glProgramUniform3i64NV */
        1572, /* glProgramUniform3i64vNV */
        1578, /* glProgramUniform3ui64NV */
        1580, /* glProgramUniform3ui64vNV */
        1594, /* glProgramUniform4i64NV */
        1596, /* glProgramUniform4i64vNV */
        1602, /* glProgramUniform4ui64NV */
        1604, /* glProgramUniform4ui64vNV */
        2012, /* glUniform1i64NV */
        2014, /* glUniform1i64vNV */
        2020, /* glUniform1ui64NV */
        2022, /* glUniform1ui64vNV */
        2034, /* glUniform2i64NV */
        2036, /* glUniform2i64vNV */
        2042, /* glUniform2ui64NV */
        2044, /* glUniform2ui64vNV */
        2056, /* glUniform3i64NV */
        2058, /* glUniform3i64vNV */
        2064, /* glUniform3ui64NV */
        2066, /* glUniform3ui64vNV */
        2078, /* glUniform4i64NV */
        2080, /* glUniform4i64vNV */
        2086, /* glUniform4ui64NV */
        2088  /* glUniform4ui64vNV */
    };
    uint32_t i;
    if(!context->AMD_gpu_shader_int64) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_interleaved_elements(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2409  /* glVertexAttribParameteriAMD */
    };
    uint32_t i;
    if(!context->AMD_interleaved_elements) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_multi_draw_indirect(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1201, /* glMultiDrawArraysIndirectAMD */
        1211  /* glMultiDrawElementsIndirectAMD */
    };
    uint32_t i;
    if(!context->AMD_multi_draw_indirect) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_name_gen_delete(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         354, /* glDeleteNamesAMD */
         580, /* glGenNamesAMD */
        1065  /* glIsNameAMD */
    };
    uint32_t i;
    if(!context->AMD_name_gen_delete) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_occlusion_query_event(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1658  /* glQueryObjectParameteruiAMD */
    };
    uint32_t i;
    if(!context->AMD_occlusion_query_event) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_performance_monitor(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          29, /* glBeginPerfMonitorAMD */
         358, /* glDeletePerfMonitorsAMD */
         477, /* glEndPerfMonitorAMD */
         583, /* glGenPerfMonitorsAMD */
         796, /* glGetPerfMonitorCounterDataAMD */
         797, /* glGetPerfMonitorCounterInfoAMD */
         798, /* glGetPerfMonitorCounterStringAMD */
         799, /* glGetPerfMonitorCountersAMD */
         800, /* glGetPerfMonitorGroupStringAMD */
         801, /* glGetPerfMonitorGroupsAMD */
        1760  /* glSelectPerfMonitorCountersAMD */
    };
    uint32_t i;
    if(!context->AMD_performance_monitor) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_sample_positions(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1769  /* glSetMultisamplefvAMD */
    };
    uint32_t i;
    if(!context->AMD_sample_positions) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_sparse_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1929, /* glTexStorageSparseAMD */
        1986  /* glTextureStorageSparseAMD */
    };
    uint32_t i;
    if(!context->AMD_sparse_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_stencil_operation_extended(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1805  /* glStencilOpValueAMD */
    };
    uint32_t i;
    if(!context->AMD_stencil_operation_extended) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_AMD_vertex_shader_tessellator(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1830, /* glTessellationFactorAMD */
        1831  /* glTessellationModeAMD */
    };
    uint32_t i;
    if(!context->AMD_vertex_shader_tessellator) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_base_vertex_base_instance(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2607, /* glDrawArraysInstancedBaseInstanceANGLE */
        2617, /* glDrawElementsInstancedBaseVertexBaseInstanceANGLE */
        2786, /* glMultiDrawArraysInstancedBaseInstanceANGLE */
        2791  /* glMultiDrawElementsInstancedBaseVertexBaseInstanceANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_base_vertex_base_instance) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_copy_texture_3d(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2579, /* glCopySubTexture3DANGLE */
        2582  /* glCopyTexture3DANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_copy_texture_3d) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_framebuffer_blit(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2559  /* glBlitFramebufferANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_framebuffer_blit) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_framebuffer_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2816  /* glRenderbufferStorageMultisampleANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_framebuffer_multisample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_get_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2679, /* glGetCompressedTexImageANGLE */
        2725, /* glGetRenderbufferImageANGLE */
        2737  /* glGetTexImageANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_get_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_get_tex_level_parameter(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2738, /* glGetTexLevelParameterfvANGLE */
        2740  /* glGetTexLevelParameterivANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_get_tex_level_parameter) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_instanced_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2606, /* glDrawArraysInstancedANGLE */
        2615, /* glDrawElementsInstancedANGLE */
        2877  /* glVertexAttribDivisorANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_instanced_arrays) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_logic_op(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2775  /* glLogicOpANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_logic_op) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_low_latency(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2774, /* glLatencyMarkerANGLE */
        2777, /* glLowLatencyModeANGLE */
        2778  /* glLowLatencyWaitANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_low_latency) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_memory_object_flags(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1925, /* glTexStorageMemFlags2DANGLE */
        1926, /* glTexStorageMemFlags2DMultisampleANGLE */
        1927, /* glTexStorageMemFlags3DANGLE */
        1928  /* glTexStorageMemFlags3DMultisampleANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_memory_object_flags) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_memory_object_fuchsia(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1024  /* glImportMemoryZirconHandleANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_memory_object_fuchsia) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_multi_draw(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2783, /* glMultiDrawArraysANGLE */
        2785, /* glMultiDrawArraysInstancedANGLE */
        2787, /* glMultiDrawElementsANGLE */
        2790  /* glMultiDrawElementsInstancedANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_multi_draw) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_polygon_mode(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2797  /* glPolygonModeANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_polygon_mode) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_provoking_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2806  /* glProvokingVertexANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_provoking_vertex) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_request_extension(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2601, /* glDisableExtensionANGLE */
        2820  /* glRequestExtensionANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_request_extension) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_robust_client_memory(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2570, /* glCompressedTexImage2DRobustANGLE */
        2572, /* glCompressedTexImage3DRobustANGLE */
        2573, /* glCompressedTexSubImage2DRobustANGLE */
        2575, /* glCompressedTexSubImage3DRobustANGLE */
        2672, /* glGetActiveUniformBlockivRobustANGLE */
        2673, /* glGetBooleani_vRobustANGLE */
        2674, /* glGetBooleanvRobustANGLE */
        2675, /* glGetBufferParameteri64vRobustANGLE */
        2676, /* glGetBufferParameterivRobustANGLE */
        2678, /* glGetBufferPointervRobustANGLE */
        2685, /* glGetFloatvRobustANGLE */
        2688, /* glGetFramebufferAttachmentParameterivRobustANGLE */
        2689, /* glGetFramebufferParameterivRobustANGLE */
        2697, /* glGetInteger64i_vRobustANGLE */
        2700, /* glGetInteger64vRobustANGLE */
        2702, /* glGetIntegeri_vRobustANGLE */
        2703, /* glGetIntegervRobustANGLE */
        2704, /* glGetInternalformativRobustANGLE */
        2706, /* glGetMultisamplefvRobustANGLE */
        2710, /* glGetPointervRobustANGLERobustANGLE */
        2712, /* glGetProgramInterfaceivRobustANGLE */
        2716, /* glGetProgramivRobustANGLE */
        2717, /* glGetQueryObjecti64vRobustANGLE */
        2719, /* glGetQueryObjectivRobustANGLE */
        2720, /* glGetQueryObjectui64vRobustANGLE */
        2722, /* glGetQueryObjectuivRobustANGLE */
        2724, /* glGetQueryivRobustANGLE */
        2726, /* glGetRenderbufferParameterivRobustANGLE */
        2729, /* glGetSamplerParameterIivRobustANGLE */
        2732, /* glGetSamplerParameterIuivRobustANGLE */
        2733, /* glGetSamplerParameterfvRobustANGLE */
        2734, /* glGetSamplerParameterivRobustANGLE */
        2735, /* glGetShaderivRobustANGLE */
        2739, /* glGetTexLevelParameterfvRobustANGLE */
        2741, /* glGetTexLevelParameterivRobustANGLE */
        2743, /* glGetTexParameterIivRobustANGLE */
        2745, /* glGetTexParameterIuivRobustANGLE */
        2746, /* glGetTexParameterfvRobustANGLE */
        2747, /* glGetTexParameterivRobustANGLE */
        2751, /* glGetUniformfvRobustANGLE */
        2752, /* glGetUniformivRobustANGLE */
        2753, /* glGetUniformuivRobustANGLE */
        2754, /* glGetVertexAttribIivRobustANGLE */
        2755, /* glGetVertexAttribIuivRobustANGLE */
        2756, /* glGetVertexAttribPointervRobustANGLE */
        2757, /* glGetVertexAttribfvRobustANGLE */
        2758, /* glGetVertexAttribivRobustANGLE */
        2761, /* glGetnUniformfvRobustANGLE */
        2764, /* glGetnUniformivRobustANGLE */
        2766, /* glGetnUniformuivRobustANGLE */
        2811, /* glReadPixelsRobustANGLE */
        2814, /* glReadnPixelsRobustANGLE */
        2825, /* glSamplerParameterIivRobustANGLE */
        2828, /* glSamplerParameterIuivRobustANGLE */
        2829, /* glSamplerParameterfvRobustANGLE */
        2830, /* glSamplerParameterivRobustANGLE */
        2846, /* glTexImage2DRobustANGLE */
        2848, /* glTexImage3DRobustANGLE */
        2851, /* glTexParameterIivRobustANGLE */
        2853, /* glTexParameterIuivRobustANGLE */
        2854, /* glTexParameterfvRobustANGLE */
        2855, /* glTexParameterivRobustANGLE */
        2860, /* glTexSubImage2DRobustANGLE */
        2862  /* glTexSubImage3DRobustANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_robust_client_memory) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_semaphore_fuchsia(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1028  /* glImportSemaphoreZirconHandleANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_semaphore_fuchsia) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_shader_pixel_local_storage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2544, /* glBeginPixelLocalStorageANGLE */
        2632, /* glEndPixelLocalStorageANGLE */
        2653, /* glFramebufferMemorylessPixelLocalStorageANGLE */
        2654, /* glFramebufferPixelLocalClearValuefvANGLE */
        2655, /* glFramebufferPixelLocalClearValueivANGLE */
        2656, /* glFramebufferPixelLocalClearValueuivANGLE */
        2657, /* glFramebufferPixelLocalStorageInterruptANGLE */
        2658, /* glFramebufferPixelLocalStorageRestoreANGLE */
        2668, /* glFramebufferTexturePixelLocalStorageANGLE */
        2690, /* glGetFramebufferPixelLocalStorageParameterfvANGLE */
        2691, /* glGetFramebufferPixelLocalStorageParameterfvRobustANGLE */
        2692, /* glGetFramebufferPixelLocalStorageParameterivANGLE */
        2693, /* glGetFramebufferPixelLocalStorageParameterivRobustANGLE */
        2796  /* glPixelLocalStorageBarrierANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_shader_pixel_local_storage) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_texture_external_update(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1049, /* glInvalidateTextureANGLE */
        1891  /* glTexImage2DExternalANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_texture_external_update) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_texture_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2705, /* glGetMultisamplefvANGLE */
        2738, /* glGetTexLevelParameterfvANGLE */
        2740, /* glGetTexLevelParameterivANGLE */
        2822, /* glSampleMaskiANGLE */
        2856  /* glTexStorage2DMultisampleANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_texture_multisample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_translated_shader_source(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2750  /* glGetTranslatedShaderSourceANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_translated_shader_source) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_vulkan_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2541, /* glAcquireTexturesANGLE */
        2815  /* glReleaseTexturesANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_vulkan_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_copy_texture_levels(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2584  /* glCopyTextureLevelsAPPLE */
    };
    uint32_t i;
    if(!context->APPLE_copy_texture_levels) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_element_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         427, /* glDrawElementArrayAPPLE */
         441, /* glDrawRangeElementArrayAPPLE */
         458, /* glElementPointerAPPLE */
        1206, /* glMultiDrawElementArrayAPPLE */
        1218  /* glMultiDrawRangeElementArrayAPPLE */
    };
    uint32_t i;
    if(!context->APPLE_element_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_fence(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         347, /* glDeleteFencesAPPLE */
         500, /* glFinishFenceAPPLE */
         502, /* glFinishObjectAPPLE */
         575, /* glGenFencesAPPLE */
        1058, /* glIsFenceAPPLE */
        1764, /* glSetFenceAPPLE */
        1832, /* glTestFenceAPPLE */
        1834  /* glTestObjectAPPLE */
    };
    uint32_t i;
    if(!context->APPLE_fence) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_flush_buffer_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         138, /* glBufferParameteriAPPLE */
         506  /* glFlushMappedBufferRangeAPPLE */
    };
    uint32_t i;
    if(!context->APPLE_flush_buffer_range) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_framebuffer_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2817, /* glRenderbufferStorageMultisampleAPPLE */
        2821  /* glResolveMultisampleFramebufferAPPLE */
    };
    uint32_t i;
    if(!context->APPLE_framebuffer_multisample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_object_purgeable(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         781, /* glGetObjectParameterivAPPLE */
        1390, /* glObjectPurgeableAPPLE */
        1391  /* glObjectUnpurgeableAPPLE */
    };
    uint32_t i;
    if(!context->APPLE_object_purgeable) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_sync(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2565, /* glClientWaitSyncAPPLE */
        2594, /* glDeleteSyncAPPLE */
        2648, /* glFenceSyncAPPLE */
        2698, /* glGetInteger64vAPPLE */
        2736, /* glGetSyncivAPPLE */
        2772, /* glIsSyncAPPLE */
        2886  /* glWaitSyncAPPLE */
    };
    uint32_t i;
    if(!context->APPLE_sync) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_texture_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         895, /* glGetTexParameterPointervAPPLE */
        1969  /* glTextureRangeAPPLE */
    };
    uint32_t i;
    if(!context->APPLE_texture_range) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_vertex_array_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          83, /* glBindVertexArrayAPPLE */
         379, /* glDeleteVertexArraysAPPLE */
         600, /* glGenVertexArraysAPPLE */
        1094  /* glIsVertexArrayAPPLE */
    };
    uint32_t i;
    if(!context->APPLE_vertex_array_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_vertex_array_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         512, /* glFlushVertexArrayRangeAPPLE */
        2190, /* glVertexArrayParameteriAPPLE */
        2191  /* glVertexArrayRangeAPPLE */
    };
    uint32_t i;
    if(!context->APPLE_vertex_array_range) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_vertex_program_evaluators(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         405, /* glDisableVertexAttribAPPLE */
         468, /* glEnableVertexAttribAPPLE */
        1095, /* glIsVertexAttribEnabledAPPLE */
        1150, /* glMapVertexAttrib1dAPPLE */
        1151, /* glMapVertexAttrib1fAPPLE */
        1152, /* glMapVertexAttrib2dAPPLE */
        1153  /* glMapVertexAttrib2fAPPLE */
    };
    uint32_t i;
    if(!context->APPLE_vertex_program_evaluators) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_ES2_compatibility(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         165, /* glClearDepthf */
         391, /* glDepthRangef */
         869, /* glGetShaderPrecisionFormat */
        1677, /* glReleaseShaderCompiler */
        1770  /* glShaderBinary */
    };
    uint32_t i;
    if(!context->ARB_ES2_compatibility) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_ES3_1_compatibility(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1188  /* glMemoryBarrierByRegion */
    };
    uint32_t i;
    if(!context->ARB_ES3_1_compatibility) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_ES3_2_compatibility(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1464  /* glPrimitiveBoundingBoxARB */
    };
    uint32_t i;
    if(!context->ARB_ES3_2_compatibility) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_base_instance(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         417, /* glDrawArraysInstancedBaseInstance */
         434, /* glDrawElementsInstancedBaseInstance */
         436  /* glDrawElementsInstancedBaseVertexBaseInstance */
    };
    uint32_t i;
    if(!context->ARB_base_instance) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_bindless_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         701, /* glGetImageHandleARB */
         899, /* glGetTextureHandleARB */
         915, /* glGetTextureSamplerHandleARB */
         968, /* glGetVertexAttribLui64vARB */
        1062, /* glIsImageHandleResidentARB */
        1088, /* glIsTextureHandleResidentARB */
        1124, /* glMakeImageHandleNonResidentARB */
        1126, /* glMakeImageHandleResidentARB */
        1130, /* glMakeTextureHandleNonResidentARB */
        1132, /* glMakeTextureHandleResidentARB */
        1608, /* glProgramUniformHandleui64ARB */
        1610, /* glProgramUniformHandleui64vARB */
        2094, /* glUniformHandleui64ARB */
        2096, /* glUniformHandleui64vARB */
        2369, /* glVertexAttribL1ui64ARB */
        2371  /* glVertexAttribL1ui64vARB */
    };
    uint32_t i;
    if(!context->ARB_bindless_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_blend_func_extended(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          55, /* glBindFragDataLocationIndexed */
         681  /* glGetFragDataIndex */
    };
    uint32_t i;
    if(!context->ARB_blend_func_extended) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_buffer_storage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         139  /* glBufferStorage */
    };
    uint32_t i;
    if(!context->ARB_buffer_storage) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_cl_event(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         323  /* glCreateSyncFromCLeventARB */
    };
    uint32_t i;
    if(!context->ARB_cl_event) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_clear_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         153, /* glClearBufferData */
         154  /* glClearBufferSubData */
    };
    uint32_t i;
    if(!context->ARB_clear_buffer_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_clear_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         177, /* glClearTexImage */
         178  /* glClearTexSubImage */
    };
    uint32_t i;
    if(!context->ARB_clear_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_clip_control(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         184  /* glClipControl */
    };
    uint32_t i;
    if(!context->ARB_clip_control) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_color_buffer_float(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         150  /* glClampColorARB */
    };
    uint32_t i;
    if(!context->ARB_color_buffer_float) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_compute_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         409, /* glDispatchCompute */
         411  /* glDispatchComputeIndirect */
    };
    uint32_t i;
    if(!context->ARB_compute_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_compute_variable_group_size(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         410  /* glDispatchComputeGroupSizeARB */
    };
    uint32_t i;
    if(!context->ARB_compute_variable_group_size) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_copy_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         267  /* glCopyBufferSubData */
    };
    uint32_t i;
    if(!context->ARB_copy_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_copy_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         272  /* glCopyImageSubData */
    };
    uint32_t i;
    if(!context->ARB_copy_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_debug_output(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         333, /* glDebugMessageCallbackARB */
         335, /* glDebugMessageControlARB */
         339, /* glDebugMessageInsertARB */
         664  /* glGetDebugMessageLogARB */
    };
    uint32_t i;
    if(!context->ARB_debug_output) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_direct_state_access(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          77, /* glBindTextureUnit */
         131, /* glBlitNamedFramebuffer */
         147, /* glCheckNamedFramebufferStatus */
         168, /* glClearNamedBufferData */
         170, /* glClearNamedBufferSubData */
         172, /* glClearNamedFramebufferfi */
         173, /* glClearNamedFramebufferfv */
         174, /* glClearNamedFramebufferiv */
         175, /* glClearNamedFramebufferuiv */
         251, /* glCompressedTextureSubImage1D */
         253, /* glCompressedTextureSubImage2D */
         255, /* glCompressedTextureSubImage3D */
         279, /* glCopyNamedBufferSubData */
         293, /* glCopyTextureSubImage1D */
         295, /* glCopyTextureSubImage2D */
         297, /* glCopyTextureSubImage3D */
         305, /* glCreateBuffers */
         307, /* glCreateFramebuffers */
         312, /* glCreateProgramPipelines */
         314, /* glCreateQueries */
         315, /* glCreateRenderbuffers */
         316, /* glCreateSamplers */
         324, /* glCreateTextures */
         325, /* glCreateTransformFeedbacks */
         326, /* glCreateVertexArrays */
         402, /* glDisableVertexArrayAttrib */
         465, /* glEnableVertexArrayAttrib */
         507, /* glFlushMappedNamedBufferRange */
         605, /* glGenerateTextureMipmap */
         654, /* glGetCompressedTextureImage */
         752, /* glGetNamedBufferParameteri64v */
         753, /* glGetNamedBufferParameteriv */
         756, /* glGetNamedBufferPointerv */
         758, /* glGetNamedBufferSubData */
         760, /* glGetNamedFramebufferAttachmentParameteriv */
         763, /* glGetNamedFramebufferParameteriv */
         771, /* glGetNamedRenderbufferParameteriv */
         844, /* glGetQueryBufferObjecti64v */
         845, /* glGetQueryBufferObjectiv */
         846, /* glGetQueryBufferObjectui64v */
         847, /* glGetQueryBufferObjectuiv */
         901, /* glGetTextureImage */
         903, /* glGetTextureLevelParameterfv */
         905, /* glGetTextureLevelParameteriv */
         907, /* glGetTextureParameterIiv */
         909, /* glGetTextureParameterIuiv */
         911, /* glGetTextureParameterfv */
         913, /* glGetTextureParameteriv */
         922, /* glGetTransformFeedbacki64_v */
         923, /* glGetTransformFeedbacki_v */
         924, /* glGetTransformFeedbackiv */
         952, /* glGetVertexArrayIndexed64iv */
         953, /* glGetVertexArrayIndexediv */
         958, /* glGetVertexArrayiv */
        1044, /* glInvalidateNamedFramebufferData */
        1045, /* glInvalidateNamedFramebufferSubData */
        1142, /* glMapNamedBuffer */
        1144, /* glMapNamedBufferRange */
        1317, /* glNamedBufferData */
        1322, /* glNamedBufferStorage */
        1326, /* glNamedBufferSubData */
        1329, /* glNamedFramebufferDrawBuffer */
        1330, /* glNamedFramebufferDrawBuffers */
        1331, /* glNamedFramebufferParameteri */
        1333, /* glNamedFramebufferReadBuffer */
        1334, /* glNamedFramebufferRenderbuffer */
        1339, /* glNamedFramebufferTexture */
        1345, /* glNamedFramebufferTextureLayer */
        1360, /* glNamedRenderbufferStorage */
        1362, /* glNamedRenderbufferStorageMultisample */
        1940, /* glTextureBuffer */
        1942, /* glTextureBufferRange */
        1957, /* glTextureParameterIiv */
        1959, /* glTextureParameterIuiv */
        1961, /* glTextureParameterf */
        1963, /* glTextureParameterfv */
        1965, /* glTextureParameteri */
        1967, /* glTextureParameteriv */
        1971, /* glTextureStorage1D */
        1973, /* glTextureStorage2D */
        1975, /* glTextureStorage2DMultisample */
        1977, /* glTextureStorage3D */
        1979, /* glTextureStorage3DMultisample */
        1987, /* glTextureSubImage1D */
        1989, /* glTextureSubImage2D */
        1991, /* glTextureSubImage3D */
        1996, /* glTransformFeedbackBufferBase */
        1997, /* glTransformFeedbackBufferRange */
        2125, /* glUnmapNamedBuffer */
        2177, /* glVertexArrayAttribBinding */
        2178, /* glVertexArrayAttribFormat */
        2179, /* glVertexArrayAttribIFormat */
        2180, /* glVertexArrayAttribLFormat */
        2182, /* glVertexArrayBindingDivisor */
        2185, /* glVertexArrayElementBuffer */
        2204, /* glVertexArrayVertexBuffer */
        2205  /* glVertexArrayVertexBuffers */
    };
    uint32_t i;
    if(!context->ARB_direct_state_access) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_draw_buffers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         421  /* glDrawBuffersARB */
    };
    uint32_t i;
    if(!context->ARB_draw_buffers) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_draw_buffers_blend(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         113, /* glBlendEquationSeparateiARB */
         115, /* glBlendEquationiARB */
         123, /* glBlendFuncSeparateiARB */
         125  /* glBlendFunciARB */
    };
    uint32_t i;
    if(!context->ARB_draw_buffers_blend) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_draw_elements_base_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         430, /* glDrawElementsBaseVertex */
         435, /* glDrawElementsInstancedBaseVertex */
         444, /* glDrawRangeElementsBaseVertex */
        1208  /* glMultiDrawElementsBaseVertex */
    };
    uint32_t i;
    if(!context->ARB_draw_elements_base_vertex) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_draw_indirect(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         414, /* glDrawArraysIndirect */
         431  /* glDrawElementsIndirect */
    };
    uint32_t i;
    if(!context->ARB_draw_indirect) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_draw_instanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         416, /* glDrawArraysInstancedARB */
         433  /* glDrawElementsInstancedARB */
    };
    uint32_t i;
    if(!context->ARB_draw_instanced) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_fragment_program(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          66, /* glBindProgramARB */
         362, /* glDeleteProgramsARB */
         585, /* glGenProgramsARB */
         817, /* glGetProgramEnvParameterdvARB */
         818, /* glGetProgramEnvParameterfvARB */
         823, /* glGetProgramLocalParameterdvARB */
         824, /* glGetProgramLocalParameterfvARB */
         838, /* glGetProgramStringARB */
         842, /* glGetProgramivARB */
        1074, /* glIsProgramARB */
        1474, /* glProgramEnvParameter4dARB */
        1475, /* glProgramEnvParameter4dvARB */
        1476, /* glProgramEnvParameter4fARB */
        1477, /* glProgramEnvParameter4fvARB */
        1485, /* glProgramLocalParameter4dARB */
        1486, /* glProgramLocalParameter4dvARB */
        1487, /* glProgramLocalParameter4fARB */
        1488, /* glProgramLocalParameter4fvARB */
        1510  /* glProgramStringARB */
    };
    uint32_t i;
    if(!context->ARB_fragment_program) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_framebuffer_no_attachments(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         545, /* glFramebufferParameteri */
         691  /* glGetFramebufferParameteriv */
    };
    uint32_t i;
    if(!context->ARB_framebuffer_no_attachments) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_framebuffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          57, /* glBindFramebuffer */
          69, /* glBindRenderbuffer */
         127, /* glBlitFramebuffer */
         145, /* glCheckFramebufferStatus */
         350, /* glDeleteFramebuffers */
         367, /* glDeleteRenderbuffers */
         548, /* glFramebufferRenderbuffer */
         554, /* glFramebufferTexture1D */
         556, /* glFramebufferTexture2D */
         558, /* glFramebufferTexture3D */
         564, /* glFramebufferTextureLayer */
         578, /* glGenFramebuffers */
         590, /* glGenRenderbuffers */
         602, /* glGenerateMipmap */
         688, /* glGetFramebufferAttachmentParameteriv */
         859, /* glGetRenderbufferParameteriv */
        1060, /* glIsFramebuffer */
        1079, /* glIsRenderbuffer */
        1679, /* glRenderbufferStorage */
        1681  /* glRenderbufferStorageMultisample */
    };
    uint32_t i;
    if(!context->ARB_framebuffer_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_geometry_shader4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         560, /* glFramebufferTextureARB */
         562, /* glFramebufferTextureFaceARB */
         565, /* glFramebufferTextureLayerARB */
        1505  /* glProgramParameteriARB */
    };
    uint32_t i;
    if(!context->ARB_geometry_shader4) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_get_program_binary(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         814, /* glGetProgramBinary */
        1470, /* glProgramBinary */
        1504  /* glProgramParameteri */
    };
    uint32_t i;
    if(!context->ARB_get_program_binary) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_get_texture_sub_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         656, /* glGetCompressedTextureSubImage */
         917  /* glGetTextureSubImage */
    };
    uint32_t i;
    if(!context->ARB_get_texture_sub_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_gl_spirv(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1787  /* glSpecializeShaderARB */
    };
    uint32_t i;
    if(!context->ARB_gl_spirv) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_gpu_shader_fp64(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         932, /* glGetUniformdv */
        2004, /* glUniform1d */
        2005, /* glUniform1dv */
        2026, /* glUniform2d */
        2027, /* glUniform2dv */
        2048, /* glUniform3d */
        2049, /* glUniform3dv */
        2070, /* glUniform4d */
        2071, /* glUniform4dv */
        2098, /* glUniformMatrix2dv */
        2101, /* glUniformMatrix2x3dv */
        2103, /* glUniformMatrix2x4dv */
        2105, /* glUniformMatrix3dv */
        2108, /* glUniformMatrix3x2dv */
        2110, /* glUniformMatrix3x4dv */
        2112, /* glUniformMatrix4dv */
        2115, /* glUniformMatrix4x2dv */
        2117  /* glUniformMatrix4x3dv */
    };
    uint32_t i;
    if(!context->ARB_gpu_shader_fp64) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_gpu_shader_int64(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         935, /* glGetUniformi64vARB */
         939, /* glGetUniformui64vARB */
         999, /* glGetnUniformi64vARB */
        1002, /* glGetnUniformui64vARB */
        1521, /* glProgramUniform1i64ARB */
        1523, /* glProgramUniform1i64vARB */
        1529, /* glProgramUniform1ui64ARB */
        1531, /* glProgramUniform1ui64vARB */
        1545, /* glProgramUniform2i64ARB */
        1547, /* glProgramUniform2i64vARB */
        1553, /* glProgramUniform2ui64ARB */
        1555, /* glProgramUniform2ui64vARB */
        1569, /* glProgramUniform3i64ARB */
        1571, /* glProgramUniform3i64vARB */
        1577, /* glProgramUniform3ui64ARB */
        1579, /* glProgramUniform3ui64vARB */
        1593, /* glProgramUniform4i64ARB */
        1595, /* glProgramUniform4i64vARB */
        1601, /* glProgramUniform4ui64ARB */
        1603, /* glProgramUniform4ui64vARB */
        2011, /* glUniform1i64ARB */
        2013, /* glUniform1i64vARB */
        2019, /* glUniform1ui64ARB */
        2021, /* glUniform1ui64vARB */
        2033, /* glUniform2i64ARB */
        2035, /* glUniform2i64vARB */
        2041, /* glUniform2ui64ARB */
        2043, /* glUniform2ui64vARB */
        2055, /* glUniform3i64ARB */
        2057, /* glUniform3i64vARB */
        2063, /* glUniform3ui64ARB */
        2065, /* glUniform3ui64vARB */
        2077, /* glUniform4i64ARB */
        2079, /* glUniform4i64vARB */
        2085, /* glUniform4ui64ARB */
        2087  /* glUniform4ui64vARB */
    };
    uint32_t i;
    if(!context->ARB_gpu_shader_int64) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_imaging(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         103, /* glBlendColor */
         106  /* glBlendEquation */
    };
    uint32_t i;
    if(!context->ARB_imaging) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_indirect_parameters(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1205, /* glMultiDrawArraysIndirectCountARB */
        1215  /* glMultiDrawElementsIndirectCountARB */
    };
    uint32_t i;
    if(!context->ARB_indirect_parameters) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_instanced_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2316  /* glVertexAttribDivisorARB */
    };
    uint32_t i;
    if(!context->ARB_instanced_arrays) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_internalformat_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         716  /* glGetInternalformativ */
    };
    uint32_t i;
    if(!context->ARB_internalformat_query) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_internalformat_query2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         715  /* glGetInternalformati64v */
    };
    uint32_t i;
    if(!context->ARB_internalformat_query2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_invalidate_subdata(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1041, /* glInvalidateBufferData */
        1042, /* glInvalidateBufferSubData */
        1043, /* glInvalidateFramebuffer */
        1046, /* glInvalidateSubFramebuffer */
        1047, /* glInvalidateTexImage */
        1048  /* glInvalidateTexSubImage */
    };
    uint32_t i;
    if(!context->ARB_invalidate_subdata) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_map_buffer_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         505, /* glFlushMappedBufferRange */
        1138  /* glMapBufferRange */
    };
    uint32_t i;
    if(!context->ARB_map_buffer_range) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_matrix_palette(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         330, /* glCurrentPaletteMatrixARB */
        1157, /* glMatrixIndexPointerARB */
        1158, /* glMatrixIndexubvARB */
        1159, /* glMatrixIndexuivARB */
        1160  /* glMatrixIndexusvARB */
    };
    uint32_t i;
    if(!context->ARB_matrix_palette) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_multi_bind(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          51, /* glBindBuffersBase */
          52, /* glBindBuffersRange */
          61, /* glBindImageTextures */
          72, /* glBindSamplers */
          79, /* glBindTextures */
          85  /* glBindVertexBuffers */
    };
    uint32_t i;
    if(!context->ARB_multi_bind) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_multi_draw_indirect(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1200, /* glMultiDrawArraysIndirect */
        1210  /* glMultiDrawElementsIndirect */
    };
    uint32_t i;
    if(!context->ARB_multi_draw_indirect) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1718  /* glSampleCoverageARB */
    };
    uint32_t i;
    if(!context->ARB_multisample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_multitexture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           6, /* glActiveTextureARB */
         179, /* glClientActiveTextureARB */
        1224, /* glMultiTexCoord1dARB */
        1225, /* glMultiTexCoord1dvARB */
        1226, /* glMultiTexCoord1fARB */
        1227, /* glMultiTexCoord1fvARB */
        1230, /* glMultiTexCoord1iARB */
        1231, /* glMultiTexCoord1ivARB */
        1232, /* glMultiTexCoord1sARB */
        1233, /* glMultiTexCoord1svARB */
        1238, /* glMultiTexCoord2dARB */
        1239, /* glMultiTexCoord2dvARB */
        1240, /* glMultiTexCoord2fARB */
        1241, /* glMultiTexCoord2fvARB */
        1244, /* glMultiTexCoord2iARB */
        1245, /* glMultiTexCoord2ivARB */
        1246, /* glMultiTexCoord2sARB */
        1247, /* glMultiTexCoord2svARB */
        1252, /* glMultiTexCoord3dARB */
        1253, /* glMultiTexCoord3dvARB */
        1254, /* glMultiTexCoord3fARB */
        1255, /* glMultiTexCoord3fvARB */
        1258, /* glMultiTexCoord3iARB */
        1259, /* glMultiTexCoord3ivARB */
        1260, /* glMultiTexCoord3sARB */
        1261, /* glMultiTexCoord3svARB */
        1266, /* glMultiTexCoord4dARB */
        1267, /* glMultiTexCoord4dvARB */
        1268, /* glMultiTexCoord4fARB */
        1269, /* glMultiTexCoord4fvARB */
        1272, /* glMultiTexCoord4iARB */
        1273, /* glMultiTexCoord4ivARB */
        1274, /* glMultiTexCoord4sARB */
        1275  /* glMultiTexCoord4svARB */
    };
    uint32_t i;
    if(!context->ARB_multitexture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_occlusion_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          32, /* glBeginQueryARB */
         365, /* glDeleteQueriesARB */
         480, /* glEndQueryARB */
         588, /* glGenQueriesARB */
         852, /* glGetQueryObjectivARB */
         856, /* glGetQueryObjectuivARB */
         858, /* glGetQueryivARB */
        1078  /* glIsQueryARB */
    };
    uint32_t i;
    if(!context->ARB_occlusion_query) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_parallel_shader_compile(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1185  /* glMaxShaderCompilerThreadsARB */
    };
    uint32_t i;
    if(!context->ARB_parallel_shader_compile) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_point_parameters(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1438, /* glPointParameterfARB */
        1442  /* glPointParameterfvARB */
    };
    uint32_t i;
    if(!context->ARB_point_parameters) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_polygon_offset_clamp(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1456  /* glPolygonOffsetClamp */
    };
    uint32_t i;
    if(!context->ARB_polygon_offset_clamp) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_program_interface_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         820, /* glGetProgramInterfaceiv */
         831, /* glGetProgramResourceIndex */
         832, /* glGetProgramResourceLocation */
         833, /* glGetProgramResourceLocationIndex */
         834, /* glGetProgramResourceName */
         836  /* glGetProgramResourceiv */
    };
    uint32_t i;
    if(!context->ARB_program_interface_query) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_provoking_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1651  /* glProvokingVertex */
    };
    uint32_t i;
    if(!context->ARB_provoking_vertex) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_robustness(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         695, /* glGetGraphicsResetStatusARB */
         992, /* glGetnCompressedTexImageARB */
         994, /* glGetnTexImageARB */
         996, /* glGetnUniformdvARB */
         998, /* glGetnUniformfvARB */
        1001, /* glGetnUniformivARB */
        1004, /* glGetnUniformuivARB */
        1672  /* glReadnPixelsARB */
    };
    uint32_t i;
    if(!context->ARB_robustness) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_sample_locations(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         492, /* glEvaluateDepthValuesARB */
         550, /* glFramebufferSampleLocationsfvARB */
        1336  /* glNamedFramebufferSampleLocationsfvARB */
    };
    uint32_t i;
    if(!context->ARB_sample_locations) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_sample_shading(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1192  /* glMinSampleShadingARB */
    };
    uint32_t i;
    if(!context->ARB_sample_shading) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_sampler_objects(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          71, /* glBindSampler */
         369, /* glDeleteSamplers */
         592, /* glGenSamplers */
         861, /* glGetSamplerParameterIiv */
         862, /* glGetSamplerParameterIuiv */
         863, /* glGetSamplerParameterfv */
         864, /* glGetSamplerParameteriv */
        1081, /* glIsSampler */
        1726, /* glSamplerParameterIiv */
        1727, /* glSamplerParameterIuiv */
        1728, /* glSamplerParameterf */
        1729, /* glSamplerParameterfv */
        1730, /* glSamplerParameteri */
        1731  /* glSamplerParameteriv */
    };
    uint32_t i;
    if(!context->ARB_sampler_objects) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_separate_shader_objects(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           3, /* glActiveShaderProgram */
          68, /* glBindProgramPipeline */
         321, /* glCreateShaderProgramv */
         361, /* glDeleteProgramPipelines */
         584, /* glGenProgramPipelines */
         829, /* glGetProgramPipelineInfoLog */
         830, /* glGetProgramPipelineiv */
        1076, /* glIsProgramPipeline */
        1504, /* glProgramParameteri */
        1512, /* glProgramUniform1d */
        1514, /* glProgramUniform1dv */
        1516, /* glProgramUniform1f */
        1518, /* glProgramUniform1fv */
        1520, /* glProgramUniform1i */
        1526, /* glProgramUniform1iv */
        1528, /* glProgramUniform1ui */
        1534, /* glProgramUniform1uiv */
        1536, /* glProgramUniform2d */
        1538, /* glProgramUniform2dv */
        1540, /* glProgramUniform2f */
        1542, /* glProgramUniform2fv */
        1544, /* glProgramUniform2i */
        1550, /* glProgramUniform2iv */
        1552, /* glProgramUniform2ui */
        1558, /* glProgramUniform2uiv */
        1560, /* glProgramUniform3d */
        1562, /* glProgramUniform3dv */
        1564, /* glProgramUniform3f */
        1566, /* glProgramUniform3fv */
        1568, /* glProgramUniform3i */
        1574, /* glProgramUniform3iv */
        1576, /* glProgramUniform3ui */
        1582, /* glProgramUniform3uiv */
        1584, /* glProgramUniform4d */
        1586, /* glProgramUniform4dv */
        1588, /* glProgramUniform4f */
        1590, /* glProgramUniform4fv */
        1592, /* glProgramUniform4i */
        1598, /* glProgramUniform4iv */
        1600, /* glProgramUniform4ui */
        1606, /* glProgramUniform4uiv */
        1612, /* glProgramUniformMatrix2dv */
        1614, /* glProgramUniformMatrix2fv */
        1616, /* glProgramUniformMatrix2x3dv */
        1618, /* glProgramUniformMatrix2x3fv */
        1620, /* glProgramUniformMatrix2x4dv */
        1622, /* glProgramUniformMatrix2x4fv */
        1624, /* glProgramUniformMatrix3dv */
        1626, /* glProgramUniformMatrix3fv */
        1628, /* glProgramUniformMatrix3x2dv */
        1630, /* glProgramUniformMatrix3x2fv */
        1632, /* glProgramUniformMatrix3x4dv */
        1634, /* glProgramUniformMatrix3x4fv */
        1636, /* glProgramUniformMatrix4dv */
        1638, /* glProgramUniformMatrix4fv */
        1640, /* glProgramUniformMatrix4x2dv */
        1642, /* glProgramUniformMatrix4x2fv */
        1644, /* glProgramUniformMatrix4x3dv */
        1646, /* glProgramUniformMatrix4x3fv */
        2133, /* glUseProgramStages */
        2148  /* glValidateProgramPipeline */
    };
    uint32_t i;
    if(!context->ARB_separate_shader_objects) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_shader_atomic_counters(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         607  /* glGetActiveAtomicCounterBufferiv */
    };
    uint32_t i;
    if(!context->ARB_shader_atomic_counters) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_shader_image_load_store(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          59, /* glBindImageTexture */
        1187  /* glMemoryBarrier */
    };
    uint32_t i;
    if(!context->ARB_shader_image_load_store) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_shader_objects(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          22, /* glAttachObjectARB */
         228, /* glCompileShaderARB */
         311, /* glCreateProgramObjectARB */
         319, /* glCreateShaderObjectARB */
         355, /* glDeleteObjectARB */
         394, /* glDetachObjectARB */
         614, /* glGetActiveUniformARB */
         622, /* glGetAttachedObjectsARB */
         696, /* glGetHandleARB */
         705, /* glGetInfoLogARB */
         780, /* glGetObjectParameterfvARB */
         782, /* glGetObjectParameterivARB */
         871, /* glGetShaderSourceARB */
         929, /* glGetUniformLocationARB */
         934, /* glGetUniformfvARB */
         938, /* glGetUniformivARB */
        1108, /* glLinkProgramARB */
        1775, /* glShaderSourceARB */
        2007, /* glUniform1fARB */
        2009, /* glUniform1fvARB */
        2015, /* glUniform1iARB */
        2017, /* glUniform1ivARB */
        2029, /* glUniform2fARB */
        2031, /* glUniform2fvARB */
        2037, /* glUniform2iARB */
        2039, /* glUniform2ivARB */
        2051, /* glUniform3fARB */
        2053, /* glUniform3fvARB */
        2059, /* glUniform3iARB */
        2061, /* glUniform3ivARB */
        2073, /* glUniform4fARB */
        2075, /* glUniform4fvARB */
        2081, /* glUniform4iARB */
        2083, /* glUniform4ivARB */
        2100, /* glUniformMatrix2fvARB */
        2107, /* glUniformMatrix3fvARB */
        2114, /* glUniformMatrix4fvARB */
        2132, /* glUseProgramObjectARB */
        2147  /* glValidateProgramARB */
    };
    uint32_t i;
    if(!context->ARB_shader_objects) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_shader_storage_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1776  /* glShaderStorageBlockBinding */
    };
    uint32_t i;
    if(!context->ARB_shader_storage_buffer_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_shader_subroutine(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         610, /* glGetActiveSubroutineName */
         611, /* glGetActiveSubroutineUniformName */
         612, /* glGetActiveSubroutineUniformiv */
         837, /* glGetProgramStageiv */
         879, /* glGetSubroutineIndex */
         880, /* glGetSubroutineUniformLocation */
         931, /* glGetUniformSubroutineuiv */
        2119  /* glUniformSubroutinesuiv */
    };
    uint32_t i;
    if(!context->ARB_shader_subroutine) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_shading_language_include(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         229, /* glCompileShaderIncludeARB */
         353, /* glDeleteNamedStringARB */
         773, /* glGetNamedStringARB */
         774, /* glGetNamedStringivARB */
        1067, /* glIsNamedStringARB */
        1366  /* glNamedStringARB */
    };
    uint32_t i;
    if(!context->ARB_shading_language_include) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_sparse_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         136, /* glBufferPageCommitmentARB */
        1319, /* glNamedBufferPageCommitmentARB */
        1320  /* glNamedBufferPageCommitmentEXT */
    };
    uint32_t i;
    if(!context->ARB_sparse_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_sparse_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1899  /* glTexPageCommitmentARB */
    };
    uint32_t i;
    if(!context->ARB_sparse_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_sync(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         183, /* glClientWaitSync */
         373, /* glDeleteSync */
         496, /* glFenceSync */
         708, /* glGetInteger64v */
         881, /* glGetSynciv */
        1085, /* glIsSync */
        2487  /* glWaitSync */
    };
    uint32_t i;
    if(!context->ARB_sync) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_tessellation_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1398, /* glPatchParameterfv */
        1399  /* glPatchParameteri */
    };
    uint32_t i;
    if(!context->ARB_tessellation_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_barrier(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1938  /* glTextureBarrier */
    };
    uint32_t i;
    if(!context->ARB_texture_barrier) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1837  /* glTexBufferARB */
    };
    uint32_t i;
    if(!context->ARB_texture_buffer_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_buffer_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1839  /* glTexBufferRange */
    };
    uint32_t i;
    if(!context->ARB_texture_buffer_range) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_compression(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         237, /* glCompressedTexImage1DARB */
         239, /* glCompressedTexImage2DARB */
         241, /* glCompressedTexImage3DARB */
         243, /* glCompressedTexSubImage1DARB */
         245, /* glCompressedTexSubImage2DARB */
         247, /* glCompressedTexSubImage3DARB */
         653  /* glGetCompressedTexImageARB */
    };
    uint32_t i;
    if(!context->ARB_texture_compression) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         750, /* glGetMultisamplefv */
        1723, /* glSampleMaski */
        1892, /* glTexImage2DMultisample */
        1896  /* glTexImage3DMultisample */
    };
    uint32_t i;
    if(!context->ARB_texture_multisample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_storage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1912, /* glTexStorage1D */
        1914, /* glTexStorage2D */
        1917  /* glTexStorage3D */
    };
    uint32_t i;
    if(!context->ARB_texture_storage) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_storage_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1916, /* glTexStorage2DMultisample */
        1919  /* glTexStorage3DMultisample */
    };
    uint32_t i;
    if(!context->ARB_texture_storage_multisample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_view(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1993  /* glTextureView */
    };
    uint32_t i;
    if(!context->ARB_texture_view) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_timer_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         849, /* glGetQueryObjecti64v */
         853, /* glGetQueryObjectui64v */
        1656  /* glQueryCounter */
    };
    uint32_t i;
    if(!context->ARB_timer_query) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_transform_feedback2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          80, /* glBindTransformFeedback */
         376, /* glDeleteTransformFeedbacks */
         447, /* glDrawTransformFeedback */
         597, /* glGenTransformFeedbacks */
        1090, /* glIsTransformFeedback */
        1418, /* glPauseTransformFeedback */
        1714  /* glResumeTransformFeedback */
    };
    uint32_t i;
    if(!context->ARB_transform_feedback2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_transform_feedback3(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          33, /* glBeginQueryIndexed */
         450, /* glDrawTransformFeedbackStream */
         481, /* glEndQueryIndexed */
         848  /* glGetQueryIndexediv */
    };
    uint32_t i;
    if(!context->ARB_transform_feedback3) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_transform_feedback_instanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         448, /* glDrawTransformFeedbackInstanced */
         451  /* glDrawTransformFeedbackStreamInstanced */
    };
    uint32_t i;
    if(!context->ARB_transform_feedback_instanced) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_transpose_matrix(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1117, /* glLoadTransposeMatrixdARB */
        1118, /* glLoadTransposeMatrixfARB */
        1195, /* glMultTransposeMatrixdARB */
        1196  /* glMultTransposeMatrixfARB */
    };
    uint32_t i;
    if(!context->ARB_transpose_matrix) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_uniform_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          43, /* glBindBufferBase */
          48, /* glBindBufferRange */
         615, /* glGetActiveUniformBlockName */
         616, /* glGetActiveUniformBlockiv */
         617, /* glGetActiveUniformName */
         618, /* glGetActiveUniformsiv */
         710, /* glGetIntegeri_v */
         925, /* glGetUniformBlockIndex */
         927, /* glGetUniformIndices */
        2092  /* glUniformBlockBinding */
    };
    uint32_t i;
    if(!context->ARB_uniform_buffer_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_array_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          82, /* glBindVertexArray */
         378, /* glDeleteVertexArrays */
         599, /* glGenVertexArrays */
        1093  /* glIsVertexArray */
    };
    uint32_t i;
    if(!context->ARB_vertex_array_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_attrib_64bit(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         965, /* glGetVertexAttribLdv */
        2363, /* glVertexAttribL1d */
        2365, /* glVertexAttribL1dv */
        2373, /* glVertexAttribL2d */
        2375, /* glVertexAttribL2dv */
        2381, /* glVertexAttribL3d */
        2383, /* glVertexAttribL3dv */
        2389, /* glVertexAttribL4d */
        2391, /* glVertexAttribL4dv */
        2399  /* glVertexAttribLPointer */
    };
    uint32_t i;
    if(!context->ARB_vertex_attrib_64bit) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_attrib_binding(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          84, /* glBindVertexBuffer */
        2314, /* glVertexAttribBinding */
        2317, /* glVertexAttribFormat */
        2359, /* glVertexAttribIFormat */
        2397, /* glVertexAttribLFormat */
        2430  /* glVertexBindingDivisor */
    };
    uint32_t i;
    if(!context->ARB_vertex_attrib_binding) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_blend(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2431, /* glVertexBlendARB */
        2490, /* glWeightPointerARB */
        2491, /* glWeightbvARB */
        2492, /* glWeightdvARB */
        2493, /* glWeightfvARB */
        2494, /* glWeightivARB */
        2495, /* glWeightsvARB */
        2496, /* glWeightubvARB */
        2497, /* glWeightuivARB */
        2498  /* glWeightusvARB */
    };
    uint32_t i;
    if(!context->ARB_vertex_blend) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          42, /* glBindBufferARB */
         135, /* glBufferDataARB */
         143, /* glBufferSubDataARB */
         345, /* glDeleteBuffersARB */
         574, /* glGenBuffersARB */
         631, /* glGetBufferParameterivARB */
         634, /* glGetBufferPointervARB */
         636, /* glGetBufferSubDataARB */
        1052, /* glIsBufferARB */
        1137, /* glMapBufferARB */
        2124  /* glUnmapBufferARB */
    };
    uint32_t i;
    if(!context->ARB_vertex_buffer_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_program(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          66, /* glBindProgramARB */
         362, /* glDeleteProgramsARB */
         407, /* glDisableVertexAttribArrayARB */
         470, /* glEnableVertexAttribArrayARB */
         585, /* glGenProgramsARB */
         817, /* glGetProgramEnvParameterdvARB */
         818, /* glGetProgramEnvParameterfvARB */
         823, /* glGetProgramLocalParameterdvARB */
         824, /* glGetProgramLocalParameterfvARB */
         838, /* glGetProgramStringARB */
         842, /* glGetProgramivARB */
         971, /* glGetVertexAttribPointervARB */
         974, /* glGetVertexAttribdvARB */
         977, /* glGetVertexAttribfvARB */
         980, /* glGetVertexAttribivARB */
        1074, /* glIsProgramARB */
        1474, /* glProgramEnvParameter4dARB */
        1475, /* glProgramEnvParameter4dvARB */
        1476, /* glProgramEnvParameter4fARB */
        1477, /* glProgramEnvParameter4fvARB */
        1485, /* glProgramLocalParameter4dARB */
        1486, /* glProgramLocalParameter4dvARB */
        1487, /* glProgramLocalParameter4fARB */
        1488, /* glProgramLocalParameter4fvARB */
        1510, /* glProgramStringARB */
        2208, /* glVertexAttrib1dARB */
        2211, /* glVertexAttrib1dvARB */
        2214, /* glVertexAttrib1fARB */
        2217, /* glVertexAttrib1fvARB */
        2222, /* glVertexAttrib1sARB */
        2225, /* glVertexAttrib1svARB */
        2228, /* glVertexAttrib2dARB */
        2231, /* glVertexAttrib2dvARB */
        2234, /* glVertexAttrib2fARB */
        2237, /* glVertexAttrib2fvARB */
        2242, /* glVertexAttrib2sARB */
        2245, /* glVertexAttrib2svARB */
        2248, /* glVertexAttrib3dARB */
        2251, /* glVertexAttrib3dvARB */
        2254, /* glVertexAttrib3fARB */
        2257, /* glVertexAttrib3fvARB */
        2262, /* glVertexAttrib3sARB */
        2265, /* glVertexAttrib3svARB */
        2268, /* glVertexAttrib4NbvARB */
        2270, /* glVertexAttrib4NivARB */
        2272, /* glVertexAttrib4NsvARB */
        2274, /* glVertexAttrib4NubARB */
        2276, /* glVertexAttrib4NubvARB */
        2278, /* glVertexAttrib4NuivARB */
        2280, /* glVertexAttrib4NusvARB */
        2282, /* glVertexAttrib4bvARB */
        2284, /* glVertexAttrib4dARB */
        2287, /* glVertexAttrib4dvARB */
        2290, /* glVertexAttrib4fARB */
        2293, /* glVertexAttrib4fvARB */
        2298, /* glVertexAttrib4ivARB */
        2300, /* glVertexAttrib4sARB */
        2303, /* glVertexAttrib4svARB */
        2307, /* glVertexAttrib4ubvARB */
        2310, /* glVertexAttrib4uivARB */
        2312, /* glVertexAttrib4usvARB */
        2411  /* glVertexAttribPointerARB */
    };
    uint32_t i;
    if(!context->ARB_vertex_program) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          40, /* glBindAttribLocationARB */
         407, /* glDisableVertexAttribArrayARB */
         470, /* glEnableVertexAttribArrayARB */
         609, /* glGetActiveAttribARB */
         625, /* glGetAttribLocationARB */
         971, /* glGetVertexAttribPointervARB */
         974, /* glGetVertexAttribdvARB */
         977, /* glGetVertexAttribfvARB */
         980, /* glGetVertexAttribivARB */
        2208, /* glVertexAttrib1dARB */
        2211, /* glVertexAttrib1dvARB */
        2214, /* glVertexAttrib1fARB */
        2217, /* glVertexAttrib1fvARB */
        2222, /* glVertexAttrib1sARB */
        2225, /* glVertexAttrib1svARB */
        2228, /* glVertexAttrib2dARB */
        2231, /* glVertexAttrib2dvARB */
        2234, /* glVertexAttrib2fARB */
        2237, /* glVertexAttrib2fvARB */
        2242, /* glVertexAttrib2sARB */
        2245, /* glVertexAttrib2svARB */
        2248, /* glVertexAttrib3dARB */
        2251, /* glVertexAttrib3dvARB */
        2254, /* glVertexAttrib3fARB */
        2257, /* glVertexAttrib3fvARB */
        2262, /* glVertexAttrib3sARB */
        2265, /* glVertexAttrib3svARB */
        2268, /* glVertexAttrib4NbvARB */
        2270, /* glVertexAttrib4NivARB */
        2272, /* glVertexAttrib4NsvARB */
        2274, /* glVertexAttrib4NubARB */
        2276, /* glVertexAttrib4NubvARB */
        2278, /* glVertexAttrib4NuivARB */
        2280, /* glVertexAttrib4NusvARB */
        2282, /* glVertexAttrib4bvARB */
        2284, /* glVertexAttrib4dARB */
        2287, /* glVertexAttrib4dvARB */
        2290, /* glVertexAttrib4fARB */
        2293, /* glVertexAttrib4fvARB */
        2298, /* glVertexAttrib4ivARB */
        2300, /* glVertexAttrib4sARB */
        2303, /* glVertexAttrib4svARB */
        2307, /* glVertexAttrib4ubvARB */
        2310, /* glVertexAttrib4uivARB */
        2312, /* glVertexAttrib4usvARB */
        2411  /* glVertexAttribPointerARB */
    };
    uint32_t i;
    if(!context->ARB_vertex_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_type_2_10_10_10_rev(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2401, /* glVertexAttribP1ui */
        2402, /* glVertexAttribP1uiv */
        2403, /* glVertexAttribP2ui */
        2404, /* glVertexAttribP2uiv */
        2405, /* glVertexAttribP3ui */
        2406, /* glVertexAttribP3uiv */
        2407, /* glVertexAttribP4ui */
        2408  /* glVertexAttribP4uiv */
    };
    uint32_t i;
    if(!context->ARB_vertex_type_2_10_10_10_rev) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_viewport_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         386, /* glDepthRangeArraydvNV */
         387, /* glDepthRangeArrayv */
         388, /* glDepthRangeIndexed */
         389, /* glDepthRangeIndexeddNV */
         667, /* glGetDoublei_v */
         677, /* glGetFloati_v */
        1734, /* glScissorArrayv */
        1737, /* glScissorIndexed */
        1738, /* glScissorIndexedv */
        2480, /* glViewportArrayv */
        2481, /* glViewportIndexedf */
        2482  /* glViewportIndexedfv */
    };
    uint32_t i;
    if(!context->ARB_viewport_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_window_pos(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2499, /* glWindowPos2dARB */
        2501, /* glWindowPos2dvARB */
        2503, /* glWindowPos2fARB */
        2505, /* glWindowPos2fvARB */
        2507, /* glWindowPos2iARB */
        2509, /* glWindowPos2ivARB */
        2511, /* glWindowPos2sARB */
        2513, /* glWindowPos2svARB */
        2515, /* glWindowPos3dARB */
        2517, /* glWindowPos3dvARB */
        2519, /* glWindowPos3fARB */
        2521, /* glWindowPos3fvARB */
        2523, /* glWindowPos3iARB */
        2525, /* glWindowPos3ivARB */
        2527, /* glWindowPos3sARB */
        2529  /* glWindowPos3svARB */
    };
    uint32_t i;
    if(!context->ARB_window_pos) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARM_shader_core_properties(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2781  /* glMaxActiveShaderCoresARM */
    };
    uint32_t i;
    if(!context->ARM_shader_core_properties) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_draw_buffers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         422  /* glDrawBuffersATI */
    };
    uint32_t i;
    if(!context->ATI_draw_buffers) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_element_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         428, /* glDrawElementArrayATI */
         442, /* glDrawRangeElementArrayATI */
         459  /* glElementPointerATI */
    };
    uint32_t i;
    if(!context->ATI_element_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_envmap_bumpmap(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         882, /* glGetTexBumpParameterfvATI */
         883, /* glGetTexBumpParameterivATI */
        1840, /* glTexBumpParameterfvATI */
        1841  /* glTexBumpParameterivATI */
    };
    uint32_t i;
    if(!context->ATI_envmap_bumpmap) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_fragment_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           8, /* glAlphaFragmentOp1ATI */
           9, /* glAlphaFragmentOp2ATI */
          10, /* glAlphaFragmentOp3ATI */
          27, /* glBeginFragmentShaderATI */
          56, /* glBindFragmentShaderATI */
         204, /* glColorFragmentOp1ATI */
         205, /* glColorFragmentOp2ATI */
         206, /* glColorFragmentOp3ATI */
         349, /* glDeleteFragmentShaderATI */
         475, /* glEndFragmentShaderATI */
         577, /* glGenFragmentShadersATI */
        1396, /* glPassTexCoordATI */
        1719, /* glSampleMapATI */
        1766  /* glSetFragmentShaderConstantATI */
    };
    uint32_t i;
    if(!context->ATI_fragment_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_map_object_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1146, /* glMapObjectBufferATI */
        2127  /* glUnmapObjectBufferATI */
    };
    uint32_t i;
    if(!context->ATI_map_object_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_pn_triangles(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1394, /* glPNTrianglesfATI */
        1395  /* glPNTrianglesiATI */
    };
    uint32_t i;
    if(!context->ATI_pn_triangles) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_separate_stencil(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1799, /* glStencilFuncSeparateATI */
        1804  /* glStencilOpSeparateATI */
    };
    uint32_t i;
    if(!context->ATI_separate_stencil) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_vertex_array_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          18, /* glArrayObjectATI */
         568, /* glFreeObjectBufferATI */
         620, /* glGetArrayObjectfvATI */
         621, /* glGetArrayObjectivATI */
         776, /* glGetObjectBufferfvATI */
         777, /* glGetObjectBufferivATI */
         945, /* glGetVariantArrayObjectfvATI */
         946, /* glGetVariantArrayObjectivATI */
        1068, /* glIsObjectBufferATI */
        1367, /* glNewObjectBufferATI */
        2129, /* glUpdateObjectBufferATI */
        2149  /* glVariantArrayObjectATI */
    };
    uint32_t i;
    if(!context->ATI_vertex_array_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_vertex_attrib_array_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         959, /* glGetVertexAttribArrayObjectfvATI */
         960, /* glGetVertexAttribArrayObjectivATI */
        2313  /* glVertexAttribArrayObjectATI */
    };
    uint32_t i;
    if(!context->ATI_vertex_attrib_array_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_vertex_streams(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         180, /* glClientActiveVertexStreamATI */
        1378, /* glNormalStream3bATI */
        1379, /* glNormalStream3bvATI */
        1380, /* glNormalStream3dATI */
        1381, /* glNormalStream3dvATI */
        1382, /* glNormalStream3fATI */
        1383, /* glNormalStream3fvATI */
        1384, /* glNormalStream3iATI */
        1385, /* glNormalStream3ivATI */
        1386, /* glNormalStream3sATI */
        1387, /* glNormalStream3svATI */
        2432, /* glVertexBlendEnvfATI */
        2433, /* glVertexBlendEnviATI */
        2438, /* glVertexStream1dATI */
        2439, /* glVertexStream1dvATI */
        2440, /* glVertexStream1fATI */
        2441, /* glVertexStream1fvATI */
        2442, /* glVertexStream1iATI */
        2443, /* glVertexStream1ivATI */
        2444, /* glVertexStream1sATI */
        2445, /* glVertexStream1svATI */
        2446, /* glVertexStream2dATI */
        2447, /* glVertexStream2dvATI */
        2448, /* glVertexStream2fATI */
        2449, /* glVertexStream2fvATI */
        2450, /* glVertexStream2iATI */
        2451, /* glVertexStream2ivATI */
        2452, /* glVertexStream2sATI */
        2453, /* glVertexStream2svATI */
        2454, /* glVertexStream3dATI */
        2455, /* glVertexStream3dvATI */
        2456, /* glVertexStream3fATI */
        2457, /* glVertexStream3fvATI */
        2458, /* glVertexStream3iATI */
        2459, /* glVertexStream3ivATI */
        2460, /* glVertexStream3sATI */
        2461, /* glVertexStream3svATI */
        2462, /* glVertexStream4dATI */
        2463, /* glVertexStream4dvATI */
        2464, /* glVertexStream4fATI */
        2465, /* glVertexStream4fvATI */
        2466, /* glVertexStream4iATI */
        2467, /* glVertexStream4ivATI */
        2468, /* glVertexStream4sATI */
        2469  /* glVertexStream4svATI */
    };
    uint32_t i;
    if(!context->ATI_vertex_streams) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_CHROMIUM_bind_uniform_location(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2548  /* glBindUniformLocationCHROMIUM */
    };
    uint32_t i;
    if(!context->CHROMIUM_bind_uniform_location) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_CHROMIUM_copy_compressed_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2569  /* glCompressedCopyTextureCHROMIUM */
    };
    uint32_t i;
    if(!context->CHROMIUM_copy_compressed_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_CHROMIUM_copy_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2580, /* glCopySubTextureCHROMIUM */
        2583  /* glCopyTextureCHROMIUM */
    };
    uint32_t i;
    if(!context->CHROMIUM_copy_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_CHROMIUM_framebuffer_mixed_samples(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2586  /* glCoverageModulationCHROMIUM */
    };
    uint32_t i;
    if(!context->CHROMIUM_framebuffer_mixed_samples) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_CHROMIUM_lose_context(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2776  /* glLoseContextCHROMIUM */
    };
    uint32_t i;
    if(!context->CHROMIUM_lose_context) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_EGL_image_storage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         453, /* glEGLImageTargetTexStorageEXT */
         454  /* glEGLImageTargetTextureStorageEXT */
    };
    uint32_t i;
    if(!context->EXT_EGL_image_storage) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_base_instance(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2608, /* glDrawArraysInstancedBaseInstanceEXT */
        2616, /* glDrawElementsInstancedBaseInstanceEXT */
        2618  /* glDrawElementsInstancedBaseVertexBaseInstanceEXT */
    };
    uint32_t i;
    if(!context->EXT_base_instance) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_bindable_uniform(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         926, /* glGetUniformBufferSizeEXT */
         930, /* glGetUniformOffsetEXT */
        2093  /* glUniformBufferEXT */
    };
    uint32_t i;
    if(!context->EXT_bindable_uniform) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_blend_color(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         104  /* glBlendColorEXT */
    };
    uint32_t i;
    if(!context->EXT_blend_color) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_blend_equation_separate(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         110  /* glBlendEquationSeparateEXT */
    };
    uint32_t i;
    if(!context->EXT_blend_equation_separate) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_blend_func_extended(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          54, /* glBindFragDataLocationEXT */
        2546, /* glBindFragDataLocationIndexedEXT */
        2686, /* glGetFragDataIndexEXT */
        2715  /* glGetProgramResourceLocationIndexEXT */
    };
    uint32_t i;
    if(!context->EXT_blend_func_extended) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_blend_func_separate(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         119  /* glBlendFuncSeparateEXT */
    };
    uint32_t i;
    if(!context->EXT_blend_func_separate) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_blend_minmax(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         107  /* glBlendEquationEXT */
    };
    uint32_t i;
    if(!context->EXT_blend_minmax) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_buffer_storage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2561  /* glBufferStorageEXT */
    };
    uint32_t i;
    if(!context->EXT_buffer_storage) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_clear_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2563, /* glClearTexImageEXT */
        2564  /* glClearTexSubImageEXT */
    };
    uint32_t i;
    if(!context->EXT_clear_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_clip_control(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2566  /* glClipControlEXT */
    };
    uint32_t i;
    if(!context->EXT_clip_control) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_color_subtable(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         213, /* glColorSubTableEXT */
         268  /* glCopyColorSubTableEXT */
    };
    uint32_t i;
    if(!context->EXT_color_subtable) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_compiled_vertex_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1120, /* glLockArraysEXT */
        2122  /* glUnlockArraysEXT */
    };
    uint32_t i;
    if(!context->EXT_compiled_vertex_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_convolution(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         259, /* glConvolutionFilter1DEXT */
         260, /* glConvolutionFilter2DEXT */
         261, /* glConvolutionParameterfEXT */
         262, /* glConvolutionParameterfvEXT */
         263, /* glConvolutionParameteriEXT */
         264, /* glConvolutionParameterivEXT */
         270, /* glCopyConvolutionFilter1DEXT */
         271, /* glCopyConvolutionFilter2DEXT */
         657, /* glGetConvolutionFilterEXT */
         658, /* glGetConvolutionParameterfvEXT */
         659, /* glGetConvolutionParameterivEXT */
         867, /* glGetSeparableFilterEXT */
        1763  /* glSeparableFilter2DEXT */
    };
    uint32_t i;
    if(!context->EXT_convolution) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_coordinate_frame(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          89, /* glBinormal3bEXT */
          90, /* glBinormal3bvEXT */
          91, /* glBinormal3dEXT */
          92, /* glBinormal3dvEXT */
          93, /* glBinormal3fEXT */
          94, /* glBinormal3fvEXT */
          95, /* glBinormal3iEXT */
          96, /* glBinormal3ivEXT */
          97, /* glBinormal3sEXT */
          98, /* glBinormal3svEXT */
          99, /* glBinormalPointerEXT */
        1818, /* glTangent3bEXT */
        1819, /* glTangent3bvEXT */
        1820, /* glTangent3dEXT */
        1821, /* glTangent3dvEXT */
        1822, /* glTangent3fEXT */
        1823, /* glTangent3fvEXT */
        1824, /* glTangent3iEXT */
        1825, /* glTangent3ivEXT */
        1826, /* glTangent3sEXT */
        1827, /* glTangent3svEXT */
        1828  /* glTangentPointerEXT */
    };
    uint32_t i;
    if(!context->EXT_coordinate_frame) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_copy_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2577  /* glCopyImageSubDataEXT */
    };
    uint32_t i;
    if(!context->EXT_copy_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_copy_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         282, /* glCopyTexImage1DEXT */
         284, /* glCopyTexImage2DEXT */
         286, /* glCopyTexSubImage1DEXT */
         288, /* glCopyTexSubImage2DEXT */
         290  /* glCopyTexSubImage3DEXT */
    };
    uint32_t i;
    if(!context->EXT_copy_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_cull_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         328, /* glCullParameterdvEXT */
         329  /* glCullParameterfvEXT */
    };
    uint32_t i;
    if(!context->EXT_cull_vertex) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_debug_label(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         779, /* glGetObjectLabelEXT */
        1099  /* glLabelObjectEXT */
    };
    uint32_t i;
    if(!context->EXT_debug_label) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_debug_marker(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1038, /* glInsertEventMarkerEXT */
        1461, /* glPopGroupMarkerEXT */
        1655  /* glPushGroupMarkerEXT */
    };
    uint32_t i;
    if(!context->EXT_debug_marker) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_depth_bounds_test(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         381  /* glDepthBoundsEXT */
    };
    uint32_t i;
    if(!context->EXT_depth_bounds_test) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_direct_state_access(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          64, /* glBindMultiTextureEXT */
         148, /* glCheckNamedFramebufferStatusEXT */
         169, /* glClearNamedBufferDataEXT */
         171, /* glClearNamedBufferSubDataEXT */
         181, /* glClientAttribDefaultEXT */
         230, /* glCompressedMultiTexImage1DEXT */
         231, /* glCompressedMultiTexImage2DEXT */
         232, /* glCompressedMultiTexImage3DEXT */
         233, /* glCompressedMultiTexSubImage1DEXT */
         234, /* glCompressedMultiTexSubImage2DEXT */
         235, /* glCompressedMultiTexSubImage3DEXT */
         248, /* glCompressedTextureImage1DEXT */
         249, /* glCompressedTextureImage2DEXT */
         250, /* glCompressedTextureImage3DEXT */
         252, /* glCompressedTextureSubImage1DEXT */
         254, /* glCompressedTextureSubImage2DEXT */
         256, /* glCompressedTextureSubImage3DEXT */
         274, /* glCopyMultiTexImage1DEXT */
         275, /* glCopyMultiTexImage2DEXT */
         276, /* glCopyMultiTexSubImage1DEXT */
         277, /* glCopyMultiTexSubImage2DEXT */
         278, /* glCopyMultiTexSubImage3DEXT */
         291, /* glCopyTextureImage1DEXT */
         292, /* glCopyTextureImage2DEXT */
         294, /* glCopyTextureSubImage1DEXT */
         296, /* glCopyTextureSubImage2DEXT */
         298, /* glCopyTextureSubImage3DEXT */
         398, /* glDisableClientStateIndexedEXT */
         399, /* glDisableClientStateiEXT */
         400, /* glDisableIndexedEXT */
         403, /* glDisableVertexArrayAttribEXT */
         404, /* glDisableVertexArrayEXT */
         461, /* glEnableClientStateIndexedEXT */
         462, /* glEnableClientStateiEXT */
         463, /* glEnableIndexedEXT */
         466, /* glEnableVertexArrayAttribEXT */
         467, /* glEnableVertexArrayEXT */
         508, /* glFlushMappedNamedBufferRangeEXT */
         542, /* glFramebufferDrawBufferEXT */
         543, /* glFramebufferDrawBuffersEXT */
         547, /* glFramebufferReadBufferEXT */
         604, /* glGenerateMultiTexMipmapEXT */
         606, /* glGenerateTextureMipmapEXT */
         626, /* glGetBooleanIndexedvEXT */
         651, /* glGetCompressedMultiTexImageEXT */
         655, /* glGetCompressedTextureImageEXT */
         666, /* glGetDoubleIndexedvEXT */
         668, /* glGetDoublei_vEXT */
         676, /* glGetFloatIndexedvEXT */
         678, /* glGetFloati_vEXT */
         692, /* glGetFramebufferParameterivEXT */
         709, /* glGetIntegerIndexedvEXT */
         738, /* glGetMultiTexEnvfvEXT */
         739, /* glGetMultiTexEnvivEXT */
         740, /* glGetMultiTexGendvEXT */
         741, /* glGetMultiTexGenfvEXT */
         742, /* glGetMultiTexGenivEXT */
         743, /* glGetMultiTexImageEXT */
         744, /* glGetMultiTexLevelParameterfvEXT */
         745, /* glGetMultiTexLevelParameterivEXT */
         746, /* glGetMultiTexParameterIivEXT */
         747, /* glGetMultiTexParameterIuivEXT */
         748, /* glGetMultiTexParameterfvEXT */
         749, /* glGetMultiTexParameterivEXT */
         754, /* glGetNamedBufferParameterivEXT */
         757, /* glGetNamedBufferPointervEXT */
         759, /* glGetNamedBufferSubDataEXT */
         761, /* glGetNamedFramebufferAttachmentParameterivEXT */
         764, /* glGetNamedFramebufferParameterivEXT */
         765, /* glGetNamedProgramLocalParameterIivEXT */
         766, /* glGetNamedProgramLocalParameterIuivEXT */
         767, /* glGetNamedProgramLocalParameterdvEXT */
         768, /* glGetNamedProgramLocalParameterfvEXT */
         769, /* glGetNamedProgramStringEXT */
         770, /* glGetNamedProgramivEXT */
         772, /* glGetNamedRenderbufferParameterivEXT */
         810, /* glGetPointerIndexedvEXT */
         811, /* glGetPointeri_vEXT */
         902, /* glGetTextureImageEXT */
         904, /* glGetTextureLevelParameterfvEXT */
         906, /* glGetTextureLevelParameterivEXT */
         908, /* glGetTextureParameterIivEXT */
         910, /* glGetTextureParameterIuivEXT */
         912, /* glGetTextureParameterfvEXT */
         914, /* glGetTextureParameterivEXT */
         954, /* glGetVertexArrayIntegeri_vEXT */
         955, /* glGetVertexArrayIntegervEXT */
         956, /* glGetVertexArrayPointeri_vEXT */
         957, /* glGetVertexArrayPointervEXT */
        1056, /* glIsEnabledIndexedEXT */
        1143, /* glMapNamedBufferEXT */
        1145, /* glMapNamedBufferRangeEXT */
        1156, /* glMatrixFrustumEXT */
        1163, /* glMatrixLoadIdentityEXT */
        1165, /* glMatrixLoadTransposedEXT */
        1166, /* glMatrixLoadTransposefEXT */
        1167, /* glMatrixLoaddEXT */
        1168, /* glMatrixLoadfEXT */
        1172, /* glMatrixMultTransposedEXT */
        1173, /* glMatrixMultTransposefEXT */
        1174, /* glMatrixMultdEXT */
        1175, /* glMatrixMultfEXT */
        1176, /* glMatrixOrthoEXT */
        1177, /* glMatrixPopEXT */
        1178, /* glMatrixPushEXT */
        1179, /* glMatrixRotatedEXT */
        1180, /* glMatrixRotatefEXT */
        1181, /* glMatrixScaledEXT */
        1182, /* glMatrixScalefEXT */
        1183, /* glMatrixTranslatedEXT */
        1184, /* glMatrixTranslatefEXT */
        1221, /* glMultiTexBufferEXT */
        1278, /* glMultiTexCoordPointerEXT */
        1279, /* glMultiTexEnvfEXT */
        1280, /* glMultiTexEnvfvEXT */
        1281, /* glMultiTexEnviEXT */
        1282, /* glMultiTexEnvivEXT */
        1283, /* glMultiTexGendEXT */
        1284, /* glMultiTexGendvEXT */
        1285, /* glMultiTexGenfEXT */
        1286, /* glMultiTexGenfvEXT */
        1287, /* glMultiTexGeniEXT */
        1288, /* glMultiTexGenivEXT */
        1289, /* glMultiTexImage1DEXT */
        1290, /* glMultiTexImage2DEXT */
        1291, /* glMultiTexImage3DEXT */
        1292, /* glMultiTexParameterIivEXT */
        1293, /* glMultiTexParameterIuivEXT */
        1294, /* glMultiTexParameterfEXT */
        1295, /* glMultiTexParameterfvEXT */
        1296, /* glMultiTexParameteriEXT */
        1297, /* glMultiTexParameterivEXT */
        1298, /* glMultiTexRenderbufferEXT */
        1299, /* glMultiTexSubImage1DEXT */
        1300, /* glMultiTexSubImage2DEXT */
        1301, /* glMultiTexSubImage3DEXT */
        1318, /* glNamedBufferDataEXT */
        1323, /* glNamedBufferStorageEXT */
        1327, /* glNamedBufferSubDataEXT */
        1328, /* glNamedCopyBufferSubDataEXT */
        1332, /* glNamedFramebufferParameteriEXT */
        1335, /* glNamedFramebufferRenderbufferEXT */
        1340, /* glNamedFramebufferTexture1DEXT */
        1341, /* glNamedFramebufferTexture2DEXT */
        1342, /* glNamedFramebufferTexture3DEXT */
        1343, /* glNamedFramebufferTextureEXT */
        1344, /* glNamedFramebufferTextureFaceEXT */
        1346, /* glNamedFramebufferTextureLayerEXT */
        1348, /* glNamedProgramLocalParameter4dEXT */
        1349, /* glNamedProgramLocalParameter4dvEXT */
        1350, /* glNamedProgramLocalParameter4fEXT */
        1351, /* glNamedProgramLocalParameter4fvEXT */
        1352, /* glNamedProgramLocalParameterI4iEXT */
        1353, /* glNamedProgramLocalParameterI4ivEXT */
        1354, /* glNamedProgramLocalParameterI4uiEXT */
        1355, /* glNamedProgramLocalParameterI4uivEXT */
        1356, /* glNamedProgramLocalParameters4fvEXT */
        1357, /* glNamedProgramLocalParametersI4ivEXT */
        1358, /* glNamedProgramLocalParametersI4uivEXT */
        1359, /* glNamedProgramStringEXT */
        1361, /* glNamedRenderbufferStorageEXT */
        1364, /* glNamedRenderbufferStorageMultisampleCoverageEXT */
        1365, /* glNamedRenderbufferStorageMultisampleEXT */
        1513, /* glProgramUniform1dEXT */
        1515, /* glProgramUniform1dvEXT */
        1517, /* glProgramUniform1fEXT */
        1519, /* glProgramUniform1fvEXT */
        1525, /* glProgramUniform1iEXT */
        1527, /* glProgramUniform1ivEXT */
        1533, /* glProgramUniform1uiEXT */
        1535, /* glProgramUniform1uivEXT */
        1537, /* glProgramUniform2dEXT */
        1539, /* glProgramUniform2dvEXT */
        1541, /* glProgramUniform2fEXT */
        1543, /* glProgramUniform2fvEXT */
        1549, /* glProgramUniform2iEXT */
        1551, /* glProgramUniform2ivEXT */
        1557, /* glProgramUniform2uiEXT */
        1559, /* glProgramUniform2uivEXT */
        1561, /* glProgramUniform3dEXT */
        1563, /* glProgramUniform3dvEXT */
        1565, /* glProgramUniform3fEXT */
        1567, /* glProgramUniform3fvEXT */
        1573, /* glProgramUniform3iEXT */
        1575, /* glProgramUniform3ivEXT */
        1581, /* glProgramUniform3uiEXT */
        1583, /* glProgramUniform3uivEXT */
        1585, /* glProgramUniform4dEXT */
        1587, /* glProgramUniform4dvEXT */
        1589, /* glProgramUniform4fEXT */
        1591, /* glProgramUniform4fvEXT */
        1597, /* glProgramUniform4iEXT */
        1599, /* glProgramUniform4ivEXT */
        1605, /* glProgramUniform4uiEXT */
        1607, /* glProgramUniform4uivEXT */
        1613, /* glProgramUniformMatrix2dvEXT */
        1615, /* glProgramUniformMatrix2fvEXT */
        1617, /* glProgramUniformMatrix2x3dvEXT */
        1619, /* glProgramUniformMatrix2x3fvEXT */
        1621, /* glProgramUniformMatrix2x4dvEXT */
        1623, /* glProgramUniformMatrix2x4fvEXT */
        1625, /* glProgramUniformMatrix3dvEXT */
        1627, /* glProgramUniformMatrix3fvEXT */
        1629, /* glProgramUniformMatrix3x2dvEXT */
        1631, /* glProgramUniformMatrix3x2fvEXT */
        1633, /* glProgramUniformMatrix3x4dvEXT */
        1635, /* glProgramUniformMatrix3x4fvEXT */
        1637, /* glProgramUniformMatrix4dvEXT */
        1639, /* glProgramUniformMatrix4fvEXT */
        1641, /* glProgramUniformMatrix4x2dvEXT */
        1643, /* glProgramUniformMatrix4x2fvEXT */
        1645, /* glProgramUniformMatrix4x3dvEXT */
        1647, /* glProgramUniformMatrix4x3fvEXT */
        1653, /* glPushClientAttribDefaultEXT */
        1941, /* glTextureBufferEXT */
        1943, /* glTextureBufferRangeEXT */
        1945, /* glTextureImage1DEXT */
        1946, /* glTextureImage2DEXT */
        1949, /* glTextureImage3DEXT */
        1955, /* glTexturePageCommitmentEXT */
        1958, /* glTextureParameterIivEXT */
        1960, /* glTextureParameterIuivEXT */
        1962, /* glTextureParameterfEXT */
        1964, /* glTextureParameterfvEXT */
        1966, /* glTextureParameteriEXT */
        1968, /* glTextureParameterivEXT */
        1970, /* glTextureRenderbufferEXT */
        1972, /* glTextureStorage1DEXT */
        1974, /* glTextureStorage2DEXT */
        1976, /* glTextureStorage2DMultisampleEXT */
        1978, /* glTextureStorage3DEXT */
        1980, /* glTextureStorage3DMultisampleEXT */
        1988, /* glTextureSubImage1DEXT */
        1990, /* glTextureSubImage2DEXT */
        1992, /* glTextureSubImage3DEXT */
        2126, /* glUnmapNamedBufferEXT */
        2181, /* glVertexArrayBindVertexBufferEXT */
        2183, /* glVertexArrayColorOffsetEXT */
        2184, /* glVertexArrayEdgeFlagOffsetEXT */
        2186, /* glVertexArrayFogCoordOffsetEXT */
        2187, /* glVertexArrayIndexOffsetEXT */
        2188, /* glVertexArrayMultiTexCoordOffsetEXT */
        2189, /* glVertexArrayNormalOffsetEXT */
        2193, /* glVertexArraySecondaryColorOffsetEXT */
        2194, /* glVertexArrayTexCoordOffsetEXT */
        2195, /* glVertexArrayVertexAttribBindingEXT */
        2196, /* glVertexArrayVertexAttribDivisorEXT */
        2197, /* glVertexArrayVertexAttribFormatEXT */
        2198, /* glVertexArrayVertexAttribIFormatEXT */
        2199, /* glVertexArrayVertexAttribIOffsetEXT */
        2200, /* glVertexArrayVertexAttribLFormatEXT */
        2201, /* glVertexArrayVertexAttribLOffsetEXT */
        2202, /* glVertexArrayVertexAttribOffsetEXT */
        2203, /* glVertexArrayVertexBindingDivisorEXT */
        2206  /* glVertexArrayVertexOffsetEXT */
    };
    uint32_t i;
    if(!context->EXT_direct_state_access) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_discard_framebuffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2605  /* glDiscardFramebufferEXT */
    };
    uint32_t i;
    if(!context->EXT_discard_framebuffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_disjoint_timer_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2545, /* glBeginQueryEXT */
        2593, /* glDeleteQueriesEXT */
        2633, /* glEndQueryEXT */
        2670, /* glGenQueriesEXT */
        2699, /* glGetInteger64vEXT */
         850, /* glGetQueryObjecti64vEXT */
        2718, /* glGetQueryObjectivEXT */
         854, /* glGetQueryObjectui64vEXT */
        2721, /* glGetQueryObjectuivEXT */
        2723, /* glGetQueryivEXT */
        2771, /* glIsQueryEXT */
        2808  /* glQueryCounterEXT */
    };
    uint32_t i;
    if(!context->EXT_disjoint_timer_query) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_draw_buffers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2610  /* glDrawBuffersEXT */
    };
    uint32_t i;
    if(!context->EXT_draw_buffers) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_draw_buffers2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         208, /* glColorMaskIndexedEXT */
         400, /* glDisableIndexedEXT */
         463, /* glEnableIndexedEXT */
         626, /* glGetBooleanIndexedvEXT */
         709, /* glGetIntegerIndexedvEXT */
        1056  /* glIsEnabledIndexedEXT */
    };
    uint32_t i;
    if(!context->EXT_draw_buffers2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_draw_buffers_indexed(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2551, /* glBlendEquationSeparateiEXT */
        2553, /* glBlendEquationiEXT */
        2555, /* glBlendFuncSeparateiEXT */
        2557, /* glBlendFunciEXT */
        2567, /* glColorMaskiEXT */
        2602, /* glDisableiEXT */
        2629, /* glEnableiEXT */
        2767  /* glIsEnablediEXT */
    };
    uint32_t i;
    if(!context->EXT_draw_buffers_indexed) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_draw_elements_base_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2613, /* glDrawElementsBaseVertexEXT */
        2619, /* glDrawElementsInstancedBaseVertexEXT */
        2622, /* glDrawRangeElementsBaseVertexEXT */
        2788  /* glMultiDrawElementsBaseVertexEXT */
    };
    uint32_t i;
    if(!context->EXT_draw_elements_base_vertex) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_draw_instanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         418, /* glDrawArraysInstancedEXT */
         437  /* glDrawElementsInstancedEXT */
    };
    uint32_t i;
    if(!context->EXT_draw_instanced) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_draw_range_elements(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         445  /* glDrawRangeElementsEXT */
    };
    uint32_t i;
    if(!context->EXT_draw_range_elements) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_draw_transform_feedback(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2624, /* glDrawTransformFeedbackEXT */
        2625  /* glDrawTransformFeedbackInstancedEXT */
    };
    uint32_t i;
    if(!context->EXT_draw_transform_feedback) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_external_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         140, /* glBufferStorageExternalEXT */
        1324  /* glNamedBufferStorageExternalEXT */
    };
    uint32_t i;
    if(!context->EXT_external_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_fog_coord(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         515, /* glFogCoordPointerEXT */
         517, /* glFogCoorddEXT */
         518, /* glFogCoorddvEXT */
         519, /* glFogCoordfEXT */
         520  /* glFogCoordfvEXT */
    };
    uint32_t i;
    if(!context->EXT_fog_coord) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_fragment_shading_rate(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2660, /* glFramebufferShadingRateEXT */
        2687, /* glGetFragmentShadingRatesEXT */
        2837, /* glShadingRateCombinerOpsEXT */
        2838  /* glShadingRateEXT */
    };
    uint32_t i;
    if(!context->EXT_fragment_shading_rate) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_framebuffer_blit(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         128  /* glBlitFramebufferEXT */
    };
    uint32_t i;
    if(!context->EXT_framebuffer_blit) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_framebuffer_blit_layers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         129, /* glBlitFramebufferLayerEXT */
         130  /* glBlitFramebufferLayersEXT */
    };
    uint32_t i;
    if(!context->EXT_framebuffer_blit_layers) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_framebuffer_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1684  /* glRenderbufferStorageMultisampleEXT */
    };
    uint32_t i;
    if(!context->EXT_framebuffer_multisample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_framebuffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          58, /* glBindFramebufferEXT */
          70, /* glBindRenderbufferEXT */
         146, /* glCheckFramebufferStatusEXT */
         351, /* glDeleteFramebuffersEXT */
         368, /* glDeleteRenderbuffersEXT */
         549, /* glFramebufferRenderbufferEXT */
         555, /* glFramebufferTexture1DEXT */
         557, /* glFramebufferTexture2DEXT */
         559, /* glFramebufferTexture3DEXT */
         579, /* glGenFramebuffersEXT */
         591, /* glGenRenderbuffersEXT */
         603, /* glGenerateMipmapEXT */
         689, /* glGetFramebufferAttachmentParameterivEXT */
         860, /* glGetRenderbufferParameterivEXT */
        1061, /* glIsFramebufferEXT */
        1080, /* glIsRenderbufferEXT */
        1680  /* glRenderbufferStorageEXT */
    };
    uint32_t i;
    if(!context->EXT_framebuffer_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_geometry_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         561  /* glFramebufferTextureEXT */
    };
    uint32_t i;
    if(!context->EXT_geometry_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_geometry_shader4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1506  /* glProgramParameteriEXT */
    };
    uint32_t i;
    if(!context->EXT_geometry_shader4) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_gpu_program_parameters(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1482, /* glProgramEnvParameters4fvEXT */
        1493  /* glProgramLocalParameters4fvEXT */
    };
    uint32_t i;
    if(!context->EXT_gpu_program_parameters) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_gpu_shader4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          54, /* glBindFragDataLocationEXT */
         683, /* glGetFragDataLocationEXT */
         942, /* glGetUniformuivEXT */
         962, /* glGetVertexAttribIivEXT */
         964, /* glGetVertexAttribIuivEXT */
        2023, /* glUniform1uiEXT */
        2025, /* glUniform1uivEXT */
        2045, /* glUniform2uiEXT */
        2047, /* glUniform2uivEXT */
        2067, /* glUniform3uiEXT */
        2069, /* glUniform3uivEXT */
        2089, /* glUniform4uiEXT */
        2091, /* glUniform4uivEXT */
        2320, /* glVertexAttribI1iEXT */
        2322, /* glVertexAttribI1ivEXT */
        2324, /* glVertexAttribI1uiEXT */
        2326, /* glVertexAttribI1uivEXT */
        2328, /* glVertexAttribI2iEXT */
        2330, /* glVertexAttribI2ivEXT */
        2332, /* glVertexAttribI2uiEXT */
        2334, /* glVertexAttribI2uivEXT */
        2336, /* glVertexAttribI3iEXT */
        2338, /* glVertexAttribI3ivEXT */
        2340, /* glVertexAttribI3uiEXT */
        2342, /* glVertexAttribI3uivEXT */
        2344, /* glVertexAttribI4bvEXT */
        2346, /* glVertexAttribI4iEXT */
        2348, /* glVertexAttribI4ivEXT */
        2350, /* glVertexAttribI4svEXT */
        2352, /* glVertexAttribI4ubvEXT */
        2354, /* glVertexAttribI4uiEXT */
        2356, /* glVertexAttribI4uivEXT */
        2358, /* glVertexAttribI4usvEXT */
        2362  /* glVertexAttribIPointerEXT */
    };
    uint32_t i;
    if(!context->EXT_gpu_shader4) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_histogram(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         697, /* glGetHistogramEXT */
         698, /* glGetHistogramParameterfvEXT */
         699, /* glGetHistogramParameterivEXT */
         735, /* glGetMinmaxEXT */
         736, /* glGetMinmaxParameterfvEXT */
         737, /* glGetMinmaxParameterivEXT */
        1015, /* glHistogramEXT */
        1193, /* glMinmaxEXT */
        1709, /* glResetHistogramEXT */
        1711  /* glResetMinmaxEXT */
    };
    uint32_t i;
    if(!context->EXT_histogram) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_index_func(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1031  /* glIndexFuncEXT */
    };
    uint32_t i;
    if(!context->EXT_index_func) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_index_material(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1032  /* glIndexMaterialEXT */
    };
    uint32_t i;
    if(!context->EXT_index_material) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_instanced_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         418, /* glDrawArraysInstancedEXT */
         437, /* glDrawElementsInstancedEXT */
        2878  /* glVertexAttribDivisorEXT */
    };
    uint32_t i;
    if(!context->EXT_instanced_arrays) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_light_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          14, /* glApplyTextureEXT */
        1952, /* glTextureLightEXT */
        1953  /* glTextureMaterialEXT */
    };
    uint32_t i;
    if(!context->EXT_light_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_map_buffer_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2649, /* glFlushMappedBufferRangeEXT */
        2780  /* glMapBufferRangeEXT */
    };
    uint32_t i;
    if(!context->EXT_map_buffer_range) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_memory_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         141, /* glBufferStorageMemEXT */
         308, /* glCreateMemoryObjectsEXT */
         352, /* glDeleteMemoryObjectsEXT */
         734, /* glGetMemoryObjectParameterivEXT */
         943, /* glGetUnsignedBytei_vEXT */
         944, /* glGetUnsignedBytevEXT */
        1064, /* glIsMemoryObjectEXT */
        1190, /* glMemoryObjectParameterivEXT */
        1325, /* glNamedBufferStorageMemEXT */
        1920, /* glTexStorageMem1DEXT */
        1921, /* glTexStorageMem2DEXT */
        1922, /* glTexStorageMem2DMultisampleEXT */
        1923, /* glTexStorageMem3DEXT */
        1924, /* glTexStorageMem3DMultisampleEXT */
        1981, /* glTextureStorageMem1DEXT */
        1982, /* glTextureStorageMem2DEXT */
        1983, /* glTextureStorageMem2DMultisampleEXT */
        1984, /* glTextureStorageMem3DEXT */
        1985  /* glTextureStorageMem3DMultisampleEXT */
    };
    uint32_t i;
    if(!context->EXT_memory_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_memory_object_fd(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1021  /* glImportMemoryFdEXT */
    };
    uint32_t i;
    if(!context->EXT_memory_object_fd) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_memory_object_win32(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1022, /* glImportMemoryWin32HandleEXT */
        1023  /* glImportMemoryWin32NameEXT */
    };
    uint32_t i;
    if(!context->EXT_memory_object_win32) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_multi_draw_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1199, /* glMultiDrawArraysEXT */
        1209  /* glMultiDrawElementsEXT */
    };
    uint32_t i;
    if(!context->EXT_multi_draw_arrays) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_multi_draw_indirect(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2784, /* glMultiDrawArraysIndirectEXT */
        2789  /* glMultiDrawElementsIndirectEXT */
    };
    uint32_t i;
    if(!context->EXT_multi_draw_indirect) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1720, /* glSampleMaskEXT */
        1724  /* glSamplePatternEXT */
    };
    uint32_t i;
    if(!context->EXT_multisample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_multisampled_render_to_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2662, /* glFramebufferTexture2DMultisampleEXT */
        1684  /* glRenderbufferStorageMultisampleEXT */
    };
    uint32_t i;
    if(!context->EXT_multisampled_render_to_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_multiview_draw_buffers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2611, /* glDrawBuffersIndexedEXT */
        2701, /* glGetIntegeri_vEXT */
        2809  /* glReadBufferIndexedEXT */
    };
    uint32_t i;
    if(!context->EXT_multiview_draw_buffers) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_occlusion_query_boolean(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2545, /* glBeginQueryEXT */
        2593, /* glDeleteQueriesEXT */
        2633, /* glEndQueryEXT */
        2670, /* glGenQueriesEXT */
        2721, /* glGetQueryObjectuivEXT */
        2723, /* glGetQueryivEXT */
        2771  /* glIsQueryEXT */
    };
    uint32_t i;
    if(!context->EXT_occlusion_query_boolean) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_paletted_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         214, /* glColorTableEXT */
         639, /* glGetColorTableEXT */
         640, /* glGetColorTableParameterfvEXT */
         642  /* glGetColorTableParameterivEXT */
    };
    uint32_t i;
    if(!context->EXT_paletted_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_pixel_transform(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         808, /* glGetPixelTransformParameterfvEXT */
         809, /* glGetPixelTransformParameterivEXT */
        1431, /* glPixelTransformParameterfEXT */
        1432, /* glPixelTransformParameterfvEXT */
        1433, /* glPixelTransformParameteriEXT */
        1434  /* glPixelTransformParameterivEXT */
    };
    uint32_t i;
    if(!context->EXT_pixel_transform) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_point_parameters(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1439, /* glPointParameterfEXT */
        1443  /* glPointParameterfvEXT */
    };
    uint32_t i;
    if(!context->EXT_point_parameters) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_polygon_offset(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1458  /* glPolygonOffsetEXT */
    };
    uint32_t i;
    if(!context->EXT_polygon_offset) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_polygon_offset_clamp(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1457  /* glPolygonOffsetClampEXT */
    };
    uint32_t i;
    if(!context->EXT_polygon_offset_clamp) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_primitive_bounding_box(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2801  /* glPrimitiveBoundingBoxEXT */
    };
    uint32_t i;
    if(!context->EXT_primitive_bounding_box) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_provoking_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1652  /* glProvokingVertexEXT */
    };
    uint32_t i;
    if(!context->EXT_provoking_vertex) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_raster_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1667  /* glRasterSamplesEXT */
    };
    uint32_t i;
    if(!context->EXT_raster_multisample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_robustness(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2695, /* glGetGraphicsResetStatusEXT */
        2759, /* glGetnUniformfvEXT */
        2762, /* glGetnUniformivEXT */
        2812  /* glReadnPixelsEXT */
    };
    uint32_t i;
    if(!context->EXT_robustness) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_secondary_color(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1739, /* glSecondaryColor3bEXT */
        1740, /* glSecondaryColor3bvEXT */
        1741, /* glSecondaryColor3dEXT */
        1742, /* glSecondaryColor3dvEXT */
        1743, /* glSecondaryColor3fEXT */
        1744, /* glSecondaryColor3fvEXT */
        1747, /* glSecondaryColor3iEXT */
        1748, /* glSecondaryColor3ivEXT */
        1749, /* glSecondaryColor3sEXT */
        1750, /* glSecondaryColor3svEXT */
        1751, /* glSecondaryColor3ubEXT */
        1752, /* glSecondaryColor3ubvEXT */
        1753, /* glSecondaryColor3uiEXT */
        1754, /* glSecondaryColor3uivEXT */
        1755, /* glSecondaryColor3usEXT */
        1756, /* glSecondaryColor3usvEXT */
        1758  /* glSecondaryColorPointerEXT */
    };
    uint32_t i;
    if(!context->EXT_secondary_color) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_semaphore(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         370, /* glDeleteSemaphoresEXT */
         593, /* glGenSemaphoresEXT */
         866, /* glGetSemaphoreParameterui64vEXT */
         943, /* glGetUnsignedBytei_vEXT */
         944, /* glGetUnsignedBytevEXT */
        1082, /* glIsSemaphoreEXT */
        1762, /* glSemaphoreParameterui64vEXT */
        1782, /* glSignalSemaphoreEXT */
        2485  /* glWaitSemaphoreEXT */
    };
    uint32_t i;
    if(!context->EXT_semaphore) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_semaphore_fd(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1025  /* glImportSemaphoreFdEXT */
    };
    uint32_t i;
    if(!context->EXT_semaphore_fd) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_semaphore_win32(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1026, /* glImportSemaphoreWin32HandleEXT */
        1027  /* glImportSemaphoreWin32NameEXT */
    };
    uint32_t i;
    if(!context->EXT_semaphore_win32) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_separate_shader_objects(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           2, /* glActiveProgramEXT */
        2542, /* glActiveShaderProgramEXT */
        2547, /* glBindProgramPipelineEXT */
         320, /* glCreateShaderProgramEXT */
        2588, /* glCreateShaderProgramvEXT */
        2592, /* glDeleteProgramPipelinesEXT */
        2669, /* glGenProgramPipelinesEXT */
        2713, /* glGetProgramPipelineInfoLogEXT */
        2714, /* glGetProgramPipelineivEXT */
        2770, /* glIsProgramPipelineEXT */
        1506, /* glProgramParameteriEXT */
        1517, /* glProgramUniform1fEXT */
        1519, /* glProgramUniform1fvEXT */
        1525, /* glProgramUniform1iEXT */
        1527, /* glProgramUniform1ivEXT */
        1533, /* glProgramUniform1uiEXT */
        1535, /* glProgramUniform1uivEXT */
        1541, /* glProgramUniform2fEXT */
        1543, /* glProgramUniform2fvEXT */
        1549, /* glProgramUniform2iEXT */
        1551, /* glProgramUniform2ivEXT */
        1557, /* glProgramUniform2uiEXT */
        1559, /* glProgramUniform2uivEXT */
        1565, /* glProgramUniform3fEXT */
        1567, /* glProgramUniform3fvEXT */
        1573, /* glProgramUniform3iEXT */
        1575, /* glProgramUniform3ivEXT */
        1581, /* glProgramUniform3uiEXT */
        1583, /* glProgramUniform3uivEXT */
        1589, /* glProgramUniform4fEXT */
        1591, /* glProgramUniform4fvEXT */
        1597, /* glProgramUniform4iEXT */
        1599, /* glProgramUniform4ivEXT */
        1605, /* glProgramUniform4uiEXT */
        1607, /* glProgramUniform4uivEXT */
        1615, /* glProgramUniformMatrix2fvEXT */
        1619, /* glProgramUniformMatrix2x3fvEXT */
        1623, /* glProgramUniformMatrix2x4fvEXT */
        1627, /* glProgramUniformMatrix3fvEXT */
        1631, /* glProgramUniformMatrix3x2fvEXT */
        1635, /* glProgramUniformMatrix3x4fvEXT */
        1639, /* glProgramUniformMatrix4fvEXT */
        1643, /* glProgramUniformMatrix4x2fvEXT */
        1647, /* glProgramUniformMatrix4x3fvEXT */
        2875, /* glUseProgramStagesEXT */
        2134, /* glUseShaderProgramEXT */
        2876  /* glValidateProgramPipelineEXT */
    };
    uint32_t i;
    if(!context->EXT_separate_shader_objects) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_shader_framebuffer_fetch_non_coherent(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         544  /* glFramebufferFetchBarrierEXT */
    };
    uint32_t i;
    if(!context->EXT_shader_framebuffer_fetch_non_coherent) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_shader_image_load_store(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          60, /* glBindImageTextureEXT */
        1189  /* glMemoryBarrierEXT */
    };
    uint32_t i;
    if(!context->EXT_shader_image_load_store) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_shader_pixel_local_storage2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2562, /* glClearPixelLocalStorageuiEXT */
        2659, /* glFramebufferPixelLocalStorageSizeEXT */
        2694  /* glGetFramebufferPixelLocalStorageSizeEXT */
    };
    uint32_t i;
    if(!context->EXT_shader_pixel_local_storage2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_sparse_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2849  /* glTexPageCommitmentEXT */
    };
    uint32_t i;
    if(!context->EXT_sparse_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_stencil_clear_tag(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1794  /* glStencilClearTagEXT */
    };
    uint32_t i;
    if(!context->EXT_stencil_clear_tag) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_stencil_two_side(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           4  /* glActiveStencilFaceEXT */
    };
    uint32_t i;
    if(!context->EXT_stencil_two_side) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_subtexture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1931, /* glTexSubImage1DEXT */
        1933  /* glTexSubImage2DEXT */
    };
    uint32_t i;
    if(!context->EXT_subtexture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_tessellation_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2794  /* glPatchParameteriEXT */
    };
    uint32_t i;
    if(!context->EXT_tessellation_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture3D(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1895, /* glTexImage3DEXT */
        1935  /* glTexSubImage3DEXT */
    };
    uint32_t i;
    if(!context->EXT_texture3D) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         566  /* glFramebufferTextureLayerEXT */
    };
    uint32_t i;
    if(!context->EXT_texture_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_border_clamp(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2727, /* glGetSamplerParameterIivEXT */
        2730, /* glGetSamplerParameterIuivEXT */
         892, /* glGetTexParameterIivEXT */
         894, /* glGetTexParameterIuivEXT */
        2823, /* glSamplerParameterIivEXT */
        2826, /* glSamplerParameterIuivEXT */
        1902, /* glTexParameterIivEXT */
        1904  /* glTexParameterIuivEXT */
    };
    uint32_t i;
    if(!context->EXT_texture_border_clamp) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1838, /* glTexBufferEXT */
        2842  /* glTexBufferRangeEXT */
    };
    uint32_t i;
    if(!context->EXT_texture_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1838  /* glTexBufferEXT */
    };
    uint32_t i;
    if(!context->EXT_texture_buffer_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_integer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         160, /* glClearColorIiEXT */
         161, /* glClearColorIuiEXT */
         892, /* glGetTexParameterIivEXT */
         894, /* glGetTexParameterIuivEXT */
        1902, /* glTexParameterIivEXT */
        1904  /* glTexParameterIuivEXT */
    };
    uint32_t i;
    if(!context->EXT_texture_integer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          16, /* glAreTexturesResidentEXT */
          76, /* glBindTextureEXT */
         375, /* glDeleteTexturesEXT */
         596, /* glGenTexturesEXT */
        1087, /* glIsTextureEXT */
        1468  /* glPrioritizeTexturesEXT */
    };
    uint32_t i;
    if(!context->EXT_texture_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_perturb_normal(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1954  /* glTextureNormalEXT */
    };
    uint32_t i;
    if(!context->EXT_texture_perturb_normal) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_storage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1913, /* glTexStorage1DEXT */
        1915, /* glTexStorage2DEXT */
        1918, /* glTexStorage3DEXT */
        1972, /* glTextureStorage1DEXT */
        1974, /* glTextureStorage2DEXT */
        1978  /* glTextureStorage3DEXT */
    };
    uint32_t i;
    if(!context->EXT_texture_storage) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_storage_compression(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2858, /* glTexStorageAttribs2DEXT */
        2859  /* glTexStorageAttribs3DEXT */
    };
    uint32_t i;
    if(!context->EXT_texture_storage_compression) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_view(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2864  /* glTextureViewEXT */
    };
    uint32_t i;
    if(!context->EXT_texture_view) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_timer_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         850, /* glGetQueryObjecti64vEXT */
         854  /* glGetQueryObjectui64vEXT */
    };
    uint32_t i;
    if(!context->EXT_timer_query) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_transform_feedback(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          35, /* glBeginTransformFeedbackEXT */
          44, /* glBindBufferBaseEXT */
          46, /* glBindBufferOffsetEXT */
          49, /* glBindBufferRangeEXT */
         483, /* glEndTransformFeedbackEXT */
         920, /* glGetTransformFeedbackVaryingEXT */
        2000  /* glTransformFeedbackVaryingsEXT */
    };
    uint32_t i;
    if(!context->EXT_transform_feedback) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_vertex_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          17, /* glArrayElementEXT */
         210, /* glColorPointerEXT */
         413, /* glDrawArraysEXT */
         456, /* glEdgeFlagPointerEXT */
         813, /* glGetPointervEXT */
        1033, /* glIndexPointerEXT */
        1375, /* glNormalPointerEXT */
        1881, /* glTexCoordPointerEXT */
        2435  /* glVertexPointerEXT */
    };
    uint32_t i;
    if(!context->EXT_vertex_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_vertex_attrib_64bit(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         966, /* glGetVertexAttribLdvEXT */
        2364, /* glVertexAttribL1dEXT */
        2366, /* glVertexAttribL1dvEXT */
        2374, /* glVertexAttribL2dEXT */
        2376, /* glVertexAttribL2dvEXT */
        2382, /* glVertexAttribL3dEXT */
        2384, /* glVertexAttribL3dvEXT */
        2390, /* glVertexAttribL4dEXT */
        2392, /* glVertexAttribL4dvEXT */
        2400  /* glVertexAttribLPointerEXT */
    };
    uint32_t i;
    if(!context->EXT_vertex_attrib_64bit) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_vertex_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          37, /* glBeginVertexShaderEXT */
          62, /* glBindLightParameterEXT */
          63, /* glBindMaterialParameterEXT */
          65, /* glBindParameterEXT */
          74, /* glBindTexGenParameterEXT */
          78, /* glBindTextureUnitParameterEXT */
          86, /* glBindVertexShaderEXT */
         380, /* glDeleteVertexShaderEXT */
         401, /* glDisableVariantClientStateEXT */
         464, /* glEnableVariantClientStateEXT */
         485, /* glEndVertexShaderEXT */
         494, /* glExtractComponentEXT */
         594, /* glGenSymbolsEXT */
         601, /* glGenVertexShadersEXT */
         717, /* glGetInvariantBooleanvEXT */
         718, /* glGetInvariantFloatvEXT */
         719, /* glGetInvariantIntegervEXT */
         723, /* glGetLocalConstantBooleanvEXT */
         724, /* glGetLocalConstantFloatvEXT */
         725, /* glGetLocalConstantIntegervEXT */
         947, /* glGetVariantBooleanvEXT */
         948, /* glGetVariantFloatvEXT */
         949, /* glGetVariantIntegervEXT */
         950, /* glGetVariantPointervEXT */
        1037, /* glInsertComponentEXT */
        1092, /* glIsVariantEnabledEXT */
        1767, /* glSetInvariantEXT */
        1768, /* glSetLocalConstantEXT */
        1771, /* glShaderOp1EXT */
        1772, /* glShaderOp2EXT */
        1773, /* glShaderOp3EXT */
        1815, /* glSwizzleEXT */
        2150, /* glVariantPointerEXT */
        2151, /* glVariantbvEXT */
        2152, /* glVariantdvEXT */
        2153, /* glVariantfvEXT */
        2154, /* glVariantivEXT */
        2155, /* glVariantsvEXT */
        2156, /* glVariantubvEXT */
        2157, /* glVariantuivEXT */
        2158, /* glVariantusvEXT */
        2540  /* glWriteMaskEXT */
    };
    uint32_t i;
    if(!context->EXT_vertex_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_vertex_weighting(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2470, /* glVertexWeightPointerEXT */
        2471, /* glVertexWeightfEXT */
        2472  /* glVertexWeightfvEXT */
    };
    uint32_t i;
    if(!context->EXT_vertex_weighting) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_win32_keyed_mutex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           1, /* glAcquireKeyedMutexWin32EXT */
        1676  /* glReleaseKeyedMutexWin32EXT */
    };
    uint32_t i;
    if(!context->EXT_win32_keyed_mutex) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_window_rectangles(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2539  /* glWindowRectanglesEXT */
    };
    uint32_t i;
    if(!context->EXT_window_rectangles) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_x11_sync_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1029  /* glImportSyncEXT */
    };
    uint32_t i;
    if(!context->EXT_x11_sync_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_GREMEDY_frame_terminator(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         540  /* glFrameTerminatorGREMEDY */
    };
    uint32_t i;
    if(!context->GREMEDY_frame_terminator) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_GREMEDY_string_marker(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1813  /* glStringMarkerGREMEDY */
    };
    uint32_t i;
    if(!context->GREMEDY_string_marker) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_HP_image_transform(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         703, /* glGetImageTransformParameterfvHP */
         704, /* glGetImageTransformParameterivHP */
        1017, /* glImageTransformParameterfHP */
        1018, /* glImageTransformParameterfvHP */
        1019, /* glImageTransformParameteriHP */
        1020  /* glImageTransformParameterivHP */
    };
    uint32_t i;
    if(!context->HP_image_transform) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_IBM_multimode_draw_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1219, /* glMultiModeDrawArraysIBM */
        1220  /* glMultiModeDrawElementsIBM */
    };
    uint32_t i;
    if(!context->IBM_multimode_draw_arrays) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_IBM_static_data(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         511  /* glFlushStaticDataIBM */
    };
    uint32_t i;
    if(!context->IBM_static_data) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_IBM_vertex_array_lists(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         211, /* glColorPointerListIBM */
         457, /* glEdgeFlagPointerListIBM */
         516, /* glFogCoordPointerListIBM */
        1034, /* glIndexPointerListIBM */
        1376, /* glNormalPointerListIBM */
        1759, /* glSecondaryColorPointerListIBM */
        1882, /* glTexCoordPointerListIBM */
        2436  /* glVertexPointerListIBM */
    };
    uint32_t i;
    if(!context->IBM_vertex_array_lists) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_IMG_bindless_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2748, /* glGetTextureHandleIMG */
        2749, /* glGetTextureSamplerHandleIMG */
        2804, /* glProgramUniformHandleui64IMG */
        2805, /* glProgramUniformHandleui64vIMG */
        2866, /* glUniformHandleui64IMG */
        2867  /* glUniformHandleui64vIMG */
    };
    uint32_t i;
    if(!context->IMG_bindless_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_IMG_framebuffer_downsample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2661, /* glFramebufferTexture2DDownsampleIMG */
        2665  /* glFramebufferTextureLayerDownsampleIMG */
    };
    uint32_t i;
    if(!context->IMG_framebuffer_downsample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_IMG_multisampled_render_to_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2663, /* glFramebufferTexture2DMultisampleIMG */
        2818  /* glRenderbufferStorageMultisampleIMG */
    };
    uint32_t i;
    if(!context->IMG_multisampled_render_to_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_INGR_blend_func_separate(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         120  /* glBlendFuncSeparateINGR */
    };
    uint32_t i;
    if(!context->INGR_blend_func_separate) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_INTEL_framebuffer_CMAA(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          13  /* glApplyFramebufferAttachmentCMAAINTEL */
    };
    uint32_t i;
    if(!context->INTEL_framebuffer_CMAA) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_INTEL_map_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1149, /* glMapTexture2DINTEL */
        1816, /* glSyncTextureINTEL */
        2128  /* glUnmapTexture2DINTEL */
    };
    uint32_t i;
    if(!context->INTEL_map_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_INTEL_parallel_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         212, /* glColorPointervINTEL */
        1377, /* glNormalPointervINTEL */
        1883, /* glTexCoordPointervINTEL */
        2437  /* glVertexPointervINTEL */
    };
    uint32_t i;
    if(!context->INTEL_parallel_arrays) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_INTEL_performance_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          30, /* glBeginPerfQueryINTEL */
         309, /* glCreatePerfQueryINTEL */
         359, /* glDeletePerfQueryINTEL */
         478, /* glEndPerfQueryINTEL */
         674, /* glGetFirstPerfQueryIdINTEL */
         775, /* glGetNextPerfQueryIdINTEL */
         795, /* glGetPerfCounterInfoINTEL */
         802, /* glGetPerfQueryDataINTEL */
         803, /* glGetPerfQueryIdByNameINTEL */
         804  /* glGetPerfQueryInfoINTEL */
    };
    uint32_t i;
    if(!context->INTEL_performance_query) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_KHR_blend_equation_advanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         101  /* glBlendBarrierKHR */
    };
    uint32_t i;
    if(!context->KHR_blend_equation_advanced) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_KHR_debug(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         331, /* glDebugMessageCallback */
        2589, /* glDebugMessageCallbackKHR */
         334, /* glDebugMessageControl */
        2590, /* glDebugMessageControlKHR */
         337, /* glDebugMessageInsert */
        2591, /* glDebugMessageInsertKHR */
         662, /* glGetDebugMessageLog */
        2680, /* glGetDebugMessageLogKHR */
         778, /* glGetObjectLabel */
        2707, /* glGetObjectLabelKHR */
         783, /* glGetObjectPtrLabel */
        2708, /* glGetObjectPtrLabelKHR */
         812, /* glGetPointerv */
        2709, /* glGetPointervKHR */
        1388, /* glObjectLabel */
        2792, /* glObjectLabelKHR */
        1389, /* glObjectPtrLabel */
        2793, /* glObjectPtrLabelKHR */
        1460, /* glPopDebugGroup */
        2799, /* glPopDebugGroupKHR */
        1654, /* glPushDebugGroup */
        2807  /* glPushDebugGroupKHR */
    };
    uint32_t i;
    if(!context->KHR_debug) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_KHR_parallel_shader_compile(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1186  /* glMaxShaderCompilerThreadsKHR */
    };
    uint32_t i;
    if(!context->KHR_parallel_shader_compile) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_KHR_robustness(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         694, /* glGetGraphicsResetStatus */
        2696, /* glGetGraphicsResetStatusKHR */
         997, /* glGetnUniformfv */
        2760, /* glGetnUniformfvKHR */
        1000, /* glGetnUniformiv */
        2763, /* glGetnUniformivKHR */
        1003, /* glGetnUniformuiv */
        2765, /* glGetnUniformuivKHR */
        1671, /* glReadnPixels */
        2813  /* glReadnPixelsKHR */
    };
    uint32_t i;
    if(!context->KHR_robustness) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_MESA_framebuffer_flip_y(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         546, /* glFramebufferParameteriMESA */
         693  /* glGetFramebufferParameterivMESA */
    };
    uint32_t i;
    if(!context->MESA_framebuffer_flip_y) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_MESA_resize_buffers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1712  /* glResizeBuffersMESA */
    };
    uint32_t i;
    if(!context->MESA_resize_buffers) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_MESA_sampler_objects(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          71, /* glBindSampler */
         369, /* glDeleteSamplers */
         592, /* glGenSamplers */
         863, /* glGetSamplerParameterfv */
         864, /* glGetSamplerParameteriv */
        1081, /* glIsSampler */
        1728, /* glSamplerParameterf */
        1729, /* glSamplerParameterfv */
        1730, /* glSamplerParameteri */
        1731  /* glSamplerParameteriv */
    };
    uint32_t i;
    if(!context->MESA_sampler_objects) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_MESA_window_pos(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2500, /* glWindowPos2dMESA */
        2502, /* glWindowPos2dvMESA */
        2504, /* glWindowPos2fMESA */
        2506, /* glWindowPos2fvMESA */
        2508, /* glWindowPos2iMESA */
        2510, /* glWindowPos2ivMESA */
        2512, /* glWindowPos2sMESA */
        2514, /* glWindowPos2svMESA */
        2516, /* glWindowPos3dMESA */
        2518, /* glWindowPos3dvMESA */
        2520, /* glWindowPos3fMESA */
        2522, /* glWindowPos3fvMESA */
        2524, /* glWindowPos3iMESA */
        2526, /* glWindowPos3ivMESA */
        2528, /* glWindowPos3sMESA */
        2530, /* glWindowPos3svMESA */
        2531, /* glWindowPos4dMESA */
        2532, /* glWindowPos4dvMESA */
        2533, /* glWindowPos4fMESA */
        2534, /* glWindowPos4fvMESA */
        2535, /* glWindowPos4iMESA */
        2536, /* glWindowPos4ivMESA */
        2537, /* glWindowPos4sMESA */
        2538  /* glWindowPos4svMESA */
    };
    uint32_t i;
    if(!context->MESA_window_pos) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NVX_conditional_render(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          26, /* glBeginConditionalRenderNVX */
         474  /* glEndConditionalRenderNVX */
    };
    uint32_t i;
    if(!context->NVX_conditional_render) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NVX_gpu_multicast2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          19, /* glAsyncCopyBufferSubDataNVX */
          20, /* glAsyncCopyImageSubDataNVX */
        1312, /* glMulticastScissorArrayvNVX */
        1313, /* glMulticastViewportArrayvNVX */
        1314, /* glMulticastViewportPositionWScaleNVX */
        2130  /* glUploadGpuMaskNVX */
    };
    uint32_t i;
    if(!context->NVX_gpu_multicast2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NVX_linked_gpu_multicast(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1096, /* glLGPUCopyImageSubDataNVX */
        1097, /* glLGPUInterlockNVX */
        1098  /* glLGPUNamedBufferSubDataNVX */
    };
    uint32_t i;
    if(!context->NVX_linked_gpu_multicast) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NVX_progress_fence(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         182, /* glClientWaitSemaphoreui64NVX */
         313, /* glCreateProgressFenceNVX */
        1783, /* glSignalSemaphoreui64NVX */
        2486  /* glWaitSemaphoreui64NVX */
    };
    uint32_t i;
    if(!context->NVX_progress_fence) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_alpha_to_coverage_dither_control(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          12  /* glAlphaToCoverageDitherControlNV */
    };
    uint32_t i;
    if(!context->NV_alpha_to_coverage_dither_control) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_bindless_multi_draw_indirect(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1203, /* glMultiDrawArraysIndirectBindlessNV */
        1213  /* glMultiDrawElementsIndirectBindlessNV */
    };
    uint32_t i;
    if(!context->NV_bindless_multi_draw_indirect) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_bindless_multi_draw_indirect_count(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1202, /* glMultiDrawArraysIndirectBindlessCountNV */
        1212  /* glMultiDrawElementsIndirectBindlessCountNV */
    };
    uint32_t i;
    if(!context->NV_bindless_multi_draw_indirect_count) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_bindless_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         702, /* glGetImageHandleNV */
         900, /* glGetTextureHandleNV */
         916, /* glGetTextureSamplerHandleNV */
        1063, /* glIsImageHandleResidentNV */
        1089, /* glIsTextureHandleResidentNV */
        1125, /* glMakeImageHandleNonResidentNV */
        1127, /* glMakeImageHandleResidentNV */
        1131, /* glMakeTextureHandleNonResidentNV */
        1133, /* glMakeTextureHandleResidentNV */
        1609, /* glProgramUniformHandleui64NV */
        1611, /* glProgramUniformHandleui64vNV */
        2095, /* glUniformHandleui64NV */
        2097  /* glUniformHandleui64vNV */
    };
    uint32_t i;
    if(!context->NV_bindless_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_blend_equation_advanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         102, /* glBlendBarrierNV */
         126  /* glBlendParameteriNV */
    };
    uint32_t i;
    if(!context->NV_blend_equation_advanced) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_clip_space_w_scaling(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2483  /* glViewportPositionWScaleNV */
    };
    uint32_t i;
    if(!context->NV_clip_space_w_scaling) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_command_list(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         144, /* glCallCommandListNV */
         225, /* glCommandListSegmentsNV */
         226, /* glCompileCommandListNV */
         306, /* glCreateCommandListsNV */
         322, /* glCreateStatesNV */
         346, /* glDeleteCommandListsNV */
         372, /* glDeleteStatesNV */
         423, /* glDrawCommandsAddressNV */
         424, /* glDrawCommandsNV */
         425, /* glDrawCommandsStatesAddressNV */
         426, /* glDrawCommandsStatesNV */
         650, /* glGetCommandHeaderNV */
         876, /* glGetStageIndexNV */
        1054, /* glIsCommandListNV */
        1084, /* glIsStateNV */
        1109, /* glListDrawCommandsStatesClientNV */
        1793  /* glStateCaptureNV */
    };
    uint32_t i;
    if(!context->NV_command_list) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_conditional_render(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          25, /* glBeginConditionalRenderNV */
         473  /* glEndConditionalRenderNV */
    };
    uint32_t i;
    if(!context->NV_conditional_render) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_conservative_raster(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1814  /* glSubpixelPrecisionBiasNV */
    };
    uint32_t i;
    if(!context->NV_conservative_raster) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_conservative_raster_dilate(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         257  /* glConservativeRasterParameterfNV */
    };
    uint32_t i;
    if(!context->NV_conservative_raster_dilate) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_conservative_raster_pre_snap_triangles(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         258  /* glConservativeRasterParameteriNV */
    };
    uint32_t i;
    if(!context->NV_conservative_raster_pre_snap_triangles) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_copy_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2576  /* glCopyBufferSubDataNV */
    };
    uint32_t i;
    if(!context->NV_copy_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_copy_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         273  /* glCopyImageSubDataNV */
    };
    uint32_t i;
    if(!context->NV_copy_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_coverage_sample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2585, /* glCoverageMaskNV */
        2587  /* glCoverageOperationNV */
    };
    uint32_t i;
    if(!context->NV_coverage_sample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_depth_buffer_float(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         164, /* glClearDepthdNV */
         382, /* glDepthBoundsdNV */
         390  /* glDepthRangedNV */
    };
    uint32_t i;
    if(!context->NV_depth_buffer_float) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_draw_buffers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2612  /* glDrawBuffersNV */
    };
    uint32_t i;
    if(!context->NV_draw_buffers) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_draw_instanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2609, /* glDrawArraysInstancedNV */
        2621  /* glDrawElementsInstancedNV */
    };
    uint32_t i;
    if(!context->NV_draw_instanced) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_draw_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         446  /* glDrawTextureNV */
    };
    uint32_t i;
    if(!context->NV_draw_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_draw_vulkan_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         452, /* glDrawVkImageNV */
         990, /* glGetVkProcAddrNV */
        1784, /* glSignalVkFenceNV */
        1785, /* glSignalVkSemaphoreNV */
        2488  /* glWaitVkSemaphoreNV */
    };
    uint32_t i;
    if(!context->NV_draw_vulkan_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_evaluators(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         491, /* glEvalMapsNV */
         726, /* glGetMapAttribParameterfvNV */
         727, /* glGetMapAttribParameterivNV */
         728, /* glGetMapControlPointsNV */
         729, /* glGetMapParameterfvNV */
         730, /* glGetMapParameterivNV */
        1139, /* glMapControlPointsNV */
        1147, /* glMapParameterfvNV */
        1148  /* glMapParameterivNV */
    };
    uint32_t i;
    if(!context->NV_evaluators) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_explicit_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         751, /* glGetMultisamplefvNV */
        1721, /* glSampleMaskIndexedNV */
        1911  /* glTexRenderbufferNV */
    };
    uint32_t i;
    if(!context->NV_explicit_multisample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_fence(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         348, /* glDeleteFencesNV */
         501, /* glFinishFenceNV */
         576, /* glGenFencesNV */
         671, /* glGetFenceivNV */
        1059, /* glIsFenceNV */
        1765, /* glSetFenceNV */
        1833  /* glTestFenceNV */
    };
    uint32_t i;
    if(!context->NV_fence) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_fragment_coverage_to_color(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         527  /* glFragmentCoverageColorNV */
    };
    uint32_t i;
    if(!context->NV_fragment_coverage_to_color) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_fragment_program(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         825, /* glGetProgramNamedParameterdvNV */
         826, /* glGetProgramNamedParameterfvNV */
        1496, /* glProgramNamedParameter4dNV */
        1497, /* glProgramNamedParameter4dvNV */
        1498, /* glProgramNamedParameter4fNV */
        1499  /* glProgramNamedParameter4fvNV */
    };
    uint32_t i;
    if(!context->NV_fragment_program) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_framebuffer_blit(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2560  /* glBlitFramebufferNV */
    };
    uint32_t i;
    if(!context->NV_framebuffer_blit) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_framebuffer_mixed_samples(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         303, /* glCoverageModulationNV */
         304, /* glCoverageModulationTableNV */
         661, /* glGetCoverageModulationTableNV */
        1667  /* glRasterSamplesEXT */
    };
    uint32_t i;
    if(!context->NV_framebuffer_mixed_samples) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_framebuffer_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2819  /* glRenderbufferStorageMultisampleNV */
    };
    uint32_t i;
    if(!context->NV_framebuffer_multisample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_framebuffer_multisample_coverage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1683  /* glRenderbufferStorageMultisampleCoverageNV */
    };
    uint32_t i;
    if(!context->NV_framebuffer_multisample_coverage) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_geometry_program4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         561, /* glFramebufferTextureEXT */
         563, /* glFramebufferTextureFaceEXT */
         566, /* glFramebufferTextureLayerEXT */
        1650  /* glProgramVertexLimitNV */
    };
    uint32_t i;
    if(!context->NV_geometry_program4) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_gpu_multicast(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1302, /* glMulticastBarrierNV */
        1303, /* glMulticastBlitFramebufferNV */
        1304, /* glMulticastBufferSubDataNV */
        1305, /* glMulticastCopyBufferSubDataNV */
        1306, /* glMulticastCopyImageSubDataNV */
        1307, /* glMulticastFramebufferSampleLocationsfvNV */
        1308, /* glMulticastGetQueryObjecti64vNV */
        1309, /* glMulticastGetQueryObjectivNV */
        1310, /* glMulticastGetQueryObjectui64vNV */
        1311, /* glMulticastGetQueryObjectuivNV */
        1315, /* glMulticastWaitSyncNV */
        1678  /* glRenderGpuMaskNV */
    };
    uint32_t i;
    if(!context->NV_gpu_multicast) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_gpu_program4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         815, /* glGetProgramEnvParameterIivNV */
         816, /* glGetProgramEnvParameterIuivNV */
         821, /* glGetProgramLocalParameterIivNV */
         822, /* glGetProgramLocalParameterIuivNV */
        1478, /* glProgramEnvParameterI4iNV */
        1479, /* glProgramEnvParameterI4ivNV */
        1480, /* glProgramEnvParameterI4uiNV */
        1481, /* glProgramEnvParameterI4uivNV */
        1483, /* glProgramEnvParametersI4ivNV */
        1484, /* glProgramEnvParametersI4uivNV */
        1489, /* glProgramLocalParameterI4iNV */
        1490, /* glProgramLocalParameterI4ivNV */
        1491, /* glProgramLocalParameterI4uiNV */
        1492, /* glProgramLocalParameterI4uivNV */
        1494, /* glProgramLocalParametersI4ivNV */
        1495  /* glProgramLocalParametersI4uivNV */
    };
    uint32_t i;
    if(!context->NV_gpu_program4) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_gpu_program5(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         840, /* glGetProgramSubroutineParameteruivNV */
        1511  /* glProgramSubroutineParametersuivNV */
    };
    uint32_t i;
    if(!context->NV_gpu_program5) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_gpu_shader5(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         936, /* glGetUniformi64vNV */
        1522, /* glProgramUniform1i64NV */
        1524, /* glProgramUniform1i64vNV */
        1530, /* glProgramUniform1ui64NV */
        1532, /* glProgramUniform1ui64vNV */
        1546, /* glProgramUniform2i64NV */
        1548, /* glProgramUniform2i64vNV */
        1554, /* glProgramUniform2ui64NV */
        1556, /* glProgramUniform2ui64vNV */
        1570, /* glProgramUniform3i64NV */
        1572, /* glProgramUniform3i64vNV */
        1578, /* glProgramUniform3ui64NV */
        1580, /* glProgramUniform3ui64vNV */
        1594, /* glProgramUniform4i64NV */
        1596, /* glProgramUniform4i64vNV */
        1602, /* glProgramUniform4ui64NV */
        1604, /* glProgramUniform4ui64vNV */
        2012, /* glUniform1i64NV */
        2014, /* glUniform1i64vNV */
        2020, /* glUniform1ui64NV */
        2022, /* glUniform1ui64vNV */
        2034, /* glUniform2i64NV */
        2036, /* glUniform2i64vNV */
        2042, /* glUniform2ui64NV */
        2044, /* glUniform2ui64vNV */
        2056, /* glUniform3i64NV */
        2058, /* glUniform3i64vNV */
        2064, /* glUniform3ui64NV */
        2066, /* glUniform3ui64vNV */
        2078, /* glUniform4i64NV */
        2080, /* glUniform4i64vNV */
        2086, /* glUniform4ui64NV */
        2088  /* glUniform4ui64vNV */
    };
    uint32_t i;
    if(!context->NV_gpu_shader5) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_half_float(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         189, /* glColor3hNV */
         190, /* glColor3hvNV */
         195, /* glColor4hNV */
         196, /* glColor4hvNV */
         521, /* glFogCoordhNV */
         522, /* glFogCoordhvNV */
        1228, /* glMultiTexCoord1hNV */
        1229, /* glMultiTexCoord1hvNV */
        1242, /* glMultiTexCoord2hNV */
        1243, /* glMultiTexCoord2hvNV */
        1256, /* glMultiTexCoord3hNV */
        1257, /* glMultiTexCoord3hvNV */
        1270, /* glMultiTexCoord4hNV */
        1271, /* glMultiTexCoord4hvNV */
        1370, /* glNormal3hNV */
        1371, /* glNormal3hvNV */
        1745, /* glSecondaryColor3hNV */
        1746, /* glSecondaryColor3hvNV */
        1844, /* glTexCoord1hNV */
        1845, /* glTexCoord1hvNV */
        1860, /* glTexCoord2hNV */
        1861, /* glTexCoord2hvNV */
        1866, /* glTexCoord3hNV */
        1867, /* glTexCoord3hvNV */
        1876, /* glTexCoord4hNV */
        1877, /* glTexCoord4hvNV */
        2161, /* glVertex2hNV */
        2162, /* glVertex2hvNV */
        2167, /* glVertex3hNV */
        2168, /* glVertex3hvNV */
        2173, /* glVertex4hNV */
        2174, /* glVertex4hvNV */
        2219, /* glVertexAttrib1hNV */
        2220, /* glVertexAttrib1hvNV */
        2239, /* glVertexAttrib2hNV */
        2240, /* glVertexAttrib2hvNV */
        2259, /* glVertexAttrib3hNV */
        2260, /* glVertexAttrib3hvNV */
        2295, /* glVertexAttrib4hNV */
        2296, /* glVertexAttrib4hvNV */
        2415, /* glVertexAttribs1hvNV */
        2419, /* glVertexAttribs2hvNV */
        2423, /* glVertexAttribs3hvNV */
        2427, /* glVertexAttribs4hvNV */
        2473, /* glVertexWeighthNV */
        2474  /* glVertexWeighthvNV */
    };
    uint32_t i;
    if(!context->NV_half_float) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_instanced_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2879  /* glVertexAttribDivisorNV */
    };
    uint32_t i;
    if(!context->NV_instanced_arrays) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_internalformat_sample_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         714  /* glGetInternalformatSampleivNV */
    };
    uint32_t i;
    if(!context->NV_internalformat_sample_query) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_memory_attachment(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         133, /* glBufferAttachMemoryNV */
         733, /* glGetMemoryObjectDetachedResourcesuivNV */
        1316, /* glNamedBufferAttachMemoryNV */
        1710, /* glResetMemoryObjectParameterNV */
        1835, /* glTexAttachMemoryNV */
        1937  /* glTextureAttachMemoryNV */
    };
    uint32_t i;
    if(!context->NV_memory_attachment) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_memory_object_sparse(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         137, /* glBufferPageCommitmentMemNV */
        1321, /* glNamedBufferPageCommitmentMemNV */
        1900, /* glTexPageCommitmentMemNV */
        1956  /* glTexturePageCommitmentMemNV */
    };
    uint32_t i;
    if(!context->NV_memory_object_sparse) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_mesh_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         439, /* glDrawMeshTasksIndirectNV */
         440, /* glDrawMeshTasksNV */
        1216, /* glMultiDrawMeshTasksIndirectCountNV */
        1217  /* glMultiDrawMeshTasksIndirectNV */
    };
    uint32_t i;
    if(!context->NV_mesh_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_non_square_matrices(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2868, /* glUniformMatrix2x3fvNV */
        2869, /* glUniformMatrix2x4fvNV */
        2870, /* glUniformMatrix3x2fvNV */
        2871, /* glUniformMatrix3x4fvNV */
        2872, /* glUniformMatrix4x2fvNV */
        2873  /* glUniformMatrix4x3fvNV */
    };
    uint32_t i;
    if(!context->NV_non_square_matrices) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_occlusion_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          28, /* glBeginOcclusionQueryNV */
         356, /* glDeleteOcclusionQueriesNV */
         476, /* glEndOcclusionQueryNV */
         581, /* glGenOcclusionQueriesNV */
         784, /* glGetOcclusionQueryivNV */
         785, /* glGetOcclusionQueryuivNV */
        1069  /* glIsOcclusionQueryNV */
    };
    uint32_t i;
    if(!context->NV_occlusion_query) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_parameter_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1471, /* glProgramBufferParametersIivNV */
        1472, /* glProgramBufferParametersIuivNV */
        1473  /* glProgramBufferParametersfvNV */
    };
    uint32_t i;
    if(!context->NV_parameter_buffer_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_path_rendering(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         280, /* glCopyPathNV */
         299, /* glCoverFillPathInstancedNV */
         300, /* glCoverFillPathNV */
         301, /* glCoverStrokePathInstancedNV */
         302, /* glCoverStrokePathNV */
         357, /* glDeletePathsNV */
         582, /* glGenPathsNV */
         786, /* glGetPathCommandsNV */
         787, /* glGetPathCoordsNV */
         788, /* glGetPathDashArrayNV */
         789, /* glGetPathLengthNV */
         790, /* glGetPathMetricRangeNV */
         791, /* glGetPathMetricsNV */
         792, /* glGetPathParameterfvNV */
         793, /* glGetPathParameterivNV */
         794, /* glGetPathSpacingNV */
         835, /* glGetProgramResourcefvNV */
        1040, /* glInterpolatePathsNV */
        1070, /* glIsPathNV */
        1071, /* glIsPointInFillPathNV */
        1072, /* glIsPointInStrokePathNV */
        1156, /* glMatrixFrustumEXT */
        1161, /* glMatrixLoad3x2fNV */
        1162, /* glMatrixLoad3x3fNV */
        1163, /* glMatrixLoadIdentityEXT */
        1164, /* glMatrixLoadTranspose3x3fNV */
        1165, /* glMatrixLoadTransposedEXT */
        1166, /* glMatrixLoadTransposefEXT */
        1167, /* glMatrixLoaddEXT */
        1168, /* glMatrixLoadfEXT */
        1169, /* glMatrixMult3x2fNV */
        1170, /* glMatrixMult3x3fNV */
        1171, /* glMatrixMultTranspose3x3fNV */
        1172, /* glMatrixMultTransposedEXT */
        1173, /* glMatrixMultTransposefEXT */
        1174, /* glMatrixMultdEXT */
        1175, /* glMatrixMultfEXT */
        1176, /* glMatrixOrthoEXT */
        1177, /* glMatrixPopEXT */
        1178, /* glMatrixPushEXT */
        1179, /* glMatrixRotatedEXT */
        1180, /* glMatrixRotatefEXT */
        1181, /* glMatrixScaledEXT */
        1182, /* glMatrixScalefEXT */
        1183, /* glMatrixTranslatedEXT */
        1184, /* glMatrixTranslatefEXT */
        1400, /* glPathCommandsNV */
        1401, /* glPathCoordsNV */
        1402, /* glPathCoverDepthFuncNV */
        1403, /* glPathDashArrayNV */
        1404, /* glPathGlyphIndexArrayNV */
        1405, /* glPathGlyphIndexRangeNV */
        1406, /* glPathGlyphRangeNV */
        1407, /* glPathGlyphsNV */
        1408, /* glPathMemoryGlyphIndexArrayNV */
        1409, /* glPathParameterfNV */
        1410, /* glPathParameterfvNV */
        1411, /* glPathParameteriNV */
        1412, /* glPathParameterivNV */
        1413, /* glPathStencilDepthOffsetNV */
        1414, /* glPathStencilFuncNV */
        1415, /* glPathStringNV */
        1416, /* glPathSubCommandsNV */
        1417, /* glPathSubCoordsNV */
        1436, /* glPointAlongPathNV */
        1509, /* glProgramPathFragmentInputGenNV */
        1795, /* glStencilFillPathInstancedNV */
        1796, /* glStencilFillPathNV */
        1806, /* glStencilStrokePathInstancedNV */
        1807, /* glStencilStrokePathNV */
        1808, /* glStencilThenCoverFillPathInstancedNV */
        1809, /* glStencilThenCoverFillPathNV */
        1810, /* glStencilThenCoverStrokePathInstancedNV */
        1811, /* glStencilThenCoverStrokePathNV */
        2002, /* glTransformPathNV */
        2489  /* glWeightPathsNV */
    };
    uint32_t i;
    if(!context->NV_path_rendering) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_pixel_data_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         509, /* glFlushPixelDataRangeNV */
        1420  /* glPixelDataRangeNV */
    };
    uint32_t i;
    if(!context->NV_pixel_data_range) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_point_sprite(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1446, /* glPointParameteriNV */
        1448  /* glPointParameterivNV */
    };
    uint32_t i;
    if(!context->NV_point_sprite) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_polygon_mode(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2798  /* glPolygonModeNV */
    };
    uint32_t i;
    if(!context->NV_polygon_mode) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_present_video(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         986, /* glGetVideoi64vNV */
         987, /* glGetVideoivNV */
         988, /* glGetVideoui64vNV */
         989, /* glGetVideouivNV */
        1462, /* glPresentFrameDualFillNV */
        1463  /* glPresentFrameKeyedNV */
    };
    uint32_t i;
    if(!context->NV_present_video) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_primitive_restart(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1466, /* glPrimitiveRestartIndexNV */
        1467  /* glPrimitiveRestartNV */
    };
    uint32_t i;
    if(!context->NV_primitive_restart) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_query_resource(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1659  /* glQueryResourceNV */
    };
    uint32_t i;
    if(!context->NV_query_resource) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_query_resource_tag(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         366, /* glDeleteQueryResourceTagNV */
         589, /* glGenQueryResourceTagNV */
        1660  /* glQueryResourceTagNV */
    };
    uint32_t i;
    if(!context->NV_query_resource_tag) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_read_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2810  /* glReadBufferNV */
    };
    uint32_t i;
    if(!context->NV_read_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_register_combiners(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         218, /* glCombinerInputNV */
         219, /* glCombinerOutputNV */
         220, /* glCombinerParameterfNV */
         221, /* glCombinerParameterfvNV */
         222, /* glCombinerParameteriNV */
         223, /* glCombinerParameterivNV */
         497, /* glFinalCombinerInputNV */
         645, /* glGetCombinerInputParameterfvNV */
         646, /* glGetCombinerInputParameterivNV */
         647, /* glGetCombinerOutputParameterfvNV */
         648, /* glGetCombinerOutputParameterivNV */
         672, /* glGetFinalCombinerInputParameterfvNV */
         673  /* glGetFinalCombinerInputParameterivNV */
    };
    uint32_t i;
    if(!context->NV_register_combiners) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_register_combiners2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         224, /* glCombinerStageParameterfvNV */
         649  /* glGetCombinerStageParameterfvNV */
    };
    uint32_t i;
    if(!context->NV_register_combiners2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_sample_locations(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         551, /* glFramebufferSampleLocationsfvNV */
        1337, /* glNamedFramebufferSampleLocationsfvNV */
        1713  /* glResolveDepthValuesNV */
    };
    uint32_t i;
    if(!context->NV_sample_locations) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_scissor_exclusive(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1735, /* glScissorExclusiveArrayvNV */
        1736  /* glScissorExclusiveNV */
    };
    uint32_t i;
    if(!context->NV_scissor_exclusive) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_shader_buffer_load(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         632, /* glGetBufferParameterui64vNV */
         712, /* glGetIntegerui64vNV */
         755, /* glGetNamedBufferParameterui64vNV */
         940, /* glGetUniformui64vNV */
        1053, /* glIsBufferResidentNV */
        1066, /* glIsNamedBufferResidentNV */
        1122, /* glMakeBufferNonResidentNV */
        1123, /* glMakeBufferResidentNV */
        1128, /* glMakeNamedBufferNonResidentNV */
        1129, /* glMakeNamedBufferResidentNV */
        1648, /* glProgramUniformui64NV */
        1649, /* glProgramUniformui64vNV */
        2120, /* glUniformui64NV */
        2121  /* glUniformui64vNV */
    };
    uint32_t i;
    if(!context->NV_shader_buffer_load) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_shading_rate_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          73, /* glBindShadingRateImageNV */
         873, /* glGetShadingRateImagePaletteNV */
         874, /* glGetShadingRateSampleLocationivNV */
        1777, /* glShadingRateImageBarrierNV */
        1778, /* glShadingRateImagePaletteNV */
        1779, /* glShadingRateSampleOrderCustomNV */
        1780  /* glShadingRateSampleOrderNV */
    };
    uint32_t i;
    if(!context->NV_shading_rate_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_texture_barrier(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1939  /* glTextureBarrierNV */
    };
    uint32_t i;
    if(!context->NV_texture_barrier) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_texture_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1893, /* glTexImage2DMultisampleCoverageNV */
        1897, /* glTexImage3DMultisampleCoverageNV */
        1947, /* glTextureImage2DMultisampleCoverageNV */
        1948, /* glTextureImage2DMultisampleNV */
        1950, /* glTextureImage3DMultisampleCoverageNV */
        1951  /* glTextureImage3DMultisampleNV */
    };
    uint32_t i;
    if(!context->NV_texture_multisample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_timeline_semaphore(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         317, /* glCreateSemaphoresNV */
         865, /* glGetSemaphoreParameterivNV */
        1761  /* glSemaphoreParameterivNV */
    };
    uint32_t i;
    if(!context->NV_timeline_semaphore) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_transform_feedback(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           7, /* glActiveVaryingNV */
          36, /* glBeginTransformFeedbackNV */
          45, /* glBindBufferBaseNV */
          47, /* glBindBufferOffsetNV */
          50, /* glBindBufferRangeNV */
         484, /* glEndTransformFeedbackNV */
         619, /* glGetActiveVaryingNV */
         921, /* glGetTransformFeedbackVaryingNV */
         951, /* glGetVaryingLocationNV */
        1995, /* glTransformFeedbackAttribsNV */
        1998, /* glTransformFeedbackStreamAttribsNV */
        2001  /* glTransformFeedbackVaryingsNV */
    };
    uint32_t i;
    if(!context->NV_transform_feedback) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_transform_feedback2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          81, /* glBindTransformFeedbackNV */
         377, /* glDeleteTransformFeedbacksNV */
         449, /* glDrawTransformFeedbackNV */
         598, /* glGenTransformFeedbacksNV */
        1091, /* glIsTransformFeedbackNV */
        1419, /* glPauseTransformFeedbackNV */
        1715  /* glResumeTransformFeedbackNV */
    };
    uint32_t i;
    if(!context->NV_transform_feedback2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_vdpau_interop(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2135, /* glVDPAUFiniNV */
        2136, /* glVDPAUGetSurfaceivNV */
        2137, /* glVDPAUInitNV */
        2138, /* glVDPAUIsSurfaceNV */
        2139, /* glVDPAUMapSurfacesNV */
        2140, /* glVDPAURegisterOutputSurfaceNV */
        2141, /* glVDPAURegisterVideoSurfaceNV */
        2143, /* glVDPAUSurfaceAccessNV */
        2144, /* glVDPAUUnmapSurfacesNV */
        2145  /* glVDPAUUnregisterSurfaceNV */
    };
    uint32_t i;
    if(!context->NV_vdpau_interop) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_vdpau_interop2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2142  /* glVDPAURegisterVideoSurfaceWithPictureStructureNV */
    };
    uint32_t i;
    if(!context->NV_vdpau_interop2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_vertex_array_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         513, /* glFlushVertexArrayRangeNV */
        2192  /* glVertexArrayRangeNV */
    };
    uint32_t i;
    if(!context->NV_vertex_array_range) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_vertex_attrib_integer_64bit(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         967, /* glGetVertexAttribLi64vNV */
         969, /* glGetVertexAttribLui64vNV */
        2367, /* glVertexAttribL1i64NV */
        2368, /* glVertexAttribL1i64vNV */
        2370, /* glVertexAttribL1ui64NV */
        2372, /* glVertexAttribL1ui64vNV */
        2377, /* glVertexAttribL2i64NV */
        2378, /* glVertexAttribL2i64vNV */
        2379, /* glVertexAttribL2ui64NV */
        2380, /* glVertexAttribL2ui64vNV */
        2385, /* glVertexAttribL3i64NV */
        2386, /* glVertexAttribL3i64vNV */
        2387, /* glVertexAttribL3ui64NV */
        2388, /* glVertexAttribL3ui64vNV */
        2393, /* glVertexAttribL4i64NV */
        2394, /* glVertexAttribL4i64vNV */
        2395, /* glVertexAttribL4ui64NV */
        2396, /* glVertexAttribL4ui64vNV */
        2398  /* glVertexAttribLFormatNV */
    };
    uint32_t i;
    if(!context->NV_vertex_attrib_integer_64bit) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_vertex_buffer_unified_memory(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         132, /* glBufferAddressRangeNV */
         203, /* glColorFormatNV */
         455, /* glEdgeFlagFormatNV */
         514, /* glFogCoordFormatNV */
         711, /* glGetIntegerui64i_vNV */
        1030, /* glIndexFormatNV */
        1374, /* glNormalFormatNV */
        1757, /* glSecondaryColorFormatNV */
        1880, /* glTexCoordFormatNV */
        2318, /* glVertexAttribFormatNV */
        2360, /* glVertexAttribIFormatNV */
        2434  /* glVertexFormatNV */
    };
    uint32_t i;
    if(!context->NV_vertex_buffer_unified_memory) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_vertex_program(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          15, /* glAreProgramsResidentNV */
          67, /* glBindProgramNV */
         363, /* glDeleteProgramsNV */
         493, /* glExecuteProgramNV */
         586, /* glGenProgramsNV */
         827, /* glGetProgramParameterdvNV */
         828, /* glGetProgramParameterfvNV */
         839, /* glGetProgramStringNV */
         843, /* glGetProgramivNV */
         918, /* glGetTrackMatrixivNV */
         972, /* glGetVertexAttribPointervNV */
         975, /* glGetVertexAttribdvNV */
         978, /* glGetVertexAttribfvNV */
         981, /* glGetVertexAttribivNV */
        1075, /* glIsProgramNV */
        1116, /* glLoadProgramNV */
        1500, /* glProgramParameter4dNV */
        1501, /* glProgramParameter4dvNV */
        1502, /* glProgramParameter4fNV */
        1503, /* glProgramParameter4fvNV */
        1507, /* glProgramParameters4dvNV */
        1508, /* glProgramParameters4fvNV */
        1708, /* glRequestResidentProgramsNV */
        1994, /* glTrackMatrixNV */
        2209, /* glVertexAttrib1dNV */
        2212, /* glVertexAttrib1dvNV */
        2215, /* glVertexAttrib1fNV */
        2218, /* glVertexAttrib1fvNV */
        2223, /* glVertexAttrib1sNV */
        2226, /* glVertexAttrib1svNV */
        2229, /* glVertexAttrib2dNV */
        2232, /* glVertexAttrib2dvNV */
        2235, /* glVertexAttrib2fNV */
        2238, /* glVertexAttrib2fvNV */
        2243, /* glVertexAttrib2sNV */
        2246, /* glVertexAttrib2svNV */
        2249, /* glVertexAttrib3dNV */
        2252, /* glVertexAttrib3dvNV */
        2255, /* glVertexAttrib3fNV */
        2258, /* glVertexAttrib3fvNV */
        2263, /* glVertexAttrib3sNV */
        2266, /* glVertexAttrib3svNV */
        2285, /* glVertexAttrib4dNV */
        2288, /* glVertexAttrib4dvNV */
        2291, /* glVertexAttrib4fNV */
        2294, /* glVertexAttrib4fvNV */
        2301, /* glVertexAttrib4sNV */
        2304, /* glVertexAttrib4svNV */
        2305, /* glVertexAttrib4ubNV */
        2308, /* glVertexAttrib4ubvNV */
        2412, /* glVertexAttribPointerNV */
        2413, /* glVertexAttribs1dvNV */
        2414, /* glVertexAttribs1fvNV */
        2416, /* glVertexAttribs1svNV */
        2417, /* glVertexAttribs2dvNV */
        2418, /* glVertexAttribs2fvNV */
        2420, /* glVertexAttribs2svNV */
        2421, /* glVertexAttribs3dvNV */
        2422, /* glVertexAttribs3fvNV */
        2424, /* glVertexAttribs3svNV */
        2425, /* glVertexAttribs4dvNV */
        2426, /* glVertexAttribs4fvNV */
        2428, /* glVertexAttribs4svNV */
        2429  /* glVertexAttribs4ubvNV */
    };
    uint32_t i;
    if(!context->NV_vertex_program) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_vertex_program4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         962, /* glGetVertexAttribIivEXT */
         964, /* glGetVertexAttribIuivEXT */
        2320, /* glVertexAttribI1iEXT */
        2322, /* glVertexAttribI1ivEXT */
        2324, /* glVertexAttribI1uiEXT */
        2326, /* glVertexAttribI1uivEXT */
        2328, /* glVertexAttribI2iEXT */
        2330, /* glVertexAttribI2ivEXT */
        2332, /* glVertexAttribI2uiEXT */
        2334, /* glVertexAttribI2uivEXT */
        2336, /* glVertexAttribI3iEXT */
        2338, /* glVertexAttribI3ivEXT */
        2340, /* glVertexAttribI3uiEXT */
        2342, /* glVertexAttribI3uivEXT */
        2344, /* glVertexAttribI4bvEXT */
        2346, /* glVertexAttribI4iEXT */
        2348, /* glVertexAttribI4ivEXT */
        2350, /* glVertexAttribI4svEXT */
        2352, /* glVertexAttribI4ubvEXT */
        2354, /* glVertexAttribI4uiEXT */
        2356, /* glVertexAttribI4uivEXT */
        2358, /* glVertexAttribI4usvEXT */
        2362  /* glVertexAttribIPointerEXT */
    };
    uint32_t i;
    if(!context->NV_vertex_program4) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_video_capture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          38, /* glBeginVideoCaptureNV */
          87, /* glBindVideoCaptureStreamBufferNV */
          88, /* glBindVideoCaptureStreamTextureNV */
         486, /* glEndVideoCaptureNV */
         982, /* glGetVideoCaptureStreamdvNV */
         983, /* glGetVideoCaptureStreamfvNV */
         984, /* glGetVideoCaptureStreamivNV */
         985, /* glGetVideoCaptureivNV */
        2475, /* glVideoCaptureNV */
        2476, /* glVideoCaptureStreamParameterdvNV */
        2477, /* glVideoCaptureStreamParameterfvNV */
        2478  /* glVideoCaptureStreamParameterivNV */
    };
    uint32_t i;
    if(!context->NV_video_capture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_viewport_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2596, /* glDepthRangeArrayfvNV */
        2598, /* glDepthRangeIndexedfNV */
        2603, /* glDisableiNV */
        2630, /* glEnableiNV */
        2683, /* glGetFloati_vNV */
        2768, /* glIsEnablediNV */
        2831, /* glScissorArrayvNV */
        2833, /* glScissorIndexedNV */
        2835, /* glScissorIndexedvNV */
        2880, /* glViewportArrayvNV */
        2882, /* glViewportIndexedfNV */
        2884  /* glViewportIndexedfvNV */
    };
    uint32_t i;
    if(!context->NV_viewport_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_viewport_swizzle(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2484  /* glViewportSwizzleNV */
    };
    uint32_t i;
    if(!context->NV_viewport_swizzle) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_EGL_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2626, /* glEGLImageTargetRenderbufferStorageOES */
        2627  /* glEGLImageTargetTexture2DOES */
    };
    uint32_t i;
    if(!context->OES_EGL_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_byte_coordinates(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1222, /* glMultiTexCoord1bOES */
        1223, /* glMultiTexCoord1bvOES */
        1236, /* glMultiTexCoord2bOES */
        1237, /* glMultiTexCoord2bvOES */
        1250, /* glMultiTexCoord3bOES */
        1251, /* glMultiTexCoord3bvOES */
        1264, /* glMultiTexCoord4bOES */
        1265, /* glMultiTexCoord4bvOES */
        1842, /* glTexCoord1bOES */
        1843, /* glTexCoord1bvOES */
        1848, /* glTexCoord2bOES */
        1849, /* glTexCoord2bvOES */
        1864, /* glTexCoord3bOES */
        1865, /* glTexCoord3bvOES */
        1870, /* glTexCoord4bOES */
        1871, /* glTexCoord4bvOES */
        2159, /* glVertex2bOES */
        2160, /* glVertex2bvOES */
        2165, /* glVertex3bOES */
        2166, /* glVertex3bvOES */
        2171, /* glVertex4bOES */
        2172  /* glVertex4bvOES */
    };
    uint32_t i;
    if(!context->OES_byte_coordinates) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_copy_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2578  /* glCopyImageSubDataOES */
    };
    uint32_t i;
    if(!context->OES_copy_image) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_draw_buffers_indexed(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2552, /* glBlendEquationSeparateiOES */
        2554, /* glBlendEquationiOES */
        2556, /* glBlendFuncSeparateiOES */
        2558, /* glBlendFunciOES */
        2568, /* glColorMaskiOES */
        2604, /* glDisableiOES */
        2631, /* glEnableiOES */
        2769  /* glIsEnablediOES */
    };
    uint32_t i;
    if(!context->OES_draw_buffers_indexed) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_draw_elements_base_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2614, /* glDrawElementsBaseVertexOES */
        2620, /* glDrawElementsInstancedBaseVertexOES */
        2623, /* glDrawRangeElementsBaseVertexOES */
        2788  /* glMultiDrawElementsBaseVertexEXT */
    };
    uint32_t i;
    if(!context->OES_draw_elements_base_vertex) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_fixed_point(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           0, /* glAccumxOES */
          11, /* glAlphaFuncxOES */
         100, /* glBitmapxOES */
         105, /* glBlendColorxOES */
         152, /* glClearAccumxOES */
         162, /* glClearColorxOES */
         167, /* glClearDepthxOES */
         186, /* glClipPlanexOES */
         191, /* glColor3xOES */
         192, /* glColor3xvOES */
         201, /* glColor4xOES */
         202, /* glColor4xvOES */
         265, /* glConvolutionParameterxOES */
         266, /* glConvolutionParameterxvOES */
         393, /* glDepthRangexOES */
         487, /* glEvalCoord1xOES */
         488, /* glEvalCoord1xvOES */
         489, /* glEvalCoord2xOES */
         490, /* glEvalCoord2xvOES */
         495, /* glFeedbackBufferxOES */
         524, /* glFogxOES */
         525, /* glFogxvOES */
         571, /* glFrustumxOES */
         638, /* glGetClipPlanexOES */
         660, /* glGetConvolutionParameterxvOES */
         675, /* glGetFixedvOES */
         700, /* glGetHistogramParameterxvOES */
         720, /* glGetLightxOES */
         731, /* glGetMapxvOES */
         732, /* glGetMaterialxOES */
         805, /* glGetPixelMapxv */
         884, /* glGetTexEnvxvOES */
         886, /* glGetTexGenxvOES */
         890, /* glGetTexLevelParameterxvOES */
         898, /* glGetTexParameterxvOES */
        1035, /* glIndexxOES */
        1036, /* glIndexxvOES */
        1101, /* glLightModelxOES */
        1102, /* glLightModelxvOES */
        1103, /* glLightxOES */
        1104, /* glLightxvOES */
        1106, /* glLineWidthxOES */
        1115, /* glLoadMatrixxOES */
        1119, /* glLoadTransposeMatrixxOES */
        1134, /* glMap1xOES */
        1135, /* glMap2xOES */
        1140, /* glMapGrid1xOES */
        1141, /* glMapGrid2xOES */
        1154, /* glMaterialxOES */
        1155, /* glMaterialxvOES */
        1194, /* glMultMatrixxOES */
        1197, /* glMultTransposeMatrixxOES */
        1234, /* glMultiTexCoord1xOES */
        1235, /* glMultiTexCoord1xvOES */
        1248, /* glMultiTexCoord2xOES */
        1249, /* glMultiTexCoord2xvOES */
        1262, /* glMultiTexCoord3xOES */
        1263, /* glMultiTexCoord3xvOES */
        1276, /* glMultiTexCoord4xOES */
        1277, /* glMultiTexCoord4xvOES */
        1372, /* glNormal3xOES */
        1373, /* glNormal3xvOES */
        1393, /* glOrthoxOES */
        1397, /* glPassThroughxOES */
        1421, /* glPixelMapx */
        1424, /* glPixelStorex */
        1430, /* glPixelTransferxOES */
        1435, /* glPixelZoomxOES */
        1449, /* glPointParameterxvOES */
        1451, /* glPointSizexOES */
        1459, /* glPolygonOffsetxOES */
        1469, /* glPrioritizeTexturesxOES */
        1661, /* glRasterPos2xOES */
        1662, /* glRasterPos2xvOES */
        1663, /* glRasterPos3xOES */
        1664, /* glRasterPos3xvOES */
        1665, /* glRasterPos4xOES */
        1666, /* glRasterPos4xvOES */
        1673, /* glRectxOES */
        1674, /* glRectxvOES */
        1716, /* glRotatexOES */
        1732, /* glScalexOES */
        1846, /* glTexCoord1xOES */
        1847, /* glTexCoord1xvOES */
        1862, /* glTexCoord2xOES */
        1863, /* glTexCoord2xvOES */
        1868, /* glTexCoord3xOES */
        1869, /* glTexCoord3xvOES */
        1878, /* glTexCoord4xOES */
        1879, /* glTexCoord4xvOES */
        1884, /* glTexEnvxOES */
        1885, /* glTexEnvxvOES */
        1887, /* glTexGenxOES */
        1888, /* glTexGenxvOES */
        1909, /* glTexParameterxOES */
        1910, /* glTexParameterxvOES */
        2003, /* glTranslatexOES */
        2163, /* glVertex2xOES */
        2164, /* glVertex2xvOES */
        2169, /* glVertex3xOES */
        2170, /* glVertex3xvOES */
        2175, /* glVertex4xOES */
        2176  /* glVertex4xvOES */
    };
    uint32_t i;
    if(!context->OES_fixed_point) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_geometry_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2667  /* glFramebufferTextureOES */
    };
    uint32_t i;
    if(!context->OES_geometry_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_get_program_binary(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2711, /* glGetProgramBinaryOES */
        2803  /* glProgramBinaryOES */
    };
    uint32_t i;
    if(!context->OES_get_program_binary) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_mapbuffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2677, /* glGetBufferPointervOES */
        2779, /* glMapBufferOES */
        2874  /* glUnmapBufferOES */
    };
    uint32_t i;
    if(!context->OES_mapbuffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_primitive_bounding_box(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2802  /* glPrimitiveBoundingBoxOES */
    };
    uint32_t i;
    if(!context->OES_primitive_bounding_box) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_query_matrix(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1657  /* glQueryMatrixxOES */
    };
    uint32_t i;
    if(!context->OES_query_matrix) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_sample_shading(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2782  /* glMinSampleShadingOES */
    };
    uint32_t i;
    if(!context->OES_sample_shading) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_single_precision(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         166, /* glClearDepthfOES */
         185, /* glClipPlanefOES */
         392, /* glDepthRangefOES */
         570, /* glFrustumfOES */
         637, /* glGetClipPlanefOES */
        1392  /* glOrthofOES */
    };
    uint32_t i;
    if(!context->OES_single_precision) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_tessellation_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2795  /* glPatchParameteriOES */
    };
    uint32_t i;
    if(!context->OES_tessellation_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_texture_3D(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2571, /* glCompressedTexImage3DOES */
        2574, /* glCompressedTexSubImage3DOES */
        2581, /* glCopyTexSubImage3DOES */
        2664, /* glFramebufferTexture3DOES */
        2847, /* glTexImage3DOES */
        2861  /* glTexSubImage3DOES */
    };
    uint32_t i;
    if(!context->OES_texture_3D) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_texture_border_clamp(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2728, /* glGetSamplerParameterIivOES */
        2731, /* glGetSamplerParameterIuivOES */
        2742, /* glGetTexParameterIivOES */
        2744, /* glGetTexParameterIuivOES */
        2824, /* glSamplerParameterIivOES */
        2827, /* glSamplerParameterIuivOES */
        2850, /* glTexParameterIivOES */
        2852  /* glTexParameterIuivOES */
    };
    uint32_t i;
    if(!context->OES_texture_border_clamp) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_texture_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2841, /* glTexBufferOES */
        2843  /* glTexBufferRangeOES */
    };
    uint32_t i;
    if(!context->OES_texture_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_texture_storage_multisample_2d_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2857  /* glTexStorage3DMultisampleOES */
    };
    uint32_t i;
    if(!context->OES_texture_storage_multisample_2d_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_texture_view(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2865  /* glTextureViewOES */
    };
    uint32_t i;
    if(!context->OES_texture_view) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_vertex_array_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2549, /* glBindVertexArrayOES */
        2595, /* glDeleteVertexArraysOES */
        2671, /* glGenVertexArraysOES */
        2773  /* glIsVertexArrayOES */
    };
    uint32_t i;
    if(!context->OES_vertex_array_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_viewport_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2597, /* glDepthRangeArrayfvOES */
        2599, /* glDepthRangeIndexedfOES */
        2604, /* glDisableiOES */
        2631, /* glEnableiOES */
        2684, /* glGetFloati_vOES */
        2769, /* glIsEnablediOES */
        2832, /* glScissorArrayvOES */
        2834, /* glScissorIndexedOES */
        2836, /* glScissorIndexedvOES */
        2881, /* glViewportArrayvOES */
        2883, /* glViewportIndexedfOES */
        2885  /* glViewportIndexedfvOES */
    };
    uint32_t i;
    if(!context->OES_viewport_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OVR_multiview(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         567, /* glFramebufferTextureMultiviewOVR */
        1347  /* glNamedFramebufferTextureMultiviewOVR */
    };
    uint32_t i;
    if(!context->OVR_multiview) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OVR_multiview_multisampled_render_to_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2666  /* glFramebufferTextureMultisampleMultiviewOVR */
    };
    uint32_t i;
    if(!context->OVR_multiview_multisampled_render_to_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_PGI_misc_hints(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1014  /* glHintPGI */
    };
    uint32_t i;
    if(!context->PGI_misc_hints) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_alpha_test(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2543  /* glAlphaFuncQCOM */
    };
    uint32_t i;
    if(!context->QCOM_alpha_test) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_driver_control(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2600, /* glDisableDriverControlQCOM */
        2628, /* glEnableDriverControlQCOM */
        2681, /* glGetDriverControlStringQCOM */
        2682  /* glGetDriverControlsQCOM */
    };
    uint32_t i;
    if(!context->QCOM_driver_control) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_extended_get(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2635, /* glExtGetBufferPointervQCOM */
        2636, /* glExtGetBuffersQCOM */
        2637, /* glExtGetFramebuffersQCOM */
        2640, /* glExtGetRenderbuffersQCOM */
        2642, /* glExtGetTexLevelParameterivQCOM */
        2643, /* glExtGetTexSubImageQCOM */
        2644, /* glExtGetTexturesQCOM */
        2646  /* glExtTexObjectStateOverrideiQCOM */
    };
    uint32_t i;
    if(!context->QCOM_extended_get) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_extended_get2(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2638, /* glExtGetProgramBinarySourceQCOM */
        2639, /* glExtGetProgramsQCOM */
        2641, /* glExtGetShadersQCOM */
        2645  /* glExtIsProgramBinaryQCOM */
    };
    uint32_t i;
    if(!context->QCOM_extended_get2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_frame_extrapolation(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2647  /* glExtrapolateTex2DQCOM */
    };
    uint32_t i;
    if(!context->QCOM_frame_extrapolation) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_framebuffer_foveated(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2651, /* glFramebufferFoveationConfigQCOM */
        2652  /* glFramebufferFoveationParametersQCOM */
    };
    uint32_t i;
    if(!context->QCOM_framebuffer_foveated) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_motion_estimation(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2844, /* glTexEstimateMotionQCOM */
        2845  /* glTexEstimateMotionRegionsQCOM */
    };
    uint32_t i;
    if(!context->QCOM_motion_estimation) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_shader_framebuffer_fetch_noncoherent(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2650  /* glFramebufferFetchBarrierQCOM */
    };
    uint32_t i;
    if(!context->QCOM_shader_framebuffer_fetch_noncoherent) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_shading_rate(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2839  /* glShadingRateQCOM */
    };
    uint32_t i;
    if(!context->QCOM_shading_rate) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_texture_foveated(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2863  /* glTextureFoveationParametersQCOM */
    };
    uint32_t i;
    if(!context->QCOM_texture_foveated) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_QCOM_tiled_rendering(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2634, /* glEndTilingQCOM */
        2840  /* glStartTilingQCOM */
    };
    uint32_t i;
    if(!context->QCOM_tiled_rendering) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_detail_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         396, /* glDetailTexFuncSGIS */
         665  /* glGetDetailTexFuncSGIS */
    };
    uint32_t i;
    if(!context->SGIS_detail_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_fog_function(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         523, /* glFogFuncSGIS */
         680  /* glGetFogFuncSGIS */
    };
    uint32_t i;
    if(!context->SGIS_fog_function) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1722, /* glSampleMaskSGIS */
        1725  /* glSamplePatternSGIS */
    };
    uint32_t i;
    if(!context->SGIS_multisample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_pixel_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         806, /* glGetPixelTexGenParameterfvSGIS */
         807, /* glGetPixelTexGenParameterivSGIS */
        1425, /* glPixelTexGenParameterfSGIS */
        1426, /* glPixelTexGenParameterfvSGIS */
        1427, /* glPixelTexGenParameteriSGIS */
        1428  /* glPixelTexGenParameterivSGIS */
    };
    uint32_t i;
    if(!context->SGIS_pixel_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_point_parameters(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1440, /* glPointParameterfSGIS */
        1444  /* glPointParameterfvSGIS */
    };
    uint32_t i;
    if(!context->SGIS_point_parameters) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_sharpen_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         875, /* glGetSharpenTexFuncSGIS */
        1781  /* glSharpenTexFuncSGIS */
    };
    uint32_t i;
    if(!context->SGIS_sharpen_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_texture4D(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1898, /* glTexImage4DSGIS */
        1936  /* glTexSubImage4DSGIS */
    };
    uint32_t i;
    if(!context->SGIS_texture4D) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_texture_color_mask(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1944  /* glTextureColorMaskSGIS */
    };
    uint32_t i;
    if(!context->SGIS_texture_color_mask) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_texture_filter4(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         885, /* glGetTexFilterFuncSGIS */
        1886  /* glTexFilterFuncSGIS */
    };
    uint32_t i;
    if(!context->SGIS_texture_filter4) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_async(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          21, /* glAsyncMarkerSGIX */
         343, /* glDeleteAsyncMarkersSGIX */
         499, /* glFinishAsyncSGIX */
         572, /* glGenAsyncMarkersSGIX */
        1050, /* glIsAsyncMarkerSGIX */
        1452  /* glPollAsyncSGIX */
    };
    uint32_t i;
    if(!context->SGIX_async) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_flush_raster(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         510  /* glFlushRasterSGIX */
    };
    uint32_t i;
    if(!context->SGIX_flush_raster) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_fragment_lighting(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         526, /* glFragmentColorMaterialSGIX */
         528, /* glFragmentLightModelfSGIX */
         529, /* glFragmentLightModelfvSGIX */
         530, /* glFragmentLightModeliSGIX */
         531, /* glFragmentLightModelivSGIX */
         532, /* glFragmentLightfSGIX */
         533, /* glFragmentLightfvSGIX */
         534, /* glFragmentLightiSGIX */
         535, /* glFragmentLightivSGIX */
         536, /* glFragmentMaterialfSGIX */
         537, /* glFragmentMaterialfvSGIX */
         538, /* glFragmentMaterialiSGIX */
         539, /* glFragmentMaterialivSGIX */
         684, /* glGetFragmentLightfvSGIX */
         685, /* glGetFragmentLightivSGIX */
         686, /* glGetFragmentMaterialfvSGIX */
         687, /* glGetFragmentMaterialivSGIX */
        1100  /* glLightEnviSGIX */
    };
    uint32_t i;
    if(!context->SGIX_fragment_lighting) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_framezoom(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         541  /* glFrameZoomSGIX */
    };
    uint32_t i;
    if(!context->SGIX_framezoom) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_igloo_interface(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1016  /* glIglooInterfaceSGIX */
    };
    uint32_t i;
    if(!context->SGIX_igloo_interface) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_instruments(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         706, /* glGetInstrumentsSGIX */
        1039, /* glInstrumentsBufferSGIX */
        1453, /* glPollInstrumentsSGIX */
        1669, /* glReadInstrumentsSGIX */
        1792, /* glStartInstrumentsSGIX */
        1812  /* glStopInstrumentsSGIX */
    };
    uint32_t i;
    if(!context->SGIX_instruments) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_list_priority(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         721, /* glGetListParameterfvSGIX */
         722, /* glGetListParameterivSGIX */
        1110, /* glListParameterfSGIX */
        1111, /* glListParameterfvSGIX */
        1112, /* glListParameteriSGIX */
        1113  /* glListParameterivSGIX */
    };
    uint32_t i;
    if(!context->SGIX_list_priority) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_pixel_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1429  /* glPixelTexGenSGIX */
    };
    uint32_t i;
    if(!context->SGIX_pixel_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_polynomial_ffd(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         340, /* glDeformSGIX */
         341, /* glDeformationMap3dSGIX */
         342, /* glDeformationMap3fSGIX */
        1114  /* glLoadIdentityDeformationMapSGIX */
    };
    uint32_t i;
    if(!context->SGIX_polynomial_ffd) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_reference_plane(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1675  /* glReferencePlaneSGIX */
    };
    uint32_t i;
    if(!context->SGIX_reference_plane) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_sprite(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1788, /* glSpriteParameterfSGIX */
        1789, /* glSpriteParameterfvSGIX */
        1790, /* glSpriteParameteriSGIX */
        1791  /* glSpriteParameterivSGIX */
    };
    uint32_t i;
    if(!context->SGIX_sprite) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIX_tag_sample_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1817  /* glTagSampleBufferSGIX */
    };
    uint32_t i;
    if(!context->SGIX_tag_sample_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGI_color_table(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         215, /* glColorTableParameterfvSGI */
         216, /* glColorTableParameterivSGI */
         217, /* glColorTableSGI */
         269, /* glCopyColorTableSGI */
         641, /* glGetColorTableParameterfvSGI */
         643, /* glGetColorTableParameterivSGI */
         644  /* glGetColorTableSGI */
    };
    uint32_t i;
    if(!context->SGI_color_table) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SUNX_constant_data(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         503  /* glFinishTextureSUNX */
    };
    uint32_t i;
    if(!context->SUNX_constant_data) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SUN_global_alpha(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1005, /* glGlobalAlphaFactorbSUN */
        1006, /* glGlobalAlphaFactordSUN */
        1007, /* glGlobalAlphaFactorfSUN */
        1008, /* glGlobalAlphaFactoriSUN */
        1009, /* glGlobalAlphaFactorsSUN */
        1010, /* glGlobalAlphaFactorubSUN */
        1011, /* glGlobalAlphaFactoruiSUN */
        1012  /* glGlobalAlphaFactorusSUN */
    };
    uint32_t i;
    if(!context->SUN_global_alpha) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SUN_mesh_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         438  /* glDrawMeshArraysSUN */
    };
    uint32_t i;
    if(!context->SUN_mesh_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SUN_triangle_list(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1685, /* glReplacementCodePointerSUN */
        1686, /* glReplacementCodeubSUN */
        1687, /* glReplacementCodeubvSUN */
        1696, /* glReplacementCodeuiSUN */
        1705, /* glReplacementCodeuivSUN */
        1706, /* glReplacementCodeusSUN */
        1707  /* glReplacementCodeusvSUN */
    };
    uint32_t i;
    if(!context->SUN_triangle_list) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SUN_vertex(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         187, /* glColor3fVertex3fSUN */
         188, /* glColor3fVertex3fvSUN */
         193, /* glColor4fNormal3fVertex3fSUN */
         194, /* glColor4fNormal3fVertex3fvSUN */
         197, /* glColor4ubVertex2fSUN */
         198, /* glColor4ubVertex2fvSUN */
         199, /* glColor4ubVertex3fSUN */
         200, /* glColor4ubVertex3fvSUN */
        1368, /* glNormal3fVertex3fSUN */
        1369, /* glNormal3fVertex3fvSUN */
        1688, /* glReplacementCodeuiColor3fVertex3fSUN */
        1689, /* glReplacementCodeuiColor3fVertex3fvSUN */
        1690, /* glReplacementCodeuiColor4fNormal3fVertex3fSUN */
        1691, /* glReplacementCodeuiColor4fNormal3fVertex3fvSUN */
        1692, /* glReplacementCodeuiColor4ubVertex3fSUN */
        1693, /* glReplacementCodeuiColor4ubVertex3fvSUN */
        1694, /* glReplacementCodeuiNormal3fVertex3fSUN */
        1695, /* glReplacementCodeuiNormal3fVertex3fvSUN */
        1697, /* glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN */
        1698, /* glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN */
        1699, /* glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN */
        1700, /* glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN */
        1701, /* glReplacementCodeuiTexCoord2fVertex3fSUN */
        1702, /* glReplacementCodeuiTexCoord2fVertex3fvSUN */
        1703, /* glReplacementCodeuiVertex3fSUN */
        1704, /* glReplacementCodeuiVertex3fvSUN */
        1850, /* glTexCoord2fColor3fVertex3fSUN */
        1851, /* glTexCoord2fColor3fVertex3fvSUN */
        1852, /* glTexCoord2fColor4fNormal3fVertex3fSUN */
        1853, /* glTexCoord2fColor4fNormal3fVertex3fvSUN */
        1854, /* glTexCoord2fColor4ubVertex3fSUN */
        1855, /* glTexCoord2fColor4ubVertex3fvSUN */
        1856, /* glTexCoord2fNormal3fVertex3fSUN */
        1857, /* glTexCoord2fNormal3fVertex3fvSUN */
        1858, /* glTexCoord2fVertex3fSUN */
        1859, /* glTexCoord2fVertex3fvSUN */
        1872, /* glTexCoord4fColor4fNormal3fVertex4fSUN */
        1873, /* glTexCoord4fColor4fNormal3fVertex4fvSUN */
        1874, /* glTexCoord4fVertex4fSUN */
        1875  /* glTexCoord4fVertex4fvSUN */
    };
    uint32_t i;
    if(!context->SUN_vertex) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_resolve_aliases(GladGLContext *context) {
    static const GladAliasPair_t s_aliases[] = {
        {    5,    6 }, /* glActiveTexture and glActiveTextureARB */
        {    6,    5 }, /* glActiveTextureARB and glActiveTexture */
        {   22,   23 }, /* glAttachObjectARB and glAttachShader */
        {   23,   22 }, /* glAttachShader and glAttachObjectARB */
        {   24,   25 }, /* glBeginConditionalRender and glBeginConditionalRenderNV */
        {   25,   24 }, /* glBeginConditionalRenderNV and glBeginConditionalRender */
        {   31,   32 }, /* glBeginQuery and glBeginQueryARB */
        {   32,   31 }, /* glBeginQueryARB and glBeginQuery */
        {   34,   35 }, /* glBeginTransformFeedback and glBeginTransformFeedbackEXT */
        {   34,   36 }, /* glBeginTransformFeedback and glBeginTransformFeedbackNV */
        {   35,   34 }, /* glBeginTransformFeedbackEXT and glBeginTransformFeedback */
        {   35,   36 }, /* glBeginTransformFeedbackEXT and glBeginTransformFeedbackNV */
        {   36,   34 }, /* glBeginTransformFeedbackNV and glBeginTransformFeedback */
        {   36,   35 }, /* glBeginTransformFeedbackNV and glBeginTransformFeedbackEXT */
        {   39,   40 }, /* glBindAttribLocation and glBindAttribLocationARB */
        {   40,   39 }, /* glBindAttribLocationARB and glBindAttribLocation */
        {   41,   42 }, /* glBindBuffer and glBindBufferARB */
        {   42,   41 }, /* glBindBufferARB and glBindBuffer */
        {   43,   44 }, /* glBindBufferBase and glBindBufferBaseEXT */
        {   43,   45 }, /* glBindBufferBase and glBindBufferBaseNV */
        {   44,   43 }, /* glBindBufferBaseEXT and glBindBufferBase */
        {   44,   45 }, /* glBindBufferBaseEXT and glBindBufferBaseNV */
        {   45,   43 }, /* glBindBufferBaseNV and glBindBufferBase */
        {   45,   44 }, /* glBindBufferBaseNV and glBindBufferBaseEXT */
        {   46,   47 }, /* glBindBufferOffsetEXT and glBindBufferOffsetNV */
        {   47,   46 }, /* glBindBufferOffsetNV and glBindBufferOffsetEXT */
        {   48,   49 }, /* glBindBufferRange and glBindBufferRangeEXT */
        {   48,   50 }, /* glBindBufferRange and glBindBufferRangeNV */
        {   49,   48 }, /* glBindBufferRangeEXT and glBindBufferRange */
        {   49,   50 }, /* glBindBufferRangeEXT and glBindBufferRangeNV */
        {   50,   48 }, /* glBindBufferRangeNV and glBindBufferRange */
        {   50,   49 }, /* glBindBufferRangeNV and glBindBufferRangeEXT */
        {   53,   54 }, /* glBindFragDataLocation and glBindFragDataLocationEXT */
        {   54,   53 }, /* glBindFragDataLocationEXT and glBindFragDataLocation */
        {   55, 2546 }, /* glBindFragDataLocationIndexed and glBindFragDataLocationIndexedEXT */
        { 2546,   55 }, /* glBindFragDataLocationIndexedEXT and glBindFragDataLocationIndexed */
        {   66,   67 }, /* glBindProgramARB and glBindProgramNV */
        {   67,   66 }, /* glBindProgramNV and glBindProgramARB */
        {   75,   76 }, /* glBindTexture and glBindTextureEXT */
        {   76,   75 }, /* glBindTextureEXT and glBindTexture */
        {   82, 2549 }, /* glBindVertexArray and glBindVertexArrayOES */
        { 2549,   82 }, /* glBindVertexArrayOES and glBindVertexArray */
        { 2550,  101 }, /* glBlendBarrier and glBlendBarrierKHR */
        { 2550,  102 }, /* glBlendBarrier and glBlendBarrierNV */
        {  101, 2550 }, /* glBlendBarrierKHR and glBlendBarrier */
        {  101,  102 }, /* glBlendBarrierKHR and glBlendBarrierNV */
        {  102, 2550 }, /* glBlendBarrierNV and glBlendBarrier */
        {  102,  101 }, /* glBlendBarrierNV and glBlendBarrierKHR */
        {  103,  104 }, /* glBlendColor and glBlendColorEXT */
        {  104,  103 }, /* glBlendColorEXT and glBlendColor */
        {  106,  107 }, /* glBlendEquation and glBlendEquationEXT */
        {  107,  106 }, /* glBlendEquationEXT and glBlendEquation */
        {  114,  108 }, /* glBlendEquationi and glBlendEquationIndexedAMD */
        {  114,  115 }, /* glBlendEquationi and glBlendEquationiARB */
        {  114, 2553 }, /* glBlendEquationi and glBlendEquationiEXT */
        {  114, 2554 }, /* glBlendEquationi and glBlendEquationiOES */
        {  115,  108 }, /* glBlendEquationiARB and glBlendEquationIndexedAMD */
        {  115,  114 }, /* glBlendEquationiARB and glBlendEquationi */
        {  115, 2553 }, /* glBlendEquationiARB and glBlendEquationiEXT */
        {  115, 2554 }, /* glBlendEquationiARB and glBlendEquationiOES */
        { 2553,  108 }, /* glBlendEquationiEXT and glBlendEquationIndexedAMD */
        { 2553,  114 }, /* glBlendEquationiEXT and glBlendEquationi */
        { 2553,  115 }, /* glBlendEquationiEXT and glBlendEquationiARB */
        { 2553, 2554 }, /* glBlendEquationiEXT and glBlendEquationiOES */
        {  108,  114 }, /* glBlendEquationIndexedAMD and glBlendEquationi */
        {  108,  115 }, /* glBlendEquationIndexedAMD and glBlendEquationiARB */
        {  108, 2553 }, /* glBlendEquationIndexedAMD and glBlendEquationiEXT */
        {  108, 2554 }, /* glBlendEquationIndexedAMD and glBlendEquationiOES */
        { 2554,  108 }, /* glBlendEquationiOES and glBlendEquationIndexedAMD */
        { 2554,  114 }, /* glBlendEquationiOES and glBlendEquationi */
        { 2554,  115 }, /* glBlendEquationiOES and glBlendEquationiARB */
        { 2554, 2553 }, /* glBlendEquationiOES and glBlendEquationiEXT */
        {  109,  110 }, /* glBlendEquationSeparate and glBlendEquationSeparateEXT */
        {  110,  109 }, /* glBlendEquationSeparateEXT and glBlendEquationSeparate */
        {  112,  111 }, /* glBlendEquationSeparatei and glBlendEquationSeparateIndexedAMD */
        {  112,  113 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiARB */
        {  112, 2551 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiEXT */
        {  112, 2552 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiOES */
        {  113,  111 }, /* glBlendEquationSeparateiARB and glBlendEquationSeparateIndexedAMD */
        {  113,  112 }, /* glBlendEquationSeparateiARB and glBlendEquationSeparatei */
        {  113, 2551 }, /* glBlendEquationSeparateiARB and glBlendEquationSeparateiEXT */
        {  113, 2552 }, /* glBlendEquationSeparateiARB and glBlendEquationSeparateiOES */
        { 2551,  111 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparateIndexedAMD */
        { 2551,  112 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparatei */
        { 2551,  113 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparateiARB */
        { 2551, 2552 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparateiOES */
        {  111,  112 }, /* glBlendEquationSeparateIndexedAMD and glBlendEquationSeparatei */
        {  111,  113 }, /* glBlendEquationSeparateIndexedAMD and glBlendEquationSeparateiARB */
        {  111, 2551 }, /* glBlendEquationSeparateIndexedAMD and glBlendEquationSeparateiEXT */
        {  111, 2552 }, /* glBlendEquationSeparateIndexedAMD and glBlendEquationSeparateiOES */
        { 2552,  111 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparateIndexedAMD */
        { 2552,  112 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparatei */
        { 2552,  113 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparateiARB */
        { 2552, 2551 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparateiEXT */
        {  124,  117 }, /* glBlendFunci and glBlendFuncIndexedAMD */
        {  124,  125 }, /* glBlendFunci and glBlendFunciARB */
        {  124, 2557 }, /* glBlendFunci and glBlendFunciEXT */
        {  124, 2558 }, /* glBlendFunci and glBlendFunciOES */
        {  125,  117 }, /* glBlendFunciARB and glBlendFuncIndexedAMD */
        {  125,  124 }, /* glBlendFunciARB and glBlendFunci */
        {  125, 2557 }, /* glBlendFunciARB and glBlendFunciEXT */
        {  125, 2558 }, /* glBlendFunciARB and glBlendFunciOES */
        { 2557,  117 }, /* glBlendFunciEXT and glBlendFuncIndexedAMD */
        { 2557,  124 }, /* glBlendFunciEXT and glBlendFunci */
        { 2557,  125 }, /* glBlendFunciEXT and glBlendFunciARB */
        { 2557, 2558 }, /* glBlendFunciEXT and glBlendFunciOES */
        {  117,  124 }, /* glBlendFuncIndexedAMD and glBlendFunci */
        {  117,  125 }, /* glBlendFuncIndexedAMD and glBlendFunciARB */
        {  117, 2557 }, /* glBlendFuncIndexedAMD and glBlendFunciEXT */
        {  117, 2558 }, /* glBlendFuncIndexedAMD and glBlendFunciOES */
        { 2558,  117 }, /* glBlendFunciOES and glBlendFuncIndexedAMD */
        { 2558,  124 }, /* glBlendFunciOES and glBlendFunci */
        { 2558,  125 }, /* glBlendFunciOES and glBlendFunciARB */
        { 2558, 2557 }, /* glBlendFunciOES and glBlendFunciEXT */
        {  118,  119 }, /* glBlendFuncSeparate and glBlendFuncSeparateEXT */
        {  118,  120 }, /* glBlendFuncSeparate and glBlendFuncSeparateINGR */
        {  119,  118 }, /* glBlendFuncSeparateEXT and glBlendFuncSeparate */
        {  119,  120 }, /* glBlendFuncSeparateEXT and glBlendFuncSeparateINGR */
        {  122,  121 }, /* glBlendFuncSeparatei and glBlendFuncSeparateIndexedAMD */
        {  122,  123 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiARB */
        {  122, 2555 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiEXT */
        {  122, 2556 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiOES */
        {  123,  121 }, /* glBlendFuncSeparateiARB and glBlendFuncSeparateIndexedAMD */
        {  123,  122 }, /* glBlendFuncSeparateiARB and glBlendFuncSeparatei */
        {  123, 2555 }, /* glBlendFuncSeparateiARB and glBlendFuncSeparateiEXT */
        {  123, 2556 }, /* glBlendFuncSeparateiARB and glBlendFuncSeparateiOES */
        { 2555,  121 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparateIndexedAMD */
        { 2555,  122 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparatei */
        { 2555,  123 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparateiARB */
        { 2555, 2556 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparateiOES */
        {  121,  122 }, /* glBlendFuncSeparateIndexedAMD and glBlendFuncSeparatei */
        {  121,  123 }, /* glBlendFuncSeparateIndexedAMD and glBlendFuncSeparateiARB */
        {  121, 2555 }, /* glBlendFuncSeparateIndexedAMD and glBlendFuncSeparateiEXT */
        {  121, 2556 }, /* glBlendFuncSeparateIndexedAMD and glBlendFuncSeparateiOES */
        {  120,  118 }, /* glBlendFuncSeparateINGR and glBlendFuncSeparate */
        {  120,  119 }, /* glBlendFuncSeparateINGR and glBlendFuncSeparateEXT */
        { 2556,  121 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparateIndexedAMD */
        { 2556,  122 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparatei */
        { 2556,  123 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparateiARB */
        { 2556, 2555 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparateiEXT */
        {  127,  128 }, /* glBlitFramebuffer and glBlitFramebufferEXT */
        {  127, 2560 }, /* glBlitFramebuffer and glBlitFramebufferNV */
        {  128,  127 }, /* glBlitFramebufferEXT and glBlitFramebuffer */
        {  128, 2560 }, /* glBlitFramebufferEXT and glBlitFramebufferNV */
        { 2560,  127 }, /* glBlitFramebufferNV and glBlitFramebuffer */
        { 2560,  128 }, /* glBlitFramebufferNV and glBlitFramebufferEXT */
        {  134,  135 }, /* glBufferData and glBufferDataARB */
        {  135,  134 }, /* glBufferDataARB and glBufferData */
        {  139, 2561 }, /* glBufferStorage and glBufferStorageEXT */
        { 2561,  139 }, /* glBufferStorageEXT and glBufferStorage */
        {  142,  143 }, /* glBufferSubData and glBufferSubDataARB */
        {  143,  142 }, /* glBufferSubDataARB and glBufferSubData */
        {  145,  146 }, /* glCheckFramebufferStatus and glCheckFramebufferStatusEXT */
        {  146,  145 }, /* glCheckFramebufferStatusEXT and glCheckFramebufferStatus */
        {  149,  150 }, /* glClampColor and glClampColorARB */
        {  150,  149 }, /* glClampColorARB and glClampColor */
        {  165,  166 }, /* glClearDepthf and glClearDepthfOES */
        {  166,  165 }, /* glClearDepthfOES and glClearDepthf */
        {  177, 2563 }, /* glClearTexImage and glClearTexImageEXT */
        { 2563,  177 }, /* glClearTexImageEXT and glClearTexImage */
        {  178, 2564 }, /* glClearTexSubImage and glClearTexSubImageEXT */
        { 2564,  178 }, /* glClearTexSubImageEXT and glClearTexSubImage */
        {  183, 2565 }, /* glClientWaitSync and glClientWaitSyncAPPLE */
        { 2565,  183 }, /* glClientWaitSyncAPPLE and glClientWaitSync */
        {  184, 2566 }, /* glClipControl and glClipControlEXT */
        { 2566,  184 }, /* glClipControlEXT and glClipControl */
        {  209,  208 }, /* glColorMaski and glColorMaskIndexedEXT */
        {  209, 2567 }, /* glColorMaski and glColorMaskiEXT */
        {  209, 2568 }, /* glColorMaski and glColorMaskiOES */
        { 2567,  208 }, /* glColorMaskiEXT and glColorMaskIndexedEXT */
        { 2567,  209 }, /* glColorMaskiEXT and glColorMaski */
        { 2567, 2568 }, /* glColorMaskiEXT and glColorMaskiOES */
        {  208,  209 }, /* glColorMaskIndexedEXT and glColorMaski */
        {  208, 2567 }, /* glColorMaskIndexedEXT and glColorMaskiEXT */
        {  208, 2568 }, /* glColorMaskIndexedEXT and glColorMaskiOES */
        { 2568,  208 }, /* glColorMaskiOES and glColorMaskIndexedEXT */
        { 2568,  209 }, /* glColorMaskiOES and glColorMaski */
        { 2568, 2567 }, /* glColorMaskiOES and glColorMaskiEXT */
        {  227,  228 }, /* glCompileShader and glCompileShaderARB */
        {  228,  227 }, /* glCompileShaderARB and glCompileShader */
        {  236,  237 }, /* glCompressedTexImage1D and glCompressedTexImage1DARB */
        {  237,  236 }, /* glCompressedTexImage1DARB and glCompressedTexImage1D */
        {  238,  239 }, /* glCompressedTexImage2D and glCompressedTexImage2DARB */
        {  239,  238 }, /* glCompressedTexImage2DARB and glCompressedTexImage2D */
        {  240,  241 }, /* glCompressedTexImage3D and glCompressedTexImage3DARB */
        {  241,  240 }, /* glCompressedTexImage3DARB and glCompressedTexImage3D */
        {  242,  243 }, /* glCompressedTexSubImage1D and glCompressedTexSubImage1DARB */
        {  243,  242 }, /* glCompressedTexSubImage1DARB and glCompressedTexSubImage1D */
        {  244,  245 }, /* glCompressedTexSubImage2D and glCompressedTexSubImage2DARB */
        {  245,  244 }, /* glCompressedTexSubImage2DARB and glCompressedTexSubImage2D */
        {  246,  247 }, /* glCompressedTexSubImage3D and glCompressedTexSubImage3DARB */
        {  247,  246 }, /* glCompressedTexSubImage3DARB and glCompressedTexSubImage3D */
        {  267, 2576 }, /* glCopyBufferSubData and glCopyBufferSubDataNV */
        { 2576,  267 }, /* glCopyBufferSubDataNV and glCopyBufferSubData */
        {  272, 2577 }, /* glCopyImageSubData and glCopyImageSubDataEXT */
        {  272, 2578 }, /* glCopyImageSubData and glCopyImageSubDataOES */
        { 2577,  272 }, /* glCopyImageSubDataEXT and glCopyImageSubData */
        { 2577, 2578 }, /* glCopyImageSubDataEXT and glCopyImageSubDataOES */
        { 2578,  272 }, /* glCopyImageSubDataOES and glCopyImageSubData */
        { 2578, 2577 }, /* glCopyImageSubDataOES and glCopyImageSubDataEXT */
        {  281,  282 }, /* glCopyTexImage1D and glCopyTexImage1DEXT */
        {  282,  281 }, /* glCopyTexImage1DEXT and glCopyTexImage1D */
        {  283,  284 }, /* glCopyTexImage2D and glCopyTexImage2DEXT */
        {  284,  283 }, /* glCopyTexImage2DEXT and glCopyTexImage2D */
        {  285,  286 }, /* glCopyTexSubImage1D and glCopyTexSubImage1DEXT */
        {  286,  285 }, /* glCopyTexSubImage1DEXT and glCopyTexSubImage1D */
        {  287,  288 }, /* glCopyTexSubImage2D and glCopyTexSubImage2DEXT */
        {  288,  287 }, /* glCopyTexSubImage2DEXT and glCopyTexSubImage2D */
        {  289,  290 }, /* glCopyTexSubImage3D and glCopyTexSubImage3DEXT */
        {  290,  289 }, /* glCopyTexSubImage3DEXT and glCopyTexSubImage3D */
        {  310,  311 }, /* glCreateProgram and glCreateProgramObjectARB */
        {  311,  310 }, /* glCreateProgramObjectARB and glCreateProgram */
        {  318,  319 }, /* glCreateShader and glCreateShaderObjectARB */
        {  319,  318 }, /* glCreateShaderObjectARB and glCreateShader */
        {  331,  333 }, /* glDebugMessageCallback and glDebugMessageCallbackARB */
        {  331, 2589 }, /* glDebugMessageCallback and glDebugMessageCallbackKHR */
        {  333,  331 }, /* glDebugMessageCallbackARB and glDebugMessageCallback */
        {  333, 2589 }, /* glDebugMessageCallbackARB and glDebugMessageCallbackKHR */
        { 2589,  331 }, /* glDebugMessageCallbackKHR and glDebugMessageCallback */
        { 2589,  333 }, /* glDebugMessageCallbackKHR and glDebugMessageCallbackARB */
        {  334,  335 }, /* glDebugMessageControl and glDebugMessageControlARB */
        {  334, 2590 }, /* glDebugMessageControl and glDebugMessageControlKHR */
        {  335,  334 }, /* glDebugMessageControlARB and glDebugMessageControl */
        {  335, 2590 }, /* glDebugMessageControlARB and glDebugMessageControlKHR */
        { 2590,  334 }, /* glDebugMessageControlKHR and glDebugMessageControl */
        { 2590,  335 }, /* glDebugMessageControlKHR and glDebugMessageControlARB */
        {  337,  339 }, /* glDebugMessageInsert and glDebugMessageInsertARB */
        {  337, 2591 }, /* glDebugMessageInsert and glDebugMessageInsertKHR */
        {  339,  337 }, /* glDebugMessageInsertARB and glDebugMessageInsert */
        {  339, 2591 }, /* glDebugMessageInsertARB and glDebugMessageInsertKHR */
        { 2591,  337 }, /* glDebugMessageInsertKHR and glDebugMessageInsert */
        { 2591,  339 }, /* glDebugMessageInsertKHR and glDebugMessageInsertARB */
        {  344,  345 }, /* glDeleteBuffers and glDeleteBuffersARB */
        {  345,  344 }, /* glDeleteBuffersARB and glDeleteBuffers */
        {  350,  351 }, /* glDeleteFramebuffers and glDeleteFramebuffersEXT */
        {  351,  350 }, /* glDeleteFramebuffersEXT and glDeleteFramebuffers */
        {  362,  363 }, /* glDeleteProgramsARB and glDeleteProgramsNV */
        {  363,  362 }, /* glDeleteProgramsNV and glDeleteProgramsARB */
        {  364,  365 }, /* glDeleteQueries and glDeleteQueriesARB */
        {  365,  364 }, /* glDeleteQueriesARB and glDeleteQueries */
        {  367,  368 }, /* glDeleteRenderbuffers and glDeleteRenderbuffersEXT */
        {  368,  367 }, /* glDeleteRenderbuffersEXT and glDeleteRenderbuffers */
        {  373, 2594 }, /* glDeleteSync and glDeleteSyncAPPLE */
        { 2594,  373 }, /* glDeleteSyncAPPLE and glDeleteSync */
        {  376,  377 }, /* glDeleteTransformFeedbacks and glDeleteTransformFeedbacksNV */
        {  377,  376 }, /* glDeleteTransformFeedbacksNV and glDeleteTransformFeedbacks */
        {  378,  379 }, /* glDeleteVertexArrays and glDeleteVertexArraysAPPLE */
        {  378, 2595 }, /* glDeleteVertexArrays and glDeleteVertexArraysOES */
        {  379,  378 }, /* glDeleteVertexArraysAPPLE and glDeleteVertexArrays */
        {  379, 2595 }, /* glDeleteVertexArraysAPPLE and glDeleteVertexArraysOES */
        { 2595,  378 }, /* glDeleteVertexArraysOES and glDeleteVertexArrays */
        { 2595,  379 }, /* glDeleteVertexArraysOES and glDeleteVertexArraysAPPLE */
        {  391,  392 }, /* glDepthRangef and glDepthRangefOES */
        {  392,  391 }, /* glDepthRangefOES and glDepthRangef */
        {  394,  395 }, /* glDetachObjectARB and glDetachShader */
        {  395,  394 }, /* glDetachShader and glDetachObjectARB */
        {  408,  400 }, /* glDisablei and glDisableIndexedEXT */
        {  408, 2602 }, /* glDisablei and glDisableiEXT */
        {  408, 2603 }, /* glDisablei and glDisableiNV */
        {  408, 2604 }, /* glDisablei and glDisableiOES */
        { 2602,  400 }, /* glDisableiEXT and glDisableIndexedEXT */
        { 2602,  408 }, /* glDisableiEXT and glDisablei */
        { 2602, 2603 }, /* glDisableiEXT and glDisableiNV */
        { 2602, 2604 }, /* glDisableiEXT and glDisableiOES */
        {  400,  408 }, /* glDisableIndexedEXT and glDisablei */
        {  400, 2602 }, /* glDisableIndexedEXT and glDisableiEXT */
        {  400, 2603 }, /* glDisableIndexedEXT and glDisableiNV */
        {  400, 2604 }, /* glDisableIndexedEXT and glDisableiOES */
        { 2603,  400 }, /* glDisableiNV and glDisableIndexedEXT */
        { 2603,  408 }, /* glDisableiNV and glDisablei */
        { 2603, 2602 }, /* glDisableiNV and glDisableiEXT */
        { 2603, 2604 }, /* glDisableiNV and glDisableiOES */
        { 2604,  400 }, /* glDisableiOES and glDisableIndexedEXT */
        { 2604,  408 }, /* glDisableiOES and glDisablei */
        { 2604, 2602 }, /* glDisableiOES and glDisableiEXT */
        { 2604, 2603 }, /* glDisableiOES and glDisableiNV */
        {  406,  407 }, /* glDisableVertexAttribArray and glDisableVertexAttribArrayARB */
        {  407,  406 }, /* glDisableVertexAttribArrayARB and glDisableVertexAttribArray */
        {  412,  413 }, /* glDrawArrays and glDrawArraysEXT */
        {  413,  412 }, /* glDrawArraysEXT and glDrawArrays */
        {  415, 2606 }, /* glDrawArraysInstanced and glDrawArraysInstancedANGLE */
        {  415,  416 }, /* glDrawArraysInstanced and glDrawArraysInstancedARB */
        {  415,  418 }, /* glDrawArraysInstanced and glDrawArraysInstancedEXT */
        {  415, 2609 }, /* glDrawArraysInstanced and glDrawArraysInstancedNV */
        { 2606,  415 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstanced */
        { 2606,  416 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstancedARB */
        { 2606,  418 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstancedEXT */
        { 2606, 2609 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstancedNV */
        {  416,  415 }, /* glDrawArraysInstancedARB and glDrawArraysInstanced */
        {  416, 2606 }, /* glDrawArraysInstancedARB and glDrawArraysInstancedANGLE */
        {  416,  418 }, /* glDrawArraysInstancedARB and glDrawArraysInstancedEXT */
        {  416, 2609 }, /* glDrawArraysInstancedARB and glDrawArraysInstancedNV */
        {  417, 2607 }, /* glDrawArraysInstancedBaseInstance and glDrawArraysInstancedBaseInstanceANGLE */
        {  417, 2608 }, /* glDrawArraysInstancedBaseInstance and glDrawArraysInstancedBaseInstanceEXT */
        { 2607,  417 }, /* glDrawArraysInstancedBaseInstanceANGLE and glDrawArraysInstancedBaseInstance */
        { 2607, 2608 }, /* glDrawArraysInstancedBaseInstanceANGLE and glDrawArraysInstancedBaseInstanceEXT */
        { 2608,  417 }, /* glDrawArraysInstancedBaseInstanceEXT and glDrawArraysInstancedBaseInstance */
        { 2608, 2607 }, /* glDrawArraysInstancedBaseInstanceEXT and glDrawArraysInstancedBaseInstanceANGLE */
        {  418,  415 }, /* glDrawArraysInstancedEXT and glDrawArraysInstanced */
        {  418, 2606 }, /* glDrawArraysInstancedEXT and glDrawArraysInstancedANGLE */
        {  418,  416 }, /* glDrawArraysInstancedEXT and glDrawArraysInstancedARB */
        {  418, 2609 }, /* glDrawArraysInstancedEXT and glDrawArraysInstancedNV */
        { 2609,  415 }, /* glDrawArraysInstancedNV and glDrawArraysInstanced */
        { 2609, 2606 }, /* glDrawArraysInstancedNV and glDrawArraysInstancedANGLE */
        { 2609,  416 }, /* glDrawArraysInstancedNV and glDrawArraysInstancedARB */
        { 2609,  418 }, /* glDrawArraysInstancedNV and glDrawArraysInstancedEXT */
        {  420,  421 }, /* glDrawBuffers and glDrawBuffersARB */
        {  420,  422 }, /* glDrawBuffers and glDrawBuffersATI */
        {  420, 2610 }, /* glDrawBuffers and glDrawBuffersEXT */
        {  421,  420 }, /* glDrawBuffersARB and glDrawBuffers */
        {  421,  422 }, /* glDrawBuffersARB and glDrawBuffersATI */
        {  421, 2610 }, /* glDrawBuffersARB and glDrawBuffersEXT */
        {  422,  420 }, /* glDrawBuffersATI and glDrawBuffers */
        {  422,  421 }, /* glDrawBuffersATI and glDrawBuffersARB */
        {  422, 2610 }, /* glDrawBuffersATI and glDrawBuffersEXT */
        { 2610,  420 }, /* glDrawBuffersEXT and glDrawBuffers */
        { 2610,  421 }, /* glDrawBuffersEXT and glDrawBuffersARB */
        { 2610,  422 }, /* glDrawBuffersEXT and glDrawBuffersATI */
        {  430, 2613 }, /* glDrawElementsBaseVertex and glDrawElementsBaseVertexEXT */
        {  430, 2614 }, /* glDrawElementsBaseVertex and glDrawElementsBaseVertexOES */
        { 2613,  430 }, /* glDrawElementsBaseVertexEXT and glDrawElementsBaseVertex */
        { 2613, 2614 }, /* glDrawElementsBaseVertexEXT and glDrawElementsBaseVertexOES */
        { 2614,  430 }, /* glDrawElementsBaseVertexOES and glDrawElementsBaseVertex */
        { 2614, 2613 }, /* glDrawElementsBaseVertexOES and glDrawElementsBaseVertexEXT */
        {  432, 2615 }, /* glDrawElementsInstanced and glDrawElementsInstancedANGLE */
        {  432,  433 }, /* glDrawElementsInstanced and glDrawElementsInstancedARB */
        {  432,  437 }, /* glDrawElementsInstanced and glDrawElementsInstancedEXT */
        {  432, 2621 }, /* glDrawElementsInstanced and glDrawElementsInstancedNV */
        { 2615,  432 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstanced */
        { 2615,  433 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstancedARB */
        { 2615,  437 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstancedEXT */
        { 2615, 2621 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstancedNV */
        {  433,  432 }, /* glDrawElementsInstancedARB and glDrawElementsInstanced */
        {  433, 2615 }, /* glDrawElementsInstancedARB and glDrawElementsInstancedANGLE */
        {  433,  437 }, /* glDrawElementsInstancedARB and glDrawElementsInstancedEXT */
        {  433, 2621 }, /* glDrawElementsInstancedARB and glDrawElementsInstancedNV */
        {  434, 2616 }, /* glDrawElementsInstancedBaseInstance and glDrawElementsInstancedBaseInstanceEXT */
        { 2616,  434 }, /* glDrawElementsInstancedBaseInstanceEXT and glDrawElementsInstancedBaseInstance */
        {  435, 2619 }, /* glDrawElementsInstancedBaseVertex and glDrawElementsInstancedBaseVertexEXT */
        {  435, 2620 }, /* glDrawElementsInstancedBaseVertex and glDrawElementsInstancedBaseVertexOES */
        {  436, 2617 }, /* glDrawElementsInstancedBaseVertexBaseInstance and glDrawElementsInstancedBaseVertexBaseInstanceANGLE */
        {  436, 2618 }, /* glDrawElementsInstancedBaseVertexBaseInstance and glDrawElementsInstancedBaseVertexBaseInstanceEXT */
        { 2617,  436 }, /* glDrawElementsInstancedBaseVertexBaseInstanceANGLE and glDrawElementsInstancedBaseVertexBaseInstance */
        { 2617, 2618 }, /* glDrawElementsInstancedBaseVertexBaseInstanceANGLE and glDrawElementsInstancedBaseVertexBaseInstanceEXT */
        { 2618,  436 }, /* glDrawElementsInstancedBaseVertexBaseInstanceEXT and glDrawElementsInstancedBaseVertexBaseInstance */
        { 2618, 2617 }, /* glDrawElementsInstancedBaseVertexBaseInstanceEXT and glDrawElementsInstancedBaseVertexBaseInstanceANGLE */
        { 2619,  435 }, /* glDrawElementsInstancedBaseVertexEXT and glDrawElementsInstancedBaseVertex */
        { 2619, 2620 }, /* glDrawElementsInstancedBaseVertexEXT and glDrawElementsInstancedBaseVertexOES */
        { 2620,  435 }, /* glDrawElementsInstancedBaseVertexOES and glDrawElementsInstancedBaseVertex */
        { 2620, 2619 }, /* glDrawElementsInstancedBaseVertexOES and glDrawElementsInstancedBaseVertexEXT */
        {  437,  432 }, /* glDrawElementsInstancedEXT and glDrawElementsInstanced */
        {  437, 2615 }, /* glDrawElementsInstancedEXT and glDrawElementsInstancedANGLE */
        {  437,  433 }, /* glDrawElementsInstancedEXT and glDrawElementsInstancedARB */
        {  437, 2621 }, /* glDrawElementsInstancedEXT and glDrawElementsInstancedNV */
        { 2621,  432 }, /* glDrawElementsInstancedNV and glDrawElementsInstanced */
        { 2621, 2615 }, /* glDrawElementsInstancedNV and glDrawElementsInstancedANGLE */
        { 2621,  433 }, /* glDrawElementsInstancedNV and glDrawElementsInstancedARB */
        { 2621,  437 }, /* glDrawElementsInstancedNV and glDrawElementsInstancedEXT */
        {  443,  445 }, /* glDrawRangeElements and glDrawRangeElementsEXT */
        {  444, 2622 }, /* glDrawRangeElementsBaseVertex and glDrawRangeElementsBaseVertexEXT */
        {  444, 2623 }, /* glDrawRangeElementsBaseVertex and glDrawRangeElementsBaseVertexOES */
        { 2622,  444 }, /* glDrawRangeElementsBaseVertexEXT and glDrawRangeElementsBaseVertex */
        { 2622, 2623 }, /* glDrawRangeElementsBaseVertexEXT and glDrawRangeElementsBaseVertexOES */
        { 2623,  444 }, /* glDrawRangeElementsBaseVertexOES and glDrawRangeElementsBaseVertex */
        { 2623, 2622 }, /* glDrawRangeElementsBaseVertexOES and glDrawRangeElementsBaseVertexEXT */
        {  445,  443 }, /* glDrawRangeElementsEXT and glDrawRangeElements */
        {  447, 2624 }, /* glDrawTransformFeedback and glDrawTransformFeedbackEXT */
        {  447,  449 }, /* glDrawTransformFeedback and glDrawTransformFeedbackNV */
        { 2624,  447 }, /* glDrawTransformFeedbackEXT and glDrawTransformFeedback */
        { 2624,  449 }, /* glDrawTransformFeedbackEXT and glDrawTransformFeedbackNV */
        {  448, 2625 }, /* glDrawTransformFeedbackInstanced and glDrawTransformFeedbackInstancedEXT */
        { 2625,  448 }, /* glDrawTransformFeedbackInstancedEXT and glDrawTransformFeedbackInstanced */
        {  449,  447 }, /* glDrawTransformFeedbackNV and glDrawTransformFeedback */
        {  449, 2624 }, /* glDrawTransformFeedbackNV and glDrawTransformFeedbackEXT */
        {  471,  463 }, /* glEnablei and glEnableIndexedEXT */
        {  471, 2629 }, /* glEnablei and glEnableiEXT */
        {  471, 2630 }, /* glEnablei and glEnableiNV */
        {  471, 2631 }, /* glEnablei and glEnableiOES */
        { 2629,  463 }, /* glEnableiEXT and glEnableIndexedEXT */
        { 2629,  471 }, /* glEnableiEXT and glEnablei */
        { 2629, 2630 }, /* glEnableiEXT and glEnableiNV */
        { 2629, 2631 }, /* glEnableiEXT and glEnableiOES */
        {  463,  471 }, /* glEnableIndexedEXT and glEnablei */
        {  463, 2629 }, /* glEnableIndexedEXT and glEnableiEXT */
        {  463, 2630 }, /* glEnableIndexedEXT and glEnableiNV */
        {  463, 2631 }, /* glEnableIndexedEXT and glEnableiOES */
        { 2630,  463 }, /* glEnableiNV and glEnableIndexedEXT */
        { 2630,  471 }, /* glEnableiNV and glEnablei */
        { 2630, 2629 }, /* glEnableiNV and glEnableiEXT */
        { 2630, 2631 }, /* glEnableiNV and glEnableiOES */
        { 2631,  463 }, /* glEnableiOES and glEnableIndexedEXT */
        { 2631,  471 }, /* glEnableiOES and glEnablei */
        { 2631, 2629 }, /* glEnableiOES and glEnableiEXT */
        { 2631, 2630 }, /* glEnableiOES and glEnableiNV */
        {  469,  470 }, /* glEnableVertexAttribArray and glEnableVertexAttribArrayARB */
        {  470,  469 }, /* glEnableVertexAttribArrayARB and glEnableVertexAttribArray */
        {  472,  473 }, /* glEndConditionalRender and glEndConditionalRenderNV */
        {  472,  474 }, /* glEndConditionalRender and glEndConditionalRenderNVX */
        {  473,  472 }, /* glEndConditionalRenderNV and glEndConditionalRender */
        {  473,  474 }, /* glEndConditionalRenderNV and glEndConditionalRenderNVX */
        {  474,  472 }, /* glEndConditionalRenderNVX and glEndConditionalRender */
        {  474,  473 }, /* glEndConditionalRenderNVX and glEndConditionalRenderNV */
        {  479,  480 }, /* glEndQuery and glEndQueryARB */
        {  480,  479 }, /* glEndQueryARB and glEndQuery */
        {  482,  483 }, /* glEndTransformFeedback and glEndTransformFeedbackEXT */
        {  482,  484 }, /* glEndTransformFeedback and glEndTransformFeedbackNV */
        {  483,  482 }, /* glEndTransformFeedbackEXT and glEndTransformFeedback */
        {  483,  484 }, /* glEndTransformFeedbackEXT and glEndTransformFeedbackNV */
        {  484,  482 }, /* glEndTransformFeedbackNV and glEndTransformFeedback */
        {  484,  483 }, /* glEndTransformFeedbackNV and glEndTransformFeedbackEXT */
        {  496, 2648 }, /* glFenceSync and glFenceSyncAPPLE */
        { 2648,  496 }, /* glFenceSyncAPPLE and glFenceSync */
        {  505,  506 }, /* glFlushMappedBufferRange and glFlushMappedBufferRangeAPPLE */
        {  505, 2649 }, /* glFlushMappedBufferRange and glFlushMappedBufferRangeEXT */
        {  506,  505 }, /* glFlushMappedBufferRangeAPPLE and glFlushMappedBufferRange */
        {  506, 2649 }, /* glFlushMappedBufferRangeAPPLE and glFlushMappedBufferRangeEXT */
        { 2649,  505 }, /* glFlushMappedBufferRangeEXT and glFlushMappedBufferRange */
        { 2649,  506 }, /* glFlushMappedBufferRangeEXT and glFlushMappedBufferRangeAPPLE */
        {  548,  549 }, /* glFramebufferRenderbuffer and glFramebufferRenderbufferEXT */
        {  549,  548 }, /* glFramebufferRenderbufferEXT and glFramebufferRenderbuffer */
        {  553,  560 }, /* glFramebufferTexture and glFramebufferTextureARB */
        {  553,  561 }, /* glFramebufferTexture and glFramebufferTextureEXT */
        {  553, 2667 }, /* glFramebufferTexture and glFramebufferTextureOES */
        {  554,  555 }, /* glFramebufferTexture1D and glFramebufferTexture1DEXT */
        {  555,  554 }, /* glFramebufferTexture1DEXT and glFramebufferTexture1D */
        {  556,  557 }, /* glFramebufferTexture2D and glFramebufferTexture2DEXT */
        {  557,  556 }, /* glFramebufferTexture2DEXT and glFramebufferTexture2D */
        {  558,  559 }, /* glFramebufferTexture3D and glFramebufferTexture3DEXT */
        {  559,  558 }, /* glFramebufferTexture3DEXT and glFramebufferTexture3D */
        {  560,  553 }, /* glFramebufferTextureARB and glFramebufferTexture */
        {  560,  561 }, /* glFramebufferTextureARB and glFramebufferTextureEXT */
        {  560, 2667 }, /* glFramebufferTextureARB and glFramebufferTextureOES */
        {  561,  553 }, /* glFramebufferTextureEXT and glFramebufferTexture */
        {  561,  560 }, /* glFramebufferTextureEXT and glFramebufferTextureARB */
        {  561, 2667 }, /* glFramebufferTextureEXT and glFramebufferTextureOES */
        {  562,  563 }, /* glFramebufferTextureFaceARB and glFramebufferTextureFaceEXT */
        {  563,  562 }, /* glFramebufferTextureFaceEXT and glFramebufferTextureFaceARB */
        {  564,  565 }, /* glFramebufferTextureLayer and glFramebufferTextureLayerARB */
        {  564,  566 }, /* glFramebufferTextureLayer and glFramebufferTextureLayerEXT */
        {  565,  564 }, /* glFramebufferTextureLayerARB and glFramebufferTextureLayer */
        {  565,  566 }, /* glFramebufferTextureLayerARB and glFramebufferTextureLayerEXT */
        {  566,  564 }, /* glFramebufferTextureLayerEXT and glFramebufferTextureLayer */
        {  566,  565 }, /* glFramebufferTextureLayerEXT and glFramebufferTextureLayerARB */
        { 2667,  553 }, /* glFramebufferTextureOES and glFramebufferTexture */
        { 2667,  560 }, /* glFramebufferTextureOES and glFramebufferTextureARB */
        { 2667,  561 }, /* glFramebufferTextureOES and glFramebufferTextureEXT */
        {  573,  574 }, /* glGenBuffers and glGenBuffersARB */
        {  574,  573 }, /* glGenBuffersARB and glGenBuffers */
        {  602,  603 }, /* glGenerateMipmap and glGenerateMipmapEXT */
        {  603,  602 }, /* glGenerateMipmapEXT and glGenerateMipmap */
        {  578,  579 }, /* glGenFramebuffers and glGenFramebuffersEXT */
        {  579,  578 }, /* glGenFramebuffersEXT and glGenFramebuffers */
        {  585,  586 }, /* glGenProgramsARB and glGenProgramsNV */
        {  586,  585 }, /* glGenProgramsNV and glGenProgramsARB */
        {  587,  588 }, /* glGenQueries and glGenQueriesARB */
        {  588,  587 }, /* glGenQueriesARB and glGenQueries */
        {  590,  591 }, /* glGenRenderbuffers and glGenRenderbuffersEXT */
        {  591,  590 }, /* glGenRenderbuffersEXT and glGenRenderbuffers */
        {  597,  598 }, /* glGenTransformFeedbacks and glGenTransformFeedbacksNV */
        {  598,  597 }, /* glGenTransformFeedbacksNV and glGenTransformFeedbacks */
        {  599,  600 }, /* glGenVertexArrays and glGenVertexArraysAPPLE */
        {  599, 2671 }, /* glGenVertexArrays and glGenVertexArraysOES */
        {  600,  599 }, /* glGenVertexArraysAPPLE and glGenVertexArrays */
        {  600, 2671 }, /* glGenVertexArraysAPPLE and glGenVertexArraysOES */
        { 2671,  599 }, /* glGenVertexArraysOES and glGenVertexArrays */
        { 2671,  600 }, /* glGenVertexArraysOES and glGenVertexArraysAPPLE */
        {  608,  609 }, /* glGetActiveAttrib and glGetActiveAttribARB */
        {  609,  608 }, /* glGetActiveAttribARB and glGetActiveAttrib */
        {  613,  614 }, /* glGetActiveUniform and glGetActiveUniformARB */
        {  614,  613 }, /* glGetActiveUniformARB and glGetActiveUniform */
        {  624,  625 }, /* glGetAttribLocation and glGetAttribLocationARB */
        {  625,  624 }, /* glGetAttribLocationARB and glGetAttribLocation */
        {  627,  626 }, /* glGetBooleani_v and glGetBooleanIndexedvEXT */
        {  626,  627 }, /* glGetBooleanIndexedvEXT and glGetBooleani_v */
        {  630,  631 }, /* glGetBufferParameteriv and glGetBufferParameterivARB */
        {  631,  630 }, /* glGetBufferParameterivARB and glGetBufferParameteriv */
        {  633,  634 }, /* glGetBufferPointerv and glGetBufferPointervARB */
        {  633, 2677 }, /* glGetBufferPointerv and glGetBufferPointervOES */
        {  634,  633 }, /* glGetBufferPointervARB and glGetBufferPointerv */
        {  634, 2677 }, /* glGetBufferPointervARB and glGetBufferPointervOES */
        { 2677,  633 }, /* glGetBufferPointervOES and glGetBufferPointerv */
        { 2677,  634 }, /* glGetBufferPointervOES and glGetBufferPointervARB */
        {  635,  636 }, /* glGetBufferSubData and glGetBufferSubDataARB */
        {  636,  635 }, /* glGetBufferSubDataARB and glGetBufferSubData */
        {  652, 2679 }, /* glGetCompressedTexImage and glGetCompressedTexImageANGLE */
        {  652,  653 }, /* glGetCompressedTexImage and glGetCompressedTexImageARB */
        { 2679,  652 }, /* glGetCompressedTexImageANGLE and glGetCompressedTexImage */
        { 2679,  653 }, /* glGetCompressedTexImageANGLE and glGetCompressedTexImageARB */
        {  653,  652 }, /* glGetCompressedTexImageARB and glGetCompressedTexImage */
        {  653, 2679 }, /* glGetCompressedTexImageARB and glGetCompressedTexImageANGLE */
        {  662,  664 }, /* glGetDebugMessageLog and glGetDebugMessageLogARB */
        {  662, 2680 }, /* glGetDebugMessageLog and glGetDebugMessageLogKHR */
        {  664,  662 }, /* glGetDebugMessageLogARB and glGetDebugMessageLog */
        {  664, 2680 }, /* glGetDebugMessageLogARB and glGetDebugMessageLogKHR */
        { 2680,  662 }, /* glGetDebugMessageLogKHR and glGetDebugMessageLog */
        { 2680,  664 }, /* glGetDebugMessageLogKHR and glGetDebugMessageLogARB */
        {  667,  666 }, /* glGetDoublei_v and glGetDoubleIndexedvEXT */
        {  667,  668 }, /* glGetDoublei_v and glGetDoublei_vEXT */
        {  668,  666 }, /* glGetDoublei_vEXT and glGetDoubleIndexedvEXT */
        {  668,  667 }, /* glGetDoublei_vEXT and glGetDoublei_v */
        {  666,  667 }, /* glGetDoubleIndexedvEXT and glGetDoublei_v */
        {  666,  668 }, /* glGetDoubleIndexedvEXT and glGetDoublei_vEXT */
        {  677,  676 }, /* glGetFloati_v and glGetFloatIndexedvEXT */
        {  677,  678 }, /* glGetFloati_v and glGetFloati_vEXT */
        {  677, 2683 }, /* glGetFloati_v and glGetFloati_vNV */
        {  677, 2684 }, /* glGetFloati_v and glGetFloati_vOES */
        {  678,  676 }, /* glGetFloati_vEXT and glGetFloatIndexedvEXT */
        {  678,  677 }, /* glGetFloati_vEXT and glGetFloati_v */
        {  678, 2683 }, /* glGetFloati_vEXT and glGetFloati_vNV */
        {  678, 2684 }, /* glGetFloati_vEXT and glGetFloati_vOES */
        { 2683,  676 }, /* glGetFloati_vNV and glGetFloatIndexedvEXT */
        { 2683,  677 }, /* glGetFloati_vNV and glGetFloati_v */
        { 2683,  678 }, /* glGetFloati_vNV and glGetFloati_vEXT */
        { 2683, 2684 }, /* glGetFloati_vNV and glGetFloati_vOES */
        { 2684,  676 }, /* glGetFloati_vOES and glGetFloatIndexedvEXT */
        { 2684,  677 }, /* glGetFloati_vOES and glGetFloati_v */
        { 2684,  678 }, /* glGetFloati_vOES and glGetFloati_vEXT */
        { 2684, 2683 }, /* glGetFloati_vOES and glGetFloati_vNV */
        {  676,  677 }, /* glGetFloatIndexedvEXT and glGetFloati_v */
        {  676,  678 }, /* glGetFloatIndexedvEXT and glGetFloati_vEXT */
        {  676, 2683 }, /* glGetFloatIndexedvEXT and glGetFloati_vNV */
        {  676, 2684 }, /* glGetFloatIndexedvEXT and glGetFloati_vOES */
        {  681, 2686 }, /* glGetFragDataIndex and glGetFragDataIndexEXT */
        { 2686,  681 }, /* glGetFragDataIndexEXT and glGetFragDataIndex */
        {  682,  683 }, /* glGetFragDataLocation and glGetFragDataLocationEXT */
        {  683,  682 }, /* glGetFragDataLocationEXT and glGetFragDataLocation */
        {  688,  689 }, /* glGetFramebufferAttachmentParameteriv and glGetFramebufferAttachmentParameterivEXT */
        {  689,  688 }, /* glGetFramebufferAttachmentParameterivEXT and glGetFramebufferAttachmentParameteriv */
        {  694, 2695 }, /* glGetGraphicsResetStatus and glGetGraphicsResetStatusEXT */
        {  694, 2696 }, /* glGetGraphicsResetStatus and glGetGraphicsResetStatusKHR */
        { 2695,  694 }, /* glGetGraphicsResetStatusEXT and glGetGraphicsResetStatus */
        { 2695, 2696 }, /* glGetGraphicsResetStatusEXT and glGetGraphicsResetStatusKHR */
        { 2696,  694 }, /* glGetGraphicsResetStatusKHR and glGetGraphicsResetStatus */
        { 2696, 2695 }, /* glGetGraphicsResetStatusKHR and glGetGraphicsResetStatusEXT */
        {  708, 2698 }, /* glGetInteger64v and glGetInteger64vAPPLE */
        {  708, 2699 }, /* glGetInteger64v and glGetInteger64vEXT */
        { 2698,  708 }, /* glGetInteger64vAPPLE and glGetInteger64v */
        { 2698, 2699 }, /* glGetInteger64vAPPLE and glGetInteger64vEXT */
        { 2699,  708 }, /* glGetInteger64vEXT and glGetInteger64v */
        { 2699, 2698 }, /* glGetInteger64vEXT and glGetInteger64vAPPLE */
        {  710,  709 }, /* glGetIntegeri_v and glGetIntegerIndexedvEXT */
        {  709,  710 }, /* glGetIntegerIndexedvEXT and glGetIntegeri_v */
        {  750, 2705 }, /* glGetMultisamplefv and glGetMultisamplefvANGLE */
        {  750,  751 }, /* glGetMultisamplefv and glGetMultisamplefvNV */
        { 2705,  750 }, /* glGetMultisamplefvANGLE and glGetMultisamplefv */
        { 2705,  751 }, /* glGetMultisamplefvANGLE and glGetMultisamplefvNV */
        {  751,  750 }, /* glGetMultisamplefvNV and glGetMultisamplefv */
        {  751, 2705 }, /* glGetMultisamplefvNV and glGetMultisamplefvANGLE */
        {  997, 2759 }, /* glGetnUniformfv and glGetnUniformfvEXT */
        {  997, 2760 }, /* glGetnUniformfv and glGetnUniformfvKHR */
        { 2759,  997 }, /* glGetnUniformfvEXT and glGetnUniformfv */
        { 2759, 2760 }, /* glGetnUniformfvEXT and glGetnUniformfvKHR */
        { 2760,  997 }, /* glGetnUniformfvKHR and glGetnUniformfv */
        { 2760, 2759 }, /* glGetnUniformfvKHR and glGetnUniformfvEXT */
        { 1000, 2762 }, /* glGetnUniformiv and glGetnUniformivEXT */
        { 1000, 2763 }, /* glGetnUniformiv and glGetnUniformivKHR */
        { 2762, 1000 }, /* glGetnUniformivEXT and glGetnUniformiv */
        { 2762, 2763 }, /* glGetnUniformivEXT and glGetnUniformivKHR */
        { 2763, 1000 }, /* glGetnUniformivKHR and glGetnUniformiv */
        { 2763, 2762 }, /* glGetnUniformivKHR and glGetnUniformivEXT */
        { 1003, 2765 }, /* glGetnUniformuiv and glGetnUniformuivKHR */
        { 2765, 1003 }, /* glGetnUniformuivKHR and glGetnUniformuiv */
        {  778, 2707 }, /* glGetObjectLabel and glGetObjectLabelKHR */
        { 2707,  778 }, /* glGetObjectLabelKHR and glGetObjectLabel */
        {  783, 2708 }, /* glGetObjectPtrLabel and glGetObjectPtrLabelKHR */
        { 2708,  783 }, /* glGetObjectPtrLabelKHR and glGetObjectPtrLabel */
        {  812,  813 }, /* glGetPointerv and glGetPointervEXT */
        {  812, 2709 }, /* glGetPointerv and glGetPointervKHR */
        {  813,  812 }, /* glGetPointervEXT and glGetPointerv */
        {  813, 2709 }, /* glGetPointervEXT and glGetPointervKHR */
        { 2709,  812 }, /* glGetPointervKHR and glGetPointerv */
        { 2709,  813 }, /* glGetPointervKHR and glGetPointervEXT */
        {  814, 2711 }, /* glGetProgramBinary and glGetProgramBinaryOES */
        { 2711,  814 }, /* glGetProgramBinaryOES and glGetProgramBinary */
        {  857,  858 }, /* glGetQueryiv and glGetQueryivARB */
        {  858,  857 }, /* glGetQueryivARB and glGetQueryiv */
        {  849,  850 }, /* glGetQueryObjecti64v and glGetQueryObjecti64vEXT */
        {  850,  849 }, /* glGetQueryObjecti64vEXT and glGetQueryObjecti64v */
        {  851,  852 }, /* glGetQueryObjectiv and glGetQueryObjectivARB */
        {  851, 2718 }, /* glGetQueryObjectiv and glGetQueryObjectivEXT */
        {  852,  851 }, /* glGetQueryObjectivARB and glGetQueryObjectiv */
        {  852, 2718 }, /* glGetQueryObjectivARB and glGetQueryObjectivEXT */
        { 2718,  851 }, /* glGetQueryObjectivEXT and glGetQueryObjectiv */
        { 2718,  852 }, /* glGetQueryObjectivEXT and glGetQueryObjectivARB */
        {  853,  854 }, /* glGetQueryObjectui64v and glGetQueryObjectui64vEXT */
        {  854,  853 }, /* glGetQueryObjectui64vEXT and glGetQueryObjectui64v */
        {  855,  856 }, /* glGetQueryObjectuiv and glGetQueryObjectuivARB */
        {  856,  855 }, /* glGetQueryObjectuivARB and glGetQueryObjectuiv */
        {  859,  860 }, /* glGetRenderbufferParameteriv and glGetRenderbufferParameterivEXT */
        {  860,  859 }, /* glGetRenderbufferParameterivEXT and glGetRenderbufferParameteriv */
        {  861, 2727 }, /* glGetSamplerParameterIiv and glGetSamplerParameterIivEXT */
        {  861, 2728 }, /* glGetSamplerParameterIiv and glGetSamplerParameterIivOES */
        { 2727,  861 }, /* glGetSamplerParameterIivEXT and glGetSamplerParameterIiv */
        { 2727, 2728 }, /* glGetSamplerParameterIivEXT and glGetSamplerParameterIivOES */
        { 2728,  861 }, /* glGetSamplerParameterIivOES and glGetSamplerParameterIiv */
        { 2728, 2727 }, /* glGetSamplerParameterIivOES and glGetSamplerParameterIivEXT */
        {  862, 2730 }, /* glGetSamplerParameterIuiv and glGetSamplerParameterIuivEXT */
        {  862, 2731 }, /* glGetSamplerParameterIuiv and glGetSamplerParameterIuivOES */
        { 2730,  862 }, /* glGetSamplerParameterIuivEXT and glGetSamplerParameterIuiv */
        { 2730, 2731 }, /* glGetSamplerParameterIuivEXT and glGetSamplerParameterIuivOES */
        { 2731,  862 }, /* glGetSamplerParameterIuivOES and glGetSamplerParameterIuiv */
        { 2731, 2730 }, /* glGetSamplerParameterIuivOES and glGetSamplerParameterIuivEXT */
        {  870,  871 }, /* glGetShaderSource and glGetShaderSourceARB */
        {  871,  870 }, /* glGetShaderSourceARB and glGetShaderSource */
        {  881, 2736 }, /* glGetSynciv and glGetSyncivAPPLE */
        { 2736,  881 }, /* glGetSyncivAPPLE and glGetSynciv */
        {  887, 2737 }, /* glGetTexImage and glGetTexImageANGLE */
        { 2737,  887 }, /* glGetTexImageANGLE and glGetTexImage */
        {  888, 2738 }, /* glGetTexLevelParameterfv and glGetTexLevelParameterfvANGLE */
        { 2738,  888 }, /* glGetTexLevelParameterfvANGLE and glGetTexLevelParameterfv */
        {  889, 2740 }, /* glGetTexLevelParameteriv and glGetTexLevelParameterivANGLE */
        { 2740,  889 }, /* glGetTexLevelParameterivANGLE and glGetTexLevelParameteriv */
        {  891,  892 }, /* glGetTexParameterIiv and glGetTexParameterIivEXT */
        {  891, 2742 }, /* glGetTexParameterIiv and glGetTexParameterIivOES */
        {  892,  891 }, /* glGetTexParameterIivEXT and glGetTexParameterIiv */
        {  892, 2742 }, /* glGetTexParameterIivEXT and glGetTexParameterIivOES */
        { 2742,  891 }, /* glGetTexParameterIivOES and glGetTexParameterIiv */
        { 2742,  892 }, /* glGetTexParameterIivOES and glGetTexParameterIivEXT */
        {  893,  894 }, /* glGetTexParameterIuiv and glGetTexParameterIuivEXT */
        {  893, 2744 }, /* glGetTexParameterIuiv and glGetTexParameterIuivOES */
        {  894,  893 }, /* glGetTexParameterIuivEXT and glGetTexParameterIuiv */
        {  894, 2744 }, /* glGetTexParameterIuivEXT and glGetTexParameterIuivOES */
        { 2744,  893 }, /* glGetTexParameterIuivOES and glGetTexParameterIuiv */
        { 2744,  894 }, /* glGetTexParameterIuivOES and glGetTexParameterIuivEXT */
        {  899, 2748 }, /* glGetTextureHandleARB and glGetTextureHandleIMG */
        { 2748,  899 }, /* glGetTextureHandleIMG and glGetTextureHandleARB */
        {  915, 2749 }, /* glGetTextureSamplerHandleARB and glGetTextureSamplerHandleIMG */
        { 2749,  915 }, /* glGetTextureSamplerHandleIMG and glGetTextureSamplerHandleARB */
        {  919,  920 }, /* glGetTransformFeedbackVarying and glGetTransformFeedbackVaryingEXT */
        {  920,  919 }, /* glGetTransformFeedbackVaryingEXT and glGetTransformFeedbackVarying */
        {  933,  934 }, /* glGetUniformfv and glGetUniformfvARB */
        {  934,  933 }, /* glGetUniformfvARB and glGetUniformfv */
        {  937,  938 }, /* glGetUniformiv and glGetUniformivARB */
        {  938,  937 }, /* glGetUniformivARB and glGetUniformiv */
        {  928,  929 }, /* glGetUniformLocation and glGetUniformLocationARB */
        {  929,  928 }, /* glGetUniformLocationARB and glGetUniformLocation */
        {  941,  942 }, /* glGetUniformuiv and glGetUniformuivEXT */
        {  942,  941 }, /* glGetUniformuivEXT and glGetUniformuiv */
        {  973,  974 }, /* glGetVertexAttribdv and glGetVertexAttribdvARB */
        {  973,  975 }, /* glGetVertexAttribdv and glGetVertexAttribdvNV */
        {  974,  973 }, /* glGetVertexAttribdvARB and glGetVertexAttribdv */
        {  974,  975 }, /* glGetVertexAttribdvARB and glGetVertexAttribdvNV */
        {  975,  973 }, /* glGetVertexAttribdvNV and glGetVertexAttribdv */
        {  975,  974 }, /* glGetVertexAttribdvNV and glGetVertexAttribdvARB */
        {  976,  977 }, /* glGetVertexAttribfv and glGetVertexAttribfvARB */
        {  976,  978 }, /* glGetVertexAttribfv and glGetVertexAttribfvNV */
        {  977,  976 }, /* glGetVertexAttribfvARB and glGetVertexAttribfv */
        {  977,  978 }, /* glGetVertexAttribfvARB and glGetVertexAttribfvNV */
        {  978,  976 }, /* glGetVertexAttribfvNV and glGetVertexAttribfv */
        {  978,  977 }, /* glGetVertexAttribfvNV and glGetVertexAttribfvARB */
        {  961,  962 }, /* glGetVertexAttribIiv and glGetVertexAttribIivEXT */
        {  962,  961 }, /* glGetVertexAttribIivEXT and glGetVertexAttribIiv */
        {  963,  964 }, /* glGetVertexAttribIuiv and glGetVertexAttribIuivEXT */
        {  964,  963 }, /* glGetVertexAttribIuivEXT and glGetVertexAttribIuiv */
        {  979,  980 }, /* glGetVertexAttribiv and glGetVertexAttribivARB */
        {  979,  981 }, /* glGetVertexAttribiv and glGetVertexAttribivNV */
        {  980,  979 }, /* glGetVertexAttribivARB and glGetVertexAttribiv */
        {  980,  981 }, /* glGetVertexAttribivARB and glGetVertexAttribivNV */
        {  981,  979 }, /* glGetVertexAttribivNV and glGetVertexAttribiv */
        {  981,  980 }, /* glGetVertexAttribivNV and glGetVertexAttribivARB */
        {  965,  966 }, /* glGetVertexAttribLdv and glGetVertexAttribLdvEXT */
        {  966,  965 }, /* glGetVertexAttribLdvEXT and glGetVertexAttribLdv */
        {  970,  971 }, /* glGetVertexAttribPointerv and glGetVertexAttribPointervARB */
        {  970,  972 }, /* glGetVertexAttribPointerv and glGetVertexAttribPointervNV */
        {  971,  970 }, /* glGetVertexAttribPointervARB and glGetVertexAttribPointerv */
        {  971,  972 }, /* glGetVertexAttribPointervARB and glGetVertexAttribPointervNV */
        {  972,  970 }, /* glGetVertexAttribPointervNV and glGetVertexAttribPointerv */
        {  972,  971 }, /* glGetVertexAttribPointervNV and glGetVertexAttribPointervARB */
        { 1051, 1052 }, /* glIsBuffer and glIsBufferARB */
        { 1052, 1051 }, /* glIsBufferARB and glIsBuffer */
        { 1057, 1056 }, /* glIsEnabledi and glIsEnabledIndexedEXT */
        { 1057, 2767 }, /* glIsEnabledi and glIsEnablediEXT */
        { 1057, 2768 }, /* glIsEnabledi and glIsEnablediNV */
        { 1057, 2769 }, /* glIsEnabledi and glIsEnablediOES */
        { 2767, 1056 }, /* glIsEnablediEXT and glIsEnabledIndexedEXT */
        { 2767, 1057 }, /* glIsEnablediEXT and glIsEnabledi */
        { 2767, 2768 }, /* glIsEnablediEXT and glIsEnablediNV */
        { 2767, 2769 }, /* glIsEnablediEXT and glIsEnablediOES */
        { 1056, 1057 }, /* glIsEnabledIndexedEXT and glIsEnabledi */
        { 1056, 2767 }, /* glIsEnabledIndexedEXT and glIsEnablediEXT */
        { 1056, 2768 }, /* glIsEnabledIndexedEXT and glIsEnablediNV */
        { 1056, 2769 }, /* glIsEnabledIndexedEXT and glIsEnablediOES */
        { 2768, 1056 }, /* glIsEnablediNV and glIsEnabledIndexedEXT */
        { 2768, 1057 }, /* glIsEnablediNV and glIsEnabledi */
        { 2768, 2767 }, /* glIsEnablediNV and glIsEnablediEXT */
        { 2768, 2769 }, /* glIsEnablediNV and glIsEnablediOES */
        { 2769, 1056 }, /* glIsEnablediOES and glIsEnabledIndexedEXT */
        { 2769, 1057 }, /* glIsEnablediOES and glIsEnabledi */
        { 2769, 2767 }, /* glIsEnablediOES and glIsEnablediEXT */
        { 2769, 2768 }, /* glIsEnablediOES and glIsEnablediNV */
        { 1060, 1061 }, /* glIsFramebuffer and glIsFramebufferEXT */
        { 1061, 1060 }, /* glIsFramebufferEXT and glIsFramebuffer */
        { 1074, 1075 }, /* glIsProgramARB and glIsProgramNV */
        { 1075, 1074 }, /* glIsProgramNV and glIsProgramARB */
        { 1077, 1078 }, /* glIsQuery and glIsQueryARB */
        { 1078, 1077 }, /* glIsQueryARB and glIsQuery */
        { 1079, 1080 }, /* glIsRenderbuffer and glIsRenderbufferEXT */
        { 1080, 1079 }, /* glIsRenderbufferEXT and glIsRenderbuffer */
        { 1085, 2772 }, /* glIsSync and glIsSyncAPPLE */
        { 2772, 1085 }, /* glIsSyncAPPLE and glIsSync */
        { 1090, 1091 }, /* glIsTransformFeedback and glIsTransformFeedbackNV */
        { 1091, 1090 }, /* glIsTransformFeedbackNV and glIsTransformFeedback */
        { 1093, 1094 }, /* glIsVertexArray and glIsVertexArrayAPPLE */
        { 1093, 2773 }, /* glIsVertexArray and glIsVertexArrayOES */
        { 1094, 1093 }, /* glIsVertexArrayAPPLE and glIsVertexArray */
        { 1094, 2773 }, /* glIsVertexArrayAPPLE and glIsVertexArrayOES */
        { 2773, 1093 }, /* glIsVertexArrayOES and glIsVertexArray */
        { 2773, 1094 }, /* glIsVertexArrayOES and glIsVertexArrayAPPLE */
        { 1107, 1108 }, /* glLinkProgram and glLinkProgramARB */
        { 1108, 1107 }, /* glLinkProgramARB and glLinkProgram */
        { 1121, 2775 }, /* glLogicOp and glLogicOpANGLE */
        { 2775, 1121 }, /* glLogicOpANGLE and glLogicOp */
        { 1136, 1137 }, /* glMapBuffer and glMapBufferARB */
        { 1136, 2779 }, /* glMapBuffer and glMapBufferOES */
        { 1137, 1136 }, /* glMapBufferARB and glMapBuffer */
        { 1137, 2779 }, /* glMapBufferARB and glMapBufferOES */
        { 2779, 1136 }, /* glMapBufferOES and glMapBuffer */
        { 2779, 1137 }, /* glMapBufferOES and glMapBufferARB */
        { 1138, 2780 }, /* glMapBufferRange and glMapBufferRangeEXT */
        { 2780, 1138 }, /* glMapBufferRangeEXT and glMapBufferRange */
        { 1185, 1186 }, /* glMaxShaderCompilerThreadsARB and glMaxShaderCompilerThreadsKHR */
        { 1186, 1185 }, /* glMaxShaderCompilerThreadsKHR and glMaxShaderCompilerThreadsARB */
        { 1187, 1189 }, /* glMemoryBarrier and glMemoryBarrierEXT */
        { 1189, 1187 }, /* glMemoryBarrierEXT and glMemoryBarrier */
        { 1191, 1192 }, /* glMinSampleShading and glMinSampleShadingARB */
        { 1191, 2782 }, /* glMinSampleShading and glMinSampleShadingOES */
        { 1192, 1191 }, /* glMinSampleShadingARB and glMinSampleShading */
        { 1192, 2782 }, /* glMinSampleShadingARB and glMinSampleShadingOES */
        { 2782, 1191 }, /* glMinSampleShadingOES and glMinSampleShading */
        { 2782, 1192 }, /* glMinSampleShadingOES and glMinSampleShadingARB */
        { 1198, 2783 }, /* glMultiDrawArrays and glMultiDrawArraysANGLE */
        { 1198, 1199 }, /* glMultiDrawArrays and glMultiDrawArraysEXT */
        { 2783, 1198 }, /* glMultiDrawArraysANGLE and glMultiDrawArrays */
        { 2783, 1199 }, /* glMultiDrawArraysANGLE and glMultiDrawArraysEXT */
        { 1199, 1198 }, /* glMultiDrawArraysEXT and glMultiDrawArrays */
        { 1199, 2783 }, /* glMultiDrawArraysEXT and glMultiDrawArraysANGLE */
        { 1200, 1201 }, /* glMultiDrawArraysIndirect and glMultiDrawArraysIndirectAMD */
        { 1200, 2784 }, /* glMultiDrawArraysIndirect and glMultiDrawArraysIndirectEXT */
        { 1201, 1200 }, /* glMultiDrawArraysIndirectAMD and glMultiDrawArraysIndirect */
        { 1201, 2784 }, /* glMultiDrawArraysIndirectAMD and glMultiDrawArraysIndirectEXT */
        { 1204, 1205 }, /* glMultiDrawArraysIndirectCount and glMultiDrawArraysIndirectCountARB */
        { 1205, 1204 }, /* glMultiDrawArraysIndirectCountARB and glMultiDrawArraysIndirectCount */
        { 2784, 1200 }, /* glMultiDrawArraysIndirectEXT and glMultiDrawArraysIndirect */
        { 2784, 1201 }, /* glMultiDrawArraysIndirectEXT and glMultiDrawArraysIndirectAMD */
        { 1207, 2787 }, /* glMultiDrawElements and glMultiDrawElementsANGLE */
        { 1207, 1209 }, /* glMultiDrawElements and glMultiDrawElementsEXT */
        { 2787, 1207 }, /* glMultiDrawElementsANGLE and glMultiDrawElements */
        { 2787, 1209 }, /* glMultiDrawElementsANGLE and glMultiDrawElementsEXT */
        { 1208, 2788 }, /* glMultiDrawElementsBaseVertex and glMultiDrawElementsBaseVertexEXT */
        { 2788, 1208 }, /* glMultiDrawElementsBaseVertexEXT and glMultiDrawElementsBaseVertex */
        { 1209, 1207 }, /* glMultiDrawElementsEXT and glMultiDrawElements */
        { 1209, 2787 }, /* glMultiDrawElementsEXT and glMultiDrawElementsANGLE */
        { 1210, 1211 }, /* glMultiDrawElementsIndirect and glMultiDrawElementsIndirectAMD */
        { 1210, 2789 }, /* glMultiDrawElementsIndirect and glMultiDrawElementsIndirectEXT */
        { 1211, 1210 }, /* glMultiDrawElementsIndirectAMD and glMultiDrawElementsIndirect */
        { 1211, 2789 }, /* glMultiDrawElementsIndirectAMD and glMultiDrawElementsIndirectEXT */
        { 1214, 1215 }, /* glMultiDrawElementsIndirectCount and glMultiDrawElementsIndirectCountARB */
        { 1215, 1214 }, /* glMultiDrawElementsIndirectCountARB and glMultiDrawElementsIndirectCount */
        { 2789, 1210 }, /* glMultiDrawElementsIndirectEXT and glMultiDrawElementsIndirect */
        { 2789, 1211 }, /* glMultiDrawElementsIndirectEXT and glMultiDrawElementsIndirectAMD */
        { 1322, 1323 }, /* glNamedBufferStorage and glNamedBufferStorageEXT */
        { 1323, 1322 }, /* glNamedBufferStorageEXT and glNamedBufferStorage */
        { 1326, 1327 }, /* glNamedBufferSubData and glNamedBufferSubDataEXT */
        { 1327, 1326 }, /* glNamedBufferSubDataEXT and glNamedBufferSubData */
        { 1388, 2792 }, /* glObjectLabel and glObjectLabelKHR */
        { 2792, 1388 }, /* glObjectLabelKHR and glObjectLabel */
        { 1389, 2793 }, /* glObjectPtrLabel and glObjectPtrLabelKHR */
        { 2793, 1389 }, /* glObjectPtrLabelKHR and glObjectPtrLabel */
        { 1399, 2794 }, /* glPatchParameteri and glPatchParameteriEXT */
        { 1399, 2795 }, /* glPatchParameteri and glPatchParameteriOES */
        { 2794, 1399 }, /* glPatchParameteriEXT and glPatchParameteri */
        { 2794, 2795 }, /* glPatchParameteriEXT and glPatchParameteriOES */
        { 2795, 1399 }, /* glPatchParameteriOES and glPatchParameteri */
        { 2795, 2794 }, /* glPatchParameteriOES and glPatchParameteriEXT */
        { 1418, 1419 }, /* glPauseTransformFeedback and glPauseTransformFeedbackNV */
        { 1419, 1418 }, /* glPauseTransformFeedbackNV and glPauseTransformFeedback */
        { 1437, 1438 }, /* glPointParameterf and glPointParameterfARB */
        { 1437, 1439 }, /* glPointParameterf and glPointParameterfEXT */
        { 1437, 1440 }, /* glPointParameterf and glPointParameterfSGIS */
        { 1438, 1437 }, /* glPointParameterfARB and glPointParameterf */
        { 1438, 1439 }, /* glPointParameterfARB and glPointParameterfEXT */
        { 1438, 1440 }, /* glPointParameterfARB and glPointParameterfSGIS */
        { 1439, 1437 }, /* glPointParameterfEXT and glPointParameterf */
        { 1439, 1438 }, /* glPointParameterfEXT and glPointParameterfARB */
        { 1439, 1440 }, /* glPointParameterfEXT and glPointParameterfSGIS */
        { 1440, 1437 }, /* glPointParameterfSGIS and glPointParameterf */
        { 1440, 1438 }, /* glPointParameterfSGIS and glPointParameterfARB */
        { 1440, 1439 }, /* glPointParameterfSGIS and glPointParameterfEXT */
        { 1441, 1442 }, /* glPointParameterfv and glPointParameterfvARB */
        { 1441, 1443 }, /* glPointParameterfv and glPointParameterfvEXT */
        { 1441, 1444 }, /* glPointParameterfv and glPointParameterfvSGIS */
        { 1442, 1441 }, /* glPointParameterfvARB and glPointParameterfv */
        { 1442, 1443 }, /* glPointParameterfvARB and glPointParameterfvEXT */
        { 1442, 1444 }, /* glPointParameterfvARB and glPointParameterfvSGIS */
        { 1443, 1441 }, /* glPointParameterfvEXT and glPointParameterfv */
        { 1443, 1442 }, /* glPointParameterfvEXT and glPointParameterfvARB */
        { 1443, 1444 }, /* glPointParameterfvEXT and glPointParameterfvSGIS */
        { 1444, 1441 }, /* glPointParameterfvSGIS and glPointParameterfv */
        { 1444, 1442 }, /* glPointParameterfvSGIS and glPointParameterfvARB */
        { 1444, 1443 }, /* glPointParameterfvSGIS and glPointParameterfvEXT */
        { 1445, 1446 }, /* glPointParameteri and glPointParameteriNV */
        { 1446, 1445 }, /* glPointParameteriNV and glPointParameteri */
        { 1447, 1448 }, /* glPointParameteriv and glPointParameterivNV */
        { 1448, 1447 }, /* glPointParameterivNV and glPointParameteriv */
        { 1454, 2798 }, /* glPolygonMode and glPolygonModeNV */
        { 2798, 1454 }, /* glPolygonModeNV and glPolygonMode */
        { 1456, 1457 }, /* glPolygonOffsetClamp and glPolygonOffsetClampEXT */
        { 1457, 1456 }, /* glPolygonOffsetClampEXT and glPolygonOffsetClamp */
        { 1460, 2799 }, /* glPopDebugGroup and glPopDebugGroupKHR */
        { 2799, 1460 }, /* glPopDebugGroupKHR and glPopDebugGroup */
        { 2800, 1464 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxARB */
        { 2800, 2801 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxEXT */
        { 2800, 2802 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxOES */
        { 1464, 2800 }, /* glPrimitiveBoundingBoxARB and glPrimitiveBoundingBox */
        { 1464, 2801 }, /* glPrimitiveBoundingBoxARB and glPrimitiveBoundingBoxEXT */
        { 1464, 2802 }, /* glPrimitiveBoundingBoxARB and glPrimitiveBoundingBoxOES */
        { 2801, 2800 }, /* glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBox */
        { 2801, 1464 }, /* glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBoxARB */
        { 2801, 2802 }, /* glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBoxOES */
        { 2802, 2800 }, /* glPrimitiveBoundingBoxOES and glPrimitiveBoundingBox */
        { 2802, 1464 }, /* glPrimitiveBoundingBoxOES and glPrimitiveBoundingBoxARB */
        { 2802, 2801 }, /* glPrimitiveBoundingBoxOES and glPrimitiveBoundingBoxEXT */
        { 1470, 2803 }, /* glProgramBinary and glProgramBinaryOES */
        { 2803, 1470 }, /* glProgramBinaryOES and glProgramBinary */
        { 1504, 1505 }, /* glProgramParameteri and glProgramParameteriARB */
        { 1504, 1506 }, /* glProgramParameteri and glProgramParameteriEXT */
        { 1505, 1504 }, /* glProgramParameteriARB and glProgramParameteri */
        { 1505, 1506 }, /* glProgramParameteriARB and glProgramParameteriEXT */
        { 1506, 1504 }, /* glProgramParameteriEXT and glProgramParameteri */
        { 1506, 1505 }, /* glProgramParameteriEXT and glProgramParameteriARB */
        { 1516, 1517 }, /* glProgramUniform1f and glProgramUniform1fEXT */
        { 1517, 1516 }, /* glProgramUniform1fEXT and glProgramUniform1f */
        { 1518, 1519 }, /* glProgramUniform1fv and glProgramUniform1fvEXT */
        { 1519, 1518 }, /* glProgramUniform1fvEXT and glProgramUniform1fv */
        { 1520, 1525 }, /* glProgramUniform1i and glProgramUniform1iEXT */
        { 1525, 1520 }, /* glProgramUniform1iEXT and glProgramUniform1i */
        { 1526, 1527 }, /* glProgramUniform1iv and glProgramUniform1ivEXT */
        { 1527, 1526 }, /* glProgramUniform1ivEXT and glProgramUniform1iv */
        { 1528, 1533 }, /* glProgramUniform1ui and glProgramUniform1uiEXT */
        { 1533, 1528 }, /* glProgramUniform1uiEXT and glProgramUniform1ui */
        { 1534, 1535 }, /* glProgramUniform1uiv and glProgramUniform1uivEXT */
        { 1535, 1534 }, /* glProgramUniform1uivEXT and glProgramUniform1uiv */
        { 1540, 1541 }, /* glProgramUniform2f and glProgramUniform2fEXT */
        { 1541, 1540 }, /* glProgramUniform2fEXT and glProgramUniform2f */
        { 1542, 1543 }, /* glProgramUniform2fv and glProgramUniform2fvEXT */
        { 1543, 1542 }, /* glProgramUniform2fvEXT and glProgramUniform2fv */
        { 1544, 1549 }, /* glProgramUniform2i and glProgramUniform2iEXT */
        { 1549, 1544 }, /* glProgramUniform2iEXT and glProgramUniform2i */
        { 1550, 1551 }, /* glProgramUniform2iv and glProgramUniform2ivEXT */
        { 1551, 1550 }, /* glProgramUniform2ivEXT and glProgramUniform2iv */
        { 1552, 1557 }, /* glProgramUniform2ui and glProgramUniform2uiEXT */
        { 1557, 1552 }, /* glProgramUniform2uiEXT and glProgramUniform2ui */
        { 1558, 1559 }, /* glProgramUniform2uiv and glProgramUniform2uivEXT */
        { 1559, 1558 }, /* glProgramUniform2uivEXT and glProgramUniform2uiv */
        { 1564, 1565 }, /* glProgramUniform3f and glProgramUniform3fEXT */
        { 1565, 1564 }, /* glProgramUniform3fEXT and glProgramUniform3f */
        { 1566, 1567 }, /* glProgramUniform3fv and glProgramUniform3fvEXT */
        { 1567, 1566 }, /* glProgramUniform3fvEXT and glProgramUniform3fv */
        { 1568, 1573 }, /* glProgramUniform3i and glProgramUniform3iEXT */
        { 1573, 1568 }, /* glProgramUniform3iEXT and glProgramUniform3i */
        { 1574, 1575 }, /* glProgramUniform3iv and glProgramUniform3ivEXT */
        { 1575, 1574 }, /* glProgramUniform3ivEXT and glProgramUniform3iv */
        { 1576, 1581 }, /* glProgramUniform3ui and glProgramUniform3uiEXT */
        { 1581, 1576 }, /* glProgramUniform3uiEXT and glProgramUniform3ui */
        { 1582, 1583 }, /* glProgramUniform3uiv and glProgramUniform3uivEXT */
        { 1583, 1582 }, /* glProgramUniform3uivEXT and glProgramUniform3uiv */
        { 1588, 1589 }, /* glProgramUniform4f and glProgramUniform4fEXT */
        { 1589, 1588 }, /* glProgramUniform4fEXT and glProgramUniform4f */
        { 1590, 1591 }, /* glProgramUniform4fv and glProgramUniform4fvEXT */
        { 1591, 1590 }, /* glProgramUniform4fvEXT and glProgramUniform4fv */
        { 1592, 1597 }, /* glProgramUniform4i and glProgramUniform4iEXT */
        { 1597, 1592 }, /* glProgramUniform4iEXT and glProgramUniform4i */
        { 1598, 1599 }, /* glProgramUniform4iv and glProgramUniform4ivEXT */
        { 1599, 1598 }, /* glProgramUniform4ivEXT and glProgramUniform4iv */
        { 1600, 1605 }, /* glProgramUniform4ui and glProgramUniform4uiEXT */
        { 1605, 1600 }, /* glProgramUniform4uiEXT and glProgramUniform4ui */
        { 1606, 1607 }, /* glProgramUniform4uiv and glProgramUniform4uivEXT */
        { 1607, 1606 }, /* glProgramUniform4uivEXT and glProgramUniform4uiv */
        { 1608, 2804 }, /* glProgramUniformHandleui64ARB and glProgramUniformHandleui64IMG */
        { 2804, 1608 }, /* glProgramUniformHandleui64IMG and glProgramUniformHandleui64ARB */
        { 1610, 2805 }, /* glProgramUniformHandleui64vARB and glProgramUniformHandleui64vIMG */
        { 2805, 1610 }, /* glProgramUniformHandleui64vIMG and glProgramUniformHandleui64vARB */
        { 1614, 1615 }, /* glProgramUniformMatrix2fv and glProgramUniformMatrix2fvEXT */
        { 1615, 1614 }, /* glProgramUniformMatrix2fvEXT and glProgramUniformMatrix2fv */
        { 1618, 1619 }, /* glProgramUniformMatrix2x3fv and glProgramUniformMatrix2x3fvEXT */
        { 1619, 1618 }, /* glProgramUniformMatrix2x3fvEXT and glProgramUniformMatrix2x3fv */
        { 1622, 1623 }, /* glProgramUniformMatrix2x4fv and glProgramUniformMatrix2x4fvEXT */
        { 1623, 1622 }, /* glProgramUniformMatrix2x4fvEXT and glProgramUniformMatrix2x4fv */
        { 1626, 1627 }, /* glProgramUniformMatrix3fv and glProgramUniformMatrix3fvEXT */
        { 1627, 1626 }, /* glProgramUniformMatrix3fvEXT and glProgramUniformMatrix3fv */
        { 1630, 1631 }, /* glProgramUniformMatrix3x2fv and glProgramUniformMatrix3x2fvEXT */
        { 1631, 1630 }, /* glProgramUniformMatrix3x2fvEXT and glProgramUniformMatrix3x2fv */
        { 1634, 1635 }, /* glProgramUniformMatrix3x4fv and glProgramUniformMatrix3x4fvEXT */
        { 1635, 1634 }, /* glProgramUniformMatrix3x4fvEXT and glProgramUniformMatrix3x4fv */
        { 1638, 1639 }, /* glProgramUniformMatrix4fv and glProgramUniformMatrix4fvEXT */
        { 1639, 1638 }, /* glProgramUniformMatrix4fvEXT and glProgramUniformMatrix4fv */
        { 1642, 1643 }, /* glProgramUniformMatrix4x2fv and glProgramUniformMatrix4x2fvEXT */
        { 1643, 1642 }, /* glProgramUniformMatrix4x2fvEXT and glProgramUniformMatrix4x2fv */
        { 1646, 1647 }, /* glProgramUniformMatrix4x3fv and glProgramUniformMatrix4x3fvEXT */
        { 1647, 1646 }, /* glProgramUniformMatrix4x3fvEXT and glProgramUniformMatrix4x3fv */
        { 1651, 2806 }, /* glProvokingVertex and glProvokingVertexANGLE */
        { 1651, 1652 }, /* glProvokingVertex and glProvokingVertexEXT */
        { 2806, 1651 }, /* glProvokingVertexANGLE and glProvokingVertex */
        { 2806, 1652 }, /* glProvokingVertexANGLE and glProvokingVertexEXT */
        { 1652, 1651 }, /* glProvokingVertexEXT and glProvokingVertex */
        { 1652, 2806 }, /* glProvokingVertexEXT and glProvokingVertexANGLE */
        { 1654, 2807 }, /* glPushDebugGroup and glPushDebugGroupKHR */
        { 2807, 1654 }, /* glPushDebugGroupKHR and glPushDebugGroup */
        { 1656, 2808 }, /* glQueryCounter and glQueryCounterEXT */
        { 2808, 1656 }, /* glQueryCounterEXT and glQueryCounter */
        { 1671, 1672 }, /* glReadnPixels and glReadnPixelsARB */
        { 1671, 2812 }, /* glReadnPixels and glReadnPixelsEXT */
        { 1671, 2813 }, /* glReadnPixels and glReadnPixelsKHR */
        { 1672, 1671 }, /* glReadnPixelsARB and glReadnPixels */
        { 1672, 2812 }, /* glReadnPixelsARB and glReadnPixelsEXT */
        { 1672, 2813 }, /* glReadnPixelsARB and glReadnPixelsKHR */
        { 2812, 1671 }, /* glReadnPixelsEXT and glReadnPixels */
        { 2812, 1672 }, /* glReadnPixelsEXT and glReadnPixelsARB */
        { 2812, 2813 }, /* glReadnPixelsEXT and glReadnPixelsKHR */
        { 2813, 1671 }, /* glReadnPixelsKHR and glReadnPixels */
        { 2813, 1672 }, /* glReadnPixelsKHR and glReadnPixelsARB */
        { 2813, 2812 }, /* glReadnPixelsKHR and glReadnPixelsEXT */
        { 1679, 1680 }, /* glRenderbufferStorage and glRenderbufferStorageEXT */
        { 1680, 1679 }, /* glRenderbufferStorageEXT and glRenderbufferStorage */
        { 1681, 1684 }, /* glRenderbufferStorageMultisample and glRenderbufferStorageMultisampleEXT */
        { 1681, 2819 }, /* glRenderbufferStorageMultisample and glRenderbufferStorageMultisampleNV */
        { 1684, 1681 }, /* glRenderbufferStorageMultisampleEXT and glRenderbufferStorageMultisample */
        { 1684, 2819 }, /* glRenderbufferStorageMultisampleEXT and glRenderbufferStorageMultisampleNV */
        { 2819, 1681 }, /* glRenderbufferStorageMultisampleNV and glRenderbufferStorageMultisample */
        { 2819, 1684 }, /* glRenderbufferStorageMultisampleNV and glRenderbufferStorageMultisampleEXT */
        { 1714, 1715 }, /* glResumeTransformFeedback and glResumeTransformFeedbackNV */
        { 1715, 1714 }, /* glResumeTransformFeedbackNV and glResumeTransformFeedback */
        { 1717, 1718 }, /* glSampleCoverage and glSampleCoverageARB */
        { 1718, 1717 }, /* glSampleCoverageARB and glSampleCoverage */
        { 1720, 1722 }, /* glSampleMaskEXT and glSampleMaskSGIS */
        { 1723, 2822 }, /* glSampleMaski and glSampleMaskiANGLE */
        { 2822, 1723 }, /* glSampleMaskiANGLE and glSampleMaski */
        { 1722, 1720 }, /* glSampleMaskSGIS and glSampleMaskEXT */
        { 1724, 1725 }, /* glSamplePatternEXT and glSamplePatternSGIS */
        { 1725, 1724 }, /* glSamplePatternSGIS and glSamplePatternEXT */
        { 1726, 2823 }, /* glSamplerParameterIiv and glSamplerParameterIivEXT */
        { 1726, 2824 }, /* glSamplerParameterIiv and glSamplerParameterIivOES */
        { 2823, 1726 }, /* glSamplerParameterIivEXT and glSamplerParameterIiv */
        { 2823, 2824 }, /* glSamplerParameterIivEXT and glSamplerParameterIivOES */
        { 2824, 1726 }, /* glSamplerParameterIivOES and glSamplerParameterIiv */
        { 2824, 2823 }, /* glSamplerParameterIivOES and glSamplerParameterIivEXT */
        { 1727, 2826 }, /* glSamplerParameterIuiv and glSamplerParameterIuivEXT */
        { 1727, 2827 }, /* glSamplerParameterIuiv and glSamplerParameterIuivOES */
        { 2826, 1727 }, /* glSamplerParameterIuivEXT and glSamplerParameterIuiv */
        { 2826, 2827 }, /* glSamplerParameterIuivEXT and glSamplerParameterIuivOES */
        { 2827, 1727 }, /* glSamplerParameterIuivOES and glSamplerParameterIuiv */
        { 2827, 2826 }, /* glSamplerParameterIuivOES and glSamplerParameterIuivEXT */
        { 1734, 2831 }, /* glScissorArrayv and glScissorArrayvNV */
        { 1734, 2832 }, /* glScissorArrayv and glScissorArrayvOES */
        { 2831, 1734 }, /* glScissorArrayvNV and glScissorArrayv */
        { 2831, 2832 }, /* glScissorArrayvNV and glScissorArrayvOES */
        { 2832, 1734 }, /* glScissorArrayvOES and glScissorArrayv */
        { 2832, 2831 }, /* glScissorArrayvOES and glScissorArrayvNV */
        { 1737, 2833 }, /* glScissorIndexed and glScissorIndexedNV */
        { 1737, 2834 }, /* glScissorIndexed and glScissorIndexedOES */
        { 2833, 1737 }, /* glScissorIndexedNV and glScissorIndexed */
        { 2833, 2834 }, /* glScissorIndexedNV and glScissorIndexedOES */
        { 2834, 1737 }, /* glScissorIndexedOES and glScissorIndexed */
        { 2834, 2833 }, /* glScissorIndexedOES and glScissorIndexedNV */
        { 1738, 2835 }, /* glScissorIndexedv and glScissorIndexedvNV */
        { 1738, 2836 }, /* glScissorIndexedv and glScissorIndexedvOES */
        { 2835, 1738 }, /* glScissorIndexedvNV and glScissorIndexedv */
        { 2835, 2836 }, /* glScissorIndexedvNV and glScissorIndexedvOES */
        { 2836, 1738 }, /* glScissorIndexedvOES and glScissorIndexedv */
        { 2836, 2835 }, /* glScissorIndexedvOES and glScissorIndexedvNV */
        { 1774, 1775 }, /* glShaderSource and glShaderSourceARB */
        { 1775, 1774 }, /* glShaderSourceARB and glShaderSource */
        { 1786, 1787 }, /* glSpecializeShader and glSpecializeShaderARB */
        { 1787, 1786 }, /* glSpecializeShaderARB and glSpecializeShader */
        { 1803, 1804 }, /* glStencilOpSeparate and glStencilOpSeparateATI */
        { 1804, 1803 }, /* glStencilOpSeparateATI and glStencilOpSeparate */
        { 1836, 1837 }, /* glTexBuffer and glTexBufferARB */
        { 1836, 1838 }, /* glTexBuffer and glTexBufferEXT */
        { 1836, 2841 }, /* glTexBuffer and glTexBufferOES */
        { 1837, 1836 }, /* glTexBufferARB and glTexBuffer */
        { 1837, 1838 }, /* glTexBufferARB and glTexBufferEXT */
        { 1837, 2841 }, /* glTexBufferARB and glTexBufferOES */
        { 1838, 1836 }, /* glTexBufferEXT and glTexBuffer */
        { 1838, 1837 }, /* glTexBufferEXT and glTexBufferARB */
        { 1838, 2841 }, /* glTexBufferEXT and glTexBufferOES */
        { 2841, 1836 }, /* glTexBufferOES and glTexBuffer */
        { 2841, 1837 }, /* glTexBufferOES and glTexBufferARB */
        { 2841, 1838 }, /* glTexBufferOES and glTexBufferEXT */
        { 1839, 2842 }, /* glTexBufferRange and glTexBufferRangeEXT */
        { 1839, 2843 }, /* glTexBufferRange and glTexBufferRangeOES */
        { 2842, 1839 }, /* glTexBufferRangeEXT and glTexBufferRange */
        { 2842, 2843 }, /* glTexBufferRangeEXT and glTexBufferRangeOES */
        { 2843, 1839 }, /* glTexBufferRangeOES and glTexBufferRange */
        { 2843, 2842 }, /* glTexBufferRangeOES and glTexBufferRangeEXT */
        { 1894, 1895 }, /* glTexImage3D and glTexImage3DEXT */
        { 1895, 1894 }, /* glTexImage3DEXT and glTexImage3D */
        { 1899, 2849 }, /* glTexPageCommitmentARB and glTexPageCommitmentEXT */
        { 2849, 1899 }, /* glTexPageCommitmentEXT and glTexPageCommitmentARB */
        { 1901, 1902 }, /* glTexParameterIiv and glTexParameterIivEXT */
        { 1901, 2850 }, /* glTexParameterIiv and glTexParameterIivOES */
        { 1902, 1901 }, /* glTexParameterIivEXT and glTexParameterIiv */
        { 1902, 2850 }, /* glTexParameterIivEXT and glTexParameterIivOES */
        { 2850, 1901 }, /* glTexParameterIivOES and glTexParameterIiv */
        { 2850, 1902 }, /* glTexParameterIivOES and glTexParameterIivEXT */
        { 1903, 1904 }, /* glTexParameterIuiv and glTexParameterIuivEXT */
        { 1903, 2852 }, /* glTexParameterIuiv and glTexParameterIuivOES */
        { 1904, 1903 }, /* glTexParameterIuivEXT and glTexParameterIuiv */
        { 1904, 2852 }, /* glTexParameterIuivEXT and glTexParameterIuivOES */
        { 2852, 1903 }, /* glTexParameterIuivOES and glTexParameterIuiv */
        { 2852, 1904 }, /* glTexParameterIuivOES and glTexParameterIuivEXT */
        { 1912, 1913 }, /* glTexStorage1D and glTexStorage1DEXT */
        { 1913, 1912 }, /* glTexStorage1DEXT and glTexStorage1D */
        { 1914, 1915 }, /* glTexStorage2D and glTexStorage2DEXT */
        { 1915, 1914 }, /* glTexStorage2DEXT and glTexStorage2D */
        { 1916, 2856 }, /* glTexStorage2DMultisample and glTexStorage2DMultisampleANGLE */
        { 2856, 1916 }, /* glTexStorage2DMultisampleANGLE and glTexStorage2DMultisample */
        { 1917, 1918 }, /* glTexStorage3D and glTexStorage3DEXT */
        { 1918, 1917 }, /* glTexStorage3DEXT and glTexStorage3D */
        { 1919, 2857 }, /* glTexStorage3DMultisample and glTexStorage3DMultisampleOES */
        { 2857, 1919 }, /* glTexStorage3DMultisampleOES and glTexStorage3DMultisample */
        { 1930, 1931 }, /* glTexSubImage1D and glTexSubImage1DEXT */
        { 1931, 1930 }, /* glTexSubImage1DEXT and glTexSubImage1D */
        { 1932, 1933 }, /* glTexSubImage2D and glTexSubImage2DEXT */
        { 1933, 1932 }, /* glTexSubImage2DEXT and glTexSubImage2D */
        { 1934, 1935 }, /* glTexSubImage3D and glTexSubImage3DEXT */
        { 1935, 1934 }, /* glTexSubImage3DEXT and glTexSubImage3D */
        { 1993, 2864 }, /* glTextureView and glTextureViewEXT */
        { 1993, 2865 }, /* glTextureView and glTextureViewOES */
        { 2864, 1993 }, /* glTextureViewEXT and glTextureView */
        { 2864, 2865 }, /* glTextureViewEXT and glTextureViewOES */
        { 2865, 1993 }, /* glTextureViewOES and glTextureView */
        { 2865, 2864 }, /* glTextureViewOES and glTextureViewEXT */
        { 1999, 2000 }, /* glTransformFeedbackVaryings and glTransformFeedbackVaryingsEXT */
        { 2000, 1999 }, /* glTransformFeedbackVaryingsEXT and glTransformFeedbackVaryings */
        { 2006, 2007 }, /* glUniform1f and glUniform1fARB */
        { 2007, 2006 }, /* glUniform1fARB and glUniform1f */
        { 2008, 2009 }, /* glUniform1fv and glUniform1fvARB */
        { 2009, 2008 }, /* glUniform1fvARB and glUniform1fv */
        { 2010, 2015 }, /* glUniform1i and glUniform1iARB */
        { 2015, 2010 }, /* glUniform1iARB and glUniform1i */
        { 2016, 2017 }, /* glUniform1iv and glUniform1ivARB */
        { 2017, 2016 }, /* glUniform1ivARB and glUniform1iv */
        { 2018, 2023 }, /* glUniform1ui and glUniform1uiEXT */
        { 2023, 2018 }, /* glUniform1uiEXT and glUniform1ui */
        { 2024, 2025 }, /* glUniform1uiv and glUniform1uivEXT */
        { 2025, 2024 }, /* glUniform1uivEXT and glUniform1uiv */
        { 2028, 2029 }, /* glUniform2f and glUniform2fARB */
        { 2029, 2028 }, /* glUniform2fARB and glUniform2f */
        { 2030, 2031 }, /* glUniform2fv and glUniform2fvARB */
        { 2031, 2030 }, /* glUniform2fvARB and glUniform2fv */
        { 2032, 2037 }, /* glUniform2i and glUniform2iARB */
        { 2037, 2032 }, /* glUniform2iARB and glUniform2i */
        { 2038, 2039 }, /* glUniform2iv and glUniform2ivARB */
        { 2039, 2038 }, /* glUniform2ivARB and glUniform2iv */
        { 2040, 2045 }, /* glUniform2ui and glUniform2uiEXT */
        { 2045, 2040 }, /* glUniform2uiEXT and glUniform2ui */
        { 2046, 2047 }, /* glUniform2uiv and glUniform2uivEXT */
        { 2047, 2046 }, /* glUniform2uivEXT and glUniform2uiv */
        { 2050, 2051 }, /* glUniform3f and glUniform3fARB */
        { 2051, 2050 }, /* glUniform3fARB and glUniform3f */
        { 2052, 2053 }, /* glUniform3fv and glUniform3fvARB */
        { 2053, 2052 }, /* glUniform3fvARB and glUniform3fv */
        { 2054, 2059 }, /* glUniform3i and glUniform3iARB */
        { 2059, 2054 }, /* glUniform3iARB and glUniform3i */
        { 2060, 2061 }, /* glUniform3iv and glUniform3ivARB */
        { 2061, 2060 }, /* glUniform3ivARB and glUniform3iv */
        { 2062, 2067 }, /* glUniform3ui and glUniform3uiEXT */
        { 2067, 2062 }, /* glUniform3uiEXT and glUniform3ui */
        { 2068, 2069 }, /* glUniform3uiv and glUniform3uivEXT */
        { 2069, 2068 }, /* glUniform3uivEXT and glUniform3uiv */
        { 2072, 2073 }, /* glUniform4f and glUniform4fARB */
        { 2073, 2072 }, /* glUniform4fARB and glUniform4f */
        { 2074, 2075 }, /* glUniform4fv and glUniform4fvARB */
        { 2075, 2074 }, /* glUniform4fvARB and glUniform4fv */
        { 2076, 2081 }, /* glUniform4i and glUniform4iARB */
        { 2081, 2076 }, /* glUniform4iARB and glUniform4i */
        { 2082, 2083 }, /* glUniform4iv and glUniform4ivARB */
        { 2083, 2082 }, /* glUniform4ivARB and glUniform4iv */
        { 2084, 2089 }, /* glUniform4ui and glUniform4uiEXT */
        { 2089, 2084 }, /* glUniform4uiEXT and glUniform4ui */
        { 2090, 2091 }, /* glUniform4uiv and glUniform4uivEXT */
        { 2091, 2090 }, /* glUniform4uivEXT and glUniform4uiv */
        { 2094, 2866 }, /* glUniformHandleui64ARB and glUniformHandleui64IMG */
        { 2866, 2094 }, /* glUniformHandleui64IMG and glUniformHandleui64ARB */
        { 2096, 2867 }, /* glUniformHandleui64vARB and glUniformHandleui64vIMG */
        { 2867, 2096 }, /* glUniformHandleui64vIMG and glUniformHandleui64vARB */
        { 2099, 2100 }, /* glUniformMatrix2fv and glUniformMatrix2fvARB */
        { 2100, 2099 }, /* glUniformMatrix2fvARB and glUniformMatrix2fv */
        { 2102, 2868 }, /* glUniformMatrix2x3fv and glUniformMatrix2x3fvNV */
        { 2868, 2102 }, /* glUniformMatrix2x3fvNV and glUniformMatrix2x3fv */
        { 2104, 2869 }, /* glUniformMatrix2x4fv and glUniformMatrix2x4fvNV */
        { 2869, 2104 }, /* glUniformMatrix2x4fvNV and glUniformMatrix2x4fv */
        { 2106, 2107 }, /* glUniformMatrix3fv and glUniformMatrix3fvARB */
        { 2107, 2106 }, /* glUniformMatrix3fvARB and glUniformMatrix3fv */
        { 2109, 2870 }, /* glUniformMatrix3x2fv and glUniformMatrix3x2fvNV */
        { 2870, 2109 }, /* glUniformMatrix3x2fvNV and glUniformMatrix3x2fv */
        { 2111, 2871 }, /* glUniformMatrix3x4fv and glUniformMatrix3x4fvNV */
        { 2871, 2111 }, /* glUniformMatrix3x4fvNV and glUniformMatrix3x4fv */
        { 2113, 2114 }, /* glUniformMatrix4fv and glUniformMatrix4fvARB */
        { 2114, 2113 }, /* glUniformMatrix4fvARB and glUniformMatrix4fv */
        { 2116, 2872 }, /* glUniformMatrix4x2fv and glUniformMatrix4x2fvNV */
        { 2872, 2116 }, /* glUniformMatrix4x2fvNV and glUniformMatrix4x2fv */
        { 2118, 2873 }, /* glUniformMatrix4x3fv and glUniformMatrix4x3fvNV */
        { 2873, 2118 }, /* glUniformMatrix4x3fvNV and glUniformMatrix4x3fv */
        { 2123, 2124 }, /* glUnmapBuffer and glUnmapBufferARB */
        { 2123, 2874 }, /* glUnmapBuffer and glUnmapBufferOES */
        { 2124, 2123 }, /* glUnmapBufferARB and glUnmapBuffer */
        { 2124, 2874 }, /* glUnmapBufferARB and glUnmapBufferOES */
        { 2874, 2123 }, /* glUnmapBufferOES and glUnmapBuffer */
        { 2874, 2124 }, /* glUnmapBufferOES and glUnmapBufferARB */
        { 2131, 2132 }, /* glUseProgram and glUseProgramObjectARB */
        { 2132, 2131 }, /* glUseProgramObjectARB and glUseProgram */
        { 2146, 2147 }, /* glValidateProgram and glValidateProgramARB */
        { 2147, 2146 }, /* glValidateProgramARB and glValidateProgram */
        { 2207, 2208 }, /* glVertexAttrib1d and glVertexAttrib1dARB */
        { 2207, 2209 }, /* glVertexAttrib1d and glVertexAttrib1dNV */
        { 2208, 2207 }, /* glVertexAttrib1dARB and glVertexAttrib1d */
        { 2208, 2209 }, /* glVertexAttrib1dARB and glVertexAttrib1dNV */
        { 2209, 2207 }, /* glVertexAttrib1dNV and glVertexAttrib1d */
        { 2209, 2208 }, /* glVertexAttrib1dNV and glVertexAttrib1dARB */
        { 2210, 2211 }, /* glVertexAttrib1dv and glVertexAttrib1dvARB */
        { 2210, 2212 }, /* glVertexAttrib1dv and glVertexAttrib1dvNV */
        { 2211, 2210 }, /* glVertexAttrib1dvARB and glVertexAttrib1dv */
        { 2211, 2212 }, /* glVertexAttrib1dvARB and glVertexAttrib1dvNV */
        { 2212, 2210 }, /* glVertexAttrib1dvNV and glVertexAttrib1dv */
        { 2212, 2211 }, /* glVertexAttrib1dvNV and glVertexAttrib1dvARB */
        { 2213, 2214 }, /* glVertexAttrib1f and glVertexAttrib1fARB */
        { 2213, 2215 }, /* glVertexAttrib1f and glVertexAttrib1fNV */
        { 2214, 2213 }, /* glVertexAttrib1fARB and glVertexAttrib1f */
        { 2214, 2215 }, /* glVertexAttrib1fARB and glVertexAttrib1fNV */
        { 2215, 2213 }, /* glVertexAttrib1fNV and glVertexAttrib1f */
        { 2215, 2214 }, /* glVertexAttrib1fNV and glVertexAttrib1fARB */
        { 2216, 2217 }, /* glVertexAttrib1fv and glVertexAttrib1fvARB */
        { 2216, 2218 }, /* glVertexAttrib1fv and glVertexAttrib1fvNV */
        { 2217, 2216 }, /* glVertexAttrib1fvARB and glVertexAttrib1fv */
        { 2217, 2218 }, /* glVertexAttrib1fvARB and glVertexAttrib1fvNV */
        { 2218, 2216 }, /* glVertexAttrib1fvNV and glVertexAttrib1fv */
        { 2218, 2217 }, /* glVertexAttrib1fvNV and glVertexAttrib1fvARB */
        { 2221, 2222 }, /* glVertexAttrib1s and glVertexAttrib1sARB */
        { 2221, 2223 }, /* glVertexAttrib1s and glVertexAttrib1sNV */
        { 2222, 2221 }, /* glVertexAttrib1sARB and glVertexAttrib1s */
        { 2222, 2223 }, /* glVertexAttrib1sARB and glVertexAttrib1sNV */
        { 2223, 2221 }, /* glVertexAttrib1sNV and glVertexAttrib1s */
        { 2223, 2222 }, /* glVertexAttrib1sNV and glVertexAttrib1sARB */
        { 2224, 2225 }, /* glVertexAttrib1sv and glVertexAttrib1svARB */
        { 2224, 2226 }, /* glVertexAttrib1sv and glVertexAttrib1svNV */
        { 2225, 2224 }, /* glVertexAttrib1svARB and glVertexAttrib1sv */
        { 2225, 2226 }, /* glVertexAttrib1svARB and glVertexAttrib1svNV */
        { 2226, 2224 }, /* glVertexAttrib1svNV and glVertexAttrib1sv */
        { 2226, 2225 }, /* glVertexAttrib1svNV and glVertexAttrib1svARB */
        { 2227, 2228 }, /* glVertexAttrib2d and glVertexAttrib2dARB */
        { 2227, 2229 }, /* glVertexAttrib2d and glVertexAttrib2dNV */
        { 2228, 2227 }, /* glVertexAttrib2dARB and glVertexAttrib2d */
        { 2228, 2229 }, /* glVertexAttrib2dARB and glVertexAttrib2dNV */
        { 2229, 2227 }, /* glVertexAttrib2dNV and glVertexAttrib2d */
        { 2229, 2228 }, /* glVertexAttrib2dNV and glVertexAttrib2dARB */
        { 2230, 2231 }, /* glVertexAttrib2dv and glVertexAttrib2dvARB */
        { 2230, 2232 }, /* glVertexAttrib2dv and glVertexAttrib2dvNV */
        { 2231, 2230 }, /* glVertexAttrib2dvARB and glVertexAttrib2dv */
        { 2231, 2232 }, /* glVertexAttrib2dvARB and glVertexAttrib2dvNV */
        { 2232, 2230 }, /* glVertexAttrib2dvNV and glVertexAttrib2dv */
        { 2232, 2231 }, /* glVertexAttrib2dvNV and glVertexAttrib2dvARB */
        { 2233, 2234 }, /* glVertexAttrib2f and glVertexAttrib2fARB */
        { 2233, 2235 }, /* glVertexAttrib2f and glVertexAttrib2fNV */
        { 2234, 2233 }, /* glVertexAttrib2fARB and glVertexAttrib2f */
        { 2234, 2235 }, /* glVertexAttrib2fARB and glVertexAttrib2fNV */
        { 2235, 2233 }, /* glVertexAttrib2fNV and glVertexAttrib2f */
        { 2235, 2234 }, /* glVertexAttrib2fNV and glVertexAttrib2fARB */
        { 2236, 2237 }, /* glVertexAttrib2fv and glVertexAttrib2fvARB */
        { 2236, 2238 }, /* glVertexAttrib2fv and glVertexAttrib2fvNV */
        { 2237, 2236 }, /* glVertexAttrib2fvARB and glVertexAttrib2fv */
        { 2237, 2238 }, /* glVertexAttrib2fvARB and glVertexAttrib2fvNV */
        { 2238, 2236 }, /* glVertexAttrib2fvNV and glVertexAttrib2fv */
        { 2238, 2237 }, /* glVertexAttrib2fvNV and glVertexAttrib2fvARB */
        { 2241, 2242 }, /* glVertexAttrib2s and glVertexAttrib2sARB */
        { 2241, 2243 }, /* glVertexAttrib2s and glVertexAttrib2sNV */
        { 2242, 2241 }, /* glVertexAttrib2sARB and glVertexAttrib2s */
        { 2242, 2243 }, /* glVertexAttrib2sARB and glVertexAttrib2sNV */
        { 2243, 2241 }, /* glVertexAttrib2sNV and glVertexAttrib2s */
        { 2243, 2242 }, /* glVertexAttrib2sNV and glVertexAttrib2sARB */
        { 2244, 2245 }, /* glVertexAttrib2sv and glVertexAttrib2svARB */
        { 2244, 2246 }, /* glVertexAttrib2sv and glVertexAttrib2svNV */
        { 2245, 2244 }, /* glVertexAttrib2svARB and glVertexAttrib2sv */
        { 2245, 2246 }, /* glVertexAttrib2svARB and glVertexAttrib2svNV */
        { 2246, 2244 }, /* glVertexAttrib2svNV and glVertexAttrib2sv */
        { 2246, 2245 }, /* glVertexAttrib2svNV and glVertexAttrib2svARB */
        { 2247, 2248 }, /* glVertexAttrib3d and glVertexAttrib3dARB */
        { 2247, 2249 }, /* glVertexAttrib3d and glVertexAttrib3dNV */
        { 2248, 2247 }, /* glVertexAttrib3dARB and glVertexAttrib3d */
        { 2248, 2249 }, /* glVertexAttrib3dARB and glVertexAttrib3dNV */
        { 2249, 2247 }, /* glVertexAttrib3dNV and glVertexAttrib3d */
        { 2249, 2248 }, /* glVertexAttrib3dNV and glVertexAttrib3dARB */
        { 2250, 2251 }, /* glVertexAttrib3dv and glVertexAttrib3dvARB */
        { 2250, 2252 }, /* glVertexAttrib3dv and glVertexAttrib3dvNV */
        { 2251, 2250 }, /* glVertexAttrib3dvARB and glVertexAttrib3dv */
        { 2251, 2252 }, /* glVertexAttrib3dvARB and glVertexAttrib3dvNV */
        { 2252, 2250 }, /* glVertexAttrib3dvNV and glVertexAttrib3dv */
        { 2252, 2251 }, /* glVertexAttrib3dvNV and glVertexAttrib3dvARB */
        { 2253, 2254 }, /* glVertexAttrib3f and glVertexAttrib3fARB */
        { 2253, 2255 }, /* glVertexAttrib3f and glVertexAttrib3fNV */
        { 2254, 2253 }, /* glVertexAttrib3fARB and glVertexAttrib3f */
        { 2254, 2255 }, /* glVertexAttrib3fARB and glVertexAttrib3fNV */
        { 2255, 2253 }, /* glVertexAttrib3fNV and glVertexAttrib3f */
        { 2255, 2254 }, /* glVertexAttrib3fNV and glVertexAttrib3fARB */
        { 2256, 2257 }, /* glVertexAttrib3fv and glVertexAttrib3fvARB */
        { 2256, 2258 }, /* glVertexAttrib3fv and glVertexAttrib3fvNV */
        { 2257, 2256 }, /* glVertexAttrib3fvARB and glVertexAttrib3fv */
        { 2257, 2258 }, /* glVertexAttrib3fvARB and glVertexAttrib3fvNV */
        { 2258, 2256 }, /* glVertexAttrib3fvNV and glVertexAttrib3fv */
        { 2258, 2257 }, /* glVertexAttrib3fvNV and glVertexAttrib3fvARB */
        { 2261, 2262 }, /* glVertexAttrib3s and glVertexAttrib3sARB */
        { 2261, 2263 }, /* glVertexAttrib3s and glVertexAttrib3sNV */
        { 2262, 2261 }, /* glVertexAttrib3sARB and glVertexAttrib3s */
        { 2262, 2263 }, /* glVertexAttrib3sARB and glVertexAttrib3sNV */
        { 2263, 2261 }, /* glVertexAttrib3sNV and glVertexAttrib3s */
        { 2263, 2262 }, /* glVertexAttrib3sNV and glVertexAttrib3sARB */
        { 2264, 2265 }, /* glVertexAttrib3sv and glVertexAttrib3svARB */
        { 2264, 2266 }, /* glVertexAttrib3sv and glVertexAttrib3svNV */
        { 2265, 2264 }, /* glVertexAttrib3svARB and glVertexAttrib3sv */
        { 2265, 2266 }, /* glVertexAttrib3svARB and glVertexAttrib3svNV */
        { 2266, 2264 }, /* glVertexAttrib3svNV and glVertexAttrib3sv */
        { 2266, 2265 }, /* glVertexAttrib3svNV and glVertexAttrib3svARB */
        { 2281, 2282 }, /* glVertexAttrib4bv and glVertexAttrib4bvARB */
        { 2282, 2281 }, /* glVertexAttrib4bvARB and glVertexAttrib4bv */
        { 2283, 2284 }, /* glVertexAttrib4d and glVertexAttrib4dARB */
        { 2283, 2285 }, /* glVertexAttrib4d and glVertexAttrib4dNV */
        { 2284, 2283 }, /* glVertexAttrib4dARB and glVertexAttrib4d */
        { 2284, 2285 }, /* glVertexAttrib4dARB and glVertexAttrib4dNV */
        { 2285, 2283 }, /* glVertexAttrib4dNV and glVertexAttrib4d */
        { 2285, 2284 }, /* glVertexAttrib4dNV and glVertexAttrib4dARB */
        { 2286, 2287 }, /* glVertexAttrib4dv and glVertexAttrib4dvARB */
        { 2286, 2288 }, /* glVertexAttrib4dv and glVertexAttrib4dvNV */
        { 2287, 2286 }, /* glVertexAttrib4dvARB and glVertexAttrib4dv */
        { 2287, 2288 }, /* glVertexAttrib4dvARB and glVertexAttrib4dvNV */
        { 2288, 2286 }, /* glVertexAttrib4dvNV and glVertexAttrib4dv */
        { 2288, 2287 }, /* glVertexAttrib4dvNV and glVertexAttrib4dvARB */
        { 2289, 2290 }, /* glVertexAttrib4f and glVertexAttrib4fARB */
        { 2289, 2291 }, /* glVertexAttrib4f and glVertexAttrib4fNV */
        { 2290, 2289 }, /* glVertexAttrib4fARB and glVertexAttrib4f */
        { 2290, 2291 }, /* glVertexAttrib4fARB and glVertexAttrib4fNV */
        { 2291, 2289 }, /* glVertexAttrib4fNV and glVertexAttrib4f */
        { 2291, 2290 }, /* glVertexAttrib4fNV and glVertexAttrib4fARB */
        { 2292, 2293 }, /* glVertexAttrib4fv and glVertexAttrib4fvARB */
        { 2292, 2294 }, /* glVertexAttrib4fv and glVertexAttrib4fvNV */
        { 2293, 2292 }, /* glVertexAttrib4fvARB and glVertexAttrib4fv */
        { 2293, 2294 }, /* glVertexAttrib4fvARB and glVertexAttrib4fvNV */
        { 2294, 2292 }, /* glVertexAttrib4fvNV and glVertexAttrib4fv */
        { 2294, 2293 }, /* glVertexAttrib4fvNV and glVertexAttrib4fvARB */
        { 2297, 2298 }, /* glVertexAttrib4iv and glVertexAttrib4ivARB */
        { 2298, 2297 }, /* glVertexAttrib4ivARB and glVertexAttrib4iv */
        { 2267, 2268 }, /* glVertexAttrib4Nbv and glVertexAttrib4NbvARB */
        { 2268, 2267 }, /* glVertexAttrib4NbvARB and glVertexAttrib4Nbv */
        { 2269, 2270 }, /* glVertexAttrib4Niv and glVertexAttrib4NivARB */
        { 2270, 2269 }, /* glVertexAttrib4NivARB and glVertexAttrib4Niv */
        { 2271, 2272 }, /* glVertexAttrib4Nsv and glVertexAttrib4NsvARB */
        { 2272, 2271 }, /* glVertexAttrib4NsvARB and glVertexAttrib4Nsv */
        { 2273, 2274 }, /* glVertexAttrib4Nub and glVertexAttrib4NubARB */
        { 2273, 2305 }, /* glVertexAttrib4Nub and glVertexAttrib4ubNV */
        { 2274, 2273 }, /* glVertexAttrib4NubARB and glVertexAttrib4Nub */
        { 2274, 2305 }, /* glVertexAttrib4NubARB and glVertexAttrib4ubNV */
        { 2275, 2276 }, /* glVertexAttrib4Nubv and glVertexAttrib4NubvARB */
        { 2275, 2308 }, /* glVertexAttrib4Nubv and glVertexAttrib4ubvNV */
        { 2276, 2275 }, /* glVertexAttrib4NubvARB and glVertexAttrib4Nubv */
        { 2276, 2308 }, /* glVertexAttrib4NubvARB and glVertexAttrib4ubvNV */
        { 2277, 2278 }, /* glVertexAttrib4Nuiv and glVertexAttrib4NuivARB */
        { 2278, 2277 }, /* glVertexAttrib4NuivARB and glVertexAttrib4Nuiv */
        { 2279, 2280 }, /* glVertexAttrib4Nusv and glVertexAttrib4NusvARB */
        { 2280, 2279 }, /* glVertexAttrib4NusvARB and glVertexAttrib4Nusv */
        { 2299, 2300 }, /* glVertexAttrib4s and glVertexAttrib4sARB */
        { 2299, 2301 }, /* glVertexAttrib4s and glVertexAttrib4sNV */
        { 2300, 2299 }, /* glVertexAttrib4sARB and glVertexAttrib4s */
        { 2300, 2301 }, /* glVertexAttrib4sARB and glVertexAttrib4sNV */
        { 2301, 2299 }, /* glVertexAttrib4sNV and glVertexAttrib4s */
        { 2301, 2300 }, /* glVertexAttrib4sNV and glVertexAttrib4sARB */
        { 2302, 2303 }, /* glVertexAttrib4sv and glVertexAttrib4svARB */
        { 2302, 2304 }, /* glVertexAttrib4sv and glVertexAttrib4svNV */
        { 2303, 2302 }, /* glVertexAttrib4svARB and glVertexAttrib4sv */
        { 2303, 2304 }, /* glVertexAttrib4svARB and glVertexAttrib4svNV */
        { 2304, 2302 }, /* glVertexAttrib4svNV and glVertexAttrib4sv */
        { 2304, 2303 }, /* glVertexAttrib4svNV and glVertexAttrib4svARB */
        { 2305, 2273 }, /* glVertexAttrib4ubNV and glVertexAttrib4Nub */
        { 2305, 2274 }, /* glVertexAttrib4ubNV and glVertexAttrib4NubARB */
        { 2306, 2307 }, /* glVertexAttrib4ubv and glVertexAttrib4ubvARB */
        { 2307, 2306 }, /* glVertexAttrib4ubvARB and glVertexAttrib4ubv */
        { 2308, 2275 }, /* glVertexAttrib4ubvNV and glVertexAttrib4Nubv */
        { 2308, 2276 }, /* glVertexAttrib4ubvNV and glVertexAttrib4NubvARB */
        { 2309, 2310 }, /* glVertexAttrib4uiv and glVertexAttrib4uivARB */
        { 2310, 2309 }, /* glVertexAttrib4uivARB and glVertexAttrib4uiv */
        { 2311, 2312 }, /* glVertexAttrib4usv and glVertexAttrib4usvARB */
        { 2312, 2311 }, /* glVertexAttrib4usvARB and glVertexAttrib4usv */
        { 2315, 2877 }, /* glVertexAttribDivisor and glVertexAttribDivisorANGLE */
        { 2315, 2316 }, /* glVertexAttribDivisor and glVertexAttribDivisorARB */
        { 2315, 2878 }, /* glVertexAttribDivisor and glVertexAttribDivisorEXT */
        { 2315, 2879 }, /* glVertexAttribDivisor and glVertexAttribDivisorNV */
        { 2877, 2315 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisor */
        { 2877, 2316 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisorARB */
        { 2877, 2878 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisorEXT */
        { 2877, 2879 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisorNV */
        { 2316, 2315 }, /* glVertexAttribDivisorARB and glVertexAttribDivisor */
        { 2316, 2877 }, /* glVertexAttribDivisorARB and glVertexAttribDivisorANGLE */
        { 2316, 2878 }, /* glVertexAttribDivisorARB and glVertexAttribDivisorEXT */
        { 2316, 2879 }, /* glVertexAttribDivisorARB and glVertexAttribDivisorNV */
        { 2878, 2315 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisor */
        { 2878, 2877 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisorANGLE */
        { 2878, 2316 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisorARB */
        { 2878, 2879 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisorNV */
        { 2879, 2315 }, /* glVertexAttribDivisorNV and glVertexAttribDivisor */
        { 2879, 2877 }, /* glVertexAttribDivisorNV and glVertexAttribDivisorANGLE */
        { 2879, 2316 }, /* glVertexAttribDivisorNV and glVertexAttribDivisorARB */
        { 2879, 2878 }, /* glVertexAttribDivisorNV and glVertexAttribDivisorEXT */
        { 2319, 2320 }, /* glVertexAttribI1i and glVertexAttribI1iEXT */
        { 2320, 2319 }, /* glVertexAttribI1iEXT and glVertexAttribI1i */
        { 2321, 2322 }, /* glVertexAttribI1iv and glVertexAttribI1ivEXT */
        { 2322, 2321 }, /* glVertexAttribI1ivEXT and glVertexAttribI1iv */
        { 2323, 2324 }, /* glVertexAttribI1ui and glVertexAttribI1uiEXT */
        { 2324, 2323 }, /* glVertexAttribI1uiEXT and glVertexAttribI1ui */
        { 2325, 2326 }, /* glVertexAttribI1uiv and glVertexAttribI1uivEXT */
        { 2326, 2325 }, /* glVertexAttribI1uivEXT and glVertexAttribI1uiv */
        { 2327, 2328 }, /* glVertexAttribI2i and glVertexAttribI2iEXT */
        { 2328, 2327 }, /* glVertexAttribI2iEXT and glVertexAttribI2i */
        { 2329, 2330 }, /* glVertexAttribI2iv and glVertexAttribI2ivEXT */
        { 2330, 2329 }, /* glVertexAttribI2ivEXT and glVertexAttribI2iv */
        { 2331, 2332 }, /* glVertexAttribI2ui and glVertexAttribI2uiEXT */
        { 2332, 2331 }, /* glVertexAttribI2uiEXT and glVertexAttribI2ui */
        { 2333, 2334 }, /* glVertexAttribI2uiv and glVertexAttribI2uivEXT */
        { 2334, 2333 }, /* glVertexAttribI2uivEXT and glVertexAttribI2uiv */
        { 2335, 2336 }, /* glVertexAttribI3i and glVertexAttribI3iEXT */
        { 2336, 2335 }, /* glVertexAttribI3iEXT and glVertexAttribI3i */
        { 2337, 2338 }, /* glVertexAttribI3iv and glVertexAttribI3ivEXT */
        { 2338, 2337 }, /* glVertexAttribI3ivEXT and glVertexAttribI3iv */
        { 2339, 2340 }, /* glVertexAttribI3ui and glVertexAttribI3uiEXT */
        { 2340, 2339 }, /* glVertexAttribI3uiEXT and glVertexAttribI3ui */
        { 2341, 2342 }, /* glVertexAttribI3uiv and glVertexAttribI3uivEXT */
        { 2342, 2341 }, /* glVertexAttribI3uivEXT and glVertexAttribI3uiv */
        { 2343, 2344 }, /* glVertexAttribI4bv and glVertexAttribI4bvEXT */
        { 2344, 2343 }, /* glVertexAttribI4bvEXT and glVertexAttribI4bv */
        { 2345, 2346 }, /* glVertexAttribI4i and glVertexAttribI4iEXT */
        { 2346, 2345 }, /* glVertexAttribI4iEXT and glVertexAttribI4i */
        { 2347, 2348 }, /* glVertexAttribI4iv and glVertexAttribI4ivEXT */
        { 2348, 2347 }, /* glVertexAttribI4ivEXT and glVertexAttribI4iv */
        { 2349, 2350 }, /* glVertexAttribI4sv and glVertexAttribI4svEXT */
        { 2350, 2349 }, /* glVertexAttribI4svEXT and glVertexAttribI4sv */
        { 2351, 2352 }, /* glVertexAttribI4ubv and glVertexAttribI4ubvEXT */
        { 2352, 2351 }, /* glVertexAttribI4ubvEXT and glVertexAttribI4ubv */
        { 2353, 2354 }, /* glVertexAttribI4ui and glVertexAttribI4uiEXT */
        { 2354, 2353 }, /* glVertexAttribI4uiEXT and glVertexAttribI4ui */
        { 2355, 2356 }, /* glVertexAttribI4uiv and glVertexAttribI4uivEXT */
        { 2356, 2355 }, /* glVertexAttribI4uivEXT and glVertexAttribI4uiv */
        { 2357, 2358 }, /* glVertexAttribI4usv and glVertexAttribI4usvEXT */
        { 2358, 2357 }, /* glVertexAttribI4usvEXT and glVertexAttribI4usv */
        { 2361, 2362 }, /* glVertexAttribIPointer and glVertexAttribIPointerEXT */
        { 2362, 2361 }, /* glVertexAttribIPointerEXT and glVertexAttribIPointer */
        { 2363, 2364 }, /* glVertexAttribL1d and glVertexAttribL1dEXT */
        { 2364, 2363 }, /* glVertexAttribL1dEXT and glVertexAttribL1d */
        { 2365, 2366 }, /* glVertexAttribL1dv and glVertexAttribL1dvEXT */
        { 2366, 2365 }, /* glVertexAttribL1dvEXT and glVertexAttribL1dv */
        { 2373, 2374 }, /* glVertexAttribL2d and glVertexAttribL2dEXT */
        { 2374, 2373 }, /* glVertexAttribL2dEXT and glVertexAttribL2d */
        { 2375, 2376 }, /* glVertexAttribL2dv and glVertexAttribL2dvEXT */
        { 2376, 2375 }, /* glVertexAttribL2dvEXT and glVertexAttribL2dv */
        { 2381, 2382 }, /* glVertexAttribL3d and glVertexAttribL3dEXT */
        { 2382, 2381 }, /* glVertexAttribL3dEXT and glVertexAttribL3d */
        { 2383, 2384 }, /* glVertexAttribL3dv and glVertexAttribL3dvEXT */
        { 2384, 2383 }, /* glVertexAttribL3dvEXT and glVertexAttribL3dv */
        { 2389, 2390 }, /* glVertexAttribL4d and glVertexAttribL4dEXT */
        { 2390, 2389 }, /* glVertexAttribL4dEXT and glVertexAttribL4d */
        { 2391, 2392 }, /* glVertexAttribL4dv and glVertexAttribL4dvEXT */
        { 2392, 2391 }, /* glVertexAttribL4dvEXT and glVertexAttribL4dv */
        { 2399, 2400 }, /* glVertexAttribLPointer and glVertexAttribLPointerEXT */
        { 2400, 2399 }, /* glVertexAttribLPointerEXT and glVertexAttribLPointer */
        { 2410, 2411 }, /* glVertexAttribPointer and glVertexAttribPointerARB */
        { 2411, 2410 }, /* glVertexAttribPointerARB and glVertexAttribPointer */
        { 2480, 2880 }, /* glViewportArrayv and glViewportArrayvNV */
        { 2480, 2881 }, /* glViewportArrayv and glViewportArrayvOES */
        { 2880, 2480 }, /* glViewportArrayvNV and glViewportArrayv */
        { 2880, 2881 }, /* glViewportArrayvNV and glViewportArrayvOES */
        { 2881, 2480 }, /* glViewportArrayvOES and glViewportArrayv */
        { 2881, 2880 }, /* glViewportArrayvOES and glViewportArrayvNV */
        { 2481, 2882 }, /* glViewportIndexedf and glViewportIndexedfNV */
        { 2481, 2883 }, /* glViewportIndexedf and glViewportIndexedfOES */
        { 2882, 2481 }, /* glViewportIndexedfNV and glViewportIndexedf */
        { 2882, 2883 }, /* glViewportIndexedfNV and glViewportIndexedfOES */
        { 2883, 2481 }, /* glViewportIndexedfOES and glViewportIndexedf */
        { 2883, 2882 }, /* glViewportIndexedfOES and glViewportIndexedfNV */
        { 2482, 2884 }, /* glViewportIndexedfv and glViewportIndexedfvNV */
        { 2482, 2885 }, /* glViewportIndexedfv and glViewportIndexedfvOES */
        { 2884, 2482 }, /* glViewportIndexedfvNV and glViewportIndexedfv */
        { 2884, 2885 }, /* glViewportIndexedfvNV and glViewportIndexedfvOES */
        { 2885, 2482 }, /* glViewportIndexedfvOES and glViewportIndexedfv */
        { 2885, 2884 }, /* glViewportIndexedfvOES and glViewportIndexedfvNV */
        { 2487, 2886 }, /* glWaitSync and glWaitSyncAPPLE */
        { 2886, 2487 }, /* glWaitSyncAPPLE and glWaitSync */
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

static int glad_gl_get_extensions(GladGLContext *context, uint64_t **out_exts, uint32_t *out_num_exts) {
    uint32_t num_exts = 0;
    uint64_t *exts = NULL;
    const char *exts_str = NULL;
    const char *cur = NULL;
    const char *next = NULL;
    uint32_t len = 0, j = 0;

#if defined(GL_ES_VERSION_3_0) || defined(GL_VERSION_3_0)
    if (context->GetStringi != NULL && context->GetIntegerv != NULL) {
        unsigned int index = 0;
        context->GetIntegerv(GL_NUM_EXTENSIONS, (int*) &num_exts);
        if (num_exts > 0) {
            exts = (uint64_t *)calloc(num_exts, sizeof(uint64_t));
        }
        if (exts == NULL) {
            return 0;
        }
        for(index = 0; index < num_exts; index++) {
            const char *gl_str_tmp = (const char*) context->GetStringi(GL_EXTENSIONS, index);
            size_t len = strlen(gl_str_tmp);
            exts[index] = glad_hash_string(gl_str_tmp, len);
        }
    } else
#endif
    {
        if (context->GetString == NULL) {
            return 0;
        }
        exts_str = (const char *)context->GetString(GL_EXTENSIONS);
        if (exts_str == NULL) {
            return 0;
        }

        /* This is done in two passes. The first pass counts up the number of
        * extensions. The second pass copies them into an allocated block of memory. */
        for (j = 0; j < 2; ++j) {
            num_exts = 0;
            cur = exts_str;
            next = cur + strcspn(cur, " ");
            while (1) {
                cur += strspn(cur, " ");

                if (!cur[0])
                    break;

                len = next - cur;

                if (exts != NULL) {
                    exts[num_exts++] = glad_hash_string(cur, len);
                } else {
                    num_exts++;
                }

                cur = next + strspn(next, " ");
                next = cur + strcspn(cur, " ");
            }

            if (!exts)
                exts = (uint64_t *)calloc(num_exts, sizeof(uint64_t));
        }
    }

    *out_num_exts = num_exts;
    *out_exts = exts;

    return 1;
}

static void glad_gl_free_extensions(uint64_t *exts) {
    free(exts);
}

static int glad_gl_has_extension(uint64_t *exts, uint32_t num_exts, uint64_t ext) {
    return glad_hash_search(exts, num_exts, ext);
}

static GLADapiproc glad_gl_get_proc_from_userptr(void *userptr, const char* name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_gl_find_extensions_gl(GladGLContext *context) {
    static const uint16_t s_extIdx[] = {
           0, /* GL_3DFX_multisample */
           1, /* GL_3DFX_tbuffer */
           2, /* GL_3DFX_texture_compression_FXT1 */
           3, /* GL_AMD_blend_minmax_factor */
           6, /* GL_AMD_conservative_depth */
           7, /* GL_AMD_debug_output */
           8, /* GL_AMD_depth_clamp_separate */
           9, /* GL_AMD_draw_buffers_blend */
          10, /* GL_AMD_framebuffer_multisample_advanced */
          11, /* GL_AMD_framebuffer_sample_positions */
          12, /* GL_AMD_gcn_shader */
          13, /* GL_AMD_gpu_shader_half_float */
          14, /* GL_AMD_gpu_shader_int16 */
          15, /* GL_AMD_gpu_shader_int64 */
          16, /* GL_AMD_interleaved_elements */
          17, /* GL_AMD_multi_draw_indirect */
          18, /* GL_AMD_name_gen_delete */
          19, /* GL_AMD_occlusion_query_event */
          20, /* GL_AMD_performance_monitor */
          21, /* GL_AMD_pinned_memory */
          23, /* GL_AMD_query_buffer_object */
          24, /* GL_AMD_sample_positions */
          25, /* GL_AMD_seamless_cubemap_per_texture */
          26, /* GL_AMD_shader_atomic_counter_ops */
          27, /* GL_AMD_shader_ballot */
          28, /* GL_AMD_shader_explicit_vertex_parameter */
          29, /* GL_AMD_shader_fragment_mask */
          30, /* GL_AMD_shader_gpu_shader_half_float_fetch */
          31, /* GL_AMD_shader_image_load_store_lod */
          32, /* GL_AMD_shader_stencil_export */
          33, /* GL_AMD_shader_trinary_minmax */
          34, /* GL_AMD_sparse_texture */
          35, /* GL_AMD_stencil_operation_extended */
          36, /* GL_AMD_texture_gather_bias_lod */
          37, /* GL_AMD_texture_texture4 */
          38, /* GL_AMD_transform_feedback3_lines_triangles */
          39, /* GL_AMD_transform_feedback4 */
          40, /* GL_AMD_vertex_shader_layer */
          41, /* GL_AMD_vertex_shader_tessellator */
          42, /* GL_AMD_vertex_shader_viewport_index */
          58, /* GL_ANGLE_memory_object_flags */
          59, /* GL_ANGLE_memory_object_fuchsia */
          74, /* GL_ANGLE_semaphore_fuchsia */
          81, /* GL_ANGLE_texture_external_update */
          87, /* GL_APPLE_aux_depth_stencil */
          88, /* GL_APPLE_client_storage */
          92, /* GL_APPLE_element_array */
          93, /* GL_APPLE_fence */
          94, /* GL_APPLE_float_pixels */
          95, /* GL_APPLE_flush_buffer_range */
          97, /* GL_APPLE_object_purgeable */
          98, /* GL_APPLE_rgb_422 */
          99, /* GL_APPLE_row_bytes */
         100, /* GL_APPLE_specular_vector */
         105, /* GL_APPLE_texture_range */
         106, /* GL_APPLE_transform_hint */
         107, /* GL_APPLE_vertex_array_object */
         108, /* GL_APPLE_vertex_array_range */
         109, /* GL_APPLE_vertex_program_evaluators */
         110, /* GL_APPLE_ycbcr_422 */
         111, /* GL_ARB_ES2_compatibility */
         112, /* GL_ARB_ES3_1_compatibility */
         113, /* GL_ARB_ES3_2_compatibility */
         114, /* GL_ARB_ES3_compatibility */
         115, /* GL_ARB_arrays_of_arrays */
         116, /* GL_ARB_base_instance */
         117, /* GL_ARB_bindless_texture */
         118, /* GL_ARB_blend_func_extended */
         119, /* GL_ARB_buffer_storage */
         120, /* GL_ARB_cl_event */
         121, /* GL_ARB_clear_buffer_object */
         122, /* GL_ARB_clear_texture */
         123, /* GL_ARB_clip_control */
         124, /* GL_ARB_color_buffer_float */
         125, /* GL_ARB_compatibility */
         126, /* GL_ARB_compressed_texture_pixel_storage */
         127, /* GL_ARB_compute_shader */
         128, /* GL_ARB_compute_variable_group_size */
         129, /* GL_ARB_conditional_render_inverted */
         130, /* GL_ARB_conservative_depth */
         131, /* GL_ARB_copy_buffer */
         132, /* GL_ARB_copy_image */
         133, /* GL_ARB_cull_distance */
         134, /* GL_ARB_debug_output */
         135, /* GL_ARB_depth_buffer_float */
         136, /* GL_ARB_depth_clamp */
         137, /* GL_ARB_depth_texture */
         138, /* GL_ARB_derivative_control */
         139, /* GL_ARB_direct_state_access */
         140, /* GL_ARB_draw_buffers */
         141, /* GL_ARB_draw_buffers_blend */
         142, /* GL_ARB_draw_elements_base_vertex */
         143, /* GL_ARB_draw_indirect */
         144, /* GL_ARB_draw_instanced */
         145, /* GL_ARB_enhanced_layouts */
         146, /* GL_ARB_explicit_attrib_location */
         147, /* GL_ARB_explicit_uniform_location */
         148, /* GL_ARB_fragment_coord_conventions */
         149, /* GL_ARB_fragment_layer_viewport */
         150, /* GL_ARB_fragment_program */
         151, /* GL_ARB_fragment_program_shadow */
         152, /* GL_ARB_fragment_shader */
         153, /* GL_ARB_fragment_shader_interlock */
         154, /* GL_ARB_framebuffer_no_attachments */
         155, /* GL_ARB_framebuffer_object */
         156, /* GL_ARB_framebuffer_sRGB */
         157, /* GL_ARB_geometry_shader4 */
         158, /* GL_ARB_get_program_binary */
         159, /* GL_ARB_get_texture_sub_image */
         160, /* GL_ARB_gl_spirv */
         161, /* GL_ARB_gpu_shader5 */
         162, /* GL_ARB_gpu_shader_fp64 */
         163, /* GL_ARB_gpu_shader_int64 */
         164, /* GL_ARB_half_float_pixel */
         165, /* GL_ARB_half_float_vertex */
         166, /* GL_ARB_imaging */
         167, /* GL_ARB_indirect_parameters */
         168, /* GL_ARB_instanced_arrays */
         169, /* GL_ARB_internalformat_query */
         170, /* GL_ARB_internalformat_query2 */
         171, /* GL_ARB_invalidate_subdata */
         172, /* GL_ARB_map_buffer_alignment */
         173, /* GL_ARB_map_buffer_range */
         174, /* GL_ARB_matrix_palette */
         175, /* GL_ARB_multi_bind */
         176, /* GL_ARB_multi_draw_indirect */
         177, /* GL_ARB_multisample */
         178, /* GL_ARB_multitexture */
         179, /* GL_ARB_occlusion_query */
         180, /* GL_ARB_occlusion_query2 */
         181, /* GL_ARB_parallel_shader_compile */
         182, /* GL_ARB_pipeline_statistics_query */
         183, /* GL_ARB_pixel_buffer_object */
         184, /* GL_ARB_point_parameters */
         185, /* GL_ARB_point_sprite */
         186, /* GL_ARB_polygon_offset_clamp */
         187, /* GL_ARB_post_depth_coverage */
         188, /* GL_ARB_program_interface_query */
         189, /* GL_ARB_provoking_vertex */
         190, /* GL_ARB_query_buffer_object */
         191, /* GL_ARB_robust_buffer_access_behavior */
         192, /* GL_ARB_robustness */
         193, /* GL_ARB_robustness_isolation */
         194, /* GL_ARB_sample_locations */
         195, /* GL_ARB_sample_shading */
         196, /* GL_ARB_sampler_objects */
         197, /* GL_ARB_seamless_cube_map */
         198, /* GL_ARB_seamless_cubemap_per_texture */
         199, /* GL_ARB_separate_shader_objects */
         200, /* GL_ARB_shader_atomic_counter_ops */
         201, /* GL_ARB_shader_atomic_counters */
         202, /* GL_ARB_shader_ballot */
         203, /* GL_ARB_shader_bit_encoding */
         204, /* GL_ARB_shader_clock */
         205, /* GL_ARB_shader_draw_parameters */
         206, /* GL_ARB_shader_group_vote */
         207, /* GL_ARB_shader_image_load_store */
         208, /* GL_ARB_shader_image_size */
         209, /* GL_ARB_shader_objects */
         210, /* GL_ARB_shader_precision */
         211, /* GL_ARB_shader_stencil_export */
         212, /* GL_ARB_shader_storage_buffer_object */
         213, /* GL_ARB_shader_subroutine */
         214, /* GL_ARB_shader_texture_image_samples */
         215, /* GL_ARB_shader_texture_lod */
         216, /* GL_ARB_shader_viewport_layer_array */
         217, /* GL_ARB_shading_language_100 */
         218, /* GL_ARB_shading_language_420pack */
         219, /* GL_ARB_shading_language_include */
         220, /* GL_ARB_shading_language_packing */
         221, /* GL_ARB_shadow */
         222, /* GL_ARB_shadow_ambient */
         223, /* GL_ARB_sparse_buffer */
         224, /* GL_ARB_sparse_texture */
         225, /* GL_ARB_sparse_texture2 */
         226, /* GL_ARB_sparse_texture_clamp */
         227, /* GL_ARB_spirv_extensions */
         228, /* GL_ARB_stencil_texturing */
         229, /* GL_ARB_sync */
         230, /* GL_ARB_tessellation_shader */
         231, /* GL_ARB_texture_barrier */
         232, /* GL_ARB_texture_border_clamp */
         233, /* GL_ARB_texture_buffer_object */
         234, /* GL_ARB_texture_buffer_object_rgb32 */
         235, /* GL_ARB_texture_buffer_range */
         236, /* GL_ARB_texture_compression */
         237, /* GL_ARB_texture_compression_bptc */
         238, /* GL_ARB_texture_compression_rgtc */
         239, /* GL_ARB_texture_cube_map */
         240, /* GL_ARB_texture_cube_map_array */
         241, /* GL_ARB_texture_env_add */
         242, /* GL_ARB_texture_env_combine */
         243, /* GL_ARB_texture_env_crossbar */
         244, /* GL_ARB_texture_env_dot3 */
         245, /* GL_ARB_texture_filter_anisotropic */
         246, /* GL_ARB_texture_filter_minmax */
         247, /* GL_ARB_texture_float */
         248, /* GL_ARB_texture_gather */
         249, /* GL_ARB_texture_mirror_clamp_to_edge */
         250, /* GL_ARB_texture_mirrored_repeat */
         251, /* GL_ARB_texture_multisample */
         252, /* GL_ARB_texture_non_power_of_two */
         253, /* GL_ARB_texture_query_levels */
         254, /* GL_ARB_texture_query_lod */
         255, /* GL_ARB_texture_rectangle */
         256, /* GL_ARB_texture_rg */
         257, /* GL_ARB_texture_rgb10_a2ui */
         258, /* GL_ARB_texture_stencil8 */
         259, /* GL_ARB_texture_storage */
         260, /* GL_ARB_texture_storage_multisample */
         261, /* GL_ARB_texture_swizzle */
         262, /* GL_ARB_texture_view */
         263, /* GL_ARB_timer_query */
         264, /* GL_ARB_transform_feedback2 */
         265, /* GL_ARB_transform_feedback3 */
         266, /* GL_ARB_transform_feedback_instanced */
         267, /* GL_ARB_transform_feedback_overflow_query */
         268, /* GL_ARB_transpose_matrix */
         269, /* GL_ARB_uniform_buffer_object */
         270, /* GL_ARB_vertex_array_bgra */
         271, /* GL_ARB_vertex_array_object */
         272, /* GL_ARB_vertex_attrib_64bit */
         273, /* GL_ARB_vertex_attrib_binding */
         274, /* GL_ARB_vertex_blend */
         275, /* GL_ARB_vertex_buffer_object */
         276, /* GL_ARB_vertex_program */
         277, /* GL_ARB_vertex_shader */
         278, /* GL_ARB_vertex_type_10f_11f_11f_rev */
         279, /* GL_ARB_vertex_type_2_10_10_10_rev */
         280, /* GL_ARB_viewport_array */
         281, /* GL_ARB_window_pos */
         285, /* GL_ARM_shader_core_builtins */
         290, /* GL_ATI_draw_buffers */
         291, /* GL_ATI_element_array */
         292, /* GL_ATI_envmap_bumpmap */
         293, /* GL_ATI_fragment_shader */
         294, /* GL_ATI_map_object_buffer */
         295, /* GL_ATI_meminfo */
         296, /* GL_ATI_pixel_format_float */
         297, /* GL_ATI_pn_triangles */
         298, /* GL_ATI_separate_stencil */
         299, /* GL_ATI_text_fragment_shader */
         300, /* GL_ATI_texture_env_combine3 */
         301, /* GL_ATI_texture_float */
         302, /* GL_ATI_texture_mirror_once */
         303, /* GL_ATI_vertex_array_object */
         304, /* GL_ATI_vertex_attrib_array_object */
         305, /* GL_ATI_vertex_streams */
         313, /* GL_EXT_422_pixels */
         315, /* GL_EXT_EGL_image_storage */
         317, /* GL_EXT_EGL_sync */
         319, /* GL_EXT_abgr */
         321, /* GL_EXT_bgra */
         322, /* GL_EXT_bindable_uniform */
         323, /* GL_EXT_blend_color */
         324, /* GL_EXT_blend_equation_separate */
         326, /* GL_EXT_blend_func_separate */
         327, /* GL_EXT_blend_logic_op */
         328, /* GL_EXT_blend_minmax */
         329, /* GL_EXT_blend_subtract */
         330, /* GL_EXT_buffer_reference */
         331, /* GL_EXT_buffer_reference2 */
         332, /* GL_EXT_buffer_reference_uvec2 */
         337, /* GL_EXT_clip_volume_hint */
         338, /* GL_EXT_cmyka */
         341, /* GL_EXT_color_subtable */
         342, /* GL_EXT_compiled_vertex_array */
         344, /* GL_EXT_control_flow_attributes */
         345, /* GL_EXT_control_flow_attributes2 */
         346, /* GL_EXT_convolution */
         347, /* GL_EXT_coordinate_frame */
         349, /* GL_EXT_copy_texture */
         350, /* GL_EXT_cull_vertex */
         351, /* GL_EXT_debug_label */
         352, /* GL_EXT_debug_marker */
         353, /* GL_EXT_debug_printf */
         354, /* GL_EXT_demote_to_helper_invocation */
         355, /* GL_EXT_depth_bounds_test */
         357, /* GL_EXT_device_group */
         358, /* GL_EXT_direct_state_access */
         362, /* GL_EXT_draw_buffers2 */
         365, /* GL_EXT_draw_instanced */
         366, /* GL_EXT_draw_range_elements */
         368, /* GL_EXT_external_buffer */
         370, /* GL_EXT_fog_coord */
         371, /* GL_EXT_fragment_invocation_density */
         372, /* GL_EXT_fragment_shader_barycentric */
         374, /* GL_EXT_framebuffer_blit */
         375, /* GL_EXT_framebuffer_blit_layers */
         376, /* GL_EXT_framebuffer_multisample */
         377, /* GL_EXT_framebuffer_multisample_blit_scaled */
         378, /* GL_EXT_framebuffer_object */
         379, /* GL_EXT_framebuffer_sRGB */
         382, /* GL_EXT_geometry_shader4 */
         383, /* GL_EXT_gpu_program_parameters */
         384, /* GL_EXT_gpu_shader4 */
         386, /* GL_EXT_histogram */
         387, /* GL_EXT_index_array_formats */
         388, /* GL_EXT_index_func */
         389, /* GL_EXT_index_material */
         390, /* GL_EXT_index_texture */
         392, /* GL_EXT_light_texture */
         394, /* GL_EXT_maximal_reconvergence */
         395, /* GL_EXT_memory_object */
         396, /* GL_EXT_memory_object_fd */
         397, /* GL_EXT_memory_object_win32 */
         398, /* GL_EXT_mesh_shader */
         399, /* GL_EXT_misc_attribute */
         400, /* GL_EXT_multi_draw_arrays */
         402, /* GL_EXT_multisample */
         407, /* GL_EXT_multiview_tessellation_geometry_shader */
         408, /* GL_EXT_multiview_texture_multisample */
         409, /* GL_EXT_multiview_timer_query */
         410, /* GL_EXT_nonuniform_qualifier */
         411, /* GL_EXT_null_initializer */
         413, /* GL_EXT_opacity_micromap */
         414, /* GL_EXT_packed_depth_stencil */
         415, /* GL_EXT_packed_float */
         416, /* GL_EXT_packed_pixels */
         417, /* GL_EXT_paletted_texture */
         418, /* GL_EXT_pixel_buffer_object */
         419, /* GL_EXT_pixel_transform */
         420, /* GL_EXT_pixel_transform_color_table */
         421, /* GL_EXT_point_parameters */
         422, /* GL_EXT_polygon_offset */
         423, /* GL_EXT_polygon_offset_clamp */
         424, /* GL_EXT_post_depth_coverage */
         427, /* GL_EXT_provoking_vertex */
         429, /* GL_EXT_raster_multisample */
         430, /* GL_EXT_ray_cull_mask */
         431, /* GL_EXT_ray_flags_primitive_culling */
         432, /* GL_EXT_ray_query */
         433, /* GL_EXT_ray_tracing */
         434, /* GL_EXT_ray_tracing_position_fetch */
         437, /* GL_EXT_rescale_normal */
         441, /* GL_EXT_samplerless_texture_functions */
         442, /* GL_EXT_scalar_block_layout */
         443, /* GL_EXT_secondary_color */
         444, /* GL_EXT_semaphore */
         445, /* GL_EXT_semaphore_fd */
         446, /* GL_EXT_semaphore_win32 */
         448, /* GL_EXT_separate_shader_objects */
         449, /* GL_EXT_separate_specular_color */
         450, /* GL_EXT_shader_16bit_storage */
         451, /* GL_EXT_shader_atomic_float */
         452, /* GL_EXT_shader_atomic_float2 */
         453, /* GL_EXT_shader_atomic_int64 */
         454, /* GL_EXT_shader_explicit_arithmetic_types */
         455, /* GL_EXT_shader_framebuffer_fetch */
         456, /* GL_EXT_shader_framebuffer_fetch_non_coherent */
         458, /* GL_EXT_shader_image_int64 */
         459, /* GL_EXT_shader_image_load_formatted */
         460, /* GL_EXT_shader_image_load_store */
         462, /* GL_EXT_shader_integer_mix */
         467, /* GL_EXT_shader_realtime_clock */
         468, /* GL_EXT_shader_samples_identical */
         469, /* GL_EXT_shader_subgroup_extended_types */
         471, /* GL_EXT_shader_tile_image */
         472, /* GL_EXT_shadow_funcs */
         474, /* GL_EXT_shared_memory_block */
         475, /* GL_EXT_shared_texture_palette */
         477, /* GL_EXT_sparse_texture2 */
         478, /* GL_EXT_stencil_clear_tag */
         479, /* GL_EXT_stencil_two_side */
         480, /* GL_EXT_stencil_wrap */
         481, /* GL_EXT_subgroup_uniform_control_flow */
         482, /* GL_EXT_subgroupuniform_qualifier */
         483, /* GL_EXT_subtexture */
         484, /* GL_EXT_terminate_invocation */
         487, /* GL_EXT_texture */
         488, /* GL_EXT_texture3D */
         489, /* GL_EXT_texture_array */
         492, /* GL_EXT_texture_buffer_object */
         496, /* GL_EXT_texture_compression_latc */
         497, /* GL_EXT_texture_compression_rgtc */
         498, /* GL_EXT_texture_compression_s3tc */
         500, /* GL_EXT_texture_cube_map */
         502, /* GL_EXT_texture_env_add */
         503, /* GL_EXT_texture_env_combine */
         504, /* GL_EXT_texture_env_dot3 */
         505, /* GL_EXT_texture_filter_anisotropic */
         506, /* GL_EXT_texture_filter_minmax */
         509, /* GL_EXT_texture_integer */
         510, /* GL_EXT_texture_lod_bias */
         511, /* GL_EXT_texture_mirror_clamp */
         514, /* GL_EXT_texture_object */
         515, /* GL_EXT_texture_perturb_normal */
         518, /* GL_EXT_texture_sRGB */
         519, /* GL_EXT_texture_sRGB_R8 */
         520, /* GL_EXT_texture_sRGB_RG8 */
         521, /* GL_EXT_texture_sRGB_decode */
         522, /* GL_EXT_texture_shadow_lod */
         523, /* GL_EXT_texture_shared_exponent */
         524, /* GL_EXT_texture_snorm */
         525, /* GL_EXT_texture_storage */
         527, /* GL_EXT_texture_swizzle */
         530, /* GL_EXT_timer_query */
         531, /* GL_EXT_transform_feedback */
         533, /* GL_EXT_vertex_array */
         534, /* GL_EXT_vertex_array_bgra */
         535, /* GL_EXT_vertex_attrib_64bit */
         536, /* GL_EXT_vertex_shader */
         537, /* GL_EXT_vertex_weighting */
         538, /* GL_EXT_vulkan_glsl_relaxed */
         539, /* GL_EXT_win32_keyed_mutex */
         540, /* GL_EXT_window_rectangles */
         541, /* GL_EXT_x11_sync_object */
         543, /* GL_GREMEDY_frame_terminator */
         544, /* GL_GREMEDY_string_marker */
         545, /* GL_HP_convolution_border_modes */
         546, /* GL_HP_image_transform */
         547, /* GL_HP_occlusion_test */
         548, /* GL_HP_texture_lighting */
         549, /* GL_HUAWEI_cluster_culling_shader */
         550, /* GL_HUAWEI_subpass_shading */
         551, /* GL_IBM_cull_vertex */
         552, /* GL_IBM_multimode_draw_arrays */
         553, /* GL_IBM_rasterpos_clip */
         554, /* GL_IBM_static_data */
         555, /* GL_IBM_texture_mirrored_repeat */
         556, /* GL_IBM_vertex_array_lists */
         566, /* GL_INGR_blend_func_separate */
         567, /* GL_INGR_color_clamp */
         568, /* GL_INGR_interlace_read */
         569, /* GL_INTEL_blackhole_render */
         570, /* GL_INTEL_conservative_rasterization */
         571, /* GL_INTEL_fragment_shader_ordering */
         572, /* GL_INTEL_framebuffer_CMAA */
         573, /* GL_INTEL_map_texture */
         574, /* GL_INTEL_parallel_arrays */
         575, /* GL_INTEL_performance_query */
         576, /* GL_KHR_blend_equation_advanced */
         577, /* GL_KHR_blend_equation_advanced_coherent */
         578, /* GL_KHR_context_flush_control */
         579, /* GL_KHR_cooperative_matrix */
         580, /* GL_KHR_debug */
         581, /* GL_KHR_memory_scope_semantics */
         582, /* GL_KHR_no_error */
         583, /* GL_KHR_parallel_shader_compile */
         584, /* GL_KHR_robust_buffer_access_behavior */
         585, /* GL_KHR_robustness */
         586, /* GL_KHR_shader_subgroup */
         587, /* GL_KHR_texture_compression_astc_hdr */
         588, /* GL_KHR_texture_compression_astc_ldr */
         589, /* GL_KHR_texture_compression_astc_sliced_3d */
         590, /* GL_KHR_vulkan_glsl */
         591, /* GL_MESAX_texture_stack */
         593, /* GL_MESA_framebuffer_flip_x */
         594, /* GL_MESA_framebuffer_flip_y */
         595, /* GL_MESA_framebuffer_swap_xy */
         596, /* GL_MESA_pack_invert */
         597, /* GL_MESA_program_binary_formats */
         598, /* GL_MESA_resize_buffers */
         600, /* GL_MESA_shader_integer_functions */
         601, /* GL_MESA_tile_raster_order */
         602, /* GL_MESA_window_pos */
         603, /* GL_MESA_ycbcr_texture */
         604, /* GL_NVX_blend_equation_advanced_multi_draw_buffers */
         605, /* GL_NVX_conditional_render */
         606, /* GL_NVX_gpu_memory_info */
         607, /* GL_NVX_gpu_multicast2 */
         608, /* GL_NVX_linked_gpu_multicast */
         609, /* GL_NVX_multiview_per_view_attributes */
         610, /* GL_NVX_progress_fence */
         611, /* GL_NV_alpha_to_coverage_dither_control */
         612, /* GL_NV_bindless_multi_draw_indirect */
         613, /* GL_NV_bindless_multi_draw_indirect_count */
         614, /* GL_NV_bindless_texture */
         615, /* GL_NV_blend_equation_advanced */
         616, /* GL_NV_blend_equation_advanced_coherent */
         617, /* GL_NV_blend_minmax_factor */
         618, /* GL_NV_blend_square */
         619, /* GL_NV_clip_space_w_scaling */
         620, /* GL_NV_command_list */
         621, /* GL_NV_compute_program5 */
         622, /* GL_NV_compute_shader_derivatives */
         623, /* GL_NV_conditional_render */
         624, /* GL_NV_conservative_raster */
         625, /* GL_NV_conservative_raster_dilate */
         626, /* GL_NV_conservative_raster_pre_snap */
         627, /* GL_NV_conservative_raster_pre_snap_triangles */
         628, /* GL_NV_conservative_raster_underestimation */
         629, /* GL_NV_cooperative_matrix */
         631, /* GL_NV_copy_depth_to_color */
         632, /* GL_NV_copy_image */
         634, /* GL_NV_deep_texture3D */
         635, /* GL_NV_depth_buffer_float */
         636, /* GL_NV_depth_clamp */
         638, /* GL_NV_displacement_micromap */
         641, /* GL_NV_draw_texture */
         642, /* GL_NV_draw_vulkan_image */
         643, /* GL_NV_evaluators */
         645, /* GL_NV_explicit_multisample */
         647, /* GL_NV_fence */
         648, /* GL_NV_fill_rectangle */
         649, /* GL_NV_float_buffer */
         650, /* GL_NV_fog_distance */
         651, /* GL_NV_fragment_coverage_to_color */
         652, /* GL_NV_fragment_program */
         653, /* GL_NV_fragment_program2 */
         654, /* GL_NV_fragment_program4 */
         655, /* GL_NV_fragment_program_option */
         656, /* GL_NV_fragment_shader_barycentric */
         657, /* GL_NV_fragment_shader_interlock */
         659, /* GL_NV_framebuffer_mixed_samples */
         661, /* GL_NV_framebuffer_multisample_coverage */
         663, /* GL_NV_geometry_program4 */
         664, /* GL_NV_geometry_shader4 */
         665, /* GL_NV_geometry_shader_passthrough */
         666, /* GL_NV_gpu_multicast */
         667, /* GL_NV_gpu_program4 */
         668, /* GL_NV_gpu_program5 */
         669, /* GL_NV_gpu_program5_mem_extended */
         670, /* GL_NV_gpu_shader5 */
         671, /* GL_NV_half_float */
         674, /* GL_NV_internalformat_sample_query */
         675, /* GL_NV_light_max_exponent */
         676, /* GL_NV_memory_attachment */
         677, /* GL_NV_memory_object_sparse */
         678, /* GL_NV_mesh_shader */
         679, /* GL_NV_multisample_coverage */
         680, /* GL_NV_multisample_filter_hint */
         682, /* GL_NV_occlusion_query */
         684, /* GL_NV_packed_depth_stencil */
         685, /* GL_NV_parameter_buffer_object */
         686, /* GL_NV_parameter_buffer_object2 */
         687, /* GL_NV_path_rendering */
         688, /* GL_NV_path_rendering_shared_edge */
         690, /* GL_NV_pixel_data_range */
         691, /* GL_NV_point_sprite */
         693, /* GL_NV_present_video */
         694, /* GL_NV_primitive_restart */
         695, /* GL_NV_primitive_shading_rate */
         696, /* GL_NV_query_resource */
         697, /* GL_NV_query_resource_tag */
         698, /* GL_NV_ray_tracing */
         699, /* GL_NV_ray_tracing_motion_blur */
         705, /* GL_NV_register_combiners */
         706, /* GL_NV_register_combiners2 */
         707, /* GL_NV_representative_fragment_test */
         708, /* GL_NV_robustness_video_memory_purge */
         710, /* GL_NV_sample_locations */
         711, /* GL_NV_sample_mask_override_coverage */
         712, /* GL_NV_scissor_exclusive */
         713, /* GL_NV_shader_atomic_counters */
         714, /* GL_NV_shader_atomic_float */
         715, /* GL_NV_shader_atomic_float64 */
         716, /* GL_NV_shader_atomic_fp16_vector */
         717, /* GL_NV_shader_atomic_int64 */
         718, /* GL_NV_shader_buffer_load */
         719, /* GL_NV_shader_buffer_store */
         720, /* GL_NV_shader_invocation_reorder */
         722, /* GL_NV_shader_sm_builtins */
         723, /* GL_NV_shader_storage_buffer_object */
         724, /* GL_NV_shader_subgroup_partitioned */
         725, /* GL_NV_shader_texture_footprint */
         726, /* GL_NV_shader_thread_group */
         727, /* GL_NV_shader_thread_shuffle */
         728, /* GL_NV_shading_rate_image */
         731, /* GL_NV_stereo_view_rendering */
         732, /* GL_NV_tessellation_program5 */
         733, /* GL_NV_texgen_emboss */
         734, /* GL_NV_texgen_reflection */
         735, /* GL_NV_texture_barrier */
         738, /* GL_NV_texture_compression_vtc */
         739, /* GL_NV_texture_env_combine4 */
         740, /* GL_NV_texture_expand_normal */
         741, /* GL_NV_texture_multisample */
         743, /* GL_NV_texture_rectangle */
         744, /* GL_NV_texture_rectangle_compressed */
         745, /* GL_NV_texture_shader */
         746, /* GL_NV_texture_shader2 */
         747, /* GL_NV_texture_shader3 */
         748, /* GL_NV_timeline_semaphore */
         749, /* GL_NV_transform_feedback */
         750, /* GL_NV_transform_feedback2 */
         751, /* GL_NV_uniform_buffer_std430_layout */
         752, /* GL_NV_uniform_buffer_unified_memory */
         753, /* GL_NV_vdpau_interop */
         754, /* GL_NV_vdpau_interop2 */
         755, /* GL_NV_vertex_array_range */
         756, /* GL_NV_vertex_array_range2 */
         757, /* GL_NV_vertex_attrib_integer_64bit */
         758, /* GL_NV_vertex_buffer_unified_memory */
         759, /* GL_NV_vertex_program */
         760, /* GL_NV_vertex_program1_1 */
         761, /* GL_NV_vertex_program2 */
         762, /* GL_NV_vertex_program2_option */
         763, /* GL_NV_vertex_program3 */
         764, /* GL_NV_vertex_program4 */
         765, /* GL_NV_video_capture */
         767, /* GL_NV_viewport_array2 */
         768, /* GL_NV_viewport_swizzle */
         772, /* GL_OES_byte_coordinates */
         775, /* GL_OES_compressed_paletted_texture */
         784, /* GL_OES_fixed_point */
         793, /* GL_OES_query_matrix */
         794, /* GL_OES_read_format */
         802, /* GL_OES_single_precision */
         826, /* GL_OML_interlace */
         827, /* GL_OML_resample */
         828, /* GL_OML_subsample */
         829, /* GL_OVR_multiview */
         830, /* GL_OVR_multiview2 */
         832, /* GL_PGI_misc_hints */
         833, /* GL_PGI_vertex_hints */
         842, /* GL_QCOM_image_processing */
         857, /* GL_REND_screen_coordinates */
         858, /* GL_S3_s3tc */
         859, /* GL_SGIS_detail_texture */
         860, /* GL_SGIS_fog_function */
         861, /* GL_SGIS_generate_mipmap */
         862, /* GL_SGIS_multisample */
         863, /* GL_SGIS_pixel_texture */
         864, /* GL_SGIS_point_line_texgen */
         865, /* GL_SGIS_point_parameters */
         866, /* GL_SGIS_sharpen_texture */
         867, /* GL_SGIS_texture4D */
         868, /* GL_SGIS_texture_border_clamp */
         869, /* GL_SGIS_texture_color_mask */
         870, /* GL_SGIS_texture_edge_clamp */
         871, /* GL_SGIS_texture_filter4 */
         872, /* GL_SGIS_texture_lod */
         873, /* GL_SGIS_texture_select */
         874, /* GL_SGIX_async */
         875, /* GL_SGIX_async_histogram */
         876, /* GL_SGIX_async_pixel */
         877, /* GL_SGIX_blend_alpha_minmax */
         878, /* GL_SGIX_calligraphic_fragment */
         879, /* GL_SGIX_clipmap */
         880, /* GL_SGIX_convolution_accuracy */
         881, /* GL_SGIX_depth_pass_instrument */
         882, /* GL_SGIX_depth_texture */
         883, /* GL_SGIX_flush_raster */
         884, /* GL_SGIX_fog_offset */
         885, /* GL_SGIX_fragment_lighting */
         886, /* GL_SGIX_framezoom */
         887, /* GL_SGIX_igloo_interface */
         888, /* GL_SGIX_instruments */
         889, /* GL_SGIX_interlace */
         890, /* GL_SGIX_ir_instrument1 */
         891, /* GL_SGIX_list_priority */
         892, /* GL_SGIX_pixel_texture */
         893, /* GL_SGIX_pixel_tiles */
         894, /* GL_SGIX_polynomial_ffd */
         895, /* GL_SGIX_reference_plane */
         896, /* GL_SGIX_resample */
         897, /* GL_SGIX_scalebias_hint */
         898, /* GL_SGIX_shadow */
         899, /* GL_SGIX_shadow_ambient */
         900, /* GL_SGIX_sprite */
         901, /* GL_SGIX_subsample */
         902, /* GL_SGIX_tag_sample_buffer */
         903, /* GL_SGIX_texture_add_env */
         904, /* GL_SGIX_texture_coordinate_clamp */
         905, /* GL_SGIX_texture_lod_bias */
         906, /* GL_SGIX_texture_multi_buffer */
         907, /* GL_SGIX_texture_scale_bias */
         908, /* GL_SGIX_vertex_preclip */
         909, /* GL_SGIX_ycrcb */
         910, /* GL_SGIX_ycrcb_subsample */
         911, /* GL_SGIX_ycrcba */
         912, /* GL_SGI_color_matrix */
         913, /* GL_SGI_color_table */
         914, /* GL_SGI_texture_color_table */
         915, /* GL_SUNX_constant_data */
         916, /* GL_SUN_convolution_border_modes */
         917, /* GL_SUN_global_alpha */
         918, /* GL_SUN_mesh_array */
         919, /* GL_SUN_slice_accum */
         920, /* GL_SUN_triangle_list */
         921, /* GL_SUN_vertex */
         923, /* GL_WIN_phong_shading */
         924, /* GL_WIN_specular_fog */
    };
    uint64_t *exts = NULL;
    uint32_t num_exts = 0;
    uint32_t i;
    if (!glad_gl_get_extensions(context, &exts, &num_exts)) return 0;

    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_extIdx); ++i) {
        const uint32_t extIdx = s_extIdx[i];
        context->extArray[extIdx] = glad_gl_has_extension(exts, num_exts, GLAD_GL_ext_hashes[extIdx]);
    }

    glad_gl_free_extensions(exts);

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

GLAD_NO_INLINE int gladLoadGLContextUserPtr(GladGLContext *context, GLADuserptrloadfunc load, void *userptr) {
    int version;

    context->GetString = (PFNGLGETSTRINGPROC) load(userptr, "glGetString");
    if(context->GetString == NULL) return 0;
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

    if (!glad_gl_find_extensions_gl(context)) return 0;
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

static int glad_gl_find_extensions_gles2(GladGLContext *context) {
    static const uint16_t s_extIdx[] = {
           4, /* GL_AMD_compressed_3DC_texture */
           5, /* GL_AMD_compressed_ATC_texture */
          10, /* GL_AMD_framebuffer_multisample_advanced */
          20, /* GL_AMD_performance_monitor */
          22, /* GL_AMD_program_binary_Z400 */
          29, /* GL_AMD_shader_fragment_mask */
          43, /* GL_ANDROID_extension_pack_es31a */
          44, /* GL_ANGLE_base_vertex_base_instance */
          45, /* GL_ANGLE_client_arrays */
          46, /* GL_ANGLE_clip_cull_distance */
          47, /* GL_ANGLE_copy_texture_3d */
          48, /* GL_ANGLE_depth_texture */
          49, /* GL_ANGLE_framebuffer_blit */
          50, /* GL_ANGLE_framebuffer_multisample */
          51, /* GL_ANGLE_get_image */
          52, /* GL_ANGLE_get_serialized_context_string */
          53, /* GL_ANGLE_get_tex_level_parameter */
          54, /* GL_ANGLE_instanced_arrays */
          55, /* GL_ANGLE_logic_op */
          56, /* GL_ANGLE_lossy_etc_decode */
          57, /* GL_ANGLE_low_latency */
          58, /* GL_ANGLE_memory_object_flags */
          59, /* GL_ANGLE_memory_object_fuchsia */
          60, /* GL_ANGLE_memory_size */
          61, /* GL_ANGLE_multi_draw */
          62, /* GL_ANGLE_pack_reverse_row_order */
          63, /* GL_ANGLE_polygon_mode */
          64, /* GL_ANGLE_program_binary */
          65, /* GL_ANGLE_program_binary_readiness_query */
          66, /* GL_ANGLE_program_cache_control */
          67, /* GL_ANGLE_provoking_vertex */
          68, /* GL_ANGLE_renderability_validation */
          69, /* GL_ANGLE_request_extension */
          70, /* GL_ANGLE_rgbx_internal_format */
          71, /* GL_ANGLE_robust_client_memory */
          72, /* GL_ANGLE_robust_fragment_shader_output */
          73, /* GL_ANGLE_robust_resource_initialization */
          74, /* GL_ANGLE_semaphore_fuchsia */
          75, /* GL_ANGLE_shader_binary */
          76, /* GL_ANGLE_shader_pixel_local_storage */
          77, /* GL_ANGLE_stencil_texturing */
          78, /* GL_ANGLE_texture_compression_dxt1 */
          79, /* GL_ANGLE_texture_compression_dxt3 */
          80, /* GL_ANGLE_texture_compression_dxt5 */
          81, /* GL_ANGLE_texture_external_update */
          82, /* GL_ANGLE_texture_multisample */
          83, /* GL_ANGLE_texture_usage */
          84, /* GL_ANGLE_translated_shader_source */
          85, /* GL_ANGLE_vulkan_image */
          86, /* GL_ANGLE_yuv_internal_format */
          89, /* GL_APPLE_clip_distance */
          90, /* GL_APPLE_color_buffer_packed_float */
          91, /* GL_APPLE_copy_texture_levels */
          96, /* GL_APPLE_framebuffer_multisample */
          98, /* GL_APPLE_rgb_422 */
         101, /* GL_APPLE_sync */
         102, /* GL_APPLE_texture_format_BGRA8888 */
         103, /* GL_APPLE_texture_max_level */
         104, /* GL_APPLE_texture_packed_float */
         282, /* GL_ARM_mali_program_binary */
         283, /* GL_ARM_mali_shader_binary */
         284, /* GL_ARM_rgba8 */
         285, /* GL_ARM_shader_core_builtins */
         286, /* GL_ARM_shader_core_properties */
         287, /* GL_ARM_shader_framebuffer_fetch */
         288, /* GL_ARM_shader_framebuffer_fetch_depth_stencil */
         289, /* GL_ARM_texture_unnormalized_coordinates */
         306, /* GL_CHROMIUM_bind_uniform_location */
         307, /* GL_CHROMIUM_copy_compressed_texture */
         308, /* GL_CHROMIUM_copy_texture */
         309, /* GL_CHROMIUM_framebuffer_mixed_samples */
         310, /* GL_CHROMIUM_lose_context */
         311, /* GL_DMP_program_binary */
         312, /* GL_DMP_shader_binary */
         314, /* GL_EXT_EGL_image_array */
         315, /* GL_EXT_EGL_image_storage */
         316, /* GL_EXT_EGL_image_storage_compression */
         318, /* GL_EXT_YUV_target */
         320, /* GL_EXT_base_instance */
         325, /* GL_EXT_blend_func_extended */
         328, /* GL_EXT_blend_minmax */
         330, /* GL_EXT_buffer_reference */
         331, /* GL_EXT_buffer_reference2 */
         332, /* GL_EXT_buffer_reference_uvec2 */
         333, /* GL_EXT_buffer_storage */
         334, /* GL_EXT_clear_texture */
         335, /* GL_EXT_clip_control */
         336, /* GL_EXT_clip_cull_distance */
         339, /* GL_EXT_color_buffer_float */
         340, /* GL_EXT_color_buffer_half_float */
         343, /* GL_EXT_conservative_depth */
         344, /* GL_EXT_control_flow_attributes */
         345, /* GL_EXT_control_flow_attributes2 */
         348, /* GL_EXT_copy_image */
         351, /* GL_EXT_debug_label */
         352, /* GL_EXT_debug_marker */
         353, /* GL_EXT_debug_printf */
         354, /* GL_EXT_demote_to_helper_invocation */
         356, /* GL_EXT_depth_clamp */
         357, /* GL_EXT_device_group */
         359, /* GL_EXT_discard_framebuffer */
         360, /* GL_EXT_disjoint_timer_query */
         361, /* GL_EXT_draw_buffers */
         363, /* GL_EXT_draw_buffers_indexed */
         364, /* GL_EXT_draw_elements_base_vertex */
         365, /* GL_EXT_draw_instanced */
         367, /* GL_EXT_draw_transform_feedback */
         368, /* GL_EXT_external_buffer */
         369, /* GL_EXT_float_blend */
         371, /* GL_EXT_fragment_invocation_density */
         372, /* GL_EXT_fragment_shader_barycentric */
         373, /* GL_EXT_fragment_shading_rate */
         375, /* GL_EXT_framebuffer_blit_layers */
         380, /* GL_EXT_geometry_point_size */
         381, /* GL_EXT_geometry_shader */
         385, /* GL_EXT_gpu_shader5 */
         391, /* GL_EXT_instanced_arrays */
         393, /* GL_EXT_map_buffer_range */
         394, /* GL_EXT_maximal_reconvergence */
         395, /* GL_EXT_memory_object */
         396, /* GL_EXT_memory_object_fd */
         397, /* GL_EXT_memory_object_win32 */
         398, /* GL_EXT_mesh_shader */
         400, /* GL_EXT_multi_draw_arrays */
         401, /* GL_EXT_multi_draw_indirect */
         403, /* GL_EXT_multisampled_compatibility */
         404, /* GL_EXT_multisampled_render_to_texture */
         405, /* GL_EXT_multisampled_render_to_texture2 */
         406, /* GL_EXT_multiview_draw_buffers */
         407, /* GL_EXT_multiview_tessellation_geometry_shader */
         408, /* GL_EXT_multiview_texture_multisample */
         409, /* GL_EXT_multiview_timer_query */
         410, /* GL_EXT_nonuniform_qualifier */
         411, /* GL_EXT_null_initializer */
         412, /* GL_EXT_occlusion_query_boolean */
         413, /* GL_EXT_opacity_micromap */
         423, /* GL_EXT_polygon_offset_clamp */
         424, /* GL_EXT_post_depth_coverage */
         425, /* GL_EXT_primitive_bounding_box */
         426, /* GL_EXT_protected_textures */
         428, /* GL_EXT_pvrtc_sRGB */
         429, /* GL_EXT_raster_multisample */
         430, /* GL_EXT_ray_cull_mask */
         431, /* GL_EXT_ray_flags_primitive_culling */
         432, /* GL_EXT_ray_query */
         433, /* GL_EXT_ray_tracing */
         434, /* GL_EXT_ray_tracing_position_fetch */
         435, /* GL_EXT_read_format_bgra */
         436, /* GL_EXT_render_snorm */
         438, /* GL_EXT_robustness */
         439, /* GL_EXT_sRGB */
         440, /* GL_EXT_sRGB_write_control */
         441, /* GL_EXT_samplerless_texture_functions */
         442, /* GL_EXT_scalar_block_layout */
         444, /* GL_EXT_semaphore */
         445, /* GL_EXT_semaphore_fd */
         446, /* GL_EXT_semaphore_win32 */
         447, /* GL_EXT_separate_depth_stencil */
         448, /* GL_EXT_separate_shader_objects */
         450, /* GL_EXT_shader_16bit_storage */
         451, /* GL_EXT_shader_atomic_float */
         452, /* GL_EXT_shader_atomic_float2 */
         453, /* GL_EXT_shader_atomic_int64 */
         454, /* GL_EXT_shader_explicit_arithmetic_types */
         455, /* GL_EXT_shader_framebuffer_fetch */
         456, /* GL_EXT_shader_framebuffer_fetch_non_coherent */
         457, /* GL_EXT_shader_group_vote */
         458, /* GL_EXT_shader_image_int64 */
         461, /* GL_EXT_shader_implicit_conversions */
         462, /* GL_EXT_shader_integer_mix */
         463, /* GL_EXT_shader_io_blocks */
         464, /* GL_EXT_shader_non_constant_global_initializers */
         465, /* GL_EXT_shader_pixel_local_storage */
         466, /* GL_EXT_shader_pixel_local_storage2 */
         467, /* GL_EXT_shader_realtime_clock */
         468, /* GL_EXT_shader_samples_identical */
         469, /* GL_EXT_shader_subgroup_extended_types */
         470, /* GL_EXT_shader_texture_lod */
         471, /* GL_EXT_shader_tile_image */
         473, /* GL_EXT_shadow_samplers */
         474, /* GL_EXT_shared_memory_block */
         476, /* GL_EXT_sparse_texture */
         477, /* GL_EXT_sparse_texture2 */
         481, /* GL_EXT_subgroup_uniform_control_flow */
         482, /* GL_EXT_subgroupuniform_qualifier */
         484, /* GL_EXT_terminate_invocation */
         485, /* GL_EXT_tessellation_point_size */
         486, /* GL_EXT_tessellation_shader */
         490, /* GL_EXT_texture_border_clamp */
         491, /* GL_EXT_texture_buffer */
         493, /* GL_EXT_texture_compression_astc_decode_mode */
         494, /* GL_EXT_texture_compression_bptc */
         495, /* GL_EXT_texture_compression_dxt1 */
         497, /* GL_EXT_texture_compression_rgtc */
         498, /* GL_EXT_texture_compression_s3tc */
         499, /* GL_EXT_texture_compression_s3tc_srgb */
         501, /* GL_EXT_texture_cube_map_array */
         505, /* GL_EXT_texture_filter_anisotropic */
         506, /* GL_EXT_texture_filter_minmax */
         507, /* GL_EXT_texture_format_BGRA8888 */
         508, /* GL_EXT_texture_format_sRGB_override */
         512, /* GL_EXT_texture_mirror_clamp_to_edge */
         513, /* GL_EXT_texture_norm16 */
         516, /* GL_EXT_texture_query_lod */
         517, /* GL_EXT_texture_rg */
         519, /* GL_EXT_texture_sRGB_R8 */
         520, /* GL_EXT_texture_sRGB_RG8 */
         521, /* GL_EXT_texture_sRGB_decode */
         522, /* GL_EXT_texture_shadow_lod */
         525, /* GL_EXT_texture_storage */
         526, /* GL_EXT_texture_storage_compression */
         528, /* GL_EXT_texture_type_2_10_10_10_REV */
         529, /* GL_EXT_texture_view */
         532, /* GL_EXT_unpack_subimage */
         538, /* GL_EXT_vulkan_glsl_relaxed */
         539, /* GL_EXT_win32_keyed_mutex */
         540, /* GL_EXT_window_rectangles */
         542, /* GL_FJ_shader_binary_GCCSO */
         549, /* GL_HUAWEI_cluster_culling_shader */
         550, /* GL_HUAWEI_subpass_shading */
         557, /* GL_IMG_bindless_texture */
         558, /* GL_IMG_framebuffer_downsample */
         559, /* GL_IMG_multisampled_render_to_texture */
         560, /* GL_IMG_program_binary */
         561, /* GL_IMG_read_format */
         562, /* GL_IMG_shader_binary */
         563, /* GL_IMG_texture_compression_pvrtc */
         564, /* GL_IMG_texture_compression_pvrtc2 */
         565, /* GL_IMG_texture_filter_cubic */
         569, /* GL_INTEL_blackhole_render */
         570, /* GL_INTEL_conservative_rasterization */
         572, /* GL_INTEL_framebuffer_CMAA */
         575, /* GL_INTEL_performance_query */
         576, /* GL_KHR_blend_equation_advanced */
         577, /* GL_KHR_blend_equation_advanced_coherent */
         578, /* GL_KHR_context_flush_control */
         579, /* GL_KHR_cooperative_matrix */
         580, /* GL_KHR_debug */
         581, /* GL_KHR_memory_scope_semantics */
         582, /* GL_KHR_no_error */
         583, /* GL_KHR_parallel_shader_compile */
         584, /* GL_KHR_robust_buffer_access_behavior */
         585, /* GL_KHR_robustness */
         586, /* GL_KHR_shader_subgroup */
         587, /* GL_KHR_texture_compression_astc_hdr */
         588, /* GL_KHR_texture_compression_astc_ldr */
         589, /* GL_KHR_texture_compression_astc_sliced_3d */
         590, /* GL_KHR_vulkan_glsl */
         592, /* GL_MESA_bgra */
         593, /* GL_MESA_framebuffer_flip_x */
         594, /* GL_MESA_framebuffer_flip_y */
         595, /* GL_MESA_framebuffer_swap_xy */
         597, /* GL_MESA_program_binary_formats */
         599, /* GL_MESA_sampler_objects */
         600, /* GL_MESA_shader_integer_functions */
         604, /* GL_NVX_blend_equation_advanced_multi_draw_buffers */
         609, /* GL_NVX_multiview_per_view_attributes */
         614, /* GL_NV_bindless_texture */
         615, /* GL_NV_blend_equation_advanced */
         616, /* GL_NV_blend_equation_advanced_coherent */
         617, /* GL_NV_blend_minmax_factor */
         619, /* GL_NV_clip_space_w_scaling */
         622, /* GL_NV_compute_shader_derivatives */
         623, /* GL_NV_conditional_render */
         624, /* GL_NV_conservative_raster */
         626, /* GL_NV_conservative_raster_pre_snap */
         627, /* GL_NV_conservative_raster_pre_snap_triangles */
         629, /* GL_NV_cooperative_matrix */
         630, /* GL_NV_copy_buffer */
         633, /* GL_NV_coverage_sample */
         637, /* GL_NV_depth_nonlinear */
         638, /* GL_NV_displacement_micromap */
         639, /* GL_NV_draw_buffers */
         640, /* GL_NV_draw_instanced */
         642, /* GL_NV_draw_vulkan_image */
         644, /* GL_NV_explicit_attrib_location */
         646, /* GL_NV_fbo_color_attachments */
         647, /* GL_NV_fence */
         648, /* GL_NV_fill_rectangle */
         651, /* GL_NV_fragment_coverage_to_color */
         656, /* GL_NV_fragment_shader_barycentric */
         657, /* GL_NV_fragment_shader_interlock */
         658, /* GL_NV_framebuffer_blit */
         659, /* GL_NV_framebuffer_mixed_samples */
         660, /* GL_NV_framebuffer_multisample */
         662, /* GL_NV_generate_mipmap_sRGB */
         665, /* GL_NV_geometry_shader_passthrough */
         670, /* GL_NV_gpu_shader5 */
         672, /* GL_NV_image_formats */
         673, /* GL_NV_instanced_arrays */
         674, /* GL_NV_internalformat_sample_query */
         676, /* GL_NV_memory_attachment */
         677, /* GL_NV_memory_object_sparse */
         678, /* GL_NV_mesh_shader */
         681, /* GL_NV_non_square_matrices */
         683, /* GL_NV_pack_subimage */
         687, /* GL_NV_path_rendering */
         688, /* GL_NV_path_rendering_shared_edge */
         689, /* GL_NV_pixel_buffer_object */
         692, /* GL_NV_polygon_mode */
         695, /* GL_NV_primitive_shading_rate */
         698, /* GL_NV_ray_tracing */
         699, /* GL_NV_ray_tracing_motion_blur */
         700, /* GL_NV_read_buffer */
         701, /* GL_NV_read_buffer_front */
         702, /* GL_NV_read_depth */
         703, /* GL_NV_read_depth_stencil */
         704, /* GL_NV_read_stencil */
         707, /* GL_NV_representative_fragment_test */
         709, /* GL_NV_sRGB_formats */
         710, /* GL_NV_sample_locations */
         711, /* GL_NV_sample_mask_override_coverage */
         712, /* GL_NV_scissor_exclusive */
         716, /* GL_NV_shader_atomic_fp16_vector */
         720, /* GL_NV_shader_invocation_reorder */
         721, /* GL_NV_shader_noperspective_interpolation */
         722, /* GL_NV_shader_sm_builtins */
         724, /* GL_NV_shader_subgroup_partitioned */
         725, /* GL_NV_shader_texture_footprint */
         728, /* GL_NV_shading_rate_image */
         729, /* GL_NV_shadow_samplers_array */
         730, /* GL_NV_shadow_samplers_cube */
         731, /* GL_NV_stereo_view_rendering */
         736, /* GL_NV_texture_border_clamp */
         737, /* GL_NV_texture_compression_s3tc_update */
         742, /* GL_NV_texture_npot_2D_mipmap */
         748, /* GL_NV_timeline_semaphore */
         766, /* GL_NV_viewport_array */
         767, /* GL_NV_viewport_array2 */
         768, /* GL_NV_viewport_swizzle */
         769, /* GL_OES_EGL_image */
         770, /* GL_OES_EGL_image_external */
         771, /* GL_OES_EGL_image_external_essl3 */
         773, /* GL_OES_compressed_ETC1_RGB8_sub_texture */
         774, /* GL_OES_compressed_ETC1_RGB8_texture */
         775, /* GL_OES_compressed_paletted_texture */
         776, /* GL_OES_copy_image */
         777, /* GL_OES_depth24 */
         778, /* GL_OES_depth32 */
         779, /* GL_OES_depth_texture */
         780, /* GL_OES_draw_buffers_indexed */
         781, /* GL_OES_draw_elements_base_vertex */
         782, /* GL_OES_element_index_uint */
         783, /* GL_OES_fbo_render_mipmap */
         785, /* GL_OES_fragment_precision_high */
         786, /* GL_OES_geometry_point_size */
         787, /* GL_OES_geometry_shader */
         788, /* GL_OES_get_program_binary */
         789, /* GL_OES_gpu_shader5 */
         790, /* GL_OES_mapbuffer */
         791, /* GL_OES_packed_depth_stencil */
         792, /* GL_OES_primitive_bounding_box */
         795, /* GL_OES_required_internalformat */
         796, /* GL_OES_rgb8_rgba8 */
         797, /* GL_OES_sample_shading */
         798, /* GL_OES_sample_variables */
         799, /* GL_OES_shader_image_atomic */
         800, /* GL_OES_shader_io_blocks */
         801, /* GL_OES_shader_multisample_interpolation */
         803, /* GL_OES_standard_derivatives */
         804, /* GL_OES_stencil1 */
         805, /* GL_OES_stencil4 */
         806, /* GL_OES_surfaceless_context */
         807, /* GL_OES_tessellation_point_size */
         808, /* GL_OES_tessellation_shader */
         809, /* GL_OES_texture_3D */
         810, /* GL_OES_texture_border_clamp */
         811, /* GL_OES_texture_buffer */
         812, /* GL_OES_texture_compression_astc */
         813, /* GL_OES_texture_cube_map_array */
         814, /* GL_OES_texture_float */
         815, /* GL_OES_texture_float_linear */
         816, /* GL_OES_texture_half_float */
         817, /* GL_OES_texture_half_float_linear */
         818, /* GL_OES_texture_npot */
         819, /* GL_OES_texture_stencil8 */
         820, /* GL_OES_texture_storage_multisample_2d_array */
         821, /* GL_OES_texture_view */
         822, /* GL_OES_vertex_array_object */
         823, /* GL_OES_vertex_half_float */
         824, /* GL_OES_vertex_type_10_10_10_2 */
         825, /* GL_OES_viewport_array */
         829, /* GL_OVR_multiview */
         830, /* GL_OVR_multiview2 */
         831, /* GL_OVR_multiview_multisampled_render_to_texture */
         834, /* GL_QCOM_YUV_texture_gather */
         835, /* GL_QCOM_alpha_test */
         836, /* GL_QCOM_binning_control */
         837, /* GL_QCOM_driver_control */
         838, /* GL_QCOM_extended_get */
         839, /* GL_QCOM_extended_get2 */
         840, /* GL_QCOM_frame_extrapolation */
         841, /* GL_QCOM_framebuffer_foveated */
         842, /* GL_QCOM_image_processing */
         843, /* GL_QCOM_motion_estimation */
         844, /* GL_QCOM_perfmon_global_mode */
         845, /* GL_QCOM_render_sRGB_R8_RG8 */
         846, /* GL_QCOM_render_shared_exponent */
         847, /* GL_QCOM_shader_framebuffer_fetch_noncoherent */
         848, /* GL_QCOM_shader_framebuffer_fetch_rate */
         849, /* GL_QCOM_shading_rate */
         850, /* GL_QCOM_texture_foveated */
         851, /* GL_QCOM_texture_foveated2 */
         852, /* GL_QCOM_texture_foveated_subsampled_layout */
         853, /* GL_QCOM_texture_lod_bias */
         854, /* GL_QCOM_tiled_rendering */
         855, /* GL_QCOM_writeonly_rendering */
         856, /* GL_QCOM_ycbcr_degamma */
         922, /* GL_VIV_shader_binary */
    };
    uint64_t *exts = NULL;
    uint32_t num_exts = 0;
    uint32_t i;
    if (!glad_gl_get_extensions(context, &exts, &num_exts)) return 0;

    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_extIdx); ++i) {
        const uint32_t extIdx = s_extIdx[i];
        context->extArray[extIdx] = glad_gl_has_extension(exts, num_exts, GLAD_GL_ext_hashes[extIdx]);
    }

    glad_gl_free_extensions(exts);

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

GLAD_NO_INLINE int gladLoadGLES2ContextUserPtr(GladGLContext *context, GLADuserptrloadfunc load, void *userptr) {
    int version;

    context->GetString = (PFNGLGETSTRINGPROC) load(userptr, "glGetString");
    if(context->GetString == NULL) return 0;
    version = glad_gl_find_core_gles2(context);

    glad_gl_load_GL_ES_VERSION_2_0(context, load, userptr);
    glad_gl_load_GL_ES_VERSION_3_0(context, load, userptr);
    glad_gl_load_GL_ES_VERSION_3_1(context, load, userptr);
    glad_gl_load_GL_ES_VERSION_3_2(context, load, userptr);

    if (!glad_gl_find_extensions_gles2(context)) return 0;
    glad_gl_load_GL_AMD_framebuffer_multisample_advanced(context, load, userptr);
    glad_gl_load_GL_AMD_performance_monitor(context, load, userptr);
    glad_gl_load_GL_ANGLE_base_vertex_base_instance(context, load, userptr);
    glad_gl_load_GL_ANGLE_copy_texture_3d(context, load, userptr);
    glad_gl_load_GL_ANGLE_framebuffer_blit(context, load, userptr);
    glad_gl_load_GL_ANGLE_framebuffer_multisample(context, load, userptr);
    glad_gl_load_GL_ANGLE_get_image(context, load, userptr);
    glad_gl_load_GL_ANGLE_get_tex_level_parameter(context, load, userptr);
    glad_gl_load_GL_ANGLE_instanced_arrays(context, load, userptr);
    glad_gl_load_GL_ANGLE_logic_op(context, load, userptr);
    glad_gl_load_GL_ANGLE_low_latency(context, load, userptr);
    glad_gl_load_GL_ANGLE_memory_object_flags(context, load, userptr);
    glad_gl_load_GL_ANGLE_memory_object_fuchsia(context, load, userptr);
    glad_gl_load_GL_ANGLE_multi_draw(context, load, userptr);
    glad_gl_load_GL_ANGLE_polygon_mode(context, load, userptr);
    glad_gl_load_GL_ANGLE_provoking_vertex(context, load, userptr);
    glad_gl_load_GL_ANGLE_request_extension(context, load, userptr);
    glad_gl_load_GL_ANGLE_robust_client_memory(context, load, userptr);
    glad_gl_load_GL_ANGLE_semaphore_fuchsia(context, load, userptr);
    glad_gl_load_GL_ANGLE_shader_pixel_local_storage(context, load, userptr);
    glad_gl_load_GL_ANGLE_texture_external_update(context, load, userptr);
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
    glad_gl_load_GL_EXT_EGL_image_storage(context, load, userptr);
    glad_gl_load_GL_EXT_base_instance(context, load, userptr);
    glad_gl_load_GL_EXT_blend_func_extended(context, load, userptr);
    glad_gl_load_GL_EXT_blend_minmax(context, load, userptr);
    glad_gl_load_GL_EXT_buffer_storage(context, load, userptr);
    glad_gl_load_GL_EXT_clear_texture(context, load, userptr);
    glad_gl_load_GL_EXT_clip_control(context, load, userptr);
    glad_gl_load_GL_EXT_copy_image(context, load, userptr);
    glad_gl_load_GL_EXT_debug_label(context, load, userptr);
    glad_gl_load_GL_EXT_debug_marker(context, load, userptr);
    glad_gl_load_GL_EXT_discard_framebuffer(context, load, userptr);
    glad_gl_load_GL_EXT_disjoint_timer_query(context, load, userptr);
    glad_gl_load_GL_EXT_draw_buffers(context, load, userptr);
    glad_gl_load_GL_EXT_draw_buffers_indexed(context, load, userptr);
    glad_gl_load_GL_EXT_draw_elements_base_vertex(context, load, userptr);
    glad_gl_load_GL_EXT_draw_instanced(context, load, userptr);
    glad_gl_load_GL_EXT_draw_transform_feedback(context, load, userptr);
    glad_gl_load_GL_EXT_external_buffer(context, load, userptr);
    glad_gl_load_GL_EXT_fragment_shading_rate(context, load, userptr);
    glad_gl_load_GL_EXT_framebuffer_blit_layers(context, load, userptr);
    glad_gl_load_GL_EXT_geometry_shader(context, load, userptr);
    glad_gl_load_GL_EXT_instanced_arrays(context, load, userptr);
    glad_gl_load_GL_EXT_map_buffer_range(context, load, userptr);
    glad_gl_load_GL_EXT_memory_object(context, load, userptr);
    glad_gl_load_GL_EXT_memory_object_fd(context, load, userptr);
    glad_gl_load_GL_EXT_memory_object_win32(context, load, userptr);
    glad_gl_load_GL_EXT_multi_draw_arrays(context, load, userptr);
    glad_gl_load_GL_EXT_multi_draw_indirect(context, load, userptr);
    glad_gl_load_GL_EXT_multisampled_render_to_texture(context, load, userptr);
    glad_gl_load_GL_EXT_multiview_draw_buffers(context, load, userptr);
    glad_gl_load_GL_EXT_occlusion_query_boolean(context, load, userptr);
    glad_gl_load_GL_EXT_polygon_offset_clamp(context, load, userptr);
    glad_gl_load_GL_EXT_primitive_bounding_box(context, load, userptr);
    glad_gl_load_GL_EXT_raster_multisample(context, load, userptr);
    glad_gl_load_GL_EXT_robustness(context, load, userptr);
    glad_gl_load_GL_EXT_semaphore(context, load, userptr);
    glad_gl_load_GL_EXT_semaphore_fd(context, load, userptr);
    glad_gl_load_GL_EXT_semaphore_win32(context, load, userptr);
    glad_gl_load_GL_EXT_separate_shader_objects(context, load, userptr);
    glad_gl_load_GL_EXT_shader_framebuffer_fetch_non_coherent(context, load, userptr);
    glad_gl_load_GL_EXT_shader_pixel_local_storage2(context, load, userptr);
    glad_gl_load_GL_EXT_sparse_texture(context, load, userptr);
    glad_gl_load_GL_EXT_tessellation_shader(context, load, userptr);
    glad_gl_load_GL_EXT_texture_border_clamp(context, load, userptr);
    glad_gl_load_GL_EXT_texture_buffer(context, load, userptr);
    glad_gl_load_GL_EXT_texture_storage(context, load, userptr);
    glad_gl_load_GL_EXT_texture_storage_compression(context, load, userptr);
    glad_gl_load_GL_EXT_texture_view(context, load, userptr);
    glad_gl_load_GL_EXT_win32_keyed_mutex(context, load, userptr);
    glad_gl_load_GL_EXT_window_rectangles(context, load, userptr);
    glad_gl_load_GL_IMG_bindless_texture(context, load, userptr);
    glad_gl_load_GL_IMG_framebuffer_downsample(context, load, userptr);
    glad_gl_load_GL_IMG_multisampled_render_to_texture(context, load, userptr);
    glad_gl_load_GL_INTEL_framebuffer_CMAA(context, load, userptr);
    glad_gl_load_GL_INTEL_performance_query(context, load, userptr);
    glad_gl_load_GL_KHR_blend_equation_advanced(context, load, userptr);
    glad_gl_load_GL_KHR_debug(context, load, userptr);
    glad_gl_load_GL_KHR_parallel_shader_compile(context, load, userptr);
    glad_gl_load_GL_KHR_robustness(context, load, userptr);
    glad_gl_load_GL_MESA_framebuffer_flip_y(context, load, userptr);
    glad_gl_load_GL_MESA_sampler_objects(context, load, userptr);
    glad_gl_load_GL_NV_bindless_texture(context, load, userptr);
    glad_gl_load_GL_NV_blend_equation_advanced(context, load, userptr);
    glad_gl_load_GL_NV_clip_space_w_scaling(context, load, userptr);
    glad_gl_load_GL_NV_conditional_render(context, load, userptr);
    glad_gl_load_GL_NV_conservative_raster(context, load, userptr);
    glad_gl_load_GL_NV_conservative_raster_pre_snap_triangles(context, load, userptr);
    glad_gl_load_GL_NV_copy_buffer(context, load, userptr);
    glad_gl_load_GL_NV_coverage_sample(context, load, userptr);
    glad_gl_load_GL_NV_draw_buffers(context, load, userptr);
    glad_gl_load_GL_NV_draw_instanced(context, load, userptr);
    glad_gl_load_GL_NV_draw_vulkan_image(context, load, userptr);
    glad_gl_load_GL_NV_fence(context, load, userptr);
    glad_gl_load_GL_NV_fragment_coverage_to_color(context, load, userptr);
    glad_gl_load_GL_NV_framebuffer_blit(context, load, userptr);
    glad_gl_load_GL_NV_framebuffer_mixed_samples(context, load, userptr);
    glad_gl_load_GL_NV_framebuffer_multisample(context, load, userptr);
    glad_gl_load_GL_NV_gpu_shader5(context, load, userptr);
    glad_gl_load_GL_NV_instanced_arrays(context, load, userptr);
    glad_gl_load_GL_NV_internalformat_sample_query(context, load, userptr);
    glad_gl_load_GL_NV_memory_attachment(context, load, userptr);
    glad_gl_load_GL_NV_memory_object_sparse(context, load, userptr);
    glad_gl_load_GL_NV_mesh_shader(context, load, userptr);
    glad_gl_load_GL_NV_non_square_matrices(context, load, userptr);
    glad_gl_load_GL_NV_path_rendering(context, load, userptr);
    glad_gl_load_GL_NV_polygon_mode(context, load, userptr);
    glad_gl_load_GL_NV_read_buffer(context, load, userptr);
    glad_gl_load_GL_NV_sample_locations(context, load, userptr);
    glad_gl_load_GL_NV_scissor_exclusive(context, load, userptr);
    glad_gl_load_GL_NV_shading_rate_image(context, load, userptr);
    glad_gl_load_GL_NV_timeline_semaphore(context, load, userptr);
    glad_gl_load_GL_NV_viewport_array(context, load, userptr);
    glad_gl_load_GL_NV_viewport_swizzle(context, load, userptr);
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
    glad_gl_load_GL_OVR_multiview(context, load, userptr);
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

        version = gladLoadGLContextUserPtr(context, glad_gl_get_proc, &userptr);

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
#elif defined(GLAD_GLES2_USE_SYSTEM_EGL)
  #include <EGL/egl.h>
  typedef __eglMustCastToProperFunctionPointerType (GLAD_API_PTR *PFNEGLGETPROCADDRESSPROC)(const char *name);
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
    GLAD_UNUSED(context);
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
#ifndef GLAD_GLES2_USE_SYSTEM_EGL
    if (eglGetProcAddress == NULL) {
        return 0;
    }
#endif
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
