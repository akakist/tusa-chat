#ifndef mXML_HH
#define mXML_HH

#include <deque>
#include "PTR.h"

#define D_UNDEF 0
#define D_TEXT 1
#define D_NODE 2
#define D_PARAM 3
struct XMLDATA
{
	unsigned char type;// 1-text, 2-node 3- (param *d=&pair<char*,char*>)
	void *d; /*char* if text or PTR::getter<XMLNODE> if node*/
	XMLDATA():type(D_UNDEF)/*,erased(false)*/{}
};
class XMLNODE: public base_container_nm
{
public:
	PTR_getter<XMLNODE> parent;
	std::deque<XMLDATA> data;
	std::string _name;

	XMLNODE():base_container_nm(""),parent(NULL){}
	virtual ~XMLNODE();
	void AddNode(XMLNODE* n);
	void AddParam(const std::string &key, const std::string &val);
	void XMLNODE::EraseParam(const char* s);
	void AddText(const std::string &txt);
	std::map<std::string,std::string> GetXMLParams();
	
	XMLNODE* GetNode(unsigned int i);
	std::string GetText(unsigned int i);
	void Erase(unsigned int i);
	std::deque<XMLNODE*> GetNodesByName(const std::string& s);
	std::deque<XMLNODE*> GetNodesByNameI(const std::string& s);
	std::string Dump(int tab);
	int size();
};
PTR_getter<XMLNODE> parse_xmlbuf(const std::string &buf, const std::string& filename);

#endif
