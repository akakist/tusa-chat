#check_path_wfn(./objR/kall)
#stat ./objR 0
#check_path_wfn(./objD/kall)
#stat ./objD 0

CFLAGS=  `cat _CFLAGS_D`  -I. -I../bot-shared

RCFLAGS= `cat _CFLAGS_R` -I. -I../bot-shared

LIBS= /usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/local/lib/mysql/libmysqlclient.a  -lpthread -lz /usr/lib/libgdbm.a   

RLIBS=/usr/local/ssl/lib/libssl.a /usr/local/ssl/lib/libcrypto.a /usr/local/lib/mysql/libmysqlclient.a  -lpthread -lz /usr/lib/libgdbm.a  

OBJDIR=./objD

ROBJDIR=./objR

all: ./libbot-roulette_d.a roulette.exe 
roulette.exe: ./libbot-roulette_d.a  $(OBJDIR)/roulette.o
		c++ $(OBJDIR)/roulette.o -o roulette.exe ./libbot-roulette_d.a  $(LIBS) 
		 strip roulette.exe 


./libbot-roulette_d.a: \
	$(OBJDIR)/_QUERY.o\
	$(OBJDIR)/_mutex.o\
	$(OBJDIR)/antiflood.o\
	$(OBJDIR)/c_conn.o\
	$(OBJDIR)/config.o\
	$(OBJDIR)/errs.o\
	$(OBJDIR)/game.o\
	$(OBJDIR)/misc.o\
	$(OBJDIR)/mysql_extens.o\
	$(OBJDIR)/st_stuff.o\
	$(OBJDIR)/utils.o
		 ar -r ./libbot-roulette_d.a $(OBJDIR)/_QUERY.o $(OBJDIR)/_mutex.o $(OBJDIR)/antiflood.o $(OBJDIR)/c_conn.o $(OBJDIR)/config.o $(OBJDIR)/errs.o $(OBJDIR)/game.o $(OBJDIR)/misc.o $(OBJDIR)/mysql_extens.o $(OBJDIR)/st_stuff.o $(OBJDIR)/utils.o 

./objD/_QUERY.o: ../bot-shared/_QUERY.cpp ../bot-shared/_QUERY.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_mutex.h \
  ../bot-shared/utils.h ../bot-shared/errs.h
	 c++ $(CFLAGS) ../bot-shared/_QUERY.cpp -o $(OBJDIR)/_QUERY.o

./objD/_mutex.o: ../bot-shared/_mutex.cpp ../bot-shared/errs.h \
  ../bot-shared/_mutex.h ../bot-shared/str_lib.h
	 c++ $(CFLAGS) ../bot-shared/_mutex.cpp -o $(OBJDIR)/_mutex.o

./objD/antiflood.o: ../bot-shared/antiflood.cpp ../bot-shared/c_conn.h \
  ../bot-shared/errs.h ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/misc.h ../bot-shared/antiflood.h
	 c++ $(CFLAGS) ../bot-shared/antiflood.cpp -o $(OBJDIR)/antiflood.o

./objD/c_conn.o: ../bot-shared/c_conn.cpp ../bot-shared/c_conn.h \
  ../bot-shared/errs.h
	 c++ $(CFLAGS) ../bot-shared/c_conn.cpp -o $(OBJDIR)/c_conn.o

./objD/config.o: ../bot-shared/config.cpp ../bot-shared/config.h \
  ../bot-shared/utils.h ../bot-shared/errs.h
	 c++ $(CFLAGS) ../bot-shared/config.cpp -o $(OBJDIR)/config.o

./objD/errs.o: ../bot-shared/errs.cpp ../bot-shared/errs.h \
  ../bot-shared/config.h
	 c++ $(CFLAGS) ../bot-shared/errs.cpp -o $(OBJDIR)/errs.o

