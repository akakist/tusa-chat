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
#include "copy_file.h"
#include "file_set.h"

#include "app_con.h"
#include "app_def.h"
#include "tcp_stats.h"
#include "chat_config.h"
#include "user_credits.h"
#include <algorithm>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#ifndef WIN32
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include "tcp_oscar_dialog_server.h"
#ifndef _NO_PROXY
#endif
#include "oscar_buffer.h"

#include "chat_globals.h"

#include "st_rsa.h"
#include "web_tools.h"
#include "update_cmd.h"
#include "chat_thread_event.h"
#include "channels.h"
//#include "app_con.h"

enum
{
    ACT_BUY_CREDIT	=1,
    ACT_LEADER		=2,
	ACT_NOOP		=3,
	ACT_CONCURS		=4,
};
string councurs_add_sms(unsigned ucha);



void url_rbill(app_connection* cc)
{
				st_dbh d;
//	cc->allow_build_response=false;

	for(map<string,string>::const_iterator i=cc->params.begin();i!=cc->params.end();i++)
	{
		logErr2("url_rbill %s %s",i->first.c_str(),i->second.c_str());
	}
	
	set<string> req_pars;
	req_pars.insert("skey");
	req_pars.insert("smsid");
	req_pars.insert("num");
	req_pars.insert("operator");
	req_pars.insert("operator_id");
	req_pars.insert("user_id");
	req_pars.insert("cost");
	req_pars.insert("msg");
	req_pars.insert("acr");
	req_pars.insert("nquery");

	bool debug=false;
/*	if(cc->params.count("debug"))
	{
		if(cc->params["debug"]=="1")
		{
			debug=true;
		}
	}*/
	for(set<string>::const_iterator i=req_pars.begin();i!=req_pars.end();i++)
	{
		if(!cc->params.count(*i)) logErr2("url_rbill: undefined field %s",i->c_str());
		req_pars.erase(*i);
	}
	for(set<string>::const_iterator i=req_pars.begin();i!=req_pars.end();i++)
	{
		logErr2("url_rbill: unused field %s",i->c_str());
	}
	string skey =cc->params["skey"];			// -  ключ-пароль сервиса (Skey)
	string smsid  =cc->params["smsid"];			//   - идентификатор сообщения, текущее время в миллисекундах, например, "1174921221.133533".
	string num  =cc->params["num"];				//  - короткий номер, на который абонент отправлял запрос, например, "1171".
	string operator$ =cc->params["operator"];	//  - наименование оператора, с которого получен запрос, например, "mts_moskow" (МТС Москва).
	string operator_id =cc->params["operator_id"];	// -  числовой индентификатор оператора. 
	string user_id =cc->params["user_id"];		//   - телефон пользователя, с заменой двух последних цифр на ХХ.
	string cost =cc->params["cost"];			//   - стоимость сообщения, сумма, которая зачисляется на счет партнера, например, "3.098".
	string msg =cc->params["msg"];				//   - сообщение, которое отправил абонент, например, "kurs".
	string acr =cc->params["acr"];				//   - коэффициент активности телефона в системе.
	string nquery =cc->params["nquery"];		//   -  номер повтора после ошибок относящихся к timeout (значения от 1 до 5).  

		d.dbh->real_queryQ((QUERY)
			"insert into rbill_log (`skey`,`smsid`,`num`,`operator`,`operator_id`,`user_id`,`cost`,`msg`,`acr`,`nquery`,`dt`)\
			values('?','?','?','?','?','?','?','?','?','?',NOW())"
			<<skey<<smsid<<num<<operator$<<operator_id<<user_id<<cost<<msg<<acr<<nquery);

	logErr2("msg '%s' ip %s",msg.c_str(),cc->peer_ipaddress.c_str());
	double _cost=atof(cost.c_str());

	
	if(MD5(skey)!="akakist512")
	{
		logErr2("---Error: invalid SKEY");
		//return;
	}
	vector<string> v=splitTOK(" \r\n\t",msg);
	string msgout;
	if(v.size()>1)
	{
		DB_id uid;CONTAINER(uid)=0; CONTAINER(uid)=atoi(v[1]);
		
		Double add_summa;add_summa.container=_cost*100;
		Double sum;sum.container=0;
		
		string login;
		{
			PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(uid)));
			sum.container=u->credit_summa.container+add_summa.container;
			login=u->login;
		}
		logErr2("login %s sum %f",login.c_str(),sum.container);
		msgout+="Za4isleno "+get_f22(add_summa.container)+ " na login '"+login+"'. Ostatok "+get_f22(sum.container)+". Spasibo za pokupku.";
		logErr2("SMS: %s",msgout.c_str());

		inc_credit_summa(uid,add_summa,"rbill");
	}
	else
	{
		logErr2("--Error SMS text, invalid format");
		msgout+="Error SMS text, invalid format";
	}
