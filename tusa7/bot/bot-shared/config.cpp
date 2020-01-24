#include "config.h"
#include <string>
#include <stdio.h>
#include <unistd.h>
#include "utils.h"
#include "errs.h"

map<string,string> params;
map<string,bool> access_users;

void load_config()
{
    params.clear();
    FILE *f=fopen(CONFIG_FILE,"r");
    if (!f) throw cError("Error during reading config file "+string(CONFIG_FILE));
    string data;
    while (!feof(f)) {
        char s[1000];
        int z=fread((void*) &s, 1, 990,f);
        s[z]=0;
        data+=s;
    }
    vector<string> v=splitTOK("\r\n",data);
    for (unsigned int i=0;i<v.size();i++) {
        string s=v[i];
        if (s.substr(0,1)=="#" || s.size()<=1) continue;
        int pz=s.find("=",0);
        if (pz==1) {
            logErr("---Error in %s on line %d - '=' not found",CONFIG_FILE,i);
            continue;
        }
        string key=s.substr(0,pz);
        string val=s.substr(pz+1,s.size()-pz-1);
        params[strupper(key)]=val;
    }
    vector<string> aa=splitTOK(", ",params["access_list"]);
    access_users.clear();
    for (unsigned int i=0;i<aa.size();i++) {
        access_users[aa[i]]=true;
    }
}

