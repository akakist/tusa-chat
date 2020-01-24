#check_path_wfn(./objR/kall)
#stat ./objR 0
#check_path_wfn(./objD/kall)
#stat ./objD 0

CFLAGS= `cat _CFLAGS_D` -DCOMPILE_TIME=`./gettime.pl` -DSVN_VERSION="\"`svnversion`\"" -I. -I../core -I../core-web -I../stdafx -Idata

RCFLAGS= `cat _CFLAGS_R` -DCOMPILE_TIME=`./gettime.pl` -DSVN_VERSION="\"`svnversion`\"" -I. -I../core -I../core-web -I../stdafx -Idata

LIBS= -lssl -lcrypto /usr/lib/libmysqlclient.a   -lpthread -lz 

RLIBS= -lssl -lcrypto /usr/lib/libmysqlclient.a -lpthread -lz 

OBJDIR=./objD

ROBJDIR=./objR

all: libchat.a CS_tusa.exe 
CS_tusa.exe: libchat.a  $(OBJDIR)/CS_tusa.o
		c++ $(OBJDIR)/CS_tusa.o -o CS_tusa.exe libchat.a  $(LIBS) 


libchat.a: \
	$(OBJDIR)/Double.o\
	$(OBJDIR)/PTR.o\
	$(OBJDIR)/_QUERY.o\
	$(OBJDIR)/__main.o\
	$(OBJDIR)/_mutex.o\
	$(OBJDIR)/_mutex1.o\
	$(OBJDIR)/admin.o\
	$(OBJDIR)/admin_ban.o\
	$(OBJDIR)/admin_old_ban.o\
	$(OBJDIR)/admin_other.o\
	$(OBJDIR)/admin_privs.o\
	$(OBJDIR)/admin_settings.o\
	$(OBJDIR)/app_con.o\
	$(OBJDIR)/app_server.o\
	$(OBJDIR)/c_conn.o\
	$(OBJDIR)/channels.o\
	$(OBJDIR)/chat_colors.o\
	$(OBJDIR)/chat_config.o\
	$(OBJDIR)/chat_globals.o\
	$(OBJDIR)/chat_msg.o\
	$(OBJDIR)/chat_thread.o\
	$(OBJDIR)/chat_thread_2.o\
	$(OBJDIR)/contact_vec.o\
	$(OBJDIR)/copy_file_common.o\
	$(OBJDIR)/core_main.o\
	$(OBJDIR)/cutils.o\
	$(OBJDIR)/db_config.o\
	$(OBJDIR)/db_config2.o\
	$(OBJDIR)/db_var.o\
	$(OBJDIR)/des_sid.o\
	$(OBJDIR)/errs.o\
	$(OBJDIR)/file_dump.o\
	$(OBJDIR)/file_set.o\
	$(OBJDIR)/file_set_init.o\
	$(OBJDIR)/global_state.o\
	$(OBJDIR)/html_out.o\
	$(OBJDIR)/ignore_vec.o\
	$(OBJDIR)/irc_admin.o\
	$(OBJDIR)/irc_login.o\
	$(OBJDIR)/irc_server.o\
	$(OBJDIR)/irc_server_config.o\
	$(OBJDIR)/irc_tools.o\
	$(OBJDIR)/irc_user.o\
	$(OBJDIR)/irc_user_cred.o\
	$(OBJDIR)/levels.o\
	$(OBJDIR)/license.o\
	$(OBJDIR)/local_user_handle.o\
	$(OBJDIR)/login.o\
	$(OBJDIR)/main.o\
	$(OBJDIR)/make_user_info.o\
	$(OBJDIR)/message.o\
	$(OBJDIR)/mutex_inspector.o\
	$(OBJDIR)/mysql_extens.o\
	$(OBJDIR)/mysql_extens2.o\
	$(OBJDIR)/nick_vec.o\
	$(OBJDIR)/notes.o\
	$(OBJDIR)/notes_containers.o\
	$(OBJDIR)/oscar_buffer.o\
	$(OBJDIR)/oscar_client.o\
	$(OBJDIR)/other.o\
	$(OBJDIR)/rijndael.o\
	$(OBJDIR)/server_config.o\
	$(OBJDIR)/st_FILE.o\
	$(OBJDIR)/st_rsa.o\
	$(OBJDIR)/st_savecwd.o\
	$(OBJDIR)/st_stream_str.o\
	$(OBJDIR)/st_stuff.o\
	$(OBJDIR)/str_lib.o\
	$(OBJDIR)/str_lib1.o\
	$(OBJDIR)/str_lib_extra.o\
	$(OBJDIR)/tcp_dialog_server.o\
	$(OBJDIR)/tcp_oscar_dialog_server.o\
	$(OBJDIR)/tcp_sender.o\
	$(OBJDIR)/tcp_server.o\
	$(OBJDIR)/tcp_server_connection.o\
	$(OBJDIR)/tcp_stats.o\
	$(OBJDIR)/thread_info_report.o\
	$(OBJDIR)/threadable.o\
	$(OBJDIR)/u_chat.o\
	$(OBJDIR)/update_cmd.o\
	$(OBJDIR)/url_change_nick.o\
	$(OBJDIR)/url_chat_messages.o\
	$(OBJDIR)/url_chat_sendmessage.o\
	$(OBJDIR)/url_ignore_user.o\
	$(OBJDIR)/url_new_nick.o\
	$(OBJDIR)/url_set_user_status.o\
	$(OBJDIR)/user.o\
	$(OBJDIR)/user_credits.o\
	$(OBJDIR)/user_nick.o\
	$(OBJDIR)/user_profile.o\
	$(OBJDIR)/user_state.o\
	$(OBJDIR)/web_adminfo.o\
	$(OBJDIR)/web_cache.o\
	$(OBJDIR)/web_connection.o\
	$(OBJDIR)/web_connection_ptcp.o\
	$(OBJDIR)/web_server.o\
	$(OBJDIR)/web_tools.o\
	$(OBJDIR)/wrappers.o
		 ar -r libchat.a $(OBJDIR)/Double.o $(OBJDIR)/PTR.o $(OBJDIR)/_QUERY.o $(OBJDIR)/__main.o $(OBJDIR)/_mutex.o $(OBJDIR)/_mutex1.o $(OBJDIR)/admin.o $(OBJDIR)/admin_ban.o $(OBJDIR)/admin_old_ban.o $(OBJDIR)/admin_other.o $(OBJDIR)/admin_privs.o $(OBJDIR)/admin_settings.o $(OBJDIR)/app_con.o $(OBJDIR)/app_server.o $(OBJDIR)/c_conn.o $(OBJDIR)/channels.o $(OBJDIR)/chat_colors.o $(OBJDIR)/chat_config.o $(OBJDIR)/chat_globals.o $(OBJDIR)/chat_msg.o $(OBJDIR)/chat_thread.o $(OBJDIR)/chat_thread_2.o $(OBJDIR)/contact_vec.o $(OBJDIR)/copy_file_common.o $(OBJDIR)/core_main.o $(OBJDIR)/cutils.o $(OBJDIR)/db_config.o $(OBJDIR)/db_config2.o $(OBJDIR)/db_var.o $(OBJDIR)/des_sid.o $(OBJDIR)/errs.o $(OBJDIR)/file_dump.o $(OBJDIR)/file_set.o $(OBJDIR)/file_set_init.o $(OBJDIR)/global_state.o $(OBJDIR)/html_out.o $(OBJDIR)/ignore_vec.o $(OBJDIR)/irc_admin.o $(OBJDIR)/irc_login.o $(OBJDIR)/irc_server.o $(OBJDIR)/irc_server_config.o $(OBJDIR)/irc_tools.o $(OBJDIR)/irc_user.o $(OBJDIR)/irc_user_cred.o $(OBJDIR)/levels.o $(OBJDIR)/license.o $(OBJDIR)/local_user_handle.o $(OBJDIR)/login.o $(OBJDIR)/main.o $(OBJDIR)/make_user_info.o $(OBJDIR)/message.o $(OBJDIR)/mutex_inspector.o $(OBJDIR)/mysql_extens.o $(OBJDIR)/mysql_extens2.o $(OBJDIR)/nick_vec.o $(OBJDIR)/notes.o $(OBJDIR)/notes_containers.o $(OBJDIR)/oscar_buffer.o $(OBJDIR)/oscar_client.o $(OBJDIR)/other.o $(OBJDIR)/rijndael.o $(OBJDIR)/server_config.o $(OBJDIR)/st_FILE.o $(OBJDIR)/st_rsa.o $(OBJDIR)/st_savecwd.o $(OBJDIR)/st_stream_str.o $(OBJDIR)/st_stuff.o $(OBJDIR)/str_lib.o $(OBJDIR)/str_lib1.o $(OBJDIR)/str_lib_extra.o $(OBJDIR)/tcp_dialog_server.o $(OBJDIR)/tcp_oscar_dialog_server.o $(OBJDIR)/tcp_sender.o $(OBJDIR)/tcp_server.o $(OBJDIR)/tcp_server_connection.o $(OBJDIR)/tcp_stats.o $(OBJDIR)/thread_info_report.o $(OBJDIR)/threadable.o $(OBJDIR)/u_chat.o $(OBJDIR)/update_cmd.o $(OBJDIR)/url_change_nick.o $(OBJDIR)/url_chat_messages.o $(OBJDIR)/url_chat_sendmessage.o $(OBJDIR)/url_ignore_user.o $(OBJDIR)/url_new_nick.o $(OBJDIR)/url_set_user_status.o $(OBJDIR)/user.o $(OBJDIR)/user_credits.o $(OBJDIR)/user_nick.o $(OBJDIR)/user_profile.o $(OBJDIR)/user_state.o $(OBJDIR)/web_adminfo.o $(OBJDIR)/web_cache.o $(OBJDIR)/web_connection.o $(OBJDIR)/web_connection_ptcp.o $(OBJDIR)/web_server.o $(OBJDIR)/web_tools.o $(OBJDIR)/wrappers.o 

./objD/CS_tusa.o: CS_tusa.cpp ../stdafx/stdafx.h ../core/file_set.h \
 ../core/M_LIST.h ../core/_mutex.h ../core/m_var.h ../core/PTR.h \
 ../core/errs.h ../core/mutex_inspector.h ../core/lockctl.h \
 ../core/mutex_inspector.h chat_def.h ../core-web/web_server_data.h \
 ../core/M_MAP.h ../core/M_DEQUE.h ../core/m_var.h ../core-web/c_conn.h \
 ../core/_mutex.h ../core/mysql_extens.h ../core/_QUERY.h user.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h cutils.h \
 ../core-web/tcp_server_data.h ../core-web/tcp_server_connection.h \
 ../core-web/c_conn.h app_server.h ../core-web/web_server.h \
 ../core-web/tcp_server.h ../core/threadable.h ../core/M_MAP.h \
 ../core/M_SET.h app_def.h version.h irc_server.h \
 ../core-web/tcp_server.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h irc_server_config.h contact_vec.h \
 ignore_vec.h channels.h notes.h ../core-web/html_out.h user_credits.h \
 chat_thread_event.h chat_stuff.h chat_msg.h chat_config.h global_state.h \
 admin.h ../core/server_config.h ../core/M_SET.h ../core/file_set.h \
 ../core/db_config.h ../core-web/tcp_sender.h
	 c++ $(CFLAGS) ./CS_tusa.cpp -o $(OBJDIR)/CS_tusa.o

./objD/Double.o: ../core/Double.cpp ../stdafx/stdafx.h ../core/oscar_buffer.h \
 ../core/Double.h ../core/str_lib.h ../core/errs.h ../core/m_var.h \
 ../core/_mutex.h
	 c++ $(CFLAGS) ../core/Double.cpp -o $(OBJDIR)/Double.o

./objD/PTR.o: ../core/PTR.cpp ../stdafx/stdafx.h ../core/PTR.h ../core/_mutex.h \
 ../core/errs.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core/lockctl.h
	 c++ $(CFLAGS) ../core/PTR.cpp -o $(OBJDIR)/PTR.o

./objD/_QUERY.o: ../core/_QUERY.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/_QUERY.h ../core/mysql_extens.h ../core/str_lib.h ../core/errs.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h \
 ../core/mutex_inspector.h ../core/lockctl.h
	 c++ $(CFLAGS) ../core/_QUERY.cpp -o $(OBJDIR)/_QUERY.o

./objD/__main.o: ../core/__main.cpp ../stdafx/stdafx.h
	 c++ $(CFLAGS) ../core/__main.cpp -o $(OBJDIR)/__main.o

./objD/_mutex.o: ../core/_mutex.cpp ../stdafx/stdafx.h ../core/errs.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/lockctl.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h
	 c++ $(CFLAGS) ../core/_mutex.cpp -o $(OBJDIR)/_mutex.o

./objD/_mutex1.o: ../core/_mutex1.cpp ../stdafx/stdafx.h ../core/errs.h \
 ../core/_mutex.h ../core/_mutex1.h ../core/mutex_inspector.h \
 ../core/lockctl.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h
	 c++ $(CFLAGS) ../core/_mutex1.cpp -o $(OBJDIR)/_mutex1.o

./objD/admin.o: admin.cpp ../stdafx/stdafx.h ../core/mutex_inspector.h \
 ../core/_mutex.h ../core/errs.h ../core/lockctl.h ../core/mysql_extens.h \
 ../core/_QUERY.h user.h ../core/_mutex.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h channels.h ../core/server_config.h ../core/M_MAP.h \
 ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h app_def.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h ../core-web/web_tools.h update_cmd.h
	 c++ $(CFLAGS) ./admin.cpp -o $(OBJDIR)/admin.o

./objD/admin_ban.o: admin_ban.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server_data.h ../core/M_MAP.h \
 ../core/M_DEQUE.h ../core/file_set.h ../core/M_LIST.h \
 ../core/copy_file.h channels.h ../core/server_config.h ../core/M_MAP.h \
 ../core/M_SET.h ../core/file_set.h app_def.h admin.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h chat_globals.h update_cmd.h \
 ../core-web/web_tools.h global_state.h chat_config.h ../core/M_SET.h
	 c++ $(CFLAGS) ./admin_ban.cpp -o $(OBJDIR)/admin_ban.o

./objD/admin_old_ban.o: admin_old_ban.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 app_con.h ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core/copy_file.h \
 admin.h channels.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h app_def.h
	 c++ $(CFLAGS) ./admin_old_ban.cpp -o $(OBJDIR)/admin_old_ban.o

./objD/admin_other.o: admin_other.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core/copy_file.h \
 channels.h ../core/server_config.h ../core/M_SET.h ../core/file_set.h \
 chat_config.h app_def.h chat_thread_event.h chat_stuff.h chat_msg.h \
 user_credits.h update_cmd.h ../core-web/web_tools.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h \
 chat_globals.h
	 c++ $(CFLAGS) ./admin_other.cpp -o $(OBJDIR)/admin_other.o

./objD/admin_privs.o: admin_privs.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server_data.h ../core/M_MAP.h \
 ../core/M_DEQUE.h ../core/file_set.h ../core/M_LIST.h \
 ../core/copy_file.h channels.h ../core/server_config.h ../core/M_MAP.h \
 ../core/M_SET.h ../core/file_set.h chat_config.h ../core/M_SET.h \
 app_def.h update_cmd.h app_con.h ../core-web/web_connection.h \
 ../core/sid_t.h ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h chat_globals.h ../core-web/web_tools.h
	 c++ $(CFLAGS) ./admin_privs.cpp -o $(OBJDIR)/admin_privs.o

./objD/admin_settings.o: admin_settings.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core/copy_file.h \
 channels.h ../core/server_config.h ../core/M_SET.h ../core/file_set.h \
 chat_config.h app_def.h chat_msg.h chat_thread_event.h chat_stuff.h \
 app_con.h ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h \
 chat_globals.h global_state.h ../core-web/web_tools.h
	 c++ $(CFLAGS) ./admin_settings.cpp -o $(OBJDIR)/admin_settings.o

./objD/app_con.o: app_con.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core-web/web_server.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core-web/tcp_server.h ../core/m_var.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/errs.h ../core/st_stuff.h ../core/str_lib.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/mysql_extens.h ../core/_QUERY.h cutils.h \
 user.h chat_def.h levels.h ../core/oscar_buffer.h message.h S_id.h \
 ../core/DB_id.h CH_id.h chat_channel_data.h user_nick.h ../core/Double.h \
 user_status.h user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core/tcp_stats.h \
 ../core/server_config.h ../core/M_SET.h ../core/file_set.h app_server.h \
 app_def.h chat_globals.h ../core-web/web_tools.h ../core/copy_file.h \
 chat_config.h global_state.h channels.h
	 c++ $(CFLAGS) ./app_con.cpp -o $(OBJDIR)/app_con.o

