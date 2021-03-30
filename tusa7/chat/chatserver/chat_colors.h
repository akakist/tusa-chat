#ifndef CHAT_COLORS_H
#define CHAT_COLORS_H
#include "PTR.h"
#include <string>
#include <map>
//#include  "object.h"

class c_pack: public base_container
{
public:
    c_pack():base_container("c_pack") {}
    string bnick;
    string makeit;
    string nick;
    string nickpriv;
    string privfrom;
    string privto;
    string stdfrom;
    string std;
    string stdto;
    string sys;
    string syspriv;
    string sysuser;
    int id;
    string name;
    string imagefname;
    string nickstyle;

};
struct __c_packs
{
    _mutex Mutex;
    map<unsigned int,PTR_getter<c_pack> > container;
public:
    void insert(unsigned int id,const PTR_getter<c_pack> &c);
    PTR_getter<c_pack> get(unsigned int id);
    unsigned int get_first_id();
    int count(unsigned int n);
    __c_packs():Mutex("__c_packs") {}
};
extern __c_packs c_packs;

string _nick$(const string &s,const bool priv,const PTR_getter<c_pack> &color_pack );
string _badnick$(const string &s,const PTR_getter<c_pack> &color_pack );

#endif
