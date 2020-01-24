#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <map>
#include "mysql_extens.h"
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "web_server.h"
#include "message.h"
#include "chat_def.h"
#include "register.h"

#include <algorithm>
#include "web_server_data.h"
#include "file_set.h"
#include "copy_file.h"

#include "channels.h"
#include "server_config.h"
#include "app_def.h"
#include "user_set.h"
#include "web_tools.h"
#include "cs_conn_data.h"
#include "html_out.h"

void url_admin_userlist(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);


    if (cc->sub_level<am_killer) {
        return;
    }
    map<string,hstring> m;
    string srt=cc->params["sort"];
    m["~msg~"]=cc->params["msg"];
    m["~sort~"]=srt;
    if (srt=="") {
        m["~sort~"]="nick";
        srt="nick";
    }
    vector<CH_id> chs=chat_channels.keys();
    if (!chs.size())return;
    CH_id ch=*chs.begin();
    if (cc->params.count("c"))
    {
        ch.container=atoi(cc->params["c"].c_str());
    }
    map<string,string>mc;
    for (unsigned int i=0;i<chs.size();i++) {
        __CH_LOCK(chat_channels[chs[i]]);
        mc[itostring(chs[i].container)]=CH->cd.name();

    }
    m["~channels~"]=make_select("c",mc,itostring(ch.container)," onchange='submit();' class=bsel");
    m["~c~"]=itostring(ch.container);

    int your_levelsub_levels=cc->sub_level;
    DB_id your_id=cc->user_id;

