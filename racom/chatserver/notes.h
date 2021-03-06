#ifndef NOTES_H__
#define NOTES_H__
#include <string>
#include <set>
#include "html_out.h"
struct old_notes_folder
{
    string name;
    unsigned int id;
    unsigned int new_cnt;
    unsigned int cnt;
    old_notes_folder() {}
};

struct retr_result
{
    hstring all_folders;
    hstring current_folder;
    unsigned int cnt_in_current_folder;
    unsigned int total_count;
    vector<old_notes_folder> vec_folders;
    retr_result() {}
};
class app_connection;
class cs_conn_data;
retr_result retrive_folders(cs_conn_data *cc,unsigned int folder,const PTR_getter<chat_user> &__UU);
struct note_file_head {
    string subject;
    string  from_nick,to_nick;
    unsigned int to_nick_id,from_nick_id;
    unsigned int to_uid,from_uid;
    bool unread,important,system;
    int content_length;
    time_t send_date;
    unsigned char status;
    bool has_attachment;
    string attachment_filename;
    int attachment_content_length;
    string as_header();
    unsigned int notify_read;

    note_file_head():to_nick_id(0),from_nick_id(0),to_uid(),from_uid(0),unread(true),important(false),system(false),content_length(0),
            send_date(time(NULL)),status(0),has_attachment(false),attachment_content_length(0),notify_read(0) {}

};

oscar_buffer& operator>>(oscar_buffer & b, note_file_head   &c);
out_oscar_buffer& operator<<(out_oscar_buffer & b, const note_file_head & c);

struct __note_head
{
    enum {
        STATUS_UNREAD_SENT=1,
        STATUS_READ_ANSWERED=3,
        STATUS_READ=0
    };
    unsigned int id;
    note_file_head nfh;
    __note_head():id(0) {}
};

out_oscar_buffer& operator<<(out_oscar_buffer & b, const __note_head & c);
oscar_buffer& operator>>(oscar_buffer & b, __note_head   &c);

struct __note_folder
{
    string name;
    set<unsigned int> filter_in;
    set<unsigned int> filter_out;
    vector<unsigned int> vec_msgs;
};

oscar_buffer& operator>>(oscar_buffer & b, __note_folder   &c);
out_oscar_buffer& operator<<(out_oscar_buffer & b, const __note_folder & c);

struct u_notes : public db_row
{
    map<unsigned int,__note_folder> map_folders;
    map<unsigned int,__note_head> map_msgs;

    enum
    {
        sort_date=1,sort_size=2,sort_from=3,sort_to=4,sort_subj=5
    };
    void resort(unsigned char sort, bool sort_desc);
    bool find_msg_by_id(unsigned int id, __note_head &h) const; // 0 failure
    u_notes();
    string update_to_db(const string& table_name) const;
    int load_from_db(const string & table_name) const;

    void pack(out_oscar_buffer &b) const;
    void unpack(oscar_buffer &b);
};


oscar_buffer& operator>>(oscar_buffer & b, u_notes   &c);
out_oscar_buffer& operator<<(out_oscar_buffer & b, const u_notes & c);


PTR_getter<u_notes> get_notes_PTR(const DB_id& uid);
PTR_getter<u_notes> get_notes_PTR_throw(const DB_id& uid);

void reload_notes(const PTR_getter<u_notes> &__U);
#define __NOTE_LOCK(uid)  PGLR(u_notes, u,get_notes_PTR_throw(uid));
#define __NOTE_LOCKW(uid)  PGLW(u_notes, u,get_notes_PTR_throw(uid));

struct note_text : public db_row
{
    string body;
    int load_from_db(const string & table_name);
    void pack(out_oscar_buffer &b) const {
        b<<body;
    }
    void unpack(oscar_buffer &b) {
        b>>body;
    }

};


extern db_map<u_notes> __notes;
extern db_map<note_text> note_texts;


#endif
