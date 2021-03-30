#ifdef __GNUC__
#pragma implementation				// gcc: implement sql_udf.h
#endif

#include "stdafx.h"
#include <stdlib.h>
#ifdef WIN32
#	include <process.h>
#	include "wrappers.h"
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <winsock.h>
#else
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <sys/stat.h>
#endif

#include <sys/types.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include "str_lib.h"
#include <fcntl.h>
#include "copy_file.h"
#ifndef WIN32
#	ifndef SOCKET_ERROR
#		define SOCKET_ERROR -1
#	else
#		error SOCKET_ERROR is already defined!!!
#	endif
#	ifndef INVALID_SOCKET
#		define INVALID_SOCKET -1
#	else
#		error INVALID_SOCKET is already defined!!!
#	endif
#endif

#include "wrappers.h"
#include <errno.h>

#include "tcp_stats.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void wrappers_cpp() {}
int my_connect(int s, const struct sockaddr *sa, int len)
{
#ifdef macintosh
    return connect(s, sa, len);
#else
    return connect(s, sa, len);
#endif
}

int my_bind(int s, const struct sockaddr *sa, int len)
{
#ifdef macintosh
    return bind(s, sa, len);
#else
    return bind(s, sa, len);
#endif
}

int my_accept(int s, struct sockaddr *sa, int *len)
{
    int retval=
#ifdef WIN32
        accept(s, sa, len);
#else
        accept(s, sa, (unsigned int *) len);
#endif
    if (retval!=-1)++tcp_total_accepted_connections;
    return retval;
}

int my_send(int s, char *buf, int len, int flags)
{
    int res=
#ifdef macintosh
        send(s, buf, len, flags);
#else
        send(s, buf, len, flags);
#endif
    if (res!=-1)tcp_total_send += res;
    return res;

}

int my_recv(int s, char *buf, int len, int flags)
{
    int ret=recv(s, buf, len, flags);
    if (ret!=-1)tcp_total_recv+=ret;
    return ret;
}

int my_sendto(int s, char *buf, int len, int flags, struct sockaddr *to, int tolen)
{
#ifdef macintosh
    return sendto(s, buf, len, flags, to, tolen);
#else
    return sendto(s, buf, len, flags, to, tolen);
#endif
}
int my_recvfrom(int s, char *buf, int len, int flags, struct sockaddr *to, int *tolen)
{
    int ret=
#ifdef WIN32
        recvfrom(s, buf, len, flags, to, tolen);
#else
        recvfrom(s, buf, len, flags, to, (unsigned int *) tolen);
#endif
    if (ret!=-1)tcp_total_recv+=ret;
    return ret;
}

int my_listen(int s, int bl)
{
#ifdef macintosh
    return listen(s, bl);
#else
    return listen(s, bl);
#endif
}

int my_getsockname(int s, struct sockaddr *addr, int *len)
{
#ifdef WIN32
    return getsockname(s, addr, len);
#else
    return getsockname(s, addr, (unsigned int *) len);
#endif
}
int my_select(int a, fd_set * b, fd_set * c, fd_set * d, struct timeval *e)
{
#ifdef macintosh
    return select(a, b, c, d, e);
#else
    return select(a, b, c, d, e);
#endif
}

/*int my_closesocket(int s)
{
#ifndef WIN32
	return close(s);
#else
	return closesocket(s);
#endif

}*/

FILE *my_fopen(char *a, char *b)
{
#ifdef macintosh
    return fopen(a, b);
#else
    return ::fopen(a, b);
#endif
}

int my_fclose(FILE * f)
{
#ifdef macintosh
    return fclose(f);
#else
    return ::fclose(f);
#endif

}
int my_fread(void *a, int b, int c, FILE * d)
{
#ifdef macintosh
    return fread(a, b, c, d);
#else
    return ::fread(a, b, c, d);
#endif

}
int my_fwrite(const void *a, int b, int c, FILE * d)
{
#ifdef macintosh
    return fwrite(a, b, c, d);
#else
    return fwrite(a, b, c, d);
#endif

}
int my_fseek(FILE * f, long l, int t)
{
#ifdef macintosh
    return fseek(f, l, t);
#else
    return ::fseek(f, l, t);
#endif
}
void my_mkdir(const string & path)
{
    int res;
#ifdef WIN32
    res = _mkdir(path.c_str());
#else
#if defined(macintosh)
    res = mkdir(to_mac_enc(path).c_str());
#else
    res = mkdir(path.c_str(), 0755);
#endif
#endif
    if (res) {
        throw_cErrorAPI("mkdir " + path);
    }
}
string my_getcwd()
{
    char s[500];
#ifdef WIN32
    char *res = _getcwd(s, 499);
#else
    char *res = getcwd(s, 499);
#endif
    if (res != s) {
        throw_cErrorAPI("getcwd");
    }
    return s;
}
int my_stat(const string & pathname, STAT * buf)
{
#if defined(macintosh)
    return stat(to_mac_enc(pathname).c_str(), buf);
#elif defined (WIN32)
    return ::_stat((char *) pathname.c_str(), buf);
#else
    return stat(pathname.c_str(), buf);
#endif
    return -1;
}
int my_chdir(const string &s)
{
#ifdef WIN32
    return _chdir(s.c_str());
#else
    return chdir(s.c_str());
#endif
}
