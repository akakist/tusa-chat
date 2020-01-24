OBJDIR=./objD
ROBJDIR=./objR
############# release config
#CFLAGS= -O2  -I/usr/include/mysql -c -I/usr/local/ssl/include -DLINUX -Dchat -Wall -static
#LIBS=../kall/_apache.a ../kall/libperl.a   /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a  -lpthread -lz -lgdbm -static
#############################


CFLAGS= `cat _CFLAGS_D`

	
RCFLAGS= `cat _CFLAGS_R`

LIBS= /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/local/lib/mysql/libmysqlclient.a  -lpthread -lz /usr/lib/libgdbm.a   -lstlport
RLIBS=/usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/local/lib/mysql/libmysqlclient.a  -lpthread -lz /usr/lib/libgdbm.a   -lstlport

LIBS_DEP=
RLIBS_DEP=

#LIBS= /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a -lboost_regex-gcc-1_32  -lpthread -lz /usr/lib/libgdbm.a    
#RLIBS= /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a -lboost_regex-gcc-1_32  -lpthread -lz /usr/lib/libgdbm.a   

#LIBS= /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex.a -lpthread  -lgdbm   -static
#RLIBS=  /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex.a -lpthread  -lgdbm -static
##########################/usr/local/lib/libstlport_gcc.a 

EXT=exe

LIBNAME=libchat.a
RLIBNAME=libchatR.a
INC_DIRS= .  ../core ../core_web  ../zdes ../kall  _lib   _conf  _forum _admin _irc   ../stdafx data klan io_stuff cs_stuff lib_cs mcassa
TARGETS=chatserver.cpp
	
OBJS=	\
	admin.cpp	\
	admin_accounts.cpp\
	admin_ban.cpp \
	admin_levelup.cpp\
	admin_logininfo.cpp\
	admin_other.cpp \
	admin_privs.cpp\
	admin_settings.cpp\
	admin_userlist_command.cpp\
	admin_vote.cpp\
	app_con.cpp\
	app_server.cpp \
	channels.cpp \
	chat_colors.cpp\
	chat_config.cpp \
	chat_funny.cpp \
	chat_globals.cpp \
	chat_msg.cpp \
	chat_thread.cpp \
	chat_thread_2.cpp \
	chat_process_web.cpp\
	contact_vec.cpp \
	file_dump.cpp\
	forum.cpp \
	fotos.cpp \
	fotos_ui.cpp \
	gallery.cpp\
	ignore_vec.cpp \
	irc_admin.cpp \
	irc_login.cpp \
	irc_server.cpp     \
	irc_server_config.cpp \
	irc_tools.cpp \
	irc_user.cpp \
	levels.cpp	\
	local_user_handle.cpp\
	login.cpp\
	main.cpp  \
	make_login_out.cpp\
	make_user_info.cpp \
	message.cpp \
	nick_vec.cpp\
	notes_containers.cpp   \
	register.cpp \
	settings.cpp\
	u_chat.cpp \
	update_cmd.cpp \
	url_admin_nickban.cpp \
	url_admin_userlist.cpp\
	url_new_nick.cpp  \
	url_settings_credits.cpp \
	user.cpp \
	user_credits.cpp \
	user_info.cpp \
	user_nick.cpp \
	user_profile.cpp \
	user_set.cpp  \
	user_stat.cpp \
	user_state.cpp \
	user_status.cpp \
	utils.cpp \
 	other.cpp \
        notes.cpp\
        vote.cpp \
	main_cs.cpp\
	klan_to_db_io.cpp\
	irc_user_cred.cpp\
	cs_conn_data.cpp\
	do_ban.cpp\
	app_server.cpp\
	PTR.cpp _QUERY.cpp __main.cpp _mutex.cpp _mutex1.cpp copy_file_common.cpp core_main.cpp db_config.cpp db_var.cpp\
    des_sid.cpp errs.cpp file_set.cpp file_set_init.cpp  mysql_extens.cpp  \
    server_config.cpp st_FILE.cpp  st_savecwd.cpp st_stuff.cpp str_lib.cpp str_lib1.cpp str_lib_extra.cpp wrappers.cpp\
    threadable.cpp st_stream_str.cpp \
    c_conn.cpp html_out.cpp tcp_dialog_server.cpp tcp_sender.cpp\
    tcp_server.cpp tcp_server_connection.cpp tcp_stats.cpp thread_info_report.cpp web_adminfo.cpp web_connection.cpp\
    web_connection_ptcp.cpp web_server.cpp web_server_config.cpp web_tools.cpp oscar_buffer.cpp cf_utils.cpp\
	
	url_mcassa.cpp\

#user_profile.cpp foto_profile.cpp 

#	web_adminfo.cpp

#tbl_user.cpp 
