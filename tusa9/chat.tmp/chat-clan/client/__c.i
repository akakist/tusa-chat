OBJDIR=./objD
ROBJDIR=./objR

CFLAGS=  `cat ../_CFLAGS_D` 
RCFLAGS= `cat ../_CFLAGS_R`

LIBS= -lssl -lcrypto /usr/local/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a     /usr/local/lib/libGeoIP.a  -shared -Xlinker "--exclude-libs=libfmD.a" -v
RLIBS= -lssl -lcrypto /usr/local/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a   /usr/local/lib/libGeoIP.a   -shared -Xlinker "--exclude-libs=libfmR.a" -v




LIBNAME=./libbos_client_d.a
RLIBNAME=./libbos_client_r.a
INC_DIRS= . ../../core   ../../core_web ../../stdafx ../../core_cs/common ../../chatserver


TARGETS=


OBJS=bos_client.cpp bos_client_interface.cpp