//    bool have_inv=has_inv(__U);
    int cnt=0;

    map<string, vector<PTR_getter<chat_user> > > map_users;

    vector< PTR_getter<chat_user> > vv=local_users.values();
    for (unsigned int i=0;i<vv.size();i++) {
        if (!vv[i]) continue;
        user_pair __Z(vv[i]);

        {
            __ZC_LOCK;
            if (z->erased) continue;
        }
        if (!I_can_see(__UU,vv[i])) continue;


        if (srt=="nick") map_users[str_nick(GET_CNICK(__Z))].push_back(vv[i]);
        else if (srt=="login") map_users[user$login(__Z)].push_back(vv[i]);
        else if (srt=="ip") {
            __ZC_LOCK;
            if (z->user_type==TYPE_WWW&& z->www_proxy_ip.size()) {
                map_users[z->www_proxy_ip].push_back(vv[i]);
            } else {
                map_users[z->cu_ip].push_back(vv[i]);
            }
        }
        else if (srt=="proxy") {
            __ZC_LOCK;
            if (z->user_type==TYPE_WWW&&z->www_proxy_ip.size()) {
                map_users[z->cu_ip].push_back(vv[i]);
            } else {
                map_users[""].push_back(vv[i]);
            }
        }
        else if (srt=="type")
        {
            __ZC_LOCK;
            map_users[itostring(z->user_type)].push_back(vv[i]);
        }
        else
            map_users[str_nick(GET_CNICK(__Z))].push_back(vv[i]);


    }
    bool one_channel=chat_channels.keys().size()==1;

    string data;
    int idx=0;
    for (typeof(map_users.begin())i=map_users.begin();i!=map_users.end();i++)
    {
        for (unsigned j=0;j<i->second.size();j++)
        {
            PTR_getter<chat_user> __ZZ=i->second[j];
            if (!__ZZ)  continue;

            if (!I_can_see(__UU,__ZZ)) continue;

            {
                PGLR(chat_user,z,__ZZ);
                if (!z->cstate.channel.count(ch)) continue;
            }
            user_pair __Z(__ZZ);
            int this_levelsub_levels;
//            bool zis_inv=is_inv(__Z);
            {
                __ZC_LOCK;
                if (z->erased) continue;

            }
            this_levelsub_levels=user$level(__Z)/sub_levels;
            cnt++;
            string nick;
            string login;
            string room;
            string ip;
            string pip;
            data+="<tr>";
            idx++;
            data+="<td>"+itostring(idx)+"</td>";
            if (user$id(__Z)==your_id || this_levelsub_levels>=your_levelsub_levels || your_levelsub_levels<am_guard) {
                nick=GET_CNICK(__Z);
            } else {
                nick="<a href='#' class=nick onclick=\"return dbn('"+GET_CNICK(__Z)+"',"+itostring(user$id(__Z).container)+")\">"+GET_CNICK(__Z)+"</a>";
            }
            //login
            if (your_levelsub_levels>=am_guard) {
                if (user$id(__Z)==your_id || this_levelsub_levels>=your_levelsub_levels) {
                    login=user$login(__Z);
                } else {
                    login="<a href='#' class=nick onclick=\"return dbl('"+string(user$login(__Z))+"',"+itostring(user$id(__Z).container)+")\">"+string(user$login(__Z))+"</a>";
                }
            }
            {
                set<CH_id> ch=user$channel(__Z);
                {
                    PGLR(chat_user,z,__ZZ);
                    if (z->user_type==TYPE_WWW) room+="www";
                    if (z->user_type==TYPE_IRC) room+="irc";
                }

            }
            //ip
            if (your_levelsub_levels>=am_guard) {
                string zz;
                zz=user$ip(__Z);

                {
                    __ZC_LOCK;
                    if (z->user_type==TYPE_WWW)
                    {
                        if (z->www_proxy_ip.size()) zz=z->www_proxy_ip;
                    }
                }

                if (your_levelsub_levels<=am_guard) zz=zz.substr(0,zz.find(".",0))+".???.???.???";
                if (your_levelsub_levels>am_guard) {
                    ip="<a href=\"#\" onclick=\"return ip_inf('"+zz+"')\"><img src='/pics/stat.gif' border=0 alt='IP info' width=6 height=11></a>&nbsp;";
                }
                ip+="<a href=\"#\" class=nick onclick=\"return dbi('"+zz+"',"+itostring(user$id(__Z).container)+")\">"+zz+"</a>";

            }
            //proxy ip
            {
                string zz;
                //if(is_www_user(__Z))
                {
                    __ZC_LOCK;
                    if (z->user_type==TYPE_WWW)
                    {
                        zz=z->www_proxy_ip;
                        if (zz.size()) zz=z->cu_ip;
                    }
                }
                if (zz!="") {
                    if (your_levelsub_levels<=am_guard) zz=zz.substr(0,zz.find(".", 0))+".???.???.???";
                    if (your_levelsub_levels>am_guard) {
                        pip="<a href=\"#\" onclick=\"return ip_inf('"+zz+"')\"><img src='/pics/stat.gif' border=0 alt='IP info' width=6 height=11></a>&nbsp;";
                    }
                    pip+="<a href=\"#\" class=nick onclick=\"return dbp('"+zz+"',"+itostring(user$id(__Z).container)+")\">"+zz+"</a>";
                }
            }
            data+="<td>"+nick+"</td><td>"+login+"</td>";
            if (!one_channel) data+="<td>"+room+"</td>";
            data+="<td>"+ip+"</td><td>"+pip+"</td>";
            if (user$id(__Z)==your_id || this_levelsub_levels>=your_levelsub_levels) {
                data+="<td></td>";
            } else {
                data+="<td><a href=\"#\" onclick=\"return dk('"+GET_CNICK(__Z)+"',"+itostring(user$id(__Z).container)+")\"><img src='/pics/kick.gif' border=0 width=16 height=16></a></td>";
            }
            data+="</tr>\r\n";

        }
    }


    if (one_channel) {
        m["~schannel~"]="<!--";
        m["~eschannel~"]="-->";
    } else {
        m["~schannel~"]="";
        m["~eschannel~"]="";
    }

    m["~data~"]=data;
    m["~cnt~"]=itostring(cnt);

    cc->html_out=make_pair(m,"admin/userlist");
}
