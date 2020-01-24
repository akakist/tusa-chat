#include "stdafx.h"
#include <list>
#include "errs.h"
#include "_mutex.h"

#include <stdio.h>
#include <errno.h>
#include <ctime>
#include "str_lib.h"
#include <string>
#ifdef WIN32
#define snprintf _snprintf
#endif
#define MUTEXLOCK_TIMEOUT 50
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void _mutex_cpp() {}
using namespace std;
#ifndef WIN32
/*
	declare not declared in std headers
*/
extern "C" int pthread_mutexattr_settype (pthread_mutexattr_t *__attr, int __kind);
#endif
_mutex::_mutex(const string& n)
#ifdef WITH_MUTEXES
//:name(n)
#endif
{
// init mutex
#ifdef WIN32
#ifdef WITH_MUTEXES
    InitializeCriticalSection((CRITICAL_SECTION *) & m_);
#endif
#else
    pthread_mutexattr_t mt;
    pthread_mutexattr_init(&mt);
#ifndef __FreeBSD__
    pthread_mutexattr_settype(&mt, PTHREAD_MUTEX_RECURSIVE_NP);
#else
    pthread_mutexattr_settype(&mt, PTHREAD_MUTEX_RECURSIVE);
#endif

#ifndef _MSL_NO_EXCEPTIONS
#ifdef WITH_MUTEXES
    if (pthread_mutex_init(&m_, &mt))
        throw bad_alloc();
#endif
#else
    pthread_mutex_init(&m_, &mt);
#endif
    pthread_mutexattr_destroy(&mt);
#endif
}

_mutex::~_mutex()
{
// destroy mutex
#ifdef WITH_MUTEXES
#ifdef WIN32
    DeleteCriticalSection((CRITICAL_SECTION*)&m_);
#else

    int res = pthread_mutex_destroy(&m_);
    if (res)
    {
        char s[100];
        snprintf(s,sizeof(s)-1,"pthread_mutex_destroy:  %p ",&m_);
        throw cError( "'"/*+name+*/"' " +(string)s);
    }
#endif
#endif
}
//std::string dump_mutex_inspectors();

void _mutex::lock()
{
// lock mutex
#ifndef WIN32
#	ifdef USE_MUTEX_TRYLOCK
// cyclic try lock. If exceeded timeout throw to check dead locks
    time_t start_t=time(NULL);
    while (trylock())
    {
        usleep(1000);
        if (time(NULL)-start_t>MUTEXLOCK_TIMEOUT)
        {
#ifdef DEBUG
            char s[300];
            snprintf(s,sizeof(s)-1,"MUTEXLOCK_TIMEOUT \n ");
            string ss="'"/*+name+*/"' "+(string)s+dump_mutex_inspectors()+"\nMREPORT_END";
            throw cError(ss);
#else
            throw cError("MUTEXLOCK_TIMEOUT");
#endif
        }
    }
#	else
    int res=pthread_mutex_lock((pthread_mutex_t*)&m_);
    if (res) throw cError("--Error: pthread_mutex_lock returns "+itostring(res)+"'"/*+name+*/"'");
#	endif
#else
#ifdef WITH_MUTEXES
    EnterCriticalSection((CRITICAL_SECTION*)&m_);
#endif
#endif
}

#ifndef WIN32
int _mutex::trylock()
{
    /*
    	try lock. Only unix version available
    */
#ifdef WITH_MUTEXES
    int res=pthread_mutex_trylock((pthread_mutex_t*)&m_);
    return res;
#endif
}
#endif

void _mutex::unlock()
{
// mutex unlock
#ifdef WITH_MUTEXES
#ifdef WIN32
    LeaveCriticalSection((CRITICAL_SECTION*)&m_);
#else
    pthread_mutex_unlock((pthread_mutex_t*)&m_);
#endif
#endif
}

#ifdef WIN32
/* win32 wrappers*/
pthread_t pthread_self() {
    return (pthread_t)GetCurrentThreadId();
}

void usleep(unsigned long l) {
    Sleep(l/1000);
}

int pthread_create(pthread_t * pt, void *attr, void *(f)
                   (void *), void *par)
{

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    DWORD tid;
    HANDLE ret = CreateThread(&sa,	// pointer to security attributes
                              0,	// initial thread stack size
                              (unsigned long (__stdcall *) (void *))f,	// pointer to thread function
                              par,	// argument for new thread
                              0,	// creation flags
                              &tid	// pointer to receive thread ID
                             );
    *pt=ret;
    if (ret == NULL)
        return 1;
    else
        return 0;
    return 0;
}
void sleep(unsigned long i)
{
    Sleep(i*1000);
}

#endif
