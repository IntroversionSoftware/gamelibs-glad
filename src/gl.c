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

#ifndef GLAD_EXTERNAL_XXHASH
#define XXH_INLINE_ALL
#define XXH_NO_STREAM
#endif
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

#ifdef __cplusplus
extern "C" {
#endif

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

GLAD_NO_INLINE static void glad_sort_hashes(uint64_t *a, size_t n) {
    /* Ciura gap sequence; we’ll skip the big ones at runtime. */
    static const size_t gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};
    size_t gi = 0;

    if (!a || n < 2)
        return;

    while (gi < GLAD_ARRAYSIZE(gaps) && gaps[gi] >= n)
        gi++;

    for (; gi < GLAD_ARRAYSIZE(gaps); ++gi) {
        size_t gap = gaps[gi], i;
        for (i = gap; i < n; ++i) {
            uint64_t v = a[i];
            size_t j = i;
            /* gapped insertion sort */
            while (j >= gap && a[j - gap] > v) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = v;
        }
    }
}

GLAD_NO_INLINE static uint64_t glad_hash_string(const char *str, size_t length)
{
    return XXH3_64bits(str, length);
}

#ifdef __cplusplus
}
#endif

#endif /* GLAD_IMPL_HASHSEARCH_C_ */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
GladGLContext glad_gl_context = {};
#else
GladGLContext glad_gl_context = { 0 };
#endif

static const char * const GLAD_GL_fn_names[] = {
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
    /* 1485 */ "glGetFragmentShadingRatesEXT",
    /* 1486 */ "glShadingRateEXT",
    /* 1487 */ "glShadingRateCombinerOpsEXT",
    /* 1488 */ "glFramebufferShadingRateEXT",
    /* 1489 */ "glBlitFramebufferEXT",
    /* 1490 */ "glBlitFramebufferLayersEXT",
    /* 1491 */ "glBlitFramebufferLayerEXT",
    /* 1492 */ "glRenderbufferStorageMultisampleEXT",
    /* 1493 */ "glIsRenderbufferEXT",
    /* 1494 */ "glBindRenderbufferEXT",
    /* 1495 */ "glDeleteRenderbuffersEXT",
    /* 1496 */ "glGenRenderbuffersEXT",
    /* 1497 */ "glRenderbufferStorageEXT",
    /* 1498 */ "glGetRenderbufferParameterivEXT",
    /* 1499 */ "glIsFramebufferEXT",
    /* 1500 */ "glBindFramebufferEXT",
    /* 1501 */ "glDeleteFramebuffersEXT",
    /* 1502 */ "glGenFramebuffersEXT",
    /* 1503 */ "glCheckFramebufferStatusEXT",
    /* 1504 */ "glFramebufferTexture1DEXT",
    /* 1505 */ "glFramebufferTexture2DEXT",
    /* 1506 */ "glFramebufferTexture3DEXT",
    /* 1507 */ "glFramebufferRenderbufferEXT",
    /* 1508 */ "glGetFramebufferAttachmentParameterivEXT",
    /* 1509 */ "glGenerateMipmapEXT",
    /* 1510 */ "glFramebufferTextureEXT",
    /* 1511 */ "glProgramParameteriEXT",
    /* 1512 */ "glProgramEnvParameters4fvEXT",
    /* 1513 */ "glProgramLocalParameters4fvEXT",
    /* 1514 */ "glGetUniformuivEXT",
    /* 1515 */ "glGetFragDataLocationEXT",
    /* 1516 */ "glUniform1uiEXT",
    /* 1517 */ "glUniform2uiEXT",
    /* 1518 */ "glUniform3uiEXT",
    /* 1519 */ "glUniform4uiEXT",
    /* 1520 */ "glUniform1uivEXT",
    /* 1521 */ "glUniform2uivEXT",
    /* 1522 */ "glUniform3uivEXT",
    /* 1523 */ "glUniform4uivEXT",
    /* 1524 */ "glVertexAttribI1iEXT",
    /* 1525 */ "glVertexAttribI2iEXT",
    /* 1526 */ "glVertexAttribI3iEXT",
    /* 1527 */ "glVertexAttribI4iEXT",
    /* 1528 */ "glVertexAttribI1uiEXT",
    /* 1529 */ "glVertexAttribI2uiEXT",
    /* 1530 */ "glVertexAttribI3uiEXT",
    /* 1531 */ "glVertexAttribI4uiEXT",
    /* 1532 */ "glVertexAttribI1ivEXT",
    /* 1533 */ "glVertexAttribI2ivEXT",
    /* 1534 */ "glVertexAttribI3ivEXT",
    /* 1535 */ "glVertexAttribI4ivEXT",
    /* 1536 */ "glVertexAttribI1uivEXT",
    /* 1537 */ "glVertexAttribI2uivEXT",
    /* 1538 */ "glVertexAttribI3uivEXT",
    /* 1539 */ "glVertexAttribI4uivEXT",
    /* 1540 */ "glVertexAttribI4bvEXT",
    /* 1541 */ "glVertexAttribI4svEXT",
    /* 1542 */ "glVertexAttribI4ubvEXT",
    /* 1543 */ "glVertexAttribI4usvEXT",
    /* 1544 */ "glVertexAttribIPointerEXT",
    /* 1545 */ "glGetVertexAttribIivEXT",
    /* 1546 */ "glGetVertexAttribIuivEXT",
    /* 1547 */ "glGetHistogramEXT",
    /* 1548 */ "glGetHistogramParameterfvEXT",
    /* 1549 */ "glGetHistogramParameterivEXT",
    /* 1550 */ "glGetMinmaxEXT",
    /* 1551 */ "glGetMinmaxParameterfvEXT",
    /* 1552 */ "glGetMinmaxParameterivEXT",
    /* 1553 */ "glHistogramEXT",
    /* 1554 */ "glMinmaxEXT",
    /* 1555 */ "glResetHistogramEXT",
    /* 1556 */ "glResetMinmaxEXT",
    /* 1557 */ "glIndexFuncEXT",
    /* 1558 */ "glIndexMaterialEXT",
    /* 1559 */ "glApplyTextureEXT",
    /* 1560 */ "glTextureLightEXT",
    /* 1561 */ "glTextureMaterialEXT",
    /* 1562 */ "glGetUnsignedBytevEXT",
    /* 1563 */ "glGetUnsignedBytei_vEXT",
    /* 1564 */ "glDeleteMemoryObjectsEXT",
    /* 1565 */ "glIsMemoryObjectEXT",
    /* 1566 */ "glCreateMemoryObjectsEXT",
    /* 1567 */ "glMemoryObjectParameterivEXT",
    /* 1568 */ "glGetMemoryObjectParameterivEXT",
    /* 1569 */ "glTexStorageMem2DEXT",
    /* 1570 */ "glTexStorageMem2DMultisampleEXT",
    /* 1571 */ "glTexStorageMem3DEXT",
    /* 1572 */ "glTexStorageMem3DMultisampleEXT",
    /* 1573 */ "glBufferStorageMemEXT",
    /* 1574 */ "glTextureStorageMem2DEXT",
    /* 1575 */ "glTextureStorageMem2DMultisampleEXT",
    /* 1576 */ "glTextureStorageMem3DEXT",
    /* 1577 */ "glTextureStorageMem3DMultisampleEXT",
    /* 1578 */ "glNamedBufferStorageMemEXT",
    /* 1579 */ "glTexStorageMem1DEXT",
    /* 1580 */ "glTextureStorageMem1DEXT",
    /* 1581 */ "glImportMemoryFdEXT",
    /* 1582 */ "glImportMemoryWin32HandleEXT",
    /* 1583 */ "glImportMemoryWin32NameEXT",
    /* 1584 */ "glMultiDrawArraysEXT",
    /* 1585 */ "glMultiDrawElementsEXT",
    /* 1586 */ "glSampleMaskEXT",
    /* 1587 */ "glSamplePatternEXT",
    /* 1588 */ "glColorTableEXT",
    /* 1589 */ "glGetColorTableEXT",
    /* 1590 */ "glGetColorTableParameterivEXT",
    /* 1591 */ "glGetColorTableParameterfvEXT",
    /* 1592 */ "glPixelTransformParameteriEXT",
    /* 1593 */ "glPixelTransformParameterfEXT",
    /* 1594 */ "glPixelTransformParameterivEXT",
    /* 1595 */ "glPixelTransformParameterfvEXT",
    /* 1596 */ "glGetPixelTransformParameterivEXT",
    /* 1597 */ "glGetPixelTransformParameterfvEXT",
    /* 1598 */ "glPointParameterfEXT",
    /* 1599 */ "glPointParameterfvEXT",
    /* 1600 */ "glPolygonOffsetEXT",
    /* 1601 */ "glPolygonOffsetClampEXT",
    /* 1602 */ "glProvokingVertexEXT",
    /* 1603 */ "glRasterSamplesEXT",
    /* 1604 */ "glGenSemaphoresEXT",
    /* 1605 */ "glDeleteSemaphoresEXT",
    /* 1606 */ "glIsSemaphoreEXT",
    /* 1607 */ "glSemaphoreParameterui64vEXT",
    /* 1608 */ "glGetSemaphoreParameterui64vEXT",
    /* 1609 */ "glWaitSemaphoreEXT",
    /* 1610 */ "glSignalSemaphoreEXT",
    /* 1611 */ "glImportSemaphoreFdEXT",
    /* 1612 */ "glImportSemaphoreWin32HandleEXT",
    /* 1613 */ "glImportSemaphoreWin32NameEXT",
    /* 1614 */ "glSecondaryColor3bEXT",
    /* 1615 */ "glSecondaryColor3bvEXT",
    /* 1616 */ "glSecondaryColor3dEXT",
    /* 1617 */ "glSecondaryColor3dvEXT",
    /* 1618 */ "glSecondaryColor3fEXT",
    /* 1619 */ "glSecondaryColor3fvEXT",
    /* 1620 */ "glSecondaryColor3iEXT",
    /* 1621 */ "glSecondaryColor3ivEXT",
    /* 1622 */ "glSecondaryColor3sEXT",
    /* 1623 */ "glSecondaryColor3svEXT",
    /* 1624 */ "glSecondaryColor3ubEXT",
    /* 1625 */ "glSecondaryColor3ubvEXT",
    /* 1626 */ "glSecondaryColor3uiEXT",
    /* 1627 */ "glSecondaryColor3uivEXT",
    /* 1628 */ "glSecondaryColor3usEXT",
    /* 1629 */ "glSecondaryColor3usvEXT",
    /* 1630 */ "glSecondaryColorPointerEXT",
    /* 1631 */ "glUseShaderProgramEXT",
    /* 1632 */ "glActiveProgramEXT",
    /* 1633 */ "glCreateShaderProgramEXT",
    /* 1634 */ "glFramebufferFetchBarrierEXT",
    /* 1635 */ "glBindImageTextureEXT",
    /* 1636 */ "glMemoryBarrierEXT",
    /* 1637 */ "glStencilClearTagEXT",
    /* 1638 */ "glActiveStencilFaceEXT",
    /* 1639 */ "glTexSubImage1DEXT",
    /* 1640 */ "glTexSubImage2DEXT",
    /* 1641 */ "glTexImage3DEXT",
    /* 1642 */ "glTexSubImage3DEXT",
    /* 1643 */ "glFramebufferTextureLayerEXT",
    /* 1644 */ "glTexParameterIivEXT",
    /* 1645 */ "glTexParameterIuivEXT",
    /* 1646 */ "glGetTexParameterIivEXT",
    /* 1647 */ "glGetTexParameterIuivEXT",
    /* 1648 */ "glTexBufferEXT",
    /* 1649 */ "glClearColorIiEXT",
    /* 1650 */ "glClearColorIuiEXT",
    /* 1651 */ "glAreTexturesResidentEXT",
    /* 1652 */ "glBindTextureEXT",
    /* 1653 */ "glDeleteTexturesEXT",
    /* 1654 */ "glGenTexturesEXT",
    /* 1655 */ "glIsTextureEXT",
    /* 1656 */ "glPrioritizeTexturesEXT",
    /* 1657 */ "glTextureNormalEXT",
    /* 1658 */ "glTexStorage1DEXT",
    /* 1659 */ "glTexStorage2DEXT",
    /* 1660 */ "glTexStorage3DEXT",
    /* 1661 */ "glCreateSemaphoresNV",
    /* 1662 */ "glSemaphoreParameterivNV",
    /* 1663 */ "glGetSemaphoreParameterivNV",
    /* 1664 */ "glBeginTransformFeedbackEXT",
    /* 1665 */ "glEndTransformFeedbackEXT",
    /* 1666 */ "glBindBufferRangeEXT",
    /* 1667 */ "glBindBufferOffsetEXT",
    /* 1668 */ "glBindBufferBaseEXT",
    /* 1669 */ "glTransformFeedbackVaryingsEXT",
    /* 1670 */ "glGetTransformFeedbackVaryingEXT",
    /* 1671 */ "glArrayElementEXT",
    /* 1672 */ "glColorPointerEXT",
    /* 1673 */ "glDrawArraysEXT",
    /* 1674 */ "glEdgeFlagPointerEXT",
    /* 1675 */ "glGetPointervEXT",
    /* 1676 */ "glIndexPointerEXT",
    /* 1677 */ "glNormalPointerEXT",
    /* 1678 */ "glTexCoordPointerEXT",
    /* 1679 */ "glVertexPointerEXT",
    /* 1680 */ "glVertexAttribL1dEXT",
    /* 1681 */ "glVertexAttribL2dEXT",
    /* 1682 */ "glVertexAttribL3dEXT",
    /* 1683 */ "glVertexAttribL4dEXT",
    /* 1684 */ "glVertexAttribL1dvEXT",
    /* 1685 */ "glVertexAttribL2dvEXT",
    /* 1686 */ "glVertexAttribL3dvEXT",
    /* 1687 */ "glVertexAttribL4dvEXT",
    /* 1688 */ "glVertexAttribLPointerEXT",
    /* 1689 */ "glGetVertexAttribLdvEXT",
    /* 1690 */ "glBeginVertexShaderEXT",
    /* 1691 */ "glEndVertexShaderEXT",
    /* 1692 */ "glBindVertexShaderEXT",
    /* 1693 */ "glGenVertexShadersEXT",
    /* 1694 */ "glDeleteVertexShaderEXT",
    /* 1695 */ "glShaderOp1EXT",
    /* 1696 */ "glShaderOp2EXT",
    /* 1697 */ "glShaderOp3EXT",
    /* 1698 */ "glSwizzleEXT",
    /* 1699 */ "glWriteMaskEXT",
    /* 1700 */ "glInsertComponentEXT",
    /* 1701 */ "glExtractComponentEXT",
    /* 1702 */ "glGenSymbolsEXT",
    /* 1703 */ "glSetInvariantEXT",
    /* 1704 */ "glSetLocalConstantEXT",
    /* 1705 */ "glVariantbvEXT",
    /* 1706 */ "glVariantsvEXT",
    /* 1707 */ "glVariantivEXT",
    /* 1708 */ "glVariantfvEXT",
    /* 1709 */ "glVariantdvEXT",
    /* 1710 */ "glVariantubvEXT",
    /* 1711 */ "glVariantusvEXT",
    /* 1712 */ "glVariantuivEXT",
    /* 1713 */ "glVariantPointerEXT",
    /* 1714 */ "glEnableVariantClientStateEXT",
    /* 1715 */ "glDisableVariantClientStateEXT",
    /* 1716 */ "glBindLightParameterEXT",
    /* 1717 */ "glBindMaterialParameterEXT",
    /* 1718 */ "glBindTexGenParameterEXT",
    /* 1719 */ "glBindTextureUnitParameterEXT",
    /* 1720 */ "glBindParameterEXT",
    /* 1721 */ "glIsVariantEnabledEXT",
    /* 1722 */ "glGetVariantBooleanvEXT",
    /* 1723 */ "glGetVariantIntegervEXT",
    /* 1724 */ "glGetVariantFloatvEXT",
    /* 1725 */ "glGetVariantPointervEXT",
    /* 1726 */ "glGetInvariantBooleanvEXT",
    /* 1727 */ "glGetInvariantIntegervEXT",
    /* 1728 */ "glGetInvariantFloatvEXT",
    /* 1729 */ "glGetLocalConstantBooleanvEXT",
    /* 1730 */ "glGetLocalConstantIntegervEXT",
    /* 1731 */ "glGetLocalConstantFloatvEXT",
    /* 1732 */ "glVertexWeightfEXT",
    /* 1733 */ "glVertexWeightfvEXT",
    /* 1734 */ "glVertexWeightPointerEXT",
    /* 1735 */ "glAcquireKeyedMutexWin32EXT",
    /* 1736 */ "glReleaseKeyedMutexWin32EXT",
    /* 1737 */ "glWindowRectanglesEXT",
    /* 1738 */ "glImportSyncEXT",
    /* 1739 */ "glFrameTerminatorGREMEDY",
    /* 1740 */ "glStringMarkerGREMEDY",
    /* 1741 */ "glImageTransformParameteriHP",
    /* 1742 */ "glImageTransformParameterfHP",
    /* 1743 */ "glImageTransformParameterivHP",
    /* 1744 */ "glImageTransformParameterfvHP",
    /* 1745 */ "glGetImageTransformParameterivHP",
    /* 1746 */ "glGetImageTransformParameterfvHP",
    /* 1747 */ "glMultiModeDrawArraysIBM",
    /* 1748 */ "glMultiModeDrawElementsIBM",
    /* 1749 */ "glFlushStaticDataIBM",
    /* 1750 */ "glColorPointerListIBM",
    /* 1751 */ "glSecondaryColorPointerListIBM",
    /* 1752 */ "glEdgeFlagPointerListIBM",
    /* 1753 */ "glFogCoordPointerListIBM",
    /* 1754 */ "glIndexPointerListIBM",
    /* 1755 */ "glNormalPointerListIBM",
    /* 1756 */ "glTexCoordPointerListIBM",
    /* 1757 */ "glVertexPointerListIBM",
    /* 1758 */ "glBlendFuncSeparateINGR",
    /* 1759 */ "glApplyFramebufferAttachmentCMAAINTEL",
    /* 1760 */ "glSyncTextureINTEL",
    /* 1761 */ "glUnmapTexture2DINTEL",
    /* 1762 */ "glMapTexture2DINTEL",
    /* 1763 */ "glVertexPointervINTEL",
    /* 1764 */ "glNormalPointervINTEL",
    /* 1765 */ "glColorPointervINTEL",
    /* 1766 */ "glTexCoordPointervINTEL",
    /* 1767 */ "glBeginPerfQueryINTEL",
    /* 1768 */ "glCreatePerfQueryINTEL",
    /* 1769 */ "glDeletePerfQueryINTEL",
    /* 1770 */ "glEndPerfQueryINTEL",
    /* 1771 */ "glGetFirstPerfQueryIdINTEL",
    /* 1772 */ "glGetNextPerfQueryIdINTEL",
    /* 1773 */ "glGetPerfCounterInfoINTEL",
    /* 1774 */ "glGetPerfQueryDataINTEL",
    /* 1775 */ "glGetPerfQueryIdByNameINTEL",
    /* 1776 */ "glGetPerfQueryInfoINTEL",
    /* 1777 */ "glBlendBarrierKHR",
    /* 1778 */ "glMaxShaderCompilerThreadsKHR",
    /* 1779 */ "glFramebufferParameteriMESA",
    /* 1780 */ "glGetFramebufferParameterivMESA",
    /* 1781 */ "glAddClientPointerRangeMESA",
    /* 1782 */ "glReleaseClientPointerRangeMESA",
    /* 1783 */ "glResizeBuffersMESA",
    /* 1784 */ "glWindowPos2dMESA",
    /* 1785 */ "glWindowPos2dvMESA",
    /* 1786 */ "glWindowPos2fMESA",
    /* 1787 */ "glWindowPos2fvMESA",
    /* 1788 */ "glWindowPos2iMESA",
    /* 1789 */ "glWindowPos2ivMESA",
    /* 1790 */ "glWindowPos2sMESA",
    /* 1791 */ "glWindowPos2svMESA",
    /* 1792 */ "glWindowPos3dMESA",
    /* 1793 */ "glWindowPos3dvMESA",
    /* 1794 */ "glWindowPos3fMESA",
    /* 1795 */ "glWindowPos3fvMESA",
    /* 1796 */ "glWindowPos3iMESA",
    /* 1797 */ "glWindowPos3ivMESA",
    /* 1798 */ "glWindowPos3sMESA",
    /* 1799 */ "glWindowPos3svMESA",
    /* 1800 */ "glWindowPos4dMESA",
    /* 1801 */ "glWindowPos4dvMESA",
    /* 1802 */ "glWindowPos4fMESA",
    /* 1803 */ "glWindowPos4fvMESA",
    /* 1804 */ "glWindowPos4iMESA",
    /* 1805 */ "glWindowPos4ivMESA",
    /* 1806 */ "glWindowPos4sMESA",
    /* 1807 */ "glWindowPos4svMESA",
    /* 1808 */ "glBeginConditionalRenderNVX",
    /* 1809 */ "glEndConditionalRenderNVX",
    /* 1810 */ "glLGPUNamedBufferSubDataNVX",
    /* 1811 */ "glLGPUCopyImageSubDataNVX",
    /* 1812 */ "glLGPUInterlockNVX",
    /* 1813 */ "glAlphaToCoverageDitherControlNV",
    /* 1814 */ "glMultiDrawArraysIndirectBindlessNV",
    /* 1815 */ "glMultiDrawElementsIndirectBindlessNV",
    /* 1816 */ "glMultiDrawArraysIndirectBindlessCountNV",
    /* 1817 */ "glMultiDrawElementsIndirectBindlessCountNV",
    /* 1818 */ "glGetTextureHandleNV",
    /* 1819 */ "glGetTextureSamplerHandleNV",
    /* 1820 */ "glMakeTextureHandleResidentNV",
    /* 1821 */ "glMakeTextureHandleNonResidentNV",
    /* 1822 */ "glGetImageHandleNV",
    /* 1823 */ "glMakeImageHandleResidentNV",
    /* 1824 */ "glMakeImageHandleNonResidentNV",
    /* 1825 */ "glUniformHandleui64NV",
    /* 1826 */ "glUniformHandleui64vNV",
    /* 1827 */ "glProgramUniformHandleui64NV",
    /* 1828 */ "glProgramUniformHandleui64vNV",
    /* 1829 */ "glIsTextureHandleResidentNV",
    /* 1830 */ "glIsImageHandleResidentNV",
    /* 1831 */ "glBlendParameteriNV",
    /* 1832 */ "glBlendBarrierNV",
    /* 1833 */ "glViewportPositionWScaleNV",
    /* 1834 */ "glCreateStatesNV",
    /* 1835 */ "glDeleteStatesNV",
    /* 1836 */ "glIsStateNV",
    /* 1837 */ "glStateCaptureNV",
    /* 1838 */ "glGetCommandHeaderNV",
    /* 1839 */ "glGetStageIndexNV",
    /* 1840 */ "glDrawCommandsNV",
    /* 1841 */ "glDrawCommandsAddressNV",
    /* 1842 */ "glDrawCommandsStatesNV",
    /* 1843 */ "glDrawCommandsStatesAddressNV",
    /* 1844 */ "glCreateCommandListsNV",
    /* 1845 */ "glDeleteCommandListsNV",
    /* 1846 */ "glIsCommandListNV",
    /* 1847 */ "glListDrawCommandsStatesClientNV",
    /* 1848 */ "glCommandListSegmentsNV",
    /* 1849 */ "glCompileCommandListNV",
    /* 1850 */ "glCallCommandListNV",
    /* 1851 */ "glBeginConditionalRenderNV",
    /* 1852 */ "glEndConditionalRenderNV",
    /* 1853 */ "glSubpixelPrecisionBiasNV",
    /* 1854 */ "glConservativeRasterParameterfNV",
    /* 1855 */ "glConservativeRasterParameteriNV",
    /* 1856 */ "glCopyImageSubDataNV",
    /* 1857 */ "glDepthRangedNV",
    /* 1858 */ "glClearDepthdNV",
    /* 1859 */ "glDepthBoundsdNV",
    /* 1860 */ "glDrawTextureNV",
    /* 1861 */ "glDrawVkImageNV",
    /* 1862 */ "glGetVkProcAddrNV",
    /* 1863 */ "glWaitVkSemaphoreNV",
    /* 1864 */ "glSignalVkSemaphoreNV",
    /* 1865 */ "glSignalVkFenceNV",
    /* 1866 */ "glMapControlPointsNV",
    /* 1867 */ "glMapParameterivNV",
    /* 1868 */ "glMapParameterfvNV",
    /* 1869 */ "glGetMapControlPointsNV",
    /* 1870 */ "glGetMapParameterivNV",
    /* 1871 */ "glGetMapParameterfvNV",
    /* 1872 */ "glGetMapAttribParameterivNV",
    /* 1873 */ "glGetMapAttribParameterfvNV",
    /* 1874 */ "glEvalMapsNV",
    /* 1875 */ "glGetMultisamplefvNV",
    /* 1876 */ "glSampleMaskIndexedNV",
    /* 1877 */ "glTexRenderbufferNV",
    /* 1878 */ "glDeleteFencesNV",
    /* 1879 */ "glGenFencesNV",
    /* 1880 */ "glIsFenceNV",
    /* 1881 */ "glTestFenceNV",
    /* 1882 */ "glGetFenceivNV",
    /* 1883 */ "glFinishFenceNV",
    /* 1884 */ "glSetFenceNV",
    /* 1885 */ "glFragmentCoverageColorNV",
    /* 1886 */ "glProgramNamedParameter4fNV",
    /* 1887 */ "glProgramNamedParameter4fvNV",
    /* 1888 */ "glProgramNamedParameter4dNV",
    /* 1889 */ "glProgramNamedParameter4dvNV",
    /* 1890 */ "glGetProgramNamedParameterfvNV",
    /* 1891 */ "glGetProgramNamedParameterdvNV",
    /* 1892 */ "glCoverageModulationTableNV",
    /* 1893 */ "glGetCoverageModulationTableNV",
    /* 1894 */ "glCoverageModulationNV",
    /* 1895 */ "glRenderbufferStorageMultisampleCoverageNV",
    /* 1896 */ "glProgramVertexLimitNV",
    /* 1897 */ "glFramebufferTextureFaceEXT",
    /* 1898 */ "glProgramLocalParameterI4iNV",
    /* 1899 */ "glProgramLocalParameterI4ivNV",
    /* 1900 */ "glProgramLocalParametersI4ivNV",
    /* 1901 */ "glProgramLocalParameterI4uiNV",
    /* 1902 */ "glProgramLocalParameterI4uivNV",
    /* 1903 */ "glProgramLocalParametersI4uivNV",
    /* 1904 */ "glProgramEnvParameterI4iNV",
    /* 1905 */ "glProgramEnvParameterI4ivNV",
    /* 1906 */ "glProgramEnvParametersI4ivNV",
    /* 1907 */ "glProgramEnvParameterI4uiNV",
    /* 1908 */ "glProgramEnvParameterI4uivNV",
    /* 1909 */ "glProgramEnvParametersI4uivNV",
    /* 1910 */ "glGetProgramLocalParameterIivNV",
    /* 1911 */ "glGetProgramLocalParameterIuivNV",
    /* 1912 */ "glGetProgramEnvParameterIivNV",
    /* 1913 */ "glGetProgramEnvParameterIuivNV",
    /* 1914 */ "glProgramSubroutineParametersuivNV",
    /* 1915 */ "glGetProgramSubroutineParameteruivNV",
    /* 1916 */ "glVertex2hNV",
    /* 1917 */ "glVertex2hvNV",
    /* 1918 */ "glVertex3hNV",
    /* 1919 */ "glVertex3hvNV",
    /* 1920 */ "glVertex4hNV",
    /* 1921 */ "glVertex4hvNV",
    /* 1922 */ "glNormal3hNV",
    /* 1923 */ "glNormal3hvNV",
    /* 1924 */ "glColor3hNV",
    /* 1925 */ "glColor3hvNV",
    /* 1926 */ "glColor4hNV",
    /* 1927 */ "glColor4hvNV",
    /* 1928 */ "glTexCoord1hNV",
    /* 1929 */ "glTexCoord1hvNV",
    /* 1930 */ "glTexCoord2hNV",
    /* 1931 */ "glTexCoord2hvNV",
    /* 1932 */ "glTexCoord3hNV",
    /* 1933 */ "glTexCoord3hvNV",
    /* 1934 */ "glTexCoord4hNV",
    /* 1935 */ "glTexCoord4hvNV",
    /* 1936 */ "glMultiTexCoord1hNV",
    /* 1937 */ "glMultiTexCoord1hvNV",
    /* 1938 */ "glMultiTexCoord2hNV",
    /* 1939 */ "glMultiTexCoord2hvNV",
    /* 1940 */ "glMultiTexCoord3hNV",
    /* 1941 */ "glMultiTexCoord3hvNV",
    /* 1942 */ "glMultiTexCoord4hNV",
    /* 1943 */ "glMultiTexCoord4hvNV",
    /* 1944 */ "glVertexAttrib1hNV",
    /* 1945 */ "glVertexAttrib1hvNV",
    /* 1946 */ "glVertexAttrib2hNV",
    /* 1947 */ "glVertexAttrib2hvNV",
    /* 1948 */ "glVertexAttrib3hNV",
    /* 1949 */ "glVertexAttrib3hvNV",
    /* 1950 */ "glVertexAttrib4hNV",
    /* 1951 */ "glVertexAttrib4hvNV",
    /* 1952 */ "glVertexAttribs1hvNV",
    /* 1953 */ "glVertexAttribs2hvNV",
    /* 1954 */ "glVertexAttribs3hvNV",
    /* 1955 */ "glVertexAttribs4hvNV",
    /* 1956 */ "glFogCoordhNV",
    /* 1957 */ "glFogCoordhvNV",
    /* 1958 */ "glSecondaryColor3hNV",
    /* 1959 */ "glSecondaryColor3hvNV",
    /* 1960 */ "glVertexWeighthNV",
    /* 1961 */ "glVertexWeighthvNV",
    /* 1962 */ "glGetInternalformatSampleivNV",
    /* 1963 */ "glRenderGpuMaskNV",
    /* 1964 */ "glMulticastBufferSubDataNV",
    /* 1965 */ "glMulticastCopyBufferSubDataNV",
    /* 1966 */ "glMulticastCopyImageSubDataNV",
    /* 1967 */ "glMulticastBlitFramebufferNV",
    /* 1968 */ "glMulticastFramebufferSampleLocationsfvNV",
    /* 1969 */ "glMulticastBarrierNV",
    /* 1970 */ "glMulticastWaitSyncNV",
    /* 1971 */ "glMulticastGetQueryObjectivNV",
    /* 1972 */ "glMulticastGetQueryObjectuivNV",
    /* 1973 */ "glMulticastGetQueryObjecti64vNV",
    /* 1974 */ "glMulticastGetQueryObjectui64vNV",
    /* 1975 */ "glUploadGpuMaskNVX",
    /* 1976 */ "glMulticastViewportArrayvNVX",
    /* 1977 */ "glMulticastViewportPositionWScaleNVX",
    /* 1978 */ "glMulticastScissorArrayvNVX",
    /* 1979 */ "glAsyncCopyBufferSubDataNVX",
    /* 1980 */ "glAsyncCopyImageSubDataNVX",
    /* 1981 */ "glCreateProgressFenceNVX",
    /* 1982 */ "glSignalSemaphoreui64NVX",
    /* 1983 */ "glWaitSemaphoreui64NVX",
    /* 1984 */ "glClientWaitSemaphoreui64NVX",
    /* 1985 */ "glGetMemoryObjectDetachedResourcesuivNV",
    /* 1986 */ "glResetMemoryObjectParameterNV",
    /* 1987 */ "glTexAttachMemoryNV",
    /* 1988 */ "glBufferAttachMemoryNV",
    /* 1989 */ "glTextureAttachMemoryNV",
    /* 1990 */ "glNamedBufferAttachMemoryNV",
    /* 1991 */ "glBufferPageCommitmentMemNV",
    /* 1992 */ "glTexPageCommitmentMemNV",
    /* 1993 */ "glNamedBufferPageCommitmentMemNV",
    /* 1994 */ "glTexturePageCommitmentMemNV",
    /* 1995 */ "glDrawMeshTasksNV",
    /* 1996 */ "glDrawMeshTasksIndirectNV",
    /* 1997 */ "glMultiDrawMeshTasksIndirectNV",
    /* 1998 */ "glMultiDrawMeshTasksIndirectCountNV",
    /* 1999 */ "glGenOcclusionQueriesNV",
    /* 2000 */ "glDeleteOcclusionQueriesNV",
    /* 2001 */ "glIsOcclusionQueryNV",
    /* 2002 */ "glBeginOcclusionQueryNV",
    /* 2003 */ "glEndOcclusionQueryNV",
    /* 2004 */ "glGetOcclusionQueryivNV",
    /* 2005 */ "glGetOcclusionQueryuivNV",
    /* 2006 */ "glProgramBufferParametersfvNV",
    /* 2007 */ "glProgramBufferParametersIivNV",
    /* 2008 */ "glProgramBufferParametersIuivNV",
    /* 2009 */ "glGenPathsNV",
    /* 2010 */ "glDeletePathsNV",
    /* 2011 */ "glIsPathNV",
    /* 2012 */ "glPathCommandsNV",
    /* 2013 */ "glPathCoordsNV",
    /* 2014 */ "glPathSubCommandsNV",
    /* 2015 */ "glPathSubCoordsNV",
    /* 2016 */ "glPathStringNV",
    /* 2017 */ "glPathGlyphsNV",
    /* 2018 */ "glPathGlyphRangeNV",
    /* 2019 */ "glWeightPathsNV",
    /* 2020 */ "glCopyPathNV",
    /* 2021 */ "glInterpolatePathsNV",
    /* 2022 */ "glTransformPathNV",
    /* 2023 */ "glPathParameterivNV",
    /* 2024 */ "glPathParameteriNV",
    /* 2025 */ "glPathParameterfvNV",
    /* 2026 */ "glPathParameterfNV",
    /* 2027 */ "glPathDashArrayNV",
    /* 2028 */ "glPathStencilFuncNV",
    /* 2029 */ "glPathStencilDepthOffsetNV",
    /* 2030 */ "glStencilFillPathNV",
    /* 2031 */ "glStencilStrokePathNV",
    /* 2032 */ "glStencilFillPathInstancedNV",
    /* 2033 */ "glStencilStrokePathInstancedNV",
    /* 2034 */ "glPathCoverDepthFuncNV",
    /* 2035 */ "glCoverFillPathNV",
    /* 2036 */ "glCoverStrokePathNV",
    /* 2037 */ "glCoverFillPathInstancedNV",
    /* 2038 */ "glCoverStrokePathInstancedNV",
    /* 2039 */ "glGetPathParameterivNV",
    /* 2040 */ "glGetPathParameterfvNV",
    /* 2041 */ "glGetPathCommandsNV",
    /* 2042 */ "glGetPathCoordsNV",
    /* 2043 */ "glGetPathDashArrayNV",
    /* 2044 */ "glGetPathMetricsNV",
    /* 2045 */ "glGetPathMetricRangeNV",
    /* 2046 */ "glGetPathSpacingNV",
    /* 2047 */ "glIsPointInFillPathNV",
    /* 2048 */ "glIsPointInStrokePathNV",
    /* 2049 */ "glGetPathLengthNV",
    /* 2050 */ "glPointAlongPathNV",
    /* 2051 */ "glMatrixLoad3x2fNV",
    /* 2052 */ "glMatrixLoad3x3fNV",
    /* 2053 */ "glMatrixLoadTranspose3x3fNV",
    /* 2054 */ "glMatrixMult3x2fNV",
    /* 2055 */ "glMatrixMult3x3fNV",
    /* 2056 */ "glMatrixMultTranspose3x3fNV",
    /* 2057 */ "glStencilThenCoverFillPathNV",
    /* 2058 */ "glStencilThenCoverStrokePathNV",
    /* 2059 */ "glStencilThenCoverFillPathInstancedNV",
    /* 2060 */ "glStencilThenCoverStrokePathInstancedNV",
    /* 2061 */ "glPathGlyphIndexRangeNV",
    /* 2062 */ "glPathGlyphIndexArrayNV",
    /* 2063 */ "glPathMemoryGlyphIndexArrayNV",
    /* 2064 */ "glProgramPathFragmentInputGenNV",
    /* 2065 */ "glGetProgramResourcefvNV",
    /* 2066 */ "glPixelDataRangeNV",
    /* 2067 */ "glFlushPixelDataRangeNV",
    /* 2068 */ "glPointParameteriNV",
    /* 2069 */ "glPointParameterivNV",
    /* 2070 */ "glPresentFrameKeyedNV",
    /* 2071 */ "glPresentFrameDualFillNV",
    /* 2072 */ "glGetVideoivNV",
    /* 2073 */ "glGetVideouivNV",
    /* 2074 */ "glGetVideoi64vNV",
    /* 2075 */ "glGetVideoui64vNV",
    /* 2076 */ "glPrimitiveRestartNV",
    /* 2077 */ "glPrimitiveRestartIndexNV",
    /* 2078 */ "glQueryResourceNV",
    /* 2079 */ "glGenQueryResourceTagNV",
    /* 2080 */ "glDeleteQueryResourceTagNV",
    /* 2081 */ "glQueryResourceTagNV",
    /* 2082 */ "glCombinerParameterfvNV",
    /* 2083 */ "glCombinerParameterfNV",
    /* 2084 */ "glCombinerParameterivNV",
    /* 2085 */ "glCombinerParameteriNV",
    /* 2086 */ "glCombinerInputNV",
    /* 2087 */ "glCombinerOutputNV",
    /* 2088 */ "glFinalCombinerInputNV",
    /* 2089 */ "glGetCombinerInputParameterfvNV",
    /* 2090 */ "glGetCombinerInputParameterivNV",
    /* 2091 */ "glGetCombinerOutputParameterfvNV",
    /* 2092 */ "glGetCombinerOutputParameterivNV",
    /* 2093 */ "glGetFinalCombinerInputParameterfvNV",
    /* 2094 */ "glGetFinalCombinerInputParameterivNV",
    /* 2095 */ "glCombinerStageParameterfvNV",
    /* 2096 */ "glGetCombinerStageParameterfvNV",
    /* 2097 */ "glFramebufferSampleLocationsfvNV",
    /* 2098 */ "glNamedFramebufferSampleLocationsfvNV",
    /* 2099 */ "glResolveDepthValuesNV",
    /* 2100 */ "glScissorExclusiveNV",
    /* 2101 */ "glScissorExclusiveArrayvNV",
    /* 2102 */ "glMakeBufferResidentNV",
    /* 2103 */ "glMakeBufferNonResidentNV",
    /* 2104 */ "glIsBufferResidentNV",
    /* 2105 */ "glMakeNamedBufferResidentNV",
    /* 2106 */ "glMakeNamedBufferNonResidentNV",
    /* 2107 */ "glIsNamedBufferResidentNV",
    /* 2108 */ "glGetBufferParameterui64vNV",
    /* 2109 */ "glGetNamedBufferParameterui64vNV",
    /* 2110 */ "glGetIntegerui64vNV",
    /* 2111 */ "glUniformui64NV",
    /* 2112 */ "glUniformui64vNV",
    /* 2113 */ "glProgramUniformui64NV",
    /* 2114 */ "glProgramUniformui64vNV",
    /* 2115 */ "glBindShadingRateImageNV",
    /* 2116 */ "glGetShadingRateImagePaletteNV",
    /* 2117 */ "glGetShadingRateSampleLocationivNV",
    /* 2118 */ "glShadingRateImageBarrierNV",
    /* 2119 */ "glShadingRateImagePaletteNV",
    /* 2120 */ "glShadingRateSampleOrderNV",
    /* 2121 */ "glShadingRateSampleOrderCustomNV",
    /* 2122 */ "glTextureBarrierNV",
    /* 2123 */ "glTexImage2DMultisampleCoverageNV",
    /* 2124 */ "glTexImage3DMultisampleCoverageNV",
    /* 2125 */ "glTextureImage2DMultisampleNV",
    /* 2126 */ "glTextureImage3DMultisampleNV",
    /* 2127 */ "glTextureImage2DMultisampleCoverageNV",
    /* 2128 */ "glTextureImage3DMultisampleCoverageNV",
    /* 2129 */ "glBeginTransformFeedbackNV",
    /* 2130 */ "glEndTransformFeedbackNV",
    /* 2131 */ "glTransformFeedbackAttribsNV",
    /* 2132 */ "glBindBufferRangeNV",
    /* 2133 */ "glBindBufferOffsetNV",
    /* 2134 */ "glBindBufferBaseNV",
    /* 2135 */ "glTransformFeedbackVaryingsNV",
    /* 2136 */ "glActiveVaryingNV",
    /* 2137 */ "glGetVaryingLocationNV",
    /* 2138 */ "glGetActiveVaryingNV",
    /* 2139 */ "glGetTransformFeedbackVaryingNV",
    /* 2140 */ "glTransformFeedbackStreamAttribsNV",
    /* 2141 */ "glBindTransformFeedbackNV",
    /* 2142 */ "glDeleteTransformFeedbacksNV",
    /* 2143 */ "glGenTransformFeedbacksNV",
    /* 2144 */ "glIsTransformFeedbackNV",
    /* 2145 */ "glPauseTransformFeedbackNV",
    /* 2146 */ "glResumeTransformFeedbackNV",
    /* 2147 */ "glDrawTransformFeedbackNV",
    /* 2148 */ "glVDPAUInitNV",
    /* 2149 */ "glVDPAUFiniNV",
    /* 2150 */ "glVDPAURegisterVideoSurfaceNV",
    /* 2151 */ "glVDPAURegisterOutputSurfaceNV",
    /* 2152 */ "glVDPAUIsSurfaceNV",
    /* 2153 */ "glVDPAUUnregisterSurfaceNV",
    /* 2154 */ "glVDPAUGetSurfaceivNV",
    /* 2155 */ "glVDPAUSurfaceAccessNV",
    /* 2156 */ "glVDPAUMapSurfacesNV",
    /* 2157 */ "glVDPAUUnmapSurfacesNV",
    /* 2158 */ "glVDPAURegisterVideoSurfaceWithPictureStructureNV",
    /* 2159 */ "glFlushVertexArrayRangeNV",
    /* 2160 */ "glVertexArrayRangeNV",
    /* 2161 */ "glVertexAttribL1i64NV",
    /* 2162 */ "glVertexAttribL2i64NV",
    /* 2163 */ "glVertexAttribL3i64NV",
    /* 2164 */ "glVertexAttribL4i64NV",
    /* 2165 */ "glVertexAttribL1i64vNV",
    /* 2166 */ "glVertexAttribL2i64vNV",
    /* 2167 */ "glVertexAttribL3i64vNV",
    /* 2168 */ "glVertexAttribL4i64vNV",
    /* 2169 */ "glVertexAttribL1ui64NV",
    /* 2170 */ "glVertexAttribL2ui64NV",
    /* 2171 */ "glVertexAttribL3ui64NV",
    /* 2172 */ "glVertexAttribL4ui64NV",
    /* 2173 */ "glVertexAttribL1ui64vNV",
    /* 2174 */ "glVertexAttribL2ui64vNV",
    /* 2175 */ "glVertexAttribL3ui64vNV",
    /* 2176 */ "glVertexAttribL4ui64vNV",
    /* 2177 */ "glGetVertexAttribLi64vNV",
    /* 2178 */ "glGetVertexAttribLui64vNV",
    /* 2179 */ "glVertexAttribLFormatNV",
    /* 2180 */ "glBufferAddressRangeNV",
    /* 2181 */ "glVertexFormatNV",
    /* 2182 */ "glNormalFormatNV",
    /* 2183 */ "glColorFormatNV",
    /* 2184 */ "glIndexFormatNV",
    /* 2185 */ "glTexCoordFormatNV",
    /* 2186 */ "glEdgeFlagFormatNV",
    /* 2187 */ "glSecondaryColorFormatNV",
    /* 2188 */ "glFogCoordFormatNV",
    /* 2189 */ "glVertexAttribFormatNV",
    /* 2190 */ "glVertexAttribIFormatNV",
    /* 2191 */ "glGetIntegerui64i_vNV",
    /* 2192 */ "glAreProgramsResidentNV",
    /* 2193 */ "glBindProgramNV",
    /* 2194 */ "glDeleteProgramsNV",
    /* 2195 */ "glExecuteProgramNV",
    /* 2196 */ "glGenProgramsNV",
    /* 2197 */ "glGetProgramParameterdvNV",
    /* 2198 */ "glGetProgramParameterfvNV",
    /* 2199 */ "glGetProgramivNV",
    /* 2200 */ "glGetProgramStringNV",
    /* 2201 */ "glGetTrackMatrixivNV",
    /* 2202 */ "glGetVertexAttribdvNV",
    /* 2203 */ "glGetVertexAttribfvNV",
    /* 2204 */ "glGetVertexAttribivNV",
    /* 2205 */ "glGetVertexAttribPointervNV",
    /* 2206 */ "glIsProgramNV",
    /* 2207 */ "glLoadProgramNV",
    /* 2208 */ "glProgramParameter4dNV",
    /* 2209 */ "glProgramParameter4dvNV",
    /* 2210 */ "glProgramParameter4fNV",
    /* 2211 */ "glProgramParameter4fvNV",
    /* 2212 */ "glProgramParameters4dvNV",
    /* 2213 */ "glProgramParameters4fvNV",
    /* 2214 */ "glRequestResidentProgramsNV",
    /* 2215 */ "glTrackMatrixNV",
    /* 2216 */ "glVertexAttribPointerNV",
    /* 2217 */ "glVertexAttrib1dNV",
    /* 2218 */ "glVertexAttrib1dvNV",
    /* 2219 */ "glVertexAttrib1fNV",
    /* 2220 */ "glVertexAttrib1fvNV",
    /* 2221 */ "glVertexAttrib1sNV",
    /* 2222 */ "glVertexAttrib1svNV",
    /* 2223 */ "glVertexAttrib2dNV",
    /* 2224 */ "glVertexAttrib2dvNV",
    /* 2225 */ "glVertexAttrib2fNV",
    /* 2226 */ "glVertexAttrib2fvNV",
    /* 2227 */ "glVertexAttrib2sNV",
    /* 2228 */ "glVertexAttrib2svNV",
    /* 2229 */ "glVertexAttrib3dNV",
    /* 2230 */ "glVertexAttrib3dvNV",
    /* 2231 */ "glVertexAttrib3fNV",
    /* 2232 */ "glVertexAttrib3fvNV",
    /* 2233 */ "glVertexAttrib3sNV",
    /* 2234 */ "glVertexAttrib3svNV",
    /* 2235 */ "glVertexAttrib4dNV",
    /* 2236 */ "glVertexAttrib4dvNV",
    /* 2237 */ "glVertexAttrib4fNV",
    /* 2238 */ "glVertexAttrib4fvNV",
    /* 2239 */ "glVertexAttrib4sNV",
    /* 2240 */ "glVertexAttrib4svNV",
    /* 2241 */ "glVertexAttrib4ubNV",
    /* 2242 */ "glVertexAttrib4ubvNV",
    /* 2243 */ "glVertexAttribs1dvNV",
    /* 2244 */ "glVertexAttribs1fvNV",
    /* 2245 */ "glVertexAttribs1svNV",
    /* 2246 */ "glVertexAttribs2dvNV",
    /* 2247 */ "glVertexAttribs2fvNV",
    /* 2248 */ "glVertexAttribs2svNV",
    /* 2249 */ "glVertexAttribs3dvNV",
    /* 2250 */ "glVertexAttribs3fvNV",
    /* 2251 */ "glVertexAttribs3svNV",
    /* 2252 */ "glVertexAttribs4dvNV",
    /* 2253 */ "glVertexAttribs4fvNV",
    /* 2254 */ "glVertexAttribs4svNV",
    /* 2255 */ "glVertexAttribs4ubvNV",
    /* 2256 */ "glBeginVideoCaptureNV",
    /* 2257 */ "glBindVideoCaptureStreamBufferNV",
    /* 2258 */ "glBindVideoCaptureStreamTextureNV",
    /* 2259 */ "glEndVideoCaptureNV",
    /* 2260 */ "glGetVideoCaptureivNV",
    /* 2261 */ "glGetVideoCaptureStreamivNV",
    /* 2262 */ "glGetVideoCaptureStreamfvNV",
    /* 2263 */ "glGetVideoCaptureStreamdvNV",
    /* 2264 */ "glVideoCaptureNV",
    /* 2265 */ "glVideoCaptureStreamParameterivNV",
    /* 2266 */ "glVideoCaptureStreamParameterfvNV",
    /* 2267 */ "glVideoCaptureStreamParameterdvNV",
    /* 2268 */ "glViewportSwizzleNV",
    /* 2269 */ "glMultiTexCoord1bOES",
    /* 2270 */ "glMultiTexCoord1bvOES",
    /* 2271 */ "glMultiTexCoord2bOES",
    /* 2272 */ "glMultiTexCoord2bvOES",
    /* 2273 */ "glMultiTexCoord3bOES",
    /* 2274 */ "glMultiTexCoord3bvOES",
    /* 2275 */ "glMultiTexCoord4bOES",
    /* 2276 */ "glMultiTexCoord4bvOES",
    /* 2277 */ "glTexCoord1bOES",
    /* 2278 */ "glTexCoord1bvOES",
    /* 2279 */ "glTexCoord2bOES",
    /* 2280 */ "glTexCoord2bvOES",
    /* 2281 */ "glTexCoord3bOES",
    /* 2282 */ "glTexCoord3bvOES",
    /* 2283 */ "glTexCoord4bOES",
    /* 2284 */ "glTexCoord4bvOES",
    /* 2285 */ "glVertex2bOES",
    /* 2286 */ "glVertex2bvOES",
    /* 2287 */ "glVertex3bOES",
    /* 2288 */ "glVertex3bvOES",
    /* 2289 */ "glVertex4bOES",
    /* 2290 */ "glVertex4bvOES",
    /* 2291 */ "glAlphaFuncxOES",
    /* 2292 */ "glClearColorxOES",
    /* 2293 */ "glClearDepthxOES",
    /* 2294 */ "glClipPlanexOES",
    /* 2295 */ "glColor4xOES",
    /* 2296 */ "glDepthRangexOES",
    /* 2297 */ "glFogxOES",
    /* 2298 */ "glFogxvOES",
    /* 2299 */ "glFrustumxOES",
    /* 2300 */ "glGetClipPlanexOES",
    /* 2301 */ "glGetFixedvOES",
    /* 2302 */ "glGetTexEnvxvOES",
    /* 2303 */ "glGetTexParameterxvOES",
    /* 2304 */ "glLightModelxOES",
    /* 2305 */ "glLightModelxvOES",
    /* 2306 */ "glLightxOES",
    /* 2307 */ "glLightxvOES",
    /* 2308 */ "glLineWidthxOES",
    /* 2309 */ "glLoadMatrixxOES",
    /* 2310 */ "glMaterialxOES",
    /* 2311 */ "glMaterialxvOES",
    /* 2312 */ "glMultMatrixxOES",
    /* 2313 */ "glMultiTexCoord4xOES",
    /* 2314 */ "glNormal3xOES",
    /* 2315 */ "glOrthoxOES",
    /* 2316 */ "glPointParameterxvOES",
    /* 2317 */ "glPointSizexOES",
    /* 2318 */ "glPolygonOffsetxOES",
    /* 2319 */ "glRotatexOES",
    /* 2320 */ "glScalexOES",
    /* 2321 */ "glTexEnvxOES",
    /* 2322 */ "glTexEnvxvOES",
    /* 2323 */ "glTexParameterxOES",
    /* 2324 */ "glTexParameterxvOES",
    /* 2325 */ "glTranslatexOES",
    /* 2326 */ "glAccumxOES",
    /* 2327 */ "glBitmapxOES",
    /* 2328 */ "glBlendColorxOES",
    /* 2329 */ "glClearAccumxOES",
    /* 2330 */ "glColor3xOES",
    /* 2331 */ "glColor3xvOES",
    /* 2332 */ "glColor4xvOES",
    /* 2333 */ "glConvolutionParameterxOES",
    /* 2334 */ "glConvolutionParameterxvOES",
    /* 2335 */ "glEvalCoord1xOES",
    /* 2336 */ "glEvalCoord1xvOES",
    /* 2337 */ "glEvalCoord2xOES",
    /* 2338 */ "glEvalCoord2xvOES",
    /* 2339 */ "glFeedbackBufferxOES",
    /* 2340 */ "glGetConvolutionParameterxvOES",
    /* 2341 */ "glGetHistogramParameterxvOES",
    /* 2342 */ "glGetLightxOES",
    /* 2343 */ "glGetMapxvOES",
    /* 2344 */ "glGetMaterialxOES",
    /* 2345 */ "glGetPixelMapxv",
    /* 2346 */ "glGetTexGenxvOES",
    /* 2347 */ "glGetTexLevelParameterxvOES",
    /* 2348 */ "glIndexxOES",
    /* 2349 */ "glIndexxvOES",
    /* 2350 */ "glLoadTransposeMatrixxOES",
    /* 2351 */ "glMap1xOES",
    /* 2352 */ "glMap2xOES",
    /* 2353 */ "glMapGrid1xOES",
    /* 2354 */ "glMapGrid2xOES",
    /* 2355 */ "glMultTransposeMatrixxOES",
    /* 2356 */ "glMultiTexCoord1xOES",
    /* 2357 */ "glMultiTexCoord1xvOES",
    /* 2358 */ "glMultiTexCoord2xOES",
    /* 2359 */ "glMultiTexCoord2xvOES",
    /* 2360 */ "glMultiTexCoord3xOES",
    /* 2361 */ "glMultiTexCoord3xvOES",
    /* 2362 */ "glMultiTexCoord4xvOES",
    /* 2363 */ "glNormal3xvOES",
    /* 2364 */ "glPassThroughxOES",
    /* 2365 */ "glPixelMapx",
    /* 2366 */ "glPixelStorex",
    /* 2367 */ "glPixelTransferxOES",
    /* 2368 */ "glPixelZoomxOES",
    /* 2369 */ "glPrioritizeTexturesxOES",
    /* 2370 */ "glRasterPos2xOES",
    /* 2371 */ "glRasterPos2xvOES",
    /* 2372 */ "glRasterPos3xOES",
    /* 2373 */ "glRasterPos3xvOES",
    /* 2374 */ "glRasterPos4xOES",
    /* 2375 */ "glRasterPos4xvOES",
    /* 2376 */ "glRectxOES",
    /* 2377 */ "glRectxvOES",
    /* 2378 */ "glTexCoord1xOES",
    /* 2379 */ "glTexCoord1xvOES",
    /* 2380 */ "glTexCoord2xOES",
    /* 2381 */ "glTexCoord2xvOES",
    /* 2382 */ "glTexCoord3xOES",
    /* 2383 */ "glTexCoord3xvOES",
    /* 2384 */ "glTexCoord4xOES",
    /* 2385 */ "glTexCoord4xvOES",
    /* 2386 */ "glTexGenxOES",
    /* 2387 */ "glTexGenxvOES",
    /* 2388 */ "glVertex2xOES",
    /* 2389 */ "glVertex2xvOES",
    /* 2390 */ "glVertex3xOES",
    /* 2391 */ "glVertex3xvOES",
    /* 2392 */ "glVertex4xOES",
    /* 2393 */ "glVertex4xvOES",
    /* 2394 */ "glQueryMatrixxOES",
    /* 2395 */ "glClearDepthfOES",
    /* 2396 */ "glClipPlanefOES",
    /* 2397 */ "glDepthRangefOES",
    /* 2398 */ "glFrustumfOES",
    /* 2399 */ "glGetClipPlanefOES",
    /* 2400 */ "glOrthofOES",
    /* 2401 */ "glFramebufferTextureMultiviewOVR",
    /* 2402 */ "glNamedFramebufferTextureMultiviewOVR",
    /* 2403 */ "glHintPGI",
    /* 2404 */ "glDetailTexFuncSGIS",
    /* 2405 */ "glGetDetailTexFuncSGIS",
    /* 2406 */ "glFogFuncSGIS",
    /* 2407 */ "glGetFogFuncSGIS",
    /* 2408 */ "glSampleMaskSGIS",
    /* 2409 */ "glSamplePatternSGIS",
    /* 2410 */ "glPixelTexGenParameteriSGIS",
    /* 2411 */ "glPixelTexGenParameterivSGIS",
    /* 2412 */ "glPixelTexGenParameterfSGIS",
    /* 2413 */ "glPixelTexGenParameterfvSGIS",
    /* 2414 */ "glGetPixelTexGenParameterivSGIS",
    /* 2415 */ "glGetPixelTexGenParameterfvSGIS",
    /* 2416 */ "glPointParameterfSGIS",
    /* 2417 */ "glPointParameterfvSGIS",
    /* 2418 */ "glSharpenTexFuncSGIS",
    /* 2419 */ "glGetSharpenTexFuncSGIS",
    /* 2420 */ "glTexImage4DSGIS",
    /* 2421 */ "glTexSubImage4DSGIS",
    /* 2422 */ "glTextureColorMaskSGIS",
    /* 2423 */ "glGetTexFilterFuncSGIS",
    /* 2424 */ "glTexFilterFuncSGIS",
    /* 2425 */ "glAsyncMarkerSGIX",
    /* 2426 */ "glFinishAsyncSGIX",
    /* 2427 */ "glPollAsyncSGIX",
    /* 2428 */ "glGenAsyncMarkersSGIX",
    /* 2429 */ "glDeleteAsyncMarkersSGIX",
    /* 2430 */ "glIsAsyncMarkerSGIX",
    /* 2431 */ "glFlushRasterSGIX",
    /* 2432 */ "glFragmentColorMaterialSGIX",
    /* 2433 */ "glFragmentLightfSGIX",
    /* 2434 */ "glFragmentLightfvSGIX",
    /* 2435 */ "glFragmentLightiSGIX",
    /* 2436 */ "glFragmentLightivSGIX",
    /* 2437 */ "glFragmentLightModelfSGIX",
    /* 2438 */ "glFragmentLightModelfvSGIX",
    /* 2439 */ "glFragmentLightModeliSGIX",
    /* 2440 */ "glFragmentLightModelivSGIX",
    /* 2441 */ "glFragmentMaterialfSGIX",
    /* 2442 */ "glFragmentMaterialfvSGIX",
    /* 2443 */ "glFragmentMaterialiSGIX",
    /* 2444 */ "glFragmentMaterialivSGIX",
    /* 2445 */ "glGetFragmentLightfvSGIX",
    /* 2446 */ "glGetFragmentLightivSGIX",
    /* 2447 */ "glGetFragmentMaterialfvSGIX",
    /* 2448 */ "glGetFragmentMaterialivSGIX",
    /* 2449 */ "glLightEnviSGIX",
    /* 2450 */ "glFrameZoomSGIX",
    /* 2451 */ "glIglooInterfaceSGIX",
    /* 2452 */ "glGetInstrumentsSGIX",
    /* 2453 */ "glInstrumentsBufferSGIX",
    /* 2454 */ "glPollInstrumentsSGIX",
    /* 2455 */ "glReadInstrumentsSGIX",
    /* 2456 */ "glStartInstrumentsSGIX",
    /* 2457 */ "glStopInstrumentsSGIX",
    /* 2458 */ "glGetListParameterfvSGIX",
    /* 2459 */ "glGetListParameterivSGIX",
    /* 2460 */ "glListParameterfSGIX",
    /* 2461 */ "glListParameterfvSGIX",
    /* 2462 */ "glListParameteriSGIX",
    /* 2463 */ "glListParameterivSGIX",
    /* 2464 */ "glPixelTexGenSGIX",
    /* 2465 */ "glDeformationMap3dSGIX",
    /* 2466 */ "glDeformationMap3fSGIX",
    /* 2467 */ "glDeformSGIX",
    /* 2468 */ "glLoadIdentityDeformationMapSGIX",
    /* 2469 */ "glReferencePlaneSGIX",
    /* 2470 */ "glSpriteParameterfSGIX",
    /* 2471 */ "glSpriteParameterfvSGIX",
    /* 2472 */ "glSpriteParameteriSGIX",
    /* 2473 */ "glSpriteParameterivSGIX",
    /* 2474 */ "glTagSampleBufferSGIX",
    /* 2475 */ "glColorTableSGI",
    /* 2476 */ "glColorTableParameterfvSGI",
    /* 2477 */ "glColorTableParameterivSGI",
    /* 2478 */ "glCopyColorTableSGI",
    /* 2479 */ "glGetColorTableSGI",
    /* 2480 */ "glGetColorTableParameterfvSGI",
    /* 2481 */ "glGetColorTableParameterivSGI",
    /* 2482 */ "glFinishTextureSUNX",
    /* 2483 */ "glGlobalAlphaFactorbSUN",
    /* 2484 */ "glGlobalAlphaFactorsSUN",
    /* 2485 */ "glGlobalAlphaFactoriSUN",
    /* 2486 */ "glGlobalAlphaFactorfSUN",
    /* 2487 */ "glGlobalAlphaFactordSUN",
    /* 2488 */ "glGlobalAlphaFactorubSUN",
    /* 2489 */ "glGlobalAlphaFactorusSUN",
    /* 2490 */ "glGlobalAlphaFactoruiSUN",
    /* 2491 */ "glDrawMeshArraysSUN",
    /* 2492 */ "glReplacementCodeuiSUN",
    /* 2493 */ "glReplacementCodeusSUN",
    /* 2494 */ "glReplacementCodeubSUN",
    /* 2495 */ "glReplacementCodeuivSUN",
    /* 2496 */ "glReplacementCodeusvSUN",
    /* 2497 */ "glReplacementCodeubvSUN",
    /* 2498 */ "glReplacementCodePointerSUN",
    /* 2499 */ "glColor4ubVertex2fSUN",
    /* 2500 */ "glColor4ubVertex2fvSUN",
    /* 2501 */ "glColor4ubVertex3fSUN",
    /* 2502 */ "glColor4ubVertex3fvSUN",
    /* 2503 */ "glColor3fVertex3fSUN",
    /* 2504 */ "glColor3fVertex3fvSUN",
    /* 2505 */ "glNormal3fVertex3fSUN",
    /* 2506 */ "glNormal3fVertex3fvSUN",
    /* 2507 */ "glColor4fNormal3fVertex3fSUN",
    /* 2508 */ "glColor4fNormal3fVertex3fvSUN",
    /* 2509 */ "glTexCoord2fVertex3fSUN",
    /* 2510 */ "glTexCoord2fVertex3fvSUN",
    /* 2511 */ "glTexCoord4fVertex4fSUN",
    /* 2512 */ "glTexCoord4fVertex4fvSUN",
    /* 2513 */ "glTexCoord2fColor4ubVertex3fSUN",
    /* 2514 */ "glTexCoord2fColor4ubVertex3fvSUN",
    /* 2515 */ "glTexCoord2fColor3fVertex3fSUN",
    /* 2516 */ "glTexCoord2fColor3fVertex3fvSUN",
    /* 2517 */ "glTexCoord2fNormal3fVertex3fSUN",
    /* 2518 */ "glTexCoord2fNormal3fVertex3fvSUN",
    /* 2519 */ "glTexCoord2fColor4fNormal3fVertex3fSUN",
    /* 2520 */ "glTexCoord2fColor4fNormal3fVertex3fvSUN",
    /* 2521 */ "glTexCoord4fColor4fNormal3fVertex4fSUN",
    /* 2522 */ "glTexCoord4fColor4fNormal3fVertex4fvSUN",
    /* 2523 */ "glReplacementCodeuiVertex3fSUN",
    /* 2524 */ "glReplacementCodeuiVertex3fvSUN",
    /* 2525 */ "glReplacementCodeuiColor4ubVertex3fSUN",
    /* 2526 */ "glReplacementCodeuiColor4ubVertex3fvSUN",
    /* 2527 */ "glReplacementCodeuiColor3fVertex3fSUN",
    /* 2528 */ "glReplacementCodeuiColor3fVertex3fvSUN",
    /* 2529 */ "glReplacementCodeuiNormal3fVertex3fSUN",
    /* 2530 */ "glReplacementCodeuiNormal3fVertex3fvSUN",
    /* 2531 */ "glReplacementCodeuiColor4fNormal3fVertex3fSUN",
    /* 2532 */ "glReplacementCodeuiColor4fNormal3fVertex3fvSUN",
    /* 2533 */ "glReplacementCodeuiTexCoord2fVertex3fSUN",
    /* 2534 */ "glReplacementCodeuiTexCoord2fVertex3fvSUN",
    /* 2535 */ "glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN",
    /* 2536 */ "glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN",
    /* 2537 */ "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN",
    /* 2538 */ "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN",
    /* 2539 */ "glTexImage2DExternalANGLE",
    /* 2540 */ "glInvalidateTextureANGLE",
    /* 2541 */ "glTexStorageMemFlags2DANGLE",
    /* 2542 */ "glTexStorageMemFlags2DMultisampleANGLE",
    /* 2543 */ "glTexStorageMemFlags3DANGLE",
    /* 2544 */ "glTexStorageMemFlags3DMultisampleANGLE",
    /* 2545 */ "glImportMemoryZirconHandleANGLE",
    /* 2546 */ "glImportSemaphoreZirconHandleANGLE",
    /* 2547 */ "glBlendBarrier",
    /* 2548 */ "glPrimitiveBoundingBox",
    /* 2549 */ "glBlitFramebufferANGLE",
    /* 2550 */ "glRenderbufferStorageMultisampleANGLE",
    /* 2551 */ "glDrawArraysInstancedANGLE",
    /* 2552 */ "glDrawElementsInstancedANGLE",
    /* 2553 */ "glVertexAttribDivisorANGLE",
    /* 2554 */ "glGetTranslatedShaderSourceANGLE",
    /* 2555 */ "glCopyTextureLevelsAPPLE",
    /* 2556 */ "glRenderbufferStorageMultisampleAPPLE",
    /* 2557 */ "glResolveMultisampleFramebufferAPPLE",
    /* 2558 */ "glFenceSyncAPPLE",
    /* 2559 */ "glIsSyncAPPLE",
    /* 2560 */ "glDeleteSyncAPPLE",
    /* 2561 */ "glClientWaitSyncAPPLE",
    /* 2562 */ "glWaitSyncAPPLE",
    /* 2563 */ "glGetInteger64vAPPLE",
    /* 2564 */ "glGetSyncivAPPLE",
    /* 2565 */ "glMaxActiveShaderCoresARM",
    /* 2566 */ "glDrawArraysInstancedBaseInstanceEXT",
    /* 2567 */ "glDrawElementsInstancedBaseInstanceEXT",
    /* 2568 */ "glDrawElementsInstancedBaseVertexBaseInstanceEXT",
    /* 2569 */ "glBindFragDataLocationIndexedEXT",
    /* 2570 */ "glGetProgramResourceLocationIndexEXT",
    /* 2571 */ "glGetFragDataIndexEXT",
    /* 2572 */ "glBufferStorageEXT",
    /* 2573 */ "glClearTexImageEXT",
    /* 2574 */ "glClearTexSubImageEXT",
    /* 2575 */ "glClipControlEXT",
    /* 2576 */ "glCopyImageSubDataEXT",
    /* 2577 */ "glDiscardFramebufferEXT",
    /* 2578 */ "glGenQueriesEXT",
    /* 2579 */ "glDeleteQueriesEXT",
    /* 2580 */ "glIsQueryEXT",
    /* 2581 */ "glBeginQueryEXT",
    /* 2582 */ "glEndQueryEXT",
    /* 2583 */ "glQueryCounterEXT",
    /* 2584 */ "glGetQueryivEXT",
    /* 2585 */ "glGetQueryObjectivEXT",
    /* 2586 */ "glGetQueryObjectuivEXT",
    /* 2587 */ "glGetInteger64vEXT",
    /* 2588 */ "glDrawBuffersEXT",
    /* 2589 */ "glEnableiEXT",
    /* 2590 */ "glDisableiEXT",
    /* 2591 */ "glBlendEquationiEXT",
    /* 2592 */ "glBlendEquationSeparateiEXT",
    /* 2593 */ "glBlendFunciEXT",
    /* 2594 */ "glBlendFuncSeparateiEXT",
    /* 2595 */ "glColorMaskiEXT",
    /* 2596 */ "glIsEnablediEXT",
    /* 2597 */ "glDrawElementsBaseVertexEXT",
    /* 2598 */ "glDrawRangeElementsBaseVertexEXT",
    /* 2599 */ "glDrawElementsInstancedBaseVertexEXT",
    /* 2600 */ "glMultiDrawElementsBaseVertexEXT",
    /* 2601 */ "glDrawTransformFeedbackEXT",
    /* 2602 */ "glDrawTransformFeedbackInstancedEXT",
    /* 2603 */ "glVertexAttribDivisorEXT",
    /* 2604 */ "glMapBufferRangeEXT",
    /* 2605 */ "glFlushMappedBufferRangeEXT",
    /* 2606 */ "glMultiDrawArraysIndirectEXT",
    /* 2607 */ "glMultiDrawElementsIndirectEXT",
    /* 2608 */ "glFramebufferTexture2DMultisampleEXT",
    /* 2609 */ "glReadBufferIndexedEXT",
    /* 2610 */ "glDrawBuffersIndexedEXT",
    /* 2611 */ "glGetIntegeri_vEXT",
    /* 2612 */ "glPrimitiveBoundingBoxEXT",
    /* 2613 */ "glGetGraphicsResetStatusEXT",
    /* 2614 */ "glReadnPixelsEXT",
    /* 2615 */ "glGetnUniformfvEXT",
    /* 2616 */ "glGetnUniformivEXT",
    /* 2617 */ "glActiveShaderProgramEXT",
    /* 2618 */ "glBindProgramPipelineEXT",
    /* 2619 */ "glCreateShaderProgramvEXT",
    /* 2620 */ "glDeleteProgramPipelinesEXT",
    /* 2621 */ "glGenProgramPipelinesEXT",
    /* 2622 */ "glGetProgramPipelineInfoLogEXT",
    /* 2623 */ "glGetProgramPipelineivEXT",
    /* 2624 */ "glIsProgramPipelineEXT",
    /* 2625 */ "glUseProgramStagesEXT",
    /* 2626 */ "glValidateProgramPipelineEXT",
    /* 2627 */ "glFramebufferPixelLocalStorageSizeEXT",
    /* 2628 */ "glGetFramebufferPixelLocalStorageSizeEXT",
    /* 2629 */ "glClearPixelLocalStorageuiEXT",
    /* 2630 */ "glTexPageCommitmentEXT",
    /* 2631 */ "glPatchParameteriEXT",
    /* 2632 */ "glSamplerParameterIivEXT",
    /* 2633 */ "glSamplerParameterIuivEXT",
    /* 2634 */ "glGetSamplerParameterIivEXT",
    /* 2635 */ "glGetSamplerParameterIuivEXT",
    /* 2636 */ "glTexBufferRangeEXT",
    /* 2637 */ "glTexStorageAttribs2DEXT",
    /* 2638 */ "glTexStorageAttribs3DEXT",
    /* 2639 */ "glTextureViewEXT",
    /* 2640 */ "glGetTextureHandleIMG",
    /* 2641 */ "glGetTextureSamplerHandleIMG",
    /* 2642 */ "glUniformHandleui64IMG",
    /* 2643 */ "glUniformHandleui64vIMG",
    /* 2644 */ "glProgramUniformHandleui64IMG",
    /* 2645 */ "glProgramUniformHandleui64vIMG",
    /* 2646 */ "glFramebufferTexture2DDownsampleIMG",
    /* 2647 */ "glFramebufferTextureLayerDownsampleIMG",
    /* 2648 */ "glRenderbufferStorageMultisampleIMG",
    /* 2649 */ "glFramebufferTexture2DMultisampleIMG",
    /* 2650 */ "glDebugMessageControlKHR",
    /* 2651 */ "glDebugMessageInsertKHR",
    /* 2652 */ "glDebugMessageCallbackKHR",
    /* 2653 */ "glGetDebugMessageLogKHR",
    /* 2654 */ "glPushDebugGroupKHR",
    /* 2655 */ "glPopDebugGroupKHR",
    /* 2656 */ "glObjectLabelKHR",
    /* 2657 */ "glGetObjectLabelKHR",
    /* 2658 */ "glObjectPtrLabelKHR",
    /* 2659 */ "glGetObjectPtrLabelKHR",
    /* 2660 */ "glGetPointervKHR",
    /* 2661 */ "glGetGraphicsResetStatusKHR",
    /* 2662 */ "glReadnPixelsKHR",
    /* 2663 */ "glGetnUniformfvKHR",
    /* 2664 */ "glGetnUniformivKHR",
    /* 2665 */ "glGetnUniformuivKHR",
    /* 2666 */ "glCopyBufferSubDataNV",
    /* 2667 */ "glCoverageMaskNV",
    /* 2668 */ "glCoverageOperationNV",
    /* 2669 */ "glDrawBuffersNV",
    /* 2670 */ "glDrawArraysInstancedNV",
    /* 2671 */ "glDrawElementsInstancedNV",
    /* 2672 */ "glBlitFramebufferNV",
    /* 2673 */ "glRenderbufferStorageMultisampleNV",
    /* 2674 */ "glVertexAttribDivisorNV",
    /* 2675 */ "glUniformMatrix2x3fvNV",
    /* 2676 */ "glUniformMatrix3x2fvNV",
    /* 2677 */ "glUniformMatrix2x4fvNV",
    /* 2678 */ "glUniformMatrix4x2fvNV",
    /* 2679 */ "glUniformMatrix3x4fvNV",
    /* 2680 */ "glUniformMatrix4x3fvNV",
    /* 2681 */ "glPolygonModeNV",
    /* 2682 */ "glReadBufferNV",
    /* 2683 */ "glViewportArrayvNV",
    /* 2684 */ "glViewportIndexedfNV",
    /* 2685 */ "glViewportIndexedfvNV",
    /* 2686 */ "glScissorArrayvNV",
    /* 2687 */ "glScissorIndexedNV",
    /* 2688 */ "glScissorIndexedvNV",
    /* 2689 */ "glDepthRangeArrayfvNV",
    /* 2690 */ "glDepthRangeIndexedfNV",
    /* 2691 */ "glGetFloati_vNV",
    /* 2692 */ "glEnableiNV",
    /* 2693 */ "glDisableiNV",
    /* 2694 */ "glIsEnablediNV",
    /* 2695 */ "glEGLImageTargetTexture2DOES",
    /* 2696 */ "glEGLImageTargetRenderbufferStorageOES",
    /* 2697 */ "glCopyImageSubDataOES",
    /* 2698 */ "glEnableiOES",
    /* 2699 */ "glDisableiOES",
    /* 2700 */ "glBlendEquationiOES",
    /* 2701 */ "glBlendEquationSeparateiOES",
    /* 2702 */ "glBlendFunciOES",
    /* 2703 */ "glBlendFuncSeparateiOES",
    /* 2704 */ "glColorMaskiOES",
    /* 2705 */ "glIsEnablediOES",
    /* 2706 */ "glDrawElementsBaseVertexOES",
    /* 2707 */ "glDrawRangeElementsBaseVertexOES",
    /* 2708 */ "glDrawElementsInstancedBaseVertexOES",
    /* 2709 */ "glFramebufferTextureOES",
    /* 2710 */ "glGetProgramBinaryOES",
    /* 2711 */ "glProgramBinaryOES",
    /* 2712 */ "glMapBufferOES",
    /* 2713 */ "glUnmapBufferOES",
    /* 2714 */ "glGetBufferPointervOES",
    /* 2715 */ "glPrimitiveBoundingBoxOES",
    /* 2716 */ "glMinSampleShadingOES",
    /* 2717 */ "glPatchParameteriOES",
    /* 2718 */ "glTexImage3DOES",
    /* 2719 */ "glTexSubImage3DOES",
    /* 2720 */ "glCopyTexSubImage3DOES",
    /* 2721 */ "glCompressedTexImage3DOES",
    /* 2722 */ "glCompressedTexSubImage3DOES",
    /* 2723 */ "glFramebufferTexture3DOES",
    /* 2724 */ "glTexParameterIivOES",
    /* 2725 */ "glTexParameterIuivOES",
    /* 2726 */ "glGetTexParameterIivOES",
    /* 2727 */ "glGetTexParameterIuivOES",
    /* 2728 */ "glSamplerParameterIivOES",
    /* 2729 */ "glSamplerParameterIuivOES",
    /* 2730 */ "glGetSamplerParameterIivOES",
    /* 2731 */ "glGetSamplerParameterIuivOES",
    /* 2732 */ "glTexBufferOES",
    /* 2733 */ "glTexBufferRangeOES",
    /* 2734 */ "glTexStorage3DMultisampleOES",
    /* 2735 */ "glTextureViewOES",
    /* 2736 */ "glBindVertexArrayOES",
    /* 2737 */ "glDeleteVertexArraysOES",
    /* 2738 */ "glGenVertexArraysOES",
    /* 2739 */ "glIsVertexArrayOES",
    /* 2740 */ "glViewportArrayvOES",
    /* 2741 */ "glViewportIndexedfOES",
    /* 2742 */ "glViewportIndexedfvOES",
    /* 2743 */ "glScissorArrayvOES",
    /* 2744 */ "glScissorIndexedOES",
    /* 2745 */ "glScissorIndexedvOES",
    /* 2746 */ "glDepthRangeArrayfvOES",
    /* 2747 */ "glDepthRangeIndexedfOES",
    /* 2748 */ "glGetFloati_vOES",
    /* 2749 */ "glFramebufferTextureMultisampleMultiviewOVR",
    /* 2750 */ "glAlphaFuncQCOM",
    /* 2751 */ "glGetDriverControlsQCOM",
    /* 2752 */ "glGetDriverControlStringQCOM",
    /* 2753 */ "glEnableDriverControlQCOM",
    /* 2754 */ "glDisableDriverControlQCOM",
    /* 2755 */ "glExtGetTexturesQCOM",
    /* 2756 */ "glExtGetBuffersQCOM",
    /* 2757 */ "glExtGetRenderbuffersQCOM",
    /* 2758 */ "glExtGetFramebuffersQCOM",
    /* 2759 */ "glExtGetTexLevelParameterivQCOM",
    /* 2760 */ "glExtTexObjectStateOverrideiQCOM",
    /* 2761 */ "glExtGetTexSubImageQCOM",
    /* 2762 */ "glExtGetBufferPointervQCOM",
    /* 2763 */ "glExtGetShadersQCOM",
    /* 2764 */ "glExtGetProgramsQCOM",
    /* 2765 */ "glExtIsProgramBinaryQCOM",
    /* 2766 */ "glExtGetProgramBinarySourceQCOM",
    /* 2767 */ "glFramebufferFoveationConfigQCOM",
    /* 2768 */ "glFramebufferFoveationParametersQCOM",
    /* 2769 */ "glTexEstimateMotionQCOM",
    /* 2770 */ "glTexEstimateMotionRegionsQCOM",
    /* 2771 */ "glExtrapolateTex2DQCOM",
    /* 2772 */ "glTextureFoveationParametersQCOM",
    /* 2773 */ "glFramebufferFetchBarrierQCOM",
    /* 2774 */ "glShadingRateQCOM",
    /* 2775 */ "glStartTilingQCOM",
    /* 2776 */ "glEndTilingQCOM",
    /* 2777 */ "glBindUniformLocationCHROMIUM",
    /* 2778 */ "glCoverageModulationCHROMIUM",
    /* 2779 */ "glCopyTextureCHROMIUM",
    /* 2780 */ "glCopySubTextureCHROMIUM",
    /* 2781 */ "glCompressedCopyTextureCHROMIUM",
    /* 2782 */ "glRequestExtensionANGLE",
    /* 2783 */ "glDisableExtensionANGLE",
    /* 2784 */ "glAcquireTexturesANGLE",
    /* 2785 */ "glReleaseTexturesANGLE",
    /* 2786 */ "glGetBooleanvRobustANGLE",
    /* 2787 */ "glGetBufferParameterivRobustANGLE",
    /* 2788 */ "glGetBufferParameteri64vRobustANGLE",
    /* 2789 */ "glGetFloatvRobustANGLE",
    /* 2790 */ "glGetFramebufferAttachmentParameterivRobustANGLE",
    /* 2791 */ "glGetIntegervRobustANGLE",
    /* 2792 */ "glGetProgramivRobustANGLE",
    /* 2793 */ "glGetRenderbufferParameterivRobustANGLE",
    /* 2794 */ "glGetShaderivRobustANGLE",
    /* 2795 */ "glGetTexParameterfvRobustANGLE",
    /* 2796 */ "glGetTexParameterivRobustANGLE",
    /* 2797 */ "glGetUniformfvRobustANGLE",
    /* 2798 */ "glGetUniformivRobustANGLE",
    /* 2799 */ "glGetVertexAttribfvRobustANGLE",
    /* 2800 */ "glGetVertexAttribivRobustANGLE",
    /* 2801 */ "glGetVertexAttribPointervRobustANGLE",
    /* 2802 */ "glReadPixelsRobustANGLE",
    /* 2803 */ "glTexImage2DRobustANGLE",
    /* 2804 */ "glTexParameterfvRobustANGLE",
    /* 2805 */ "glTexParameterivRobustANGLE",
    /* 2806 */ "glTexSubImage2DRobustANGLE",
    /* 2807 */ "glTexImage3DRobustANGLE",
    /* 2808 */ "glTexSubImage3DRobustANGLE",
    /* 2809 */ "glCompressedTexImage2DRobustANGLE",
    /* 2810 */ "glCompressedTexSubImage2DRobustANGLE",
    /* 2811 */ "glCompressedTexImage3DRobustANGLE",
    /* 2812 */ "glCompressedTexSubImage3DRobustANGLE",
    /* 2813 */ "glGetQueryivRobustANGLE",
    /* 2814 */ "glGetQueryObjectuivRobustANGLE",
    /* 2815 */ "glGetBufferPointervRobustANGLE",
    /* 2816 */ "glGetIntegeri_vRobustANGLE",
    /* 2817 */ "glGetInternalformativRobustANGLE",
    /* 2818 */ "glGetVertexAttribIivRobustANGLE",
    /* 2819 */ "glGetVertexAttribIuivRobustANGLE",
    /* 2820 */ "glGetUniformuivRobustANGLE",
    /* 2821 */ "glGetActiveUniformBlockivRobustANGLE",
    /* 2822 */ "glGetInteger64vRobustANGLE",
    /* 2823 */ "glGetInteger64i_vRobustANGLE",
    /* 2824 */ "glSamplerParameterivRobustANGLE",
    /* 2825 */ "glSamplerParameterfvRobustANGLE",
    /* 2826 */ "glGetSamplerParameterivRobustANGLE",
    /* 2827 */ "glGetSamplerParameterfvRobustANGLE",
    /* 2828 */ "glGetMultisamplefvRobustANGLE",
    /* 2829 */ "glGetTexLevelParameterivRobustANGLE",
    /* 2830 */ "glGetTexLevelParameterfvRobustANGLE",
    /* 2831 */ "glGetQueryObjectivRobustANGLE",
    /* 2832 */ "glGetQueryObjecti64vRobustANGLE",
    /* 2833 */ "glGetQueryObjectui64vRobustANGLE",
    /* 2834 */ "glGetFramebufferPixelLocalStorageParameterfvRobustANGLE",
    /* 2835 */ "glGetFramebufferPixelLocalStorageParameterivRobustANGLE",
    /* 2836 */ "glGetFramebufferPixelLocalStorageParameteruivRobustANGLE",
    /* 2837 */ "glCopyTexture3DANGLE",
    /* 2838 */ "glCopySubTexture3DANGLE",
    /* 2839 */ "glTexStorage2DMultisampleANGLE",
    /* 2840 */ "glGetMultisamplefvANGLE",
    /* 2841 */ "glSampleMaskiANGLE",
    /* 2842 */ "glMultiDrawArraysANGLE",
    /* 2843 */ "glMultiDrawArraysInstancedANGLE",
    /* 2844 */ "glMultiDrawElementsANGLE",
    /* 2845 */ "glMultiDrawElementsInstancedANGLE",
    /* 2846 */ "glDrawArraysInstancedBaseInstanceANGLE",
    /* 2847 */ "glDrawElementsInstancedBaseVertexBaseInstanceANGLE",
    /* 2848 */ "glMultiDrawArraysInstancedBaseInstanceANGLE",
    /* 2849 */ "glMultiDrawElementsInstancedBaseVertexBaseInstanceANGLE",
    /* 2850 */ "glPolygonModeANGLE",
    /* 2851 */ "glProvokingVertexANGLE",
    /* 2852 */ "glLoseContextCHROMIUM",
    /* 2853 */ "glGetTexImageANGLE",
    /* 2854 */ "glGetCompressedTexImageANGLE",
    /* 2855 */ "glGetRenderbufferImageANGLE",
    /* 2856 */ "glGetTexLevelParameterfvANGLE",
    /* 2857 */ "glGetTexLevelParameterivANGLE",
    /* 2858 */ "glFramebufferMemorylessPixelLocalStorageANGLE",
    /* 2859 */ "glFramebufferTexturePixelLocalStorageANGLE",
    /* 2860 */ "glFramebufferPixelLocalClearValuefvANGLE",
    /* 2861 */ "glFramebufferPixelLocalClearValueivANGLE",
    /* 2862 */ "glFramebufferPixelLocalClearValueuivANGLE",
    /* 2863 */ "glBeginPixelLocalStorageANGLE",
    /* 2864 */ "glEndPixelLocalStorageANGLE",
    /* 2865 */ "glEndPixelLocalStorageImplicitANGLE",
    /* 2866 */ "glPixelLocalStorageBarrierANGLE",
    /* 2867 */ "glFramebufferPixelLocalStorageInterruptANGLE",
    /* 2868 */ "glFramebufferPixelLocalStorageRestoreANGLE",
    /* 2869 */ "glGetFramebufferPixelLocalStorageParameterfvANGLE",
    /* 2870 */ "glGetFramebufferPixelLocalStorageParameterivANGLE",
    /* 2871 */ "glGetFramebufferPixelLocalStorageParameteruivANGLE",
    /* 2872 */ "glLogicOpANGLE",
    /* 2873 */ "glBlobCacheCallbacksANGLE",
    /* 2874 */ "glGetPointervANGLE"
};

static const GladPfnRange_t GLAD_GL_feature_pfn_ranges[] = {
    {    0,    0,   48 }, /* GL_VERSION_1_0 */
    {    1,   48,   14 }, /* GL_VERSION_1_1 */
    {    2,   62,    4 }, /* GL_VERSION_1_2 */
    {    3,   66,    9 }, /* GL_VERSION_1_3 */
    {    4,   75,    9 }, /* GL_VERSION_1_4 */
    {    5,   84,   19 }, /* GL_VERSION_1_5 */
    {    6,  103,   93 }, /* GL_VERSION_2_0 */
    {    7,  196,    6 }, /* GL_VERSION_2_1 */
    {    8,  202,   84 }, /* GL_VERSION_3_0 */
    {    9,  204,    1 }, /* GL_VERSION_3_1 */
    {    9,  210,    2 }, /* GL_VERSION_3_1 */
    {    9,  286,   12 }, /* GL_VERSION_3_1 */
    {   10,  298,   19 }, /* GL_VERSION_3_2 */
    {   11,  317,   28 }, /* GL_VERSION_3_3 */
    {   12,  345,   46 }, /* GL_VERSION_4_0 */
    {   13,  391,   88 }, /* GL_VERSION_4_1 */
    {   14,  479,   12 }, /* GL_VERSION_4_2 */
    {   15,   50,    1 }, /* GL_VERSION_4_3 */
    {   15,  491,   43 }, /* GL_VERSION_4_3 */
    {   16,  534,    9 }, /* GL_VERSION_4_4 */
    {   17,  543,  110 }, /* GL_VERSION_4_5 */
    {   18,  653,    4 }, /* GL_VERSION_4_6 */
    {   19,    0,    4 }, /* GL_ES_VERSION_2_0 */
    {   19,    6,    5 }, /* GL_ES_VERSION_2_0 */
    {   19,   12,    1 }, /* GL_ES_VERSION_2_0 */
    {   19,   14,    3 }, /* GL_ES_VERSION_2_0 */
    {   19,   18,    8 }, /* GL_ES_VERSION_2_0 */
    {   19,   27,    3 }, /* GL_ES_VERSION_2_0 */
    {   19,   31,    1 }, /* GL_ES_VERSION_2_0 */
    {   19,   33,    2 }, /* GL_ES_VERSION_2_0 */
    {   19,   36,    4 }, /* GL_ES_VERSION_2_0 */
    {   19,   41,    2 }, /* GL_ES_VERSION_2_0 */
    {   19,   45,    1 }, /* GL_ES_VERSION_2_0 */
    {   19,   47,    3 }, /* GL_ES_VERSION_2_0 */
    {   19,   51,    1 }, /* GL_ES_VERSION_2_0 */
    {   19,   53,    1 }, /* GL_ES_VERSION_2_0 */
    {   19,   55,    1 }, /* GL_ES_VERSION_2_0 */
    {   19,   57,    5 }, /* GL_ES_VERSION_2_0 */
    {   19,   66,    2 }, /* GL_ES_VERSION_2_0 */
    {   19,   69,    1 }, /* GL_ES_VERSION_2_0 */
    {   19,   72,    1 }, /* GL_ES_VERSION_2_0 */
    {   19,   75,    1 }, /* GL_ES_VERSION_2_0 */
    {   19,   82,    2 }, /* GL_ES_VERSION_2_0 */
    {   19,   92,    6 }, /* GL_ES_VERSION_2_0 */
    {   19,  101,    1 }, /* GL_ES_VERSION_2_0 */
    {   19,  103,    1 }, /* GL_ES_VERSION_2_0 */
    {   19,  105,   25 }, /* GL_ES_VERSION_2_0 */
    {   19,  131,   28 }, /* GL_ES_VERSION_2_0 */
    {   19,  161,    2 }, /* GL_ES_VERSION_2_0 */
    {   19,  167,    2 }, /* GL_ES_VERSION_2_0 */
    {   19,  173,    2 }, /* GL_ES_VERSION_2_0 */
    {   19,  187,    2 }, /* GL_ES_VERSION_2_0 */
    {   19,  195,    1 }, /* GL_ES_VERSION_2_0 */
    {   19,  260,   11 }, /* GL_ES_VERSION_2_0 */
    {   19,  272,    1 }, /* GL_ES_VERSION_2_0 */
    {   19,  274,    3 }, /* GL_ES_VERSION_2_0 */
    {   19,  391,    5 }, /* GL_ES_VERSION_2_0 */
    {   20,   32,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,   62,    4 }, /* GL_ES_VERSION_3_0 */
    {   20,   68,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,   71,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,   84,    6 }, /* GL_ES_VERSION_3_0 */
    {   20,   91,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,  100,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,  102,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,  104,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,  196,    6 }, /* GL_ES_VERSION_3_0 */
    {   20,  204,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,  208,    6 }, /* GL_ES_VERSION_3_0 */
    {   20,  217,    3 }, /* GL_ES_VERSION_3_0 */
    {   20,  223,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,  227,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,  231,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,  235,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,  240,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,  242,    9 }, /* GL_ES_VERSION_3_0 */
    {   20,  255,    5 }, /* GL_ES_VERSION_3_0 */
    {   20,  277,   11 }, /* GL_ES_VERSION_3_0 */
    {   20,  290,    3 }, /* GL_ES_VERSION_3_0 */
    {   20,  294,    4 }, /* GL_ES_VERSION_3_0 */
    {   20,  303,    9 }, /* GL_ES_VERSION_3_0 */
    {   20,  319,    8 }, /* GL_ES_VERSION_3_0 */
    {   20,  329,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,  331,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,  336,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,  380,    6 }, /* GL_ES_VERSION_3_0 */
    {   20,  396,    3 }, /* GL_ES_VERSION_3_0 */
    {   20,  482,    1 }, /* GL_ES_VERSION_3_0 */
    {   20,  487,    2 }, /* GL_ES_VERSION_3_0 */
    {   20,  503,    2 }, /* GL_ES_VERSION_3_0 */
    {   21,   43,    2 }, /* GL_ES_VERSION_3_1 */
    {   21,  203,    1 }, /* GL_ES_VERSION_3_1 */
    {   21,  315,    2 }, /* GL_ES_VERSION_3_1 */
    {   21,  350,    2 }, /* GL_ES_VERSION_3_1 */
    {   21,  399,   12 }, /* GL_ES_VERSION_3_1 */
    {   21,  413,    6 }, /* GL_ES_VERSION_3_1 */
    {   21,  421,    6 }, /* GL_ES_VERSION_3_1 */
    {   21,  429,    6 }, /* GL_ES_VERSION_3_1 */
    {   21,  437,    5 }, /* GL_ES_VERSION_3_1 */
    {   21,  445,    6 }, /* GL_ES_VERSION_3_1 */
    {   21,  457,    2 }, /* GL_ES_VERSION_3_1 */
    {   21,  484,    2 }, /* GL_ES_VERSION_3_1 */
    {   21,  493,    2 }, /* GL_ES_VERSION_3_1 */
    {   21,  496,    2 }, /* GL_ES_VERSION_3_1 */
    {   21,  507,    5 }, /* GL_ES_VERSION_3_1 */
    {   21,  515,    1 }, /* GL_ES_VERSION_3_1 */
    {   21,  518,    3 }, /* GL_ES_VERSION_3_1 */
    {   21,  522,    2 }, /* GL_ES_VERSION_3_1 */
    {   21,  641,    1 }, /* GL_ES_VERSION_3_1 */
    {   22,   50,    1 }, /* GL_ES_VERSION_3_2 */
    {   22,  202,    1 }, /* GL_ES_VERSION_3_2 */
    {   22,  205,    3 }, /* GL_ES_VERSION_3_2 */
    {   22,  251,    4 }, /* GL_ES_VERSION_3_2 */
    {   22,  288,    1 }, /* GL_ES_VERSION_3_2 */
    {   22,  298,    3 }, /* GL_ES_VERSION_3_2 */
    {   22,  312,    1 }, /* GL_ES_VERSION_3_2 */
    {   22,  327,    2 }, /* GL_ES_VERSION_3_2 */
    {   22,  330,    1 }, /* GL_ES_VERSION_3_2 */
    {   22,  332,    1 }, /* GL_ES_VERSION_3_2 */
    {   22,  345,    5 }, /* GL_ES_VERSION_3_2 */
    {   22,  378,    1 }, /* GL_ES_VERSION_3_2 */
    {   22,  495,    1 }, /* GL_ES_VERSION_3_2 */
    {   22,  514,    1 }, /* GL_ES_VERSION_3_2 */
    {   22,  516,    1 }, /* GL_ES_VERSION_3_2 */
    {   22,  524,   10 }, /* GL_ES_VERSION_3_2 */
    {   22,  644,    1 }, /* GL_ES_VERSION_3_2 */
    {   22,  648,    4 }, /* GL_ES_VERSION_3_2 */
    {   22, 2547,    2 }, /* GL_ES_VERSION_3_2 */
};

static const GladPfnRange_t GLAD_gl_ext_pfn_ranges[] = {
    {    1,  657,    1 }, /* GL_3DFX_tbuffer */
    {    7,  658,    4 }, /* GL_AMD_debug_output */
    {    9,  662,    4 }, /* GL_AMD_draw_buffers_blend */
    {   10,  666,    2 }, /* GL_AMD_framebuffer_multisample_advanced */
    {   11,  668,    4 }, /* GL_AMD_framebuffer_sample_positions */
    {   15,  672,   34 }, /* GL_AMD_gpu_shader_int64 */
    {   16,  706,    1 }, /* GL_AMD_interleaved_elements */
    {   17,  707,    2 }, /* GL_AMD_multi_draw_indirect */
    {   18,  709,    3 }, /* GL_AMD_name_gen_delete */
    {   19,  712,    1 }, /* GL_AMD_occlusion_query_event */
    {   20,  713,   11 }, /* GL_AMD_performance_monitor */
    {   24,  724,    1 }, /* GL_AMD_sample_positions */
    {   34,  725,    2 }, /* GL_AMD_sparse_texture */
    {   35,  727,    1 }, /* GL_AMD_stencil_operation_extended */
    {   41,  728,    2 }, /* GL_AMD_vertex_shader_tessellator */
    {   58, 2541,    4 }, /* GL_ANGLE_memory_object_flags */
    {   59, 2545,    1 }, /* GL_ANGLE_memory_object_fuchsia */
    {   74, 2546,    1 }, /* GL_ANGLE_semaphore_fuchsia */
    {   81, 2539,    2 }, /* GL_ANGLE_texture_external_update */
    {   92,  730,    5 }, /* GL_APPLE_element_array */
    {   93,  735,    8 }, /* GL_APPLE_fence */
    {   95,  743,    2 }, /* GL_APPLE_flush_buffer_range */
    {   97,  745,    3 }, /* GL_APPLE_object_purgeable */
    {  105,  748,    2 }, /* GL_APPLE_texture_range */
    {  107,  750,    4 }, /* GL_APPLE_vertex_array_object */
    {  108,  754,    3 }, /* GL_APPLE_vertex_array_range */
    {  109,  757,    7 }, /* GL_APPLE_vertex_program_evaluators */
    {  111,  391,    5 }, /* GL_ARB_ES2_compatibility */
    {  112,  641,    1 }, /* GL_ARB_ES3_1_compatibility */
    {  113,  764,    1 }, /* GL_ARB_ES3_2_compatibility */
    {  116,  479,    3 }, /* GL_ARB_base_instance */
    {  117,  765,   16 }, /* GL_ARB_bindless_texture */
    {  118,  317,    2 }, /* GL_ARB_blend_func_extended */
    {  119,  534,    1 }, /* GL_ARB_buffer_storage */
    {  120,  781,    1 }, /* GL_ARB_cl_event */
    {  121,  491,    2 }, /* GL_ARB_clear_buffer_object */
    {  122,  535,    2 }, /* GL_ARB_clear_texture */
    {  123,  543,    1 }, /* GL_ARB_clip_control */
    {  124,  782,    1 }, /* GL_ARB_color_buffer_float */
    {  127,  493,    2 }, /* GL_ARB_compute_shader */
    {  128,  783,    1 }, /* GL_ARB_compute_variable_group_size */
    {  131,  290,    1 }, /* GL_ARB_copy_buffer */
    {  132,  495,    1 }, /* GL_ARB_copy_image */
    {  134,  784,    4 }, /* GL_ARB_debug_output */
    {  139,  544,   97 }, /* GL_ARB_direct_state_access */
    {  140,  788,    1 }, /* GL_ARB_draw_buffers */
    {  141,  789,    4 }, /* GL_ARB_draw_buffers_blend */
    {  142,  298,    4 }, /* GL_ARB_draw_elements_base_vertex */
    {  143,  350,    2 }, /* GL_ARB_draw_indirect */
    {  144,  793,    2 }, /* GL_ARB_draw_instanced */
    {  150,  795,   19 }, /* GL_ARB_fragment_program */
    {  154,  496,    2 }, /* GL_ARB_framebuffer_no_attachments */
    {  155,  260,   20 }, /* GL_ARB_framebuffer_object */
    {  157,  814,    4 }, /* GL_ARB_geometry_shader4 */
    {  158,  396,    3 }, /* GL_ARB_get_program_binary */
    {  159,  642,    2 }, /* GL_ARB_get_texture_sub_image */
    {  160,  818,    1 }, /* GL_ARB_gl_spirv */
    {  162,  352,   18 }, /* GL_ARB_gpu_shader_fp64 */
    {  163,  819,   36 }, /* GL_ARB_gpu_shader_int64 */
    {  166,   82,    2 }, /* GL_ARB_imaging */
    {  167,  855,    2 }, /* GL_ARB_indirect_parameters */
    {  168,  857,    1 }, /* GL_ARB_instanced_arrays */
    {  169,  482,    1 }, /* GL_ARB_internalformat_query */
    {  170,  498,    1 }, /* GL_ARB_internalformat_query2 */
    {  171,  499,    6 }, /* GL_ARB_invalidate_subdata */
    {  173,  280,    2 }, /* GL_ARB_map_buffer_range */
    {  174,  858,    5 }, /* GL_ARB_matrix_palette */
    {  175,  537,    6 }, /* GL_ARB_multi_bind */
    {  176,  505,    2 }, /* GL_ARB_multi_draw_indirect */
    {  177,  863,    1 }, /* GL_ARB_multisample */
    {  178,  864,   34 }, /* GL_ARB_multitexture */
    {  179,  898,    8 }, /* GL_ARB_occlusion_query */
    {  181,  906,    1 }, /* GL_ARB_parallel_shader_compile */
    {  184,  907,    2 }, /* GL_ARB_point_parameters */
    {  186,  656,    1 }, /* GL_ARB_polygon_offset_clamp */
    {  188,  507,    6 }, /* GL_ARB_program_interface_query */
    {  189,  302,    1 }, /* GL_ARB_provoking_vertex */
    {  192,  909,    8 }, /* GL_ARB_robustness */
    {  194,  917,    3 }, /* GL_ARB_sample_locations */
    {  195,  920,    1 }, /* GL_ARB_sample_shading */
    {  196,  319,   14 }, /* GL_ARB_sampler_objects */
    {  199,  398,   61 }, /* GL_ARB_separate_shader_objects */
    {  201,  483,    1 }, /* GL_ARB_shader_atomic_counters */
    {  207,  484,    2 }, /* GL_ARB_shader_image_load_store */
    {  209,  921,   39 }, /* GL_ARB_shader_objects */
    {  212,  513,    1 }, /* GL_ARB_shader_storage_buffer_object */
    {  213,  370,    8 }, /* GL_ARB_shader_subroutine */
    {  219,  960,    6 }, /* GL_ARB_shading_language_include */
    {  223,  966,    3 }, /* GL_ARB_sparse_buffer */
    {  224,  969,    1 }, /* GL_ARB_sparse_texture */
    {  229,  303,    7 }, /* GL_ARB_sync */
    {  230,  378,    2 }, /* GL_ARB_tessellation_shader */
    {  231,  652,    1 }, /* GL_ARB_texture_barrier */
    {  233,  970,    1 }, /* GL_ARB_texture_buffer_object */
    {  235,  514,    1 }, /* GL_ARB_texture_buffer_range */
    {  236,  971,    7 }, /* GL_ARB_texture_compression */
    {  251,  313,    4 }, /* GL_ARB_texture_multisample */
    {  259,  486,    3 }, /* GL_ARB_texture_storage */
    {  260,  515,    2 }, /* GL_ARB_texture_storage_multisample */
    {  262,  517,    1 }, /* GL_ARB_texture_view */
    {  263,  333,    3 }, /* GL_ARB_timer_query */
    {  264,  380,    7 }, /* GL_ARB_transform_feedback2 */
    {  265,  387,    4 }, /* GL_ARB_transform_feedback3 */
    {  266,  489,    2 }, /* GL_ARB_transform_feedback_instanced */
    {  268,  978,    4 }, /* GL_ARB_transpose_matrix */
    {  269,  204,    1 }, /* GL_ARB_uniform_buffer_object */
    {  269,  210,    2 }, /* GL_ARB_uniform_buffer_object */
    {  269,  291,    7 }, /* GL_ARB_uniform_buffer_object */
    {  271,  282,    4 }, /* GL_ARB_vertex_array_object */
    {  272,  459,   10 }, /* GL_ARB_vertex_attrib_64bit */
    {  273,  518,    6 }, /* GL_ARB_vertex_attrib_binding */
    {  274,  982,   10 }, /* GL_ARB_vertex_blend */
    {  275,  992,   11 }, /* GL_ARB_vertex_buffer_object */
    {  276,  795,   19 }, /* GL_ARB_vertex_program */
    {  276, 1003,   43 }, /* GL_ARB_vertex_program */
    {  277, 1003,   46 }, /* GL_ARB_vertex_shader */
    {  279,  337,    8 }, /* GL_ARB_vertex_type_2_10_10_10_rev */
    {  280,  469,   10 }, /* GL_ARB_viewport_array */
    {  280, 1049,    2 }, /* GL_ARB_viewport_array */
    {  281, 1051,   16 }, /* GL_ARB_window_pos */
    {  291, 1067,    1 }, /* GL_ATI_draw_buffers */
    {  292, 1068,    3 }, /* GL_ATI_element_array */
    {  293, 1071,    4 }, /* GL_ATI_envmap_bumpmap */
    {  294, 1075,   14 }, /* GL_ATI_fragment_shader */
    {  295, 1089,    2 }, /* GL_ATI_map_object_buffer */
    {  298, 1091,    2 }, /* GL_ATI_pn_triangles */
    {  299, 1093,    2 }, /* GL_ATI_separate_stencil */
    {  304, 1095,   12 }, /* GL_ATI_vertex_array_object */
    {  305, 1107,    3 }, /* GL_ATI_vertex_attrib_array_object */
    {  306, 1110,   45 }, /* GL_ATI_vertex_streams */
    {  316, 1155,    2 }, /* GL_EXT_EGL_image_storage */
    {  324, 1157,    3 }, /* GL_EXT_bindable_uniform */
    {  325, 1160,    1 }, /* GL_EXT_blend_color */
    {  326, 1161,    1 }, /* GL_EXT_blend_equation_separate */
    {  328, 1163,    1 }, /* GL_EXT_blend_func_separate */
    {  330, 1164,    1 }, /* GL_EXT_blend_minmax */
    {  343, 1165,    2 }, /* GL_EXT_color_subtable */
    {  344, 1167,    2 }, /* GL_EXT_compiled_vertex_array */
    {  348, 1169,   13 }, /* GL_EXT_convolution */
    {  349, 1182,   22 }, /* GL_EXT_coordinate_frame */
    {  351, 1204,    5 }, /* GL_EXT_copy_texture */
    {  352, 1209,    2 }, /* GL_EXT_cull_vertex */
    {  353, 1211,    2 }, /* GL_EXT_debug_label */
    {  354, 1213,    3 }, /* GL_EXT_debug_marker */
    {  357, 1216,    1 }, /* GL_EXT_depth_bounds_test */
    {  360, 1217,  255 }, /* GL_EXT_direct_state_access */
    {  364, 1296,    5 }, /* GL_EXT_draw_buffers2 */
    {  364, 1474,    1 }, /* GL_EXT_draw_buffers2 */
    {  367, 1475,    2 }, /* GL_EXT_draw_instanced */
    {  368, 1477,    1 }, /* GL_EXT_draw_range_elements */
    {  371, 1478,    2 }, /* GL_EXT_external_buffer */
    {  374, 1480,    5 }, /* GL_EXT_fog_coord */
    {  377, 1485,    4 }, /* GL_EXT_fragment_shading_rate */
    {  378, 1489,    1 }, /* GL_EXT_framebuffer_blit */
    {  379, 1490,    2 }, /* GL_EXT_framebuffer_blit_layers */
    {  380, 1492,    1 }, /* GL_EXT_framebuffer_multisample */
    {  382, 1493,   17 }, /* GL_EXT_framebuffer_object */
    {  386, 1511,    1 }, /* GL_EXT_geometry_shader4 */
    {  387, 1512,    2 }, /* GL_EXT_gpu_program_parameters */
    {  388, 1162,    1 }, /* GL_EXT_gpu_shader4 */
    {  388, 1514,   33 }, /* GL_EXT_gpu_shader4 */
    {  390, 1547,   10 }, /* GL_EXT_histogram */
    {  392, 1557,    1 }, /* GL_EXT_index_func */
    {  393, 1558,    1 }, /* GL_EXT_index_material */
    {  397, 1559,    3 }, /* GL_EXT_light_texture */
    {  400, 1562,   19 }, /* GL_EXT_memory_object */
    {  401, 1581,    1 }, /* GL_EXT_memory_object_fd */
    {  402, 1582,    2 }, /* GL_EXT_memory_object_win32 */
    {  405, 1584,    2 }, /* GL_EXT_multi_draw_arrays */
    {  407, 1586,    2 }, /* GL_EXT_multisample */
    {  423, 1588,    4 }, /* GL_EXT_paletted_texture */
    {  425, 1592,    6 }, /* GL_EXT_pixel_transform */
    {  427, 1598,    2 }, /* GL_EXT_point_parameters */
    {  428, 1600,    1 }, /* GL_EXT_polygon_offset */
    {  429, 1601,    1 }, /* GL_EXT_polygon_offset_clamp */
    {  433, 1602,    1 }, /* GL_EXT_provoking_vertex */
    {  435, 1603,    1 }, /* GL_EXT_raster_multisample */
    {  449, 1614,   17 }, /* GL_EXT_secondary_color */
    {  450, 1562,    2 }, /* GL_EXT_semaphore */
    {  450, 1604,    7 }, /* GL_EXT_semaphore */
    {  451, 1611,    1 }, /* GL_EXT_semaphore_fd */
    {  452, 1612,    2 }, /* GL_EXT_semaphore_win32 */
    {  454, 1631,    3 }, /* GL_EXT_separate_shader_objects */
    {  470, 1634,    1 }, /* GL_EXT_shader_framebuffer_fetch_non_coherent */
    {  474, 1635,    2 }, /* GL_EXT_shader_image_load_store */
    {  500, 1637,    1 }, /* GL_EXT_stencil_clear_tag */
    {  501, 1638,    1 }, /* GL_EXT_stencil_two_side */
    {  505, 1639,    2 }, /* GL_EXT_subtexture */
    {  510, 1641,    2 }, /* GL_EXT_texture3D */
    {  511, 1643,    1 }, /* GL_EXT_texture_array */
    {  514, 1648,    1 }, /* GL_EXT_texture_buffer_object */
    {  531, 1644,    4 }, /* GL_EXT_texture_integer */
    {  531, 1649,    2 }, /* GL_EXT_texture_integer */
    {  536, 1651,    6 }, /* GL_EXT_texture_object */
    {  538, 1657,    1 }, /* GL_EXT_texture_perturb_normal */
    {  548, 1458,    3 }, /* GL_EXT_texture_storage */
    {  548, 1658,    3 }, /* GL_EXT_texture_storage */
    {  553, 1472,    2 }, /* GL_EXT_timer_query */
    {  554, 1664,    7 }, /* GL_EXT_transform_feedback */
    {  556, 1671,    9 }, /* GL_EXT_vertex_array */
    {  558, 1680,   10 }, /* GL_EXT_vertex_attrib_64bit */
    {  559, 1690,   42 }, /* GL_EXT_vertex_shader */
    {  560, 1732,    3 }, /* GL_EXT_vertex_weighting */
    {  562, 1735,    2 }, /* GL_EXT_win32_keyed_mutex */
    {  563, 1737,    1 }, /* GL_EXT_window_rectangles */
    {  564, 1738,    1 }, /* GL_EXT_x11_sync_object */
    {  566, 1739,    1 }, /* GL_GREMEDY_frame_terminator */
    {  567, 1740,    1 }, /* GL_GREMEDY_string_marker */
    {  569, 1741,    6 }, /* GL_HP_image_transform */
    {  577, 1747,    2 }, /* GL_IBM_multimode_draw_arrays */
    {  579, 1749,    1 }, /* GL_IBM_static_data */
    {  581, 1750,    8 }, /* GL_IBM_vertex_array_lists */
    {  591, 1758,    1 }, /* GL_INGR_blend_func_separate */
    {  597, 1759,    1 }, /* GL_INTEL_framebuffer_CMAA */
    {  598, 1760,    3 }, /* GL_INTEL_map_texture */
    {  599, 1763,    4 }, /* GL_INTEL_parallel_arrays */
    {  600, 1767,   10 }, /* GL_INTEL_performance_query */
    {  601, 1777,    1 }, /* GL_KHR_blend_equation_advanced */
    {  605,   50,    1 }, /* GL_KHR_debug */
    {  605,  524,   10 }, /* GL_KHR_debug */
    {  608, 1778,    1 }, /* GL_KHR_parallel_shader_compile */
    {  610,  644,    1 }, /* GL_KHR_robustness */
    {  610,  648,    4 }, /* GL_KHR_robustness */
    {  628, 1779,    2 }, /* GL_MESA_framebuffer_flip_y */
    {  630, 1781,    2 }, /* GL_MESA_map_buffer_client_pointer */
    {  633, 1783,    1 }, /* GL_MESA_resize_buffers */
    {  638, 1784,   24 }, /* GL_MESA_window_pos */
    {  641, 1808,    2 }, /* GL_NVX_conditional_render */
    {  643, 1975,    6 }, /* GL_NVX_gpu_multicast2 */
    {  644, 1810,    3 }, /* GL_NVX_linked_gpu_multicast */
    {  646, 1981,    4 }, /* GL_NVX_progress_fence */
    {  647, 1813,    1 }, /* GL_NV_alpha_to_coverage_dither_control */
    {  648, 1814,    2 }, /* GL_NV_bindless_multi_draw_indirect */
    {  649, 1816,    2 }, /* GL_NV_bindless_multi_draw_indirect_count */
    {  650, 1818,   13 }, /* GL_NV_bindless_texture */
    {  651, 1831,    2 }, /* GL_NV_blend_equation_advanced */
    {  655, 1833,    1 }, /* GL_NV_clip_space_w_scaling */
    {  657, 1834,   17 }, /* GL_NV_command_list */
    {  660, 1851,    2 }, /* GL_NV_conditional_render */
    {  661, 1853,    1 }, /* GL_NV_conservative_raster */
    {  662, 1854,    1 }, /* GL_NV_conservative_raster_dilate */
    {  664, 1855,    1 }, /* GL_NV_conservative_raster_pre_snap_triangles */
    {  671, 1856,    1 }, /* GL_NV_copy_image */
    {  674, 1857,    3 }, /* GL_NV_depth_buffer_float */
    {  680, 1860,    1 }, /* GL_NV_draw_texture */
    {  681, 1861,    5 }, /* GL_NV_draw_vulkan_image */
    {  682, 1866,    9 }, /* GL_NV_evaluators */
    {  684, 1875,    3 }, /* GL_NV_explicit_multisample */
    {  686, 1878,    7 }, /* GL_NV_fence */
    {  690, 1885,    1 }, /* GL_NV_fragment_coverage_to_color */
    {  691, 1886,    6 }, /* GL_NV_fragment_program */
    {  698, 1603,    1 }, /* GL_NV_framebuffer_mixed_samples */
    {  698, 1892,    3 }, /* GL_NV_framebuffer_mixed_samples */
    {  700, 1895,    1 }, /* GL_NV_framebuffer_multisample_coverage */
    {  702, 1510,    1 }, /* GL_NV_geometry_program4 */
    {  702, 1643,    1 }, /* GL_NV_geometry_program4 */
    {  702, 1896,    2 }, /* GL_NV_geometry_program4 */
    {  705, 1963,   12 }, /* GL_NV_gpu_multicast */
    {  706, 1898,   16 }, /* GL_NV_gpu_program4 */
    {  707, 1914,    2 }, /* GL_NV_gpu_program5 */
    {  709,  672,   17 }, /* GL_NV_gpu_shader5 */
    {  709,  690,   16 }, /* GL_NV_gpu_shader5 */
    {  710, 1916,   46 }, /* GL_NV_half_float */
    {  714, 1962,    1 }, /* GL_NV_internalformat_sample_query */
    {  717, 1985,    6 }, /* GL_NV_memory_attachment */
    {  718, 1991,    4 }, /* GL_NV_memory_object_sparse */
    {  719, 1995,    4 }, /* GL_NV_mesh_shader */
    {  723, 1999,    7 }, /* GL_NV_occlusion_query */
    {  726, 2006,    3 }, /* GL_NV_parameter_buffer_object */
    {  728, 1217,   15 }, /* GL_NV_path_rendering */
    {  728, 1315,    4 }, /* GL_NV_path_rendering */
    {  728, 2009,   57 }, /* GL_NV_path_rendering */
    {  731, 2066,    2 }, /* GL_NV_pixel_data_range */
    {  732, 2068,    2 }, /* GL_NV_point_sprite */
    {  734, 2070,    6 }, /* GL_NV_present_video */
    {  735, 2076,    2 }, /* GL_NV_primitive_restart */
    {  737, 2078,    1 }, /* GL_NV_query_resource */
    {  738, 2079,    3 }, /* GL_NV_query_resource_tag */
    {  746, 2082,   13 }, /* GL_NV_register_combiners */
    {  747, 2095,    2 }, /* GL_NV_register_combiners2 */
    {  751, 2097,    3 }, /* GL_NV_sample_locations */
    {  753, 2100,    2 }, /* GL_NV_scissor_exclusive */
    {  759,  689,    1 }, /* GL_NV_shader_buffer_load */
    {  759, 2102,   13 }, /* GL_NV_shader_buffer_load */
    {  769, 2115,    7 }, /* GL_NV_shading_rate_image */
    {  776, 2122,    1 }, /* GL_NV_texture_barrier */
    {  782, 2123,    6 }, /* GL_NV_texture_multisample */
    {  789, 1661,    3 }, /* GL_NV_timeline_semaphore */
    {  790, 2129,   12 }, /* GL_NV_transform_feedback */
    {  791, 2141,    7 }, /* GL_NV_transform_feedback2 */
    {  794, 2148,   10 }, /* GL_NV_vdpau_interop */
    {  795, 2158,    1 }, /* GL_NV_vdpau_interop2 */
    {  796, 2159,    2 }, /* GL_NV_vertex_array_range */
    {  798, 2161,   19 }, /* GL_NV_vertex_attrib_integer_64bit */
    {  799, 2180,   12 }, /* GL_NV_vertex_buffer_unified_memory */
    {  800, 2192,   64 }, /* GL_NV_vertex_program */
    {  805, 1524,   23 }, /* GL_NV_vertex_program4 */
    {  806, 2256,   12 }, /* GL_NV_video_capture */
    {  809, 2268,    1 }, /* GL_NV_viewport_swizzle */
    {  813, 2269,   22 }, /* GL_OES_byte_coordinates */
    {  825, 2291,  103 }, /* GL_OES_fixed_point */
    {  834, 2394,    1 }, /* GL_OES_query_matrix */
    {  843, 2395,    6 }, /* GL_OES_single_precision */
    {  870, 2401,    2 }, /* GL_OVR_multiview */
    {  873, 2403,    1 }, /* GL_PGI_misc_hints */
    {  903, 2404,    2 }, /* GL_SGIS_detail_texture */
    {  904, 2406,    2 }, /* GL_SGIS_fog_function */
    {  906, 2408,    2 }, /* GL_SGIS_multisample */
    {  907, 2410,    6 }, /* GL_SGIS_pixel_texture */
    {  909, 2416,    2 }, /* GL_SGIS_point_parameters */
    {  910, 2418,    2 }, /* GL_SGIS_sharpen_texture */
    {  911, 2420,    2 }, /* GL_SGIS_texture4D */
    {  913, 2422,    1 }, /* GL_SGIS_texture_color_mask */
    {  915, 2423,    2 }, /* GL_SGIS_texture_filter4 */
    {  918, 2425,    6 }, /* GL_SGIX_async */
    {  927, 2431,    1 }, /* GL_SGIX_flush_raster */
    {  929, 2432,   18 }, /* GL_SGIX_fragment_lighting */
    {  930, 2450,    1 }, /* GL_SGIX_framezoom */
    {  931, 2451,    1 }, /* GL_SGIX_igloo_interface */
    {  932, 2452,    6 }, /* GL_SGIX_instruments */
    {  935, 2458,    6 }, /* GL_SGIX_list_priority */
    {  936, 2464,    1 }, /* GL_SGIX_pixel_texture */
    {  938, 2465,    4 }, /* GL_SGIX_polynomial_ffd */
    {  939, 2469,    1 }, /* GL_SGIX_reference_plane */
    {  944, 2470,    4 }, /* GL_SGIX_sprite */
    {  946, 2474,    1 }, /* GL_SGIX_tag_sample_buffer */
    {  957, 2475,    7 }, /* GL_SGI_color_table */
    {  959, 2482,    1 }, /* GL_SUNX_constant_data */
    {  961, 2483,    8 }, /* GL_SUN_global_alpha */
    {  962, 2491,    1 }, /* GL_SUN_mesh_array */
    {  964, 2492,    7 }, /* GL_SUN_triangle_list */
    {  965, 2499,   40 }, /* GL_SUN_vertex */
};

static const GladPfnRange_t GLAD_gles2_ext_pfn_ranges[] = {
    {   10,  666,    2 }, /* GL_AMD_framebuffer_multisample_advanced */
    {   20,  713,   11 }, /* GL_AMD_performance_monitor */
    {   44, 2846,    4 }, /* GL_ANGLE_base_vertex_base_instance */
    {   45, 2873,    2 }, /* GL_ANGLE_blob_cache */
    {   48, 2837,    2 }, /* GL_ANGLE_copy_texture_3d */
    {   50, 2549,    1 }, /* GL_ANGLE_framebuffer_blit */
    {   51, 2550,    1 }, /* GL_ANGLE_framebuffer_multisample */
    {   52, 2853,    3 }, /* GL_ANGLE_get_image */
    {   54, 2856,    2 }, /* GL_ANGLE_get_tex_level_parameter */
    {   55, 2551,    3 }, /* GL_ANGLE_instanced_arrays */
    {   56, 2872,    1 }, /* GL_ANGLE_logic_op */
    {   58, 2541,    4 }, /* GL_ANGLE_memory_object_flags */
    {   59, 2545,    1 }, /* GL_ANGLE_memory_object_fuchsia */
    {   61, 2842,    4 }, /* GL_ANGLE_multi_draw */
    {   63, 2850,    1 }, /* GL_ANGLE_polygon_mode */
    {   67, 2851,    1 }, /* GL_ANGLE_provoking_vertex */
    {   69, 2782,    2 }, /* GL_ANGLE_request_extension */
    {   71, 2786,   51 }, /* GL_ANGLE_robust_client_memory */
    {   74, 2546,    1 }, /* GL_ANGLE_semaphore_fuchsia */
    {   76, 2858,   14 }, /* GL_ANGLE_shader_pixel_local_storage */
    {   81, 2539,    2 }, /* GL_ANGLE_texture_external_update */
    {   82, 2839,    3 }, /* GL_ANGLE_texture_multisample */
    {   84, 2554,    1 }, /* GL_ANGLE_translated_shader_source */
    {   85, 2784,    2 }, /* GL_ANGLE_vulkan_image */
    {   91, 2555,    1 }, /* GL_APPLE_copy_texture_levels */
    {   96, 2556,    2 }, /* GL_APPLE_framebuffer_multisample */
    {  101, 2558,    7 }, /* GL_APPLE_sync */
    {  287, 2565,    1 }, /* GL_ARM_shader_core_properties */
    {  307, 2777,    1 }, /* GL_CHROMIUM_bind_uniform_location */
    {  308, 2781,    1 }, /* GL_CHROMIUM_copy_compressed_texture */
    {  309, 2779,    2 }, /* GL_CHROMIUM_copy_texture */
    {  310, 2778,    1 }, /* GL_CHROMIUM_framebuffer_mixed_samples */
    {  311, 2852,    1 }, /* GL_CHROMIUM_lose_context */
    {  316, 1155,    2 }, /* GL_EXT_EGL_image_storage */
    {  321, 2566,    3 }, /* GL_EXT_base_instance */
    {  327, 1162,    1 }, /* GL_EXT_blend_func_extended */
    {  327, 2569,    3 }, /* GL_EXT_blend_func_extended */
    {  335, 2572,    1 }, /* GL_EXT_buffer_storage */
    {  336, 2573,    2 }, /* GL_EXT_clear_texture */
    {  337, 2575,    1 }, /* GL_EXT_clip_control */
    {  350, 2576,    1 }, /* GL_EXT_copy_image */
    {  353, 1211,    2 }, /* GL_EXT_debug_label */
    {  354, 1213,    3 }, /* GL_EXT_debug_marker */
    {  361, 2577,    1 }, /* GL_EXT_discard_framebuffer */
    {  362, 1472,    2 }, /* GL_EXT_disjoint_timer_query */
    {  362, 2578,   10 }, /* GL_EXT_disjoint_timer_query */
    {  363, 2588,    1 }, /* GL_EXT_draw_buffers */
    {  365, 2589,    8 }, /* GL_EXT_draw_buffers_indexed */
    {  366, 2597,    4 }, /* GL_EXT_draw_elements_base_vertex */
    {  367, 1475,    2 }, /* GL_EXT_draw_instanced */
    {  369, 2601,    2 }, /* GL_EXT_draw_transform_feedback */
    {  371, 1478,    2 }, /* GL_EXT_external_buffer */
    {  377, 1485,    4 }, /* GL_EXT_fragment_shading_rate */
    {  379, 1490,    2 }, /* GL_EXT_framebuffer_blit_layers */
    {  385, 1510,    1 }, /* GL_EXT_geometry_shader */
    {  395, 1475,    2 }, /* GL_EXT_instanced_arrays */
    {  395, 2603,    1 }, /* GL_EXT_instanced_arrays */
    {  398, 2604,    2 }, /* GL_EXT_map_buffer_range */
    {  400, 1562,   17 }, /* GL_EXT_memory_object */
    {  401, 1581,    1 }, /* GL_EXT_memory_object_fd */
    {  402, 1582,    2 }, /* GL_EXT_memory_object_win32 */
    {  405, 1584,    2 }, /* GL_EXT_multi_draw_arrays */
    {  406, 2606,    2 }, /* GL_EXT_multi_draw_indirect */
    {  409, 1492,    1 }, /* GL_EXT_multisampled_render_to_texture */
    {  409, 2608,    1 }, /* GL_EXT_multisampled_render_to_texture */
    {  411, 2609,    3 }, /* GL_EXT_multiview_draw_buffers */
    {  418, 2578,    5 }, /* GL_EXT_occlusion_query_boolean */
    {  418, 2584,    1 }, /* GL_EXT_occlusion_query_boolean */
    {  418, 2586,    1 }, /* GL_EXT_occlusion_query_boolean */
    {  429, 1601,    1 }, /* GL_EXT_polygon_offset_clamp */
    {  431, 2612,    1 }, /* GL_EXT_primitive_bounding_box */
    {  435, 1603,    1 }, /* GL_EXT_raster_multisample */
    {  444, 2613,    4 }, /* GL_EXT_robustness */
    {  450, 1562,    2 }, /* GL_EXT_semaphore */
    {  450, 1604,    7 }, /* GL_EXT_semaphore */
    {  451, 1611,    1 }, /* GL_EXT_semaphore_fd */
    {  452, 1612,    2 }, /* GL_EXT_semaphore_win32 */
    {  454, 1326,   25 }, /* GL_EXT_separate_shader_objects */
    {  454, 1361,    8 }, /* GL_EXT_separate_shader_objects */
    {  454, 1511,    1 }, /* GL_EXT_separate_shader_objects */
    {  454, 2617,   10 }, /* GL_EXT_separate_shader_objects */
    {  470, 1634,    1 }, /* GL_EXT_shader_framebuffer_fetch_non_coherent */
    {  480, 2627,    3 }, /* GL_EXT_shader_pixel_local_storage2 */
    {  496, 2630,    1 }, /* GL_EXT_sparse_texture */
    {  508, 2631,    1 }, /* GL_EXT_tessellation_shader */
    {  512, 1644,    4 }, /* GL_EXT_texture_border_clamp */
    {  512, 2632,    4 }, /* GL_EXT_texture_border_clamp */
    {  513, 1648,    1 }, /* GL_EXT_texture_buffer */
    {  513, 2636,    1 }, /* GL_EXT_texture_buffer */
    {  548, 1458,    3 }, /* GL_EXT_texture_storage */
    {  548, 1658,    3 }, /* GL_EXT_texture_storage */
    {  549, 2637,    2 }, /* GL_EXT_texture_storage_compression */
    {  552, 2639,    1 }, /* GL_EXT_texture_view */
    {  562, 1735,    2 }, /* GL_EXT_win32_keyed_mutex */
    {  563, 1737,    1 }, /* GL_EXT_window_rectangles */
    {  582, 2640,    6 }, /* GL_IMG_bindless_texture */
    {  583, 2646,    2 }, /* GL_IMG_framebuffer_downsample */
    {  584, 2648,    2 }, /* GL_IMG_multisampled_render_to_texture */
    {  597, 1759,    1 }, /* GL_INTEL_framebuffer_CMAA */
    {  600, 1767,   10 }, /* GL_INTEL_performance_query */
    {  601, 1777,    1 }, /* GL_KHR_blend_equation_advanced */
    {  605, 2650,   11 }, /* GL_KHR_debug */
    {  608, 1778,    1 }, /* GL_KHR_parallel_shader_compile */
    {  610, 2661,    5 }, /* GL_KHR_robustness */
    {  628, 1779,    2 }, /* GL_MESA_framebuffer_flip_y */
    {  634,  319,    8 }, /* GL_MESA_sampler_objects */
    {  634,  329,    1 }, /* GL_MESA_sampler_objects */
    {  634,  331,    1 }, /* GL_MESA_sampler_objects */
    {  650, 1818,   13 }, /* GL_NV_bindless_texture */
    {  651, 1831,    2 }, /* GL_NV_blend_equation_advanced */
    {  655, 1833,    1 }, /* GL_NV_clip_space_w_scaling */
    {  660, 1851,    2 }, /* GL_NV_conditional_render */
    {  661, 1853,    1 }, /* GL_NV_conservative_raster */
    {  664, 1855,    1 }, /* GL_NV_conservative_raster_pre_snap_triangles */
    {  669, 2666,    1 }, /* GL_NV_copy_buffer */
    {  672, 2667,    2 }, /* GL_NV_coverage_sample */
    {  678, 2669,    1 }, /* GL_NV_draw_buffers */
    {  679, 2670,    2 }, /* GL_NV_draw_instanced */
    {  681, 1861,    5 }, /* GL_NV_draw_vulkan_image */
    {  686, 1878,    7 }, /* GL_NV_fence */
    {  690, 1885,    1 }, /* GL_NV_fragment_coverage_to_color */
    {  697, 2672,    1 }, /* GL_NV_framebuffer_blit */
    {  698, 1603,    1 }, /* GL_NV_framebuffer_mixed_samples */
    {  698, 1892,    3 }, /* GL_NV_framebuffer_mixed_samples */
    {  699, 2673,    1 }, /* GL_NV_framebuffer_multisample */
    {  709,  672,   17 }, /* GL_NV_gpu_shader5 */
    {  709,  690,   16 }, /* GL_NV_gpu_shader5 */
    {  712, 2674,    1 }, /* GL_NV_instanced_arrays */
    {  714, 1962,    1 }, /* GL_NV_internalformat_sample_query */
    {  717, 1985,    6 }, /* GL_NV_memory_attachment */
    {  718, 1991,    4 }, /* GL_NV_memory_object_sparse */
    {  719, 1995,    4 }, /* GL_NV_mesh_shader */
    {  722, 2675,    6 }, /* GL_NV_non_square_matrices */
    {  728, 1217,   15 }, /* GL_NV_path_rendering */
    {  728, 1315,    4 }, /* GL_NV_path_rendering */
    {  728, 2009,   57 }, /* GL_NV_path_rendering */
    {  733, 2681,    1 }, /* GL_NV_polygon_mode */
    {  741, 2682,    1 }, /* GL_NV_read_buffer */
    {  751, 2097,    3 }, /* GL_NV_sample_locations */
    {  753, 2100,    2 }, /* GL_NV_scissor_exclusive */
    {  769, 2115,    7 }, /* GL_NV_shading_rate_image */
    {  776, 2122,    1 }, /* GL_NV_texture_barrier */
    {  789, 1661,    3 }, /* GL_NV_timeline_semaphore */
    {  807, 2683,   12 }, /* GL_NV_viewport_array */
    {  809, 2268,    1 }, /* GL_NV_viewport_swizzle */
    {  810, 2695,    2 }, /* GL_OES_EGL_image */
    {  811, 2695,    1 }, /* GL_OES_EGL_image_external */
    {  817, 2697,    1 }, /* GL_OES_copy_image */
    {  821, 2698,    8 }, /* GL_OES_draw_buffers_indexed */
    {  822, 2600,    1 }, /* GL_OES_draw_elements_base_vertex */
    {  822, 2706,    3 }, /* GL_OES_draw_elements_base_vertex */
    {  828, 2709,    1 }, /* GL_OES_geometry_shader */
    {  829, 2710,    2 }, /* GL_OES_get_program_binary */
    {  831, 2712,    3 }, /* GL_OES_mapbuffer */
    {  833, 2715,    1 }, /* GL_OES_primitive_bounding_box */
    {  838, 2716,    1 }, /* GL_OES_sample_shading */
    {  849, 2717,    1 }, /* GL_OES_tessellation_shader */
    {  850, 2718,    6 }, /* GL_OES_texture_3D */
    {  851, 2724,    8 }, /* GL_OES_texture_border_clamp */
    {  852, 2732,    2 }, /* GL_OES_texture_buffer */
    {  861, 2734,    1 }, /* GL_OES_texture_storage_multisample_2d_array */
    {  862, 2735,    1 }, /* GL_OES_texture_view */
    {  863, 2736,    4 }, /* GL_OES_vertex_array_object */
    {  866, 2698,    2 }, /* GL_OES_viewport_array */
    {  866, 2705,    1 }, /* GL_OES_viewport_array */
    {  866, 2740,    9 }, /* GL_OES_viewport_array */
    {  870, 2401,    2 }, /* GL_OVR_multiview */
    {  872, 2749,    1 }, /* GL_OVR_multiview_multisampled_render_to_texture */
    {  876, 2750,    1 }, /* GL_QCOM_alpha_test */
    {  879, 2751,    4 }, /* GL_QCOM_driver_control */
    {  880, 2755,    8 }, /* GL_QCOM_extended_get */
    {  881, 2763,    4 }, /* GL_QCOM_extended_get2 */
    {  882, 2771,    1 }, /* GL_QCOM_frame_extrapolation */
    {  883, 2767,    2 }, /* GL_QCOM_framebuffer_foveated */
    {  886, 2769,    2 }, /* GL_QCOM_motion_estimation */
    {  890, 2773,    1 }, /* GL_QCOM_shader_framebuffer_fetch_noncoherent */
    {  892, 2774,    1 }, /* GL_QCOM_shading_rate */
    {  893, 2772,    1 }, /* GL_QCOM_texture_foveated */
    {  898, 2775,    2 }, /* GL_QCOM_tiled_rendering */
};

static const uint64_t GLAD_GL_ext_hashes[] = {
    /*    0 */ 0xa3f15a4859642e24ULL, /* GL_3DFX_multisample */
    /*    1 */ 0x4cf5d1995a66a5feULL, /* GL_3DFX_tbuffer */
    /*    2 */ 0x389939b5cbd91a14ULL, /* GL_3DFX_texture_compression_FXT1 */
    /*    3 */ 0xbf938a3109ec723dULL, /* GL_AMD_blend_minmax_factor */
    /*    4 */ 0xfbca194ce346f79dULL, /* GL_AMD_compressed_3DC_texture */
    /*    5 */ 0xb60a0647d19ecd25ULL, /* GL_AMD_compressed_ATC_texture */
    /*    6 */ 0x3a0fcb022a0e918aULL, /* GL_AMD_conservative_depth */
    /*    7 */ 0x2bbc0581a1b2b142ULL, /* GL_AMD_debug_output */
    /*    8 */ 0x8528a16a1fdb6d51ULL, /* GL_AMD_depth_clamp_separate */
    /*    9 */ 0x746cf03f26c4858aULL, /* GL_AMD_draw_buffers_blend */
    /*   10 */ 0xfaa176d058525abfULL, /* GL_AMD_framebuffer_multisample_advanced */
    /*   11 */ 0xb81865d628d4822eULL, /* GL_AMD_framebuffer_sample_positions */
    /*   12 */ 0x54b9b5e1e15805ffULL, /* GL_AMD_gcn_shader */
    /*   13 */ 0xf2b3ada35ec86eceULL, /* GL_AMD_gpu_shader_half_float */
    /*   14 */ 0x58e280e4b7565424ULL, /* GL_AMD_gpu_shader_int16 */
    /*   15 */ 0xa314f8e9473e8e89ULL, /* GL_AMD_gpu_shader_int64 */
    /*   16 */ 0x601bad09d1d7fc1eULL, /* GL_AMD_interleaved_elements */
    /*   17 */ 0x173d9b4be210ea12ULL, /* GL_AMD_multi_draw_indirect */
    /*   18 */ 0x3e05101dd76b1e5cULL, /* GL_AMD_name_gen_delete */
    /*   19 */ 0xd587d820af131b88ULL, /* GL_AMD_occlusion_query_event */
    /*   20 */ 0xf677c0636b66a6a3ULL, /* GL_AMD_performance_monitor */
    /*   21 */ 0xb735d6755296c48cULL, /* GL_AMD_pinned_memory */
    /*   22 */ 0xb965a8b418ce69c6ULL, /* GL_AMD_program_binary_Z400 */
    /*   23 */ 0xb3185e56ea54b6fdULL, /* GL_AMD_query_buffer_object */
    /*   24 */ 0x5b0c6a562ce2569dULL, /* GL_AMD_sample_positions */
    /*   25 */ 0x3ff7cc5aa13067f5ULL, /* GL_AMD_seamless_cubemap_per_texture */
    /*   26 */ 0x49e444d707242c80ULL, /* GL_AMD_shader_atomic_counter_ops */
    /*   27 */ 0xf504ee512dc7b00cULL, /* GL_AMD_shader_ballot */
    /*   28 */ 0xcd0e9d8a9f876dd2ULL, /* GL_AMD_shader_explicit_vertex_parameter */
    /*   29 */ 0xdcf2ddfe44d1fe83ULL, /* GL_AMD_shader_fragment_mask */
    /*   30 */ 0x336dfdc747f76e82ULL, /* GL_AMD_shader_gpu_shader_half_float_fetch */
    /*   31 */ 0x96b07741ca00233dULL, /* GL_AMD_shader_image_load_store_lod */
    /*   32 */ 0xc126db7d83e09283ULL, /* GL_AMD_shader_stencil_export */
    /*   33 */ 0x177b92b7cd669d32ULL, /* GL_AMD_shader_trinary_minmax */
    /*   34 */ 0x68c5d21c9c5abe68ULL, /* GL_AMD_sparse_texture */
    /*   35 */ 0xd7a31898c597c5c3ULL, /* GL_AMD_stencil_operation_extended */
    /*   36 */ 0xb50e97696e955bbeULL, /* GL_AMD_texture_gather_bias_lod */
    /*   37 */ 0x013afe81eb3c2e0aULL, /* GL_AMD_texture_texture4 */
    /*   38 */ 0x4c4606ee62053585ULL, /* GL_AMD_transform_feedback3_lines_triangles */
    /*   39 */ 0x164bc52d21b26a0dULL, /* GL_AMD_transform_feedback4 */
    /*   40 */ 0x34b4364b37b53b68ULL, /* GL_AMD_vertex_shader_layer */
    /*   41 */ 0xfcd565a5b4211b86ULL, /* GL_AMD_vertex_shader_tessellator */
    /*   42 */ 0xcff6900b34a57200ULL, /* GL_AMD_vertex_shader_viewport_index */
    /*   43 */ 0xc41066419a80a1a5ULL, /* GL_ANDROID_extension_pack_es31a */
    /*   44 */ 0x269b1b3d43f0044bULL, /* GL_ANGLE_base_vertex_base_instance */
    /*   45 */ 0x2e2561f11ae590dcULL, /* GL_ANGLE_blob_cache */
    /*   46 */ 0x482ab3c6619af337ULL, /* GL_ANGLE_client_arrays */
    /*   47 */ 0x41739af4618fe843ULL, /* GL_ANGLE_clip_cull_distance */
    /*   48 */ 0xa1378a5ab6903c05ULL, /* GL_ANGLE_copy_texture_3d */
    /*   49 */ 0xaa8f55d75eb1ea08ULL, /* GL_ANGLE_depth_texture */
    /*   50 */ 0xeb72d824895faa8cULL, /* GL_ANGLE_framebuffer_blit */
    /*   51 */ 0x45e7dae6cdab912bULL, /* GL_ANGLE_framebuffer_multisample */
    /*   52 */ 0x352e547dc4c723c9ULL, /* GL_ANGLE_get_image */
    /*   53 */ 0x3b399821bf301295ULL, /* GL_ANGLE_get_serialized_context_string */
    /*   54 */ 0xa8bc2a751596a8c9ULL, /* GL_ANGLE_get_tex_level_parameter */
    /*   55 */ 0xf21d57ef70efa97fULL, /* GL_ANGLE_instanced_arrays */
    /*   56 */ 0x611ffec7970d55f4ULL, /* GL_ANGLE_logic_op */
    /*   57 */ 0xce13622f2ae81cf6ULL, /* GL_ANGLE_lossy_etc_decode */
    /*   58 */ 0xf1c5c3418f5bfbbcULL, /* GL_ANGLE_memory_object_flags */
    /*   59 */ 0x2655c424cb0e67d6ULL, /* GL_ANGLE_memory_object_fuchsia */
    /*   60 */ 0x29c14753da729d8bULL, /* GL_ANGLE_memory_size */
    /*   61 */ 0x96c6dc8ae13a863fULL, /* GL_ANGLE_multi_draw */
    /*   62 */ 0x5648b6070cf43450ULL, /* GL_ANGLE_pack_reverse_row_order */
    /*   63 */ 0xf830ca37ce4d57e9ULL, /* GL_ANGLE_polygon_mode */
    /*   64 */ 0x7e99ccc7605afe66ULL, /* GL_ANGLE_program_binary */
    /*   65 */ 0x66f0ab28691d8be7ULL, /* GL_ANGLE_program_binary_readiness_query */
    /*   66 */ 0x75815242daf456c4ULL, /* GL_ANGLE_program_cache_control */
    /*   67 */ 0x636fa9fe6b321bd4ULL, /* GL_ANGLE_provoking_vertex */
    /*   68 */ 0xecb6507e3e1d02f8ULL, /* GL_ANGLE_renderability_validation */
    /*   69 */ 0xe81bb93ca0cf6f2aULL, /* GL_ANGLE_request_extension */
    /*   70 */ 0x25833e2905e922d8ULL, /* GL_ANGLE_rgbx_internal_format */
    /*   71 */ 0xe20f551fc33bd429ULL, /* GL_ANGLE_robust_client_memory */
    /*   72 */ 0xf0b98d581ffeb5e0ULL, /* GL_ANGLE_robust_fragment_shader_output */
    /*   73 */ 0x5d895fe77bc5a43fULL, /* GL_ANGLE_robust_resource_initialization */
    /*   74 */ 0xd4ba1c0aafe5b41fULL, /* GL_ANGLE_semaphore_fuchsia */
    /*   75 */ 0x2c1380c8a72e821aULL, /* GL_ANGLE_shader_binary */
    /*   76 */ 0x69a67f8bce5ed738ULL, /* GL_ANGLE_shader_pixel_local_storage */
    /*   77 */ 0x1cdf91894ef6922dULL, /* GL_ANGLE_stencil_texturing */
    /*   78 */ 0xe4c777c3da15fb5dULL, /* GL_ANGLE_texture_compression_dxt1 */
    /*   79 */ 0x3ced8289e55b381fULL, /* GL_ANGLE_texture_compression_dxt3 */
    /*   80 */ 0xe031d89a47ab0e88ULL, /* GL_ANGLE_texture_compression_dxt5 */
    /*   81 */ 0x261f90903ebb2b21ULL, /* GL_ANGLE_texture_external_update */
    /*   82 */ 0xbae723a89da1bdfdULL, /* GL_ANGLE_texture_multisample */
    /*   83 */ 0x2164a76cb4716269ULL, /* GL_ANGLE_texture_usage */
    /*   84 */ 0x210dd20de1d385d7ULL, /* GL_ANGLE_translated_shader_source */
    /*   85 */ 0x186b1da5d851bbecULL, /* GL_ANGLE_vulkan_image */
    /*   86 */ 0xf870cb9d6ba30da8ULL, /* GL_ANGLE_yuv_internal_format */
    /*   87 */ 0xedd8d13a9eab22a7ULL, /* GL_APPLE_aux_depth_stencil */
    /*   88 */ 0x9cb930c662d0cbc5ULL, /* GL_APPLE_client_storage */
    /*   89 */ 0xca00966a7d53874dULL, /* GL_APPLE_clip_distance */
    /*   90 */ 0x8b12f4834ed80365ULL, /* GL_APPLE_color_buffer_packed_float */
    /*   91 */ 0x3b1ff61d2ca7ebefULL, /* GL_APPLE_copy_texture_levels */
    /*   92 */ 0x393954d6a157dc34ULL, /* GL_APPLE_element_array */
    /*   93 */ 0x248c97fa0866c224ULL, /* GL_APPLE_fence */
    /*   94 */ 0x4b598c5361e19ad0ULL, /* GL_APPLE_float_pixels */
    /*   95 */ 0x90a2f67506c1c227ULL, /* GL_APPLE_flush_buffer_range */
    /*   96 */ 0x349436461b4902f0ULL, /* GL_APPLE_framebuffer_multisample */
    /*   97 */ 0x41f28225bfe72cb5ULL, /* GL_APPLE_object_purgeable */
    /*   98 */ 0xc380c84097cc2eaaULL, /* GL_APPLE_rgb_422 */
    /*   99 */ 0x65041d91620fe255ULL, /* GL_APPLE_row_bytes */
    /*  100 */ 0xe73b092a3adf8b6fULL, /* GL_APPLE_specular_vector */
    /*  101 */ 0x965df8be0c61c5efULL, /* GL_APPLE_sync */
    /*  102 */ 0xd46cf8fd7182caf2ULL, /* GL_APPLE_texture_format_BGRA8888 */
    /*  103 */ 0x45f22d7fbb944c1aULL, /* GL_APPLE_texture_max_level */
    /*  104 */ 0x9d3d6479810f97acULL, /* GL_APPLE_texture_packed_float */
    /*  105 */ 0x9ab7d0b3c514d378ULL, /* GL_APPLE_texture_range */
    /*  106 */ 0x5d3f53e18fb3ff55ULL, /* GL_APPLE_transform_hint */
    /*  107 */ 0xb0874f6446afabceULL, /* GL_APPLE_vertex_array_object */
    /*  108 */ 0xd3da8f94dff875f1ULL, /* GL_APPLE_vertex_array_range */
    /*  109 */ 0x9bf0cbe91e220c86ULL, /* GL_APPLE_vertex_program_evaluators */
    /*  110 */ 0xe908f191198042d8ULL, /* GL_APPLE_ycbcr_422 */
    /*  111 */ 0x1f6122983853ff45ULL, /* GL_ARB_ES2_compatibility */
    /*  112 */ 0xa9d98ac21fcaf80bULL, /* GL_ARB_ES3_1_compatibility */
    /*  113 */ 0x8945b05fdf09b074ULL, /* GL_ARB_ES3_2_compatibility */
    /*  114 */ 0xea26087e653cab2bULL, /* GL_ARB_ES3_compatibility */
    /*  115 */ 0x08410053810ead05ULL, /* GL_ARB_arrays_of_arrays */
    /*  116 */ 0x40b475be6ab996bbULL, /* GL_ARB_base_instance */
    /*  117 */ 0xb2e0c01fbc4a0d90ULL, /* GL_ARB_bindless_texture */
    /*  118 */ 0x98330877cd269847ULL, /* GL_ARB_blend_func_extended */
    /*  119 */ 0x2aa09aeb0f69408bULL, /* GL_ARB_buffer_storage */
    /*  120 */ 0xf1d364213ef0dd70ULL, /* GL_ARB_cl_event */
    /*  121 */ 0x68a226aab21d4c06ULL, /* GL_ARB_clear_buffer_object */
    /*  122 */ 0xb9bb33941fa4b35fULL, /* GL_ARB_clear_texture */
    /*  123 */ 0x0062a8cb7bae8d41ULL, /* GL_ARB_clip_control */
    /*  124 */ 0x9ab3cde2bbe8e41cULL, /* GL_ARB_color_buffer_float */
    /*  125 */ 0xe421f74d58d12f0fULL, /* GL_ARB_compatibility */
    /*  126 */ 0xfcfdeecd633ecd3fULL, /* GL_ARB_compressed_texture_pixel_storage */
    /*  127 */ 0xd9df667054f06223ULL, /* GL_ARB_compute_shader */
    /*  128 */ 0xc49c40e9865275e6ULL, /* GL_ARB_compute_variable_group_size */
    /*  129 */ 0x6bf8cd6035aef76cULL, /* GL_ARB_conditional_render_inverted */
    /*  130 */ 0xcc005319118f39bbULL, /* GL_ARB_conservative_depth */
    /*  131 */ 0x66bffd41bcf61546ULL, /* GL_ARB_copy_buffer */
    /*  132 */ 0x66cd5d5964674061ULL, /* GL_ARB_copy_image */
    /*  133 */ 0x59cf6e44c2fc962aULL, /* GL_ARB_cull_distance */
    /*  134 */ 0x2b16e3dcc2f78c79ULL, /* GL_ARB_debug_output */
    /*  135 */ 0x3f93699d406e0f0eULL, /* GL_ARB_depth_buffer_float */
    /*  136 */ 0x53b30bc0d3be88f6ULL, /* GL_ARB_depth_clamp */
    /*  137 */ 0xd0e68b1ed9117edfULL, /* GL_ARB_depth_texture */
    /*  138 */ 0x34fe88e233827c23ULL, /* GL_ARB_derivative_control */
    /*  139 */ 0x8e24d5c3614e8aa2ULL, /* GL_ARB_direct_state_access */
    /*  140 */ 0xe11ab2833ee38b1aULL, /* GL_ARB_draw_buffers */
    /*  141 */ 0xae64ff49ea7e95afULL, /* GL_ARB_draw_buffers_blend */
    /*  142 */ 0xe8f87e4358abe5adULL, /* GL_ARB_draw_elements_base_vertex */
    /*  143 */ 0x115e5b64ca1e3904ULL, /* GL_ARB_draw_indirect */
    /*  144 */ 0x1b97c8e7f6e23b1dULL, /* GL_ARB_draw_instanced */
    /*  145 */ 0x43e30679379342ceULL, /* GL_ARB_enhanced_layouts */
    /*  146 */ 0xae63483486dde7caULL, /* GL_ARB_explicit_attrib_location */
    /*  147 */ 0x2024ab894c4d472eULL, /* GL_ARB_explicit_uniform_location */
    /*  148 */ 0x5f268b1f7c820480ULL, /* GL_ARB_fragment_coord_conventions */
    /*  149 */ 0x737ecdaaf0007debULL, /* GL_ARB_fragment_layer_viewport */
    /*  150 */ 0x73c41f19063c2fe6ULL, /* GL_ARB_fragment_program */
    /*  151 */ 0xefae304da60b251dULL, /* GL_ARB_fragment_program_shadow */
    /*  152 */ 0x52146e3d84c4168cULL, /* GL_ARB_fragment_shader */
    /*  153 */ 0x0c70408f81c04928ULL, /* GL_ARB_fragment_shader_interlock */
    /*  154 */ 0x2448dc255a192f81ULL, /* GL_ARB_framebuffer_no_attachments */
    /*  155 */ 0x1fbce4d5ca5a1f15ULL, /* GL_ARB_framebuffer_object */
    /*  156 */ 0x7423a1c932459ccaULL, /* GL_ARB_framebuffer_sRGB */
    /*  157 */ 0xf680b4cebba73b4eULL, /* GL_ARB_geometry_shader4 */
    /*  158 */ 0xa3d697b5a581321aULL, /* GL_ARB_get_program_binary */
    /*  159 */ 0xeff63c42ef3b05e6ULL, /* GL_ARB_get_texture_sub_image */
    /*  160 */ 0xea214db7cd5e19d1ULL, /* GL_ARB_gl_spirv */
    /*  161 */ 0x2c7de1df96f6285aULL, /* GL_ARB_gpu_shader5 */
    /*  162 */ 0x19c411e568c50761ULL, /* GL_ARB_gpu_shader_fp64 */
    /*  163 */ 0xbed2c39a8ee82e31ULL, /* GL_ARB_gpu_shader_int64 */
    /*  164 */ 0x54e0f735df67d1a9ULL, /* GL_ARB_half_float_pixel */
    /*  165 */ 0x49a053607b3fe223ULL, /* GL_ARB_half_float_vertex */
    /*  166 */ 0x4569da13c0840fbeULL, /* GL_ARB_imaging */
    /*  167 */ 0x3b7fae1bd2e0c889ULL, /* GL_ARB_indirect_parameters */
    /*  168 */ 0x3b10779fb6b7fcbbULL, /* GL_ARB_instanced_arrays */
    /*  169 */ 0xf96f1159070d5ce7ULL, /* GL_ARB_internalformat_query */
    /*  170 */ 0x80a297f08b3101dfULL, /* GL_ARB_internalformat_query2 */
    /*  171 */ 0x6a0e063354f3a32cULL, /* GL_ARB_invalidate_subdata */
    /*  172 */ 0x70a2bf7a3574e20fULL, /* GL_ARB_map_buffer_alignment */
    /*  173 */ 0xbf533265f999152cULL, /* GL_ARB_map_buffer_range */
    /*  174 */ 0xfbe76f26f72891f3ULL, /* GL_ARB_matrix_palette */
    /*  175 */ 0xc2eb1cf0ae1fb90bULL, /* GL_ARB_multi_bind */
    /*  176 */ 0x05681bd649da4453ULL, /* GL_ARB_multi_draw_indirect */
    /*  177 */ 0x494b5f42fc0a83e4ULL, /* GL_ARB_multisample */
    /*  178 */ 0x4a56c37f2c0b7aadULL, /* GL_ARB_multitexture */
    /*  179 */ 0xe8818f3733977678ULL, /* GL_ARB_occlusion_query */
    /*  180 */ 0x06e18ccc664317ebULL, /* GL_ARB_occlusion_query2 */
    /*  181 */ 0x5d7b0c48219844f4ULL, /* GL_ARB_parallel_shader_compile */
    /*  182 */ 0x6399433cf89bb920ULL, /* GL_ARB_pipeline_statistics_query */
    /*  183 */ 0xac3ec29ab5db4b9eULL, /* GL_ARB_pixel_buffer_object */
    /*  184 */ 0xffe8ee561ae2346cULL, /* GL_ARB_point_parameters */
    /*  185 */ 0xb48886ec024907bbULL, /* GL_ARB_point_sprite */
    /*  186 */ 0x0c2f051e773ac84aULL, /* GL_ARB_polygon_offset_clamp */
    /*  187 */ 0x94125022598b506eULL, /* GL_ARB_post_depth_coverage */
    /*  188 */ 0x680e7d29d6b97883ULL, /* GL_ARB_program_interface_query */
    /*  189 */ 0x028da0039f30b414ULL, /* GL_ARB_provoking_vertex */
    /*  190 */ 0x76c8a711474dcb0eULL, /* GL_ARB_query_buffer_object */
    /*  191 */ 0x4b042cda7a10234cULL, /* GL_ARB_robust_buffer_access_behavior */
    /*  192 */ 0x321298a6a261de34ULL, /* GL_ARB_robustness */
    /*  193 */ 0x945bce717134d350ULL, /* GL_ARB_robustness_isolation */
    /*  194 */ 0x94596e17ac6ec3c8ULL, /* GL_ARB_sample_locations */
    /*  195 */ 0x7870651576fc1ccdULL, /* GL_ARB_sample_shading */
    /*  196 */ 0x1db0e3c87246c7f7ULL, /* GL_ARB_sampler_objects */
    /*  197 */ 0x6d414fea6b2a0b05ULL, /* GL_ARB_seamless_cube_map */
    /*  198 */ 0xbe6ffda1c253ce69ULL, /* GL_ARB_seamless_cubemap_per_texture */
    /*  199 */ 0xf39b353f6c8d6795ULL, /* GL_ARB_separate_shader_objects */
    /*  200 */ 0x2c6b3e0ac4318eacULL, /* GL_ARB_shader_atomic_counter_ops */
    /*  201 */ 0x4d13222ef8dc85a8ULL, /* GL_ARB_shader_atomic_counters */
    /*  202 */ 0xb7f68cebd72707b2ULL, /* GL_ARB_shader_ballot */
    /*  203 */ 0x6157ef1dc9a5ec6aULL, /* GL_ARB_shader_bit_encoding */
    /*  204 */ 0x604fb19fc38ead7bULL, /* GL_ARB_shader_clock */
    /*  205 */ 0x44796ed6cecb76ddULL, /* GL_ARB_shader_draw_parameters */
    /*  206 */ 0x24f42ed6fd7e1224ULL, /* GL_ARB_shader_group_vote */
    /*  207 */ 0x8e1d8ffee2ffc980ULL, /* GL_ARB_shader_image_load_store */
    /*  208 */ 0x3c986ee0af879682ULL, /* GL_ARB_shader_image_size */
    /*  209 */ 0xd8de76a336031ff0ULL, /* GL_ARB_shader_objects */
    /*  210 */ 0x06bce3aace8af5a7ULL, /* GL_ARB_shader_precision */
    /*  211 */ 0x10bfd775e284ac36ULL, /* GL_ARB_shader_stencil_export */
    /*  212 */ 0x191e16f9c16a5423ULL, /* GL_ARB_shader_storage_buffer_object */
    /*  213 */ 0x9f832fb5b2517157ULL, /* GL_ARB_shader_subroutine */
    /*  214 */ 0xa53df22a8387d8c0ULL, /* GL_ARB_shader_texture_image_samples */
    /*  215 */ 0xfd460b3ffea5238eULL, /* GL_ARB_shader_texture_lod */
    /*  216 */ 0x3b0ccc78e1ae6cceULL, /* GL_ARB_shader_viewport_layer_array */
    /*  217 */ 0xf2d5eb1652b5c218ULL, /* GL_ARB_shading_language_100 */
    /*  218 */ 0x566b1b0b87fe805dULL, /* GL_ARB_shading_language_420pack */
    /*  219 */ 0x2f59115a058a0c1aULL, /* GL_ARB_shading_language_include */
    /*  220 */ 0x6c8387915ce0e735ULL, /* GL_ARB_shading_language_packing */
    /*  221 */ 0xd6597e1597f4f3cfULL, /* GL_ARB_shadow */
    /*  222 */ 0xecdc51a7a12e0820ULL, /* GL_ARB_shadow_ambient */
    /*  223 */ 0xcc6098f61c4e626aULL, /* GL_ARB_sparse_buffer */
    /*  224 */ 0xb8b8ba783156beb9ULL, /* GL_ARB_sparse_texture */
    /*  225 */ 0xa11019635b421922ULL, /* GL_ARB_sparse_texture2 */
    /*  226 */ 0x7dc85bdb35fadb35ULL, /* GL_ARB_sparse_texture_clamp */
    /*  227 */ 0xcf62e2741dd9a807ULL, /* GL_ARB_spirv_extensions */
    /*  228 */ 0xa56221685de2b254ULL, /* GL_ARB_stencil_texturing */
    /*  229 */ 0x0d3c113e7ffc3be4ULL, /* GL_ARB_sync */
    /*  230 */ 0xaefddf2f9dcfa46aULL, /* GL_ARB_tessellation_shader */
    /*  231 */ 0x9d0747678a9d3fdfULL, /* GL_ARB_texture_barrier */
    /*  232 */ 0xb4a8554df00d4edeULL, /* GL_ARB_texture_border_clamp */
    /*  233 */ 0xc59d9bef1f9b2de9ULL, /* GL_ARB_texture_buffer_object */
    /*  234 */ 0xbab79763204b079aULL, /* GL_ARB_texture_buffer_object_rgb32 */
    /*  235 */ 0x843bbbf9107595d8ULL, /* GL_ARB_texture_buffer_range */
    /*  236 */ 0x582477dc03c7221cULL, /* GL_ARB_texture_compression */
    /*  237 */ 0x83bfab2872b14819ULL, /* GL_ARB_texture_compression_bptc */
    /*  238 */ 0x5e62ceda4eb9b901ULL, /* GL_ARB_texture_compression_rgtc */
    /*  239 */ 0xac7bb6c963c7dd4cULL, /* GL_ARB_texture_cube_map */
    /*  240 */ 0x68d233a2df517789ULL, /* GL_ARB_texture_cube_map_array */
    /*  241 */ 0x9061271ef3971e4dULL, /* GL_ARB_texture_env_add */
    /*  242 */ 0x729ad094490ac067ULL, /* GL_ARB_texture_env_combine */
    /*  243 */ 0xc258a95e80a7ac1dULL, /* GL_ARB_texture_env_crossbar */
    /*  244 */ 0x87e8597c801caffbULL, /* GL_ARB_texture_env_dot3 */
    /*  245 */ 0xf8867e9b2392c62cULL, /* GL_ARB_texture_filter_anisotropic */
    /*  246 */ 0x9a2662f4f2a023fcULL, /* GL_ARB_texture_filter_minmax */
    /*  247 */ 0x6f4b69f418935051ULL, /* GL_ARB_texture_float */
    /*  248 */ 0xa57e1ab78c203089ULL, /* GL_ARB_texture_gather */
    /*  249 */ 0x7c5b8fd73b8f1d2aULL, /* GL_ARB_texture_mirror_clamp_to_edge */
    /*  250 */ 0x7f8109dad2ae72acULL, /* GL_ARB_texture_mirrored_repeat */
    /*  251 */ 0xce2742707049542eULL, /* GL_ARB_texture_multisample */
    /*  252 */ 0x39526d131df64c59ULL, /* GL_ARB_texture_non_power_of_two */
    /*  253 */ 0x46b457622b5dab21ULL, /* GL_ARB_texture_query_levels */
    /*  254 */ 0x0c5b6193b98fc63bULL, /* GL_ARB_texture_query_lod */
    /*  255 */ 0x5d6d6585c47fc200ULL, /* GL_ARB_texture_rectangle */
    /*  256 */ 0xb7acf24a6eb5a7f4ULL, /* GL_ARB_texture_rg */
    /*  257 */ 0x97b3807033cf6f62ULL, /* GL_ARB_texture_rgb10_a2ui */
    /*  258 */ 0x12a12b44ee899f08ULL, /* GL_ARB_texture_stencil8 */
    /*  259 */ 0x2bb0e7be62c590f8ULL, /* GL_ARB_texture_storage */
    /*  260 */ 0xeacfe755a96db7a7ULL, /* GL_ARB_texture_storage_multisample */
    /*  261 */ 0x421bedbb68fd4661ULL, /* GL_ARB_texture_swizzle */
    /*  262 */ 0x5b877369a37b65e6ULL, /* GL_ARB_texture_view */
    /*  263 */ 0x0d8a574b96669a1bULL, /* GL_ARB_timer_query */
    /*  264 */ 0xeaa1709ae2b12764ULL, /* GL_ARB_transform_feedback2 */
    /*  265 */ 0xfbc74ea814b15d2fULL, /* GL_ARB_transform_feedback3 */
    /*  266 */ 0x3f96154fd49046f3ULL, /* GL_ARB_transform_feedback_instanced */
    /*  267 */ 0xf54fc92b7e8ec635ULL, /* GL_ARB_transform_feedback_overflow_query */
    /*  268 */ 0x77013d69fddefe87ULL, /* GL_ARB_transpose_matrix */
    /*  269 */ 0x7f397ae5fad4b735ULL, /* GL_ARB_uniform_buffer_object */
    /*  270 */ 0x502a9d2c5469c136ULL, /* GL_ARB_vertex_array_bgra */
    /*  271 */ 0x1a1e2d3306313eb9ULL, /* GL_ARB_vertex_array_object */
    /*  272 */ 0x7b47ed54530d0661ULL, /* GL_ARB_vertex_attrib_64bit */
    /*  273 */ 0xe394a5028a00c565ULL, /* GL_ARB_vertex_attrib_binding */
    /*  274 */ 0xbe2f3323a7af4844ULL, /* GL_ARB_vertex_blend */
    /*  275 */ 0xab4f226cf8bf14b2ULL, /* GL_ARB_vertex_buffer_object */
    /*  276 */ 0x2b91406e8801f26dULL, /* GL_ARB_vertex_program */
    /*  277 */ 0xb74f5593e3c89e02ULL, /* GL_ARB_vertex_shader */
    /*  278 */ 0x5adbfa9b8494c869ULL, /* GL_ARB_vertex_type_10f_11f_11f_rev */
    /*  279 */ 0x70aa23c3893ff4f7ULL, /* GL_ARB_vertex_type_2_10_10_10_rev */
    /*  280 */ 0x11f657f3da3dbeb7ULL, /* GL_ARB_viewport_array */
    /*  281 */ 0x8fd0fb55626075a1ULL, /* GL_ARB_window_pos */
    /*  282 */ 0x6caeb7737f26924aULL, /* GL_ARM_cooperative_matrix_layouts */
    /*  283 */ 0x2fbeb7cb81220b5eULL, /* GL_ARM_mali_program_binary */
    /*  284 */ 0x174de60965d38c78ULL, /* GL_ARM_mali_shader_binary */
    /*  285 */ 0x0770bcbef6d87eccULL, /* GL_ARM_rgba8 */
    /*  286 */ 0xc97fd975c7c94d78ULL, /* GL_ARM_shader_core_builtins */
    /*  287 */ 0xd022cfc81a420445ULL, /* GL_ARM_shader_core_properties */
    /*  288 */ 0xf0d2f4cff333f04eULL, /* GL_ARM_shader_framebuffer_fetch */
    /*  289 */ 0xbfa10a2d7557623fULL, /* GL_ARM_shader_framebuffer_fetch_depth_stencil */
    /*  290 */ 0x8a7a1adbc8af57ffULL, /* GL_ARM_texture_unnormalized_coordinates */
    /*  291 */ 0xc43e90f15fb8db01ULL, /* GL_ATI_draw_buffers */
    /*  292 */ 0x237ddecca4711d26ULL, /* GL_ATI_element_array */
    /*  293 */ 0x8465366774288b57ULL, /* GL_ATI_envmap_bumpmap */
    /*  294 */ 0x7eace62f803a3a1dULL, /* GL_ATI_fragment_shader */
    /*  295 */ 0x601618adc78f06edULL, /* GL_ATI_map_object_buffer */
    /*  296 */ 0xc2367d65629265d3ULL, /* GL_ATI_meminfo */
    /*  297 */ 0x3ed6aa98977b6026ULL, /* GL_ATI_pixel_format_float */
    /*  298 */ 0xecc62354179a5498ULL, /* GL_ATI_pn_triangles */
    /*  299 */ 0xc9e128c539750596ULL, /* GL_ATI_separate_stencil */
    /*  300 */ 0xf8002b1602911364ULL, /* GL_ATI_text_fragment_shader */
    /*  301 */ 0x8f696d877000fa6aULL, /* GL_ATI_texture_env_combine3 */
    /*  302 */ 0x72137067e0c140bcULL, /* GL_ATI_texture_float */
    /*  303 */ 0x184114955f32fdedULL, /* GL_ATI_texture_mirror_once */
    /*  304 */ 0x99180d4f8d9c5d52ULL, /* GL_ATI_vertex_array_object */
    /*  305 */ 0x4bedffd7142a0313ULL, /* GL_ATI_vertex_attrib_array_object */
    /*  306 */ 0xf2a1201512faef81ULL, /* GL_ATI_vertex_streams */
    /*  307 */ 0x9a85b4342c34b2f8ULL, /* GL_CHROMIUM_bind_uniform_location */
    /*  308 */ 0x0dd808babc9daaabULL, /* GL_CHROMIUM_copy_compressed_texture */
    /*  309 */ 0xe6bdf6222c3733efULL, /* GL_CHROMIUM_copy_texture */
    /*  310 */ 0x0bd5e31cc0c829e7ULL, /* GL_CHROMIUM_framebuffer_mixed_samples */
    /*  311 */ 0x04af64470030272eULL, /* GL_CHROMIUM_lose_context */
    /*  312 */ 0x2b55ba018525895bULL, /* GL_DMP_program_binary */
    /*  313 */ 0x8e5f4ce24de544d5ULL, /* GL_DMP_shader_binary */
    /*  314 */ 0x0cf95c40c08a43a8ULL, /* GL_EXT_422_pixels */
    /*  315 */ 0x2a61d7b733e75c77ULL, /* GL_EXT_EGL_image_array */
    /*  316 */ 0x35b7bb88d6ff4a1eULL, /* GL_EXT_EGL_image_storage */
    /*  317 */ 0xfe8066998f34da8eULL, /* GL_EXT_EGL_image_storage_compression */
    /*  318 */ 0xb8221664855c83bdULL, /* GL_EXT_EGL_sync */
    /*  319 */ 0x6fac3cb4234e6c59ULL, /* GL_EXT_YUV_target */
    /*  320 */ 0xc118d96a66b6bea3ULL, /* GL_EXT_abgr */
    /*  321 */ 0x6b5e9b6cfbdc3dc0ULL, /* GL_EXT_base_instance */
    /*  322 */ 0x94adfa4ef027ccd6ULL, /* GL_EXT_bfloat16 */
    /*  323 */ 0x2c343f7622589325ULL, /* GL_EXT_bgra */
    /*  324 */ 0x9d83c1e02304fb00ULL, /* GL_EXT_bindable_uniform */
    /*  325 */ 0x1cafcd91efe0e1d6ULL, /* GL_EXT_blend_color */
    /*  326 */ 0x3510ec477f22f7e7ULL, /* GL_EXT_blend_equation_separate */
    /*  327 */ 0x888e740cefe39cc4ULL, /* GL_EXT_blend_func_extended */
    /*  328 */ 0x97c1a7c0b569dfb8ULL, /* GL_EXT_blend_func_separate */
    /*  329 */ 0x709f5d763ef0911fULL, /* GL_EXT_blend_logic_op */
    /*  330 */ 0x1163ab5d43e9b052ULL, /* GL_EXT_blend_minmax */
    /*  331 */ 0x2c5c11d0c1161814ULL, /* GL_EXT_blend_subtract */
    /*  332 */ 0x8a59c192ebd08825ULL, /* GL_EXT_buffer_reference */
    /*  333 */ 0x1fe18a884a2d4d2aULL, /* GL_EXT_buffer_reference2 */
    /*  334 */ 0xb839402fc769c51eULL, /* GL_EXT_buffer_reference_uvec2 */
    /*  335 */ 0xf57e9c9fe9c776cdULL, /* GL_EXT_buffer_storage */
    /*  336 */ 0xaafb791a26428890ULL, /* GL_EXT_clear_texture */
    /*  337 */ 0x9452d292aa14805eULL, /* GL_EXT_clip_control */
    /*  338 */ 0x5737e20452f91527ULL, /* GL_EXT_clip_cull_distance */
    /*  339 */ 0x56a5c2f21e51bb5aULL, /* GL_EXT_clip_volume_hint */
    /*  340 */ 0x82b62c808e4abb64ULL, /* GL_EXT_cmyka */
    /*  341 */ 0xa297c2c3a49a99beULL, /* GL_EXT_color_buffer_float */
    /*  342 */ 0xf9449646b78eab54ULL, /* GL_EXT_color_buffer_half_float */
    /*  343 */ 0x6d76340b1318b839ULL, /* GL_EXT_color_subtable */
    /*  344 */ 0xf1bda7fa0a83d383ULL, /* GL_EXT_compiled_vertex_array */
    /*  345 */ 0x9ddf99bdc50f4149ULL, /* GL_EXT_conservative_depth */
    /*  346 */ 0x354415fe7a6e013eULL, /* GL_EXT_control_flow_attributes */
    /*  347 */ 0x04f0f0ce501bd29dULL, /* GL_EXT_control_flow_attributes2 */
    /*  348 */ 0xe9260724f594f80bULL, /* GL_EXT_convolution */
    /*  349 */ 0xf9792a196e0ab7c9ULL, /* GL_EXT_coordinate_frame */
    /*  350 */ 0xa26b121ae33c3436ULL, /* GL_EXT_copy_image */
    /*  351 */ 0x2611c2618f21aa2fULL, /* GL_EXT_copy_texture */
    /*  352 */ 0xddfc92096368bfbbULL, /* GL_EXT_cull_vertex */
    /*  353 */ 0xed15a3d914865c56ULL, /* GL_EXT_debug_label */
    /*  354 */ 0x84891a2031a0f162ULL, /* GL_EXT_debug_marker */
    /*  355 */ 0x3d46dbc8319361c9ULL, /* GL_EXT_debug_printf */
    /*  356 */ 0x2a423943f8be1307ULL, /* GL_EXT_demote_to_helper_invocation */
    /*  357 */ 0xe21a2b607eb5c6bbULL, /* GL_EXT_depth_bounds_test */
    /*  358 */ 0xdc5fb3a8d43d753eULL, /* GL_EXT_depth_clamp */
    /*  359 */ 0xee026f0d1b48c324ULL, /* GL_EXT_device_group */
    /*  360 */ 0xff4a74da40c62745ULL, /* GL_EXT_direct_state_access */
    /*  361 */ 0x3287a129fb1e11c1ULL, /* GL_EXT_discard_framebuffer */
    /*  362 */ 0x3d06b0f91612d10dULL, /* GL_EXT_disjoint_timer_query */
    /*  363 */ 0xd3ac9ca278a62f1aULL, /* GL_EXT_draw_buffers */
    /*  364 */ 0x5d6aa36dbdce372dULL, /* GL_EXT_draw_buffers2 */
    /*  365 */ 0x997893a6ac44f7feULL, /* GL_EXT_draw_buffers_indexed */
    /*  366 */ 0x548657f15226635bULL, /* GL_EXT_draw_elements_base_vertex */
    /*  367 */ 0xeb1b622faf7697c7ULL, /* GL_EXT_draw_instanced */
    /*  368 */ 0xbb5e6eb0e1559ef1ULL, /* GL_EXT_draw_range_elements */
    /*  369 */ 0x0ccbfada83c13182ULL, /* GL_EXT_draw_transform_feedback */
    /*  370 */ 0xa3176575cdaf6f54ULL, /* GL_EXT_expect_assume */
    /*  371 */ 0x5e1ad5852ce64f31ULL, /* GL_EXT_external_buffer */
    /*  372 */ 0x31e50bc0029e76b2ULL, /* GL_EXT_float8_e5m2_e4m3 */
    /*  373 */ 0x18d7b8f80d477ce9ULL, /* GL_EXT_float_blend */
    /*  374 */ 0xe09e32cd1ae79288ULL, /* GL_EXT_fog_coord */
    /*  375 */ 0xc117232bce18d68eULL, /* GL_EXT_fragment_invocation_density */
    /*  376 */ 0x2f9b21678a5e0043ULL, /* GL_EXT_fragment_shader_barycentric */
    /*  377 */ 0xde0a545f611c91b2ULL, /* GL_EXT_fragment_shading_rate */
    /*  378 */ 0xdefc19d979b2e3e2ULL, /* GL_EXT_framebuffer_blit */
    /*  379 */ 0x616048bcd1aa9223ULL, /* GL_EXT_framebuffer_blit_layers */
    /*  380 */ 0x8cbb2537704d8953ULL, /* GL_EXT_framebuffer_multisample */
    /*  381 */ 0x5634f30b2756d601ULL, /* GL_EXT_framebuffer_multisample_blit_scaled */
    /*  382 */ 0x8350f19ac13e7c07ULL, /* GL_EXT_framebuffer_object */
    /*  383 */ 0xa45a63878264c1e5ULL, /* GL_EXT_framebuffer_sRGB */
    /*  384 */ 0x30d017755de50dd9ULL, /* GL_EXT_geometry_point_size */
    /*  385 */ 0xfa22129bb4d04128ULL, /* GL_EXT_geometry_shader */
    /*  386 */ 0x5370f0fbdd1b1f1dULL, /* GL_EXT_geometry_shader4 */
    /*  387 */ 0x3604f5b2b65016b2ULL, /* GL_EXT_gpu_program_parameters */
    /*  388 */ 0x020c60828c37ce5dULL, /* GL_EXT_gpu_shader4 */
    /*  389 */ 0x53dbe9871073dca3ULL, /* GL_EXT_gpu_shader5 */
    /*  390 */ 0xcebb9285fc482cfdULL, /* GL_EXT_histogram */
    /*  391 */ 0x64ea7e43377361ffULL, /* GL_EXT_index_array_formats */
    /*  392 */ 0xecf771ddabe3f8edULL, /* GL_EXT_index_func */
    /*  393 */ 0x649623e695acbfb0ULL, /* GL_EXT_index_material */
    /*  394 */ 0x43fd3f035960e92cULL, /* GL_EXT_index_texture */
    /*  395 */ 0x9c3c026caab1aaf7ULL, /* GL_EXT_instanced_arrays */
    /*  396 */ 0x82ec9e979f47f3ddULL, /* GL_EXT_integer_dot_product */
    /*  397 */ 0x6b0a475df16ae9f2ULL, /* GL_EXT_light_texture */
    /*  398 */ 0xf41152d50d03cc16ULL, /* GL_EXT_map_buffer_range */
    /*  399 */ 0xdea398d907b668d0ULL, /* GL_EXT_maximal_reconvergence */
    /*  400 */ 0xebb55934637c6ab7ULL, /* GL_EXT_memory_object */
    /*  401 */ 0x7e941665b79d31c4ULL, /* GL_EXT_memory_object_fd */
    /*  402 */ 0x6bf3a6b6ec24354bULL, /* GL_EXT_memory_object_win32 */
    /*  403 */ 0x67079bf943104541ULL, /* GL_EXT_mesh_shader */
    /*  404 */ 0xda6fb882011aa28eULL, /* GL_EXT_misc_attribute */
    /*  405 */ 0x6077bed8aa109362ULL, /* GL_EXT_multi_draw_arrays */
    /*  406 */ 0x55b4806b38f2b08eULL, /* GL_EXT_multi_draw_indirect */
    /*  407 */ 0x872a66595e5024caULL, /* GL_EXT_multisample */
    /*  408 */ 0x3e4a3b0ff8584927ULL, /* GL_EXT_multisampled_compatibility */
    /*  409 */ 0x33b89ab037aed106ULL, /* GL_EXT_multisampled_render_to_texture */
    /*  410 */ 0x39f0379607d459f0ULL, /* GL_EXT_multisampled_render_to_texture2 */
    /*  411 */ 0x49f63d58daabfccbULL, /* GL_EXT_multiview_draw_buffers */
    /*  412 */ 0x5b7a6a36ed0fe897ULL, /* GL_EXT_multiview_tessellation_geometry_shader */
    /*  413 */ 0x3679a0ac14e16e97ULL, /* GL_EXT_multiview_texture_multisample */
    /*  414 */ 0x39d0f3848228d38fULL, /* GL_EXT_multiview_timer_query */
    /*  415 */ 0x02a2910cd422340eULL, /* GL_EXT_nontemporal_keyword */
    /*  416 */ 0x0d7bdf1d96e54238ULL, /* GL_EXT_nonuniform_qualifier */
    /*  417 */ 0xff653ce0c16c5c81ULL, /* GL_EXT_null_initializer */
    /*  418 */ 0xbf12db2b88c87ccfULL, /* GL_EXT_occlusion_query_boolean */
    /*  419 */ 0x927980c53f038149ULL, /* GL_EXT_opacity_micromap */
    /*  420 */ 0x757af2451eae9d25ULL, /* GL_EXT_packed_depth_stencil */
    /*  421 */ 0x2ace1d8656332b56ULL, /* GL_EXT_packed_float */
    /*  422 */ 0x248d529c3993285cULL, /* GL_EXT_packed_pixels */
    /*  423 */ 0xecd5d2503b35bb13ULL, /* GL_EXT_paletted_texture */
    /*  424 */ 0xc7f3ad7137661622ULL, /* GL_EXT_pixel_buffer_object */
    /*  425 */ 0x59d7be95f9b27b9aULL, /* GL_EXT_pixel_transform */
    /*  426 */ 0xd7024b008ea1463bULL, /* GL_EXT_pixel_transform_color_table */
    /*  427 */ 0x14eaf45986c9bfa1ULL, /* GL_EXT_point_parameters */
    /*  428 */ 0x5640aa3e3a0202cbULL, /* GL_EXT_polygon_offset */
    /*  429 */ 0xd55f7ac9bd1eba74ULL, /* GL_EXT_polygon_offset_clamp */
    /*  430 */ 0x55695328ecdeb972ULL, /* GL_EXT_post_depth_coverage */
    /*  431 */ 0x849565c10789238eULL, /* GL_EXT_primitive_bounding_box */
    /*  432 */ 0x638afa82b47ca539ULL, /* GL_EXT_protected_textures */
    /*  433 */ 0xfc1cd6391217f09eULL, /* GL_EXT_provoking_vertex */
    /*  434 */ 0xc36c4a5ae294a717ULL, /* GL_EXT_pvrtc_sRGB */
    /*  435 */ 0x864a43fa5616bb8cULL, /* GL_EXT_raster_multisample */
    /*  436 */ 0xb0b19c0e9f3b0f5cULL, /* GL_EXT_ray_cull_mask */
    /*  437 */ 0xd982b05f307f6fcdULL, /* GL_EXT_ray_flags_primitive_culling */
    /*  438 */ 0xbf4a58353f9a7a75ULL, /* GL_EXT_ray_query */
    /*  439 */ 0x5d7ccf8ac93b7140ULL, /* GL_EXT_ray_tracing */
    /*  440 */ 0x98b5a9c9f9d792ddULL, /* GL_EXT_ray_tracing_position_fetch */
    /*  441 */ 0x1b664521b8e7ceddULL, /* GL_EXT_read_format_bgra */
    /*  442 */ 0x461ed0af7d9ee57eULL, /* GL_EXT_render_snorm */
    /*  443 */ 0xc99a47326d03fd17ULL, /* GL_EXT_rescale_normal */
    /*  444 */ 0x04aaf7c50fd23609ULL, /* GL_EXT_robustness */
    /*  445 */ 0x72a714dfac11ff63ULL, /* GL_EXT_sRGB */
    /*  446 */ 0xa329e9d07bf41faaULL, /* GL_EXT_sRGB_write_control */
    /*  447 */ 0x6c203c99634fa814ULL, /* GL_EXT_samplerless_texture_functions */
    /*  448 */ 0xe045958c8c43c35fULL, /* GL_EXT_scalar_block_layout */
    /*  449 */ 0x5da9f01e568b2e0bULL, /* GL_EXT_secondary_color */
    /*  450 */ 0x40ea8dbcbb4d106fULL, /* GL_EXT_semaphore */
    /*  451 */ 0xb3de6f78cadcbed7ULL, /* GL_EXT_semaphore_fd */
    /*  452 */ 0xd80cf52931619f45ULL, /* GL_EXT_semaphore_win32 */
    /*  453 */ 0xde7c2e65ed21d1e7ULL, /* GL_EXT_separate_depth_stencil */
    /*  454 */ 0xb207ff65f8bf495dULL, /* GL_EXT_separate_shader_objects */
    /*  455 */ 0xeb07329b2f67d2ecULL, /* GL_EXT_separate_specular_color */
    /*  456 */ 0x49d751ecfad21a12ULL, /* GL_EXT_shader_16bit_storage */
    /*  457 */ 0x9861ec1bd88d15cfULL, /* GL_EXT_shader_8bit_storage */
    /*  458 */ 0x71c6281257d16bdfULL, /* GL_EXT_shader_atomic_float */
    /*  459 */ 0x3b6516e3dbabfb91ULL, /* GL_EXT_shader_atomic_float2 */
    /*  460 */ 0x59bd13c26a6e0f68ULL, /* GL_EXT_shader_atomic_int64 */
    /*  461 */ 0x6e599868ea3a939fULL, /* GL_EXT_shader_explicit_arithmetic_types */
    /*  462 */ 0x38889dc6669f650dULL, /* GL_EXT_shader_explicit_arithmetic_types_float16 */
    /*  463 */ 0x935e023eaa3a09f7ULL, /* GL_EXT_shader_explicit_arithmetic_types_float32 */
    /*  464 */ 0x898fe8394abadf05ULL, /* GL_EXT_shader_explicit_arithmetic_types_float64 */
    /*  465 */ 0x9177b5f32c341f00ULL, /* GL_EXT_shader_explicit_arithmetic_types_int16 */
    /*  466 */ 0x974487e410e50b66ULL, /* GL_EXT_shader_explicit_arithmetic_types_int32 */
    /*  467 */ 0x6cf4f9de748703f8ULL, /* GL_EXT_shader_explicit_arithmetic_types_int64 */
    /*  468 */ 0x43904cfef5f6138eULL, /* GL_EXT_shader_explicit_arithmetic_types_int8 */
    /*  469 */ 0x86da0f80c54cef33ULL, /* GL_EXT_shader_framebuffer_fetch */
    /*  470 */ 0xcd3c990c9f8c0a64ULL, /* GL_EXT_shader_framebuffer_fetch_non_coherent */
    /*  471 */ 0x17434ddfdf3a5893ULL, /* GL_EXT_shader_group_vote */
    /*  472 */ 0xeab14f8fb076d3f3ULL, /* GL_EXT_shader_image_int64 */
    /*  473 */ 0xc1de48ba5bbf7b01ULL, /* GL_EXT_shader_image_load_formatted */
    /*  474 */ 0x6ab82341e3e65156ULL, /* GL_EXT_shader_image_load_store */
    /*  475 */ 0xe19d3a68c60c0ef4ULL, /* GL_EXT_shader_implicit_conversions */
    /*  476 */ 0x033287cccf9a6962ULL, /* GL_EXT_shader_integer_mix */
    /*  477 */ 0xd055bdf912abe3b0ULL, /* GL_EXT_shader_io_blocks */
    /*  478 */ 0x07975202b868bf83ULL, /* GL_EXT_shader_non_constant_global_initializers */
    /*  479 */ 0x49f7e4529e189129ULL, /* GL_EXT_shader_pixel_local_storage */
    /*  480 */ 0x28720bf0be8ab661ULL, /* GL_EXT_shader_pixel_local_storage2 */
    /*  481 */ 0x9b3693eac0a5b344ULL, /* GL_EXT_shader_quad_control */
    /*  482 */ 0x28c00ec379a98b9dULL, /* GL_EXT_shader_realtime_clock */
    /*  483 */ 0x3ef958340d410019ULL, /* GL_EXT_shader_samples_identical */
    /*  484 */ 0xa3a7633df81fa8b1ULL, /* GL_EXT_shader_subgroup_extended_types */
    /*  485 */ 0xdb7ea225c0575a72ULL, /* GL_EXT_shader_subgroup_extended_types_float16 */
    /*  486 */ 0x50620210b36d2a7eULL, /* GL_EXT_shader_subgroup_extended_types_int16 */
    /*  487 */ 0xcaf721268b43e997ULL, /* GL_EXT_shader_subgroup_extended_types_int64 */
    /*  488 */ 0x6de284e02f65aff5ULL, /* GL_EXT_shader_subgroup_extended_types_int8 */
    /*  489 */ 0x0fbf30e41210d727ULL, /* GL_EXT_shader_texture_lod */
    /*  490 */ 0x9383bd5e3c4d02ceULL, /* GL_EXT_shader_texture_samples */
    /*  491 */ 0x0e7ba3c5e5be8403ULL, /* GL_EXT_shader_tile_image */
    /*  492 */ 0xe504594d7646deb5ULL, /* GL_EXT_shadow_funcs */
    /*  493 */ 0x7c7d332de021da36ULL, /* GL_EXT_shadow_samplers */
    /*  494 */ 0x4851b197319900c7ULL, /* GL_EXT_shared_memory_block */
    /*  495 */ 0xa39da1f69d0cad57ULL, /* GL_EXT_shared_texture_palette */
    /*  496 */ 0x86ac1bf74755a73bULL, /* GL_EXT_sparse_texture */
    /*  497 */ 0x81ed537411dae865ULL, /* GL_EXT_sparse_texture2 */
    /*  498 */ 0x3e990113969288c9ULL, /* GL_EXT_spec_constant_composites */
    /*  499 */ 0x5d049f1a9498df05ULL, /* GL_EXT_spirv_intrinsics */
    /*  500 */ 0xe20fb1c3faf6f7d8ULL, /* GL_EXT_stencil_clear_tag */
    /*  501 */ 0x629c334d67e5c718ULL, /* GL_EXT_stencil_two_side */
    /*  502 */ 0x961b80206055e672ULL, /* GL_EXT_stencil_wrap */
    /*  503 */ 0x8a56add0af10cbb6ULL, /* GL_EXT_subgroup_uniform_control_flow */
    /*  504 */ 0xf85c8111e381b059ULL, /* GL_EXT_subgroupuniform_qualifier */
    /*  505 */ 0xe101571ccdddbe44ULL, /* GL_EXT_subtexture */
    /*  506 */ 0x80fb7149e30bd23aULL, /* GL_EXT_terminate_invocation */
    /*  507 */ 0x9e9a449841a4392bULL, /* GL_EXT_tessellation_point_size */
    /*  508 */ 0xa694e21c70c92ac7ULL, /* GL_EXT_tessellation_shader */
    /*  509 */ 0x7893ebdfb50f10a6ULL, /* GL_EXT_texture */
    /*  510 */ 0x3c1975837c97841bULL, /* GL_EXT_texture3D */
    /*  511 */ 0x2e4c3fc71fe20a24ULL, /* GL_EXT_texture_array */
    /*  512 */ 0xf02848fc36653917ULL, /* GL_EXT_texture_border_clamp */
    /*  513 */ 0x990b742e339cfdabULL, /* GL_EXT_texture_buffer */
    /*  514 */ 0xe30b1bf963964b94ULL, /* GL_EXT_texture_buffer_object */
    /*  515 */ 0x7c8af8bc6e29a35bULL, /* GL_EXT_texture_compression_astc_decode_mode */
    /*  516 */ 0x8c12f4a29dd9872dULL, /* GL_EXT_texture_compression_bptc */
    /*  517 */ 0x42f4b0934de6c2dcULL, /* GL_EXT_texture_compression_dxt1 */
    /*  518 */ 0x789187ec36c3334eULL, /* GL_EXT_texture_compression_latc */
    /*  519 */ 0x6d7076425ffdf707ULL, /* GL_EXT_texture_compression_rgtc */
    /*  520 */ 0x675e8f3271d1d5caULL, /* GL_EXT_texture_compression_s3tc */
    /*  521 */ 0x747ed54119078205ULL, /* GL_EXT_texture_compression_s3tc_srgb */
    /*  522 */ 0x511d1308a8dfc13fULL, /* GL_EXT_texture_cube_map */
    /*  523 */ 0x143e4c21a6ff53ccULL, /* GL_EXT_texture_cube_map_array */
    /*  524 */ 0xd7d84a9c353851fdULL, /* GL_EXT_texture_env_add */
    /*  525 */ 0x9d216b7a877bbcfbULL, /* GL_EXT_texture_env_combine */
    /*  526 */ 0x4bacf852b1cc1a43ULL, /* GL_EXT_texture_env_dot3 */
    /*  527 */ 0xeafde92a9cccc4edULL, /* GL_EXT_texture_filter_anisotropic */
    /*  528 */ 0x7738fa89f1d13a13ULL, /* GL_EXT_texture_filter_minmax */
    /*  529 */ 0x39751dec512ae77cULL, /* GL_EXT_texture_format_BGRA8888 */
    /*  530 */ 0xeb53a2bedf43571dULL, /* GL_EXT_texture_format_sRGB_override */
    /*  531 */ 0xaf09c3ff42c89eb5ULL, /* GL_EXT_texture_integer */
    /*  532 */ 0x41cf52695838c61cULL, /* GL_EXT_texture_lod_bias */
    /*  533 */ 0x17fb25156306ea61ULL, /* GL_EXT_texture_mirror_clamp */
    /*  534 */ 0x9a5a807af7e26b3fULL, /* GL_EXT_texture_mirror_clamp_to_edge */
    /*  535 */ 0x94b22c00bec3e518ULL, /* GL_EXT_texture_norm16 */
    /*  536 */ 0x10827f593acd1ba7ULL, /* GL_EXT_texture_object */
    /*  537 */ 0xbdcbb1418f18d3a4ULL, /* GL_EXT_texture_offset_non_const */
    /*  538 */ 0x971e595b62f38066ULL, /* GL_EXT_texture_perturb_normal */
    /*  539 */ 0x1e6eaad4a57ca1b5ULL, /* GL_EXT_texture_query_lod */
    /*  540 */ 0x95f0b0bc421f25d3ULL, /* GL_EXT_texture_rg */
    /*  541 */ 0xd43be8ff9c7c7adaULL, /* GL_EXT_texture_sRGB */
    /*  542 */ 0xfe62dc3d8ab9f10bULL, /* GL_EXT_texture_sRGB_R8 */
    /*  543 */ 0xcb6984e200d35ff9ULL, /* GL_EXT_texture_sRGB_RG8 */
    /*  544 */ 0x2b44a8b2473d6e5fULL, /* GL_EXT_texture_sRGB_decode */
    /*  545 */ 0x127856e58a250c1bULL, /* GL_EXT_texture_shadow_lod */
    /*  546 */ 0x30a7dd27a9ac5760ULL, /* GL_EXT_texture_shared_exponent */
    /*  547 */ 0xa2f8f4e45d997df3ULL, /* GL_EXT_texture_snorm */
    /*  548 */ 0x154c4c8b80533dc0ULL, /* GL_EXT_texture_storage */
    /*  549 */ 0x8768e67dadd2a7fdULL, /* GL_EXT_texture_storage_compression */
    /*  550 */ 0x183ae240682f4ad7ULL, /* GL_EXT_texture_swizzle */
    /*  551 */ 0x4a802d8de71af8e9ULL, /* GL_EXT_texture_type_2_10_10_10_REV */
    /*  552 */ 0x19afe800141638dcULL, /* GL_EXT_texture_view */
    /*  553 */ 0x4ab0caa70a996495ULL, /* GL_EXT_timer_query */
    /*  554 */ 0x471536c0a27f5c81ULL, /* GL_EXT_transform_feedback */
    /*  555 */ 0x1675c7c13b385f42ULL, /* GL_EXT_unpack_subimage */
    /*  556 */ 0x2347ebc551d02975ULL, /* GL_EXT_vertex_array */
    /*  557 */ 0xc5160cefc841200dULL, /* GL_EXT_vertex_array_bgra */
    /*  558 */ 0xfe8f41c3d0888d86ULL, /* GL_EXT_vertex_attrib_64bit */
    /*  559 */ 0x10ce9358a245f782ULL, /* GL_EXT_vertex_shader */
    /*  560 */ 0x80e4c2ee68e62a5fULL, /* GL_EXT_vertex_weighting */
    /*  561 */ 0x71431741b9e82753ULL, /* GL_EXT_vulkan_glsl_relaxed */
    /*  562 */ 0xb7046ff80ce07f1aULL, /* GL_EXT_win32_keyed_mutex */
    /*  563 */ 0x225b607d5cdf07d5ULL, /* GL_EXT_window_rectangles */
    /*  564 */ 0x80306c2b70f53adaULL, /* GL_EXT_x11_sync_object */
    /*  565 */ 0xaf38ae454737b45aULL, /* GL_FJ_shader_binary_GCCSO */
    /*  566 */ 0x776d5f9ce5dc30adULL, /* GL_GREMEDY_frame_terminator */
    /*  567 */ 0x2b64919ae0d632d6ULL, /* GL_GREMEDY_string_marker */
    /*  568 */ 0x4ba0a53809cd8e1cULL, /* GL_HP_convolution_border_modes */
    /*  569 */ 0x175101ef679b74d1ULL, /* GL_HP_image_transform */
    /*  570 */ 0x21db09dff47e8865ULL, /* GL_HP_occlusion_test */
    /*  571 */ 0xbccb311192bef9fcULL, /* GL_HP_texture_lighting */
    /*  572 */ 0x3f692d999fbf45a2ULL, /* GL_HUAWEI_cluster_culling_shader */
    /*  573 */ 0xf5546e69b4a74cb1ULL, /* GL_HUAWEI_program_binary */
    /*  574 */ 0x1ca5a9610adbc615ULL, /* GL_HUAWEI_shader_binary */
    /*  575 */ 0x01088281231ac4b3ULL, /* GL_HUAWEI_subpass_shading */
    /*  576 */ 0x052c78ec9092b2bcULL, /* GL_IBM_cull_vertex */
    /*  577 */ 0xbed7db565a3dcdb1ULL, /* GL_IBM_multimode_draw_arrays */
    /*  578 */ 0xb0a341b3ba34bde7ULL, /* GL_IBM_rasterpos_clip */
    /*  579 */ 0xe5d4e67e743793afULL, /* GL_IBM_static_data */
    /*  580 */ 0x42e7c1e06f5230cbULL, /* GL_IBM_texture_mirrored_repeat */
    /*  581 */ 0x3801878506a0d3e5ULL, /* GL_IBM_vertex_array_lists */
    /*  582 */ 0xe966fe12585d0ee3ULL, /* GL_IMG_bindless_texture */
    /*  583 */ 0xee05cb0623b18588ULL, /* GL_IMG_framebuffer_downsample */
    /*  584 */ 0x6cd4bff21f14cba9ULL, /* GL_IMG_multisampled_render_to_texture */
    /*  585 */ 0x10eae89c21411416ULL, /* GL_IMG_program_binary */
    /*  586 */ 0xe1d246c5f2217570ULL, /* GL_IMG_read_format */
    /*  587 */ 0x631524850de59dddULL, /* GL_IMG_shader_binary */
    /*  588 */ 0x26bbd5573ad61282ULL, /* GL_IMG_texture_compression_pvrtc */
    /*  589 */ 0x46869091dbce71a6ULL, /* GL_IMG_texture_compression_pvrtc2 */
    /*  590 */ 0xd44d6d9763e6fd68ULL, /* GL_IMG_texture_filter_cubic */
    /*  591 */ 0xf8c1cfe37858c556ULL, /* GL_INGR_blend_func_separate */
    /*  592 */ 0x9d3ca51fe0f2a837ULL, /* GL_INGR_color_clamp */
    /*  593 */ 0x231c00090b681c01ULL, /* GL_INGR_interlace_read */
    /*  594 */ 0xc0f54564fa652ebaULL, /* GL_INTEL_blackhole_render */
    /*  595 */ 0x8cfa061f6a006e62ULL, /* GL_INTEL_conservative_rasterization */
    /*  596 */ 0x693a15be925d42bbULL, /* GL_INTEL_fragment_shader_ordering */
    /*  597 */ 0x14386616e0282da8ULL, /* GL_INTEL_framebuffer_CMAA */
    /*  598 */ 0xfe0a30102b2b7f11ULL, /* GL_INTEL_map_texture */
    /*  599 */ 0x6d9138f92a97a9b2ULL, /* GL_INTEL_parallel_arrays */
    /*  600 */ 0x331d1b2f1d575bd8ULL, /* GL_INTEL_performance_query */
    /*  601 */ 0x898f16e7a19612feULL, /* GL_KHR_blend_equation_advanced */
    /*  602 */ 0xa66b25957f58c923ULL, /* GL_KHR_blend_equation_advanced_coherent */
    /*  603 */ 0x0956a658c75ab600ULL, /* GL_KHR_context_flush_control */
    /*  604 */ 0x836eea06917bcccbULL, /* GL_KHR_cooperative_matrix */
    /*  605 */ 0x5e0c5b9607ac8784ULL, /* GL_KHR_debug */
    /*  606 */ 0x08ce79df715e69dcULL, /* GL_KHR_memory_scope_semantics */
    /*  607 */ 0x12316ddfcc85238eULL, /* GL_KHR_no_error */
    /*  608 */ 0x3406b66e92343753ULL, /* GL_KHR_parallel_shader_compile */
    /*  609 */ 0xfa6bb57654b50c92ULL, /* GL_KHR_robust_buffer_access_behavior */
    /*  610 */ 0x474beac5f6910636ULL, /* GL_KHR_robustness */
    /*  611 */ 0x65263f2081d063e7ULL, /* GL_KHR_shader_subgroup */
    /*  612 */ 0x877be0bdc1f8d36cULL, /* GL_KHR_shader_subgroup_arithmetic */
    /*  613 */ 0x61e703f91e0948f3ULL, /* GL_KHR_shader_subgroup_ballot */
    /*  614 */ 0x5b9c554fd0d5a036ULL, /* GL_KHR_shader_subgroup_basic */
    /*  615 */ 0xe1044b09af95d72aULL, /* GL_KHR_shader_subgroup_clustered */
    /*  616 */ 0x4b76468cfb09dabcULL, /* GL_KHR_shader_subgroup_quad */
    /*  617 */ 0x55436fcdf6a6d27dULL, /* GL_KHR_shader_subgroup_rotate */
    /*  618 */ 0xaa09aac681765f3aULL, /* GL_KHR_shader_subgroup_shuffle */
    /*  619 */ 0x56a562daeb0a2f26ULL, /* GL_KHR_shader_subgroup_shuffle_relative */
    /*  620 */ 0x85bb9015d69ab32dULL, /* GL_KHR_shader_subgroup_vote */
    /*  621 */ 0x24c80aab81e859b3ULL, /* GL_KHR_texture_compression_astc_hdr */
    /*  622 */ 0x16f59295398b9d0aULL, /* GL_KHR_texture_compression_astc_ldr */
    /*  623 */ 0xa4a29c6f56f2023eULL, /* GL_KHR_texture_compression_astc_sliced_3d */
    /*  624 */ 0xcbbacf3d7c96adccULL, /* GL_KHR_vulkan_glsl */
    /*  625 */ 0x70bbb44bbc67a914ULL, /* GL_MESAX_texture_stack */
    /*  626 */ 0x4b833beb1f90e758ULL, /* GL_MESA_bgra */
    /*  627 */ 0xf9cfb61b2f897c12ULL, /* GL_MESA_framebuffer_flip_x */
    /*  628 */ 0xdf842b85f40b8f2dULL, /* GL_MESA_framebuffer_flip_y */
    /*  629 */ 0xc735e4d56089513eULL, /* GL_MESA_framebuffer_swap_xy */
    /*  630 */ 0x208599190bbb22ccULL, /* GL_MESA_map_buffer_client_pointer */
    /*  631 */ 0xac7eeedfea22e53dULL, /* GL_MESA_pack_invert */
    /*  632 */ 0xe164dc7b3064a548ULL, /* GL_MESA_program_binary_formats */
    /*  633 */ 0x39376b06206502d6ULL, /* GL_MESA_resize_buffers */
    /*  634 */ 0xa14ebc048c19e849ULL, /* GL_MESA_sampler_objects */
    /*  635 */ 0x58e3c24874e50b2fULL, /* GL_MESA_shader_integer_functions */
    /*  636 */ 0x7148e64fc5eef950ULL, /* GL_MESA_texture_const_bandwidth */
    /*  637 */ 0x8ee739e5f4f16337ULL, /* GL_MESA_tile_raster_order */
    /*  638 */ 0x00063de42ab739f6ULL, /* GL_MESA_window_pos */
    /*  639 */ 0x05840d0e5ebfdb5dULL, /* GL_MESA_ycbcr_texture */
    /*  640 */ 0x210f54fb5023bd27ULL, /* GL_NVX_blend_equation_advanced_multi_draw_buffers */
    /*  641 */ 0xdb3d40c973a8401dULL, /* GL_NVX_conditional_render */
    /*  642 */ 0xdba64e974cfda98bULL, /* GL_NVX_gpu_memory_info */
    /*  643 */ 0xfadb1fc8cec16ab6ULL, /* GL_NVX_gpu_multicast2 */
    /*  644 */ 0xcd2e0dc9329fd277ULL, /* GL_NVX_linked_gpu_multicast */
    /*  645 */ 0xd9dac6ae420f2bc1ULL, /* GL_NVX_multiview_per_view_attributes */
    /*  646 */ 0xd0ab24d9b21b5714ULL, /* GL_NVX_progress_fence */
    /*  647 */ 0xf60ebf70e765dadeULL, /* GL_NV_alpha_to_coverage_dither_control */
    /*  648 */ 0x0125c6b149dc763dULL, /* GL_NV_bindless_multi_draw_indirect */
    /*  649 */ 0xbf25dd3d5b684860ULL, /* GL_NV_bindless_multi_draw_indirect_count */
    /*  650 */ 0xfe0701cf0661b283ULL, /* GL_NV_bindless_texture */
    /*  651 */ 0xdfb2fe6dc8d05e7bULL, /* GL_NV_blend_equation_advanced */
    /*  652 */ 0x93143e8adaf57589ULL, /* GL_NV_blend_equation_advanced_coherent */
    /*  653 */ 0xea9c32d0ef37492eULL, /* GL_NV_blend_minmax_factor */
    /*  654 */ 0xcfb887fc69ba21e3ULL, /* GL_NV_blend_square */
    /*  655 */ 0xa4c52c3b41a4fcadULL, /* GL_NV_clip_space_w_scaling */
    /*  656 */ 0xd5cc92349ed5c556ULL, /* GL_NV_cluster_acceleration_structure */
    /*  657 */ 0x86fd725bf0f0d470ULL, /* GL_NV_command_list */
    /*  658 */ 0x909a590b136b2993ULL, /* GL_NV_compute_program5 */
    /*  659 */ 0x6e8fcfc637ce5f42ULL, /* GL_NV_compute_shader_derivatives */
    /*  660 */ 0x30dc18387f98fe17ULL, /* GL_NV_conditional_render */
    /*  661 */ 0xe3492208f94da35fULL, /* GL_NV_conservative_raster */
    /*  662 */ 0xd3d407b80b1805aeULL, /* GL_NV_conservative_raster_dilate */
    /*  663 */ 0x10c99e7e01aae44fULL, /* GL_NV_conservative_raster_pre_snap */
    /*  664 */ 0xf4ef9c1caf911a2cULL, /* GL_NV_conservative_raster_pre_snap_triangles */
    /*  665 */ 0x9a8099482ede4695ULL, /* GL_NV_conservative_raster_underestimation */
    /*  666 */ 0x82f2d3fffe63ccbaULL, /* GL_NV_cooperative_matrix */
    /*  667 */ 0xc3e52c0f74e3a5b4ULL, /* GL_NV_cooperative_matrix2 */
    /*  668 */ 0xc5b30d49db3f4c5dULL, /* GL_NV_cooperative_vector */
    /*  669 */ 0x1250d4e984fabb8aULL, /* GL_NV_copy_buffer */
    /*  670 */ 0xddf225eb383a722aULL, /* GL_NV_copy_depth_to_color */
    /*  671 */ 0x542626fd538a9ee0ULL, /* GL_NV_copy_image */
    /*  672 */ 0x1f3cf0884049a65cULL, /* GL_NV_coverage_sample */
    /*  673 */ 0xa115ed21a9ad2718ULL, /* GL_NV_deep_texture3D */
    /*  674 */ 0x11d0e662e981dd10ULL, /* GL_NV_depth_buffer_float */
    /*  675 */ 0x25caf626c8dc4876ULL, /* GL_NV_depth_clamp */
    /*  676 */ 0x23fb225c6189b719ULL, /* GL_NV_depth_nonlinear */
    /*  677 */ 0xc7c2a14929f83872ULL, /* GL_NV_displacement_micromap */
    /*  678 */ 0xe30effdb6e04aad2ULL, /* GL_NV_draw_buffers */
    /*  679 */ 0x5cef483902a0a7d1ULL, /* GL_NV_draw_instanced */
    /*  680 */ 0x0ac29b41db04db89ULL, /* GL_NV_draw_texture */
    /*  681 */ 0x0c3ad3a0bb6ea832ULL, /* GL_NV_draw_vulkan_image */
    /*  682 */ 0x86aaaa35812cc6e4ULL, /* GL_NV_evaluators */
    /*  683 */ 0x0d0ad1150bf11b93ULL, /* GL_NV_explicit_attrib_location */
    /*  684 */ 0xb1fb52088193eb75ULL, /* GL_NV_explicit_multisample */
    /*  685 */ 0xf69d212a36261f45ULL, /* GL_NV_fbo_color_attachments */
    /*  686 */ 0x9f9d6242407aaa0dULL, /* GL_NV_fence */
    /*  687 */ 0x574a28d0edc9eb1fULL, /* GL_NV_fill_rectangle */
    /*  688 */ 0x60178d619bd63acdULL, /* GL_NV_float_buffer */
    /*  689 */ 0x3a25bd3423152eb5ULL, /* GL_NV_fog_distance */
    /*  690 */ 0xbd0368ffaa60b1e1ULL, /* GL_NV_fragment_coverage_to_color */
    /*  691 */ 0xd63f48ff142e3931ULL, /* GL_NV_fragment_program */
    /*  692 */ 0x9607f3b2549a29c3ULL, /* GL_NV_fragment_program2 */
    /*  693 */ 0x3fc3c14225294207ULL, /* GL_NV_fragment_program4 */
    /*  694 */ 0x7e38a803870eb005ULL, /* GL_NV_fragment_program_option */
    /*  695 */ 0x63f3491b75562351ULL, /* GL_NV_fragment_shader_barycentric */
    /*  696 */ 0xf907528dfaacf5d1ULL, /* GL_NV_fragment_shader_interlock */
    /*  697 */ 0xc7b0688e759eaccaULL, /* GL_NV_framebuffer_blit */
    /*  698 */ 0x7690d69739f37d49ULL, /* GL_NV_framebuffer_mixed_samples */
    /*  699 */ 0xd333a1d53faf1645ULL, /* GL_NV_framebuffer_multisample */
    /*  700 */ 0xb7e1d7ede28f1eb6ULL, /* GL_NV_framebuffer_multisample_coverage */
    /*  701 */ 0x42fb5b03beace82dULL, /* GL_NV_generate_mipmap_sRGB */
    /*  702 */ 0xd649529b8b1dc13fULL, /* GL_NV_geometry_program4 */
    /*  703 */ 0x85be2495755b8912ULL, /* GL_NV_geometry_shader4 */
    /*  704 */ 0x2650d5fc619ace25ULL, /* GL_NV_geometry_shader_passthrough */
    /*  705 */ 0x0f309973ce34369dULL, /* GL_NV_gpu_multicast */
    /*  706 */ 0xb97d5c93298f0cd0ULL, /* GL_NV_gpu_program4 */
    /*  707 */ 0xfee0597c2b98bd5aULL, /* GL_NV_gpu_program5 */
    /*  708 */ 0x76ac1ada5bbc4ea2ULL, /* GL_NV_gpu_program5_mem_extended */
    /*  709 */ 0x9ca801fbedd18a78ULL, /* GL_NV_gpu_shader5 */
    /*  710 */ 0x185a8632c27d17b4ULL, /* GL_NV_half_float */
    /*  711 */ 0xe34c3aba26b785e0ULL, /* GL_NV_image_formats */
    /*  712 */ 0xc2e8b0284eeb3343ULL, /* GL_NV_instanced_arrays */
    /*  713 */ 0xaeae3147a430714aULL, /* GL_NV_integer_cooperative_matrix */
    /*  714 */ 0xa5628152267b8db5ULL, /* GL_NV_internalformat_sample_query */
    /*  715 */ 0x4514ca3e8473d61dULL, /* GL_NV_light_max_exponent */
    /*  716 */ 0xfc66f81ba1dde103ULL, /* GL_NV_linear_swept_spheres */
    /*  717 */ 0xe91f9b1323143013ULL, /* GL_NV_memory_attachment */
    /*  718 */ 0x529b823de64f6ca0ULL, /* GL_NV_memory_object_sparse */
    /*  719 */ 0x2793373463edd95bULL, /* GL_NV_mesh_shader */
    /*  720 */ 0x8d5187c2fb3e3879ULL, /* GL_NV_multisample_coverage */
    /*  721 */ 0x92f77a4cfb0d4df3ULL, /* GL_NV_multisample_filter_hint */
    /*  722 */ 0x5b891d5155380820ULL, /* GL_NV_non_square_matrices */
    /*  723 */ 0xdff6cf35e1df2d8dULL, /* GL_NV_occlusion_query */
    /*  724 */ 0xda29f4099a052321ULL, /* GL_NV_pack_subimage */
    /*  725 */ 0x1a5932681cefa5ebULL, /* GL_NV_packed_depth_stencil */
    /*  726 */ 0xbffccb846b13070aULL, /* GL_NV_parameter_buffer_object */
    /*  727 */ 0xb153f109324c418bULL, /* GL_NV_parameter_buffer_object2 */
    /*  728 */ 0x77bc468b065f8fdbULL, /* GL_NV_path_rendering */
    /*  729 */ 0x2f70022ecb786aedULL, /* GL_NV_path_rendering_shared_edge */
    /*  730 */ 0x0b44f2e633646ab5ULL, /* GL_NV_pixel_buffer_object */
    /*  731 */ 0x43d8732157b4106dULL, /* GL_NV_pixel_data_range */
    /*  732 */ 0x839efae2d0736a4cULL, /* GL_NV_point_sprite */
    /*  733 */ 0x3330eb9a4ceb6c0cULL, /* GL_NV_polygon_mode */
    /*  734 */ 0x6512c3d1922a98dbULL, /* GL_NV_present_video */
    /*  735 */ 0x8c542b195b5b3c94ULL, /* GL_NV_primitive_restart */
    /*  736 */ 0x0cacb49d8f1c105aULL, /* GL_NV_primitive_shading_rate */
    /*  737 */ 0x9b1b0441d8d19911ULL, /* GL_NV_query_resource */
    /*  738 */ 0x15f0661a8638b338ULL, /* GL_NV_query_resource_tag */
    /*  739 */ 0xdd74002f450fb368ULL, /* GL_NV_ray_tracing */
    /*  740 */ 0x182d9aed7af08983ULL, /* GL_NV_ray_tracing_motion_blur */
    /*  741 */ 0xb51b7c433236bd06ULL, /* GL_NV_read_buffer */
    /*  742 */ 0xc91023f37354df43ULL, /* GL_NV_read_buffer_front */
    /*  743 */ 0x3dfff3ed25362196ULL, /* GL_NV_read_depth */
    /*  744 */ 0x55261906f55bb17aULL, /* GL_NV_read_depth_stencil */
    /*  745 */ 0x7bab8fd7e4a04ee8ULL, /* GL_NV_read_stencil */
    /*  746 */ 0xd791c5687139b905ULL, /* GL_NV_register_combiners */
    /*  747 */ 0x8814ab530e95a798ULL, /* GL_NV_register_combiners2 */
    /*  748 */ 0xb46bd57f88e91d64ULL, /* GL_NV_representative_fragment_test */
    /*  749 */ 0xc4eada8b9cbe17c0ULL, /* GL_NV_robustness_video_memory_purge */
    /*  750 */ 0x2c2775936dc2a882ULL, /* GL_NV_sRGB_formats */
    /*  751 */ 0xc50ae467eedfefdeULL, /* GL_NV_sample_locations */
    /*  752 */ 0x446a05466a6d6429ULL, /* GL_NV_sample_mask_override_coverage */
    /*  753 */ 0x4247a4acbfcdb098ULL, /* GL_NV_scissor_exclusive */
    /*  754 */ 0x0383e334dd39d9a0ULL, /* GL_NV_shader_atomic_counters */
    /*  755 */ 0x02399be47930fbf4ULL, /* GL_NV_shader_atomic_float */
    /*  756 */ 0x8c8c8962eadf1230ULL, /* GL_NV_shader_atomic_float64 */
    /*  757 */ 0x4c3311286ab16152ULL, /* GL_NV_shader_atomic_fp16_vector */
    /*  758 */ 0xb14dbc3c64a1326fULL, /* GL_NV_shader_atomic_int64 */
    /*  759 */ 0x3ae6fc5c42bab2c2ULL, /* GL_NV_shader_buffer_load */
    /*  760 */ 0x1c05604500113691ULL, /* GL_NV_shader_buffer_store */
    /*  761 */ 0x22e85dcf4a44b2f7ULL, /* GL_NV_shader_invocation_reorder */
    /*  762 */ 0xbb5c10f38325fdf8ULL, /* GL_NV_shader_noperspective_interpolation */
    /*  763 */ 0x6d97890637a77774ULL, /* GL_NV_shader_sm_builtins */
    /*  764 */ 0xaf5c0eb5c483eb28ULL, /* GL_NV_shader_storage_buffer_object */
    /*  765 */ 0x826afa0d2f696f22ULL, /* GL_NV_shader_subgroup_partitioned */
    /*  766 */ 0x7b3f8fad48cfd967ULL, /* GL_NV_shader_texture_footprint */
    /*  767 */ 0xfd2aa76218c9354eULL, /* GL_NV_shader_thread_group */
    /*  768 */ 0x74a053165bf8ada4ULL, /* GL_NV_shader_thread_shuffle */
    /*  769 */ 0xf9355d5174ef4c70ULL, /* GL_NV_shading_rate_image */
    /*  770 */ 0x28944cfc0cca07ecULL, /* GL_NV_shadow_samplers_array */
    /*  771 */ 0xfdbd6232791ce36fULL, /* GL_NV_shadow_samplers_cube */
    /*  772 */ 0x56dc6bb2a7d8736fULL, /* GL_NV_stereo_view_rendering */
    /*  773 */ 0x2410081ec485d619ULL, /* GL_NV_tessellation_program5 */
    /*  774 */ 0x6a6887942da6a4c4ULL, /* GL_NV_texgen_emboss */
    /*  775 */ 0x35865e06d7292c9bULL, /* GL_NV_texgen_reflection */
    /*  776 */ 0x282f885e0bfd25deULL, /* GL_NV_texture_barrier */
    /*  777 */ 0x373989acbf486191ULL, /* GL_NV_texture_border_clamp */
    /*  778 */ 0x4d5276bd5a1f04ceULL, /* GL_NV_texture_compression_s3tc_update */
    /*  779 */ 0x25b70b1f5bbed713ULL, /* GL_NV_texture_compression_vtc */
    /*  780 */ 0x84b70fe53fcdcde1ULL, /* GL_NV_texture_env_combine4 */
    /*  781 */ 0x07e650e01fee3678ULL, /* GL_NV_texture_expand_normal */
    /*  782 */ 0x4679eee96470073fULL, /* GL_NV_texture_multisample */
    /*  783 */ 0xcba499c04274ad25ULL, /* GL_NV_texture_npot_2D_mipmap */
    /*  784 */ 0xccbc8154a70c3605ULL, /* GL_NV_texture_rectangle */
    /*  785 */ 0x5da6e59a7e51bc40ULL, /* GL_NV_texture_rectangle_compressed */
    /*  786 */ 0x8a67a1269b408254ULL, /* GL_NV_texture_shader */
    /*  787 */ 0x816b354fd0cd9228ULL, /* GL_NV_texture_shader2 */
    /*  788 */ 0x5526327fa18acddeULL, /* GL_NV_texture_shader3 */
    /*  789 */ 0x39f7dcc9a62c5153ULL, /* GL_NV_timeline_semaphore */
    /*  790 */ 0xf09b77c741443fcbULL, /* GL_NV_transform_feedback */
    /*  791 */ 0x32519ec17990e826ULL, /* GL_NV_transform_feedback2 */
    /*  792 */ 0x5600eb6f04e474eeULL, /* GL_NV_uniform_buffer_std430_layout */
    /*  793 */ 0x5a3050e67df48f2cULL, /* GL_NV_uniform_buffer_unified_memory */
    /*  794 */ 0xc270d7ffe7e44b23ULL, /* GL_NV_vdpau_interop */
    /*  795 */ 0x613710111a2944f7ULL, /* GL_NV_vdpau_interop2 */
    /*  796 */ 0x2670ae7bcc80188eULL, /* GL_NV_vertex_array_range */
    /*  797 */ 0x79ae834a103024c5ULL, /* GL_NV_vertex_array_range2 */
    /*  798 */ 0xe688c60fe2e62039ULL, /* GL_NV_vertex_attrib_integer_64bit */
    /*  799 */ 0x7e2fb60c66658e57ULL, /* GL_NV_vertex_buffer_unified_memory */
    /*  800 */ 0x527413b984649803ULL, /* GL_NV_vertex_program */
    /*  801 */ 0x7d2fc2b85898af18ULL, /* GL_NV_vertex_program1_1 */
    /*  802 */ 0x2d5a70a0a1d00d78ULL, /* GL_NV_vertex_program2 */
    /*  803 */ 0x747ed48148981054ULL, /* GL_NV_vertex_program2_option */
    /*  804 */ 0xc13798df29c369e2ULL, /* GL_NV_vertex_program3 */
    /*  805 */ 0xa796194638bbdc74ULL, /* GL_NV_vertex_program4 */
    /*  806 */ 0x89ae752e4cfcfae8ULL, /* GL_NV_video_capture */
    /*  807 */ 0x1b9db3e10e73323bULL, /* GL_NV_viewport_array */
    /*  808 */ 0x4e9c3fc0856350f9ULL, /* GL_NV_viewport_array2 */
    /*  809 */ 0xdf18b1c27e48f432ULL, /* GL_NV_viewport_swizzle */
    /*  810 */ 0xc05411382c7e9b6fULL, /* GL_OES_EGL_image */
    /*  811 */ 0xb3f47895b1c4d5f8ULL, /* GL_OES_EGL_image_external */
    /*  812 */ 0xbbae531ab8d7e16fULL, /* GL_OES_EGL_image_external_essl3 */
    /*  813 */ 0x55f4d891b16ad96cULL, /* GL_OES_byte_coordinates */
    /*  814 */ 0x866125fa75aab774ULL, /* GL_OES_compressed_ETC1_RGB8_sub_texture */
    /*  815 */ 0x5b4df7888b81a92bULL, /* GL_OES_compressed_ETC1_RGB8_texture */
    /*  816 */ 0xd1ae5222afe37da5ULL, /* GL_OES_compressed_paletted_texture */
    /*  817 */ 0xc5e1ddc1ea43276eULL, /* GL_OES_copy_image */
    /*  818 */ 0xa3f0bbbc7660d96cULL, /* GL_OES_depth24 */
    /*  819 */ 0xb8b2dd3478f1ec83ULL, /* GL_OES_depth32 */
    /*  820 */ 0x67516f69dbc843f6ULL, /* GL_OES_depth_texture */
    /*  821 */ 0x012b99c59ced284fULL, /* GL_OES_draw_buffers_indexed */
    /*  822 */ 0x4638dd889d2b7eabULL, /* GL_OES_draw_elements_base_vertex */
    /*  823 */ 0x29e68bee4a9705f1ULL, /* GL_OES_element_index_uint */
    /*  824 */ 0xe0b0d82d6dc31daeULL, /* GL_OES_fbo_render_mipmap */
    /*  825 */ 0x9f59932407436633ULL, /* GL_OES_fixed_point */
    /*  826 */ 0x116a77aa55534c76ULL, /* GL_OES_fragment_precision_high */
    /*  827 */ 0x5e6f26587d551ffcULL, /* GL_OES_geometry_point_size */
    /*  828 */ 0xaa384a84e450d595ULL, /* GL_OES_geometry_shader */
    /*  829 */ 0x503ad238c5e97931ULL, /* GL_OES_get_program_binary */
    /*  830 */ 0x77f35c2a7a2bd390ULL, /* GL_OES_gpu_shader5 */
    /*  831 */ 0x22e521fe25c89a3bULL, /* GL_OES_mapbuffer */
    /*  832 */ 0xb124b23bca92b355ULL, /* GL_OES_packed_depth_stencil */
    /*  833 */ 0x303e15e4f8fb9ee6ULL, /* GL_OES_primitive_bounding_box */
    /*  834 */ 0xc8d3d0277204ac3dULL, /* GL_OES_query_matrix */
    /*  835 */ 0xca46680e5cfc3e18ULL, /* GL_OES_read_format */
    /*  836 */ 0xd6c9bec1dd5d5b89ULL, /* GL_OES_required_internalformat */
    /*  837 */ 0xccb18f4e376e6c74ULL, /* GL_OES_rgb8_rgba8 */
    /*  838 */ 0xcb740362814f4ca0ULL, /* GL_OES_sample_shading */
    /*  839 */ 0x8f4eb2b127c21f67ULL, /* GL_OES_sample_variables */
    /*  840 */ 0xa023718702859970ULL, /* GL_OES_shader_image_atomic */
    /*  841 */ 0x8cc1262bb8c2d393ULL, /* GL_OES_shader_io_blocks */
    /*  842 */ 0xc772b78382e1a793ULL, /* GL_OES_shader_multisample_interpolation */
    /*  843 */ 0xbcbfeb8171756944ULL, /* GL_OES_single_precision */
    /*  844 */ 0x4e9710576f516b4eULL, /* GL_OES_standard_derivatives */
    /*  845 */ 0x79f1937e076eb6e0ULL, /* GL_OES_stencil1 */
    /*  846 */ 0x7361db1a08c53c55ULL, /* GL_OES_stencil4 */
    /*  847 */ 0x6df979b4adc4989bULL, /* GL_OES_surfaceless_context */
    /*  848 */ 0xdc7532bffc48cb01ULL, /* GL_OES_tessellation_point_size */
    /*  849 */ 0x8bbb4c0c94dc1415ULL, /* GL_OES_tessellation_shader */
    /*  850 */ 0xccac53b0ed36c73cULL, /* GL_OES_texture_3D */
    /*  851 */ 0xedc39fcb928c7be5ULL, /* GL_OES_texture_border_clamp */
    /*  852 */ 0xc7d6a2d8a596bf50ULL, /* GL_OES_texture_buffer */
    /*  853 */ 0x552cece98cadbaa6ULL, /* GL_OES_texture_compression_astc */
    /*  854 */ 0xfad8c3de7cf9ffc4ULL, /* GL_OES_texture_cube_map_array */
    /*  855 */ 0x32ed502b39dd1594ULL, /* GL_OES_texture_float */
    /*  856 */ 0x5afe2be3731190e1ULL, /* GL_OES_texture_float_linear */
    /*  857 */ 0xa9fdcf0e5b6803ddULL, /* GL_OES_texture_half_float */
    /*  858 */ 0x0011e43010189be7ULL, /* GL_OES_texture_half_float_linear */
    /*  859 */ 0xe706ff7638659b7eULL, /* GL_OES_texture_npot */
    /*  860 */ 0xdfa8a0ccd9d60d53ULL, /* GL_OES_texture_stencil8 */
    /*  861 */ 0xbc655ee4febdcfcaULL, /* GL_OES_texture_storage_multisample_2d_array */
    /*  862 */ 0x8fc2a146f6290d39ULL, /* GL_OES_texture_view */
    /*  863 */ 0x7cd6041965da7d3cULL, /* GL_OES_vertex_array_object */
    /*  864 */ 0x8d77aa22bdd641e8ULL, /* GL_OES_vertex_half_float */
    /*  865 */ 0x244e9e511573b959ULL, /* GL_OES_vertex_type_10_10_10_2 */
    /*  866 */ 0x2e0ac92809baabbdULL, /* GL_OES_viewport_array */
    /*  867 */ 0xe4756190e24cfae1ULL, /* GL_OML_interlace */
    /*  868 */ 0xf00e1502b0d1f5d7ULL, /* GL_OML_resample */
    /*  869 */ 0xee17f2c40613fa28ULL, /* GL_OML_subsample */
    /*  870 */ 0x462789e64be7acd7ULL, /* GL_OVR_multiview */
    /*  871 */ 0x4d3b083404c10e3fULL, /* GL_OVR_multiview2 */
    /*  872 */ 0xdd9450d3b97e069bULL, /* GL_OVR_multiview_multisampled_render_to_texture */
    /*  873 */ 0xb1df54452698a7beULL, /* GL_PGI_misc_hints */
    /*  874 */ 0x830c412288059800ULL, /* GL_PGI_vertex_hints */
    /*  875 */ 0x03b99dd37fd50188ULL, /* GL_QCOM_YUV_texture_gather */
    /*  876 */ 0x3aa5ff0497f38e96ULL, /* GL_QCOM_alpha_test */
    /*  877 */ 0x8b6f2c405eed8fc9ULL, /* GL_QCOM_binning_control */
    /*  878 */ 0xf4d179d0eb998db1ULL, /* GL_QCOM_cooperative_matrix_conversion */
    /*  879 */ 0xd69ddd5074f27947ULL, /* GL_QCOM_driver_control */
    /*  880 */ 0x2cfff6c37fa549bcULL, /* GL_QCOM_extended_get */
    /*  881 */ 0xa36cbb8c3a77c3a1ULL, /* GL_QCOM_extended_get2 */
    /*  882 */ 0x1359ba3cc79be309ULL, /* GL_QCOM_frame_extrapolation */
    /*  883 */ 0xa96b1c721f28a1c2ULL, /* GL_QCOM_framebuffer_foveated */
    /*  884 */ 0xaa7b8918e97b02c0ULL, /* GL_QCOM_image_processing */
    /*  885 */ 0x87abde46d2fd3251ULL, /* GL_QCOM_image_processing2 */
    /*  886 */ 0x822886625bd76c4aULL, /* GL_QCOM_motion_estimation */
    /*  887 */ 0x62c4f9e3d0cf2728ULL, /* GL_QCOM_perfmon_global_mode */
    /*  888 */ 0x6667e13047800b18ULL, /* GL_QCOM_render_sRGB_R8_RG8 */
    /*  889 */ 0x005a335cb406a184ULL, /* GL_QCOM_render_shared_exponent */
    /*  890 */ 0x0668ea2d27f4b9c7ULL, /* GL_QCOM_shader_framebuffer_fetch_noncoherent */
    /*  891 */ 0x2f8fba53941074deULL, /* GL_QCOM_shader_framebuffer_fetch_rate */
    /*  892 */ 0x360f4bc982306308ULL, /* GL_QCOM_shading_rate */
    /*  893 */ 0xa23647ccb657fc93ULL, /* GL_QCOM_texture_foveated */
    /*  894 */ 0xac6fb0841696dc5fULL, /* GL_QCOM_texture_foveated2 */
    /*  895 */ 0xb7f306a63180d3dfULL, /* GL_QCOM_texture_foveated_subsampled_layout */
    /*  896 */ 0x70d9c41ab20f93f9ULL, /* GL_QCOM_texture_lod_bias */
    /*  897 */ 0x539f28eaf685b3e5ULL, /* GL_QCOM_tile_shading */
    /*  898 */ 0x288ca2e6c7c5c86dULL, /* GL_QCOM_tiled_rendering */
    /*  899 */ 0x28eabd27e2f106a8ULL, /* GL_QCOM_writeonly_rendering */
    /*  900 */ 0xafb9cdf7b9a2826aULL, /* GL_QCOM_ycbcr_degamma */
    /*  901 */ 0x14dac5dff736a3dfULL, /* GL_REND_screen_coordinates */
    /*  902 */ 0x93469fe128fc0919ULL, /* GL_S3_s3tc */
    /*  903 */ 0x8c7ee523e6ed026aULL, /* GL_SGIS_detail_texture */
    /*  904 */ 0xe54deb13059b8c4cULL, /* GL_SGIS_fog_function */
    /*  905 */ 0xb1b31f0af9b1e3c1ULL, /* GL_SGIS_generate_mipmap */
    /*  906 */ 0x39568b3690efef18ULL, /* GL_SGIS_multisample */
    /*  907 */ 0xf250c15acefa1ac9ULL, /* GL_SGIS_pixel_texture */
    /*  908 */ 0x9b7bb525c279e853ULL, /* GL_SGIS_point_line_texgen */
    /*  909 */ 0x4e3e0fa2dfafd5b4ULL, /* GL_SGIS_point_parameters */
    /*  910 */ 0x4a4aa0671eb15c9fULL, /* GL_SGIS_sharpen_texture */
    /*  911 */ 0xe3880e70b14a01efULL, /* GL_SGIS_texture4D */
    /*  912 */ 0x70c7cab7e228743cULL, /* GL_SGIS_texture_border_clamp */
    /*  913 */ 0x04eb37e0f3c4686aULL, /* GL_SGIS_texture_color_mask */
    /*  914 */ 0xb6400bcd7a346c99ULL, /* GL_SGIS_texture_edge_clamp */
    /*  915 */ 0xd79b6287779eca3fULL, /* GL_SGIS_texture_filter4 */
    /*  916 */ 0xf25eb0173c775af1ULL, /* GL_SGIS_texture_lod */
    /*  917 */ 0x4b818d48997acf33ULL, /* GL_SGIS_texture_select */
    /*  918 */ 0x42053ed5c2789d8aULL, /* GL_SGIX_async */
    /*  919 */ 0x9baec4623ae00aa8ULL, /* GL_SGIX_async_histogram */
    /*  920 */ 0xbed04383395711b9ULL, /* GL_SGIX_async_pixel */
    /*  921 */ 0xd3cc8d1ef603a7f6ULL, /* GL_SGIX_blend_alpha_minmax */
    /*  922 */ 0xe60980f13acb1fe8ULL, /* GL_SGIX_calligraphic_fragment */
    /*  923 */ 0x5d613989907c2996ULL, /* GL_SGIX_clipmap */
    /*  924 */ 0x8fa248e9981db96eULL, /* GL_SGIX_convolution_accuracy */
    /*  925 */ 0x47ef8f4254eec5a0ULL, /* GL_SGIX_depth_pass_instrument */
    /*  926 */ 0x3489d57ce09fdb5eULL, /* GL_SGIX_depth_texture */
    /*  927 */ 0x37a8cdae9276920fULL, /* GL_SGIX_flush_raster */
    /*  928 */ 0x21b4c2f4db4fb980ULL, /* GL_SGIX_fog_offset */
    /*  929 */ 0x5379c01e285814d7ULL, /* GL_SGIX_fragment_lighting */
    /*  930 */ 0xbc4f1c742be26f3fULL, /* GL_SGIX_framezoom */
    /*  931 */ 0xd8ea1ff9ab303390ULL, /* GL_SGIX_igloo_interface */
    /*  932 */ 0x828685155c316d20ULL, /* GL_SGIX_instruments */
    /*  933 */ 0xaf75b3c8a321fd9bULL, /* GL_SGIX_interlace */
    /*  934 */ 0xac3c1477e6f161efULL, /* GL_SGIX_ir_instrument1 */
    /*  935 */ 0xe6f72d5da01567e9ULL, /* GL_SGIX_list_priority */
    /*  936 */ 0x945b05eefbbaf60cULL, /* GL_SGIX_pixel_texture */
    /*  937 */ 0x3c667c7037c70246ULL, /* GL_SGIX_pixel_tiles */
    /*  938 */ 0x17349f9e9a6e5976ULL, /* GL_SGIX_polynomial_ffd */
    /*  939 */ 0xe64b4cbd5d5fe178ULL, /* GL_SGIX_reference_plane */
    /*  940 */ 0x007a4678f7628880ULL, /* GL_SGIX_resample */
    /*  941 */ 0xfc833b6c6a1f8cc1ULL, /* GL_SGIX_scalebias_hint */
    /*  942 */ 0xfe04490bc9621226ULL, /* GL_SGIX_shadow */
    /*  943 */ 0xa1f64483e1ed6c09ULL, /* GL_SGIX_shadow_ambient */
    /*  944 */ 0x1b1eb2d33e2626cbULL, /* GL_SGIX_sprite */
    /*  945 */ 0xab712623aed89578ULL, /* GL_SGIX_subsample */
    /*  946 */ 0xf6707a8df70625ffULL, /* GL_SGIX_tag_sample_buffer */
    /*  947 */ 0xb31cc86db966473bULL, /* GL_SGIX_texture_add_env */
    /*  948 */ 0x8b7acea8e9290faeULL, /* GL_SGIX_texture_coordinate_clamp */
    /*  949 */ 0xb5df7fecc6d921f7ULL, /* GL_SGIX_texture_lod_bias */
    /*  950 */ 0xb819f1015daf16c4ULL, /* GL_SGIX_texture_multi_buffer */
    /*  951 */ 0x3c9d7b66aea3cba1ULL, /* GL_SGIX_texture_scale_bias */
    /*  952 */ 0xe9afc853af27422dULL, /* GL_SGIX_vertex_preclip */
    /*  953 */ 0x3bb1183ffedb9c68ULL, /* GL_SGIX_ycrcb */
    /*  954 */ 0x004ffc30998c20dbULL, /* GL_SGIX_ycrcb_subsample */
    /*  955 */ 0x7ab4a4b4639c69dfULL, /* GL_SGIX_ycrcba */
    /*  956 */ 0x014fc2d56670cd5aULL, /* GL_SGI_color_matrix */
    /*  957 */ 0x5f28de108b449e5dULL, /* GL_SGI_color_table */
    /*  958 */ 0xa03c2d1d2eeb1bd2ULL, /* GL_SGI_texture_color_table */
    /*  959 */ 0xd3460591a825bcf6ULL, /* GL_SUNX_constant_data */
    /*  960 */ 0x4e5296cda0471f61ULL, /* GL_SUN_convolution_border_modes */
    /*  961 */ 0xe19c670da3369515ULL, /* GL_SUN_global_alpha */
    /*  962 */ 0xbd8a54b9db901974ULL, /* GL_SUN_mesh_array */
    /*  963 */ 0xa52af6dd6a5fb2d3ULL, /* GL_SUN_slice_accum */
    /*  964 */ 0xbeb30cddf53ae288ULL, /* GL_SUN_triangle_list */
    /*  965 */ 0xd0bf54f2a8798b55ULL, /* GL_SUN_vertex */
    /*  966 */ 0x156892df7146814dULL, /* GL_VIV_shader_binary */
    /*  967 */ 0xf09a257256bde8f6ULL, /* GL_WIN_phong_shading */
    /*  968 */ 0x5a3e106713a38cffULL  /* GL_WIN_specular_fog */
};

static const GladAliasPair_t GLAD_GL_command_aliases[] = {
    {   66,  864 }, /* glActiveTexture and glActiveTextureARB */
    {  108,  928 }, /* glAttachShader and glAttachObjectARB */
    {  215, 1851 }, /* glBeginConditionalRender and glBeginConditionalRenderNV */
    {   87,  901 }, /* glBeginQuery and glBeginQueryARB */
    {  208, 1664 }, /* glBeginTransformFeedback and glBeginTransformFeedbackEXT */
    {  208, 2129 }, /* glBeginTransformFeedback and glBeginTransformFeedbackNV */
    {  109, 1046 }, /* glBindAttribLocation and glBindAttribLocationARB */
    {   92,  992 }, /* glBindBuffer and glBindBufferARB */
    {  211, 1668 }, /* glBindBufferBase and glBindBufferBaseEXT */
    {  211, 2134 }, /* glBindBufferBase and glBindBufferBaseNV */
    { 2133, 1667 }, /* glBindBufferOffsetNV and glBindBufferOffsetEXT */
    {  210, 1666 }, /* glBindBufferRange and glBindBufferRangeEXT */
    {  210, 2132 }, /* glBindBufferRange and glBindBufferRangeNV */
    {  241, 1162 }, /* glBindFragDataLocation and glBindFragDataLocationEXT */
    {  317, 2569 }, /* glBindFragDataLocationIndexed and glBindFragDataLocationIndexedEXT */
    { 2193,  796 }, /* glBindProgramNV and glBindProgramARB */
    {   58, 1652 }, /* glBindTexture and glBindTextureEXT */
    {  282, 2736 }, /* glBindVertexArray and glBindVertexArrayOES */
    { 2547, 1777 }, /* glBlendBarrier and glBlendBarrierKHR */
    { 2547, 1832 }, /* glBlendBarrier and glBlendBarrierNV */
    {   82, 1160 }, /* glBlendColor and glBlendColorEXT */
    {   83, 1164 }, /* glBlendEquation and glBlendEquationEXT */
    {  346,  664 }, /* glBlendEquationi and glBlendEquationIndexedAMD */
    {  346,  789 }, /* glBlendEquationi and glBlendEquationiARB */
    {  346, 2591 }, /* glBlendEquationi and glBlendEquationiEXT */
    {  346, 2700 }, /* glBlendEquationi and glBlendEquationiOES */
    {  103, 1161 }, /* glBlendEquationSeparate and glBlendEquationSeparateEXT */
    {  347,  665 }, /* glBlendEquationSeparatei and glBlendEquationSeparateIndexedAMD */
    {  347,  790 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiARB */
    {  347, 2592 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiEXT */
    {  347, 2701 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiOES */
    {  348,  662 }, /* glBlendFunci and glBlendFuncIndexedAMD */
    {  348,  791 }, /* glBlendFunci and glBlendFunciARB */
    {  348, 2593 }, /* glBlendFunci and glBlendFunciEXT */
    {  348, 2702 }, /* glBlendFunci and glBlendFunciOES */
    {   75, 1163 }, /* glBlendFuncSeparate and glBlendFuncSeparateEXT */
    {   75, 1758 }, /* glBlendFuncSeparate and glBlendFuncSeparateINGR */
    {  349,  663 }, /* glBlendFuncSeparatei and glBlendFuncSeparateIndexedAMD */
    {  349,  792 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiARB */
    {  349, 2594 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiEXT */
    {  349, 2703 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiOES */
    {  277, 1489 }, /* glBlitFramebuffer and glBlitFramebufferEXT */
    {  277, 2672 }, /* glBlitFramebuffer and glBlitFramebufferNV */
    {   96,  996 }, /* glBufferData and glBufferDataARB */
    {  534, 2572 }, /* glBufferStorage and glBufferStorageEXT */
    {   97,  997 }, /* glBufferSubData and glBufferSubDataARB */
    {  270, 1503 }, /* glCheckFramebufferStatus and glCheckFramebufferStatusEXT */
    {  214,  782 }, /* glClampColor and glClampColorARB */
    {  395, 2395 }, /* glClearDepthf and glClearDepthfOES */
    {  535, 2573 }, /* glClearTexImage and glClearTexImageEXT */
    {  536, 2574 }, /* glClearTexSubImage and glClearTexSubImageEXT */
    {  306, 2561 }, /* glClientWaitSync and glClientWaitSyncAPPLE */
    {  543, 2575 }, /* glClipControl and glClipControlEXT */
    {  202, 1474 }, /* glColorMaski and glColorMaskIndexedEXT */
    {  202, 2595 }, /* glColorMaski and glColorMaskiEXT */
    {  202, 2704 }, /* glColorMaski and glColorMaskiOES */
    {  110,  926 }, /* glCompileShader and glCompileShaderARB */
    {   70,  973 }, /* glCompressedTexImage1D and glCompressedTexImage1DARB */
    {   69,  972 }, /* glCompressedTexImage2D and glCompressedTexImage2DARB */
    {   68,  971 }, /* glCompressedTexImage3D and glCompressedTexImage3DARB */
    {   73,  976 }, /* glCompressedTexSubImage1D and glCompressedTexSubImage1DARB */
    {   72,  975 }, /* glCompressedTexSubImage2D and glCompressedTexSubImage2DARB */
    {   71,  974 }, /* glCompressedTexSubImage3D and glCompressedTexSubImage3DARB */
    {  290, 2666 }, /* glCopyBufferSubData and glCopyBufferSubDataNV */
    {  495, 2576 }, /* glCopyImageSubData and glCopyImageSubDataEXT */
    {  495, 2697 }, /* glCopyImageSubData and glCopyImageSubDataOES */
    {   52, 1204 }, /* glCopyTexImage1D and glCopyTexImage1DEXT */
    {   53, 1205 }, /* glCopyTexImage2D and glCopyTexImage2DEXT */
    {   54, 1206 }, /* glCopyTexSubImage1D and glCopyTexSubImage1DEXT */
    {   55, 1207 }, /* glCopyTexSubImage2D and glCopyTexSubImage2DEXT */
    {   65, 1208 }, /* glCopyTexSubImage3D and glCopyTexSubImage3DEXT */
    {  111,  927 }, /* glCreateProgram and glCreateProgramObjectARB */
    {  112,  924 }, /* glCreateShader and glCreateShaderObjectARB */
    {  526,  786 }, /* glDebugMessageCallback and glDebugMessageCallbackARB */
    {  526, 2652 }, /* glDebugMessageCallback and glDebugMessageCallbackKHR */
    {  524,  784 }, /* glDebugMessageControl and glDebugMessageControlARB */
    {  524, 2650 }, /* glDebugMessageControl and glDebugMessageControlKHR */
    {  525,  785 }, /* glDebugMessageInsert and glDebugMessageInsertARB */
    {  525, 2651 }, /* glDebugMessageInsert and glDebugMessageInsertKHR */
    {   93,  993 }, /* glDeleteBuffers and glDeleteBuffersARB */
    {  268, 1501 }, /* glDeleteFramebuffers and glDeleteFramebuffersEXT */
    { 2194,  797 }, /* glDeleteProgramsNV and glDeleteProgramsARB */
    {   85,  899 }, /* glDeleteQueries and glDeleteQueriesARB */
    {  262, 1495 }, /* glDeleteRenderbuffers and glDeleteRenderbuffersEXT */
    {  305, 2560 }, /* glDeleteSync and glDeleteSyncAPPLE */
    {  381, 2142 }, /* glDeleteTransformFeedbacks and glDeleteTransformFeedbacksNV */
    {  283,  751 }, /* glDeleteVertexArrays and glDeleteVertexArraysAPPLE */
    {  283, 2737 }, /* glDeleteVertexArrays and glDeleteVertexArraysOES */
    {  394, 2397 }, /* glDepthRangef and glDepthRangefOES */
    {  115,  923 }, /* glDetachShader and glDetachObjectARB */
    {  206, 1297 }, /* glDisablei and glDisableIndexedEXT */
    {  206, 2590 }, /* glDisablei and glDisableiEXT */
    {  206, 2693 }, /* glDisablei and glDisableiNV */
    {  206, 2699 }, /* glDisablei and glDisableiOES */
    {  116, 1041 }, /* glDisableVertexAttribArray and glDisableVertexAttribArrayARB */
    {   48, 1673 }, /* glDrawArrays and glDrawArraysEXT */
    {  286, 2551 }, /* glDrawArraysInstanced and glDrawArraysInstancedANGLE */
    {  286,  793 }, /* glDrawArraysInstanced and glDrawArraysInstancedARB */
    {  286, 1475 }, /* glDrawArraysInstanced and glDrawArraysInstancedEXT */
    {  286, 2670 }, /* glDrawArraysInstanced and glDrawArraysInstancedNV */
    {  479, 2846 }, /* glDrawArraysInstancedBaseInstance and glDrawArraysInstancedBaseInstanceANGLE */
    {  479, 2566 }, /* glDrawArraysInstancedBaseInstance and glDrawArraysInstancedBaseInstanceEXT */
    {  104,  788 }, /* glDrawBuffers and glDrawBuffersARB */
    {  104, 1067 }, /* glDrawBuffers and glDrawBuffersATI */
    {  104, 2588 }, /* glDrawBuffers and glDrawBuffersEXT */
    {  298, 2597 }, /* glDrawElementsBaseVertex and glDrawElementsBaseVertexEXT */
    {  298, 2706 }, /* glDrawElementsBaseVertex and glDrawElementsBaseVertexOES */
    {  287, 2552 }, /* glDrawElementsInstanced and glDrawElementsInstancedANGLE */
    {  287,  794 }, /* glDrawElementsInstanced and glDrawElementsInstancedARB */
    {  287, 1476 }, /* glDrawElementsInstanced and glDrawElementsInstancedEXT */
    {  287, 2671 }, /* glDrawElementsInstanced and glDrawElementsInstancedNV */
    {  480, 2567 }, /* glDrawElementsInstancedBaseInstance and glDrawElementsInstancedBaseInstanceEXT */
    {  300, 2599 }, /* glDrawElementsInstancedBaseVertex and glDrawElementsInstancedBaseVertexEXT */
    {  300, 2708 }, /* glDrawElementsInstancedBaseVertex and glDrawElementsInstancedBaseVertexOES */
    {  481, 2847 }, /* glDrawElementsInstancedBaseVertexBaseInstance and glDrawElementsInstancedBaseVertexBaseInstanceANGLE */
    {  481, 2568 }, /* glDrawElementsInstancedBaseVertexBaseInstance and glDrawElementsInstancedBaseVertexBaseInstanceEXT */
    {   62, 1477 }, /* glDrawRangeElements and glDrawRangeElementsEXT */
    {  299, 2598 }, /* glDrawRangeElementsBaseVertex and glDrawRangeElementsBaseVertexEXT */
    {  299, 2707 }, /* glDrawRangeElementsBaseVertex and glDrawRangeElementsBaseVertexOES */
    {  386, 2601 }, /* glDrawTransformFeedback and glDrawTransformFeedbackEXT */
    {  386, 2147 }, /* glDrawTransformFeedback and glDrawTransformFeedbackNV */
    {  489, 2602 }, /* glDrawTransformFeedbackInstanced and glDrawTransformFeedbackInstancedEXT */
    {  205, 1296 }, /* glEnablei and glEnableIndexedEXT */
    {  205, 2589 }, /* glEnablei and glEnableiEXT */
    {  205, 2692 }, /* glEnablei and glEnableiNV */
    {  205, 2698 }, /* glEnablei and glEnableiOES */
    {  117, 1040 }, /* glEnableVertexAttribArray and glEnableVertexAttribArrayARB */
    {  216, 1852 }, /* glEndConditionalRender and glEndConditionalRenderNV */
    {  216, 1809 }, /* glEndConditionalRender and glEndConditionalRenderNVX */
    {   88,  902 }, /* glEndQuery and glEndQueryARB */
    {  209, 1665 }, /* glEndTransformFeedback and glEndTransformFeedbackEXT */
    {  209, 2130 }, /* glEndTransformFeedback and glEndTransformFeedbackNV */
    {  303, 2558 }, /* glFenceSync and glFenceSyncAPPLE */
    {  281,  744 }, /* glFlushMappedBufferRange and glFlushMappedBufferRangeAPPLE */
    {  281, 2605 }, /* glFlushMappedBufferRange and glFlushMappedBufferRangeEXT */
    {  274, 1507 }, /* glFramebufferRenderbuffer and glFramebufferRenderbufferEXT */
    {  312,  815 }, /* glFramebufferTexture and glFramebufferTextureARB */
    {  312, 1510 }, /* glFramebufferTexture and glFramebufferTextureEXT */
    {  312, 2709 }, /* glFramebufferTexture and glFramebufferTextureOES */
    {  271, 1504 }, /* glFramebufferTexture1D and glFramebufferTexture1DEXT */
    {  272, 1505 }, /* glFramebufferTexture2D and glFramebufferTexture2DEXT */
    {  273, 1506 }, /* glFramebufferTexture3D and glFramebufferTexture3DEXT */
    {  817, 1897 }, /* glFramebufferTextureFaceARB and glFramebufferTextureFaceEXT */
    {  279,  816 }, /* glFramebufferTextureLayer and glFramebufferTextureLayerARB */
    {  279, 1643 }, /* glFramebufferTextureLayer and glFramebufferTextureLayerEXT */
    {   94,  994 }, /* glGenBuffers and glGenBuffersARB */
    {  276, 1509 }, /* glGenerateMipmap and glGenerateMipmapEXT */
    {  269, 1502 }, /* glGenFramebuffers and glGenFramebuffersEXT */
    { 2196,  798 }, /* glGenProgramsNV and glGenProgramsARB */
    {   84,  898 }, /* glGenQueries and glGenQueriesARB */
    {  263, 1496 }, /* glGenRenderbuffers and glGenRenderbuffersEXT */
    {  382, 2143 }, /* glGenTransformFeedbacks and glGenTransformFeedbacksNV */
    {  284,  752 }, /* glGenVertexArrays and glGenVertexArraysAPPLE */
    {  284, 2738 }, /* glGenVertexArrays and glGenVertexArraysOES */
    {  118, 1047 }, /* glGetActiveAttrib and glGetActiveAttribARB */
    {  119,  956 }, /* glGetActiveUniform and glGetActiveUniformARB */
    {  121, 1048 }, /* glGetAttribLocation and glGetAttribLocationARB */
    {  203, 1300 }, /* glGetBooleani_v and glGetBooleanIndexedvEXT */
    {  101, 1001 }, /* glGetBufferParameteriv and glGetBufferParameterivARB */
    {  102, 1002 }, /* glGetBufferPointerv and glGetBufferPointervARB */
    {  102, 2714 }, /* glGetBufferPointerv and glGetBufferPointervOES */
    {   98,  998 }, /* glGetBufferSubData and glGetBufferSubDataARB */
    {   74, 2854 }, /* glGetCompressedTexImage and glGetCompressedTexImageANGLE */
    {   74,  977 }, /* glGetCompressedTexImage and glGetCompressedTexImageARB */
    {  527,  787 }, /* glGetDebugMessageLog and glGetDebugMessageLogARB */
    {  527, 2653 }, /* glGetDebugMessageLog and glGetDebugMessageLogKHR */
    {  478, 1294 }, /* glGetDoublei_v and glGetDoubleIndexedvEXT */
    {  478, 1381 }, /* glGetDoublei_v and glGetDoublei_vEXT */
    {  477, 1293 }, /* glGetFloati_v and glGetFloatIndexedvEXT */
    {  477, 1380 }, /* glGetFloati_v and glGetFloati_vEXT */
    {  477, 2691 }, /* glGetFloati_v and glGetFloati_vNV */
    {  477, 2748 }, /* glGetFloati_v and glGetFloati_vOES */
    {  318, 2571 }, /* glGetFragDataIndex and glGetFragDataIndexEXT */
    {  242, 1515 }, /* glGetFragDataLocation and glGetFragDataLocationEXT */
    {  275, 1508 }, /* glGetFramebufferAttachmentParameteriv and glGetFramebufferAttachmentParameterivEXT */
    {  644, 2613 }, /* glGetGraphicsResetStatus and glGetGraphicsResetStatusEXT */
    {  644, 2661 }, /* glGetGraphicsResetStatus and glGetGraphicsResetStatusKHR */
    {  308, 2563 }, /* glGetInteger64v and glGetInteger64vAPPLE */
    {  308, 2587 }, /* glGetInteger64v and glGetInteger64vEXT */
    {  204, 1299 }, /* glGetIntegeri_v and glGetIntegerIndexedvEXT */
    {  315, 2840 }, /* glGetMultisamplefv and glGetMultisamplefvANGLE */
    {  315, 1875 }, /* glGetMultisamplefv and glGetMultisamplefvNV */
    {  648, 2615 }, /* glGetnUniformfv and glGetnUniformfvEXT */
    {  648, 2663 }, /* glGetnUniformfv and glGetnUniformfvKHR */
    {  649, 2616 }, /* glGetnUniformiv and glGetnUniformivEXT */
    {  649, 2664 }, /* glGetnUniformiv and glGetnUniformivKHR */
    {  650, 2665 }, /* glGetnUniformuiv and glGetnUniformuivKHR */
    {  531, 2657 }, /* glGetObjectLabel and glGetObjectLabelKHR */
    {  533, 2659 }, /* glGetObjectPtrLabel and glGetObjectPtrLabelKHR */
    {   50, 2874 }, /* glGetPointerv and glGetPointervANGLE */
    {   50, 1675 }, /* glGetPointerv and glGetPointervEXT */
    {   50, 2660 }, /* glGetPointerv and glGetPointervKHR */
    {  396, 2710 }, /* glGetProgramBinary and glGetProgramBinaryOES */
    {   89,  903 }, /* glGetQueryiv and glGetQueryivARB */
    {  334, 1472 }, /* glGetQueryObjecti64v and glGetQueryObjecti64vEXT */
    {   90,  904 }, /* glGetQueryObjectiv and glGetQueryObjectivARB */
    {   90, 2585 }, /* glGetQueryObjectiv and glGetQueryObjectivEXT */
    {  335, 1473 }, /* glGetQueryObjectui64v and glGetQueryObjectui64vEXT */
    {   91,  905 }, /* glGetQueryObjectuiv and glGetQueryObjectuivARB */
    {  265, 1498 }, /* glGetRenderbufferParameteriv and glGetRenderbufferParameterivEXT */
    {  330, 2634 }, /* glGetSamplerParameterIiv and glGetSamplerParameterIivEXT */
    {  330, 2730 }, /* glGetSamplerParameterIiv and glGetSamplerParameterIivOES */
    {  332, 2635 }, /* glGetSamplerParameterIuiv and glGetSamplerParameterIuivEXT */
    {  332, 2731 }, /* glGetSamplerParameterIuiv and glGetSamplerParameterIuivOES */
    {  126,  959 }, /* glGetShaderSource and glGetShaderSourceARB */
    {  309, 2564 }, /* glGetSynciv and glGetSyncivAPPLE */
    {   40, 2853 }, /* glGetTexImage and glGetTexImageANGLE */
    {   43, 2856 }, /* glGetTexLevelParameterfv and glGetTexLevelParameterfvANGLE */
    {   44, 2857 }, /* glGetTexLevelParameteriv and glGetTexLevelParameterivANGLE */
    {  253, 1646 }, /* glGetTexParameterIiv and glGetTexParameterIivEXT */
    {  253, 2726 }, /* glGetTexParameterIiv and glGetTexParameterIivOES */
    {  254, 1647 }, /* glGetTexParameterIuiv and glGetTexParameterIuivEXT */
    {  254, 2727 }, /* glGetTexParameterIuiv and glGetTexParameterIuivOES */
    {  765, 2640 }, /* glGetTextureHandleARB and glGetTextureHandleIMG */
    {  766, 2641 }, /* glGetTextureSamplerHandleARB and glGetTextureSamplerHandleIMG */
    {  213, 1670 }, /* glGetTransformFeedbackVarying and glGetTransformFeedbackVaryingEXT */
    {  128,  957 }, /* glGetUniformfv and glGetUniformfvARB */
    {  129,  958 }, /* glGetUniformiv and glGetUniformivARB */
    {  127,  955 }, /* glGetUniformLocation and glGetUniformLocationARB */
    {  240, 1514 }, /* glGetUniformuiv and glGetUniformuivEXT */
    {  130, 1042 }, /* glGetVertexAttribdv and glGetVertexAttribdvARB */
    {  130, 2202 }, /* glGetVertexAttribdv and glGetVertexAttribdvNV */
    {  131, 1043 }, /* glGetVertexAttribfv and glGetVertexAttribfvARB */
    {  131, 2203 }, /* glGetVertexAttribfv and glGetVertexAttribfvNV */
    {  218, 1545 }, /* glGetVertexAttribIiv and glGetVertexAttribIivEXT */
    {  219, 1546 }, /* glGetVertexAttribIuiv and glGetVertexAttribIuivEXT */
    {  132, 1044 }, /* glGetVertexAttribiv and glGetVertexAttribivARB */
    {  132, 2204 }, /* glGetVertexAttribiv and glGetVertexAttribivNV */
    {  468, 1689 }, /* glGetVertexAttribLdv and glGetVertexAttribLdvEXT */
    {  133, 1045 }, /* glGetVertexAttribPointerv and glGetVertexAttribPointervARB */
    {  133, 2205 }, /* glGetVertexAttribPointerv and glGetVertexAttribPointervNV */
    {   95,  995 }, /* glIsBuffer and glIsBufferARB */
    {  207, 1298 }, /* glIsEnabledi and glIsEnabledIndexedEXT */
    {  207, 2596 }, /* glIsEnabledi and glIsEnablediEXT */
    {  207, 2694 }, /* glIsEnabledi and glIsEnablediNV */
    {  207, 2705 }, /* glIsEnabledi and glIsEnablediOES */
    {  266, 1499 }, /* glIsFramebuffer and glIsFramebufferEXT */
    { 2206,  813 }, /* glIsProgramNV and glIsProgramARB */
    {   86,  900 }, /* glIsQuery and glIsQueryARB */
    {  260, 1493 }, /* glIsRenderbuffer and glIsRenderbufferEXT */
    {  304, 2559 }, /* glIsSync and glIsSyncAPPLE */
    {  383, 2144 }, /* glIsTransformFeedback and glIsTransformFeedbackNV */
    {  285,  753 }, /* glIsVertexArray and glIsVertexArrayAPPLE */
    {  285, 2739 }, /* glIsVertexArray and glIsVertexArrayOES */
    {  136,  929 }, /* glLinkProgram and glLinkProgramARB */
    {   26, 2872 }, /* glLogicOp and glLogicOpANGLE */
    {   99,  999 }, /* glMapBuffer and glMapBufferARB */
    {   99, 2712 }, /* glMapBuffer and glMapBufferOES */
    {  280, 2604 }, /* glMapBufferRange and glMapBufferRangeEXT */
    {  906, 1778 }, /* glMaxShaderCompilerThreadsARB and glMaxShaderCompilerThreadsKHR */
    {  485, 1636 }, /* glMemoryBarrier and glMemoryBarrierEXT */
    {  345,  920 }, /* glMinSampleShading and glMinSampleShadingARB */
    {  345, 2716 }, /* glMinSampleShading and glMinSampleShadingOES */
    {   76, 2842 }, /* glMultiDrawArrays and glMultiDrawArraysANGLE */
    {   76, 1584 }, /* glMultiDrawArrays and glMultiDrawArraysEXT */
    {  505,  707 }, /* glMultiDrawArraysIndirect and glMultiDrawArraysIndirectAMD */
    {  505, 2606 }, /* glMultiDrawArraysIndirect and glMultiDrawArraysIndirectEXT */
    {  654,  855 }, /* glMultiDrawArraysIndirectCount and glMultiDrawArraysIndirectCountARB */
    {   77, 2844 }, /* glMultiDrawElements and glMultiDrawElementsANGLE */
    {   77, 1585 }, /* glMultiDrawElements and glMultiDrawElementsEXT */
    {  301, 2600 }, /* glMultiDrawElementsBaseVertex and glMultiDrawElementsBaseVertexEXT */
    {  506,  708 }, /* glMultiDrawElementsIndirect and glMultiDrawElementsIndirectAMD */
    {  506, 2607 }, /* glMultiDrawElementsIndirect and glMultiDrawElementsIndirectEXT */
    {  655,  856 }, /* glMultiDrawElementsIndirectCount and glMultiDrawElementsIndirectCountARB */
    {  551, 1435 }, /* glNamedBufferStorage and glNamedBufferStorageEXT */
    {  553, 1320 }, /* glNamedBufferSubData and glNamedBufferSubDataEXT */
    {  530, 2656 }, /* glObjectLabel and glObjectLabelKHR */
    {  532, 2658 }, /* glObjectPtrLabel and glObjectPtrLabelKHR */
    {  378, 2631 }, /* glPatchParameteri and glPatchParameteriEXT */
    {  378, 2717 }, /* glPatchParameteri and glPatchParameteriOES */
    {  384, 2145 }, /* glPauseTransformFeedback and glPauseTransformFeedbackNV */
    {   78,  907 }, /* glPointParameterf and glPointParameterfARB */
    {   78, 1598 }, /* glPointParameterf and glPointParameterfEXT */
    {   78, 2416 }, /* glPointParameterf and glPointParameterfSGIS */
    {   79,  908 }, /* glPointParameterfv and glPointParameterfvARB */
    {   79, 1599 }, /* glPointParameterfv and glPointParameterfvEXT */
    {   79, 2417 }, /* glPointParameterfv and glPointParameterfvSGIS */
    {   80, 2068 }, /* glPointParameteri and glPointParameteriNV */
    {   81, 2069 }, /* glPointParameteriv and glPointParameterivNV */
    {    5, 2681 }, /* glPolygonMode and glPolygonModeNV */
    {  656, 1601 }, /* glPolygonOffsetClamp and glPolygonOffsetClampEXT */
    {  529, 2655 }, /* glPopDebugGroup and glPopDebugGroupKHR */
    { 2548,  764 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxARB */
    { 2548, 2612 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxEXT */
    { 2548, 2715 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxOES */
    {  397, 2711 }, /* glProgramBinary and glProgramBinaryOES */
    {  398,  814 }, /* glProgramParameteri and glProgramParameteriARB */
    {  398, 1511 }, /* glProgramParameteri and glProgramParameteriEXT */
    {  409, 1326 }, /* glProgramUniform1f and glProgramUniform1fEXT */
    {  410, 1334 }, /* glProgramUniform1fv and glProgramUniform1fvEXT */
    {  407, 1330 }, /* glProgramUniform1i and glProgramUniform1iEXT */
    {  408, 1338 }, /* glProgramUniform1iv and glProgramUniform1ivEXT */
    {  413, 1361 }, /* glProgramUniform1ui and glProgramUniform1uiEXT */
    {  414, 1365 }, /* glProgramUniform1uiv and glProgramUniform1uivEXT */
    {  417, 1327 }, /* glProgramUniform2f and glProgramUniform2fEXT */
    {  418, 1335 }, /* glProgramUniform2fv and glProgramUniform2fvEXT */
    {  415, 1331 }, /* glProgramUniform2i and glProgramUniform2iEXT */
    {  416, 1339 }, /* glProgramUniform2iv and glProgramUniform2ivEXT */
    {  421, 1362 }, /* glProgramUniform2ui and glProgramUniform2uiEXT */
    {  422, 1366 }, /* glProgramUniform2uiv and glProgramUniform2uivEXT */
    {  425, 1328 }, /* glProgramUniform3f and glProgramUniform3fEXT */
    {  426, 1336 }, /* glProgramUniform3fv and glProgramUniform3fvEXT */
    {  423, 1332 }, /* glProgramUniform3i and glProgramUniform3iEXT */
    {  424, 1340 }, /* glProgramUniform3iv and glProgramUniform3ivEXT */
    {  429, 1363 }, /* glProgramUniform3ui and glProgramUniform3uiEXT */
    {  430, 1367 }, /* glProgramUniform3uiv and glProgramUniform3uivEXT */
    {  433, 1329 }, /* glProgramUniform4f and glProgramUniform4fEXT */
    {  434, 1337 }, /* glProgramUniform4fv and glProgramUniform4fvEXT */
    {  431, 1333 }, /* glProgramUniform4i and glProgramUniform4iEXT */
    {  432, 1341 }, /* glProgramUniform4iv and glProgramUniform4ivEXT */
    {  437, 1364 }, /* glProgramUniform4ui and glProgramUniform4uiEXT */
    {  438, 1368 }, /* glProgramUniform4uiv and glProgramUniform4uivEXT */
    {  774, 2644 }, /* glProgramUniformHandleui64ARB and glProgramUniformHandleui64IMG */
    {  775, 2645 }, /* glProgramUniformHandleui64vARB and glProgramUniformHandleui64vIMG */
    {  439, 1342 }, /* glProgramUniformMatrix2fv and glProgramUniformMatrix2fvEXT */
    {  445, 1345 }, /* glProgramUniformMatrix2x3fv and glProgramUniformMatrix2x3fvEXT */
    {  447, 1347 }, /* glProgramUniformMatrix2x4fv and glProgramUniformMatrix2x4fvEXT */
    {  440, 1343 }, /* glProgramUniformMatrix3fv and glProgramUniformMatrix3fvEXT */
    {  446, 1346 }, /* glProgramUniformMatrix3x2fv and glProgramUniformMatrix3x2fvEXT */
    {  449, 1349 }, /* glProgramUniformMatrix3x4fv and glProgramUniformMatrix3x4fvEXT */
    {  441, 1344 }, /* glProgramUniformMatrix4fv and glProgramUniformMatrix4fvEXT */
    {  448, 1348 }, /* glProgramUniformMatrix4x2fv and glProgramUniformMatrix4x2fvEXT */
    {  450, 1350 }, /* glProgramUniformMatrix4x3fv and glProgramUniformMatrix4x3fvEXT */
    {  302, 2851 }, /* glProvokingVertex and glProvokingVertexANGLE */
    {  302, 1602 }, /* glProvokingVertex and glProvokingVertexEXT */
    {  528, 2654 }, /* glPushDebugGroup and glPushDebugGroupKHR */
    {  333, 2583 }, /* glQueryCounter and glQueryCounterEXT */
    {  651,  911 }, /* glReadnPixels and glReadnPixelsARB */
    {  651, 2614 }, /* glReadnPixels and glReadnPixelsEXT */
    {  651, 2662 }, /* glReadnPixels and glReadnPixelsKHR */
    {  264, 1497 }, /* glRenderbufferStorage and glRenderbufferStorageEXT */
    {  278, 1492 }, /* glRenderbufferStorageMultisample and glRenderbufferStorageMultisampleEXT */
    {  278, 2673 }, /* glRenderbufferStorageMultisample and glRenderbufferStorageMultisampleNV */
    {  385, 2146 }, /* glResumeTransformFeedback and glResumeTransformFeedbackNV */
    {   67,  863 }, /* glSampleCoverage and glSampleCoverageARB */
    { 1586, 2408 }, /* glSampleMaskEXT and glSampleMaskSGIS */
    {  316, 2841 }, /* glSampleMaski and glSampleMaskiANGLE */
    { 1587, 2409 }, /* glSamplePatternEXT and glSamplePatternSGIS */
    {  327, 2632 }, /* glSamplerParameterIiv and glSamplerParameterIivEXT */
    {  327, 2728 }, /* glSamplerParameterIiv and glSamplerParameterIivOES */
    {  328, 2633 }, /* glSamplerParameterIuiv and glSamplerParameterIuivEXT */
    {  328, 2729 }, /* glSamplerParameterIuiv and glSamplerParameterIuivOES */
    {  472, 2686 }, /* glScissorArrayv and glScissorArrayvNV */
    {  472, 2743 }, /* glScissorArrayv and glScissorArrayvOES */
    {  473, 2687 }, /* glScissorIndexed and glScissorIndexedNV */
    {  473, 2744 }, /* glScissorIndexed and glScissorIndexedOES */
    {  474, 2688 }, /* glScissorIndexedv and glScissorIndexedvNV */
    {  474, 2745 }, /* glScissorIndexedv and glScissorIndexedvOES */
    {  137,  925 }, /* glShaderSource and glShaderSourceARB */
    {  653,  818 }, /* glSpecializeShader and glSpecializeShaderARB */
    {  105, 1093 }, /* glStencilOpSeparate and glStencilOpSeparateATI */
    {  288,  970 }, /* glTexBuffer and glTexBufferARB */
    {  288, 1648 }, /* glTexBuffer and glTexBufferEXT */
    {  288, 2732 }, /* glTexBuffer and glTexBufferOES */
    {  514, 2636 }, /* glTexBufferRange and glTexBufferRangeEXT */
    {  514, 2733 }, /* glTexBufferRange and glTexBufferRangeOES */
    {   63, 1641 }, /* glTexImage3D and glTexImage3DEXT */
    {  969, 2630 }, /* glTexPageCommitmentARB and glTexPageCommitmentEXT */
    {  251, 1644 }, /* glTexParameterIiv and glTexParameterIivEXT */
    {  251, 2724 }, /* glTexParameterIiv and glTexParameterIivOES */
    {  252, 1645 }, /* glTexParameterIuiv and glTexParameterIuivEXT */
    {  252, 2725 }, /* glTexParameterIuiv and glTexParameterIuivOES */
    {  486, 1658 }, /* glTexStorage1D and glTexStorage1DEXT */
    {  487, 1659 }, /* glTexStorage2D and glTexStorage2DEXT */
    {  515, 2839 }, /* glTexStorage2DMultisample and glTexStorage2DMultisampleANGLE */
    {  488, 1660 }, /* glTexStorage3D and glTexStorage3DEXT */
    {  516, 2734 }, /* glTexStorage3DMultisample and glTexStorage3DMultisampleOES */
    {   56, 1639 }, /* glTexSubImage1D and glTexSubImage1DEXT */
    {   57, 1640 }, /* glTexSubImage2D and glTexSubImage2DEXT */
    {   64, 1642 }, /* glTexSubImage3D and glTexSubImage3DEXT */
    {  517, 2639 }, /* glTextureView and glTextureViewEXT */
    {  517, 2735 }, /* glTextureView and glTextureViewOES */
    {  212, 1669 }, /* glTransformFeedbackVaryings and glTransformFeedbackVaryingsEXT */
    {  139,  932 }, /* glUniform1f and glUniform1fARB */
    {  147,  940 }, /* glUniform1fv and glUniform1fvARB */
    {  143,  936 }, /* glUniform1i and glUniform1iARB */
    {  151,  944 }, /* glUniform1iv and glUniform1ivARB */
    {  243, 1516 }, /* glUniform1ui and glUniform1uiEXT */
    {  247, 1520 }, /* glUniform1uiv and glUniform1uivEXT */
    {  140,  933 }, /* glUniform2f and glUniform2fARB */
    {  148,  941 }, /* glUniform2fv and glUniform2fvARB */
    {  144,  937 }, /* glUniform2i and glUniform2iARB */
    {  152,  945 }, /* glUniform2iv and glUniform2ivARB */
    {  244, 1517 }, /* glUniform2ui and glUniform2uiEXT */
    {  248, 1521 }, /* glUniform2uiv and glUniform2uivEXT */
    {  141,  934 }, /* glUniform3f and glUniform3fARB */
    {  149,  942 }, /* glUniform3fv and glUniform3fvARB */
    {  145,  938 }, /* glUniform3i and glUniform3iARB */
    {  153,  946 }, /* glUniform3iv and glUniform3ivARB */
    {  245, 1518 }, /* glUniform3ui and glUniform3uiEXT */
    {  249, 1522 }, /* glUniform3uiv and glUniform3uivEXT */
    {  142,  935 }, /* glUniform4f and glUniform4fARB */
    {  150,  943 }, /* glUniform4fv and glUniform4fvARB */
    {  146,  939 }, /* glUniform4i and glUniform4iARB */
    {  154,  947 }, /* glUniform4iv and glUniform4ivARB */
    {  246, 1519 }, /* glUniform4ui and glUniform4uiEXT */
    {  250, 1523 }, /* glUniform4uiv and glUniform4uivEXT */
    {  772, 2642 }, /* glUniformHandleui64ARB and glUniformHandleui64IMG */
    {  773, 2643 }, /* glUniformHandleui64vARB and glUniformHandleui64vIMG */
    {  155,  948 }, /* glUniformMatrix2fv and glUniformMatrix2fvARB */
    {  196, 2675 }, /* glUniformMatrix2x3fv and glUniformMatrix2x3fvNV */
    {  198, 2677 }, /* glUniformMatrix2x4fv and glUniformMatrix2x4fvNV */
    {  156,  949 }, /* glUniformMatrix3fv and glUniformMatrix3fvARB */
    {  197, 2676 }, /* glUniformMatrix3x2fv and glUniformMatrix3x2fvNV */
    {  200, 2679 }, /* glUniformMatrix3x4fv and glUniformMatrix3x4fvNV */
    {  157,  950 }, /* glUniformMatrix4fv and glUniformMatrix4fvARB */
    {  199, 2678 }, /* glUniformMatrix4x2fv and glUniformMatrix4x2fvNV */
    {  201, 2680 }, /* glUniformMatrix4x3fv and glUniformMatrix4x3fvNV */
    {  100, 1000 }, /* glUnmapBuffer and glUnmapBufferARB */
    {  100, 2713 }, /* glUnmapBuffer and glUnmapBufferOES */
    {  138,  930 }, /* glUseProgram and glUseProgramObjectARB */
    {  158,  931 }, /* glValidateProgram and glValidateProgramARB */
    {  159, 1003 }, /* glVertexAttrib1d and glVertexAttrib1dARB */
    {  159, 2217 }, /* glVertexAttrib1d and glVertexAttrib1dNV */
    {  160, 1004 }, /* glVertexAttrib1dv and glVertexAttrib1dvARB */
    {  160, 2218 }, /* glVertexAttrib1dv and glVertexAttrib1dvNV */
    {  161, 1005 }, /* glVertexAttrib1f and glVertexAttrib1fARB */
    {  161, 2219 }, /* glVertexAttrib1f and glVertexAttrib1fNV */
    {  162, 1006 }, /* glVertexAttrib1fv and glVertexAttrib1fvARB */
    {  162, 2220 }, /* glVertexAttrib1fv and glVertexAttrib1fvNV */
    {  163, 1007 }, /* glVertexAttrib1s and glVertexAttrib1sARB */
    {  163, 2221 }, /* glVertexAttrib1s and glVertexAttrib1sNV */
    {  164, 1008 }, /* glVertexAttrib1sv and glVertexAttrib1svARB */
    {  164, 2222 }, /* glVertexAttrib1sv and glVertexAttrib1svNV */
    {  165, 1009 }, /* glVertexAttrib2d and glVertexAttrib2dARB */
    {  165, 2223 }, /* glVertexAttrib2d and glVertexAttrib2dNV */
    {  166, 1010 }, /* glVertexAttrib2dv and glVertexAttrib2dvARB */
    {  166, 2224 }, /* glVertexAttrib2dv and glVertexAttrib2dvNV */
    {  167, 1011 }, /* glVertexAttrib2f and glVertexAttrib2fARB */
    {  167, 2225 }, /* glVertexAttrib2f and glVertexAttrib2fNV */
    {  168, 1012 }, /* glVertexAttrib2fv and glVertexAttrib2fvARB */
    {  168, 2226 }, /* glVertexAttrib2fv and glVertexAttrib2fvNV */
    {  169, 1013 }, /* glVertexAttrib2s and glVertexAttrib2sARB */
    {  169, 2227 }, /* glVertexAttrib2s and glVertexAttrib2sNV */
    {  170, 1014 }, /* glVertexAttrib2sv and glVertexAttrib2svARB */
    {  170, 2228 }, /* glVertexAttrib2sv and glVertexAttrib2svNV */
    {  171, 1015 }, /* glVertexAttrib3d and glVertexAttrib3dARB */
    {  171, 2229 }, /* glVertexAttrib3d and glVertexAttrib3dNV */
    {  172, 1016 }, /* glVertexAttrib3dv and glVertexAttrib3dvARB */
    {  172, 2230 }, /* glVertexAttrib3dv and glVertexAttrib3dvNV */
    {  173, 1017 }, /* glVertexAttrib3f and glVertexAttrib3fARB */
    {  173, 2231 }, /* glVertexAttrib3f and glVertexAttrib3fNV */
    {  174, 1018 }, /* glVertexAttrib3fv and glVertexAttrib3fvARB */
    {  174, 2232 }, /* glVertexAttrib3fv and glVertexAttrib3fvNV */
    {  175, 1019 }, /* glVertexAttrib3s and glVertexAttrib3sARB */
    {  175, 2233 }, /* glVertexAttrib3s and glVertexAttrib3sNV */
    {  176, 1020 }, /* glVertexAttrib3sv and glVertexAttrib3svARB */
    {  176, 2234 }, /* glVertexAttrib3sv and glVertexAttrib3svNV */
    {  184, 1028 }, /* glVertexAttrib4bv and glVertexAttrib4bvARB */
    {  185, 1029 }, /* glVertexAttrib4d and glVertexAttrib4dARB */
    {  185, 2235 }, /* glVertexAttrib4d and glVertexAttrib4dNV */
    {  186, 1030 }, /* glVertexAttrib4dv and glVertexAttrib4dvARB */
    {  186, 2236 }, /* glVertexAttrib4dv and glVertexAttrib4dvNV */
    {  187, 1031 }, /* glVertexAttrib4f and glVertexAttrib4fARB */
    {  187, 2237 }, /* glVertexAttrib4f and glVertexAttrib4fNV */
    {  188, 1032 }, /* glVertexAttrib4fv and glVertexAttrib4fvARB */
    {  188, 2238 }, /* glVertexAttrib4fv and glVertexAttrib4fvNV */
    {  189, 1033 }, /* glVertexAttrib4iv and glVertexAttrib4ivARB */
    {  177, 1021 }, /* glVertexAttrib4Nbv and glVertexAttrib4NbvARB */
    {  178, 1022 }, /* glVertexAttrib4Niv and glVertexAttrib4NivARB */
    {  179, 1023 }, /* glVertexAttrib4Nsv and glVertexAttrib4NsvARB */
    {  180, 1024 }, /* glVertexAttrib4Nub and glVertexAttrib4NubARB */
    {  180, 2241 }, /* glVertexAttrib4Nub and glVertexAttrib4ubNV */
    {  181, 1025 }, /* glVertexAttrib4Nubv and glVertexAttrib4NubvARB */
    {  181, 2242 }, /* glVertexAttrib4Nubv and glVertexAttrib4ubvNV */
    {  182, 1026 }, /* glVertexAttrib4Nuiv and glVertexAttrib4NuivARB */
    {  183, 1027 }, /* glVertexAttrib4Nusv and glVertexAttrib4NusvARB */
    {  190, 1034 }, /* glVertexAttrib4s and glVertexAttrib4sARB */
    {  190, 2239 }, /* glVertexAttrib4s and glVertexAttrib4sNV */
    {  191, 1035 }, /* glVertexAttrib4sv and glVertexAttrib4svARB */
    {  191, 2240 }, /* glVertexAttrib4sv and glVertexAttrib4svNV */
    {  192, 1036 }, /* glVertexAttrib4ubv and glVertexAttrib4ubvARB */
    {  193, 1037 }, /* glVertexAttrib4uiv and glVertexAttrib4uivARB */
    {  194, 1038 }, /* glVertexAttrib4usv and glVertexAttrib4usvARB */
    {  336, 2553 }, /* glVertexAttribDivisor and glVertexAttribDivisorANGLE */
    {  336,  857 }, /* glVertexAttribDivisor and glVertexAttribDivisorARB */
    {  336, 2603 }, /* glVertexAttribDivisor and glVertexAttribDivisorEXT */
    {  336, 2674 }, /* glVertexAttribDivisor and glVertexAttribDivisorNV */
    {  220, 1524 }, /* glVertexAttribI1i and glVertexAttribI1iEXT */
    {  228, 1532 }, /* glVertexAttribI1iv and glVertexAttribI1ivEXT */
    {  224, 1528 }, /* glVertexAttribI1ui and glVertexAttribI1uiEXT */
    {  232, 1536 }, /* glVertexAttribI1uiv and glVertexAttribI1uivEXT */
    {  221, 1525 }, /* glVertexAttribI2i and glVertexAttribI2iEXT */
    {  229, 1533 }, /* glVertexAttribI2iv and glVertexAttribI2ivEXT */
    {  225, 1529 }, /* glVertexAttribI2ui and glVertexAttribI2uiEXT */
    {  233, 1537 }, /* glVertexAttribI2uiv and glVertexAttribI2uivEXT */
    {  222, 1526 }, /* glVertexAttribI3i and glVertexAttribI3iEXT */
    {  230, 1534 }, /* glVertexAttribI3iv and glVertexAttribI3ivEXT */
    {  226, 1530 }, /* glVertexAttribI3ui and glVertexAttribI3uiEXT */
    {  234, 1538 }, /* glVertexAttribI3uiv and glVertexAttribI3uivEXT */
    {  236, 1540 }, /* glVertexAttribI4bv and glVertexAttribI4bvEXT */
    {  223, 1527 }, /* glVertexAttribI4i and glVertexAttribI4iEXT */
    {  231, 1535 }, /* glVertexAttribI4iv and glVertexAttribI4ivEXT */
    {  237, 1541 }, /* glVertexAttribI4sv and glVertexAttribI4svEXT */
    {  238, 1542 }, /* glVertexAttribI4ubv and glVertexAttribI4ubvEXT */
    {  227, 1531 }, /* glVertexAttribI4ui and glVertexAttribI4uiEXT */
    {  235, 1539 }, /* glVertexAttribI4uiv and glVertexAttribI4uivEXT */
    {  239, 1543 }, /* glVertexAttribI4usv and glVertexAttribI4usvEXT */
    {  217, 1544 }, /* glVertexAttribIPointer and glVertexAttribIPointerEXT */
    {  459, 1680 }, /* glVertexAttribL1d and glVertexAttribL1dEXT */
    {  463, 1684 }, /* glVertexAttribL1dv and glVertexAttribL1dvEXT */
    {  460, 1681 }, /* glVertexAttribL2d and glVertexAttribL2dEXT */
    {  464, 1685 }, /* glVertexAttribL2dv and glVertexAttribL2dvEXT */
    {  461, 1682 }, /* glVertexAttribL3d and glVertexAttribL3dEXT */
    {  465, 1686 }, /* glVertexAttribL3dv and glVertexAttribL3dvEXT */
    {  462, 1683 }, /* glVertexAttribL4d and glVertexAttribL4dEXT */
    {  466, 1687 }, /* glVertexAttribL4dv and glVertexAttribL4dvEXT */
    {  467, 1688 }, /* glVertexAttribLPointer and glVertexAttribLPointerEXT */
    {  195, 1039 }, /* glVertexAttribPointer and glVertexAttribPointerARB */
    {  469, 2683 }, /* glViewportArrayv and glViewportArrayvNV */
    {  469, 2740 }, /* glViewportArrayv and glViewportArrayvOES */
    {  470, 2684 }, /* glViewportIndexedf and glViewportIndexedfNV */
    {  470, 2741 }, /* glViewportIndexedf and glViewportIndexedfOES */
    {  471, 2685 }, /* glViewportIndexedfv and glViewportIndexedfvNV */
    {  471, 2742 }, /* glViewportIndexedfv and glViewportIndexedfvOES */
    {  307, 2562 }, /* glWaitSync and glWaitSyncAPPLE */
};

static uint32_t glad_gl_resolve_alias_group(GladGLContext *context, const GladAliasPair_t *pairs, uint32_t start_idx, uint32_t total_count) {
    void **pfnArray = context->pfnArray;
    void *canonical_ptr;
    uint16_t canonical_idx = pairs[start_idx].first;
    uint32_t i, end_idx = start_idx;

    /* Find the end of this group (consecutive pairs with same canonical index) */
    while (end_idx < total_count && pairs[end_idx].first == canonical_idx) {
        end_idx++;
    }

    /* Pass 1: Find any loaded secondary for this canonical */
    canonical_ptr = pfnArray[canonical_idx];
    if (canonical_ptr == NULL) {
        for (i = start_idx; i < end_idx; ++i) {
            if (pfnArray[pairs[i].second] != NULL) {
                canonical_ptr = pfnArray[pairs[i].second];
                pfnArray[canonical_idx] = canonical_ptr;
                break;
            }
        }
    }

    /* Pass 2: Populate unloaded secondaries */
    if (canonical_ptr != NULL) {
        for (i = start_idx; i < end_idx; ++i) {
            if (pfnArray[pairs[i].second] == NULL) {
                pfnArray[pairs[i].second] = canonical_ptr;
            }
        }
    }

    return end_idx - 1;  /* Return index of last processed pair */
}

GLAD_NO_INLINE static void glad_gl_resolve_aliases(GladGLContext *context) {
    uint32_t i;

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_GL_command_aliases); ++i) {
        i = glad_gl_resolve_alias_group(context, GLAD_GL_command_aliases, i, GLAD_ARRAYSIZE(GLAD_GL_command_aliases));
    }
}

static void glad_gl_load_pfn_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr, uint16_t pfnStart, uint32_t numPfns)
{
    uint32_t pfnIdx;

    for (pfnIdx = pfnStart; pfnIdx < pfnStart + numPfns; ++pfnIdx) {
        context->pfnArray[pfnIdx] = (void *)load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static int glad_gl_get_extensions(GladGLContext *context, uint64_t **out_exts, uint32_t *out_num_exts) {
    uint32_t num_exts = 0;
    uint64_t *exts = NULL;
    const char *exts_str = NULL;
    const char *cur = NULL;
    const char *next = NULL;
    uint32_t j;
    size_t len;

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
            len = strlen(gl_str_tmp);
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
         * extensions. The second pass hashes their names and stores them in
         * a heap-allocated uint64 array for searching.
         */
        for (j = 0; j < 2; ++j) {
            num_exts = 0;
            cur = exts_str;
            next = cur + strcspn(cur, " ");
            while (1) {
                cur += strspn(cur, " ");

                if (!cur[0])
                    break;

                len = (size_t)(next - cur);

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

    /* Sort extension list for binary search */
    glad_sort_hashes(exts, num_exts);

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
         322, /* GL_EXT_bfloat16 */
         323, /* GL_EXT_bgra */
         324, /* GL_EXT_bindable_uniform */
         325, /* GL_EXT_blend_color */
         326, /* GL_EXT_blend_equation_separate */
         328, /* GL_EXT_blend_func_separate */
         329, /* GL_EXT_blend_logic_op */
         330, /* GL_EXT_blend_minmax */
         331, /* GL_EXT_blend_subtract */
         332, /* GL_EXT_buffer_reference */
         333, /* GL_EXT_buffer_reference2 */
         334, /* GL_EXT_buffer_reference_uvec2 */
         339, /* GL_EXT_clip_volume_hint */
         340, /* GL_EXT_cmyka */
         343, /* GL_EXT_color_subtable */
         344, /* GL_EXT_compiled_vertex_array */
         346, /* GL_EXT_control_flow_attributes */
         347, /* GL_EXT_control_flow_attributes2 */
         348, /* GL_EXT_convolution */
         349, /* GL_EXT_coordinate_frame */
         351, /* GL_EXT_copy_texture */
         352, /* GL_EXT_cull_vertex */
         353, /* GL_EXT_debug_label */
         354, /* GL_EXT_debug_marker */
         355, /* GL_EXT_debug_printf */
         356, /* GL_EXT_demote_to_helper_invocation */
         357, /* GL_EXT_depth_bounds_test */
         359, /* GL_EXT_device_group */
         360, /* GL_EXT_direct_state_access */
         364, /* GL_EXT_draw_buffers2 */
         367, /* GL_EXT_draw_instanced */
         368, /* GL_EXT_draw_range_elements */
         370, /* GL_EXT_expect_assume */
         371, /* GL_EXT_external_buffer */
         372, /* GL_EXT_float8_e5m2_e4m3 */
         374, /* GL_EXT_fog_coord */
         375, /* GL_EXT_fragment_invocation_density */
         376, /* GL_EXT_fragment_shader_barycentric */
         377, /* GL_EXT_fragment_shading_rate */
         378, /* GL_EXT_framebuffer_blit */
         379, /* GL_EXT_framebuffer_blit_layers */
         380, /* GL_EXT_framebuffer_multisample */
         381, /* GL_EXT_framebuffer_multisample_blit_scaled */
         382, /* GL_EXT_framebuffer_object */
         383, /* GL_EXT_framebuffer_sRGB */
         386, /* GL_EXT_geometry_shader4 */
         387, /* GL_EXT_gpu_program_parameters */
         388, /* GL_EXT_gpu_shader4 */
         390, /* GL_EXT_histogram */
         391, /* GL_EXT_index_array_formats */
         392, /* GL_EXT_index_func */
         393, /* GL_EXT_index_material */
         394, /* GL_EXT_index_texture */
         396, /* GL_EXT_integer_dot_product */
         397, /* GL_EXT_light_texture */
         399, /* GL_EXT_maximal_reconvergence */
         400, /* GL_EXT_memory_object */
         401, /* GL_EXT_memory_object_fd */
         402, /* GL_EXT_memory_object_win32 */
         403, /* GL_EXT_mesh_shader */
         404, /* GL_EXT_misc_attribute */
         405, /* GL_EXT_multi_draw_arrays */
         407, /* GL_EXT_multisample */
         412, /* GL_EXT_multiview_tessellation_geometry_shader */
         413, /* GL_EXT_multiview_texture_multisample */
         414, /* GL_EXT_multiview_timer_query */
         415, /* GL_EXT_nontemporal_keyword */
         416, /* GL_EXT_nonuniform_qualifier */
         417, /* GL_EXT_null_initializer */
         419, /* GL_EXT_opacity_micromap */
         420, /* GL_EXT_packed_depth_stencil */
         421, /* GL_EXT_packed_float */
         422, /* GL_EXT_packed_pixels */
         423, /* GL_EXT_paletted_texture */
         424, /* GL_EXT_pixel_buffer_object */
         425, /* GL_EXT_pixel_transform */
         426, /* GL_EXT_pixel_transform_color_table */
         427, /* GL_EXT_point_parameters */
         428, /* GL_EXT_polygon_offset */
         429, /* GL_EXT_polygon_offset_clamp */
         430, /* GL_EXT_post_depth_coverage */
         433, /* GL_EXT_provoking_vertex */
         435, /* GL_EXT_raster_multisample */
         436, /* GL_EXT_ray_cull_mask */
         437, /* GL_EXT_ray_flags_primitive_culling */
         438, /* GL_EXT_ray_query */
         439, /* GL_EXT_ray_tracing */
         440, /* GL_EXT_ray_tracing_position_fetch */
         443, /* GL_EXT_rescale_normal */
         447, /* GL_EXT_samplerless_texture_functions */
         448, /* GL_EXT_scalar_block_layout */
         449, /* GL_EXT_secondary_color */
         450, /* GL_EXT_semaphore */
         451, /* GL_EXT_semaphore_fd */
         452, /* GL_EXT_semaphore_win32 */
         454, /* GL_EXT_separate_shader_objects */
         455, /* GL_EXT_separate_specular_color */
         456, /* GL_EXT_shader_16bit_storage */
         457, /* GL_EXT_shader_8bit_storage */
         458, /* GL_EXT_shader_atomic_float */
         459, /* GL_EXT_shader_atomic_float2 */
         460, /* GL_EXT_shader_atomic_int64 */
         461, /* GL_EXT_shader_explicit_arithmetic_types */
         462, /* GL_EXT_shader_explicit_arithmetic_types_float16 */
         463, /* GL_EXT_shader_explicit_arithmetic_types_float32 */
         464, /* GL_EXT_shader_explicit_arithmetic_types_float64 */
         465, /* GL_EXT_shader_explicit_arithmetic_types_int16 */
         466, /* GL_EXT_shader_explicit_arithmetic_types_int32 */
         467, /* GL_EXT_shader_explicit_arithmetic_types_int64 */
         468, /* GL_EXT_shader_explicit_arithmetic_types_int8 */
         469, /* GL_EXT_shader_framebuffer_fetch */
         470, /* GL_EXT_shader_framebuffer_fetch_non_coherent */
         472, /* GL_EXT_shader_image_int64 */
         473, /* GL_EXT_shader_image_load_formatted */
         474, /* GL_EXT_shader_image_load_store */
         476, /* GL_EXT_shader_integer_mix */
         481, /* GL_EXT_shader_quad_control */
         482, /* GL_EXT_shader_realtime_clock */
         483, /* GL_EXT_shader_samples_identical */
         484, /* GL_EXT_shader_subgroup_extended_types */
         485, /* GL_EXT_shader_subgroup_extended_types_float16 */
         486, /* GL_EXT_shader_subgroup_extended_types_int16 */
         487, /* GL_EXT_shader_subgroup_extended_types_int64 */
         488, /* GL_EXT_shader_subgroup_extended_types_int8 */
         491, /* GL_EXT_shader_tile_image */
         492, /* GL_EXT_shadow_funcs */
         494, /* GL_EXT_shared_memory_block */
         495, /* GL_EXT_shared_texture_palette */
         497, /* GL_EXT_sparse_texture2 */
         498, /* GL_EXT_spec_constant_composites */
         499, /* GL_EXT_spirv_intrinsics */
         500, /* GL_EXT_stencil_clear_tag */
         501, /* GL_EXT_stencil_two_side */
         502, /* GL_EXT_stencil_wrap */
         503, /* GL_EXT_subgroup_uniform_control_flow */
         504, /* GL_EXT_subgroupuniform_qualifier */
         505, /* GL_EXT_subtexture */
         506, /* GL_EXT_terminate_invocation */
         509, /* GL_EXT_texture */
         510, /* GL_EXT_texture3D */
         511, /* GL_EXT_texture_array */
         514, /* GL_EXT_texture_buffer_object */
         518, /* GL_EXT_texture_compression_latc */
         519, /* GL_EXT_texture_compression_rgtc */
         520, /* GL_EXT_texture_compression_s3tc */
         522, /* GL_EXT_texture_cube_map */
         524, /* GL_EXT_texture_env_add */
         525, /* GL_EXT_texture_env_combine */
         526, /* GL_EXT_texture_env_dot3 */
         527, /* GL_EXT_texture_filter_anisotropic */
         528, /* GL_EXT_texture_filter_minmax */
         531, /* GL_EXT_texture_integer */
         532, /* GL_EXT_texture_lod_bias */
         533, /* GL_EXT_texture_mirror_clamp */
         536, /* GL_EXT_texture_object */
         537, /* GL_EXT_texture_offset_non_const */
         538, /* GL_EXT_texture_perturb_normal */
         541, /* GL_EXT_texture_sRGB */
         542, /* GL_EXT_texture_sRGB_R8 */
         543, /* GL_EXT_texture_sRGB_RG8 */
         544, /* GL_EXT_texture_sRGB_decode */
         545, /* GL_EXT_texture_shadow_lod */
         546, /* GL_EXT_texture_shared_exponent */
         547, /* GL_EXT_texture_snorm */
         548, /* GL_EXT_texture_storage */
         550, /* GL_EXT_texture_swizzle */
         553, /* GL_EXT_timer_query */
         554, /* GL_EXT_transform_feedback */
         556, /* GL_EXT_vertex_array */
         557, /* GL_EXT_vertex_array_bgra */
         558, /* GL_EXT_vertex_attrib_64bit */
         559, /* GL_EXT_vertex_shader */
         560, /* GL_EXT_vertex_weighting */
         561, /* GL_EXT_vulkan_glsl_relaxed */
         562, /* GL_EXT_win32_keyed_mutex */
         563, /* GL_EXT_window_rectangles */
         564, /* GL_EXT_x11_sync_object */
         566, /* GL_GREMEDY_frame_terminator */
         567, /* GL_GREMEDY_string_marker */
         568, /* GL_HP_convolution_border_modes */
         569, /* GL_HP_image_transform */
         570, /* GL_HP_occlusion_test */
         571, /* GL_HP_texture_lighting */
         572, /* GL_HUAWEI_cluster_culling_shader */
         575, /* GL_HUAWEI_subpass_shading */
         576, /* GL_IBM_cull_vertex */
         577, /* GL_IBM_multimode_draw_arrays */
         578, /* GL_IBM_rasterpos_clip */
         579, /* GL_IBM_static_data */
         580, /* GL_IBM_texture_mirrored_repeat */
         581, /* GL_IBM_vertex_array_lists */
         591, /* GL_INGR_blend_func_separate */
         592, /* GL_INGR_color_clamp */
         593, /* GL_INGR_interlace_read */
         594, /* GL_INTEL_blackhole_render */
         595, /* GL_INTEL_conservative_rasterization */
         596, /* GL_INTEL_fragment_shader_ordering */
         597, /* GL_INTEL_framebuffer_CMAA */
         598, /* GL_INTEL_map_texture */
         599, /* GL_INTEL_parallel_arrays */
         600, /* GL_INTEL_performance_query */
         601, /* GL_KHR_blend_equation_advanced */
         602, /* GL_KHR_blend_equation_advanced_coherent */
         603, /* GL_KHR_context_flush_control */
         604, /* GL_KHR_cooperative_matrix */
         605, /* GL_KHR_debug */
         606, /* GL_KHR_memory_scope_semantics */
         607, /* GL_KHR_no_error */
         608, /* GL_KHR_parallel_shader_compile */
         609, /* GL_KHR_robust_buffer_access_behavior */
         610, /* GL_KHR_robustness */
         611, /* GL_KHR_shader_subgroup */
         612, /* GL_KHR_shader_subgroup_arithmetic */
         613, /* GL_KHR_shader_subgroup_ballot */
         614, /* GL_KHR_shader_subgroup_basic */
         615, /* GL_KHR_shader_subgroup_clustered */
         616, /* GL_KHR_shader_subgroup_quad */
         617, /* GL_KHR_shader_subgroup_rotate */
         618, /* GL_KHR_shader_subgroup_shuffle */
         619, /* GL_KHR_shader_subgroup_shuffle_relative */
         620, /* GL_KHR_shader_subgroup_vote */
         621, /* GL_KHR_texture_compression_astc_hdr */
         622, /* GL_KHR_texture_compression_astc_ldr */
         623, /* GL_KHR_texture_compression_astc_sliced_3d */
         624, /* GL_KHR_vulkan_glsl */
         625, /* GL_MESAX_texture_stack */
         627, /* GL_MESA_framebuffer_flip_x */
         628, /* GL_MESA_framebuffer_flip_y */
         629, /* GL_MESA_framebuffer_swap_xy */
         630, /* GL_MESA_map_buffer_client_pointer */
         631, /* GL_MESA_pack_invert */
         632, /* GL_MESA_program_binary_formats */
         633, /* GL_MESA_resize_buffers */
         635, /* GL_MESA_shader_integer_functions */
         636, /* GL_MESA_texture_const_bandwidth */
         637, /* GL_MESA_tile_raster_order */
         638, /* GL_MESA_window_pos */
         639, /* GL_MESA_ycbcr_texture */
         640, /* GL_NVX_blend_equation_advanced_multi_draw_buffers */
         641, /* GL_NVX_conditional_render */
         642, /* GL_NVX_gpu_memory_info */
         643, /* GL_NVX_gpu_multicast2 */
         644, /* GL_NVX_linked_gpu_multicast */
         645, /* GL_NVX_multiview_per_view_attributes */
         646, /* GL_NVX_progress_fence */
         647, /* GL_NV_alpha_to_coverage_dither_control */
         648, /* GL_NV_bindless_multi_draw_indirect */
         649, /* GL_NV_bindless_multi_draw_indirect_count */
         650, /* GL_NV_bindless_texture */
         651, /* GL_NV_blend_equation_advanced */
         652, /* GL_NV_blend_equation_advanced_coherent */
         653, /* GL_NV_blend_minmax_factor */
         654, /* GL_NV_blend_square */
         655, /* GL_NV_clip_space_w_scaling */
         656, /* GL_NV_cluster_acceleration_structure */
         657, /* GL_NV_command_list */
         658, /* GL_NV_compute_program5 */
         659, /* GL_NV_compute_shader_derivatives */
         660, /* GL_NV_conditional_render */
         661, /* GL_NV_conservative_raster */
         662, /* GL_NV_conservative_raster_dilate */
         663, /* GL_NV_conservative_raster_pre_snap */
         664, /* GL_NV_conservative_raster_pre_snap_triangles */
         665, /* GL_NV_conservative_raster_underestimation */
         666, /* GL_NV_cooperative_matrix */
         667, /* GL_NV_cooperative_matrix2 */
         668, /* GL_NV_cooperative_vector */
         670, /* GL_NV_copy_depth_to_color */
         671, /* GL_NV_copy_image */
         673, /* GL_NV_deep_texture3D */
         674, /* GL_NV_depth_buffer_float */
         675, /* GL_NV_depth_clamp */
         677, /* GL_NV_displacement_micromap */
         680, /* GL_NV_draw_texture */
         681, /* GL_NV_draw_vulkan_image */
         682, /* GL_NV_evaluators */
         684, /* GL_NV_explicit_multisample */
         686, /* GL_NV_fence */
         687, /* GL_NV_fill_rectangle */
         688, /* GL_NV_float_buffer */
         689, /* GL_NV_fog_distance */
         690, /* GL_NV_fragment_coverage_to_color */
         691, /* GL_NV_fragment_program */
         692, /* GL_NV_fragment_program2 */
         693, /* GL_NV_fragment_program4 */
         694, /* GL_NV_fragment_program_option */
         695, /* GL_NV_fragment_shader_barycentric */
         696, /* GL_NV_fragment_shader_interlock */
         698, /* GL_NV_framebuffer_mixed_samples */
         700, /* GL_NV_framebuffer_multisample_coverage */
         702, /* GL_NV_geometry_program4 */
         703, /* GL_NV_geometry_shader4 */
         704, /* GL_NV_geometry_shader_passthrough */
         705, /* GL_NV_gpu_multicast */
         706, /* GL_NV_gpu_program4 */
         707, /* GL_NV_gpu_program5 */
         708, /* GL_NV_gpu_program5_mem_extended */
         709, /* GL_NV_gpu_shader5 */
         710, /* GL_NV_half_float */
         713, /* GL_NV_integer_cooperative_matrix */
         714, /* GL_NV_internalformat_sample_query */
         715, /* GL_NV_light_max_exponent */
         716, /* GL_NV_linear_swept_spheres */
         717, /* GL_NV_memory_attachment */
         718, /* GL_NV_memory_object_sparse */
         719, /* GL_NV_mesh_shader */
         720, /* GL_NV_multisample_coverage */
         721, /* GL_NV_multisample_filter_hint */
         723, /* GL_NV_occlusion_query */
         725, /* GL_NV_packed_depth_stencil */
         726, /* GL_NV_parameter_buffer_object */
         727, /* GL_NV_parameter_buffer_object2 */
         728, /* GL_NV_path_rendering */
         729, /* GL_NV_path_rendering_shared_edge */
         731, /* GL_NV_pixel_data_range */
         732, /* GL_NV_point_sprite */
         734, /* GL_NV_present_video */
         735, /* GL_NV_primitive_restart */
         736, /* GL_NV_primitive_shading_rate */
         737, /* GL_NV_query_resource */
         738, /* GL_NV_query_resource_tag */
         739, /* GL_NV_ray_tracing */
         740, /* GL_NV_ray_tracing_motion_blur */
         746, /* GL_NV_register_combiners */
         747, /* GL_NV_register_combiners2 */
         748, /* GL_NV_representative_fragment_test */
         749, /* GL_NV_robustness_video_memory_purge */
         751, /* GL_NV_sample_locations */
         752, /* GL_NV_sample_mask_override_coverage */
         753, /* GL_NV_scissor_exclusive */
         754, /* GL_NV_shader_atomic_counters */
         755, /* GL_NV_shader_atomic_float */
         756, /* GL_NV_shader_atomic_float64 */
         757, /* GL_NV_shader_atomic_fp16_vector */
         758, /* GL_NV_shader_atomic_int64 */
         759, /* GL_NV_shader_buffer_load */
         760, /* GL_NV_shader_buffer_store */
         761, /* GL_NV_shader_invocation_reorder */
         763, /* GL_NV_shader_sm_builtins */
         764, /* GL_NV_shader_storage_buffer_object */
         765, /* GL_NV_shader_subgroup_partitioned */
         766, /* GL_NV_shader_texture_footprint */
         767, /* GL_NV_shader_thread_group */
         768, /* GL_NV_shader_thread_shuffle */
         769, /* GL_NV_shading_rate_image */
         772, /* GL_NV_stereo_view_rendering */
         773, /* GL_NV_tessellation_program5 */
         774, /* GL_NV_texgen_emboss */
         775, /* GL_NV_texgen_reflection */
         776, /* GL_NV_texture_barrier */
         779, /* GL_NV_texture_compression_vtc */
         780, /* GL_NV_texture_env_combine4 */
         781, /* GL_NV_texture_expand_normal */
         782, /* GL_NV_texture_multisample */
         784, /* GL_NV_texture_rectangle */
         785, /* GL_NV_texture_rectangle_compressed */
         786, /* GL_NV_texture_shader */
         787, /* GL_NV_texture_shader2 */
         788, /* GL_NV_texture_shader3 */
         789, /* GL_NV_timeline_semaphore */
         790, /* GL_NV_transform_feedback */
         791, /* GL_NV_transform_feedback2 */
         792, /* GL_NV_uniform_buffer_std430_layout */
         793, /* GL_NV_uniform_buffer_unified_memory */
         794, /* GL_NV_vdpau_interop */
         795, /* GL_NV_vdpau_interop2 */
         796, /* GL_NV_vertex_array_range */
         797, /* GL_NV_vertex_array_range2 */
         798, /* GL_NV_vertex_attrib_integer_64bit */
         799, /* GL_NV_vertex_buffer_unified_memory */
         800, /* GL_NV_vertex_program */
         801, /* GL_NV_vertex_program1_1 */
         802, /* GL_NV_vertex_program2 */
         803, /* GL_NV_vertex_program2_option */
         804, /* GL_NV_vertex_program3 */
         805, /* GL_NV_vertex_program4 */
         806, /* GL_NV_video_capture */
         808, /* GL_NV_viewport_array2 */
         809, /* GL_NV_viewport_swizzle */
         813, /* GL_OES_byte_coordinates */
         816, /* GL_OES_compressed_paletted_texture */
         825, /* GL_OES_fixed_point */
         834, /* GL_OES_query_matrix */
         835, /* GL_OES_read_format */
         843, /* GL_OES_single_precision */
         867, /* GL_OML_interlace */
         868, /* GL_OML_resample */
         869, /* GL_OML_subsample */
         870, /* GL_OVR_multiview */
         871, /* GL_OVR_multiview2 */
         873, /* GL_PGI_misc_hints */
         874, /* GL_PGI_vertex_hints */
         878, /* GL_QCOM_cooperative_matrix_conversion */
         884, /* GL_QCOM_image_processing */
         885, /* GL_QCOM_image_processing2 */
         897, /* GL_QCOM_tile_shading */
         901, /* GL_REND_screen_coordinates */
         902, /* GL_S3_s3tc */
         903, /* GL_SGIS_detail_texture */
         904, /* GL_SGIS_fog_function */
         905, /* GL_SGIS_generate_mipmap */
         906, /* GL_SGIS_multisample */
         907, /* GL_SGIS_pixel_texture */
         908, /* GL_SGIS_point_line_texgen */
         909, /* GL_SGIS_point_parameters */
         910, /* GL_SGIS_sharpen_texture */
         911, /* GL_SGIS_texture4D */
         912, /* GL_SGIS_texture_border_clamp */
         913, /* GL_SGIS_texture_color_mask */
         914, /* GL_SGIS_texture_edge_clamp */
         915, /* GL_SGIS_texture_filter4 */
         916, /* GL_SGIS_texture_lod */
         917, /* GL_SGIS_texture_select */
         918, /* GL_SGIX_async */
         919, /* GL_SGIX_async_histogram */
         920, /* GL_SGIX_async_pixel */
         921, /* GL_SGIX_blend_alpha_minmax */
         922, /* GL_SGIX_calligraphic_fragment */
         923, /* GL_SGIX_clipmap */
         924, /* GL_SGIX_convolution_accuracy */
         925, /* GL_SGIX_depth_pass_instrument */
         926, /* GL_SGIX_depth_texture */
         927, /* GL_SGIX_flush_raster */
         928, /* GL_SGIX_fog_offset */
         929, /* GL_SGIX_fragment_lighting */
         930, /* GL_SGIX_framezoom */
         931, /* GL_SGIX_igloo_interface */
         932, /* GL_SGIX_instruments */
         933, /* GL_SGIX_interlace */
         934, /* GL_SGIX_ir_instrument1 */
         935, /* GL_SGIX_list_priority */
         936, /* GL_SGIX_pixel_texture */
         937, /* GL_SGIX_pixel_tiles */
         938, /* GL_SGIX_polynomial_ffd */
         939, /* GL_SGIX_reference_plane */
         940, /* GL_SGIX_resample */
         941, /* GL_SGIX_scalebias_hint */
         942, /* GL_SGIX_shadow */
         943, /* GL_SGIX_shadow_ambient */
         944, /* GL_SGIX_sprite */
         945, /* GL_SGIX_subsample */
         946, /* GL_SGIX_tag_sample_buffer */
         947, /* GL_SGIX_texture_add_env */
         948, /* GL_SGIX_texture_coordinate_clamp */
         949, /* GL_SGIX_texture_lod_bias */
         950, /* GL_SGIX_texture_multi_buffer */
         951, /* GL_SGIX_texture_scale_bias */
         952, /* GL_SGIX_vertex_preclip */
         953, /* GL_SGIX_ycrcb */
         954, /* GL_SGIX_ycrcb_subsample */
         955, /* GL_SGIX_ycrcba */
         956, /* GL_SGI_color_matrix */
         957, /* GL_SGI_color_table */
         958, /* GL_SGI_texture_color_table */
         959, /* GL_SUNX_constant_data */
         960, /* GL_SUN_convolution_border_modes */
         961, /* GL_SUN_global_alpha */
         962, /* GL_SUN_mesh_array */
         963, /* GL_SUN_slice_accum */
         964, /* GL_SUN_triangle_list */
         965, /* GL_SUN_vertex */
         967, /* GL_WIN_phong_shading */
         968, /* GL_WIN_specular_fog */
    };
    uint64_t *exts = NULL;
    uint32_t num_exts = 0;
    uint32_t i;
    if (!glad_gl_get_extensions(context, &exts, &num_exts)) return 0;

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

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_gl_ext_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_gl_ext_pfn_ranges[i];
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
         322, /* GL_EXT_bfloat16 */
         327, /* GL_EXT_blend_func_extended */
         330, /* GL_EXT_blend_minmax */
         332, /* GL_EXT_buffer_reference */
         333, /* GL_EXT_buffer_reference2 */
         334, /* GL_EXT_buffer_reference_uvec2 */
         335, /* GL_EXT_buffer_storage */
         336, /* GL_EXT_clear_texture */
         337, /* GL_EXT_clip_control */
         338, /* GL_EXT_clip_cull_distance */
         341, /* GL_EXT_color_buffer_float */
         342, /* GL_EXT_color_buffer_half_float */
         345, /* GL_EXT_conservative_depth */
         346, /* GL_EXT_control_flow_attributes */
         347, /* GL_EXT_control_flow_attributes2 */
         350, /* GL_EXT_copy_image */
         353, /* GL_EXT_debug_label */
         354, /* GL_EXT_debug_marker */
         356, /* GL_EXT_demote_to_helper_invocation */
         358, /* GL_EXT_depth_clamp */
         359, /* GL_EXT_device_group */
         361, /* GL_EXT_discard_framebuffer */
         362, /* GL_EXT_disjoint_timer_query */
         363, /* GL_EXT_draw_buffers */
         365, /* GL_EXT_draw_buffers_indexed */
         366, /* GL_EXT_draw_elements_base_vertex */
         367, /* GL_EXT_draw_instanced */
         369, /* GL_EXT_draw_transform_feedback */
         370, /* GL_EXT_expect_assume */
         371, /* GL_EXT_external_buffer */
         372, /* GL_EXT_float8_e5m2_e4m3 */
         373, /* GL_EXT_float_blend */
         375, /* GL_EXT_fragment_invocation_density */
         376, /* GL_EXT_fragment_shader_barycentric */
         377, /* GL_EXT_fragment_shading_rate */
         379, /* GL_EXT_framebuffer_blit_layers */
         384, /* GL_EXT_geometry_point_size */
         385, /* GL_EXT_geometry_shader */
         389, /* GL_EXT_gpu_shader5 */
         395, /* GL_EXT_instanced_arrays */
         396, /* GL_EXT_integer_dot_product */
         398, /* GL_EXT_map_buffer_range */
         399, /* GL_EXT_maximal_reconvergence */
         400, /* GL_EXT_memory_object */
         401, /* GL_EXT_memory_object_fd */
         402, /* GL_EXT_memory_object_win32 */
         403, /* GL_EXT_mesh_shader */
         405, /* GL_EXT_multi_draw_arrays */
         406, /* GL_EXT_multi_draw_indirect */
         408, /* GL_EXT_multisampled_compatibility */
         409, /* GL_EXT_multisampled_render_to_texture */
         410, /* GL_EXT_multisampled_render_to_texture2 */
         411, /* GL_EXT_multiview_draw_buffers */
         412, /* GL_EXT_multiview_tessellation_geometry_shader */
         413, /* GL_EXT_multiview_texture_multisample */
         414, /* GL_EXT_multiview_timer_query */
         415, /* GL_EXT_nontemporal_keyword */
         417, /* GL_EXT_null_initializer */
         418, /* GL_EXT_occlusion_query_boolean */
         429, /* GL_EXT_polygon_offset_clamp */
         430, /* GL_EXT_post_depth_coverage */
         431, /* GL_EXT_primitive_bounding_box */
         432, /* GL_EXT_protected_textures */
         434, /* GL_EXT_pvrtc_sRGB */
         435, /* GL_EXT_raster_multisample */
         441, /* GL_EXT_read_format_bgra */
         442, /* GL_EXT_render_snorm */
         444, /* GL_EXT_robustness */
         445, /* GL_EXT_sRGB */
         446, /* GL_EXT_sRGB_write_control */
         447, /* GL_EXT_samplerless_texture_functions */
         448, /* GL_EXT_scalar_block_layout */
         450, /* GL_EXT_semaphore */
         451, /* GL_EXT_semaphore_fd */
         452, /* GL_EXT_semaphore_win32 */
         453, /* GL_EXT_separate_depth_stencil */
         454, /* GL_EXT_separate_shader_objects */
         456, /* GL_EXT_shader_16bit_storage */
         457, /* GL_EXT_shader_8bit_storage */
         461, /* GL_EXT_shader_explicit_arithmetic_types */
         462, /* GL_EXT_shader_explicit_arithmetic_types_float16 */
         463, /* GL_EXT_shader_explicit_arithmetic_types_float32 */
         464, /* GL_EXT_shader_explicit_arithmetic_types_float64 */
         465, /* GL_EXT_shader_explicit_arithmetic_types_int16 */
         466, /* GL_EXT_shader_explicit_arithmetic_types_int32 */
         467, /* GL_EXT_shader_explicit_arithmetic_types_int64 */
         468, /* GL_EXT_shader_explicit_arithmetic_types_int8 */
         469, /* GL_EXT_shader_framebuffer_fetch */
         470, /* GL_EXT_shader_framebuffer_fetch_non_coherent */
         471, /* GL_EXT_shader_group_vote */
         472, /* GL_EXT_shader_image_int64 */
         475, /* GL_EXT_shader_implicit_conversions */
         476, /* GL_EXT_shader_integer_mix */
         477, /* GL_EXT_shader_io_blocks */
         478, /* GL_EXT_shader_non_constant_global_initializers */
         479, /* GL_EXT_shader_pixel_local_storage */
         480, /* GL_EXT_shader_pixel_local_storage2 */
         481, /* GL_EXT_shader_quad_control */
         483, /* GL_EXT_shader_samples_identical */
         484, /* GL_EXT_shader_subgroup_extended_types */
         485, /* GL_EXT_shader_subgroup_extended_types_float16 */
         486, /* GL_EXT_shader_subgroup_extended_types_int16 */
         487, /* GL_EXT_shader_subgroup_extended_types_int64 */
         488, /* GL_EXT_shader_subgroup_extended_types_int8 */
         489, /* GL_EXT_shader_texture_lod */
         490, /* GL_EXT_shader_texture_samples */
         493, /* GL_EXT_shadow_samplers */
         494, /* GL_EXT_shared_memory_block */
         496, /* GL_EXT_sparse_texture */
         497, /* GL_EXT_sparse_texture2 */
         498, /* GL_EXT_spec_constant_composites */
         503, /* GL_EXT_subgroup_uniform_control_flow */
         504, /* GL_EXT_subgroupuniform_qualifier */
         506, /* GL_EXT_terminate_invocation */
         507, /* GL_EXT_tessellation_point_size */
         508, /* GL_EXT_tessellation_shader */
         512, /* GL_EXT_texture_border_clamp */
         513, /* GL_EXT_texture_buffer */
         515, /* GL_EXT_texture_compression_astc_decode_mode */
         516, /* GL_EXT_texture_compression_bptc */
         517, /* GL_EXT_texture_compression_dxt1 */
         519, /* GL_EXT_texture_compression_rgtc */
         520, /* GL_EXT_texture_compression_s3tc */
         521, /* GL_EXT_texture_compression_s3tc_srgb */
         523, /* GL_EXT_texture_cube_map_array */
         527, /* GL_EXT_texture_filter_anisotropic */
         528, /* GL_EXT_texture_filter_minmax */
         529, /* GL_EXT_texture_format_BGRA8888 */
         530, /* GL_EXT_texture_format_sRGB_override */
         534, /* GL_EXT_texture_mirror_clamp_to_edge */
         535, /* GL_EXT_texture_norm16 */
         537, /* GL_EXT_texture_offset_non_const */
         539, /* GL_EXT_texture_query_lod */
         540, /* GL_EXT_texture_rg */
         542, /* GL_EXT_texture_sRGB_R8 */
         543, /* GL_EXT_texture_sRGB_RG8 */
         544, /* GL_EXT_texture_sRGB_decode */
         545, /* GL_EXT_texture_shadow_lod */
         548, /* GL_EXT_texture_storage */
         549, /* GL_EXT_texture_storage_compression */
         551, /* GL_EXT_texture_type_2_10_10_10_REV */
         552, /* GL_EXT_texture_view */
         555, /* GL_EXT_unpack_subimage */
         561, /* GL_EXT_vulkan_glsl_relaxed */
         562, /* GL_EXT_win32_keyed_mutex */
         563, /* GL_EXT_window_rectangles */
         565, /* GL_FJ_shader_binary_GCCSO */
         572, /* GL_HUAWEI_cluster_culling_shader */
         573, /* GL_HUAWEI_program_binary */
         574, /* GL_HUAWEI_shader_binary */
         575, /* GL_HUAWEI_subpass_shading */
         582, /* GL_IMG_bindless_texture */
         583, /* GL_IMG_framebuffer_downsample */
         584, /* GL_IMG_multisampled_render_to_texture */
         585, /* GL_IMG_program_binary */
         586, /* GL_IMG_read_format */
         587, /* GL_IMG_shader_binary */
         588, /* GL_IMG_texture_compression_pvrtc */
         589, /* GL_IMG_texture_compression_pvrtc2 */
         590, /* GL_IMG_texture_filter_cubic */
         594, /* GL_INTEL_blackhole_render */
         595, /* GL_INTEL_conservative_rasterization */
         597, /* GL_INTEL_framebuffer_CMAA */
         600, /* GL_INTEL_performance_query */
         601, /* GL_KHR_blend_equation_advanced */
         602, /* GL_KHR_blend_equation_advanced_coherent */
         603, /* GL_KHR_context_flush_control */
         604, /* GL_KHR_cooperative_matrix */
         605, /* GL_KHR_debug */
         606, /* GL_KHR_memory_scope_semantics */
         607, /* GL_KHR_no_error */
         608, /* GL_KHR_parallel_shader_compile */
         609, /* GL_KHR_robust_buffer_access_behavior */
         610, /* GL_KHR_robustness */
         611, /* GL_KHR_shader_subgroup */
         612, /* GL_KHR_shader_subgroup_arithmetic */
         613, /* GL_KHR_shader_subgroup_ballot */
         614, /* GL_KHR_shader_subgroup_basic */
         615, /* GL_KHR_shader_subgroup_clustered */
         616, /* GL_KHR_shader_subgroup_quad */
         617, /* GL_KHR_shader_subgroup_rotate */
         618, /* GL_KHR_shader_subgroup_shuffle */
         619, /* GL_KHR_shader_subgroup_shuffle_relative */
         620, /* GL_KHR_shader_subgroup_vote */
         621, /* GL_KHR_texture_compression_astc_hdr */
         622, /* GL_KHR_texture_compression_astc_ldr */
         623, /* GL_KHR_texture_compression_astc_sliced_3d */
         624, /* GL_KHR_vulkan_glsl */
         626, /* GL_MESA_bgra */
         627, /* GL_MESA_framebuffer_flip_x */
         628, /* GL_MESA_framebuffer_flip_y */
         629, /* GL_MESA_framebuffer_swap_xy */
         632, /* GL_MESA_program_binary_formats */
         634, /* GL_MESA_sampler_objects */
         635, /* GL_MESA_shader_integer_functions */
         636, /* GL_MESA_texture_const_bandwidth */
         640, /* GL_NVX_blend_equation_advanced_multi_draw_buffers */
         650, /* GL_NV_bindless_texture */
         651, /* GL_NV_blend_equation_advanced */
         652, /* GL_NV_blend_equation_advanced_coherent */
         653, /* GL_NV_blend_minmax_factor */
         655, /* GL_NV_clip_space_w_scaling */
         659, /* GL_NV_compute_shader_derivatives */
         660, /* GL_NV_conditional_render */
         661, /* GL_NV_conservative_raster */
         663, /* GL_NV_conservative_raster_pre_snap */
         664, /* GL_NV_conservative_raster_pre_snap_triangles */
         666, /* GL_NV_cooperative_matrix */
         667, /* GL_NV_cooperative_matrix2 */
         668, /* GL_NV_cooperative_vector */
         669, /* GL_NV_copy_buffer */
         672, /* GL_NV_coverage_sample */
         676, /* GL_NV_depth_nonlinear */
         678, /* GL_NV_draw_buffers */
         679, /* GL_NV_draw_instanced */
         681, /* GL_NV_draw_vulkan_image */
         683, /* GL_NV_explicit_attrib_location */
         685, /* GL_NV_fbo_color_attachments */
         686, /* GL_NV_fence */
         687, /* GL_NV_fill_rectangle */
         690, /* GL_NV_fragment_coverage_to_color */
         695, /* GL_NV_fragment_shader_barycentric */
         696, /* GL_NV_fragment_shader_interlock */
         697, /* GL_NV_framebuffer_blit */
         698, /* GL_NV_framebuffer_mixed_samples */
         699, /* GL_NV_framebuffer_multisample */
         701, /* GL_NV_generate_mipmap_sRGB */
         704, /* GL_NV_geometry_shader_passthrough */
         709, /* GL_NV_gpu_shader5 */
         711, /* GL_NV_image_formats */
         712, /* GL_NV_instanced_arrays */
         713, /* GL_NV_integer_cooperative_matrix */
         714, /* GL_NV_internalformat_sample_query */
         717, /* GL_NV_memory_attachment */
         718, /* GL_NV_memory_object_sparse */
         719, /* GL_NV_mesh_shader */
         722, /* GL_NV_non_square_matrices */
         724, /* GL_NV_pack_subimage */
         728, /* GL_NV_path_rendering */
         729, /* GL_NV_path_rendering_shared_edge */
         730, /* GL_NV_pixel_buffer_object */
         733, /* GL_NV_polygon_mode */
         736, /* GL_NV_primitive_shading_rate */
         741, /* GL_NV_read_buffer */
         742, /* GL_NV_read_buffer_front */
         743, /* GL_NV_read_depth */
         744, /* GL_NV_read_depth_stencil */
         745, /* GL_NV_read_stencil */
         748, /* GL_NV_representative_fragment_test */
         750, /* GL_NV_sRGB_formats */
         751, /* GL_NV_sample_locations */
         752, /* GL_NV_sample_mask_override_coverage */
         753, /* GL_NV_scissor_exclusive */
         757, /* GL_NV_shader_atomic_fp16_vector */
         762, /* GL_NV_shader_noperspective_interpolation */
         763, /* GL_NV_shader_sm_builtins */
         765, /* GL_NV_shader_subgroup_partitioned */
         766, /* GL_NV_shader_texture_footprint */
         769, /* GL_NV_shading_rate_image */
         770, /* GL_NV_shadow_samplers_array */
         771, /* GL_NV_shadow_samplers_cube */
         772, /* GL_NV_stereo_view_rendering */
         776, /* GL_NV_texture_barrier */
         777, /* GL_NV_texture_border_clamp */
         778, /* GL_NV_texture_compression_s3tc_update */
         783, /* GL_NV_texture_npot_2D_mipmap */
         789, /* GL_NV_timeline_semaphore */
         807, /* GL_NV_viewport_array */
         808, /* GL_NV_viewport_array2 */
         809, /* GL_NV_viewport_swizzle */
         810, /* GL_OES_EGL_image */
         811, /* GL_OES_EGL_image_external */
         812, /* GL_OES_EGL_image_external_essl3 */
         814, /* GL_OES_compressed_ETC1_RGB8_sub_texture */
         815, /* GL_OES_compressed_ETC1_RGB8_texture */
         816, /* GL_OES_compressed_paletted_texture */
         817, /* GL_OES_copy_image */
         818, /* GL_OES_depth24 */
         819, /* GL_OES_depth32 */
         820, /* GL_OES_depth_texture */
         821, /* GL_OES_draw_buffers_indexed */
         822, /* GL_OES_draw_elements_base_vertex */
         823, /* GL_OES_element_index_uint */
         824, /* GL_OES_fbo_render_mipmap */
         826, /* GL_OES_fragment_precision_high */
         827, /* GL_OES_geometry_point_size */
         828, /* GL_OES_geometry_shader */
         829, /* GL_OES_get_program_binary */
         830, /* GL_OES_gpu_shader5 */
         831, /* GL_OES_mapbuffer */
         832, /* GL_OES_packed_depth_stencil */
         833, /* GL_OES_primitive_bounding_box */
         836, /* GL_OES_required_internalformat */
         837, /* GL_OES_rgb8_rgba8 */
         838, /* GL_OES_sample_shading */
         839, /* GL_OES_sample_variables */
         840, /* GL_OES_shader_image_atomic */
         841, /* GL_OES_shader_io_blocks */
         842, /* GL_OES_shader_multisample_interpolation */
         844, /* GL_OES_standard_derivatives */
         845, /* GL_OES_stencil1 */
         846, /* GL_OES_stencil4 */
         847, /* GL_OES_surfaceless_context */
         848, /* GL_OES_tessellation_point_size */
         849, /* GL_OES_tessellation_shader */
         850, /* GL_OES_texture_3D */
         851, /* GL_OES_texture_border_clamp */
         852, /* GL_OES_texture_buffer */
         853, /* GL_OES_texture_compression_astc */
         854, /* GL_OES_texture_cube_map_array */
         855, /* GL_OES_texture_float */
         856, /* GL_OES_texture_float_linear */
         857, /* GL_OES_texture_half_float */
         858, /* GL_OES_texture_half_float_linear */
         859, /* GL_OES_texture_npot */
         860, /* GL_OES_texture_stencil8 */
         861, /* GL_OES_texture_storage_multisample_2d_array */
         862, /* GL_OES_texture_view */
         863, /* GL_OES_vertex_array_object */
         864, /* GL_OES_vertex_half_float */
         865, /* GL_OES_vertex_type_10_10_10_2 */
         866, /* GL_OES_viewport_array */
         870, /* GL_OVR_multiview */
         871, /* GL_OVR_multiview2 */
         872, /* GL_OVR_multiview_multisampled_render_to_texture */
         875, /* GL_QCOM_YUV_texture_gather */
         876, /* GL_QCOM_alpha_test */
         877, /* GL_QCOM_binning_control */
         878, /* GL_QCOM_cooperative_matrix_conversion */
         879, /* GL_QCOM_driver_control */
         880, /* GL_QCOM_extended_get */
         881, /* GL_QCOM_extended_get2 */
         882, /* GL_QCOM_frame_extrapolation */
         883, /* GL_QCOM_framebuffer_foveated */
         884, /* GL_QCOM_image_processing */
         885, /* GL_QCOM_image_processing2 */
         886, /* GL_QCOM_motion_estimation */
         887, /* GL_QCOM_perfmon_global_mode */
         888, /* GL_QCOM_render_sRGB_R8_RG8 */
         889, /* GL_QCOM_render_shared_exponent */
         890, /* GL_QCOM_shader_framebuffer_fetch_noncoherent */
         891, /* GL_QCOM_shader_framebuffer_fetch_rate */
         892, /* GL_QCOM_shading_rate */
         893, /* GL_QCOM_texture_foveated */
         894, /* GL_QCOM_texture_foveated2 */
         895, /* GL_QCOM_texture_foveated_subsampled_layout */
         896, /* GL_QCOM_texture_lod_bias */
         897, /* GL_QCOM_tile_shading */
         898, /* GL_QCOM_tiled_rendering */
         899, /* GL_QCOM_writeonly_rendering */
         900, /* GL_QCOM_ycbcr_degamma */
         966, /* GL_VIV_shader_binary */
    };
    uint64_t *exts = NULL;
    uint32_t num_exts = 0;
    uint32_t i;
    if (!glad_gl_get_extensions(context, &exts, &num_exts)) return 0;

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

    for (i = 0; i < GLAD_ARRAYSIZE(GLAD_gles2_ext_pfn_ranges); ++i) {
        const GladPfnRange_t *range = &GLAD_gles2_ext_pfn_ranges[i];
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
