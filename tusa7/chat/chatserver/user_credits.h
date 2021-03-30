#ifndef USERCREDITS_H__
#define USERCREDITS_H__
#include "db_var.h"
#include <string>
#include "M_DEQUE.h"

class user_credit:public db_row
{
public:
    db_var<double> summa;
    db_var<time_t> last_access;
    string update_to_db(const string& table_name) const;
    int load_from_db(const string& table_name) const;
    user_credit();
    ~user_credit() {}
    void pack(out_oscar_buffer &b) const;
    void unpack(oscar_buffer &b);
};

struct credit_transaction
{
    DB_id from_user_id,to_user_id;
    double summa;
    string operation_code;
    time_t t;
    credit_transaction() {}
    ~credit_transaction() {}
};
extern M_DEQUE<credit_transaction> credit_transactions;
void dump_credits_log();


extern db_map<user_credit> user_credits;
bool buy_thing(const DB_id& from_uid,const DB_id&  to_uid,double price, const string &opcode); // true if success
double credit_reminder(const DB_id& uid);
string update_to_db(const PTR_getter<user_credit>&__P,const string &tblname);

#endif
