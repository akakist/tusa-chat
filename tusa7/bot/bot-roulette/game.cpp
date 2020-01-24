#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "c_conn.h"
#include "errs.h"
#include "config.h"
#include "utils.h"
#include "misc.h"
#include "mysql_extens.h"
#include <vector>
#include "roulette.h"
#include "antiflood.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define ACCEPTING_STAKES_TIME 60
#define STAKES_STOPPED_TIME 5
#define RUNNING_WHEEL_TIME 5
#define THROW_BALL_TIME 5
#define NEXT_GAME_TIME 7
#define HINT_1_TIME	15

time_t next_stoptime=0;

bool game_started=false;
time_t next_game_time=0;
time_t next_hint_time=0;

bool hint1=false;
bool hint2=false;
enum GAME_STATE {
    STATE_UNDEF=0,
    ACCEPTING_STAKES=1,
    STAKES_STOPPED,
    RUNNING_WHEEL,
    THROW_BALL,
    WAIT_NEXT_GAME,
    RETURNING_VINS

};
GAME_STATE game_state=STATE_UNDEF;
int stakes_count=0;

vector<string> hints_ACCEPTING_STAKES;
unsigned int __id=0;

map<unsigned int,string> cttu_nicks;
unsigned int next_id()
{
    return ++__id;
}
string get_f22(double dd)
{
    char s[100];
    snprintf(s, sizeof(s) - 1, "%2.2f", dd);
    return s;

}

