#ifndef CS_CONN_DATA__H
#define CS_CONN_DATA__H
class app_connection;
class web_connection;
class cs_conn_data
{
public:
    //in
    web_connection * wc;
    map<string,string>& params;
    string &url;
    vector<string>&vurl;
    string &proxy_ip;
    string &peer_ipaddress;
    unsigned int &clan_id;

    //out
    map<string,string>& cookies;
    hstring &html_out;
    string redirect_url;

    // tmp vars
    bool &user_unregistered;
    DB_id &user_id;
    unsigned int &sub_level;

    // methods
    void redirect(const string &url);
    string redirect();
    cs_conn_data(web_connection *_wc,
                 map<string,string>& _params,
                 string &_url,
                 vector<string>&_vurl,
                 string &_proxy_ip,
                 string &_peer_ipaddress,
                 unsigned int &clan_id,
                 map<string,string>& _cookies,
                 hstring &_html_out,
                 bool &_user_unregistered,
                 DB_id &_user_id,
                 unsigned int &_sub_level);
    ~cs_conn_data();
};
#endif
