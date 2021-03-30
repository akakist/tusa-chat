#ifndef CHANNLES_H
#define CHANNLES_H
#include "PTR.h"
#include "user.h"
class __chat_channels
{
private:
    map<CH_id,PTR_getter<chat_channel > >container;
    map<string,PTR_getter<chat_channel> > irc_name2channel; //
    _mutex Mutex;
public:
    void add(const CH_id & channel,const PTR_getter<chat_channel> &p);
    PTR_getter<chat_channel> operator[](const CH_id&);
    PTR_getter<chat_channel> by_irc(const string &chan);
    vector<CH_id> keys();
    void clear();
    __chat_channels():Mutex("__chat_channels") {}

};
extern	 __chat_channels  chat_channels;
bool load_channels();

#define __CH_LOCK(__ii__) PGLR(chat_channel, CH,__ii__);
#define __CH_LOCKW(__ii__) PGLW(chat_channel, CH,__ii__);

#endif
