# meson --buildtype debug build_debug
project('libplis','cpp',
        version: '0.1.4',
        default_options : ['c_std=c++14'])

subdir('include')
libplis_inc = include_directories('include')

subdir('src')

libplis_dep = declare_dependency(
  include_directories : libplis_inc,
  link_with : libplis_lib)

subdir('tests')

# plis.pc
pkg = import('pkgconfig')
if not meson.is_subproject()
  pkg.generate(libplis_lib,
    name: 'libplis',
    filebase: 'libplis',
    description: 'A perl like c++ string library',
    version: meson.project_version())
endif
