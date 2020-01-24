#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include <mysql/mysql.h>
#include "mysql_extens.h"
#include "cMYSQL.h"
#include "mysql_extens.h"
#include <time.h>
#include "DB_id.h"
#include "copy_file.h"
#define LIMIT 500
string str_nick(const string &n);
#define TRYOP(nnn) 	try{\
	nnn ; \
	}catch(cError e){printf("\n%s\n",e.what());};
#define SPLITTER "/"
map<string,string> params;
string olddb;
#define OLDDB "r"
#define NEWDB "ratest"
void load_config()
{
	params.clear();
	FILE *f=fopen(".config","r");
	if(!f) throw cError("Error during reading config file "+string(".config"));
	string data;
	while (!feof(f)){
		char s[1000];
		int z=fread((void*) &s, 1, 990,f);
		s[z]=0;
		data+=s;
	}
	vector<string> v=splitTOK("\r\n",data);
	for(unsigned int i=0;i<v.size();i++){
		string s=v[i];
		if(s.substr(0,1)=="#" || s.size()<=1) continue;
		int pz=s.find("=",0);
		if(pz==1){
			logErr("---Error in %s on line %d - '=' not found",".config",i);
			continue;
		}
		string key=s.substr(0,pz);
		string val=s.substr(pz+1,s.size()-pz-1);
		printf("'%s' -> '%s'",key.c_str(),val.c_str());
		params[strupper(key)]=val;
	}
}

