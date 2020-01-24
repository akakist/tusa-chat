#include "stdafx.h"
#include <signal.h>
#include <errno.h>

#include "str_lib.h"
#include "server_config.h"
#include "wrappers.h"
#include "st_stuff.h"
#include "file_set.h"
//#include "utils.h"

using namespace std;

__global_config global_config;
__global_config::__global_config():use_mem_files(UMF_DISK_ONLY)
{
}
void __global_config::load_config(const string& server_config, bool with_files_conf)
{
//logErr2("__global_config::load_config %s",server_config.c_str());
    map<string,string>	m=load_m_file(server_config);
    server_params.read(server_config);

    set_cfg_str(m,"var_dir", server_config,var_dir,"" SPLITTER "var" SPLITTER "chat");

//	set_cfg_str(m,"log_name", server_config,log_name,"./log");
#ifdef __WITH_FILES_CONF__
    if (with_files_conf)
    {
        files_conf.read(get_cfg_str(m,"files_config",server_config, "./conf/files.conf"));
        load_files();
    }
#endif
//    print_rest_cfg(m,server_config);

}
int load_1_file_from_disk(string & res, const string & fn);
static int load_1_file_from_mem(string & res, const string & fn)
{
//-1 err
    if (!global_config.files_dump.exists(fn)) {
        return -1;
    }
    else {
        res = global_config.files_dump.get(fn);
        return res.size();
    }
    return -1;

}
int load_1_file(string & res, const string & fn)//-1 err
{
    try {
        int umf=global_config.use_mem_files.get();

        if (umf==__global_config::UMF_MEMORY_ONLY)
        {
            return load_1_file_from_mem(res,fn);
        }
        else if (umf==__global_config::UMF_DISK_ONLY)
        {
            return load_1_file_from_disk(res,fn);
        }
        else if (umf==__global_config::UMF_1MEMORY_2DISK)
        {
            int r=load_1_file_from_mem(res,fn);
            if (r!=-1)return r;
            return load_1_file_from_disk(res,fn);
        }
        else if (umf==__global_config::UMF_1DISK_2MEMORY)
        {
            int r=load_1_file_from_disk(res,fn);
            if (r!=-1)return r;
            return load_1_file_from_mem(res,fn);
        }
    }
    catch (...) {
        return -1;
    }
    return -1;
}
#ifdef __WITH_FILES_CONF__
bool __global_config::files_exists(const string& key)
{
    return files_conf.exists(key);
}
#endif
#ifdef __WITH_FILES_CONF__
string __global_config::files_get(const string& key)
{
    if (files.exists(key))
    {
        return files[key];
    }
    else if (files_conf.exists(key))
    {
        string body;
        if (load_1_file(body,files_conf[key]) == -1) {
            logErr2("--Error: Failed to read file %s (%s)", key.c_str(), strerror(errno));
            return "";
        }
        files.set(key,body);
        return body;
    }
    logErr2("--Error: Failed to read file %s not defined in files_conf", key.c_str());
    return "";
}
void __global_config::load_files()
{
    files.clear();
    return;
}
#endif
void __global_config::save_cmd_args(int argc, char *argv[])
{
    for (int i=0;i<argc;i++)
    {
        __cmd_args.push_back(argv[i]);
    }
}
void __global_config::scan_opts(params_map& pset,M_LIST<string>&li)
{
    list<string> l=li.get_container();
    for (list<string> ::iterator i=l.begin();i!=l.end();i++)
    {
        int pz = i->find("=", 0);
        if (pz == -1) {
            continue;
        }
        pset.set(i->substr(0, pz), i->substr(pz + 1, i->length() - pz - 1));

    }
}
