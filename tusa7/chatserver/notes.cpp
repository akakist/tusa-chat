#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <map>

#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "web_server.h"
#include "message.h"
#include "chat_def.h"
#include "copy_file.h"
#include "wrappers.h"
#include "file_set.h"
#include "notes.h"
#include "levels.h"
#include "server_config.h"
#include "chat_config.h"
#include "app_con.h"
#include "app_def.h"

#include "user.h"
#include "user_credits.h"
#include "update_cmd.h"
#include "ignore_vec.h"
#include "web_tools.h"
#include "cs_conn_data.h"
#include "chat_globals.h"
#include "DR_types.h"

void load(unsigned int & n, const string &s, map<string,string>&m);
void load(int & n, const string &s, map<string,string>&m);

string update_to_db(const PTR_getter<u_notes>&__P,const string &tblname);
string update_to_db(const PTR_getter<note_text>&__P,const string &tblname);
string FOLD_ID(const DB_id&  uid, unsigned int fold);


static void url_notes_send(const PTR_getter<chat_user> &__U,cs_conn_data* cc);
void check_notes_config(const DB_id&  uid);
string RVfiles(const char *filekey);

string attach_pn(const DB_id&,unsigned int msgid, const string& orig);

void delete_message(const PTR_getter<chat_user> &__U,const DB_id&  uid,unsigned int msgid);
void move_message(const PTR_getter<chat_user> &__UN,unsigned int fold,unsigned int to_folder,unsigned int msgid, bool save_filter);
/*-1 error*/
int send_other_from_disk_ext(web_connection * cc, const string & fn,bool use_rv, const string& exten);
vector<string> get_id_uid_nick_by_nick(const string &to_nick);

struct note
{
    string from_nick;
    unsigned int from_nick_id;
};
static void url_notes_frames(const PTR_getter<chat_user> &__UU,cs_conn_data* cc)
{


    if (!__UU || cc->user_unregistered) {
        cc->html_out=cc->redirect();
        return;
    }
    map<string,hstring> m;
    if (cc->params["f"]=="") {
        m["~folder~"]="";
    } else {
        m["~folder~"]="?f="+cc->params["f"];
    }
    cc->html_out+=make_pair (m, "notes/frames");
}


static string make_folders_select(const vector<old_notes_folder> &v,const string &name, unsigned int def_folder)
{
    string res="<SELECT name="+name+">";
    for (unsigned int i=0;i<v.size();i++) {
        res+="<OPTION value="+itostring(v[i].id);
        if (v[i].id==def_folder) res+=" SELECTED";
        res+=">"+v[i].name;
    }
    res+="</SELECT>";
    return res;
}
void mark_msg_answered(const DB_id&  uid,unsigned int msgid)
{
    DB_id from_uid;
    unsigned int notify_read;
    {
        __NOTE_LOCKW(uid);
        map<unsigned int,__note_head> ::iterator h=u->map_msgs.find(msgid);
        if (h!=u->map_msgs.end())
        {
            if (h->second.nfh.to_uid!=uid.container) return;

            from_uid.container=h->second.nfh.from_uid;

            h->second.nfh.unread=false;
            send_update_g3(note$set_unread,uid,msgid);
            notify_read=h->second.nfh.notify_read;
            if (h->second.nfh.status==__note_head::STATUS_READ)
            {
                h->second.nfh.status=__note_head::STATUS_READ_ANSWERED;
                send_update_g4(note$set_status,uid,msgid,__note_head::STATUS_READ_ANSWERED);

            }

        }
        else
        {
            logErr2("msg not found %s","");
            return;
        }
    }
    if (from_uid.container!=0 && notify_read!=0)
    {
        __NOTE_LOCKW(from_uid);
        map<unsigned int,__note_head> ::iterator h=u->map_msgs.find(notify_read);
        if (h!=u->map_msgs.end())
        {
            h->second.nfh.unread=false;
            {
                send_update_g3(note$set_unread,from_uid,notify_read);

            }
            if (h->second.nfh.status==__note_head::STATUS_READ)
            {
                h->second.nfh.status=__note_head::STATUS_READ_ANSWERED;
                send_update_g4(note$set_status,from_uid,notify_read,__note_head::STATUS_READ_ANSWERED);

            }
        }
        else
        {
#ifdef DEBUG
            logErr2("parent msg not found");
#endif
        }
    }
}
void mark_msg_read(const DB_id& uid,unsigned int __msgid)
{
    DB_id from_uid;
    unsigned int notify_read;
    {
        __NOTE_LOCKW(uid);
        unsigned int msgid=__msgid;
        map<unsigned int,__note_head> ::iterator h=u->map_msgs.find(msgid);
        if (h!=u->map_msgs.end())
        {
            if (h->second.nfh.to_uid!=uid.container) return;
            h->second.nfh.unread=false;
            {
                send_update_g3(note$set_unread,uid,msgid);
            }

            from_uid.container=h->second.nfh.from_uid;

            if (h->second.nfh.status==__note_head::STATUS_UNREAD_SENT)
            {
                h->second.nfh.status=__note_head::STATUS_READ;
                send_update_g4(note$set_status,uid,msgid,__note_head::STATUS_READ);

            }
            notify_read=h->second.nfh.notify_read;


        }
        else
        {
            logErr2("msg not found %s","");
            return;
        }
    }
    if (from_uid.container)
    {
        __NOTE_LOCKW(from_uid);
        map<unsigned int,__note_head> ::iterator h=u->map_msgs.find(notify_read);
        if (h!=u->map_msgs.end())
        {
            h->second.nfh.unread=false;
            send_update_g3(note$set_unread,from_uid,notify_read);

            if (h->second.nfh.status==__note_head::STATUS_UNREAD_SENT)
            {
                h->second.nfh.status=__note_head::STATUS_READ;
                send_update_g4(note$set_status,from_uid,notify_read,__note_head::STATUS_READ);

            }
        }
    }

}

