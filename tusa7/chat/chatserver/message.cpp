#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <list>
#include <stdio.h>
#include "errs.h"
#include <map>
#include "utils.h"
#include "web_server.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "user.h"
#include "message.h"
#include "web_server.h"
#include "copy_file.h"
#include "wrappers.h"
#include "file_set.h"
#include "channels.h"
#include "levels.h"
#include "server_config.h"

#include "chat_colors.h"
#include "chat_config.h"

#include "irc_utils.h"
#include "irc_server_config.h"
#include "DB_id.h"
#include "CH_id.h"
#include "update_cmd.h"
#include "chat_msg.h"
#include "cm_container.h"
#include "M_DEQUE.h"
extern M_DEQUE<pair<string,string> > messages_to_backup;
cm_container msgs_defstatus("defstatus");
cm_container msgs_greeting("greetings");
cm_container msgs_bye("bye");
cm_container msgs_kicking("kicking");
cm_container msgs_killing("killing");
cm_container msgs_changes("changes");
cm_container msgs_nickchanges("nick_changes");
cm_container msgs_topicchanges("topic_changes");
cm_container msgs_modechanges("mode_changes");
cm_container msgs_maty("cenmess");
chat_channel::chat_channel():base_container("chat_channel")
{

}

chat_channel::~chat_channel()
{
}
string chat_channel_data::name() const
{
    map<string,string>::const_iterator i=names.find("");
    if (i!=names.end()) return i->second;
    i=names.find("");
    if (i!=names.end()) return i->second;
    logErr2("messaglist %d name does not exists",chid.container);
    return "";
}

string chat_channel_data::name2() const
{
    map<string,string>::const_iterator i=names.find("2");
    if (i!=names.end()) return i->second;
    i=names.find("2");
    if (i!=names.end()) return i->second;
    logErr2("messaglist %d name2 does not exists",chid.container);
    return "";
}


extern M_DEQUE<pair<string,string> > messages_to_backup;
void chat_channels_backup_messages()
{
    string fn__=(string)chat_config.history_dir+split_char+date4file(time(NULL));
    deque<pair<string,string> > d=messages_to_backup.extract_all();
    string out_bin;
    string out_txt;
    for (typeof(d.begin())i=d.begin();i!=d.end();i++)
    {
        out_bin+=i->first;
        out_txt+=i->second;
    }
    try {
        if (out_bin.size())
        {
            string fn=fn__+".bin";
            check_path_wfn(fn.c_str());
            st_FILE f(fn,"ab");
            f.write(out_bin);
        }
        if (out_txt.size())
        {
            string fn2=fn__+".txt";
            check_path_wfn(fn2.c_str());
            st_FILE f(fn2,"ab");
            f.write(out_txt);

        }
    }
    catch (cError e)
    {
        logErr2("catched %s %d '%s'",__FILE__,__LINE__,e.what());
    }
    catch (...)
    {

    }
}
string cm_container::get(unsigned int g,unsigned int n)
{
    M_LOCK(Mutex);
    if (g >= container.size()) {
        logErr2("--Error: n>container.size() - in %s.%d",_name.get().c_str(),g);
        return "";
    }
    if (n >= container[g].size()) {
        logErr2("--Error: n>container.size() - in %s.%d",_name.get().c_str(),g);
        return "";
    }
    return container[g][n];
}

unsigned int cm_container::size()
{
    M_LOCK(Mutex);
    if (container.size())
        return container[0].size();
    return 0;
}

string cm_container::get_random(unsigned int g)
{
    unsigned int n=get_random_n(g);
    M_LOCK(Mutex);
    if (g >= container.size()) {
        logErr2("--Error: n>container.size() - in %s.%d",_name.get().c_str(),g);
        return "";
    }
    if (n >= container[g].size()) {
        logErr2("--Error: n>container.size() - in %s.%d",_name.get().c_str(),g);
        return "";
    }
    return container[g][n];
}

unsigned int cm_container::get_random_n(unsigned int g)
{

    M_LOCK(Mutex);
    int k=container[g].size();
    unsigned int n=0;
    if (k)n=rand()%k;
    if (n>=container[g].size()) {
        n=0;
    }
    return n;
}

void cm_container::assign(const vector< vector<string> >  &v)
{
    M_LOCK(Mutex);
    container=v;
}
void cm_container::assign_ck(const vector< vector<string> > &v)
{
    {
        M_LOCK(Mutex);
        container=v;
    }
    check();
}

void cm_container::clear()
{
    M_LOCK(Mutex);
    container.clear();
}

void cm_container::check()
{
    M_LOCK(Mutex);
    unsigned int max=0;
    for (unsigned int j=0;j<container.size();j++) {
        if (max<container[j].size()) max=container[j].size();
    }
    {
        for (unsigned int j=0;j<container.size();j++) {
            if (container[j].size()!=max) logErr2("--Error: size different in %s.%d: normal size=%d current size=%d",_name.get().c_str(),j,max,container[j].size());
        }
    }
}

void send_syspriv_msg(const PTR_getter<chat_user>&__U,const string &msg)
{
    user_pair __UU(__U);
    send_syspriv_msg(__UU,msg);
}
void send_syspriv_msg(const user_pair&__U,const string &msg)
{
    int utype;
    {
        __UC_LOCK;
        utype=u->user_type;
    }
    if (utype==TYPE_WWW)
    {
        string out;
        map<string,string> m;
        string syspriv;
        int ncolor;
        ncolor=user$n_color_pack(__U);
        PTR_getter<c_pack> __C=c_packs.get(ncolor);
        {
            PGLR(c_pack, c,__C);
            syspriv=c->syspriv;
        }
        m["~msg~"]=msg;
        m["~fornick~"]="";
        out=replace_vals(m,syspriv);
        data_push_back(__U,out+SCROLL+"\r\n");
    }
    else if (utype==TYPE_IRC) {
        string from_nick=GET_CNICK(__U);
        irc_send_notice(__U,msg,from_nick);
    }
}

