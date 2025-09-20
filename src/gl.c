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

typedef struct {
    uint16_t extension;
    uint16_t start;
    uint16_t count;
} GladPfnRange_t;

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
GladGLContext glad_gl_context = {};
#else
GladGLContext glad_gl_context = { 0 };
#endif

static const char *GLAD_GL_fn_names[] = {
    /*    0 */ "glCullFace",
    /*    1 */ "glFrontFace",
    /*    2 */ "glHint",
    /*    3 */ "glLineWidth",
    /*    4 */ "glPointSize",
    /*    5 */ "glPolygonMode",
    /*    6 */ "glScissor",
    /*    7 */ "glTexParameterf",
    /*    8 */ "glTexParameterfv",
    /*    9 */ "glTexParameteri",
    /*   10 */ "glTexParameteriv",
    /*   11 */ "glTexImage1D",
    /*   12 */ "glTexImage2D",
    /*   13 */ "glDrawBuffer",
    /*   14 */ "glClear",
    /*   15 */ "glClearColor",
    /*   16 */ "glClearStencil",
    /*   17 */ "glClearDepth",
    /*   18 */ "glStencilMask",
    /*   19 */ "glColorMask",
    /*   20 */ "glDepthMask",
    /*   21 */ "glDisable",
    /*   22 */ "glEnable",
    /*   23 */ "glFinish",
    /*   24 */ "glFlush",
    /*   25 */ "glBlendFunc",
    /*   26 */ "glLogicOp",
    /*   27 */ "glStencilFunc",
    /*   28 */ "glStencilOp",
    /*   29 */ "glDepthFunc",
    /*   30 */ "glPixelStoref",
    /*   31 */ "glPixelStorei",
    /*   32 */ "glReadBuffer",
    /*   33 */ "glReadPixels",
    /*   34 */ "glGetBooleanv",
    /*   35 */ "glGetDoublev",
    /*   36 */ "glGetError",
    /*   37 */ "glGetFloatv",
    /*   38 */ "glGetIntegerv",
    /*   39 */ "glGetString",
    /*   40 */ "glGetTexImage",
    /*   41 */ "glGetTexParameterfv",
    /*   42 */ "glGetTexParameteriv",
    /*   43 */ "glGetTexLevelParameterfv",
    /*   44 */ "glGetTexLevelParameteriv",
    /*   45 */ "glIsEnabled",
    /*   46 */ "glDepthRange",
    /*   47 */ "glViewport",
    /*   48 */ "glDrawArrays",
    /*   49 */ "glDrawElements",
    /*   50 */ "glGetPointerv",
    /*   51 */ "glPolygonOffset",
    /*   52 */ "glCopyTexImage1D",
    /*   53 */ "glCopyTexImage2D",
    /*   54 */ "glCopyTexSubImage1D",
    /*   55 */ "glCopyTexSubImage2D",
    /*   56 */ "glTexSubImage1D",
    /*   57 */ "glTexSubImage2D",
    /*   58 */ "glBindTexture",
    /*   59 */ "glDeleteTextures",
    /*   60 */ "glGenTextures",
    /*   61 */ "glIsTexture",
    /*   62 */ "glDrawRangeElements",
    /*   63 */ "glTexImage3D",
    /*   64 */ "glTexSubImage3D",
    /*   65 */ "glCopyTexSubImage3D",
    /*   66 */ "glActiveTexture",
    /*   67 */ "glSampleCoverage",
    /*   68 */ "glCompressedTexImage3D",
    /*   69 */ "glCompressedTexImage2D",
    /*   70 */ "glCompressedTexImage1D",
    /*   71 */ "glCompressedTexSubImage3D",
    /*   72 */ "glCompressedTexSubImage2D",
    /*   73 */ "glCompressedTexSubImage1D",
    /*   74 */ "glGetCompressedTexImage",
    /*   75 */ "glBlendFuncSeparate",
    /*   76 */ "glMultiDrawArrays",
    /*   77 */ "glMultiDrawElements",
    /*   78 */ "glPointParameterf",
    /*   79 */ "glPointParameterfv",
    /*   80 */ "glPointParameteri",
    /*   81 */ "glPointParameteriv",
    /*   82 */ "glBlendColor",
    /*   83 */ "glBlendEquation",
    /*   84 */ "glGenQueries",
    /*   85 */ "glDeleteQueries",
    /*   86 */ "glIsQuery",
    /*   87 */ "glBeginQuery",
    /*   88 */ "glEndQuery",
    /*   89 */ "glGetQueryiv",
    /*   90 */ "glGetQueryObjectiv",
    /*   91 */ "glGetQueryObjectuiv",
    /*   92 */ "glBindBuffer",
    /*   93 */ "glDeleteBuffers",
    /*   94 */ "glGenBuffers",
    /*   95 */ "glIsBuffer",
    /*   96 */ "glBufferData",
    /*   97 */ "glBufferSubData",
    /*   98 */ "glGetBufferSubData",
    /*   99 */ "glMapBuffer",
    /*  100 */ "glUnmapBuffer",
    /*  101 */ "glGetBufferParameteriv",
    /*  102 */ "glGetBufferPointerv",
    /*  103 */ "glBlendEquationSeparate",
    /*  104 */ "glDrawBuffers",
    /*  105 */ "glStencilOpSeparate",
    /*  106 */ "glStencilFuncSeparate",
    /*  107 */ "glStencilMaskSeparate",
    /*  108 */ "glAttachShader",
    /*  109 */ "glBindAttribLocation",
    /*  110 */ "glCompileShader",
    /*  111 */ "glCreateProgram",
    /*  112 */ "glCreateShader",
    /*  113 */ "glDeleteProgram",
    /*  114 */ "glDeleteShader",
    /*  115 */ "glDetachShader",
    /*  116 */ "glDisableVertexAttribArray",
    /*  117 */ "glEnableVertexAttribArray",
    /*  118 */ "glGetActiveAttrib",
    /*  119 */ "glGetActiveUniform",
    /*  120 */ "glGetAttachedShaders",
    /*  121 */ "glGetAttribLocation",
    /*  122 */ "glGetProgramiv",
    /*  123 */ "glGetProgramInfoLog",
    /*  124 */ "glGetShaderiv",
    /*  125 */ "glGetShaderInfoLog",
    /*  126 */ "glGetShaderSource",
    /*  127 */ "glGetUniformLocation",
    /*  128 */ "glGetUniformfv",
    /*  129 */ "glGetUniformiv",
    /*  130 */ "glGetVertexAttribdv",
    /*  131 */ "glGetVertexAttribfv",
    /*  132 */ "glGetVertexAttribiv",
    /*  133 */ "glGetVertexAttribPointerv",
    /*  134 */ "glIsProgram",
    /*  135 */ "glIsShader",
    /*  136 */ "glLinkProgram",
    /*  137 */ "glShaderSource",
    /*  138 */ "glUseProgram",
    /*  139 */ "glUniform1f",
    /*  140 */ "glUniform2f",
    /*  141 */ "glUniform3f",
    /*  142 */ "glUniform4f",
    /*  143 */ "glUniform1i",
    /*  144 */ "glUniform2i",
    /*  145 */ "glUniform3i",
    /*  146 */ "glUniform4i",
    /*  147 */ "glUniform1fv",
    /*  148 */ "glUniform2fv",
    /*  149 */ "glUniform3fv",
    /*  150 */ "glUniform4fv",
    /*  151 */ "glUniform1iv",
    /*  152 */ "glUniform2iv",
    /*  153 */ "glUniform3iv",
    /*  154 */ "glUniform4iv",
    /*  155 */ "glUniformMatrix2fv",
    /*  156 */ "glUniformMatrix3fv",
    /*  157 */ "glUniformMatrix4fv",
    /*  158 */ "glValidateProgram",
    /*  159 */ "glVertexAttrib1d",
    /*  160 */ "glVertexAttrib1dv",
    /*  161 */ "glVertexAttrib1f",
    /*  162 */ "glVertexAttrib1fv",
    /*  163 */ "glVertexAttrib1s",
    /*  164 */ "glVertexAttrib1sv",
    /*  165 */ "glVertexAttrib2d",
    /*  166 */ "glVertexAttrib2dv",
    /*  167 */ "glVertexAttrib2f",
    /*  168 */ "glVertexAttrib2fv",
    /*  169 */ "glVertexAttrib2s",
    /*  170 */ "glVertexAttrib2sv",
    /*  171 */ "glVertexAttrib3d",
    /*  172 */ "glVertexAttrib3dv",
    /*  173 */ "glVertexAttrib3f",
    /*  174 */ "glVertexAttrib3fv",
    /*  175 */ "glVertexAttrib3s",
    /*  176 */ "glVertexAttrib3sv",
    /*  177 */ "glVertexAttrib4Nbv",
    /*  178 */ "glVertexAttrib4Niv",
    /*  179 */ "glVertexAttrib4Nsv",
    /*  180 */ "glVertexAttrib4Nub",
    /*  181 */ "glVertexAttrib4Nubv",
    /*  182 */ "glVertexAttrib4Nuiv",
    /*  183 */ "glVertexAttrib4Nusv",
    /*  184 */ "glVertexAttrib4bv",
    /*  185 */ "glVertexAttrib4d",
    /*  186 */ "glVertexAttrib4dv",
    /*  187 */ "glVertexAttrib4f",
    /*  188 */ "glVertexAttrib4fv",
    /*  189 */ "glVertexAttrib4iv",
    /*  190 */ "glVertexAttrib4s",
    /*  191 */ "glVertexAttrib4sv",
    /*  192 */ "glVertexAttrib4ubv",
    /*  193 */ "glVertexAttrib4uiv",
    /*  194 */ "glVertexAttrib4usv",
    /*  195 */ "glVertexAttribPointer",
    /*  196 */ "glUniformMatrix2x3fv",
    /*  197 */ "glUniformMatrix3x2fv",
    /*  198 */ "glUniformMatrix2x4fv",
    /*  199 */ "glUniformMatrix4x2fv",
    /*  200 */ "glUniformMatrix3x4fv",
    /*  201 */ "glUniformMatrix4x3fv",
    /*  202 */ "glColorMaski",
    /*  203 */ "glGetBooleani_v",
    /*  204 */ "glGetIntegeri_v",
    /*  205 */ "glEnablei",
    /*  206 */ "glDisablei",
    /*  207 */ "glIsEnabledi",
    /*  208 */ "glBeginTransformFeedback",
    /*  209 */ "glEndTransformFeedback",
    /*  210 */ "glBindBufferRange",
    /*  211 */ "glBindBufferBase",
    /*  212 */ "glTransformFeedbackVaryings",
    /*  213 */ "glGetTransformFeedbackVarying",
    /*  214 */ "glClampColor",
    /*  215 */ "glBeginConditionalRender",
    /*  216 */ "glEndConditionalRender",
    /*  217 */ "glVertexAttribIPointer",
    /*  218 */ "glGetVertexAttribIiv",
    /*  219 */ "glGetVertexAttribIuiv",
    /*  220 */ "glVertexAttribI1i",
    /*  221 */ "glVertexAttribI2i",
    /*  222 */ "glVertexAttribI3i",
    /*  223 */ "glVertexAttribI4i",
    /*  224 */ "glVertexAttribI1ui",
    /*  225 */ "glVertexAttribI2ui",
    /*  226 */ "glVertexAttribI3ui",
    /*  227 */ "glVertexAttribI4ui",
    /*  228 */ "glVertexAttribI1iv",
    /*  229 */ "glVertexAttribI2iv",
    /*  230 */ "glVertexAttribI3iv",
    /*  231 */ "glVertexAttribI4iv",
    /*  232 */ "glVertexAttribI1uiv",
    /*  233 */ "glVertexAttribI2uiv",
    /*  234 */ "glVertexAttribI3uiv",
    /*  235 */ "glVertexAttribI4uiv",
    /*  236 */ "glVertexAttribI4bv",
    /*  237 */ "glVertexAttribI4sv",
    /*  238 */ "glVertexAttribI4ubv",
    /*  239 */ "glVertexAttribI4usv",
    /*  240 */ "glGetUniformuiv",
    /*  241 */ "glBindFragDataLocation",
    /*  242 */ "glGetFragDataLocation",
    /*  243 */ "glUniform1ui",
    /*  244 */ "glUniform2ui",
    /*  245 */ "glUniform3ui",
    /*  246 */ "glUniform4ui",
    /*  247 */ "glUniform1uiv",
    /*  248 */ "glUniform2uiv",
    /*  249 */ "glUniform3uiv",
    /*  250 */ "glUniform4uiv",
    /*  251 */ "glTexParameterIiv",
    /*  252 */ "glTexParameterIuiv",
    /*  253 */ "glGetTexParameterIiv",
    /*  254 */ "glGetTexParameterIuiv",
    /*  255 */ "glClearBufferiv",
    /*  256 */ "glClearBufferuiv",
    /*  257 */ "glClearBufferfv",
    /*  258 */ "glClearBufferfi",
    /*  259 */ "glGetStringi",
    /*  260 */ "glIsRenderbuffer",
    /*  261 */ "glBindRenderbuffer",
    /*  262 */ "glDeleteRenderbuffers",
    /*  263 */ "glGenRenderbuffers",
    /*  264 */ "glRenderbufferStorage",
    /*  265 */ "glGetRenderbufferParameteriv",
    /*  266 */ "glIsFramebuffer",
    /*  267 */ "glBindFramebuffer",
    /*  268 */ "glDeleteFramebuffers",
    /*  269 */ "glGenFramebuffers",
    /*  270 */ "glCheckFramebufferStatus",
    /*  271 */ "glFramebufferTexture1D",
    /*  272 */ "glFramebufferTexture2D",
    /*  273 */ "glFramebufferTexture3D",
    /*  274 */ "glFramebufferRenderbuffer",
    /*  275 */ "glGetFramebufferAttachmentParameteriv",
    /*  276 */ "glGenerateMipmap",
    /*  277 */ "glBlitFramebuffer",
    /*  278 */ "glRenderbufferStorageMultisample",
    /*  279 */ "glFramebufferTextureLayer",
    /*  280 */ "glMapBufferRange",
    /*  281 */ "glFlushMappedBufferRange",
    /*  282 */ "glBindVertexArray",
    /*  283 */ "glDeleteVertexArrays",
    /*  284 */ "glGenVertexArrays",
    /*  285 */ "glIsVertexArray",
    /*  286 */ "glDrawArraysInstanced",
    /*  287 */ "glDrawElementsInstanced",
    /*  288 */ "glTexBuffer",
    /*  289 */ "glPrimitiveRestartIndex",
    /*  290 */ "glCopyBufferSubData",
    /*  291 */ "glGetUniformIndices",
    /*  292 */ "glGetActiveUniformsiv",
    /*  293 */ "glGetActiveUniformName",
    /*  294 */ "glGetUniformBlockIndex",
    /*  295 */ "glGetActiveUniformBlockiv",
    /*  296 */ "glGetActiveUniformBlockName",
    /*  297 */ "glUniformBlockBinding",
    /*  298 */ "glDrawElementsBaseVertex",
    /*  299 */ "glDrawRangeElementsBaseVertex",
    /*  300 */ "glDrawElementsInstancedBaseVertex",
    /*  301 */ "glMultiDrawElementsBaseVertex",
    /*  302 */ "glProvokingVertex",
    /*  303 */ "glFenceSync",
    /*  304 */ "glIsSync",
    /*  305 */ "glDeleteSync",
    /*  306 */ "glClientWaitSync",
    /*  307 */ "glWaitSync",
    /*  308 */ "glGetInteger64v",
    /*  309 */ "glGetSynciv",
    /*  310 */ "glGetInteger64i_v",
    /*  311 */ "glGetBufferParameteri64v",
    /*  312 */ "glFramebufferTexture",
    /*  313 */ "glTexImage2DMultisample",
    /*  314 */ "glTexImage3DMultisample",
    /*  315 */ "glGetMultisamplefv",
    /*  316 */ "glSampleMaski",
    /*  317 */ "glBindFragDataLocationIndexed",
    /*  318 */ "glGetFragDataIndex",
    /*  319 */ "glGenSamplers",
    /*  320 */ "glDeleteSamplers",
    /*  321 */ "glIsSampler",
    /*  322 */ "glBindSampler",
    /*  323 */ "glSamplerParameteri",
    /*  324 */ "glSamplerParameteriv",
    /*  325 */ "glSamplerParameterf",
    /*  326 */ "glSamplerParameterfv",
    /*  327 */ "glSamplerParameterIiv",
    /*  328 */ "glSamplerParameterIuiv",
    /*  329 */ "glGetSamplerParameteriv",
    /*  330 */ "glGetSamplerParameterIiv",
    /*  331 */ "glGetSamplerParameterfv",
    /*  332 */ "glGetSamplerParameterIuiv",
    /*  333 */ "glQueryCounter",
    /*  334 */ "glGetQueryObjecti64v",
    /*  335 */ "glGetQueryObjectui64v",
    /*  336 */ "glVertexAttribDivisor",
    /*  337 */ "glVertexAttribP1ui",
    /*  338 */ "glVertexAttribP1uiv",
    /*  339 */ "glVertexAttribP2ui",
    /*  340 */ "glVertexAttribP2uiv",
    /*  341 */ "glVertexAttribP3ui",
    /*  342 */ "glVertexAttribP3uiv",
    /*  343 */ "glVertexAttribP4ui",
    /*  344 */ "glVertexAttribP4uiv",
    /*  345 */ "glMinSampleShading",
    /*  346 */ "glBlendEquationi",
    /*  347 */ "glBlendEquationSeparatei",
    /*  348 */ "glBlendFunci",
    /*  349 */ "glBlendFuncSeparatei",
    /*  350 */ "glDrawArraysIndirect",
    /*  351 */ "glDrawElementsIndirect",
    /*  352 */ "glUniform1d",
    /*  353 */ "glUniform2d",
    /*  354 */ "glUniform3d",
    /*  355 */ "glUniform4d",
    /*  356 */ "glUniform1dv",
    /*  357 */ "glUniform2dv",
    /*  358 */ "glUniform3dv",
    /*  359 */ "glUniform4dv",
    /*  360 */ "glUniformMatrix2dv",
    /*  361 */ "glUniformMatrix3dv",
    /*  362 */ "glUniformMatrix4dv",
    /*  363 */ "glUniformMatrix2x3dv",
    /*  364 */ "glUniformMatrix2x4dv",
    /*  365 */ "glUniformMatrix3x2dv",
    /*  366 */ "glUniformMatrix3x4dv",
    /*  367 */ "glUniformMatrix4x2dv",
    /*  368 */ "glUniformMatrix4x3dv",
    /*  369 */ "glGetUniformdv",
    /*  370 */ "glGetSubroutineUniformLocation",
    /*  371 */ "glGetSubroutineIndex",
    /*  372 */ "glGetActiveSubroutineUniformiv",
    /*  373 */ "glGetActiveSubroutineUniformName",
    /*  374 */ "glGetActiveSubroutineName",
    /*  375 */ "glUniformSubroutinesuiv",
    /*  376 */ "glGetUniformSubroutineuiv",
    /*  377 */ "glGetProgramStageiv",
    /*  378 */ "glPatchParameteri",
    /*  379 */ "glPatchParameterfv",
    /*  380 */ "glBindTransformFeedback",
    /*  381 */ "glDeleteTransformFeedbacks",
    /*  382 */ "glGenTransformFeedbacks",
    /*  383 */ "glIsTransformFeedback",
    /*  384 */ "glPauseTransformFeedback",
    /*  385 */ "glResumeTransformFeedback",
    /*  386 */ "glDrawTransformFeedback",
    /*  387 */ "glDrawTransformFeedbackStream",
    /*  388 */ "glBeginQueryIndexed",
    /*  389 */ "glEndQueryIndexed",
    /*  390 */ "glGetQueryIndexediv",
    /*  391 */ "glReleaseShaderCompiler",
    /*  392 */ "glShaderBinary",
    /*  393 */ "glGetShaderPrecisionFormat",
    /*  394 */ "glDepthRangef",
    /*  395 */ "glClearDepthf",
    /*  396 */ "glGetProgramBinary",
    /*  397 */ "glProgramBinary",
    /*  398 */ "glProgramParameteri",
    /*  399 */ "glUseProgramStages",
    /*  400 */ "glActiveShaderProgram",
    /*  401 */ "glCreateShaderProgramv",
    /*  402 */ "glBindProgramPipeline",
    /*  403 */ "glDeleteProgramPipelines",
    /*  404 */ "glGenProgramPipelines",
    /*  405 */ "glIsProgramPipeline",
    /*  406 */ "glGetProgramPipelineiv",
    /*  407 */ "glProgramUniform1i",
    /*  408 */ "glProgramUniform1iv",
    /*  409 */ "glProgramUniform1f",
    /*  410 */ "glProgramUniform1fv",
    /*  411 */ "glProgramUniform1d",
    /*  412 */ "glProgramUniform1dv",
    /*  413 */ "glProgramUniform1ui",
    /*  414 */ "glProgramUniform1uiv",
    /*  415 */ "glProgramUniform2i",
    /*  416 */ "glProgramUniform2iv",
    /*  417 */ "glProgramUniform2f",
    /*  418 */ "glProgramUniform2fv",
    /*  419 */ "glProgramUniform2d",
    /*  420 */ "glProgramUniform2dv",
    /*  421 */ "glProgramUniform2ui",
    /*  422 */ "glProgramUniform2uiv",
    /*  423 */ "glProgramUniform3i",
    /*  424 */ "glProgramUniform3iv",
    /*  425 */ "glProgramUniform3f",
    /*  426 */ "glProgramUniform3fv",
    /*  427 */ "glProgramUniform3d",
    /*  428 */ "glProgramUniform3dv",
    /*  429 */ "glProgramUniform3ui",
    /*  430 */ "glProgramUniform3uiv",
    /*  431 */ "glProgramUniform4i",
    /*  432 */ "glProgramUniform4iv",
    /*  433 */ "glProgramUniform4f",
    /*  434 */ "glProgramUniform4fv",
    /*  435 */ "glProgramUniform4d",
    /*  436 */ "glProgramUniform4dv",
    /*  437 */ "glProgramUniform4ui",
    /*  438 */ "glProgramUniform4uiv",
    /*  439 */ "glProgramUniformMatrix2fv",
    /*  440 */ "glProgramUniformMatrix3fv",
    /*  441 */ "glProgramUniformMatrix4fv",
    /*  442 */ "glProgramUniformMatrix2dv",
    /*  443 */ "glProgramUniformMatrix3dv",
    /*  444 */ "glProgramUniformMatrix4dv",
    /*  445 */ "glProgramUniformMatrix2x3fv",
    /*  446 */ "glProgramUniformMatrix3x2fv",
    /*  447 */ "glProgramUniformMatrix2x4fv",
    /*  448 */ "glProgramUniformMatrix4x2fv",
    /*  449 */ "glProgramUniformMatrix3x4fv",
    /*  450 */ "glProgramUniformMatrix4x3fv",
    /*  451 */ "glProgramUniformMatrix2x3dv",
    /*  452 */ "glProgramUniformMatrix3x2dv",
    /*  453 */ "glProgramUniformMatrix2x4dv",
    /*  454 */ "glProgramUniformMatrix4x2dv",
    /*  455 */ "glProgramUniformMatrix3x4dv",
    /*  456 */ "glProgramUniformMatrix4x3dv",
    /*  457 */ "glValidateProgramPipeline",
    /*  458 */ "glGetProgramPipelineInfoLog",
    /*  459 */ "glVertexAttribL1d",
    /*  460 */ "glVertexAttribL2d",
    /*  461 */ "glVertexAttribL3d",
    /*  462 */ "glVertexAttribL4d",
    /*  463 */ "glVertexAttribL1dv",
    /*  464 */ "glVertexAttribL2dv",
    /*  465 */ "glVertexAttribL3dv",
    /*  466 */ "glVertexAttribL4dv",
    /*  467 */ "glVertexAttribLPointer",
    /*  468 */ "glGetVertexAttribLdv",
    /*  469 */ "glViewportArrayv",
    /*  470 */ "glViewportIndexedf",
    /*  471 */ "glViewportIndexedfv",
    /*  472 */ "glScissorArrayv",
    /*  473 */ "glScissorIndexed",
    /*  474 */ "glScissorIndexedv",
    /*  475 */ "glDepthRangeArrayv",
    /*  476 */ "glDepthRangeIndexed",
    /*  477 */ "glGetFloati_v",
    /*  478 */ "glGetDoublei_v",
    /*  479 */ "glDrawArraysInstancedBaseInstance",
    /*  480 */ "glDrawElementsInstancedBaseInstance",
    /*  481 */ "glDrawElementsInstancedBaseVertexBaseInstance",
    /*  482 */ "glGetInternalformativ",
    /*  483 */ "glGetActiveAtomicCounterBufferiv",
    /*  484 */ "glBindImageTexture",
    /*  485 */ "glMemoryBarrier",
    /*  486 */ "glTexStorage1D",
    /*  487 */ "glTexStorage2D",
    /*  488 */ "glTexStorage3D",
    /*  489 */ "glDrawTransformFeedbackInstanced",
    /*  490 */ "glDrawTransformFeedbackStreamInstanced",
    /*  491 */ "glClearBufferData",
    /*  492 */ "glClearBufferSubData",
    /*  493 */ "glDispatchCompute",
    /*  494 */ "glDispatchComputeIndirect",
    /*  495 */ "glCopyImageSubData",
    /*  496 */ "glFramebufferParameteri",
    /*  497 */ "glGetFramebufferParameteriv",
    /*  498 */ "glGetInternalformati64v",
    /*  499 */ "glInvalidateTexSubImage",
    /*  500 */ "glInvalidateTexImage",
    /*  501 */ "glInvalidateBufferSubData",
    /*  502 */ "glInvalidateBufferData",
    /*  503 */ "glInvalidateFramebuffer",
    /*  504 */ "glInvalidateSubFramebuffer",
    /*  505 */ "glMultiDrawArraysIndirect",
    /*  506 */ "glMultiDrawElementsIndirect",
    /*  507 */ "glGetProgramInterfaceiv",
    /*  508 */ "glGetProgramResourceIndex",
    /*  509 */ "glGetProgramResourceName",
    /*  510 */ "glGetProgramResourceiv",
    /*  511 */ "glGetProgramResourceLocation",
    /*  512 */ "glGetProgramResourceLocationIndex",
    /*  513 */ "glShaderStorageBlockBinding",
    /*  514 */ "glTexBufferRange",
    /*  515 */ "glTexStorage2DMultisample",
    /*  516 */ "glTexStorage3DMultisample",
    /*  517 */ "glTextureView",
    /*  518 */ "glBindVertexBuffer",
    /*  519 */ "glVertexAttribFormat",
    /*  520 */ "glVertexAttribIFormat",
    /*  521 */ "glVertexAttribLFormat",
    /*  522 */ "glVertexAttribBinding",
    /*  523 */ "glVertexBindingDivisor",
    /*  524 */ "glDebugMessageControl",
    /*  525 */ "glDebugMessageInsert",
    /*  526 */ "glDebugMessageCallback",
    /*  527 */ "glGetDebugMessageLog",
    /*  528 */ "glPushDebugGroup",
    /*  529 */ "glPopDebugGroup",
    /*  530 */ "glObjectLabel",
    /*  531 */ "glGetObjectLabel",
    /*  532 */ "glObjectPtrLabel",
    /*  533 */ "glGetObjectPtrLabel",
    /*  534 */ "glBufferStorage",
    /*  535 */ "glClearTexImage",
    /*  536 */ "glClearTexSubImage",
    /*  537 */ "glBindBuffersBase",
    /*  538 */ "glBindBuffersRange",
    /*  539 */ "glBindTextures",
    /*  540 */ "glBindSamplers",
    /*  541 */ "glBindImageTextures",
    /*  542 */ "glBindVertexBuffers",
    /*  543 */ "glClipControl",
    /*  544 */ "glCreateTransformFeedbacks",
    /*  545 */ "glTransformFeedbackBufferBase",
    /*  546 */ "glTransformFeedbackBufferRange",
    /*  547 */ "glGetTransformFeedbackiv",
    /*  548 */ "glGetTransformFeedbacki_v",
    /*  549 */ "glGetTransformFeedbacki64_v",
    /*  550 */ "glCreateBuffers",
    /*  551 */ "glNamedBufferStorage",
    /*  552 */ "glNamedBufferData",
    /*  553 */ "glNamedBufferSubData",
    /*  554 */ "glCopyNamedBufferSubData",
    /*  555 */ "glClearNamedBufferData",
    /*  556 */ "glClearNamedBufferSubData",
    /*  557 */ "glMapNamedBuffer",
    /*  558 */ "glMapNamedBufferRange",
    /*  559 */ "glUnmapNamedBuffer",
    /*  560 */ "glFlushMappedNamedBufferRange",
    /*  561 */ "glGetNamedBufferParameteriv",
    /*  562 */ "glGetNamedBufferParameteri64v",
    /*  563 */ "glGetNamedBufferPointerv",
    /*  564 */ "glGetNamedBufferSubData",
    /*  565 */ "glCreateFramebuffers",
    /*  566 */ "glNamedFramebufferRenderbuffer",
    /*  567 */ "glNamedFramebufferParameteri",
    /*  568 */ "glNamedFramebufferTexture",
    /*  569 */ "glNamedFramebufferTextureLayer",
    /*  570 */ "glNamedFramebufferDrawBuffer",
    /*  571 */ "glNamedFramebufferDrawBuffers",
    /*  572 */ "glNamedFramebufferReadBuffer",
    /*  573 */ "glInvalidateNamedFramebufferData",
    /*  574 */ "glInvalidateNamedFramebufferSubData",
    /*  575 */ "glClearNamedFramebufferiv",
    /*  576 */ "glClearNamedFramebufferuiv",
    /*  577 */ "glClearNamedFramebufferfv",
    /*  578 */ "glClearNamedFramebufferfi",
    /*  579 */ "glBlitNamedFramebuffer",
    /*  580 */ "glCheckNamedFramebufferStatus",
    /*  581 */ "glGetNamedFramebufferParameteriv",
    /*  582 */ "glGetNamedFramebufferAttachmentParameteriv",
    /*  583 */ "glCreateRenderbuffers",
    /*  584 */ "glNamedRenderbufferStorage",
    /*  585 */ "glNamedRenderbufferStorageMultisample",
    /*  586 */ "glGetNamedRenderbufferParameteriv",
    /*  587 */ "glCreateTextures",
    /*  588 */ "glTextureBuffer",
    /*  589 */ "glTextureBufferRange",
    /*  590 */ "glTextureStorage1D",
    /*  591 */ "glTextureStorage2D",
    /*  592 */ "glTextureStorage3D",
    /*  593 */ "glTextureStorage2DMultisample",
    /*  594 */ "glTextureStorage3DMultisample",
    /*  595 */ "glTextureSubImage1D",
    /*  596 */ "glTextureSubImage2D",
    /*  597 */ "glTextureSubImage3D",
    /*  598 */ "glCompressedTextureSubImage1D",
    /*  599 */ "glCompressedTextureSubImage2D",
    /*  600 */ "glCompressedTextureSubImage3D",
    /*  601 */ "glCopyTextureSubImage1D",
    /*  602 */ "glCopyTextureSubImage2D",
    /*  603 */ "glCopyTextureSubImage3D",
    /*  604 */ "glTextureParameterf",
    /*  605 */ "glTextureParameterfv",
    /*  606 */ "glTextureParameteri",
    /*  607 */ "glTextureParameterIiv",
    /*  608 */ "glTextureParameterIuiv",
    /*  609 */ "glTextureParameteriv",
    /*  610 */ "glGenerateTextureMipmap",
    /*  611 */ "glBindTextureUnit",
    /*  612 */ "glGetTextureImage",
    /*  613 */ "glGetCompressedTextureImage",
    /*  614 */ "glGetTextureLevelParameterfv",
    /*  615 */ "glGetTextureLevelParameteriv",
    /*  616 */ "glGetTextureParameterfv",
    /*  617 */ "glGetTextureParameterIiv",
    /*  618 */ "glGetTextureParameterIuiv",
    /*  619 */ "glGetTextureParameteriv",
    /*  620 */ "glCreateVertexArrays",
    /*  621 */ "glDisableVertexArrayAttrib",
    /*  622 */ "glEnableVertexArrayAttrib",
    /*  623 */ "glVertexArrayElementBuffer",
    /*  624 */ "glVertexArrayVertexBuffer",
    /*  625 */ "glVertexArrayVertexBuffers",
    /*  626 */ "glVertexArrayAttribBinding",
    /*  627 */ "glVertexArrayAttribFormat",
    /*  628 */ "glVertexArrayAttribIFormat",
    /*  629 */ "glVertexArrayAttribLFormat",
    /*  630 */ "glVertexArrayBindingDivisor",
    /*  631 */ "glGetVertexArrayiv",
    /*  632 */ "glGetVertexArrayIndexediv",
    /*  633 */ "glGetVertexArrayIndexed64iv",
    /*  634 */ "glCreateSamplers",
    /*  635 */ "glCreateProgramPipelines",
    /*  636 */ "glCreateQueries",
    /*  637 */ "glGetQueryBufferObjecti64v",
    /*  638 */ "glGetQueryBufferObjectiv",
    /*  639 */ "glGetQueryBufferObjectui64v",
    /*  640 */ "glGetQueryBufferObjectuiv",
    /*  641 */ "glMemoryBarrierByRegion",
    /*  642 */ "glGetTextureSubImage",
    /*  643 */ "glGetCompressedTextureSubImage",
    /*  644 */ "glGetGraphicsResetStatus",
    /*  645 */ "glGetnCompressedTexImage",
    /*  646 */ "glGetnTexImage",
    /*  647 */ "glGetnUniformdv",
    /*  648 */ "glGetnUniformfv",
    /*  649 */ "glGetnUniformiv",
    /*  650 */ "glGetnUniformuiv",
    /*  651 */ "glReadnPixels",
    /*  652 */ "glTextureBarrier",
    /*  653 */ "glSpecializeShader",
    /*  654 */ "glMultiDrawArraysIndirectCount",
    /*  655 */ "glMultiDrawElementsIndirectCount",
    /*  656 */ "glPolygonOffsetClamp",
    /*  657 */ "glTbufferMask3DFX",
    /*  658 */ "glDebugMessageEnableAMD",
    /*  659 */ "glDebugMessageInsertAMD",
    /*  660 */ "glDebugMessageCallbackAMD",
    /*  661 */ "glGetDebugMessageLogAMD",
    /*  662 */ "glBlendFuncIndexedAMD",
    /*  663 */ "glBlendFuncSeparateIndexedAMD",
    /*  664 */ "glBlendEquationIndexedAMD",
    /*  665 */ "glBlendEquationSeparateIndexedAMD",
    /*  666 */ "glRenderbufferStorageMultisampleAdvancedAMD",
    /*  667 */ "glNamedRenderbufferStorageMultisampleAdvancedAMD",
    /*  668 */ "glFramebufferSamplePositionsfvAMD",
    /*  669 */ "glNamedFramebufferSamplePositionsfvAMD",
    /*  670 */ "glGetFramebufferParameterfvAMD",
    /*  671 */ "glGetNamedFramebufferParameterfvAMD",
    /*  672 */ "glUniform1i64NV",
    /*  673 */ "glUniform2i64NV",
    /*  674 */ "glUniform3i64NV",
    /*  675 */ "glUniform4i64NV",
    /*  676 */ "glUniform1i64vNV",
    /*  677 */ "glUniform2i64vNV",
    /*  678 */ "glUniform3i64vNV",
    /*  679 */ "glUniform4i64vNV",
    /*  680 */ "glUniform1ui64NV",
    /*  681 */ "glUniform2ui64NV",
    /*  682 */ "glUniform3ui64NV",
    /*  683 */ "glUniform4ui64NV",
    /*  684 */ "glUniform1ui64vNV",
    /*  685 */ "glUniform2ui64vNV",
    /*  686 */ "glUniform3ui64vNV",
    /*  687 */ "glUniform4ui64vNV",
    /*  688 */ "glGetUniformi64vNV",
    /*  689 */ "glGetUniformui64vNV",
    /*  690 */ "glProgramUniform1i64NV",
    /*  691 */ "glProgramUniform2i64NV",
    /*  692 */ "glProgramUniform3i64NV",
    /*  693 */ "glProgramUniform4i64NV",
    /*  694 */ "glProgramUniform1i64vNV",
    /*  695 */ "glProgramUniform2i64vNV",
    /*  696 */ "glProgramUniform3i64vNV",
    /*  697 */ "glProgramUniform4i64vNV",
    /*  698 */ "glProgramUniform1ui64NV",
    /*  699 */ "glProgramUniform2ui64NV",
    /*  700 */ "glProgramUniform3ui64NV",
    /*  701 */ "glProgramUniform4ui64NV",
    /*  702 */ "glProgramUniform1ui64vNV",
    /*  703 */ "glProgramUniform2ui64vNV",
    /*  704 */ "glProgramUniform3ui64vNV",
    /*  705 */ "glProgramUniform4ui64vNV",
    /*  706 */ "glVertexAttribParameteriAMD",
    /*  707 */ "glMultiDrawArraysIndirectAMD",
    /*  708 */ "glMultiDrawElementsIndirectAMD",
    /*  709 */ "glGenNamesAMD",
    /*  710 */ "glDeleteNamesAMD",
    /*  711 */ "glIsNameAMD",
    /*  712 */ "glQueryObjectParameteruiAMD",
    /*  713 */ "glGetPerfMonitorGroupsAMD",
    /*  714 */ "glGetPerfMonitorCountersAMD",
    /*  715 */ "glGetPerfMonitorGroupStringAMD",
    /*  716 */ "glGetPerfMonitorCounterStringAMD",
    /*  717 */ "glGetPerfMonitorCounterInfoAMD",
    /*  718 */ "glGenPerfMonitorsAMD",
    /*  719 */ "glDeletePerfMonitorsAMD",
    /*  720 */ "glSelectPerfMonitorCountersAMD",
    /*  721 */ "glBeginPerfMonitorAMD",
    /*  722 */ "glEndPerfMonitorAMD",
    /*  723 */ "glGetPerfMonitorCounterDataAMD",
    /*  724 */ "glSetMultisamplefvAMD",
    /*  725 */ "glTexStorageSparseAMD",
    /*  726 */ "glTextureStorageSparseAMD",
    /*  727 */ "glStencilOpValueAMD",
    /*  728 */ "glTessellationFactorAMD",
    /*  729 */ "glTessellationModeAMD",
    /*  730 */ "glElementPointerAPPLE",
    /*  731 */ "glDrawElementArrayAPPLE",
    /*  732 */ "glDrawRangeElementArrayAPPLE",
    /*  733 */ "glMultiDrawElementArrayAPPLE",
    /*  734 */ "glMultiDrawRangeElementArrayAPPLE",
    /*  735 */ "glGenFencesAPPLE",
    /*  736 */ "glDeleteFencesAPPLE",
    /*  737 */ "glSetFenceAPPLE",
    /*  738 */ "glIsFenceAPPLE",
    /*  739 */ "glTestFenceAPPLE",
    /*  740 */ "glFinishFenceAPPLE",
    /*  741 */ "glTestObjectAPPLE",
    /*  742 */ "glFinishObjectAPPLE",
    /*  743 */ "glBufferParameteriAPPLE",
    /*  744 */ "glFlushMappedBufferRangeAPPLE",
    /*  745 */ "glObjectPurgeableAPPLE",
    /*  746 */ "glObjectUnpurgeableAPPLE",
    /*  747 */ "glGetObjectParameterivAPPLE",
    /*  748 */ "glTextureRangeAPPLE",
    /*  749 */ "glGetTexParameterPointervAPPLE",
    /*  750 */ "glBindVertexArrayAPPLE",
    /*  751 */ "glDeleteVertexArraysAPPLE",
    /*  752 */ "glGenVertexArraysAPPLE",
    /*  753 */ "glIsVertexArrayAPPLE",
    /*  754 */ "glVertexArrayRangeAPPLE",
    /*  755 */ "glFlushVertexArrayRangeAPPLE",
    /*  756 */ "glVertexArrayParameteriAPPLE",
    /*  757 */ "glEnableVertexAttribAPPLE",
    /*  758 */ "glDisableVertexAttribAPPLE",
    /*  759 */ "glIsVertexAttribEnabledAPPLE",
    /*  760 */ "glMapVertexAttrib1dAPPLE",
    /*  761 */ "glMapVertexAttrib1fAPPLE",
    /*  762 */ "glMapVertexAttrib2dAPPLE",
    /*  763 */ "glMapVertexAttrib2fAPPLE",
    /*  764 */ "glPrimitiveBoundingBoxARB",
    /*  765 */ "glGetTextureHandleARB",
    /*  766 */ "glGetTextureSamplerHandleARB",
    /*  767 */ "glMakeTextureHandleResidentARB",
    /*  768 */ "glMakeTextureHandleNonResidentARB",
    /*  769 */ "glGetImageHandleARB",
    /*  770 */ "glMakeImageHandleResidentARB",
    /*  771 */ "glMakeImageHandleNonResidentARB",
    /*  772 */ "glUniformHandleui64ARB",
    /*  773 */ "glUniformHandleui64vARB",
    /*  774 */ "glProgramUniformHandleui64ARB",
    /*  775 */ "glProgramUniformHandleui64vARB",
    /*  776 */ "glIsTextureHandleResidentARB",
    /*  777 */ "glIsImageHandleResidentARB",
    /*  778 */ "glVertexAttribL1ui64ARB",
    /*  779 */ "glVertexAttribL1ui64vARB",
    /*  780 */ "glGetVertexAttribLui64vARB",
    /*  781 */ "glCreateSyncFromCLeventARB",
    /*  782 */ "glClampColorARB",
    /*  783 */ "glDispatchComputeGroupSizeARB",
    /*  784 */ "glDebugMessageControlARB",
    /*  785 */ "glDebugMessageInsertARB",
    /*  786 */ "glDebugMessageCallbackARB",
    /*  787 */ "glGetDebugMessageLogARB",
    /*  788 */ "glDrawBuffersARB",
    /*  789 */ "glBlendEquationiARB",
    /*  790 */ "glBlendEquationSeparateiARB",
    /*  791 */ "glBlendFunciARB",
    /*  792 */ "glBlendFuncSeparateiARB",
    /*  793 */ "glDrawArraysInstancedARB",
    /*  794 */ "glDrawElementsInstancedARB",
    /*  795 */ "glProgramStringARB",
    /*  796 */ "glBindProgramARB",
    /*  797 */ "glDeleteProgramsARB",
    /*  798 */ "glGenProgramsARB",
    /*  799 */ "glProgramEnvParameter4dARB",
    /*  800 */ "glProgramEnvParameter4dvARB",
    /*  801 */ "glProgramEnvParameter4fARB",
    /*  802 */ "glProgramEnvParameter4fvARB",
    /*  803 */ "glProgramLocalParameter4dARB",
    /*  804 */ "glProgramLocalParameter4dvARB",
    /*  805 */ "glProgramLocalParameter4fARB",
    /*  806 */ "glProgramLocalParameter4fvARB",
    /*  807 */ "glGetProgramEnvParameterdvARB",
    /*  808 */ "glGetProgramEnvParameterfvARB",
    /*  809 */ "glGetProgramLocalParameterdvARB",
    /*  810 */ "glGetProgramLocalParameterfvARB",
    /*  811 */ "glGetProgramivARB",
    /*  812 */ "glGetProgramStringARB",
    /*  813 */ "glIsProgramARB",
    /*  814 */ "glProgramParameteriARB",
    /*  815 */ "glFramebufferTextureARB",
    /*  816 */ "glFramebufferTextureLayerARB",
    /*  817 */ "glFramebufferTextureFaceARB",
    /*  818 */ "glSpecializeShaderARB",
    /*  819 */ "glUniform1i64ARB",
    /*  820 */ "glUniform2i64ARB",
    /*  821 */ "glUniform3i64ARB",
    /*  822 */ "glUniform4i64ARB",
    /*  823 */ "glUniform1i64vARB",
    /*  824 */ "glUniform2i64vARB",
    /*  825 */ "glUniform3i64vARB",
    /*  826 */ "glUniform4i64vARB",
    /*  827 */ "glUniform1ui64ARB",
    /*  828 */ "glUniform2ui64ARB",
    /*  829 */ "glUniform3ui64ARB",
    /*  830 */ "glUniform4ui64ARB",
    /*  831 */ "glUniform1ui64vARB",
    /*  832 */ "glUniform2ui64vARB",
    /*  833 */ "glUniform3ui64vARB",
    /*  834 */ "glUniform4ui64vARB",
    /*  835 */ "glGetUniformi64vARB",
    /*  836 */ "glGetUniformui64vARB",
    /*  837 */ "glGetnUniformi64vARB",
    /*  838 */ "glGetnUniformui64vARB",
    /*  839 */ "glProgramUniform1i64ARB",
    /*  840 */ "glProgramUniform2i64ARB",
    /*  841 */ "glProgramUniform3i64ARB",
    /*  842 */ "glProgramUniform4i64ARB",
    /*  843 */ "glProgramUniform1i64vARB",
    /*  844 */ "glProgramUniform2i64vARB",
    /*  845 */ "glProgramUniform3i64vARB",
    /*  846 */ "glProgramUniform4i64vARB",
    /*  847 */ "glProgramUniform1ui64ARB",
    /*  848 */ "glProgramUniform2ui64ARB",
    /*  849 */ "glProgramUniform3ui64ARB",
    /*  850 */ "glProgramUniform4ui64ARB",
    /*  851 */ "glProgramUniform1ui64vARB",
    /*  852 */ "glProgramUniform2ui64vARB",
    /*  853 */ "glProgramUniform3ui64vARB",
    /*  854 */ "glProgramUniform4ui64vARB",
    /*  855 */ "glMultiDrawArraysIndirectCountARB",
    /*  856 */ "glMultiDrawElementsIndirectCountARB",
    /*  857 */ "glVertexAttribDivisorARB",
    /*  858 */ "glCurrentPaletteMatrixARB",
    /*  859 */ "glMatrixIndexubvARB",
    /*  860 */ "glMatrixIndexusvARB",
    /*  861 */ "glMatrixIndexuivARB",
    /*  862 */ "glMatrixIndexPointerARB",
    /*  863 */ "glSampleCoverageARB",
    /*  864 */ "glActiveTextureARB",
    /*  865 */ "glClientActiveTextureARB",
    /*  866 */ "glMultiTexCoord1dARB",
    /*  867 */ "glMultiTexCoord1dvARB",
    /*  868 */ "glMultiTexCoord1fARB",
    /*  869 */ "glMultiTexCoord1fvARB",
    /*  870 */ "glMultiTexCoord1iARB",
    /*  871 */ "glMultiTexCoord1ivARB",
    /*  872 */ "glMultiTexCoord1sARB",
    /*  873 */ "glMultiTexCoord1svARB",
    /*  874 */ "glMultiTexCoord2dARB",
    /*  875 */ "glMultiTexCoord2dvARB",
    /*  876 */ "glMultiTexCoord2fARB",
    /*  877 */ "glMultiTexCoord2fvARB",
    /*  878 */ "glMultiTexCoord2iARB",
    /*  879 */ "glMultiTexCoord2ivARB",
    /*  880 */ "glMultiTexCoord2sARB",
    /*  881 */ "glMultiTexCoord2svARB",
    /*  882 */ "glMultiTexCoord3dARB",
    /*  883 */ "glMultiTexCoord3dvARB",
    /*  884 */ "glMultiTexCoord3fARB",
    /*  885 */ "glMultiTexCoord3fvARB",
    /*  886 */ "glMultiTexCoord3iARB",
    /*  887 */ "glMultiTexCoord3ivARB",
    /*  888 */ "glMultiTexCoord3sARB",
    /*  889 */ "glMultiTexCoord3svARB",
    /*  890 */ "glMultiTexCoord4dARB",
    /*  891 */ "glMultiTexCoord4dvARB",
    /*  892 */ "glMultiTexCoord4fARB",
    /*  893 */ "glMultiTexCoord4fvARB",
    /*  894 */ "glMultiTexCoord4iARB",
    /*  895 */ "glMultiTexCoord4ivARB",
    /*  896 */ "glMultiTexCoord4sARB",
    /*  897 */ "glMultiTexCoord4svARB",
    /*  898 */ "glGenQueriesARB",
    /*  899 */ "glDeleteQueriesARB",
    /*  900 */ "glIsQueryARB",
    /*  901 */ "glBeginQueryARB",
    /*  902 */ "glEndQueryARB",
    /*  903 */ "glGetQueryivARB",
    /*  904 */ "glGetQueryObjectivARB",
    /*  905 */ "glGetQueryObjectuivARB",
    /*  906 */ "glMaxShaderCompilerThreadsARB",
    /*  907 */ "glPointParameterfARB",
    /*  908 */ "glPointParameterfvARB",
    /*  909 */ "glGetGraphicsResetStatusARB",
    /*  910 */ "glGetnTexImageARB",
    /*  911 */ "glReadnPixelsARB",
    /*  912 */ "glGetnCompressedTexImageARB",
    /*  913 */ "glGetnUniformfvARB",
    /*  914 */ "glGetnUniformivARB",
    /*  915 */ "glGetnUniformuivARB",
    /*  916 */ "glGetnUniformdvARB",
    /*  917 */ "glFramebufferSampleLocationsfvARB",
    /*  918 */ "glNamedFramebufferSampleLocationsfvARB",
    /*  919 */ "glEvaluateDepthValuesARB",
    /*  920 */ "glMinSampleShadingARB",
    /*  921 */ "glDeleteObjectARB",
    /*  922 */ "glGetHandleARB",
    /*  923 */ "glDetachObjectARB",
    /*  924 */ "glCreateShaderObjectARB",
    /*  925 */ "glShaderSourceARB",
    /*  926 */ "glCompileShaderARB",
    /*  927 */ "glCreateProgramObjectARB",
    /*  928 */ "glAttachObjectARB",
    /*  929 */ "glLinkProgramARB",
    /*  930 */ "glUseProgramObjectARB",
    /*  931 */ "glValidateProgramARB",
    /*  932 */ "glUniform1fARB",
    /*  933 */ "glUniform2fARB",
    /*  934 */ "glUniform3fARB",
    /*  935 */ "glUniform4fARB",
    /*  936 */ "glUniform1iARB",
    /*  937 */ "glUniform2iARB",
    /*  938 */ "glUniform3iARB",
    /*  939 */ "glUniform4iARB",
    /*  940 */ "glUniform1fvARB",
    /*  941 */ "glUniform2fvARB",
    /*  942 */ "glUniform3fvARB",
    /*  943 */ "glUniform4fvARB",
    /*  944 */ "glUniform1ivARB",
    /*  945 */ "glUniform2ivARB",
    /*  946 */ "glUniform3ivARB",
    /*  947 */ "glUniform4ivARB",
    /*  948 */ "glUniformMatrix2fvARB",
    /*  949 */ "glUniformMatrix3fvARB",
    /*  950 */ "glUniformMatrix4fvARB",
    /*  951 */ "glGetObjectParameterfvARB",
    /*  952 */ "glGetObjectParameterivARB",
    /*  953 */ "glGetInfoLogARB",
    /*  954 */ "glGetAttachedObjectsARB",
    /*  955 */ "glGetUniformLocationARB",
    /*  956 */ "glGetActiveUniformARB",
    /*  957 */ "glGetUniformfvARB",
    /*  958 */ "glGetUniformivARB",
    /*  959 */ "glGetShaderSourceARB",
    /*  960 */ "glNamedStringARB",
    /*  961 */ "glDeleteNamedStringARB",
    /*  962 */ "glCompileShaderIncludeARB",
    /*  963 */ "glIsNamedStringARB",
    /*  964 */ "glGetNamedStringARB",
    /*  965 */ "glGetNamedStringivARB",
    /*  966 */ "glBufferPageCommitmentARB",
    /*  967 */ "glNamedBufferPageCommitmentEXT",
    /*  968 */ "glNamedBufferPageCommitmentARB",
    /*  969 */ "glTexPageCommitmentARB",
    /*  970 */ "glTexBufferARB",
    /*  971 */ "glCompressedTexImage3DARB",
    /*  972 */ "glCompressedTexImage2DARB",
    /*  973 */ "glCompressedTexImage1DARB",
    /*  974 */ "glCompressedTexSubImage3DARB",
    /*  975 */ "glCompressedTexSubImage2DARB",
    /*  976 */ "glCompressedTexSubImage1DARB",
    /*  977 */ "glGetCompressedTexImageARB",
    /*  978 */ "glLoadTransposeMatrixfARB",
    /*  979 */ "glLoadTransposeMatrixdARB",
    /*  980 */ "glMultTransposeMatrixfARB",
    /*  981 */ "glMultTransposeMatrixdARB",
    /*  982 */ "glWeightbvARB",
    /*  983 */ "glWeightsvARB",
    /*  984 */ "glWeightivARB",
    /*  985 */ "glWeightfvARB",
    /*  986 */ "glWeightdvARB",
    /*  987 */ "glWeightubvARB",
    /*  988 */ "glWeightusvARB",
    /*  989 */ "glWeightuivARB",
    /*  990 */ "glWeightPointerARB",
    /*  991 */ "glVertexBlendARB",
    /*  992 */ "glBindBufferARB",
    /*  993 */ "glDeleteBuffersARB",
    /*  994 */ "glGenBuffersARB",
    /*  995 */ "glIsBufferARB",
    /*  996 */ "glBufferDataARB",
    /*  997 */ "glBufferSubDataARB",
    /*  998 */ "glGetBufferSubDataARB",
    /*  999 */ "glMapBufferARB",
    /* 1000 */ "glUnmapBufferARB",
    /* 1001 */ "glGetBufferParameterivARB",
    /* 1002 */ "glGetBufferPointervARB",
    /* 1003 */ "glVertexAttrib1dARB",
    /* 1004 */ "glVertexAttrib1dvARB",
    /* 1005 */ "glVertexAttrib1fARB",
    /* 1006 */ "glVertexAttrib1fvARB",
    /* 1007 */ "glVertexAttrib1sARB",
    /* 1008 */ "glVertexAttrib1svARB",
    /* 1009 */ "glVertexAttrib2dARB",
    /* 1010 */ "glVertexAttrib2dvARB",
    /* 1011 */ "glVertexAttrib2fARB",
    /* 1012 */ "glVertexAttrib2fvARB",
    /* 1013 */ "glVertexAttrib2sARB",
    /* 1014 */ "glVertexAttrib2svARB",
    /* 1015 */ "glVertexAttrib3dARB",
    /* 1016 */ "glVertexAttrib3dvARB",
    /* 1017 */ "glVertexAttrib3fARB",
    /* 1018 */ "glVertexAttrib3fvARB",
    /* 1019 */ "glVertexAttrib3sARB",
    /* 1020 */ "glVertexAttrib3svARB",
    /* 1021 */ "glVertexAttrib4NbvARB",
    /* 1022 */ "glVertexAttrib4NivARB",
    /* 1023 */ "glVertexAttrib4NsvARB",
    /* 1024 */ "glVertexAttrib4NubARB",
    /* 1025 */ "glVertexAttrib4NubvARB",
    /* 1026 */ "glVertexAttrib4NuivARB",
    /* 1027 */ "glVertexAttrib4NusvARB",
    /* 1028 */ "glVertexAttrib4bvARB",
    /* 1029 */ "glVertexAttrib4dARB",
    /* 1030 */ "glVertexAttrib4dvARB",
    /* 1031 */ "glVertexAttrib4fARB",
    /* 1032 */ "glVertexAttrib4fvARB",
    /* 1033 */ "glVertexAttrib4ivARB",
    /* 1034 */ "glVertexAttrib4sARB",
    /* 1035 */ "glVertexAttrib4svARB",
    /* 1036 */ "glVertexAttrib4ubvARB",
    /* 1037 */ "glVertexAttrib4uivARB",
    /* 1038 */ "glVertexAttrib4usvARB",
    /* 1039 */ "glVertexAttribPointerARB",
    /* 1040 */ "glEnableVertexAttribArrayARB",
    /* 1041 */ "glDisableVertexAttribArrayARB",
    /* 1042 */ "glGetVertexAttribdvARB",
    /* 1043 */ "glGetVertexAttribfvARB",
    /* 1044 */ "glGetVertexAttribivARB",
    /* 1045 */ "glGetVertexAttribPointervARB",
    /* 1046 */ "glBindAttribLocationARB",
    /* 1047 */ "glGetActiveAttribARB",
    /* 1048 */ "glGetAttribLocationARB",
    /* 1049 */ "glDepthRangeArraydvNV",
    /* 1050 */ "glDepthRangeIndexeddNV",
    /* 1051 */ "glWindowPos2dARB",
    /* 1052 */ "glWindowPos2dvARB",
    /* 1053 */ "glWindowPos2fARB",
    /* 1054 */ "glWindowPos2fvARB",
    /* 1055 */ "glWindowPos2iARB",
    /* 1056 */ "glWindowPos2ivARB",
    /* 1057 */ "glWindowPos2sARB",
    /* 1058 */ "glWindowPos2svARB",
    /* 1059 */ "glWindowPos3dARB",
    /* 1060 */ "glWindowPos3dvARB",
    /* 1061 */ "glWindowPos3fARB",
    /* 1062 */ "glWindowPos3fvARB",
    /* 1063 */ "glWindowPos3iARB",
    /* 1064 */ "glWindowPos3ivARB",
    /* 1065 */ "glWindowPos3sARB",
    /* 1066 */ "glWindowPos3svARB",
    /* 1067 */ "glDrawBuffersATI",
    /* 1068 */ "glElementPointerATI",
    /* 1069 */ "glDrawElementArrayATI",
    /* 1070 */ "glDrawRangeElementArrayATI",
    /* 1071 */ "glTexBumpParameterivATI",
    /* 1072 */ "glTexBumpParameterfvATI",
    /* 1073 */ "glGetTexBumpParameterivATI",
    /* 1074 */ "glGetTexBumpParameterfvATI",
    /* 1075 */ "glGenFragmentShadersATI",
    /* 1076 */ "glBindFragmentShaderATI",
    /* 1077 */ "glDeleteFragmentShaderATI",
    /* 1078 */ "glBeginFragmentShaderATI",
    /* 1079 */ "glEndFragmentShaderATI",
    /* 1080 */ "glPassTexCoordATI",
    /* 1081 */ "glSampleMapATI",
    /* 1082 */ "glColorFragmentOp1ATI",
    /* 1083 */ "glColorFragmentOp2ATI",
    /* 1084 */ "glColorFragmentOp3ATI",
    /* 1085 */ "glAlphaFragmentOp1ATI",
    /* 1086 */ "glAlphaFragmentOp2ATI",
    /* 1087 */ "glAlphaFragmentOp3ATI",
    /* 1088 */ "glSetFragmentShaderConstantATI",
    /* 1089 */ "glMapObjectBufferATI",
    /* 1090 */ "glUnmapObjectBufferATI",
    /* 1091 */ "glPNTrianglesiATI",
    /* 1092 */ "glPNTrianglesfATI",
    /* 1093 */ "glStencilOpSeparateATI",
    /* 1094 */ "glStencilFuncSeparateATI",
    /* 1095 */ "glNewObjectBufferATI",
    /* 1096 */ "glIsObjectBufferATI",
    /* 1097 */ "glUpdateObjectBufferATI",
    /* 1098 */ "glGetObjectBufferfvATI",
    /* 1099 */ "glGetObjectBufferivATI",
    /* 1100 */ "glFreeObjectBufferATI",
    /* 1101 */ "glArrayObjectATI",
    /* 1102 */ "glGetArrayObjectfvATI",
    /* 1103 */ "glGetArrayObjectivATI",
    /* 1104 */ "glVariantArrayObjectATI",
    /* 1105 */ "glGetVariantArrayObjectfvATI",
    /* 1106 */ "glGetVariantArrayObjectivATI",
    /* 1107 */ "glVertexAttribArrayObjectATI",
    /* 1108 */ "glGetVertexAttribArrayObjectfvATI",
    /* 1109 */ "glGetVertexAttribArrayObjectivATI",
    /* 1110 */ "glVertexStream1sATI",
    /* 1111 */ "glVertexStream1svATI",
    /* 1112 */ "glVertexStream1iATI",
    /* 1113 */ "glVertexStream1ivATI",
    /* 1114 */ "glVertexStream1fATI",
    /* 1115 */ "glVertexStream1fvATI",
    /* 1116 */ "glVertexStream1dATI",
    /* 1117 */ "glVertexStream1dvATI",
    /* 1118 */ "glVertexStream2sATI",
    /* 1119 */ "glVertexStream2svATI",
    /* 1120 */ "glVertexStream2iATI",
    /* 1121 */ "glVertexStream2ivATI",
    /* 1122 */ "glVertexStream2fATI",
    /* 1123 */ "glVertexStream2fvATI",
    /* 1124 */ "glVertexStream2dATI",
    /* 1125 */ "glVertexStream2dvATI",
    /* 1126 */ "glVertexStream3sATI",
    /* 1127 */ "glVertexStream3svATI",
    /* 1128 */ "glVertexStream3iATI",
    /* 1129 */ "glVertexStream3ivATI",
    /* 1130 */ "glVertexStream3fATI",
    /* 1131 */ "glVertexStream3fvATI",
    /* 1132 */ "glVertexStream3dATI",
    /* 1133 */ "glVertexStream3dvATI",
    /* 1134 */ "glVertexStream4sATI",
    /* 1135 */ "glVertexStream4svATI",
    /* 1136 */ "glVertexStream4iATI",
    /* 1137 */ "glVertexStream4ivATI",
    /* 1138 */ "glVertexStream4fATI",
    /* 1139 */ "glVertexStream4fvATI",
    /* 1140 */ "glVertexStream4dATI",
    /* 1141 */ "glVertexStream4dvATI",
    /* 1142 */ "glNormalStream3bATI",
    /* 1143 */ "glNormalStream3bvATI",
    /* 1144 */ "glNormalStream3sATI",
    /* 1145 */ "glNormalStream3svATI",
    /* 1146 */ "glNormalStream3iATI",
    /* 1147 */ "glNormalStream3ivATI",
    /* 1148 */ "glNormalStream3fATI",
    /* 1149 */ "glNormalStream3fvATI",
    /* 1150 */ "glNormalStream3dATI",
    /* 1151 */ "glNormalStream3dvATI",
    /* 1152 */ "glClientActiveVertexStreamATI",
    /* 1153 */ "glVertexBlendEnviATI",
    /* 1154 */ "glVertexBlendEnvfATI",
    /* 1155 */ "glEGLImageTargetTexStorageEXT",
    /* 1156 */ "glEGLImageTargetTextureStorageEXT",
    /* 1157 */ "glUniformBufferEXT",
    /* 1158 */ "glGetUniformBufferSizeEXT",
    /* 1159 */ "glGetUniformOffsetEXT",
    /* 1160 */ "glBlendColorEXT",
    /* 1161 */ "glBlendEquationSeparateEXT",
    /* 1162 */ "glBindFragDataLocationEXT",
    /* 1163 */ "glBlendFuncSeparateEXT",
    /* 1164 */ "glBlendEquationEXT",
    /* 1165 */ "glColorSubTableEXT",
    /* 1166 */ "glCopyColorSubTableEXT",
    /* 1167 */ "glLockArraysEXT",
    /* 1168 */ "glUnlockArraysEXT",
    /* 1169 */ "glConvolutionFilter1DEXT",
    /* 1170 */ "glConvolutionFilter2DEXT",
    /* 1171 */ "glConvolutionParameterfEXT",
    /* 1172 */ "glConvolutionParameterfvEXT",
    /* 1173 */ "glConvolutionParameteriEXT",
    /* 1174 */ "glConvolutionParameterivEXT",
    /* 1175 */ "glCopyConvolutionFilter1DEXT",
    /* 1176 */ "glCopyConvolutionFilter2DEXT",
    /* 1177 */ "glGetConvolutionFilterEXT",
    /* 1178 */ "glGetConvolutionParameterfvEXT",
    /* 1179 */ "glGetConvolutionParameterivEXT",
    /* 1180 */ "glGetSeparableFilterEXT",
    /* 1181 */ "glSeparableFilter2DEXT",
    /* 1182 */ "glTangent3bEXT",
    /* 1183 */ "glTangent3bvEXT",
    /* 1184 */ "glTangent3dEXT",
    /* 1185 */ "glTangent3dvEXT",
    /* 1186 */ "glTangent3fEXT",
    /* 1187 */ "glTangent3fvEXT",
    /* 1188 */ "glTangent3iEXT",
    /* 1189 */ "glTangent3ivEXT",
    /* 1190 */ "glTangent3sEXT",
    /* 1191 */ "glTangent3svEXT",
    /* 1192 */ "glBinormal3bEXT",
    /* 1193 */ "glBinormal3bvEXT",
    /* 1194 */ "glBinormal3dEXT",
    /* 1195 */ "glBinormal3dvEXT",
    /* 1196 */ "glBinormal3fEXT",
    /* 1197 */ "glBinormal3fvEXT",
    /* 1198 */ "glBinormal3iEXT",
    /* 1199 */ "glBinormal3ivEXT",
    /* 1200 */ "glBinormal3sEXT",
    /* 1201 */ "glBinormal3svEXT",
    /* 1202 */ "glTangentPointerEXT",
    /* 1203 */ "glBinormalPointerEXT",
    /* 1204 */ "glCopyTexImage1DEXT",
    /* 1205 */ "glCopyTexImage2DEXT",
    /* 1206 */ "glCopyTexSubImage1DEXT",
    /* 1207 */ "glCopyTexSubImage2DEXT",
    /* 1208 */ "glCopyTexSubImage3DEXT",
    /* 1209 */ "glCullParameterdvEXT",
    /* 1210 */ "glCullParameterfvEXT",
    /* 1211 */ "glLabelObjectEXT",
    /* 1212 */ "glGetObjectLabelEXT",
    /* 1213 */ "glInsertEventMarkerEXT",
    /* 1214 */ "glPushGroupMarkerEXT",
    /* 1215 */ "glPopGroupMarkerEXT",
    /* 1216 */ "glDepthBoundsEXT",
    /* 1217 */ "glMatrixLoadfEXT",
    /* 1218 */ "glMatrixLoaddEXT",
    /* 1219 */ "glMatrixMultfEXT",
    /* 1220 */ "glMatrixMultdEXT",
    /* 1221 */ "glMatrixLoadIdentityEXT",
    /* 1222 */ "glMatrixRotatefEXT",
    /* 1223 */ "glMatrixRotatedEXT",
    /* 1224 */ "glMatrixScalefEXT",
    /* 1225 */ "glMatrixScaledEXT",
    /* 1226 */ "glMatrixTranslatefEXT",
    /* 1227 */ "glMatrixTranslatedEXT",
    /* 1228 */ "glMatrixFrustumEXT",
    /* 1229 */ "glMatrixOrthoEXT",
    /* 1230 */ "glMatrixPopEXT",
    /* 1231 */ "glMatrixPushEXT",
    /* 1232 */ "glClientAttribDefaultEXT",
    /* 1233 */ "glPushClientAttribDefaultEXT",
    /* 1234 */ "glTextureParameterfEXT",
    /* 1235 */ "glTextureParameterfvEXT",
    /* 1236 */ "glTextureParameteriEXT",
    /* 1237 */ "glTextureParameterivEXT",
    /* 1238 */ "glTextureImage1DEXT",
    /* 1239 */ "glTextureImage2DEXT",
    /* 1240 */ "glTextureSubImage1DEXT",
    /* 1241 */ "glTextureSubImage2DEXT",
    /* 1242 */ "glCopyTextureImage1DEXT",
    /* 1243 */ "glCopyTextureImage2DEXT",
    /* 1244 */ "glCopyTextureSubImage1DEXT",
    /* 1245 */ "glCopyTextureSubImage2DEXT",
    /* 1246 */ "glGetTextureImageEXT",
    /* 1247 */ "glGetTextureParameterfvEXT",
    /* 1248 */ "glGetTextureParameterivEXT",
    /* 1249 */ "glGetTextureLevelParameterfvEXT",
    /* 1250 */ "glGetTextureLevelParameterivEXT",
    /* 1251 */ "glTextureImage3DEXT",
    /* 1252 */ "glTextureSubImage3DEXT",
    /* 1253 */ "glCopyTextureSubImage3DEXT",
    /* 1254 */ "glBindMultiTextureEXT",
    /* 1255 */ "glMultiTexCoordPointerEXT",
    /* 1256 */ "glMultiTexEnvfEXT",
    /* 1257 */ "glMultiTexEnvfvEXT",
    /* 1258 */ "glMultiTexEnviEXT",
    /* 1259 */ "glMultiTexEnvivEXT",
    /* 1260 */ "glMultiTexGendEXT",
    /* 1261 */ "glMultiTexGendvEXT",
    /* 1262 */ "glMultiTexGenfEXT",
    /* 1263 */ "glMultiTexGenfvEXT",
    /* 1264 */ "glMultiTexGeniEXT",
    /* 1265 */ "glMultiTexGenivEXT",
    /* 1266 */ "glGetMultiTexEnvfvEXT",
    /* 1267 */ "glGetMultiTexEnvivEXT",
    /* 1268 */ "glGetMultiTexGendvEXT",
    /* 1269 */ "glGetMultiTexGenfvEXT",
    /* 1270 */ "glGetMultiTexGenivEXT",
    /* 1271 */ "glMultiTexParameteriEXT",
    /* 1272 */ "glMultiTexParameterivEXT",
    /* 1273 */ "glMultiTexParameterfEXT",
    /* 1274 */ "glMultiTexParameterfvEXT",
    /* 1275 */ "glMultiTexImage1DEXT",
    /* 1276 */ "glMultiTexImage2DEXT",
    /* 1277 */ "glMultiTexSubImage1DEXT",
    /* 1278 */ "glMultiTexSubImage2DEXT",
    /* 1279 */ "glCopyMultiTexImage1DEXT",
    /* 1280 */ "glCopyMultiTexImage2DEXT",
    /* 1281 */ "glCopyMultiTexSubImage1DEXT",
    /* 1282 */ "glCopyMultiTexSubImage2DEXT",
    /* 1283 */ "glGetMultiTexImageEXT",
    /* 1284 */ "glGetMultiTexParameterfvEXT",
    /* 1285 */ "glGetMultiTexParameterivEXT",
    /* 1286 */ "glGetMultiTexLevelParameterfvEXT",
    /* 1287 */ "glGetMultiTexLevelParameterivEXT",
    /* 1288 */ "glMultiTexImage3DEXT",
    /* 1289 */ "glMultiTexSubImage3DEXT",
    /* 1290 */ "glCopyMultiTexSubImage3DEXT",
    /* 1291 */ "glEnableClientStateIndexedEXT",
    /* 1292 */ "glDisableClientStateIndexedEXT",
    /* 1293 */ "glGetFloatIndexedvEXT",
    /* 1294 */ "glGetDoubleIndexedvEXT",
    /* 1295 */ "glGetPointerIndexedvEXT",
    /* 1296 */ "glEnableIndexedEXT",
    /* 1297 */ "glDisableIndexedEXT",
    /* 1298 */ "glIsEnabledIndexedEXT",
    /* 1299 */ "glGetIntegerIndexedvEXT",
    /* 1300 */ "glGetBooleanIndexedvEXT",
    /* 1301 */ "glCompressedTextureImage3DEXT",
    /* 1302 */ "glCompressedTextureImage2DEXT",
    /* 1303 */ "glCompressedTextureImage1DEXT",
    /* 1304 */ "glCompressedTextureSubImage3DEXT",
    /* 1305 */ "glCompressedTextureSubImage2DEXT",
    /* 1306 */ "glCompressedTextureSubImage1DEXT",
    /* 1307 */ "glGetCompressedTextureImageEXT",
    /* 1308 */ "glCompressedMultiTexImage3DEXT",
    /* 1309 */ "glCompressedMultiTexImage2DEXT",
    /* 1310 */ "glCompressedMultiTexImage1DEXT",
    /* 1311 */ "glCompressedMultiTexSubImage3DEXT",
    /* 1312 */ "glCompressedMultiTexSubImage2DEXT",
    /* 1313 */ "glCompressedMultiTexSubImage1DEXT",
    /* 1314 */ "glGetCompressedMultiTexImageEXT",
    /* 1315 */ "glMatrixLoadTransposefEXT",
    /* 1316 */ "glMatrixLoadTransposedEXT",
    /* 1317 */ "glMatrixMultTransposefEXT",
    /* 1318 */ "glMatrixMultTransposedEXT",
    /* 1319 */ "glNamedBufferDataEXT",
    /* 1320 */ "glNamedBufferSubDataEXT",
    /* 1321 */ "glMapNamedBufferEXT",
    /* 1322 */ "glUnmapNamedBufferEXT",
    /* 1323 */ "glGetNamedBufferParameterivEXT",
    /* 1324 */ "glGetNamedBufferPointervEXT",
    /* 1325 */ "glGetNamedBufferSubDataEXT",
    /* 1326 */ "glProgramUniform1fEXT",
    /* 1327 */ "glProgramUniform2fEXT",
    /* 1328 */ "glProgramUniform3fEXT",
    /* 1329 */ "glProgramUniform4fEXT",
    /* 1330 */ "glProgramUniform1iEXT",
    /* 1331 */ "glProgramUniform2iEXT",
    /* 1332 */ "glProgramUniform3iEXT",
    /* 1333 */ "glProgramUniform4iEXT",
    /* 1334 */ "glProgramUniform1fvEXT",
    /* 1335 */ "glProgramUniform2fvEXT",
    /* 1336 */ "glProgramUniform3fvEXT",
    /* 1337 */ "glProgramUniform4fvEXT",
    /* 1338 */ "glProgramUniform1ivEXT",
    /* 1339 */ "glProgramUniform2ivEXT",
    /* 1340 */ "glProgramUniform3ivEXT",
    /* 1341 */ "glProgramUniform4ivEXT",
    /* 1342 */ "glProgramUniformMatrix2fvEXT",
    /* 1343 */ "glProgramUniformMatrix3fvEXT",
    /* 1344 */ "glProgramUniformMatrix4fvEXT",
    /* 1345 */ "glProgramUniformMatrix2x3fvEXT",
    /* 1346 */ "glProgramUniformMatrix3x2fvEXT",
    /* 1347 */ "glProgramUniformMatrix2x4fvEXT",
    /* 1348 */ "glProgramUniformMatrix4x2fvEXT",
    /* 1349 */ "glProgramUniformMatrix3x4fvEXT",
    /* 1350 */ "glProgramUniformMatrix4x3fvEXT",
    /* 1351 */ "glTextureBufferEXT",
    /* 1352 */ "glMultiTexBufferEXT",
    /* 1353 */ "glTextureParameterIivEXT",
    /* 1354 */ "glTextureParameterIuivEXT",
    /* 1355 */ "glGetTextureParameterIivEXT",
    /* 1356 */ "glGetTextureParameterIuivEXT",
    /* 1357 */ "glMultiTexParameterIivEXT",
    /* 1358 */ "glMultiTexParameterIuivEXT",
    /* 1359 */ "glGetMultiTexParameterIivEXT",
    /* 1360 */ "glGetMultiTexParameterIuivEXT",
    /* 1361 */ "glProgramUniform1uiEXT",
    /* 1362 */ "glProgramUniform2uiEXT",
    /* 1363 */ "glProgramUniform3uiEXT",
    /* 1364 */ "glProgramUniform4uiEXT",
    /* 1365 */ "glProgramUniform1uivEXT",
    /* 1366 */ "glProgramUniform2uivEXT",
    /* 1367 */ "glProgramUniform3uivEXT",
    /* 1368 */ "glProgramUniform4uivEXT",
    /* 1369 */ "glNamedProgramLocalParameters4fvEXT",
    /* 1370 */ "glNamedProgramLocalParameterI4iEXT",
    /* 1371 */ "glNamedProgramLocalParameterI4ivEXT",
    /* 1372 */ "glNamedProgramLocalParametersI4ivEXT",
    /* 1373 */ "glNamedProgramLocalParameterI4uiEXT",
    /* 1374 */ "glNamedProgramLocalParameterI4uivEXT",
    /* 1375 */ "glNamedProgramLocalParametersI4uivEXT",
    /* 1376 */ "glGetNamedProgramLocalParameterIivEXT",
    /* 1377 */ "glGetNamedProgramLocalParameterIuivEXT",
    /* 1378 */ "glEnableClientStateiEXT",
    /* 1379 */ "glDisableClientStateiEXT",
    /* 1380 */ "glGetFloati_vEXT",
    /* 1381 */ "glGetDoublei_vEXT",
    /* 1382 */ "glGetPointeri_vEXT",
    /* 1383 */ "glNamedProgramStringEXT",
    /* 1384 */ "glNamedProgramLocalParameter4dEXT",
    /* 1385 */ "glNamedProgramLocalParameter4dvEXT",
    /* 1386 */ "glNamedProgramLocalParameter4fEXT",
    /* 1387 */ "glNamedProgramLocalParameter4fvEXT",
    /* 1388 */ "glGetNamedProgramLocalParameterdvEXT",
    /* 1389 */ "glGetNamedProgramLocalParameterfvEXT",
    /* 1390 */ "glGetNamedProgramivEXT",
    /* 1391 */ "glGetNamedProgramStringEXT",
    /* 1392 */ "glNamedRenderbufferStorageEXT",
    /* 1393 */ "glGetNamedRenderbufferParameterivEXT",
    /* 1394 */ "glNamedRenderbufferStorageMultisampleEXT",
    /* 1395 */ "glNamedRenderbufferStorageMultisampleCoverageEXT",
    /* 1396 */ "glCheckNamedFramebufferStatusEXT",
    /* 1397 */ "glNamedFramebufferTexture1DEXT",
    /* 1398 */ "glNamedFramebufferTexture2DEXT",
    /* 1399 */ "glNamedFramebufferTexture3DEXT",
    /* 1400 */ "glNamedFramebufferRenderbufferEXT",
    /* 1401 */ "glGetNamedFramebufferAttachmentParameterivEXT",
    /* 1402 */ "glGenerateTextureMipmapEXT",
    /* 1403 */ "glGenerateMultiTexMipmapEXT",
    /* 1404 */ "glFramebufferDrawBufferEXT",
    /* 1405 */ "glFramebufferDrawBuffersEXT",
    /* 1406 */ "glFramebufferReadBufferEXT",
    /* 1407 */ "glGetFramebufferParameterivEXT",
    /* 1408 */ "glNamedCopyBufferSubDataEXT",
    /* 1409 */ "glNamedFramebufferTextureEXT",
    /* 1410 */ "glNamedFramebufferTextureLayerEXT",
    /* 1411 */ "glNamedFramebufferTextureFaceEXT",
    /* 1412 */ "glTextureRenderbufferEXT",
    /* 1413 */ "glMultiTexRenderbufferEXT",
    /* 1414 */ "glVertexArrayVertexOffsetEXT",
    /* 1415 */ "glVertexArrayColorOffsetEXT",
    /* 1416 */ "glVertexArrayEdgeFlagOffsetEXT",
    /* 1417 */ "glVertexArrayIndexOffsetEXT",
    /* 1418 */ "glVertexArrayNormalOffsetEXT",
    /* 1419 */ "glVertexArrayTexCoordOffsetEXT",
    /* 1420 */ "glVertexArrayMultiTexCoordOffsetEXT",
    /* 1421 */ "glVertexArrayFogCoordOffsetEXT",
    /* 1422 */ "glVertexArraySecondaryColorOffsetEXT",
    /* 1423 */ "glVertexArrayVertexAttribOffsetEXT",
    /* 1424 */ "glVertexArrayVertexAttribIOffsetEXT",
    /* 1425 */ "glEnableVertexArrayEXT",
    /* 1426 */ "glDisableVertexArrayEXT",
    /* 1427 */ "glEnableVertexArrayAttribEXT",
    /* 1428 */ "glDisableVertexArrayAttribEXT",
    /* 1429 */ "glGetVertexArrayIntegervEXT",
    /* 1430 */ "glGetVertexArrayPointervEXT",
    /* 1431 */ "glGetVertexArrayIntegeri_vEXT",
    /* 1432 */ "glGetVertexArrayPointeri_vEXT",
    /* 1433 */ "glMapNamedBufferRangeEXT",
    /* 1434 */ "glFlushMappedNamedBufferRangeEXT",
    /* 1435 */ "glNamedBufferStorageEXT",
    /* 1436 */ "glClearNamedBufferDataEXT",
    /* 1437 */ "glClearNamedBufferSubDataEXT",
    /* 1438 */ "glNamedFramebufferParameteriEXT",
    /* 1439 */ "glGetNamedFramebufferParameterivEXT",
    /* 1440 */ "glProgramUniform1dEXT",
    /* 1441 */ "glProgramUniform2dEXT",
    /* 1442 */ "glProgramUniform3dEXT",
    /* 1443 */ "glProgramUniform4dEXT",
    /* 1444 */ "glProgramUniform1dvEXT",
    /* 1445 */ "glProgramUniform2dvEXT",
    /* 1446 */ "glProgramUniform3dvEXT",
    /* 1447 */ "glProgramUniform4dvEXT",
    /* 1448 */ "glProgramUniformMatrix2dvEXT",
    /* 1449 */ "glProgramUniformMatrix3dvEXT",
    /* 1450 */ "glProgramUniformMatrix4dvEXT",
    /* 1451 */ "glProgramUniformMatrix2x3dvEXT",
    /* 1452 */ "glProgramUniformMatrix2x4dvEXT",
    /* 1453 */ "glProgramUniformMatrix3x2dvEXT",
    /* 1454 */ "glProgramUniformMatrix3x4dvEXT",
    /* 1455 */ "glProgramUniformMatrix4x2dvEXT",
    /* 1456 */ "glProgramUniformMatrix4x3dvEXT",
    /* 1457 */ "glTextureBufferRangeEXT",
    /* 1458 */ "glTextureStorage1DEXT",
    /* 1459 */ "glTextureStorage2DEXT",
    /* 1460 */ "glTextureStorage3DEXT",
    /* 1461 */ "glTextureStorage2DMultisampleEXT",
    /* 1462 */ "glTextureStorage3DMultisampleEXT",
    /* 1463 */ "glVertexArrayBindVertexBufferEXT",
    /* 1464 */ "glVertexArrayVertexAttribFormatEXT",
    /* 1465 */ "glVertexArrayVertexAttribIFormatEXT",
    /* 1466 */ "glVertexArrayVertexAttribLFormatEXT",
    /* 1467 */ "glVertexArrayVertexAttribBindingEXT",
    /* 1468 */ "glVertexArrayVertexBindingDivisorEXT",
    /* 1469 */ "glVertexArrayVertexAttribLOffsetEXT",
    /* 1470 */ "glTexturePageCommitmentEXT",
    /* 1471 */ "glVertexArrayVertexAttribDivisorEXT",
    /* 1472 */ "glGetQueryObjecti64vEXT",
    /* 1473 */ "glGetQueryObjectui64vEXT",
    /* 1474 */ "glColorMaskIndexedEXT",
    /* 1475 */ "glDrawArraysInstancedEXT",
    /* 1476 */ "glDrawElementsInstancedEXT",
    /* 1477 */ "glDrawRangeElementsEXT",
    /* 1478 */ "glBufferStorageExternalEXT",
    /* 1479 */ "glNamedBufferStorageExternalEXT",
    /* 1480 */ "glFogCoordfEXT",
    /* 1481 */ "glFogCoordfvEXT",
    /* 1482 */ "glFogCoorddEXT",
    /* 1483 */ "glFogCoorddvEXT",
    /* 1484 */ "glFogCoordPointerEXT",
    /* 1485 */ "glBlitFramebufferEXT",
    /* 1486 */ "glBlitFramebufferLayersEXT",
    /* 1487 */ "glBlitFramebufferLayerEXT",
    /* 1488 */ "glRenderbufferStorageMultisampleEXT",
    /* 1489 */ "glIsRenderbufferEXT",
    /* 1490 */ "glBindRenderbufferEXT",
    /* 1491 */ "glDeleteRenderbuffersEXT",
    /* 1492 */ "glGenRenderbuffersEXT",
    /* 1493 */ "glRenderbufferStorageEXT",
    /* 1494 */ "glGetRenderbufferParameterivEXT",
    /* 1495 */ "glIsFramebufferEXT",
    /* 1496 */ "glBindFramebufferEXT",
    /* 1497 */ "glDeleteFramebuffersEXT",
    /* 1498 */ "glGenFramebuffersEXT",
    /* 1499 */ "glCheckFramebufferStatusEXT",
    /* 1500 */ "glFramebufferTexture1DEXT",
    /* 1501 */ "glFramebufferTexture2DEXT",
    /* 1502 */ "glFramebufferTexture3DEXT",
    /* 1503 */ "glFramebufferRenderbufferEXT",
    /* 1504 */ "glGetFramebufferAttachmentParameterivEXT",
    /* 1505 */ "glGenerateMipmapEXT",
    /* 1506 */ "glFramebufferTextureEXT",
    /* 1507 */ "glProgramParameteriEXT",
    /* 1508 */ "glProgramEnvParameters4fvEXT",
    /* 1509 */ "glProgramLocalParameters4fvEXT",
    /* 1510 */ "glGetUniformuivEXT",
    /* 1511 */ "glGetFragDataLocationEXT",
    /* 1512 */ "glUniform1uiEXT",
    /* 1513 */ "glUniform2uiEXT",
    /* 1514 */ "glUniform3uiEXT",
    /* 1515 */ "glUniform4uiEXT",
    /* 1516 */ "glUniform1uivEXT",
    /* 1517 */ "glUniform2uivEXT",
    /* 1518 */ "glUniform3uivEXT",
    /* 1519 */ "glUniform4uivEXT",
    /* 1520 */ "glVertexAttribI1iEXT",
    /* 1521 */ "glVertexAttribI2iEXT",
    /* 1522 */ "glVertexAttribI3iEXT",
    /* 1523 */ "glVertexAttribI4iEXT",
    /* 1524 */ "glVertexAttribI1uiEXT",
    /* 1525 */ "glVertexAttribI2uiEXT",
    /* 1526 */ "glVertexAttribI3uiEXT",
    /* 1527 */ "glVertexAttribI4uiEXT",
    /* 1528 */ "glVertexAttribI1ivEXT",
    /* 1529 */ "glVertexAttribI2ivEXT",
    /* 1530 */ "glVertexAttribI3ivEXT",
    /* 1531 */ "glVertexAttribI4ivEXT",
    /* 1532 */ "glVertexAttribI1uivEXT",
    /* 1533 */ "glVertexAttribI2uivEXT",
    /* 1534 */ "glVertexAttribI3uivEXT",
    /* 1535 */ "glVertexAttribI4uivEXT",
    /* 1536 */ "glVertexAttribI4bvEXT",
    /* 1537 */ "glVertexAttribI4svEXT",
    /* 1538 */ "glVertexAttribI4ubvEXT",
    /* 1539 */ "glVertexAttribI4usvEXT",
    /* 1540 */ "glVertexAttribIPointerEXT",
    /* 1541 */ "glGetVertexAttribIivEXT",
    /* 1542 */ "glGetVertexAttribIuivEXT",
    /* 1543 */ "glGetHistogramEXT",
    /* 1544 */ "glGetHistogramParameterfvEXT",
    /* 1545 */ "glGetHistogramParameterivEXT",
    /* 1546 */ "glGetMinmaxEXT",
    /* 1547 */ "glGetMinmaxParameterfvEXT",
    /* 1548 */ "glGetMinmaxParameterivEXT",
    /* 1549 */ "glHistogramEXT",
    /* 1550 */ "glMinmaxEXT",
    /* 1551 */ "glResetHistogramEXT",
    /* 1552 */ "glResetMinmaxEXT",
    /* 1553 */ "glIndexFuncEXT",
    /* 1554 */ "glIndexMaterialEXT",
    /* 1555 */ "glApplyTextureEXT",
    /* 1556 */ "glTextureLightEXT",
    /* 1557 */ "glTextureMaterialEXT",
    /* 1558 */ "glGetUnsignedBytevEXT",
    /* 1559 */ "glGetUnsignedBytei_vEXT",
    /* 1560 */ "glDeleteMemoryObjectsEXT",
    /* 1561 */ "glIsMemoryObjectEXT",
    /* 1562 */ "glCreateMemoryObjectsEXT",
    /* 1563 */ "glMemoryObjectParameterivEXT",
    /* 1564 */ "glGetMemoryObjectParameterivEXT",
    /* 1565 */ "glTexStorageMem2DEXT",
    /* 1566 */ "glTexStorageMem2DMultisampleEXT",
    /* 1567 */ "glTexStorageMem3DEXT",
    /* 1568 */ "glTexStorageMem3DMultisampleEXT",
    /* 1569 */ "glBufferStorageMemEXT",
    /* 1570 */ "glTextureStorageMem2DEXT",
    /* 1571 */ "glTextureStorageMem2DMultisampleEXT",
    /* 1572 */ "glTextureStorageMem3DEXT",
    /* 1573 */ "glTextureStorageMem3DMultisampleEXT",
    /* 1574 */ "glNamedBufferStorageMemEXT",
    /* 1575 */ "glTexStorageMem1DEXT",
    /* 1576 */ "glTextureStorageMem1DEXT",
    /* 1577 */ "glImportMemoryFdEXT",
    /* 1578 */ "glImportMemoryWin32HandleEXT",
    /* 1579 */ "glImportMemoryWin32NameEXT",
    /* 1580 */ "glMultiDrawArraysEXT",
    /* 1581 */ "glMultiDrawElementsEXT",
    /* 1582 */ "glSampleMaskEXT",
    /* 1583 */ "glSamplePatternEXT",
    /* 1584 */ "glColorTableEXT",
    /* 1585 */ "glGetColorTableEXT",
    /* 1586 */ "glGetColorTableParameterivEXT",
    /* 1587 */ "glGetColorTableParameterfvEXT",
    /* 1588 */ "glPixelTransformParameteriEXT",
    /* 1589 */ "glPixelTransformParameterfEXT",
    /* 1590 */ "glPixelTransformParameterivEXT",
    /* 1591 */ "glPixelTransformParameterfvEXT",
    /* 1592 */ "glGetPixelTransformParameterivEXT",
    /* 1593 */ "glGetPixelTransformParameterfvEXT",
    /* 1594 */ "glPointParameterfEXT",
    /* 1595 */ "glPointParameterfvEXT",
    /* 1596 */ "glPolygonOffsetEXT",
    /* 1597 */ "glPolygonOffsetClampEXT",
    /* 1598 */ "glProvokingVertexEXT",
    /* 1599 */ "glRasterSamplesEXT",
    /* 1600 */ "glGenSemaphoresEXT",
    /* 1601 */ "glDeleteSemaphoresEXT",
    /* 1602 */ "glIsSemaphoreEXT",
    /* 1603 */ "glSemaphoreParameterui64vEXT",
    /* 1604 */ "glGetSemaphoreParameterui64vEXT",
    /* 1605 */ "glWaitSemaphoreEXT",
    /* 1606 */ "glSignalSemaphoreEXT",
    /* 1607 */ "glImportSemaphoreFdEXT",
    /* 1608 */ "glImportSemaphoreWin32HandleEXT",
    /* 1609 */ "glImportSemaphoreWin32NameEXT",
    /* 1610 */ "glSecondaryColor3bEXT",
    /* 1611 */ "glSecondaryColor3bvEXT",
    /* 1612 */ "glSecondaryColor3dEXT",
    /* 1613 */ "glSecondaryColor3dvEXT",
    /* 1614 */ "glSecondaryColor3fEXT",
    /* 1615 */ "glSecondaryColor3fvEXT",
    /* 1616 */ "glSecondaryColor3iEXT",
    /* 1617 */ "glSecondaryColor3ivEXT",
    /* 1618 */ "glSecondaryColor3sEXT",
    /* 1619 */ "glSecondaryColor3svEXT",
    /* 1620 */ "glSecondaryColor3ubEXT",
    /* 1621 */ "glSecondaryColor3ubvEXT",
    /* 1622 */ "glSecondaryColor3uiEXT",
    /* 1623 */ "glSecondaryColor3uivEXT",
    /* 1624 */ "glSecondaryColor3usEXT",
    /* 1625 */ "glSecondaryColor3usvEXT",
    /* 1626 */ "glSecondaryColorPointerEXT",
    /* 1627 */ "glUseShaderProgramEXT",
    /* 1628 */ "glActiveProgramEXT",
    /* 1629 */ "glCreateShaderProgramEXT",
    /* 1630 */ "glFramebufferFetchBarrierEXT",
    /* 1631 */ "glBindImageTextureEXT",
    /* 1632 */ "glMemoryBarrierEXT",
    /* 1633 */ "glStencilClearTagEXT",
    /* 1634 */ "glActiveStencilFaceEXT",
    /* 1635 */ "glTexSubImage1DEXT",
    /* 1636 */ "glTexSubImage2DEXT",
    /* 1637 */ "glTexImage3DEXT",
    /* 1638 */ "glTexSubImage3DEXT",
    /* 1639 */ "glFramebufferTextureLayerEXT",
    /* 1640 */ "glTexParameterIivEXT",
    /* 1641 */ "glTexParameterIuivEXT",
    /* 1642 */ "glGetTexParameterIivEXT",
    /* 1643 */ "glGetTexParameterIuivEXT",
    /* 1644 */ "glTexBufferEXT",
    /* 1645 */ "glClearColorIiEXT",
    /* 1646 */ "glClearColorIuiEXT",
    /* 1647 */ "glAreTexturesResidentEXT",
    /* 1648 */ "glBindTextureEXT",
    /* 1649 */ "glDeleteTexturesEXT",
    /* 1650 */ "glGenTexturesEXT",
    /* 1651 */ "glIsTextureEXT",
    /* 1652 */ "glPrioritizeTexturesEXT",
    /* 1653 */ "glTextureNormalEXT",
    /* 1654 */ "glTexStorage1DEXT",
    /* 1655 */ "glTexStorage2DEXT",
    /* 1656 */ "glTexStorage3DEXT",
    /* 1657 */ "glCreateSemaphoresNV",
    /* 1658 */ "glSemaphoreParameterivNV",
    /* 1659 */ "glGetSemaphoreParameterivNV",
    /* 1660 */ "glBeginTransformFeedbackEXT",
    /* 1661 */ "glEndTransformFeedbackEXT",
    /* 1662 */ "glBindBufferRangeEXT",
    /* 1663 */ "glBindBufferOffsetEXT",
    /* 1664 */ "glBindBufferBaseEXT",
    /* 1665 */ "glTransformFeedbackVaryingsEXT",
    /* 1666 */ "glGetTransformFeedbackVaryingEXT",
    /* 1667 */ "glArrayElementEXT",
    /* 1668 */ "glColorPointerEXT",
    /* 1669 */ "glDrawArraysEXT",
    /* 1670 */ "glEdgeFlagPointerEXT",
    /* 1671 */ "glGetPointervEXT",
    /* 1672 */ "glIndexPointerEXT",
    /* 1673 */ "glNormalPointerEXT",
    /* 1674 */ "glTexCoordPointerEXT",
    /* 1675 */ "glVertexPointerEXT",
    /* 1676 */ "glVertexAttribL1dEXT",
    /* 1677 */ "glVertexAttribL2dEXT",
    /* 1678 */ "glVertexAttribL3dEXT",
    /* 1679 */ "glVertexAttribL4dEXT",
    /* 1680 */ "glVertexAttribL1dvEXT",
    /* 1681 */ "glVertexAttribL2dvEXT",
    /* 1682 */ "glVertexAttribL3dvEXT",
    /* 1683 */ "glVertexAttribL4dvEXT",
    /* 1684 */ "glVertexAttribLPointerEXT",
    /* 1685 */ "glGetVertexAttribLdvEXT",
    /* 1686 */ "glBeginVertexShaderEXT",
    /* 1687 */ "glEndVertexShaderEXT",
    /* 1688 */ "glBindVertexShaderEXT",
    /* 1689 */ "glGenVertexShadersEXT",
    /* 1690 */ "glDeleteVertexShaderEXT",
    /* 1691 */ "glShaderOp1EXT",
    /* 1692 */ "glShaderOp2EXT",
    /* 1693 */ "glShaderOp3EXT",
    /* 1694 */ "glSwizzleEXT",
    /* 1695 */ "glWriteMaskEXT",
    /* 1696 */ "glInsertComponentEXT",
    /* 1697 */ "glExtractComponentEXT",
    /* 1698 */ "glGenSymbolsEXT",
    /* 1699 */ "glSetInvariantEXT",
    /* 1700 */ "glSetLocalConstantEXT",
    /* 1701 */ "glVariantbvEXT",
    /* 1702 */ "glVariantsvEXT",
    /* 1703 */ "glVariantivEXT",
    /* 1704 */ "glVariantfvEXT",
    /* 1705 */ "glVariantdvEXT",
    /* 1706 */ "glVariantubvEXT",
    /* 1707 */ "glVariantusvEXT",
    /* 1708 */ "glVariantuivEXT",
    /* 1709 */ "glVariantPointerEXT",
    /* 1710 */ "glEnableVariantClientStateEXT",
    /* 1711 */ "glDisableVariantClientStateEXT",
    /* 1712 */ "glBindLightParameterEXT",
    /* 1713 */ "glBindMaterialParameterEXT",
    /* 1714 */ "glBindTexGenParameterEXT",
    /* 1715 */ "glBindTextureUnitParameterEXT",
    /* 1716 */ "glBindParameterEXT",
    /* 1717 */ "glIsVariantEnabledEXT",
    /* 1718 */ "glGetVariantBooleanvEXT",
    /* 1719 */ "glGetVariantIntegervEXT",
    /* 1720 */ "glGetVariantFloatvEXT",
    /* 1721 */ "glGetVariantPointervEXT",
    /* 1722 */ "glGetInvariantBooleanvEXT",
    /* 1723 */ "glGetInvariantIntegervEXT",
    /* 1724 */ "glGetInvariantFloatvEXT",
    /* 1725 */ "glGetLocalConstantBooleanvEXT",
    /* 1726 */ "glGetLocalConstantIntegervEXT",
    /* 1727 */ "glGetLocalConstantFloatvEXT",
    /* 1728 */ "glVertexWeightfEXT",
    /* 1729 */ "glVertexWeightfvEXT",
    /* 1730 */ "glVertexWeightPointerEXT",
    /* 1731 */ "glAcquireKeyedMutexWin32EXT",
    /* 1732 */ "glReleaseKeyedMutexWin32EXT",
    /* 1733 */ "glWindowRectanglesEXT",
    /* 1734 */ "glImportSyncEXT",
    /* 1735 */ "glFrameTerminatorGREMEDY",
    /* 1736 */ "glStringMarkerGREMEDY",
    /* 1737 */ "glImageTransformParameteriHP",
    /* 1738 */ "glImageTransformParameterfHP",
    /* 1739 */ "glImageTransformParameterivHP",
    /* 1740 */ "glImageTransformParameterfvHP",
    /* 1741 */ "glGetImageTransformParameterivHP",
    /* 1742 */ "glGetImageTransformParameterfvHP",
    /* 1743 */ "glMultiModeDrawArraysIBM",
    /* 1744 */ "glMultiModeDrawElementsIBM",
    /* 1745 */ "glFlushStaticDataIBM",
    /* 1746 */ "glColorPointerListIBM",
    /* 1747 */ "glSecondaryColorPointerListIBM",
    /* 1748 */ "glEdgeFlagPointerListIBM",
    /* 1749 */ "glFogCoordPointerListIBM",
    /* 1750 */ "glIndexPointerListIBM",
    /* 1751 */ "glNormalPointerListIBM",
    /* 1752 */ "glTexCoordPointerListIBM",
    /* 1753 */ "glVertexPointerListIBM",
    /* 1754 */ "glBlendFuncSeparateINGR",
    /* 1755 */ "glApplyFramebufferAttachmentCMAAINTEL",
    /* 1756 */ "glSyncTextureINTEL",
    /* 1757 */ "glUnmapTexture2DINTEL",
    /* 1758 */ "glMapTexture2DINTEL",
    /* 1759 */ "glVertexPointervINTEL",
    /* 1760 */ "glNormalPointervINTEL",
    /* 1761 */ "glColorPointervINTEL",
    /* 1762 */ "glTexCoordPointervINTEL",
    /* 1763 */ "glBeginPerfQueryINTEL",
    /* 1764 */ "glCreatePerfQueryINTEL",
    /* 1765 */ "glDeletePerfQueryINTEL",
    /* 1766 */ "glEndPerfQueryINTEL",
    /* 1767 */ "glGetFirstPerfQueryIdINTEL",
    /* 1768 */ "glGetNextPerfQueryIdINTEL",
    /* 1769 */ "glGetPerfCounterInfoINTEL",
    /* 1770 */ "glGetPerfQueryDataINTEL",
    /* 1771 */ "glGetPerfQueryIdByNameINTEL",
    /* 1772 */ "glGetPerfQueryInfoINTEL",
    /* 1773 */ "glBlendBarrierKHR",
    /* 1774 */ "glMaxShaderCompilerThreadsKHR",
    /* 1775 */ "glFramebufferParameteriMESA",
    /* 1776 */ "glGetFramebufferParameterivMESA",
    /* 1777 */ "glResizeBuffersMESA",
    /* 1778 */ "glWindowPos2dMESA",
    /* 1779 */ "glWindowPos2dvMESA",
    /* 1780 */ "glWindowPos2fMESA",
    /* 1781 */ "glWindowPos2fvMESA",
    /* 1782 */ "glWindowPos2iMESA",
    /* 1783 */ "glWindowPos2ivMESA",
    /* 1784 */ "glWindowPos2sMESA",
    /* 1785 */ "glWindowPos2svMESA",
    /* 1786 */ "glWindowPos3dMESA",
    /* 1787 */ "glWindowPos3dvMESA",
    /* 1788 */ "glWindowPos3fMESA",
    /* 1789 */ "glWindowPos3fvMESA",
    /* 1790 */ "glWindowPos3iMESA",
    /* 1791 */ "glWindowPos3ivMESA",
    /* 1792 */ "glWindowPos3sMESA",
    /* 1793 */ "glWindowPos3svMESA",
    /* 1794 */ "glWindowPos4dMESA",
    /* 1795 */ "glWindowPos4dvMESA",
    /* 1796 */ "glWindowPos4fMESA",
    /* 1797 */ "glWindowPos4fvMESA",
    /* 1798 */ "glWindowPos4iMESA",
    /* 1799 */ "glWindowPos4ivMESA",
    /* 1800 */ "glWindowPos4sMESA",
    /* 1801 */ "glWindowPos4svMESA",
    /* 1802 */ "glBeginConditionalRenderNVX",
    /* 1803 */ "glEndConditionalRenderNVX",
    /* 1804 */ "glLGPUNamedBufferSubDataNVX",
    /* 1805 */ "glLGPUCopyImageSubDataNVX",
    /* 1806 */ "glLGPUInterlockNVX",
    /* 1807 */ "glAlphaToCoverageDitherControlNV",
    /* 1808 */ "glMultiDrawArraysIndirectBindlessNV",
    /* 1809 */ "glMultiDrawElementsIndirectBindlessNV",
    /* 1810 */ "glMultiDrawArraysIndirectBindlessCountNV",
    /* 1811 */ "glMultiDrawElementsIndirectBindlessCountNV",
    /* 1812 */ "glGetTextureHandleNV",
    /* 1813 */ "glGetTextureSamplerHandleNV",
    /* 1814 */ "glMakeTextureHandleResidentNV",
    /* 1815 */ "glMakeTextureHandleNonResidentNV",
    /* 1816 */ "glGetImageHandleNV",
    /* 1817 */ "glMakeImageHandleResidentNV",
    /* 1818 */ "glMakeImageHandleNonResidentNV",
    /* 1819 */ "glUniformHandleui64NV",
    /* 1820 */ "glUniformHandleui64vNV",
    /* 1821 */ "glProgramUniformHandleui64NV",
    /* 1822 */ "glProgramUniformHandleui64vNV",
    /* 1823 */ "glIsTextureHandleResidentNV",
    /* 1824 */ "glIsImageHandleResidentNV",
    /* 1825 */ "glBlendParameteriNV",
    /* 1826 */ "glBlendBarrierNV",
    /* 1827 */ "glViewportPositionWScaleNV",
    /* 1828 */ "glCreateStatesNV",
    /* 1829 */ "glDeleteStatesNV",
    /* 1830 */ "glIsStateNV",
    /* 1831 */ "glStateCaptureNV",
    /* 1832 */ "glGetCommandHeaderNV",
    /* 1833 */ "glGetStageIndexNV",
    /* 1834 */ "glDrawCommandsNV",
    /* 1835 */ "glDrawCommandsAddressNV",
    /* 1836 */ "glDrawCommandsStatesNV",
    /* 1837 */ "glDrawCommandsStatesAddressNV",
    /* 1838 */ "glCreateCommandListsNV",
    /* 1839 */ "glDeleteCommandListsNV",
    /* 1840 */ "glIsCommandListNV",
    /* 1841 */ "glListDrawCommandsStatesClientNV",
    /* 1842 */ "glCommandListSegmentsNV",
    /* 1843 */ "glCompileCommandListNV",
    /* 1844 */ "glCallCommandListNV",
    /* 1845 */ "glBeginConditionalRenderNV",
    /* 1846 */ "glEndConditionalRenderNV",
    /* 1847 */ "glSubpixelPrecisionBiasNV",
    /* 1848 */ "glConservativeRasterParameterfNV",
    /* 1849 */ "glConservativeRasterParameteriNV",
    /* 1850 */ "glCopyImageSubDataNV",
    /* 1851 */ "glDepthRangedNV",
    /* 1852 */ "glClearDepthdNV",
    /* 1853 */ "glDepthBoundsdNV",
    /* 1854 */ "glDrawTextureNV",
    /* 1855 */ "glDrawVkImageNV",
    /* 1856 */ "glGetVkProcAddrNV",
    /* 1857 */ "glWaitVkSemaphoreNV",
    /* 1858 */ "glSignalVkSemaphoreNV",
    /* 1859 */ "glSignalVkFenceNV",
    /* 1860 */ "glMapControlPointsNV",
    /* 1861 */ "glMapParameterivNV",
    /* 1862 */ "glMapParameterfvNV",
    /* 1863 */ "glGetMapControlPointsNV",
    /* 1864 */ "glGetMapParameterivNV",
    /* 1865 */ "glGetMapParameterfvNV",
    /* 1866 */ "glGetMapAttribParameterivNV",
    /* 1867 */ "glGetMapAttribParameterfvNV",
    /* 1868 */ "glEvalMapsNV",
    /* 1869 */ "glGetMultisamplefvNV",
    /* 1870 */ "glSampleMaskIndexedNV",
    /* 1871 */ "glTexRenderbufferNV",
    /* 1872 */ "glDeleteFencesNV",
    /* 1873 */ "glGenFencesNV",
    /* 1874 */ "glIsFenceNV",
    /* 1875 */ "glTestFenceNV",
    /* 1876 */ "glGetFenceivNV",
    /* 1877 */ "glFinishFenceNV",
    /* 1878 */ "glSetFenceNV",
    /* 1879 */ "glFragmentCoverageColorNV",
    /* 1880 */ "glProgramNamedParameter4fNV",
    /* 1881 */ "glProgramNamedParameter4fvNV",
    /* 1882 */ "glProgramNamedParameter4dNV",
    /* 1883 */ "glProgramNamedParameter4dvNV",
    /* 1884 */ "glGetProgramNamedParameterfvNV",
    /* 1885 */ "glGetProgramNamedParameterdvNV",
    /* 1886 */ "glCoverageModulationTableNV",
    /* 1887 */ "glGetCoverageModulationTableNV",
    /* 1888 */ "glCoverageModulationNV",
    /* 1889 */ "glRenderbufferStorageMultisampleCoverageNV",
    /* 1890 */ "glProgramVertexLimitNV",
    /* 1891 */ "glFramebufferTextureFaceEXT",
    /* 1892 */ "glProgramLocalParameterI4iNV",
    /* 1893 */ "glProgramLocalParameterI4ivNV",
    /* 1894 */ "glProgramLocalParametersI4ivNV",
    /* 1895 */ "glProgramLocalParameterI4uiNV",
    /* 1896 */ "glProgramLocalParameterI4uivNV",
    /* 1897 */ "glProgramLocalParametersI4uivNV",
    /* 1898 */ "glProgramEnvParameterI4iNV",
    /* 1899 */ "glProgramEnvParameterI4ivNV",
    /* 1900 */ "glProgramEnvParametersI4ivNV",
    /* 1901 */ "glProgramEnvParameterI4uiNV",
    /* 1902 */ "glProgramEnvParameterI4uivNV",
    /* 1903 */ "glProgramEnvParametersI4uivNV",
    /* 1904 */ "glGetProgramLocalParameterIivNV",
    /* 1905 */ "glGetProgramLocalParameterIuivNV",
    /* 1906 */ "glGetProgramEnvParameterIivNV",
    /* 1907 */ "glGetProgramEnvParameterIuivNV",
    /* 1908 */ "glProgramSubroutineParametersuivNV",
    /* 1909 */ "glGetProgramSubroutineParameteruivNV",
    /* 1910 */ "glVertex2hNV",
    /* 1911 */ "glVertex2hvNV",
    /* 1912 */ "glVertex3hNV",
    /* 1913 */ "glVertex3hvNV",
    /* 1914 */ "glVertex4hNV",
    /* 1915 */ "glVertex4hvNV",
    /* 1916 */ "glNormal3hNV",
    /* 1917 */ "glNormal3hvNV",
    /* 1918 */ "glColor3hNV",
    /* 1919 */ "glColor3hvNV",
    /* 1920 */ "glColor4hNV",
    /* 1921 */ "glColor4hvNV",
    /* 1922 */ "glTexCoord1hNV",
    /* 1923 */ "glTexCoord1hvNV",
    /* 1924 */ "glTexCoord2hNV",
    /* 1925 */ "glTexCoord2hvNV",
    /* 1926 */ "glTexCoord3hNV",
    /* 1927 */ "glTexCoord3hvNV",
    /* 1928 */ "glTexCoord4hNV",
    /* 1929 */ "glTexCoord4hvNV",
    /* 1930 */ "glMultiTexCoord1hNV",
    /* 1931 */ "glMultiTexCoord1hvNV",
    /* 1932 */ "glMultiTexCoord2hNV",
    /* 1933 */ "glMultiTexCoord2hvNV",
    /* 1934 */ "glMultiTexCoord3hNV",
    /* 1935 */ "glMultiTexCoord3hvNV",
    /* 1936 */ "glMultiTexCoord4hNV",
    /* 1937 */ "glMultiTexCoord4hvNV",
    /* 1938 */ "glVertexAttrib1hNV",
    /* 1939 */ "glVertexAttrib1hvNV",
    /* 1940 */ "glVertexAttrib2hNV",
    /* 1941 */ "glVertexAttrib2hvNV",
    /* 1942 */ "glVertexAttrib3hNV",
    /* 1943 */ "glVertexAttrib3hvNV",
    /* 1944 */ "glVertexAttrib4hNV",
    /* 1945 */ "glVertexAttrib4hvNV",
    /* 1946 */ "glVertexAttribs1hvNV",
    /* 1947 */ "glVertexAttribs2hvNV",
    /* 1948 */ "glVertexAttribs3hvNV",
    /* 1949 */ "glVertexAttribs4hvNV",
    /* 1950 */ "glFogCoordhNV",
    /* 1951 */ "glFogCoordhvNV",
    /* 1952 */ "glSecondaryColor3hNV",
    /* 1953 */ "glSecondaryColor3hvNV",
    /* 1954 */ "glVertexWeighthNV",
    /* 1955 */ "glVertexWeighthvNV",
    /* 1956 */ "glGetInternalformatSampleivNV",
    /* 1957 */ "glRenderGpuMaskNV",
    /* 1958 */ "glMulticastBufferSubDataNV",
    /* 1959 */ "glMulticastCopyBufferSubDataNV",
    /* 1960 */ "glMulticastCopyImageSubDataNV",
    /* 1961 */ "glMulticastBlitFramebufferNV",
    /* 1962 */ "glMulticastFramebufferSampleLocationsfvNV",
    /* 1963 */ "glMulticastBarrierNV",
    /* 1964 */ "glMulticastWaitSyncNV",
    /* 1965 */ "glMulticastGetQueryObjectivNV",
    /* 1966 */ "glMulticastGetQueryObjectuivNV",
    /* 1967 */ "glMulticastGetQueryObjecti64vNV",
    /* 1968 */ "glMulticastGetQueryObjectui64vNV",
    /* 1969 */ "glUploadGpuMaskNVX",
    /* 1970 */ "glMulticastViewportArrayvNVX",
    /* 1971 */ "glMulticastViewportPositionWScaleNVX",
    /* 1972 */ "glMulticastScissorArrayvNVX",
    /* 1973 */ "glAsyncCopyBufferSubDataNVX",
    /* 1974 */ "glAsyncCopyImageSubDataNVX",
    /* 1975 */ "glCreateProgressFenceNVX",
    /* 1976 */ "glSignalSemaphoreui64NVX",
    /* 1977 */ "glWaitSemaphoreui64NVX",
    /* 1978 */ "glClientWaitSemaphoreui64NVX",
    /* 1979 */ "glGetMemoryObjectDetachedResourcesuivNV",
    /* 1980 */ "glResetMemoryObjectParameterNV",
    /* 1981 */ "glTexAttachMemoryNV",
    /* 1982 */ "glBufferAttachMemoryNV",
    /* 1983 */ "glTextureAttachMemoryNV",
    /* 1984 */ "glNamedBufferAttachMemoryNV",
    /* 1985 */ "glBufferPageCommitmentMemNV",
    /* 1986 */ "glTexPageCommitmentMemNV",
    /* 1987 */ "glNamedBufferPageCommitmentMemNV",
    /* 1988 */ "glTexturePageCommitmentMemNV",
    /* 1989 */ "glDrawMeshTasksNV",
    /* 1990 */ "glDrawMeshTasksIndirectNV",
    /* 1991 */ "glMultiDrawMeshTasksIndirectNV",
    /* 1992 */ "glMultiDrawMeshTasksIndirectCountNV",
    /* 1993 */ "glGenOcclusionQueriesNV",
    /* 1994 */ "glDeleteOcclusionQueriesNV",
    /* 1995 */ "glIsOcclusionQueryNV",
    /* 1996 */ "glBeginOcclusionQueryNV",
    /* 1997 */ "glEndOcclusionQueryNV",
    /* 1998 */ "glGetOcclusionQueryivNV",
    /* 1999 */ "glGetOcclusionQueryuivNV",
    /* 2000 */ "glProgramBufferParametersfvNV",
    /* 2001 */ "glProgramBufferParametersIivNV",
    /* 2002 */ "glProgramBufferParametersIuivNV",
    /* 2003 */ "glGenPathsNV",
    /* 2004 */ "glDeletePathsNV",
    /* 2005 */ "glIsPathNV",
    /* 2006 */ "glPathCommandsNV",
    /* 2007 */ "glPathCoordsNV",
    /* 2008 */ "glPathSubCommandsNV",
    /* 2009 */ "glPathSubCoordsNV",
    /* 2010 */ "glPathStringNV",
    /* 2011 */ "glPathGlyphsNV",
    /* 2012 */ "glPathGlyphRangeNV",
    /* 2013 */ "glWeightPathsNV",
    /* 2014 */ "glCopyPathNV",
    /* 2015 */ "glInterpolatePathsNV",
    /* 2016 */ "glTransformPathNV",
    /* 2017 */ "glPathParameterivNV",
    /* 2018 */ "glPathParameteriNV",
    /* 2019 */ "glPathParameterfvNV",
    /* 2020 */ "glPathParameterfNV",
    /* 2021 */ "glPathDashArrayNV",
    /* 2022 */ "glPathStencilFuncNV",
    /* 2023 */ "glPathStencilDepthOffsetNV",
    /* 2024 */ "glStencilFillPathNV",
    /* 2025 */ "glStencilStrokePathNV",
    /* 2026 */ "glStencilFillPathInstancedNV",
    /* 2027 */ "glStencilStrokePathInstancedNV",
    /* 2028 */ "glPathCoverDepthFuncNV",
    /* 2029 */ "glCoverFillPathNV",
    /* 2030 */ "glCoverStrokePathNV",
    /* 2031 */ "glCoverFillPathInstancedNV",
    /* 2032 */ "glCoverStrokePathInstancedNV",
    /* 2033 */ "glGetPathParameterivNV",
    /* 2034 */ "glGetPathParameterfvNV",
    /* 2035 */ "glGetPathCommandsNV",
    /* 2036 */ "glGetPathCoordsNV",
    /* 2037 */ "glGetPathDashArrayNV",
    /* 2038 */ "glGetPathMetricsNV",
    /* 2039 */ "glGetPathMetricRangeNV",
    /* 2040 */ "glGetPathSpacingNV",
    /* 2041 */ "glIsPointInFillPathNV",
    /* 2042 */ "glIsPointInStrokePathNV",
    /* 2043 */ "glGetPathLengthNV",
    /* 2044 */ "glPointAlongPathNV",
    /* 2045 */ "glMatrixLoad3x2fNV",
    /* 2046 */ "glMatrixLoad3x3fNV",
    /* 2047 */ "glMatrixLoadTranspose3x3fNV",
    /* 2048 */ "glMatrixMult3x2fNV",
    /* 2049 */ "glMatrixMult3x3fNV",
    /* 2050 */ "glMatrixMultTranspose3x3fNV",
    /* 2051 */ "glStencilThenCoverFillPathNV",
    /* 2052 */ "glStencilThenCoverStrokePathNV",
    /* 2053 */ "glStencilThenCoverFillPathInstancedNV",
    /* 2054 */ "glStencilThenCoverStrokePathInstancedNV",
    /* 2055 */ "glPathGlyphIndexRangeNV",
    /* 2056 */ "glPathGlyphIndexArrayNV",
    /* 2057 */ "glPathMemoryGlyphIndexArrayNV",
    /* 2058 */ "glProgramPathFragmentInputGenNV",
    /* 2059 */ "glGetProgramResourcefvNV",
    /* 2060 */ "glPixelDataRangeNV",
    /* 2061 */ "glFlushPixelDataRangeNV",
    /* 2062 */ "glPointParameteriNV",
    /* 2063 */ "glPointParameterivNV",
    /* 2064 */ "glPresentFrameKeyedNV",
    /* 2065 */ "glPresentFrameDualFillNV",
    /* 2066 */ "glGetVideoivNV",
    /* 2067 */ "glGetVideouivNV",
    /* 2068 */ "glGetVideoi64vNV",
    /* 2069 */ "glGetVideoui64vNV",
    /* 2070 */ "glPrimitiveRestartNV",
    /* 2071 */ "glPrimitiveRestartIndexNV",
    /* 2072 */ "glQueryResourceNV",
    /* 2073 */ "glGenQueryResourceTagNV",
    /* 2074 */ "glDeleteQueryResourceTagNV",
    /* 2075 */ "glQueryResourceTagNV",
    /* 2076 */ "glCombinerParameterfvNV",
    /* 2077 */ "glCombinerParameterfNV",
    /* 2078 */ "glCombinerParameterivNV",
    /* 2079 */ "glCombinerParameteriNV",
    /* 2080 */ "glCombinerInputNV",
    /* 2081 */ "glCombinerOutputNV",
    /* 2082 */ "glFinalCombinerInputNV",
    /* 2083 */ "glGetCombinerInputParameterfvNV",
    /* 2084 */ "glGetCombinerInputParameterivNV",
    /* 2085 */ "glGetCombinerOutputParameterfvNV",
    /* 2086 */ "glGetCombinerOutputParameterivNV",
    /* 2087 */ "glGetFinalCombinerInputParameterfvNV",
    /* 2088 */ "glGetFinalCombinerInputParameterivNV",
    /* 2089 */ "glCombinerStageParameterfvNV",
    /* 2090 */ "glGetCombinerStageParameterfvNV",
    /* 2091 */ "glFramebufferSampleLocationsfvNV",
    /* 2092 */ "glNamedFramebufferSampleLocationsfvNV",
    /* 2093 */ "glResolveDepthValuesNV",
    /* 2094 */ "glScissorExclusiveNV",
    /* 2095 */ "glScissorExclusiveArrayvNV",
    /* 2096 */ "glMakeBufferResidentNV",
    /* 2097 */ "glMakeBufferNonResidentNV",
    /* 2098 */ "glIsBufferResidentNV",
    /* 2099 */ "glMakeNamedBufferResidentNV",
    /* 2100 */ "glMakeNamedBufferNonResidentNV",
    /* 2101 */ "glIsNamedBufferResidentNV",
    /* 2102 */ "glGetBufferParameterui64vNV",
    /* 2103 */ "glGetNamedBufferParameterui64vNV",
    /* 2104 */ "glGetIntegerui64vNV",
    /* 2105 */ "glUniformui64NV",
    /* 2106 */ "glUniformui64vNV",
    /* 2107 */ "glProgramUniformui64NV",
    /* 2108 */ "glProgramUniformui64vNV",
    /* 2109 */ "glBindShadingRateImageNV",
    /* 2110 */ "glGetShadingRateImagePaletteNV",
    /* 2111 */ "glGetShadingRateSampleLocationivNV",
    /* 2112 */ "glShadingRateImageBarrierNV",
    /* 2113 */ "glShadingRateImagePaletteNV",
    /* 2114 */ "glShadingRateSampleOrderNV",
    /* 2115 */ "glShadingRateSampleOrderCustomNV",
    /* 2116 */ "glTextureBarrierNV",
    /* 2117 */ "glTexImage2DMultisampleCoverageNV",
    /* 2118 */ "glTexImage3DMultisampleCoverageNV",
    /* 2119 */ "glTextureImage2DMultisampleNV",
    /* 2120 */ "glTextureImage3DMultisampleNV",
    /* 2121 */ "glTextureImage2DMultisampleCoverageNV",
    /* 2122 */ "glTextureImage3DMultisampleCoverageNV",
    /* 2123 */ "glBeginTransformFeedbackNV",
    /* 2124 */ "glEndTransformFeedbackNV",
    /* 2125 */ "glTransformFeedbackAttribsNV",
    /* 2126 */ "glBindBufferRangeNV",
    /* 2127 */ "glBindBufferOffsetNV",
    /* 2128 */ "glBindBufferBaseNV",
    /* 2129 */ "glTransformFeedbackVaryingsNV",
    /* 2130 */ "glActiveVaryingNV",
    /* 2131 */ "glGetVaryingLocationNV",
    /* 2132 */ "glGetActiveVaryingNV",
    /* 2133 */ "glGetTransformFeedbackVaryingNV",
    /* 2134 */ "glTransformFeedbackStreamAttribsNV",
    /* 2135 */ "glBindTransformFeedbackNV",
    /* 2136 */ "glDeleteTransformFeedbacksNV",
    /* 2137 */ "glGenTransformFeedbacksNV",
    /* 2138 */ "glIsTransformFeedbackNV",
    /* 2139 */ "glPauseTransformFeedbackNV",
    /* 2140 */ "glResumeTransformFeedbackNV",
    /* 2141 */ "glDrawTransformFeedbackNV",
    /* 2142 */ "glVDPAUInitNV",
    /* 2143 */ "glVDPAUFiniNV",
    /* 2144 */ "glVDPAURegisterVideoSurfaceNV",
    /* 2145 */ "glVDPAURegisterOutputSurfaceNV",
    /* 2146 */ "glVDPAUIsSurfaceNV",
    /* 2147 */ "glVDPAUUnregisterSurfaceNV",
    /* 2148 */ "glVDPAUGetSurfaceivNV",
    /* 2149 */ "glVDPAUSurfaceAccessNV",
    /* 2150 */ "glVDPAUMapSurfacesNV",
    /* 2151 */ "glVDPAUUnmapSurfacesNV",
    /* 2152 */ "glVDPAURegisterVideoSurfaceWithPictureStructureNV",
    /* 2153 */ "glFlushVertexArrayRangeNV",
    /* 2154 */ "glVertexArrayRangeNV",
    /* 2155 */ "glVertexAttribL1i64NV",
    /* 2156 */ "glVertexAttribL2i64NV",
    /* 2157 */ "glVertexAttribL3i64NV",
    /* 2158 */ "glVertexAttribL4i64NV",
    /* 2159 */ "glVertexAttribL1i64vNV",
    /* 2160 */ "glVertexAttribL2i64vNV",
    /* 2161 */ "glVertexAttribL3i64vNV",
    /* 2162 */ "glVertexAttribL4i64vNV",
    /* 2163 */ "glVertexAttribL1ui64NV",
    /* 2164 */ "glVertexAttribL2ui64NV",
    /* 2165 */ "glVertexAttribL3ui64NV",
    /* 2166 */ "glVertexAttribL4ui64NV",
    /* 2167 */ "glVertexAttribL1ui64vNV",
    /* 2168 */ "glVertexAttribL2ui64vNV",
    /* 2169 */ "glVertexAttribL3ui64vNV",
    /* 2170 */ "glVertexAttribL4ui64vNV",
    /* 2171 */ "glGetVertexAttribLi64vNV",
    /* 2172 */ "glGetVertexAttribLui64vNV",
    /* 2173 */ "glVertexAttribLFormatNV",
    /* 2174 */ "glBufferAddressRangeNV",
    /* 2175 */ "glVertexFormatNV",
    /* 2176 */ "glNormalFormatNV",
    /* 2177 */ "glColorFormatNV",
    /* 2178 */ "glIndexFormatNV",
    /* 2179 */ "glTexCoordFormatNV",
    /* 2180 */ "glEdgeFlagFormatNV",
    /* 2181 */ "glSecondaryColorFormatNV",
    /* 2182 */ "glFogCoordFormatNV",
    /* 2183 */ "glVertexAttribFormatNV",
    /* 2184 */ "glVertexAttribIFormatNV",
    /* 2185 */ "glGetIntegerui64i_vNV",
    /* 2186 */ "glAreProgramsResidentNV",
    /* 2187 */ "glBindProgramNV",
    /* 2188 */ "glDeleteProgramsNV",
    /* 2189 */ "glExecuteProgramNV",
    /* 2190 */ "glGenProgramsNV",
    /* 2191 */ "glGetProgramParameterdvNV",
    /* 2192 */ "glGetProgramParameterfvNV",
    /* 2193 */ "glGetProgramivNV",
    /* 2194 */ "glGetProgramStringNV",
    /* 2195 */ "glGetTrackMatrixivNV",
    /* 2196 */ "glGetVertexAttribdvNV",
    /* 2197 */ "glGetVertexAttribfvNV",
    /* 2198 */ "glGetVertexAttribivNV",
    /* 2199 */ "glGetVertexAttribPointervNV",
    /* 2200 */ "glIsProgramNV",
    /* 2201 */ "glLoadProgramNV",
    /* 2202 */ "glProgramParameter4dNV",
    /* 2203 */ "glProgramParameter4dvNV",
    /* 2204 */ "glProgramParameter4fNV",
    /* 2205 */ "glProgramParameter4fvNV",
    /* 2206 */ "glProgramParameters4dvNV",
    /* 2207 */ "glProgramParameters4fvNV",
    /* 2208 */ "glRequestResidentProgramsNV",
    /* 2209 */ "glTrackMatrixNV",
    /* 2210 */ "glVertexAttribPointerNV",
    /* 2211 */ "glVertexAttrib1dNV",
    /* 2212 */ "glVertexAttrib1dvNV",
    /* 2213 */ "glVertexAttrib1fNV",
    /* 2214 */ "glVertexAttrib1fvNV",
    /* 2215 */ "glVertexAttrib1sNV",
    /* 2216 */ "glVertexAttrib1svNV",
    /* 2217 */ "glVertexAttrib2dNV",
    /* 2218 */ "glVertexAttrib2dvNV",
    /* 2219 */ "glVertexAttrib2fNV",
    /* 2220 */ "glVertexAttrib2fvNV",
    /* 2221 */ "glVertexAttrib2sNV",
    /* 2222 */ "glVertexAttrib2svNV",
    /* 2223 */ "glVertexAttrib3dNV",
    /* 2224 */ "glVertexAttrib3dvNV",
    /* 2225 */ "glVertexAttrib3fNV",
    /* 2226 */ "glVertexAttrib3fvNV",
    /* 2227 */ "glVertexAttrib3sNV",
    /* 2228 */ "glVertexAttrib3svNV",
    /* 2229 */ "glVertexAttrib4dNV",
    /* 2230 */ "glVertexAttrib4dvNV",
    /* 2231 */ "glVertexAttrib4fNV",
    /* 2232 */ "glVertexAttrib4fvNV",
    /* 2233 */ "glVertexAttrib4sNV",
    /* 2234 */ "glVertexAttrib4svNV",
    /* 2235 */ "glVertexAttrib4ubNV",
    /* 2236 */ "glVertexAttrib4ubvNV",
    /* 2237 */ "glVertexAttribs1dvNV",
    /* 2238 */ "glVertexAttribs1fvNV",
    /* 2239 */ "glVertexAttribs1svNV",
    /* 2240 */ "glVertexAttribs2dvNV",
    /* 2241 */ "glVertexAttribs2fvNV",
    /* 2242 */ "glVertexAttribs2svNV",
    /* 2243 */ "glVertexAttribs3dvNV",
    /* 2244 */ "glVertexAttribs3fvNV",
    /* 2245 */ "glVertexAttribs3svNV",
    /* 2246 */ "glVertexAttribs4dvNV",
    /* 2247 */ "glVertexAttribs4fvNV",
    /* 2248 */ "glVertexAttribs4svNV",
    /* 2249 */ "glVertexAttribs4ubvNV",
    /* 2250 */ "glBeginVideoCaptureNV",
    /* 2251 */ "glBindVideoCaptureStreamBufferNV",
    /* 2252 */ "glBindVideoCaptureStreamTextureNV",
    /* 2253 */ "glEndVideoCaptureNV",
    /* 2254 */ "glGetVideoCaptureivNV",
    /* 2255 */ "glGetVideoCaptureStreamivNV",
    /* 2256 */ "glGetVideoCaptureStreamfvNV",
    /* 2257 */ "glGetVideoCaptureStreamdvNV",
    /* 2258 */ "glVideoCaptureNV",
    /* 2259 */ "glVideoCaptureStreamParameterivNV",
    /* 2260 */ "glVideoCaptureStreamParameterfvNV",
    /* 2261 */ "glVideoCaptureStreamParameterdvNV",
    /* 2262 */ "glViewportSwizzleNV",
    /* 2263 */ "glMultiTexCoord1bOES",
    /* 2264 */ "glMultiTexCoord1bvOES",
    /* 2265 */ "glMultiTexCoord2bOES",
    /* 2266 */ "glMultiTexCoord2bvOES",
    /* 2267 */ "glMultiTexCoord3bOES",
    /* 2268 */ "glMultiTexCoord3bvOES",
    /* 2269 */ "glMultiTexCoord4bOES",
    /* 2270 */ "glMultiTexCoord4bvOES",
    /* 2271 */ "glTexCoord1bOES",
    /* 2272 */ "glTexCoord1bvOES",
    /* 2273 */ "glTexCoord2bOES",
    /* 2274 */ "glTexCoord2bvOES",
    /* 2275 */ "glTexCoord3bOES",
    /* 2276 */ "glTexCoord3bvOES",
    /* 2277 */ "glTexCoord4bOES",
    /* 2278 */ "glTexCoord4bvOES",
    /* 2279 */ "glVertex2bOES",
    /* 2280 */ "glVertex2bvOES",
    /* 2281 */ "glVertex3bOES",
    /* 2282 */ "glVertex3bvOES",
    /* 2283 */ "glVertex4bOES",
    /* 2284 */ "glVertex4bvOES",
    /* 2285 */ "glAlphaFuncxOES",
    /* 2286 */ "glClearColorxOES",
    /* 2287 */ "glClearDepthxOES",
    /* 2288 */ "glClipPlanexOES",
    /* 2289 */ "glColor4xOES",
    /* 2290 */ "glDepthRangexOES",
    /* 2291 */ "glFogxOES",
    /* 2292 */ "glFogxvOES",
    /* 2293 */ "glFrustumxOES",
    /* 2294 */ "glGetClipPlanexOES",
    /* 2295 */ "glGetFixedvOES",
    /* 2296 */ "glGetTexEnvxvOES",
    /* 2297 */ "glGetTexParameterxvOES",
    /* 2298 */ "glLightModelxOES",
    /* 2299 */ "glLightModelxvOES",
    /* 2300 */ "glLightxOES",
    /* 2301 */ "glLightxvOES",
    /* 2302 */ "glLineWidthxOES",
    /* 2303 */ "glLoadMatrixxOES",
    /* 2304 */ "glMaterialxOES",
    /* 2305 */ "glMaterialxvOES",
    /* 2306 */ "glMultMatrixxOES",
    /* 2307 */ "glMultiTexCoord4xOES",
    /* 2308 */ "glNormal3xOES",
    /* 2309 */ "glOrthoxOES",
    /* 2310 */ "glPointParameterxvOES",
    /* 2311 */ "glPointSizexOES",
    /* 2312 */ "glPolygonOffsetxOES",
    /* 2313 */ "glRotatexOES",
    /* 2314 */ "glScalexOES",
    /* 2315 */ "glTexEnvxOES",
    /* 2316 */ "glTexEnvxvOES",
    /* 2317 */ "glTexParameterxOES",
    /* 2318 */ "glTexParameterxvOES",
    /* 2319 */ "glTranslatexOES",
    /* 2320 */ "glAccumxOES",
    /* 2321 */ "glBitmapxOES",
    /* 2322 */ "glBlendColorxOES",
    /* 2323 */ "glClearAccumxOES",
    /* 2324 */ "glColor3xOES",
    /* 2325 */ "glColor3xvOES",
    /* 2326 */ "glColor4xvOES",
    /* 2327 */ "glConvolutionParameterxOES",
    /* 2328 */ "glConvolutionParameterxvOES",
    /* 2329 */ "glEvalCoord1xOES",
    /* 2330 */ "glEvalCoord1xvOES",
    /* 2331 */ "glEvalCoord2xOES",
    /* 2332 */ "glEvalCoord2xvOES",
    /* 2333 */ "glFeedbackBufferxOES",
    /* 2334 */ "glGetConvolutionParameterxvOES",
    /* 2335 */ "glGetHistogramParameterxvOES",
    /* 2336 */ "glGetLightxOES",
    /* 2337 */ "glGetMapxvOES",
    /* 2338 */ "glGetMaterialxOES",
    /* 2339 */ "glGetPixelMapxv",
    /* 2340 */ "glGetTexGenxvOES",
    /* 2341 */ "glGetTexLevelParameterxvOES",
    /* 2342 */ "glIndexxOES",
    /* 2343 */ "glIndexxvOES",
    /* 2344 */ "glLoadTransposeMatrixxOES",
    /* 2345 */ "glMap1xOES",
    /* 2346 */ "glMap2xOES",
    /* 2347 */ "glMapGrid1xOES",
    /* 2348 */ "glMapGrid2xOES",
    /* 2349 */ "glMultTransposeMatrixxOES",
    /* 2350 */ "glMultiTexCoord1xOES",
    /* 2351 */ "glMultiTexCoord1xvOES",
    /* 2352 */ "glMultiTexCoord2xOES",
    /* 2353 */ "glMultiTexCoord2xvOES",
    /* 2354 */ "glMultiTexCoord3xOES",
    /* 2355 */ "glMultiTexCoord3xvOES",
    /* 2356 */ "glMultiTexCoord4xvOES",
    /* 2357 */ "glNormal3xvOES",
    /* 2358 */ "glPassThroughxOES",
    /* 2359 */ "glPixelMapx",
    /* 2360 */ "glPixelStorex",
    /* 2361 */ "glPixelTransferxOES",
    /* 2362 */ "glPixelZoomxOES",
    /* 2363 */ "glPrioritizeTexturesxOES",
    /* 2364 */ "glRasterPos2xOES",
    /* 2365 */ "glRasterPos2xvOES",
    /* 2366 */ "glRasterPos3xOES",
    /* 2367 */ "glRasterPos3xvOES",
    /* 2368 */ "glRasterPos4xOES",
    /* 2369 */ "glRasterPos4xvOES",
    /* 2370 */ "glRectxOES",
    /* 2371 */ "glRectxvOES",
    /* 2372 */ "glTexCoord1xOES",
    /* 2373 */ "glTexCoord1xvOES",
    /* 2374 */ "glTexCoord2xOES",
    /* 2375 */ "glTexCoord2xvOES",
    /* 2376 */ "glTexCoord3xOES",
    /* 2377 */ "glTexCoord3xvOES",
    /* 2378 */ "glTexCoord4xOES",
    /* 2379 */ "glTexCoord4xvOES",
    /* 2380 */ "glTexGenxOES",
    /* 2381 */ "glTexGenxvOES",
    /* 2382 */ "glVertex2xOES",
    /* 2383 */ "glVertex2xvOES",
    /* 2384 */ "glVertex3xOES",
    /* 2385 */ "glVertex3xvOES",
    /* 2386 */ "glVertex4xOES",
    /* 2387 */ "glVertex4xvOES",
    /* 2388 */ "glQueryMatrixxOES",
    /* 2389 */ "glClearDepthfOES",
    /* 2390 */ "glClipPlanefOES",
    /* 2391 */ "glDepthRangefOES",
    /* 2392 */ "glFrustumfOES",
    /* 2393 */ "glGetClipPlanefOES",
    /* 2394 */ "glOrthofOES",
    /* 2395 */ "glFramebufferTextureMultiviewOVR",
    /* 2396 */ "glNamedFramebufferTextureMultiviewOVR",
    /* 2397 */ "glHintPGI",
    /* 2398 */ "glDetailTexFuncSGIS",
    /* 2399 */ "glGetDetailTexFuncSGIS",
    /* 2400 */ "glFogFuncSGIS",
    /* 2401 */ "glGetFogFuncSGIS",
    /* 2402 */ "glSampleMaskSGIS",
    /* 2403 */ "glSamplePatternSGIS",
    /* 2404 */ "glPixelTexGenParameteriSGIS",
    /* 2405 */ "glPixelTexGenParameterivSGIS",
    /* 2406 */ "glPixelTexGenParameterfSGIS",
    /* 2407 */ "glPixelTexGenParameterfvSGIS",
    /* 2408 */ "glGetPixelTexGenParameterivSGIS",
    /* 2409 */ "glGetPixelTexGenParameterfvSGIS",
    /* 2410 */ "glPointParameterfSGIS",
    /* 2411 */ "glPointParameterfvSGIS",
    /* 2412 */ "glSharpenTexFuncSGIS",
    /* 2413 */ "glGetSharpenTexFuncSGIS",
    /* 2414 */ "glTexImage4DSGIS",
    /* 2415 */ "glTexSubImage4DSGIS",
    /* 2416 */ "glTextureColorMaskSGIS",
    /* 2417 */ "glGetTexFilterFuncSGIS",
    /* 2418 */ "glTexFilterFuncSGIS",
    /* 2419 */ "glAsyncMarkerSGIX",
    /* 2420 */ "glFinishAsyncSGIX",
    /* 2421 */ "glPollAsyncSGIX",
    /* 2422 */ "glGenAsyncMarkersSGIX",
    /* 2423 */ "glDeleteAsyncMarkersSGIX",
    /* 2424 */ "glIsAsyncMarkerSGIX",
    /* 2425 */ "glFlushRasterSGIX",
    /* 2426 */ "glFragmentColorMaterialSGIX",
    /* 2427 */ "glFragmentLightfSGIX",
    /* 2428 */ "glFragmentLightfvSGIX",
    /* 2429 */ "glFragmentLightiSGIX",
    /* 2430 */ "glFragmentLightivSGIX",
    /* 2431 */ "glFragmentLightModelfSGIX",
    /* 2432 */ "glFragmentLightModelfvSGIX",
    /* 2433 */ "glFragmentLightModeliSGIX",
    /* 2434 */ "glFragmentLightModelivSGIX",
    /* 2435 */ "glFragmentMaterialfSGIX",
    /* 2436 */ "glFragmentMaterialfvSGIX",
    /* 2437 */ "glFragmentMaterialiSGIX",
    /* 2438 */ "glFragmentMaterialivSGIX",
    /* 2439 */ "glGetFragmentLightfvSGIX",
    /* 2440 */ "glGetFragmentLightivSGIX",
    /* 2441 */ "glGetFragmentMaterialfvSGIX",
    /* 2442 */ "glGetFragmentMaterialivSGIX",
    /* 2443 */ "glLightEnviSGIX",
    /* 2444 */ "glFrameZoomSGIX",
    /* 2445 */ "glIglooInterfaceSGIX",
    /* 2446 */ "glGetInstrumentsSGIX",
    /* 2447 */ "glInstrumentsBufferSGIX",
    /* 2448 */ "glPollInstrumentsSGIX",
    /* 2449 */ "glReadInstrumentsSGIX",
    /* 2450 */ "glStartInstrumentsSGIX",
    /* 2451 */ "glStopInstrumentsSGIX",
    /* 2452 */ "glGetListParameterfvSGIX",
    /* 2453 */ "glGetListParameterivSGIX",
    /* 2454 */ "glListParameterfSGIX",
    /* 2455 */ "glListParameterfvSGIX",
    /* 2456 */ "glListParameteriSGIX",
    /* 2457 */ "glListParameterivSGIX",
    /* 2458 */ "glPixelTexGenSGIX",
    /* 2459 */ "glDeformationMap3dSGIX",
    /* 2460 */ "glDeformationMap3fSGIX",
    /* 2461 */ "glDeformSGIX",
    /* 2462 */ "glLoadIdentityDeformationMapSGIX",
    /* 2463 */ "glReferencePlaneSGIX",
    /* 2464 */ "glSpriteParameterfSGIX",
    /* 2465 */ "glSpriteParameterfvSGIX",
    /* 2466 */ "glSpriteParameteriSGIX",
    /* 2467 */ "glSpriteParameterivSGIX",
    /* 2468 */ "glTagSampleBufferSGIX",
    /* 2469 */ "glColorTableSGI",
    /* 2470 */ "glColorTableParameterfvSGI",
    /* 2471 */ "glColorTableParameterivSGI",
    /* 2472 */ "glCopyColorTableSGI",
    /* 2473 */ "glGetColorTableSGI",
    /* 2474 */ "glGetColorTableParameterfvSGI",
    /* 2475 */ "glGetColorTableParameterivSGI",
    /* 2476 */ "glFinishTextureSUNX",
    /* 2477 */ "glGlobalAlphaFactorbSUN",
    /* 2478 */ "glGlobalAlphaFactorsSUN",
    /* 2479 */ "glGlobalAlphaFactoriSUN",
    /* 2480 */ "glGlobalAlphaFactorfSUN",
    /* 2481 */ "glGlobalAlphaFactordSUN",
    /* 2482 */ "glGlobalAlphaFactorubSUN",
    /* 2483 */ "glGlobalAlphaFactorusSUN",
    /* 2484 */ "glGlobalAlphaFactoruiSUN",
    /* 2485 */ "glDrawMeshArraysSUN",
    /* 2486 */ "glReplacementCodeuiSUN",
    /* 2487 */ "glReplacementCodeusSUN",
    /* 2488 */ "glReplacementCodeubSUN",
    /* 2489 */ "glReplacementCodeuivSUN",
    /* 2490 */ "glReplacementCodeusvSUN",
    /* 2491 */ "glReplacementCodeubvSUN",
    /* 2492 */ "glReplacementCodePointerSUN",
    /* 2493 */ "glColor4ubVertex2fSUN",
    /* 2494 */ "glColor4ubVertex2fvSUN",
    /* 2495 */ "glColor4ubVertex3fSUN",
    /* 2496 */ "glColor4ubVertex3fvSUN",
    /* 2497 */ "glColor3fVertex3fSUN",
    /* 2498 */ "glColor3fVertex3fvSUN",
    /* 2499 */ "glNormal3fVertex3fSUN",
    /* 2500 */ "glNormal3fVertex3fvSUN",
    /* 2501 */ "glColor4fNormal3fVertex3fSUN",
    /* 2502 */ "glColor4fNormal3fVertex3fvSUN",
    /* 2503 */ "glTexCoord2fVertex3fSUN",
    /* 2504 */ "glTexCoord2fVertex3fvSUN",
    /* 2505 */ "glTexCoord4fVertex4fSUN",
    /* 2506 */ "glTexCoord4fVertex4fvSUN",
    /* 2507 */ "glTexCoord2fColor4ubVertex3fSUN",
    /* 2508 */ "glTexCoord2fColor4ubVertex3fvSUN",
    /* 2509 */ "glTexCoord2fColor3fVertex3fSUN",
    /* 2510 */ "glTexCoord2fColor3fVertex3fvSUN",
    /* 2511 */ "glTexCoord2fNormal3fVertex3fSUN",
    /* 2512 */ "glTexCoord2fNormal3fVertex3fvSUN",
    /* 2513 */ "glTexCoord2fColor4fNormal3fVertex3fSUN",
    /* 2514 */ "glTexCoord2fColor4fNormal3fVertex3fvSUN",
    /* 2515 */ "glTexCoord4fColor4fNormal3fVertex4fSUN",
    /* 2516 */ "glTexCoord4fColor4fNormal3fVertex4fvSUN",
    /* 2517 */ "glReplacementCodeuiVertex3fSUN",
    /* 2518 */ "glReplacementCodeuiVertex3fvSUN",
    /* 2519 */ "glReplacementCodeuiColor4ubVertex3fSUN",
    /* 2520 */ "glReplacementCodeuiColor4ubVertex3fvSUN",
    /* 2521 */ "glReplacementCodeuiColor3fVertex3fSUN",
    /* 2522 */ "glReplacementCodeuiColor3fVertex3fvSUN",
    /* 2523 */ "glReplacementCodeuiNormal3fVertex3fSUN",
    /* 2524 */ "glReplacementCodeuiNormal3fVertex3fvSUN",
    /* 2525 */ "glReplacementCodeuiColor4fNormal3fVertex3fSUN",
    /* 2526 */ "glReplacementCodeuiColor4fNormal3fVertex3fvSUN",
    /* 2527 */ "glReplacementCodeuiTexCoord2fVertex3fSUN",
    /* 2528 */ "glReplacementCodeuiTexCoord2fVertex3fvSUN",
    /* 2529 */ "glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN",
    /* 2530 */ "glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN",
    /* 2531 */ "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN",
    /* 2532 */ "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN",
    /* 2533 */ "glTexImage2DExternalANGLE",
    /* 2534 */ "glInvalidateTextureANGLE",
    /* 2535 */ "glTexStorageMemFlags2DANGLE",
    /* 2536 */ "glTexStorageMemFlags2DMultisampleANGLE",
    /* 2537 */ "glTexStorageMemFlags3DANGLE",
    /* 2538 */ "glTexStorageMemFlags3DMultisampleANGLE",
    /* 2539 */ "glImportMemoryZirconHandleANGLE",
    /* 2540 */ "glImportSemaphoreZirconHandleANGLE",
    /* 2541 */ "glBlendBarrier",
    /* 2542 */ "glPrimitiveBoundingBox",
    /* 2543 */ "glBlitFramebufferANGLE",
    /* 2544 */ "glRenderbufferStorageMultisampleANGLE",
    /* 2545 */ "glDrawArraysInstancedANGLE",
    /* 2546 */ "glDrawElementsInstancedANGLE",
    /* 2547 */ "glVertexAttribDivisorANGLE",
    /* 2548 */ "glGetTranslatedShaderSourceANGLE",
    /* 2549 */ "glCopyTextureLevelsAPPLE",
    /* 2550 */ "glRenderbufferStorageMultisampleAPPLE",
    /* 2551 */ "glResolveMultisampleFramebufferAPPLE",
    /* 2552 */ "glFenceSyncAPPLE",
    /* 2553 */ "glIsSyncAPPLE",
    /* 2554 */ "glDeleteSyncAPPLE",
    /* 2555 */ "glClientWaitSyncAPPLE",
    /* 2556 */ "glWaitSyncAPPLE",
    /* 2557 */ "glGetInteger64vAPPLE",
    /* 2558 */ "glGetSyncivAPPLE",
    /* 2559 */ "glMaxActiveShaderCoresARM",
    /* 2560 */ "glDrawArraysInstancedBaseInstanceEXT",
    /* 2561 */ "glDrawElementsInstancedBaseInstanceEXT",
    /* 2562 */ "glDrawElementsInstancedBaseVertexBaseInstanceEXT",
    /* 2563 */ "glBindFragDataLocationIndexedEXT",
    /* 2564 */ "glGetProgramResourceLocationIndexEXT",
    /* 2565 */ "glGetFragDataIndexEXT",
    /* 2566 */ "glBufferStorageEXT",
    /* 2567 */ "glClearTexImageEXT",
    /* 2568 */ "glClearTexSubImageEXT",
    /* 2569 */ "glClipControlEXT",
    /* 2570 */ "glCopyImageSubDataEXT",
    /* 2571 */ "glDiscardFramebufferEXT",
    /* 2572 */ "glGenQueriesEXT",
    /* 2573 */ "glDeleteQueriesEXT",
    /* 2574 */ "glIsQueryEXT",
    /* 2575 */ "glBeginQueryEXT",
    /* 2576 */ "glEndQueryEXT",
    /* 2577 */ "glQueryCounterEXT",
    /* 2578 */ "glGetQueryivEXT",
    /* 2579 */ "glGetQueryObjectivEXT",
    /* 2580 */ "glGetQueryObjectuivEXT",
    /* 2581 */ "glGetInteger64vEXT",
    /* 2582 */ "glDrawBuffersEXT",
    /* 2583 */ "glEnableiEXT",
    /* 2584 */ "glDisableiEXT",
    /* 2585 */ "glBlendEquationiEXT",
    /* 2586 */ "glBlendEquationSeparateiEXT",
    /* 2587 */ "glBlendFunciEXT",
    /* 2588 */ "glBlendFuncSeparateiEXT",
    /* 2589 */ "glColorMaskiEXT",
    /* 2590 */ "glIsEnablediEXT",
    /* 2591 */ "glDrawElementsBaseVertexEXT",
    /* 2592 */ "glDrawRangeElementsBaseVertexEXT",
    /* 2593 */ "glDrawElementsInstancedBaseVertexEXT",
    /* 2594 */ "glMultiDrawElementsBaseVertexEXT",
    /* 2595 */ "glDrawTransformFeedbackEXT",
    /* 2596 */ "glDrawTransformFeedbackInstancedEXT",
    /* 2597 */ "glGetFragmentShadingRatesEXT",
    /* 2598 */ "glShadingRateEXT",
    /* 2599 */ "glShadingRateCombinerOpsEXT",
    /* 2600 */ "glFramebufferShadingRateEXT",
    /* 2601 */ "glVertexAttribDivisorEXT",
    /* 2602 */ "glMapBufferRangeEXT",
    /* 2603 */ "glFlushMappedBufferRangeEXT",
    /* 2604 */ "glMultiDrawArraysIndirectEXT",
    /* 2605 */ "glMultiDrawElementsIndirectEXT",
    /* 2606 */ "glFramebufferTexture2DMultisampleEXT",
    /* 2607 */ "glReadBufferIndexedEXT",
    /* 2608 */ "glDrawBuffersIndexedEXT",
    /* 2609 */ "glGetIntegeri_vEXT",
    /* 2610 */ "glPrimitiveBoundingBoxEXT",
    /* 2611 */ "glGetGraphicsResetStatusEXT",
    /* 2612 */ "glReadnPixelsEXT",
    /* 2613 */ "glGetnUniformfvEXT",
    /* 2614 */ "glGetnUniformivEXT",
    /* 2615 */ "glActiveShaderProgramEXT",
    /* 2616 */ "glBindProgramPipelineEXT",
    /* 2617 */ "glCreateShaderProgramvEXT",
    /* 2618 */ "glDeleteProgramPipelinesEXT",
    /* 2619 */ "glGenProgramPipelinesEXT",
    /* 2620 */ "glGetProgramPipelineInfoLogEXT",
    /* 2621 */ "glGetProgramPipelineivEXT",
    /* 2622 */ "glIsProgramPipelineEXT",
    /* 2623 */ "glUseProgramStagesEXT",
    /* 2624 */ "glValidateProgramPipelineEXT",
    /* 2625 */ "glFramebufferPixelLocalStorageSizeEXT",
    /* 2626 */ "glGetFramebufferPixelLocalStorageSizeEXT",
    /* 2627 */ "glClearPixelLocalStorageuiEXT",
    /* 2628 */ "glTexPageCommitmentEXT",
    /* 2629 */ "glPatchParameteriEXT",
    /* 2630 */ "glSamplerParameterIivEXT",
    /* 2631 */ "glSamplerParameterIuivEXT",
    /* 2632 */ "glGetSamplerParameterIivEXT",
    /* 2633 */ "glGetSamplerParameterIuivEXT",
    /* 2634 */ "glTexBufferRangeEXT",
    /* 2635 */ "glTexStorageAttribs2DEXT",
    /* 2636 */ "glTexStorageAttribs3DEXT",
    /* 2637 */ "glTextureViewEXT",
    /* 2638 */ "glGetTextureHandleIMG",
    /* 2639 */ "glGetTextureSamplerHandleIMG",
    /* 2640 */ "glUniformHandleui64IMG",
    /* 2641 */ "glUniformHandleui64vIMG",
    /* 2642 */ "glProgramUniformHandleui64IMG",
    /* 2643 */ "glProgramUniformHandleui64vIMG",
    /* 2644 */ "glFramebufferTexture2DDownsampleIMG",
    /* 2645 */ "glFramebufferTextureLayerDownsampleIMG",
    /* 2646 */ "glRenderbufferStorageMultisampleIMG",
    /* 2647 */ "glFramebufferTexture2DMultisampleIMG",
    /* 2648 */ "glDebugMessageControlKHR",
    /* 2649 */ "glDebugMessageInsertKHR",
    /* 2650 */ "glDebugMessageCallbackKHR",
    /* 2651 */ "glGetDebugMessageLogKHR",
    /* 2652 */ "glPushDebugGroupKHR",
    /* 2653 */ "glPopDebugGroupKHR",
    /* 2654 */ "glObjectLabelKHR",
    /* 2655 */ "glGetObjectLabelKHR",
    /* 2656 */ "glObjectPtrLabelKHR",
    /* 2657 */ "glGetObjectPtrLabelKHR",
    /* 2658 */ "glGetPointervKHR",
    /* 2659 */ "glGetGraphicsResetStatusKHR",
    /* 2660 */ "glReadnPixelsKHR",
    /* 2661 */ "glGetnUniformfvKHR",
    /* 2662 */ "glGetnUniformivKHR",
    /* 2663 */ "glGetnUniformuivKHR",
    /* 2664 */ "glCopyBufferSubDataNV",
    /* 2665 */ "glCoverageMaskNV",
    /* 2666 */ "glCoverageOperationNV",
    /* 2667 */ "glDrawBuffersNV",
    /* 2668 */ "glDrawArraysInstancedNV",
    /* 2669 */ "glDrawElementsInstancedNV",
    /* 2670 */ "glBlitFramebufferNV",
    /* 2671 */ "glRenderbufferStorageMultisampleNV",
    /* 2672 */ "glVertexAttribDivisorNV",
    /* 2673 */ "glUniformMatrix2x3fvNV",
    /* 2674 */ "glUniformMatrix3x2fvNV",
    /* 2675 */ "glUniformMatrix2x4fvNV",
    /* 2676 */ "glUniformMatrix4x2fvNV",
    /* 2677 */ "glUniformMatrix3x4fvNV",
    /* 2678 */ "glUniformMatrix4x3fvNV",
    /* 2679 */ "glPolygonModeNV",
    /* 2680 */ "glReadBufferNV",
    /* 2681 */ "glViewportArrayvNV",
    /* 2682 */ "glViewportIndexedfNV",
    /* 2683 */ "glViewportIndexedfvNV",
    /* 2684 */ "glScissorArrayvNV",
    /* 2685 */ "glScissorIndexedNV",
    /* 2686 */ "glScissorIndexedvNV",
    /* 2687 */ "glDepthRangeArrayfvNV",
    /* 2688 */ "glDepthRangeIndexedfNV",
    /* 2689 */ "glGetFloati_vNV",
    /* 2690 */ "glEnableiNV",
    /* 2691 */ "glDisableiNV",
    /* 2692 */ "glIsEnablediNV",
    /* 2693 */ "glEGLImageTargetTexture2DOES",
    /* 2694 */ "glEGLImageTargetRenderbufferStorageOES",
    /* 2695 */ "glCopyImageSubDataOES",
    /* 2696 */ "glEnableiOES",
    /* 2697 */ "glDisableiOES",
    /* 2698 */ "glBlendEquationiOES",
    /* 2699 */ "glBlendEquationSeparateiOES",
    /* 2700 */ "glBlendFunciOES",
    /* 2701 */ "glBlendFuncSeparateiOES",
    /* 2702 */ "glColorMaskiOES",
    /* 2703 */ "glIsEnablediOES",
    /* 2704 */ "glDrawElementsBaseVertexOES",
    /* 2705 */ "glDrawRangeElementsBaseVertexOES",
    /* 2706 */ "glDrawElementsInstancedBaseVertexOES",
    /* 2707 */ "glFramebufferTextureOES",
    /* 2708 */ "glGetProgramBinaryOES",
    /* 2709 */ "glProgramBinaryOES",
    /* 2710 */ "glMapBufferOES",
    /* 2711 */ "glUnmapBufferOES",
    /* 2712 */ "glGetBufferPointervOES",
    /* 2713 */ "glPrimitiveBoundingBoxOES",
    /* 2714 */ "glMinSampleShadingOES",
    /* 2715 */ "glPatchParameteriOES",
    /* 2716 */ "glTexImage3DOES",
    /* 2717 */ "glTexSubImage3DOES",
    /* 2718 */ "glCopyTexSubImage3DOES",
    /* 2719 */ "glCompressedTexImage3DOES",
    /* 2720 */ "glCompressedTexSubImage3DOES",
    /* 2721 */ "glFramebufferTexture3DOES",
    /* 2722 */ "glTexParameterIivOES",
    /* 2723 */ "glTexParameterIuivOES",
    /* 2724 */ "glGetTexParameterIivOES",
    /* 2725 */ "glGetTexParameterIuivOES",
    /* 2726 */ "glSamplerParameterIivOES",
    /* 2727 */ "glSamplerParameterIuivOES",
    /* 2728 */ "glGetSamplerParameterIivOES",
    /* 2729 */ "glGetSamplerParameterIuivOES",
    /* 2730 */ "glTexBufferOES",
    /* 2731 */ "glTexBufferRangeOES",
    /* 2732 */ "glTexStorage3DMultisampleOES",
    /* 2733 */ "glTextureViewOES",
    /* 2734 */ "glBindVertexArrayOES",
    /* 2735 */ "glDeleteVertexArraysOES",
    /* 2736 */ "glGenVertexArraysOES",
    /* 2737 */ "glIsVertexArrayOES",
    /* 2738 */ "glViewportArrayvOES",
    /* 2739 */ "glViewportIndexedfOES",
    /* 2740 */ "glViewportIndexedfvOES",
    /* 2741 */ "glScissorArrayvOES",
    /* 2742 */ "glScissorIndexedOES",
    /* 2743 */ "glScissorIndexedvOES",
    /* 2744 */ "glDepthRangeArrayfvOES",
    /* 2745 */ "glDepthRangeIndexedfOES",
    /* 2746 */ "glGetFloati_vOES",
    /* 2747 */ "glFramebufferTextureMultisampleMultiviewOVR",
    /* 2748 */ "glAlphaFuncQCOM",
    /* 2749 */ "glGetDriverControlsQCOM",
    /* 2750 */ "glGetDriverControlStringQCOM",
    /* 2751 */ "glEnableDriverControlQCOM",
    /* 2752 */ "glDisableDriverControlQCOM",
    /* 2753 */ "glExtGetTexturesQCOM",
    /* 2754 */ "glExtGetBuffersQCOM",
    /* 2755 */ "glExtGetRenderbuffersQCOM",
    /* 2756 */ "glExtGetFramebuffersQCOM",
    /* 2757 */ "glExtGetTexLevelParameterivQCOM",
    /* 2758 */ "glExtTexObjectStateOverrideiQCOM",
    /* 2759 */ "glExtGetTexSubImageQCOM",
    /* 2760 */ "glExtGetBufferPointervQCOM",
    /* 2761 */ "glExtGetShadersQCOM",
    /* 2762 */ "glExtGetProgramsQCOM",
    /* 2763 */ "glExtIsProgramBinaryQCOM",
    /* 2764 */ "glExtGetProgramBinarySourceQCOM",
    /* 2765 */ "glFramebufferFoveationConfigQCOM",
    /* 2766 */ "glFramebufferFoveationParametersQCOM",
    /* 2767 */ "glTexEstimateMotionQCOM",
    /* 2768 */ "glTexEstimateMotionRegionsQCOM",
    /* 2769 */ "glExtrapolateTex2DQCOM",
    /* 2770 */ "glTextureFoveationParametersQCOM",
    /* 2771 */ "glFramebufferFetchBarrierQCOM",
    /* 2772 */ "glShadingRateQCOM",
    /* 2773 */ "glStartTilingQCOM",
    /* 2774 */ "glEndTilingQCOM",
    /* 2775 */ "glBindUniformLocationCHROMIUM",
    /* 2776 */ "glCoverageModulationCHROMIUM",
    /* 2777 */ "glCopyTextureCHROMIUM",
    /* 2778 */ "glCopySubTextureCHROMIUM",
    /* 2779 */ "glCompressedCopyTextureCHROMIUM",
    /* 2780 */ "glRequestExtensionANGLE",
    /* 2781 */ "glDisableExtensionANGLE",
    /* 2782 */ "glAcquireTexturesANGLE",
    /* 2783 */ "glReleaseTexturesANGLE",
    /* 2784 */ "glGetBooleanvRobustANGLE",
    /* 2785 */ "glGetBufferParameterivRobustANGLE",
    /* 2786 */ "glGetBufferParameteri64vRobustANGLE",
    /* 2787 */ "glGetFloatvRobustANGLE",
    /* 2788 */ "glGetFramebufferAttachmentParameterivRobustANGLE",
    /* 2789 */ "glGetIntegervRobustANGLE",
    /* 2790 */ "glGetProgramivRobustANGLE",
    /* 2791 */ "glGetRenderbufferParameterivRobustANGLE",
    /* 2792 */ "glGetShaderivRobustANGLE",
    /* 2793 */ "glGetTexParameterfvRobustANGLE",
    /* 2794 */ "glGetTexParameterivRobustANGLE",
    /* 2795 */ "glGetUniformfvRobustANGLE",
    /* 2796 */ "glGetUniformivRobustANGLE",
    /* 2797 */ "glGetVertexAttribfvRobustANGLE",
    /* 2798 */ "glGetVertexAttribivRobustANGLE",
    /* 2799 */ "glGetVertexAttribPointervRobustANGLE",
    /* 2800 */ "glReadPixelsRobustANGLE",
    /* 2801 */ "glTexImage2DRobustANGLE",
    /* 2802 */ "glTexParameterfvRobustANGLE",
    /* 2803 */ "glTexParameterivRobustANGLE",
    /* 2804 */ "glTexSubImage2DRobustANGLE",
    /* 2805 */ "glTexImage3DRobustANGLE",
    /* 2806 */ "glTexSubImage3DRobustANGLE",
    /* 2807 */ "glCompressedTexImage2DRobustANGLE",
    /* 2808 */ "glCompressedTexSubImage2DRobustANGLE",
    /* 2809 */ "glCompressedTexImage3DRobustANGLE",
    /* 2810 */ "glCompressedTexSubImage3DRobustANGLE",
    /* 2811 */ "glGetQueryivRobustANGLE",
    /* 2812 */ "glGetQueryObjectuivRobustANGLE",
    /* 2813 */ "glGetBufferPointervRobustANGLE",
    /* 2814 */ "glGetIntegeri_vRobustANGLE",
    /* 2815 */ "glGetInternalformativRobustANGLE",
    /* 2816 */ "glGetVertexAttribIivRobustANGLE",
    /* 2817 */ "glGetVertexAttribIuivRobustANGLE",
    /* 2818 */ "glGetUniformuivRobustANGLE",
    /* 2819 */ "glGetActiveUniformBlockivRobustANGLE",
    /* 2820 */ "glGetInteger64vRobustANGLE",
    /* 2821 */ "glGetInteger64i_vRobustANGLE",
    /* 2822 */ "glSamplerParameterivRobustANGLE",
    /* 2823 */ "glSamplerParameterfvRobustANGLE",
    /* 2824 */ "glGetSamplerParameterivRobustANGLE",
    /* 2825 */ "glGetSamplerParameterfvRobustANGLE",
    /* 2826 */ "glGetFramebufferParameterivRobustANGLE",
    /* 2827 */ "glGetProgramInterfaceivRobustANGLE",
    /* 2828 */ "glGetBooleani_vRobustANGLE",
    /* 2829 */ "glGetMultisamplefvRobustANGLE",
    /* 2830 */ "glGetTexLevelParameterivRobustANGLE",
    /* 2831 */ "glGetTexLevelParameterfvRobustANGLE",
    /* 2832 */ "glGetPointervRobustANGLERobustANGLE",
    /* 2833 */ "glReadnPixelsRobustANGLE",
    /* 2834 */ "glGetnUniformfvRobustANGLE",
    /* 2835 */ "glGetnUniformivRobustANGLE",
    /* 2836 */ "glGetnUniformuivRobustANGLE",
    /* 2837 */ "glTexParameterIivRobustANGLE",
    /* 2838 */ "glTexParameterIuivRobustANGLE",
    /* 2839 */ "glGetTexParameterIivRobustANGLE",
    /* 2840 */ "glGetTexParameterIuivRobustANGLE",
    /* 2841 */ "glSamplerParameterIivRobustANGLE",
    /* 2842 */ "glSamplerParameterIuivRobustANGLE",
    /* 2843 */ "glGetSamplerParameterIivRobustANGLE",
    /* 2844 */ "glGetSamplerParameterIuivRobustANGLE",
    /* 2845 */ "glGetQueryObjectivRobustANGLE",
    /* 2846 */ "glGetQueryObjecti64vRobustANGLE",
    /* 2847 */ "glGetQueryObjectui64vRobustANGLE",
    /* 2848 */ "glGetFramebufferPixelLocalStorageParameterfvRobustANGLE",
    /* 2849 */ "glGetFramebufferPixelLocalStorageParameterivRobustANGLE",
    /* 2850 */ "glCopyTexture3DANGLE",
    /* 2851 */ "glCopySubTexture3DANGLE",
    /* 2852 */ "glTexStorage2DMultisampleANGLE",
    /* 2853 */ "glGetMultisamplefvANGLE",
    /* 2854 */ "glSampleMaskiANGLE",
    /* 2855 */ "glMultiDrawArraysANGLE",
    /* 2856 */ "glMultiDrawArraysInstancedANGLE",
    /* 2857 */ "glMultiDrawElementsANGLE",
    /* 2858 */ "glMultiDrawElementsInstancedANGLE",
    /* 2859 */ "glDrawArraysInstancedBaseInstanceANGLE",
    /* 2860 */ "glDrawElementsInstancedBaseVertexBaseInstanceANGLE",
    /* 2861 */ "glMultiDrawArraysInstancedBaseInstanceANGLE",
    /* 2862 */ "glMultiDrawElementsInstancedBaseVertexBaseInstanceANGLE",
    /* 2863 */ "glPolygonModeANGLE",
    /* 2864 */ "glProvokingVertexANGLE",
    /* 2865 */ "glLoseContextCHROMIUM",
    /* 2866 */ "glGetTexImageANGLE",
    /* 2867 */ "glGetCompressedTexImageANGLE",
    /* 2868 */ "glGetRenderbufferImageANGLE",
    /* 2869 */ "glGetTexLevelParameterfvANGLE",
    /* 2870 */ "glGetTexLevelParameterivANGLE",
    /* 2871 */ "glFramebufferMemorylessPixelLocalStorageANGLE",
    /* 2872 */ "glFramebufferTexturePixelLocalStorageANGLE",
    /* 2873 */ "glFramebufferPixelLocalClearValuefvANGLE",
    /* 2874 */ "glFramebufferPixelLocalClearValueivANGLE",
    /* 2875 */ "glFramebufferPixelLocalClearValueuivANGLE",
    /* 2876 */ "glBeginPixelLocalStorageANGLE",
    /* 2877 */ "glEndPixelLocalStorageANGLE",
    /* 2878 */ "glPixelLocalStorageBarrierANGLE",
    /* 2879 */ "glFramebufferPixelLocalStorageInterruptANGLE",
    /* 2880 */ "glFramebufferPixelLocalStorageRestoreANGLE",
    /* 2881 */ "glGetFramebufferPixelLocalStorageParameterfvANGLE",
    /* 2882 */ "glGetFramebufferPixelLocalStorageParameterivANGLE",
    /* 2883 */ "glLogicOpANGLE",
    /* 2884 */ "glBlobCacheCallbacksANGLE",
    /* 2885 */ "glGetPointervANGLE"
};

static const GladPfnRange_t GLAD_GL_feature_pfn_ranges[] = {
    /* GL_VERSION_1_0 */
    {    0,    0,   48 },

    /* GL_VERSION_1_1 */
    {    1,   48,   14 },

    /* GL_VERSION_1_2 */
    {    2,   62,    4 },

    /* GL_VERSION_1_3 */
    {    3,   66,    9 },

    /* GL_VERSION_1_4 */
    {    4,   75,    9 },

    /* GL_VERSION_1_5 */
    {    5,   84,   19 },

    /* GL_VERSION_2_0 */
    {    6,  103,   93 },

    /* GL_VERSION_2_1 */
    {    7,  196,    6 },

    /* GL_VERSION_3_0 */
    {    8,  202,   84 },

    /* GL_VERSION_3_1 */
    {    9,  204,    1 },
    {    9,  210,    2 },
    {    9,  286,   12 },

    /* GL_VERSION_3_2 */
    {   10,  298,   19 },

    /* GL_VERSION_3_3 */
    {   11,  317,   28 },

    /* GL_VERSION_4_0 */
    {   12,  345,   46 },

    /* GL_VERSION_4_1 */
    {   13,  391,   88 },

    /* GL_VERSION_4_2 */
    {   14,  479,   12 },

    /* GL_VERSION_4_3 */
    {   15,   50,    1 },
    {   15,  491,   43 },

    /* GL_VERSION_4_4 */
    {   16,  534,    9 },

    /* GL_VERSION_4_5 */
    {   17,  543,  110 },

    /* GL_VERSION_4_6 */
    {   18,  653,    4 },

    /* GL_ES_VERSION_2_0 */
    {   19,    0,    4 },
    {   19,    6,    5 },
    {   19,   12,    1 },
    {   19,   14,    3 },
    {   19,   18,    8 },
    {   19,   27,    3 },
    {   19,   31,    1 },
    {   19,   33,    2 },
    {   19,   36,    4 },
    {   19,   41,    2 },
    {   19,   45,    1 },
    {   19,   47,    3 },
    {   19,   51,    1 },
    {   19,   53,    1 },
    {   19,   55,    1 },
    {   19,   57,    5 },
    {   19,   66,    2 },
    {   19,   69,    1 },
    {   19,   72,    1 },
    {   19,   75,    1 },
    {   19,   82,    2 },
    {   19,   92,    6 },
    {   19,  101,    1 },
    {   19,  103,    1 },
    {   19,  105,   25 },
    {   19,  131,   28 },
    {   19,  161,    2 },
    {   19,  167,    2 },
    {   19,  173,    2 },
    {   19,  187,    2 },
    {   19,  195,    1 },
    {   19,  260,   11 },
    {   19,  272,    1 },
    {   19,  274,    3 },
    {   19,  391,    5 },

    /* GL_ES_VERSION_3_0 */
    {   20,   32,    1 },
    {   20,   62,    4 },
    {   20,   68,    1 },
    {   20,   71,    1 },
    {   20,   84,    6 },
    {   20,   91,    1 },
    {   20,  100,    1 },
    {   20,  102,    1 },
    {   20,  104,    1 },
    {   20,  196,    6 },
    {   20,  204,    1 },
    {   20,  208,    6 },
    {   20,  217,    3 },
    {   20,  223,    1 },
    {   20,  227,    1 },
    {   20,  231,    1 },
    {   20,  235,    1 },
    {   20,  240,    1 },
    {   20,  242,    9 },
    {   20,  255,    5 },
    {   20,  277,   11 },
    {   20,  290,    3 },
    {   20,  294,    4 },
    {   20,  303,    9 },
    {   20,  319,    8 },
    {   20,  329,    1 },
    {   20,  331,    1 },
    {   20,  336,    1 },
    {   20,  380,    6 },
    {   20,  396,    3 },
    {   20,  482,    1 },
    {   20,  487,    2 },
    {   20,  503,    2 },

    /* GL_ES_VERSION_3_1 */
    {   21,   43,    2 },
    {   21,  203,    1 },
    {   21,  315,    2 },
    {   21,  350,    2 },
    {   21,  399,   12 },
    {   21,  413,    6 },
    {   21,  421,    6 },
    {   21,  429,    6 },
    {   21,  437,    5 },
    {   21,  445,    6 },
    {   21,  457,    2 },
    {   21,  484,    2 },
    {   21,  493,    2 },
    {   21,  496,    2 },
    {   21,  507,    5 },
    {   21,  515,    1 },
    {   21,  518,    3 },
    {   21,  522,    2 },
    {   21,  641,    1 },

    /* GL_ES_VERSION_3_2 */
    {   22,   50,    1 },
    {   22,  202,    1 },
    {   22,  205,    3 },
    {   22,  251,    4 },
    {   22,  288,    1 },
    {   22,  298,    3 },
    {   22,  312,    1 },
    {   22,  327,    2 },
    {   22,  330,    1 },
    {   22,  332,    1 },
    {   22,  345,    5 },
    {   22,  378,    1 },
    {   22,  495,    1 },
    {   22,  514,    1 },
    {   22,  516,    1 },
    {   22,  524,   10 },
    {   22,  644,    1 },
    {   22,  648,    4 },
    {   22, 2541,    2 },
};

static const GladPfnRange_t GLAD_GL_ext_pfn_ranges[] = {
    /* GL_3DFX_tbuffer */
    {    1,  657,    1 },

    /* GL_AMD_debug_output */
    {    7,  658,    4 },

    /* GL_AMD_draw_buffers_blend */
    {    9,  662,    4 },

    /* GL_AMD_framebuffer_multisample_advanced */
    {   10,  666,    2 },

    /* GL_AMD_framebuffer_sample_positions */
    {   11,  668,    4 },

    /* GL_AMD_gpu_shader_int64 */
    {   15,  672,   34 },

    /* GL_AMD_interleaved_elements */
    {   16,  706,    1 },

    /* GL_AMD_multi_draw_indirect */
    {   17,  707,    2 },

    /* GL_AMD_name_gen_delete */
    {   18,  709,    3 },

    /* GL_AMD_occlusion_query_event */
    {   19,  712,    1 },

    /* GL_AMD_performance_monitor */
    {   20,  713,   11 },

    /* GL_AMD_sample_positions */
    {   24,  724,    1 },

    /* GL_AMD_sparse_texture */
    {   34,  725,    2 },

    /* GL_AMD_stencil_operation_extended */
    {   35,  727,    1 },

    /* GL_AMD_vertex_shader_tessellator */
    {   41,  728,    2 },

    /* GL_ANGLE_base_vertex_base_instance */
    {   44, 2859,    4 },

    /* GL_ANGLE_blob_cache */
    {   45, 2884,    2 },

    /* GL_ANGLE_copy_texture_3d */
    {   48, 2850,    2 },

    /* GL_ANGLE_framebuffer_blit */
    {   50, 2543,    1 },

    /* GL_ANGLE_framebuffer_multisample */
    {   51, 2544,    1 },

    /* GL_ANGLE_get_image */
    {   52, 2866,    3 },

    /* GL_ANGLE_get_tex_level_parameter */
    {   54, 2869,    2 },

    /* GL_ANGLE_instanced_arrays */
    {   55, 2545,    3 },

    /* GL_ANGLE_logic_op */
    {   56, 2883,    1 },

    /* GL_ANGLE_memory_object_flags */
    {   58, 2535,    4 },

    /* GL_ANGLE_memory_object_fuchsia */
    {   59, 2539,    1 },

    /* GL_ANGLE_multi_draw */
    {   61, 2855,    4 },

    /* GL_ANGLE_polygon_mode */
    {   63, 2863,    1 },

    /* GL_ANGLE_provoking_vertex */
    {   67, 2864,    1 },

    /* GL_ANGLE_request_extension */
    {   69, 2780,    2 },

    /* GL_ANGLE_robust_client_memory */
    {   71, 2784,   66 },

    /* GL_ANGLE_semaphore_fuchsia */
    {   74, 2540,    1 },

    /* GL_ANGLE_shader_pixel_local_storage */
    {   76, 2871,   12 },

    /* GL_ANGLE_texture_external_update */
    {   81, 2533,    2 },

    /* GL_ANGLE_texture_multisample */
    {   82, 2852,    3 },

    /* GL_ANGLE_translated_shader_source */
    {   84, 2548,    1 },

    /* GL_ANGLE_vulkan_image */
    {   85, 2782,    2 },

    /* GL_APPLE_copy_texture_levels */
    {   91, 2549,    1 },

    /* GL_APPLE_element_array */
    {   92,  730,    5 },

    /* GL_APPLE_fence */
    {   93,  735,    8 },

    /* GL_APPLE_flush_buffer_range */
    {   95,  743,    2 },

    /* GL_APPLE_framebuffer_multisample */
    {   96, 2550,    2 },

    /* GL_APPLE_object_purgeable */
    {   97,  745,    3 },

    /* GL_APPLE_sync */
    {  101, 2552,    7 },

    /* GL_APPLE_texture_range */
    {  105,  748,    2 },

    /* GL_APPLE_vertex_array_object */
    {  107,  750,    4 },

    /* GL_APPLE_vertex_array_range */
    {  108,  754,    3 },

    /* GL_APPLE_vertex_program_evaluators */
    {  109,  757,    7 },

    /* GL_ARB_ES2_compatibility */
    {  111,  391,    5 },

    /* GL_ARB_ES3_1_compatibility */
    {  112,  641,    1 },

    /* GL_ARB_ES3_2_compatibility */
    {  113,  764,    1 },

    /* GL_ARB_base_instance */
    {  116,  479,    3 },

    /* GL_ARB_bindless_texture */
    {  117,  765,   16 },

    /* GL_ARB_blend_func_extended */
    {  118,  317,    2 },

    /* GL_ARB_buffer_storage */
    {  119,  534,    1 },

    /* GL_ARB_cl_event */
    {  120,  781,    1 },

    /* GL_ARB_clear_buffer_object */
    {  121,  491,    2 },

    /* GL_ARB_clear_texture */
    {  122,  535,    2 },

    /* GL_ARB_clip_control */
    {  123,  543,    1 },

    /* GL_ARB_color_buffer_float */
    {  124,  782,    1 },

    /* GL_ARB_compute_shader */
    {  127,  493,    2 },

    /* GL_ARB_compute_variable_group_size */
    {  128,  783,    1 },

    /* GL_ARB_copy_buffer */
    {  131,  290,    1 },

    /* GL_ARB_copy_image */
    {  132,  495,    1 },

    /* GL_ARB_debug_output */
    {  134,  784,    4 },

    /* GL_ARB_direct_state_access */
    {  139,  544,   97 },

    /* GL_ARB_draw_buffers */
    {  140,  788,    1 },

    /* GL_ARB_draw_buffers_blend */
    {  141,  789,    4 },

    /* GL_ARB_draw_elements_base_vertex */
    {  142,  298,    4 },

    /* GL_ARB_draw_indirect */
    {  143,  350,    2 },

    /* GL_ARB_draw_instanced */
    {  144,  793,    2 },

    /* GL_ARB_fragment_program */
    {  150,  795,   19 },

    /* GL_ARB_framebuffer_no_attachments */
    {  154,  496,    2 },

    /* GL_ARB_framebuffer_object */
    {  155,  260,   20 },

    /* GL_ARB_geometry_shader4 */
    {  157,  814,    4 },

    /* GL_ARB_get_program_binary */
    {  158,  396,    3 },

    /* GL_ARB_get_texture_sub_image */
    {  159,  642,    2 },

    /* GL_ARB_gl_spirv */
    {  160,  818,    1 },

    /* GL_ARB_gpu_shader_fp64 */
    {  162,  352,   18 },

    /* GL_ARB_gpu_shader_int64 */
    {  163,  819,   36 },

    /* GL_ARB_imaging */
    {  166,   82,    2 },

    /* GL_ARB_indirect_parameters */
    {  167,  855,    2 },

    /* GL_ARB_instanced_arrays */
    {  168,  857,    1 },

    /* GL_ARB_internalformat_query */
    {  169,  482,    1 },

    /* GL_ARB_internalformat_query2 */
    {  170,  498,    1 },

    /* GL_ARB_invalidate_subdata */
    {  171,  499,    6 },

    /* GL_ARB_map_buffer_range */
    {  173,  280,    2 },

    /* GL_ARB_matrix_palette */
    {  174,  858,    5 },

    /* GL_ARB_multi_bind */
    {  175,  537,    6 },

    /* GL_ARB_multi_draw_indirect */
    {  176,  505,    2 },

    /* GL_ARB_multisample */
    {  177,  863,    1 },

    /* GL_ARB_multitexture */
    {  178,  864,   34 },

    /* GL_ARB_occlusion_query */
    {  179,  898,    8 },

    /* GL_ARB_parallel_shader_compile */
    {  181,  906,    1 },

    /* GL_ARB_point_parameters */
    {  184,  907,    2 },

    /* GL_ARB_polygon_offset_clamp */
    {  186,  656,    1 },

    /* GL_ARB_program_interface_query */
    {  188,  507,    6 },

    /* GL_ARB_provoking_vertex */
    {  189,  302,    1 },

    /* GL_ARB_robustness */
    {  192,  909,    8 },

    /* GL_ARB_sample_locations */
    {  194,  917,    3 },

    /* GL_ARB_sample_shading */
    {  195,  920,    1 },

    /* GL_ARB_sampler_objects */
    {  196,  319,   14 },

    /* GL_ARB_separate_shader_objects */
    {  199,  398,   61 },

    /* GL_ARB_shader_atomic_counters */
    {  201,  483,    1 },

    /* GL_ARB_shader_image_load_store */
    {  207,  484,    2 },

    /* GL_ARB_shader_objects */
    {  209,  921,   39 },

    /* GL_ARB_shader_storage_buffer_object */
    {  212,  513,    1 },

    /* GL_ARB_shader_subroutine */
    {  213,  370,    8 },

    /* GL_ARB_shading_language_include */
    {  219,  960,    6 },

    /* GL_ARB_sparse_buffer */
    {  223,  966,    3 },

    /* GL_ARB_sparse_texture */
    {  224,  969,    1 },

    /* GL_ARB_sync */
    {  229,  303,    7 },

    /* GL_ARB_tessellation_shader */
    {  230,  378,    2 },

    /* GL_ARB_texture_barrier */
    {  231,  652,    1 },

    /* GL_ARB_texture_buffer_object */
    {  233,  970,    1 },

    /* GL_ARB_texture_buffer_range */
    {  235,  514,    1 },

    /* GL_ARB_texture_compression */
    {  236,  971,    7 },

    /* GL_ARB_texture_multisample */
    {  251,  313,    4 },

    /* GL_ARB_texture_storage */
    {  259,  486,    3 },

    /* GL_ARB_texture_storage_multisample */
    {  260,  515,    2 },

    /* GL_ARB_texture_view */
    {  262,  517,    1 },

    /* GL_ARB_timer_query */
    {  263,  333,    3 },

    /* GL_ARB_transform_feedback2 */
    {  264,  380,    7 },

    /* GL_ARB_transform_feedback3 */
    {  265,  387,    4 },

    /* GL_ARB_transform_feedback_instanced */
    {  266,  489,    2 },

    /* GL_ARB_transpose_matrix */
    {  268,  978,    4 },

    /* GL_ARB_uniform_buffer_object */
    {  269,  204,    1 },
    {  269,  210,    2 },
    {  269,  291,    7 },

    /* GL_ARB_vertex_array_object */
    {  271,  282,    4 },

    /* GL_ARB_vertex_attrib_64bit */
    {  272,  459,   10 },

    /* GL_ARB_vertex_attrib_binding */
    {  273,  518,    6 },

    /* GL_ARB_vertex_blend */
    {  274,  982,   10 },

    /* GL_ARB_vertex_buffer_object */
    {  275,  992,   11 },

    /* GL_ARB_vertex_program */
    {  276,  795,   19 },
    {  276, 1003,   43 },

    /* GL_ARB_vertex_shader */
    {  277, 1003,   46 },

    /* GL_ARB_vertex_type_2_10_10_10_rev */
    {  279,  337,    8 },

    /* GL_ARB_viewport_array */
    {  280,  469,   10 },
    {  280, 1049,    2 },

    /* GL_ARB_window_pos */
    {  281, 1051,   16 },

    /* GL_ARM_shader_core_properties */
    {  287, 2559,    1 },

    /* GL_ATI_draw_buffers */
    {  291, 1067,    1 },

    /* GL_ATI_element_array */
    {  292, 1068,    3 },

    /* GL_ATI_envmap_bumpmap */
    {  293, 1071,    4 },

    /* GL_ATI_fragment_shader */
    {  294, 1075,   14 },

    /* GL_ATI_map_object_buffer */
    {  295, 1089,    2 },

    /* GL_ATI_pn_triangles */
    {  298, 1091,    2 },

    /* GL_ATI_separate_stencil */
    {  299, 1093,    2 },

    /* GL_ATI_vertex_array_object */
    {  304, 1095,   12 },

    /* GL_ATI_vertex_attrib_array_object */
    {  305, 1107,    3 },

    /* GL_ATI_vertex_streams */
    {  306, 1110,   45 },

    /* GL_CHROMIUM_bind_uniform_location */
    {  307, 2775,    1 },

    /* GL_CHROMIUM_copy_compressed_texture */
    {  308, 2779,    1 },

    /* GL_CHROMIUM_copy_texture */
    {  309, 2777,    2 },

    /* GL_CHROMIUM_framebuffer_mixed_samples */
    {  310, 2776,    1 },

    /* GL_CHROMIUM_lose_context */
    {  311, 2865,    1 },

    /* GL_EXT_EGL_image_storage */
    {  316, 1155,    2 },

    /* GL_EXT_base_instance */
    {  321, 2560,    3 },

    /* GL_EXT_bindable_uniform */
    {  323, 1157,    3 },

    /* GL_EXT_blend_color */
    {  324, 1160,    1 },

    /* GL_EXT_blend_equation_separate */
    {  325, 1161,    1 },

    /* GL_EXT_blend_func_extended */
    {  326, 1162,    1 },
    {  326, 2563,    3 },

    /* GL_EXT_blend_func_separate */
    {  327, 1163,    1 },

    /* GL_EXT_blend_minmax */
    {  329, 1164,    1 },

    /* GL_EXT_buffer_storage */
    {  334, 2566,    1 },

    /* GL_EXT_clear_texture */
    {  335, 2567,    2 },

    /* GL_EXT_clip_control */
    {  336, 2569,    1 },

    /* GL_EXT_color_subtable */
    {  342, 1165,    2 },

    /* GL_EXT_compiled_vertex_array */
    {  343, 1167,    2 },

    /* GL_EXT_convolution */
    {  347, 1169,   13 },

    /* GL_EXT_coordinate_frame */
    {  348, 1182,   22 },

    /* GL_EXT_copy_image */
    {  349, 2570,    1 },

    /* GL_EXT_copy_texture */
    {  350, 1204,    5 },

    /* GL_EXT_cull_vertex */
    {  351, 1209,    2 },

    /* GL_EXT_debug_label */
    {  352, 1211,    2 },

    /* GL_EXT_debug_marker */
    {  353, 1213,    3 },

    /* GL_EXT_depth_bounds_test */
    {  356, 1216,    1 },

    /* GL_EXT_direct_state_access */
    {  359, 1217,  255 },

    /* GL_EXT_discard_framebuffer */
    {  360, 2571,    1 },

    /* GL_EXT_disjoint_timer_query */
    {  361, 1472,    2 },
    {  361, 2572,   10 },

    /* GL_EXT_draw_buffers */
    {  362, 2582,    1 },

    /* GL_EXT_draw_buffers2 */
    {  363, 1296,    5 },
    {  363, 1474,    1 },

    /* GL_EXT_draw_buffers_indexed */
    {  364, 2583,    8 },

    /* GL_EXT_draw_elements_base_vertex */
    {  365, 2591,    4 },

    /* GL_EXT_draw_instanced */
    {  366, 1475,    2 },

    /* GL_EXT_draw_range_elements */
    {  367, 1477,    1 },

    /* GL_EXT_draw_transform_feedback */
    {  368, 2595,    2 },

    /* GL_EXT_external_buffer */
    {  370, 1478,    2 },

    /* GL_EXT_fog_coord */
    {  372, 1480,    5 },

    /* GL_EXT_fragment_shading_rate */
    {  375, 2597,    4 },

    /* GL_EXT_framebuffer_blit */
    {  376, 1485,    1 },

    /* GL_EXT_framebuffer_blit_layers */
    {  377, 1486,    2 },

    /* GL_EXT_framebuffer_multisample */
    {  378, 1488,    1 },

    /* GL_EXT_framebuffer_object */
    {  380, 1489,   17 },

    /* GL_EXT_geometry_shader */
    {  383, 1506,    1 },

    /* GL_EXT_geometry_shader4 */
    {  384, 1507,    1 },

    /* GL_EXT_gpu_program_parameters */
    {  385, 1508,    2 },

    /* GL_EXT_gpu_shader4 */
    {  386, 1162,    1 },
    {  386, 1510,   33 },

    /* GL_EXT_histogram */
    {  388, 1543,   10 },

    /* GL_EXT_index_func */
    {  390, 1553,    1 },

    /* GL_EXT_index_material */
    {  391, 1554,    1 },

    /* GL_EXT_instanced_arrays */
    {  393, 1475,    2 },
    {  393, 2601,    1 },

    /* GL_EXT_light_texture */
    {  394, 1555,    3 },

    /* GL_EXT_map_buffer_range */
    {  395, 2602,    2 },

    /* GL_EXT_memory_object */
    {  397, 1558,   19 },

    /* GL_EXT_memory_object_fd */
    {  398, 1577,    1 },

    /* GL_EXT_memory_object_win32 */
    {  399, 1578,    2 },

    /* GL_EXT_multi_draw_arrays */
    {  402, 1580,    2 },

    /* GL_EXT_multi_draw_indirect */
    {  403, 2604,    2 },

    /* GL_EXT_multisample */
    {  404, 1582,    2 },

    /* GL_EXT_multisampled_render_to_texture */
    {  406, 1488,    1 },
    {  406, 2606,    1 },

    /* GL_EXT_multiview_draw_buffers */
    {  408, 2607,    3 },

    /* GL_EXT_occlusion_query_boolean */
    {  414, 2572,    5 },
    {  414, 2578,    1 },
    {  414, 2580,    1 },

    /* GL_EXT_paletted_texture */
    {  419, 1584,    4 },

    /* GL_EXT_pixel_transform */
    {  421, 1588,    6 },

    /* GL_EXT_point_parameters */
    {  423, 1594,    2 },

    /* GL_EXT_polygon_offset */
    {  424, 1596,    1 },

    /* GL_EXT_polygon_offset_clamp */
    {  425, 1597,    1 },

    /* GL_EXT_primitive_bounding_box */
    {  427, 2610,    1 },

    /* GL_EXT_provoking_vertex */
    {  429, 1598,    1 },

    /* GL_EXT_raster_multisample */
    {  431, 1599,    1 },

    /* GL_EXT_robustness */
    {  440, 2611,    4 },

    /* GL_EXT_secondary_color */
    {  445, 1610,   17 },

    /* GL_EXT_semaphore */
    {  446, 1558,    2 },
    {  446, 1600,    7 },

    /* GL_EXT_semaphore_fd */
    {  447, 1607,    1 },

    /* GL_EXT_semaphore_win32 */
    {  448, 1608,    2 },

    /* GL_EXT_separate_shader_objects */
    {  450, 1326,   25 },
    {  450, 1361,    8 },
    {  450, 1507,    1 },
    {  450, 1627,    3 },
    {  450, 2615,   10 },

    /* GL_EXT_shader_framebuffer_fetch_non_coherent */
    {  466, 1630,    1 },

    /* GL_EXT_shader_image_load_store */
    {  470, 1631,    2 },

    /* GL_EXT_shader_pixel_local_storage2 */
    {  476, 2625,    3 },

    /* GL_EXT_sparse_texture */
    {  490, 2628,    1 },

    /* GL_EXT_stencil_clear_tag */
    {  494, 1633,    1 },

    /* GL_EXT_stencil_two_side */
    {  495, 1634,    1 },

    /* GL_EXT_subtexture */
    {  499, 1635,    2 },

    /* GL_EXT_tessellation_shader */
    {  502, 2629,    1 },

    /* GL_EXT_texture3D */
    {  504, 1637,    2 },

    /* GL_EXT_texture_array */
    {  505, 1639,    1 },

    /* GL_EXT_texture_border_clamp */
    {  506, 1640,    4 },
    {  506, 2630,    4 },

    /* GL_EXT_texture_buffer */
    {  507, 1644,    1 },
    {  507, 2634,    1 },

    /* GL_EXT_texture_buffer_object */
    {  508, 1644,    1 },

    /* GL_EXT_texture_integer */
    {  525, 1640,    4 },
    {  525, 1645,    2 },

    /* GL_EXT_texture_object */
    {  530, 1647,    6 },

    /* GL_EXT_texture_perturb_normal */
    {  532, 1653,    1 },

    /* GL_EXT_texture_storage */
    {  542, 1458,    3 },
    {  542, 1654,    3 },

    /* GL_EXT_texture_storage_compression */
    {  543, 2635,    2 },

    /* GL_EXT_texture_view */
    {  546, 2637,    1 },

    /* GL_EXT_timer_query */
    {  547, 1472,    2 },

    /* GL_EXT_transform_feedback */
    {  548, 1660,    7 },

    /* GL_EXT_vertex_array */
    {  550, 1667,    9 },

    /* GL_EXT_vertex_attrib_64bit */
    {  552, 1676,   10 },

    /* GL_EXT_vertex_shader */
    {  553, 1686,   42 },

    /* GL_EXT_vertex_weighting */
    {  554, 1728,    3 },

    /* GL_EXT_win32_keyed_mutex */
    {  556, 1731,    2 },

    /* GL_EXT_window_rectangles */
    {  557, 1733,    1 },

    /* GL_EXT_x11_sync_object */
    {  558, 1734,    1 },

    /* GL_GREMEDY_frame_terminator */
    {  560, 1735,    1 },

    /* GL_GREMEDY_string_marker */
    {  561, 1736,    1 },

    /* GL_HP_image_transform */
    {  563, 1737,    6 },

    /* GL_IBM_multimode_draw_arrays */
    {  570, 1743,    2 },

    /* GL_IBM_static_data */
    {  572, 1745,    1 },

    /* GL_IBM_vertex_array_lists */
    {  574, 1746,    8 },

    /* GL_IMG_bindless_texture */
    {  575, 2638,    6 },

    /* GL_IMG_framebuffer_downsample */
    {  576, 2644,    2 },

    /* GL_IMG_multisampled_render_to_texture */
    {  577, 2646,    2 },

    /* GL_INGR_blend_func_separate */
    {  584, 1754,    1 },

    /* GL_INTEL_framebuffer_CMAA */
    {  590, 1755,    1 },

    /* GL_INTEL_map_texture */
    {  591, 1756,    3 },

    /* GL_INTEL_parallel_arrays */
    {  592, 1759,    4 },

    /* GL_INTEL_performance_query */
    {  593, 1763,   10 },

    /* GL_KHR_blend_equation_advanced */
    {  594, 1773,    1 },

    /* GL_KHR_debug */
    {  597,   50,    1 },
    {  597,  524,   10 },
    {  597, 2648,   11 },

    /* GL_KHR_parallel_shader_compile */
    {  600, 1774,    1 },

    /* GL_KHR_robustness */
    {  602,  644,    1 },
    {  602,  648,    4 },
    {  602, 2659,    5 },

    /* GL_MESA_framebuffer_flip_y */
    {  620, 1775,    2 },

    /* GL_MESA_resize_buffers */
    {  624, 1777,    1 },

    /* GL_MESA_sampler_objects */
    {  625,  319,    8 },
    {  625,  329,    1 },
    {  625,  331,    1 },

    /* GL_MESA_window_pos */
    {  629, 1778,   24 },

    /* GL_NVX_conditional_render */
    {  632, 1802,    2 },

    /* GL_NVX_gpu_multicast2 */
    {  634, 1969,    6 },

    /* GL_NVX_linked_gpu_multicast */
    {  635, 1804,    3 },

    /* GL_NVX_progress_fence */
    {  637, 1975,    4 },

    /* GL_NV_alpha_to_coverage_dither_control */
    {  638, 1807,    1 },

    /* GL_NV_bindless_multi_draw_indirect */
    {  639, 1808,    2 },

    /* GL_NV_bindless_multi_draw_indirect_count */
    {  640, 1810,    2 },

    /* GL_NV_bindless_texture */
    {  641, 1812,   13 },

    /* GL_NV_blend_equation_advanced */
    {  642, 1825,    2 },

    /* GL_NV_clip_space_w_scaling */
    {  646, 1827,    1 },

    /* GL_NV_command_list */
    {  647, 1828,   17 },

    /* GL_NV_conditional_render */
    {  650, 1845,    2 },

    /* GL_NV_conservative_raster */
    {  651, 1847,    1 },

    /* GL_NV_conservative_raster_dilate */
    {  652, 1848,    1 },

    /* GL_NV_conservative_raster_pre_snap_triangles */
    {  654, 1849,    1 },

    /* GL_NV_copy_buffer */
    {  658, 2664,    1 },

    /* GL_NV_copy_image */
    {  660, 1850,    1 },

    /* GL_NV_coverage_sample */
    {  661, 2665,    2 },

    /* GL_NV_depth_buffer_float */
    {  663, 1851,    3 },

    /* GL_NV_draw_buffers */
    {  667, 2667,    1 },

    /* GL_NV_draw_instanced */
    {  668, 2668,    2 },

    /* GL_NV_draw_texture */
    {  669, 1854,    1 },

    /* GL_NV_draw_vulkan_image */
    {  670, 1855,    5 },

    /* GL_NV_evaluators */
    {  671, 1860,    9 },

    /* GL_NV_explicit_multisample */
    {  673, 1869,    3 },

    /* GL_NV_fence */
    {  675, 1872,    7 },

    /* GL_NV_fragment_coverage_to_color */
    {  679, 1879,    1 },

    /* GL_NV_fragment_program */
    {  680, 1880,    6 },

    /* GL_NV_framebuffer_blit */
    {  686, 2670,    1 },

    /* GL_NV_framebuffer_mixed_samples */
    {  687, 1599,    1 },
    {  687, 1886,    3 },

    /* GL_NV_framebuffer_multisample */
    {  688, 2671,    1 },

    /* GL_NV_framebuffer_multisample_coverage */
    {  689, 1889,    1 },

    /* GL_NV_geometry_program4 */
    {  691, 1506,    1 },
    {  691, 1639,    1 },
    {  691, 1890,    2 },

    /* GL_NV_gpu_multicast */
    {  694, 1957,   12 },

    /* GL_NV_gpu_program4 */
    {  695, 1892,   16 },

    /* GL_NV_gpu_program5 */
    {  696, 1908,    2 },

    /* GL_NV_gpu_shader5 */
    {  698,  672,   17 },
    {  698,  690,   16 },

    /* GL_NV_half_float */
    {  699, 1910,   46 },

    /* GL_NV_instanced_arrays */
    {  701, 2672,    1 },

    /* GL_NV_internalformat_sample_query */
    {  703, 1956,    1 },

    /* GL_NV_memory_attachment */
    {  705, 1979,    6 },

    /* GL_NV_memory_object_sparse */
    {  706, 1985,    4 },

    /* GL_NV_mesh_shader */
    {  707, 1989,    4 },

    /* GL_NV_non_square_matrices */
    {  710, 2673,    6 },

    /* GL_NV_occlusion_query */
    {  711, 1993,    7 },

    /* GL_NV_parameter_buffer_object */
    {  714, 2000,    3 },

    /* GL_NV_path_rendering */
    {  716, 1217,   15 },
    {  716, 1315,    4 },
    {  716, 2003,   57 },

    /* GL_NV_pixel_data_range */
    {  719, 2060,    2 },

    /* GL_NV_point_sprite */
    {  720, 2062,    2 },

    /* GL_NV_polygon_mode */
    {  721, 2679,    1 },

    /* GL_NV_present_video */
    {  722, 2064,    6 },

    /* GL_NV_primitive_restart */
    {  723, 2070,    2 },

    /* GL_NV_query_resource */
    {  725, 2072,    1 },

    /* GL_NV_query_resource_tag */
    {  726, 2073,    3 },

    /* GL_NV_read_buffer */
    {  729, 2680,    1 },

    /* GL_NV_register_combiners */
    {  734, 2076,   13 },

    /* GL_NV_register_combiners2 */
    {  735, 2089,    2 },

    /* GL_NV_sample_locations */
    {  739, 2091,    3 },

    /* GL_NV_scissor_exclusive */
    {  741, 2094,    2 },

    /* GL_NV_shader_buffer_load */
    {  747,  689,    1 },
    {  747, 2096,   13 },

    /* GL_NV_shading_rate_image */
    {  757, 2109,    7 },

    /* GL_NV_texture_barrier */
    {  764, 2116,    1 },

    /* GL_NV_texture_multisample */
    {  770, 2117,    6 },

    /* GL_NV_timeline_semaphore */
    {  777, 1657,    3 },

    /* GL_NV_transform_feedback */
    {  778, 2123,   12 },

    /* GL_NV_transform_feedback2 */
    {  779, 2135,    7 },

    /* GL_NV_vdpau_interop */
    {  782, 2142,   10 },

    /* GL_NV_vdpau_interop2 */
    {  783, 2152,    1 },

    /* GL_NV_vertex_array_range */
    {  784, 2153,    2 },

    /* GL_NV_vertex_attrib_integer_64bit */
    {  786, 2155,   19 },

    /* GL_NV_vertex_buffer_unified_memory */
    {  787, 2174,   12 },

    /* GL_NV_vertex_program */
    {  788, 2186,   64 },

    /* GL_NV_vertex_program4 */
    {  793, 1520,   23 },

    /* GL_NV_video_capture */
    {  794, 2250,   12 },

    /* GL_NV_viewport_array */
    {  795, 2681,   12 },

    /* GL_NV_viewport_swizzle */
    {  797, 2262,    1 },

    /* GL_OES_EGL_image */
    {  798, 2693,    2 },

    /* GL_OES_EGL_image_external */
    {  799, 2693,    1 },

    /* GL_OES_byte_coordinates */
    {  801, 2263,   22 },

    /* GL_OES_copy_image */
    {  805, 2695,    1 },

    /* GL_OES_draw_buffers_indexed */
    {  809, 2696,    8 },

    /* GL_OES_draw_elements_base_vertex */
    {  810, 2594,    1 },
    {  810, 2704,    3 },

    /* GL_OES_fixed_point */
    {  813, 2285,  103 },

    /* GL_OES_geometry_shader */
    {  816, 2707,    1 },

    /* GL_OES_get_program_binary */
    {  817, 2708,    2 },

    /* GL_OES_mapbuffer */
    {  819, 2710,    3 },

    /* GL_OES_primitive_bounding_box */
    {  821, 2713,    1 },

    /* GL_OES_query_matrix */
    {  822, 2388,    1 },

    /* GL_OES_sample_shading */
    {  826, 2714,    1 },

    /* GL_OES_single_precision */
    {  831, 2389,    6 },

    /* GL_OES_tessellation_shader */
    {  837, 2715,    1 },

    /* GL_OES_texture_3D */
    {  838, 2716,    6 },

    /* GL_OES_texture_border_clamp */
    {  839, 2722,    8 },

    /* GL_OES_texture_buffer */
    {  840, 2730,    2 },

    /* GL_OES_texture_storage_multisample_2d_array */
    {  849, 2732,    1 },

    /* GL_OES_texture_view */
    {  850, 2733,    1 },

    /* GL_OES_vertex_array_object */
    {  851, 2734,    4 },

    /* GL_OES_viewport_array */
    {  854, 2696,    2 },
    {  854, 2703,    1 },
    {  854, 2738,    9 },

    /* GL_OVR_multiview */
    {  858, 2395,    2 },

    /* GL_OVR_multiview_multisampled_render_to_texture */
    {  860, 2747,    1 },

    /* GL_PGI_misc_hints */
    {  861, 2397,    1 },

    /* GL_QCOM_alpha_test */
    {  864, 2748,    1 },

    /* GL_QCOM_driver_control */
    {  866, 2749,    4 },

    /* GL_QCOM_extended_get */
    {  867, 2753,    8 },

    /* GL_QCOM_extended_get2 */
    {  868, 2761,    4 },

    /* GL_QCOM_frame_extrapolation */
    {  869, 2769,    1 },

    /* GL_QCOM_framebuffer_foveated */
    {  870, 2765,    2 },

    /* GL_QCOM_motion_estimation */
    {  873, 2767,    2 },

    /* GL_QCOM_shader_framebuffer_fetch_noncoherent */
    {  877, 2771,    1 },

    /* GL_QCOM_shading_rate */
    {  879, 2772,    1 },

    /* GL_QCOM_texture_foveated */
    {  880, 2770,    1 },

    /* GL_QCOM_tiled_rendering */
    {  884, 2773,    2 },

    /* GL_SGIS_detail_texture */
    {  889, 2398,    2 },

    /* GL_SGIS_fog_function */
    {  890, 2400,    2 },

    /* GL_SGIS_multisample */
    {  892, 2402,    2 },

    /* GL_SGIS_pixel_texture */
    {  893, 2404,    6 },

    /* GL_SGIS_point_parameters */
    {  895, 2410,    2 },

    /* GL_SGIS_sharpen_texture */
    {  896, 2412,    2 },

    /* GL_SGIS_texture4D */
    {  897, 2414,    2 },

    /* GL_SGIS_texture_color_mask */
    {  899, 2416,    1 },

    /* GL_SGIS_texture_filter4 */
    {  901, 2417,    2 },

    /* GL_SGIX_async */
    {  904, 2419,    6 },

    /* GL_SGIX_flush_raster */
    {  913, 2425,    1 },

    /* GL_SGIX_fragment_lighting */
    {  915, 2426,   18 },

    /* GL_SGIX_framezoom */
    {  916, 2444,    1 },

    /* GL_SGIX_igloo_interface */
    {  917, 2445,    1 },

    /* GL_SGIX_instruments */
    {  918, 2446,    6 },

    /* GL_SGIX_list_priority */
    {  921, 2452,    6 },

    /* GL_SGIX_pixel_texture */
    {  922, 2458,    1 },

    /* GL_SGIX_polynomial_ffd */
    {  924, 2459,    4 },

    /* GL_SGIX_reference_plane */
    {  925, 2463,    1 },

    /* GL_SGIX_sprite */
    {  930, 2464,    4 },

    /* GL_SGIX_tag_sample_buffer */
    {  932, 2468,    1 },

    /* GL_SGI_color_table */
    {  943, 2469,    7 },

    /* GL_SUNX_constant_data */
    {  945, 2476,    1 },

    /* GL_SUN_global_alpha */
    {  947, 2477,    8 },

    /* GL_SUN_mesh_array */
    {  948, 2485,    1 },

    /* GL_SUN_triangle_list */
    {  950, 2486,    7 },

    /* GL_SUN_vertex */
    {  951, 2493,   40 },
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
    /*   45 */ 0x2e2561f11ae590dc, /* GL_ANGLE_blob_cache */
    /*   46 */ 0x482ab3c6619af337, /* GL_ANGLE_client_arrays */
    /*   47 */ 0x41739af4618fe843, /* GL_ANGLE_clip_cull_distance */
    /*   48 */ 0xa1378a5ab6903c05, /* GL_ANGLE_copy_texture_3d */
    /*   49 */ 0xaa8f55d75eb1ea08, /* GL_ANGLE_depth_texture */
    /*   50 */ 0xeb72d824895faa8c, /* GL_ANGLE_framebuffer_blit */
    /*   51 */ 0x45e7dae6cdab912b, /* GL_ANGLE_framebuffer_multisample */
    /*   52 */ 0x352e547dc4c723c9, /* GL_ANGLE_get_image */
    /*   53 */ 0x3b399821bf301295, /* GL_ANGLE_get_serialized_context_string */
    /*   54 */ 0xa8bc2a751596a8c9, /* GL_ANGLE_get_tex_level_parameter */
    /*   55 */ 0xf21d57ef70efa97f, /* GL_ANGLE_instanced_arrays */
    /*   56 */ 0x611ffec7970d55f4, /* GL_ANGLE_logic_op */
    /*   57 */ 0xce13622f2ae81cf6, /* GL_ANGLE_lossy_etc_decode */
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
    /*  282 */ 0x6caeb7737f26924a, /* GL_ARM_cooperative_matrix_layouts */
    /*  283 */ 0x2fbeb7cb81220b5e, /* GL_ARM_mali_program_binary */
    /*  284 */ 0x174de60965d38c78, /* GL_ARM_mali_shader_binary */
    /*  285 */ 0x0770bcbef6d87ecc, /* GL_ARM_rgba8 */
    /*  286 */ 0xc97fd975c7c94d78, /* GL_ARM_shader_core_builtins */
    /*  287 */ 0xd022cfc81a420445, /* GL_ARM_shader_core_properties */
    /*  288 */ 0xf0d2f4cff333f04e, /* GL_ARM_shader_framebuffer_fetch */
    /*  289 */ 0xbfa10a2d7557623f, /* GL_ARM_shader_framebuffer_fetch_depth_stencil */
    /*  290 */ 0x8a7a1adbc8af57ff, /* GL_ARM_texture_unnormalized_coordinates */
    /*  291 */ 0xc43e90f15fb8db01, /* GL_ATI_draw_buffers */
    /*  292 */ 0x237ddecca4711d26, /* GL_ATI_element_array */
    /*  293 */ 0x8465366774288b57, /* GL_ATI_envmap_bumpmap */
    /*  294 */ 0x7eace62f803a3a1d, /* GL_ATI_fragment_shader */
    /*  295 */ 0x601618adc78f06ed, /* GL_ATI_map_object_buffer */
    /*  296 */ 0xc2367d65629265d3, /* GL_ATI_meminfo */
    /*  297 */ 0x3ed6aa98977b6026, /* GL_ATI_pixel_format_float */
    /*  298 */ 0xecc62354179a5498, /* GL_ATI_pn_triangles */
    /*  299 */ 0xc9e128c539750596, /* GL_ATI_separate_stencil */
    /*  300 */ 0xf8002b1602911364, /* GL_ATI_text_fragment_shader */
    /*  301 */ 0x8f696d877000fa6a, /* GL_ATI_texture_env_combine3 */
    /*  302 */ 0x72137067e0c140bc, /* GL_ATI_texture_float */
    /*  303 */ 0x184114955f32fded, /* GL_ATI_texture_mirror_once */
    /*  304 */ 0x99180d4f8d9c5d52, /* GL_ATI_vertex_array_object */
    /*  305 */ 0x4bedffd7142a0313, /* GL_ATI_vertex_attrib_array_object */
    /*  306 */ 0xf2a1201512faef81, /* GL_ATI_vertex_streams */
    /*  307 */ 0x9a85b4342c34b2f8, /* GL_CHROMIUM_bind_uniform_location */
    /*  308 */ 0x0dd808babc9daaab, /* GL_CHROMIUM_copy_compressed_texture */
    /*  309 */ 0xe6bdf6222c3733ef, /* GL_CHROMIUM_copy_texture */
    /*  310 */ 0x0bd5e31cc0c829e7, /* GL_CHROMIUM_framebuffer_mixed_samples */
    /*  311 */ 0x04af64470030272e, /* GL_CHROMIUM_lose_context */
    /*  312 */ 0x2b55ba018525895b, /* GL_DMP_program_binary */
    /*  313 */ 0x8e5f4ce24de544d5, /* GL_DMP_shader_binary */
    /*  314 */ 0x0cf95c40c08a43a8, /* GL_EXT_422_pixels */
    /*  315 */ 0x2a61d7b733e75c77, /* GL_EXT_EGL_image_array */
    /*  316 */ 0x35b7bb88d6ff4a1e, /* GL_EXT_EGL_image_storage */
    /*  317 */ 0xfe8066998f34da8e, /* GL_EXT_EGL_image_storage_compression */
    /*  318 */ 0xb8221664855c83bd, /* GL_EXT_EGL_sync */
    /*  319 */ 0x6fac3cb4234e6c59, /* GL_EXT_YUV_target */
    /*  320 */ 0xc118d96a66b6bea3, /* GL_EXT_abgr */
    /*  321 */ 0x6b5e9b6cfbdc3dc0, /* GL_EXT_base_instance */
    /*  322 */ 0x2c343f7622589325, /* GL_EXT_bgra */
    /*  323 */ 0x9d83c1e02304fb00, /* GL_EXT_bindable_uniform */
    /*  324 */ 0x1cafcd91efe0e1d6, /* GL_EXT_blend_color */
    /*  325 */ 0x3510ec477f22f7e7, /* GL_EXT_blend_equation_separate */
    /*  326 */ 0x888e740cefe39cc4, /* GL_EXT_blend_func_extended */
    /*  327 */ 0x97c1a7c0b569dfb8, /* GL_EXT_blend_func_separate */
    /*  328 */ 0x709f5d763ef0911f, /* GL_EXT_blend_logic_op */
    /*  329 */ 0x1163ab5d43e9b052, /* GL_EXT_blend_minmax */
    /*  330 */ 0x2c5c11d0c1161814, /* GL_EXT_blend_subtract */
    /*  331 */ 0x8a59c192ebd08825, /* GL_EXT_buffer_reference */
    /*  332 */ 0x1fe18a884a2d4d2a, /* GL_EXT_buffer_reference2 */
    /*  333 */ 0xb839402fc769c51e, /* GL_EXT_buffer_reference_uvec2 */
    /*  334 */ 0xf57e9c9fe9c776cd, /* GL_EXT_buffer_storage */
    /*  335 */ 0xaafb791a26428890, /* GL_EXT_clear_texture */
    /*  336 */ 0x9452d292aa14805e, /* GL_EXT_clip_control */
    /*  337 */ 0x5737e20452f91527, /* GL_EXT_clip_cull_distance */
    /*  338 */ 0x56a5c2f21e51bb5a, /* GL_EXT_clip_volume_hint */
    /*  339 */ 0x82b62c808e4abb64, /* GL_EXT_cmyka */
    /*  340 */ 0xa297c2c3a49a99be, /* GL_EXT_color_buffer_float */
    /*  341 */ 0xf9449646b78eab54, /* GL_EXT_color_buffer_half_float */
    /*  342 */ 0x6d76340b1318b839, /* GL_EXT_color_subtable */
    /*  343 */ 0xf1bda7fa0a83d383, /* GL_EXT_compiled_vertex_array */
    /*  344 */ 0x9ddf99bdc50f4149, /* GL_EXT_conservative_depth */
    /*  345 */ 0x354415fe7a6e013e, /* GL_EXT_control_flow_attributes */
    /*  346 */ 0x04f0f0ce501bd29d, /* GL_EXT_control_flow_attributes2 */
    /*  347 */ 0xe9260724f594f80b, /* GL_EXT_convolution */
    /*  348 */ 0xf9792a196e0ab7c9, /* GL_EXT_coordinate_frame */
    /*  349 */ 0xa26b121ae33c3436, /* GL_EXT_copy_image */
    /*  350 */ 0x2611c2618f21aa2f, /* GL_EXT_copy_texture */
    /*  351 */ 0xddfc92096368bfbb, /* GL_EXT_cull_vertex */
    /*  352 */ 0xed15a3d914865c56, /* GL_EXT_debug_label */
    /*  353 */ 0x84891a2031a0f162, /* GL_EXT_debug_marker */
    /*  354 */ 0x3d46dbc8319361c9, /* GL_EXT_debug_printf */
    /*  355 */ 0x2a423943f8be1307, /* GL_EXT_demote_to_helper_invocation */
    /*  356 */ 0xe21a2b607eb5c6bb, /* GL_EXT_depth_bounds_test */
    /*  357 */ 0xdc5fb3a8d43d753e, /* GL_EXT_depth_clamp */
    /*  358 */ 0xee026f0d1b48c324, /* GL_EXT_device_group */
    /*  359 */ 0xff4a74da40c62745, /* GL_EXT_direct_state_access */
    /*  360 */ 0x3287a129fb1e11c1, /* GL_EXT_discard_framebuffer */
    /*  361 */ 0x3d06b0f91612d10d, /* GL_EXT_disjoint_timer_query */
    /*  362 */ 0xd3ac9ca278a62f1a, /* GL_EXT_draw_buffers */
    /*  363 */ 0x5d6aa36dbdce372d, /* GL_EXT_draw_buffers2 */
    /*  364 */ 0x997893a6ac44f7fe, /* GL_EXT_draw_buffers_indexed */
    /*  365 */ 0x548657f15226635b, /* GL_EXT_draw_elements_base_vertex */
    /*  366 */ 0xeb1b622faf7697c7, /* GL_EXT_draw_instanced */
    /*  367 */ 0xbb5e6eb0e1559ef1, /* GL_EXT_draw_range_elements */
    /*  368 */ 0x0ccbfada83c13182, /* GL_EXT_draw_transform_feedback */
    /*  369 */ 0xa3176575cdaf6f54, /* GL_EXT_expect_assume */
    /*  370 */ 0x5e1ad5852ce64f31, /* GL_EXT_external_buffer */
    /*  371 */ 0x18d7b8f80d477ce9, /* GL_EXT_float_blend */
    /*  372 */ 0xe09e32cd1ae79288, /* GL_EXT_fog_coord */
    /*  373 */ 0xc117232bce18d68e, /* GL_EXT_fragment_invocation_density */
    /*  374 */ 0x2f9b21678a5e0043, /* GL_EXT_fragment_shader_barycentric */
    /*  375 */ 0xde0a545f611c91b2, /* GL_EXT_fragment_shading_rate */
    /*  376 */ 0xdefc19d979b2e3e2, /* GL_EXT_framebuffer_blit */
    /*  377 */ 0x616048bcd1aa9223, /* GL_EXT_framebuffer_blit_layers */
    /*  378 */ 0x8cbb2537704d8953, /* GL_EXT_framebuffer_multisample */
    /*  379 */ 0x5634f30b2756d601, /* GL_EXT_framebuffer_multisample_blit_scaled */
    /*  380 */ 0x8350f19ac13e7c07, /* GL_EXT_framebuffer_object */
    /*  381 */ 0xa45a63878264c1e5, /* GL_EXT_framebuffer_sRGB */
    /*  382 */ 0x30d017755de50dd9, /* GL_EXT_geometry_point_size */
    /*  383 */ 0xfa22129bb4d04128, /* GL_EXT_geometry_shader */
    /*  384 */ 0x5370f0fbdd1b1f1d, /* GL_EXT_geometry_shader4 */
    /*  385 */ 0x3604f5b2b65016b2, /* GL_EXT_gpu_program_parameters */
    /*  386 */ 0x020c60828c37ce5d, /* GL_EXT_gpu_shader4 */
    /*  387 */ 0x53dbe9871073dca3, /* GL_EXT_gpu_shader5 */
    /*  388 */ 0xcebb9285fc482cfd, /* GL_EXT_histogram */
    /*  389 */ 0x64ea7e43377361ff, /* GL_EXT_index_array_formats */
    /*  390 */ 0xecf771ddabe3f8ed, /* GL_EXT_index_func */
    /*  391 */ 0x649623e695acbfb0, /* GL_EXT_index_material */
    /*  392 */ 0x43fd3f035960e92c, /* GL_EXT_index_texture */
    /*  393 */ 0x9c3c026caab1aaf7, /* GL_EXT_instanced_arrays */
    /*  394 */ 0x6b0a475df16ae9f2, /* GL_EXT_light_texture */
    /*  395 */ 0xf41152d50d03cc16, /* GL_EXT_map_buffer_range */
    /*  396 */ 0xdea398d907b668d0, /* GL_EXT_maximal_reconvergence */
    /*  397 */ 0xebb55934637c6ab7, /* GL_EXT_memory_object */
    /*  398 */ 0x7e941665b79d31c4, /* GL_EXT_memory_object_fd */
    /*  399 */ 0x6bf3a6b6ec24354b, /* GL_EXT_memory_object_win32 */
    /*  400 */ 0x67079bf943104541, /* GL_EXT_mesh_shader */
    /*  401 */ 0xda6fb882011aa28e, /* GL_EXT_misc_attribute */
    /*  402 */ 0x6077bed8aa109362, /* GL_EXT_multi_draw_arrays */
    /*  403 */ 0x55b4806b38f2b08e, /* GL_EXT_multi_draw_indirect */
    /*  404 */ 0x872a66595e5024ca, /* GL_EXT_multisample */
    /*  405 */ 0x3e4a3b0ff8584927, /* GL_EXT_multisampled_compatibility */
    /*  406 */ 0x33b89ab037aed106, /* GL_EXT_multisampled_render_to_texture */
    /*  407 */ 0x39f0379607d459f0, /* GL_EXT_multisampled_render_to_texture2 */
    /*  408 */ 0x49f63d58daabfccb, /* GL_EXT_multiview_draw_buffers */
    /*  409 */ 0x5b7a6a36ed0fe897, /* GL_EXT_multiview_tessellation_geometry_shader */
    /*  410 */ 0x3679a0ac14e16e97, /* GL_EXT_multiview_texture_multisample */
    /*  411 */ 0x39d0f3848228d38f, /* GL_EXT_multiview_timer_query */
    /*  412 */ 0x0d7bdf1d96e54238, /* GL_EXT_nonuniform_qualifier */
    /*  413 */ 0xff653ce0c16c5c81, /* GL_EXT_null_initializer */
    /*  414 */ 0xbf12db2b88c87ccf, /* GL_EXT_occlusion_query_boolean */
    /*  415 */ 0x927980c53f038149, /* GL_EXT_opacity_micromap */
    /*  416 */ 0x757af2451eae9d25, /* GL_EXT_packed_depth_stencil */
    /*  417 */ 0x2ace1d8656332b56, /* GL_EXT_packed_float */
    /*  418 */ 0x248d529c3993285c, /* GL_EXT_packed_pixels */
    /*  419 */ 0xecd5d2503b35bb13, /* GL_EXT_paletted_texture */
    /*  420 */ 0xc7f3ad7137661622, /* GL_EXT_pixel_buffer_object */
    /*  421 */ 0x59d7be95f9b27b9a, /* GL_EXT_pixel_transform */
    /*  422 */ 0xd7024b008ea1463b, /* GL_EXT_pixel_transform_color_table */
    /*  423 */ 0x14eaf45986c9bfa1, /* GL_EXT_point_parameters */
    /*  424 */ 0x5640aa3e3a0202cb, /* GL_EXT_polygon_offset */
    /*  425 */ 0xd55f7ac9bd1eba74, /* GL_EXT_polygon_offset_clamp */
    /*  426 */ 0x55695328ecdeb972, /* GL_EXT_post_depth_coverage */
    /*  427 */ 0x849565c10789238e, /* GL_EXT_primitive_bounding_box */
    /*  428 */ 0x638afa82b47ca539, /* GL_EXT_protected_textures */
    /*  429 */ 0xfc1cd6391217f09e, /* GL_EXT_provoking_vertex */
    /*  430 */ 0xc36c4a5ae294a717, /* GL_EXT_pvrtc_sRGB */
    /*  431 */ 0x864a43fa5616bb8c, /* GL_EXT_raster_multisample */
    /*  432 */ 0xb0b19c0e9f3b0f5c, /* GL_EXT_ray_cull_mask */
    /*  433 */ 0xd982b05f307f6fcd, /* GL_EXT_ray_flags_primitive_culling */
    /*  434 */ 0xbf4a58353f9a7a75, /* GL_EXT_ray_query */
    /*  435 */ 0x5d7ccf8ac93b7140, /* GL_EXT_ray_tracing */
    /*  436 */ 0x98b5a9c9f9d792dd, /* GL_EXT_ray_tracing_position_fetch */
    /*  437 */ 0x1b664521b8e7cedd, /* GL_EXT_read_format_bgra */
    /*  438 */ 0x461ed0af7d9ee57e, /* GL_EXT_render_snorm */
    /*  439 */ 0xc99a47326d03fd17, /* GL_EXT_rescale_normal */
    /*  440 */ 0x04aaf7c50fd23609, /* GL_EXT_robustness */
    /*  441 */ 0x72a714dfac11ff63, /* GL_EXT_sRGB */
    /*  442 */ 0xa329e9d07bf41faa, /* GL_EXT_sRGB_write_control */
    /*  443 */ 0x6c203c99634fa814, /* GL_EXT_samplerless_texture_functions */
    /*  444 */ 0xe045958c8c43c35f, /* GL_EXT_scalar_block_layout */
    /*  445 */ 0x5da9f01e568b2e0b, /* GL_EXT_secondary_color */
    /*  446 */ 0x40ea8dbcbb4d106f, /* GL_EXT_semaphore */
    /*  447 */ 0xb3de6f78cadcbed7, /* GL_EXT_semaphore_fd */
    /*  448 */ 0xd80cf52931619f45, /* GL_EXT_semaphore_win32 */
    /*  449 */ 0xde7c2e65ed21d1e7, /* GL_EXT_separate_depth_stencil */
    /*  450 */ 0xb207ff65f8bf495d, /* GL_EXT_separate_shader_objects */
    /*  451 */ 0xeb07329b2f67d2ec, /* GL_EXT_separate_specular_color */
    /*  452 */ 0x49d751ecfad21a12, /* GL_EXT_shader_16bit_storage */
    /*  453 */ 0x9861ec1bd88d15cf, /* GL_EXT_shader_8bit_storage */
    /*  454 */ 0x71c6281257d16bdf, /* GL_EXT_shader_atomic_float */
    /*  455 */ 0x3b6516e3dbabfb91, /* GL_EXT_shader_atomic_float2 */
    /*  456 */ 0x59bd13c26a6e0f68, /* GL_EXT_shader_atomic_int64 */
    /*  457 */ 0x6e599868ea3a939f, /* GL_EXT_shader_explicit_arithmetic_types */
    /*  458 */ 0x38889dc6669f650d, /* GL_EXT_shader_explicit_arithmetic_types_float16 */
    /*  459 */ 0x935e023eaa3a09f7, /* GL_EXT_shader_explicit_arithmetic_types_float32 */
    /*  460 */ 0x898fe8394abadf05, /* GL_EXT_shader_explicit_arithmetic_types_float64 */
    /*  461 */ 0x9177b5f32c341f00, /* GL_EXT_shader_explicit_arithmetic_types_int16 */
    /*  462 */ 0x974487e410e50b66, /* GL_EXT_shader_explicit_arithmetic_types_int32 */
    /*  463 */ 0x6cf4f9de748703f8, /* GL_EXT_shader_explicit_arithmetic_types_int64 */
    /*  464 */ 0x43904cfef5f6138e, /* GL_EXT_shader_explicit_arithmetic_types_int8 */
    /*  465 */ 0x86da0f80c54cef33, /* GL_EXT_shader_framebuffer_fetch */
    /*  466 */ 0xcd3c990c9f8c0a64, /* GL_EXT_shader_framebuffer_fetch_non_coherent */
    /*  467 */ 0x17434ddfdf3a5893, /* GL_EXT_shader_group_vote */
    /*  468 */ 0xeab14f8fb076d3f3, /* GL_EXT_shader_image_int64 */
    /*  469 */ 0xc1de48ba5bbf7b01, /* GL_EXT_shader_image_load_formatted */
    /*  470 */ 0x6ab82341e3e65156, /* GL_EXT_shader_image_load_store */
    /*  471 */ 0xe19d3a68c60c0ef4, /* GL_EXT_shader_implicit_conversions */
    /*  472 */ 0x033287cccf9a6962, /* GL_EXT_shader_integer_mix */
    /*  473 */ 0xd055bdf912abe3b0, /* GL_EXT_shader_io_blocks */
    /*  474 */ 0x07975202b868bf83, /* GL_EXT_shader_non_constant_global_initializers */
    /*  475 */ 0x49f7e4529e189129, /* GL_EXT_shader_pixel_local_storage */
    /*  476 */ 0x28720bf0be8ab661, /* GL_EXT_shader_pixel_local_storage2 */
    /*  477 */ 0x9b3693eac0a5b344, /* GL_EXT_shader_quad_control */
    /*  478 */ 0x28c00ec379a98b9d, /* GL_EXT_shader_realtime_clock */
    /*  479 */ 0x3ef958340d410019, /* GL_EXT_shader_samples_identical */
    /*  480 */ 0xdb7ea225c0575a72, /* GL_EXT_shader_subgroup_extended_types_float16 */
    /*  481 */ 0x50620210b36d2a7e, /* GL_EXT_shader_subgroup_extended_types_int16 */
    /*  482 */ 0xcaf721268b43e997, /* GL_EXT_shader_subgroup_extended_types_int64 */
    /*  483 */ 0x6de284e02f65aff5, /* GL_EXT_shader_subgroup_extended_types_int8 */
    /*  484 */ 0x0fbf30e41210d727, /* GL_EXT_shader_texture_lod */
    /*  485 */ 0x0e7ba3c5e5be8403, /* GL_EXT_shader_tile_image */
    /*  486 */ 0xe504594d7646deb5, /* GL_EXT_shadow_funcs */
    /*  487 */ 0x7c7d332de021da36, /* GL_EXT_shadow_samplers */
    /*  488 */ 0x4851b197319900c7, /* GL_EXT_shared_memory_block */
    /*  489 */ 0xa39da1f69d0cad57, /* GL_EXT_shared_texture_palette */
    /*  490 */ 0x86ac1bf74755a73b, /* GL_EXT_sparse_texture */
    /*  491 */ 0x81ed537411dae865, /* GL_EXT_sparse_texture2 */
    /*  492 */ 0x3e990113969288c9, /* GL_EXT_spec_constant_composites */
    /*  493 */ 0x5d049f1a9498df05, /* GL_EXT_spirv_intrinsics */
    /*  494 */ 0xe20fb1c3faf6f7d8, /* GL_EXT_stencil_clear_tag */
    /*  495 */ 0x629c334d67e5c718, /* GL_EXT_stencil_two_side */
    /*  496 */ 0x961b80206055e672, /* GL_EXT_stencil_wrap */
    /*  497 */ 0x8a56add0af10cbb6, /* GL_EXT_subgroup_uniform_control_flow */
    /*  498 */ 0xf85c8111e381b059, /* GL_EXT_subgroupuniform_qualifier */
    /*  499 */ 0xe101571ccdddbe44, /* GL_EXT_subtexture */
    /*  500 */ 0x80fb7149e30bd23a, /* GL_EXT_terminate_invocation */
    /*  501 */ 0x9e9a449841a4392b, /* GL_EXT_tessellation_point_size */
    /*  502 */ 0xa694e21c70c92ac7, /* GL_EXT_tessellation_shader */
    /*  503 */ 0x7893ebdfb50f10a6, /* GL_EXT_texture */
    /*  504 */ 0x3c1975837c97841b, /* GL_EXT_texture3D */
    /*  505 */ 0x2e4c3fc71fe20a24, /* GL_EXT_texture_array */
    /*  506 */ 0xf02848fc36653917, /* GL_EXT_texture_border_clamp */
    /*  507 */ 0x990b742e339cfdab, /* GL_EXT_texture_buffer */
    /*  508 */ 0xe30b1bf963964b94, /* GL_EXT_texture_buffer_object */
    /*  509 */ 0x7c8af8bc6e29a35b, /* GL_EXT_texture_compression_astc_decode_mode */
    /*  510 */ 0x8c12f4a29dd9872d, /* GL_EXT_texture_compression_bptc */
    /*  511 */ 0x42f4b0934de6c2dc, /* GL_EXT_texture_compression_dxt1 */
    /*  512 */ 0x789187ec36c3334e, /* GL_EXT_texture_compression_latc */
    /*  513 */ 0x6d7076425ffdf707, /* GL_EXT_texture_compression_rgtc */
    /*  514 */ 0x675e8f3271d1d5ca, /* GL_EXT_texture_compression_s3tc */
    /*  515 */ 0x747ed54119078205, /* GL_EXT_texture_compression_s3tc_srgb */
    /*  516 */ 0x511d1308a8dfc13f, /* GL_EXT_texture_cube_map */
    /*  517 */ 0x143e4c21a6ff53cc, /* GL_EXT_texture_cube_map_array */
    /*  518 */ 0xd7d84a9c353851fd, /* GL_EXT_texture_env_add */
    /*  519 */ 0x9d216b7a877bbcfb, /* GL_EXT_texture_env_combine */
    /*  520 */ 0x4bacf852b1cc1a43, /* GL_EXT_texture_env_dot3 */
    /*  521 */ 0xeafde92a9cccc4ed, /* GL_EXT_texture_filter_anisotropic */
    /*  522 */ 0x7738fa89f1d13a13, /* GL_EXT_texture_filter_minmax */
    /*  523 */ 0x39751dec512ae77c, /* GL_EXT_texture_format_BGRA8888 */
    /*  524 */ 0xeb53a2bedf43571d, /* GL_EXT_texture_format_sRGB_override */
    /*  525 */ 0xaf09c3ff42c89eb5, /* GL_EXT_texture_integer */
    /*  526 */ 0x41cf52695838c61c, /* GL_EXT_texture_lod_bias */
    /*  527 */ 0x17fb25156306ea61, /* GL_EXT_texture_mirror_clamp */
    /*  528 */ 0x9a5a807af7e26b3f, /* GL_EXT_texture_mirror_clamp_to_edge */
    /*  529 */ 0x94b22c00bec3e518, /* GL_EXT_texture_norm16 */
    /*  530 */ 0x10827f593acd1ba7, /* GL_EXT_texture_object */
    /*  531 */ 0xbdcbb1418f18d3a4, /* GL_EXT_texture_offset_non_const */
    /*  532 */ 0x971e595b62f38066, /* GL_EXT_texture_perturb_normal */
    /*  533 */ 0x1e6eaad4a57ca1b5, /* GL_EXT_texture_query_lod */
    /*  534 */ 0x95f0b0bc421f25d3, /* GL_EXT_texture_rg */
    /*  535 */ 0xd43be8ff9c7c7ada, /* GL_EXT_texture_sRGB */
    /*  536 */ 0xfe62dc3d8ab9f10b, /* GL_EXT_texture_sRGB_R8 */
    /*  537 */ 0xcb6984e200d35ff9, /* GL_EXT_texture_sRGB_RG8 */
    /*  538 */ 0x2b44a8b2473d6e5f, /* GL_EXT_texture_sRGB_decode */
    /*  539 */ 0x127856e58a250c1b, /* GL_EXT_texture_shadow_lod */
    /*  540 */ 0x30a7dd27a9ac5760, /* GL_EXT_texture_shared_exponent */
    /*  541 */ 0xa2f8f4e45d997df3, /* GL_EXT_texture_snorm */
    /*  542 */ 0x154c4c8b80533dc0, /* GL_EXT_texture_storage */
    /*  543 */ 0x8768e67dadd2a7fd, /* GL_EXT_texture_storage_compression */
    /*  544 */ 0x183ae240682f4ad7, /* GL_EXT_texture_swizzle */
    /*  545 */ 0x4a802d8de71af8e9, /* GL_EXT_texture_type_2_10_10_10_REV */
    /*  546 */ 0x19afe800141638dc, /* GL_EXT_texture_view */
    /*  547 */ 0x4ab0caa70a996495, /* GL_EXT_timer_query */
    /*  548 */ 0x471536c0a27f5c81, /* GL_EXT_transform_feedback */
    /*  549 */ 0x1675c7c13b385f42, /* GL_EXT_unpack_subimage */
    /*  550 */ 0x2347ebc551d02975, /* GL_EXT_vertex_array */
    /*  551 */ 0xc5160cefc841200d, /* GL_EXT_vertex_array_bgra */
    /*  552 */ 0xfe8f41c3d0888d86, /* GL_EXT_vertex_attrib_64bit */
    /*  553 */ 0x10ce9358a245f782, /* GL_EXT_vertex_shader */
    /*  554 */ 0x80e4c2ee68e62a5f, /* GL_EXT_vertex_weighting */
    /*  555 */ 0x71431741b9e82753, /* GL_EXT_vulkan_glsl_relaxed */
    /*  556 */ 0xb7046ff80ce07f1a, /* GL_EXT_win32_keyed_mutex */
    /*  557 */ 0x225b607d5cdf07d5, /* GL_EXT_window_rectangles */
    /*  558 */ 0x80306c2b70f53ada, /* GL_EXT_x11_sync_object */
    /*  559 */ 0xaf38ae454737b45a, /* GL_FJ_shader_binary_GCCSO */
    /*  560 */ 0x776d5f9ce5dc30ad, /* GL_GREMEDY_frame_terminator */
    /*  561 */ 0x2b64919ae0d632d6, /* GL_GREMEDY_string_marker */
    /*  562 */ 0x4ba0a53809cd8e1c, /* GL_HP_convolution_border_modes */
    /*  563 */ 0x175101ef679b74d1, /* GL_HP_image_transform */
    /*  564 */ 0x21db09dff47e8865, /* GL_HP_occlusion_test */
    /*  565 */ 0xbccb311192bef9fc, /* GL_HP_texture_lighting */
    /*  566 */ 0xf5546e69b4a74cb1, /* GL_HUAWEI_program_binary */
    /*  567 */ 0x1ca5a9610adbc615, /* GL_HUAWEI_shader_binary */
    /*  568 */ 0x01088281231ac4b3, /* GL_HUAWEI_subpass_shading */
    /*  569 */ 0x052c78ec9092b2bc, /* GL_IBM_cull_vertex */
    /*  570 */ 0xbed7db565a3dcdb1, /* GL_IBM_multimode_draw_arrays */
    /*  571 */ 0xb0a341b3ba34bde7, /* GL_IBM_rasterpos_clip */
    /*  572 */ 0xe5d4e67e743793af, /* GL_IBM_static_data */
    /*  573 */ 0x42e7c1e06f5230cb, /* GL_IBM_texture_mirrored_repeat */
    /*  574 */ 0x3801878506a0d3e5, /* GL_IBM_vertex_array_lists */
    /*  575 */ 0xe966fe12585d0ee3, /* GL_IMG_bindless_texture */
    /*  576 */ 0xee05cb0623b18588, /* GL_IMG_framebuffer_downsample */
    /*  577 */ 0x6cd4bff21f14cba9, /* GL_IMG_multisampled_render_to_texture */
    /*  578 */ 0x10eae89c21411416, /* GL_IMG_program_binary */
    /*  579 */ 0xe1d246c5f2217570, /* GL_IMG_read_format */
    /*  580 */ 0x631524850de59ddd, /* GL_IMG_shader_binary */
    /*  581 */ 0x26bbd5573ad61282, /* GL_IMG_texture_compression_pvrtc */
    /*  582 */ 0x46869091dbce71a6, /* GL_IMG_texture_compression_pvrtc2 */
    /*  583 */ 0xd44d6d9763e6fd68, /* GL_IMG_texture_filter_cubic */
    /*  584 */ 0xf8c1cfe37858c556, /* GL_INGR_blend_func_separate */
    /*  585 */ 0x9d3ca51fe0f2a837, /* GL_INGR_color_clamp */
    /*  586 */ 0x231c00090b681c01, /* GL_INGR_interlace_read */
    /*  587 */ 0xc0f54564fa652eba, /* GL_INTEL_blackhole_render */
    /*  588 */ 0x8cfa061f6a006e62, /* GL_INTEL_conservative_rasterization */
    /*  589 */ 0x693a15be925d42bb, /* GL_INTEL_fragment_shader_ordering */
    /*  590 */ 0x14386616e0282da8, /* GL_INTEL_framebuffer_CMAA */
    /*  591 */ 0xfe0a30102b2b7f11, /* GL_INTEL_map_texture */
    /*  592 */ 0x6d9138f92a97a9b2, /* GL_INTEL_parallel_arrays */
    /*  593 */ 0x331d1b2f1d575bd8, /* GL_INTEL_performance_query */
    /*  594 */ 0x898f16e7a19612fe, /* GL_KHR_blend_equation_advanced */
    /*  595 */ 0xa66b25957f58c923, /* GL_KHR_blend_equation_advanced_coherent */
    /*  596 */ 0x0956a658c75ab600, /* GL_KHR_context_flush_control */
    /*  597 */ 0x5e0c5b9607ac8784, /* GL_KHR_debug */
    /*  598 */ 0x08ce79df715e69dc, /* GL_KHR_memory_scope_semantics */
    /*  599 */ 0x12316ddfcc85238e, /* GL_KHR_no_error */
    /*  600 */ 0x3406b66e92343753, /* GL_KHR_parallel_shader_compile */
    /*  601 */ 0xfa6bb57654b50c92, /* GL_KHR_robust_buffer_access_behavior */
    /*  602 */ 0x474beac5f6910636, /* GL_KHR_robustness */
    /*  603 */ 0x65263f2081d063e7, /* GL_KHR_shader_subgroup */
    /*  604 */ 0x877be0bdc1f8d36c, /* GL_KHR_shader_subgroup_arithmetic */
    /*  605 */ 0x61e703f91e0948f3, /* GL_KHR_shader_subgroup_ballot */
    /*  606 */ 0x5b9c554fd0d5a036, /* GL_KHR_shader_subgroup_basic */
    /*  607 */ 0xe1044b09af95d72a, /* GL_KHR_shader_subgroup_clustered */
    /*  608 */ 0x4b76468cfb09dabc, /* GL_KHR_shader_subgroup_quad */
    /*  609 */ 0x55436fcdf6a6d27d, /* GL_KHR_shader_subgroup_rotate */
    /*  610 */ 0xaa09aac681765f3a, /* GL_KHR_shader_subgroup_shuffle */
    /*  611 */ 0x56a562daeb0a2f26, /* GL_KHR_shader_subgroup_shuffle_relative */
    /*  612 */ 0x85bb9015d69ab32d, /* GL_KHR_shader_subgroup_vote */
    /*  613 */ 0x24c80aab81e859b3, /* GL_KHR_texture_compression_astc_hdr */
    /*  614 */ 0x16f59295398b9d0a, /* GL_KHR_texture_compression_astc_ldr */
    /*  615 */ 0xa4a29c6f56f2023e, /* GL_KHR_texture_compression_astc_sliced_3d */
    /*  616 */ 0xcbbacf3d7c96adcc, /* GL_KHR_vulkan_glsl */
    /*  617 */ 0x70bbb44bbc67a914, /* GL_MESAX_texture_stack */
    /*  618 */ 0x4b833beb1f90e758, /* GL_MESA_bgra */
    /*  619 */ 0xf9cfb61b2f897c12, /* GL_MESA_framebuffer_flip_x */
    /*  620 */ 0xdf842b85f40b8f2d, /* GL_MESA_framebuffer_flip_y */
    /*  621 */ 0xc735e4d56089513e, /* GL_MESA_framebuffer_swap_xy */
    /*  622 */ 0xac7eeedfea22e53d, /* GL_MESA_pack_invert */
    /*  623 */ 0xe164dc7b3064a548, /* GL_MESA_program_binary_formats */
    /*  624 */ 0x39376b06206502d6, /* GL_MESA_resize_buffers */
    /*  625 */ 0xa14ebc048c19e849, /* GL_MESA_sampler_objects */
    /*  626 */ 0x58e3c24874e50b2f, /* GL_MESA_shader_integer_functions */
    /*  627 */ 0x7148e64fc5eef950, /* GL_MESA_texture_const_bandwidth */
    /*  628 */ 0x8ee739e5f4f16337, /* GL_MESA_tile_raster_order */
    /*  629 */ 0x00063de42ab739f6, /* GL_MESA_window_pos */
    /*  630 */ 0x05840d0e5ebfdb5d, /* GL_MESA_ycbcr_texture */
    /*  631 */ 0x210f54fb5023bd27, /* GL_NVX_blend_equation_advanced_multi_draw_buffers */
    /*  632 */ 0xdb3d40c973a8401d, /* GL_NVX_conditional_render */
    /*  633 */ 0xdba64e974cfda98b, /* GL_NVX_gpu_memory_info */
    /*  634 */ 0xfadb1fc8cec16ab6, /* GL_NVX_gpu_multicast2 */
    /*  635 */ 0xcd2e0dc9329fd277, /* GL_NVX_linked_gpu_multicast */
    /*  636 */ 0xd9dac6ae420f2bc1, /* GL_NVX_multiview_per_view_attributes */
    /*  637 */ 0xd0ab24d9b21b5714, /* GL_NVX_progress_fence */
    /*  638 */ 0xf60ebf70e765dade, /* GL_NV_alpha_to_coverage_dither_control */
    /*  639 */ 0x0125c6b149dc763d, /* GL_NV_bindless_multi_draw_indirect */
    /*  640 */ 0xbf25dd3d5b684860, /* GL_NV_bindless_multi_draw_indirect_count */
    /*  641 */ 0xfe0701cf0661b283, /* GL_NV_bindless_texture */
    /*  642 */ 0xdfb2fe6dc8d05e7b, /* GL_NV_blend_equation_advanced */
    /*  643 */ 0x93143e8adaf57589, /* GL_NV_blend_equation_advanced_coherent */
    /*  644 */ 0xea9c32d0ef37492e, /* GL_NV_blend_minmax_factor */
    /*  645 */ 0xcfb887fc69ba21e3, /* GL_NV_blend_square */
    /*  646 */ 0xa4c52c3b41a4fcad, /* GL_NV_clip_space_w_scaling */
    /*  647 */ 0x86fd725bf0f0d470, /* GL_NV_command_list */
    /*  648 */ 0x909a590b136b2993, /* GL_NV_compute_program5 */
    /*  649 */ 0x6e8fcfc637ce5f42, /* GL_NV_compute_shader_derivatives */
    /*  650 */ 0x30dc18387f98fe17, /* GL_NV_conditional_render */
    /*  651 */ 0xe3492208f94da35f, /* GL_NV_conservative_raster */
    /*  652 */ 0xd3d407b80b1805ae, /* GL_NV_conservative_raster_dilate */
    /*  653 */ 0x10c99e7e01aae44f, /* GL_NV_conservative_raster_pre_snap */
    /*  654 */ 0xf4ef9c1caf911a2c, /* GL_NV_conservative_raster_pre_snap_triangles */
    /*  655 */ 0x9a8099482ede4695, /* GL_NV_conservative_raster_underestimation */
    /*  656 */ 0x82f2d3fffe63ccba, /* GL_NV_cooperative_matrix */
    /*  657 */ 0xc3e52c0f74e3a5b4, /* GL_NV_cooperative_matrix2 */
    /*  658 */ 0x1250d4e984fabb8a, /* GL_NV_copy_buffer */
    /*  659 */ 0xddf225eb383a722a, /* GL_NV_copy_depth_to_color */
    /*  660 */ 0x542626fd538a9ee0, /* GL_NV_copy_image */
    /*  661 */ 0x1f3cf0884049a65c, /* GL_NV_coverage_sample */
    /*  662 */ 0xa115ed21a9ad2718, /* GL_NV_deep_texture3D */
    /*  663 */ 0x11d0e662e981dd10, /* GL_NV_depth_buffer_float */
    /*  664 */ 0x25caf626c8dc4876, /* GL_NV_depth_clamp */
    /*  665 */ 0x23fb225c6189b719, /* GL_NV_depth_nonlinear */
    /*  666 */ 0xc7c2a14929f83872, /* GL_NV_displacement_micromap */
    /*  667 */ 0xe30effdb6e04aad2, /* GL_NV_draw_buffers */
    /*  668 */ 0x5cef483902a0a7d1, /* GL_NV_draw_instanced */
    /*  669 */ 0x0ac29b41db04db89, /* GL_NV_draw_texture */
    /*  670 */ 0x0c3ad3a0bb6ea832, /* GL_NV_draw_vulkan_image */
    /*  671 */ 0x86aaaa35812cc6e4, /* GL_NV_evaluators */
    /*  672 */ 0x0d0ad1150bf11b93, /* GL_NV_explicit_attrib_location */
    /*  673 */ 0xb1fb52088193eb75, /* GL_NV_explicit_multisample */
    /*  674 */ 0xf69d212a36261f45, /* GL_NV_fbo_color_attachments */
    /*  675 */ 0x9f9d6242407aaa0d, /* GL_NV_fence */
    /*  676 */ 0x574a28d0edc9eb1f, /* GL_NV_fill_rectangle */
    /*  677 */ 0x60178d619bd63acd, /* GL_NV_float_buffer */
    /*  678 */ 0x3a25bd3423152eb5, /* GL_NV_fog_distance */
    /*  679 */ 0xbd0368ffaa60b1e1, /* GL_NV_fragment_coverage_to_color */
    /*  680 */ 0xd63f48ff142e3931, /* GL_NV_fragment_program */
    /*  681 */ 0x9607f3b2549a29c3, /* GL_NV_fragment_program2 */
    /*  682 */ 0x3fc3c14225294207, /* GL_NV_fragment_program4 */
    /*  683 */ 0x7e38a803870eb005, /* GL_NV_fragment_program_option */
    /*  684 */ 0x63f3491b75562351, /* GL_NV_fragment_shader_barycentric */
    /*  685 */ 0xf907528dfaacf5d1, /* GL_NV_fragment_shader_interlock */
    /*  686 */ 0xc7b0688e759eacca, /* GL_NV_framebuffer_blit */
    /*  687 */ 0x7690d69739f37d49, /* GL_NV_framebuffer_mixed_samples */
    /*  688 */ 0xd333a1d53faf1645, /* GL_NV_framebuffer_multisample */
    /*  689 */ 0xb7e1d7ede28f1eb6, /* GL_NV_framebuffer_multisample_coverage */
    /*  690 */ 0x42fb5b03beace82d, /* GL_NV_generate_mipmap_sRGB */
    /*  691 */ 0xd649529b8b1dc13f, /* GL_NV_geometry_program4 */
    /*  692 */ 0x85be2495755b8912, /* GL_NV_geometry_shader4 */
    /*  693 */ 0x2650d5fc619ace25, /* GL_NV_geometry_shader_passthrough */
    /*  694 */ 0x0f309973ce34369d, /* GL_NV_gpu_multicast */
    /*  695 */ 0xb97d5c93298f0cd0, /* GL_NV_gpu_program4 */
    /*  696 */ 0xfee0597c2b98bd5a, /* GL_NV_gpu_program5 */
    /*  697 */ 0x76ac1ada5bbc4ea2, /* GL_NV_gpu_program5_mem_extended */
    /*  698 */ 0x9ca801fbedd18a78, /* GL_NV_gpu_shader5 */
    /*  699 */ 0x185a8632c27d17b4, /* GL_NV_half_float */
    /*  700 */ 0xe34c3aba26b785e0, /* GL_NV_image_formats */
    /*  701 */ 0xc2e8b0284eeb3343, /* GL_NV_instanced_arrays */
    /*  702 */ 0xaeae3147a430714a, /* GL_NV_integer_cooperative_matrix */
    /*  703 */ 0xa5628152267b8db5, /* GL_NV_internalformat_sample_query */
    /*  704 */ 0x4514ca3e8473d61d, /* GL_NV_light_max_exponent */
    /*  705 */ 0xe91f9b1323143013, /* GL_NV_memory_attachment */
    /*  706 */ 0x529b823de64f6ca0, /* GL_NV_memory_object_sparse */
    /*  707 */ 0x2793373463edd95b, /* GL_NV_mesh_shader */
    /*  708 */ 0x8d5187c2fb3e3879, /* GL_NV_multisample_coverage */
    /*  709 */ 0x92f77a4cfb0d4df3, /* GL_NV_multisample_filter_hint */
    /*  710 */ 0x5b891d5155380820, /* GL_NV_non_square_matrices */
    /*  711 */ 0xdff6cf35e1df2d8d, /* GL_NV_occlusion_query */
    /*  712 */ 0xda29f4099a052321, /* GL_NV_pack_subimage */
    /*  713 */ 0x1a5932681cefa5eb, /* GL_NV_packed_depth_stencil */
    /*  714 */ 0xbffccb846b13070a, /* GL_NV_parameter_buffer_object */
    /*  715 */ 0xb153f109324c418b, /* GL_NV_parameter_buffer_object2 */
    /*  716 */ 0x77bc468b065f8fdb, /* GL_NV_path_rendering */
    /*  717 */ 0x2f70022ecb786aed, /* GL_NV_path_rendering_shared_edge */
    /*  718 */ 0x0b44f2e633646ab5, /* GL_NV_pixel_buffer_object */
    /*  719 */ 0x43d8732157b4106d, /* GL_NV_pixel_data_range */
    /*  720 */ 0x839efae2d0736a4c, /* GL_NV_point_sprite */
    /*  721 */ 0x3330eb9a4ceb6c0c, /* GL_NV_polygon_mode */
    /*  722 */ 0x6512c3d1922a98db, /* GL_NV_present_video */
    /*  723 */ 0x8c542b195b5b3c94, /* GL_NV_primitive_restart */
    /*  724 */ 0x0cacb49d8f1c105a, /* GL_NV_primitive_shading_rate */
    /*  725 */ 0x9b1b0441d8d19911, /* GL_NV_query_resource */
    /*  726 */ 0x15f0661a8638b338, /* GL_NV_query_resource_tag */
    /*  727 */ 0xdd74002f450fb368, /* GL_NV_ray_tracing */
    /*  728 */ 0x182d9aed7af08983, /* GL_NV_ray_tracing_motion_blur */
    /*  729 */ 0xb51b7c433236bd06, /* GL_NV_read_buffer */
    /*  730 */ 0xc91023f37354df43, /* GL_NV_read_buffer_front */
    /*  731 */ 0x3dfff3ed25362196, /* GL_NV_read_depth */
    /*  732 */ 0x55261906f55bb17a, /* GL_NV_read_depth_stencil */
    /*  733 */ 0x7bab8fd7e4a04ee8, /* GL_NV_read_stencil */
    /*  734 */ 0xd791c5687139b905, /* GL_NV_register_combiners */
    /*  735 */ 0x8814ab530e95a798, /* GL_NV_register_combiners2 */
    /*  736 */ 0xb46bd57f88e91d64, /* GL_NV_representative_fragment_test */
    /*  737 */ 0xc4eada8b9cbe17c0, /* GL_NV_robustness_video_memory_purge */
    /*  738 */ 0x2c2775936dc2a882, /* GL_NV_sRGB_formats */
    /*  739 */ 0xc50ae467eedfefde, /* GL_NV_sample_locations */
    /*  740 */ 0x446a05466a6d6429, /* GL_NV_sample_mask_override_coverage */
    /*  741 */ 0x4247a4acbfcdb098, /* GL_NV_scissor_exclusive */
    /*  742 */ 0x0383e334dd39d9a0, /* GL_NV_shader_atomic_counters */
    /*  743 */ 0x02399be47930fbf4, /* GL_NV_shader_atomic_float */
    /*  744 */ 0x8c8c8962eadf1230, /* GL_NV_shader_atomic_float64 */
    /*  745 */ 0x4c3311286ab16152, /* GL_NV_shader_atomic_fp16_vector */
    /*  746 */ 0xb14dbc3c64a1326f, /* GL_NV_shader_atomic_int64 */
    /*  747 */ 0x3ae6fc5c42bab2c2, /* GL_NV_shader_buffer_load */
    /*  748 */ 0x1c05604500113691, /* GL_NV_shader_buffer_store */
    /*  749 */ 0x22e85dcf4a44b2f7, /* GL_NV_shader_invocation_reorder */
    /*  750 */ 0xbb5c10f38325fdf8, /* GL_NV_shader_noperspective_interpolation */
    /*  751 */ 0x6d97890637a77774, /* GL_NV_shader_sm_builtins */
    /*  752 */ 0xaf5c0eb5c483eb28, /* GL_NV_shader_storage_buffer_object */
    /*  753 */ 0x826afa0d2f696f22, /* GL_NV_shader_subgroup_partitioned */
    /*  754 */ 0x7b3f8fad48cfd967, /* GL_NV_shader_texture_footprint */
    /*  755 */ 0xfd2aa76218c9354e, /* GL_NV_shader_thread_group */
    /*  756 */ 0x74a053165bf8ada4, /* GL_NV_shader_thread_shuffle */
    /*  757 */ 0xf9355d5174ef4c70, /* GL_NV_shading_rate_image */
    /*  758 */ 0x28944cfc0cca07ec, /* GL_NV_shadow_samplers_array */
    /*  759 */ 0xfdbd6232791ce36f, /* GL_NV_shadow_samplers_cube */
    /*  760 */ 0x56dc6bb2a7d8736f, /* GL_NV_stereo_view_rendering */
    /*  761 */ 0x2410081ec485d619, /* GL_NV_tessellation_program5 */
    /*  762 */ 0x6a6887942da6a4c4, /* GL_NV_texgen_emboss */
    /*  763 */ 0x35865e06d7292c9b, /* GL_NV_texgen_reflection */
    /*  764 */ 0x282f885e0bfd25de, /* GL_NV_texture_barrier */
    /*  765 */ 0x373989acbf486191, /* GL_NV_texture_border_clamp */
    /*  766 */ 0x4d5276bd5a1f04ce, /* GL_NV_texture_compression_s3tc_update */
    /*  767 */ 0x25b70b1f5bbed713, /* GL_NV_texture_compression_vtc */
    /*  768 */ 0x84b70fe53fcdcde1, /* GL_NV_texture_env_combine4 */
    /*  769 */ 0x07e650e01fee3678, /* GL_NV_texture_expand_normal */
    /*  770 */ 0x4679eee96470073f, /* GL_NV_texture_multisample */
    /*  771 */ 0xcba499c04274ad25, /* GL_NV_texture_npot_2D_mipmap */
    /*  772 */ 0xccbc8154a70c3605, /* GL_NV_texture_rectangle */
    /*  773 */ 0x5da6e59a7e51bc40, /* GL_NV_texture_rectangle_compressed */
    /*  774 */ 0x8a67a1269b408254, /* GL_NV_texture_shader */
    /*  775 */ 0x816b354fd0cd9228, /* GL_NV_texture_shader2 */
    /*  776 */ 0x5526327fa18acdde, /* GL_NV_texture_shader3 */
    /*  777 */ 0x39f7dcc9a62c5153, /* GL_NV_timeline_semaphore */
    /*  778 */ 0xf09b77c741443fcb, /* GL_NV_transform_feedback */
    /*  779 */ 0x32519ec17990e826, /* GL_NV_transform_feedback2 */
    /*  780 */ 0x5600eb6f04e474ee, /* GL_NV_uniform_buffer_std430_layout */
    /*  781 */ 0x5a3050e67df48f2c, /* GL_NV_uniform_buffer_unified_memory */
    /*  782 */ 0xc270d7ffe7e44b23, /* GL_NV_vdpau_interop */
    /*  783 */ 0x613710111a2944f7, /* GL_NV_vdpau_interop2 */
    /*  784 */ 0x2670ae7bcc80188e, /* GL_NV_vertex_array_range */
    /*  785 */ 0x79ae834a103024c5, /* GL_NV_vertex_array_range2 */
    /*  786 */ 0xe688c60fe2e62039, /* GL_NV_vertex_attrib_integer_64bit */
    /*  787 */ 0x7e2fb60c66658e57, /* GL_NV_vertex_buffer_unified_memory */
    /*  788 */ 0x527413b984649803, /* GL_NV_vertex_program */
    /*  789 */ 0x7d2fc2b85898af18, /* GL_NV_vertex_program1_1 */
    /*  790 */ 0x2d5a70a0a1d00d78, /* GL_NV_vertex_program2 */
    /*  791 */ 0x747ed48148981054, /* GL_NV_vertex_program2_option */
    /*  792 */ 0xc13798df29c369e2, /* GL_NV_vertex_program3 */
    /*  793 */ 0xa796194638bbdc74, /* GL_NV_vertex_program4 */
    /*  794 */ 0x89ae752e4cfcfae8, /* GL_NV_video_capture */
    /*  795 */ 0x1b9db3e10e73323b, /* GL_NV_viewport_array */
    /*  796 */ 0x4e9c3fc0856350f9, /* GL_NV_viewport_array2 */
    /*  797 */ 0xdf18b1c27e48f432, /* GL_NV_viewport_swizzle */
    /*  798 */ 0xc05411382c7e9b6f, /* GL_OES_EGL_image */
    /*  799 */ 0xb3f47895b1c4d5f8, /* GL_OES_EGL_image_external */
    /*  800 */ 0xbbae531ab8d7e16f, /* GL_OES_EGL_image_external_essl3 */
    /*  801 */ 0x55f4d891b16ad96c, /* GL_OES_byte_coordinates */
    /*  802 */ 0x866125fa75aab774, /* GL_OES_compressed_ETC1_RGB8_sub_texture */
    /*  803 */ 0x5b4df7888b81a92b, /* GL_OES_compressed_ETC1_RGB8_texture */
    /*  804 */ 0xd1ae5222afe37da5, /* GL_OES_compressed_paletted_texture */
    /*  805 */ 0xc5e1ddc1ea43276e, /* GL_OES_copy_image */
    /*  806 */ 0xa3f0bbbc7660d96c, /* GL_OES_depth24 */
    /*  807 */ 0xb8b2dd3478f1ec83, /* GL_OES_depth32 */
    /*  808 */ 0x67516f69dbc843f6, /* GL_OES_depth_texture */
    /*  809 */ 0x012b99c59ced284f, /* GL_OES_draw_buffers_indexed */
    /*  810 */ 0x4638dd889d2b7eab, /* GL_OES_draw_elements_base_vertex */
    /*  811 */ 0x29e68bee4a9705f1, /* GL_OES_element_index_uint */
    /*  812 */ 0xe0b0d82d6dc31dae, /* GL_OES_fbo_render_mipmap */
    /*  813 */ 0x9f59932407436633, /* GL_OES_fixed_point */
    /*  814 */ 0x116a77aa55534c76, /* GL_OES_fragment_precision_high */
    /*  815 */ 0x5e6f26587d551ffc, /* GL_OES_geometry_point_size */
    /*  816 */ 0xaa384a84e450d595, /* GL_OES_geometry_shader */
    /*  817 */ 0x503ad238c5e97931, /* GL_OES_get_program_binary */
    /*  818 */ 0x77f35c2a7a2bd390, /* GL_OES_gpu_shader5 */
    /*  819 */ 0x22e521fe25c89a3b, /* GL_OES_mapbuffer */
    /*  820 */ 0xb124b23bca92b355, /* GL_OES_packed_depth_stencil */
    /*  821 */ 0x303e15e4f8fb9ee6, /* GL_OES_primitive_bounding_box */
    /*  822 */ 0xc8d3d0277204ac3d, /* GL_OES_query_matrix */
    /*  823 */ 0xca46680e5cfc3e18, /* GL_OES_read_format */
    /*  824 */ 0xd6c9bec1dd5d5b89, /* GL_OES_required_internalformat */
    /*  825 */ 0xccb18f4e376e6c74, /* GL_OES_rgb8_rgba8 */
    /*  826 */ 0xcb740362814f4ca0, /* GL_OES_sample_shading */
    /*  827 */ 0x8f4eb2b127c21f67, /* GL_OES_sample_variables */
    /*  828 */ 0xa023718702859970, /* GL_OES_shader_image_atomic */
    /*  829 */ 0x8cc1262bb8c2d393, /* GL_OES_shader_io_blocks */
    /*  830 */ 0xc772b78382e1a793, /* GL_OES_shader_multisample_interpolation */
    /*  831 */ 0xbcbfeb8171756944, /* GL_OES_single_precision */
    /*  832 */ 0x4e9710576f516b4e, /* GL_OES_standard_derivatives */
    /*  833 */ 0x79f1937e076eb6e0, /* GL_OES_stencil1 */
    /*  834 */ 0x7361db1a08c53c55, /* GL_OES_stencil4 */
    /*  835 */ 0x6df979b4adc4989b, /* GL_OES_surfaceless_context */
    /*  836 */ 0xdc7532bffc48cb01, /* GL_OES_tessellation_point_size */
    /*  837 */ 0x8bbb4c0c94dc1415, /* GL_OES_tessellation_shader */
    /*  838 */ 0xccac53b0ed36c73c, /* GL_OES_texture_3D */
    /*  839 */ 0xedc39fcb928c7be5, /* GL_OES_texture_border_clamp */
    /*  840 */ 0xc7d6a2d8a596bf50, /* GL_OES_texture_buffer */
    /*  841 */ 0x552cece98cadbaa6, /* GL_OES_texture_compression_astc */
    /*  842 */ 0xfad8c3de7cf9ffc4, /* GL_OES_texture_cube_map_array */
    /*  843 */ 0x32ed502b39dd1594, /* GL_OES_texture_float */
    /*  844 */ 0x5afe2be3731190e1, /* GL_OES_texture_float_linear */
    /*  845 */ 0xa9fdcf0e5b6803dd, /* GL_OES_texture_half_float */
    /*  846 */ 0x0011e43010189be7, /* GL_OES_texture_half_float_linear */
    /*  847 */ 0xe706ff7638659b7e, /* GL_OES_texture_npot */
    /*  848 */ 0xdfa8a0ccd9d60d53, /* GL_OES_texture_stencil8 */
    /*  849 */ 0xbc655ee4febdcfca, /* GL_OES_texture_storage_multisample_2d_array */
    /*  850 */ 0x8fc2a146f6290d39, /* GL_OES_texture_view */
    /*  851 */ 0x7cd6041965da7d3c, /* GL_OES_vertex_array_object */
    /*  852 */ 0x8d77aa22bdd641e8, /* GL_OES_vertex_half_float */
    /*  853 */ 0x244e9e511573b959, /* GL_OES_vertex_type_10_10_10_2 */
    /*  854 */ 0x2e0ac92809baabbd, /* GL_OES_viewport_array */
    /*  855 */ 0xe4756190e24cfae1, /* GL_OML_interlace */
    /*  856 */ 0xf00e1502b0d1f5d7, /* GL_OML_resample */
    /*  857 */ 0xee17f2c40613fa28, /* GL_OML_subsample */
    /*  858 */ 0x462789e64be7acd7, /* GL_OVR_multiview */
    /*  859 */ 0x4d3b083404c10e3f, /* GL_OVR_multiview2 */
    /*  860 */ 0xdd9450d3b97e069b, /* GL_OVR_multiview_multisampled_render_to_texture */
    /*  861 */ 0xb1df54452698a7be, /* GL_PGI_misc_hints */
    /*  862 */ 0x830c412288059800, /* GL_PGI_vertex_hints */
    /*  863 */ 0x03b99dd37fd50188, /* GL_QCOM_YUV_texture_gather */
    /*  864 */ 0x3aa5ff0497f38e96, /* GL_QCOM_alpha_test */
    /*  865 */ 0x8b6f2c405eed8fc9, /* GL_QCOM_binning_control */
    /*  866 */ 0xd69ddd5074f27947, /* GL_QCOM_driver_control */
    /*  867 */ 0x2cfff6c37fa549bc, /* GL_QCOM_extended_get */
    /*  868 */ 0xa36cbb8c3a77c3a1, /* GL_QCOM_extended_get2 */
    /*  869 */ 0x1359ba3cc79be309, /* GL_QCOM_frame_extrapolation */
    /*  870 */ 0xa96b1c721f28a1c2, /* GL_QCOM_framebuffer_foveated */
    /*  871 */ 0xaa7b8918e97b02c0, /* GL_QCOM_image_processing */
    /*  872 */ 0x87abde46d2fd3251, /* GL_QCOM_image_processing2 */
    /*  873 */ 0x822886625bd76c4a, /* GL_QCOM_motion_estimation */
    /*  874 */ 0x62c4f9e3d0cf2728, /* GL_QCOM_perfmon_global_mode */
    /*  875 */ 0x6667e13047800b18, /* GL_QCOM_render_sRGB_R8_RG8 */
    /*  876 */ 0x005a335cb406a184, /* GL_QCOM_render_shared_exponent */
    /*  877 */ 0x0668ea2d27f4b9c7, /* GL_QCOM_shader_framebuffer_fetch_noncoherent */
    /*  878 */ 0x2f8fba53941074de, /* GL_QCOM_shader_framebuffer_fetch_rate */
    /*  879 */ 0x360f4bc982306308, /* GL_QCOM_shading_rate */
    /*  880 */ 0xa23647ccb657fc93, /* GL_QCOM_texture_foveated */
    /*  881 */ 0xac6fb0841696dc5f, /* GL_QCOM_texture_foveated2 */
    /*  882 */ 0xb7f306a63180d3df, /* GL_QCOM_texture_foveated_subsampled_layout */
    /*  883 */ 0x70d9c41ab20f93f9, /* GL_QCOM_texture_lod_bias */
    /*  884 */ 0x288ca2e6c7c5c86d, /* GL_QCOM_tiled_rendering */
    /*  885 */ 0x28eabd27e2f106a8, /* GL_QCOM_writeonly_rendering */
    /*  886 */ 0xafb9cdf7b9a2826a, /* GL_QCOM_ycbcr_degamma */
    /*  887 */ 0x14dac5dff736a3df, /* GL_REND_screen_coordinates */
    /*  888 */ 0x93469fe128fc0919, /* GL_S3_s3tc */
    /*  889 */ 0x8c7ee523e6ed026a, /* GL_SGIS_detail_texture */
    /*  890 */ 0xe54deb13059b8c4c, /* GL_SGIS_fog_function */
    /*  891 */ 0xb1b31f0af9b1e3c1, /* GL_SGIS_generate_mipmap */
    /*  892 */ 0x39568b3690efef18, /* GL_SGIS_multisample */
    /*  893 */ 0xf250c15acefa1ac9, /* GL_SGIS_pixel_texture */
    /*  894 */ 0x9b7bb525c279e853, /* GL_SGIS_point_line_texgen */
    /*  895 */ 0x4e3e0fa2dfafd5b4, /* GL_SGIS_point_parameters */
    /*  896 */ 0x4a4aa0671eb15c9f, /* GL_SGIS_sharpen_texture */
    /*  897 */ 0xe3880e70b14a01ef, /* GL_SGIS_texture4D */
    /*  898 */ 0x70c7cab7e228743c, /* GL_SGIS_texture_border_clamp */
    /*  899 */ 0x04eb37e0f3c4686a, /* GL_SGIS_texture_color_mask */
    /*  900 */ 0xb6400bcd7a346c99, /* GL_SGIS_texture_edge_clamp */
    /*  901 */ 0xd79b6287779eca3f, /* GL_SGIS_texture_filter4 */
    /*  902 */ 0xf25eb0173c775af1, /* GL_SGIS_texture_lod */
    /*  903 */ 0x4b818d48997acf33, /* GL_SGIS_texture_select */
    /*  904 */ 0x42053ed5c2789d8a, /* GL_SGIX_async */
    /*  905 */ 0x9baec4623ae00aa8, /* GL_SGIX_async_histogram */
    /*  906 */ 0xbed04383395711b9, /* GL_SGIX_async_pixel */
    /*  907 */ 0xd3cc8d1ef603a7f6, /* GL_SGIX_blend_alpha_minmax */
    /*  908 */ 0xe60980f13acb1fe8, /* GL_SGIX_calligraphic_fragment */
    /*  909 */ 0x5d613989907c2996, /* GL_SGIX_clipmap */
    /*  910 */ 0x8fa248e9981db96e, /* GL_SGIX_convolution_accuracy */
    /*  911 */ 0x47ef8f4254eec5a0, /* GL_SGIX_depth_pass_instrument */
    /*  912 */ 0x3489d57ce09fdb5e, /* GL_SGIX_depth_texture */
    /*  913 */ 0x37a8cdae9276920f, /* GL_SGIX_flush_raster */
    /*  914 */ 0x21b4c2f4db4fb980, /* GL_SGIX_fog_offset */
    /*  915 */ 0x5379c01e285814d7, /* GL_SGIX_fragment_lighting */
    /*  916 */ 0xbc4f1c742be26f3f, /* GL_SGIX_framezoom */
    /*  917 */ 0xd8ea1ff9ab303390, /* GL_SGIX_igloo_interface */
    /*  918 */ 0x828685155c316d20, /* GL_SGIX_instruments */
    /*  919 */ 0xaf75b3c8a321fd9b, /* GL_SGIX_interlace */
    /*  920 */ 0xac3c1477e6f161ef, /* GL_SGIX_ir_instrument1 */
    /*  921 */ 0xe6f72d5da01567e9, /* GL_SGIX_list_priority */
    /*  922 */ 0x945b05eefbbaf60c, /* GL_SGIX_pixel_texture */
    /*  923 */ 0x3c667c7037c70246, /* GL_SGIX_pixel_tiles */
    /*  924 */ 0x17349f9e9a6e5976, /* GL_SGIX_polynomial_ffd */
    /*  925 */ 0xe64b4cbd5d5fe178, /* GL_SGIX_reference_plane */
    /*  926 */ 0x007a4678f7628880, /* GL_SGIX_resample */
    /*  927 */ 0xfc833b6c6a1f8cc1, /* GL_SGIX_scalebias_hint */
    /*  928 */ 0xfe04490bc9621226, /* GL_SGIX_shadow */
    /*  929 */ 0xa1f64483e1ed6c09, /* GL_SGIX_shadow_ambient */
    /*  930 */ 0x1b1eb2d33e2626cb, /* GL_SGIX_sprite */
    /*  931 */ 0xab712623aed89578, /* GL_SGIX_subsample */
    /*  932 */ 0xf6707a8df70625ff, /* GL_SGIX_tag_sample_buffer */
    /*  933 */ 0xb31cc86db966473b, /* GL_SGIX_texture_add_env */
    /*  934 */ 0x8b7acea8e9290fae, /* GL_SGIX_texture_coordinate_clamp */
    /*  935 */ 0xb5df7fecc6d921f7, /* GL_SGIX_texture_lod_bias */
    /*  936 */ 0xb819f1015daf16c4, /* GL_SGIX_texture_multi_buffer */
    /*  937 */ 0x3c9d7b66aea3cba1, /* GL_SGIX_texture_scale_bias */
    /*  938 */ 0xe9afc853af27422d, /* GL_SGIX_vertex_preclip */
    /*  939 */ 0x3bb1183ffedb9c68, /* GL_SGIX_ycrcb */
    /*  940 */ 0x004ffc30998c20db, /* GL_SGIX_ycrcb_subsample */
    /*  941 */ 0x7ab4a4b4639c69df, /* GL_SGIX_ycrcba */
    /*  942 */ 0x014fc2d56670cd5a, /* GL_SGI_color_matrix */
    /*  943 */ 0x5f28de108b449e5d, /* GL_SGI_color_table */
    /*  944 */ 0xa03c2d1d2eeb1bd2, /* GL_SGI_texture_color_table */
    /*  945 */ 0xd3460591a825bcf6, /* GL_SUNX_constant_data */
    /*  946 */ 0x4e5296cda0471f61, /* GL_SUN_convolution_border_modes */
    /*  947 */ 0xe19c670da3369515, /* GL_SUN_global_alpha */
    /*  948 */ 0xbd8a54b9db901974, /* GL_SUN_mesh_array */
    /*  949 */ 0xa52af6dd6a5fb2d3, /* GL_SUN_slice_accum */
    /*  950 */ 0xbeb30cddf53ae288, /* GL_SUN_triangle_list */
    /*  951 */ 0xd0bf54f2a8798b55, /* GL_SUN_vertex */
    /*  952 */ 0x156892df7146814d, /* GL_VIV_shader_binary */
    /*  953 */ 0xf09a257256bde8f6, /* GL_WIN_phong_shading */
    /*  954 */ 0x5a3e106713a38cff  /* GL_WIN_specular_fog */
};

static void glad_gl_load_pfn_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr, uint16_t pfnStart, uint32_t numPfns)
{
    uint32_t pfnIdx;

    #ifdef __clang__
    #pragma nounroll
    #endif
    for (pfnIdx = pfnStart; pfnIdx < pfnStart + numPfns; ++pfnIdx) {
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_resolve_aliases(GladGLContext *context) {
    static const GladAliasPair_t s_aliases[] = {
        {   66,  864 }, /* glActiveTexture and glActiveTextureARB */
        {  864,   66 }, /* glActiveTextureARB and glActiveTexture */
        {  928,  108 }, /* glAttachObjectARB and glAttachShader */
        {  108,  928 }, /* glAttachShader and glAttachObjectARB */
        {  215, 1845 }, /* glBeginConditionalRender and glBeginConditionalRenderNV */
        { 1845,  215 }, /* glBeginConditionalRenderNV and glBeginConditionalRender */
        {   87,  901 }, /* glBeginQuery and glBeginQueryARB */
        {  901,   87 }, /* glBeginQueryARB and glBeginQuery */
        {  208, 1660 }, /* glBeginTransformFeedback and glBeginTransformFeedbackEXT */
        {  208, 2123 }, /* glBeginTransformFeedback and glBeginTransformFeedbackNV */
        { 1660,  208 }, /* glBeginTransformFeedbackEXT and glBeginTransformFeedback */
        { 1660, 2123 }, /* glBeginTransformFeedbackEXT and glBeginTransformFeedbackNV */
        { 2123,  208 }, /* glBeginTransformFeedbackNV and glBeginTransformFeedback */
        { 2123, 1660 }, /* glBeginTransformFeedbackNV and glBeginTransformFeedbackEXT */
        {  109, 1046 }, /* glBindAttribLocation and glBindAttribLocationARB */
        { 1046,  109 }, /* glBindAttribLocationARB and glBindAttribLocation */
        {   92,  992 }, /* glBindBuffer and glBindBufferARB */
        {  992,   92 }, /* glBindBufferARB and glBindBuffer */
        {  211, 1664 }, /* glBindBufferBase and glBindBufferBaseEXT */
        {  211, 2128 }, /* glBindBufferBase and glBindBufferBaseNV */
        { 1664,  211 }, /* glBindBufferBaseEXT and glBindBufferBase */
        { 1664, 2128 }, /* glBindBufferBaseEXT and glBindBufferBaseNV */
        { 2128,  211 }, /* glBindBufferBaseNV and glBindBufferBase */
        { 2128, 1664 }, /* glBindBufferBaseNV and glBindBufferBaseEXT */
        { 1663, 2127 }, /* glBindBufferOffsetEXT and glBindBufferOffsetNV */
        { 2127, 1663 }, /* glBindBufferOffsetNV and glBindBufferOffsetEXT */
        {  210, 1662 }, /* glBindBufferRange and glBindBufferRangeEXT */
        {  210, 2126 }, /* glBindBufferRange and glBindBufferRangeNV */
        { 1662,  210 }, /* glBindBufferRangeEXT and glBindBufferRange */
        { 1662, 2126 }, /* glBindBufferRangeEXT and glBindBufferRangeNV */
        { 2126,  210 }, /* glBindBufferRangeNV and glBindBufferRange */
        { 2126, 1662 }, /* glBindBufferRangeNV and glBindBufferRangeEXT */
        {  241, 1162 }, /* glBindFragDataLocation and glBindFragDataLocationEXT */
        { 1162,  241 }, /* glBindFragDataLocationEXT and glBindFragDataLocation */
        {  317, 2563 }, /* glBindFragDataLocationIndexed and glBindFragDataLocationIndexedEXT */
        { 2563,  317 }, /* glBindFragDataLocationIndexedEXT and glBindFragDataLocationIndexed */
        {  796, 2187 }, /* glBindProgramARB and glBindProgramNV */
        { 2187,  796 }, /* glBindProgramNV and glBindProgramARB */
        {   58, 1648 }, /* glBindTexture and glBindTextureEXT */
        { 1648,   58 }, /* glBindTextureEXT and glBindTexture */
        {  282, 2734 }, /* glBindVertexArray and glBindVertexArrayOES */
        { 2734,  282 }, /* glBindVertexArrayOES and glBindVertexArray */
        { 2541, 1773 }, /* glBlendBarrier and glBlendBarrierKHR */
        { 2541, 1826 }, /* glBlendBarrier and glBlendBarrierNV */
        { 1773, 2541 }, /* glBlendBarrierKHR and glBlendBarrier */
        { 1773, 1826 }, /* glBlendBarrierKHR and glBlendBarrierNV */
        { 1826, 2541 }, /* glBlendBarrierNV and glBlendBarrier */
        { 1826, 1773 }, /* glBlendBarrierNV and glBlendBarrierKHR */
        {   82, 1160 }, /* glBlendColor and glBlendColorEXT */
        { 1160,   82 }, /* glBlendColorEXT and glBlendColor */
        {   83, 1164 }, /* glBlendEquation and glBlendEquationEXT */
        { 1164,   83 }, /* glBlendEquationEXT and glBlendEquation */
        {  346,  664 }, /* glBlendEquationi and glBlendEquationIndexedAMD */
        {  346,  789 }, /* glBlendEquationi and glBlendEquationiARB */
        {  346, 2585 }, /* glBlendEquationi and glBlendEquationiEXT */
        {  346, 2698 }, /* glBlendEquationi and glBlendEquationiOES */
        {  789,  664 }, /* glBlendEquationiARB and glBlendEquationIndexedAMD */
        {  789,  346 }, /* glBlendEquationiARB and glBlendEquationi */
        {  789, 2585 }, /* glBlendEquationiARB and glBlendEquationiEXT */
        {  789, 2698 }, /* glBlendEquationiARB and glBlendEquationiOES */
        { 2585,  664 }, /* glBlendEquationiEXT and glBlendEquationIndexedAMD */
        { 2585,  346 }, /* glBlendEquationiEXT and glBlendEquationi */
        { 2585,  789 }, /* glBlendEquationiEXT and glBlendEquationiARB */
        { 2585, 2698 }, /* glBlendEquationiEXT and glBlendEquationiOES */
        {  664,  346 }, /* glBlendEquationIndexedAMD and glBlendEquationi */
        {  664,  789 }, /* glBlendEquationIndexedAMD and glBlendEquationiARB */
        {  664, 2585 }, /* glBlendEquationIndexedAMD and glBlendEquationiEXT */
        {  664, 2698 }, /* glBlendEquationIndexedAMD and glBlendEquationiOES */
        { 2698,  664 }, /* glBlendEquationiOES and glBlendEquationIndexedAMD */
        { 2698,  346 }, /* glBlendEquationiOES and glBlendEquationi */
        { 2698,  789 }, /* glBlendEquationiOES and glBlendEquationiARB */
        { 2698, 2585 }, /* glBlendEquationiOES and glBlendEquationiEXT */
        {  103, 1161 }, /* glBlendEquationSeparate and glBlendEquationSeparateEXT */
        { 1161,  103 }, /* glBlendEquationSeparateEXT and glBlendEquationSeparate */
        {  347,  665 }, /* glBlendEquationSeparatei and glBlendEquationSeparateIndexedAMD */
        {  347,  790 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiARB */
        {  347, 2586 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiEXT */
        {  347, 2699 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiOES */
        {  790,  665 }, /* glBlendEquationSeparateiARB and glBlendEquationSeparateIndexedAMD */
        {  790,  347 }, /* glBlendEquationSeparateiARB and glBlendEquationSeparatei */
        {  790, 2586 }, /* glBlendEquationSeparateiARB and glBlendEquationSeparateiEXT */
        {  790, 2699 }, /* glBlendEquationSeparateiARB and glBlendEquationSeparateiOES */
        { 2586,  665 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparateIndexedAMD */
        { 2586,  347 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparatei */
        { 2586,  790 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparateiARB */
        { 2586, 2699 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparateiOES */
        {  665,  347 }, /* glBlendEquationSeparateIndexedAMD and glBlendEquationSeparatei */
        {  665,  790 }, /* glBlendEquationSeparateIndexedAMD and glBlendEquationSeparateiARB */
        {  665, 2586 }, /* glBlendEquationSeparateIndexedAMD and glBlendEquationSeparateiEXT */
        {  665, 2699 }, /* glBlendEquationSeparateIndexedAMD and glBlendEquationSeparateiOES */
        { 2699,  665 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparateIndexedAMD */
        { 2699,  347 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparatei */
        { 2699,  790 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparateiARB */
        { 2699, 2586 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparateiEXT */
        {  348,  662 }, /* glBlendFunci and glBlendFuncIndexedAMD */
        {  348,  791 }, /* glBlendFunci and glBlendFunciARB */
        {  348, 2587 }, /* glBlendFunci and glBlendFunciEXT */
        {  348, 2700 }, /* glBlendFunci and glBlendFunciOES */
        {  791,  662 }, /* glBlendFunciARB and glBlendFuncIndexedAMD */
        {  791,  348 }, /* glBlendFunciARB and glBlendFunci */
        {  791, 2587 }, /* glBlendFunciARB and glBlendFunciEXT */
        {  791, 2700 }, /* glBlendFunciARB and glBlendFunciOES */
        { 2587,  662 }, /* glBlendFunciEXT and glBlendFuncIndexedAMD */
        { 2587,  348 }, /* glBlendFunciEXT and glBlendFunci */
        { 2587,  791 }, /* glBlendFunciEXT and glBlendFunciARB */
        { 2587, 2700 }, /* glBlendFunciEXT and glBlendFunciOES */
        {  662,  348 }, /* glBlendFuncIndexedAMD and glBlendFunci */
        {  662,  791 }, /* glBlendFuncIndexedAMD and glBlendFunciARB */
        {  662, 2587 }, /* glBlendFuncIndexedAMD and glBlendFunciEXT */
        {  662, 2700 }, /* glBlendFuncIndexedAMD and glBlendFunciOES */
        { 2700,  662 }, /* glBlendFunciOES and glBlendFuncIndexedAMD */
        { 2700,  348 }, /* glBlendFunciOES and glBlendFunci */
        { 2700,  791 }, /* glBlendFunciOES and glBlendFunciARB */
        { 2700, 2587 }, /* glBlendFunciOES and glBlendFunciEXT */
        {   75, 1163 }, /* glBlendFuncSeparate and glBlendFuncSeparateEXT */
        {   75, 1754 }, /* glBlendFuncSeparate and glBlendFuncSeparateINGR */
        { 1163,   75 }, /* glBlendFuncSeparateEXT and glBlendFuncSeparate */
        { 1163, 1754 }, /* glBlendFuncSeparateEXT and glBlendFuncSeparateINGR */
        {  349,  663 }, /* glBlendFuncSeparatei and glBlendFuncSeparateIndexedAMD */
        {  349,  792 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiARB */
        {  349, 2588 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiEXT */
        {  349, 2701 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiOES */
        {  792,  663 }, /* glBlendFuncSeparateiARB and glBlendFuncSeparateIndexedAMD */
        {  792,  349 }, /* glBlendFuncSeparateiARB and glBlendFuncSeparatei */
        {  792, 2588 }, /* glBlendFuncSeparateiARB and glBlendFuncSeparateiEXT */
        {  792, 2701 }, /* glBlendFuncSeparateiARB and glBlendFuncSeparateiOES */
        { 2588,  663 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparateIndexedAMD */
        { 2588,  349 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparatei */
        { 2588,  792 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparateiARB */
        { 2588, 2701 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparateiOES */
        {  663,  349 }, /* glBlendFuncSeparateIndexedAMD and glBlendFuncSeparatei */
        {  663,  792 }, /* glBlendFuncSeparateIndexedAMD and glBlendFuncSeparateiARB */
        {  663, 2588 }, /* glBlendFuncSeparateIndexedAMD and glBlendFuncSeparateiEXT */
        {  663, 2701 }, /* glBlendFuncSeparateIndexedAMD and glBlendFuncSeparateiOES */
        { 1754,   75 }, /* glBlendFuncSeparateINGR and glBlendFuncSeparate */
        { 1754, 1163 }, /* glBlendFuncSeparateINGR and glBlendFuncSeparateEXT */
        { 2701,  663 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparateIndexedAMD */
        { 2701,  349 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparatei */
        { 2701,  792 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparateiARB */
        { 2701, 2588 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparateiEXT */
        {  277, 1485 }, /* glBlitFramebuffer and glBlitFramebufferEXT */
        {  277, 2670 }, /* glBlitFramebuffer and glBlitFramebufferNV */
        { 1485,  277 }, /* glBlitFramebufferEXT and glBlitFramebuffer */
        { 1485, 2670 }, /* glBlitFramebufferEXT and glBlitFramebufferNV */
        { 2670,  277 }, /* glBlitFramebufferNV and glBlitFramebuffer */
        { 2670, 1485 }, /* glBlitFramebufferNV and glBlitFramebufferEXT */
        {   96,  996 }, /* glBufferData and glBufferDataARB */
        {  996,   96 }, /* glBufferDataARB and glBufferData */
        {  534, 2566 }, /* glBufferStorage and glBufferStorageEXT */
        { 2566,  534 }, /* glBufferStorageEXT and glBufferStorage */
        {   97,  997 }, /* glBufferSubData and glBufferSubDataARB */
        {  997,   97 }, /* glBufferSubDataARB and glBufferSubData */
        {  270, 1499 }, /* glCheckFramebufferStatus and glCheckFramebufferStatusEXT */
        { 1499,  270 }, /* glCheckFramebufferStatusEXT and glCheckFramebufferStatus */
        {  214,  782 }, /* glClampColor and glClampColorARB */
        {  782,  214 }, /* glClampColorARB and glClampColor */
        {  395, 2389 }, /* glClearDepthf and glClearDepthfOES */
        { 2389,  395 }, /* glClearDepthfOES and glClearDepthf */
        {  535, 2567 }, /* glClearTexImage and glClearTexImageEXT */
        { 2567,  535 }, /* glClearTexImageEXT and glClearTexImage */
        {  536, 2568 }, /* glClearTexSubImage and glClearTexSubImageEXT */
        { 2568,  536 }, /* glClearTexSubImageEXT and glClearTexSubImage */
        {  306, 2555 }, /* glClientWaitSync and glClientWaitSyncAPPLE */
        { 2555,  306 }, /* glClientWaitSyncAPPLE and glClientWaitSync */
        {  543, 2569 }, /* glClipControl and glClipControlEXT */
        { 2569,  543 }, /* glClipControlEXT and glClipControl */
        {  202, 1474 }, /* glColorMaski and glColorMaskIndexedEXT */
        {  202, 2589 }, /* glColorMaski and glColorMaskiEXT */
        {  202, 2702 }, /* glColorMaski and glColorMaskiOES */
        { 2589, 1474 }, /* glColorMaskiEXT and glColorMaskIndexedEXT */
        { 2589,  202 }, /* glColorMaskiEXT and glColorMaski */
        { 2589, 2702 }, /* glColorMaskiEXT and glColorMaskiOES */
        { 1474,  202 }, /* glColorMaskIndexedEXT and glColorMaski */
        { 1474, 2589 }, /* glColorMaskIndexedEXT and glColorMaskiEXT */
        { 1474, 2702 }, /* glColorMaskIndexedEXT and glColorMaskiOES */
        { 2702, 1474 }, /* glColorMaskiOES and glColorMaskIndexedEXT */
        { 2702,  202 }, /* glColorMaskiOES and glColorMaski */
        { 2702, 2589 }, /* glColorMaskiOES and glColorMaskiEXT */
        {  110,  926 }, /* glCompileShader and glCompileShaderARB */
        {  926,  110 }, /* glCompileShaderARB and glCompileShader */
        {   70,  973 }, /* glCompressedTexImage1D and glCompressedTexImage1DARB */
        {  973,   70 }, /* glCompressedTexImage1DARB and glCompressedTexImage1D */
        {   69,  972 }, /* glCompressedTexImage2D and glCompressedTexImage2DARB */
        {  972,   69 }, /* glCompressedTexImage2DARB and glCompressedTexImage2D */
        {   68,  971 }, /* glCompressedTexImage3D and glCompressedTexImage3DARB */
        {  971,   68 }, /* glCompressedTexImage3DARB and glCompressedTexImage3D */
        {   73,  976 }, /* glCompressedTexSubImage1D and glCompressedTexSubImage1DARB */
        {  976,   73 }, /* glCompressedTexSubImage1DARB and glCompressedTexSubImage1D */
        {   72,  975 }, /* glCompressedTexSubImage2D and glCompressedTexSubImage2DARB */
        {  975,   72 }, /* glCompressedTexSubImage2DARB and glCompressedTexSubImage2D */
        {   71,  974 }, /* glCompressedTexSubImage3D and glCompressedTexSubImage3DARB */
        {  974,   71 }, /* glCompressedTexSubImage3DARB and glCompressedTexSubImage3D */
        {  290, 2664 }, /* glCopyBufferSubData and glCopyBufferSubDataNV */
        { 2664,  290 }, /* glCopyBufferSubDataNV and glCopyBufferSubData */
        {  495, 2570 }, /* glCopyImageSubData and glCopyImageSubDataEXT */
        {  495, 2695 }, /* glCopyImageSubData and glCopyImageSubDataOES */
        { 2570,  495 }, /* glCopyImageSubDataEXT and glCopyImageSubData */
        { 2570, 2695 }, /* glCopyImageSubDataEXT and glCopyImageSubDataOES */
        { 2695,  495 }, /* glCopyImageSubDataOES and glCopyImageSubData */
        { 2695, 2570 }, /* glCopyImageSubDataOES and glCopyImageSubDataEXT */
        {   52, 1204 }, /* glCopyTexImage1D and glCopyTexImage1DEXT */
        { 1204,   52 }, /* glCopyTexImage1DEXT and glCopyTexImage1D */
        {   53, 1205 }, /* glCopyTexImage2D and glCopyTexImage2DEXT */
        { 1205,   53 }, /* glCopyTexImage2DEXT and glCopyTexImage2D */
        {   54, 1206 }, /* glCopyTexSubImage1D and glCopyTexSubImage1DEXT */
        { 1206,   54 }, /* glCopyTexSubImage1DEXT and glCopyTexSubImage1D */
        {   55, 1207 }, /* glCopyTexSubImage2D and glCopyTexSubImage2DEXT */
        { 1207,   55 }, /* glCopyTexSubImage2DEXT and glCopyTexSubImage2D */
        {   65, 1208 }, /* glCopyTexSubImage3D and glCopyTexSubImage3DEXT */
        { 1208,   65 }, /* glCopyTexSubImage3DEXT and glCopyTexSubImage3D */
        {  111,  927 }, /* glCreateProgram and glCreateProgramObjectARB */
        {  927,  111 }, /* glCreateProgramObjectARB and glCreateProgram */
        {  112,  924 }, /* glCreateShader and glCreateShaderObjectARB */
        {  924,  112 }, /* glCreateShaderObjectARB and glCreateShader */
        {  526,  786 }, /* glDebugMessageCallback and glDebugMessageCallbackARB */
        {  526, 2650 }, /* glDebugMessageCallback and glDebugMessageCallbackKHR */
        {  786,  526 }, /* glDebugMessageCallbackARB and glDebugMessageCallback */
        {  786, 2650 }, /* glDebugMessageCallbackARB and glDebugMessageCallbackKHR */
        { 2650,  526 }, /* glDebugMessageCallbackKHR and glDebugMessageCallback */
        { 2650,  786 }, /* glDebugMessageCallbackKHR and glDebugMessageCallbackARB */
        {  524,  784 }, /* glDebugMessageControl and glDebugMessageControlARB */
        {  524, 2648 }, /* glDebugMessageControl and glDebugMessageControlKHR */
        {  784,  524 }, /* glDebugMessageControlARB and glDebugMessageControl */
        {  784, 2648 }, /* glDebugMessageControlARB and glDebugMessageControlKHR */
        { 2648,  524 }, /* glDebugMessageControlKHR and glDebugMessageControl */
        { 2648,  784 }, /* glDebugMessageControlKHR and glDebugMessageControlARB */
        {  525,  785 }, /* glDebugMessageInsert and glDebugMessageInsertARB */
        {  525, 2649 }, /* glDebugMessageInsert and glDebugMessageInsertKHR */
        {  785,  525 }, /* glDebugMessageInsertARB and glDebugMessageInsert */
        {  785, 2649 }, /* glDebugMessageInsertARB and glDebugMessageInsertKHR */
        { 2649,  525 }, /* glDebugMessageInsertKHR and glDebugMessageInsert */
        { 2649,  785 }, /* glDebugMessageInsertKHR and glDebugMessageInsertARB */
        {   93,  993 }, /* glDeleteBuffers and glDeleteBuffersARB */
        {  993,   93 }, /* glDeleteBuffersARB and glDeleteBuffers */
        {  268, 1497 }, /* glDeleteFramebuffers and glDeleteFramebuffersEXT */
        { 1497,  268 }, /* glDeleteFramebuffersEXT and glDeleteFramebuffers */
        {  797, 2188 }, /* glDeleteProgramsARB and glDeleteProgramsNV */
        { 2188,  797 }, /* glDeleteProgramsNV and glDeleteProgramsARB */
        {   85,  899 }, /* glDeleteQueries and glDeleteQueriesARB */
        {  899,   85 }, /* glDeleteQueriesARB and glDeleteQueries */
        {  262, 1491 }, /* glDeleteRenderbuffers and glDeleteRenderbuffersEXT */
        { 1491,  262 }, /* glDeleteRenderbuffersEXT and glDeleteRenderbuffers */
        {  305, 2554 }, /* glDeleteSync and glDeleteSyncAPPLE */
        { 2554,  305 }, /* glDeleteSyncAPPLE and glDeleteSync */
        {  381, 2136 }, /* glDeleteTransformFeedbacks and glDeleteTransformFeedbacksNV */
        { 2136,  381 }, /* glDeleteTransformFeedbacksNV and glDeleteTransformFeedbacks */
        {  283,  751 }, /* glDeleteVertexArrays and glDeleteVertexArraysAPPLE */
        {  283, 2735 }, /* glDeleteVertexArrays and glDeleteVertexArraysOES */
        {  751,  283 }, /* glDeleteVertexArraysAPPLE and glDeleteVertexArrays */
        {  751, 2735 }, /* glDeleteVertexArraysAPPLE and glDeleteVertexArraysOES */
        { 2735,  283 }, /* glDeleteVertexArraysOES and glDeleteVertexArrays */
        { 2735,  751 }, /* glDeleteVertexArraysOES and glDeleteVertexArraysAPPLE */
        {  394, 2391 }, /* glDepthRangef and glDepthRangefOES */
        { 2391,  394 }, /* glDepthRangefOES and glDepthRangef */
        {  923,  115 }, /* glDetachObjectARB and glDetachShader */
        {  115,  923 }, /* glDetachShader and glDetachObjectARB */
        {  206, 1297 }, /* glDisablei and glDisableIndexedEXT */
        {  206, 2584 }, /* glDisablei and glDisableiEXT */
        {  206, 2691 }, /* glDisablei and glDisableiNV */
        {  206, 2697 }, /* glDisablei and glDisableiOES */
        { 2584, 1297 }, /* glDisableiEXT and glDisableIndexedEXT */
        { 2584,  206 }, /* glDisableiEXT and glDisablei */
        { 2584, 2691 }, /* glDisableiEXT and glDisableiNV */
        { 2584, 2697 }, /* glDisableiEXT and glDisableiOES */
        { 1297,  206 }, /* glDisableIndexedEXT and glDisablei */
        { 1297, 2584 }, /* glDisableIndexedEXT and glDisableiEXT */
        { 1297, 2691 }, /* glDisableIndexedEXT and glDisableiNV */
        { 1297, 2697 }, /* glDisableIndexedEXT and glDisableiOES */
        { 2691, 1297 }, /* glDisableiNV and glDisableIndexedEXT */
        { 2691,  206 }, /* glDisableiNV and glDisablei */
        { 2691, 2584 }, /* glDisableiNV and glDisableiEXT */
        { 2691, 2697 }, /* glDisableiNV and glDisableiOES */
        { 2697, 1297 }, /* glDisableiOES and glDisableIndexedEXT */
        { 2697,  206 }, /* glDisableiOES and glDisablei */
        { 2697, 2584 }, /* glDisableiOES and glDisableiEXT */
        { 2697, 2691 }, /* glDisableiOES and glDisableiNV */
        {  116, 1041 }, /* glDisableVertexAttribArray and glDisableVertexAttribArrayARB */
        { 1041,  116 }, /* glDisableVertexAttribArrayARB and glDisableVertexAttribArray */
        {   48, 1669 }, /* glDrawArrays and glDrawArraysEXT */
        { 1669,   48 }, /* glDrawArraysEXT and glDrawArrays */
        {  286, 2545 }, /* glDrawArraysInstanced and glDrawArraysInstancedANGLE */
        {  286,  793 }, /* glDrawArraysInstanced and glDrawArraysInstancedARB */
        {  286, 1475 }, /* glDrawArraysInstanced and glDrawArraysInstancedEXT */
        {  286, 2668 }, /* glDrawArraysInstanced and glDrawArraysInstancedNV */
        { 2545,  286 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstanced */
        { 2545,  793 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstancedARB */
        { 2545, 1475 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstancedEXT */
        { 2545, 2668 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstancedNV */
        {  793,  286 }, /* glDrawArraysInstancedARB and glDrawArraysInstanced */
        {  793, 2545 }, /* glDrawArraysInstancedARB and glDrawArraysInstancedANGLE */
        {  793, 1475 }, /* glDrawArraysInstancedARB and glDrawArraysInstancedEXT */
        {  793, 2668 }, /* glDrawArraysInstancedARB and glDrawArraysInstancedNV */
        {  479, 2859 }, /* glDrawArraysInstancedBaseInstance and glDrawArraysInstancedBaseInstanceANGLE */
        {  479, 2560 }, /* glDrawArraysInstancedBaseInstance and glDrawArraysInstancedBaseInstanceEXT */
        { 2859,  479 }, /* glDrawArraysInstancedBaseInstanceANGLE and glDrawArraysInstancedBaseInstance */
        { 2859, 2560 }, /* glDrawArraysInstancedBaseInstanceANGLE and glDrawArraysInstancedBaseInstanceEXT */
        { 2560,  479 }, /* glDrawArraysInstancedBaseInstanceEXT and glDrawArraysInstancedBaseInstance */
        { 2560, 2859 }, /* glDrawArraysInstancedBaseInstanceEXT and glDrawArraysInstancedBaseInstanceANGLE */
        { 1475,  286 }, /* glDrawArraysInstancedEXT and glDrawArraysInstanced */
        { 1475, 2545 }, /* glDrawArraysInstancedEXT and glDrawArraysInstancedANGLE */
        { 1475,  793 }, /* glDrawArraysInstancedEXT and glDrawArraysInstancedARB */
        { 1475, 2668 }, /* glDrawArraysInstancedEXT and glDrawArraysInstancedNV */
        { 2668,  286 }, /* glDrawArraysInstancedNV and glDrawArraysInstanced */
        { 2668, 2545 }, /* glDrawArraysInstancedNV and glDrawArraysInstancedANGLE */
        { 2668,  793 }, /* glDrawArraysInstancedNV and glDrawArraysInstancedARB */
        { 2668, 1475 }, /* glDrawArraysInstancedNV and glDrawArraysInstancedEXT */
        {  104,  788 }, /* glDrawBuffers and glDrawBuffersARB */
        {  104, 1067 }, /* glDrawBuffers and glDrawBuffersATI */
        {  104, 2582 }, /* glDrawBuffers and glDrawBuffersEXT */
        {  788,  104 }, /* glDrawBuffersARB and glDrawBuffers */
        {  788, 1067 }, /* glDrawBuffersARB and glDrawBuffersATI */
        {  788, 2582 }, /* glDrawBuffersARB and glDrawBuffersEXT */
        { 1067,  104 }, /* glDrawBuffersATI and glDrawBuffers */
        { 1067,  788 }, /* glDrawBuffersATI and glDrawBuffersARB */
        { 1067, 2582 }, /* glDrawBuffersATI and glDrawBuffersEXT */
        { 2582,  104 }, /* glDrawBuffersEXT and glDrawBuffers */
        { 2582,  788 }, /* glDrawBuffersEXT and glDrawBuffersARB */
        { 2582, 1067 }, /* glDrawBuffersEXT and glDrawBuffersATI */
        {  298, 2591 }, /* glDrawElementsBaseVertex and glDrawElementsBaseVertexEXT */
        {  298, 2704 }, /* glDrawElementsBaseVertex and glDrawElementsBaseVertexOES */
        { 2591,  298 }, /* glDrawElementsBaseVertexEXT and glDrawElementsBaseVertex */
        { 2591, 2704 }, /* glDrawElementsBaseVertexEXT and glDrawElementsBaseVertexOES */
        { 2704,  298 }, /* glDrawElementsBaseVertexOES and glDrawElementsBaseVertex */
        { 2704, 2591 }, /* glDrawElementsBaseVertexOES and glDrawElementsBaseVertexEXT */
        {  287, 2546 }, /* glDrawElementsInstanced and glDrawElementsInstancedANGLE */
        {  287,  794 }, /* glDrawElementsInstanced and glDrawElementsInstancedARB */
        {  287, 1476 }, /* glDrawElementsInstanced and glDrawElementsInstancedEXT */
        {  287, 2669 }, /* glDrawElementsInstanced and glDrawElementsInstancedNV */
        { 2546,  287 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstanced */
        { 2546,  794 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstancedARB */
        { 2546, 1476 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstancedEXT */
        { 2546, 2669 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstancedNV */
        {  794,  287 }, /* glDrawElementsInstancedARB and glDrawElementsInstanced */
        {  794, 2546 }, /* glDrawElementsInstancedARB and glDrawElementsInstancedANGLE */
        {  794, 1476 }, /* glDrawElementsInstancedARB and glDrawElementsInstancedEXT */
        {  794, 2669 }, /* glDrawElementsInstancedARB and glDrawElementsInstancedNV */
        {  480, 2561 }, /* glDrawElementsInstancedBaseInstance and glDrawElementsInstancedBaseInstanceEXT */
        { 2561,  480 }, /* glDrawElementsInstancedBaseInstanceEXT and glDrawElementsInstancedBaseInstance */
        {  300, 2593 }, /* glDrawElementsInstancedBaseVertex and glDrawElementsInstancedBaseVertexEXT */
        {  300, 2706 }, /* glDrawElementsInstancedBaseVertex and glDrawElementsInstancedBaseVertexOES */
        {  481, 2860 }, /* glDrawElementsInstancedBaseVertexBaseInstance and glDrawElementsInstancedBaseVertexBaseInstanceANGLE */
        {  481, 2562 }, /* glDrawElementsInstancedBaseVertexBaseInstance and glDrawElementsInstancedBaseVertexBaseInstanceEXT */
        { 2860,  481 }, /* glDrawElementsInstancedBaseVertexBaseInstanceANGLE and glDrawElementsInstancedBaseVertexBaseInstance */
        { 2860, 2562 }, /* glDrawElementsInstancedBaseVertexBaseInstanceANGLE and glDrawElementsInstancedBaseVertexBaseInstanceEXT */
        { 2562,  481 }, /* glDrawElementsInstancedBaseVertexBaseInstanceEXT and glDrawElementsInstancedBaseVertexBaseInstance */
        { 2562, 2860 }, /* glDrawElementsInstancedBaseVertexBaseInstanceEXT and glDrawElementsInstancedBaseVertexBaseInstanceANGLE */
        { 2593,  300 }, /* glDrawElementsInstancedBaseVertexEXT and glDrawElementsInstancedBaseVertex */
        { 2593, 2706 }, /* glDrawElementsInstancedBaseVertexEXT and glDrawElementsInstancedBaseVertexOES */
        { 2706,  300 }, /* glDrawElementsInstancedBaseVertexOES and glDrawElementsInstancedBaseVertex */
        { 2706, 2593 }, /* glDrawElementsInstancedBaseVertexOES and glDrawElementsInstancedBaseVertexEXT */
        { 1476,  287 }, /* glDrawElementsInstancedEXT and glDrawElementsInstanced */
        { 1476, 2546 }, /* glDrawElementsInstancedEXT and glDrawElementsInstancedANGLE */
        { 1476,  794 }, /* glDrawElementsInstancedEXT and glDrawElementsInstancedARB */
        { 1476, 2669 }, /* glDrawElementsInstancedEXT and glDrawElementsInstancedNV */
        { 2669,  287 }, /* glDrawElementsInstancedNV and glDrawElementsInstanced */
        { 2669, 2546 }, /* glDrawElementsInstancedNV and glDrawElementsInstancedANGLE */
        { 2669,  794 }, /* glDrawElementsInstancedNV and glDrawElementsInstancedARB */
        { 2669, 1476 }, /* glDrawElementsInstancedNV and glDrawElementsInstancedEXT */
        {   62, 1477 }, /* glDrawRangeElements and glDrawRangeElementsEXT */
        {  299, 2592 }, /* glDrawRangeElementsBaseVertex and glDrawRangeElementsBaseVertexEXT */
        {  299, 2705 }, /* glDrawRangeElementsBaseVertex and glDrawRangeElementsBaseVertexOES */
        { 2592,  299 }, /* glDrawRangeElementsBaseVertexEXT and glDrawRangeElementsBaseVertex */
        { 2592, 2705 }, /* glDrawRangeElementsBaseVertexEXT and glDrawRangeElementsBaseVertexOES */
        { 2705,  299 }, /* glDrawRangeElementsBaseVertexOES and glDrawRangeElementsBaseVertex */
        { 2705, 2592 }, /* glDrawRangeElementsBaseVertexOES and glDrawRangeElementsBaseVertexEXT */
        { 1477,   62 }, /* glDrawRangeElementsEXT and glDrawRangeElements */
        {  386, 2595 }, /* glDrawTransformFeedback and glDrawTransformFeedbackEXT */
        {  386, 2141 }, /* glDrawTransformFeedback and glDrawTransformFeedbackNV */
        { 2595,  386 }, /* glDrawTransformFeedbackEXT and glDrawTransformFeedback */
        { 2595, 2141 }, /* glDrawTransformFeedbackEXT and glDrawTransformFeedbackNV */
        {  489, 2596 }, /* glDrawTransformFeedbackInstanced and glDrawTransformFeedbackInstancedEXT */
        { 2596,  489 }, /* glDrawTransformFeedbackInstancedEXT and glDrawTransformFeedbackInstanced */
        { 2141,  386 }, /* glDrawTransformFeedbackNV and glDrawTransformFeedback */
        { 2141, 2595 }, /* glDrawTransformFeedbackNV and glDrawTransformFeedbackEXT */
        {  205, 1296 }, /* glEnablei and glEnableIndexedEXT */
        {  205, 2583 }, /* glEnablei and glEnableiEXT */
        {  205, 2690 }, /* glEnablei and glEnableiNV */
        {  205, 2696 }, /* glEnablei and glEnableiOES */
        { 2583, 1296 }, /* glEnableiEXT and glEnableIndexedEXT */
        { 2583,  205 }, /* glEnableiEXT and glEnablei */
        { 2583, 2690 }, /* glEnableiEXT and glEnableiNV */
        { 2583, 2696 }, /* glEnableiEXT and glEnableiOES */
        { 1296,  205 }, /* glEnableIndexedEXT and glEnablei */
        { 1296, 2583 }, /* glEnableIndexedEXT and glEnableiEXT */
        { 1296, 2690 }, /* glEnableIndexedEXT and glEnableiNV */
        { 1296, 2696 }, /* glEnableIndexedEXT and glEnableiOES */
        { 2690, 1296 }, /* glEnableiNV and glEnableIndexedEXT */
        { 2690,  205 }, /* glEnableiNV and glEnablei */
        { 2690, 2583 }, /* glEnableiNV and glEnableiEXT */
        { 2690, 2696 }, /* glEnableiNV and glEnableiOES */
        { 2696, 1296 }, /* glEnableiOES and glEnableIndexedEXT */
        { 2696,  205 }, /* glEnableiOES and glEnablei */
        { 2696, 2583 }, /* glEnableiOES and glEnableiEXT */
        { 2696, 2690 }, /* glEnableiOES and glEnableiNV */
        {  117, 1040 }, /* glEnableVertexAttribArray and glEnableVertexAttribArrayARB */
        { 1040,  117 }, /* glEnableVertexAttribArrayARB and glEnableVertexAttribArray */
        {  216, 1846 }, /* glEndConditionalRender and glEndConditionalRenderNV */
        {  216, 1803 }, /* glEndConditionalRender and glEndConditionalRenderNVX */
        { 1846,  216 }, /* glEndConditionalRenderNV and glEndConditionalRender */
        { 1846, 1803 }, /* glEndConditionalRenderNV and glEndConditionalRenderNVX */
        { 1803,  216 }, /* glEndConditionalRenderNVX and glEndConditionalRender */
        { 1803, 1846 }, /* glEndConditionalRenderNVX and glEndConditionalRenderNV */
        {   88,  902 }, /* glEndQuery and glEndQueryARB */
        {  902,   88 }, /* glEndQueryARB and glEndQuery */
        {  209, 1661 }, /* glEndTransformFeedback and glEndTransformFeedbackEXT */
        {  209, 2124 }, /* glEndTransformFeedback and glEndTransformFeedbackNV */
        { 1661,  209 }, /* glEndTransformFeedbackEXT and glEndTransformFeedback */
        { 1661, 2124 }, /* glEndTransformFeedbackEXT and glEndTransformFeedbackNV */
        { 2124,  209 }, /* glEndTransformFeedbackNV and glEndTransformFeedback */
        { 2124, 1661 }, /* glEndTransformFeedbackNV and glEndTransformFeedbackEXT */
        {  303, 2552 }, /* glFenceSync and glFenceSyncAPPLE */
        { 2552,  303 }, /* glFenceSyncAPPLE and glFenceSync */
        {  281,  744 }, /* glFlushMappedBufferRange and glFlushMappedBufferRangeAPPLE */
        {  281, 2603 }, /* glFlushMappedBufferRange and glFlushMappedBufferRangeEXT */
        {  744,  281 }, /* glFlushMappedBufferRangeAPPLE and glFlushMappedBufferRange */
        {  744, 2603 }, /* glFlushMappedBufferRangeAPPLE and glFlushMappedBufferRangeEXT */
        { 2603,  281 }, /* glFlushMappedBufferRangeEXT and glFlushMappedBufferRange */
        { 2603,  744 }, /* glFlushMappedBufferRangeEXT and glFlushMappedBufferRangeAPPLE */
        {  274, 1503 }, /* glFramebufferRenderbuffer and glFramebufferRenderbufferEXT */
        { 1503,  274 }, /* glFramebufferRenderbufferEXT and glFramebufferRenderbuffer */
        {  312,  815 }, /* glFramebufferTexture and glFramebufferTextureARB */
        {  312, 1506 }, /* glFramebufferTexture and glFramebufferTextureEXT */
        {  312, 2707 }, /* glFramebufferTexture and glFramebufferTextureOES */
        {  271, 1500 }, /* glFramebufferTexture1D and glFramebufferTexture1DEXT */
        { 1500,  271 }, /* glFramebufferTexture1DEXT and glFramebufferTexture1D */
        {  272, 1501 }, /* glFramebufferTexture2D and glFramebufferTexture2DEXT */
        { 1501,  272 }, /* glFramebufferTexture2DEXT and glFramebufferTexture2D */
        {  273, 1502 }, /* glFramebufferTexture3D and glFramebufferTexture3DEXT */
        { 1502,  273 }, /* glFramebufferTexture3DEXT and glFramebufferTexture3D */
        {  815,  312 }, /* glFramebufferTextureARB and glFramebufferTexture */
        {  815, 1506 }, /* glFramebufferTextureARB and glFramebufferTextureEXT */
        {  815, 2707 }, /* glFramebufferTextureARB and glFramebufferTextureOES */
        { 1506,  312 }, /* glFramebufferTextureEXT and glFramebufferTexture */
        { 1506,  815 }, /* glFramebufferTextureEXT and glFramebufferTextureARB */
        { 1506, 2707 }, /* glFramebufferTextureEXT and glFramebufferTextureOES */
        {  817, 1891 }, /* glFramebufferTextureFaceARB and glFramebufferTextureFaceEXT */
        { 1891,  817 }, /* glFramebufferTextureFaceEXT and glFramebufferTextureFaceARB */
        {  279,  816 }, /* glFramebufferTextureLayer and glFramebufferTextureLayerARB */
        {  279, 1639 }, /* glFramebufferTextureLayer and glFramebufferTextureLayerEXT */
        {  816,  279 }, /* glFramebufferTextureLayerARB and glFramebufferTextureLayer */
        {  816, 1639 }, /* glFramebufferTextureLayerARB and glFramebufferTextureLayerEXT */
        { 1639,  279 }, /* glFramebufferTextureLayerEXT and glFramebufferTextureLayer */
        { 1639,  816 }, /* glFramebufferTextureLayerEXT and glFramebufferTextureLayerARB */
        { 2707,  312 }, /* glFramebufferTextureOES and glFramebufferTexture */
        { 2707,  815 }, /* glFramebufferTextureOES and glFramebufferTextureARB */
        { 2707, 1506 }, /* glFramebufferTextureOES and glFramebufferTextureEXT */
        {   94,  994 }, /* glGenBuffers and glGenBuffersARB */
        {  994,   94 }, /* glGenBuffersARB and glGenBuffers */
        {  276, 1505 }, /* glGenerateMipmap and glGenerateMipmapEXT */
        { 1505,  276 }, /* glGenerateMipmapEXT and glGenerateMipmap */
        {  269, 1498 }, /* glGenFramebuffers and glGenFramebuffersEXT */
        { 1498,  269 }, /* glGenFramebuffersEXT and glGenFramebuffers */
        {  798, 2190 }, /* glGenProgramsARB and glGenProgramsNV */
        { 2190,  798 }, /* glGenProgramsNV and glGenProgramsARB */
        {   84,  898 }, /* glGenQueries and glGenQueriesARB */
        {  898,   84 }, /* glGenQueriesARB and glGenQueries */
        {  263, 1492 }, /* glGenRenderbuffers and glGenRenderbuffersEXT */
        { 1492,  263 }, /* glGenRenderbuffersEXT and glGenRenderbuffers */
        {  382, 2137 }, /* glGenTransformFeedbacks and glGenTransformFeedbacksNV */
        { 2137,  382 }, /* glGenTransformFeedbacksNV and glGenTransformFeedbacks */
        {  284,  752 }, /* glGenVertexArrays and glGenVertexArraysAPPLE */
        {  284, 2736 }, /* glGenVertexArrays and glGenVertexArraysOES */
        {  752,  284 }, /* glGenVertexArraysAPPLE and glGenVertexArrays */
        {  752, 2736 }, /* glGenVertexArraysAPPLE and glGenVertexArraysOES */
        { 2736,  284 }, /* glGenVertexArraysOES and glGenVertexArrays */
        { 2736,  752 }, /* glGenVertexArraysOES and glGenVertexArraysAPPLE */
        {  118, 1047 }, /* glGetActiveAttrib and glGetActiveAttribARB */
        { 1047,  118 }, /* glGetActiveAttribARB and glGetActiveAttrib */
        {  119,  956 }, /* glGetActiveUniform and glGetActiveUniformARB */
        {  956,  119 }, /* glGetActiveUniformARB and glGetActiveUniform */
        {  121, 1048 }, /* glGetAttribLocation and glGetAttribLocationARB */
        { 1048,  121 }, /* glGetAttribLocationARB and glGetAttribLocation */
        {  203, 1300 }, /* glGetBooleani_v and glGetBooleanIndexedvEXT */
        { 1300,  203 }, /* glGetBooleanIndexedvEXT and glGetBooleani_v */
        {  101, 1001 }, /* glGetBufferParameteriv and glGetBufferParameterivARB */
        { 1001,  101 }, /* glGetBufferParameterivARB and glGetBufferParameteriv */
        {  102, 1002 }, /* glGetBufferPointerv and glGetBufferPointervARB */
        {  102, 2712 }, /* glGetBufferPointerv and glGetBufferPointervOES */
        { 1002,  102 }, /* glGetBufferPointervARB and glGetBufferPointerv */
        { 1002, 2712 }, /* glGetBufferPointervARB and glGetBufferPointervOES */
        { 2712,  102 }, /* glGetBufferPointervOES and glGetBufferPointerv */
        { 2712, 1002 }, /* glGetBufferPointervOES and glGetBufferPointervARB */
        {   98,  998 }, /* glGetBufferSubData and glGetBufferSubDataARB */
        {  998,   98 }, /* glGetBufferSubDataARB and glGetBufferSubData */
        {   74, 2867 }, /* glGetCompressedTexImage and glGetCompressedTexImageANGLE */
        {   74,  977 }, /* glGetCompressedTexImage and glGetCompressedTexImageARB */
        { 2867,   74 }, /* glGetCompressedTexImageANGLE and glGetCompressedTexImage */
        { 2867,  977 }, /* glGetCompressedTexImageANGLE and glGetCompressedTexImageARB */
        {  977,   74 }, /* glGetCompressedTexImageARB and glGetCompressedTexImage */
        {  977, 2867 }, /* glGetCompressedTexImageARB and glGetCompressedTexImageANGLE */
        {  527,  787 }, /* glGetDebugMessageLog and glGetDebugMessageLogARB */
        {  527, 2651 }, /* glGetDebugMessageLog and glGetDebugMessageLogKHR */
        {  787,  527 }, /* glGetDebugMessageLogARB and glGetDebugMessageLog */
        {  787, 2651 }, /* glGetDebugMessageLogARB and glGetDebugMessageLogKHR */
        { 2651,  527 }, /* glGetDebugMessageLogKHR and glGetDebugMessageLog */
        { 2651,  787 }, /* glGetDebugMessageLogKHR and glGetDebugMessageLogARB */
        {  478, 1294 }, /* glGetDoublei_v and glGetDoubleIndexedvEXT */
        {  478, 1381 }, /* glGetDoublei_v and glGetDoublei_vEXT */
        { 1381, 1294 }, /* glGetDoublei_vEXT and glGetDoubleIndexedvEXT */
        { 1381,  478 }, /* glGetDoublei_vEXT and glGetDoublei_v */
        { 1294,  478 }, /* glGetDoubleIndexedvEXT and glGetDoublei_v */
        { 1294, 1381 }, /* glGetDoubleIndexedvEXT and glGetDoublei_vEXT */
        {  477, 1293 }, /* glGetFloati_v and glGetFloatIndexedvEXT */
        {  477, 1380 }, /* glGetFloati_v and glGetFloati_vEXT */
        {  477, 2689 }, /* glGetFloati_v and glGetFloati_vNV */
        {  477, 2746 }, /* glGetFloati_v and glGetFloati_vOES */
        { 1380, 1293 }, /* glGetFloati_vEXT and glGetFloatIndexedvEXT */
        { 1380,  477 }, /* glGetFloati_vEXT and glGetFloati_v */
        { 1380, 2689 }, /* glGetFloati_vEXT and glGetFloati_vNV */
        { 1380, 2746 }, /* glGetFloati_vEXT and glGetFloati_vOES */
        { 2689, 1293 }, /* glGetFloati_vNV and glGetFloatIndexedvEXT */
        { 2689,  477 }, /* glGetFloati_vNV and glGetFloati_v */
        { 2689, 1380 }, /* glGetFloati_vNV and glGetFloati_vEXT */
        { 2689, 2746 }, /* glGetFloati_vNV and glGetFloati_vOES */
        { 2746, 1293 }, /* glGetFloati_vOES and glGetFloatIndexedvEXT */
        { 2746,  477 }, /* glGetFloati_vOES and glGetFloati_v */
        { 2746, 1380 }, /* glGetFloati_vOES and glGetFloati_vEXT */
        { 2746, 2689 }, /* glGetFloati_vOES and glGetFloati_vNV */
        { 1293,  477 }, /* glGetFloatIndexedvEXT and glGetFloati_v */
        { 1293, 1380 }, /* glGetFloatIndexedvEXT and glGetFloati_vEXT */
        { 1293, 2689 }, /* glGetFloatIndexedvEXT and glGetFloati_vNV */
        { 1293, 2746 }, /* glGetFloatIndexedvEXT and glGetFloati_vOES */
        {  318, 2565 }, /* glGetFragDataIndex and glGetFragDataIndexEXT */
        { 2565,  318 }, /* glGetFragDataIndexEXT and glGetFragDataIndex */
        {  242, 1511 }, /* glGetFragDataLocation and glGetFragDataLocationEXT */
        { 1511,  242 }, /* glGetFragDataLocationEXT and glGetFragDataLocation */
        {  275, 1504 }, /* glGetFramebufferAttachmentParameteriv and glGetFramebufferAttachmentParameterivEXT */
        { 1504,  275 }, /* glGetFramebufferAttachmentParameterivEXT and glGetFramebufferAttachmentParameteriv */
        {  644, 2611 }, /* glGetGraphicsResetStatus and glGetGraphicsResetStatusEXT */
        {  644, 2659 }, /* glGetGraphicsResetStatus and glGetGraphicsResetStatusKHR */
        { 2611,  644 }, /* glGetGraphicsResetStatusEXT and glGetGraphicsResetStatus */
        { 2611, 2659 }, /* glGetGraphicsResetStatusEXT and glGetGraphicsResetStatusKHR */
        { 2659,  644 }, /* glGetGraphicsResetStatusKHR and glGetGraphicsResetStatus */
        { 2659, 2611 }, /* glGetGraphicsResetStatusKHR and glGetGraphicsResetStatusEXT */
        {  308, 2557 }, /* glGetInteger64v and glGetInteger64vAPPLE */
        {  308, 2581 }, /* glGetInteger64v and glGetInteger64vEXT */
        { 2557,  308 }, /* glGetInteger64vAPPLE and glGetInteger64v */
        { 2557, 2581 }, /* glGetInteger64vAPPLE and glGetInteger64vEXT */
        { 2581,  308 }, /* glGetInteger64vEXT and glGetInteger64v */
        { 2581, 2557 }, /* glGetInteger64vEXT and glGetInteger64vAPPLE */
        {  204, 1299 }, /* glGetIntegeri_v and glGetIntegerIndexedvEXT */
        { 1299,  204 }, /* glGetIntegerIndexedvEXT and glGetIntegeri_v */
        {  315, 2853 }, /* glGetMultisamplefv and glGetMultisamplefvANGLE */
        {  315, 1869 }, /* glGetMultisamplefv and glGetMultisamplefvNV */
        { 2853,  315 }, /* glGetMultisamplefvANGLE and glGetMultisamplefv */
        { 2853, 1869 }, /* glGetMultisamplefvANGLE and glGetMultisamplefvNV */
        { 1869,  315 }, /* glGetMultisamplefvNV and glGetMultisamplefv */
        { 1869, 2853 }, /* glGetMultisamplefvNV and glGetMultisamplefvANGLE */
        {  648, 2613 }, /* glGetnUniformfv and glGetnUniformfvEXT */
        {  648, 2661 }, /* glGetnUniformfv and glGetnUniformfvKHR */
        { 2613,  648 }, /* glGetnUniformfvEXT and glGetnUniformfv */
        { 2613, 2661 }, /* glGetnUniformfvEXT and glGetnUniformfvKHR */
        { 2661,  648 }, /* glGetnUniformfvKHR and glGetnUniformfv */
        { 2661, 2613 }, /* glGetnUniformfvKHR and glGetnUniformfvEXT */
        {  649, 2614 }, /* glGetnUniformiv and glGetnUniformivEXT */
        {  649, 2662 }, /* glGetnUniformiv and glGetnUniformivKHR */
        { 2614,  649 }, /* glGetnUniformivEXT and glGetnUniformiv */
        { 2614, 2662 }, /* glGetnUniformivEXT and glGetnUniformivKHR */
        { 2662,  649 }, /* glGetnUniformivKHR and glGetnUniformiv */
        { 2662, 2614 }, /* glGetnUniformivKHR and glGetnUniformivEXT */
        {  650, 2663 }, /* glGetnUniformuiv and glGetnUniformuivKHR */
        { 2663,  650 }, /* glGetnUniformuivKHR and glGetnUniformuiv */
        {  531, 2655 }, /* glGetObjectLabel and glGetObjectLabelKHR */
        { 2655,  531 }, /* glGetObjectLabelKHR and glGetObjectLabel */
        {  533, 2657 }, /* glGetObjectPtrLabel and glGetObjectPtrLabelKHR */
        { 2657,  533 }, /* glGetObjectPtrLabelKHR and glGetObjectPtrLabel */
        {   50, 2885 }, /* glGetPointerv and glGetPointervANGLE */
        {   50, 1671 }, /* glGetPointerv and glGetPointervEXT */
        {   50, 2658 }, /* glGetPointerv and glGetPointervKHR */
        { 2885,   50 }, /* glGetPointervANGLE and glGetPointerv */
        { 2885, 1671 }, /* glGetPointervANGLE and glGetPointervEXT */
        { 2885, 2658 }, /* glGetPointervANGLE and glGetPointervKHR */
        { 1671,   50 }, /* glGetPointervEXT and glGetPointerv */
        { 1671, 2885 }, /* glGetPointervEXT and glGetPointervANGLE */
        { 1671, 2658 }, /* glGetPointervEXT and glGetPointervKHR */
        { 2658,   50 }, /* glGetPointervKHR and glGetPointerv */
        { 2658, 2885 }, /* glGetPointervKHR and glGetPointervANGLE */
        { 2658, 1671 }, /* glGetPointervKHR and glGetPointervEXT */
        {  396, 2708 }, /* glGetProgramBinary and glGetProgramBinaryOES */
        { 2708,  396 }, /* glGetProgramBinaryOES and glGetProgramBinary */
        {   89,  903 }, /* glGetQueryiv and glGetQueryivARB */
        {  903,   89 }, /* glGetQueryivARB and glGetQueryiv */
        {  334, 1472 }, /* glGetQueryObjecti64v and glGetQueryObjecti64vEXT */
        { 1472,  334 }, /* glGetQueryObjecti64vEXT and glGetQueryObjecti64v */
        {   90,  904 }, /* glGetQueryObjectiv and glGetQueryObjectivARB */
        {   90, 2579 }, /* glGetQueryObjectiv and glGetQueryObjectivEXT */
        {  904,   90 }, /* glGetQueryObjectivARB and glGetQueryObjectiv */
        {  904, 2579 }, /* glGetQueryObjectivARB and glGetQueryObjectivEXT */
        { 2579,   90 }, /* glGetQueryObjectivEXT and glGetQueryObjectiv */
        { 2579,  904 }, /* glGetQueryObjectivEXT and glGetQueryObjectivARB */
        {  335, 1473 }, /* glGetQueryObjectui64v and glGetQueryObjectui64vEXT */
        { 1473,  335 }, /* glGetQueryObjectui64vEXT and glGetQueryObjectui64v */
        {   91,  905 }, /* glGetQueryObjectuiv and glGetQueryObjectuivARB */
        {  905,   91 }, /* glGetQueryObjectuivARB and glGetQueryObjectuiv */
        {  265, 1494 }, /* glGetRenderbufferParameteriv and glGetRenderbufferParameterivEXT */
        { 1494,  265 }, /* glGetRenderbufferParameterivEXT and glGetRenderbufferParameteriv */
        {  330, 2632 }, /* glGetSamplerParameterIiv and glGetSamplerParameterIivEXT */
        {  330, 2728 }, /* glGetSamplerParameterIiv and glGetSamplerParameterIivOES */
        { 2632,  330 }, /* glGetSamplerParameterIivEXT and glGetSamplerParameterIiv */
        { 2632, 2728 }, /* glGetSamplerParameterIivEXT and glGetSamplerParameterIivOES */
        { 2728,  330 }, /* glGetSamplerParameterIivOES and glGetSamplerParameterIiv */
        { 2728, 2632 }, /* glGetSamplerParameterIivOES and glGetSamplerParameterIivEXT */
        {  332, 2633 }, /* glGetSamplerParameterIuiv and glGetSamplerParameterIuivEXT */
        {  332, 2729 }, /* glGetSamplerParameterIuiv and glGetSamplerParameterIuivOES */
        { 2633,  332 }, /* glGetSamplerParameterIuivEXT and glGetSamplerParameterIuiv */
        { 2633, 2729 }, /* glGetSamplerParameterIuivEXT and glGetSamplerParameterIuivOES */
        { 2729,  332 }, /* glGetSamplerParameterIuivOES and glGetSamplerParameterIuiv */
        { 2729, 2633 }, /* glGetSamplerParameterIuivOES and glGetSamplerParameterIuivEXT */
        {  126,  959 }, /* glGetShaderSource and glGetShaderSourceARB */
        {  959,  126 }, /* glGetShaderSourceARB and glGetShaderSource */
        {  309, 2558 }, /* glGetSynciv and glGetSyncivAPPLE */
        { 2558,  309 }, /* glGetSyncivAPPLE and glGetSynciv */
        {   40, 2866 }, /* glGetTexImage and glGetTexImageANGLE */
        { 2866,   40 }, /* glGetTexImageANGLE and glGetTexImage */
        {   43, 2869 }, /* glGetTexLevelParameterfv and glGetTexLevelParameterfvANGLE */
        { 2869,   43 }, /* glGetTexLevelParameterfvANGLE and glGetTexLevelParameterfv */
        {   44, 2870 }, /* glGetTexLevelParameteriv and glGetTexLevelParameterivANGLE */
        { 2870,   44 }, /* glGetTexLevelParameterivANGLE and glGetTexLevelParameteriv */
        {  253, 1642 }, /* glGetTexParameterIiv and glGetTexParameterIivEXT */
        {  253, 2724 }, /* glGetTexParameterIiv and glGetTexParameterIivOES */
        { 1642,  253 }, /* glGetTexParameterIivEXT and glGetTexParameterIiv */
        { 1642, 2724 }, /* glGetTexParameterIivEXT and glGetTexParameterIivOES */
        { 2724,  253 }, /* glGetTexParameterIivOES and glGetTexParameterIiv */
        { 2724, 1642 }, /* glGetTexParameterIivOES and glGetTexParameterIivEXT */
        {  254, 1643 }, /* glGetTexParameterIuiv and glGetTexParameterIuivEXT */
        {  254, 2725 }, /* glGetTexParameterIuiv and glGetTexParameterIuivOES */
        { 1643,  254 }, /* glGetTexParameterIuivEXT and glGetTexParameterIuiv */
        { 1643, 2725 }, /* glGetTexParameterIuivEXT and glGetTexParameterIuivOES */
        { 2725,  254 }, /* glGetTexParameterIuivOES and glGetTexParameterIuiv */
        { 2725, 1643 }, /* glGetTexParameterIuivOES and glGetTexParameterIuivEXT */
        {  765, 2638 }, /* glGetTextureHandleARB and glGetTextureHandleIMG */
        { 2638,  765 }, /* glGetTextureHandleIMG and glGetTextureHandleARB */
        {  766, 2639 }, /* glGetTextureSamplerHandleARB and glGetTextureSamplerHandleIMG */
        { 2639,  766 }, /* glGetTextureSamplerHandleIMG and glGetTextureSamplerHandleARB */
        {  213, 1666 }, /* glGetTransformFeedbackVarying and glGetTransformFeedbackVaryingEXT */
        { 1666,  213 }, /* glGetTransformFeedbackVaryingEXT and glGetTransformFeedbackVarying */
        {  128,  957 }, /* glGetUniformfv and glGetUniformfvARB */
        {  957,  128 }, /* glGetUniformfvARB and glGetUniformfv */
        {  129,  958 }, /* glGetUniformiv and glGetUniformivARB */
        {  958,  129 }, /* glGetUniformivARB and glGetUniformiv */
        {  127,  955 }, /* glGetUniformLocation and glGetUniformLocationARB */
        {  955,  127 }, /* glGetUniformLocationARB and glGetUniformLocation */
        {  240, 1510 }, /* glGetUniformuiv and glGetUniformuivEXT */
        { 1510,  240 }, /* glGetUniformuivEXT and glGetUniformuiv */
        {  130, 1042 }, /* glGetVertexAttribdv and glGetVertexAttribdvARB */
        {  130, 2196 }, /* glGetVertexAttribdv and glGetVertexAttribdvNV */
        { 1042,  130 }, /* glGetVertexAttribdvARB and glGetVertexAttribdv */
        { 1042, 2196 }, /* glGetVertexAttribdvARB and glGetVertexAttribdvNV */
        { 2196,  130 }, /* glGetVertexAttribdvNV and glGetVertexAttribdv */
        { 2196, 1042 }, /* glGetVertexAttribdvNV and glGetVertexAttribdvARB */
        {  131, 1043 }, /* glGetVertexAttribfv and glGetVertexAttribfvARB */
        {  131, 2197 }, /* glGetVertexAttribfv and glGetVertexAttribfvNV */
        { 1043,  131 }, /* glGetVertexAttribfvARB and glGetVertexAttribfv */
        { 1043, 2197 }, /* glGetVertexAttribfvARB and glGetVertexAttribfvNV */
        { 2197,  131 }, /* glGetVertexAttribfvNV and glGetVertexAttribfv */
        { 2197, 1043 }, /* glGetVertexAttribfvNV and glGetVertexAttribfvARB */
        {  218, 1541 }, /* glGetVertexAttribIiv and glGetVertexAttribIivEXT */
        { 1541,  218 }, /* glGetVertexAttribIivEXT and glGetVertexAttribIiv */
        {  219, 1542 }, /* glGetVertexAttribIuiv and glGetVertexAttribIuivEXT */
        { 1542,  219 }, /* glGetVertexAttribIuivEXT and glGetVertexAttribIuiv */
        {  132, 1044 }, /* glGetVertexAttribiv and glGetVertexAttribivARB */
        {  132, 2198 }, /* glGetVertexAttribiv and glGetVertexAttribivNV */
        { 1044,  132 }, /* glGetVertexAttribivARB and glGetVertexAttribiv */
        { 1044, 2198 }, /* glGetVertexAttribivARB and glGetVertexAttribivNV */
        { 2198,  132 }, /* glGetVertexAttribivNV and glGetVertexAttribiv */
        { 2198, 1044 }, /* glGetVertexAttribivNV and glGetVertexAttribivARB */
        {  468, 1685 }, /* glGetVertexAttribLdv and glGetVertexAttribLdvEXT */
        { 1685,  468 }, /* glGetVertexAttribLdvEXT and glGetVertexAttribLdv */
        {  133, 1045 }, /* glGetVertexAttribPointerv and glGetVertexAttribPointervARB */
        {  133, 2199 }, /* glGetVertexAttribPointerv and glGetVertexAttribPointervNV */
        { 1045,  133 }, /* glGetVertexAttribPointervARB and glGetVertexAttribPointerv */
        { 1045, 2199 }, /* glGetVertexAttribPointervARB and glGetVertexAttribPointervNV */
        { 2199,  133 }, /* glGetVertexAttribPointervNV and glGetVertexAttribPointerv */
        { 2199, 1045 }, /* glGetVertexAttribPointervNV and glGetVertexAttribPointervARB */
        {   95,  995 }, /* glIsBuffer and glIsBufferARB */
        {  995,   95 }, /* glIsBufferARB and glIsBuffer */
        {  207, 1298 }, /* glIsEnabledi and glIsEnabledIndexedEXT */
        {  207, 2590 }, /* glIsEnabledi and glIsEnablediEXT */
        {  207, 2692 }, /* glIsEnabledi and glIsEnablediNV */
        {  207, 2703 }, /* glIsEnabledi and glIsEnablediOES */
        { 2590, 1298 }, /* glIsEnablediEXT and glIsEnabledIndexedEXT */
        { 2590,  207 }, /* glIsEnablediEXT and glIsEnabledi */
        { 2590, 2692 }, /* glIsEnablediEXT and glIsEnablediNV */
        { 2590, 2703 }, /* glIsEnablediEXT and glIsEnablediOES */
        { 1298,  207 }, /* glIsEnabledIndexedEXT and glIsEnabledi */
        { 1298, 2590 }, /* glIsEnabledIndexedEXT and glIsEnablediEXT */
        { 1298, 2692 }, /* glIsEnabledIndexedEXT and glIsEnablediNV */
        { 1298, 2703 }, /* glIsEnabledIndexedEXT and glIsEnablediOES */
        { 2692, 1298 }, /* glIsEnablediNV and glIsEnabledIndexedEXT */
        { 2692,  207 }, /* glIsEnablediNV and glIsEnabledi */
        { 2692, 2590 }, /* glIsEnablediNV and glIsEnablediEXT */
        { 2692, 2703 }, /* glIsEnablediNV and glIsEnablediOES */
        { 2703, 1298 }, /* glIsEnablediOES and glIsEnabledIndexedEXT */
        { 2703,  207 }, /* glIsEnablediOES and glIsEnabledi */
        { 2703, 2590 }, /* glIsEnablediOES and glIsEnablediEXT */
        { 2703, 2692 }, /* glIsEnablediOES and glIsEnablediNV */
        {  266, 1495 }, /* glIsFramebuffer and glIsFramebufferEXT */
        { 1495,  266 }, /* glIsFramebufferEXT and glIsFramebuffer */
        {  813, 2200 }, /* glIsProgramARB and glIsProgramNV */
        { 2200,  813 }, /* glIsProgramNV and glIsProgramARB */
        {   86,  900 }, /* glIsQuery and glIsQueryARB */
        {  900,   86 }, /* glIsQueryARB and glIsQuery */
        {  260, 1489 }, /* glIsRenderbuffer and glIsRenderbufferEXT */
        { 1489,  260 }, /* glIsRenderbufferEXT and glIsRenderbuffer */
        {  304, 2553 }, /* glIsSync and glIsSyncAPPLE */
        { 2553,  304 }, /* glIsSyncAPPLE and glIsSync */
        {  383, 2138 }, /* glIsTransformFeedback and glIsTransformFeedbackNV */
        { 2138,  383 }, /* glIsTransformFeedbackNV and glIsTransformFeedback */
        {  285,  753 }, /* glIsVertexArray and glIsVertexArrayAPPLE */
        {  285, 2737 }, /* glIsVertexArray and glIsVertexArrayOES */
        {  753,  285 }, /* glIsVertexArrayAPPLE and glIsVertexArray */
        {  753, 2737 }, /* glIsVertexArrayAPPLE and glIsVertexArrayOES */
        { 2737,  285 }, /* glIsVertexArrayOES and glIsVertexArray */
        { 2737,  753 }, /* glIsVertexArrayOES and glIsVertexArrayAPPLE */
        {  136,  929 }, /* glLinkProgram and glLinkProgramARB */
        {  929,  136 }, /* glLinkProgramARB and glLinkProgram */
        {   26, 2883 }, /* glLogicOp and glLogicOpANGLE */
        { 2883,   26 }, /* glLogicOpANGLE and glLogicOp */
        {   99,  999 }, /* glMapBuffer and glMapBufferARB */
        {   99, 2710 }, /* glMapBuffer and glMapBufferOES */
        {  999,   99 }, /* glMapBufferARB and glMapBuffer */
        {  999, 2710 }, /* glMapBufferARB and glMapBufferOES */
        { 2710,   99 }, /* glMapBufferOES and glMapBuffer */
        { 2710,  999 }, /* glMapBufferOES and glMapBufferARB */
        {  280, 2602 }, /* glMapBufferRange and glMapBufferRangeEXT */
        { 2602,  280 }, /* glMapBufferRangeEXT and glMapBufferRange */
        {  906, 1774 }, /* glMaxShaderCompilerThreadsARB and glMaxShaderCompilerThreadsKHR */
        { 1774,  906 }, /* glMaxShaderCompilerThreadsKHR and glMaxShaderCompilerThreadsARB */
        {  485, 1632 }, /* glMemoryBarrier and glMemoryBarrierEXT */
        { 1632,  485 }, /* glMemoryBarrierEXT and glMemoryBarrier */
        {  345,  920 }, /* glMinSampleShading and glMinSampleShadingARB */
        {  345, 2714 }, /* glMinSampleShading and glMinSampleShadingOES */
        {  920,  345 }, /* glMinSampleShadingARB and glMinSampleShading */
        {  920, 2714 }, /* glMinSampleShadingARB and glMinSampleShadingOES */
        { 2714,  345 }, /* glMinSampleShadingOES and glMinSampleShading */
        { 2714,  920 }, /* glMinSampleShadingOES and glMinSampleShadingARB */
        {   76, 2855 }, /* glMultiDrawArrays and glMultiDrawArraysANGLE */
        {   76, 1580 }, /* glMultiDrawArrays and glMultiDrawArraysEXT */
        { 2855,   76 }, /* glMultiDrawArraysANGLE and glMultiDrawArrays */
        { 2855, 1580 }, /* glMultiDrawArraysANGLE and glMultiDrawArraysEXT */
        { 1580,   76 }, /* glMultiDrawArraysEXT and glMultiDrawArrays */
        { 1580, 2855 }, /* glMultiDrawArraysEXT and glMultiDrawArraysANGLE */
        {  505,  707 }, /* glMultiDrawArraysIndirect and glMultiDrawArraysIndirectAMD */
        {  505, 2604 }, /* glMultiDrawArraysIndirect and glMultiDrawArraysIndirectEXT */
        {  707,  505 }, /* glMultiDrawArraysIndirectAMD and glMultiDrawArraysIndirect */
        {  707, 2604 }, /* glMultiDrawArraysIndirectAMD and glMultiDrawArraysIndirectEXT */
        {  654,  855 }, /* glMultiDrawArraysIndirectCount and glMultiDrawArraysIndirectCountARB */
        {  855,  654 }, /* glMultiDrawArraysIndirectCountARB and glMultiDrawArraysIndirectCount */
        { 2604,  505 }, /* glMultiDrawArraysIndirectEXT and glMultiDrawArraysIndirect */
        { 2604,  707 }, /* glMultiDrawArraysIndirectEXT and glMultiDrawArraysIndirectAMD */
        {   77, 2857 }, /* glMultiDrawElements and glMultiDrawElementsANGLE */
        {   77, 1581 }, /* glMultiDrawElements and glMultiDrawElementsEXT */
        { 2857,   77 }, /* glMultiDrawElementsANGLE and glMultiDrawElements */
        { 2857, 1581 }, /* glMultiDrawElementsANGLE and glMultiDrawElementsEXT */
        {  301, 2594 }, /* glMultiDrawElementsBaseVertex and glMultiDrawElementsBaseVertexEXT */
        { 2594,  301 }, /* glMultiDrawElementsBaseVertexEXT and glMultiDrawElementsBaseVertex */
        { 1581,   77 }, /* glMultiDrawElementsEXT and glMultiDrawElements */
        { 1581, 2857 }, /* glMultiDrawElementsEXT and glMultiDrawElementsANGLE */
        {  506,  708 }, /* glMultiDrawElementsIndirect and glMultiDrawElementsIndirectAMD */
        {  506, 2605 }, /* glMultiDrawElementsIndirect and glMultiDrawElementsIndirectEXT */
        {  708,  506 }, /* glMultiDrawElementsIndirectAMD and glMultiDrawElementsIndirect */
        {  708, 2605 }, /* glMultiDrawElementsIndirectAMD and glMultiDrawElementsIndirectEXT */
        {  655,  856 }, /* glMultiDrawElementsIndirectCount and glMultiDrawElementsIndirectCountARB */
        {  856,  655 }, /* glMultiDrawElementsIndirectCountARB and glMultiDrawElementsIndirectCount */
        { 2605,  506 }, /* glMultiDrawElementsIndirectEXT and glMultiDrawElementsIndirect */
        { 2605,  708 }, /* glMultiDrawElementsIndirectEXT and glMultiDrawElementsIndirectAMD */
        {  551, 1435 }, /* glNamedBufferStorage and glNamedBufferStorageEXT */
        { 1435,  551 }, /* glNamedBufferStorageEXT and glNamedBufferStorage */
        {  553, 1320 }, /* glNamedBufferSubData and glNamedBufferSubDataEXT */
        { 1320,  553 }, /* glNamedBufferSubDataEXT and glNamedBufferSubData */
        {  530, 2654 }, /* glObjectLabel and glObjectLabelKHR */
        { 2654,  530 }, /* glObjectLabelKHR and glObjectLabel */
        {  532, 2656 }, /* glObjectPtrLabel and glObjectPtrLabelKHR */
        { 2656,  532 }, /* glObjectPtrLabelKHR and glObjectPtrLabel */
        {  378, 2629 }, /* glPatchParameteri and glPatchParameteriEXT */
        {  378, 2715 }, /* glPatchParameteri and glPatchParameteriOES */
        { 2629,  378 }, /* glPatchParameteriEXT and glPatchParameteri */
        { 2629, 2715 }, /* glPatchParameteriEXT and glPatchParameteriOES */
        { 2715,  378 }, /* glPatchParameteriOES and glPatchParameteri */
        { 2715, 2629 }, /* glPatchParameteriOES and glPatchParameteriEXT */
        {  384, 2139 }, /* glPauseTransformFeedback and glPauseTransformFeedbackNV */
        { 2139,  384 }, /* glPauseTransformFeedbackNV and glPauseTransformFeedback */
        {   78,  907 }, /* glPointParameterf and glPointParameterfARB */
        {   78, 1594 }, /* glPointParameterf and glPointParameterfEXT */
        {   78, 2410 }, /* glPointParameterf and glPointParameterfSGIS */
        {  907,   78 }, /* glPointParameterfARB and glPointParameterf */
        {  907, 1594 }, /* glPointParameterfARB and glPointParameterfEXT */
        {  907, 2410 }, /* glPointParameterfARB and glPointParameterfSGIS */
        { 1594,   78 }, /* glPointParameterfEXT and glPointParameterf */
        { 1594,  907 }, /* glPointParameterfEXT and glPointParameterfARB */
        { 1594, 2410 }, /* glPointParameterfEXT and glPointParameterfSGIS */
        { 2410,   78 }, /* glPointParameterfSGIS and glPointParameterf */
        { 2410,  907 }, /* glPointParameterfSGIS and glPointParameterfARB */
        { 2410, 1594 }, /* glPointParameterfSGIS and glPointParameterfEXT */
        {   79,  908 }, /* glPointParameterfv and glPointParameterfvARB */
        {   79, 1595 }, /* glPointParameterfv and glPointParameterfvEXT */
        {   79, 2411 }, /* glPointParameterfv and glPointParameterfvSGIS */
        {  908,   79 }, /* glPointParameterfvARB and glPointParameterfv */
        {  908, 1595 }, /* glPointParameterfvARB and glPointParameterfvEXT */
        {  908, 2411 }, /* glPointParameterfvARB and glPointParameterfvSGIS */
        { 1595,   79 }, /* glPointParameterfvEXT and glPointParameterfv */
        { 1595,  908 }, /* glPointParameterfvEXT and glPointParameterfvARB */
        { 1595, 2411 }, /* glPointParameterfvEXT and glPointParameterfvSGIS */
        { 2411,   79 }, /* glPointParameterfvSGIS and glPointParameterfv */
        { 2411,  908 }, /* glPointParameterfvSGIS and glPointParameterfvARB */
        { 2411, 1595 }, /* glPointParameterfvSGIS and glPointParameterfvEXT */
        {   80, 2062 }, /* glPointParameteri and glPointParameteriNV */
        { 2062,   80 }, /* glPointParameteriNV and glPointParameteri */
        {   81, 2063 }, /* glPointParameteriv and glPointParameterivNV */
        { 2063,   81 }, /* glPointParameterivNV and glPointParameteriv */
        {    5, 2679 }, /* glPolygonMode and glPolygonModeNV */
        { 2679,    5 }, /* glPolygonModeNV and glPolygonMode */
        {  656, 1597 }, /* glPolygonOffsetClamp and glPolygonOffsetClampEXT */
        { 1597,  656 }, /* glPolygonOffsetClampEXT and glPolygonOffsetClamp */
        {  529, 2653 }, /* glPopDebugGroup and glPopDebugGroupKHR */
        { 2653,  529 }, /* glPopDebugGroupKHR and glPopDebugGroup */
        { 2542,  764 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxARB */
        { 2542, 2610 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxEXT */
        { 2542, 2713 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxOES */
        {  764, 2542 }, /* glPrimitiveBoundingBoxARB and glPrimitiveBoundingBox */
        {  764, 2610 }, /* glPrimitiveBoundingBoxARB and glPrimitiveBoundingBoxEXT */
        {  764, 2713 }, /* glPrimitiveBoundingBoxARB and glPrimitiveBoundingBoxOES */
        { 2610, 2542 }, /* glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBox */
        { 2610,  764 }, /* glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBoxARB */
        { 2610, 2713 }, /* glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBoxOES */
        { 2713, 2542 }, /* glPrimitiveBoundingBoxOES and glPrimitiveBoundingBox */
        { 2713,  764 }, /* glPrimitiveBoundingBoxOES and glPrimitiveBoundingBoxARB */
        { 2713, 2610 }, /* glPrimitiveBoundingBoxOES and glPrimitiveBoundingBoxEXT */
        {  397, 2709 }, /* glProgramBinary and glProgramBinaryOES */
        { 2709,  397 }, /* glProgramBinaryOES and glProgramBinary */
        {  398,  814 }, /* glProgramParameteri and glProgramParameteriARB */
        {  398, 1507 }, /* glProgramParameteri and glProgramParameteriEXT */
        {  814,  398 }, /* glProgramParameteriARB and glProgramParameteri */
        {  814, 1507 }, /* glProgramParameteriARB and glProgramParameteriEXT */
        { 1507,  398 }, /* glProgramParameteriEXT and glProgramParameteri */
        { 1507,  814 }, /* glProgramParameteriEXT and glProgramParameteriARB */
        {  409, 1326 }, /* glProgramUniform1f and glProgramUniform1fEXT */
        { 1326,  409 }, /* glProgramUniform1fEXT and glProgramUniform1f */
        {  410, 1334 }, /* glProgramUniform1fv and glProgramUniform1fvEXT */
        { 1334,  410 }, /* glProgramUniform1fvEXT and glProgramUniform1fv */
        {  407, 1330 }, /* glProgramUniform1i and glProgramUniform1iEXT */
        { 1330,  407 }, /* glProgramUniform1iEXT and glProgramUniform1i */
        {  408, 1338 }, /* glProgramUniform1iv and glProgramUniform1ivEXT */
        { 1338,  408 }, /* glProgramUniform1ivEXT and glProgramUniform1iv */
        {  413, 1361 }, /* glProgramUniform1ui and glProgramUniform1uiEXT */
        { 1361,  413 }, /* glProgramUniform1uiEXT and glProgramUniform1ui */
        {  414, 1365 }, /* glProgramUniform1uiv and glProgramUniform1uivEXT */
        { 1365,  414 }, /* glProgramUniform1uivEXT and glProgramUniform1uiv */
        {  417, 1327 }, /* glProgramUniform2f and glProgramUniform2fEXT */
        { 1327,  417 }, /* glProgramUniform2fEXT and glProgramUniform2f */
        {  418, 1335 }, /* glProgramUniform2fv and glProgramUniform2fvEXT */
        { 1335,  418 }, /* glProgramUniform2fvEXT and glProgramUniform2fv */
        {  415, 1331 }, /* glProgramUniform2i and glProgramUniform2iEXT */
        { 1331,  415 }, /* glProgramUniform2iEXT and glProgramUniform2i */
        {  416, 1339 }, /* glProgramUniform2iv and glProgramUniform2ivEXT */
        { 1339,  416 }, /* glProgramUniform2ivEXT and glProgramUniform2iv */
        {  421, 1362 }, /* glProgramUniform2ui and glProgramUniform2uiEXT */
        { 1362,  421 }, /* glProgramUniform2uiEXT and glProgramUniform2ui */
        {  422, 1366 }, /* glProgramUniform2uiv and glProgramUniform2uivEXT */
        { 1366,  422 }, /* glProgramUniform2uivEXT and glProgramUniform2uiv */
        {  425, 1328 }, /* glProgramUniform3f and glProgramUniform3fEXT */
        { 1328,  425 }, /* glProgramUniform3fEXT and glProgramUniform3f */
        {  426, 1336 }, /* glProgramUniform3fv and glProgramUniform3fvEXT */
        { 1336,  426 }, /* glProgramUniform3fvEXT and glProgramUniform3fv */
        {  423, 1332 }, /* glProgramUniform3i and glProgramUniform3iEXT */
        { 1332,  423 }, /* glProgramUniform3iEXT and glProgramUniform3i */
        {  424, 1340 }, /* glProgramUniform3iv and glProgramUniform3ivEXT */
        { 1340,  424 }, /* glProgramUniform3ivEXT and glProgramUniform3iv */
        {  429, 1363 }, /* glProgramUniform3ui and glProgramUniform3uiEXT */
        { 1363,  429 }, /* glProgramUniform3uiEXT and glProgramUniform3ui */
        {  430, 1367 }, /* glProgramUniform3uiv and glProgramUniform3uivEXT */
        { 1367,  430 }, /* glProgramUniform3uivEXT and glProgramUniform3uiv */
        {  433, 1329 }, /* glProgramUniform4f and glProgramUniform4fEXT */
        { 1329,  433 }, /* glProgramUniform4fEXT and glProgramUniform4f */
        {  434, 1337 }, /* glProgramUniform4fv and glProgramUniform4fvEXT */
        { 1337,  434 }, /* glProgramUniform4fvEXT and glProgramUniform4fv */
        {  431, 1333 }, /* glProgramUniform4i and glProgramUniform4iEXT */
        { 1333,  431 }, /* glProgramUniform4iEXT and glProgramUniform4i */
        {  432, 1341 }, /* glProgramUniform4iv and glProgramUniform4ivEXT */
        { 1341,  432 }, /* glProgramUniform4ivEXT and glProgramUniform4iv */
        {  437, 1364 }, /* glProgramUniform4ui and glProgramUniform4uiEXT */
        { 1364,  437 }, /* glProgramUniform4uiEXT and glProgramUniform4ui */
        {  438, 1368 }, /* glProgramUniform4uiv and glProgramUniform4uivEXT */
        { 1368,  438 }, /* glProgramUniform4uivEXT and glProgramUniform4uiv */
        {  774, 2642 }, /* glProgramUniformHandleui64ARB and glProgramUniformHandleui64IMG */
        { 2642,  774 }, /* glProgramUniformHandleui64IMG and glProgramUniformHandleui64ARB */
        {  775, 2643 }, /* glProgramUniformHandleui64vARB and glProgramUniformHandleui64vIMG */
        { 2643,  775 }, /* glProgramUniformHandleui64vIMG and glProgramUniformHandleui64vARB */
        {  439, 1342 }, /* glProgramUniformMatrix2fv and glProgramUniformMatrix2fvEXT */
        { 1342,  439 }, /* glProgramUniformMatrix2fvEXT and glProgramUniformMatrix2fv */
        {  445, 1345 }, /* glProgramUniformMatrix2x3fv and glProgramUniformMatrix2x3fvEXT */
        { 1345,  445 }, /* glProgramUniformMatrix2x3fvEXT and glProgramUniformMatrix2x3fv */
        {  447, 1347 }, /* glProgramUniformMatrix2x4fv and glProgramUniformMatrix2x4fvEXT */
        { 1347,  447 }, /* glProgramUniformMatrix2x4fvEXT and glProgramUniformMatrix2x4fv */
        {  440, 1343 }, /* glProgramUniformMatrix3fv and glProgramUniformMatrix3fvEXT */
        { 1343,  440 }, /* glProgramUniformMatrix3fvEXT and glProgramUniformMatrix3fv */
        {  446, 1346 }, /* glProgramUniformMatrix3x2fv and glProgramUniformMatrix3x2fvEXT */
        { 1346,  446 }, /* glProgramUniformMatrix3x2fvEXT and glProgramUniformMatrix3x2fv */
        {  449, 1349 }, /* glProgramUniformMatrix3x4fv and glProgramUniformMatrix3x4fvEXT */
        { 1349,  449 }, /* glProgramUniformMatrix3x4fvEXT and glProgramUniformMatrix3x4fv */
        {  441, 1344 }, /* glProgramUniformMatrix4fv and glProgramUniformMatrix4fvEXT */
        { 1344,  441 }, /* glProgramUniformMatrix4fvEXT and glProgramUniformMatrix4fv */
        {  448, 1348 }, /* glProgramUniformMatrix4x2fv and glProgramUniformMatrix4x2fvEXT */
        { 1348,  448 }, /* glProgramUniformMatrix4x2fvEXT and glProgramUniformMatrix4x2fv */
        {  450, 1350 }, /* glProgramUniformMatrix4x3fv and glProgramUniformMatrix4x3fvEXT */
        { 1350,  450 }, /* glProgramUniformMatrix4x3fvEXT and glProgramUniformMatrix4x3fv */
        {  302, 2864 }, /* glProvokingVertex and glProvokingVertexANGLE */
        {  302, 1598 }, /* glProvokingVertex and glProvokingVertexEXT */
        { 2864,  302 }, /* glProvokingVertexANGLE and glProvokingVertex */
        { 2864, 1598 }, /* glProvokingVertexANGLE and glProvokingVertexEXT */
        { 1598,  302 }, /* glProvokingVertexEXT and glProvokingVertex */
        { 1598, 2864 }, /* glProvokingVertexEXT and glProvokingVertexANGLE */
        {  528, 2652 }, /* glPushDebugGroup and glPushDebugGroupKHR */
        { 2652,  528 }, /* glPushDebugGroupKHR and glPushDebugGroup */
        {  333, 2577 }, /* glQueryCounter and glQueryCounterEXT */
        { 2577,  333 }, /* glQueryCounterEXT and glQueryCounter */
        {  651,  911 }, /* glReadnPixels and glReadnPixelsARB */
        {  651, 2612 }, /* glReadnPixels and glReadnPixelsEXT */
        {  651, 2660 }, /* glReadnPixels and glReadnPixelsKHR */
        {  911,  651 }, /* glReadnPixelsARB and glReadnPixels */
        {  911, 2612 }, /* glReadnPixelsARB and glReadnPixelsEXT */
        {  911, 2660 }, /* glReadnPixelsARB and glReadnPixelsKHR */
        { 2612,  651 }, /* glReadnPixelsEXT and glReadnPixels */
        { 2612,  911 }, /* glReadnPixelsEXT and glReadnPixelsARB */
        { 2612, 2660 }, /* glReadnPixelsEXT and glReadnPixelsKHR */
        { 2660,  651 }, /* glReadnPixelsKHR and glReadnPixels */
        { 2660,  911 }, /* glReadnPixelsKHR and glReadnPixelsARB */
        { 2660, 2612 }, /* glReadnPixelsKHR and glReadnPixelsEXT */
        {  264, 1493 }, /* glRenderbufferStorage and glRenderbufferStorageEXT */
        { 1493,  264 }, /* glRenderbufferStorageEXT and glRenderbufferStorage */
        {  278, 1488 }, /* glRenderbufferStorageMultisample and glRenderbufferStorageMultisampleEXT */
        {  278, 2671 }, /* glRenderbufferStorageMultisample and glRenderbufferStorageMultisampleNV */
        { 1488,  278 }, /* glRenderbufferStorageMultisampleEXT and glRenderbufferStorageMultisample */
        { 1488, 2671 }, /* glRenderbufferStorageMultisampleEXT and glRenderbufferStorageMultisampleNV */
        { 2671,  278 }, /* glRenderbufferStorageMultisampleNV and glRenderbufferStorageMultisample */
        { 2671, 1488 }, /* glRenderbufferStorageMultisampleNV and glRenderbufferStorageMultisampleEXT */
        {  385, 2140 }, /* glResumeTransformFeedback and glResumeTransformFeedbackNV */
        { 2140,  385 }, /* glResumeTransformFeedbackNV and glResumeTransformFeedback */
        {   67,  863 }, /* glSampleCoverage and glSampleCoverageARB */
        {  863,   67 }, /* glSampleCoverageARB and glSampleCoverage */
        { 1582, 2402 }, /* glSampleMaskEXT and glSampleMaskSGIS */
        {  316, 2854 }, /* glSampleMaski and glSampleMaskiANGLE */
        { 2854,  316 }, /* glSampleMaskiANGLE and glSampleMaski */
        { 2402, 1582 }, /* glSampleMaskSGIS and glSampleMaskEXT */
        { 1583, 2403 }, /* glSamplePatternEXT and glSamplePatternSGIS */
        { 2403, 1583 }, /* glSamplePatternSGIS and glSamplePatternEXT */
        {  327, 2630 }, /* glSamplerParameterIiv and glSamplerParameterIivEXT */
        {  327, 2726 }, /* glSamplerParameterIiv and glSamplerParameterIivOES */
        { 2630,  327 }, /* glSamplerParameterIivEXT and glSamplerParameterIiv */
        { 2630, 2726 }, /* glSamplerParameterIivEXT and glSamplerParameterIivOES */
        { 2726,  327 }, /* glSamplerParameterIivOES and glSamplerParameterIiv */
        { 2726, 2630 }, /* glSamplerParameterIivOES and glSamplerParameterIivEXT */
        {  328, 2631 }, /* glSamplerParameterIuiv and glSamplerParameterIuivEXT */
        {  328, 2727 }, /* glSamplerParameterIuiv and glSamplerParameterIuivOES */
        { 2631,  328 }, /* glSamplerParameterIuivEXT and glSamplerParameterIuiv */
        { 2631, 2727 }, /* glSamplerParameterIuivEXT and glSamplerParameterIuivOES */
        { 2727,  328 }, /* glSamplerParameterIuivOES and glSamplerParameterIuiv */
        { 2727, 2631 }, /* glSamplerParameterIuivOES and glSamplerParameterIuivEXT */
        {  472, 2684 }, /* glScissorArrayv and glScissorArrayvNV */
        {  472, 2741 }, /* glScissorArrayv and glScissorArrayvOES */
        { 2684,  472 }, /* glScissorArrayvNV and glScissorArrayv */
        { 2684, 2741 }, /* glScissorArrayvNV and glScissorArrayvOES */
        { 2741,  472 }, /* glScissorArrayvOES and glScissorArrayv */
        { 2741, 2684 }, /* glScissorArrayvOES and glScissorArrayvNV */
        {  473, 2685 }, /* glScissorIndexed and glScissorIndexedNV */
        {  473, 2742 }, /* glScissorIndexed and glScissorIndexedOES */
        { 2685,  473 }, /* glScissorIndexedNV and glScissorIndexed */
        { 2685, 2742 }, /* glScissorIndexedNV and glScissorIndexedOES */
        { 2742,  473 }, /* glScissorIndexedOES and glScissorIndexed */
        { 2742, 2685 }, /* glScissorIndexedOES and glScissorIndexedNV */
        {  474, 2686 }, /* glScissorIndexedv and glScissorIndexedvNV */
        {  474, 2743 }, /* glScissorIndexedv and glScissorIndexedvOES */
        { 2686,  474 }, /* glScissorIndexedvNV and glScissorIndexedv */
        { 2686, 2743 }, /* glScissorIndexedvNV and glScissorIndexedvOES */
        { 2743,  474 }, /* glScissorIndexedvOES and glScissorIndexedv */
        { 2743, 2686 }, /* glScissorIndexedvOES and glScissorIndexedvNV */
        {  137,  925 }, /* glShaderSource and glShaderSourceARB */
        {  925,  137 }, /* glShaderSourceARB and glShaderSource */
        {  653,  818 }, /* glSpecializeShader and glSpecializeShaderARB */
        {  818,  653 }, /* glSpecializeShaderARB and glSpecializeShader */
        {  105, 1093 }, /* glStencilOpSeparate and glStencilOpSeparateATI */
        { 1093,  105 }, /* glStencilOpSeparateATI and glStencilOpSeparate */
        {  288,  970 }, /* glTexBuffer and glTexBufferARB */
        {  288, 1644 }, /* glTexBuffer and glTexBufferEXT */
        {  288, 2730 }, /* glTexBuffer and glTexBufferOES */
        {  970,  288 }, /* glTexBufferARB and glTexBuffer */
        {  970, 1644 }, /* glTexBufferARB and glTexBufferEXT */
        {  970, 2730 }, /* glTexBufferARB and glTexBufferOES */
        { 1644,  288 }, /* glTexBufferEXT and glTexBuffer */
        { 1644,  970 }, /* glTexBufferEXT and glTexBufferARB */
        { 1644, 2730 }, /* glTexBufferEXT and glTexBufferOES */
        { 2730,  288 }, /* glTexBufferOES and glTexBuffer */
        { 2730,  970 }, /* glTexBufferOES and glTexBufferARB */
        { 2730, 1644 }, /* glTexBufferOES and glTexBufferEXT */
        {  514, 2634 }, /* glTexBufferRange and glTexBufferRangeEXT */
        {  514, 2731 }, /* glTexBufferRange and glTexBufferRangeOES */
        { 2634,  514 }, /* glTexBufferRangeEXT and glTexBufferRange */
        { 2634, 2731 }, /* glTexBufferRangeEXT and glTexBufferRangeOES */
        { 2731,  514 }, /* glTexBufferRangeOES and glTexBufferRange */
        { 2731, 2634 }, /* glTexBufferRangeOES and glTexBufferRangeEXT */
        {   63, 1637 }, /* glTexImage3D and glTexImage3DEXT */
        { 1637,   63 }, /* glTexImage3DEXT and glTexImage3D */
        {  969, 2628 }, /* glTexPageCommitmentARB and glTexPageCommitmentEXT */
        { 2628,  969 }, /* glTexPageCommitmentEXT and glTexPageCommitmentARB */
        {  251, 1640 }, /* glTexParameterIiv and glTexParameterIivEXT */
        {  251, 2722 }, /* glTexParameterIiv and glTexParameterIivOES */
        { 1640,  251 }, /* glTexParameterIivEXT and glTexParameterIiv */
        { 1640, 2722 }, /* glTexParameterIivEXT and glTexParameterIivOES */
        { 2722,  251 }, /* glTexParameterIivOES and glTexParameterIiv */
        { 2722, 1640 }, /* glTexParameterIivOES and glTexParameterIivEXT */
        {  252, 1641 }, /* glTexParameterIuiv and glTexParameterIuivEXT */
        {  252, 2723 }, /* glTexParameterIuiv and glTexParameterIuivOES */
        { 1641,  252 }, /* glTexParameterIuivEXT and glTexParameterIuiv */
        { 1641, 2723 }, /* glTexParameterIuivEXT and glTexParameterIuivOES */
        { 2723,  252 }, /* glTexParameterIuivOES and glTexParameterIuiv */
        { 2723, 1641 }, /* glTexParameterIuivOES and glTexParameterIuivEXT */
        {  486, 1654 }, /* glTexStorage1D and glTexStorage1DEXT */
        { 1654,  486 }, /* glTexStorage1DEXT and glTexStorage1D */
        {  487, 1655 }, /* glTexStorage2D and glTexStorage2DEXT */
        { 1655,  487 }, /* glTexStorage2DEXT and glTexStorage2D */
        {  515, 2852 }, /* glTexStorage2DMultisample and glTexStorage2DMultisampleANGLE */
        { 2852,  515 }, /* glTexStorage2DMultisampleANGLE and glTexStorage2DMultisample */
        {  488, 1656 }, /* glTexStorage3D and glTexStorage3DEXT */
        { 1656,  488 }, /* glTexStorage3DEXT and glTexStorage3D */
        {  516, 2732 }, /* glTexStorage3DMultisample and glTexStorage3DMultisampleOES */
        { 2732,  516 }, /* glTexStorage3DMultisampleOES and glTexStorage3DMultisample */
        {   56, 1635 }, /* glTexSubImage1D and glTexSubImage1DEXT */
        { 1635,   56 }, /* glTexSubImage1DEXT and glTexSubImage1D */
        {   57, 1636 }, /* glTexSubImage2D and glTexSubImage2DEXT */
        { 1636,   57 }, /* glTexSubImage2DEXT and glTexSubImage2D */
        {   64, 1638 }, /* glTexSubImage3D and glTexSubImage3DEXT */
        { 1638,   64 }, /* glTexSubImage3DEXT and glTexSubImage3D */
        {  517, 2637 }, /* glTextureView and glTextureViewEXT */
        {  517, 2733 }, /* glTextureView and glTextureViewOES */
        { 2637,  517 }, /* glTextureViewEXT and glTextureView */
        { 2637, 2733 }, /* glTextureViewEXT and glTextureViewOES */
        { 2733,  517 }, /* glTextureViewOES and glTextureView */
        { 2733, 2637 }, /* glTextureViewOES and glTextureViewEXT */
        {  212, 1665 }, /* glTransformFeedbackVaryings and glTransformFeedbackVaryingsEXT */
        { 1665,  212 }, /* glTransformFeedbackVaryingsEXT and glTransformFeedbackVaryings */
        {  139,  932 }, /* glUniform1f and glUniform1fARB */
        {  932,  139 }, /* glUniform1fARB and glUniform1f */
        {  147,  940 }, /* glUniform1fv and glUniform1fvARB */
        {  940,  147 }, /* glUniform1fvARB and glUniform1fv */
        {  143,  936 }, /* glUniform1i and glUniform1iARB */
        {  936,  143 }, /* glUniform1iARB and glUniform1i */
        {  151,  944 }, /* glUniform1iv and glUniform1ivARB */
        {  944,  151 }, /* glUniform1ivARB and glUniform1iv */
        {  243, 1512 }, /* glUniform1ui and glUniform1uiEXT */
        { 1512,  243 }, /* glUniform1uiEXT and glUniform1ui */
        {  247, 1516 }, /* glUniform1uiv and glUniform1uivEXT */
        { 1516,  247 }, /* glUniform1uivEXT and glUniform1uiv */
        {  140,  933 }, /* glUniform2f and glUniform2fARB */
        {  933,  140 }, /* glUniform2fARB and glUniform2f */
        {  148,  941 }, /* glUniform2fv and glUniform2fvARB */
        {  941,  148 }, /* glUniform2fvARB and glUniform2fv */
        {  144,  937 }, /* glUniform2i and glUniform2iARB */
        {  937,  144 }, /* glUniform2iARB and glUniform2i */
        {  152,  945 }, /* glUniform2iv and glUniform2ivARB */
        {  945,  152 }, /* glUniform2ivARB and glUniform2iv */
        {  244, 1513 }, /* glUniform2ui and glUniform2uiEXT */
        { 1513,  244 }, /* glUniform2uiEXT and glUniform2ui */
        {  248, 1517 }, /* glUniform2uiv and glUniform2uivEXT */
        { 1517,  248 }, /* glUniform2uivEXT and glUniform2uiv */
        {  141,  934 }, /* glUniform3f and glUniform3fARB */
        {  934,  141 }, /* glUniform3fARB and glUniform3f */
        {  149,  942 }, /* glUniform3fv and glUniform3fvARB */
        {  942,  149 }, /* glUniform3fvARB and glUniform3fv */
        {  145,  938 }, /* glUniform3i and glUniform3iARB */
        {  938,  145 }, /* glUniform3iARB and glUniform3i */
        {  153,  946 }, /* glUniform3iv and glUniform3ivARB */
        {  946,  153 }, /* glUniform3ivARB and glUniform3iv */
        {  245, 1514 }, /* glUniform3ui and glUniform3uiEXT */
        { 1514,  245 }, /* glUniform3uiEXT and glUniform3ui */
        {  249, 1518 }, /* glUniform3uiv and glUniform3uivEXT */
        { 1518,  249 }, /* glUniform3uivEXT and glUniform3uiv */
        {  142,  935 }, /* glUniform4f and glUniform4fARB */
        {  935,  142 }, /* glUniform4fARB and glUniform4f */
        {  150,  943 }, /* glUniform4fv and glUniform4fvARB */
        {  943,  150 }, /* glUniform4fvARB and glUniform4fv */
        {  146,  939 }, /* glUniform4i and glUniform4iARB */
        {  939,  146 }, /* glUniform4iARB and glUniform4i */
        {  154,  947 }, /* glUniform4iv and glUniform4ivARB */
        {  947,  154 }, /* glUniform4ivARB and glUniform4iv */
        {  246, 1515 }, /* glUniform4ui and glUniform4uiEXT */
        { 1515,  246 }, /* glUniform4uiEXT and glUniform4ui */
        {  250, 1519 }, /* glUniform4uiv and glUniform4uivEXT */
        { 1519,  250 }, /* glUniform4uivEXT and glUniform4uiv */
        {  772, 2640 }, /* glUniformHandleui64ARB and glUniformHandleui64IMG */
        { 2640,  772 }, /* glUniformHandleui64IMG and glUniformHandleui64ARB */
        {  773, 2641 }, /* glUniformHandleui64vARB and glUniformHandleui64vIMG */
        { 2641,  773 }, /* glUniformHandleui64vIMG and glUniformHandleui64vARB */
        {  155,  948 }, /* glUniformMatrix2fv and glUniformMatrix2fvARB */
        {  948,  155 }, /* glUniformMatrix2fvARB and glUniformMatrix2fv */
        {  196, 2673 }, /* glUniformMatrix2x3fv and glUniformMatrix2x3fvNV */
        { 2673,  196 }, /* glUniformMatrix2x3fvNV and glUniformMatrix2x3fv */
        {  198, 2675 }, /* glUniformMatrix2x4fv and glUniformMatrix2x4fvNV */
        { 2675,  198 }, /* glUniformMatrix2x4fvNV and glUniformMatrix2x4fv */
        {  156,  949 }, /* glUniformMatrix3fv and glUniformMatrix3fvARB */
        {  949,  156 }, /* glUniformMatrix3fvARB and glUniformMatrix3fv */
        {  197, 2674 }, /* glUniformMatrix3x2fv and glUniformMatrix3x2fvNV */
        { 2674,  197 }, /* glUniformMatrix3x2fvNV and glUniformMatrix3x2fv */
        {  200, 2677 }, /* glUniformMatrix3x4fv and glUniformMatrix3x4fvNV */
        { 2677,  200 }, /* glUniformMatrix3x4fvNV and glUniformMatrix3x4fv */
        {  157,  950 }, /* glUniformMatrix4fv and glUniformMatrix4fvARB */
        {  950,  157 }, /* glUniformMatrix4fvARB and glUniformMatrix4fv */
        {  199, 2676 }, /* glUniformMatrix4x2fv and glUniformMatrix4x2fvNV */
        { 2676,  199 }, /* glUniformMatrix4x2fvNV and glUniformMatrix4x2fv */
        {  201, 2678 }, /* glUniformMatrix4x3fv and glUniformMatrix4x3fvNV */
        { 2678,  201 }, /* glUniformMatrix4x3fvNV and glUniformMatrix4x3fv */
        {  100, 1000 }, /* glUnmapBuffer and glUnmapBufferARB */
        {  100, 2711 }, /* glUnmapBuffer and glUnmapBufferOES */
        { 1000,  100 }, /* glUnmapBufferARB and glUnmapBuffer */
        { 1000, 2711 }, /* glUnmapBufferARB and glUnmapBufferOES */
        { 2711,  100 }, /* glUnmapBufferOES and glUnmapBuffer */
        { 2711, 1000 }, /* glUnmapBufferOES and glUnmapBufferARB */
        {  138,  930 }, /* glUseProgram and glUseProgramObjectARB */
        {  930,  138 }, /* glUseProgramObjectARB and glUseProgram */
        {  158,  931 }, /* glValidateProgram and glValidateProgramARB */
        {  931,  158 }, /* glValidateProgramARB and glValidateProgram */
        {  159, 1003 }, /* glVertexAttrib1d and glVertexAttrib1dARB */
        {  159, 2211 }, /* glVertexAttrib1d and glVertexAttrib1dNV */
        { 1003,  159 }, /* glVertexAttrib1dARB and glVertexAttrib1d */
        { 1003, 2211 }, /* glVertexAttrib1dARB and glVertexAttrib1dNV */
        { 2211,  159 }, /* glVertexAttrib1dNV and glVertexAttrib1d */
        { 2211, 1003 }, /* glVertexAttrib1dNV and glVertexAttrib1dARB */
        {  160, 1004 }, /* glVertexAttrib1dv and glVertexAttrib1dvARB */
        {  160, 2212 }, /* glVertexAttrib1dv and glVertexAttrib1dvNV */
        { 1004,  160 }, /* glVertexAttrib1dvARB and glVertexAttrib1dv */
        { 1004, 2212 }, /* glVertexAttrib1dvARB and glVertexAttrib1dvNV */
        { 2212,  160 }, /* glVertexAttrib1dvNV and glVertexAttrib1dv */
        { 2212, 1004 }, /* glVertexAttrib1dvNV and glVertexAttrib1dvARB */
        {  161, 1005 }, /* glVertexAttrib1f and glVertexAttrib1fARB */
        {  161, 2213 }, /* glVertexAttrib1f and glVertexAttrib1fNV */
        { 1005,  161 }, /* glVertexAttrib1fARB and glVertexAttrib1f */
        { 1005, 2213 }, /* glVertexAttrib1fARB and glVertexAttrib1fNV */
        { 2213,  161 }, /* glVertexAttrib1fNV and glVertexAttrib1f */
        { 2213, 1005 }, /* glVertexAttrib1fNV and glVertexAttrib1fARB */
        {  162, 1006 }, /* glVertexAttrib1fv and glVertexAttrib1fvARB */
        {  162, 2214 }, /* glVertexAttrib1fv and glVertexAttrib1fvNV */
        { 1006,  162 }, /* glVertexAttrib1fvARB and glVertexAttrib1fv */
        { 1006, 2214 }, /* glVertexAttrib1fvARB and glVertexAttrib1fvNV */
        { 2214,  162 }, /* glVertexAttrib1fvNV and glVertexAttrib1fv */
        { 2214, 1006 }, /* glVertexAttrib1fvNV and glVertexAttrib1fvARB */
        {  163, 1007 }, /* glVertexAttrib1s and glVertexAttrib1sARB */
        {  163, 2215 }, /* glVertexAttrib1s and glVertexAttrib1sNV */
        { 1007,  163 }, /* glVertexAttrib1sARB and glVertexAttrib1s */
        { 1007, 2215 }, /* glVertexAttrib1sARB and glVertexAttrib1sNV */
        { 2215,  163 }, /* glVertexAttrib1sNV and glVertexAttrib1s */
        { 2215, 1007 }, /* glVertexAttrib1sNV and glVertexAttrib1sARB */
        {  164, 1008 }, /* glVertexAttrib1sv and glVertexAttrib1svARB */
        {  164, 2216 }, /* glVertexAttrib1sv and glVertexAttrib1svNV */
        { 1008,  164 }, /* glVertexAttrib1svARB and glVertexAttrib1sv */
        { 1008, 2216 }, /* glVertexAttrib1svARB and glVertexAttrib1svNV */
        { 2216,  164 }, /* glVertexAttrib1svNV and glVertexAttrib1sv */
        { 2216, 1008 }, /* glVertexAttrib1svNV and glVertexAttrib1svARB */
        {  165, 1009 }, /* glVertexAttrib2d and glVertexAttrib2dARB */
        {  165, 2217 }, /* glVertexAttrib2d and glVertexAttrib2dNV */
        { 1009,  165 }, /* glVertexAttrib2dARB and glVertexAttrib2d */
        { 1009, 2217 }, /* glVertexAttrib2dARB and glVertexAttrib2dNV */
        { 2217,  165 }, /* glVertexAttrib2dNV and glVertexAttrib2d */
        { 2217, 1009 }, /* glVertexAttrib2dNV and glVertexAttrib2dARB */
        {  166, 1010 }, /* glVertexAttrib2dv and glVertexAttrib2dvARB */
        {  166, 2218 }, /* glVertexAttrib2dv and glVertexAttrib2dvNV */
        { 1010,  166 }, /* glVertexAttrib2dvARB and glVertexAttrib2dv */
        { 1010, 2218 }, /* glVertexAttrib2dvARB and glVertexAttrib2dvNV */
        { 2218,  166 }, /* glVertexAttrib2dvNV and glVertexAttrib2dv */
        { 2218, 1010 }, /* glVertexAttrib2dvNV and glVertexAttrib2dvARB */
        {  167, 1011 }, /* glVertexAttrib2f and glVertexAttrib2fARB */
        {  167, 2219 }, /* glVertexAttrib2f and glVertexAttrib2fNV */
        { 1011,  167 }, /* glVertexAttrib2fARB and glVertexAttrib2f */
        { 1011, 2219 }, /* glVertexAttrib2fARB and glVertexAttrib2fNV */
        { 2219,  167 }, /* glVertexAttrib2fNV and glVertexAttrib2f */
        { 2219, 1011 }, /* glVertexAttrib2fNV and glVertexAttrib2fARB */
        {  168, 1012 }, /* glVertexAttrib2fv and glVertexAttrib2fvARB */
        {  168, 2220 }, /* glVertexAttrib2fv and glVertexAttrib2fvNV */
        { 1012,  168 }, /* glVertexAttrib2fvARB and glVertexAttrib2fv */
        { 1012, 2220 }, /* glVertexAttrib2fvARB and glVertexAttrib2fvNV */
        { 2220,  168 }, /* glVertexAttrib2fvNV and glVertexAttrib2fv */
        { 2220, 1012 }, /* glVertexAttrib2fvNV and glVertexAttrib2fvARB */
        {  169, 1013 }, /* glVertexAttrib2s and glVertexAttrib2sARB */
        {  169, 2221 }, /* glVertexAttrib2s and glVertexAttrib2sNV */
        { 1013,  169 }, /* glVertexAttrib2sARB and glVertexAttrib2s */
        { 1013, 2221 }, /* glVertexAttrib2sARB and glVertexAttrib2sNV */
        { 2221,  169 }, /* glVertexAttrib2sNV and glVertexAttrib2s */
        { 2221, 1013 }, /* glVertexAttrib2sNV and glVertexAttrib2sARB */
        {  170, 1014 }, /* glVertexAttrib2sv and glVertexAttrib2svARB */
        {  170, 2222 }, /* glVertexAttrib2sv and glVertexAttrib2svNV */
        { 1014,  170 }, /* glVertexAttrib2svARB and glVertexAttrib2sv */
        { 1014, 2222 }, /* glVertexAttrib2svARB and glVertexAttrib2svNV */
        { 2222,  170 }, /* glVertexAttrib2svNV and glVertexAttrib2sv */
        { 2222, 1014 }, /* glVertexAttrib2svNV and glVertexAttrib2svARB */
        {  171, 1015 }, /* glVertexAttrib3d and glVertexAttrib3dARB */
        {  171, 2223 }, /* glVertexAttrib3d and glVertexAttrib3dNV */
        { 1015,  171 }, /* glVertexAttrib3dARB and glVertexAttrib3d */
        { 1015, 2223 }, /* glVertexAttrib3dARB and glVertexAttrib3dNV */
        { 2223,  171 }, /* glVertexAttrib3dNV and glVertexAttrib3d */
        { 2223, 1015 }, /* glVertexAttrib3dNV and glVertexAttrib3dARB */
        {  172, 1016 }, /* glVertexAttrib3dv and glVertexAttrib3dvARB */
        {  172, 2224 }, /* glVertexAttrib3dv and glVertexAttrib3dvNV */
        { 1016,  172 }, /* glVertexAttrib3dvARB and glVertexAttrib3dv */
        { 1016, 2224 }, /* glVertexAttrib3dvARB and glVertexAttrib3dvNV */
        { 2224,  172 }, /* glVertexAttrib3dvNV and glVertexAttrib3dv */
        { 2224, 1016 }, /* glVertexAttrib3dvNV and glVertexAttrib3dvARB */
        {  173, 1017 }, /* glVertexAttrib3f and glVertexAttrib3fARB */
        {  173, 2225 }, /* glVertexAttrib3f and glVertexAttrib3fNV */
        { 1017,  173 }, /* glVertexAttrib3fARB and glVertexAttrib3f */
        { 1017, 2225 }, /* glVertexAttrib3fARB and glVertexAttrib3fNV */
        { 2225,  173 }, /* glVertexAttrib3fNV and glVertexAttrib3f */
        { 2225, 1017 }, /* glVertexAttrib3fNV and glVertexAttrib3fARB */
        {  174, 1018 }, /* glVertexAttrib3fv and glVertexAttrib3fvARB */
        {  174, 2226 }, /* glVertexAttrib3fv and glVertexAttrib3fvNV */
        { 1018,  174 }, /* glVertexAttrib3fvARB and glVertexAttrib3fv */
        { 1018, 2226 }, /* glVertexAttrib3fvARB and glVertexAttrib3fvNV */
        { 2226,  174 }, /* glVertexAttrib3fvNV and glVertexAttrib3fv */
        { 2226, 1018 }, /* glVertexAttrib3fvNV and glVertexAttrib3fvARB */
        {  175, 1019 }, /* glVertexAttrib3s and glVertexAttrib3sARB */
        {  175, 2227 }, /* glVertexAttrib3s and glVertexAttrib3sNV */
        { 1019,  175 }, /* glVertexAttrib3sARB and glVertexAttrib3s */
        { 1019, 2227 }, /* glVertexAttrib3sARB and glVertexAttrib3sNV */
        { 2227,  175 }, /* glVertexAttrib3sNV and glVertexAttrib3s */
        { 2227, 1019 }, /* glVertexAttrib3sNV and glVertexAttrib3sARB */
        {  176, 1020 }, /* glVertexAttrib3sv and glVertexAttrib3svARB */
        {  176, 2228 }, /* glVertexAttrib3sv and glVertexAttrib3svNV */
        { 1020,  176 }, /* glVertexAttrib3svARB and glVertexAttrib3sv */
        { 1020, 2228 }, /* glVertexAttrib3svARB and glVertexAttrib3svNV */
        { 2228,  176 }, /* glVertexAttrib3svNV and glVertexAttrib3sv */
        { 2228, 1020 }, /* glVertexAttrib3svNV and glVertexAttrib3svARB */
        {  184, 1028 }, /* glVertexAttrib4bv and glVertexAttrib4bvARB */
        { 1028,  184 }, /* glVertexAttrib4bvARB and glVertexAttrib4bv */
        {  185, 1029 }, /* glVertexAttrib4d and glVertexAttrib4dARB */
        {  185, 2229 }, /* glVertexAttrib4d and glVertexAttrib4dNV */
        { 1029,  185 }, /* glVertexAttrib4dARB and glVertexAttrib4d */
        { 1029, 2229 }, /* glVertexAttrib4dARB and glVertexAttrib4dNV */
        { 2229,  185 }, /* glVertexAttrib4dNV and glVertexAttrib4d */
        { 2229, 1029 }, /* glVertexAttrib4dNV and glVertexAttrib4dARB */
        {  186, 1030 }, /* glVertexAttrib4dv and glVertexAttrib4dvARB */
        {  186, 2230 }, /* glVertexAttrib4dv and glVertexAttrib4dvNV */
        { 1030,  186 }, /* glVertexAttrib4dvARB and glVertexAttrib4dv */
        { 1030, 2230 }, /* glVertexAttrib4dvARB and glVertexAttrib4dvNV */
        { 2230,  186 }, /* glVertexAttrib4dvNV and glVertexAttrib4dv */
        { 2230, 1030 }, /* glVertexAttrib4dvNV and glVertexAttrib4dvARB */
        {  187, 1031 }, /* glVertexAttrib4f and glVertexAttrib4fARB */
        {  187, 2231 }, /* glVertexAttrib4f and glVertexAttrib4fNV */
        { 1031,  187 }, /* glVertexAttrib4fARB and glVertexAttrib4f */
        { 1031, 2231 }, /* glVertexAttrib4fARB and glVertexAttrib4fNV */
        { 2231,  187 }, /* glVertexAttrib4fNV and glVertexAttrib4f */
        { 2231, 1031 }, /* glVertexAttrib4fNV and glVertexAttrib4fARB */
        {  188, 1032 }, /* glVertexAttrib4fv and glVertexAttrib4fvARB */
        {  188, 2232 }, /* glVertexAttrib4fv and glVertexAttrib4fvNV */
        { 1032,  188 }, /* glVertexAttrib4fvARB and glVertexAttrib4fv */
        { 1032, 2232 }, /* glVertexAttrib4fvARB and glVertexAttrib4fvNV */
        { 2232,  188 }, /* glVertexAttrib4fvNV and glVertexAttrib4fv */
        { 2232, 1032 }, /* glVertexAttrib4fvNV and glVertexAttrib4fvARB */
        {  189, 1033 }, /* glVertexAttrib4iv and glVertexAttrib4ivARB */
        { 1033,  189 }, /* glVertexAttrib4ivARB and glVertexAttrib4iv */
        {  177, 1021 }, /* glVertexAttrib4Nbv and glVertexAttrib4NbvARB */
        { 1021,  177 }, /* glVertexAttrib4NbvARB and glVertexAttrib4Nbv */
        {  178, 1022 }, /* glVertexAttrib4Niv and glVertexAttrib4NivARB */
        { 1022,  178 }, /* glVertexAttrib4NivARB and glVertexAttrib4Niv */
        {  179, 1023 }, /* glVertexAttrib4Nsv and glVertexAttrib4NsvARB */
        { 1023,  179 }, /* glVertexAttrib4NsvARB and glVertexAttrib4Nsv */
        {  180, 1024 }, /* glVertexAttrib4Nub and glVertexAttrib4NubARB */
        {  180, 2235 }, /* glVertexAttrib4Nub and glVertexAttrib4ubNV */
        { 1024,  180 }, /* glVertexAttrib4NubARB and glVertexAttrib4Nub */
        { 1024, 2235 }, /* glVertexAttrib4NubARB and glVertexAttrib4ubNV */
        {  181, 1025 }, /* glVertexAttrib4Nubv and glVertexAttrib4NubvARB */
        {  181, 2236 }, /* glVertexAttrib4Nubv and glVertexAttrib4ubvNV */
        { 1025,  181 }, /* glVertexAttrib4NubvARB and glVertexAttrib4Nubv */
        { 1025, 2236 }, /* glVertexAttrib4NubvARB and glVertexAttrib4ubvNV */
        {  182, 1026 }, /* glVertexAttrib4Nuiv and glVertexAttrib4NuivARB */
        { 1026,  182 }, /* glVertexAttrib4NuivARB and glVertexAttrib4Nuiv */
        {  183, 1027 }, /* glVertexAttrib4Nusv and glVertexAttrib4NusvARB */
        { 1027,  183 }, /* glVertexAttrib4NusvARB and glVertexAttrib4Nusv */
        {  190, 1034 }, /* glVertexAttrib4s and glVertexAttrib4sARB */
        {  190, 2233 }, /* glVertexAttrib4s and glVertexAttrib4sNV */
        { 1034,  190 }, /* glVertexAttrib4sARB and glVertexAttrib4s */
        { 1034, 2233 }, /* glVertexAttrib4sARB and glVertexAttrib4sNV */
        { 2233,  190 }, /* glVertexAttrib4sNV and glVertexAttrib4s */
        { 2233, 1034 }, /* glVertexAttrib4sNV and glVertexAttrib4sARB */
        {  191, 1035 }, /* glVertexAttrib4sv and glVertexAttrib4svARB */
        {  191, 2234 }, /* glVertexAttrib4sv and glVertexAttrib4svNV */
        { 1035,  191 }, /* glVertexAttrib4svARB and glVertexAttrib4sv */
        { 1035, 2234 }, /* glVertexAttrib4svARB and glVertexAttrib4svNV */
        { 2234,  191 }, /* glVertexAttrib4svNV and glVertexAttrib4sv */
        { 2234, 1035 }, /* glVertexAttrib4svNV and glVertexAttrib4svARB */
        { 2235,  180 }, /* glVertexAttrib4ubNV and glVertexAttrib4Nub */
        { 2235, 1024 }, /* glVertexAttrib4ubNV and glVertexAttrib4NubARB */
        {  192, 1036 }, /* glVertexAttrib4ubv and glVertexAttrib4ubvARB */
        { 1036,  192 }, /* glVertexAttrib4ubvARB and glVertexAttrib4ubv */
        { 2236,  181 }, /* glVertexAttrib4ubvNV and glVertexAttrib4Nubv */
        { 2236, 1025 }, /* glVertexAttrib4ubvNV and glVertexAttrib4NubvARB */
        {  193, 1037 }, /* glVertexAttrib4uiv and glVertexAttrib4uivARB */
        { 1037,  193 }, /* glVertexAttrib4uivARB and glVertexAttrib4uiv */
        {  194, 1038 }, /* glVertexAttrib4usv and glVertexAttrib4usvARB */
        { 1038,  194 }, /* glVertexAttrib4usvARB and glVertexAttrib4usv */
        {  336, 2547 }, /* glVertexAttribDivisor and glVertexAttribDivisorANGLE */
        {  336,  857 }, /* glVertexAttribDivisor and glVertexAttribDivisorARB */
        {  336, 2601 }, /* glVertexAttribDivisor and glVertexAttribDivisorEXT */
        {  336, 2672 }, /* glVertexAttribDivisor and glVertexAttribDivisorNV */
        { 2547,  336 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisor */
        { 2547,  857 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisorARB */
        { 2547, 2601 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisorEXT */
        { 2547, 2672 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisorNV */
        {  857,  336 }, /* glVertexAttribDivisorARB and glVertexAttribDivisor */
        {  857, 2547 }, /* glVertexAttribDivisorARB and glVertexAttribDivisorANGLE */
        {  857, 2601 }, /* glVertexAttribDivisorARB and glVertexAttribDivisorEXT */
        {  857, 2672 }, /* glVertexAttribDivisorARB and glVertexAttribDivisorNV */
        { 2601,  336 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisor */
        { 2601, 2547 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisorANGLE */
        { 2601,  857 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisorARB */
        { 2601, 2672 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisorNV */
        { 2672,  336 }, /* glVertexAttribDivisorNV and glVertexAttribDivisor */
        { 2672, 2547 }, /* glVertexAttribDivisorNV and glVertexAttribDivisorANGLE */
        { 2672,  857 }, /* glVertexAttribDivisorNV and glVertexAttribDivisorARB */
        { 2672, 2601 }, /* glVertexAttribDivisorNV and glVertexAttribDivisorEXT */
        {  220, 1520 }, /* glVertexAttribI1i and glVertexAttribI1iEXT */
        { 1520,  220 }, /* glVertexAttribI1iEXT and glVertexAttribI1i */
        {  228, 1528 }, /* glVertexAttribI1iv and glVertexAttribI1ivEXT */
        { 1528,  228 }, /* glVertexAttribI1ivEXT and glVertexAttribI1iv */
        {  224, 1524 }, /* glVertexAttribI1ui and glVertexAttribI1uiEXT */
        { 1524,  224 }, /* glVertexAttribI1uiEXT and glVertexAttribI1ui */
        {  232, 1532 }, /* glVertexAttribI1uiv and glVertexAttribI1uivEXT */
        { 1532,  232 }, /* glVertexAttribI1uivEXT and glVertexAttribI1uiv */
        {  221, 1521 }, /* glVertexAttribI2i and glVertexAttribI2iEXT */
        { 1521,  221 }, /* glVertexAttribI2iEXT and glVertexAttribI2i */
        {  229, 1529 }, /* glVertexAttribI2iv and glVertexAttribI2ivEXT */
        { 1529,  229 }, /* glVertexAttribI2ivEXT and glVertexAttribI2iv */
        {  225, 1525 }, /* glVertexAttribI2ui and glVertexAttribI2uiEXT */
        { 1525,  225 }, /* glVertexAttribI2uiEXT and glVertexAttribI2ui */
        {  233, 1533 }, /* glVertexAttribI2uiv and glVertexAttribI2uivEXT */
        { 1533,  233 }, /* glVertexAttribI2uivEXT and glVertexAttribI2uiv */
        {  222, 1522 }, /* glVertexAttribI3i and glVertexAttribI3iEXT */
        { 1522,  222 }, /* glVertexAttribI3iEXT and glVertexAttribI3i */
        {  230, 1530 }, /* glVertexAttribI3iv and glVertexAttribI3ivEXT */
        { 1530,  230 }, /* glVertexAttribI3ivEXT and glVertexAttribI3iv */
        {  226, 1526 }, /* glVertexAttribI3ui and glVertexAttribI3uiEXT */
        { 1526,  226 }, /* glVertexAttribI3uiEXT and glVertexAttribI3ui */
        {  234, 1534 }, /* glVertexAttribI3uiv and glVertexAttribI3uivEXT */
        { 1534,  234 }, /* glVertexAttribI3uivEXT and glVertexAttribI3uiv */
        {  236, 1536 }, /* glVertexAttribI4bv and glVertexAttribI4bvEXT */
        { 1536,  236 }, /* glVertexAttribI4bvEXT and glVertexAttribI4bv */
        {  223, 1523 }, /* glVertexAttribI4i and glVertexAttribI4iEXT */
        { 1523,  223 }, /* glVertexAttribI4iEXT and glVertexAttribI4i */
        {  231, 1531 }, /* glVertexAttribI4iv and glVertexAttribI4ivEXT */
        { 1531,  231 }, /* glVertexAttribI4ivEXT and glVertexAttribI4iv */
        {  237, 1537 }, /* glVertexAttribI4sv and glVertexAttribI4svEXT */
        { 1537,  237 }, /* glVertexAttribI4svEXT and glVertexAttribI4sv */
        {  238, 1538 }, /* glVertexAttribI4ubv and glVertexAttribI4ubvEXT */
        { 1538,  238 }, /* glVertexAttribI4ubvEXT and glVertexAttribI4ubv */
        {  227, 1527 }, /* glVertexAttribI4ui and glVertexAttribI4uiEXT */
        { 1527,  227 }, /* glVertexAttribI4uiEXT and glVertexAttribI4ui */
        {  235, 1535 }, /* glVertexAttribI4uiv and glVertexAttribI4uivEXT */
        { 1535,  235 }, /* glVertexAttribI4uivEXT and glVertexAttribI4uiv */
        {  239, 1539 }, /* glVertexAttribI4usv and glVertexAttribI4usvEXT */
        { 1539,  239 }, /* glVertexAttribI4usvEXT and glVertexAttribI4usv */
        {  217, 1540 }, /* glVertexAttribIPointer and glVertexAttribIPointerEXT */
        { 1540,  217 }, /* glVertexAttribIPointerEXT and glVertexAttribIPointer */
        {  459, 1676 }, /* glVertexAttribL1d and glVertexAttribL1dEXT */
        { 1676,  459 }, /* glVertexAttribL1dEXT and glVertexAttribL1d */
        {  463, 1680 }, /* glVertexAttribL1dv and glVertexAttribL1dvEXT */
        { 1680,  463 }, /* glVertexAttribL1dvEXT and glVertexAttribL1dv */
        {  460, 1677 }, /* glVertexAttribL2d and glVertexAttribL2dEXT */
        { 1677,  460 }, /* glVertexAttribL2dEXT and glVertexAttribL2d */
        {  464, 1681 }, /* glVertexAttribL2dv and glVertexAttribL2dvEXT */
        { 1681,  464 }, /* glVertexAttribL2dvEXT and glVertexAttribL2dv */
        {  461, 1678 }, /* glVertexAttribL3d and glVertexAttribL3dEXT */
        { 1678,  461 }, /* glVertexAttribL3dEXT and glVertexAttribL3d */
        {  465, 1682 }, /* glVertexAttribL3dv and glVertexAttribL3dvEXT */
        { 1682,  465 }, /* glVertexAttribL3dvEXT and glVertexAttribL3dv */
        {  462, 1679 }, /* glVertexAttribL4d and glVertexAttribL4dEXT */
        { 1679,  462 }, /* glVertexAttribL4dEXT and glVertexAttribL4d */
        {  466, 1683 }, /* glVertexAttribL4dv and glVertexAttribL4dvEXT */
        { 1683,  466 }, /* glVertexAttribL4dvEXT and glVertexAttribL4dv */
        {  467, 1684 }, /* glVertexAttribLPointer and glVertexAttribLPointerEXT */
        { 1684,  467 }, /* glVertexAttribLPointerEXT and glVertexAttribLPointer */
        {  195, 1039 }, /* glVertexAttribPointer and glVertexAttribPointerARB */
        { 1039,  195 }, /* glVertexAttribPointerARB and glVertexAttribPointer */
        {  469, 2681 }, /* glViewportArrayv and glViewportArrayvNV */
        {  469, 2738 }, /* glViewportArrayv and glViewportArrayvOES */
        { 2681,  469 }, /* glViewportArrayvNV and glViewportArrayv */
        { 2681, 2738 }, /* glViewportArrayvNV and glViewportArrayvOES */
        { 2738,  469 }, /* glViewportArrayvOES and glViewportArrayv */
        { 2738, 2681 }, /* glViewportArrayvOES and glViewportArrayvNV */
        {  470, 2682 }, /* glViewportIndexedf and glViewportIndexedfNV */
        {  470, 2739 }, /* glViewportIndexedf and glViewportIndexedfOES */
        { 2682,  470 }, /* glViewportIndexedfNV and glViewportIndexedf */
        { 2682, 2739 }, /* glViewportIndexedfNV and glViewportIndexedfOES */
        { 2739,  470 }, /* glViewportIndexedfOES and glViewportIndexedf */
        { 2739, 2682 }, /* glViewportIndexedfOES and glViewportIndexedfNV */
        {  471, 2683 }, /* glViewportIndexedfv and glViewportIndexedfvNV */
        {  471, 2740 }, /* glViewportIndexedfv and glViewportIndexedfvOES */
        { 2683,  471 }, /* glViewportIndexedfvNV and glViewportIndexedfv */
        { 2683, 2740 }, /* glViewportIndexedfvNV and glViewportIndexedfvOES */
        { 2740,  471 }, /* glViewportIndexedfvOES and glViewportIndexedfv */
        { 2740, 2683 }, /* glViewportIndexedfvOES and glViewportIndexedfvNV */
        {  307, 2556 }, /* glWaitSync and glWaitSyncAPPLE */
        { 2556,  307 }, /* glWaitSyncAPPLE and glWaitSync */
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

    qsort(exts, num_exts, sizeof(uint64_t), compare_uint64);

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
         282, /* GL_ARM_cooperative_matrix_layouts */
         286, /* GL_ARM_shader_core_builtins */
         291, /* GL_ATI_draw_buffers */
         292, /* GL_ATI_element_array */
         293, /* GL_ATI_envmap_bumpmap */
         294, /* GL_ATI_fragment_shader */
         295, /* GL_ATI_map_object_buffer */
         296, /* GL_ATI_meminfo */
         297, /* GL_ATI_pixel_format_float */
         298, /* GL_ATI_pn_triangles */
         299, /* GL_ATI_separate_stencil */
         300, /* GL_ATI_text_fragment_shader */
         301, /* GL_ATI_texture_env_combine3 */
         302, /* GL_ATI_texture_float */
         303, /* GL_ATI_texture_mirror_once */
         304, /* GL_ATI_vertex_array_object */
         305, /* GL_ATI_vertex_attrib_array_object */
         306, /* GL_ATI_vertex_streams */
         314, /* GL_EXT_422_pixels */
         316, /* GL_EXT_EGL_image_storage */
         318, /* GL_EXT_EGL_sync */
         320, /* GL_EXT_abgr */
         322, /* GL_EXT_bgra */
         323, /* GL_EXT_bindable_uniform */
         324, /* GL_EXT_blend_color */
         325, /* GL_EXT_blend_equation_separate */
         327, /* GL_EXT_blend_func_separate */
         328, /* GL_EXT_blend_logic_op */
         329, /* GL_EXT_blend_minmax */
         330, /* GL_EXT_blend_subtract */
         331, /* GL_EXT_buffer_reference */
         332, /* GL_EXT_buffer_reference2 */
         333, /* GL_EXT_buffer_reference_uvec2 */
         338, /* GL_EXT_clip_volume_hint */
         339, /* GL_EXT_cmyka */
         342, /* GL_EXT_color_subtable */
         343, /* GL_EXT_compiled_vertex_array */
         345, /* GL_EXT_control_flow_attributes */
         346, /* GL_EXT_control_flow_attributes2 */
         347, /* GL_EXT_convolution */
         348, /* GL_EXT_coordinate_frame */
         350, /* GL_EXT_copy_texture */
         351, /* GL_EXT_cull_vertex */
         352, /* GL_EXT_debug_label */
         353, /* GL_EXT_debug_marker */
         354, /* GL_EXT_debug_printf */
         355, /* GL_EXT_demote_to_helper_invocation */
         356, /* GL_EXT_depth_bounds_test */
         358, /* GL_EXT_device_group */
         359, /* GL_EXT_direct_state_access */
         363, /* GL_EXT_draw_buffers2 */
         366, /* GL_EXT_draw_instanced */
         367, /* GL_EXT_draw_range_elements */
         369, /* GL_EXT_expect_assume */
         370, /* GL_EXT_external_buffer */
         372, /* GL_EXT_fog_coord */
         373, /* GL_EXT_fragment_invocation_density */
         374, /* GL_EXT_fragment_shader_barycentric */
         376, /* GL_EXT_framebuffer_blit */
         377, /* GL_EXT_framebuffer_blit_layers */
         378, /* GL_EXT_framebuffer_multisample */
         379, /* GL_EXT_framebuffer_multisample_blit_scaled */
         380, /* GL_EXT_framebuffer_object */
         381, /* GL_EXT_framebuffer_sRGB */
         384, /* GL_EXT_geometry_shader4 */
         385, /* GL_EXT_gpu_program_parameters */
         386, /* GL_EXT_gpu_shader4 */
         388, /* GL_EXT_histogram */
         389, /* GL_EXT_index_array_formats */
         390, /* GL_EXT_index_func */
         391, /* GL_EXT_index_material */
         392, /* GL_EXT_index_texture */
         394, /* GL_EXT_light_texture */
         396, /* GL_EXT_maximal_reconvergence */
         397, /* GL_EXT_memory_object */
         398, /* GL_EXT_memory_object_fd */
         399, /* GL_EXT_memory_object_win32 */
         400, /* GL_EXT_mesh_shader */
         401, /* GL_EXT_misc_attribute */
         402, /* GL_EXT_multi_draw_arrays */
         404, /* GL_EXT_multisample */
         409, /* GL_EXT_multiview_tessellation_geometry_shader */
         410, /* GL_EXT_multiview_texture_multisample */
         411, /* GL_EXT_multiview_timer_query */
         412, /* GL_EXT_nonuniform_qualifier */
         413, /* GL_EXT_null_initializer */
         415, /* GL_EXT_opacity_micromap */
         416, /* GL_EXT_packed_depth_stencil */
         417, /* GL_EXT_packed_float */
         418, /* GL_EXT_packed_pixels */
         419, /* GL_EXT_paletted_texture */
         420, /* GL_EXT_pixel_buffer_object */
         421, /* GL_EXT_pixel_transform */
         422, /* GL_EXT_pixel_transform_color_table */
         423, /* GL_EXT_point_parameters */
         424, /* GL_EXT_polygon_offset */
         425, /* GL_EXT_polygon_offset_clamp */
         426, /* GL_EXT_post_depth_coverage */
         429, /* GL_EXT_provoking_vertex */
         431, /* GL_EXT_raster_multisample */
         432, /* GL_EXT_ray_cull_mask */
         433, /* GL_EXT_ray_flags_primitive_culling */
         434, /* GL_EXT_ray_query */
         435, /* GL_EXT_ray_tracing */
         436, /* GL_EXT_ray_tracing_position_fetch */
         439, /* GL_EXT_rescale_normal */
         443, /* GL_EXT_samplerless_texture_functions */
         444, /* GL_EXT_scalar_block_layout */
         445, /* GL_EXT_secondary_color */
         446, /* GL_EXT_semaphore */
         447, /* GL_EXT_semaphore_fd */
         448, /* GL_EXT_semaphore_win32 */
         450, /* GL_EXT_separate_shader_objects */
         451, /* GL_EXT_separate_specular_color */
         452, /* GL_EXT_shader_16bit_storage */
         453, /* GL_EXT_shader_8bit_storage */
         454, /* GL_EXT_shader_atomic_float */
         455, /* GL_EXT_shader_atomic_float2 */
         456, /* GL_EXT_shader_atomic_int64 */
         457, /* GL_EXT_shader_explicit_arithmetic_types */
         458, /* GL_EXT_shader_explicit_arithmetic_types_float16 */
         459, /* GL_EXT_shader_explicit_arithmetic_types_float32 */
         460, /* GL_EXT_shader_explicit_arithmetic_types_float64 */
         461, /* GL_EXT_shader_explicit_arithmetic_types_int16 */
         462, /* GL_EXT_shader_explicit_arithmetic_types_int32 */
         463, /* GL_EXT_shader_explicit_arithmetic_types_int64 */
         464, /* GL_EXT_shader_explicit_arithmetic_types_int8 */
         465, /* GL_EXT_shader_framebuffer_fetch */
         466, /* GL_EXT_shader_framebuffer_fetch_non_coherent */
         468, /* GL_EXT_shader_image_int64 */
         469, /* GL_EXT_shader_image_load_formatted */
         470, /* GL_EXT_shader_image_load_store */
         472, /* GL_EXT_shader_integer_mix */
         477, /* GL_EXT_shader_quad_control */
         478, /* GL_EXT_shader_realtime_clock */
         479, /* GL_EXT_shader_samples_identical */
         480, /* GL_EXT_shader_subgroup_extended_types_float16 */
         481, /* GL_EXT_shader_subgroup_extended_types_int16 */
         482, /* GL_EXT_shader_subgroup_extended_types_int64 */
         483, /* GL_EXT_shader_subgroup_extended_types_int8 */
         485, /* GL_EXT_shader_tile_image */
         486, /* GL_EXT_shadow_funcs */
         488, /* GL_EXT_shared_memory_block */
         489, /* GL_EXT_shared_texture_palette */
         491, /* GL_EXT_sparse_texture2 */
         492, /* GL_EXT_spec_constant_composites */
         493, /* GL_EXT_spirv_intrinsics */
         494, /* GL_EXT_stencil_clear_tag */
         495, /* GL_EXT_stencil_two_side */
         496, /* GL_EXT_stencil_wrap */
         497, /* GL_EXT_subgroup_uniform_control_flow */
         498, /* GL_EXT_subgroupuniform_qualifier */
         499, /* GL_EXT_subtexture */
         500, /* GL_EXT_terminate_invocation */
         503, /* GL_EXT_texture */
         504, /* GL_EXT_texture3D */
         505, /* GL_EXT_texture_array */
         508, /* GL_EXT_texture_buffer_object */
         512, /* GL_EXT_texture_compression_latc */
         513, /* GL_EXT_texture_compression_rgtc */
         514, /* GL_EXT_texture_compression_s3tc */
         516, /* GL_EXT_texture_cube_map */
         518, /* GL_EXT_texture_env_add */
         519, /* GL_EXT_texture_env_combine */
         520, /* GL_EXT_texture_env_dot3 */
         521, /* GL_EXT_texture_filter_anisotropic */
         522, /* GL_EXT_texture_filter_minmax */
         525, /* GL_EXT_texture_integer */
         526, /* GL_EXT_texture_lod_bias */
         527, /* GL_EXT_texture_mirror_clamp */
         530, /* GL_EXT_texture_object */
         531, /* GL_EXT_texture_offset_non_const */
         532, /* GL_EXT_texture_perturb_normal */
         535, /* GL_EXT_texture_sRGB */
         536, /* GL_EXT_texture_sRGB_R8 */
         537, /* GL_EXT_texture_sRGB_RG8 */
         538, /* GL_EXT_texture_sRGB_decode */
         539, /* GL_EXT_texture_shadow_lod */
         540, /* GL_EXT_texture_shared_exponent */
         541, /* GL_EXT_texture_snorm */
         542, /* GL_EXT_texture_storage */
         544, /* GL_EXT_texture_swizzle */
         547, /* GL_EXT_timer_query */
         548, /* GL_EXT_transform_feedback */
         550, /* GL_EXT_vertex_array */
         551, /* GL_EXT_vertex_array_bgra */
         552, /* GL_EXT_vertex_attrib_64bit */
         553, /* GL_EXT_vertex_shader */
         554, /* GL_EXT_vertex_weighting */
         555, /* GL_EXT_vulkan_glsl_relaxed */
         556, /* GL_EXT_win32_keyed_mutex */
         557, /* GL_EXT_window_rectangles */
         558, /* GL_EXT_x11_sync_object */
         560, /* GL_GREMEDY_frame_terminator */
         561, /* GL_GREMEDY_string_marker */
         562, /* GL_HP_convolution_border_modes */
         563, /* GL_HP_image_transform */
         564, /* GL_HP_occlusion_test */
         565, /* GL_HP_texture_lighting */
         568, /* GL_HUAWEI_subpass_shading */
         569, /* GL_IBM_cull_vertex */
         570, /* GL_IBM_multimode_draw_arrays */
         571, /* GL_IBM_rasterpos_clip */
         572, /* GL_IBM_static_data */
         573, /* GL_IBM_texture_mirrored_repeat */
         574, /* GL_IBM_vertex_array_lists */
         584, /* GL_INGR_blend_func_separate */
         585, /* GL_INGR_color_clamp */
         586, /* GL_INGR_interlace_read */
         587, /* GL_INTEL_blackhole_render */
         588, /* GL_INTEL_conservative_rasterization */
         589, /* GL_INTEL_fragment_shader_ordering */
         590, /* GL_INTEL_framebuffer_CMAA */
         591, /* GL_INTEL_map_texture */
         592, /* GL_INTEL_parallel_arrays */
         593, /* GL_INTEL_performance_query */
         594, /* GL_KHR_blend_equation_advanced */
         595, /* GL_KHR_blend_equation_advanced_coherent */
         596, /* GL_KHR_context_flush_control */
         597, /* GL_KHR_debug */
         598, /* GL_KHR_memory_scope_semantics */
         599, /* GL_KHR_no_error */
         600, /* GL_KHR_parallel_shader_compile */
         601, /* GL_KHR_robust_buffer_access_behavior */
         602, /* GL_KHR_robustness */
         603, /* GL_KHR_shader_subgroup */
         604, /* GL_KHR_shader_subgroup_arithmetic */
         605, /* GL_KHR_shader_subgroup_ballot */
         606, /* GL_KHR_shader_subgroup_basic */
         607, /* GL_KHR_shader_subgroup_clustered */
         608, /* GL_KHR_shader_subgroup_quad */
         609, /* GL_KHR_shader_subgroup_rotate */
         610, /* GL_KHR_shader_subgroup_shuffle */
         611, /* GL_KHR_shader_subgroup_shuffle_relative */
         612, /* GL_KHR_shader_subgroup_vote */
         613, /* GL_KHR_texture_compression_astc_hdr */
         614, /* GL_KHR_texture_compression_astc_ldr */
         615, /* GL_KHR_texture_compression_astc_sliced_3d */
         616, /* GL_KHR_vulkan_glsl */
         617, /* GL_MESAX_texture_stack */
         619, /* GL_MESA_framebuffer_flip_x */
         620, /* GL_MESA_framebuffer_flip_y */
         621, /* GL_MESA_framebuffer_swap_xy */
         622, /* GL_MESA_pack_invert */
         623, /* GL_MESA_program_binary_formats */
         624, /* GL_MESA_resize_buffers */
         626, /* GL_MESA_shader_integer_functions */
         627, /* GL_MESA_texture_const_bandwidth */
         628, /* GL_MESA_tile_raster_order */
         629, /* GL_MESA_window_pos */
         630, /* GL_MESA_ycbcr_texture */
         631, /* GL_NVX_blend_equation_advanced_multi_draw_buffers */
         632, /* GL_NVX_conditional_render */
         633, /* GL_NVX_gpu_memory_info */
         634, /* GL_NVX_gpu_multicast2 */
         635, /* GL_NVX_linked_gpu_multicast */
         636, /* GL_NVX_multiview_per_view_attributes */
         637, /* GL_NVX_progress_fence */
         638, /* GL_NV_alpha_to_coverage_dither_control */
         639, /* GL_NV_bindless_multi_draw_indirect */
         640, /* GL_NV_bindless_multi_draw_indirect_count */
         641, /* GL_NV_bindless_texture */
         642, /* GL_NV_blend_equation_advanced */
         643, /* GL_NV_blend_equation_advanced_coherent */
         644, /* GL_NV_blend_minmax_factor */
         645, /* GL_NV_blend_square */
         646, /* GL_NV_clip_space_w_scaling */
         647, /* GL_NV_command_list */
         648, /* GL_NV_compute_program5 */
         649, /* GL_NV_compute_shader_derivatives */
         650, /* GL_NV_conditional_render */
         651, /* GL_NV_conservative_raster */
         652, /* GL_NV_conservative_raster_dilate */
         653, /* GL_NV_conservative_raster_pre_snap */
         654, /* GL_NV_conservative_raster_pre_snap_triangles */
         655, /* GL_NV_conservative_raster_underestimation */
         656, /* GL_NV_cooperative_matrix */
         657, /* GL_NV_cooperative_matrix2 */
         659, /* GL_NV_copy_depth_to_color */
         660, /* GL_NV_copy_image */
         662, /* GL_NV_deep_texture3D */
         663, /* GL_NV_depth_buffer_float */
         664, /* GL_NV_depth_clamp */
         666, /* GL_NV_displacement_micromap */
         669, /* GL_NV_draw_texture */
         670, /* GL_NV_draw_vulkan_image */
         671, /* GL_NV_evaluators */
         673, /* GL_NV_explicit_multisample */
         675, /* GL_NV_fence */
         676, /* GL_NV_fill_rectangle */
         677, /* GL_NV_float_buffer */
         678, /* GL_NV_fog_distance */
         679, /* GL_NV_fragment_coverage_to_color */
         680, /* GL_NV_fragment_program */
         681, /* GL_NV_fragment_program2 */
         682, /* GL_NV_fragment_program4 */
         683, /* GL_NV_fragment_program_option */
         684, /* GL_NV_fragment_shader_barycentric */
         685, /* GL_NV_fragment_shader_interlock */
         687, /* GL_NV_framebuffer_mixed_samples */
         689, /* GL_NV_framebuffer_multisample_coverage */
         691, /* GL_NV_geometry_program4 */
         692, /* GL_NV_geometry_shader4 */
         693, /* GL_NV_geometry_shader_passthrough */
         694, /* GL_NV_gpu_multicast */
         695, /* GL_NV_gpu_program4 */
         696, /* GL_NV_gpu_program5 */
         697, /* GL_NV_gpu_program5_mem_extended */
         698, /* GL_NV_gpu_shader5 */
         699, /* GL_NV_half_float */
         702, /* GL_NV_integer_cooperative_matrix */
         703, /* GL_NV_internalformat_sample_query */
         704, /* GL_NV_light_max_exponent */
         705, /* GL_NV_memory_attachment */
         706, /* GL_NV_memory_object_sparse */
         707, /* GL_NV_mesh_shader */
         708, /* GL_NV_multisample_coverage */
         709, /* GL_NV_multisample_filter_hint */
         711, /* GL_NV_occlusion_query */
         713, /* GL_NV_packed_depth_stencil */
         714, /* GL_NV_parameter_buffer_object */
         715, /* GL_NV_parameter_buffer_object2 */
         716, /* GL_NV_path_rendering */
         717, /* GL_NV_path_rendering_shared_edge */
         719, /* GL_NV_pixel_data_range */
         720, /* GL_NV_point_sprite */
         722, /* GL_NV_present_video */
         723, /* GL_NV_primitive_restart */
         724, /* GL_NV_primitive_shading_rate */
         725, /* GL_NV_query_resource */
         726, /* GL_NV_query_resource_tag */
         727, /* GL_NV_ray_tracing */
         728, /* GL_NV_ray_tracing_motion_blur */
         734, /* GL_NV_register_combiners */
         735, /* GL_NV_register_combiners2 */
         736, /* GL_NV_representative_fragment_test */
         737, /* GL_NV_robustness_video_memory_purge */
         739, /* GL_NV_sample_locations */
         740, /* GL_NV_sample_mask_override_coverage */
         741, /* GL_NV_scissor_exclusive */
         742, /* GL_NV_shader_atomic_counters */
         743, /* GL_NV_shader_atomic_float */
         744, /* GL_NV_shader_atomic_float64 */
         745, /* GL_NV_shader_atomic_fp16_vector */
         746, /* GL_NV_shader_atomic_int64 */
         747, /* GL_NV_shader_buffer_load */
         748, /* GL_NV_shader_buffer_store */
         749, /* GL_NV_shader_invocation_reorder */
         751, /* GL_NV_shader_sm_builtins */
         752, /* GL_NV_shader_storage_buffer_object */
         753, /* GL_NV_shader_subgroup_partitioned */
         754, /* GL_NV_shader_texture_footprint */
         755, /* GL_NV_shader_thread_group */
         756, /* GL_NV_shader_thread_shuffle */
         757, /* GL_NV_shading_rate_image */
         760, /* GL_NV_stereo_view_rendering */
         761, /* GL_NV_tessellation_program5 */
         762, /* GL_NV_texgen_emboss */
         763, /* GL_NV_texgen_reflection */
         764, /* GL_NV_texture_barrier */
         767, /* GL_NV_texture_compression_vtc */
         768, /* GL_NV_texture_env_combine4 */
         769, /* GL_NV_texture_expand_normal */
         770, /* GL_NV_texture_multisample */
         772, /* GL_NV_texture_rectangle */
         773, /* GL_NV_texture_rectangle_compressed */
         774, /* GL_NV_texture_shader */
         775, /* GL_NV_texture_shader2 */
         776, /* GL_NV_texture_shader3 */
         777, /* GL_NV_timeline_semaphore */
         778, /* GL_NV_transform_feedback */
         779, /* GL_NV_transform_feedback2 */
         780, /* GL_NV_uniform_buffer_std430_layout */
         781, /* GL_NV_uniform_buffer_unified_memory */
         782, /* GL_NV_vdpau_interop */
         783, /* GL_NV_vdpau_interop2 */
         784, /* GL_NV_vertex_array_range */
         785, /* GL_NV_vertex_array_range2 */
         786, /* GL_NV_vertex_attrib_integer_64bit */
         787, /* GL_NV_vertex_buffer_unified_memory */
         788, /* GL_NV_vertex_program */
         789, /* GL_NV_vertex_program1_1 */
         790, /* GL_NV_vertex_program2 */
         791, /* GL_NV_vertex_program2_option */
         792, /* GL_NV_vertex_program3 */
         793, /* GL_NV_vertex_program4 */
         794, /* GL_NV_video_capture */
         796, /* GL_NV_viewport_array2 */
         797, /* GL_NV_viewport_swizzle */
         801, /* GL_OES_byte_coordinates */
         804, /* GL_OES_compressed_paletted_texture */
         813, /* GL_OES_fixed_point */
         822, /* GL_OES_query_matrix */
         823, /* GL_OES_read_format */
         831, /* GL_OES_single_precision */
         855, /* GL_OML_interlace */
         856, /* GL_OML_resample */
         857, /* GL_OML_subsample */
         858, /* GL_OVR_multiview */
         859, /* GL_OVR_multiview2 */
         861, /* GL_PGI_misc_hints */
         862, /* GL_PGI_vertex_hints */
         871, /* GL_QCOM_image_processing */
         872, /* GL_QCOM_image_processing2 */
         887, /* GL_REND_screen_coordinates */
         888, /* GL_S3_s3tc */
         889, /* GL_SGIS_detail_texture */
         890, /* GL_SGIS_fog_function */
         891, /* GL_SGIS_generate_mipmap */
         892, /* GL_SGIS_multisample */
         893, /* GL_SGIS_pixel_texture */
         894, /* GL_SGIS_point_line_texgen */
         895, /* GL_SGIS_point_parameters */
         896, /* GL_SGIS_sharpen_texture */
         897, /* GL_SGIS_texture4D */
         898, /* GL_SGIS_texture_border_clamp */
         899, /* GL_SGIS_texture_color_mask */
         900, /* GL_SGIS_texture_edge_clamp */
         901, /* GL_SGIS_texture_filter4 */
         902, /* GL_SGIS_texture_lod */
         903, /* GL_SGIS_texture_select */
         904, /* GL_SGIX_async */
         905, /* GL_SGIX_async_histogram */
         906, /* GL_SGIX_async_pixel */
         907, /* GL_SGIX_blend_alpha_minmax */
         908, /* GL_SGIX_calligraphic_fragment */
         909, /* GL_SGIX_clipmap */
         910, /* GL_SGIX_convolution_accuracy */
         911, /* GL_SGIX_depth_pass_instrument */
         912, /* GL_SGIX_depth_texture */
         913, /* GL_SGIX_flush_raster */
         914, /* GL_SGIX_fog_offset */
         915, /* GL_SGIX_fragment_lighting */
         916, /* GL_SGIX_framezoom */
         917, /* GL_SGIX_igloo_interface */
         918, /* GL_SGIX_instruments */
         919, /* GL_SGIX_interlace */
         920, /* GL_SGIX_ir_instrument1 */
         921, /* GL_SGIX_list_priority */
         922, /* GL_SGIX_pixel_texture */
         923, /* GL_SGIX_pixel_tiles */
         924, /* GL_SGIX_polynomial_ffd */
         925, /* GL_SGIX_reference_plane */
         926, /* GL_SGIX_resample */
         927, /* GL_SGIX_scalebias_hint */
         928, /* GL_SGIX_shadow */
         929, /* GL_SGIX_shadow_ambient */
         930, /* GL_SGIX_sprite */
         931, /* GL_SGIX_subsample */
         932, /* GL_SGIX_tag_sample_buffer */
         933, /* GL_SGIX_texture_add_env */
         934, /* GL_SGIX_texture_coordinate_clamp */
         935, /* GL_SGIX_texture_lod_bias */
         936, /* GL_SGIX_texture_multi_buffer */
         937, /* GL_SGIX_texture_scale_bias */
         938, /* GL_SGIX_vertex_preclip */
         939, /* GL_SGIX_ycrcb */
         940, /* GL_SGIX_ycrcb_subsample */
         941, /* GL_SGIX_ycrcba */
         942, /* GL_SGI_color_matrix */
         943, /* GL_SGI_color_table */
         944, /* GL_SGI_texture_color_table */
         945, /* GL_SUNX_constant_data */
         946, /* GL_SUN_convolution_border_modes */
         947, /* GL_SUN_global_alpha */
         948, /* GL_SUN_mesh_array */
         949, /* GL_SUN_slice_accum */
         950, /* GL_SUN_triangle_list */
         951, /* GL_SUN_vertex */
         953, /* GL_WIN_phong_shading */
         954, /* GL_WIN_specular_fog */
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
    unsigned short version_value;
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

    version_value = (major << 8U) | minor;

    context->VERSION_1_0 = version_value >= 0x0100;
    context->VERSION_1_1 = version_value >= 0x0101;
    context->VERSION_1_2 = version_value >= 0x0102;
    context->VERSION_1_3 = version_value >= 0x0103;
    context->VERSION_1_4 = version_value >= 0x0104;
    context->VERSION_1_5 = version_value >= 0x0105;
    context->VERSION_2_0 = version_value >= 0x0200;
    context->VERSION_2_1 = version_value >= 0x0201;
    context->VERSION_3_0 = version_value >= 0x0300;
    context->VERSION_3_1 = version_value >= 0x0301;
    context->VERSION_3_2 = version_value >= 0x0302;
    context->VERSION_3_3 = version_value >= 0x0303;
    context->VERSION_4_0 = version_value >= 0x0400;
    context->VERSION_4_1 = version_value >= 0x0401;
    context->VERSION_4_2 = version_value >= 0x0402;
    context->VERSION_4_3 = version_value >= 0x0403;
    context->VERSION_4_4 = version_value >= 0x0404;
    context->VERSION_4_5 = version_value >= 0x0405;
    context->VERSION_4_6 = version_value >= 0x0406;

    return GLAD_MAKE_VERSION(major, minor);
}

GLAD_NO_INLINE int gladLoadGLContextUserPtr(GladGLContext *context, GLADuserptrloadfunc load, void *userptr) {
    int version;
    uint32_t i;

    context->GetString = (PFNGLGETSTRINGPROC) load(userptr, "glGetString");
    if(context->GetString == NULL) return 0;
    version = glad_gl_find_core_gl(context);

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_GL_feature_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_GL_feature_pfn_ranges[i];
        if (context->featArray[range->extension]) {
            glad_gl_load_pfn_range(context, load, userptr, range->start, range->count);
        }
    }

    if (!glad_gl_find_extensions_gl(context)) return 0;

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_GL_ext_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_GL_ext_pfn_ranges[i];
        if (context->extArray[range->extension]) {
            glad_gl_load_pfn_range(context, load, userptr, range->start, range->count);
        }
    }

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
          45, /* GL_ANGLE_blob_cache */
          46, /* GL_ANGLE_client_arrays */
          47, /* GL_ANGLE_clip_cull_distance */
          48, /* GL_ANGLE_copy_texture_3d */
          49, /* GL_ANGLE_depth_texture */
          50, /* GL_ANGLE_framebuffer_blit */
          51, /* GL_ANGLE_framebuffer_multisample */
          52, /* GL_ANGLE_get_image */
          53, /* GL_ANGLE_get_serialized_context_string */
          54, /* GL_ANGLE_get_tex_level_parameter */
          55, /* GL_ANGLE_instanced_arrays */
          56, /* GL_ANGLE_logic_op */
          57, /* GL_ANGLE_lossy_etc_decode */
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
         282, /* GL_ARM_cooperative_matrix_layouts */
         283, /* GL_ARM_mali_program_binary */
         284, /* GL_ARM_mali_shader_binary */
         285, /* GL_ARM_rgba8 */
         286, /* GL_ARM_shader_core_builtins */
         287, /* GL_ARM_shader_core_properties */
         288, /* GL_ARM_shader_framebuffer_fetch */
         289, /* GL_ARM_shader_framebuffer_fetch_depth_stencil */
         290, /* GL_ARM_texture_unnormalized_coordinates */
         307, /* GL_CHROMIUM_bind_uniform_location */
         308, /* GL_CHROMIUM_copy_compressed_texture */
         309, /* GL_CHROMIUM_copy_texture */
         310, /* GL_CHROMIUM_framebuffer_mixed_samples */
         311, /* GL_CHROMIUM_lose_context */
         312, /* GL_DMP_program_binary */
         313, /* GL_DMP_shader_binary */
         315, /* GL_EXT_EGL_image_array */
         316, /* GL_EXT_EGL_image_storage */
         317, /* GL_EXT_EGL_image_storage_compression */
         319, /* GL_EXT_YUV_target */
         321, /* GL_EXT_base_instance */
         326, /* GL_EXT_blend_func_extended */
         329, /* GL_EXT_blend_minmax */
         331, /* GL_EXT_buffer_reference */
         332, /* GL_EXT_buffer_reference2 */
         333, /* GL_EXT_buffer_reference_uvec2 */
         334, /* GL_EXT_buffer_storage */
         335, /* GL_EXT_clear_texture */
         336, /* GL_EXT_clip_control */
         337, /* GL_EXT_clip_cull_distance */
         340, /* GL_EXT_color_buffer_float */
         341, /* GL_EXT_color_buffer_half_float */
         344, /* GL_EXT_conservative_depth */
         345, /* GL_EXT_control_flow_attributes */
         346, /* GL_EXT_control_flow_attributes2 */
         349, /* GL_EXT_copy_image */
         352, /* GL_EXT_debug_label */
         353, /* GL_EXT_debug_marker */
         354, /* GL_EXT_debug_printf */
         355, /* GL_EXT_demote_to_helper_invocation */
         357, /* GL_EXT_depth_clamp */
         358, /* GL_EXT_device_group */
         360, /* GL_EXT_discard_framebuffer */
         361, /* GL_EXT_disjoint_timer_query */
         362, /* GL_EXT_draw_buffers */
         364, /* GL_EXT_draw_buffers_indexed */
         365, /* GL_EXT_draw_elements_base_vertex */
         366, /* GL_EXT_draw_instanced */
         368, /* GL_EXT_draw_transform_feedback */
         369, /* GL_EXT_expect_assume */
         370, /* GL_EXT_external_buffer */
         371, /* GL_EXT_float_blend */
         373, /* GL_EXT_fragment_invocation_density */
         374, /* GL_EXT_fragment_shader_barycentric */
         375, /* GL_EXT_fragment_shading_rate */
         377, /* GL_EXT_framebuffer_blit_layers */
         382, /* GL_EXT_geometry_point_size */
         383, /* GL_EXT_geometry_shader */
         387, /* GL_EXT_gpu_shader5 */
         393, /* GL_EXT_instanced_arrays */
         395, /* GL_EXT_map_buffer_range */
         396, /* GL_EXT_maximal_reconvergence */
         397, /* GL_EXT_memory_object */
         398, /* GL_EXT_memory_object_fd */
         399, /* GL_EXT_memory_object_win32 */
         400, /* GL_EXT_mesh_shader */
         402, /* GL_EXT_multi_draw_arrays */
         403, /* GL_EXT_multi_draw_indirect */
         405, /* GL_EXT_multisampled_compatibility */
         406, /* GL_EXT_multisampled_render_to_texture */
         407, /* GL_EXT_multisampled_render_to_texture2 */
         408, /* GL_EXT_multiview_draw_buffers */
         409, /* GL_EXT_multiview_tessellation_geometry_shader */
         410, /* GL_EXT_multiview_texture_multisample */
         411, /* GL_EXT_multiview_timer_query */
         412, /* GL_EXT_nonuniform_qualifier */
         413, /* GL_EXT_null_initializer */
         414, /* GL_EXT_occlusion_query_boolean */
         415, /* GL_EXT_opacity_micromap */
         425, /* GL_EXT_polygon_offset_clamp */
         426, /* GL_EXT_post_depth_coverage */
         427, /* GL_EXT_primitive_bounding_box */
         428, /* GL_EXT_protected_textures */
         430, /* GL_EXT_pvrtc_sRGB */
         431, /* GL_EXT_raster_multisample */
         432, /* GL_EXT_ray_cull_mask */
         433, /* GL_EXT_ray_flags_primitive_culling */
         434, /* GL_EXT_ray_query */
         435, /* GL_EXT_ray_tracing */
         436, /* GL_EXT_ray_tracing_position_fetch */
         437, /* GL_EXT_read_format_bgra */
         438, /* GL_EXT_render_snorm */
         440, /* GL_EXT_robustness */
         441, /* GL_EXT_sRGB */
         442, /* GL_EXT_sRGB_write_control */
         443, /* GL_EXT_samplerless_texture_functions */
         444, /* GL_EXT_scalar_block_layout */
         446, /* GL_EXT_semaphore */
         447, /* GL_EXT_semaphore_fd */
         448, /* GL_EXT_semaphore_win32 */
         449, /* GL_EXT_separate_depth_stencil */
         450, /* GL_EXT_separate_shader_objects */
         452, /* GL_EXT_shader_16bit_storage */
         453, /* GL_EXT_shader_8bit_storage */
         454, /* GL_EXT_shader_atomic_float */
         455, /* GL_EXT_shader_atomic_float2 */
         456, /* GL_EXT_shader_atomic_int64 */
         457, /* GL_EXT_shader_explicit_arithmetic_types */
         458, /* GL_EXT_shader_explicit_arithmetic_types_float16 */
         459, /* GL_EXT_shader_explicit_arithmetic_types_float32 */
         460, /* GL_EXT_shader_explicit_arithmetic_types_float64 */
         461, /* GL_EXT_shader_explicit_arithmetic_types_int16 */
         462, /* GL_EXT_shader_explicit_arithmetic_types_int32 */
         463, /* GL_EXT_shader_explicit_arithmetic_types_int64 */
         464, /* GL_EXT_shader_explicit_arithmetic_types_int8 */
         465, /* GL_EXT_shader_framebuffer_fetch */
         466, /* GL_EXT_shader_framebuffer_fetch_non_coherent */
         467, /* GL_EXT_shader_group_vote */
         468, /* GL_EXT_shader_image_int64 */
         471, /* GL_EXT_shader_implicit_conversions */
         472, /* GL_EXT_shader_integer_mix */
         473, /* GL_EXT_shader_io_blocks */
         474, /* GL_EXT_shader_non_constant_global_initializers */
         475, /* GL_EXT_shader_pixel_local_storage */
         476, /* GL_EXT_shader_pixel_local_storage2 */
         477, /* GL_EXT_shader_quad_control */
         478, /* GL_EXT_shader_realtime_clock */
         479, /* GL_EXT_shader_samples_identical */
         480, /* GL_EXT_shader_subgroup_extended_types_float16 */
         481, /* GL_EXT_shader_subgroup_extended_types_int16 */
         482, /* GL_EXT_shader_subgroup_extended_types_int64 */
         483, /* GL_EXT_shader_subgroup_extended_types_int8 */
         484, /* GL_EXT_shader_texture_lod */
         485, /* GL_EXT_shader_tile_image */
         487, /* GL_EXT_shadow_samplers */
         488, /* GL_EXT_shared_memory_block */
         490, /* GL_EXT_sparse_texture */
         491, /* GL_EXT_sparse_texture2 */
         492, /* GL_EXT_spec_constant_composites */
         493, /* GL_EXT_spirv_intrinsics */
         497, /* GL_EXT_subgroup_uniform_control_flow */
         498, /* GL_EXT_subgroupuniform_qualifier */
         500, /* GL_EXT_terminate_invocation */
         501, /* GL_EXT_tessellation_point_size */
         502, /* GL_EXT_tessellation_shader */
         506, /* GL_EXT_texture_border_clamp */
         507, /* GL_EXT_texture_buffer */
         509, /* GL_EXT_texture_compression_astc_decode_mode */
         510, /* GL_EXT_texture_compression_bptc */
         511, /* GL_EXT_texture_compression_dxt1 */
         513, /* GL_EXT_texture_compression_rgtc */
         514, /* GL_EXT_texture_compression_s3tc */
         515, /* GL_EXT_texture_compression_s3tc_srgb */
         517, /* GL_EXT_texture_cube_map_array */
         521, /* GL_EXT_texture_filter_anisotropic */
         522, /* GL_EXT_texture_filter_minmax */
         523, /* GL_EXT_texture_format_BGRA8888 */
         524, /* GL_EXT_texture_format_sRGB_override */
         528, /* GL_EXT_texture_mirror_clamp_to_edge */
         529, /* GL_EXT_texture_norm16 */
         531, /* GL_EXT_texture_offset_non_const */
         533, /* GL_EXT_texture_query_lod */
         534, /* GL_EXT_texture_rg */
         536, /* GL_EXT_texture_sRGB_R8 */
         537, /* GL_EXT_texture_sRGB_RG8 */
         538, /* GL_EXT_texture_sRGB_decode */
         539, /* GL_EXT_texture_shadow_lod */
         542, /* GL_EXT_texture_storage */
         543, /* GL_EXT_texture_storage_compression */
         545, /* GL_EXT_texture_type_2_10_10_10_REV */
         546, /* GL_EXT_texture_view */
         549, /* GL_EXT_unpack_subimage */
         555, /* GL_EXT_vulkan_glsl_relaxed */
         556, /* GL_EXT_win32_keyed_mutex */
         557, /* GL_EXT_window_rectangles */
         559, /* GL_FJ_shader_binary_GCCSO */
         566, /* GL_HUAWEI_program_binary */
         567, /* GL_HUAWEI_shader_binary */
         568, /* GL_HUAWEI_subpass_shading */
         575, /* GL_IMG_bindless_texture */
         576, /* GL_IMG_framebuffer_downsample */
         577, /* GL_IMG_multisampled_render_to_texture */
         578, /* GL_IMG_program_binary */
         579, /* GL_IMG_read_format */
         580, /* GL_IMG_shader_binary */
         581, /* GL_IMG_texture_compression_pvrtc */
         582, /* GL_IMG_texture_compression_pvrtc2 */
         583, /* GL_IMG_texture_filter_cubic */
         587, /* GL_INTEL_blackhole_render */
         588, /* GL_INTEL_conservative_rasterization */
         590, /* GL_INTEL_framebuffer_CMAA */
         593, /* GL_INTEL_performance_query */
         594, /* GL_KHR_blend_equation_advanced */
         595, /* GL_KHR_blend_equation_advanced_coherent */
         596, /* GL_KHR_context_flush_control */
         597, /* GL_KHR_debug */
         598, /* GL_KHR_memory_scope_semantics */
         599, /* GL_KHR_no_error */
         600, /* GL_KHR_parallel_shader_compile */
         601, /* GL_KHR_robust_buffer_access_behavior */
         602, /* GL_KHR_robustness */
         603, /* GL_KHR_shader_subgroup */
         604, /* GL_KHR_shader_subgroup_arithmetic */
         605, /* GL_KHR_shader_subgroup_ballot */
         606, /* GL_KHR_shader_subgroup_basic */
         607, /* GL_KHR_shader_subgroup_clustered */
         608, /* GL_KHR_shader_subgroup_quad */
         609, /* GL_KHR_shader_subgroup_rotate */
         610, /* GL_KHR_shader_subgroup_shuffle */
         611, /* GL_KHR_shader_subgroup_shuffle_relative */
         612, /* GL_KHR_shader_subgroup_vote */
         613, /* GL_KHR_texture_compression_astc_hdr */
         614, /* GL_KHR_texture_compression_astc_ldr */
         615, /* GL_KHR_texture_compression_astc_sliced_3d */
         616, /* GL_KHR_vulkan_glsl */
         618, /* GL_MESA_bgra */
         619, /* GL_MESA_framebuffer_flip_x */
         620, /* GL_MESA_framebuffer_flip_y */
         621, /* GL_MESA_framebuffer_swap_xy */
         623, /* GL_MESA_program_binary_formats */
         625, /* GL_MESA_sampler_objects */
         626, /* GL_MESA_shader_integer_functions */
         627, /* GL_MESA_texture_const_bandwidth */
         631, /* GL_NVX_blend_equation_advanced_multi_draw_buffers */
         636, /* GL_NVX_multiview_per_view_attributes */
         641, /* GL_NV_bindless_texture */
         642, /* GL_NV_blend_equation_advanced */
         643, /* GL_NV_blend_equation_advanced_coherent */
         644, /* GL_NV_blend_minmax_factor */
         646, /* GL_NV_clip_space_w_scaling */
         649, /* GL_NV_compute_shader_derivatives */
         650, /* GL_NV_conditional_render */
         651, /* GL_NV_conservative_raster */
         653, /* GL_NV_conservative_raster_pre_snap */
         654, /* GL_NV_conservative_raster_pre_snap_triangles */
         656, /* GL_NV_cooperative_matrix */
         657, /* GL_NV_cooperative_matrix2 */
         658, /* GL_NV_copy_buffer */
         661, /* GL_NV_coverage_sample */
         665, /* GL_NV_depth_nonlinear */
         666, /* GL_NV_displacement_micromap */
         667, /* GL_NV_draw_buffers */
         668, /* GL_NV_draw_instanced */
         670, /* GL_NV_draw_vulkan_image */
         672, /* GL_NV_explicit_attrib_location */
         674, /* GL_NV_fbo_color_attachments */
         675, /* GL_NV_fence */
         676, /* GL_NV_fill_rectangle */
         679, /* GL_NV_fragment_coverage_to_color */
         684, /* GL_NV_fragment_shader_barycentric */
         685, /* GL_NV_fragment_shader_interlock */
         686, /* GL_NV_framebuffer_blit */
         687, /* GL_NV_framebuffer_mixed_samples */
         688, /* GL_NV_framebuffer_multisample */
         690, /* GL_NV_generate_mipmap_sRGB */
         693, /* GL_NV_geometry_shader_passthrough */
         698, /* GL_NV_gpu_shader5 */
         700, /* GL_NV_image_formats */
         701, /* GL_NV_instanced_arrays */
         702, /* GL_NV_integer_cooperative_matrix */
         703, /* GL_NV_internalformat_sample_query */
         705, /* GL_NV_memory_attachment */
         706, /* GL_NV_memory_object_sparse */
         707, /* GL_NV_mesh_shader */
         710, /* GL_NV_non_square_matrices */
         712, /* GL_NV_pack_subimage */
         716, /* GL_NV_path_rendering */
         717, /* GL_NV_path_rendering_shared_edge */
         718, /* GL_NV_pixel_buffer_object */
         721, /* GL_NV_polygon_mode */
         724, /* GL_NV_primitive_shading_rate */
         727, /* GL_NV_ray_tracing */
         728, /* GL_NV_ray_tracing_motion_blur */
         729, /* GL_NV_read_buffer */
         730, /* GL_NV_read_buffer_front */
         731, /* GL_NV_read_depth */
         732, /* GL_NV_read_depth_stencil */
         733, /* GL_NV_read_stencil */
         736, /* GL_NV_representative_fragment_test */
         738, /* GL_NV_sRGB_formats */
         739, /* GL_NV_sample_locations */
         740, /* GL_NV_sample_mask_override_coverage */
         741, /* GL_NV_scissor_exclusive */
         745, /* GL_NV_shader_atomic_fp16_vector */
         749, /* GL_NV_shader_invocation_reorder */
         750, /* GL_NV_shader_noperspective_interpolation */
         751, /* GL_NV_shader_sm_builtins */
         753, /* GL_NV_shader_subgroup_partitioned */
         754, /* GL_NV_shader_texture_footprint */
         757, /* GL_NV_shading_rate_image */
         758, /* GL_NV_shadow_samplers_array */
         759, /* GL_NV_shadow_samplers_cube */
         760, /* GL_NV_stereo_view_rendering */
         764, /* GL_NV_texture_barrier */
         765, /* GL_NV_texture_border_clamp */
         766, /* GL_NV_texture_compression_s3tc_update */
         771, /* GL_NV_texture_npot_2D_mipmap */
         777, /* GL_NV_timeline_semaphore */
         795, /* GL_NV_viewport_array */
         796, /* GL_NV_viewport_array2 */
         797, /* GL_NV_viewport_swizzle */
         798, /* GL_OES_EGL_image */
         799, /* GL_OES_EGL_image_external */
         800, /* GL_OES_EGL_image_external_essl3 */
         802, /* GL_OES_compressed_ETC1_RGB8_sub_texture */
         803, /* GL_OES_compressed_ETC1_RGB8_texture */
         804, /* GL_OES_compressed_paletted_texture */
         805, /* GL_OES_copy_image */
         806, /* GL_OES_depth24 */
         807, /* GL_OES_depth32 */
         808, /* GL_OES_depth_texture */
         809, /* GL_OES_draw_buffers_indexed */
         810, /* GL_OES_draw_elements_base_vertex */
         811, /* GL_OES_element_index_uint */
         812, /* GL_OES_fbo_render_mipmap */
         814, /* GL_OES_fragment_precision_high */
         815, /* GL_OES_geometry_point_size */
         816, /* GL_OES_geometry_shader */
         817, /* GL_OES_get_program_binary */
         818, /* GL_OES_gpu_shader5 */
         819, /* GL_OES_mapbuffer */
         820, /* GL_OES_packed_depth_stencil */
         821, /* GL_OES_primitive_bounding_box */
         824, /* GL_OES_required_internalformat */
         825, /* GL_OES_rgb8_rgba8 */
         826, /* GL_OES_sample_shading */
         827, /* GL_OES_sample_variables */
         828, /* GL_OES_shader_image_atomic */
         829, /* GL_OES_shader_io_blocks */
         830, /* GL_OES_shader_multisample_interpolation */
         832, /* GL_OES_standard_derivatives */
         833, /* GL_OES_stencil1 */
         834, /* GL_OES_stencil4 */
         835, /* GL_OES_surfaceless_context */
         836, /* GL_OES_tessellation_point_size */
         837, /* GL_OES_tessellation_shader */
         838, /* GL_OES_texture_3D */
         839, /* GL_OES_texture_border_clamp */
         840, /* GL_OES_texture_buffer */
         841, /* GL_OES_texture_compression_astc */
         842, /* GL_OES_texture_cube_map_array */
         843, /* GL_OES_texture_float */
         844, /* GL_OES_texture_float_linear */
         845, /* GL_OES_texture_half_float */
         846, /* GL_OES_texture_half_float_linear */
         847, /* GL_OES_texture_npot */
         848, /* GL_OES_texture_stencil8 */
         849, /* GL_OES_texture_storage_multisample_2d_array */
         850, /* GL_OES_texture_view */
         851, /* GL_OES_vertex_array_object */
         852, /* GL_OES_vertex_half_float */
         853, /* GL_OES_vertex_type_10_10_10_2 */
         854, /* GL_OES_viewport_array */
         858, /* GL_OVR_multiview */
         859, /* GL_OVR_multiview2 */
         860, /* GL_OVR_multiview_multisampled_render_to_texture */
         863, /* GL_QCOM_YUV_texture_gather */
         864, /* GL_QCOM_alpha_test */
         865, /* GL_QCOM_binning_control */
         866, /* GL_QCOM_driver_control */
         867, /* GL_QCOM_extended_get */
         868, /* GL_QCOM_extended_get2 */
         869, /* GL_QCOM_frame_extrapolation */
         870, /* GL_QCOM_framebuffer_foveated */
         871, /* GL_QCOM_image_processing */
         872, /* GL_QCOM_image_processing2 */
         873, /* GL_QCOM_motion_estimation */
         874, /* GL_QCOM_perfmon_global_mode */
         875, /* GL_QCOM_render_sRGB_R8_RG8 */
         876, /* GL_QCOM_render_shared_exponent */
         877, /* GL_QCOM_shader_framebuffer_fetch_noncoherent */
         878, /* GL_QCOM_shader_framebuffer_fetch_rate */
         879, /* GL_QCOM_shading_rate */
         880, /* GL_QCOM_texture_foveated */
         881, /* GL_QCOM_texture_foveated2 */
         882, /* GL_QCOM_texture_foveated_subsampled_layout */
         883, /* GL_QCOM_texture_lod_bias */
         884, /* GL_QCOM_tiled_rendering */
         885, /* GL_QCOM_writeonly_rendering */
         886, /* GL_QCOM_ycbcr_degamma */
         952, /* GL_VIV_shader_binary */
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
    unsigned short version_value;
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

    version_value = (major << 8U) | minor;

    context->ES_VERSION_2_0 = version_value >= 0x0200;
    context->ES_VERSION_3_0 = version_value >= 0x0300;
    context->ES_VERSION_3_1 = version_value >= 0x0301;
    context->ES_VERSION_3_2 = version_value >= 0x0302;

    return GLAD_MAKE_VERSION(major, minor);
}

GLAD_NO_INLINE int gladLoadGLES2ContextUserPtr(GladGLContext *context, GLADuserptrloadfunc load, void *userptr) {
    int version;
    uint32_t i;

    context->GetString = (PFNGLGETSTRINGPROC) load(userptr, "glGetString");
    if(context->GetString == NULL) return 0;
    version = glad_gl_find_core_gles2(context);

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_GL_feature_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_GL_feature_pfn_ranges[i];
        if (context->featArray[range->extension]) {
            glad_gl_load_pfn_range(context, load, userptr, range->start, range->count);
        }
    }

    if (!glad_gl_find_extensions_gles2(context)) return 0;

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_GL_ext_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_GL_ext_pfn_ranges[i];
        if (context->extArray[range->extension]) {
            glad_gl_load_pfn_range(context, load, userptr, range->start, range->count);
        }
    }

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
