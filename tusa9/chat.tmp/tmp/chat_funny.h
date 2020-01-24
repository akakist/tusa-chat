#ifndef CHAT_FUNNY
#define CHAT_FUNNY
#include <string>
#include <vector>

class s_text_funny
{
	public:
	int id;
	string text;
	string add_by;
	s_text_funny();
};

class funny_pic
{
	public:
	int id;
	string name;
	string descr;	
	funny_pic();
};
class c_neu
{
	public:
	int id;
	//int nid;
	string txt;
	string add_by;
	time_t add_date;
	c_neu();
};

	bool load_histories();
	bool load_anekdots();
	bool load_funnypics();
	bool load_hints();
	bool load_news();

	funny_pic FUNNYPICS(unsigned int n);
	unsigned int FUNNYPICS_SIZE();
	s_text_funny ANEKDOTS(unsigned int n);
	unsigned int ANEKDOTS_SIZE();
	s_text_funny HISTORIES(unsigned int n);
	unsigned int HISTORIES_SIZE();
	string HINTS();
	unsigned int NEWS_SIZE();
	vector<c_neu> NEWS();
	vector < c_neu >  NEWS_GET_N(int cnt);

#endif