./objD/game.o: game.cpp stdafx.h ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h ../bot-shared/_mutex.h roulette.h \
  ../bot-shared/antiflood.h ../bot-shared/misc.h
	 c++ $(CFLAGS) ./game.cpp -o $(OBJDIR)/game.o

./objD/misc.o: ../bot-shared/misc.cpp ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/utils.h ../bot-shared/config.h \
  ../bot-shared/errs.h
	 c++ $(CFLAGS) ../bot-shared/misc.cpp -o $(OBJDIR)/misc.o

./objD/mysql_extens.o: ../bot-shared/mysql_extens.cpp ../bot-shared/str_lib.h \
  ../bot-shared/errs.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h ../bot-shared/_mutex.h ../bot-shared/st_stuff.h \
  ../bot-shared/m_var.h ../bot-shared/config.h
	 c++ $(CFLAGS) ../bot-shared/mysql_extens.cpp -o $(OBJDIR)/mysql_extens.o

./objD/roulette.o: roulette.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h ../bot-shared/_mutex.h game.h roulette.h
	 c++ $(CFLAGS) ./roulette.cpp -o $(OBJDIR)/roulette.o

./objD/st_stuff.o: ../bot-shared/st_stuff.cpp ../bot-shared/st_stuff.h \
  ../bot-shared/errs.h ../bot-shared/str_lib.h ../bot-shared/_mutex.h
	 c++ $(CFLAGS) ../bot-shared/st_stuff.cpp -o $(OBJDIR)/st_stuff.o

./objD/utils.o: ../bot-shared/utils.cpp ../bot-shared/utils.h \
  ../bot-shared/errs.h
	 c++ $(CFLAGS) ../bot-shared/utils.cpp -o $(OBJDIR)/utils.o

release: ./libot-roulette_r.a roulette.release.exe 
roulette.release.exe: ./libot-roulette_r.a  $(ROBJDIR)/roulette.o
		c++ $(ROBJDIR)/roulette.o -o roulette.release.exe ./libot-roulette_r.a  $(RLIBS)
		 strip roulette.release.exe 


./libot-roulette_r.a: \
	$(ROBJDIR)/_QUERY.o \
	$(ROBJDIR)/_mutex.o \
	$(ROBJDIR)/antiflood.o \
	$(ROBJDIR)/c_conn.o \
	$(ROBJDIR)/config.o \
	$(ROBJDIR)/errs.o \
	$(ROBJDIR)/game.o \
	$(ROBJDIR)/misc.o \
	$(ROBJDIR)/mysql_extens.o \
	$(ROBJDIR)/st_stuff.o \
	$(ROBJDIR)/utils.o 
		 ar -r ./libot-roulette_r.a $(ROBJDIR)/_QUERY.o $(ROBJDIR)/_mutex.o $(ROBJDIR)/antiflood.o $(ROBJDIR)/c_conn.o $(ROBJDIR)/config.o $(ROBJDIR)/errs.o $(ROBJDIR)/game.o $(ROBJDIR)/misc.o $(ROBJDIR)/mysql_extens.o $(ROBJDIR)/st_stuff.o $(ROBJDIR)/utils.o 

./objR/_QUERY.o: ../bot-shared/_QUERY.cpp ../bot-shared/_QUERY.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_mutex.h \
  ../bot-shared/utils.h ../bot-shared/errs.h
	 c++ $(RCFLAGS) ../bot-shared/_QUERY.cpp -o $(ROBJDIR)/_QUERY.o

./objR/_mutex.o: ../bot-shared/_mutex.cpp ../bot-shared/errs.h \
  ../bot-shared/_mutex.h ../bot-shared/str_lib.h
	 c++ $(RCFLAGS) ../bot-shared/_mutex.cpp -o $(ROBJDIR)/_mutex.o

./objR/antiflood.o: ../bot-shared/antiflood.cpp ../bot-shared/c_conn.h \
  ../bot-shared/errs.h ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/misc.h ../bot-shared/antiflood.h
	 c++ $(RCFLAGS) ../bot-shared/antiflood.cpp -o $(ROBJDIR)/antiflood.o

