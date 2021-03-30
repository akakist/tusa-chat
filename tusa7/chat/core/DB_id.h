#ifndef DB__ID__HH
#define DB__ID__HH
#include "oscar_buffer.h"
#include "errs.h"
struct DB_id
{
    unsigned int container;
    DB_id():container(0) {}
    DB_id(const string&s)
    {
        if (s.size()!=sizeof(container))
            throw cError((string)"invalid init string size ");
        memcpy(&container,s.data(),sizeof(container));
    }
    string as_string()
    {
        return string((char*)&container,sizeof(container));
    }
};
inline int operator < (const DB_id &a,const DB_id &b) {
    return a.container<b.container;
}
inline bool operator == (const DB_id &a,const DB_id &b) {
    return a.container==b.container;
}
inline bool operator != (const DB_id &a,const DB_id &b) {
    return a.container!=b.container;
}
inline out_oscar_buffer & operator<< (out_oscar_buffer& b,const DB_id &s) {
    b<<s.container;
    return b;
}
inline oscar_buffer & operator>> (oscar_buffer& b,  DB_id &s) {
    b>>s.container;
    return b;
}

#endif
