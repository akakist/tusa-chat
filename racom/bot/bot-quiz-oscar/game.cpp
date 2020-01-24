#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "c_conn.h"
#include "errs.h"
#include "config.h"
#include "utils.h"
#include "misc.h"
#include "mysql_extens.h"
#include <vector>
#include "quiz.h"
#include "antiflood.h"
/*class user_nick
{
public:
    string name;
    unsigned int id;
//	user_nick();

//	user_nick(const string &n);
//	user_nick(const string &n,unsigned int i);
};

struct user_status
{
	string name;
	int pic;
	int id;
	bool disable_invite;
	bool uniq;
};

class user_state
{

	public:

	enum
	{
		UNDEF=0xffff0000
	};
		unsigned int channel;
		user_status status;
		user_nick nick;
//		bool contact_mode; // true if userlist contains contacts only
//		user_state():nick("undef",UNDEF){channel=UNDEF;status.id=UNDEF;nick.id=UNDEF;}
};*/
/*oscar_buffer & operator>>(oscar_buffer&b, user_nick &n)
{
	DWORD_LE id;
	oscar_buffer::L_STR ni;
	b>>id>>ni;
	n.id=id.obj;
	n.name=ni.container;
	return b;
}

oscar_buffer & operator>>(oscar_buffer&b, user_status &n)
{
	oscar_buffer::L_STR name;
	DWORD_LE pic,id;
	__BYTE di,uniq;
	b>>name>>pic>>id>>di>>uniq;
	n.name=name.container;
	n.pic=pic.obj;
	n.id=id.obj;
	n.disable_invite=di.obj;
	n.uniq=uniq.obj;

	return b;
}

oscar_buffer & operator>>(oscar_buffer&b, user_state& n)
{
	DWORD_LE c;
	b>>c;
	n.channel=c.obj;
	b>>n.status>>n.nick;
	return b;
}
*/

void get_question()
{//
    
//	printf("qc=%d\n",questions_count);
    question_id=(rand() % questions_count)+1;
//	question_id=1;
//	printf("id=%d qc=%d\n",question_id,questions_count);
    vector<string> v=dbh->select_1_rowQ((QUERY)"select question,answer from questions where id=?"<<question_id);
    if (v.size()!=2) throw cError("select failed.");
    question=v[0];
    answer=v[1];
    
}

void ask_question()
{//
    
    action("- <b>"+question+"</b> ("+itostring(answer.size())+" букв)");
//	action("N"+itostring(question_id)+": <b>"+question+"</b> ("+itostring(answer.size())+" букв)");
//	privmsg("Mazar",answer);
//	privmsg("South",answer);
//	privmsg("Arsenic",answer);
    
}

void check_state()
{//
    
    time_t t=time(NULL);
    if (game_started) {
        if (t>=next_question_time && !question_asked) {
            get_question();
            hint1=false;
            hint2=false;
            question_asked=true;
            question_asked_time=time(NULL);
            answers_count=0;
            ask_question();
        }
        if (question_asked && t>=question_asked_time+HINT_1_TIME && !hint1) {
            hint1=true;
            if (answer.size()>1) {
                string hint=answer.substr(0,1);
                action("Подсказка: <b>"+hint+"</b>");
            }
        }
        if (question_asked && t>=question_asked_time+HINT_2_TIME && !hint2) {
            hint2=true;
            if (answer.size()>1) {
                int ll=answer.size() / 3;
                if (ll<2 && answer.size()>1) ll=2;
                string hint=answer.substr(0,ll);
                action("Подсказка: <b>"+hint+"</b>");
            }
        }
        if (question_asked && t>=question_asked_time+TIME_LIMIT) {
            question_asked=false;
            next_question_time=t+QUESTION_PERIOD;
            if (answers_count==0) {
                game_started=false;
                action("Время истекло. Следущего вопроса не будет, т.к. количество ответов на предыдущий вопрос=0. Для начала викторины используйте команду !старт");
            } else {
                action("Время истекло. Сдедующий вопрос через "+itostring(QUESTION_PERIOD)+" секунд.");
            }
        }
    }
    
}



