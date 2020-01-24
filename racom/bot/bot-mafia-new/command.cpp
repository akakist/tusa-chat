#include "command.h"
#include <string>
#include <stdio.h>
#include "utils.h"
#include "mafia.h"
#include "errs.h"
#include "misc.h"
#include "game.h"
#include "user.h"
#include "messages.h"
#include "config.h"
#include "night.h"
#include "day.h"
#include <unistd.h>
#include "antiflood.h"
#include "config.h"


map<string,bool> greet_send;

void process_command(c_command &cmd)
{
    try {
        if (cmd.cmd=="PRIVMSG") {
            check_for_flood(cmd);
            if (cmd.tonick==params["CHANNEL"]) {
                process_channel_command(cmd);
            } else {
                process_private_command(cmd);
            }
        }
        if (cmd.cmd=="QUIT" || cmd.cmd=="KICK") {
            if (game_started || registration || roles_assign) {
                string nk;
                if (cmd.cmd=="QUIT") nk=str_nick(cmd.fromnick);
                else nk=str_nick(cmd.tonick);
//				printf("nick='%s'\n",nk.c_str());
                if (gamers_by_nick.find(nk)!=gamers_by_nick.end()) {
                    c_user *u=gamers_by_nick.find(nk)->second;
                    if (u->marked_for_delete) return;
                    u->left=true;
                    if (!registration) {
                        action(_MSG("userleft",0,u->nick.c_str()));
                    }
                }
            }
        }
        if (cmd.cmd=="JOIN") {
            if (!voiced) {
                sock.response("MODE "+params["CHANNEL"]+" +v "+params["NICKNAME"]);
                voiced=true;
            }
            if (!greet_send[cmd.user]) {
                greet_send[cmd.user]=true;
                privmsg(cmd.fromnick,_MSG("greeting"));
            }
            if (game_started || registration || roles_assign) {
                if (gamers_by_nick.find(str_nick(cmd.fromnick))!=gamers_by_nick.end()) {
                    c_user *u=gamers_by_nick.find(str_nick(cmd.fromnick))->second;
                    if (u->marked_for_delete) return;
                    if (u->chnick) return;
                    if (u->left) {
                        u->left=false;
                        if (!registration) action(_MSG("userreturned",0,u->nick.c_str()));
                        sock.response("MODE "+params["CHANNEL"]+" +v "+u->nick);
                    }
                }
            }
        }
        if (cmd.cmd=="NICK") {
            if (game_started || roles_assign || registration) {
                if (gamers_by_nick.find(str_nick(cmd.fromnick))!=gamers_by_nick.end()) {
                    c_user *u=gamers_by_nick.find(str_nick(cmd.fromnick))->second;
                    if (u->marked_for_delete) return;
                    if (game_started || roles_assign) {
                        action(_MSG("nickchanging",u->gender,u->nick.c_str()));
                        sock.response("MODE "+params["CHANNEL"]+" -v "+u->nick);
                        u->left=true;
                        u->chnick=true;
                    } else {
                        gamers_by_nick.erase(str_nick(u->nick));
                        u->nick=cmd.msg;
                        gamers_by_nick[str_nick(u->nick)]=u;
                    }
                }
            }
        }
        if (cmd.cmd=="EUI_REPLY" && registration) {
            vector<string> pr=splitTOK(":",cmd.msg);
            if (pr.size()!=7) return;
            int lev=atoi(pr[4]);
            if (pr[3]=="1" || lev<20) {
                if (pr[3]=="1") privmsg(pr[0],_MSG("unregistered",atoi(pr[2]),pr[0].c_str()));
                else privmsg(pr[0],_MSG("lowlevel",atoi(pr[2]),pr[0].c_str()));
            } else {
                register_user(pr[0],pr[1],atoi(pr[2]),pr[6]);
            }
        }
    } catch (cError e) {
        logErr("---Error during process command: %s",e.error_string.c_str());
    }
}

void process_day_or_night(c_command &cmd)
{
    string msg=cmd.msg;
//	printf("msg='%s'\n",msg.c_str());
    if (msg.size()<1) return;
    if (msg.substr(0,1)!="!") return;
    if (night || day) {
        string d;
        bool dbl;
        if (msg.size()<2) return;
        if (msg.substr(1,1)=="!" && msg.size()>2) {
            d=msg.substr(2,msg.size()-2);
            dbl=true;
        } else {
            d=msg.substr(1,msg.size()-1);
            dbl=false;
        }
//		printf("dbl=%d n=%s\n",dbl,d.c_str());
        int id=atoi(d);
//		printf("cond id=%d\n",id);
        if (gamers_by_nick.find(str_nick(cmd.fromnick))==gamers_by_nick.end()) return;
        int uid=gamers_by_nick.find(str_nick(cmd.fromnick))->second->id;
        if (night) {
            if (gamers_by_id.find(uid)->second->role==ROLE_MIR) return;
        }
        if (!id) {
            if (gamers_by_nick.find(str_nick(d))!=gamers_by_nick.end()) {
                id=gamers_by_nick.find(str_nick(d))->second->id;
            }
        }
        if (gamers_by_id.find(id)==gamers_by_id.end()) {
            privmsg(cmd.fromnick,_MSG("wrongcommand"));
            return;
        }
//		printf("fromid=%d toid=%d\n",uid,id);
//		printf("process!!!!!!!\n");
        if (day) process_day(uid,id,dbl);
        if (night) process_night(uid,id,dbl);
    }

}