./objD/app_server.o: app_server.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core-web/web_server.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core-web/tcp_server.h ../core/m_var.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/errs.h ../core/st_stuff.h ../core/str_lib.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/mysql_extens.h ../core/_QUERY.h cutils.h \
 user.h chat_def.h levels.h ../core/oscar_buffer.h message.h S_id.h \
 ../core/DB_id.h CH_id.h chat_channel_data.h user_nick.h ../core/Double.h \
 user_status.h user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core/tcp_stats.h \
 ../core/server_config.h ../core/M_SET.h ../core/file_set.h app_server.h \
 app_def.h ../core-web/tcp_sender.h ../core-web/web_tools.h version.h \
 user_credits.h irc_server_config.h chat_config.h notes.h \
 ../core-web/html_out.h channels.h irc_utils.h irc_server.h \
 ../core-web/tcp_server.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h update_cmd.h ignore_vec.h contact_vec.h \
 chat_globals.h admin.h chat_thread_event.h chat_stuff.h chat_msg.h \
 global_state.h ../core/copy_file.h
	 c++ $(CFLAGS) ./app_server.cpp -o $(OBJDIR)/app_server.o

./objD/c_conn.o: ../core-web/c_conn.cpp ../stdafx/stdafx.h ../core-web/c_conn.h \
 ../core/_mutex.h ../core/m_var.h ../core/_mutex.h ../core/PTR.h \
 ../core/errs.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core/lockctl.h ../core/tcp_stats.h ../core/mutex_inspector.h \
 ../core/str_lib.h ../core/Double.h ../core/oscar_buffer.h \
 ../core/st_stuff.h ../core/str_lib.h ../core-web/tcp_sender.h \
 ../core/oscar_buffer.h ../core/st_rsa.h
	 c++ $(CFLAGS) ../core-web/c_conn.cpp -o $(OBJDIR)/c_conn.o

./objD/channels.o: channels.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/PTR.h ../core/_mutex.h ../core/errs.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/mutex_inspector.h \
 ../core/mysql_extens.h ../core/_QUERY.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h S_id.h \
 ../core/DB_id.h CH_id.h chat_channel_data.h user_nick.h ../core/Double.h \
 user_status.h user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h \
 ../core/str_lib.h ../core/errs.h ../core/M_MAP.h channels.h \
 chat_config.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 update_cmd.h admin.h ../core/time_limit.h
	 c++ $(CFLAGS) ./channels.cpp -o $(OBJDIR)/channels.o

./objD/chat_colors.o: chat_colors.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h cutils.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h ../core/file_set.h \
 ../core/M_LIST.h chat_colors.h ../core/server_config.h ../core/M_MAP.h \
 ../core/M_SET.h ../core/file_set.h chat_config.h ../core/M_MAP.h \
 ../core/M_SET.h ../core/time_limit.h
	 c++ $(CFLAGS) ./chat_colors.cpp -o $(OBJDIR)/chat_colors.o

./objD/chat_config.o: chat_config.cpp ../stdafx/stdafx.h ../core/file_set.h \
 ../core/M_LIST.h ../core/_mutex.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/errs.h ../core/lockctl.h \
 ../core/oscar_buffer.h chat_config.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h \
 ../core/server_config.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/file_set.h ../core/str_lib.h ../core/Double.h message.h \
 ../core/_mutex.h ../core/st_stuff.h ../core/str_lib.h ../core/PTR.h \
 ../core/mutex_inspector.h user.h chat_def.h levels.h ../core/DB_id.h \
 CH_id.h S_id.h user_nick.h user_status.h user_state.h nick_vec.h \
 ../core/db_var.h ../core/PTR.h ../core/mysql_extens.h ../core/_QUERY.h \
 user_profile.h ../core-web/c_conn.h chat_channel_data.h cm_container.h \
 ../core/time_limit.h
	 c++ $(CFLAGS) ./chat_config.cpp -o $(OBJDIR)/chat_config.o

./objD/chat_globals.o: chat_globals.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/errs.h ../core-web/web_tools.h ../core-web/web_server_data.h \
 ../core/M_DEQUE.h channels.h irc_server_config.h ../core/db_config.h \
 ../core/M_SET.h ../core/db_config2.h notes.h ../core-web/html_out.h \
 contact_vec.h ignore_vec.h user_credits.h chat_config.h \
 ../core/server_config.h ../core/file_set.h
	 c++ $(CFLAGS) ./chat_globals.cpp -o $(OBJDIR)/chat_globals.o

./objD/chat_msg.o: chat_msg.cpp ../stdafx/stdafx.h ../core/PTR.h \
 ../core/_mutex.h ../core/errs.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/oscar_buffer.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/DB_id.h CH_id.h chat_msg.h user_nick.h \
 ../core/Double.h chat_colors.h cm_container.h cutils.h user.h \
 ../core/_mutex.h chat_def.h levels.h message.h ../core/st_stuff.h \
 ../core/str_lib.h S_id.h chat_channel_data.h user_status.h user_state.h \
 nick_vec.h ../core/db_var.h ../core/PTR.h ../core/mysql_extens.h \
 ../core/_QUERY.h user_profile.h ../core-web/c_conn.h chat_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/M_DEQUE.h chat_stuff.h ../core/threadable.h ../core/M_MAP.h
	 c++ $(CFLAGS) ./chat_msg.cpp -o $(OBJDIR)/chat_msg.o

./objD/chat_thread.o: chat_thread.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/DB_id.h ../core/oscar_buffer.h CH_id.h \
 S_id.h user_nick.h ../core/Double.h chat_msg.h ../core/M_DEQUE.h \
 user_status.h user_state.h levels.h chat_stuff.h chat_channel_data.h \
 ../core/threadable.h ../core/M_MAP.h message.h ../core/_mutex.h \
 ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 user.h chat_def.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h channels.h update_cmd.h cutils.h \
 ../core/server_config.h ../core/M_SET.h ../core/file_set.h \
 ../core/M_LIST.h chat_thread_event.h irc_utils.h irc_server.h \
 ../core-web/tcp_server.h ../core-web/c_conn.h \
 ../core-web/tcp_server_connection.h ../core-web/tcp_dialog_server.h \
 ../core-web/tcp_server.h ../core-web/tcp_server_connection.h \
 ../core/M_SET.h irc_server_config.h ../core/M_MAP.h chat_globals.h \
 ../core-web/html_out.h chat_config.h ../core/file_set.h global_state.h \
 contact_vec.h ignore_vec.h admin.h chat_colors.h
	 c++ $(CFLAGS) ./chat_thread.cpp -o $(OBJDIR)/chat_thread.o

./objD/chat_thread_2.o: chat_thread_2.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/DB_id.h ../core/oscar_buffer.h CH_id.h \
 S_id.h ../core/M_DEQUE.h user_status.h user_nick.h ../core/Double.h \
 user_state.h levels.h chat_stuff.h chat_channel_data.h chat_msg.h \
 ../core/threadable.h ../core/M_MAP.h message.h ../core/_mutex.h \
 ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 user.h chat_def.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h channels.h cutils.h ../core-web/web_tools.h \
 cm_container.h irc_server_config.h ../core/M_MAP.h ../core/M_SET.h \
 chat_globals.h chat_thread_event.h chat_config.h ../core/file_set.h \
 ../core/M_LIST.h
	 c++ $(CFLAGS) ./chat_thread_2.cpp -o $(OBJDIR)/chat_thread_2.o

./objD/contact_vec.o: contact_vec.cpp ../stdafx/stdafx.h ../core/db_var.h \
 ../core/str_lib.h ../core/errs.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/mysql_extens.h \
 ../core/_QUERY.h contact_vec.h ../core/DB_id.h user.h ../core/_mutex.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/PTR.h S_id.h CH_id.h chat_channel_data.h user_nick.h \
 ../core/Double.h user_status.h user_state.h nick_vec.h user_profile.h \
 ../core-web/c_conn.h ../core/mysql_extens.h
	 c++ $(CFLAGS) ./contact_vec.cpp -o $(OBJDIR)/contact_vec.o

./objD/copy_file_common.o: ../core/copy_file_common.cpp ../stdafx/stdafx.h \
 ../core/str_lib.h ../core/errs.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/m_var.h ../core/M_MAP.h \
 ../core/st_stuff.h ../core/copy_file.h ../core/wrappers.h \
 ../core/mutex_inspector.h ../core/lockctl.h
	 c++ $(CFLAGS) ../core/copy_file_common.cpp -o $(OBJDIR)/copy_file_common.o

./objD/core_main.o: ../core/core_main.cpp ../stdafx/stdafx.h \
 ../core/server_config.h ../core/_mutex.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/m_var.h ../core/file_set.h ../core/M_LIST.h ../core/errs.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h
	 c++ $(CFLAGS) ../core/core_main.cpp -o $(OBJDIR)/core_main.o

./objD/cutils.o: cutils.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h cutils.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/str_lib.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h chat_config.h chat_globals.h ../core/mysql_extens.h
	 c++ $(CFLAGS) ./cutils.cpp -o $(OBJDIR)/cutils.o

./objD/db_config.o: ../core/db_config.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/db_config.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/m_var.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h
	 c++ $(CFLAGS) ../core/db_config.cpp -o $(OBJDIR)/db_config.o

./objD/db_config2.o: ../core/db_config2.cpp ../stdafx/stdafx.h
	 c++ $(CFLAGS) ../core/db_config2.cpp -o $(OBJDIR)/db_config2.o

./objD/db_var.o: ../core/db_var.cpp ../stdafx/stdafx.h
	 c++ $(CFLAGS) ../core/db_var.cpp -o $(OBJDIR)/db_var.o

./objD/des_sid.o: ../core/des_sid.cpp ../stdafx/stdafx.h ../core/str_lib.h \
 ../core/errs.h ../core/m_var.h ../core/_mutex.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/st_stuff.h ../core/m_var.h \
 ../core/des_locl.h ../core/sid_t.h ../core/des_sid.h
	 c++ $(CFLAGS) ../core/des_sid.cpp -o $(OBJDIR)/des_sid.o

./objD/errs.o: ../core/errs.cpp ../stdafx/stdafx.h ../core/errs.h \
 ../core/str_lib.h ../core/m_var.h ../core/_mutex.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/m_var.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/st_stuff.h
	 c++ $(CFLAGS) ../core/errs.cpp -o $(OBJDIR)/errs.o

./objD/file_dump.o: file_dump.cpp ../stdafx/stdafx.h
	 c++ $(CFLAGS) ./file_dump.cpp -o $(OBJDIR)/file_dump.o

./objD/file_set.o: ../core/file_set.cpp ../stdafx/stdafx.h ../core/wrappers.h \
 ../core/file_set.h ../core/M_LIST.h ../core/_mutex.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/errs.h ../core/lockctl.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/st_stuff.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h
	 c++ $(CFLAGS) ../core/file_set.cpp -o $(OBJDIR)/file_set.o

./objD/file_set_init.o: ../core/file_set_init.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/errs.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/st_stuff.h \
 ../core/file_set.h ../core/M_LIST.h ../core/m_var.h \
 ../core/st_stream_str.h ../core/st_rsa.h ../core/copy_file.h \
 ../core/wrappers.h ../core/mutex_inspector.h ../core/lockctl.h \
 ../core/server_config.h ../core/M_MAP.h ../core/M_SET.h
	 c++ $(CFLAGS) ../core/file_set_init.cpp -o $(OBJDIR)/file_set_init.o

./objD/global_state.o: global_state.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/DB_id.h ../core/oscar_buffer.h \
 ../core/mutex_inspector.h CH_id.h user_status.h user_nick.h \
 ../core/Double.h user_state.h global_state.h
	 c++ $(CFLAGS) ./global_state.cpp -o $(OBJDIR)/global_state.o

./objD/html_out.o: ../core-web/html_out.cpp ../stdafx/stdafx.h ../core/PTR.h \
 ../core/_mutex.h ../core/errs.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core-web/html_out.h \
 ../core-web/web_tools.h ../core/m_var.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/str_lib.h ../core/Double.h ../core/oscar_buffer.h \
 ../core/oscar_buffer.h
	 c++ $(CFLAGS) ../core-web/html_out.cpp -o $(OBJDIR)/html_out.o

./objD/ignore_vec.o: ignore_vec.cpp ../stdafx/stdafx.h ../core/db_var.h \
 ../core/str_lib.h ../core/errs.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/mysql_extens.h \
 ../core/_QUERY.h ignore_vec.h ../core/DB_id.h user.h ../core/_mutex.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/PTR.h S_id.h CH_id.h chat_channel_data.h user_nick.h \
 ../core/Double.h user_status.h user_state.h nick_vec.h user_profile.h \
 ../core-web/c_conn.h ../core/mysql_extens.h
	 c++ $(CFLAGS) ./ignore_vec.cpp -o $(OBJDIR)/ignore_vec.o

./objD/irc_admin.o: irc_admin.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core/file_set.h ../core/M_LIST.h ../core-web/web_server_data.h \
 ../core/M_MAP.h channels.h irc_server_config.h irc_utils.h update_cmd.h \
 admin.h chat_globals.h app_def.h
	 c++ $(CFLAGS) ./irc_admin.cpp -o $(OBJDIR)/irc_admin.o

./objD/irc_login.o: irc_login.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core/file_set.h ../core/M_LIST.h ../core-web/web_server_data.h \
 ../core/M_MAP.h channels.h irc_server_config.h irc_utils.h update_cmd.h \
 contact_vec.h chat_thread_event.h chat_stuff.h chat_msg.h global_state.h \
 chat_config.h
	 c++ $(CFLAGS) ./irc_login.cpp -o $(OBJDIR)/irc_login.o

./objD/irc_server.o: irc_server.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core/file_set.h ../core/M_LIST.h ../core-web/web_server_data.h \
 ../core/M_MAP.h channels.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h ../core-web/tcp_server_data.h irc_server_config.h \
 irc_utils.h irc_session.h chat_thread_event.h chat_stuff.h chat_msg.h \
 update_cmd.h ../core/tcp_stats.h global_state.h ../core/des_sid.h \
 ../core/sid_t.h
	 c++ $(CFLAGS) ./irc_server.cpp -o $(OBJDIR)/irc_server.o

./objD/irc_server_config.o: irc_server_config.cpp ../stdafx/stdafx.h \
 ../core/file_set.h ../core/M_LIST.h ../core/_mutex.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/errs.h ../core/lockctl.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h irc_server_config.h ../core/M_MAP.h \
 ../core/M_SET.h cutils.h user.h ../core/_mutex.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/PTR.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h
	 c++ $(CFLAGS) ./irc_server_config.cpp -o $(OBJDIR)/irc_server_config.o

./objD/irc_tools.o: irc_tools.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core/file_set.h ../core/M_LIST.h ../core-web/web_server_data.h \
 ../core/M_MAP.h channels.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h version.h irc_server_config.h irc_utils.h \
 irc_session.h global_state.h chat_config.h
	 c++ $(CFLAGS) ./irc_tools.cpp -o $(OBJDIR)/irc_tools.o

./objD/irc_user.o: irc_user.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core/file_set.h ../core/M_LIST.h ../core-web/web_server_data.h \
 ../core/M_MAP.h channels.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h irc_server_config.h user_credits.h \
 ../core/thread_descr.h irc_utils.h ../core/tcp_stats.h \
 chat_thread_event.h chat_stuff.h chat_msg.h irc_session.h chat_globals.h \
 update_cmd.h global_state.h admin.h
	 c++ $(CFLAGS) ./irc_user.cpp -o $(OBJDIR)/irc_user.o

./objD/irc_user_cred.o: irc_user_cred.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core/file_set.h ../core/M_LIST.h ../core-web/web_server_data.h \
 ../core/M_MAP.h channels.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h irc_server_config.h user_credits.h \
 ../core/thread_descr.h irc_utils.h ../core/tcp_stats.h \
 chat_thread_event.h chat_stuff.h chat_msg.h irc_session.h chat_globals.h
	 c++ $(CFLAGS) ./irc_user_cred.cpp -o $(OBJDIR)/irc_user_cred.o

./objD/levels.o: levels.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h ../core-web/web_server.h \
 ../core-web/tcp_server.h ../core/threadable.h ../core/M_MAP.h \
 ../core-web/c_conn.h ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h \
 ../core/M_LIST.h ../core/errs.h ../core-web/web_tools.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core/server_config.h \
 ../core/M_SET.h ../core/file_set.h chat_config.h
	 c++ $(CFLAGS) ./levels.cpp -o $(OBJDIR)/levels.o

