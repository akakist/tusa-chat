#include "stdafx.h"
#include <list>
#include "_mutex.h"

#include <stdio.h>
#include "errs.h"
#include <signal.h>
#include "st_stuff.h"
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <algorithm>
#include "file_set.h"
#include "tcp_stats.h"
#include "M_MAP.h"


#ifndef WIN32
#include <arpa/inet.h>
#endif

#ifdef THREAD_NAME_DBUG
extern M_MAP <pid_t,string> thread_name_by_pid;
extern M_MAP <pthread_t,string> thread_name_by_pthread;
extern M_MAP <pthread_t,string> thread_descr_by_pthread;
#endif
#ifdef __linux__
extern M_MAP <pthread_t, pid_t> threads_pids;

#endif

