#ifndef ERRS_Hhh
#define ERRS_Hhh
#include <string>
#ifndef WIN32
#include <unistd.h>
#endif
#include <vector>
#include <stdexcept>

//using namespace std;

#define E_NOERR 0
struct sockaddr_in;
struct hstring;

#ifdef DEBUG
#define DBG(a) a
#else
#define DBG(a)
#endif

struct
#ifdef WIN32
            __declspec (dllexport)
#endif
            cError
{
    enum
    {

        E_COMMON			=1,
        //////////// SERVER SIDE

        E_INVALIDLOGIN		=10,
        E_OPERATIONDENIED	=11,
        E_USERALREADYEXISTS	=12,
        E_USERBUSY			=13,
        E_PASSWORDNOTMATCH	=14,


        //////////// CLIENT SIDE
        E_INVALIDANSWER		=15,
        E_BADCA				=16,
        E_MD5NOTMATCH		=17,

        //////////// BOTH
        E_BADCERT			=18,
        E_TIMEOUT			=19,
        E_MYSQL				=20,
        EDATABASE			=21,
        ENOROLEDEFINED 		=22,
        E_SUBPARTREMOVED	=23,
        E_OPERATIONDENIEDMESS=24,
        E_MSGSERVER				=25,
        // WEBICQ
        E_ICQCLIENTNULL=26,
        E_FATAL=27

    };
    unsigned  char 	error_code;
    std::string 		error_string;
//	    hstring *_hstr;
    ///////////////////////////////
    ///NEDDED fo CLIENT
    bool fatal;

//	    cError(int e);
    cError(int e, const std::string &s);
    cError(const std::string&);
//	    cError(const hstring&);
    ~cError() {};

    void handle_error();
    void handle_error(bool fatal);
    const char *what() {
        return error_string.c_str();
    }
};
class socketError:public cError
{
public:
    socketError(const std::string s): cError(s) {}

};
class too_many_users_Error:public cError
{
public:
    too_many_users_Error(): cError("too many users") {}

};

extern std::vector<std::string> err_vector;
#ifndef macintosh
struct LException {};
#endif
#define __CATCH(level)		 catch(cError e){e.handle_error(level);}\
								catch(LException e){FatalErrorDialog("LException occured");Terminate();}\
								catch(std::string s){FatalErrorDialog(s);}\
								catch(...) {logErr("Unknown exception");}


#define throw_cErrorAPI(a) {std::string _ss=(std::string)a+" "+strerror(errno);throw cError(_ss);}
#ifdef DEBUG
#define throw_cErrorFL(a) {char sss[200];snprintf(sss,sizeof(sss)-1,"%s: %s %d",a,__FILE__,__LINE__);throw cError(sss);}
#else
#define throw_cErrorFL(a) {throw cError(a);}
#endif
//extern "C"
//{
#ifdef WIN32
__declspec(dllexport)
#endif
void logErr(const char *fmt,...);
#ifdef WIN32
__declspec(dllexport)
#endif
void logErr2(const char *fmt, ...);
//}

#ifdef DEBUG
#	define __FL__	__FILE__,__LINE__
#else
#	define __FL__	"",0
#endif

#define DUMP(a) /* fprintf(stderr,"%s %s %d\n",a,__FILE__,__LINE__);*/
#ifdef DEBUG
#define STDCATCHS(SSS)       \
	  catch(socketError e){}catch(cError e) {\
	  logErr2("---Error: '%s' '%s' %s %d", SSS,e.error_string.c_str(),__FILE__,__LINE__);\
      }\
	  catch(logic_error e)\
	  {\
		 logErr2("---Error: logic_error:  '%s' '%s' %s %d", SSS,e.what(),__FILE__,__LINE__);\
	  }\
	  catch(runtime_error e)\
	  {\
		 logErr2("---Error: runtime_error:  '%s' '%s' %s %d", SSS,e.what(),__FILE__,__LINE__);\
	  }\
	  catch(exception e)\
	  {\
		 logErr2("---Error: exception:  '%s' '%s' %s %d", SSS,e.what(),__FILE__,__LINE__);\
	  }\
      catch(...) {\
	 logErr2("---Error: Unknown error: '%s' %s %d",SSS,__FILE__,__LINE__);\
      }
#else
#define STDCATCHS(SSS)       catch(socketError e){} catch(cError e) {\
	 logErr2("---Error: '%s' %s", SSS,e.error_string.c_str());\
	 sleep(1);\
      }\
	  catch(logic_error e)\
	  {\
		 logErr2("---Error: logic_error:  '%s' %s", SSS,e.what());\
		 sleep(1);\
	  }\
	  catch(runtime_error e)\
	  {\
		 logErr2("---Error: runtime_error:  '%s' %s", SSS,e.what());\
		 sleep(1);\
	  }\
	  catch(exception e)\
	  {\
		 logErr2("---Error: exception:  '%s' '%s' %s %d", SSS,e.what(),__FL__);\
	  }\
      catch(...) {\
	 logErr2("---Error: Unknown error: '%s'",SSS);\
	  sleep(1);\
      }
#endif

#endif
