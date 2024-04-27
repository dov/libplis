lib_LTLIBRARIES = libplis.la

libplis_la_SOURCES = plis.cc
libplis_la_inc_HEADERS = plis.h plis_regexp.h

libplis_la_incdir = $(includedir)/plis
libplis_la_LIBADD = 

EXTRA_DIST = test_library.cc 

# set the include path found by configure
AM_CPPFLAGS= $(all_includes)

noinst_PROGRAMS = test_library

test_library_SOURCES = test_library.cc
test_library_CXXFLAGS = @PCRE_CFLAGS@
test_library_LDADD = libplis.la @PCRE_LIBS@

