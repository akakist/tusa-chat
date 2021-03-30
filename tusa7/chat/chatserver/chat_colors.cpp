#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <errno.h>
#include <map>
#include "_mutex.h"
#include "utils.h"
#include "str_lib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "_mutex.h"
#include <stdio.h>
#include "errs.h"
#include "file_set.h"
#include "chat_colors.h"
#include "server_config.h"
#include "chat_config.h"

__c_packs c_packs;

static void l(const string &fn,string &p,map<string,string> &m, const string &name)
{
    if (!m.count(name)) {
        logErr2("color_pack (%s) member '%s' undefined",fn.c_str(),name.c_str());
        throw cError("color_pack member undefined");
    }
    p=m[name];
}
void load_color_packs(const string &scpack,const string& conf_name)
{

    vector<string> v=splitTOK(",",scpack);
    for (unsigned i=0;i<v.size();i++)
    {
        vector<string> w=splitTOK(":",v[i]);
        if (w.size()==2)
        {
            unsigned id=atoi(w[0].c_str());
            map<string,string> m=load_m_file(w[1]);
            if (m.size())
            {
                c_pack *p=new c_pack;
                l(w[1],p->bnick,m,"bnick");
                l(w[1],p->imagefname,m,"imagefname");
                l(w[1],p->makeit,m,"makeit");
                l(w[1],p->name,m,"name");
                l(w[1],p->nick,m,"nick");
                l(w[1],p->nickpriv,m,"nickpriv");
                l(w[1],p->nickstyle,m,"nickstyle");
                l(w[1],p->privfrom,m,"privfrom");
                l(w[1],p->privto,m,"privto");
                l(w[1],p->stdfrom,m,"stdfrom");
                l(w[1],p->std,m,"std");
                l(w[1],p->stdto,m,"stdto");
                l(w[1],p->sys,m,"sys");
                l(w[1],p->syspriv,m,"syspriv");
                l(w[1],p->sysuser,m,"sysuser");
                c_packs.insert(id,p);
            }
        }
        else
        {
            logErr2("--Error: in %s, item color_pack '%s' has invalid syntax",conf_name.c_str(),v[i].c_str());
            continue;
        }
    }
}

void __c_packs::insert(unsigned int id, const PTR_getter<c_pack > &c)
{
    M_LOCK(Mutex);
    container.insert(pair < unsigned int, PTR_getter<c_pack > >(id, c));
}
PTR_getter<c_pack > __c_packs::get(unsigned int id)
{
    M_LOCK(Mutex);
    map< unsigned int, PTR_getter<c_pack > >::iterator i = container.find(id);
    if (i == container.end()) {
        if (container.size())
            return container.begin()->second;
        else
            throw cError("color packs size=0");
    }
    return i->second;
}
unsigned int __c_packs::get_first_id()
{
    M_LOCK(Mutex);
    if (container.size())
        return container.begin()->first;
    else
        throw cError("color packs size=0");
}
int __c_packs::count(unsigned int n)
{
    M_LOCK(Mutex);
    return container.count(n);
}
