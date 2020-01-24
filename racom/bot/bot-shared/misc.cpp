#include <string>
#include <strings.h>
#include "misc.h"
#include "utils.h"
#include "config.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "errs.h"
#include <stdio.h>

bool odd;

void privmsg(const string &nick,const string &msg)
{
    
    if (odd) {
        sock.response("PRIVMSG "+nick+" :"+msg);
    } else {
        sock.response("PRIVMSG "+nick+" :"+msg+" ");
    }
    odd=!odd;
    
}

void channelmsg(const string &msg)
{
    
    if (odd) {
        sock.response("PRIVMSG "+params["CHANNEL"]+" :"+msg);
    } else {
        sock.response("PRIVMSG "+params["CHANNEL"]+" :"+msg+" ");
    }
    odd=!odd;
    
}

void action(const string &msg)
{
    
    char c01=01;
    string s01;
    s01.assign(c01,1);
    if (odd) {
        sock.response("PRIVMSG "+params["CHANNEL"]+" :"+s01+"ACTION "+msg+s01);
    } else {
        sock.response("PRIVMSG "+params["CHANNEL"]+" :"+s01+"ACTION "+msg+" "+s01);
    }
    odd=!odd;
    
}


c_command parse_string(const string &os)
{
    string s=os;
    c_command cmd;
    
    if (!s.size()) return cmd;
    if (s.size()>9) {
        if (s.substr(0,9)=="EUI_REPLY") {
            
            cmd.cmd="EUI_REPLY";
            int pz=s.find(" ",0);
            string ss=s.substr(pz+1,s.size()-pz-1);
            cmd.msg=ss;
            return cmd;
            
        }
        if (s.substr(0,10)=="UTTC_REPLY") {
            
            cmd.cmd="UTTC_REPLY";
            int pz=s.find(" ",0);
            string ss=s.substr(pz+1,s.size()-pz-1);
            cmd.msg=ss;
            return cmd;
            
        }
    }
    if (s.substr(0,1)==":") {
        
        if (s.find("!",0)!=-1 && s.find("@",0)!=-1) {
            int pfn=-1;
            pfn=s.find("!");
            int pu=-1;
            if (pfn!=-1) pu=s.find("@",pfn+1);
            int ph=-1;
            if (pu!=-1) ph=s.find(" ",pu+1);
            int pc=-1;
            if (ph!=-1) pc=s.find(" ",ph+1);
            int pai=-1;
            if (pc!=-1) pai=s.find(":",pc+1);
            cmd.fromnick=s.substr(1,pfn-1);
            cmd.user=s.substr(pfn+1,pu-pfn-1);
            cmd.host=s.substr(pu+1,ph-pu-1);
            if (pc!=-1) {
                

                cmd.cmd=strupper(s.substr(ph+1,pc-ph-1));
                if (pai!=-1) {
                    
                    cmd.msg=s.substr(pai+1,s.size()-pai-1);
                    
                }

                if (cmd.cmd=="KICK" && pai!=-1) {
                    
                    int zpz=s.find(" ",pc+1);
                    if (zpz!=-1) cmd.tonick=s.substr(zpz+1,pai-zpz-2);
                    
                }
                if (cmd.cmd=="PRIVMSG" || cmd.cmd=="MODE") {
                    
                    int cc=s.find(" ",pc+1);
                    if (cc!=-1) cmd.tonick=s.substr(pc+1,cc-pc-1);
                    
                }
                if (cmd.cmd=="PRIVMSG") {
                    
                    //logErr("if(cmd.cmd==\"PRIVMSG\")");
                    //logErr("cmd.tonick %s",cmd.tonick.c_str());
                    if (cmd.msg.substr(1,6)=="ACTION") {
                        cmd.msg=cmd.msg.substr(8,cmd.msg.size()-9);
                    }
                    int l=params["NICKNAME"].size();
                    //logErr("l=%d",l);
                    //logErr("--2-- cmd.msg %s",cmd.msg.c_str());
                    if (cmd.msg.size()>=l+2) {
                        
                        //logErr("if(cmd.msg.size()>=l+2)");;
                        //logErr("--- cmd.msg %s",cmd.msg.c_str());
                        if (cmd.msg.substr(1,l)==params["NICKNAME"]) {
                            
                            //logErr("cmd.msg.substr(1,l)==params[\"NICKNAME\"]");
                            if (cmd.msg.size()>l+2)
                            {
                                cmd.msg=cmd.msg.substr(l+3,cmd.msg.size()-l-4);
                            }
                            cmd.ppriv=true;
                            //logErr("cmd.ppriv=true");

                            
                        }
                        
                    }
                    
                }
                
            }

        } else {

        }
        

    }
    
    //logErr("cmd.msg %s",cmd.msg.c_str());
    return cmd;
}


c_socket sock;

struct hostent *host_info;


void connect_to_server()
{
    
    if (sock.sock==-1) {
        sockaddr_in serv_addr;
        if ((host_info = gethostbyname(params["HOST_TO_CONNECT"].c_str()))) {
            bcopy(host_info->h_addr, (char *)&serv_addr.sin_addr,host_info->h_length);
        } else {
            logErr("---Error: unable resolve host name %s",params["HOST_TO_CONNECT"].c_str());
        }
//		serv_addr.sin_addr.s_addr = inet_addr(params["IP_TO_CONNECT"].c_str());
        serv_addr.sin_port = htons(atoi(params["PORT_TO_CONNECT"]));
        serv_addr.sin_family = AF_INET;
        int sk = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        sock.sock=sk;
        sock.connect((sockaddr*) &serv_addr,sizeof(serv_addr));
    }
    
}

