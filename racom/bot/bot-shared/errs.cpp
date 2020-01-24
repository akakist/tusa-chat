#include "errs.h"
#include <cstdarg>
#include <ctime>
#include <stdio.h>
#include "config.h"
#include <deque>

void logErr (char *fmt, ...)
{
    va_list argptr;
    va_start (argptr, fmt);
    FILE *f = fopen (params["LOGNAME"].c_str (), "a");
    if (f)
    {
        time_t t = time (NULL);
        string ss = ctime (&t);
        if (ss.size ())
            fprintf (f, "%s: ", ss.substr (0, ss.size () - 1).c_str ());
        vfprintf (f, fmt, argptr);
        fprintf (f, "\n");
        fclose (f);
    }
}


cError::cError (const string & e)
{
    error_code = E_COMMON;
    error_string = e;
}

cError::cError (int e, const string & s)
{
    error_code = e;
    error_string = s;
}

