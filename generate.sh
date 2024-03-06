#!/bin/bash

set -ex

EXTENSIONS=(
	GL_ARB_buffer_storage
	GL_ARB_vertex_buffer_object
	GL_EXT_texture_storage
	GL_KHR_debug
)
printf -v extlist '%s,' "${EXTENSIONS[@]}"

GLAD_ARGS=(
	# If you don't want to pull the latest ones via HTTPS
	--reproducible

	# If you enable this, it will only include the extensions we've explicitly
	# listed above.
	--extensions="${extlist}"

	# Can be more restrictive, e.g. "gl:core=3.3", but you have to account for
	# other differences such as some GLAD_GL_VERSION_* macros not being defined
	--api=gl:compatibility=2.1,gles2,vulkan,egl,glx,wgl

	--out-path="$PWD"
	--merge
	c
	--alias
	--loader

	# Even though we don't use the multi-context feature for its declared
	# purpose, it does reduce the amount of memory consumed (by using
	# bitfields) and simplifies context reset.
	--mx --mx-global
)

# Faster profile for testing changes with the C generator
#GLAD_ARGS=(
#	--reproducible
#	--api=gl:core=3.3
#	--out-path="$PWD"
#	--merge
#	c
#	--alias
#	--loader
#	--mx --mx-global
#	--header-only
#)

#
# NOTE: This 'glad' binary is from my fork of glad2
#       https://github.com/tycho/glad/tree/glad2
#

exec glad "${GLAD_ARGS[@]}"
