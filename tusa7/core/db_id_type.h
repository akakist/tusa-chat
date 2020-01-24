#ifndef db_id_type__h
#define db_id_type__h
#include "DB_id.h"
class db_id_type
{
public:
    enum IDT {TUINT,TSTRING,TUNDEF};
    string id;
    IDT itype;
    db_id_type(unsigned int n);
    db_id_type(int n);
    db_id_type(unsigned long n);
    db_id_type(long n);
    db_id_type(short n);
    db_id_type(unsigned short n);
    db_id_type(const string &n);
    db_id_type(IDT t);
    db_id_type(const DB_id &n);
    int operator < (const db_id_type & n)const {
        return id<n.id;
    }
    int operator > (const db_id_type & n)const {
        return id>n.id;
    }
    unsigned int as_int() const;
    string as_string() const;
};

#endif
