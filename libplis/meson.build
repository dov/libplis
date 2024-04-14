libplis_sources = [
  'plis.cc'
]

pcre2_dep = dependency('libpcre2-8')
deps = [pcre2_dep]

libplis = library('libplis',
                  libplis_sources,
                  dependencies : deps,    
                  install: true)

test_library = executable('test_library',
                          ['test_library.cc'],
                          link_with : libplis,
                          install: false)

install_headers(['plis.h', 'plis_regexp.h'],
                install_dir: 'plis'
                )

# Custom target to run the test
run_target('run_test',
  command: [test_library],  
  depends: [test_library],  
)
