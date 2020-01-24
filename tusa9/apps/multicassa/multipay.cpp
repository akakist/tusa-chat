#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include <deque>
#include "copy_file.h"
#include <sys/stat.h>
#include <cgi.h>
#include "__mXML.h"
deque<string>nn;

string repl_percent(const string & s)
{
	string a;
	for (unsigned int i = 0; i < s.size(); i++) {
		if (s[i] == '%') {
			if (i + 2 > s.size()) {
				break;
			}
			int c1 = u_table[s[i + 1]];
			int c2 = u_table[s[i + 2]];
			i += 2;
			if (c1 > 70 || c2 > 70) {continue;}
			if (c1 < 48 || c2 < 48) {continue;}
			if (c1 >= 48 && c1 <= 57) {c1 -= 48;}
			if (c2 >= 48 && c2 <= 57) {c2 -= 48;}
			if (c1 >= 65 && c1 <= 70) {c1 -= 55;}
			if (c2 >= 65 && c2 <= 70) {c2 -= 55;}
			a += (char) c1 *16 + c2;
		} else {
			if (s[i] == '+') {a += " ";}
			else {a += s[i];}
		}
	}
	return a;
}

string date2mcassa(time_t t)
{
    struct tm *q;
    q=localtime(&t);
    return
        lzstring(q->tm_mday)+"-"+ lzstring(q->tm_mon+1)+"-"+ itostring(q->tm_year+1900)+
        " "+lzstring(q->tm_hour)+":"+lzstring(q->tm_min)+":"+lzstring(q->tm_sec);
}

time_t mcassa2date(const string & t)
{
    vector < string > v = splitTOK(":- ", t);
    if (v.size() != 6) {
        throw cError("mcassa2date: to few arguments! t=" + t);
    }
    struct tm q;
    q.tm_mday = atoi(v[0]);
    q.tm_mon = atoi(v[1]) - 1;
    q.tm_year = atoi(v[2]) - 1900;
    q.tm_hour = atoi(v[3]);
    q.tm_min = atoi(v[4]);
    q.tm_sec = atoi(v[5]);
    return mktime(&q);
}