unsigned int get_random()
{

    FILE *f=fopen("/dev/urandom","rb");
    if (f==NULL)
    {
        logErr("failed open urandom");
        exit(1);
    }
    unsigned int n;
    fread(&n,1,sizeof(n),f);
    fclose(f);
    return n;
}
void check_state()
{
    
    time_t t=time(NULL);
    if (game_started) {

        if (game_state==WAIT_NEXT_GAME && time(NULL)>next_stoptime && next_stoptime!=0)
        {
            action("Начинается новая игра... Делаем ставки!");
            next_stoptime=0;
            game_state=STATE_UNDEF;
            stakes_count=0;
            next_hint_time=0;
        }
        if (game_state==THROW_BALL && time(NULL)>next_stoptime && next_stoptime!=0)
        {
            int no=get_random()%37;
            string no_s;
            if (no!=0)
                no_s=itostring(no);
            else no_s="ЗЕРО";
            action("Выпалo  <b>"+no_s+"</b>");
            bool is_zero=no==0;
            bool is_odd=no%2==1;
            bool is_even=no%2==0;
            bool is_1p=no>=1 && no<=18;
            bool is_2p=no>=19 && no<=36;
            bool is_1d=no>=1 && no<=12;
            bool is_2d=no>=13 && no<=24;
            bool is_3d=no>=25 && no<=36;

            if (is_zero)
            {
                is_odd=false;
                is_even=false;
                is_1p=false;
                is_2p=false;
                is_1d=false;
                is_2d=false;
                is_3d=false;

            }
            vector<vector<string> > v=dbh->exec("select id,login,summa,tip,number from stawki where done='0'");
            map<string,double> tot_stawki;
            map<string,double> tot_wins;
            for (unsigned i=0;i<v.size();i++)
            {
                if (v[i].size()==5)
                {
                    string id=v[i][0];
                    string login=v[i][1];
                    string summa=v[i][2];
                    string tip=v[i][3];
                    string number=v[i][4];
                    if (users.count(login))
                    {
                        if (tot_stawki.count(login)) tot_stawki[login]+=atof(summa.c_str());
                        else tot_stawki.insert(make_pair(login,atof(summa.c_str())));

                        dbh->real_queryQ((QUERY)"update stawki set done='1' where id=?"<<id);
                        double win=0;
                        if (tip=="num")
                        {
                            if (no==atoi(number))
                            {
                                if (tot_wins.count(login)) tot_wins[login]+=atof(summa.c_str())*36;
                                else tot_wins.insert(make_pair(login,atof(summa.c_str())*36));

                                win=atof(summa.c_str())*36;

                            }
                        }
                        if ((tip=="odd" && is_odd)||(tip=="even" && is_even) || (tip=="p1" && is_1p) || (tip=="p2" && is_2p) )
                        {
                            if (tot_wins.count(login)) tot_wins[login]+=atof(summa.c_str())*2;
                            else tot_wins.insert(make_pair(login,atof(summa.c_str())*2));
                            win=atof(summa.c_str())*2;
                        }
                        if ((tip=="d1" && is_1d)||(tip=="d2" && is_2d) || (tip=="d3" && is_3d))
                        {
                            if (tot_wins.count(login)) tot_wins[login]+=atof(summa.c_str())*3;
                            else tot_wins.insert(make_pair(login,atof(summa.c_str())*3));
                            win=atof(summa.c_str())*3;
                        }

                        if (win>0)
                        {
                            dbh->real_queryQ((QUERY)"insert into wins (login,tip,summa,number,winnumber,winsumma,dt) values ('?','?',?,?,?,?,NOW())"
                                             <<login<<tip<<atof(summa.c_str())<<atoi(number)<<no<<win
                                            );
                        }


                    }
                }

            }
            if (tot_wins.size())
            {
                string swin="<b>Выигрыши</b>: ";
                for (typeof(tot_wins.begin())i=tot_wins.begin();i!=tot_wins.end();i++)
                {
                    if (users.count(i->first))
                    {
                        swin+="<b>"+users[i->first]->nick+":"+get_f22(i->second)+"</b> ";
                        privmsg(users[i->first]->nick,"Поздравляю, вы выиграли "+ftostring(i->second)+" кред");
                        unsigned int id=next_id();
                        cttu_nicks[id]=users[i->first]->nick;
                        sock.response((string)"CTTU "+users[i->first]->nick+" "+ftostring(i->second)+" r_win "+itostring(id));
                    }
                }
                action(swin);
            }
            else action("К сожалению никто не выиграл..");


            if (tot_stawki.size())
            {
                for (typeof(tot_stawki.begin())i=tot_stawki.begin();i!=tot_stawki.end();i++)
                {
                    if (users.count(i->first))
                    {
                        if (tot_wins.count(i->first)==0)
                        {
                            privmsg(users[i->first]->nick,"К сожалению вы проиграли, попробуйте еще.");
                        }
                    }
                }
            }

            action("Игра закончена. Следующая игра через <b>"+itostring(NEXT_GAME_TIME)+"</b> сек.");
            game_state=WAIT_NEXT_GAME;
            next_stoptime=time(NULL)+NEXT_GAME_TIME;
        }
        if (game_state==RUNNING_WHEEL && time(NULL)>next_stoptime && next_stoptime!=0)
        {
            action("Бросаю шарик....");
            game_state=THROW_BALL;
            next_stoptime=time(NULL)+THROW_BALL_TIME;

        }
        if (game_state==STAKES_STOPPED && time(NULL)>next_stoptime && next_stoptime!=0)
        {
            action("Раскручиваю рулетку....");
            game_state=RUNNING_WHEEL;
            next_stoptime=time(NULL)+RUNNING_WHEEL_TIME;
        }
        if (game_state==ACCEPTING_STAKES && time(NULL)>next_stoptime && next_stoptime!=0)
        {
            action((string)"Прием ставок завершен. Поставить или снять ставку уже нельзя. Рулетку начну крутить через <b>"+itostring(STAKES_STOPPED_TIME) +"</b> сек." );
            next_stoptime=0;
            game_state=STAKES_STOPPED;
            next_stoptime=time(NULL)+STAKES_STOPPED_TIME;
            vector<string> v=dbh->select_1_column("select login from stawki where done!='1'");
            //map<string,string> login2nick;
            set<string> vv;
            for (unsigned i=0;i<v.size();i++)
            {
                if (users.count(v[i]))
                {
                    vv.insert(users[v[i]]->nick);
                }

            }
            if (vv.size()==1)
            {
                action((string)"Играeт <b>"+*vv.begin()+"</b>");
            }
            else if (vv.size()>1)
            {
                vector<string>vz;
                for (typeof(vv.begin())i=vv.begin();i!=vv.end();i++)
                    vz.push_back(*i);
                action((string)"Играют <b>"+join(", ",vz)+"</b>.");
            }
        }
        if (stakes_count==0)
        {
            game_state=ACCEPTING_STAKES;
        }
        //printf("next_stoptime %d GS %d stakes_count %d\n",next_stoptime,game_state,stakes_count);
        if (stakes_count!=0 && game_state==ACCEPTING_STAKES && next_stoptime==0)
        {
            action((string)"Первая ставка сделана, прием ставок завершается через <b>"+itostring(ACCEPTING_STAKES_TIME)+"</b> сек.");
            next_stoptime=time(NULL)+ACCEPTING_STAKES_TIME;
        }
        if (game_state==ACCEPTING_STAKES)
        {
            if (next_hint_time==0)
                next_hint_time=time(NULL)+HINT_1_TIME;
            if (t>next_hint_time && game_state==ACCEPTING_STAKES)
            {
                next_hint_time=time(NULL)+HINT_1_TIME;
                if (hints_ACCEPTING_STAKES.size()==0)
                {
                    printf("hints_ACCEPTING_STAKES.size()==0");
                    exit(1);
                }
                string s=hints_ACCEPTING_STAKES[rand()%hints_ACCEPTING_STAKES.size()];
                if (next_stoptime!=0 && rand()%2==0)
                    s+=" Прием ставок завершается через <b>"+itostring(next_stoptime-time(NULL)) +"</b> сек.";
                action(s);
            }

        }
    }
    
}




