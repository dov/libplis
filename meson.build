# meson --buildtype debug build_debug
project('libplis','cpp',
        version: '0.1.4',
        default_options : ['c_std=c++11'])

cxx = meson.get_compiler('cpp')
dep_pcre = cxx.find_library('pcre')

subdir('libplis')

# plis.pc
if not meson.is_subproject()
  pkg = import('pkgconfig')
  pkg.generate(libplis,
    name: 'libplis',
    filebase: 'libplis',
    description: 'A perl like c++ string library',
    version: meson.project_version())
endif
