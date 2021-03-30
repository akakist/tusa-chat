#ifdef __GNUC__
#pragma implementation				// gcc: implement sql_udf.h
#endif

#include "stdafx.h"
#include <sys/stat.h>
#include <list>
#include "sid_t.h"
#include "web_server.h"
#include "des_sid.h"
#include "str_lib.h"
#include "web_connection.h"

#include "file_set.h"
#include "web_tools.h"
#include "web_server_data.h"


#include "st_stuff.h"
#include "server_config.h"

#include "thread_descr.h"
int S_recv(const PTR_getter<c_socket>&__S,void *buf, size_t len, int flags);

std::string __gets(const PTR_getter <c_socket> &__S, const string &delim);

void WRITES__(const string &S)
{
    string s=S+"\n";
    static _mutex Mutex("WRITES__MX");
    M_LOCK(Mutex);
    FILE * f=fopen("in.dmp","ab+");
    fwrite(s.data(),s.size(),1,f);
    printf("%s",s.c_str());
    fclose(f);
}
void web_connection::process_tcp()
{

    try {
        int total_recv=0;
        if (!socket)
        {
            return;
        }
        {

            PGLW(c_socket, psock,socket);
            if (psock->get_socket_fd()>FD_SETSIZE-1)
            {
                psock->timeout_sec = 1;
                psock->timeout_usec = 1;
            }
            else
            {
                psock->timeout_sec = 1;
                psock->timeout_usec = 1;
            }
        }
        max_recv = 1024;
        {

            string fl=__gets(socket,"\r\n");
            total_recv+=fl.size();
            int pom = fl.find(" ", 0);
            if (pom == -1) {
                return;
            }


            string METHOD = strupper(fl.substr(0, pom));
            url = fl.substr(pom + 1, fl.find(" ", pom + 1) - pom - 1);
            url = repl_percent(url);
            if (url.find("..", 0) != -1) {
                return;
            }
            string newstr;
            {
                newstr = __gets(socket,"\r\n");
                total_recv+=newstr.size();
            }
            time_t start_t=time(NULL);
            while (newstr != "") {
                if (time(NULL)-start_t>5) {
                    PGLR(c_socket,s,socket);
                    return;
                }
                int pop = newstr.find(":", 0);
                if (pop == -1) {
                    return;
                }
                params[strupper(newstr.substr(0, pop))] = newstr.substr(pop + 2, newstr.length() - pop - 2);
                newstr = __gets(socket,"\r\n");
                total_recv+=newstr.size();
            }
            if (METHOD != "GET" && METHOD != "POST") {
                return;
            }
            if (params.find("COOKIE") != params.end()) {

                vector < string > v = splitTOK("; ", params["COOKIE"]);
                for (unsigned int i = 0; i < v.size(); i++) {
                    string q = v[i];
                    if (q == " ") {
                        continue;
                    }
                    int z;
                    z = q.find("=", 0);
                    if (z == -1) {
                        continue;
                    }
                    params[q.substr(0, z)] = q.substr(z + 1, q.size() - z - 1);
                }
            }

            int qp = url.find("?", 0);
            if (parse_url && qp != -1) {
                original_params=url.substr(qp + 1, url.length() - qp - 1);
                split_params(original_params);
                url = url.substr(0, qp);
            }
//            params["URL"] = url;
            if (METHOD == "POST") {

                if (params["CONTENT-TYPE"].find("multipart/form", 0) == -1) {
                    //std method
                    int maxpost = server_ref->max_post.get();
                    max_recv = total_recv + maxpost;
                    int clen = atoi(params["CONTENT-LENGTH"]);
                    if (clen <= 0 || clen > maxpost) {
                        return;
                    }
                    st_malloc b(clen + 10);
                    int rdlen=0;
                    time_t start_t=time(NULL);
                    while (1)
                    {
                        if (time(NULL)-start_t>10) {
                            PGLR(c_socket,s,socket);
                            throw cError("break loop");
                            return;
                        }
                        int res=0;
//			if(readable(socket,0,0))
                        //..{
                        res=S_recv(socket,(char *)b.buf+rdlen, clen-rdlen,0);
                        //}
                        if (res==-1) {
                            return;
                        }

                        rdlen+=res;
                        if (rdlen==clen) break;
                    }

                    //					}
                    string pd((char *)b.buf, clen);
                    split_params(pd);
                }
                else {

                    //Multipart form
                    max_recv = total_recv + server_ref->max_multipart.get();

                    string t(params["CONTENT-TYPE"]);
                    int pz = t.find("boundary=", 0);
                    if (pz == -1) {

                        return;
                    }
                    string bound = "--" + t.substr(pz + 9, t.length() - pz - 9);
                    string ebound = bound + "--";
                    string sbuf;
                    string n;
                    bool is_data = false;
                    bool nfirst = false;
                    string data;


                    {


                        sbuf = __gets(socket,ebound);

                        time_t start_t=time(NULL);
                        while (sbuf.size())
                        {
                            if (time(NULL)-start_t>5) {
                                PGLR(c_socket,s,socket);
                                throw cError("break loop");
                                return;
                            }

                            string s;
                            int pos=sbuf.find(bound);
                            if (pos==-1)
                            {
                                s=sbuf;
                                sbuf="";
                            }
                            else
                            {
                                s=sbuf.substr(0,pos);
                                sbuf=sbuf.substr(pos+bound.size(),sbuf.size()-pos-bound.size());
                            }


                            if (s.size()>1)
                            {
                                if (s[0]=='\r'&&s[1]=='\n') s=s.substr(2,s.size()-2);
                            }

                            if (s.size())
                            {
                                map<string,string> lparams;
                                string content;
                                time_t start_t=time(NULL);
                                while (1)
                                {
                                    if (time(NULL)-start_t>5) {
                                        PGLR(c_socket,s,socket);
                                        throw cError("break loop");
                                        return;
                                    }


                                    string sloc;
                                    int pp=s.find("\r\n");
                                    if (pp==-1) {
                                        logErr2("bad multipart %s %d",__FILE__,__LINE__);
                                        return;
                                    }
                                    sloc=s.substr(0,pp);
                                    s=s.substr(pp+2,s.size()-pp-2);
                                    if (!sloc.size()) {
                                        content=s.substr(0,s.size()-2);
                                        break;
                                    }
                                    int pz=sloc.find(": ");
                                    if (pz==-1) {
                                        logErr2("bad multipart %s %d",__FILE__,__LINE__);
                                        return;
                                    }
                                    string key=sloc.substr(0,pz);
                                    string val=sloc.substr(pz+2,sloc.size()-pz-2);
                                    lparams[key]=val;
                                }

                                if (lparams.count("Content-Disposition"))
                                {
                                    string cd=lparams["Content-Disposition"];
                                    vector<string> flds;
                                    time_t start_t=time(NULL);
                                    while (cd.size())
                                    {
                                        if (time(NULL)-start_t>5) {
                                            PGLR(c_socket,s,socket);
                                            throw cError("break loop");
                                            return;
                                        }
                                        int ps=cd.find("; ");
                                        if (ps==-1)
                                        {
                                            flds.push_back(cd);
                                            cd="";
                                        }
                                        else
                                        {
                                            flds.push_back(cd.substr(0,ps));
                                            cd=cd.substr(ps+2,cd.size()-2);
                                        }
                                    }
                                    string name;
                                    string filename;
                                    for (unsigned i=0;i<flds.size();i++)
                                    {
                                        int pzz=flds[i].find("=");
                                        if (pzz!=-1)
                                        {
                                            string key=flds[i].substr(0,pzz);
                                            string val=flds[i].substr(pzz+1,flds[i].size()-1);
                                            if (val.size()>2)
                                            {
                                                if (val[0]=='\"' && val[val.size()-1]=='\"') val=val.substr(1,val.size()-2);
                                            }
                                            if (val=="\"\"") val="";
                                            if (key=="name") name=val;
                                            if (key=="filename") filename=val;
                                        }
                                    }
                                    params[name]=content;
                                    if (filename.size())
                                        params[name+"_FILENAME"]=filename;
                                    for (map<string,string>::iterator i=lparams.begin();i!=lparams.end();i++)
                                    {
                                        string q = strupper(i->first);
                                        string k=name + "_" + q;
                                        params[k] = i->second;
                                    }
                                }
                            }
                        }
                    }
                    //return;
                }
            }
        }
        if (!params.count("USER-AGENT")) params["USER-AGENT"]="User-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)";
        string url_lwr(strlower(url));
        if (params["USER-AGENT"].find("MSIE", 0) == -1) {
            browser = "nn";
        }
        if (url.substr(0, 5) == "/css/") {
            string n = url.substr(5, url.size() - 5);
            send_other((string)server_ref->document_root.get() + url);
            return;
        }
        set<string> du=server_ref->doc_urls.get_container();
        for (set<string>::iterator i=du.begin();i!=du.end();i++)
        {
            if (url.substr(0, i->size()) == *i) {
                send_other(server_ref->document_root.get() + url);
                return;
            }

        }
        ///////////////
        string outtt;
        proxy_ip=params["X-FORWARDED-FOR"];
        peer_ipaddress=tcp_peer_ipaddress;
        process_web();	//PROCESS !!!!
        bool connected;
        {
            PGLW(c_socket, psock,socket);
            connected=psock->connected();
        }
        if (connected && allow_build_response) {

            outtt = build_html_response();
        }
        if (outtt.size() && allow_build_response) {
            write(outtt);

        }
        return;
    }
    catch (socketError e) {//
#ifdef DEBUG
        if (e.error_string.find("reset by") == -1 && e.error_string.find("timeout") == -1 && e.error_string.find("send Broke") == -1)
            logErr("--socketError: wc_ptcp() - %s [%s]", e.error_string.c_str(), peer_ipaddress.c_str());
#endif
    }
    catch (cError e) {
#ifdef DEBUG
        if (e.error_string.find("reset by") == -1 && e.error_string.find("timeout") == -1 && e.error_string.find("send Broke") == -1)
            logErr("--cError: wc_ptcp() - %s [%s]", e.error_string.c_str(), peer_ipaddress.c_str());
#endif
    }
    catch (...) {
#ifdef DEBUG
        logErr("--Error: wc_ptcp() - unknown error [%s]", peer_ipaddress.c_str());
#endif
    }
}
