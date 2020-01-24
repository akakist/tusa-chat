#include "stdafx.h"
#include <sys/types.h>
#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

#include <vector>
#include <map>
#include <map>
#include "tcp_server_connection.h"
#include <stdio.h>
#include "_mutex.h"
#include "errs.h"
#include "str_lib.h"
#include "st_stuff.h"
#include <errno.h>

#include "file_set.h"

#include <algorithm>
#include <set>
#include <deque>

#include "M_DEQUE.h"

#include "tcp_server_data.h"

#include "tcp_stats.h"
#ifdef WIN32
#define snprintf _snprintf
#endif
#ifdef THREAD_NAME_DBUG
extern M_MAP <pid_t,string> thread_name_by_pid;
extern M_MAP <pthread_t,string> thread_name_by_pthread;
extern M_MAP <pthread_t,string> thread_descr_by_pthread;
#endif
void log_start_thread(const std::string &n)
{
    logErr2("Started thread %s",n.c_str());
}
#ifdef __linux__
time_t thread_wtime(pid_t pid);
extern M_MAP <pthread_t, pid_t> threads_pids;

#else
time_t total_wtime()
{
    return 0;
}
#ifdef __linux__
time_t thread_wtime(pid_t pid)
{
    return 0;
}
#endif
#endif

#ifndef WIN32
#endif
