#ifdef __GNUC__
#pragma implementation				// gcc: implement sql_udf.h
#endif

#include "stdafx.h"
#include <signal.h>
#include <errno.h>
#include "file_set.h"

#include "web_server_config.h"
#include <sys/types.h>
#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <sys/stat.h>
#include <stdio.h>

#include "str_lib.h"
#ifdef __CKALL
__web_server_config web_server_config;
//#ifndef WIN32
static char mime[]="YXBwbGljYXRpb24vYWN0aXZlbWVzc2FnZQphcHBsaWNhdGlvbi9hbmRyZXctaW5zZXQJZXoKYXBwbGljYXRpb24vYXBwbGVmaWxlCmFwcGxpY2F0aW9uL2F0b21pY21haWwKYXBwbGljYXRpb24vY3Utc2VlbWUJCWNzbSBjdQphcHBsaWNhdGlvbi9kY2EtcmZ0CmFwcGxpY2F0aW9uL2RlYy1keAphcHBsaWNhdGlvbi9leGNlbAkJeGxzCmFwcGxpY2F0aW9uL2dob3N0dmlldwkJCmFwcGxpY2F0aW9uL21hYy1iaW5oZXg0MAlocXgKYXBwbGljYXRpb24vbWFjLWNvbXBhY3Rwcm8JY3B0CmFwcGxpY2F0aW9uL21hY3dyaXRlaWkKYXBwbGljYXRpb24vbXN3b3JkCQlkb2MgZG90IHdyZAphcHBsaWNhdGlvbi9uZXdzLW1lc3NhZ2UtaWQKYXBwbGljYXRpb24vbmV3cy10cmFuc21pc3Npb24KYXBwbGljYXRpb24vb2N0ZXQtc3RyZWFtCWJpbiBkbXMgbGhhIGx6aCBleGUgY2xhc3MKYXBwbGljYXRpb24vb2RhCQkJb2RhCmFwcGxpY2F0aW9uL3BkZgkJCXBkZgphcHBsaWNhdGlvbi9wZ3AJCQlwZ3AKYXBwbGljYXRpb24vcGdwLXNpZ25hdHVyZQlwZ3AKYXBwbGljYXRpb24vcG9zdHNjcmlwdAkJYWkgZXBzIHBzCmFwcGxpY2F0aW9uL3Bvd2VycG9pbnQJCXBwdAphcHBsaWNhdGlvbi9yZW1vdGUtcHJpbnRpbmcKYXBwbGljYXRpb24vcnRmCQkJcnRmCmFwcGxpY2F0aW9uL3NsYXRlCmFwcGxpY2F0aW9uL3dpdGEKYXBwbGljYXRpb24vd29yZHBlcmZlY3Q1LjEJd3A1CmFwcGxpY2F0aW9uL3gtMTIzCQl3awphcHBsaWNhdGlvbi94LVdpbmd6CQl3egphcHBsaWNhdGlvbi94LWJjcGlvCQliY3BpbwphcHBsaWNhdGlvbi94LWNkbGluawkJdmNkCmFwcGxpY2F0aW9uL3gtY2hlc3MtcGduCQlwZ24KYXBwbGljYXRpb24veC1jb21wcmVzcwkJeiBaCmFwcGxpY2F0aW9uL3gtY3BpbwkJY3BpbwphcHBsaWNhdGlvbi94LWNzaAkJY3NoCmFwcGxpY2F0aW9uL3gtZGViaWFuLXBhY2thZ2UJZGViCmFwcGxpY2F0aW9uL3gtZGlyZWN0b3IJCWRjciBkaXIgZHhyCmFwcGxpY2F0aW9uL3gtZHZpCQlkdmkKYXBwbGljYXRpb24veC1ndGFyCQlndGFyIHRnegphcHBsaWNhdGlvbi94LWd1bnppcAkJZ3oKYXBwbGljYXRpb24veC1nemlwCQlnegphcHBsaWNhdGlvbi94LWhkZgkJaGRmCmFwcGxpY2F0aW9uL3gtaHR0cGQtcGhwCQlwaHRtbCBwaHQgcGhwCmFwcGxpY2F0aW9uL3gtamF2YXNjcmlwdAlqcwphcHBsaWNhdGlvbi94LWtvYW4JCXNrcCBza2Qgc2t0IHNrbQphcHBsaWNhdGlvbi94LWxhdGV4CQlsYXRleAphcHBsaWNhdGlvbi94LW1ha2VyCQlmcm0gbWFrZXIgZnJhbWUgZm0gZmIgYm9vayBmYmRvYwphcHBsaWNhdGlvbi94LW1pZgkJbWlmCmFwcGxpY2F0aW9uL3gtbXNkb3MtcHJvZ3JhbQljb20gZXhlIGJhdAphcHBsaWNhdGlvbi94LW5ldGNkZgkJbmMgY2RmCmFwcGxpY2F0aW9uL3gtbnMtcHJveHktYXV0b2NvbmZpZwlwYWMKYXBwbGljYXRpb24veC1wZXJsCQlwbCBwbQphcHBsaWNhdGlvbi94LXNoCQlzaAphcHBsaWNhdGlvbi94LXNoYXIJCXNoYXIKYXBwbGljYXRpb24veC1zdHVmZml0CQlzaXQK"
                   "YXBwbGljYXRpb24veC1zdjRjcGlvCQlzdjRjcGlvCmFwcGxpY2F0aW9uL3gtc3Y0Y3JjCQlzdjRjcmMKYXBwbGljYXRpb24veC10YXIJCXRhcgphcHBsaWNhdGlvbi94LXRjbAkJdGNsCmFwcGxpY2F0aW9uL3gtdGV4CQl0ZXgKYXBwbGljYXRpb24veC10ZXhpbmZvCQl0ZXhpbmZvIHRleGkKYXBwbGljYXRpb24veC10cm9mZgkJdCB0ciByb2ZmCmFwcGxpY2F0aW9uL3gtdHJvZmYtbWFuCQltYW4KYXBwbGljYXRpb24veC10cm9mZi1tZQkJbWUKYXBwbGljYXRpb24veC10cm9mZi1tcwkJbXMKYXBwbGljYXRpb24veC11c3RhcgkJdXN0YXIKYXBwbGljYXRpb24veC13YWlzLXNvdXJjZQlzcmMKYXBwbGljYXRpb24vemlwCQkJemlwCmF1ZGlvL2Jhc2ljCQkJYXUgc25kCmF1ZGlvL21pZGkJCQltaWQgbWlkaSBrYXIKYXVkaW8vbXBlZwkJCW1wZ2EgbXAyIG1wMwphdWRpby94LWFpZmYJCQlhaWYgYWlmYyBhaWZmCmF1ZGlvL3gtcG4tcmVhbGF1ZGlvCQlyYSByYW0KYXVkaW8veC1wbi1yZWFsYXVkaW8tcGx1Z2luCmF1ZGlvL3gtcmVhbGF1ZGlvCQlyYQphdWRpby94LXdhdgkJCXdhdgpjaGVtaWNhbC94LXBkYgkJCXBkYiB4eXoKaW1hZ2UvZ2lmCQkJZ2lmCmltYWdlL2llZgkJCWllZgppbWFnZS9qcGVnCQkJanBlZyBqcGcganBlCmltYWdlL3BuZwkJCXBuZwppbWFnZS90aWZmCQkJdGlmZiB0aWYKaW1hZ2UveC1jbXUtcmFzdGVyCQlyYXMKaW1hZ2UveC1wb3J0YWJsZS1hbnltYXAJCXBubQppbWFnZS94LXBvcnRhYmxlLWJpdG1hcAkJcGJtCmltYWdlL3gtcG9ydGFibGUtZ3JheW1hcAlwZ20KaW1hZ2UveC1wb3J0YWJsZS1waXhtYXAJCXBwbQppbWFnZS94LXJnYgkJCXJnYgppbWFnZS94LXhiaXRtYXAJCQl4Ym0KaW1hZ2UveC14cGl4bWFwCQkJeHBtCmltYWdlL3gteHdpbmRvd2R1bXAJCXh3ZAptZXNzYWdlL2V4dGVybmFsLWJvZHkKbWVzc2FnZS9uZXdzCm1lc3NhZ2UvcGFydGlhbAptZXNzYWdlL3JmYzgyMgptb2RlbC9pZ2VzCQkJaWdzIGlnZXMKbW9kZWwvbWVzaAkJCW1zaCBtZXNoIHNpbG8KbW9kZWwvdnJtbAkJCXdybCB2cm1sCm11bHRpcGFydC9hbHRlcm5hdGl2ZQptdWx0aXBhcnQvYXBwbGVkb3VibGUKbXVsdGlwYXJ0L2RpZ2VzdAptdWx0aXBhcnQvbWl4ZWQKbXVsdGlwYXJ0L3BhcmFsbGVsCnRleHQvY3NzCQkJY3NzCnRleHQvaHRtbAkJCWh0bWwgaHRtCnRleHQvcGxhaW4JCQlhc2MgdHh0IGMgY2MgaCBoaCBjcHAgaHBwCnRleHQvcmljaHRleHQJCQlydHgKdGV4dC90YWItc2VwYXJhdGVkLXZhbHVlcwl0c3YKdGV4dC94LXNldGV4dAkJCWV0eAp0ZXh0L3gtc2dtbAkJCXNnbWwgc2dtCnRleHQveC12Q2FsZW5kYXIJCXZjcwp0ZXh0L3gtdkNhcmQJCQl2Y2YKdGV4dC94bWwJCQl4bWwgZHRkCnZpZGVvL2RsCQkJZGwKdmlkZW8vZmxpCQkJZmxpCnZpZGVvL2dsCQkJZ2wKdmlkZW8vbXBlZwkJCW1wMiBtcGUgbXBlZyBtcGcKdmlkZW8vcXVpY2t0aW1lCQkJcXQgbW92CnZpZGVvL3gtbXN2aWRlbwkJCWF2aQp2aWRlby94LXNnaS1tb3ZpZQkJbW92aWUKeC1jb25mZXJlbmNlL3gtY29vbHRhbGsJ"
                   "CWljZQp4LXdvcmxkL3gtdnJtbAkJCXdybCB2cm1sCg==";