//	cc->allow_build_response=false;
/*
<?
$smsid=$_GET['smsid'];
echo "smsid:$smsid\n";
echo "status:reply\n";
echo "content-type:text/plain\n";
echo "\n";
echo "Ваш ответ абоненту\n";
?>
*/

//	string out = "HTTP/1.1 200 OK\r\n";
	cc->html_out += "smsid:"+smsid+"\n";
	cc->html_out += "status:reply\n";
	cc->html_out += "content-type:text/plain\n";
	cc->html_out += "\n";
	cc->html_out+=msgout+"\n";
//	cc->write(out);
	logErr2("%s",cc->html_out.c_str());
	/*
	smsid: 1174921221.133533
	
	content-type: (text/plain |  flash-msg |  wap-push |  app-port-long)

	*/
}


void url_ifree(app_connection* cc)
{
				st_dbh d;

	for(map<string,string>::const_iterator i=cc->params.begin();i!=cc->params.end();i++)
	{
		logErr2("url_ifree %s %s",i->first.c_str(),i->second.c_str());
	}
	
	set<string> req_pars;
	req_pars.insert("abonentId");
	req_pars.insert("country");
	req_pars.insert("evtId");
	req_pars.insert("md5Phone");
	req_pars.insert("md5key");
	req_pars.insert("now");
	req_pars.insert("operator");
	req_pars.insert("phone");
	req_pars.insert("serviceNumber");
	req_pars.insert("smsText");
	bool debug=false;
	if(cc->params.count("debug"))
	{
		if(cc->params["debug"]=="1")
		{
			debug=true;
		}
	}
	for(set<string>::const_iterator i=req_pars.begin();i!=req_pars.end();i++)
	{
		if(!cc->params.count(*i)) logErr2("url_ifree: undefined field %s",i->c_str());
		
	}
	string abonentId=cc->params["abonentId"];
	string country=cc->params["country"];
	string evtId=cc->params["evtId"];
	string md5Phone=cc->params["md5Phone"];
	string md5key=cc->params["md5key"];
	string now=cc->params["now"];
	string _operator=cc->params["operator"];
	string phone=cc->params["phone"];
	string serviceNumber=cc->params["serviceNumber"];
	string smsTextEncoded=cc->params["smsText"];

	string smsText=Base64Decode(smsTextEncoded);
	logErr2("ifree %s",smsText.c_str());
	try{
		d.dbh->real_queryQ((QUERY)
			"insert into ifree_log (abonentId,country,evtId,md5Phone,md5key,`now`,operator,phone,serviceNumber,smsText,dt)\
			values('?','?','?','?','?','?','?','?','?','?',NOW())"
			<<abonentId<<country<<evtId<<md5Phone<<md5key<<now<<_operator<<phone<<serviceNumber<<smsText);
	}
	STDCATCHS("");

	logErr2("smsText '%s' ip %s",smsText.c_str(),cc->peer_ipaddress.c_str());
	double cost=0;
	if(serviceNumber=="4440") cost=0.05;
	else if(serviceNumber=="4443") cost=0.15;
	else if(serviceNumber=="4444") cost=0.30;
	else if(serviceNumber=="4445") cost=0.60;
	else if(serviceNumber=="4446") cost=0.99;
	else if(serviceNumber=="4447") cost=1.30;
	else if(serviceNumber=="4448") cost=2.00;
	else if(serviceNumber=="4449") cost=3.00;
	else if(serviceNumber=="4161") cost=4.75;
	else if(serviceNumber=="4151") cost=0.99;
	else if(serviceNumber=="2444") cost=0.40;
	else if(serviceNumber=="3444") cost=0.20;
	else if(serviceNumber=="5444") cost=0.59;
	else if(serviceNumber=="8444") cost=2.00;
	else logErr2("url_ifree: invalid serviceNumber %s",serviceNumber.c_str());

	

	

	string md5CheckSrc=serviceNumber+smsTextEncoded+country+abonentId+"kall"+now;
	string md5CheckSrc1=md5CheckSrc+"1";
	string md5CheckSrc0=md5CheckSrc+"1";
	
	string md5hash=bin2hex(MD5(md5CheckSrc));
	string md5hash1=bin2hex(MD5(md5CheckSrc1));
	string md5hash0=bin2hex(MD5(md5CheckSrc0));
	
	if(!(md5hash==md5key||md5hash0==md5key||md5hash1==md5key))
	{

	}

	vector<string> vv=splitTOK(" +",smsText);
	Double add_summa;
	int action=ACT_NOOP;
	
	
	map<string,string> m=chat_config.get_pay_params();
	if(vv.size()>=2)
	{
		if(serviceNumber=="4443" && str_nick(vv[0])=="HMZA")
		{
		    if(!m.count("ifree_4443")) 
		    {
			logErr2("!!!!!!!!!!!ERROR ifree_hmza not defined");
		    }
			add_summa.container=atof(m["ifree_hmza"].c_str());
			action=ACT_BUY_CREDIT;

		}
		else if(serviceNumber=="4444" && str_nick(vv[0])=="HMZB")
		{
		    if(!m.count("ifree_hmzb")) 
		    {
			logErr2("!!!!!!!!!!!ERROR ifree_hmzb not defined");
		    }
			add_summa.container=atof(m["ifree_hmzb"].c_str());
			action=ACT_BUY_CREDIT;
		}
		else if(serviceNumber=="4446" && str_nick(vv[0])=="HMZC")
		{
		    if(!m.count("ifree_hmzc")) 
		    {
			logErr2("!!!!!!!!!!!ERROR ifree_hmzc not defined");
		    }
			add_summa.container=atof(m["ifree_hmzc"].c_str());
//			add_summa.container=240.0;
			action=ACT_BUY_CREDIT;
		}
		else if(serviceNumber=="4449" && str_nick(vv[0])=="HMZD")
		{
		    if(!m.count("ifree_hmzd")) 
		    {
			logErr2("!!!!!!!!!!!ERROR ifree_hmzd not defined");
		    }
			add_summa.container=atof(m["ifree_hmzd"].c_str());
//			add_summa.container=750.0;
			action=ACT_BUY_CREDIT;
		}
		else if(serviceNumber=="4445" && str_nick(vv[0])=="HMZL")
		{
			action=ACT_LEADER;
		}
		else if(str_nick(vv[0])=="HMGL")
		{
			action=ACT_CONCURS;
		}
		else
		{
		     logErr2("Error: Invalid url_ifree request %s",smsText.c_str());
		    cc->html_out+="<Response><SmsText>Invalid request format</SmsText></Response>";
		    return;
		}     

			if(action==ACT_CONCURS)
			{
				
				string r=councurs_add_sms(atoi(vv[1]));
				cc->html_out+="<Response><SmsText>"+r+"</SmsText></Response>";
				return;
			}
			if(action==ACT_BUY_CREDIT)
			{
				DB_id uid;CONTAINER(uid)=0;CONTAINER(uid)=0;

				CONTAINER(uid)=atoi(vv[1]);

				if(CONTAINER(uid)==0)
				{
					cc->html_out+="<Response><SmsText>Invalid format of SMS text. Ne ukazan ID. Mozhete poslat korrektnyj zapros i napisat Mazar'u ob oshibke. S ukazaniem wremeni i nomera prawilnogo zaprosa.</SmsText></Response>";
					return;
				}


//				logErr2("uid %d",CONTAINER(uid));
				Double sum;sum.container=0;
				string login;
				{
					PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(uid)));
					login=u->login;
					sum.container=u->credit_summa.container+add_summa.container;
				}
				logErr2("login %s sum %f",login.c_str(),sum.container);
				cc->html_out="<Response><SmsText> Za4isleno "+get_f22(add_summa.container)+ " na login '"+login+"'. Ostatok "+get_f22(sum.container)+". Spasibo za pokupku.</SmsText></Response>";
				logErr2("SMS: %s",cc->html_out.c_str());
				
				inc_credit_summa(uid,add_summa,"ifree");

				

			}

	}
	else 
	{
		    cc->html_out+="<Response><SmsText>Invalid request format</SmsText></Response>";
		    return;
	
	}
}