static void url_notes_read(const PTR_getter<chat_user> &__UU,cs_conn_data* cc)
{
    if (!__UU || cc->user_unregistered) return;
    user_pair __U(__UU);
    DB_id u_id=user$id(__U);
    map<string,hstring> m;
    unsigned int folder=atoi(cc->params["f"]);
    int id=atoi(cc->params["id"]);
    int next_id=0;
    int prev_id=0;
    bool found=false;
    __note_head h;
    {
        __NOTE_LOCK(u_id);

        if (!u->map_folders.count(folder)) throw cError("folder not found");
        map<unsigned int,__note_folder>::const_iterator ff=u->map_folders.find(folder);
        for (unsigned j=0;j<ff->second.vec_msgs.size();j++)
        {
            if (ff->second.vec_msgs[j]==id)
            {
                found=true;
                if (j>0) prev_id=ff->second.vec_msgs[j-1];
                if (j<ff->second.vec_msgs.size()-1)next_id=ff->second.vec_msgs[j+1];
            }
        }
        if (found)
        {
            if (!u->map_msgs.count(id)) throw cError("--Error !un->map_msgs.count(id)");
            h=u->map_msgs.find(id)->second;
        }
    }

    if (!found) {
        map<string,hstring> K;
        cc->html_out+=make_pair(K,"notes/read_badmessage");
        return;
    }
    if (cc->params["del"]=="1") {
        delete_message(__UU,cc->user_id,id);
        id=0;
        if (next_id!=0) {
            id=next_id;
        }
        if (id==0 && prev_id!=0) {
            id=prev_id;
        }
        if (id==0) {
            cc->params["del"]="";
            cc->redirect("notes?f="+itostring(folder));
            return;
        }
        found=false;
        {
            __NOTE_LOCK(u_id);

            map<unsigned int,__note_folder>::const_iterator ff=u->map_folders.find(folder);
            if (ff==u->map_folders.end()) throw cError("Folder not found");
            for (unsigned j=0;j<ff->second.vec_msgs.size();j++)
            {
                if (ff->second.vec_msgs[j]==id)
                {
                    found=true;
                    if (j>0) prev_id=ff->second.vec_msgs[j-1];
                    if (j<ff->second.vec_msgs.size()-1)next_id=ff->second.vec_msgs[j+1];
                }
            }
            if (found)
            {
                if (!u->map_msgs.count(id)) throw cError("--Error !un->map_msgs.count(id)");
                h=u->map_msgs.find(id)->second;
            }
        }
    }
    if (h.nfh.unread) {		//set note status to read (for receiver and sender)
        mark_msg_read(cc->user_id,h.id);
    }

    retr_result fold=retrive_folders(cc,folder,__UU);
    m["~foldername~"]=fold.current_folder;
    m["~folders~"]=fold.all_folders;
    m["~fnid~"]=itostring(h.nfh.from_uid)+"."+itostring(h.nfh.from_nick_id);
    m["~tnid~"]=itostring(h.nfh.to_uid)+"."+itostring(h.nfh.to_nick_id);
    m["~from~"]=h.nfh.from_nick;
    m["~to~"]=h.nfh.to_nick;
    m["~subj~"]=h.nfh.subject;
    m["~date~"]=datetime2rus(h.nfh.send_date);


    string body;
    {
        PGLR(note_text,n,note_texts.find_by_id(itostring(cc->user_id.container)+"."+itostring(h.id)))
        body=n->body;
    }



    m["~message~"]=body;
    m["~delhref~"]="/notes/read?id="+itostring(h.id)+"&del=1&f="+itostring(folder);
    m["~id~"]=itostring(h.id);

    if (h.nfh.has_attachment) {
        m["~file~"]="";
        m["~efile~"]="";
    } else {
        m["~file~"]="<!--";
        m["~efile~"]="-->";
    }
    m["~filepath~"]="/attach/"+itostring(cc->user_id.container)+"/"+itostring(folder)+"/"+itostring(h.id)+"/"+h.nfh.attachment_filename;
    m["~filename~"]=h.nfh.attachment_filename;
    m["~filesize~"]=number2text(h.nfh.attachment_content_length);

    if (prev_id!=0) {
        m["~prev~"]="href=\"/notes/read?id="+itostring(prev_id)+"&f="+itostring(folder)+"\"";
    } else {
        m["~prev~"]="";
    }
    if (next_id!=0) {
        m["~next~"]="href=\"/notes/read?id="+itostring(next_id)+"&f="+itostring(folder)+"\"";
    } else {
        m["~next~"]="";
    }
    cc->html_out+=make_pair(m,"notes/read");
}

static void url_notes_write(const PTR_getter<chat_user> &__UU,cs_conn_data* cc)
{

    if (!__UU || cc->user_unregistered) return;
    user_pair __U(__UU);
    DB_id u_id=user$id(__U);
    if (user$nicks_size(cc->user_id.container)==0) {
        map<string,hstring> m;
        m["~new~"]="";
        cc->html_out+=make_pair(m,"notes/write_nonicks");
        return;
    }
    map<string,hstring> m;
    m["~tonick~"]="";
    m["~nicks~"]=build_nicks_select(__U,"fromnick",GET_CNICK_ID(__U),"style=\"width: 150\"");
    m["~subj~"]="";
    m["~script~"]="";
    m["~file~"]="";
    m["~efile~"]="";
    {
        if (cc->params["id"]!="") {		//reply
            int iid=atoi(cc->params["id"]);
            __note_head h;
            bool found=false;
            {
                __NOTE_LOCK(u_id);
                found=u->find_msg_by_id(iid,h);
            }
            mark_msg_answered(cc->user_id,iid);

            if (found)
            {
                if (!h.nfh.system)
                {
                    string subj=h.nfh.subject;
                    if (subj.substr(0,3)!="Re:") {
                        subj="Re: "+subj;
                    }
                    m["~subj~"]=subj;
                    m["~tonick~"]=h.nfh.from_nick;
                    int nick=0;
                    m["~nicks~"]=build_nicks_select(__U,"fromnick",h.nfh.to_nick,"style=\"width: 150\"");
                    m["~script~"]="<script>document.f.msg.focus();</script> <input type=hidden name=id value=\""+cc->params["id"]+"\">";
                }
            }
        }
    }
    int level=user$level(__U);
    if (level/sub_levels==am_sadmin) {
        m["~sys~"]="";
        m["~esys~"]="";
    } else {
        m["~sys~"]="<!--";
        m["~esys~"]="-->";
    }
    m["~important~"]="";
    retr_result res=retrive_folders(cc,0,__UU);
    m["~folders~"]=res.all_folders;
    cc->html_out+=make_pair(m,"notes/write");
}


