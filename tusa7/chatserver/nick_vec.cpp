#include "stdafx.h"
#include <string>
#include "db_var.h"
#include "nick_vec.h"
#include "user.h"
#include "utils.h"
#include "web_tools.h"
#include "DR_types.h"
#include <math.h>
nick_vec::nick_vec() {}
nick_vec::~nick_vec() {}
#ifdef __CLAN

int nick_vec::load_from_db(const string & table_name)
{
    DB_id id;
    id.container=get_db_row_id().as_int();
    string r=clan_data_request(DR_nick_vec,id);
    oscar_buffer bb(r.data(),r.size());
    unpack(bb);
    return 0;
}
#else
int nick_vec::load_from_db(const string & table_name)
{

    unsigned int uid=get_db_row_id().as_int();
    if (uid==0 ) {
        logErr2("uid==0 || uid>UNREG_BASE (%d) %s",uid,"");
        throw cError("if(get_db_row_id().as_int()==0) || uid>UNREG_BASE "+itostring(uid)+" ");
    }

    st_dbh d;
    u_nicks.clear();
    vector<vector<string> >v=d.dbh->execQ((QUERY)"select id,nick,uid,ready_to_sale,cost from nicks where banned=0 and uid=? and id<>0"<<get_db_row_id().as_int());
    for (unsigned i=0;i<v.size();i++)
    {
        if (v[i].size()==5)
        {
            DB_id uid;
            uid.container=atoi(v[i][2]);
            user_nick n(v[i][1],atoi(v[i][0]),uid,atoi(v[i][3]), fabs(atof(v[i][3].c_str())));
            u_nicks.insert(pair<unsigned int, user_nick>(n.id,n));
        }
    }

    return 0;
}
#endif
string update_to_db(const PTR_getter<nick_vec> &__U,const string& table_name)
{
    return "";
}

int srt_nick__(const pair<string,string> &a,const pair<string,string> &b)
{
    return str_nick(a.second)<str_nick(b.second);
}


string build_nicks_select(const PTR_getter<nick_vec> &__N,const string &name,const string defnick,const string &addp)
{
    vector<pair<string,string> >m;
    int def=0;
    PGLR(nick_vec, u,__N);
    for (map<unsigned int,user_nick>::const_iterator i=u->u_nicks.begin();i!=u->u_nicks.end();i++) {
        if (str_nick(defnick)==str_nick(i->second.name)) {
            def=i->second.id;
        }
        m.push_back(pair<string,string> (itostring(i->second.id),i->second.name));


    }
    sort(m.begin(),m.end(),srt_nick__);
    return make_select(name,m,itostring(def),addp);

}
string build_nicks_select(const PTR_getter<nick_vec> &__N,const string &name,int def,const string &addp)
{
    vector< pair<string,string> > m;
    PGLR(nick_vec, u,__N);
    for (map<unsigned int,user_nick>::const_iterator i=u->u_nicks.begin();i!=u->u_nicks.end();i++) {
        m.push_back(pair<string,string> (itostring(i->second.id),i->second.name));
    }
    sort(m.begin(),m.end(),srt_nick__);
    return make_select(name,m,itostring(def),addp);

}
string build_nicks_select(unsigned int uid,const string &name,int def,const string &addp)
{
    return build_nicks_select(nick_vecs.find_by_id(uid),name,def,addp);
}
string build_nicks_select(unsigned int uid,const string &name,const string &defn,const string &addp)
{
    return build_nicks_select(nick_vecs.find_by_id(uid),name,defn,addp);
}

string build_nicks_select(const user_pair& __U,const string &name,int def,const string &addp)
{
    return build_nicks_select(nick_vecs.find_by_id(user$id(__U)),name,def,addp);
}
string build_nicks_select(const user_pair& __U,const string &name,const string &defn,const string &addp)
{
    return build_nicks_select(nick_vecs.find_by_id(user$id(__U)),name,defn,addp);
}
void nick_vec::pack(out_oscar_buffer &b) const
{
    b<<u_nicks;
}
void nick_vec::unpack(oscar_buffer &b)
{
    b>>u_nicks;
}
