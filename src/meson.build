libplis_sources = files(
  'plis.cc'
)

pcre2_dep = dependency('libpcre2-8')
deps = [pcre2_dep]

libplis_lib = library('plis',
                      libplis_sources,
                      include_directories: libplis_inc,
                      dependencies : deps,    
                      install: not meson.is_subproject())

