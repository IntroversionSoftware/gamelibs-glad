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
    /*    0 */ "glAccum",
    /*    1 */ "glAccumxOES",
    /*    2 */ "glAcquireKeyedMutexWin32EXT",
    /*    3 */ "glActiveProgramEXT",
    /*    4 */ "glActiveShaderProgram",
    /*    5 */ "glActiveStencilFaceEXT",
    /*    6 */ "glActiveTexture",
    /*    7 */ "glActiveTextureARB",
    /*    8 */ "glActiveVaryingNV",
    /*    9 */ "glAlphaFragmentOp1ATI",
    /*   10 */ "glAlphaFragmentOp2ATI",
    /*   11 */ "glAlphaFragmentOp3ATI",
    /*   12 */ "glAlphaFunc",
    /*   13 */ "glAlphaFuncxOES",
    /*   14 */ "glAlphaToCoverageDitherControlNV",
    /*   15 */ "glApplyFramebufferAttachmentCMAAINTEL",
    /*   16 */ "glApplyTextureEXT",
    /*   17 */ "glAreProgramsResidentNV",
    /*   18 */ "glAreTexturesResident",
    /*   19 */ "glAreTexturesResidentEXT",
    /*   20 */ "glArrayElement",
    /*   21 */ "glArrayElementEXT",
    /*   22 */ "glArrayObjectATI",
    /*   23 */ "glAsyncCopyBufferSubDataNVX",
    /*   24 */ "glAsyncCopyImageSubDataNVX",
    /*   25 */ "glAsyncMarkerSGIX",
    /*   26 */ "glAttachObjectARB",
    /*   27 */ "glAttachShader",
    /*   28 */ "glBegin",
    /*   29 */ "glBeginConditionalRender",
    /*   30 */ "glBeginConditionalRenderNV",
    /*   31 */ "glBeginConditionalRenderNVX",
    /*   32 */ "glBeginFragmentShaderATI",
    /*   33 */ "glBeginOcclusionQueryNV",
    /*   34 */ "glBeginPerfMonitorAMD",
    /*   35 */ "glBeginPerfQueryINTEL",
    /*   36 */ "glBeginQuery",
    /*   37 */ "glBeginQueryARB",
    /*   38 */ "glBeginQueryIndexed",
    /*   39 */ "glBeginTransformFeedback",
    /*   40 */ "glBeginTransformFeedbackEXT",
    /*   41 */ "glBeginTransformFeedbackNV",
    /*   42 */ "glBeginVertexShaderEXT",
    /*   43 */ "glBeginVideoCaptureNV",
    /*   44 */ "glBindAttribLocation",
    /*   45 */ "glBindAttribLocationARB",
    /*   46 */ "glBindBuffer",
    /*   47 */ "glBindBufferARB",
    /*   48 */ "glBindBufferBase",
    /*   49 */ "glBindBufferBaseEXT",
    /*   50 */ "glBindBufferBaseNV",
    /*   51 */ "glBindBufferOffsetEXT",
    /*   52 */ "glBindBufferOffsetNV",
    /*   53 */ "glBindBufferRange",
    /*   54 */ "glBindBufferRangeEXT",
    /*   55 */ "glBindBufferRangeNV",
    /*   56 */ "glBindBuffersBase",
    /*   57 */ "glBindBuffersRange",
    /*   58 */ "glBindFragDataLocation",
    /*   59 */ "glBindFragDataLocationEXT",
    /*   60 */ "glBindFragDataLocationIndexed",
    /*   61 */ "glBindFragmentShaderATI",
    /*   62 */ "glBindFramebuffer",
    /*   63 */ "glBindFramebufferEXT",
    /*   64 */ "glBindImageTexture",
    /*   65 */ "glBindImageTextureEXT",
    /*   66 */ "glBindImageTextures",
    /*   67 */ "glBindLightParameterEXT",
    /*   68 */ "glBindMaterialParameterEXT",
    /*   69 */ "glBindMultiTextureEXT",
    /*   70 */ "glBindParameterEXT",
    /*   71 */ "glBindProgramARB",
    /*   72 */ "glBindProgramNV",
    /*   73 */ "glBindProgramPipeline",
    /*   74 */ "glBindRenderbuffer",
    /*   75 */ "glBindRenderbufferEXT",
    /*   76 */ "glBindSampler",
    /*   77 */ "glBindSamplers",
    /*   78 */ "glBindShadingRateImageNV",
    /*   79 */ "glBindTexGenParameterEXT",
    /*   80 */ "glBindTexture",
    /*   81 */ "glBindTextureEXT",
    /*   82 */ "glBindTextureUnit",
    /*   83 */ "glBindTextureUnitParameterEXT",
    /*   84 */ "glBindTextures",
    /*   85 */ "glBindTransformFeedback",
    /*   86 */ "glBindTransformFeedbackNV",
    /*   87 */ "glBindVertexArray",
    /*   88 */ "glBindVertexArrayAPPLE",
    /*   89 */ "glBindVertexBuffer",
    /*   90 */ "glBindVertexBuffers",
    /*   91 */ "glBindVertexShaderEXT",
    /*   92 */ "glBindVideoCaptureStreamBufferNV",
    /*   93 */ "glBindVideoCaptureStreamTextureNV",
    /*   94 */ "glBinormal3bEXT",
    /*   95 */ "glBinormal3bvEXT",
    /*   96 */ "glBinormal3dEXT",
    /*   97 */ "glBinormal3dvEXT",
    /*   98 */ "glBinormal3fEXT",
    /*   99 */ "glBinormal3fvEXT",
    /*  100 */ "glBinormal3iEXT",
    /*  101 */ "glBinormal3ivEXT",
    /*  102 */ "glBinormal3sEXT",
    /*  103 */ "glBinormal3svEXT",
    /*  104 */ "glBinormalPointerEXT",
    /*  105 */ "glBitmap",
    /*  106 */ "glBitmapxOES",
    /*  107 */ "glBlendBarrierKHR",
    /*  108 */ "glBlendBarrierNV",
    /*  109 */ "glBlendColor",
    /*  110 */ "glBlendColorEXT",
    /*  111 */ "glBlendColorxOES",
    /*  112 */ "glBlendEquation",
    /*  113 */ "glBlendEquationEXT",
    /*  114 */ "glBlendEquationIndexedAMD",
    /*  115 */ "glBlendEquationSeparate",
    /*  116 */ "glBlendEquationSeparateEXT",
    /*  117 */ "glBlendEquationSeparateIndexedAMD",
    /*  118 */ "glBlendEquationSeparatei",
    /*  119 */ "glBlendEquationSeparateiARB",
    /*  120 */ "glBlendEquationi",
    /*  121 */ "glBlendEquationiARB",
    /*  122 */ "glBlendFunc",
    /*  123 */ "glBlendFuncIndexedAMD",
    /*  124 */ "glBlendFuncSeparate",
    /*  125 */ "glBlendFuncSeparateEXT",
    /*  126 */ "glBlendFuncSeparateINGR",
    /*  127 */ "glBlendFuncSeparateIndexedAMD",
    /*  128 */ "glBlendFuncSeparatei",
    /*  129 */ "glBlendFuncSeparateiARB",
    /*  130 */ "glBlendFunci",
    /*  131 */ "glBlendFunciARB",
    /*  132 */ "glBlendParameteriNV",
    /*  133 */ "glBlitFramebuffer",
    /*  134 */ "glBlitFramebufferEXT",
    /*  135 */ "glBlitFramebufferLayerEXT",
    /*  136 */ "glBlitFramebufferLayersEXT",
    /*  137 */ "glBlitNamedFramebuffer",
    /*  138 */ "glBufferAddressRangeNV",
    /*  139 */ "glBufferAttachMemoryNV",
    /*  140 */ "glBufferData",
    /*  141 */ "glBufferDataARB",
    /*  142 */ "glBufferPageCommitmentARB",
    /*  143 */ "glBufferPageCommitmentMemNV",
    /*  144 */ "glBufferParameteriAPPLE",
    /*  145 */ "glBufferStorage",
    /*  146 */ "glBufferStorageExternalEXT",
    /*  147 */ "glBufferStorageMemEXT",
    /*  148 */ "glBufferSubData",
    /*  149 */ "glBufferSubDataARB",
    /*  150 */ "glCallCommandListNV",
    /*  151 */ "glCallList",
    /*  152 */ "glCallLists",
    /*  153 */ "glCheckFramebufferStatus",
    /*  154 */ "glCheckFramebufferStatusEXT",
    /*  155 */ "glCheckNamedFramebufferStatus",
    /*  156 */ "glCheckNamedFramebufferStatusEXT",
    /*  157 */ "glClampColor",
    /*  158 */ "glClampColorARB",
    /*  159 */ "glClear",
    /*  160 */ "glClearAccum",
    /*  161 */ "glClearAccumxOES",
    /*  162 */ "glClearBufferData",
    /*  163 */ "glClearBufferSubData",
    /*  164 */ "glClearBufferfi",
    /*  165 */ "glClearBufferfv",
    /*  166 */ "glClearBufferiv",
    /*  167 */ "glClearBufferuiv",
    /*  168 */ "glClearColor",
    /*  169 */ "glClearColorIiEXT",
    /*  170 */ "glClearColorIuiEXT",
    /*  171 */ "glClearColorxOES",
    /*  172 */ "glClearDepth",
    /*  173 */ "glClearDepthdNV",
    /*  174 */ "glClearDepthf",
    /*  175 */ "glClearDepthfOES",
    /*  176 */ "glClearDepthxOES",
    /*  177 */ "glClearIndex",
    /*  178 */ "glClearNamedBufferData",
    /*  179 */ "glClearNamedBufferDataEXT",
    /*  180 */ "glClearNamedBufferSubData",
    /*  181 */ "glClearNamedBufferSubDataEXT",
    /*  182 */ "glClearNamedFramebufferfi",
    /*  183 */ "glClearNamedFramebufferfv",
    /*  184 */ "glClearNamedFramebufferiv",
    /*  185 */ "glClearNamedFramebufferuiv",
    /*  186 */ "glClearStencil",
    /*  187 */ "glClearTexImage",
    /*  188 */ "glClearTexSubImage",
    /*  189 */ "glClientActiveTexture",
    /*  190 */ "glClientActiveTextureARB",
    /*  191 */ "glClientActiveVertexStreamATI",
    /*  192 */ "glClientAttribDefaultEXT",
    /*  193 */ "glClientWaitSemaphoreui64NVX",
    /*  194 */ "glClientWaitSync",
    /*  195 */ "glClipControl",
    /*  196 */ "glClipPlane",
    /*  197 */ "glClipPlanefOES",
    /*  198 */ "glClipPlanexOES",
    /*  199 */ "glColor3b",
    /*  200 */ "glColor3bv",
    /*  201 */ "glColor3d",
    /*  202 */ "glColor3dv",
    /*  203 */ "glColor3f",
    /*  204 */ "glColor3fVertex3fSUN",
    /*  205 */ "glColor3fVertex3fvSUN",
    /*  206 */ "glColor3fv",
    /*  207 */ "glColor3hNV",
    /*  208 */ "glColor3hvNV",
    /*  209 */ "glColor3i",
    /*  210 */ "glColor3iv",
    /*  211 */ "glColor3s",
    /*  212 */ "glColor3sv",
    /*  213 */ "glColor3ub",
    /*  214 */ "glColor3ubv",
    /*  215 */ "glColor3ui",
    /*  216 */ "glColor3uiv",
    /*  217 */ "glColor3us",
    /*  218 */ "glColor3usv",
    /*  219 */ "glColor3xOES",
    /*  220 */ "glColor3xvOES",
    /*  221 */ "glColor4b",
    /*  222 */ "glColor4bv",
    /*  223 */ "glColor4d",
    /*  224 */ "glColor4dv",
    /*  225 */ "glColor4f",
    /*  226 */ "glColor4fNormal3fVertex3fSUN",
    /*  227 */ "glColor4fNormal3fVertex3fvSUN",
    /*  228 */ "glColor4fv",
    /*  229 */ "glColor4hNV",
    /*  230 */ "glColor4hvNV",
    /*  231 */ "glColor4i",
    /*  232 */ "glColor4iv",
    /*  233 */ "glColor4s",
    /*  234 */ "glColor4sv",
    /*  235 */ "glColor4ub",
    /*  236 */ "glColor4ubVertex2fSUN",
    /*  237 */ "glColor4ubVertex2fvSUN",
    /*  238 */ "glColor4ubVertex3fSUN",
    /*  239 */ "glColor4ubVertex3fvSUN",
    /*  240 */ "glColor4ubv",
    /*  241 */ "glColor4ui",
    /*  242 */ "glColor4uiv",
    /*  243 */ "glColor4us",
    /*  244 */ "glColor4usv",
    /*  245 */ "glColor4xOES",
    /*  246 */ "glColor4xvOES",
    /*  247 */ "glColorFormatNV",
    /*  248 */ "glColorFragmentOp1ATI",
    /*  249 */ "glColorFragmentOp2ATI",
    /*  250 */ "glColorFragmentOp3ATI",
    /*  251 */ "glColorMask",
    /*  252 */ "glColorMaskIndexedEXT",
    /*  253 */ "glColorMaski",
    /*  254 */ "glColorMaterial",
    /*  255 */ "glColorP3ui",
    /*  256 */ "glColorP3uiv",
    /*  257 */ "glColorP4ui",
    /*  258 */ "glColorP4uiv",
    /*  259 */ "glColorPointer",
    /*  260 */ "glColorPointerEXT",
    /*  261 */ "glColorPointerListIBM",
    /*  262 */ "glColorPointervINTEL",
    /*  263 */ "glColorSubTable",
    /*  264 */ "glColorSubTableEXT",
    /*  265 */ "glColorTable",
    /*  266 */ "glColorTableEXT",
    /*  267 */ "glColorTableParameterfv",
    /*  268 */ "glColorTableParameterfvSGI",
    /*  269 */ "glColorTableParameteriv",
    /*  270 */ "glColorTableParameterivSGI",
    /*  271 */ "glColorTableSGI",
    /*  272 */ "glCombinerInputNV",
    /*  273 */ "glCombinerOutputNV",
    /*  274 */ "glCombinerParameterfNV",
    /*  275 */ "glCombinerParameterfvNV",
    /*  276 */ "glCombinerParameteriNV",
    /*  277 */ "glCombinerParameterivNV",
    /*  278 */ "glCombinerStageParameterfvNV",
    /*  279 */ "glCommandListSegmentsNV",
    /*  280 */ "glCompileCommandListNV",
    /*  281 */ "glCompileShader",
    /*  282 */ "glCompileShaderARB",
    /*  283 */ "glCompileShaderIncludeARB",
    /*  284 */ "glCompressedMultiTexImage1DEXT",
    /*  285 */ "glCompressedMultiTexImage2DEXT",
    /*  286 */ "glCompressedMultiTexImage3DEXT",
    /*  287 */ "glCompressedMultiTexSubImage1DEXT",
    /*  288 */ "glCompressedMultiTexSubImage2DEXT",
    /*  289 */ "glCompressedMultiTexSubImage3DEXT",
    /*  290 */ "glCompressedTexImage1D",
    /*  291 */ "glCompressedTexImage1DARB",
    /*  292 */ "glCompressedTexImage2D",
    /*  293 */ "glCompressedTexImage2DARB",
    /*  294 */ "glCompressedTexImage3D",
    /*  295 */ "glCompressedTexImage3DARB",
    /*  296 */ "glCompressedTexSubImage1D",
    /*  297 */ "glCompressedTexSubImage1DARB",
    /*  298 */ "glCompressedTexSubImage2D",
    /*  299 */ "glCompressedTexSubImage2DARB",
    /*  300 */ "glCompressedTexSubImage3D",
    /*  301 */ "glCompressedTexSubImage3DARB",
    /*  302 */ "glCompressedTextureImage1DEXT",
    /*  303 */ "glCompressedTextureImage2DEXT",
    /*  304 */ "glCompressedTextureImage3DEXT",
    /*  305 */ "glCompressedTextureSubImage1D",
    /*  306 */ "glCompressedTextureSubImage1DEXT",
    /*  307 */ "glCompressedTextureSubImage2D",
    /*  308 */ "glCompressedTextureSubImage2DEXT",
    /*  309 */ "glCompressedTextureSubImage3D",
    /*  310 */ "glCompressedTextureSubImage3DEXT",
    /*  311 */ "glConservativeRasterParameterfNV",
    /*  312 */ "glConservativeRasterParameteriNV",
    /*  313 */ "glConvolutionFilter1D",
    /*  314 */ "glConvolutionFilter1DEXT",
    /*  315 */ "glConvolutionFilter2D",
    /*  316 */ "glConvolutionFilter2DEXT",
    /*  317 */ "glConvolutionParameterf",
    /*  318 */ "glConvolutionParameterfEXT",
    /*  319 */ "glConvolutionParameterfv",
    /*  320 */ "glConvolutionParameterfvEXT",
    /*  321 */ "glConvolutionParameteri",
    /*  322 */ "glConvolutionParameteriEXT",
    /*  323 */ "glConvolutionParameteriv",
    /*  324 */ "glConvolutionParameterivEXT",
    /*  325 */ "glConvolutionParameterxOES",
    /*  326 */ "glConvolutionParameterxvOES",
    /*  327 */ "glCopyBufferSubData",
    /*  328 */ "glCopyColorSubTable",
    /*  329 */ "glCopyColorSubTableEXT",
    /*  330 */ "glCopyColorTable",
    /*  331 */ "glCopyColorTableSGI",
    /*  332 */ "glCopyConvolutionFilter1D",
    /*  333 */ "glCopyConvolutionFilter1DEXT",
    /*  334 */ "glCopyConvolutionFilter2D",
    /*  335 */ "glCopyConvolutionFilter2DEXT",
    /*  336 */ "glCopyImageSubData",
    /*  337 */ "glCopyImageSubDataNV",
    /*  338 */ "glCopyMultiTexImage1DEXT",
    /*  339 */ "glCopyMultiTexImage2DEXT",
    /*  340 */ "glCopyMultiTexSubImage1DEXT",
    /*  341 */ "glCopyMultiTexSubImage2DEXT",
    /*  342 */ "glCopyMultiTexSubImage3DEXT",
    /*  343 */ "glCopyNamedBufferSubData",
    /*  344 */ "glCopyPathNV",
    /*  345 */ "glCopyPixels",
    /*  346 */ "glCopyTexImage1D",
    /*  347 */ "glCopyTexImage1DEXT",
    /*  348 */ "glCopyTexImage2D",
    /*  349 */ "glCopyTexImage2DEXT",
    /*  350 */ "glCopyTexSubImage1D",
    /*  351 */ "glCopyTexSubImage1DEXT",
    /*  352 */ "glCopyTexSubImage2D",
    /*  353 */ "glCopyTexSubImage2DEXT",
    /*  354 */ "glCopyTexSubImage3D",
    /*  355 */ "glCopyTexSubImage3DEXT",
    /*  356 */ "glCopyTextureImage1DEXT",
    /*  357 */ "glCopyTextureImage2DEXT",
    /*  358 */ "glCopyTextureSubImage1D",
    /*  359 */ "glCopyTextureSubImage1DEXT",
    /*  360 */ "glCopyTextureSubImage2D",
    /*  361 */ "glCopyTextureSubImage2DEXT",
    /*  362 */ "glCopyTextureSubImage3D",
    /*  363 */ "glCopyTextureSubImage3DEXT",
    /*  364 */ "glCoverFillPathInstancedNV",
    /*  365 */ "glCoverFillPathNV",
    /*  366 */ "glCoverStrokePathInstancedNV",
    /*  367 */ "glCoverStrokePathNV",
    /*  368 */ "glCoverageModulationNV",
    /*  369 */ "glCoverageModulationTableNV",
    /*  370 */ "glCreateBuffers",
    /*  371 */ "glCreateCommandListsNV",
    /*  372 */ "glCreateFramebuffers",
    /*  373 */ "glCreateMemoryObjectsEXT",
    /*  374 */ "glCreatePerfQueryINTEL",
    /*  375 */ "glCreateProgram",
    /*  376 */ "glCreateProgramObjectARB",
    /*  377 */ "glCreateProgramPipelines",
    /*  378 */ "glCreateProgressFenceNVX",
    /*  379 */ "glCreateQueries",
    /*  380 */ "glCreateRenderbuffers",
    /*  381 */ "glCreateSamplers",
    /*  382 */ "glCreateSemaphoresNV",
    /*  383 */ "glCreateShader",
    /*  384 */ "glCreateShaderObjectARB",
    /*  385 */ "glCreateShaderProgramEXT",
    /*  386 */ "glCreateShaderProgramv",
    /*  387 */ "glCreateStatesNV",
    /*  388 */ "glCreateSyncFromCLeventARB",
    /*  389 */ "glCreateTextures",
    /*  390 */ "glCreateTransformFeedbacks",
    /*  391 */ "glCreateVertexArrays",
    /*  392 */ "glCullFace",
    /*  393 */ "glCullParameterdvEXT",
    /*  394 */ "glCullParameterfvEXT",
    /*  395 */ "glCurrentPaletteMatrixARB",
    /*  396 */ "glDebugMessageCallback",
    /*  397 */ "glDebugMessageCallbackAMD",
    /*  398 */ "glDebugMessageCallbackARB",
    /*  399 */ "glDebugMessageControl",
    /*  400 */ "glDebugMessageControlARB",
    /*  401 */ "glDebugMessageEnableAMD",
    /*  402 */ "glDebugMessageInsert",
    /*  403 */ "glDebugMessageInsertAMD",
    /*  404 */ "glDebugMessageInsertARB",
    /*  405 */ "glDeformSGIX",
    /*  406 */ "glDeformationMap3dSGIX",
    /*  407 */ "glDeformationMap3fSGIX",
    /*  408 */ "glDeleteAsyncMarkersSGIX",
    /*  409 */ "glDeleteBuffers",
    /*  410 */ "glDeleteBuffersARB",
    /*  411 */ "glDeleteCommandListsNV",
    /*  412 */ "glDeleteFencesAPPLE",
    /*  413 */ "glDeleteFencesNV",
    /*  414 */ "glDeleteFragmentShaderATI",
    /*  415 */ "glDeleteFramebuffers",
    /*  416 */ "glDeleteFramebuffersEXT",
    /*  417 */ "glDeleteLists",
    /*  418 */ "glDeleteMemoryObjectsEXT",
    /*  419 */ "glDeleteNamedStringARB",
    /*  420 */ "glDeleteNamesAMD",
    /*  421 */ "glDeleteObjectARB",
    /*  422 */ "glDeleteOcclusionQueriesNV",
    /*  423 */ "glDeletePathsNV",
    /*  424 */ "glDeletePerfMonitorsAMD",
    /*  425 */ "glDeletePerfQueryINTEL",
    /*  426 */ "glDeleteProgram",
    /*  427 */ "glDeleteProgramPipelines",
    /*  428 */ "glDeleteProgramsARB",
    /*  429 */ "glDeleteProgramsNV",
    /*  430 */ "glDeleteQueries",
    /*  431 */ "glDeleteQueriesARB",
    /*  432 */ "glDeleteQueryResourceTagNV",
    /*  433 */ "glDeleteRenderbuffers",
    /*  434 */ "glDeleteRenderbuffersEXT",
    /*  435 */ "glDeleteSamplers",
    /*  436 */ "glDeleteSemaphoresEXT",
    /*  437 */ "glDeleteShader",
    /*  438 */ "glDeleteStatesNV",
    /*  439 */ "glDeleteSync",
    /*  440 */ "glDeleteTextures",
    /*  441 */ "glDeleteTexturesEXT",
    /*  442 */ "glDeleteTransformFeedbacks",
    /*  443 */ "glDeleteTransformFeedbacksNV",
    /*  444 */ "glDeleteVertexArrays",
    /*  445 */ "glDeleteVertexArraysAPPLE",
    /*  446 */ "glDeleteVertexShaderEXT",
    /*  447 */ "glDepthBoundsEXT",
    /*  448 */ "glDepthBoundsdNV",
    /*  449 */ "glDepthFunc",
    /*  450 */ "glDepthMask",
    /*  451 */ "glDepthRange",
    /*  452 */ "glDepthRangeArraydvNV",
    /*  453 */ "glDepthRangeArrayv",
    /*  454 */ "glDepthRangeIndexed",
    /*  455 */ "glDepthRangeIndexeddNV",
    /*  456 */ "glDepthRangedNV",
    /*  457 */ "glDepthRangef",
    /*  458 */ "glDepthRangefOES",
    /*  459 */ "glDepthRangexOES",
    /*  460 */ "glDetachObjectARB",
    /*  461 */ "glDetachShader",
    /*  462 */ "glDetailTexFuncSGIS",
    /*  463 */ "glDisable",
    /*  464 */ "glDisableClientState",
    /*  465 */ "glDisableClientStateIndexedEXT",
    /*  466 */ "glDisableClientStateiEXT",
    /*  467 */ "glDisableIndexedEXT",
    /*  468 */ "glDisableVariantClientStateEXT",
    /*  469 */ "glDisableVertexArrayAttrib",
    /*  470 */ "glDisableVertexArrayAttribEXT",
    /*  471 */ "glDisableVertexArrayEXT",
    /*  472 */ "glDisableVertexAttribAPPLE",
    /*  473 */ "glDisableVertexAttribArray",
    /*  474 */ "glDisableVertexAttribArrayARB",
    /*  475 */ "glDisablei",
    /*  476 */ "glDispatchCompute",
    /*  477 */ "glDispatchComputeGroupSizeARB",
    /*  478 */ "glDispatchComputeIndirect",
    /*  479 */ "glDrawArrays",
    /*  480 */ "glDrawArraysEXT",
    /*  481 */ "glDrawArraysIndirect",
    /*  482 */ "glDrawArraysInstanced",
    /*  483 */ "glDrawArraysInstancedARB",
    /*  484 */ "glDrawArraysInstancedBaseInstance",
    /*  485 */ "glDrawArraysInstancedEXT",
    /*  486 */ "glDrawBuffer",
    /*  487 */ "glDrawBuffers",
    /*  488 */ "glDrawBuffersARB",
    /*  489 */ "glDrawBuffersATI",
    /*  490 */ "glDrawCommandsAddressNV",
    /*  491 */ "glDrawCommandsNV",
    /*  492 */ "glDrawCommandsStatesAddressNV",
    /*  493 */ "glDrawCommandsStatesNV",
    /*  494 */ "glDrawElementArrayAPPLE",
    /*  495 */ "glDrawElementArrayATI",
    /*  496 */ "glDrawElements",
    /*  497 */ "glDrawElementsBaseVertex",
    /*  498 */ "glDrawElementsIndirect",
    /*  499 */ "glDrawElementsInstanced",
    /*  500 */ "glDrawElementsInstancedARB",
    /*  501 */ "glDrawElementsInstancedBaseInstance",
    /*  502 */ "glDrawElementsInstancedBaseVertex",
    /*  503 */ "glDrawElementsInstancedBaseVertexBaseInstance",
    /*  504 */ "glDrawElementsInstancedEXT",
    /*  505 */ "glDrawMeshArraysSUN",
    /*  506 */ "glDrawMeshTasksIndirectNV",
    /*  507 */ "glDrawMeshTasksNV",
    /*  508 */ "glDrawPixels",
    /*  509 */ "glDrawRangeElementArrayAPPLE",
    /*  510 */ "glDrawRangeElementArrayATI",
    /*  511 */ "glDrawRangeElements",
    /*  512 */ "glDrawRangeElementsBaseVertex",
    /*  513 */ "glDrawRangeElementsEXT",
    /*  514 */ "glDrawTextureNV",
    /*  515 */ "glDrawTransformFeedback",
    /*  516 */ "glDrawTransformFeedbackInstanced",
    /*  517 */ "glDrawTransformFeedbackNV",
    /*  518 */ "glDrawTransformFeedbackStream",
    /*  519 */ "glDrawTransformFeedbackStreamInstanced",
    /*  520 */ "glDrawVkImageNV",
    /*  521 */ "glEGLImageTargetTexStorageEXT",
    /*  522 */ "glEGLImageTargetTextureStorageEXT",
    /*  523 */ "glEdgeFlag",
    /*  524 */ "glEdgeFlagFormatNV",
    /*  525 */ "glEdgeFlagPointer",
    /*  526 */ "glEdgeFlagPointerEXT",
    /*  527 */ "glEdgeFlagPointerListIBM",
    /*  528 */ "glEdgeFlagv",
    /*  529 */ "glElementPointerAPPLE",
    /*  530 */ "glElementPointerATI",
    /*  531 */ "glEnable",
    /*  532 */ "glEnableClientState",
    /*  533 */ "glEnableClientStateIndexedEXT",
    /*  534 */ "glEnableClientStateiEXT",
    /*  535 */ "glEnableIndexedEXT",
    /*  536 */ "glEnableVariantClientStateEXT",
    /*  537 */ "glEnableVertexArrayAttrib",
    /*  538 */ "glEnableVertexArrayAttribEXT",
    /*  539 */ "glEnableVertexArrayEXT",
    /*  540 */ "glEnableVertexAttribAPPLE",
    /*  541 */ "glEnableVertexAttribArray",
    /*  542 */ "glEnableVertexAttribArrayARB",
    /*  543 */ "glEnablei",
    /*  544 */ "glEnd",
    /*  545 */ "glEndConditionalRender",
    /*  546 */ "glEndConditionalRenderNV",
    /*  547 */ "glEndConditionalRenderNVX",
    /*  548 */ "glEndFragmentShaderATI",
    /*  549 */ "glEndList",
    /*  550 */ "glEndOcclusionQueryNV",
    /*  551 */ "glEndPerfMonitorAMD",
    /*  552 */ "glEndPerfQueryINTEL",
    /*  553 */ "glEndQuery",
    /*  554 */ "glEndQueryARB",
    /*  555 */ "glEndQueryIndexed",
    /*  556 */ "glEndTransformFeedback",
    /*  557 */ "glEndTransformFeedbackEXT",
    /*  558 */ "glEndTransformFeedbackNV",
    /*  559 */ "glEndVertexShaderEXT",
    /*  560 */ "glEndVideoCaptureNV",
    /*  561 */ "glEvalCoord1d",
    /*  562 */ "glEvalCoord1dv",
    /*  563 */ "glEvalCoord1f",
    /*  564 */ "glEvalCoord1fv",
    /*  565 */ "glEvalCoord1xOES",
    /*  566 */ "glEvalCoord1xvOES",
    /*  567 */ "glEvalCoord2d",
    /*  568 */ "glEvalCoord2dv",
    /*  569 */ "glEvalCoord2f",
    /*  570 */ "glEvalCoord2fv",
    /*  571 */ "glEvalCoord2xOES",
    /*  572 */ "glEvalCoord2xvOES",
    /*  573 */ "glEvalMapsNV",
    /*  574 */ "glEvalMesh1",
    /*  575 */ "glEvalMesh2",
    /*  576 */ "glEvalPoint1",
    /*  577 */ "glEvalPoint2",
    /*  578 */ "glEvaluateDepthValuesARB",
    /*  579 */ "glExecuteProgramNV",
    /*  580 */ "glExtractComponentEXT",
    /*  581 */ "glFeedbackBuffer",
    /*  582 */ "glFeedbackBufferxOES",
    /*  583 */ "glFenceSync",
    /*  584 */ "glFinalCombinerInputNV",
    /*  585 */ "glFinish",
    /*  586 */ "glFinishAsyncSGIX",
    /*  587 */ "glFinishFenceAPPLE",
    /*  588 */ "glFinishFenceNV",
    /*  589 */ "glFinishObjectAPPLE",
    /*  590 */ "glFinishTextureSUNX",
    /*  591 */ "glFlush",
    /*  592 */ "glFlushMappedBufferRange",
    /*  593 */ "glFlushMappedBufferRangeAPPLE",
    /*  594 */ "glFlushMappedNamedBufferRange",
    /*  595 */ "glFlushMappedNamedBufferRangeEXT",
    /*  596 */ "glFlushPixelDataRangeNV",
    /*  597 */ "glFlushRasterSGIX",
    /*  598 */ "glFlushStaticDataIBM",
    /*  599 */ "glFlushVertexArrayRangeAPPLE",
    /*  600 */ "glFlushVertexArrayRangeNV",
    /*  601 */ "glFogCoordFormatNV",
    /*  602 */ "glFogCoordPointer",
    /*  603 */ "glFogCoordPointerEXT",
    /*  604 */ "glFogCoordPointerListIBM",
    /*  605 */ "glFogCoordd",
    /*  606 */ "glFogCoorddEXT",
    /*  607 */ "glFogCoorddv",
    /*  608 */ "glFogCoorddvEXT",
    /*  609 */ "glFogCoordf",
    /*  610 */ "glFogCoordfEXT",
    /*  611 */ "glFogCoordfv",
    /*  612 */ "glFogCoordfvEXT",
    /*  613 */ "glFogCoordhNV",
    /*  614 */ "glFogCoordhvNV",
    /*  615 */ "glFogFuncSGIS",
    /*  616 */ "glFogf",
    /*  617 */ "glFogfv",
    /*  618 */ "glFogi",
    /*  619 */ "glFogiv",
    /*  620 */ "glFogxOES",
    /*  621 */ "glFogxvOES",
    /*  622 */ "glFragmentColorMaterialSGIX",
    /*  623 */ "glFragmentCoverageColorNV",
    /*  624 */ "glFragmentLightModelfSGIX",
    /*  625 */ "glFragmentLightModelfvSGIX",
    /*  626 */ "glFragmentLightModeliSGIX",
    /*  627 */ "glFragmentLightModelivSGIX",
    /*  628 */ "glFragmentLightfSGIX",
    /*  629 */ "glFragmentLightfvSGIX",
    /*  630 */ "glFragmentLightiSGIX",
    /*  631 */ "glFragmentLightivSGIX",
    /*  632 */ "glFragmentMaterialfSGIX",
    /*  633 */ "glFragmentMaterialfvSGIX",
    /*  634 */ "glFragmentMaterialiSGIX",
    /*  635 */ "glFragmentMaterialivSGIX",
    /*  636 */ "glFrameTerminatorGREMEDY",
    /*  637 */ "glFrameZoomSGIX",
    /*  638 */ "glFramebufferDrawBufferEXT",
    /*  639 */ "glFramebufferDrawBuffersEXT",
    /*  640 */ "glFramebufferFetchBarrierEXT",
    /*  641 */ "glFramebufferParameteri",
    /*  642 */ "glFramebufferParameteriMESA",
    /*  643 */ "glFramebufferReadBufferEXT",
    /*  644 */ "glFramebufferRenderbuffer",
    /*  645 */ "glFramebufferRenderbufferEXT",
    /*  646 */ "glFramebufferSampleLocationsfvARB",
    /*  647 */ "glFramebufferSampleLocationsfvNV",
    /*  648 */ "glFramebufferSamplePositionsfvAMD",
    /*  649 */ "glFramebufferTexture",
    /*  650 */ "glFramebufferTexture1D",
    /*  651 */ "glFramebufferTexture1DEXT",
    /*  652 */ "glFramebufferTexture2D",
    /*  653 */ "glFramebufferTexture2DEXT",
    /*  654 */ "glFramebufferTexture3D",
    /*  655 */ "glFramebufferTexture3DEXT",
    /*  656 */ "glFramebufferTextureARB",
    /*  657 */ "glFramebufferTextureEXT",
    /*  658 */ "glFramebufferTextureFaceARB",
    /*  659 */ "glFramebufferTextureFaceEXT",
    /*  660 */ "glFramebufferTextureLayer",
    /*  661 */ "glFramebufferTextureLayerARB",
    /*  662 */ "glFramebufferTextureLayerEXT",
    /*  663 */ "glFramebufferTextureMultiviewOVR",
    /*  664 */ "glFreeObjectBufferATI",
    /*  665 */ "glFrontFace",
    /*  666 */ "glFrustum",
    /*  667 */ "glFrustumfOES",
    /*  668 */ "glFrustumxOES",
    /*  669 */ "glGenAsyncMarkersSGIX",
    /*  670 */ "glGenBuffers",
    /*  671 */ "glGenBuffersARB",
    /*  672 */ "glGenFencesAPPLE",
    /*  673 */ "glGenFencesNV",
    /*  674 */ "glGenFragmentShadersATI",
    /*  675 */ "glGenFramebuffers",
    /*  676 */ "glGenFramebuffersEXT",
    /*  677 */ "glGenLists",
    /*  678 */ "glGenNamesAMD",
    /*  679 */ "glGenOcclusionQueriesNV",
    /*  680 */ "glGenPathsNV",
    /*  681 */ "glGenPerfMonitorsAMD",
    /*  682 */ "glGenProgramPipelines",
    /*  683 */ "glGenProgramsARB",
    /*  684 */ "glGenProgramsNV",
    /*  685 */ "glGenQueries",
    /*  686 */ "glGenQueriesARB",
    /*  687 */ "glGenQueryResourceTagNV",
    /*  688 */ "glGenRenderbuffers",
    /*  689 */ "glGenRenderbuffersEXT",
    /*  690 */ "glGenSamplers",
    /*  691 */ "glGenSemaphoresEXT",
    /*  692 */ "glGenSymbolsEXT",
    /*  693 */ "glGenTextures",
    /*  694 */ "glGenTexturesEXT",
    /*  695 */ "glGenTransformFeedbacks",
    /*  696 */ "glGenTransformFeedbacksNV",
    /*  697 */ "glGenVertexArrays",
    /*  698 */ "glGenVertexArraysAPPLE",
    /*  699 */ "glGenVertexShadersEXT",
    /*  700 */ "glGenerateMipmap",
    /*  701 */ "glGenerateMipmapEXT",
    /*  702 */ "glGenerateMultiTexMipmapEXT",
    /*  703 */ "glGenerateTextureMipmap",
    /*  704 */ "glGenerateTextureMipmapEXT",
    /*  705 */ "glGetActiveAtomicCounterBufferiv",
    /*  706 */ "glGetActiveAttrib",
    /*  707 */ "glGetActiveAttribARB",
    /*  708 */ "glGetActiveSubroutineName",
    /*  709 */ "glGetActiveSubroutineUniformName",
    /*  710 */ "glGetActiveSubroutineUniformiv",
    /*  711 */ "glGetActiveUniform",
    /*  712 */ "glGetActiveUniformARB",
    /*  713 */ "glGetActiveUniformBlockName",
    /*  714 */ "glGetActiveUniformBlockiv",
    /*  715 */ "glGetActiveUniformName",
    /*  716 */ "glGetActiveUniformsiv",
    /*  717 */ "glGetActiveVaryingNV",
    /*  718 */ "glGetArrayObjectfvATI",
    /*  719 */ "glGetArrayObjectivATI",
    /*  720 */ "glGetAttachedObjectsARB",
    /*  721 */ "glGetAttachedShaders",
    /*  722 */ "glGetAttribLocation",
    /*  723 */ "glGetAttribLocationARB",
    /*  724 */ "glGetBooleanIndexedvEXT",
    /*  725 */ "glGetBooleani_v",
    /*  726 */ "glGetBooleanv",
    /*  727 */ "glGetBufferParameteri64v",
    /*  728 */ "glGetBufferParameteriv",
    /*  729 */ "glGetBufferParameterivARB",
    /*  730 */ "glGetBufferParameterui64vNV",
    /*  731 */ "glGetBufferPointerv",
    /*  732 */ "glGetBufferPointervARB",
    /*  733 */ "glGetBufferSubData",
    /*  734 */ "glGetBufferSubDataARB",
    /*  735 */ "glGetClipPlane",
    /*  736 */ "glGetClipPlanefOES",
    /*  737 */ "glGetClipPlanexOES",
    /*  738 */ "glGetColorTable",
    /*  739 */ "glGetColorTableEXT",
    /*  740 */ "glGetColorTableParameterfv",
    /*  741 */ "glGetColorTableParameterfvEXT",
    /*  742 */ "glGetColorTableParameterfvSGI",
    /*  743 */ "glGetColorTableParameteriv",
    /*  744 */ "glGetColorTableParameterivEXT",
    /*  745 */ "glGetColorTableParameterivSGI",
    /*  746 */ "glGetColorTableSGI",
    /*  747 */ "glGetCombinerInputParameterfvNV",
    /*  748 */ "glGetCombinerInputParameterivNV",
    /*  749 */ "glGetCombinerOutputParameterfvNV",
    /*  750 */ "glGetCombinerOutputParameterivNV",
    /*  751 */ "glGetCombinerStageParameterfvNV",
    /*  752 */ "glGetCommandHeaderNV",
    /*  753 */ "glGetCompressedMultiTexImageEXT",
    /*  754 */ "glGetCompressedTexImage",
    /*  755 */ "glGetCompressedTexImageARB",
    /*  756 */ "glGetCompressedTextureImage",
    /*  757 */ "glGetCompressedTextureImageEXT",
    /*  758 */ "glGetCompressedTextureSubImage",
    /*  759 */ "glGetConvolutionFilter",
    /*  760 */ "glGetConvolutionFilterEXT",
    /*  761 */ "glGetConvolutionParameterfv",
    /*  762 */ "glGetConvolutionParameterfvEXT",
    /*  763 */ "glGetConvolutionParameteriv",
    /*  764 */ "glGetConvolutionParameterivEXT",
    /*  765 */ "glGetConvolutionParameterxvOES",
    /*  766 */ "glGetCoverageModulationTableNV",
    /*  767 */ "glGetDebugMessageLog",
    /*  768 */ "glGetDebugMessageLogAMD",
    /*  769 */ "glGetDebugMessageLogARB",
    /*  770 */ "glGetDetailTexFuncSGIS",
    /*  771 */ "glGetDoubleIndexedvEXT",
    /*  772 */ "glGetDoublei_v",
    /*  773 */ "glGetDoublei_vEXT",
    /*  774 */ "glGetDoublev",
    /*  775 */ "glGetError",
    /*  776 */ "glGetFenceivNV",
    /*  777 */ "glGetFinalCombinerInputParameterfvNV",
    /*  778 */ "glGetFinalCombinerInputParameterivNV",
    /*  779 */ "glGetFirstPerfQueryIdINTEL",
    /*  780 */ "glGetFixedvOES",
    /*  781 */ "glGetFloatIndexedvEXT",
    /*  782 */ "glGetFloati_v",
    /*  783 */ "glGetFloati_vEXT",
    /*  784 */ "glGetFloatv",
    /*  785 */ "glGetFogFuncSGIS",
    /*  786 */ "glGetFragDataIndex",
    /*  787 */ "glGetFragDataLocation",
    /*  788 */ "glGetFragDataLocationEXT",
    /*  789 */ "glGetFragmentLightfvSGIX",
    /*  790 */ "glGetFragmentLightivSGIX",
    /*  791 */ "glGetFragmentMaterialfvSGIX",
    /*  792 */ "glGetFragmentMaterialivSGIX",
    /*  793 */ "glGetFramebufferAttachmentParameteriv",
    /*  794 */ "glGetFramebufferAttachmentParameterivEXT",
    /*  795 */ "glGetFramebufferParameterfvAMD",
    /*  796 */ "glGetFramebufferParameteriv",
    /*  797 */ "glGetFramebufferParameterivEXT",
    /*  798 */ "glGetFramebufferParameterivMESA",
    /*  799 */ "glGetGraphicsResetStatus",
    /*  800 */ "glGetGraphicsResetStatusARB",
    /*  801 */ "glGetHandleARB",
    /*  802 */ "glGetHistogram",
    /*  803 */ "glGetHistogramEXT",
    /*  804 */ "glGetHistogramParameterfv",
    /*  805 */ "glGetHistogramParameterfvEXT",
    /*  806 */ "glGetHistogramParameteriv",
    /*  807 */ "glGetHistogramParameterivEXT",
    /*  808 */ "glGetHistogramParameterxvOES",
    /*  809 */ "glGetImageHandleARB",
    /*  810 */ "glGetImageHandleNV",
    /*  811 */ "glGetImageTransformParameterfvHP",
    /*  812 */ "glGetImageTransformParameterivHP",
    /*  813 */ "glGetInfoLogARB",
    /*  814 */ "glGetInstrumentsSGIX",
    /*  815 */ "glGetInteger64i_v",
    /*  816 */ "glGetInteger64v",
    /*  817 */ "glGetIntegerIndexedvEXT",
    /*  818 */ "glGetIntegeri_v",
    /*  819 */ "glGetIntegerui64i_vNV",
    /*  820 */ "glGetIntegerui64vNV",
    /*  821 */ "glGetIntegerv",
    /*  822 */ "glGetInternalformatSampleivNV",
    /*  823 */ "glGetInternalformati64v",
    /*  824 */ "glGetInternalformativ",
    /*  825 */ "glGetInvariantBooleanvEXT",
    /*  826 */ "glGetInvariantFloatvEXT",
    /*  827 */ "glGetInvariantIntegervEXT",
    /*  828 */ "glGetLightfv",
    /*  829 */ "glGetLightiv",
    /*  830 */ "glGetLightxOES",
    /*  831 */ "glGetListParameterfvSGIX",
    /*  832 */ "glGetListParameterivSGIX",
    /*  833 */ "glGetLocalConstantBooleanvEXT",
    /*  834 */ "glGetLocalConstantFloatvEXT",
    /*  835 */ "glGetLocalConstantIntegervEXT",
    /*  836 */ "glGetMapAttribParameterfvNV",
    /*  837 */ "glGetMapAttribParameterivNV",
    /*  838 */ "glGetMapControlPointsNV",
    /*  839 */ "glGetMapParameterfvNV",
    /*  840 */ "glGetMapParameterivNV",
    /*  841 */ "glGetMapdv",
    /*  842 */ "glGetMapfv",
    /*  843 */ "glGetMapiv",
    /*  844 */ "glGetMapxvOES",
    /*  845 */ "glGetMaterialfv",
    /*  846 */ "glGetMaterialiv",
    /*  847 */ "glGetMaterialxOES",
    /*  848 */ "glGetMemoryObjectDetachedResourcesuivNV",
    /*  849 */ "glGetMemoryObjectParameterivEXT",
    /*  850 */ "glGetMinmax",
    /*  851 */ "glGetMinmaxEXT",
    /*  852 */ "glGetMinmaxParameterfv",
    /*  853 */ "glGetMinmaxParameterfvEXT",
    /*  854 */ "glGetMinmaxParameteriv",
    /*  855 */ "glGetMinmaxParameterivEXT",
    /*  856 */ "glGetMultiTexEnvfvEXT",
    /*  857 */ "glGetMultiTexEnvivEXT",
    /*  858 */ "glGetMultiTexGendvEXT",
    /*  859 */ "glGetMultiTexGenfvEXT",
    /*  860 */ "glGetMultiTexGenivEXT",
    /*  861 */ "glGetMultiTexImageEXT",
    /*  862 */ "glGetMultiTexLevelParameterfvEXT",
    /*  863 */ "glGetMultiTexLevelParameterivEXT",
    /*  864 */ "glGetMultiTexParameterIivEXT",
    /*  865 */ "glGetMultiTexParameterIuivEXT",
    /*  866 */ "glGetMultiTexParameterfvEXT",
    /*  867 */ "glGetMultiTexParameterivEXT",
    /*  868 */ "glGetMultisamplefv",
    /*  869 */ "glGetMultisamplefvNV",
    /*  870 */ "glGetNamedBufferParameteri64v",
    /*  871 */ "glGetNamedBufferParameteriv",
    /*  872 */ "glGetNamedBufferParameterivEXT",
    /*  873 */ "glGetNamedBufferParameterui64vNV",
    /*  874 */ "glGetNamedBufferPointerv",
    /*  875 */ "glGetNamedBufferPointervEXT",
    /*  876 */ "glGetNamedBufferSubData",
    /*  877 */ "glGetNamedBufferSubDataEXT",
    /*  878 */ "glGetNamedFramebufferAttachmentParameteriv",
    /*  879 */ "glGetNamedFramebufferAttachmentParameterivEXT",
    /*  880 */ "glGetNamedFramebufferParameterfvAMD",
    /*  881 */ "glGetNamedFramebufferParameteriv",
    /*  882 */ "glGetNamedFramebufferParameterivEXT",
    /*  883 */ "glGetNamedProgramLocalParameterIivEXT",
    /*  884 */ "glGetNamedProgramLocalParameterIuivEXT",
    /*  885 */ "glGetNamedProgramLocalParameterdvEXT",
    /*  886 */ "glGetNamedProgramLocalParameterfvEXT",
    /*  887 */ "glGetNamedProgramStringEXT",
    /*  888 */ "glGetNamedProgramivEXT",
    /*  889 */ "glGetNamedRenderbufferParameteriv",
    /*  890 */ "glGetNamedRenderbufferParameterivEXT",
    /*  891 */ "glGetNamedStringARB",
    /*  892 */ "glGetNamedStringivARB",
    /*  893 */ "glGetNextPerfQueryIdINTEL",
    /*  894 */ "glGetObjectBufferfvATI",
    /*  895 */ "glGetObjectBufferivATI",
    /*  896 */ "glGetObjectLabel",
    /*  897 */ "glGetObjectLabelEXT",
    /*  898 */ "glGetObjectParameterfvARB",
    /*  899 */ "glGetObjectParameterivAPPLE",
    /*  900 */ "glGetObjectParameterivARB",
    /*  901 */ "glGetObjectPtrLabel",
    /*  902 */ "glGetOcclusionQueryivNV",
    /*  903 */ "glGetOcclusionQueryuivNV",
    /*  904 */ "glGetPathColorGenfvNV",
    /*  905 */ "glGetPathColorGenivNV",
    /*  906 */ "glGetPathCommandsNV",
    /*  907 */ "glGetPathCoordsNV",
    /*  908 */ "glGetPathDashArrayNV",
    /*  909 */ "glGetPathLengthNV",
    /*  910 */ "glGetPathMetricRangeNV",
    /*  911 */ "glGetPathMetricsNV",
    /*  912 */ "glGetPathParameterfvNV",
    /*  913 */ "glGetPathParameterivNV",
    /*  914 */ "glGetPathSpacingNV",
    /*  915 */ "glGetPathTexGenfvNV",
    /*  916 */ "glGetPathTexGenivNV",
    /*  917 */ "glGetPerfCounterInfoINTEL",
    /*  918 */ "glGetPerfMonitorCounterDataAMD",
    /*  919 */ "glGetPerfMonitorCounterInfoAMD",
    /*  920 */ "glGetPerfMonitorCounterStringAMD",
    /*  921 */ "glGetPerfMonitorCountersAMD",
    /*  922 */ "glGetPerfMonitorGroupStringAMD",
    /*  923 */ "glGetPerfMonitorGroupsAMD",
    /*  924 */ "glGetPerfQueryDataINTEL",
    /*  925 */ "glGetPerfQueryIdByNameINTEL",
    /*  926 */ "glGetPerfQueryInfoINTEL",
    /*  927 */ "glGetPixelMapfv",
    /*  928 */ "glGetPixelMapuiv",
    /*  929 */ "glGetPixelMapusv",
    /*  930 */ "glGetPixelMapxv",
    /*  931 */ "glGetPixelTexGenParameterfvSGIS",
    /*  932 */ "glGetPixelTexGenParameterivSGIS",
    /*  933 */ "glGetPixelTransformParameterfvEXT",
    /*  934 */ "glGetPixelTransformParameterivEXT",
    /*  935 */ "glGetPointerIndexedvEXT",
    /*  936 */ "glGetPointeri_vEXT",
    /*  937 */ "glGetPointerv",
    /*  938 */ "glGetPointervEXT",
    /*  939 */ "glGetPolygonStipple",
    /*  940 */ "glGetProgramBinary",
    /*  941 */ "glGetProgramEnvParameterIivNV",
    /*  942 */ "glGetProgramEnvParameterIuivNV",
    /*  943 */ "glGetProgramEnvParameterdvARB",
    /*  944 */ "glGetProgramEnvParameterfvARB",
    /*  945 */ "glGetProgramInfoLog",
    /*  946 */ "glGetProgramInterfaceiv",
    /*  947 */ "glGetProgramLocalParameterIivNV",
    /*  948 */ "glGetProgramLocalParameterIuivNV",
    /*  949 */ "glGetProgramLocalParameterdvARB",
    /*  950 */ "glGetProgramLocalParameterfvARB",
    /*  951 */ "glGetProgramNamedParameterdvNV",
    /*  952 */ "glGetProgramNamedParameterfvNV",
    /*  953 */ "glGetProgramParameterdvNV",
    /*  954 */ "glGetProgramParameterfvNV",
    /*  955 */ "glGetProgramPipelineInfoLog",
    /*  956 */ "glGetProgramPipelineiv",
    /*  957 */ "glGetProgramResourceIndex",
    /*  958 */ "glGetProgramResourceLocation",
    /*  959 */ "glGetProgramResourceLocationIndex",
    /*  960 */ "glGetProgramResourceName",
    /*  961 */ "glGetProgramResourcefvNV",
    /*  962 */ "glGetProgramResourceiv",
    /*  963 */ "glGetProgramStageiv",
    /*  964 */ "glGetProgramStringARB",
    /*  965 */ "glGetProgramStringNV",
    /*  966 */ "glGetProgramSubroutineParameteruivNV",
    /*  967 */ "glGetProgramiv",
    /*  968 */ "glGetProgramivARB",
    /*  969 */ "glGetProgramivNV",
    /*  970 */ "glGetQueryBufferObjecti64v",
    /*  971 */ "glGetQueryBufferObjectiv",
    /*  972 */ "glGetQueryBufferObjectui64v",
    /*  973 */ "glGetQueryBufferObjectuiv",
    /*  974 */ "glGetQueryIndexediv",
    /*  975 */ "glGetQueryObjecti64v",
    /*  976 */ "glGetQueryObjecti64vEXT",
    /*  977 */ "glGetQueryObjectiv",
    /*  978 */ "glGetQueryObjectivARB",
    /*  979 */ "glGetQueryObjectui64v",
    /*  980 */ "glGetQueryObjectui64vEXT",
    /*  981 */ "glGetQueryObjectuiv",
    /*  982 */ "glGetQueryObjectuivARB",
    /*  983 */ "glGetQueryiv",
    /*  984 */ "glGetQueryivARB",
    /*  985 */ "glGetRenderbufferParameteriv",
    /*  986 */ "glGetRenderbufferParameterivEXT",
    /*  987 */ "glGetSamplerParameterIiv",
    /*  988 */ "glGetSamplerParameterIuiv",
    /*  989 */ "glGetSamplerParameterfv",
    /*  990 */ "glGetSamplerParameteriv",
    /*  991 */ "glGetSemaphoreParameterivNV",
    /*  992 */ "glGetSemaphoreParameterui64vEXT",
    /*  993 */ "glGetSeparableFilter",
    /*  994 */ "glGetSeparableFilterEXT",
    /*  995 */ "glGetShaderInfoLog",
    /*  996 */ "glGetShaderPrecisionFormat",
    /*  997 */ "glGetShaderSource",
    /*  998 */ "glGetShaderSourceARB",
    /*  999 */ "glGetShaderiv",
    /* 1000 */ "glGetShadingRateImagePaletteNV",
    /* 1001 */ "glGetShadingRateSampleLocationivNV",
    /* 1002 */ "glGetSharpenTexFuncSGIS",
    /* 1003 */ "glGetStageIndexNV",
    /* 1004 */ "glGetString",
    /* 1005 */ "glGetStringi",
    /* 1006 */ "glGetSubroutineIndex",
    /* 1007 */ "glGetSubroutineUniformLocation",
    /* 1008 */ "glGetSynciv",
    /* 1009 */ "glGetTexBumpParameterfvATI",
    /* 1010 */ "glGetTexBumpParameterivATI",
    /* 1011 */ "glGetTexEnvfv",
    /* 1012 */ "glGetTexEnviv",
    /* 1013 */ "glGetTexEnvxvOES",
    /* 1014 */ "glGetTexFilterFuncSGIS",
    /* 1015 */ "glGetTexGendv",
    /* 1016 */ "glGetTexGenfv",
    /* 1017 */ "glGetTexGeniv",
    /* 1018 */ "glGetTexGenxvOES",
    /* 1019 */ "glGetTexImage",
    /* 1020 */ "glGetTexLevelParameterfv",
    /* 1021 */ "glGetTexLevelParameteriv",
    /* 1022 */ "glGetTexLevelParameterxvOES",
    /* 1023 */ "glGetTexParameterIiv",
    /* 1024 */ "glGetTexParameterIivEXT",
    /* 1025 */ "glGetTexParameterIuiv",
    /* 1026 */ "glGetTexParameterIuivEXT",
    /* 1027 */ "glGetTexParameterPointervAPPLE",
    /* 1028 */ "glGetTexParameterfv",
    /* 1029 */ "glGetTexParameteriv",
    /* 1030 */ "glGetTexParameterxvOES",
    /* 1031 */ "glGetTextureHandleARB",
    /* 1032 */ "glGetTextureHandleNV",
    /* 1033 */ "glGetTextureImage",
    /* 1034 */ "glGetTextureImageEXT",
    /* 1035 */ "glGetTextureLevelParameterfv",
    /* 1036 */ "glGetTextureLevelParameterfvEXT",
    /* 1037 */ "glGetTextureLevelParameteriv",
    /* 1038 */ "glGetTextureLevelParameterivEXT",
    /* 1039 */ "glGetTextureParameterIiv",
    /* 1040 */ "glGetTextureParameterIivEXT",
    /* 1041 */ "glGetTextureParameterIuiv",
    /* 1042 */ "glGetTextureParameterIuivEXT",
    /* 1043 */ "glGetTextureParameterfv",
    /* 1044 */ "glGetTextureParameterfvEXT",
    /* 1045 */ "glGetTextureParameteriv",
    /* 1046 */ "glGetTextureParameterivEXT",
    /* 1047 */ "glGetTextureSamplerHandleARB",
    /* 1048 */ "glGetTextureSamplerHandleNV",
    /* 1049 */ "glGetTextureSubImage",
    /* 1050 */ "glGetTrackMatrixivNV",
    /* 1051 */ "glGetTransformFeedbackVarying",
    /* 1052 */ "glGetTransformFeedbackVaryingEXT",
    /* 1053 */ "glGetTransformFeedbackVaryingNV",
    /* 1054 */ "glGetTransformFeedbacki64_v",
    /* 1055 */ "glGetTransformFeedbacki_v",
    /* 1056 */ "glGetTransformFeedbackiv",
    /* 1057 */ "glGetUniformBlockIndex",
    /* 1058 */ "glGetUniformBufferSizeEXT",
    /* 1059 */ "glGetUniformIndices",
    /* 1060 */ "glGetUniformLocation",
    /* 1061 */ "glGetUniformLocationARB",
    /* 1062 */ "glGetUniformOffsetEXT",
    /* 1063 */ "glGetUniformSubroutineuiv",
    /* 1064 */ "glGetUniformdv",
    /* 1065 */ "glGetUniformfv",
    /* 1066 */ "glGetUniformfvARB",
    /* 1067 */ "glGetUniformi64vARB",
    /* 1068 */ "glGetUniformi64vNV",
    /* 1069 */ "glGetUniformiv",
    /* 1070 */ "glGetUniformivARB",
    /* 1071 */ "glGetUniformui64vARB",
    /* 1072 */ "glGetUniformui64vNV",
    /* 1073 */ "glGetUniformuiv",
    /* 1074 */ "glGetUniformuivEXT",
    /* 1075 */ "glGetUnsignedBytei_vEXT",
    /* 1076 */ "glGetUnsignedBytevEXT",
    /* 1077 */ "glGetVariantArrayObjectfvATI",
    /* 1078 */ "glGetVariantArrayObjectivATI",
    /* 1079 */ "glGetVariantBooleanvEXT",
    /* 1080 */ "glGetVariantFloatvEXT",
    /* 1081 */ "glGetVariantIntegervEXT",
    /* 1082 */ "glGetVariantPointervEXT",
    /* 1083 */ "glGetVaryingLocationNV",
    /* 1084 */ "glGetVertexArrayIndexed64iv",
    /* 1085 */ "glGetVertexArrayIndexediv",
    /* 1086 */ "glGetVertexArrayIntegeri_vEXT",
    /* 1087 */ "glGetVertexArrayIntegervEXT",
    /* 1088 */ "glGetVertexArrayPointeri_vEXT",
    /* 1089 */ "glGetVertexArrayPointervEXT",
    /* 1090 */ "glGetVertexArrayiv",
    /* 1091 */ "glGetVertexAttribArrayObjectfvATI",
    /* 1092 */ "glGetVertexAttribArrayObjectivATI",
    /* 1093 */ "glGetVertexAttribIiv",
    /* 1094 */ "glGetVertexAttribIivEXT",
    /* 1095 */ "glGetVertexAttribIuiv",
    /* 1096 */ "glGetVertexAttribIuivEXT",
    /* 1097 */ "glGetVertexAttribLdv",
    /* 1098 */ "glGetVertexAttribLdvEXT",
    /* 1099 */ "glGetVertexAttribLi64vNV",
    /* 1100 */ "glGetVertexAttribLui64vARB",
    /* 1101 */ "glGetVertexAttribLui64vNV",
    /* 1102 */ "glGetVertexAttribPointerv",
    /* 1103 */ "glGetVertexAttribPointervARB",
    /* 1104 */ "glGetVertexAttribPointervNV",
    /* 1105 */ "glGetVertexAttribdv",
    /* 1106 */ "glGetVertexAttribdvARB",
    /* 1107 */ "glGetVertexAttribdvNV",
    /* 1108 */ "glGetVertexAttribfv",
    /* 1109 */ "glGetVertexAttribfvARB",
    /* 1110 */ "glGetVertexAttribfvNV",
    /* 1111 */ "glGetVertexAttribiv",
    /* 1112 */ "glGetVertexAttribivARB",
    /* 1113 */ "glGetVertexAttribivNV",
    /* 1114 */ "glGetVideoCaptureStreamdvNV",
    /* 1115 */ "glGetVideoCaptureStreamfvNV",
    /* 1116 */ "glGetVideoCaptureStreamivNV",
    /* 1117 */ "glGetVideoCaptureivNV",
    /* 1118 */ "glGetVideoi64vNV",
    /* 1119 */ "glGetVideoivNV",
    /* 1120 */ "glGetVideoui64vNV",
    /* 1121 */ "glGetVideouivNV",
    /* 1122 */ "glGetVkProcAddrNV",
    /* 1123 */ "glGetnColorTable",
    /* 1124 */ "glGetnColorTableARB",
    /* 1125 */ "glGetnCompressedTexImage",
    /* 1126 */ "glGetnCompressedTexImageARB",
    /* 1127 */ "glGetnConvolutionFilter",
    /* 1128 */ "glGetnConvolutionFilterARB",
    /* 1129 */ "glGetnHistogram",
    /* 1130 */ "glGetnHistogramARB",
    /* 1131 */ "glGetnMapdv",
    /* 1132 */ "glGetnMapdvARB",
    /* 1133 */ "glGetnMapfv",
    /* 1134 */ "glGetnMapfvARB",
    /* 1135 */ "glGetnMapiv",
    /* 1136 */ "glGetnMapivARB",
    /* 1137 */ "glGetnMinmax",
    /* 1138 */ "glGetnMinmaxARB",
    /* 1139 */ "glGetnPixelMapfv",
    /* 1140 */ "glGetnPixelMapfvARB",
    /* 1141 */ "glGetnPixelMapuiv",
    /* 1142 */ "glGetnPixelMapuivARB",
    /* 1143 */ "glGetnPixelMapusv",
    /* 1144 */ "glGetnPixelMapusvARB",
    /* 1145 */ "glGetnPolygonStipple",
    /* 1146 */ "glGetnPolygonStippleARB",
    /* 1147 */ "glGetnSeparableFilter",
    /* 1148 */ "glGetnSeparableFilterARB",
    /* 1149 */ "glGetnTexImage",
    /* 1150 */ "glGetnTexImageARB",
    /* 1151 */ "glGetnUniformdv",
    /* 1152 */ "glGetnUniformdvARB",
    /* 1153 */ "glGetnUniformfv",
    /* 1154 */ "glGetnUniformfvARB",
    /* 1155 */ "glGetnUniformi64vARB",
    /* 1156 */ "glGetnUniformiv",
    /* 1157 */ "glGetnUniformivARB",
    /* 1158 */ "glGetnUniformui64vARB",
    /* 1159 */ "glGetnUniformuiv",
    /* 1160 */ "glGetnUniformuivARB",
    /* 1161 */ "glGlobalAlphaFactorbSUN",
    /* 1162 */ "glGlobalAlphaFactordSUN",
    /* 1163 */ "glGlobalAlphaFactorfSUN",
    /* 1164 */ "glGlobalAlphaFactoriSUN",
    /* 1165 */ "glGlobalAlphaFactorsSUN",
    /* 1166 */ "glGlobalAlphaFactorubSUN",
    /* 1167 */ "glGlobalAlphaFactoruiSUN",
    /* 1168 */ "glGlobalAlphaFactorusSUN",
    /* 1169 */ "glHint",
    /* 1170 */ "glHintPGI",
    /* 1171 */ "glHistogram",
    /* 1172 */ "glHistogramEXT",
    /* 1173 */ "glIglooInterfaceSGIX",
    /* 1174 */ "glImageTransformParameterfHP",
    /* 1175 */ "glImageTransformParameterfvHP",
    /* 1176 */ "glImageTransformParameteriHP",
    /* 1177 */ "glImageTransformParameterivHP",
    /* 1178 */ "glImportMemoryFdEXT",
    /* 1179 */ "glImportMemoryWin32HandleEXT",
    /* 1180 */ "glImportMemoryWin32NameEXT",
    /* 1181 */ "glImportMemoryZirconHandleANGLE",
    /* 1182 */ "glImportSemaphoreFdEXT",
    /* 1183 */ "glImportSemaphoreWin32HandleEXT",
    /* 1184 */ "glImportSemaphoreWin32NameEXT",
    /* 1185 */ "glImportSemaphoreZirconHandleANGLE",
    /* 1186 */ "glImportSyncEXT",
    /* 1187 */ "glIndexFormatNV",
    /* 1188 */ "glIndexFuncEXT",
    /* 1189 */ "glIndexMask",
    /* 1190 */ "glIndexMaterialEXT",
    /* 1191 */ "glIndexPointer",
    /* 1192 */ "glIndexPointerEXT",
    /* 1193 */ "glIndexPointerListIBM",
    /* 1194 */ "glIndexd",
    /* 1195 */ "glIndexdv",
    /* 1196 */ "glIndexf",
    /* 1197 */ "glIndexfv",
    /* 1198 */ "glIndexi",
    /* 1199 */ "glIndexiv",
    /* 1200 */ "glIndexs",
    /* 1201 */ "glIndexsv",
    /* 1202 */ "glIndexub",
    /* 1203 */ "glIndexubv",
    /* 1204 */ "glIndexxOES",
    /* 1205 */ "glIndexxvOES",
    /* 1206 */ "glInitNames",
    /* 1207 */ "glInsertComponentEXT",
    /* 1208 */ "glInsertEventMarkerEXT",
    /* 1209 */ "glInstrumentsBufferSGIX",
    /* 1210 */ "glInterleavedArrays",
    /* 1211 */ "glInterpolatePathsNV",
    /* 1212 */ "glInvalidateBufferData",
    /* 1213 */ "glInvalidateBufferSubData",
    /* 1214 */ "glInvalidateFramebuffer",
    /* 1215 */ "glInvalidateNamedFramebufferData",
    /* 1216 */ "glInvalidateNamedFramebufferSubData",
    /* 1217 */ "glInvalidateSubFramebuffer",
    /* 1218 */ "glInvalidateTexImage",
    /* 1219 */ "glInvalidateTexSubImage",
    /* 1220 */ "glInvalidateTextureANGLE",
    /* 1221 */ "glIsAsyncMarkerSGIX",
    /* 1222 */ "glIsBuffer",
    /* 1223 */ "glIsBufferARB",
    /* 1224 */ "glIsBufferResidentNV",
    /* 1225 */ "glIsCommandListNV",
    /* 1226 */ "glIsEnabled",
    /* 1227 */ "glIsEnabledIndexedEXT",
    /* 1228 */ "glIsEnabledi",
    /* 1229 */ "glIsFenceAPPLE",
    /* 1230 */ "glIsFenceNV",
    /* 1231 */ "glIsFramebuffer",
    /* 1232 */ "glIsFramebufferEXT",
    /* 1233 */ "glIsImageHandleResidentARB",
    /* 1234 */ "glIsImageHandleResidentNV",
    /* 1235 */ "glIsList",
    /* 1236 */ "glIsMemoryObjectEXT",
    /* 1237 */ "glIsNameAMD",
    /* 1238 */ "glIsNamedBufferResidentNV",
    /* 1239 */ "glIsNamedStringARB",
    /* 1240 */ "glIsObjectBufferATI",
    /* 1241 */ "glIsOcclusionQueryNV",
    /* 1242 */ "glIsPathNV",
    /* 1243 */ "glIsPointInFillPathNV",
    /* 1244 */ "glIsPointInStrokePathNV",
    /* 1245 */ "glIsProgram",
    /* 1246 */ "glIsProgramARB",
    /* 1247 */ "glIsProgramNV",
    /* 1248 */ "glIsProgramPipeline",
    /* 1249 */ "glIsQuery",
    /* 1250 */ "glIsQueryARB",
    /* 1251 */ "glIsRenderbuffer",
    /* 1252 */ "glIsRenderbufferEXT",
    /* 1253 */ "glIsSampler",
    /* 1254 */ "glIsSemaphoreEXT",
    /* 1255 */ "glIsShader",
    /* 1256 */ "glIsStateNV",
    /* 1257 */ "glIsSync",
    /* 1258 */ "glIsTexture",
    /* 1259 */ "glIsTextureEXT",
    /* 1260 */ "glIsTextureHandleResidentARB",
    /* 1261 */ "glIsTextureHandleResidentNV",
    /* 1262 */ "glIsTransformFeedback",
    /* 1263 */ "glIsTransformFeedbackNV",
    /* 1264 */ "glIsVariantEnabledEXT",
    /* 1265 */ "glIsVertexArray",
    /* 1266 */ "glIsVertexArrayAPPLE",
    /* 1267 */ "glIsVertexAttribEnabledAPPLE",
    /* 1268 */ "glLGPUCopyImageSubDataNVX",
    /* 1269 */ "glLGPUInterlockNVX",
    /* 1270 */ "glLGPUNamedBufferSubDataNVX",
    /* 1271 */ "glLabelObjectEXT",
    /* 1272 */ "glLightEnviSGIX",
    /* 1273 */ "glLightModelf",
    /* 1274 */ "glLightModelfv",
    /* 1275 */ "glLightModeli",
    /* 1276 */ "glLightModeliv",
    /* 1277 */ "glLightModelxOES",
    /* 1278 */ "glLightModelxvOES",
    /* 1279 */ "glLightf",
    /* 1280 */ "glLightfv",
    /* 1281 */ "glLighti",
    /* 1282 */ "glLightiv",
    /* 1283 */ "glLightxOES",
    /* 1284 */ "glLightxvOES",
    /* 1285 */ "glLineStipple",
    /* 1286 */ "glLineWidth",
    /* 1287 */ "glLineWidthxOES",
    /* 1288 */ "glLinkProgram",
    /* 1289 */ "glLinkProgramARB",
    /* 1290 */ "glListBase",
    /* 1291 */ "glListDrawCommandsStatesClientNV",
    /* 1292 */ "glListParameterfSGIX",
    /* 1293 */ "glListParameterfvSGIX",
    /* 1294 */ "glListParameteriSGIX",
    /* 1295 */ "glListParameterivSGIX",
    /* 1296 */ "glLoadIdentity",
    /* 1297 */ "glLoadIdentityDeformationMapSGIX",
    /* 1298 */ "glLoadMatrixd",
    /* 1299 */ "glLoadMatrixf",
    /* 1300 */ "glLoadMatrixxOES",
    /* 1301 */ "glLoadName",
    /* 1302 */ "glLoadProgramNV",
    /* 1303 */ "glLoadTransposeMatrixd",
    /* 1304 */ "glLoadTransposeMatrixdARB",
    /* 1305 */ "glLoadTransposeMatrixf",
    /* 1306 */ "glLoadTransposeMatrixfARB",
    /* 1307 */ "glLoadTransposeMatrixxOES",
    /* 1308 */ "glLockArraysEXT",
    /* 1309 */ "glLogicOp",
    /* 1310 */ "glMakeBufferNonResidentNV",
    /* 1311 */ "glMakeBufferResidentNV",
    /* 1312 */ "glMakeImageHandleNonResidentARB",
    /* 1313 */ "glMakeImageHandleNonResidentNV",
    /* 1314 */ "glMakeImageHandleResidentARB",
    /* 1315 */ "glMakeImageHandleResidentNV",
    /* 1316 */ "glMakeNamedBufferNonResidentNV",
    /* 1317 */ "glMakeNamedBufferResidentNV",
    /* 1318 */ "glMakeTextureHandleNonResidentARB",
    /* 1319 */ "glMakeTextureHandleNonResidentNV",
    /* 1320 */ "glMakeTextureHandleResidentARB",
    /* 1321 */ "glMakeTextureHandleResidentNV",
    /* 1322 */ "glMap1d",
    /* 1323 */ "glMap1f",
    /* 1324 */ "glMap1xOES",
    /* 1325 */ "glMap2d",
    /* 1326 */ "glMap2f",
    /* 1327 */ "glMap2xOES",
    /* 1328 */ "glMapBuffer",
    /* 1329 */ "glMapBufferARB",
    /* 1330 */ "glMapBufferRange",
    /* 1331 */ "glMapControlPointsNV",
    /* 1332 */ "glMapGrid1d",
    /* 1333 */ "glMapGrid1f",
    /* 1334 */ "glMapGrid1xOES",
    /* 1335 */ "glMapGrid2d",
    /* 1336 */ "glMapGrid2f",
    /* 1337 */ "glMapGrid2xOES",
    /* 1338 */ "glMapNamedBuffer",
    /* 1339 */ "glMapNamedBufferEXT",
    /* 1340 */ "glMapNamedBufferRange",
    /* 1341 */ "glMapNamedBufferRangeEXT",
    /* 1342 */ "glMapObjectBufferATI",
    /* 1343 */ "glMapParameterfvNV",
    /* 1344 */ "glMapParameterivNV",
    /* 1345 */ "glMapTexture2DINTEL",
    /* 1346 */ "glMapVertexAttrib1dAPPLE",
    /* 1347 */ "glMapVertexAttrib1fAPPLE",
    /* 1348 */ "glMapVertexAttrib2dAPPLE",
    /* 1349 */ "glMapVertexAttrib2fAPPLE",
    /* 1350 */ "glMaterialf",
    /* 1351 */ "glMaterialfv",
    /* 1352 */ "glMateriali",
    /* 1353 */ "glMaterialiv",
    /* 1354 */ "glMaterialxOES",
    /* 1355 */ "glMaterialxvOES",
    /* 1356 */ "glMatrixFrustumEXT",
    /* 1357 */ "glMatrixIndexPointerARB",
    /* 1358 */ "glMatrixIndexubvARB",
    /* 1359 */ "glMatrixIndexuivARB",
    /* 1360 */ "glMatrixIndexusvARB",
    /* 1361 */ "glMatrixLoad3x2fNV",
    /* 1362 */ "glMatrixLoad3x3fNV",
    /* 1363 */ "glMatrixLoadIdentityEXT",
    /* 1364 */ "glMatrixLoadTranspose3x3fNV",
    /* 1365 */ "glMatrixLoadTransposedEXT",
    /* 1366 */ "glMatrixLoadTransposefEXT",
    /* 1367 */ "glMatrixLoaddEXT",
    /* 1368 */ "glMatrixLoadfEXT",
    /* 1369 */ "glMatrixMode",
    /* 1370 */ "glMatrixMult3x2fNV",
    /* 1371 */ "glMatrixMult3x3fNV",
    /* 1372 */ "glMatrixMultTranspose3x3fNV",
    /* 1373 */ "glMatrixMultTransposedEXT",
    /* 1374 */ "glMatrixMultTransposefEXT",
    /* 1375 */ "glMatrixMultdEXT",
    /* 1376 */ "glMatrixMultfEXT",
    /* 1377 */ "glMatrixOrthoEXT",
    /* 1378 */ "glMatrixPopEXT",
    /* 1379 */ "glMatrixPushEXT",
    /* 1380 */ "glMatrixRotatedEXT",
    /* 1381 */ "glMatrixRotatefEXT",
    /* 1382 */ "glMatrixScaledEXT",
    /* 1383 */ "glMatrixScalefEXT",
    /* 1384 */ "glMatrixTranslatedEXT",
    /* 1385 */ "glMatrixTranslatefEXT",
    /* 1386 */ "glMaxShaderCompilerThreadsARB",
    /* 1387 */ "glMaxShaderCompilerThreadsKHR",
    /* 1388 */ "glMemoryBarrier",
    /* 1389 */ "glMemoryBarrierByRegion",
    /* 1390 */ "glMemoryBarrierEXT",
    /* 1391 */ "glMemoryObjectParameterivEXT",
    /* 1392 */ "glMinSampleShading",
    /* 1393 */ "glMinSampleShadingARB",
    /* 1394 */ "glMinmax",
    /* 1395 */ "glMinmaxEXT",
    /* 1396 */ "glMultMatrixd",
    /* 1397 */ "glMultMatrixf",
    /* 1398 */ "glMultMatrixxOES",
    /* 1399 */ "glMultTransposeMatrixd",
    /* 1400 */ "glMultTransposeMatrixdARB",
    /* 1401 */ "glMultTransposeMatrixf",
    /* 1402 */ "glMultTransposeMatrixfARB",
    /* 1403 */ "glMultTransposeMatrixxOES",
    /* 1404 */ "glMultiDrawArrays",
    /* 1405 */ "glMultiDrawArraysEXT",
    /* 1406 */ "glMultiDrawArraysIndirect",
    /* 1407 */ "glMultiDrawArraysIndirectAMD",
    /* 1408 */ "glMultiDrawArraysIndirectBindlessCountNV",
    /* 1409 */ "glMultiDrawArraysIndirectBindlessNV",
    /* 1410 */ "glMultiDrawArraysIndirectCount",
    /* 1411 */ "glMultiDrawArraysIndirectCountARB",
    /* 1412 */ "glMultiDrawElementArrayAPPLE",
    /* 1413 */ "glMultiDrawElements",
    /* 1414 */ "glMultiDrawElementsBaseVertex",
    /* 1415 */ "glMultiDrawElementsEXT",
    /* 1416 */ "glMultiDrawElementsIndirect",
    /* 1417 */ "glMultiDrawElementsIndirectAMD",
    /* 1418 */ "glMultiDrawElementsIndirectBindlessCountNV",
    /* 1419 */ "glMultiDrawElementsIndirectBindlessNV",
    /* 1420 */ "glMultiDrawElementsIndirectCount",
    /* 1421 */ "glMultiDrawElementsIndirectCountARB",
    /* 1422 */ "glMultiDrawMeshTasksIndirectCountNV",
    /* 1423 */ "glMultiDrawMeshTasksIndirectNV",
    /* 1424 */ "glMultiDrawRangeElementArrayAPPLE",
    /* 1425 */ "glMultiModeDrawArraysIBM",
    /* 1426 */ "glMultiModeDrawElementsIBM",
    /* 1427 */ "glMultiTexBufferEXT",
    /* 1428 */ "glMultiTexCoord1bOES",
    /* 1429 */ "glMultiTexCoord1bvOES",
    /* 1430 */ "glMultiTexCoord1d",
    /* 1431 */ "glMultiTexCoord1dARB",
    /* 1432 */ "glMultiTexCoord1dv",
    /* 1433 */ "glMultiTexCoord1dvARB",
    /* 1434 */ "glMultiTexCoord1f",
    /* 1435 */ "glMultiTexCoord1fARB",
    /* 1436 */ "glMultiTexCoord1fv",
    /* 1437 */ "glMultiTexCoord1fvARB",
    /* 1438 */ "glMultiTexCoord1hNV",
    /* 1439 */ "glMultiTexCoord1hvNV",
    /* 1440 */ "glMultiTexCoord1i",
    /* 1441 */ "glMultiTexCoord1iARB",
    /* 1442 */ "glMultiTexCoord1iv",
    /* 1443 */ "glMultiTexCoord1ivARB",
    /* 1444 */ "glMultiTexCoord1s",
    /* 1445 */ "glMultiTexCoord1sARB",
    /* 1446 */ "glMultiTexCoord1sv",
    /* 1447 */ "glMultiTexCoord1svARB",
    /* 1448 */ "glMultiTexCoord1xOES",
    /* 1449 */ "glMultiTexCoord1xvOES",
    /* 1450 */ "glMultiTexCoord2bOES",
    /* 1451 */ "glMultiTexCoord2bvOES",
    /* 1452 */ "glMultiTexCoord2d",
    /* 1453 */ "glMultiTexCoord2dARB",
    /* 1454 */ "glMultiTexCoord2dv",
    /* 1455 */ "glMultiTexCoord2dvARB",
    /* 1456 */ "glMultiTexCoord2f",
    /* 1457 */ "glMultiTexCoord2fARB",
    /* 1458 */ "glMultiTexCoord2fv",
    /* 1459 */ "glMultiTexCoord2fvARB",
    /* 1460 */ "glMultiTexCoord2hNV",
    /* 1461 */ "glMultiTexCoord2hvNV",
    /* 1462 */ "glMultiTexCoord2i",
    /* 1463 */ "glMultiTexCoord2iARB",
    /* 1464 */ "glMultiTexCoord2iv",
    /* 1465 */ "glMultiTexCoord2ivARB",
    /* 1466 */ "glMultiTexCoord2s",
    /* 1467 */ "glMultiTexCoord2sARB",
    /* 1468 */ "glMultiTexCoord2sv",
    /* 1469 */ "glMultiTexCoord2svARB",
    /* 1470 */ "glMultiTexCoord2xOES",
    /* 1471 */ "glMultiTexCoord2xvOES",
    /* 1472 */ "glMultiTexCoord3bOES",
    /* 1473 */ "glMultiTexCoord3bvOES",
    /* 1474 */ "glMultiTexCoord3d",
    /* 1475 */ "glMultiTexCoord3dARB",
    /* 1476 */ "glMultiTexCoord3dv",
    /* 1477 */ "glMultiTexCoord3dvARB",
    /* 1478 */ "glMultiTexCoord3f",
    /* 1479 */ "glMultiTexCoord3fARB",
    /* 1480 */ "glMultiTexCoord3fv",
    /* 1481 */ "glMultiTexCoord3fvARB",
    /* 1482 */ "glMultiTexCoord3hNV",
    /* 1483 */ "glMultiTexCoord3hvNV",
    /* 1484 */ "glMultiTexCoord3i",
    /* 1485 */ "glMultiTexCoord3iARB",
    /* 1486 */ "glMultiTexCoord3iv",
    /* 1487 */ "glMultiTexCoord3ivARB",
    /* 1488 */ "glMultiTexCoord3s",
    /* 1489 */ "glMultiTexCoord3sARB",
    /* 1490 */ "glMultiTexCoord3sv",
    /* 1491 */ "glMultiTexCoord3svARB",
    /* 1492 */ "glMultiTexCoord3xOES",
    /* 1493 */ "glMultiTexCoord3xvOES",
    /* 1494 */ "glMultiTexCoord4bOES",
    /* 1495 */ "glMultiTexCoord4bvOES",
    /* 1496 */ "glMultiTexCoord4d",
    /* 1497 */ "glMultiTexCoord4dARB",
    /* 1498 */ "glMultiTexCoord4dv",
    /* 1499 */ "glMultiTexCoord4dvARB",
    /* 1500 */ "glMultiTexCoord4f",
    /* 1501 */ "glMultiTexCoord4fARB",
    /* 1502 */ "glMultiTexCoord4fv",
    /* 1503 */ "glMultiTexCoord4fvARB",
    /* 1504 */ "glMultiTexCoord4hNV",
    /* 1505 */ "glMultiTexCoord4hvNV",
    /* 1506 */ "glMultiTexCoord4i",
    /* 1507 */ "glMultiTexCoord4iARB",
    /* 1508 */ "glMultiTexCoord4iv",
    /* 1509 */ "glMultiTexCoord4ivARB",
    /* 1510 */ "glMultiTexCoord4s",
    /* 1511 */ "glMultiTexCoord4sARB",
    /* 1512 */ "glMultiTexCoord4sv",
    /* 1513 */ "glMultiTexCoord4svARB",
    /* 1514 */ "glMultiTexCoord4xOES",
    /* 1515 */ "glMultiTexCoord4xvOES",
    /* 1516 */ "glMultiTexCoordP1ui",
    /* 1517 */ "glMultiTexCoordP1uiv",
    /* 1518 */ "glMultiTexCoordP2ui",
    /* 1519 */ "glMultiTexCoordP2uiv",
    /* 1520 */ "glMultiTexCoordP3ui",
    /* 1521 */ "glMultiTexCoordP3uiv",
    /* 1522 */ "glMultiTexCoordP4ui",
    /* 1523 */ "glMultiTexCoordP4uiv",
    /* 1524 */ "glMultiTexCoordPointerEXT",
    /* 1525 */ "glMultiTexEnvfEXT",
    /* 1526 */ "glMultiTexEnvfvEXT",
    /* 1527 */ "glMultiTexEnviEXT",
    /* 1528 */ "glMultiTexEnvivEXT",
    /* 1529 */ "glMultiTexGendEXT",
    /* 1530 */ "glMultiTexGendvEXT",
    /* 1531 */ "glMultiTexGenfEXT",
    /* 1532 */ "glMultiTexGenfvEXT",
    /* 1533 */ "glMultiTexGeniEXT",
    /* 1534 */ "glMultiTexGenivEXT",
    /* 1535 */ "glMultiTexImage1DEXT",
    /* 1536 */ "glMultiTexImage2DEXT",
    /* 1537 */ "glMultiTexImage3DEXT",
    /* 1538 */ "glMultiTexParameterIivEXT",
    /* 1539 */ "glMultiTexParameterIuivEXT",
    /* 1540 */ "glMultiTexParameterfEXT",
    /* 1541 */ "glMultiTexParameterfvEXT",
    /* 1542 */ "glMultiTexParameteriEXT",
    /* 1543 */ "glMultiTexParameterivEXT",
    /* 1544 */ "glMultiTexRenderbufferEXT",
    /* 1545 */ "glMultiTexSubImage1DEXT",
    /* 1546 */ "glMultiTexSubImage2DEXT",
    /* 1547 */ "glMultiTexSubImage3DEXT",
    /* 1548 */ "glMulticastBarrierNV",
    /* 1549 */ "glMulticastBlitFramebufferNV",
    /* 1550 */ "glMulticastBufferSubDataNV",
    /* 1551 */ "glMulticastCopyBufferSubDataNV",
    /* 1552 */ "glMulticastCopyImageSubDataNV",
    /* 1553 */ "glMulticastFramebufferSampleLocationsfvNV",
    /* 1554 */ "glMulticastGetQueryObjecti64vNV",
    /* 1555 */ "glMulticastGetQueryObjectivNV",
    /* 1556 */ "glMulticastGetQueryObjectui64vNV",
    /* 1557 */ "glMulticastGetQueryObjectuivNV",
    /* 1558 */ "glMulticastScissorArrayvNVX",
    /* 1559 */ "glMulticastViewportArrayvNVX",
    /* 1560 */ "glMulticastViewportPositionWScaleNVX",
    /* 1561 */ "glMulticastWaitSyncNV",
    /* 1562 */ "glNamedBufferAttachMemoryNV",
    /* 1563 */ "glNamedBufferData",
    /* 1564 */ "glNamedBufferDataEXT",
    /* 1565 */ "glNamedBufferPageCommitmentARB",
    /* 1566 */ "glNamedBufferPageCommitmentEXT",
    /* 1567 */ "glNamedBufferPageCommitmentMemNV",
    /* 1568 */ "glNamedBufferStorage",
    /* 1569 */ "glNamedBufferStorageEXT",
    /* 1570 */ "glNamedBufferStorageExternalEXT",
    /* 1571 */ "glNamedBufferStorageMemEXT",
    /* 1572 */ "glNamedBufferSubData",
    /* 1573 */ "glNamedBufferSubDataEXT",
    /* 1574 */ "glNamedCopyBufferSubDataEXT",
    /* 1575 */ "glNamedFramebufferDrawBuffer",
    /* 1576 */ "glNamedFramebufferDrawBuffers",
    /* 1577 */ "glNamedFramebufferParameteri",
    /* 1578 */ "glNamedFramebufferParameteriEXT",
    /* 1579 */ "glNamedFramebufferReadBuffer",
    /* 1580 */ "glNamedFramebufferRenderbuffer",
    /* 1581 */ "glNamedFramebufferRenderbufferEXT",
    /* 1582 */ "glNamedFramebufferSampleLocationsfvARB",
    /* 1583 */ "glNamedFramebufferSampleLocationsfvNV",
    /* 1584 */ "glNamedFramebufferSamplePositionsfvAMD",
    /* 1585 */ "glNamedFramebufferTexture",
    /* 1586 */ "glNamedFramebufferTexture1DEXT",
    /* 1587 */ "glNamedFramebufferTexture2DEXT",
    /* 1588 */ "glNamedFramebufferTexture3DEXT",
    /* 1589 */ "glNamedFramebufferTextureEXT",
    /* 1590 */ "glNamedFramebufferTextureFaceEXT",
    /* 1591 */ "glNamedFramebufferTextureLayer",
    /* 1592 */ "glNamedFramebufferTextureLayerEXT",
    /* 1593 */ "glNamedProgramLocalParameter4dEXT",
    /* 1594 */ "glNamedProgramLocalParameter4dvEXT",
    /* 1595 */ "glNamedProgramLocalParameter4fEXT",
    /* 1596 */ "glNamedProgramLocalParameter4fvEXT",
    /* 1597 */ "glNamedProgramLocalParameterI4iEXT",
    /* 1598 */ "glNamedProgramLocalParameterI4ivEXT",
    /* 1599 */ "glNamedProgramLocalParameterI4uiEXT",
    /* 1600 */ "glNamedProgramLocalParameterI4uivEXT",
    /* 1601 */ "glNamedProgramLocalParameters4fvEXT",
    /* 1602 */ "glNamedProgramLocalParametersI4ivEXT",
    /* 1603 */ "glNamedProgramLocalParametersI4uivEXT",
    /* 1604 */ "glNamedProgramStringEXT",
    /* 1605 */ "glNamedRenderbufferStorage",
    /* 1606 */ "glNamedRenderbufferStorageEXT",
    /* 1607 */ "glNamedRenderbufferStorageMultisample",
    /* 1608 */ "glNamedRenderbufferStorageMultisampleAdvancedAMD",
    /* 1609 */ "glNamedRenderbufferStorageMultisampleCoverageEXT",
    /* 1610 */ "glNamedRenderbufferStorageMultisampleEXT",
    /* 1611 */ "glNamedStringARB",
    /* 1612 */ "glNewList",
    /* 1613 */ "glNewObjectBufferATI",
    /* 1614 */ "glNormal3b",
    /* 1615 */ "glNormal3bv",
    /* 1616 */ "glNormal3d",
    /* 1617 */ "glNormal3dv",
    /* 1618 */ "glNormal3f",
    /* 1619 */ "glNormal3fVertex3fSUN",
    /* 1620 */ "glNormal3fVertex3fvSUN",
    /* 1621 */ "glNormal3fv",
    /* 1622 */ "glNormal3hNV",
    /* 1623 */ "glNormal3hvNV",
    /* 1624 */ "glNormal3i",
    /* 1625 */ "glNormal3iv",
    /* 1626 */ "glNormal3s",
    /* 1627 */ "glNormal3sv",
    /* 1628 */ "glNormal3xOES",
    /* 1629 */ "glNormal3xvOES",
    /* 1630 */ "glNormalFormatNV",
    /* 1631 */ "glNormalP3ui",
    /* 1632 */ "glNormalP3uiv",
    /* 1633 */ "glNormalPointer",
    /* 1634 */ "glNormalPointerEXT",
    /* 1635 */ "glNormalPointerListIBM",
    /* 1636 */ "glNormalPointervINTEL",
    /* 1637 */ "glNormalStream3bATI",
    /* 1638 */ "glNormalStream3bvATI",
    /* 1639 */ "glNormalStream3dATI",
    /* 1640 */ "glNormalStream3dvATI",
    /* 1641 */ "glNormalStream3fATI",
    /* 1642 */ "glNormalStream3fvATI",
    /* 1643 */ "glNormalStream3iATI",
    /* 1644 */ "glNormalStream3ivATI",
    /* 1645 */ "glNormalStream3sATI",
    /* 1646 */ "glNormalStream3svATI",
    /* 1647 */ "glObjectLabel",
    /* 1648 */ "glObjectPtrLabel",
    /* 1649 */ "glObjectPurgeableAPPLE",
    /* 1650 */ "glObjectUnpurgeableAPPLE",
    /* 1651 */ "glOrtho",
    /* 1652 */ "glOrthofOES",
    /* 1653 */ "glOrthoxOES",
    /* 1654 */ "glPNTrianglesfATI",
    /* 1655 */ "glPNTrianglesiATI",
    /* 1656 */ "glPassTexCoordATI",
    /* 1657 */ "glPassThrough",
    /* 1658 */ "glPassThroughxOES",
    /* 1659 */ "glPatchParameterfv",
    /* 1660 */ "glPatchParameteri",
    /* 1661 */ "glPathColorGenNV",
    /* 1662 */ "glPathCommandsNV",
    /* 1663 */ "glPathCoordsNV",
    /* 1664 */ "glPathCoverDepthFuncNV",
    /* 1665 */ "glPathDashArrayNV",
    /* 1666 */ "glPathFogGenNV",
    /* 1667 */ "glPathGlyphIndexArrayNV",
    /* 1668 */ "glPathGlyphIndexRangeNV",
    /* 1669 */ "glPathGlyphRangeNV",
    /* 1670 */ "glPathGlyphsNV",
    /* 1671 */ "glPathMemoryGlyphIndexArrayNV",
    /* 1672 */ "glPathParameterfNV",
    /* 1673 */ "glPathParameterfvNV",
    /* 1674 */ "glPathParameteriNV",
    /* 1675 */ "glPathParameterivNV",
    /* 1676 */ "glPathStencilDepthOffsetNV",
    /* 1677 */ "glPathStencilFuncNV",
    /* 1678 */ "glPathStringNV",
    /* 1679 */ "glPathSubCommandsNV",
    /* 1680 */ "glPathSubCoordsNV",
    /* 1681 */ "glPathTexGenNV",
    /* 1682 */ "glPauseTransformFeedback",
    /* 1683 */ "glPauseTransformFeedbackNV",
    /* 1684 */ "glPixelDataRangeNV",
    /* 1685 */ "glPixelMapfv",
    /* 1686 */ "glPixelMapuiv",
    /* 1687 */ "glPixelMapusv",
    /* 1688 */ "glPixelMapx",
    /* 1689 */ "glPixelStoref",
    /* 1690 */ "glPixelStorei",
    /* 1691 */ "glPixelStorex",
    /* 1692 */ "glPixelTexGenParameterfSGIS",
    /* 1693 */ "glPixelTexGenParameterfvSGIS",
    /* 1694 */ "glPixelTexGenParameteriSGIS",
    /* 1695 */ "glPixelTexGenParameterivSGIS",
    /* 1696 */ "glPixelTexGenSGIX",
    /* 1697 */ "glPixelTransferf",
    /* 1698 */ "glPixelTransferi",
    /* 1699 */ "glPixelTransferxOES",
    /* 1700 */ "glPixelTransformParameterfEXT",
    /* 1701 */ "glPixelTransformParameterfvEXT",
    /* 1702 */ "glPixelTransformParameteriEXT",
    /* 1703 */ "glPixelTransformParameterivEXT",
    /* 1704 */ "glPixelZoom",
    /* 1705 */ "glPixelZoomxOES",
    /* 1706 */ "glPointAlongPathNV",
    /* 1707 */ "glPointParameterf",
    /* 1708 */ "glPointParameterfARB",
    /* 1709 */ "glPointParameterfEXT",
    /* 1710 */ "glPointParameterfSGIS",
    /* 1711 */ "glPointParameterfv",
    /* 1712 */ "glPointParameterfvARB",
    /* 1713 */ "glPointParameterfvEXT",
    /* 1714 */ "glPointParameterfvSGIS",
    /* 1715 */ "glPointParameteri",
    /* 1716 */ "glPointParameteriNV",
    /* 1717 */ "glPointParameteriv",
    /* 1718 */ "glPointParameterivNV",
    /* 1719 */ "glPointParameterxvOES",
    /* 1720 */ "glPointSize",
    /* 1721 */ "glPointSizexOES",
    /* 1722 */ "glPollAsyncSGIX",
    /* 1723 */ "glPollInstrumentsSGIX",
    /* 1724 */ "glPolygonMode",
    /* 1725 */ "glPolygonOffset",
    /* 1726 */ "glPolygonOffsetClamp",
    /* 1727 */ "glPolygonOffsetClampEXT",
    /* 1728 */ "glPolygonOffsetEXT",
    /* 1729 */ "glPolygonOffsetxOES",
    /* 1730 */ "glPolygonStipple",
    /* 1731 */ "glPopAttrib",
    /* 1732 */ "glPopClientAttrib",
    /* 1733 */ "glPopDebugGroup",
    /* 1734 */ "glPopGroupMarkerEXT",
    /* 1735 */ "glPopMatrix",
    /* 1736 */ "glPopName",
    /* 1737 */ "glPresentFrameDualFillNV",
    /* 1738 */ "glPresentFrameKeyedNV",
    /* 1739 */ "glPrimitiveBoundingBoxARB",
    /* 1740 */ "glPrimitiveRestartIndex",
    /* 1741 */ "glPrimitiveRestartIndexNV",
    /* 1742 */ "glPrimitiveRestartNV",
    /* 1743 */ "glPrioritizeTextures",
    /* 1744 */ "glPrioritizeTexturesEXT",
    /* 1745 */ "glPrioritizeTexturesxOES",
    /* 1746 */ "glProgramBinary",
    /* 1747 */ "glProgramBufferParametersIivNV",
    /* 1748 */ "glProgramBufferParametersIuivNV",
    /* 1749 */ "glProgramBufferParametersfvNV",
    /* 1750 */ "glProgramEnvParameter4dARB",
    /* 1751 */ "glProgramEnvParameter4dvARB",
    /* 1752 */ "glProgramEnvParameter4fARB",
    /* 1753 */ "glProgramEnvParameter4fvARB",
    /* 1754 */ "glProgramEnvParameterI4iNV",
    /* 1755 */ "glProgramEnvParameterI4ivNV",
    /* 1756 */ "glProgramEnvParameterI4uiNV",
    /* 1757 */ "glProgramEnvParameterI4uivNV",
    /* 1758 */ "glProgramEnvParameters4fvEXT",
    /* 1759 */ "glProgramEnvParametersI4ivNV",
    /* 1760 */ "glProgramEnvParametersI4uivNV",
    /* 1761 */ "glProgramLocalParameter4dARB",
    /* 1762 */ "glProgramLocalParameter4dvARB",
    /* 1763 */ "glProgramLocalParameter4fARB",
    /* 1764 */ "glProgramLocalParameter4fvARB",
    /* 1765 */ "glProgramLocalParameterI4iNV",
    /* 1766 */ "glProgramLocalParameterI4ivNV",
    /* 1767 */ "glProgramLocalParameterI4uiNV",
    /* 1768 */ "glProgramLocalParameterI4uivNV",
    /* 1769 */ "glProgramLocalParameters4fvEXT",
    /* 1770 */ "glProgramLocalParametersI4ivNV",
    /* 1771 */ "glProgramLocalParametersI4uivNV",
    /* 1772 */ "glProgramNamedParameter4dNV",
    /* 1773 */ "glProgramNamedParameter4dvNV",
    /* 1774 */ "glProgramNamedParameter4fNV",
    /* 1775 */ "glProgramNamedParameter4fvNV",
    /* 1776 */ "glProgramParameter4dNV",
    /* 1777 */ "glProgramParameter4dvNV",
    /* 1778 */ "glProgramParameter4fNV",
    /* 1779 */ "glProgramParameter4fvNV",
    /* 1780 */ "glProgramParameteri",
    /* 1781 */ "glProgramParameteriARB",
    /* 1782 */ "glProgramParameteriEXT",
    /* 1783 */ "glProgramParameters4dvNV",
    /* 1784 */ "glProgramParameters4fvNV",
    /* 1785 */ "glProgramPathFragmentInputGenNV",
    /* 1786 */ "glProgramStringARB",
    /* 1787 */ "glProgramSubroutineParametersuivNV",
    /* 1788 */ "glProgramUniform1d",
    /* 1789 */ "glProgramUniform1dEXT",
    /* 1790 */ "glProgramUniform1dv",
    /* 1791 */ "glProgramUniform1dvEXT",
    /* 1792 */ "glProgramUniform1f",
    /* 1793 */ "glProgramUniform1fEXT",
    /* 1794 */ "glProgramUniform1fv",
    /* 1795 */ "glProgramUniform1fvEXT",
    /* 1796 */ "glProgramUniform1i",
    /* 1797 */ "glProgramUniform1i64ARB",
    /* 1798 */ "glProgramUniform1i64NV",
    /* 1799 */ "glProgramUniform1i64vARB",
    /* 1800 */ "glProgramUniform1i64vNV",
    /* 1801 */ "glProgramUniform1iEXT",
    /* 1802 */ "glProgramUniform1iv",
    /* 1803 */ "glProgramUniform1ivEXT",
    /* 1804 */ "glProgramUniform1ui",
    /* 1805 */ "glProgramUniform1ui64ARB",
    /* 1806 */ "glProgramUniform1ui64NV",
    /* 1807 */ "glProgramUniform1ui64vARB",
    /* 1808 */ "glProgramUniform1ui64vNV",
    /* 1809 */ "glProgramUniform1uiEXT",
    /* 1810 */ "glProgramUniform1uiv",
    /* 1811 */ "glProgramUniform1uivEXT",
    /* 1812 */ "glProgramUniform2d",
    /* 1813 */ "glProgramUniform2dEXT",
    /* 1814 */ "glProgramUniform2dv",
    /* 1815 */ "glProgramUniform2dvEXT",
    /* 1816 */ "glProgramUniform2f",
    /* 1817 */ "glProgramUniform2fEXT",
    /* 1818 */ "glProgramUniform2fv",
    /* 1819 */ "glProgramUniform2fvEXT",
    /* 1820 */ "glProgramUniform2i",
    /* 1821 */ "glProgramUniform2i64ARB",
    /* 1822 */ "glProgramUniform2i64NV",
    /* 1823 */ "glProgramUniform2i64vARB",
    /* 1824 */ "glProgramUniform2i64vNV",
    /* 1825 */ "glProgramUniform2iEXT",
    /* 1826 */ "glProgramUniform2iv",
    /* 1827 */ "glProgramUniform2ivEXT",
    /* 1828 */ "glProgramUniform2ui",
    /* 1829 */ "glProgramUniform2ui64ARB",
    /* 1830 */ "glProgramUniform2ui64NV",
    /* 1831 */ "glProgramUniform2ui64vARB",
    /* 1832 */ "glProgramUniform2ui64vNV",
    /* 1833 */ "glProgramUniform2uiEXT",
    /* 1834 */ "glProgramUniform2uiv",
    /* 1835 */ "glProgramUniform2uivEXT",
    /* 1836 */ "glProgramUniform3d",
    /* 1837 */ "glProgramUniform3dEXT",
    /* 1838 */ "glProgramUniform3dv",
    /* 1839 */ "glProgramUniform3dvEXT",
    /* 1840 */ "glProgramUniform3f",
    /* 1841 */ "glProgramUniform3fEXT",
    /* 1842 */ "glProgramUniform3fv",
    /* 1843 */ "glProgramUniform3fvEXT",
    /* 1844 */ "glProgramUniform3i",
    /* 1845 */ "glProgramUniform3i64ARB",
    /* 1846 */ "glProgramUniform3i64NV",
    /* 1847 */ "glProgramUniform3i64vARB",
    /* 1848 */ "glProgramUniform3i64vNV",
    /* 1849 */ "glProgramUniform3iEXT",
    /* 1850 */ "glProgramUniform3iv",
    /* 1851 */ "glProgramUniform3ivEXT",
    /* 1852 */ "glProgramUniform3ui",
    /* 1853 */ "glProgramUniform3ui64ARB",
    /* 1854 */ "glProgramUniform3ui64NV",
    /* 1855 */ "glProgramUniform3ui64vARB",
    /* 1856 */ "glProgramUniform3ui64vNV",
    /* 1857 */ "glProgramUniform3uiEXT",
    /* 1858 */ "glProgramUniform3uiv",
    /* 1859 */ "glProgramUniform3uivEXT",
    /* 1860 */ "glProgramUniform4d",
    /* 1861 */ "glProgramUniform4dEXT",
    /* 1862 */ "glProgramUniform4dv",
    /* 1863 */ "glProgramUniform4dvEXT",
    /* 1864 */ "glProgramUniform4f",
    /* 1865 */ "glProgramUniform4fEXT",
    /* 1866 */ "glProgramUniform4fv",
    /* 1867 */ "glProgramUniform4fvEXT",
    /* 1868 */ "glProgramUniform4i",
    /* 1869 */ "glProgramUniform4i64ARB",
    /* 1870 */ "glProgramUniform4i64NV",
    /* 1871 */ "glProgramUniform4i64vARB",
    /* 1872 */ "glProgramUniform4i64vNV",
    /* 1873 */ "glProgramUniform4iEXT",
    /* 1874 */ "glProgramUniform4iv",
    /* 1875 */ "glProgramUniform4ivEXT",
    /* 1876 */ "glProgramUniform4ui",
    /* 1877 */ "glProgramUniform4ui64ARB",
    /* 1878 */ "glProgramUniform4ui64NV",
    /* 1879 */ "glProgramUniform4ui64vARB",
    /* 1880 */ "glProgramUniform4ui64vNV",
    /* 1881 */ "glProgramUniform4uiEXT",
    /* 1882 */ "glProgramUniform4uiv",
    /* 1883 */ "glProgramUniform4uivEXT",
    /* 1884 */ "glProgramUniformHandleui64ARB",
    /* 1885 */ "glProgramUniformHandleui64NV",
    /* 1886 */ "glProgramUniformHandleui64vARB",
    /* 1887 */ "glProgramUniformHandleui64vNV",
    /* 1888 */ "glProgramUniformMatrix2dv",
    /* 1889 */ "glProgramUniformMatrix2dvEXT",
    /* 1890 */ "glProgramUniformMatrix2fv",
    /* 1891 */ "glProgramUniformMatrix2fvEXT",
    /* 1892 */ "glProgramUniformMatrix2x3dv",
    /* 1893 */ "glProgramUniformMatrix2x3dvEXT",
    /* 1894 */ "glProgramUniformMatrix2x3fv",
    /* 1895 */ "glProgramUniformMatrix2x3fvEXT",
    /* 1896 */ "glProgramUniformMatrix2x4dv",
    /* 1897 */ "glProgramUniformMatrix2x4dvEXT",
    /* 1898 */ "glProgramUniformMatrix2x4fv",
    /* 1899 */ "glProgramUniformMatrix2x4fvEXT",
    /* 1900 */ "glProgramUniformMatrix3dv",
    /* 1901 */ "glProgramUniformMatrix3dvEXT",
    /* 1902 */ "glProgramUniformMatrix3fv",
    /* 1903 */ "glProgramUniformMatrix3fvEXT",
    /* 1904 */ "glProgramUniformMatrix3x2dv",
    /* 1905 */ "glProgramUniformMatrix3x2dvEXT",
    /* 1906 */ "glProgramUniformMatrix3x2fv",
    /* 1907 */ "glProgramUniformMatrix3x2fvEXT",
    /* 1908 */ "glProgramUniformMatrix3x4dv",
    /* 1909 */ "glProgramUniformMatrix3x4dvEXT",
    /* 1910 */ "glProgramUniformMatrix3x4fv",
    /* 1911 */ "glProgramUniformMatrix3x4fvEXT",
    /* 1912 */ "glProgramUniformMatrix4dv",
    /* 1913 */ "glProgramUniformMatrix4dvEXT",
    /* 1914 */ "glProgramUniformMatrix4fv",
    /* 1915 */ "glProgramUniformMatrix4fvEXT",
    /* 1916 */ "glProgramUniformMatrix4x2dv",
    /* 1917 */ "glProgramUniformMatrix4x2dvEXT",
    /* 1918 */ "glProgramUniformMatrix4x2fv",
    /* 1919 */ "glProgramUniformMatrix4x2fvEXT",
    /* 1920 */ "glProgramUniformMatrix4x3dv",
    /* 1921 */ "glProgramUniformMatrix4x3dvEXT",
    /* 1922 */ "glProgramUniformMatrix4x3fv",
    /* 1923 */ "glProgramUniformMatrix4x3fvEXT",
    /* 1924 */ "glProgramUniformui64NV",
    /* 1925 */ "glProgramUniformui64vNV",
    /* 1926 */ "glProgramVertexLimitNV",
    /* 1927 */ "glProvokingVertex",
    /* 1928 */ "glProvokingVertexEXT",
    /* 1929 */ "glPushAttrib",
    /* 1930 */ "glPushClientAttrib",
    /* 1931 */ "glPushClientAttribDefaultEXT",
    /* 1932 */ "glPushDebugGroup",
    /* 1933 */ "glPushGroupMarkerEXT",
    /* 1934 */ "glPushMatrix",
    /* 1935 */ "glPushName",
    /* 1936 */ "glQueryCounter",
    /* 1937 */ "glQueryMatrixxOES",
    /* 1938 */ "glQueryObjectParameteruiAMD",
    /* 1939 */ "glQueryResourceNV",
    /* 1940 */ "glQueryResourceTagNV",
    /* 1941 */ "glRasterPos2d",
    /* 1942 */ "glRasterPos2dv",
    /* 1943 */ "glRasterPos2f",
    /* 1944 */ "glRasterPos2fv",
    /* 1945 */ "glRasterPos2i",
    /* 1946 */ "glRasterPos2iv",
    /* 1947 */ "glRasterPos2s",
    /* 1948 */ "glRasterPos2sv",
    /* 1949 */ "glRasterPos2xOES",
    /* 1950 */ "glRasterPos2xvOES",
    /* 1951 */ "glRasterPos3d",
    /* 1952 */ "glRasterPos3dv",
    /* 1953 */ "glRasterPos3f",
    /* 1954 */ "glRasterPos3fv",
    /* 1955 */ "glRasterPos3i",
    /* 1956 */ "glRasterPos3iv",
    /* 1957 */ "glRasterPos3s",
    /* 1958 */ "glRasterPos3sv",
    /* 1959 */ "glRasterPos3xOES",
    /* 1960 */ "glRasterPos3xvOES",
    /* 1961 */ "glRasterPos4d",
    /* 1962 */ "glRasterPos4dv",
    /* 1963 */ "glRasterPos4f",
    /* 1964 */ "glRasterPos4fv",
    /* 1965 */ "glRasterPos4i",
    /* 1966 */ "glRasterPos4iv",
    /* 1967 */ "glRasterPos4s",
    /* 1968 */ "glRasterPos4sv",
    /* 1969 */ "glRasterPos4xOES",
    /* 1970 */ "glRasterPos4xvOES",
    /* 1971 */ "glRasterSamplesEXT",
    /* 1972 */ "glReadBuffer",
    /* 1973 */ "glReadInstrumentsSGIX",
    /* 1974 */ "glReadPixels",
    /* 1975 */ "glReadnPixels",
    /* 1976 */ "glReadnPixelsARB",
    /* 1977 */ "glRectd",
    /* 1978 */ "glRectdv",
    /* 1979 */ "glRectf",
    /* 1980 */ "glRectfv",
    /* 1981 */ "glRecti",
    /* 1982 */ "glRectiv",
    /* 1983 */ "glRects",
    /* 1984 */ "glRectsv",
    /* 1985 */ "glRectxOES",
    /* 1986 */ "glRectxvOES",
    /* 1987 */ "glReferencePlaneSGIX",
    /* 1988 */ "glReleaseKeyedMutexWin32EXT",
    /* 1989 */ "glReleaseShaderCompiler",
    /* 1990 */ "glRenderGpuMaskNV",
    /* 1991 */ "glRenderMode",
    /* 1992 */ "glRenderbufferStorage",
    /* 1993 */ "glRenderbufferStorageEXT",
    /* 1994 */ "glRenderbufferStorageMultisample",
    /* 1995 */ "glRenderbufferStorageMultisampleAdvancedAMD",
    /* 1996 */ "glRenderbufferStorageMultisampleCoverageNV",
    /* 1997 */ "glRenderbufferStorageMultisampleEXT",
    /* 1998 */ "glReplacementCodePointerSUN",
    /* 1999 */ "glReplacementCodeubSUN",
    /* 2000 */ "glReplacementCodeubvSUN",
    /* 2001 */ "glReplacementCodeuiColor3fVertex3fSUN",
    /* 2002 */ "glReplacementCodeuiColor3fVertex3fvSUN",
    /* 2003 */ "glReplacementCodeuiColor4fNormal3fVertex3fSUN",
    /* 2004 */ "glReplacementCodeuiColor4fNormal3fVertex3fvSUN",
    /* 2005 */ "glReplacementCodeuiColor4ubVertex3fSUN",
    /* 2006 */ "glReplacementCodeuiColor4ubVertex3fvSUN",
    /* 2007 */ "glReplacementCodeuiNormal3fVertex3fSUN",
    /* 2008 */ "glReplacementCodeuiNormal3fVertex3fvSUN",
    /* 2009 */ "glReplacementCodeuiSUN",
    /* 2010 */ "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN",
    /* 2011 */ "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN",
    /* 2012 */ "glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN",
    /* 2013 */ "glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN",
    /* 2014 */ "glReplacementCodeuiTexCoord2fVertex3fSUN",
    /* 2015 */ "glReplacementCodeuiTexCoord2fVertex3fvSUN",
    /* 2016 */ "glReplacementCodeuiVertex3fSUN",
    /* 2017 */ "glReplacementCodeuiVertex3fvSUN",
    /* 2018 */ "glReplacementCodeuivSUN",
    /* 2019 */ "glReplacementCodeusSUN",
    /* 2020 */ "glReplacementCodeusvSUN",
    /* 2021 */ "glRequestResidentProgramsNV",
    /* 2022 */ "glResetHistogram",
    /* 2023 */ "glResetHistogramEXT",
    /* 2024 */ "glResetMemoryObjectParameterNV",
    /* 2025 */ "glResetMinmax",
    /* 2026 */ "glResetMinmaxEXT",
    /* 2027 */ "glResizeBuffersMESA",
    /* 2028 */ "glResolveDepthValuesNV",
    /* 2029 */ "glResumeTransformFeedback",
    /* 2030 */ "glResumeTransformFeedbackNV",
    /* 2031 */ "glRotated",
    /* 2032 */ "glRotatef",
    /* 2033 */ "glRotatexOES",
    /* 2034 */ "glSampleCoverage",
    /* 2035 */ "glSampleCoverageARB",
    /* 2036 */ "glSampleMapATI",
    /* 2037 */ "glSampleMaskEXT",
    /* 2038 */ "glSampleMaskIndexedNV",
    /* 2039 */ "glSampleMaskSGIS",
    /* 2040 */ "glSampleMaski",
    /* 2041 */ "glSamplePatternEXT",
    /* 2042 */ "glSamplePatternSGIS",
    /* 2043 */ "glSamplerParameterIiv",
    /* 2044 */ "glSamplerParameterIuiv",
    /* 2045 */ "glSamplerParameterf",
    /* 2046 */ "glSamplerParameterfv",
    /* 2047 */ "glSamplerParameteri",
    /* 2048 */ "glSamplerParameteriv",
    /* 2049 */ "glScaled",
    /* 2050 */ "glScalef",
    /* 2051 */ "glScalexOES",
    /* 2052 */ "glScissor",
    /* 2053 */ "glScissorArrayv",
    /* 2054 */ "glScissorExclusiveArrayvNV",
    /* 2055 */ "glScissorExclusiveNV",
    /* 2056 */ "glScissorIndexed",
    /* 2057 */ "glScissorIndexedv",
    /* 2058 */ "glSecondaryColor3b",
    /* 2059 */ "glSecondaryColor3bEXT",
    /* 2060 */ "glSecondaryColor3bv",
    /* 2061 */ "glSecondaryColor3bvEXT",
    /* 2062 */ "glSecondaryColor3d",
    /* 2063 */ "glSecondaryColor3dEXT",
    /* 2064 */ "glSecondaryColor3dv",
    /* 2065 */ "glSecondaryColor3dvEXT",
    /* 2066 */ "glSecondaryColor3f",
    /* 2067 */ "glSecondaryColor3fEXT",
    /* 2068 */ "glSecondaryColor3fv",
    /* 2069 */ "glSecondaryColor3fvEXT",
    /* 2070 */ "glSecondaryColor3hNV",
    /* 2071 */ "glSecondaryColor3hvNV",
    /* 2072 */ "glSecondaryColor3i",
    /* 2073 */ "glSecondaryColor3iEXT",
    /* 2074 */ "glSecondaryColor3iv",
    /* 2075 */ "glSecondaryColor3ivEXT",
    /* 2076 */ "glSecondaryColor3s",
    /* 2077 */ "glSecondaryColor3sEXT",
    /* 2078 */ "glSecondaryColor3sv",
    /* 2079 */ "glSecondaryColor3svEXT",
    /* 2080 */ "glSecondaryColor3ub",
    /* 2081 */ "glSecondaryColor3ubEXT",
    /* 2082 */ "glSecondaryColor3ubv",
    /* 2083 */ "glSecondaryColor3ubvEXT",
    /* 2084 */ "glSecondaryColor3ui",
    /* 2085 */ "glSecondaryColor3uiEXT",
    /* 2086 */ "glSecondaryColor3uiv",
    /* 2087 */ "glSecondaryColor3uivEXT",
    /* 2088 */ "glSecondaryColor3us",
    /* 2089 */ "glSecondaryColor3usEXT",
    /* 2090 */ "glSecondaryColor3usv",
    /* 2091 */ "glSecondaryColor3usvEXT",
    /* 2092 */ "glSecondaryColorFormatNV",
    /* 2093 */ "glSecondaryColorP3ui",
    /* 2094 */ "glSecondaryColorP3uiv",
    /* 2095 */ "glSecondaryColorPointer",
    /* 2096 */ "glSecondaryColorPointerEXT",
    /* 2097 */ "glSecondaryColorPointerListIBM",
    /* 2098 */ "glSelectBuffer",
    /* 2099 */ "glSelectPerfMonitorCountersAMD",
    /* 2100 */ "glSemaphoreParameterivNV",
    /* 2101 */ "glSemaphoreParameterui64vEXT",
    /* 2102 */ "glSeparableFilter2D",
    /* 2103 */ "glSeparableFilter2DEXT",
    /* 2104 */ "glSetFenceAPPLE",
    /* 2105 */ "glSetFenceNV",
    /* 2106 */ "glSetFragmentShaderConstantATI",
    /* 2107 */ "glSetInvariantEXT",
    /* 2108 */ "glSetLocalConstantEXT",
    /* 2109 */ "glSetMultisamplefvAMD",
    /* 2110 */ "glShadeModel",
    /* 2111 */ "glShaderBinary",
    /* 2112 */ "glShaderOp1EXT",
    /* 2113 */ "glShaderOp2EXT",
    /* 2114 */ "glShaderOp3EXT",
    /* 2115 */ "glShaderSource",
    /* 2116 */ "glShaderSourceARB",
    /* 2117 */ "glShaderStorageBlockBinding",
    /* 2118 */ "glShadingRateImageBarrierNV",
    /* 2119 */ "glShadingRateImagePaletteNV",
    /* 2120 */ "glShadingRateSampleOrderCustomNV",
    /* 2121 */ "glShadingRateSampleOrderNV",
    /* 2122 */ "glSharpenTexFuncSGIS",
    /* 2123 */ "glSignalSemaphoreEXT",
    /* 2124 */ "glSignalSemaphoreui64NVX",
    /* 2125 */ "glSignalVkFenceNV",
    /* 2126 */ "glSignalVkSemaphoreNV",
    /* 2127 */ "glSpecializeShader",
    /* 2128 */ "glSpecializeShaderARB",
    /* 2129 */ "glSpriteParameterfSGIX",
    /* 2130 */ "glSpriteParameterfvSGIX",
    /* 2131 */ "glSpriteParameteriSGIX",
    /* 2132 */ "glSpriteParameterivSGIX",
    /* 2133 */ "glStartInstrumentsSGIX",
    /* 2134 */ "glStateCaptureNV",
    /* 2135 */ "glStencilClearTagEXT",
    /* 2136 */ "glStencilFillPathInstancedNV",
    /* 2137 */ "glStencilFillPathNV",
    /* 2138 */ "glStencilFunc",
    /* 2139 */ "glStencilFuncSeparate",
    /* 2140 */ "glStencilFuncSeparateATI",
    /* 2141 */ "glStencilMask",
    /* 2142 */ "glStencilMaskSeparate",
    /* 2143 */ "glStencilOp",
    /* 2144 */ "glStencilOpSeparate",
    /* 2145 */ "glStencilOpSeparateATI",
    /* 2146 */ "glStencilOpValueAMD",
    /* 2147 */ "glStencilStrokePathInstancedNV",
    /* 2148 */ "glStencilStrokePathNV",
    /* 2149 */ "glStencilThenCoverFillPathInstancedNV",
    /* 2150 */ "glStencilThenCoverFillPathNV",
    /* 2151 */ "glStencilThenCoverStrokePathInstancedNV",
    /* 2152 */ "glStencilThenCoverStrokePathNV",
    /* 2153 */ "glStopInstrumentsSGIX",
    /* 2154 */ "glStringMarkerGREMEDY",
    /* 2155 */ "glSubpixelPrecisionBiasNV",
    /* 2156 */ "glSwizzleEXT",
    /* 2157 */ "glSyncTextureINTEL",
    /* 2158 */ "glTagSampleBufferSGIX",
    /* 2159 */ "glTangent3bEXT",
    /* 2160 */ "glTangent3bvEXT",
    /* 2161 */ "glTangent3dEXT",
    /* 2162 */ "glTangent3dvEXT",
    /* 2163 */ "glTangent3fEXT",
    /* 2164 */ "glTangent3fvEXT",
    /* 2165 */ "glTangent3iEXT",
    /* 2166 */ "glTangent3ivEXT",
    /* 2167 */ "glTangent3sEXT",
    /* 2168 */ "glTangent3svEXT",
    /* 2169 */ "glTangentPointerEXT",
    /* 2170 */ "glTbufferMask3DFX",
    /* 2171 */ "glTessellationFactorAMD",
    /* 2172 */ "glTessellationModeAMD",
    /* 2173 */ "glTestFenceAPPLE",
    /* 2174 */ "glTestFenceNV",
    /* 2175 */ "glTestObjectAPPLE",
    /* 2176 */ "glTexAttachMemoryNV",
    /* 2177 */ "glTexBuffer",
    /* 2178 */ "glTexBufferARB",
    /* 2179 */ "glTexBufferEXT",
    /* 2180 */ "glTexBufferRange",
    /* 2181 */ "glTexBumpParameterfvATI",
    /* 2182 */ "glTexBumpParameterivATI",
    /* 2183 */ "glTexCoord1bOES",
    /* 2184 */ "glTexCoord1bvOES",
    /* 2185 */ "glTexCoord1d",
    /* 2186 */ "glTexCoord1dv",
    /* 2187 */ "glTexCoord1f",
    /* 2188 */ "glTexCoord1fv",
    /* 2189 */ "glTexCoord1hNV",
    /* 2190 */ "glTexCoord1hvNV",
    /* 2191 */ "glTexCoord1i",
    /* 2192 */ "glTexCoord1iv",
    /* 2193 */ "glTexCoord1s",
    /* 2194 */ "glTexCoord1sv",
    /* 2195 */ "glTexCoord1xOES",
    /* 2196 */ "glTexCoord1xvOES",
    /* 2197 */ "glTexCoord2bOES",
    /* 2198 */ "glTexCoord2bvOES",
    /* 2199 */ "glTexCoord2d",
    /* 2200 */ "glTexCoord2dv",
    /* 2201 */ "glTexCoord2f",
    /* 2202 */ "glTexCoord2fColor3fVertex3fSUN",
    /* 2203 */ "glTexCoord2fColor3fVertex3fvSUN",
    /* 2204 */ "glTexCoord2fColor4fNormal3fVertex3fSUN",
    /* 2205 */ "glTexCoord2fColor4fNormal3fVertex3fvSUN",
    /* 2206 */ "glTexCoord2fColor4ubVertex3fSUN",
    /* 2207 */ "glTexCoord2fColor4ubVertex3fvSUN",
    /* 2208 */ "glTexCoord2fNormal3fVertex3fSUN",
    /* 2209 */ "glTexCoord2fNormal3fVertex3fvSUN",
    /* 2210 */ "glTexCoord2fVertex3fSUN",
    /* 2211 */ "glTexCoord2fVertex3fvSUN",
    /* 2212 */ "glTexCoord2fv",
    /* 2213 */ "glTexCoord2hNV",
    /* 2214 */ "glTexCoord2hvNV",
    /* 2215 */ "glTexCoord2i",
    /* 2216 */ "glTexCoord2iv",
    /* 2217 */ "glTexCoord2s",
    /* 2218 */ "glTexCoord2sv",
    /* 2219 */ "glTexCoord2xOES",
    /* 2220 */ "glTexCoord2xvOES",
    /* 2221 */ "glTexCoord3bOES",
    /* 2222 */ "glTexCoord3bvOES",
    /* 2223 */ "glTexCoord3d",
    /* 2224 */ "glTexCoord3dv",
    /* 2225 */ "glTexCoord3f",
    /* 2226 */ "glTexCoord3fv",
    /* 2227 */ "glTexCoord3hNV",
    /* 2228 */ "glTexCoord3hvNV",
    /* 2229 */ "glTexCoord3i",
    /* 2230 */ "glTexCoord3iv",
    /* 2231 */ "glTexCoord3s",
    /* 2232 */ "glTexCoord3sv",
    /* 2233 */ "glTexCoord3xOES",
    /* 2234 */ "glTexCoord3xvOES",
    /* 2235 */ "glTexCoord4bOES",
    /* 2236 */ "glTexCoord4bvOES",
    /* 2237 */ "glTexCoord4d",
    /* 2238 */ "glTexCoord4dv",
    /* 2239 */ "glTexCoord4f",
    /* 2240 */ "glTexCoord4fColor4fNormal3fVertex4fSUN",
    /* 2241 */ "glTexCoord4fColor4fNormal3fVertex4fvSUN",
    /* 2242 */ "glTexCoord4fVertex4fSUN",
    /* 2243 */ "glTexCoord4fVertex4fvSUN",
    /* 2244 */ "glTexCoord4fv",
    /* 2245 */ "glTexCoord4hNV",
    /* 2246 */ "glTexCoord4hvNV",
    /* 2247 */ "glTexCoord4i",
    /* 2248 */ "glTexCoord4iv",
    /* 2249 */ "glTexCoord4s",
    /* 2250 */ "glTexCoord4sv",
    /* 2251 */ "glTexCoord4xOES",
    /* 2252 */ "glTexCoord4xvOES",
    /* 2253 */ "glTexCoordFormatNV",
    /* 2254 */ "glTexCoordP1ui",
    /* 2255 */ "glTexCoordP1uiv",
    /* 2256 */ "glTexCoordP2ui",
    /* 2257 */ "glTexCoordP2uiv",
    /* 2258 */ "glTexCoordP3ui",
    /* 2259 */ "glTexCoordP3uiv",
    /* 2260 */ "glTexCoordP4ui",
    /* 2261 */ "glTexCoordP4uiv",
    /* 2262 */ "glTexCoordPointer",
    /* 2263 */ "glTexCoordPointerEXT",
    /* 2264 */ "glTexCoordPointerListIBM",
    /* 2265 */ "glTexCoordPointervINTEL",
    /* 2266 */ "glTexEnvf",
    /* 2267 */ "glTexEnvfv",
    /* 2268 */ "glTexEnvi",
    /* 2269 */ "glTexEnviv",
    /* 2270 */ "glTexEnvxOES",
    /* 2271 */ "glTexEnvxvOES",
    /* 2272 */ "glTexFilterFuncSGIS",
    /* 2273 */ "glTexGend",
    /* 2274 */ "glTexGendv",
    /* 2275 */ "glTexGenf",
    /* 2276 */ "glTexGenfv",
    /* 2277 */ "glTexGeni",
    /* 2278 */ "glTexGeniv",
    /* 2279 */ "glTexGenxOES",
    /* 2280 */ "glTexGenxvOES",
    /* 2281 */ "glTexImage1D",
    /* 2282 */ "glTexImage2D",
    /* 2283 */ "glTexImage2DExternalANGLE",
    /* 2284 */ "glTexImage2DMultisample",
    /* 2285 */ "glTexImage2DMultisampleCoverageNV",
    /* 2286 */ "glTexImage3D",
    /* 2287 */ "glTexImage3DEXT",
    /* 2288 */ "glTexImage3DMultisample",
    /* 2289 */ "glTexImage3DMultisampleCoverageNV",
    /* 2290 */ "glTexImage4DSGIS",
    /* 2291 */ "glTexPageCommitmentARB",
    /* 2292 */ "glTexPageCommitmentMemNV",
    /* 2293 */ "glTexParameterIiv",
    /* 2294 */ "glTexParameterIivEXT",
    /* 2295 */ "glTexParameterIuiv",
    /* 2296 */ "glTexParameterIuivEXT",
    /* 2297 */ "glTexParameterf",
    /* 2298 */ "glTexParameterfv",
    /* 2299 */ "glTexParameteri",
    /* 2300 */ "glTexParameteriv",
    /* 2301 */ "glTexParameterxOES",
    /* 2302 */ "glTexParameterxvOES",
    /* 2303 */ "glTexRenderbufferNV",
    /* 2304 */ "glTexStorage1D",
    /* 2305 */ "glTexStorage1DEXT",
    /* 2306 */ "glTexStorage2D",
    /* 2307 */ "glTexStorage2DEXT",
    /* 2308 */ "glTexStorage2DMultisample",
    /* 2309 */ "glTexStorage3D",
    /* 2310 */ "glTexStorage3DEXT",
    /* 2311 */ "glTexStorage3DMultisample",
    /* 2312 */ "glTexStorageMem1DEXT",
    /* 2313 */ "glTexStorageMem2DEXT",
    /* 2314 */ "glTexStorageMem2DMultisampleEXT",
    /* 2315 */ "glTexStorageMem3DEXT",
    /* 2316 */ "glTexStorageMem3DMultisampleEXT",
    /* 2317 */ "glTexStorageMemFlags2DANGLE",
    /* 2318 */ "glTexStorageMemFlags2DMultisampleANGLE",
    /* 2319 */ "glTexStorageMemFlags3DANGLE",
    /* 2320 */ "glTexStorageMemFlags3DMultisampleANGLE",
    /* 2321 */ "glTexStorageSparseAMD",
    /* 2322 */ "glTexSubImage1D",
    /* 2323 */ "glTexSubImage1DEXT",
    /* 2324 */ "glTexSubImage2D",
    /* 2325 */ "glTexSubImage2DEXT",
    /* 2326 */ "glTexSubImage3D",
    /* 2327 */ "glTexSubImage3DEXT",
    /* 2328 */ "glTexSubImage4DSGIS",
    /* 2329 */ "glTextureAttachMemoryNV",
    /* 2330 */ "glTextureBarrier",
    /* 2331 */ "glTextureBarrierNV",
    /* 2332 */ "glTextureBuffer",
    /* 2333 */ "glTextureBufferEXT",
    /* 2334 */ "glTextureBufferRange",
    /* 2335 */ "glTextureBufferRangeEXT",
    /* 2336 */ "glTextureColorMaskSGIS",
    /* 2337 */ "glTextureImage1DEXT",
    /* 2338 */ "glTextureImage2DEXT",
    /* 2339 */ "glTextureImage2DMultisampleCoverageNV",
    /* 2340 */ "glTextureImage2DMultisampleNV",
    /* 2341 */ "glTextureImage3DEXT",
    /* 2342 */ "glTextureImage3DMultisampleCoverageNV",
    /* 2343 */ "glTextureImage3DMultisampleNV",
    /* 2344 */ "glTextureLightEXT",
    /* 2345 */ "glTextureMaterialEXT",
    /* 2346 */ "glTextureNormalEXT",
    /* 2347 */ "glTexturePageCommitmentEXT",
    /* 2348 */ "glTexturePageCommitmentMemNV",
    /* 2349 */ "glTextureParameterIiv",
    /* 2350 */ "glTextureParameterIivEXT",
    /* 2351 */ "glTextureParameterIuiv",
    /* 2352 */ "glTextureParameterIuivEXT",
    /* 2353 */ "glTextureParameterf",
    /* 2354 */ "glTextureParameterfEXT",
    /* 2355 */ "glTextureParameterfv",
    /* 2356 */ "glTextureParameterfvEXT",
    /* 2357 */ "glTextureParameteri",
    /* 2358 */ "glTextureParameteriEXT",
    /* 2359 */ "glTextureParameteriv",
    /* 2360 */ "glTextureParameterivEXT",
    /* 2361 */ "glTextureRangeAPPLE",
    /* 2362 */ "glTextureRenderbufferEXT",
    /* 2363 */ "glTextureStorage1D",
    /* 2364 */ "glTextureStorage1DEXT",
    /* 2365 */ "glTextureStorage2D",
    /* 2366 */ "glTextureStorage2DEXT",
    /* 2367 */ "glTextureStorage2DMultisample",
    /* 2368 */ "glTextureStorage2DMultisampleEXT",
    /* 2369 */ "glTextureStorage3D",
    /* 2370 */ "glTextureStorage3DEXT",
    /* 2371 */ "glTextureStorage3DMultisample",
    /* 2372 */ "glTextureStorage3DMultisampleEXT",
    /* 2373 */ "glTextureStorageMem1DEXT",
    /* 2374 */ "glTextureStorageMem2DEXT",
    /* 2375 */ "glTextureStorageMem2DMultisampleEXT",
    /* 2376 */ "glTextureStorageMem3DEXT",
    /* 2377 */ "glTextureStorageMem3DMultisampleEXT",
    /* 2378 */ "glTextureStorageSparseAMD",
    /* 2379 */ "glTextureSubImage1D",
    /* 2380 */ "glTextureSubImage1DEXT",
    /* 2381 */ "glTextureSubImage2D",
    /* 2382 */ "glTextureSubImage2DEXT",
    /* 2383 */ "glTextureSubImage3D",
    /* 2384 */ "glTextureSubImage3DEXT",
    /* 2385 */ "glTextureView",
    /* 2386 */ "glTrackMatrixNV",
    /* 2387 */ "glTransformFeedbackAttribsNV",
    /* 2388 */ "glTransformFeedbackBufferBase",
    /* 2389 */ "glTransformFeedbackBufferRange",
    /* 2390 */ "glTransformFeedbackStreamAttribsNV",
    /* 2391 */ "glTransformFeedbackVaryings",
    /* 2392 */ "glTransformFeedbackVaryingsEXT",
    /* 2393 */ "glTransformFeedbackVaryingsNV",
    /* 2394 */ "glTransformPathNV",
    /* 2395 */ "glTranslated",
    /* 2396 */ "glTranslatef",
    /* 2397 */ "glTranslatexOES",
    /* 2398 */ "glUniform1d",
    /* 2399 */ "glUniform1dv",
    /* 2400 */ "glUniform1f",
    /* 2401 */ "glUniform1fARB",
    /* 2402 */ "glUniform1fv",
    /* 2403 */ "glUniform1fvARB",
    /* 2404 */ "glUniform1i",
    /* 2405 */ "glUniform1i64ARB",
    /* 2406 */ "glUniform1i64NV",
    /* 2407 */ "glUniform1i64vARB",
    /* 2408 */ "glUniform1i64vNV",
    /* 2409 */ "glUniform1iARB",
    /* 2410 */ "glUniform1iv",
    /* 2411 */ "glUniform1ivARB",
    /* 2412 */ "glUniform1ui",
    /* 2413 */ "glUniform1ui64ARB",
    /* 2414 */ "glUniform1ui64NV",
    /* 2415 */ "glUniform1ui64vARB",
    /* 2416 */ "glUniform1ui64vNV",
    /* 2417 */ "glUniform1uiEXT",
    /* 2418 */ "glUniform1uiv",
    /* 2419 */ "glUniform1uivEXT",
    /* 2420 */ "glUniform2d",
    /* 2421 */ "glUniform2dv",
    /* 2422 */ "glUniform2f",
    /* 2423 */ "glUniform2fARB",
    /* 2424 */ "glUniform2fv",
    /* 2425 */ "glUniform2fvARB",
    /* 2426 */ "glUniform2i",
    /* 2427 */ "glUniform2i64ARB",
    /* 2428 */ "glUniform2i64NV",
    /* 2429 */ "glUniform2i64vARB",
    /* 2430 */ "glUniform2i64vNV",
    /* 2431 */ "glUniform2iARB",
    /* 2432 */ "glUniform2iv",
    /* 2433 */ "glUniform2ivARB",
    /* 2434 */ "glUniform2ui",
    /* 2435 */ "glUniform2ui64ARB",
    /* 2436 */ "glUniform2ui64NV",
    /* 2437 */ "glUniform2ui64vARB",
    /* 2438 */ "glUniform2ui64vNV",
    /* 2439 */ "glUniform2uiEXT",
    /* 2440 */ "glUniform2uiv",
    /* 2441 */ "glUniform2uivEXT",
    /* 2442 */ "glUniform3d",
    /* 2443 */ "glUniform3dv",
    /* 2444 */ "glUniform3f",
    /* 2445 */ "glUniform3fARB",
    /* 2446 */ "glUniform3fv",
    /* 2447 */ "glUniform3fvARB",
    /* 2448 */ "glUniform3i",
    /* 2449 */ "glUniform3i64ARB",
    /* 2450 */ "glUniform3i64NV",
    /* 2451 */ "glUniform3i64vARB",
    /* 2452 */ "glUniform3i64vNV",
    /* 2453 */ "glUniform3iARB",
    /* 2454 */ "glUniform3iv",
    /* 2455 */ "glUniform3ivARB",
    /* 2456 */ "glUniform3ui",
    /* 2457 */ "glUniform3ui64ARB",
    /* 2458 */ "glUniform3ui64NV",
    /* 2459 */ "glUniform3ui64vARB",
    /* 2460 */ "glUniform3ui64vNV",
    /* 2461 */ "glUniform3uiEXT",
    /* 2462 */ "glUniform3uiv",
    /* 2463 */ "glUniform3uivEXT",
    /* 2464 */ "glUniform4d",
    /* 2465 */ "glUniform4dv",
    /* 2466 */ "glUniform4f",
    /* 2467 */ "glUniform4fARB",
    /* 2468 */ "glUniform4fv",
    /* 2469 */ "glUniform4fvARB",
    /* 2470 */ "glUniform4i",
    /* 2471 */ "glUniform4i64ARB",
    /* 2472 */ "glUniform4i64NV",
    /* 2473 */ "glUniform4i64vARB",
    /* 2474 */ "glUniform4i64vNV",
    /* 2475 */ "glUniform4iARB",
    /* 2476 */ "glUniform4iv",
    /* 2477 */ "glUniform4ivARB",
    /* 2478 */ "glUniform4ui",
    /* 2479 */ "glUniform4ui64ARB",
    /* 2480 */ "glUniform4ui64NV",
    /* 2481 */ "glUniform4ui64vARB",
    /* 2482 */ "glUniform4ui64vNV",
    /* 2483 */ "glUniform4uiEXT",
    /* 2484 */ "glUniform4uiv",
    /* 2485 */ "glUniform4uivEXT",
    /* 2486 */ "glUniformBlockBinding",
    /* 2487 */ "glUniformBufferEXT",
    /* 2488 */ "glUniformHandleui64ARB",
    /* 2489 */ "glUniformHandleui64NV",
    /* 2490 */ "glUniformHandleui64vARB",
    /* 2491 */ "glUniformHandleui64vNV",
    /* 2492 */ "glUniformMatrix2dv",
    /* 2493 */ "glUniformMatrix2fv",
    /* 2494 */ "glUniformMatrix2fvARB",
    /* 2495 */ "glUniformMatrix2x3dv",
    /* 2496 */ "glUniformMatrix2x3fv",
    /* 2497 */ "glUniformMatrix2x4dv",
    /* 2498 */ "glUniformMatrix2x4fv",
    /* 2499 */ "glUniformMatrix3dv",
    /* 2500 */ "glUniformMatrix3fv",
    /* 2501 */ "glUniformMatrix3fvARB",
    /* 2502 */ "glUniformMatrix3x2dv",
    /* 2503 */ "glUniformMatrix3x2fv",
    /* 2504 */ "glUniformMatrix3x4dv",
    /* 2505 */ "glUniformMatrix3x4fv",
    /* 2506 */ "glUniformMatrix4dv",
    /* 2507 */ "glUniformMatrix4fv",
    /* 2508 */ "glUniformMatrix4fvARB",
    /* 2509 */ "glUniformMatrix4x2dv",
    /* 2510 */ "glUniformMatrix4x2fv",
    /* 2511 */ "glUniformMatrix4x3dv",
    /* 2512 */ "glUniformMatrix4x3fv",
    /* 2513 */ "glUniformSubroutinesuiv",
    /* 2514 */ "glUniformui64NV",
    /* 2515 */ "glUniformui64vNV",
    /* 2516 */ "glUnlockArraysEXT",
    /* 2517 */ "glUnmapBuffer",
    /* 2518 */ "glUnmapBufferARB",
    /* 2519 */ "glUnmapNamedBuffer",
    /* 2520 */ "glUnmapNamedBufferEXT",
    /* 2521 */ "glUnmapObjectBufferATI",
    /* 2522 */ "glUnmapTexture2DINTEL",
    /* 2523 */ "glUpdateObjectBufferATI",
    /* 2524 */ "glUploadGpuMaskNVX",
    /* 2525 */ "glUseProgram",
    /* 2526 */ "glUseProgramObjectARB",
    /* 2527 */ "glUseProgramStages",
    /* 2528 */ "glUseShaderProgramEXT",
    /* 2529 */ "glVDPAUFiniNV",
    /* 2530 */ "glVDPAUGetSurfaceivNV",
    /* 2531 */ "glVDPAUInitNV",
    /* 2532 */ "glVDPAUIsSurfaceNV",
    /* 2533 */ "glVDPAUMapSurfacesNV",
    /* 2534 */ "glVDPAURegisterOutputSurfaceNV",
    /* 2535 */ "glVDPAURegisterVideoSurfaceNV",
    /* 2536 */ "glVDPAURegisterVideoSurfaceWithPictureStructureNV",
    /* 2537 */ "glVDPAUSurfaceAccessNV",
    /* 2538 */ "glVDPAUUnmapSurfacesNV",
    /* 2539 */ "glVDPAUUnregisterSurfaceNV",
    /* 2540 */ "glValidateProgram",
    /* 2541 */ "glValidateProgramARB",
    /* 2542 */ "glValidateProgramPipeline",
    /* 2543 */ "glVariantArrayObjectATI",
    /* 2544 */ "glVariantPointerEXT",
    /* 2545 */ "glVariantbvEXT",
    /* 2546 */ "glVariantdvEXT",
    /* 2547 */ "glVariantfvEXT",
    /* 2548 */ "glVariantivEXT",
    /* 2549 */ "glVariantsvEXT",
    /* 2550 */ "glVariantubvEXT",
    /* 2551 */ "glVariantuivEXT",
    /* 2552 */ "glVariantusvEXT",
    /* 2553 */ "glVertex2bOES",
    /* 2554 */ "glVertex2bvOES",
    /* 2555 */ "glVertex2d",
    /* 2556 */ "glVertex2dv",
    /* 2557 */ "glVertex2f",
    /* 2558 */ "glVertex2fv",
    /* 2559 */ "glVertex2hNV",
    /* 2560 */ "glVertex2hvNV",
    /* 2561 */ "glVertex2i",
    /* 2562 */ "glVertex2iv",
    /* 2563 */ "glVertex2s",
    /* 2564 */ "glVertex2sv",
    /* 2565 */ "glVertex2xOES",
    /* 2566 */ "glVertex2xvOES",
    /* 2567 */ "glVertex3bOES",
    /* 2568 */ "glVertex3bvOES",
    /* 2569 */ "glVertex3d",
    /* 2570 */ "glVertex3dv",
    /* 2571 */ "glVertex3f",
    /* 2572 */ "glVertex3fv",
    /* 2573 */ "glVertex3hNV",
    /* 2574 */ "glVertex3hvNV",
    /* 2575 */ "glVertex3i",
    /* 2576 */ "glVertex3iv",
    /* 2577 */ "glVertex3s",
    /* 2578 */ "glVertex3sv",
    /* 2579 */ "glVertex3xOES",
    /* 2580 */ "glVertex3xvOES",
    /* 2581 */ "glVertex4bOES",
    /* 2582 */ "glVertex4bvOES",
    /* 2583 */ "glVertex4d",
    /* 2584 */ "glVertex4dv",
    /* 2585 */ "glVertex4f",
    /* 2586 */ "glVertex4fv",
    /* 2587 */ "glVertex4hNV",
    /* 2588 */ "glVertex4hvNV",
    /* 2589 */ "glVertex4i",
    /* 2590 */ "glVertex4iv",
    /* 2591 */ "glVertex4s",
    /* 2592 */ "glVertex4sv",
    /* 2593 */ "glVertex4xOES",
    /* 2594 */ "glVertex4xvOES",
    /* 2595 */ "glVertexArrayAttribBinding",
    /* 2596 */ "glVertexArrayAttribFormat",
    /* 2597 */ "glVertexArrayAttribIFormat",
    /* 2598 */ "glVertexArrayAttribLFormat",
    /* 2599 */ "glVertexArrayBindVertexBufferEXT",
    /* 2600 */ "glVertexArrayBindingDivisor",
    /* 2601 */ "glVertexArrayColorOffsetEXT",
    /* 2602 */ "glVertexArrayEdgeFlagOffsetEXT",
    /* 2603 */ "glVertexArrayElementBuffer",
    /* 2604 */ "glVertexArrayFogCoordOffsetEXT",
    /* 2605 */ "glVertexArrayIndexOffsetEXT",
    /* 2606 */ "glVertexArrayMultiTexCoordOffsetEXT",
    /* 2607 */ "glVertexArrayNormalOffsetEXT",
    /* 2608 */ "glVertexArrayParameteriAPPLE",
    /* 2609 */ "glVertexArrayRangeAPPLE",
    /* 2610 */ "glVertexArrayRangeNV",
    /* 2611 */ "glVertexArraySecondaryColorOffsetEXT",
    /* 2612 */ "glVertexArrayTexCoordOffsetEXT",
    /* 2613 */ "glVertexArrayVertexAttribBindingEXT",
    /* 2614 */ "glVertexArrayVertexAttribDivisorEXT",
    /* 2615 */ "glVertexArrayVertexAttribFormatEXT",
    /* 2616 */ "glVertexArrayVertexAttribIFormatEXT",
    /* 2617 */ "glVertexArrayVertexAttribIOffsetEXT",
    /* 2618 */ "glVertexArrayVertexAttribLFormatEXT",
    /* 2619 */ "glVertexArrayVertexAttribLOffsetEXT",
    /* 2620 */ "glVertexArrayVertexAttribOffsetEXT",
    /* 2621 */ "glVertexArrayVertexBindingDivisorEXT",
    /* 2622 */ "glVertexArrayVertexBuffer",
    /* 2623 */ "glVertexArrayVertexBuffers",
    /* 2624 */ "glVertexArrayVertexOffsetEXT",
    /* 2625 */ "glVertexAttrib1d",
    /* 2626 */ "glVertexAttrib1dARB",
    /* 2627 */ "glVertexAttrib1dNV",
    /* 2628 */ "glVertexAttrib1dv",
    /* 2629 */ "glVertexAttrib1dvARB",
    /* 2630 */ "glVertexAttrib1dvNV",
    /* 2631 */ "glVertexAttrib1f",
    /* 2632 */ "glVertexAttrib1fARB",
    /* 2633 */ "glVertexAttrib1fNV",
    /* 2634 */ "glVertexAttrib1fv",
    /* 2635 */ "glVertexAttrib1fvARB",
    /* 2636 */ "glVertexAttrib1fvNV",
    /* 2637 */ "glVertexAttrib1hNV",
    /* 2638 */ "glVertexAttrib1hvNV",
    /* 2639 */ "glVertexAttrib1s",
    /* 2640 */ "glVertexAttrib1sARB",
    /* 2641 */ "glVertexAttrib1sNV",
    /* 2642 */ "glVertexAttrib1sv",
    /* 2643 */ "glVertexAttrib1svARB",
    /* 2644 */ "glVertexAttrib1svNV",
    /* 2645 */ "glVertexAttrib2d",
    /* 2646 */ "glVertexAttrib2dARB",
    /* 2647 */ "glVertexAttrib2dNV",
    /* 2648 */ "glVertexAttrib2dv",
    /* 2649 */ "glVertexAttrib2dvARB",
    /* 2650 */ "glVertexAttrib2dvNV",
    /* 2651 */ "glVertexAttrib2f",
    /* 2652 */ "glVertexAttrib2fARB",
    /* 2653 */ "glVertexAttrib2fNV",
    /* 2654 */ "glVertexAttrib2fv",
    /* 2655 */ "glVertexAttrib2fvARB",
    /* 2656 */ "glVertexAttrib2fvNV",
    /* 2657 */ "glVertexAttrib2hNV",
    /* 2658 */ "glVertexAttrib2hvNV",
    /* 2659 */ "glVertexAttrib2s",
    /* 2660 */ "glVertexAttrib2sARB",
    /* 2661 */ "glVertexAttrib2sNV",
    /* 2662 */ "glVertexAttrib2sv",
    /* 2663 */ "glVertexAttrib2svARB",
    /* 2664 */ "glVertexAttrib2svNV",
    /* 2665 */ "glVertexAttrib3d",
    /* 2666 */ "glVertexAttrib3dARB",
    /* 2667 */ "glVertexAttrib3dNV",
    /* 2668 */ "glVertexAttrib3dv",
    /* 2669 */ "glVertexAttrib3dvARB",
    /* 2670 */ "glVertexAttrib3dvNV",
    /* 2671 */ "glVertexAttrib3f",
    /* 2672 */ "glVertexAttrib3fARB",
    /* 2673 */ "glVertexAttrib3fNV",
    /* 2674 */ "glVertexAttrib3fv",
    /* 2675 */ "glVertexAttrib3fvARB",
    /* 2676 */ "glVertexAttrib3fvNV",
    /* 2677 */ "glVertexAttrib3hNV",
    /* 2678 */ "glVertexAttrib3hvNV",
    /* 2679 */ "glVertexAttrib3s",
    /* 2680 */ "glVertexAttrib3sARB",
    /* 2681 */ "glVertexAttrib3sNV",
    /* 2682 */ "glVertexAttrib3sv",
    /* 2683 */ "glVertexAttrib3svARB",
    /* 2684 */ "glVertexAttrib3svNV",
    /* 2685 */ "glVertexAttrib4Nbv",
    /* 2686 */ "glVertexAttrib4NbvARB",
    /* 2687 */ "glVertexAttrib4Niv",
    /* 2688 */ "glVertexAttrib4NivARB",
    /* 2689 */ "glVertexAttrib4Nsv",
    /* 2690 */ "glVertexAttrib4NsvARB",
    /* 2691 */ "glVertexAttrib4Nub",
    /* 2692 */ "glVertexAttrib4NubARB",
    /* 2693 */ "glVertexAttrib4Nubv",
    /* 2694 */ "glVertexAttrib4NubvARB",
    /* 2695 */ "glVertexAttrib4Nuiv",
    /* 2696 */ "glVertexAttrib4NuivARB",
    /* 2697 */ "glVertexAttrib4Nusv",
    /* 2698 */ "glVertexAttrib4NusvARB",
    /* 2699 */ "glVertexAttrib4bv",
    /* 2700 */ "glVertexAttrib4bvARB",
    /* 2701 */ "glVertexAttrib4d",
    /* 2702 */ "glVertexAttrib4dARB",
    /* 2703 */ "glVertexAttrib4dNV",
    /* 2704 */ "glVertexAttrib4dv",
    /* 2705 */ "glVertexAttrib4dvARB",
    /* 2706 */ "glVertexAttrib4dvNV",
    /* 2707 */ "glVertexAttrib4f",
    /* 2708 */ "glVertexAttrib4fARB",
    /* 2709 */ "glVertexAttrib4fNV",
    /* 2710 */ "glVertexAttrib4fv",
    /* 2711 */ "glVertexAttrib4fvARB",
    /* 2712 */ "glVertexAttrib4fvNV",
    /* 2713 */ "glVertexAttrib4hNV",
    /* 2714 */ "glVertexAttrib4hvNV",
    /* 2715 */ "glVertexAttrib4iv",
    /* 2716 */ "glVertexAttrib4ivARB",
    /* 2717 */ "glVertexAttrib4s",
    /* 2718 */ "glVertexAttrib4sARB",
    /* 2719 */ "glVertexAttrib4sNV",
    /* 2720 */ "glVertexAttrib4sv",
    /* 2721 */ "glVertexAttrib4svARB",
    /* 2722 */ "glVertexAttrib4svNV",
    /* 2723 */ "glVertexAttrib4ubNV",
    /* 2724 */ "glVertexAttrib4ubv",
    /* 2725 */ "glVertexAttrib4ubvARB",
    /* 2726 */ "glVertexAttrib4ubvNV",
    /* 2727 */ "glVertexAttrib4uiv",
    /* 2728 */ "glVertexAttrib4uivARB",
    /* 2729 */ "glVertexAttrib4usv",
    /* 2730 */ "glVertexAttrib4usvARB",
    /* 2731 */ "glVertexAttribArrayObjectATI",
    /* 2732 */ "glVertexAttribBinding",
    /* 2733 */ "glVertexAttribDivisor",
    /* 2734 */ "glVertexAttribDivisorARB",
    /* 2735 */ "glVertexAttribFormat",
    /* 2736 */ "glVertexAttribFormatNV",
    /* 2737 */ "glVertexAttribI1i",
    /* 2738 */ "glVertexAttribI1iEXT",
    /* 2739 */ "glVertexAttribI1iv",
    /* 2740 */ "glVertexAttribI1ivEXT",
    /* 2741 */ "glVertexAttribI1ui",
    /* 2742 */ "glVertexAttribI1uiEXT",
    /* 2743 */ "glVertexAttribI1uiv",
    /* 2744 */ "glVertexAttribI1uivEXT",
    /* 2745 */ "glVertexAttribI2i",
    /* 2746 */ "glVertexAttribI2iEXT",
    /* 2747 */ "glVertexAttribI2iv",
    /* 2748 */ "glVertexAttribI2ivEXT",
    /* 2749 */ "glVertexAttribI2ui",
    /* 2750 */ "glVertexAttribI2uiEXT",
    /* 2751 */ "glVertexAttribI2uiv",
    /* 2752 */ "glVertexAttribI2uivEXT",
    /* 2753 */ "glVertexAttribI3i",
    /* 2754 */ "glVertexAttribI3iEXT",
    /* 2755 */ "glVertexAttribI3iv",
    /* 2756 */ "glVertexAttribI3ivEXT",
    /* 2757 */ "glVertexAttribI3ui",
    /* 2758 */ "glVertexAttribI3uiEXT",
    /* 2759 */ "glVertexAttribI3uiv",
    /* 2760 */ "glVertexAttribI3uivEXT",
    /* 2761 */ "glVertexAttribI4bv",
    /* 2762 */ "glVertexAttribI4bvEXT",
    /* 2763 */ "glVertexAttribI4i",
    /* 2764 */ "glVertexAttribI4iEXT",
    /* 2765 */ "glVertexAttribI4iv",
    /* 2766 */ "glVertexAttribI4ivEXT",
    /* 2767 */ "glVertexAttribI4sv",
    /* 2768 */ "glVertexAttribI4svEXT",
    /* 2769 */ "glVertexAttribI4ubv",
    /* 2770 */ "glVertexAttribI4ubvEXT",
    /* 2771 */ "glVertexAttribI4ui",
    /* 2772 */ "glVertexAttribI4uiEXT",
    /* 2773 */ "glVertexAttribI4uiv",
    /* 2774 */ "glVertexAttribI4uivEXT",
    /* 2775 */ "glVertexAttribI4usv",
    /* 2776 */ "glVertexAttribI4usvEXT",
    /* 2777 */ "glVertexAttribIFormat",
    /* 2778 */ "glVertexAttribIFormatNV",
    /* 2779 */ "glVertexAttribIPointer",
    /* 2780 */ "glVertexAttribIPointerEXT",
    /* 2781 */ "glVertexAttribL1d",
    /* 2782 */ "glVertexAttribL1dEXT",
    /* 2783 */ "glVertexAttribL1dv",
    /* 2784 */ "glVertexAttribL1dvEXT",
    /* 2785 */ "glVertexAttribL1i64NV",
    /* 2786 */ "glVertexAttribL1i64vNV",
    /* 2787 */ "glVertexAttribL1ui64ARB",
    /* 2788 */ "glVertexAttribL1ui64NV",
    /* 2789 */ "glVertexAttribL1ui64vARB",
    /* 2790 */ "glVertexAttribL1ui64vNV",
    /* 2791 */ "glVertexAttribL2d",
    /* 2792 */ "glVertexAttribL2dEXT",
    /* 2793 */ "glVertexAttribL2dv",
    /* 2794 */ "glVertexAttribL2dvEXT",
    /* 2795 */ "glVertexAttribL2i64NV",
    /* 2796 */ "glVertexAttribL2i64vNV",
    /* 2797 */ "glVertexAttribL2ui64NV",
    /* 2798 */ "glVertexAttribL2ui64vNV",
    /* 2799 */ "glVertexAttribL3d",
    /* 2800 */ "glVertexAttribL3dEXT",
    /* 2801 */ "glVertexAttribL3dv",
    /* 2802 */ "glVertexAttribL3dvEXT",
    /* 2803 */ "glVertexAttribL3i64NV",
    /* 2804 */ "glVertexAttribL3i64vNV",
    /* 2805 */ "glVertexAttribL3ui64NV",
    /* 2806 */ "glVertexAttribL3ui64vNV",
    /* 2807 */ "glVertexAttribL4d",
    /* 2808 */ "glVertexAttribL4dEXT",
    /* 2809 */ "glVertexAttribL4dv",
    /* 2810 */ "glVertexAttribL4dvEXT",
    /* 2811 */ "glVertexAttribL4i64NV",
    /* 2812 */ "glVertexAttribL4i64vNV",
    /* 2813 */ "glVertexAttribL4ui64NV",
    /* 2814 */ "glVertexAttribL4ui64vNV",
    /* 2815 */ "glVertexAttribLFormat",
    /* 2816 */ "glVertexAttribLFormatNV",
    /* 2817 */ "glVertexAttribLPointer",
    /* 2818 */ "glVertexAttribLPointerEXT",
    /* 2819 */ "glVertexAttribP1ui",
    /* 2820 */ "glVertexAttribP1uiv",
    /* 2821 */ "glVertexAttribP2ui",
    /* 2822 */ "glVertexAttribP2uiv",
    /* 2823 */ "glVertexAttribP3ui",
    /* 2824 */ "glVertexAttribP3uiv",
    /* 2825 */ "glVertexAttribP4ui",
    /* 2826 */ "glVertexAttribP4uiv",
    /* 2827 */ "glVertexAttribParameteriAMD",
    /* 2828 */ "glVertexAttribPointer",
    /* 2829 */ "glVertexAttribPointerARB",
    /* 2830 */ "glVertexAttribPointerNV",
    /* 2831 */ "glVertexAttribs1dvNV",
    /* 2832 */ "glVertexAttribs1fvNV",
    /* 2833 */ "glVertexAttribs1hvNV",
    /* 2834 */ "glVertexAttribs1svNV",
    /* 2835 */ "glVertexAttribs2dvNV",
    /* 2836 */ "glVertexAttribs2fvNV",
    /* 2837 */ "glVertexAttribs2hvNV",
    /* 2838 */ "glVertexAttribs2svNV",
    /* 2839 */ "glVertexAttribs3dvNV",
    /* 2840 */ "glVertexAttribs3fvNV",
    /* 2841 */ "glVertexAttribs3hvNV",
    /* 2842 */ "glVertexAttribs3svNV",
    /* 2843 */ "glVertexAttribs4dvNV",
    /* 2844 */ "glVertexAttribs4fvNV",
    /* 2845 */ "glVertexAttribs4hvNV",
    /* 2846 */ "glVertexAttribs4svNV",
    /* 2847 */ "glVertexAttribs4ubvNV",
    /* 2848 */ "glVertexBindingDivisor",
    /* 2849 */ "glVertexBlendARB",
    /* 2850 */ "glVertexBlendEnvfATI",
    /* 2851 */ "glVertexBlendEnviATI",
    /* 2852 */ "glVertexFormatNV",
    /* 2853 */ "glVertexP2ui",
    /* 2854 */ "glVertexP2uiv",
    /* 2855 */ "glVertexP3ui",
    /* 2856 */ "glVertexP3uiv",
    /* 2857 */ "glVertexP4ui",
    /* 2858 */ "glVertexP4uiv",
    /* 2859 */ "glVertexPointer",
    /* 2860 */ "glVertexPointerEXT",
    /* 2861 */ "glVertexPointerListIBM",
    /* 2862 */ "glVertexPointervINTEL",
    /* 2863 */ "glVertexStream1dATI",
    /* 2864 */ "glVertexStream1dvATI",
    /* 2865 */ "glVertexStream1fATI",
    /* 2866 */ "glVertexStream1fvATI",
    /* 2867 */ "glVertexStream1iATI",
    /* 2868 */ "glVertexStream1ivATI",
    /* 2869 */ "glVertexStream1sATI",
    /* 2870 */ "glVertexStream1svATI",
    /* 2871 */ "glVertexStream2dATI",
    /* 2872 */ "glVertexStream2dvATI",
    /* 2873 */ "glVertexStream2fATI",
    /* 2874 */ "glVertexStream2fvATI",
    /* 2875 */ "glVertexStream2iATI",
    /* 2876 */ "glVertexStream2ivATI",
    /* 2877 */ "glVertexStream2sATI",
    /* 2878 */ "glVertexStream2svATI",
    /* 2879 */ "glVertexStream3dATI",
    /* 2880 */ "glVertexStream3dvATI",
    /* 2881 */ "glVertexStream3fATI",
    /* 2882 */ "glVertexStream3fvATI",
    /* 2883 */ "glVertexStream3iATI",
    /* 2884 */ "glVertexStream3ivATI",
    /* 2885 */ "glVertexStream3sATI",
    /* 2886 */ "glVertexStream3svATI",
    /* 2887 */ "glVertexStream4dATI",
    /* 2888 */ "glVertexStream4dvATI",
    /* 2889 */ "glVertexStream4fATI",
    /* 2890 */ "glVertexStream4fvATI",
    /* 2891 */ "glVertexStream4iATI",
    /* 2892 */ "glVertexStream4ivATI",
    /* 2893 */ "glVertexStream4sATI",
    /* 2894 */ "glVertexStream4svATI",
    /* 2895 */ "glVertexWeightPointerEXT",
    /* 2896 */ "glVertexWeightfEXT",
    /* 2897 */ "glVertexWeightfvEXT",
    /* 2898 */ "glVertexWeighthNV",
    /* 2899 */ "glVertexWeighthvNV",
    /* 2900 */ "glVideoCaptureNV",
    /* 2901 */ "glVideoCaptureStreamParameterdvNV",
    /* 2902 */ "glVideoCaptureStreamParameterfvNV",
    /* 2903 */ "glVideoCaptureStreamParameterivNV",
    /* 2904 */ "glViewport",
    /* 2905 */ "glViewportArrayv",
    /* 2906 */ "glViewportIndexedf",
    /* 2907 */ "glViewportIndexedfv",
    /* 2908 */ "glViewportPositionWScaleNV",
    /* 2909 */ "glViewportSwizzleNV",
    /* 2910 */ "glWaitSemaphoreEXT",
    /* 2911 */ "glWaitSemaphoreui64NVX",
    /* 2912 */ "glWaitSync",
    /* 2913 */ "glWaitVkSemaphoreNV",
    /* 2914 */ "glWeightPathsNV",
    /* 2915 */ "glWeightPointerARB",
    /* 2916 */ "glWeightbvARB",
    /* 2917 */ "glWeightdvARB",
    /* 2918 */ "glWeightfvARB",
    /* 2919 */ "glWeightivARB",
    /* 2920 */ "glWeightsvARB",
    /* 2921 */ "glWeightubvARB",
    /* 2922 */ "glWeightuivARB",
    /* 2923 */ "glWeightusvARB",
    /* 2924 */ "glWindowPos2d",
    /* 2925 */ "glWindowPos2dARB",
    /* 2926 */ "glWindowPos2dMESA",
    /* 2927 */ "glWindowPos2dv",
    /* 2928 */ "glWindowPos2dvARB",
    /* 2929 */ "glWindowPos2dvMESA",
    /* 2930 */ "glWindowPos2f",
    /* 2931 */ "glWindowPos2fARB",
    /* 2932 */ "glWindowPos2fMESA",
    /* 2933 */ "glWindowPos2fv",
    /* 2934 */ "glWindowPos2fvARB",
    /* 2935 */ "glWindowPos2fvMESA",
    /* 2936 */ "glWindowPos2i",
    /* 2937 */ "glWindowPos2iARB",
    /* 2938 */ "glWindowPos2iMESA",
    /* 2939 */ "glWindowPos2iv",
    /* 2940 */ "glWindowPos2ivARB",
    /* 2941 */ "glWindowPos2ivMESA",
    /* 2942 */ "glWindowPos2s",
    /* 2943 */ "glWindowPos2sARB",
    /* 2944 */ "glWindowPos2sMESA",
    /* 2945 */ "glWindowPos2sv",
    /* 2946 */ "glWindowPos2svARB",
    /* 2947 */ "glWindowPos2svMESA",
    /* 2948 */ "glWindowPos3d",
    /* 2949 */ "glWindowPos3dARB",
    /* 2950 */ "glWindowPos3dMESA",
    /* 2951 */ "glWindowPos3dv",
    /* 2952 */ "glWindowPos3dvARB",
    /* 2953 */ "glWindowPos3dvMESA",
    /* 2954 */ "glWindowPos3f",
    /* 2955 */ "glWindowPos3fARB",
    /* 2956 */ "glWindowPos3fMESA",
    /* 2957 */ "glWindowPos3fv",
    /* 2958 */ "glWindowPos3fvARB",
    /* 2959 */ "glWindowPos3fvMESA",
    /* 2960 */ "glWindowPos3i",
    /* 2961 */ "glWindowPos3iARB",
    /* 2962 */ "glWindowPos3iMESA",
    /* 2963 */ "glWindowPos3iv",
    /* 2964 */ "glWindowPos3ivARB",
    /* 2965 */ "glWindowPos3ivMESA",
    /* 2966 */ "glWindowPos3s",
    /* 2967 */ "glWindowPos3sARB",
    /* 2968 */ "glWindowPos3sMESA",
    /* 2969 */ "glWindowPos3sv",
    /* 2970 */ "glWindowPos3svARB",
    /* 2971 */ "glWindowPos3svMESA",
    /* 2972 */ "glWindowPos4dMESA",
    /* 2973 */ "glWindowPos4dvMESA",
    /* 2974 */ "glWindowPos4fMESA",
    /* 2975 */ "glWindowPos4fvMESA",
    /* 2976 */ "glWindowPos4iMESA",
    /* 2977 */ "glWindowPos4ivMESA",
    /* 2978 */ "glWindowPos4sMESA",
    /* 2979 */ "glWindowPos4svMESA",
    /* 2980 */ "glWindowRectanglesEXT",
    /* 2981 */ "glWriteMaskEXT",
    /* 2982 */ "glAcquireTexturesANGLE",
    /* 2983 */ "glActiveShaderProgramEXT",
    /* 2984 */ "glAlphaFuncQCOM",
    /* 2985 */ "glBeginPixelLocalStorageANGLE",
    /* 2986 */ "glBeginQueryEXT",
    /* 2987 */ "glBindFragDataLocationIndexedEXT",
    /* 2988 */ "glBindProgramPipelineEXT",
    /* 2989 */ "glBindUniformLocationCHROMIUM",
    /* 2990 */ "glBindVertexArrayOES",
    /* 2991 */ "glBlendBarrier",
    /* 2992 */ "glBlendEquationSeparateiEXT",
    /* 2993 */ "glBlendEquationSeparateiOES",
    /* 2994 */ "glBlendEquationiEXT",
    /* 2995 */ "glBlendEquationiOES",
    /* 2996 */ "glBlendFuncSeparateiEXT",
    /* 2997 */ "glBlendFuncSeparateiOES",
    /* 2998 */ "glBlendFunciEXT",
    /* 2999 */ "glBlendFunciOES",
    /* 3000 */ "glBlitFramebufferANGLE",
    /* 3001 */ "glBlitFramebufferNV",
    /* 3002 */ "glBufferStorageEXT",
    /* 3003 */ "glClearPixelLocalStorageuiEXT",
    /* 3004 */ "glClearTexImageEXT",
    /* 3005 */ "glClearTexSubImageEXT",
    /* 3006 */ "glClientWaitSyncAPPLE",
    /* 3007 */ "glClipControlEXT",
    /* 3008 */ "glColorMaskiEXT",
    /* 3009 */ "glColorMaskiOES",
    /* 3010 */ "glCompressedCopyTextureCHROMIUM",
    /* 3011 */ "glCompressedTexImage2DRobustANGLE",
    /* 3012 */ "glCompressedTexImage3DOES",
    /* 3013 */ "glCompressedTexImage3DRobustANGLE",
    /* 3014 */ "glCompressedTexSubImage2DRobustANGLE",
    /* 3015 */ "glCompressedTexSubImage3DOES",
    /* 3016 */ "glCompressedTexSubImage3DRobustANGLE",
    /* 3017 */ "glCopyBufferSubDataNV",
    /* 3018 */ "glCopyImageSubDataEXT",
    /* 3019 */ "glCopyImageSubDataOES",
    /* 3020 */ "glCopySubTexture3DANGLE",
    /* 3021 */ "glCopySubTextureCHROMIUM",
    /* 3022 */ "glCopyTexSubImage3DOES",
    /* 3023 */ "glCopyTexture3DANGLE",
    /* 3024 */ "glCopyTextureCHROMIUM",
    /* 3025 */ "glCopyTextureLevelsAPPLE",
    /* 3026 */ "glCoverageMaskNV",
    /* 3027 */ "glCoverageModulationCHROMIUM",
    /* 3028 */ "glCoverageOperationNV",
    /* 3029 */ "glCreateShaderProgramvEXT",
    /* 3030 */ "glDebugMessageCallbackKHR",
    /* 3031 */ "glDebugMessageControlKHR",
    /* 3032 */ "glDebugMessageInsertKHR",
    /* 3033 */ "glDeleteProgramPipelinesEXT",
    /* 3034 */ "glDeleteQueriesEXT",
    /* 3035 */ "glDeleteSyncAPPLE",
    /* 3036 */ "glDeleteVertexArraysOES",
    /* 3037 */ "glDepthRangeArrayfvNV",
    /* 3038 */ "glDepthRangeArrayfvOES",
    /* 3039 */ "glDepthRangeIndexedfNV",
    /* 3040 */ "glDepthRangeIndexedfOES",
    /* 3041 */ "glDisableDriverControlQCOM",
    /* 3042 */ "glDisableExtensionANGLE",
    /* 3043 */ "glDisableiEXT",
    /* 3044 */ "glDisableiNV",
    /* 3045 */ "glDisableiOES",
    /* 3046 */ "glDiscardFramebufferEXT",
    /* 3047 */ "glDrawArraysInstancedANGLE",
    /* 3048 */ "glDrawArraysInstancedBaseInstanceANGLE",
    /* 3049 */ "glDrawArraysInstancedBaseInstanceEXT",
    /* 3050 */ "glDrawArraysInstancedNV",
    /* 3051 */ "glDrawBuffersEXT",
    /* 3052 */ "glDrawBuffersIndexedEXT",
    /* 3053 */ "glDrawBuffersNV",
    /* 3054 */ "glDrawElementsBaseVertexEXT",
    /* 3055 */ "glDrawElementsBaseVertexOES",
    /* 3056 */ "glDrawElementsInstancedANGLE",
    /* 3057 */ "glDrawElementsInstancedBaseInstanceEXT",
    /* 3058 */ "glDrawElementsInstancedBaseVertexBaseInstanceANGLE",
    /* 3059 */ "glDrawElementsInstancedBaseVertexBaseInstanceEXT",
    /* 3060 */ "glDrawElementsInstancedBaseVertexEXT",
    /* 3061 */ "glDrawElementsInstancedBaseVertexOES",
    /* 3062 */ "glDrawElementsInstancedNV",
    /* 3063 */ "glDrawRangeElementsBaseVertexEXT",
    /* 3064 */ "glDrawRangeElementsBaseVertexOES",
    /* 3065 */ "glDrawTransformFeedbackEXT",
    /* 3066 */ "glDrawTransformFeedbackInstancedEXT",
    /* 3067 */ "glEGLImageTargetRenderbufferStorageOES",
    /* 3068 */ "glEGLImageTargetTexture2DOES",
    /* 3069 */ "glEnableDriverControlQCOM",
    /* 3070 */ "glEnableiEXT",
    /* 3071 */ "glEnableiNV",
    /* 3072 */ "glEnableiOES",
    /* 3073 */ "glEndPixelLocalStorageANGLE",
    /* 3074 */ "glEndQueryEXT",
    /* 3075 */ "glEndTilingQCOM",
    /* 3076 */ "glExtGetBufferPointervQCOM",
    /* 3077 */ "glExtGetBuffersQCOM",
    /* 3078 */ "glExtGetFramebuffersQCOM",
    /* 3079 */ "glExtGetProgramBinarySourceQCOM",
    /* 3080 */ "glExtGetProgramsQCOM",
    /* 3081 */ "glExtGetRenderbuffersQCOM",
    /* 3082 */ "glExtGetShadersQCOM",
    /* 3083 */ "glExtGetTexLevelParameterivQCOM",
    /* 3084 */ "glExtGetTexSubImageQCOM",
    /* 3085 */ "glExtGetTexturesQCOM",
    /* 3086 */ "glExtIsProgramBinaryQCOM",
    /* 3087 */ "glExtTexObjectStateOverrideiQCOM",
    /* 3088 */ "glExtrapolateTex2DQCOM",
    /* 3089 */ "glFenceSyncAPPLE",
    /* 3090 */ "glFlushMappedBufferRangeEXT",
    /* 3091 */ "glFramebufferFetchBarrierQCOM",
    /* 3092 */ "glFramebufferFoveationConfigQCOM",
    /* 3093 */ "glFramebufferFoveationParametersQCOM",
    /* 3094 */ "glFramebufferMemorylessPixelLocalStorageANGLE",
    /* 3095 */ "glFramebufferPixelLocalClearValuefvANGLE",
    /* 3096 */ "glFramebufferPixelLocalClearValueivANGLE",
    /* 3097 */ "glFramebufferPixelLocalClearValueuivANGLE",
    /* 3098 */ "glFramebufferPixelLocalStorageInterruptANGLE",
    /* 3099 */ "glFramebufferPixelLocalStorageRestoreANGLE",
    /* 3100 */ "glFramebufferPixelLocalStorageSizeEXT",
    /* 3101 */ "glFramebufferShadingRateEXT",
    /* 3102 */ "glFramebufferTexture2DDownsampleIMG",
    /* 3103 */ "glFramebufferTexture2DMultisampleEXT",
    /* 3104 */ "glFramebufferTexture2DMultisampleIMG",
    /* 3105 */ "glFramebufferTexture3DOES",
    /* 3106 */ "glFramebufferTextureLayerDownsampleIMG",
    /* 3107 */ "glFramebufferTextureMultisampleMultiviewOVR",
    /* 3108 */ "glFramebufferTextureOES",
    /* 3109 */ "glFramebufferTexturePixelLocalStorageANGLE",
    /* 3110 */ "glGenProgramPipelinesEXT",
    /* 3111 */ "glGenQueriesEXT",
    /* 3112 */ "glGenVertexArraysOES",
    /* 3113 */ "glGetActiveUniformBlockivRobustANGLE",
    /* 3114 */ "glGetBooleani_vRobustANGLE",
    /* 3115 */ "glGetBooleanvRobustANGLE",
    /* 3116 */ "glGetBufferParameteri64vRobustANGLE",
    /* 3117 */ "glGetBufferParameterivRobustANGLE",
    /* 3118 */ "glGetBufferPointervOES",
    /* 3119 */ "glGetBufferPointervRobustANGLE",
    /* 3120 */ "glGetCompressedTexImageANGLE",
    /* 3121 */ "glGetDebugMessageLogKHR",
    /* 3122 */ "glGetDriverControlStringQCOM",
    /* 3123 */ "glGetDriverControlsQCOM",
    /* 3124 */ "glGetFloati_vNV",
    /* 3125 */ "glGetFloati_vOES",
    /* 3126 */ "glGetFloatvRobustANGLE",
    /* 3127 */ "glGetFragDataIndexEXT",
    /* 3128 */ "glGetFragmentShadingRatesEXT",
    /* 3129 */ "glGetFramebufferAttachmentParameterivRobustANGLE",
    /* 3130 */ "glGetFramebufferParameterivRobustANGLE",
    /* 3131 */ "glGetFramebufferPixelLocalStorageParameterfvANGLE",
    /* 3132 */ "glGetFramebufferPixelLocalStorageParameterfvRobustANGLE",
    /* 3133 */ "glGetFramebufferPixelLocalStorageParameterivANGLE",
    /* 3134 */ "glGetFramebufferPixelLocalStorageParameterivRobustANGLE",
    /* 3135 */ "glGetFramebufferPixelLocalStorageSizeEXT",
    /* 3136 */ "glGetGraphicsResetStatusEXT",
    /* 3137 */ "glGetGraphicsResetStatusKHR",
    /* 3138 */ "glGetInteger64i_vRobustANGLE",
    /* 3139 */ "glGetInteger64vAPPLE",
    /* 3140 */ "glGetInteger64vEXT",
    /* 3141 */ "glGetInteger64vRobustANGLE",
    /* 3142 */ "glGetIntegeri_vEXT",
    /* 3143 */ "glGetIntegeri_vRobustANGLE",
    /* 3144 */ "glGetIntegervRobustANGLE",
    /* 3145 */ "glGetInternalformativRobustANGLE",
    /* 3146 */ "glGetMultisamplefvANGLE",
    /* 3147 */ "glGetMultisamplefvRobustANGLE",
    /* 3148 */ "glGetObjectLabelKHR",
    /* 3149 */ "glGetObjectPtrLabelKHR",
    /* 3150 */ "glGetPointervKHR",
    /* 3151 */ "glGetPointervRobustANGLERobustANGLE",
    /* 3152 */ "glGetProgramBinaryOES",
    /* 3153 */ "glGetProgramInterfaceivRobustANGLE",
    /* 3154 */ "glGetProgramPipelineInfoLogEXT",
    /* 3155 */ "glGetProgramPipelineivEXT",
    /* 3156 */ "glGetProgramResourceLocationIndexEXT",
    /* 3157 */ "glGetProgramivRobustANGLE",
    /* 3158 */ "glGetQueryObjecti64vRobustANGLE",
    /* 3159 */ "glGetQueryObjectivEXT",
    /* 3160 */ "glGetQueryObjectivRobustANGLE",
    /* 3161 */ "glGetQueryObjectui64vRobustANGLE",
    /* 3162 */ "glGetQueryObjectuivEXT",
    /* 3163 */ "glGetQueryObjectuivRobustANGLE",
    /* 3164 */ "glGetQueryivEXT",
    /* 3165 */ "glGetQueryivRobustANGLE",
    /* 3166 */ "glGetRenderbufferImageANGLE",
    /* 3167 */ "glGetRenderbufferParameterivRobustANGLE",
    /* 3168 */ "glGetSamplerParameterIivEXT",
    /* 3169 */ "glGetSamplerParameterIivOES",
    /* 3170 */ "glGetSamplerParameterIivRobustANGLE",
    /* 3171 */ "glGetSamplerParameterIuivEXT",
    /* 3172 */ "glGetSamplerParameterIuivOES",
    /* 3173 */ "glGetSamplerParameterIuivRobustANGLE",
    /* 3174 */ "glGetSamplerParameterfvRobustANGLE",
    /* 3175 */ "glGetSamplerParameterivRobustANGLE",
    /* 3176 */ "glGetShaderivRobustANGLE",
    /* 3177 */ "glGetSyncivAPPLE",
    /* 3178 */ "glGetTexImageANGLE",
    /* 3179 */ "glGetTexLevelParameterfvANGLE",
    /* 3180 */ "glGetTexLevelParameterfvRobustANGLE",
    /* 3181 */ "glGetTexLevelParameterivANGLE",
    /* 3182 */ "glGetTexLevelParameterivRobustANGLE",
    /* 3183 */ "glGetTexParameterIivOES",
    /* 3184 */ "glGetTexParameterIivRobustANGLE",
    /* 3185 */ "glGetTexParameterIuivOES",
    /* 3186 */ "glGetTexParameterIuivRobustANGLE",
    /* 3187 */ "glGetTexParameterfvRobustANGLE",
    /* 3188 */ "glGetTexParameterivRobustANGLE",
    /* 3189 */ "glGetTextureHandleIMG",
    /* 3190 */ "glGetTextureSamplerHandleIMG",
    /* 3191 */ "glGetTranslatedShaderSourceANGLE",
    /* 3192 */ "glGetUniformfvRobustANGLE",
    /* 3193 */ "glGetUniformivRobustANGLE",
    /* 3194 */ "glGetUniformuivRobustANGLE",
    /* 3195 */ "glGetVertexAttribIivRobustANGLE",
    /* 3196 */ "glGetVertexAttribIuivRobustANGLE",
    /* 3197 */ "glGetVertexAttribPointervRobustANGLE",
    /* 3198 */ "glGetVertexAttribfvRobustANGLE",
    /* 3199 */ "glGetVertexAttribivRobustANGLE",
    /* 3200 */ "glGetnUniformfvEXT",
    /* 3201 */ "glGetnUniformfvKHR",
    /* 3202 */ "glGetnUniformfvRobustANGLE",
    /* 3203 */ "glGetnUniformivEXT",
    /* 3204 */ "glGetnUniformivKHR",
    /* 3205 */ "glGetnUniformivRobustANGLE",
    /* 3206 */ "glGetnUniformuivKHR",
    /* 3207 */ "glGetnUniformuivRobustANGLE",
    /* 3208 */ "glIsEnablediEXT",
    /* 3209 */ "glIsEnablediNV",
    /* 3210 */ "glIsEnablediOES",
    /* 3211 */ "glIsProgramPipelineEXT",
    /* 3212 */ "glIsQueryEXT",
    /* 3213 */ "glIsSyncAPPLE",
    /* 3214 */ "glIsVertexArrayOES",
    /* 3215 */ "glLogicOpANGLE",
    /* 3216 */ "glLoseContextCHROMIUM",
    /* 3217 */ "glMapBufferOES",
    /* 3218 */ "glMapBufferRangeEXT",
    /* 3219 */ "glMaxActiveShaderCoresARM",
    /* 3220 */ "glMinSampleShadingOES",
    /* 3221 */ "glMultiDrawArraysANGLE",
    /* 3222 */ "glMultiDrawArraysIndirectEXT",
    /* 3223 */ "glMultiDrawArraysInstancedANGLE",
    /* 3224 */ "glMultiDrawArraysInstancedBaseInstanceANGLE",
    /* 3225 */ "glMultiDrawElementsANGLE",
    /* 3226 */ "glMultiDrawElementsBaseVertexEXT",
    /* 3227 */ "glMultiDrawElementsIndirectEXT",
    /* 3228 */ "glMultiDrawElementsInstancedANGLE",
    /* 3229 */ "glMultiDrawElementsInstancedBaseVertexBaseInstanceANGLE",
    /* 3230 */ "glObjectLabelKHR",
    /* 3231 */ "glObjectPtrLabelKHR",
    /* 3232 */ "glPatchParameteriEXT",
    /* 3233 */ "glPatchParameteriOES",
    /* 3234 */ "glPixelLocalStorageBarrierANGLE",
    /* 3235 */ "glPolygonModeANGLE",
    /* 3236 */ "glPolygonModeNV",
    /* 3237 */ "glPopDebugGroupKHR",
    /* 3238 */ "glPrimitiveBoundingBox",
    /* 3239 */ "glPrimitiveBoundingBoxEXT",
    /* 3240 */ "glPrimitiveBoundingBoxOES",
    /* 3241 */ "glProgramBinaryOES",
    /* 3242 */ "glProgramUniformHandleui64IMG",
    /* 3243 */ "glProgramUniformHandleui64vIMG",
    /* 3244 */ "glProvokingVertexANGLE",
    /* 3245 */ "glPushDebugGroupKHR",
    /* 3246 */ "glQueryCounterEXT",
    /* 3247 */ "glReadBufferIndexedEXT",
    /* 3248 */ "glReadBufferNV",
    /* 3249 */ "glReadPixelsRobustANGLE",
    /* 3250 */ "glReadnPixelsEXT",
    /* 3251 */ "glReadnPixelsKHR",
    /* 3252 */ "glReadnPixelsRobustANGLE",
    /* 3253 */ "glReleaseTexturesANGLE",
    /* 3254 */ "glRenderbufferStorageMultisampleANGLE",
    /* 3255 */ "glRenderbufferStorageMultisampleAPPLE",
    /* 3256 */ "glRenderbufferStorageMultisampleIMG",
    /* 3257 */ "glRenderbufferStorageMultisampleNV",
    /* 3258 */ "glRequestExtensionANGLE",
    /* 3259 */ "glResolveMultisampleFramebufferAPPLE",
    /* 3260 */ "glSampleMaskiANGLE",
    /* 3261 */ "glSamplerParameterIivEXT",
    /* 3262 */ "glSamplerParameterIivOES",
    /* 3263 */ "glSamplerParameterIivRobustANGLE",
    /* 3264 */ "glSamplerParameterIuivEXT",
    /* 3265 */ "glSamplerParameterIuivOES",
    /* 3266 */ "glSamplerParameterIuivRobustANGLE",
    /* 3267 */ "glSamplerParameterfvRobustANGLE",
    /* 3268 */ "glSamplerParameterivRobustANGLE",
    /* 3269 */ "glScissorArrayvNV",
    /* 3270 */ "glScissorArrayvOES",
    /* 3271 */ "glScissorIndexedNV",
    /* 3272 */ "glScissorIndexedOES",
    /* 3273 */ "glScissorIndexedvNV",
    /* 3274 */ "glScissorIndexedvOES",
    /* 3275 */ "glShadingRateCombinerOpsEXT",
    /* 3276 */ "glShadingRateEXT",
    /* 3277 */ "glShadingRateQCOM",
    /* 3278 */ "glStartTilingQCOM",
    /* 3279 */ "glTexBufferOES",
    /* 3280 */ "glTexBufferRangeEXT",
    /* 3281 */ "glTexBufferRangeOES",
    /* 3282 */ "glTexEstimateMotionQCOM",
    /* 3283 */ "glTexEstimateMotionRegionsQCOM",
    /* 3284 */ "glTexImage2DRobustANGLE",
    /* 3285 */ "glTexImage3DOES",
    /* 3286 */ "glTexImage3DRobustANGLE",
    /* 3287 */ "glTexPageCommitmentEXT",
    /* 3288 */ "glTexParameterIivOES",
    /* 3289 */ "glTexParameterIivRobustANGLE",
    /* 3290 */ "glTexParameterIuivOES",
    /* 3291 */ "glTexParameterIuivRobustANGLE",
    /* 3292 */ "glTexParameterfvRobustANGLE",
    /* 3293 */ "glTexParameterivRobustANGLE",
    /* 3294 */ "glTexStorage2DMultisampleANGLE",
    /* 3295 */ "glTexStorage3DMultisampleOES",
    /* 3296 */ "glTexStorageAttribs2DEXT",
    /* 3297 */ "glTexStorageAttribs3DEXT",
    /* 3298 */ "glTexSubImage2DRobustANGLE",
    /* 3299 */ "glTexSubImage3DOES",
    /* 3300 */ "glTexSubImage3DRobustANGLE",
    /* 3301 */ "glTextureFoveationParametersQCOM",
    /* 3302 */ "glTextureViewEXT",
    /* 3303 */ "glTextureViewOES",
    /* 3304 */ "glUniformHandleui64IMG",
    /* 3305 */ "glUniformHandleui64vIMG",
    /* 3306 */ "glUniformMatrix2x3fvNV",
    /* 3307 */ "glUniformMatrix2x4fvNV",
    /* 3308 */ "glUniformMatrix3x2fvNV",
    /* 3309 */ "glUniformMatrix3x4fvNV",
    /* 3310 */ "glUniformMatrix4x2fvNV",
    /* 3311 */ "glUniformMatrix4x3fvNV",
    /* 3312 */ "glUnmapBufferOES",
    /* 3313 */ "glUseProgramStagesEXT",
    /* 3314 */ "glValidateProgramPipelineEXT",
    /* 3315 */ "glVertexAttribDivisorANGLE",
    /* 3316 */ "glVertexAttribDivisorEXT",
    /* 3317 */ "glVertexAttribDivisorNV",
    /* 3318 */ "glViewportArrayvNV",
    /* 3319 */ "glViewportArrayvOES",
    /* 3320 */ "glViewportIndexedfNV",
    /* 3321 */ "glViewportIndexedfOES",
    /* 3322 */ "glViewportIndexedfvNV",
    /* 3323 */ "glViewportIndexedfvOES",
    /* 3324 */ "glWaitSyncAPPLE"
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
    /*   57 */ 0xf1c5c3418f5bfbbc, /* GL_ANGLE_memory_object_flags */
    /*   58 */ 0x2655c424cb0e67d6, /* GL_ANGLE_memory_object_fuchsia */
    /*   59 */ 0x29c14753da729d8b, /* GL_ANGLE_memory_size */
    /*   60 */ 0x96c6dc8ae13a863f, /* GL_ANGLE_multi_draw */
    /*   61 */ 0x5648b6070cf43450, /* GL_ANGLE_pack_reverse_row_order */
    /*   62 */ 0xf830ca37ce4d57e9, /* GL_ANGLE_polygon_mode */
    /*   63 */ 0x7e99ccc7605afe66, /* GL_ANGLE_program_binary */
    /*   64 */ 0x75815242daf456c4, /* GL_ANGLE_program_cache_control */
    /*   65 */ 0x636fa9fe6b321bd4, /* GL_ANGLE_provoking_vertex */
    /*   66 */ 0xecb6507e3e1d02f8, /* GL_ANGLE_renderability_validation */
    /*   67 */ 0xe81bb93ca0cf6f2a, /* GL_ANGLE_request_extension */
    /*   68 */ 0x25833e2905e922d8, /* GL_ANGLE_rgbx_internal_format */
    /*   69 */ 0xe20f551fc33bd429, /* GL_ANGLE_robust_client_memory */
    /*   70 */ 0xf0b98d581ffeb5e0, /* GL_ANGLE_robust_fragment_shader_output */
    /*   71 */ 0x5d895fe77bc5a43f, /* GL_ANGLE_robust_resource_initialization */
    /*   72 */ 0xd4ba1c0aafe5b41f, /* GL_ANGLE_semaphore_fuchsia */
    /*   73 */ 0x69a67f8bce5ed738, /* GL_ANGLE_shader_pixel_local_storage */
    /*   74 */ 0x1cdf91894ef6922d, /* GL_ANGLE_stencil_texturing */
    /*   75 */ 0x6dd97fced6819d19, /* GL_ANGLE_texture_compression_dxt */
    /*   76 */ 0x3ced8289e55b381f, /* GL_ANGLE_texture_compression_dxt3 */
    /*   77 */ 0xe031d89a47ab0e88, /* GL_ANGLE_texture_compression_dxt5 */
    /*   78 */ 0x261f90903ebb2b21, /* GL_ANGLE_texture_external_update */
    /*   79 */ 0xbae723a89da1bdfd, /* GL_ANGLE_texture_multisample */
    /*   80 */ 0x2164a76cb4716269, /* GL_ANGLE_texture_usage */
    /*   81 */ 0xaa724fba9f206a4e, /* GL_ANGLE_timer_query */
    /*   82 */ 0x210dd20de1d385d7, /* GL_ANGLE_translated_shader_source */
    /*   83 */ 0x186b1da5d851bbec, /* GL_ANGLE_vulkan_image */
    /*   84 */ 0xf870cb9d6ba30da8, /* GL_ANGLE_yuv_internal_format */
    /*   85 */ 0xedd8d13a9eab22a7, /* GL_APPLE_aux_depth_stencil */
    /*   86 */ 0x9cb930c662d0cbc5, /* GL_APPLE_client_storage */
    /*   87 */ 0xca00966a7d53874d, /* GL_APPLE_clip_distance */
    /*   88 */ 0x8b12f4834ed80365, /* GL_APPLE_color_buffer_packed_float */
    /*   89 */ 0x3b1ff61d2ca7ebef, /* GL_APPLE_copy_texture_levels */
    /*   90 */ 0x393954d6a157dc34, /* GL_APPLE_element_array */
    /*   91 */ 0x248c97fa0866c224, /* GL_APPLE_fence */
    /*   92 */ 0x4b598c5361e19ad0, /* GL_APPLE_float_pixels */
    /*   93 */ 0x90a2f67506c1c227, /* GL_APPLE_flush_buffer_range */
    /*   94 */ 0x349436461b4902f0, /* GL_APPLE_framebuffer_multisample */
    /*   95 */ 0x41f28225bfe72cb5, /* GL_APPLE_object_purgeable */
    /*   96 */ 0xc380c84097cc2eaa, /* GL_APPLE_rgb_422 */
    /*   97 */ 0x65041d91620fe255, /* GL_APPLE_row_bytes */
    /*   98 */ 0xe73b092a3adf8b6f, /* GL_APPLE_specular_vector */
    /*   99 */ 0x965df8be0c61c5ef, /* GL_APPLE_sync */
    /*  100 */ 0xd46cf8fd7182caf2, /* GL_APPLE_texture_format_BGRA8888 */
    /*  101 */ 0x45f22d7fbb944c1a, /* GL_APPLE_texture_max_level */
    /*  102 */ 0x9d3d6479810f97ac, /* GL_APPLE_texture_packed_float */
    /*  103 */ 0x9ab7d0b3c514d378, /* GL_APPLE_texture_range */
    /*  104 */ 0x5d3f53e18fb3ff55, /* GL_APPLE_transform_hint */
    /*  105 */ 0xb0874f6446afabce, /* GL_APPLE_vertex_array_object */
    /*  106 */ 0xd3da8f94dff875f1, /* GL_APPLE_vertex_array_range */
    /*  107 */ 0x9bf0cbe91e220c86, /* GL_APPLE_vertex_program_evaluators */
    /*  108 */ 0xe908f191198042d8, /* GL_APPLE_ycbcr_422 */
    /*  109 */ 0x1f6122983853ff45, /* GL_ARB_ES2_compatibility */
    /*  110 */ 0xa9d98ac21fcaf80b, /* GL_ARB_ES3_1_compatibility */
    /*  111 */ 0x8945b05fdf09b074, /* GL_ARB_ES3_2_compatibility */
    /*  112 */ 0xea26087e653cab2b, /* GL_ARB_ES3_compatibility */
    /*  113 */ 0x08410053810ead05, /* GL_ARB_arrays_of_arrays */
    /*  114 */ 0x40b475be6ab996bb, /* GL_ARB_base_instance */
    /*  115 */ 0xb2e0c01fbc4a0d90, /* GL_ARB_bindless_texture */
    /*  116 */ 0x98330877cd269847, /* GL_ARB_blend_func_extended */
    /*  117 */ 0x2aa09aeb0f69408b, /* GL_ARB_buffer_storage */
    /*  118 */ 0xf1d364213ef0dd70, /* GL_ARB_cl_event */
    /*  119 */ 0x68a226aab21d4c06, /* GL_ARB_clear_buffer_object */
    /*  120 */ 0xb9bb33941fa4b35f, /* GL_ARB_clear_texture */
    /*  121 */ 0x0062a8cb7bae8d41, /* GL_ARB_clip_control */
    /*  122 */ 0x9ab3cde2bbe8e41c, /* GL_ARB_color_buffer_float */
    /*  123 */ 0xe421f74d58d12f0f, /* GL_ARB_compatibility */
    /*  124 */ 0xfcfdeecd633ecd3f, /* GL_ARB_compressed_texture_pixel_storage */
    /*  125 */ 0xd9df667054f06223, /* GL_ARB_compute_shader */
    /*  126 */ 0xc49c40e9865275e6, /* GL_ARB_compute_variable_group_size */
    /*  127 */ 0x6bf8cd6035aef76c, /* GL_ARB_conditional_render_inverted */
    /*  128 */ 0xcc005319118f39bb, /* GL_ARB_conservative_depth */
    /*  129 */ 0x66bffd41bcf61546, /* GL_ARB_copy_buffer */
    /*  130 */ 0x66cd5d5964674061, /* GL_ARB_copy_image */
    /*  131 */ 0x59cf6e44c2fc962a, /* GL_ARB_cull_distance */
    /*  132 */ 0x2b16e3dcc2f78c79, /* GL_ARB_debug_output */
    /*  133 */ 0x3f93699d406e0f0e, /* GL_ARB_depth_buffer_float */
    /*  134 */ 0x53b30bc0d3be88f6, /* GL_ARB_depth_clamp */
    /*  135 */ 0xd0e68b1ed9117edf, /* GL_ARB_depth_texture */
    /*  136 */ 0x34fe88e233827c23, /* GL_ARB_derivative_control */
    /*  137 */ 0x8e24d5c3614e8aa2, /* GL_ARB_direct_state_access */
    /*  138 */ 0xe11ab2833ee38b1a, /* GL_ARB_draw_buffers */
    /*  139 */ 0xae64ff49ea7e95af, /* GL_ARB_draw_buffers_blend */
    /*  140 */ 0xe8f87e4358abe5ad, /* GL_ARB_draw_elements_base_vertex */
    /*  141 */ 0x115e5b64ca1e3904, /* GL_ARB_draw_indirect */
    /*  142 */ 0x1b97c8e7f6e23b1d, /* GL_ARB_draw_instanced */
    /*  143 */ 0x43e30679379342ce, /* GL_ARB_enhanced_layouts */
    /*  144 */ 0xae63483486dde7ca, /* GL_ARB_explicit_attrib_location */
    /*  145 */ 0x2024ab894c4d472e, /* GL_ARB_explicit_uniform_location */
    /*  146 */ 0x5f268b1f7c820480, /* GL_ARB_fragment_coord_conventions */
    /*  147 */ 0x737ecdaaf0007deb, /* GL_ARB_fragment_layer_viewport */
    /*  148 */ 0x73c41f19063c2fe6, /* GL_ARB_fragment_program */
    /*  149 */ 0xefae304da60b251d, /* GL_ARB_fragment_program_shadow */
    /*  150 */ 0x52146e3d84c4168c, /* GL_ARB_fragment_shader */
    /*  151 */ 0x0c70408f81c04928, /* GL_ARB_fragment_shader_interlock */
    /*  152 */ 0x2448dc255a192f81, /* GL_ARB_framebuffer_no_attachments */
    /*  153 */ 0x1fbce4d5ca5a1f15, /* GL_ARB_framebuffer_object */
    /*  154 */ 0x7423a1c932459cca, /* GL_ARB_framebuffer_sRGB */
    /*  155 */ 0xf680b4cebba73b4e, /* GL_ARB_geometry_shader4 */
    /*  156 */ 0xa3d697b5a581321a, /* GL_ARB_get_program_binary */
    /*  157 */ 0xeff63c42ef3b05e6, /* GL_ARB_get_texture_sub_image */
    /*  158 */ 0xea214db7cd5e19d1, /* GL_ARB_gl_spirv */
    /*  159 */ 0x2c7de1df96f6285a, /* GL_ARB_gpu_shader5 */
    /*  160 */ 0x19c411e568c50761, /* GL_ARB_gpu_shader_fp64 */
    /*  161 */ 0xbed2c39a8ee82e31, /* GL_ARB_gpu_shader_int64 */
    /*  162 */ 0x54e0f735df67d1a9, /* GL_ARB_half_float_pixel */
    /*  163 */ 0x49a053607b3fe223, /* GL_ARB_half_float_vertex */
    /*  164 */ 0x4569da13c0840fbe, /* GL_ARB_imaging */
    /*  165 */ 0x3b7fae1bd2e0c889, /* GL_ARB_indirect_parameters */
    /*  166 */ 0x3b10779fb6b7fcbb, /* GL_ARB_instanced_arrays */
    /*  167 */ 0xf96f1159070d5ce7, /* GL_ARB_internalformat_query */
    /*  168 */ 0x80a297f08b3101df, /* GL_ARB_internalformat_query2 */
    /*  169 */ 0x6a0e063354f3a32c, /* GL_ARB_invalidate_subdata */
    /*  170 */ 0x70a2bf7a3574e20f, /* GL_ARB_map_buffer_alignment */
    /*  171 */ 0xbf533265f999152c, /* GL_ARB_map_buffer_range */
    /*  172 */ 0xfbe76f26f72891f3, /* GL_ARB_matrix_palette */
    /*  173 */ 0xc2eb1cf0ae1fb90b, /* GL_ARB_multi_bind */
    /*  174 */ 0x05681bd649da4453, /* GL_ARB_multi_draw_indirect */
    /*  175 */ 0x494b5f42fc0a83e4, /* GL_ARB_multisample */
    /*  176 */ 0x4a56c37f2c0b7aad, /* GL_ARB_multitexture */
    /*  177 */ 0xe8818f3733977678, /* GL_ARB_occlusion_query */
    /*  178 */ 0x06e18ccc664317eb, /* GL_ARB_occlusion_query2 */
    /*  179 */ 0x5d7b0c48219844f4, /* GL_ARB_parallel_shader_compile */
    /*  180 */ 0x6399433cf89bb920, /* GL_ARB_pipeline_statistics_query */
    /*  181 */ 0xac3ec29ab5db4b9e, /* GL_ARB_pixel_buffer_object */
    /*  182 */ 0xffe8ee561ae2346c, /* GL_ARB_point_parameters */
    /*  183 */ 0xb48886ec024907bb, /* GL_ARB_point_sprite */
    /*  184 */ 0x0c2f051e773ac84a, /* GL_ARB_polygon_offset_clamp */
    /*  185 */ 0x94125022598b506e, /* GL_ARB_post_depth_coverage */
    /*  186 */ 0x680e7d29d6b97883, /* GL_ARB_program_interface_query */
    /*  187 */ 0x028da0039f30b414, /* GL_ARB_provoking_vertex */
    /*  188 */ 0x76c8a711474dcb0e, /* GL_ARB_query_buffer_object */
    /*  189 */ 0x4b042cda7a10234c, /* GL_ARB_robust_buffer_access_behavior */
    /*  190 */ 0x321298a6a261de34, /* GL_ARB_robustness */
    /*  191 */ 0x945bce717134d350, /* GL_ARB_robustness_isolation */
    /*  192 */ 0x94596e17ac6ec3c8, /* GL_ARB_sample_locations */
    /*  193 */ 0x7870651576fc1ccd, /* GL_ARB_sample_shading */
    /*  194 */ 0x1db0e3c87246c7f7, /* GL_ARB_sampler_objects */
    /*  195 */ 0x6d414fea6b2a0b05, /* GL_ARB_seamless_cube_map */
    /*  196 */ 0xbe6ffda1c253ce69, /* GL_ARB_seamless_cubemap_per_texture */
    /*  197 */ 0xf39b353f6c8d6795, /* GL_ARB_separate_shader_objects */
    /*  198 */ 0x2c6b3e0ac4318eac, /* GL_ARB_shader_atomic_counter_ops */
    /*  199 */ 0x4d13222ef8dc85a8, /* GL_ARB_shader_atomic_counters */
    /*  200 */ 0xb7f68cebd72707b2, /* GL_ARB_shader_ballot */
    /*  201 */ 0x6157ef1dc9a5ec6a, /* GL_ARB_shader_bit_encoding */
    /*  202 */ 0x604fb19fc38ead7b, /* GL_ARB_shader_clock */
    /*  203 */ 0x44796ed6cecb76dd, /* GL_ARB_shader_draw_parameters */
    /*  204 */ 0x24f42ed6fd7e1224, /* GL_ARB_shader_group_vote */
    /*  205 */ 0x8e1d8ffee2ffc980, /* GL_ARB_shader_image_load_store */
    /*  206 */ 0x3c986ee0af879682, /* GL_ARB_shader_image_size */
    /*  207 */ 0xd8de76a336031ff0, /* GL_ARB_shader_objects */
    /*  208 */ 0x06bce3aace8af5a7, /* GL_ARB_shader_precision */
    /*  209 */ 0x10bfd775e284ac36, /* GL_ARB_shader_stencil_export */
    /*  210 */ 0x191e16f9c16a5423, /* GL_ARB_shader_storage_buffer_object */
    /*  211 */ 0x9f832fb5b2517157, /* GL_ARB_shader_subroutine */
    /*  212 */ 0xa53df22a8387d8c0, /* GL_ARB_shader_texture_image_samples */
    /*  213 */ 0xfd460b3ffea5238e, /* GL_ARB_shader_texture_lod */
    /*  214 */ 0x3b0ccc78e1ae6cce, /* GL_ARB_shader_viewport_layer_array */
    /*  215 */ 0xf2d5eb1652b5c218, /* GL_ARB_shading_language_100 */
    /*  216 */ 0x566b1b0b87fe805d, /* GL_ARB_shading_language_420pack */
    /*  217 */ 0x2f59115a058a0c1a, /* GL_ARB_shading_language_include */
    /*  218 */ 0x6c8387915ce0e735, /* GL_ARB_shading_language_packing */
    /*  219 */ 0xd6597e1597f4f3cf, /* GL_ARB_shadow */
    /*  220 */ 0xecdc51a7a12e0820, /* GL_ARB_shadow_ambient */
    /*  221 */ 0xcc6098f61c4e626a, /* GL_ARB_sparse_buffer */
    /*  222 */ 0xb8b8ba783156beb9, /* GL_ARB_sparse_texture */
    /*  223 */ 0xa11019635b421922, /* GL_ARB_sparse_texture2 */
    /*  224 */ 0x7dc85bdb35fadb35, /* GL_ARB_sparse_texture_clamp */
    /*  225 */ 0xcf62e2741dd9a807, /* GL_ARB_spirv_extensions */
    /*  226 */ 0xa56221685de2b254, /* GL_ARB_stencil_texturing */
    /*  227 */ 0x0d3c113e7ffc3be4, /* GL_ARB_sync */
    /*  228 */ 0xaefddf2f9dcfa46a, /* GL_ARB_tessellation_shader */
    /*  229 */ 0x9d0747678a9d3fdf, /* GL_ARB_texture_barrier */
    /*  230 */ 0xb4a8554df00d4ede, /* GL_ARB_texture_border_clamp */
    /*  231 */ 0xc59d9bef1f9b2de9, /* GL_ARB_texture_buffer_object */
    /*  232 */ 0xbab79763204b079a, /* GL_ARB_texture_buffer_object_rgb32 */
    /*  233 */ 0x843bbbf9107595d8, /* GL_ARB_texture_buffer_range */
    /*  234 */ 0x582477dc03c7221c, /* GL_ARB_texture_compression */
    /*  235 */ 0x83bfab2872b14819, /* GL_ARB_texture_compression_bptc */
    /*  236 */ 0x5e62ceda4eb9b901, /* GL_ARB_texture_compression_rgtc */
    /*  237 */ 0xac7bb6c963c7dd4c, /* GL_ARB_texture_cube_map */
    /*  238 */ 0x68d233a2df517789, /* GL_ARB_texture_cube_map_array */
    /*  239 */ 0x9061271ef3971e4d, /* GL_ARB_texture_env_add */
    /*  240 */ 0x729ad094490ac067, /* GL_ARB_texture_env_combine */
    /*  241 */ 0xc258a95e80a7ac1d, /* GL_ARB_texture_env_crossbar */
    /*  242 */ 0x87e8597c801caffb, /* GL_ARB_texture_env_dot3 */
    /*  243 */ 0xf8867e9b2392c62c, /* GL_ARB_texture_filter_anisotropic */
    /*  244 */ 0x9a2662f4f2a023fc, /* GL_ARB_texture_filter_minmax */
    /*  245 */ 0x6f4b69f418935051, /* GL_ARB_texture_float */
    /*  246 */ 0xa57e1ab78c203089, /* GL_ARB_texture_gather */
    /*  247 */ 0x7c5b8fd73b8f1d2a, /* GL_ARB_texture_mirror_clamp_to_edge */
    /*  248 */ 0x7f8109dad2ae72ac, /* GL_ARB_texture_mirrored_repeat */
    /*  249 */ 0xce2742707049542e, /* GL_ARB_texture_multisample */
    /*  250 */ 0x39526d131df64c59, /* GL_ARB_texture_non_power_of_two */
    /*  251 */ 0x46b457622b5dab21, /* GL_ARB_texture_query_levels */
    /*  252 */ 0x0c5b6193b98fc63b, /* GL_ARB_texture_query_lod */
    /*  253 */ 0x5d6d6585c47fc200, /* GL_ARB_texture_rectangle */
    /*  254 */ 0xb7acf24a6eb5a7f4, /* GL_ARB_texture_rg */
    /*  255 */ 0x97b3807033cf6f62, /* GL_ARB_texture_rgb10_a2ui */
    /*  256 */ 0x12a12b44ee899f08, /* GL_ARB_texture_stencil8 */
    /*  257 */ 0x2bb0e7be62c590f8, /* GL_ARB_texture_storage */
    /*  258 */ 0xeacfe755a96db7a7, /* GL_ARB_texture_storage_multisample */
    /*  259 */ 0x421bedbb68fd4661, /* GL_ARB_texture_swizzle */
    /*  260 */ 0x5b877369a37b65e6, /* GL_ARB_texture_view */
    /*  261 */ 0x0d8a574b96669a1b, /* GL_ARB_timer_query */
    /*  262 */ 0xeaa1709ae2b12764, /* GL_ARB_transform_feedback2 */
    /*  263 */ 0xfbc74ea814b15d2f, /* GL_ARB_transform_feedback3 */
    /*  264 */ 0x3f96154fd49046f3, /* GL_ARB_transform_feedback_instanced */
    /*  265 */ 0xf54fc92b7e8ec635, /* GL_ARB_transform_feedback_overflow_query */
    /*  266 */ 0x77013d69fddefe87, /* GL_ARB_transpose_matrix */
    /*  267 */ 0x7f397ae5fad4b735, /* GL_ARB_uniform_buffer_object */
    /*  268 */ 0x502a9d2c5469c136, /* GL_ARB_vertex_array_bgra */
    /*  269 */ 0x1a1e2d3306313eb9, /* GL_ARB_vertex_array_object */
    /*  270 */ 0x7b47ed54530d0661, /* GL_ARB_vertex_attrib_64bit */
    /*  271 */ 0xe394a5028a00c565, /* GL_ARB_vertex_attrib_binding */
    /*  272 */ 0xbe2f3323a7af4844, /* GL_ARB_vertex_blend */
    /*  273 */ 0xab4f226cf8bf14b2, /* GL_ARB_vertex_buffer_object */
    /*  274 */ 0x2b91406e8801f26d, /* GL_ARB_vertex_program */
    /*  275 */ 0xb74f5593e3c89e02, /* GL_ARB_vertex_shader */
    /*  276 */ 0x5adbfa9b8494c869, /* GL_ARB_vertex_type_10f_11f_11f_rev */
    /*  277 */ 0x70aa23c3893ff4f7, /* GL_ARB_vertex_type_2_10_10_10_rev */
    /*  278 */ 0x11f657f3da3dbeb7, /* GL_ARB_viewport_array */
    /*  279 */ 0x8fd0fb55626075a1, /* GL_ARB_window_pos */
    /*  280 */ 0x2fbeb7cb81220b5e, /* GL_ARM_mali_program_binary */
    /*  281 */ 0x174de60965d38c78, /* GL_ARM_mali_shader_binary */
    /*  282 */ 0x0770bcbef6d87ecc, /* GL_ARM_rgba8 */
    /*  283 */ 0xd022cfc81a420445, /* GL_ARM_shader_core_properties */
    /*  284 */ 0xf0d2f4cff333f04e, /* GL_ARM_shader_framebuffer_fetch */
    /*  285 */ 0xbfa10a2d7557623f, /* GL_ARM_shader_framebuffer_fetch_depth_stencil */
    /*  286 */ 0x8a7a1adbc8af57ff, /* GL_ARM_texture_unnormalized_coordinates */
    /*  287 */ 0xc43e90f15fb8db01, /* GL_ATI_draw_buffers */
    /*  288 */ 0x237ddecca4711d26, /* GL_ATI_element_array */
    /*  289 */ 0x8465366774288b57, /* GL_ATI_envmap_bumpmap */
    /*  290 */ 0x7eace62f803a3a1d, /* GL_ATI_fragment_shader */
    /*  291 */ 0x601618adc78f06ed, /* GL_ATI_map_object_buffer */
    /*  292 */ 0xc2367d65629265d3, /* GL_ATI_meminfo */
    /*  293 */ 0x3ed6aa98977b6026, /* GL_ATI_pixel_format_float */
    /*  294 */ 0xecc62354179a5498, /* GL_ATI_pn_triangles */
    /*  295 */ 0xc9e128c539750596, /* GL_ATI_separate_stencil */
    /*  296 */ 0xf8002b1602911364, /* GL_ATI_text_fragment_shader */
    /*  297 */ 0x8f696d877000fa6a, /* GL_ATI_texture_env_combine3 */
    /*  298 */ 0x72137067e0c140bc, /* GL_ATI_texture_float */
    /*  299 */ 0x184114955f32fded, /* GL_ATI_texture_mirror_once */
    /*  300 */ 0x99180d4f8d9c5d52, /* GL_ATI_vertex_array_object */
    /*  301 */ 0x4bedffd7142a0313, /* GL_ATI_vertex_attrib_array_object */
    /*  302 */ 0xf2a1201512faef81, /* GL_ATI_vertex_streams */
    /*  303 */ 0x9a85b4342c34b2f8, /* GL_CHROMIUM_bind_uniform_location */
    /*  304 */ 0x0dd808babc9daaab, /* GL_CHROMIUM_copy_compressed_texture */
    /*  305 */ 0xe6bdf6222c3733ef, /* GL_CHROMIUM_copy_texture */
    /*  306 */ 0x0bd5e31cc0c829e7, /* GL_CHROMIUM_framebuffer_mixed_samples */
    /*  307 */ 0x04af64470030272e, /* GL_CHROMIUM_lose_context */
    /*  308 */ 0x2b55ba018525895b, /* GL_DMP_program_binary */
    /*  309 */ 0x8e5f4ce24de544d5, /* GL_DMP_shader_binary */
    /*  310 */ 0x0cf95c40c08a43a8, /* GL_EXT_422_pixels */
    /*  311 */ 0x2a61d7b733e75c77, /* GL_EXT_EGL_image_array */
    /*  312 */ 0x35b7bb88d6ff4a1e, /* GL_EXT_EGL_image_storage */
    /*  313 */ 0xfe8066998f34da8e, /* GL_EXT_EGL_image_storage_compression */
    /*  314 */ 0xb8221664855c83bd, /* GL_EXT_EGL_sync */
    /*  315 */ 0x6fac3cb4234e6c59, /* GL_EXT_YUV_target */
    /*  316 */ 0xc118d96a66b6bea3, /* GL_EXT_abgr */
    /*  317 */ 0x6b5e9b6cfbdc3dc0, /* GL_EXT_base_instance */
    /*  318 */ 0x2c343f7622589325, /* GL_EXT_bgra */
    /*  319 */ 0x9d83c1e02304fb00, /* GL_EXT_bindable_uniform */
    /*  320 */ 0x1cafcd91efe0e1d6, /* GL_EXT_blend_color */
    /*  321 */ 0x3510ec477f22f7e7, /* GL_EXT_blend_equation_separate */
    /*  322 */ 0x888e740cefe39cc4, /* GL_EXT_blend_func_extended */
    /*  323 */ 0x97c1a7c0b569dfb8, /* GL_EXT_blend_func_separate */
    /*  324 */ 0x709f5d763ef0911f, /* GL_EXT_blend_logic_op */
    /*  325 */ 0x1163ab5d43e9b052, /* GL_EXT_blend_minmax */
    /*  326 */ 0x2c5c11d0c1161814, /* GL_EXT_blend_subtract */
    /*  327 */ 0x8a59c192ebd08825, /* GL_EXT_buffer_reference */
    /*  328 */ 0x1fe18a884a2d4d2a, /* GL_EXT_buffer_reference2 */
    /*  329 */ 0xf57e9c9fe9c776cd, /* GL_EXT_buffer_storage */
    /*  330 */ 0xaafb791a26428890, /* GL_EXT_clear_texture */
    /*  331 */ 0x9452d292aa14805e, /* GL_EXT_clip_control */
    /*  332 */ 0x5737e20452f91527, /* GL_EXT_clip_cull_distance */
    /*  333 */ 0x56a5c2f21e51bb5a, /* GL_EXT_clip_volume_hint */
    /*  334 */ 0x82b62c808e4abb64, /* GL_EXT_cmyka */
    /*  335 */ 0xa297c2c3a49a99be, /* GL_EXT_color_buffer_float */
    /*  336 */ 0xf9449646b78eab54, /* GL_EXT_color_buffer_half_float */
    /*  337 */ 0x6d76340b1318b839, /* GL_EXT_color_subtable */
    /*  338 */ 0xf1bda7fa0a83d383, /* GL_EXT_compiled_vertex_array */
    /*  339 */ 0x9ddf99bdc50f4149, /* GL_EXT_conservative_depth */
    /*  340 */ 0x354415fe7a6e013e, /* GL_EXT_control_flow_attributes */
    /*  341 */ 0xe9260724f594f80b, /* GL_EXT_convolution */
    /*  342 */ 0xf9792a196e0ab7c9, /* GL_EXT_coordinate_frame */
    /*  343 */ 0xa26b121ae33c3436, /* GL_EXT_copy_image */
    /*  344 */ 0x2611c2618f21aa2f, /* GL_EXT_copy_texture */
    /*  345 */ 0xddfc92096368bfbb, /* GL_EXT_cull_vertex */
    /*  346 */ 0xed15a3d914865c56, /* GL_EXT_debug_label */
    /*  347 */ 0x84891a2031a0f162, /* GL_EXT_debug_marker */
    /*  348 */ 0x3d46dbc8319361c9, /* GL_EXT_debug_printf */
    /*  349 */ 0x2a423943f8be1307, /* GL_EXT_demote_to_helper_invocation */
    /*  350 */ 0xe21a2b607eb5c6bb, /* GL_EXT_depth_bounds_test */
    /*  351 */ 0xdc5fb3a8d43d753e, /* GL_EXT_depth_clamp */
    /*  352 */ 0xee026f0d1b48c324, /* GL_EXT_device_group */
    /*  353 */ 0xff4a74da40c62745, /* GL_EXT_direct_state_access */
    /*  354 */ 0x3287a129fb1e11c1, /* GL_EXT_discard_framebuffer */
    /*  355 */ 0x3d06b0f91612d10d, /* GL_EXT_disjoint_timer_query */
    /*  356 */ 0xd3ac9ca278a62f1a, /* GL_EXT_draw_buffers */
    /*  357 */ 0x5d6aa36dbdce372d, /* GL_EXT_draw_buffers2 */
    /*  358 */ 0x997893a6ac44f7fe, /* GL_EXT_draw_buffers_indexed */
    /*  359 */ 0x548657f15226635b, /* GL_EXT_draw_elements_base_vertex */
    /*  360 */ 0xeb1b622faf7697c7, /* GL_EXT_draw_instanced */
    /*  361 */ 0xbb5e6eb0e1559ef1, /* GL_EXT_draw_range_elements */
    /*  362 */ 0x0ccbfada83c13182, /* GL_EXT_draw_transform_feedback */
    /*  363 */ 0x5e1ad5852ce64f31, /* GL_EXT_external_buffer */
    /*  364 */ 0x18d7b8f80d477ce9, /* GL_EXT_float_blend */
    /*  365 */ 0xe09e32cd1ae79288, /* GL_EXT_fog_coord */
    /*  366 */ 0xc117232bce18d68e, /* GL_EXT_fragment_invocation_density */
    /*  367 */ 0x2f9b21678a5e0043, /* GL_EXT_fragment_shader_barycentric */
    /*  368 */ 0xde0a545f611c91b2, /* GL_EXT_fragment_shading_rate */
    /*  369 */ 0xdefc19d979b2e3e2, /* GL_EXT_framebuffer_blit */
    /*  370 */ 0x616048bcd1aa9223, /* GL_EXT_framebuffer_blit_layers */
    /*  371 */ 0x8cbb2537704d8953, /* GL_EXT_framebuffer_multisample */
    /*  372 */ 0x5634f30b2756d601, /* GL_EXT_framebuffer_multisample_blit_scaled */
    /*  373 */ 0x8350f19ac13e7c07, /* GL_EXT_framebuffer_object */
    /*  374 */ 0xa45a63878264c1e5, /* GL_EXT_framebuffer_sRGB */
    /*  375 */ 0x30d017755de50dd9, /* GL_EXT_geometry_point_size */
    /*  376 */ 0xfa22129bb4d04128, /* GL_EXT_geometry_shader */
    /*  377 */ 0x5370f0fbdd1b1f1d, /* GL_EXT_geometry_shader4 */
    /*  378 */ 0x3604f5b2b65016b2, /* GL_EXT_gpu_program_parameters */
    /*  379 */ 0x020c60828c37ce5d, /* GL_EXT_gpu_shader4 */
    /*  380 */ 0x53dbe9871073dca3, /* GL_EXT_gpu_shader5 */
    /*  381 */ 0xcebb9285fc482cfd, /* GL_EXT_histogram */
    /*  382 */ 0x64ea7e43377361ff, /* GL_EXT_index_array_formats */
    /*  383 */ 0xecf771ddabe3f8ed, /* GL_EXT_index_func */
    /*  384 */ 0x649623e695acbfb0, /* GL_EXT_index_material */
    /*  385 */ 0x43fd3f035960e92c, /* GL_EXT_index_texture */
    /*  386 */ 0x9c3c026caab1aaf7, /* GL_EXT_instanced_arrays */
    /*  387 */ 0x6b0a475df16ae9f2, /* GL_EXT_light_texture */
    /*  388 */ 0xf41152d50d03cc16, /* GL_EXT_map_buffer_range */
    /*  389 */ 0xebb55934637c6ab7, /* GL_EXT_memory_object */
    /*  390 */ 0x7e941665b79d31c4, /* GL_EXT_memory_object_fd */
    /*  391 */ 0x6bf3a6b6ec24354b, /* GL_EXT_memory_object_win32 */
    /*  392 */ 0xda6fb882011aa28e, /* GL_EXT_misc_attribute */
    /*  393 */ 0x6077bed8aa109362, /* GL_EXT_multi_draw_arrays */
    /*  394 */ 0x55b4806b38f2b08e, /* GL_EXT_multi_draw_indirect */
    /*  395 */ 0x872a66595e5024ca, /* GL_EXT_multisample */
    /*  396 */ 0x3e4a3b0ff8584927, /* GL_EXT_multisampled_compatibility */
    /*  397 */ 0x33b89ab037aed106, /* GL_EXT_multisampled_render_to_texture */
    /*  398 */ 0x39f0379607d459f0, /* GL_EXT_multisampled_render_to_texture2 */
    /*  399 */ 0x49f63d58daabfccb, /* GL_EXT_multiview_draw_buffers */
    /*  400 */ 0x5b7a6a36ed0fe897, /* GL_EXT_multiview_tessellation_geometry_shader */
    /*  401 */ 0x3679a0ac14e16e97, /* GL_EXT_multiview_texture_multisample */
    /*  402 */ 0x39d0f3848228d38f, /* GL_EXT_multiview_timer_query */
    /*  403 */ 0x0d7bdf1d96e54238, /* GL_EXT_nonuniform_qualifier */
    /*  404 */ 0xbf12db2b88c87ccf, /* GL_EXT_occlusion_query_boolean */
    /*  405 */ 0x757af2451eae9d25, /* GL_EXT_packed_depth_stencil */
    /*  406 */ 0x2ace1d8656332b56, /* GL_EXT_packed_float */
    /*  407 */ 0x248d529c3993285c, /* GL_EXT_packed_pixels */
    /*  408 */ 0xecd5d2503b35bb13, /* GL_EXT_paletted_texture */
    /*  409 */ 0xc7f3ad7137661622, /* GL_EXT_pixel_buffer_object */
    /*  410 */ 0x59d7be95f9b27b9a, /* GL_EXT_pixel_transform */
    /*  411 */ 0xd7024b008ea1463b, /* GL_EXT_pixel_transform_color_table */
    /*  412 */ 0x14eaf45986c9bfa1, /* GL_EXT_point_parameters */
    /*  413 */ 0x5640aa3e3a0202cb, /* GL_EXT_polygon_offset */
    /*  414 */ 0xd55f7ac9bd1eba74, /* GL_EXT_polygon_offset_clamp */
    /*  415 */ 0x55695328ecdeb972, /* GL_EXT_post_depth_coverage */
    /*  416 */ 0x849565c10789238e, /* GL_EXT_primitive_bounding_box */
    /*  417 */ 0x638afa82b47ca539, /* GL_EXT_protected_textures */
    /*  418 */ 0xfc1cd6391217f09e, /* GL_EXT_provoking_vertex */
    /*  419 */ 0xc36c4a5ae294a717, /* GL_EXT_pvrtc_sRGB */
    /*  420 */ 0x864a43fa5616bb8c, /* GL_EXT_raster_multisample */
    /*  421 */ 0xb0b19c0e9f3b0f5c, /* GL_EXT_ray_cull_mask */
    /*  422 */ 0xd982b05f307f6fcd, /* GL_EXT_ray_flags_primitive_culling */
    /*  423 */ 0xbf4a58353f9a7a75, /* GL_EXT_ray_query */
    /*  424 */ 0x5d7ccf8ac93b7140, /* GL_EXT_ray_tracing */
    /*  425 */ 0x1b664521b8e7cedd, /* GL_EXT_read_format_bgra */
    /*  426 */ 0x461ed0af7d9ee57e, /* GL_EXT_render_snorm */
    /*  427 */ 0xc99a47326d03fd17, /* GL_EXT_rescale_normal */
    /*  428 */ 0x04aaf7c50fd23609, /* GL_EXT_robustness */
    /*  429 */ 0x72a714dfac11ff63, /* GL_EXT_sRGB */
    /*  430 */ 0xa329e9d07bf41faa, /* GL_EXT_sRGB_write_control */
    /*  431 */ 0x6c203c99634fa814, /* GL_EXT_samplerless_texture_functions */
    /*  432 */ 0xe045958c8c43c35f, /* GL_EXT_scalar_block_layout */
    /*  433 */ 0x5da9f01e568b2e0b, /* GL_EXT_secondary_color */
    /*  434 */ 0x40ea8dbcbb4d106f, /* GL_EXT_semaphore */
    /*  435 */ 0xb3de6f78cadcbed7, /* GL_EXT_semaphore_fd */
    /*  436 */ 0xd80cf52931619f45, /* GL_EXT_semaphore_win32 */
    /*  437 */ 0xde7c2e65ed21d1e7, /* GL_EXT_separate_depth_stencil */
    /*  438 */ 0xb207ff65f8bf495d, /* GL_EXT_separate_shader_objects */
    /*  439 */ 0xeb07329b2f67d2ec, /* GL_EXT_separate_specular_color */
    /*  440 */ 0x49d751ecfad21a12, /* GL_EXT_shader_16bit_storage */
    /*  441 */ 0x71c6281257d16bdf, /* GL_EXT_shader_atomic_float */
    /*  442 */ 0x6e599868ea3a939f, /* GL_EXT_shader_explicit_arithmetic_types */
    /*  443 */ 0x86da0f80c54cef33, /* GL_EXT_shader_framebuffer_fetch */
    /*  444 */ 0xcd3c990c9f8c0a64, /* GL_EXT_shader_framebuffer_fetch_non_coherent */
    /*  445 */ 0x17434ddfdf3a5893, /* GL_EXT_shader_group_vote */
    /*  446 */ 0xeab14f8fb076d3f3, /* GL_EXT_shader_image_int64 */
    /*  447 */ 0xc1de48ba5bbf7b01, /* GL_EXT_shader_image_load_formatted */
    /*  448 */ 0x6ab82341e3e65156, /* GL_EXT_shader_image_load_store */
    /*  449 */ 0xe19d3a68c60c0ef4, /* GL_EXT_shader_implicit_conversions */
    /*  450 */ 0x033287cccf9a6962, /* GL_EXT_shader_integer_mix */
    /*  451 */ 0xd055bdf912abe3b0, /* GL_EXT_shader_io_blocks */
    /*  452 */ 0x07975202b868bf83, /* GL_EXT_shader_non_constant_global_initializers */
    /*  453 */ 0x49f7e4529e189129, /* GL_EXT_shader_pixel_local_storage */
    /*  454 */ 0x28720bf0be8ab661, /* GL_EXT_shader_pixel_local_storage2 */
    /*  455 */ 0x28c00ec379a98b9d, /* GL_EXT_shader_realtime_clock */
    /*  456 */ 0x3ef958340d410019, /* GL_EXT_shader_samples_identical */
    /*  457 */ 0xa3a7633df81fa8b1, /* GL_EXT_shader_subgroup_extended_types */
    /*  458 */ 0x0fbf30e41210d727, /* GL_EXT_shader_texture_lod */
    /*  459 */ 0xe504594d7646deb5, /* GL_EXT_shadow_funcs */
    /*  460 */ 0x7c7d332de021da36, /* GL_EXT_shadow_samplers */
    /*  461 */ 0x4851b197319900c7, /* GL_EXT_shared_memory_block */
    /*  462 */ 0xa39da1f69d0cad57, /* GL_EXT_shared_texture_palette */
    /*  463 */ 0x86ac1bf74755a73b, /* GL_EXT_sparse_texture */
    /*  464 */ 0x81ed537411dae865, /* GL_EXT_sparse_texture2 */
    /*  465 */ 0xe20fb1c3faf6f7d8, /* GL_EXT_stencil_clear_tag */
    /*  466 */ 0x629c334d67e5c718, /* GL_EXT_stencil_two_side */
    /*  467 */ 0x961b80206055e672, /* GL_EXT_stencil_wrap */
    /*  468 */ 0x8a56add0af10cbb6, /* GL_EXT_subgroup_uniform_control_flow */
    /*  469 */ 0xf85c8111e381b059, /* GL_EXT_subgroupuniform_qualifier */
    /*  470 */ 0xe101571ccdddbe44, /* GL_EXT_subtexture */
    /*  471 */ 0x9e9a449841a4392b, /* GL_EXT_tessellation_point_size */
    /*  472 */ 0xa694e21c70c92ac7, /* GL_EXT_tessellation_shader */
    /*  473 */ 0x7893ebdfb50f10a6, /* GL_EXT_texture */
    /*  474 */ 0x3c1975837c97841b, /* GL_EXT_texture3D */
    /*  475 */ 0x2e4c3fc71fe20a24, /* GL_EXT_texture_array */
    /*  476 */ 0xf02848fc36653917, /* GL_EXT_texture_border_clamp */
    /*  477 */ 0x990b742e339cfdab, /* GL_EXT_texture_buffer */
    /*  478 */ 0xe30b1bf963964b94, /* GL_EXT_texture_buffer_object */
    /*  479 */ 0x7c8af8bc6e29a35b, /* GL_EXT_texture_compression_astc_decode_mode */
    /*  480 */ 0x8c12f4a29dd9872d, /* GL_EXT_texture_compression_bptc */
    /*  481 */ 0x42f4b0934de6c2dc, /* GL_EXT_texture_compression_dxt1 */
    /*  482 */ 0x789187ec36c3334e, /* GL_EXT_texture_compression_latc */
    /*  483 */ 0x6d7076425ffdf707, /* GL_EXT_texture_compression_rgtc */
    /*  484 */ 0x675e8f3271d1d5ca, /* GL_EXT_texture_compression_s3tc */
    /*  485 */ 0x747ed54119078205, /* GL_EXT_texture_compression_s3tc_srgb */
    /*  486 */ 0x511d1308a8dfc13f, /* GL_EXT_texture_cube_map */
    /*  487 */ 0x143e4c21a6ff53cc, /* GL_EXT_texture_cube_map_array */
    /*  488 */ 0xd7d84a9c353851fd, /* GL_EXT_texture_env_add */
    /*  489 */ 0x9d216b7a877bbcfb, /* GL_EXT_texture_env_combine */
    /*  490 */ 0x4bacf852b1cc1a43, /* GL_EXT_texture_env_dot3 */
    /*  491 */ 0xeafde92a9cccc4ed, /* GL_EXT_texture_filter_anisotropic */
    /*  492 */ 0x7738fa89f1d13a13, /* GL_EXT_texture_filter_minmax */
    /*  493 */ 0x39751dec512ae77c, /* GL_EXT_texture_format_BGRA8888 */
    /*  494 */ 0xeb53a2bedf43571d, /* GL_EXT_texture_format_sRGB_override */
    /*  495 */ 0xaf09c3ff42c89eb5, /* GL_EXT_texture_integer */
    /*  496 */ 0x41cf52695838c61c, /* GL_EXT_texture_lod_bias */
    /*  497 */ 0x17fb25156306ea61, /* GL_EXT_texture_mirror_clamp */
    /*  498 */ 0x9a5a807af7e26b3f, /* GL_EXT_texture_mirror_clamp_to_edge */
    /*  499 */ 0x94b22c00bec3e518, /* GL_EXT_texture_norm16 */
    /*  500 */ 0x10827f593acd1ba7, /* GL_EXT_texture_object */
    /*  501 */ 0x971e595b62f38066, /* GL_EXT_texture_perturb_normal */
    /*  502 */ 0x1e6eaad4a57ca1b5, /* GL_EXT_texture_query_lod */
    /*  503 */ 0x95f0b0bc421f25d3, /* GL_EXT_texture_rg */
    /*  504 */ 0xd43be8ff9c7c7ada, /* GL_EXT_texture_sRGB */
    /*  505 */ 0xfe62dc3d8ab9f10b, /* GL_EXT_texture_sRGB_R8 */
    /*  506 */ 0xcb6984e200d35ff9, /* GL_EXT_texture_sRGB_RG8 */
    /*  507 */ 0x2b44a8b2473d6e5f, /* GL_EXT_texture_sRGB_decode */
    /*  508 */ 0x127856e58a250c1b, /* GL_EXT_texture_shadow_lod */
    /*  509 */ 0x30a7dd27a9ac5760, /* GL_EXT_texture_shared_exponent */
    /*  510 */ 0xa2f8f4e45d997df3, /* GL_EXT_texture_snorm */
    /*  511 */ 0x154c4c8b80533dc0, /* GL_EXT_texture_storage */
    /*  512 */ 0x8768e67dadd2a7fd, /* GL_EXT_texture_storage_compression */
    /*  513 */ 0x183ae240682f4ad7, /* GL_EXT_texture_swizzle */
    /*  514 */ 0x4a802d8de71af8e9, /* GL_EXT_texture_type_2_10_10_10_REV */
    /*  515 */ 0x19afe800141638dc, /* GL_EXT_texture_view */
    /*  516 */ 0x4ab0caa70a996495, /* GL_EXT_timer_query */
    /*  517 */ 0x471536c0a27f5c81, /* GL_EXT_transform_feedback */
    /*  518 */ 0x1675c7c13b385f42, /* GL_EXT_unpack_subimage */
    /*  519 */ 0x2347ebc551d02975, /* GL_EXT_vertex_array */
    /*  520 */ 0xc5160cefc841200d, /* GL_EXT_vertex_array_bgra */
    /*  521 */ 0xfe8f41c3d0888d86, /* GL_EXT_vertex_attrib_64bit */
    /*  522 */ 0x10ce9358a245f782, /* GL_EXT_vertex_shader */
    /*  523 */ 0x80e4c2ee68e62a5f, /* GL_EXT_vertex_weighting */
    /*  524 */ 0x71431741b9e82753, /* GL_EXT_vulkan_glsl_relaxed */
    /*  525 */ 0xb7046ff80ce07f1a, /* GL_EXT_win32_keyed_mutex */
    /*  526 */ 0x225b607d5cdf07d5, /* GL_EXT_window_rectangles */
    /*  527 */ 0x80306c2b70f53ada, /* GL_EXT_x11_sync_object */
    /*  528 */ 0xaf38ae454737b45a, /* GL_FJ_shader_binary_GCCSO */
    /*  529 */ 0x776d5f9ce5dc30ad, /* GL_GREMEDY_frame_terminator */
    /*  530 */ 0x2b64919ae0d632d6, /* GL_GREMEDY_string_marker */
    /*  531 */ 0x4ba0a53809cd8e1c, /* GL_HP_convolution_border_modes */
    /*  532 */ 0x175101ef679b74d1, /* GL_HP_image_transform */
    /*  533 */ 0x21db09dff47e8865, /* GL_HP_occlusion_test */
    /*  534 */ 0xbccb311192bef9fc, /* GL_HP_texture_lighting */
    /*  535 */ 0x01088281231ac4b3, /* GL_HUAWEI_subpass_shading */
    /*  536 */ 0x052c78ec9092b2bc, /* GL_IBM_cull_vertex */
    /*  537 */ 0xbed7db565a3dcdb1, /* GL_IBM_multimode_draw_arrays */
    /*  538 */ 0xb0a341b3ba34bde7, /* GL_IBM_rasterpos_clip */
    /*  539 */ 0xe5d4e67e743793af, /* GL_IBM_static_data */
    /*  540 */ 0x42e7c1e06f5230cb, /* GL_IBM_texture_mirrored_repeat */
    /*  541 */ 0x3801878506a0d3e5, /* GL_IBM_vertex_array_lists */
    /*  542 */ 0xe966fe12585d0ee3, /* GL_IMG_bindless_texture */
    /*  543 */ 0xee05cb0623b18588, /* GL_IMG_framebuffer_downsample */
    /*  544 */ 0x6cd4bff21f14cba9, /* GL_IMG_multisampled_render_to_texture */
    /*  545 */ 0x10eae89c21411416, /* GL_IMG_program_binary */
    /*  546 */ 0xe1d246c5f2217570, /* GL_IMG_read_format */
    /*  547 */ 0x631524850de59ddd, /* GL_IMG_shader_binary */
    /*  548 */ 0x26bbd5573ad61282, /* GL_IMG_texture_compression_pvrtc */
    /*  549 */ 0x46869091dbce71a6, /* GL_IMG_texture_compression_pvrtc2 */
    /*  550 */ 0xd44d6d9763e6fd68, /* GL_IMG_texture_filter_cubic */
    /*  551 */ 0xf8c1cfe37858c556, /* GL_INGR_blend_func_separate */
    /*  552 */ 0x9d3ca51fe0f2a837, /* GL_INGR_color_clamp */
    /*  553 */ 0x231c00090b681c01, /* GL_INGR_interlace_read */
    /*  554 */ 0xc0f54564fa652eba, /* GL_INTEL_blackhole_render */
    /*  555 */ 0x8cfa061f6a006e62, /* GL_INTEL_conservative_rasterization */
    /*  556 */ 0x693a15be925d42bb, /* GL_INTEL_fragment_shader_ordering */
    /*  557 */ 0x14386616e0282da8, /* GL_INTEL_framebuffer_CMAA */
    /*  558 */ 0xfe0a30102b2b7f11, /* GL_INTEL_map_texture */
    /*  559 */ 0x6d9138f92a97a9b2, /* GL_INTEL_parallel_arrays */
    /*  560 */ 0x331d1b2f1d575bd8, /* GL_INTEL_performance_query */
    /*  561 */ 0x898f16e7a19612fe, /* GL_KHR_blend_equation_advanced */
    /*  562 */ 0xa66b25957f58c923, /* GL_KHR_blend_equation_advanced_coherent */
    /*  563 */ 0x0956a658c75ab600, /* GL_KHR_context_flush_control */
    /*  564 */ 0x5e0c5b9607ac8784, /* GL_KHR_debug */
    /*  565 */ 0x08ce79df715e69dc, /* GL_KHR_memory_scope_semantics */
    /*  566 */ 0x12316ddfcc85238e, /* GL_KHR_no_error */
    /*  567 */ 0x3406b66e92343753, /* GL_KHR_parallel_shader_compile */
    /*  568 */ 0xfa6bb57654b50c92, /* GL_KHR_robust_buffer_access_behavior */
    /*  569 */ 0x474beac5f6910636, /* GL_KHR_robustness */
    /*  570 */ 0x65263f2081d063e7, /* GL_KHR_shader_subgroup */
    /*  571 */ 0x24c80aab81e859b3, /* GL_KHR_texture_compression_astc_hdr */
    /*  572 */ 0x16f59295398b9d0a, /* GL_KHR_texture_compression_astc_ldr */
    /*  573 */ 0xa4a29c6f56f2023e, /* GL_KHR_texture_compression_astc_sliced_3d */
    /*  574 */ 0xcbbacf3d7c96adcc, /* GL_KHR_vulkan_glsl */
    /*  575 */ 0x70bbb44bbc67a914, /* GL_MESAX_texture_stack */
    /*  576 */ 0x4b833beb1f90e758, /* GL_MESA_bgra */
    /*  577 */ 0xf9cfb61b2f897c12, /* GL_MESA_framebuffer_flip_x */
    /*  578 */ 0xdf842b85f40b8f2d, /* GL_MESA_framebuffer_flip_y */
    /*  579 */ 0xc735e4d56089513e, /* GL_MESA_framebuffer_swap_xy */
    /*  580 */ 0xac7eeedfea22e53d, /* GL_MESA_pack_invert */
    /*  581 */ 0xe164dc7b3064a548, /* GL_MESA_program_binary_formats */
    /*  582 */ 0x39376b06206502d6, /* GL_MESA_resize_buffers */
    /*  583 */ 0xa14ebc048c19e849, /* GL_MESA_sampler_objects */
    /*  584 */ 0x58e3c24874e50b2f, /* GL_MESA_shader_integer_functions */
    /*  585 */ 0x8ee739e5f4f16337, /* GL_MESA_tile_raster_order */
    /*  586 */ 0x00063de42ab739f6, /* GL_MESA_window_pos */
    /*  587 */ 0x05840d0e5ebfdb5d, /* GL_MESA_ycbcr_texture */
    /*  588 */ 0x210f54fb5023bd27, /* GL_NVX_blend_equation_advanced_multi_draw_buffers */
    /*  589 */ 0xdb3d40c973a8401d, /* GL_NVX_conditional_render */
    /*  590 */ 0xdba64e974cfda98b, /* GL_NVX_gpu_memory_info */
    /*  591 */ 0xfadb1fc8cec16ab6, /* GL_NVX_gpu_multicast2 */
    /*  592 */ 0xcd2e0dc9329fd277, /* GL_NVX_linked_gpu_multicast */
    /*  593 */ 0xd9dac6ae420f2bc1, /* GL_NVX_multiview_per_view_attributes */
    /*  594 */ 0xd0ab24d9b21b5714, /* GL_NVX_progress_fence */
    /*  595 */ 0xf60ebf70e765dade, /* GL_NV_alpha_to_coverage_dither_control */
    /*  596 */ 0x0125c6b149dc763d, /* GL_NV_bindless_multi_draw_indirect */
    /*  597 */ 0xbf25dd3d5b684860, /* GL_NV_bindless_multi_draw_indirect_count */
    /*  598 */ 0xfe0701cf0661b283, /* GL_NV_bindless_texture */
    /*  599 */ 0xdfb2fe6dc8d05e7b, /* GL_NV_blend_equation_advanced */
    /*  600 */ 0x93143e8adaf57589, /* GL_NV_blend_equation_advanced_coherent */
    /*  601 */ 0xea9c32d0ef37492e, /* GL_NV_blend_minmax_factor */
    /*  602 */ 0xcfb887fc69ba21e3, /* GL_NV_blend_square */
    /*  603 */ 0xa4c52c3b41a4fcad, /* GL_NV_clip_space_w_scaling */
    /*  604 */ 0x86fd725bf0f0d470, /* GL_NV_command_list */
    /*  605 */ 0x909a590b136b2993, /* GL_NV_compute_program5 */
    /*  606 */ 0x6e8fcfc637ce5f42, /* GL_NV_compute_shader_derivatives */
    /*  607 */ 0x30dc18387f98fe17, /* GL_NV_conditional_render */
    /*  608 */ 0xe3492208f94da35f, /* GL_NV_conservative_raster */
    /*  609 */ 0xd3d407b80b1805ae, /* GL_NV_conservative_raster_dilate */
    /*  610 */ 0x10c99e7e01aae44f, /* GL_NV_conservative_raster_pre_snap */
    /*  611 */ 0xf4ef9c1caf911a2c, /* GL_NV_conservative_raster_pre_snap_triangles */
    /*  612 */ 0x9a8099482ede4695, /* GL_NV_conservative_raster_underestimation */
    /*  613 */ 0x82f2d3fffe63ccba, /* GL_NV_cooperative_matrix */
    /*  614 */ 0x1250d4e984fabb8a, /* GL_NV_copy_buffer */
    /*  615 */ 0xddf225eb383a722a, /* GL_NV_copy_depth_to_color */
    /*  616 */ 0x542626fd538a9ee0, /* GL_NV_copy_image */
    /*  617 */ 0x1f3cf0884049a65c, /* GL_NV_coverage_sample */
    /*  618 */ 0xa115ed21a9ad2718, /* GL_NV_deep_texture3D */
    /*  619 */ 0x11d0e662e981dd10, /* GL_NV_depth_buffer_float */
    /*  620 */ 0x25caf626c8dc4876, /* GL_NV_depth_clamp */
    /*  621 */ 0x23fb225c6189b719, /* GL_NV_depth_nonlinear */
    /*  622 */ 0xe30effdb6e04aad2, /* GL_NV_draw_buffers */
    /*  623 */ 0x5cef483902a0a7d1, /* GL_NV_draw_instanced */
    /*  624 */ 0x0ac29b41db04db89, /* GL_NV_draw_texture */
    /*  625 */ 0x0c3ad3a0bb6ea832, /* GL_NV_draw_vulkan_image */
    /*  626 */ 0x86aaaa35812cc6e4, /* GL_NV_evaluators */
    /*  627 */ 0x0d0ad1150bf11b93, /* GL_NV_explicit_attrib_location */
    /*  628 */ 0xb1fb52088193eb75, /* GL_NV_explicit_multisample */
    /*  629 */ 0xf69d212a36261f45, /* GL_NV_fbo_color_attachments */
    /*  630 */ 0x9f9d6242407aaa0d, /* GL_NV_fence */
    /*  631 */ 0x574a28d0edc9eb1f, /* GL_NV_fill_rectangle */
    /*  632 */ 0x60178d619bd63acd, /* GL_NV_float_buffer */
    /*  633 */ 0x3a25bd3423152eb5, /* GL_NV_fog_distance */
    /*  634 */ 0xbd0368ffaa60b1e1, /* GL_NV_fragment_coverage_to_color */
    /*  635 */ 0xd63f48ff142e3931, /* GL_NV_fragment_program */
    /*  636 */ 0x9607f3b2549a29c3, /* GL_NV_fragment_program2 */
    /*  637 */ 0x3fc3c14225294207, /* GL_NV_fragment_program4 */
    /*  638 */ 0x7e38a803870eb005, /* GL_NV_fragment_program_option */
    /*  639 */ 0x63f3491b75562351, /* GL_NV_fragment_shader_barycentric */
    /*  640 */ 0xf907528dfaacf5d1, /* GL_NV_fragment_shader_interlock */
    /*  641 */ 0xc7b0688e759eacca, /* GL_NV_framebuffer_blit */
    /*  642 */ 0x7690d69739f37d49, /* GL_NV_framebuffer_mixed_samples */
    /*  643 */ 0xd333a1d53faf1645, /* GL_NV_framebuffer_multisample */
    /*  644 */ 0xb7e1d7ede28f1eb6, /* GL_NV_framebuffer_multisample_coverage */
    /*  645 */ 0x42fb5b03beace82d, /* GL_NV_generate_mipmap_sRGB */
    /*  646 */ 0xd649529b8b1dc13f, /* GL_NV_geometry_program4 */
    /*  647 */ 0x85be2495755b8912, /* GL_NV_geometry_shader4 */
    /*  648 */ 0x2650d5fc619ace25, /* GL_NV_geometry_shader_passthrough */
    /*  649 */ 0x0f309973ce34369d, /* GL_NV_gpu_multicast */
    /*  650 */ 0xb97d5c93298f0cd0, /* GL_NV_gpu_program4 */
    /*  651 */ 0xfee0597c2b98bd5a, /* GL_NV_gpu_program5 */
    /*  652 */ 0x76ac1ada5bbc4ea2, /* GL_NV_gpu_program5_mem_extended */
    /*  653 */ 0x9ca801fbedd18a78, /* GL_NV_gpu_shader5 */
    /*  654 */ 0x185a8632c27d17b4, /* GL_NV_half_float */
    /*  655 */ 0xe34c3aba26b785e0, /* GL_NV_image_formats */
    /*  656 */ 0xc2e8b0284eeb3343, /* GL_NV_instanced_arrays */
    /*  657 */ 0xa5628152267b8db5, /* GL_NV_internalformat_sample_query */
    /*  658 */ 0x4514ca3e8473d61d, /* GL_NV_light_max_exponent */
    /*  659 */ 0xe91f9b1323143013, /* GL_NV_memory_attachment */
    /*  660 */ 0x529b823de64f6ca0, /* GL_NV_memory_object_sparse */
    /*  661 */ 0x2793373463edd95b, /* GL_NV_mesh_shader */
    /*  662 */ 0x8d5187c2fb3e3879, /* GL_NV_multisample_coverage */
    /*  663 */ 0x92f77a4cfb0d4df3, /* GL_NV_multisample_filter_hint */
    /*  664 */ 0x5b891d5155380820, /* GL_NV_non_square_matrices */
    /*  665 */ 0xdff6cf35e1df2d8d, /* GL_NV_occlusion_query */
    /*  666 */ 0xda29f4099a052321, /* GL_NV_pack_subimage */
    /*  667 */ 0x1a5932681cefa5eb, /* GL_NV_packed_depth_stencil */
    /*  668 */ 0xbffccb846b13070a, /* GL_NV_parameter_buffer_object */
    /*  669 */ 0xb153f109324c418b, /* GL_NV_parameter_buffer_object2 */
    /*  670 */ 0x77bc468b065f8fdb, /* GL_NV_path_rendering */
    /*  671 */ 0x2f70022ecb786aed, /* GL_NV_path_rendering_shared_edge */
    /*  672 */ 0x0b44f2e633646ab5, /* GL_NV_pixel_buffer_object */
    /*  673 */ 0x43d8732157b4106d, /* GL_NV_pixel_data_range */
    /*  674 */ 0x839efae2d0736a4c, /* GL_NV_point_sprite */
    /*  675 */ 0x3330eb9a4ceb6c0c, /* GL_NV_polygon_mode */
    /*  676 */ 0x6512c3d1922a98db, /* GL_NV_present_video */
    /*  677 */ 0x8c542b195b5b3c94, /* GL_NV_primitive_restart */
    /*  678 */ 0x0cacb49d8f1c105a, /* GL_NV_primitive_shading_rate */
    /*  679 */ 0x9b1b0441d8d19911, /* GL_NV_query_resource */
    /*  680 */ 0x15f0661a8638b338, /* GL_NV_query_resource_tag */
    /*  681 */ 0xdd74002f450fb368, /* GL_NV_ray_tracing */
    /*  682 */ 0x182d9aed7af08983, /* GL_NV_ray_tracing_motion_blur */
    /*  683 */ 0xb51b7c433236bd06, /* GL_NV_read_buffer */
    /*  684 */ 0xc91023f37354df43, /* GL_NV_read_buffer_front */
    /*  685 */ 0x3dfff3ed25362196, /* GL_NV_read_depth */
    /*  686 */ 0x55261906f55bb17a, /* GL_NV_read_depth_stencil */
    /*  687 */ 0x7bab8fd7e4a04ee8, /* GL_NV_read_stencil */
    /*  688 */ 0xd791c5687139b905, /* GL_NV_register_combiners */
    /*  689 */ 0x8814ab530e95a798, /* GL_NV_register_combiners2 */
    /*  690 */ 0xb46bd57f88e91d64, /* GL_NV_representative_fragment_test */
    /*  691 */ 0xc4eada8b9cbe17c0, /* GL_NV_robustness_video_memory_purge */
    /*  692 */ 0x2c2775936dc2a882, /* GL_NV_sRGB_formats */
    /*  693 */ 0xc50ae467eedfefde, /* GL_NV_sample_locations */
    /*  694 */ 0x446a05466a6d6429, /* GL_NV_sample_mask_override_coverage */
    /*  695 */ 0x4247a4acbfcdb098, /* GL_NV_scissor_exclusive */
    /*  696 */ 0x0383e334dd39d9a0, /* GL_NV_shader_atomic_counters */
    /*  697 */ 0x02399be47930fbf4, /* GL_NV_shader_atomic_float */
    /*  698 */ 0x8c8c8962eadf1230, /* GL_NV_shader_atomic_float64 */
    /*  699 */ 0x4c3311286ab16152, /* GL_NV_shader_atomic_fp16_vector */
    /*  700 */ 0xb14dbc3c64a1326f, /* GL_NV_shader_atomic_int64 */
    /*  701 */ 0x3ae6fc5c42bab2c2, /* GL_NV_shader_buffer_load */
    /*  702 */ 0x1c05604500113691, /* GL_NV_shader_buffer_store */
    /*  703 */ 0xbb5c10f38325fdf8, /* GL_NV_shader_noperspective_interpolation */
    /*  704 */ 0x6d97890637a77774, /* GL_NV_shader_sm_builtins */
    /*  705 */ 0xaf5c0eb5c483eb28, /* GL_NV_shader_storage_buffer_object */
    /*  706 */ 0x826afa0d2f696f22, /* GL_NV_shader_subgroup_partitioned */
    /*  707 */ 0x7b3f8fad48cfd967, /* GL_NV_shader_texture_footprint */
    /*  708 */ 0xfd2aa76218c9354e, /* GL_NV_shader_thread_group */
    /*  709 */ 0x74a053165bf8ada4, /* GL_NV_shader_thread_shuffle */
    /*  710 */ 0xf9355d5174ef4c70, /* GL_NV_shading_rate_image */
    /*  711 */ 0x28944cfc0cca07ec, /* GL_NV_shadow_samplers_array */
    /*  712 */ 0xfdbd6232791ce36f, /* GL_NV_shadow_samplers_cube */
    /*  713 */ 0x56dc6bb2a7d8736f, /* GL_NV_stereo_view_rendering */
    /*  714 */ 0x2410081ec485d619, /* GL_NV_tessellation_program5 */
    /*  715 */ 0x6a6887942da6a4c4, /* GL_NV_texgen_emboss */
    /*  716 */ 0x35865e06d7292c9b, /* GL_NV_texgen_reflection */
    /*  717 */ 0x282f885e0bfd25de, /* GL_NV_texture_barrier */
    /*  718 */ 0x373989acbf486191, /* GL_NV_texture_border_clamp */
    /*  719 */ 0x4d5276bd5a1f04ce, /* GL_NV_texture_compression_s3tc_update */
    /*  720 */ 0x25b70b1f5bbed713, /* GL_NV_texture_compression_vtc */
    /*  721 */ 0x84b70fe53fcdcde1, /* GL_NV_texture_env_combine4 */
    /*  722 */ 0x07e650e01fee3678, /* GL_NV_texture_expand_normal */
    /*  723 */ 0x4679eee96470073f, /* GL_NV_texture_multisample */
    /*  724 */ 0xcba499c04274ad25, /* GL_NV_texture_npot_2D_mipmap */
    /*  725 */ 0xccbc8154a70c3605, /* GL_NV_texture_rectangle */
    /*  726 */ 0x5da6e59a7e51bc40, /* GL_NV_texture_rectangle_compressed */
    /*  727 */ 0x8a67a1269b408254, /* GL_NV_texture_shader */
    /*  728 */ 0x816b354fd0cd9228, /* GL_NV_texture_shader2 */
    /*  729 */ 0x5526327fa18acdde, /* GL_NV_texture_shader3 */
    /*  730 */ 0x39f7dcc9a62c5153, /* GL_NV_timeline_semaphore */
    /*  731 */ 0xf09b77c741443fcb, /* GL_NV_transform_feedback */
    /*  732 */ 0x32519ec17990e826, /* GL_NV_transform_feedback2 */
    /*  733 */ 0x5600eb6f04e474ee, /* GL_NV_uniform_buffer_std430_layout */
    /*  734 */ 0x5a3050e67df48f2c, /* GL_NV_uniform_buffer_unified_memory */
    /*  735 */ 0xc270d7ffe7e44b23, /* GL_NV_vdpau_interop */
    /*  736 */ 0x613710111a2944f7, /* GL_NV_vdpau_interop2 */
    /*  737 */ 0x2670ae7bcc80188e, /* GL_NV_vertex_array_range */
    /*  738 */ 0x79ae834a103024c5, /* GL_NV_vertex_array_range2 */
    /*  739 */ 0xe688c60fe2e62039, /* GL_NV_vertex_attrib_integer_64bit */
    /*  740 */ 0x7e2fb60c66658e57, /* GL_NV_vertex_buffer_unified_memory */
    /*  741 */ 0x527413b984649803, /* GL_NV_vertex_program */
    /*  742 */ 0x7d2fc2b85898af18, /* GL_NV_vertex_program1_1 */
    /*  743 */ 0x2d5a70a0a1d00d78, /* GL_NV_vertex_program2 */
    /*  744 */ 0x747ed48148981054, /* GL_NV_vertex_program2_option */
    /*  745 */ 0xc13798df29c369e2, /* GL_NV_vertex_program3 */
    /*  746 */ 0xa796194638bbdc74, /* GL_NV_vertex_program4 */
    /*  747 */ 0x89ae752e4cfcfae8, /* GL_NV_video_capture */
    /*  748 */ 0x1b9db3e10e73323b, /* GL_NV_viewport_array */
    /*  749 */ 0x4e9c3fc0856350f9, /* GL_NV_viewport_array2 */
    /*  750 */ 0xdf18b1c27e48f432, /* GL_NV_viewport_swizzle */
    /*  751 */ 0xc05411382c7e9b6f, /* GL_OES_EGL_image */
    /*  752 */ 0xb3f47895b1c4d5f8, /* GL_OES_EGL_image_external */
    /*  753 */ 0xbbae531ab8d7e16f, /* GL_OES_EGL_image_external_essl3 */
    /*  754 */ 0x55f4d891b16ad96c, /* GL_OES_byte_coordinates */
    /*  755 */ 0x866125fa75aab774, /* GL_OES_compressed_ETC1_RGB8_sub_texture */
    /*  756 */ 0x5b4df7888b81a92b, /* GL_OES_compressed_ETC1_RGB8_texture */
    /*  757 */ 0xd1ae5222afe37da5, /* GL_OES_compressed_paletted_texture */
    /*  758 */ 0xc5e1ddc1ea43276e, /* GL_OES_copy_image */
    /*  759 */ 0xa3f0bbbc7660d96c, /* GL_OES_depth24 */
    /*  760 */ 0xb8b2dd3478f1ec83, /* GL_OES_depth32 */
    /*  761 */ 0x67516f69dbc843f6, /* GL_OES_depth_texture */
    /*  762 */ 0x012b99c59ced284f, /* GL_OES_draw_buffers_indexed */
    /*  763 */ 0x4638dd889d2b7eab, /* GL_OES_draw_elements_base_vertex */
    /*  764 */ 0x29e68bee4a9705f1, /* GL_OES_element_index_uint */
    /*  765 */ 0xe0b0d82d6dc31dae, /* GL_OES_fbo_render_mipmap */
    /*  766 */ 0x9f59932407436633, /* GL_OES_fixed_point */
    /*  767 */ 0x116a77aa55534c76, /* GL_OES_fragment_precision_high */
    /*  768 */ 0x5e6f26587d551ffc, /* GL_OES_geometry_point_size */
    /*  769 */ 0xaa384a84e450d595, /* GL_OES_geometry_shader */
    /*  770 */ 0x503ad238c5e97931, /* GL_OES_get_program_binary */
    /*  771 */ 0x77f35c2a7a2bd390, /* GL_OES_gpu_shader5 */
    /*  772 */ 0x22e521fe25c89a3b, /* GL_OES_mapbuffer */
    /*  773 */ 0xb124b23bca92b355, /* GL_OES_packed_depth_stencil */
    /*  774 */ 0x303e15e4f8fb9ee6, /* GL_OES_primitive_bounding_box */
    /*  775 */ 0xc8d3d0277204ac3d, /* GL_OES_query_matrix */
    /*  776 */ 0xca46680e5cfc3e18, /* GL_OES_read_format */
    /*  777 */ 0xd6c9bec1dd5d5b89, /* GL_OES_required_internalformat */
    /*  778 */ 0xccb18f4e376e6c74, /* GL_OES_rgb8_rgba8 */
    /*  779 */ 0xcb740362814f4ca0, /* GL_OES_sample_shading */
    /*  780 */ 0x8f4eb2b127c21f67, /* GL_OES_sample_variables */
    /*  781 */ 0xa023718702859970, /* GL_OES_shader_image_atomic */
    /*  782 */ 0x8cc1262bb8c2d393, /* GL_OES_shader_io_blocks */
    /*  783 */ 0xc772b78382e1a793, /* GL_OES_shader_multisample_interpolation */
    /*  784 */ 0xbcbfeb8171756944, /* GL_OES_single_precision */
    /*  785 */ 0x4e9710576f516b4e, /* GL_OES_standard_derivatives */
    /*  786 */ 0x79f1937e076eb6e0, /* GL_OES_stencil1 */
    /*  787 */ 0x7361db1a08c53c55, /* GL_OES_stencil4 */
    /*  788 */ 0x6df979b4adc4989b, /* GL_OES_surfaceless_context */
    /*  789 */ 0xdc7532bffc48cb01, /* GL_OES_tessellation_point_size */
    /*  790 */ 0x8bbb4c0c94dc1415, /* GL_OES_tessellation_shader */
    /*  791 */ 0xccac53b0ed36c73c, /* GL_OES_texture_3D */
    /*  792 */ 0xedc39fcb928c7be5, /* GL_OES_texture_border_clamp */
    /*  793 */ 0xc7d6a2d8a596bf50, /* GL_OES_texture_buffer */
    /*  794 */ 0x552cece98cadbaa6, /* GL_OES_texture_compression_astc */
    /*  795 */ 0xfad8c3de7cf9ffc4, /* GL_OES_texture_cube_map_array */
    /*  796 */ 0x32ed502b39dd1594, /* GL_OES_texture_float */
    /*  797 */ 0x5afe2be3731190e1, /* GL_OES_texture_float_linear */
    /*  798 */ 0xa9fdcf0e5b6803dd, /* GL_OES_texture_half_float */
    /*  799 */ 0x0011e43010189be7, /* GL_OES_texture_half_float_linear */
    /*  800 */ 0xe706ff7638659b7e, /* GL_OES_texture_npot */
    /*  801 */ 0xdfa8a0ccd9d60d53, /* GL_OES_texture_stencil8 */
    /*  802 */ 0xbc655ee4febdcfca, /* GL_OES_texture_storage_multisample_2d_array */
    /*  803 */ 0x8fc2a146f6290d39, /* GL_OES_texture_view */
    /*  804 */ 0x7cd6041965da7d3c, /* GL_OES_vertex_array_object */
    /*  805 */ 0x8d77aa22bdd641e8, /* GL_OES_vertex_half_float */
    /*  806 */ 0x244e9e511573b959, /* GL_OES_vertex_type_10_10_10_2 */
    /*  807 */ 0x2e0ac92809baabbd, /* GL_OES_viewport_array */
    /*  808 */ 0xe4756190e24cfae1, /* GL_OML_interlace */
    /*  809 */ 0xf00e1502b0d1f5d7, /* GL_OML_resample */
    /*  810 */ 0xee17f2c40613fa28, /* GL_OML_subsample */
    /*  811 */ 0x462789e64be7acd7, /* GL_OVR_multiview */
    /*  812 */ 0x4d3b083404c10e3f, /* GL_OVR_multiview2 */
    /*  813 */ 0xdd9450d3b97e069b, /* GL_OVR_multiview_multisampled_render_to_texture */
    /*  814 */ 0xb1df54452698a7be, /* GL_PGI_misc_hints */
    /*  815 */ 0x830c412288059800, /* GL_PGI_vertex_hints */
    /*  816 */ 0x03b99dd37fd50188, /* GL_QCOM_YUV_texture_gather */
    /*  817 */ 0x3aa5ff0497f38e96, /* GL_QCOM_alpha_test */
    /*  818 */ 0x8b6f2c405eed8fc9, /* GL_QCOM_binning_control */
    /*  819 */ 0xd69ddd5074f27947, /* GL_QCOM_driver_control */
    /*  820 */ 0x2cfff6c37fa549bc, /* GL_QCOM_extended_get */
    /*  821 */ 0xa36cbb8c3a77c3a1, /* GL_QCOM_extended_get2 */
    /*  822 */ 0x1359ba3cc79be309, /* GL_QCOM_frame_extrapolation */
    /*  823 */ 0xa96b1c721f28a1c2, /* GL_QCOM_framebuffer_foveated */
    /*  824 */ 0x822886625bd76c4a, /* GL_QCOM_motion_estimation */
    /*  825 */ 0x62c4f9e3d0cf2728, /* GL_QCOM_perfmon_global_mode */
    /*  826 */ 0x6667e13047800b18, /* GL_QCOM_render_sRGB_R8_RG8 */
    /*  827 */ 0x005a335cb406a184, /* GL_QCOM_render_shared_exponent */
    /*  828 */ 0x0668ea2d27f4b9c7, /* GL_QCOM_shader_framebuffer_fetch_noncoherent */
    /*  829 */ 0x2f8fba53941074de, /* GL_QCOM_shader_framebuffer_fetch_rate */
    /*  830 */ 0x360f4bc982306308, /* GL_QCOM_shading_rate */
    /*  831 */ 0xa23647ccb657fc93, /* GL_QCOM_texture_foveated */
    /*  832 */ 0xac6fb0841696dc5f, /* GL_QCOM_texture_foveated2 */
    /*  833 */ 0xb7f306a63180d3df, /* GL_QCOM_texture_foveated_subsampled_layout */
    /*  834 */ 0x70d9c41ab20f93f9, /* GL_QCOM_texture_lod_bias */
    /*  835 */ 0x288ca2e6c7c5c86d, /* GL_QCOM_tiled_rendering */
    /*  836 */ 0x28eabd27e2f106a8, /* GL_QCOM_writeonly_rendering */
    /*  837 */ 0x14dac5dff736a3df, /* GL_REND_screen_coordinates */
    /*  838 */ 0x93469fe128fc0919, /* GL_S3_s3tc */
    /*  839 */ 0x8c7ee523e6ed026a, /* GL_SGIS_detail_texture */
    /*  840 */ 0xe54deb13059b8c4c, /* GL_SGIS_fog_function */
    /*  841 */ 0xb1b31f0af9b1e3c1, /* GL_SGIS_generate_mipmap */
    /*  842 */ 0x39568b3690efef18, /* GL_SGIS_multisample */
    /*  843 */ 0xf250c15acefa1ac9, /* GL_SGIS_pixel_texture */
    /*  844 */ 0x9b7bb525c279e853, /* GL_SGIS_point_line_texgen */
    /*  845 */ 0x4e3e0fa2dfafd5b4, /* GL_SGIS_point_parameters */
    /*  846 */ 0x4a4aa0671eb15c9f, /* GL_SGIS_sharpen_texture */
    /*  847 */ 0xe3880e70b14a01ef, /* GL_SGIS_texture4D */
    /*  848 */ 0x70c7cab7e228743c, /* GL_SGIS_texture_border_clamp */
    /*  849 */ 0x04eb37e0f3c4686a, /* GL_SGIS_texture_color_mask */
    /*  850 */ 0xb6400bcd7a346c99, /* GL_SGIS_texture_edge_clamp */
    /*  851 */ 0xd79b6287779eca3f, /* GL_SGIS_texture_filter4 */
    /*  852 */ 0xf25eb0173c775af1, /* GL_SGIS_texture_lod */
    /*  853 */ 0x4b818d48997acf33, /* GL_SGIS_texture_select */
    /*  854 */ 0x42053ed5c2789d8a, /* GL_SGIX_async */
    /*  855 */ 0x9baec4623ae00aa8, /* GL_SGIX_async_histogram */
    /*  856 */ 0xbed04383395711b9, /* GL_SGIX_async_pixel */
    /*  857 */ 0xd3cc8d1ef603a7f6, /* GL_SGIX_blend_alpha_minmax */
    /*  858 */ 0xe60980f13acb1fe8, /* GL_SGIX_calligraphic_fragment */
    /*  859 */ 0x5d613989907c2996, /* GL_SGIX_clipmap */
    /*  860 */ 0x8fa248e9981db96e, /* GL_SGIX_convolution_accuracy */
    /*  861 */ 0x47ef8f4254eec5a0, /* GL_SGIX_depth_pass_instrument */
    /*  862 */ 0x3489d57ce09fdb5e, /* GL_SGIX_depth_texture */
    /*  863 */ 0x37a8cdae9276920f, /* GL_SGIX_flush_raster */
    /*  864 */ 0x21b4c2f4db4fb980, /* GL_SGIX_fog_offset */
    /*  865 */ 0x5379c01e285814d7, /* GL_SGIX_fragment_lighting */
    /*  866 */ 0xbc4f1c742be26f3f, /* GL_SGIX_framezoom */
    /*  867 */ 0xd8ea1ff9ab303390, /* GL_SGIX_igloo_interface */
    /*  868 */ 0x828685155c316d20, /* GL_SGIX_instruments */
    /*  869 */ 0xaf75b3c8a321fd9b, /* GL_SGIX_interlace */
    /*  870 */ 0xac3c1477e6f161ef, /* GL_SGIX_ir_instrument1 */
    /*  871 */ 0xe6f72d5da01567e9, /* GL_SGIX_list_priority */
    /*  872 */ 0x945b05eefbbaf60c, /* GL_SGIX_pixel_texture */
    /*  873 */ 0x3c667c7037c70246, /* GL_SGIX_pixel_tiles */
    /*  874 */ 0x17349f9e9a6e5976, /* GL_SGIX_polynomial_ffd */
    /*  875 */ 0xe64b4cbd5d5fe178, /* GL_SGIX_reference_plane */
    /*  876 */ 0x007a4678f7628880, /* GL_SGIX_resample */
    /*  877 */ 0xfc833b6c6a1f8cc1, /* GL_SGIX_scalebias_hint */
    /*  878 */ 0xfe04490bc9621226, /* GL_SGIX_shadow */
    /*  879 */ 0xa1f64483e1ed6c09, /* GL_SGIX_shadow_ambient */
    /*  880 */ 0x1b1eb2d33e2626cb, /* GL_SGIX_sprite */
    /*  881 */ 0xab712623aed89578, /* GL_SGIX_subsample */
    /*  882 */ 0xf6707a8df70625ff, /* GL_SGIX_tag_sample_buffer */
    /*  883 */ 0xb31cc86db966473b, /* GL_SGIX_texture_add_env */
    /*  884 */ 0x8b7acea8e9290fae, /* GL_SGIX_texture_coordinate_clamp */
    /*  885 */ 0xb5df7fecc6d921f7, /* GL_SGIX_texture_lod_bias */
    /*  886 */ 0xb819f1015daf16c4, /* GL_SGIX_texture_multi_buffer */
    /*  887 */ 0x3c9d7b66aea3cba1, /* GL_SGIX_texture_scale_bias */
    /*  888 */ 0xe9afc853af27422d, /* GL_SGIX_vertex_preclip */
    /*  889 */ 0x3bb1183ffedb9c68, /* GL_SGIX_ycrcb */
    /*  890 */ 0x004ffc30998c20db, /* GL_SGIX_ycrcb_subsample */
    /*  891 */ 0x7ab4a4b4639c69df, /* GL_SGIX_ycrcba */
    /*  892 */ 0x014fc2d56670cd5a, /* GL_SGI_color_matrix */
    /*  893 */ 0x5f28de108b449e5d, /* GL_SGI_color_table */
    /*  894 */ 0xa03c2d1d2eeb1bd2, /* GL_SGI_texture_color_table */
    /*  895 */ 0xd3460591a825bcf6, /* GL_SUNX_constant_data */
    /*  896 */ 0x4e5296cda0471f61, /* GL_SUN_convolution_border_modes */
    /*  897 */ 0xe19c670da3369515, /* GL_SUN_global_alpha */
    /*  898 */ 0xbd8a54b9db901974, /* GL_SUN_mesh_array */
    /*  899 */ 0xa52af6dd6a5fb2d3, /* GL_SUN_slice_accum */
    /*  900 */ 0xbeb30cddf53ae288, /* GL_SUN_triangle_list */
    /*  901 */ 0xd0bf54f2a8798b55, /* GL_SUN_vertex */
    /*  902 */ 0x156892df7146814d, /* GL_VIV_shader_binary */
    /*  903 */ 0xf09a257256bde8f6, /* GL_WIN_phong_shading */
    /*  904 */ 0x5a3e106713a38cff  /* GL_WIN_specular_fog */
};

#ifdef __cplusplus
GladGLContext glad_gl_context = {};
#else
GladGLContext glad_gl_context = { 0 };
#endif

static void glad_gl_load_GL_VERSION_1_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           0, /* glAccum */
          12, /* glAlphaFunc */
          28, /* glBegin */
         105, /* glBitmap */
         122, /* glBlendFunc */
         151, /* glCallList */
         152, /* glCallLists */
         159, /* glClear */
         160, /* glClearAccum */
         168, /* glClearColor */
         172, /* glClearDepth */
         177, /* glClearIndex */
         186, /* glClearStencil */
         196, /* glClipPlane */
         199, /* glColor3b */
         200, /* glColor3bv */
         201, /* glColor3d */
         202, /* glColor3dv */
         203, /* glColor3f */
         206, /* glColor3fv */
         209, /* glColor3i */
         210, /* glColor3iv */
         211, /* glColor3s */
         212, /* glColor3sv */
         213, /* glColor3ub */
         214, /* glColor3ubv */
         215, /* glColor3ui */
         216, /* glColor3uiv */
         217, /* glColor3us */
         218, /* glColor3usv */
         221, /* glColor4b */
         222, /* glColor4bv */
         223, /* glColor4d */
         224, /* glColor4dv */
         225, /* glColor4f */
         228, /* glColor4fv */
         231, /* glColor4i */
         232, /* glColor4iv */
         233, /* glColor4s */
         234, /* glColor4sv */
         235, /* glColor4ub */
         240, /* glColor4ubv */
         241, /* glColor4ui */
         242, /* glColor4uiv */
         243, /* glColor4us */
         244, /* glColor4usv */
         251, /* glColorMask */
         254, /* glColorMaterial */
         345, /* glCopyPixels */
         392, /* glCullFace */
         417, /* glDeleteLists */
         449, /* glDepthFunc */
         450, /* glDepthMask */
         451, /* glDepthRange */
         463, /* glDisable */
         486, /* glDrawBuffer */
         508, /* glDrawPixels */
         523, /* glEdgeFlag */
         528, /* glEdgeFlagv */
         531, /* glEnable */
         544, /* glEnd */
         549, /* glEndList */
         561, /* glEvalCoord1d */
         562, /* glEvalCoord1dv */
         563, /* glEvalCoord1f */
         564, /* glEvalCoord1fv */
         567, /* glEvalCoord2d */
         568, /* glEvalCoord2dv */
         569, /* glEvalCoord2f */
         570, /* glEvalCoord2fv */
         574, /* glEvalMesh1 */
         575, /* glEvalMesh2 */
         576, /* glEvalPoint1 */
         577, /* glEvalPoint2 */
         581, /* glFeedbackBuffer */
         585, /* glFinish */
         591, /* glFlush */
         616, /* glFogf */
         617, /* glFogfv */
         618, /* glFogi */
         619, /* glFogiv */
         665, /* glFrontFace */
         666, /* glFrustum */
         677, /* glGenLists */
         726, /* glGetBooleanv */
         735, /* glGetClipPlane */
         774, /* glGetDoublev */
         775, /* glGetError */
         784, /* glGetFloatv */
         821, /* glGetIntegerv */
         828, /* glGetLightfv */
         829, /* glGetLightiv */
         841, /* glGetMapdv */
         842, /* glGetMapfv */
         843, /* glGetMapiv */
         845, /* glGetMaterialfv */
         846, /* glGetMaterialiv */
         927, /* glGetPixelMapfv */
         928, /* glGetPixelMapuiv */
         929, /* glGetPixelMapusv */
         939, /* glGetPolygonStipple */
        1004, /* glGetString */
        1011, /* glGetTexEnvfv */
        1012, /* glGetTexEnviv */
        1015, /* glGetTexGendv */
        1016, /* glGetTexGenfv */
        1017, /* glGetTexGeniv */
        1019, /* glGetTexImage */
        1020, /* glGetTexLevelParameterfv */
        1021, /* glGetTexLevelParameteriv */
        1028, /* glGetTexParameterfv */
        1029, /* glGetTexParameteriv */
        1169, /* glHint */
        1189, /* glIndexMask */
        1194, /* glIndexd */
        1195, /* glIndexdv */
        1196, /* glIndexf */
        1197, /* glIndexfv */
        1198, /* glIndexi */
        1199, /* glIndexiv */
        1200, /* glIndexs */
        1201, /* glIndexsv */
        1206, /* glInitNames */
        1226, /* glIsEnabled */
        1235, /* glIsList */
        1273, /* glLightModelf */
        1274, /* glLightModelfv */
        1275, /* glLightModeli */
        1276, /* glLightModeliv */
        1279, /* glLightf */
        1280, /* glLightfv */
        1281, /* glLighti */
        1282, /* glLightiv */
        1285, /* glLineStipple */
        1286, /* glLineWidth */
        1290, /* glListBase */
        1296, /* glLoadIdentity */
        1298, /* glLoadMatrixd */
        1299, /* glLoadMatrixf */
        1301, /* glLoadName */
        1309, /* glLogicOp */
        1322, /* glMap1d */
        1323, /* glMap1f */
        1325, /* glMap2d */
        1326, /* glMap2f */
        1332, /* glMapGrid1d */
        1333, /* glMapGrid1f */
        1335, /* glMapGrid2d */
        1336, /* glMapGrid2f */
        1350, /* glMaterialf */
        1351, /* glMaterialfv */
        1352, /* glMateriali */
        1353, /* glMaterialiv */
        1369, /* glMatrixMode */
        1396, /* glMultMatrixd */
        1397, /* glMultMatrixf */
        1612, /* glNewList */
        1614, /* glNormal3b */
        1615, /* glNormal3bv */
        1616, /* glNormal3d */
        1617, /* glNormal3dv */
        1618, /* glNormal3f */
        1621, /* glNormal3fv */
        1624, /* glNormal3i */
        1625, /* glNormal3iv */
        1626, /* glNormal3s */
        1627, /* glNormal3sv */
        1651, /* glOrtho */
        1657, /* glPassThrough */
        1685, /* glPixelMapfv */
        1686, /* glPixelMapuiv */
        1687, /* glPixelMapusv */
        1689, /* glPixelStoref */
        1690, /* glPixelStorei */
        1697, /* glPixelTransferf */
        1698, /* glPixelTransferi */
        1704, /* glPixelZoom */
        1720, /* glPointSize */
        1724, /* glPolygonMode */
        1730, /* glPolygonStipple */
        1731, /* glPopAttrib */
        1735, /* glPopMatrix */
        1736, /* glPopName */
        1929, /* glPushAttrib */
        1934, /* glPushMatrix */
        1935, /* glPushName */
        1941, /* glRasterPos2d */
        1942, /* glRasterPos2dv */
        1943, /* glRasterPos2f */
        1944, /* glRasterPos2fv */
        1945, /* glRasterPos2i */
        1946, /* glRasterPos2iv */
        1947, /* glRasterPos2s */
        1948, /* glRasterPos2sv */
        1951, /* glRasterPos3d */
        1952, /* glRasterPos3dv */
        1953, /* glRasterPos3f */
        1954, /* glRasterPos3fv */
        1955, /* glRasterPos3i */
        1956, /* glRasterPos3iv */
        1957, /* glRasterPos3s */
        1958, /* glRasterPos3sv */
        1961, /* glRasterPos4d */
        1962, /* glRasterPos4dv */
        1963, /* glRasterPos4f */
        1964, /* glRasterPos4fv */
        1965, /* glRasterPos4i */
        1966, /* glRasterPos4iv */
        1967, /* glRasterPos4s */
        1968, /* glRasterPos4sv */
        1972, /* glReadBuffer */
        1974, /* glReadPixels */
        1977, /* glRectd */
        1978, /* glRectdv */
        1979, /* glRectf */
        1980, /* glRectfv */
        1981, /* glRecti */
        1982, /* glRectiv */
        1983, /* glRects */
        1984, /* glRectsv */
        1991, /* glRenderMode */
        2031, /* glRotated */
        2032, /* glRotatef */
        2049, /* glScaled */
        2050, /* glScalef */
        2052, /* glScissor */
        2098, /* glSelectBuffer */
        2110, /* glShadeModel */
        2138, /* glStencilFunc */
        2141, /* glStencilMask */
        2143, /* glStencilOp */
        2185, /* glTexCoord1d */
        2186, /* glTexCoord1dv */
        2187, /* glTexCoord1f */
        2188, /* glTexCoord1fv */
        2191, /* glTexCoord1i */
        2192, /* glTexCoord1iv */
        2193, /* glTexCoord1s */
        2194, /* glTexCoord1sv */
        2199, /* glTexCoord2d */
        2200, /* glTexCoord2dv */
        2201, /* glTexCoord2f */
        2212, /* glTexCoord2fv */
        2215, /* glTexCoord2i */
        2216, /* glTexCoord2iv */
        2217, /* glTexCoord2s */
        2218, /* glTexCoord2sv */
        2223, /* glTexCoord3d */
        2224, /* glTexCoord3dv */
        2225, /* glTexCoord3f */
        2226, /* glTexCoord3fv */
        2229, /* glTexCoord3i */
        2230, /* glTexCoord3iv */
        2231, /* glTexCoord3s */
        2232, /* glTexCoord3sv */
        2237, /* glTexCoord4d */
        2238, /* glTexCoord4dv */
        2239, /* glTexCoord4f */
        2244, /* glTexCoord4fv */
        2247, /* glTexCoord4i */
        2248, /* glTexCoord4iv */
        2249, /* glTexCoord4s */
        2250, /* glTexCoord4sv */
        2266, /* glTexEnvf */
        2267, /* glTexEnvfv */
        2268, /* glTexEnvi */
        2269, /* glTexEnviv */
        2273, /* glTexGend */
        2274, /* glTexGendv */
        2275, /* glTexGenf */
        2276, /* glTexGenfv */
        2277, /* glTexGeni */
        2278, /* glTexGeniv */
        2281, /* glTexImage1D */
        2282, /* glTexImage2D */
        2297, /* glTexParameterf */
        2298, /* glTexParameterfv */
        2299, /* glTexParameteri */
        2300, /* glTexParameteriv */
        2395, /* glTranslated */
        2396, /* glTranslatef */
        2555, /* glVertex2d */
        2556, /* glVertex2dv */
        2557, /* glVertex2f */
        2558, /* glVertex2fv */
        2561, /* glVertex2i */
        2562, /* glVertex2iv */
        2563, /* glVertex2s */
        2564, /* glVertex2sv */
        2569, /* glVertex3d */
        2570, /* glVertex3dv */
        2571, /* glVertex3f */
        2572, /* glVertex3fv */
        2575, /* glVertex3i */
        2576, /* glVertex3iv */
        2577, /* glVertex3s */
        2578, /* glVertex3sv */
        2583, /* glVertex4d */
        2584, /* glVertex4dv */
        2585, /* glVertex4f */
        2586, /* glVertex4fv */
        2589, /* glVertex4i */
        2590, /* glVertex4iv */
        2591, /* glVertex4s */
        2592, /* glVertex4sv */
        2904  /* glViewport */
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
          18, /* glAreTexturesResident */
          20, /* glArrayElement */
          80, /* glBindTexture */
         259, /* glColorPointer */
         346, /* glCopyTexImage1D */
         348, /* glCopyTexImage2D */
         350, /* glCopyTexSubImage1D */
         352, /* glCopyTexSubImage2D */
         440, /* glDeleteTextures */
         464, /* glDisableClientState */
         479, /* glDrawArrays */
         496, /* glDrawElements */
         525, /* glEdgeFlagPointer */
         532, /* glEnableClientState */
         693, /* glGenTextures */
         937, /* glGetPointerv */
        1191, /* glIndexPointer */
        1202, /* glIndexub */
        1203, /* glIndexubv */
        1210, /* glInterleavedArrays */
        1258, /* glIsTexture */
        1633, /* glNormalPointer */
        1725, /* glPolygonOffset */
        1732, /* glPopClientAttrib */
        1743, /* glPrioritizeTextures */
        1930, /* glPushClientAttrib */
        2262, /* glTexCoordPointer */
        2322, /* glTexSubImage1D */
        2324, /* glTexSubImage2D */
        2859  /* glVertexPointer */
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
         354, /* glCopyTexSubImage3D */
         511, /* glDrawRangeElements */
        2286, /* glTexImage3D */
        2326  /* glTexSubImage3D */
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
           6, /* glActiveTexture */
         189, /* glClientActiveTexture */
         290, /* glCompressedTexImage1D */
         292, /* glCompressedTexImage2D */
         294, /* glCompressedTexImage3D */
         296, /* glCompressedTexSubImage1D */
         298, /* glCompressedTexSubImage2D */
         300, /* glCompressedTexSubImage3D */
         754, /* glGetCompressedTexImage */
        1303, /* glLoadTransposeMatrixd */
        1305, /* glLoadTransposeMatrixf */
        1399, /* glMultTransposeMatrixd */
        1401, /* glMultTransposeMatrixf */
        1430, /* glMultiTexCoord1d */
        1432, /* glMultiTexCoord1dv */
        1434, /* glMultiTexCoord1f */
        1436, /* glMultiTexCoord1fv */
        1440, /* glMultiTexCoord1i */
        1442, /* glMultiTexCoord1iv */
        1444, /* glMultiTexCoord1s */
        1446, /* glMultiTexCoord1sv */
        1452, /* glMultiTexCoord2d */
        1454, /* glMultiTexCoord2dv */
        1456, /* glMultiTexCoord2f */
        1458, /* glMultiTexCoord2fv */
        1462, /* glMultiTexCoord2i */
        1464, /* glMultiTexCoord2iv */
        1466, /* glMultiTexCoord2s */
        1468, /* glMultiTexCoord2sv */
        1474, /* glMultiTexCoord3d */
        1476, /* glMultiTexCoord3dv */
        1478, /* glMultiTexCoord3f */
        1480, /* glMultiTexCoord3fv */
        1484, /* glMultiTexCoord3i */
        1486, /* glMultiTexCoord3iv */
        1488, /* glMultiTexCoord3s */
        1490, /* glMultiTexCoord3sv */
        1496, /* glMultiTexCoord4d */
        1498, /* glMultiTexCoord4dv */
        1500, /* glMultiTexCoord4f */
        1502, /* glMultiTexCoord4fv */
        1506, /* glMultiTexCoord4i */
        1508, /* glMultiTexCoord4iv */
        1510, /* glMultiTexCoord4s */
        1512, /* glMultiTexCoord4sv */
        2034  /* glSampleCoverage */
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
         109, /* glBlendColor */
         112, /* glBlendEquation */
         124, /* glBlendFuncSeparate */
         602, /* glFogCoordPointer */
         605, /* glFogCoordd */
         607, /* glFogCoorddv */
         609, /* glFogCoordf */
         611, /* glFogCoordfv */
        1404, /* glMultiDrawArrays */
        1413, /* glMultiDrawElements */
        1707, /* glPointParameterf */
        1711, /* glPointParameterfv */
        1715, /* glPointParameteri */
        1717, /* glPointParameteriv */
        2058, /* glSecondaryColor3b */
        2060, /* glSecondaryColor3bv */
        2062, /* glSecondaryColor3d */
        2064, /* glSecondaryColor3dv */
        2066, /* glSecondaryColor3f */
        2068, /* glSecondaryColor3fv */
        2072, /* glSecondaryColor3i */
        2074, /* glSecondaryColor3iv */
        2076, /* glSecondaryColor3s */
        2078, /* glSecondaryColor3sv */
        2080, /* glSecondaryColor3ub */
        2082, /* glSecondaryColor3ubv */
        2084, /* glSecondaryColor3ui */
        2086, /* glSecondaryColor3uiv */
        2088, /* glSecondaryColor3us */
        2090, /* glSecondaryColor3usv */
        2095, /* glSecondaryColorPointer */
        2924, /* glWindowPos2d */
        2927, /* glWindowPos2dv */
        2930, /* glWindowPos2f */
        2933, /* glWindowPos2fv */
        2936, /* glWindowPos2i */
        2939, /* glWindowPos2iv */
        2942, /* glWindowPos2s */
        2945, /* glWindowPos2sv */
        2948, /* glWindowPos3d */
        2951, /* glWindowPos3dv */
        2954, /* glWindowPos3f */
        2957, /* glWindowPos3fv */
        2960, /* glWindowPos3i */
        2963, /* glWindowPos3iv */
        2966, /* glWindowPos3s */
        2969  /* glWindowPos3sv */
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
          36, /* glBeginQuery */
          46, /* glBindBuffer */
         140, /* glBufferData */
         148, /* glBufferSubData */
         409, /* glDeleteBuffers */
         430, /* glDeleteQueries */
         553, /* glEndQuery */
         670, /* glGenBuffers */
         685, /* glGenQueries */
         728, /* glGetBufferParameteriv */
         731, /* glGetBufferPointerv */
         733, /* glGetBufferSubData */
         977, /* glGetQueryObjectiv */
         981, /* glGetQueryObjectuiv */
         983, /* glGetQueryiv */
        1222, /* glIsBuffer */
        1249, /* glIsQuery */
        1328, /* glMapBuffer */
        2517  /* glUnmapBuffer */
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
          27, /* glAttachShader */
          44, /* glBindAttribLocation */
         115, /* glBlendEquationSeparate */
         281, /* glCompileShader */
         375, /* glCreateProgram */
         383, /* glCreateShader */
         426, /* glDeleteProgram */
         437, /* glDeleteShader */
         461, /* glDetachShader */
         473, /* glDisableVertexAttribArray */
         487, /* glDrawBuffers */
         541, /* glEnableVertexAttribArray */
         706, /* glGetActiveAttrib */
         711, /* glGetActiveUniform */
         721, /* glGetAttachedShaders */
         722, /* glGetAttribLocation */
         945, /* glGetProgramInfoLog */
         967, /* glGetProgramiv */
         995, /* glGetShaderInfoLog */
         997, /* glGetShaderSource */
         999, /* glGetShaderiv */
        1060, /* glGetUniformLocation */
        1065, /* glGetUniformfv */
        1069, /* glGetUniformiv */
        1102, /* glGetVertexAttribPointerv */
        1105, /* glGetVertexAttribdv */
        1108, /* glGetVertexAttribfv */
        1111, /* glGetVertexAttribiv */
        1245, /* glIsProgram */
        1255, /* glIsShader */
        1288, /* glLinkProgram */
        2115, /* glShaderSource */
        2139, /* glStencilFuncSeparate */
        2142, /* glStencilMaskSeparate */
        2144, /* glStencilOpSeparate */
        2400, /* glUniform1f */
        2402, /* glUniform1fv */
        2404, /* glUniform1i */
        2410, /* glUniform1iv */
        2422, /* glUniform2f */
        2424, /* glUniform2fv */
        2426, /* glUniform2i */
        2432, /* glUniform2iv */
        2444, /* glUniform3f */
        2446, /* glUniform3fv */
        2448, /* glUniform3i */
        2454, /* glUniform3iv */
        2466, /* glUniform4f */
        2468, /* glUniform4fv */
        2470, /* glUniform4i */
        2476, /* glUniform4iv */
        2493, /* glUniformMatrix2fv */
        2500, /* glUniformMatrix3fv */
        2507, /* glUniformMatrix4fv */
        2525, /* glUseProgram */
        2540, /* glValidateProgram */
        2625, /* glVertexAttrib1d */
        2628, /* glVertexAttrib1dv */
        2631, /* glVertexAttrib1f */
        2634, /* glVertexAttrib1fv */
        2639, /* glVertexAttrib1s */
        2642, /* glVertexAttrib1sv */
        2645, /* glVertexAttrib2d */
        2648, /* glVertexAttrib2dv */
        2651, /* glVertexAttrib2f */
        2654, /* glVertexAttrib2fv */
        2659, /* glVertexAttrib2s */
        2662, /* glVertexAttrib2sv */
        2665, /* glVertexAttrib3d */
        2668, /* glVertexAttrib3dv */
        2671, /* glVertexAttrib3f */
        2674, /* glVertexAttrib3fv */
        2679, /* glVertexAttrib3s */
        2682, /* glVertexAttrib3sv */
        2685, /* glVertexAttrib4Nbv */
        2687, /* glVertexAttrib4Niv */
        2689, /* glVertexAttrib4Nsv */
        2691, /* glVertexAttrib4Nub */
        2693, /* glVertexAttrib4Nubv */
        2695, /* glVertexAttrib4Nuiv */
        2697, /* glVertexAttrib4Nusv */
        2699, /* glVertexAttrib4bv */
        2701, /* glVertexAttrib4d */
        2704, /* glVertexAttrib4dv */
        2707, /* glVertexAttrib4f */
        2710, /* glVertexAttrib4fv */
        2715, /* glVertexAttrib4iv */
        2717, /* glVertexAttrib4s */
        2720, /* glVertexAttrib4sv */
        2724, /* glVertexAttrib4ubv */
        2727, /* glVertexAttrib4uiv */
        2729, /* glVertexAttrib4usv */
        2828  /* glVertexAttribPointer */
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
        2496, /* glUniformMatrix2x3fv */
        2498, /* glUniformMatrix2x4fv */
        2503, /* glUniformMatrix3x2fv */
        2505, /* glUniformMatrix3x4fv */
        2510, /* glUniformMatrix4x2fv */
        2512  /* glUniformMatrix4x3fv */
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
          29, /* glBeginConditionalRender */
          39, /* glBeginTransformFeedback */
          48, /* glBindBufferBase */
          53, /* glBindBufferRange */
          58, /* glBindFragDataLocation */
          62, /* glBindFramebuffer */
          74, /* glBindRenderbuffer */
          87, /* glBindVertexArray */
         133, /* glBlitFramebuffer */
         153, /* glCheckFramebufferStatus */
         157, /* glClampColor */
         164, /* glClearBufferfi */
         165, /* glClearBufferfv */
         166, /* glClearBufferiv */
         167, /* glClearBufferuiv */
         253, /* glColorMaski */
         415, /* glDeleteFramebuffers */
         433, /* glDeleteRenderbuffers */
         444, /* glDeleteVertexArrays */
         475, /* glDisablei */
         543, /* glEnablei */
         545, /* glEndConditionalRender */
         556, /* glEndTransformFeedback */
         592, /* glFlushMappedBufferRange */
         644, /* glFramebufferRenderbuffer */
         650, /* glFramebufferTexture1D */
         652, /* glFramebufferTexture2D */
         654, /* glFramebufferTexture3D */
         660, /* glFramebufferTextureLayer */
         675, /* glGenFramebuffers */
         688, /* glGenRenderbuffers */
         697, /* glGenVertexArrays */
         700, /* glGenerateMipmap */
         725, /* glGetBooleani_v */
         787, /* glGetFragDataLocation */
         793, /* glGetFramebufferAttachmentParameteriv */
         818, /* glGetIntegeri_v */
         985, /* glGetRenderbufferParameteriv */
        1005, /* glGetStringi */
        1023, /* glGetTexParameterIiv */
        1025, /* glGetTexParameterIuiv */
        1051, /* glGetTransformFeedbackVarying */
        1073, /* glGetUniformuiv */
        1093, /* glGetVertexAttribIiv */
        1095, /* glGetVertexAttribIuiv */
        1228, /* glIsEnabledi */
        1231, /* glIsFramebuffer */
        1251, /* glIsRenderbuffer */
        1265, /* glIsVertexArray */
        1330, /* glMapBufferRange */
        1992, /* glRenderbufferStorage */
        1994, /* glRenderbufferStorageMultisample */
        2293, /* glTexParameterIiv */
        2295, /* glTexParameterIuiv */
        2391, /* glTransformFeedbackVaryings */
        2412, /* glUniform1ui */
        2418, /* glUniform1uiv */
        2434, /* glUniform2ui */
        2440, /* glUniform2uiv */
        2456, /* glUniform3ui */
        2462, /* glUniform3uiv */
        2478, /* glUniform4ui */
        2484, /* glUniform4uiv */
        2737, /* glVertexAttribI1i */
        2739, /* glVertexAttribI1iv */
        2741, /* glVertexAttribI1ui */
        2743, /* glVertexAttribI1uiv */
        2745, /* glVertexAttribI2i */
        2747, /* glVertexAttribI2iv */
        2749, /* glVertexAttribI2ui */
        2751, /* glVertexAttribI2uiv */
        2753, /* glVertexAttribI3i */
        2755, /* glVertexAttribI3iv */
        2757, /* glVertexAttribI3ui */
        2759, /* glVertexAttribI3uiv */
        2761, /* glVertexAttribI4bv */
        2763, /* glVertexAttribI4i */
        2765, /* glVertexAttribI4iv */
        2767, /* glVertexAttribI4sv */
        2769, /* glVertexAttribI4ubv */
        2771, /* glVertexAttribI4ui */
        2773, /* glVertexAttribI4uiv */
        2775, /* glVertexAttribI4usv */
        2779  /* glVertexAttribIPointer */
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
          48, /* glBindBufferBase */
          53, /* glBindBufferRange */
         327, /* glCopyBufferSubData */
         482, /* glDrawArraysInstanced */
         499, /* glDrawElementsInstanced */
         713, /* glGetActiveUniformBlockName */
         714, /* glGetActiveUniformBlockiv */
         715, /* glGetActiveUniformName */
         716, /* glGetActiveUniformsiv */
         818, /* glGetIntegeri_v */
        1057, /* glGetUniformBlockIndex */
        1059, /* glGetUniformIndices */
        1740, /* glPrimitiveRestartIndex */
        2177, /* glTexBuffer */
        2486  /* glUniformBlockBinding */
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
         194, /* glClientWaitSync */
         439, /* glDeleteSync */
         497, /* glDrawElementsBaseVertex */
         502, /* glDrawElementsInstancedBaseVertex */
         512, /* glDrawRangeElementsBaseVertex */
         583, /* glFenceSync */
         649, /* glFramebufferTexture */
         727, /* glGetBufferParameteri64v */
         815, /* glGetInteger64i_v */
         816, /* glGetInteger64v */
         868, /* glGetMultisamplefv */
        1008, /* glGetSynciv */
        1257, /* glIsSync */
        1414, /* glMultiDrawElementsBaseVertex */
        1927, /* glProvokingVertex */
        2040, /* glSampleMaski */
        2284, /* glTexImage2DMultisample */
        2288, /* glTexImage3DMultisample */
        2912  /* glWaitSync */
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
          60, /* glBindFragDataLocationIndexed */
          76, /* glBindSampler */
         255, /* glColorP3ui */
         256, /* glColorP3uiv */
         257, /* glColorP4ui */
         258, /* glColorP4uiv */
         435, /* glDeleteSamplers */
         690, /* glGenSamplers */
         786, /* glGetFragDataIndex */
         975, /* glGetQueryObjecti64v */
         979, /* glGetQueryObjectui64v */
         987, /* glGetSamplerParameterIiv */
         988, /* glGetSamplerParameterIuiv */
         989, /* glGetSamplerParameterfv */
         990, /* glGetSamplerParameteriv */
        1253, /* glIsSampler */
        1516, /* glMultiTexCoordP1ui */
        1517, /* glMultiTexCoordP1uiv */
        1518, /* glMultiTexCoordP2ui */
        1519, /* glMultiTexCoordP2uiv */
        1520, /* glMultiTexCoordP3ui */
        1521, /* glMultiTexCoordP3uiv */
        1522, /* glMultiTexCoordP4ui */
        1523, /* glMultiTexCoordP4uiv */
        1631, /* glNormalP3ui */
        1632, /* glNormalP3uiv */
        1936, /* glQueryCounter */
        2043, /* glSamplerParameterIiv */
        2044, /* glSamplerParameterIuiv */
        2045, /* glSamplerParameterf */
        2046, /* glSamplerParameterfv */
        2047, /* glSamplerParameteri */
        2048, /* glSamplerParameteriv */
        2093, /* glSecondaryColorP3ui */
        2094, /* glSecondaryColorP3uiv */
        2254, /* glTexCoordP1ui */
        2255, /* glTexCoordP1uiv */
        2256, /* glTexCoordP2ui */
        2257, /* glTexCoordP2uiv */
        2258, /* glTexCoordP3ui */
        2259, /* glTexCoordP3uiv */
        2260, /* glTexCoordP4ui */
        2261, /* glTexCoordP4uiv */
        2733, /* glVertexAttribDivisor */
        2819, /* glVertexAttribP1ui */
        2820, /* glVertexAttribP1uiv */
        2821, /* glVertexAttribP2ui */
        2822, /* glVertexAttribP2uiv */
        2823, /* glVertexAttribP3ui */
        2824, /* glVertexAttribP3uiv */
        2825, /* glVertexAttribP4ui */
        2826, /* glVertexAttribP4uiv */
        2853, /* glVertexP2ui */
        2854, /* glVertexP2uiv */
        2855, /* glVertexP3ui */
        2856, /* glVertexP3uiv */
        2857, /* glVertexP4ui */
        2858  /* glVertexP4uiv */
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
          38, /* glBeginQueryIndexed */
          85, /* glBindTransformFeedback */
         118, /* glBlendEquationSeparatei */
         120, /* glBlendEquationi */
         128, /* glBlendFuncSeparatei */
         130, /* glBlendFunci */
         442, /* glDeleteTransformFeedbacks */
         481, /* glDrawArraysIndirect */
         498, /* glDrawElementsIndirect */
         515, /* glDrawTransformFeedback */
         518, /* glDrawTransformFeedbackStream */
         555, /* glEndQueryIndexed */
         695, /* glGenTransformFeedbacks */
         708, /* glGetActiveSubroutineName */
         709, /* glGetActiveSubroutineUniformName */
         710, /* glGetActiveSubroutineUniformiv */
         963, /* glGetProgramStageiv */
         974, /* glGetQueryIndexediv */
        1006, /* glGetSubroutineIndex */
        1007, /* glGetSubroutineUniformLocation */
        1063, /* glGetUniformSubroutineuiv */
        1064, /* glGetUniformdv */
        1262, /* glIsTransformFeedback */
        1392, /* glMinSampleShading */
        1659, /* glPatchParameterfv */
        1660, /* glPatchParameteri */
        1682, /* glPauseTransformFeedback */
        2029, /* glResumeTransformFeedback */
        2398, /* glUniform1d */
        2399, /* glUniform1dv */
        2420, /* glUniform2d */
        2421, /* glUniform2dv */
        2442, /* glUniform3d */
        2443, /* glUniform3dv */
        2464, /* glUniform4d */
        2465, /* glUniform4dv */
        2492, /* glUniformMatrix2dv */
        2495, /* glUniformMatrix2x3dv */
        2497, /* glUniformMatrix2x4dv */
        2499, /* glUniformMatrix3dv */
        2502, /* glUniformMatrix3x2dv */
        2504, /* glUniformMatrix3x4dv */
        2506, /* glUniformMatrix4dv */
        2509, /* glUniformMatrix4x2dv */
        2511, /* glUniformMatrix4x3dv */
        2513  /* glUniformSubroutinesuiv */
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
           4, /* glActiveShaderProgram */
          73, /* glBindProgramPipeline */
         174, /* glClearDepthf */
         386, /* glCreateShaderProgramv */
         427, /* glDeleteProgramPipelines */
         453, /* glDepthRangeArrayv */
         454, /* glDepthRangeIndexed */
         457, /* glDepthRangef */
         682, /* glGenProgramPipelines */
         772, /* glGetDoublei_v */
         782, /* glGetFloati_v */
         940, /* glGetProgramBinary */
         955, /* glGetProgramPipelineInfoLog */
         956, /* glGetProgramPipelineiv */
         996, /* glGetShaderPrecisionFormat */
        1097, /* glGetVertexAttribLdv */
        1248, /* glIsProgramPipeline */
        1746, /* glProgramBinary */
        1780, /* glProgramParameteri */
        1788, /* glProgramUniform1d */
        1790, /* glProgramUniform1dv */
        1792, /* glProgramUniform1f */
        1794, /* glProgramUniform1fv */
        1796, /* glProgramUniform1i */
        1802, /* glProgramUniform1iv */
        1804, /* glProgramUniform1ui */
        1810, /* glProgramUniform1uiv */
        1812, /* glProgramUniform2d */
        1814, /* glProgramUniform2dv */
        1816, /* glProgramUniform2f */
        1818, /* glProgramUniform2fv */
        1820, /* glProgramUniform2i */
        1826, /* glProgramUniform2iv */
        1828, /* glProgramUniform2ui */
        1834, /* glProgramUniform2uiv */
        1836, /* glProgramUniform3d */
        1838, /* glProgramUniform3dv */
        1840, /* glProgramUniform3f */
        1842, /* glProgramUniform3fv */
        1844, /* glProgramUniform3i */
        1850, /* glProgramUniform3iv */
        1852, /* glProgramUniform3ui */
        1858, /* glProgramUniform3uiv */
        1860, /* glProgramUniform4d */
        1862, /* glProgramUniform4dv */
        1864, /* glProgramUniform4f */
        1866, /* glProgramUniform4fv */
        1868, /* glProgramUniform4i */
        1874, /* glProgramUniform4iv */
        1876, /* glProgramUniform4ui */
        1882, /* glProgramUniform4uiv */
        1888, /* glProgramUniformMatrix2dv */
        1890, /* glProgramUniformMatrix2fv */
        1892, /* glProgramUniformMatrix2x3dv */
        1894, /* glProgramUniformMatrix2x3fv */
        1896, /* glProgramUniformMatrix2x4dv */
        1898, /* glProgramUniformMatrix2x4fv */
        1900, /* glProgramUniformMatrix3dv */
        1902, /* glProgramUniformMatrix3fv */
        1904, /* glProgramUniformMatrix3x2dv */
        1906, /* glProgramUniformMatrix3x2fv */
        1908, /* glProgramUniformMatrix3x4dv */
        1910, /* glProgramUniformMatrix3x4fv */
        1912, /* glProgramUniformMatrix4dv */
        1914, /* glProgramUniformMatrix4fv */
        1916, /* glProgramUniformMatrix4x2dv */
        1918, /* glProgramUniformMatrix4x2fv */
        1920, /* glProgramUniformMatrix4x3dv */
        1922, /* glProgramUniformMatrix4x3fv */
        1989, /* glReleaseShaderCompiler */
        2053, /* glScissorArrayv */
        2056, /* glScissorIndexed */
        2057, /* glScissorIndexedv */
        2111, /* glShaderBinary */
        2527, /* glUseProgramStages */
        2542, /* glValidateProgramPipeline */
        2781, /* glVertexAttribL1d */
        2783, /* glVertexAttribL1dv */
        2791, /* glVertexAttribL2d */
        2793, /* glVertexAttribL2dv */
        2799, /* glVertexAttribL3d */
        2801, /* glVertexAttribL3dv */
        2807, /* glVertexAttribL4d */
        2809, /* glVertexAttribL4dv */
        2817, /* glVertexAttribLPointer */
        2905, /* glViewportArrayv */
        2906, /* glViewportIndexedf */
        2907  /* glViewportIndexedfv */
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
          64, /* glBindImageTexture */
         484, /* glDrawArraysInstancedBaseInstance */
         501, /* glDrawElementsInstancedBaseInstance */
         503, /* glDrawElementsInstancedBaseVertexBaseInstance */
         516, /* glDrawTransformFeedbackInstanced */
         519, /* glDrawTransformFeedbackStreamInstanced */
         705, /* glGetActiveAtomicCounterBufferiv */
         824, /* glGetInternalformativ */
        1388, /* glMemoryBarrier */
        2304, /* glTexStorage1D */
        2306, /* glTexStorage2D */
        2309  /* glTexStorage3D */
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
          89, /* glBindVertexBuffer */
         162, /* glClearBufferData */
         163, /* glClearBufferSubData */
         336, /* glCopyImageSubData */
         396, /* glDebugMessageCallback */
         399, /* glDebugMessageControl */
         402, /* glDebugMessageInsert */
         476, /* glDispatchCompute */
         478, /* glDispatchComputeIndirect */
         641, /* glFramebufferParameteri */
         767, /* glGetDebugMessageLog */
         796, /* glGetFramebufferParameteriv */
         823, /* glGetInternalformati64v */
         896, /* glGetObjectLabel */
         901, /* glGetObjectPtrLabel */
         937, /* glGetPointerv */
         946, /* glGetProgramInterfaceiv */
         957, /* glGetProgramResourceIndex */
         958, /* glGetProgramResourceLocation */
         959, /* glGetProgramResourceLocationIndex */
         960, /* glGetProgramResourceName */
         962, /* glGetProgramResourceiv */
        1212, /* glInvalidateBufferData */
        1213, /* glInvalidateBufferSubData */
        1214, /* glInvalidateFramebuffer */
        1217, /* glInvalidateSubFramebuffer */
        1218, /* glInvalidateTexImage */
        1219, /* glInvalidateTexSubImage */
        1406, /* glMultiDrawArraysIndirect */
        1416, /* glMultiDrawElementsIndirect */
        1647, /* glObjectLabel */
        1648, /* glObjectPtrLabel */
        1733, /* glPopDebugGroup */
        1932, /* glPushDebugGroup */
        2117, /* glShaderStorageBlockBinding */
        2180, /* glTexBufferRange */
        2308, /* glTexStorage2DMultisample */
        2311, /* glTexStorage3DMultisample */
        2385, /* glTextureView */
        2732, /* glVertexAttribBinding */
        2735, /* glVertexAttribFormat */
        2777, /* glVertexAttribIFormat */
        2815, /* glVertexAttribLFormat */
        2848  /* glVertexBindingDivisor */
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
          56, /* glBindBuffersBase */
          57, /* glBindBuffersRange */
          66, /* glBindImageTextures */
          77, /* glBindSamplers */
          84, /* glBindTextures */
          90, /* glBindVertexBuffers */
         145, /* glBufferStorage */
         187, /* glClearTexImage */
         188  /* glClearTexSubImage */
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
          82, /* glBindTextureUnit */
         137, /* glBlitNamedFramebuffer */
         155, /* glCheckNamedFramebufferStatus */
         178, /* glClearNamedBufferData */
         180, /* glClearNamedBufferSubData */
         182, /* glClearNamedFramebufferfi */
         183, /* glClearNamedFramebufferfv */
         184, /* glClearNamedFramebufferiv */
         185, /* glClearNamedFramebufferuiv */
         195, /* glClipControl */
         305, /* glCompressedTextureSubImage1D */
         307, /* glCompressedTextureSubImage2D */
         309, /* glCompressedTextureSubImage3D */
         343, /* glCopyNamedBufferSubData */
         358, /* glCopyTextureSubImage1D */
         360, /* glCopyTextureSubImage2D */
         362, /* glCopyTextureSubImage3D */
         370, /* glCreateBuffers */
         372, /* glCreateFramebuffers */
         377, /* glCreateProgramPipelines */
         379, /* glCreateQueries */
         380, /* glCreateRenderbuffers */
         381, /* glCreateSamplers */
         389, /* glCreateTextures */
         390, /* glCreateTransformFeedbacks */
         391, /* glCreateVertexArrays */
         469, /* glDisableVertexArrayAttrib */
         537, /* glEnableVertexArrayAttrib */
         594, /* glFlushMappedNamedBufferRange */
         703, /* glGenerateTextureMipmap */
         756, /* glGetCompressedTextureImage */
         758, /* glGetCompressedTextureSubImage */
         799, /* glGetGraphicsResetStatus */
         870, /* glGetNamedBufferParameteri64v */
         871, /* glGetNamedBufferParameteriv */
         874, /* glGetNamedBufferPointerv */
         876, /* glGetNamedBufferSubData */
         878, /* glGetNamedFramebufferAttachmentParameteriv */
         881, /* glGetNamedFramebufferParameteriv */
         889, /* glGetNamedRenderbufferParameteriv */
         970, /* glGetQueryBufferObjecti64v */
         971, /* glGetQueryBufferObjectiv */
         972, /* glGetQueryBufferObjectui64v */
         973, /* glGetQueryBufferObjectuiv */
        1033, /* glGetTextureImage */
        1035, /* glGetTextureLevelParameterfv */
        1037, /* glGetTextureLevelParameteriv */
        1039, /* glGetTextureParameterIiv */
        1041, /* glGetTextureParameterIuiv */
        1043, /* glGetTextureParameterfv */
        1045, /* glGetTextureParameteriv */
        1049, /* glGetTextureSubImage */
        1054, /* glGetTransformFeedbacki64_v */
        1055, /* glGetTransformFeedbacki_v */
        1056, /* glGetTransformFeedbackiv */
        1084, /* glGetVertexArrayIndexed64iv */
        1085, /* glGetVertexArrayIndexediv */
        1090, /* glGetVertexArrayiv */
        1123, /* glGetnColorTable */
        1125, /* glGetnCompressedTexImage */
        1127, /* glGetnConvolutionFilter */
        1129, /* glGetnHistogram */
        1131, /* glGetnMapdv */
        1133, /* glGetnMapfv */
        1135, /* glGetnMapiv */
        1137, /* glGetnMinmax */
        1139, /* glGetnPixelMapfv */
        1141, /* glGetnPixelMapuiv */
        1143, /* glGetnPixelMapusv */
        1145, /* glGetnPolygonStipple */
        1147, /* glGetnSeparableFilter */
        1149, /* glGetnTexImage */
        1151, /* glGetnUniformdv */
        1153, /* glGetnUniformfv */
        1156, /* glGetnUniformiv */
        1159, /* glGetnUniformuiv */
        1215, /* glInvalidateNamedFramebufferData */
        1216, /* glInvalidateNamedFramebufferSubData */
        1338, /* glMapNamedBuffer */
        1340, /* glMapNamedBufferRange */
        1389, /* glMemoryBarrierByRegion */
        1563, /* glNamedBufferData */
        1568, /* glNamedBufferStorage */
        1572, /* glNamedBufferSubData */
        1575, /* glNamedFramebufferDrawBuffer */
        1576, /* glNamedFramebufferDrawBuffers */
        1577, /* glNamedFramebufferParameteri */
        1579, /* glNamedFramebufferReadBuffer */
        1580, /* glNamedFramebufferRenderbuffer */
        1585, /* glNamedFramebufferTexture */
        1591, /* glNamedFramebufferTextureLayer */
        1605, /* glNamedRenderbufferStorage */
        1607, /* glNamedRenderbufferStorageMultisample */
        1975, /* glReadnPixels */
        2330, /* glTextureBarrier */
        2332, /* glTextureBuffer */
        2334, /* glTextureBufferRange */
        2349, /* glTextureParameterIiv */
        2351, /* glTextureParameterIuiv */
        2353, /* glTextureParameterf */
        2355, /* glTextureParameterfv */
        2357, /* glTextureParameteri */
        2359, /* glTextureParameteriv */
        2363, /* glTextureStorage1D */
        2365, /* glTextureStorage2D */
        2367, /* glTextureStorage2DMultisample */
        2369, /* glTextureStorage3D */
        2371, /* glTextureStorage3DMultisample */
        2379, /* glTextureSubImage1D */
        2381, /* glTextureSubImage2D */
        2383, /* glTextureSubImage3D */
        2388, /* glTransformFeedbackBufferBase */
        2389, /* glTransformFeedbackBufferRange */
        2519, /* glUnmapNamedBuffer */
        2595, /* glVertexArrayAttribBinding */
        2596, /* glVertexArrayAttribFormat */
        2597, /* glVertexArrayAttribIFormat */
        2598, /* glVertexArrayAttribLFormat */
        2600, /* glVertexArrayBindingDivisor */
        2603, /* glVertexArrayElementBuffer */
        2622, /* glVertexArrayVertexBuffer */
        2623  /* glVertexArrayVertexBuffers */
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
        1410, /* glMultiDrawArraysIndirectCount */
        1420, /* glMultiDrawElementsIndirectCount */
        1726, /* glPolygonOffsetClamp */
        2127  /* glSpecializeShader */
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
           6, /* glActiveTexture */
          27, /* glAttachShader */
          44, /* glBindAttribLocation */
          46, /* glBindBuffer */
          62, /* glBindFramebuffer */
          74, /* glBindRenderbuffer */
          80, /* glBindTexture */
         109, /* glBlendColor */
         112, /* glBlendEquation */
         115, /* glBlendEquationSeparate */
         122, /* glBlendFunc */
         124, /* glBlendFuncSeparate */
         140, /* glBufferData */
         148, /* glBufferSubData */
         153, /* glCheckFramebufferStatus */
         159, /* glClear */
         168, /* glClearColor */
         174, /* glClearDepthf */
         186, /* glClearStencil */
         251, /* glColorMask */
         281, /* glCompileShader */
         292, /* glCompressedTexImage2D */
         298, /* glCompressedTexSubImage2D */
         348, /* glCopyTexImage2D */
         352, /* glCopyTexSubImage2D */
         375, /* glCreateProgram */
         383, /* glCreateShader */
         392, /* glCullFace */
         409, /* glDeleteBuffers */
         415, /* glDeleteFramebuffers */
         426, /* glDeleteProgram */
         433, /* glDeleteRenderbuffers */
         437, /* glDeleteShader */
         440, /* glDeleteTextures */
         449, /* glDepthFunc */
         450, /* glDepthMask */
         457, /* glDepthRangef */
         461, /* glDetachShader */
         463, /* glDisable */
         473, /* glDisableVertexAttribArray */
         479, /* glDrawArrays */
         496, /* glDrawElements */
         531, /* glEnable */
         541, /* glEnableVertexAttribArray */
         585, /* glFinish */
         591, /* glFlush */
         644, /* glFramebufferRenderbuffer */
         652, /* glFramebufferTexture2D */
         665, /* glFrontFace */
         670, /* glGenBuffers */
         675, /* glGenFramebuffers */
         688, /* glGenRenderbuffers */
         693, /* glGenTextures */
         700, /* glGenerateMipmap */
         706, /* glGetActiveAttrib */
         711, /* glGetActiveUniform */
         721, /* glGetAttachedShaders */
         722, /* glGetAttribLocation */
         726, /* glGetBooleanv */
         728, /* glGetBufferParameteriv */
         775, /* glGetError */
         784, /* glGetFloatv */
         793, /* glGetFramebufferAttachmentParameteriv */
         821, /* glGetIntegerv */
         945, /* glGetProgramInfoLog */
         967, /* glGetProgramiv */
         985, /* glGetRenderbufferParameteriv */
         995, /* glGetShaderInfoLog */
         996, /* glGetShaderPrecisionFormat */
         997, /* glGetShaderSource */
         999, /* glGetShaderiv */
        1004, /* glGetString */
        1028, /* glGetTexParameterfv */
        1029, /* glGetTexParameteriv */
        1060, /* glGetUniformLocation */
        1065, /* glGetUniformfv */
        1069, /* glGetUniformiv */
        1102, /* glGetVertexAttribPointerv */
        1108, /* glGetVertexAttribfv */
        1111, /* glGetVertexAttribiv */
        1169, /* glHint */
        1222, /* glIsBuffer */
        1226, /* glIsEnabled */
        1231, /* glIsFramebuffer */
        1245, /* glIsProgram */
        1251, /* glIsRenderbuffer */
        1255, /* glIsShader */
        1258, /* glIsTexture */
        1286, /* glLineWidth */
        1288, /* glLinkProgram */
        1690, /* glPixelStorei */
        1725, /* glPolygonOffset */
        1974, /* glReadPixels */
        1989, /* glReleaseShaderCompiler */
        1992, /* glRenderbufferStorage */
        2034, /* glSampleCoverage */
        2052, /* glScissor */
        2111, /* glShaderBinary */
        2115, /* glShaderSource */
        2138, /* glStencilFunc */
        2139, /* glStencilFuncSeparate */
        2141, /* glStencilMask */
        2142, /* glStencilMaskSeparate */
        2143, /* glStencilOp */
        2144, /* glStencilOpSeparate */
        2282, /* glTexImage2D */
        2297, /* glTexParameterf */
        2298, /* glTexParameterfv */
        2299, /* glTexParameteri */
        2300, /* glTexParameteriv */
        2324, /* glTexSubImage2D */
        2400, /* glUniform1f */
        2402, /* glUniform1fv */
        2404, /* glUniform1i */
        2410, /* glUniform1iv */
        2422, /* glUniform2f */
        2424, /* glUniform2fv */
        2426, /* glUniform2i */
        2432, /* glUniform2iv */
        2444, /* glUniform3f */
        2446, /* glUniform3fv */
        2448, /* glUniform3i */
        2454, /* glUniform3iv */
        2466, /* glUniform4f */
        2468, /* glUniform4fv */
        2470, /* glUniform4i */
        2476, /* glUniform4iv */
        2493, /* glUniformMatrix2fv */
        2500, /* glUniformMatrix3fv */
        2507, /* glUniformMatrix4fv */
        2525, /* glUseProgram */
        2540, /* glValidateProgram */
        2631, /* glVertexAttrib1f */
        2634, /* glVertexAttrib1fv */
        2651, /* glVertexAttrib2f */
        2654, /* glVertexAttrib2fv */
        2671, /* glVertexAttrib3f */
        2674, /* glVertexAttrib3fv */
        2707, /* glVertexAttrib4f */
        2710, /* glVertexAttrib4fv */
        2828, /* glVertexAttribPointer */
        2904  /* glViewport */
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
          36, /* glBeginQuery */
          39, /* glBeginTransformFeedback */
          48, /* glBindBufferBase */
          53, /* glBindBufferRange */
          76, /* glBindSampler */
          85, /* glBindTransformFeedback */
          87, /* glBindVertexArray */
         133, /* glBlitFramebuffer */
         164, /* glClearBufferfi */
         165, /* glClearBufferfv */
         166, /* glClearBufferiv */
         167, /* glClearBufferuiv */
         194, /* glClientWaitSync */
         294, /* glCompressedTexImage3D */
         300, /* glCompressedTexSubImage3D */
         327, /* glCopyBufferSubData */
         354, /* glCopyTexSubImage3D */
         430, /* glDeleteQueries */
         435, /* glDeleteSamplers */
         439, /* glDeleteSync */
         442, /* glDeleteTransformFeedbacks */
         444, /* glDeleteVertexArrays */
         482, /* glDrawArraysInstanced */
         487, /* glDrawBuffers */
         499, /* glDrawElementsInstanced */
         511, /* glDrawRangeElements */
         553, /* glEndQuery */
         556, /* glEndTransformFeedback */
         583, /* glFenceSync */
         592, /* glFlushMappedBufferRange */
         660, /* glFramebufferTextureLayer */
         685, /* glGenQueries */
         690, /* glGenSamplers */
         695, /* glGenTransformFeedbacks */
         697, /* glGenVertexArrays */
         713, /* glGetActiveUniformBlockName */
         714, /* glGetActiveUniformBlockiv */
         716, /* glGetActiveUniformsiv */
         727, /* glGetBufferParameteri64v */
         731, /* glGetBufferPointerv */
         787, /* glGetFragDataLocation */
         815, /* glGetInteger64i_v */
         816, /* glGetInteger64v */
         818, /* glGetIntegeri_v */
         824, /* glGetInternalformativ */
         940, /* glGetProgramBinary */
         981, /* glGetQueryObjectuiv */
         983, /* glGetQueryiv */
         989, /* glGetSamplerParameterfv */
         990, /* glGetSamplerParameteriv */
        1005, /* glGetStringi */
        1008, /* glGetSynciv */
        1051, /* glGetTransformFeedbackVarying */
        1057, /* glGetUniformBlockIndex */
        1059, /* glGetUniformIndices */
        1073, /* glGetUniformuiv */
        1093, /* glGetVertexAttribIiv */
        1095, /* glGetVertexAttribIuiv */
        1214, /* glInvalidateFramebuffer */
        1217, /* glInvalidateSubFramebuffer */
        1249, /* glIsQuery */
        1253, /* glIsSampler */
        1257, /* glIsSync */
        1262, /* glIsTransformFeedback */
        1265, /* glIsVertexArray */
        1330, /* glMapBufferRange */
        1682, /* glPauseTransformFeedback */
        1746, /* glProgramBinary */
        1780, /* glProgramParameteri */
        1972, /* glReadBuffer */
        1994, /* glRenderbufferStorageMultisample */
        2029, /* glResumeTransformFeedback */
        2045, /* glSamplerParameterf */
        2046, /* glSamplerParameterfv */
        2047, /* glSamplerParameteri */
        2048, /* glSamplerParameteriv */
        2286, /* glTexImage3D */
        2306, /* glTexStorage2D */
        2309, /* glTexStorage3D */
        2326, /* glTexSubImage3D */
        2391, /* glTransformFeedbackVaryings */
        2412, /* glUniform1ui */
        2418, /* glUniform1uiv */
        2434, /* glUniform2ui */
        2440, /* glUniform2uiv */
        2456, /* glUniform3ui */
        2462, /* glUniform3uiv */
        2478, /* glUniform4ui */
        2484, /* glUniform4uiv */
        2486, /* glUniformBlockBinding */
        2496, /* glUniformMatrix2x3fv */
        2498, /* glUniformMatrix2x4fv */
        2503, /* glUniformMatrix3x2fv */
        2505, /* glUniformMatrix3x4fv */
        2510, /* glUniformMatrix4x2fv */
        2512, /* glUniformMatrix4x3fv */
        2517, /* glUnmapBuffer */
        2733, /* glVertexAttribDivisor */
        2763, /* glVertexAttribI4i */
        2765, /* glVertexAttribI4iv */
        2771, /* glVertexAttribI4ui */
        2773, /* glVertexAttribI4uiv */
        2779, /* glVertexAttribIPointer */
        2912  /* glWaitSync */
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
           4, /* glActiveShaderProgram */
          64, /* glBindImageTexture */
          73, /* glBindProgramPipeline */
          89, /* glBindVertexBuffer */
         386, /* glCreateShaderProgramv */
         427, /* glDeleteProgramPipelines */
         476, /* glDispatchCompute */
         478, /* glDispatchComputeIndirect */
         481, /* glDrawArraysIndirect */
         498, /* glDrawElementsIndirect */
         641, /* glFramebufferParameteri */
         682, /* glGenProgramPipelines */
         725, /* glGetBooleani_v */
         796, /* glGetFramebufferParameteriv */
         868, /* glGetMultisamplefv */
         946, /* glGetProgramInterfaceiv */
         955, /* glGetProgramPipelineInfoLog */
         956, /* glGetProgramPipelineiv */
         957, /* glGetProgramResourceIndex */
         958, /* glGetProgramResourceLocation */
         960, /* glGetProgramResourceName */
         962, /* glGetProgramResourceiv */
        1020, /* glGetTexLevelParameterfv */
        1021, /* glGetTexLevelParameteriv */
        1248, /* glIsProgramPipeline */
        1388, /* glMemoryBarrier */
        1389, /* glMemoryBarrierByRegion */
        1792, /* glProgramUniform1f */
        1794, /* glProgramUniform1fv */
        1796, /* glProgramUniform1i */
        1802, /* glProgramUniform1iv */
        1804, /* glProgramUniform1ui */
        1810, /* glProgramUniform1uiv */
        1816, /* glProgramUniform2f */
        1818, /* glProgramUniform2fv */
        1820, /* glProgramUniform2i */
        1826, /* glProgramUniform2iv */
        1828, /* glProgramUniform2ui */
        1834, /* glProgramUniform2uiv */
        1840, /* glProgramUniform3f */
        1842, /* glProgramUniform3fv */
        1844, /* glProgramUniform3i */
        1850, /* glProgramUniform3iv */
        1852, /* glProgramUniform3ui */
        1858, /* glProgramUniform3uiv */
        1864, /* glProgramUniform4f */
        1866, /* glProgramUniform4fv */
        1868, /* glProgramUniform4i */
        1874, /* glProgramUniform4iv */
        1876, /* glProgramUniform4ui */
        1882, /* glProgramUniform4uiv */
        1890, /* glProgramUniformMatrix2fv */
        1894, /* glProgramUniformMatrix2x3fv */
        1898, /* glProgramUniformMatrix2x4fv */
        1902, /* glProgramUniformMatrix3fv */
        1906, /* glProgramUniformMatrix3x2fv */
        1910, /* glProgramUniformMatrix3x4fv */
        1914, /* glProgramUniformMatrix4fv */
        1918, /* glProgramUniformMatrix4x2fv */
        1922, /* glProgramUniformMatrix4x3fv */
        2040, /* glSampleMaski */
        2308, /* glTexStorage2DMultisample */
        2527, /* glUseProgramStages */
        2542, /* glValidateProgramPipeline */
        2732, /* glVertexAttribBinding */
        2735, /* glVertexAttribFormat */
        2777, /* glVertexAttribIFormat */
        2848  /* glVertexBindingDivisor */
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
        2991, /* glBlendBarrier */
         118, /* glBlendEquationSeparatei */
         120, /* glBlendEquationi */
         128, /* glBlendFuncSeparatei */
         130, /* glBlendFunci */
         253, /* glColorMaski */
         336, /* glCopyImageSubData */
         396, /* glDebugMessageCallback */
         399, /* glDebugMessageControl */
         402, /* glDebugMessageInsert */
         475, /* glDisablei */
         497, /* glDrawElementsBaseVertex */
         502, /* glDrawElementsInstancedBaseVertex */
         512, /* glDrawRangeElementsBaseVertex */
         543, /* glEnablei */
         649, /* glFramebufferTexture */
         767, /* glGetDebugMessageLog */
         799, /* glGetGraphicsResetStatus */
         896, /* glGetObjectLabel */
         901, /* glGetObjectPtrLabel */
         937, /* glGetPointerv */
         987, /* glGetSamplerParameterIiv */
         988, /* glGetSamplerParameterIuiv */
        1023, /* glGetTexParameterIiv */
        1025, /* glGetTexParameterIuiv */
        1153, /* glGetnUniformfv */
        1156, /* glGetnUniformiv */
        1159, /* glGetnUniformuiv */
        1228, /* glIsEnabledi */
        1392, /* glMinSampleShading */
        1647, /* glObjectLabel */
        1648, /* glObjectPtrLabel */
        1660, /* glPatchParameteri */
        1733, /* glPopDebugGroup */
        3238, /* glPrimitiveBoundingBox */
        1932, /* glPushDebugGroup */
        1975, /* glReadnPixels */
        2043, /* glSamplerParameterIiv */
        2044, /* glSamplerParameterIuiv */
        2177, /* glTexBuffer */
        2180, /* glTexBufferRange */
        2293, /* glTexParameterIiv */
        2295, /* glTexParameterIuiv */
        2311  /* glTexStorage3DMultisample */
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
        2170  /* glTbufferMask3DFX */
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
         397, /* glDebugMessageCallbackAMD */
         401, /* glDebugMessageEnableAMD */
         403, /* glDebugMessageInsertAMD */
         768  /* glGetDebugMessageLogAMD */
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
         114, /* glBlendEquationIndexedAMD */
         117, /* glBlendEquationSeparateIndexedAMD */
         123, /* glBlendFuncIndexedAMD */
         127  /* glBlendFuncSeparateIndexedAMD */
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
        1608, /* glNamedRenderbufferStorageMultisampleAdvancedAMD */
        1995  /* glRenderbufferStorageMultisampleAdvancedAMD */
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
         648, /* glFramebufferSamplePositionsfvAMD */
         795, /* glGetFramebufferParameterfvAMD */
         880, /* glGetNamedFramebufferParameterfvAMD */
        1584  /* glNamedFramebufferSamplePositionsfvAMD */
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
        1068, /* glGetUniformi64vNV */
        1072, /* glGetUniformui64vNV */
        1798, /* glProgramUniform1i64NV */
        1800, /* glProgramUniform1i64vNV */
        1806, /* glProgramUniform1ui64NV */
        1808, /* glProgramUniform1ui64vNV */
        1822, /* glProgramUniform2i64NV */
        1824, /* glProgramUniform2i64vNV */
        1830, /* glProgramUniform2ui64NV */
        1832, /* glProgramUniform2ui64vNV */
        1846, /* glProgramUniform3i64NV */
        1848, /* glProgramUniform3i64vNV */
        1854, /* glProgramUniform3ui64NV */
        1856, /* glProgramUniform3ui64vNV */
        1870, /* glProgramUniform4i64NV */
        1872, /* glProgramUniform4i64vNV */
        1878, /* glProgramUniform4ui64NV */
        1880, /* glProgramUniform4ui64vNV */
        2406, /* glUniform1i64NV */
        2408, /* glUniform1i64vNV */
        2414, /* glUniform1ui64NV */
        2416, /* glUniform1ui64vNV */
        2428, /* glUniform2i64NV */
        2430, /* glUniform2i64vNV */
        2436, /* glUniform2ui64NV */
        2438, /* glUniform2ui64vNV */
        2450, /* glUniform3i64NV */
        2452, /* glUniform3i64vNV */
        2458, /* glUniform3ui64NV */
        2460, /* glUniform3ui64vNV */
        2472, /* glUniform4i64NV */
        2474, /* glUniform4i64vNV */
        2480, /* glUniform4ui64NV */
        2482  /* glUniform4ui64vNV */
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
        2827  /* glVertexAttribParameteriAMD */
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
        1407, /* glMultiDrawArraysIndirectAMD */
        1417  /* glMultiDrawElementsIndirectAMD */
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
         420, /* glDeleteNamesAMD */
         678, /* glGenNamesAMD */
        1237  /* glIsNameAMD */
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
        1938  /* glQueryObjectParameteruiAMD */
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
          34, /* glBeginPerfMonitorAMD */
         424, /* glDeletePerfMonitorsAMD */
         551, /* glEndPerfMonitorAMD */
         681, /* glGenPerfMonitorsAMD */
         918, /* glGetPerfMonitorCounterDataAMD */
         919, /* glGetPerfMonitorCounterInfoAMD */
         920, /* glGetPerfMonitorCounterStringAMD */
         921, /* glGetPerfMonitorCountersAMD */
         922, /* glGetPerfMonitorGroupStringAMD */
         923, /* glGetPerfMonitorGroupsAMD */
        2099  /* glSelectPerfMonitorCountersAMD */
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
        2109  /* glSetMultisamplefvAMD */
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
        2321, /* glTexStorageSparseAMD */
        2378  /* glTextureStorageSparseAMD */
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
        2146  /* glStencilOpValueAMD */
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
        2171, /* glTessellationFactorAMD */
        2172  /* glTessellationModeAMD */
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
        3048, /* glDrawArraysInstancedBaseInstanceANGLE */
        3058, /* glDrawElementsInstancedBaseVertexBaseInstanceANGLE */
        3224, /* glMultiDrawArraysInstancedBaseInstanceANGLE */
        3229  /* glMultiDrawElementsInstancedBaseVertexBaseInstanceANGLE */
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
        3020, /* glCopySubTexture3DANGLE */
        3023  /* glCopyTexture3DANGLE */
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
        3000  /* glBlitFramebufferANGLE */
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
        3254  /* glRenderbufferStorageMultisampleANGLE */
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
        3120, /* glGetCompressedTexImageANGLE */
        3166, /* glGetRenderbufferImageANGLE */
        3178  /* glGetTexImageANGLE */
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
        3179, /* glGetTexLevelParameterfvANGLE */
        3181  /* glGetTexLevelParameterivANGLE */
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
        3047, /* glDrawArraysInstancedANGLE */
        3056, /* glDrawElementsInstancedANGLE */
        3315  /* glVertexAttribDivisorANGLE */
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
        3215  /* glLogicOpANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_logic_op) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_memory_object_flags(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        2317, /* glTexStorageMemFlags2DANGLE */
        2318, /* glTexStorageMemFlags2DMultisampleANGLE */
        2319, /* glTexStorageMemFlags3DANGLE */
        2320  /* glTexStorageMemFlags3DMultisampleANGLE */
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
        1181  /* glImportMemoryZirconHandleANGLE */
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
        3221, /* glMultiDrawArraysANGLE */
        3223, /* glMultiDrawArraysInstancedANGLE */
        3225, /* glMultiDrawElementsANGLE */
        3228  /* glMultiDrawElementsInstancedANGLE */
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
        3235  /* glPolygonModeANGLE */
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
        3244  /* glProvokingVertexANGLE */
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
        3042, /* glDisableExtensionANGLE */
        3258  /* glRequestExtensionANGLE */
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
        3011, /* glCompressedTexImage2DRobustANGLE */
        3013, /* glCompressedTexImage3DRobustANGLE */
        3014, /* glCompressedTexSubImage2DRobustANGLE */
        3016, /* glCompressedTexSubImage3DRobustANGLE */
        3113, /* glGetActiveUniformBlockivRobustANGLE */
        3114, /* glGetBooleani_vRobustANGLE */
        3115, /* glGetBooleanvRobustANGLE */
        3116, /* glGetBufferParameteri64vRobustANGLE */
        3117, /* glGetBufferParameterivRobustANGLE */
        3119, /* glGetBufferPointervRobustANGLE */
        3126, /* glGetFloatvRobustANGLE */
        3129, /* glGetFramebufferAttachmentParameterivRobustANGLE */
        3130, /* glGetFramebufferParameterivRobustANGLE */
        3138, /* glGetInteger64i_vRobustANGLE */
        3141, /* glGetInteger64vRobustANGLE */
        3143, /* glGetIntegeri_vRobustANGLE */
        3144, /* glGetIntegervRobustANGLE */
        3145, /* glGetInternalformativRobustANGLE */
        3147, /* glGetMultisamplefvRobustANGLE */
        3151, /* glGetPointervRobustANGLERobustANGLE */
        3153, /* glGetProgramInterfaceivRobustANGLE */
        3157, /* glGetProgramivRobustANGLE */
        3158, /* glGetQueryObjecti64vRobustANGLE */
        3160, /* glGetQueryObjectivRobustANGLE */
        3161, /* glGetQueryObjectui64vRobustANGLE */
        3163, /* glGetQueryObjectuivRobustANGLE */
        3165, /* glGetQueryivRobustANGLE */
        3167, /* glGetRenderbufferParameterivRobustANGLE */
        3170, /* glGetSamplerParameterIivRobustANGLE */
        3173, /* glGetSamplerParameterIuivRobustANGLE */
        3174, /* glGetSamplerParameterfvRobustANGLE */
        3175, /* glGetSamplerParameterivRobustANGLE */
        3176, /* glGetShaderivRobustANGLE */
        3180, /* glGetTexLevelParameterfvRobustANGLE */
        3182, /* glGetTexLevelParameterivRobustANGLE */
        3184, /* glGetTexParameterIivRobustANGLE */
        3186, /* glGetTexParameterIuivRobustANGLE */
        3187, /* glGetTexParameterfvRobustANGLE */
        3188, /* glGetTexParameterivRobustANGLE */
        3192, /* glGetUniformfvRobustANGLE */
        3193, /* glGetUniformivRobustANGLE */
        3194, /* glGetUniformuivRobustANGLE */
        3195, /* glGetVertexAttribIivRobustANGLE */
        3196, /* glGetVertexAttribIuivRobustANGLE */
        3197, /* glGetVertexAttribPointervRobustANGLE */
        3198, /* glGetVertexAttribfvRobustANGLE */
        3199, /* glGetVertexAttribivRobustANGLE */
        3202, /* glGetnUniformfvRobustANGLE */
        3205, /* glGetnUniformivRobustANGLE */
        3207, /* glGetnUniformuivRobustANGLE */
        3249, /* glReadPixelsRobustANGLE */
        3252, /* glReadnPixelsRobustANGLE */
        3263, /* glSamplerParameterIivRobustANGLE */
        3266, /* glSamplerParameterIuivRobustANGLE */
        3267, /* glSamplerParameterfvRobustANGLE */
        3268, /* glSamplerParameterivRobustANGLE */
        3284, /* glTexImage2DRobustANGLE */
        3286, /* glTexImage3DRobustANGLE */
        3289, /* glTexParameterIivRobustANGLE */
        3291, /* glTexParameterIuivRobustANGLE */
        3292, /* glTexParameterfvRobustANGLE */
        3293, /* glTexParameterivRobustANGLE */
        3298, /* glTexSubImage2DRobustANGLE */
        3300  /* glTexSubImage3DRobustANGLE */
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
        1185  /* glImportSemaphoreZirconHandleANGLE */
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
        2985, /* glBeginPixelLocalStorageANGLE */
        3073, /* glEndPixelLocalStorageANGLE */
        3094, /* glFramebufferMemorylessPixelLocalStorageANGLE */
        3095, /* glFramebufferPixelLocalClearValuefvANGLE */
        3096, /* glFramebufferPixelLocalClearValueivANGLE */
        3097, /* glFramebufferPixelLocalClearValueuivANGLE */
        3098, /* glFramebufferPixelLocalStorageInterruptANGLE */
        3099, /* glFramebufferPixelLocalStorageRestoreANGLE */
        3109, /* glFramebufferTexturePixelLocalStorageANGLE */
        3131, /* glGetFramebufferPixelLocalStorageParameterfvANGLE */
        3132, /* glGetFramebufferPixelLocalStorageParameterfvRobustANGLE */
        3133, /* glGetFramebufferPixelLocalStorageParameterivANGLE */
        3134, /* glGetFramebufferPixelLocalStorageParameterivRobustANGLE */
        3234  /* glPixelLocalStorageBarrierANGLE */
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
        1220, /* glInvalidateTextureANGLE */
        2283  /* glTexImage2DExternalANGLE */
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
        3146, /* glGetMultisamplefvANGLE */
        3179, /* glGetTexLevelParameterfvANGLE */
        3181, /* glGetTexLevelParameterivANGLE */
        3260, /* glSampleMaskiANGLE */
        3294  /* glTexStorage2DMultisampleANGLE */
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
        3191  /* glGetTranslatedShaderSourceANGLE */
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
        2982, /* glAcquireTexturesANGLE */
        3253  /* glReleaseTexturesANGLE */
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
        3025  /* glCopyTextureLevelsAPPLE */
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
         494, /* glDrawElementArrayAPPLE */
         509, /* glDrawRangeElementArrayAPPLE */
         529, /* glElementPointerAPPLE */
        1412, /* glMultiDrawElementArrayAPPLE */
        1424  /* glMultiDrawRangeElementArrayAPPLE */
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
         412, /* glDeleteFencesAPPLE */
         587, /* glFinishFenceAPPLE */
         589, /* glFinishObjectAPPLE */
         672, /* glGenFencesAPPLE */
        1229, /* glIsFenceAPPLE */
        2104, /* glSetFenceAPPLE */
        2173, /* glTestFenceAPPLE */
        2175  /* glTestObjectAPPLE */
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
         144, /* glBufferParameteriAPPLE */
         593  /* glFlushMappedBufferRangeAPPLE */
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
        3255, /* glRenderbufferStorageMultisampleAPPLE */
        3259  /* glResolveMultisampleFramebufferAPPLE */
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
         899, /* glGetObjectParameterivAPPLE */
        1649, /* glObjectPurgeableAPPLE */
        1650  /* glObjectUnpurgeableAPPLE */
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
        3006, /* glClientWaitSyncAPPLE */
        3035, /* glDeleteSyncAPPLE */
        3089, /* glFenceSyncAPPLE */
        3139, /* glGetInteger64vAPPLE */
        3177, /* glGetSyncivAPPLE */
        3213, /* glIsSyncAPPLE */
        3324  /* glWaitSyncAPPLE */
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
        1027, /* glGetTexParameterPointervAPPLE */
        2361  /* glTextureRangeAPPLE */
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
          88, /* glBindVertexArrayAPPLE */
         445, /* glDeleteVertexArraysAPPLE */
         698, /* glGenVertexArraysAPPLE */
        1266  /* glIsVertexArrayAPPLE */
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
         599, /* glFlushVertexArrayRangeAPPLE */
        2608, /* glVertexArrayParameteriAPPLE */
        2609  /* glVertexArrayRangeAPPLE */
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
         472, /* glDisableVertexAttribAPPLE */
         540, /* glEnableVertexAttribAPPLE */
        1267, /* glIsVertexAttribEnabledAPPLE */
        1346, /* glMapVertexAttrib1dAPPLE */
        1347, /* glMapVertexAttrib1fAPPLE */
        1348, /* glMapVertexAttrib2dAPPLE */
        1349  /* glMapVertexAttrib2fAPPLE */
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
         174, /* glClearDepthf */
         457, /* glDepthRangef */
         996, /* glGetShaderPrecisionFormat */
        1989, /* glReleaseShaderCompiler */
        2111  /* glShaderBinary */
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
        1389  /* glMemoryBarrierByRegion */
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
        1739  /* glPrimitiveBoundingBoxARB */
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
         484, /* glDrawArraysInstancedBaseInstance */
         501, /* glDrawElementsInstancedBaseInstance */
         503  /* glDrawElementsInstancedBaseVertexBaseInstance */
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
         809, /* glGetImageHandleARB */
        1031, /* glGetTextureHandleARB */
        1047, /* glGetTextureSamplerHandleARB */
        1100, /* glGetVertexAttribLui64vARB */
        1233, /* glIsImageHandleResidentARB */
        1260, /* glIsTextureHandleResidentARB */
        1312, /* glMakeImageHandleNonResidentARB */
        1314, /* glMakeImageHandleResidentARB */
        1318, /* glMakeTextureHandleNonResidentARB */
        1320, /* glMakeTextureHandleResidentARB */
        1884, /* glProgramUniformHandleui64ARB */
        1886, /* glProgramUniformHandleui64vARB */
        2488, /* glUniformHandleui64ARB */
        2490, /* glUniformHandleui64vARB */
        2787, /* glVertexAttribL1ui64ARB */
        2789  /* glVertexAttribL1ui64vARB */
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
          60, /* glBindFragDataLocationIndexed */
         786  /* glGetFragDataIndex */
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
         145  /* glBufferStorage */
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
         388  /* glCreateSyncFromCLeventARB */
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
         162, /* glClearBufferData */
         163  /* glClearBufferSubData */
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
         187, /* glClearTexImage */
         188  /* glClearTexSubImage */
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
         195  /* glClipControl */
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
         158  /* glClampColorARB */
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
         476, /* glDispatchCompute */
         478  /* glDispatchComputeIndirect */
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
         477  /* glDispatchComputeGroupSizeARB */
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
         327  /* glCopyBufferSubData */
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
         336  /* glCopyImageSubData */
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
         398, /* glDebugMessageCallbackARB */
         400, /* glDebugMessageControlARB */
         404, /* glDebugMessageInsertARB */
         769  /* glGetDebugMessageLogARB */
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
          82, /* glBindTextureUnit */
         137, /* glBlitNamedFramebuffer */
         155, /* glCheckNamedFramebufferStatus */
         178, /* glClearNamedBufferData */
         180, /* glClearNamedBufferSubData */
         182, /* glClearNamedFramebufferfi */
         183, /* glClearNamedFramebufferfv */
         184, /* glClearNamedFramebufferiv */
         185, /* glClearNamedFramebufferuiv */
         305, /* glCompressedTextureSubImage1D */
         307, /* glCompressedTextureSubImage2D */
         309, /* glCompressedTextureSubImage3D */
         343, /* glCopyNamedBufferSubData */
         358, /* glCopyTextureSubImage1D */
         360, /* glCopyTextureSubImage2D */
         362, /* glCopyTextureSubImage3D */
         370, /* glCreateBuffers */
         372, /* glCreateFramebuffers */
         377, /* glCreateProgramPipelines */
         379, /* glCreateQueries */
         380, /* glCreateRenderbuffers */
         381, /* glCreateSamplers */
         389, /* glCreateTextures */
         390, /* glCreateTransformFeedbacks */
         391, /* glCreateVertexArrays */
         469, /* glDisableVertexArrayAttrib */
         537, /* glEnableVertexArrayAttrib */
         594, /* glFlushMappedNamedBufferRange */
         703, /* glGenerateTextureMipmap */
         756, /* glGetCompressedTextureImage */
         870, /* glGetNamedBufferParameteri64v */
         871, /* glGetNamedBufferParameteriv */
         874, /* glGetNamedBufferPointerv */
         876, /* glGetNamedBufferSubData */
         878, /* glGetNamedFramebufferAttachmentParameteriv */
         881, /* glGetNamedFramebufferParameteriv */
         889, /* glGetNamedRenderbufferParameteriv */
         970, /* glGetQueryBufferObjecti64v */
         971, /* glGetQueryBufferObjectiv */
         972, /* glGetQueryBufferObjectui64v */
         973, /* glGetQueryBufferObjectuiv */
        1033, /* glGetTextureImage */
        1035, /* glGetTextureLevelParameterfv */
        1037, /* glGetTextureLevelParameteriv */
        1039, /* glGetTextureParameterIiv */
        1041, /* glGetTextureParameterIuiv */
        1043, /* glGetTextureParameterfv */
        1045, /* glGetTextureParameteriv */
        1054, /* glGetTransformFeedbacki64_v */
        1055, /* glGetTransformFeedbacki_v */
        1056, /* glGetTransformFeedbackiv */
        1084, /* glGetVertexArrayIndexed64iv */
        1085, /* glGetVertexArrayIndexediv */
        1090, /* glGetVertexArrayiv */
        1215, /* glInvalidateNamedFramebufferData */
        1216, /* glInvalidateNamedFramebufferSubData */
        1338, /* glMapNamedBuffer */
        1340, /* glMapNamedBufferRange */
        1563, /* glNamedBufferData */
        1568, /* glNamedBufferStorage */
        1572, /* glNamedBufferSubData */
        1575, /* glNamedFramebufferDrawBuffer */
        1576, /* glNamedFramebufferDrawBuffers */
        1577, /* glNamedFramebufferParameteri */
        1579, /* glNamedFramebufferReadBuffer */
        1580, /* glNamedFramebufferRenderbuffer */
        1585, /* glNamedFramebufferTexture */
        1591, /* glNamedFramebufferTextureLayer */
        1605, /* glNamedRenderbufferStorage */
        1607, /* glNamedRenderbufferStorageMultisample */
        2332, /* glTextureBuffer */
        2334, /* glTextureBufferRange */
        2349, /* glTextureParameterIiv */
        2351, /* glTextureParameterIuiv */
        2353, /* glTextureParameterf */
        2355, /* glTextureParameterfv */
        2357, /* glTextureParameteri */
        2359, /* glTextureParameteriv */
        2363, /* glTextureStorage1D */
        2365, /* glTextureStorage2D */
        2367, /* glTextureStorage2DMultisample */
        2369, /* glTextureStorage3D */
        2371, /* glTextureStorage3DMultisample */
        2379, /* glTextureSubImage1D */
        2381, /* glTextureSubImage2D */
        2383, /* glTextureSubImage3D */
        2388, /* glTransformFeedbackBufferBase */
        2389, /* glTransformFeedbackBufferRange */
        2519, /* glUnmapNamedBuffer */
        2595, /* glVertexArrayAttribBinding */
        2596, /* glVertexArrayAttribFormat */
        2597, /* glVertexArrayAttribIFormat */
        2598, /* glVertexArrayAttribLFormat */
        2600, /* glVertexArrayBindingDivisor */
        2603, /* glVertexArrayElementBuffer */
        2622, /* glVertexArrayVertexBuffer */
        2623  /* glVertexArrayVertexBuffers */
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
         488  /* glDrawBuffersARB */
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
         119, /* glBlendEquationSeparateiARB */
         121, /* glBlendEquationiARB */
         129, /* glBlendFuncSeparateiARB */
         131  /* glBlendFunciARB */
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
         497, /* glDrawElementsBaseVertex */
         502, /* glDrawElementsInstancedBaseVertex */
         512, /* glDrawRangeElementsBaseVertex */
        1414  /* glMultiDrawElementsBaseVertex */
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
         481, /* glDrawArraysIndirect */
         498  /* glDrawElementsIndirect */
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
         483, /* glDrawArraysInstancedARB */
         500  /* glDrawElementsInstancedARB */
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
          71, /* glBindProgramARB */
         428, /* glDeleteProgramsARB */
         683, /* glGenProgramsARB */
         943, /* glGetProgramEnvParameterdvARB */
         944, /* glGetProgramEnvParameterfvARB */
         949, /* glGetProgramLocalParameterdvARB */
         950, /* glGetProgramLocalParameterfvARB */
         964, /* glGetProgramStringARB */
         968, /* glGetProgramivARB */
        1246, /* glIsProgramARB */
        1750, /* glProgramEnvParameter4dARB */
        1751, /* glProgramEnvParameter4dvARB */
        1752, /* glProgramEnvParameter4fARB */
        1753, /* glProgramEnvParameter4fvARB */
        1761, /* glProgramLocalParameter4dARB */
        1762, /* glProgramLocalParameter4dvARB */
        1763, /* glProgramLocalParameter4fARB */
        1764, /* glProgramLocalParameter4fvARB */
        1786  /* glProgramStringARB */
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
         641, /* glFramebufferParameteri */
         796  /* glGetFramebufferParameteriv */
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
          62, /* glBindFramebuffer */
          74, /* glBindRenderbuffer */
         133, /* glBlitFramebuffer */
         153, /* glCheckFramebufferStatus */
         415, /* glDeleteFramebuffers */
         433, /* glDeleteRenderbuffers */
         644, /* glFramebufferRenderbuffer */
         650, /* glFramebufferTexture1D */
         652, /* glFramebufferTexture2D */
         654, /* glFramebufferTexture3D */
         660, /* glFramebufferTextureLayer */
         675, /* glGenFramebuffers */
         688, /* glGenRenderbuffers */
         700, /* glGenerateMipmap */
         793, /* glGetFramebufferAttachmentParameteriv */
         985, /* glGetRenderbufferParameteriv */
        1231, /* glIsFramebuffer */
        1251, /* glIsRenderbuffer */
        1992, /* glRenderbufferStorage */
        1994  /* glRenderbufferStorageMultisample */
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
         656, /* glFramebufferTextureARB */
         658, /* glFramebufferTextureFaceARB */
         661, /* glFramebufferTextureLayerARB */
        1781  /* glProgramParameteriARB */
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
         940, /* glGetProgramBinary */
        1746, /* glProgramBinary */
        1780  /* glProgramParameteri */
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
         758, /* glGetCompressedTextureSubImage */
        1049  /* glGetTextureSubImage */
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
        2128  /* glSpecializeShaderARB */
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
        1064, /* glGetUniformdv */
        2398, /* glUniform1d */
        2399, /* glUniform1dv */
        2420, /* glUniform2d */
        2421, /* glUniform2dv */
        2442, /* glUniform3d */
        2443, /* glUniform3dv */
        2464, /* glUniform4d */
        2465, /* glUniform4dv */
        2492, /* glUniformMatrix2dv */
        2495, /* glUniformMatrix2x3dv */
        2497, /* glUniformMatrix2x4dv */
        2499, /* glUniformMatrix3dv */
        2502, /* glUniformMatrix3x2dv */
        2504, /* glUniformMatrix3x4dv */
        2506, /* glUniformMatrix4dv */
        2509, /* glUniformMatrix4x2dv */
        2511  /* glUniformMatrix4x3dv */
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
        1067, /* glGetUniformi64vARB */
        1071, /* glGetUniformui64vARB */
        1155, /* glGetnUniformi64vARB */
        1158, /* glGetnUniformui64vARB */
        1797, /* glProgramUniform1i64ARB */
        1799, /* glProgramUniform1i64vARB */
        1805, /* glProgramUniform1ui64ARB */
        1807, /* glProgramUniform1ui64vARB */
        1821, /* glProgramUniform2i64ARB */
        1823, /* glProgramUniform2i64vARB */
        1829, /* glProgramUniform2ui64ARB */
        1831, /* glProgramUniform2ui64vARB */
        1845, /* glProgramUniform3i64ARB */
        1847, /* glProgramUniform3i64vARB */
        1853, /* glProgramUniform3ui64ARB */
        1855, /* glProgramUniform3ui64vARB */
        1869, /* glProgramUniform4i64ARB */
        1871, /* glProgramUniform4i64vARB */
        1877, /* glProgramUniform4ui64ARB */
        1879, /* glProgramUniform4ui64vARB */
        2405, /* glUniform1i64ARB */
        2407, /* glUniform1i64vARB */
        2413, /* glUniform1ui64ARB */
        2415, /* glUniform1ui64vARB */
        2427, /* glUniform2i64ARB */
        2429, /* glUniform2i64vARB */
        2435, /* glUniform2ui64ARB */
        2437, /* glUniform2ui64vARB */
        2449, /* glUniform3i64ARB */
        2451, /* glUniform3i64vARB */
        2457, /* glUniform3ui64ARB */
        2459, /* glUniform3ui64vARB */
        2471, /* glUniform4i64ARB */
        2473, /* glUniform4i64vARB */
        2479, /* glUniform4ui64ARB */
        2481  /* glUniform4ui64vARB */
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
         109, /* glBlendColor */
         112, /* glBlendEquation */
         263, /* glColorSubTable */
         265, /* glColorTable */
         267, /* glColorTableParameterfv */
         269, /* glColorTableParameteriv */
         313, /* glConvolutionFilter1D */
         315, /* glConvolutionFilter2D */
         317, /* glConvolutionParameterf */
         319, /* glConvolutionParameterfv */
         321, /* glConvolutionParameteri */
         323, /* glConvolutionParameteriv */
         328, /* glCopyColorSubTable */
         330, /* glCopyColorTable */
         332, /* glCopyConvolutionFilter1D */
         334, /* glCopyConvolutionFilter2D */
         738, /* glGetColorTable */
         740, /* glGetColorTableParameterfv */
         743, /* glGetColorTableParameteriv */
         759, /* glGetConvolutionFilter */
         761, /* glGetConvolutionParameterfv */
         763, /* glGetConvolutionParameteriv */
         802, /* glGetHistogram */
         804, /* glGetHistogramParameterfv */
         806, /* glGetHistogramParameteriv */
         850, /* glGetMinmax */
         852, /* glGetMinmaxParameterfv */
         854, /* glGetMinmaxParameteriv */
         993, /* glGetSeparableFilter */
        1171, /* glHistogram */
        1394, /* glMinmax */
        2022, /* glResetHistogram */
        2025, /* glResetMinmax */
        2102  /* glSeparableFilter2D */
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
        1411, /* glMultiDrawArraysIndirectCountARB */
        1421  /* glMultiDrawElementsIndirectCountARB */
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
        2734  /* glVertexAttribDivisorARB */
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
         824  /* glGetInternalformativ */
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
         823  /* glGetInternalformati64v */
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
        1212, /* glInvalidateBufferData */
        1213, /* glInvalidateBufferSubData */
        1214, /* glInvalidateFramebuffer */
        1217, /* glInvalidateSubFramebuffer */
        1218, /* glInvalidateTexImage */
        1219  /* glInvalidateTexSubImage */
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
         592, /* glFlushMappedBufferRange */
        1330  /* glMapBufferRange */
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
         395, /* glCurrentPaletteMatrixARB */
        1357, /* glMatrixIndexPointerARB */
        1358, /* glMatrixIndexubvARB */
        1359, /* glMatrixIndexuivARB */
        1360  /* glMatrixIndexusvARB */
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
          56, /* glBindBuffersBase */
          57, /* glBindBuffersRange */
          66, /* glBindImageTextures */
          77, /* glBindSamplers */
          84, /* glBindTextures */
          90  /* glBindVertexBuffers */
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
        1406, /* glMultiDrawArraysIndirect */
        1416  /* glMultiDrawElementsIndirect */
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
        2035  /* glSampleCoverageARB */
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
           7, /* glActiveTextureARB */
         190, /* glClientActiveTextureARB */
        1431, /* glMultiTexCoord1dARB */
        1433, /* glMultiTexCoord1dvARB */
        1435, /* glMultiTexCoord1fARB */
        1437, /* glMultiTexCoord1fvARB */
        1441, /* glMultiTexCoord1iARB */
        1443, /* glMultiTexCoord1ivARB */
        1445, /* glMultiTexCoord1sARB */
        1447, /* glMultiTexCoord1svARB */
        1453, /* glMultiTexCoord2dARB */
        1455, /* glMultiTexCoord2dvARB */
        1457, /* glMultiTexCoord2fARB */
        1459, /* glMultiTexCoord2fvARB */
        1463, /* glMultiTexCoord2iARB */
        1465, /* glMultiTexCoord2ivARB */
        1467, /* glMultiTexCoord2sARB */
        1469, /* glMultiTexCoord2svARB */
        1475, /* glMultiTexCoord3dARB */
        1477, /* glMultiTexCoord3dvARB */
        1479, /* glMultiTexCoord3fARB */
        1481, /* glMultiTexCoord3fvARB */
        1485, /* glMultiTexCoord3iARB */
        1487, /* glMultiTexCoord3ivARB */
        1489, /* glMultiTexCoord3sARB */
        1491, /* glMultiTexCoord3svARB */
        1497, /* glMultiTexCoord4dARB */
        1499, /* glMultiTexCoord4dvARB */
        1501, /* glMultiTexCoord4fARB */
        1503, /* glMultiTexCoord4fvARB */
        1507, /* glMultiTexCoord4iARB */
        1509, /* glMultiTexCoord4ivARB */
        1511, /* glMultiTexCoord4sARB */
        1513  /* glMultiTexCoord4svARB */
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
          37, /* glBeginQueryARB */
         431, /* glDeleteQueriesARB */
         554, /* glEndQueryARB */
         686, /* glGenQueriesARB */
         978, /* glGetQueryObjectivARB */
         982, /* glGetQueryObjectuivARB */
         984, /* glGetQueryivARB */
        1250  /* glIsQueryARB */
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
        1386  /* glMaxShaderCompilerThreadsARB */
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
        1708, /* glPointParameterfARB */
        1712  /* glPointParameterfvARB */
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
        1726  /* glPolygonOffsetClamp */
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
         946, /* glGetProgramInterfaceiv */
         957, /* glGetProgramResourceIndex */
         958, /* glGetProgramResourceLocation */
         959, /* glGetProgramResourceLocationIndex */
         960, /* glGetProgramResourceName */
         962  /* glGetProgramResourceiv */
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
        1927  /* glProvokingVertex */
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
         800, /* glGetGraphicsResetStatusARB */
        1124, /* glGetnColorTableARB */
        1126, /* glGetnCompressedTexImageARB */
        1128, /* glGetnConvolutionFilterARB */
        1130, /* glGetnHistogramARB */
        1132, /* glGetnMapdvARB */
        1134, /* glGetnMapfvARB */
        1136, /* glGetnMapivARB */
        1138, /* glGetnMinmaxARB */
        1140, /* glGetnPixelMapfvARB */
        1142, /* glGetnPixelMapuivARB */
        1144, /* glGetnPixelMapusvARB */
        1146, /* glGetnPolygonStippleARB */
        1148, /* glGetnSeparableFilterARB */
        1150, /* glGetnTexImageARB */
        1152, /* glGetnUniformdvARB */
        1154, /* glGetnUniformfvARB */
        1157, /* glGetnUniformivARB */
        1160, /* glGetnUniformuivARB */
        1976  /* glReadnPixelsARB */
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
         578, /* glEvaluateDepthValuesARB */
         646, /* glFramebufferSampleLocationsfvARB */
        1582  /* glNamedFramebufferSampleLocationsfvARB */
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
        1393  /* glMinSampleShadingARB */
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
          76, /* glBindSampler */
         435, /* glDeleteSamplers */
         690, /* glGenSamplers */
         987, /* glGetSamplerParameterIiv */
         988, /* glGetSamplerParameterIuiv */
         989, /* glGetSamplerParameterfv */
         990, /* glGetSamplerParameteriv */
        1253, /* glIsSampler */
        2043, /* glSamplerParameterIiv */
        2044, /* glSamplerParameterIuiv */
        2045, /* glSamplerParameterf */
        2046, /* glSamplerParameterfv */
        2047, /* glSamplerParameteri */
        2048  /* glSamplerParameteriv */
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
           4, /* glActiveShaderProgram */
          73, /* glBindProgramPipeline */
         386, /* glCreateShaderProgramv */
         427, /* glDeleteProgramPipelines */
         682, /* glGenProgramPipelines */
         955, /* glGetProgramPipelineInfoLog */
         956, /* glGetProgramPipelineiv */
        1248, /* glIsProgramPipeline */
        1780, /* glProgramParameteri */
        1788, /* glProgramUniform1d */
        1790, /* glProgramUniform1dv */
        1792, /* glProgramUniform1f */
        1794, /* glProgramUniform1fv */
        1796, /* glProgramUniform1i */
        1802, /* glProgramUniform1iv */
        1804, /* glProgramUniform1ui */
        1810, /* glProgramUniform1uiv */
        1812, /* glProgramUniform2d */
        1814, /* glProgramUniform2dv */
        1816, /* glProgramUniform2f */
        1818, /* glProgramUniform2fv */
        1820, /* glProgramUniform2i */
        1826, /* glProgramUniform2iv */
        1828, /* glProgramUniform2ui */
        1834, /* glProgramUniform2uiv */
        1836, /* glProgramUniform3d */
        1838, /* glProgramUniform3dv */
        1840, /* glProgramUniform3f */
        1842, /* glProgramUniform3fv */
        1844, /* glProgramUniform3i */
        1850, /* glProgramUniform3iv */
        1852, /* glProgramUniform3ui */
        1858, /* glProgramUniform3uiv */
        1860, /* glProgramUniform4d */
        1862, /* glProgramUniform4dv */
        1864, /* glProgramUniform4f */
        1866, /* glProgramUniform4fv */
        1868, /* glProgramUniform4i */
        1874, /* glProgramUniform4iv */
        1876, /* glProgramUniform4ui */
        1882, /* glProgramUniform4uiv */
        1888, /* glProgramUniformMatrix2dv */
        1890, /* glProgramUniformMatrix2fv */
        1892, /* glProgramUniformMatrix2x3dv */
        1894, /* glProgramUniformMatrix2x3fv */
        1896, /* glProgramUniformMatrix2x4dv */
        1898, /* glProgramUniformMatrix2x4fv */
        1900, /* glProgramUniformMatrix3dv */
        1902, /* glProgramUniformMatrix3fv */
        1904, /* glProgramUniformMatrix3x2dv */
        1906, /* glProgramUniformMatrix3x2fv */
        1908, /* glProgramUniformMatrix3x4dv */
        1910, /* glProgramUniformMatrix3x4fv */
        1912, /* glProgramUniformMatrix4dv */
        1914, /* glProgramUniformMatrix4fv */
        1916, /* glProgramUniformMatrix4x2dv */
        1918, /* glProgramUniformMatrix4x2fv */
        1920, /* glProgramUniformMatrix4x3dv */
        1922, /* glProgramUniformMatrix4x3fv */
        2527, /* glUseProgramStages */
        2542  /* glValidateProgramPipeline */
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
         705  /* glGetActiveAtomicCounterBufferiv */
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
          64, /* glBindImageTexture */
        1388  /* glMemoryBarrier */
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
          26, /* glAttachObjectARB */
         282, /* glCompileShaderARB */
         376, /* glCreateProgramObjectARB */
         384, /* glCreateShaderObjectARB */
         421, /* glDeleteObjectARB */
         460, /* glDetachObjectARB */
         712, /* glGetActiveUniformARB */
         720, /* glGetAttachedObjectsARB */
         801, /* glGetHandleARB */
         813, /* glGetInfoLogARB */
         898, /* glGetObjectParameterfvARB */
         900, /* glGetObjectParameterivARB */
         998, /* glGetShaderSourceARB */
        1061, /* glGetUniformLocationARB */
        1066, /* glGetUniformfvARB */
        1070, /* glGetUniformivARB */
        1289, /* glLinkProgramARB */
        2116, /* glShaderSourceARB */
        2401, /* glUniform1fARB */
        2403, /* glUniform1fvARB */
        2409, /* glUniform1iARB */
        2411, /* glUniform1ivARB */
        2423, /* glUniform2fARB */
        2425, /* glUniform2fvARB */
        2431, /* glUniform2iARB */
        2433, /* glUniform2ivARB */
        2445, /* glUniform3fARB */
        2447, /* glUniform3fvARB */
        2453, /* glUniform3iARB */
        2455, /* glUniform3ivARB */
        2467, /* glUniform4fARB */
        2469, /* glUniform4fvARB */
        2475, /* glUniform4iARB */
        2477, /* glUniform4ivARB */
        2494, /* glUniformMatrix2fvARB */
        2501, /* glUniformMatrix3fvARB */
        2508, /* glUniformMatrix4fvARB */
        2526, /* glUseProgramObjectARB */
        2541  /* glValidateProgramARB */
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
        2117  /* glShaderStorageBlockBinding */
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
         708, /* glGetActiveSubroutineName */
         709, /* glGetActiveSubroutineUniformName */
         710, /* glGetActiveSubroutineUniformiv */
         963, /* glGetProgramStageiv */
        1006, /* glGetSubroutineIndex */
        1007, /* glGetSubroutineUniformLocation */
        1063, /* glGetUniformSubroutineuiv */
        2513  /* glUniformSubroutinesuiv */
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
         283, /* glCompileShaderIncludeARB */
         419, /* glDeleteNamedStringARB */
         891, /* glGetNamedStringARB */
         892, /* glGetNamedStringivARB */
        1239, /* glIsNamedStringARB */
        1611  /* glNamedStringARB */
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
         142, /* glBufferPageCommitmentARB */
        1565, /* glNamedBufferPageCommitmentARB */
        1566  /* glNamedBufferPageCommitmentEXT */
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
        2291  /* glTexPageCommitmentARB */
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
         194, /* glClientWaitSync */
         439, /* glDeleteSync */
         583, /* glFenceSync */
         816, /* glGetInteger64v */
        1008, /* glGetSynciv */
        1257, /* glIsSync */
        2912  /* glWaitSync */
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
        1659, /* glPatchParameterfv */
        1660  /* glPatchParameteri */
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
        2330  /* glTextureBarrier */
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
        2178  /* glTexBufferARB */
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
        2180  /* glTexBufferRange */
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
         291, /* glCompressedTexImage1DARB */
         293, /* glCompressedTexImage2DARB */
         295, /* glCompressedTexImage3DARB */
         297, /* glCompressedTexSubImage1DARB */
         299, /* glCompressedTexSubImage2DARB */
         301, /* glCompressedTexSubImage3DARB */
         755  /* glGetCompressedTexImageARB */
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
         868, /* glGetMultisamplefv */
        2040, /* glSampleMaski */
        2284, /* glTexImage2DMultisample */
        2288  /* glTexImage3DMultisample */
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
        2304, /* glTexStorage1D */
        2306, /* glTexStorage2D */
        2309  /* glTexStorage3D */
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
        2308, /* glTexStorage2DMultisample */
        2311  /* glTexStorage3DMultisample */
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
        2385  /* glTextureView */
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
         975, /* glGetQueryObjecti64v */
         979, /* glGetQueryObjectui64v */
        1936  /* glQueryCounter */
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
          85, /* glBindTransformFeedback */
         442, /* glDeleteTransformFeedbacks */
         515, /* glDrawTransformFeedback */
         695, /* glGenTransformFeedbacks */
        1262, /* glIsTransformFeedback */
        1682, /* glPauseTransformFeedback */
        2029  /* glResumeTransformFeedback */
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
          38, /* glBeginQueryIndexed */
         518, /* glDrawTransformFeedbackStream */
         555, /* glEndQueryIndexed */
         974  /* glGetQueryIndexediv */
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
         516, /* glDrawTransformFeedbackInstanced */
         519  /* glDrawTransformFeedbackStreamInstanced */
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
        1304, /* glLoadTransposeMatrixdARB */
        1306, /* glLoadTransposeMatrixfARB */
        1400, /* glMultTransposeMatrixdARB */
        1402  /* glMultTransposeMatrixfARB */
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
          48, /* glBindBufferBase */
          53, /* glBindBufferRange */
         713, /* glGetActiveUniformBlockName */
         714, /* glGetActiveUniformBlockiv */
         715, /* glGetActiveUniformName */
         716, /* glGetActiveUniformsiv */
         818, /* glGetIntegeri_v */
        1057, /* glGetUniformBlockIndex */
        1059, /* glGetUniformIndices */
        2486  /* glUniformBlockBinding */
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
          87, /* glBindVertexArray */
         444, /* glDeleteVertexArrays */
         697, /* glGenVertexArrays */
        1265  /* glIsVertexArray */
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
        1097, /* glGetVertexAttribLdv */
        2781, /* glVertexAttribL1d */
        2783, /* glVertexAttribL1dv */
        2791, /* glVertexAttribL2d */
        2793, /* glVertexAttribL2dv */
        2799, /* glVertexAttribL3d */
        2801, /* glVertexAttribL3dv */
        2807, /* glVertexAttribL4d */
        2809, /* glVertexAttribL4dv */
        2817  /* glVertexAttribLPointer */
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
          89, /* glBindVertexBuffer */
        2732, /* glVertexAttribBinding */
        2735, /* glVertexAttribFormat */
        2777, /* glVertexAttribIFormat */
        2815, /* glVertexAttribLFormat */
        2848  /* glVertexBindingDivisor */
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
        2849, /* glVertexBlendARB */
        2915, /* glWeightPointerARB */
        2916, /* glWeightbvARB */
        2917, /* glWeightdvARB */
        2918, /* glWeightfvARB */
        2919, /* glWeightivARB */
        2920, /* glWeightsvARB */
        2921, /* glWeightubvARB */
        2922, /* glWeightuivARB */
        2923  /* glWeightusvARB */
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
          47, /* glBindBufferARB */
         141, /* glBufferDataARB */
         149, /* glBufferSubDataARB */
         410, /* glDeleteBuffersARB */
         671, /* glGenBuffersARB */
         729, /* glGetBufferParameterivARB */
         732, /* glGetBufferPointervARB */
         734, /* glGetBufferSubDataARB */
        1223, /* glIsBufferARB */
        1329, /* glMapBufferARB */
        2518  /* glUnmapBufferARB */
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
          71, /* glBindProgramARB */
         428, /* glDeleteProgramsARB */
         474, /* glDisableVertexAttribArrayARB */
         542, /* glEnableVertexAttribArrayARB */
         683, /* glGenProgramsARB */
         943, /* glGetProgramEnvParameterdvARB */
         944, /* glGetProgramEnvParameterfvARB */
         949, /* glGetProgramLocalParameterdvARB */
         950, /* glGetProgramLocalParameterfvARB */
         964, /* glGetProgramStringARB */
         968, /* glGetProgramivARB */
        1103, /* glGetVertexAttribPointervARB */
        1106, /* glGetVertexAttribdvARB */
        1109, /* glGetVertexAttribfvARB */
        1112, /* glGetVertexAttribivARB */
        1246, /* glIsProgramARB */
        1750, /* glProgramEnvParameter4dARB */
        1751, /* glProgramEnvParameter4dvARB */
        1752, /* glProgramEnvParameter4fARB */
        1753, /* glProgramEnvParameter4fvARB */
        1761, /* glProgramLocalParameter4dARB */
        1762, /* glProgramLocalParameter4dvARB */
        1763, /* glProgramLocalParameter4fARB */
        1764, /* glProgramLocalParameter4fvARB */
        1786, /* glProgramStringARB */
        2626, /* glVertexAttrib1dARB */
        2629, /* glVertexAttrib1dvARB */
        2632, /* glVertexAttrib1fARB */
        2635, /* glVertexAttrib1fvARB */
        2640, /* glVertexAttrib1sARB */
        2643, /* glVertexAttrib1svARB */
        2646, /* glVertexAttrib2dARB */
        2649, /* glVertexAttrib2dvARB */
        2652, /* glVertexAttrib2fARB */
        2655, /* glVertexAttrib2fvARB */
        2660, /* glVertexAttrib2sARB */
        2663, /* glVertexAttrib2svARB */
        2666, /* glVertexAttrib3dARB */
        2669, /* glVertexAttrib3dvARB */
        2672, /* glVertexAttrib3fARB */
        2675, /* glVertexAttrib3fvARB */
        2680, /* glVertexAttrib3sARB */
        2683, /* glVertexAttrib3svARB */
        2686, /* glVertexAttrib4NbvARB */
        2688, /* glVertexAttrib4NivARB */
        2690, /* glVertexAttrib4NsvARB */
        2692, /* glVertexAttrib4NubARB */
        2694, /* glVertexAttrib4NubvARB */
        2696, /* glVertexAttrib4NuivARB */
        2698, /* glVertexAttrib4NusvARB */
        2700, /* glVertexAttrib4bvARB */
        2702, /* glVertexAttrib4dARB */
        2705, /* glVertexAttrib4dvARB */
        2708, /* glVertexAttrib4fARB */
        2711, /* glVertexAttrib4fvARB */
        2716, /* glVertexAttrib4ivARB */
        2718, /* glVertexAttrib4sARB */
        2721, /* glVertexAttrib4svARB */
        2725, /* glVertexAttrib4ubvARB */
        2728, /* glVertexAttrib4uivARB */
        2730, /* glVertexAttrib4usvARB */
        2829  /* glVertexAttribPointerARB */
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
          45, /* glBindAttribLocationARB */
         474, /* glDisableVertexAttribArrayARB */
         542, /* glEnableVertexAttribArrayARB */
         707, /* glGetActiveAttribARB */
         723, /* glGetAttribLocationARB */
        1103, /* glGetVertexAttribPointervARB */
        1106, /* glGetVertexAttribdvARB */
        1109, /* glGetVertexAttribfvARB */
        1112, /* glGetVertexAttribivARB */
        2626, /* glVertexAttrib1dARB */
        2629, /* glVertexAttrib1dvARB */
        2632, /* glVertexAttrib1fARB */
        2635, /* glVertexAttrib1fvARB */
        2640, /* glVertexAttrib1sARB */
        2643, /* glVertexAttrib1svARB */
        2646, /* glVertexAttrib2dARB */
        2649, /* glVertexAttrib2dvARB */
        2652, /* glVertexAttrib2fARB */
        2655, /* glVertexAttrib2fvARB */
        2660, /* glVertexAttrib2sARB */
        2663, /* glVertexAttrib2svARB */
        2666, /* glVertexAttrib3dARB */
        2669, /* glVertexAttrib3dvARB */
        2672, /* glVertexAttrib3fARB */
        2675, /* glVertexAttrib3fvARB */
        2680, /* glVertexAttrib3sARB */
        2683, /* glVertexAttrib3svARB */
        2686, /* glVertexAttrib4NbvARB */
        2688, /* glVertexAttrib4NivARB */
        2690, /* glVertexAttrib4NsvARB */
        2692, /* glVertexAttrib4NubARB */
        2694, /* glVertexAttrib4NubvARB */
        2696, /* glVertexAttrib4NuivARB */
        2698, /* glVertexAttrib4NusvARB */
        2700, /* glVertexAttrib4bvARB */
        2702, /* glVertexAttrib4dARB */
        2705, /* glVertexAttrib4dvARB */
        2708, /* glVertexAttrib4fARB */
        2711, /* glVertexAttrib4fvARB */
        2716, /* glVertexAttrib4ivARB */
        2718, /* glVertexAttrib4sARB */
        2721, /* glVertexAttrib4svARB */
        2725, /* glVertexAttrib4ubvARB */
        2728, /* glVertexAttrib4uivARB */
        2730, /* glVertexAttrib4usvARB */
        2829  /* glVertexAttribPointerARB */
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
         255, /* glColorP3ui */
         256, /* glColorP3uiv */
         257, /* glColorP4ui */
         258, /* glColorP4uiv */
        1516, /* glMultiTexCoordP1ui */
        1517, /* glMultiTexCoordP1uiv */
        1518, /* glMultiTexCoordP2ui */
        1519, /* glMultiTexCoordP2uiv */
        1520, /* glMultiTexCoordP3ui */
        1521, /* glMultiTexCoordP3uiv */
        1522, /* glMultiTexCoordP4ui */
        1523, /* glMultiTexCoordP4uiv */
        1631, /* glNormalP3ui */
        1632, /* glNormalP3uiv */
        2093, /* glSecondaryColorP3ui */
        2094, /* glSecondaryColorP3uiv */
        2254, /* glTexCoordP1ui */
        2255, /* glTexCoordP1uiv */
        2256, /* glTexCoordP2ui */
        2257, /* glTexCoordP2uiv */
        2258, /* glTexCoordP3ui */
        2259, /* glTexCoordP3uiv */
        2260, /* glTexCoordP4ui */
        2261, /* glTexCoordP4uiv */
        2819, /* glVertexAttribP1ui */
        2820, /* glVertexAttribP1uiv */
        2821, /* glVertexAttribP2ui */
        2822, /* glVertexAttribP2uiv */
        2823, /* glVertexAttribP3ui */
        2824, /* glVertexAttribP3uiv */
        2825, /* glVertexAttribP4ui */
        2826, /* glVertexAttribP4uiv */
        2853, /* glVertexP2ui */
        2854, /* glVertexP2uiv */
        2855, /* glVertexP3ui */
        2856, /* glVertexP3uiv */
        2857, /* glVertexP4ui */
        2858  /* glVertexP4uiv */
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
         452, /* glDepthRangeArraydvNV */
         453, /* glDepthRangeArrayv */
         454, /* glDepthRangeIndexed */
         455, /* glDepthRangeIndexeddNV */
         772, /* glGetDoublei_v */
         782, /* glGetFloati_v */
        2053, /* glScissorArrayv */
        2056, /* glScissorIndexed */
        2057, /* glScissorIndexedv */
        2905, /* glViewportArrayv */
        2906, /* glViewportIndexedf */
        2907  /* glViewportIndexedfv */
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
        2925, /* glWindowPos2dARB */
        2928, /* glWindowPos2dvARB */
        2931, /* glWindowPos2fARB */
        2934, /* glWindowPos2fvARB */
        2937, /* glWindowPos2iARB */
        2940, /* glWindowPos2ivARB */
        2943, /* glWindowPos2sARB */
        2946, /* glWindowPos2svARB */
        2949, /* glWindowPos3dARB */
        2952, /* glWindowPos3dvARB */
        2955, /* glWindowPos3fARB */
        2958, /* glWindowPos3fvARB */
        2961, /* glWindowPos3iARB */
        2964, /* glWindowPos3ivARB */
        2967, /* glWindowPos3sARB */
        2970  /* glWindowPos3svARB */
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
        3219  /* glMaxActiveShaderCoresARM */
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
         489  /* glDrawBuffersATI */
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
         495, /* glDrawElementArrayATI */
         510, /* glDrawRangeElementArrayATI */
         530  /* glElementPointerATI */
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
        1009, /* glGetTexBumpParameterfvATI */
        1010, /* glGetTexBumpParameterivATI */
        2181, /* glTexBumpParameterfvATI */
        2182  /* glTexBumpParameterivATI */
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
           9, /* glAlphaFragmentOp1ATI */
          10, /* glAlphaFragmentOp2ATI */
          11, /* glAlphaFragmentOp3ATI */
          32, /* glBeginFragmentShaderATI */
          61, /* glBindFragmentShaderATI */
         248, /* glColorFragmentOp1ATI */
         249, /* glColorFragmentOp2ATI */
         250, /* glColorFragmentOp3ATI */
         414, /* glDeleteFragmentShaderATI */
         548, /* glEndFragmentShaderATI */
         674, /* glGenFragmentShadersATI */
        1656, /* glPassTexCoordATI */
        2036, /* glSampleMapATI */
        2106  /* glSetFragmentShaderConstantATI */
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
        1342, /* glMapObjectBufferATI */
        2521  /* glUnmapObjectBufferATI */
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
        1654, /* glPNTrianglesfATI */
        1655  /* glPNTrianglesiATI */
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
        2140, /* glStencilFuncSeparateATI */
        2145  /* glStencilOpSeparateATI */
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
          22, /* glArrayObjectATI */
         664, /* glFreeObjectBufferATI */
         718, /* glGetArrayObjectfvATI */
         719, /* glGetArrayObjectivATI */
         894, /* glGetObjectBufferfvATI */
         895, /* glGetObjectBufferivATI */
        1077, /* glGetVariantArrayObjectfvATI */
        1078, /* glGetVariantArrayObjectivATI */
        1240, /* glIsObjectBufferATI */
        1613, /* glNewObjectBufferATI */
        2523, /* glUpdateObjectBufferATI */
        2543  /* glVariantArrayObjectATI */
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
        1091, /* glGetVertexAttribArrayObjectfvATI */
        1092, /* glGetVertexAttribArrayObjectivATI */
        2731  /* glVertexAttribArrayObjectATI */
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
         191, /* glClientActiveVertexStreamATI */
        1637, /* glNormalStream3bATI */
        1638, /* glNormalStream3bvATI */
        1639, /* glNormalStream3dATI */
        1640, /* glNormalStream3dvATI */
        1641, /* glNormalStream3fATI */
        1642, /* glNormalStream3fvATI */
        1643, /* glNormalStream3iATI */
        1644, /* glNormalStream3ivATI */
        1645, /* glNormalStream3sATI */
        1646, /* glNormalStream3svATI */
        2850, /* glVertexBlendEnvfATI */
        2851, /* glVertexBlendEnviATI */
        2863, /* glVertexStream1dATI */
        2864, /* glVertexStream1dvATI */
        2865, /* glVertexStream1fATI */
        2866, /* glVertexStream1fvATI */
        2867, /* glVertexStream1iATI */
        2868, /* glVertexStream1ivATI */
        2869, /* glVertexStream1sATI */
        2870, /* glVertexStream1svATI */
        2871, /* glVertexStream2dATI */
        2872, /* glVertexStream2dvATI */
        2873, /* glVertexStream2fATI */
        2874, /* glVertexStream2fvATI */
        2875, /* glVertexStream2iATI */
        2876, /* glVertexStream2ivATI */
        2877, /* glVertexStream2sATI */
        2878, /* glVertexStream2svATI */
        2879, /* glVertexStream3dATI */
        2880, /* glVertexStream3dvATI */
        2881, /* glVertexStream3fATI */
        2882, /* glVertexStream3fvATI */
        2883, /* glVertexStream3iATI */
        2884, /* glVertexStream3ivATI */
        2885, /* glVertexStream3sATI */
        2886, /* glVertexStream3svATI */
        2887, /* glVertexStream4dATI */
        2888, /* glVertexStream4dvATI */
        2889, /* glVertexStream4fATI */
        2890, /* glVertexStream4fvATI */
        2891, /* glVertexStream4iATI */
        2892, /* glVertexStream4ivATI */
        2893, /* glVertexStream4sATI */
        2894  /* glVertexStream4svATI */
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
        2989  /* glBindUniformLocationCHROMIUM */
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
        3010  /* glCompressedCopyTextureCHROMIUM */
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
        3021, /* glCopySubTextureCHROMIUM */
        3024  /* glCopyTextureCHROMIUM */
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
        3027  /* glCoverageModulationCHROMIUM */
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
        3216  /* glLoseContextCHROMIUM */
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
         521, /* glEGLImageTargetTexStorageEXT */
         522  /* glEGLImageTargetTextureStorageEXT */
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
        3049, /* glDrawArraysInstancedBaseInstanceEXT */
        3057, /* glDrawElementsInstancedBaseInstanceEXT */
        3059  /* glDrawElementsInstancedBaseVertexBaseInstanceEXT */
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
        1058, /* glGetUniformBufferSizeEXT */
        1062, /* glGetUniformOffsetEXT */
        2487  /* glUniformBufferEXT */
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
         110  /* glBlendColorEXT */
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
         116  /* glBlendEquationSeparateEXT */
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
          59, /* glBindFragDataLocationEXT */
        2987, /* glBindFragDataLocationIndexedEXT */
        3127, /* glGetFragDataIndexEXT */
        3156  /* glGetProgramResourceLocationIndexEXT */
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
         125  /* glBlendFuncSeparateEXT */
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
         113  /* glBlendEquationEXT */
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
        3002  /* glBufferStorageEXT */
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
        3004, /* glClearTexImageEXT */
        3005  /* glClearTexSubImageEXT */
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
        3007  /* glClipControlEXT */
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
         264, /* glColorSubTableEXT */
         329  /* glCopyColorSubTableEXT */
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
        1308, /* glLockArraysEXT */
        2516  /* glUnlockArraysEXT */
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
         314, /* glConvolutionFilter1DEXT */
         316, /* glConvolutionFilter2DEXT */
         318, /* glConvolutionParameterfEXT */
         320, /* glConvolutionParameterfvEXT */
         322, /* glConvolutionParameteriEXT */
         324, /* glConvolutionParameterivEXT */
         333, /* glCopyConvolutionFilter1DEXT */
         335, /* glCopyConvolutionFilter2DEXT */
         760, /* glGetConvolutionFilterEXT */
         762, /* glGetConvolutionParameterfvEXT */
         764, /* glGetConvolutionParameterivEXT */
         994, /* glGetSeparableFilterEXT */
        2103  /* glSeparableFilter2DEXT */
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
          94, /* glBinormal3bEXT */
          95, /* glBinormal3bvEXT */
          96, /* glBinormal3dEXT */
          97, /* glBinormal3dvEXT */
          98, /* glBinormal3fEXT */
          99, /* glBinormal3fvEXT */
         100, /* glBinormal3iEXT */
         101, /* glBinormal3ivEXT */
         102, /* glBinormal3sEXT */
         103, /* glBinormal3svEXT */
         104, /* glBinormalPointerEXT */
        2159, /* glTangent3bEXT */
        2160, /* glTangent3bvEXT */
        2161, /* glTangent3dEXT */
        2162, /* glTangent3dvEXT */
        2163, /* glTangent3fEXT */
        2164, /* glTangent3fvEXT */
        2165, /* glTangent3iEXT */
        2166, /* glTangent3ivEXT */
        2167, /* glTangent3sEXT */
        2168, /* glTangent3svEXT */
        2169  /* glTangentPointerEXT */
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
        3018  /* glCopyImageSubDataEXT */
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
         347, /* glCopyTexImage1DEXT */
         349, /* glCopyTexImage2DEXT */
         351, /* glCopyTexSubImage1DEXT */
         353, /* glCopyTexSubImage2DEXT */
         355  /* glCopyTexSubImage3DEXT */
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
         393, /* glCullParameterdvEXT */
         394  /* glCullParameterfvEXT */
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
         897, /* glGetObjectLabelEXT */
        1271  /* glLabelObjectEXT */
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
        1208, /* glInsertEventMarkerEXT */
        1734, /* glPopGroupMarkerEXT */
        1933  /* glPushGroupMarkerEXT */
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
         447  /* glDepthBoundsEXT */
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
          69, /* glBindMultiTextureEXT */
         156, /* glCheckNamedFramebufferStatusEXT */
         179, /* glClearNamedBufferDataEXT */
         181, /* glClearNamedBufferSubDataEXT */
         192, /* glClientAttribDefaultEXT */
         284, /* glCompressedMultiTexImage1DEXT */
         285, /* glCompressedMultiTexImage2DEXT */
         286, /* glCompressedMultiTexImage3DEXT */
         287, /* glCompressedMultiTexSubImage1DEXT */
         288, /* glCompressedMultiTexSubImage2DEXT */
         289, /* glCompressedMultiTexSubImage3DEXT */
         302, /* glCompressedTextureImage1DEXT */
         303, /* glCompressedTextureImage2DEXT */
         304, /* glCompressedTextureImage3DEXT */
         306, /* glCompressedTextureSubImage1DEXT */
         308, /* glCompressedTextureSubImage2DEXT */
         310, /* glCompressedTextureSubImage3DEXT */
         338, /* glCopyMultiTexImage1DEXT */
         339, /* glCopyMultiTexImage2DEXT */
         340, /* glCopyMultiTexSubImage1DEXT */
         341, /* glCopyMultiTexSubImage2DEXT */
         342, /* glCopyMultiTexSubImage3DEXT */
         356, /* glCopyTextureImage1DEXT */
         357, /* glCopyTextureImage2DEXT */
         359, /* glCopyTextureSubImage1DEXT */
         361, /* glCopyTextureSubImage2DEXT */
         363, /* glCopyTextureSubImage3DEXT */
         465, /* glDisableClientStateIndexedEXT */
         466, /* glDisableClientStateiEXT */
         467, /* glDisableIndexedEXT */
         470, /* glDisableVertexArrayAttribEXT */
         471, /* glDisableVertexArrayEXT */
         533, /* glEnableClientStateIndexedEXT */
         534, /* glEnableClientStateiEXT */
         535, /* glEnableIndexedEXT */
         538, /* glEnableVertexArrayAttribEXT */
         539, /* glEnableVertexArrayEXT */
         595, /* glFlushMappedNamedBufferRangeEXT */
         638, /* glFramebufferDrawBufferEXT */
         639, /* glFramebufferDrawBuffersEXT */
         643, /* glFramebufferReadBufferEXT */
         702, /* glGenerateMultiTexMipmapEXT */
         704, /* glGenerateTextureMipmapEXT */
         724, /* glGetBooleanIndexedvEXT */
         753, /* glGetCompressedMultiTexImageEXT */
         757, /* glGetCompressedTextureImageEXT */
         771, /* glGetDoubleIndexedvEXT */
         773, /* glGetDoublei_vEXT */
         781, /* glGetFloatIndexedvEXT */
         783, /* glGetFloati_vEXT */
         797, /* glGetFramebufferParameterivEXT */
         817, /* glGetIntegerIndexedvEXT */
         856, /* glGetMultiTexEnvfvEXT */
         857, /* glGetMultiTexEnvivEXT */
         858, /* glGetMultiTexGendvEXT */
         859, /* glGetMultiTexGenfvEXT */
         860, /* glGetMultiTexGenivEXT */
         861, /* glGetMultiTexImageEXT */
         862, /* glGetMultiTexLevelParameterfvEXT */
         863, /* glGetMultiTexLevelParameterivEXT */
         864, /* glGetMultiTexParameterIivEXT */
         865, /* glGetMultiTexParameterIuivEXT */
         866, /* glGetMultiTexParameterfvEXT */
         867, /* glGetMultiTexParameterivEXT */
         872, /* glGetNamedBufferParameterivEXT */
         875, /* glGetNamedBufferPointervEXT */
         877, /* glGetNamedBufferSubDataEXT */
         879, /* glGetNamedFramebufferAttachmentParameterivEXT */
         882, /* glGetNamedFramebufferParameterivEXT */
         883, /* glGetNamedProgramLocalParameterIivEXT */
         884, /* glGetNamedProgramLocalParameterIuivEXT */
         885, /* glGetNamedProgramLocalParameterdvEXT */
         886, /* glGetNamedProgramLocalParameterfvEXT */
         887, /* glGetNamedProgramStringEXT */
         888, /* glGetNamedProgramivEXT */
         890, /* glGetNamedRenderbufferParameterivEXT */
         935, /* glGetPointerIndexedvEXT */
         936, /* glGetPointeri_vEXT */
        1034, /* glGetTextureImageEXT */
        1036, /* glGetTextureLevelParameterfvEXT */
        1038, /* glGetTextureLevelParameterivEXT */
        1040, /* glGetTextureParameterIivEXT */
        1042, /* glGetTextureParameterIuivEXT */
        1044, /* glGetTextureParameterfvEXT */
        1046, /* glGetTextureParameterivEXT */
        1086, /* glGetVertexArrayIntegeri_vEXT */
        1087, /* glGetVertexArrayIntegervEXT */
        1088, /* glGetVertexArrayPointeri_vEXT */
        1089, /* glGetVertexArrayPointervEXT */
        1227, /* glIsEnabledIndexedEXT */
        1339, /* glMapNamedBufferEXT */
        1341, /* glMapNamedBufferRangeEXT */
        1356, /* glMatrixFrustumEXT */
        1363, /* glMatrixLoadIdentityEXT */
        1365, /* glMatrixLoadTransposedEXT */
        1366, /* glMatrixLoadTransposefEXT */
        1367, /* glMatrixLoaddEXT */
        1368, /* glMatrixLoadfEXT */
        1373, /* glMatrixMultTransposedEXT */
        1374, /* glMatrixMultTransposefEXT */
        1375, /* glMatrixMultdEXT */
        1376, /* glMatrixMultfEXT */
        1377, /* glMatrixOrthoEXT */
        1378, /* glMatrixPopEXT */
        1379, /* glMatrixPushEXT */
        1380, /* glMatrixRotatedEXT */
        1381, /* glMatrixRotatefEXT */
        1382, /* glMatrixScaledEXT */
        1383, /* glMatrixScalefEXT */
        1384, /* glMatrixTranslatedEXT */
        1385, /* glMatrixTranslatefEXT */
        1427, /* glMultiTexBufferEXT */
        1524, /* glMultiTexCoordPointerEXT */
        1525, /* glMultiTexEnvfEXT */
        1526, /* glMultiTexEnvfvEXT */
        1527, /* glMultiTexEnviEXT */
        1528, /* glMultiTexEnvivEXT */
        1529, /* glMultiTexGendEXT */
        1530, /* glMultiTexGendvEXT */
        1531, /* glMultiTexGenfEXT */
        1532, /* glMultiTexGenfvEXT */
        1533, /* glMultiTexGeniEXT */
        1534, /* glMultiTexGenivEXT */
        1535, /* glMultiTexImage1DEXT */
        1536, /* glMultiTexImage2DEXT */
        1537, /* glMultiTexImage3DEXT */
        1538, /* glMultiTexParameterIivEXT */
        1539, /* glMultiTexParameterIuivEXT */
        1540, /* glMultiTexParameterfEXT */
        1541, /* glMultiTexParameterfvEXT */
        1542, /* glMultiTexParameteriEXT */
        1543, /* glMultiTexParameterivEXT */
        1544, /* glMultiTexRenderbufferEXT */
        1545, /* glMultiTexSubImage1DEXT */
        1546, /* glMultiTexSubImage2DEXT */
        1547, /* glMultiTexSubImage3DEXT */
        1564, /* glNamedBufferDataEXT */
        1569, /* glNamedBufferStorageEXT */
        1573, /* glNamedBufferSubDataEXT */
        1574, /* glNamedCopyBufferSubDataEXT */
        1578, /* glNamedFramebufferParameteriEXT */
        1581, /* glNamedFramebufferRenderbufferEXT */
        1586, /* glNamedFramebufferTexture1DEXT */
        1587, /* glNamedFramebufferTexture2DEXT */
        1588, /* glNamedFramebufferTexture3DEXT */
        1589, /* glNamedFramebufferTextureEXT */
        1590, /* glNamedFramebufferTextureFaceEXT */
        1592, /* glNamedFramebufferTextureLayerEXT */
        1593, /* glNamedProgramLocalParameter4dEXT */
        1594, /* glNamedProgramLocalParameter4dvEXT */
        1595, /* glNamedProgramLocalParameter4fEXT */
        1596, /* glNamedProgramLocalParameter4fvEXT */
        1597, /* glNamedProgramLocalParameterI4iEXT */
        1598, /* glNamedProgramLocalParameterI4ivEXT */
        1599, /* glNamedProgramLocalParameterI4uiEXT */
        1600, /* glNamedProgramLocalParameterI4uivEXT */
        1601, /* glNamedProgramLocalParameters4fvEXT */
        1602, /* glNamedProgramLocalParametersI4ivEXT */
        1603, /* glNamedProgramLocalParametersI4uivEXT */
        1604, /* glNamedProgramStringEXT */
        1606, /* glNamedRenderbufferStorageEXT */
        1609, /* glNamedRenderbufferStorageMultisampleCoverageEXT */
        1610, /* glNamedRenderbufferStorageMultisampleEXT */
        1789, /* glProgramUniform1dEXT */
        1791, /* glProgramUniform1dvEXT */
        1793, /* glProgramUniform1fEXT */
        1795, /* glProgramUniform1fvEXT */
        1801, /* glProgramUniform1iEXT */
        1803, /* glProgramUniform1ivEXT */
        1809, /* glProgramUniform1uiEXT */
        1811, /* glProgramUniform1uivEXT */
        1813, /* glProgramUniform2dEXT */
        1815, /* glProgramUniform2dvEXT */
        1817, /* glProgramUniform2fEXT */
        1819, /* glProgramUniform2fvEXT */
        1825, /* glProgramUniform2iEXT */
        1827, /* glProgramUniform2ivEXT */
        1833, /* glProgramUniform2uiEXT */
        1835, /* glProgramUniform2uivEXT */
        1837, /* glProgramUniform3dEXT */
        1839, /* glProgramUniform3dvEXT */
        1841, /* glProgramUniform3fEXT */
        1843, /* glProgramUniform3fvEXT */
        1849, /* glProgramUniform3iEXT */
        1851, /* glProgramUniform3ivEXT */
        1857, /* glProgramUniform3uiEXT */
        1859, /* glProgramUniform3uivEXT */
        1861, /* glProgramUniform4dEXT */
        1863, /* glProgramUniform4dvEXT */
        1865, /* glProgramUniform4fEXT */
        1867, /* glProgramUniform4fvEXT */
        1873, /* glProgramUniform4iEXT */
        1875, /* glProgramUniform4ivEXT */
        1881, /* glProgramUniform4uiEXT */
        1883, /* glProgramUniform4uivEXT */
        1889, /* glProgramUniformMatrix2dvEXT */
        1891, /* glProgramUniformMatrix2fvEXT */
        1893, /* glProgramUniformMatrix2x3dvEXT */
        1895, /* glProgramUniformMatrix2x3fvEXT */
        1897, /* glProgramUniformMatrix2x4dvEXT */
        1899, /* glProgramUniformMatrix2x4fvEXT */
        1901, /* glProgramUniformMatrix3dvEXT */
        1903, /* glProgramUniformMatrix3fvEXT */
        1905, /* glProgramUniformMatrix3x2dvEXT */
        1907, /* glProgramUniformMatrix3x2fvEXT */
        1909, /* glProgramUniformMatrix3x4dvEXT */
        1911, /* glProgramUniformMatrix3x4fvEXT */
        1913, /* glProgramUniformMatrix4dvEXT */
        1915, /* glProgramUniformMatrix4fvEXT */
        1917, /* glProgramUniformMatrix4x2dvEXT */
        1919, /* glProgramUniformMatrix4x2fvEXT */
        1921, /* glProgramUniformMatrix4x3dvEXT */
        1923, /* glProgramUniformMatrix4x3fvEXT */
        1931, /* glPushClientAttribDefaultEXT */
        2333, /* glTextureBufferEXT */
        2335, /* glTextureBufferRangeEXT */
        2337, /* glTextureImage1DEXT */
        2338, /* glTextureImage2DEXT */
        2341, /* glTextureImage3DEXT */
        2347, /* glTexturePageCommitmentEXT */
        2350, /* glTextureParameterIivEXT */
        2352, /* glTextureParameterIuivEXT */
        2354, /* glTextureParameterfEXT */
        2356, /* glTextureParameterfvEXT */
        2358, /* glTextureParameteriEXT */
        2360, /* glTextureParameterivEXT */
        2362, /* glTextureRenderbufferEXT */
        2364, /* glTextureStorage1DEXT */
        2366, /* glTextureStorage2DEXT */
        2368, /* glTextureStorage2DMultisampleEXT */
        2370, /* glTextureStorage3DEXT */
        2372, /* glTextureStorage3DMultisampleEXT */
        2380, /* glTextureSubImage1DEXT */
        2382, /* glTextureSubImage2DEXT */
        2384, /* glTextureSubImage3DEXT */
        2520, /* glUnmapNamedBufferEXT */
        2599, /* glVertexArrayBindVertexBufferEXT */
        2601, /* glVertexArrayColorOffsetEXT */
        2602, /* glVertexArrayEdgeFlagOffsetEXT */
        2604, /* glVertexArrayFogCoordOffsetEXT */
        2605, /* glVertexArrayIndexOffsetEXT */
        2606, /* glVertexArrayMultiTexCoordOffsetEXT */
        2607, /* glVertexArrayNormalOffsetEXT */
        2611, /* glVertexArraySecondaryColorOffsetEXT */
        2612, /* glVertexArrayTexCoordOffsetEXT */
        2613, /* glVertexArrayVertexAttribBindingEXT */
        2614, /* glVertexArrayVertexAttribDivisorEXT */
        2615, /* glVertexArrayVertexAttribFormatEXT */
        2616, /* glVertexArrayVertexAttribIFormatEXT */
        2617, /* glVertexArrayVertexAttribIOffsetEXT */
        2618, /* glVertexArrayVertexAttribLFormatEXT */
        2619, /* glVertexArrayVertexAttribLOffsetEXT */
        2620, /* glVertexArrayVertexAttribOffsetEXT */
        2621, /* glVertexArrayVertexBindingDivisorEXT */
        2624  /* glVertexArrayVertexOffsetEXT */
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
        3046  /* glDiscardFramebufferEXT */
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
        2986, /* glBeginQueryEXT */
        3034, /* glDeleteQueriesEXT */
        3074, /* glEndQueryEXT */
        3111, /* glGenQueriesEXT */
        3140, /* glGetInteger64vEXT */
         976, /* glGetQueryObjecti64vEXT */
        3159, /* glGetQueryObjectivEXT */
         980, /* glGetQueryObjectui64vEXT */
        3162, /* glGetQueryObjectuivEXT */
        3164, /* glGetQueryivEXT */
        3212, /* glIsQueryEXT */
        3246  /* glQueryCounterEXT */
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
        3051  /* glDrawBuffersEXT */
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
         252, /* glColorMaskIndexedEXT */
         467, /* glDisableIndexedEXT */
         535, /* glEnableIndexedEXT */
         724, /* glGetBooleanIndexedvEXT */
         817, /* glGetIntegerIndexedvEXT */
        1227  /* glIsEnabledIndexedEXT */
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
        2992, /* glBlendEquationSeparateiEXT */
        2994, /* glBlendEquationiEXT */
        2996, /* glBlendFuncSeparateiEXT */
        2998, /* glBlendFunciEXT */
        3008, /* glColorMaskiEXT */
        3043, /* glDisableiEXT */
        3070, /* glEnableiEXT */
        3208  /* glIsEnablediEXT */
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
        3054, /* glDrawElementsBaseVertexEXT */
        3060, /* glDrawElementsInstancedBaseVertexEXT */
        3063, /* glDrawRangeElementsBaseVertexEXT */
        3226  /* glMultiDrawElementsBaseVertexEXT */
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
         485, /* glDrawArraysInstancedEXT */
         504  /* glDrawElementsInstancedEXT */
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
         513  /* glDrawRangeElementsEXT */
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
        3065, /* glDrawTransformFeedbackEXT */
        3066  /* glDrawTransformFeedbackInstancedEXT */
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
         146, /* glBufferStorageExternalEXT */
        1570  /* glNamedBufferStorageExternalEXT */
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
         603, /* glFogCoordPointerEXT */
         606, /* glFogCoorddEXT */
         608, /* glFogCoorddvEXT */
         610, /* glFogCoordfEXT */
         612  /* glFogCoordfvEXT */
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
        3101, /* glFramebufferShadingRateEXT */
        3128, /* glGetFragmentShadingRatesEXT */
        3275, /* glShadingRateCombinerOpsEXT */
        3276  /* glShadingRateEXT */
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
         134  /* glBlitFramebufferEXT */
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
         135, /* glBlitFramebufferLayerEXT */
         136  /* glBlitFramebufferLayersEXT */
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
        1997  /* glRenderbufferStorageMultisampleEXT */
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
          63, /* glBindFramebufferEXT */
          75, /* glBindRenderbufferEXT */
         154, /* glCheckFramebufferStatusEXT */
         416, /* glDeleteFramebuffersEXT */
         434, /* glDeleteRenderbuffersEXT */
         645, /* glFramebufferRenderbufferEXT */
         651, /* glFramebufferTexture1DEXT */
         653, /* glFramebufferTexture2DEXT */
         655, /* glFramebufferTexture3DEXT */
         676, /* glGenFramebuffersEXT */
         689, /* glGenRenderbuffersEXT */
         701, /* glGenerateMipmapEXT */
         794, /* glGetFramebufferAttachmentParameterivEXT */
         986, /* glGetRenderbufferParameterivEXT */
        1232, /* glIsFramebufferEXT */
        1252, /* glIsRenderbufferEXT */
        1993  /* glRenderbufferStorageEXT */
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
         657  /* glFramebufferTextureEXT */
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
        1782  /* glProgramParameteriEXT */
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
        1758, /* glProgramEnvParameters4fvEXT */
        1769  /* glProgramLocalParameters4fvEXT */
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
          59, /* glBindFragDataLocationEXT */
         788, /* glGetFragDataLocationEXT */
        1074, /* glGetUniformuivEXT */
        1094, /* glGetVertexAttribIivEXT */
        1096, /* glGetVertexAttribIuivEXT */
        2417, /* glUniform1uiEXT */
        2419, /* glUniform1uivEXT */
        2439, /* glUniform2uiEXT */
        2441, /* glUniform2uivEXT */
        2461, /* glUniform3uiEXT */
        2463, /* glUniform3uivEXT */
        2483, /* glUniform4uiEXT */
        2485, /* glUniform4uivEXT */
        2738, /* glVertexAttribI1iEXT */
        2740, /* glVertexAttribI1ivEXT */
        2742, /* glVertexAttribI1uiEXT */
        2744, /* glVertexAttribI1uivEXT */
        2746, /* glVertexAttribI2iEXT */
        2748, /* glVertexAttribI2ivEXT */
        2750, /* glVertexAttribI2uiEXT */
        2752, /* glVertexAttribI2uivEXT */
        2754, /* glVertexAttribI3iEXT */
        2756, /* glVertexAttribI3ivEXT */
        2758, /* glVertexAttribI3uiEXT */
        2760, /* glVertexAttribI3uivEXT */
        2762, /* glVertexAttribI4bvEXT */
        2764, /* glVertexAttribI4iEXT */
        2766, /* glVertexAttribI4ivEXT */
        2768, /* glVertexAttribI4svEXT */
        2770, /* glVertexAttribI4ubvEXT */
        2772, /* glVertexAttribI4uiEXT */
        2774, /* glVertexAttribI4uivEXT */
        2776, /* glVertexAttribI4usvEXT */
        2780  /* glVertexAttribIPointerEXT */
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
         803, /* glGetHistogramEXT */
         805, /* glGetHistogramParameterfvEXT */
         807, /* glGetHistogramParameterivEXT */
         851, /* glGetMinmaxEXT */
         853, /* glGetMinmaxParameterfvEXT */
         855, /* glGetMinmaxParameterivEXT */
        1172, /* glHistogramEXT */
        1395, /* glMinmaxEXT */
        2023, /* glResetHistogramEXT */
        2026  /* glResetMinmaxEXT */
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
        1188  /* glIndexFuncEXT */
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
        1190  /* glIndexMaterialEXT */
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
         485, /* glDrawArraysInstancedEXT */
         504, /* glDrawElementsInstancedEXT */
        3316  /* glVertexAttribDivisorEXT */
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
          16, /* glApplyTextureEXT */
        2344, /* glTextureLightEXT */
        2345  /* glTextureMaterialEXT */
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
        3090, /* glFlushMappedBufferRangeEXT */
        3218  /* glMapBufferRangeEXT */
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
         147, /* glBufferStorageMemEXT */
         373, /* glCreateMemoryObjectsEXT */
         418, /* glDeleteMemoryObjectsEXT */
         849, /* glGetMemoryObjectParameterivEXT */
        1075, /* glGetUnsignedBytei_vEXT */
        1076, /* glGetUnsignedBytevEXT */
        1236, /* glIsMemoryObjectEXT */
        1391, /* glMemoryObjectParameterivEXT */
        1571, /* glNamedBufferStorageMemEXT */
        2312, /* glTexStorageMem1DEXT */
        2313, /* glTexStorageMem2DEXT */
        2314, /* glTexStorageMem2DMultisampleEXT */
        2315, /* glTexStorageMem3DEXT */
        2316, /* glTexStorageMem3DMultisampleEXT */
        2373, /* glTextureStorageMem1DEXT */
        2374, /* glTextureStorageMem2DEXT */
        2375, /* glTextureStorageMem2DMultisampleEXT */
        2376, /* glTextureStorageMem3DEXT */
        2377  /* glTextureStorageMem3DMultisampleEXT */
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
        1178  /* glImportMemoryFdEXT */
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
        1179, /* glImportMemoryWin32HandleEXT */
        1180  /* glImportMemoryWin32NameEXT */
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
        1405, /* glMultiDrawArraysEXT */
        1415  /* glMultiDrawElementsEXT */
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
        3222, /* glMultiDrawArraysIndirectEXT */
        3227  /* glMultiDrawElementsIndirectEXT */
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
        2037, /* glSampleMaskEXT */
        2041  /* glSamplePatternEXT */
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
        3103, /* glFramebufferTexture2DMultisampleEXT */
        1997  /* glRenderbufferStorageMultisampleEXT */
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
        3052, /* glDrawBuffersIndexedEXT */
        3142, /* glGetIntegeri_vEXT */
        3247  /* glReadBufferIndexedEXT */
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
        2986, /* glBeginQueryEXT */
        3034, /* glDeleteQueriesEXT */
        3074, /* glEndQueryEXT */
        3111, /* glGenQueriesEXT */
        3162, /* glGetQueryObjectuivEXT */
        3164, /* glGetQueryivEXT */
        3212  /* glIsQueryEXT */
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
         266, /* glColorTableEXT */
         739, /* glGetColorTableEXT */
         741, /* glGetColorTableParameterfvEXT */
         744  /* glGetColorTableParameterivEXT */
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
         933, /* glGetPixelTransformParameterfvEXT */
         934, /* glGetPixelTransformParameterivEXT */
        1700, /* glPixelTransformParameterfEXT */
        1701, /* glPixelTransformParameterfvEXT */
        1702, /* glPixelTransformParameteriEXT */
        1703  /* glPixelTransformParameterivEXT */
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
        1709, /* glPointParameterfEXT */
        1713  /* glPointParameterfvEXT */
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
        1728  /* glPolygonOffsetEXT */
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
        1727  /* glPolygonOffsetClampEXT */
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
        3239  /* glPrimitiveBoundingBoxEXT */
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
        1928  /* glProvokingVertexEXT */
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
        1971  /* glRasterSamplesEXT */
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
        3136, /* glGetGraphicsResetStatusEXT */
        3200, /* glGetnUniformfvEXT */
        3203, /* glGetnUniformivEXT */
        3250  /* glReadnPixelsEXT */
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
        2059, /* glSecondaryColor3bEXT */
        2061, /* glSecondaryColor3bvEXT */
        2063, /* glSecondaryColor3dEXT */
        2065, /* glSecondaryColor3dvEXT */
        2067, /* glSecondaryColor3fEXT */
        2069, /* glSecondaryColor3fvEXT */
        2073, /* glSecondaryColor3iEXT */
        2075, /* glSecondaryColor3ivEXT */
        2077, /* glSecondaryColor3sEXT */
        2079, /* glSecondaryColor3svEXT */
        2081, /* glSecondaryColor3ubEXT */
        2083, /* glSecondaryColor3ubvEXT */
        2085, /* glSecondaryColor3uiEXT */
        2087, /* glSecondaryColor3uivEXT */
        2089, /* glSecondaryColor3usEXT */
        2091, /* glSecondaryColor3usvEXT */
        2096  /* glSecondaryColorPointerEXT */
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
         436, /* glDeleteSemaphoresEXT */
         691, /* glGenSemaphoresEXT */
         992, /* glGetSemaphoreParameterui64vEXT */
        1075, /* glGetUnsignedBytei_vEXT */
        1076, /* glGetUnsignedBytevEXT */
        1254, /* glIsSemaphoreEXT */
        2101, /* glSemaphoreParameterui64vEXT */
        2123, /* glSignalSemaphoreEXT */
        2910  /* glWaitSemaphoreEXT */
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
        1182  /* glImportSemaphoreFdEXT */
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
        1183, /* glImportSemaphoreWin32HandleEXT */
        1184  /* glImportSemaphoreWin32NameEXT */
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
           3, /* glActiveProgramEXT */
        2983, /* glActiveShaderProgramEXT */
        2988, /* glBindProgramPipelineEXT */
         385, /* glCreateShaderProgramEXT */
        3029, /* glCreateShaderProgramvEXT */
        3033, /* glDeleteProgramPipelinesEXT */
        3110, /* glGenProgramPipelinesEXT */
        3154, /* glGetProgramPipelineInfoLogEXT */
        3155, /* glGetProgramPipelineivEXT */
        3211, /* glIsProgramPipelineEXT */
        1782, /* glProgramParameteriEXT */
        1793, /* glProgramUniform1fEXT */
        1795, /* glProgramUniform1fvEXT */
        1801, /* glProgramUniform1iEXT */
        1803, /* glProgramUniform1ivEXT */
        1809, /* glProgramUniform1uiEXT */
        1811, /* glProgramUniform1uivEXT */
        1817, /* glProgramUniform2fEXT */
        1819, /* glProgramUniform2fvEXT */
        1825, /* glProgramUniform2iEXT */
        1827, /* glProgramUniform2ivEXT */
        1833, /* glProgramUniform2uiEXT */
        1835, /* glProgramUniform2uivEXT */
        1841, /* glProgramUniform3fEXT */
        1843, /* glProgramUniform3fvEXT */
        1849, /* glProgramUniform3iEXT */
        1851, /* glProgramUniform3ivEXT */
        1857, /* glProgramUniform3uiEXT */
        1859, /* glProgramUniform3uivEXT */
        1865, /* glProgramUniform4fEXT */
        1867, /* glProgramUniform4fvEXT */
        1873, /* glProgramUniform4iEXT */
        1875, /* glProgramUniform4ivEXT */
        1881, /* glProgramUniform4uiEXT */
        1883, /* glProgramUniform4uivEXT */
        1891, /* glProgramUniformMatrix2fvEXT */
        1895, /* glProgramUniformMatrix2x3fvEXT */
        1899, /* glProgramUniformMatrix2x4fvEXT */
        1903, /* glProgramUniformMatrix3fvEXT */
        1907, /* glProgramUniformMatrix3x2fvEXT */
        1911, /* glProgramUniformMatrix3x4fvEXT */
        1915, /* glProgramUniformMatrix4fvEXT */
        1919, /* glProgramUniformMatrix4x2fvEXT */
        1923, /* glProgramUniformMatrix4x3fvEXT */
        3313, /* glUseProgramStagesEXT */
        2528, /* glUseShaderProgramEXT */
        3314  /* glValidateProgramPipelineEXT */
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
         640  /* glFramebufferFetchBarrierEXT */
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
          65, /* glBindImageTextureEXT */
        1390  /* glMemoryBarrierEXT */
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
        3003, /* glClearPixelLocalStorageuiEXT */
        3100, /* glFramebufferPixelLocalStorageSizeEXT */
        3135  /* glGetFramebufferPixelLocalStorageSizeEXT */
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
        3287  /* glTexPageCommitmentEXT */
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
        2135  /* glStencilClearTagEXT */
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
           5  /* glActiveStencilFaceEXT */
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
        2323, /* glTexSubImage1DEXT */
        2325  /* glTexSubImage2DEXT */
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
        3232  /* glPatchParameteriEXT */
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
        2287, /* glTexImage3DEXT */
        2327  /* glTexSubImage3DEXT */
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
         662  /* glFramebufferTextureLayerEXT */
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
        3168, /* glGetSamplerParameterIivEXT */
        3171, /* glGetSamplerParameterIuivEXT */
        1024, /* glGetTexParameterIivEXT */
        1026, /* glGetTexParameterIuivEXT */
        3261, /* glSamplerParameterIivEXT */
        3264, /* glSamplerParameterIuivEXT */
        2294, /* glTexParameterIivEXT */
        2296  /* glTexParameterIuivEXT */
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
        2179, /* glTexBufferEXT */
        3280  /* glTexBufferRangeEXT */
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
        2179  /* glTexBufferEXT */
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
         169, /* glClearColorIiEXT */
         170, /* glClearColorIuiEXT */
        1024, /* glGetTexParameterIivEXT */
        1026, /* glGetTexParameterIuivEXT */
        2294, /* glTexParameterIivEXT */
        2296  /* glTexParameterIuivEXT */
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
          19, /* glAreTexturesResidentEXT */
          81, /* glBindTextureEXT */
         441, /* glDeleteTexturesEXT */
         694, /* glGenTexturesEXT */
        1259, /* glIsTextureEXT */
        1744  /* glPrioritizeTexturesEXT */
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
        2346  /* glTextureNormalEXT */
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
        2305, /* glTexStorage1DEXT */
        2307, /* glTexStorage2DEXT */
        2310, /* glTexStorage3DEXT */
        2364, /* glTextureStorage1DEXT */
        2366, /* glTextureStorage2DEXT */
        2370  /* glTextureStorage3DEXT */
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
        3296, /* glTexStorageAttribs2DEXT */
        3297  /* glTexStorageAttribs3DEXT */
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
        3302  /* glTextureViewEXT */
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
         976, /* glGetQueryObjecti64vEXT */
         980  /* glGetQueryObjectui64vEXT */
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
          40, /* glBeginTransformFeedbackEXT */
          49, /* glBindBufferBaseEXT */
          51, /* glBindBufferOffsetEXT */
          54, /* glBindBufferRangeEXT */
         557, /* glEndTransformFeedbackEXT */
        1052, /* glGetTransformFeedbackVaryingEXT */
        2392  /* glTransformFeedbackVaryingsEXT */
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
          21, /* glArrayElementEXT */
         260, /* glColorPointerEXT */
         480, /* glDrawArraysEXT */
         526, /* glEdgeFlagPointerEXT */
         938, /* glGetPointervEXT */
        1192, /* glIndexPointerEXT */
        1634, /* glNormalPointerEXT */
        2263, /* glTexCoordPointerEXT */
        2860  /* glVertexPointerEXT */
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
        1098, /* glGetVertexAttribLdvEXT */
        2782, /* glVertexAttribL1dEXT */
        2784, /* glVertexAttribL1dvEXT */
        2792, /* glVertexAttribL2dEXT */
        2794, /* glVertexAttribL2dvEXT */
        2800, /* glVertexAttribL3dEXT */
        2802, /* glVertexAttribL3dvEXT */
        2808, /* glVertexAttribL4dEXT */
        2810, /* glVertexAttribL4dvEXT */
        2818  /* glVertexAttribLPointerEXT */
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
          42, /* glBeginVertexShaderEXT */
          67, /* glBindLightParameterEXT */
          68, /* glBindMaterialParameterEXT */
          70, /* glBindParameterEXT */
          79, /* glBindTexGenParameterEXT */
          83, /* glBindTextureUnitParameterEXT */
          91, /* glBindVertexShaderEXT */
         446, /* glDeleteVertexShaderEXT */
         468, /* glDisableVariantClientStateEXT */
         536, /* glEnableVariantClientStateEXT */
         559, /* glEndVertexShaderEXT */
         580, /* glExtractComponentEXT */
         692, /* glGenSymbolsEXT */
         699, /* glGenVertexShadersEXT */
         825, /* glGetInvariantBooleanvEXT */
         826, /* glGetInvariantFloatvEXT */
         827, /* glGetInvariantIntegervEXT */
         833, /* glGetLocalConstantBooleanvEXT */
         834, /* glGetLocalConstantFloatvEXT */
         835, /* glGetLocalConstantIntegervEXT */
        1079, /* glGetVariantBooleanvEXT */
        1080, /* glGetVariantFloatvEXT */
        1081, /* glGetVariantIntegervEXT */
        1082, /* glGetVariantPointervEXT */
        1207, /* glInsertComponentEXT */
        1264, /* glIsVariantEnabledEXT */
        2107, /* glSetInvariantEXT */
        2108, /* glSetLocalConstantEXT */
        2112, /* glShaderOp1EXT */
        2113, /* glShaderOp2EXT */
        2114, /* glShaderOp3EXT */
        2156, /* glSwizzleEXT */
        2544, /* glVariantPointerEXT */
        2545, /* glVariantbvEXT */
        2546, /* glVariantdvEXT */
        2547, /* glVariantfvEXT */
        2548, /* glVariantivEXT */
        2549, /* glVariantsvEXT */
        2550, /* glVariantubvEXT */
        2551, /* glVariantuivEXT */
        2552, /* glVariantusvEXT */
        2981  /* glWriteMaskEXT */
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
        2895, /* glVertexWeightPointerEXT */
        2896, /* glVertexWeightfEXT */
        2897  /* glVertexWeightfvEXT */
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
           2, /* glAcquireKeyedMutexWin32EXT */
        1988  /* glReleaseKeyedMutexWin32EXT */
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
        2980  /* glWindowRectanglesEXT */
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
        1186  /* glImportSyncEXT */
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
         636  /* glFrameTerminatorGREMEDY */
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
        2154  /* glStringMarkerGREMEDY */
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
         811, /* glGetImageTransformParameterfvHP */
         812, /* glGetImageTransformParameterivHP */
        1174, /* glImageTransformParameterfHP */
        1175, /* glImageTransformParameterfvHP */
        1176, /* glImageTransformParameteriHP */
        1177  /* glImageTransformParameterivHP */
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
        1425, /* glMultiModeDrawArraysIBM */
        1426  /* glMultiModeDrawElementsIBM */
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
         598  /* glFlushStaticDataIBM */
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
         261, /* glColorPointerListIBM */
         527, /* glEdgeFlagPointerListIBM */
         604, /* glFogCoordPointerListIBM */
        1193, /* glIndexPointerListIBM */
        1635, /* glNormalPointerListIBM */
        2097, /* glSecondaryColorPointerListIBM */
        2264, /* glTexCoordPointerListIBM */
        2861  /* glVertexPointerListIBM */
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
        3189, /* glGetTextureHandleIMG */
        3190, /* glGetTextureSamplerHandleIMG */
        3242, /* glProgramUniformHandleui64IMG */
        3243, /* glProgramUniformHandleui64vIMG */
        3304, /* glUniformHandleui64IMG */
        3305  /* glUniformHandleui64vIMG */
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
        3102, /* glFramebufferTexture2DDownsampleIMG */
        3106  /* glFramebufferTextureLayerDownsampleIMG */
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
        3104, /* glFramebufferTexture2DMultisampleIMG */
        3256  /* glRenderbufferStorageMultisampleIMG */
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
         126  /* glBlendFuncSeparateINGR */
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
          15  /* glApplyFramebufferAttachmentCMAAINTEL */
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
        1345, /* glMapTexture2DINTEL */
        2157, /* glSyncTextureINTEL */
        2522  /* glUnmapTexture2DINTEL */
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
         262, /* glColorPointervINTEL */
        1636, /* glNormalPointervINTEL */
        2265, /* glTexCoordPointervINTEL */
        2862  /* glVertexPointervINTEL */
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
          35, /* glBeginPerfQueryINTEL */
         374, /* glCreatePerfQueryINTEL */
         425, /* glDeletePerfQueryINTEL */
         552, /* glEndPerfQueryINTEL */
         779, /* glGetFirstPerfQueryIdINTEL */
         893, /* glGetNextPerfQueryIdINTEL */
         917, /* glGetPerfCounterInfoINTEL */
         924, /* glGetPerfQueryDataINTEL */
         925, /* glGetPerfQueryIdByNameINTEL */
         926  /* glGetPerfQueryInfoINTEL */
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
         107  /* glBlendBarrierKHR */
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
         396, /* glDebugMessageCallback */
        3030, /* glDebugMessageCallbackKHR */
         399, /* glDebugMessageControl */
        3031, /* glDebugMessageControlKHR */
         402, /* glDebugMessageInsert */
        3032, /* glDebugMessageInsertKHR */
         767, /* glGetDebugMessageLog */
        3121, /* glGetDebugMessageLogKHR */
         896, /* glGetObjectLabel */
        3148, /* glGetObjectLabelKHR */
         901, /* glGetObjectPtrLabel */
        3149, /* glGetObjectPtrLabelKHR */
         937, /* glGetPointerv */
        3150, /* glGetPointervKHR */
        1647, /* glObjectLabel */
        3230, /* glObjectLabelKHR */
        1648, /* glObjectPtrLabel */
        3231, /* glObjectPtrLabelKHR */
        1733, /* glPopDebugGroup */
        3237, /* glPopDebugGroupKHR */
        1932, /* glPushDebugGroup */
        3245  /* glPushDebugGroupKHR */
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
        1387  /* glMaxShaderCompilerThreadsKHR */
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
         799, /* glGetGraphicsResetStatus */
        3137, /* glGetGraphicsResetStatusKHR */
        1153, /* glGetnUniformfv */
        3201, /* glGetnUniformfvKHR */
        1156, /* glGetnUniformiv */
        3204, /* glGetnUniformivKHR */
        1159, /* glGetnUniformuiv */
        3206, /* glGetnUniformuivKHR */
        1975, /* glReadnPixels */
        3251  /* glReadnPixelsKHR */
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
         642, /* glFramebufferParameteriMESA */
         798  /* glGetFramebufferParameterivMESA */
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
        2027  /* glResizeBuffersMESA */
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
          76, /* glBindSampler */
         435, /* glDeleteSamplers */
         690, /* glGenSamplers */
         989, /* glGetSamplerParameterfv */
         990, /* glGetSamplerParameteriv */
        1253, /* glIsSampler */
        2045, /* glSamplerParameterf */
        2046, /* glSamplerParameterfv */
        2047, /* glSamplerParameteri */
        2048  /* glSamplerParameteriv */
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
        2926, /* glWindowPos2dMESA */
        2929, /* glWindowPos2dvMESA */
        2932, /* glWindowPos2fMESA */
        2935, /* glWindowPos2fvMESA */
        2938, /* glWindowPos2iMESA */
        2941, /* glWindowPos2ivMESA */
        2944, /* glWindowPos2sMESA */
        2947, /* glWindowPos2svMESA */
        2950, /* glWindowPos3dMESA */
        2953, /* glWindowPos3dvMESA */
        2956, /* glWindowPos3fMESA */
        2959, /* glWindowPos3fvMESA */
        2962, /* glWindowPos3iMESA */
        2965, /* glWindowPos3ivMESA */
        2968, /* glWindowPos3sMESA */
        2971, /* glWindowPos3svMESA */
        2972, /* glWindowPos4dMESA */
        2973, /* glWindowPos4dvMESA */
        2974, /* glWindowPos4fMESA */
        2975, /* glWindowPos4fvMESA */
        2976, /* glWindowPos4iMESA */
        2977, /* glWindowPos4ivMESA */
        2978, /* glWindowPos4sMESA */
        2979  /* glWindowPos4svMESA */
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
          31, /* glBeginConditionalRenderNVX */
         547  /* glEndConditionalRenderNVX */
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
          23, /* glAsyncCopyBufferSubDataNVX */
          24, /* glAsyncCopyImageSubDataNVX */
        1558, /* glMulticastScissorArrayvNVX */
        1559, /* glMulticastViewportArrayvNVX */
        1560, /* glMulticastViewportPositionWScaleNVX */
        2524  /* glUploadGpuMaskNVX */
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
        1268, /* glLGPUCopyImageSubDataNVX */
        1269, /* glLGPUInterlockNVX */
        1270  /* glLGPUNamedBufferSubDataNVX */
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
         193, /* glClientWaitSemaphoreui64NVX */
         378, /* glCreateProgressFenceNVX */
        2124, /* glSignalSemaphoreui64NVX */
        2911  /* glWaitSemaphoreui64NVX */
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
          14  /* glAlphaToCoverageDitherControlNV */
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
        1409, /* glMultiDrawArraysIndirectBindlessNV */
        1419  /* glMultiDrawElementsIndirectBindlessNV */
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
        1408, /* glMultiDrawArraysIndirectBindlessCountNV */
        1418  /* glMultiDrawElementsIndirectBindlessCountNV */
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
         810, /* glGetImageHandleNV */
        1032, /* glGetTextureHandleNV */
        1048, /* glGetTextureSamplerHandleNV */
        1234, /* glIsImageHandleResidentNV */
        1261, /* glIsTextureHandleResidentNV */
        1313, /* glMakeImageHandleNonResidentNV */
        1315, /* glMakeImageHandleResidentNV */
        1319, /* glMakeTextureHandleNonResidentNV */
        1321, /* glMakeTextureHandleResidentNV */
        1885, /* glProgramUniformHandleui64NV */
        1887, /* glProgramUniformHandleui64vNV */
        2489, /* glUniformHandleui64NV */
        2491  /* glUniformHandleui64vNV */
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
         108, /* glBlendBarrierNV */
         132  /* glBlendParameteriNV */
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
        2908  /* glViewportPositionWScaleNV */
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
         150, /* glCallCommandListNV */
         279, /* glCommandListSegmentsNV */
         280, /* glCompileCommandListNV */
         371, /* glCreateCommandListsNV */
         387, /* glCreateStatesNV */
         411, /* glDeleteCommandListsNV */
         438, /* glDeleteStatesNV */
         490, /* glDrawCommandsAddressNV */
         491, /* glDrawCommandsNV */
         492, /* glDrawCommandsStatesAddressNV */
         493, /* glDrawCommandsStatesNV */
         752, /* glGetCommandHeaderNV */
        1003, /* glGetStageIndexNV */
        1225, /* glIsCommandListNV */
        1256, /* glIsStateNV */
        1291, /* glListDrawCommandsStatesClientNV */
        2134  /* glStateCaptureNV */
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
          30, /* glBeginConditionalRenderNV */
         546  /* glEndConditionalRenderNV */
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
        2155  /* glSubpixelPrecisionBiasNV */
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
         311  /* glConservativeRasterParameterfNV */
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
         312  /* glConservativeRasterParameteriNV */
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
        3017  /* glCopyBufferSubDataNV */
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
         337  /* glCopyImageSubDataNV */
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
        3026, /* glCoverageMaskNV */
        3028  /* glCoverageOperationNV */
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
         173, /* glClearDepthdNV */
         448, /* glDepthBoundsdNV */
         456  /* glDepthRangedNV */
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
        3053  /* glDrawBuffersNV */
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
        3050, /* glDrawArraysInstancedNV */
        3062  /* glDrawElementsInstancedNV */
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
         514  /* glDrawTextureNV */
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
         520, /* glDrawVkImageNV */
        1122, /* glGetVkProcAddrNV */
        2125, /* glSignalVkFenceNV */
        2126, /* glSignalVkSemaphoreNV */
        2913  /* glWaitVkSemaphoreNV */
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
         573, /* glEvalMapsNV */
         836, /* glGetMapAttribParameterfvNV */
         837, /* glGetMapAttribParameterivNV */
         838, /* glGetMapControlPointsNV */
         839, /* glGetMapParameterfvNV */
         840, /* glGetMapParameterivNV */
        1331, /* glMapControlPointsNV */
        1343, /* glMapParameterfvNV */
        1344  /* glMapParameterivNV */
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
         869, /* glGetMultisamplefvNV */
        2038, /* glSampleMaskIndexedNV */
        2303  /* glTexRenderbufferNV */
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
         413, /* glDeleteFencesNV */
         588, /* glFinishFenceNV */
         673, /* glGenFencesNV */
         776, /* glGetFenceivNV */
        1230, /* glIsFenceNV */
        2105, /* glSetFenceNV */
        2174  /* glTestFenceNV */
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
         623  /* glFragmentCoverageColorNV */
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
         951, /* glGetProgramNamedParameterdvNV */
         952, /* glGetProgramNamedParameterfvNV */
        1772, /* glProgramNamedParameter4dNV */
        1773, /* glProgramNamedParameter4dvNV */
        1774, /* glProgramNamedParameter4fNV */
        1775  /* glProgramNamedParameter4fvNV */
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
        3001  /* glBlitFramebufferNV */
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
         368, /* glCoverageModulationNV */
         369, /* glCoverageModulationTableNV */
         766, /* glGetCoverageModulationTableNV */
        1971  /* glRasterSamplesEXT */
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
        3257  /* glRenderbufferStorageMultisampleNV */
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
        1996  /* glRenderbufferStorageMultisampleCoverageNV */
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
         657, /* glFramebufferTextureEXT */
         659, /* glFramebufferTextureFaceEXT */
         662, /* glFramebufferTextureLayerEXT */
        1926  /* glProgramVertexLimitNV */
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
        1548, /* glMulticastBarrierNV */
        1549, /* glMulticastBlitFramebufferNV */
        1550, /* glMulticastBufferSubDataNV */
        1551, /* glMulticastCopyBufferSubDataNV */
        1552, /* glMulticastCopyImageSubDataNV */
        1553, /* glMulticastFramebufferSampleLocationsfvNV */
        1554, /* glMulticastGetQueryObjecti64vNV */
        1555, /* glMulticastGetQueryObjectivNV */
        1556, /* glMulticastGetQueryObjectui64vNV */
        1557, /* glMulticastGetQueryObjectuivNV */
        1561, /* glMulticastWaitSyncNV */
        1990  /* glRenderGpuMaskNV */
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
         941, /* glGetProgramEnvParameterIivNV */
         942, /* glGetProgramEnvParameterIuivNV */
         947, /* glGetProgramLocalParameterIivNV */
         948, /* glGetProgramLocalParameterIuivNV */
        1754, /* glProgramEnvParameterI4iNV */
        1755, /* glProgramEnvParameterI4ivNV */
        1756, /* glProgramEnvParameterI4uiNV */
        1757, /* glProgramEnvParameterI4uivNV */
        1759, /* glProgramEnvParametersI4ivNV */
        1760, /* glProgramEnvParametersI4uivNV */
        1765, /* glProgramLocalParameterI4iNV */
        1766, /* glProgramLocalParameterI4ivNV */
        1767, /* glProgramLocalParameterI4uiNV */
        1768, /* glProgramLocalParameterI4uivNV */
        1770, /* glProgramLocalParametersI4ivNV */
        1771  /* glProgramLocalParametersI4uivNV */
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
         966, /* glGetProgramSubroutineParameteruivNV */
        1787  /* glProgramSubroutineParametersuivNV */
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
        1068, /* glGetUniformi64vNV */
        1798, /* glProgramUniform1i64NV */
        1800, /* glProgramUniform1i64vNV */
        1806, /* glProgramUniform1ui64NV */
        1808, /* glProgramUniform1ui64vNV */
        1822, /* glProgramUniform2i64NV */
        1824, /* glProgramUniform2i64vNV */
        1830, /* glProgramUniform2ui64NV */
        1832, /* glProgramUniform2ui64vNV */
        1846, /* glProgramUniform3i64NV */
        1848, /* glProgramUniform3i64vNV */
        1854, /* glProgramUniform3ui64NV */
        1856, /* glProgramUniform3ui64vNV */
        1870, /* glProgramUniform4i64NV */
        1872, /* glProgramUniform4i64vNV */
        1878, /* glProgramUniform4ui64NV */
        1880, /* glProgramUniform4ui64vNV */
        2406, /* glUniform1i64NV */
        2408, /* glUniform1i64vNV */
        2414, /* glUniform1ui64NV */
        2416, /* glUniform1ui64vNV */
        2428, /* glUniform2i64NV */
        2430, /* glUniform2i64vNV */
        2436, /* glUniform2ui64NV */
        2438, /* glUniform2ui64vNV */
        2450, /* glUniform3i64NV */
        2452, /* glUniform3i64vNV */
        2458, /* glUniform3ui64NV */
        2460, /* glUniform3ui64vNV */
        2472, /* glUniform4i64NV */
        2474, /* glUniform4i64vNV */
        2480, /* glUniform4ui64NV */
        2482  /* glUniform4ui64vNV */
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
         207, /* glColor3hNV */
         208, /* glColor3hvNV */
         229, /* glColor4hNV */
         230, /* glColor4hvNV */
         613, /* glFogCoordhNV */
         614, /* glFogCoordhvNV */
        1438, /* glMultiTexCoord1hNV */
        1439, /* glMultiTexCoord1hvNV */
        1460, /* glMultiTexCoord2hNV */
        1461, /* glMultiTexCoord2hvNV */
        1482, /* glMultiTexCoord3hNV */
        1483, /* glMultiTexCoord3hvNV */
        1504, /* glMultiTexCoord4hNV */
        1505, /* glMultiTexCoord4hvNV */
        1622, /* glNormal3hNV */
        1623, /* glNormal3hvNV */
        2070, /* glSecondaryColor3hNV */
        2071, /* glSecondaryColor3hvNV */
        2189, /* glTexCoord1hNV */
        2190, /* glTexCoord1hvNV */
        2213, /* glTexCoord2hNV */
        2214, /* glTexCoord2hvNV */
        2227, /* glTexCoord3hNV */
        2228, /* glTexCoord3hvNV */
        2245, /* glTexCoord4hNV */
        2246, /* glTexCoord4hvNV */
        2559, /* glVertex2hNV */
        2560, /* glVertex2hvNV */
        2573, /* glVertex3hNV */
        2574, /* glVertex3hvNV */
        2587, /* glVertex4hNV */
        2588, /* glVertex4hvNV */
        2637, /* glVertexAttrib1hNV */
        2638, /* glVertexAttrib1hvNV */
        2657, /* glVertexAttrib2hNV */
        2658, /* glVertexAttrib2hvNV */
        2677, /* glVertexAttrib3hNV */
        2678, /* glVertexAttrib3hvNV */
        2713, /* glVertexAttrib4hNV */
        2714, /* glVertexAttrib4hvNV */
        2833, /* glVertexAttribs1hvNV */
        2837, /* glVertexAttribs2hvNV */
        2841, /* glVertexAttribs3hvNV */
        2845, /* glVertexAttribs4hvNV */
        2898, /* glVertexWeighthNV */
        2899  /* glVertexWeighthvNV */
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
        3317  /* glVertexAttribDivisorNV */
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
         822  /* glGetInternalformatSampleivNV */
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
         139, /* glBufferAttachMemoryNV */
         848, /* glGetMemoryObjectDetachedResourcesuivNV */
        1562, /* glNamedBufferAttachMemoryNV */
        2024, /* glResetMemoryObjectParameterNV */
        2176, /* glTexAttachMemoryNV */
        2329  /* glTextureAttachMemoryNV */
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
         143, /* glBufferPageCommitmentMemNV */
        1567, /* glNamedBufferPageCommitmentMemNV */
        2292, /* glTexPageCommitmentMemNV */
        2348  /* glTexturePageCommitmentMemNV */
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
         506, /* glDrawMeshTasksIndirectNV */
         507, /* glDrawMeshTasksNV */
        1422, /* glMultiDrawMeshTasksIndirectCountNV */
        1423  /* glMultiDrawMeshTasksIndirectNV */
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
        3306, /* glUniformMatrix2x3fvNV */
        3307, /* glUniformMatrix2x4fvNV */
        3308, /* glUniformMatrix3x2fvNV */
        3309, /* glUniformMatrix3x4fvNV */
        3310, /* glUniformMatrix4x2fvNV */
        3311  /* glUniformMatrix4x3fvNV */
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
          33, /* glBeginOcclusionQueryNV */
         422, /* glDeleteOcclusionQueriesNV */
         550, /* glEndOcclusionQueryNV */
         679, /* glGenOcclusionQueriesNV */
         902, /* glGetOcclusionQueryivNV */
         903, /* glGetOcclusionQueryuivNV */
        1241  /* glIsOcclusionQueryNV */
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
        1747, /* glProgramBufferParametersIivNV */
        1748, /* glProgramBufferParametersIuivNV */
        1749  /* glProgramBufferParametersfvNV */
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
         344, /* glCopyPathNV */
         364, /* glCoverFillPathInstancedNV */
         365, /* glCoverFillPathNV */
         366, /* glCoverStrokePathInstancedNV */
         367, /* glCoverStrokePathNV */
         423, /* glDeletePathsNV */
         680, /* glGenPathsNV */
         904, /* glGetPathColorGenfvNV */
         905, /* glGetPathColorGenivNV */
         906, /* glGetPathCommandsNV */
         907, /* glGetPathCoordsNV */
         908, /* glGetPathDashArrayNV */
         909, /* glGetPathLengthNV */
         910, /* glGetPathMetricRangeNV */
         911, /* glGetPathMetricsNV */
         912, /* glGetPathParameterfvNV */
         913, /* glGetPathParameterivNV */
         914, /* glGetPathSpacingNV */
         915, /* glGetPathTexGenfvNV */
         916, /* glGetPathTexGenivNV */
         961, /* glGetProgramResourcefvNV */
        1211, /* glInterpolatePathsNV */
        1242, /* glIsPathNV */
        1243, /* glIsPointInFillPathNV */
        1244, /* glIsPointInStrokePathNV */
        1356, /* glMatrixFrustumEXT */
        1361, /* glMatrixLoad3x2fNV */
        1362, /* glMatrixLoad3x3fNV */
        1363, /* glMatrixLoadIdentityEXT */
        1364, /* glMatrixLoadTranspose3x3fNV */
        1365, /* glMatrixLoadTransposedEXT */
        1366, /* glMatrixLoadTransposefEXT */
        1367, /* glMatrixLoaddEXT */
        1368, /* glMatrixLoadfEXT */
        1370, /* glMatrixMult3x2fNV */
        1371, /* glMatrixMult3x3fNV */
        1372, /* glMatrixMultTranspose3x3fNV */
        1373, /* glMatrixMultTransposedEXT */
        1374, /* glMatrixMultTransposefEXT */
        1375, /* glMatrixMultdEXT */
        1376, /* glMatrixMultfEXT */
        1377, /* glMatrixOrthoEXT */
        1378, /* glMatrixPopEXT */
        1379, /* glMatrixPushEXT */
        1380, /* glMatrixRotatedEXT */
        1381, /* glMatrixRotatefEXT */
        1382, /* glMatrixScaledEXT */
        1383, /* glMatrixScalefEXT */
        1384, /* glMatrixTranslatedEXT */
        1385, /* glMatrixTranslatefEXT */
        1661, /* glPathColorGenNV */
        1662, /* glPathCommandsNV */
        1663, /* glPathCoordsNV */
        1664, /* glPathCoverDepthFuncNV */
        1665, /* glPathDashArrayNV */
        1666, /* glPathFogGenNV */
        1667, /* glPathGlyphIndexArrayNV */
        1668, /* glPathGlyphIndexRangeNV */
        1669, /* glPathGlyphRangeNV */
        1670, /* glPathGlyphsNV */
        1671, /* glPathMemoryGlyphIndexArrayNV */
        1672, /* glPathParameterfNV */
        1673, /* glPathParameterfvNV */
        1674, /* glPathParameteriNV */
        1675, /* glPathParameterivNV */
        1676, /* glPathStencilDepthOffsetNV */
        1677, /* glPathStencilFuncNV */
        1678, /* glPathStringNV */
        1679, /* glPathSubCommandsNV */
        1680, /* glPathSubCoordsNV */
        1681, /* glPathTexGenNV */
        1706, /* glPointAlongPathNV */
        1785, /* glProgramPathFragmentInputGenNV */
        2136, /* glStencilFillPathInstancedNV */
        2137, /* glStencilFillPathNV */
        2147, /* glStencilStrokePathInstancedNV */
        2148, /* glStencilStrokePathNV */
        2149, /* glStencilThenCoverFillPathInstancedNV */
        2150, /* glStencilThenCoverFillPathNV */
        2151, /* glStencilThenCoverStrokePathInstancedNV */
        2152, /* glStencilThenCoverStrokePathNV */
        2394, /* glTransformPathNV */
        2914  /* glWeightPathsNV */
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
         596, /* glFlushPixelDataRangeNV */
        1684  /* glPixelDataRangeNV */
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
        1716, /* glPointParameteriNV */
        1718  /* glPointParameterivNV */
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
        3236  /* glPolygonModeNV */
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
        1118, /* glGetVideoi64vNV */
        1119, /* glGetVideoivNV */
        1120, /* glGetVideoui64vNV */
        1121, /* glGetVideouivNV */
        1737, /* glPresentFrameDualFillNV */
        1738  /* glPresentFrameKeyedNV */
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
        1741, /* glPrimitiveRestartIndexNV */
        1742  /* glPrimitiveRestartNV */
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
        1939  /* glQueryResourceNV */
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
         432, /* glDeleteQueryResourceTagNV */
         687, /* glGenQueryResourceTagNV */
        1940  /* glQueryResourceTagNV */
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
        3248  /* glReadBufferNV */
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
         272, /* glCombinerInputNV */
         273, /* glCombinerOutputNV */
         274, /* glCombinerParameterfNV */
         275, /* glCombinerParameterfvNV */
         276, /* glCombinerParameteriNV */
         277, /* glCombinerParameterivNV */
         584, /* glFinalCombinerInputNV */
         747, /* glGetCombinerInputParameterfvNV */
         748, /* glGetCombinerInputParameterivNV */
         749, /* glGetCombinerOutputParameterfvNV */
         750, /* glGetCombinerOutputParameterivNV */
         777, /* glGetFinalCombinerInputParameterfvNV */
         778  /* glGetFinalCombinerInputParameterivNV */
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
         278, /* glCombinerStageParameterfvNV */
         751  /* glGetCombinerStageParameterfvNV */
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
         647, /* glFramebufferSampleLocationsfvNV */
        1583, /* glNamedFramebufferSampleLocationsfvNV */
        2028  /* glResolveDepthValuesNV */
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
        2054, /* glScissorExclusiveArrayvNV */
        2055  /* glScissorExclusiveNV */
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
         730, /* glGetBufferParameterui64vNV */
         820, /* glGetIntegerui64vNV */
         873, /* glGetNamedBufferParameterui64vNV */
        1072, /* glGetUniformui64vNV */
        1224, /* glIsBufferResidentNV */
        1238, /* glIsNamedBufferResidentNV */
        1310, /* glMakeBufferNonResidentNV */
        1311, /* glMakeBufferResidentNV */
        1316, /* glMakeNamedBufferNonResidentNV */
        1317, /* glMakeNamedBufferResidentNV */
        1924, /* glProgramUniformui64NV */
        1925, /* glProgramUniformui64vNV */
        2514, /* glUniformui64NV */
        2515  /* glUniformui64vNV */
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
          78, /* glBindShadingRateImageNV */
        1000, /* glGetShadingRateImagePaletteNV */
        1001, /* glGetShadingRateSampleLocationivNV */
        2118, /* glShadingRateImageBarrierNV */
        2119, /* glShadingRateImagePaletteNV */
        2120, /* glShadingRateSampleOrderCustomNV */
        2121  /* glShadingRateSampleOrderNV */
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
        2331  /* glTextureBarrierNV */
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
        2285, /* glTexImage2DMultisampleCoverageNV */
        2289, /* glTexImage3DMultisampleCoverageNV */
        2339, /* glTextureImage2DMultisampleCoverageNV */
        2340, /* glTextureImage2DMultisampleNV */
        2342, /* glTextureImage3DMultisampleCoverageNV */
        2343  /* glTextureImage3DMultisampleNV */
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
         382, /* glCreateSemaphoresNV */
         991, /* glGetSemaphoreParameterivNV */
        2100  /* glSemaphoreParameterivNV */
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
           8, /* glActiveVaryingNV */
          41, /* glBeginTransformFeedbackNV */
          50, /* glBindBufferBaseNV */
          52, /* glBindBufferOffsetNV */
          55, /* glBindBufferRangeNV */
         558, /* glEndTransformFeedbackNV */
         717, /* glGetActiveVaryingNV */
        1053, /* glGetTransformFeedbackVaryingNV */
        1083, /* glGetVaryingLocationNV */
        2387, /* glTransformFeedbackAttribsNV */
        2390, /* glTransformFeedbackStreamAttribsNV */
        2393  /* glTransformFeedbackVaryingsNV */
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
          86, /* glBindTransformFeedbackNV */
         443, /* glDeleteTransformFeedbacksNV */
         517, /* glDrawTransformFeedbackNV */
         696, /* glGenTransformFeedbacksNV */
        1263, /* glIsTransformFeedbackNV */
        1683, /* glPauseTransformFeedbackNV */
        2030  /* glResumeTransformFeedbackNV */
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
        2529, /* glVDPAUFiniNV */
        2530, /* glVDPAUGetSurfaceivNV */
        2531, /* glVDPAUInitNV */
        2532, /* glVDPAUIsSurfaceNV */
        2533, /* glVDPAUMapSurfacesNV */
        2534, /* glVDPAURegisterOutputSurfaceNV */
        2535, /* glVDPAURegisterVideoSurfaceNV */
        2537, /* glVDPAUSurfaceAccessNV */
        2538, /* glVDPAUUnmapSurfacesNV */
        2539  /* glVDPAUUnregisterSurfaceNV */
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
        2536  /* glVDPAURegisterVideoSurfaceWithPictureStructureNV */
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
         600, /* glFlushVertexArrayRangeNV */
        2610  /* glVertexArrayRangeNV */
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
        1099, /* glGetVertexAttribLi64vNV */
        1101, /* glGetVertexAttribLui64vNV */
        2785, /* glVertexAttribL1i64NV */
        2786, /* glVertexAttribL1i64vNV */
        2788, /* glVertexAttribL1ui64NV */
        2790, /* glVertexAttribL1ui64vNV */
        2795, /* glVertexAttribL2i64NV */
        2796, /* glVertexAttribL2i64vNV */
        2797, /* glVertexAttribL2ui64NV */
        2798, /* glVertexAttribL2ui64vNV */
        2803, /* glVertexAttribL3i64NV */
        2804, /* glVertexAttribL3i64vNV */
        2805, /* glVertexAttribL3ui64NV */
        2806, /* glVertexAttribL3ui64vNV */
        2811, /* glVertexAttribL4i64NV */
        2812, /* glVertexAttribL4i64vNV */
        2813, /* glVertexAttribL4ui64NV */
        2814, /* glVertexAttribL4ui64vNV */
        2816  /* glVertexAttribLFormatNV */
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
         138, /* glBufferAddressRangeNV */
         247, /* glColorFormatNV */
         524, /* glEdgeFlagFormatNV */
         601, /* glFogCoordFormatNV */
         819, /* glGetIntegerui64i_vNV */
        1187, /* glIndexFormatNV */
        1630, /* glNormalFormatNV */
        2092, /* glSecondaryColorFormatNV */
        2253, /* glTexCoordFormatNV */
        2736, /* glVertexAttribFormatNV */
        2778, /* glVertexAttribIFormatNV */
        2852  /* glVertexFormatNV */
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
          17, /* glAreProgramsResidentNV */
          72, /* glBindProgramNV */
         429, /* glDeleteProgramsNV */
         579, /* glExecuteProgramNV */
         684, /* glGenProgramsNV */
         953, /* glGetProgramParameterdvNV */
         954, /* glGetProgramParameterfvNV */
         965, /* glGetProgramStringNV */
         969, /* glGetProgramivNV */
        1050, /* glGetTrackMatrixivNV */
        1104, /* glGetVertexAttribPointervNV */
        1107, /* glGetVertexAttribdvNV */
        1110, /* glGetVertexAttribfvNV */
        1113, /* glGetVertexAttribivNV */
        1247, /* glIsProgramNV */
        1302, /* glLoadProgramNV */
        1776, /* glProgramParameter4dNV */
        1777, /* glProgramParameter4dvNV */
        1778, /* glProgramParameter4fNV */
        1779, /* glProgramParameter4fvNV */
        1783, /* glProgramParameters4dvNV */
        1784, /* glProgramParameters4fvNV */
        2021, /* glRequestResidentProgramsNV */
        2386, /* glTrackMatrixNV */
        2627, /* glVertexAttrib1dNV */
        2630, /* glVertexAttrib1dvNV */
        2633, /* glVertexAttrib1fNV */
        2636, /* glVertexAttrib1fvNV */
        2641, /* glVertexAttrib1sNV */
        2644, /* glVertexAttrib1svNV */
        2647, /* glVertexAttrib2dNV */
        2650, /* glVertexAttrib2dvNV */
        2653, /* glVertexAttrib2fNV */
        2656, /* glVertexAttrib2fvNV */
        2661, /* glVertexAttrib2sNV */
        2664, /* glVertexAttrib2svNV */
        2667, /* glVertexAttrib3dNV */
        2670, /* glVertexAttrib3dvNV */
        2673, /* glVertexAttrib3fNV */
        2676, /* glVertexAttrib3fvNV */
        2681, /* glVertexAttrib3sNV */
        2684, /* glVertexAttrib3svNV */
        2703, /* glVertexAttrib4dNV */
        2706, /* glVertexAttrib4dvNV */
        2709, /* glVertexAttrib4fNV */
        2712, /* glVertexAttrib4fvNV */
        2719, /* glVertexAttrib4sNV */
        2722, /* glVertexAttrib4svNV */
        2723, /* glVertexAttrib4ubNV */
        2726, /* glVertexAttrib4ubvNV */
        2830, /* glVertexAttribPointerNV */
        2831, /* glVertexAttribs1dvNV */
        2832, /* glVertexAttribs1fvNV */
        2834, /* glVertexAttribs1svNV */
        2835, /* glVertexAttribs2dvNV */
        2836, /* glVertexAttribs2fvNV */
        2838, /* glVertexAttribs2svNV */
        2839, /* glVertexAttribs3dvNV */
        2840, /* glVertexAttribs3fvNV */
        2842, /* glVertexAttribs3svNV */
        2843, /* glVertexAttribs4dvNV */
        2844, /* glVertexAttribs4fvNV */
        2846, /* glVertexAttribs4svNV */
        2847  /* glVertexAttribs4ubvNV */
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
        1094, /* glGetVertexAttribIivEXT */
        1096, /* glGetVertexAttribIuivEXT */
        2738, /* glVertexAttribI1iEXT */
        2740, /* glVertexAttribI1ivEXT */
        2742, /* glVertexAttribI1uiEXT */
        2744, /* glVertexAttribI1uivEXT */
        2746, /* glVertexAttribI2iEXT */
        2748, /* glVertexAttribI2ivEXT */
        2750, /* glVertexAttribI2uiEXT */
        2752, /* glVertexAttribI2uivEXT */
        2754, /* glVertexAttribI3iEXT */
        2756, /* glVertexAttribI3ivEXT */
        2758, /* glVertexAttribI3uiEXT */
        2760, /* glVertexAttribI3uivEXT */
        2762, /* glVertexAttribI4bvEXT */
        2764, /* glVertexAttribI4iEXT */
        2766, /* glVertexAttribI4ivEXT */
        2768, /* glVertexAttribI4svEXT */
        2770, /* glVertexAttribI4ubvEXT */
        2772, /* glVertexAttribI4uiEXT */
        2774, /* glVertexAttribI4uivEXT */
        2776, /* glVertexAttribI4usvEXT */
        2780  /* glVertexAttribIPointerEXT */
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
          43, /* glBeginVideoCaptureNV */
          92, /* glBindVideoCaptureStreamBufferNV */
          93, /* glBindVideoCaptureStreamTextureNV */
         560, /* glEndVideoCaptureNV */
        1114, /* glGetVideoCaptureStreamdvNV */
        1115, /* glGetVideoCaptureStreamfvNV */
        1116, /* glGetVideoCaptureStreamivNV */
        1117, /* glGetVideoCaptureivNV */
        2900, /* glVideoCaptureNV */
        2901, /* glVideoCaptureStreamParameterdvNV */
        2902, /* glVideoCaptureStreamParameterfvNV */
        2903  /* glVideoCaptureStreamParameterivNV */
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
        3037, /* glDepthRangeArrayfvNV */
        3039, /* glDepthRangeIndexedfNV */
        3044, /* glDisableiNV */
        3071, /* glEnableiNV */
        3124, /* glGetFloati_vNV */
        3209, /* glIsEnablediNV */
        3269, /* glScissorArrayvNV */
        3271, /* glScissorIndexedNV */
        3273, /* glScissorIndexedvNV */
        3318, /* glViewportArrayvNV */
        3320, /* glViewportIndexedfNV */
        3322  /* glViewportIndexedfvNV */
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
        2909  /* glViewportSwizzleNV */
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
        3067, /* glEGLImageTargetRenderbufferStorageOES */
        3068  /* glEGLImageTargetTexture2DOES */
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
        1428, /* glMultiTexCoord1bOES */
        1429, /* glMultiTexCoord1bvOES */
        1450, /* glMultiTexCoord2bOES */
        1451, /* glMultiTexCoord2bvOES */
        1472, /* glMultiTexCoord3bOES */
        1473, /* glMultiTexCoord3bvOES */
        1494, /* glMultiTexCoord4bOES */
        1495, /* glMultiTexCoord4bvOES */
        2183, /* glTexCoord1bOES */
        2184, /* glTexCoord1bvOES */
        2197, /* glTexCoord2bOES */
        2198, /* glTexCoord2bvOES */
        2221, /* glTexCoord3bOES */
        2222, /* glTexCoord3bvOES */
        2235, /* glTexCoord4bOES */
        2236, /* glTexCoord4bvOES */
        2553, /* glVertex2bOES */
        2554, /* glVertex2bvOES */
        2567, /* glVertex3bOES */
        2568, /* glVertex3bvOES */
        2581, /* glVertex4bOES */
        2582  /* glVertex4bvOES */
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
        3019  /* glCopyImageSubDataOES */
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
        2993, /* glBlendEquationSeparateiOES */
        2995, /* glBlendEquationiOES */
        2997, /* glBlendFuncSeparateiOES */
        2999, /* glBlendFunciOES */
        3009, /* glColorMaskiOES */
        3045, /* glDisableiOES */
        3072, /* glEnableiOES */
        3210  /* glIsEnablediOES */
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
        3055, /* glDrawElementsBaseVertexOES */
        3061, /* glDrawElementsInstancedBaseVertexOES */
        3064, /* glDrawRangeElementsBaseVertexOES */
        3226  /* glMultiDrawElementsBaseVertexEXT */
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
           1, /* glAccumxOES */
          13, /* glAlphaFuncxOES */
         106, /* glBitmapxOES */
         111, /* glBlendColorxOES */
         161, /* glClearAccumxOES */
         171, /* glClearColorxOES */
         176, /* glClearDepthxOES */
         198, /* glClipPlanexOES */
         219, /* glColor3xOES */
         220, /* glColor3xvOES */
         245, /* glColor4xOES */
         246, /* glColor4xvOES */
         325, /* glConvolutionParameterxOES */
         326, /* glConvolutionParameterxvOES */
         459, /* glDepthRangexOES */
         565, /* glEvalCoord1xOES */
         566, /* glEvalCoord1xvOES */
         571, /* glEvalCoord2xOES */
         572, /* glEvalCoord2xvOES */
         582, /* glFeedbackBufferxOES */
         620, /* glFogxOES */
         621, /* glFogxvOES */
         668, /* glFrustumxOES */
         737, /* glGetClipPlanexOES */
         765, /* glGetConvolutionParameterxvOES */
         780, /* glGetFixedvOES */
         808, /* glGetHistogramParameterxvOES */
         830, /* glGetLightxOES */
         844, /* glGetMapxvOES */
         847, /* glGetMaterialxOES */
         930, /* glGetPixelMapxv */
        1013, /* glGetTexEnvxvOES */
        1018, /* glGetTexGenxvOES */
        1022, /* glGetTexLevelParameterxvOES */
        1030, /* glGetTexParameterxvOES */
        1204, /* glIndexxOES */
        1205, /* glIndexxvOES */
        1277, /* glLightModelxOES */
        1278, /* glLightModelxvOES */
        1283, /* glLightxOES */
        1284, /* glLightxvOES */
        1287, /* glLineWidthxOES */
        1300, /* glLoadMatrixxOES */
        1307, /* glLoadTransposeMatrixxOES */
        1324, /* glMap1xOES */
        1327, /* glMap2xOES */
        1334, /* glMapGrid1xOES */
        1337, /* glMapGrid2xOES */
        1354, /* glMaterialxOES */
        1355, /* glMaterialxvOES */
        1398, /* glMultMatrixxOES */
        1403, /* glMultTransposeMatrixxOES */
        1448, /* glMultiTexCoord1xOES */
        1449, /* glMultiTexCoord1xvOES */
        1470, /* glMultiTexCoord2xOES */
        1471, /* glMultiTexCoord2xvOES */
        1492, /* glMultiTexCoord3xOES */
        1493, /* glMultiTexCoord3xvOES */
        1514, /* glMultiTexCoord4xOES */
        1515, /* glMultiTexCoord4xvOES */
        1628, /* glNormal3xOES */
        1629, /* glNormal3xvOES */
        1653, /* glOrthoxOES */
        1658, /* glPassThroughxOES */
        1688, /* glPixelMapx */
        1691, /* glPixelStorex */
        1699, /* glPixelTransferxOES */
        1705, /* glPixelZoomxOES */
        1719, /* glPointParameterxvOES */
        1721, /* glPointSizexOES */
        1729, /* glPolygonOffsetxOES */
        1745, /* glPrioritizeTexturesxOES */
        1949, /* glRasterPos2xOES */
        1950, /* glRasterPos2xvOES */
        1959, /* glRasterPos3xOES */
        1960, /* glRasterPos3xvOES */
        1969, /* glRasterPos4xOES */
        1970, /* glRasterPos4xvOES */
        1985, /* glRectxOES */
        1986, /* glRectxvOES */
        2033, /* glRotatexOES */
        2051, /* glScalexOES */
        2195, /* glTexCoord1xOES */
        2196, /* glTexCoord1xvOES */
        2219, /* glTexCoord2xOES */
        2220, /* glTexCoord2xvOES */
        2233, /* glTexCoord3xOES */
        2234, /* glTexCoord3xvOES */
        2251, /* glTexCoord4xOES */
        2252, /* glTexCoord4xvOES */
        2270, /* glTexEnvxOES */
        2271, /* glTexEnvxvOES */
        2279, /* glTexGenxOES */
        2280, /* glTexGenxvOES */
        2301, /* glTexParameterxOES */
        2302, /* glTexParameterxvOES */
        2397, /* glTranslatexOES */
        2565, /* glVertex2xOES */
        2566, /* glVertex2xvOES */
        2579, /* glVertex3xOES */
        2580, /* glVertex3xvOES */
        2593, /* glVertex4xOES */
        2594  /* glVertex4xvOES */
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
        3108  /* glFramebufferTextureOES */
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
        3152, /* glGetProgramBinaryOES */
        3241  /* glProgramBinaryOES */
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
        3118, /* glGetBufferPointervOES */
        3217, /* glMapBufferOES */
        3312  /* glUnmapBufferOES */
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
        3240  /* glPrimitiveBoundingBoxOES */
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
        1937  /* glQueryMatrixxOES */
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
        3220  /* glMinSampleShadingOES */
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
         175, /* glClearDepthfOES */
         197, /* glClipPlanefOES */
         458, /* glDepthRangefOES */
         667, /* glFrustumfOES */
         736, /* glGetClipPlanefOES */
        1652  /* glOrthofOES */
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
        3233  /* glPatchParameteriOES */
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
        3012, /* glCompressedTexImage3DOES */
        3015, /* glCompressedTexSubImage3DOES */
        3022, /* glCopyTexSubImage3DOES */
        3105, /* glFramebufferTexture3DOES */
        3285, /* glTexImage3DOES */
        3299  /* glTexSubImage3DOES */
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
        3169, /* glGetSamplerParameterIivOES */
        3172, /* glGetSamplerParameterIuivOES */
        3183, /* glGetTexParameterIivOES */
        3185, /* glGetTexParameterIuivOES */
        3262, /* glSamplerParameterIivOES */
        3265, /* glSamplerParameterIuivOES */
        3288, /* glTexParameterIivOES */
        3290  /* glTexParameterIuivOES */
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
        3279, /* glTexBufferOES */
        3281  /* glTexBufferRangeOES */
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
        3295  /* glTexStorage3DMultisampleOES */
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
        3303  /* glTextureViewOES */
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
        2990, /* glBindVertexArrayOES */
        3036, /* glDeleteVertexArraysOES */
        3112, /* glGenVertexArraysOES */
        3214  /* glIsVertexArrayOES */
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
        3038, /* glDepthRangeArrayfvOES */
        3040, /* glDepthRangeIndexedfOES */
        3045, /* glDisableiOES */
        3072, /* glEnableiOES */
        3125, /* glGetFloati_vOES */
        3210, /* glIsEnablediOES */
        3270, /* glScissorArrayvOES */
        3272, /* glScissorIndexedOES */
        3274, /* glScissorIndexedvOES */
        3319, /* glViewportArrayvOES */
        3321, /* glViewportIndexedfOES */
        3323  /* glViewportIndexedfvOES */
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
         663  /* glFramebufferTextureMultiviewOVR */
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
        3107  /* glFramebufferTextureMultisampleMultiviewOVR */
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
        1170  /* glHintPGI */
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
        2984  /* glAlphaFuncQCOM */
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
        3041, /* glDisableDriverControlQCOM */
        3069, /* glEnableDriverControlQCOM */
        3122, /* glGetDriverControlStringQCOM */
        3123  /* glGetDriverControlsQCOM */
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
        3076, /* glExtGetBufferPointervQCOM */
        3077, /* glExtGetBuffersQCOM */
        3078, /* glExtGetFramebuffersQCOM */
        3081, /* glExtGetRenderbuffersQCOM */
        3083, /* glExtGetTexLevelParameterivQCOM */
        3084, /* glExtGetTexSubImageQCOM */
        3085, /* glExtGetTexturesQCOM */
        3087  /* glExtTexObjectStateOverrideiQCOM */
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
        3079, /* glExtGetProgramBinarySourceQCOM */
        3080, /* glExtGetProgramsQCOM */
        3082, /* glExtGetShadersQCOM */
        3086  /* glExtIsProgramBinaryQCOM */
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
        3088  /* glExtrapolateTex2DQCOM */
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
        3092, /* glFramebufferFoveationConfigQCOM */
        3093  /* glFramebufferFoveationParametersQCOM */
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
        3282, /* glTexEstimateMotionQCOM */
        3283  /* glTexEstimateMotionRegionsQCOM */
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
        3091  /* glFramebufferFetchBarrierQCOM */
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
        3277  /* glShadingRateQCOM */
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
        3301  /* glTextureFoveationParametersQCOM */
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
        3075, /* glEndTilingQCOM */
        3278  /* glStartTilingQCOM */
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
         462, /* glDetailTexFuncSGIS */
         770  /* glGetDetailTexFuncSGIS */
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
         615, /* glFogFuncSGIS */
         785  /* glGetFogFuncSGIS */
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
        2039, /* glSampleMaskSGIS */
        2042  /* glSamplePatternSGIS */
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
         931, /* glGetPixelTexGenParameterfvSGIS */
         932, /* glGetPixelTexGenParameterivSGIS */
        1692, /* glPixelTexGenParameterfSGIS */
        1693, /* glPixelTexGenParameterfvSGIS */
        1694, /* glPixelTexGenParameteriSGIS */
        1695  /* glPixelTexGenParameterivSGIS */
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
        1710, /* glPointParameterfSGIS */
        1714  /* glPointParameterfvSGIS */
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
        1002, /* glGetSharpenTexFuncSGIS */
        2122  /* glSharpenTexFuncSGIS */
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
        2290, /* glTexImage4DSGIS */
        2328  /* glTexSubImage4DSGIS */
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
        2336  /* glTextureColorMaskSGIS */
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
        1014, /* glGetTexFilterFuncSGIS */
        2272  /* glTexFilterFuncSGIS */
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
          25, /* glAsyncMarkerSGIX */
         408, /* glDeleteAsyncMarkersSGIX */
         586, /* glFinishAsyncSGIX */
         669, /* glGenAsyncMarkersSGIX */
        1221, /* glIsAsyncMarkerSGIX */
        1722  /* glPollAsyncSGIX */
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
         597  /* glFlushRasterSGIX */
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
         622, /* glFragmentColorMaterialSGIX */
         624, /* glFragmentLightModelfSGIX */
         625, /* glFragmentLightModelfvSGIX */
         626, /* glFragmentLightModeliSGIX */
         627, /* glFragmentLightModelivSGIX */
         628, /* glFragmentLightfSGIX */
         629, /* glFragmentLightfvSGIX */
         630, /* glFragmentLightiSGIX */
         631, /* glFragmentLightivSGIX */
         632, /* glFragmentMaterialfSGIX */
         633, /* glFragmentMaterialfvSGIX */
         634, /* glFragmentMaterialiSGIX */
         635, /* glFragmentMaterialivSGIX */
         789, /* glGetFragmentLightfvSGIX */
         790, /* glGetFragmentLightivSGIX */
         791, /* glGetFragmentMaterialfvSGIX */
         792, /* glGetFragmentMaterialivSGIX */
        1272  /* glLightEnviSGIX */
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
         637  /* glFrameZoomSGIX */
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
        1173  /* glIglooInterfaceSGIX */
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
         814, /* glGetInstrumentsSGIX */
        1209, /* glInstrumentsBufferSGIX */
        1723, /* glPollInstrumentsSGIX */
        1973, /* glReadInstrumentsSGIX */
        2133, /* glStartInstrumentsSGIX */
        2153  /* glStopInstrumentsSGIX */
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
         831, /* glGetListParameterfvSGIX */
         832, /* glGetListParameterivSGIX */
        1292, /* glListParameterfSGIX */
        1293, /* glListParameterfvSGIX */
        1294, /* glListParameteriSGIX */
        1295  /* glListParameterivSGIX */
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
        1696  /* glPixelTexGenSGIX */
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
         405, /* glDeformSGIX */
         406, /* glDeformationMap3dSGIX */
         407, /* glDeformationMap3fSGIX */
        1297  /* glLoadIdentityDeformationMapSGIX */
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
        1987  /* glReferencePlaneSGIX */
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
        2129, /* glSpriteParameterfSGIX */
        2130, /* glSpriteParameterfvSGIX */
        2131, /* glSpriteParameteriSGIX */
        2132  /* glSpriteParameterivSGIX */
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
        2158  /* glTagSampleBufferSGIX */
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
         268, /* glColorTableParameterfvSGI */
         270, /* glColorTableParameterivSGI */
         271, /* glColorTableSGI */
         331, /* glCopyColorTableSGI */
         742, /* glGetColorTableParameterfvSGI */
         745, /* glGetColorTableParameterivSGI */
         746  /* glGetColorTableSGI */
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
         590  /* glFinishTextureSUNX */
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
        1161, /* glGlobalAlphaFactorbSUN */
        1162, /* glGlobalAlphaFactordSUN */
        1163, /* glGlobalAlphaFactorfSUN */
        1164, /* glGlobalAlphaFactoriSUN */
        1165, /* glGlobalAlphaFactorsSUN */
        1166, /* glGlobalAlphaFactorubSUN */
        1167, /* glGlobalAlphaFactoruiSUN */
        1168  /* glGlobalAlphaFactorusSUN */
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
         505  /* glDrawMeshArraysSUN */
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
        1998, /* glReplacementCodePointerSUN */
        1999, /* glReplacementCodeubSUN */
        2000, /* glReplacementCodeubvSUN */
        2009, /* glReplacementCodeuiSUN */
        2018, /* glReplacementCodeuivSUN */
        2019, /* glReplacementCodeusSUN */
        2020  /* glReplacementCodeusvSUN */
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
         204, /* glColor3fVertex3fSUN */
         205, /* glColor3fVertex3fvSUN */
         226, /* glColor4fNormal3fVertex3fSUN */
         227, /* glColor4fNormal3fVertex3fvSUN */
         236, /* glColor4ubVertex2fSUN */
         237, /* glColor4ubVertex2fvSUN */
         238, /* glColor4ubVertex3fSUN */
         239, /* glColor4ubVertex3fvSUN */
        1619, /* glNormal3fVertex3fSUN */
        1620, /* glNormal3fVertex3fvSUN */
        2001, /* glReplacementCodeuiColor3fVertex3fSUN */
        2002, /* glReplacementCodeuiColor3fVertex3fvSUN */
        2003, /* glReplacementCodeuiColor4fNormal3fVertex3fSUN */
        2004, /* glReplacementCodeuiColor4fNormal3fVertex3fvSUN */
        2005, /* glReplacementCodeuiColor4ubVertex3fSUN */
        2006, /* glReplacementCodeuiColor4ubVertex3fvSUN */
        2007, /* glReplacementCodeuiNormal3fVertex3fSUN */
        2008, /* glReplacementCodeuiNormal3fVertex3fvSUN */
        2010, /* glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN */
        2011, /* glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN */
        2012, /* glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN */
        2013, /* glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN */
        2014, /* glReplacementCodeuiTexCoord2fVertex3fSUN */
        2015, /* glReplacementCodeuiTexCoord2fVertex3fvSUN */
        2016, /* glReplacementCodeuiVertex3fSUN */
        2017, /* glReplacementCodeuiVertex3fvSUN */
        2202, /* glTexCoord2fColor3fVertex3fSUN */
        2203, /* glTexCoord2fColor3fVertex3fvSUN */
        2204, /* glTexCoord2fColor4fNormal3fVertex3fSUN */
        2205, /* glTexCoord2fColor4fNormal3fVertex3fvSUN */
        2206, /* glTexCoord2fColor4ubVertex3fSUN */
        2207, /* glTexCoord2fColor4ubVertex3fvSUN */
        2208, /* glTexCoord2fNormal3fVertex3fSUN */
        2209, /* glTexCoord2fNormal3fVertex3fvSUN */
        2210, /* glTexCoord2fVertex3fSUN */
        2211, /* glTexCoord2fVertex3fvSUN */
        2240, /* glTexCoord4fColor4fNormal3fVertex4fSUN */
        2241, /* glTexCoord4fColor4fNormal3fVertex4fvSUN */
        2242, /* glTexCoord4fVertex4fSUN */
        2243  /* glTexCoord4fVertex4fvSUN */
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
        {    6,    7 }, /* glActiveTexture and glActiveTextureARB */
        {    7,    6 }, /* glActiveTextureARB and glActiveTexture */
        {   20,   21 }, /* glArrayElement and glArrayElementEXT */
        {   21,   20 }, /* glArrayElementEXT and glArrayElement */
        {   26,   27 }, /* glAttachObjectARB and glAttachShader */
        {   27,   26 }, /* glAttachShader and glAttachObjectARB */
        {   29,   30 }, /* glBeginConditionalRender and glBeginConditionalRenderNV */
        {   30,   29 }, /* glBeginConditionalRenderNV and glBeginConditionalRender */
        {   36,   37 }, /* glBeginQuery and glBeginQueryARB */
        {   37,   36 }, /* glBeginQueryARB and glBeginQuery */
        {   39,   40 }, /* glBeginTransformFeedback and glBeginTransformFeedbackEXT */
        {   39,   41 }, /* glBeginTransformFeedback and glBeginTransformFeedbackNV */
        {   40,   39 }, /* glBeginTransformFeedbackEXT and glBeginTransformFeedback */
        {   40,   41 }, /* glBeginTransformFeedbackEXT and glBeginTransformFeedbackNV */
        {   41,   39 }, /* glBeginTransformFeedbackNV and glBeginTransformFeedback */
        {   41,   40 }, /* glBeginTransformFeedbackNV and glBeginTransformFeedbackEXT */
        {   44,   45 }, /* glBindAttribLocation and glBindAttribLocationARB */
        {   45,   44 }, /* glBindAttribLocationARB and glBindAttribLocation */
        {   46,   47 }, /* glBindBuffer and glBindBufferARB */
        {   47,   46 }, /* glBindBufferARB and glBindBuffer */
        {   48,   49 }, /* glBindBufferBase and glBindBufferBaseEXT */
        {   48,   50 }, /* glBindBufferBase and glBindBufferBaseNV */
        {   49,   48 }, /* glBindBufferBaseEXT and glBindBufferBase */
        {   49,   50 }, /* glBindBufferBaseEXT and glBindBufferBaseNV */
        {   50,   48 }, /* glBindBufferBaseNV and glBindBufferBase */
        {   50,   49 }, /* glBindBufferBaseNV and glBindBufferBaseEXT */
        {   51,   52 }, /* glBindBufferOffsetEXT and glBindBufferOffsetNV */
        {   52,   51 }, /* glBindBufferOffsetNV and glBindBufferOffsetEXT */
        {   53,   54 }, /* glBindBufferRange and glBindBufferRangeEXT */
        {   53,   55 }, /* glBindBufferRange and glBindBufferRangeNV */
        {   54,   53 }, /* glBindBufferRangeEXT and glBindBufferRange */
        {   54,   55 }, /* glBindBufferRangeEXT and glBindBufferRangeNV */
        {   55,   53 }, /* glBindBufferRangeNV and glBindBufferRange */
        {   55,   54 }, /* glBindBufferRangeNV and glBindBufferRangeEXT */
        {   58,   59 }, /* glBindFragDataLocation and glBindFragDataLocationEXT */
        {   59,   58 }, /* glBindFragDataLocationEXT and glBindFragDataLocation */
        {   60, 2987 }, /* glBindFragDataLocationIndexed and glBindFragDataLocationIndexedEXT */
        { 2987,   60 }, /* glBindFragDataLocationIndexedEXT and glBindFragDataLocationIndexed */
        {   71,   72 }, /* glBindProgramARB and glBindProgramNV */
        {   72,   71 }, /* glBindProgramNV and glBindProgramARB */
        {   80,   81 }, /* glBindTexture and glBindTextureEXT */
        {   81,   80 }, /* glBindTextureEXT and glBindTexture */
        {   87, 2990 }, /* glBindVertexArray and glBindVertexArrayOES */
        { 2990,   87 }, /* glBindVertexArrayOES and glBindVertexArray */
        { 2991,  107 }, /* glBlendBarrier and glBlendBarrierKHR */
        { 2991,  108 }, /* glBlendBarrier and glBlendBarrierNV */
        {  107, 2991 }, /* glBlendBarrierKHR and glBlendBarrier */
        {  107,  108 }, /* glBlendBarrierKHR and glBlendBarrierNV */
        {  108, 2991 }, /* glBlendBarrierNV and glBlendBarrier */
        {  108,  107 }, /* glBlendBarrierNV and glBlendBarrierKHR */
        {  109,  110 }, /* glBlendColor and glBlendColorEXT */
        {  110,  109 }, /* glBlendColorEXT and glBlendColor */
        {  112,  113 }, /* glBlendEquation and glBlendEquationEXT */
        {  113,  112 }, /* glBlendEquationEXT and glBlendEquation */
        {  120,  114 }, /* glBlendEquationi and glBlendEquationIndexedAMD */
        {  120,  121 }, /* glBlendEquationi and glBlendEquationiARB */
        {  120, 2994 }, /* glBlendEquationi and glBlendEquationiEXT */
        {  120, 2995 }, /* glBlendEquationi and glBlendEquationiOES */
        {  121,  114 }, /* glBlendEquationiARB and glBlendEquationIndexedAMD */
        {  121,  120 }, /* glBlendEquationiARB and glBlendEquationi */
        {  121, 2994 }, /* glBlendEquationiARB and glBlendEquationiEXT */
        {  121, 2995 }, /* glBlendEquationiARB and glBlendEquationiOES */
        { 2994,  114 }, /* glBlendEquationiEXT and glBlendEquationIndexedAMD */
        { 2994,  120 }, /* glBlendEquationiEXT and glBlendEquationi */
        { 2994,  121 }, /* glBlendEquationiEXT and glBlendEquationiARB */
        { 2994, 2995 }, /* glBlendEquationiEXT and glBlendEquationiOES */
        {  114,  120 }, /* glBlendEquationIndexedAMD and glBlendEquationi */
        {  114,  121 }, /* glBlendEquationIndexedAMD and glBlendEquationiARB */
        {  114, 2994 }, /* glBlendEquationIndexedAMD and glBlendEquationiEXT */
        {  114, 2995 }, /* glBlendEquationIndexedAMD and glBlendEquationiOES */
        { 2995,  114 }, /* glBlendEquationiOES and glBlendEquationIndexedAMD */
        { 2995,  120 }, /* glBlendEquationiOES and glBlendEquationi */
        { 2995,  121 }, /* glBlendEquationiOES and glBlendEquationiARB */
        { 2995, 2994 }, /* glBlendEquationiOES and glBlendEquationiEXT */
        {  115,  116 }, /* glBlendEquationSeparate and glBlendEquationSeparateEXT */
        {  116,  115 }, /* glBlendEquationSeparateEXT and glBlendEquationSeparate */
        {  118,  117 }, /* glBlendEquationSeparatei and glBlendEquationSeparateIndexedAMD */
        {  118,  119 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiARB */
        {  118, 2992 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiEXT */
        {  118, 2993 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiOES */
        {  119,  117 }, /* glBlendEquationSeparateiARB and glBlendEquationSeparateIndexedAMD */
        {  119,  118 }, /* glBlendEquationSeparateiARB and glBlendEquationSeparatei */
        {  119, 2992 }, /* glBlendEquationSeparateiARB and glBlendEquationSeparateiEXT */
        {  119, 2993 }, /* glBlendEquationSeparateiARB and glBlendEquationSeparateiOES */
        { 2992,  117 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparateIndexedAMD */
        { 2992,  118 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparatei */
        { 2992,  119 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparateiARB */
        { 2992, 2993 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparateiOES */
        {  117,  118 }, /* glBlendEquationSeparateIndexedAMD and glBlendEquationSeparatei */
        {  117,  119 }, /* glBlendEquationSeparateIndexedAMD and glBlendEquationSeparateiARB */
        {  117, 2992 }, /* glBlendEquationSeparateIndexedAMD and glBlendEquationSeparateiEXT */
        {  117, 2993 }, /* glBlendEquationSeparateIndexedAMD and glBlendEquationSeparateiOES */
        { 2993,  117 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparateIndexedAMD */
        { 2993,  118 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparatei */
        { 2993,  119 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparateiARB */
        { 2993, 2992 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparateiEXT */
        {  130,  123 }, /* glBlendFunci and glBlendFuncIndexedAMD */
        {  130,  131 }, /* glBlendFunci and glBlendFunciARB */
        {  130, 2998 }, /* glBlendFunci and glBlendFunciEXT */
        {  130, 2999 }, /* glBlendFunci and glBlendFunciOES */
        {  131,  123 }, /* glBlendFunciARB and glBlendFuncIndexedAMD */
        {  131,  130 }, /* glBlendFunciARB and glBlendFunci */
        {  131, 2998 }, /* glBlendFunciARB and glBlendFunciEXT */
        {  131, 2999 }, /* glBlendFunciARB and glBlendFunciOES */
        { 2998,  123 }, /* glBlendFunciEXT and glBlendFuncIndexedAMD */
        { 2998,  130 }, /* glBlendFunciEXT and glBlendFunci */
        { 2998,  131 }, /* glBlendFunciEXT and glBlendFunciARB */
        { 2998, 2999 }, /* glBlendFunciEXT and glBlendFunciOES */
        {  123,  130 }, /* glBlendFuncIndexedAMD and glBlendFunci */
        {  123,  131 }, /* glBlendFuncIndexedAMD and glBlendFunciARB */
        {  123, 2998 }, /* glBlendFuncIndexedAMD and glBlendFunciEXT */
        {  123, 2999 }, /* glBlendFuncIndexedAMD and glBlendFunciOES */
        { 2999,  123 }, /* glBlendFunciOES and glBlendFuncIndexedAMD */
        { 2999,  130 }, /* glBlendFunciOES and glBlendFunci */
        { 2999,  131 }, /* glBlendFunciOES and glBlendFunciARB */
        { 2999, 2998 }, /* glBlendFunciOES and glBlendFunciEXT */
        {  124,  125 }, /* glBlendFuncSeparate and glBlendFuncSeparateEXT */
        {  124,  126 }, /* glBlendFuncSeparate and glBlendFuncSeparateINGR */
        {  125,  124 }, /* glBlendFuncSeparateEXT and glBlendFuncSeparate */
        {  125,  126 }, /* glBlendFuncSeparateEXT and glBlendFuncSeparateINGR */
        {  128,  127 }, /* glBlendFuncSeparatei and glBlendFuncSeparateIndexedAMD */
        {  128,  129 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiARB */
        {  128, 2996 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiEXT */
        {  128, 2997 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiOES */
        {  129,  127 }, /* glBlendFuncSeparateiARB and glBlendFuncSeparateIndexedAMD */
        {  129,  128 }, /* glBlendFuncSeparateiARB and glBlendFuncSeparatei */
        {  129, 2996 }, /* glBlendFuncSeparateiARB and glBlendFuncSeparateiEXT */
        {  129, 2997 }, /* glBlendFuncSeparateiARB and glBlendFuncSeparateiOES */
        { 2996,  127 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparateIndexedAMD */
        { 2996,  128 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparatei */
        { 2996,  129 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparateiARB */
        { 2996, 2997 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparateiOES */
        {  127,  128 }, /* glBlendFuncSeparateIndexedAMD and glBlendFuncSeparatei */
        {  127,  129 }, /* glBlendFuncSeparateIndexedAMD and glBlendFuncSeparateiARB */
        {  127, 2996 }, /* glBlendFuncSeparateIndexedAMD and glBlendFuncSeparateiEXT */
        {  127, 2997 }, /* glBlendFuncSeparateIndexedAMD and glBlendFuncSeparateiOES */
        {  126,  124 }, /* glBlendFuncSeparateINGR and glBlendFuncSeparate */
        {  126,  125 }, /* glBlendFuncSeparateINGR and glBlendFuncSeparateEXT */
        { 2997,  127 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparateIndexedAMD */
        { 2997,  128 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparatei */
        { 2997,  129 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparateiARB */
        { 2997, 2996 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparateiEXT */
        {  133,  134 }, /* glBlitFramebuffer and glBlitFramebufferEXT */
        {  133, 3001 }, /* glBlitFramebuffer and glBlitFramebufferNV */
        {  134,  133 }, /* glBlitFramebufferEXT and glBlitFramebuffer */
        {  134, 3001 }, /* glBlitFramebufferEXT and glBlitFramebufferNV */
        { 3001,  133 }, /* glBlitFramebufferNV and glBlitFramebuffer */
        { 3001,  134 }, /* glBlitFramebufferNV and glBlitFramebufferEXT */
        {  140,  141 }, /* glBufferData and glBufferDataARB */
        {  141,  140 }, /* glBufferDataARB and glBufferData */
        {  145, 3002 }, /* glBufferStorage and glBufferStorageEXT */
        { 3002,  145 }, /* glBufferStorageEXT and glBufferStorage */
        {  148,  149 }, /* glBufferSubData and glBufferSubDataARB */
        {  149,  148 }, /* glBufferSubDataARB and glBufferSubData */
        {  153,  154 }, /* glCheckFramebufferStatus and glCheckFramebufferStatusEXT */
        {  154,  153 }, /* glCheckFramebufferStatusEXT and glCheckFramebufferStatus */
        {  157,  158 }, /* glClampColor and glClampColorARB */
        {  158,  157 }, /* glClampColorARB and glClampColor */
        {  174,  175 }, /* glClearDepthf and glClearDepthfOES */
        {  175,  174 }, /* glClearDepthfOES and glClearDepthf */
        {  187, 3004 }, /* glClearTexImage and glClearTexImageEXT */
        { 3004,  187 }, /* glClearTexImageEXT and glClearTexImage */
        {  188, 3005 }, /* glClearTexSubImage and glClearTexSubImageEXT */
        { 3005,  188 }, /* glClearTexSubImageEXT and glClearTexSubImage */
        {  189,  190 }, /* glClientActiveTexture and glClientActiveTextureARB */
        {  190,  189 }, /* glClientActiveTextureARB and glClientActiveTexture */
        {  194, 3006 }, /* glClientWaitSync and glClientWaitSyncAPPLE */
        { 3006,  194 }, /* glClientWaitSyncAPPLE and glClientWaitSync */
        {  195, 3007 }, /* glClipControl and glClipControlEXT */
        { 3007,  195 }, /* glClipControlEXT and glClipControl */
        {  253,  252 }, /* glColorMaski and glColorMaskIndexedEXT */
        {  253, 3008 }, /* glColorMaski and glColorMaskiEXT */
        {  253, 3009 }, /* glColorMaski and glColorMaskiOES */
        { 3008,  252 }, /* glColorMaskiEXT and glColorMaskIndexedEXT */
        { 3008,  253 }, /* glColorMaskiEXT and glColorMaski */
        { 3008, 3009 }, /* glColorMaskiEXT and glColorMaskiOES */
        {  252,  253 }, /* glColorMaskIndexedEXT and glColorMaski */
        {  252, 3008 }, /* glColorMaskIndexedEXT and glColorMaskiEXT */
        {  252, 3009 }, /* glColorMaskIndexedEXT and glColorMaskiOES */
        { 3009,  252 }, /* glColorMaskiOES and glColorMaskIndexedEXT */
        { 3009,  253 }, /* glColorMaskiOES and glColorMaski */
        { 3009, 3008 }, /* glColorMaskiOES and glColorMaskiEXT */
        {  263,  264 }, /* glColorSubTable and glColorSubTableEXT */
        {  264,  263 }, /* glColorSubTableEXT and glColorSubTable */
        {  265,  266 }, /* glColorTable and glColorTableEXT */
        {  265,  271 }, /* glColorTable and glColorTableSGI */
        {  266,  265 }, /* glColorTableEXT and glColorTable */
        {  266,  271 }, /* glColorTableEXT and glColorTableSGI */
        {  267,  268 }, /* glColorTableParameterfv and glColorTableParameterfvSGI */
        {  268,  267 }, /* glColorTableParameterfvSGI and glColorTableParameterfv */
        {  269,  270 }, /* glColorTableParameteriv and glColorTableParameterivSGI */
        {  270,  269 }, /* glColorTableParameterivSGI and glColorTableParameteriv */
        {  271,  265 }, /* glColorTableSGI and glColorTable */
        {  271,  266 }, /* glColorTableSGI and glColorTableEXT */
        {  281,  282 }, /* glCompileShader and glCompileShaderARB */
        {  282,  281 }, /* glCompileShaderARB and glCompileShader */
        {  290,  291 }, /* glCompressedTexImage1D and glCompressedTexImage1DARB */
        {  291,  290 }, /* glCompressedTexImage1DARB and glCompressedTexImage1D */
        {  292,  293 }, /* glCompressedTexImage2D and glCompressedTexImage2DARB */
        {  293,  292 }, /* glCompressedTexImage2DARB and glCompressedTexImage2D */
        {  294,  295 }, /* glCompressedTexImage3D and glCompressedTexImage3DARB */
        {  295,  294 }, /* glCompressedTexImage3DARB and glCompressedTexImage3D */
        {  296,  297 }, /* glCompressedTexSubImage1D and glCompressedTexSubImage1DARB */
        {  297,  296 }, /* glCompressedTexSubImage1DARB and glCompressedTexSubImage1D */
        {  298,  299 }, /* glCompressedTexSubImage2D and glCompressedTexSubImage2DARB */
        {  299,  298 }, /* glCompressedTexSubImage2DARB and glCompressedTexSubImage2D */
        {  300,  301 }, /* glCompressedTexSubImage3D and glCompressedTexSubImage3DARB */
        {  301,  300 }, /* glCompressedTexSubImage3DARB and glCompressedTexSubImage3D */
        {  313,  314 }, /* glConvolutionFilter1D and glConvolutionFilter1DEXT */
        {  314,  313 }, /* glConvolutionFilter1DEXT and glConvolutionFilter1D */
        {  315,  316 }, /* glConvolutionFilter2D and glConvolutionFilter2DEXT */
        {  316,  315 }, /* glConvolutionFilter2DEXT and glConvolutionFilter2D */
        {  317,  318 }, /* glConvolutionParameterf and glConvolutionParameterfEXT */
        {  318,  317 }, /* glConvolutionParameterfEXT and glConvolutionParameterf */
        {  319,  320 }, /* glConvolutionParameterfv and glConvolutionParameterfvEXT */
        {  320,  319 }, /* glConvolutionParameterfvEXT and glConvolutionParameterfv */
        {  321,  322 }, /* glConvolutionParameteri and glConvolutionParameteriEXT */
        {  322,  321 }, /* glConvolutionParameteriEXT and glConvolutionParameteri */
        {  323,  324 }, /* glConvolutionParameteriv and glConvolutionParameterivEXT */
        {  324,  323 }, /* glConvolutionParameterivEXT and glConvolutionParameteriv */
        {  327, 3017 }, /* glCopyBufferSubData and glCopyBufferSubDataNV */
        { 3017,  327 }, /* glCopyBufferSubDataNV and glCopyBufferSubData */
        {  328,  329 }, /* glCopyColorSubTable and glCopyColorSubTableEXT */
        {  329,  328 }, /* glCopyColorSubTableEXT and glCopyColorSubTable */
        {  330,  331 }, /* glCopyColorTable and glCopyColorTableSGI */
        {  331,  330 }, /* glCopyColorTableSGI and glCopyColorTable */
        {  332,  333 }, /* glCopyConvolutionFilter1D and glCopyConvolutionFilter1DEXT */
        {  333,  332 }, /* glCopyConvolutionFilter1DEXT and glCopyConvolutionFilter1D */
        {  334,  335 }, /* glCopyConvolutionFilter2D and glCopyConvolutionFilter2DEXT */
        {  335,  334 }, /* glCopyConvolutionFilter2DEXT and glCopyConvolutionFilter2D */
        {  336, 3018 }, /* glCopyImageSubData and glCopyImageSubDataEXT */
        {  336, 3019 }, /* glCopyImageSubData and glCopyImageSubDataOES */
        { 3018,  336 }, /* glCopyImageSubDataEXT and glCopyImageSubData */
        { 3018, 3019 }, /* glCopyImageSubDataEXT and glCopyImageSubDataOES */
        { 3019,  336 }, /* glCopyImageSubDataOES and glCopyImageSubData */
        { 3019, 3018 }, /* glCopyImageSubDataOES and glCopyImageSubDataEXT */
        {  346,  347 }, /* glCopyTexImage1D and glCopyTexImage1DEXT */
        {  347,  346 }, /* glCopyTexImage1DEXT and glCopyTexImage1D */
        {  348,  349 }, /* glCopyTexImage2D and glCopyTexImage2DEXT */
        {  349,  348 }, /* glCopyTexImage2DEXT and glCopyTexImage2D */
        {  350,  351 }, /* glCopyTexSubImage1D and glCopyTexSubImage1DEXT */
        {  351,  350 }, /* glCopyTexSubImage1DEXT and glCopyTexSubImage1D */
        {  352,  353 }, /* glCopyTexSubImage2D and glCopyTexSubImage2DEXT */
        {  353,  352 }, /* glCopyTexSubImage2DEXT and glCopyTexSubImage2D */
        {  354,  355 }, /* glCopyTexSubImage3D and glCopyTexSubImage3DEXT */
        {  355,  354 }, /* glCopyTexSubImage3DEXT and glCopyTexSubImage3D */
        {  375,  376 }, /* glCreateProgram and glCreateProgramObjectARB */
        {  376,  375 }, /* glCreateProgramObjectARB and glCreateProgram */
        {  383,  384 }, /* glCreateShader and glCreateShaderObjectARB */
        {  384,  383 }, /* glCreateShaderObjectARB and glCreateShader */
        {  396,  398 }, /* glDebugMessageCallback and glDebugMessageCallbackARB */
        {  396, 3030 }, /* glDebugMessageCallback and glDebugMessageCallbackKHR */
        {  398,  396 }, /* glDebugMessageCallbackARB and glDebugMessageCallback */
        {  398, 3030 }, /* glDebugMessageCallbackARB and glDebugMessageCallbackKHR */
        { 3030,  396 }, /* glDebugMessageCallbackKHR and glDebugMessageCallback */
        { 3030,  398 }, /* glDebugMessageCallbackKHR and glDebugMessageCallbackARB */
        {  399,  400 }, /* glDebugMessageControl and glDebugMessageControlARB */
        {  399, 3031 }, /* glDebugMessageControl and glDebugMessageControlKHR */
        {  400,  399 }, /* glDebugMessageControlARB and glDebugMessageControl */
        {  400, 3031 }, /* glDebugMessageControlARB and glDebugMessageControlKHR */
        { 3031,  399 }, /* glDebugMessageControlKHR and glDebugMessageControl */
        { 3031,  400 }, /* glDebugMessageControlKHR and glDebugMessageControlARB */
        {  402,  404 }, /* glDebugMessageInsert and glDebugMessageInsertARB */
        {  402, 3032 }, /* glDebugMessageInsert and glDebugMessageInsertKHR */
        {  404,  402 }, /* glDebugMessageInsertARB and glDebugMessageInsert */
        {  404, 3032 }, /* glDebugMessageInsertARB and glDebugMessageInsertKHR */
        { 3032,  402 }, /* glDebugMessageInsertKHR and glDebugMessageInsert */
        { 3032,  404 }, /* glDebugMessageInsertKHR and glDebugMessageInsertARB */
        {  409,  410 }, /* glDeleteBuffers and glDeleteBuffersARB */
        {  410,  409 }, /* glDeleteBuffersARB and glDeleteBuffers */
        {  415,  416 }, /* glDeleteFramebuffers and glDeleteFramebuffersEXT */
        {  416,  415 }, /* glDeleteFramebuffersEXT and glDeleteFramebuffers */
        {  428,  429 }, /* glDeleteProgramsARB and glDeleteProgramsNV */
        {  429,  428 }, /* glDeleteProgramsNV and glDeleteProgramsARB */
        {  430,  431 }, /* glDeleteQueries and glDeleteQueriesARB */
        {  431,  430 }, /* glDeleteQueriesARB and glDeleteQueries */
        {  433,  434 }, /* glDeleteRenderbuffers and glDeleteRenderbuffersEXT */
        {  434,  433 }, /* glDeleteRenderbuffersEXT and glDeleteRenderbuffers */
        {  439, 3035 }, /* glDeleteSync and glDeleteSyncAPPLE */
        { 3035,  439 }, /* glDeleteSyncAPPLE and glDeleteSync */
        {  442,  443 }, /* glDeleteTransformFeedbacks and glDeleteTransformFeedbacksNV */
        {  443,  442 }, /* glDeleteTransformFeedbacksNV and glDeleteTransformFeedbacks */
        {  444,  445 }, /* glDeleteVertexArrays and glDeleteVertexArraysAPPLE */
        {  444, 3036 }, /* glDeleteVertexArrays and glDeleteVertexArraysOES */
        {  445,  444 }, /* glDeleteVertexArraysAPPLE and glDeleteVertexArrays */
        {  445, 3036 }, /* glDeleteVertexArraysAPPLE and glDeleteVertexArraysOES */
        { 3036,  444 }, /* glDeleteVertexArraysOES and glDeleteVertexArrays */
        { 3036,  445 }, /* glDeleteVertexArraysOES and glDeleteVertexArraysAPPLE */
        {  457,  458 }, /* glDepthRangef and glDepthRangefOES */
        {  458,  457 }, /* glDepthRangefOES and glDepthRangef */
        {  460,  461 }, /* glDetachObjectARB and glDetachShader */
        {  461,  460 }, /* glDetachShader and glDetachObjectARB */
        {  475,  467 }, /* glDisablei and glDisableIndexedEXT */
        {  475, 3043 }, /* glDisablei and glDisableiEXT */
        {  475, 3044 }, /* glDisablei and glDisableiNV */
        {  475, 3045 }, /* glDisablei and glDisableiOES */
        { 3043,  467 }, /* glDisableiEXT and glDisableIndexedEXT */
        { 3043,  475 }, /* glDisableiEXT and glDisablei */
        { 3043, 3044 }, /* glDisableiEXT and glDisableiNV */
        { 3043, 3045 }, /* glDisableiEXT and glDisableiOES */
        {  467,  475 }, /* glDisableIndexedEXT and glDisablei */
        {  467, 3043 }, /* glDisableIndexedEXT and glDisableiEXT */
        {  467, 3044 }, /* glDisableIndexedEXT and glDisableiNV */
        {  467, 3045 }, /* glDisableIndexedEXT and glDisableiOES */
        { 3044,  467 }, /* glDisableiNV and glDisableIndexedEXT */
        { 3044,  475 }, /* glDisableiNV and glDisablei */
        { 3044, 3043 }, /* glDisableiNV and glDisableiEXT */
        { 3044, 3045 }, /* glDisableiNV and glDisableiOES */
        { 3045,  467 }, /* glDisableiOES and glDisableIndexedEXT */
        { 3045,  475 }, /* glDisableiOES and glDisablei */
        { 3045, 3043 }, /* glDisableiOES and glDisableiEXT */
        { 3045, 3044 }, /* glDisableiOES and glDisableiNV */
        {  473,  474 }, /* glDisableVertexAttribArray and glDisableVertexAttribArrayARB */
        {  474,  473 }, /* glDisableVertexAttribArrayARB and glDisableVertexAttribArray */
        {  479,  480 }, /* glDrawArrays and glDrawArraysEXT */
        {  480,  479 }, /* glDrawArraysEXT and glDrawArrays */
        {  482, 3047 }, /* glDrawArraysInstanced and glDrawArraysInstancedANGLE */
        {  482,  483 }, /* glDrawArraysInstanced and glDrawArraysInstancedARB */
        {  482,  485 }, /* glDrawArraysInstanced and glDrawArraysInstancedEXT */
        {  482, 3050 }, /* glDrawArraysInstanced and glDrawArraysInstancedNV */
        { 3047,  482 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstanced */
        { 3047,  483 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstancedARB */
        { 3047,  485 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstancedEXT */
        { 3047, 3050 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstancedNV */
        {  483,  482 }, /* glDrawArraysInstancedARB and glDrawArraysInstanced */
        {  483, 3047 }, /* glDrawArraysInstancedARB and glDrawArraysInstancedANGLE */
        {  483,  485 }, /* glDrawArraysInstancedARB and glDrawArraysInstancedEXT */
        {  483, 3050 }, /* glDrawArraysInstancedARB and glDrawArraysInstancedNV */
        {  484, 3049 }, /* glDrawArraysInstancedBaseInstance and glDrawArraysInstancedBaseInstanceEXT */
        { 3049,  484 }, /* glDrawArraysInstancedBaseInstanceEXT and glDrawArraysInstancedBaseInstance */
        {  485,  482 }, /* glDrawArraysInstancedEXT and glDrawArraysInstanced */
        {  485, 3047 }, /* glDrawArraysInstancedEXT and glDrawArraysInstancedANGLE */
        {  485,  483 }, /* glDrawArraysInstancedEXT and glDrawArraysInstancedARB */
        {  485, 3050 }, /* glDrawArraysInstancedEXT and glDrawArraysInstancedNV */
        { 3050,  482 }, /* glDrawArraysInstancedNV and glDrawArraysInstanced */
        { 3050, 3047 }, /* glDrawArraysInstancedNV and glDrawArraysInstancedANGLE */
        { 3050,  483 }, /* glDrawArraysInstancedNV and glDrawArraysInstancedARB */
        { 3050,  485 }, /* glDrawArraysInstancedNV and glDrawArraysInstancedEXT */
        {  487,  488 }, /* glDrawBuffers and glDrawBuffersARB */
        {  487,  489 }, /* glDrawBuffers and glDrawBuffersATI */
        {  487, 3051 }, /* glDrawBuffers and glDrawBuffersEXT */
        {  488,  487 }, /* glDrawBuffersARB and glDrawBuffers */
        {  488,  489 }, /* glDrawBuffersARB and glDrawBuffersATI */
        {  488, 3051 }, /* glDrawBuffersARB and glDrawBuffersEXT */
        {  489,  487 }, /* glDrawBuffersATI and glDrawBuffers */
        {  489,  488 }, /* glDrawBuffersATI and glDrawBuffersARB */
        {  489, 3051 }, /* glDrawBuffersATI and glDrawBuffersEXT */
        { 3051,  487 }, /* glDrawBuffersEXT and glDrawBuffers */
        { 3051,  488 }, /* glDrawBuffersEXT and glDrawBuffersARB */
        { 3051,  489 }, /* glDrawBuffersEXT and glDrawBuffersATI */
        {  497, 3054 }, /* glDrawElementsBaseVertex and glDrawElementsBaseVertexEXT */
        {  497, 3055 }, /* glDrawElementsBaseVertex and glDrawElementsBaseVertexOES */
        { 3054,  497 }, /* glDrawElementsBaseVertexEXT and glDrawElementsBaseVertex */
        { 3054, 3055 }, /* glDrawElementsBaseVertexEXT and glDrawElementsBaseVertexOES */
        { 3055,  497 }, /* glDrawElementsBaseVertexOES and glDrawElementsBaseVertex */
        { 3055, 3054 }, /* glDrawElementsBaseVertexOES and glDrawElementsBaseVertexEXT */
        {  499, 3056 }, /* glDrawElementsInstanced and glDrawElementsInstancedANGLE */
        {  499,  500 }, /* glDrawElementsInstanced and glDrawElementsInstancedARB */
        {  499,  504 }, /* glDrawElementsInstanced and glDrawElementsInstancedEXT */
        {  499, 3062 }, /* glDrawElementsInstanced and glDrawElementsInstancedNV */
        { 3056,  499 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstanced */
        { 3056,  500 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstancedARB */
        { 3056,  504 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstancedEXT */
        { 3056, 3062 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstancedNV */
        {  500,  499 }, /* glDrawElementsInstancedARB and glDrawElementsInstanced */
        {  500, 3056 }, /* glDrawElementsInstancedARB and glDrawElementsInstancedANGLE */
        {  500,  504 }, /* glDrawElementsInstancedARB and glDrawElementsInstancedEXT */
        {  500, 3062 }, /* glDrawElementsInstancedARB and glDrawElementsInstancedNV */
        {  501, 3057 }, /* glDrawElementsInstancedBaseInstance and glDrawElementsInstancedBaseInstanceEXT */
        { 3057,  501 }, /* glDrawElementsInstancedBaseInstanceEXT and glDrawElementsInstancedBaseInstance */
        {  502, 3060 }, /* glDrawElementsInstancedBaseVertex and glDrawElementsInstancedBaseVertexEXT */
        {  502, 3061 }, /* glDrawElementsInstancedBaseVertex and glDrawElementsInstancedBaseVertexOES */
        {  503, 3059 }, /* glDrawElementsInstancedBaseVertexBaseInstance and glDrawElementsInstancedBaseVertexBaseInstanceEXT */
        { 3059,  503 }, /* glDrawElementsInstancedBaseVertexBaseInstanceEXT and glDrawElementsInstancedBaseVertexBaseInstance */
        { 3060,  502 }, /* glDrawElementsInstancedBaseVertexEXT and glDrawElementsInstancedBaseVertex */
        { 3060, 3061 }, /* glDrawElementsInstancedBaseVertexEXT and glDrawElementsInstancedBaseVertexOES */
        { 3061,  502 }, /* glDrawElementsInstancedBaseVertexOES and glDrawElementsInstancedBaseVertex */
        { 3061, 3060 }, /* glDrawElementsInstancedBaseVertexOES and glDrawElementsInstancedBaseVertexEXT */
        {  504,  499 }, /* glDrawElementsInstancedEXT and glDrawElementsInstanced */
        {  504, 3056 }, /* glDrawElementsInstancedEXT and glDrawElementsInstancedANGLE */
        {  504,  500 }, /* glDrawElementsInstancedEXT and glDrawElementsInstancedARB */
        {  504, 3062 }, /* glDrawElementsInstancedEXT and glDrawElementsInstancedNV */
        { 3062,  499 }, /* glDrawElementsInstancedNV and glDrawElementsInstanced */
        { 3062, 3056 }, /* glDrawElementsInstancedNV and glDrawElementsInstancedANGLE */
        { 3062,  500 }, /* glDrawElementsInstancedNV and glDrawElementsInstancedARB */
        { 3062,  504 }, /* glDrawElementsInstancedNV and glDrawElementsInstancedEXT */
        {  511,  513 }, /* glDrawRangeElements and glDrawRangeElementsEXT */
        {  512, 3063 }, /* glDrawRangeElementsBaseVertex and glDrawRangeElementsBaseVertexEXT */
        {  512, 3064 }, /* glDrawRangeElementsBaseVertex and glDrawRangeElementsBaseVertexOES */
        { 3063,  512 }, /* glDrawRangeElementsBaseVertexEXT and glDrawRangeElementsBaseVertex */
        { 3063, 3064 }, /* glDrawRangeElementsBaseVertexEXT and glDrawRangeElementsBaseVertexOES */
        { 3064,  512 }, /* glDrawRangeElementsBaseVertexOES and glDrawRangeElementsBaseVertex */
        { 3064, 3063 }, /* glDrawRangeElementsBaseVertexOES and glDrawRangeElementsBaseVertexEXT */
        {  513,  511 }, /* glDrawRangeElementsEXT and glDrawRangeElements */
        {  515, 3065 }, /* glDrawTransformFeedback and glDrawTransformFeedbackEXT */
        {  515,  517 }, /* glDrawTransformFeedback and glDrawTransformFeedbackNV */
        { 3065,  515 }, /* glDrawTransformFeedbackEXT and glDrawTransformFeedback */
        { 3065,  517 }, /* glDrawTransformFeedbackEXT and glDrawTransformFeedbackNV */
        {  516, 3066 }, /* glDrawTransformFeedbackInstanced and glDrawTransformFeedbackInstancedEXT */
        { 3066,  516 }, /* glDrawTransformFeedbackInstancedEXT and glDrawTransformFeedbackInstanced */
        {  517,  515 }, /* glDrawTransformFeedbackNV and glDrawTransformFeedback */
        {  517, 3065 }, /* glDrawTransformFeedbackNV and glDrawTransformFeedbackEXT */
        {  543,  535 }, /* glEnablei and glEnableIndexedEXT */
        {  543, 3070 }, /* glEnablei and glEnableiEXT */
        {  543, 3071 }, /* glEnablei and glEnableiNV */
        {  543, 3072 }, /* glEnablei and glEnableiOES */
        { 3070,  535 }, /* glEnableiEXT and glEnableIndexedEXT */
        { 3070,  543 }, /* glEnableiEXT and glEnablei */
        { 3070, 3071 }, /* glEnableiEXT and glEnableiNV */
        { 3070, 3072 }, /* glEnableiEXT and glEnableiOES */
        {  535,  543 }, /* glEnableIndexedEXT and glEnablei */
        {  535, 3070 }, /* glEnableIndexedEXT and glEnableiEXT */
        {  535, 3071 }, /* glEnableIndexedEXT and glEnableiNV */
        {  535, 3072 }, /* glEnableIndexedEXT and glEnableiOES */
        { 3071,  535 }, /* glEnableiNV and glEnableIndexedEXT */
        { 3071,  543 }, /* glEnableiNV and glEnablei */
        { 3071, 3070 }, /* glEnableiNV and glEnableiEXT */
        { 3071, 3072 }, /* glEnableiNV and glEnableiOES */
        { 3072,  535 }, /* glEnableiOES and glEnableIndexedEXT */
        { 3072,  543 }, /* glEnableiOES and glEnablei */
        { 3072, 3070 }, /* glEnableiOES and glEnableiEXT */
        { 3072, 3071 }, /* glEnableiOES and glEnableiNV */
        {  541,  542 }, /* glEnableVertexAttribArray and glEnableVertexAttribArrayARB */
        {  542,  541 }, /* glEnableVertexAttribArrayARB and glEnableVertexAttribArray */
        {  545,  546 }, /* glEndConditionalRender and glEndConditionalRenderNV */
        {  545,  547 }, /* glEndConditionalRender and glEndConditionalRenderNVX */
        {  546,  545 }, /* glEndConditionalRenderNV and glEndConditionalRender */
        {  546,  547 }, /* glEndConditionalRenderNV and glEndConditionalRenderNVX */
        {  547,  545 }, /* glEndConditionalRenderNVX and glEndConditionalRender */
        {  547,  546 }, /* glEndConditionalRenderNVX and glEndConditionalRenderNV */
        {  553,  554 }, /* glEndQuery and glEndQueryARB */
        {  554,  553 }, /* glEndQueryARB and glEndQuery */
        {  556,  557 }, /* glEndTransformFeedback and glEndTransformFeedbackEXT */
        {  556,  558 }, /* glEndTransformFeedback and glEndTransformFeedbackNV */
        {  557,  556 }, /* glEndTransformFeedbackEXT and glEndTransformFeedback */
        {  557,  558 }, /* glEndTransformFeedbackEXT and glEndTransformFeedbackNV */
        {  558,  556 }, /* glEndTransformFeedbackNV and glEndTransformFeedback */
        {  558,  557 }, /* glEndTransformFeedbackNV and glEndTransformFeedbackEXT */
        {  583, 3089 }, /* glFenceSync and glFenceSyncAPPLE */
        { 3089,  583 }, /* glFenceSyncAPPLE and glFenceSync */
        {  592,  593 }, /* glFlushMappedBufferRange and glFlushMappedBufferRangeAPPLE */
        {  592, 3090 }, /* glFlushMappedBufferRange and glFlushMappedBufferRangeEXT */
        {  593,  592 }, /* glFlushMappedBufferRangeAPPLE and glFlushMappedBufferRange */
        {  593, 3090 }, /* glFlushMappedBufferRangeAPPLE and glFlushMappedBufferRangeEXT */
        { 3090,  592 }, /* glFlushMappedBufferRangeEXT and glFlushMappedBufferRange */
        { 3090,  593 }, /* glFlushMappedBufferRangeEXT and glFlushMappedBufferRangeAPPLE */
        {  605,  606 }, /* glFogCoordd and glFogCoorddEXT */
        {  606,  605 }, /* glFogCoorddEXT and glFogCoordd */
        {  607,  608 }, /* glFogCoorddv and glFogCoorddvEXT */
        {  608,  607 }, /* glFogCoorddvEXT and glFogCoorddv */
        {  609,  610 }, /* glFogCoordf and glFogCoordfEXT */
        {  610,  609 }, /* glFogCoordfEXT and glFogCoordf */
        {  611,  612 }, /* glFogCoordfv and glFogCoordfvEXT */
        {  612,  611 }, /* glFogCoordfvEXT and glFogCoordfv */
        {  602,  603 }, /* glFogCoordPointer and glFogCoordPointerEXT */
        {  603,  602 }, /* glFogCoordPointerEXT and glFogCoordPointer */
        {  644,  645 }, /* glFramebufferRenderbuffer and glFramebufferRenderbufferEXT */
        {  645,  644 }, /* glFramebufferRenderbufferEXT and glFramebufferRenderbuffer */
        {  649,  656 }, /* glFramebufferTexture and glFramebufferTextureARB */
        {  649,  657 }, /* glFramebufferTexture and glFramebufferTextureEXT */
        {  649, 3108 }, /* glFramebufferTexture and glFramebufferTextureOES */
        {  650,  651 }, /* glFramebufferTexture1D and glFramebufferTexture1DEXT */
        {  651,  650 }, /* glFramebufferTexture1DEXT and glFramebufferTexture1D */
        {  652,  653 }, /* glFramebufferTexture2D and glFramebufferTexture2DEXT */
        {  653,  652 }, /* glFramebufferTexture2DEXT and glFramebufferTexture2D */
        {  654,  655 }, /* glFramebufferTexture3D and glFramebufferTexture3DEXT */
        {  655,  654 }, /* glFramebufferTexture3DEXT and glFramebufferTexture3D */
        {  656,  649 }, /* glFramebufferTextureARB and glFramebufferTexture */
        {  656,  657 }, /* glFramebufferTextureARB and glFramebufferTextureEXT */
        {  656, 3108 }, /* glFramebufferTextureARB and glFramebufferTextureOES */
        {  657,  649 }, /* glFramebufferTextureEXT and glFramebufferTexture */
        {  657,  656 }, /* glFramebufferTextureEXT and glFramebufferTextureARB */
        {  657, 3108 }, /* glFramebufferTextureEXT and glFramebufferTextureOES */
        {  658,  659 }, /* glFramebufferTextureFaceARB and glFramebufferTextureFaceEXT */
        {  659,  658 }, /* glFramebufferTextureFaceEXT and glFramebufferTextureFaceARB */
        {  660,  661 }, /* glFramebufferTextureLayer and glFramebufferTextureLayerARB */
        {  660,  662 }, /* glFramebufferTextureLayer and glFramebufferTextureLayerEXT */
        {  661,  660 }, /* glFramebufferTextureLayerARB and glFramebufferTextureLayer */
        {  661,  662 }, /* glFramebufferTextureLayerARB and glFramebufferTextureLayerEXT */
        {  662,  660 }, /* glFramebufferTextureLayerEXT and glFramebufferTextureLayer */
        {  662,  661 }, /* glFramebufferTextureLayerEXT and glFramebufferTextureLayerARB */
        { 3108,  649 }, /* glFramebufferTextureOES and glFramebufferTexture */
        { 3108,  656 }, /* glFramebufferTextureOES and glFramebufferTextureARB */
        { 3108,  657 }, /* glFramebufferTextureOES and glFramebufferTextureEXT */
        {  670,  671 }, /* glGenBuffers and glGenBuffersARB */
        {  671,  670 }, /* glGenBuffersARB and glGenBuffers */
        {  700,  701 }, /* glGenerateMipmap and glGenerateMipmapEXT */
        {  701,  700 }, /* glGenerateMipmapEXT and glGenerateMipmap */
        {  675,  676 }, /* glGenFramebuffers and glGenFramebuffersEXT */
        {  676,  675 }, /* glGenFramebuffersEXT and glGenFramebuffers */
        {  683,  684 }, /* glGenProgramsARB and glGenProgramsNV */
        {  684,  683 }, /* glGenProgramsNV and glGenProgramsARB */
        {  685,  686 }, /* glGenQueries and glGenQueriesARB */
        {  686,  685 }, /* glGenQueriesARB and glGenQueries */
        {  688,  689 }, /* glGenRenderbuffers and glGenRenderbuffersEXT */
        {  689,  688 }, /* glGenRenderbuffersEXT and glGenRenderbuffers */
        {  695,  696 }, /* glGenTransformFeedbacks and glGenTransformFeedbacksNV */
        {  696,  695 }, /* glGenTransformFeedbacksNV and glGenTransformFeedbacks */
        {  697,  698 }, /* glGenVertexArrays and glGenVertexArraysAPPLE */
        {  697, 3112 }, /* glGenVertexArrays and glGenVertexArraysOES */
        {  698,  697 }, /* glGenVertexArraysAPPLE and glGenVertexArrays */
        {  698, 3112 }, /* glGenVertexArraysAPPLE and glGenVertexArraysOES */
        { 3112,  697 }, /* glGenVertexArraysOES and glGenVertexArrays */
        { 3112,  698 }, /* glGenVertexArraysOES and glGenVertexArraysAPPLE */
        {  706,  707 }, /* glGetActiveAttrib and glGetActiveAttribARB */
        {  707,  706 }, /* glGetActiveAttribARB and glGetActiveAttrib */
        {  711,  712 }, /* glGetActiveUniform and glGetActiveUniformARB */
        {  712,  711 }, /* glGetActiveUniformARB and glGetActiveUniform */
        {  722,  723 }, /* glGetAttribLocation and glGetAttribLocationARB */
        {  723,  722 }, /* glGetAttribLocationARB and glGetAttribLocation */
        {  725,  724 }, /* glGetBooleani_v and glGetBooleanIndexedvEXT */
        {  724,  725 }, /* glGetBooleanIndexedvEXT and glGetBooleani_v */
        {  728,  729 }, /* glGetBufferParameteriv and glGetBufferParameterivARB */
        {  729,  728 }, /* glGetBufferParameterivARB and glGetBufferParameteriv */
        {  731,  732 }, /* glGetBufferPointerv and glGetBufferPointervARB */
        {  731, 3118 }, /* glGetBufferPointerv and glGetBufferPointervOES */
        {  732,  731 }, /* glGetBufferPointervARB and glGetBufferPointerv */
        {  732, 3118 }, /* glGetBufferPointervARB and glGetBufferPointervOES */
        { 3118,  731 }, /* glGetBufferPointervOES and glGetBufferPointerv */
        { 3118,  732 }, /* glGetBufferPointervOES and glGetBufferPointervARB */
        {  733,  734 }, /* glGetBufferSubData and glGetBufferSubDataARB */
        {  734,  733 }, /* glGetBufferSubDataARB and glGetBufferSubData */
        {  738,  739 }, /* glGetColorTable and glGetColorTableEXT */
        {  739,  738 }, /* glGetColorTableEXT and glGetColorTable */
        {  740,  741 }, /* glGetColorTableParameterfv and glGetColorTableParameterfvEXT */
        {  741,  740 }, /* glGetColorTableParameterfvEXT and glGetColorTableParameterfv */
        {  743,  744 }, /* glGetColorTableParameteriv and glGetColorTableParameterivEXT */
        {  744,  743 }, /* glGetColorTableParameterivEXT and glGetColorTableParameteriv */
        {  754,  755 }, /* glGetCompressedTexImage and glGetCompressedTexImageARB */
        {  755,  754 }, /* glGetCompressedTexImageARB and glGetCompressedTexImage */
        {  767,  769 }, /* glGetDebugMessageLog and glGetDebugMessageLogARB */
        {  767, 3121 }, /* glGetDebugMessageLog and glGetDebugMessageLogKHR */
        {  769,  767 }, /* glGetDebugMessageLogARB and glGetDebugMessageLog */
        {  769, 3121 }, /* glGetDebugMessageLogARB and glGetDebugMessageLogKHR */
        { 3121,  767 }, /* glGetDebugMessageLogKHR and glGetDebugMessageLog */
        { 3121,  769 }, /* glGetDebugMessageLogKHR and glGetDebugMessageLogARB */
        {  772,  771 }, /* glGetDoublei_v and glGetDoubleIndexedvEXT */
        {  772,  773 }, /* glGetDoublei_v and glGetDoublei_vEXT */
        {  773,  771 }, /* glGetDoublei_vEXT and glGetDoubleIndexedvEXT */
        {  773,  772 }, /* glGetDoublei_vEXT and glGetDoublei_v */
        {  771,  772 }, /* glGetDoubleIndexedvEXT and glGetDoublei_v */
        {  771,  773 }, /* glGetDoubleIndexedvEXT and glGetDoublei_vEXT */
        {  782,  781 }, /* glGetFloati_v and glGetFloatIndexedvEXT */
        {  782,  783 }, /* glGetFloati_v and glGetFloati_vEXT */
        {  782, 3124 }, /* glGetFloati_v and glGetFloati_vNV */
        {  782, 3125 }, /* glGetFloati_v and glGetFloati_vOES */
        {  783,  781 }, /* glGetFloati_vEXT and glGetFloatIndexedvEXT */
        {  783,  782 }, /* glGetFloati_vEXT and glGetFloati_v */
        {  783, 3124 }, /* glGetFloati_vEXT and glGetFloati_vNV */
        {  783, 3125 }, /* glGetFloati_vEXT and glGetFloati_vOES */
        { 3124,  781 }, /* glGetFloati_vNV and glGetFloatIndexedvEXT */
        { 3124,  782 }, /* glGetFloati_vNV and glGetFloati_v */
        { 3124,  783 }, /* glGetFloati_vNV and glGetFloati_vEXT */
        { 3124, 3125 }, /* glGetFloati_vNV and glGetFloati_vOES */
        { 3125,  781 }, /* glGetFloati_vOES and glGetFloatIndexedvEXT */
        { 3125,  782 }, /* glGetFloati_vOES and glGetFloati_v */
        { 3125,  783 }, /* glGetFloati_vOES and glGetFloati_vEXT */
        { 3125, 3124 }, /* glGetFloati_vOES and glGetFloati_vNV */
        {  781,  782 }, /* glGetFloatIndexedvEXT and glGetFloati_v */
        {  781,  783 }, /* glGetFloatIndexedvEXT and glGetFloati_vEXT */
        {  781, 3124 }, /* glGetFloatIndexedvEXT and glGetFloati_vNV */
        {  781, 3125 }, /* glGetFloatIndexedvEXT and glGetFloati_vOES */
        {  786, 3127 }, /* glGetFragDataIndex and glGetFragDataIndexEXT */
        { 3127,  786 }, /* glGetFragDataIndexEXT and glGetFragDataIndex */
        {  787,  788 }, /* glGetFragDataLocation and glGetFragDataLocationEXT */
        {  788,  787 }, /* glGetFragDataLocationEXT and glGetFragDataLocation */
        {  793,  794 }, /* glGetFramebufferAttachmentParameteriv and glGetFramebufferAttachmentParameterivEXT */
        {  794,  793 }, /* glGetFramebufferAttachmentParameterivEXT and glGetFramebufferAttachmentParameteriv */
        {  799, 3136 }, /* glGetGraphicsResetStatus and glGetGraphicsResetStatusEXT */
        {  799, 3137 }, /* glGetGraphicsResetStatus and glGetGraphicsResetStatusKHR */
        { 3136,  799 }, /* glGetGraphicsResetStatusEXT and glGetGraphicsResetStatus */
        { 3136, 3137 }, /* glGetGraphicsResetStatusEXT and glGetGraphicsResetStatusKHR */
        { 3137,  799 }, /* glGetGraphicsResetStatusKHR and glGetGraphicsResetStatus */
        { 3137, 3136 }, /* glGetGraphicsResetStatusKHR and glGetGraphicsResetStatusEXT */
        {  816, 3139 }, /* glGetInteger64v and glGetInteger64vAPPLE */
        {  816, 3140 }, /* glGetInteger64v and glGetInteger64vEXT */
        { 3139,  816 }, /* glGetInteger64vAPPLE and glGetInteger64v */
        { 3139, 3140 }, /* glGetInteger64vAPPLE and glGetInteger64vEXT */
        { 3140,  816 }, /* glGetInteger64vEXT and glGetInteger64v */
        { 3140, 3139 }, /* glGetInteger64vEXT and glGetInteger64vAPPLE */
        {  818,  817 }, /* glGetIntegeri_v and glGetIntegerIndexedvEXT */
        {  817,  818 }, /* glGetIntegerIndexedvEXT and glGetIntegeri_v */
        {  868,  869 }, /* glGetMultisamplefv and glGetMultisamplefvNV */
        {  869,  868 }, /* glGetMultisamplefvNV and glGetMultisamplefv */
        { 1153, 3200 }, /* glGetnUniformfv and glGetnUniformfvEXT */
        { 1153, 3201 }, /* glGetnUniformfv and glGetnUniformfvKHR */
        { 3200, 1153 }, /* glGetnUniformfvEXT and glGetnUniformfv */
        { 3200, 3201 }, /* glGetnUniformfvEXT and glGetnUniformfvKHR */
        { 3201, 1153 }, /* glGetnUniformfvKHR and glGetnUniformfv */
        { 3201, 3200 }, /* glGetnUniformfvKHR and glGetnUniformfvEXT */
        { 1156, 3203 }, /* glGetnUniformiv and glGetnUniformivEXT */
        { 1156, 3204 }, /* glGetnUniformiv and glGetnUniformivKHR */
        { 3203, 1156 }, /* glGetnUniformivEXT and glGetnUniformiv */
        { 3203, 3204 }, /* glGetnUniformivEXT and glGetnUniformivKHR */
        { 3204, 1156 }, /* glGetnUniformivKHR and glGetnUniformiv */
        { 3204, 3203 }, /* glGetnUniformivKHR and glGetnUniformivEXT */
        { 1159, 3206 }, /* glGetnUniformuiv and glGetnUniformuivKHR */
        { 3206, 1159 }, /* glGetnUniformuivKHR and glGetnUniformuiv */
        {  896, 3148 }, /* glGetObjectLabel and glGetObjectLabelKHR */
        { 3148,  896 }, /* glGetObjectLabelKHR and glGetObjectLabel */
        {  901, 3149 }, /* glGetObjectPtrLabel and glGetObjectPtrLabelKHR */
        { 3149,  901 }, /* glGetObjectPtrLabelKHR and glGetObjectPtrLabel */
        {  937,  938 }, /* glGetPointerv and glGetPointervEXT */
        {  937, 3150 }, /* glGetPointerv and glGetPointervKHR */
        {  938,  937 }, /* glGetPointervEXT and glGetPointerv */
        {  938, 3150 }, /* glGetPointervEXT and glGetPointervKHR */
        { 3150,  937 }, /* glGetPointervKHR and glGetPointerv */
        { 3150,  938 }, /* glGetPointervKHR and glGetPointervEXT */
        {  940, 3152 }, /* glGetProgramBinary and glGetProgramBinaryOES */
        { 3152,  940 }, /* glGetProgramBinaryOES and glGetProgramBinary */
        {  983,  984 }, /* glGetQueryiv and glGetQueryivARB */
        {  984,  983 }, /* glGetQueryivARB and glGetQueryiv */
        {  975,  976 }, /* glGetQueryObjecti64v and glGetQueryObjecti64vEXT */
        {  976,  975 }, /* glGetQueryObjecti64vEXT and glGetQueryObjecti64v */
        {  977,  978 }, /* glGetQueryObjectiv and glGetQueryObjectivARB */
        {  977, 3159 }, /* glGetQueryObjectiv and glGetQueryObjectivEXT */
        {  978,  977 }, /* glGetQueryObjectivARB and glGetQueryObjectiv */
        {  978, 3159 }, /* glGetQueryObjectivARB and glGetQueryObjectivEXT */
        { 3159,  977 }, /* glGetQueryObjectivEXT and glGetQueryObjectiv */
        { 3159,  978 }, /* glGetQueryObjectivEXT and glGetQueryObjectivARB */
        {  979,  980 }, /* glGetQueryObjectui64v and glGetQueryObjectui64vEXT */
        {  980,  979 }, /* glGetQueryObjectui64vEXT and glGetQueryObjectui64v */
        {  981,  982 }, /* glGetQueryObjectuiv and glGetQueryObjectuivARB */
        {  982,  981 }, /* glGetQueryObjectuivARB and glGetQueryObjectuiv */
        {  985,  986 }, /* glGetRenderbufferParameteriv and glGetRenderbufferParameterivEXT */
        {  986,  985 }, /* glGetRenderbufferParameterivEXT and glGetRenderbufferParameteriv */
        {  987, 3168 }, /* glGetSamplerParameterIiv and glGetSamplerParameterIivEXT */
        {  987, 3169 }, /* glGetSamplerParameterIiv and glGetSamplerParameterIivOES */
        { 3168,  987 }, /* glGetSamplerParameterIivEXT and glGetSamplerParameterIiv */
        { 3168, 3169 }, /* glGetSamplerParameterIivEXT and glGetSamplerParameterIivOES */
        { 3169,  987 }, /* glGetSamplerParameterIivOES and glGetSamplerParameterIiv */
        { 3169, 3168 }, /* glGetSamplerParameterIivOES and glGetSamplerParameterIivEXT */
        {  988, 3171 }, /* glGetSamplerParameterIuiv and glGetSamplerParameterIuivEXT */
        {  988, 3172 }, /* glGetSamplerParameterIuiv and glGetSamplerParameterIuivOES */
        { 3171,  988 }, /* glGetSamplerParameterIuivEXT and glGetSamplerParameterIuiv */
        { 3171, 3172 }, /* glGetSamplerParameterIuivEXT and glGetSamplerParameterIuivOES */
        { 3172,  988 }, /* glGetSamplerParameterIuivOES and glGetSamplerParameterIuiv */
        { 3172, 3171 }, /* glGetSamplerParameterIuivOES and glGetSamplerParameterIuivEXT */
        {  997,  998 }, /* glGetShaderSource and glGetShaderSourceARB */
        {  998,  997 }, /* glGetShaderSourceARB and glGetShaderSource */
        { 1008, 3177 }, /* glGetSynciv and glGetSyncivAPPLE */
        { 3177, 1008 }, /* glGetSyncivAPPLE and glGetSynciv */
        { 1023, 1024 }, /* glGetTexParameterIiv and glGetTexParameterIivEXT */
        { 1023, 3183 }, /* glGetTexParameterIiv and glGetTexParameterIivOES */
        { 1024, 1023 }, /* glGetTexParameterIivEXT and glGetTexParameterIiv */
        { 1024, 3183 }, /* glGetTexParameterIivEXT and glGetTexParameterIivOES */
        { 3183, 1023 }, /* glGetTexParameterIivOES and glGetTexParameterIiv */
        { 3183, 1024 }, /* glGetTexParameterIivOES and glGetTexParameterIivEXT */
        { 1025, 1026 }, /* glGetTexParameterIuiv and glGetTexParameterIuivEXT */
        { 1025, 3185 }, /* glGetTexParameterIuiv and glGetTexParameterIuivOES */
        { 1026, 1025 }, /* glGetTexParameterIuivEXT and glGetTexParameterIuiv */
        { 1026, 3185 }, /* glGetTexParameterIuivEXT and glGetTexParameterIuivOES */
        { 3185, 1025 }, /* glGetTexParameterIuivOES and glGetTexParameterIuiv */
        { 3185, 1026 }, /* glGetTexParameterIuivOES and glGetTexParameterIuivEXT */
        { 1031, 3189 }, /* glGetTextureHandleARB and glGetTextureHandleIMG */
        { 3189, 1031 }, /* glGetTextureHandleIMG and glGetTextureHandleARB */
        { 1047, 3190 }, /* glGetTextureSamplerHandleARB and glGetTextureSamplerHandleIMG */
        { 3190, 1047 }, /* glGetTextureSamplerHandleIMG and glGetTextureSamplerHandleARB */
        { 1051, 1052 }, /* glGetTransformFeedbackVarying and glGetTransformFeedbackVaryingEXT */
        { 1052, 1051 }, /* glGetTransformFeedbackVaryingEXT and glGetTransformFeedbackVarying */
        { 1065, 1066 }, /* glGetUniformfv and glGetUniformfvARB */
        { 1066, 1065 }, /* glGetUniformfvARB and glGetUniformfv */
        { 1069, 1070 }, /* glGetUniformiv and glGetUniformivARB */
        { 1070, 1069 }, /* glGetUniformivARB and glGetUniformiv */
        { 1060, 1061 }, /* glGetUniformLocation and glGetUniformLocationARB */
        { 1061, 1060 }, /* glGetUniformLocationARB and glGetUniformLocation */
        { 1073, 1074 }, /* glGetUniformuiv and glGetUniformuivEXT */
        { 1074, 1073 }, /* glGetUniformuivEXT and glGetUniformuiv */
        { 1105, 1106 }, /* glGetVertexAttribdv and glGetVertexAttribdvARB */
        { 1105, 1107 }, /* glGetVertexAttribdv and glGetVertexAttribdvNV */
        { 1106, 1105 }, /* glGetVertexAttribdvARB and glGetVertexAttribdv */
        { 1106, 1107 }, /* glGetVertexAttribdvARB and glGetVertexAttribdvNV */
        { 1107, 1105 }, /* glGetVertexAttribdvNV and glGetVertexAttribdv */
        { 1107, 1106 }, /* glGetVertexAttribdvNV and glGetVertexAttribdvARB */
        { 1108, 1109 }, /* glGetVertexAttribfv and glGetVertexAttribfvARB */
        { 1108, 1110 }, /* glGetVertexAttribfv and glGetVertexAttribfvNV */
        { 1109, 1108 }, /* glGetVertexAttribfvARB and glGetVertexAttribfv */
        { 1109, 1110 }, /* glGetVertexAttribfvARB and glGetVertexAttribfvNV */
        { 1110, 1108 }, /* glGetVertexAttribfvNV and glGetVertexAttribfv */
        { 1110, 1109 }, /* glGetVertexAttribfvNV and glGetVertexAttribfvARB */
        { 1093, 1094 }, /* glGetVertexAttribIiv and glGetVertexAttribIivEXT */
        { 1094, 1093 }, /* glGetVertexAttribIivEXT and glGetVertexAttribIiv */
        { 1095, 1096 }, /* glGetVertexAttribIuiv and glGetVertexAttribIuivEXT */
        { 1096, 1095 }, /* glGetVertexAttribIuivEXT and glGetVertexAttribIuiv */
        { 1111, 1112 }, /* glGetVertexAttribiv and glGetVertexAttribivARB */
        { 1111, 1113 }, /* glGetVertexAttribiv and glGetVertexAttribivNV */
        { 1112, 1111 }, /* glGetVertexAttribivARB and glGetVertexAttribiv */
        { 1112, 1113 }, /* glGetVertexAttribivARB and glGetVertexAttribivNV */
        { 1113, 1111 }, /* glGetVertexAttribivNV and glGetVertexAttribiv */
        { 1113, 1112 }, /* glGetVertexAttribivNV and glGetVertexAttribivARB */
        { 1097, 1098 }, /* glGetVertexAttribLdv and glGetVertexAttribLdvEXT */
        { 1098, 1097 }, /* glGetVertexAttribLdvEXT and glGetVertexAttribLdv */
        { 1102, 1103 }, /* glGetVertexAttribPointerv and glGetVertexAttribPointervARB */
        { 1102, 1104 }, /* glGetVertexAttribPointerv and glGetVertexAttribPointervNV */
        { 1103, 1102 }, /* glGetVertexAttribPointervARB and glGetVertexAttribPointerv */
        { 1103, 1104 }, /* glGetVertexAttribPointervARB and glGetVertexAttribPointervNV */
        { 1104, 1102 }, /* glGetVertexAttribPointervNV and glGetVertexAttribPointerv */
        { 1104, 1103 }, /* glGetVertexAttribPointervNV and glGetVertexAttribPointervARB */
        { 1171, 1172 }, /* glHistogram and glHistogramEXT */
        { 1172, 1171 }, /* glHistogramEXT and glHistogram */
        { 1222, 1223 }, /* glIsBuffer and glIsBufferARB */
        { 1223, 1222 }, /* glIsBufferARB and glIsBuffer */
        { 1228, 1227 }, /* glIsEnabledi and glIsEnabledIndexedEXT */
        { 1228, 3208 }, /* glIsEnabledi and glIsEnablediEXT */
        { 1228, 3209 }, /* glIsEnabledi and glIsEnablediNV */
        { 1228, 3210 }, /* glIsEnabledi and glIsEnablediOES */
        { 3208, 1227 }, /* glIsEnablediEXT and glIsEnabledIndexedEXT */
        { 3208, 1228 }, /* glIsEnablediEXT and glIsEnabledi */
        { 3208, 3209 }, /* glIsEnablediEXT and glIsEnablediNV */
        { 3208, 3210 }, /* glIsEnablediEXT and glIsEnablediOES */
        { 1227, 1228 }, /* glIsEnabledIndexedEXT and glIsEnabledi */
        { 1227, 3208 }, /* glIsEnabledIndexedEXT and glIsEnablediEXT */
        { 1227, 3209 }, /* glIsEnabledIndexedEXT and glIsEnablediNV */
        { 1227, 3210 }, /* glIsEnabledIndexedEXT and glIsEnablediOES */
        { 3209, 1227 }, /* glIsEnablediNV and glIsEnabledIndexedEXT */
        { 3209, 1228 }, /* glIsEnablediNV and glIsEnabledi */
        { 3209, 3208 }, /* glIsEnablediNV and glIsEnablediEXT */
        { 3209, 3210 }, /* glIsEnablediNV and glIsEnablediOES */
        { 3210, 1227 }, /* glIsEnablediOES and glIsEnabledIndexedEXT */
        { 3210, 1228 }, /* glIsEnablediOES and glIsEnabledi */
        { 3210, 3208 }, /* glIsEnablediOES and glIsEnablediEXT */
        { 3210, 3209 }, /* glIsEnablediOES and glIsEnablediNV */
        { 1231, 1232 }, /* glIsFramebuffer and glIsFramebufferEXT */
        { 1232, 1231 }, /* glIsFramebufferEXT and glIsFramebuffer */
        { 1246, 1247 }, /* glIsProgramARB and glIsProgramNV */
        { 1247, 1246 }, /* glIsProgramNV and glIsProgramARB */
        { 1249, 1250 }, /* glIsQuery and glIsQueryARB */
        { 1250, 1249 }, /* glIsQueryARB and glIsQuery */
        { 1251, 1252 }, /* glIsRenderbuffer and glIsRenderbufferEXT */
        { 1252, 1251 }, /* glIsRenderbufferEXT and glIsRenderbuffer */
        { 1257, 3213 }, /* glIsSync and glIsSyncAPPLE */
        { 3213, 1257 }, /* glIsSyncAPPLE and glIsSync */
        { 1262, 1263 }, /* glIsTransformFeedback and glIsTransformFeedbackNV */
        { 1263, 1262 }, /* glIsTransformFeedbackNV and glIsTransformFeedback */
        { 1265, 1266 }, /* glIsVertexArray and glIsVertexArrayAPPLE */
        { 1265, 3214 }, /* glIsVertexArray and glIsVertexArrayOES */
        { 1266, 1265 }, /* glIsVertexArrayAPPLE and glIsVertexArray */
        { 1266, 3214 }, /* glIsVertexArrayAPPLE and glIsVertexArrayOES */
        { 3214, 1265 }, /* glIsVertexArrayOES and glIsVertexArray */
        { 3214, 1266 }, /* glIsVertexArrayOES and glIsVertexArrayAPPLE */
        { 1288, 1289 }, /* glLinkProgram and glLinkProgramARB */
        { 1289, 1288 }, /* glLinkProgramARB and glLinkProgram */
        { 1303, 1304 }, /* glLoadTransposeMatrixd and glLoadTransposeMatrixdARB */
        { 1304, 1303 }, /* glLoadTransposeMatrixdARB and glLoadTransposeMatrixd */
        { 1305, 1306 }, /* glLoadTransposeMatrixf and glLoadTransposeMatrixfARB */
        { 1306, 1305 }, /* glLoadTransposeMatrixfARB and glLoadTransposeMatrixf */
        { 1328, 1329 }, /* glMapBuffer and glMapBufferARB */
        { 1328, 3217 }, /* glMapBuffer and glMapBufferOES */
        { 1329, 1328 }, /* glMapBufferARB and glMapBuffer */
        { 1329, 3217 }, /* glMapBufferARB and glMapBufferOES */
        { 3217, 1328 }, /* glMapBufferOES and glMapBuffer */
        { 3217, 1329 }, /* glMapBufferOES and glMapBufferARB */
        { 1330, 3218 }, /* glMapBufferRange and glMapBufferRangeEXT */
        { 3218, 1330 }, /* glMapBufferRangeEXT and glMapBufferRange */
        { 1386, 1387 }, /* glMaxShaderCompilerThreadsARB and glMaxShaderCompilerThreadsKHR */
        { 1387, 1386 }, /* glMaxShaderCompilerThreadsKHR and glMaxShaderCompilerThreadsARB */
        { 1388, 1390 }, /* glMemoryBarrier and glMemoryBarrierEXT */
        { 1390, 1388 }, /* glMemoryBarrierEXT and glMemoryBarrier */
        { 1394, 1395 }, /* glMinmax and glMinmaxEXT */
        { 1395, 1394 }, /* glMinmaxEXT and glMinmax */
        { 1392, 1393 }, /* glMinSampleShading and glMinSampleShadingARB */
        { 1392, 3220 }, /* glMinSampleShading and glMinSampleShadingOES */
        { 1393, 1392 }, /* glMinSampleShadingARB and glMinSampleShading */
        { 1393, 3220 }, /* glMinSampleShadingARB and glMinSampleShadingOES */
        { 3220, 1392 }, /* glMinSampleShadingOES and glMinSampleShading */
        { 3220, 1393 }, /* glMinSampleShadingOES and glMinSampleShadingARB */
        { 1404, 1405 }, /* glMultiDrawArrays and glMultiDrawArraysEXT */
        { 1405, 1404 }, /* glMultiDrawArraysEXT and glMultiDrawArrays */
        { 1406, 1407 }, /* glMultiDrawArraysIndirect and glMultiDrawArraysIndirectAMD */
        { 1406, 3222 }, /* glMultiDrawArraysIndirect and glMultiDrawArraysIndirectEXT */
        { 1407, 1406 }, /* glMultiDrawArraysIndirectAMD and glMultiDrawArraysIndirect */
        { 1407, 3222 }, /* glMultiDrawArraysIndirectAMD and glMultiDrawArraysIndirectEXT */
        { 1410, 1411 }, /* glMultiDrawArraysIndirectCount and glMultiDrawArraysIndirectCountARB */
        { 1411, 1410 }, /* glMultiDrawArraysIndirectCountARB and glMultiDrawArraysIndirectCount */
        { 3222, 1406 }, /* glMultiDrawArraysIndirectEXT and glMultiDrawArraysIndirect */
        { 3222, 1407 }, /* glMultiDrawArraysIndirectEXT and glMultiDrawArraysIndirectAMD */
        { 1413, 1415 }, /* glMultiDrawElements and glMultiDrawElementsEXT */
        { 1414, 3226 }, /* glMultiDrawElementsBaseVertex and glMultiDrawElementsBaseVertexEXT */
        { 3226, 1414 }, /* glMultiDrawElementsBaseVertexEXT and glMultiDrawElementsBaseVertex */
        { 1415, 1413 }, /* glMultiDrawElementsEXT and glMultiDrawElements */
        { 1416, 1417 }, /* glMultiDrawElementsIndirect and glMultiDrawElementsIndirectAMD */
        { 1416, 3227 }, /* glMultiDrawElementsIndirect and glMultiDrawElementsIndirectEXT */
        { 1417, 1416 }, /* glMultiDrawElementsIndirectAMD and glMultiDrawElementsIndirect */
        { 1417, 3227 }, /* glMultiDrawElementsIndirectAMD and glMultiDrawElementsIndirectEXT */
        { 1420, 1421 }, /* glMultiDrawElementsIndirectCount and glMultiDrawElementsIndirectCountARB */
        { 1421, 1420 }, /* glMultiDrawElementsIndirectCountARB and glMultiDrawElementsIndirectCount */
        { 3227, 1416 }, /* glMultiDrawElementsIndirectEXT and glMultiDrawElementsIndirect */
        { 3227, 1417 }, /* glMultiDrawElementsIndirectEXT and glMultiDrawElementsIndirectAMD */
        { 1430, 1431 }, /* glMultiTexCoord1d and glMultiTexCoord1dARB */
        { 1431, 1430 }, /* glMultiTexCoord1dARB and glMultiTexCoord1d */
        { 1432, 1433 }, /* glMultiTexCoord1dv and glMultiTexCoord1dvARB */
        { 1433, 1432 }, /* glMultiTexCoord1dvARB and glMultiTexCoord1dv */
        { 1434, 1435 }, /* glMultiTexCoord1f and glMultiTexCoord1fARB */
        { 1435, 1434 }, /* glMultiTexCoord1fARB and glMultiTexCoord1f */
        { 1436, 1437 }, /* glMultiTexCoord1fv and glMultiTexCoord1fvARB */
        { 1437, 1436 }, /* glMultiTexCoord1fvARB and glMultiTexCoord1fv */
        { 1440, 1441 }, /* glMultiTexCoord1i and glMultiTexCoord1iARB */
        { 1441, 1440 }, /* glMultiTexCoord1iARB and glMultiTexCoord1i */
        { 1442, 1443 }, /* glMultiTexCoord1iv and glMultiTexCoord1ivARB */
        { 1443, 1442 }, /* glMultiTexCoord1ivARB and glMultiTexCoord1iv */
        { 1444, 1445 }, /* glMultiTexCoord1s and glMultiTexCoord1sARB */
        { 1445, 1444 }, /* glMultiTexCoord1sARB and glMultiTexCoord1s */
        { 1446, 1447 }, /* glMultiTexCoord1sv and glMultiTexCoord1svARB */
        { 1447, 1446 }, /* glMultiTexCoord1svARB and glMultiTexCoord1sv */
        { 1452, 1453 }, /* glMultiTexCoord2d and glMultiTexCoord2dARB */
        { 1453, 1452 }, /* glMultiTexCoord2dARB and glMultiTexCoord2d */
        { 1454, 1455 }, /* glMultiTexCoord2dv and glMultiTexCoord2dvARB */
        { 1455, 1454 }, /* glMultiTexCoord2dvARB and glMultiTexCoord2dv */
        { 1456, 1457 }, /* glMultiTexCoord2f and glMultiTexCoord2fARB */
        { 1457, 1456 }, /* glMultiTexCoord2fARB and glMultiTexCoord2f */
        { 1458, 1459 }, /* glMultiTexCoord2fv and glMultiTexCoord2fvARB */
        { 1459, 1458 }, /* glMultiTexCoord2fvARB and glMultiTexCoord2fv */
        { 1462, 1463 }, /* glMultiTexCoord2i and glMultiTexCoord2iARB */
        { 1463, 1462 }, /* glMultiTexCoord2iARB and glMultiTexCoord2i */
        { 1464, 1465 }, /* glMultiTexCoord2iv and glMultiTexCoord2ivARB */
        { 1465, 1464 }, /* glMultiTexCoord2ivARB and glMultiTexCoord2iv */
        { 1466, 1467 }, /* glMultiTexCoord2s and glMultiTexCoord2sARB */
        { 1467, 1466 }, /* glMultiTexCoord2sARB and glMultiTexCoord2s */
        { 1468, 1469 }, /* glMultiTexCoord2sv and glMultiTexCoord2svARB */
        { 1469, 1468 }, /* glMultiTexCoord2svARB and glMultiTexCoord2sv */
        { 1474, 1475 }, /* glMultiTexCoord3d and glMultiTexCoord3dARB */
        { 1475, 1474 }, /* glMultiTexCoord3dARB and glMultiTexCoord3d */
        { 1476, 1477 }, /* glMultiTexCoord3dv and glMultiTexCoord3dvARB */
        { 1477, 1476 }, /* glMultiTexCoord3dvARB and glMultiTexCoord3dv */
        { 1478, 1479 }, /* glMultiTexCoord3f and glMultiTexCoord3fARB */
        { 1479, 1478 }, /* glMultiTexCoord3fARB and glMultiTexCoord3f */
        { 1480, 1481 }, /* glMultiTexCoord3fv and glMultiTexCoord3fvARB */
        { 1481, 1480 }, /* glMultiTexCoord3fvARB and glMultiTexCoord3fv */
        { 1484, 1485 }, /* glMultiTexCoord3i and glMultiTexCoord3iARB */
        { 1485, 1484 }, /* glMultiTexCoord3iARB and glMultiTexCoord3i */
        { 1486, 1487 }, /* glMultiTexCoord3iv and glMultiTexCoord3ivARB */
        { 1487, 1486 }, /* glMultiTexCoord3ivARB and glMultiTexCoord3iv */
        { 1488, 1489 }, /* glMultiTexCoord3s and glMultiTexCoord3sARB */
        { 1489, 1488 }, /* glMultiTexCoord3sARB and glMultiTexCoord3s */
        { 1490, 1491 }, /* glMultiTexCoord3sv and glMultiTexCoord3svARB */
        { 1491, 1490 }, /* glMultiTexCoord3svARB and glMultiTexCoord3sv */
        { 1496, 1497 }, /* glMultiTexCoord4d and glMultiTexCoord4dARB */
        { 1497, 1496 }, /* glMultiTexCoord4dARB and glMultiTexCoord4d */
        { 1498, 1499 }, /* glMultiTexCoord4dv and glMultiTexCoord4dvARB */
        { 1499, 1498 }, /* glMultiTexCoord4dvARB and glMultiTexCoord4dv */
        { 1500, 1501 }, /* glMultiTexCoord4f and glMultiTexCoord4fARB */
        { 1501, 1500 }, /* glMultiTexCoord4fARB and glMultiTexCoord4f */
        { 1502, 1503 }, /* glMultiTexCoord4fv and glMultiTexCoord4fvARB */
        { 1503, 1502 }, /* glMultiTexCoord4fvARB and glMultiTexCoord4fv */
        { 1506, 1507 }, /* glMultiTexCoord4i and glMultiTexCoord4iARB */
        { 1507, 1506 }, /* glMultiTexCoord4iARB and glMultiTexCoord4i */
        { 1508, 1509 }, /* glMultiTexCoord4iv and glMultiTexCoord4ivARB */
        { 1509, 1508 }, /* glMultiTexCoord4ivARB and glMultiTexCoord4iv */
        { 1510, 1511 }, /* glMultiTexCoord4s and glMultiTexCoord4sARB */
        { 1511, 1510 }, /* glMultiTexCoord4sARB and glMultiTexCoord4s */
        { 1512, 1513 }, /* glMultiTexCoord4sv and glMultiTexCoord4svARB */
        { 1513, 1512 }, /* glMultiTexCoord4svARB and glMultiTexCoord4sv */
        { 1399, 1400 }, /* glMultTransposeMatrixd and glMultTransposeMatrixdARB */
        { 1400, 1399 }, /* glMultTransposeMatrixdARB and glMultTransposeMatrixd */
        { 1401, 1402 }, /* glMultTransposeMatrixf and glMultTransposeMatrixfARB */
        { 1402, 1401 }, /* glMultTransposeMatrixfARB and glMultTransposeMatrixf */
        { 1568, 1569 }, /* glNamedBufferStorage and glNamedBufferStorageEXT */
        { 1569, 1568 }, /* glNamedBufferStorageEXT and glNamedBufferStorage */
        { 1572, 1573 }, /* glNamedBufferSubData and glNamedBufferSubDataEXT */
        { 1573, 1572 }, /* glNamedBufferSubDataEXT and glNamedBufferSubData */
        { 1647, 3230 }, /* glObjectLabel and glObjectLabelKHR */
        { 3230, 1647 }, /* glObjectLabelKHR and glObjectLabel */
        { 1648, 3231 }, /* glObjectPtrLabel and glObjectPtrLabelKHR */
        { 3231, 1648 }, /* glObjectPtrLabelKHR and glObjectPtrLabel */
        { 1660, 3232 }, /* glPatchParameteri and glPatchParameteriEXT */
        { 1660, 3233 }, /* glPatchParameteri and glPatchParameteriOES */
        { 3232, 1660 }, /* glPatchParameteriEXT and glPatchParameteri */
        { 3232, 3233 }, /* glPatchParameteriEXT and glPatchParameteriOES */
        { 3233, 1660 }, /* glPatchParameteriOES and glPatchParameteri */
        { 3233, 3232 }, /* glPatchParameteriOES and glPatchParameteriEXT */
        { 1682, 1683 }, /* glPauseTransformFeedback and glPauseTransformFeedbackNV */
        { 1683, 1682 }, /* glPauseTransformFeedbackNV and glPauseTransformFeedback */
        { 1707, 1708 }, /* glPointParameterf and glPointParameterfARB */
        { 1707, 1709 }, /* glPointParameterf and glPointParameterfEXT */
        { 1707, 1710 }, /* glPointParameterf and glPointParameterfSGIS */
        { 1708, 1707 }, /* glPointParameterfARB and glPointParameterf */
        { 1708, 1709 }, /* glPointParameterfARB and glPointParameterfEXT */
        { 1708, 1710 }, /* glPointParameterfARB and glPointParameterfSGIS */
        { 1709, 1707 }, /* glPointParameterfEXT and glPointParameterf */
        { 1709, 1708 }, /* glPointParameterfEXT and glPointParameterfARB */
        { 1709, 1710 }, /* glPointParameterfEXT and glPointParameterfSGIS */
        { 1710, 1707 }, /* glPointParameterfSGIS and glPointParameterf */
        { 1710, 1708 }, /* glPointParameterfSGIS and glPointParameterfARB */
        { 1710, 1709 }, /* glPointParameterfSGIS and glPointParameterfEXT */
        { 1711, 1712 }, /* glPointParameterfv and glPointParameterfvARB */
        { 1711, 1713 }, /* glPointParameterfv and glPointParameterfvEXT */
        { 1711, 1714 }, /* glPointParameterfv and glPointParameterfvSGIS */
        { 1712, 1711 }, /* glPointParameterfvARB and glPointParameterfv */
        { 1712, 1713 }, /* glPointParameterfvARB and glPointParameterfvEXT */
        { 1712, 1714 }, /* glPointParameterfvARB and glPointParameterfvSGIS */
        { 1713, 1711 }, /* glPointParameterfvEXT and glPointParameterfv */
        { 1713, 1712 }, /* glPointParameterfvEXT and glPointParameterfvARB */
        { 1713, 1714 }, /* glPointParameterfvEXT and glPointParameterfvSGIS */
        { 1714, 1711 }, /* glPointParameterfvSGIS and glPointParameterfv */
        { 1714, 1712 }, /* glPointParameterfvSGIS and glPointParameterfvARB */
        { 1714, 1713 }, /* glPointParameterfvSGIS and glPointParameterfvEXT */
        { 1715, 1716 }, /* glPointParameteri and glPointParameteriNV */
        { 1716, 1715 }, /* glPointParameteriNV and glPointParameteri */
        { 1717, 1718 }, /* glPointParameteriv and glPointParameterivNV */
        { 1718, 1717 }, /* glPointParameterivNV and glPointParameteriv */
        { 1724, 3236 }, /* glPolygonMode and glPolygonModeNV */
        { 3236, 1724 }, /* glPolygonModeNV and glPolygonMode */
        { 1726, 1727 }, /* glPolygonOffsetClamp and glPolygonOffsetClampEXT */
        { 1727, 1726 }, /* glPolygonOffsetClampEXT and glPolygonOffsetClamp */
        { 1733, 3237 }, /* glPopDebugGroup and glPopDebugGroupKHR */
        { 3237, 1733 }, /* glPopDebugGroupKHR and glPopDebugGroup */
        { 3238, 1739 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxARB */
        { 3238, 3239 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxEXT */
        { 3238, 3240 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxOES */
        { 1739, 3238 }, /* glPrimitiveBoundingBoxARB and glPrimitiveBoundingBox */
        { 1739, 3239 }, /* glPrimitiveBoundingBoxARB and glPrimitiveBoundingBoxEXT */
        { 1739, 3240 }, /* glPrimitiveBoundingBoxARB and glPrimitiveBoundingBoxOES */
        { 3239, 3238 }, /* glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBox */
        { 3239, 1739 }, /* glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBoxARB */
        { 3239, 3240 }, /* glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBoxOES */
        { 3240, 3238 }, /* glPrimitiveBoundingBoxOES and glPrimitiveBoundingBox */
        { 3240, 1739 }, /* glPrimitiveBoundingBoxOES and glPrimitiveBoundingBoxARB */
        { 3240, 3239 }, /* glPrimitiveBoundingBoxOES and glPrimitiveBoundingBoxEXT */
        { 1743, 1744 }, /* glPrioritizeTextures and glPrioritizeTexturesEXT */
        { 1744, 1743 }, /* glPrioritizeTexturesEXT and glPrioritizeTextures */
        { 1746, 3241 }, /* glProgramBinary and glProgramBinaryOES */
        { 3241, 1746 }, /* glProgramBinaryOES and glProgramBinary */
        { 1780, 1781 }, /* glProgramParameteri and glProgramParameteriARB */
        { 1780, 1782 }, /* glProgramParameteri and glProgramParameteriEXT */
        { 1781, 1780 }, /* glProgramParameteriARB and glProgramParameteri */
        { 1781, 1782 }, /* glProgramParameteriARB and glProgramParameteriEXT */
        { 1782, 1780 }, /* glProgramParameteriEXT and glProgramParameteri */
        { 1782, 1781 }, /* glProgramParameteriEXT and glProgramParameteriARB */
        { 1792, 1793 }, /* glProgramUniform1f and glProgramUniform1fEXT */
        { 1793, 1792 }, /* glProgramUniform1fEXT and glProgramUniform1f */
        { 1794, 1795 }, /* glProgramUniform1fv and glProgramUniform1fvEXT */
        { 1795, 1794 }, /* glProgramUniform1fvEXT and glProgramUniform1fv */
        { 1796, 1801 }, /* glProgramUniform1i and glProgramUniform1iEXT */
        { 1801, 1796 }, /* glProgramUniform1iEXT and glProgramUniform1i */
        { 1802, 1803 }, /* glProgramUniform1iv and glProgramUniform1ivEXT */
        { 1803, 1802 }, /* glProgramUniform1ivEXT and glProgramUniform1iv */
        { 1804, 1809 }, /* glProgramUniform1ui and glProgramUniform1uiEXT */
        { 1809, 1804 }, /* glProgramUniform1uiEXT and glProgramUniform1ui */
        { 1810, 1811 }, /* glProgramUniform1uiv and glProgramUniform1uivEXT */
        { 1811, 1810 }, /* glProgramUniform1uivEXT and glProgramUniform1uiv */
        { 1816, 1817 }, /* glProgramUniform2f and glProgramUniform2fEXT */
        { 1817, 1816 }, /* glProgramUniform2fEXT and glProgramUniform2f */
        { 1818, 1819 }, /* glProgramUniform2fv and glProgramUniform2fvEXT */
        { 1819, 1818 }, /* glProgramUniform2fvEXT and glProgramUniform2fv */
        { 1820, 1825 }, /* glProgramUniform2i and glProgramUniform2iEXT */
        { 1825, 1820 }, /* glProgramUniform2iEXT and glProgramUniform2i */
        { 1826, 1827 }, /* glProgramUniform2iv and glProgramUniform2ivEXT */
        { 1827, 1826 }, /* glProgramUniform2ivEXT and glProgramUniform2iv */
        { 1828, 1833 }, /* glProgramUniform2ui and glProgramUniform2uiEXT */
        { 1833, 1828 }, /* glProgramUniform2uiEXT and glProgramUniform2ui */
        { 1834, 1835 }, /* glProgramUniform2uiv and glProgramUniform2uivEXT */
        { 1835, 1834 }, /* glProgramUniform2uivEXT and glProgramUniform2uiv */
        { 1840, 1841 }, /* glProgramUniform3f and glProgramUniform3fEXT */
        { 1841, 1840 }, /* glProgramUniform3fEXT and glProgramUniform3f */
        { 1842, 1843 }, /* glProgramUniform3fv and glProgramUniform3fvEXT */
        { 1843, 1842 }, /* glProgramUniform3fvEXT and glProgramUniform3fv */
        { 1844, 1849 }, /* glProgramUniform3i and glProgramUniform3iEXT */
        { 1849, 1844 }, /* glProgramUniform3iEXT and glProgramUniform3i */
        { 1850, 1851 }, /* glProgramUniform3iv and glProgramUniform3ivEXT */
        { 1851, 1850 }, /* glProgramUniform3ivEXT and glProgramUniform3iv */
        { 1852, 1857 }, /* glProgramUniform3ui and glProgramUniform3uiEXT */
        { 1857, 1852 }, /* glProgramUniform3uiEXT and glProgramUniform3ui */
        { 1858, 1859 }, /* glProgramUniform3uiv and glProgramUniform3uivEXT */
        { 1859, 1858 }, /* glProgramUniform3uivEXT and glProgramUniform3uiv */
        { 1864, 1865 }, /* glProgramUniform4f and glProgramUniform4fEXT */
        { 1865, 1864 }, /* glProgramUniform4fEXT and glProgramUniform4f */
        { 1866, 1867 }, /* glProgramUniform4fv and glProgramUniform4fvEXT */
        { 1867, 1866 }, /* glProgramUniform4fvEXT and glProgramUniform4fv */
        { 1868, 1873 }, /* glProgramUniform4i and glProgramUniform4iEXT */
        { 1873, 1868 }, /* glProgramUniform4iEXT and glProgramUniform4i */
        { 1874, 1875 }, /* glProgramUniform4iv and glProgramUniform4ivEXT */
        { 1875, 1874 }, /* glProgramUniform4ivEXT and glProgramUniform4iv */
        { 1876, 1881 }, /* glProgramUniform4ui and glProgramUniform4uiEXT */
        { 1881, 1876 }, /* glProgramUniform4uiEXT and glProgramUniform4ui */
        { 1882, 1883 }, /* glProgramUniform4uiv and glProgramUniform4uivEXT */
        { 1883, 1882 }, /* glProgramUniform4uivEXT and glProgramUniform4uiv */
        { 1884, 3242 }, /* glProgramUniformHandleui64ARB and glProgramUniformHandleui64IMG */
        { 3242, 1884 }, /* glProgramUniformHandleui64IMG and glProgramUniformHandleui64ARB */
        { 1886, 3243 }, /* glProgramUniformHandleui64vARB and glProgramUniformHandleui64vIMG */
        { 3243, 1886 }, /* glProgramUniformHandleui64vIMG and glProgramUniformHandleui64vARB */
        { 1890, 1891 }, /* glProgramUniformMatrix2fv and glProgramUniformMatrix2fvEXT */
        { 1891, 1890 }, /* glProgramUniformMatrix2fvEXT and glProgramUniformMatrix2fv */
        { 1894, 1895 }, /* glProgramUniformMatrix2x3fv and glProgramUniformMatrix2x3fvEXT */
        { 1895, 1894 }, /* glProgramUniformMatrix2x3fvEXT and glProgramUniformMatrix2x3fv */
        { 1898, 1899 }, /* glProgramUniformMatrix2x4fv and glProgramUniformMatrix2x4fvEXT */
        { 1899, 1898 }, /* glProgramUniformMatrix2x4fvEXT and glProgramUniformMatrix2x4fv */
        { 1902, 1903 }, /* glProgramUniformMatrix3fv and glProgramUniformMatrix3fvEXT */
        { 1903, 1902 }, /* glProgramUniformMatrix3fvEXT and glProgramUniformMatrix3fv */
        { 1906, 1907 }, /* glProgramUniformMatrix3x2fv and glProgramUniformMatrix3x2fvEXT */
        { 1907, 1906 }, /* glProgramUniformMatrix3x2fvEXT and glProgramUniformMatrix3x2fv */
        { 1910, 1911 }, /* glProgramUniformMatrix3x4fv and glProgramUniformMatrix3x4fvEXT */
        { 1911, 1910 }, /* glProgramUniformMatrix3x4fvEXT and glProgramUniformMatrix3x4fv */
        { 1914, 1915 }, /* glProgramUniformMatrix4fv and glProgramUniformMatrix4fvEXT */
        { 1915, 1914 }, /* glProgramUniformMatrix4fvEXT and glProgramUniformMatrix4fv */
        { 1918, 1919 }, /* glProgramUniformMatrix4x2fv and glProgramUniformMatrix4x2fvEXT */
        { 1919, 1918 }, /* glProgramUniformMatrix4x2fvEXT and glProgramUniformMatrix4x2fv */
        { 1922, 1923 }, /* glProgramUniformMatrix4x3fv and glProgramUniformMatrix4x3fvEXT */
        { 1923, 1922 }, /* glProgramUniformMatrix4x3fvEXT and glProgramUniformMatrix4x3fv */
        { 1927, 3244 }, /* glProvokingVertex and glProvokingVertexANGLE */
        { 1927, 1928 }, /* glProvokingVertex and glProvokingVertexEXT */
        { 3244, 1927 }, /* glProvokingVertexANGLE and glProvokingVertex */
        { 3244, 1928 }, /* glProvokingVertexANGLE and glProvokingVertexEXT */
        { 1928, 1927 }, /* glProvokingVertexEXT and glProvokingVertex */
        { 1928, 3244 }, /* glProvokingVertexEXT and glProvokingVertexANGLE */
        { 1932, 3245 }, /* glPushDebugGroup and glPushDebugGroupKHR */
        { 3245, 1932 }, /* glPushDebugGroupKHR and glPushDebugGroup */
        { 1936, 3246 }, /* glQueryCounter and glQueryCounterEXT */
        { 3246, 1936 }, /* glQueryCounterEXT and glQueryCounter */
        { 1975, 1976 }, /* glReadnPixels and glReadnPixelsARB */
        { 1975, 3250 }, /* glReadnPixels and glReadnPixelsEXT */
        { 1975, 3251 }, /* glReadnPixels and glReadnPixelsKHR */
        { 1976, 1975 }, /* glReadnPixelsARB and glReadnPixels */
        { 1976, 3250 }, /* glReadnPixelsARB and glReadnPixelsEXT */
        { 1976, 3251 }, /* glReadnPixelsARB and glReadnPixelsKHR */
        { 3250, 1975 }, /* glReadnPixelsEXT and glReadnPixels */
        { 3250, 1976 }, /* glReadnPixelsEXT and glReadnPixelsARB */
        { 3250, 3251 }, /* glReadnPixelsEXT and glReadnPixelsKHR */
        { 3251, 1975 }, /* glReadnPixelsKHR and glReadnPixels */
        { 3251, 1976 }, /* glReadnPixelsKHR and glReadnPixelsARB */
        { 3251, 3250 }, /* glReadnPixelsKHR and glReadnPixelsEXT */
        { 1992, 1993 }, /* glRenderbufferStorage and glRenderbufferStorageEXT */
        { 1993, 1992 }, /* glRenderbufferStorageEXT and glRenderbufferStorage */
        { 1994, 1997 }, /* glRenderbufferStorageMultisample and glRenderbufferStorageMultisampleEXT */
        { 1994, 3257 }, /* glRenderbufferStorageMultisample and glRenderbufferStorageMultisampleNV */
        { 1997, 1994 }, /* glRenderbufferStorageMultisampleEXT and glRenderbufferStorageMultisample */
        { 1997, 3257 }, /* glRenderbufferStorageMultisampleEXT and glRenderbufferStorageMultisampleNV */
        { 3257, 1994 }, /* glRenderbufferStorageMultisampleNV and glRenderbufferStorageMultisample */
        { 3257, 1997 }, /* glRenderbufferStorageMultisampleNV and glRenderbufferStorageMultisampleEXT */
        { 2022, 2023 }, /* glResetHistogram and glResetHistogramEXT */
        { 2023, 2022 }, /* glResetHistogramEXT and glResetHistogram */
        { 2025, 2026 }, /* glResetMinmax and glResetMinmaxEXT */
        { 2026, 2025 }, /* glResetMinmaxEXT and glResetMinmax */
        { 2029, 2030 }, /* glResumeTransformFeedback and glResumeTransformFeedbackNV */
        { 2030, 2029 }, /* glResumeTransformFeedbackNV and glResumeTransformFeedback */
        { 2034, 2035 }, /* glSampleCoverage and glSampleCoverageARB */
        { 2035, 2034 }, /* glSampleCoverageARB and glSampleCoverage */
        { 2037, 2039 }, /* glSampleMaskEXT and glSampleMaskSGIS */
        { 2039, 2037 }, /* glSampleMaskSGIS and glSampleMaskEXT */
        { 2041, 2042 }, /* glSamplePatternEXT and glSamplePatternSGIS */
        { 2042, 2041 }, /* glSamplePatternSGIS and glSamplePatternEXT */
        { 2043, 3261 }, /* glSamplerParameterIiv and glSamplerParameterIivEXT */
        { 2043, 3262 }, /* glSamplerParameterIiv and glSamplerParameterIivOES */
        { 3261, 2043 }, /* glSamplerParameterIivEXT and glSamplerParameterIiv */
        { 3261, 3262 }, /* glSamplerParameterIivEXT and glSamplerParameterIivOES */
        { 3262, 2043 }, /* glSamplerParameterIivOES and glSamplerParameterIiv */
        { 3262, 3261 }, /* glSamplerParameterIivOES and glSamplerParameterIivEXT */
        { 2044, 3264 }, /* glSamplerParameterIuiv and glSamplerParameterIuivEXT */
        { 2044, 3265 }, /* glSamplerParameterIuiv and glSamplerParameterIuivOES */
        { 3264, 2044 }, /* glSamplerParameterIuivEXT and glSamplerParameterIuiv */
        { 3264, 3265 }, /* glSamplerParameterIuivEXT and glSamplerParameterIuivOES */
        { 3265, 2044 }, /* glSamplerParameterIuivOES and glSamplerParameterIuiv */
        { 3265, 3264 }, /* glSamplerParameterIuivOES and glSamplerParameterIuivEXT */
        { 2053, 3269 }, /* glScissorArrayv and glScissorArrayvNV */
        { 2053, 3270 }, /* glScissorArrayv and glScissorArrayvOES */
        { 3269, 2053 }, /* glScissorArrayvNV and glScissorArrayv */
        { 3269, 3270 }, /* glScissorArrayvNV and glScissorArrayvOES */
        { 3270, 2053 }, /* glScissorArrayvOES and glScissorArrayv */
        { 3270, 3269 }, /* glScissorArrayvOES and glScissorArrayvNV */
        { 2056, 3271 }, /* glScissorIndexed and glScissorIndexedNV */
        { 2056, 3272 }, /* glScissorIndexed and glScissorIndexedOES */
        { 3271, 2056 }, /* glScissorIndexedNV and glScissorIndexed */
        { 3271, 3272 }, /* glScissorIndexedNV and glScissorIndexedOES */
        { 3272, 2056 }, /* glScissorIndexedOES and glScissorIndexed */
        { 3272, 3271 }, /* glScissorIndexedOES and glScissorIndexedNV */
        { 2057, 3273 }, /* glScissorIndexedv and glScissorIndexedvNV */
        { 2057, 3274 }, /* glScissorIndexedv and glScissorIndexedvOES */
        { 3273, 2057 }, /* glScissorIndexedvNV and glScissorIndexedv */
        { 3273, 3274 }, /* glScissorIndexedvNV and glScissorIndexedvOES */
        { 3274, 2057 }, /* glScissorIndexedvOES and glScissorIndexedv */
        { 3274, 3273 }, /* glScissorIndexedvOES and glScissorIndexedvNV */
        { 2058, 2059 }, /* glSecondaryColor3b and glSecondaryColor3bEXT */
        { 2059, 2058 }, /* glSecondaryColor3bEXT and glSecondaryColor3b */
        { 2060, 2061 }, /* glSecondaryColor3bv and glSecondaryColor3bvEXT */
        { 2061, 2060 }, /* glSecondaryColor3bvEXT and glSecondaryColor3bv */
        { 2062, 2063 }, /* glSecondaryColor3d and glSecondaryColor3dEXT */
        { 2063, 2062 }, /* glSecondaryColor3dEXT and glSecondaryColor3d */
        { 2064, 2065 }, /* glSecondaryColor3dv and glSecondaryColor3dvEXT */
        { 2065, 2064 }, /* glSecondaryColor3dvEXT and glSecondaryColor3dv */
        { 2066, 2067 }, /* glSecondaryColor3f and glSecondaryColor3fEXT */
        { 2067, 2066 }, /* glSecondaryColor3fEXT and glSecondaryColor3f */
        { 2068, 2069 }, /* glSecondaryColor3fv and glSecondaryColor3fvEXT */
        { 2069, 2068 }, /* glSecondaryColor3fvEXT and glSecondaryColor3fv */
        { 2072, 2073 }, /* glSecondaryColor3i and glSecondaryColor3iEXT */
        { 2073, 2072 }, /* glSecondaryColor3iEXT and glSecondaryColor3i */
        { 2074, 2075 }, /* glSecondaryColor3iv and glSecondaryColor3ivEXT */
        { 2075, 2074 }, /* glSecondaryColor3ivEXT and glSecondaryColor3iv */
        { 2076, 2077 }, /* glSecondaryColor3s and glSecondaryColor3sEXT */
        { 2077, 2076 }, /* glSecondaryColor3sEXT and glSecondaryColor3s */
        { 2078, 2079 }, /* glSecondaryColor3sv and glSecondaryColor3svEXT */
        { 2079, 2078 }, /* glSecondaryColor3svEXT and glSecondaryColor3sv */
        { 2080, 2081 }, /* glSecondaryColor3ub and glSecondaryColor3ubEXT */
        { 2081, 2080 }, /* glSecondaryColor3ubEXT and glSecondaryColor3ub */
        { 2082, 2083 }, /* glSecondaryColor3ubv and glSecondaryColor3ubvEXT */
        { 2083, 2082 }, /* glSecondaryColor3ubvEXT and glSecondaryColor3ubv */
        { 2084, 2085 }, /* glSecondaryColor3ui and glSecondaryColor3uiEXT */
        { 2085, 2084 }, /* glSecondaryColor3uiEXT and glSecondaryColor3ui */
        { 2086, 2087 }, /* glSecondaryColor3uiv and glSecondaryColor3uivEXT */
        { 2087, 2086 }, /* glSecondaryColor3uivEXT and glSecondaryColor3uiv */
        { 2088, 2089 }, /* glSecondaryColor3us and glSecondaryColor3usEXT */
        { 2089, 2088 }, /* glSecondaryColor3usEXT and glSecondaryColor3us */
        { 2090, 2091 }, /* glSecondaryColor3usv and glSecondaryColor3usvEXT */
        { 2091, 2090 }, /* glSecondaryColor3usvEXT and glSecondaryColor3usv */
        { 2095, 2096 }, /* glSecondaryColorPointer and glSecondaryColorPointerEXT */
        { 2096, 2095 }, /* glSecondaryColorPointerEXT and glSecondaryColorPointer */
        { 2102, 2103 }, /* glSeparableFilter2D and glSeparableFilter2DEXT */
        { 2103, 2102 }, /* glSeparableFilter2DEXT and glSeparableFilter2D */
        { 2115, 2116 }, /* glShaderSource and glShaderSourceARB */
        { 2116, 2115 }, /* glShaderSourceARB and glShaderSource */
        { 2127, 2128 }, /* glSpecializeShader and glSpecializeShaderARB */
        { 2128, 2127 }, /* glSpecializeShaderARB and glSpecializeShader */
        { 2144, 2145 }, /* glStencilOpSeparate and glStencilOpSeparateATI */
        { 2145, 2144 }, /* glStencilOpSeparateATI and glStencilOpSeparate */
        { 2177, 2178 }, /* glTexBuffer and glTexBufferARB */
        { 2177, 2179 }, /* glTexBuffer and glTexBufferEXT */
        { 2177, 3279 }, /* glTexBuffer and glTexBufferOES */
        { 2178, 2177 }, /* glTexBufferARB and glTexBuffer */
        { 2178, 2179 }, /* glTexBufferARB and glTexBufferEXT */
        { 2178, 3279 }, /* glTexBufferARB and glTexBufferOES */
        { 2179, 2177 }, /* glTexBufferEXT and glTexBuffer */
        { 2179, 2178 }, /* glTexBufferEXT and glTexBufferARB */
        { 2179, 3279 }, /* glTexBufferEXT and glTexBufferOES */
        { 3279, 2177 }, /* glTexBufferOES and glTexBuffer */
        { 3279, 2178 }, /* glTexBufferOES and glTexBufferARB */
        { 3279, 2179 }, /* glTexBufferOES and glTexBufferEXT */
        { 2180, 3280 }, /* glTexBufferRange and glTexBufferRangeEXT */
        { 2180, 3281 }, /* glTexBufferRange and glTexBufferRangeOES */
        { 3280, 2180 }, /* glTexBufferRangeEXT and glTexBufferRange */
        { 3280, 3281 }, /* glTexBufferRangeEXT and glTexBufferRangeOES */
        { 3281, 2180 }, /* glTexBufferRangeOES and glTexBufferRange */
        { 3281, 3280 }, /* glTexBufferRangeOES and glTexBufferRangeEXT */
        { 2286, 2287 }, /* glTexImage3D and glTexImage3DEXT */
        { 2287, 2286 }, /* glTexImage3DEXT and glTexImage3D */
        { 2291, 3287 }, /* glTexPageCommitmentARB and glTexPageCommitmentEXT */
        { 3287, 2291 }, /* glTexPageCommitmentEXT and glTexPageCommitmentARB */
        { 2293, 2294 }, /* glTexParameterIiv and glTexParameterIivEXT */
        { 2293, 3288 }, /* glTexParameterIiv and glTexParameterIivOES */
        { 2294, 2293 }, /* glTexParameterIivEXT and glTexParameterIiv */
        { 2294, 3288 }, /* glTexParameterIivEXT and glTexParameterIivOES */
        { 3288, 2293 }, /* glTexParameterIivOES and glTexParameterIiv */
        { 3288, 2294 }, /* glTexParameterIivOES and glTexParameterIivEXT */
        { 2295, 2296 }, /* glTexParameterIuiv and glTexParameterIuivEXT */
        { 2295, 3290 }, /* glTexParameterIuiv and glTexParameterIuivOES */
        { 2296, 2295 }, /* glTexParameterIuivEXT and glTexParameterIuiv */
        { 2296, 3290 }, /* glTexParameterIuivEXT and glTexParameterIuivOES */
        { 3290, 2295 }, /* glTexParameterIuivOES and glTexParameterIuiv */
        { 3290, 2296 }, /* glTexParameterIuivOES and glTexParameterIuivEXT */
        { 2304, 2305 }, /* glTexStorage1D and glTexStorage1DEXT */
        { 2305, 2304 }, /* glTexStorage1DEXT and glTexStorage1D */
        { 2306, 2307 }, /* glTexStorage2D and glTexStorage2DEXT */
        { 2307, 2306 }, /* glTexStorage2DEXT and glTexStorage2D */
        { 2309, 2310 }, /* glTexStorage3D and glTexStorage3DEXT */
        { 2310, 2309 }, /* glTexStorage3DEXT and glTexStorage3D */
        { 2311, 3295 }, /* glTexStorage3DMultisample and glTexStorage3DMultisampleOES */
        { 3295, 2311 }, /* glTexStorage3DMultisampleOES and glTexStorage3DMultisample */
        { 2322, 2323 }, /* glTexSubImage1D and glTexSubImage1DEXT */
        { 2323, 2322 }, /* glTexSubImage1DEXT and glTexSubImage1D */
        { 2324, 2325 }, /* glTexSubImage2D and glTexSubImage2DEXT */
        { 2325, 2324 }, /* glTexSubImage2DEXT and glTexSubImage2D */
        { 2326, 2327 }, /* glTexSubImage3D and glTexSubImage3DEXT */
        { 2327, 2326 }, /* glTexSubImage3DEXT and glTexSubImage3D */
        { 2385, 3302 }, /* glTextureView and glTextureViewEXT */
        { 2385, 3303 }, /* glTextureView and glTextureViewOES */
        { 3302, 2385 }, /* glTextureViewEXT and glTextureView */
        { 3302, 3303 }, /* glTextureViewEXT and glTextureViewOES */
        { 3303, 2385 }, /* glTextureViewOES and glTextureView */
        { 3303, 3302 }, /* glTextureViewOES and glTextureViewEXT */
        { 2391, 2392 }, /* glTransformFeedbackVaryings and glTransformFeedbackVaryingsEXT */
        { 2392, 2391 }, /* glTransformFeedbackVaryingsEXT and glTransformFeedbackVaryings */
        { 2400, 2401 }, /* glUniform1f and glUniform1fARB */
        { 2401, 2400 }, /* glUniform1fARB and glUniform1f */
        { 2402, 2403 }, /* glUniform1fv and glUniform1fvARB */
        { 2403, 2402 }, /* glUniform1fvARB and glUniform1fv */
        { 2404, 2409 }, /* glUniform1i and glUniform1iARB */
        { 2409, 2404 }, /* glUniform1iARB and glUniform1i */
        { 2410, 2411 }, /* glUniform1iv and glUniform1ivARB */
        { 2411, 2410 }, /* glUniform1ivARB and glUniform1iv */
        { 2412, 2417 }, /* glUniform1ui and glUniform1uiEXT */
        { 2417, 2412 }, /* glUniform1uiEXT and glUniform1ui */
        { 2418, 2419 }, /* glUniform1uiv and glUniform1uivEXT */
        { 2419, 2418 }, /* glUniform1uivEXT and glUniform1uiv */
        { 2422, 2423 }, /* glUniform2f and glUniform2fARB */
        { 2423, 2422 }, /* glUniform2fARB and glUniform2f */
        { 2424, 2425 }, /* glUniform2fv and glUniform2fvARB */
        { 2425, 2424 }, /* glUniform2fvARB and glUniform2fv */
        { 2426, 2431 }, /* glUniform2i and glUniform2iARB */
        { 2431, 2426 }, /* glUniform2iARB and glUniform2i */
        { 2432, 2433 }, /* glUniform2iv and glUniform2ivARB */
        { 2433, 2432 }, /* glUniform2ivARB and glUniform2iv */
        { 2434, 2439 }, /* glUniform2ui and glUniform2uiEXT */
        { 2439, 2434 }, /* glUniform2uiEXT and glUniform2ui */
        { 2440, 2441 }, /* glUniform2uiv and glUniform2uivEXT */
        { 2441, 2440 }, /* glUniform2uivEXT and glUniform2uiv */
        { 2444, 2445 }, /* glUniform3f and glUniform3fARB */
        { 2445, 2444 }, /* glUniform3fARB and glUniform3f */
        { 2446, 2447 }, /* glUniform3fv and glUniform3fvARB */
        { 2447, 2446 }, /* glUniform3fvARB and glUniform3fv */
        { 2448, 2453 }, /* glUniform3i and glUniform3iARB */
        { 2453, 2448 }, /* glUniform3iARB and glUniform3i */
        { 2454, 2455 }, /* glUniform3iv and glUniform3ivARB */
        { 2455, 2454 }, /* glUniform3ivARB and glUniform3iv */
        { 2456, 2461 }, /* glUniform3ui and glUniform3uiEXT */
        { 2461, 2456 }, /* glUniform3uiEXT and glUniform3ui */
        { 2462, 2463 }, /* glUniform3uiv and glUniform3uivEXT */
        { 2463, 2462 }, /* glUniform3uivEXT and glUniform3uiv */
        { 2466, 2467 }, /* glUniform4f and glUniform4fARB */
        { 2467, 2466 }, /* glUniform4fARB and glUniform4f */
        { 2468, 2469 }, /* glUniform4fv and glUniform4fvARB */
        { 2469, 2468 }, /* glUniform4fvARB and glUniform4fv */
        { 2470, 2475 }, /* glUniform4i and glUniform4iARB */
        { 2475, 2470 }, /* glUniform4iARB and glUniform4i */
        { 2476, 2477 }, /* glUniform4iv and glUniform4ivARB */
        { 2477, 2476 }, /* glUniform4ivARB and glUniform4iv */
        { 2478, 2483 }, /* glUniform4ui and glUniform4uiEXT */
        { 2483, 2478 }, /* glUniform4uiEXT and glUniform4ui */
        { 2484, 2485 }, /* glUniform4uiv and glUniform4uivEXT */
        { 2485, 2484 }, /* glUniform4uivEXT and glUniform4uiv */
        { 2488, 3304 }, /* glUniformHandleui64ARB and glUniformHandleui64IMG */
        { 3304, 2488 }, /* glUniformHandleui64IMG and glUniformHandleui64ARB */
        { 2490, 3305 }, /* glUniformHandleui64vARB and glUniformHandleui64vIMG */
        { 3305, 2490 }, /* glUniformHandleui64vIMG and glUniformHandleui64vARB */
        { 2493, 2494 }, /* glUniformMatrix2fv and glUniformMatrix2fvARB */
        { 2494, 2493 }, /* glUniformMatrix2fvARB and glUniformMatrix2fv */
        { 2496, 3306 }, /* glUniformMatrix2x3fv and glUniformMatrix2x3fvNV */
        { 3306, 2496 }, /* glUniformMatrix2x3fvNV and glUniformMatrix2x3fv */
        { 2498, 3307 }, /* glUniformMatrix2x4fv and glUniformMatrix2x4fvNV */
        { 3307, 2498 }, /* glUniformMatrix2x4fvNV and glUniformMatrix2x4fv */
        { 2500, 2501 }, /* glUniformMatrix3fv and glUniformMatrix3fvARB */
        { 2501, 2500 }, /* glUniformMatrix3fvARB and glUniformMatrix3fv */
        { 2503, 3308 }, /* glUniformMatrix3x2fv and glUniformMatrix3x2fvNV */
        { 3308, 2503 }, /* glUniformMatrix3x2fvNV and glUniformMatrix3x2fv */
        { 2505, 3309 }, /* glUniformMatrix3x4fv and glUniformMatrix3x4fvNV */
        { 3309, 2505 }, /* glUniformMatrix3x4fvNV and glUniformMatrix3x4fv */
        { 2507, 2508 }, /* glUniformMatrix4fv and glUniformMatrix4fvARB */
        { 2508, 2507 }, /* glUniformMatrix4fvARB and glUniformMatrix4fv */
        { 2510, 3310 }, /* glUniformMatrix4x2fv and glUniformMatrix4x2fvNV */
        { 3310, 2510 }, /* glUniformMatrix4x2fvNV and glUniformMatrix4x2fv */
        { 2512, 3311 }, /* glUniformMatrix4x3fv and glUniformMatrix4x3fvNV */
        { 3311, 2512 }, /* glUniformMatrix4x3fvNV and glUniformMatrix4x3fv */
        { 2517, 2518 }, /* glUnmapBuffer and glUnmapBufferARB */
        { 2517, 3312 }, /* glUnmapBuffer and glUnmapBufferOES */
        { 2518, 2517 }, /* glUnmapBufferARB and glUnmapBuffer */
        { 2518, 3312 }, /* glUnmapBufferARB and glUnmapBufferOES */
        { 3312, 2517 }, /* glUnmapBufferOES and glUnmapBuffer */
        { 3312, 2518 }, /* glUnmapBufferOES and glUnmapBufferARB */
        { 2525, 2526 }, /* glUseProgram and glUseProgramObjectARB */
        { 2526, 2525 }, /* glUseProgramObjectARB and glUseProgram */
        { 2540, 2541 }, /* glValidateProgram and glValidateProgramARB */
        { 2541, 2540 }, /* glValidateProgramARB and glValidateProgram */
        { 2625, 2626 }, /* glVertexAttrib1d and glVertexAttrib1dARB */
        { 2625, 2627 }, /* glVertexAttrib1d and glVertexAttrib1dNV */
        { 2626, 2625 }, /* glVertexAttrib1dARB and glVertexAttrib1d */
        { 2626, 2627 }, /* glVertexAttrib1dARB and glVertexAttrib1dNV */
        { 2627, 2625 }, /* glVertexAttrib1dNV and glVertexAttrib1d */
        { 2627, 2626 }, /* glVertexAttrib1dNV and glVertexAttrib1dARB */
        { 2628, 2629 }, /* glVertexAttrib1dv and glVertexAttrib1dvARB */
        { 2628, 2630 }, /* glVertexAttrib1dv and glVertexAttrib1dvNV */
        { 2629, 2628 }, /* glVertexAttrib1dvARB and glVertexAttrib1dv */
        { 2629, 2630 }, /* glVertexAttrib1dvARB and glVertexAttrib1dvNV */
        { 2630, 2628 }, /* glVertexAttrib1dvNV and glVertexAttrib1dv */
        { 2630, 2629 }, /* glVertexAttrib1dvNV and glVertexAttrib1dvARB */
        { 2631, 2632 }, /* glVertexAttrib1f and glVertexAttrib1fARB */
        { 2631, 2633 }, /* glVertexAttrib1f and glVertexAttrib1fNV */
        { 2632, 2631 }, /* glVertexAttrib1fARB and glVertexAttrib1f */
        { 2632, 2633 }, /* glVertexAttrib1fARB and glVertexAttrib1fNV */
        { 2633, 2631 }, /* glVertexAttrib1fNV and glVertexAttrib1f */
        { 2633, 2632 }, /* glVertexAttrib1fNV and glVertexAttrib1fARB */
        { 2634, 2635 }, /* glVertexAttrib1fv and glVertexAttrib1fvARB */
        { 2634, 2636 }, /* glVertexAttrib1fv and glVertexAttrib1fvNV */
        { 2635, 2634 }, /* glVertexAttrib1fvARB and glVertexAttrib1fv */
        { 2635, 2636 }, /* glVertexAttrib1fvARB and glVertexAttrib1fvNV */
        { 2636, 2634 }, /* glVertexAttrib1fvNV and glVertexAttrib1fv */
        { 2636, 2635 }, /* glVertexAttrib1fvNV and glVertexAttrib1fvARB */
        { 2639, 2640 }, /* glVertexAttrib1s and glVertexAttrib1sARB */
        { 2639, 2641 }, /* glVertexAttrib1s and glVertexAttrib1sNV */
        { 2640, 2639 }, /* glVertexAttrib1sARB and glVertexAttrib1s */
        { 2640, 2641 }, /* glVertexAttrib1sARB and glVertexAttrib1sNV */
        { 2641, 2639 }, /* glVertexAttrib1sNV and glVertexAttrib1s */
        { 2641, 2640 }, /* glVertexAttrib1sNV and glVertexAttrib1sARB */
        { 2642, 2643 }, /* glVertexAttrib1sv and glVertexAttrib1svARB */
        { 2642, 2644 }, /* glVertexAttrib1sv and glVertexAttrib1svNV */
        { 2643, 2642 }, /* glVertexAttrib1svARB and glVertexAttrib1sv */
        { 2643, 2644 }, /* glVertexAttrib1svARB and glVertexAttrib1svNV */
        { 2644, 2642 }, /* glVertexAttrib1svNV and glVertexAttrib1sv */
        { 2644, 2643 }, /* glVertexAttrib1svNV and glVertexAttrib1svARB */
        { 2645, 2646 }, /* glVertexAttrib2d and glVertexAttrib2dARB */
        { 2645, 2647 }, /* glVertexAttrib2d and glVertexAttrib2dNV */
        { 2646, 2645 }, /* glVertexAttrib2dARB and glVertexAttrib2d */
        { 2646, 2647 }, /* glVertexAttrib2dARB and glVertexAttrib2dNV */
        { 2647, 2645 }, /* glVertexAttrib2dNV and glVertexAttrib2d */
        { 2647, 2646 }, /* glVertexAttrib2dNV and glVertexAttrib2dARB */
        { 2648, 2649 }, /* glVertexAttrib2dv and glVertexAttrib2dvARB */
        { 2648, 2650 }, /* glVertexAttrib2dv and glVertexAttrib2dvNV */
        { 2649, 2648 }, /* glVertexAttrib2dvARB and glVertexAttrib2dv */
        { 2649, 2650 }, /* glVertexAttrib2dvARB and glVertexAttrib2dvNV */
        { 2650, 2648 }, /* glVertexAttrib2dvNV and glVertexAttrib2dv */
        { 2650, 2649 }, /* glVertexAttrib2dvNV and glVertexAttrib2dvARB */
        { 2651, 2652 }, /* glVertexAttrib2f and glVertexAttrib2fARB */
        { 2651, 2653 }, /* glVertexAttrib2f and glVertexAttrib2fNV */
        { 2652, 2651 }, /* glVertexAttrib2fARB and glVertexAttrib2f */
        { 2652, 2653 }, /* glVertexAttrib2fARB and glVertexAttrib2fNV */
        { 2653, 2651 }, /* glVertexAttrib2fNV and glVertexAttrib2f */
        { 2653, 2652 }, /* glVertexAttrib2fNV and glVertexAttrib2fARB */
        { 2654, 2655 }, /* glVertexAttrib2fv and glVertexAttrib2fvARB */
        { 2654, 2656 }, /* glVertexAttrib2fv and glVertexAttrib2fvNV */
        { 2655, 2654 }, /* glVertexAttrib2fvARB and glVertexAttrib2fv */
        { 2655, 2656 }, /* glVertexAttrib2fvARB and glVertexAttrib2fvNV */
        { 2656, 2654 }, /* glVertexAttrib2fvNV and glVertexAttrib2fv */
        { 2656, 2655 }, /* glVertexAttrib2fvNV and glVertexAttrib2fvARB */
        { 2659, 2660 }, /* glVertexAttrib2s and glVertexAttrib2sARB */
        { 2659, 2661 }, /* glVertexAttrib2s and glVertexAttrib2sNV */
        { 2660, 2659 }, /* glVertexAttrib2sARB and glVertexAttrib2s */
        { 2660, 2661 }, /* glVertexAttrib2sARB and glVertexAttrib2sNV */
        { 2661, 2659 }, /* glVertexAttrib2sNV and glVertexAttrib2s */
        { 2661, 2660 }, /* glVertexAttrib2sNV and glVertexAttrib2sARB */
        { 2662, 2663 }, /* glVertexAttrib2sv and glVertexAttrib2svARB */
        { 2662, 2664 }, /* glVertexAttrib2sv and glVertexAttrib2svNV */
        { 2663, 2662 }, /* glVertexAttrib2svARB and glVertexAttrib2sv */
        { 2663, 2664 }, /* glVertexAttrib2svARB and glVertexAttrib2svNV */
        { 2664, 2662 }, /* glVertexAttrib2svNV and glVertexAttrib2sv */
        { 2664, 2663 }, /* glVertexAttrib2svNV and glVertexAttrib2svARB */
        { 2665, 2666 }, /* glVertexAttrib3d and glVertexAttrib3dARB */
        { 2665, 2667 }, /* glVertexAttrib3d and glVertexAttrib3dNV */
        { 2666, 2665 }, /* glVertexAttrib3dARB and glVertexAttrib3d */
        { 2666, 2667 }, /* glVertexAttrib3dARB and glVertexAttrib3dNV */
        { 2667, 2665 }, /* glVertexAttrib3dNV and glVertexAttrib3d */
        { 2667, 2666 }, /* glVertexAttrib3dNV and glVertexAttrib3dARB */
        { 2668, 2669 }, /* glVertexAttrib3dv and glVertexAttrib3dvARB */
        { 2668, 2670 }, /* glVertexAttrib3dv and glVertexAttrib3dvNV */
        { 2669, 2668 }, /* glVertexAttrib3dvARB and glVertexAttrib3dv */
        { 2669, 2670 }, /* glVertexAttrib3dvARB and glVertexAttrib3dvNV */
        { 2670, 2668 }, /* glVertexAttrib3dvNV and glVertexAttrib3dv */
        { 2670, 2669 }, /* glVertexAttrib3dvNV and glVertexAttrib3dvARB */
        { 2671, 2672 }, /* glVertexAttrib3f and glVertexAttrib3fARB */
        { 2671, 2673 }, /* glVertexAttrib3f and glVertexAttrib3fNV */
        { 2672, 2671 }, /* glVertexAttrib3fARB and glVertexAttrib3f */
        { 2672, 2673 }, /* glVertexAttrib3fARB and glVertexAttrib3fNV */
        { 2673, 2671 }, /* glVertexAttrib3fNV and glVertexAttrib3f */
        { 2673, 2672 }, /* glVertexAttrib3fNV and glVertexAttrib3fARB */
        { 2674, 2675 }, /* glVertexAttrib3fv and glVertexAttrib3fvARB */
        { 2674, 2676 }, /* glVertexAttrib3fv and glVertexAttrib3fvNV */
        { 2675, 2674 }, /* glVertexAttrib3fvARB and glVertexAttrib3fv */
        { 2675, 2676 }, /* glVertexAttrib3fvARB and glVertexAttrib3fvNV */
        { 2676, 2674 }, /* glVertexAttrib3fvNV and glVertexAttrib3fv */
        { 2676, 2675 }, /* glVertexAttrib3fvNV and glVertexAttrib3fvARB */
        { 2679, 2680 }, /* glVertexAttrib3s and glVertexAttrib3sARB */
        { 2679, 2681 }, /* glVertexAttrib3s and glVertexAttrib3sNV */
        { 2680, 2679 }, /* glVertexAttrib3sARB and glVertexAttrib3s */
        { 2680, 2681 }, /* glVertexAttrib3sARB and glVertexAttrib3sNV */
        { 2681, 2679 }, /* glVertexAttrib3sNV and glVertexAttrib3s */
        { 2681, 2680 }, /* glVertexAttrib3sNV and glVertexAttrib3sARB */
        { 2682, 2683 }, /* glVertexAttrib3sv and glVertexAttrib3svARB */
        { 2682, 2684 }, /* glVertexAttrib3sv and glVertexAttrib3svNV */
        { 2683, 2682 }, /* glVertexAttrib3svARB and glVertexAttrib3sv */
        { 2683, 2684 }, /* glVertexAttrib3svARB and glVertexAttrib3svNV */
        { 2684, 2682 }, /* glVertexAttrib3svNV and glVertexAttrib3sv */
        { 2684, 2683 }, /* glVertexAttrib3svNV and glVertexAttrib3svARB */
        { 2699, 2700 }, /* glVertexAttrib4bv and glVertexAttrib4bvARB */
        { 2700, 2699 }, /* glVertexAttrib4bvARB and glVertexAttrib4bv */
        { 2701, 2702 }, /* glVertexAttrib4d and glVertexAttrib4dARB */
        { 2701, 2703 }, /* glVertexAttrib4d and glVertexAttrib4dNV */
        { 2702, 2701 }, /* glVertexAttrib4dARB and glVertexAttrib4d */
        { 2702, 2703 }, /* glVertexAttrib4dARB and glVertexAttrib4dNV */
        { 2703, 2701 }, /* glVertexAttrib4dNV and glVertexAttrib4d */
        { 2703, 2702 }, /* glVertexAttrib4dNV and glVertexAttrib4dARB */
        { 2704, 2705 }, /* glVertexAttrib4dv and glVertexAttrib4dvARB */
        { 2704, 2706 }, /* glVertexAttrib4dv and glVertexAttrib4dvNV */
        { 2705, 2704 }, /* glVertexAttrib4dvARB and glVertexAttrib4dv */
        { 2705, 2706 }, /* glVertexAttrib4dvARB and glVertexAttrib4dvNV */
        { 2706, 2704 }, /* glVertexAttrib4dvNV and glVertexAttrib4dv */
        { 2706, 2705 }, /* glVertexAttrib4dvNV and glVertexAttrib4dvARB */
        { 2707, 2708 }, /* glVertexAttrib4f and glVertexAttrib4fARB */
        { 2707, 2709 }, /* glVertexAttrib4f and glVertexAttrib4fNV */
        { 2708, 2707 }, /* glVertexAttrib4fARB and glVertexAttrib4f */
        { 2708, 2709 }, /* glVertexAttrib4fARB and glVertexAttrib4fNV */
        { 2709, 2707 }, /* glVertexAttrib4fNV and glVertexAttrib4f */
        { 2709, 2708 }, /* glVertexAttrib4fNV and glVertexAttrib4fARB */
        { 2710, 2711 }, /* glVertexAttrib4fv and glVertexAttrib4fvARB */
        { 2710, 2712 }, /* glVertexAttrib4fv and glVertexAttrib4fvNV */
        { 2711, 2710 }, /* glVertexAttrib4fvARB and glVertexAttrib4fv */
        { 2711, 2712 }, /* glVertexAttrib4fvARB and glVertexAttrib4fvNV */
        { 2712, 2710 }, /* glVertexAttrib4fvNV and glVertexAttrib4fv */
        { 2712, 2711 }, /* glVertexAttrib4fvNV and glVertexAttrib4fvARB */
        { 2715, 2716 }, /* glVertexAttrib4iv and glVertexAttrib4ivARB */
        { 2716, 2715 }, /* glVertexAttrib4ivARB and glVertexAttrib4iv */
        { 2685, 2686 }, /* glVertexAttrib4Nbv and glVertexAttrib4NbvARB */
        { 2686, 2685 }, /* glVertexAttrib4NbvARB and glVertexAttrib4Nbv */
        { 2687, 2688 }, /* glVertexAttrib4Niv and glVertexAttrib4NivARB */
        { 2688, 2687 }, /* glVertexAttrib4NivARB and glVertexAttrib4Niv */
        { 2689, 2690 }, /* glVertexAttrib4Nsv and glVertexAttrib4NsvARB */
        { 2690, 2689 }, /* glVertexAttrib4NsvARB and glVertexAttrib4Nsv */
        { 2691, 2692 }, /* glVertexAttrib4Nub and glVertexAttrib4NubARB */
        { 2691, 2723 }, /* glVertexAttrib4Nub and glVertexAttrib4ubNV */
        { 2692, 2691 }, /* glVertexAttrib4NubARB and glVertexAttrib4Nub */
        { 2692, 2723 }, /* glVertexAttrib4NubARB and glVertexAttrib4ubNV */
        { 2693, 2694 }, /* glVertexAttrib4Nubv and glVertexAttrib4NubvARB */
        { 2693, 2726 }, /* glVertexAttrib4Nubv and glVertexAttrib4ubvNV */
        { 2694, 2693 }, /* glVertexAttrib4NubvARB and glVertexAttrib4Nubv */
        { 2694, 2726 }, /* glVertexAttrib4NubvARB and glVertexAttrib4ubvNV */
        { 2695, 2696 }, /* glVertexAttrib4Nuiv and glVertexAttrib4NuivARB */
        { 2696, 2695 }, /* glVertexAttrib4NuivARB and glVertexAttrib4Nuiv */
        { 2697, 2698 }, /* glVertexAttrib4Nusv and glVertexAttrib4NusvARB */
        { 2698, 2697 }, /* glVertexAttrib4NusvARB and glVertexAttrib4Nusv */
        { 2717, 2718 }, /* glVertexAttrib4s and glVertexAttrib4sARB */
        { 2717, 2719 }, /* glVertexAttrib4s and glVertexAttrib4sNV */
        { 2718, 2717 }, /* glVertexAttrib4sARB and glVertexAttrib4s */
        { 2718, 2719 }, /* glVertexAttrib4sARB and glVertexAttrib4sNV */
        { 2719, 2717 }, /* glVertexAttrib4sNV and glVertexAttrib4s */
        { 2719, 2718 }, /* glVertexAttrib4sNV and glVertexAttrib4sARB */
        { 2720, 2721 }, /* glVertexAttrib4sv and glVertexAttrib4svARB */
        { 2720, 2722 }, /* glVertexAttrib4sv and glVertexAttrib4svNV */
        { 2721, 2720 }, /* glVertexAttrib4svARB and glVertexAttrib4sv */
        { 2721, 2722 }, /* glVertexAttrib4svARB and glVertexAttrib4svNV */
        { 2722, 2720 }, /* glVertexAttrib4svNV and glVertexAttrib4sv */
        { 2722, 2721 }, /* glVertexAttrib4svNV and glVertexAttrib4svARB */
        { 2723, 2691 }, /* glVertexAttrib4ubNV and glVertexAttrib4Nub */
        { 2723, 2692 }, /* glVertexAttrib4ubNV and glVertexAttrib4NubARB */
        { 2724, 2725 }, /* glVertexAttrib4ubv and glVertexAttrib4ubvARB */
        { 2725, 2724 }, /* glVertexAttrib4ubvARB and glVertexAttrib4ubv */
        { 2726, 2693 }, /* glVertexAttrib4ubvNV and glVertexAttrib4Nubv */
        { 2726, 2694 }, /* glVertexAttrib4ubvNV and glVertexAttrib4NubvARB */
        { 2727, 2728 }, /* glVertexAttrib4uiv and glVertexAttrib4uivARB */
        { 2728, 2727 }, /* glVertexAttrib4uivARB and glVertexAttrib4uiv */
        { 2729, 2730 }, /* glVertexAttrib4usv and glVertexAttrib4usvARB */
        { 2730, 2729 }, /* glVertexAttrib4usvARB and glVertexAttrib4usv */
        { 2733, 3315 }, /* glVertexAttribDivisor and glVertexAttribDivisorANGLE */
        { 2733, 2734 }, /* glVertexAttribDivisor and glVertexAttribDivisorARB */
        { 2733, 3316 }, /* glVertexAttribDivisor and glVertexAttribDivisorEXT */
        { 2733, 3317 }, /* glVertexAttribDivisor and glVertexAttribDivisorNV */
        { 3315, 2733 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisor */
        { 3315, 2734 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisorARB */
        { 3315, 3316 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisorEXT */
        { 3315, 3317 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisorNV */
        { 2734, 2733 }, /* glVertexAttribDivisorARB and glVertexAttribDivisor */
        { 2734, 3315 }, /* glVertexAttribDivisorARB and glVertexAttribDivisorANGLE */
        { 2734, 3316 }, /* glVertexAttribDivisorARB and glVertexAttribDivisorEXT */
        { 2734, 3317 }, /* glVertexAttribDivisorARB and glVertexAttribDivisorNV */
        { 3316, 2733 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisor */
        { 3316, 3315 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisorANGLE */
        { 3316, 2734 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisorARB */
        { 3316, 3317 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisorNV */
        { 3317, 2733 }, /* glVertexAttribDivisorNV and glVertexAttribDivisor */
        { 3317, 3315 }, /* glVertexAttribDivisorNV and glVertexAttribDivisorANGLE */
        { 3317, 2734 }, /* glVertexAttribDivisorNV and glVertexAttribDivisorARB */
        { 3317, 3316 }, /* glVertexAttribDivisorNV and glVertexAttribDivisorEXT */
        { 2737, 2738 }, /* glVertexAttribI1i and glVertexAttribI1iEXT */
        { 2738, 2737 }, /* glVertexAttribI1iEXT and glVertexAttribI1i */
        { 2739, 2740 }, /* glVertexAttribI1iv and glVertexAttribI1ivEXT */
        { 2740, 2739 }, /* glVertexAttribI1ivEXT and glVertexAttribI1iv */
        { 2741, 2742 }, /* glVertexAttribI1ui and glVertexAttribI1uiEXT */
        { 2742, 2741 }, /* glVertexAttribI1uiEXT and glVertexAttribI1ui */
        { 2743, 2744 }, /* glVertexAttribI1uiv and glVertexAttribI1uivEXT */
        { 2744, 2743 }, /* glVertexAttribI1uivEXT and glVertexAttribI1uiv */
        { 2745, 2746 }, /* glVertexAttribI2i and glVertexAttribI2iEXT */
        { 2746, 2745 }, /* glVertexAttribI2iEXT and glVertexAttribI2i */
        { 2747, 2748 }, /* glVertexAttribI2iv and glVertexAttribI2ivEXT */
        { 2748, 2747 }, /* glVertexAttribI2ivEXT and glVertexAttribI2iv */
        { 2749, 2750 }, /* glVertexAttribI2ui and glVertexAttribI2uiEXT */
        { 2750, 2749 }, /* glVertexAttribI2uiEXT and glVertexAttribI2ui */
        { 2751, 2752 }, /* glVertexAttribI2uiv and glVertexAttribI2uivEXT */
        { 2752, 2751 }, /* glVertexAttribI2uivEXT and glVertexAttribI2uiv */
        { 2753, 2754 }, /* glVertexAttribI3i and glVertexAttribI3iEXT */
        { 2754, 2753 }, /* glVertexAttribI3iEXT and glVertexAttribI3i */
        { 2755, 2756 }, /* glVertexAttribI3iv and glVertexAttribI3ivEXT */
        { 2756, 2755 }, /* glVertexAttribI3ivEXT and glVertexAttribI3iv */
        { 2757, 2758 }, /* glVertexAttribI3ui and glVertexAttribI3uiEXT */
        { 2758, 2757 }, /* glVertexAttribI3uiEXT and glVertexAttribI3ui */
        { 2759, 2760 }, /* glVertexAttribI3uiv and glVertexAttribI3uivEXT */
        { 2760, 2759 }, /* glVertexAttribI3uivEXT and glVertexAttribI3uiv */
        { 2761, 2762 }, /* glVertexAttribI4bv and glVertexAttribI4bvEXT */
        { 2762, 2761 }, /* glVertexAttribI4bvEXT and glVertexAttribI4bv */
        { 2763, 2764 }, /* glVertexAttribI4i and glVertexAttribI4iEXT */
        { 2764, 2763 }, /* glVertexAttribI4iEXT and glVertexAttribI4i */
        { 2765, 2766 }, /* glVertexAttribI4iv and glVertexAttribI4ivEXT */
        { 2766, 2765 }, /* glVertexAttribI4ivEXT and glVertexAttribI4iv */
        { 2767, 2768 }, /* glVertexAttribI4sv and glVertexAttribI4svEXT */
        { 2768, 2767 }, /* glVertexAttribI4svEXT and glVertexAttribI4sv */
        { 2769, 2770 }, /* glVertexAttribI4ubv and glVertexAttribI4ubvEXT */
        { 2770, 2769 }, /* glVertexAttribI4ubvEXT and glVertexAttribI4ubv */
        { 2771, 2772 }, /* glVertexAttribI4ui and glVertexAttribI4uiEXT */
        { 2772, 2771 }, /* glVertexAttribI4uiEXT and glVertexAttribI4ui */
        { 2773, 2774 }, /* glVertexAttribI4uiv and glVertexAttribI4uivEXT */
        { 2774, 2773 }, /* glVertexAttribI4uivEXT and glVertexAttribI4uiv */
        { 2775, 2776 }, /* glVertexAttribI4usv and glVertexAttribI4usvEXT */
        { 2776, 2775 }, /* glVertexAttribI4usvEXT and glVertexAttribI4usv */
        { 2779, 2780 }, /* glVertexAttribIPointer and glVertexAttribIPointerEXT */
        { 2780, 2779 }, /* glVertexAttribIPointerEXT and glVertexAttribIPointer */
        { 2781, 2782 }, /* glVertexAttribL1d and glVertexAttribL1dEXT */
        { 2782, 2781 }, /* glVertexAttribL1dEXT and glVertexAttribL1d */
        { 2783, 2784 }, /* glVertexAttribL1dv and glVertexAttribL1dvEXT */
        { 2784, 2783 }, /* glVertexAttribL1dvEXT and glVertexAttribL1dv */
        { 2791, 2792 }, /* glVertexAttribL2d and glVertexAttribL2dEXT */
        { 2792, 2791 }, /* glVertexAttribL2dEXT and glVertexAttribL2d */
        { 2793, 2794 }, /* glVertexAttribL2dv and glVertexAttribL2dvEXT */
        { 2794, 2793 }, /* glVertexAttribL2dvEXT and glVertexAttribL2dv */
        { 2799, 2800 }, /* glVertexAttribL3d and glVertexAttribL3dEXT */
        { 2800, 2799 }, /* glVertexAttribL3dEXT and glVertexAttribL3d */
        { 2801, 2802 }, /* glVertexAttribL3dv and glVertexAttribL3dvEXT */
        { 2802, 2801 }, /* glVertexAttribL3dvEXT and glVertexAttribL3dv */
        { 2807, 2808 }, /* glVertexAttribL4d and glVertexAttribL4dEXT */
        { 2808, 2807 }, /* glVertexAttribL4dEXT and glVertexAttribL4d */
        { 2809, 2810 }, /* glVertexAttribL4dv and glVertexAttribL4dvEXT */
        { 2810, 2809 }, /* glVertexAttribL4dvEXT and glVertexAttribL4dv */
        { 2817, 2818 }, /* glVertexAttribLPointer and glVertexAttribLPointerEXT */
        { 2818, 2817 }, /* glVertexAttribLPointerEXT and glVertexAttribLPointer */
        { 2828, 2829 }, /* glVertexAttribPointer and glVertexAttribPointerARB */
        { 2829, 2828 }, /* glVertexAttribPointerARB and glVertexAttribPointer */
        { 2905, 3318 }, /* glViewportArrayv and glViewportArrayvNV */
        { 2905, 3319 }, /* glViewportArrayv and glViewportArrayvOES */
        { 3318, 2905 }, /* glViewportArrayvNV and glViewportArrayv */
        { 3318, 3319 }, /* glViewportArrayvNV and glViewportArrayvOES */
        { 3319, 2905 }, /* glViewportArrayvOES and glViewportArrayv */
        { 3319, 3318 }, /* glViewportArrayvOES and glViewportArrayvNV */
        { 2906, 3320 }, /* glViewportIndexedf and glViewportIndexedfNV */
        { 2906, 3321 }, /* glViewportIndexedf and glViewportIndexedfOES */
        { 3320, 2906 }, /* glViewportIndexedfNV and glViewportIndexedf */
        { 3320, 3321 }, /* glViewportIndexedfNV and glViewportIndexedfOES */
        { 3321, 2906 }, /* glViewportIndexedfOES and glViewportIndexedf */
        { 3321, 3320 }, /* glViewportIndexedfOES and glViewportIndexedfNV */
        { 2907, 3322 }, /* glViewportIndexedfv and glViewportIndexedfvNV */
        { 2907, 3323 }, /* glViewportIndexedfv and glViewportIndexedfvOES */
        { 3322, 2907 }, /* glViewportIndexedfvNV and glViewportIndexedfv */
        { 3322, 3323 }, /* glViewportIndexedfvNV and glViewportIndexedfvOES */
        { 3323, 2907 }, /* glViewportIndexedfvOES and glViewportIndexedfv */
        { 3323, 3322 }, /* glViewportIndexedfvOES and glViewportIndexedfvNV */
        { 2912, 3324 }, /* glWaitSync and glWaitSyncAPPLE */
        { 3324, 2912 }, /* glWaitSyncAPPLE and glWaitSync */
        { 2924, 2925 }, /* glWindowPos2d and glWindowPos2dARB */
        { 2924, 2926 }, /* glWindowPos2d and glWindowPos2dMESA */
        { 2925, 2924 }, /* glWindowPos2dARB and glWindowPos2d */
        { 2925, 2926 }, /* glWindowPos2dARB and glWindowPos2dMESA */
        { 2926, 2924 }, /* glWindowPos2dMESA and glWindowPos2d */
        { 2926, 2925 }, /* glWindowPos2dMESA and glWindowPos2dARB */
        { 2927, 2928 }, /* glWindowPos2dv and glWindowPos2dvARB */
        { 2927, 2929 }, /* glWindowPos2dv and glWindowPos2dvMESA */
        { 2928, 2927 }, /* glWindowPos2dvARB and glWindowPos2dv */
        { 2928, 2929 }, /* glWindowPos2dvARB and glWindowPos2dvMESA */
        { 2929, 2927 }, /* glWindowPos2dvMESA and glWindowPos2dv */
        { 2929, 2928 }, /* glWindowPos2dvMESA and glWindowPos2dvARB */
        { 2930, 2931 }, /* glWindowPos2f and glWindowPos2fARB */
        { 2930, 2932 }, /* glWindowPos2f and glWindowPos2fMESA */
        { 2931, 2930 }, /* glWindowPos2fARB and glWindowPos2f */
        { 2931, 2932 }, /* glWindowPos2fARB and glWindowPos2fMESA */
        { 2932, 2930 }, /* glWindowPos2fMESA and glWindowPos2f */
        { 2932, 2931 }, /* glWindowPos2fMESA and glWindowPos2fARB */
        { 2933, 2934 }, /* glWindowPos2fv and glWindowPos2fvARB */
        { 2933, 2935 }, /* glWindowPos2fv and glWindowPos2fvMESA */
        { 2934, 2933 }, /* glWindowPos2fvARB and glWindowPos2fv */
        { 2934, 2935 }, /* glWindowPos2fvARB and glWindowPos2fvMESA */
        { 2935, 2933 }, /* glWindowPos2fvMESA and glWindowPos2fv */
        { 2935, 2934 }, /* glWindowPos2fvMESA and glWindowPos2fvARB */
        { 2936, 2937 }, /* glWindowPos2i and glWindowPos2iARB */
        { 2936, 2938 }, /* glWindowPos2i and glWindowPos2iMESA */
        { 2937, 2936 }, /* glWindowPos2iARB and glWindowPos2i */
        { 2937, 2938 }, /* glWindowPos2iARB and glWindowPos2iMESA */
        { 2938, 2936 }, /* glWindowPos2iMESA and glWindowPos2i */
        { 2938, 2937 }, /* glWindowPos2iMESA and glWindowPos2iARB */
        { 2939, 2940 }, /* glWindowPos2iv and glWindowPos2ivARB */
        { 2939, 2941 }, /* glWindowPos2iv and glWindowPos2ivMESA */
        { 2940, 2939 }, /* glWindowPos2ivARB and glWindowPos2iv */
        { 2940, 2941 }, /* glWindowPos2ivARB and glWindowPos2ivMESA */
        { 2941, 2939 }, /* glWindowPos2ivMESA and glWindowPos2iv */
        { 2941, 2940 }, /* glWindowPos2ivMESA and glWindowPos2ivARB */
        { 2942, 2943 }, /* glWindowPos2s and glWindowPos2sARB */
        { 2942, 2944 }, /* glWindowPos2s and glWindowPos2sMESA */
        { 2943, 2942 }, /* glWindowPos2sARB and glWindowPos2s */
        { 2943, 2944 }, /* glWindowPos2sARB and glWindowPos2sMESA */
        { 2944, 2942 }, /* glWindowPos2sMESA and glWindowPos2s */
        { 2944, 2943 }, /* glWindowPos2sMESA and glWindowPos2sARB */
        { 2945, 2946 }, /* glWindowPos2sv and glWindowPos2svARB */
        { 2945, 2947 }, /* glWindowPos2sv and glWindowPos2svMESA */
        { 2946, 2945 }, /* glWindowPos2svARB and glWindowPos2sv */
        { 2946, 2947 }, /* glWindowPos2svARB and glWindowPos2svMESA */
        { 2947, 2945 }, /* glWindowPos2svMESA and glWindowPos2sv */
        { 2947, 2946 }, /* glWindowPos2svMESA and glWindowPos2svARB */
        { 2948, 2949 }, /* glWindowPos3d and glWindowPos3dARB */
        { 2948, 2950 }, /* glWindowPos3d and glWindowPos3dMESA */
        { 2949, 2948 }, /* glWindowPos3dARB and glWindowPos3d */
        { 2949, 2950 }, /* glWindowPos3dARB and glWindowPos3dMESA */
        { 2950, 2948 }, /* glWindowPos3dMESA and glWindowPos3d */
        { 2950, 2949 }, /* glWindowPos3dMESA and glWindowPos3dARB */
        { 2951, 2952 }, /* glWindowPos3dv and glWindowPos3dvARB */
        { 2951, 2953 }, /* glWindowPos3dv and glWindowPos3dvMESA */
        { 2952, 2951 }, /* glWindowPos3dvARB and glWindowPos3dv */
        { 2952, 2953 }, /* glWindowPos3dvARB and glWindowPos3dvMESA */
        { 2953, 2951 }, /* glWindowPos3dvMESA and glWindowPos3dv */
        { 2953, 2952 }, /* glWindowPos3dvMESA and glWindowPos3dvARB */
        { 2954, 2955 }, /* glWindowPos3f and glWindowPos3fARB */
        { 2954, 2956 }, /* glWindowPos3f and glWindowPos3fMESA */
        { 2955, 2954 }, /* glWindowPos3fARB and glWindowPos3f */
        { 2955, 2956 }, /* glWindowPos3fARB and glWindowPos3fMESA */
        { 2956, 2954 }, /* glWindowPos3fMESA and glWindowPos3f */
        { 2956, 2955 }, /* glWindowPos3fMESA and glWindowPos3fARB */
        { 2957, 2958 }, /* glWindowPos3fv and glWindowPos3fvARB */
        { 2957, 2959 }, /* glWindowPos3fv and glWindowPos3fvMESA */
        { 2958, 2957 }, /* glWindowPos3fvARB and glWindowPos3fv */
        { 2958, 2959 }, /* glWindowPos3fvARB and glWindowPos3fvMESA */
        { 2959, 2957 }, /* glWindowPos3fvMESA and glWindowPos3fv */
        { 2959, 2958 }, /* glWindowPos3fvMESA and glWindowPos3fvARB */
        { 2960, 2961 }, /* glWindowPos3i and glWindowPos3iARB */
        { 2960, 2962 }, /* glWindowPos3i and glWindowPos3iMESA */
        { 2961, 2960 }, /* glWindowPos3iARB and glWindowPos3i */
        { 2961, 2962 }, /* glWindowPos3iARB and glWindowPos3iMESA */
        { 2962, 2960 }, /* glWindowPos3iMESA and glWindowPos3i */
        { 2962, 2961 }, /* glWindowPos3iMESA and glWindowPos3iARB */
        { 2963, 2964 }, /* glWindowPos3iv and glWindowPos3ivARB */
        { 2963, 2965 }, /* glWindowPos3iv and glWindowPos3ivMESA */
        { 2964, 2963 }, /* glWindowPos3ivARB and glWindowPos3iv */
        { 2964, 2965 }, /* glWindowPos3ivARB and glWindowPos3ivMESA */
        { 2965, 2963 }, /* glWindowPos3ivMESA and glWindowPos3iv */
        { 2965, 2964 }, /* glWindowPos3ivMESA and glWindowPos3ivARB */
        { 2966, 2967 }, /* glWindowPos3s and glWindowPos3sARB */
        { 2966, 2968 }, /* glWindowPos3s and glWindowPos3sMESA */
        { 2967, 2966 }, /* glWindowPos3sARB and glWindowPos3s */
        { 2967, 2968 }, /* glWindowPos3sARB and glWindowPos3sMESA */
        { 2968, 2966 }, /* glWindowPos3sMESA and glWindowPos3s */
        { 2968, 2967 }, /* glWindowPos3sMESA and glWindowPos3sARB */
        { 2969, 2970 }, /* glWindowPos3sv and glWindowPos3svARB */
        { 2969, 2971 }, /* glWindowPos3sv and glWindowPos3svMESA */
        { 2970, 2969 }, /* glWindowPos3svARB and glWindowPos3sv */
        { 2970, 2971 }, /* glWindowPos3svARB and glWindowPos3svMESA */
        { 2971, 2969 }, /* glWindowPos3svMESA and glWindowPos3sv */
        { 2971, 2970 }, /* glWindowPos3svMESA and glWindowPos3svARB */
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

#if defined(GL_ES_VERSION_3_0) || defined(GL_VERSION_3_0)
#define GLAD_GL_IS_SOME_NEW_VERSION 1
#else
#define GLAD_GL_IS_SOME_NEW_VERSION 0
#endif

static int glad_gl_get_extensions(GladGLContext *context, int version, uint64_t **out_exts, uint32_t *out_num_exts) {
    uint32_t num_exts = 0;
    uint64_t *exts = NULL;
    const char *exts_str = NULL;
    const char *cur = NULL;
    const char *next = NULL;
    uint32_t len = 0, j = 0;

#if GLAD_GL_IS_SOME_NEW_VERSION
    if(GLAD_VERSION_MAJOR(version) < 3) {
#else
    GLAD_UNUSED(version);
#endif
        if (context->GetString == NULL) {
            return 0;
        }
        exts_str = (const char *)context->GetString(GL_EXTENSIONS);

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
#if GLAD_GL_IS_SOME_NEW_VERSION
    } else {
        unsigned int index = 0;
        if (context->GetStringi == NULL || context->GetIntegerv == NULL) {
            return 0;
        }
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
    }
#endif

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

static int glad_gl_find_extensions_gl(GladGLContext *context, int version) {
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
          57, /* GL_ANGLE_memory_object_flags */
          58, /* GL_ANGLE_memory_object_fuchsia */
          72, /* GL_ANGLE_semaphore_fuchsia */
          75, /* GL_ANGLE_texture_compression_dxt */
          78, /* GL_ANGLE_texture_external_update */
          85, /* GL_APPLE_aux_depth_stencil */
          86, /* GL_APPLE_client_storage */
          90, /* GL_APPLE_element_array */
          91, /* GL_APPLE_fence */
          92, /* GL_APPLE_float_pixels */
          93, /* GL_APPLE_flush_buffer_range */
          95, /* GL_APPLE_object_purgeable */
          96, /* GL_APPLE_rgb_422 */
          97, /* GL_APPLE_row_bytes */
          98, /* GL_APPLE_specular_vector */
         103, /* GL_APPLE_texture_range */
         104, /* GL_APPLE_transform_hint */
         105, /* GL_APPLE_vertex_array_object */
         106, /* GL_APPLE_vertex_array_range */
         107, /* GL_APPLE_vertex_program_evaluators */
         108, /* GL_APPLE_ycbcr_422 */
         109, /* GL_ARB_ES2_compatibility */
         110, /* GL_ARB_ES3_1_compatibility */
         111, /* GL_ARB_ES3_2_compatibility */
         112, /* GL_ARB_ES3_compatibility */
         113, /* GL_ARB_arrays_of_arrays */
         114, /* GL_ARB_base_instance */
         115, /* GL_ARB_bindless_texture */
         116, /* GL_ARB_blend_func_extended */
         117, /* GL_ARB_buffer_storage */
         118, /* GL_ARB_cl_event */
         119, /* GL_ARB_clear_buffer_object */
         120, /* GL_ARB_clear_texture */
         121, /* GL_ARB_clip_control */
         122, /* GL_ARB_color_buffer_float */
         123, /* GL_ARB_compatibility */
         124, /* GL_ARB_compressed_texture_pixel_storage */
         125, /* GL_ARB_compute_shader */
         126, /* GL_ARB_compute_variable_group_size */
         127, /* GL_ARB_conditional_render_inverted */
         128, /* GL_ARB_conservative_depth */
         129, /* GL_ARB_copy_buffer */
         130, /* GL_ARB_copy_image */
         131, /* GL_ARB_cull_distance */
         132, /* GL_ARB_debug_output */
         133, /* GL_ARB_depth_buffer_float */
         134, /* GL_ARB_depth_clamp */
         135, /* GL_ARB_depth_texture */
         136, /* GL_ARB_derivative_control */
         137, /* GL_ARB_direct_state_access */
         138, /* GL_ARB_draw_buffers */
         139, /* GL_ARB_draw_buffers_blend */
         140, /* GL_ARB_draw_elements_base_vertex */
         141, /* GL_ARB_draw_indirect */
         142, /* GL_ARB_draw_instanced */
         143, /* GL_ARB_enhanced_layouts */
         144, /* GL_ARB_explicit_attrib_location */
         145, /* GL_ARB_explicit_uniform_location */
         146, /* GL_ARB_fragment_coord_conventions */
         147, /* GL_ARB_fragment_layer_viewport */
         148, /* GL_ARB_fragment_program */
         149, /* GL_ARB_fragment_program_shadow */
         150, /* GL_ARB_fragment_shader */
         151, /* GL_ARB_fragment_shader_interlock */
         152, /* GL_ARB_framebuffer_no_attachments */
         153, /* GL_ARB_framebuffer_object */
         154, /* GL_ARB_framebuffer_sRGB */
         155, /* GL_ARB_geometry_shader4 */
         156, /* GL_ARB_get_program_binary */
         157, /* GL_ARB_get_texture_sub_image */
         158, /* GL_ARB_gl_spirv */
         159, /* GL_ARB_gpu_shader5 */
         160, /* GL_ARB_gpu_shader_fp64 */
         161, /* GL_ARB_gpu_shader_int64 */
         162, /* GL_ARB_half_float_pixel */
         163, /* GL_ARB_half_float_vertex */
         164, /* GL_ARB_imaging */
         165, /* GL_ARB_indirect_parameters */
         166, /* GL_ARB_instanced_arrays */
         167, /* GL_ARB_internalformat_query */
         168, /* GL_ARB_internalformat_query2 */
         169, /* GL_ARB_invalidate_subdata */
         170, /* GL_ARB_map_buffer_alignment */
         171, /* GL_ARB_map_buffer_range */
         172, /* GL_ARB_matrix_palette */
         173, /* GL_ARB_multi_bind */
         174, /* GL_ARB_multi_draw_indirect */
         175, /* GL_ARB_multisample */
         176, /* GL_ARB_multitexture */
         177, /* GL_ARB_occlusion_query */
         178, /* GL_ARB_occlusion_query2 */
         179, /* GL_ARB_parallel_shader_compile */
         180, /* GL_ARB_pipeline_statistics_query */
         181, /* GL_ARB_pixel_buffer_object */
         182, /* GL_ARB_point_parameters */
         183, /* GL_ARB_point_sprite */
         184, /* GL_ARB_polygon_offset_clamp */
         185, /* GL_ARB_post_depth_coverage */
         186, /* GL_ARB_program_interface_query */
         187, /* GL_ARB_provoking_vertex */
         188, /* GL_ARB_query_buffer_object */
         189, /* GL_ARB_robust_buffer_access_behavior */
         190, /* GL_ARB_robustness */
         191, /* GL_ARB_robustness_isolation */
         192, /* GL_ARB_sample_locations */
         193, /* GL_ARB_sample_shading */
         194, /* GL_ARB_sampler_objects */
         195, /* GL_ARB_seamless_cube_map */
         196, /* GL_ARB_seamless_cubemap_per_texture */
         197, /* GL_ARB_separate_shader_objects */
         198, /* GL_ARB_shader_atomic_counter_ops */
         199, /* GL_ARB_shader_atomic_counters */
         200, /* GL_ARB_shader_ballot */
         201, /* GL_ARB_shader_bit_encoding */
         202, /* GL_ARB_shader_clock */
         203, /* GL_ARB_shader_draw_parameters */
         204, /* GL_ARB_shader_group_vote */
         205, /* GL_ARB_shader_image_load_store */
         206, /* GL_ARB_shader_image_size */
         207, /* GL_ARB_shader_objects */
         208, /* GL_ARB_shader_precision */
         209, /* GL_ARB_shader_stencil_export */
         210, /* GL_ARB_shader_storage_buffer_object */
         211, /* GL_ARB_shader_subroutine */
         212, /* GL_ARB_shader_texture_image_samples */
         213, /* GL_ARB_shader_texture_lod */
         214, /* GL_ARB_shader_viewport_layer_array */
         215, /* GL_ARB_shading_language_100 */
         216, /* GL_ARB_shading_language_420pack */
         217, /* GL_ARB_shading_language_include */
         218, /* GL_ARB_shading_language_packing */
         219, /* GL_ARB_shadow */
         220, /* GL_ARB_shadow_ambient */
         221, /* GL_ARB_sparse_buffer */
         222, /* GL_ARB_sparse_texture */
         223, /* GL_ARB_sparse_texture2 */
         224, /* GL_ARB_sparse_texture_clamp */
         225, /* GL_ARB_spirv_extensions */
         226, /* GL_ARB_stencil_texturing */
         227, /* GL_ARB_sync */
         228, /* GL_ARB_tessellation_shader */
         229, /* GL_ARB_texture_barrier */
         230, /* GL_ARB_texture_border_clamp */
         231, /* GL_ARB_texture_buffer_object */
         232, /* GL_ARB_texture_buffer_object_rgb32 */
         233, /* GL_ARB_texture_buffer_range */
         234, /* GL_ARB_texture_compression */
         235, /* GL_ARB_texture_compression_bptc */
         236, /* GL_ARB_texture_compression_rgtc */
         237, /* GL_ARB_texture_cube_map */
         238, /* GL_ARB_texture_cube_map_array */
         239, /* GL_ARB_texture_env_add */
         240, /* GL_ARB_texture_env_combine */
         241, /* GL_ARB_texture_env_crossbar */
         242, /* GL_ARB_texture_env_dot3 */
         243, /* GL_ARB_texture_filter_anisotropic */
         244, /* GL_ARB_texture_filter_minmax */
         245, /* GL_ARB_texture_float */
         246, /* GL_ARB_texture_gather */
         247, /* GL_ARB_texture_mirror_clamp_to_edge */
         248, /* GL_ARB_texture_mirrored_repeat */
         249, /* GL_ARB_texture_multisample */
         250, /* GL_ARB_texture_non_power_of_two */
         251, /* GL_ARB_texture_query_levels */
         252, /* GL_ARB_texture_query_lod */
         253, /* GL_ARB_texture_rectangle */
         254, /* GL_ARB_texture_rg */
         255, /* GL_ARB_texture_rgb10_a2ui */
         256, /* GL_ARB_texture_stencil8 */
         257, /* GL_ARB_texture_storage */
         258, /* GL_ARB_texture_storage_multisample */
         259, /* GL_ARB_texture_swizzle */
         260, /* GL_ARB_texture_view */
         261, /* GL_ARB_timer_query */
         262, /* GL_ARB_transform_feedback2 */
         263, /* GL_ARB_transform_feedback3 */
         264, /* GL_ARB_transform_feedback_instanced */
         265, /* GL_ARB_transform_feedback_overflow_query */
         266, /* GL_ARB_transpose_matrix */
         267, /* GL_ARB_uniform_buffer_object */
         268, /* GL_ARB_vertex_array_bgra */
         269, /* GL_ARB_vertex_array_object */
         270, /* GL_ARB_vertex_attrib_64bit */
         271, /* GL_ARB_vertex_attrib_binding */
         272, /* GL_ARB_vertex_blend */
         273, /* GL_ARB_vertex_buffer_object */
         274, /* GL_ARB_vertex_program */
         275, /* GL_ARB_vertex_shader */
         276, /* GL_ARB_vertex_type_10f_11f_11f_rev */
         277, /* GL_ARB_vertex_type_2_10_10_10_rev */
         278, /* GL_ARB_viewport_array */
         279, /* GL_ARB_window_pos */
         287, /* GL_ATI_draw_buffers */
         288, /* GL_ATI_element_array */
         289, /* GL_ATI_envmap_bumpmap */
         290, /* GL_ATI_fragment_shader */
         291, /* GL_ATI_map_object_buffer */
         292, /* GL_ATI_meminfo */
         293, /* GL_ATI_pixel_format_float */
         294, /* GL_ATI_pn_triangles */
         295, /* GL_ATI_separate_stencil */
         296, /* GL_ATI_text_fragment_shader */
         297, /* GL_ATI_texture_env_combine3 */
         298, /* GL_ATI_texture_float */
         299, /* GL_ATI_texture_mirror_once */
         300, /* GL_ATI_vertex_array_object */
         301, /* GL_ATI_vertex_attrib_array_object */
         302, /* GL_ATI_vertex_streams */
         310, /* GL_EXT_422_pixels */
         312, /* GL_EXT_EGL_image_storage */
         314, /* GL_EXT_EGL_sync */
         316, /* GL_EXT_abgr */
         318, /* GL_EXT_bgra */
         319, /* GL_EXT_bindable_uniform */
         320, /* GL_EXT_blend_color */
         321, /* GL_EXT_blend_equation_separate */
         323, /* GL_EXT_blend_func_separate */
         324, /* GL_EXT_blend_logic_op */
         325, /* GL_EXT_blend_minmax */
         326, /* GL_EXT_blend_subtract */
         327, /* GL_EXT_buffer_reference */
         328, /* GL_EXT_buffer_reference2 */
         333, /* GL_EXT_clip_volume_hint */
         334, /* GL_EXT_cmyka */
         337, /* GL_EXT_color_subtable */
         338, /* GL_EXT_compiled_vertex_array */
         340, /* GL_EXT_control_flow_attributes */
         341, /* GL_EXT_convolution */
         342, /* GL_EXT_coordinate_frame */
         344, /* GL_EXT_copy_texture */
         345, /* GL_EXT_cull_vertex */
         346, /* GL_EXT_debug_label */
         347, /* GL_EXT_debug_marker */
         348, /* GL_EXT_debug_printf */
         349, /* GL_EXT_demote_to_helper_invocation */
         350, /* GL_EXT_depth_bounds_test */
         352, /* GL_EXT_device_group */
         353, /* GL_EXT_direct_state_access */
         357, /* GL_EXT_draw_buffers2 */
         360, /* GL_EXT_draw_instanced */
         361, /* GL_EXT_draw_range_elements */
         363, /* GL_EXT_external_buffer */
         365, /* GL_EXT_fog_coord */
         366, /* GL_EXT_fragment_invocation_density */
         367, /* GL_EXT_fragment_shader_barycentric */
         369, /* GL_EXT_framebuffer_blit */
         370, /* GL_EXT_framebuffer_blit_layers */
         371, /* GL_EXT_framebuffer_multisample */
         372, /* GL_EXT_framebuffer_multisample_blit_scaled */
         373, /* GL_EXT_framebuffer_object */
         374, /* GL_EXT_framebuffer_sRGB */
         377, /* GL_EXT_geometry_shader4 */
         378, /* GL_EXT_gpu_program_parameters */
         379, /* GL_EXT_gpu_shader4 */
         381, /* GL_EXT_histogram */
         382, /* GL_EXT_index_array_formats */
         383, /* GL_EXT_index_func */
         384, /* GL_EXT_index_material */
         385, /* GL_EXT_index_texture */
         387, /* GL_EXT_light_texture */
         389, /* GL_EXT_memory_object */
         390, /* GL_EXT_memory_object_fd */
         391, /* GL_EXT_memory_object_win32 */
         392, /* GL_EXT_misc_attribute */
         393, /* GL_EXT_multi_draw_arrays */
         395, /* GL_EXT_multisample */
         400, /* GL_EXT_multiview_tessellation_geometry_shader */
         401, /* GL_EXT_multiview_texture_multisample */
         402, /* GL_EXT_multiview_timer_query */
         403, /* GL_EXT_nonuniform_qualifier */
         405, /* GL_EXT_packed_depth_stencil */
         406, /* GL_EXT_packed_float */
         407, /* GL_EXT_packed_pixels */
         408, /* GL_EXT_paletted_texture */
         409, /* GL_EXT_pixel_buffer_object */
         410, /* GL_EXT_pixel_transform */
         411, /* GL_EXT_pixel_transform_color_table */
         412, /* GL_EXT_point_parameters */
         413, /* GL_EXT_polygon_offset */
         414, /* GL_EXT_polygon_offset_clamp */
         415, /* GL_EXT_post_depth_coverage */
         418, /* GL_EXT_provoking_vertex */
         420, /* GL_EXT_raster_multisample */
         421, /* GL_EXT_ray_cull_mask */
         422, /* GL_EXT_ray_flags_primitive_culling */
         423, /* GL_EXT_ray_query */
         424, /* GL_EXT_ray_tracing */
         427, /* GL_EXT_rescale_normal */
         431, /* GL_EXT_samplerless_texture_functions */
         432, /* GL_EXT_scalar_block_layout */
         433, /* GL_EXT_secondary_color */
         434, /* GL_EXT_semaphore */
         435, /* GL_EXT_semaphore_fd */
         436, /* GL_EXT_semaphore_win32 */
         438, /* GL_EXT_separate_shader_objects */
         439, /* GL_EXT_separate_specular_color */
         440, /* GL_EXT_shader_16bit_storage */
         441, /* GL_EXT_shader_atomic_float */
         442, /* GL_EXT_shader_explicit_arithmetic_types */
         443, /* GL_EXT_shader_framebuffer_fetch */
         444, /* GL_EXT_shader_framebuffer_fetch_non_coherent */
         446, /* GL_EXT_shader_image_int64 */
         447, /* GL_EXT_shader_image_load_formatted */
         448, /* GL_EXT_shader_image_load_store */
         450, /* GL_EXT_shader_integer_mix */
         455, /* GL_EXT_shader_realtime_clock */
         456, /* GL_EXT_shader_samples_identical */
         457, /* GL_EXT_shader_subgroup_extended_types */
         459, /* GL_EXT_shadow_funcs */
         461, /* GL_EXT_shared_memory_block */
         462, /* GL_EXT_shared_texture_palette */
         464, /* GL_EXT_sparse_texture2 */
         465, /* GL_EXT_stencil_clear_tag */
         466, /* GL_EXT_stencil_two_side */
         467, /* GL_EXT_stencil_wrap */
         468, /* GL_EXT_subgroup_uniform_control_flow */
         469, /* GL_EXT_subgroupuniform_qualifier */
         470, /* GL_EXT_subtexture */
         473, /* GL_EXT_texture */
         474, /* GL_EXT_texture3D */
         475, /* GL_EXT_texture_array */
         478, /* GL_EXT_texture_buffer_object */
         482, /* GL_EXT_texture_compression_latc */
         483, /* GL_EXT_texture_compression_rgtc */
         484, /* GL_EXT_texture_compression_s3tc */
         486, /* GL_EXT_texture_cube_map */
         488, /* GL_EXT_texture_env_add */
         489, /* GL_EXT_texture_env_combine */
         490, /* GL_EXT_texture_env_dot3 */
         491, /* GL_EXT_texture_filter_anisotropic */
         492, /* GL_EXT_texture_filter_minmax */
         495, /* GL_EXT_texture_integer */
         496, /* GL_EXT_texture_lod_bias */
         497, /* GL_EXT_texture_mirror_clamp */
         500, /* GL_EXT_texture_object */
         501, /* GL_EXT_texture_perturb_normal */
         504, /* GL_EXT_texture_sRGB */
         505, /* GL_EXT_texture_sRGB_R8 */
         506, /* GL_EXT_texture_sRGB_RG8 */
         507, /* GL_EXT_texture_sRGB_decode */
         508, /* GL_EXT_texture_shadow_lod */
         509, /* GL_EXT_texture_shared_exponent */
         510, /* GL_EXT_texture_snorm */
         511, /* GL_EXT_texture_storage */
         513, /* GL_EXT_texture_swizzle */
         516, /* GL_EXT_timer_query */
         517, /* GL_EXT_transform_feedback */
         519, /* GL_EXT_vertex_array */
         520, /* GL_EXT_vertex_array_bgra */
         521, /* GL_EXT_vertex_attrib_64bit */
         522, /* GL_EXT_vertex_shader */
         523, /* GL_EXT_vertex_weighting */
         524, /* GL_EXT_vulkan_glsl_relaxed */
         525, /* GL_EXT_win32_keyed_mutex */
         526, /* GL_EXT_window_rectangles */
         527, /* GL_EXT_x11_sync_object */
         529, /* GL_GREMEDY_frame_terminator */
         530, /* GL_GREMEDY_string_marker */
         531, /* GL_HP_convolution_border_modes */
         532, /* GL_HP_image_transform */
         533, /* GL_HP_occlusion_test */
         534, /* GL_HP_texture_lighting */
         535, /* GL_HUAWEI_subpass_shading */
         536, /* GL_IBM_cull_vertex */
         537, /* GL_IBM_multimode_draw_arrays */
         538, /* GL_IBM_rasterpos_clip */
         539, /* GL_IBM_static_data */
         540, /* GL_IBM_texture_mirrored_repeat */
         541, /* GL_IBM_vertex_array_lists */
         551, /* GL_INGR_blend_func_separate */
         552, /* GL_INGR_color_clamp */
         553, /* GL_INGR_interlace_read */
         554, /* GL_INTEL_blackhole_render */
         555, /* GL_INTEL_conservative_rasterization */
         556, /* GL_INTEL_fragment_shader_ordering */
         557, /* GL_INTEL_framebuffer_CMAA */
         558, /* GL_INTEL_map_texture */
         559, /* GL_INTEL_parallel_arrays */
         560, /* GL_INTEL_performance_query */
         561, /* GL_KHR_blend_equation_advanced */
         562, /* GL_KHR_blend_equation_advanced_coherent */
         563, /* GL_KHR_context_flush_control */
         564, /* GL_KHR_debug */
         565, /* GL_KHR_memory_scope_semantics */
         566, /* GL_KHR_no_error */
         567, /* GL_KHR_parallel_shader_compile */
         568, /* GL_KHR_robust_buffer_access_behavior */
         569, /* GL_KHR_robustness */
         570, /* GL_KHR_shader_subgroup */
         571, /* GL_KHR_texture_compression_astc_hdr */
         572, /* GL_KHR_texture_compression_astc_ldr */
         573, /* GL_KHR_texture_compression_astc_sliced_3d */
         574, /* GL_KHR_vulkan_glsl */
         575, /* GL_MESAX_texture_stack */
         577, /* GL_MESA_framebuffer_flip_x */
         578, /* GL_MESA_framebuffer_flip_y */
         579, /* GL_MESA_framebuffer_swap_xy */
         580, /* GL_MESA_pack_invert */
         581, /* GL_MESA_program_binary_formats */
         582, /* GL_MESA_resize_buffers */
         584, /* GL_MESA_shader_integer_functions */
         585, /* GL_MESA_tile_raster_order */
         586, /* GL_MESA_window_pos */
         587, /* GL_MESA_ycbcr_texture */
         588, /* GL_NVX_blend_equation_advanced_multi_draw_buffers */
         589, /* GL_NVX_conditional_render */
         590, /* GL_NVX_gpu_memory_info */
         591, /* GL_NVX_gpu_multicast2 */
         592, /* GL_NVX_linked_gpu_multicast */
         593, /* GL_NVX_multiview_per_view_attributes */
         594, /* GL_NVX_progress_fence */
         595, /* GL_NV_alpha_to_coverage_dither_control */
         596, /* GL_NV_bindless_multi_draw_indirect */
         597, /* GL_NV_bindless_multi_draw_indirect_count */
         598, /* GL_NV_bindless_texture */
         599, /* GL_NV_blend_equation_advanced */
         600, /* GL_NV_blend_equation_advanced_coherent */
         601, /* GL_NV_blend_minmax_factor */
         602, /* GL_NV_blend_square */
         603, /* GL_NV_clip_space_w_scaling */
         604, /* GL_NV_command_list */
         605, /* GL_NV_compute_program5 */
         606, /* GL_NV_compute_shader_derivatives */
         607, /* GL_NV_conditional_render */
         608, /* GL_NV_conservative_raster */
         609, /* GL_NV_conservative_raster_dilate */
         610, /* GL_NV_conservative_raster_pre_snap */
         611, /* GL_NV_conservative_raster_pre_snap_triangles */
         612, /* GL_NV_conservative_raster_underestimation */
         613, /* GL_NV_cooperative_matrix */
         615, /* GL_NV_copy_depth_to_color */
         616, /* GL_NV_copy_image */
         618, /* GL_NV_deep_texture3D */
         619, /* GL_NV_depth_buffer_float */
         620, /* GL_NV_depth_clamp */
         624, /* GL_NV_draw_texture */
         625, /* GL_NV_draw_vulkan_image */
         626, /* GL_NV_evaluators */
         628, /* GL_NV_explicit_multisample */
         630, /* GL_NV_fence */
         631, /* GL_NV_fill_rectangle */
         632, /* GL_NV_float_buffer */
         633, /* GL_NV_fog_distance */
         634, /* GL_NV_fragment_coverage_to_color */
         635, /* GL_NV_fragment_program */
         636, /* GL_NV_fragment_program2 */
         637, /* GL_NV_fragment_program4 */
         638, /* GL_NV_fragment_program_option */
         639, /* GL_NV_fragment_shader_barycentric */
         640, /* GL_NV_fragment_shader_interlock */
         642, /* GL_NV_framebuffer_mixed_samples */
         644, /* GL_NV_framebuffer_multisample_coverage */
         646, /* GL_NV_geometry_program4 */
         647, /* GL_NV_geometry_shader4 */
         648, /* GL_NV_geometry_shader_passthrough */
         649, /* GL_NV_gpu_multicast */
         650, /* GL_NV_gpu_program4 */
         651, /* GL_NV_gpu_program5 */
         652, /* GL_NV_gpu_program5_mem_extended */
         653, /* GL_NV_gpu_shader5 */
         654, /* GL_NV_half_float */
         657, /* GL_NV_internalformat_sample_query */
         658, /* GL_NV_light_max_exponent */
         659, /* GL_NV_memory_attachment */
         660, /* GL_NV_memory_object_sparse */
         661, /* GL_NV_mesh_shader */
         662, /* GL_NV_multisample_coverage */
         663, /* GL_NV_multisample_filter_hint */
         665, /* GL_NV_occlusion_query */
         667, /* GL_NV_packed_depth_stencil */
         668, /* GL_NV_parameter_buffer_object */
         669, /* GL_NV_parameter_buffer_object2 */
         670, /* GL_NV_path_rendering */
         671, /* GL_NV_path_rendering_shared_edge */
         673, /* GL_NV_pixel_data_range */
         674, /* GL_NV_point_sprite */
         676, /* GL_NV_present_video */
         677, /* GL_NV_primitive_restart */
         678, /* GL_NV_primitive_shading_rate */
         679, /* GL_NV_query_resource */
         680, /* GL_NV_query_resource_tag */
         681, /* GL_NV_ray_tracing */
         682, /* GL_NV_ray_tracing_motion_blur */
         688, /* GL_NV_register_combiners */
         689, /* GL_NV_register_combiners2 */
         690, /* GL_NV_representative_fragment_test */
         691, /* GL_NV_robustness_video_memory_purge */
         693, /* GL_NV_sample_locations */
         694, /* GL_NV_sample_mask_override_coverage */
         695, /* GL_NV_scissor_exclusive */
         696, /* GL_NV_shader_atomic_counters */
         697, /* GL_NV_shader_atomic_float */
         698, /* GL_NV_shader_atomic_float64 */
         699, /* GL_NV_shader_atomic_fp16_vector */
         700, /* GL_NV_shader_atomic_int64 */
         701, /* GL_NV_shader_buffer_load */
         702, /* GL_NV_shader_buffer_store */
         704, /* GL_NV_shader_sm_builtins */
         705, /* GL_NV_shader_storage_buffer_object */
         706, /* GL_NV_shader_subgroup_partitioned */
         707, /* GL_NV_shader_texture_footprint */
         708, /* GL_NV_shader_thread_group */
         709, /* GL_NV_shader_thread_shuffle */
         710, /* GL_NV_shading_rate_image */
         713, /* GL_NV_stereo_view_rendering */
         714, /* GL_NV_tessellation_program5 */
         715, /* GL_NV_texgen_emboss */
         716, /* GL_NV_texgen_reflection */
         717, /* GL_NV_texture_barrier */
         720, /* GL_NV_texture_compression_vtc */
         721, /* GL_NV_texture_env_combine4 */
         722, /* GL_NV_texture_expand_normal */
         723, /* GL_NV_texture_multisample */
         725, /* GL_NV_texture_rectangle */
         726, /* GL_NV_texture_rectangle_compressed */
         727, /* GL_NV_texture_shader */
         728, /* GL_NV_texture_shader2 */
         729, /* GL_NV_texture_shader3 */
         730, /* GL_NV_timeline_semaphore */
         731, /* GL_NV_transform_feedback */
         732, /* GL_NV_transform_feedback2 */
         733, /* GL_NV_uniform_buffer_std430_layout */
         734, /* GL_NV_uniform_buffer_unified_memory */
         735, /* GL_NV_vdpau_interop */
         736, /* GL_NV_vdpau_interop2 */
         737, /* GL_NV_vertex_array_range */
         738, /* GL_NV_vertex_array_range2 */
         739, /* GL_NV_vertex_attrib_integer_64bit */
         740, /* GL_NV_vertex_buffer_unified_memory */
         741, /* GL_NV_vertex_program */
         742, /* GL_NV_vertex_program1_1 */
         743, /* GL_NV_vertex_program2 */
         744, /* GL_NV_vertex_program2_option */
         745, /* GL_NV_vertex_program3 */
         746, /* GL_NV_vertex_program4 */
         747, /* GL_NV_video_capture */
         749, /* GL_NV_viewport_array2 */
         750, /* GL_NV_viewport_swizzle */
         754, /* GL_OES_byte_coordinates */
         757, /* GL_OES_compressed_paletted_texture */
         766, /* GL_OES_fixed_point */
         775, /* GL_OES_query_matrix */
         776, /* GL_OES_read_format */
         784, /* GL_OES_single_precision */
         808, /* GL_OML_interlace */
         809, /* GL_OML_resample */
         810, /* GL_OML_subsample */
         811, /* GL_OVR_multiview */
         812, /* GL_OVR_multiview2 */
         814, /* GL_PGI_misc_hints */
         815, /* GL_PGI_vertex_hints */
         837, /* GL_REND_screen_coordinates */
         838, /* GL_S3_s3tc */
         839, /* GL_SGIS_detail_texture */
         840, /* GL_SGIS_fog_function */
         841, /* GL_SGIS_generate_mipmap */
         842, /* GL_SGIS_multisample */
         843, /* GL_SGIS_pixel_texture */
         844, /* GL_SGIS_point_line_texgen */
         845, /* GL_SGIS_point_parameters */
         846, /* GL_SGIS_sharpen_texture */
         847, /* GL_SGIS_texture4D */
         848, /* GL_SGIS_texture_border_clamp */
         849, /* GL_SGIS_texture_color_mask */
         850, /* GL_SGIS_texture_edge_clamp */
         851, /* GL_SGIS_texture_filter4 */
         852, /* GL_SGIS_texture_lod */
         853, /* GL_SGIS_texture_select */
         854, /* GL_SGIX_async */
         855, /* GL_SGIX_async_histogram */
         856, /* GL_SGIX_async_pixel */
         857, /* GL_SGIX_blend_alpha_minmax */
         858, /* GL_SGIX_calligraphic_fragment */
         859, /* GL_SGIX_clipmap */
         860, /* GL_SGIX_convolution_accuracy */
         861, /* GL_SGIX_depth_pass_instrument */
         862, /* GL_SGIX_depth_texture */
         863, /* GL_SGIX_flush_raster */
         864, /* GL_SGIX_fog_offset */
         865, /* GL_SGIX_fragment_lighting */
         866, /* GL_SGIX_framezoom */
         867, /* GL_SGIX_igloo_interface */
         868, /* GL_SGIX_instruments */
         869, /* GL_SGIX_interlace */
         870, /* GL_SGIX_ir_instrument1 */
         871, /* GL_SGIX_list_priority */
         872, /* GL_SGIX_pixel_texture */
         873, /* GL_SGIX_pixel_tiles */
         874, /* GL_SGIX_polynomial_ffd */
         875, /* GL_SGIX_reference_plane */
         876, /* GL_SGIX_resample */
         877, /* GL_SGIX_scalebias_hint */
         878, /* GL_SGIX_shadow */
         879, /* GL_SGIX_shadow_ambient */
         880, /* GL_SGIX_sprite */
         881, /* GL_SGIX_subsample */
         882, /* GL_SGIX_tag_sample_buffer */
         883, /* GL_SGIX_texture_add_env */
         884, /* GL_SGIX_texture_coordinate_clamp */
         885, /* GL_SGIX_texture_lod_bias */
         886, /* GL_SGIX_texture_multi_buffer */
         887, /* GL_SGIX_texture_scale_bias */
         888, /* GL_SGIX_vertex_preclip */
         889, /* GL_SGIX_ycrcb */
         890, /* GL_SGIX_ycrcb_subsample */
         891, /* GL_SGIX_ycrcba */
         892, /* GL_SGI_color_matrix */
         893, /* GL_SGI_color_table */
         894, /* GL_SGI_texture_color_table */
         895, /* GL_SUNX_constant_data */
         896, /* GL_SUN_convolution_border_modes */
         897, /* GL_SUN_global_alpha */
         898, /* GL_SUN_mesh_array */
         899, /* GL_SUN_slice_accum */
         900, /* GL_SUN_triangle_list */
         901, /* GL_SUN_vertex */
         903, /* GL_WIN_phong_shading */
         904, /* GL_WIN_specular_fog */
    };
    uint64_t *exts = NULL;
    uint32_t num_exts = 0;
    uint32_t i;
    if (!glad_gl_get_extensions(context, version, &exts, &num_exts)) return 0;

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
          57, /* GL_ANGLE_memory_object_flags */
          58, /* GL_ANGLE_memory_object_fuchsia */
          59, /* GL_ANGLE_memory_size */
          60, /* GL_ANGLE_multi_draw */
          61, /* GL_ANGLE_pack_reverse_row_order */
          62, /* GL_ANGLE_polygon_mode */
          63, /* GL_ANGLE_program_binary */
          64, /* GL_ANGLE_program_cache_control */
          65, /* GL_ANGLE_provoking_vertex */
          66, /* GL_ANGLE_renderability_validation */
          67, /* GL_ANGLE_request_extension */
          68, /* GL_ANGLE_rgbx_internal_format */
          69, /* GL_ANGLE_robust_client_memory */
          70, /* GL_ANGLE_robust_fragment_shader_output */
          71, /* GL_ANGLE_robust_resource_initialization */
          72, /* GL_ANGLE_semaphore_fuchsia */
          73, /* GL_ANGLE_shader_pixel_local_storage */
          74, /* GL_ANGLE_stencil_texturing */
          75, /* GL_ANGLE_texture_compression_dxt */
          76, /* GL_ANGLE_texture_compression_dxt3 */
          77, /* GL_ANGLE_texture_compression_dxt5 */
          78, /* GL_ANGLE_texture_external_update */
          79, /* GL_ANGLE_texture_multisample */
          80, /* GL_ANGLE_texture_usage */
          81, /* GL_ANGLE_timer_query */
          82, /* GL_ANGLE_translated_shader_source */
          83, /* GL_ANGLE_vulkan_image */
          84, /* GL_ANGLE_yuv_internal_format */
          87, /* GL_APPLE_clip_distance */
          88, /* GL_APPLE_color_buffer_packed_float */
          89, /* GL_APPLE_copy_texture_levels */
          94, /* GL_APPLE_framebuffer_multisample */
          96, /* GL_APPLE_rgb_422 */
          99, /* GL_APPLE_sync */
         100, /* GL_APPLE_texture_format_BGRA8888 */
         101, /* GL_APPLE_texture_max_level */
         102, /* GL_APPLE_texture_packed_float */
         280, /* GL_ARM_mali_program_binary */
         281, /* GL_ARM_mali_shader_binary */
         282, /* GL_ARM_rgba8 */
         283, /* GL_ARM_shader_core_properties */
         284, /* GL_ARM_shader_framebuffer_fetch */
         285, /* GL_ARM_shader_framebuffer_fetch_depth_stencil */
         286, /* GL_ARM_texture_unnormalized_coordinates */
         303, /* GL_CHROMIUM_bind_uniform_location */
         304, /* GL_CHROMIUM_copy_compressed_texture */
         305, /* GL_CHROMIUM_copy_texture */
         306, /* GL_CHROMIUM_framebuffer_mixed_samples */
         307, /* GL_CHROMIUM_lose_context */
         308, /* GL_DMP_program_binary */
         309, /* GL_DMP_shader_binary */
         311, /* GL_EXT_EGL_image_array */
         312, /* GL_EXT_EGL_image_storage */
         313, /* GL_EXT_EGL_image_storage_compression */
         315, /* GL_EXT_YUV_target */
         317, /* GL_EXT_base_instance */
         322, /* GL_EXT_blend_func_extended */
         325, /* GL_EXT_blend_minmax */
         327, /* GL_EXT_buffer_reference */
         328, /* GL_EXT_buffer_reference2 */
         329, /* GL_EXT_buffer_storage */
         330, /* GL_EXT_clear_texture */
         331, /* GL_EXT_clip_control */
         332, /* GL_EXT_clip_cull_distance */
         335, /* GL_EXT_color_buffer_float */
         336, /* GL_EXT_color_buffer_half_float */
         339, /* GL_EXT_conservative_depth */
         340, /* GL_EXT_control_flow_attributes */
         343, /* GL_EXT_copy_image */
         346, /* GL_EXT_debug_label */
         347, /* GL_EXT_debug_marker */
         348, /* GL_EXT_debug_printf */
         349, /* GL_EXT_demote_to_helper_invocation */
         351, /* GL_EXT_depth_clamp */
         352, /* GL_EXT_device_group */
         354, /* GL_EXT_discard_framebuffer */
         355, /* GL_EXT_disjoint_timer_query */
         356, /* GL_EXT_draw_buffers */
         358, /* GL_EXT_draw_buffers_indexed */
         359, /* GL_EXT_draw_elements_base_vertex */
         360, /* GL_EXT_draw_instanced */
         362, /* GL_EXT_draw_transform_feedback */
         363, /* GL_EXT_external_buffer */
         364, /* GL_EXT_float_blend */
         366, /* GL_EXT_fragment_invocation_density */
         367, /* GL_EXT_fragment_shader_barycentric */
         368, /* GL_EXT_fragment_shading_rate */
         370, /* GL_EXT_framebuffer_blit_layers */
         375, /* GL_EXT_geometry_point_size */
         376, /* GL_EXT_geometry_shader */
         380, /* GL_EXT_gpu_shader5 */
         386, /* GL_EXT_instanced_arrays */
         388, /* GL_EXT_map_buffer_range */
         389, /* GL_EXT_memory_object */
         390, /* GL_EXT_memory_object_fd */
         391, /* GL_EXT_memory_object_win32 */
         393, /* GL_EXT_multi_draw_arrays */
         394, /* GL_EXT_multi_draw_indirect */
         396, /* GL_EXT_multisampled_compatibility */
         397, /* GL_EXT_multisampled_render_to_texture */
         398, /* GL_EXT_multisampled_render_to_texture2 */
         399, /* GL_EXT_multiview_draw_buffers */
         400, /* GL_EXT_multiview_tessellation_geometry_shader */
         401, /* GL_EXT_multiview_texture_multisample */
         402, /* GL_EXT_multiview_timer_query */
         403, /* GL_EXT_nonuniform_qualifier */
         404, /* GL_EXT_occlusion_query_boolean */
         414, /* GL_EXT_polygon_offset_clamp */
         415, /* GL_EXT_post_depth_coverage */
         416, /* GL_EXT_primitive_bounding_box */
         417, /* GL_EXT_protected_textures */
         419, /* GL_EXT_pvrtc_sRGB */
         420, /* GL_EXT_raster_multisample */
         421, /* GL_EXT_ray_cull_mask */
         422, /* GL_EXT_ray_flags_primitive_culling */
         423, /* GL_EXT_ray_query */
         424, /* GL_EXT_ray_tracing */
         425, /* GL_EXT_read_format_bgra */
         426, /* GL_EXT_render_snorm */
         428, /* GL_EXT_robustness */
         429, /* GL_EXT_sRGB */
         430, /* GL_EXT_sRGB_write_control */
         431, /* GL_EXT_samplerless_texture_functions */
         432, /* GL_EXT_scalar_block_layout */
         434, /* GL_EXT_semaphore */
         435, /* GL_EXT_semaphore_fd */
         436, /* GL_EXT_semaphore_win32 */
         437, /* GL_EXT_separate_depth_stencil */
         438, /* GL_EXT_separate_shader_objects */
         440, /* GL_EXT_shader_16bit_storage */
         441, /* GL_EXT_shader_atomic_float */
         442, /* GL_EXT_shader_explicit_arithmetic_types */
         443, /* GL_EXT_shader_framebuffer_fetch */
         444, /* GL_EXT_shader_framebuffer_fetch_non_coherent */
         445, /* GL_EXT_shader_group_vote */
         446, /* GL_EXT_shader_image_int64 */
         449, /* GL_EXT_shader_implicit_conversions */
         450, /* GL_EXT_shader_integer_mix */
         451, /* GL_EXT_shader_io_blocks */
         452, /* GL_EXT_shader_non_constant_global_initializers */
         453, /* GL_EXT_shader_pixel_local_storage */
         454, /* GL_EXT_shader_pixel_local_storage2 */
         455, /* GL_EXT_shader_realtime_clock */
         456, /* GL_EXT_shader_samples_identical */
         457, /* GL_EXT_shader_subgroup_extended_types */
         458, /* GL_EXT_shader_texture_lod */
         460, /* GL_EXT_shadow_samplers */
         461, /* GL_EXT_shared_memory_block */
         463, /* GL_EXT_sparse_texture */
         464, /* GL_EXT_sparse_texture2 */
         468, /* GL_EXT_subgroup_uniform_control_flow */
         469, /* GL_EXT_subgroupuniform_qualifier */
         471, /* GL_EXT_tessellation_point_size */
         472, /* GL_EXT_tessellation_shader */
         476, /* GL_EXT_texture_border_clamp */
         477, /* GL_EXT_texture_buffer */
         479, /* GL_EXT_texture_compression_astc_decode_mode */
         480, /* GL_EXT_texture_compression_bptc */
         481, /* GL_EXT_texture_compression_dxt1 */
         483, /* GL_EXT_texture_compression_rgtc */
         484, /* GL_EXT_texture_compression_s3tc */
         485, /* GL_EXT_texture_compression_s3tc_srgb */
         487, /* GL_EXT_texture_cube_map_array */
         491, /* GL_EXT_texture_filter_anisotropic */
         492, /* GL_EXT_texture_filter_minmax */
         493, /* GL_EXT_texture_format_BGRA8888 */
         494, /* GL_EXT_texture_format_sRGB_override */
         498, /* GL_EXT_texture_mirror_clamp_to_edge */
         499, /* GL_EXT_texture_norm16 */
         502, /* GL_EXT_texture_query_lod */
         503, /* GL_EXT_texture_rg */
         505, /* GL_EXT_texture_sRGB_R8 */
         506, /* GL_EXT_texture_sRGB_RG8 */
         507, /* GL_EXT_texture_sRGB_decode */
         508, /* GL_EXT_texture_shadow_lod */
         511, /* GL_EXT_texture_storage */
         512, /* GL_EXT_texture_storage_compression */
         514, /* GL_EXT_texture_type_2_10_10_10_REV */
         515, /* GL_EXT_texture_view */
         518, /* GL_EXT_unpack_subimage */
         524, /* GL_EXT_vulkan_glsl_relaxed */
         525, /* GL_EXT_win32_keyed_mutex */
         526, /* GL_EXT_window_rectangles */
         528, /* GL_FJ_shader_binary_GCCSO */
         535, /* GL_HUAWEI_subpass_shading */
         542, /* GL_IMG_bindless_texture */
         543, /* GL_IMG_framebuffer_downsample */
         544, /* GL_IMG_multisampled_render_to_texture */
         545, /* GL_IMG_program_binary */
         546, /* GL_IMG_read_format */
         547, /* GL_IMG_shader_binary */
         548, /* GL_IMG_texture_compression_pvrtc */
         549, /* GL_IMG_texture_compression_pvrtc2 */
         550, /* GL_IMG_texture_filter_cubic */
         554, /* GL_INTEL_blackhole_render */
         555, /* GL_INTEL_conservative_rasterization */
         557, /* GL_INTEL_framebuffer_CMAA */
         560, /* GL_INTEL_performance_query */
         561, /* GL_KHR_blend_equation_advanced */
         562, /* GL_KHR_blend_equation_advanced_coherent */
         563, /* GL_KHR_context_flush_control */
         564, /* GL_KHR_debug */
         565, /* GL_KHR_memory_scope_semantics */
         566, /* GL_KHR_no_error */
         567, /* GL_KHR_parallel_shader_compile */
         568, /* GL_KHR_robust_buffer_access_behavior */
         569, /* GL_KHR_robustness */
         570, /* GL_KHR_shader_subgroup */
         571, /* GL_KHR_texture_compression_astc_hdr */
         572, /* GL_KHR_texture_compression_astc_ldr */
         573, /* GL_KHR_texture_compression_astc_sliced_3d */
         574, /* GL_KHR_vulkan_glsl */
         576, /* GL_MESA_bgra */
         577, /* GL_MESA_framebuffer_flip_x */
         578, /* GL_MESA_framebuffer_flip_y */
         579, /* GL_MESA_framebuffer_swap_xy */
         581, /* GL_MESA_program_binary_formats */
         583, /* GL_MESA_sampler_objects */
         584, /* GL_MESA_shader_integer_functions */
         588, /* GL_NVX_blend_equation_advanced_multi_draw_buffers */
         593, /* GL_NVX_multiview_per_view_attributes */
         598, /* GL_NV_bindless_texture */
         599, /* GL_NV_blend_equation_advanced */
         600, /* GL_NV_blend_equation_advanced_coherent */
         601, /* GL_NV_blend_minmax_factor */
         603, /* GL_NV_clip_space_w_scaling */
         606, /* GL_NV_compute_shader_derivatives */
         607, /* GL_NV_conditional_render */
         608, /* GL_NV_conservative_raster */
         610, /* GL_NV_conservative_raster_pre_snap */
         611, /* GL_NV_conservative_raster_pre_snap_triangles */
         613, /* GL_NV_cooperative_matrix */
         614, /* GL_NV_copy_buffer */
         617, /* GL_NV_coverage_sample */
         621, /* GL_NV_depth_nonlinear */
         622, /* GL_NV_draw_buffers */
         623, /* GL_NV_draw_instanced */
         625, /* GL_NV_draw_vulkan_image */
         627, /* GL_NV_explicit_attrib_location */
         629, /* GL_NV_fbo_color_attachments */
         630, /* GL_NV_fence */
         631, /* GL_NV_fill_rectangle */
         634, /* GL_NV_fragment_coverage_to_color */
         639, /* GL_NV_fragment_shader_barycentric */
         640, /* GL_NV_fragment_shader_interlock */
         641, /* GL_NV_framebuffer_blit */
         642, /* GL_NV_framebuffer_mixed_samples */
         643, /* GL_NV_framebuffer_multisample */
         645, /* GL_NV_generate_mipmap_sRGB */
         648, /* GL_NV_geometry_shader_passthrough */
         653, /* GL_NV_gpu_shader5 */
         655, /* GL_NV_image_formats */
         656, /* GL_NV_instanced_arrays */
         657, /* GL_NV_internalformat_sample_query */
         659, /* GL_NV_memory_attachment */
         660, /* GL_NV_memory_object_sparse */
         661, /* GL_NV_mesh_shader */
         664, /* GL_NV_non_square_matrices */
         666, /* GL_NV_pack_subimage */
         670, /* GL_NV_path_rendering */
         671, /* GL_NV_path_rendering_shared_edge */
         672, /* GL_NV_pixel_buffer_object */
         675, /* GL_NV_polygon_mode */
         678, /* GL_NV_primitive_shading_rate */
         681, /* GL_NV_ray_tracing */
         682, /* GL_NV_ray_tracing_motion_blur */
         683, /* GL_NV_read_buffer */
         684, /* GL_NV_read_buffer_front */
         685, /* GL_NV_read_depth */
         686, /* GL_NV_read_depth_stencil */
         687, /* GL_NV_read_stencil */
         690, /* GL_NV_representative_fragment_test */
         692, /* GL_NV_sRGB_formats */
         693, /* GL_NV_sample_locations */
         694, /* GL_NV_sample_mask_override_coverage */
         695, /* GL_NV_scissor_exclusive */
         699, /* GL_NV_shader_atomic_fp16_vector */
         703, /* GL_NV_shader_noperspective_interpolation */
         704, /* GL_NV_shader_sm_builtins */
         706, /* GL_NV_shader_subgroup_partitioned */
         707, /* GL_NV_shader_texture_footprint */
         710, /* GL_NV_shading_rate_image */
         711, /* GL_NV_shadow_samplers_array */
         712, /* GL_NV_shadow_samplers_cube */
         713, /* GL_NV_stereo_view_rendering */
         718, /* GL_NV_texture_border_clamp */
         719, /* GL_NV_texture_compression_s3tc_update */
         724, /* GL_NV_texture_npot_2D_mipmap */
         730, /* GL_NV_timeline_semaphore */
         748, /* GL_NV_viewport_array */
         749, /* GL_NV_viewport_array2 */
         750, /* GL_NV_viewport_swizzle */
         751, /* GL_OES_EGL_image */
         752, /* GL_OES_EGL_image_external */
         753, /* GL_OES_EGL_image_external_essl3 */
         755, /* GL_OES_compressed_ETC1_RGB8_sub_texture */
         756, /* GL_OES_compressed_ETC1_RGB8_texture */
         757, /* GL_OES_compressed_paletted_texture */
         758, /* GL_OES_copy_image */
         759, /* GL_OES_depth24 */
         760, /* GL_OES_depth32 */
         761, /* GL_OES_depth_texture */
         762, /* GL_OES_draw_buffers_indexed */
         763, /* GL_OES_draw_elements_base_vertex */
         764, /* GL_OES_element_index_uint */
         765, /* GL_OES_fbo_render_mipmap */
         767, /* GL_OES_fragment_precision_high */
         768, /* GL_OES_geometry_point_size */
         769, /* GL_OES_geometry_shader */
         770, /* GL_OES_get_program_binary */
         771, /* GL_OES_gpu_shader5 */
         772, /* GL_OES_mapbuffer */
         773, /* GL_OES_packed_depth_stencil */
         774, /* GL_OES_primitive_bounding_box */
         777, /* GL_OES_required_internalformat */
         778, /* GL_OES_rgb8_rgba8 */
         779, /* GL_OES_sample_shading */
         780, /* GL_OES_sample_variables */
         781, /* GL_OES_shader_image_atomic */
         782, /* GL_OES_shader_io_blocks */
         783, /* GL_OES_shader_multisample_interpolation */
         785, /* GL_OES_standard_derivatives */
         786, /* GL_OES_stencil1 */
         787, /* GL_OES_stencil4 */
         788, /* GL_OES_surfaceless_context */
         789, /* GL_OES_tessellation_point_size */
         790, /* GL_OES_tessellation_shader */
         791, /* GL_OES_texture_3D */
         792, /* GL_OES_texture_border_clamp */
         793, /* GL_OES_texture_buffer */
         794, /* GL_OES_texture_compression_astc */
         795, /* GL_OES_texture_cube_map_array */
         796, /* GL_OES_texture_float */
         797, /* GL_OES_texture_float_linear */
         798, /* GL_OES_texture_half_float */
         799, /* GL_OES_texture_half_float_linear */
         800, /* GL_OES_texture_npot */
         801, /* GL_OES_texture_stencil8 */
         802, /* GL_OES_texture_storage_multisample_2d_array */
         803, /* GL_OES_texture_view */
         804, /* GL_OES_vertex_array_object */
         805, /* GL_OES_vertex_half_float */
         806, /* GL_OES_vertex_type_10_10_10_2 */
         807, /* GL_OES_viewport_array */
         811, /* GL_OVR_multiview */
         812, /* GL_OVR_multiview2 */
         813, /* GL_OVR_multiview_multisampled_render_to_texture */
         816, /* GL_QCOM_YUV_texture_gather */
         817, /* GL_QCOM_alpha_test */
         818, /* GL_QCOM_binning_control */
         819, /* GL_QCOM_driver_control */
         820, /* GL_QCOM_extended_get */
         821, /* GL_QCOM_extended_get2 */
         822, /* GL_QCOM_frame_extrapolation */
         823, /* GL_QCOM_framebuffer_foveated */
         824, /* GL_QCOM_motion_estimation */
         825, /* GL_QCOM_perfmon_global_mode */
         826, /* GL_QCOM_render_sRGB_R8_RG8 */
         827, /* GL_QCOM_render_shared_exponent */
         828, /* GL_QCOM_shader_framebuffer_fetch_noncoherent */
         829, /* GL_QCOM_shader_framebuffer_fetch_rate */
         830, /* GL_QCOM_shading_rate */
         831, /* GL_QCOM_texture_foveated */
         832, /* GL_QCOM_texture_foveated2 */
         833, /* GL_QCOM_texture_foveated_subsampled_layout */
         834, /* GL_QCOM_texture_lod_bias */
         835, /* GL_QCOM_tiled_rendering */
         836, /* GL_QCOM_writeonly_rendering */
         902, /* GL_VIV_shader_binary */
    };
    uint64_t *exts = NULL;
    uint32_t num_exts = 0;
    uint32_t i;
    if (!glad_gl_get_extensions(context, version, &exts, &num_exts)) return 0;

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
    if(context->GetString(GL_VERSION) == NULL) return 0;
    version = glad_gl_find_core_gles2(context);

    glad_gl_load_GL_ES_VERSION_2_0(context, load, userptr);
    glad_gl_load_GL_ES_VERSION_3_0(context, load, userptr);
    glad_gl_load_GL_ES_VERSION_3_1(context, load, userptr);
    glad_gl_load_GL_ES_VERSION_3_2(context, load, userptr);

    if (!glad_gl_find_extensions_gles2(context, version)) return 0;
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
