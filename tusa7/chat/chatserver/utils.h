#ifndef CHAT_UTILS_H__
#define CHAT_UTILS_H__
#include "user.h"
#include <time.h>
#include <vector>
#include <string>
#define SCROLL	"<script>DS()</script>\n"



string ES(const string &s);
string ESB(const string &s);

string MESL(const string &s);

string remove_tags(const string &s);

string remove_maty(const string &s);

bool check_maty(const string &ms);

string make_time(time_t t);

string replace_links(const string &m);

bool check_login(const string &s);
bool check_nick(const string &s);

string remove_spaces(const string &s);

string split_long(const string &s);

string str_nick(const string &n);

string nick_for_sort(const string &n);


string redirect();


string number2text(const int i);

string strtime(const time_t t);
string strtime_short(const time_t t);

string datetime2rus_short(const time_t t);
string datetime2rus(const time_t t);
string date2rus(const time_t t);

string date4file(const time_t t);
string date2num(const time_t t);
string datetime2num(const time_t t);

string get_rus_month(const int z);
string get_rus_month2(const int z);

void str_sort(vector<string> &v);

string checked(const string &s);
string checked(int z);
int chk(const string &s,int z);

extern unsigned char nicks_char[256];

struct tm LOCALTIME(time_t timep);
time_t get_cur_hour(time_t t);
time_t get_cur_day(time_t t);
time_t get_cur_week(time_t t);
time_t get_cur_month(time_t t);
time_t get_cur_year(time_t t);
time_t get_cur_whole(time_t t);

vector<string> si_2_vs(const set<unsigned int> &s);
set<unsigned int> vs_2_si(const vector<string>&v);
set<unsigned int> s_2_si(const string &s);
string si_2_s(const set<unsigned int> &s);
map<unsigned int,double> s_2_mid(const string &s);

void remove_from_string_set(string &stringset,unsigned int v);
void add_to_string_set(string &stringset,unsigned int v);

map<string, vector< vector<string> > > load_st_file(const string &fname);
vector<string> load_l_file(const string &fname);

string get_f22(double dd);


#endif
