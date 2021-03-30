#ifndef CHAT_CHANNLE_DATA___H
#define CHAT_CHANNLE_DATA___H
class chat_channel_data
{
public:
    string irc_name;
    map<string,string> 	names;
    CH_id chid;
    int move_to_channel;
    bool move;
    bool save_messages;
    bool censored;
    string topic;
    string set_by;
    time_t topic_time;
    int read_level;
    int write_level;
    bool extended;
    bool moderated;
    bool no_statistic;
    string name() const;
    string name2() const;

};
out_oscar_buffer & operator<<(out_oscar_buffer&b, const chat_channel_data &n);
oscar_buffer & operator>>(oscar_buffer&b, chat_channel_data &n);

#endif
