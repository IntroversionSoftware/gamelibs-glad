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
    /*    1 */ "glActiveTexture",
    /*    2 */ "glActiveTextureARB",
    /*    3 */ "glAlphaFunc",
    /*    4 */ "glAreProgramsResidentNV",
    /*    5 */ "glAreTexturesResident",
    /*    6 */ "glAreTexturesResidentEXT",
    /*    7 */ "glArrayElement",
    /*    8 */ "glArrayElementEXT",
    /*    9 */ "glAttachObjectARB",
    /*   10 */ "glAttachShader",
    /*   11 */ "glBegin",
    /*   12 */ "glBeginQuery",
    /*   13 */ "glBeginQueryARB",
    /*   14 */ "glBindAttribLocation",
    /*   15 */ "glBindAttribLocationARB",
    /*   16 */ "glBindBuffer",
    /*   17 */ "glBindBufferARB",
    /*   18 */ "glBindMultiTextureEXT",
    /*   19 */ "glBindProgramARB",
    /*   20 */ "glBindProgramNV",
    /*   21 */ "glBindTexture",
    /*   22 */ "glBindTextureEXT",
    /*   23 */ "glBitmap",
    /*   24 */ "glBlendColor",
    /*   25 */ "glBlendColorEXT",
    /*   26 */ "glBlendEquation",
    /*   27 */ "glBlendEquationEXT",
    /*   28 */ "glBlendEquationSeparate",
    /*   29 */ "glBlendEquationSeparateEXT",
    /*   30 */ "glBlendFunc",
    /*   31 */ "glBlendFuncSeparate",
    /*   32 */ "glBlendFuncSeparateEXT",
    /*   33 */ "glBlendFuncSeparateINGR",
    /*   34 */ "glBufferData",
    /*   35 */ "glBufferDataARB",
    /*   36 */ "glBufferStorage",
    /*   37 */ "glBufferSubData",
    /*   38 */ "glBufferSubDataARB",
    /*   39 */ "glCallList",
    /*   40 */ "glCallLists",
    /*   41 */ "glCheckNamedFramebufferStatusEXT",
    /*   42 */ "glClear",
    /*   43 */ "glClearAccum",
    /*   44 */ "glClearColor",
    /*   45 */ "glClearDepth",
    /*   46 */ "glClearIndex",
    /*   47 */ "glClearNamedBufferDataEXT",
    /*   48 */ "glClearNamedBufferSubDataEXT",
    /*   49 */ "glClearStencil",
    /*   50 */ "glClientActiveTexture",
    /*   51 */ "glClientActiveTextureARB",
    /*   52 */ "glClientAttribDefaultEXT",
    /*   53 */ "glClipPlane",
    /*   54 */ "glColor3b",
    /*   55 */ "glColor3bv",
    /*   56 */ "glColor3d",
    /*   57 */ "glColor3dv",
    /*   58 */ "glColor3f",
    /*   59 */ "glColor3fv",
    /*   60 */ "glColor3i",
    /*   61 */ "glColor3iv",
    /*   62 */ "glColor3s",
    /*   63 */ "glColor3sv",
    /*   64 */ "glColor3ub",
    /*   65 */ "glColor3ubv",
    /*   66 */ "glColor3ui",
    /*   67 */ "glColor3uiv",
    /*   68 */ "glColor3us",
    /*   69 */ "glColor3usv",
    /*   70 */ "glColor4b",
    /*   71 */ "glColor4bv",
    /*   72 */ "glColor4d",
    /*   73 */ "glColor4dv",
    /*   74 */ "glColor4f",
    /*   75 */ "glColor4fv",
    /*   76 */ "glColor4i",
    /*   77 */ "glColor4iv",
    /*   78 */ "glColor4s",
    /*   79 */ "glColor4sv",
    /*   80 */ "glColor4ub",
    /*   81 */ "glColor4ubv",
    /*   82 */ "glColor4ui",
    /*   83 */ "glColor4uiv",
    /*   84 */ "glColor4us",
    /*   85 */ "glColor4usv",
    /*   86 */ "glColorMask",
    /*   87 */ "glColorMaterial",
    /*   88 */ "glColorPointer",
    /*   89 */ "glColorPointerEXT",
    /*   90 */ "glColorSubTable",
    /*   91 */ "glColorTable",
    /*   92 */ "glColorTableParameterfv",
    /*   93 */ "glColorTableParameteriv",
    /*   94 */ "glCompileShader",
    /*   95 */ "glCompileShaderARB",
    /*   96 */ "glCompressedMultiTexImage1DEXT",
    /*   97 */ "glCompressedMultiTexImage2DEXT",
    /*   98 */ "glCompressedMultiTexImage3DEXT",
    /*   99 */ "glCompressedMultiTexSubImage1DEXT",
    /*  100 */ "glCompressedMultiTexSubImage2DEXT",
    /*  101 */ "glCompressedMultiTexSubImage3DEXT",
    /*  102 */ "glCompressedTexImage1D",
    /*  103 */ "glCompressedTexImage1DARB",
    /*  104 */ "glCompressedTexImage2D",
    /*  105 */ "glCompressedTexImage2DARB",
    /*  106 */ "glCompressedTexImage3D",
    /*  107 */ "glCompressedTexImage3DARB",
    /*  108 */ "glCompressedTexSubImage1D",
    /*  109 */ "glCompressedTexSubImage1DARB",
    /*  110 */ "glCompressedTexSubImage2D",
    /*  111 */ "glCompressedTexSubImage2DARB",
    /*  112 */ "glCompressedTexSubImage3D",
    /*  113 */ "glCompressedTexSubImage3DARB",
    /*  114 */ "glCompressedTextureImage1DEXT",
    /*  115 */ "glCompressedTextureImage2DEXT",
    /*  116 */ "glCompressedTextureImage3DEXT",
    /*  117 */ "glCompressedTextureSubImage1DEXT",
    /*  118 */ "glCompressedTextureSubImage2DEXT",
    /*  119 */ "glCompressedTextureSubImage3DEXT",
    /*  120 */ "glConvolutionFilter1D",
    /*  121 */ "glConvolutionFilter2D",
    /*  122 */ "glConvolutionParameterf",
    /*  123 */ "glConvolutionParameterfv",
    /*  124 */ "glConvolutionParameteri",
    /*  125 */ "glConvolutionParameteriv",
    /*  126 */ "glCopyColorSubTable",
    /*  127 */ "glCopyColorTable",
    /*  128 */ "glCopyConvolutionFilter1D",
    /*  129 */ "glCopyConvolutionFilter2D",
    /*  130 */ "glCopyMultiTexImage1DEXT",
    /*  131 */ "glCopyMultiTexImage2DEXT",
    /*  132 */ "glCopyMultiTexSubImage1DEXT",
    /*  133 */ "glCopyMultiTexSubImage2DEXT",
    /*  134 */ "glCopyMultiTexSubImage3DEXT",
    /*  135 */ "glCopyPixels",
    /*  136 */ "glCopyTexImage1D",
    /*  137 */ "glCopyTexImage1DEXT",
    /*  138 */ "glCopyTexImage2D",
    /*  139 */ "glCopyTexImage2DEXT",
    /*  140 */ "glCopyTexSubImage1D",
    /*  141 */ "glCopyTexSubImage1DEXT",
    /*  142 */ "glCopyTexSubImage2D",
    /*  143 */ "glCopyTexSubImage2DEXT",
    /*  144 */ "glCopyTexSubImage3D",
    /*  145 */ "glCopyTexSubImage3DEXT",
    /*  146 */ "glCopyTextureImage1DEXT",
    /*  147 */ "glCopyTextureImage2DEXT",
    /*  148 */ "glCopyTextureSubImage1DEXT",
    /*  149 */ "glCopyTextureSubImage2DEXT",
    /*  150 */ "glCopyTextureSubImage3DEXT",
    /*  151 */ "glCreateProgram",
    /*  152 */ "glCreateProgramObjectARB",
    /*  153 */ "glCreateShader",
    /*  154 */ "glCreateShaderObjectARB",
    /*  155 */ "glCullFace",
    /*  156 */ "glDebugMessageCallback",
    /*  157 */ "glDebugMessageCallbackARB",
    /*  158 */ "glDebugMessageControl",
    /*  159 */ "glDebugMessageControlARB",
    /*  160 */ "glDebugMessageInsert",
    /*  161 */ "glDebugMessageInsertARB",
    /*  162 */ "glDeleteBuffers",
    /*  163 */ "glDeleteBuffersARB",
    /*  164 */ "glDeleteLists",
    /*  165 */ "glDeleteObjectARB",
    /*  166 */ "glDeleteProgram",
    /*  167 */ "glDeleteProgramsARB",
    /*  168 */ "glDeleteProgramsNV",
    /*  169 */ "glDeleteQueries",
    /*  170 */ "glDeleteQueriesARB",
    /*  171 */ "glDeleteShader",
    /*  172 */ "glDeleteTextures",
    /*  173 */ "glDeleteTexturesEXT",
    /*  174 */ "glDepthFunc",
    /*  175 */ "glDepthMask",
    /*  176 */ "glDepthRange",
    /*  177 */ "glDetachObjectARB",
    /*  178 */ "glDetachShader",
    /*  179 */ "glDisable",
    /*  180 */ "glDisableClientState",
    /*  181 */ "glDisableClientStateIndexedEXT",
    /*  182 */ "glDisableClientStateiEXT",
    /*  183 */ "glDisableIndexedEXT",
    /*  184 */ "glDisableVertexArrayAttribEXT",
    /*  185 */ "glDisableVertexArrayEXT",
    /*  186 */ "glDisableVertexAttribArray",
    /*  187 */ "glDisableVertexAttribArrayARB",
    /*  188 */ "glDrawArrays",
    /*  189 */ "glDrawArraysEXT",
    /*  190 */ "glDrawBuffer",
    /*  191 */ "glDrawBuffers",
    /*  192 */ "glDrawBuffersARB",
    /*  193 */ "glDrawBuffersATI",
    /*  194 */ "glDrawElements",
    /*  195 */ "glDrawPixels",
    /*  196 */ "glDrawRangeElements",
    /*  197 */ "glDrawRangeElementsEXT",
    /*  198 */ "glEdgeFlag",
    /*  199 */ "glEdgeFlagPointer",
    /*  200 */ "glEdgeFlagPointerEXT",
    /*  201 */ "glEdgeFlagv",
    /*  202 */ "glEnable",
    /*  203 */ "glEnableClientState",
    /*  204 */ "glEnableClientStateIndexedEXT",
    /*  205 */ "glEnableClientStateiEXT",
    /*  206 */ "glEnableIndexedEXT",
    /*  207 */ "glEnableVertexArrayAttribEXT",
    /*  208 */ "glEnableVertexArrayEXT",
    /*  209 */ "glEnableVertexAttribArray",
    /*  210 */ "glEnableVertexAttribArrayARB",
    /*  211 */ "glEnd",
    /*  212 */ "glEndList",
    /*  213 */ "glEndQuery",
    /*  214 */ "glEndQueryARB",
    /*  215 */ "glEvalCoord1d",
    /*  216 */ "glEvalCoord1dv",
    /*  217 */ "glEvalCoord1f",
    /*  218 */ "glEvalCoord1fv",
    /*  219 */ "glEvalCoord2d",
    /*  220 */ "glEvalCoord2dv",
    /*  221 */ "glEvalCoord2f",
    /*  222 */ "glEvalCoord2fv",
    /*  223 */ "glEvalMesh1",
    /*  224 */ "glEvalMesh2",
    /*  225 */ "glEvalPoint1",
    /*  226 */ "glEvalPoint2",
    /*  227 */ "glExecuteProgramNV",
    /*  228 */ "glFeedbackBuffer",
    /*  229 */ "glFinish",
    /*  230 */ "glFlush",
    /*  231 */ "glFlushMappedNamedBufferRangeEXT",
    /*  232 */ "glFogCoordPointer",
    /*  233 */ "glFogCoordPointerEXT",
    /*  234 */ "glFogCoordd",
    /*  235 */ "glFogCoorddEXT",
    /*  236 */ "glFogCoorddv",
    /*  237 */ "glFogCoorddvEXT",
    /*  238 */ "glFogCoordf",
    /*  239 */ "glFogCoordfEXT",
    /*  240 */ "glFogCoordfv",
    /*  241 */ "glFogCoordfvEXT",
    /*  242 */ "glFogf",
    /*  243 */ "glFogfv",
    /*  244 */ "glFogi",
    /*  245 */ "glFogiv",
    /*  246 */ "glFramebufferDrawBufferEXT",
    /*  247 */ "glFramebufferDrawBuffersEXT",
    /*  248 */ "glFramebufferReadBufferEXT",
    /*  249 */ "glFrontFace",
    /*  250 */ "glFrustum",
    /*  251 */ "glGenBuffers",
    /*  252 */ "glGenBuffersARB",
    /*  253 */ "glGenLists",
    /*  254 */ "glGenProgramsARB",
    /*  255 */ "glGenProgramsNV",
    /*  256 */ "glGenQueries",
    /*  257 */ "glGenQueriesARB",
    /*  258 */ "glGenTextures",
    /*  259 */ "glGenTexturesEXT",
    /*  260 */ "glGenerateMultiTexMipmapEXT",
    /*  261 */ "glGenerateTextureMipmapEXT",
    /*  262 */ "glGetActiveAttrib",
    /*  263 */ "glGetActiveAttribARB",
    /*  264 */ "glGetActiveUniform",
    /*  265 */ "glGetActiveUniformARB",
    /*  266 */ "glGetAttachedObjectsARB",
    /*  267 */ "glGetAttachedShaders",
    /*  268 */ "glGetAttribLocation",
    /*  269 */ "glGetAttribLocationARB",
    /*  270 */ "glGetBooleanIndexedvEXT",
    /*  271 */ "glGetBooleanv",
    /*  272 */ "glGetBufferParameteriv",
    /*  273 */ "glGetBufferParameterivARB",
    /*  274 */ "glGetBufferPointerv",
    /*  275 */ "glGetBufferPointervARB",
    /*  276 */ "glGetBufferSubData",
    /*  277 */ "glGetBufferSubDataARB",
    /*  278 */ "glGetClipPlane",
    /*  279 */ "glGetColorTable",
    /*  280 */ "glGetColorTableParameterfv",
    /*  281 */ "glGetColorTableParameteriv",
    /*  282 */ "glGetCompressedMultiTexImageEXT",
    /*  283 */ "glGetCompressedTexImage",
    /*  284 */ "glGetCompressedTexImageARB",
    /*  285 */ "glGetCompressedTextureImageEXT",
    /*  286 */ "glGetConvolutionFilter",
    /*  287 */ "glGetConvolutionParameterfv",
    /*  288 */ "glGetConvolutionParameteriv",
    /*  289 */ "glGetDebugMessageLog",
    /*  290 */ "glGetDebugMessageLogARB",
    /*  291 */ "glGetDoubleIndexedvEXT",
    /*  292 */ "glGetDoublei_vEXT",
    /*  293 */ "glGetDoublev",
    /*  294 */ "glGetError",
    /*  295 */ "glGetFloatIndexedvEXT",
    /*  296 */ "glGetFloati_vEXT",
    /*  297 */ "glGetFloatv",
    /*  298 */ "glGetFramebufferParameterivEXT",
    /*  299 */ "glGetHandleARB",
    /*  300 */ "glGetHistogram",
    /*  301 */ "glGetHistogramParameterfv",
    /*  302 */ "glGetHistogramParameteriv",
    /*  303 */ "glGetInfoLogARB",
    /*  304 */ "glGetIntegerIndexedvEXT",
    /*  305 */ "glGetIntegerv",
    /*  306 */ "glGetLightfv",
    /*  307 */ "glGetLightiv",
    /*  308 */ "glGetMapdv",
    /*  309 */ "glGetMapfv",
    /*  310 */ "glGetMapiv",
    /*  311 */ "glGetMaterialfv",
    /*  312 */ "glGetMaterialiv",
    /*  313 */ "glGetMinmax",
    /*  314 */ "glGetMinmaxParameterfv",
    /*  315 */ "glGetMinmaxParameteriv",
    /*  316 */ "glGetMultiTexEnvfvEXT",
    /*  317 */ "glGetMultiTexEnvivEXT",
    /*  318 */ "glGetMultiTexGendvEXT",
    /*  319 */ "glGetMultiTexGenfvEXT",
    /*  320 */ "glGetMultiTexGenivEXT",
    /*  321 */ "glGetMultiTexImageEXT",
    /*  322 */ "glGetMultiTexLevelParameterfvEXT",
    /*  323 */ "glGetMultiTexLevelParameterivEXT",
    /*  324 */ "glGetMultiTexParameterIivEXT",
    /*  325 */ "glGetMultiTexParameterIuivEXT",
    /*  326 */ "glGetMultiTexParameterfvEXT",
    /*  327 */ "glGetMultiTexParameterivEXT",
    /*  328 */ "glGetNamedBufferParameterivEXT",
    /*  329 */ "glGetNamedBufferPointervEXT",
    /*  330 */ "glGetNamedBufferSubDataEXT",
    /*  331 */ "glGetNamedFramebufferAttachmentParameterivEXT",
    /*  332 */ "glGetNamedFramebufferParameterivEXT",
    /*  333 */ "glGetNamedProgramLocalParameterIivEXT",
    /*  334 */ "glGetNamedProgramLocalParameterIuivEXT",
    /*  335 */ "glGetNamedProgramLocalParameterdvEXT",
    /*  336 */ "glGetNamedProgramLocalParameterfvEXT",
    /*  337 */ "glGetNamedProgramStringEXT",
    /*  338 */ "glGetNamedProgramivEXT",
    /*  339 */ "glGetNamedRenderbufferParameterivEXT",
    /*  340 */ "glGetObjectLabel",
    /*  341 */ "glGetObjectParameterfvARB",
    /*  342 */ "glGetObjectParameterivARB",
    /*  343 */ "glGetObjectPtrLabel",
    /*  344 */ "glGetPixelMapfv",
    /*  345 */ "glGetPixelMapuiv",
    /*  346 */ "glGetPixelMapusv",
    /*  347 */ "glGetPointerIndexedvEXT",
    /*  348 */ "glGetPointeri_vEXT",
    /*  349 */ "glGetPointerv",
    /*  350 */ "glGetPointervEXT",
    /*  351 */ "glGetPolygonStipple",
    /*  352 */ "glGetProgramEnvParameterdvARB",
    /*  353 */ "glGetProgramEnvParameterfvARB",
    /*  354 */ "glGetProgramInfoLog",
    /*  355 */ "glGetProgramLocalParameterdvARB",
    /*  356 */ "glGetProgramLocalParameterfvARB",
    /*  357 */ "glGetProgramParameterdvNV",
    /*  358 */ "glGetProgramParameterfvNV",
    /*  359 */ "glGetProgramStringARB",
    /*  360 */ "glGetProgramStringNV",
    /*  361 */ "glGetProgramiv",
    /*  362 */ "glGetProgramivARB",
    /*  363 */ "glGetProgramivNV",
    /*  364 */ "glGetQueryObjectiv",
    /*  365 */ "glGetQueryObjectivARB",
    /*  366 */ "glGetQueryObjectuiv",
    /*  367 */ "glGetQueryObjectuivARB",
    /*  368 */ "glGetQueryiv",
    /*  369 */ "glGetQueryivARB",
    /*  370 */ "glGetSeparableFilter",
    /*  371 */ "glGetShaderInfoLog",
    /*  372 */ "glGetShaderSource",
    /*  373 */ "glGetShaderSourceARB",
    /*  374 */ "glGetShaderiv",
    /*  375 */ "glGetString",
    /*  376 */ "glGetTexEnvfv",
    /*  377 */ "glGetTexEnviv",
    /*  378 */ "glGetTexGendv",
    /*  379 */ "glGetTexGenfv",
    /*  380 */ "glGetTexGeniv",
    /*  381 */ "glGetTexImage",
    /*  382 */ "glGetTexLevelParameterfv",
    /*  383 */ "glGetTexLevelParameteriv",
    /*  384 */ "glGetTexParameterfv",
    /*  385 */ "glGetTexParameteriv",
    /*  386 */ "glGetTextureImageEXT",
    /*  387 */ "glGetTextureLevelParameterfvEXT",
    /*  388 */ "glGetTextureLevelParameterivEXT",
    /*  389 */ "glGetTextureParameterIivEXT",
    /*  390 */ "glGetTextureParameterIuivEXT",
    /*  391 */ "glGetTextureParameterfvEXT",
    /*  392 */ "glGetTextureParameterivEXT",
    /*  393 */ "glGetTrackMatrixivNV",
    /*  394 */ "glGetUniformLocation",
    /*  395 */ "glGetUniformLocationARB",
    /*  396 */ "glGetUniformfv",
    /*  397 */ "glGetUniformfvARB",
    /*  398 */ "glGetUniformiv",
    /*  399 */ "glGetUniformivARB",
    /*  400 */ "glGetVertexArrayIntegeri_vEXT",
    /*  401 */ "glGetVertexArrayIntegervEXT",
    /*  402 */ "glGetVertexArrayPointeri_vEXT",
    /*  403 */ "glGetVertexArrayPointervEXT",
    /*  404 */ "glGetVertexAttribPointerv",
    /*  405 */ "glGetVertexAttribPointervARB",
    /*  406 */ "glGetVertexAttribPointervNV",
    /*  407 */ "glGetVertexAttribdv",
    /*  408 */ "glGetVertexAttribdvARB",
    /*  409 */ "glGetVertexAttribdvNV",
    /*  410 */ "glGetVertexAttribfv",
    /*  411 */ "glGetVertexAttribfvARB",
    /*  412 */ "glGetVertexAttribfvNV",
    /*  413 */ "glGetVertexAttribiv",
    /*  414 */ "glGetVertexAttribivARB",
    /*  415 */ "glGetVertexAttribivNV",
    /*  416 */ "glHint",
    /*  417 */ "glHistogram",
    /*  418 */ "glIndexMask",
    /*  419 */ "glIndexPointer",
    /*  420 */ "glIndexPointerEXT",
    /*  421 */ "glIndexd",
    /*  422 */ "glIndexdv",
    /*  423 */ "glIndexf",
    /*  424 */ "glIndexfv",
    /*  425 */ "glIndexi",
    /*  426 */ "glIndexiv",
    /*  427 */ "glIndexs",
    /*  428 */ "glIndexsv",
    /*  429 */ "glIndexub",
    /*  430 */ "glIndexubv",
    /*  431 */ "glInitNames",
    /*  432 */ "glInterleavedArrays",
    /*  433 */ "glIsBuffer",
    /*  434 */ "glIsBufferARB",
    /*  435 */ "glIsEnabled",
    /*  436 */ "glIsEnabledIndexedEXT",
    /*  437 */ "glIsList",
    /*  438 */ "glIsProgram",
    /*  439 */ "glIsProgramARB",
    /*  440 */ "glIsProgramNV",
    /*  441 */ "glIsQuery",
    /*  442 */ "glIsQueryARB",
    /*  443 */ "glIsShader",
    /*  444 */ "glIsTexture",
    /*  445 */ "glIsTextureEXT",
    /*  446 */ "glLightModelf",
    /*  447 */ "glLightModelfv",
    /*  448 */ "glLightModeli",
    /*  449 */ "glLightModeliv",
    /*  450 */ "glLightf",
    /*  451 */ "glLightfv",
    /*  452 */ "glLighti",
    /*  453 */ "glLightiv",
    /*  454 */ "glLineStipple",
    /*  455 */ "glLineWidth",
    /*  456 */ "glLinkProgram",
    /*  457 */ "glLinkProgramARB",
    /*  458 */ "glListBase",
    /*  459 */ "glLoadIdentity",
    /*  460 */ "glLoadMatrixd",
    /*  461 */ "glLoadMatrixf",
    /*  462 */ "glLoadName",
    /*  463 */ "glLoadProgramNV",
    /*  464 */ "glLoadTransposeMatrixd",
    /*  465 */ "glLoadTransposeMatrixdARB",
    /*  466 */ "glLoadTransposeMatrixf",
    /*  467 */ "glLoadTransposeMatrixfARB",
    /*  468 */ "glLogicOp",
    /*  469 */ "glMap1d",
    /*  470 */ "glMap1f",
    /*  471 */ "glMap2d",
    /*  472 */ "glMap2f",
    /*  473 */ "glMapBuffer",
    /*  474 */ "glMapBufferARB",
    /*  475 */ "glMapGrid1d",
    /*  476 */ "glMapGrid1f",
    /*  477 */ "glMapGrid2d",
    /*  478 */ "glMapGrid2f",
    /*  479 */ "glMapNamedBufferEXT",
    /*  480 */ "glMapNamedBufferRangeEXT",
    /*  481 */ "glMaterialf",
    /*  482 */ "glMaterialfv",
    /*  483 */ "glMateriali",
    /*  484 */ "glMaterialiv",
    /*  485 */ "glMatrixFrustumEXT",
    /*  486 */ "glMatrixLoadIdentityEXT",
    /*  487 */ "glMatrixLoadTransposedEXT",
    /*  488 */ "glMatrixLoadTransposefEXT",
    /*  489 */ "glMatrixLoaddEXT",
    /*  490 */ "glMatrixLoadfEXT",
    /*  491 */ "glMatrixMode",
    /*  492 */ "glMatrixMultTransposedEXT",
    /*  493 */ "glMatrixMultTransposefEXT",
    /*  494 */ "glMatrixMultdEXT",
    /*  495 */ "glMatrixMultfEXT",
    /*  496 */ "glMatrixOrthoEXT",
    /*  497 */ "glMatrixPopEXT",
    /*  498 */ "glMatrixPushEXT",
    /*  499 */ "glMatrixRotatedEXT",
    /*  500 */ "glMatrixRotatefEXT",
    /*  501 */ "glMatrixScaledEXT",
    /*  502 */ "glMatrixScalefEXT",
    /*  503 */ "glMatrixTranslatedEXT",
    /*  504 */ "glMatrixTranslatefEXT",
    /*  505 */ "glMinmax",
    /*  506 */ "glMultMatrixd",
    /*  507 */ "glMultMatrixf",
    /*  508 */ "glMultTransposeMatrixd",
    /*  509 */ "glMultTransposeMatrixdARB",
    /*  510 */ "glMultTransposeMatrixf",
    /*  511 */ "glMultTransposeMatrixfARB",
    /*  512 */ "glMultiDrawArrays",
    /*  513 */ "glMultiDrawArraysEXT",
    /*  514 */ "glMultiDrawElements",
    /*  515 */ "glMultiDrawElementsEXT",
    /*  516 */ "glMultiTexBufferEXT",
    /*  517 */ "glMultiTexCoord1d",
    /*  518 */ "glMultiTexCoord1dARB",
    /*  519 */ "glMultiTexCoord1dv",
    /*  520 */ "glMultiTexCoord1dvARB",
    /*  521 */ "glMultiTexCoord1f",
    /*  522 */ "glMultiTexCoord1fARB",
    /*  523 */ "glMultiTexCoord1fv",
    /*  524 */ "glMultiTexCoord1fvARB",
    /*  525 */ "glMultiTexCoord1i",
    /*  526 */ "glMultiTexCoord1iARB",
    /*  527 */ "glMultiTexCoord1iv",
    /*  528 */ "glMultiTexCoord1ivARB",
    /*  529 */ "glMultiTexCoord1s",
    /*  530 */ "glMultiTexCoord1sARB",
    /*  531 */ "glMultiTexCoord1sv",
    /*  532 */ "glMultiTexCoord1svARB",
    /*  533 */ "glMultiTexCoord2d",
    /*  534 */ "glMultiTexCoord2dARB",
    /*  535 */ "glMultiTexCoord2dv",
    /*  536 */ "glMultiTexCoord2dvARB",
    /*  537 */ "glMultiTexCoord2f",
    /*  538 */ "glMultiTexCoord2fARB",
    /*  539 */ "glMultiTexCoord2fv",
    /*  540 */ "glMultiTexCoord2fvARB",
    /*  541 */ "glMultiTexCoord2i",
    /*  542 */ "glMultiTexCoord2iARB",
    /*  543 */ "glMultiTexCoord2iv",
    /*  544 */ "glMultiTexCoord2ivARB",
    /*  545 */ "glMultiTexCoord2s",
    /*  546 */ "glMultiTexCoord2sARB",
    /*  547 */ "glMultiTexCoord2sv",
    /*  548 */ "glMultiTexCoord2svARB",
    /*  549 */ "glMultiTexCoord3d",
    /*  550 */ "glMultiTexCoord3dARB",
    /*  551 */ "glMultiTexCoord3dv",
    /*  552 */ "glMultiTexCoord3dvARB",
    /*  553 */ "glMultiTexCoord3f",
    /*  554 */ "glMultiTexCoord3fARB",
    /*  555 */ "glMultiTexCoord3fv",
    /*  556 */ "glMultiTexCoord3fvARB",
    /*  557 */ "glMultiTexCoord3i",
    /*  558 */ "glMultiTexCoord3iARB",
    /*  559 */ "glMultiTexCoord3iv",
    /*  560 */ "glMultiTexCoord3ivARB",
    /*  561 */ "glMultiTexCoord3s",
    /*  562 */ "glMultiTexCoord3sARB",
    /*  563 */ "glMultiTexCoord3sv",
    /*  564 */ "glMultiTexCoord3svARB",
    /*  565 */ "glMultiTexCoord4d",
    /*  566 */ "glMultiTexCoord4dARB",
    /*  567 */ "glMultiTexCoord4dv",
    /*  568 */ "glMultiTexCoord4dvARB",
    /*  569 */ "glMultiTexCoord4f",
    /*  570 */ "glMultiTexCoord4fARB",
    /*  571 */ "glMultiTexCoord4fv",
    /*  572 */ "glMultiTexCoord4fvARB",
    /*  573 */ "glMultiTexCoord4i",
    /*  574 */ "glMultiTexCoord4iARB",
    /*  575 */ "glMultiTexCoord4iv",
    /*  576 */ "glMultiTexCoord4ivARB",
    /*  577 */ "glMultiTexCoord4s",
    /*  578 */ "glMultiTexCoord4sARB",
    /*  579 */ "glMultiTexCoord4sv",
    /*  580 */ "glMultiTexCoord4svARB",
    /*  581 */ "glMultiTexCoordPointerEXT",
    /*  582 */ "glMultiTexEnvfEXT",
    /*  583 */ "glMultiTexEnvfvEXT",
    /*  584 */ "glMultiTexEnviEXT",
    /*  585 */ "glMultiTexEnvivEXT",
    /*  586 */ "glMultiTexGendEXT",
    /*  587 */ "glMultiTexGendvEXT",
    /*  588 */ "glMultiTexGenfEXT",
    /*  589 */ "glMultiTexGenfvEXT",
    /*  590 */ "glMultiTexGeniEXT",
    /*  591 */ "glMultiTexGenivEXT",
    /*  592 */ "glMultiTexImage1DEXT",
    /*  593 */ "glMultiTexImage2DEXT",
    /*  594 */ "glMultiTexImage3DEXT",
    /*  595 */ "glMultiTexParameterIivEXT",
    /*  596 */ "glMultiTexParameterIuivEXT",
    /*  597 */ "glMultiTexParameterfEXT",
    /*  598 */ "glMultiTexParameterfvEXT",
    /*  599 */ "glMultiTexParameteriEXT",
    /*  600 */ "glMultiTexParameterivEXT",
    /*  601 */ "glMultiTexRenderbufferEXT",
    /*  602 */ "glMultiTexSubImage1DEXT",
    /*  603 */ "glMultiTexSubImage2DEXT",
    /*  604 */ "glMultiTexSubImage3DEXT",
    /*  605 */ "glNamedBufferDataEXT",
    /*  606 */ "glNamedBufferStorageEXT",
    /*  607 */ "glNamedBufferSubDataEXT",
    /*  608 */ "glNamedCopyBufferSubDataEXT",
    /*  609 */ "glNamedFramebufferParameteriEXT",
    /*  610 */ "glNamedFramebufferRenderbufferEXT",
    /*  611 */ "glNamedFramebufferTexture1DEXT",
    /*  612 */ "glNamedFramebufferTexture2DEXT",
    /*  613 */ "glNamedFramebufferTexture3DEXT",
    /*  614 */ "glNamedFramebufferTextureEXT",
    /*  615 */ "glNamedFramebufferTextureFaceEXT",
    /*  616 */ "glNamedFramebufferTextureLayerEXT",
    /*  617 */ "glNamedProgramLocalParameter4dEXT",
    /*  618 */ "glNamedProgramLocalParameter4dvEXT",
    /*  619 */ "glNamedProgramLocalParameter4fEXT",
    /*  620 */ "glNamedProgramLocalParameter4fvEXT",
    /*  621 */ "glNamedProgramLocalParameterI4iEXT",
    /*  622 */ "glNamedProgramLocalParameterI4ivEXT",
    /*  623 */ "glNamedProgramLocalParameterI4uiEXT",
    /*  624 */ "glNamedProgramLocalParameterI4uivEXT",
    /*  625 */ "glNamedProgramLocalParameters4fvEXT",
    /*  626 */ "glNamedProgramLocalParametersI4ivEXT",
    /*  627 */ "glNamedProgramLocalParametersI4uivEXT",
    /*  628 */ "glNamedProgramStringEXT",
    /*  629 */ "glNamedRenderbufferStorageEXT",
    /*  630 */ "glNamedRenderbufferStorageMultisampleCoverageEXT",
    /*  631 */ "glNamedRenderbufferStorageMultisampleEXT",
    /*  632 */ "glNewList",
    /*  633 */ "glNormal3b",
    /*  634 */ "glNormal3bv",
    /*  635 */ "glNormal3d",
    /*  636 */ "glNormal3dv",
    /*  637 */ "glNormal3f",
    /*  638 */ "glNormal3fv",
    /*  639 */ "glNormal3i",
    /*  640 */ "glNormal3iv",
    /*  641 */ "glNormal3s",
    /*  642 */ "glNormal3sv",
    /*  643 */ "glNormalPointer",
    /*  644 */ "glNormalPointerEXT",
    /*  645 */ "glObjectLabel",
    /*  646 */ "glObjectPtrLabel",
    /*  647 */ "glOrtho",
    /*  648 */ "glPassThrough",
    /*  649 */ "glPixelMapfv",
    /*  650 */ "glPixelMapuiv",
    /*  651 */ "glPixelMapusv",
    /*  652 */ "glPixelStoref",
    /*  653 */ "glPixelStorei",
    /*  654 */ "glPixelTransferf",
    /*  655 */ "glPixelTransferi",
    /*  656 */ "glPixelZoom",
    /*  657 */ "glPointParameterf",
    /*  658 */ "glPointParameterfARB",
    /*  659 */ "glPointParameterfEXT",
    /*  660 */ "glPointParameterfSGIS",
    /*  661 */ "glPointParameterfv",
    /*  662 */ "glPointParameterfvARB",
    /*  663 */ "glPointParameterfvEXT",
    /*  664 */ "glPointParameterfvSGIS",
    /*  665 */ "glPointParameteri",
    /*  666 */ "glPointParameteriNV",
    /*  667 */ "glPointParameteriv",
    /*  668 */ "glPointParameterivNV",
    /*  669 */ "glPointSize",
    /*  670 */ "glPolygonMode",
    /*  671 */ "glPolygonOffset",
    /*  672 */ "glPolygonStipple",
    /*  673 */ "glPopAttrib",
    /*  674 */ "glPopClientAttrib",
    /*  675 */ "glPopDebugGroup",
    /*  676 */ "glPopMatrix",
    /*  677 */ "glPopName",
    /*  678 */ "glPrioritizeTextures",
    /*  679 */ "glPrioritizeTexturesEXT",
    /*  680 */ "glProgramEnvParameter4dARB",
    /*  681 */ "glProgramEnvParameter4dvARB",
    /*  682 */ "glProgramEnvParameter4fARB",
    /*  683 */ "glProgramEnvParameter4fvARB",
    /*  684 */ "glProgramLocalParameter4dARB",
    /*  685 */ "glProgramLocalParameter4dvARB",
    /*  686 */ "glProgramLocalParameter4fARB",
    /*  687 */ "glProgramLocalParameter4fvARB",
    /*  688 */ "glProgramParameter4dNV",
    /*  689 */ "glProgramParameter4dvNV",
    /*  690 */ "glProgramParameter4fNV",
    /*  691 */ "glProgramParameter4fvNV",
    /*  692 */ "glProgramParameters4dvNV",
    /*  693 */ "glProgramParameters4fvNV",
    /*  694 */ "glProgramStringARB",
    /*  695 */ "glProgramUniform1dEXT",
    /*  696 */ "glProgramUniform1dvEXT",
    /*  697 */ "glProgramUniform1fEXT",
    /*  698 */ "glProgramUniform1fvEXT",
    /*  699 */ "glProgramUniform1iEXT",
    /*  700 */ "glProgramUniform1ivEXT",
    /*  701 */ "glProgramUniform1uiEXT",
    /*  702 */ "glProgramUniform1uivEXT",
    /*  703 */ "glProgramUniform2dEXT",
    /*  704 */ "glProgramUniform2dvEXT",
    /*  705 */ "glProgramUniform2fEXT",
    /*  706 */ "glProgramUniform2fvEXT",
    /*  707 */ "glProgramUniform2iEXT",
    /*  708 */ "glProgramUniform2ivEXT",
    /*  709 */ "glProgramUniform2uiEXT",
    /*  710 */ "glProgramUniform2uivEXT",
    /*  711 */ "glProgramUniform3dEXT",
    /*  712 */ "glProgramUniform3dvEXT",
    /*  713 */ "glProgramUniform3fEXT",
    /*  714 */ "glProgramUniform3fvEXT",
    /*  715 */ "glProgramUniform3iEXT",
    /*  716 */ "glProgramUniform3ivEXT",
    /*  717 */ "glProgramUniform3uiEXT",
    /*  718 */ "glProgramUniform3uivEXT",
    /*  719 */ "glProgramUniform4dEXT",
    /*  720 */ "glProgramUniform4dvEXT",
    /*  721 */ "glProgramUniform4fEXT",
    /*  722 */ "glProgramUniform4fvEXT",
    /*  723 */ "glProgramUniform4iEXT",
    /*  724 */ "glProgramUniform4ivEXT",
    /*  725 */ "glProgramUniform4uiEXT",
    /*  726 */ "glProgramUniform4uivEXT",
    /*  727 */ "glProgramUniformMatrix2dvEXT",
    /*  728 */ "glProgramUniformMatrix2fvEXT",
    /*  729 */ "glProgramUniformMatrix2x3dvEXT",
    /*  730 */ "glProgramUniformMatrix2x3fvEXT",
    /*  731 */ "glProgramUniformMatrix2x4dvEXT",
    /*  732 */ "glProgramUniformMatrix2x4fvEXT",
    /*  733 */ "glProgramUniformMatrix3dvEXT",
    /*  734 */ "glProgramUniformMatrix3fvEXT",
    /*  735 */ "glProgramUniformMatrix3x2dvEXT",
    /*  736 */ "glProgramUniformMatrix3x2fvEXT",
    /*  737 */ "glProgramUniformMatrix3x4dvEXT",
    /*  738 */ "glProgramUniformMatrix3x4fvEXT",
    /*  739 */ "glProgramUniformMatrix4dvEXT",
    /*  740 */ "glProgramUniformMatrix4fvEXT",
    /*  741 */ "glProgramUniformMatrix4x2dvEXT",
    /*  742 */ "glProgramUniformMatrix4x2fvEXT",
    /*  743 */ "glProgramUniformMatrix4x3dvEXT",
    /*  744 */ "glProgramUniformMatrix4x3fvEXT",
    /*  745 */ "glPushAttrib",
    /*  746 */ "glPushClientAttrib",
    /*  747 */ "glPushClientAttribDefaultEXT",
    /*  748 */ "glPushDebugGroup",
    /*  749 */ "glPushMatrix",
    /*  750 */ "glPushName",
    /*  751 */ "glRasterPos2d",
    /*  752 */ "glRasterPos2dv",
    /*  753 */ "glRasterPos2f",
    /*  754 */ "glRasterPos2fv",
    /*  755 */ "glRasterPos2i",
    /*  756 */ "glRasterPos2iv",
    /*  757 */ "glRasterPos2s",
    /*  758 */ "glRasterPos2sv",
    /*  759 */ "glRasterPos3d",
    /*  760 */ "glRasterPos3dv",
    /*  761 */ "glRasterPos3f",
    /*  762 */ "glRasterPos3fv",
    /*  763 */ "glRasterPos3i",
    /*  764 */ "glRasterPos3iv",
    /*  765 */ "glRasterPos3s",
    /*  766 */ "glRasterPos3sv",
    /*  767 */ "glRasterPos4d",
    /*  768 */ "glRasterPos4dv",
    /*  769 */ "glRasterPos4f",
    /*  770 */ "glRasterPos4fv",
    /*  771 */ "glRasterPos4i",
    /*  772 */ "glRasterPos4iv",
    /*  773 */ "glRasterPos4s",
    /*  774 */ "glRasterPos4sv",
    /*  775 */ "glReadBuffer",
    /*  776 */ "glReadPixels",
    /*  777 */ "glRectd",
    /*  778 */ "glRectdv",
    /*  779 */ "glRectf",
    /*  780 */ "glRectfv",
    /*  781 */ "glRecti",
    /*  782 */ "glRectiv",
    /*  783 */ "glRects",
    /*  784 */ "glRectsv",
    /*  785 */ "glRenderMode",
    /*  786 */ "glRequestResidentProgramsNV",
    /*  787 */ "glResetHistogram",
    /*  788 */ "glResetMinmax",
    /*  789 */ "glRotated",
    /*  790 */ "glRotatef",
    /*  791 */ "glSampleCoverage",
    /*  792 */ "glSampleCoverageARB",
    /*  793 */ "glScaled",
    /*  794 */ "glScalef",
    /*  795 */ "glScissor",
    /*  796 */ "glSecondaryColor3b",
    /*  797 */ "glSecondaryColor3bEXT",
    /*  798 */ "glSecondaryColor3bv",
    /*  799 */ "glSecondaryColor3bvEXT",
    /*  800 */ "glSecondaryColor3d",
    /*  801 */ "glSecondaryColor3dEXT",
    /*  802 */ "glSecondaryColor3dv",
    /*  803 */ "glSecondaryColor3dvEXT",
    /*  804 */ "glSecondaryColor3f",
    /*  805 */ "glSecondaryColor3fEXT",
    /*  806 */ "glSecondaryColor3fv",
    /*  807 */ "glSecondaryColor3fvEXT",
    /*  808 */ "glSecondaryColor3i",
    /*  809 */ "glSecondaryColor3iEXT",
    /*  810 */ "glSecondaryColor3iv",
    /*  811 */ "glSecondaryColor3ivEXT",
    /*  812 */ "glSecondaryColor3s",
    /*  813 */ "glSecondaryColor3sEXT",
    /*  814 */ "glSecondaryColor3sv",
    /*  815 */ "glSecondaryColor3svEXT",
    /*  816 */ "glSecondaryColor3ub",
    /*  817 */ "glSecondaryColor3ubEXT",
    /*  818 */ "glSecondaryColor3ubv",
    /*  819 */ "glSecondaryColor3ubvEXT",
    /*  820 */ "glSecondaryColor3ui",
    /*  821 */ "glSecondaryColor3uiEXT",
    /*  822 */ "glSecondaryColor3uiv",
    /*  823 */ "glSecondaryColor3uivEXT",
    /*  824 */ "glSecondaryColor3us",
    /*  825 */ "glSecondaryColor3usEXT",
    /*  826 */ "glSecondaryColor3usv",
    /*  827 */ "glSecondaryColor3usvEXT",
    /*  828 */ "glSecondaryColorPointer",
    /*  829 */ "glSecondaryColorPointerEXT",
    /*  830 */ "glSelectBuffer",
    /*  831 */ "glSeparableFilter2D",
    /*  832 */ "glShadeModel",
    /*  833 */ "glShaderSource",
    /*  834 */ "glShaderSourceARB",
    /*  835 */ "glStencilFunc",
    /*  836 */ "glStencilFuncSeparate",
    /*  837 */ "glStencilFuncSeparateATI",
    /*  838 */ "glStencilMask",
    /*  839 */ "glStencilMaskSeparate",
    /*  840 */ "glStencilOp",
    /*  841 */ "glStencilOpSeparate",
    /*  842 */ "glStencilOpSeparateATI",
    /*  843 */ "glTexCoord1d",
    /*  844 */ "glTexCoord1dv",
    /*  845 */ "glTexCoord1f",
    /*  846 */ "glTexCoord1fv",
    /*  847 */ "glTexCoord1i",
    /*  848 */ "glTexCoord1iv",
    /*  849 */ "glTexCoord1s",
    /*  850 */ "glTexCoord1sv",
    /*  851 */ "glTexCoord2d",
    /*  852 */ "glTexCoord2dv",
    /*  853 */ "glTexCoord2f",
    /*  854 */ "glTexCoord2fv",
    /*  855 */ "glTexCoord2i",
    /*  856 */ "glTexCoord2iv",
    /*  857 */ "glTexCoord2s",
    /*  858 */ "glTexCoord2sv",
    /*  859 */ "glTexCoord3d",
    /*  860 */ "glTexCoord3dv",
    /*  861 */ "glTexCoord3f",
    /*  862 */ "glTexCoord3fv",
    /*  863 */ "glTexCoord3i",
    /*  864 */ "glTexCoord3iv",
    /*  865 */ "glTexCoord3s",
    /*  866 */ "glTexCoord3sv",
    /*  867 */ "glTexCoord4d",
    /*  868 */ "glTexCoord4dv",
    /*  869 */ "glTexCoord4f",
    /*  870 */ "glTexCoord4fv",
    /*  871 */ "glTexCoord4i",
    /*  872 */ "glTexCoord4iv",
    /*  873 */ "glTexCoord4s",
    /*  874 */ "glTexCoord4sv",
    /*  875 */ "glTexCoordPointer",
    /*  876 */ "glTexCoordPointerEXT",
    /*  877 */ "glTexEnvf",
    /*  878 */ "glTexEnvfv",
    /*  879 */ "glTexEnvi",
    /*  880 */ "glTexEnviv",
    /*  881 */ "glTexGend",
    /*  882 */ "glTexGendv",
    /*  883 */ "glTexGenf",
    /*  884 */ "glTexGenfv",
    /*  885 */ "glTexGeni",
    /*  886 */ "glTexGeniv",
    /*  887 */ "glTexImage1D",
    /*  888 */ "glTexImage2D",
    /*  889 */ "glTexImage3D",
    /*  890 */ "glTexImage3DEXT",
    /*  891 */ "glTexParameterf",
    /*  892 */ "glTexParameterfv",
    /*  893 */ "glTexParameteri",
    /*  894 */ "glTexParameteriv",
    /*  895 */ "glTexStorage1DEXT",
    /*  896 */ "glTexStorage2DEXT",
    /*  897 */ "glTexStorage3DEXT",
    /*  898 */ "glTexSubImage1D",
    /*  899 */ "glTexSubImage1DEXT",
    /*  900 */ "glTexSubImage2D",
    /*  901 */ "glTexSubImage2DEXT",
    /*  902 */ "glTexSubImage3D",
    /*  903 */ "glTexSubImage3DEXT",
    /*  904 */ "glTextureBufferEXT",
    /*  905 */ "glTextureBufferRangeEXT",
    /*  906 */ "glTextureImage1DEXT",
    /*  907 */ "glTextureImage2DEXT",
    /*  908 */ "glTextureImage3DEXT",
    /*  909 */ "glTexturePageCommitmentEXT",
    /*  910 */ "glTextureParameterIivEXT",
    /*  911 */ "glTextureParameterIuivEXT",
    /*  912 */ "glTextureParameterfEXT",
    /*  913 */ "glTextureParameterfvEXT",
    /*  914 */ "glTextureParameteriEXT",
    /*  915 */ "glTextureParameterivEXT",
    /*  916 */ "glTextureRenderbufferEXT",
    /*  917 */ "glTextureStorage1DEXT",
    /*  918 */ "glTextureStorage2DEXT",
    /*  919 */ "glTextureStorage2DMultisampleEXT",
    /*  920 */ "glTextureStorage3DEXT",
    /*  921 */ "glTextureStorage3DMultisampleEXT",
    /*  922 */ "glTextureSubImage1DEXT",
    /*  923 */ "glTextureSubImage2DEXT",
    /*  924 */ "glTextureSubImage3DEXT",
    /*  925 */ "glTrackMatrixNV",
    /*  926 */ "glTranslated",
    /*  927 */ "glTranslatef",
    /*  928 */ "glUniform1f",
    /*  929 */ "glUniform1fARB",
    /*  930 */ "glUniform1fv",
    /*  931 */ "glUniform1fvARB",
    /*  932 */ "glUniform1i",
    /*  933 */ "glUniform1iARB",
    /*  934 */ "glUniform1iv",
    /*  935 */ "glUniform1ivARB",
    /*  936 */ "glUniform2f",
    /*  937 */ "glUniform2fARB",
    /*  938 */ "glUniform2fv",
    /*  939 */ "glUniform2fvARB",
    /*  940 */ "glUniform2i",
    /*  941 */ "glUniform2iARB",
    /*  942 */ "glUniform2iv",
    /*  943 */ "glUniform2ivARB",
    /*  944 */ "glUniform3f",
    /*  945 */ "glUniform3fARB",
    /*  946 */ "glUniform3fv",
    /*  947 */ "glUniform3fvARB",
    /*  948 */ "glUniform3i",
    /*  949 */ "glUniform3iARB",
    /*  950 */ "glUniform3iv",
    /*  951 */ "glUniform3ivARB",
    /*  952 */ "glUniform4f",
    /*  953 */ "glUniform4fARB",
    /*  954 */ "glUniform4fv",
    /*  955 */ "glUniform4fvARB",
    /*  956 */ "glUniform4i",
    /*  957 */ "glUniform4iARB",
    /*  958 */ "glUniform4iv",
    /*  959 */ "glUniform4ivARB",
    /*  960 */ "glUniformMatrix2fv",
    /*  961 */ "glUniformMatrix2fvARB",
    /*  962 */ "glUniformMatrix2x3fv",
    /*  963 */ "glUniformMatrix2x4fv",
    /*  964 */ "glUniformMatrix3fv",
    /*  965 */ "glUniformMatrix3fvARB",
    /*  966 */ "glUniformMatrix3x2fv",
    /*  967 */ "glUniformMatrix3x4fv",
    /*  968 */ "glUniformMatrix4fv",
    /*  969 */ "glUniformMatrix4fvARB",
    /*  970 */ "glUniformMatrix4x2fv",
    /*  971 */ "glUniformMatrix4x3fv",
    /*  972 */ "glUnmapBuffer",
    /*  973 */ "glUnmapBufferARB",
    /*  974 */ "glUnmapNamedBufferEXT",
    /*  975 */ "glUseProgram",
    /*  976 */ "glUseProgramObjectARB",
    /*  977 */ "glValidateProgram",
    /*  978 */ "glValidateProgramARB",
    /*  979 */ "glVertex2d",
    /*  980 */ "glVertex2dv",
    /*  981 */ "glVertex2f",
    /*  982 */ "glVertex2fv",
    /*  983 */ "glVertex2i",
    /*  984 */ "glVertex2iv",
    /*  985 */ "glVertex2s",
    /*  986 */ "glVertex2sv",
    /*  987 */ "glVertex3d",
    /*  988 */ "glVertex3dv",
    /*  989 */ "glVertex3f",
    /*  990 */ "glVertex3fv",
    /*  991 */ "glVertex3i",
    /*  992 */ "glVertex3iv",
    /*  993 */ "glVertex3s",
    /*  994 */ "glVertex3sv",
    /*  995 */ "glVertex4d",
    /*  996 */ "glVertex4dv",
    /*  997 */ "glVertex4f",
    /*  998 */ "glVertex4fv",
    /*  999 */ "glVertex4i",
    /* 1000 */ "glVertex4iv",
    /* 1001 */ "glVertex4s",
    /* 1002 */ "glVertex4sv",
    /* 1003 */ "glVertexArrayBindVertexBufferEXT",
    /* 1004 */ "glVertexArrayColorOffsetEXT",
    /* 1005 */ "glVertexArrayEdgeFlagOffsetEXT",
    /* 1006 */ "glVertexArrayFogCoordOffsetEXT",
    /* 1007 */ "glVertexArrayIndexOffsetEXT",
    /* 1008 */ "glVertexArrayMultiTexCoordOffsetEXT",
    /* 1009 */ "glVertexArrayNormalOffsetEXT",
    /* 1010 */ "glVertexArraySecondaryColorOffsetEXT",
    /* 1011 */ "glVertexArrayTexCoordOffsetEXT",
    /* 1012 */ "glVertexArrayVertexAttribBindingEXT",
    /* 1013 */ "glVertexArrayVertexAttribDivisorEXT",
    /* 1014 */ "glVertexArrayVertexAttribFormatEXT",
    /* 1015 */ "glVertexArrayVertexAttribIFormatEXT",
    /* 1016 */ "glVertexArrayVertexAttribIOffsetEXT",
    /* 1017 */ "glVertexArrayVertexAttribLFormatEXT",
    /* 1018 */ "glVertexArrayVertexAttribLOffsetEXT",
    /* 1019 */ "glVertexArrayVertexAttribOffsetEXT",
    /* 1020 */ "glVertexArrayVertexBindingDivisorEXT",
    /* 1021 */ "glVertexArrayVertexOffsetEXT",
    /* 1022 */ "glVertexAttrib1d",
    /* 1023 */ "glVertexAttrib1dARB",
    /* 1024 */ "glVertexAttrib1dNV",
    /* 1025 */ "glVertexAttrib1dv",
    /* 1026 */ "glVertexAttrib1dvARB",
    /* 1027 */ "glVertexAttrib1dvNV",
    /* 1028 */ "glVertexAttrib1f",
    /* 1029 */ "glVertexAttrib1fARB",
    /* 1030 */ "glVertexAttrib1fNV",
    /* 1031 */ "glVertexAttrib1fv",
    /* 1032 */ "glVertexAttrib1fvARB",
    /* 1033 */ "glVertexAttrib1fvNV",
    /* 1034 */ "glVertexAttrib1s",
    /* 1035 */ "glVertexAttrib1sARB",
    /* 1036 */ "glVertexAttrib1sNV",
    /* 1037 */ "glVertexAttrib1sv",
    /* 1038 */ "glVertexAttrib1svARB",
    /* 1039 */ "glVertexAttrib1svNV",
    /* 1040 */ "glVertexAttrib2d",
    /* 1041 */ "glVertexAttrib2dARB",
    /* 1042 */ "glVertexAttrib2dNV",
    /* 1043 */ "glVertexAttrib2dv",
    /* 1044 */ "glVertexAttrib2dvARB",
    /* 1045 */ "glVertexAttrib2dvNV",
    /* 1046 */ "glVertexAttrib2f",
    /* 1047 */ "glVertexAttrib2fARB",
    /* 1048 */ "glVertexAttrib2fNV",
    /* 1049 */ "glVertexAttrib2fv",
    /* 1050 */ "glVertexAttrib2fvARB",
    /* 1051 */ "glVertexAttrib2fvNV",
    /* 1052 */ "glVertexAttrib2s",
    /* 1053 */ "glVertexAttrib2sARB",
    /* 1054 */ "glVertexAttrib2sNV",
    /* 1055 */ "glVertexAttrib2sv",
    /* 1056 */ "glVertexAttrib2svARB",
    /* 1057 */ "glVertexAttrib2svNV",
    /* 1058 */ "glVertexAttrib3d",
    /* 1059 */ "glVertexAttrib3dARB",
    /* 1060 */ "glVertexAttrib3dNV",
    /* 1061 */ "glVertexAttrib3dv",
    /* 1062 */ "glVertexAttrib3dvARB",
    /* 1063 */ "glVertexAttrib3dvNV",
    /* 1064 */ "glVertexAttrib3f",
    /* 1065 */ "glVertexAttrib3fARB",
    /* 1066 */ "glVertexAttrib3fNV",
    /* 1067 */ "glVertexAttrib3fv",
    /* 1068 */ "glVertexAttrib3fvARB",
    /* 1069 */ "glVertexAttrib3fvNV",
    /* 1070 */ "glVertexAttrib3s",
    /* 1071 */ "glVertexAttrib3sARB",
    /* 1072 */ "glVertexAttrib3sNV",
    /* 1073 */ "glVertexAttrib3sv",
    /* 1074 */ "glVertexAttrib3svARB",
    /* 1075 */ "glVertexAttrib3svNV",
    /* 1076 */ "glVertexAttrib4Nbv",
    /* 1077 */ "glVertexAttrib4NbvARB",
    /* 1078 */ "glVertexAttrib4Niv",
    /* 1079 */ "glVertexAttrib4NivARB",
    /* 1080 */ "glVertexAttrib4Nsv",
    /* 1081 */ "glVertexAttrib4NsvARB",
    /* 1082 */ "glVertexAttrib4Nub",
    /* 1083 */ "glVertexAttrib4NubARB",
    /* 1084 */ "glVertexAttrib4Nubv",
    /* 1085 */ "glVertexAttrib4NubvARB",
    /* 1086 */ "glVertexAttrib4Nuiv",
    /* 1087 */ "glVertexAttrib4NuivARB",
    /* 1088 */ "glVertexAttrib4Nusv",
    /* 1089 */ "glVertexAttrib4NusvARB",
    /* 1090 */ "glVertexAttrib4bv",
    /* 1091 */ "glVertexAttrib4bvARB",
    /* 1092 */ "glVertexAttrib4d",
    /* 1093 */ "glVertexAttrib4dARB",
    /* 1094 */ "glVertexAttrib4dNV",
    /* 1095 */ "glVertexAttrib4dv",
    /* 1096 */ "glVertexAttrib4dvARB",
    /* 1097 */ "glVertexAttrib4dvNV",
    /* 1098 */ "glVertexAttrib4f",
    /* 1099 */ "glVertexAttrib4fARB",
    /* 1100 */ "glVertexAttrib4fNV",
    /* 1101 */ "glVertexAttrib4fv",
    /* 1102 */ "glVertexAttrib4fvARB",
    /* 1103 */ "glVertexAttrib4fvNV",
    /* 1104 */ "glVertexAttrib4iv",
    /* 1105 */ "glVertexAttrib4ivARB",
    /* 1106 */ "glVertexAttrib4s",
    /* 1107 */ "glVertexAttrib4sARB",
    /* 1108 */ "glVertexAttrib4sNV",
    /* 1109 */ "glVertexAttrib4sv",
    /* 1110 */ "glVertexAttrib4svARB",
    /* 1111 */ "glVertexAttrib4svNV",
    /* 1112 */ "glVertexAttrib4ubNV",
    /* 1113 */ "glVertexAttrib4ubv",
    /* 1114 */ "glVertexAttrib4ubvARB",
    /* 1115 */ "glVertexAttrib4ubvNV",
    /* 1116 */ "glVertexAttrib4uiv",
    /* 1117 */ "glVertexAttrib4uivARB",
    /* 1118 */ "glVertexAttrib4usv",
    /* 1119 */ "glVertexAttrib4usvARB",
    /* 1120 */ "glVertexAttribPointer",
    /* 1121 */ "glVertexAttribPointerARB",
    /* 1122 */ "glVertexAttribPointerNV",
    /* 1123 */ "glVertexAttribs1dvNV",
    /* 1124 */ "glVertexAttribs1fvNV",
    /* 1125 */ "glVertexAttribs1svNV",
    /* 1126 */ "glVertexAttribs2dvNV",
    /* 1127 */ "glVertexAttribs2fvNV",
    /* 1128 */ "glVertexAttribs2svNV",
    /* 1129 */ "glVertexAttribs3dvNV",
    /* 1130 */ "glVertexAttribs3fvNV",
    /* 1131 */ "glVertexAttribs3svNV",
    /* 1132 */ "glVertexAttribs4dvNV",
    /* 1133 */ "glVertexAttribs4fvNV",
    /* 1134 */ "glVertexAttribs4svNV",
    /* 1135 */ "glVertexAttribs4ubvNV",
    /* 1136 */ "glVertexPointer",
    /* 1137 */ "glVertexPointerEXT",
    /* 1138 */ "glViewport",
    /* 1139 */ "glWindowPos2d",
    /* 1140 */ "glWindowPos2dARB",
    /* 1141 */ "glWindowPos2dMESA",
    /* 1142 */ "glWindowPos2dv",
    /* 1143 */ "glWindowPos2dvARB",
    /* 1144 */ "glWindowPos2dvMESA",
    /* 1145 */ "glWindowPos2f",
    /* 1146 */ "glWindowPos2fARB",
    /* 1147 */ "glWindowPos2fMESA",
    /* 1148 */ "glWindowPos2fv",
    /* 1149 */ "glWindowPos2fvARB",
    /* 1150 */ "glWindowPos2fvMESA",
    /* 1151 */ "glWindowPos2i",
    /* 1152 */ "glWindowPos2iARB",
    /* 1153 */ "glWindowPos2iMESA",
    /* 1154 */ "glWindowPos2iv",
    /* 1155 */ "glWindowPos2ivARB",
    /* 1156 */ "glWindowPos2ivMESA",
    /* 1157 */ "glWindowPos2s",
    /* 1158 */ "glWindowPos2sARB",
    /* 1159 */ "glWindowPos2sMESA",
    /* 1160 */ "glWindowPos2sv",
    /* 1161 */ "glWindowPos2svARB",
    /* 1162 */ "glWindowPos2svMESA",
    /* 1163 */ "glWindowPos3d",
    /* 1164 */ "glWindowPos3dARB",
    /* 1165 */ "glWindowPos3dMESA",
    /* 1166 */ "glWindowPos3dv",
    /* 1167 */ "glWindowPos3dvARB",
    /* 1168 */ "glWindowPos3dvMESA",
    /* 1169 */ "glWindowPos3f",
    /* 1170 */ "glWindowPos3fARB",
    /* 1171 */ "glWindowPos3fMESA",
    /* 1172 */ "glWindowPos3fv",
    /* 1173 */ "glWindowPos3fvARB",
    /* 1174 */ "glWindowPos3fvMESA",
    /* 1175 */ "glWindowPos3i",
    /* 1176 */ "glWindowPos3iARB",
    /* 1177 */ "glWindowPos3iMESA",
    /* 1178 */ "glWindowPos3iv",
    /* 1179 */ "glWindowPos3ivARB",
    /* 1180 */ "glWindowPos3ivMESA",
    /* 1181 */ "glWindowPos3s",
    /* 1182 */ "glWindowPos3sARB",
    /* 1183 */ "glWindowPos3sMESA",
    /* 1184 */ "glWindowPos3sv",
    /* 1185 */ "glWindowPos3svARB",
    /* 1186 */ "glWindowPos3svMESA",
    /* 1187 */ "glWindowPos4dMESA",
    /* 1188 */ "glWindowPos4dvMESA",
    /* 1189 */ "glWindowPos4fMESA",
    /* 1190 */ "glWindowPos4fvMESA",
    /* 1191 */ "glWindowPos4iMESA",
    /* 1192 */ "glWindowPos4ivMESA",
    /* 1193 */ "glWindowPos4sMESA",
    /* 1194 */ "glWindowPos4svMESA",
    /* 1195 */ "glActiveShaderProgram",
    /* 1196 */ "glActiveShaderProgramEXT",
    /* 1197 */ "glBeginQueryEXT",
    /* 1198 */ "glBeginTransformFeedback",
    /* 1199 */ "glBindBufferBase",
    /* 1200 */ "glBindBufferRange",
    /* 1201 */ "glBindFramebuffer",
    /* 1202 */ "glBindImageTexture",
    /* 1203 */ "glBindProgramPipeline",
    /* 1204 */ "glBindProgramPipelineEXT",
    /* 1205 */ "glBindRenderbuffer",
    /* 1206 */ "glBindSampler",
    /* 1207 */ "glBindTransformFeedback",
    /* 1208 */ "glBindVertexArray",
    /* 1209 */ "glBindVertexArrayOES",
    /* 1210 */ "glBindVertexBuffer",
    /* 1211 */ "glBlendBarrier",
    /* 1212 */ "glBlendBarrierKHR",
    /* 1213 */ "glBlendBarrierNV",
    /* 1214 */ "glBlendEquationSeparatei",
    /* 1215 */ "glBlendEquationSeparateiEXT",
    /* 1216 */ "glBlendEquationSeparateiOES",
    /* 1217 */ "glBlendEquationi",
    /* 1218 */ "glBlendEquationiEXT",
    /* 1219 */ "glBlendEquationiOES",
    /* 1220 */ "glBlendFuncSeparatei",
    /* 1221 */ "glBlendFuncSeparateiEXT",
    /* 1222 */ "glBlendFuncSeparateiOES",
    /* 1223 */ "glBlendFunci",
    /* 1224 */ "glBlendFunciEXT",
    /* 1225 */ "glBlendFunciOES",
    /* 1226 */ "glBlendParameteriNV",
    /* 1227 */ "glBlitFramebuffer",
    /* 1228 */ "glBlitFramebufferNV",
    /* 1229 */ "glCheckFramebufferStatus",
    /* 1230 */ "glClearBufferfi",
    /* 1231 */ "glClearBufferfv",
    /* 1232 */ "glClearBufferiv",
    /* 1233 */ "glClearBufferuiv",
    /* 1234 */ "glClearDepthf",
    /* 1235 */ "glClientWaitSync",
    /* 1236 */ "glClientWaitSyncAPPLE",
    /* 1237 */ "glColorMaski",
    /* 1238 */ "glColorMaskiEXT",
    /* 1239 */ "glColorMaskiOES",
    /* 1240 */ "glCopyBufferSubData",
    /* 1241 */ "glCopyBufferSubDataNV",
    /* 1242 */ "glCopyImageSubData",
    /* 1243 */ "glCopyImageSubDataEXT",
    /* 1244 */ "glCopyImageSubDataOES",
    /* 1245 */ "glCreateShaderProgramv",
    /* 1246 */ "glCreateShaderProgramvEXT",
    /* 1247 */ "glDebugMessageCallbackKHR",
    /* 1248 */ "glDebugMessageControlKHR",
    /* 1249 */ "glDebugMessageInsertKHR",
    /* 1250 */ "glDeleteFramebuffers",
    /* 1251 */ "glDeleteProgramPipelines",
    /* 1252 */ "glDeleteProgramPipelinesEXT",
    /* 1253 */ "glDeleteQueriesEXT",
    /* 1254 */ "glDeleteRenderbuffers",
    /* 1255 */ "glDeleteSamplers",
    /* 1256 */ "glDeleteSync",
    /* 1257 */ "glDeleteSyncAPPLE",
    /* 1258 */ "glDeleteTransformFeedbacks",
    /* 1259 */ "glDeleteVertexArrays",
    /* 1260 */ "glDeleteVertexArraysOES",
    /* 1261 */ "glDepthRangeArrayfvNV",
    /* 1262 */ "glDepthRangeArrayfvOES",
    /* 1263 */ "glDepthRangeIndexedfNV",
    /* 1264 */ "glDepthRangeIndexedfOES",
    /* 1265 */ "glDepthRangef",
    /* 1266 */ "glDisablei",
    /* 1267 */ "glDisableiEXT",
    /* 1268 */ "glDisableiNV",
    /* 1269 */ "glDisableiOES",
    /* 1270 */ "glDispatchCompute",
    /* 1271 */ "glDispatchComputeIndirect",
    /* 1272 */ "glDrawArraysIndirect",
    /* 1273 */ "glDrawArraysInstanced",
    /* 1274 */ "glDrawArraysInstancedANGLE",
    /* 1275 */ "glDrawArraysInstancedEXT",
    /* 1276 */ "glDrawArraysInstancedNV",
    /* 1277 */ "glDrawBuffersEXT",
    /* 1278 */ "glDrawElementsBaseVertex",
    /* 1279 */ "glDrawElementsBaseVertexEXT",
    /* 1280 */ "glDrawElementsBaseVertexOES",
    /* 1281 */ "glDrawElementsIndirect",
    /* 1282 */ "glDrawElementsInstanced",
    /* 1283 */ "glDrawElementsInstancedANGLE",
    /* 1284 */ "glDrawElementsInstancedBaseVertex",
    /* 1285 */ "glDrawElementsInstancedBaseVertexEXT",
    /* 1286 */ "glDrawElementsInstancedBaseVertexOES",
    /* 1287 */ "glDrawElementsInstancedEXT",
    /* 1288 */ "glDrawElementsInstancedNV",
    /* 1289 */ "glDrawRangeElementsBaseVertex",
    /* 1290 */ "glDrawRangeElementsBaseVertexEXT",
    /* 1291 */ "glDrawRangeElementsBaseVertexOES",
    /* 1292 */ "glEnablei",
    /* 1293 */ "glEnableiEXT",
    /* 1294 */ "glEnableiNV",
    /* 1295 */ "glEnableiOES",
    /* 1296 */ "glEndQueryEXT",
    /* 1297 */ "glEndTransformFeedback",
    /* 1298 */ "glFenceSync",
    /* 1299 */ "glFenceSyncAPPLE",
    /* 1300 */ "glFlushMappedBufferRange",
    /* 1301 */ "glFlushMappedBufferRangeEXT",
    /* 1302 */ "glFramebufferParameteri",
    /* 1303 */ "glFramebufferRenderbuffer",
    /* 1304 */ "glFramebufferTexture",
    /* 1305 */ "glFramebufferTexture2D",
    /* 1306 */ "glFramebufferTexture2DMultisampleEXT",
    /* 1307 */ "glFramebufferTextureEXT",
    /* 1308 */ "glFramebufferTextureLayer",
    /* 1309 */ "glFramebufferTextureOES",
    /* 1310 */ "glGenFramebuffers",
    /* 1311 */ "glGenProgramPipelines",
    /* 1312 */ "glGenProgramPipelinesEXT",
    /* 1313 */ "glGenQueriesEXT",
    /* 1314 */ "glGenRenderbuffers",
    /* 1315 */ "glGenSamplers",
    /* 1316 */ "glGenTransformFeedbacks",
    /* 1317 */ "glGenVertexArrays",
    /* 1318 */ "glGenVertexArraysOES",
    /* 1319 */ "glGenerateMipmap",
    /* 1320 */ "glGetActiveUniformBlockName",
    /* 1321 */ "glGetActiveUniformBlockiv",
    /* 1322 */ "glGetActiveUniformsiv",
    /* 1323 */ "glGetBooleani_v",
    /* 1324 */ "glGetBufferParameteri64v",
    /* 1325 */ "glGetBufferPointervOES",
    /* 1326 */ "glGetDebugMessageLogKHR",
    /* 1327 */ "glGetFloati_vNV",
    /* 1328 */ "glGetFloati_vOES",
    /* 1329 */ "glGetFragDataLocation",
    /* 1330 */ "glGetFramebufferAttachmentParameteriv",
    /* 1331 */ "glGetFramebufferParameteriv",
    /* 1332 */ "glGetGraphicsResetStatus",
    /* 1333 */ "glGetGraphicsResetStatusEXT",
    /* 1334 */ "glGetGraphicsResetStatusKHR",
    /* 1335 */ "glGetInteger64i_v",
    /* 1336 */ "glGetInteger64v",
    /* 1337 */ "glGetInteger64vAPPLE",
    /* 1338 */ "glGetInteger64vEXT",
    /* 1339 */ "glGetIntegeri_v",
    /* 1340 */ "glGetInternalformativ",
    /* 1341 */ "glGetMultisamplefv",
    /* 1342 */ "glGetMultisamplefvANGLE",
    /* 1343 */ "glGetObjectLabelKHR",
    /* 1344 */ "glGetObjectPtrLabelKHR",
    /* 1345 */ "glGetPointervKHR",
    /* 1346 */ "glGetProgramBinary",
    /* 1347 */ "glGetProgramBinaryOES",
    /* 1348 */ "glGetProgramInterfaceiv",
    /* 1349 */ "glGetProgramPipelineInfoLog",
    /* 1350 */ "glGetProgramPipelineInfoLogEXT",
    /* 1351 */ "glGetProgramPipelineiv",
    /* 1352 */ "glGetProgramPipelineivEXT",
    /* 1353 */ "glGetProgramResourceIndex",
    /* 1354 */ "glGetProgramResourceLocation",
    /* 1355 */ "glGetProgramResourceName",
    /* 1356 */ "glGetProgramResourceiv",
    /* 1357 */ "glGetQueryObjecti64vEXT",
    /* 1358 */ "glGetQueryObjectivEXT",
    /* 1359 */ "glGetQueryObjectui64vEXT",
    /* 1360 */ "glGetQueryObjectuivEXT",
    /* 1361 */ "glGetQueryivEXT",
    /* 1362 */ "glGetRenderbufferParameteriv",
    /* 1363 */ "glGetSamplerParameterIiv",
    /* 1364 */ "glGetSamplerParameterIivEXT",
    /* 1365 */ "glGetSamplerParameterIivOES",
    /* 1366 */ "glGetSamplerParameterIuiv",
    /* 1367 */ "glGetSamplerParameterIuivEXT",
    /* 1368 */ "glGetSamplerParameterIuivOES",
    /* 1369 */ "glGetSamplerParameterfv",
    /* 1370 */ "glGetSamplerParameteriv",
    /* 1371 */ "glGetShaderPrecisionFormat",
    /* 1372 */ "glGetStringi",
    /* 1373 */ "glGetSynciv",
    /* 1374 */ "glGetSyncivAPPLE",
    /* 1375 */ "glGetTexLevelParameterfvANGLE",
    /* 1376 */ "glGetTexLevelParameterivANGLE",
    /* 1377 */ "glGetTexParameterIiv",
    /* 1378 */ "glGetTexParameterIivEXT",
    /* 1379 */ "glGetTexParameterIivOES",
    /* 1380 */ "glGetTexParameterIuiv",
    /* 1381 */ "glGetTexParameterIuivEXT",
    /* 1382 */ "glGetTexParameterIuivOES",
    /* 1383 */ "glGetTransformFeedbackVarying",
    /* 1384 */ "glGetUniformBlockIndex",
    /* 1385 */ "glGetUniformIndices",
    /* 1386 */ "glGetUniformuiv",
    /* 1387 */ "glGetVertexAttribIiv",
    /* 1388 */ "glGetVertexAttribIuiv",
    /* 1389 */ "glGetnUniformfv",
    /* 1390 */ "glGetnUniformfvEXT",
    /* 1391 */ "glGetnUniformfvKHR",
    /* 1392 */ "glGetnUniformiv",
    /* 1393 */ "glGetnUniformivEXT",
    /* 1394 */ "glGetnUniformivKHR",
    /* 1395 */ "glGetnUniformuiv",
    /* 1396 */ "glGetnUniformuivKHR",
    /* 1397 */ "glInvalidateFramebuffer",
    /* 1398 */ "glInvalidateSubFramebuffer",
    /* 1399 */ "glIsEnabledi",
    /* 1400 */ "glIsEnablediEXT",
    /* 1401 */ "glIsEnablediNV",
    /* 1402 */ "glIsEnablediOES",
    /* 1403 */ "glIsFramebuffer",
    /* 1404 */ "glIsProgramPipeline",
    /* 1405 */ "glIsProgramPipelineEXT",
    /* 1406 */ "glIsQueryEXT",
    /* 1407 */ "glIsRenderbuffer",
    /* 1408 */ "glIsSampler",
    /* 1409 */ "glIsSync",
    /* 1410 */ "glIsSyncAPPLE",
    /* 1411 */ "glIsTransformFeedback",
    /* 1412 */ "glIsVertexArray",
    /* 1413 */ "glIsVertexArrayOES",
    /* 1414 */ "glMapBufferOES",
    /* 1415 */ "glMapBufferRange",
    /* 1416 */ "glMapBufferRangeEXT",
    /* 1417 */ "glMemoryBarrier",
    /* 1418 */ "glMemoryBarrierByRegion",
    /* 1419 */ "glMinSampleShading",
    /* 1420 */ "glMinSampleShadingOES",
    /* 1421 */ "glMultiDrawElementsBaseVertexEXT",
    /* 1422 */ "glObjectLabelKHR",
    /* 1423 */ "glObjectPtrLabelKHR",
    /* 1424 */ "glPatchParameteri",
    /* 1425 */ "glPatchParameteriEXT",
    /* 1426 */ "glPatchParameteriOES",
    /* 1427 */ "glPauseTransformFeedback",
    /* 1428 */ "glPopDebugGroupKHR",
    /* 1429 */ "glPrimitiveBoundingBox",
    /* 1430 */ "glPrimitiveBoundingBoxEXT",
    /* 1431 */ "glPrimitiveBoundingBoxOES",
    /* 1432 */ "glProgramBinary",
    /* 1433 */ "glProgramBinaryOES",
    /* 1434 */ "glProgramParameteri",
    /* 1435 */ "glProgramParameteriEXT",
    /* 1436 */ "glProgramUniform1f",
    /* 1437 */ "glProgramUniform1fv",
    /* 1438 */ "glProgramUniform1i",
    /* 1439 */ "glProgramUniform1iv",
    /* 1440 */ "glProgramUniform1ui",
    /* 1441 */ "glProgramUniform1uiv",
    /* 1442 */ "glProgramUniform2f",
    /* 1443 */ "glProgramUniform2fv",
    /* 1444 */ "glProgramUniform2i",
    /* 1445 */ "glProgramUniform2iv",
    /* 1446 */ "glProgramUniform2ui",
    /* 1447 */ "glProgramUniform2uiv",
    /* 1448 */ "glProgramUniform3f",
    /* 1449 */ "glProgramUniform3fv",
    /* 1450 */ "glProgramUniform3i",
    /* 1451 */ "glProgramUniform3iv",
    /* 1452 */ "glProgramUniform3ui",
    /* 1453 */ "glProgramUniform3uiv",
    /* 1454 */ "glProgramUniform4f",
    /* 1455 */ "glProgramUniform4fv",
    /* 1456 */ "glProgramUniform4i",
    /* 1457 */ "glProgramUniform4iv",
    /* 1458 */ "glProgramUniform4ui",
    /* 1459 */ "glProgramUniform4uiv",
    /* 1460 */ "glProgramUniformMatrix2fv",
    /* 1461 */ "glProgramUniformMatrix2x3fv",
    /* 1462 */ "glProgramUniformMatrix2x4fv",
    /* 1463 */ "glProgramUniformMatrix3fv",
    /* 1464 */ "glProgramUniformMatrix3x2fv",
    /* 1465 */ "glProgramUniformMatrix3x4fv",
    /* 1466 */ "glProgramUniformMatrix4fv",
    /* 1467 */ "glProgramUniformMatrix4x2fv",
    /* 1468 */ "glProgramUniformMatrix4x3fv",
    /* 1469 */ "glPushDebugGroupKHR",
    /* 1470 */ "glQueryCounterEXT",
    /* 1471 */ "glReadnPixels",
    /* 1472 */ "glReadnPixelsEXT",
    /* 1473 */ "glReadnPixelsKHR",
    /* 1474 */ "glReleaseShaderCompiler",
    /* 1475 */ "glRenderbufferStorage",
    /* 1476 */ "glRenderbufferStorageMultisample",
    /* 1477 */ "glRenderbufferStorageMultisampleEXT",
    /* 1478 */ "glRenderbufferStorageMultisampleNV",
    /* 1479 */ "glResumeTransformFeedback",
    /* 1480 */ "glSampleMaski",
    /* 1481 */ "glSampleMaskiANGLE",
    /* 1482 */ "glSamplerParameterIiv",
    /* 1483 */ "glSamplerParameterIivEXT",
    /* 1484 */ "glSamplerParameterIivOES",
    /* 1485 */ "glSamplerParameterIuiv",
    /* 1486 */ "glSamplerParameterIuivEXT",
    /* 1487 */ "glSamplerParameterIuivOES",
    /* 1488 */ "glSamplerParameterf",
    /* 1489 */ "glSamplerParameterfv",
    /* 1490 */ "glSamplerParameteri",
    /* 1491 */ "glSamplerParameteriv",
    /* 1492 */ "glScissorArrayvNV",
    /* 1493 */ "glScissorArrayvOES",
    /* 1494 */ "glScissorIndexedNV",
    /* 1495 */ "glScissorIndexedOES",
    /* 1496 */ "glScissorIndexedvNV",
    /* 1497 */ "glScissorIndexedvOES",
    /* 1498 */ "glShaderBinary",
    /* 1499 */ "glTexBuffer",
    /* 1500 */ "glTexBufferEXT",
    /* 1501 */ "glTexBufferOES",
    /* 1502 */ "glTexBufferRange",
    /* 1503 */ "glTexBufferRangeEXT",
    /* 1504 */ "glTexBufferRangeOES",
    /* 1505 */ "glTexParameterIiv",
    /* 1506 */ "glTexParameterIivEXT",
    /* 1507 */ "glTexParameterIivOES",
    /* 1508 */ "glTexParameterIuiv",
    /* 1509 */ "glTexParameterIuivEXT",
    /* 1510 */ "glTexParameterIuivOES",
    /* 1511 */ "glTexStorage2D",
    /* 1512 */ "glTexStorage2DMultisample",
    /* 1513 */ "glTexStorage2DMultisampleANGLE",
    /* 1514 */ "glTexStorage3D",
    /* 1515 */ "glTexStorage3DMultisample",
    /* 1516 */ "glTexStorage3DMultisampleOES",
    /* 1517 */ "glTransformFeedbackVaryings",
    /* 1518 */ "glUniform1ui",
    /* 1519 */ "glUniform1uiv",
    /* 1520 */ "glUniform2ui",
    /* 1521 */ "glUniform2uiv",
    /* 1522 */ "glUniform3ui",
    /* 1523 */ "glUniform3uiv",
    /* 1524 */ "glUniform4ui",
    /* 1525 */ "glUniform4uiv",
    /* 1526 */ "glUniformBlockBinding",
    /* 1527 */ "glUniformMatrix2x3fvNV",
    /* 1528 */ "glUniformMatrix2x4fvNV",
    /* 1529 */ "glUniformMatrix3x2fvNV",
    /* 1530 */ "glUniformMatrix3x4fvNV",
    /* 1531 */ "glUniformMatrix4x2fvNV",
    /* 1532 */ "glUniformMatrix4x3fvNV",
    /* 1533 */ "glUnmapBufferOES",
    /* 1534 */ "glUseProgramStages",
    /* 1535 */ "glUseProgramStagesEXT",
    /* 1536 */ "glValidateProgramPipeline",
    /* 1537 */ "glValidateProgramPipelineEXT",
    /* 1538 */ "glVertexAttribBinding",
    /* 1539 */ "glVertexAttribDivisor",
    /* 1540 */ "glVertexAttribDivisorANGLE",
    /* 1541 */ "glVertexAttribDivisorEXT",
    /* 1542 */ "glVertexAttribDivisorNV",
    /* 1543 */ "glVertexAttribFormat",
    /* 1544 */ "glVertexAttribI4i",
    /* 1545 */ "glVertexAttribI4iv",
    /* 1546 */ "glVertexAttribI4ui",
    /* 1547 */ "glVertexAttribI4uiv",
    /* 1548 */ "glVertexAttribIFormat",
    /* 1549 */ "glVertexAttribIPointer",
    /* 1550 */ "glVertexBindingDivisor",
    /* 1551 */ "glViewportArrayvNV",
    /* 1552 */ "glViewportArrayvOES",
    /* 1553 */ "glViewportIndexedfNV",
    /* 1554 */ "glViewportIndexedfOES",
    /* 1555 */ "glViewportIndexedfvNV",
    /* 1556 */ "glViewportIndexedfvOES",
    /* 1557 */ "glWaitSync",
    /* 1558 */ "glWaitSyncAPPLE"
};

