OBJDIR=./objD
ROBJDIR=./objR
############# release config
#CFLAGS= -O2  -I/usr/include/mysql -c -I/usr/local/ssl/include -DLINUX -Dchat -Wall 
#LIBS=../kall/_apache.a ../kall/libperl.a   /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a  -lpthread -lz -lgdbm 
#############################


CFLAGS= `cat _CFLAGS_D` -DSVN_VERSION="\"`svnversion`\""

#-DUSE_MUTEX_TRYLOCK	
	
RCFLAGS= `cat _CFLAGS_R` -DSVN_VERSION="\"`svnversion`\""

#32bit

#LIBS=  /usr/lib/libssl.a /usr/lib/libcrypto.a  /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread /usr/lib/libz.a /usr/lib/libgdbm.a       
#RLIBS=  /usr/lib/libssl.a /usr/lib/libcrypto.a  /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread /usr/lib/libz.a /usr/lib/libgdbm.a     

#64 bit

LIBS= /usr/lib/libssl.a /usr/lib/libcrypto.a /usr/local/lib/mysql/libmysqlclient.a   -lpthread /usr/lib/libz.a /usr/local/lib/libstlport.a
RLIBS= /usr/lib/libssl.a /usr/lib/libcrypto.a /usr/local/lib/mysql/libmysqlclient.a -lpthread /usr/lib/libz.a  /usr/local/lib/libstlport.a


LIBS_DEP=core_web1/libcoreweb_d.a core1/libcommon_d.a  
RLIBS_DEP=core_web1/libcoreweb_r.a core1/libcommon_r.a

#LIBS= /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a -lboost_regex-gcc-1_32  -lpthread -lz /usr/lib/libgdbm.a    
#RLIBS= /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a -lboost_regex-gcc-1_32  -lpthread -lz /usr/lib/libgdbm.a   

#LIBS= /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex.a -lpthread  -lgdbm   -static
#RLIBS=  /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex.a -lpthread  -lgdbm -static
##########################/usr/local/lib/libstlport_gcc.a 



LIBNAME=libchat_d.a
RLIBNAME=libchat_r.a
INC_DIRS= .  ../core ../core_web ../chatserver ../stdafx ../core_cs/common     ../chatserver/_lib   _conf  ../chatserver/_forum ../chatserver/_admin ../chatserver/_irc    ../chatserver/data ../chatserver/klan ../chatserver/io_stuff   ../core_cs/bos_client ../chatserver/_forum  
TARGETS=clan_server.cpp 
	
OBJS= app_con.cpp app_server.cpp clan_parser.cpp  file_dump.cpp clan_con.cpp main.cpp\
    channels.cpp u_chat.cpp fotos.cpp notes.cpp notes_containers.cpp chat_config.cpp message.cpp chat_colors.cpp\
    user_set.cpp levels.cpp chat_globals.cpp  update_cmd.cpp ignore_vec.cpp user_set.cpp user.cpp\
    contact_vec.cpp user_stat.cpp user_stat.cpp user_state.cpp user_status.cpp chat_thread.cpp  \
    chat_thread_2.cpp user_nick.cpp utils.cpp irc_server_config.cpp nick_vec.cpp chat_msg.cpp irc_tools.cpp\
     user_credits.cpp user_profile.cpp irc_server.cpp irc_user.cpp irc_admin.cpp irc_login.cpp\
    klan_to_db_io.cpp user_info.cpp make_user_info.cpp  register.cpp login.cpp make_login_out.cpp\
    fotos_ui.cpp other.cpp settings.cpp gallery.cpp klan_to_db_io.cpp local_user_handle.cpp  clan_client.cpp\
    bos_client_interface.cpp bos_client.cpp oscar_client.cpp global_state.cpp vote.cpp forum.cpp admin_ban.cpp\
    url_settings_credits.cpp url_new_nick.cpp admin.cpp admin_settings.cpp admin_logininfo.cpp admin_privs.cpp\
    admin_levelup.cpp admin_userlist_command.cpp url_admin_userlist.cpp admin_other.cpp admin_vote.cpp
	

#user_profile.cpp foto_profile.cpp 

#	web_adminfo.cpp

#tbl_user.cpp 