void do_greeting(const string &nick,const string &login, int gender);

void on_greeting(const string &nick,const string &login)
{
    
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
{
    printf("do_greeting");
    privmsg(nick,"Крупье приветствует Вас. <u>Правила игры</u> здесь: http://tusovka.tomsk.ru/html/help/roulette.html   Наберите в канале <u>!help</u> для получения справки о коммандах.");
}

void do_help(const string &nick)
{
    
    privmsg(nick,"Помощь:<br>"
            "<u>!старт| !start</u> - начать игру<br>"
            "Ставки:"
            "<u>!номер сумма</u> - Поставить сумму на номер, пример '!33,1-5,12 0.5'. Диапазон от 0 (зеро) до 36<br>"
            "<u>!odd !even !чет !нечет сумма</u> Поставить сумму на чет или нечет<br>"
            "<u>!p1 !п1 !p2 !п2 сумма</u> Поставить сумму на первую или вторую половину. От 1 до 18  или с 19 до 36<br>"
            "<u>!d1 !d2, !d3 !д1 !д2 !д3  сумма</u> Поставить сумму на первую, вторую или третью дюжину. 1-12, 13-24,25-36<br>"
            "<u>!ставки !stakes</u> - вывести свои ставки в текущей игре<br>"
            //	    "<u>!отмена !cancel</u> - отменить все ставки<br>"
           ) ;

    
}
void do_num_stawka(const string &nick, const string &msg)
{
    if (game_state!=ACCEPTING_STAKES)
    {
        privmsg(nick,"Извините, ставки уже не принимаются.");
        return;
    }
    user *u=NULL;
    if (users.find(nick)==users.end()) {
        printf("nick not found\n");
        privmsg(nick,"Пожалуйста перезайдите в игру, либо повторите ставку.");
        sock.response("EUI "+nick);
        return;
    }
    u=users[nick];

    //    printf("do_num_stawka %s c %s sum %s\n",nick.c_str(),code.c_str(),summa.c_str());


    set<unsigned int> nums;
    vector<string> vV=splitTOK(" ",msg);
    if (vV.size()<2)
    {
        printf("invalid format do_num_stawka '%s'",msg.c_str());
        privmsg(nick,"Неправильный формат ставки.");
        return;
    }
    string summa=vV[1];
    string nsum;
    for (unsigned i=0;i<summa.size();i++)
    {
        if (summa[i]==',')nsum+='.';
        else nsum+=summa[i];
    }
    summa=nsum;
    if (atof(summa.c_str())<=0)
    {
        printf("invalid format do_num_stawka '%s'",msg.c_str());
        privmsg(nick,"Неправильный формат ставки.");
        return;
    }
    vector<string> vz=splitTOK("!,",vV[0]);
    for (unsigned int i=0;i<vz.size();i++)
    {
        vector<string> vm=splitTOK("-",vz[i]);
        if (vm.size()==1)
        {
            if (atoi(vm[0])<=36)
                nums.insert(atoi(vm[0]));
        }
        else if (vm.size()==2)
        {
            int start=atoi(vm[0]);
            int end=atoi(vm[1]);
            if (end>36)
            {
                privmsg(nick,"Неправильный формат ставки. Максимальное число не может превышать 36.");
                return;

            }
            if (start<0)
            {
                privmsg(nick,"Неправильный формат ставки. Числа должны быть положительными.");
                return;

            }
            if (start>end)
            {
                privmsg(nick,"Неправильный формат ставки. Первое число должно быть меньше последнего.");
                return;

            }
            for (int j=start;j<=end;j++)
            {
                nums.insert(j);
            }
        }
        else
        {
            privmsg(nick,"Неправильный формат ставки.");
            return;
        }
    }
    pay p;
    p.nums=nums;
    p.type="num";
    p.id=next_id();

    p.summa=atof(summa.c_str());
    if (p.summa<=0) {
        privmsg(nick,"Неправильный формат ставки.");
        return;
    }
    if (p.summa/p.nums.size()<0.01)
    {
        privmsg(nick,"Слишком маленькая ставка на одно число. Минимальная ставка должна быть больше 0.01 кр");
        return;
    }
    u->pays[p.id]=p;
    char s[300];

    snprintf(s,sizeof(s),"UTTC %s %f get_roulette_num %d",nick.c_str(),p.summa,p.id);
    sock.response(s);
    return;

}
void do_odd_even_stawka(const string& type,const string &nick,const string &msg)
{
    if (game_state!=ACCEPTING_STAKES)
    {
        privmsg(nick,"Извините, ставки уже не принимаются.");
        return;
    }

    user *u=NULL;
    if (users.find(nick)==users.end()) {
        printf("nick not found\n");
        privmsg(nick,"Пожалуйста перезайдите в игру, либо повторите ставку.");
        sock.response("EUI "+nick);
        return;
    }
    u=users[nick];
    vector<string> v=splitTOK(" ",msg);
    if (v.size()>1)
    {

        pay p;
        p.type=type;
        p.id=next_id();
        string summa=v[1];

        string nsum;
        for (unsigned i=0;i<summa.size();i++)
        {
            if (summa[i]==',')nsum+='.';
            else nsum+=summa[i];
        }
        summa=nsum;

        p.summa=atof(summa.c_str());
        if (p.summa<=0)
        {
            privmsg(nick,"Неправильный формат ставки.");
            return;
        }
        u->pays[p.id]=p;
        char s[300];
        snprintf(s,sizeof(s),"UTTC %s %f get_roulette_%s %d",nick.c_str(),p.summa,type.c_str(),p.id);
        sock.response(s);
        return;

    }
    else
    {
        privmsg(nick,"Неправильный формат ставки.");
    }

}
void do_dozen_stawka(c_command &cmd)
{

}
void do_polowina_stawka(c_command &cmd)
{

}
void do_UTTC_REPLY(c_command &cmd)
{
    vector<string> pr=splitTOK(":",cmd.msg);
    if (pr.size()!=6)
    {
        printf("bad UTTC_REPLY format %s",cmd.msg.c_str());
    }
    string nick=pr[0];
    string result=pr[1];
    string summa=pr[2];
    string cookie=pr[3];
    string from_reminder=pr[4];
    if (result!="OK")
    {
        if (summa=="Not_enough_credits")
            privmsg(nick,"У вас недостаточно кредитов на счету, ставка не принята.");
        else
            privmsg(nick,"Произошла непонятная ошибка, ставка не принята.");
    }
    else
    {
        stakes_count++;
        unsigned int id=atoi(cookie);

        user *u=NULL;
        if (users.find(nick)==users.end()) {
            printf("nick not found\n");
            privmsg(nick,"Пожалуйста перезайдите в игру, либо повторите ставку.");
            sock.response("EUI "+nick);
            return;
        }
        u=users[nick];
        if (u->pays.count(id)==0)
        {
            privmsg(nick,"Ошибка ставка не найдена.");
            return;
        }
        pay p=u->pays[id];
        if (atof(summa.c_str())!=p.summa)
        {
            privmsg(nick,"Не совпадают суммы.");
            return;
        }
        if (p.type=="num")
        {

            //double sum=atof(summa.c_str());
            double sum1=p.summa/p.nums.size();
            vector<string> snums;

            for (typeof(p.nums.begin())i=p.nums.begin();i!=p.nums.end();i++)
            {
                snums.push_back(itostring(*i));
                dbh->real_queryQ((QUERY)"insert into stawki (login,tip,summa,number,dt) values ('?','num',?,?,NOW())"<<u->login<<sum1<<*i);
            }
            if (p.nums.size()==1)
            {
                action("<b>"+nick+"</b> поставил(а) на число <b>"+join(",",snums)+" "+get_f22(sum1)+"</b> кред");
                privmsg(nick,"Принята ставка на число "+join(",",snums)+" по "+get_f22(sum1)+" кред. Остаток на счету "+get_f22(atof(from_reminder.c_str()))+" кред.");

            }
            else
            {
                action("<b>"+nick+"</b> поставил(а) на числа <b>"+join(",",snums)+" по "+get_f22(sum1)+"</b> кред.");
                privmsg(nick,"Принята ставка на числа "+join(",",snums)+" по "+get_f22(sum1)+" кред. Остаток на счету "+get_f22(atof(from_reminder.c_str()))+" кред.");
            }

            u->pays.erase(p.id);

        }
        else if (p.type=="odd" || p.type=="even" || p.type=="p1" || p.type=="p2" || p.type=="d1" || p.type=="d2" || p.type=="d3")
        {

            double sum=p.summa;
            string tt;
            if (p.type=="odd") tt="нечетное";
            else if (p.type=="even") tt="четное";
            else if (p.type=="p1") tt="первую половину";
            else if (p.type=="p2") tt="вторую половину";
            else if (p.type=="d1") tt="первую дюжину";
            else if (p.type=="d2") tt="вторую дюжину";
            else if (p.type=="d3") tt="третью дюжину";
            else
            {
                privmsg(nick,"неправильная ставка" +p.type);
            }
            dbh->real_queryQ((QUERY)"insert into stawki (login,tip,summa,dt) values ('?','?',?,NOW())"<<u->login<<p.type<<sum);
            action("<b>"+nick+"</b> поставил(а) на <b>"+tt+" "+get_f22(sum)+"</b> кред.");
            privmsg(nick,(string)"Принята ставка на <b>"+tt+"</b> сумма <b>"+get_f22(sum)+"</b> кред. Остаток на счету "+get_f22(atof(from_reminder.c_str()))+" кред.");
            u->pays.erase(p.id);
        }
    }

}
void do_stawki(c_command &cmd)
{
    if (game_state!=ACCEPTING_STAKES)
    {
        privmsg(cmd.fromnick,"Извините, ставки уже не принимаются.");
        return;
    }
    user *u=NULL;
    if (users.find(cmd.fromnick)==users.end()) {
        printf("nick not found\n");
        privmsg(cmd.fromnick,"Пожалуйста перезайдите в игру, либо повторите ставку.");
        sock.response("EUI "+cmd.fromnick);
        return;
    }
    u=users[cmd.fromnick];
    vector<vector<string> > v=dbh->execQ((QUERY)"select id, summa,tip,number from stawki where login='?' and done='0'"<<u->login);
    for (unsigned i=0;i<v.size();i++)
    {
        if (v[i].size()==4)
        {
            string summa=v[i][1];
            string tip=v[i][2];
            string num=v[i][3];
            if (tip=="num")
            {
                char s[200];
                snprintf(s,sizeof(s),"%s на номер %s",summa.c_str(),num.c_str());
                privmsg(cmd.fromnick,s);
            }
            else if (tip=="odd")
            {
                char s[200];
                snprintf(s,sizeof(s),"%s на нечетное",summa.c_str());
                privmsg(cmd.fromnick,s);
            }
            else if (tip=="even")
            {
                char s[200];
                snprintf(s,sizeof(s),"%s на четное",summa.c_str());
                privmsg(cmd.fromnick,s);
            }

        }
    }

}

void load_messages()
{
    //	msgs.clear();
    if (hints_ACCEPTING_STAKES.size()==0)
    {
        FILE *f = fopen("./hints_ACCEPTING_STAKES", "r");
        if (!f) {
            logErr("---Error: mafia.messages not found!");
            exit(1);
        }
        string data;
        while (!feof(f)) {
            char s[40000];
            int z=fread((void*) &s, 1, 990,f);
            s[z]=0;
            data+=s;
        }
        hints_ACCEPTING_STAKES=splitTOK("\r\n",data);
    }
}

void process_command(c_command &cmd)
{
    
    string cdb=params["CHAT_DB_NAME"];
    string msg=cmd.msg;

    load_messages();

    check_for_flood(cmd);
    //	printf("cmd=%s\n",cmd.cmd.c_str());
    if (cmd.cmd=="JOIN") {
        printf("on join");
        on_greeting(cmd.fromnick,cmd.user);
        return;
    }
    if (cmd.cmd=="NICK") {
        user *u;
        if (users.find(cmd.fromnick)==users.end()) return;
        u=users[cmd.fromnick];
        users[cmd.cmd]=u;
        u->nick=cmd.fromnick;
        return;
    }

    if (cmd.cmd=="UTTC_REPLY") {
        do_UTTC_REPLY(cmd);

    }

    if (cmd.cmd=="CTTU_REPLY") {
        vector<string> pr=splitTOK(":",cmd.msg);
        if (pr.size()==6)
        {
            string cookie=pr[3];
            string treminder=pr[5];
            if (cttu_nicks.count(atoi(cookie)))
            {
                privmsg(cttu_nicks[atoi(cookie)],"У вас на счету "+treminder+" кред.");
            }
        }
        printf("increment for %s from %s\n",pr[0].c_str(),pr[1].c_str());
    }
//    printf("\n\ncmd=%s\n\n",cmd.cmd.c_str());
    if (cmd.cmd=="EUI_REPLY") {
        vector<string> pr=splitTOK(":",cmd.msg);
        printf("eui_relplu size=%d\n",pr.size());
        if (pr.size()!=7) return;
        string nick=pr[0];
        //		int pz=nick.find
        string login=pr[1];
        int gender=atoi(pr[2]);
        bool unreg=atoi(pr[3]);
        //		logErr("");
        if (unreg) {
            privmsg(nick,"Т.к. Вы незарегистрированный пользователь Вы не можете играть...");
            return;
        }
        bool ok=false;
        for (typeof(users.begin()) i=users.begin();i!=users.end();i++) {
            if (i->second->login==login) {
                printf("found old\n");
                users[nick]=i->second;
                users[nick]->nick=nick;
                users[login]=i->second;
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
        users[nick]->nick=nick;
        users[login]=users[nick];
        //				logErr("users[nick (%s) ]->credits %f", nick.c_str(),float(users[nick]->credits));
        //		printf("n=%s l=%s\n",nick.c_str(),login.c_str());
        do_greeting(nick,login,gender);
    }
    if (cmd.cmd=="PRIVMSG") {


        if (strex(msg,"!help") || strex(msg,"!хелп") || strex(msg,"!помощь")) {
            do_help(cmd.fromnick);
            return;
        }

        printf("msg '%s'",msg.c_str());
        if (msg.size()>2)
        {
            if (msg[0]=='!' && isdigit(msg[1]))
                do_num_stawka(cmd.fromnick,msg);
        }

        if ((strex(msg,"!odd")||strex(msg,"!неч")))
        {
            do_odd_even_stawka("odd",cmd.fromnick,msg);
        }
        if ((strex(msg,"!eve")||strex(msg,"!чет")))
        {
            do_odd_even_stawka("even",cmd.fromnick,msg);
        }
        if ((strex(msg,"!d1")||strex(msg,"!д1")))
        {
            do_odd_even_stawka("d1",cmd.fromnick,msg);
        }
        if ((strex(msg,"!d2")||strex(msg,"!д2")))
        {
            do_odd_even_stawka("d2",cmd.fromnick,msg);
        }
        if ((strex(msg,"!d3")||strex(msg,"!д3")))
        {
            do_odd_even_stawka("d3",cmd.fromnick,msg);
        }
        if ((strex(msg,"!p1")||strex(msg,"!п1")))
        {
            do_odd_even_stawka("p1",cmd.fromnick,msg);
        }
        if ((strex(msg,"!p2")||strex(msg,"!п2")))
        {
            do_odd_even_stawka("p2",cmd.fromnick,msg);
        }


        if ((strex(msg,"!stak")||strex(msg,"!став")))
        {
            do_stawki(cmd);

        }



        if (strex(msg,"!start") || strex(msg,"!старт") || strex(msg,"!cnfhn") || strex(msg,"!ыефке")) {
            if (!game_started) {
                game_started=true;
                action("Начинается игра <b>\"Рулетка\"</b>. Делайте ставки господа.");

                //next_game_time=time(NULL)+GAME_PERIOD;
            }
            return;
        }
    }
    
}

