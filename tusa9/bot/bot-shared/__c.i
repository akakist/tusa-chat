OBJDIR=./objD
ROBJDIR=./objR

CFLAGS=  `cat _CFLAGS_D` 
RCFLAGS= `cat _CFLAGS_R`

LIBS= -lssl -lcrypto -lmysqlient /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a       -shared -Xlinker "--exclude-libs=libfmD.a" -v
RLIBS= -lssl -lcrypto -lmysqlient /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a      -shared -Xlinker "--exclude-libs=libfmR.a" -v




LIBNAME=./libbot-shared_d.a
RLIBNAME=./libbot-shared_r.a
INC_DIRS= . 


TARGETS=


OBJS=_QUERY.cpp _mutex.cpp antiflood.cpp c_conn.cpp config.cpp errs.cpp misc.cpp  mysql_extens.cpp oscar_buffer.cpp st_stuff.cpp utils.cpp


	 