./objD/license.o: ../core/license.cpp ../stdafx/stdafx.h
	 c++ $(CFLAGS) ../core/license.cpp -o $(OBJDIR)/license.o

./objD/local_user_handle.o: local_user_handle.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h ../core-web/web_server.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h ../core-web/tcp_server.h \
 ../core/m_var.h ../core/threadable.h ../core/M_MAP.h \
 ../core-web/c_conn.h ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h \
 ../core/M_LIST.h ../core/errs.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h cutils.h user.h chat_def.h \
 levels.h ../core/oscar_buffer.h message.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core-web/web_server_data.h ../core/M_DEQUE.h \
 ../core/tcp_stats.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h app_def.h ../core-web/tcp_sender.h \
 ../core-web/web_tools.h version.h user_credits.h irc_server_config.h \
 chat_config.h channels.h irc_utils.h irc_server.h \
 ../core-web/tcp_server.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server_connection.h \
 update_cmd.h ignore_vec.h contact_vec.h notes.h ../core-web/html_out.h \
 global_state.h chat_thread_event.h chat_stuff.h chat_msg.h
	 c++ $(CFLAGS) ./local_user_handle.cpp -o $(OBJDIR)/local_user_handle.o

./objD/login.o: login.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core-web/web_server.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core-web/tcp_server.h ../core/m_var.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 chat_def.h cutils.h user.h levels.h ../core/oscar_buffer.h message.h \
 ../core/st_stuff.h ../core/str_lib.h ../core/Double.h \
 ../core/oscar_buffer.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core-web/web_server_data.h \
 ../core/M_DEQUE.h ../core-web/web_tools.h user_credits.h channels.h \
 ../core/server_config.h ../core/M_SET.h ../core/file_set.h chat_config.h \
 app_def.h update_cmd.h contact_vec.h chat_thread_event.h chat_stuff.h \
 chat_msg.h ../core/des_sid.h ../core/sid_t.h ../core-web/html_out.h \
 ../core/time_limit.h chat_globals.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h
	 c++ $(CFLAGS) ./login.cpp -o $(OBJDIR)/login.o

./objD/main.o: main.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_tools.h admin.h channels.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h app_def.h \
 chat_config.h ../core/M_MAP.h ../core/M_SET.h update_cmd.h \
 chat_thread_event.h ../core/M_DEQUE.h chat_stuff.h chat_msg.h \
 ../core/threadable.h chat_globals.h ignore_vec.h global_state.h
	 c++ $(CFLAGS) ./main.cpp -o $(OBJDIR)/main.o

./objD/make_user_info.o: make_user_info.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core-web/html_out.h chat_globals.h contact_vec.h update_cmd.h \
 user_credits.h ../core-web/web_tools.h chat_thread_event.h chat_stuff.h \
 chat_msg.h app_con.h ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/html_out.h ../core/mysql_extens.h app_def.h
	 c++ $(CFLAGS) ./make_user_info.cpp -o $(OBJDIR)/make_user_info.o

./objD/message.o: message.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/errs.h cutils.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/copy_file.h ../core/wrappers.h channels.h \
 ../core/server_config.h ../core/M_SET.h ../core/file_set.h chat_config.h \
 irc_utils.h irc_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core-web/tcp_dialog_server.h \
 ../core-web/tcp_server_connection.h ../core/M_DEQUE.h \
 irc_server_config.h update_cmd.h chat_msg.h cm_container.h \
 ../core/mysql_extens.h chat_colors.h global_state.h
	 c++ $(CFLAGS) ./message.cpp -o $(OBJDIR)/message.o

./objD/mutex_inspector.o: ../core/mutex_inspector.cpp ../stdafx/stdafx.h \
 ../core/errs.h ../core/str_lib.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/_mutex1.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/M_MAP.h
	 c++ $(CFLAGS) ../core/mutex_inspector.cpp -o $(OBJDIR)/mutex_inspector.o

./objD/mysql_extens.o: ../core/mysql_extens.cpp ../stdafx/stdafx.h \
 ../core/str_lib.h ../core/errs.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/mysql_extens.h \
 ../core/_QUERY.h ../core/mutex_inspector.h ../core/lockctl.h \
 ../core/file_set.h ../core/M_LIST.h ../core/m_var.h ../core/st_stuff.h \
 ../core/db_config.h ../core/M_MAP.h ../core/M_SET.h ../core/cMYSQL.h
	 c++ $(CFLAGS) ../core/mysql_extens.cpp -o $(OBJDIR)/mysql_extens.o

./objD/mysql_extens2.o: ../core/mysql_extens2.cpp ../stdafx/stdafx.h
	 c++ $(CFLAGS) ../core/mysql_extens2.cpp -o $(OBJDIR)/mysql_extens2.o

./objD/nick_vec.o: nick_vec.cpp ../stdafx/stdafx.h ../core/db_var.h \
 ../core/str_lib.h ../core/errs.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/mysql_extens.h \
 ../core/_QUERY.h nick_vec.h user_nick.h ../core/Double.h ../core/DB_id.h \
 user.h ../core/_mutex.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/PTR.h S_id.h CH_id.h \
 chat_channel_data.h user_status.h user_state.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core-web/web_tools.h
	 c++ $(CFLAGS) ./nick_vec.cpp -o $(OBJDIR)/nick_vec.o

./objD/notes.o: notes.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h ../core-web/web_server.h \
 ../core-web/tcp_server.h ../core/threadable.h ../core/M_MAP.h \
 ../core-web/c_conn.h ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h \
 ../core/M_LIST.h ../core/copy_file.h ../core/wrappers.h notes.h \
 ../core-web/html_out.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h chat_config.h app_con.h ../core-web/web_connection.h \
 ../core/sid_t.h ../core-web/tcp_server_connection.h \
 ../core-web/html_out.h app_def.h user_credits.h ../core/M_DEQUE.h \
 update_cmd.h ignore_vec.h ../core-web/web_tools.h chat_globals.h
	 c++ $(CFLAGS) ./notes.cpp -o $(OBJDIR)/notes.o

./objD/notes_containers.o: notes_containers.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h \
 user.h chat_def.h levels.h ../core/oscar_buffer.h message.h \
 ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/copy_file.h ../core/wrappers.h notes.h ../core-web/html_out.h \
 ../core/server_config.h ../core/M_SET.h ../core/file_set.h chat_config.h \
 ../core/time_limit.h
	 c++ $(CFLAGS) ./notes_containers.cpp -o $(OBJDIR)/notes_containers.o

./objD/oscar_buffer.o: ../core/oscar_buffer.cpp ../stdafx/stdafx.h \
 ../core/oscar_buffer.h ../core/str_lib.h ../core/errs.h ../core/m_var.h \
 ../core/_mutex.h ../core/Double.h ../core/mutex_inspector.h \
 ../core/lockctl.h
	 c++ $(CFLAGS) ../core/oscar_buffer.cpp -o $(OBJDIR)/oscar_buffer.o

./objD/oscar_client.o: ../core-web/oscar_client.cpp ../stdafx/stdafx.h \
 ../core/errs.h ../core/str_lib.h ../core/errs.h ../core/m_var.h \
 ../core/_mutex.h ../core/Double.h ../core/oscar_buffer.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core-web/oscar_client.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/_mutex.h
	 c++ $(CFLAGS) ../core-web/oscar_client.cpp -o $(OBJDIR)/oscar_client.o

./objD/other.o: other.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h cutils.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core-web/web_server.h \
 ../core-web/tcp_server.h ../core/threadable.h ../core/M_MAP.h \
 ../core-web/c_conn.h ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h \
 ../core/M_LIST.h ../core/copy_file.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h \
 ../core/tcp_stats.h chat_config.h user_credits.h ../core/M_DEQUE.h \
 ../core-web/tcp_oscar_dialog_server.h ../core-web/tcp_dialog_server.h \
 chat_globals.h app_def.h
	 c++ $(CFLAGS) ./other.cpp -o $(OBJDIR)/other.o

./objD/rijndael.o: ../core/rijndael.cpp ../core/rijndael.h
	 c++ $(CFLAGS) ../core/rijndael.cpp -o $(OBJDIR)/rijndael.o

./objD/server_config.o: ../core/server_config.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/server_config.h ../core/M_MAP.h \
 ../core/M_SET.h ../core/m_var.h ../core/file_set.h ../core/M_LIST.h \
 ../core/wrappers.h ../core/st_stuff.h
	 c++ $(CFLAGS) ../core/server_config.cpp -o $(OBJDIR)/server_config.o

./objD/st_FILE.o: ../core/st_FILE.cpp ../stdafx/stdafx.h ../core/st_stuff.h \
 ../core/errs.h ../core/str_lib.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/copy_file.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/wrappers.h
	 c++ $(CFLAGS) ../core/st_FILE.cpp -o $(OBJDIR)/st_FILE.o

./objD/st_rsa.o: ../core/st_rsa.cpp ../stdafx/stdafx.h ../core/st_stuff.h \
 ../core/errs.h ../core/str_lib.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/mutex_inspector.h \
 ../core/lockctl.h ../core/m_var.h ../core/st_rsa.h
	 c++ $(CFLAGS) ../core/st_rsa.cpp -o $(OBJDIR)/st_rsa.o

./objD/st_savecwd.o: ../core/st_savecwd.cpp ../stdafx/stdafx.h \
 ../core/st_stuff.h ../core/errs.h ../core/str_lib.h ../core/m_var.h \
 ../core/_mutex.h ../core/Double.h ../core/oscar_buffer.h \
 ../core/copy_file.h ../core/mutex_inspector.h ../core/lockctl.h
	 c++ $(CFLAGS) ../core/st_savecwd.cpp -o $(OBJDIR)/st_savecwd.o

./objD/st_stream_str.o: ../core/st_stream_str.cpp ../stdafx/stdafx.h \
 ../core/str_lib.h ../core/errs.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/st_stream_str.h \
 ../core/st_stuff.h
	 c++ $(CFLAGS) ../core/st_stream_str.cpp -o $(OBJDIR)/st_stream_str.o

./objD/st_stuff.o: ../core/st_stuff.cpp ../stdafx/stdafx.h ../core/st_stuff.h \
 ../core/errs.h ../core/str_lib.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/mutex_inspector.h \
 ../core/lockctl.h
	 c++ $(CFLAGS) ../core/st_stuff.cpp -o $(OBJDIR)/st_stuff.o

./objD/str_lib.o: ../core/str_lib.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/errs.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/mutex_inspector.h ../core/lockctl.h
	 c++ $(CFLAGS) ../core/str_lib.cpp -o $(OBJDIR)/str_lib.o

./objD/str_lib1.o: ../core/str_lib1.cpp ../stdafx/stdafx.h \
 ../core/oscar_buffer.h ../core/Double.h ../core/_mutex.h ../core/errs.h \
 ../core/str_lib.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core/lockctl.h
	 c++ $(CFLAGS) ../core/str_lib1.cpp -o $(OBJDIR)/str_lib1.o

./objD/str_lib_extra.o: ../core/str_lib_extra.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/errs.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/st_stuff.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/st_stream_str.h
	 c++ $(CFLAGS) ../core/str_lib_extra.cpp -o $(OBJDIR)/str_lib_extra.o

./objD/tcp_dialog_server.o: ../core-web/tcp_dialog_server.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h ../core/lockctl.h ../core-web/c_conn.h \
 ../core/m_var.h ../core/PTR.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/tcp_server_connection.h \
 ../core/oscar_buffer.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core-web/tcp_server_data.h ../core/M_MAP.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h
	 c++ $(CFLAGS) ../core-web/tcp_dialog_server.cpp -o $(OBJDIR)/tcp_dialog_server.o

./objD/tcp_oscar_dialog_server.o: ../core-web/tcp_oscar_dialog_server.cpp \
 ../stdafx/stdafx.h ../core/_mutex.h ../core/mutex_inspector.h \
 ../core/_mutex.h ../core/errs.h ../core/lockctl.h ../core/lockctl.h \
 ../core-web/tcp_oscar_dialog_server.h ../core-web/tcp_dialog_server.h \
 ../core-web/tcp_server.h ../core/m_var.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core-web/tcp_server_connection.h \
 ../core/oscar_buffer.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core/str_lib.h ../core/Double.h ../core/oscar_buffer.h
	 c++ $(CFLAGS) ../core-web/tcp_oscar_dialog_server.cpp -o $(OBJDIR)/tcp_oscar_dialog_server.o

./objD/tcp_sender.o: ../core-web/tcp_sender.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core-web/tcp_server_data.h ../core/M_DEQUE.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core/_mutex.h ../core/m_var.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/M_MAP.h ../core/file_set.h \
 ../core/M_LIST.h ../core/str_lib.h ../core/Double.h \
 ../core/oscar_buffer.h ../core-web/tcp_sender.h ../core/tcp_stats.h \
 ../core/M_SET.h ../core/threadable.h ../core/M_MAP.h
	 c++ $(CFLAGS) ../core-web/tcp_sender.cpp -o $(OBJDIR)/tcp_sender.o

./objD/tcp_server.o: ../core-web/tcp_server.cpp ../stdafx/stdafx.h \
 ../core-web/tcp_server_data.h ../core/M_DEQUE.h ../core/_mutex.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core/_mutex.h ../core/m_var.h ../core/PTR.h ../core/errs.h \
 ../core/m_var.h ../core/mutex_inspector.h ../core/lockctl.h \
 ../core/M_MAP.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core/mutex_inspector.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/tcp_stats.h
	 c++ $(CFLAGS) ../core-web/tcp_server.cpp -o $(OBJDIR)/tcp_server.o

./objD/tcp_server_connection.o: ../core-web/tcp_server_connection.cpp \
 ../stdafx/stdafx.h ../core-web/tcp_server_connection.h \
 ../core-web/c_conn.h ../core/_mutex.h ../core/m_var.h ../core/_mutex.h \
 ../core/PTR.h ../core/errs.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core/lockctl.h ../core/errs.h ../core/str_lib.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/mutex_inspector.h \
 ../core-web/tcp_sender.h
	 c++ $(CFLAGS) ../core-web/tcp_server_connection.cpp -o $(OBJDIR)/tcp_server_connection.o

./objD/tcp_stats.o: ../core/tcp_stats.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/m_var.h
	 c++ $(CFLAGS) ../core/tcp_stats.cpp -o $(OBJDIR)/tcp_stats.o

./objD/thread_info_report.o: ../core-web/thread_info_report.cpp \
 ../stdafx/stdafx.h ../core-web/tcp_server_connection.h \
 ../core-web/c_conn.h ../core/_mutex.h ../core/m_var.h ../core/_mutex.h \
 ../core/PTR.h ../core/errs.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core/lockctl.h ../core/errs.h ../core/str_lib.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/file_set.h ../core/M_LIST.h ../core/mutex_inspector.h \
 ../core/M_DEQUE.h ../core-web/tcp_server_data.h ../core/M_MAP.h \
 ../core/tcp_stats.h
	 c++ $(CFLAGS) ../core-web/thread_info_report.cpp -o $(OBJDIR)/thread_info_report.o

./objD/threadable.o: ../core/threadable.cpp ../stdafx/stdafx.h \
 ../core/threadable.h ../core/M_MAP.h ../core/_mutex.h ../core/errs.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h
	 c++ $(CFLAGS) ../core/threadable.cpp -o $(OBJDIR)/threadable.o

./objD/u_chat.o: u_chat.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 ../core-web/web_tools.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_server_data.h ../core/M_MAP.h ../core/M_DEQUE.h \
 ../core-web/tcp_sender.h channels.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h chat_config.h \
 ../core/M_SET.h irc_server_config.h irc_utils.h irc_server.h \
 ../core-web/tcp_server.h ../core/threadable.h ../core-web/c_conn.h \
 ../core-web/tcp_server_connection.h ../core-web/tcp_dialog_server.h \
 ../core-web/tcp_server.h ../core-web/tcp_server_connection.h \
 update_cmd.h cm_container.h ignore_vec.h contact_vec.h notes.h \
 ../core-web/html_out.h global_state.h ../core/copy_file.h
	 c++ $(CFLAGS) ./u_chat.cpp -o $(OBJDIR)/u_chat.o

