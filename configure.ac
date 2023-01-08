dnl Process this file with autoconf to produce a configure script.

AC_INIT([libplis],[1.5])
AM_INIT_AUTOMAKE()

AM_MAINTAINER_MODE

dnl Use libtool to get shared libraries
LT_PREREQ
LT_INIT
AC_ENABLE_SHARED
AC_DISABLE_STATIC

dnl dito install
AC_PROG_INSTALL

AC_CONFIG_HEADERS([config.h])

AC_PROG_CXX

PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([PCRE], [libpcre])

dnl add here all your Makefiles. These will be created by configure
AC_CONFIG_FILES(plis.pc:plis.pc.in Makefile libplis/Makefile)
AC_OUTPUT
