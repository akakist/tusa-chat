#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

#include "_mutex.h"
#include <list>
#include "mutex_inspector.h"
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
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
#include "levels.h"
#include "app_def.h"
#include "chat_config.h"
#include "web_tools.h"
#include "notes.h"
#include "update_cmd.h"

#include "chat_globals.h"
#include "app_con.h"
#ifdef __WITH_LICENSE
#include "license.h"
#endif

////#include "web_cache.h"
DB_id get_uid_by_nick(const string& nick);
unsigned int get_nid_by_nick(const string& nick);



void url_vote_info(const PTR_getter<chat_user> &__U,app_connection*cc);
void check_notes_config(const DB_id& uid);
void send_system_note(const DB_id& uid,const string &subj,const string& msg);

static void send_note_to_user(double yes,double no,double all,const string &level,const DB_id& uid,const string &tonick,const unsigned int to_nick_id,const int &vid)
{
    MUTEX_INSPECTOR;

    //st_sqls sql;


    check_notes_config(uid);

    unsigned char sort;
    bool sort_desc;
    {
        PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(uid)));
		if(u)
		{
			sort=u->notes_sort;
			sort_desc=u->notes_sort_desc;
		}
    }


    st_dbh d;
    if (1){
        string subj=_MSG("vote_ended_subj");
        map<string,string> z;
        z["~yes~"]=fmt_d("%3.1f",yes);
        z["~no~"]=fmt_d("%3.1f",no);
        z["~total~"]=fmt_d("%3.1f",all);
        z["~level~"]=level;
        string msg;
        string key;
        if (yes>=chat_config.vote_yes_percent.get()){
            key="vote/vote_ended_yes";
        }else{
            key="vote/vote_ended_no";
        }

        string ms;
        vector< vector<string> > q=d.dbh->execQ((QUERY)"select from_nick,ip,UNIX_TIMESTAMP(add_date),msg,show_nick from grant_messages where gid=? order by add_date"<<vid);
        for (unsigned int i=0;i<q.size();i++){
            if (q[i].size()!=5){throw cError("select failed. size different"+_DMI());}
            map<string,string> a;
            if (q[i][4]=="1"){
                a["~nick~"]="<b>"+q[i][0]+"</b> ";
            }else{
                a["~nick~"]="";
            }
            a["~date~"]=datetime2num(atoi(q[i][2]));
            a["~msg~"]=q[i][3];
            ms+=RVfiles(a,"vote/info_msg");
        }
        z["~messages~"]=ms;

        msg=RVfiles(z,key.c_str());

        send_system_note(uid,subj,msg);

    }
}

