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
    /*    1 */ "glAlphaFunc",
    /*    2 */ "glAreTexturesResident",
    /*    3 */ "glAreTexturesResidentEXT",
    /*    4 */ "glArrayElement",
    /*    5 */ "glArrayElementEXT",
    /*    6 */ "glBegin",
    /*    7 */ "glBindBufferARB",
    /*    8 */ "glBindMultiTextureEXT",
    /*    9 */ "glBindTexture",
    /*   10 */ "glBindTextureEXT",
    /*   11 */ "glBitmap",
    /*   12 */ "glBlendFunc",
    /*   13 */ "glBufferDataARB",
    /*   14 */ "glBufferStorage",
    /*   15 */ "glBufferSubDataARB",
    /*   16 */ "glCallList",
    /*   17 */ "glCallLists",
    /*   18 */ "glCheckNamedFramebufferStatusEXT",
    /*   19 */ "glClear",
    /*   20 */ "glClearAccum",
    /*   21 */ "glClearColor",
    /*   22 */ "glClearDepth",
    /*   23 */ "glClearIndex",
    /*   24 */ "glClearNamedBufferDataEXT",
    /*   25 */ "glClearNamedBufferSubDataEXT",
    /*   26 */ "glClearStencil",
    /*   27 */ "glClientAttribDefaultEXT",
    /*   28 */ "glClipPlane",
    /*   29 */ "glColor3b",
    /*   30 */ "glColor3bv",
    /*   31 */ "glColor3d",
    /*   32 */ "glColor3dv",
    /*   33 */ "glColor3f",
    /*   34 */ "glColor3fv",
    /*   35 */ "glColor3i",
    /*   36 */ "glColor3iv",
    /*   37 */ "glColor3s",
    /*   38 */ "glColor3sv",
    /*   39 */ "glColor3ub",
    /*   40 */ "glColor3ubv",
    /*   41 */ "glColor3ui",
    /*   42 */ "glColor3uiv",
    /*   43 */ "glColor3us",
    /*   44 */ "glColor3usv",
    /*   45 */ "glColor4b",
    /*   46 */ "glColor4bv",
    /*   47 */ "glColor4d",
    /*   48 */ "glColor4dv",
    /*   49 */ "glColor4f",
    /*   50 */ "glColor4fv",
    /*   51 */ "glColor4i",
    /*   52 */ "glColor4iv",
    /*   53 */ "glColor4s",
    /*   54 */ "glColor4sv",
    /*   55 */ "glColor4ub",
    /*   56 */ "glColor4ubv",
    /*   57 */ "glColor4ui",
    /*   58 */ "glColor4uiv",
    /*   59 */ "glColor4us",
    /*   60 */ "glColor4usv",
    /*   61 */ "glColorMask",
    /*   62 */ "glColorMaterial",
    /*   63 */ "glColorPointer",
    /*   64 */ "glColorPointerEXT",
    /*   65 */ "glCompressedMultiTexImage1DEXT",
    /*   66 */ "glCompressedMultiTexImage2DEXT",
    /*   67 */ "glCompressedMultiTexImage3DEXT",
    /*   68 */ "glCompressedMultiTexSubImage1DEXT",
    /*   69 */ "glCompressedMultiTexSubImage2DEXT",
    /*   70 */ "glCompressedMultiTexSubImage3DEXT",
    /*   71 */ "glCompressedTextureImage1DEXT",
    /*   72 */ "glCompressedTextureImage2DEXT",
    /*   73 */ "glCompressedTextureImage3DEXT",
    /*   74 */ "glCompressedTextureSubImage1DEXT",
    /*   75 */ "glCompressedTextureSubImage2DEXT",
    /*   76 */ "glCompressedTextureSubImage3DEXT",
    /*   77 */ "glCopyMultiTexImage1DEXT",
    /*   78 */ "glCopyMultiTexImage2DEXT",
    /*   79 */ "glCopyMultiTexSubImage1DEXT",
    /*   80 */ "glCopyMultiTexSubImage2DEXT",
    /*   81 */ "glCopyMultiTexSubImage3DEXT",
    /*   82 */ "glCopyPixels",
    /*   83 */ "glCopyTexImage1D",
    /*   84 */ "glCopyTexImage1DEXT",
    /*   85 */ "glCopyTexImage2D",
    /*   86 */ "glCopyTexImage2DEXT",
    /*   87 */ "glCopyTexSubImage1D",
    /*   88 */ "glCopyTexSubImage1DEXT",
    /*   89 */ "glCopyTexSubImage2D",
    /*   90 */ "glCopyTexSubImage2DEXT",
    /*   91 */ "glCopyTexSubImage3D",
    /*   92 */ "glCopyTexSubImage3DEXT",
    /*   93 */ "glCopyTextureImage1DEXT",
    /*   94 */ "glCopyTextureImage2DEXT",
    /*   95 */ "glCopyTextureSubImage1DEXT",
    /*   96 */ "glCopyTextureSubImage2DEXT",
    /*   97 */ "glCopyTextureSubImage3DEXT",
    /*   98 */ "glCullFace",
    /*   99 */ "glDebugMessageCallback",
    /*  100 */ "glDebugMessageCallbackARB",
    /*  101 */ "glDebugMessageControl",
    /*  102 */ "glDebugMessageControlARB",
    /*  103 */ "glDebugMessageInsert",
    /*  104 */ "glDebugMessageInsertARB",
    /*  105 */ "glDeleteBuffersARB",
    /*  106 */ "glDeleteLists",
    /*  107 */ "glDeleteTextures",
    /*  108 */ "glDeleteTexturesEXT",
    /*  109 */ "glDepthFunc",
    /*  110 */ "glDepthMask",
    /*  111 */ "glDepthRange",
    /*  112 */ "glDisable",
    /*  113 */ "glDisableClientState",
    /*  114 */ "glDisableClientStateIndexedEXT",
    /*  115 */ "glDisableClientStateiEXT",
    /*  116 */ "glDisableIndexedEXT",
    /*  117 */ "glDisableVertexArrayAttribEXT",
    /*  118 */ "glDisableVertexArrayEXT",
    /*  119 */ "glDrawArrays",
    /*  120 */ "glDrawArraysEXT",
    /*  121 */ "glDrawBuffer",
    /*  122 */ "glDrawElements",
    /*  123 */ "glDrawPixels",
    /*  124 */ "glDrawRangeElements",
    /*  125 */ "glDrawRangeElementsEXT",
    /*  126 */ "glEdgeFlag",
    /*  127 */ "glEdgeFlagPointer",
    /*  128 */ "glEdgeFlagPointerEXT",
    /*  129 */ "glEdgeFlagv",
    /*  130 */ "glEnable",
    /*  131 */ "glEnableClientState",
    /*  132 */ "glEnableClientStateIndexedEXT",
    /*  133 */ "glEnableClientStateiEXT",
    /*  134 */ "glEnableIndexedEXT",
    /*  135 */ "glEnableVertexArrayAttribEXT",
    /*  136 */ "glEnableVertexArrayEXT",
    /*  137 */ "glEnd",
    /*  138 */ "glEndList",
    /*  139 */ "glEvalCoord1d",
    /*  140 */ "glEvalCoord1dv",
    /*  141 */ "glEvalCoord1f",
    /*  142 */ "glEvalCoord1fv",
    /*  143 */ "glEvalCoord2d",
    /*  144 */ "glEvalCoord2dv",
    /*  145 */ "glEvalCoord2f",
    /*  146 */ "glEvalCoord2fv",
    /*  147 */ "glEvalMesh1",
    /*  148 */ "glEvalMesh2",
    /*  149 */ "glEvalPoint1",
    /*  150 */ "glEvalPoint2",
    /*  151 */ "glFeedbackBuffer",
    /*  152 */ "glFinish",
    /*  153 */ "glFlush",
    /*  154 */ "glFlushMappedNamedBufferRangeEXT",
    /*  155 */ "glFogf",
    /*  156 */ "glFogfv",
    /*  157 */ "glFogi",
    /*  158 */ "glFogiv",
    /*  159 */ "glFramebufferDrawBufferEXT",
    /*  160 */ "glFramebufferDrawBuffersEXT",
    /*  161 */ "glFramebufferReadBufferEXT",
    /*  162 */ "glFrontFace",
    /*  163 */ "glFrustum",
    /*  164 */ "glGenBuffersARB",
    /*  165 */ "glGenLists",
    /*  166 */ "glGenTextures",
    /*  167 */ "glGenTexturesEXT",
    /*  168 */ "glGenerateMultiTexMipmapEXT",
    /*  169 */ "glGenerateTextureMipmapEXT",
    /*  170 */ "glGetBooleanIndexedvEXT",
    /*  171 */ "glGetBooleanv",
    /*  172 */ "glGetBufferParameterivARB",
    /*  173 */ "glGetBufferPointervARB",
    /*  174 */ "glGetBufferSubDataARB",
    /*  175 */ "glGetClipPlane",
    /*  176 */ "glGetCompressedMultiTexImageEXT",
    /*  177 */ "glGetCompressedTextureImageEXT",
    /*  178 */ "glGetDebugMessageLog",
    /*  179 */ "glGetDebugMessageLogARB",
    /*  180 */ "glGetDoubleIndexedvEXT",
    /*  181 */ "glGetDoublei_vEXT",
    /*  182 */ "glGetDoublev",
    /*  183 */ "glGetError",
    /*  184 */ "glGetFloatIndexedvEXT",
    /*  185 */ "glGetFloati_vEXT",
    /*  186 */ "glGetFloatv",
    /*  187 */ "glGetFramebufferParameterivEXT",
    /*  188 */ "glGetIntegerIndexedvEXT",
    /*  189 */ "glGetIntegerv",
    /*  190 */ "glGetLightfv",
    /*  191 */ "glGetLightiv",
    /*  192 */ "glGetMapdv",
    /*  193 */ "glGetMapfv",
    /*  194 */ "glGetMapiv",
    /*  195 */ "glGetMaterialfv",
    /*  196 */ "glGetMaterialiv",
    /*  197 */ "glGetMultiTexEnvfvEXT",
    /*  198 */ "glGetMultiTexEnvivEXT",
    /*  199 */ "glGetMultiTexGendvEXT",
    /*  200 */ "glGetMultiTexGenfvEXT",
    /*  201 */ "glGetMultiTexGenivEXT",
    /*  202 */ "glGetMultiTexImageEXT",
    /*  203 */ "glGetMultiTexLevelParameterfvEXT",
    /*  204 */ "glGetMultiTexLevelParameterivEXT",
    /*  205 */ "glGetMultiTexParameterIivEXT",
    /*  206 */ "glGetMultiTexParameterIuivEXT",
    /*  207 */ "glGetMultiTexParameterfvEXT",
    /*  208 */ "glGetMultiTexParameterivEXT",
    /*  209 */ "glGetNamedBufferParameterivEXT",
    /*  210 */ "glGetNamedBufferPointervEXT",
    /*  211 */ "glGetNamedBufferSubDataEXT",
    /*  212 */ "glGetNamedFramebufferAttachmentParameterivEXT",
    /*  213 */ "glGetNamedFramebufferParameterivEXT",
    /*  214 */ "glGetNamedProgramLocalParameterIivEXT",
    /*  215 */ "glGetNamedProgramLocalParameterIuivEXT",
    /*  216 */ "glGetNamedProgramLocalParameterdvEXT",
    /*  217 */ "glGetNamedProgramLocalParameterfvEXT",
    /*  218 */ "glGetNamedProgramStringEXT",
    /*  219 */ "glGetNamedProgramivEXT",
    /*  220 */ "glGetNamedRenderbufferParameterivEXT",
    /*  221 */ "glGetObjectLabel",
    /*  222 */ "glGetObjectPtrLabel",
    /*  223 */ "glGetPixelMapfv",
    /*  224 */ "glGetPixelMapuiv",
    /*  225 */ "glGetPixelMapusv",
    /*  226 */ "glGetPointerIndexedvEXT",
    /*  227 */ "glGetPointeri_vEXT",
    /*  228 */ "glGetPointerv",
    /*  229 */ "glGetPointervEXT",
    /*  230 */ "glGetPolygonStipple",
    /*  231 */ "glGetString",
    /*  232 */ "glGetTexEnvfv",
    /*  233 */ "glGetTexEnviv",
    /*  234 */ "glGetTexGendv",
    /*  235 */ "glGetTexGenfv",
    /*  236 */ "glGetTexGeniv",
    /*  237 */ "glGetTexImage",
    /*  238 */ "glGetTexLevelParameterfv",
    /*  239 */ "glGetTexLevelParameteriv",
    /*  240 */ "glGetTexParameterfv",
    /*  241 */ "glGetTexParameteriv",
    /*  242 */ "glGetTextureImageEXT",
    /*  243 */ "glGetTextureLevelParameterfvEXT",
    /*  244 */ "glGetTextureLevelParameterivEXT",
    /*  245 */ "glGetTextureParameterIivEXT",
    /*  246 */ "glGetTextureParameterIuivEXT",
    /*  247 */ "glGetTextureParameterfvEXT",
    /*  248 */ "glGetTextureParameterivEXT",
    /*  249 */ "glGetVertexArrayIntegeri_vEXT",
    /*  250 */ "glGetVertexArrayIntegervEXT",
    /*  251 */ "glGetVertexArrayPointeri_vEXT",
    /*  252 */ "glGetVertexArrayPointervEXT",
    /*  253 */ "glHint",
    /*  254 */ "glIndexMask",
    /*  255 */ "glIndexPointer",
    /*  256 */ "glIndexPointerEXT",
    /*  257 */ "glIndexd",
    /*  258 */ "glIndexdv",
    /*  259 */ "glIndexf",
    /*  260 */ "glIndexfv",
    /*  261 */ "glIndexi",
    /*  262 */ "glIndexiv",
    /*  263 */ "glIndexs",
    /*  264 */ "glIndexsv",
    /*  265 */ "glIndexub",
    /*  266 */ "glIndexubv",
    /*  267 */ "glInitNames",
    /*  268 */ "glInterleavedArrays",
    /*  269 */ "glIsBufferARB",
    /*  270 */ "glIsEnabled",
    /*  271 */ "glIsEnabledIndexedEXT",
    /*  272 */ "glIsList",
    /*  273 */ "glIsTexture",
    /*  274 */ "glIsTextureEXT",
    /*  275 */ "glLightModelf",
    /*  276 */ "glLightModelfv",
    /*  277 */ "glLightModeli",
    /*  278 */ "glLightModeliv",
    /*  279 */ "glLightf",
    /*  280 */ "glLightfv",
    /*  281 */ "glLighti",
    /*  282 */ "glLightiv",
    /*  283 */ "glLineStipple",
    /*  284 */ "glLineWidth",
    /*  285 */ "glListBase",
    /*  286 */ "glLoadIdentity",
    /*  287 */ "glLoadMatrixd",
    /*  288 */ "glLoadMatrixf",
    /*  289 */ "glLoadName",
    /*  290 */ "glLogicOp",
    /*  291 */ "glMap1d",
    /*  292 */ "glMap1f",
    /*  293 */ "glMap2d",
    /*  294 */ "glMap2f",
    /*  295 */ "glMapBufferARB",
    /*  296 */ "glMapGrid1d",
    /*  297 */ "glMapGrid1f",
    /*  298 */ "glMapGrid2d",
    /*  299 */ "glMapGrid2f",
    /*  300 */ "glMapNamedBufferEXT",
    /*  301 */ "glMapNamedBufferRangeEXT",
    /*  302 */ "glMaterialf",
    /*  303 */ "glMaterialfv",
    /*  304 */ "glMateriali",
    /*  305 */ "glMaterialiv",
    /*  306 */ "glMatrixFrustumEXT",
    /*  307 */ "glMatrixLoadIdentityEXT",
    /*  308 */ "glMatrixLoadTransposedEXT",
    /*  309 */ "glMatrixLoadTransposefEXT",
    /*  310 */ "glMatrixLoaddEXT",
    /*  311 */ "glMatrixLoadfEXT",
    /*  312 */ "glMatrixMode",
    /*  313 */ "glMatrixMultTransposedEXT",
    /*  314 */ "glMatrixMultTransposefEXT",
    /*  315 */ "glMatrixMultdEXT",
    /*  316 */ "glMatrixMultfEXT",
    /*  317 */ "glMatrixOrthoEXT",
    /*  318 */ "glMatrixPopEXT",
    /*  319 */ "glMatrixPushEXT",
    /*  320 */ "glMatrixRotatedEXT",
    /*  321 */ "glMatrixRotatefEXT",
    /*  322 */ "glMatrixScaledEXT",
    /*  323 */ "glMatrixScalefEXT",
    /*  324 */ "glMatrixTranslatedEXT",
    /*  325 */ "glMatrixTranslatefEXT",
    /*  326 */ "glMultMatrixd",
    /*  327 */ "glMultMatrixf",
    /*  328 */ "glMultiTexBufferEXT",
    /*  329 */ "glMultiTexCoordPointerEXT",
    /*  330 */ "glMultiTexEnvfEXT",
    /*  331 */ "glMultiTexEnvfvEXT",
    /*  332 */ "glMultiTexEnviEXT",
    /*  333 */ "glMultiTexEnvivEXT",
    /*  334 */ "glMultiTexGendEXT",
    /*  335 */ "glMultiTexGendvEXT",
    /*  336 */ "glMultiTexGenfEXT",
    /*  337 */ "glMultiTexGenfvEXT",
    /*  338 */ "glMultiTexGeniEXT",
    /*  339 */ "glMultiTexGenivEXT",
    /*  340 */ "glMultiTexImage1DEXT",
    /*  341 */ "glMultiTexImage2DEXT",
    /*  342 */ "glMultiTexImage3DEXT",
    /*  343 */ "glMultiTexParameterIivEXT",
    /*  344 */ "glMultiTexParameterIuivEXT",
    /*  345 */ "glMultiTexParameterfEXT",
    /*  346 */ "glMultiTexParameterfvEXT",
    /*  347 */ "glMultiTexParameteriEXT",
    /*  348 */ "glMultiTexParameterivEXT",
    /*  349 */ "glMultiTexRenderbufferEXT",
    /*  350 */ "glMultiTexSubImage1DEXT",
    /*  351 */ "glMultiTexSubImage2DEXT",
    /*  352 */ "glMultiTexSubImage3DEXT",
    /*  353 */ "glNamedBufferDataEXT",
    /*  354 */ "glNamedBufferStorageEXT",
    /*  355 */ "glNamedBufferSubDataEXT",
    /*  356 */ "glNamedCopyBufferSubDataEXT",
    /*  357 */ "glNamedFramebufferParameteriEXT",
    /*  358 */ "glNamedFramebufferRenderbufferEXT",
    /*  359 */ "glNamedFramebufferTexture1DEXT",
    /*  360 */ "glNamedFramebufferTexture2DEXT",
    /*  361 */ "glNamedFramebufferTexture3DEXT",
    /*  362 */ "glNamedFramebufferTextureEXT",
    /*  363 */ "glNamedFramebufferTextureFaceEXT",
    /*  364 */ "glNamedFramebufferTextureLayerEXT",
    /*  365 */ "glNamedProgramLocalParameter4dEXT",
    /*  366 */ "glNamedProgramLocalParameter4dvEXT",
    /*  367 */ "glNamedProgramLocalParameter4fEXT",
    /*  368 */ "glNamedProgramLocalParameter4fvEXT",
    /*  369 */ "glNamedProgramLocalParameterI4iEXT",
    /*  370 */ "glNamedProgramLocalParameterI4ivEXT",
    /*  371 */ "glNamedProgramLocalParameterI4uiEXT",
    /*  372 */ "glNamedProgramLocalParameterI4uivEXT",
    /*  373 */ "glNamedProgramLocalParameters4fvEXT",
    /*  374 */ "glNamedProgramLocalParametersI4ivEXT",
    /*  375 */ "glNamedProgramLocalParametersI4uivEXT",
    /*  376 */ "glNamedProgramStringEXT",
    /*  377 */ "glNamedRenderbufferStorageEXT",
    /*  378 */ "glNamedRenderbufferStorageMultisampleCoverageEXT",
    /*  379 */ "glNamedRenderbufferStorageMultisampleEXT",
    /*  380 */ "glNewList",
    /*  381 */ "glNormal3b",
    /*  382 */ "glNormal3bv",
    /*  383 */ "glNormal3d",
    /*  384 */ "glNormal3dv",
    /*  385 */ "glNormal3f",
    /*  386 */ "glNormal3fv",
    /*  387 */ "glNormal3i",
    /*  388 */ "glNormal3iv",
    /*  389 */ "glNormal3s",
    /*  390 */ "glNormal3sv",
    /*  391 */ "glNormalPointer",
    /*  392 */ "glNormalPointerEXT",
    /*  393 */ "glObjectLabel",
    /*  394 */ "glObjectPtrLabel",
    /*  395 */ "glOrtho",
    /*  396 */ "glPassThrough",
    /*  397 */ "glPixelMapfv",
    /*  398 */ "glPixelMapuiv",
    /*  399 */ "glPixelMapusv",
    /*  400 */ "glPixelStoref",
    /*  401 */ "glPixelStorei",
    /*  402 */ "glPixelTransferf",
    /*  403 */ "glPixelTransferi",
    /*  404 */ "glPixelZoom",
    /*  405 */ "glPointSize",
    /*  406 */ "glPolygonMode",
    /*  407 */ "glPolygonOffset",
    /*  408 */ "glPolygonStipple",
    /*  409 */ "glPopAttrib",
    /*  410 */ "glPopClientAttrib",
    /*  411 */ "glPopDebugGroup",
    /*  412 */ "glPopMatrix",
    /*  413 */ "glPopName",
    /*  414 */ "glPrioritizeTextures",
    /*  415 */ "glPrioritizeTexturesEXT",
    /*  416 */ "glProgramUniform1dEXT",
    /*  417 */ "glProgramUniform1dvEXT",
    /*  418 */ "glProgramUniform1fEXT",
    /*  419 */ "glProgramUniform1fvEXT",
    /*  420 */ "glProgramUniform1iEXT",
    /*  421 */ "glProgramUniform1ivEXT",
    /*  422 */ "glProgramUniform1uiEXT",
    /*  423 */ "glProgramUniform1uivEXT",
    /*  424 */ "glProgramUniform2dEXT",
    /*  425 */ "glProgramUniform2dvEXT",
    /*  426 */ "glProgramUniform2fEXT",
    /*  427 */ "glProgramUniform2fvEXT",
    /*  428 */ "glProgramUniform2iEXT",
    /*  429 */ "glProgramUniform2ivEXT",
    /*  430 */ "glProgramUniform2uiEXT",
    /*  431 */ "glProgramUniform2uivEXT",
    /*  432 */ "glProgramUniform3dEXT",
    /*  433 */ "glProgramUniform3dvEXT",
    /*  434 */ "glProgramUniform3fEXT",
    /*  435 */ "glProgramUniform3fvEXT",
    /*  436 */ "glProgramUniform3iEXT",
    /*  437 */ "glProgramUniform3ivEXT",
    /*  438 */ "glProgramUniform3uiEXT",
    /*  439 */ "glProgramUniform3uivEXT",
    /*  440 */ "glProgramUniform4dEXT",
    /*  441 */ "glProgramUniform4dvEXT",
    /*  442 */ "glProgramUniform4fEXT",
    /*  443 */ "glProgramUniform4fvEXT",
    /*  444 */ "glProgramUniform4iEXT",
    /*  445 */ "glProgramUniform4ivEXT",
    /*  446 */ "glProgramUniform4uiEXT",
    /*  447 */ "glProgramUniform4uivEXT",
    /*  448 */ "glProgramUniformMatrix2dvEXT",
    /*  449 */ "glProgramUniformMatrix2fvEXT",
    /*  450 */ "glProgramUniformMatrix2x3dvEXT",
    /*  451 */ "glProgramUniformMatrix2x3fvEXT",
    /*  452 */ "glProgramUniformMatrix2x4dvEXT",
    /*  453 */ "glProgramUniformMatrix2x4fvEXT",
    /*  454 */ "glProgramUniformMatrix3dvEXT",
    /*  455 */ "glProgramUniformMatrix3fvEXT",
    /*  456 */ "glProgramUniformMatrix3x2dvEXT",
    /*  457 */ "glProgramUniformMatrix3x2fvEXT",
    /*  458 */ "glProgramUniformMatrix3x4dvEXT",
    /*  459 */ "glProgramUniformMatrix3x4fvEXT",
    /*  460 */ "glProgramUniformMatrix4dvEXT",
    /*  461 */ "glProgramUniformMatrix4fvEXT",
    /*  462 */ "glProgramUniformMatrix4x2dvEXT",
    /*  463 */ "glProgramUniformMatrix4x2fvEXT",
    /*  464 */ "glProgramUniformMatrix4x3dvEXT",
    /*  465 */ "glProgramUniformMatrix4x3fvEXT",
    /*  466 */ "glPushAttrib",
    /*  467 */ "glPushClientAttrib",
    /*  468 */ "glPushClientAttribDefaultEXT",
    /*  469 */ "glPushDebugGroup",
    /*  470 */ "glPushMatrix",
    /*  471 */ "glPushName",
    /*  472 */ "glRasterPos2d",
    /*  473 */ "glRasterPos2dv",
    /*  474 */ "glRasterPos2f",
    /*  475 */ "glRasterPos2fv",
    /*  476 */ "glRasterPos2i",
    /*  477 */ "glRasterPos2iv",
    /*  478 */ "glRasterPos2s",
    /*  479 */ "glRasterPos2sv",
    /*  480 */ "glRasterPos3d",
    /*  481 */ "glRasterPos3dv",
    /*  482 */ "glRasterPos3f",
    /*  483 */ "glRasterPos3fv",
    /*  484 */ "glRasterPos3i",
    /*  485 */ "glRasterPos3iv",
    /*  486 */ "glRasterPos3s",
    /*  487 */ "glRasterPos3sv",
    /*  488 */ "glRasterPos4d",
    /*  489 */ "glRasterPos4dv",
    /*  490 */ "glRasterPos4f",
    /*  491 */ "glRasterPos4fv",
    /*  492 */ "glRasterPos4i",
    /*  493 */ "glRasterPos4iv",
    /*  494 */ "glRasterPos4s",
    /*  495 */ "glRasterPos4sv",
    /*  496 */ "glReadBuffer",
    /*  497 */ "glReadPixels",
    /*  498 */ "glRectd",
    /*  499 */ "glRectdv",
    /*  500 */ "glRectf",
    /*  501 */ "glRectfv",
    /*  502 */ "glRecti",
    /*  503 */ "glRectiv",
    /*  504 */ "glRects",
    /*  505 */ "glRectsv",
    /*  506 */ "glRenderMode",
    /*  507 */ "glRotated",
    /*  508 */ "glRotatef",
    /*  509 */ "glScaled",
    /*  510 */ "glScalef",
    /*  511 */ "glScissor",
    /*  512 */ "glSelectBuffer",
    /*  513 */ "glShadeModel",
    /*  514 */ "glStencilFunc",
    /*  515 */ "glStencilMask",
    /*  516 */ "glStencilOp",
    /*  517 */ "glTexCoord1d",
    /*  518 */ "glTexCoord1dv",
    /*  519 */ "glTexCoord1f",
    /*  520 */ "glTexCoord1fv",
    /*  521 */ "glTexCoord1i",
    /*  522 */ "glTexCoord1iv",
    /*  523 */ "glTexCoord1s",
    /*  524 */ "glTexCoord1sv",
    /*  525 */ "glTexCoord2d",
    /*  526 */ "glTexCoord2dv",
    /*  527 */ "glTexCoord2f",
    /*  528 */ "glTexCoord2fv",
    /*  529 */ "glTexCoord2i",
    /*  530 */ "glTexCoord2iv",
    /*  531 */ "glTexCoord2s",
    /*  532 */ "glTexCoord2sv",
    /*  533 */ "glTexCoord3d",
    /*  534 */ "glTexCoord3dv",
    /*  535 */ "glTexCoord3f",
    /*  536 */ "glTexCoord3fv",
    /*  537 */ "glTexCoord3i",
    /*  538 */ "glTexCoord3iv",
    /*  539 */ "glTexCoord3s",
    /*  540 */ "glTexCoord3sv",
    /*  541 */ "glTexCoord4d",
    /*  542 */ "glTexCoord4dv",
    /*  543 */ "glTexCoord4f",
    /*  544 */ "glTexCoord4fv",
    /*  545 */ "glTexCoord4i",
    /*  546 */ "glTexCoord4iv",
    /*  547 */ "glTexCoord4s",
    /*  548 */ "glTexCoord4sv",
    /*  549 */ "glTexCoordPointer",
    /*  550 */ "glTexCoordPointerEXT",
    /*  551 */ "glTexEnvf",
    /*  552 */ "glTexEnvfv",
    /*  553 */ "glTexEnvi",
    /*  554 */ "glTexEnviv",
    /*  555 */ "glTexGend",
    /*  556 */ "glTexGendv",
    /*  557 */ "glTexGenf",
    /*  558 */ "glTexGenfv",
    /*  559 */ "glTexGeni",
    /*  560 */ "glTexGeniv",
    /*  561 */ "glTexImage1D",
    /*  562 */ "glTexImage2D",
    /*  563 */ "glTexImage3D",
    /*  564 */ "glTexImage3DEXT",
    /*  565 */ "glTexParameterf",
    /*  566 */ "glTexParameterfv",
    /*  567 */ "glTexParameteri",
    /*  568 */ "glTexParameteriv",
    /*  569 */ "glTexStorage1DEXT",
    /*  570 */ "glTexStorage2DEXT",
    /*  571 */ "glTexStorage3DEXT",
    /*  572 */ "glTexSubImage1D",
    /*  573 */ "glTexSubImage1DEXT",
    /*  574 */ "glTexSubImage2D",
    /*  575 */ "glTexSubImage2DEXT",
    /*  576 */ "glTexSubImage3D",
    /*  577 */ "glTexSubImage3DEXT",
    /*  578 */ "glTextureBufferEXT",
    /*  579 */ "glTextureBufferRangeEXT",
    /*  580 */ "glTextureImage1DEXT",
    /*  581 */ "glTextureImage2DEXT",
    /*  582 */ "glTextureImage3DEXT",
    /*  583 */ "glTexturePageCommitmentEXT",
    /*  584 */ "glTextureParameterIivEXT",
    /*  585 */ "glTextureParameterIuivEXT",
    /*  586 */ "glTextureParameterfEXT",
    /*  587 */ "glTextureParameterfvEXT",
    /*  588 */ "glTextureParameteriEXT",
    /*  589 */ "glTextureParameterivEXT",
    /*  590 */ "glTextureRenderbufferEXT",
    /*  591 */ "glTextureStorage1DEXT",
    /*  592 */ "glTextureStorage2DEXT",
    /*  593 */ "glTextureStorage2DMultisampleEXT",
    /*  594 */ "glTextureStorage3DEXT",
    /*  595 */ "glTextureStorage3DMultisampleEXT",
    /*  596 */ "glTextureSubImage1DEXT",
    /*  597 */ "glTextureSubImage2DEXT",
    /*  598 */ "glTextureSubImage3DEXT",
    /*  599 */ "glTranslated",
    /*  600 */ "glTranslatef",
    /*  601 */ "glUnmapBufferARB",
    /*  602 */ "glUnmapNamedBufferEXT",
    /*  603 */ "glVertex2d",
    /*  604 */ "glVertex2dv",
    /*  605 */ "glVertex2f",
    /*  606 */ "glVertex2fv",
    /*  607 */ "glVertex2i",
    /*  608 */ "glVertex2iv",
    /*  609 */ "glVertex2s",
    /*  610 */ "glVertex2sv",
    /*  611 */ "glVertex3d",
    /*  612 */ "glVertex3dv",
    /*  613 */ "glVertex3f",
    /*  614 */ "glVertex3fv",
    /*  615 */ "glVertex3i",
    /*  616 */ "glVertex3iv",
    /*  617 */ "glVertex3s",
    /*  618 */ "glVertex3sv",
    /*  619 */ "glVertex4d",
    /*  620 */ "glVertex4dv",
    /*  621 */ "glVertex4f",
    /*  622 */ "glVertex4fv",
    /*  623 */ "glVertex4i",
    /*  624 */ "glVertex4iv",
    /*  625 */ "glVertex4s",
    /*  626 */ "glVertex4sv",
    /*  627 */ "glVertexArrayBindVertexBufferEXT",
    /*  628 */ "glVertexArrayColorOffsetEXT",
    /*  629 */ "glVertexArrayEdgeFlagOffsetEXT",
    /*  630 */ "glVertexArrayFogCoordOffsetEXT",
    /*  631 */ "glVertexArrayIndexOffsetEXT",
    /*  632 */ "glVertexArrayMultiTexCoordOffsetEXT",
    /*  633 */ "glVertexArrayNormalOffsetEXT",
    /*  634 */ "glVertexArraySecondaryColorOffsetEXT",
    /*  635 */ "glVertexArrayTexCoordOffsetEXT",
    /*  636 */ "glVertexArrayVertexAttribBindingEXT",
    /*  637 */ "glVertexArrayVertexAttribDivisorEXT",
    /*  638 */ "glVertexArrayVertexAttribFormatEXT",
    /*  639 */ "glVertexArrayVertexAttribIFormatEXT",
    /*  640 */ "glVertexArrayVertexAttribIOffsetEXT",
    /*  641 */ "glVertexArrayVertexAttribLFormatEXT",
    /*  642 */ "glVertexArrayVertexAttribLOffsetEXT",
    /*  643 */ "glVertexArrayVertexAttribOffsetEXT",
    /*  644 */ "glVertexArrayVertexBindingDivisorEXT",
    /*  645 */ "glVertexArrayVertexOffsetEXT",
    /*  646 */ "glVertexPointer",
    /*  647 */ "glVertexPointerEXT",
    /*  648 */ "glViewport",
    /*  649 */ "glActiveShaderProgram",
    /*  650 */ "glActiveShaderProgramEXT",
    /*  651 */ "glActiveTexture",
    /*  652 */ "glAttachShader",
    /*  653 */ "glBeginQuery",
    /*  654 */ "glBeginQueryEXT",
    /*  655 */ "glBeginTransformFeedback",
    /*  656 */ "glBindAttribLocation",
    /*  657 */ "glBindBuffer",
    /*  658 */ "glBindBufferBase",
    /*  659 */ "glBindBufferRange",
    /*  660 */ "glBindFramebuffer",
    /*  661 */ "glBindImageTexture",
    /*  662 */ "glBindProgramPipeline",
    /*  663 */ "glBindProgramPipelineEXT",
    /*  664 */ "glBindRenderbuffer",
    /*  665 */ "glBindSampler",
    /*  666 */ "glBindTransformFeedback",
    /*  667 */ "glBindVertexArray",
    /*  668 */ "glBindVertexArrayOES",
    /*  669 */ "glBindVertexBuffer",
    /*  670 */ "glBlendBarrier",
    /*  671 */ "glBlendBarrierKHR",
    /*  672 */ "glBlendBarrierNV",
    /*  673 */ "glBlendColor",
    /*  674 */ "glBlendEquation",
    /*  675 */ "glBlendEquationSeparate",
    /*  676 */ "glBlendEquationSeparatei",
    /*  677 */ "glBlendEquationSeparateiEXT",
    /*  678 */ "glBlendEquationSeparateiOES",
    /*  679 */ "glBlendEquationi",
    /*  680 */ "glBlendEquationiEXT",
    /*  681 */ "glBlendEquationiOES",
    /*  682 */ "glBlendFuncSeparate",
    /*  683 */ "glBlendFuncSeparatei",
    /*  684 */ "glBlendFuncSeparateiEXT",
    /*  685 */ "glBlendFuncSeparateiOES",
    /*  686 */ "glBlendFunci",
    /*  687 */ "glBlendFunciEXT",
    /*  688 */ "glBlendFunciOES",
    /*  689 */ "glBlendParameteriNV",
    /*  690 */ "glBlitFramebuffer",
    /*  691 */ "glBlitFramebufferNV",
    /*  692 */ "glBufferData",
    /*  693 */ "glBufferSubData",
    /*  694 */ "glCheckFramebufferStatus",
    /*  695 */ "glClearBufferfi",
    /*  696 */ "glClearBufferfv",
    /*  697 */ "glClearBufferiv",
    /*  698 */ "glClearBufferuiv",
    /*  699 */ "glClearDepthf",
    /*  700 */ "glClientWaitSync",
    /*  701 */ "glClientWaitSyncAPPLE",
    /*  702 */ "glColorMaski",
    /*  703 */ "glColorMaskiEXT",
    /*  704 */ "glColorMaskiOES",
    /*  705 */ "glCompileShader",
    /*  706 */ "glCompressedTexImage2D",
    /*  707 */ "glCompressedTexImage3D",
    /*  708 */ "glCompressedTexSubImage2D",
    /*  709 */ "glCompressedTexSubImage3D",
    /*  710 */ "glCopyBufferSubData",
    /*  711 */ "glCopyBufferSubDataNV",
    /*  712 */ "glCopyImageSubData",
    /*  713 */ "glCopyImageSubDataEXT",
    /*  714 */ "glCopyImageSubDataOES",
    /*  715 */ "glCreateProgram",
    /*  716 */ "glCreateShader",
    /*  717 */ "glCreateShaderProgramv",
    /*  718 */ "glCreateShaderProgramvEXT",
    /*  719 */ "glDebugMessageCallbackKHR",
    /*  720 */ "glDebugMessageControlKHR",
    /*  721 */ "glDebugMessageInsertKHR",
    /*  722 */ "glDeleteBuffers",
    /*  723 */ "glDeleteFramebuffers",
    /*  724 */ "glDeleteProgram",
    /*  725 */ "glDeleteProgramPipelines",
    /*  726 */ "glDeleteProgramPipelinesEXT",
    /*  727 */ "glDeleteQueries",
    /*  728 */ "glDeleteQueriesEXT",
    /*  729 */ "glDeleteRenderbuffers",
    /*  730 */ "glDeleteSamplers",
    /*  731 */ "glDeleteShader",
    /*  732 */ "glDeleteSync",
    /*  733 */ "glDeleteSyncAPPLE",
    /*  734 */ "glDeleteTransformFeedbacks",
    /*  735 */ "glDeleteVertexArrays",
    /*  736 */ "glDeleteVertexArraysOES",
    /*  737 */ "glDepthRangeArrayfvNV",
    /*  738 */ "glDepthRangeArrayfvOES",
    /*  739 */ "glDepthRangeIndexedfNV",
    /*  740 */ "glDepthRangeIndexedfOES",
    /*  741 */ "glDepthRangef",
    /*  742 */ "glDetachShader",
    /*  743 */ "glDisableVertexAttribArray",
    /*  744 */ "glDisablei",
    /*  745 */ "glDisableiEXT",
    /*  746 */ "glDisableiNV",
    /*  747 */ "glDisableiOES",
    /*  748 */ "glDispatchCompute",
    /*  749 */ "glDispatchComputeIndirect",
    /*  750 */ "glDrawArraysIndirect",
    /*  751 */ "glDrawArraysInstanced",
    /*  752 */ "glDrawArraysInstancedANGLE",
    /*  753 */ "glDrawArraysInstancedEXT",
    /*  754 */ "glDrawArraysInstancedNV",
    /*  755 */ "glDrawBuffers",
    /*  756 */ "glDrawBuffersEXT",
    /*  757 */ "glDrawElementsBaseVertex",
    /*  758 */ "glDrawElementsBaseVertexEXT",
    /*  759 */ "glDrawElementsBaseVertexOES",
    /*  760 */ "glDrawElementsIndirect",
    /*  761 */ "glDrawElementsInstanced",
    /*  762 */ "glDrawElementsInstancedANGLE",
    /*  763 */ "glDrawElementsInstancedBaseVertex",
    /*  764 */ "glDrawElementsInstancedBaseVertexEXT",
    /*  765 */ "glDrawElementsInstancedBaseVertexOES",
    /*  766 */ "glDrawElementsInstancedEXT",
    /*  767 */ "glDrawElementsInstancedNV",
    /*  768 */ "glDrawRangeElementsBaseVertex",
    /*  769 */ "glDrawRangeElementsBaseVertexEXT",
    /*  770 */ "glDrawRangeElementsBaseVertexOES",
    /*  771 */ "glEnableVertexAttribArray",
    /*  772 */ "glEnablei",
    /*  773 */ "glEnableiEXT",
    /*  774 */ "glEnableiNV",
    /*  775 */ "glEnableiOES",
    /*  776 */ "glEndQuery",
    /*  777 */ "glEndQueryEXT",
    /*  778 */ "glEndTransformFeedback",
    /*  779 */ "glFenceSync",
    /*  780 */ "glFenceSyncAPPLE",
    /*  781 */ "glFlushMappedBufferRange",
    /*  782 */ "glFlushMappedBufferRangeEXT",
    /*  783 */ "glFramebufferParameteri",
    /*  784 */ "glFramebufferRenderbuffer",
    /*  785 */ "glFramebufferTexture",
    /*  786 */ "glFramebufferTexture2D",
    /*  787 */ "glFramebufferTexture2DMultisampleEXT",
    /*  788 */ "glFramebufferTextureEXT",
    /*  789 */ "glFramebufferTextureLayer",
    /*  790 */ "glFramebufferTextureOES",
    /*  791 */ "glGenBuffers",
    /*  792 */ "glGenFramebuffers",
    /*  793 */ "glGenProgramPipelines",
    /*  794 */ "glGenProgramPipelinesEXT",
    /*  795 */ "glGenQueries",
    /*  796 */ "glGenQueriesEXT",
    /*  797 */ "glGenRenderbuffers",
    /*  798 */ "glGenSamplers",
    /*  799 */ "glGenTransformFeedbacks",
    /*  800 */ "glGenVertexArrays",
    /*  801 */ "glGenVertexArraysOES",
    /*  802 */ "glGenerateMipmap",
    /*  803 */ "glGetActiveAttrib",
    /*  804 */ "glGetActiveUniform",
    /*  805 */ "glGetActiveUniformBlockName",
    /*  806 */ "glGetActiveUniformBlockiv",
    /*  807 */ "glGetActiveUniformsiv",
    /*  808 */ "glGetAttachedShaders",
    /*  809 */ "glGetAttribLocation",
    /*  810 */ "glGetBooleani_v",
    /*  811 */ "glGetBufferParameteri64v",
    /*  812 */ "glGetBufferParameteriv",
    /*  813 */ "glGetBufferPointerv",
    /*  814 */ "glGetBufferPointervOES",
    /*  815 */ "glGetDebugMessageLogKHR",
    /*  816 */ "glGetFloati_vNV",
    /*  817 */ "glGetFloati_vOES",
    /*  818 */ "glGetFragDataLocation",
    /*  819 */ "glGetFramebufferAttachmentParameteriv",
    /*  820 */ "glGetFramebufferParameteriv",
    /*  821 */ "glGetGraphicsResetStatus",
    /*  822 */ "glGetGraphicsResetStatusEXT",
    /*  823 */ "glGetGraphicsResetStatusKHR",
    /*  824 */ "glGetInteger64i_v",
    /*  825 */ "glGetInteger64v",
    /*  826 */ "glGetInteger64vAPPLE",
    /*  827 */ "glGetInteger64vEXT",
    /*  828 */ "glGetIntegeri_v",
    /*  829 */ "glGetInternalformativ",
    /*  830 */ "glGetMultisamplefv",
    /*  831 */ "glGetObjectLabelKHR",
    /*  832 */ "glGetObjectPtrLabelKHR",
    /*  833 */ "glGetPointervKHR",
    /*  834 */ "glGetProgramBinary",
    /*  835 */ "glGetProgramBinaryOES",
    /*  836 */ "glGetProgramInfoLog",
    /*  837 */ "glGetProgramInterfaceiv",
    /*  838 */ "glGetProgramPipelineInfoLog",
    /*  839 */ "glGetProgramPipelineInfoLogEXT",
    /*  840 */ "glGetProgramPipelineiv",
    /*  841 */ "glGetProgramPipelineivEXT",
    /*  842 */ "glGetProgramResourceIndex",
    /*  843 */ "glGetProgramResourceLocation",
    /*  844 */ "glGetProgramResourceName",
    /*  845 */ "glGetProgramResourceiv",
    /*  846 */ "glGetProgramiv",
    /*  847 */ "glGetQueryObjecti64vEXT",
    /*  848 */ "glGetQueryObjectivEXT",
    /*  849 */ "glGetQueryObjectui64vEXT",
    /*  850 */ "glGetQueryObjectuiv",
    /*  851 */ "glGetQueryObjectuivEXT",
    /*  852 */ "glGetQueryiv",
    /*  853 */ "glGetQueryivEXT",
    /*  854 */ "glGetRenderbufferParameteriv",
    /*  855 */ "glGetSamplerParameterIiv",
    /*  856 */ "glGetSamplerParameterIivEXT",
    /*  857 */ "glGetSamplerParameterIivOES",
    /*  858 */ "glGetSamplerParameterIuiv",
    /*  859 */ "glGetSamplerParameterIuivEXT",
    /*  860 */ "glGetSamplerParameterIuivOES",
    /*  861 */ "glGetSamplerParameterfv",
    /*  862 */ "glGetSamplerParameteriv",
    /*  863 */ "glGetShaderInfoLog",
    /*  864 */ "glGetShaderPrecisionFormat",
    /*  865 */ "glGetShaderSource",
    /*  866 */ "glGetShaderiv",
    /*  867 */ "glGetStringi",
    /*  868 */ "glGetSynciv",
    /*  869 */ "glGetSyncivAPPLE",
    /*  870 */ "glGetTexParameterIiv",
    /*  871 */ "glGetTexParameterIivEXT",
    /*  872 */ "glGetTexParameterIivOES",
    /*  873 */ "glGetTexParameterIuiv",
    /*  874 */ "glGetTexParameterIuivEXT",
    /*  875 */ "glGetTexParameterIuivOES",
    /*  876 */ "glGetTransformFeedbackVarying",
    /*  877 */ "glGetUniformBlockIndex",
    /*  878 */ "glGetUniformIndices",
    /*  879 */ "glGetUniformLocation",
    /*  880 */ "glGetUniformfv",
    /*  881 */ "glGetUniformiv",
    /*  882 */ "glGetUniformuiv",
    /*  883 */ "glGetVertexAttribIiv",
    /*  884 */ "glGetVertexAttribIuiv",
    /*  885 */ "glGetVertexAttribPointerv",
    /*  886 */ "glGetVertexAttribfv",
    /*  887 */ "glGetVertexAttribiv",
    /*  888 */ "glGetnUniformfv",
    /*  889 */ "glGetnUniformfvEXT",
    /*  890 */ "glGetnUniformfvKHR",
    /*  891 */ "glGetnUniformiv",
    /*  892 */ "glGetnUniformivEXT",
    /*  893 */ "glGetnUniformivKHR",
    /*  894 */ "glGetnUniformuiv",
    /*  895 */ "glGetnUniformuivKHR",
    /*  896 */ "glInvalidateFramebuffer",
    /*  897 */ "glInvalidateSubFramebuffer",
    /*  898 */ "glIsBuffer",
    /*  899 */ "glIsEnabledi",
    /*  900 */ "glIsEnablediEXT",
    /*  901 */ "glIsEnablediNV",
    /*  902 */ "glIsEnablediOES",
    /*  903 */ "glIsFramebuffer",
    /*  904 */ "glIsProgram",
    /*  905 */ "glIsProgramPipeline",
    /*  906 */ "glIsProgramPipelineEXT",
    /*  907 */ "glIsQuery",
    /*  908 */ "glIsQueryEXT",
    /*  909 */ "glIsRenderbuffer",
    /*  910 */ "glIsSampler",
    /*  911 */ "glIsShader",
    /*  912 */ "glIsSync",
    /*  913 */ "glIsSyncAPPLE",
    /*  914 */ "glIsTransformFeedback",
    /*  915 */ "glIsVertexArray",
    /*  916 */ "glIsVertexArrayOES",
    /*  917 */ "glLinkProgram",
    /*  918 */ "glMapBufferOES",
    /*  919 */ "glMapBufferRange",
    /*  920 */ "glMapBufferRangeEXT",
    /*  921 */ "glMemoryBarrier",
    /*  922 */ "glMemoryBarrierByRegion",
    /*  923 */ "glMinSampleShading",
    /*  924 */ "glMinSampleShadingOES",
    /*  925 */ "glMultiDrawElementsBaseVertexEXT",
    /*  926 */ "glObjectLabelKHR",
    /*  927 */ "glObjectPtrLabelKHR",
    /*  928 */ "glPatchParameteri",
    /*  929 */ "glPatchParameteriEXT",
    /*  930 */ "glPatchParameteriOES",
    /*  931 */ "glPauseTransformFeedback",
    /*  932 */ "glPopDebugGroupKHR",
    /*  933 */ "glPrimitiveBoundingBox",
    /*  934 */ "glPrimitiveBoundingBoxEXT",
    /*  935 */ "glPrimitiveBoundingBoxOES",
    /*  936 */ "glProgramBinary",
    /*  937 */ "glProgramBinaryOES",
    /*  938 */ "glProgramParameteri",
    /*  939 */ "glProgramParameteriEXT",
    /*  940 */ "glProgramUniform1f",
    /*  941 */ "glProgramUniform1fv",
    /*  942 */ "glProgramUniform1i",
    /*  943 */ "glProgramUniform1iv",
    /*  944 */ "glProgramUniform1ui",
    /*  945 */ "glProgramUniform1uiv",
    /*  946 */ "glProgramUniform2f",
    /*  947 */ "glProgramUniform2fv",
    /*  948 */ "glProgramUniform2i",
    /*  949 */ "glProgramUniform2iv",
    /*  950 */ "glProgramUniform2ui",
    /*  951 */ "glProgramUniform2uiv",
    /*  952 */ "glProgramUniform3f",
    /*  953 */ "glProgramUniform3fv",
    /*  954 */ "glProgramUniform3i",
    /*  955 */ "glProgramUniform3iv",
    /*  956 */ "glProgramUniform3ui",
    /*  957 */ "glProgramUniform3uiv",
    /*  958 */ "glProgramUniform4f",
    /*  959 */ "glProgramUniform4fv",
    /*  960 */ "glProgramUniform4i",
    /*  961 */ "glProgramUniform4iv",
    /*  962 */ "glProgramUniform4ui",
    /*  963 */ "glProgramUniform4uiv",
    /*  964 */ "glProgramUniformMatrix2fv",
    /*  965 */ "glProgramUniformMatrix2x3fv",
    /*  966 */ "glProgramUniformMatrix2x4fv",
    /*  967 */ "glProgramUniformMatrix3fv",
    /*  968 */ "glProgramUniformMatrix3x2fv",
    /*  969 */ "glProgramUniformMatrix3x4fv",
    /*  970 */ "glProgramUniformMatrix4fv",
    /*  971 */ "glProgramUniformMatrix4x2fv",
    /*  972 */ "glProgramUniformMatrix4x3fv",
    /*  973 */ "glPushDebugGroupKHR",
    /*  974 */ "glQueryCounterEXT",
    /*  975 */ "glReadnPixels",
    /*  976 */ "glReadnPixelsEXT",
    /*  977 */ "glReadnPixelsKHR",
    /*  978 */ "glReleaseShaderCompiler",
    /*  979 */ "glRenderbufferStorage",
    /*  980 */ "glRenderbufferStorageMultisample",
    /*  981 */ "glRenderbufferStorageMultisampleEXT",
    /*  982 */ "glRenderbufferStorageMultisampleNV",
    /*  983 */ "glResumeTransformFeedback",
    /*  984 */ "glSampleCoverage",
    /*  985 */ "glSampleMaski",
    /*  986 */ "glSamplerParameterIiv",
    /*  987 */ "glSamplerParameterIivEXT",
    /*  988 */ "glSamplerParameterIivOES",
    /*  989 */ "glSamplerParameterIuiv",
    /*  990 */ "glSamplerParameterIuivEXT",
    /*  991 */ "glSamplerParameterIuivOES",
    /*  992 */ "glSamplerParameterf",
    /*  993 */ "glSamplerParameterfv",
    /*  994 */ "glSamplerParameteri",
    /*  995 */ "glSamplerParameteriv",
    /*  996 */ "glScissorArrayvNV",
    /*  997 */ "glScissorArrayvOES",
    /*  998 */ "glScissorIndexedNV",
    /*  999 */ "glScissorIndexedOES",
    /* 1000 */ "glScissorIndexedvNV",
    /* 1001 */ "glScissorIndexedvOES",
    /* 1002 */ "glShaderBinary",
    /* 1003 */ "glShaderSource",
    /* 1004 */ "glStencilFuncSeparate",
    /* 1005 */ "glStencilMaskSeparate",
    /* 1006 */ "glStencilOpSeparate",
    /* 1007 */ "glTexBuffer",
    /* 1008 */ "glTexBufferEXT",
    /* 1009 */ "glTexBufferOES",
    /* 1010 */ "glTexBufferRange",
    /* 1011 */ "glTexBufferRangeEXT",
    /* 1012 */ "glTexBufferRangeOES",
    /* 1013 */ "glTexParameterIiv",
    /* 1014 */ "glTexParameterIivEXT",
    /* 1015 */ "glTexParameterIivOES",
    /* 1016 */ "glTexParameterIuiv",
    /* 1017 */ "glTexParameterIuivEXT",
    /* 1018 */ "glTexParameterIuivOES",
    /* 1019 */ "glTexStorage2D",
    /* 1020 */ "glTexStorage2DMultisample",
    /* 1021 */ "glTexStorage3D",
    /* 1022 */ "glTexStorage3DMultisample",
    /* 1023 */ "glTexStorage3DMultisampleOES",
    /* 1024 */ "glTransformFeedbackVaryings",
    /* 1025 */ "glUniform1f",
    /* 1026 */ "glUniform1fv",
    /* 1027 */ "glUniform1i",
    /* 1028 */ "glUniform1iv",
    /* 1029 */ "glUniform1ui",
    /* 1030 */ "glUniform1uiv",
    /* 1031 */ "glUniform2f",
    /* 1032 */ "glUniform2fv",
    /* 1033 */ "glUniform2i",
    /* 1034 */ "glUniform2iv",
    /* 1035 */ "glUniform2ui",
    /* 1036 */ "glUniform2uiv",
    /* 1037 */ "glUniform3f",
    /* 1038 */ "glUniform3fv",
    /* 1039 */ "glUniform3i",
    /* 1040 */ "glUniform3iv",
    /* 1041 */ "glUniform3ui",
    /* 1042 */ "glUniform3uiv",
    /* 1043 */ "glUniform4f",
    /* 1044 */ "glUniform4fv",
    /* 1045 */ "glUniform4i",
    /* 1046 */ "glUniform4iv",
    /* 1047 */ "glUniform4ui",
    /* 1048 */ "glUniform4uiv",
    /* 1049 */ "glUniformBlockBinding",
    /* 1050 */ "glUniformMatrix2fv",
    /* 1051 */ "glUniformMatrix2x3fv",
    /* 1052 */ "glUniformMatrix2x3fvNV",
    /* 1053 */ "glUniformMatrix2x4fv",
    /* 1054 */ "glUniformMatrix2x4fvNV",
    /* 1055 */ "glUniformMatrix3fv",
    /* 1056 */ "glUniformMatrix3x2fv",
    /* 1057 */ "glUniformMatrix3x2fvNV",
    /* 1058 */ "glUniformMatrix3x4fv",
    /* 1059 */ "glUniformMatrix3x4fvNV",
    /* 1060 */ "glUniformMatrix4fv",
    /* 1061 */ "glUniformMatrix4x2fv",
    /* 1062 */ "glUniformMatrix4x2fvNV",
    /* 1063 */ "glUniformMatrix4x3fv",
    /* 1064 */ "glUniformMatrix4x3fvNV",
    /* 1065 */ "glUnmapBuffer",
    /* 1066 */ "glUnmapBufferOES",
    /* 1067 */ "glUseProgram",
    /* 1068 */ "glUseProgramStages",
    /* 1069 */ "glUseProgramStagesEXT",
    /* 1070 */ "glValidateProgram",
    /* 1071 */ "glValidateProgramPipeline",
    /* 1072 */ "glValidateProgramPipelineEXT",
    /* 1073 */ "glVertexAttrib1f",
    /* 1074 */ "glVertexAttrib1fv",
    /* 1075 */ "glVertexAttrib2f",
    /* 1076 */ "glVertexAttrib2fv",
    /* 1077 */ "glVertexAttrib3f",
    /* 1078 */ "glVertexAttrib3fv",
    /* 1079 */ "glVertexAttrib4f",
    /* 1080 */ "glVertexAttrib4fv",
    /* 1081 */ "glVertexAttribBinding",
    /* 1082 */ "glVertexAttribDivisor",
    /* 1083 */ "glVertexAttribDivisorANGLE",
    /* 1084 */ "glVertexAttribDivisorEXT",
    /* 1085 */ "glVertexAttribDivisorNV",
    /* 1086 */ "glVertexAttribFormat",
    /* 1087 */ "glVertexAttribI4i",
    /* 1088 */ "glVertexAttribI4iv",
    /* 1089 */ "glVertexAttribI4ui",
    /* 1090 */ "glVertexAttribI4uiv",
    /* 1091 */ "glVertexAttribIFormat",
    /* 1092 */ "glVertexAttribIPointer",
    /* 1093 */ "glVertexAttribPointer",
    /* 1094 */ "glVertexBindingDivisor",
    /* 1095 */ "glViewportArrayvNV",
    /* 1096 */ "glViewportArrayvOES",
    /* 1097 */ "glViewportIndexedfNV",
    /* 1098 */ "glViewportIndexedfOES",
    /* 1099 */ "glViewportIndexedfvNV",
    /* 1100 */ "glViewportIndexedfvOES",
    /* 1101 */ "glWaitSync",
    /* 1102 */ "glWaitSyncAPPLE"
};

