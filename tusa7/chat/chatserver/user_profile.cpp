#include "stdafx.h"
#include <string>
using namespace std;
#include "user.h"
#include "utils.h"
#include "db_var.h"
#include "user_profile.h"
#include "cm_container.h"
#include "DR_types.h"
user_profile::user_profile() {
    b_mon=0;
    reg_date=time(NULL);
    level=0;
    vote_balls=0;
    db_privileges=0;
    gender=0;
}
user_profile::~user_profile() {}

string update_to_db(const PTR_getter< user_profile> &__U,const string& table_name)
{
    return "";
}

#ifdef __CLAN
int user_profile::load_from_db(const string& table_name)  // 0 - no error
{
    DB_id id;
    id.container=get_db_row_id().as_int();
    //    logErr2("user_profile::load_from_db %d",id.container);
    string r=clan_data_request(DR_user_profile,id);
    oscar_buffer bb(r.data(),r.size());
    unpack(bb);
    return 0;

}
#else
int user_profile::load_from_db(const string& table_name)  // 0 - no error
{
    unsigned int uid=get_db_row_id().as_int();
    if (uid==0) {
        logErr2("uid==0 || uid>UNREG_BASE (%d) %s",uid,"");
        throw cError("if(get_db_row_id().as_int()==0) || uid>UNREG_BASE");
    }


    st_dbh d;

    vector<vector<string> > v;


    v=d.dbh->execQ((QUERY)"select id,name,pic,disable_invite,uniq from user_status where uid=?"<<get_db_row_id().as_int());

    status.clear();
    for (unsigned i=0;i<v.size();i++)
    {
        if (v[i].size()==5)
        {
            user_status s;
            s.id=atoi(v[i][0]);
            s.name=v[i][1];
            s.pic=atoi(v[i][2]);
            s.disable_invite=atoi(v[i][3]);
            s.uniq=atoi(v[i][4]);
            status[s.id]=s;
        }
    }
    for (unsigned int i=0;i<msgs_defstatus.size();i++) {
        user_status c;
        c.id=i;
        c.name=msgs_defstatus.get(gender,i);
        c.pic=i-2;
        c.disable_invite=false;
        status[i]=c;
    }
    status[0].pic=1000;
    status[1].pic=998;
    status[2].pic=999;
    status[7].disable_invite=true;


    {
        vector<string> v=d.dbh->select_1_rowQ((QUERY)
                                              "select icq,city,info,homepage,tel,b_day,b_mon,b_year,fname,lname,email,UNIX_TIMESTAMP(reg_date),"
                                              "level,login,pass,vote_balls,db_privileges,gender "
                                              "from ? "
                                              "where refid=?"<<table_name<<get_db_row_id().as_int());
        if (v.size()!=18) {
            return -1;
        }
        icq=v[0];
        city=v[1];
        info=v[2];
        homepage=v[3];
        tel=v[4];
        b_day=v[5];
        b_mon=atoi(v[6]);
        b_year=v[7];
        fname=v[8];
        lname=v[9];
        email=v[10];
        reg_date=atoi(v[11]);
        level=atoi(v[12]);
        login=v[13];
        pass=v[14];
        vote_balls=atoi(v[15]);
        db_privileges=atoi(v[16]);
        set_gender(atoi(v[17]));
    }



    return 0;
}
#endif
unsigned char user_profile::get_gender()const {
    return gender;
}
void user_profile::set_gender(unsigned char g)
{
    gender=g;
    for (unsigned int i=0;i<msgs_defstatus.size();i++) {
        user_status c;
        c.id=i;
        c.name=msgs_defstatus.get(gender,i);
        c.pic=i-2;
        c.disable_invite=false;
        status[i]=c;
    }
    status[0].pic=1000;
    status[1].pic=998;
    status[2].pic=999;
    status[7].disable_invite=true;


}
void user_profile::pack(out_oscar_buffer &b) const
{
    b<<icq<<
    city<<
    info<<
    homepage<<
    tel<<
    b_day<<
    b_mon<<
    b_year<<
    fname<<
    lname<<
    email<<
    reg_date<<
    level<<
    login<<
    pass<<
    vote_balls<<
    db_privileges<<
    status<<
    gender;

}
void user_profile::unpack(oscar_buffer &b)
{
    b>>icq>>
    city>>
    info>>
    homepage>>
    tel>>
    b_day>>
    b_mon>>
    b_year>>
    fname>>
    lname>>
    email>>
    reg_date>>
    level>>
    login>>
    pass>>
    vote_balls>>
    db_privileges>>
    status>>
    gender;

}
