OBJDIR=./objD
ROBJDIR=./objR

CFLAGS=  `cat _CFLAGS_D` 
RCFLAGS= `cat _CFLAGS_R`

LIBS= /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/local/lib/mysql/libmysqlclient.a  -lpthread -lz /usr/lib/libgdbm.a   
RLIBS=/usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/local/lib/mysql/libmysqlclient.a  -lpthread -lz /usr/lib/libgdbm.a  
EXT=exe



LIBNAME=./libbot-mafia_d.a
RLIBNAME=./libot-mafia_r.a
INC_DIRS= . ../bot-shared


TARGETS=mafia.cpp 


OBJS=command.cpp day.cpp game.cpp mafia.cpp messages.cpp night.cpp user.cpp _QUERY.cpp _mutex.cpp antiflood.cpp c_conn.cpp config.cpp errs.cpp misc.cpp  mysql_extens.cpp st_stuff.cpp utils.cpp



	 
