#ifndef ERRS_Hhh1
#define ERRS_Hhh1
#include <string>
#ifndef WIN32
#include <unistd.h>
#endif
#include <vector>
#include <stdexcept>
#include "errno.h"
using namespace std;

#define E_NOERR 0
struct sockaddr_in;


void logErr(char *fmt, ...);

struct cError
{
    enum
    {

        E_COMMON			=1,
        E_TIMEOUT			=19,
        E_MYSQL				=20,
        E_FATAL=27
    };

    unsigned char error_code;
    string error_string;

    bool fatal;

    cError(int e, const string &s);
    cError(const string&);
    void handle_error();
    void handle_error(bool fatal);
    const char *what() {
        return error_string.c_str();
    }
};

class socketError:public cError
{
public:
    socketError(const string s): cError(s) {}

};

#define throw_cErrorAPI(a) {string _ss=(string)a+" "+strerror(errno);throw cError(_ss);}




#endif

