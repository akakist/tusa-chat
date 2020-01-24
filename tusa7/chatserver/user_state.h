#ifndef USER___STATE___H
#define USER___STATE___H
struct user_status;
class user_nick;
struct user_pair;
class user_state
{

public:

    enum
    {
        UNDEF=0xffff0000
    };
    set<CH_id> channel;
    user_status status;
    user_nick nick;
    user_state();
    set<CH_id> voice;
    bool operator!=(const user_state&) const;
    enum
    {
        PARTALL			=1,
        RECALC			=2,
        CHANGE_CONTACT_MODE	=3,
        SET_NICK		=4,
        KICK			=5,
        SET_BIN_STATE		=6,
        SET_STATUS		=7,
        CHANGE_CHANNEL		=8,
        PART			=9,
        JOIN			=10,
        CONTACT_ADD		=11,
        CONTACT_REMOVE		=12,
#ifdef __CLAN
        SET_BIN_STATE2		=13
#endif
    };

};
out_oscar_buffer & operator<<(out_oscar_buffer&b, const user_state& n);
oscar_buffer & operator>>(oscar_buffer&b, user_state& n);

#endif
