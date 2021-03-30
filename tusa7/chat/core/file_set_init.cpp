#ifdef __GNUC__
#pragma implementation				// gcc: implement sql_udf.h
#endif

#include "stdafx.h"
#include <sys/types.h>
#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#else
//#include "kks_interface.h"
#include "wrappers.h"
#endif
#include <vector>
#include <map>
#include <stdio.h>
#include "_mutex.h"
#include "errs.h"
#include "str_lib.h"
#include "st_stuff.h"
#include <errno.h>
#include "file_set.h"
#include "st_stream_str.h"
#include "copy_file.h"
#include "wrappers.h"

#include "server_config.h"
#include <ctype.h>
void file_set_init_cpp() {}
m_var<bool> files_dump_inited(false);


