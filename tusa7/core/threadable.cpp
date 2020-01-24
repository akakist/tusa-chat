#include "stdafx.h"
#include "threadable.h"
#include "errs.h"
#ifndef WIN32
#include <pthread.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

M_MAP<pthread_t, string> threadable::pths;
bool threadable::SLEEP(int sec)
{
    ;
    int n=sec*100;
    for (int i=0;i<n;i++)
    {
        ;
        if (exit_thread) {
            return true;
        }
        usleep(10000);
        
    }
    
    return false;
}
bool threadable::USLEEP(int usec)
{
    ;
    if (exit_thread) {
        return true;
    }
    usleep(usec);
    
    return false;
}
threadable::~threadable()
{
    kill_threads();
}
threadable::threadable():exit_thread(false)
{
}
void threadable::create_thread(void * (*start_routine)(void *), const std::string & __name)
{
    ;
    name=__name;
#ifdef WIN32
    thread_handle=CreateThread (NULL, 0,(LPTHREAD_START_ROUTINE) start_routine, (void*)this, 0, &thread_id);
#else
    pthread_t pt;
    int res = pthread_create(&pt, NULL, start_routine, (void *)this);
    pths.set(pt,name);

    if (res != 0) {
        throw cError("--Error: cant create pthread "+name);
    }
#endif
    

}
void threadable::kill_threads()
{

#ifdef WIN32
    /*	PostThreadMessage(thread_id,STOP_THREAD,0,0);
    	WaitForSingleObject (thread_handle, 5000);
    	CloseHandle(thread_handle);*/
#endif
}
