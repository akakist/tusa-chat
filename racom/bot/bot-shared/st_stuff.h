/*
core
(c) belialov.com
*/
#ifndef ST_STUFF_H
#define ST_STUFF_H
#ifndef WIN32
#include <zlib.h>
#endif
#include "errs.h"
#include "str_lib.h"
#include <stdio.h>
#include <set>
#include <map>
#include <list>
#include <deque>
using namespace std;


struct st_malloc
{
private:
    st_malloc(const st_malloc&);             // Not defined
    st_malloc& operator=(const st_malloc&);  // Not defined
public:
    void *buf;
    st_malloc(unsigned long size);
    ~st_malloc();
};

struct st_gdbm {
    string pathname;
    st_gdbm (const string &pn);
    ~st_gdbm ();
    void store(const string&, const string&);
    string fetch(const string &key);
    map<string,string> container;

};
struct st_save_cwd
{
    string cwd;
    st_save_cwd();
    ~st_save_cwd();
};
struct st_GUSIHookDisable
{
    st_GUSIHookDisable();
    ~st_GUSIHookDisable();
    void (*savehook)();
};

#endif


