#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include <map>
#include "_mutex.h"
#include <list>
#include <time.h>
#include <errno.h>
#include <map>
#include "PTR.h"
#ifndef __CLAN
#include "mysql_extens.h"
#endif

#include "user.h"
#include "str_lib.h"
#include "message.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include "errs.h"
#include "M_MAP.h"
#include "channels.h"
#include "DR_types.h"

__chat_channels chat_channels;
static m_var<bool> channels_loaded(false);
bool load_channels()
{
    if (channels_loaded) return true;
    channels_loaded=true;
    logErr2("Loading channels...");



    vector< vector<string> > cv;
    {
        st_dbh d;
        cv=d.dbh->exec("select id,censored,save,move_to_channel,move,no_stat,ext,read_level,write_level,irc_name from channels");
    }

    if (cv.size()==0) {
        chat_channel *m=new chat_channel();

        if (!m)throw cError("!m ");
        m->cd.chid.container=0;

        m->cd.censored=false;
        m->cd.save_messages=false;
        m->cd.move_to_channel=0;
        m->cd.move=false;
        m->cd.extended=false;
        m->cd.no_statistic=false;
        m->cd.moderated=false;
        m->cd.read_level=0;
        m->cd.write_level=0;
        chat_channels.add( m->cd.chid,m);
        return true;
    }

    for (unsigned int i=0;i<cv.size();i++) {
        if (cv[i].size()!=10) throw cError("select failed in load_channels");
        chat_channel *m=new chat_channel();
        if (!m)throw cError("!m ");
        m->cd.chid.container=atoi(cv[i][0].c_str());

        vector< vector<string> > v;
        {
            st_dbh d;
            v=d.dbh->execQ((QUERY)"select lang,name from channels_names where cid=?"<<cv[i][0]);
        }
        for (unsigned int j=0;j<v.size();j++) {
            if (v[j].size()!=2) throw cError("select failed");
            m->cd.names[v[j][0]]=v[j][1];
        }
        m->cd.irc_name=cv[i][9];
        m->cd.censored=atoi(cv[i][1].c_str());
        m->cd.save_messages=atoi(cv[i][2].c_str());
        m->cd.move_to_channel=atoi(cv[i][3].c_str());
        m->cd.move=atoi(cv[i][4].c_str());
        m->cd.no_statistic=atoi(cv[i][5].c_str());
        m->cd.extended=atoi(cv[i][6].c_str());
        m->cd.read_level=atoi(cv[i][7].c_str());
        m->cd.write_level=atoi(cv[i][8].c_str());
        m->cd.moderated=false;

        vector<string> vvv;
        {
            st_dbh d;
            vvv=d.dbh->select_1_rowQ((QUERY)"select topic,owner,UNIX_TIMESTAMP(set_time) from topics where channel=? and disabled='0'"<<m->cd.chid.container);
        }
        if (vvv.size()==3)
        {

            m->cd.topic=vvv[0];
            m->cd.topic_time=atoi(vvv[2].c_str());
            DB_id o_id;
            o_id.container=atoi(vvv[1].c_str());
            if (o_id.container);
            {
                PGLR(user_set,u,user_sets.find_by_id(o_id));
                m->cd.set_by=u->last_nick;
            }
        }

        chat_channels.add(m->cd.chid,m);
    }

    return true;
}
void __chat_channels::add(const CH_id&chan,const PTR_getter<chat_channel > &p)
{

    {
        string ircname;
        {
            PGLR(chat_channel, m,p);
            ircname=m->cd.irc_name;

        }
        M_LOCK(Mutex);
        {
            container.insert(make_pair(chan,p));
            irc_name2channel.insert(pair<string,PTR_getter<chat_channel> >("#"+ircname,p));
        }
    }
}
PTR_getter<chat_channel> __chat_channels::operator[](const CH_id& n)
{

    PTR_getter<chat_channel > zz(NULL);
    M_LOCK(Mutex);
    {
        if (container.count(n)) return container.find(n)->second;
    }
    if (!zz)
        throw cError("operator[]: !zz "+itostring(n.container)+" " );
    return zz;
}
PTR_getter<chat_channel> __chat_channels::by_irc(const string &chan)
{
    PTR_getter<chat_channel > zz(NULL);
    {
        M_LOCK(Mutex);
        if (irc_name2channel.count(chan))
            return irc_name2channel.find(chan)->second;
    }
    vector<CH_id> chs=keys();
    {
        for (int i=0;i<chs.size();i++)
        {
            PTR_getter<chat_channel>C=operator[](chs[i]);
            if (C)
            {
                __CH_LOCK(C);

                if (CH->cd.irc_name==chan) {
                    logErr2("__chat_channels::by_irc not found in map, but found by iter %s",chan.c_str());
                    return C;
                }
            }

        }
    }
    return zz;
}

void __chat_channels::clear() {
    container.clear();
    irc_name2channel.clear();
}
vector<CH_id> __chat_channels::keys()
{
    vector<CH_id> r;
    {
        M_LOCK(Mutex);
        for (map<CH_id,PTR_getter<chat_channel > >::iterator i=container.begin();i!=container.end();i++)
        {
            r.push_back(i->first);
        }
    }
    return r;
}
out_oscar_buffer & operator<<(out_oscar_buffer&b, const chat_channel_data &n)
{
    b<<n.irc_name;
    b<<n.names;
    b<<n.chid;
    b<<n.move_to_channel;
    b<<n.move;
    b<<n.save_messages;
    b<<n.censored;
    b<<n.topic;
    b<<n.set_by;
    b<<n.topic_time;
    b<<n.read_level;
    b<<n.write_level;
    b<<n.extended;
    b<<n.moderated;
    b<<n.no_statistic;
    return b;

}
oscar_buffer & operator>>(oscar_buffer&b, chat_channel_data &n)
{
    b>>n.irc_name;
    b>>n.names;
    b>>n.chid;
    b>>n.move_to_channel;
    b>>n.move;
    b>>n.save_messages;
    b>>n.censored;
    b>>n.topic;
    b>>n.set_by;
    b>>n.topic_time;
    b>>n.read_level;
    b>>n.write_level;
    b>>n.extended;
    b>>n.moderated;
    b>>n.no_statistic;
    return b;

}
void pack_channels(out_oscar_buffer &bb)
{
    vector<CH_id>chs=chat_channels.keys();
    bb<<chs.size();
    for (unsigned int i=0;i<chs.size();i++) {
        __CH_LOCK(chat_channels[chs[i]]);
        bb<<CH->cd;
    }

}
void unpack_channels(oscar_buffer &bb)
{
    int n;
    bb>>n;
    for (int i=0;i<n;i++)
    {
        chat_channel *m=new chat_channel();
        bb>>m->cd;
        chat_channels.add(m->cd.chid,m);

    }

}
