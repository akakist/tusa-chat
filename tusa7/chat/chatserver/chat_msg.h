#ifndef CHAT_MSG______H
#define CHAT_MSG______H

enum M_TYPE {
    STDTO,
    PRIV,
    MAKEIT,
    SYS,
    SYSPRIV,
    INVITE,
    JOIN,
    CHTOPIC,
    KILLED,
    KICK,
    CHNICK,
    MODE,
    CHROOM,
    MAT,
    QUIT
};
struct chat_thread_stuff;
struct chat_msg$ {
    M_TYPE msgtype;
    virtual string make(const CH_id&, const DB_id &id)=0;
    virtual string make_backup(chat_thread_stuff&)=0;
    virtual void pack(out_oscar_buffer &o)=0;
    virtual void unpack(oscar_buffer &o)=0;
    chat_msg$(M_TYPE t):msgtype(t) {}
    virtual ~chat_msg$() {}
};
struct chat_msg: public base_container_nm
{
    chat_msg$ * data;
    chat_msg(chat_msg$* m):data(m) {};
    ~chat_msg() {
        if (data)delete data;
    }
};

struct chat_msg_STDTO: public chat_msg$
{
    CH_id channel;
    DB_id from_id;
    DB_id to_id;
    string from_nick;
    string msg;
    unsigned int n_color_pack;
    string make(const CH_id&,const DB_id &id);
    virtual void pack(out_oscar_buffer &o);
    virtual void unpack(oscar_buffer &o);
    virtual string make_backup(chat_thread_stuff&);
    ~chat_msg_STDTO();
    chat_msg_STDTO();
private:
    string prepf,prept,prepa;
};
struct chat_msg_PRIV: public chat_msg$
{
    CH_id channel;
    DB_id from_id;
    DB_id to_id;
    string from_nick;
    string to_nick;
    string msg;
    unsigned int n_color_pack;
    string make(const CH_id&,const DB_id &id);
    virtual string make_backup(chat_thread_stuff&);
    virtual void pack(out_oscar_buffer &o);
    virtual void unpack(oscar_buffer &o);
    ~chat_msg_PRIV();
    chat_msg_PRIV();
private:
    string prepf,prept;
};
struct chat_msg_MAKEIT: public chat_msg$
{
    CH_id channel;
    DB_id from_id;
    string from_nick;
    string msg;
    unsigned int n_color_pack;
    string make(const CH_id&,const DB_id &id);
    virtual string make_backup(chat_thread_stuff&);
    virtual void pack(out_oscar_buffer &o);
    virtual void unpack(oscar_buffer &o);
    ~chat_msg_MAKEIT();
    chat_msg_MAKEIT();
private:
    string preparation;
};
struct chat_msg_MODE: public chat_msg$
{
    CH_id channel;
    DB_id from_id;
    string nick1,nick2,msg;
    int n_index;
    unsigned char gender;
    string make(const CH_id&,const DB_id &id);
    virtual string make_backup(chat_thread_stuff&);
    virtual void pack(out_oscar_buffer &o);
    virtual void unpack(oscar_buffer &o);
    ~chat_msg_MODE();
    chat_msg_MODE();
private:
    string preparation;
};
struct chat_msg_SYS: public chat_msg$
{
    CH_id channel;
    DB_id from_id;
    string msg;
    string make(const CH_id&,const DB_id &id);
    virtual string make_backup(chat_thread_stuff&);
    virtual void pack(out_oscar_buffer &o);
    virtual void unpack(oscar_buffer &o);
    ~chat_msg_SYS();
    chat_msg_SYS();
private:
    string preparation;
};
struct chat_msg_SYSPRIV: public chat_msg$
{
    CH_id channel;
    DB_id from_id;
    DB_id to_id;
    string to_nick;
    string msg;
    string make(const CH_id&,const DB_id &id);
    virtual string make_backup(chat_thread_stuff&);
    virtual void pack(out_oscar_buffer &o);
    virtual void unpack(oscar_buffer &o);
    ~chat_msg_SYSPRIV();
    chat_msg_SYSPRIV();
private:
    map<DB_id,string> preparations;
};
struct chat_msg_JOIN: public chat_msg$
{
    CH_id channel;
    int n_index;
    string location;
    string nick;
    unsigned char gender;
    virtual string make_backup(chat_thread_stuff&);
    string make(const CH_id &channel,const DB_id &);
    virtual void pack(out_oscar_buffer &o);
    virtual void unpack(oscar_buffer &o);
    ~chat_msg_JOIN();
    chat_msg_JOIN();
private:
    string preparation;

};
struct chat_msg_KILLED: public chat_msg$
{
    CH_id channel;
    int n_index;
    unsigned char gender;
    string nick;
    virtual string make_backup(chat_thread_stuff&);
    string make(const CH_id &channel,const DB_id &__id);
    virtual void pack(out_oscar_buffer &o);
    virtual void unpack(oscar_buffer &o);
    ~chat_msg_KILLED();
    chat_msg_KILLED();
private:
    string preparation;
};
struct chat_msg_QUIT: public chat_msg$
{
    CH_id channel;
    int n_index;
    string nick;
    string add_info;
    unsigned char gender;
    string make(const CH_id &chan,const DB_id &__id);
    virtual string make_backup(chat_thread_stuff&);
    virtual void pack(out_oscar_buffer &o);
    virtual void unpack(oscar_buffer &o);
    ~chat_msg_QUIT();
    chat_msg_QUIT();
private:
    string preparation;

};
struct chat_msg_KICK: public chat_msg$
{
    CH_id channel;
    string nick;
    string zamsg;
    unsigned char gender;
    int n_index;
    string make(const CH_id &chan,const DB_id &__id);
    virtual string make_backup(chat_thread_stuff&);
    virtual void pack(out_oscar_buffer &o);
    virtual void unpack(oscar_buffer &o);
    ~chat_msg_KICK();
    chat_msg_KICK();
private:
    string preparation;
};
struct chat_msg_CHROOM: public chat_msg$
{
    CH_id channel;
    unsigned char gender;
    int n_index;
    string nick;
    string chroomname;
    string make(const CH_id &chan,const DB_id &__id);
    virtual string make_backup(chat_thread_stuff&);
    virtual void pack(out_oscar_buffer &o);
    virtual void unpack(oscar_buffer &o);
    ~chat_msg_CHROOM();
    chat_msg_CHROOM();
private:
    string preparation;

};
struct chat_msg_CHNICK: public chat_msg$
{
    CH_id channel;
    unsigned char gender;
    int n_index;
    string oldnick;
    string newnick;
    string make(const CH_id &chan,const DB_id &__id);
    virtual string make_backup(chat_thread_stuff&);
    virtual void pack(out_oscar_buffer &o);
    virtual void unpack(oscar_buffer &o);
    ~chat_msg_CHNICK();
    chat_msg_CHNICK();
private:
    string preparation;
};
struct chat_msg_CHTOPIC: public chat_msg$
{
    CH_id channel;
    unsigned char gender;
    int n_index;
    string nick;
    string topic;

    virtual string make_backup(chat_thread_stuff&);
    string make(const CH_id &chan,const DB_id &__id);
    virtual void pack(out_oscar_buffer &o);
    virtual void unpack(oscar_buffer &o);
    ~chat_msg_CHTOPIC();
    chat_msg_CHTOPIC();
private:
    string preparation;
};


struct chat_msg_MAT: public chat_msg$
{
    CH_id channel;
    unsigned char gender;
    int n_index;
    string nick;
    virtual string make_backup(chat_thread_stuff&);
    string make(const CH_id &chan,const DB_id &__id);
    virtual void pack(out_oscar_buffer &o);
    virtual void unpack(oscar_buffer &o);
    ~chat_msg_MAT();
    chat_msg_MAT();
private:
    string preparation;
};


void send_chat_msg(chat_msg$ *m);
#endif