static void send_msg_to_user(app_connection *cc,const DB_id& id)
{
    vector<PTR_getter<chat_user> >__ZZ=local_users.get$(id);
    for (unsigned i=0;i<__ZZ.size();i++)
        if (__ZZ[i]){
            user_pair __Z(__ZZ[i]);
            send_syspriv_msg(__Z,_MSG("voteended"));

        }
}
int sortstring(const string& a,const string& b)
{
    return a<b;
}
void url_vote(const PTR_getter<chat_user> &__UU,app_connection*cc)
{
    MUTEX_INSPECTOR;
    LICENSE_CK(15);
	st_update stu;
	st_dbh d;
    switch_cc_ret("info",url_vote_info(__UU,cc));
    map<string,string> m;
    m["~msg~"]="";
    int balls=0;
    DB_id auid;CONTAINER(auid)=0;
    bool may_add=false;
    bool admin=false;
    string cnick;
    bool allow_tags=false;
    if (__UU)
    {user_pair __U(__UU);
        cnick=GET_CNICK(__U);
        {
			balls=atoi(d.dbh->select_1Q((QUERY)"select vote_balls from tbl_users where id="<<CONTAINER(user$id(__U))));
            
            allow_tags=user__privileges(__U,"$tags");
            may_add=user$level(__U)/sub_levels>=am_admin;
            if (user__privileges(__U,"$vote")) admin=true;
            if (!may_add && admin) may_add=true;
            auid=user$id(__UU);
            //login=user$login(__U);

        }
    if (balls==0){may_add=false;}
    }

    if (admin && cc->params["removeold"]=="1"){
        time_t t=time(NULL)-345600;	//older 4 days
        st_dbh d;
        vector<string> v=d.dbh->select_1_columnQ((QUERY)"select id from grant_vote where status!=0 and add_date<=FROM_UNIXTIME(?)"<<t);
        for (unsigned int i=0;i<v.size();i++){
            d.dbh->real_queryQ((QUERY)"delete from grant_agrees where gid=?"<<v[i]);
            d.dbh->real_queryQ((QUERY)"delete from grant_messages where gid=?"<<v[i]);
            d.dbh->real_queryQ((QUERY)"delete from grant_vote where id=?"<<v[i]);
            d.dbh->real_queryQ((QUERY)"delete from grant_readden where gid=?"<<v[i]);
        }
        cc->redirect("/vote.tse");
        return;
    }

    if (may_add && cc->params["addnick"]!=""){	//add person
		user_pair __U(__UU);
        string n=remove_spaces(cc->params["addnick"]);
        DB_id uid=get_uid_by_nick(n);
        ;
        st_dbh d;
        if (CONTAINER(uid)==0){
            m["~msg~"]=_MSG("thisnicknotexists");
        }else{
            //uid=v[0];
            vector<string> v=d.dbh->select_1_rowQ((QUERY)"select id from grant_vote where uid=?"<<CONTAINER(uid));
            if (v.size()>0){
                m["~msg~"]=_MSG("nickalreadyinvote");
            }else{
                int ll=0;
                {
                    PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(uid)));
					if(u)
					{
						ll=u->level;
					}
                }
                int l=atoi(cc->params["level"]);


                //int ll=atoi(z[0]);

                if (l<am_newuser*sub_levels+sub_levels || l>=am_admin*sub_levels+sub_levels){l=am_newuser*sub_levels;}
                if (l==ll){
                    m["~msg~"]=_MSG("userhasthislevel");
                }else{
                    if (ll/sub_levels>user$level(__U)/sub_levels){
                        m["~msg~"]=_MSG("cantaddtovoting");
                    }else{
                        d.dbh->real_queryQ((QUERY)"insert into grant_vote (nick,llevel,nlevel,uid,add_date,add_by,status)"
                                           " values('?',?,?,?,NOW(),?,0)"
                                           <<n<<ll<<l<<CONTAINER(uid)<<CONTAINER(auid)
                                          );
                        DB_id gid;CONTAINER(gid)=0;
                        CONTAINER(gid)=atoi(d.dbh->select_1("select LAST_INSERT_ID() from grant_vote"));
                        d.dbh->real_queryQ((QUERY)"insert into grant_agrees (gid,uid,yes,no) values(?,0,0,0)"<<CONTAINER(gid));
                        if (cc->params["descr"]!=""){
                            string dd=cc->params["descr"];
                            if (!allow_tags) dd=remove_tags(dd);
                            dd=str_replace("\r\n","<br>",dd);
                            dd=replace_links(dd);
                            d.dbh->real_queryQ((QUERY)"insert into grant_messages (gid,from_nick,ip,add_date,msg)"
                                               " values(?,'?','?',NOW(),'?')"
                                               <<CONTAINER(gid)<<cnick<<cc->peer_ipaddress<<dd
                                              );
                        }
                        cc->redirect("/vote.tse");
                    }

                }
            }
        }
    }

    double all_balls;
    {
        st_dbh d;
        all_balls=atoi(d.dbh->select_1("select sum(vote_balls) from tbl_users"));
    }
    double all_balls_100=all_balls / 100;

    if (balls>0 && (cc->params["a"]=="agree" || cc->params["a"]=="disagree")){	//voting
        st_dbh d;
        vector<string> z=d.dbh->select_1_rowQ((QUERY)"select id from grant_agrees where gid='?' and uid=?"<<atoi(cc->params["id"])<<CONTAINER(auid));
        if (z.size()>0){
            m["~msg~"]=_MSG("alreadyvoted");
        }else{
            int b=balls;
            int bb=balls;
            int id=atoi(cc->params["id"]);
            z=d.dbh->select_1_rowQ((QUERY)"select id from grant_vote where id='?'"<<id);
            if (z.size()>0){
                if (cc->params["a"]=="disagree"){b=0;}
                if (cc->params["a"]=="agree"){bb=0;}
                d.dbh->real_queryQ((QUERY)"insert into grant_agrees (gid,uid,yes,no)"
                                   "values('?','?','?','?')"
                                   <<id<<CONTAINER(auid)<<b<<bb
                                  );
                vector<string> e=d.dbh->select_1_rowQ((QUERY)"select sum(yes),sum(no) from grant_agrees where gid='?'"<<id);
                if (e.size()!=2){throw cError("select failed. size different"+_DMI());}
                double e1=atoi(e[0]);
                double e2=atoi(e[1]);
                double ee=e1/all_balls_100;
                double eall=(e1+e2)/all_balls_100;
                double yes=e1/all_balls_100;
                double no=e2/all_balls_100;
                if (yes>=chat_config.vote_yes_percent.get() || eall>=100 || no>=50){
                    e=d.dbh->select_1_rowQ((QUERY)"select nlevel,uid,nick from grant_vote where id='?'"<<id);
                    if (e.size()!=3){throw cError("select failed."+_DMI());}
                    unsigned int nid=get_nid_by_nick(e[2]);
                    if (ee>=chat_config.vote_yes_percent.get()){


                        d.dbh->real_queryQ((QUERY)"update grant_vote set status=1 where id='?'"<<id);
                        {
                            PGLW(user_profile, z,user$profiles.FindByID(atoi(e[1])));
							z->level=__LEVELS(atoi(e[0])).id;
							d.dbh->real_queryQ((QUERY)"update tbl_users set level='?' where id='?'"<<z->level<<e[1]);
							d.dbh->real_queryQ((QUERY)"insert into ext_events (event) values ('flush tbl_users ?')"<<e[1]);
							//__send_update_d3(user_profile$level$3,atoi(e[1]),z->level);
						}
                        unsigned int zid=atoi(e[1]);
                    }else{
                        d.dbh->real_queryQ((QUERY)"update grant_vote set status=2 where id='?'"<<id);
                    }
                    DB_id zid;CONTAINER(zid)=0;
                    CONTAINER(zid)=atoi(e[1]);
                    send_note_to_user(e1/all_balls_100,e2/all_balls_100,eall,LEVEL_NAME(atoi(e[0]),0),zid,MES(e[2]),nid,id);

                    send_msg_to_user(cc,zid);
                }
                cc->redirect("/vote.tse");
                return;
            }else{
                m["~msg~"]=_MSG("rec_not_found");
            }
        }
    }

    if (balls>0){
        map<string,string>K;
        m["~mainrow~"]=RVfiles(K,"vote/main_row_adm");
    }else{
        map<string,string>K;
        m["~mainrow~"]=RVfiles(K,"vote/main_row");
    }
