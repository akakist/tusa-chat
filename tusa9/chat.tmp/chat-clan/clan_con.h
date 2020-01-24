#ifndef clan_con__H
#define clan_con__H
#include "PTR.h"
#include "c_conn.h"
#include <map>
#include <string>
using namespace std;

class app_connection;
class clan_con: public base_container
{

    public:
    int luid;
    time_t create_time;
    app_connection *wc;
    clan_con();
    ~clan_con();

};
class __clan_cons
{

    _mutex Mutex;
    std::map<int,PTR_getter<clan_con> > container;
    public:    
    __clan_cons();
    PTR_getter<clan_con> find(int _luid);
    PTR_getter<clan_con> extract(int _luid);
    void insert(const PTR_getter<clan_con> &__CLU);
};
    
extern __clan_cons clan_cons;
#endif
