OBJDIR=./objD
ROBJDIR=./objR

CFLAGS=  `cat ../_CFLAGS_D` 
RCFLAGS= `cat ../_CFLAGS_R`

LIBS= -lssl -lcrypto /usr/local/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a     /usr/local/lib/libGeoIP.a  -shared -Xlinker "--exclude-libs=libfmD.a" -v
RLIBS= -lssl -lcrypto /usr/local/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a   /usr/local/lib/libGeoIP.a   -shared -Xlinker "--exclude-libs=libfmR.a" -v




LIBNAME=./libcoreweb_d.a
RLIBNAME=./libcoreweb_r.a
INC_DIRS= . ../../core ../../core_web ../../stdafx


TARGETS=


OBJS=c_conn.cpp html_out.cpp  tcp_dialog_server.cpp tcp_oscar_dialog_server.cpp tcp_sender.cpp\
    tcp_server.cpp tcp_server_connection.cpp tcp_stats.cpp thread_info_report.cpp web_adminfo.cpp web_connection.cpp\
    web_connection_ptcp.cpp web_server.cpp web_tools.cpp  web_cache.cpp\




	 