./objD/update_cmd.o: update_cmd.cpp ../stdafx/stdafx.h ../core/M_DEQUE.h \
 ../core/_mutex.h ../core/oscar_buffer.h ../core/DB_id.h \
 ../core/oscar_buffer.h ../core/errs.h ../core/mutex_inspector.h \
 ../core/lockctl.h ../core/mutex_inspector.h update_cmd.h CH_id.h \
 ../core/mysql_extens.h ../core/_QUERY.h user.h ../core/_mutex.h \
 chat_def.h levels.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/PTR.h ../core/m_var.h S_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h \
 chat_thread_event.h chat_stuff.h chat_msg.h ../core/threadable.h \
 ../core/M_MAP.h ignore_vec.h channels.h ../core/copy_file.h cutils.h \
 user_credits.h notes.h ../core-web/html_out.h contact_vec.h admin.h \
 ../core/time_limit.h
	 c++ $(CFLAGS) ./update_cmd.cpp -o $(OBJDIR)/update_cmd.o

./objD/url_change_nick.o: url_change_nick.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_tools.h admin.h channels.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h app_def.h \
 chat_config.h ../core/M_MAP.h ../core/M_SET.h update_cmd.h \
 chat_thread_event.h ../core/M_DEQUE.h chat_stuff.h chat_msg.h \
 ../core/threadable.h chat_globals.h ignore_vec.h global_state.h
	 c++ $(CFLAGS) ./url_change_nick.cpp -o $(OBJDIR)/url_change_nick.o

./objD/url_chat_messages.o: url_chat_messages.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_tools.h admin.h channels.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h app_def.h \
 chat_config.h ../core/M_MAP.h ../core/M_SET.h update_cmd.h \
 chat_thread_event.h ../core/M_DEQUE.h chat_stuff.h chat_msg.h \
 ../core/threadable.h chat_globals.h ignore_vec.h global_state.h
	 c++ $(CFLAGS) ./url_chat_messages.cpp -o $(OBJDIR)/url_chat_messages.o

./objD/url_chat_sendmessage.o: url_chat_sendmessage.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_tools.h admin.h channels.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h app_def.h \
 chat_config.h ../core/M_MAP.h ../core/M_SET.h update_cmd.h \
 chat_thread_event.h ../core/M_DEQUE.h chat_stuff.h chat_msg.h \
 ../core/threadable.h chat_globals.h ignore_vec.h global_state.h
	 c++ $(CFLAGS) ./url_chat_sendmessage.cpp -o $(OBJDIR)/url_chat_sendmessage.o

./objD/url_ignore_user.o: url_ignore_user.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_tools.h admin.h channels.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h app_def.h \
 chat_config.h ../core/M_MAP.h ../core/M_SET.h update_cmd.h \
 chat_thread_event.h ../core/M_DEQUE.h chat_stuff.h chat_msg.h \
 ../core/threadable.h chat_globals.h ignore_vec.h global_state.h
	 c++ $(CFLAGS) ./url_ignore_user.cpp -o $(OBJDIR)/url_ignore_user.o

./objD/url_new_nick.o: url_new_nick.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core-web/web_tools.h \
 channels.h ../core/server_config.h ../core/M_SET.h ../core/file_set.h \
 app_def.h chat_config.h irc_server_config.h update_cmd.h chat_globals.h \
 user_credits.h app_con.h ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h
	 c++ $(CFLAGS) ./url_new_nick.cpp -o $(OBJDIR)/url_new_nick.o

./objD/url_set_user_status.o: url_set_user_status.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_tools.h admin.h channels.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h app_def.h \
 chat_config.h ../core/M_MAP.h ../core/M_SET.h update_cmd.h \
 chat_thread_event.h ../core/M_DEQUE.h chat_stuff.h chat_msg.h \
 ../core/threadable.h chat_globals.h ignore_vec.h global_state.h
	 c++ $(CFLAGS) ./url_set_user_status.cpp -o $(OBJDIR)/url_set_user_status.o

./objD/user.o: user.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 ../core-web/web_tools.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_server_data.h ../core/M_MAP.h ../core/M_DEQUE.h \
 channels.h ../core/server_config.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/file_set.h chat_config.h ../core/M_SET.h irc_server_config.h \
 irc_utils.h irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core-web/tcp_sender.h \
 update_cmd.h chat_msg.h cm_container.h chat_thread_event.h chat_stuff.h \
 ignore_vec.h contact_vec.h chat_globals.h global_state.h user_credits.h \
 admin.h ../core/M_HASHMAP.h chat_colors.h
	 c++ $(CFLAGS) ./user.cpp -o $(OBJDIR)/user.o

./objD/user_credits.o: user_credits.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 ../core/_mutex.h chat_def.h levels.h ../core/oscar_buffer.h message.h \
 ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/copy_file.h user_credits.h ../core/M_DEQUE.h \
 ../core/server_config.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/file_set.h ../core/M_LIST.h update_cmd.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h chat_config.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/file_set.h
	 c++ $(CFLAGS) ./user_credits.cpp -o $(OBJDIR)/user_credits.o

./objD/user_nick.o: user_nick.cpp ../stdafx/stdafx.h ../core/oscar_buffer.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/DB_id.h ../core/oscar_buffer.h \
 ../core/mutex_inspector.h user_nick.h ../core/Double.h user.h \
 ../core/_mutex.h chat_def.h levels.h message.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h ../core/PTR.h \
 ../core/m_var.h S_id.h CH_id.h chat_channel_data.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h
	 c++ $(CFLAGS) ./user_nick.cpp -o $(OBJDIR)/user_nick.o

./objD/user_profile.o: user_profile.cpp ../stdafx/stdafx.h user.h \
 ../core/_mutex.h chat_def.h levels.h ../core/oscar_buffer.h message.h \
 ../core/st_stuff.h ../core/errs.h ../core/str_lib.h ../core/m_var.h \
 ../core/_mutex.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h ../core/lockctl.h S_id.h \
 ../core/DB_id.h CH_id.h chat_channel_data.h user_nick.h ../core/Double.h \
 user_status.h user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h cm_container.h notes.h \
 ../core-web/html_out.h
	 c++ $(CFLAGS) ./user_profile.cpp -o $(OBJDIR)/user_profile.o

./objD/user_state.o: user_state.cpp ../stdafx/stdafx.h user.h ../core/_mutex.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/errs.h ../core/str_lib.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h S_id.h ../core/DB_id.h \
 CH_id.h chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h
	 c++ $(CFLAGS) ./user_state.cpp -o $(OBJDIR)/user_state.o

./objD/web_adminfo.o: ../core-web/web_adminfo.cpp ../stdafx/stdafx.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core/_mutex.h ../core/m_var.h ../core/_mutex.h ../core/PTR.h \
 ../core/errs.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core/lockctl.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/file_set.h ../core/M_LIST.h ../core/errs.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/des_sid.h ../core/sid_t.h \
 ../core/mutex_inspector.h ../core/M_DEQUE.h \
 ../core-web/tcp_server_data.h ../core-web/web_connection.h \
 ../core/sid_t.h ../core-web/html_out.h ../core-web/web_server_data.h \
 ../core-web/c_conn.h ../core/tcp_stats.h
	 c++ $(CFLAGS) ../core-web/web_adminfo.cpp -o $(OBJDIR)/web_adminfo.o

./objD/web_cache.o: ../core-web/web_cache.cpp ../stdafx/stdafx.h
	 c++ $(CFLAGS) ../core-web/web_cache.cpp -o $(OBJDIR)/web_cache.o

./objD/web_connection.o: ../core-web/web_connection.cpp ../stdafx/stdafx.h \
 ../core/sid_t.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h ../core-web/web_server.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h ../core-web/tcp_server.h \
 ../core/m_var.h ../core/threadable.h ../core/M_MAP.h \
 ../core-web/c_conn.h ../core/_mutex.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/file_set.h ../core/M_LIST.h ../core/des_sid.h ../core/sid_t.h \
 ../core/str_lib.h ../core/Double.h ../core/oscar_buffer.h \
 ../core-web/web_connection.h ../core-web/tcp_server_connection.h \
 ../core-web/html_out.h ../core-web/web_tools.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core-web/c_conn.h \
 ../core/st_stuff.h ../core/str_lib.h ../core/server_config.h \
 ../core/M_SET.h ../core/file_set.h ../core/oscar_buffer.h
	 c++ $(CFLAGS) ../core-web/web_connection.cpp -o $(OBJDIR)/web_connection.o

./objD/web_connection_ptcp.o: ../core-web/web_connection_ptcp.cpp \
 ../stdafx/stdafx.h ../core/sid_t.h ../core/mutex_inspector.h \
 ../core/_mutex.h ../core/errs.h ../core/lockctl.h \
 ../core-web/web_server.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core-web/tcp_server.h ../core/m_var.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/_mutex.h ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h \
 ../core/M_LIST.h ../core/des_sid.h ../core/sid_t.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h ../core-web/web_connection.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h \
 ../core-web/web_tools.h ../core-web/web_server_data.h ../core/M_DEQUE.h \
 ../core-web/c_conn.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/server_config.h ../core/M_SET.h ../core/file_set.h \
 ../core/thread_descr.h
	 c++ $(CFLAGS) ../core-web/web_connection_ptcp.cpp -o $(OBJDIR)/web_connection_ptcp.o

./objD/web_server.o: ../core-web/web_server.cpp ../stdafx/stdafx.h \
 ../core-web/web_server.h ../core/PTR.h ../core/_mutex.h ../core/errs.h \
 ../core/m_var.h ../core/mutex_inspector.h ../core/lockctl.h \
 ../core-web/tcp_server.h ../core/m_var.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core/_mutex.h ../core/M_MAP.h \
 ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core-web/c_conn.h \
 ../core/mutex_inspector.h ../core-web/tcp_server_data.h \
 ../core-web/tcp_server_connection.h ../core-web/web_connection.h \
 ../core/sid_t.h ../core-web/html_out.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h ../core-web/tcp_sender.h
	 c++ $(CFLAGS) ../core-web/web_server.cpp -o $(OBJDIR)/web_server.o

./objD/web_tools.o: ../core-web/web_tools.cpp ../stdafx/stdafx.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core/_mutex.h ../core/m_var.h ../core/_mutex.h ../core/PTR.h \
 ../core/errs.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core/lockctl.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/file_set.h ../core/M_LIST.h ../core/errs.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/st_stuff.h \
 ../core/str_lib.h ../core-web/web_tools.h ../core/sid_t.h \
 ../core/des_sid.h ../core/sid_t.h ../core/server_config.h \
 ../core/M_SET.h ../core/file_set.h ../core/mutex_inspector.h
	 c++ $(CFLAGS) ../core-web/web_tools.cpp -o $(OBJDIR)/web_tools.o

./objD/wrappers.o: ../core/wrappers.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/copy_file.h ../core/wrappers.h \
 ../core/tcp_stats.h
	 c++ $(CFLAGS) ../core/wrappers.cpp -o $(OBJDIR)/wrappers.o

release: libchatR.a CS_tusa.release.exe 
CS_tusa.release.exe: libchatR.a  $(ROBJDIR)/CS_tusa.o
		c++ $(ROBJDIR)/CS_tusa.o -o CS_tusa.release.exe libchatR.a  $(RLIBS)


libchatR.a: \
	$(ROBJDIR)/Double.o \
	$(ROBJDIR)/PTR.o \
	$(ROBJDIR)/_QUERY.o \
	$(ROBJDIR)/__main.o \
	$(ROBJDIR)/_mutex.o \
	$(ROBJDIR)/_mutex1.o \
	$(ROBJDIR)/admin.o \
	$(ROBJDIR)/admin_ban.o \
	$(ROBJDIR)/admin_old_ban.o \
	$(ROBJDIR)/admin_other.o \
	$(ROBJDIR)/admin_privs.o \
	$(ROBJDIR)/admin_settings.o \
	$(ROBJDIR)/app_con.o \
	$(ROBJDIR)/app_server.o \
	$(ROBJDIR)/c_conn.o \
	$(ROBJDIR)/channels.o \
	$(ROBJDIR)/chat_colors.o \
	$(ROBJDIR)/chat_config.o \
	$(ROBJDIR)/chat_globals.o \
	$(ROBJDIR)/chat_msg.o \
	$(ROBJDIR)/chat_thread.o \
	$(ROBJDIR)/chat_thread_2.o \
	$(ROBJDIR)/contact_vec.o \
	$(ROBJDIR)/copy_file_common.o \
	$(ROBJDIR)/core_main.o \
	$(ROBJDIR)/cutils.o \
	$(ROBJDIR)/db_config.o \
	$(ROBJDIR)/db_config2.o \
	$(ROBJDIR)/db_var.o \
	$(ROBJDIR)/des_sid.o \
	$(ROBJDIR)/errs.o \
	$(ROBJDIR)/file_dump.o \
	$(ROBJDIR)/file_set.o \
	$(ROBJDIR)/file_set_init.o \
	$(ROBJDIR)/global_state.o \
	$(ROBJDIR)/html_out.o \
	$(ROBJDIR)/ignore_vec.o \
	$(ROBJDIR)/irc_admin.o \
	$(ROBJDIR)/irc_login.o \
	$(ROBJDIR)/irc_server.o \
	$(ROBJDIR)/irc_server_config.o \
	$(ROBJDIR)/irc_tools.o \
	$(ROBJDIR)/irc_user.o \
	$(ROBJDIR)/irc_user_cred.o \
	$(ROBJDIR)/levels.o \
	$(ROBJDIR)/license.o \
	$(ROBJDIR)/local_user_handle.o \
	$(ROBJDIR)/login.o \
	$(ROBJDIR)/main.o \
	$(ROBJDIR)/make_user_info.o \
	$(ROBJDIR)/message.o \
	$(ROBJDIR)/mutex_inspector.o \
	$(ROBJDIR)/mysql_extens.o \
	$(ROBJDIR)/mysql_extens2.o \
	$(ROBJDIR)/nick_vec.o \
	$(ROBJDIR)/notes.o \
	$(ROBJDIR)/notes_containers.o \
	$(ROBJDIR)/oscar_buffer.o \
	$(ROBJDIR)/oscar_client.o \
	$(ROBJDIR)/other.o \
	$(ROBJDIR)/rijndael.o \
	$(ROBJDIR)/server_config.o \
	$(ROBJDIR)/st_FILE.o \
	$(ROBJDIR)/st_rsa.o \
	$(ROBJDIR)/st_savecwd.o \
	$(ROBJDIR)/st_stream_str.o \
	$(ROBJDIR)/st_stuff.o \
	$(ROBJDIR)/str_lib.o \
	$(ROBJDIR)/str_lib1.o \
	$(ROBJDIR)/str_lib_extra.o \
	$(ROBJDIR)/tcp_dialog_server.o \
	$(ROBJDIR)/tcp_oscar_dialog_server.o \
	$(ROBJDIR)/tcp_sender.o \
	$(ROBJDIR)/tcp_server.o \
	$(ROBJDIR)/tcp_server_connection.o \
	$(ROBJDIR)/tcp_stats.o \
	$(ROBJDIR)/thread_info_report.o \
	$(ROBJDIR)/threadable.o \
	$(ROBJDIR)/u_chat.o \
	$(ROBJDIR)/update_cmd.o \
	$(ROBJDIR)/url_change_nick.o \
	$(ROBJDIR)/url_chat_messages.o \
	$(ROBJDIR)/url_chat_sendmessage.o \
	$(ROBJDIR)/url_ignore_user.o \
	$(ROBJDIR)/url_new_nick.o \
	$(ROBJDIR)/url_set_user_status.o \
	$(ROBJDIR)/user.o \
	$(ROBJDIR)/user_credits.o \
	$(ROBJDIR)/user_nick.o \
	$(ROBJDIR)/user_profile.o \
	$(ROBJDIR)/user_state.o \
	$(ROBJDIR)/web_adminfo.o \
	$(ROBJDIR)/web_cache.o \
	$(ROBJDIR)/web_connection.o \
	$(ROBJDIR)/web_connection_ptcp.o \
	$(ROBJDIR)/web_server.o \
	$(ROBJDIR)/web_tools.o \
	$(ROBJDIR)/wrappers.o 
		 ar -r libchatR.a $(ROBJDIR)/Double.o $(ROBJDIR)/PTR.o $(ROBJDIR)/_QUERY.o $(ROBJDIR)/__main.o $(ROBJDIR)/_mutex.o $(ROBJDIR)/_mutex1.o $(ROBJDIR)/admin.o $(ROBJDIR)/admin_ban.o $(ROBJDIR)/admin_old_ban.o $(ROBJDIR)/admin_other.o $(ROBJDIR)/admin_privs.o $(ROBJDIR)/admin_settings.o $(ROBJDIR)/app_con.o $(ROBJDIR)/app_server.o $(ROBJDIR)/c_conn.o $(ROBJDIR)/channels.o $(ROBJDIR)/chat_colors.o $(ROBJDIR)/chat_config.o $(ROBJDIR)/chat_globals.o $(ROBJDIR)/chat_msg.o $(ROBJDIR)/chat_thread.o $(ROBJDIR)/chat_thread_2.o $(ROBJDIR)/contact_vec.o $(ROBJDIR)/copy_file_common.o $(ROBJDIR)/core_main.o $(ROBJDIR)/cutils.o $(ROBJDIR)/db_config.o $(ROBJDIR)/db_config2.o $(ROBJDIR)/db_var.o $(ROBJDIR)/des_sid.o $(ROBJDIR)/errs.o $(ROBJDIR)/file_dump.o $(ROBJDIR)/file_set.o $(ROBJDIR)/file_set_init.o $(ROBJDIR)/global_state.o $(ROBJDIR)/html_out.o $(ROBJDIR)/ignore_vec.o $(ROBJDIR)/irc_admin.o $(ROBJDIR)/irc_login.o $(ROBJDIR)/irc_server.o $(ROBJDIR)/irc_server_config.o $(ROBJDIR)/irc_tools.o $(ROBJDIR)/irc_user.o $(ROBJDIR)/irc_user_cred.o $(ROBJDIR)/levels.o $(ROBJDIR)/license.o $(ROBJDIR)/local_user_handle.o $(ROBJDIR)/login.o $(ROBJDIR)/main.o $(ROBJDIR)/make_user_info.o $(ROBJDIR)/message.o $(ROBJDIR)/mutex_inspector.o $(ROBJDIR)/mysql_extens.o $(ROBJDIR)/mysql_extens2.o $(ROBJDIR)/nick_vec.o $(ROBJDIR)/notes.o $(ROBJDIR)/notes_containers.o $(ROBJDIR)/oscar_buffer.o $(ROBJDIR)/oscar_client.o $(ROBJDIR)/other.o $(ROBJDIR)/rijndael.o $(ROBJDIR)/server_config.o $(ROBJDIR)/st_FILE.o $(ROBJDIR)/st_rsa.o $(ROBJDIR)/st_savecwd.o $(ROBJDIR)/st_stream_str.o $(ROBJDIR)/st_stuff.o $(ROBJDIR)/str_lib.o $(ROBJDIR)/str_lib1.o $(ROBJDIR)/str_lib_extra.o $(ROBJDIR)/tcp_dialog_server.o $(ROBJDIR)/tcp_oscar_dialog_server.o $(ROBJDIR)/tcp_sender.o $(ROBJDIR)/tcp_server.o $(ROBJDIR)/tcp_server_connection.o $(ROBJDIR)/tcp_stats.o $(ROBJDIR)/thread_info_report.o $(ROBJDIR)/threadable.o $(ROBJDIR)/u_chat.o $(ROBJDIR)/update_cmd.o $(ROBJDIR)/url_change_nick.o $(ROBJDIR)/url_chat_messages.o $(ROBJDIR)/url_chat_sendmessage.o $(ROBJDIR)/url_ignore_user.o $(ROBJDIR)/url_new_nick.o $(ROBJDIR)/url_set_user_status.o $(ROBJDIR)/user.o $(ROBJDIR)/user_credits.o $(ROBJDIR)/user_nick.o $(ROBJDIR)/user_profile.o $(ROBJDIR)/user_state.o $(ROBJDIR)/web_adminfo.o $(ROBJDIR)/web_cache.o $(ROBJDIR)/web_connection.o $(ROBJDIR)/web_connection_ptcp.o $(ROBJDIR)/web_server.o $(ROBJDIR)/web_tools.o $(ROBJDIR)/wrappers.o 