static uint64_t GLAD_GL_ext_hashes[] = {
    /*    0 */ 0xf21d57ef70efa97f, /* GL_ANGLE_instanced_arrays */
    /*    1 */ 0x965df8be0c61c5ef, /* GL_APPLE_sync */
    /*    2 */ 0x2aa09aeb0f69408b, /* GL_ARB_buffer_storage */
    /*    3 */ 0x2b16e3dcc2f78c79, /* GL_ARB_debug_output */
    /*    4 */ 0xab4f226cf8bf14b2, /* GL_ARB_vertex_buffer_object */
    /*    5 */ 0xa26b121ae33c3436, /* GL_EXT_copy_image */
    /*    6 */ 0x2611c2618f21aa2f, /* GL_EXT_copy_texture */
    /*    7 */ 0xff4a74da40c62745, /* GL_EXT_direct_state_access */
    /*    8 */ 0x3d06b0f91612d10d, /* GL_EXT_disjoint_timer_query */
    /*    9 */ 0xd3ac9ca278a62f1a, /* GL_EXT_draw_buffers */
    /*   10 */ 0x997893a6ac44f7fe, /* GL_EXT_draw_buffers_indexed */
    /*   11 */ 0x548657f15226635b, /* GL_EXT_draw_elements_base_vertex */
    /*   12 */ 0xeb1b622faf7697c7, /* GL_EXT_draw_instanced */
    /*   13 */ 0xbb5e6eb0e1559ef1, /* GL_EXT_draw_range_elements */
    /*   14 */ 0xfa22129bb4d04128, /* GL_EXT_geometry_shader */
    /*   15 */ 0x9c3c026caab1aaf7, /* GL_EXT_instanced_arrays */
    /*   16 */ 0xf41152d50d03cc16, /* GL_EXT_map_buffer_range */
    /*   17 */ 0x33b89ab037aed106, /* GL_EXT_multisampled_render_to_texture */
    /*   18 */ 0x849565c10789238e, /* GL_EXT_primitive_bounding_box */
    /*   19 */ 0x04aaf7c50fd23609, /* GL_EXT_robustness */
    /*   20 */ 0xb207ff65f8bf495d, /* GL_EXT_separate_shader_objects */
    /*   21 */ 0xe101571ccdddbe44, /* GL_EXT_subtexture */
    /*   22 */ 0xa694e21c70c92ac7, /* GL_EXT_tessellation_shader */
    /*   23 */ 0x3c1975837c97841b, /* GL_EXT_texture3D */
    /*   24 */ 0xf02848fc36653917, /* GL_EXT_texture_border_clamp */
    /*   25 */ 0x990b742e339cfdab, /* GL_EXT_texture_buffer */
    /*   26 */ 0x10827f593acd1ba7, /* GL_EXT_texture_object */
    /*   27 */ 0x154c4c8b80533dc0, /* GL_EXT_texture_storage */
    /*   28 */ 0x2347ebc551d02975, /* GL_EXT_vertex_array */
    /*   29 */ 0x898f16e7a19612fe, /* GL_KHR_blend_equation_advanced */
    /*   30 */ 0x5e0c5b9607ac8784, /* GL_KHR_debug */
    /*   31 */ 0x474beac5f6910636, /* GL_KHR_robustness */
    /*   32 */ 0xa14ebc048c19e849, /* GL_MESA_sampler_objects */
    /*   33 */ 0xdfb2fe6dc8d05e7b, /* GL_NV_blend_equation_advanced */
    /*   34 */ 0x1250d4e984fabb8a, /* GL_NV_copy_buffer */
    /*   35 */ 0x5cef483902a0a7d1, /* GL_NV_draw_instanced */
    /*   36 */ 0xc7b0688e759eacca, /* GL_NV_framebuffer_blit */
    /*   37 */ 0xd333a1d53faf1645, /* GL_NV_framebuffer_multisample */
    /*   38 */ 0xc2e8b0284eeb3343, /* GL_NV_instanced_arrays */
    /*   39 */ 0x5b891d5155380820, /* GL_NV_non_square_matrices */
    /*   40 */ 0x1b9db3e10e73323b, /* GL_NV_viewport_array */
    /*   41 */ 0xc5e1ddc1ea43276e, /* GL_OES_copy_image */
    /*   42 */ 0x012b99c59ced284f, /* GL_OES_draw_buffers_indexed */
    /*   43 */ 0x4638dd889d2b7eab, /* GL_OES_draw_elements_base_vertex */
    /*   44 */ 0xaa384a84e450d595, /* GL_OES_geometry_shader */
    /*   45 */ 0x503ad238c5e97931, /* GL_OES_get_program_binary */
    /*   46 */ 0x22e521fe25c89a3b, /* GL_OES_mapbuffer */
    /*   47 */ 0x303e15e4f8fb9ee6, /* GL_OES_primitive_bounding_box */
    /*   48 */ 0xcb740362814f4ca0, /* GL_OES_sample_shading */
    /*   49 */ 0x8bbb4c0c94dc1415, /* GL_OES_tessellation_shader */
    /*   50 */ 0xedc39fcb928c7be5, /* GL_OES_texture_border_clamp */
    /*   51 */ 0xc7d6a2d8a596bf50, /* GL_OES_texture_buffer */
    /*   52 */ 0xbc655ee4febdcfca, /* GL_OES_texture_storage_multisample_2d_array */
    /*   53 */ 0x7cd6041965da7d3c, /* GL_OES_vertex_array_object */
    /*   54 */ 0x2e0ac92809baabbd  /* GL_OES_viewport_array */
};

