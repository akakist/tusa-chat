#include "stdafx.h"
#include <stdio.h>
#include "str_lib.h"
#include <time.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <sys/stat.h>
#include <stdio.h>
#include <signal.h>
#include <algorithm>
//#include <atlenc.h>
#include <set>
#include <map>
#include <vector>

#include "__mXML.h"
#include "PTR.h"

#include <expat.h>
#include <deque>
using namespace std;
void XMLNODE::AddNode(XMLNODE* n)
{
	XMLDATA d;
	d.type=D_NODE;
	PTR_getter<XMLNODE> *ppp=new PTR_getter<XMLNODE> (n);
	ppp->__get__PTR__()->parent=this;
	d.d=ppp;
	data.push_back(d);
}
deque<XMLNODE*> XMLNODE::GetNodesByName(const string&s )
{
	deque<XMLNODE*> ret;
	for(unsigned i=0;i<data.size();i++)
	{
		if(data[i].type==D_NODE && data[i].d)
		{
			PTR_getter<XMLNODE> *ppp=(PTR_getter<XMLNODE> *)data[i].d;
			if(ppp&&ppp->__get__PTR__()&&ppp->__get__PTR__()->_name==s)
			{
				ret.push_back(ppp->__get__PTR__());
			}
		}
	}
	return ret;
}
deque<XMLNODE*> XMLNODE::GetNodesByNameI(const string&s )
{
	deque<XMLNODE*> ret;
	for(unsigned i=0;i<data.size();i++)
	{
		if(data[i].type==D_NODE && data[i].d)
		{
			PTR_getter<XMLNODE> *ppp=(PTR_getter<XMLNODE> *)data[i].d;
			if(ppp&& ppp->__get__PTR__()&&strlower(ppp->__get__PTR__()->_name)==strlower(s))
			{
				ret.push_back(ppp->__get__PTR__());
			}
		}
	}
	return ret;
}
XMLNODE* XMLNODE::GetNode(unsigned int i)
{
	if(i>=data.size())return NULL;
	if(!data[i].d) return NULL;
	PTR_getter<XMLNODE> *ppp=(PTR_getter<XMLNODE> *)data[i].d;
	return ppp->__get__PTR__();
}
string XMLNODE::GetText(unsigned int i)
{
	if(!data[i].d) return "";
	char *s=(char*)data[i].d;
	//PTR_getter<XMLNODE> *ppp=(PTR_getter<XMLNODE> *)data[i].d;
	return s;
}
void XMLNODE::AddParam(const string &key, const string &val)
{
	pair<char*,char*> *p=new pair<char*,char*> (strdup(key.c_str()),strdup(val.c_str()));
	XMLDATA d;
	d.type=D_PARAM;
	d.d=p;
	data.push_back(d);

}
void XMLNODE::Erase(unsigned int i)
{

	{
		if(!data[i].d)return;
		if(data[i].type==D_PARAM)
		{
			pair<char*,char*> *p=(pair<char*,char*> *)data[i].d;
			if(p)
			{
				if(p->first)free(p->first);
				if(p->second) free(p->second);
				delete p;
				data[i].d=NULL;

			}

		}
		else if(data[i].type==D_TEXT)
		{
			char *s=(char*)data[i].d;
			free(s);
			data[i].d=NULL;
		}
		else if(data[i].type==D_NODE)
		{
			PTR_getter<XMLNODE>* p=(PTR_getter<XMLNODE>* )data[i].d;
			delete p;
			data[i].d=NULL;
		
		}
	}

}
void XMLNODE::EraseParam(const char* s)
{
	for(unsigned i=0;i<data.size();i++)
	{
		if(data[i].type==D_PARAM && data[i].d)
		{
			pair<char*,char*> *p=(pair<char*,char*> *)data[i].d;
			if(!strcmp(p->first,s))
			{
				Erase(i);
				return;
			}
			
		}
	}
}	
void XMLNODE::AddText(const string &txt)
{
	XMLDATA d;
	d.type=D_TEXT;
	d.d=strdup(txt.c_str());
	data.push_back(d);

}
map<string,string> XMLNODE::GetXMLParams()
{
//	if(params==NULL)
//	{
		map<string,string>params;//=new map<string,string>;
		for(unsigned i=0;i<data.size();i++)
		{
			if(data[i].type==D_PARAM && data[i].d)
			{
				pair<char*,char*> *p=(pair<char*,char*> *)data[i].d;
				params[p->first]=p->second;
			}
		}
//	}
	//map<string,string> m;
	return params;
}
XMLNODE::~XMLNODE()
{
	
	for(unsigned i=0;i<data.size();i++)
	{
		Erase(i);
	}
//	if(params)delete params;
}
PTR_getter<XMLNODE>  deflt(NULL);

