/*
 * version 1.6
 * Regexp is a class that encapsulates the Regular expression
 * stuff. Hopefully this means I can plug in different regexp
 * libraries without the rest of my code needing to be changed.
 * Written by Jim Morris,  jegm@sgi.com
 *
 * Ported to encapsulate PCRE by Dov Grobgeld 2001. The original licence
 * seems to allow any us whatsoever of the code.
 */
#ifndef	_REGEXP_H
#define _REGEXP_H
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

/*! The range class simply handles a ranged expressed as a start and an end.
  It is used internally in the Regexp and the plis classes.
*/
namespace plis
{
    class Range {
        private:
        int st, en;
    
        public:
        Range()
        {
            st=0; en= -1;
        }
    
        Range(int s, int e)
        {
            st= s; en= e;
        }
    
        int start(void) const { return st;}
        int end(void) const { return en;}
        int length(void) const { return (en-st)+1;}
    };
  
    /*! A C++ wrapper for the PCRE engine. It is used internally by the plis
      library for handling regular expressions.
    */
    class Regexp
    {
        private:
        pcre2_code *repat;
        pcre2_match_data *match_data;
        int number_of_substrings;
        PCRE2_SIZE *ovector;
      
        public:
        /*! The constructor takes a regexp string as input and immediately
          compiles it. The compiled version will be saved until the class
          is destroyed. */
        Regexp(const char *rege, const char *flag_string = "")
        {
            int options = chars_to_options(flag_string);
            int errornumber;
            PCRE2_SIZE erroroffset;
	  
            repat = pcre2_compile((PCRE2_SPTR)rege, // The pattern
                                  PCRE2_ZERO_TERMINATED,
                                  options,
                                  &errornumber,
                                  &erroroffset,
                                  nullptr);
            if (repat == NULL) 
                throw std::runtime_error("pcre_compile() failed!\n");

            match_data = pcre2_match_data_create_from_pattern(repat, NULL);
            ovector = pcre2_get_ovector_pointer(match_data);
        }
      
        ~Regexp()
        {
            pcre2_match_data_free(match_data);
            pcre2_code_free(repat);
        }    
      
        /*! \brief match a regular expression string */
        int match(const std::string& targ)
        {
            int rc = pcre2_match(
              repat,                     /* the compiled pattern */
              (PCRE2_SPTR)targ.c_str(),  /* the subject string */
              targ.size(),               /* the length of the subject */
              0,                         /* start at offset 0 in the subject */
              0,                         /* default options */
              match_data,                /* block for storing the result */
              NULL);                     /* use default match context */

            if (rc > 0)
                number_of_substrings = rc;
            else
                number_of_substrings = 0;
	  
            return ((rc >= 0) ? 1 : 0);
        }
      
        /*! \brief Returns number of substrings in the last match operation */
        int groups()
        {
            return number_of_substrings;
        }
      
        /*! \brief Get a group from the last match operation */
        Range getgroup(int n) const
        {
            // assert(n < number_of_substrings);
	  
            return Range(ovector[2*n],
                         ovector[2*n+1]-1);
        }
      
        private:
        // Currently only recognizes the perl "i" flag for case
        // independant matching.
        int chars_to_options(const std::string& flag_string)
        {
            int flags = 0;
            if (flag_string.find("i") != std::string::npos)
                flags |= PCRE2_CASELESS;
            return flags;
        }
      
    };
};
#endif
