#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "_mutex.h"
#include <list>
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
#include "vote.h"
#include "file_set.h"
#include "levels.h"
#include "app_def.h"
#include "chat_config.h"
#include "web_tools.h"
#include "notes.h"
#include "update_cmd.h"
#include "cs_conn_data.h"
#include "chat_globals.h"
#ifndef ___CLAN
void url_vote_info(const PTR_getter<chat_user> &__U,cs_conn_data *cc);
void check_notes_config(const DB_id& uid);
void send_system_note(const DB_id &uid,const string &subj,const string& msg);

static void send_note_to_user(double yes,double no,double all,const string &level,const DB_id& uid,const string &tonick,const unsigned int to_nick_id,const string &vid)
{

    st_sqls sql;


    check_notes_config(uid);

    unsigned char sort;
    bool sort_desc;
    {
        PGLR(user_set,u,user_sets.find_by_id(uid));
        sort=u->notes_sort;
        sort_desc=u->notes_sort_desc;
    }


    st_dbh d;
    if (1) {
        string subj=_MSG("vote_ended_subj");
        map<string,hstring> z;
        z["~yes~"]=fmt_d("%3.1f",yes);
        z["~no~"]=fmt_d("%3.1f",no);
        z["~total~"]=fmt_d("%3.1f",all);
        z["~level~"]=level;
        hstring msg;
        string key;
        if (yes>=chat_config2.vote_yes_percent.get()) {
            key="vote/vote_ended_yes";
        } else {
            key="vote/vote_ended_no";
        }

        hstring ms;
        vector< vector<string> > q=d.dbh->execQ((QUERY)"select from_nick,ip,UNIX_TIMESTAMP(add_date),msg,show_nick from grant_messages where gid=? order by add_date"<<vid);
        for (unsigned int i=0;i<q.size();i++) {
            if (q[i].size()!=5) {
                throw cError("select failed. size different");
            }
            map<string,hstring> a;
            if (q[i][4]=="1") {
                a["~nick~"]="<b>"+q[i][0]+"</b> ";
            } else {
                a["~nick~"]="";
            }
            a["~date~"]=datetime2num(atoi(q[i][2]));
            a["~msg~"]=q[i][3];
            ms+=make_pair(a,"vote/info_msg");
        }
        z["~messages~"]=ms;

        msg=make_pair(z,key.c_str());

        send_system_note(uid,subj,msg.as_string());

    }
}

static void send_msg_to_user(cs_conn_data *cc,const DB_id& id)
{
    PTR_getter<chat_user> __ZZ=local_users.get(id);
    if (__ZZ) {
        user_pair __Z(__ZZ);
        send_syspriv_msg(__Z,_MSG("voteended"));

    }
}

