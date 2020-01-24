#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

#include <list>
#include "mutex_inspector.h"
#include <map>
#include "utils.h"
#include "str_lib.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "copy_file.h"
#include "web_tools.h"
#include "chat_config.h"

#include "app_con.h"
#include "app_def.h"

#include "fotos.h"
#include "update_cmd.h"
#include "chat_globals.h"
#include "server_config.h"
#ifdef __WITH_LICENSE
#include "license.h"
#endif
#include "mysql_extens.h"
string thumb_big_url(unsigned int pid);
string thumb_small_url(unsigned int pid);

void foto_remove(unsigned int pid);
void process_update_command(const string& cmd);



bool addfoto(const DB_id& _uid,map<string,string> &params,const string &fdescr)
{
    MUTEX_INSPECTOR;
    st_sqls sqls;
    __foto ft;

    string &fbody=params["foto"];
    if (params["foto_CONTENT-TYPE"]=="image/gif" && fbody.size()>10){
        ft.ext="gif";
    }else{
        ft.ext="jpeg";
    }
    vector<string> z=splitTOK("\\:/",params["foto_FILENAME"].c_str());
    if (z.size()!=0){
        ft.orig_fn=z[z.size()-1];
    }
    ft.size=fbody.size();
    ft.descr=remove_tags(fdescr);
    //string tmp_from=(string)global_config.var_dir.get()+ "/tmp/in/"+itostring((long)&params)+"."+ft.ext;
    //string tmp_to=(string)global_config.var_dir.get()+ "/tmp/out/"+itostring((long)&params)+"."+ft.ext;

    //check_path_wfn(tmp_from);
    //check_path_wfn(tmp_to);
	string pn=itostring((int)&ft)+".jpeg";
	{
		FILE *fin=fopen(pn.c_str(),"wb");
		if (!fin)throw cError("cannot create file "+pn +_DMI());
		size_t r=fwrite(fbody.data(),1,fbody.size(),fin);
		fclose(fin);
	}
    /*{
        MUTEX_INSPECTOR;
    if (r!=fbody.size()){unlink(pn.c_str()); throw cError("insufficient disk space write error"+_DMI());}
#ifdef WIN32
        string cmd="./_img_make_thumbs.php "+pn;
#else
        string cmd="./_img_cvt.exe scale 1000 "+tmp_from+" "+tmp_to +">>"+(string)global_config.var_dir.get()+ "/tmp/img_cvt.log";
#endif

        unlink(tmp_from.c_str());

        if ( load_1_file(fbody,tmp_to)==-1)
        {
            logErr2("cannot load picture %s",tmp_to.c_str());
            return false;
        }
        unlink(tmp_to.c_str());

    }*/
    {
        MUTEX_INSPECTOR;
        st_dbh d;
        QUERY q=(QUERY)"insert into photos (uid,orig_filename,descr,size,ext) values ('?','?','?','?','?')"
                <<CONTAINER(_uid)<<ft.orig_fn<<ft.descr<<ft.size<<ft.ext;
        d.dbh->real_queryQ(q);
        ft.id=atoi(d.dbh->select_1("SELECT LAST_INSERT_ID()"));
    }
	string cmd="./_img_make_thumbs.php "+itostring(ft.id)+" "+pn+" >>/tmp/imglog";
        system(cmd.c_str());
	unlink(pn.c_str());
	st_dbh d;
	unsigned int newid=atoi(d.dbh->select_1Q((QUERY)"select id from photos where id=?"<<ft.id));
	if(ft.id!=newid) return false;
    {
        MUTEX_INSPECTOR;
        PGLW(user_fotos,u,users_fotos.find_by_id_create(CONTAINER(_uid)));
        u->fotos.insert(make_pair(ft.id,ft));
    }
//    foto_remove(ft.id);
    {
        MUTEX_INSPECTOR;
  //      out_oscar_buffer o;
    //    o<<ft<<fbody;
        /*string fn=foto_pn(ft.id,ft.ext);
        check_path_wfn(fn);
        st_FILE fil(fn,"wb");

        fil.puts(fbody);*/


    }

    return true;
}
void url_userphotos(const PTR_getter<chat_user>&__UU, app_connection*cc)
{
    MUTEX_INSPECTOR;
    LICENSE_CK(12);
    st_sqls sqls;
//    unsigned int privs=0;
    DB_id cc_user_id;CONTAINER(cc_user_id)=0;
    if (__UU)
        cc_user_id=user$id(__UU);


    if (!__UU){
        cc->html_out=cc->redirect();return;
    }
    user_pair __U(__UU);

    
    map<string,string> m;
    m["~error~"]="";

    DB_id zid;CONTAINER(zid)=0;
    if (cc->vurl.size())
    {
        MUTEX_INSPECTOR;
        CONTAINER(zid)=atoi(cc->vurl[0]);
        cc->vurl.pop_front();
    }
    

    if (cc->params["foto_FILENAME"].size())
    {
        MUTEX_INSPECTOR;
        if (!addfoto(cc_user_id,cc->params,cc->params["desc"]))
        {
            m["~error~"]="Ќепон€тный формат фотки, ее невозможно загрузить";
            cc->html_out=cc->rvfiles(m,"photos/user_photos");
            return;
        }
        int n=0;
        {
            PGLW(user_fotos,u,users_fotos.find_by_id_create(CONTAINER(cc_user_id)));
            if (u->fotos.size())
            {
                n=u->fotos.rbegin()->first;
            }
        }
        cc->redirect("/userphotos/"+itostring(CONTAINER(cc_user_id))+"/"+itostring(n+1));
        return;
    }
    m["~rate~"]="";
    int nphoto=0;
    if (cc->vurl.size())
    {
        MUTEX_INSPECTOR;
        nphoto=atoi(cc->vurl[0]);
        cc->vurl.pop_front();
    }
    if (nphoto==0)
    {
        MUTEX_INSPECTOR;
        PGLW(user_fotos,z,users_fotos.find_by_id_create(CONTAINER(zid)));
        if (z->fotos.size())
        {
            if (!z->fotos.count(nphoto))
                nphoto=z->fotos.begin()->first;
        }

    }
    {

        m["~rate~"]="";


    }
    
    if (zid==cc_user_id || user__privileges(__U,"$photo")|| user__privileges(__U,"$accounts"))
    {

        MUTEX_INSPECTOR;
        if (cc->params["todo"]=="del")
        {
            bool redir=false;
            {
                MUTEX_INSPECTOR;
                PGLW(user_fotos,z,users_fotos.find_by_id_create(CONTAINER(zid)));

                {
                    if (!z->fotos.count(nphoto))
                    {
                        if (z->fotos.size())
                            nphoto=z->fotos.begin()->first;
                    }
                    if (z->fotos.count(nphoto))
                    {

                        QUERY q;

                        q=(QUERY)"delete from photos where id=? and uid=?"<<nphoto<<CONTAINER(zid);

                        sqls.push_back(q);
                        redir=true;
                        {
                            MUTEX_INSPECTOR;
                            foto_remove(nphoto);
                            //__foto_cache.remove(zid,nphoto);
                            z->fotos.erase(nphoto);

                        }


                    }
                    else logErr2("fotos not found");
                }
            }
            if (redir)
            {
                cc->redirect("/userphotos/"+itostring(CONTAINER(cc_user_id))+"/"+itostring(nphoto));
                return;
            }
        }

    }
    
    if (zid==cc_user_id)
    {
        MUTEX_INSPECTOR;
        if (cc->params["todo"]=="mainphoto")
        {

            {
                PGLW(user_fotos,z,users_fotos.find_by_id_create(CONTAINER(cc_user_id)));

                if (!z->fotos.count(nphoto))
                {
                    logErr2("Error: not found primary foto");
                    return;
                }
                z->primary=nphoto;

            }

            QUERY q=(QUERY)"update tbl_users set primary_photo='?' where id=?"<<nphoto<<CONTAINER(cc_user_id);
            sqls.push_back(q);
            cc->redirect("/userphotos/"+itostring(CONTAINER(cc_user_id))+"/"+itostring(nphoto));
            return;

        }
        

    }
    

    if (CONTAINER(zid)==0 || cc->params["todo"]=="add")
    {
        cc->html_out=cc->rvfiles(m,"photos/add_photo");
        return;
    }
    bool u_fotoadm=user__privileges(__U,"$photo");
    bool u_acc_adm=user__privileges(__U,"$accounts");
    
//    if (cc_user_id==zid ||  u_fotoadm|| u_acc_adm)
    {
        PGLW(user_fotos,z,users_fotos.find_by_id_create(CONTAINER(zid)));
        MUTEX_INSPECTOR;
//        if (cc_user_id==zid)
        {
            if (z->fotos.size()==0)
            {
                if (cc_user_id==zid)
                {
                    cc->html_out=cc->rvfiles(m,"photos/add_photo");
                    return;
                }
                else
                {
                    cc->html_out=cc->rvfiles(m,"photos/no_photo");
                    return;

                }
            }
        }


        if (z->fotos.size()==0)
        {
            cc->html_out="<html><script> alert('Photos for user was not found!');</script>\n";
            return;
        }
        if (!z->fotos.count(nphoto))nphoto=z->fotos.begin()->first;
        if (CONTAINER(zid)==0) //New photo;
        {

        }

        
        m["~prev~"]="0";
        m["~next~"]="0";
        m["~id~"]=itostring(CONTAINER(zid));
        
        if (z->fotos.size())
        {
            

            MUTEX_INSPECTOR;
            int prev=0;
            int next=0;
            vector<unsigned int> flist;
            for (map<unsigned int, __foto> ::const_iterator i=z->fotos.begin();i!=z->fotos.end();i++)
            {
                flist.push_back(i->first);
            }
            
            if (flist.size())
            {
                prev=flist[flist.size()-1];
                next=flist[0];
            }
            
            for (int i=0;i<flist.size();i++)
            {
                MUTEX_INSPECTOR;
                if (nphoto==flist[i])
                {
                    if (i>0) prev=flist[i-1];
                    else prev=flist[flist.size()-1];
                    if (i+1<flist.size()) next=flist[i+1];
                    else next=flist[0];
                }
            }
            
            m["~prev~"]=itostring(prev);
            m["~next~"]=itostring(next);

        }
        
        map<unsigned int, __foto>::iterator pp=z->fotos.find(nphoto);
        if (pp==z->fotos.end()) throw cError("pp==p->photos.end()"+_DMI());
        if (cc->params["todo"]=="onedit")
        {
            pp->second.descr=replace_links(cc->params["desc"]);
            QUERY q=(QUERY)"update photos set descr='?' where uid=? and id=?"<<pp->second.descr<<CONTAINER(cc_user_id)<<pp->first;
            sqls.push_back(q);
        }
        

        m["~descrb~"]=ESB(pp->second.descr);
        m["~descra~"]=ES(pp->second.descr);
        string furl=thumb_big_url(nphoto);
//	"/photos/"+itostring(CONTAINER(zid))+"/"+itostring(nphoto)+"/scale/600/"+itostring(rand()%1000)+"/"+pp->second.orig_fn;
        m["~fname~"]=furl;

        int nsec=1;
        {
            for (map<unsigned int, __foto>::const_iterator i=z->fotos.begin();i!=z->fotos.end();i++,nsec++)
                if (i->first==nphoto)break;
        }
        
        m["~nsec~"]=itostring(nsec);
        m["~n~"]=itostring(nphoto);
        m["~all~"]=itostring(z->fotos.size());
        {
            MUTEX_INSPECTOR;
            map<string,string>q;

            if (zid==cc_user_id)
            {
                if (nphoto==z->primary)
                    m["~mainphoto~"]=RVfiles(q,"photos/mainphoto");
                else
                    m["~mainphoto~"]=RVfiles(q,"photos/mainphoto_link");

            }
            else m["~mainphoto~"]="";
        }
        

        if (z->fotos.size()>1)
        {
            m["~many~"]=RVfiles(m,"photos/many");
        }
        else m["~many~"]="";

        m["~del~"]="";
        m["~add~"]="";
        m["~edit~"]="";
        m["~90~"]="";
        m["~180~"]="";
        m["~270~"]="";
        

        if (cc_user_id==zid || u_fotoadm|| u_acc_adm)
        {
            MUTEX_INSPECTOR;
            m["~del~"]=RVfiles(m,"photos/del");
            if (cc_user_id==zid)
            {
                m["~add~"]=RVfiles(m,"photos/add");
                m["~edit~"]=RVfiles(m,"photos/edit");
                m["~90~"]=RVfiles(m,"photos/90");
                m["~180~"]=RVfiles(m,"photos/180");
                m["~270~"]=RVfiles(m,"photos/270");
            }
        }
        
        if (cc->params["todo"]=="edit" && cc_user_id==zid)
        {
            m["~descrb~"]=RVfiles(m,"photos/edit_form");
        }

        cc->html_out=cc->rvfiles(m,"photos/user_photos");
    }

}
/*-1 error*/ int send_other_from_disk_ext(web_connection * cc, const string & fn,bool use_rv, const string& exten);