void check_answer(const string &nick,const string &login,const string &ans)
{//
    
    if (!question_asked) return;
    if (nick==params["NICKNAME"]) return;
    answers_count++;
    user *u;
    if (users.find(nick)==users.end()) {
        printf("nick not found\n");
//		privmsg(nick,"Пожалуйста перезайдите в игру");
        sock.response("EUI "+nick);
        return;
    }
    u=users[nick];
//	logErr("user %s has %2.3f credits\n",nick.c_str(),float(u->credits));
#ifdef WITH_BANK
    if (u->credits<=0) {
        privmsg(nick,"У Вас нет кредитов и Вы не можете играть в игру.");
        return;
    }
#endif
    if (strupper(answer)==strupper(ans)) {
        printf("answer ok nick=%s\n",nick.c_str());

        question_asked=false;
        question_asked=false;
        int sec=time(NULL)-question_asked_time;
        int score=atoi(dbh->select_1Q((QUERY)"select score from rating where login='?'"<<u->login));
        if (!score) {
            score=1;
            dbh->real_queryQ((QUERY)"insert into rating (login,score) values ('?',1)"<<u->login);
        } else {
            score++;
            dbh->real_queryQ((QUERY)"update rating set score=? where login='?'"<<score<<u->login);
        }
        next_question_time=time(NULL)+QUESTION_PERIOD;

#ifdef WITH_BANK
        double inc_val=bank;
#else
        double inc_val=0.01;
#endif
        action("Молодец "+nick+", правильный ответ - <b>"+answer+"</b> был дан за "+itostring(sec)+" сек. "+nick+" отвечает правильно на "+itostring(score)+" вопросов и зарабатывает "+ftostring(inc_val)+" кредитов. Следущий вопрос через "+itostring(QUESTION_PERIOD)+" сек.");
//		sock.response("CTTU "+nick+" "+ftostring(inc_val)+"\n");
        sock.response("CTTU "+nick+" "+ftostring(inc_val)+" quiz_prize "+itostring(1));
    } else {
//		cc+=0.01;
    }
    
}

void do_greeting(const string &nick,const string &login, int gender);

void on_greeting(const string &nick,const string &login)
{//
    
    if (nick==params["NICKNAME"]) return;
    if (users.find(nick)==users.end()) {
        sock.response("EUI "+nick);
    } else {
        printf("founded in exists\n");
        user *u=users.find(nick)->second;
        do_greeting(nick,u->login,u->gender);
    }
    
}

void do_greeting(const string &nick,const string &login,int gender)
{//
    
    int score=atoi(dbh->select_1Q((QUERY)"select score from rating where login='?'"<<login));
    if (!score) {
        privmsg(nick,"<u>Правила игры</u>: Кто быстрее ответил, тому плюсуется очко. Очки суммируются на тот login, под которым Вы сейчас находитесь. Наберите в канале <u>!help</u> для получения справки о коммандах.");
        channelmsg(nick+", Привет. Ты ни на один вопрос не ответил(а). Удачи!");
    } else {
        string pl=dbh->select_1Q((QUERY)"select count(*) from rating where score>=?"<<score);
        string suff="";
        if (gender==0) suff="о";
        if (gender==2) suff="а";
        channelmsg(nick+", Привет. Ты ответил"+suff+" правильно на "+itostring(score)+" вопросов, и занимаешь "+pl+"-е место. Удачи!");
    }
    
}

void do_help(const string &nick)
{//
    
    privmsg(nick,"Помощь:<br>"
            "<u>!старт</u> - начать игру<br>"
            "<u>!вон</u> - Ваше место и кол-во очков<br>"
            "<u>!вон [ник]</u> Место и кол-во очков у [ник]<br>"
            "<u>!вопрос</u> - повтор вопроса<br>"
            "<u>!top</u> - TOP 10 самых крутых игроков");
    
}

