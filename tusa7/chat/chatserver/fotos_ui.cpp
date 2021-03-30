#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <map>
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "web_server.h"
#include "message.h"
#include "chat_def.h"

#include <sys/stat.h>
#include <sys/types.h>
#include "register.h"
#include "copy_file.h"
#include "wrappers.h"
#include "web_tools.h"
#include "file_set.h"
#include "register.h"
#include "levels.h"
#include "server_config.h"

#include "chat_colors.h"
#include "chat_config.h"

#include "app_con.h"
#include "app_def.h"

#include "fotos.h"
#include "update_cmd.h"
#include "cs_conn_data.h"
#include "DR_types.h"

string foto_pn_cache(const DB_id& uid,unsigned int pid, unsigned int xsize,const string& ext);
void foto_rm_cache(const DB_id& uid,unsigned int pid);
void process_update_command(const string& cmd);

void addfoto(const DB_id& _uid,map<string,string> &params,/*const string &dr,*/const string &fdescr)
{
    __foto ft;

    if (params["foto_CONTENT-TYPE"]=="image/gif" && params["foto"].size()>10) {
        ft.ext="gif";
    } else {
        ft.ext="jpeg";
    }

    vector<string> z=splitTOK("\\:/",params["foto_FILENAME"].c_str());
    if (z.size()!=0) {
        ft.orig_fn=z[z.size()-1];
    }
    ft.size=params["foto"].size();
    ft.descr=fdescr;

    unsigned int fid=0;
    {
        PGLW(user_fotos,u,users_fotos.find_by_id(_uid));
        if (u->fotos.size()) fid=u->fotos.rbegin()->second.id;
    }
    fid++;
    ft.id=fid;
    ft.uid=_uid;

    {
        PGLW(user_fotos,u,users_fotos.find_by_id(_uid));
        u->fotos.insert(make_pair(ft.id,ft));
    }
    foto_rm_cache(_uid,fid);
    {
        out_oscar_buffer o;
        o<<ft;
#ifdef ACCEPT_PHOTOS
        send_update_g2(foto$add,o);
#endif
    }
    {
        out_oscar_buffer o;
        o<<ft<<params["foto"];
#ifdef ACCEPT_PHOTOS
        send_update_g2_cs_only(foto$set_body,o);
#endif
    }


}
void url_user_photos(cs_conn_data *cc)
{
    unsigned int privs=0;
    int level=0;

    PTR_getter<chat_user> __UU=local_users.get(cc->user_id);
    if (__UU)
    {
        user_pair __U(__UU);
        privs=user$privileges(__U);
        level=user$level(__U);
    }
    map<string,hstring> m;

    DB_id zid;
    zid.container=atoi(cc->params["id"].c_str());
    if (cc->params["foto_FILENAME"].size())
    {
        addfoto(cc->user_id,cc->params,cc->params["desc"]);
        int n=0;
        {
            PGLW(user_fotos,u,users_fotos.find_by_id(cc->user_id));
            if (u->fotos.size())
            {
                n=u->fotos.rbegin()->first;
            }
        }
        cc->redirect("/userphotos?id="+itostring(cc->user_id.container)+"&n="+itostring(n));
        return;
    }
    m["~rate~"]="";
    if (__UU && cc->user_id.container && zid!=cc->user_id && level>=300)
    {
        map<string,hstring>q;
        int n=atoi(cc->params["n"]);

        vector<pair<string,string> > v;
        int curr_rate=0;
        for (unsigned i=0;i<11;i++)
        {
            string si=itostring(i);
            v.push_back(make_pair(si,si));
        }

        if (cc->params["todo"]=="rate")
        {
            curr_rate=atoi(cc->params["rating"]);


            PGLW(user_fotos,z,users_fotos.find_by_id(zid));
            if (z->fotos.count(n))
            {
                if (curr_rate==0)
                    z->fotos[n].rates.erase(cc->user_id);
                else z->fotos[n].rates[cc->user_id]=curr_rate;

                out_oscar_buffer o;
                o<<foto$set_rate<<zid<<n<<cc->user_id<<curr_rate;
                process_update_command(o.as_string());
            }

        }
        else
        {
            PGLW(user_fotos,z,users_fotos.find_by_id(zid));
            if (!z->fotos.count(n))n=z->fotos.begin()->first;

            if (z->fotos.count(n))
            {
                if (z->fotos[n].rates.count(cc->user_id))
                {
                    curr_rate=z->fotos[n].rates[cc->user_id];
                }
            }

        }
        q["~rating_select~"]=make_select("rating",v,itostring(curr_rate));
        m["~rate~"]=make_pair(q,"photos/rate");


    }
    if (zid==cc->user_id || privs&u_is_photo_admin || privs& u_is_accounts_admin)
    {
        if (cc->params["todo"]=="del")
        {
            PGLW(user_fotos,z,users_fotos.find_by_id(zid));
            int n=atoi(cc->params["n"]);
            {
                if (z->fotos.count(n))
                {

                    send_update_g4(foto$remove,zid,n,z->fotos.find(n)->second.ext);
                    z->fotos.erase(n);

                }
            }
        }

    }
    if (zid==cc->user_id)
    {
        if (cc->params["todo"]=="90"
                || cc->params["todo"]=="180"
                || cc->params["todo"]=="270"
           )
        {
            string ext;
            int nph1=atoi(cc->params["n"]);
            {
                PGLW(user_fotos,z,users_fotos.find_by_id(cc->user_id));

                if (!z->fotos.count(nph1))
                {
                    return;
                }
                ext=z->fotos.find(nph1)->second.ext;

            }
            if (ext=="jpeg")
            {
                string fn=foto_pn(cc->user_id,nph1,ext);
                string cmd="./_img_cvt.exe rotate "+cc->params["todo"]+" "+fn;
                system(cmd.c_str());
                foto_rm_cache(cc->user_id,nph1);
                {
                    PGLW(user_fotos,z,users_fotos.find_by_id(cc->user_id));
                    if (z->fotos.count(nph1))
                    {
                        string f=z->fotos[nph1].orig_fn;
                        int pz=f.rfind(".");
                        string f2;
                        if (pz!=-1)
                        {
                            f2=f.substr(0,pz)+"r"+f.substr(pz,f.size()-pz);
                        }
                        else
                            f2=f+"r";
                        z->fotos[nph1].orig_fn=f2;
                    }
                }
            }
        }
    }

    if (zid.container==0 || cc->params["todo"]=="add")
    {
        cc->html_out=make_pair(m,"photos/add_photo");
        return;
    }
    if (cc->user_id==zid ||  privs&u_is_photo_admin || privs& u_is_accounts_admin) {
        PGLW(user_fotos,z,users_fotos.find_by_id(zid));
        if (z->fotos.size()==0)
        {
            if (cc->user_id==zid)
            {
                cc->html_out=make_pair(m,"photos/add_photo");
                return;
            }
            else
            {
                cc->html_out=make_pair(m,"photos/no_photo");
                return;

            }
        }

    }
    {
        unsigned int n=atoi(cc->params["n"]);
        PGLW(user_fotos,z,users_fotos.find_by_id(zid));
        if (z->fotos.size()==0)
        {
            cc->html_out="<html><script> alert('Photos for user was not found!');</script>";
            return;
        }
        if (!z->fotos.count(n))n=z->fotos.begin()->first;
        if (zid.container==0) //new photo;
        {

        }

        m["~prev~"]="0";
        m["~next~"]="0";
        m["~id~"]=itostring(zid.container);
        if (z->fotos.size())
        {

            int prev=0;
            int next=0;

            if (!z->fotos.count(n)) n=z->fotos.begin()->first;
            if (n==z->fotos.begin()->first)
            {
                prev=z->fotos.rbegin()->first;
                map<unsigned int, __foto> ::iterator it=z->fotos.find(n);
                it++;
                next=it->first;
            }

            else if (n==z->fotos.rbegin()->first)
            {
                next=z->fotos.begin()->first;
                map<unsigned int, __foto> ::iterator it=z->fotos.find(n);
                it--;
                prev=it->first;
            }
            else
            {
                {
                    map<unsigned int, __foto> ::iterator it0,it=z->fotos.find(n);
                    it0=it;
                    it++;
                    next=it->first;
                    it0--;
                    prev=it0->first;
                }
            }
            m["~prev~"]=itostring(prev);
            m["~next~"]=itostring(next);

        }
        map<unsigned int, __foto>::iterator pp=z->fotos.find(n);
        if (pp==z->fotos.end()) throw cError("pp==p->photos.end()");
        if (cc->params["todo"]=="onedit")
        {
            pp->second.descr=replace_links(cc->params["desc"]);
#ifdef ACCEPT_PHOTOS
            send_update_g4(foto$change_description,cc->user_id,pp->first,pp->second.descr);
#endif
        }

        m["~descrb~"]=ESB(pp->second.descr);
        m["~descra~"]=ES(pp->second.descr);
        m["~fname~"]="/photos/700/"+itostring(zid.container)+"/"+itostring(n)+"/"+itostring(rand()%1000)+"/"+pp->second.orig_fn;
        int nsec=1;
        {
            for (map<unsigned int, __foto>::iterator i=z->fotos.begin();i!=z->fotos.end();i++,nsec++)
                if (i->first==n)break;
        }
        m["~nsec~"]=itostring(nsec);
        m["~n~"]=itostring(n);
        m["~all~"]=itostring(z->fotos.size());

        if (z->fotos.size()>1)
        {
            m["~many~"]=make_pair(m,"photos/many");
        }
        else m["~many~"]="";

        m["~del~"]="";
        m["~add~"]="";
        m["~edit~"]="";
        m["~90~"]="";
        m["~180~"]="";
        m["~270~"]="";

        if (cc->user_id==zid || privs&u_is_photo_admin || privs& u_is_accounts_admin)
        {
            m["~del~"]=make_pair(m,"photos/del");
            if (cc->user_id==zid)
            {
                m["~add~"]=make_pair(m,"photos/add");
                m["~edit~"]=make_pair(m,"photos/edit");
                m["~90~"]=make_pair(m,"photos/90");
                m["~180~"]=make_pair(m,"photos/180");
                m["~270~"]=make_pair(m,"photos/270");
            }
        }
        if (cc->params["todo"]=="edit" && cc->user_id==zid)
        {
            m["~descrb~"]=make_pair(m,"photos/edit_form");
        }

        cc->html_out=make_pair(m,"photos/user_photos");
    }
}
/*-1 error*/ int send_other_from_disk_ext(web_connection * cc, const string & fn,bool use_rv, const string& exten);