./objR/CS_tusa.o: CS_tusa.cpp ../stdafx/stdafx.h ../core/file_set.h \
 ../core/M_LIST.h ../core/_mutex.h ../core/m_var.h ../core/PTR.h \
 ../core/errs.h ../core/mutex_inspector.h ../core/lockctl.h \
 ../core/mutex_inspector.h chat_def.h ../core-web/web_server_data.h \
 ../core/M_MAP.h ../core/M_DEQUE.h ../core/m_var.h ../core-web/c_conn.h \
 ../core/_mutex.h ../core/mysql_extens.h ../core/_QUERY.h user.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h cutils.h \
 ../core-web/tcp_server_data.h ../core-web/tcp_server_connection.h \
 ../core-web/c_conn.h app_server.h ../core-web/web_server.h \
 ../core-web/tcp_server.h ../core/threadable.h ../core/M_MAP.h \
 ../core/M_SET.h app_def.h version.h irc_server.h \
 ../core-web/tcp_server.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h irc_server_config.h contact_vec.h \
 ignore_vec.h channels.h notes.h ../core-web/html_out.h user_credits.h \
 chat_thread_event.h chat_stuff.h chat_msg.h chat_config.h global_state.h \
 admin.h ../core/server_config.h ../core/M_SET.h ../core/file_set.h \
 ../core/db_config.h ../core-web/tcp_sender.h
	 c++ $(RCFLAGS) ./CS_tusa.cpp -o $(ROBJDIR)/CS_tusa.o

./objR/Double.o: ../core/Double.cpp ../stdafx/stdafx.h ../core/oscar_buffer.h \
 ../core/Double.h ../core/str_lib.h ../core/errs.h ../core/m_var.h \
 ../core/_mutex.h
	 c++ $(RCFLAGS) ../core/Double.cpp -o $(ROBJDIR)/Double.o

./objR/PTR.o: ../core/PTR.cpp ../stdafx/stdafx.h ../core/PTR.h ../core/_mutex.h \
 ../core/errs.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core/lockctl.h
	 c++ $(RCFLAGS) ../core/PTR.cpp -o $(ROBJDIR)/PTR.o

./objR/_QUERY.o: ../core/_QUERY.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/_QUERY.h ../core/mysql_extens.h ../core/str_lib.h ../core/errs.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h \
 ../core/mutex_inspector.h ../core/lockctl.h
	 c++ $(RCFLAGS) ../core/_QUERY.cpp -o $(ROBJDIR)/_QUERY.o

./objR/__main.o: ../core/__main.cpp ../stdafx/stdafx.h
	 c++ $(RCFLAGS) ../core/__main.cpp -o $(ROBJDIR)/__main.o

./objR/_mutex.o: ../core/_mutex.cpp ../stdafx/stdafx.h ../core/errs.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/lockctl.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h
	 c++ $(RCFLAGS) ../core/_mutex.cpp -o $(ROBJDIR)/_mutex.o

./objR/_mutex1.o: ../core/_mutex1.cpp ../stdafx/stdafx.h ../core/errs.h \
 ../core/_mutex.h ../core/_mutex1.h ../core/mutex_inspector.h \
 ../core/lockctl.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h
	 c++ $(RCFLAGS) ../core/_mutex1.cpp -o $(ROBJDIR)/_mutex1.o

./objR/admin.o: admin.cpp ../stdafx/stdafx.h ../core/mutex_inspector.h \
 ../core/_mutex.h ../core/errs.h ../core/lockctl.h ../core/mysql_extens.h \
 ../core/_QUERY.h user.h ../core/_mutex.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h channels.h ../core/server_config.h ../core/M_MAP.h \
 ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h app_def.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h ../core-web/web_tools.h update_cmd.h
	 c++ $(RCFLAGS) ./admin.cpp -o $(ROBJDIR)/admin.o

./objR/admin_ban.o: admin_ban.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server_data.h ../core/M_MAP.h \
 ../core/M_DEQUE.h ../core/file_set.h ../core/M_LIST.h \
 ../core/copy_file.h channels.h ../core/server_config.h ../core/M_MAP.h \
 ../core/M_SET.h ../core/file_set.h app_def.h admin.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h chat_globals.h update_cmd.h \
 ../core-web/web_tools.h global_state.h chat_config.h ../core/M_SET.h
	 c++ $(RCFLAGS) ./admin_ban.cpp -o $(ROBJDIR)/admin_ban.o

./objR/admin_old_ban.o: admin_old_ban.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 app_con.h ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core/copy_file.h \
 admin.h channels.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h app_def.h
	 c++ $(RCFLAGS) ./admin_old_ban.cpp -o $(ROBJDIR)/admin_old_ban.o

./objR/admin_other.o: admin_other.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core/copy_file.h \
 channels.h ../core/server_config.h ../core/M_SET.h ../core/file_set.h \
 chat_config.h app_def.h chat_thread_event.h chat_stuff.h chat_msg.h \
 user_credits.h update_cmd.h ../core-web/web_tools.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h \
 chat_globals.h
	 c++ $(RCFLAGS) ./admin_other.cpp -o $(ROBJDIR)/admin_other.o

./objR/admin_privs.o: admin_privs.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server_data.h ../core/M_MAP.h \
 ../core/M_DEQUE.h ../core/file_set.h ../core/M_LIST.h \
 ../core/copy_file.h channels.h ../core/server_config.h ../core/M_MAP.h \
 ../core/M_SET.h ../core/file_set.h chat_config.h ../core/M_SET.h \
 app_def.h update_cmd.h app_con.h ../core-web/web_connection.h \
 ../core/sid_t.h ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h chat_globals.h ../core-web/web_tools.h
	 c++ $(RCFLAGS) ./admin_privs.cpp -o $(ROBJDIR)/admin_privs.o

./objR/admin_settings.o: admin_settings.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core/copy_file.h \
 channels.h ../core/server_config.h ../core/M_SET.h ../core/file_set.h \
 chat_config.h app_def.h chat_msg.h chat_thread_event.h chat_stuff.h \
 app_con.h ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h \
 chat_globals.h global_state.h ../core-web/web_tools.h
	 c++ $(RCFLAGS) ./admin_settings.cpp -o $(ROBJDIR)/admin_settings.o

./objR/app_con.o: app_con.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core-web/web_server.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core-web/tcp_server.h ../core/m_var.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/errs.h ../core/st_stuff.h ../core/str_lib.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/mysql_extens.h ../core/_QUERY.h cutils.h \
 user.h chat_def.h levels.h ../core/oscar_buffer.h message.h S_id.h \
 ../core/DB_id.h CH_id.h chat_channel_data.h user_nick.h ../core/Double.h \
 user_status.h user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core/tcp_stats.h \
 ../core/server_config.h ../core/M_SET.h ../core/file_set.h app_server.h \
 app_def.h chat_globals.h ../core-web/web_tools.h ../core/copy_file.h \
 chat_config.h global_state.h channels.h
	 c++ $(RCFLAGS) ./app_con.cpp -o $(ROBJDIR)/app_con.o

./objR/app_server.o: app_server.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core-web/web_server.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core-web/tcp_server.h ../core/m_var.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/errs.h ../core/st_stuff.h ../core/str_lib.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/mysql_extens.h ../core/_QUERY.h cutils.h \
 user.h chat_def.h levels.h ../core/oscar_buffer.h message.h S_id.h \
 ../core/DB_id.h CH_id.h chat_channel_data.h user_nick.h ../core/Double.h \
 user_status.h user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core/tcp_stats.h \
 ../core/server_config.h ../core/M_SET.h ../core/file_set.h app_server.h \
 app_def.h ../core-web/tcp_sender.h ../core-web/web_tools.h version.h \
 user_credits.h irc_server_config.h chat_config.h notes.h \
 ../core-web/html_out.h channels.h irc_utils.h irc_server.h \
 ../core-web/tcp_server.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h update_cmd.h ignore_vec.h contact_vec.h \
 chat_globals.h admin.h chat_thread_event.h chat_stuff.h chat_msg.h \
 global_state.h ../core/copy_file.h
	 c++ $(RCFLAGS) ./app_server.cpp -o $(ROBJDIR)/app_server.o

./objR/c_conn.o: ../core-web/c_conn.cpp ../stdafx/stdafx.h ../core-web/c_conn.h \
 ../core/_mutex.h ../core/m_var.h ../core/_mutex.h ../core/PTR.h \
 ../core/errs.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core/lockctl.h ../core/tcp_stats.h ../core/mutex_inspector.h \
 ../core/str_lib.h ../core/Double.h ../core/oscar_buffer.h \
 ../core/st_stuff.h ../core/str_lib.h ../core-web/tcp_sender.h \
 ../core/oscar_buffer.h ../core/st_rsa.h
	 c++ $(RCFLAGS) ../core-web/c_conn.cpp -o $(ROBJDIR)/c_conn.o

./objR/channels.o: channels.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/PTR.h ../core/_mutex.h ../core/errs.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/mutex_inspector.h \
 ../core/mysql_extens.h ../core/_QUERY.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h S_id.h \
 ../core/DB_id.h CH_id.h chat_channel_data.h user_nick.h ../core/Double.h \
 user_status.h user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h \
 ../core/str_lib.h ../core/errs.h ../core/M_MAP.h channels.h \
 chat_config.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 update_cmd.h admin.h ../core/time_limit.h
	 c++ $(RCFLAGS) ./channels.cpp -o $(ROBJDIR)/channels.o

./objR/chat_colors.o: chat_colors.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h cutils.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h ../core/file_set.h \
 ../core/M_LIST.h chat_colors.h ../core/server_config.h ../core/M_MAP.h \
 ../core/M_SET.h ../core/file_set.h chat_config.h ../core/M_MAP.h \
 ../core/M_SET.h ../core/time_limit.h
	 c++ $(RCFLAGS) ./chat_colors.cpp -o $(ROBJDIR)/chat_colors.o

./objR/chat_config.o: chat_config.cpp ../stdafx/stdafx.h ../core/file_set.h \
 ../core/M_LIST.h ../core/_mutex.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/errs.h ../core/lockctl.h \
 ../core/oscar_buffer.h chat_config.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h \
 ../core/server_config.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/file_set.h ../core/str_lib.h ../core/Double.h message.h \
 ../core/_mutex.h ../core/st_stuff.h ../core/str_lib.h ../core/PTR.h \
 ../core/mutex_inspector.h user.h chat_def.h levels.h ../core/DB_id.h \
 CH_id.h S_id.h user_nick.h user_status.h user_state.h nick_vec.h \
 ../core/db_var.h ../core/PTR.h ../core/mysql_extens.h ../core/_QUERY.h \
 user_profile.h ../core-web/c_conn.h chat_channel_data.h cm_container.h \
 ../core/time_limit.h
	 c++ $(RCFLAGS) ./chat_config.cpp -o $(ROBJDIR)/chat_config.o

./objR/chat_globals.o: chat_globals.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/errs.h ../core-web/web_tools.h ../core-web/web_server_data.h \
 ../core/M_DEQUE.h channels.h irc_server_config.h ../core/db_config.h \
 ../core/M_SET.h ../core/db_config2.h notes.h ../core-web/html_out.h \
 contact_vec.h ignore_vec.h user_credits.h chat_config.h \
 ../core/server_config.h ../core/file_set.h
	 c++ $(RCFLAGS) ./chat_globals.cpp -o $(ROBJDIR)/chat_globals.o

./objR/chat_msg.o: chat_msg.cpp ../stdafx/stdafx.h ../core/PTR.h \
 ../core/_mutex.h ../core/errs.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/oscar_buffer.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/DB_id.h CH_id.h chat_msg.h user_nick.h \
 ../core/Double.h chat_colors.h cm_container.h cutils.h user.h \
 ../core/_mutex.h chat_def.h levels.h message.h ../core/st_stuff.h \
 ../core/str_lib.h S_id.h chat_channel_data.h user_status.h user_state.h \
 nick_vec.h ../core/db_var.h ../core/PTR.h ../core/mysql_extens.h \
 ../core/_QUERY.h user_profile.h ../core-web/c_conn.h chat_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/M_DEQUE.h chat_stuff.h ../core/threadable.h ../core/M_MAP.h
	 c++ $(RCFLAGS) ./chat_msg.cpp -o $(ROBJDIR)/chat_msg.o

./objR/chat_thread.o: chat_thread.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/DB_id.h ../core/oscar_buffer.h CH_id.h \
 S_id.h user_nick.h ../core/Double.h chat_msg.h ../core/M_DEQUE.h \
 user_status.h user_state.h levels.h chat_stuff.h chat_channel_data.h \
 ../core/threadable.h ../core/M_MAP.h message.h ../core/_mutex.h \
 ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 user.h chat_def.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h channels.h update_cmd.h cutils.h \
 ../core/server_config.h ../core/M_SET.h ../core/file_set.h \
 ../core/M_LIST.h chat_thread_event.h irc_utils.h irc_server.h \
 ../core-web/tcp_server.h ../core-web/c_conn.h \
 ../core-web/tcp_server_connection.h ../core-web/tcp_dialog_server.h \
 ../core-web/tcp_server.h ../core-web/tcp_server_connection.h \
 ../core/M_SET.h irc_server_config.h ../core/M_MAP.h chat_globals.h \
 ../core-web/html_out.h chat_config.h ../core/file_set.h global_state.h \
 contact_vec.h ignore_vec.h admin.h chat_colors.h
	 c++ $(RCFLAGS) ./chat_thread.cpp -o $(ROBJDIR)/chat_thread.o

