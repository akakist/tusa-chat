#include "stdafx.h"
#include <map>
#include <string>
using namespace std;
#include "DB_id.h"
#include "PTR.h"
#include "html_out.h"
#include "c_conn.h"
#include "cs_conn_data.h"
#include "app_server.h"
#include "user.h"
#include "app_con.h"

void cs_conn_data::redirect(const string &url)
{

    if (wc)
        return wc->redirect(url);
    else redirect_url=url;
}
string cs_conn_data::redirect()
{
    return "<html><script>window.top.location='/relogin';</script>";
}
cs_conn_data::cs_conn_data(web_connection *_wc,
                           map<string,string>& _params,
                           string &_url,
                           vector<string>&_vurl,
                           string &_proxy_ip,
                           string &_peer_ipaddress,
                           unsigned int & _clan_id,
                           map<string,string>& _cookies,
                           hstring &_html_out,
                           bool &_user_unregistered,
                           DB_id &_user_id,
                           unsigned int &_sub_level
                          ): wc(_wc),params(_params),url(_url),vurl(_vurl),proxy_ip(_proxy_ip),peer_ipaddress(_peer_ipaddress),clan_id(_clan_id),
        cookies(_cookies),html_out(_html_out),user_unregistered(_user_unregistered),user_id(_user_id),sub_level(_sub_level)
{
}

cs_conn_data::~cs_conn_data()
{
}
