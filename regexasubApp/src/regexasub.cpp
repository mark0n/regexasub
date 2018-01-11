#include "regexasub.hpp"
#include <regex>
#include <iostream>
#include <string>
#include <errlog.h>
#include <registryFunction.h>
#include <epicsExport.h>

const int max_epics_str_len = 40;

using namespace std;

//static long regexASubInit( struct subRecord *prec )
//{
//  return 0;
//}

static long regexASubProcess( struct aSubRecord *prec )
{
  char *inp_str = (char *)prec->a;
  char *re_str  = (char *)prec->b;
  char *fmt_str = (char *)prec->c;

  if (regexASubDebug) {
    errlogPrintf("%s: PV: %s, input string:       \"%s\"\n", __func__,
                 prec->name, inp_str);
    errlogPrintf("%s: PV: %s, regular expression: \"%s\"\n", __func__,
                 prec->name, re_str);
    errlogPrintf("%s: PV: %s, format string:      \"%s\"\n", __func__,
                 prec->name, fmt_str);
  }

  string out_str;
  long ret = REGEX_OK;
  try {
    regex re(re_str);
    out_str = regex_replace(inp_str, re, fmt_str);
    if ( out_str.length() > max_epics_str_len ) {
      throw runtime_error("length of output string exceeds max. length of "
                          "EPICS type STRING - truncating to " +
                          to_string(max_epics_str_len) + " characters");
    }
  } catch(std::exception& e) {
    errlogPrintf("%s: PV: %s, error processing regular expression (%s)\n", __func__,
                 prec->name, e.what());
    ret = REGEX_ERROR;
  }

  strncpy( (char *)prec->vala, out_str.c_str(), max_epics_str_len );

  if (regexASubDebug) {
    errlogPrintf("%s: PV: %s, output string: \"%s\"\n", __func__, prec->name,
                 out_str.c_str());
  }

  return ret;
}

// Register these symbols for use by the IOC code:
epicsExportAddress( int, regexASubDebug );
epicsRegisterFunction( regexASubProcess );
