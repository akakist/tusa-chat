#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "map"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <errno.h>
#include <map>
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "web_server.h"
#include "message.h"

#include <sys/types.h>
#include <sys/stat.h>
#include "chat_def.h"
#include "_mutex.h"
#include <stdio.h>
#include "errs.h"
#include "utils.h"
#include "M_MAP.h"
#include "file_set.h"
#include "web_tools.h"
#include "web_server_data.h"
#include "web_server.h"
#include "levels.h"
#include "server_config.h"

#include "chat_config.h"
#include <ctype.h>
#include "DR_types.h"
map<string,string> load_m_file(const string &fn);
vector<string> load_l_file(const string &fn);


static map<unsigned int, c_level> levels;
static _mutex levels_Mutex("levels_Mutex");



map<unsigned int, c_level> get_all_levels()
{
    M_LOCK(levels_Mutex);
    return levels;
}
string LEVEL_NAME(unsigned int id,unsigned char gender)
{
    M_LOCK(levels_Mutex);
    if (!levels.count(id)) return "";
    return levels[id].name(gender);

}
static bool is_emptyS(const string &s)
{
    bool ret=true;
    for (unsigned i=0;i<s.size();i++)
    {
        if (!isspace(s[i])) ret=false;
    }
    return ret;
}
void pack_levels(out_oscar_buffer &b)
{
    M_LOCK(levels_Mutex);
    b<<levels;
}
void unpack_levels(oscar_buffer &b)
{
    M_LOCK(levels_Mutex);
    b>>levels;
}
#ifdef __CLAN
bool load_levels(const string &pn)
{

    DB_id v;
    string cr=clan_data_request(DR_load_levels);
    oscar_buffer b(cr.data(),cr.size());

    M_LOCK(levels_Mutex);
    b>>levels;
    return true;
}
#else
bool load_levels(const string &pn)
{
    M_LOCK(levels_Mutex);
    logErr("Loading levels...");
    levels.clear();
    params_map levels_conf;
    levels_conf.clear();
    levels_conf.read(pn);
    map<string,string> c=levels_conf.get_container();
    for (map<string,string>::iterator i=c.begin();i!=c.end();i++) {
        string nn=i->first;
        if (nn.substr(0,1)=="#" ||!nn.size()) continue;
        if (is_emptyS(nn)) continue;
        unsigned int n=atoi(nn);
        map<string,string> params=load_m_file(i->second);
        c_level lev;
        if (levels.find(n)!=levels.end()) lev=levels[n];
        lev.replacements.clear();
        lev.colors.clear();
        lev.id=n;
        lev.quota=atoi(params["quota"]);
        if (lev.quota==0) lev.quota=1;
        lev.max_msg_len=atoi(params["msg_len"]);
        lev._max_nicks_count=atoi(params["nicks_count"]);
        lev.privileges=atoi(params["privileges"]);
        lev.invisibility=atoi(params["invisibility"].c_str())*100;
        lev.levelup_ability=atoi(params["levelup_ability"]);
        lev.leveldown_ability=atoi(params["leveldown_ability"]);
        lev.kick_shield=atoi(params["kick_shield"])*100;
        lev.kick_ability=atoi(params["kick_ability"])*100;

        for (map<string,string>::iterator q=params.begin();q!=params.end();q++) {
            string s=q->first;
            int pz=s.find("@",0);
            if (pz!=-1) {
                s=s.substr(pz+1,s.size()-pz-1);
            }
            if (s=="names") {
                vector<string> v=splitTOK(",",q->second);
                if (!v.size()) {
                    logErr("---Error: no names for level %d defined. ignoring...",lev.id);
                    continue;
                }
                for (unsigned j=v.size();j<=2;j++) v.push_back(v[0]);
                lev.names=v;
            }
            if (s=="replacements") {
                vector<string> repls=load_l_file(q->second);
                for (unsigned int z=0;z<repls.size();z++) {
                    string k=repls[z];
                    int ppz=k.find(" ");
                    if (ppz==-1) {
                        logErr("--Error: load_levels: replacements: syntax error in %s line %d",q->second.c_str(),z);
                        continue;
                    }
                    string key=k.substr(0,ppz);
                    string val=k.substr(ppz+1,k.size()-ppz-1);
                    lev.replacements[key]=val;
                }
            }
            if (s=="color_packs")
            {
                vector<string> c=splitTOK(",",q->second);
                for (unsigned i=0;i<c.size();i++)
                {
                    lev.colors.insert(atoi(c[i]));
                }
            }
        }
        levels[n]=lev;
    }
    return true;
}
#endif
map<unsigned int, c_level> LEVELS_GET()
{
    M_LOCK(levels_Mutex);
    return levels;
}

c_level LEVELS(unsigned int n)
{
    M_LOCK(levels_Mutex);
    c_level l;
    if (levels.find(n)!=levels.end()) {
        l=levels[n];
    } else {
        throw cError("--Error: level n="+itostring(n)+" not found!");
    }
    return l;
}

string c_level::name(unsigned int g)
{

    if (g<names.size())
        return names[g];
    else
        throw cError("level name  has (i->sec.size()<=gender) n="+itostring(id)+" gender="+itostring(g));
    return "";
}

void c_level::assign_names(const vector<string>& v)
{
    names=v;
}

void c_level::add_names(const vector<string> &v)
{
    names=v;
}

void c_level::print()
{
    logErr("Loaded level %d: quota=%d nicks_count=%d message_len=%d invisibility=%2.2f kick_shield=%2.2f kick_ability=%2.2f levelup_ability=%d leveldown_ability=%d",id,quota,_max_nicks_count,max_msg_len,invisibility,kick_shield,kick_ability,levelup_ability,leveldown_ability);
    string ln;
    for (unsigned int j=0;j<names.size();j++) {
        ln+=names[j]+" ";
    }
    string cl;
    {
        for (set<unsigned int>::iterator i=colors.begin();i!=colors.end();i++) {
            cl+=itostring(*i)+" ";
        }
    }
    logErr("\t level names: %s",ln.c_str());
    logErr("\t color: %s",cl.c_str());
}
oscar_buffer& operator>>(oscar_buffer & b, c_level   &c)
{
    b>>c.names;

    b>>c.quota;
    b>>c._max_nicks_count;
    b>>c.max_msg_len;
    b>>c.privileges;
    b>>c.replacements;
    b>>c.colors;
    b>>c.id;
    b>>c.levelup_ability;
    b>>c.leveldown_ability;
    b>>c.invisibility;
    b>>c.kick_shield;
    b>>c.kick_ability;
    return b;

}
out_oscar_buffer& operator<<(out_oscar_buffer & b, const c_level & c)
{
    b<<c.names;

    b<<c.quota;
    b<<c._max_nicks_count;
    b<<c.max_msg_len;
    b<<c.privileges;
    b<<c.replacements;
    b<<c.colors;
    b<<c.id;
    b<<c.levelup_ability;
    b<<c.leveldown_ability;
    b<<c.invisibility;
    b<<c.kick_shield;
    b<<c.kick_ability;
    return b;
}
