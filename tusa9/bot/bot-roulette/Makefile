#check_path_wfn(./objR/kall)
#stat ./objR 0
#check_path_wfn(./objD/kall)
#stat ./objD 0

CFLAGS=  `cat _CFLAGS_D`  -I. -I../bot-shared

RCFLAGS= `cat _CFLAGS_R` -I. -I../bot-shared

LIBS=  `cat _LFLAGS_D` 

RLIBS= `cat _LFLAGS_R`

OBJDIR=./objD

ROBJDIR=./objR

all: ./libbot-roulette_d.a roulette.exe 
roulette.exe: ./libbot-roulette_d.a ../bot-shared/libbot-shared_d.a $(OBJDIR)/roulette.o
		c++ $(OBJDIR)/roulette.o -o roulette.exe ./libbot-roulette_d.a ../bot-shared/libbot-shared_d.a $(LIBS) 
		 strip roulette.exe 


./libbot-roulette_d.a: \
	$(OBJDIR)/game.o
		 ar -r ./libbot-roulette_d.a $(OBJDIR)/game.o 

./objD/game.o: game.cpp stdafx.h ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h roulette.h \
  ../bot-shared/antiflood.h ../bot-shared/misc.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/mutex_inspector.h \
  ../bot-shared/errs.h
	 c++ $(CFLAGS) ./game.cpp -o $(OBJDIR)/game.o

./objD/roulette.o: roulette.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h game.h roulette.h
	 c++ $(CFLAGS) ./roulette.cpp -o $(OBJDIR)/roulette.o

release: ./libot-roulette_r.a roulette.release.exe 
roulette.release.exe: ./libot-roulette_r.a ../bot-shared/libbot-shared_r.a $(ROBJDIR)/roulette.o
		c++ $(ROBJDIR)/roulette.o -o roulette.release.exe ./libot-roulette_r.a ../bot-shared/libbot-shared_r.a $(RLIBS)
		 strip roulette.release.exe 


./libot-roulette_r.a: \
	$(ROBJDIR)/game.o 
		 ar -r ./libot-roulette_r.a $(ROBJDIR)/game.o 

./objR/game.o: game.cpp stdafx.h ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h roulette.h \
  ../bot-shared/antiflood.h ../bot-shared/misc.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/mutex_inspector.h \
  ../bot-shared/errs.h
	 c++ $(RCFLAGS) ./game.cpp -o $(ROBJDIR)/game.o

./objR/roulette.o: roulette.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h game.h roulette.h
	 c++ $(RCFLAGS) ./roulette.cpp -o $(ROBJDIR)/roulette.o

clean:
	 rm roulette.exe roulette.release.exe z.out kaka.xxx file_dump.cpp TERM* 1 2

both: all release



cleanobjs:
	 rm $(OBJDIR)/game.o $(OBJDIR)/roulette.o $(ROBJDIR)/game.o $(ROBJDIR)/roulette.o ./libbot-roulette_d.a ./libot-roulette_r.a


cleanall: clean cleanobjs


