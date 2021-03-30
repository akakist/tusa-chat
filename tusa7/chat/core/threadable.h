#ifndef threadable__h
#define threadable__h
#include "M_MAP.h"
#include <string>
using namespace std;
#define STOP_THREAD 0
class threadable
{
public:
    string name;
    virtual ~threadable();
    threadable();
    bool SLEEP(int sec);
    bool USLEEP(int usec);
    void create_thread(void * (*start_routine)(void *), const std::string & __name);

//    void create_thread(void * (*start_routine)(void *), const std::string & name);
    void kill_threads();
#ifdef WIN32
    DWORD thread_id;
    HANDLE thread_handle;
#endif
private:
    bool exit_thread;
    static M_MAP<pthread_t, string> pths;


};
#endif