static uint64_t GLAD_GL_ext_hashes[] = {
    /*    0 */ 0xa8bc2a751596a8c9, /* GL_ANGLE_get_tex_level_parameter */
    /*    1 */ 0xf21d57ef70efa97f, /* GL_ANGLE_instanced_arrays */
    /*    2 */ 0xbae723a89da1bdfd, /* GL_ANGLE_texture_multisample */
    /*    3 */ 0x965df8be0c61c5ef, /* GL_APPLE_sync */
    /*    4 */ 0x2aa09aeb0f69408b, /* GL_ARB_buffer_storage */
    /*    5 */ 0x2b16e3dcc2f78c79, /* GL_ARB_debug_output */
    /*    6 */ 0xe11ab2833ee38b1a, /* GL_ARB_draw_buffers */
    /*    7 */ 0x4569da13c0840fbe, /* GL_ARB_imaging */
    /*    8 */ 0x494b5f42fc0a83e4, /* GL_ARB_multisample */
    /*    9 */ 0x4a56c37f2c0b7aad, /* GL_ARB_multitexture */
    /*   10 */ 0xe8818f3733977678, /* GL_ARB_occlusion_query */
    /*   11 */ 0xffe8ee561ae2346c, /* GL_ARB_point_parameters */
    /*   12 */ 0xd8de76a336031ff0, /* GL_ARB_shader_objects */
    /*   13 */ 0x582477dc03c7221c, /* GL_ARB_texture_compression */
    /*   14 */ 0x77013d69fddefe87, /* GL_ARB_transpose_matrix */
    /*   15 */ 0xab4f226cf8bf14b2, /* GL_ARB_vertex_buffer_object */
    /*   16 */ 0x2b91406e8801f26d, /* GL_ARB_vertex_program */
    /*   17 */ 0xb74f5593e3c89e02, /* GL_ARB_vertex_shader */
    /*   18 */ 0x8fd0fb55626075a1, /* GL_ARB_window_pos */
    /*   19 */ 0xc43e90f15fb8db01, /* GL_ATI_draw_buffers */
    /*   20 */ 0xc9e128c539750596, /* GL_ATI_separate_stencil */
    /*   21 */ 0x1cafcd91efe0e1d6, /* GL_EXT_blend_color */
    /*   22 */ 0x3510ec477f22f7e7, /* GL_EXT_blend_equation_separate */
    /*   23 */ 0x97c1a7c0b569dfb8, /* GL_EXT_blend_func_separate */
    /*   24 */ 0x1163ab5d43e9b052, /* GL_EXT_blend_minmax */
    /*   25 */ 0xa26b121ae33c3436, /* GL_EXT_copy_image */
    /*   26 */ 0x2611c2618f21aa2f, /* GL_EXT_copy_texture */
    /*   27 */ 0xff4a74da40c62745, /* GL_EXT_direct_state_access */
    /*   28 */ 0x3d06b0f91612d10d, /* GL_EXT_disjoint_timer_query */
    /*   29 */ 0xd3ac9ca278a62f1a, /* GL_EXT_draw_buffers */
    /*   30 */ 0x997893a6ac44f7fe, /* GL_EXT_draw_buffers_indexed */
    /*   31 */ 0x548657f15226635b, /* GL_EXT_draw_elements_base_vertex */
    /*   32 */ 0xeb1b622faf7697c7, /* GL_EXT_draw_instanced */
    /*   33 */ 0xbb5e6eb0e1559ef1, /* GL_EXT_draw_range_elements */
    /*   34 */ 0xe09e32cd1ae79288, /* GL_EXT_fog_coord */
    /*   35 */ 0xfa22129bb4d04128, /* GL_EXT_geometry_shader */
    /*   36 */ 0x9c3c026caab1aaf7, /* GL_EXT_instanced_arrays */
    /*   37 */ 0xf41152d50d03cc16, /* GL_EXT_map_buffer_range */
    /*   38 */ 0x6077bed8aa109362, /* GL_EXT_multi_draw_arrays */
    /*   39 */ 0x33b89ab037aed106, /* GL_EXT_multisampled_render_to_texture */
    /*   40 */ 0x14eaf45986c9bfa1, /* GL_EXT_point_parameters */
    /*   41 */ 0x849565c10789238e, /* GL_EXT_primitive_bounding_box */
    /*   42 */ 0x04aaf7c50fd23609, /* GL_EXT_robustness */
    /*   43 */ 0x5da9f01e568b2e0b, /* GL_EXT_secondary_color */
    /*   44 */ 0xb207ff65f8bf495d, /* GL_EXT_separate_shader_objects */
    /*   45 */ 0xe101571ccdddbe44, /* GL_EXT_subtexture */
    /*   46 */ 0xa694e21c70c92ac7, /* GL_EXT_tessellation_shader */
    /*   47 */ 0x3c1975837c97841b, /* GL_EXT_texture3D */
    /*   48 */ 0xf02848fc36653917, /* GL_EXT_texture_border_clamp */
    /*   49 */ 0x990b742e339cfdab, /* GL_EXT_texture_buffer */
    /*   50 */ 0x10827f593acd1ba7, /* GL_EXT_texture_object */
    /*   51 */ 0x154c4c8b80533dc0, /* GL_EXT_texture_storage */
    /*   52 */ 0x2347ebc551d02975, /* GL_EXT_vertex_array */
    /*   53 */ 0xf8c1cfe37858c556, /* GL_INGR_blend_func_separate */
    /*   54 */ 0x898f16e7a19612fe, /* GL_KHR_blend_equation_advanced */
    /*   55 */ 0x5e0c5b9607ac8784, /* GL_KHR_debug */
    /*   56 */ 0x474beac5f6910636, /* GL_KHR_robustness */
    /*   57 */ 0xa14ebc048c19e849, /* GL_MESA_sampler_objects */
    /*   58 */ 0x00063de42ab739f6, /* GL_MESA_window_pos */
    /*   59 */ 0xdfb2fe6dc8d05e7b, /* GL_NV_blend_equation_advanced */
    /*   60 */ 0x1250d4e984fabb8a, /* GL_NV_copy_buffer */
    /*   61 */ 0x5cef483902a0a7d1, /* GL_NV_draw_instanced */
    /*   62 */ 0xc7b0688e759eacca, /* GL_NV_framebuffer_blit */
    /*   63 */ 0xd333a1d53faf1645, /* GL_NV_framebuffer_multisample */
    /*   64 */ 0xc2e8b0284eeb3343, /* GL_NV_instanced_arrays */
    /*   65 */ 0x5b891d5155380820, /* GL_NV_non_square_matrices */
    /*   66 */ 0x839efae2d0736a4c, /* GL_NV_point_sprite */
    /*   67 */ 0x527413b984649803, /* GL_NV_vertex_program */
    /*   68 */ 0x1b9db3e10e73323b, /* GL_NV_viewport_array */
    /*   69 */ 0xc5e1ddc1ea43276e, /* GL_OES_copy_image */
    /*   70 */ 0x012b99c59ced284f, /* GL_OES_draw_buffers_indexed */
    /*   71 */ 0x4638dd889d2b7eab, /* GL_OES_draw_elements_base_vertex */
    /*   72 */ 0xaa384a84e450d595, /* GL_OES_geometry_shader */
    /*   73 */ 0x503ad238c5e97931, /* GL_OES_get_program_binary */
    /*   74 */ 0x22e521fe25c89a3b, /* GL_OES_mapbuffer */
    /*   75 */ 0x303e15e4f8fb9ee6, /* GL_OES_primitive_bounding_box */
    /*   76 */ 0xcb740362814f4ca0, /* GL_OES_sample_shading */
    /*   77 */ 0x8bbb4c0c94dc1415, /* GL_OES_tessellation_shader */
    /*   78 */ 0xedc39fcb928c7be5, /* GL_OES_texture_border_clamp */
    /*   79 */ 0xc7d6a2d8a596bf50, /* GL_OES_texture_buffer */
    /*   80 */ 0xbc655ee4febdcfca, /* GL_OES_texture_storage_multisample_2d_array */
    /*   81 */ 0x7cd6041965da7d3c, /* GL_OES_vertex_array_object */
    /*   82 */ 0x2e0ac92809baabbd, /* GL_OES_viewport_array */
    /*   83 */ 0x4e3e0fa2dfafd5b4  /* GL_SGIS_point_parameters */
};

