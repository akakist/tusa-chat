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
#include "cmd.h"
#include <signal.h>
#include "girl.h"

cMYSQL *dbh;

vector<string> user_msg;
vector<string> simple_msg;
vector<string> greeting_msg;
void onterm(int signum);

void read_messages()
{

    user_msg=dbh->select_1_column("select msg from unknow");
    simple_msg=dbh->select_1_column("select answer from simplemsg");
    greeting_msg=dbh->select_1_column("select answer from greetingmsg");
}

void onterm(int signum)
{
    logErr("Terminating");
    printf("Terminating\n");
    if (signum==1) {
        load_config();
        read_messages();
        logErr("Config reloaded.");
    } else {
        signal(SIGPIPE,SIG_IGN);
        signal(SIGABRT,SIG_IGN);
        signal(SIGTERM,SIG_IGN);
        signal(SIGINT,SIG_IGN);
        signal(SIGSEGV,SIG_IGN);
        signal(SIGFPE,SIG_IGN);
        signal(SIGQUIT,SIG_IGN);
        signal(SIGILL,SIG_IGN);
        signal(SIGBUS,SIG_IGN);
        signal(SIGHUP,SIG_IGN);

        string out;
        printf("du");
        string fn;
        fn = (string) "TERM." + itostring (time (NULL));
        if (out.size () ||true)
        {
            out = "Terminating on SIGNAL " + itostring (signum) + "\n" + out;

            FILE *f = fopen (fn.c_str (), "wb");
            if (f)
            {
                fprintf (f, "%s", out.c_str ());
                fclose (f);
            }
        }


        logErr("Got signal %d, terminating...",signum);
//		unlink("girl.pid");
        exit(1);
    }
}


int main(int argc,char* argv[])
{

    printf("BOT Girl v1.0.0 (C) www.belialov.com\n");
    if (argc>1) {
        if (strcmp(argv[1],"-d")==0) {
            printf("Continuing as daemon\n");
            if (fork()) exit(1);
        }
        if (strcmp(argv[1],"--help")==0) {
            printf("\t -d - to run as deamon\n");
            exit(1);
        }
    }


//	FILE *pid=fopen("girl.pid","r");
//	if(pid){
//		fclose(pid);
//		logErr("Bot is alredy running!");
//		printf("Bot is alredy running!\n");
//		exit(1);
//	}
//#ifndef DEBUG
//	if(fork()) exit(1);
//#endif
//	pid=fopen("girl.pid","w");
//	if(!pid){
//		logErr("unable to create PID file girl.pid!");
//		exit(1);
//	}
//	fprintf(pid,"%d",getpid());
//	fclose(pid);

    signal(SIGPIPE,SIG_IGN);
    signal(SIGABRT,onterm);
    signal(SIGTERM,onterm);
    signal(SIGINT,onterm);
    signal(SIGSEGV,onterm);
    signal(SIGFPE,onterm);
    signal(SIGQUIT,onterm);
    signal(SIGILL,onterm);
    signal(SIGBUS,onterm);
    signal(SIGHUP,onterm);

    bool logined=false;
    bool joined=false;

    try {
        load_config();
        srandom(time(NULL));
        logErr("Bot started.");

        dbh=std_new_cMYSQL();

        read_messages();


        init();
    } catch (socketError e) {
        logErr("---Socket error: %s",e.error_string.c_str());
    } catch (cError e) {
        logErr("---Error: %s",e.error_string.c_str());
    } catch (...) {
        logErr("---Error: unknow!");
    }

    while (1) {
        int cnt=0;
        try {
            logErr("Connecting...");
            printf("Connecting...\n");
            connect_to_server();
            while (sock.connected()) {
//			printf("loop\n");
//		printf("qc=%d\n",questions_count);
                if (!logined) {
                    sock.response("USER bot bot bot: Botter");
                    sleep(1);
                    sock.response("NICK "+params["NICKNAME"]);
                    sleep(1);
                    sock.response("PASS "+params["PASSWD"]);
                    logined=true;
                }
//			printf("before data\n");
                if (!sock.readable(0)) {
//				printf("sock not readable\n");
                    usleep(10000);
                    check_state();
                    cnt++;
//				printf("cnt=%d\n",cnt);
                    if (cnt>2000) {
                        sock.response("PONG tusovka.tomsk.ru");
//					printf("sending alarm pong\n");
                        cnt=0;
                    }
                    continue;
                }
//			printf("after data\n");
                if (!joined) {
                    sock.response("JOIN "+params["CHANNEL"]);
                    joined=true;
                }
//			printf("before data\n");
                string data=sock.gets();
//			printf("after data\n");
                if (data.find(":tusovka.tomsk.ru 433 * :"+params["NICKNAME"]+": Nick is already in use.")!=-1) {
                    printf("This nickname is already in use. May be bot is already running.\n");
                    logErr("This nickname is already in use. May be bot is already running.");
                    sock.disconnect();
                    exit(1);
                }
#ifdef DEBUG
                printf("|>> %s\n",data.c_str());
                logErr("|>> %s",data.c_str());
#endif
                //process received buffer

                if (data.substr(0,1)!=".") {
                    if (data.substr(0,4)=="PING") {
                        string h=data.substr(5,data.size()-5);
                        sock.response("PONG "+h);
                        continue;
                    }
                }
                c_command cmd=parse_string(data);
                process_command(cmd);
            }


        } catch (socketError e) {
            logErr("---Socket error: %s",e.error_string.c_str());
        } catch (cError e) {
            logErr("---Error: %s",e.error_string.c_str());
        } catch (...) {
            logErr("---Error: unknow!");
        }
        sock.disconnect();
        logErr("Connection lost. Reconnecting...");
        logined=false;
        joined=false;
        sleep(5);
    }
}
