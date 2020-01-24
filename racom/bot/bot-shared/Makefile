#check_path_wfn(./objR/kall)
#stat ./objR 0
#check_path_wfn(./objD/kall)
#stat ./objD 0

CFLAGS=  `cat _CFLAGS_D`  -I.

RCFLAGS= `cat _CFLAGS_R` -I.

LIBS= -lssl -lcrypto /usr/local/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a       -shared -Xlinker "--exclude-libs=libfmD.a" -v

RLIBS= -lssl -lcrypto /usr/local/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a      -shared -Xlinker "--exclude-libs=libfmR.a" -v

OBJDIR=./objD

ROBJDIR=./objR

all: ./libbot-shared_d.a 


./libbot-shared_d.a: \
	$(OBJDIR)/_QUERY.o\
	$(OBJDIR)/_mutex.o\
	$(OBJDIR)/antiflood.o\
	$(OBJDIR)/c_conn.o\
	$(OBJDIR)/config.o\
	$(OBJDIR)/errs.o\
	$(OBJDIR)/misc.o\
	$(OBJDIR)/mysql_extens.o\
	$(OBJDIR)/st_stuff.o\
	$(OBJDIR)/utils.o
		 ar -r ./libbot-shared_d.a $(OBJDIR)/_QUERY.o $(OBJDIR)/_mutex.o $(OBJDIR)/antiflood.o $(OBJDIR)/c_conn.o $(OBJDIR)/config.o $(OBJDIR)/errs.o $(OBJDIR)/misc.o $(OBJDIR)/mysql_extens.o $(OBJDIR)/st_stuff.o $(OBJDIR)/utils.o 

./objD/_mutex.o: _mutex.cpp errs.h _mutex.h str_lib.h
	 c++ $(CFLAGS) ./_mutex.cpp -o $(OBJDIR)/_mutex.o

./objD/antiflood.o: antiflood.cpp c_conn.h errs.h config.h utils.h misc.h \
  antiflood.h
	 c++ $(CFLAGS) ./antiflood.cpp -o $(OBJDIR)/antiflood.o

./objD/c_conn.o: c_conn.cpp c_conn.h errs.h
	 c++ $(CFLAGS) ./c_conn.cpp -o $(OBJDIR)/c_conn.o

./objD/config.o: config.cpp config.h utils.h errs.h
	 c++ $(CFLAGS) ./config.cpp -o $(OBJDIR)/config.o

./objD/errs.o: errs.cpp errs.h config.h
	 c++ $(CFLAGS) ./errs.cpp -o $(OBJDIR)/errs.o

./objD/misc.o: misc.cpp misc.h c_conn.h utils.h config.h errs.h
	 c++ $(CFLAGS) ./misc.cpp -o $(OBJDIR)/misc.o

./objD/mysql_extens.o: mysql_extens.cpp str_lib.h errs.h mysql_extens.h _QUERY.h \
  _mutex.h st_stuff.h m_var.h config.h
	 c++ $(CFLAGS) ./mysql_extens.cpp -o $(OBJDIR)/mysql_extens.o

./objD/st_stuff.o: st_stuff.cpp st_stuff.h errs.h str_lib.h _mutex.h
	 c++ $(CFLAGS) ./st_stuff.cpp -o $(OBJDIR)/st_stuff.o

release: ./libbot-shared_r.a 


./libbot-shared_r.a: \
	$(ROBJDIR)/_QUERY.o \
	$(ROBJDIR)/_mutex.o \
	$(ROBJDIR)/antiflood.o \
	$(ROBJDIR)/c_conn.o \
	$(ROBJDIR)/config.o \
	$(ROBJDIR)/errs.o \
	$(ROBJDIR)/misc.o \
	$(ROBJDIR)/mysql_extens.o \
	$(ROBJDIR)/st_stuff.o \
	$(ROBJDIR)/utils.o 
		 ar -r ./libbot-shared_r.a $(ROBJDIR)/_QUERY.o $(ROBJDIR)/_mutex.o $(ROBJDIR)/antiflood.o $(ROBJDIR)/c_conn.o $(ROBJDIR)/config.o $(ROBJDIR)/errs.o $(ROBJDIR)/misc.o $(ROBJDIR)/mysql_extens.o $(ROBJDIR)/st_stuff.o $(ROBJDIR)/utils.o 

./objR/_mutex.o: _mutex.cpp errs.h _mutex.h str_lib.h
	 c++ $(RCFLAGS) ./_mutex.cpp -o $(ROBJDIR)/_mutex.o

./objR/antiflood.o: antiflood.cpp c_conn.h errs.h config.h utils.h misc.h \
  antiflood.h
	 c++ $(RCFLAGS) ./antiflood.cpp -o $(ROBJDIR)/antiflood.o

./objR/c_conn.o: c_conn.cpp c_conn.h errs.h
	 c++ $(RCFLAGS) ./c_conn.cpp -o $(ROBJDIR)/c_conn.o

./objR/config.o: config.cpp config.h utils.h errs.h
	 c++ $(RCFLAGS) ./config.cpp -o $(ROBJDIR)/config.o

./objR/errs.o: errs.cpp errs.h config.h
	 c++ $(RCFLAGS) ./errs.cpp -o $(ROBJDIR)/errs.o

./objR/misc.o: misc.cpp misc.h c_conn.h utils.h config.h errs.h
	 c++ $(RCFLAGS) ./misc.cpp -o $(ROBJDIR)/misc.o

./objR/mysql_extens.o: mysql_extens.cpp str_lib.h errs.h mysql_extens.h _QUERY.h \
  _mutex.h st_stuff.h m_var.h config.h
	 c++ $(RCFLAGS) ./mysql_extens.cpp -o $(ROBJDIR)/mysql_extens.o

./objR/st_stuff.o: st_stuff.cpp st_stuff.h errs.h str_lib.h _mutex.h
	 c++ $(RCFLAGS) ./st_stuff.cpp -o $(ROBJDIR)/st_stuff.o

clean:
	 rm   z.out kaka.xxx file_dump.cpp TERM* 1 2

both: all release



cleanobjs:
	 rm $(OBJDIR)/_mutex.o $(OBJDIR)/antiflood.o $(OBJDIR)/c_conn.o $(OBJDIR)/config.o $(OBJDIR)/errs.o $(OBJDIR)/misc.o $(OBJDIR)/mysql_extens.o $(OBJDIR)/st_stuff.o $(ROBJDIR)/_mutex.o $(ROBJDIR)/antiflood.o $(ROBJDIR)/c_conn.o $(ROBJDIR)/config.o $(ROBJDIR)/errs.o $(ROBJDIR)/misc.o $(ROBJDIR)/mysql_extens.o $(ROBJDIR)/st_stuff.o ./libbot-shared_d.a ./libbot-shared_r.a


cleanall: clean cleanobjs


