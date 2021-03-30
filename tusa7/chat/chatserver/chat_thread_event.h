#ifndef chat_event___h
#define chat_event___h
#include "oscar_buffer.h"
#include "S_id.h"
#include "DB_id.h"
#include "CH_id.h"
#ifndef __CLAN
#endif
class chat_event
{
public:
    enum TYPE {
        INVITE				=1,
        CHMODE				=2,
        CHVOICE				=3,
        CHAT_MESSAGES			=4,
        SEND_MESSAGE			=5,
        SET_USER_STATE			=6,
        SEND_DATA_TO_WWW_USERS		=7,
        CHTOPIC				=8,
        UPDATE_DATA			=9,
        UPDATE_USER_SESSION		=11,
        __IGNORE				=12,
        SEND_USER_STATES		=14,
        irc_cmd_ISON			=15,
        irc_cmd_WHOIS			=16,
        EVT_chat_thread_stuff_pack	=17,
        EVT_chat_thread_stuff_restore	=18,
    };
    TYPE type;
    virtual ~chat_event() {}
    chat_event(TYPE t):type(t) {}
    virtual void pack(out_oscar_buffer &b)=0;
    virtual void unpack(oscar_buffer &b)=0;
    virtual string dump()=0;

};
class  chat_event_INVITE: public  chat_event
{
public:
    DB_id uid;
    DB_id zid;
    string msg;
    chat_event_INVITE():chat_event(INVITE) {}
    void pack(out_oscar_buffer &b);
    void unpack(oscar_buffer &b);
    string dump();
};

class chat_event_CHVOICE: public  chat_event
{
public:
    string nick;
    CH_id channel;
    DB_id uid;
    int voice;// // -1 to invert current voice
    chat_event_CHVOICE():chat_event(CHVOICE) {}
    void pack(out_oscar_buffer &b);
    void unpack(oscar_buffer &b);
    string dump();
};
class chat_event_CHMODE: public  chat_event
{
public:
    string nick;
    CH_id channel;
    DB_id uid;
    int mode; // -1 to invert current mode
    chat_event_CHMODE():chat_event(CHMODE) {}
    void pack(out_oscar_buffer &b);
    void unpack(oscar_buffer &b);
    string dump();
};
class chat_event_CHAT_MESSAGES: public  chat_event
{
public:
    chat_event_CHAT_MESSAGES():chat_event(CHAT_MESSAGES) {}
    string c;
    DB_id uid;
    void pack(out_oscar_buffer &b);
    void unpack(oscar_buffer &b);
    string dump();
};

class chat_event_SEND_MESSAGE: public  chat_event
{
public:
    chat_event_SEND_MESSAGE():chat_event(SEND_MESSAGE) {}
    DB_id from_uid;
    string msg;
    string tonick;
    bool priv;
    bool sys;
    bool makeit;
    CH_id channel;
    unsigned char user_type;
    void pack(out_oscar_buffer &b);
    void unpack(oscar_buffer &b);
    string dump();
};
class user_state;
class chat_event_SET_USER_STATE: public  chat_event
{
public:
    chat_event_SET_USER_STATE():chat_event(SET_USER_STATE) {}
    string msg;
    void pack(out_oscar_buffer &b);
    void unpack(oscar_buffer &b);
    string dump();
};

class chat_event_SEND_DATA_TO_WWW_USERS: public  chat_event
{
public:
    chat_event_SEND_DATA_TO_WWW_USERS():chat_event(SEND_DATA_TO_WWW_USERS) {}
    string msg;
    void pack(out_oscar_buffer &b);
    void unpack(oscar_buffer &b);
    string dump();
};

class chat_event_CHTOPIC: public  chat_event
{
public:
    DB_id uid;
    CH_id channel;
    string top;
    chat_event_CHTOPIC():chat_event(CHTOPIC) {}
    void pack(out_oscar_buffer &b);
    void unpack(oscar_buffer &b);
    string dump();
};

class chat_event_UPDATE_DATA: public  chat_event
{
public:
    string buf;
    chat_event_UPDATE_DATA():chat_event(UPDATE_DATA) {}
    void pack(out_oscar_buffer &b);
    void unpack(oscar_buffer &b);
    string dump();
};

class chat_event_UPDATE_USER_SESSION: public  chat_event
{
public:
    DB_id uid;
    string ip;
    string pip;
    unsigned char user_type;
    chat_event_UPDATE_USER_SESSION():chat_event(UPDATE_USER_SESSION) {}
    void pack(out_oscar_buffer &b);
    void unpack(oscar_buffer &b);
    string dump();
};
class chat_event_IGNORE: public  chat_event
{
public:
    DB_id uid,zid;
    chat_event_IGNORE():chat_event(__IGNORE) {}
    void pack(out_oscar_buffer &b);
    void unpack(oscar_buffer &b);
    string dump();
};

class chat_event_irc_cmd_ISON: public  chat_event
{
public:
    vector<string> nicks;
    PTR_getter<chat_user> __U;
    chat_event_irc_cmd_ISON():chat_event(irc_cmd_ISON),__U(NULL) {}
    void pack(out_oscar_buffer &b);
    void unpack(oscar_buffer &b);
    string dump();

};
class chat_event_irc_cmd_WHOIS: public  chat_event
{
public:
    string nick;
    PTR_getter<chat_user> __U;
    chat_event_irc_cmd_WHOIS():chat_event(irc_cmd_WHOIS),__U(NULL) {}
    void pack(out_oscar_buffer &b);
    void unpack(oscar_buffer &b);
    string dump();

};

extern M_DEQUE<chat_event*> __chat_events;
void send_chat_event(chat_event*, bool broadcast);

#endif