./objR/chat_thread_2.o: chat_thread_2.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/DB_id.h ../core/oscar_buffer.h CH_id.h \
 S_id.h ../core/M_DEQUE.h user_status.h user_nick.h ../core/Double.h \
 user_state.h levels.h chat_stuff.h chat_channel_data.h chat_msg.h \
 ../core/threadable.h ../core/M_MAP.h message.h ../core/_mutex.h \
 ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 user.h chat_def.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h channels.h cutils.h ../core-web/web_tools.h \
 cm_container.h irc_server_config.h ../core/M_MAP.h ../core/M_SET.h \
 chat_globals.h chat_thread_event.h chat_config.h ../core/file_set.h \
 ../core/M_LIST.h
	 c++ $(RCFLAGS) ./chat_thread_2.cpp -o $(ROBJDIR)/chat_thread_2.o

./objR/contact_vec.o: contact_vec.cpp ../stdafx/stdafx.h ../core/db_var.h \
 ../core/str_lib.h ../core/errs.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/mysql_extens.h \
 ../core/_QUERY.h contact_vec.h ../core/DB_id.h user.h ../core/_mutex.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/PTR.h S_id.h CH_id.h chat_channel_data.h user_nick.h \
 ../core/Double.h user_status.h user_state.h nick_vec.h user_profile.h \
 ../core-web/c_conn.h ../core/mysql_extens.h
	 c++ $(RCFLAGS) ./contact_vec.cpp -o $(ROBJDIR)/contact_vec.o

./objR/copy_file_common.o: ../core/copy_file_common.cpp ../stdafx/stdafx.h \
 ../core/str_lib.h ../core/errs.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/m_var.h ../core/M_MAP.h \
 ../core/st_stuff.h ../core/copy_file.h ../core/wrappers.h \
 ../core/mutex_inspector.h ../core/lockctl.h
	 c++ $(RCFLAGS) ../core/copy_file_common.cpp -o $(ROBJDIR)/copy_file_common.o

./objR/core_main.o: ../core/core_main.cpp ../stdafx/stdafx.h \
 ../core/server_config.h ../core/_mutex.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/m_var.h ../core/file_set.h ../core/M_LIST.h ../core/errs.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h
	 c++ $(RCFLAGS) ../core/core_main.cpp -o $(ROBJDIR)/core_main.o

./objR/cutils.o: cutils.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h cutils.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/str_lib.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h chat_config.h chat_globals.h ../core/mysql_extens.h
	 c++ $(RCFLAGS) ./cutils.cpp -o $(ROBJDIR)/cutils.o

./objR/db_config.o: ../core/db_config.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/db_config.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/m_var.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h
	 c++ $(RCFLAGS) ../core/db_config.cpp -o $(ROBJDIR)/db_config.o

./objR/db_config2.o: ../core/db_config2.cpp ../stdafx/stdafx.h
	 c++ $(RCFLAGS) ../core/db_config2.cpp -o $(ROBJDIR)/db_config2.o

./objR/db_var.o: ../core/db_var.cpp ../stdafx/stdafx.h
	 c++ $(RCFLAGS) ../core/db_var.cpp -o $(ROBJDIR)/db_var.o

./objR/des_sid.o: ../core/des_sid.cpp ../stdafx/stdafx.h ../core/str_lib.h \
 ../core/errs.h ../core/m_var.h ../core/_mutex.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/st_stuff.h ../core/m_var.h \
 ../core/des_locl.h ../core/sid_t.h ../core/des_sid.h
	 c++ $(RCFLAGS) ../core/des_sid.cpp -o $(ROBJDIR)/des_sid.o

./objR/errs.o: ../core/errs.cpp ../stdafx/stdafx.h ../core/errs.h \
 ../core/str_lib.h ../core/m_var.h ../core/_mutex.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/m_var.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/st_stuff.h
	 c++ $(RCFLAGS) ../core/errs.cpp -o $(ROBJDIR)/errs.o

./objR/file_dump.o: file_dump.cpp ../stdafx/stdafx.h
	 c++ $(RCFLAGS) ./file_dump.cpp -o $(ROBJDIR)/file_dump.o

./objR/file_set.o: ../core/file_set.cpp ../stdafx/stdafx.h ../core/wrappers.h \
 ../core/file_set.h ../core/M_LIST.h ../core/_mutex.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/errs.h ../core/lockctl.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/st_stuff.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h
	 c++ $(RCFLAGS) ../core/file_set.cpp -o $(ROBJDIR)/file_set.o

./objR/file_set_init.o: ../core/file_set_init.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/errs.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/st_stuff.h \
 ../core/file_set.h ../core/M_LIST.h ../core/m_var.h \
 ../core/st_stream_str.h ../core/st_rsa.h ../core/copy_file.h \
 ../core/wrappers.h ../core/mutex_inspector.h ../core/lockctl.h \
 ../core/server_config.h ../core/M_MAP.h ../core/M_SET.h
	 c++ $(RCFLAGS) ../core/file_set_init.cpp -o $(ROBJDIR)/file_set_init.o

./objR/global_state.o: global_state.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/DB_id.h ../core/oscar_buffer.h CH_id.h \
 user_status.h user_nick.h ../core/Double.h user_state.h global_state.h
	 c++ $(RCFLAGS) ./global_state.cpp -o $(ROBJDIR)/global_state.o

./objR/html_out.o: ../core-web/html_out.cpp ../stdafx/stdafx.h ../core/PTR.h \
 ../core/_mutex.h ../core/errs.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core-web/html_out.h \
 ../core-web/web_tools.h ../core/m_var.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/str_lib.h ../core/Double.h ../core/oscar_buffer.h \
 ../core/oscar_buffer.h
	 c++ $(RCFLAGS) ../core-web/html_out.cpp -o $(ROBJDIR)/html_out.o

./objR/ignore_vec.o: ignore_vec.cpp ../stdafx/stdafx.h ../core/db_var.h \
 ../core/str_lib.h ../core/errs.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/mysql_extens.h \
 ../core/_QUERY.h ignore_vec.h ../core/DB_id.h user.h ../core/_mutex.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/PTR.h S_id.h CH_id.h chat_channel_data.h user_nick.h \
 ../core/Double.h user_status.h user_state.h nick_vec.h user_profile.h \
 ../core-web/c_conn.h ../core/mysql_extens.h
	 c++ $(RCFLAGS) ./ignore_vec.cpp -o $(ROBJDIR)/ignore_vec.o

./objR/irc_admin.o: irc_admin.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core/file_set.h ../core/M_LIST.h ../core-web/web_server_data.h \
 ../core/M_MAP.h channels.h irc_server_config.h irc_utils.h update_cmd.h \
 admin.h chat_globals.h app_def.h
	 c++ $(RCFLAGS) ./irc_admin.cpp -o $(ROBJDIR)/irc_admin.o

./objR/irc_login.o: irc_login.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core/file_set.h ../core/M_LIST.h ../core-web/web_server_data.h \
 ../core/M_MAP.h channels.h irc_server_config.h irc_utils.h update_cmd.h \
 contact_vec.h chat_thread_event.h chat_stuff.h chat_msg.h global_state.h \
 chat_config.h
	 c++ $(RCFLAGS) ./irc_login.cpp -o $(ROBJDIR)/irc_login.o

./objR/irc_server.o: irc_server.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core/file_set.h ../core/M_LIST.h ../core-web/web_server_data.h \
 ../core/M_MAP.h channels.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h ../core-web/tcp_server_data.h irc_server_config.h \
 irc_utils.h irc_session.h chat_thread_event.h chat_stuff.h chat_msg.h \
 update_cmd.h ../core/tcp_stats.h global_state.h ../core/des_sid.h \
 ../core/sid_t.h
	 c++ $(RCFLAGS) ./irc_server.cpp -o $(ROBJDIR)/irc_server.o

./objR/irc_server_config.o: irc_server_config.cpp ../stdafx/stdafx.h \
 ../core/file_set.h ../core/M_LIST.h ../core/_mutex.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/errs.h ../core/lockctl.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h irc_server_config.h ../core/M_MAP.h \
 ../core/M_SET.h cutils.h user.h ../core/_mutex.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/PTR.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h
	 c++ $(RCFLAGS) ./irc_server_config.cpp -o $(ROBJDIR)/irc_server_config.o

./objR/irc_tools.o: irc_tools.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core/file_set.h ../core/M_LIST.h ../core-web/web_server_data.h \
 ../core/M_MAP.h channels.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h version.h irc_server_config.h irc_utils.h \
 irc_session.h global_state.h chat_config.h
	 c++ $(RCFLAGS) ./irc_tools.cpp -o $(ROBJDIR)/irc_tools.o

./objR/irc_user.o: irc_user.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core/file_set.h ../core/M_LIST.h ../core-web/web_server_data.h \
 ../core/M_MAP.h channels.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h irc_server_config.h user_credits.h \
 ../core/thread_descr.h irc_utils.h ../core/tcp_stats.h \
 chat_thread_event.h chat_stuff.h chat_msg.h irc_session.h chat_globals.h \
 update_cmd.h global_state.h admin.h
	 c++ $(RCFLAGS) ./irc_user.cpp -o $(ROBJDIR)/irc_user.o

./objR/irc_user_cred.o: irc_user_cred.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core/file_set.h ../core/M_LIST.h ../core-web/web_server_data.h \
 ../core/M_MAP.h channels.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h irc_server_config.h user_credits.h \
 ../core/thread_descr.h irc_utils.h ../core/tcp_stats.h \
 chat_thread_event.h chat_stuff.h chat_msg.h irc_session.h chat_globals.h
	 c++ $(RCFLAGS) ./irc_user_cred.cpp -o $(ROBJDIR)/irc_user_cred.o

./objR/levels.o: levels.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h ../core-web/web_server.h \
 ../core-web/tcp_server.h ../core/threadable.h ../core/M_MAP.h \
 ../core-web/c_conn.h ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h \
 ../core/M_LIST.h ../core/errs.h ../core-web/web_tools.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core/server_config.h \
 ../core/M_SET.h ../core/file_set.h chat_config.h
	 c++ $(RCFLAGS) ./levels.cpp -o $(ROBJDIR)/levels.o

./objR/license.o: ../core/license.cpp ../stdafx/stdafx.h
	 c++ $(RCFLAGS) ../core/license.cpp -o $(ROBJDIR)/license.o

./objR/local_user_handle.o: local_user_handle.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h ../core-web/web_server.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h ../core-web/tcp_server.h \
 ../core/m_var.h ../core/threadable.h ../core/M_MAP.h \
 ../core-web/c_conn.h ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h \
 ../core/M_LIST.h ../core/errs.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h cutils.h user.h chat_def.h \
 levels.h ../core/oscar_buffer.h message.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core-web/web_server_data.h ../core/M_DEQUE.h \
 ../core/tcp_stats.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h app_def.h ../core-web/tcp_sender.h \
 ../core-web/web_tools.h version.h user_credits.h irc_server_config.h \
 chat_config.h channels.h irc_utils.h irc_server.h \
 ../core-web/tcp_server.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server_connection.h \
 update_cmd.h ignore_vec.h contact_vec.h notes.h ../core-web/html_out.h \
 global_state.h chat_thread_event.h chat_stuff.h chat_msg.h
	 c++ $(RCFLAGS) ./local_user_handle.cpp -o $(ROBJDIR)/local_user_handle.o

./objR/login.o: login.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core-web/web_server.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core-web/tcp_server.h ../core/m_var.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 chat_def.h cutils.h user.h levels.h ../core/oscar_buffer.h message.h \
 ../core/st_stuff.h ../core/str_lib.h ../core/Double.h \
 ../core/oscar_buffer.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core-web/web_server_data.h \
 ../core/M_DEQUE.h ../core-web/web_tools.h user_credits.h channels.h \
 ../core/server_config.h ../core/M_SET.h ../core/file_set.h chat_config.h \
 app_def.h update_cmd.h contact_vec.h chat_thread_event.h chat_stuff.h \
 chat_msg.h ../core/des_sid.h ../core/sid_t.h ../core-web/html_out.h \
 ../core/time_limit.h chat_globals.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h
	 c++ $(RCFLAGS) ./login.cpp -o $(ROBJDIR)/login.o

./objR/main.o: main.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_tools.h admin.h channels.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h app_def.h \
 chat_config.h ../core/M_MAP.h ../core/M_SET.h update_cmd.h \
 chat_thread_event.h ../core/M_DEQUE.h chat_stuff.h chat_msg.h \
 ../core/threadable.h chat_globals.h ignore_vec.h global_state.h
	 c++ $(RCFLAGS) ./main.cpp -o $(ROBJDIR)/main.o

./objR/make_user_info.o: make_user_info.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core-web/html_out.h chat_globals.h contact_vec.h update_cmd.h \
 user_credits.h ../core-web/web_tools.h chat_thread_event.h chat_stuff.h \
 chat_msg.h app_con.h ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/html_out.h ../core/mysql_extens.h app_def.h
	 c++ $(RCFLAGS) ./make_user_info.cpp -o $(ROBJDIR)/make_user_info.o

./objR/message.o: message.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/errs.h cutils.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/copy_file.h ../core/wrappers.h channels.h \
 ../core/server_config.h ../core/M_SET.h ../core/file_set.h chat_config.h \
 irc_utils.h irc_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core-web/tcp_dialog_server.h \
 ../core-web/tcp_server_connection.h ../core/M_DEQUE.h \
 irc_server_config.h update_cmd.h chat_msg.h cm_container.h \
 ../core/mysql_extens.h chat_colors.h global_state.h
	 c++ $(RCFLAGS) ./message.cpp -o $(ROBJDIR)/message.o

./objR/mutex_inspector.o: ../core/mutex_inspector.cpp ../stdafx/stdafx.h \
 ../core/errs.h ../core/str_lib.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/_mutex1.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/M_MAP.h
	 c++ $(RCFLAGS) ../core/mutex_inspector.cpp -o $(ROBJDIR)/mutex_inspector.o

./objR/mysql_extens.o: ../core/mysql_extens.cpp ../stdafx/stdafx.h \
 ../core/str_lib.h ../core/errs.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/mysql_extens.h \
 ../core/_QUERY.h ../core/mutex_inspector.h ../core/lockctl.h \
 ../core/file_set.h ../core/M_LIST.h ../core/m_var.h ../core/st_stuff.h \
 ../core/db_config.h ../core/M_MAP.h ../core/M_SET.h ../core/cMYSQL.h
	 c++ $(RCFLAGS) ../core/mysql_extens.cpp -o $(ROBJDIR)/mysql_extens.o

./objR/mysql_extens2.o: ../core/mysql_extens2.cpp ../stdafx/stdafx.h
	 c++ $(RCFLAGS) ../core/mysql_extens2.cpp -o $(ROBJDIR)/mysql_extens2.o

./objR/nick_vec.o: nick_vec.cpp ../stdafx/stdafx.h ../core/db_var.h \
 ../core/str_lib.h ../core/errs.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/mysql_extens.h \
 ../core/_QUERY.h nick_vec.h user_nick.h ../core/Double.h ../core/DB_id.h \
 user.h ../core/_mutex.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/PTR.h S_id.h CH_id.h \
 chat_channel_data.h user_status.h user_state.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core-web/web_tools.h
	 c++ $(RCFLAGS) ./nick_vec.cpp -o $(ROBJDIR)/nick_vec.o

./objR/notes.o: notes.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h ../core-web/web_server.h \
 ../core-web/tcp_server.h ../core/threadable.h ../core/M_MAP.h \
 ../core-web/c_conn.h ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h \
 ../core/M_LIST.h ../core/copy_file.h ../core/wrappers.h notes.h \
 ../core-web/html_out.h ../core/server_config.h ../core/M_SET.h \
 ../core/file_set.h chat_config.h app_con.h ../core-web/web_connection.h \
 ../core/sid_t.h ../core-web/tcp_server_connection.h \
 ../core-web/html_out.h app_def.h user_credits.h ../core/M_DEQUE.h \
 update_cmd.h ignore_vec.h ../core-web/web_tools.h chat_globals.h
	 c++ $(RCFLAGS) ./notes.cpp -o $(ROBJDIR)/notes.o