void process_command(c_command &cmd)
{//
    
    string cdb=params["CHAT_DB_NAME"];
    string msg=cmd.msg;
    check_for_flood(cmd);
//	printf("cmd=%s\n",cmd.cmd.c_str());
    if (cmd.cmd=="JOIN") {
        on_greeting(cmd.fromnick,cmd.user);
        return;
    }
    if (cmd.cmd=="NICK") {
        user *u;
        if (users.find(cmd.fromnick)==users.end()) return;
        u=users[cmd.fromnick];
        users[cmd.cmd]=u;
        return;
    }
#ifdef WITH_BANK
    if (cmd.cmd=="UTTC_REPLY") {
        vector<string> pr=splitTOK(":",cmd.msg);
        printf("increment for %s from %s\n",pr[0].c_str(),pr[1].c_str());
        bank+=0.01;
        if (users.find(pr[0])!=users.end()) {
            user *u=users[pr[0]];
            u->credits=atof(pr[1].c_str());
        }
    }
#endif
    if (cmd.cmd=="CTTU_REPLY") {
        vector<string> pr=splitTOK(":",cmd.msg);
        printf("increment for %s from %s\n",pr[0].c_str(),pr[1].c_str());
#ifdef WITH_BANK
        bank+=0.01;
        if (users.find(pr[0])!=users.end()) {
            user *u=users[pr[0]];
            u->credits=atof(pr[1].c_str());
        }
#endif
    }
    if (cmd.cmd=="EUI_REPLY") {
        vector<string> pr=splitTOK(":",cmd.msg);
        if (pr.size()!=7) return;
        string nick=pr[0];
//		int pz=nick.find
        string login=pr[1];
        int gender=atoi(pr[2]);
        bool unreg=atoi(pr[3]);
#ifdef WITH_BANK
        double cred=atof(pr[5].c_str());
#endif
//		logErr("");
        if (unreg) {
            privmsg(nick,"Т.к. Вы незарегистрированный пользователь Вы не можете играть в викторину...");
            return;
        }
        bool ok=false;
        for (typeof(users.begin()) i=users.begin();i!=users.end();i++) {
            if (i->second->login==login) {
                printf("found old\n");
                users[nick]=i->second;
                ok=true;
            }
        }
        if (!ok) {
//			logErr("greating new user %s\n",login.c_str());
            user* u=new user;
            users[nick]=u;
        }
        users[nick]->login=login;
        users[nick]->gender=gender;
        users[nick]->unreg=unreg;
        do_greeting(nick,login,gender);
    }
    if (cmd.cmd=="PRIVMSG") {
        if (strex(msg,"!help") || strex(msg,"!хелп") || strex(msg,"!помощь")) {
            do_help(cmd.fromnick);
            return;
        }
        if (strex(msg,"!вон") || strex(msg,"!djy")) {
            string nick;
            string login;
            if (msg.size()==4 || msg.size()==5) {
                nick=cmd.fromnick;
//				login=cmd.user;
            } else {
                if (msg.size()>5) {
                    nick=msg.substr(5,msg.size()-5);
                }
            }
            string uid=dbh->select_1Q((QUERY)"select ?.nicks.uid from ?.nicks where ?.nicks.str_nick='?'"<<cdb<<cdb<<cdb<<str_nick(nick));
//			printf("'%s' - '%s'\n",str_nick(nick).c_str(),login.c_str());
            login=dbh->select_1Q((QUERY)"select login from ?.user_profiles where refid='?'"<<cdb<<uid);
            string score;
            if (login.size()) {
                score=dbh->select_1Q((QUERY)"select score from rating where login='?'"<<login);
            }
            if (score.size()) {
                string pl=dbh->select_1Q((QUERY)"select count(*) from rating where score>=?"<<score);
                privmsg(cmd.fromnick,"У пользователя "+nick+" <b>"+score+"</b> правильных ответов и он занимает <b>"+pl+"</b>-е место в рейтинге");
            } else {
                privmsg(cmd.fromnick,"В базе нет игрока с ником "+nick);
            }
            return;
        }
        if (strex(msg,"!top") || strex(msg,"!топ")) {
            vector<vector<string> > v=dbh->execQ((QUERY)
                                                 "select ?.user_sets.last_nick,?.user_profiles.refid,rating.score from ?.user_profiles,rating,?.user_sets "
                                                 "where rating.login=?.user_profiles.login and ?.user_profiles.refid=?.user_sets.refid  order by rating.score desc limit 20"<<cdb<<cdb<<cdb<<cdb<<cdb<<cdb<<cdb);

            /*			vector< vector<string> > v=dbh->execQ((QUERY)
            			"select user_sets.lstate, quiz.rating.score from user_sets,quiz.rating,user_profiles
            			 where quiz.rating.login=user_profiles.login and user_profiles.refid=user_sets.refid order by quiz.rating.score desc limit 20"<<cdb<<cdb<<cdb);*/
            string repl="TOP 10 Самый лучших игроков:";
            for (unsigned int i=0;i<v.size();i++) {
                repl+="<br>";
                if (v[i].size()==3) {
                    /*					oscar_buffer b;
                    					b.Pack(v[i][0]);
                    					user_state st;
                    					b>>st;*/
                    repl+=itostring(i+1)+": <u>"+v[i][0]+"</u> - "+v[i][2];
                }
            }
            privmsg(cmd.fromnick,repl);
            return;
        }
        if (strex(msg,"!start") || strex(msg,"!старт") || strex(msg,"!cnfhn") || strex(msg,"!ыефке")) {
            if (!game_started) {
                game_started=true;
                action("Начинается игра \"Викторина\". Следущий вопрос через "+itostring(QUESTION_PERIOD)+" сек.");
                next_question_time=time(NULL)+QUESTION_PERIOD;
            }
            return;
        }
        if (strex(msg,"!quest") || strex(msg,"!вопрос")) {
            if (question_asked) ask_question();
            return;
        }
        if (!cmd.ppriv && cmd.tonick!=params["NICKNAME"]) check_answer(cmd.fromnick,cmd.user,cmd.msg);
    }
    
}

