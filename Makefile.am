SUBDIRS = libplis docs 

EXTRA_DIST = AUTHORS COPYING ChangeLog INSTALL README TODO plis.pc.in

AUTOMAKE_OPTIONS = foreign 1.4

bin_SCRIPTS = plis-config

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = plis.pc

tests: 
	libplis/test_library