struct conc_item
{

    unsigned ucha;
    DB_id uid;
    string nick;

    unsigned int __rate;
    conc_item():ucha(0),__rate(0)
    {
        CONTAINER(uid)=0;
    }

};
struct __concurs
{
    struct __MX
    {
        _mutex Mutex;
        map<unsigned,conc_item> cont;
        vector<conc_item> __sorted;
        vector<unsigned/*ucha*/> sms;
        map<DB_id /*who voted*/, unsigned /*ucha*/> votes;
        static int srt(const conc_item& a, const conc_item&b)
        {
            if (a.__rate>b.__rate) return true;
            if (a.ucha<b.ucha) return true;
            return false;
        }
        void resort()
        {
            MUTEX_INSPECTOR;
            __sorted.clear();
            for (map<unsigned,conc_item>::iterator i=cont.begin();i!=cont.end();i++)
            {
                i->second.__rate=0;

            }
            for ( map<DB_id /*who voted*/, unsigned /*ucha*/> ::iterator i=votes.begin();i!=votes.end();i++)
            {
                if (cont.count(i->second))
                    cont[i->second].__rate++;
            }
            for (unsigned i=0;i<sms.size();i++)
            {
                if (cont.count(sms[i]))
                    cont[sms[i]].__rate++;
            }

            for (map<unsigned,conc_item>::iterator i=cont.begin();i!=cont.end();i++)
            {
                __sorted.push_back(i->second);
            }
            sort(__sorted.begin(),__sorted.end(),srt);
        }

    };
    __MX MX;

public:
    bool loaded;
    __concurs():loaded(false){}
    void ck_load()
    {
        if (!loaded)
        {
            reload();
            loaded=true;
        }
    }
    bool can_vote(const DB_id & who)
    {
        ck_load();
        return true;

    }
    bool add_vote(const DB_id & who, unsigned ucha)
    {
        MUTEX_INSPECTOR;
        ck_load();
        {
            M_LOCK(MX.Mutex);
            if (!MX.votes.count(who))
            {
                MX.votes[who]=ucha;

                st_dbh d;
                d.dbh->real_queryQ((QUERY)"insert into concurs_vote(who, ucha) values (?,?)"<<CONTAINER(who)<<ucha);
                MX.resort();
                return true;
            }
            else
            {
                MX.votes[who]=ucha;
                st_dbh d;
                d.dbh->real_queryQ((QUERY)"update concurs_vote set ucha='?' where who='?'"<<ucha<<CONTAINER(who));
                MX.resort();
                return true;
            }

        }
        return false;
    }
    string add_sms(unsigned  ucha)
    {
        MUTEX_INSPECTOR;
        ck_load();
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"insert into concurs_sms(ucha, dt) values (?,NOW())"<<ucha);
        {
            M_LOCK(MX.Mutex);
            if (MX.cont.count(ucha))
            {
                MX.sms.push_back(ucha);
                MX.resort();
                return "wi progolosovali za u4astnicu N "+itostring(ucha);
            }
            return "oshibka, newerniy nomer u4astnici";

        }

    }
    void reload()
    {
        MUTEX_INSPECTOR;
        {
            M_LOCK(MX.Mutex);
            MX.cont.clear();
            MX.__sorted.clear();
            MX.votes.clear();
        }
        st_dbh d;
        vector<vector<string> >	v=d.dbh->exec("select who,ucha from concurs_vote");
        {
            MUTEX_INSPECTOR;
            for (unsigned i=0;i<v.size();i++)
            {
                if (v[i].size()==2)
                {
                    DB_id who;CONTAINER(who)=atoi(v[i][0]);
                    unsigned ucha=atoi(v[i][1]);
                    {
                        M_LOCK(MX.Mutex);
                        MX.votes[who]=ucha;
                    }
                }
            }
        }
        v=d.dbh->exec("select ucha,uid,nick from concurs_ucha");
        for (unsigned i=0;i<v.size();i++)
        {
            if (v[i].size()==3)
            {
                conc_item it;
                it.ucha=atoi(v[i][0]);
                CONTAINER(it.uid)=atoi(v[i][1]);
                it.nick=v[i][2];
                {
                    M_LOCK(MX.Mutex);
                    MX.cont[it.ucha]=it;
                }
            }
        }
        vector<string> vc=d.dbh->select_1_column("select ucha from concurs_sms");
        for (unsigned i=0;i<vc.size();i++)
        {

            M_LOCK(MX.Mutex);
            MX.sms.push_back(atoi(vc[i]));
        }
        {
            M_LOCK(MX.Mutex);
            for (map<unsigned,conc_item> ::iterator i=MX.cont.begin();i!=MX.cont.end();i++)
            {
                i->second.__rate=0;
            }
        }
        {
            M_LOCK(MX.Mutex);
            MX.resort();
        }

    }

    vector<conc_item> get_sorted()
    {


        M_LOCK(MX.Mutex);
        return MX.__sorted;


    }
    bool get_model(unsigned uid,conc_item& it)
    {
        M_LOCK(MX.Mutex);
        if (MX.cont.count(uid))
        {
            it=MX.cont[uid];
            return true;
        }
        return false;

    }
};

