#ifndef C_CONN__K
#define C_CONN__K
#ifndef WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include <map>
#include "_mutex.h"
#include "m_var.h"
#include "PTR.h"

#ifdef WIN32
typedef int socklen_t;
#include <winsock.h>
#endif


class c_socket: public base_container
{
public:
    std::string peer_ipaddress;
    sockaddr_in peer_address;
    std::string rd_buf;


private:
    int m__sock;
public:
    std::string send_buf;
    int timeout_sec;/*for select*/
    int timeout_usec;/*for select*/
    int recv0;
    c_socket(int sock);
    virtual ~c_socket();
    std::string get_socket_descr() const;
    int get_socket_fd() const;
    void set_socket_descr(int s);
    bool connected() const;
    int connect(const struct sockaddr*,socklen_t);
    void sock_linger(int sec);
    c_socket * __get_this__();

};
inline std::string get_object_name(c_socket*) {
    return "c_socket";
}
class out_oscar_buffer;
struct OCALC;
void reply_socket(const PTR_getter <c_socket> &__S, const std::string & _data);
void reply_socket(const PTR_getter <c_socket> &__S, const OCALC &_data);

bool readable(const PTR_getter<c_socket> &__S,int sec, int usec);
bool writeable(const PTR_getter<c_socket>& __S, int timeout_sec, int timeout_usec);
bool readable(const PTR_getter<c_socket>&__S);
bool writeable(const PTR_getter<c_socket>&__S);
std::string __gets(const PTR_getter <c_socket> &__S);
void disconnect(const PTR_getter <c_socket> &__S);
unsigned long gethostname(const char *hostname);
#endif
