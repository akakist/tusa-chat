/*
core
(c) belialov.com
*/
//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#ifndef WIN32
#include <sys/stat.h>
#endif
#include "st_stuff.h"
#include "str_lib.h"
#include "errs.h"
#include <errno.h>

//#include <mysql.h>
#include <errno.h>
#include "_mutex.h"
#define DUMP(a)
void st_stuff_cpp() {}
st_malloc::st_malloc(unsigned long size)
{
    buf = malloc(size + 1);
    if (buf==NULL)throw cError("st_malloc failed");
    DUMP("malloc");
}

st_malloc::~st_malloc()
{
    free(buf);
    DUMP("free");
}

