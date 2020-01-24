#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <stdio.h>
#include <map>
#include <set>
#include "user.h"
#include "str_lib.h"
#include "st_stuff.h"
#include "errs.h"
#include "message.h"
#include "chat_def.h"
#include "utils.h"
#include "irc_server.h"
#include "register.h"
#include "file_set.h"
#include "web_server_data.h"
#include "register.h"

#include "channels.h"
#include "irc_server_config.h"
#include "irc_utils.h"
#include "update_cmd.h"
#include "admin.h"
#include "chat_globals.h"
#include "app_def.h"

void irc_cmd_MODE(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_KICK(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_EYE(const PTR_getter<chat_user> &__UU,irc_command &cmd);
void irc_cmd_EYEN(const PTR_getter<chat_user> &__UU,irc_command &cmd);

void irc_cmd_MODE(const PTR_getter<chat_user> &__UU,irc_command &cmd)
{

    string dop;

    vector<string> vc=splitTOK(" ",cmd.data);
    if (vc.size()==0)
    {
        irc_send_reply(__UU,403,"Bad command.");
        return;
    }
    string ircchan=vc[0];

    PTR_getter<chat_channel> ML=chat_channels.by_irc(ircchan);
    if (!ML)
    {
        irc_send_reply(__UU,403,"Unknown channel.");
        return;
    }

    bool moderated=false;
    CH_id ch_id;
    {
        __CH_LOCK(ML);
        moderated=CH->cd.moderated;
        ch_id=CH->cd.chid;
    }
    if (vc.size()>1) {
        dop=strupper(vc[1]);
    }
    string opt;
    {
        user_pair __U(__UU);
        if (user$level(__U)/sub_levels<am_vip && !(user$privileges(__U)&u_allow_set_topic)) opt="+t";
        if (moderated) {
            if (opt.size()) opt+="m";
            else opt="+m";
        }
    }
    user_pair __U(__UU);
    string cnick=GET_CNICK(__U);
    if (!dop.size())
    {
        string sss;
        sss<<":"<<string(irc_server_config.host)<<" 324 "<<cnick<<" "<<ircchan<<" "<<opt<<"\r\n";
        data_push_back(__UU,sss);
    }
    if (dop=="+E") {		//get excepts list
        irc_send_reply(__UU,368,ircchan,"End of exception list");
        return;
    }
    if (dop=="+B") {	//get ban list
        irc_send_reply(__UU,368,ircchan,"End of ban list");
        return;
    }
    if (dop=="+I") {	//get invite list
        irc_send_reply(__UU,347,ircchan,"End of invite list");
        return;
    }
    if (dop=="+BI" || dop=="+BL" || dop=="+BN" || dop=="+V" || dop=="-V" || dop=="+M" || dop=="-M") {
        if (vc.size()<2)
        {
            irc_send_reply(__UU,403,"Bad syntax.");
            return;
        }

        string n;
        if (vc.size()>2)n=vc[2];
        string ip;
        string pip;
        DB_id id;
        unsigned int levsub_levels;
        bool allok=false;
        if (dop=="+M" || dop=="-M") {

            bool state=false;
            if (dop=="+M") state=true;
            if (!do_change_mode(ML,__UU,state)) {
                irc_send_reply(__UU,481,"Operation not permitted.");
            }
            return;
        }
        DB_id zid=all_user_nick_2_DB_id(n);
        if (zid.container) allok=true;
        string znick;
        {
            PGLR(user_set,z,user_sets.find_by_id(zid));
            znick=z->last_nick;
        }
        if (!allok) {
            irc_send_reply(__UU,401,"No such nick/channel.");
            return;
        }
        {
            user_pair __U(__UU);
            levsub_levels=user$level(__U)/sub_levels;
            id=user$id(__U);
        }
        if (dop=="+V" || dop=="-V") {
            bool state=false;
            if (dop=="+V") state=true;
            if (!do_change_voice(ch_id,id,znick,state)) {
                irc_send_reply(__UU,481,"Operation not permitted.");
            }
            return;
        }
        if (levsub_levels<am_guard) {
            irc_send_reply(__UU,481,"Permission denied. You not an IRC operator, or you have few privileges.");
            return;
        }
        int r;
        if (levsub_levels>=7) {
            if (dop=="+BI") r=do_ipban(ip,pip,600,id);
            if (dop=="+BL") r=do_loginban(zid,"",600,id,levsub_levels);
            if (dop=="+BN") r=do_nickban(znick,id,levsub_levels);
        } else {
            r=-1;
        }
        if (r==0 || r==2) {
            {
                user_pair __U(__UU);
                logErr2("%s (%s) banned address %s-%s [%s - %s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),ip.c_str(),pip.c_str(),user$ip(__U).c_str(),user$proxy_ip(__U).c_str());
            }
            irc_send_reply(__UU,481,"Ban MODE: Successfull");
            return;
        } else if (r==-1) {
            irc_send_reply(__UU,481,"Permission denied. You not an IRC operator, or you have few privileges.");
            return;
        }
        else {
            irc_send_reply(__UU,481,"Ban MODE: Already banned.");
            return;
        }
    }

}
void irc_cmd_KICK(const PTR_getter<chat_user> &__UU,irc_command &cmd)
{
    user_pair __U(__UU);
    {
        string cnick;
        string login;
        unsigned int levelsub_levels;
        string kmsg;
        string nick;
        string ip;
        cnick=GET_CNICK(__U);
        login=user$login(__U);
        levelsub_levels=user$level(__U)/sub_levels;
        {
            __UC_LOCK;
            ip=u->cu_ip;
        }
        size_t pz=cmd.data.find(" ",0);
        size_t ppz=cmd.data.find(":",pz);
        if (pz>0) {
            if (ppz!=-1) {
                nick=remove_spaces(cmd.data.substr(pz,ppz-pz));
                kmsg=cmd.data.substr(ppz+1,cmd.data.size()-ppz-1);
            }
            if (ppz==-1) nick=remove_spaces(cmd.data.substr(pz,cmd.data.size()-pz));
        }
        if (!nick.size()) {
            irc_send_reply(__U,401,"No such nick/channel");
            return;
        }
        bool noprivs=false;
        if (levelsub_levels<am_killer) noprivs=true;
        bool done=false;
        if (!noprivs) {
            DB_id zid=all_user_nick_2_DB_id(nick);
            if (zid.container)
            {
//                user_pair __Z(__ZZ);
                unsigned int zlevel;
                string znick,zlogin;

                {
                    PGLR(user_profile,z,user_profiles.find_by_id(zid));
                    zlevel=z->level;
                    zlogin=z->login;
                }
                {
                    PGLR(user_set,z,user_sets.find_by_id(zid));
                    znick=z->last_nick;

                }

                int u_kick_ability=LEVELS(user$level(__U)).kick_ability;
                int z_kick_shield=LEVELS(zlevel).kick_shield;
                if (u_kick_ability>z_kick_shield)
                {
                    kick_user(zid,kmsg);
                    //string znick,zlogin;

                    logErr2("User %s (%s) was kicked by %s (%s) - %s [%s]",znick.c_str(),zlogin.c_str(),cnick.c_str(),login.c_str(),kmsg.c_str(),ip.c_str());
                    done=true;
                    send_update_g2(user_stat$inc_kick_count,user$id(__U));
                    send_update_g2(user_stat$inc_kicked_count,zid);

                } else {
                    irc_send_reply(__U,481,"Permission denied. Not enough kick ability.");
                    noprivs=true;
                    return;
                }
            }
        }
        if (noprivs) {
            irc_send_reply(__U,481,"Permission denied. You not an IRC operator, or you have few privileges.");
            return;
        }
        if (!done) {
            irc_send_reply(__U,401,"No such nick/channel");
            return;
        }
    }

}
void irc_cmd_EYE(const PTR_getter<chat_user> &__UU,irc_command &cmd)
{
    user_pair __U(__UU);
    {
        int ulevel;
        ulevel=user$level(__U);
        if (ulevel/sub_levels<am_admin) {
            irc_send_reply(__U,481,"Permission denied. You not an IRC operator, or you have few privileges.");
            return;
        }
        DB_id id=user$id(__U);
        if (strupper(cmd.data)=="ON") {
            DB_id id=user$id(__U);
            {
                PGLW(user_set, u,user_sets.find_by_id(id));
                u->setting_show_eye=true;
                send_update_g3(user_set$setting_show_eye,id,u->setting_show_eye);
            }
            irc_send_reply(__U,300,"Eye state is on ON");
        } else if (strupper(cmd.data)=="OFF") {
            {
                PGLW(user_set, u,user_sets.find_by_id(id));
                u->setting_show_eye=false;
                send_update_g3(user_set$setting_show_eye,id,u->setting_show_eye);
            }
            irc_send_reply(__U,300,"Eye state is on OFF");
        } else {
            irc_send_reply(__U,421,cmd.command+": not enough arguments. Syntax: EYE on|off");
        }
    }
}
void irc_cmd_EYEN(const PTR_getter<chat_user> &__UU,irc_command &cmd)
{
    user_pair __U(__UU);
    DB_id id=user$id(__U);
    {
        PGLW(user_set, u,user_sets.find_by_id(id));
        u->neye=atoi(cmd.data);
        send_update_g3(user_set$neye,id,u->neye);
    }
    irc_send_reply(__U,300,"Eye number set to "+itostring(atoi(cmd.data)));
}
