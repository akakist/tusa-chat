#ifndef photo_323PROFILE__H___
#define photo_323PROFILE__H___
#include <map>
#include <hash_map>
#include <set>
#include <string>
#include "db_var.h"
#include "DB_id.h"
using namespace std;
struct __foto
{
	__foto(){
	//	CONTAINER(uid)=0;
	}
	string descr,orig_fn,ext;
	size_t size;
	unsigned int id;
//	DB_id uid;
	map<DB_id,int> rates;
	map<string,pair<string /*content type*/,string/*body*/> > pics;
};
class user_fotos: public db_row
{
	public:
	unsigned int id;
		const char* getclassname()const {return "user_fotos";}

	unsigned primary;
	map<unsigned int, __foto> fotos;
	unsigned int index2id(unsigned int index) const;
	size_t getsize() const;
	void reload$();
	int load_from_db(const string & table_name) const;
	void on_id_not_exists(const string &tbname, unsigned int _id);



	void pack(out_oscar_buffer &b) const;
	void unpack(oscar_buffer &b);
	user_fotos():primary(0),id(0){}
};

extern db_map<unsigned int,user_fotos> users_fotos;
//string foto_pn(/*const DB_id& uid,*/ unsigned int fid,const string &ext);

out_oscar_buffer & operator<<(out_oscar_buffer&b, const __foto &n);
oscar_buffer & operator>>(oscar_buffer&b, __foto &n);

#endif
