OBJDIR=./objD
ROBJDIR=./objR

CFLAGS=  `cat ../_CFLAGS_D` 
RCFLAGS= `cat ../_CFLAGS_R`

LIBS= -lssl -lcrypto /usr/local/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a     /usr/local/lib/libGeoIP.a  -shared -Xlinker "--exclude-libs=libfmD.a" -v
RLIBS= -lssl -lcrypto /usr/local/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a   /usr/local/lib/libGeoIP.a   -shared -Xlinker "--exclude-libs=libfmR.a" -v




LIBNAME=./libcommon_d.a
RLIBNAME=./libcommon_r.a
INC_DIRS= . ../../core_web ../../core  ../../stdafx


TARGETS=


OBJS=PTR.cpp __main.cpp _mutex.cpp _mutex1.cpp copy_file_common.cpp core_main.cpp  db_var.cpp\
    des_sid.cpp errs.cpp file_set.cpp file_set_init.cpp mutex_inspector.cpp  oscar_buffer.cpp rijndael.cpp\
    server_config.cpp st_FILE.cpp st_rsa.cpp st_savecwd.cpp st_stuff.cpp str_lib.cpp str_lib1.cpp str_lib_extra.cpp wrappers.cpp\
    threadable.cpp st_stream_str.cpp mysql_extens.cpp mysql_extens2.cpp _QUERY.cpp  db_config2.cpp Double.cpp



	 
