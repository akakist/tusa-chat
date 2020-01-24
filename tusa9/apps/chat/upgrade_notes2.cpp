#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include <deque>
#include "copy_file.h"
#include <sys/stat.h>
deque<string>nn;
string homedir(unsigned int uid)
{
	char pn[300];
	string sid=itostring(uid);
	if(uid<100)
	{
		snprintf(pn,sizeof(pn)-1,"%s/0/%02d","/var/chat/homes",uid);
	}
	else if(uid<10000)
	{
		snprintf(pn,sizeof(pn)-1,"%s/1/%02d/%02d","/var/chat/homes",uid/100,uid%100);
	}
	else if(uid<1000000)
	{
		int u1=uid/10000;
		int u2=(uid-(u1*10000))/100;
		int u3=uid%100;
		snprintf(pn,sizeof(pn)-1,"%s/2/%02d/%02d/%02d","/var/chat/homes",u1,u2,u3);
	}
	return pn;

}
string notes_homedir(unsigned int uid)
{
	return homedir(uid)+"/.notes";
}

void process_notes(unsigned int uid, cMYSQL *dbh, map<string,string> &m)
{
    map<unsigned int,set<unsigned int> > filters_in;
    map<unsigned int,set<unsigned int> > filters_out;
    if(atoi(dbh->select_1Q((QUERY)"select count(*) from notes where uid=?"<<uid))==0) return;

    {
        vector<vector<string> > vv=dbh->execQ((QUERY)"select fid, to_folder from notes_filters where uid=?"<<uid);
        for(unsigned j=0;j<vv.size();j++)
        {
            if(vv[j].size()==2)
            {
                unsigned int fromnick=atoi(vv[j][0]);
                unsigned int to_folder=atoi(vv[j][1]);
                filters_in[to_folder].insert(fromnick);
            }
        }
        vector<string>		vsf=dbh->select_1_rowQ((QUERY)"select notes_sent_folder from user_settings where uid=?"<<uid);
        if(vsf.size())
        {
            unsigned int sent_f=atoi(vsf[0]);
            filters_out[sent_f].insert(0);
        }
    }
    vector<vector< string> > vv=dbh->execQ((QUERY)"select id,name,cant_remove from notes_folders where uid=?"<<uid);
    vector<string> folders;
    for(unsigned j=0;j<vv.size();j++)
    {
        if(vv[j].size()==3)
        {
            unsigned int fid=atoi(vv[j][0]);
            folders.push_back(itostring(fid));
            vector<vector<string> > vvm=dbh->execQ((QUERY)	"select
                                                   id,
                                                   from_nick,
                                                   from_nick_id,
                                                   to_nick,
                                                   to_nick_id,
                                                   subj,
                                                   UNIX_TIMESTAMP(sent_date),
                                                   important,
                                                   status,
                                                   unread,
                                                   attach,
                                                   file_name,
                                                   file_path,
                                                   msg,
                                                   parent
                                                   from notes
                                                   where folder=?"<<fid);
            vector<string>		 mids;
            for(unsigned im=0;im<vvm.size();im++)
            {
                if(vvm[im].size()==15)
                {
                    if(!vvm[im][13].size()) continue;
                    unsigned int msgid=atoi(vvm[im][0]);

                    mids.push_back(itostring(msgid));
                    string pn=notes_homedir(uid)+"/"+itostring(msgid)+".msg";
                    check_path_wfn(pn);
                    st_FILE f(pn,"wb");
                    f.write((string)"From: "+vvm[im][1]+"\n");
                    f.write((string)"From-ID: "+vvm[im][2]+"\n");
                    f.write((string)"To: "+vvm[im][3]+"\n");
                    f.write((string)"To-ID: "+vvm[im][4]+"\n");
                    f.write((string)"Subject: "+vvm[im][5]+"\n");
                    f.write((string)"Send-Date: "+date2mysql(atoi(vvm[im][6]))+"\n");
                    if(vvm[im][7]=="1")
                        f.write((string)"Important: "+vvm[im][7]+"\n");
                    f.write((string)"Status: "+vvm[im][8]+"\n");
                    if(vvm[im][9]=="1")
                        f.write((string)"Unread: "+vvm[im][9]+"\n");
                    if(vvm[im][10]=="1")
                    {
                        string pold=(string)"/var/chat/notes/"+vvm[im][12];
                        string pnew=notes_homedir(uid)+"/"+itostring(msgid)+".att";
                        check_path_wfn(pnew);
                        check_path_wfn(pold);
							
                        if(link(pold.c_str(),pnew.c_str()))
                        {
                            printf("link failed %s -> %s\n",pold.c_str(),pnew.c_str());

                        }
                        else
                        {
                            f.write((string)"Attachment: "+vvm[im][11]+"\n");
                        }
                    }
                    f.write((string)"Content-Length: "+itostring(vvm[im][13].size())+"\n");
                    if(atoi(vvm[im][14])!=0)
                    {
                        vector<string> v=dbh->select_1_rowQ((QUERY)"select uid,folder from notes where id=?"<<vvm[im][14]);
                        if(v.size()==2)
                        {
                            f.write((string)"Parent: "+v[0]+"."+v[1]+"."+vvm[im][14]+"\n");
                        }
                    }
                    f.write((string)"\n");
                    f.write(vvm[im][13]);

                }
            }

//            string pn=notes_homedir(uid)+"/"+itostring(fid)+"/"+".profile";
//            check_path_wfn(pn);
            {
  //              st_FILE f(pn,"wb");
  				m["note_folder_"+itostring(fid)+"_name"]=vv[j][1];
				if(mids.size())
	  				m["note_folder_"+itostring(fid)+"_msgs"]=join(",",mids);
//                f.write((string)"name="+vv[j][1].c_str()+"\n");
//              f.write((string)"msgs="+join(",",mids)+"\n");
				
                unsigned int fid=atoi(vv[j][0]);
                {
                    vector<string> fv;
                    for(set<unsigned int>::iterator j=filters_in[fid].begin();j!=filters_in[fid].end();j++)
                    {
                        fv.push_back(itostring(*j));
                    }
                    if(fv.size())
					{
		  				m["note_folder_"+itostring(fid)+"_filter_in"]=join(",",fv);
//                        f.write((string)"filter_in="+join(",",fv)+"\n");
					}	
                }
                {
                    vector<string> fv;
                    for(set<unsigned int>::iterator j=filters_out[fid].begin();j!=filters_out[fid].end();j++)
                    {
                        fv.push_back(itostring(*j));
                    }
                    if(fv.size())
					{
		  				m["note_folder_"+itostring(fid)+"_filter_out"]=join(",",fv);
//                        f.write((string)"filter_out="+join(",",fv)+"\n");
					}	
                }

            }
        }
    }
    {
        vector<string>v=dbh->select_1_rowQ((QUERY)"select notes_sent_folder,notes_msg_per_page,notes_save_copy from user_settings where uid=?"<<uid);
//        string pn=notes_homedir(uid)+"/"+".profile";
//        check_path_wfn(pn);
//        st_FILE f(pn,"wb");
		m["note_folders"]=join(",",folders);
//        f.write((string)"folders="+join(",",folders)+"\n");
        if(v.size()==3)
        {
            //                    f.write((string)"sent_folder="+v[0]+"\n");
			m["note_msg_per_page"]=v[1];
			m["note_save_copy"]=v[2];
//            f.write((string)"msg_per_page="+v[1]+"\n");
//            f.write((string)"save_copy="+v[2]+"\n");
        }
    }

}
void process_profiler(unsigned int uid, cMYSQL *dbh, map<string,string> &m)
{
    vector<string> ign=dbh->select_1_columnQ((QUERY)"select iid from ignores where uid=?"<<uid);
    if(ign.size())
    {
//        string pn=homedir(uid)+"/"+".profile";
//        check_path_wfn(pn);
//        st_FILE f(pn,"wb");
		m["ignores"]=join(",",ign);
//        f.write("ignores="+join(",",ign)+"\n");
    }
    vector<string> lev=dbh->select_1_rowQ((QUERY)"select accessmode from users where id=?"<<uid);
    if(lev.size())
		m["level"]=lev[0];
//       f.write("level="+lev[0]+"\n");
}
void process_fotos(unsigned int uid, cMYSQL *dbh, map<string,string> &m)
{
	vector<vector<string> > v=dbh->execQ((QUERY)"select filename,orig_filename,descr,sx,sy,size from photos where uid=?"<<uid);
//	map<string,string> m;
	vector<string> vf;
	struct stat st;
	for(unsigned i=0;i<v.size();i++)
	{
		if(v[i].size()==6)
		{
			string old_fn="/var/chat/photos/"+v[i][0];
			if(stat(old_fn.c_str(),&st)) continue;
			string new_fn=homedir(uid)+"/.fotos/"+itostring(i)+".ph";
            check_path_wfn(new_fn);
			if(link(old_fn.c_str(),new_fn.c_str()))
			{
				printf("error link %s -> %s\n",old_fn.c_str(),new_fn.c_str());
				continue;
			}
			int sz;
			{
				struct stat st;
				if(stat(new_fn.c_str(),&st)){
					continue;
				}
				sz=st.st_size;
			}
			vector<string> vE=splitTOK(".",v[i][0]);
			if(vE.size())
			{
				string ext=strlower(vE[vE.size()-1]);
				m["ph_ext_"+itostring(i)]=ext;
			}
			else printf("!vE.size() %s",v[i][0].c_str());

			if(v[i][1].size())m["ph_orig_fn_"+itostring(i)]=v[i][1];
			if(v[i][2].size())m["ph_descr_"+itostring(i)]=v[i][2];
//			if(atoi(v[i][3]))m["ph_sx_"+itostring(i)]=v[i][3];
//			if(atoi(v[i][4]))m["ph_sy_"+itostring(i)]=v[i][4];
			if(sz) m["ph_size_"+itostring(i)]=itostring(st.st_size);
			vf.push_back(itostring(i));
		}
		else printf("v.size()==6\n");
	}
	if(vf.size())
		m["fotos"]=join(",",vf);
/*
	string out;
	for(map<string,string>::iterator i=m.begin();i!=m.end();i++)
	{
		out+=i->first+"="+i->second+"\n";
	}
	if(out.size())
	{
	string ppn=homedir(uid)+"/.fotos/.profile";
    check_path_wfn(ppn);
	st_FILE f(ppn,"wb");
	f.write(out);
	}*/
}

int main(int argc,char *argv[])
{
    try{
        MYSQL *_dbh=new MYSQL;
        mysql_init(_dbh);
        MYSQL *res=mysql_real_connect(_dbh,NULL,NULL,NULL,"chat",0,NULL,0);
        if(!res)
        {
            logErr("chat_sender: mysql_real_connect failed to %s","chat");
            exit(1);
        }
        cMYSQL *dbh=new cMYSQL(_dbh);
        dbh->connected=true;

        vector<string> v=dbh->select_1_column("select id from users order by id");

        printf("selected %d users\n",v.size());
        for(int i=0;i<v.size();i++){
            unsigned int uid=atoi(v[i]);
            map<string,string>m;
            process_notes(uid,dbh,m);
			printf("after process_notes(uid,dbh,m);\n");
            process_profiler(uid,dbh,m);
			printf("after process_profiler(uid,dbh,m);\n");
            process_fotos(uid,dbh,m);
			printf("after process_fotos(uid,dbh,m);\n");
            string out;
            for(map<string,string>::iterator j=m.begin();j!=m.end();j++)
            {
                out+=j->first+"="+j->second+"\n";
            }
            if(out.size())
            {
                string ppn=homedir(uid)+"/.profile";
                check_path_wfn(ppn);
                st_FILE f(ppn,"wb");
                f.write(out);
                printf("updated %d (%d) users of %d\n",i,atoi(v[i]),v.size());
            }
			{
				map<string,pair<string,string> >m;
				vector<vector< string > > v1=dbh->execQ((QUERY)"select nicks.uppernick,users.pass,nicks.uid from nicks,users where nicks.uid=users.id" );
				vector<vector< string > > v2=dbh->execQ((QUERY)"select UPPER(login),pass,id from users");
				for(unsigned i=0;i<v1.size();i++)
				{
					if(v1[i].size()==3)
					{
						m[v1[i][0]]=pair<string,string>(v1[i][1],v1[i][2]);
					}
				}
				for(unsigned i=0;i<v2.size();i++)
				{
					if(v2[i].size()==3)
					{
						m[v2[i][0]]=pair<string,string>(v2[i][1],v2[i][2]);
					}
				}
	            string out;
    	        for(map<string,pair<string,string > >::iterator j=m.begin();j!=m.end();j++)
        	    {
            	    out+=bin2hex(j->first,10)+"="+j->second.first+"."+j->second.second+"\n";
            	}
	            if(out.size())
    	        {
        	        string ppn="/.profile";
            	    check_path_wfn(ppn);
                	st_FILE f(ppn,"wb");
	                f.write(out);
        	    }
				exit(1);
			}
        }
    }catch(cError e){
        printf("Error: %s\n",e.error_string.c_str());
    }
    return 0;
}
