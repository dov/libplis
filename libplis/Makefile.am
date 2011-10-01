lib_LIBRARIES = libplis.a

libplis_a_SOURCES = plis.cc

libplis_a_inc_HEADERS = plis.h plis_regexp.h

libplis_a_incdir = $(includedir)/plis
libplis_a_LIBADD = 

EXTRA_DIST = test_library.cc 

# set the include path found by configure
INCLUDES= $(all_includes)

noinst_PROGRAMS = test_library

test_library_SOURCES = test_library.cc
test_library_LDADD   =  $(lib_LIBRARIES) $(all_libraries)
test_library_LDFLAGS = 
test_library_DEPENDENCIES = $(lib_LIBRARIES)