string cvts(const string& s)
{
    string out;
    for(unsigned i=0;i<s.size();i++)
    {
	if(s[i]==13 || s[i]==10) continue;
	if(s[i]=='\"')
	{
	    out+="\\\"";
	    continue;
	}
	out+=s[i];
	
    }
    return out;
}
int main(int argc,char *argv[])
{
    try{
        //	FILE *f=fopen("clear_users.log","a");
/*
var diz=new Array();

diz[0]=
{
bad_nick_tmpl:"<a class=nick0 style=\"font-weight: bold\">~nick~</a>",
nickstd_tmpl:"<a class=nick0 href=\"javascript: parent.parent.Answer('~nick~')\" target=addmessage OnMouseOver=\"return os();\" style=\"font-weight: bold\">~nick~</a>",
nickpriv_tmpl:"<a class=nick0 href=\"javascript: parent.parent.Answer('~nick~',1)\" target=addmessage OnMouseOver=\"return os();\" style=\"font-weight: bold\">~nick~</a>",
from_stdmsg_tmpl:"<TABLE><TR><TD nowrap>~nick~: </TD><TD><font class=mt0>~msg~</font></TD></TR></TABLE>",
to_stdmsg_tmpl:"<TABLE><TR><TD nowrap>~nick~: </TD><TD><font class=mf0><b>~msg~</b></TD></TR></TABLE>",
stdmsg_tmpl:"<TABLE id=hm0><TR><TD nowrap>~nick~: </TD><TD>~msg~</TD></TR></TABLE>",
from_privmsg_tmpl:"<TABLE class=mpt0><TR><TD class=mp0>*** Приватное сообщение для ~nick~<BR><font class=mp0>~msg~</TD></TR></TABLE>",
to_privmsg_tmpl:"<TABLE class=mpt0><TR><TD class=mp0>*** Приватное сообщение от ~nick~<BR><font class=mptxt0><b>~msg~</b></font></TD></TR></TABLE>",
makeitmsg_tmpl:"<TABLE><TR><TD><font class=mmit0>*** ~nick~ ~msg~</font></TD></TR></TABLE>",
sysmsg_tmpl:"<TABLE border=0 id=hs0><TR><TD><font class=ms0>*** ~msg~</TD></TR></TABLE>",
sysprivmsg_tmpl1:"<TABLE class=mpst0><TR><TD class=mps0>*** Приватное системное сообщение ~n~<BR><b>~msg~</b></TD></TR></TABLE>",
sysprivmsg_tmpl2:"<TABLE class=mpst0><TR><TD class=mps0>*** Приватное системное сообщение <BR><b>~msg~</b></TD></TR></TABLE>"
};

*/
    printf("var diz=new Array();\n");
        
        string cf="color_packs=0:conf/colors/0std.conf,1:conf/colors/1green.conf,2:conf/colors/2blue.conf,3:conf/colors/3violet.conf,4:conf/colors/4red.conf,5:conf/colors/5spring.conf,6:conf/colors/6summer.conf,7:conf/colors/7autumn.conf,8:conf/colors/8winter.conf,9:conf/colors/9black.conf,10:conf/colors/10day.conf,11:conf/colors/11award.conf,12:conf/colors/12invinc.conf,13:conf/colors/13zags.conf,14:conf/colors/14adonis.conf,15:conf/colors/15real.conf,16:conf/colors/16konami.conf,17:conf/colors/17lion.conf,18:conf/colors/18real_1.conf,19:conf/colors/19kisa.conf,20:conf/colors/20vanga.conf,21:conf/colors/21diablo.conf,22:conf/colors/22queen.conf,23:conf/colors/23prison.conf,24:conf/colors/24bots.conf,25:conf/colors/25black.conf,26:conf/colors/26santa.conf,27:conf/colors/27serega.conf,28:conf/colors/28helper.conf,29:conf/colors/29unique.conf,30:conf/colors/30elite.conf";
        vector<string> v=splitTOK(", \r\n",cf);
        for (unsigned i=0;i<v.size();i++)
        {
            vector<string>w=splitTOK(":",v[i]);
            if (w.size()==2)
            {
                unsigned id=atoi(w[0]);
                map<string,string> m=load_m_file(w[1]);
                if (m.size())
                {
		    string pnout="out/"+w[1];
		    check_path_wfn(pnout);
		    string out;
		    vector<string> todel;
		    vector<pair<string,string> > toadd;
		    for(map<string,string>::iterator it=m.begin();it!=m.end();it++)
		    {
			if(it->first.substr(0,3)=="ru@")
			{
			    string key=it->first.substr(3,it->first.size()-3);
			    if(!m.count(key)) toadd.push_back(make_pair(key,it->second));
			}
			if(it->first.substr(0,3)=="en@")
			    todel.push_back(it->first);
		    }
		    for(unsigned it=0;it<toadd.size();it++)
		    {
			m[toadd[it].first]=toadd[it].second;
		    }
		    for(unsigned it=0;it<todel.size();it++)
			m.erase(todel[it]);
			
		    if(m.count("imagefname"))
		    {
			out+="imagefname="+m["imagefname"]+"\n";
		    }
		    else logErr2("%s: imagefname NF");
		    
		    if(m.count("name"))
		    {
			out+="name="+m["name"]+"\n";
		    }
		    else logErr2("%s: name NF");
		    st_FILE f(pnout,"wb");
		    f.write(out);
		    printf("diz[%d]=//%s\n{\n",id,m["name"].c_str());
		    string badnick=m["bnick"];
		    
		    printf("bad_nick_tmpl: \"%s\"",cvts(m["bnick"]).c_str());printf(",\n");
		    printf("nickstd_tmpl: \"%s\"",cvts(m["nick"]).c_str());printf(",\n");
		    printf("nickpriv_tmpl: \"%s\"",cvts(m["nickpriv"]).c_str());printf(",\n");
		    printf("from_stdmsg_tmpl: \"%s\"",cvts(m["stdfrom"]).c_str());printf(",\n");
		    printf("to_stdmsg_tmpl: \"%s\"",cvts(m["stdto"]).c_str());printf(",\n");
		    printf("stdmsg_tmpl: \"%s\"",cvts(m["std"]).c_str());printf(",\n");
		    printf("from_privmsg_tmpl: \"%s\"",cvts(m["privfrom"]).c_str());printf(",\n");
		    printf("to_privmsg_tmpl: \"%s\"",cvts(m["privto"]).c_str());printf(",\n");
		    printf("makeitmsg_tmpl: \"%s\"",cvts(m["makeit"]).c_str());printf(",\n");
		    printf("sysmsg_tmpl: \"%s\"",cvts(m["sys"]).c_str());printf(",\n");
		    printf("sysprivmsg_tmpl1: \"%s\"",cvts(m["syspriv"]).c_str());printf(",\n");
		    printf("sysprivmsg_tmpl2: \"%s\"",cvts(m["sysuser"]).c_str());printf("\n");
		    printf("};\n");
                }
            }
        }


    }catch (cError e)
    {
        printf("%s",e.what());
    }

    return 0;
}





