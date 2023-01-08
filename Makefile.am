SUBDIRS = libplis 

EXTRA_DIST = AUTHORS COPYING ChangeLog INSTALL README TODO plis.pc.in

AUTOMAKE_OPTIONS = foreign 1.4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = plis.pc

tests: 
	libplis/test_library