void check_scaled_foto(const DB_id &uid,unsigned int pid,const string& ext,int xsz)
{
    string fc=foto_pn_cache(uid,pid, xsz,ext);
    struct stat st;
    if (stat(fc.c_str(),&st))
    {
        string fn=foto_pn(uid,pid,ext);
#ifndef __CLAN
        string cmd="./_img_cvt.exe scale "+itostring(xsz)+" "+fn+" "+fc;
        system(cmd.c_str());
#else
        out_oscar_buffer o;
        o<<uid<<pid<<ext<<xsz;
        string r=clan_data_request(DR_get_foto,o);
        oscar_buffer bb(r.data(),r.size());
        string body;
        bb>>body;
        check_path_wfn(fc);
        FILE *f=fopen(fc.c_str(),"wb");
        if (f)
        {
            fwrite(body.data(),body.size(),1,f);
            fclose(f);
        }
#endif
    }
}
void url_user_photo(cs_conn_data* cc)
{
    if (!cc->wc) throw cError("if(!cc->wc)");

    cc->wc->allow_build_response=false;
    vector<string> z=splitTOK("/",cc->url);
    if (z.size()<4) {
        return;
    }
    try {
        string fn;
        int xsz=atoi(z[1]);
        DB_id uid;
        uid.container=atoi(z[2]);
        unsigned int pid=atoi(z[3]);
        string ext;
        {
            PGLR(user_fotos, z,users_fotos.find_by_id(uid));
            if (!z->fotos.count(pid)) return;
            ext=z->fotos.find(pid)->second.ext;
        }
        check_scaled_foto(uid,pid,ext,xsz);
        fn=foto_pn_cache(uid,pid, xsz,ext);

        {
            send_other_from_disk_ext(cc->wc,fn,false,ext);
        }
    }
    catch (cError e)
    {
        logErr2("catched %s [%s]",e.what(),cc->peer_ipaddress.c_str());
    }

    catch (...)
    {
        logErr2("catched ... [%s] %s %d",cc->peer_ipaddress.c_str(),__FILE__,__LINE__);
    }
}
