#ifndef USER_INFO__H
#define USER_INFO__H
#include "fotos.h"






class user_credit;

class ignore_vec;
class contact_vec;

string update_to_db(const PTR_getter<user_credit>&__P,const string &tblname);
string update_to_db(const PTR_getter<u_notes>&__P,const string &tblname);
string update_to_db(const PTR_getter<user_stat>&__P,const string &tblname);
string update_to_db(const PTR_getter<user_set>&__P,const string &tblname);
string update_to_db(const PTR_getter<user_profile>&__P,const string &tblname);
string update_to_db(const PTR_getter<nick_vec>&__P,const string &tblname);
string update_to_db(const PTR_getter<user_fotos>&__P,const string &tblname);
string update_to_db(const PTR_getter<ignore_vec>&__P,const string &tblname);

string update_to_db(const PTR_getter<contact_vec>&__P,const string &tblname);


#endif

