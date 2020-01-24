#include "user.h"
#include <map>
#include <string>
#include "utils.h"
#include "mafia.h"
#include "game.h"
#include "config.h"
#include <stdio.h>
#include "errs.h"

map<unsigned int,c_user*> gamers_by_id;
map<string,c_user*> gamers_by_nick;

unsigned int register_counter;

c_user::c_user() {
    win=false;
    gender=0;
    role=ROLE_MIR;
    score=0;
    last_score=0;
    id=0;
    accepted=false;
    main_maf=false;
    order=0;
    valed=false;
    marked_for_delete=false;
    killed=false;
    devoiced=false;
    left=false;
    chnick=false;
    need_update=false;
    doc_self=0;
}


string get_role_name(int role)
{
    if (role==ROLE_MIR) return "������";
    if (role==ROLE_MAF) return "�������";
    if (role==ROLE_MAN) return "��������";
    if (role==ROLE_DOC) return "��������";
    if (role==ROLE_KAT) return "������";
    if (role==ROLE_BOM) return "������";
    if (role==ROLE_VAL) return "�������";
    return "��";
}

string get_role_name2(int role)
{
    if (role==ROLE_MIR) return "������ ������";
    if (role==ROLE_MAF) return "�������";
    if (role==ROLE_MAN) return "������";
    if (role==ROLE_DOC) return "������";
    if (role==ROLE_KAT) return "��������� ������";
    if (role==ROLE_BOM) return "����";
    if (role==ROLE_VAL) return "�������� �����";
    return "��";
}

string get_role_name_cnt(int role,int cnt)
{
//	printf("role=%d cnt=%d\n",role,cnt);
    if (role==ROLE_MIR && cnt<=1) return "������";
    if (role==ROLE_MAF) return "�������";
    if (role==ROLE_MAN && cnt<=1) return "������";
    if (role==ROLE_DOC && cnt<=1) return "������";
    if (role==ROLE_KAT) return "������";
    if (role==ROLE_BOM && cnt<=1) return "����";
    if (role==ROLE_VAL && cnt<=1) return "�������";

    if (role==ROLE_MIR && cnt>1) return "������";
    if (role==ROLE_MAN && cnt>1) return "�������";
    if (role==ROLE_DOC && cnt>1) return "�������";
    if (role==ROLE_BOM && cnt>1) return "�����";
    if (role==ROLE_VAL && cnt>1) return "�������";

    return "��";
}

string get_role_shortname(int role)
{
    if (role==ROLE_MIR) return "mir";
    if (role==ROLE_MAF) return "maf";
    if (role==ROLE_MAN) return "man";
    if (role==ROLE_DOC) return "doc";
    if (role==ROLE_KAT) return "kat";
    if (role==ROLE_BOM) return "bom";
    if (role==ROLE_VAL) return "val";
    return "hz";
}

void register_user(const string &nick,const string &login,unsigned int gender, const string& ip)
{

    if (!registration) return;
    logErr("---register user %s %s",login.c_str(), nick.c_str());
    for (typeof(gamers_by_id.begin()) i=gamers_by_id.begin();i!=gamers_by_id.end();i++) {
        if (i->second->marked_for_delete) continue;
        if (i->second->login==login) {
//			i->second->nick=str_nick(nick);
            return;
        }
        if (i->second->ip==ip)
        {
            privmsg(nick,"������������ � ����� IP ������� ��� �������.");
            return;
        }
    }
    register_counter++;
    c_user *u=new c_user;
    u->nick=nick;
    u->login=login;
    u->id=register_counter;
    u->gender=gender;
    u->ip=ip;
    gamers_by_id[u->id]=u;
    gamers_by_nick[str_nick(nick)]=u;
    sock.response("MODE "+params["CHANNEL"]+" +v "+nick);
}

void unregister_user(const string &nick)
{
    logErr("---register user  %s", nick.c_str());
    typeof(gamers_by_nick.begin()) i=gamers_by_nick.find(str_nick(nick));
    if (i!=gamers_by_nick.end()) {
        if (!i->second->devoiced) sock.response("MODE "+params["CHANNEL"]+" -v "+i->second->nick);
        unsigned int id=i->second->id;
        c_user *u=i->second;
        if (u->need_update) {
            string sc=dbh->select_1Q((QUERY)"select score from score where login='?'"<<u->login);
            if (!sc.size()) {
                int win=0;
                int loose=0;
                if (u->win) win=1;
                else loose=1;
                dbh->real_queryQ((QUERY)"insert into score (win,loose,score,login) values (?,?,?,'?')"<<win<<loose<<u->score<<u->login);
            } else {
                int win=0;
                int loose=0;
                if (u->win) win=1;
                else loose=1;
                dbh->real_queryQ((QUERY)"update score set win=win+?,loose=loose+?,score=score+? where login='?'"<<win<<loose<<u->score<<u->login);
            }
        }

        delete i->second;
        gamers_by_id.erase(id);
        gamers_by_nick.erase(i);
    }
}


void clear_users() {
    for (typeof(gamers_by_nick.begin()) i=gamers_by_nick.begin();i!=gamers_by_nick.end();i++) {
        unregister_user(i->second->nick);
    }
    gamers_by_nick.clear();
    gamers_by_id.clear();
}

int get_active_users_count()
{
    int cnt=0;
    for (typeof(gamers_by_id.begin()) i=gamers_by_id.begin();i!=gamers_by_id.end();i++) {
        if (!i->second->marked_for_delete) cnt++;
    }
    return cnt;
}