./objR/notes_containers.o: notes_containers.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h \
 user.h chat_def.h levels.h ../core/oscar_buffer.h message.h \
 ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core/copy_file.h ../core/wrappers.h notes.h ../core-web/html_out.h \
 ../core/server_config.h ../core/M_SET.h ../core/file_set.h chat_config.h \
 ../core/time_limit.h
	 c++ $(RCFLAGS) ./notes_containers.cpp -o $(ROBJDIR)/notes_containers.o

./objR/oscar_buffer.o: ../core/oscar_buffer.cpp ../stdafx/stdafx.h \
 ../core/oscar_buffer.h ../core/str_lib.h ../core/errs.h ../core/m_var.h \
 ../core/_mutex.h ../core/Double.h ../core/mutex_inspector.h \
 ../core/lockctl.h
	 c++ $(RCFLAGS) ../core/oscar_buffer.cpp -o $(ROBJDIR)/oscar_buffer.o

./objR/oscar_client.o: ../core-web/oscar_client.cpp ../stdafx/stdafx.h \
 ../core/errs.h ../core/str_lib.h ../core/errs.h ../core/m_var.h \
 ../core/_mutex.h ../core/Double.h ../core/oscar_buffer.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core-web/oscar_client.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/_mutex.h
	 c++ $(RCFLAGS) ../core-web/oscar_client.cpp -o $(ROBJDIR)/oscar_client.o

./objR/other.o: other.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h cutils.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core-web/web_server.h \
 ../core-web/tcp_server.h ../core/threadable.h ../core/M_MAP.h \
 ../core-web/c_conn.h ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h \
 ../core/M_LIST.h ../core/copy_file.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h \
 ../core/tcp_stats.h chat_config.h user_credits.h ../core/M_DEQUE.h \
 ../core-web/tcp_oscar_dialog_server.h ../core-web/tcp_dialog_server.h \
 chat_globals.h app_def.h
	 c++ $(RCFLAGS) ./other.cpp -o $(ROBJDIR)/other.o

./objR/rijndael.o: ../core/rijndael.cpp ../core/rijndael.h
	 c++ $(RCFLAGS) ../core/rijndael.cpp -o $(ROBJDIR)/rijndael.o

./objR/server_config.o: ../core/server_config.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/server_config.h ../core/M_MAP.h \
 ../core/M_SET.h ../core/m_var.h ../core/file_set.h ../core/M_LIST.h \
 ../core/wrappers.h ../core/st_stuff.h
	 c++ $(RCFLAGS) ../core/server_config.cpp -o $(ROBJDIR)/server_config.o

./objR/st_FILE.o: ../core/st_FILE.cpp ../stdafx/stdafx.h ../core/st_stuff.h \
 ../core/errs.h ../core/str_lib.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/copy_file.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/wrappers.h
	 c++ $(RCFLAGS) ../core/st_FILE.cpp -o $(ROBJDIR)/st_FILE.o

./objR/st_rsa.o: ../core/st_rsa.cpp ../stdafx/stdafx.h ../core/st_stuff.h \
 ../core/errs.h ../core/str_lib.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/mutex_inspector.h \
 ../core/lockctl.h ../core/m_var.h ../core/st_rsa.h
	 c++ $(RCFLAGS) ../core/st_rsa.cpp -o $(ROBJDIR)/st_rsa.o

./objR/st_savecwd.o: ../core/st_savecwd.cpp ../stdafx/stdafx.h \
 ../core/st_stuff.h ../core/errs.h ../core/str_lib.h ../core/m_var.h \
 ../core/_mutex.h ../core/Double.h ../core/oscar_buffer.h \
 ../core/copy_file.h ../core/mutex_inspector.h ../core/lockctl.h
	 c++ $(RCFLAGS) ../core/st_savecwd.cpp -o $(ROBJDIR)/st_savecwd.o

./objR/st_stream_str.o: ../core/st_stream_str.cpp ../stdafx/stdafx.h \
 ../core/str_lib.h ../core/errs.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/st_stream_str.h \
 ../core/st_stuff.h
	 c++ $(RCFLAGS) ../core/st_stream_str.cpp -o $(ROBJDIR)/st_stream_str.o

./objR/st_stuff.o: ../core/st_stuff.cpp ../stdafx/stdafx.h ../core/st_stuff.h \
 ../core/errs.h ../core/str_lib.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/mutex_inspector.h \
 ../core/lockctl.h
	 c++ $(RCFLAGS) ../core/st_stuff.cpp -o $(ROBJDIR)/st_stuff.o

./objR/str_lib.o: ../core/str_lib.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/errs.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/mutex_inspector.h ../core/lockctl.h
	 c++ $(RCFLAGS) ../core/str_lib.cpp -o $(ROBJDIR)/str_lib.o

./objR/str_lib1.o: ../core/str_lib1.cpp ../stdafx/stdafx.h \
 ../core/oscar_buffer.h ../core/Double.h ../core/_mutex.h ../core/errs.h \
 ../core/str_lib.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core/lockctl.h
	 c++ $(RCFLAGS) ../core/str_lib1.cpp -o $(ROBJDIR)/str_lib1.o

./objR/str_lib_extra.o: ../core/str_lib_extra.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/errs.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/st_stuff.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/st_stream_str.h
	 c++ $(RCFLAGS) ../core/str_lib_extra.cpp -o $(ROBJDIR)/str_lib_extra.o

./objR/tcp_dialog_server.o: ../core-web/tcp_dialog_server.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h ../core/lockctl.h ../core-web/c_conn.h \
 ../core/m_var.h ../core/PTR.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/tcp_server_connection.h \
 ../core/oscar_buffer.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core-web/tcp_server_data.h ../core/M_MAP.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h
	 c++ $(RCFLAGS) ../core-web/tcp_dialog_server.cpp -o $(ROBJDIR)/tcp_dialog_server.o

./objR/tcp_oscar_dialog_server.o: ../core-web/tcp_oscar_dialog_server.cpp \
 ../stdafx/stdafx.h ../core/_mutex.h ../core/mutex_inspector.h \
 ../core/_mutex.h ../core/errs.h ../core/lockctl.h ../core/lockctl.h \
 ../core-web/tcp_oscar_dialog_server.h ../core-web/tcp_dialog_server.h \
 ../core-web/tcp_server.h ../core/m_var.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core-web/tcp_server_connection.h \
 ../core/oscar_buffer.h ../core/M_SET.h ../core/M_DEQUE.h \
 ../core/str_lib.h ../core/Double.h ../core/oscar_buffer.h
	 c++ $(RCFLAGS) ../core-web/tcp_oscar_dialog_server.cpp -o $(ROBJDIR)/tcp_oscar_dialog_server.o

./objR/tcp_sender.o: ../core-web/tcp_sender.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core-web/tcp_server_data.h ../core/M_DEQUE.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core/_mutex.h ../core/m_var.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/M_MAP.h ../core/file_set.h \
 ../core/M_LIST.h ../core/str_lib.h ../core/Double.h \
 ../core/oscar_buffer.h ../core-web/tcp_sender.h ../core/tcp_stats.h \
 ../core/M_SET.h ../core/threadable.h ../core/M_MAP.h
	 c++ $(RCFLAGS) ../core-web/tcp_sender.cpp -o $(ROBJDIR)/tcp_sender.o

./objR/tcp_server.o: ../core-web/tcp_server.cpp ../stdafx/stdafx.h \
 ../core-web/tcp_server_data.h ../core/M_DEQUE.h ../core/_mutex.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core/_mutex.h ../core/m_var.h ../core/PTR.h ../core/errs.h \
 ../core/m_var.h ../core/mutex_inspector.h ../core/lockctl.h \
 ../core/M_MAP.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core/M_MAP.h ../core/mutex_inspector.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/tcp_stats.h
	 c++ $(RCFLAGS) ../core-web/tcp_server.cpp -o $(ROBJDIR)/tcp_server.o

./objR/tcp_server_connection.o: ../core-web/tcp_server_connection.cpp \
 ../stdafx/stdafx.h ../core-web/tcp_server_connection.h \
 ../core-web/c_conn.h ../core/_mutex.h ../core/m_var.h ../core/_mutex.h \
 ../core/PTR.h ../core/errs.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core/lockctl.h ../core/errs.h ../core/str_lib.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/mutex_inspector.h \
 ../core-web/tcp_sender.h
	 c++ $(RCFLAGS) ../core-web/tcp_server_connection.cpp -o $(ROBJDIR)/tcp_server_connection.o

./objR/tcp_stats.o: ../core/tcp_stats.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/m_var.h
	 c++ $(RCFLAGS) ../core/tcp_stats.cpp -o $(ROBJDIR)/tcp_stats.o

./objR/thread_info_report.o: ../core-web/thread_info_report.cpp \
 ../stdafx/stdafx.h ../core-web/tcp_server_connection.h \
 ../core-web/c_conn.h ../core/_mutex.h ../core/m_var.h ../core/_mutex.h \
 ../core/PTR.h ../core/errs.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core/lockctl.h ../core/errs.h ../core/str_lib.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/file_set.h ../core/M_LIST.h ../core/mutex_inspector.h \
 ../core/M_DEQUE.h ../core-web/tcp_server_data.h ../core/M_MAP.h \
 ../core/tcp_stats.h
	 c++ $(RCFLAGS) ../core-web/thread_info_report.cpp -o $(ROBJDIR)/thread_info_report.o

./objR/threadable.o: ../core/threadable.cpp ../stdafx/stdafx.h \
 ../core/threadable.h ../core/M_MAP.h ../core/_mutex.h ../core/errs.h \
 ../core/mutex_inspector.h ../core/lockctl.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h
	 c++ $(RCFLAGS) ../core/threadable.cpp -o $(ROBJDIR)/threadable.o

./objR/u_chat.o: u_chat.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 ../core-web/web_tools.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_server_data.h ../core/M_MAP.h ../core/M_DEQUE.h \
 ../core-web/tcp_sender.h channels.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h chat_config.h \
 ../core/M_SET.h irc_server_config.h irc_utils.h irc_server.h \
 ../core-web/tcp_server.h ../core/threadable.h ../core-web/c_conn.h \
 ../core-web/tcp_server_connection.h ../core-web/tcp_dialog_server.h \
 ../core-web/tcp_server.h ../core-web/tcp_server_connection.h \
 update_cmd.h cm_container.h ignore_vec.h contact_vec.h notes.h \
 ../core-web/html_out.h global_state.h ../core/copy_file.h
	 c++ $(RCFLAGS) ./u_chat.cpp -o $(ROBJDIR)/u_chat.o

./objR/update_cmd.o: update_cmd.cpp ../stdafx/stdafx.h ../core/M_DEQUE.h \
 ../core/_mutex.h ../core/oscar_buffer.h ../core/DB_id.h \
 ../core/oscar_buffer.h ../core/errs.h ../core/mutex_inspector.h \
 ../core/lockctl.h update_cmd.h CH_id.h ../core/mysql_extens.h \
 ../core/_QUERY.h user.h ../core/_mutex.h chat_def.h levels.h message.h \
 ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/PTR.h ../core/m_var.h ../core/mutex_inspector.h S_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h \
 chat_thread_event.h chat_stuff.h chat_msg.h ../core/threadable.h \
 ../core/M_MAP.h ignore_vec.h channels.h ../core/copy_file.h cutils.h \
 user_credits.h notes.h ../core-web/html_out.h contact_vec.h admin.h \
 ../core/time_limit.h
	 c++ $(RCFLAGS) ./update_cmd.cpp -o $(ROBJDIR)/update_cmd.o

./objR/url_change_nick.o: url_change_nick.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_tools.h admin.h channels.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h app_def.h \
 chat_config.h ../core/M_MAP.h ../core/M_SET.h update_cmd.h \
 chat_thread_event.h ../core/M_DEQUE.h chat_stuff.h chat_msg.h \
 ../core/threadable.h chat_globals.h ignore_vec.h global_state.h
	 c++ $(RCFLAGS) ./url_change_nick.cpp -o $(ROBJDIR)/url_change_nick.o

./objR/url_chat_messages.o: url_chat_messages.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_tools.h admin.h channels.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h app_def.h \
 chat_config.h ../core/M_MAP.h ../core/M_SET.h update_cmd.h \
 chat_thread_event.h ../core/M_DEQUE.h chat_stuff.h chat_msg.h \
 ../core/threadable.h chat_globals.h ignore_vec.h global_state.h
	 c++ $(RCFLAGS) ./url_chat_messages.cpp -o $(ROBJDIR)/url_chat_messages.o

./objR/url_chat_sendmessage.o: url_chat_sendmessage.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_tools.h admin.h channels.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h app_def.h \
 chat_config.h ../core/M_MAP.h ../core/M_SET.h update_cmd.h \
 chat_thread_event.h ../core/M_DEQUE.h chat_stuff.h chat_msg.h \
 ../core/threadable.h chat_globals.h ignore_vec.h global_state.h
	 c++ $(RCFLAGS) ./url_chat_sendmessage.cpp -o $(ROBJDIR)/url_chat_sendmessage.o

./objR/url_ignore_user.o: url_ignore_user.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_tools.h admin.h channels.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h app_def.h \
 chat_config.h ../core/M_MAP.h ../core/M_SET.h update_cmd.h \
 chat_thread_event.h ../core/M_DEQUE.h chat_stuff.h chat_msg.h \
 ../core/threadable.h chat_globals.h ignore_vec.h global_state.h
	 c++ $(RCFLAGS) ./url_ignore_user.cpp -o $(ROBJDIR)/url_ignore_user.o

./objR/url_new_nick.o: url_new_nick.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/str_lib.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core-web/web_tools.h \
 channels.h ../core/server_config.h ../core/M_SET.h ../core/file_set.h \
 app_def.h chat_config.h irc_server_config.h update_cmd.h chat_globals.h \
 user_credits.h app_con.h ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h
	 c++ $(RCFLAGS) ./url_new_nick.cpp -o $(ROBJDIR)/url_new_nick.o

./objR/url_set_user_status.o: url_set_user_status.cpp ../stdafx/stdafx.h \
 ../core/_mutex.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h user.h chat_def.h levels.h \
 ../core/oscar_buffer.h message.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/m_var.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h ../core/str_lib.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_tools.h admin.h channels.h ../core/server_config.h \
 ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h app_def.h \
 chat_config.h ../core/M_MAP.h ../core/M_SET.h update_cmd.h \
 chat_thread_event.h ../core/M_DEQUE.h chat_stuff.h chat_msg.h \
 ../core/threadable.h chat_globals.h ignore_vec.h global_state.h
	 c++ $(RCFLAGS) ./url_set_user_status.cpp -o $(ROBJDIR)/url_set_user_status.o

./objR/user.o: user.cpp ../stdafx/stdafx.h ../core/_mutex.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h user.h chat_def.h levels.h ../core/oscar_buffer.h \
 message.h ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h ../core/str_lib.h ../core/errs.h cutils.h \
 ../core-web/web_tools.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_server_data.h ../core/M_MAP.h ../core/M_DEQUE.h \
 channels.h ../core/server_config.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/file_set.h chat_config.h ../core/M_SET.h irc_server_config.h \
 irc_utils.h irc_server.h ../core-web/tcp_server.h ../core/threadable.h \
 ../core-web/c_conn.h ../core-web/tcp_server_connection.h \
 ../core-web/tcp_dialog_server.h ../core-web/tcp_server.h \
 ../core-web/tcp_server_connection.h ../core-web/tcp_sender.h \
 update_cmd.h chat_msg.h cm_container.h chat_thread_event.h chat_stuff.h \
 ignore_vec.h contact_vec.h chat_globals.h global_state.h user_credits.h \
 admin.h ../core/M_HASHMAP.h chat_colors.h
	 c++ $(RCFLAGS) ./user.cpp -o $(ROBJDIR)/user.o

./objR/user_credits.o: user_credits.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/mysql_extens.h ../core/_QUERY.h user.h \
 ../core/_mutex.h chat_def.h levels.h ../core/oscar_buffer.h message.h \
 ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h S_id.h ../core/DB_id.h CH_id.h \
 chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h user_profile.h ../core-web/c_conn.h cutils.h \
 ../core/copy_file.h user_credits.h ../core/M_DEQUE.h \
 ../core/server_config.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/file_set.h ../core/M_LIST.h update_cmd.h app_con.h \
 ../core-web/web_connection.h ../core/sid_t.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core-web/html_out.h chat_config.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/file_set.h
	 c++ $(RCFLAGS) ./user_credits.cpp -o $(ROBJDIR)/user_credits.o

