#ifndef USER___STATUS__H
#define USER___STATUS__H

struct user_status
{
    string name;
    int pic;
    int id;
    bool disable_invite;
    bool uniq;
    bool operator!=(const user_status&) const;
};
out_oscar_buffer & operator<<(out_oscar_buffer&b, const user_status &n);
oscar_buffer & operator>>(oscar_buffer&b, user_status &n);

#endif
