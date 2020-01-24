OBJDIR=./objD
ROBJDIR=./objR
############# release config
#CFLAGS= -O2  -I/usr/include/mysql -c -I/usr/local/ssl/include -DLINUX -Dchat -Wall 
#LIBS=../kall/_apache.a ../kall/libperl.a   /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a  -lpthread -lz -lgdbm 
#############################


CFLAGS= `cat _CFLAGS_D`

#-DUSE_MUTEX_TRYLOCK	
	
RCFLAGS= `cat _CFLAGS_R`

LIBS=  /usr/lib/libssl.a /usr/lib/libcrypto.a  /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread /usr/lib/libz.a /usr/lib/libgdbm.a       
RLIBS=  /usr/lib/libssl.a /usr/lib/libcrypto.a  /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread /usr/lib/libz.a /usr/lib/libgdbm.a     

#LIBS_DEP=client/libbos_client_d.a core_web1/libcoreweb_d.a core1/libcommon_d.a  
#RLIBS_DEP=client/libbos_client_r.a core_web1/libcoreweb_r.a core1/libcommon_r.a

#LIBS= /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a -lboost_regex-gcc-1_32  -lpthread -lz /usr/lib/libgdbm.a    
#RLIBS= /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a -lboost_regex-gcc-1_32  -lpthread -lz /usr/lib/libgdbm.a   

#LIBS= /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex.a -lpthread  -lgdbm   -static
#RLIBS=  /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex.a -lpthread  -lgdbm -static
##########################/usr/local/lib/libstlport_gcc.a 



LIBNAME=libchat_d.a
RLIBNAME=libchat_r.a
INC_DIRS= . ..  ../../../core_cs/bos_client ../../../core ../../../core_web  ../../../stdafx ../../../core_cs/common
TARGETS=ifree_client.cpp
	
OBJS= \
    rijndael.cpp\
    _mutex.cpp\
    mutex_inspector.cpp\
    errs.cpp\
    _mutex1.cpp\
    c_conn.cpp\
    tcp_stats.cpp\
    PTR.cpp\
    oscar_buffer.cpp\
    tcp_sender.cpp\
    threadable.cpp\
    str_lib.cpp\
    str_lib1.cpp\
    bos_client.cpp\
    st_rsa.cpp\
    server_config.cpp\
    file_set.cpp\
    st_stuff.cpp\
    st_FILE.cpp\
    wrappers.cpp\
    core_main.cpp\
    __main.cpp\
    tcp_sender.cpp\
    oscar_client.cpp\
    bos_client_interface.cpp\
    str_lib_extra.cpp\
    st_stream_str.cpp\
    

#ifree_client.cpp
	

#user_profile.cpp foto_profile.cpp 

#	web_adminfo.cpp

#tbl_user.cpp 