void process_channel_command(c_command &cmd)
{
    string msg=cmd.msg;
//	if()
    if (day) {
        if (msg.find("!list")!=-1 || msg.find("!список")!=-1) {
            action(get_gamers_list(false).c_str());
            return;
        }
        if (msg.find("!!night")!=-1 || msg.find("!!ночь")!=-1 || msg.find("!!yjxm")!=-1) {
            if (gamers_by_nick.count(str_nick(cmd.fromnick)))
            {
                int uid=gamers_by_nick.find(str_nick(cmd.fromnick))->second->id;
                process_day(uid,1000000,false);
            }
            return;
        }
        if (vote2 && !vote_say) {
            if (strex(msg,"!да") || strex(msg,"!нуы") || strex(msg,"!yes") || strex(msg,"!lf")) {
                do_vote_yes(cmd.fromnick);
            }
            if (strex(msg,"!нет") || strex(msg,"!тщ") || strex(msg,"!no") || strex(msg,"!ytn")) {
                do_vote_no(cmd.fromnick);
            }
            return;
        }
        if (vote_say) {
            if (strex(msg,"!все") || strex(msg,"!all") || strex(msg,"!dct") || strex(msg,"!фдд")) {
                if (gamers_by_nick.count(str_nick(cmd.fromnick)))
                {
                    c_user *u=gamers_by_nick.find(str_nick(cmd.fromnick))->second;
                    if (u==vote2_person) vote_say_time=0;
                }
                return;
            }
        }
    }
    if (strex(msg,"!")) {
        //help
        if (strex(msg,"!help") || strex(msg,"!хелп") || strex(msg,"!comm")) {
            do_help(cmd);
            return;
        }
        if (strex(msg,"!rules") || strex(msg,"!правила") || strex(msg,"!кглуы")) {
            do_rules(cmd);
            return;
        }
        if (strex(msg,"!start") || strex(msg,"!старт") || strex(msg,"!cnfhn") || strex(msg,"!ыефке")) {
            start_game(cmd);
            return;
        }
        if (strex(msg,"!reg") || strex(msg,"!htu") || strex(msg,"!куп") || strex(msg,"!рег")) {
            if (!registration) return;
            if (gamers_by_nick.find(str_nick(cmd.fromnick))==gamers_by_nick.end() && str_nick(cmd.fromnick)!=str_nick(params["NICKNAME"])) {
                sock.response("EUI "+cmd.fromnick);
            }
            return;
        }
        if (strex(msg,"!unreg") || strex(msg,"!гткуп")) {
            if (registration) unregister_user(cmd.fromnick);
            return;
        }
        if (strex(msg,"!stat") || strex(msg,"!cnfn") || strex(msg,"!стат") || strex(msg,"!ыефе")) {
            if (game_started) show_roles();
            return;
        }
    }
    if (day || night) {
        process_day_or_night(cmd);
        return;
    }
    if (registration) {
        string cdb=params["CHAT_DB_NAME"];
        if (strex(msg,"!вон") || strex(msg,"!djy")) {
            string nick;
            string login;
            if (msg.size()==4 || msg.size()==5) {
                nick=cmd.fromnick;
                login=cmd.user;
            } else {
                if (msg.size()>5) {
                    nick=msg.substr(5,msg.size()-5);
                }
                login=dbh->select_1Q((QUERY)"select ?.nicks.login from ?.nicks where ?.nicks.uppernick='?'"<<cdb<<cdb<<cdb<<str_nick(nick));
            }
            vector<string> score;
            if (login.size()) {
                score=dbh->select_1_rowQ((QUERY)"select score,win,loose from score where login='?'"<<login);
            }
            if (score.size()==3) {
                channelmsg("На счету у <u>"+nick+"</u> - <u>"+score[0]+"</u> очков, играл(а) в <u>"+itostring(atoi(score[1])+atoi(score[2]))+"</u> игр, выигрышей - <u>"+score[1]+"</u>, проигрышей - <u>"+score[2]+"</u>");
            } else {
                channelmsg("В базе нет игрока с ником "+nick);
            }
            return;
        }
        if (strex(msg,"!place") || strex(msg,"!здфсу")) {
            string nick;
            string login;
            if (msg.size()==6 || msg.size()==7) {
                nick=cmd.fromnick;
                login=cmd.user;
            } else {
                if (msg.size()>7) {
                    nick=msg.substr(7,msg.size()-7);
                }
                login=dbh->select_1Q((QUERY)"select ?.nicks.login from ?.nicks where ?.nicks.uppernick='?'"<<cdb<<cdb<<cdb<<str_nick(nick));
            }
//			printf("in place: n=%s l=%s\n",nick.c_str(),login.c_str());
            if (login.size()) {
                string score=dbh->select_1Q((QUERY)"select score from score where login='?'"<<login);
                string pl=dbh->select_1Q((QUERY)"select count(*) from score where score>=?"<<score);
                channelmsg("<u>"+nick+"</u> занимает <u>"+pl+"</u> место в рейтинге.");
            } else {
                channelmsg("В базе нет игрока с ником "+nick);
            }
            return;
        }
        if (strex("!top",msg) || strex("!топ",msg)) {
            /*			vector< vector<string> > v=dbh->execQ((QUERY)"select a.nick,b.score from ?.nicks a,score b,?.users c,?.user_settings d where b.login=c.login and d.uid=c.id and a.id=d.anick order by b.score desc limit 10"<<cdb<<cdb<<cdb);
            			string repl="</b></b><b>TOP 10</b> Самых лучших игроков:";
            			for(unsigned int i=0;i<v.size();i++){
            				repl+="<br>";
            				if(v[i].size()==2){
            					if(i==0){
            						repl+="<b>"+itostring(i+1)+": <u>"+v[i][0]+"</u> - "+v[i][1]+"</b>";
            					}else{
            						repl+=itostring(i+1)+"</b>: <u>"+v[i][0]+"</u> - "+v[i][1];
            					}
            				}
            			}
            			privmsg(cmd.fromnick,repl);
            			return;*/
            vector< vector<string> > v=dbh->execQ((QUERY)
                                                  "select ?.user_sets.last_nick,score.score from "
                                                  "?.user_profiles, "
                                                  "score,"
                                                  "?.user_sets where score.login=?.user_profiles.login  "
                                                  "and ?.user_sets.refid=?.user_profiles.refid order by score.score desc limit 10"<<cdb<<cdb<<cdb<<cdb<<cdb<<cdb<<cdb);
            string repl="</b></b><b>TOP 10</b> Самых лучших игроков:";
            for (unsigned int i=0;i<v.size();i++) {
                repl+="<br>";
                if (v[i].size()==2) {
                    /*oscar_buffer b;
                    b.Pack(v[i][0]);
                    user_state st;
                    b>>st;*/

                    if (i==0) {
                        repl+="<b>"+itostring(i+1)+": <u>"+v[i][0] +"</u> - "+v[i][1]+"</b>";
                    } else {
                        repl+=itostring(i+1)+"</b>: <u>"+v[i][0]+"</u> - "+v[i][1];
                    }
                }
            }
            privmsg(cmd.fromnick,repl);
            return;

        }
    }
}

