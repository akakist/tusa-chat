#include "stdafx.h"
#include "errs.h"
#include "str_lib.h"
#include "_mutex.h"
#include <cstdarg>
#include <ctime>
#include "m_var.h"
#include "server_config.h"

#include <stdio.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

void errs_cpp() {}
static _mutex _localtime_MX("_localtime_MX");
struct tm LOCALTIME(time_t timep)
{
    MUTEX_LOCK aa(_localtime_MX);
    struct tm *p=localtime(&timep);
    return *p;
}


_mutex log_mutex("log_mutex");

static FILE *log_f=NULL;
static time_t open_f_time;
static string log_fname;
m_var<string> __APPNAME;
string log_name()
{
    string logname = "log."+__APPNAME.get();
    tm tt=LOCALTIME(time(NULL));
    char ss[200];
    snprintf(ss,sizeof(ss)-1,".%04d%02d%02d",1900+tt.tm_year,tt.tm_mon+1,tt.tm_mday);
    logname+=ss;
    return logname;
}
#ifdef WIN32
__declspec (dllexport)
#endif
void logErr(const char *fmt, ...)
{
    /*
    	log format into log file _c_log_name
    */


#ifndef WIN32
    MUTEX_TRY_LOCK kall(log_mutex);
    if (!kall.result) {
#else
    M_LOCK(log_mutex);
    if (1) {
#endif
        string ln=log_name();
        va_list argptr;
        va_start(argptr, fmt);
        if (log_f && (time(NULL)-open_f_time>1000 || log_fname!=ln))
        {
            fclose(log_f);
            log_f=NULL;
        }
        if (!log_f)
        {



            log_f = ::fopen(log_name().c_str(), "a");
            log_fname=ln;
            open_f_time=time(NULL);
        }
        if (log_f) {
            time_t t = time(NULL);
            string ss = ctime(&t);
            if (ss.size())
                fprintf(log_f, "%s: ", ss.substr(0, ss.size() - 1).c_str());
            vfprintf(log_f, fmt, argptr);
            fprintf(log_f, "\n");
            ::fflush(log_f);
        }
    }

}
#ifdef WIN32
__declspec (dllexport)
#endif

void logErr2(const char *fmt, ...)
{
    /*
    	log format into log file _c_log_name and into stdout
    */
    /*    string logname = "log."+__APPNAME.get();
    //            string logname = global_config.log_name;
                tm tt=LOCALTIME(time(NULL));
                char ss[200];
                snprintf(ss,sizeof(ss)-1,".%04d%02d%02d",1900+tt.tm_year,tt.tm_mon+1,tt.tm_mday);
                logname+=ss;*/

#ifndef WIN32
    MUTEX_TRY_LOCK kall(log_mutex);
    if (!kall.result) {
#else
    M_LOCK(log_mutex);
    if (1) {
#endif
        va_list argptr;
        va_start(argptr, fmt);
        string logname=log_name();
        if (log_f && ( time(NULL)-open_f_time>1000 ||log_fname!=logname))
        {
            fclose(log_f);
            log_f=NULL;
        }
        if (!log_f)
        {
            log_f = ::fopen(log_name().c_str(), "a");
            log_fname=logname;
            open_f_time=time(NULL);

        }
        if (log_f) {
            time_t t = time(NULL);
            string ss = ::ctime(&t);
            if (ss.size())
            {
                ::fprintf(log_f, "%s: ", ss.substr(0, ss.size() - 1).c_str());
            }
            {
                va_list argptr;
                va_start(argptr, fmt);
                ::vfprintf(log_f, fmt, argptr);
            }
            {
                ::fprintf(log_f, "\n");
                ::fflush(log_f);
            }
        }
        {
            va_list argptr;
            va_start(argptr, fmt);
            ::vprintf(fmt, argptr);
            printf("\n");
        }
    }
}

cError::cError(const string & e)
{
    error_code = E_COMMON;
    error_string = e;
}
cError::cError(int e, const string & s)
{
    error_code = e;
    error_string = s;
}
