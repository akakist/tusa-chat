#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <sys/stat.h>
#include <map>
#include "mysql_extens.h"
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "web_server.h"
#include "message.h"
#include "chat_def.h"
#include "file_set.h"
#include "web_server_data.h"
#include "web_tools.h"

#include "chat_funny.h"
#include "channels.h"
#include "levels.h"
#include "server_config.h"
#include "app_def.h"
#include "chat_colors.h"
#include "chat_config.h"
#include "register.h"
#include "irc_server_config.h"

#include "update_cmd.h"
#include "oscar_buffer.h"
#include "CH_id.h"
#include "DB_id.h"
#include "chat_thread_event.h"
#include "user_credits.h"
#include "html_out.h"
#include "cs_conn_data.h"
#include "chat_globals.h"
extern M_MAP<DB_id,user_state> global_states;
void url_chat_topic(cs_conn_data *cc)
{

    CH_id channel;
    set<CH_id> channels;
    channels=global_states.get(cc->user_id).channel;
    if (!channels.size())throw cError("not in channel");
    channel=*channels.begin();
//    channel.container=atoi(cc->params["channel"]);
    /*    {
            PGLR(chat_user,u,__UU);
            if(u->cstate.channel.size())
                channel=*u->cstate.channel.begin();
    	else
        }*/


    map<string,hstring> m;
    m["~result~"]="";


    st_dbh d;
    vector<string>v=d.dbh->select_1_rowQ((QUERY)"select topic,current_price,owner,UNIX_TIMESTAMP(last_recalc) from topics where channel=? and disabled='0'"<<channel.container);
    double old_cost=0.1;
    string topic="";
    DB_id old_owner;
    double return_cost=0;
    if (v.size()==4)
    {
        topic=v[0];
        double oc=atof(v[1].c_str());
        if (oc>old_cost)
            old_cost=oc;
        if (oc>0)return_cost=oc;
        old_owner.container=atoi(v[2].c_str());
    }
    double summa;
    {
        PGLR(user_credit,u,user_credits.find_by_id(cc->user_id));
        summa=u->summa;
    }
    double new_cost=(old_cost)*1.2;
    m["~summa~"]=get_f22(summa);
    m["~cost~"]=get_f22(new_cost);
    m["~topic~"]=topic;
    m["~channel~"]=itostring(channel.container);

    if (cc->params["todo"]=="change")
    {


        if (summa<new_cost)
        {
            m["~result~"]=_MSG("notenoughcredits");
            m["~channel~"]=itostring(channel.container);
            cc->html_out+=make_pair(m,"chat/topic");
            return;
        }
        if (new_cost>atof(cc->params["cost"].c_str()))
        {
            m["~result~"]=_MSG("wrongtopiccost");
            m["~channel~"]=itostring(channel.container);
            cc->html_out+=make_pair(m,"chat/topic");
            return;
        }

        new_cost=atof(cc->params["cost"].c_str());
        DB_id topic_saler_account;
        topic_saler_account.container=chat_config2.topic_saler_account.get();
        if (!buy_thing(cc->user_id,topic_saler_account,new_cost, "topic"))
        {
            m["~result~"]=_MSG("credittransfererror");
            logErr2("--Error: return credits failded on topic %s %d",__FILE__,__LINE__);
            cc->html_out+=FREP("chat/topic");
            return;
        }
        if (old_owner.container!=0 && return_cost!=0)
        {
            if (!buy_thing(topic_saler_account,old_owner,return_cost, "topic_return"))
            {
                logErr2("--Error: return credits failded on topic %s %d",__FILE__,__LINE__);
            }

        }
        if (v.size())
        {
            d.dbh->real_queryQ((QUERY)"update topics set disabled='1' where channel=? and disabled='0'"<<channel.container);
        }
        string top=cc->params["topic"];
        if (top.size()>128) top=top.substr(0,128);
        top=str_replace("'","",top);
        top=str_replace("\\\\","",top);

        string cnick;
        {
            PGLR(user_set,u,user_sets.find_by_id(cc->user_id));
            cnick=u->last_nick;
        }
        out_oscar_buffer b;
        b<<channel<<top<<cnick<<time(NULL);
        send_update_g2(channel$topic,b);
        chat_event_CHTOPIC *e=new chat_event_CHTOPIC;
        e->uid=cc->user_id;

        e->channel=channel;
        e->top=top;
        send_chat_event(e,true);
        d.dbh->real_queryQ((QUERY)"insert into topics (channel,topic,current_price,orig_price,owner,last_recalc,disabled,set_time)"
                           "values(?,'?',?,?,?,FROM_UNIXTIME(?),'0',FROM_UNIXTIME(?))"
                           <<channel.container<<top<<new_cost<<new_cost<<cc->user_id.container<<time(NULL)<<time(NULL)
                          );
        m["~result~"]=_MSG("topicchanged");
        old_cost=new_cost;
        {
            PGLR(user_credit,u,user_credits.find_by_id(cc->user_id));
            summa=u->summa;
        }
        topic=top;
        new_cost=old_cost*1.1;
        m["~summa~"]=get_f22(summa);
        m["~cost~"]=get_f22(new_cost);
        m["~topic~"]=topic;

    }
    if (summa<new_cost)
        m["~result~"]=_MSG("notenoughcredits");
    cc->html_out+=make_pair(m,"chat/topic");
}
