# Introduction

Plis is a library for string handling in C++. It is built upon the splash
library [1] which in turn is based on the perl philosophy of strings. Examples
of functions supported by it are split(), join(), push(), shift(), grep() and
many others. It's regular expression engine is provided by pcre2.

# Dependencies

* Plis depends on pcre2.
* It needs Doxygen for documentation.

## Building

Plis should preferably be built with `meson`. automake building is currently broken.

# License

Plis is licensed under the terms of the GNU Lesser Public License (LGPL) - see
the file COPYING for details.

# References
- [1] http://www.wolfman.com/splash