./objR/user_nick.o: user_nick.cpp ../stdafx/stdafx.h ../core/oscar_buffer.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/DB_id.h ../core/oscar_buffer.h user_nick.h \
 ../core/Double.h user.h ../core/_mutex.h chat_def.h levels.h message.h \
 ../core/st_stuff.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/PTR.h ../core/m_var.h ../core/mutex_inspector.h S_id.h CH_id.h \
 chat_channel_data.h user_status.h user_state.h nick_vec.h \
 ../core/db_var.h ../core/PTR.h ../core/mysql_extens.h ../core/_QUERY.h \
 user_profile.h ../core-web/c_conn.h cutils.h
	 c++ $(RCFLAGS) ./user_nick.cpp -o $(ROBJDIR)/user_nick.o

./objR/user_profile.o: user_profile.cpp ../stdafx/stdafx.h user.h \
 ../core/_mutex.h chat_def.h levels.h ../core/oscar_buffer.h message.h \
 ../core/st_stuff.h ../core/errs.h ../core/str_lib.h ../core/m_var.h \
 ../core/_mutex.h ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h ../core/lockctl.h S_id.h \
 ../core/DB_id.h CH_id.h chat_channel_data.h user_nick.h ../core/Double.h \
 user_status.h user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h cm_container.h notes.h \
 ../core-web/html_out.h
	 c++ $(RCFLAGS) ./user_profile.cpp -o $(ROBJDIR)/user_profile.o

./objR/user_state.o: user_state.cpp ../stdafx/stdafx.h user.h ../core/_mutex.h \
 chat_def.h levels.h ../core/oscar_buffer.h message.h ../core/st_stuff.h \
 ../core/errs.h ../core/str_lib.h ../core/m_var.h ../core/_mutex.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core/lockctl.h S_id.h ../core/DB_id.h \
 CH_id.h chat_channel_data.h user_nick.h ../core/Double.h user_status.h \
 user_state.h nick_vec.h ../core/db_var.h ../core/PTR.h \
 ../core/mysql_extens.h ../core/_QUERY.h user_profile.h \
 ../core-web/c_conn.h cutils.h
	 c++ $(RCFLAGS) ./user_state.cpp -o $(ROBJDIR)/user_state.o

./objR/web_adminfo.o: ../core-web/web_adminfo.cpp ../stdafx/stdafx.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core/_mutex.h ../core/m_var.h ../core/_mutex.h ../core/PTR.h \
 ../core/errs.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core/lockctl.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/file_set.h ../core/M_LIST.h ../core/errs.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/st_stuff.h \
 ../core/str_lib.h ../core/des_sid.h ../core/sid_t.h \
 ../core/mutex_inspector.h ../core/M_DEQUE.h \
 ../core-web/tcp_server_data.h ../core-web/web_connection.h \
 ../core/sid_t.h ../core-web/html_out.h ../core-web/web_server_data.h \
 ../core-web/c_conn.h ../core/tcp_stats.h
	 c++ $(RCFLAGS) ../core-web/web_adminfo.cpp -o $(ROBJDIR)/web_adminfo.o

./objR/web_cache.o: ../core-web/web_cache.cpp ../stdafx/stdafx.h
	 c++ $(RCFLAGS) ../core-web/web_cache.cpp -o $(ROBJDIR)/web_cache.o

./objR/web_connection.o: ../core-web/web_connection.cpp ../stdafx/stdafx.h \
 ../core/sid_t.h ../core/mutex_inspector.h ../core/_mutex.h \
 ../core/errs.h ../core/lockctl.h ../core-web/web_server.h ../core/PTR.h \
 ../core/m_var.h ../core/mutex_inspector.h ../core-web/tcp_server.h \
 ../core/m_var.h ../core/threadable.h ../core/M_MAP.h \
 ../core-web/c_conn.h ../core/_mutex.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/file_set.h ../core/M_LIST.h ../core/des_sid.h ../core/sid_t.h \
 ../core/str_lib.h ../core/Double.h ../core/oscar_buffer.h \
 ../core-web/web_connection.h ../core-web/tcp_server_connection.h \
 ../core-web/html_out.h ../core-web/web_tools.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core-web/c_conn.h \
 ../core/st_stuff.h ../core/str_lib.h ../core/server_config.h \
 ../core/M_SET.h ../core/file_set.h ../core/oscar_buffer.h
	 c++ $(RCFLAGS) ../core-web/web_connection.cpp -o $(ROBJDIR)/web_connection.o

./objR/web_connection_ptcp.o: ../core-web/web_connection_ptcp.cpp \
 ../stdafx/stdafx.h ../core/sid_t.h ../core/mutex_inspector.h \
 ../core/_mutex.h ../core/errs.h ../core/lockctl.h \
 ../core-web/web_server.h ../core/PTR.h ../core/m_var.h \
 ../core/mutex_inspector.h ../core-web/tcp_server.h ../core/m_var.h \
 ../core/threadable.h ../core/M_MAP.h ../core-web/c_conn.h \
 ../core/_mutex.h ../core/M_MAP.h ../core/M_SET.h ../core/file_set.h \
 ../core/M_LIST.h ../core/des_sid.h ../core/sid_t.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h ../core-web/web_connection.h \
 ../core-web/tcp_server_connection.h ../core-web/html_out.h \
 ../core-web/web_tools.h ../core-web/web_server_data.h ../core/M_DEQUE.h \
 ../core-web/c_conn.h ../core/st_stuff.h ../core/str_lib.h \
 ../core/server_config.h ../core/M_SET.h ../core/file_set.h \
 ../core/thread_descr.h
	 c++ $(RCFLAGS) ../core-web/web_connection_ptcp.cpp -o $(ROBJDIR)/web_connection_ptcp.o

./objR/web_server.o: ../core-web/web_server.cpp ../stdafx/stdafx.h \
 ../core-web/web_server.h ../core/PTR.h ../core/_mutex.h ../core/errs.h \
 ../core/m_var.h ../core/mutex_inspector.h ../core/lockctl.h \
 ../core-web/tcp_server.h ../core/m_var.h ../core/threadable.h \
 ../core/M_MAP.h ../core-web/c_conn.h ../core/_mutex.h ../core/M_MAP.h \
 ../core/M_SET.h ../core/file_set.h ../core/M_LIST.h \
 ../core-web/web_server_data.h ../core/M_DEQUE.h ../core-web/c_conn.h \
 ../core/mutex_inspector.h ../core-web/tcp_server_data.h \
 ../core-web/tcp_server_connection.h ../core-web/web_connection.h \
 ../core/sid_t.h ../core-web/html_out.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h ../core-web/tcp_sender.h
	 c++ $(RCFLAGS) ../core-web/web_server.cpp -o $(ROBJDIR)/web_server.o

./objR/web_tools.o: ../core-web/web_tools.cpp ../stdafx/stdafx.h \
 ../core-web/tcp_server_connection.h ../core-web/c_conn.h \
 ../core/_mutex.h ../core/m_var.h ../core/_mutex.h ../core/PTR.h \
 ../core/errs.h ../core/m_var.h ../core/mutex_inspector.h \
 ../core/lockctl.h ../core-web/web_server.h ../core-web/tcp_server.h \
 ../core/threadable.h ../core/M_MAP.h ../core/M_MAP.h ../core/M_SET.h \
 ../core/file_set.h ../core/M_LIST.h ../core/errs.h ../core/str_lib.h \
 ../core/Double.h ../core/oscar_buffer.h ../core/st_stuff.h \
 ../core/str_lib.h ../core-web/web_tools.h ../core/sid_t.h \
 ../core/des_sid.h ../core/sid_t.h ../core/server_config.h \
 ../core/M_SET.h ../core/file_set.h ../core/mutex_inspector.h
	 c++ $(RCFLAGS) ../core-web/web_tools.cpp -o $(ROBJDIR)/web_tools.o

./objR/wrappers.o: ../core/wrappers.cpp ../stdafx/stdafx.h \
 ../core/mutex_inspector.h ../core/_mutex.h ../core/errs.h \
 ../core/lockctl.h ../core/str_lib.h ../core/m_var.h ../core/Double.h \
 ../core/oscar_buffer.h ../core/copy_file.h ../core/wrappers.h \
 ../core/tcp_stats.h
	 c++ $(RCFLAGS) ../core/wrappers.cpp -o $(ROBJDIR)/wrappers.o

clean:
	 rm CS_tusa.exe CS_tusa.release.exe z.out kaka.xxx file_dump.cpp TERM* 1 2

both: all release



cleanobjs:
	 rm $(OBJDIR)/CS_tusa.o $(OBJDIR)/Double.o $(OBJDIR)/PTR.o $(OBJDIR)/_QUERY.o $(OBJDIR)/__main.o $(OBJDIR)/_mutex.o $(OBJDIR)/_mutex1.o $(OBJDIR)/admin.o $(OBJDIR)/admin_ban.o $(OBJDIR)/admin_old_ban.o $(OBJDIR)/admin_other.o $(OBJDIR)/admin_privs.o $(OBJDIR)/admin_settings.o $(OBJDIR)/app_con.o $(OBJDIR)/app_server.o $(OBJDIR)/c_conn.o $(OBJDIR)/channels.o $(OBJDIR)/chat_colors.o $(OBJDIR)/chat_config.o $(OBJDIR)/chat_globals.o $(OBJDIR)/chat_msg.o $(OBJDIR)/chat_thread.o $(OBJDIR)/chat_thread_2.o $(OBJDIR)/contact_vec.o $(OBJDIR)/copy_file_common.o $(OBJDIR)/core_main.o $(OBJDIR)/cutils.o $(OBJDIR)/db_config.o $(OBJDIR)/db_config2.o $(OBJDIR)/db_var.o $(OBJDIR)/des_sid.o $(OBJDIR)/errs.o $(OBJDIR)/file_dump.o $(OBJDIR)/file_set.o $(OBJDIR)/file_set_init.o $(OBJDIR)/global_state.o $(OBJDIR)/html_out.o $(OBJDIR)/ignore_vec.o $(OBJDIR)/irc_admin.o $(OBJDIR)/irc_login.o $(OBJDIR)/irc_server.o $(OBJDIR)/irc_server_config.o $(OBJDIR)/irc_tools.o $(OBJDIR)/irc_user.o $(OBJDIR)/irc_user_cred.o $(OBJDIR)/levels.o $(OBJDIR)/license.o $(OBJDIR)/local_user_handle.o $(OBJDIR)/login.o $(OBJDIR)/main.o $(OBJDIR)/make_user_info.o $(OBJDIR)/message.o $(OBJDIR)/mutex_inspector.o $(OBJDIR)/mysql_extens.o $(OBJDIR)/mysql_extens2.o $(OBJDIR)/nick_vec.o $(OBJDIR)/notes.o $(OBJDIR)/notes_containers.o $(OBJDIR)/oscar_buffer.o $(OBJDIR)/oscar_client.o $(OBJDIR)/other.o $(OBJDIR)/rijndael.o $(OBJDIR)/server_config.o $(OBJDIR)/st_FILE.o $(OBJDIR)/st_rsa.o $(OBJDIR)/st_savecwd.o $(OBJDIR)/st_stream_str.o $(OBJDIR)/st_stuff.o $(OBJDIR)/str_lib.o $(OBJDIR)/str_lib1.o $(OBJDIR)/str_lib_extra.o $(OBJDIR)/tcp_dialog_server.o $(OBJDIR)/tcp_oscar_dialog_server.o $(OBJDIR)/tcp_sender.o $(OBJDIR)/tcp_server.o $(OBJDIR)/tcp_server_connection.o $(OBJDIR)/tcp_stats.o $(OBJDIR)/thread_info_report.o $(OBJDIR)/threadable.o $(OBJDIR)/u_chat.o $(OBJDIR)/update_cmd.o $(OBJDIR)/url_change_nick.o $(OBJDIR)/url_chat_messages.o $(OBJDIR)/url_chat_sendmessage.o $(OBJDIR)/url_ignore_user.o $(OBJDIR)/url_new_nick.o $(OBJDIR)/url_set_user_status.o $(OBJDIR)/user.o $(OBJDIR)/user_credits.o $(OBJDIR)/user_nick.o $(OBJDIR)/user_profile.o $(OBJDIR)/user_state.o $(OBJDIR)/web_adminfo.o $(OBJDIR)/web_cache.o $(OBJDIR)/web_connection.o $(OBJDIR)/web_connection_ptcp.o $(OBJDIR)/web_server.o $(OBJDIR)/web_tools.o $(OBJDIR)/wrappers.o $(ROBJDIR)/CS_tusa.o $(ROBJDIR)/Double.o $(ROBJDIR)/PTR.o $(ROBJDIR)/_QUERY.o $(ROBJDIR)/__main.o $(ROBJDIR)/_mutex.o $(ROBJDIR)/_mutex1.o $(ROBJDIR)/admin.o $(ROBJDIR)/admin_ban.o $(ROBJDIR)/admin_old_ban.o $(ROBJDIR)/admin_other.o $(ROBJDIR)/admin_privs.o $(ROBJDIR)/admin_settings.o $(ROBJDIR)/app_con.o $(ROBJDIR)/app_server.o $(ROBJDIR)/c_conn.o $(ROBJDIR)/channels.o $(ROBJDIR)/chat_colors.o $(ROBJDIR)/chat_config.o $(ROBJDIR)/chat_globals.o $(ROBJDIR)/chat_msg.o $(ROBJDIR)/chat_thread.o $(ROBJDIR)/chat_thread_2.o $(ROBJDIR)/contact_vec.o $(ROBJDIR)/copy_file_common.o $(ROBJDIR)/core_main.o $(ROBJDIR)/cutils.o $(ROBJDIR)/db_config.o $(ROBJDIR)/db_config2.o $(ROBJDIR)/db_var.o $(ROBJDIR)/des_sid.o $(ROBJDIR)/errs.o $(ROBJDIR)/file_dump.o $(ROBJDIR)/file_set.o $(ROBJDIR)/file_set_init.o $(ROBJDIR)/global_state.o $(ROBJDIR)/html_out.o $(ROBJDIR)/ignore_vec.o $(ROBJDIR)/irc_admin.o $(ROBJDIR)/irc_login.o $(ROBJDIR)/irc_server.o $(ROBJDIR)/irc_server_config.o $(ROBJDIR)/irc_tools.o $(ROBJDIR)/irc_user.o $(ROBJDIR)/irc_user_cred.o $(ROBJDIR)/levels.o $(ROBJDIR)/license.o $(ROBJDIR)/local_user_handle.o $(ROBJDIR)/login.o $(ROBJDIR)/main.o $(ROBJDIR)/make_user_info.o $(ROBJDIR)/message.o $(ROBJDIR)/mutex_inspector.o $(ROBJDIR)/mysql_extens.o $(ROBJDIR)/mysql_extens2.o $(ROBJDIR)/nick_vec.o $(ROBJDIR)/notes.o $(ROBJDIR)/notes_containers.o $(ROBJDIR)/oscar_buffer.o $(ROBJDIR)/oscar_client.o $(ROBJDIR)/other.o $(ROBJDIR)/rijndael.o $(ROBJDIR)/server_config.o $(ROBJDIR)/st_FILE.o $(ROBJDIR)/st_rsa.o $(ROBJDIR)/st_savecwd.o $(ROBJDIR)/st_stream_str.o $(ROBJDIR)/st_stuff.o $(ROBJDIR)/str_lib.o $(ROBJDIR)/str_lib1.o $(ROBJDIR)/str_lib_extra.o $(ROBJDIR)/tcp_dialog_server.o $(ROBJDIR)/tcp_oscar_dialog_server.o $(ROBJDIR)/tcp_sender.o $(ROBJDIR)/tcp_server.o $(ROBJDIR)/tcp_server_connection.o $(ROBJDIR)/tcp_stats.o $(ROBJDIR)/thread_info_report.o $(ROBJDIR)/threadable.o $(ROBJDIR)/u_chat.o $(ROBJDIR)/update_cmd.o $(ROBJDIR)/url_change_nick.o $(ROBJDIR)/url_chat_messages.o $(ROBJDIR)/url_chat_sendmessage.o $(ROBJDIR)/url_ignore_user.o $(ROBJDIR)/url_new_nick.o $(ROBJDIR)/url_set_user_status.o $(ROBJDIR)/user.o $(ROBJDIR)/user_credits.o $(ROBJDIR)/user_nick.o $(ROBJDIR)/user_profile.o $(ROBJDIR)/user_state.o $(ROBJDIR)/web_adminfo.o $(ROBJDIR)/web_cache.o $(ROBJDIR)/web_connection.o $(ROBJDIR)/web_connection_ptcp.o $(ROBJDIR)/web_server.o $(ROBJDIR)/web_tools.o $(ROBJDIR)/wrappers.o libchat.a libchatR.a


cleanall: clean cleanobjs


