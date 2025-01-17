# -*- Makefile -*- for glad

.SECONDEXPANSION:
.SUFFIXES:

ifneq ($(findstring $(MAKEFLAGS),s),s)
ifndef V
        QUIET          = @
        QUIET_CC       = @echo '   ' CC $<;
        QUIET_AR       = @echo '   ' AR $@;
        QUIET_RANLIB   = @echo '   ' RANLIB $@;
        QUIET_INSTALL  = @echo '   ' INSTALL $<;
        export V
endif
endif

LIB    = libglad.a
AR    ?= ar
ARFLAGS ?= rc
CC    ?= gcc
RANLIB?= ranlib
RM    ?= rm -f

BUILD_DIR := build
BUILD_ID  ?= default-build-id
OBJ_DIR   := $(BUILD_DIR)/$(BUILD_ID)

ifeq (,$(BUILD_ID))
$(error BUILD_ID cannot be an empty string)
endif

prefix ?= /usr/local
libdir := $(prefix)/lib
includedir := $(prefix)/include

HEADERS := \
	include/EGL/eglplatform.h \
	include/KHR/khrplatform.h \
	include/glad/wgl.h \
	include/glad/glx.h \
	include/glad/egl.h \
	include/glad/gl.h \
	include/glad/vulkan.h \
	include/vk_video/vulkan_video_codec_h264std.h \
	include/vk_video/vulkan_video_codec_h264std_decode.h \
	include/vk_video/vulkan_video_codec_h264std_encode.h \
	include/vk_video/vulkan_video_codec_h265std.h \
	include/vk_video/vulkan_video_codec_h265std_decode.h \
	include/vk_video/vulkan_video_codec_h265std_encode.h \
	include/vk_video/vulkan_video_codecs_common.h \
	include/vk_platform.h
SOURCES := \
	src/egl.c \
	src/gl.c \
	src/glx.c \
	src/wgl.c \
	src/vulkan.c

HEADERS_INST := $(patsubst include/%,$(includedir)/%,$(HEADERS))
OBJECTS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SOURCES))

CFLAGS ?= -O2
CPPFLAGS += -Iinclude -I../xxHash

.PHONY: install

all: $(OBJ_DIR)/$(LIB)

$(includedir)/%.h: include/%.h
	-@if [ ! -d $(includedir)/vk_video ]; then mkdir -p $(includedir)/vk_video; fi
	-@if [ ! -d $(includedir)/glad ]; then mkdir -p $(includedir)/glad; fi
	-@if [ ! -d $(includedir)/KHR ]; then mkdir -p $(includedir)/KHR; fi
	-@if [ ! -d $(includedir)/EGL ]; then mkdir -p $(includedir)/EGL; fi
	$(QUIET_INSTALL)cp $< $@
	@chmod 0644 $@

$(libdir)/%.a: $(OBJ_DIR)/%.a
	-@if [ ! -d $(libdir)  ]; then mkdir -p $(libdir); fi
	$(QUIET_INSTALL)cp $< $@
	@chmod 0644 $@

install: $(HEADERS_INST) $(libdir)/$(LIB)

clean:
	$(RM) -r $(OBJ_DIR)

distclean:
	$(RM) -r $(BUILD_DIR)

$(OBJ_DIR)/$(LIB): $(OBJECTS) | $$(@D)/.
	$(QUIET_AR)$(AR) $(ARFLAGS) $@ $^
	$(QUIET_RANLIB)$(RANLIB) $@

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)/.cflags | $$(@D)/.
	$(QUIET_CC)$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

.PRECIOUS: $(OBJ_DIR)/. $(OBJ_DIR)%/.

$(OBJ_DIR)/.:
	$(QUIET)mkdir -p $@

$(OBJ_DIR)%/.:
	$(QUIET)mkdir -p $@

TRACK_CFLAGS = $(subst ','\'',$(CC) $(CFLAGS) $(CPPFLAGS))

$(OBJ_DIR)/.cflags: .force-cflags | $$(@D)/.
	@FLAGS='$(TRACK_CFLAGS)'; \
    if test x"$$FLAGS" != x"`cat $(OBJ_DIR)/.cflags 2>/dev/null`" ; then \
        echo "    * rebuilding glad: new build flags or prefix"; \
        echo "$$FLAGS" > $(OBJ_DIR)/.cflags; \
    fi

.PHONY: .force-cflags
