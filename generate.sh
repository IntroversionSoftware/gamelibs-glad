#!/bin/bash

set -ex

EXTENSIONS=(
	EGL_ANDROID_blob_cache
	EGL_ANGLE_colorspace_attribute_passthrough
	EGL_ANGLE_create_context_extensions_enabled
	EGL_ANGLE_create_surface_swap_interval
	EGL_ANGLE_device_vulkan
	EGL_ANGLE_direct_composition
	EGL_ANGLE_display_power_preference
	EGL_ANGLE_feature_control
	EGL_ANGLE_platform_angle
	EGL_ANGLE_platform_angle_d3d
	EGL_ANGLE_platform_angle_d3d11on12
	EGL_ANGLE_platform_angle_device_id
	EGL_ANGLE_platform_angle_metal
	EGL_ANGLE_platform_angle_opengl
	EGL_ANGLE_platform_angle_vulkan
	EGL_ANGLE_program_cache_control
	EGL_ANGLE_surface_orientation
	EGL_EXT_device_query
	EGL_EXT_gl_colorspace_scrgb_linear
	EGL_EXT_platform_wayland
	EGL_EXT_platform_x11
	EGL_KHR_debug
	EGL_KHR_gl_colorspace
	GL_AMD_gpu_shader_half_float
	GL_AMD_gpu_shader_int16
	GL_ANGLE_base_vertex_base_instance
	GL_ANGLE_multi_draw
	GL_ANGLE_provoking_vertex
	GL_ANGLE_texture_multisample
	GL_ANGLE_texture_usage
	GL_APPLE_clip_distance
	GL_APPLE_texture_format_BGRA8888
	GL_ARB_base_instance
	GL_ARB_buffer_storage
	GL_ARB_clip_control
	GL_ARB_conservative_depth
	GL_ARB_debug_output
	GL_ARB_direct_state_access
	GL_ARB_draw_indirect
	GL_ARB_get_program_binary
	GL_ARB_gpu_shader5
	GL_ARB_invalidate_subdata
	GL_ARB_multi_bind
	GL_ARB_multi_draw_indirect
	GL_ARB_multisample
	GL_ARB_query_buffer_object
	GL_ARB_sample_shading
	GL_ARB_shading_language_packing
	GL_ARB_texture_filter_anisotropic
	GL_ARB_texture_gather
	GL_ARB_texture_storage
	GL_ARB_vertex_attrib_binding
	GL_EXT_base_instance
	GL_EXT_buffer_storage
	GL_EXT_clip_control
	GL_EXT_clip_cull_distance
	GL_EXT_debug_marker
	GL_EXT_direct_state_access
	GL_EXT_fragment_shader_barycentric
	GL_EXT_fragment_shading_rate
	GL_EXT_gpu_shader5
	GL_EXT_multi_draw_indirect
	GL_EXT_multisample
	GL_EXT_multisampled_render_to_texture
	GL_EXT_multisampled_render_to_texture2
	GL_EXT_sRGB_write_control
	GL_EXT_shader_16bit_storage
	GL_EXT_shader_explicit_arithmetic_types
	GL_EXT_texture_env_combine
	GL_EXT_texture_filter_anisotropic
	GL_EXT_texture_format_BGRA8888
	GL_EXT_texture_storage
	GL_KHR_debug
	GL_KHR_parallel_shader_compile
	GL_NV_fence
	GL_NV_fragment_shader_barycentric
	GL_QCOM_shading_rate
	VK_EXT_memory_budget
	VK_KHR_get_physical_device_properties2
	VK_KHR_portability_enumeration
	VK_KHR_timeline_semaphore
)
printf -v extlist '%s,' "${EXTENSIONS[@]}"

GLAD_ARGS=(
	# If you don't want to pull the latest ones via HTTPS
	--reproducible

	# If you enable this, it will only include the extensions we've explicitly
	# listed above.
	#--extensions="${extlist}"

	# Can be more restrictive, e.g. "gl:core=3.3", but you have to account for
	# other differences such as some GLAD_GL_VERSION_* macros not being defined
	--api=gl:core,gles2,vulkan,egl,glx,wgl

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

#
# NOTE: This 'glad' binary is from my fork of glad2
#       https://github.com/tycho/glad/tree/glad2
#

exec glad "${GLAD_ARGS[@]}"