string GetTagContent(XMLNODE * n, const string & tagname, bool throw_on_notexists)
{
    deque<XMLNODE*> x_tags=n->GetNodesByNameI(tagname);
    if(x_tags.size()!=1)throw cError("x_tags.size()!=1");
    XMLNODE *x_tag=x_tags[0];
    if(!x_tag)throw cError("!x_tag");
    if(x_tag->size()!=1)throw cError("x_tag->size()!=1");
    if(x_tag->data[0].type!=D_TEXT) throw cError("!x_tag->data->type==D_TEXT");
    return x_tag->GetText(0);

}
struct operation
{
    time_t _time;
    unsigned int id;
    unsigned int point;
    unsigned int service;
    string account;
    double total;
    unsigned int id_prov;
};
vector<operation> operation_list;
map<string,string>params;
int main(int argc,char *argv[])
{
    string response;
/*	    char sbuff[10000];
            string fl=gets(sbuff);
            int pom = fl.find(" ", 0);
            if (pom == -1) {
			//logErr2("return %s %d",__FILE__,__LINE__);
                return;
            }

            string METHOD = strupper(fl.substr(0, pom));
            params["METHOD"] = METHOD;
            string url= fl.substr(pom + 1, fl.find(" ", pom + 1) - pom - 1);
            url = repl_percent(url);
            string newstr;
            {
                //				PGLW(c_socket, psock,socket);
                newstr = __gets(socket,"\r\n");
                total_recv+=newstr.size();
                //WRITES__(newstr);
                //                              printf("%s\n",newstr.c_str());
            }*/

    
	printf("Content-type: text/plain\r\n\r\n");
	fflush(stdout);
//	FILE * f=popen("/usr/bin/pwd","r");
/*	while(!feof(f))
	{
	    char c=fgetc(f);
	    putchar(c);
	}
	printf("<p>");*/
	while(1)
	{
	    unsigned int c=getchar();
	    if(c==EOF) break;
	    putchar(c);
	}
        cgi_init();
        cgi_process_form();
    	cgi_init_headers();
    try{
        MYSQL *_dbh=new MYSQL;
        mysql_init(_dbh);
        MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"chat",0,NULL,0);
        if(!res)
        {
            logErr("chat_sender: mysql_real_connect failed to %s","chat");
	    throw cError("chat_sender: mysql_real_connect failed to  chat");
//            exit(1);
        }
	printf("<p>cuccessfully connected<p>\n");
        cMYSQL *dbh=new cMYSQL(_dbh);
        dbh->connected=true;
//	exit(0);		

/*        string header="Content-type: text/plain\n";
        header+="Host: www.operator.ru\n";
        header+="\n";
        printf("%s kall",header.c_str());*/
	
        string xml=cgi_param("xml");
        string sign=cgi_param("sign");
	logErr("<pre>%s\n<p>%s\n</pre>",repl_percent(xml).c_str(),repl_percent(sign).c_str());
	printf("<pre>%s\n<p>%s\n</pre>",repl_percent(xml).c_str(),repl_percent(sign).c_str());
	exit(0);		
        if(!xml.size())
        {
            throw cError("xml.size()==0");


        }
        PTR_getter<XMLNODE> ROOT=parse_xmlbuf(xml, "xml buf");
        if(!ROOT) throw cError("cannot parse xml buffer");
        if(ROOT.__get__PTR__()->_name!="root")    throw cError("rootname != root");

        deque<XMLNODE*> x_heads=ROOT.__get__PTR__()->GetNodesByName("header");
        if(x_heads.size()!=1)throw cError("headre size !=1");

        XMLNODE *x_head=x_heads[0];
        string timestr;
        if(!x_head)throw cError("!x_head");

        time_t head_time=mcassa2date(GetTagContent(x_head,"time",true));
        string user=GetTagContent(x_head,"user",true);
        string password=GetTagContent(x_head,"password",true);
        bool emergency=GetTagContent(x_head,"emergency",true)=="true";
	
	
	deque<XMLNODE*> x_op_list=ROOT.__get__PTR__()->GetNodesByName("operations_list");
	if(x_op_list.size()!=1) throw cError("x_op_list.size()!=1"); 
	deque<XMLNODE*> x_ops=x_op_list[0]->GetNodesByName("operation");
	for(unsigned i=0;i<x_ops.size();i++)
	{
	    operation op;
	    
	    op.point=atoi(GetTagContent(x_ops[i],"point", true));
	    op.id=atoi(GetTagContent(x_ops[i],"id", true));
	    op.service=atoi(GetTagContent(x_ops[i],"service", true));
	    op._time=mcassa2date(GetTagContent(x_ops[i],"time", true));
	    op.account=GetTagContent(x_ops[i],"account", true);
	    op.total=atof(GetTagContent(x_ops[i],"total", true).c_str());

	    dbh->real_queryQ((QUERY)
	    "insert into mcassa_requests (user, head_dt,dt,op_id,op_point,op_service,op_dt,op_total,op_account)  values"
	    "('?',FROM_UNIXTIME(?),NOW(),'?','?','?',FROM_UNIXTIME(?),'?','?')"
	    <<user
	    <<head_time
	    <<op.id
	    <<op.point
	    <<op.service
	    <<op._time
	    <<op.total
	    <<op.account
	    );
	    string li=dbh->select_1("select last_insert_id()");
	    op.id_prov=atoi(li);

	    operation_list.push_back(op);

	}
	
	response="<root>\n";
	response+="\t<header>\n";
	response+="\t\t<time>"+date2mcassa(time(NULL))+"</time>\n";
	response+="\t\t\<refresh_timeout>1</refresh_timeout>\n";
	response+="\t\t<balance>0</balance>\n";
	response+="\t\t<limit>0</limit>\n";
	response+="\t</header>\n";
	
	if(operation_list.size())
	{
	
	    response+="\t<operations_list>\n";
	    for(unsigned i=0;i<operation_list.size();i++)
	    {
		response+="\t\t<result>\n";
		response+="\t\t\t<time>"+date2mcassa(operation_list[i]._time)+"</time>\n";
		response+="\t\t\t<point>"+itostring(operation_list[i].point)+"</point>\n";
		response+="\t\t\t<id>"+itostring(operation_list[i].id)+"</id>\n";
		response+="\t\t\t<id_prov>"+itostring(operation_list[i].id_prov)+"</id_prov>\n";
		response+="\t\t\t<code>0</code>\n";
		
		response+="\t\t</result>\n";
	    }
	    response+="\t</operations_list>\n";
	}

	response+="</root>\n";
    }
    catch(cError e)
    {
	    response=(string)"cError: "+e.what();

    }
    catch(...)
    {
	    response="error ....";
	
    }
    printf("Content-type: text/plain\r\n");
    printf("Content-length: %d\r\n",response.size());
    printf("\r\n");
    printf(response.c_str());
    logErr(response.c_str());
    
    return 0;
}