#ifdef __cplusplus
GladGLContext glad_gl_context = {};
#else
GladGLContext glad_gl_context = { 0 };
#endif

static void glad_gl_load_GL_VERSION_1_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           0, /* glAccum */
           1, /* glAlphaFunc */
           6, /* glBegin */
          11, /* glBitmap */
          12, /* glBlendFunc */
          16, /* glCallList */
          17, /* glCallLists */
          19, /* glClear */
          20, /* glClearAccum */
          21, /* glClearColor */
          22, /* glClearDepth */
          23, /* glClearIndex */
          26, /* glClearStencil */
          28, /* glClipPlane */
          29, /* glColor3b */
          30, /* glColor3bv */
          31, /* glColor3d */
          32, /* glColor3dv */
          33, /* glColor3f */
          34, /* glColor3fv */
          35, /* glColor3i */
          36, /* glColor3iv */
          37, /* glColor3s */
          38, /* glColor3sv */
          39, /* glColor3ub */
          40, /* glColor3ubv */
          41, /* glColor3ui */
          42, /* glColor3uiv */
          43, /* glColor3us */
          44, /* glColor3usv */
          45, /* glColor4b */
          46, /* glColor4bv */
          47, /* glColor4d */
          48, /* glColor4dv */
          49, /* glColor4f */
          50, /* glColor4fv */
          51, /* glColor4i */
          52, /* glColor4iv */
          53, /* glColor4s */
          54, /* glColor4sv */
          55, /* glColor4ub */
          56, /* glColor4ubv */
          57, /* glColor4ui */
          58, /* glColor4uiv */
          59, /* glColor4us */
          60, /* glColor4usv */
          61, /* glColorMask */
          62, /* glColorMaterial */
          82, /* glCopyPixels */
          98, /* glCullFace */
         106, /* glDeleteLists */
         109, /* glDepthFunc */
         110, /* glDepthMask */
         111, /* glDepthRange */
         112, /* glDisable */
         121, /* glDrawBuffer */
         123, /* glDrawPixels */
         126, /* glEdgeFlag */
         129, /* glEdgeFlagv */
         130, /* glEnable */
         137, /* glEnd */
         138, /* glEndList */
         139, /* glEvalCoord1d */
         140, /* glEvalCoord1dv */
         141, /* glEvalCoord1f */
         142, /* glEvalCoord1fv */
         143, /* glEvalCoord2d */
         144, /* glEvalCoord2dv */
         145, /* glEvalCoord2f */
         146, /* glEvalCoord2fv */
         147, /* glEvalMesh1 */
         148, /* glEvalMesh2 */
         149, /* glEvalPoint1 */
         150, /* glEvalPoint2 */
         151, /* glFeedbackBuffer */
         152, /* glFinish */
         153, /* glFlush */
         155, /* glFogf */
         156, /* glFogfv */
         157, /* glFogi */
         158, /* glFogiv */
         162, /* glFrontFace */
         163, /* glFrustum */
         165, /* glGenLists */
         171, /* glGetBooleanv */
         175, /* glGetClipPlane */
         182, /* glGetDoublev */
         183, /* glGetError */
         186, /* glGetFloatv */
         189, /* glGetIntegerv */
         190, /* glGetLightfv */
         191, /* glGetLightiv */
         192, /* glGetMapdv */
         193, /* glGetMapfv */
         194, /* glGetMapiv */
         195, /* glGetMaterialfv */
         196, /* glGetMaterialiv */
         223, /* glGetPixelMapfv */
         224, /* glGetPixelMapuiv */
         225, /* glGetPixelMapusv */
         230, /* glGetPolygonStipple */
         231, /* glGetString */
         232, /* glGetTexEnvfv */
         233, /* glGetTexEnviv */
         234, /* glGetTexGendv */
         235, /* glGetTexGenfv */
         236, /* glGetTexGeniv */
         237, /* glGetTexImage */
         238, /* glGetTexLevelParameterfv */
         239, /* glGetTexLevelParameteriv */
         240, /* glGetTexParameterfv */
         241, /* glGetTexParameteriv */
         253, /* glHint */
         254, /* glIndexMask */
         257, /* glIndexd */
         258, /* glIndexdv */
         259, /* glIndexf */
         260, /* glIndexfv */
         261, /* glIndexi */
         262, /* glIndexiv */
         263, /* glIndexs */
         264, /* glIndexsv */
         267, /* glInitNames */
         270, /* glIsEnabled */
         272, /* glIsList */
         275, /* glLightModelf */
         276, /* glLightModelfv */
         277, /* glLightModeli */
         278, /* glLightModeliv */
         279, /* glLightf */
         280, /* glLightfv */
         281, /* glLighti */
         282, /* glLightiv */
         283, /* glLineStipple */
         284, /* glLineWidth */
         285, /* glListBase */
         286, /* glLoadIdentity */
         287, /* glLoadMatrixd */
         288, /* glLoadMatrixf */
         289, /* glLoadName */
         290, /* glLogicOp */
         291, /* glMap1d */
         292, /* glMap1f */
         293, /* glMap2d */
         294, /* glMap2f */
         296, /* glMapGrid1d */
         297, /* glMapGrid1f */
         298, /* glMapGrid2d */
         299, /* glMapGrid2f */
         302, /* glMaterialf */
         303, /* glMaterialfv */
         304, /* glMateriali */
         305, /* glMaterialiv */
         312, /* glMatrixMode */
         326, /* glMultMatrixd */
         327, /* glMultMatrixf */
         380, /* glNewList */
         381, /* glNormal3b */
         382, /* glNormal3bv */
         383, /* glNormal3d */
         384, /* glNormal3dv */
         385, /* glNormal3f */
         386, /* glNormal3fv */
         387, /* glNormal3i */
         388, /* glNormal3iv */
         389, /* glNormal3s */
         390, /* glNormal3sv */
         395, /* glOrtho */
         396, /* glPassThrough */
         397, /* glPixelMapfv */
         398, /* glPixelMapuiv */
         399, /* glPixelMapusv */
         400, /* glPixelStoref */
         401, /* glPixelStorei */
         402, /* glPixelTransferf */
         403, /* glPixelTransferi */
         404, /* glPixelZoom */
         405, /* glPointSize */
         406, /* glPolygonMode */
         408, /* glPolygonStipple */
         409, /* glPopAttrib */
         412, /* glPopMatrix */
         413, /* glPopName */
         466, /* glPushAttrib */
         470, /* glPushMatrix */
         471, /* glPushName */
         472, /* glRasterPos2d */
         473, /* glRasterPos2dv */
         474, /* glRasterPos2f */
         475, /* glRasterPos2fv */
         476, /* glRasterPos2i */
         477, /* glRasterPos2iv */
         478, /* glRasterPos2s */
         479, /* glRasterPos2sv */
         480, /* glRasterPos3d */
         481, /* glRasterPos3dv */
         482, /* glRasterPos3f */
         483, /* glRasterPos3fv */
         484, /* glRasterPos3i */
         485, /* glRasterPos3iv */
         486, /* glRasterPos3s */
         487, /* glRasterPos3sv */
         488, /* glRasterPos4d */
         489, /* glRasterPos4dv */
         490, /* glRasterPos4f */
         491, /* glRasterPos4fv */
         492, /* glRasterPos4i */
         493, /* glRasterPos4iv */
         494, /* glRasterPos4s */
         495, /* glRasterPos4sv */
         496, /* glReadBuffer */
         497, /* glReadPixels */
         498, /* glRectd */
         499, /* glRectdv */
         500, /* glRectf */
         501, /* glRectfv */
         502, /* glRecti */
         503, /* glRectiv */
         504, /* glRects */
         505, /* glRectsv */
         506, /* glRenderMode */
         507, /* glRotated */
         508, /* glRotatef */
         509, /* glScaled */
         510, /* glScalef */
         511, /* glScissor */
         512, /* glSelectBuffer */
         513, /* glShadeModel */
         514, /* glStencilFunc */
         515, /* glStencilMask */
         516, /* glStencilOp */
         517, /* glTexCoord1d */
         518, /* glTexCoord1dv */
         519, /* glTexCoord1f */
         520, /* glTexCoord1fv */
         521, /* glTexCoord1i */
         522, /* glTexCoord1iv */
         523, /* glTexCoord1s */
         524, /* glTexCoord1sv */
         525, /* glTexCoord2d */
         526, /* glTexCoord2dv */
         527, /* glTexCoord2f */
         528, /* glTexCoord2fv */
         529, /* glTexCoord2i */
         530, /* glTexCoord2iv */
         531, /* glTexCoord2s */
         532, /* glTexCoord2sv */
         533, /* glTexCoord3d */
         534, /* glTexCoord3dv */
         535, /* glTexCoord3f */
         536, /* glTexCoord3fv */
         537, /* glTexCoord3i */
         538, /* glTexCoord3iv */
         539, /* glTexCoord3s */
         540, /* glTexCoord3sv */
         541, /* glTexCoord4d */
         542, /* glTexCoord4dv */
         543, /* glTexCoord4f */
         544, /* glTexCoord4fv */
         545, /* glTexCoord4i */
         546, /* glTexCoord4iv */
         547, /* glTexCoord4s */
         548, /* glTexCoord4sv */
         551, /* glTexEnvf */
         552, /* glTexEnvfv */
         553, /* glTexEnvi */
         554, /* glTexEnviv */
         555, /* glTexGend */
         556, /* glTexGendv */
         557, /* glTexGenf */
         558, /* glTexGenfv */
         559, /* glTexGeni */
         560, /* glTexGeniv */
         561, /* glTexImage1D */
         562, /* glTexImage2D */
         565, /* glTexParameterf */
         566, /* glTexParameterfv */
         567, /* glTexParameteri */
         568, /* glTexParameteriv */
         599, /* glTranslated */
         600, /* glTranslatef */
         603, /* glVertex2d */
         604, /* glVertex2dv */
         605, /* glVertex2f */
         606, /* glVertex2fv */
         607, /* glVertex2i */
         608, /* glVertex2iv */
         609, /* glVertex2s */
         610, /* glVertex2sv */
         611, /* glVertex3d */
         612, /* glVertex3dv */
         613, /* glVertex3f */
         614, /* glVertex3fv */
         615, /* glVertex3i */
         616, /* glVertex3iv */
         617, /* glVertex3s */
         618, /* glVertex3sv */
         619, /* glVertex4d */
         620, /* glVertex4dv */
         621, /* glVertex4f */
         622, /* glVertex4fv */
         623, /* glVertex4i */
         624, /* glVertex4iv */
         625, /* glVertex4s */
         626, /* glVertex4sv */
         648  /* glViewport */
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
           2, /* glAreTexturesResident */
           4, /* glArrayElement */
           9, /* glBindTexture */
          63, /* glColorPointer */
          83, /* glCopyTexImage1D */
          85, /* glCopyTexImage2D */
          87, /* glCopyTexSubImage1D */
          89, /* glCopyTexSubImage2D */
         107, /* glDeleteTextures */
         113, /* glDisableClientState */
         119, /* glDrawArrays */
         122, /* glDrawElements */
         127, /* glEdgeFlagPointer */
         131, /* glEnableClientState */
         166, /* glGenTextures */
         228, /* glGetPointerv */
         255, /* glIndexPointer */
         265, /* glIndexub */
         266, /* glIndexubv */
         268, /* glInterleavedArrays */
         273, /* glIsTexture */
         391, /* glNormalPointer */
         407, /* glPolygonOffset */
         410, /* glPopClientAttrib */
         414, /* glPrioritizeTextures */
         467, /* glPushClientAttrib */
         549, /* glTexCoordPointer */
         572, /* glTexSubImage1D */
         574, /* glTexSubImage2D */
         646  /* glVertexPointer */
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
          91, /* glCopyTexSubImage3D */
         124, /* glDrawRangeElements */
         563, /* glTexImage3D */
         576  /* glTexSubImage3D */
    };
    uint32_t i;
    if(!context->VERSION_1_2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ES_VERSION_2_0(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         651, /* glActiveTexture */
         652, /* glAttachShader */
         656, /* glBindAttribLocation */
         657, /* glBindBuffer */
         660, /* glBindFramebuffer */
         664, /* glBindRenderbuffer */
           9, /* glBindTexture */
         673, /* glBlendColor */
         674, /* glBlendEquation */
         675, /* glBlendEquationSeparate */
          12, /* glBlendFunc */
         682, /* glBlendFuncSeparate */
         692, /* glBufferData */
         693, /* glBufferSubData */
         694, /* glCheckFramebufferStatus */
          19, /* glClear */
          21, /* glClearColor */
         699, /* glClearDepthf */
          26, /* glClearStencil */
          61, /* glColorMask */
         705, /* glCompileShader */
         706, /* glCompressedTexImage2D */
         708, /* glCompressedTexSubImage2D */
          85, /* glCopyTexImage2D */
          89, /* glCopyTexSubImage2D */
         715, /* glCreateProgram */
         716, /* glCreateShader */
          98, /* glCullFace */
         722, /* glDeleteBuffers */
         723, /* glDeleteFramebuffers */
         724, /* glDeleteProgram */
         729, /* glDeleteRenderbuffers */
         731, /* glDeleteShader */
         107, /* glDeleteTextures */
         109, /* glDepthFunc */
         110, /* glDepthMask */
         741, /* glDepthRangef */
         742, /* glDetachShader */
         112, /* glDisable */
         743, /* glDisableVertexAttribArray */
         119, /* glDrawArrays */
         122, /* glDrawElements */
         130, /* glEnable */
         771, /* glEnableVertexAttribArray */
         152, /* glFinish */
         153, /* glFlush */
         784, /* glFramebufferRenderbuffer */
         786, /* glFramebufferTexture2D */
         162, /* glFrontFace */
         791, /* glGenBuffers */
         792, /* glGenFramebuffers */
         797, /* glGenRenderbuffers */
         166, /* glGenTextures */
         802, /* glGenerateMipmap */
         803, /* glGetActiveAttrib */
         804, /* glGetActiveUniform */
         808, /* glGetAttachedShaders */
         809, /* glGetAttribLocation */
         171, /* glGetBooleanv */
         812, /* glGetBufferParameteriv */
         183, /* glGetError */
         186, /* glGetFloatv */
         819, /* glGetFramebufferAttachmentParameteriv */
         189, /* glGetIntegerv */
         836, /* glGetProgramInfoLog */
         846, /* glGetProgramiv */
         854, /* glGetRenderbufferParameteriv */
         863, /* glGetShaderInfoLog */
         864, /* glGetShaderPrecisionFormat */
         865, /* glGetShaderSource */
         866, /* glGetShaderiv */
         231, /* glGetString */
         240, /* glGetTexParameterfv */
         241, /* glGetTexParameteriv */
         879, /* glGetUniformLocation */
         880, /* glGetUniformfv */
         881, /* glGetUniformiv */
         885, /* glGetVertexAttribPointerv */
         886, /* glGetVertexAttribfv */
         887, /* glGetVertexAttribiv */
         253, /* glHint */
         898, /* glIsBuffer */
         270, /* glIsEnabled */
         903, /* glIsFramebuffer */
         904, /* glIsProgram */
         909, /* glIsRenderbuffer */
         911, /* glIsShader */
         273, /* glIsTexture */
         284, /* glLineWidth */
         917, /* glLinkProgram */
         401, /* glPixelStorei */
         407, /* glPolygonOffset */
         497, /* glReadPixels */
         978, /* glReleaseShaderCompiler */
         979, /* glRenderbufferStorage */
         984, /* glSampleCoverage */
         511, /* glScissor */
        1002, /* glShaderBinary */
        1003, /* glShaderSource */
         514, /* glStencilFunc */
        1004, /* glStencilFuncSeparate */
         515, /* glStencilMask */
        1005, /* glStencilMaskSeparate */
         516, /* glStencilOp */
        1006, /* glStencilOpSeparate */
         562, /* glTexImage2D */
         565, /* glTexParameterf */
         566, /* glTexParameterfv */
         567, /* glTexParameteri */
         568, /* glTexParameteriv */
         574, /* glTexSubImage2D */
        1025, /* glUniform1f */
        1026, /* glUniform1fv */
        1027, /* glUniform1i */
        1028, /* glUniform1iv */
        1031, /* glUniform2f */
        1032, /* glUniform2fv */
        1033, /* glUniform2i */
        1034, /* glUniform2iv */
        1037, /* glUniform3f */
        1038, /* glUniform3fv */
        1039, /* glUniform3i */
        1040, /* glUniform3iv */
        1043, /* glUniform4f */
        1044, /* glUniform4fv */
        1045, /* glUniform4i */
        1046, /* glUniform4iv */
        1050, /* glUniformMatrix2fv */
        1055, /* glUniformMatrix3fv */
        1060, /* glUniformMatrix4fv */
        1067, /* glUseProgram */
        1070, /* glValidateProgram */
        1073, /* glVertexAttrib1f */
        1074, /* glVertexAttrib1fv */
        1075, /* glVertexAttrib2f */
        1076, /* glVertexAttrib2fv */
        1077, /* glVertexAttrib3f */
        1078, /* glVertexAttrib3fv */
        1079, /* glVertexAttrib4f */
        1080, /* glVertexAttrib4fv */
        1093, /* glVertexAttribPointer */
         648  /* glViewport */
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
         653, /* glBeginQuery */
         655, /* glBeginTransformFeedback */
         658, /* glBindBufferBase */
         659, /* glBindBufferRange */
         665, /* glBindSampler */
         666, /* glBindTransformFeedback */
         667, /* glBindVertexArray */
         690, /* glBlitFramebuffer */
         695, /* glClearBufferfi */
         696, /* glClearBufferfv */
         697, /* glClearBufferiv */
         698, /* glClearBufferuiv */
         700, /* glClientWaitSync */
         707, /* glCompressedTexImage3D */
         709, /* glCompressedTexSubImage3D */
         710, /* glCopyBufferSubData */
          91, /* glCopyTexSubImage3D */
         727, /* glDeleteQueries */
         730, /* glDeleteSamplers */
         732, /* glDeleteSync */
         734, /* glDeleteTransformFeedbacks */
         735, /* glDeleteVertexArrays */
         751, /* glDrawArraysInstanced */
         755, /* glDrawBuffers */
         761, /* glDrawElementsInstanced */
         124, /* glDrawRangeElements */
         776, /* glEndQuery */
         778, /* glEndTransformFeedback */
         779, /* glFenceSync */
         781, /* glFlushMappedBufferRange */
         789, /* glFramebufferTextureLayer */
         795, /* glGenQueries */
         798, /* glGenSamplers */
         799, /* glGenTransformFeedbacks */
         800, /* glGenVertexArrays */
         805, /* glGetActiveUniformBlockName */
         806, /* glGetActiveUniformBlockiv */
         807, /* glGetActiveUniformsiv */
         811, /* glGetBufferParameteri64v */
         813, /* glGetBufferPointerv */
         818, /* glGetFragDataLocation */
         824, /* glGetInteger64i_v */
         825, /* glGetInteger64v */
         828, /* glGetIntegeri_v */
         829, /* glGetInternalformativ */
         834, /* glGetProgramBinary */
         850, /* glGetQueryObjectuiv */
         852, /* glGetQueryiv */
         861, /* glGetSamplerParameterfv */
         862, /* glGetSamplerParameteriv */
         867, /* glGetStringi */
         868, /* glGetSynciv */
         876, /* glGetTransformFeedbackVarying */
         877, /* glGetUniformBlockIndex */
         878, /* glGetUniformIndices */
         882, /* glGetUniformuiv */
         883, /* glGetVertexAttribIiv */
         884, /* glGetVertexAttribIuiv */
         896, /* glInvalidateFramebuffer */
         897, /* glInvalidateSubFramebuffer */
         907, /* glIsQuery */
         910, /* glIsSampler */
         912, /* glIsSync */
         914, /* glIsTransformFeedback */
         915, /* glIsVertexArray */
         919, /* glMapBufferRange */
         931, /* glPauseTransformFeedback */
         936, /* glProgramBinary */
         938, /* glProgramParameteri */
         496, /* glReadBuffer */
         980, /* glRenderbufferStorageMultisample */
         983, /* glResumeTransformFeedback */
         992, /* glSamplerParameterf */
         993, /* glSamplerParameterfv */
         994, /* glSamplerParameteri */
         995, /* glSamplerParameteriv */
         563, /* glTexImage3D */
        1019, /* glTexStorage2D */
        1021, /* glTexStorage3D */
         576, /* glTexSubImage3D */
        1024, /* glTransformFeedbackVaryings */
        1029, /* glUniform1ui */
        1030, /* glUniform1uiv */
        1035, /* glUniform2ui */
        1036, /* glUniform2uiv */
        1041, /* glUniform3ui */
        1042, /* glUniform3uiv */
        1047, /* glUniform4ui */
        1048, /* glUniform4uiv */
        1049, /* glUniformBlockBinding */
        1051, /* glUniformMatrix2x3fv */
        1053, /* glUniformMatrix2x4fv */
        1056, /* glUniformMatrix3x2fv */
        1058, /* glUniformMatrix3x4fv */
        1061, /* glUniformMatrix4x2fv */
        1063, /* glUniformMatrix4x3fv */
        1065, /* glUnmapBuffer */
        1082, /* glVertexAttribDivisor */
        1087, /* glVertexAttribI4i */
        1088, /* glVertexAttribI4iv */
        1089, /* glVertexAttribI4ui */
        1090, /* glVertexAttribI4uiv */
        1092, /* glVertexAttribIPointer */
        1101  /* glWaitSync */
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
         649, /* glActiveShaderProgram */
         661, /* glBindImageTexture */
         662, /* glBindProgramPipeline */
         669, /* glBindVertexBuffer */
         717, /* glCreateShaderProgramv */
         725, /* glDeleteProgramPipelines */
         748, /* glDispatchCompute */
         749, /* glDispatchComputeIndirect */
         750, /* glDrawArraysIndirect */
         760, /* glDrawElementsIndirect */
         783, /* glFramebufferParameteri */
         793, /* glGenProgramPipelines */
         810, /* glGetBooleani_v */
         820, /* glGetFramebufferParameteriv */
         830, /* glGetMultisamplefv */
         837, /* glGetProgramInterfaceiv */
         838, /* glGetProgramPipelineInfoLog */
         840, /* glGetProgramPipelineiv */
         842, /* glGetProgramResourceIndex */
         843, /* glGetProgramResourceLocation */
         844, /* glGetProgramResourceName */
         845, /* glGetProgramResourceiv */
         238, /* glGetTexLevelParameterfv */
         239, /* glGetTexLevelParameteriv */
         905, /* glIsProgramPipeline */
         921, /* glMemoryBarrier */
         922, /* glMemoryBarrierByRegion */
         940, /* glProgramUniform1f */
         941, /* glProgramUniform1fv */
         942, /* glProgramUniform1i */
         943, /* glProgramUniform1iv */
         944, /* glProgramUniform1ui */
         945, /* glProgramUniform1uiv */
         946, /* glProgramUniform2f */
         947, /* glProgramUniform2fv */
         948, /* glProgramUniform2i */
         949, /* glProgramUniform2iv */
         950, /* glProgramUniform2ui */
         951, /* glProgramUniform2uiv */
         952, /* glProgramUniform3f */
         953, /* glProgramUniform3fv */
         954, /* glProgramUniform3i */
         955, /* glProgramUniform3iv */
         956, /* glProgramUniform3ui */
         957, /* glProgramUniform3uiv */
         958, /* glProgramUniform4f */
         959, /* glProgramUniform4fv */
         960, /* glProgramUniform4i */
         961, /* glProgramUniform4iv */
         962, /* glProgramUniform4ui */
         963, /* glProgramUniform4uiv */
         964, /* glProgramUniformMatrix2fv */
         965, /* glProgramUniformMatrix2x3fv */
         966, /* glProgramUniformMatrix2x4fv */
         967, /* glProgramUniformMatrix3fv */
         968, /* glProgramUniformMatrix3x2fv */
         969, /* glProgramUniformMatrix3x4fv */
         970, /* glProgramUniformMatrix4fv */
         971, /* glProgramUniformMatrix4x2fv */
         972, /* glProgramUniformMatrix4x3fv */
         985, /* glSampleMaski */
        1020, /* glTexStorage2DMultisample */
        1068, /* glUseProgramStages */
        1071, /* glValidateProgramPipeline */
        1081, /* glVertexAttribBinding */
        1086, /* glVertexAttribFormat */
        1091, /* glVertexAttribIFormat */
        1094  /* glVertexBindingDivisor */
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
         670, /* glBlendBarrier */
         676, /* glBlendEquationSeparatei */
         679, /* glBlendEquationi */
         683, /* glBlendFuncSeparatei */
         686, /* glBlendFunci */
         702, /* glColorMaski */
         712, /* glCopyImageSubData */
          99, /* glDebugMessageCallback */
         101, /* glDebugMessageControl */
         103, /* glDebugMessageInsert */
         744, /* glDisablei */
         757, /* glDrawElementsBaseVertex */
         763, /* glDrawElementsInstancedBaseVertex */
         768, /* glDrawRangeElementsBaseVertex */
         772, /* glEnablei */
         785, /* glFramebufferTexture */
         178, /* glGetDebugMessageLog */
         821, /* glGetGraphicsResetStatus */
         221, /* glGetObjectLabel */
         222, /* glGetObjectPtrLabel */
         228, /* glGetPointerv */
         855, /* glGetSamplerParameterIiv */
         858, /* glGetSamplerParameterIuiv */
         870, /* glGetTexParameterIiv */
         873, /* glGetTexParameterIuiv */
         888, /* glGetnUniformfv */
         891, /* glGetnUniformiv */
         894, /* glGetnUniformuiv */
         899, /* glIsEnabledi */
         923, /* glMinSampleShading */
         393, /* glObjectLabel */
         394, /* glObjectPtrLabel */
         928, /* glPatchParameteri */
         411, /* glPopDebugGroup */
         933, /* glPrimitiveBoundingBox */
         469, /* glPushDebugGroup */
         975, /* glReadnPixels */
         986, /* glSamplerParameterIiv */
         989, /* glSamplerParameterIuiv */
        1007, /* glTexBuffer */
        1010, /* glTexBufferRange */
        1013, /* glTexParameterIiv */
        1016, /* glTexParameterIuiv */
        1022  /* glTexStorage3DMultisample */
    };
    uint32_t i;
    if(!context->ES_VERSION_3_2) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ANGLE_instanced_arrays(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         752, /* glDrawArraysInstancedANGLE */
         762, /* glDrawElementsInstancedANGLE */
        1083  /* glVertexAttribDivisorANGLE */
    };
    uint32_t i;
    if(!context->ANGLE_instanced_arrays) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_APPLE_sync(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         701, /* glClientWaitSyncAPPLE */
         733, /* glDeleteSyncAPPLE */
         780, /* glFenceSyncAPPLE */
         826, /* glGetInteger64vAPPLE */
         869, /* glGetSyncivAPPLE */
         913, /* glIsSyncAPPLE */
        1102  /* glWaitSyncAPPLE */
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
          14  /* glBufferStorage */
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
         100, /* glDebugMessageCallbackARB */
         102, /* glDebugMessageControlARB */
         104, /* glDebugMessageInsertARB */
         179  /* glGetDebugMessageLogARB */
    };
    uint32_t i;
    if(!context->ARB_debug_output) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_ARB_vertex_buffer_object(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
           7, /* glBindBufferARB */
          13, /* glBufferDataARB */
          15, /* glBufferSubDataARB */
         105, /* glDeleteBuffersARB */
         164, /* glGenBuffersARB */
         172, /* glGetBufferParameterivARB */
         173, /* glGetBufferPointervARB */
         174, /* glGetBufferSubDataARB */
         269, /* glIsBufferARB */
         295, /* glMapBufferARB */
         601  /* glUnmapBufferARB */
    };
    uint32_t i;
    if(!context->ARB_vertex_buffer_object) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_copy_image(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         713  /* glCopyImageSubDataEXT */
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
          84, /* glCopyTexImage1DEXT */
          86, /* glCopyTexImage2DEXT */
          88, /* glCopyTexSubImage1DEXT */
          90, /* glCopyTexSubImage2DEXT */
          92  /* glCopyTexSubImage3DEXT */
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
           8, /* glBindMultiTextureEXT */
          18, /* glCheckNamedFramebufferStatusEXT */
          24, /* glClearNamedBufferDataEXT */
          25, /* glClearNamedBufferSubDataEXT */
          27, /* glClientAttribDefaultEXT */
          65, /* glCompressedMultiTexImage1DEXT */
          66, /* glCompressedMultiTexImage2DEXT */
          67, /* glCompressedMultiTexImage3DEXT */
          68, /* glCompressedMultiTexSubImage1DEXT */
          69, /* glCompressedMultiTexSubImage2DEXT */
          70, /* glCompressedMultiTexSubImage3DEXT */
          71, /* glCompressedTextureImage1DEXT */
          72, /* glCompressedTextureImage2DEXT */
          73, /* glCompressedTextureImage3DEXT */
          74, /* glCompressedTextureSubImage1DEXT */
          75, /* glCompressedTextureSubImage2DEXT */
          76, /* glCompressedTextureSubImage3DEXT */
          77, /* glCopyMultiTexImage1DEXT */
          78, /* glCopyMultiTexImage2DEXT */
          79, /* glCopyMultiTexSubImage1DEXT */
          80, /* glCopyMultiTexSubImage2DEXT */
          81, /* glCopyMultiTexSubImage3DEXT */
          93, /* glCopyTextureImage1DEXT */
          94, /* glCopyTextureImage2DEXT */
          95, /* glCopyTextureSubImage1DEXT */
          96, /* glCopyTextureSubImage2DEXT */
          97, /* glCopyTextureSubImage3DEXT */
         114, /* glDisableClientStateIndexedEXT */
         115, /* glDisableClientStateiEXT */
         116, /* glDisableIndexedEXT */
         117, /* glDisableVertexArrayAttribEXT */
         118, /* glDisableVertexArrayEXT */
         132, /* glEnableClientStateIndexedEXT */
         133, /* glEnableClientStateiEXT */
         134, /* glEnableIndexedEXT */
         135, /* glEnableVertexArrayAttribEXT */
         136, /* glEnableVertexArrayEXT */
         154, /* glFlushMappedNamedBufferRangeEXT */
         159, /* glFramebufferDrawBufferEXT */
         160, /* glFramebufferDrawBuffersEXT */
         161, /* glFramebufferReadBufferEXT */
         168, /* glGenerateMultiTexMipmapEXT */
         169, /* glGenerateTextureMipmapEXT */
         170, /* glGetBooleanIndexedvEXT */
         176, /* glGetCompressedMultiTexImageEXT */
         177, /* glGetCompressedTextureImageEXT */
         180, /* glGetDoubleIndexedvEXT */
         181, /* glGetDoublei_vEXT */
         184, /* glGetFloatIndexedvEXT */
         185, /* glGetFloati_vEXT */
         187, /* glGetFramebufferParameterivEXT */
         188, /* glGetIntegerIndexedvEXT */
         197, /* glGetMultiTexEnvfvEXT */
         198, /* glGetMultiTexEnvivEXT */
         199, /* glGetMultiTexGendvEXT */
         200, /* glGetMultiTexGenfvEXT */
         201, /* glGetMultiTexGenivEXT */
         202, /* glGetMultiTexImageEXT */
         203, /* glGetMultiTexLevelParameterfvEXT */
         204, /* glGetMultiTexLevelParameterivEXT */
         205, /* glGetMultiTexParameterIivEXT */
         206, /* glGetMultiTexParameterIuivEXT */
         207, /* glGetMultiTexParameterfvEXT */
         208, /* glGetMultiTexParameterivEXT */
         209, /* glGetNamedBufferParameterivEXT */
         210, /* glGetNamedBufferPointervEXT */
         211, /* glGetNamedBufferSubDataEXT */
         212, /* glGetNamedFramebufferAttachmentParameterivEXT */
         213, /* glGetNamedFramebufferParameterivEXT */
         214, /* glGetNamedProgramLocalParameterIivEXT */
         215, /* glGetNamedProgramLocalParameterIuivEXT */
         216, /* glGetNamedProgramLocalParameterdvEXT */
         217, /* glGetNamedProgramLocalParameterfvEXT */
         218, /* glGetNamedProgramStringEXT */
         219, /* glGetNamedProgramivEXT */
         220, /* glGetNamedRenderbufferParameterivEXT */
         226, /* glGetPointerIndexedvEXT */
         227, /* glGetPointeri_vEXT */
         242, /* glGetTextureImageEXT */
         243, /* glGetTextureLevelParameterfvEXT */
         244, /* glGetTextureLevelParameterivEXT */
         245, /* glGetTextureParameterIivEXT */
         246, /* glGetTextureParameterIuivEXT */
         247, /* glGetTextureParameterfvEXT */
         248, /* glGetTextureParameterivEXT */
         249, /* glGetVertexArrayIntegeri_vEXT */
         250, /* glGetVertexArrayIntegervEXT */
         251, /* glGetVertexArrayPointeri_vEXT */
         252, /* glGetVertexArrayPointervEXT */
         271, /* glIsEnabledIndexedEXT */
         300, /* glMapNamedBufferEXT */
         301, /* glMapNamedBufferRangeEXT */
         306, /* glMatrixFrustumEXT */
         307, /* glMatrixLoadIdentityEXT */
         308, /* glMatrixLoadTransposedEXT */
         309, /* glMatrixLoadTransposefEXT */
         310, /* glMatrixLoaddEXT */
         311, /* glMatrixLoadfEXT */
         313, /* glMatrixMultTransposedEXT */
         314, /* glMatrixMultTransposefEXT */
         315, /* glMatrixMultdEXT */
         316, /* glMatrixMultfEXT */
         317, /* glMatrixOrthoEXT */
         318, /* glMatrixPopEXT */
         319, /* glMatrixPushEXT */
         320, /* glMatrixRotatedEXT */
         321, /* glMatrixRotatefEXT */
         322, /* glMatrixScaledEXT */
         323, /* glMatrixScalefEXT */
         324, /* glMatrixTranslatedEXT */
         325, /* glMatrixTranslatefEXT */
         328, /* glMultiTexBufferEXT */
         329, /* glMultiTexCoordPointerEXT */
         330, /* glMultiTexEnvfEXT */
         331, /* glMultiTexEnvfvEXT */
         332, /* glMultiTexEnviEXT */
         333, /* glMultiTexEnvivEXT */
         334, /* glMultiTexGendEXT */
         335, /* glMultiTexGendvEXT */
         336, /* glMultiTexGenfEXT */
         337, /* glMultiTexGenfvEXT */
         338, /* glMultiTexGeniEXT */
         339, /* glMultiTexGenivEXT */
         340, /* glMultiTexImage1DEXT */
         341, /* glMultiTexImage2DEXT */
         342, /* glMultiTexImage3DEXT */
         343, /* glMultiTexParameterIivEXT */
         344, /* glMultiTexParameterIuivEXT */
         345, /* glMultiTexParameterfEXT */
         346, /* glMultiTexParameterfvEXT */
         347, /* glMultiTexParameteriEXT */
         348, /* glMultiTexParameterivEXT */
         349, /* glMultiTexRenderbufferEXT */
         350, /* glMultiTexSubImage1DEXT */
         351, /* glMultiTexSubImage2DEXT */
         352, /* glMultiTexSubImage3DEXT */
         353, /* glNamedBufferDataEXT */
         354, /* glNamedBufferStorageEXT */
         355, /* glNamedBufferSubDataEXT */
         356, /* glNamedCopyBufferSubDataEXT */
         357, /* glNamedFramebufferParameteriEXT */
         358, /* glNamedFramebufferRenderbufferEXT */
         359, /* glNamedFramebufferTexture1DEXT */
         360, /* glNamedFramebufferTexture2DEXT */
         361, /* glNamedFramebufferTexture3DEXT */
         362, /* glNamedFramebufferTextureEXT */
         363, /* glNamedFramebufferTextureFaceEXT */
         364, /* glNamedFramebufferTextureLayerEXT */
         365, /* glNamedProgramLocalParameter4dEXT */
         366, /* glNamedProgramLocalParameter4dvEXT */
         367, /* glNamedProgramLocalParameter4fEXT */
         368, /* glNamedProgramLocalParameter4fvEXT */
         369, /* glNamedProgramLocalParameterI4iEXT */
         370, /* glNamedProgramLocalParameterI4ivEXT */
         371, /* glNamedProgramLocalParameterI4uiEXT */
         372, /* glNamedProgramLocalParameterI4uivEXT */
         373, /* glNamedProgramLocalParameters4fvEXT */
         374, /* glNamedProgramLocalParametersI4ivEXT */
         375, /* glNamedProgramLocalParametersI4uivEXT */
         376, /* glNamedProgramStringEXT */
         377, /* glNamedRenderbufferStorageEXT */
         378, /* glNamedRenderbufferStorageMultisampleCoverageEXT */
         379, /* glNamedRenderbufferStorageMultisampleEXT */
         416, /* glProgramUniform1dEXT */
         417, /* glProgramUniform1dvEXT */
         418, /* glProgramUniform1fEXT */
         419, /* glProgramUniform1fvEXT */
         420, /* glProgramUniform1iEXT */
         421, /* glProgramUniform1ivEXT */
         422, /* glProgramUniform1uiEXT */
         423, /* glProgramUniform1uivEXT */
         424, /* glProgramUniform2dEXT */
         425, /* glProgramUniform2dvEXT */
         426, /* glProgramUniform2fEXT */
         427, /* glProgramUniform2fvEXT */
         428, /* glProgramUniform2iEXT */
         429, /* glProgramUniform2ivEXT */
         430, /* glProgramUniform2uiEXT */
         431, /* glProgramUniform2uivEXT */
         432, /* glProgramUniform3dEXT */
         433, /* glProgramUniform3dvEXT */
         434, /* glProgramUniform3fEXT */
         435, /* glProgramUniform3fvEXT */
         436, /* glProgramUniform3iEXT */
         437, /* glProgramUniform3ivEXT */
         438, /* glProgramUniform3uiEXT */
         439, /* glProgramUniform3uivEXT */
         440, /* glProgramUniform4dEXT */
         441, /* glProgramUniform4dvEXT */
         442, /* glProgramUniform4fEXT */
         443, /* glProgramUniform4fvEXT */
         444, /* glProgramUniform4iEXT */
         445, /* glProgramUniform4ivEXT */
         446, /* glProgramUniform4uiEXT */
         447, /* glProgramUniform4uivEXT */
         448, /* glProgramUniformMatrix2dvEXT */
         449, /* glProgramUniformMatrix2fvEXT */
         450, /* glProgramUniformMatrix2x3dvEXT */
         451, /* glProgramUniformMatrix2x3fvEXT */
         452, /* glProgramUniformMatrix2x4dvEXT */
         453, /* glProgramUniformMatrix2x4fvEXT */
         454, /* glProgramUniformMatrix3dvEXT */
         455, /* glProgramUniformMatrix3fvEXT */
         456, /* glProgramUniformMatrix3x2dvEXT */
         457, /* glProgramUniformMatrix3x2fvEXT */
         458, /* glProgramUniformMatrix3x4dvEXT */
         459, /* glProgramUniformMatrix3x4fvEXT */
         460, /* glProgramUniformMatrix4dvEXT */
         461, /* glProgramUniformMatrix4fvEXT */
         462, /* glProgramUniformMatrix4x2dvEXT */
         463, /* glProgramUniformMatrix4x2fvEXT */
         464, /* glProgramUniformMatrix4x3dvEXT */
         465, /* glProgramUniformMatrix4x3fvEXT */
         468, /* glPushClientAttribDefaultEXT */
         578, /* glTextureBufferEXT */
         579, /* glTextureBufferRangeEXT */
         580, /* glTextureImage1DEXT */
         581, /* glTextureImage2DEXT */
         582, /* glTextureImage3DEXT */
         583, /* glTexturePageCommitmentEXT */
         584, /* glTextureParameterIivEXT */
         585, /* glTextureParameterIuivEXT */
         586, /* glTextureParameterfEXT */
         587, /* glTextureParameterfvEXT */
         588, /* glTextureParameteriEXT */
         589, /* glTextureParameterivEXT */
         590, /* glTextureRenderbufferEXT */
         591, /* glTextureStorage1DEXT */
         592, /* glTextureStorage2DEXT */
         593, /* glTextureStorage2DMultisampleEXT */
         594, /* glTextureStorage3DEXT */
         595, /* glTextureStorage3DMultisampleEXT */
         596, /* glTextureSubImage1DEXT */
         597, /* glTextureSubImage2DEXT */
         598, /* glTextureSubImage3DEXT */
         602, /* glUnmapNamedBufferEXT */
         627, /* glVertexArrayBindVertexBufferEXT */
         628, /* glVertexArrayColorOffsetEXT */
         629, /* glVertexArrayEdgeFlagOffsetEXT */
         630, /* glVertexArrayFogCoordOffsetEXT */
         631, /* glVertexArrayIndexOffsetEXT */
         632, /* glVertexArrayMultiTexCoordOffsetEXT */
         633, /* glVertexArrayNormalOffsetEXT */
         634, /* glVertexArraySecondaryColorOffsetEXT */
         635, /* glVertexArrayTexCoordOffsetEXT */
         636, /* glVertexArrayVertexAttribBindingEXT */
         637, /* glVertexArrayVertexAttribDivisorEXT */
         638, /* glVertexArrayVertexAttribFormatEXT */
         639, /* glVertexArrayVertexAttribIFormatEXT */
         640, /* glVertexArrayVertexAttribIOffsetEXT */
         641, /* glVertexArrayVertexAttribLFormatEXT */
         642, /* glVertexArrayVertexAttribLOffsetEXT */
         643, /* glVertexArrayVertexAttribOffsetEXT */
         644, /* glVertexArrayVertexBindingDivisorEXT */
         645  /* glVertexArrayVertexOffsetEXT */
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
         654, /* glBeginQueryEXT */
         728, /* glDeleteQueriesEXT */
         777, /* glEndQueryEXT */
         796, /* glGenQueriesEXT */
         827, /* glGetInteger64vEXT */
         847, /* glGetQueryObjecti64vEXT */
         848, /* glGetQueryObjectivEXT */
         849, /* glGetQueryObjectui64vEXT */
         851, /* glGetQueryObjectuivEXT */
         853, /* glGetQueryivEXT */
         908, /* glIsQueryEXT */
         974  /* glQueryCounterEXT */
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
         756  /* glDrawBuffersEXT */
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
         677, /* glBlendEquationSeparateiEXT */
         680, /* glBlendEquationiEXT */
         684, /* glBlendFuncSeparateiEXT */
         687, /* glBlendFunciEXT */
         703, /* glColorMaskiEXT */
         745, /* glDisableiEXT */
         773, /* glEnableiEXT */
         900  /* glIsEnablediEXT */
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
         758, /* glDrawElementsBaseVertexEXT */
         764, /* glDrawElementsInstancedBaseVertexEXT */
         769, /* glDrawRangeElementsBaseVertexEXT */
         925  /* glMultiDrawElementsBaseVertexEXT */
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
         753, /* glDrawArraysInstancedEXT */
         766  /* glDrawElementsInstancedEXT */
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
         125  /* glDrawRangeElementsEXT */
    };
    uint32_t i;
    if(!context->EXT_draw_range_elements) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_geometry_shader(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         788  /* glFramebufferTextureEXT */
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
         753, /* glDrawArraysInstancedEXT */
         766, /* glDrawElementsInstancedEXT */
        1084  /* glVertexAttribDivisorEXT */
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
         782, /* glFlushMappedBufferRangeEXT */
         920  /* glMapBufferRangeEXT */
    };
    uint32_t i;
    if(!context->EXT_map_buffer_range) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_multisampled_render_to_texture(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         787, /* glFramebufferTexture2DMultisampleEXT */
         981  /* glRenderbufferStorageMultisampleEXT */
    };
    uint32_t i;
    if(!context->EXT_multisampled_render_to_texture) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_primitive_bounding_box(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         934  /* glPrimitiveBoundingBoxEXT */
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
         822, /* glGetGraphicsResetStatusEXT */
         889, /* glGetnUniformfvEXT */
         892, /* glGetnUniformivEXT */
         976  /* glReadnPixelsEXT */
    };
    uint32_t i;
    if(!context->EXT_robustness) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_EXT_separate_shader_objects(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         650, /* glActiveShaderProgramEXT */
         663, /* glBindProgramPipelineEXT */
         718, /* glCreateShaderProgramvEXT */
         726, /* glDeleteProgramPipelinesEXT */
         794, /* glGenProgramPipelinesEXT */
         839, /* glGetProgramPipelineInfoLogEXT */
         841, /* glGetProgramPipelineivEXT */
         906, /* glIsProgramPipelineEXT */
         939, /* glProgramParameteriEXT */
         418, /* glProgramUniform1fEXT */
         419, /* glProgramUniform1fvEXT */
         420, /* glProgramUniform1iEXT */
         421, /* glProgramUniform1ivEXT */
         422, /* glProgramUniform1uiEXT */
         423, /* glProgramUniform1uivEXT */
         426, /* glProgramUniform2fEXT */
         427, /* glProgramUniform2fvEXT */
         428, /* glProgramUniform2iEXT */
         429, /* glProgramUniform2ivEXT */
         430, /* glProgramUniform2uiEXT */
         431, /* glProgramUniform2uivEXT */
         434, /* glProgramUniform3fEXT */
         435, /* glProgramUniform3fvEXT */
         436, /* glProgramUniform3iEXT */
         437, /* glProgramUniform3ivEXT */
         438, /* glProgramUniform3uiEXT */
         439, /* glProgramUniform3uivEXT */
         442, /* glProgramUniform4fEXT */
         443, /* glProgramUniform4fvEXT */
         444, /* glProgramUniform4iEXT */
         445, /* glProgramUniform4ivEXT */
         446, /* glProgramUniform4uiEXT */
         447, /* glProgramUniform4uivEXT */
         449, /* glProgramUniformMatrix2fvEXT */
         451, /* glProgramUniformMatrix2x3fvEXT */
         453, /* glProgramUniformMatrix2x4fvEXT */
         455, /* glProgramUniformMatrix3fvEXT */
         457, /* glProgramUniformMatrix3x2fvEXT */
         459, /* glProgramUniformMatrix3x4fvEXT */
         461, /* glProgramUniformMatrix4fvEXT */
         463, /* glProgramUniformMatrix4x2fvEXT */
         465, /* glProgramUniformMatrix4x3fvEXT */
        1069, /* glUseProgramStagesEXT */
        1072  /* glValidateProgramPipelineEXT */
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
         573, /* glTexSubImage1DEXT */
         575  /* glTexSubImage2DEXT */
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
         929  /* glPatchParameteriEXT */
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
         564, /* glTexImage3DEXT */
         577  /* glTexSubImage3DEXT */
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
         856, /* glGetSamplerParameterIivEXT */
         859, /* glGetSamplerParameterIuivEXT */
         871, /* glGetTexParameterIivEXT */
         874, /* glGetTexParameterIuivEXT */
         987, /* glSamplerParameterIivEXT */
         990, /* glSamplerParameterIuivEXT */
        1014, /* glTexParameterIivEXT */
        1017  /* glTexParameterIuivEXT */
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
        1008, /* glTexBufferEXT */
        1011  /* glTexBufferRangeEXT */
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
           3, /* glAreTexturesResidentEXT */
          10, /* glBindTextureEXT */
         108, /* glDeleteTexturesEXT */
         167, /* glGenTexturesEXT */
         274, /* glIsTextureEXT */
         415  /* glPrioritizeTexturesEXT */
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
         569, /* glTexStorage1DEXT */
         570, /* glTexStorage2DEXT */
         571, /* glTexStorage3DEXT */
         591, /* glTextureStorage1DEXT */
         592, /* glTextureStorage2DEXT */
         594  /* glTextureStorage3DEXT */
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
           5, /* glArrayElementEXT */
          64, /* glColorPointerEXT */
         120, /* glDrawArraysEXT */
         128, /* glEdgeFlagPointerEXT */
         229, /* glGetPointervEXT */
         256, /* glIndexPointerEXT */
         392, /* glNormalPointerEXT */
         550, /* glTexCoordPointerEXT */
         647  /* glVertexPointerEXT */
    };
    uint32_t i;
    if(!context->EXT_vertex_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_KHR_blend_equation_advanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         671  /* glBlendBarrierKHR */
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
          99, /* glDebugMessageCallback */
         719, /* glDebugMessageCallbackKHR */
         101, /* glDebugMessageControl */
         720, /* glDebugMessageControlKHR */
         103, /* glDebugMessageInsert */
         721, /* glDebugMessageInsertKHR */
         178, /* glGetDebugMessageLog */
         815, /* glGetDebugMessageLogKHR */
         221, /* glGetObjectLabel */
         831, /* glGetObjectLabelKHR */
         222, /* glGetObjectPtrLabel */
         832, /* glGetObjectPtrLabelKHR */
         228, /* glGetPointerv */
         833, /* glGetPointervKHR */
         393, /* glObjectLabel */
         926, /* glObjectLabelKHR */
         394, /* glObjectPtrLabel */
         927, /* glObjectPtrLabelKHR */
         411, /* glPopDebugGroup */
         932, /* glPopDebugGroupKHR */
         469, /* glPushDebugGroup */
         973  /* glPushDebugGroupKHR */
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
         821, /* glGetGraphicsResetStatus */
         823, /* glGetGraphicsResetStatusKHR */
         888, /* glGetnUniformfv */
         890, /* glGetnUniformfvKHR */
         891, /* glGetnUniformiv */
         893, /* glGetnUniformivKHR */
         894, /* glGetnUniformuiv */
         895, /* glGetnUniformuivKHR */
         975, /* glReadnPixels */
         977  /* glReadnPixelsKHR */
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
         665, /* glBindSampler */
         730, /* glDeleteSamplers */
         798, /* glGenSamplers */
         861, /* glGetSamplerParameterfv */
         862, /* glGetSamplerParameteriv */
         910, /* glIsSampler */
         992, /* glSamplerParameterf */
         993, /* glSamplerParameterfv */
         994, /* glSamplerParameteri */
         995  /* glSamplerParameteriv */
    };
    uint32_t i;
    if(!context->MESA_sampler_objects) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_blend_equation_advanced(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         672, /* glBlendBarrierNV */
         689  /* glBlendParameteriNV */
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
         711  /* glCopyBufferSubDataNV */
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
         754, /* glDrawArraysInstancedNV */
         767  /* glDrawElementsInstancedNV */
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
         691  /* glBlitFramebufferNV */
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
         982  /* glRenderbufferStorageMultisampleNV */
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
        1085  /* glVertexAttribDivisorNV */
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
        1052, /* glUniformMatrix2x3fvNV */
        1054, /* glUniformMatrix2x4fvNV */
        1057, /* glUniformMatrix3x2fvNV */
        1059, /* glUniformMatrix3x4fvNV */
        1062, /* glUniformMatrix4x2fvNV */
        1064  /* glUniformMatrix4x3fvNV */
    };
    uint32_t i;
    if(!context->NV_non_square_matrices) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_load_GL_NV_viewport_array(GladGLContext *context, GLADuserptrloadfunc load, void* userptr) {
    static const uint16_t s_pfnIdx[] = {
         737, /* glDepthRangeArrayfvNV */
         739, /* glDepthRangeIndexedfNV */
         746, /* glDisableiNV */
         774, /* glEnableiNV */
         816, /* glGetFloati_vNV */
         901, /* glIsEnablediNV */
         996, /* glScissorArrayvNV */
         998, /* glScissorIndexedNV */
        1000, /* glScissorIndexedvNV */
        1095, /* glViewportArrayvNV */
        1097, /* glViewportIndexedfNV */
        1099  /* glViewportIndexedfvNV */
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
         714  /* glCopyImageSubDataOES */
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
         678, /* glBlendEquationSeparateiOES */
         681, /* glBlendEquationiOES */
         685, /* glBlendFuncSeparateiOES */
         688, /* glBlendFunciOES */
         704, /* glColorMaskiOES */
         747, /* glDisableiOES */
         775, /* glEnableiOES */
         902  /* glIsEnablediOES */
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
         759, /* glDrawElementsBaseVertexOES */
         765, /* glDrawElementsInstancedBaseVertexOES */
         770, /* glDrawRangeElementsBaseVertexOES */
         925  /* glMultiDrawElementsBaseVertexEXT */
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
         790  /* glFramebufferTextureOES */
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
         835, /* glGetProgramBinaryOES */
         937  /* glProgramBinaryOES */
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
         814, /* glGetBufferPointervOES */
         918, /* glMapBufferOES */
        1066  /* glUnmapBufferOES */
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
         935  /* glPrimitiveBoundingBoxOES */
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
         924  /* glMinSampleShadingOES */
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
         930  /* glPatchParameteriOES */
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
         857, /* glGetSamplerParameterIivOES */
         860, /* glGetSamplerParameterIuivOES */
         872, /* glGetTexParameterIivOES */
         875, /* glGetTexParameterIuivOES */
         988, /* glSamplerParameterIivOES */
         991, /* glSamplerParameterIuivOES */
        1015, /* glTexParameterIivOES */
        1018  /* glTexParameterIuivOES */
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
        1009, /* glTexBufferOES */
        1012  /* glTexBufferRangeOES */
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
        1023  /* glTexStorage3DMultisampleOES */
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
         668, /* glBindVertexArrayOES */
         736, /* glDeleteVertexArraysOES */
         801, /* glGenVertexArraysOES */
         916  /* glIsVertexArrayOES */
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
         738, /* glDepthRangeArrayfvOES */
         740, /* glDepthRangeIndexedfOES */
         747, /* glDisableiOES */
         775, /* glEnableiOES */
         817, /* glGetFloati_vOES */
         902, /* glIsEnablediOES */
         997, /* glScissorArrayvOES */
         999, /* glScissorIndexedOES */
        1001, /* glScissorIndexedvOES */
        1096, /* glViewportArrayvOES */
        1098, /* glViewportIndexedfOES */
        1100  /* glViewportIndexedfvOES */
    };
    uint32_t i;
    if(!context->OES_viewport_array) return;
    #pragma nounroll
    for (i = 0; i < GLAD_ARRAYSIZE(s_pfnIdx); ++i) {
        const uint16_t pfnIdx = s_pfnIdx[i];
        context->pfnArray[pfnIdx] = load(userptr, GLAD_GL_fn_names[pfnIdx]);
    }
}

static void glad_gl_resolve_aliases(GladGLContext *context) {
    static const GladAliasPair_t s_aliases[] = {
        {    4,    5 }, /* glArrayElement and glArrayElementEXT */
        {    5,    4 }, /* glArrayElementEXT and glArrayElement */
        {  657,    7 }, /* glBindBuffer and glBindBufferARB */
        {    7,  657 }, /* glBindBufferARB and glBindBuffer */
        {    9,   10 }, /* glBindTexture and glBindTextureEXT */
        {   10,    9 }, /* glBindTextureEXT and glBindTexture */
        {  667,  668 }, /* glBindVertexArray and glBindVertexArrayOES */
        {  668,  667 }, /* glBindVertexArrayOES and glBindVertexArray */
        {  670,  671 }, /* glBlendBarrier and glBlendBarrierKHR */
        {  670,  672 }, /* glBlendBarrier and glBlendBarrierNV */
        {  671,  670 }, /* glBlendBarrierKHR and glBlendBarrier */
        {  671,  672 }, /* glBlendBarrierKHR and glBlendBarrierNV */
        {  672,  670 }, /* glBlendBarrierNV and glBlendBarrier */
        {  672,  671 }, /* glBlendBarrierNV and glBlendBarrierKHR */
        {  679,  680 }, /* glBlendEquationi and glBlendEquationiEXT */
        {  679,  681 }, /* glBlendEquationi and glBlendEquationiOES */
        {  680,  679 }, /* glBlendEquationiEXT and glBlendEquationi */
        {  680,  681 }, /* glBlendEquationiEXT and glBlendEquationiOES */
        {  681,  679 }, /* glBlendEquationiOES and glBlendEquationi */
        {  681,  680 }, /* glBlendEquationiOES and glBlendEquationiEXT */
        {  676,  677 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiEXT */
        {  676,  678 }, /* glBlendEquationSeparatei and glBlendEquationSeparateiOES */
        {  677,  676 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparatei */
        {  677,  678 }, /* glBlendEquationSeparateiEXT and glBlendEquationSeparateiOES */
        {  678,  676 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparatei */
        {  678,  677 }, /* glBlendEquationSeparateiOES and glBlendEquationSeparateiEXT */
        {  686,  687 }, /* glBlendFunci and glBlendFunciEXT */
        {  686,  688 }, /* glBlendFunci and glBlendFunciOES */
        {  687,  686 }, /* glBlendFunciEXT and glBlendFunci */
        {  687,  688 }, /* glBlendFunciEXT and glBlendFunciOES */
        {  688,  686 }, /* glBlendFunciOES and glBlendFunci */
        {  688,  687 }, /* glBlendFunciOES and glBlendFunciEXT */
        {  683,  684 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiEXT */
        {  683,  685 }, /* glBlendFuncSeparatei and glBlendFuncSeparateiOES */
        {  684,  683 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparatei */
        {  684,  685 }, /* glBlendFuncSeparateiEXT and glBlendFuncSeparateiOES */
        {  685,  683 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparatei */
        {  685,  684 }, /* glBlendFuncSeparateiOES and glBlendFuncSeparateiEXT */
        {  690,  691 }, /* glBlitFramebuffer and glBlitFramebufferNV */
        {  691,  690 }, /* glBlitFramebufferNV and glBlitFramebuffer */
        {  692,   13 }, /* glBufferData and glBufferDataARB */
        {   13,  692 }, /* glBufferDataARB and glBufferData */
        {  693,   15 }, /* glBufferSubData and glBufferSubDataARB */
        {   15,  693 }, /* glBufferSubDataARB and glBufferSubData */
        {  700,  701 }, /* glClientWaitSync and glClientWaitSyncAPPLE */
        {  701,  700 }, /* glClientWaitSyncAPPLE and glClientWaitSync */
        {  702,  703 }, /* glColorMaski and glColorMaskiEXT */
        {  702,  704 }, /* glColorMaski and glColorMaskiOES */
        {  703,  702 }, /* glColorMaskiEXT and glColorMaski */
        {  703,  704 }, /* glColorMaskiEXT and glColorMaskiOES */
        {  704,  702 }, /* glColorMaskiOES and glColorMaski */
        {  704,  703 }, /* glColorMaskiOES and glColorMaskiEXT */
        {  710,  711 }, /* glCopyBufferSubData and glCopyBufferSubDataNV */
        {  711,  710 }, /* glCopyBufferSubDataNV and glCopyBufferSubData */
        {  712,  713 }, /* glCopyImageSubData and glCopyImageSubDataEXT */
        {  712,  714 }, /* glCopyImageSubData and glCopyImageSubDataOES */
        {  713,  712 }, /* glCopyImageSubDataEXT and glCopyImageSubData */
        {  713,  714 }, /* glCopyImageSubDataEXT and glCopyImageSubDataOES */
        {  714,  712 }, /* glCopyImageSubDataOES and glCopyImageSubData */
        {  714,  713 }, /* glCopyImageSubDataOES and glCopyImageSubDataEXT */
        {   83,   84 }, /* glCopyTexImage1D and glCopyTexImage1DEXT */
        {   84,   83 }, /* glCopyTexImage1DEXT and glCopyTexImage1D */
        {   85,   86 }, /* glCopyTexImage2D and glCopyTexImage2DEXT */
        {   86,   85 }, /* glCopyTexImage2DEXT and glCopyTexImage2D */
        {   87,   88 }, /* glCopyTexSubImage1D and glCopyTexSubImage1DEXT */
        {   88,   87 }, /* glCopyTexSubImage1DEXT and glCopyTexSubImage1D */
        {   89,   90 }, /* glCopyTexSubImage2D and glCopyTexSubImage2DEXT */
        {   90,   89 }, /* glCopyTexSubImage2DEXT and glCopyTexSubImage2D */
        {   91,   92 }, /* glCopyTexSubImage3D and glCopyTexSubImage3DEXT */
        {   92,   91 }, /* glCopyTexSubImage3DEXT and glCopyTexSubImage3D */
        {   99,  100 }, /* glDebugMessageCallback and glDebugMessageCallbackARB */
        {   99,  719 }, /* glDebugMessageCallback and glDebugMessageCallbackKHR */
        {  100,   99 }, /* glDebugMessageCallbackARB and glDebugMessageCallback */
        {  100,  719 }, /* glDebugMessageCallbackARB and glDebugMessageCallbackKHR */
        {  719,   99 }, /* glDebugMessageCallbackKHR and glDebugMessageCallback */
        {  719,  100 }, /* glDebugMessageCallbackKHR and glDebugMessageCallbackARB */
        {  101,  102 }, /* glDebugMessageControl and glDebugMessageControlARB */
        {  101,  720 }, /* glDebugMessageControl and glDebugMessageControlKHR */
        {  102,  101 }, /* glDebugMessageControlARB and glDebugMessageControl */
        {  102,  720 }, /* glDebugMessageControlARB and glDebugMessageControlKHR */
        {  720,  101 }, /* glDebugMessageControlKHR and glDebugMessageControl */
        {  720,  102 }, /* glDebugMessageControlKHR and glDebugMessageControlARB */
        {  103,  104 }, /* glDebugMessageInsert and glDebugMessageInsertARB */
        {  103,  721 }, /* glDebugMessageInsert and glDebugMessageInsertKHR */
        {  104,  103 }, /* glDebugMessageInsertARB and glDebugMessageInsert */
        {  104,  721 }, /* glDebugMessageInsertARB and glDebugMessageInsertKHR */
        {  721,  103 }, /* glDebugMessageInsertKHR and glDebugMessageInsert */
        {  721,  104 }, /* glDebugMessageInsertKHR and glDebugMessageInsertARB */
        {  722,  105 }, /* glDeleteBuffers and glDeleteBuffersARB */
        {  105,  722 }, /* glDeleteBuffersARB and glDeleteBuffers */
        {  732,  733 }, /* glDeleteSync and glDeleteSyncAPPLE */
        {  733,  732 }, /* glDeleteSyncAPPLE and glDeleteSync */
        {  735,  736 }, /* glDeleteVertexArrays and glDeleteVertexArraysOES */
        {  736,  735 }, /* glDeleteVertexArraysOES and glDeleteVertexArrays */
        {  744,  116 }, /* glDisablei and glDisableIndexedEXT */
        {  744,  745 }, /* glDisablei and glDisableiEXT */
        {  744,  746 }, /* glDisablei and glDisableiNV */
        {  744,  747 }, /* glDisablei and glDisableiOES */
        {  745,  116 }, /* glDisableiEXT and glDisableIndexedEXT */
        {  745,  744 }, /* glDisableiEXT and glDisablei */
        {  745,  746 }, /* glDisableiEXT and glDisableiNV */
        {  745,  747 }, /* glDisableiEXT and glDisableiOES */
        {  116,  744 }, /* glDisableIndexedEXT and glDisablei */
        {  116,  745 }, /* glDisableIndexedEXT and glDisableiEXT */
        {  116,  746 }, /* glDisableIndexedEXT and glDisableiNV */
        {  116,  747 }, /* glDisableIndexedEXT and glDisableiOES */
        {  746,  116 }, /* glDisableiNV and glDisableIndexedEXT */
        {  746,  744 }, /* glDisableiNV and glDisablei */
        {  746,  745 }, /* glDisableiNV and glDisableiEXT */
        {  746,  747 }, /* glDisableiNV and glDisableiOES */
        {  747,  116 }, /* glDisableiOES and glDisableIndexedEXT */
        {  747,  744 }, /* glDisableiOES and glDisablei */
        {  747,  745 }, /* glDisableiOES and glDisableiEXT */
        {  747,  746 }, /* glDisableiOES and glDisableiNV */
        {  119,  120 }, /* glDrawArrays and glDrawArraysEXT */
        {  120,  119 }, /* glDrawArraysEXT and glDrawArrays */
        {  751,  752 }, /* glDrawArraysInstanced and glDrawArraysInstancedANGLE */
        {  751,  753 }, /* glDrawArraysInstanced and glDrawArraysInstancedEXT */
        {  751,  754 }, /* glDrawArraysInstanced and glDrawArraysInstancedNV */
        {  752,  751 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstanced */
        {  752,  753 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstancedEXT */
        {  752,  754 }, /* glDrawArraysInstancedANGLE and glDrawArraysInstancedNV */
        {  753,  751 }, /* glDrawArraysInstancedEXT and glDrawArraysInstanced */
        {  753,  752 }, /* glDrawArraysInstancedEXT and glDrawArraysInstancedANGLE */
        {  753,  754 }, /* glDrawArraysInstancedEXT and glDrawArraysInstancedNV */
        {  754,  751 }, /* glDrawArraysInstancedNV and glDrawArraysInstanced */
        {  754,  752 }, /* glDrawArraysInstancedNV and glDrawArraysInstancedANGLE */
        {  754,  753 }, /* glDrawArraysInstancedNV and glDrawArraysInstancedEXT */
        {  755,  756 }, /* glDrawBuffers and glDrawBuffersEXT */
        {  756,  755 }, /* glDrawBuffersEXT and glDrawBuffers */
        {  757,  758 }, /* glDrawElementsBaseVertex and glDrawElementsBaseVertexEXT */
        {  757,  759 }, /* glDrawElementsBaseVertex and glDrawElementsBaseVertexOES */
        {  758,  757 }, /* glDrawElementsBaseVertexEXT and glDrawElementsBaseVertex */
        {  758,  759 }, /* glDrawElementsBaseVertexEXT and glDrawElementsBaseVertexOES */
        {  759,  757 }, /* glDrawElementsBaseVertexOES and glDrawElementsBaseVertex */
        {  759,  758 }, /* glDrawElementsBaseVertexOES and glDrawElementsBaseVertexEXT */
        {  761,  762 }, /* glDrawElementsInstanced and glDrawElementsInstancedANGLE */
        {  761,  766 }, /* glDrawElementsInstanced and glDrawElementsInstancedEXT */
        {  761,  767 }, /* glDrawElementsInstanced and glDrawElementsInstancedNV */
        {  762,  761 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstanced */
        {  762,  766 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstancedEXT */
        {  762,  767 }, /* glDrawElementsInstancedANGLE and glDrawElementsInstancedNV */
        {  763,  764 }, /* glDrawElementsInstancedBaseVertex and glDrawElementsInstancedBaseVertexEXT */
        {  763,  765 }, /* glDrawElementsInstancedBaseVertex and glDrawElementsInstancedBaseVertexOES */
        {  764,  763 }, /* glDrawElementsInstancedBaseVertexEXT and glDrawElementsInstancedBaseVertex */
        {  764,  765 }, /* glDrawElementsInstancedBaseVertexEXT and glDrawElementsInstancedBaseVertexOES */
        {  765,  763 }, /* glDrawElementsInstancedBaseVertexOES and glDrawElementsInstancedBaseVertex */
        {  765,  764 }, /* glDrawElementsInstancedBaseVertexOES and glDrawElementsInstancedBaseVertexEXT */
        {  766,  761 }, /* glDrawElementsInstancedEXT and glDrawElementsInstanced */
        {  766,  762 }, /* glDrawElementsInstancedEXT and glDrawElementsInstancedANGLE */
        {  766,  767 }, /* glDrawElementsInstancedEXT and glDrawElementsInstancedNV */
        {  767,  761 }, /* glDrawElementsInstancedNV and glDrawElementsInstanced */
        {  767,  762 }, /* glDrawElementsInstancedNV and glDrawElementsInstancedANGLE */
        {  767,  766 }, /* glDrawElementsInstancedNV and glDrawElementsInstancedEXT */
        {  124,  125 }, /* glDrawRangeElements and glDrawRangeElementsEXT */
        {  768,  769 }, /* glDrawRangeElementsBaseVertex and glDrawRangeElementsBaseVertexEXT */
        {  768,  770 }, /* glDrawRangeElementsBaseVertex and glDrawRangeElementsBaseVertexOES */
        {  769,  768 }, /* glDrawRangeElementsBaseVertexEXT and glDrawRangeElementsBaseVertex */
        {  769,  770 }, /* glDrawRangeElementsBaseVertexEXT and glDrawRangeElementsBaseVertexOES */
        {  770,  768 }, /* glDrawRangeElementsBaseVertexOES and glDrawRangeElementsBaseVertex */
        {  770,  769 }, /* glDrawRangeElementsBaseVertexOES and glDrawRangeElementsBaseVertexEXT */
        {  125,  124 }, /* glDrawRangeElementsEXT and glDrawRangeElements */
        {  772,  134 }, /* glEnablei and glEnableIndexedEXT */
        {  772,  773 }, /* glEnablei and glEnableiEXT */
        {  772,  774 }, /* glEnablei and glEnableiNV */
        {  772,  775 }, /* glEnablei and glEnableiOES */
        {  773,  134 }, /* glEnableiEXT and glEnableIndexedEXT */
        {  773,  772 }, /* glEnableiEXT and glEnablei */
        {  773,  774 }, /* glEnableiEXT and glEnableiNV */
        {  773,  775 }, /* glEnableiEXT and glEnableiOES */
        {  134,  772 }, /* glEnableIndexedEXT and glEnablei */
        {  134,  773 }, /* glEnableIndexedEXT and glEnableiEXT */
        {  134,  774 }, /* glEnableIndexedEXT and glEnableiNV */
        {  134,  775 }, /* glEnableIndexedEXT and glEnableiOES */
        {  774,  134 }, /* glEnableiNV and glEnableIndexedEXT */
        {  774,  772 }, /* glEnableiNV and glEnablei */
        {  774,  773 }, /* glEnableiNV and glEnableiEXT */
        {  774,  775 }, /* glEnableiNV and glEnableiOES */
        {  775,  134 }, /* glEnableiOES and glEnableIndexedEXT */
        {  775,  772 }, /* glEnableiOES and glEnablei */
        {  775,  773 }, /* glEnableiOES and glEnableiEXT */
        {  775,  774 }, /* glEnableiOES and glEnableiNV */
        {  779,  780 }, /* glFenceSync and glFenceSyncAPPLE */
        {  780,  779 }, /* glFenceSyncAPPLE and glFenceSync */
        {  781,  782 }, /* glFlushMappedBufferRange and glFlushMappedBufferRangeEXT */
        {  782,  781 }, /* glFlushMappedBufferRangeEXT and glFlushMappedBufferRange */
        {  785,  788 }, /* glFramebufferTexture and glFramebufferTextureEXT */
        {  785,  790 }, /* glFramebufferTexture and glFramebufferTextureOES */
        {  788,  785 }, /* glFramebufferTextureEXT and glFramebufferTexture */
        {  788,  790 }, /* glFramebufferTextureEXT and glFramebufferTextureOES */
        {  790,  785 }, /* glFramebufferTextureOES and glFramebufferTexture */
        {  790,  788 }, /* glFramebufferTextureOES and glFramebufferTextureEXT */
        {  791,  164 }, /* glGenBuffers and glGenBuffersARB */
        {  164,  791 }, /* glGenBuffersARB and glGenBuffers */
        {  800,  801 }, /* glGenVertexArrays and glGenVertexArraysOES */
        {  801,  800 }, /* glGenVertexArraysOES and glGenVertexArrays */
        {  810,  170 }, /* glGetBooleani_v and glGetBooleanIndexedvEXT */
        {  170,  810 }, /* glGetBooleanIndexedvEXT and glGetBooleani_v */
        {  812,  172 }, /* glGetBufferParameteriv and glGetBufferParameterivARB */
        {  172,  812 }, /* glGetBufferParameterivARB and glGetBufferParameteriv */
        {  813,  173 }, /* glGetBufferPointerv and glGetBufferPointervARB */
        {  813,  814 }, /* glGetBufferPointerv and glGetBufferPointervOES */
        {  173,  813 }, /* glGetBufferPointervARB and glGetBufferPointerv */
        {  173,  814 }, /* glGetBufferPointervARB and glGetBufferPointervOES */
        {  814,  813 }, /* glGetBufferPointervOES and glGetBufferPointerv */
        {  814,  173 }, /* glGetBufferPointervOES and glGetBufferPointervARB */
        {  178,  179 }, /* glGetDebugMessageLog and glGetDebugMessageLogARB */
        {  178,  815 }, /* glGetDebugMessageLog and glGetDebugMessageLogKHR */
        {  179,  178 }, /* glGetDebugMessageLogARB and glGetDebugMessageLog */
        {  179,  815 }, /* glGetDebugMessageLogARB and glGetDebugMessageLogKHR */
        {  815,  178 }, /* glGetDebugMessageLogKHR and glGetDebugMessageLog */
        {  815,  179 }, /* glGetDebugMessageLogKHR and glGetDebugMessageLogARB */
        {  821,  822 }, /* glGetGraphicsResetStatus and glGetGraphicsResetStatusEXT */
        {  821,  823 }, /* glGetGraphicsResetStatus and glGetGraphicsResetStatusKHR */
        {  822,  821 }, /* glGetGraphicsResetStatusEXT and glGetGraphicsResetStatus */
        {  822,  823 }, /* glGetGraphicsResetStatusEXT and glGetGraphicsResetStatusKHR */
        {  823,  821 }, /* glGetGraphicsResetStatusKHR and glGetGraphicsResetStatus */
        {  823,  822 }, /* glGetGraphicsResetStatusKHR and glGetGraphicsResetStatusEXT */
        {  825,  826 }, /* glGetInteger64v and glGetInteger64vAPPLE */
        {  825,  827 }, /* glGetInteger64v and glGetInteger64vEXT */
        {  826,  825 }, /* glGetInteger64vAPPLE and glGetInteger64v */
        {  826,  827 }, /* glGetInteger64vAPPLE and glGetInteger64vEXT */
        {  827,  825 }, /* glGetInteger64vEXT and glGetInteger64v */
        {  827,  826 }, /* glGetInteger64vEXT and glGetInteger64vAPPLE */
        {  828,  188 }, /* glGetIntegeri_v and glGetIntegerIndexedvEXT */
        {  188,  828 }, /* glGetIntegerIndexedvEXT and glGetIntegeri_v */
        {  888,  889 }, /* glGetnUniformfv and glGetnUniformfvEXT */
        {  888,  890 }, /* glGetnUniformfv and glGetnUniformfvKHR */
        {  889,  888 }, /* glGetnUniformfvEXT and glGetnUniformfv */
        {  889,  890 }, /* glGetnUniformfvEXT and glGetnUniformfvKHR */
        {  890,  888 }, /* glGetnUniformfvKHR and glGetnUniformfv */
        {  890,  889 }, /* glGetnUniformfvKHR and glGetnUniformfvEXT */
        {  891,  892 }, /* glGetnUniformiv and glGetnUniformivEXT */
        {  891,  893 }, /* glGetnUniformiv and glGetnUniformivKHR */
        {  892,  891 }, /* glGetnUniformivEXT and glGetnUniformiv */
        {  892,  893 }, /* glGetnUniformivEXT and glGetnUniformivKHR */
        {  893,  891 }, /* glGetnUniformivKHR and glGetnUniformiv */
        {  893,  892 }, /* glGetnUniformivKHR and glGetnUniformivEXT */
        {  894,  895 }, /* glGetnUniformuiv and glGetnUniformuivKHR */
        {  895,  894 }, /* glGetnUniformuivKHR and glGetnUniformuiv */
        {  221,  831 }, /* glGetObjectLabel and glGetObjectLabelKHR */
        {  831,  221 }, /* glGetObjectLabelKHR and glGetObjectLabel */
        {  222,  832 }, /* glGetObjectPtrLabel and glGetObjectPtrLabelKHR */
        {  832,  222 }, /* glGetObjectPtrLabelKHR and glGetObjectPtrLabel */
        {  228,  229 }, /* glGetPointerv and glGetPointervEXT */
        {  228,  833 }, /* glGetPointerv and glGetPointervKHR */
        {  229,  228 }, /* glGetPointervEXT and glGetPointerv */
        {  229,  833 }, /* glGetPointervEXT and glGetPointervKHR */
        {  833,  228 }, /* glGetPointervKHR and glGetPointerv */
        {  833,  229 }, /* glGetPointervKHR and glGetPointervEXT */
        {  834,  835 }, /* glGetProgramBinary and glGetProgramBinaryOES */
        {  835,  834 }, /* glGetProgramBinaryOES and glGetProgramBinary */
        {  855,  856 }, /* glGetSamplerParameterIiv and glGetSamplerParameterIivEXT */
        {  855,  857 }, /* glGetSamplerParameterIiv and glGetSamplerParameterIivOES */
        {  856,  855 }, /* glGetSamplerParameterIivEXT and glGetSamplerParameterIiv */
        {  856,  857 }, /* glGetSamplerParameterIivEXT and glGetSamplerParameterIivOES */
        {  857,  855 }, /* glGetSamplerParameterIivOES and glGetSamplerParameterIiv */
        {  857,  856 }, /* glGetSamplerParameterIivOES and glGetSamplerParameterIivEXT */
        {  858,  859 }, /* glGetSamplerParameterIuiv and glGetSamplerParameterIuivEXT */
        {  858,  860 }, /* glGetSamplerParameterIuiv and glGetSamplerParameterIuivOES */
        {  859,  858 }, /* glGetSamplerParameterIuivEXT and glGetSamplerParameterIuiv */
        {  859,  860 }, /* glGetSamplerParameterIuivEXT and glGetSamplerParameterIuivOES */
        {  860,  858 }, /* glGetSamplerParameterIuivOES and glGetSamplerParameterIuiv */
        {  860,  859 }, /* glGetSamplerParameterIuivOES and glGetSamplerParameterIuivEXT */
        {  868,  869 }, /* glGetSynciv and glGetSyncivAPPLE */
        {  869,  868 }, /* glGetSyncivAPPLE and glGetSynciv */
        {  870,  871 }, /* glGetTexParameterIiv and glGetTexParameterIivEXT */
        {  870,  872 }, /* glGetTexParameterIiv and glGetTexParameterIivOES */
        {  871,  870 }, /* glGetTexParameterIivEXT and glGetTexParameterIiv */
        {  871,  872 }, /* glGetTexParameterIivEXT and glGetTexParameterIivOES */
        {  872,  870 }, /* glGetTexParameterIivOES and glGetTexParameterIiv */
        {  872,  871 }, /* glGetTexParameterIivOES and glGetTexParameterIivEXT */
        {  873,  874 }, /* glGetTexParameterIuiv and glGetTexParameterIuivEXT */
        {  873,  875 }, /* glGetTexParameterIuiv and glGetTexParameterIuivOES */
        {  874,  873 }, /* glGetTexParameterIuivEXT and glGetTexParameterIuiv */
        {  874,  875 }, /* glGetTexParameterIuivEXT and glGetTexParameterIuivOES */
        {  875,  873 }, /* glGetTexParameterIuivOES and glGetTexParameterIuiv */
        {  875,  874 }, /* glGetTexParameterIuivOES and glGetTexParameterIuivEXT */
        {  898,  269 }, /* glIsBuffer and glIsBufferARB */
        {  269,  898 }, /* glIsBufferARB and glIsBuffer */
        {  899,  271 }, /* glIsEnabledi and glIsEnabledIndexedEXT */
        {  899,  900 }, /* glIsEnabledi and glIsEnablediEXT */
        {  899,  901 }, /* glIsEnabledi and glIsEnablediNV */
        {  899,  902 }, /* glIsEnabledi and glIsEnablediOES */
        {  900,  271 }, /* glIsEnablediEXT and glIsEnabledIndexedEXT */
        {  900,  899 }, /* glIsEnablediEXT and glIsEnabledi */
        {  900,  901 }, /* glIsEnablediEXT and glIsEnablediNV */
        {  900,  902 }, /* glIsEnablediEXT and glIsEnablediOES */
        {  271,  899 }, /* glIsEnabledIndexedEXT and glIsEnabledi */
        {  271,  900 }, /* glIsEnabledIndexedEXT and glIsEnablediEXT */
        {  271,  901 }, /* glIsEnabledIndexedEXT and glIsEnablediNV */
        {  271,  902 }, /* glIsEnabledIndexedEXT and glIsEnablediOES */
        {  901,  271 }, /* glIsEnablediNV and glIsEnabledIndexedEXT */
        {  901,  899 }, /* glIsEnablediNV and glIsEnabledi */
        {  901,  900 }, /* glIsEnablediNV and glIsEnablediEXT */
        {  901,  902 }, /* glIsEnablediNV and glIsEnablediOES */
        {  902,  271 }, /* glIsEnablediOES and glIsEnabledIndexedEXT */
        {  902,  899 }, /* glIsEnablediOES and glIsEnabledi */
        {  902,  900 }, /* glIsEnablediOES and glIsEnablediEXT */
        {  902,  901 }, /* glIsEnablediOES and glIsEnablediNV */
        {  912,  913 }, /* glIsSync and glIsSyncAPPLE */
        {  913,  912 }, /* glIsSyncAPPLE and glIsSync */
        {  915,  916 }, /* glIsVertexArray and glIsVertexArrayOES */
        {  916,  915 }, /* glIsVertexArrayOES and glIsVertexArray */
        {  919,  920 }, /* glMapBufferRange and glMapBufferRangeEXT */
        {  920,  919 }, /* glMapBufferRangeEXT and glMapBufferRange */
        {  923,  924 }, /* glMinSampleShading and glMinSampleShadingOES */
        {  924,  923 }, /* glMinSampleShadingOES and glMinSampleShading */
        {  393,  926 }, /* glObjectLabel and glObjectLabelKHR */
        {  926,  393 }, /* glObjectLabelKHR and glObjectLabel */
        {  394,  927 }, /* glObjectPtrLabel and glObjectPtrLabelKHR */
        {  927,  394 }, /* glObjectPtrLabelKHR and glObjectPtrLabel */
        {  928,  929 }, /* glPatchParameteri and glPatchParameteriEXT */
        {  928,  930 }, /* glPatchParameteri and glPatchParameteriOES */
        {  929,  928 }, /* glPatchParameteriEXT and glPatchParameteri */
        {  929,  930 }, /* glPatchParameteriEXT and glPatchParameteriOES */
        {  930,  928 }, /* glPatchParameteriOES and glPatchParameteri */
        {  930,  929 }, /* glPatchParameteriOES and glPatchParameteriEXT */
        {  411,  932 }, /* glPopDebugGroup and glPopDebugGroupKHR */
        {  932,  411 }, /* glPopDebugGroupKHR and glPopDebugGroup */
        {  933,  934 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxEXT */
        {  933,  935 }, /* glPrimitiveBoundingBox and glPrimitiveBoundingBoxOES */
        {  934,  933 }, /* glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBox */
        {  934,  935 }, /* glPrimitiveBoundingBoxEXT and glPrimitiveBoundingBoxOES */
        {  935,  933 }, /* glPrimitiveBoundingBoxOES and glPrimitiveBoundingBox */
        {  935,  934 }, /* glPrimitiveBoundingBoxOES and glPrimitiveBoundingBoxEXT */
        {  414,  415 }, /* glPrioritizeTextures and glPrioritizeTexturesEXT */
        {  415,  414 }, /* glPrioritizeTexturesEXT and glPrioritizeTextures */
        {  936,  937 }, /* glProgramBinary and glProgramBinaryOES */
        {  937,  936 }, /* glProgramBinaryOES and glProgramBinary */
        {  938,  939 }, /* glProgramParameteri and glProgramParameteriEXT */
        {  939,  938 }, /* glProgramParameteriEXT and glProgramParameteri */
        {  940,  418 }, /* glProgramUniform1f and glProgramUniform1fEXT */
        {  418,  940 }, /* glProgramUniform1fEXT and glProgramUniform1f */
        {  941,  419 }, /* glProgramUniform1fv and glProgramUniform1fvEXT */
        {  419,  941 }, /* glProgramUniform1fvEXT and glProgramUniform1fv */
        {  942,  420 }, /* glProgramUniform1i and glProgramUniform1iEXT */
        {  420,  942 }, /* glProgramUniform1iEXT and glProgramUniform1i */
        {  943,  421 }, /* glProgramUniform1iv and glProgramUniform1ivEXT */
        {  421,  943 }, /* glProgramUniform1ivEXT and glProgramUniform1iv */
        {  944,  422 }, /* glProgramUniform1ui and glProgramUniform1uiEXT */
        {  422,  944 }, /* glProgramUniform1uiEXT and glProgramUniform1ui */
        {  945,  423 }, /* glProgramUniform1uiv and glProgramUniform1uivEXT */
        {  423,  945 }, /* glProgramUniform1uivEXT and glProgramUniform1uiv */
        {  946,  426 }, /* glProgramUniform2f and glProgramUniform2fEXT */
        {  426,  946 }, /* glProgramUniform2fEXT and glProgramUniform2f */
        {  947,  427 }, /* glProgramUniform2fv and glProgramUniform2fvEXT */
        {  427,  947 }, /* glProgramUniform2fvEXT and glProgramUniform2fv */
        {  948,  428 }, /* glProgramUniform2i and glProgramUniform2iEXT */
        {  428,  948 }, /* glProgramUniform2iEXT and glProgramUniform2i */
        {  949,  429 }, /* glProgramUniform2iv and glProgramUniform2ivEXT */
        {  429,  949 }, /* glProgramUniform2ivEXT and glProgramUniform2iv */
        {  950,  430 }, /* glProgramUniform2ui and glProgramUniform2uiEXT */
        {  430,  950 }, /* glProgramUniform2uiEXT and glProgramUniform2ui */
        {  951,  431 }, /* glProgramUniform2uiv and glProgramUniform2uivEXT */
        {  431,  951 }, /* glProgramUniform2uivEXT and glProgramUniform2uiv */
        {  952,  434 }, /* glProgramUniform3f and glProgramUniform3fEXT */
        {  434,  952 }, /* glProgramUniform3fEXT and glProgramUniform3f */
        {  953,  435 }, /* glProgramUniform3fv and glProgramUniform3fvEXT */
        {  435,  953 }, /* glProgramUniform3fvEXT and glProgramUniform3fv */
        {  954,  436 }, /* glProgramUniform3i and glProgramUniform3iEXT */
        {  436,  954 }, /* glProgramUniform3iEXT and glProgramUniform3i */
        {  955,  437 }, /* glProgramUniform3iv and glProgramUniform3ivEXT */
        {  437,  955 }, /* glProgramUniform3ivEXT and glProgramUniform3iv */
        {  956,  438 }, /* glProgramUniform3ui and glProgramUniform3uiEXT */
        {  438,  956 }, /* glProgramUniform3uiEXT and glProgramUniform3ui */
        {  957,  439 }, /* glProgramUniform3uiv and glProgramUniform3uivEXT */
        {  439,  957 }, /* glProgramUniform3uivEXT and glProgramUniform3uiv */
        {  958,  442 }, /* glProgramUniform4f and glProgramUniform4fEXT */
        {  442,  958 }, /* glProgramUniform4fEXT and glProgramUniform4f */
        {  959,  443 }, /* glProgramUniform4fv and glProgramUniform4fvEXT */
        {  443,  959 }, /* glProgramUniform4fvEXT and glProgramUniform4fv */
        {  960,  444 }, /* glProgramUniform4i and glProgramUniform4iEXT */
        {  444,  960 }, /* glProgramUniform4iEXT and glProgramUniform4i */
        {  961,  445 }, /* glProgramUniform4iv and glProgramUniform4ivEXT */
        {  445,  961 }, /* glProgramUniform4ivEXT and glProgramUniform4iv */
        {  962,  446 }, /* glProgramUniform4ui and glProgramUniform4uiEXT */
        {  446,  962 }, /* glProgramUniform4uiEXT and glProgramUniform4ui */
        {  963,  447 }, /* glProgramUniform4uiv and glProgramUniform4uivEXT */
        {  447,  963 }, /* glProgramUniform4uivEXT and glProgramUniform4uiv */
        {  964,  449 }, /* glProgramUniformMatrix2fv and glProgramUniformMatrix2fvEXT */
        {  449,  964 }, /* glProgramUniformMatrix2fvEXT and glProgramUniformMatrix2fv */
        {  965,  451 }, /* glProgramUniformMatrix2x3fv and glProgramUniformMatrix2x3fvEXT */
        {  451,  965 }, /* glProgramUniformMatrix2x3fvEXT and glProgramUniformMatrix2x3fv */
        {  966,  453 }, /* glProgramUniformMatrix2x4fv and glProgramUniformMatrix2x4fvEXT */
        {  453,  966 }, /* glProgramUniformMatrix2x4fvEXT and glProgramUniformMatrix2x4fv */
        {  967,  455 }, /* glProgramUniformMatrix3fv and glProgramUniformMatrix3fvEXT */
        {  455,  967 }, /* glProgramUniformMatrix3fvEXT and glProgramUniformMatrix3fv */
        {  968,  457 }, /* glProgramUniformMatrix3x2fv and glProgramUniformMatrix3x2fvEXT */
        {  457,  968 }, /* glProgramUniformMatrix3x2fvEXT and glProgramUniformMatrix3x2fv */
        {  969,  459 }, /* glProgramUniformMatrix3x4fv and glProgramUniformMatrix3x4fvEXT */
        {  459,  969 }, /* glProgramUniformMatrix3x4fvEXT and glProgramUniformMatrix3x4fv */
        {  970,  461 }, /* glProgramUniformMatrix4fv and glProgramUniformMatrix4fvEXT */
        {  461,  970 }, /* glProgramUniformMatrix4fvEXT and glProgramUniformMatrix4fv */
        {  971,  463 }, /* glProgramUniformMatrix4x2fv and glProgramUniformMatrix4x2fvEXT */
        {  463,  971 }, /* glProgramUniformMatrix4x2fvEXT and glProgramUniformMatrix4x2fv */
        {  972,  465 }, /* glProgramUniformMatrix4x3fv and glProgramUniformMatrix4x3fvEXT */
        {  465,  972 }, /* glProgramUniformMatrix4x3fvEXT and glProgramUniformMatrix4x3fv */
        {  469,  973 }, /* glPushDebugGroup and glPushDebugGroupKHR */
        {  973,  469 }, /* glPushDebugGroupKHR and glPushDebugGroup */
        {  975,  976 }, /* glReadnPixels and glReadnPixelsEXT */
        {  975,  977 }, /* glReadnPixels and glReadnPixelsKHR */
        {  976,  975 }, /* glReadnPixelsEXT and glReadnPixels */
        {  976,  977 }, /* glReadnPixelsEXT and glReadnPixelsKHR */
        {  977,  975 }, /* glReadnPixelsKHR and glReadnPixels */
        {  977,  976 }, /* glReadnPixelsKHR and glReadnPixelsEXT */
        {  980,  981 }, /* glRenderbufferStorageMultisample and glRenderbufferStorageMultisampleEXT */
        {  980,  982 }, /* glRenderbufferStorageMultisample and glRenderbufferStorageMultisampleNV */
        {  981,  980 }, /* glRenderbufferStorageMultisampleEXT and glRenderbufferStorageMultisample */
        {  981,  982 }, /* glRenderbufferStorageMultisampleEXT and glRenderbufferStorageMultisampleNV */
        {  982,  980 }, /* glRenderbufferStorageMultisampleNV and glRenderbufferStorageMultisample */
        {  982,  981 }, /* glRenderbufferStorageMultisampleNV and glRenderbufferStorageMultisampleEXT */
        {  986,  987 }, /* glSamplerParameterIiv and glSamplerParameterIivEXT */
        {  986,  988 }, /* glSamplerParameterIiv and glSamplerParameterIivOES */
        {  987,  986 }, /* glSamplerParameterIivEXT and glSamplerParameterIiv */
        {  987,  988 }, /* glSamplerParameterIivEXT and glSamplerParameterIivOES */
        {  988,  986 }, /* glSamplerParameterIivOES and glSamplerParameterIiv */
        {  988,  987 }, /* glSamplerParameterIivOES and glSamplerParameterIivEXT */
        {  989,  990 }, /* glSamplerParameterIuiv and glSamplerParameterIuivEXT */
        {  989,  991 }, /* glSamplerParameterIuiv and glSamplerParameterIuivOES */
        {  990,  989 }, /* glSamplerParameterIuivEXT and glSamplerParameterIuiv */
        {  990,  991 }, /* glSamplerParameterIuivEXT and glSamplerParameterIuivOES */
        {  991,  989 }, /* glSamplerParameterIuivOES and glSamplerParameterIuiv */
        {  991,  990 }, /* glSamplerParameterIuivOES and glSamplerParameterIuivEXT */
        { 1007, 1008 }, /* glTexBuffer and glTexBufferEXT */
        { 1007, 1009 }, /* glTexBuffer and glTexBufferOES */
        { 1008, 1007 }, /* glTexBufferEXT and glTexBuffer */
        { 1008, 1009 }, /* glTexBufferEXT and glTexBufferOES */
        { 1009, 1007 }, /* glTexBufferOES and glTexBuffer */
        { 1009, 1008 }, /* glTexBufferOES and glTexBufferEXT */
        { 1010, 1011 }, /* glTexBufferRange and glTexBufferRangeEXT */
        { 1010, 1012 }, /* glTexBufferRange and glTexBufferRangeOES */
        { 1011, 1010 }, /* glTexBufferRangeEXT and glTexBufferRange */
        { 1011, 1012 }, /* glTexBufferRangeEXT and glTexBufferRangeOES */
        { 1012, 1010 }, /* glTexBufferRangeOES and glTexBufferRange */
        { 1012, 1011 }, /* glTexBufferRangeOES and glTexBufferRangeEXT */
        {  563,  564 }, /* glTexImage3D and glTexImage3DEXT */
        {  564,  563 }, /* glTexImage3DEXT and glTexImage3D */
        { 1013, 1014 }, /* glTexParameterIiv and glTexParameterIivEXT */
        { 1013, 1015 }, /* glTexParameterIiv and glTexParameterIivOES */
        { 1014, 1013 }, /* glTexParameterIivEXT and glTexParameterIiv */
        { 1014, 1015 }, /* glTexParameterIivEXT and glTexParameterIivOES */
        { 1015, 1013 }, /* glTexParameterIivOES and glTexParameterIiv */
        { 1015, 1014 }, /* glTexParameterIivOES and glTexParameterIivEXT */
        { 1016, 1017 }, /* glTexParameterIuiv and glTexParameterIuivEXT */
        { 1016, 1018 }, /* glTexParameterIuiv and glTexParameterIuivOES */
        { 1017, 1016 }, /* glTexParameterIuivEXT and glTexParameterIuiv */
        { 1017, 1018 }, /* glTexParameterIuivEXT and glTexParameterIuivOES */
        { 1018, 1016 }, /* glTexParameterIuivOES and glTexParameterIuiv */
        { 1018, 1017 }, /* glTexParameterIuivOES and glTexParameterIuivEXT */
        { 1019,  570 }, /* glTexStorage2D and glTexStorage2DEXT */
        {  570, 1019 }, /* glTexStorage2DEXT and glTexStorage2D */
        { 1021,  571 }, /* glTexStorage3D and glTexStorage3DEXT */
        {  571, 1021 }, /* glTexStorage3DEXT and glTexStorage3D */
        { 1022, 1023 }, /* glTexStorage3DMultisample and glTexStorage3DMultisampleOES */
        { 1023, 1022 }, /* glTexStorage3DMultisampleOES and glTexStorage3DMultisample */
        {  572,  573 }, /* glTexSubImage1D and glTexSubImage1DEXT */
        {  573,  572 }, /* glTexSubImage1DEXT and glTexSubImage1D */
        {  574,  575 }, /* glTexSubImage2D and glTexSubImage2DEXT */
        {  575,  574 }, /* glTexSubImage2DEXT and glTexSubImage2D */
        {  576,  577 }, /* glTexSubImage3D and glTexSubImage3DEXT */
        {  577,  576 }, /* glTexSubImage3DEXT and glTexSubImage3D */
        { 1051, 1052 }, /* glUniformMatrix2x3fv and glUniformMatrix2x3fvNV */
        { 1052, 1051 }, /* glUniformMatrix2x3fvNV and glUniformMatrix2x3fv */
        { 1053, 1054 }, /* glUniformMatrix2x4fv and glUniformMatrix2x4fvNV */
        { 1054, 1053 }, /* glUniformMatrix2x4fvNV and glUniformMatrix2x4fv */
        { 1056, 1057 }, /* glUniformMatrix3x2fv and glUniformMatrix3x2fvNV */
        { 1057, 1056 }, /* glUniformMatrix3x2fvNV and glUniformMatrix3x2fv */
        { 1058, 1059 }, /* glUniformMatrix3x4fv and glUniformMatrix3x4fvNV */
        { 1059, 1058 }, /* glUniformMatrix3x4fvNV and glUniformMatrix3x4fv */
        { 1061, 1062 }, /* glUniformMatrix4x2fv and glUniformMatrix4x2fvNV */
        { 1062, 1061 }, /* glUniformMatrix4x2fvNV and glUniformMatrix4x2fv */
        { 1063, 1064 }, /* glUniformMatrix4x3fv and glUniformMatrix4x3fvNV */
        { 1064, 1063 }, /* glUniformMatrix4x3fvNV and glUniformMatrix4x3fv */
        { 1065,  601 }, /* glUnmapBuffer and glUnmapBufferARB */
        { 1065, 1066 }, /* glUnmapBuffer and glUnmapBufferOES */
        {  601, 1065 }, /* glUnmapBufferARB and glUnmapBuffer */
        {  601, 1066 }, /* glUnmapBufferARB and glUnmapBufferOES */
        { 1066, 1065 }, /* glUnmapBufferOES and glUnmapBuffer */
        { 1066,  601 }, /* glUnmapBufferOES and glUnmapBufferARB */
        { 1082, 1083 }, /* glVertexAttribDivisor and glVertexAttribDivisorANGLE */
        { 1082, 1084 }, /* glVertexAttribDivisor and glVertexAttribDivisorEXT */
        { 1082, 1085 }, /* glVertexAttribDivisor and glVertexAttribDivisorNV */
        { 1083, 1082 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisor */
        { 1083, 1084 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisorEXT */
        { 1083, 1085 }, /* glVertexAttribDivisorANGLE and glVertexAttribDivisorNV */
        { 1084, 1082 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisor */
        { 1084, 1083 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisorANGLE */
        { 1084, 1085 }, /* glVertexAttribDivisorEXT and glVertexAttribDivisorNV */
        { 1085, 1082 }, /* glVertexAttribDivisorNV and glVertexAttribDivisor */
        { 1085, 1083 }, /* glVertexAttribDivisorNV and glVertexAttribDivisorANGLE */
        { 1085, 1084 }, /* glVertexAttribDivisorNV and glVertexAttribDivisorEXT */
        { 1101, 1102 }, /* glWaitSync and glWaitSyncAPPLE */
        { 1102, 1101 }, /* glWaitSyncAPPLE and glWaitSync */
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
           2, /* GL_ARB_buffer_storage */
           3, /* GL_ARB_debug_output */
           4, /* GL_ARB_vertex_buffer_object */
           6, /* GL_EXT_copy_texture */
           7, /* GL_EXT_direct_state_access */
          12, /* GL_EXT_draw_instanced */
          13, /* GL_EXT_draw_range_elements */
          20, /* GL_EXT_separate_shader_objects */
          21, /* GL_EXT_subtexture */
          23, /* GL_EXT_texture3D */
          26, /* GL_EXT_texture_object */
          27, /* GL_EXT_texture_storage */
          28, /* GL_EXT_vertex_array */
          29, /* GL_KHR_blend_equation_advanced */
          30, /* GL_KHR_debug */
          31, /* GL_KHR_robustness */
          33, /* GL_NV_blend_equation_advanced */
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

    if (!glad_gl_find_extensions_gl(context, version)) return 0;
    glad_gl_load_GL_ARB_buffer_storage(context, load, userptr);
    glad_gl_load_GL_ARB_debug_output(context, load, userptr);
    glad_gl_load_GL_ARB_vertex_buffer_object(context, load, userptr);
    glad_gl_load_GL_EXT_copy_texture(context, load, userptr);
    glad_gl_load_GL_EXT_direct_state_access(context, load, userptr);
    glad_gl_load_GL_EXT_draw_instanced(context, load, userptr);
    glad_gl_load_GL_EXT_draw_range_elements(context, load, userptr);
    glad_gl_load_GL_EXT_separate_shader_objects(context, load, userptr);
    glad_gl_load_GL_EXT_subtexture(context, load, userptr);
    glad_gl_load_GL_EXT_texture3D(context, load, userptr);
    glad_gl_load_GL_EXT_texture_object(context, load, userptr);
    glad_gl_load_GL_EXT_texture_storage(context, load, userptr);
    glad_gl_load_GL_EXT_vertex_array(context, load, userptr);
    glad_gl_load_GL_KHR_blend_equation_advanced(context, load, userptr);
    glad_gl_load_GL_KHR_debug(context, load, userptr);
    glad_gl_load_GL_KHR_robustness(context, load, userptr);
    glad_gl_load_GL_NV_blend_equation_advanced(context, load, userptr);

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
           0, /* GL_ANGLE_instanced_arrays */
           1, /* GL_APPLE_sync */
           5, /* GL_EXT_copy_image */
           8, /* GL_EXT_disjoint_timer_query */
           9, /* GL_EXT_draw_buffers */
          10, /* GL_EXT_draw_buffers_indexed */
          11, /* GL_EXT_draw_elements_base_vertex */
          12, /* GL_EXT_draw_instanced */
          14, /* GL_EXT_geometry_shader */
          15, /* GL_EXT_instanced_arrays */
          16, /* GL_EXT_map_buffer_range */
          17, /* GL_EXT_multisampled_render_to_texture */
          18, /* GL_EXT_primitive_bounding_box */
          19, /* GL_EXT_robustness */
          20, /* GL_EXT_separate_shader_objects */
          22, /* GL_EXT_tessellation_shader */
          24, /* GL_EXT_texture_border_clamp */
          25, /* GL_EXT_texture_buffer */
          27, /* GL_EXT_texture_storage */
          29, /* GL_KHR_blend_equation_advanced */
          30, /* GL_KHR_debug */
          31, /* GL_KHR_robustness */
          32, /* GL_MESA_sampler_objects */
          33, /* GL_NV_blend_equation_advanced */
          34, /* GL_NV_copy_buffer */
          35, /* GL_NV_draw_instanced */
          36, /* GL_NV_framebuffer_blit */
          37, /* GL_NV_framebuffer_multisample */
          38, /* GL_NV_instanced_arrays */
          39, /* GL_NV_non_square_matrices */
          40, /* GL_NV_viewport_array */
          41, /* GL_OES_copy_image */
          42, /* GL_OES_draw_buffers_indexed */
          43, /* GL_OES_draw_elements_base_vertex */
          44, /* GL_OES_geometry_shader */
          45, /* GL_OES_get_program_binary */
          46, /* GL_OES_mapbuffer */
          47, /* GL_OES_primitive_bounding_box */
          48, /* GL_OES_sample_shading */
          49, /* GL_OES_tessellation_shader */
          50, /* GL_OES_texture_border_clamp */
          51, /* GL_OES_texture_buffer */
          52, /* GL_OES_texture_storage_multisample_2d_array */
          53, /* GL_OES_vertex_array_object */
          54, /* GL_OES_viewport_array */
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
    glad_gl_load_GL_ANGLE_instanced_arrays(context, load, userptr);
    glad_gl_load_GL_APPLE_sync(context, load, userptr);
    glad_gl_load_GL_EXT_copy_image(context, load, userptr);
    glad_gl_load_GL_EXT_disjoint_timer_query(context, load, userptr);
    glad_gl_load_GL_EXT_draw_buffers(context, load, userptr);
    glad_gl_load_GL_EXT_draw_buffers_indexed(context, load, userptr);
    glad_gl_load_GL_EXT_draw_elements_base_vertex(context, load, userptr);
    glad_gl_load_GL_EXT_draw_instanced(context, load, userptr);
    glad_gl_load_GL_EXT_geometry_shader(context, load, userptr);
    glad_gl_load_GL_EXT_instanced_arrays(context, load, userptr);
    glad_gl_load_GL_EXT_map_buffer_range(context, load, userptr);
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
