## Process this file with automake to produce Makefile.in

EXTRA_DIST = mainpage.h doxygen_footer.html libplis.doxygen

noinst_DATA = index.html 

index.html: libplis.doxygen
	doxygen libplis.doxygen

htmldir = share/doc/plis/html
install-data-hook:
	mkdir -p $(prefix)/$(htmldir)
	cp -dpR html/* $(prefix)/$(htmldir)
