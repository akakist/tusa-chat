OBJDIR=./objD
ROBJDIR=./objR
############# release config
#CFLAGS= -O2  -I/usr/include/mysql -c -I/usr/local/ssl/include -DLINUX -Dchat -Wall 
#LIBS=../kall/_apache.a ../kall/libperl.a   /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a  -lpthread -lz -lgdbm 
#############################


CFLAGS= `cat _CFLAGS_D` -DSVN_VERSION="\"`svnversion`\""


#-DUSE_MUTEX_TRYLOCK	
	
RCFLAGS= `cat _CFLAGS_R` -DSVN_VERSION="\"`svnversion`\""


LIBS=  -lssl -lcrypto  /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a     /usr/local/lib/libGeoIP.a 
RLIBS=  -lssl -lcrypto  /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a   /usr/local/lib/libGeoIP.a 

#LIBS_DEP=client/libbos_client_d.a core_web1/libcoreweb_d.a core1/libcommon_d.a  
#RLIBS_DEP=client/libbos_client_r.a core_web1/libcoreweb_r.a core1/libcommon_r.a

#LIBS= /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a -lboost_regex-gcc-1_32  -lpthread -lz /usr/lib/libgdbm.a    
#RLIBS= /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a -lboost_regex-gcc-1_32  -lpthread -lz /usr/lib/libgdbm.a   

#LIBS= /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex.a -lpthread  -lgdbm   -static
#RLIBS=  /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex.a -lpthread  -lgdbm -static
##########################/usr/local/lib/libstlport_gcc.a 



LIBNAME=libchat_d.a
RLIBNAME=libchat_r.a
INC_DIRS= .  ../core ../core_web    client ../chatserver  \
	    ../chatserver/_admin \
	    ../chatserver/_forum \
	    ../chatserver/_lib \
	    ../chatserver/data \
	    ../chatserver/klan \
	    ../chatserver/io_stuff \
                
                
                  
                  
              
TARGETS=clan_server.cpp 
	
OBJS= app_con.cpp app_server.cpp clan_parser.cpp file_dump.cpp clan_con.cpp main.cpp\
    channels.cpp u_chat.cpp fotos.cpp notes.cpp notes_containers.cpp chat_config.cpp message.cpp chat_colors.cpp\
    user_set.cpp levels.cpp chat_globals.cpp update_cmd.cpp ignore_vec.cpp user_set.cpp user.cpp\
    contact_vec.cpp user_stat.cpp user_stat.cpp user_state.cpp user_status.cpp chat_thread.cpp  \
    chat_thread_2.cpp user_nick.cpp utils.cpp irc_server_config.cpp nick_vec.cpp chat_msg.cpp irc_tools.cpp\
    cs_conn_data.cpp user_credits.cpp user_profile.cpp irc_server.cpp irc_user.cpp irc_admin.cpp irc_login.cpp\
    klan_to_db_io.cpp user_info.cpp make_user_info.cpp register.cpp login.cpp make_login_out.cpp\
    fotos_ui.cpp other.cpp settings.cpp gallery.cpp klan_to_db_io.cpp PTR.cpp __main.cpp _mutex.cpp _mutex1.cpp copy_file_common.cpp core_main.cpp  db_var.cpp\
    des_sid.cpp errs.cpp file_set.cpp file_set_init.cpp mutex_inspector.cpp  oscar_buffer.cpp rijndael.cpp\
    server_config.cpp st_FILE.cpp st_rsa.cpp st_savecwd.cpp st_stuff.cpp str_lib.cpp str_lib1.cpp str_lib_extra.cpp wrappers.cpp\
    c_conn.cpp html_out.cpp tcp_dialog_server.cpp tcp_oscar_dialog_server.cpp tcp_sender.cpp\
    tcp_server.cpp tcp_server_connection.cpp tcp_stats.cpp thread_info_report.cpp web_adminfo.cpp web_connection.cpp\
    web_connection_ptcp.cpp web_server.cpp web_tools.cpp \
    bos_client.cpp
	

#user_profile.cpp foto_profile.cpp 

#	web_adminfo.cpp

#tbl_user.cpp 