#ifdef __cplusplus
GladGLContext glad_gl_context = {};
#else
GladGLContext glad_gl_context = { 0 };
#endif

static void glad_gl_load_GL_VERSION_1_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           0, /* glAccum */
           3, /* glAlphaFunc */
          11, /* glBegin */
          23, /* glBitmap */
          30, /* glBlendFunc */
          39, /* glCallList */
          40, /* glCallLists */
          42, /* glClear */
          43, /* glClearAccum */
          44, /* glClearColor */
          45, /* glClearDepth */
          46, /* glClearIndex */
          49, /* glClearStencil */
          53, /* glClipPlane */
          54, /* glColor3b */
          55, /* glColor3bv */
          56, /* glColor3d */
          57, /* glColor3dv */
          58, /* glColor3f */
          59, /* glColor3fv */
          60, /* glColor3i */
          61, /* glColor3iv */
          62, /* glColor3s */
          63, /* glColor3sv */
          64, /* glColor3ub */
          65, /* glColor3ubv */
          66, /* glColor3ui */
          67, /* glColor3uiv */
          68, /* glColor3us */
          69, /* glColor3usv */
          70, /* glColor4b */
          71, /* glColor4bv */
          72, /* glColor4d */
          73, /* glColor4dv */
          74, /* glColor4f */
          75, /* glColor4fv */
          76, /* glColor4i */
          77, /* glColor4iv */
          78, /* glColor4s */
          79, /* glColor4sv */
          80, /* glColor4ub */
          81, /* glColor4ubv */
          82, /* glColor4ui */
          83, /* glColor4uiv */
          84, /* glColor4us */
          85, /* glColor4usv */
          86, /* glColorMask */
          87, /* glColorMaterial */
         135, /* glCopyPixels */
         155, /* glCullFace */
         164, /* glDeleteLists */
         174, /* glDepthFunc */
         175, /* glDepthMask */
         176, /* glDepthRange */
         179, /* glDisable */
         190, /* glDrawBuffer */
         195, /* glDrawPixels */
         198, /* glEdgeFlag */
         201, /* glEdgeFlagv */
         202, /* glEnable */
         211, /* glEnd */
         212, /* glEndList */
         215, /* glEvalCoord1d */
         216, /* glEvalCoord1dv */
         217, /* glEvalCoord1f */
         218, /* glEvalCoord1fv */
         219, /* glEvalCoord2d */
         220, /* glEvalCoord2dv */
         221, /* glEvalCoord2f */
         222, /* glEvalCoord2fv */
         223, /* glEvalMesh1 */
         224, /* glEvalMesh2 */
         225, /* glEvalPoint1 */
         226, /* glEvalPoint2 */
         228, /* glFeedbackBuffer */
         229, /* glFinish */
         230, /* glFlush */
         242, /* glFogf */
         243, /* glFogfv */
         244, /* glFogi */
         245, /* glFogiv */
         249, /* glFrontFace */
         250, /* glFrustum */
         253, /* glGenLists */
         271, /* glGetBooleanv */
         278, /* glGetClipPlane */
         293, /* glGetDoublev */
         294, /* glGetError */
         297, /* glGetFloatv */
         305, /* glGetIntegerv */
         306, /* glGetLightfv */
         307, /* glGetLightiv */
         308, /* glGetMapdv */
         309, /* glGetMapfv */
         310, /* glGetMapiv */
         311, /* glGetMaterialfv */
         312, /* glGetMaterialiv */
         344, /* glGetPixelMapfv */
         345, /* glGetPixelMapuiv */
         346, /* glGetPixelMapusv */
         351, /* glGetPolygonStipple */
         375, /* glGetString */
         376, /* glGetTexEnvfv */
         377, /* glGetTexEnviv */
         378, /* glGetTexGendv */
         379, /* glGetTexGenfv */
         380, /* glGetTexGeniv */
         381, /* glGetTexImage */
         382, /* glGetTexLevelParameterfv */
         383, /* glGetTexLevelParameteriv */
         384, /* glGetTexParameterfv */
         385, /* glGetTexParameteriv */
         416, /* glHint */
         418, /* glIndexMask */
         421, /* glIndexd */
         422, /* glIndexdv */
         423, /* glIndexf */
         424, /* glIndexfv */
         425, /* glIndexi */
         426, /* glIndexiv */
         427, /* glIndexs */
         428, /* glIndexsv */
         431, /* glInitNames */
         435, /* glIsEnabled */
         437, /* glIsList */
         446, /* glLightModelf */
         447, /* glLightModelfv */
         448, /* glLightModeli */
         449, /* glLightModeliv */
         450, /* glLightf */
         451, /* glLightfv */
         452, /* glLighti */
         453, /* glLightiv */
         454, /* glLineStipple */
         455, /* glLineWidth */
         458, /* glListBase */
         459, /* glLoadIdentity */
         460, /* glLoadMatrixd */
         461, /* glLoadMatrixf */
         462, /* glLoadName */
         468, /* glLogicOp */
         469, /* glMap1d */
         470, /* glMap1f */
         471, /* glMap2d */
         472, /* glMap2f */
         475, /* glMapGrid1d */
         476, /* glMapGrid1f */
         477, /* glMapGrid2d */
         478, /* glMapGrid2f */
         481, /* glMaterialf */
         482, /* glMaterialfv */
         483, /* glMateriali */
         484, /* glMaterialiv */
         491, /* glMatrixMode */
         506, /* glMultMatrixd */
         507, /* glMultMatrixf */
         632, /* glNewList */
         633, /* glNormal3b */
         634, /* glNormal3bv */
         635, /* glNormal3d */
         636, /* glNormal3dv */
         637, /* glNormal3f */
         638, /* glNormal3fv */
         639, /* glNormal3i */
         640, /* glNormal3iv */
         641, /* glNormal3s */
         642, /* glNormal3sv */
         647, /* glOrtho */
         648, /* glPassThrough */
         649, /* glPixelMapfv */
         650, /* glPixelMapuiv */
         651, /* glPixelMapusv */
         652, /* glPixelStoref */
         653, /* glPixelStorei */
         654, /* glPixelTransferf */
         655, /* glPixelTransferi */
         656, /* glPixelZoom */
         669, /* glPointSize */
         670, /* glPolygonMode */
         672, /* glPolygonStipple */
         673, /* glPopAttrib */
         676, /* glPopMatrix */
         677, /* glPopName */
         745, /* glPushAttrib */
         749, /* glPushMatrix */
         750, /* glPushName */
         751, /* glRasterPos2d */
         752, /* glRasterPos2dv */
         753, /* glRasterPos2f */
         754, /* glRasterPos2fv */
         755, /* glRasterPos2i */
         756, /* glRasterPos2iv */
         757, /* glRasterPos2s */
         758, /* glRasterPos2sv */
         759, /* glRasterPos3d */
         760, /* glRasterPos3dv */
         761, /* glRasterPos3f */
         762, /* glRasterPos3fv */
         763, /* glRasterPos3i */
         764, /* glRasterPos3iv */
         765, /* glRasterPos3s */
         766, /* glRasterPos3sv */
         767, /* glRasterPos4d */
         768, /* glRasterPos4dv */
         769, /* glRasterPos4f */
         770, /* glRasterPos4fv */
         771, /* glRasterPos4i */
         772, /* glRasterPos4iv */
         773, /* glRasterPos4s */
         774, /* glRasterPos4sv */
         775, /* glReadBuffer */
         776, /* glReadPixels */
         777, /* glRectd */
         778, /* glRectdv */
         779, /* glRectf */
         780, /* glRectfv */
         781, /* glRecti */
         782, /* glRectiv */
         783, /* glRects */
         784, /* glRectsv */
         785, /* glRenderMode */
         789, /* glRotated */
         790, /* glRotatef */
         793, /* glScaled */
         794, /* glScalef */
         795, /* glScissor */
         830, /* glSelectBuffer */
         832, /* glShadeModel */
         835, /* glStencilFunc */
         838, /* glStencilMask */
         840, /* glStencilOp */
         843, /* glTexCoord1d */
         844, /* glTexCoord1dv */
         845, /* glTexCoord1f */
         846, /* glTexCoord1fv */
         847, /* glTexCoord1i */
         848, /* glTexCoord1iv */
         849, /* glTexCoord1s */
         850, /* glTexCoord1sv */
         851, /* glTexCoord2d */
         852, /* glTexCoord2dv */
         853, /* glTexCoord2f */
         854, /* glTexCoord2fv */
         855, /* glTexCoord2i */
         856, /* glTexCoord2iv */
         857, /* glTexCoord2s */
         858, /* glTexCoord2sv */
         859, /* glTexCoord3d */
         860, /* glTexCoord3dv */
         861, /* glTexCoord3f */
         862, /* glTexCoord3fv */
         863, /* glTexCoord3i */
         864, /* glTexCoord3iv */
         865, /* glTexCoord3s */
         866, /* glTexCoord3sv */
         867, /* glTexCoord4d */
         868, /* glTexCoord4dv */
         869, /* glTexCoord4f */
         870, /* glTexCoord4fv */
         871, /* glTexCoord4i */
         872, /* glTexCoord4iv */
         873, /* glTexCoord4s */
         874, /* glTexCoord4sv */
         877, /* glTexEnvf */
         878, /* glTexEnvfv */
         879, /* glTexEnvi */
         880, /* glTexEnviv */
         881, /* glTexGend */
         882, /* glTexGendv */
         883, /* glTexGenf */
         884, /* glTexGenfv */
         885, /* glTexGeni */
         886, /* glTexGeniv */
         887, /* glTexImage1D */
         888, /* glTexImage2D */
         891, /* glTexParameterf */
         892, /* glTexParameterfv */
         893, /* glTexParameteri */
         894, /* glTexParameteriv */
         926, /* glTranslated */
         927, /* glTranslatef */
         979, /* glVertex2d */
         980, /* glVertex2dv */
         981, /* glVertex2f */
         982, /* glVertex2fv */
         983, /* glVertex2i */
         984, /* glVertex2iv */
         985, /* glVertex2s */
         986, /* glVertex2sv */
         987, /* glVertex3d */
         988, /* glVertex3dv */
         989, /* glVertex3f */
         990, /* glVertex3fv */
         991, /* glVertex3i */
         992, /* glVertex3iv */
         993, /* glVertex3s */
         994, /* glVertex3sv */
         995, /* glVertex4d */
         996, /* glVertex4dv */
         997, /* glVertex4f */
         998, /* glVertex4fv */
         999, /* glVertex4i */
        1000, /* glVertex4iv */
        1001, /* glVertex4s */
        1002, /* glVertex4sv */
        1138  /* glViewport */
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
           5, /* glAreTexturesResident */
           7, /* glArrayElement */
          21, /* glBindTexture */
          88, /* glColorPointer */
         136, /* glCopyTexImage1D */
         138, /* glCopyTexImage2D */
         140, /* glCopyTexSubImage1D */
         142, /* glCopyTexSubImage2D */
         172, /* glDeleteTextures */
         180, /* glDisableClientState */
         188, /* glDrawArrays */
         194, /* glDrawElements */
         199, /* glEdgeFlagPointer */
         203, /* glEnableClientState */
         258, /* glGenTextures */
         349, /* glGetPointerv */
         419, /* glIndexPointer */
         429, /* glIndexub */
         430, /* glIndexubv */
         432, /* glInterleavedArrays */
         444, /* glIsTexture */
         643, /* glNormalPointer */
         671, /* glPolygonOffset */
         674, /* glPopClientAttrib */
         678, /* glPrioritizeTextures */
         746, /* glPushClientAttrib */
         875, /* glTexCoordPointer */
         898, /* glTexSubImage1D */
         900, /* glTexSubImage2D */
        1136  /* glVertexPointer */
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
         144, /* glCopyTexSubImage3D */
         196, /* glDrawRangeElements */
         889, /* glTexImage3D */
         902  /* glTexSubImage3D */
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
           1, /* glActiveTexture */
          50, /* glClientActiveTexture */
         102, /* glCompressedTexImage1D */
         104, /* glCompressedTexImage2D */
         106, /* glCompressedTexImage3D */
         108, /* glCompressedTexSubImage1D */
         110, /* glCompressedTexSubImage2D */
         112, /* glCompressedTexSubImage3D */
         283, /* glGetCompressedTexImage */
         464, /* glLoadTransposeMatrixd */
         466, /* glLoadTransposeMatrixf */
         508, /* glMultTransposeMatrixd */
         510, /* glMultTransposeMatrixf */
         517, /* glMultiTexCoord1d */
         519, /* glMultiTexCoord1dv */
         521, /* glMultiTexCoord1f */
         523, /* glMultiTexCoord1fv */
         525, /* glMultiTexCoord1i */
         527, /* glMultiTexCoord1iv */
         529, /* glMultiTexCoord1s */
         531, /* glMultiTexCoord1sv */
         533, /* glMultiTexCoord2d */
         535, /* glMultiTexCoord2dv */
         537, /* glMultiTexCoord2f */
         539, /* glMultiTexCoord2fv */
         541, /* glMultiTexCoord2i */
         543, /* glMultiTexCoord2iv */
         545, /* glMultiTexCoord2s */
         547, /* glMultiTexCoord2sv */
         549, /* glMultiTexCoord3d */
         551, /* glMultiTexCoord3dv */
         553, /* glMultiTexCoord3f */
         555, /* glMultiTexCoord3fv */
         557, /* glMultiTexCoord3i */
         559, /* glMultiTexCoord3iv */
         561, /* glMultiTexCoord3s */
         563, /* glMultiTexCoord3sv */
         565, /* glMultiTexCoord4d */
         567, /* glMultiTexCoord4dv */
         569, /* glMultiTexCoord4f */
         571, /* glMultiTexCoord4fv */
         573, /* glMultiTexCoord4i */
         575, /* glMultiTexCoord4iv */
         577, /* glMultiTexCoord4s */
         579, /* glMultiTexCoord4sv */
         791  /* glSampleCoverage */
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
          24, /* glBlendColor */
          26, /* glBlendEquation */
          31, /* glBlendFuncSeparate */
         232, /* glFogCoordPointer */
         234, /* glFogCoordd */
         236, /* glFogCoorddv */
         238, /* glFogCoordf */
         240, /* glFogCoordfv */
         512, /* glMultiDrawArrays */
         514, /* glMultiDrawElements */
         657, /* glPointParameterf */
         661, /* glPointParameterfv */
         665, /* glPointParameteri */
         667, /* glPointParameteriv */
         796, /* glSecondaryColor3b */
         798, /* glSecondaryColor3bv */
         800, /* glSecondaryColor3d */
         802, /* glSecondaryColor3dv */
         804, /* glSecondaryColor3f */
         806, /* glSecondaryColor3fv */
         808, /* glSecondaryColor3i */
         810, /* glSecondaryColor3iv */
         812, /* glSecondaryColor3s */
         814, /* glSecondaryColor3sv */
         816, /* glSecondaryColor3ub */
         818, /* glSecondaryColor3ubv */
         820, /* glSecondaryColor3ui */
         822, /* glSecondaryColor3uiv */
         824, /* glSecondaryColor3us */
         826, /* glSecondaryColor3usv */
         828, /* glSecondaryColorPointer */
        1139, /* glWindowPos2d */
        1142, /* glWindowPos2dv */
        1145, /* glWindowPos2f */
        1148, /* glWindowPos2fv */
        1151, /* glWindowPos2i */
        1154, /* glWindowPos2iv */
        1157, /* glWindowPos2s */
        1160, /* glWindowPos2sv */
        1163, /* glWindowPos3d */
        1166, /* glWindowPos3dv */
        1169, /* glWindowPos3f */
        1172, /* glWindowPos3fv */
        1175, /* glWindowPos3i */
        1178, /* glWindowPos3iv */
        1181, /* glWindowPos3s */
        1184  /* glWindowPos3sv */
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
          12, /* glBeginQuery */
          16, /* glBindBuffer */
          34, /* glBufferData */
          37, /* glBufferSubData */
         162, /* glDeleteBuffers */
         169, /* glDeleteQueries */
         213, /* glEndQuery */
         251, /* glGenBuffers */
         256, /* glGenQueries */
         272, /* glGetBufferParameteriv */
         274, /* glGetBufferPointerv */
         276, /* glGetBufferSubData */
         364, /* glGetQueryObjectiv */
         366, /* glGetQueryObjectuiv */
         368, /* glGetQueryiv */
         433, /* glIsBuffer */
         441, /* glIsQuery */
         473, /* glMapBuffer */
         972  /* glUnmapBuffer */
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
          10, /* glAttachShader */
          14, /* glBindAttribLocation */
          28, /* glBlendEquationSeparate */
          94, /* glCompileShader */
         151, /* glCreateProgram */
         153, /* glCreateShader */
         166, /* glDeleteProgram */
         171, /* glDeleteShader */
         178, /* glDetachShader */
         186, /* glDisableVertexAttribArray */
         191, /* glDrawBuffers */
         209, /* glEnableVertexAttribArray */
         262, /* glGetActiveAttrib */
         264, /* glGetActiveUniform */
         267, /* glGetAttachedShaders */
         268, /* glGetAttribLocation */
         354, /* glGetProgramInfoLog */
         361, /* glGetProgramiv */
         371, /* glGetShaderInfoLog */
         372, /* glGetShaderSource */
         374, /* glGetShaderiv */
         394, /* glGetUniformLocation */
         396, /* glGetUniformfv */
         398, /* glGetUniformiv */
         404, /* glGetVertexAttribPointerv */
         407, /* glGetVertexAttribdv */
         410, /* glGetVertexAttribfv */
         413, /* glGetVertexAttribiv */
         438, /* glIsProgram */
         443, /* glIsShader */
         456, /* glLinkProgram */
         833, /* glShaderSource */
         836, /* glStencilFuncSeparate */
         839, /* glStencilMaskSeparate */
         841, /* glStencilOpSeparate */
         928, /* glUniform1f */
         930, /* glUniform1fv */
         932, /* glUniform1i */
         934, /* glUniform1iv */
         936, /* glUniform2f */
         938, /* glUniform2fv */
         940, /* glUniform2i */
         942, /* glUniform2iv */
         944, /* glUniform3f */
         946, /* glUniform3fv */
         948, /* glUniform3i */
         950, /* glUniform3iv */
         952, /* glUniform4f */
         954, /* glUniform4fv */
         956, /* glUniform4i */
         958, /* glUniform4iv */
         960, /* glUniformMatrix2fv */
         964, /* glUniformMatrix3fv */
         968, /* glUniformMatrix4fv */
         975, /* glUseProgram */
         977, /* glValidateProgram */
        1022, /* glVertexAttrib1d */
        1025, /* glVertexAttrib1dv */
        1028, /* glVertexAttrib1f */
        1031, /* glVertexAttrib1fv */
        1034, /* glVertexAttrib1s */
        1037, /* glVertexAttrib1sv */
        1040, /* glVertexAttrib2d */
        1043, /* glVertexAttrib2dv */
        1046, /* glVertexAttrib2f */
        1049, /* glVertexAttrib2fv */
        1052, /* glVertexAttrib2s */
        1055, /* glVertexAttrib2sv */
        1058, /* glVertexAttrib3d */
        1061, /* glVertexAttrib3dv */
        1064, /* glVertexAttrib3f */
        1067, /* glVertexAttrib3fv */
        1070, /* glVertexAttrib3s */
        1073, /* glVertexAttrib3sv */
        1076, /* glVertexAttrib4Nbv */
        1078, /* glVertexAttrib4Niv */
        1080, /* glVertexAttrib4Nsv */
        1082, /* glVertexAttrib4Nub */
        1084, /* glVertexAttrib4Nubv */
        1086, /* glVertexAttrib4Nuiv */
        1088, /* glVertexAttrib4Nusv */
        1090, /* glVertexAttrib4bv */
        1092, /* glVertexAttrib4d */
        1095, /* glVertexAttrib4dv */
        1098, /* glVertexAttrib4f */
        1101, /* glVertexAttrib4fv */
        1104, /* glVertexAttrib4iv */
        1106, /* glVertexAttrib4s */
        1109, /* glVertexAttrib4sv */
        1113, /* glVertexAttrib4ubv */
        1116, /* glVertexAttrib4uiv */
        1118, /* glVertexAttrib4usv */
        1120  /* glVertexAttribPointer */
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
         962, /* glUniformMatrix2x3fv */
         963, /* glUniformMatrix2x4fv */
         966, /* glUniformMatrix3x2fv */
         967, /* glUniformMatrix3x4fv */
         970, /* glUniformMatrix4x2fv */
         971  /* glUniformMatrix4x3fv */
    };
    uint32_t i;
    if(!context->VERSION_2_1) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ES_VERSION_2_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           1, /* glActiveTexture */
          10, /* glAttachShader */
          14, /* glBindAttribLocation */
          16, /* glBindBuffer */
        1201, /* glBindFramebuffer */
        1205, /* glBindRenderbuffer */
          21, /* glBindTexture */
          24, /* glBlendColor */
          26, /* glBlendEquation */
          28, /* glBlendEquationSeparate */
          30, /* glBlendFunc */
          31, /* glBlendFuncSeparate */
          34, /* glBufferData */
          37, /* glBufferSubData */
        1229, /* glCheckFramebufferStatus */
          42, /* glClear */
          44, /* glClearColor */
        1234, /* glClearDepthf */
          49, /* glClearStencil */
          86, /* glColorMask */
          94, /* glCompileShader */
         104, /* glCompressedTexImage2D */
         110, /* glCompressedTexSubImage2D */
         138, /* glCopyTexImage2D */
         142, /* glCopyTexSubImage2D */
         151, /* glCreateProgram */
         153, /* glCreateShader */
         155, /* glCullFace */
         162, /* glDeleteBuffers */
        1250, /* glDeleteFramebuffers */
         166, /* glDeleteProgram */
        1254, /* glDeleteRenderbuffers */
         171, /* glDeleteShader */
         172, /* glDeleteTextures */
         174, /* glDepthFunc */
         175, /* glDepthMask */
        1265, /* glDepthRangef */
         178, /* glDetachShader */
         179, /* glDisable */
         186, /* glDisableVertexAttribArray */
         188, /* glDrawArrays */
         194, /* glDrawElements */
         202, /* glEnable */
         209, /* glEnableVertexAttribArray */
         229, /* glFinish */
         230, /* glFlush */
        1303, /* glFramebufferRenderbuffer */
        1305, /* glFramebufferTexture2D */
         249, /* glFrontFace */
         251, /* glGenBuffers */
        1310, /* glGenFramebuffers */
        1314, /* glGenRenderbuffers */
         258, /* glGenTextures */
        1319, /* glGenerateMipmap */
         262, /* glGetActiveAttrib */
         264, /* glGetActiveUniform */
         267, /* glGetAttachedShaders */
         268, /* glGetAttribLocation */
         271, /* glGetBooleanv */
         272, /* glGetBufferParameteriv */
         294, /* glGetError */
         297, /* glGetFloatv */
        1330, /* glGetFramebufferAttachmentParameteriv */
         305, /* glGetIntegerv */
         354, /* glGetProgramInfoLog */
         361, /* glGetProgramiv */
        1362, /* glGetRenderbufferParameteriv */
         371, /* glGetShaderInfoLog */
        1371, /* glGetShaderPrecisionFormat */
         372, /* glGetShaderSource */
         374, /* glGetShaderiv */
         375, /* glGetString */
         384, /* glGetTexParameterfv */
         385, /* glGetTexParameteriv */
         394, /* glGetUniformLocation */
         396, /* glGetUniformfv */
         398, /* glGetUniformiv */
         404, /* glGetVertexAttribPointerv */
         410, /* glGetVertexAttribfv */
         413, /* glGetVertexAttribiv */
         416, /* glHint */
         433, /* glIsBuffer */
         435, /* glIsEnabled */
        1403, /* glIsFramebuffer */
         438, /* glIsProgram */
        1407, /* glIsRenderbuffer */
         443, /* glIsShader */
         444, /* glIsTexture */
         455, /* glLineWidth */
         456, /* glLinkProgram */
         653, /* glPixelStorei */
         671, /* glPolygonOffset */
         776, /* glReadPixels */
        1474, /* glReleaseShaderCompiler */
        1475, /* glRenderbufferStorage */
         791, /* glSampleCoverage */
         795, /* glScissor */
        1498, /* glShaderBinary */
         833, /* glShaderSource */
         835, /* glStencilFunc */
         836, /* glStencilFuncSeparate */
         838, /* glStencilMask */
         839, /* glStencilMaskSeparate */
         840, /* glStencilOp */
         841, /* glStencilOpSeparate */
         888, /* glTexImage2D */
         891, /* glTexParameterf */
         892, /* glTexParameterfv */
         893, /* glTexParameteri */
         894, /* glTexParameteriv */
         900, /* glTexSubImage2D */
         928, /* glUniform1f */
         930, /* glUniform1fv */
         932, /* glUniform1i */
         934, /* glUniform1iv */
         936, /* glUniform2f */
         938, /* glUniform2fv */
         940, /* glUniform2i */
         942, /* glUniform2iv */
         944, /* glUniform3f */
         946, /* glUniform3fv */
         948, /* glUniform3i */
         950, /* glUniform3iv */
         952, /* glUniform4f */
         954, /* glUniform4fv */
         956, /* glUniform4i */
         958, /* glUniform4iv */
         960, /* glUniformMatrix2fv */
         964, /* glUniformMatrix3fv */
         968, /* glUniformMatrix4fv */
         975, /* glUseProgram */
         977, /* glValidateProgram */
        1028, /* glVertexAttrib1f */
        1031, /* glVertexAttrib1fv */
        1046, /* glVertexAttrib2f */
        1049, /* glVertexAttrib2fv */
        1064, /* glVertexAttrib3f */
        1067, /* glVertexAttrib3fv */
        1098, /* glVertexAttrib4f */
        1101, /* glVertexAttrib4fv */
        1120, /* glVertexAttribPointer */
        1138  /* glViewport */
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
          12, /* glBeginQuery */
        1198, /* glBeginTransformFeedback */
        1199, /* glBindBufferBase */
        1200, /* glBindBufferRange */
        1206, /* glBindSampler */
        1207, /* glBindTransformFeedback */
        1208, /* glBindVertexArray */
        1227, /* glBlitFramebuffer */
        1230, /* glClearBufferfi */
        1231, /* glClearBufferfv */
        1232, /* glClearBufferiv */
        1233, /* glClearBufferuiv */
        1235, /* glClientWaitSync */
         106, /* glCompressedTexImage3D */
         112, /* glCompressedTexSubImage3D */
        1240, /* glCopyBufferSubData */
         144, /* glCopyTexSubImage3D */
         169, /* glDeleteQueries */
        1255, /* glDeleteSamplers */
        1256, /* glDeleteSync */
        1258, /* glDeleteTransformFeedbacks */
        1259, /* glDeleteVertexArrays */
        1273, /* glDrawArraysInstanced */
         191, /* glDrawBuffers */
        1282, /* glDrawElementsInstanced */
         196, /* glDrawRangeElements */
         213, /* glEndQuery */
        1297, /* glEndTransformFeedback */
        1298, /* glFenceSync */
        1300, /* glFlushMappedBufferRange */
        1308, /* glFramebufferTextureLayer */
         256, /* glGenQueries */
        1315, /* glGenSamplers */
        1316, /* glGenTransformFeedbacks */
        1317, /* glGenVertexArrays */
        1320, /* glGetActiveUniformBlockName */
        1321, /* glGetActiveUniformBlockiv */
        1322, /* glGetActiveUniformsiv */
        1324, /* glGetBufferParameteri64v */
         274, /* glGetBufferPointerv */
        1329, /* glGetFragDataLocation */
        1335, /* glGetInteger64i_v */
        1336, /* glGetInteger64v */
        1339, /* glGetIntegeri_v */
        1340, /* glGetInternalformativ */
        1346, /* glGetProgramBinary */
         366, /* glGetQueryObjectuiv */
         368, /* glGetQueryiv */
        1369, /* glGetSamplerParameterfv */
        1370, /* glGetSamplerParameteriv */
        1372, /* glGetStringi */
        1373, /* glGetSynciv */
        1383, /* glGetTransformFeedbackVarying */
        1384, /* glGetUniformBlockIndex */
        1385, /* glGetUniformIndices */
        1386, /* glGetUniformuiv */
        1387, /* glGetVertexAttribIiv */
        1388, /* glGetVertexAttribIuiv */
        1397, /* glInvalidateFramebuffer */
        1398, /* glInvalidateSubFramebuffer */
         441, /* glIsQuery */
        1408, /* glIsSampler */
        1409, /* glIsSync */
        1411, /* glIsTransformFeedback */
        1412, /* glIsVertexArray */
        1415, /* glMapBufferRange */
        1427, /* glPauseTransformFeedback */
        1432, /* glProgramBinary */
        1434, /* glProgramParameteri */
         775, /* glReadBuffer */
        1476, /* glRenderbufferStorageMultisample */
        1479, /* glResumeTransformFeedback */
        1488, /* glSamplerParameterf */
        1489, /* glSamplerParameterfv */
        1490, /* glSamplerParameteri */
        1491, /* glSamplerParameteriv */
         889, /* glTexImage3D */
        1511, /* glTexStorage2D */
        1514, /* glTexStorage3D */
         902, /* glTexSubImage3D */
        1517, /* glTransformFeedbackVaryings */
        1518, /* glUniform1ui */
        1519, /* glUniform1uiv */
        1520, /* glUniform2ui */
        1521, /* glUniform2uiv */
        1522, /* glUniform3ui */
        1523, /* glUniform3uiv */
        1524, /* glUniform4ui */
        1525, /* glUniform4uiv */
        1526, /* glUniformBlockBinding */
         962, /* glUniformMatrix2x3fv */
         963, /* glUniformMatrix2x4fv */
         966, /* glUniformMatrix3x2fv */
         967, /* glUniformMatrix3x4fv */
         970, /* glUniformMatrix4x2fv */
         971, /* glUniformMatrix4x3fv */
         972, /* glUnmapBuffer */
        1539, /* glVertexAttribDivisor */
        1544, /* glVertexAttribI4i */
        1545, /* glVertexAttribI4iv */
        1546, /* glVertexAttribI4ui */
        1547, /* glVertexAttribI4uiv */
        1549, /* glVertexAttribIPointer */
        1557  /* glWaitSync */
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
        1195, /* glActiveShaderProgram */
        1202, /* glBindImageTexture */
        1203, /* glBindProgramPipeline */
        1210, /* glBindVertexBuffer */
        1245, /* glCreateShaderProgramv */
        1251, /* glDeleteProgramPipelines */
        1270, /* glDispatchCompute */
        1271, /* glDispatchComputeIndirect */
        1272, /* glDrawArraysIndirect */
        1281, /* glDrawElementsIndirect */
        1302, /* glFramebufferParameteri */
        1311, /* glGenProgramPipelines */
        1323, /* glGetBooleani_v */
        1331, /* glGetFramebufferParameteriv */
        1341, /* glGetMultisamplefv */
        1348, /* glGetProgramInterfaceiv */
        1349, /* glGetProgramPipelineInfoLog */
        1351, /* glGetProgramPipelineiv */
        1353, /* glGetProgramResourceIndex */
        1354, /* glGetProgramResourceLocation */
        1355, /* glGetProgramResourceName */
        1356, /* glGetProgramResourceiv */
         382, /* glGetTexLevelParameterfv */
         383, /* glGetTexLevelParameteriv */
        1404, /* glIsProgramPipeline */
        1417, /* glMemoryBarrier */
        1418, /* glMemoryBarrierByRegion */
        1436, /* glProgramUniform1f */
        1437, /* glProgramUniform1fv */
        1438, /* glProgramUniform1i */
        1439, /* glProgramUniform1iv */
        1440, /* glProgramUniform1ui */
        1441, /* glProgramUniform1uiv */
        1442, /* glProgramUniform2f */
        1443, /* glProgramUniform2fv */
        1444, /* glProgramUniform2i */
        1445, /* glProgramUniform2iv */
        1446, /* glProgramUniform2ui */
        1447, /* glProgramUniform2uiv */
        1448, /* glProgramUniform3f */
        1449, /* glProgramUniform3fv */
        1450, /* glProgramUniform3i */
        1451, /* glProgramUniform3iv */
        1452, /* glProgramUniform3ui */
        1453, /* glProgramUniform3uiv */
        1454, /* glProgramUniform4f */
        1455, /* glProgramUniform4fv */
        1456, /* glProgramUniform4i */
        1457, /* glProgramUniform4iv */
        1458, /* glProgramUniform4ui */
        1459, /* glProgramUniform4uiv */
        1460, /* glProgramUniformMatrix2fv */
        1461, /* glProgramUniformMatrix2x3fv */
        1462, /* glProgramUniformMatrix2x4fv */
        1463, /* glProgramUniformMatrix3fv */
        1464, /* glProgramUniformMatrix3x2fv */
        1465, /* glProgramUniformMatrix3x4fv */
        1466, /* glProgramUniformMatrix4fv */
        1467, /* glProgramUniformMatrix4x2fv */
        1468, /* glProgramUniformMatrix4x3fv */
        1480, /* glSampleMaski */
        1512, /* glTexStorage2DMultisample */
        1534, /* glUseProgramStages */
        1536, /* glValidateProgramPipeline */
        1538, /* glVertexAttribBinding */
        1543, /* glVertexAttribFormat */
        1548, /* glVertexAttribIFormat */
        1550  /* glVertexBindingDivisor */
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
        1211, /* glBlendBarrier */
        1214, /* glBlendEquationSeparatei */
        1217, /* glBlendEquationi */
        1220, /* glBlendFuncSeparatei */
        1223, /* glBlendFunci */
        1237, /* glColorMaski */
        1242, /* glCopyImageSubData */
         156, /* glDebugMessageCallback */
         158, /* glDebugMessageControl */
         160, /* glDebugMessageInsert */
        1266, /* glDisablei */
        1278, /* glDrawElementsBaseVertex */
        1284, /* glDrawElementsInstancedBaseVertex */
        1289, /* glDrawRangeElementsBaseVertex */
        1292, /* glEnablei */
        1304, /* glFramebufferTexture */
         289, /* glGetDebugMessageLog */
        1332, /* glGetGraphicsResetStatus */
         340, /* glGetObjectLabel */
         343, /* glGetObjectPtrLabel */
         349, /* glGetPointerv */
        1363, /* glGetSamplerParameterIiv */
        1366, /* glGetSamplerParameterIuiv */
        1377, /* glGetTexParameterIiv */
        1380, /* glGetTexParameterIuiv */
        1389, /* glGetnUniformfv */
        1392, /* glGetnUniformiv */
        1395, /* glGetnUniformuiv */
        1399, /* glIsEnabledi */
        1419, /* glMinSampleShading */
         645, /* glObjectLabel */
         646, /* glObjectPtrLabel */
        1424, /* glPatchParameteri */
         675, /* glPopDebugGroup */
        1429, /* glPrimitiveBoundingBox */
         748, /* glPushDebugGroup */
        1471, /* glReadnPixels */
        1482, /* glSamplerParameterIiv */
        1485, /* glSamplerParameterIuiv */
        1499, /* glTexBuffer */
        1502, /* glTexBufferRange */
        1505, /* glTexParameterIiv */
        1508, /* glTexParameterIuiv */
        1515  /* glTexStorage3DMultisample */
    };
    uint32_t i;
    if(!context->ES_VERSION_3_2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_get_tex_level_parameter(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1375, /* glGetTexLevelParameterfvANGLE */
        1376  /* glGetTexLevelParameterivANGLE */
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
        1274, /* glDrawArraysInstancedANGLE */
        1283, /* glDrawElementsInstancedANGLE */
        1540  /* glVertexAttribDivisorANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_instanced_arrays) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_texture_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1342, /* glGetMultisamplefvANGLE */
        1375, /* glGetTexLevelParameterfvANGLE */
        1376, /* glGetTexLevelParameterivANGLE */
        1481, /* glSampleMaskiANGLE */
        1513  /* glTexStorage2DMultisampleANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_texture_multisample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_sync(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1236, /* glClientWaitSyncAPPLE */
        1257, /* glDeleteSyncAPPLE */
        1299, /* glFenceSyncAPPLE */
        1337, /* glGetInteger64vAPPLE */
        1374, /* glGetSyncivAPPLE */
        1410, /* glIsSyncAPPLE */
        1558  /* glWaitSyncAPPLE */
    };
    uint32_t i;
    if(!context->APPLE_sync) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_buffer_storage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          36  /* glBufferStorage */
    };
    uint32_t i;
    if(!context->ARB_buffer_storage) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_debug_output(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         157, /* glDebugMessageCallbackARB */
         159, /* glDebugMessageControlARB */
         161, /* glDebugMessageInsertARB */
         290  /* glGetDebugMessageLogARB */
    };
    uint32_t i;
    if(!context->ARB_debug_output) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_draw_buffers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         192  /* glDrawBuffersARB */
    };
    uint32_t i;
    if(!context->ARB_draw_buffers) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_imaging(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          24, /* glBlendColor */
          26, /* glBlendEquation */
          90, /* glColorSubTable */
          91, /* glColorTable */
          92, /* glColorTableParameterfv */
          93, /* glColorTableParameteriv */
         120, /* glConvolutionFilter1D */
         121, /* glConvolutionFilter2D */
         122, /* glConvolutionParameterf */
         123, /* glConvolutionParameterfv */
         124, /* glConvolutionParameteri */
         125, /* glConvolutionParameteriv */
         126, /* glCopyColorSubTable */
         127, /* glCopyColorTable */
         128, /* glCopyConvolutionFilter1D */
         129, /* glCopyConvolutionFilter2D */
         279, /* glGetColorTable */
         280, /* glGetColorTableParameterfv */
         281, /* glGetColorTableParameteriv */
         286, /* glGetConvolutionFilter */
         287, /* glGetConvolutionParameterfv */
         288, /* glGetConvolutionParameteriv */
         300, /* glGetHistogram */
         301, /* glGetHistogramParameterfv */
         302, /* glGetHistogramParameteriv */
         313, /* glGetMinmax */
         314, /* glGetMinmaxParameterfv */
         315, /* glGetMinmaxParameteriv */
         370, /* glGetSeparableFilter */
         417, /* glHistogram */
         505, /* glMinmax */
         787, /* glResetHistogram */
         788, /* glResetMinmax */
         831  /* glSeparableFilter2D */
    };
    uint32_t i;
    if(!context->ARB_imaging) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         792  /* glSampleCoverageARB */
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
           2, /* glActiveTextureARB */
          51, /* glClientActiveTextureARB */
         518, /* glMultiTexCoord1dARB */
         520, /* glMultiTexCoord1dvARB */
         522, /* glMultiTexCoord1fARB */
         524, /* glMultiTexCoord1fvARB */
         526, /* glMultiTexCoord1iARB */
         528, /* glMultiTexCoord1ivARB */
         530, /* glMultiTexCoord1sARB */
         532, /* glMultiTexCoord1svARB */
         534, /* glMultiTexCoord2dARB */
         536, /* glMultiTexCoord2dvARB */
         538, /* glMultiTexCoord2fARB */
         540, /* glMultiTexCoord2fvARB */
         542, /* glMultiTexCoord2iARB */
         544, /* glMultiTexCoord2ivARB */
         546, /* glMultiTexCoord2sARB */
         548, /* glMultiTexCoord2svARB */
         550, /* glMultiTexCoord3dARB */
         552, /* glMultiTexCoord3dvARB */
         554, /* glMultiTexCoord3fARB */
         556, /* glMultiTexCoord3fvARB */
         558, /* glMultiTexCoord3iARB */
         560, /* glMultiTexCoord3ivARB */
         562, /* glMultiTexCoord3sARB */
         564, /* glMultiTexCoord3svARB */
         566, /* glMultiTexCoord4dARB */
         568, /* glMultiTexCoord4dvARB */
         570, /* glMultiTexCoord4fARB */
         572, /* glMultiTexCoord4fvARB */
         574, /* glMultiTexCoord4iARB */
         576, /* glMultiTexCoord4ivARB */
         578, /* glMultiTexCoord4sARB */
         580  /* glMultiTexCoord4svARB */
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
          13, /* glBeginQueryARB */
         170, /* glDeleteQueriesARB */
         214, /* glEndQueryARB */
         257, /* glGenQueriesARB */
         365, /* glGetQueryObjectivARB */
         367, /* glGetQueryObjectuivARB */
         369, /* glGetQueryivARB */
         442  /* glIsQueryARB */
    };
    uint32_t i;
    if(!context->ARB_occlusion_query) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_point_parameters(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         658, /* glPointParameterfARB */
         662  /* glPointParameterfvARB */
    };
    uint32_t i;
    if(!context->ARB_point_parameters) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_shader_objects(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           9, /* glAttachObjectARB */
          95, /* glCompileShaderARB */
         152, /* glCreateProgramObjectARB */
         154, /* glCreateShaderObjectARB */
         165, /* glDeleteObjectARB */
         177, /* glDetachObjectARB */
         265, /* glGetActiveUniformARB */
         266, /* glGetAttachedObjectsARB */
         299, /* glGetHandleARB */
         303, /* glGetInfoLogARB */
         341, /* glGetObjectParameterfvARB */
         342, /* glGetObjectParameterivARB */
         373, /* glGetShaderSourceARB */
         395, /* glGetUniformLocationARB */
         397, /* glGetUniformfvARB */
         399, /* glGetUniformivARB */
         457, /* glLinkProgramARB */
         834, /* glShaderSourceARB */
         929, /* glUniform1fARB */
         931, /* glUniform1fvARB */
         933, /* glUniform1iARB */
         935, /* glUniform1ivARB */
         937, /* glUniform2fARB */
         939, /* glUniform2fvARB */
         941, /* glUniform2iARB */
         943, /* glUniform2ivARB */
         945, /* glUniform3fARB */
         947, /* glUniform3fvARB */
         949, /* glUniform3iARB */
         951, /* glUniform3ivARB */
         953, /* glUniform4fARB */
         955, /* glUniform4fvARB */
         957, /* glUniform4iARB */
         959, /* glUniform4ivARB */
         961, /* glUniformMatrix2fvARB */
         965, /* glUniformMatrix3fvARB */
         969, /* glUniformMatrix4fvARB */
         976, /* glUseProgramObjectARB */
         978  /* glValidateProgramARB */
    };
    uint32_t i;
    if(!context->ARB_shader_objects) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_texture_compression(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         103, /* glCompressedTexImage1DARB */
         105, /* glCompressedTexImage2DARB */
         107, /* glCompressedTexImage3DARB */
         109, /* glCompressedTexSubImage1DARB */
         111, /* glCompressedTexSubImage2DARB */
         113, /* glCompressedTexSubImage3DARB */
         284  /* glGetCompressedTexImageARB */
    };
    uint32_t i;
    if(!context->ARB_texture_compression) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_transpose_matrix(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         465, /* glLoadTransposeMatrixdARB */
         467, /* glLoadTransposeMatrixfARB */
         509, /* glMultTransposeMatrixdARB */
         511  /* glMultTransposeMatrixfARB */
    };
    uint32_t i;
    if(!context->ARB_transpose_matrix) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          17, /* glBindBufferARB */
          35, /* glBufferDataARB */
          38, /* glBufferSubDataARB */
         163, /* glDeleteBuffersARB */
         252, /* glGenBuffersARB */
         273, /* glGetBufferParameterivARB */
         275, /* glGetBufferPointervARB */
         277, /* glGetBufferSubDataARB */
         434, /* glIsBufferARB */
         474, /* glMapBufferARB */
         973  /* glUnmapBufferARB */
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
          19, /* glBindProgramARB */
         167, /* glDeleteProgramsARB */
         187, /* glDisableVertexAttribArrayARB */
         210, /* glEnableVertexAttribArrayARB */
         254, /* glGenProgramsARB */
         352, /* glGetProgramEnvParameterdvARB */
         353, /* glGetProgramEnvParameterfvARB */
         355, /* glGetProgramLocalParameterdvARB */
         356, /* glGetProgramLocalParameterfvARB */
         359, /* glGetProgramStringARB */
         362, /* glGetProgramivARB */
         405, /* glGetVertexAttribPointervARB */
         408, /* glGetVertexAttribdvARB */
         411, /* glGetVertexAttribfvARB */
         414, /* glGetVertexAttribivARB */
         439, /* glIsProgramARB */
         680, /* glProgramEnvParameter4dARB */
         681, /* glProgramEnvParameter4dvARB */
         682, /* glProgramEnvParameter4fARB */
         683, /* glProgramEnvParameter4fvARB */
         684, /* glProgramLocalParameter4dARB */
         685, /* glProgramLocalParameter4dvARB */
         686, /* glProgramLocalParameter4fARB */
         687, /* glProgramLocalParameter4fvARB */
         694, /* glProgramStringARB */
        1023, /* glVertexAttrib1dARB */
        1026, /* glVertexAttrib1dvARB */
        1029, /* glVertexAttrib1fARB */
        1032, /* glVertexAttrib1fvARB */
        1035, /* glVertexAttrib1sARB */
        1038, /* glVertexAttrib1svARB */
        1041, /* glVertexAttrib2dARB */
        1044, /* glVertexAttrib2dvARB */
        1047, /* glVertexAttrib2fARB */
        1050, /* glVertexAttrib2fvARB */
        1053, /* glVertexAttrib2sARB */
        1056, /* glVertexAttrib2svARB */
        1059, /* glVertexAttrib3dARB */
        1062, /* glVertexAttrib3dvARB */
        1065, /* glVertexAttrib3fARB */
        1068, /* glVertexAttrib3fvARB */
        1071, /* glVertexAttrib3sARB */
        1074, /* glVertexAttrib3svARB */
        1077, /* glVertexAttrib4NbvARB */
        1079, /* glVertexAttrib4NivARB */
        1081, /* glVertexAttrib4NsvARB */
        1083, /* glVertexAttrib4NubARB */
        1085, /* glVertexAttrib4NubvARB */
        1087, /* glVertexAttrib4NuivARB */
        1089, /* glVertexAttrib4NusvARB */
        1091, /* glVertexAttrib4bvARB */
        1093, /* glVertexAttrib4dARB */
        1096, /* glVertexAttrib4dvARB */
        1099, /* glVertexAttrib4fARB */
        1102, /* glVertexAttrib4fvARB */
        1105, /* glVertexAttrib4ivARB */
        1107, /* glVertexAttrib4sARB */
        1110, /* glVertexAttrib4svARB */
        1114, /* glVertexAttrib4ubvARB */
        1117, /* glVertexAttrib4uivARB */
        1119, /* glVertexAttrib4usvARB */
        1121  /* glVertexAttribPointerARB */
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
          15, /* glBindAttribLocationARB */
         187, /* glDisableVertexAttribArrayARB */
         210, /* glEnableVertexAttribArrayARB */
         263, /* glGetActiveAttribARB */
         269, /* glGetAttribLocationARB */
         405, /* glGetVertexAttribPointervARB */
         408, /* glGetVertexAttribdvARB */
         411, /* glGetVertexAttribfvARB */
         414, /* glGetVertexAttribivARB */
        1023, /* glVertexAttrib1dARB */
        1026, /* glVertexAttrib1dvARB */
        1029, /* glVertexAttrib1fARB */
        1032, /* glVertexAttrib1fvARB */
        1035, /* glVertexAttrib1sARB */
        1038, /* glVertexAttrib1svARB */
        1041, /* glVertexAttrib2dARB */
        1044, /* glVertexAttrib2dvARB */
        1047, /* glVertexAttrib2fARB */
        1050, /* glVertexAttrib2fvARB */
        1053, /* glVertexAttrib2sARB */
        1056, /* glVertexAttrib2svARB */
        1059, /* glVertexAttrib3dARB */
        1062, /* glVertexAttrib3dvARB */
        1065, /* glVertexAttrib3fARB */
        1068, /* glVertexAttrib3fvARB */
        1071, /* glVertexAttrib3sARB */
        1074, /* glVertexAttrib3svARB */
        1077, /* glVertexAttrib4NbvARB */
        1079, /* glVertexAttrib4NivARB */
        1081, /* glVertexAttrib4NsvARB */
        1083, /* glVertexAttrib4NubARB */
        1085, /* glVertexAttrib4NubvARB */
        1087, /* glVertexAttrib4NuivARB */
        1089, /* glVertexAttrib4NusvARB */
        1091, /* glVertexAttrib4bvARB */
        1093, /* glVertexAttrib4dARB */
        1096, /* glVertexAttrib4dvARB */
        1099, /* glVertexAttrib4fARB */
        1102, /* glVertexAttrib4fvARB */
        1105, /* glVertexAttrib4ivARB */
        1107, /* glVertexAttrib4sARB */
        1110, /* glVertexAttrib4svARB */
        1114, /* glVertexAttrib4ubvARB */
        1117, /* glVertexAttrib4uivARB */
        1119, /* glVertexAttrib4usvARB */
        1121  /* glVertexAttribPointerARB */
    };
    uint32_t i;
    if(!context->ARB_vertex_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_window_pos(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1140, /* glWindowPos2dARB */
        1143, /* glWindowPos2dvARB */
        1146, /* glWindowPos2fARB */
        1149, /* glWindowPos2fvARB */
        1152, /* glWindowPos2iARB */
        1155, /* glWindowPos2ivARB */
        1158, /* glWindowPos2sARB */
        1161, /* glWindowPos2svARB */
        1164, /* glWindowPos3dARB */
        1167, /* glWindowPos3dvARB */
        1170, /* glWindowPos3fARB */
        1173, /* glWindowPos3fvARB */
        1176, /* glWindowPos3iARB */
        1179, /* glWindowPos3ivARB */
        1182, /* glWindowPos3sARB */
        1185  /* glWindowPos3svARB */
    };
    uint32_t i;
    if(!context->ARB_window_pos) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_draw_buffers(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         193  /* glDrawBuffersATI */
    };
    uint32_t i;
    if(!context->ATI_draw_buffers) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ATI_separate_stencil(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         837, /* glStencilFuncSeparateATI */
         842  /* glStencilOpSeparateATI */
    };
    uint32_t i;
    if(!context->ATI_separate_stencil) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_blend_color(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          25  /* glBlendColorEXT */
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
          29  /* glBlendEquationSeparateEXT */
    };
    uint32_t i;
    if(!context->EXT_blend_equation_separate) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_blend_func_separate(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          32  /* glBlendFuncSeparateEXT */
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
          27  /* glBlendEquationEXT */
    };
    uint32_t i;
    if(!context->EXT_blend_minmax) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_copy_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1243  /* glCopyImageSubDataEXT */
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
         137, /* glCopyTexImage1DEXT */
         139, /* glCopyTexImage2DEXT */
         141, /* glCopyTexSubImage1DEXT */
         143, /* glCopyTexSubImage2DEXT */
         145  /* glCopyTexSubImage3DEXT */
    };
    uint32_t i;
    if(!context->EXT_copy_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_direct_state_access(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          18, /* glBindMultiTextureEXT */
          41, /* glCheckNamedFramebufferStatusEXT */
          47, /* glClearNamedBufferDataEXT */
          48, /* glClearNamedBufferSubDataEXT */
          52, /* glClientAttribDefaultEXT */
          96, /* glCompressedMultiTexImage1DEXT */
          97, /* glCompressedMultiTexImage2DEXT */
          98, /* glCompressedMultiTexImage3DEXT */
          99, /* glCompressedMultiTexSubImage1DEXT */
         100, /* glCompressedMultiTexSubImage2DEXT */
         101, /* glCompressedMultiTexSubImage3DEXT */
         114, /* glCompressedTextureImage1DEXT */
         115, /* glCompressedTextureImage2DEXT */
         116, /* glCompressedTextureImage3DEXT */
         117, /* glCompressedTextureSubImage1DEXT */
         118, /* glCompressedTextureSubImage2DEXT */
         119, /* glCompressedTextureSubImage3DEXT */
         130, /* glCopyMultiTexImage1DEXT */
         131, /* glCopyMultiTexImage2DEXT */
         132, /* glCopyMultiTexSubImage1DEXT */
         133, /* glCopyMultiTexSubImage2DEXT */
         134, /* glCopyMultiTexSubImage3DEXT */
         146, /* glCopyTextureImage1DEXT */
         147, /* glCopyTextureImage2DEXT */
         148, /* glCopyTextureSubImage1DEXT */
         149, /* glCopyTextureSubImage2DEXT */
         150, /* glCopyTextureSubImage3DEXT */
         181, /* glDisableClientStateIndexedEXT */
         182, /* glDisableClientStateiEXT */
         183, /* glDisableIndexedEXT */
         184, /* glDisableVertexArrayAttribEXT */
         185, /* glDisableVertexArrayEXT */
         204, /* glEnableClientStateIndexedEXT */
         205, /* glEnableClientStateiEXT */
         206, /* glEnableIndexedEXT */
         207, /* glEnableVertexArrayAttribEXT */
         208, /* glEnableVertexArrayEXT */
         231, /* glFlushMappedNamedBufferRangeEXT */
         246, /* glFramebufferDrawBufferEXT */
         247, /* glFramebufferDrawBuffersEXT */
         248, /* glFramebufferReadBufferEXT */
         260, /* glGenerateMultiTexMipmapEXT */
         261, /* glGenerateTextureMipmapEXT */
         270, /* glGetBooleanIndexedvEXT */
         282, /* glGetCompressedMultiTexImageEXT */
         285, /* glGetCompressedTextureImageEXT */
         291, /* glGetDoubleIndexedvEXT */
         292, /* glGetDoublei_vEXT */
         295, /* glGetFloatIndexedvEXT */
         296, /* glGetFloati_vEXT */
         298, /* glGetFramebufferParameterivEXT */
         304, /* glGetIntegerIndexedvEXT */
         316, /* glGetMultiTexEnvfvEXT */
         317, /* glGetMultiTexEnvivEXT */
         318, /* glGetMultiTexGendvEXT */
         319, /* glGetMultiTexGenfvEXT */
         320, /* glGetMultiTexGenivEXT */
         321, /* glGetMultiTexImageEXT */
         322, /* glGetMultiTexLevelParameterfvEXT */
         323, /* glGetMultiTexLevelParameterivEXT */
         324, /* glGetMultiTexParameterIivEXT */
         325, /* glGetMultiTexParameterIuivEXT */
         326, /* glGetMultiTexParameterfvEXT */
         327, /* glGetMultiTexParameterivEXT */
         328, /* glGetNamedBufferParameterivEXT */
         329, /* glGetNamedBufferPointervEXT */
         330, /* glGetNamedBufferSubDataEXT */
         331, /* glGetNamedFramebufferAttachmentParameterivEXT */
         332, /* glGetNamedFramebufferParameterivEXT */
         333, /* glGetNamedProgramLocalParameterIivEXT */
         334, /* glGetNamedProgramLocalParameterIuivEXT */
         335, /* glGetNamedProgramLocalParameterdvEXT */
         336, /* glGetNamedProgramLocalParameterfvEXT */
         337, /* glGetNamedProgramStringEXT */
         338, /* glGetNamedProgramivEXT */
         339, /* glGetNamedRenderbufferParameterivEXT */
         347, /* glGetPointerIndexedvEXT */
         348, /* glGetPointeri_vEXT */
         386, /* glGetTextureImageEXT */
         387, /* glGetTextureLevelParameterfvEXT */
         388, /* glGetTextureLevelParameterivEXT */
         389, /* glGetTextureParameterIivEXT */
         390, /* glGetTextureParameterIuivEXT */
         391, /* glGetTextureParameterfvEXT */
         392, /* glGetTextureParameterivEXT */
         400, /* glGetVertexArrayIntegeri_vEXT */
         401, /* glGetVertexArrayIntegervEXT */
         402, /* glGetVertexArrayPointeri_vEXT */
         403, /* glGetVertexArrayPointervEXT */
         436, /* glIsEnabledIndexedEXT */
         479, /* glMapNamedBufferEXT */
         480, /* glMapNamedBufferRangeEXT */
         485, /* glMatrixFrustumEXT */
         486, /* glMatrixLoadIdentityEXT */
         487, /* glMatrixLoadTransposedEXT */
         488, /* glMatrixLoadTransposefEXT */
         489, /* glMatrixLoaddEXT */
         490, /* glMatrixLoadfEXT */
         492, /* glMatrixMultTransposedEXT */
         493, /* glMatrixMultTransposefEXT */
         494, /* glMatrixMultdEXT */
         495, /* glMatrixMultfEXT */
         496, /* glMatrixOrthoEXT */
         497, /* glMatrixPopEXT */
         498, /* glMatrixPushEXT */
         499, /* glMatrixRotatedEXT */
         500, /* glMatrixRotatefEXT */
         501, /* glMatrixScaledEXT */
         502, /* glMatrixScalefEXT */
         503, /* glMatrixTranslatedEXT */
         504, /* glMatrixTranslatefEXT */
         516, /* glMultiTexBufferEXT */
         581, /* glMultiTexCoordPointerEXT */
         582, /* glMultiTexEnvfEXT */
         583, /* glMultiTexEnvfvEXT */
         584, /* glMultiTexEnviEXT */
         585, /* glMultiTexEnvivEXT */
         586, /* glMultiTexGendEXT */
         587, /* glMultiTexGendvEXT */
         588, /* glMultiTexGenfEXT */
         589, /* glMultiTexGenfvEXT */
         590, /* glMultiTexGeniEXT */
         591, /* glMultiTexGenivEXT */
         592, /* glMultiTexImage1DEXT */
         593, /* glMultiTexImage2DEXT */
         594, /* glMultiTexImage3DEXT */
         595, /* glMultiTexParameterIivEXT */
         596, /* glMultiTexParameterIuivEXT */
         597, /* glMultiTexParameterfEXT */
         598, /* glMultiTexParameterfvEXT */
         599, /* glMultiTexParameteriEXT */
         600, /* glMultiTexParameterivEXT */
         601, /* glMultiTexRenderbufferEXT */
         602, /* glMultiTexSubImage1DEXT */
         603, /* glMultiTexSubImage2DEXT */
         604, /* glMultiTexSubImage3DEXT */
         605, /* glNamedBufferDataEXT */
         606, /* glNamedBufferStorageEXT */
         607, /* glNamedBufferSubDataEXT */
         608, /* glNamedCopyBufferSubDataEXT */
         609, /* glNamedFramebufferParameteriEXT */
         610, /* glNamedFramebufferRenderbufferEXT */
         611, /* glNamedFramebufferTexture1DEXT */
         612, /* glNamedFramebufferTexture2DEXT */
         613, /* glNamedFramebufferTexture3DEXT */
         614, /* glNamedFramebufferTextureEXT */
         615, /* glNamedFramebufferTextureFaceEXT */
         616, /* glNamedFramebufferTextureLayerEXT */
         617, /* glNamedProgramLocalParameter4dEXT */
         618, /* glNamedProgramLocalParameter4dvEXT */
         619, /* glNamedProgramLocalParameter4fEXT */
         620, /* glNamedProgramLocalParameter4fvEXT */
         621, /* glNamedProgramLocalParameterI4iEXT */
         622, /* glNamedProgramLocalParameterI4ivEXT */
         623, /* glNamedProgramLocalParameterI4uiEXT */
         624, /* glNamedProgramLocalParameterI4uivEXT */
         625, /* glNamedProgramLocalParameters4fvEXT */
         626, /* glNamedProgramLocalParametersI4ivEXT */
         627, /* glNamedProgramLocalParametersI4uivEXT */
         628, /* glNamedProgramStringEXT */
         629, /* glNamedRenderbufferStorageEXT */
         630, /* glNamedRenderbufferStorageMultisampleCoverageEXT */
         631, /* glNamedRenderbufferStorageMultisampleEXT */
         695, /* glProgramUniform1dEXT */
         696, /* glProgramUniform1dvEXT */
         697, /* glProgramUniform1fEXT */
         698, /* glProgramUniform1fvEXT */
         699, /* glProgramUniform1iEXT */
         700, /* glProgramUniform1ivEXT */
         701, /* glProgramUniform1uiEXT */
         702, /* glProgramUniform1uivEXT */
         703, /* glProgramUniform2dEXT */
         704, /* glProgramUniform2dvEXT */
         705, /* glProgramUniform2fEXT */
         706, /* glProgramUniform2fvEXT */
         707, /* glProgramUniform2iEXT */
         708, /* glProgramUniform2ivEXT */
         709, /* glProgramUniform2uiEXT */
         710, /* glProgramUniform2uivEXT */
         711, /* glProgramUniform3dEXT */
         712, /* glProgramUniform3dvEXT */
         713, /* glProgramUniform3fEXT */
         714, /* glProgramUniform3fvEXT */
         715, /* glProgramUniform3iEXT */
         716, /* glProgramUniform3ivEXT */
         717, /* glProgramUniform3uiEXT */
         718, /* glProgramUniform3uivEXT */
         719, /* glProgramUniform4dEXT */
         720, /* glProgramUniform4dvEXT */
         721, /* glProgramUniform4fEXT */
         722, /* glProgramUniform4fvEXT */
         723, /* glProgramUniform4iEXT */
         724, /* glProgramUniform4ivEXT */
         725, /* glProgramUniform4uiEXT */
         726, /* glProgramUniform4uivEXT */
         727, /* glProgramUniformMatrix2dvEXT */
         728, /* glProgramUniformMatrix2fvEXT */
         729, /* glProgramUniformMatrix2x3dvEXT */
         730, /* glProgramUniformMatrix2x3fvEXT */
         731, /* glProgramUniformMatrix2x4dvEXT */
         732, /* glProgramUniformMatrix2x4fvEXT */
         733, /* glProgramUniformMatrix3dvEXT */
         734, /* glProgramUniformMatrix3fvEXT */
         735, /* glProgramUniformMatrix3x2dvEXT */
         736, /* glProgramUniformMatrix3x2fvEXT */
         737, /* glProgramUniformMatrix3x4dvEXT */
         738, /* glProgramUniformMatrix3x4fvEXT */
         739, /* glProgramUniformMatrix4dvEXT */
         740, /* glProgramUniformMatrix4fvEXT */
         741, /* glProgramUniformMatrix4x2dvEXT */
         742, /* glProgramUniformMatrix4x2fvEXT */
         743, /* glProgramUniformMatrix4x3dvEXT */
         744, /* glProgramUniformMatrix4x3fvEXT */
         747, /* glPushClientAttribDefaultEXT */
         904, /* glTextureBufferEXT */
         905, /* glTextureBufferRangeEXT */
         906, /* glTextureImage1DEXT */
         907, /* glTextureImage2DEXT */
         908, /* glTextureImage3DEXT */
         909, /* glTexturePageCommitmentEXT */
         910, /* glTextureParameterIivEXT */
         911, /* glTextureParameterIuivEXT */
         912, /* glTextureParameterfEXT */
         913, /* glTextureParameterfvEXT */
         914, /* glTextureParameteriEXT */
         915, /* glTextureParameterivEXT */
         916, /* glTextureRenderbufferEXT */
         917, /* glTextureStorage1DEXT */
         918, /* glTextureStorage2DEXT */
         919, /* glTextureStorage2DMultisampleEXT */
         920, /* glTextureStorage3DEXT */
         921, /* glTextureStorage3DMultisampleEXT */
         922, /* glTextureSubImage1DEXT */
         923, /* glTextureSubImage2DEXT */
         924, /* glTextureSubImage3DEXT */
         974, /* glUnmapNamedBufferEXT */
        1003, /* glVertexArrayBindVertexBufferEXT */
        1004, /* glVertexArrayColorOffsetEXT */
        1005, /* glVertexArrayEdgeFlagOffsetEXT */
        1006, /* glVertexArrayFogCoordOffsetEXT */
        1007, /* glVertexArrayIndexOffsetEXT */
        1008, /* glVertexArrayMultiTexCoordOffsetEXT */
        1009, /* glVertexArrayNormalOffsetEXT */
        1010, /* glVertexArraySecondaryColorOffsetEXT */
        1011, /* glVertexArrayTexCoordOffsetEXT */
        1012, /* glVertexArrayVertexAttribBindingEXT */
        1013, /* glVertexArrayVertexAttribDivisorEXT */
        1014, /* glVertexArrayVertexAttribFormatEXT */
        1015, /* glVertexArrayVertexAttribIFormatEXT */
        1016, /* glVertexArrayVertexAttribIOffsetEXT */
        1017, /* glVertexArrayVertexAttribLFormatEXT */
        1018, /* glVertexArrayVertexAttribLOffsetEXT */
        1019, /* glVertexArrayVertexAttribOffsetEXT */
        1020, /* glVertexArrayVertexBindingDivisorEXT */
        1021  /* glVertexArrayVertexOffsetEXT */
    };
    uint32_t i;
    if(!context->EXT_direct_state_access) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_disjoint_timer_query(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1197, /* glBeginQueryEXT */
        1253, /* glDeleteQueriesEXT */
        1296, /* glEndQueryEXT */
        1313, /* glGenQueriesEXT */
        1338, /* glGetInteger64vEXT */
        1357, /* glGetQueryObjecti64vEXT */
        1358, /* glGetQueryObjectivEXT */
        1359, /* glGetQueryObjectui64vEXT */
        1360, /* glGetQueryObjectuivEXT */
        1361, /* glGetQueryivEXT */
        1406, /* glIsQueryEXT */
        1470  /* glQueryCounterEXT */
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
        1277  /* glDrawBuffersEXT */
    };
    uint32_t i;
    if(!context->EXT_draw_buffers) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_draw_buffers_indexed(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1215, /* glBlendEquationSeparateiEXT */
        1218, /* glBlendEquationiEXT */
        1221, /* glBlendFuncSeparateiEXT */
        1224, /* glBlendFunciEXT */
        1238, /* glColorMaskiEXT */
        1267, /* glDisableiEXT */
        1293, /* glEnableiEXT */
        1400  /* glIsEnablediEXT */
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
        1279, /* glDrawElementsBaseVertexEXT */
        1285, /* glDrawElementsInstancedBaseVertexEXT */
        1290, /* glDrawRangeElementsBaseVertexEXT */
        1421  /* glMultiDrawElementsBaseVertexEXT */
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
        1275, /* glDrawArraysInstancedEXT */
        1287  /* glDrawElementsInstancedEXT */
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
         197  /* glDrawRangeElementsEXT */
    };
    uint32_t i;
    if(!context->EXT_draw_range_elements) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_fog_coord(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         233, /* glFogCoordPointerEXT */
         235, /* glFogCoorddEXT */
         237, /* glFogCoorddvEXT */
         239, /* glFogCoordfEXT */
         241  /* glFogCoordfvEXT */
    };
    uint32_t i;
    if(!context->EXT_fog_coord) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_geometry_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1307  /* glFramebufferTextureEXT */
    };
    uint32_t i;
    if(!context->EXT_geometry_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_instanced_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1275, /* glDrawArraysInstancedEXT */
        1287, /* glDrawElementsInstancedEXT */
        1541  /* glVertexAttribDivisorEXT */
    };
    uint32_t i;
    if(!context->EXT_instanced_arrays) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_map_buffer_range(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1301, /* glFlushMappedBufferRangeEXT */
        1416  /* glMapBufferRangeEXT */
    };
    uint32_t i;
    if(!context->EXT_map_buffer_range) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_multi_draw_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         513, /* glMultiDrawArraysEXT */
         515  /* glMultiDrawElementsEXT */
    };
    uint32_t i;
    if(!context->EXT_multi_draw_arrays) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_multisampled_render_to_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1306, /* glFramebufferTexture2DMultisampleEXT */
        1477  /* glRenderbufferStorageMultisampleEXT */
    };
    uint32_t i;
    if(!context->EXT_multisampled_render_to_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_point_parameters(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         659, /* glPointParameterfEXT */
         663  /* glPointParameterfvEXT */
    };
    uint32_t i;
    if(!context->EXT_point_parameters) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_primitive_bounding_box(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1430  /* glPrimitiveBoundingBoxEXT */
    };
    uint32_t i;
    if(!context->EXT_primitive_bounding_box) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_robustness(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1333, /* glGetGraphicsResetStatusEXT */
        1390, /* glGetnUniformfvEXT */
        1393, /* glGetnUniformivEXT */
        1472  /* glReadnPixelsEXT */
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
         797, /* glSecondaryColor3bEXT */
         799, /* glSecondaryColor3bvEXT */
         801, /* glSecondaryColor3dEXT */
         803, /* glSecondaryColor3dvEXT */
         805, /* glSecondaryColor3fEXT */
         807, /* glSecondaryColor3fvEXT */
         809, /* glSecondaryColor3iEXT */
         811, /* glSecondaryColor3ivEXT */
         813, /* glSecondaryColor3sEXT */
         815, /* glSecondaryColor3svEXT */
         817, /* glSecondaryColor3ubEXT */
         819, /* glSecondaryColor3ubvEXT */
         821, /* glSecondaryColor3uiEXT */
         823, /* glSecondaryColor3uivEXT */
         825, /* glSecondaryColor3usEXT */
         827, /* glSecondaryColor3usvEXT */
         829  /* glSecondaryColorPointerEXT */
    };
    uint32_t i;
    if(!context->EXT_secondary_color) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_separate_shader_objects(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1196, /* glActiveShaderProgramEXT */
        1204, /* glBindProgramPipelineEXT */
        1246, /* glCreateShaderProgramvEXT */
        1252, /* glDeleteProgramPipelinesEXT */
        1312, /* glGenProgramPipelinesEXT */
        1350, /* glGetProgramPipelineInfoLogEXT */
        1352, /* glGetProgramPipelineivEXT */
        1405, /* glIsProgramPipelineEXT */
        1435, /* glProgramParameteriEXT */
         697, /* glProgramUniform1fEXT */
         698, /* glProgramUniform1fvEXT */
         699, /* glProgramUniform1iEXT */
         700, /* glProgramUniform1ivEXT */
         701, /* glProgramUniform1uiEXT */
         702, /* glProgramUniform1uivEXT */
         705, /* glProgramUniform2fEXT */
         706, /* glProgramUniform2fvEXT */
         707, /* glProgramUniform2iEXT */
         708, /* glProgramUniform2ivEXT */
         709, /* glProgramUniform2uiEXT */
         710, /* glProgramUniform2uivEXT */
         713, /* glProgramUniform3fEXT */
         714, /* glProgramUniform3fvEXT */
         715, /* glProgramUniform3iEXT */
         716, /* glProgramUniform3ivEXT */
         717, /* glProgramUniform3uiEXT */
         718, /* glProgramUniform3uivEXT */
         721, /* glProgramUniform4fEXT */
         722, /* glProgramUniform4fvEXT */
         723, /* glProgramUniform4iEXT */
         724, /* glProgramUniform4ivEXT */
         725, /* glProgramUniform4uiEXT */
         726, /* glProgramUniform4uivEXT */
         728, /* glProgramUniformMatrix2fvEXT */
         730, /* glProgramUniformMatrix2x3fvEXT */
         732, /* glProgramUniformMatrix2x4fvEXT */
         734, /* glProgramUniformMatrix3fvEXT */
         736, /* glProgramUniformMatrix3x2fvEXT */
         738, /* glProgramUniformMatrix3x4fvEXT */
         740, /* glProgramUniformMatrix4fvEXT */
         742, /* glProgramUniformMatrix4x2fvEXT */
         744, /* glProgramUniformMatrix4x3fvEXT */
        1535, /* glUseProgramStagesEXT */
        1537  /* glValidateProgramPipelineEXT */
    };
    uint32_t i;
    if(!context->EXT_separate_shader_objects) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_subtexture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         899, /* glTexSubImage1DEXT */
         901  /* glTexSubImage2DEXT */
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
        1425  /* glPatchParameteriEXT */
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
         890, /* glTexImage3DEXT */
         903  /* glTexSubImage3DEXT */
    };
    uint32_t i;
    if(!context->EXT_texture3D) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_border_clamp(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1364, /* glGetSamplerParameterIivEXT */
        1367, /* glGetSamplerParameterIuivEXT */
        1378, /* glGetTexParameterIivEXT */
        1381, /* glGetTexParameterIuivEXT */
        1483, /* glSamplerParameterIivEXT */
        1486, /* glSamplerParameterIuivEXT */
        1506, /* glTexParameterIivEXT */
        1509  /* glTexParameterIuivEXT */
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
        1500, /* glTexBufferEXT */
        1503  /* glTexBufferRangeEXT */
    };
    uint32_t i;
    if(!context->EXT_texture_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           6, /* glAreTexturesResidentEXT */
          22, /* glBindTextureEXT */
         173, /* glDeleteTexturesEXT */
         259, /* glGenTexturesEXT */
         445, /* glIsTextureEXT */
         679  /* glPrioritizeTexturesEXT */
    };
    uint32_t i;
    if(!context->EXT_texture_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_texture_storage(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         895, /* glTexStorage1DEXT */
         896, /* glTexStorage2DEXT */
         897, /* glTexStorage3DEXT */
         917, /* glTextureStorage1DEXT */
         918, /* glTextureStorage2DEXT */
         920  /* glTextureStorage3DEXT */
    };
    uint32_t i;
    if(!context->EXT_texture_storage) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_vertex_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           8, /* glArrayElementEXT */
          89, /* glColorPointerEXT */
         189, /* glDrawArraysEXT */
         200, /* glEdgeFlagPointerEXT */
         350, /* glGetPointervEXT */
         420, /* glIndexPointerEXT */
         644, /* glNormalPointerEXT */
         876, /* glTexCoordPointerEXT */
        1137  /* glVertexPointerEXT */
    };
    uint32_t i;
    if(!context->EXT_vertex_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_INGR_blend_func_separate(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
          33  /* glBlendFuncSeparateINGR */
    };
    uint32_t i;
    if(!context->INGR_blend_func_separate) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_KHR_blend_equation_advanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1212  /* glBlendBarrierKHR */
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
         156, /* glDebugMessageCallback */
        1247, /* glDebugMessageCallbackKHR */
         158, /* glDebugMessageControl */
        1248, /* glDebugMessageControlKHR */
         160, /* glDebugMessageInsert */
        1249, /* glDebugMessageInsertKHR */
         289, /* glGetDebugMessageLog */
        1326, /* glGetDebugMessageLogKHR */
         340, /* glGetObjectLabel */
        1343, /* glGetObjectLabelKHR */
         343, /* glGetObjectPtrLabel */
        1344, /* glGetObjectPtrLabelKHR */
         349, /* glGetPointerv */
        1345, /* glGetPointervKHR */
         645, /* glObjectLabel */
        1422, /* glObjectLabelKHR */
         646, /* glObjectPtrLabel */
        1423, /* glObjectPtrLabelKHR */
         675, /* glPopDebugGroup */
        1428, /* glPopDebugGroupKHR */
         748, /* glPushDebugGroup */
        1469  /* glPushDebugGroupKHR */
    };
    uint32_t i;
    if(!context->KHR_debug) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_KHR_robustness(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1332, /* glGetGraphicsResetStatus */
        1334, /* glGetGraphicsResetStatusKHR */
        1389, /* glGetnUniformfv */
        1391, /* glGetnUniformfvKHR */
        1392, /* glGetnUniformiv */
        1394, /* glGetnUniformivKHR */
        1395, /* glGetnUniformuiv */
        1396, /* glGetnUniformuivKHR */
        1471, /* glReadnPixels */
        1473  /* glReadnPixelsKHR */
    };
    uint32_t i;
    if(!context->KHR_robustness) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_MESA_sampler_objects(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1206, /* glBindSampler */
        1255, /* glDeleteSamplers */
        1315, /* glGenSamplers */
        1369, /* glGetSamplerParameterfv */
        1370, /* glGetSamplerParameteriv */
        1408, /* glIsSampler */
        1488, /* glSamplerParameterf */
        1489, /* glSamplerParameterfv */
        1490, /* glSamplerParameteri */
        1491  /* glSamplerParameteriv */
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
        1141, /* glWindowPos2dMESA */
        1144, /* glWindowPos2dvMESA */
        1147, /* glWindowPos2fMESA */
        1150, /* glWindowPos2fvMESA */
        1153, /* glWindowPos2iMESA */
        1156, /* glWindowPos2ivMESA */
        1159, /* glWindowPos2sMESA */
        1162, /* glWindowPos2svMESA */
        1165, /* glWindowPos3dMESA */
        1168, /* glWindowPos3dvMESA */
        1171, /* glWindowPos3fMESA */
        1174, /* glWindowPos3fvMESA */
        1177, /* glWindowPos3iMESA */
        1180, /* glWindowPos3ivMESA */
        1183, /* glWindowPos3sMESA */
        1186, /* glWindowPos3svMESA */
        1187, /* glWindowPos4dMESA */
        1188, /* glWindowPos4dvMESA */
        1189, /* glWindowPos4fMESA */
        1190, /* glWindowPos4fvMESA */
        1191, /* glWindowPos4iMESA */
        1192, /* glWindowPos4ivMESA */
        1193, /* glWindowPos4sMESA */
        1194  /* glWindowPos4svMESA */
    };
    uint32_t i;
    if(!context->MESA_window_pos) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_blend_equation_advanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1213, /* glBlendBarrierNV */
        1226  /* glBlendParameteriNV */
    };
    uint32_t i;
    if(!context->NV_blend_equation_advanced) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_copy_buffer(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1241  /* glCopyBufferSubDataNV */
    };
    uint32_t i;
    if(!context->NV_copy_buffer) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_draw_instanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1276, /* glDrawArraysInstancedNV */
        1288  /* glDrawElementsInstancedNV */
    };
    uint32_t i;
    if(!context->NV_draw_instanced) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_framebuffer_blit(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1228  /* glBlitFramebufferNV */
    };
    uint32_t i;
    if(!context->NV_framebuffer_blit) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_framebuffer_multisample(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1478  /* glRenderbufferStorageMultisampleNV */
    };
    uint32_t i;
    if(!context->NV_framebuffer_multisample) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_instanced_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1542  /* glVertexAttribDivisorNV */
    };
    uint32_t i;
    if(!context->NV_instanced_arrays) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_non_square_matrices(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1527, /* glUniformMatrix2x3fvNV */
        1528, /* glUniformMatrix2x4fvNV */
        1529, /* glUniformMatrix3x2fvNV */
        1530, /* glUniformMatrix3x4fvNV */
        1531, /* glUniformMatrix4x2fvNV */
        1532  /* glUniformMatrix4x3fvNV */
    };
    uint32_t i;
    if(!context->NV_non_square_matrices) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_point_sprite(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         666, /* glPointParameteriNV */
         668  /* glPointParameterivNV */
    };
    uint32_t i;
    if(!context->NV_point_sprite) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_vertex_program(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           4, /* glAreProgramsResidentNV */
          20, /* glBindProgramNV */
         168, /* glDeleteProgramsNV */
         227, /* glExecuteProgramNV */
         255, /* glGenProgramsNV */
         357, /* glGetProgramParameterdvNV */
         358, /* glGetProgramParameterfvNV */
         360, /* glGetProgramStringNV */
         363, /* glGetProgramivNV */
         393, /* glGetTrackMatrixivNV */
         406, /* glGetVertexAttribPointervNV */
         409, /* glGetVertexAttribdvNV */
         412, /* glGetVertexAttribfvNV */
         415, /* glGetVertexAttribivNV */
         440, /* glIsProgramNV */
         463, /* glLoadProgramNV */
         688, /* glProgramParameter4dNV */
         689, /* glProgramParameter4dvNV */
         690, /* glProgramParameter4fNV */
         691, /* glProgramParameter4fvNV */
         692, /* glProgramParameters4dvNV */
         693, /* glProgramParameters4fvNV */
         786, /* glRequestResidentProgramsNV */
         925, /* glTrackMatrixNV */
        1024, /* glVertexAttrib1dNV */
        1027, /* glVertexAttrib1dvNV */
        1030, /* glVertexAttrib1fNV */
        1033, /* glVertexAttrib1fvNV */
        1036, /* glVertexAttrib1sNV */
        1039, /* glVertexAttrib1svNV */
        1042, /* glVertexAttrib2dNV */
        1045, /* glVertexAttrib2dvNV */
        1048, /* glVertexAttrib2fNV */
        1051, /* glVertexAttrib2fvNV */
        1054, /* glVertexAttrib2sNV */
        1057, /* glVertexAttrib2svNV */
        1060, /* glVertexAttrib3dNV */
        1063, /* glVertexAttrib3dvNV */
        1066, /* glVertexAttrib3fNV */
        1069, /* glVertexAttrib3fvNV */
        1072, /* glVertexAttrib3sNV */
        1075, /* glVertexAttrib3svNV */
        1094, /* glVertexAttrib4dNV */
        1097, /* glVertexAttrib4dvNV */
        1100, /* glVertexAttrib4fNV */
        1103, /* glVertexAttrib4fvNV */
        1108, /* glVertexAttrib4sNV */
        1111, /* glVertexAttrib4svNV */
        1112, /* glVertexAttrib4ubNV */
        1115, /* glVertexAttrib4ubvNV */
        1122, /* glVertexAttribPointerNV */
        1123, /* glVertexAttribs1dvNV */
        1124, /* glVertexAttribs1fvNV */
        1125, /* glVertexAttribs1svNV */
        1126, /* glVertexAttribs2dvNV */
        1127, /* glVertexAttribs2fvNV */
        1128, /* glVertexAttribs2svNV */
        1129, /* glVertexAttribs3dvNV */
        1130, /* glVertexAttribs3fvNV */
        1131, /* glVertexAttribs3svNV */
        1132, /* glVertexAttribs4dvNV */
        1133, /* glVertexAttribs4fvNV */
        1134, /* glVertexAttribs4svNV */
        1135  /* glVertexAttribs4ubvNV */
    };
    uint32_t i;
    if(!context->NV_vertex_program) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_viewport_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1261, /* glDepthRangeArrayfvNV */
        1263, /* glDepthRangeIndexedfNV */
        1268, /* glDisableiNV */
        1294, /* glEnableiNV */
        1327, /* glGetFloati_vNV */
        1401, /* glIsEnablediNV */
        1492, /* glScissorArrayvNV */
        1494, /* glScissorIndexedNV */
        1496, /* glScissorIndexedvNV */
        1551, /* glViewportArrayvNV */
        1553, /* glViewportIndexedfNV */
        1555  /* glViewportIndexedfvNV */
    };
    uint32_t i;
    if(!context->NV_viewport_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_copy_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1244  /* glCopyImageSubDataOES */
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
        1216, /* glBlendEquationSeparateiOES */
        1219, /* glBlendEquationiOES */
        1222, /* glBlendFuncSeparateiOES */
        1225, /* glBlendFunciOES */
        1239, /* glColorMaskiOES */
        1269, /* glDisableiOES */
        1295, /* glEnableiOES */
        1402  /* glIsEnablediOES */
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
        1280, /* glDrawElementsBaseVertexOES */
        1286, /* glDrawElementsInstancedBaseVertexOES */
        1291, /* glDrawRangeElementsBaseVertexOES */
        1421  /* glMultiDrawElementsBaseVertexEXT */
    };
    uint32_t i;
    if(!context->OES_draw_elements_base_vertex) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_geometry_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1309  /* glFramebufferTextureOES */
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
        1347, /* glGetProgramBinaryOES */
        1433  /* glProgramBinaryOES */
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
        1325, /* glGetBufferPointervOES */
        1414, /* glMapBufferOES */
        1533  /* glUnmapBufferOES */
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
        1431  /* glPrimitiveBoundingBoxOES */
    };
    uint32_t i;
    if(!context->OES_primitive_bounding_box) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_sample_shading(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1420  /* glMinSampleShadingOES */
    };
    uint32_t i;
    if(!context->OES_sample_shading) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_tessellation_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1426  /* glPatchParameteriOES */
    };
    uint32_t i;
    if(!context->OES_tessellation_shader) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_texture_border_clamp(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1365, /* glGetSamplerParameterIivOES */
        1368, /* glGetSamplerParameterIuivOES */
        1379, /* glGetTexParameterIivOES */
        1382, /* glGetTexParameterIuivOES */
        1484, /* glSamplerParameterIivOES */
        1487, /* glSamplerParameterIuivOES */
        1507, /* glTexParameterIivOES */
        1510  /* glTexParameterIuivOES */
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
        1501, /* glTexBufferOES */
        1504  /* glTexBufferRangeOES */
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
        1516  /* glTexStorage3DMultisampleOES */
    };
    uint32_t i;
    if(!context->OES_texture_storage_multisample_2d_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_OES_vertex_array_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
        1209, /* glBindVertexArrayOES */
        1260, /* glDeleteVertexArraysOES */
        1318, /* glGenVertexArraysOES */
        1413  /* glIsVertexArrayOES */
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
        1262, /* glDepthRangeArrayfvOES */
        1264, /* glDepthRangeIndexedfOES */
        1269, /* glDisableiOES */
        1295, /* glEnableiOES */
        1328, /* glGetFloati_vOES */
        1402, /* glIsEnablediOES */
        1493, /* glScissorArrayvOES */
        1495, /* glScissorIndexedOES */
        1497, /* glScissorIndexedvOES */
        1552, /* glViewportArrayvOES */
        1554, /* glViewportIndexedfOES */
        1556  /* glViewportIndexedfvOES */
    };
    uint32_t i;
    if(!context->OES_viewport_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_SGIS_point_parameters(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         660, /* glPointParameterfSGIS */
         664  /* glPointParameterfvSGIS */
    };
    uint32_t i;
    if(!context->SGIS_point_parameters) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_resolve_aliases(GladGLContext *context) {
    static const GladAliasPair_t s_aliases[] = {
        {    1,    2 }, /* glActiveTexture and glActiveTextureARB */
        {    2,    1 }, /* glActiveTextureARB and glActiveTexture */
        {    7,    8 }, /* glArrayElement and glArrayElementEXT */
        {    8,    7 }, /* glArrayElementEXT and glArrayElement */
        {    9,   10 }, /* glAttachObjectARB and glAttachShader */
        {   10,    9 }, /* glAttachShader and glAttachObjectARB */
        {   12,   13 }, /* glBeginQuery and glBeginQueryARB */
        {   13,   12 }, /* glBeginQueryARB and glBeginQuery */
        {   14,   15 }, /* glBindAttribLocation and glBindAttribLocationARB */
        {   15,   14 }, /* glBindAttribLocationARB and glBindAttribLocation */
        {   16,   17 }, /* glBindBuffer and glBindBufferARB */
        {   17,   16 }, /* glBindBufferARB and glBindBuffer */
        {   19,   20 }, /* glBindProgramARB and glBindProgramNV */
        {   20,   19 }, /* glBindProgramNV and glBindProgramARB */
        {   21,   22 }, /* glBindTexture and glBindTextureEXT */
        {   22,   21 }, /* glBindTextureEXT and glBindTexture */
        { 1208, 1209 }, /* glBindVertexArray and glBindVertexArrayOES */
        { 1209, 1208 }, /* glBindVertexArrayOES and glBindVertexArray */
        { 1211, 1212 }, /* glBlendBarrier and glBlendBarrierKHR */
        { 1211, 1213 }, /* glBlendBarrier and glBlendBarrierNV */
        { 1212, 1211 }, /* glBlendBarrierKHR and glBlendBarrier */
        { 1212, 1213 }, /* glBlendBarrierKHR and glBlendBarrierNV */
        { 1213, 1211 }, /* glBlendBarrierNV and glBlendBarrier */
        { 1213, 1212 }, /* glBlendBarrierNV and glBlendBarrierKHR */
        {   24,   25 }, /* glBlendColor and glBlendColorEXT */
        {   25,   24 }, /* glBlendColorEXT and glBlendColor */
        {   26,   27 }, /* glBlendEquation and glBlendEquationEXT */
        {   27,   26 }, /* glBlendEquationEXT and glBlendEquation */
        { 1217, 1218 }, /* glBlendEquationi and glBlendEquationiEXT */
        { 1217, 1219 }, /* glBlendEquationi and glBlendEquationiOES */
        { 1218, 1217 }, /* glBlendEquationiEXT and glBlendEquationi */
        { 1218, 1219 }, /* glBlendEquationiEXT and glBlendEquationiOES */
        { 1219, 1217 }, /* glBlendEquationiOES and glBlendEquationi */
        { 1219, 1218 }, /* glBlendEquationiOES and glBlendEquationiEXT */
        {   28,   29 }, /* glBlendEquationSeparate and glBlendEquationSeparateEXT */
        {   29,   28 }, /* glBlendEquationSeparateEXT and glBlendEquationSeparate */
        { 1214, 1215 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiEXT */
        { 1214, 1216 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiOES */
        { 1215, 1214 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparatei */
        { 1215, 1216 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparateiOES */
        { 1216, 1214 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparatei */
        { 1216, 1215 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparateiEXT */
        { 1223, 1224 }, /* glBlendFunci and glBlendFunciEXT */
        { 1223, 1225 }, /* glBlendFunci and glBlendFunciOES */
        { 1224, 1223 }, /* glBlendFunciEXT and glBlendFunci */
        { 1224, 1225 }, /* glBlendFunciEXT and glBlendFunciOES */
        { 1225, 1223 }, /* glBlendFunciOES and glBlendFunci */
        { 1225, 1224 }, /* glBlendFunciOES and glBlendFunciEXT */
        {   31,   32 }, /* glBlendFuncSeparate and glBlendFuncSeparateEXT */
        {   31,   33 }, /* glBlendFuncSeparate and glBlendFuncSeparateINGR */
        {   32,   31 }, /* glBlendFuncSeparateEXT and glBlendFuncSeparate */
        {   32,   33 }, /* glBlendFuncSeparateEXT and glBlendFuncSeparateINGR */
        { 1220, 1221 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiEXT */
        { 1220, 1222 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiOES */
        { 1221, 1220 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparatei */
        { 1221, 1222 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparateiOES */
        {   33,   31 }, /* glBlendFuncSeparateINGR and glBlendFuncSeparate */
        {   33,   32 }, /* glBlendFuncSeparateINGR and glBlendFuncSeparateEXT */
        { 1222, 1220 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparatei */
        { 1222, 1221 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparateiEXT */
        { 1227, 1228 }, /* glBlitFramebuffer and glBlitFramebufferNV */
        { 1228, 1227 }, /* glBlitFramebufferNV and glBlitFramebuffer */
        {   34,   35 }, /* glBufferData and glBufferDataARB */
        {   35,   34 }, /* glBufferDataARB and glBufferData */
        {   37,   38 }, /* glBufferSubData and glBufferSubDataARB */
        {   38,   37 }, /* glBufferSubDataARB and glBufferSubData */
        {   50,   51 }, /* glClientActiveTexture and glClientActiveTextureARB */
        {   51,   50 }, /* glClientActiveTextureARB and glClientActiveTexture */
        { 1235, 1236 }, /* glClientWaitSync and glClientWaitSyncAPPLE */
        { 1236, 1235 }, /* glClientWaitSyncAPPLE and glClientWaitSync */
        { 1237, 1238 }, /* glColorMaski and glColorMaskiEXT */
        { 1237, 1239 }, /* glColorMaski and glColorMaskiOES */
        { 1238, 1237 }, /* glColorMaskiEXT and glColorMaski */
        { 1238, 1239 }, /* glColorMaskiEXT and glColorMaskiOES */
        { 1239, 1237 }, /* glColorMaskiOES and glColorMaski */
        { 1239, 1238 }, /* glColorMaskiOES and glColorMaskiEXT */
        {   94,   95 }, /* glCompileShader and glCompileShaderARB */
        {   95,   94 }, /* glCompileShaderARB and glCompileShader */
        {  102,  103 }, /* glCompressedTexImage1D and glCompressedTexImage1DARB */
        {  103,  102 }, /* glCompressedTexImage1DARB and glCompressedTexImage1D */
        {  104,  105 }, /* glCompressedTexImage2D and glCompressedTexImage2DARB */
        {  105,  104 }, /* glCompressedTexImage2DARB and glCompressedTexImage2D */
        {  106,  107 }, /* glCompressedTexImage3D and glCompressedTexImage3DARB */
        {  107,  106 }, /* glCompressedTexImage3DARB and glCompressedTexImage3D */
        {  108,  109 }, /* glCompressedTexSubImage1D and glCompressedTexSubImage1DARB */
        {  109,  108 }, /* glCompressedTexSubImage1DARB and glCompressedTexSubImage1D */
        {  110,  111 }, /* glCompressedTexSubImage2D and glCompressedTexSubImage2DARB */
        {  111,  110 }, /* glCompressedTexSubImage2DARB and glCompressedTexSubImage2D */
        {  112,  113 }, /* glCompressedTexSubImage3D and glCompressedTexSubImage3DARB */
        {  113,  112 }, /* glCompressedTexSubImage3DARB and glCompressedTexSubImage3D */
        { 1240, 1241 }, /* glCopyBufferSubData and glCopyBufferSubDataNV */
        { 1241, 1240 }, /* glCopyBufferSubDataNV and glCopyBufferSubData */
        { 1242, 1243 }, /* glCopyImageSubData and glCopyImageSubDataEXT */
        { 1242, 1244 }, /* glCopyImageSubData and glCopyImageSubDataOES */
        { 1243, 1242 }, /* glCopyImageSubDataEXT and glCopyImageSubData */
        { 1243, 1244 }, /* glCopyImageSubDataEXT and glCopyImageSubDataOES */
        { 1244, 1242 }, /* glCopyImageSubDataOES and glCopyImageSubData */
        { 1244, 1243 }, /* glCopyImageSubDataOES and glCopyImageSubDataEXT */
        {  136,  137 }, /* glCopyTexImage1D and glCopyTexImage1DEXT */
        {  137,  136 }, /* glCopyTexImage1DEXT and glCopyTexImage1D */
        {  138,  139 }, /* glCopyTexImage2D and glCopyTexImage2DEXT */
        {  139,  138 }, /* glCopyTexImage2DEXT and glCopyTexImage2D */
        {  140,  141 }, /* glCopyTexSubImage1D and glCopyTexSubImage1DEXT */
        {  141,  140 }, /* glCopyTexSubImage1DEXT and glCopyTexSubImage1D */
        {  142,  143 }, /* glCopyTexSubImage2D and glCopyTexSubImage2DEXT */
        {  143,  142 }, /* glCopyTexSubImage2DEXT and glCopyTexSubImage2D */
        {  144,  145 }, /* glCopyTexSubImage3D and glCopyTexSubImage3DEXT */
        {  145,  144 }, /* glCopyTexSubImage3DEXT and glCopyTexSubImage3D */
        {  151,  152 }, /* glCreateProgram and glCreateProgramObjectARB */
        {  152,  151 }, /* glCreateProgramObjectARB and glCreateProgram */
        {  153,  154 }, /* glCreateShader and glCreateShaderObjectARB */
        {  154,  153 }, /* glCreateShaderObjectARB and glCreateShader */
        {  156,  157 }, /* glDebugMessageCallback and glDebugMessageCallbackARB */
        {  156, 1247 }, /* glDebugMessageCallback and glDebugMessageCallbackKHR */
        {  157,  156 }, /* glDebugMessageCallbackARB and glDebugMessageCallback */
        {  157, 1247 }, /* glDebugMessageCallbackARB and glDebugMessageCallbackKHR */
        { 1247,  156 }, /* glDebugMessageCallbackKHR and glDebugMessageCallback */
        { 1247,  157 }, /* glDebugMessageCallbackKHR and glDebugMessageCallbackARB */
        {  158,  159 }, /* glDebugMessageControl and glDebugMessageControlARB */
        {  158, 1248 }, /* glDebugMessageControl and glDebugMessageControlKHR */
        {  159,  158 }, /* glDebugMessageControlARB and glDebugMessageControl */
        {  159, 1248 }, /* glDebugMessageControlARB and glDebugMessageControlKHR */
        { 1248,  158 }, /* glDebugMessageControlKHR and glDebugMessageControl */
        { 1248,  159 }, /* glDebugMessageControlKHR and glDebugMessageControlARB */
        {  160,  161 }, /* glDebugMessageInsert and glDebugMessageInsertARB */
        {  160, 1249 }, /* glDebugMessageInsert and glDebugMessageInsertKHR */
        {  161,  160 }, /* glDebugMessageInsertARB and glDebugMessageInsert */
        {  161, 1249 }, /* glDebugMessageInsertARB and glDebugMessageInsertKHR */
        { 1249,  160 }, /* glDebugMessageInsertKHR and glDebugMessageInsert */
        { 1249,  161 }, /* glDebugMessageInsertKHR and glDebugMessageInsertARB */
        {  162,  163 }, /* glDeleteBuffers and glDeleteBuffersARB */
        {  163,  162 }, /* glDeleteBuffersARB and glDeleteBuffers */
        {  167,  168 }, /* glDeleteProgramsARB and glDeleteProgramsNV */
        {  168,  167 }, /* glDeleteProgramsNV and glDeleteProgramsARB */
        {  169,  170 }, /* glDeleteQueries and glDeleteQueriesARB */
        {  170,  169 }, /* glDeleteQueriesARB and glDeleteQueries */
        { 1256, 1257 }, /* glDeleteSync and glDeleteSyncAPPLE */
        { 1257, 1256 }, /* glDeleteSyncAPPLE and glDeleteSync */
        { 1259, 1260 }, /* glDeleteVertexArrays and glDeleteVertexArraysOES */
        { 1260, 1259 }, /* glDeleteVertexArraysOES and glDeleteVertexArrays */
        {  177,  178 }, /* glDetachObjectARB and glDetachShader */
        {  178,  177 }, /* glDetachShader and glDetachObjectARB */
        { 1266,  183 }, /* glDisablei and glDisableIndexedEXT */
        { 1266, 1267 }, /* glDisablei and glDisableiEXT */
        { 1266, 1268 }, /* glDisablei and glDisableiNV */
        { 1266, 1269 }, /* glDisablei and glDisableiOES */
        { 1267,  183 }, /* glDisableiEXT and glDisableIndexedEXT */
        { 1267, 1266 }, /* glDisableiEXT and glDisablei */
        { 1267, 1268 }, /* glDisableiEXT and glDisableiNV */
        { 1267, 1269 }, /* glDisableiEXT and glDisableiOES */
        {  183, 1266 }, /* glDisableIndexedEXT and glDisablei */
        {  183, 1267 }, /* glDisableIndexedEXT and glDisableiEXT */
        {  183, 1268 }, /* glDisableIndexedEXT and glDisableiNV */
        {  183, 1269 }, /* glDisableIndexedEXT and glDisableiOES */
        { 1268,  183 }, /* glDisableiNV and glDisableIndexedEXT */
        { 1268, 1266 }, /* glDisableiNV and glDisablei */
        { 1268, 1267 }, /* glDisableiNV and glDisableiEXT */
        { 1268, 1269 }, /* glDisableiNV and glDisableiOES */
        { 1269,  183 }, /* glDisableiOES and glDisableIndexedEXT */
        { 1269, 1266 }, /* glDisableiOES and glDisablei */
        { 1269, 1267 }, /* glDisableiOES and glDisableiEXT */
        { 1269, 1268 }, /* glDisableiOES and glDisableiNV */
        {  186,  187 }, /* glDisableVertexAttribArray and glDisableVertexAttribArrayARB */
        {  187,  186 }, /* glDisableVertexAttribArrayARB and glDisableVertexAttribArray */
        {  188,  189 }, /* glDrawArrays and glDrawArraysEXT */
        {  189,  188 }, /* glDrawArraysEXT and glDrawArrays */
        { 1273, 1274 }, /* glDrawArraysInstanced and glDrawArraysInstancedANGLE */
        { 1273, 1275 }, /* glDrawArraysInstanced and glDrawArraysInstancedEXT */
        { 1273, 1276 }, /* glDrawArraysInstanced and glDrawArraysInstancedNV */
        { 1274, 1273 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstanced */
        { 1274, 1275 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstancedEXT */
        { 1274, 1276 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstancedNV */
        { 1275, 1273 }, /* glDrawArraysInstancedEXT and glDrawArraysInstanced */
        { 1275, 1274 }, /* glDrawArraysInstancedEXT and glDrawArraysInstancedANGLE */
        { 1275, 1276 }, /* glDrawArraysInstancedEXT and glDrawArraysInstancedNV */
        { 1276, 1273 }, /* glDrawArraysInstancedNV and glDrawArraysInstanced */
        { 1276, 1274 }, /* glDrawArraysInstancedNV and glDrawArraysInstancedANGLE */
        { 1276, 1275 }, /* glDrawArraysInstancedNV and glDrawArraysInstancedEXT */
        {  191,  192 }, /* glDrawBuffers and glDrawBuffersARB */
        {  191,  193 }, /* glDrawBuffers and glDrawBuffersATI */
        {  191, 1277 }, /* glDrawBuffers and glDrawBuffersEXT */
        {  192,  191 }, /* glDrawBuffersARB and glDrawBuffers */
        {  192,  193 }, /* glDrawBuffersARB and glDrawBuffersATI */
        {  192, 1277 }, /* glDrawBuffersARB and glDrawBuffersEXT */
        {  193,  191 }, /* glDrawBuffersATI and glDrawBuffers */
        {  193,  192 }, /* glDrawBuffersATI and glDrawBuffersARB */
        {  193, 1277 }, /* glDrawBuffersATI and glDrawBuffersEXT */
        { 1277,  191 }, /* glDrawBuffersEXT and glDrawBuffers */
        { 1277,  192 }, /* glDrawBuffersEXT and glDrawBuffersARB */
        { 1277,  193 }, /* glDrawBuffersEXT and glDrawBuffersATI */
        { 1278, 1279 }, /* glDrawElementsBaseVertex and glDrawElementsBaseVertexEXT */
        { 1278, 1280 }, /* glDrawElementsBaseVertex and glDrawElementsBaseVertexOES */
        { 1279, 1278 }, /* glDrawElementsBaseVertexEXT and glDrawElementsBaseVertex */
        { 1279, 1280 }, /* glDrawElementsBaseVertexEXT and glDrawElementsBaseVertexOES */
        { 1280, 1278 }, /* glDrawElementsBaseVertexOES and glDrawElementsBaseVertex */
        { 1280, 1279 }, /* glDrawElementsBaseVertexOES and glDrawElementsBaseVertexEXT */
        { 1282, 1283 }, /* glDrawElementsInstanced and glDrawElementsInstancedANGLE */
        { 1282, 1287 }, /* glDrawElementsInstanced and glDrawElementsInstancedEXT */
        { 1282, 1288 }, /* glDrawElementsInstanced and glDrawElementsInstancedNV */
        { 1283, 1282 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstanced */
        { 1283, 1287 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstancedEXT */
        { 1283, 1288 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstancedNV */
        { 1284, 1285 }, /* glDrawElementsInstancedBaseVertex and glDrawElementsInstancedBaseVertexEXT */
        { 1284, 1286 }, /* glDrawElementsInstancedBaseVertex and glDrawElementsInstancedBaseVertexOES */
        { 1285, 1284 }, /* glDrawElementsInstancedBaseVertexEXT and glDrawElementsInstancedBaseVertex */
        { 1285, 1286 }, /* glDrawElementsInstancedBaseVertexEXT and glDrawElementsInstancedBaseVertexOES */
        { 1286, 1284 }, /* glDrawElementsInstancedBaseVertexOES and glDrawElementsInstancedBaseVertex */
        { 1286, 1285 }, /* glDrawElementsInstancedBaseVertexOES and glDrawElementsInstancedBaseVertexEXT */
        { 1287, 1282 }, /* glDrawElementsInstancedEXT and glDrawElementsInstanced */
        { 1287, 1283 }, /* glDrawElementsInstancedEXT and glDrawElementsInstancedANGLE */
        { 1287, 1288 }, /* glDrawElementsInstancedEXT and glDrawElementsInstancedNV */
        { 1288, 1282 }, /* glDrawElementsInstancedNV and glDrawElementsInstanced */
        { 1288, 1283 }, /* glDrawElementsInstancedNV and glDrawElementsInstancedANGLE */
        { 1288, 1287 }, /* glDrawElementsInstancedNV and glDrawElementsInstancedEXT */
        {  196,  197 }, /* glDrawRangeElements and glDrawRangeElementsEXT */
        { 1289, 1290 }, /* glDrawRangeElementsBaseVertex and glDrawRangeElementsBaseVertexEXT */
        { 1289, 1291 }, /* glDrawRangeElementsBaseVertex and glDrawRangeElementsBaseVertexOES */
        { 1290, 1289 }, /* glDrawRangeElementsBaseVertexEXT and glDrawRangeElementsBaseVertex */
        { 1290, 1291 }, /* glDrawRangeElementsBaseVertexEXT and glDrawRangeElementsBaseVertexOES */
        { 1291, 1289 }, /* glDrawRangeElementsBaseVertexOES and glDrawRangeElementsBaseVertex */
        { 1291, 1290 }, /* glDrawRangeElementsBaseVertexOES and glDrawRangeElementsBaseVertexEXT */
        {  197,  196 }, /* glDrawRangeElementsEXT and glDrawRangeElements */
        { 1292,  206 }, /* glEnablei and glEnableIndexedEXT */
        { 1292, 1293 }, /* glEnablei and glEnableiEXT */
        { 1292, 1294 }, /* glEnablei and glEnableiNV */
        { 1292, 1295 }, /* glEnablei and glEnableiOES */
        { 1293,  206 }, /* glEnableiEXT and glEnableIndexedEXT */
        { 1293, 1292 }, /* glEnableiEXT and glEnablei */
        { 1293, 1294 }, /* glEnableiEXT and glEnableiNV */
        { 1293, 1295 }, /* glEnableiEXT and glEnableiOES */
        {  206, 1292 }, /* glEnableIndexedEXT and glEnablei */
        {  206, 1293 }, /* glEnableIndexedEXT and glEnableiEXT */
        {  206, 1294 }, /* glEnableIndexedEXT and glEnableiNV */
        {  206, 1295 }, /* glEnableIndexedEXT and glEnableiOES */
        { 1294,  206 }, /* glEnableiNV and glEnableIndexedEXT */
        { 1294, 1292 }, /* glEnableiNV and glEnablei */
        { 1294, 1293 }, /* glEnableiNV and glEnableiEXT */
        { 1294, 1295 }, /* glEnableiNV and glEnableiOES */
        { 1295,  206 }, /* glEnableiOES and glEnableIndexedEXT */
        { 1295, 1292 }, /* glEnableiOES and glEnablei */
        { 1295, 1293 }, /* glEnableiOES and glEnableiEXT */
        { 1295, 1294 }, /* glEnableiOES and glEnableiNV */
        {  209,  210 }, /* glEnableVertexAttribArray and glEnableVertexAttribArrayARB */
        {  210,  209 }, /* glEnableVertexAttribArrayARB and glEnableVertexAttribArray */
        {  213,  214 }, /* glEndQuery and glEndQueryARB */
        {  214,  213 }, /* glEndQueryARB and glEndQuery */
        { 1298, 1299 }, /* glFenceSync and glFenceSyncAPPLE */
        { 1299, 1298 }, /* glFenceSyncAPPLE and glFenceSync */
        { 1300, 1301 }, /* glFlushMappedBufferRange and glFlushMappedBufferRangeEXT */
        { 1301, 1300 }, /* glFlushMappedBufferRangeEXT and glFlushMappedBufferRange */
        {  234,  235 }, /* glFogCoordd and glFogCoorddEXT */
        {  235,  234 }, /* glFogCoorddEXT and glFogCoordd */
        {  236,  237 }, /* glFogCoorddv and glFogCoorddvEXT */
        {  237,  236 }, /* glFogCoorddvEXT and glFogCoorddv */
        {  238,  239 }, /* glFogCoordf and glFogCoordfEXT */
        {  239,  238 }, /* glFogCoordfEXT and glFogCoordf */
        {  240,  241 }, /* glFogCoordfv and glFogCoordfvEXT */
        {  241,  240 }, /* glFogCoordfvEXT and glFogCoordfv */
        {  232,  233 }, /* glFogCoordPointer and glFogCoordPointerEXT */
        {  233,  232 }, /* glFogCoordPointerEXT and glFogCoordPointer */
        { 1304, 1307 }, /* glFramebufferTexture and glFramebufferTextureEXT */
        { 1304, 1309 }, /* glFramebufferTexture and glFramebufferTextureOES */
        { 1307, 1304 }, /* glFramebufferTextureEXT and glFramebufferTexture */
        { 1307, 1309 }, /* glFramebufferTextureEXT and glFramebufferTextureOES */
        { 1309, 1304 }, /* glFramebufferTextureOES and glFramebufferTexture */
        { 1309, 1307 }, /* glFramebufferTextureOES and glFramebufferTextureEXT */
        {  251,  252 }, /* glGenBuffers and glGenBuffersARB */
        {  252,  251 }, /* glGenBuffersARB and glGenBuffers */
        {  254,  255 }, /* glGenProgramsARB and glGenProgramsNV */
        {  255,  254 }, /* glGenProgramsNV and glGenProgramsARB */
        {  256,  257 }, /* glGenQueries and glGenQueriesARB */
        {  257,  256 }, /* glGenQueriesARB and glGenQueries */
        { 1317, 1318 }, /* glGenVertexArrays and glGenVertexArraysOES */
        { 1318, 1317 }, /* glGenVertexArraysOES and glGenVertexArrays */
        {  262,  263 }, /* glGetActiveAttrib and glGetActiveAttribARB */
        {  263,  262 }, /* glGetActiveAttribARB and glGetActiveAttrib */
        {  264,  265 }, /* glGetActiveUniform and glGetActiveUniformARB */
        {  265,  264 }, /* glGetActiveUniformARB and glGetActiveUniform */
        {  268,  269 }, /* glGetAttribLocation and glGetAttribLocationARB */
        {  269,  268 }, /* glGetAttribLocationARB and glGetAttribLocation */
        { 1323,  270 }, /* glGetBooleani_v and glGetBooleanIndexedvEXT */
        {  270, 1323 }, /* glGetBooleanIndexedvEXT and glGetBooleani_v */
        {  272,  273 }, /* glGetBufferParameteriv and glGetBufferParameterivARB */
        {  273,  272 }, /* glGetBufferParameterivARB and glGetBufferParameteriv */
        {  274,  275 }, /* glGetBufferPointerv and glGetBufferPointervARB */
        {  274, 1325 }, /* glGetBufferPointerv and glGetBufferPointervOES */
        {  275,  274 }, /* glGetBufferPointervARB and glGetBufferPointerv */
        {  275, 1325 }, /* glGetBufferPointervARB and glGetBufferPointervOES */
        { 1325,  274 }, /* glGetBufferPointervOES and glGetBufferPointerv */
        { 1325,  275 }, /* glGetBufferPointervOES and glGetBufferPointervARB */
        {  276,  277 }, /* glGetBufferSubData and glGetBufferSubDataARB */
        {  277,  276 }, /* glGetBufferSubDataARB and glGetBufferSubData */
        {  283,  284 }, /* glGetCompressedTexImage and glGetCompressedTexImageARB */
        {  284,  283 }, /* glGetCompressedTexImageARB and glGetCompressedTexImage */
        {  289,  290 }, /* glGetDebugMessageLog and glGetDebugMessageLogARB */
        {  289, 1326 }, /* glGetDebugMessageLog and glGetDebugMessageLogKHR */
        {  290,  289 }, /* glGetDebugMessageLogARB and glGetDebugMessageLog */
        {  290, 1326 }, /* glGetDebugMessageLogARB and glGetDebugMessageLogKHR */
        { 1326,  289 }, /* glGetDebugMessageLogKHR and glGetDebugMessageLog */
        { 1326,  290 }, /* glGetDebugMessageLogKHR and glGetDebugMessageLogARB */
        { 1332, 1333 }, /* glGetGraphicsResetStatus and glGetGraphicsResetStatusEXT */
        { 1332, 1334 }, /* glGetGraphicsResetStatus and glGetGraphicsResetStatusKHR */
        { 1333, 1332 }, /* glGetGraphicsResetStatusEXT and glGetGraphicsResetStatus */
        { 1333, 1334 }, /* glGetGraphicsResetStatusEXT and glGetGraphicsResetStatusKHR */
        { 1334, 1332 }, /* glGetGraphicsResetStatusKHR and glGetGraphicsResetStatus */
        { 1334, 1333 }, /* glGetGraphicsResetStatusKHR and glGetGraphicsResetStatusEXT */
        { 1336, 1337 }, /* glGetInteger64v and glGetInteger64vAPPLE */
        { 1336, 1338 }, /* glGetInteger64v and glGetInteger64vEXT */
        { 1337, 1336 }, /* glGetInteger64vAPPLE and glGetInteger64v */
        { 1337, 1338 }, /* glGetInteger64vAPPLE and glGetInteger64vEXT */
        { 1338, 1336 }, /* glGetInteger64vEXT and glGetInteger64v */
        { 1338, 1337 }, /* glGetInteger64vEXT and glGetInteger64vAPPLE */
        { 1339,  304 }, /* glGetIntegeri_v and glGetIntegerIndexedvEXT */
        {  304, 1339 }, /* glGetIntegerIndexedvEXT and glGetIntegeri_v */
        { 1341, 1342 }, /* glGetMultisamplefv and glGetMultisamplefvANGLE */
        { 1342, 1341 }, /* glGetMultisamplefvANGLE and glGetMultisamplefv */
        { 1389, 1390 }, /* glGetnUniformfv and glGetnUniformfvEXT */
        { 1389, 1391 }, /* glGetnUniformfv and glGetnUniformfvKHR */
        { 1390, 1389 }, /* glGetnUniformfvEXT and glGetnUniformfv */
        { 1390, 1391 }, /* glGetnUniformfvEXT and glGetnUniformfvKHR */
        { 1391, 1389 }, /* glGetnUniformfvKHR and glGetnUniformfv */
        { 1391, 1390 }, /* glGetnUniformfvKHR and glGetnUniformfvEXT */
        { 1392, 1393 }, /* glGetnUniformiv and glGetnUniformivEXT */
        { 1392, 1394 }, /* glGetnUniformiv and glGetnUniformivKHR */
        { 1393, 1392 }, /* glGetnUniformivEXT and glGetnUniformiv */
        { 1393, 1394 }, /* glGetnUniformivEXT and glGetnUniformivKHR */
        { 1394, 1392 }, /* glGetnUniformivKHR and glGetnUniformiv */
        { 1394, 1393 }, /* glGetnUniformivKHR and glGetnUniformivEXT */
        { 1395, 1396 }, /* glGetnUniformuiv and glGetnUniformuivKHR */
        { 1396, 1395 }, /* glGetnUniformuivKHR and glGetnUniformuiv */
        {  340, 1343 }, /* glGetObjectLabel and glGetObjectLabelKHR */
        { 1343,  340 }, /* glGetObjectLabelKHR and glGetObjectLabel */
        {  343, 1344 }, /* glGetObjectPtrLabel and glGetObjectPtrLabelKHR */
        { 1344,  343 }, /* glGetObjectPtrLabelKHR and glGetObjectPtrLabel */
        {  349,  350 }, /* glGetPointerv and glGetPointervEXT */
        {  349, 1345 }, /* glGetPointerv and glGetPointervKHR */
        {  350,  349 }, /* glGetPointervEXT and glGetPointerv */
        {  350, 1345 }, /* glGetPointervEXT and glGetPointervKHR */
        { 1345,  349 }, /* glGetPointervKHR and glGetPointerv */
        { 1345,  350 }, /* glGetPointervKHR and glGetPointervEXT */
        { 1346, 1347 }, /* glGetProgramBinary and glGetProgramBinaryOES */
        { 1347, 1346 }, /* glGetProgramBinaryOES and glGetProgramBinary */
        {  368,  369 }, /* glGetQueryiv and glGetQueryivARB */
        {  369,  368 }, /* glGetQueryivARB and glGetQueryiv */
        {  364,  365 }, /* glGetQueryObjectiv and glGetQueryObjectivARB */
        {  364, 1358 }, /* glGetQueryObjectiv and glGetQueryObjectivEXT */
        {  365,  364 }, /* glGetQueryObjectivARB and glGetQueryObjectiv */
        {  365, 1358 }, /* glGetQueryObjectivARB and glGetQueryObjectivEXT */
        { 1358,  364 }, /* glGetQueryObjectivEXT and glGetQueryObjectiv */
        { 1358,  365 }, /* glGetQueryObjectivEXT and glGetQueryObjectivARB */
        {  366,  367 }, /* glGetQueryObjectuiv and glGetQueryObjectuivARB */
        {  367,  366 }, /* glGetQueryObjectuivARB and glGetQueryObjectuiv */
        { 1363, 1364 }, /* glGetSamplerParameterIiv and glGetSamplerParameterIivEXT */
        { 1363, 1365 }, /* glGetSamplerParameterIiv and glGetSamplerParameterIivOES */
        { 1364, 1363 }, /* glGetSamplerParameterIivEXT and glGetSamplerParameterIiv */
        { 1364, 1365 }, /* glGetSamplerParameterIivEXT and glGetSamplerParameterIivOES */
        { 1365, 1363 }, /* glGetSamplerParameterIivOES and glGetSamplerParameterIiv */
        { 1365, 1364 }, /* glGetSamplerParameterIivOES and glGetSamplerParameterIivEXT */
        { 1366, 1367 }, /* glGetSamplerParameterIuiv and glGetSamplerParameterIuivEXT */
        { 1366, 1368 }, /* glGetSamplerParameterIuiv and glGetSamplerParameterIuivOES */
        { 1367, 1366 }, /* glGetSamplerParameterIuivEXT and glGetSamplerParameterIuiv */
        { 1367, 1368 }, /* glGetSamplerParameterIuivEXT and glGetSamplerParameterIuivOES */
        { 1368, 1366 }, /* glGetSamplerParameterIuivOES and glGetSamplerParameterIuiv */
        { 1368, 1367 }, /* glGetSamplerParameterIuivOES and glGetSamplerParameterIuivEXT */
        {  372,  373 }, /* glGetShaderSource and glGetShaderSourceARB */
        {  373,  372 }, /* glGetShaderSourceARB and glGetShaderSource */
        { 1373, 1374 }, /* glGetSynciv and glGetSyncivAPPLE */
        { 1374, 1373 }, /* glGetSyncivAPPLE and glGetSynciv */
        {  382, 1375 }, /* glGetTexLevelParameterfv and glGetTexLevelParameterfvANGLE */
        { 1375,  382 }, /* glGetTexLevelParameterfvANGLE and glGetTexLevelParameterfv */
        {  383, 1376 }, /* glGetTexLevelParameteriv and glGetTexLevelParameterivANGLE */
        { 1376,  383 }, /* glGetTexLevelParameterivANGLE and glGetTexLevelParameteriv */
        { 1377, 1378 }, /* glGetTexParameterIiv and glGetTexParameterIivEXT */
        { 1377, 1379 }, /* glGetTexParameterIiv and glGetTexParameterIivOES */
        { 1378, 1377 }, /* glGetTexParameterIivEXT and glGetTexParameterIiv */
        { 1378, 1379 }, /* glGetTexParameterIivEXT and glGetTexParameterIivOES */
        { 1379, 1377 }, /* glGetTexParameterIivOES and glGetTexParameterIiv */
        { 1379, 1378 }, /* glGetTexParameterIivOES and glGetTexParameterIivEXT */
        { 1380, 1381 }, /* glGetTexParameterIuiv and glGetTexParameterIuivEXT */
        { 1380, 1382 }, /* glGetTexParameterIuiv and glGetTexParameterIuivOES */
        { 1381, 1380 }, /* glGetTexParameterIuivEXT and glGetTexParameterIuiv */
        { 1381, 1382 }, /* glGetTexParameterIuivEXT and glGetTexParameterIuivOES */
        { 1382, 1380 }, /* glGetTexParameterIuivOES and glGetTexParameterIuiv */
        { 1382, 1381 }, /* glGetTexParameterIuivOES and glGetTexParameterIuivEXT */
        {  396,  397 }, /* glGetUniformfv and glGetUniformfvARB */
        {  397,  396 }, /* glGetUniformfvARB and glGetUniformfv */
        {  398,  399 }, /* glGetUniformiv and glGetUniformivARB */
        {  399,  398 }, /* glGetUniformivARB and glGetUniformiv */
        {  394,  395 }, /* glGetUniformLocation and glGetUniformLocationARB */
        {  395,  394 }, /* glGetUniformLocationARB and glGetUniformLocation */
        {  407,  408 }, /* glGetVertexAttribdv and glGetVertexAttribdvARB */
        {  407,  409 }, /* glGetVertexAttribdv and glGetVertexAttribdvNV */
        {  408,  407 }, /* glGetVertexAttribdvARB and glGetVertexAttribdv */
        {  408,  409 }, /* glGetVertexAttribdvARB and glGetVertexAttribdvNV */
        {  409,  407 }, /* glGetVertexAttribdvNV and glGetVertexAttribdv */
        {  409,  408 }, /* glGetVertexAttribdvNV and glGetVertexAttribdvARB */
        {  410,  411 }, /* glGetVertexAttribfv and glGetVertexAttribfvARB */
        {  410,  412 }, /* glGetVertexAttribfv and glGetVertexAttribfvNV */
        {  411,  410 }, /* glGetVertexAttribfvARB and glGetVertexAttribfv */
        {  411,  412 }, /* glGetVertexAttribfvARB and glGetVertexAttribfvNV */
        {  412,  410 }, /* glGetVertexAttribfvNV and glGetVertexAttribfv */
        {  412,  411 }, /* glGetVertexAttribfvNV and glGetVertexAttribfvARB */
        {  413,  414 }, /* glGetVertexAttribiv and glGetVertexAttribivARB */
        {  413,  415 }, /* glGetVertexAttribiv and glGetVertexAttribivNV */
        {  414,  413 }, /* glGetVertexAttribivARB and glGetVertexAttribiv */
        {  414,  415 }, /* glGetVertexAttribivARB and glGetVertexAttribivNV */
        {  415,  413 }, /* glGetVertexAttribivNV and glGetVertexAttribiv */
        {  415,  414 }, /* glGetVertexAttribivNV and glGetVertexAttribivARB */
        {  404,  405 }, /* glGetVertexAttribPointerv and glGetVertexAttribPointervARB */
        {  404,  406 }, /* glGetVertexAttribPointerv and glGetVertexAttribPointervNV */
        {  405,  404 }, /* glGetVertexAttribPointervARB and glGetVertexAttribPointerv */
        {  405,  406 }, /* glGetVertexAttribPointervARB and glGetVertexAttribPointervNV */
        {  406,  404 }, /* glGetVertexAttribPointervNV and glGetVertexAttribPointerv */
        {  406,  405 }, /* glGetVertexAttribPointervNV and glGetVertexAttribPointervARB */
        {  433,  434 }, /* glIsBuffer and glIsBufferARB */
        {  434,  433 }, /* glIsBufferARB and glIsBuffer */
        { 1399,  436 }, /* glIsEnabledi and glIsEnabledIndexedEXT */
        { 1399, 1400 }, /* glIsEnabledi and glIsEnablediEXT */
        { 1399, 1401 }, /* glIsEnabledi and glIsEnablediNV */
        { 1399, 1402 }, /* glIsEnabledi and glIsEnablediOES */
        { 1400,  436 }, /* glIsEnablediEXT and glIsEnabledIndexedEXT */
        { 1400, 1399 }, /* glIsEnablediEXT and glIsEnabledi */
        { 1400, 1401 }, /* glIsEnablediEXT and glIsEnablediNV */
        { 1400, 1402 }, /* glIsEnablediEXT and glIsEnablediOES */
        {  436, 1399 }, /* glIsEnabledIndexedEXT and glIsEnabledi */
        {  436, 1400 }, /* glIsEnabledIndexedEXT and glIsEnablediEXT */
        {  436, 1401 }, /* glIsEnabledIndexedEXT and glIsEnablediNV */
        {  436, 1402 }, /* glIsEnabledIndexedEXT and glIsEnablediOES */
        { 1401,  436 }, /* glIsEnablediNV and glIsEnabledIndexedEXT */
        { 1401, 1399 }, /* glIsEnablediNV and glIsEnabledi */
        { 1401, 1400 }, /* glIsEnablediNV and glIsEnablediEXT */
        { 1401, 1402 }, /* glIsEnablediNV and glIsEnablediOES */
        { 1402,  436 }, /* glIsEnablediOES and glIsEnabledIndexedEXT */
        { 1402, 1399 }, /* glIsEnablediOES and glIsEnabledi */
        { 1402, 1400 }, /* glIsEnablediOES and glIsEnablediEXT */
        { 1402, 1401 }, /* glIsEnablediOES and glIsEnablediNV */
        {  439,  440 }, /* glIsProgramARB and glIsProgramNV */
        {  440,  439 }, /* glIsProgramNV and glIsProgramARB */
        {  441,  442 }, /* glIsQuery and glIsQueryARB */
        {  442,  441 }, /* glIsQueryARB and glIsQuery */
        { 1409, 1410 }, /* glIsSync and glIsSyncAPPLE */
        { 1410, 1409 }, /* glIsSyncAPPLE and glIsSync */
        { 1412, 1413 }, /* glIsVertexArray and glIsVertexArrayOES */
        { 1413, 1412 }, /* glIsVertexArrayOES and glIsVertexArray */
        {  456,  457 }, /* glLinkProgram and glLinkProgramARB */
        {  457,  456 }, /* glLinkProgramARB and glLinkProgram */
        {  464,  465 }, /* glLoadTransposeMatrixd and glLoadTransposeMatrixdARB */
        {  465,  464 }, /* glLoadTransposeMatrixdARB and glLoadTransposeMatrixd */
        {  466,  467 }, /* glLoadTransposeMatrixf and glLoadTransposeMatrixfARB */
        {  467,  466 }, /* glLoadTransposeMatrixfARB and glLoadTransposeMatrixf */
        {  473,  474 }, /* glMapBuffer and glMapBufferARB */
        {  473, 1414 }, /* glMapBuffer and glMapBufferOES */
        {  474,  473 }, /* glMapBufferARB and glMapBuffer */
        {  474, 1414 }, /* glMapBufferARB and glMapBufferOES */
        { 1414,  473 }, /* glMapBufferOES and glMapBuffer */
        { 1414,  474 }, /* glMapBufferOES and glMapBufferARB */
        { 1415, 1416 }, /* glMapBufferRange and glMapBufferRangeEXT */
        { 1416, 1415 }, /* glMapBufferRangeEXT and glMapBufferRange */
        { 1419, 1420 }, /* glMinSampleShading and glMinSampleShadingOES */
        { 1420, 1419 }, /* glMinSampleShadingOES and glMinSampleShading */
        {  512,  513 }, /* glMultiDrawArrays and glMultiDrawArraysEXT */
        {  513,  512 }, /* glMultiDrawArraysEXT and glMultiDrawArrays */
        {  514,  515 }, /* glMultiDrawElements and glMultiDrawElementsEXT */
        {  515,  514 }, /* glMultiDrawElementsEXT and glMultiDrawElements */
        {  517,  518 }, /* glMultiTexCoord1d and glMultiTexCoord1dARB */
        {  518,  517 }, /* glMultiTexCoord1dARB and glMultiTexCoord1d */
        {  519,  520 }, /* glMultiTexCoord1dv and glMultiTexCoord1dvARB */
        {  520,  519 }, /* glMultiTexCoord1dvARB and glMultiTexCoord1dv */
        {  521,  522 }, /* glMultiTexCoord1f and glMultiTexCoord1fARB */
        {  522,  521 }, /* glMultiTexCoord1fARB and glMultiTexCoord1f */
        {  523,  524 }, /* glMultiTexCoord1fv and glMultiTexCoord1fvARB */
        {  524,  523 }, /* glMultiTexCoord1fvARB and glMultiTexCoord1fv */
        {  525,  526 }, /* glMultiTexCoord1i and glMultiTexCoord1iARB */
        {  526,  525 }, /* glMultiTexCoord1iARB and glMultiTexCoord1i */
        {  527,  528 }, /* glMultiTexCoord1iv and glMultiTexCoord1ivARB */
        {  528,  527 }, /* glMultiTexCoord1ivARB and glMultiTexCoord1iv */
        {  529,  530 }, /* glMultiTexCoord1s and glMultiTexCoord1sARB */
        {  530,  529 }, /* glMultiTexCoord1sARB and glMultiTexCoord1s */
        {  531,  532 }, /* glMultiTexCoord1sv and glMultiTexCoord1svARB */
        {  532,  531 }, /* glMultiTexCoord1svARB and glMultiTexCoord1sv */
        {  533,  534 }, /* glMultiTexCoord2d and glMultiTexCoord2dARB */
        {  534,  533 }, /* glMultiTexCoord2dARB and glMultiTexCoord2d */
        {  535,  536 }, /* glMultiTexCoord2dv and glMultiTexCoord2dvARB */
        {  536,  535 }, /* glMultiTexCoord2dvARB and glMultiTexCoord2dv */
        {  537,  538 }, /* glMultiTexCoord2f and glMultiTexCoord2fARB */
        {  538,  537 }, /* glMultiTexCoord2fARB and glMultiTexCoord2f */
        {  539,  540 }, /* glMultiTexCoord2fv and glMultiTexCoord2fvARB */
        {  540,  539 }, /* glMultiTexCoord2fvARB and glMultiTexCoord2fv */
        {  541,  542 }, /* glMultiTexCoord2i and glMultiTexCoord2iARB */
        {  542,  541 }, /* glMultiTexCoord2iARB and glMultiTexCoord2i */
        {  543,  544 }, /* glMultiTexCoord2iv and glMultiTexCoord2ivARB */
        {  544,  543 }, /* glMultiTexCoord2ivARB and glMultiTexCoord2iv */
        {  545,  546 }, /* glMultiTexCoord2s and glMultiTexCoord2sARB */
        {  546,  545 }, /* glMultiTexCoord2sARB and glMultiTexCoord2s */
        {  547,  548 }, /* glMultiTexCoord2sv and glMultiTexCoord2svARB */
        {  548,  547 }, /* glMultiTexCoord2svARB and glMultiTexCoord2sv */
        {  549,  550 }, /* glMultiTexCoord3d and glMultiTexCoord3dARB */
        {  550,  549 }, /* glMultiTexCoord3dARB and glMultiTexCoord3d */
        {  551,  552 }, /* glMultiTexCoord3dv and glMultiTexCoord3dvARB */
        {  552,  551 }, /* glMultiTexCoord3dvARB and glMultiTexCoord3dv */
        {  553,  554 }, /* glMultiTexCoord3f and glMultiTexCoord3fARB */
        {  554,  553 }, /* glMultiTexCoord3fARB and glMultiTexCoord3f */
        {  555,  556 }, /* glMultiTexCoord3fv and glMultiTexCoord3fvARB */
        {  556,  555 }, /* glMultiTexCoord3fvARB and glMultiTexCoord3fv */
        {  557,  558 }, /* glMultiTexCoord3i and glMultiTexCoord3iARB */
        {  558,  557 }, /* glMultiTexCoord3iARB and glMultiTexCoord3i */
        {  559,  560 }, /* glMultiTexCoord3iv and glMultiTexCoord3ivARB */
        {  560,  559 }, /* glMultiTexCoord3ivARB and glMultiTexCoord3iv */
        {  561,  562 }, /* glMultiTexCoord3s and glMultiTexCoord3sARB */
        {  562,  561 }, /* glMultiTexCoord3sARB and glMultiTexCoord3s */
        {  563,  564 }, /* glMultiTexCoord3sv and glMultiTexCoord3svARB */
        {  564,  563 }, /* glMultiTexCoord3svARB and glMultiTexCoord3sv */
        {  565,  566 }, /* glMultiTexCoord4d and glMultiTexCoord4dARB */
        {  566,  565 }, /* glMultiTexCoord4dARB and glMultiTexCoord4d */
        {  567,  568 }, /* glMultiTexCoord4dv and glMultiTexCoord4dvARB */
        {  568,  567 }, /* glMultiTexCoord4dvARB and glMultiTexCoord4dv */
        {  569,  570 }, /* glMultiTexCoord4f and glMultiTexCoord4fARB */
        {  570,  569 }, /* glMultiTexCoord4fARB and glMultiTexCoord4f */
        {  571,  572 }, /* glMultiTexCoord4fv and glMultiTexCoord4fvARB */
        {  572,  571 }, /* glMultiTexCoord4fvARB and glMultiTexCoord4fv */
        {  573,  574 }, /* glMultiTexCoord4i and glMultiTexCoord4iARB */
        {  574,  573 }, /* glMultiTexCoord4iARB and glMultiTexCoord4i */
        {  575,  576 }, /* glMultiTexCoord4iv and glMultiTexCoord4ivARB */
        {  576,  575 }, /* glMultiTexCoord4ivARB and glMultiTexCoord4iv */
        {  577,  578 }, /* glMultiTexCoord4s and glMultiTexCoord4sARB */
        {  578,  577 }, /* glMultiTexCoord4sARB and glMultiTexCoord4s */
        {  579,  580 }, /* glMultiTexCoord4sv and glMultiTexCoord4svARB */
        {  580,  579 }, /* glMultiTexCoord4svARB and glMultiTexCoord4sv */
        {  508,  509 }, /* glMultTransposeMatrixd and glMultTransposeMatrixdARB */
        {  509,  508 }, /* glMultTransposeMatrixdARB and glMultTransposeMatrixd */
        {  510,  511 }, /* glMultTransposeMatrixf and glMultTransposeMatrixfARB */
        {  511,  510 }, /* glMultTransposeMatrixfARB and glMultTransposeMatrixf */
        {  645, 1422 }, /* glObjectLabel and glObjectLabelKHR */
        { 1422,  645 }, /* glObjectLabelKHR and glObjectLabel */
        {  646, 1423 }, /* glObjectPtrLabel and glObjectPtrLabelKHR */
        { 1423,  646 }, /* glObjectPtrLabelKHR and glObjectPtrLabel */
        { 1424, 1425 }, /* glPatchParameteri and glPatchParameteriEXT */
        { 1424, 1426 }, /* glPatchParameteri and glPatchParameteriOES */
        { 1425, 1424 }, /* glPatchParameteriEXT and glPatchParameteri */
        { 1425, 1426 }, /* glPatchParameteriEXT and glPatchParameteriOES */
        { 1426, 1424 }, /* glPatchParameteriOES and glPatchParameteri */
        { 1426, 1425 }, /* glPatchParameteriOES and glPatchParameteriEXT */
        {  657,  658 }, /* glPointParameterf and glPointParameterfARB */
        {  657,  659 }, /* glPointParameterf and glPointParameterfEXT */
        {  657,  660 }, /* glPointParameterf and glPointParameterfSGIS */
        {  658,  657 }, /* glPointParameterfARB and glPointParameterf */
        {  658,  659 }, /* glPointParameterfARB and glPointParameterfEXT */
        {  658,  660 }, /* glPointParameterfARB and glPointParameterfSGIS */
        {  659,  657 }, /* glPointParameterfEXT and glPointParameterf */
        {  659,  658 }, /* glPointParameterfEXT and glPointParameterfARB */
        {  659,  660 }, /* glPointParameterfEXT and glPointParameterfSGIS */
        {  660,  657 }, /* glPointParameterfSGIS and glPointParameterf */
        {  660,  658 }, /* glPointParameterfSGIS and glPointParameterfARB */
        {  660,  659 }, /* glPointParameterfSGIS and glPointParameterfEXT */
        {  661,  662 }, /* glPointParameterfv and glPointParameterfvARB */
        {  661,  663 }, /* glPointParameterfv and glPointParameterfvEXT */
        {  661,  664 }, /* glPointParameterfv and glPointParameterfvSGIS */
        {  662,  661 }, /* glPointParameterfvARB and glPointParameterfv */
        {  662,  663 }, /* glPointParameterfvARB and glPointParameterfvEXT */
        {  662,  664 }, /* glPointParameterfvARB and glPointParameterfvSGIS */
        {  663,  661 }, /* glPointParameterfvEXT and glPointParameterfv */
        {  663,  662 }, /* glPointParameterfvEXT and glPointParameterfvARB */
        {  663,  664 }, /* glPointParameterfvEXT and glPointParameterfvSGIS */
        {  664,  661 }, /* glPointParameterfvSGIS and glPointParameterfv */
        {  664,  662 }, /* glPointParameterfvSGIS and glPointParameterfvARB */
        {  664,  663 }, /* glPointParameterfvSGIS and glPointParameterfvEXT */
        {  665,  666 }, /* glPointParameteri and glPointParameteriNV */
        {  666,  665 }, /* glPointParameteriNV and glPointParameteri */
        {  667,  668 }, /* glPointParameteriv and glPointParameterivNV */
        {  668,  667 }, /* glPointParameterivNV and glPointParameteriv */
        {  675, 1428 }, /* glPopDebugGroup and glPopDebugGroupKHR */
        { 1428,  675 }, /* glPopDebugGroupKHR and glPopDebugGroup */
        { 1429, 1430 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxEXT */
        { 1429, 1431 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxOES */
        { 1430, 1429 }, /* glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBox */
        { 1430, 1431 }, /* glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBoxOES */
        { 1431, 1429 }, /* glPrimitiveBoundingBoxOES and glPrimitiveBoundingBox */
        { 1431, 1430 }, /* glPrimitiveBoundingBoxOES and glPrimitiveBoundingBoxEXT */
        {  678,  679 }, /* glPrioritizeTextures and glPrioritizeTexturesEXT */
        {  679,  678 }, /* glPrioritizeTexturesEXT and glPrioritizeTextures */
        { 1432, 1433 }, /* glProgramBinary and glProgramBinaryOES */
        { 1433, 1432 }, /* glProgramBinaryOES and glProgramBinary */
        { 1434, 1435 }, /* glProgramParameteri and glProgramParameteriEXT */
        { 1435, 1434 }, /* glProgramParameteriEXT and glProgramParameteri */
        { 1436,  697 }, /* glProgramUniform1f and glProgramUniform1fEXT */
        {  697, 1436 }, /* glProgramUniform1fEXT and glProgramUniform1f */
        { 1437,  698 }, /* glProgramUniform1fv and glProgramUniform1fvEXT */
        {  698, 1437 }, /* glProgramUniform1fvEXT and glProgramUniform1fv */
        { 1438,  699 }, /* glProgramUniform1i and glProgramUniform1iEXT */
        {  699, 1438 }, /* glProgramUniform1iEXT and glProgramUniform1i */
        { 1439,  700 }, /* glProgramUniform1iv and glProgramUniform1ivEXT */
        {  700, 1439 }, /* glProgramUniform1ivEXT and glProgramUniform1iv */
        { 1440,  701 }, /* glProgramUniform1ui and glProgramUniform1uiEXT */
        {  701, 1440 }, /* glProgramUniform1uiEXT and glProgramUniform1ui */
        { 1441,  702 }, /* glProgramUniform1uiv and glProgramUniform1uivEXT */
        {  702, 1441 }, /* glProgramUniform1uivEXT and glProgramUniform1uiv */
        { 1442,  705 }, /* glProgramUniform2f and glProgramUniform2fEXT */
        {  705, 1442 }, /* glProgramUniform2fEXT and glProgramUniform2f */
        { 1443,  706 }, /* glProgramUniform2fv and glProgramUniform2fvEXT */
        {  706, 1443 }, /* glProgramUniform2fvEXT and glProgramUniform2fv */
        { 1444,  707 }, /* glProgramUniform2i and glProgramUniform2iEXT */
        {  707, 1444 }, /* glProgramUniform2iEXT and glProgramUniform2i */
        { 1445,  708 }, /* glProgramUniform2iv and glProgramUniform2ivEXT */
        {  708, 1445 }, /* glProgramUniform2ivEXT and glProgramUniform2iv */
        { 1446,  709 }, /* glProgramUniform2ui and glProgramUniform2uiEXT */
        {  709, 1446 }, /* glProgramUniform2uiEXT and glProgramUniform2ui */
        { 1447,  710 }, /* glProgramUniform2uiv and glProgramUniform2uivEXT */
        {  710, 1447 }, /* glProgramUniform2uivEXT and glProgramUniform2uiv */
        { 1448,  713 }, /* glProgramUniform3f and glProgramUniform3fEXT */
        {  713, 1448 }, /* glProgramUniform3fEXT and glProgramUniform3f */
        { 1449,  714 }, /* glProgramUniform3fv and glProgramUniform3fvEXT */
        {  714, 1449 }, /* glProgramUniform3fvEXT and glProgramUniform3fv */
        { 1450,  715 }, /* glProgramUniform3i and glProgramUniform3iEXT */
        {  715, 1450 }, /* glProgramUniform3iEXT and glProgramUniform3i */
        { 1451,  716 }, /* glProgramUniform3iv and glProgramUniform3ivEXT */
        {  716, 1451 }, /* glProgramUniform3ivEXT and glProgramUniform3iv */
        { 1452,  717 }, /* glProgramUniform3ui and glProgramUniform3uiEXT */
        {  717, 1452 }, /* glProgramUniform3uiEXT and glProgramUniform3ui */
        { 1453,  718 }, /* glProgramUniform3uiv and glProgramUniform3uivEXT */
        {  718, 1453 }, /* glProgramUniform3uivEXT and glProgramUniform3uiv */
        { 1454,  721 }, /* glProgramUniform4f and glProgramUniform4fEXT */
        {  721, 1454 }, /* glProgramUniform4fEXT and glProgramUniform4f */
        { 1455,  722 }, /* glProgramUniform4fv and glProgramUniform4fvEXT */
        {  722, 1455 }, /* glProgramUniform4fvEXT and glProgramUniform4fv */
        { 1456,  723 }, /* glProgramUniform4i and glProgramUniform4iEXT */
        {  723, 1456 }, /* glProgramUniform4iEXT and glProgramUniform4i */
        { 1457,  724 }, /* glProgramUniform4iv and glProgramUniform4ivEXT */
        {  724, 1457 }, /* glProgramUniform4ivEXT and glProgramUniform4iv */
        { 1458,  725 }, /* glProgramUniform4ui and glProgramUniform4uiEXT */
        {  725, 1458 }, /* glProgramUniform4uiEXT and glProgramUniform4ui */
        { 1459,  726 }, /* glProgramUniform4uiv and glProgramUniform4uivEXT */
        {  726, 1459 }, /* glProgramUniform4uivEXT and glProgramUniform4uiv */
        { 1460,  728 }, /* glProgramUniformMatrix2fv and glProgramUniformMatrix2fvEXT */
        {  728, 1460 }, /* glProgramUniformMatrix2fvEXT and glProgramUniformMatrix2fv */
        { 1461,  730 }, /* glProgramUniformMatrix2x3fv and glProgramUniformMatrix2x3fvEXT */
        {  730, 1461 }, /* glProgramUniformMatrix2x3fvEXT and glProgramUniformMatrix2x3fv */
        { 1462,  732 }, /* glProgramUniformMatrix2x4fv and glProgramUniformMatrix2x4fvEXT */
        {  732, 1462 }, /* glProgramUniformMatrix2x4fvEXT and glProgramUniformMatrix2x4fv */
        { 1463,  734 }, /* glProgramUniformMatrix3fv and glProgramUniformMatrix3fvEXT */
        {  734, 1463 }, /* glProgramUniformMatrix3fvEXT and glProgramUniformMatrix3fv */
        { 1464,  736 }, /* glProgramUniformMatrix3x2fv and glProgramUniformMatrix3x2fvEXT */
        {  736, 1464 }, /* glProgramUniformMatrix3x2fvEXT and glProgramUniformMatrix3x2fv */
        { 1465,  738 }, /* glProgramUniformMatrix3x4fv and glProgramUniformMatrix3x4fvEXT */
        {  738, 1465 }, /* glProgramUniformMatrix3x4fvEXT and glProgramUniformMatrix3x4fv */
        { 1466,  740 }, /* glProgramUniformMatrix4fv and glProgramUniformMatrix4fvEXT */
        {  740, 1466 }, /* glProgramUniformMatrix4fvEXT and glProgramUniformMatrix4fv */
        { 1467,  742 }, /* glProgramUniformMatrix4x2fv and glProgramUniformMatrix4x2fvEXT */
        {  742, 1467 }, /* glProgramUniformMatrix4x2fvEXT and glProgramUniformMatrix4x2fv */
        { 1468,  744 }, /* glProgramUniformMatrix4x3fv and glProgramUniformMatrix4x3fvEXT */
        {  744, 1468 }, /* glProgramUniformMatrix4x3fvEXT and glProgramUniformMatrix4x3fv */
        {  748, 1469 }, /* glPushDebugGroup and glPushDebugGroupKHR */
        { 1469,  748 }, /* glPushDebugGroupKHR and glPushDebugGroup */
        { 1471, 1472 }, /* glReadnPixels and glReadnPixelsEXT */
        { 1471, 1473 }, /* glReadnPixels and glReadnPixelsKHR */
        { 1472, 1471 }, /* glReadnPixelsEXT and glReadnPixels */
        { 1472, 1473 }, /* glReadnPixelsEXT and glReadnPixelsKHR */
        { 1473, 1471 }, /* glReadnPixelsKHR and glReadnPixels */
        { 1473, 1472 }, /* glReadnPixelsKHR and glReadnPixelsEXT */
        { 1476, 1477 }, /* glRenderbufferStorageMultisample and glRenderbufferStorageMultisampleEXT */
        { 1476, 1478 }, /* glRenderbufferStorageMultisample and glRenderbufferStorageMultisampleNV */
        { 1477, 1476 }, /* glRenderbufferStorageMultisampleEXT and glRenderbufferStorageMultisample */
        { 1477, 1478 }, /* glRenderbufferStorageMultisampleEXT and glRenderbufferStorageMultisampleNV */
        { 1478, 1476 }, /* glRenderbufferStorageMultisampleNV and glRenderbufferStorageMultisample */
        { 1478, 1477 }, /* glRenderbufferStorageMultisampleNV and glRenderbufferStorageMultisampleEXT */
        {  791,  792 }, /* glSampleCoverage and glSampleCoverageARB */
        {  792,  791 }, /* glSampleCoverageARB and glSampleCoverage */
        { 1480, 1481 }, /* glSampleMaski and glSampleMaskiANGLE */
        { 1481, 1480 }, /* glSampleMaskiANGLE and glSampleMaski */
        { 1482, 1483 }, /* glSamplerParameterIiv and glSamplerParameterIivEXT */
        { 1482, 1484 }, /* glSamplerParameterIiv and glSamplerParameterIivOES */
        { 1483, 1482 }, /* glSamplerParameterIivEXT and glSamplerParameterIiv */
        { 1483, 1484 }, /* glSamplerParameterIivEXT and glSamplerParameterIivOES */
        { 1484, 1482 }, /* glSamplerParameterIivOES and glSamplerParameterIiv */
        { 1484, 1483 }, /* glSamplerParameterIivOES and glSamplerParameterIivEXT */
        { 1485, 1486 }, /* glSamplerParameterIuiv and glSamplerParameterIuivEXT */
        { 1485, 1487 }, /* glSamplerParameterIuiv and glSamplerParameterIuivOES */
        { 1486, 1485 }, /* glSamplerParameterIuivEXT and glSamplerParameterIuiv */
        { 1486, 1487 }, /* glSamplerParameterIuivEXT and glSamplerParameterIuivOES */
        { 1487, 1485 }, /* glSamplerParameterIuivOES and glSamplerParameterIuiv */
        { 1487, 1486 }, /* glSamplerParameterIuivOES and glSamplerParameterIuivEXT */
        {  796,  797 }, /* glSecondaryColor3b and glSecondaryColor3bEXT */
        {  797,  796 }, /* glSecondaryColor3bEXT and glSecondaryColor3b */
        {  798,  799 }, /* glSecondaryColor3bv and glSecondaryColor3bvEXT */
        {  799,  798 }, /* glSecondaryColor3bvEXT and glSecondaryColor3bv */
        {  800,  801 }, /* glSecondaryColor3d and glSecondaryColor3dEXT */
        {  801,  800 }, /* glSecondaryColor3dEXT and glSecondaryColor3d */
        {  802,  803 }, /* glSecondaryColor3dv and glSecondaryColor3dvEXT */
        {  803,  802 }, /* glSecondaryColor3dvEXT and glSecondaryColor3dv */
        {  804,  805 }, /* glSecondaryColor3f and glSecondaryColor3fEXT */
        {  805,  804 }, /* glSecondaryColor3fEXT and glSecondaryColor3f */
        {  806,  807 }, /* glSecondaryColor3fv and glSecondaryColor3fvEXT */
        {  807,  806 }, /* glSecondaryColor3fvEXT and glSecondaryColor3fv */
        {  808,  809 }, /* glSecondaryColor3i and glSecondaryColor3iEXT */
        {  809,  808 }, /* glSecondaryColor3iEXT and glSecondaryColor3i */
        {  810,  811 }, /* glSecondaryColor3iv and glSecondaryColor3ivEXT */
        {  811,  810 }, /* glSecondaryColor3ivEXT and glSecondaryColor3iv */
        {  812,  813 }, /* glSecondaryColor3s and glSecondaryColor3sEXT */
        {  813,  812 }, /* glSecondaryColor3sEXT and glSecondaryColor3s */
        {  814,  815 }, /* glSecondaryColor3sv and glSecondaryColor3svEXT */
        {  815,  814 }, /* glSecondaryColor3svEXT and glSecondaryColor3sv */
        {  816,  817 }, /* glSecondaryColor3ub and glSecondaryColor3ubEXT */
        {  817,  816 }, /* glSecondaryColor3ubEXT and glSecondaryColor3ub */
        {  818,  819 }, /* glSecondaryColor3ubv and glSecondaryColor3ubvEXT */
        {  819,  818 }, /* glSecondaryColor3ubvEXT and glSecondaryColor3ubv */
        {  820,  821 }, /* glSecondaryColor3ui and glSecondaryColor3uiEXT */
        {  821,  820 }, /* glSecondaryColor3uiEXT and glSecondaryColor3ui */
        {  822,  823 }, /* glSecondaryColor3uiv and glSecondaryColor3uivEXT */
        {  823,  822 }, /* glSecondaryColor3uivEXT and glSecondaryColor3uiv */
        {  824,  825 }, /* glSecondaryColor3us and glSecondaryColor3usEXT */
        {  825,  824 }, /* glSecondaryColor3usEXT and glSecondaryColor3us */
        {  826,  827 }, /* glSecondaryColor3usv and glSecondaryColor3usvEXT */
        {  827,  826 }, /* glSecondaryColor3usvEXT and glSecondaryColor3usv */
        {  828,  829 }, /* glSecondaryColorPointer and glSecondaryColorPointerEXT */
        {  829,  828 }, /* glSecondaryColorPointerEXT and glSecondaryColorPointer */
        {  833,  834 }, /* glShaderSource and glShaderSourceARB */
        {  834,  833 }, /* glShaderSourceARB and glShaderSource */
        {  841,  842 }, /* glStencilOpSeparate and glStencilOpSeparateATI */
        {  842,  841 }, /* glStencilOpSeparateATI and glStencilOpSeparate */
        { 1499, 1500 }, /* glTexBuffer and glTexBufferEXT */
        { 1499, 1501 }, /* glTexBuffer and glTexBufferOES */
        { 1500, 1499 }, /* glTexBufferEXT and glTexBuffer */
        { 1500, 1501 }, /* glTexBufferEXT and glTexBufferOES */
        { 1501, 1499 }, /* glTexBufferOES and glTexBuffer */
        { 1501, 1500 }, /* glTexBufferOES and glTexBufferEXT */
        { 1502, 1503 }, /* glTexBufferRange and glTexBufferRangeEXT */
        { 1502, 1504 }, /* glTexBufferRange and glTexBufferRangeOES */
        { 1503, 1502 }, /* glTexBufferRangeEXT and glTexBufferRange */
        { 1503, 1504 }, /* glTexBufferRangeEXT and glTexBufferRangeOES */
        { 1504, 1502 }, /* glTexBufferRangeOES and glTexBufferRange */
        { 1504, 1503 }, /* glTexBufferRangeOES and glTexBufferRangeEXT */
        {  889,  890 }, /* glTexImage3D and glTexImage3DEXT */
        {  890,  889 }, /* glTexImage3DEXT and glTexImage3D */
        { 1505, 1506 }, /* glTexParameterIiv and glTexParameterIivEXT */
        { 1505, 1507 }, /* glTexParameterIiv and glTexParameterIivOES */
        { 1506, 1505 }, /* glTexParameterIivEXT and glTexParameterIiv */
        { 1506, 1507 }, /* glTexParameterIivEXT and glTexParameterIivOES */
        { 1507, 1505 }, /* glTexParameterIivOES and glTexParameterIiv */
        { 1507, 1506 }, /* glTexParameterIivOES and glTexParameterIivEXT */
        { 1508, 1509 }, /* glTexParameterIuiv and glTexParameterIuivEXT */
        { 1508, 1510 }, /* glTexParameterIuiv and glTexParameterIuivOES */
        { 1509, 1508 }, /* glTexParameterIuivEXT and glTexParameterIuiv */
        { 1509, 1510 }, /* glTexParameterIuivEXT and glTexParameterIuivOES */
        { 1510, 1508 }, /* glTexParameterIuivOES and glTexParameterIuiv */
        { 1510, 1509 }, /* glTexParameterIuivOES and glTexParameterIuivEXT */
        { 1511,  896 }, /* glTexStorage2D and glTexStorage2DEXT */
        {  896, 1511 }, /* glTexStorage2DEXT and glTexStorage2D */
        { 1512, 1513 }, /* glTexStorage2DMultisample and glTexStorage2DMultisampleANGLE */
        { 1513, 1512 }, /* glTexStorage2DMultisampleANGLE and glTexStorage2DMultisample */
        { 1514,  897 }, /* glTexStorage3D and glTexStorage3DEXT */
        {  897, 1514 }, /* glTexStorage3DEXT and glTexStorage3D */
        { 1515, 1516 }, /* glTexStorage3DMultisample and glTexStorage3DMultisampleOES */
        { 1516, 1515 }, /* glTexStorage3DMultisampleOES and glTexStorage3DMultisample */
        {  898,  899 }, /* glTexSubImage1D and glTexSubImage1DEXT */
        {  899,  898 }, /* glTexSubImage1DEXT and glTexSubImage1D */
        {  900,  901 }, /* glTexSubImage2D and glTexSubImage2DEXT */
        {  901,  900 }, /* glTexSubImage2DEXT and glTexSubImage2D */
        {  902,  903 }, /* glTexSubImage3D and glTexSubImage3DEXT */
        {  903,  902 }, /* glTexSubImage3DEXT and glTexSubImage3D */
        {  928,  929 }, /* glUniform1f and glUniform1fARB */
        {  929,  928 }, /* glUniform1fARB and glUniform1f */
        {  930,  931 }, /* glUniform1fv and glUniform1fvARB */
        {  931,  930 }, /* glUniform1fvARB and glUniform1fv */
        {  932,  933 }, /* glUniform1i and glUniform1iARB */
        {  933,  932 }, /* glUniform1iARB and glUniform1i */
        {  934,  935 }, /* glUniform1iv and glUniform1ivARB */
        {  935,  934 }, /* glUniform1ivARB and glUniform1iv */
        {  936,  937 }, /* glUniform2f and glUniform2fARB */
        {  937,  936 }, /* glUniform2fARB and glUniform2f */
        {  938,  939 }, /* glUniform2fv and glUniform2fvARB */
        {  939,  938 }, /* glUniform2fvARB and glUniform2fv */
        {  940,  941 }, /* glUniform2i and glUniform2iARB */
        {  941,  940 }, /* glUniform2iARB and glUniform2i */
        {  942,  943 }, /* glUniform2iv and glUniform2ivARB */
        {  943,  942 }, /* glUniform2ivARB and glUniform2iv */
        {  944,  945 }, /* glUniform3f and glUniform3fARB */
        {  945,  944 }, /* glUniform3fARB and glUniform3f */
        {  946,  947 }, /* glUniform3fv and glUniform3fvARB */
        {  947,  946 }, /* glUniform3fvARB and glUniform3fv */
        {  948,  949 }, /* glUniform3i and glUniform3iARB */
        {  949,  948 }, /* glUniform3iARB and glUniform3i */
        {  950,  951 }, /* glUniform3iv and glUniform3ivARB */
        {  951,  950 }, /* glUniform3ivARB and glUniform3iv */
        {  952,  953 }, /* glUniform4f and glUniform4fARB */
        {  953,  952 }, /* glUniform4fARB and glUniform4f */
        {  954,  955 }, /* glUniform4fv and glUniform4fvARB */
        {  955,  954 }, /* glUniform4fvARB and glUniform4fv */
        {  956,  957 }, /* glUniform4i and glUniform4iARB */
        {  957,  956 }, /* glUniform4iARB and glUniform4i */
        {  958,  959 }, /* glUniform4iv and glUniform4ivARB */
        {  959,  958 }, /* glUniform4ivARB and glUniform4iv */
        {  960,  961 }, /* glUniformMatrix2fv and glUniformMatrix2fvARB */
        {  961,  960 }, /* glUniformMatrix2fvARB and glUniformMatrix2fv */
        {  962, 1527 }, /* glUniformMatrix2x3fv and glUniformMatrix2x3fvNV */
        { 1527,  962 }, /* glUniformMatrix2x3fvNV and glUniformMatrix2x3fv */
        {  963, 1528 }, /* glUniformMatrix2x4fv and glUniformMatrix2x4fvNV */
        { 1528,  963 }, /* glUniformMatrix2x4fvNV and glUniformMatrix2x4fv */
        {  964,  965 }, /* glUniformMatrix3fv and glUniformMatrix3fvARB */
        {  965,  964 }, /* glUniformMatrix3fvARB and glUniformMatrix3fv */
        {  966, 1529 }, /* glUniformMatrix3x2fv and glUniformMatrix3x2fvNV */
        { 1529,  966 }, /* glUniformMatrix3x2fvNV and glUniformMatrix3x2fv */
        {  967, 1530 }, /* glUniformMatrix3x4fv and glUniformMatrix3x4fvNV */
        { 1530,  967 }, /* glUniformMatrix3x4fvNV and glUniformMatrix3x4fv */
        {  968,  969 }, /* glUniformMatrix4fv and glUniformMatrix4fvARB */
        {  969,  968 }, /* glUniformMatrix4fvARB and glUniformMatrix4fv */
        {  970, 1531 }, /* glUniformMatrix4x2fv and glUniformMatrix4x2fvNV */
        { 1531,  970 }, /* glUniformMatrix4x2fvNV and glUniformMatrix4x2fv */
        {  971, 1532 }, /* glUniformMatrix4x3fv and glUniformMatrix4x3fvNV */
        { 1532,  971 }, /* glUniformMatrix4x3fvNV and glUniformMatrix4x3fv */
        {  972,  973 }, /* glUnmapBuffer and glUnmapBufferARB */
        {  972, 1533 }, /* glUnmapBuffer and glUnmapBufferOES */
        {  973,  972 }, /* glUnmapBufferARB and glUnmapBuffer */
        {  973, 1533 }, /* glUnmapBufferARB and glUnmapBufferOES */
        { 1533,  972 }, /* glUnmapBufferOES and glUnmapBuffer */
        { 1533,  973 }, /* glUnmapBufferOES and glUnmapBufferARB */
        {  975,  976 }, /* glUseProgram and glUseProgramObjectARB */
        {  976,  975 }, /* glUseProgramObjectARB and glUseProgram */
        {  977,  978 }, /* glValidateProgram and glValidateProgramARB */
        {  978,  977 }, /* glValidateProgramARB and glValidateProgram */
        { 1022, 1023 }, /* glVertexAttrib1d and glVertexAttrib1dARB */
        { 1022, 1024 }, /* glVertexAttrib1d and glVertexAttrib1dNV */
        { 1023, 1022 }, /* glVertexAttrib1dARB and glVertexAttrib1d */
        { 1023, 1024 }, /* glVertexAttrib1dARB and glVertexAttrib1dNV */
        { 1024, 1022 }, /* glVertexAttrib1dNV and glVertexAttrib1d */
        { 1024, 1023 }, /* glVertexAttrib1dNV and glVertexAttrib1dARB */
        { 1025, 1026 }, /* glVertexAttrib1dv and glVertexAttrib1dvARB */
        { 1025, 1027 }, /* glVertexAttrib1dv and glVertexAttrib1dvNV */
        { 1026, 1025 }, /* glVertexAttrib1dvARB and glVertexAttrib1dv */
        { 1026, 1027 }, /* glVertexAttrib1dvARB and glVertexAttrib1dvNV */
        { 1027, 1025 }, /* glVertexAttrib1dvNV and glVertexAttrib1dv */
        { 1027, 1026 }, /* glVertexAttrib1dvNV and glVertexAttrib1dvARB */
        { 1028, 1029 }, /* glVertexAttrib1f and glVertexAttrib1fARB */
        { 1028, 1030 }, /* glVertexAttrib1f and glVertexAttrib1fNV */
        { 1029, 1028 }, /* glVertexAttrib1fARB and glVertexAttrib1f */
        { 1029, 1030 }, /* glVertexAttrib1fARB and glVertexAttrib1fNV */
        { 1030, 1028 }, /* glVertexAttrib1fNV and glVertexAttrib1f */
        { 1030, 1029 }, /* glVertexAttrib1fNV and glVertexAttrib1fARB */
        { 1031, 1032 }, /* glVertexAttrib1fv and glVertexAttrib1fvARB */
        { 1031, 1033 }, /* glVertexAttrib1fv and glVertexAttrib1fvNV */
        { 1032, 1031 }, /* glVertexAttrib1fvARB and glVertexAttrib1fv */
        { 1032, 1033 }, /* glVertexAttrib1fvARB and glVertexAttrib1fvNV */
        { 1033, 1031 }, /* glVertexAttrib1fvNV and glVertexAttrib1fv */
        { 1033, 1032 }, /* glVertexAttrib1fvNV and glVertexAttrib1fvARB */
        { 1034, 1035 }, /* glVertexAttrib1s and glVertexAttrib1sARB */
        { 1034, 1036 }, /* glVertexAttrib1s and glVertexAttrib1sNV */
        { 1035, 1034 }, /* glVertexAttrib1sARB and glVertexAttrib1s */
        { 1035, 1036 }, /* glVertexAttrib1sARB and glVertexAttrib1sNV */
        { 1036, 1034 }, /* glVertexAttrib1sNV and glVertexAttrib1s */
        { 1036, 1035 }, /* glVertexAttrib1sNV and glVertexAttrib1sARB */
        { 1037, 1038 }, /* glVertexAttrib1sv and glVertexAttrib1svARB */
        { 1037, 1039 }, /* glVertexAttrib1sv and glVertexAttrib1svNV */
        { 1038, 1037 }, /* glVertexAttrib1svARB and glVertexAttrib1sv */
        { 1038, 1039 }, /* glVertexAttrib1svARB and glVertexAttrib1svNV */
        { 1039, 1037 }, /* glVertexAttrib1svNV and glVertexAttrib1sv */
        { 1039, 1038 }, /* glVertexAttrib1svNV and glVertexAttrib1svARB */
        { 1040, 1041 }, /* glVertexAttrib2d and glVertexAttrib2dARB */
        { 1040, 1042 }, /* glVertexAttrib2d and glVertexAttrib2dNV */
        { 1041, 1040 }, /* glVertexAttrib2dARB and glVertexAttrib2d */
        { 1041, 1042 }, /* glVertexAttrib2dARB and glVertexAttrib2dNV */
        { 1042, 1040 }, /* glVertexAttrib2dNV and glVertexAttrib2d */
        { 1042, 1041 }, /* glVertexAttrib2dNV and glVertexAttrib2dARB */
        { 1043, 1044 }, /* glVertexAttrib2dv and glVertexAttrib2dvARB */
        { 1043, 1045 }, /* glVertexAttrib2dv and glVertexAttrib2dvNV */
        { 1044, 1043 }, /* glVertexAttrib2dvARB and glVertexAttrib2dv */
        { 1044, 1045 }, /* glVertexAttrib2dvARB and glVertexAttrib2dvNV */
        { 1045, 1043 }, /* glVertexAttrib2dvNV and glVertexAttrib2dv */
        { 1045, 1044 }, /* glVertexAttrib2dvNV and glVertexAttrib2dvARB */
        { 1046, 1047 }, /* glVertexAttrib2f and glVertexAttrib2fARB */
        { 1046, 1048 }, /* glVertexAttrib2f and glVertexAttrib2fNV */
        { 1047, 1046 }, /* glVertexAttrib2fARB and glVertexAttrib2f */
        { 1047, 1048 }, /* glVertexAttrib2fARB and glVertexAttrib2fNV */
        { 1048, 1046 }, /* glVertexAttrib2fNV and glVertexAttrib2f */
        { 1048, 1047 }, /* glVertexAttrib2fNV and glVertexAttrib2fARB */
        { 1049, 1050 }, /* glVertexAttrib2fv and glVertexAttrib2fvARB */
        { 1049, 1051 }, /* glVertexAttrib2fv and glVertexAttrib2fvNV */
        { 1050, 1049 }, /* glVertexAttrib2fvARB and glVertexAttrib2fv */
        { 1050, 1051 }, /* glVertexAttrib2fvARB and glVertexAttrib2fvNV */
        { 1051, 1049 }, /* glVertexAttrib2fvNV and glVertexAttrib2fv */
        { 1051, 1050 }, /* glVertexAttrib2fvNV and glVertexAttrib2fvARB */
        { 1052, 1053 }, /* glVertexAttrib2s and glVertexAttrib2sARB */
        { 1052, 1054 }, /* glVertexAttrib2s and glVertexAttrib2sNV */
        { 1053, 1052 }, /* glVertexAttrib2sARB and glVertexAttrib2s */
        { 1053, 1054 }, /* glVertexAttrib2sARB and glVertexAttrib2sNV */
        { 1054, 1052 }, /* glVertexAttrib2sNV and glVertexAttrib2s */
        { 1054, 1053 }, /* glVertexAttrib2sNV and glVertexAttrib2sARB */
        { 1055, 1056 }, /* glVertexAttrib2sv and glVertexAttrib2svARB */
        { 1055, 1057 }, /* glVertexAttrib2sv and glVertexAttrib2svNV */
        { 1056, 1055 }, /* glVertexAttrib2svARB and glVertexAttrib2sv */
        { 1056, 1057 }, /* glVertexAttrib2svARB and glVertexAttrib2svNV */
        { 1057, 1055 }, /* glVertexAttrib2svNV and glVertexAttrib2sv */
        { 1057, 1056 }, /* glVertexAttrib2svNV and glVertexAttrib2svARB */
        { 1058, 1059 }, /* glVertexAttrib3d and glVertexAttrib3dARB */
        { 1058, 1060 }, /* glVertexAttrib3d and glVertexAttrib3dNV */
        { 1059, 1058 }, /* glVertexAttrib3dARB and glVertexAttrib3d */
        { 1059, 1060 }, /* glVertexAttrib3dARB and glVertexAttrib3dNV */
        { 1060, 1058 }, /* glVertexAttrib3dNV and glVertexAttrib3d */
        { 1060, 1059 }, /* glVertexAttrib3dNV and glVertexAttrib3dARB */
        { 1061, 1062 }, /* glVertexAttrib3dv and glVertexAttrib3dvARB */
        { 1061, 1063 }, /* glVertexAttrib3dv and glVertexAttrib3dvNV */
        { 1062, 1061 }, /* glVertexAttrib3dvARB and glVertexAttrib3dv */
        { 1062, 1063 }, /* glVertexAttrib3dvARB and glVertexAttrib3dvNV */
        { 1063, 1061 }, /* glVertexAttrib3dvNV and glVertexAttrib3dv */
        { 1063, 1062 }, /* glVertexAttrib3dvNV and glVertexAttrib3dvARB */
        { 1064, 1065 }, /* glVertexAttrib3f and glVertexAttrib3fARB */
        { 1064, 1066 }, /* glVertexAttrib3f and glVertexAttrib3fNV */
        { 1065, 1064 }, /* glVertexAttrib3fARB and glVertexAttrib3f */
        { 1065, 1066 }, /* glVertexAttrib3fARB and glVertexAttrib3fNV */
        { 1066, 1064 }, /* glVertexAttrib3fNV and glVertexAttrib3f */
        { 1066, 1065 }, /* glVertexAttrib3fNV and glVertexAttrib3fARB */
        { 1067, 1068 }, /* glVertexAttrib3fv and glVertexAttrib3fvARB */
        { 1067, 1069 }, /* glVertexAttrib3fv and glVertexAttrib3fvNV */
        { 1068, 1067 }, /* glVertexAttrib3fvARB and glVertexAttrib3fv */
        { 1068, 1069 }, /* glVertexAttrib3fvARB and glVertexAttrib3fvNV */
        { 1069, 1067 }, /* glVertexAttrib3fvNV and glVertexAttrib3fv */
        { 1069, 1068 }, /* glVertexAttrib3fvNV and glVertexAttrib3fvARB */
        { 1070, 1071 }, /* glVertexAttrib3s and glVertexAttrib3sARB */
        { 1070, 1072 }, /* glVertexAttrib3s and glVertexAttrib3sNV */
        { 1071, 1070 }, /* glVertexAttrib3sARB and glVertexAttrib3s */
        { 1071, 1072 }, /* glVertexAttrib3sARB and glVertexAttrib3sNV */
        { 1072, 1070 }, /* glVertexAttrib3sNV and glVertexAttrib3s */
        { 1072, 1071 }, /* glVertexAttrib3sNV and glVertexAttrib3sARB */
        { 1073, 1074 }, /* glVertexAttrib3sv and glVertexAttrib3svARB */
        { 1073, 1075 }, /* glVertexAttrib3sv and glVertexAttrib3svNV */
        { 1074, 1073 }, /* glVertexAttrib3svARB and glVertexAttrib3sv */
        { 1074, 1075 }, /* glVertexAttrib3svARB and glVertexAttrib3svNV */
        { 1075, 1073 }, /* glVertexAttrib3svNV and glVertexAttrib3sv */
        { 1075, 1074 }, /* glVertexAttrib3svNV and glVertexAttrib3svARB */
        { 1090, 1091 }, /* glVertexAttrib4bv and glVertexAttrib4bvARB */
        { 1091, 1090 }, /* glVertexAttrib4bvARB and glVertexAttrib4bv */
        { 1092, 1093 }, /* glVertexAttrib4d and glVertexAttrib4dARB */
        { 1092, 1094 }, /* glVertexAttrib4d and glVertexAttrib4dNV */
        { 1093, 1092 }, /* glVertexAttrib4dARB and glVertexAttrib4d */
        { 1093, 1094 }, /* glVertexAttrib4dARB and glVertexAttrib4dNV */
        { 1094, 1092 }, /* glVertexAttrib4dNV and glVertexAttrib4d */
        { 1094, 1093 }, /* glVertexAttrib4dNV and glVertexAttrib4dARB */
        { 1095, 1096 }, /* glVertexAttrib4dv and glVertexAttrib4dvARB */
        { 1095, 1097 }, /* glVertexAttrib4dv and glVertexAttrib4dvNV */
        { 1096, 1095 }, /* glVertexAttrib4dvARB and glVertexAttrib4dv */
        { 1096, 1097 }, /* glVertexAttrib4dvARB and glVertexAttrib4dvNV */
        { 1097, 1095 }, /* glVertexAttrib4dvNV and glVertexAttrib4dv */
        { 1097, 1096 }, /* glVertexAttrib4dvNV and glVertexAttrib4dvARB */
        { 1098, 1099 }, /* glVertexAttrib4f and glVertexAttrib4fARB */
        { 1098, 1100 }, /* glVertexAttrib4f and glVertexAttrib4fNV */
        { 1099, 1098 }, /* glVertexAttrib4fARB and glVertexAttrib4f */
        { 1099, 1100 }, /* glVertexAttrib4fARB and glVertexAttrib4fNV */
        { 1100, 1098 }, /* glVertexAttrib4fNV and glVertexAttrib4f */
        { 1100, 1099 }, /* glVertexAttrib4fNV and glVertexAttrib4fARB */
        { 1101, 1102 }, /* glVertexAttrib4fv and glVertexAttrib4fvARB */
        { 1101, 1103 }, /* glVertexAttrib4fv and glVertexAttrib4fvNV */
        { 1102, 1101 }, /* glVertexAttrib4fvARB and glVertexAttrib4fv */
        { 1102, 1103 }, /* glVertexAttrib4fvARB and glVertexAttrib4fvNV */
        { 1103, 1101 }, /* glVertexAttrib4fvNV and glVertexAttrib4fv */
        { 1103, 1102 }, /* glVertexAttrib4fvNV and glVertexAttrib4fvARB */
        { 1104, 1105 }, /* glVertexAttrib4iv and glVertexAttrib4ivARB */
        { 1105, 1104 }, /* glVertexAttrib4ivARB and glVertexAttrib4iv */
        { 1076, 1077 }, /* glVertexAttrib4Nbv and glVertexAttrib4NbvARB */
        { 1077, 1076 }, /* glVertexAttrib4NbvARB and glVertexAttrib4Nbv */
        { 1078, 1079 }, /* glVertexAttrib4Niv and glVertexAttrib4NivARB */
        { 1079, 1078 }, /* glVertexAttrib4NivARB and glVertexAttrib4Niv */
        { 1080, 1081 }, /* glVertexAttrib4Nsv and glVertexAttrib4NsvARB */
        { 1081, 1080 }, /* glVertexAttrib4NsvARB and glVertexAttrib4Nsv */
        { 1082, 1083 }, /* glVertexAttrib4Nub and glVertexAttrib4NubARB */
        { 1082, 1112 }, /* glVertexAttrib4Nub and glVertexAttrib4ubNV */
        { 1083, 1082 }, /* glVertexAttrib4NubARB and glVertexAttrib4Nub */
        { 1083, 1112 }, /* glVertexAttrib4NubARB and glVertexAttrib4ubNV */
        { 1084, 1085 }, /* glVertexAttrib4Nubv and glVertexAttrib4NubvARB */
        { 1084, 1115 }, /* glVertexAttrib4Nubv and glVertexAttrib4ubvNV */
        { 1085, 1084 }, /* glVertexAttrib4NubvARB and glVertexAttrib4Nubv */
        { 1085, 1115 }, /* glVertexAttrib4NubvARB and glVertexAttrib4ubvNV */
        { 1086, 1087 }, /* glVertexAttrib4Nuiv and glVertexAttrib4NuivARB */
        { 1087, 1086 }, /* glVertexAttrib4NuivARB and glVertexAttrib4Nuiv */
        { 1088, 1089 }, /* glVertexAttrib4Nusv and glVertexAttrib4NusvARB */
        { 1089, 1088 }, /* glVertexAttrib4NusvARB and glVertexAttrib4Nusv */
        { 1106, 1107 }, /* glVertexAttrib4s and glVertexAttrib4sARB */
        { 1106, 1108 }, /* glVertexAttrib4s and glVertexAttrib4sNV */
        { 1107, 1106 }, /* glVertexAttrib4sARB and glVertexAttrib4s */
        { 1107, 1108 }, /* glVertexAttrib4sARB and glVertexAttrib4sNV */
        { 1108, 1106 }, /* glVertexAttrib4sNV and glVertexAttrib4s */
        { 1108, 1107 }, /* glVertexAttrib4sNV and glVertexAttrib4sARB */
        { 1109, 1110 }, /* glVertexAttrib4sv and glVertexAttrib4svARB */
        { 1109, 1111 }, /* glVertexAttrib4sv and glVertexAttrib4svNV */
        { 1110, 1109 }, /* glVertexAttrib4svARB and glVertexAttrib4sv */
        { 1110, 1111 }, /* glVertexAttrib4svARB and glVertexAttrib4svNV */
        { 1111, 1109 }, /* glVertexAttrib4svNV and glVertexAttrib4sv */
        { 1111, 1110 }, /* glVertexAttrib4svNV and glVertexAttrib4svARB */
        { 1112, 1082 }, /* glVertexAttrib4ubNV and glVertexAttrib4Nub */
        { 1112, 1083 }, /* glVertexAttrib4ubNV and glVertexAttrib4NubARB */
        { 1113, 1114 }, /* glVertexAttrib4ubv and glVertexAttrib4ubvARB */
        { 1114, 1113 }, /* glVertexAttrib4ubvARB and glVertexAttrib4ubv */
        { 1115, 1084 }, /* glVertexAttrib4ubvNV and glVertexAttrib4Nubv */
        { 1115, 1085 }, /* glVertexAttrib4ubvNV and glVertexAttrib4NubvARB */
        { 1116, 1117 }, /* glVertexAttrib4uiv and glVertexAttrib4uivARB */
        { 1117, 1116 }, /* glVertexAttrib4uivARB and glVertexAttrib4uiv */
        { 1118, 1119 }, /* glVertexAttrib4usv and glVertexAttrib4usvARB */
        { 1119, 1118 }, /* glVertexAttrib4usvARB and glVertexAttrib4usv */
        { 1539, 1540 }, /* glVertexAttribDivisor and glVertexAttribDivisorANGLE */
        { 1539, 1541 }, /* glVertexAttribDivisor and glVertexAttribDivisorEXT */
        { 1539, 1542 }, /* glVertexAttribDivisor and glVertexAttribDivisorNV */
        { 1540, 1539 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisor */
        { 1540, 1541 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisorEXT */
        { 1540, 1542 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisorNV */
        { 1541, 1539 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisor */
        { 1541, 1540 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisorANGLE */
        { 1541, 1542 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisorNV */
        { 1542, 1539 }, /* glVertexAttribDivisorNV and glVertexAttribDivisor */
        { 1542, 1540 }, /* glVertexAttribDivisorNV and glVertexAttribDivisorANGLE */
        { 1542, 1541 }, /* glVertexAttribDivisorNV and glVertexAttribDivisorEXT */
        { 1120, 1121 }, /* glVertexAttribPointer and glVertexAttribPointerARB */
        { 1121, 1120 }, /* glVertexAttribPointerARB and glVertexAttribPointer */
        { 1557, 1558 }, /* glWaitSync and glWaitSyncAPPLE */
        { 1558, 1557 }, /* glWaitSyncAPPLE and glWaitSync */
        { 1139, 1140 }, /* glWindowPos2d and glWindowPos2dARB */
        { 1139, 1141 }, /* glWindowPos2d and glWindowPos2dMESA */
        { 1140, 1139 }, /* glWindowPos2dARB and glWindowPos2d */
        { 1140, 1141 }, /* glWindowPos2dARB and glWindowPos2dMESA */
        { 1141, 1139 }, /* glWindowPos2dMESA and glWindowPos2d */
        { 1141, 1140 }, /* glWindowPos2dMESA and glWindowPos2dARB */
        { 1142, 1143 }, /* glWindowPos2dv and glWindowPos2dvARB */
        { 1142, 1144 }, /* glWindowPos2dv and glWindowPos2dvMESA */
        { 1143, 1142 }, /* glWindowPos2dvARB and glWindowPos2dv */
        { 1143, 1144 }, /* glWindowPos2dvARB and glWindowPos2dvMESA */
        { 1144, 1142 }, /* glWindowPos2dvMESA and glWindowPos2dv */
        { 1144, 1143 }, /* glWindowPos2dvMESA and glWindowPos2dvARB */
        { 1145, 1146 }, /* glWindowPos2f and glWindowPos2fARB */
        { 1145, 1147 }, /* glWindowPos2f and glWindowPos2fMESA */
        { 1146, 1145 }, /* glWindowPos2fARB and glWindowPos2f */
        { 1146, 1147 }, /* glWindowPos2fARB and glWindowPos2fMESA */
        { 1147, 1145 }, /* glWindowPos2fMESA and glWindowPos2f */
        { 1147, 1146 }, /* glWindowPos2fMESA and glWindowPos2fARB */
        { 1148, 1149 }, /* glWindowPos2fv and glWindowPos2fvARB */
        { 1148, 1150 }, /* glWindowPos2fv and glWindowPos2fvMESA */
        { 1149, 1148 }, /* glWindowPos2fvARB and glWindowPos2fv */
        { 1149, 1150 }, /* glWindowPos2fvARB and glWindowPos2fvMESA */
        { 1150, 1148 }, /* glWindowPos2fvMESA and glWindowPos2fv */
        { 1150, 1149 }, /* glWindowPos2fvMESA and glWindowPos2fvARB */
        { 1151, 1152 }, /* glWindowPos2i and glWindowPos2iARB */
        { 1151, 1153 }, /* glWindowPos2i and glWindowPos2iMESA */
        { 1152, 1151 }, /* glWindowPos2iARB and glWindowPos2i */
        { 1152, 1153 }, /* glWindowPos2iARB and glWindowPos2iMESA */
        { 1153, 1151 }, /* glWindowPos2iMESA and glWindowPos2i */
        { 1153, 1152 }, /* glWindowPos2iMESA and glWindowPos2iARB */
        { 1154, 1155 }, /* glWindowPos2iv and glWindowPos2ivARB */
        { 1154, 1156 }, /* glWindowPos2iv and glWindowPos2ivMESA */
        { 1155, 1154 }, /* glWindowPos2ivARB and glWindowPos2iv */
        { 1155, 1156 }, /* glWindowPos2ivARB and glWindowPos2ivMESA */
        { 1156, 1154 }, /* glWindowPos2ivMESA and glWindowPos2iv */
        { 1156, 1155 }, /* glWindowPos2ivMESA and glWindowPos2ivARB */
        { 1157, 1158 }, /* glWindowPos2s and glWindowPos2sARB */
        { 1157, 1159 }, /* glWindowPos2s and glWindowPos2sMESA */
        { 1158, 1157 }, /* glWindowPos2sARB and glWindowPos2s */
        { 1158, 1159 }, /* glWindowPos2sARB and glWindowPos2sMESA */
        { 1159, 1157 }, /* glWindowPos2sMESA and glWindowPos2s */
        { 1159, 1158 }, /* glWindowPos2sMESA and glWindowPos2sARB */
        { 1160, 1161 }, /* glWindowPos2sv and glWindowPos2svARB */
        { 1160, 1162 }, /* glWindowPos2sv and glWindowPos2svMESA */
        { 1161, 1160 }, /* glWindowPos2svARB and glWindowPos2sv */
        { 1161, 1162 }, /* glWindowPos2svARB and glWindowPos2svMESA */
        { 1162, 1160 }, /* glWindowPos2svMESA and glWindowPos2sv */
        { 1162, 1161 }, /* glWindowPos2svMESA and glWindowPos2svARB */
        { 1163, 1164 }, /* glWindowPos3d and glWindowPos3dARB */
        { 1163, 1165 }, /* glWindowPos3d and glWindowPos3dMESA */
        { 1164, 1163 }, /* glWindowPos3dARB and glWindowPos3d */
        { 1164, 1165 }, /* glWindowPos3dARB and glWindowPos3dMESA */
        { 1165, 1163 }, /* glWindowPos3dMESA and glWindowPos3d */
        { 1165, 1164 }, /* glWindowPos3dMESA and glWindowPos3dARB */
        { 1166, 1167 }, /* glWindowPos3dv and glWindowPos3dvARB */
        { 1166, 1168 }, /* glWindowPos3dv and glWindowPos3dvMESA */
        { 1167, 1166 }, /* glWindowPos3dvARB and glWindowPos3dv */
        { 1167, 1168 }, /* glWindowPos3dvARB and glWindowPos3dvMESA */
        { 1168, 1166 }, /* glWindowPos3dvMESA and glWindowPos3dv */
        { 1168, 1167 }, /* glWindowPos3dvMESA and glWindowPos3dvARB */
        { 1169, 1170 }, /* glWindowPos3f and glWindowPos3fARB */
        { 1169, 1171 }, /* glWindowPos3f and glWindowPos3fMESA */
        { 1170, 1169 }, /* glWindowPos3fARB and glWindowPos3f */
        { 1170, 1171 }, /* glWindowPos3fARB and glWindowPos3fMESA */
        { 1171, 1169 }, /* glWindowPos3fMESA and glWindowPos3f */
        { 1171, 1170 }, /* glWindowPos3fMESA and glWindowPos3fARB */
        { 1172, 1173 }, /* glWindowPos3fv and glWindowPos3fvARB */
        { 1172, 1174 }, /* glWindowPos3fv and glWindowPos3fvMESA */
        { 1173, 1172 }, /* glWindowPos3fvARB and glWindowPos3fv */
        { 1173, 1174 }, /* glWindowPos3fvARB and glWindowPos3fvMESA */
        { 1174, 1172 }, /* glWindowPos3fvMESA and glWindowPos3fv */
        { 1174, 1173 }, /* glWindowPos3fvMESA and glWindowPos3fvARB */
        { 1175, 1176 }, /* glWindowPos3i and glWindowPos3iARB */
        { 1175, 1177 }, /* glWindowPos3i and glWindowPos3iMESA */
        { 1176, 1175 }, /* glWindowPos3iARB and glWindowPos3i */
        { 1176, 1177 }, /* glWindowPos3iARB and glWindowPos3iMESA */
        { 1177, 1175 }, /* glWindowPos3iMESA and glWindowPos3i */
        { 1177, 1176 }, /* glWindowPos3iMESA and glWindowPos3iARB */
        { 1178, 1179 }, /* glWindowPos3iv and glWindowPos3ivARB */
        { 1178, 1180 }, /* glWindowPos3iv and glWindowPos3ivMESA */
        { 1179, 1178 }, /* glWindowPos3ivARB and glWindowPos3iv */
        { 1179, 1180 }, /* glWindowPos3ivARB and glWindowPos3ivMESA */
        { 1180, 1178 }, /* glWindowPos3ivMESA and glWindowPos3iv */
        { 1180, 1179 }, /* glWindowPos3ivMESA and glWindowPos3ivARB */
        { 1181, 1182 }, /* glWindowPos3s and glWindowPos3sARB */
        { 1181, 1183 }, /* glWindowPos3s and glWindowPos3sMESA */
        { 1182, 1181 }, /* glWindowPos3sARB and glWindowPos3s */
        { 1182, 1183 }, /* glWindowPos3sARB and glWindowPos3sMESA */
        { 1183, 1181 }, /* glWindowPos3sMESA and glWindowPos3s */
        { 1183, 1182 }, /* glWindowPos3sMESA and glWindowPos3sARB */
        { 1184, 1185 }, /* glWindowPos3sv and glWindowPos3svARB */
        { 1184, 1186 }, /* glWindowPos3sv and glWindowPos3svMESA */
        { 1185, 1184 }, /* glWindowPos3svARB and glWindowPos3sv */
        { 1185, 1186 }, /* glWindowPos3svARB and glWindowPos3svMESA */
        { 1186, 1184 }, /* glWindowPos3svMESA and glWindowPos3sv */
        { 1186, 1185 }, /* glWindowPos3svMESA and glWindowPos3svARB */
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
           4, /* GL_ARB_buffer_storage */
           5, /* GL_ARB_debug_output */
           6, /* GL_ARB_draw_buffers */
           7, /* GL_ARB_imaging */
           8, /* GL_ARB_multisample */
           9, /* GL_ARB_multitexture */
          10, /* GL_ARB_occlusion_query */
          11, /* GL_ARB_point_parameters */
          12, /* GL_ARB_shader_objects */
          13, /* GL_ARB_texture_compression */
          14, /* GL_ARB_transpose_matrix */
          15, /* GL_ARB_vertex_buffer_object */
          16, /* GL_ARB_vertex_program */
          17, /* GL_ARB_vertex_shader */
          18, /* GL_ARB_window_pos */
          19, /* GL_ATI_draw_buffers */
          20, /* GL_ATI_separate_stencil */
          21, /* GL_EXT_blend_color */
          22, /* GL_EXT_blend_equation_separate */
          23, /* GL_EXT_blend_func_separate */
          24, /* GL_EXT_blend_minmax */
          26, /* GL_EXT_copy_texture */
          27, /* GL_EXT_direct_state_access */
          32, /* GL_EXT_draw_instanced */
          33, /* GL_EXT_draw_range_elements */
          34, /* GL_EXT_fog_coord */
          38, /* GL_EXT_multi_draw_arrays */
          40, /* GL_EXT_point_parameters */
          43, /* GL_EXT_secondary_color */
          44, /* GL_EXT_separate_shader_objects */
          45, /* GL_EXT_subtexture */
          47, /* GL_EXT_texture3D */
          50, /* GL_EXT_texture_object */
          51, /* GL_EXT_texture_storage */
          52, /* GL_EXT_vertex_array */
          53, /* GL_INGR_blend_func_separate */
          54, /* GL_KHR_blend_equation_advanced */
          55, /* GL_KHR_debug */
          56, /* GL_KHR_robustness */
          58, /* GL_MESA_window_pos */
          59, /* GL_NV_blend_equation_advanced */
          66, /* GL_NV_point_sprite */
          67, /* GL_NV_vertex_program */
          83, /* GL_SGIS_point_parameters */
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

    if (!glad_gl_find_extensions_gl(context)) return 0;
    glad_gl_load_GL_ARB_buffer_storage(context, load, userptr);
    glad_gl_load_GL_ARB_debug_output(context, load, userptr);
    glad_gl_load_GL_ARB_draw_buffers(context, load, userptr);
    glad_gl_load_GL_ARB_imaging(context, load, userptr);
    glad_gl_load_GL_ARB_multisample(context, load, userptr);
    glad_gl_load_GL_ARB_multitexture(context, load, userptr);
    glad_gl_load_GL_ARB_occlusion_query(context, load, userptr);
    glad_gl_load_GL_ARB_point_parameters(context, load, userptr);
    glad_gl_load_GL_ARB_shader_objects(context, load, userptr);
    glad_gl_load_GL_ARB_texture_compression(context, load, userptr);
    glad_gl_load_GL_ARB_transpose_matrix(context, load, userptr);
    glad_gl_load_GL_ARB_vertex_buffer_object(context, load, userptr);
    glad_gl_load_GL_ARB_vertex_program(context, load, userptr);
    glad_gl_load_GL_ARB_vertex_shader(context, load, userptr);
    glad_gl_load_GL_ARB_window_pos(context, load, userptr);
    glad_gl_load_GL_ATI_draw_buffers(context, load, userptr);
    glad_gl_load_GL_ATI_separate_stencil(context, load, userptr);
    glad_gl_load_GL_EXT_blend_color(context, load, userptr);
    glad_gl_load_GL_EXT_blend_equation_separate(context, load, userptr);
    glad_gl_load_GL_EXT_blend_func_separate(context, load, userptr);
    glad_gl_load_GL_EXT_blend_minmax(context, load, userptr);
    glad_gl_load_GL_EXT_copy_texture(context, load, userptr);
    glad_gl_load_GL_EXT_direct_state_access(context, load, userptr);
    glad_gl_load_GL_EXT_draw_instanced(context, load, userptr);
    glad_gl_load_GL_EXT_draw_range_elements(context, load, userptr);
    glad_gl_load_GL_EXT_fog_coord(context, load, userptr);
    glad_gl_load_GL_EXT_multi_draw_arrays(context, load, userptr);
    glad_gl_load_GL_EXT_point_parameters(context, load, userptr);
    glad_gl_load_GL_EXT_secondary_color(context, load, userptr);
    glad_gl_load_GL_EXT_separate_shader_objects(context, load, userptr);
    glad_gl_load_GL_EXT_subtexture(context, load, userptr);
    glad_gl_load_GL_EXT_texture3D(context, load, userptr);
    glad_gl_load_GL_EXT_texture_object(context, load, userptr);
    glad_gl_load_GL_EXT_texture_storage(context, load, userptr);
    glad_gl_load_GL_EXT_vertex_array(context, load, userptr);
    glad_gl_load_GL_INGR_blend_func_separate(context, load, userptr);
    glad_gl_load_GL_KHR_blend_equation_advanced(context, load, userptr);
    glad_gl_load_GL_KHR_debug(context, load, userptr);
    glad_gl_load_GL_KHR_robustness(context, load, userptr);
    glad_gl_load_GL_MESA_window_pos(context, load, userptr);
    glad_gl_load_GL_NV_blend_equation_advanced(context, load, userptr);
    glad_gl_load_GL_NV_point_sprite(context, load, userptr);
    glad_gl_load_GL_NV_vertex_program(context, load, userptr);
    glad_gl_load_GL_SGIS_point_parameters(context, load, userptr);

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
           0, /* GL_ANGLE_get_tex_level_parameter */
           1, /* GL_ANGLE_instanced_arrays */
           2, /* GL_ANGLE_texture_multisample */
           3, /* GL_APPLE_sync */
          24, /* GL_EXT_blend_minmax */
          25, /* GL_EXT_copy_image */
          28, /* GL_EXT_disjoint_timer_query */
          29, /* GL_EXT_draw_buffers */
          30, /* GL_EXT_draw_buffers_indexed */
          31, /* GL_EXT_draw_elements_base_vertex */
          32, /* GL_EXT_draw_instanced */
          35, /* GL_EXT_geometry_shader */
          36, /* GL_EXT_instanced_arrays */
          37, /* GL_EXT_map_buffer_range */
          38, /* GL_EXT_multi_draw_arrays */
          39, /* GL_EXT_multisampled_render_to_texture */
          41, /* GL_EXT_primitive_bounding_box */
          42, /* GL_EXT_robustness */
          44, /* GL_EXT_separate_shader_objects */
          46, /* GL_EXT_tessellation_shader */
          48, /* GL_EXT_texture_border_clamp */
          49, /* GL_EXT_texture_buffer */
          51, /* GL_EXT_texture_storage */
          54, /* GL_KHR_blend_equation_advanced */
          55, /* GL_KHR_debug */
          56, /* GL_KHR_robustness */
          57, /* GL_MESA_sampler_objects */
          59, /* GL_NV_blend_equation_advanced */
          60, /* GL_NV_copy_buffer */
          61, /* GL_NV_draw_instanced */
          62, /* GL_NV_framebuffer_blit */
          63, /* GL_NV_framebuffer_multisample */
          64, /* GL_NV_instanced_arrays */
          65, /* GL_NV_non_square_matrices */
          68, /* GL_NV_viewport_array */
          69, /* GL_OES_copy_image */
          70, /* GL_OES_draw_buffers_indexed */
          71, /* GL_OES_draw_elements_base_vertex */
          72, /* GL_OES_geometry_shader */
          73, /* GL_OES_get_program_binary */
          74, /* GL_OES_mapbuffer */
          75, /* GL_OES_primitive_bounding_box */
          76, /* GL_OES_sample_shading */
          77, /* GL_OES_tessellation_shader */
          78, /* GL_OES_texture_border_clamp */
          79, /* GL_OES_texture_buffer */
          80, /* GL_OES_texture_storage_multisample_2d_array */
          81, /* GL_OES_vertex_array_object */
          82, /* GL_OES_viewport_array */
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
    glad_gl_load_GL_ANGLE_get_tex_level_parameter(context, load, userptr);
    glad_gl_load_GL_ANGLE_instanced_arrays(context, load, userptr);
    glad_gl_load_GL_ANGLE_texture_multisample(context, load, userptr);
    glad_gl_load_GL_APPLE_sync(context, load, userptr);
    glad_gl_load_GL_EXT_blend_minmax(context, load, userptr);
    glad_gl_load_GL_EXT_copy_image(context, load, userptr);
    glad_gl_load_GL_EXT_disjoint_timer_query(context, load, userptr);
    glad_gl_load_GL_EXT_draw_buffers(context, load, userptr);
    glad_gl_load_GL_EXT_draw_buffers_indexed(context, load, userptr);
    glad_gl_load_GL_EXT_draw_elements_base_vertex(context, load, userptr);
    glad_gl_load_GL_EXT_draw_instanced(context, load, userptr);
    glad_gl_load_GL_EXT_geometry_shader(context, load, userptr);
    glad_gl_load_GL_EXT_instanced_arrays(context, load, userptr);
    glad_gl_load_GL_EXT_map_buffer_range(context, load, userptr);
    glad_gl_load_GL_EXT_multi_draw_arrays(context, load, userptr);
    glad_gl_load_GL_EXT_multisampled_render_to_texture(context, load, userptr);
    glad_gl_load_GL_EXT_primitive_bounding_box(context, load, userptr);
    glad_gl_load_GL_EXT_robustness(context, load, userptr);
    glad_gl_load_GL_EXT_separate_shader_objects(context, load, userptr);
    glad_gl_load_GL_EXT_tessellation_shader(context, load, userptr);
    glad_gl_load_GL_EXT_texture_border_clamp(context, load, userptr);
    glad_gl_load_GL_EXT_texture_buffer(context, load, userptr);
    glad_gl_load_GL_EXT_texture_storage(context, load, userptr);
    glad_gl_load_GL_KHR_blend_equation_advanced(context, load, userptr);
    glad_gl_load_GL_KHR_debug(context, load, userptr);
    glad_gl_load_GL_KHR_robustness(context, load, userptr);
    glad_gl_load_GL_MESA_sampler_objects(context, load, userptr);
    glad_gl_load_GL_NV_blend_equation_advanced(context, load, userptr);
    glad_gl_load_GL_NV_copy_buffer(context, load, userptr);
    glad_gl_load_GL_NV_draw_instanced(context, load, userptr);
    glad_gl_load_GL_NV_framebuffer_blit(context, load, userptr);
    glad_gl_load_GL_NV_framebuffer_multisample(context, load, userptr);
    glad_gl_load_GL_NV_instanced_arrays(context, load, userptr);
    glad_gl_load_GL_NV_non_square_matrices(context, load, userptr);
    glad_gl_load_GL_NV_viewport_array(context, load, userptr);
    glad_gl_load_GL_OES_copy_image(context, load, userptr);
    glad_gl_load_GL_OES_draw_buffers_indexed(context, load, userptr);
    glad_gl_load_GL_OES_draw_elements_base_vertex(context, load, userptr);
    glad_gl_load_GL_OES_geometry_shader(context, load, userptr);
    glad_gl_load_GL_OES_get_program_binary(context, load, userptr);
    glad_gl_load_GL_OES_mapbuffer(context, load, userptr);
    glad_gl_load_GL_OES_primitive_bounding_box(context, load, userptr);
    glad_gl_load_GL_OES_sample_shading(context, load, userptr);
    glad_gl_load_GL_OES_tessellation_shader(context, load, userptr);
    glad_gl_load_GL_OES_texture_border_clamp(context, load, userptr);
    glad_gl_load_GL_OES_texture_buffer(context, load, userptr);
    glad_gl_load_GL_OES_texture_storage_multisample_2d_array(context, load, userptr);
    glad_gl_load_GL_OES_vertex_array_object(context, load, userptr);
    glad_gl_load_GL_OES_viewport_array(context, load, userptr);

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
#elif GLAD_GLES2_USE_SYSTEM_EGL
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
#if !GLAD_GLES2_USE_SYSTEM_EGL
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