./objR/c_conn.o: ../bot-shared/c_conn.cpp ../bot-shared/c_conn.h \
  ../bot-shared/errs.h
	 c++ $(RCFLAGS) ../bot-shared/c_conn.cpp -o $(ROBJDIR)/c_conn.o

./objR/config.o: ../bot-shared/config.cpp ../bot-shared/config.h \
  ../bot-shared/utils.h ../bot-shared/errs.h
	 c++ $(RCFLAGS) ../bot-shared/config.cpp -o $(ROBJDIR)/config.o

./objR/errs.o: ../bot-shared/errs.cpp ../bot-shared/errs.h \
  ../bot-shared/config.h
	 c++ $(RCFLAGS) ../bot-shared/errs.cpp -o $(ROBJDIR)/errs.o

./objR/game.o: game.cpp stdafx.h ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h ../bot-shared/_mutex.h roulette.h \
  ../bot-shared/antiflood.h ../bot-shared/misc.h
	 c++ $(RCFLAGS) ./game.cpp -o $(ROBJDIR)/game.o

./objR/misc.o: ../bot-shared/misc.cpp ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/utils.h ../bot-shared/config.h \
  ../bot-shared/errs.h
	 c++ $(RCFLAGS) ../bot-shared/misc.cpp -o $(ROBJDIR)/misc.o

./objR/mysql_extens.o: ../bot-shared/mysql_extens.cpp ../bot-shared/str_lib.h \
  ../bot-shared/errs.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h ../bot-shared/_mutex.h ../bot-shared/st_stuff.h \
  ../bot-shared/m_var.h ../bot-shared/config.h
	 c++ $(RCFLAGS) ../bot-shared/mysql_extens.cpp -o $(ROBJDIR)/mysql_extens.o

./objR/roulette.o: roulette.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h ../bot-shared/_mutex.h game.h roulette.h
	 c++ $(RCFLAGS) ./roulette.cpp -o $(ROBJDIR)/roulette.o

./objR/st_stuff.o: ../bot-shared/st_stuff.cpp ../bot-shared/st_stuff.h \
  ../bot-shared/errs.h ../bot-shared/str_lib.h ../bot-shared/_mutex.h
	 c++ $(RCFLAGS) ../bot-shared/st_stuff.cpp -o $(ROBJDIR)/st_stuff.o

./objR/utils.o: ../bot-shared/utils.cpp ../bot-shared/utils.h \
  ../bot-shared/errs.h
	 c++ $(RCFLAGS) ../bot-shared/utils.cpp -o $(ROBJDIR)/utils.o

clean:
	 rm roulette.exe roulette.release.exe z.out kaka.xxx file_dump.cpp TERM* 1 2

both: all release



cleanobjs:
	 rm $(OBJDIR)/_QUERY.o $(OBJDIR)/_mutex.o $(OBJDIR)/antiflood.o $(OBJDIR)/c_conn.o $(OBJDIR)/config.o $(OBJDIR)/errs.o $(OBJDIR)/game.o $(OBJDIR)/misc.o $(OBJDIR)/mysql_extens.o $(OBJDIR)/roulette.o $(OBJDIR)/st_stuff.o $(OBJDIR)/utils.o $(ROBJDIR)/_QUERY.o $(ROBJDIR)/_mutex.o $(ROBJDIR)/antiflood.o $(ROBJDIR)/c_conn.o $(ROBJDIR)/config.o $(ROBJDIR)/errs.o $(ROBJDIR)/game.o $(ROBJDIR)/misc.o $(ROBJDIR)/mysql_extens.o $(ROBJDIR)/roulette.o $(ROBJDIR)/st_stuff.o $(ROBJDIR)/utils.o ./libbot-roulette_d.a ./libot-roulette_r.a


cleanall: clean cleanobjs


