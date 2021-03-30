#ifndef CH__ID__HH
#define CH__ID__HH
#include <string.h>
struct CH_id
{
    unsigned int container;
    CH_id():container(0) {}
    CH_id(const string&s)
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
inline int operator < (const CH_id &a,const CH_id &b) {
    return a.container<b.container;
}
inline bool operator == (const CH_id &a,const CH_id &b) {
    return a.container==b.container;
}
inline bool operator != (const CH_id &a,const CH_id &b) {
    return a.container!=b.container;
}
inline out_oscar_buffer & operator<< (out_oscar_buffer& b,const CH_id &s) {
    b<<s.container;
    return b;
}
inline oscar_buffer & operator>> (oscar_buffer& b,  CH_id &s) {
    b>>s.container;
    return b;
}

#endif