void process_private_command(c_command &cmd)
{
    string msg=cmd.msg;
    if (strex(msg,"!halt")) {
        if (access_users.find(cmd.user)!=access_users.end()) {
            if (game_started || registration || roles_assign) {
                action("Игра остановлена администратором!");
                sock.response("MODE "+params["CHANNEL"]+" -m");
                clear_users();
                registration=false;
                roles_assign=false;
                night=false;
                day=false;
                morning=false;
                game_started=false;
                return;
            }
        }
    }
    if (strex(msg,"!lf") || strex(msg,"!yes") || strex(msg,"!да") || strex(msg,"!нуы")) {
        if (roles_assign) {
            accept_role(cmd.fromnick);
            return;
        }
    }
    if (strex(msg,"!ytn") || strex(msg,"!no") || strex(msg,"!нет") || strex(msg,"!тщ")) {
        if (roles_assign) {
            decline_role(cmd.fromnick,true);
            return;
        }
    }
//	printf("processing1p d=%d n=%d\n",day,night);
    if (night || morning) {
        if (strex(msg,"!фраза") || strex(msg,"!ahfpf")) {
            add_phrase(cmd);
            return;
        }
    }
    if (day || night) {
        if (strex(msg,"!мафия") || strex(msg,"!mafia")) {
            if (gamers_by_nick.find(str_nick(cmd.fromnick))!=gamers_by_nick.end()) {
                c_user *u=gamers_by_nick.find(str_nick(cmd.fromnick))->second;
                if (!u->marked_for_delete) {
                    if (u->role==ROLE_MAF) {
                        string s=get_mafia();
                        privmsg(cmd.fromnick,s);
                    }
                }
            }
            return;
        }
    }
    if (day || night) {
//		printf("processing1p\n");
        process_day_or_night(cmd);
        return;
    }
}