static void url_notes_sent(const PTR_getter<chat_user>&__UU, cs_conn_data* cc)
{

    if (!__UU || cc->user_unregistered) return;
    user_pair __U(__UU);
    retr_result r=retrive_folders(cc,0,__UU);
    map<string,hstring> m;
    DB_id u_id=user$id(__U);
    m["~folders~"]=r.all_folders;
    bool save_copy;
    {
        PGLR(user_set,u,__U.us);
        save_copy=u->notes_save_copy;
    }
    {
        __NOTE_LOCK(u_id);

        unsigned int sfld=0;
        for (map<unsigned int,__note_folder>::const_iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
        {
            if (i->second.filter_out.count(0)) sfld=i->first;
        }
        if (!sfld) throw cError("!sent folder");
        if (!save_copy) {
            if (r.vec_folders.size()) m["~sent_folder~"]=itostring(r.vec_folders[0].id);
        } else {
            m["~sent_folder~"]=itostring(sfld);
        }
    }
    cc->html_out=make_pair(m,"notes/sent");
}

static void url_notes_settings(const PTR_getter<chat_user> &__UU,cs_conn_data* cc)
{

    if (!__UU || cc->user_unregistered) return;
    user_pair __U(__UU);
    DB_id u_id=user$id(__U);
    map<string,hstring> m;

    string cmd=cc->params["cmd"];
    if (cmd=="settings") {


        {

            {
                unsigned int dest_f=atoi(cc->params["send_to_folder"]);
                if (dest_f)
                {
                    bool need_change=false;
                    {
                        __NOTE_LOCKW(u_id);
                        if (!u->map_folders.count(dest_f)) throw cError("destination folder not found ");
                        for (map<unsigned int,__note_folder>::iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
                        {
                            if (i->second.filter_out.count(0) && dest_f!=i->first)
                                need_change=true;
                        }

                    }

                    if (need_change)
                    {
                        __NOTE_LOCKW(u_id);
                        if (!u->map_folders.count(dest_f)) throw cError("destination folder not found ");
                        for (map<unsigned int,__note_folder>::iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
                        {
                            if (i->second.filter_out.count(0) && dest_f!=i->first) {
                                i->second.filter_out.erase(0);

                                send_update_g4(note$filter_out_delete,u_id,i->first,0);
                                u->map_folders[dest_f].filter_out.insert(0);
                                send_update_g4(note$filter_out_insert,u_id,dest_f,0);
                                break;
                            }
                        }
                    }
                }

            }
            {
                unsigned int dest_f=atoi(cc->params["recv_from_folder"]);
                if (dest_f)
                {
                    bool need_change=false;
                    {
                        __NOTE_LOCKW(u_id);
                        if (!u->map_folders.count(dest_f)) throw cError("destination folder not found ");
                        for (map<unsigned int,__note_folder>::iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
                        {
                            if (i->second.filter_in.count(0) && dest_f!=i->first)
                                need_change=true;

                        }
                    }
                    if (need_change)
                    {
                        __NOTE_LOCKW(u_id);
                        if (!u->map_folders.count(dest_f)) throw cError("destination folder not found ");
                        for (map<unsigned int,__note_folder>::iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
                        {
                            if (i->second.filter_in.count(0) && dest_f!=i->first) {
                                i->second.filter_in.erase(0);
                                send_update_g4(note$filter_in_delete,u_id,i->first,0);
                                u->map_folders[dest_f].filter_in.insert(0);
                                send_update_g4(note$filter_in_insert,u_id,dest_f,0);
                                break;
                            }
                        }
                    }

                }
            }

        }
        {
            PGLW(user_set,u,__U.us);
            bool notes_save_copy=strupper(cc->params["save_copy"])=="ON";
            if (u->notes_save_copy!=notes_save_copy)
            {
                u->notes_save_copy=notes_save_copy;
                send_update_g3(user_set$notes_save_copy,u_id,u->notes_save_copy);
            }
            unsigned int notes_msg_per_page=atoi(cc->params["msg_per_page"]);
            if (u->notes_msg_per_page!=notes_msg_per_page)
            {
                u->notes_msg_per_page=notes_msg_per_page;
                send_update_g3(user_set$notes_msg_per_page,u_id,u->notes_msg_per_page);

            }
        }

    }
    if (cmd=="new_folder") {
        string fname=cc->params["new_folder"];
        if (fname.size()>30) fname=fname.substr(0,30);
        unsigned int newfid=1;
        {
            __NOTE_LOCKW(u_id);
            if (u->map_folders.size())
                newfid=u->map_folders.rbegin()->first+1;

        }
        {
            __NOTE_LOCKW(u_id);
            __note_folder f;
            f.name=fname;
            u->map_folders[newfid]=f;
            u->map_folders[newfid].name=fname;
        }
        send_update_g4(note$folder_create,u_id,newfid,fname);
    }
    if (cmd=="rename") {
        string fname=cc->params["nname"];
        if (fname.size()>30) fname=fname.substr(0,30);
        bool found=false;
        unsigned int fid=atoi(cc->params["id"]);
        {
            __NOTE_LOCKW(u_id);
            if (u->map_folders.count(fid))
            {
                u->map_folders[fid].name=fname;
            }
        }
        send_update_g4(note$folder_rename,u_id,fid,fname);
    }
    if (cmd=="remove") {
        unsigned int fid=atoi(cc->params["id"]);
        {
            __NOTE_LOCKW(u_id);
            if (u->map_folders.count(fid))
            {
                if (u->map_folders.find(fid)->second.vec_msgs.size())
                {
                    cc->html_out=(string)RVfiles("/notes/msg_fld_not_empty");
                    return;
                }
            }
            u->map_folders.erase(fid);

        }
        send_update_g3(note$folder_remove,u_id,fid);
    }
    retr_result r=retrive_folders(cc,0,__UU);
    {
        {
            __NOTE_LOCKW(u_id);
            unsigned int sent_f=0, recvd_f=0;
            for (map<unsigned int,__note_folder>::iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
            {
                if (i->second.filter_out.count(0)) sent_f=i->first;
                if (i->second.filter_in.count(0)) recvd_f=i->first;
            }

            m["~send_to_folder~"]=make_folders_select(r.vec_folders,"send_to_folder",sent_f);
            m["~recv_from_folder~"]=make_folders_select(r.vec_folders,"recv_from_folder",recvd_f);
        }
        {
            PGLR(user_set,u,__U.us);
            m["~msg_per_page~"]=itostring(u->notes_msg_per_page);
            m["~save_copy~"]=checked(u->notes_save_copy);

        }
        m["~folders~"]=r.all_folders;
        hstring ff;
        for (unsigned int i=0;i<r.vec_folders.size();i++) {
            map<string,hstring> q;
            q["~name~"]=r.vec_folders[i].name;
            q["~id~"]=itostring(r.vec_folders[i].id);
            if (r.vec_folders[i].cnt>0) {
                q["~confirm~"]="1";
            } else {
                q["~confirm~"]="0";
            }
            q["~may_remove~"]="1";
            ff+=make_pair(q,"notes/settings_folder");
        }
        m["~folders_table~"]=ff;
    }
    cc->html_out+=make_pair(m,"notes/settings");
}


static void mk_move(const PTR_getter<chat_user> &__UU, cs_conn_data* cc, unsigned int folder)
{
    user_pair __U(__UU);
    DB_id u_id=user$id(__U);
    unsigned int to_folder=atoi(cc->params["move_to"]);
    bool save_filter=strupper(cc->params["save_filter"])=="ON";
    for (map<string,string>::iterator i=cc->params.begin();i!=cc->params.end();i++) {
        if (strupper(i->second)!="ON") {
            continue;
        }
        string c=i->first;
        if (c.substr(0,3)!="cid") {
            continue;
        }
        move_message(__UU,folder,to_folder,atoi(c.substr(3,c.size()-3)), save_filter);
    }
    unsigned char sort;
    bool sort_desc;

    {
        PGLR(user_set,u,__U.us);
        sort=u->notes_sort;
        sort_desc=u->notes_sort_desc;
    }
    {
        __NOTE_LOCKW(u_id);
        u->resort(sort,sort_desc);
    }

}
static void mk_del(const PTR_getter<chat_user> &__UU, cs_conn_data* cc, unsigned int folder)
{
    user_pair __U(__UU);
    DB_id u_id=user$id(__U);
    for (map<string,string>::iterator i=cc->params.begin();i!=cc->params.end();i++) {
        if (strupper(i->second)!="ON") {
            continue;
        }
        string c=i->first;
        if (c.substr(0,3)!="cid") {
            continue;
        }
        unsigned int msgid=atoi(c.substr(3,c.size()-3));
        delete_message(__UU,cc->user_id,msgid);
    }
    unsigned char sort;
    bool sort_desc;

    {
        PGLR(user_set,u,__U.us);
        sort=u->notes_sort;
        sort_desc=u->notes_sort_desc;
    }

    {
        __NOTE_LOCKW(u_id);
        u->resort(sort,sort_desc);
    }
}
static void mk_sort(const PTR_getter<chat_user> &__UU, const string &srt)
{
    user_pair __U(__UU);

    DB_id u_id=user$id(__U);
    {
        PGLW(user_set,u,__U.us);
        unsigned char notes_sort;
        unsigned char last_sort=u->notes_sort;
        if (srt=="from_nick") notes_sort=u_notes::sort_from;
        else if (srt=="to_nick") notes_sort=u_notes::sort_to;
        else if (srt=="subj") notes_sort=u_notes::sort_subj;
        else if (srt=="size") notes_sort=u_notes::sort_size;
        else notes_sort=u_notes::sort_date;
        if (u->notes_sort!=notes_sort)
        {
            u->notes_sort=notes_sort;
            send_update_g3(user_set$notes_sort,u_id,u->notes_sort);
        }
        if (u->notes_sort==last_sort)
        {
            if (u->notes_sort_desc)u->notes_sort_desc=false;
            else u->notes_sort_desc=true;
            send_update_g3(user_set$notes_sort_desc,u_id,u->notes_sort_desc);
        }
    }
    unsigned char sort;
    bool sort_desc;

    {
        PGLR(user_set,u,__U.us);
        sort=u->notes_sort;
        sort_desc=u->notes_sort_desc;
    }

    {
        __NOTE_LOCKW(u_id);
        u->resort(sort,sort_desc);
    }
}
static void url_notes_index(const PTR_getter<chat_user>&__UU,cs_conn_data* cc)
{
    if (!__UU || cc->user_unregistered) return;
    user_pair __U(__UU);

    DB_id u_id=user$id(__U);
    check_notes_config(u_id);
    unsigned int msg_per_page=20;
    {

        PGLR(user_set,u,__U.us);
        msg_per_page=u->notes_msg_per_page;
    }
    map<string,hstring> m;


    unsigned int folder=0;
    if (cc->params["f"]!="") folder=atoi(cc->params["f"]);
    if (folder) {
        if (cc->params.count("sort")) {
            string srt=cc->params["sort"];
            mk_sort(__UU,srt);
        }
        if (cc->params["cmd"]=="del") {
            mk_del(__UU,cc, folder);
        }
        if (cc->params["cmd"]=="move") {
            mk_move(__UU,cc, folder);
        }
        retr_result res=retrive_folders(cc,folder,__UU);
        int start=atoi(cc->params["l"]);
        int prev=start-msg_per_page;
        int next=start+msg_per_page;

        if (prev>=0) {
            m["~prev~"]="href=\"/notes?f="+itostring(folder)+"&l="+itostring(prev)+"\"";
        } else {
            m["~prev~"]="";
        }
        if (next<=res.cnt_in_current_folder) {
            m["~next~"]="href=\"/notes?f="+itostring(folder)+"&l="+itostring(next)+"\"";
        } else {
            m["~next~"]="";
        }

        m["~foldername~"]=res.current_folder;
        m["~folder~"]=itostring(folder);
        m["~allcnt~"]=itostring(res.cnt_in_current_folder);
        m["~start~"]=itostring(start+1);
        m["~folders~"]=res.all_folders;
        m["~move_to_folder~"]=make_folders_select(res.vec_folders,"move_to",0);
        if (start+msg_per_page>res.cnt_in_current_folder) {
            m["~end~"]=itostring(res.cnt_in_current_folder);
        } else {
            m["~end~"]=itostring(start+msg_per_page);
        }
        hstring n;
        {
            __NOTE_LOCK(u_id);
            if (!u->map_folders.count(folder)) throw cError("--- Error: cannot find folder ");
            {
                {
                    map<unsigned int,__note_folder> ::const_iterator  f=u->map_folders.find(folder);
                    if (f==u->map_folders.end()) throw cError("--- Error: cannot find folder ");

                    for (unsigned j=start;j<f->second.vec_msgs.size()&& j<start+msg_per_page;j++)
                    {
                        if (!u->map_msgs.count(f->second.vec_msgs[j])) {
                            throw cError("if(!un->map_msgs.count(f.msgs[j]))");
                        }
                        map<unsigned int,__note_head> ::const_iterator h=u->map_msgs.find(f->second.vec_msgs[j]);
                        map<string,hstring> z;
                        int status=h->second.nfh.status;
                        z["~filename~"]=h->second.nfh.attachment_filename;
                        z["~filepath~"]="/attachs/"+itostring(cc->user_id.container)+"/"+itostring(folder)+"/"+itostring(h->first)+"/"+h->second.nfh.attachment_filename;
                        if (h->second.nfh.has_attachment) {	//attachment
                            z["~attach~"]="";
                            z["~eattach~"]="";
                        } else {
                            z["~attach~"]="<!--";
                            z["~eattach~"]="-->";
                        }
                        if (h->second.nfh.important) {	//important note
                            z["~flag~"]="";
                            z["~eflag~"]="";
                        } else {
                            z["~flag~"]="<!--";
                            z["~eflag~"]="-->";
                        }
                        z["~fnid~"]=itostring(h->second.nfh.from_uid)+"."+itostring(h->second.nfh.from_nick_id);
                        z["~tnid~"]=itostring(h->second.nfh.to_uid)+"."+itostring(h->second.nfh.to_nick_id);

                        z["~fromnick~"]=h->second.nfh.from_nick;
                        z["~tonick~"]=h->second.nfh.to_nick;
                        z["~date~"]=datetime2rus_short(h->second.nfh.send_date);
                        z["~size~"]=number2text(h->second.nfh.content_length+h->second.nfh.attachment_content_length);
                        z["~href~"]="/notes/read?id="+itostring(h->first)+"&f="+itostring(folder);
                        z["~id~"]=itostring(h->first);
                        string subj=h->second.nfh.subject;
                        if (subj.size()>30) {
                            subj=subj.substr(0,30)+"...";
                        }
                        z["~subj~"]=subj;
                        if (h->second.nfh.unread && h->second.nfh.from_uid && h->second.nfh.from_uid!=cc->user_id.container) {
                            n+=make_pair(z,"notes/row_unread");
                        } else {
                            if (status==__note_head::STATUS_UNREAD_SENT && h->second.nfh.from_uid && h->second.nfh.from_uid==cc->user_id.container ) n+=make_pair(z,"notes/row_unread_sent");
                            else if (status==__note_head::STATUS_READ_ANSWERED && h->second.nfh.from_uid && h->second.nfh.from_uid!=cc->user_id.container) n+=make_pair(z,"notes/row_read_answered");
                            else if (status==__note_head::STATUS_READ) n+=make_pair(z,"notes/row_read");
                            else n+=make_pair(z,"notes/row_read");
                        }

                    }

                }
            }
        }
        if (!n.hstr_size()) {
            map<string,hstring> K;
            n=make_pair(K,"notes/no_messages");
        }
        m["~notes~"]=n;
        cc->html_out+=make_pair(m,"notes/folder");
        return;
    }

    //notes statistic page

    retr_result res=retrive_folders(cc,folder,__UU);
    int f_in=0;
    unsigned int sz=0;
    {
        __NOTE_LOCK(u_id);
        for (map<unsigned int,__note_head> ::const_iterator i=u->map_msgs.begin();i!=u->map_msgs.end();i++)
        {
            if (i->second.nfh.has_attachment)f_in++;
            {
                sz+=i->second.nfh.content_length+i->second.nfh.attachment_content_length;
            }
        }

    }
    m["~folders~"]=res.all_folders;
    m["~allnotes~"]=itostring(res.total_count);
    m["~files~"]=itostring(f_in);
    m["~notessize~"]=number2text(sz);

    cc->html_out+=make_pair(m,"notes/notes");
}

void url_notes(const PTR_getter<chat_user> &__U,cs_conn_data* cc)
{
    if (!__U || cc->user_unregistered) {
        cc->html_out=cc->redirect();
        return;
    }
    if (cc->vurl.size()) {
        if (*cc->vurl.begin()=="frames") {
            cc->vurl.erase(cc->vurl.begin());
            url_notes_frames(__U,cc);
            return;
        }
        if (*cc->vurl.begin()=="settings") {
            cc->vurl.erase(cc->vurl.begin());
            url_notes_settings(__U,cc);
            return;
        }
        if (*cc->vurl.begin()=="read") {
            cc->vurl.erase(cc->vurl.begin());
            url_notes_read(__U,cc);
            return;
        }
        if (*cc->vurl.begin()=="write") {
            cc->vurl.erase(cc->vurl.begin());
            url_notes_write(__U,cc);
            return;
        }
        if (*cc->vurl.begin()=="send") {
            cc->vurl.erase(cc->vurl.begin());
            url_notes_send(__U,cc);
            return;
        }
        if (*cc->vurl.begin()=="sent") {
            cc->vurl.erase(cc->vurl.begin());
            url_notes_sent(__U,cc);
            return;
        }
    }
    url_notes_index(__U,cc);
}



static void url_notes_send(const PTR_getter<chat_user> &__UU,cs_conn_data* cc)
{
    if (!__UU || cc->user_unregistered) return;
    user_pair __U(__UU);

    unsigned char sort;
    bool sort_desc;
    {
        PGLR(user_set,u,__U.us);
        sort=u->notes_sort;
        sort_desc=u->notes_sort_desc;
    }
    DB_id u_id=user$id(__U);
    bool save_copy;
    unsigned int notes_sent_folder;
    {
        {
            __NOTE_LOCK(u_id);


            unsigned int sent_f;
            for (map<unsigned int,__note_folder>::const_iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
            {
                if (i->second.filter_out.count(0)) sent_f=i->first;
            }
            notes_sent_folder=sent_f;

        }
        {
            PGLR(user_set,u,__U.us);
            save_copy=u->notes_save_copy;
        }
    }
    try {
        unsigned int nick=atoi(cc->params["fromnick"]);
        bool sys=strupper(cc->params["system"])=="ON";
        unsigned int ulvl=user$level(__U);

        user_nick from_nick=GET_NICK(__U,nick);

        if (ulvl/sub_levels!=am_sadmin) {
            sys=false;
        }
        string to_nick=remove_spaces(cc->params["tonick"]);
        DB_id to_uid;
        unsigned int  to_nick_id;
        {
            vector<string> v=get_id_uid_nick_by_nick(to_nick);
            if (!v.size()) {
                map<string,string> q;
                q["~nick~"]=to_nick;
                cc->html_out+=RVfiles(q,"notes/msg_nick_not_exists");
                return;
            }

            if (v.size()!=3) {
                throw cError("select failed. size different.");
            }
            to_nick_id=atoi(v[0]);
            to_uid.container=atoi(v[1]);

            if (cc->user_id==to_uid && !sys) {

                cc->html_out+=RVfiles("notes/msg_cantsendyourself");
                return;
            }
            to_nick=v[2];
        }
        check_notes_config(to_uid);
        check_notes_config(u_id);
        {
            PGLR(ignore_vec,z,ignore_vecs.find_by_id(to_uid))

            if (z->ignore.count(cc->user_id))
            {
                cc->html_out+=RVfiles("notes/msg_cantsendnote");
                return;
            }
        }

        if (sys) {
            DB_id ZZ00;
            from_nick=user_nick(_MSG("system"),0,ZZ00,false,0);
        }
        string subj=cc->params["subj"];
        string msg=cc->params["msg"];
        bool important=strupper(cc->params["important"])=="ON";
        bool attach=false;
        if (subj.size()>64) subj=subj.substr(0,64);
        if (remove_spaces(subj)=="") subj=_MSG("withouttheme");
        if (msg.size()>65535) {
            msg=msg.substr(0,65535);
        }

        if (!(user$privileges(__U)&u_allow_tags)) {
            subj=remove_tags(subj);
            msg=remove_tags(msg);
        }
        msg=str_replace("\n","<br>",msg);
        msg=replace_links(msg);

        int msgsize=subj.size()+msg.size()+cc->params["attach"].size();
        bool OK=true;
        if (save_copy && !sys)
        {
            if (!can_write_diskspace(__U, msgsize))
            {
                OK=false;
                map<string,string>q;
                q["~nick~"]=from_nick.name;
                cc->html_out+=RVfiles(q,"notes/msg_nofreespace");
                return;
            }
        }

        // select folders
        unsigned int from_folder=0,to_folder=0;
        unsigned int from_folder_0=0,to_folder_0=0;
        {
            __NOTE_LOCK(u_id);
            for (map<unsigned int,__note_folder>::const_iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
            {
                if (i->second.filter_out.count(to_uid.container)) from_folder=i->first;
                if (i->second.filter_out.count(0)) from_folder_0=i->first;
            }
        }
        if (from_folder_0==0) throw cError("if(from_folder_0==0)");
        if (from_folder==0) from_folder=from_folder_0;
        {
            __NOTE_LOCK(to_uid);
            for (map<unsigned int,__note_folder>::const_iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
            {
                if (i->second.filter_in.count(u_id.container)) to_folder=i->first;
                if (i->second.filter_in.count(0)) to_folder_0=i->first;
            }
        }
        if (to_folder_0==0) throw cError("if(to_folder_0==0)");
        if (to_folder==0) to_folder=to_folder_0;
        bool has_attachment=false;
        string attachment_filename;
        string attachment_body;
        {
            if (cc->params["attach"].size()) {
                has_attachment=true;
                string file_name=cc->params["attach_FILENAME"];
                vector<string> z=splitTOK("\\:/",file_name.c_str());
                if (z.size()!=0) {

                    attachment_filename=z[z.size()-1];
                }
                else
                {
                    throw cError("attchment size if(z.size()!=0){");
                }
                attachment_body=cc->params["attach"];
            }

        }
        unsigned int from_msg_id, to_msg_id;
        note_file_head h;
        h.from_nick=from_nick.name;
        h.to_nick=to_nick;
        h.subject=subj;
        h.from_nick_id=from_nick.id;
        h.to_nick_id=to_nick_id;
        h.from_uid=cc->user_id.container;
        h.to_uid=to_uid.container;
        h.unread=true;
        h.important=important;
        h.system=sys;
        h.content_length=msg.size();
        h.send_date=time(NULL);
        h.status=__note_head::STATUS_UNREAD_SENT;
        h.has_attachment=has_attachment;
        if (has_attachment)
        {
            h.attachment_filename=attachment_filename;
            h.attachment_content_length=cc->params["attach"].size();
        }

        unsigned int to_noteid=1;
        {
            __NOTE_LOCKW(to_uid);
        }
        {
            __note_head hh;
            __NOTE_LOCKW(to_uid);
            if (u->map_msgs.size())
            {
                to_noteid=u->map_msgs.rbegin()->first+1;
            }
            hh.id=to_noteid;
            hh.nfh=h;

            if (!u->map_folders.count(to_folder)) throw cError("!u->map_folders.count(to_folder)");
            u->map_msgs[to_noteid]=hh;
            u->map_folders[to_folder].vec_msgs.push_back(to_noteid);
            u->resort(sort,sort_desc);

            out_oscar_buffer o;
            o<<to_uid<<to_folder<<hh;
            send_update_g2(note$set_head,o);

        }
        {
            PGLW(note_text,n,note_texts.find_by_id(itostring(to_uid.container)+"."+itostring(to_noteid)));
            n->body=msg;
        }
        {
            out_oscar_buffer o;
            o<<to_uid<<to_noteid<<(string)msg;
            send_update_g2_cs_only(note$set_msg,o);
        }


        int from_noteid=1;
        if (!sys && save_copy) {
            __NOTE_LOCKW(u_id);
            if (u->map_msgs.size())
            {
                from_noteid=u->map_msgs.rbegin()->first+1;
            }

            __note_head hh;
            hh.id=from_noteid;
            hh.nfh=h;
            hh.nfh.unread=false;
            if (!u->map_folders.count(from_folder)) throw cError("!u->map_folders.count(from_folder)");
            u->map_msgs[from_noteid]=hh;
            u->map_folders[from_folder].vec_msgs.push_back(from_noteid);
            u->resort(sort,sort_desc);
            out_oscar_buffer o;
            o<<u_id<<from_folder<<hh;
            send_update_g2(note$set_head,o);

        }
        {
            PGLW(note_text,n,note_texts.find_by_id(itostring(u_id.container)+"."+itostring(from_noteid)));
            n->body=msg;
        }
        {
            out_oscar_buffer o;
            o<<u_id<<from_noteid<<msg;
            send_update_g2_cs_only(note$set_msg,o);
        }

        if (has_attachment)
        {
            out_oscar_buffer o;
            if (!sys && save_copy)
            {
                o<<2;
                o<<to_uid<<to_noteid;
                o<<u_id<<from_noteid;

            }
            else
            {
                o<<1;
                o<<to_uid<<to_noteid;
            }

            o<<h.attachment_filename;
            o<<cc->params["attach"];
#ifdef ACCEPT_NOTE_ATTACHMENTS
            send_update_g2_cs_only(note$set_attachment,o);
#endif
        }

        {
            vector<PTR_getter<chat_user> > uv=local_users.values();
            for (unsigned int i=0;i<uv.size();i++)
            {
                user_pair __Z(uv[i]);

                if (user$id(__Z)==to_uid && inchat$(__Z.cu))
                {
                    string im;
                    if (important) {
                        im=_MSG("important");
                    }
                    char _s[300];
                    snprintf(_s,sizeof(_s)-1,_MSG("noteincoming").c_str(),im.c_str(),from_nick.name.c_str());
                    send_syspriv_msg(__Z,_s);
                }
            }
        }
        cc->html_out+=RVfiles("notes/script_on_sent");
    } catch (cError e) {
        map<string,string> q;
        q["~error~"]=e.error_string;
        cc->html_out+=RVfiles(q,"notes/msg_internalerror");
        logErr2("--Error: url_notes_send - %s",e.error_string.c_str());
    }
}

void check_notes_config(const DB_id&  uid)
{

    unsigned int from_folder_0=0,to_folder_0=0;
    __NOTE_LOCKW(uid);
    for (map<unsigned int,__note_folder>::const_iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
    {
        if (i->second.filter_out.count(0)) from_folder_0=i->first;
        if (i->second.filter_in.count(0)) to_folder_0=i->first;
    }
    if (to_folder_0==0)
    {
//	logErr2("to_folder_0==0");
        string name=RVfiles("notes/names/incoming");
        int newfid=1;
        if (u->map_folders.size()) {
            newfid=u->map_folders.rbegin()->first+1;
        }


        __note_folder f;
        f.name=name;
        f.filter_in.insert(0);
        u->map_folders[newfid]=f;
        send_update_g4(note$folder_create,uid,newfid,name);
        send_update_g4(note$filter_in_insert,uid,newfid,0);
    }
    if (from_folder_0==0)
    {
//	logErr2("from_folder_0==0");

        int newfid=1;
        if (u->map_folders.size()) {
            newfid=u->map_folders.rbegin()->first+1;
        }

        string name=RVfiles("notes/names/outgoing");
        __note_folder f;
        f.name=name;
        f.filter_out.insert(0);
        u->map_folders[newfid]=f;

        send_update_g4(note$folder_create,uid,newfid,name);
        send_update_g4(note$filter_out_insert,uid,newfid,0);
    }
    set<unsigned int>m;
    for (map<unsigned int,__note_folder>::iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
    {
        for (vector<unsigned int>::const_iterator j=i->second.vec_msgs.begin();j!=i->second.vec_msgs.end();j++)
        {
            m.insert(*j);
            if (!u->map_msgs.count(*j)) logErr2("lost message %d in folder %d uid %d",*j,i->first,uid.container);
        }
    }
    vector<unsigned int> todel;
    for (map<unsigned int,__note_head> ::iterator i=u->map_msgs.begin();i!=u->map_msgs.end();i++)
    {
        if (!m.count(i->first))
        {
            logErr2("unreferenced msg %d uid %d",i->first,uid.container);
            todel.push_back(i->first);
        }
    }
    for (unsigned i=0;i<todel.size();i++)
    {
        u->map_msgs.erase(todel[i]);
        send_update_g3(note$remove,uid,todel[i]);
    }
}

PTR_getter<u_notes> get_notes_PTR_throw(const DB_id&  uid)
{
    PTR_getter<u_notes> __U(__notes.find_by_id(uid));
    if (!__U)throw cError("if(!__U)");
    return __U;
}
PTR_getter<u_notes> get_notes_PTR(const DB_id& uid)
{
    PTR_getter<u_notes> __U(__notes.find_by_id(uid));
    return __U;
}

void check_notes_config(const DB_id &uid);
retr_result retrive_folders(cs_conn_data *cc,unsigned int folder,const PTR_getter<chat_user> &__UU)
{
    user_pair __U(__UU);

    DB_id id;
    id=user$id(__U);
    check_notes_config(id);
    retr_result res;
    res.total_count=0;
    {
        __NOTE_LOCK(id);

        for (map<unsigned int,__note_folder>::const_iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
        {
            int sumunread=0;
            unsigned int fid=i->first;

            int cnt=i->second.vec_msgs.size();
            for (unsigned j=0;j<i->second.vec_msgs.size();j++)
            {
                if (u->map_msgs.count(i->second.vec_msgs[j]))
                {
                    map<unsigned int,__note_head> ::const_iterator h=u->map_msgs.find(i->second.vec_msgs[j]);
                    if (h->second.nfh.unread && h->second.nfh.from_uid!=id.container &&  h->second.nfh.from_uid) sumunread++;
                }
            }
            map<string,hstring> q;
            {
                q["~id~"]=itostring(fid);
                q["~name~"]=i->second.name;
                int newn=sumunread;
                if (newn) {
                    q["~new~"]="";
                    q["~enew~"]="";
                } else {
                    q["~new~"]="<!--";
                    q["~enew~"]="-->";
                }
                q["~newcnt~"]=itostring(newn);
                res.all_folders+=make_pair(q,"notes/folder_row");
                if (folder==i->first) {
                    res.current_folder=i->second.name;
                    res.cnt_in_current_folder=i->second.vec_msgs.size();
                }

                old_notes_folder ff;
                ff.name=i->second.name;
                ff.new_cnt=newn;
                ff.cnt=cnt;
                ff.id=fid;
                res.vec_folders.push_back(ff);
                res.total_count+=cnt;
            }

        }
    }
    return res;
}
void delete_message(const PTR_getter<chat_user> &__UU,const DB_id& /*uid*/,unsigned int msgid)
{
    user_pair __U(__UU);
    DB_id u_id=user$id(__U);
    {
        __NOTE_LOCK(u_id);
        if (!u->map_msgs.count(msgid)) {
            logErr2("---Error: ABSENT message");
            return;
        }
    }
    unsigned char sort;
    bool sort_desc;

    {
        PGLR(user_set,u,__U.us);
        sort=u->notes_sort;
        sort_desc=u->notes_sort_desc;
    }
    unsigned int fld=0;
    string attpn;
    {
        __NOTE_LOCKW(u_id);
        if (u->map_msgs[msgid].nfh.has_attachment)
        {
            attpn=attach_pn(u_id,msgid,u->map_msgs[msgid].nfh.attachment_filename);
        }

        for (map<unsigned int,__note_folder>::iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
        {
            for (vector<unsigned int>::iterator j=i->second.vec_msgs.begin();j!=i->second.vec_msgs.end();j++)
            {
                if (*j==msgid)
                {
                    i->second.vec_msgs.erase(j);
                    fld=i->first;
                    break;
                }
            }
        }
        u->resort(sort,sort_desc);
    }

    if (fld && msgid)
    {
        send_update_g3(note$remove,u_id,msgid);
    }


}
void move_message(const PTR_getter<chat_user> &__UU,unsigned int fold,unsigned int to_folder,unsigned int msgid,bool save_filter)
{
    user_pair __U(__UU);
    DB_id u_id=user$id(__U);

    {
        __NOTE_LOCKW(u_id);
        if (!u->map_msgs.count(msgid)) {
            logErr2("---Error: ABSENT message");
            return;
        }
        for (vector<unsigned int>::iterator i=u->map_folders[fold].vec_msgs.begin();i!=u->map_folders[fold].vec_msgs.end();i++)
        {
            if (*i==msgid)
            {
                u->map_folders[fold].vec_msgs.erase(i);
                break;
            }
        }
        out_oscar_buffer o;
        o<<u_id<<msgid<<fold<<to_folder;
        send_update_g2(note$move_message,o);

        if (save_filter)
        {
            __note_head &h=u->map_msgs[msgid];
            if (h.nfh.from_uid==u_id.container)
            {
                // filter_out;
                unsigned int touid=h.nfh.to_uid;
                if (touid)
                {
                    for (map<unsigned int,__note_folder>::iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
                    {
                        if (i->second.filter_out.count(touid)) {
                            send_update_g4(note$filter_out_delete,u_id,i->first,touid);
                            i->second.filter_out.erase(touid);
                        }
                    }
                    u->map_folders[to_folder].filter_out.insert(touid);
                    send_update_g4(note$filter_out_insert,u_id,to_folder,touid);
                }
            }
            if (h.nfh.to_uid==u_id.container)
            {
                // filter_in;
                unsigned int fromuid=h.nfh.from_uid;
                for (map<unsigned int,__note_folder>::iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
                {
                    if (i->second.filter_in.count(fromuid)) {
                        i->second.filter_in.erase(fromuid);
                        send_update_g4(note$filter_in_delete,u_id,i->first,fromuid);

                    }
                }
                u->map_folders[to_folder].filter_in.insert(fromuid);
                send_update_g4(note$filter_in_insert,u_id,to_folder,fromuid);
            }
        }
    }

}
void send_system_note(const DB_id &uid,const string &subj,const string& msg)
{
    string cnick;
    unsigned int cnickid;
    {
        PGLR(user_set,u,user_sets.find_by_id(uid));
        cnick=u->last_nick;
        cnickid=u->last_nick_id;
    }


    unsigned int to_folder=0;
    unsigned int to_folder_0=0;
    int nextmsgid=1;
    {
        __NOTE_LOCK(uid);
        for (map<unsigned int,__note_folder>::const_iterator i=u->map_folders.begin();i!=u->map_folders.end();i++)
        {
            if (i->second.filter_in.count(0)) to_folder_0=i->first;
        }
        if (u->map_msgs.size())
            nextmsgid=u->map_msgs.rbegin()->first+1;
    }
    if (to_folder_0==0) throw cError("if(to_folder_0==0)");
    if (to_folder==0) to_folder=to_folder_0;


    unsigned int from_msg_id, to_msg_id;
    note_file_head h;
    h.from_nick=_MSG("system");
    h.to_nick=cnick;
    h.subject=subj;
    h.from_nick_id=0;
    h.to_nick_id=cnickid;
    h.from_uid=chat_config2.system_note_uid.get();
    h.to_uid=uid.container;
    h.unread=true;
    h.important=true;
    h.system=true;
    h.content_length=msg.size();
    h.send_date=time(NULL);
    h.status=__note_head::STATUS_UNREAD_SENT;
    h.has_attachment=false;

    out_oscar_buffer o;
    __note_head hh;
    hh.id=nextmsgid;
    hh.nfh=h;
    o<<uid<<to_folder<<hh;
    send_update_g2(note$set_head,o);

    {
        out_oscar_buffer o;
        o<<uid<<nextmsgid<<msg;
        send_update_g2_cs_only(note$set_msg,o);
    }
}
void note_resort(const DB_id &uid)
{
    unsigned char sort;
    bool sort_desc;

    {
        PGLR(user_set,u,user_sets.find_by_id(uid));
        sort=u->notes_sort;
        sort_desc=u->notes_sort_desc;
    }
    {
        __NOTE_LOCKW(uid);
        u->resort(sort,sort_desc);
    }

}
void url_notes_attach(const PTR_getter<chat_user> &__U,cs_conn_data* cc)
{

    if (!__U || cc->user_unregistered) return;
    if (!cc->wc) throw cError("if(!cc->wc)");
    cc->wc->allow_build_response=false;
    vector<string> z=splitTOK("/",cc->url/*cc->params["URL"].c_str()*/);
    if (z.size()<5) {
        return;
    }
    DB_id uid;
    uid.container=atoi(z[1]);
    if (uid!=cc->user_id)
        return;
    unsigned int folder=atoi(z[2]);
    unsigned int msgid=atoi(z[3]);
    string ext = get_file_ext(z[4]);
    string attfn;
    {
        __NOTE_LOCK(uid);
        if (u->map_msgs.count(msgid))
            attfn=u->map_msgs.find(msgid)->second.nfh.attachment_filename;

    }
    string fn=attach_pn(uid,msgid,attfn);
    try {
        if (z[0]=="attachs") {
            if (send_other_from_disk_ext(cc->wc,fn,false,strlower(ext))==-1) {
                return;
            }
        } else {
            if (send_other_from_disk_ext(cc->wc,fn,false,strlower(ext))==-1) {
                return;
            }
        }
    } catch (...) {

    }
}