//#else
//static char mime[]="";
//#endif
__web_server_config::__web_server_config():replacementsMX("replacementsMX")
{
    listen_ip="INADDR_ANY";
    listen_port=80;
    accept_handler_timeout_usec=200000;
    max_number_of_accept_handlers=0;
    max_multipart=3050000;
    max_post=200000;
    document_root="./www";
    doc_urls.assign(splitTOKs(",","/html/,/pics/"));

    vector<string> v=splitTOK("\r\n",Base64Decode(mime));
    for (unsigned int i=0;i<v.size();i++) {
        if (!v[i].size()) {
            continue;
        }
        vector<string> q=splitTOK("\t ",v[i].c_str());
        if (q.size()<1) {
            continue;
        }
        string val=q[0];
        for (unsigned int j=1;j<q.size();j++) {
            if (!q[j].size()) {
                continue;
            }
            mime_types.set(q[j],val);
        }
    }

}


void __web_server_config::load_config(const string&pn)
{
    map<string,string>	m=load_m_file(pn);

    set_cfg_i(m,"max_multipart", pn,max_multipart,3050000);
    set_cfg_i(m,"max_post", pn,max_post,200000);
    set_cfg_str(m,"document_root", pn,document_root,"./www");
    set_cfg_i(m,"inspector_time_usec", pn,inspector_time_usec,1000000);

    set_cfg_str(m,"adminfo_url", pn,adminfo_url,"/ainf");


    if (m.count("doc_urls"))
        doc_urls.assign(splitTOKs(",",m["doc_urls"]));
    else
    {
        logErr2("%s: skipped 'doc_urls' parameter, using default '/html/,/pics/'",pn.c_str());
        doc_urls.assign(splitTOKs(",","/html/,/pics/"));
    }
    m.erase("doc_urls");

    if (!m.count("mime_types"))
    {
        logErr2("%s: skipped 'mime_types' unable to continue",pn.c_str());
    }
    string all;
    if (load_1_file(all, m["mime_types"])!=-1)
    {
        vector<string> v=splitTOK("\r\n",all.c_str());
        for (unsigned int i=0;i<v.size();i++) {
            if (!v[i].size()) {
                continue;
            }
            vector<string> q=splitTOK("\t ",v[i].c_str());
            if (q.size()<1) {
                continue;
            }
            string val=q[0];
            for (unsigned int j=1;j<q.size();j++) {
                if (!q[j].size()) {
                    continue;
                }
                mime_types.set(q[j],val);
            }
        }
    }
    m.erase("mime_types");

    replacement_conf.clear();
    {
        string a=get_cfg_str(m,"replacement_config",pn, "./conf/replacement.conf");
        replacement_conf.read(a);
    }
    init_replacements();

    print_rest_cfg(m,pn);

}
void __web_server_config::init_replacements()
{
    M_LOCK(replacementsMX);
    replacements=replacement_conf.get_replacements();
}
map<string,string> __web_server_config::get_replacements()
{
    M_LOCK(replacementsMX);
    map<string,string> ret;
    for (typeof(replacements.begin()) i=replacements.begin();i!=replacements.end();i++)
    {
        if (i->second.size()==1)
        {
            ret[i->first]=i->second[0];
        }
        else
        {
            ret[i->first]=i->second[rand()%i->second.size()];
        }
    }
    return ret;
}
static M_SET<string> ips;

#endif
