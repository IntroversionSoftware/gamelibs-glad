project('glad', 'c', version: '2.0.0')

compiler = meson.get_compiler('c')
link_deps = []

incdirs = ['include']

sources = [
	'src/gl.c',
]

incdirs = include_directories(incdirs)

lib = static_library(
    'glad',
    sources,
    include_directories: incdirs,
    dependencies: link_deps,
)

glad_dep = declare_dependency(
    include_directories: incdirs,
    dependencies: link_deps,
    link_with: lib,
    version: meson.project_version()
)

meson.override_dependency('glad', glad_dep)

# vim: set ts=4 sts=4 sw=4 et:
