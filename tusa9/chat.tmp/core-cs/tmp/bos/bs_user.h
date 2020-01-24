#ifndef bs_user__H
#define bs_user__H
#include "PTR.h"
#include "c_conn.h"
#include <map>
#include "BU_session.h"
#include "rijndael.h"
#include "st_rsa.h"

class c_socket;
class bos_server;
struct bs_user :public base_container
{

    const char* getclassname()const {return "bs_user";}

    BU_session session_id; // session ID
    std::map<std::string,std::string> relogin_params;
    std::string login_data;
    PTR_getter<c_socket> __socket;
    time_t last_access_time;
    std::string peer_ipaddress;
    bool authorized;
    time_t create_time;

    unsigned char rjKey[RIJNDAEL_KEYSIZE];
    unsigned char rjIV_in[RIJNDAEL_BLOCKSIZE];
    unsigned char rjIV_out[RIJNDAEL_BLOCKSIZE];
    RIJNDAEL_context rjctx_in;
    RIJNDAEL_context rjctx_out;
    std::string rjDecode(const enc_string & in);
    enc_string  rjEncode(const std::string &in);
    bs_user();
    ~bs_user();

    static void reply(const PTR_getter<bs_user> &__S, const OCALC & _data);
};


class ___bs_users:public Mutexable
{
    //Mutex Mutex;
    std::map<BU_session, PTR_getter<bs_user> > container;
    bos_server* server;
public:
	___bs_users(bos_server* s):server(s){}
    void _BS_insert(const BU_session&, const PTR_getter<bs_user>& __U);
    PTR_getter<bs_user> _BS_find(const BU_session& id);
    size_t _BS_count(const BU_session& id);
    std::vector<BU_session> _BS_keys();
    void _BS_erase(const BU_session& id);
    void _BS_clear();
    size_t _BS_size();
    void on_iterate();
    std::map<BU_session, PTR_getter<bs_user> > _BS_get_container();
};


#endif