//    st_dbh d;
    vector< vector<string> > v=d.dbh->exec(
                                   "select grant_vote.nick,"
                                   "grant_vote.llevel,"
                                   "grant_vote.nlevel,"
                                   "grant_vote.uid,"
                                   "UNIX_TIMESTAMP(grant_vote.add_date),"
                                   "grant_vote.add_by,"
                                   "grant_vote.status,"
                                   "grant_vote.id,"
                                   "sum(grant_agrees.yes),"
                                   "sum(grant_agrees.no) "
                                   "from grant_vote,grant_agrees where grant_agrees.gid=grant_vote.id group by 1 order by add_date desc");

    string row;
    for (unsigned int i=0;i<v.size();i++){
        if (v[i].size()!=10){throw cError("select failed. size different."+_DMI());}
        double yes=atoi(v[i][8]);
        double no=atoi(v[i][9]);
        double yp=yes / all_balls_100;
        double np=no / all_balls_100;
        map<string,string> q;
        int ll=atoi(v[i][1]);
        int nl=atoi(v[i][2]);
        int st=atoi(v[i][6]);
        q["~nick~"]=v[i][0];
        q["~llevel~"]=LEVEL_NAME(ll,0);
        q["~nlevel~"]=LEVEL_NAME(nl,0);
        q["~date~"]=date2num(atoi(v[i][4]));
        if (st==0){
            q["~percent~"]="<td class=trd colspan=2 align=center><font class=vnf>"+fmt_d("%3.1f%%",yp+np)+"</td>";
        }else{
            q["~percent~"]="<td class=trd><font class=vyes>"+fmt_d("%3.1f%%",yp)+"</td><td class=trd><font class=vno>"+fmt_d("%3.1f%%",np)+"</td>";
        }

        if (st==0){
            q["~status~"]="/pics/processing.gif";
        }
        if (st==1){
            q["~status~"]="/pics/granted.gif";
        }
        if (st==2){
            q["~status~"]="/pics/del.gif";
        }
        if (balls>0){
            vector<string> w=d.dbh->select_1_rowQ((QUERY)"select yes from grant_agrees where gid=? and uid=?"<<v[i][7]<<CONTAINER(auid));
            bool readden=atoi(d.dbh->select_1Q((QUERY)"select readden from grant_readden where gid=? and uid=?"<<v[i][7]<<CONTAINER(auid)));
            bool voted=w.size()>0;
            string inf;
            if (readden){
                inf="&nbsp;<a href=\"#\" onclick=\"return opwin('/vote.tse/info.tse?id="+v[i][7]+"',510,500)\"><img src=\"/pics/hint16.gif\" width=16 height=16 border=0 name='i"+v[i][7]+"'></a>";
            }else{
                inf="&nbsp;<a href=\"#\" onclick=\"return opwin('/vote.tse/info.tse?id="+v[i][7]+"',510,500)\"><img src=\"/pics/hint16y.gif\" width=16 height=16 border=0 name='i"+v[i][7]+"'></a>";
            }
            if (voted){
                if (w[0]!="0"){
                    q["~vote~"]=_MSG("voteagree")+inf;
                }else{
                    q["~vote~"]=_MSG("votedisagree")+inf;
                }
            }else{
                if (st!=0){
                    q["~vote~"]=inf;
                }else{
                    q["~vote~"]="<a href=\"/vote.tse?a=agree&id="+v[i][7]+"\" onclick=\"return confirm('"+_MSG("voteagree")+"?')\"><img src=\"/pics/granted.gif\" border=0 width=16 height=16 alt=\""+_MSG("voteagree")+"\"></a>&nbsp;"
                                "<a href=\"/vote.tse?a=disagree&id="+v[i][7]+"\" onclick=\"return confirm('"+_MSG("votedisagree")+"?')\"><img src=\"/pics/del.gif\" border=0 width=16 height=16 alt=\""+_MSG("votedisagree")+"\"></a>"+inf;
                }
            }
            row+=RVfiles(q,"vote/row_adm");
        }else{
            row+=RVfiles(q,"vote/row");
        }
    }

    if (v.size()==0){
        map<string,string> K;
        m["~rows~"]=RVfiles(K,"vote/row_empty");
    }else{
        m["~rows~"]=row;
    }
    if (may_add){
        map<string,string> q;
        string s="<SELECT name=level>";
        map<unsigned int,c_level> lvl=LEVELS_GET();

        for (map<unsigned int,c_level>::const_iterator i=lvl.begin();i!=lvl.end();i++){
            if (i->first<am_newuser*sub_levels+sub_levels || i->first>=am_admin*sub_levels+sub_levels) continue;
            s+="<option value="+itostring(i->first)+">"+i->second.name(0)+"\r\n";
        }
        s+="</SELECT>";
        q["~levels~"]=s;
        m["~addperson~"]=RVfiles(q,"vote/add");
    }else{
        m["~addperson~"]="";
    }
    if (admin){
        m["~foradm~"]="<a href=\"?removeold=1\">"+_MSG("removeold")+"</a>";
    }else{
        m["~foradm~"]="";
    }
    cc->html_out+=cc->rvfiles(m,"vote/vote");
}