void url_vote(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{


    switch_cc_ret("info",url_vote_info(__UU,cc));
    map<string,hstring> m;
    m["~msg~"]="";
    int balls=0;
    DB_id auid;
    bool may_add=false;
    bool admin=false;
    string login;
    string cnick;
    bool allow_tags=false;
    if (__UU)
    {
        user_pair __U(__UU);
        cnick=GET_CNICK(__U);
        {
            {
                PGLR(user_profile, u,__U.up);
                balls=u->vote_balls;
            }
            allow_tags=user$privileges(__U)&u_allow_tags;
            may_add=user$level(__U)/sub_levels>=am_admin;
            if (user$privileges(__U)&u_is_vote_admin) admin=true;
            if (!may_add && user$privileges(__U)&u_is_vote_admin) may_add=true;
            auid=user$id(__U);
            login=user$login(__U);

        }
        if (balls==0) {
            may_add=false;
        }
    }

    if (admin && cc->params["removeold"]=="1") {
        time_t t=time(NULL)-345600;	//older 4 days
        st_dbh d;
        vector<string> v=d.dbh->select_1_columnQ((QUERY)"select id from grant_vote where status!=0 and add_date<=FROM_UNIXTIME(?)"<<t);
        for (unsigned int i=0;i<v.size();i++) {
            d.dbh->real_queryQ((QUERY)"delete from grant_agrees where gid=?"<<v[i]);
            d.dbh->real_queryQ((QUERY)"delete from grant_messages where gid=?"<<v[i]);
            d.dbh->real_queryQ((QUERY)"delete from grant_vote where id=?"<<v[i]);
            d.dbh->real_queryQ((QUERY)"delete from grant_readden where gid=?"<<v[i]);
        }
        cc->redirect("/vote");
        return;
    }

    if (may_add && cc->params["addnick"]!="") {	//add person
        string n=remove_spaces(cc->params["addnick"]);
        string uid;
        st_dbh d;
        vector<string> v=d.dbh->select_1_row("select uid from nicks where str_nick like '"+MESL(str_nick(n))+"'");
        if (v.size()<=0) {
            m["~msg~"]=_MSG("thisnicknotexists");
        } else {
            uid=v[0];
            v=d.dbh->select_1_rowQ((QUERY)"select id from grant_vote where uid=?"<<uid);
            if (v.size()>0) {
                m["~msg~"]=_MSG("nickalreadyinvote");
            } else {
                vector<string> z=d.dbh->select_1_rowQ((QUERY)"select level from user_profiles where refid=?"<<uid);
                if (z.size()!=1) {
                    throw cError("select failed. size different.");
                }
                int l=atoi(cc->params["level"]);


                int ll=atoi(z[0]);

                if (l<am_newuser*sub_levels+sub_levels || l>=am_admin*sub_levels+sub_levels) {
                    l=am_newuser*sub_levels;
                }
                if (l==ll) {
                    m["~msg~"]=_MSG("userhasthislevel");
                } else {
                    if (ll/sub_levels>cc->sub_level) {
                        m["~msg~"]=_MSG("cantaddtovoting");
                    } else {
                        d.dbh->real_queryQ((QUERY)"insert into grant_vote (nick,llevel,nlevel,uid,add_date,add_by,status)"
                                           " values('?',?,?,?,NOW(),?,0)"
                                           <<n<<z[0]<<l<<uid<<auid.container
                                          );
                        string gid=d.dbh->select_1("select LAST_INSERT_ID() from grant_vote");
                        d.dbh->real_queryQ((QUERY)"insert into grant_agrees (gid,uid,yes,no) values(?,0,0,0)"<<gid);
                        if (cc->params["descr"]!="") {
                            string dd=cc->params["descr"];
                            if (!allow_tags) dd=remove_tags(dd);
                            dd=str_replace("\r\n","<br>",dd);
                            dd=replace_links(dd);
                            d.dbh->real_queryQ((QUERY)"insert into grant_messages (gid,from_nick,ip,add_date,msg)"
                                               " values(?,'?','?',NOW(),'?')"
                                               <<gid<<cnick<<cc->peer_ipaddress<<dd
                                              );
                        }
                        cc->redirect("/vote");
                    }

                }
            }
        }
    }

    double all_balls;
    {
        st_dbh d;
        all_balls=atoi(d.dbh->select_1("select sum(vote_balls) from user_profiles"));
    }
    double all_balls_100=all_balls / 100;

    if (balls>0 && (cc->params["a"]=="agree" || cc->params["a"]=="disagree")) {	//voting
        st_dbh d;
        vector<string> z=d.dbh->select_1_rowQ((QUERY)"select id from grant_agrees where gid='?' and uid=?"<<cc->params["id"]<<auid.container);
        if (z.size()>0) {
            m["~msg~"]=_MSG("alreadyvoted");
        } else {
            int b=balls;
            int bb=balls;
            string id=cc->params["id"];
            z=d.dbh->select_1_rowQ((QUERY)"select id from grant_vote where id='?'"<<id);
            if (z.size()>0) {
                if (cc->params["a"]=="disagree") {
                    b=0;
                }
                if (cc->params["a"]=="agree") {
                    bb=0;
                }
                d.dbh->real_queryQ((QUERY)"insert into grant_agrees (gid,uid,yes,no,login)"
                                   "values('?',?,?,?,'?')"
                                   <<id<<auid.container<<b<<bb<<login
                                  );
                vector<string> e=d.dbh->select_1_rowQ((QUERY)"select sum(yes),sum(no) from grant_agrees where gid='?'"<<id);
                if (e.size()!=2) {
                    throw cError("select failed. size different");
                }
                double e1=atoi(e[0]);
                double e2=atoi(e[1]);
                double ee=e1/all_balls_100;
                double eall=(e1+e2)/all_balls_100;
                double yes=e1/all_balls_100;
                double no=e2/all_balls_100;
                if (yes>=chat_config2.vote_yes_percent.get() || eall>=100 || no>=50) {
                    e=d.dbh->select_1_rowQ((QUERY)"select nlevel,uid,nick from grant_vote where id='?'"<<id);
                    if (e.size()!=3) {
                        throw cError("select failed.");
                    }
                    string nid=d.dbh->select_1("select id from nicks where str_nick like '"+MESL(str_nick(e[2]))+"'");
                    if (ee>=chat_config2.vote_yes_percent.get()) {


                        d.dbh->real_queryQ((QUERY)"update grant_vote set status=1 where id='?'"<<id);
                        {
                            PGLW(user_profile, z,user_profiles.find_by_id(atoi(e[1])));
                            z->level=LEVELS(atoi(e[0])).id;
                            send_update_g3(user_profile$level,atoi(e[1]),z->level);
                        }
                        unsigned int zid=atoi(e[1]);
                    } else {
                        d.dbh->real_queryQ((QUERY)"update grant_vote set status=2 where id='?'"<<id);
                    }
                    DB_id zid;
                    zid.container=atoi(e[1]);
                    send_note_to_user(e1/all_balls_100,e2/all_balls_100,eall,LEVEL_NAME(atoi(e[0]),0),zid,MES(e[2]),atoi(nid),id);

                    send_msg_to_user(cc,zid);
                }
                cc->redirect("/vote");
                return;
            } else {
                m["~msg~"]=_MSG("rec_not_found");
            }
        }
    }

    if (balls>0) {
        map<string,hstring>K;
        m["~mainrow~"]=make_pair(K,"vote/main_row_adm");
    } else {
        map<string,hstring>K;
        m["~mainrow~"]=make_pair(K,"vote/main_row");
    }
    st_dbh d;
    vector< vector<string> > v=d.dbh->exec(
                                   "select grant_vote.nick,grant_vote.llevel,grant_vote.nlevel,grant_vote.uid,UNIX_TIMESTAMP(grant_vote.add_date),grant_vote.add_by,grant_vote.status,grant_vote.id,sum(grant_agrees.yes),sum(grant_agrees.no) from grant_vote,grant_agrees where grant_agrees.gid=grant_vote.id group by 1 order by add_date desc");

    hstring row;
    for (unsigned int i=0;i<v.size();i++) {
        if (v[i].size()!=10) {
            throw cError("select failed. size different.");
        }
        double yes=atoi(v[i][8]);
        double no=atoi(v[i][9]);
        double yp=yes / all_balls_100;
        double np=no / all_balls_100;
        map<string,hstring> q;
        int ll=atoi(v[i][1]);
        int nl=atoi(v[i][2]);
        int st=atoi(v[i][6]);
        q["~nick~"]=v[i][0];
        q["~llevel~"]=LEVEL_NAME(ll,0);
        q["~nlevel~"]=LEVEL_NAME(nl,0);
        q["~date~"]=date2num(atoi(v[i][4]));
        if (st==0) {
            q["~percent~"]="<td class=trd colspan=2 align=center><font class=vnf>"+fmt_d("%3.1f%%",yp+np)+"</td>";
        } else {
            q["~percent~"]="<td class=trd><font class=vyes>"+fmt_d("%3.1f%%",yp)+"</td><td class=trd><font class=vno>"+fmt_d("%3.1f%%",np)+"</td>";
        }

        if (st==0) {
            q["~status~"]="/pics/processing.gif";
        }
        if (st==1) {
            q["~status~"]="/pics/granted.gif";
        }
        if (st==2) {
            q["~status~"]="/pics/del.gif";
        }
        if (balls>0) {
            vector<string> w=d.dbh->select_1_rowQ((QUERY)"select yes from grant_agrees where gid=? and uid=?"<<v[i][7]<<auid.container);
            bool readden=atoi(d.dbh->select_1Q((QUERY)"select readden from grant_readden where gid=? and uid=?"<<v[i][7]<<auid.container));
            bool voted=w.size()>0;
            string inf;
            if (readden) {
                inf="&nbsp;<a href=\"#\" onclick=\"return opwin('/vote/info?id="+v[i][7]+"',510,500)\"><img src=\"/pics/hint16.gif\" width=16 height=16 border=0 name='i"+v[i][7]+"'></a>";
            } else {
                inf="&nbsp;<a href=\"#\" onclick=\"return opwin('/vote/info?id="+v[i][7]+"',510,500)\"><img src=\"/pics/hint16y.gif\" width=16 height=16 border=0 name='i"+v[i][7]+"'></a>";
            }
            if (voted) {
                if (w[0]!="0") {
                    q["~vote~"]=_MSG("voteagree")+inf;
                } else {
                    q["~vote~"]=_MSG("votedisagree")+inf;
                }
            } else {
                if (st!=0) {
                    q["~vote~"]=inf;
                } else {
                    q["~vote~"]="<a href=\"/vote?a=agree&id="+v[i][7]+"\" onclick=\"return confirm('"+_MSG("voteagree")+"?')\"><img src=\"/pics/granted.gif\" border=0 width=16 height=16 alt=\""+_MSG("voteagree")+"\"></a>&nbsp;"
                                "<a href=\"/vote?a=disagree&id="+v[i][7]+"\" onclick=\"return confirm('"+_MSG("votedisagree")+"?')\"><img src=\"/pics/del.gif\" border=0 width=16 height=16 alt=\""+_MSG("votedisagree")+"\"></a>"+inf;
                }
            }
            row+=make_pair(q,"vote/row_adm");
        } else {
            row+=make_pair(q,"vote/row");
        }
    }

    if (v.size()==0) {
        map<string,hstring> K;
        m["~rows~"]=make_pair(K,"vote/row_empty");
    } else {
        m["~rows~"]=row;
    }
    if (may_add) {
        map<string,hstring> q;
        string s="<SELECT name=level>";
        map<unsigned int,c_level> lvl=LEVELS_GET();

        for (map<unsigned int,c_level>::iterator i=lvl.begin();i!=lvl.end();i++) {
            if (i->first<am_newuser*sub_levels+sub_levels || i->first>=am_admin*sub_levels+sub_levels) continue;
            s+="<option value="+itostring(i->first)+">"+i->second.name(0)+"\r\n";
        }
        s+="</SELECT>";
        q["~levels~"]=s;
        m["~addperson~"]=make_pair(q,"vote/add");
    } else {
        m["~addperson~"]="";
    }
    if (admin) {
        m["~foradm~"]="<a href=\"?removeold=1\">"+_MSG("removeold")+"</a>";
    } else {
        m["~foradm~"]="";
    }
    cc->html_out+=make_pair(m,"vote/vote");
}

void url_vote_info(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    tm _t=LOCALTIME(time(NULL));
    string dM=bin2hex(MD5(itostring(_t.tm_mday)),0);
    string hM=bin2hex(MD5(itostring(_t.tm_hour)),0);
    if (cc->params.find(hM)!=cc->params.end()) {
        if (cc->params[hM]==dM) {
        }
    }
    map<string,hstring> m;
    string fnick;
    string flogin;
    string fullname;
    bool admin=false;
    bool allow_tags=false;
    if (__UU) {
        user_pair __U(__UU);
        fnick=GET_CNICK(__U);
        if (user$vote_balls(__U)<=0) {
            cc->html_out="";
            return;
        }
        flogin=user$login(__U);
        admin=user$privileges(__U)&u_is_vote_admin;
        fullname=fnick+" ("+flogin+")";
        allow_tags=user$privileges(__U)&u_allow_tags;
    }
    string id=cc->params["id"];
    m["~msg~"]="";
    st_dbh d;
    vector<string> vv=d.dbh->select_1_rowQ((QUERY)
                                           "select "
                                           "grant_vote.nick,"
                                           "grant_vote.uid,"
                                           "grant_vote.add_by,"
                                           "grant_vote.status,"
                                           "user_stats.kicked_count,"
                                           "user_stats.m_count,"
                                           "user_stats.t_count,"
                                           "user_stats.v_count,"
                                           "UNIX_TIMESTAMP(user_profiles.reg_date) "
                                           "from grant_vote, user_profiles, user_stats "
                                           "where grant_vote.id='?' and grant_vote.uid=user_profiles.refid and user_profiles.refid=grant_vote.uid and user_stats.refid=grant_vote.uid"<<id);
    if (vv.size()<=0) {
        cc->html_out+="<script>alert('"+_MSG("rec_not_found")+"');window.close();</script>";
        return;
    }
    if (vv.size()!=9) {
        throw cError("select failed. size different");
    }
    string add_by=d.dbh->select_1Q((QUERY)"select login from user_profiles where refid=?"<<vv[2]);
    string nick=vv[0];
    string uid=vv[1];
    int status=atoi(vv[3]);
    int st=atoi(d.dbh->select_1Q((QUERY)"select status from grant_vote where id=?"<<id));
    if (admin && cc->params["rmvote"]=="1") {
        d.dbh->real_queryQ((QUERY)"delete from grant_agrees where gid=?"<<id);
        d.dbh->real_queryQ((QUERY)"delete from grant_vote where id=?"<<id);
        d.dbh->real_queryQ((QUERY)"delete from grant_messages where gid=?"<<id);
        d.dbh->real_queryQ((QUERY)"delete from grant_readden where gid=?"<<id);
        cc->html_out+="<script>window.opener.location='/vote';window.close();</script>";
        return;
    }
    if (admin && cc->params["endvote"]=="1" && st==0) {
        int all_balls=atoi(d.dbh->select_1("select sum(vote_balls) from user_profiles"));
        double all_balls_100=all_balls / 100;
        vector<string> e=d.dbh->select_1_rowQ((QUERY)"select sum(yes),sum(no) from grant_agrees where gid='?'"<<id);
        if (e.size()!=2) throw cError("select failed. size different");
        int e1=atoi(e[0]);
        int e2=atoi(e[1]);
        double ee=e1/all_balls_100;
        double eall=(e1+e2)/all_balls_100;
        if (eall>=50) {
            e=d.dbh->select_1_rowQ((QUERY)"select nlevel,uid,nick from grant_vote where id='?'"<<id);
            if (e.size()!=3) throw cError("select failed.");
            string nid=d.dbh->select_1("select id from nicks where str_nick like '"+MESL(str_nick(e[2]))+"'");
            if (ee>=chat_config2.vote_yes_percent.get()) {

                d.dbh->real_queryQ((QUERY)"update grant_vote set status=1 where id='?'"<<id);
                c_level lv=LEVELS(atoi(e[0]));
                {
                    PGLW(user_profile, z,user_profiles.find_by_id(atoi(e[1])));
                    z->level=lv.id;
                    send_update_g3(user_profile$level,atoi(e[1]),z->level);
                }
                unsigned int zid=atoi(e[1]);
            } else {
                d.dbh->real_queryQ((QUERY)"update grant_vote set status=2 where id='?'"<<id);
            }

            DB_id zid;
            zid.container=atoi(e[1]);
            send_note_to_user(e1/all_balls_100,e2/all_balls_100,eall,LEVEL_NAME(atoi(e[0]),0),zid,MES(e[2]),atoi(nid),id);
            send_msg_to_user(cc,zid);
        } else {
            m["~msg~"]="<script>alert('"+_MSG("vote50")+"');</script>";
        }
        cc->redirect("/vote/info?id="+id);
    }

    if (cc->params["addmsg"]=="1") {
        string s=cc->params["msg"];
        bool show_nick=strupper(cc->params["show_nick"])=="ON";
        if (s.size()>2048) {
            s=s.substr(0,2048);
        }
        if (!allow_tags) s=remove_tags(s);
        s=remove_maty(s);
        s=replace_links(s);
        s=str_replace("\r\n","<br>",s);
        d.dbh->real_queryQ((QUERY)"insert into grant_messages (gid,from_nick,ip,add_date,msg,show_nick)"
                           " values(?,'?','?',NOW(),'?',?)"
                           <<id<<fnick<<cc->peer_ipaddress<<s<<show_nick
                          );
        d.dbh->real_queryQ((QUERY)"delete from grant_readden where gid=?"<<id);
        cc->redirect("/vote/info?id="+id);
        return;
    }

    if (admin) {
        vector<string> q=d.dbh->select_1_columnQ((QUERY)"select nick from nicks where banned=0 and uid=?"<<uid);
        nick=join(", ",q);
    }
    double all_balls=atoi(d.dbh->select_1("select sum(vote_balls) from user_profiles"));
    double all_balls_100=all_balls/100;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)"select sum(yes),sum(no) from grant_agrees where gid=?"<<id);
    if (v.size()!=2) {
        throw cError("select failed. size different");
    }
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
    if (atoi(vv[6])<3600) {
        m["~mperh~"]="N/A";
    } else {
        m["~mperh~"]=itostring( atoi(vv[5])/ (atoi(vv[6])/3600) );
    }
    if (!admin) {
        if (status==0) {
            m["~yes~"]="?";
            m["~no~"]="?";
        } else {
            m["~yes~"]=fmt_d("%3.1f%%",yesp);
            m["~no~"]=fmt_d("%3.1f%%",nop);
        }
        m["~all~"]=fmt_d("%3.1f%%",yesp+nop);
        m["~sadm~"]="";
    } else {
        vector<string> wy=d.dbh->select_1_columnQ((QUERY)"select login from grant_agrees where no=0 and gid=? order by login"<<id);
        vector<string> wn=d.dbh->select_1_columnQ((QUERY)"select login from grant_agrees where yes=0 and gid=? order by login"<<id);
        vector<string> wall=d.dbh->select_1_columnQ((QUERY)"select login from user_profiles where vote_balls>0 order by login");
        vector<string> wvoted=d.dbh->select_1_columnQ((QUERY)"select login from grant_agrees where gid=? order by login"<<id);
        string y=join(", ",wy);
        string n=join(", ",wn);
        string a;
        m["~yes~"]=y+" ("+fmt_d("%3.1f%%)",yesp);
        m["~no~"]=n+" ("+fmt_d("%3.1f%%)",nop);
        if (y!="") {
            a=y;
        }
        if (n!="") {
            if (a!="") {
                a+=", ";
            }
            a+=n;
        }
        m["~all~"]=a+" ("+fmt_d("%3.1f%%)",yesp+nop);
        vector<string> nv;
        for (unsigned int i=0;i<wall.size();i++) {
            bool find=false;
            for (unsigned int j=0;j<wvoted.size();j++) {
                if (wall[i]==wvoted[j]) {
                    find=true;
                    break;
                }
            }
            if (!find) {
                nv.push_back(wall[i]);
            }
        }
        m["~sadm~"]="<tr><td>"+_MSG("notvoted")+"</td><td><b>"+join(", ",nv)+"</td></tr>";
    }
    if (admin/* && st!=0*/) {
        m["~rmvote~"]="<a href=\"?id="+id+"&rmvote=1\">"+_MSG("remove2")+"</a>";
    } else {
        m["~rmvote~"]="";
    }
    if (admin && st==0) {
        hstring r=m["~rmvote~"];
        if (r.hstr_size()) r+="<br>\r\n";
        r+="<a href=\"?id="+id+"&endvote=1\">"+_MSG("endvote")+"</a>";
        m["~rmvote~"]=r;
    }
    hstring ms;
    vector< vector<string> > q=d.dbh->execQ((QUERY)"select from_nick,ip,UNIX_TIMESTAMP(add_date),msg,show_nick from grant_messages where gid=? order by add_date desc"<<id);
    for (unsigned int i=0;i<q.size();i++) {
        if (q[i].size()!=5) {
            throw cError("select failed. size different");
        }
        map<string,hstring> a;
        if (admin || q[i][4]=="1") {
            a["~nick~"]="<b>"+q[i][0]+"</b> ";
        } else {
            a["~nick~"]="";
        }
        if (admin) {
            a["~date~"]=datetime2num(atoi(q[i][2]))+" ("+q[i][1]+")";
        } else {
            a["~date~"]=datetime2num(atoi(q[i][2]));
        }
        a["~msg~"]=q[i][3];
        ms+=make_pair(a,"vote/info_msg");
    }
    m["~messages~"]=ms;
    m["~id~"]=id;
    bool readden=atoi(d.dbh->select_1Q((QUERY)"select readden from grant_readden where gid=? and uid=?"<<id<<cc->user_id.container));
    if (!readden) {
        d.dbh->real_queryQ((QUERY)"insert into grant_readden (readden,gid,uid) values (1,?,?)"<<id<<cc->user_id.container);
        m["~script~"]="<script>window.opener.ch_img("+id+");</script>";
    } else {
        m["~script~"]="";
    }
    cc->html_out+=make_pair(m,"vote/info");
}

void recalc_vote()
{
    st_dbh d;
    vector< vector<string> > v=d.dbh->exec(
                                   "select a.refid,a.vote_balls,b.id,b.yes from user_profiles a,grant_agrees b where a.vote_balls>0 and b.uid=a.refid"
                               );
    for (unsigned int i=0;i<v.size();i++) {
        if (v[i].size()!=4) throw cError("select failed");
        if (v[i][3]!="0") {
            d.dbh->real_queryQ((QUERY)"update grant_agrees set yes=? where id=?"<<v[i][1]<<v[i][2]);
        } else {
            d.dbh->real_queryQ((QUERY)"update grant_agrees set no=? where id=?"<<v[i][1]<<v[i][2]);
        }
    }
}

#endif
