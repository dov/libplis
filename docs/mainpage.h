/*! \mainpage 

  \section intro Introduction

  plis is a C++ library of Perl Like Structures. It includes the
  string class \link slip plis::slip \endlink and its friend, the list class
  \link llip plis::llip \endlink (pronounced "yip"). For name protection
  these have been put in the namespace plis.

  plis is based on the Splash library by Jim Morris, that was first
  described in the October 1993 issue of The C Users Journal (see
  http://www.wolfman.com/splash.html). The plis library is directly
  based on this library but with the following changes:

    - Updated to use STL structures (string and dequeue) as its
      underlying base classes.

    - Replaced the regular expression library with great PCRE library.

    - Renamed the string and the list structures to slip and llip.
      (Ok, this might not have been a good idea. If you have a better
      idea for names please let me know!)

    - Added support for more perl functions.

  \section API API documentation
  
    - \link plis::slip slip \endlink - The string class.
    - \link plis::llip llip \endlink - The list class.

  \section Examples Examples
  Here are a few examples of some uses of plis.

  \subsection example_while_loop The basic while loop
  The following shows the basic prototype for a the perl while(<>)
  idiom. It is not very useful, but it may be used as a placeholder
  for more advanced parsing.
  \code
#include <fstream>
#include <plis.h>

using namespace std;
using namespace plis;

int main(int argc, char*argv[])
{
    fstream inf;
    slip S_;

    if (argc>1) 
	inf.open (argv[1], fstream::in);
    else 
        inf.open(0);

    while((*inf) >> s) {
        s.chomp();

        // skip comments
        if (s.m("^#"))
            continue;

	// Place your own line based parsing here.

        cout << s + "\n";
    }
}
  
  \endcode

  \subsection command_line_parsing Command line parsing
  The split() and the shift() commands make it very easy to parse
  the input, just like in perl. the slipprintf provides a printf
  compatible function that is sorely missing from the standard
  std::string function.
  \code
:
slip parse(slip command)
{
    llip cmds = command.split();
    int ntimes = 0;

    while(cmds) {
	slip S_ = cmds.shift();

	if (S_.m("^eat$")) {
	    slip S_ = cmds.shift();
	    return slipprintf("I like eating %s\n", (const char*)S_);
	}
	if (S_.m("^ntimes$")) {
	    ntimes = cmds.shift().atoi();
	    continue;
	}
	break;
    }
    return "ok";
}
  \endcode

  \subsection substitutions Substitutions
  Thanks to PCRE regular expressions work just like in perl! The
  following example shows a non-trivial conversion of a list of
  integers into a STL vector.
  \code
  // Read strings of ranges in perl syntax and build a vector<int> list.
  //
  // E.g. "1, 5, 6..9"
  //
  vector<int> slip_to_int_list(slip s)
  {
      vector<int> int_list;
      llip terms = s.split(",\\s*");

      while(terms) {
	  plis term = terms.shift();
	  llip match;
	  
	  if (term.m("^\\d+$", match)) {
	      int_list.push_back(match[0].atoi());  // match[0] == $&
	  }
	  else if (term.m("^(\\d+)\\s*\\.\\.\\s*(\\d+)$", match)) {
	      int i1 = match[1].atoi();   // match[1] == $1
	      int i2 = match[2].atoi();
	      for (int i=i1; i<=i2; i++) 
		  int_list.push_back(i);
	  }
	  else 
	      die((slip) "Unknown string in list: " + term);
      }


      return int_list;
   }
  \endcode

  More examples may be found in the test_library.cc program.
*/