__concurs concurs;
string councurs_add_sms(unsigned ucha)
{
    return concurs.add_sms(ucha);
}
string get_councurs_table(const PTR_getter<chat_user>&__UU)
{
    MUTEX_INSPECTOR;
    concurs.ck_load();
    vector<conc_item> v=concurs.get_sorted();
    string rows;
    DB_id uid;CONTAINER(uid)=0;CONTAINER(uid)=0;
    unsigned int ulevel=0;
    if (__UU)
    {
        uid=user$id(__UU);
        user_pair __U(__UU);
        ulevel=user$level(__U);
    }
    for (unsigned i=0;i<v.size();i++)
    {
        map<string,string>q;
        q["~mesto~"]=itostring(i+1);
        q["~nick~"]=v[i].nick;
        q["~uid~"]=itostring(CONTAINER(v[i].uid));
        q["~nomer~"]=itostring(v[i].ucha);
        q["~balls~"]=itostring(v[i].__rate);
        bool can_vote=ulevel>=300;
        if (can_vote&& CONTAINER(uid))
        {
            can_vote=concurs.can_vote(uid);
        }
        if (can_vote)
            rows+=RVfiles(q,"concurs/table_row_vote");
        else
            rows+=RVfiles(q,"concurs/table_row_novote");
    }
    map<string,string>m;
    m["~rows~"]=rows;

    return RVfiles(m,"concurs/table");
}
void url_concurs_vote(const PTR_getter<chat_user>&__UU, app_connection*cc)
{
    MUTEX_INSPECTOR;
    concurs.ck_load();
    DB_id uid;CONTAINER(uid)=0;CONTAINER(uid)=0;
    unsigned int ulevel=0;
    if (__UU)
    {
        uid=user$id(__UU);
        user_pair __U(__UU);
        ulevel=user$level(__U);
    }
    bool can_vote=ulevel>=300;
    if (can_vote&& CONTAINER(uid))
    {
        can_vote=concurs.can_vote(uid);
    }

    unsigned mid=atoi(cc->params["id"]);
    conc_item it;
    map<string,string> m;
    m["~uid~"]="0";
    m["~nick~"]="";
    m["~nomer~"]="";
    m["~error~"]="";
    m["~mesto~"]="";
    m["~balls~"]="";
    if (concurs.get_model(mid,it))
    {
        MUTEX_INSPECTOR;
        if (cc->params["todo"]=="update")
        {
            MUTEX_INSPECTOR;
            if (concurs.add_vote(user$id(__UU),mid))
                m["~error~"]=_MSG("model_vote_success");
            else
                m["~error~"]=_MSG("model_vote_fail");
            can_vote=false;
            cc->html_out=cc->rvfiles(m,"concurs/vote_end");
            return;

        }
        m["~uid~"]=itostring(CONTAINER(it.uid));
        m["~nomer~"]=itostring(it.ucha);
        m["~nick~"]=it.nick;
        m["~balls~"]=itostring(it.__rate);
        if (can_vote)
        {
            cc->html_out=cc->rvfiles(m,"concurs/vote_yes");
        }
        else
        {
            MUTEX_INSPECTOR;
            if (CONTAINER(uid)==0)
            {
                cc->html_out=cc->rvfiles(m,"concurs/vote_nologged");
                return;
            }
            if (ulevel<300)
            {
                cc->html_out=cc->rvfiles(m,"concurs/vote_lowlevel");
                return;

            }
            cc->html_out=cc->rvfiles(m,"concurs/vote_voted");
            return;
        }
    }

}
