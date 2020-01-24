#check_path_wfn(./objR/kall)
#stat ./objR 0
#check_path_wfn(./objD/kall)
#stat ./objD 0

CFLAGS= `cat _CFLAGS_D` -I. -I../chatserver -I../chatserver/_admin -I../chatserver/_forum -I../chatserver/_irc -I../chatserver/_lib -I../chatserver/cs_stuff -I../chatserver/data -I../chatserver/io_stuff -I../chatserver/klan -I../chatserver/lib_cs -I../chatserver/mcassa -I../core -I../core_web -I../kall -I../stdafx -I../zdes -I_conf

RCFLAGS= `cat _CFLAGS_R` -I. -I../chatserver -I../chatserver/_admin -I../chatserver/_forum -I../chatserver/_irc -I../chatserver/_lib -I../chatserver/cs_stuff -I../chatserver/data -I../chatserver/io_stuff -I../chatserver/klan -I../chatserver/lib_cs -I../chatserver/mcassa -I../core -I../core_web -I../kall -I../stdafx -I../zdes -I_conf

LIBS=  /usr/local/lib/libstlport.a /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/local/lib/mysql/libmysqlclient.a    -lpthread -lz /usr/lib/libgdbm.a  -static   

RLIBS= /usr/local/lib/libstlport.a /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/local/lib/mysql/libmysqlclient.a   -lpthread -lz /usr/lib/libgdbm.a  -static  

OBJDIR=./objD

ROBJDIR=./objR