bool isspace(const XML_Char *s,int len)
{
	for(unsigned i=0;i<len;i++)
	{
		if(!isspace(s[i])) return false;
	}
	return true;
}
static void XMLCALL char_handler(void *data,const XML_Char *s,int len)
{
	if(isspace(s,len)) return;
	string sss=string(s,len);
	deflt.__get__PTR__()->AddText(sss);
	//logErr2("text: '%s'",sss.c_str());
}

static void XMLCALL
start(void *data, const char *el, const char **attr)
{
	PTR_getter<XMLNODE> n(new XMLNODE);
	n.__get__PTR__()->_name=el;

	for (int i = 0; attr[i]; i += 2) {
		n.__get__PTR__()->AddParam(attr[i], attr[i + 1]);
	 }
	deflt.__get__PTR__()->AddNode(n.__get__PTR__());
	deflt=n;
}

static void XMLCALL
end(void *data, const char *el)
{
	PTR_getter<XMLNODE> p=deflt.__get__PTR__()->parent;
	deflt.__get__PTR__()->parent=NULL;
	deflt=p;
}

_mutex parse_xmlbuf_MX("parse_xmlbuf_MX");
//extern "C"
PTR_getter<XMLNODE> parse_xmlbuf(const string &buf, const string& filename)
{
	MUTEX_LOCK kall(parse_xmlbuf_MX);
	PTR_getter<XMLNODE> n(new XMLNODE);
	deflt=n;
  XML_Parser prs = XML_ParserCreate(NULL);
  if (! prs) {
    throw cError("Couldn't allocate memory for parser\n");
    return NULL;
  }
  XML_SetElementHandler(prs, start, end);
  XML_SetCharacterDataHandler(prs,char_handler);

    int done=0;
    if (XML_Parse(prs, buf.c_str(),buf.size(), done) == XML_STATUS_ERROR) {
		char sss[200];
		snprintf(sss,sizeof(sss),"Parse error at %s: line %d:\n%s\n",
				filename.c_str(),
              XML_GetCurrentLineNumber(prs),
              XML_ErrorString(XML_GetErrorCode(prs)));
		throw cError(sss);
		logErr2("Parse error at %s: line %d:\n%s\n",
				filename.c_str(),
              XML_GetCurrentLineNumber(prs),
              XML_ErrorString(XML_GetErrorCode(prs)));
		return NULL;
    }
	XML_ParserFree(prs);
  return n;
}
int XMLNODE::size()
{

    return data.size();
}
string XMLNODE::Dump(int tab)
{
	string s;
	int n;
	if(!data.size()) return s;
	for(int i=0;i<tab;i++) s += "   ";
	s = s + "<" + _name;
	int i;
	for(i=0;i<data.size();i++) {
		if(data[i].type==D_PARAM && data[i].d)
		{
			pair<char*,char*> *p=(pair<char*,char*> *)data[i].d;
			s = s + " " + p->first + "=\"" + p->second + "\"";
		}
	}
	for(i=0;i<data.size() && data[i].type!=D_NODE && data[i].type!=D_TEXT;i++);
	if(i==data.size()) s = s + "/>\r\n";
	else {
		s = s + ">";
		for(n=0;n<data.size() && data[n].type!=D_NODE;n++);
		if(n<data.size()) s = s + "\r\n";
		for(int i=0;i<data.size();i++) {
			if(data[i].type==D_NODE && data[i].d) {
				PTR_getter<XMLNODE> *ppp=(PTR_getter<XMLNODE> *)data[i].d;
				s = s + ppp->__get__PTR__()->Dump(tab+1);
			}
			else if(data[i].type==D_TEXT)
			{
				char *text=(char*)data[i].d;
				for(int i=0;i<strlen(text);i++) {
					if(text[i]=='<') s=s+"&lt;";
					else if(text[i]=='>') s=s+"&gt;";
					else if(text[i]=='&') s=s+"&amp;";
					else if(text[i]=='\'') s=s+"&apos;";
					else if(text[i]=='\"') s=s+"&quot;";
					else s=s+text[i];
				}
//				s = s + text;
			}
		}
		if(n<data.size()) for(int i=0;i<tab;i++) s += "   ";
		s = s + "</" + _name + ">\r\n";
	}
	return s;
}