void url_vote_info(const PTR_getter<chat_user> &__UU,app_connection*cc)
{
    LICENSE_CK(12);
    MUTEX_INSPECTOR;
	st_update stu;
    if (!__UU) return;
    DB_id cc_user_id=user$id(__UU);

    map<string,string> m;
    string fnick;
    string flogin;
    string fullname;
    bool admin=false;
    bool allow_tags=false;
    if (__UU){
        user_pair __U(__UU);
        fnick=GET_CNICK(__U);
        int vb;
	st_dbh d;
		vb=atoi(d.dbh->select_1Q((QUERY)"select vote_balls from tbl_users where id="<<CONTAINER(user$id(__U))));
        

        if (vb<=0){
            MUTEX_INSPECTOR;
            cc->html_out="";
            return;
        }
        flogin=user$login(__U);
        admin=user__privileges(__U,"$vote");
        fullname=fnick+" ("+flogin+")";
        allow_tags=user__privileges(__U,"$tags");
    }
    int id=atoi(cc->params["id"]);
    m["~msg~"]="";
    st_dbh d;
    vector<string> vv=d.dbh->select_1_rowQ((QUERY)
                                           "select "
                                           "grant_vote.nick,"
                                           "grant_vote.uid,"
                                           "grant_vote.add_by,"
                                           "grant_vote.status,"
                                           "tbl_users.kicked_count,"
                                           "tbl_users.stat_m_count,"
                                           "tbl_users.stat_t_count,"
                                           "tbl_users.stat_v_count,"
                                           "UNIX_TIMESTAMP(tbl_users.reg_date) "
                                           "from grant_vote, tbl_users "
                                           "where grant_vote.id='?' "
                                           "and tbl_users.id=grant_vote.uid "<<id);
    if (vv.size()<=0){
        MUTEX_INSPECTOR;
        cc->html_out+="<script>alert('"+_MSG("rec_not_found")+"');window.close();</script>\n";
        return;
    }
    if (vv.size()!=9){throw cError("select failed. size different"+_DMI());}
    string add_by;
    {
        MUTEX_INSPECTOR;
        PGLR(user_profile,u,user$profiles.FindByID(atoi(vv[2])));
		if(u)
		{
			add_by=u->login;
		}
    }

    string nick=vv[0];
    DB_id uid;CONTAINER(uid)=0;CONTAINER(uid)=atoi(vv[1]);
    int status=atoi(vv[3]);
    int st=atoi(d.dbh->select_1Q((QUERY)"select status from grant_vote where id=?"<<id));
    if (admin && cc->params["rmvote"]=="1"){
        MUTEX_INSPECTOR;
        d.dbh->real_queryQ((QUERY)"delete from grant_agrees where gid=?"<<id);
        d.dbh->real_queryQ((QUERY)"delete from grant_vote where id=?"<<id);
        d.dbh->real_queryQ((QUERY)"delete from grant_messages where gid=?"<<id);
        d.dbh->real_queryQ((QUERY)"delete from grant_readden where gid=?"<<id);
        cc->html_out+=RVfiles("scripts/open_vote");
        return;
    }
    if (admin && cc->params["endvote"]=="1" && st==0){
        MUTEX_INSPECTOR;
        int all_balls=atoi(d.dbh->select_1("select sum(vote_balls) from tbl_users"));
        double all_balls_100=all_balls / 100;
        vector<string> e=d.dbh->select_1_rowQ((QUERY)"select sum(yes),sum(no) from grant_agrees where gid='?'"<<id);
        if (e.size()!=2) throw cError("select failed. size different"+_DMI());
        int e1=atoi(e[0]);
        int e2=atoi(e[1]);
        double ee=e1/all_balls_100;
        double eall=(e1+e2)/all_balls_100;
        if (eall>=50){
            e=d.dbh->select_1_rowQ((QUERY)"select nlevel,uid,nick from grant_vote where id='?'"<<id);
            if (e.size()!=3) throw cError("select failed."+_DMI());
            unsigned int nid=get_nid_by_nick(e[2]);
            if (ee>=chat_config.vote_yes_percent.get()){
                MUTEX_INSPECTOR;

                d.dbh->real_queryQ((QUERY)"update grant_vote set status=1 where id='?'"<<id);
                c_level lv=__LEVELS(atoi(e[0]));
                {
                    MUTEX_INSPECTOR;
                    PGLW(user_profile, z,user$profiles.FindByID(atoi(e[1])));
					z->level=lv.id;
					d.dbh->real_queryQ((QUERY)"update tbl_users set level='?' where id='?'"<<z->level<<e[1]);
					d.dbh->real_queryQ((QUERY)"insert into ext_events (event) values ('flush tbl_users ?')"<<e[1]);
					//__send_update_d3(user_profile$level$3,atoi(e[1]),z->level);
				}
                unsigned int zid=atoi(e[1]);
            }else{
                MUTEX_INSPECTOR;
                d.dbh->real_queryQ((QUERY)"update grant_vote set status=2 where id='?'"<<id);
            }

            DB_id zid;CONTAINER(zid)=0;
            CONTAINER(zid)=atoi(e[1]);
            send_note_to_user(e1/all_balls_100,e2/all_balls_100,eall,LEVEL_NAME(atoi(e[0]),0),zid,MES(e[2]),nid,id);
            send_msg_to_user(cc,zid);
        }else{
            MUTEX_INSPECTOR;
            m["~msg~"]="<script>alert('"+_MSG("vote50")+"');</script>\n";
        }
        cc->redirect("/vote.tse/info.tse?id="+itostring(id));
    }

    if (cc->params["addmsg"]=="1"){
        MUTEX_INSPECTOR;
        string s=cc->params["msg"];
        bool show_nick=strupper(cc->params["show_nick"])=="ON";
        if (s.size()>2048){s=s.substr(0,2048);}
        if (!allow_tags) s=remove_tags(s);
        s=remove_maty(s);
        s=replace_links(s);
        s=str_replace("\r\n","<br>",s);
        d.dbh->real_queryQ((QUERY)"insert into grant_messages (gid,from_nick,ip,add_date,msg,show_nick)"
                           " values(?,'?','?',NOW(),'?',?)"
                           <<id<<fnick<<cc->peer_ipaddress<<s<<show_nick
                          );
        d.dbh->real_queryQ((QUERY)"delete from grant_readden where gid=?"<<id);
        cc->redirect("/vote.tse/info.tse?id="+itostring(id));
        return;
    }

    if (admin){
        MUTEX_INSPECTOR;
        vector<string> q;
        {
            MUTEX_INSPECTOR;
            PGLR(nick_vec,n,nick_vecs.find_by_id_create(CONTAINER(uid)));
            for (map<unsigned int,user_nick>::const_iterator i=n->u_nicks.begin();i!=n->u_nicks.end();i++)
            {
                MUTEX_INSPECTOR;
                q.push_back(i->second.name);
            }
        }
        nick=join(", ",q);
    }
    double all_balls=atoi(d.dbh->select_1("select sum(vote_balls) from tbl_users"));
    double all_balls_100=all_balls/100;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)"select sum(yes),sum(no) from grant_agrees where gid=?"<<id);
    if (v.size()!=2){throw cError("select failed. size different"+_DMI());}
    double yes=atoi(v[0]);
    double no=atoi(v[1]);
    double yesp=yes/all_balls_100;
    double nop=no/all_balls_100;

    m["~nick~"]=nick;
    m["~msgcnt~"]=vv[5];
    m["~regdate~"]=date2rus(atoi(vv[8]));
    m["~timecnt~"]=make_time(atoi(vv[6]));
    m["~viscnt~"]=vv[7];
    m["~addby~"]=add_by;
    m["~kickedcnt~"]=vv[4];
    if (atoi(vv[6])<3600){
        m["~mperh~"]="N/A";
    }else{
        m["~mperh~"]=itostring( atoi(vv[5])/ (atoi(vv[6])/3600) );
    }
    if (!admin){
        MUTEX_INSPECTOR;
        if (status==0){
            m["~yes~"]="?";
            m["~no~"]="?";
        }else{
            m["~yes~"]=fmt_d("%3.1f%%",yesp);
            m["~no~"]=fmt_d("%3.1f%%",nop);
        }
        m["~all~"]=fmt_d("%3.1f%%",yesp+nop);
        m["~sadm~"]="";
    }else{
        MUTEX_INSPECTOR;

        vector<string> __wy=d.dbh->select_1_columnQ((QUERY)"select uid from grant_agrees where no=0 and gid=?"<<id);
        set<string> wy;
        for (unsigned i=0;i<__wy.size();i++)
        {
            MUTEX_INSPECTOR;
            if (atoi(__wy[i])){
                PGLR(user_profile,u,user$profiles.FindByID(atoi(__wy[i])));
				if(u)
				{
					wy.insert(u->login);
				}
            }
        }
        vector<string> __wn=d.dbh->select_1_columnQ((QUERY)"select uid from grant_agrees where yes=0 and gid=?"<<id);
        set<string> wn;
        for (unsigned i=0;i<__wn.size();i++)
        {
            MUTEX_INSPECTOR;
            if (atoi(__wn[i])){
                PGLR(user_profile,u,user$profiles.FindByID(atoi(__wn[i])));
				if(u)
				{
					wn.insert(u->login);
				}
            }
        }
        vector<string> __wall=d.dbh->select_1_columnQ((QUERY)"select id from tbl_users where vote_balls>0");
        set<string> wall;
        for (unsigned i=0;i<__wall.size();i++)
        {
            MUTEX_INSPECTOR;
            if (atoi(__wall[i])){
                PGLR(user_profile,u,user$profiles.FindByID(atoi(__wall[i])));
				if(u)
				{
					wall.insert(u->login);
				}
            }
        }

        vector<string> __wvoted=d.dbh->select_1_columnQ((QUERY)"select uid from grant_agrees where gid=?"<<id);
        set<string> wvoted;
        for (unsigned i=0;i<__wvoted.size();i++)
        {
            MUTEX_INSPECTOR;
            if (atoi(__wvoted[i])){
                PGLR(user_profile,u,user$profiles.FindByID(atoi(__wvoted[i])));
				if(u)
				{
					wvoted.insert(u->login);
				}
            }
        }
        string y=join(", ",wy);
        string n=join(", ",wn);
        string a;
        m["~yes~"]=y+" ("+fmt_d("%3.1f%%)",yesp);
        m["~no~"]=n+" ("+fmt_d("%3.1f%%)",nop);
        if (y!=""){
            a=y;
        }
        if (n!=""){
            if (a!=""){a+=", ";}
            a+=n;
        }
        m["~all~"]=a+" ("+fmt_d("%3.1f%%)",yesp+nop);
        vector<string> nv;
        for (set<string>::const_iterator i=wall.begin();i!=wall.end();i++){
            MUTEX_INSPECTOR;
            bool find=false;
            if (!wvoted.count(*i))
                nv.push_back(*i);
        }
        m["~sadm~"]="<tr><td>"+_MSG("notvoted")+"</td><td><b>"+join(", ",nv)+"</td></tr>";
    }
    if (admin){
        m["~rmvote~"]="<a href=\"?id="+itostring(id)+"&rmvote=1\">"+_MSG("remove2")+"</a>";
    }else{
        m["~rmvote~"]="";
    }
    if (admin && st==0){
        MUTEX_INSPECTOR;
        string r=m["~rmvote~"];
        if (r.size()) r+="<br>\r\n";
        r+="<a href=\"?id="+itostring(id)+"&endvote=1\">"+_MSG("endvote")+"</a>";
        m["~rmvote~"]=r;
    }
    string ms;
    vector< vector<string> > q=d.dbh->execQ((QUERY)"select from_nick,ip,UNIX_TIMESTAMP(add_date),msg,show_nick from grant_messages where gid=? order by add_date desc"<<id);
    for (unsigned int i=0;i<q.size();i++){
        MUTEX_INSPECTOR;
        if (q[i].size()!=5){throw cError("select failed. size different"+_DMI());}
        map<string,string> a;
        if (admin || q[i][4]=="1"){
            a["~nick~"]="<b>"+q[i][0]+"</b> ";
        }else{
            a["~nick~"]="";
        }
        if (admin){
            a["~date~"]=datetime2num(atoi(q[i][2]))+" ("+q[i][1]+")";
        }else{
            a["~date~"]=datetime2num(atoi(q[i][2]));
        }
        a["~msg~"]=q[i][3];
        ms+=RVfiles(a,"vote/info_msg");
    }
    m["~messages~"]=ms;
    m["~id~"]=itostring(id);
    bool readden=atoi(d.dbh->select_1Q((QUERY)"select readden from grant_readden where gid=? and uid=?"<<id<<CONTAINER(cc_user_id)));
    if (!readden) {
        MUTEX_INSPECTOR;
        d.dbh->real_queryQ((QUERY)"insert into grant_readden (readden,gid,uid) values (1,?,?)"<<id<<CONTAINER(cc_user_id));
        m["~script~"]="<script>window.opener.ch_img("+itostring(id)+");</script>\n";
    }else{
        m["~script~"]="";
    }
    cc->html_out+=cc->rvfiles(m,"vote/info");
}

void recalc_vote()
{
    MUTEX_INSPECTOR;
    st_dbh d;
    vector< vector<string> > v=d.dbh->exec(
                                   "select "
                                   "tbl_users.id,"
                                   "tbl_users.vote_balls,"
                                   "grant_agrees.id,"
                                   "grant_agrees.yes "
                                   "from grant_agrees,tbl_users "
                                   "where tbl_users.vote_balls>0 and grant_agrees.uid=tbl_users.id"
                               );
    for (unsigned int i=0;i<v.size();i++){
        if (v[i].size()!=4) throw cError("select failed"+_DMI());
        if (v[i][3]!="0"){
            d.dbh->real_queryQ((QUERY)"update grant_agrees set yes=? where id=?"<<v[i][1]<<v[i][2]);
        }else{
            d.dbh->real_queryQ((QUERY)"update grant_agrees set no=? where id=?"<<v[i][1]<<v[i][2]);
        }
    }
    
}


