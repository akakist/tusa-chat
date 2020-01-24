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

all: ./libbot-mafia_d.a mafia.exe 
mafia.exe: ./libbot-mafia_d.a  $(OBJDIR)/mafia.o
		c++ $(OBJDIR)/mafia.o -o mafia.exe ./libbot-mafia_d.a  $(LIBS) 
		 strip mafia.exe 


./libbot-mafia_d.a: \
	$(OBJDIR)/_QUERY.o\
	$(OBJDIR)/_mutex.o\
	$(OBJDIR)/antiflood.o\
	$(OBJDIR)/c_conn.o\
	$(OBJDIR)/command.o\
	$(OBJDIR)/config.o\
	$(OBJDIR)/day.o\
	$(OBJDIR)/errs.o\
	$(OBJDIR)/game.o\
	$(OBJDIR)/mafia.o\
	$(OBJDIR)/messages.o\
	$(OBJDIR)/misc.o\
	$(OBJDIR)/mysql_extens.o\
	$(OBJDIR)/night.o\
	$(OBJDIR)/st_stuff.o\
	$(OBJDIR)/user.o\
	$(OBJDIR)/utils.o
		 ar -r ./libbot-mafia_d.a $(OBJDIR)/_QUERY.o $(OBJDIR)/_mutex.o $(OBJDIR)/antiflood.o $(OBJDIR)/c_conn.o $(OBJDIR)/command.o $(OBJDIR)/config.o $(OBJDIR)/day.o $(OBJDIR)/errs.o $(OBJDIR)/game.o $(OBJDIR)/mafia.o $(OBJDIR)/messages.o $(OBJDIR)/misc.o $(OBJDIR)/mysql_extens.o $(OBJDIR)/night.o $(OBJDIR)/st_stuff.o $(OBJDIR)/user.o $(OBJDIR)/utils.o 

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

./objD/command.o: command.cpp command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/utils.h mafia.h \
  ../bot-shared/c_conn.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h ../bot-shared/_mutex.h ../bot-shared/errs.h \
  game.h user.h messages.h ../bot-shared/config.h night.h day.h \
  ../bot-shared/antiflood.h ../bot-shared/misc.h
	 c++ $(CFLAGS) ./command.cpp -o $(OBJDIR)/command.o

./objD/config.o: ../bot-shared/config.cpp ../bot-shared/config.h \
  ../bot-shared/utils.h ../bot-shared/errs.h
	 c++ $(CFLAGS) ../bot-shared/config.cpp -o $(OBJDIR)/config.o

./objD/day.o: day.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h messages.h user.h ../bot-shared/utils.h \
  ../bot-shared/config.h day.h night.h ../bot-shared/errs.h
	 c++ $(CFLAGS) ./day.cpp -o $(OBJDIR)/day.o

./objD/errs.o: ../bot-shared/errs.cpp ../bot-shared/errs.h \
  ../bot-shared/config.h
	 c++ $(CFLAGS) ../bot-shared/errs.cpp -o $(OBJDIR)/errs.o

./objD/game.o: game.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h messages.h user.h ../bot-shared/utils.h \
  ../bot-shared/config.h night.h day.h ../bot-shared/errs.h
	 c++ $(CFLAGS) ./game.cpp -o $(OBJDIR)/game.o

./objD/mafia.o: mafia.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h mafia.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h user.h game.h messages.h ../bot-shared/config.h \
  ../bot-shared/utils.h
	 c++ $(CFLAGS) ./mafia.cpp -o $(OBJDIR)/mafia.o

./objD/messages.o: messages.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h ../bot-shared/errs.h \
  ../bot-shared/utils.h
	 c++ $(CFLAGS) ./messages.cpp -o $(OBJDIR)/messages.o

./objD/misc.o: ../bot-shared/misc.cpp ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/utils.h ../bot-shared/config.h \
  ../bot-shared/errs.h
	 c++ $(CFLAGS) ../bot-shared/misc.cpp -o $(OBJDIR)/misc.o

./objD/mysql_extens.o: ../bot-shared/mysql_extens.cpp ../bot-shared/str_lib.h \
  ../bot-shared/errs.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h ../bot-shared/_mutex.h ../bot-shared/st_stuff.h \
  ../bot-shared/m_var.h ../bot-shared/config.h
	 c++ $(CFLAGS) ../bot-shared/mysql_extens.cpp -o $(OBJDIR)/mysql_extens.o

./objD/night.o: night.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h messages.h user.h ../bot-shared/utils.h \
  ../bot-shared/config.h night.h ../bot-shared/errs.h
	 c++ $(CFLAGS) ./night.cpp -o $(OBJDIR)/night.o

./objD/st_stuff.o: ../bot-shared/st_stuff.cpp ../bot-shared/st_stuff.h \
  ../bot-shared/errs.h ../bot-shared/str_lib.h ../bot-shared/_mutex.h
	 c++ $(CFLAGS) ../bot-shared/st_stuff.cpp -o $(OBJDIR)/st_stuff.o

./objD/user.o: user.cpp user.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/utils.h mafia.h \
  ../bot-shared/c_conn.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h ../bot-shared/_mutex.h game.h \
  ../bot-shared/config.h ../bot-shared/errs.h
	 c++ $(CFLAGS) ./user.cpp -o $(OBJDIR)/user.o

./objD/utils.o: ../bot-shared/utils.cpp ../bot-shared/utils.h \
  ../bot-shared/errs.h
	 c++ $(CFLAGS) ../bot-shared/utils.cpp -o $(OBJDIR)/utils.o

release: ./libot-mafia_r.a mafia.release.exe 
mafia.release.exe: ./libot-mafia_r.a  $(ROBJDIR)/mafia.o
		c++ $(ROBJDIR)/mafia.o -o mafia.release.exe ./libot-mafia_r.a  $(RLIBS)
		 strip mafia.release.exe 


./libot-mafia_r.a: \
	$(ROBJDIR)/_QUERY.o \
	$(ROBJDIR)/_mutex.o \
	$(ROBJDIR)/antiflood.o \
	$(ROBJDIR)/c_conn.o \
	$(ROBJDIR)/command.o \
	$(ROBJDIR)/config.o \
	$(ROBJDIR)/day.o \
	$(ROBJDIR)/errs.o \
	$(ROBJDIR)/game.o \
	$(ROBJDIR)/mafia.o \
	$(ROBJDIR)/messages.o \
	$(ROBJDIR)/misc.o \
	$(ROBJDIR)/mysql_extens.o \
	$(ROBJDIR)/night.o \
	$(ROBJDIR)/st_stuff.o \
	$(ROBJDIR)/user.o \
	$(ROBJDIR)/utils.o 
		 ar -r ./libot-mafia_r.a $(ROBJDIR)/_QUERY.o $(ROBJDIR)/_mutex.o $(ROBJDIR)/antiflood.o $(ROBJDIR)/c_conn.o $(ROBJDIR)/command.o $(ROBJDIR)/config.o $(ROBJDIR)/day.o $(ROBJDIR)/errs.o $(ROBJDIR)/game.o $(ROBJDIR)/mafia.o $(ROBJDIR)/messages.o $(ROBJDIR)/misc.o $(ROBJDIR)/mysql_extens.o $(ROBJDIR)/night.o $(ROBJDIR)/st_stuff.o $(ROBJDIR)/user.o $(ROBJDIR)/utils.o 

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

./objR/command.o: command.cpp command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/utils.h mafia.h \
  ../bot-shared/c_conn.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h ../bot-shared/_mutex.h ../bot-shared/errs.h \
  game.h user.h messages.h ../bot-shared/config.h night.h day.h \
  ../bot-shared/antiflood.h ../bot-shared/misc.h
	 c++ $(RCFLAGS) ./command.cpp -o $(ROBJDIR)/command.o

./objR/config.o: ../bot-shared/config.cpp ../bot-shared/config.h \
  ../bot-shared/utils.h ../bot-shared/errs.h
	 c++ $(RCFLAGS) ../bot-shared/config.cpp -o $(ROBJDIR)/config.o

./objR/day.o: day.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h messages.h user.h ../bot-shared/utils.h \
  ../bot-shared/config.h day.h night.h ../bot-shared/errs.h
	 c++ $(RCFLAGS) ./day.cpp -o $(ROBJDIR)/day.o

./objR/errs.o: ../bot-shared/errs.cpp ../bot-shared/errs.h \
  ../bot-shared/config.h
	 c++ $(RCFLAGS) ../bot-shared/errs.cpp -o $(ROBJDIR)/errs.o

./objR/game.o: game.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h messages.h user.h ../bot-shared/utils.h \
  ../bot-shared/config.h night.h day.h ../bot-shared/errs.h
	 c++ $(RCFLAGS) ./game.cpp -o $(ROBJDIR)/game.o

./objR/mafia.o: mafia.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h mafia.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h user.h game.h messages.h ../bot-shared/config.h \
  ../bot-shared/utils.h
	 c++ $(RCFLAGS) ./mafia.cpp -o $(ROBJDIR)/mafia.o

./objR/messages.o: messages.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h ../bot-shared/errs.h \
  ../bot-shared/utils.h
	 c++ $(RCFLAGS) ./messages.cpp -o $(ROBJDIR)/messages.o

./objR/misc.o: ../bot-shared/misc.cpp ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/utils.h ../bot-shared/config.h \
  ../bot-shared/errs.h
	 c++ $(RCFLAGS) ../bot-shared/misc.cpp -o $(ROBJDIR)/misc.o

./objR/mysql_extens.o: ../bot-shared/mysql_extens.cpp ../bot-shared/str_lib.h \
  ../bot-shared/errs.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h ../bot-shared/_mutex.h ../bot-shared/st_stuff.h \
  ../bot-shared/m_var.h ../bot-shared/config.h
	 c++ $(RCFLAGS) ../bot-shared/mysql_extens.cpp -o $(ROBJDIR)/mysql_extens.o

./objR/night.o: night.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h messages.h user.h ../bot-shared/utils.h \
  ../bot-shared/config.h night.h ../bot-shared/errs.h
	 c++ $(RCFLAGS) ./night.cpp -o $(ROBJDIR)/night.o

./objR/st_stuff.o: ../bot-shared/st_stuff.cpp ../bot-shared/st_stuff.h \
  ../bot-shared/errs.h ../bot-shared/str_lib.h ../bot-shared/_mutex.h
	 c++ $(RCFLAGS) ../bot-shared/st_stuff.cpp -o $(ROBJDIR)/st_stuff.o

./objR/user.o: user.cpp user.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/utils.h mafia.h \
  ../bot-shared/c_conn.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h ../bot-shared/_mutex.h game.h \
  ../bot-shared/config.h ../bot-shared/errs.h
	 c++ $(RCFLAGS) ./user.cpp -o $(ROBJDIR)/user.o

./objR/utils.o: ../bot-shared/utils.cpp ../bot-shared/utils.h \
  ../bot-shared/errs.h
	 c++ $(RCFLAGS) ../bot-shared/utils.cpp -o $(ROBJDIR)/utils.o

clean:
	 rm mafia.exe mafia.release.exe z.out kaka.xxx file_dump.cpp TERM* 1 2

both: all release



cleanobjs:
	 rm $(OBJDIR)/_QUERY.o $(OBJDIR)/_mutex.o $(OBJDIR)/antiflood.o $(OBJDIR)/c_conn.o $(OBJDIR)/command.o $(OBJDIR)/config.o $(OBJDIR)/day.o $(OBJDIR)/errs.o $(OBJDIR)/game.o $(OBJDIR)/mafia.o $(OBJDIR)/messages.o $(OBJDIR)/misc.o $(OBJDIR)/mysql_extens.o $(OBJDIR)/night.o $(OBJDIR)/st_stuff.o $(OBJDIR)/user.o $(OBJDIR)/utils.o $(ROBJDIR)/_QUERY.o $(ROBJDIR)/_mutex.o $(ROBJDIR)/antiflood.o $(ROBJDIR)/c_conn.o $(ROBJDIR)/command.o $(ROBJDIR)/config.o $(ROBJDIR)/day.o $(ROBJDIR)/errs.o $(ROBJDIR)/game.o $(ROBJDIR)/mafia.o $(ROBJDIR)/messages.o $(ROBJDIR)/misc.o $(ROBJDIR)/mysql_extens.o $(ROBJDIR)/night.o $(ROBJDIR)/st_stuff.o $(ROBJDIR)/user.o $(ROBJDIR)/utils.o ./libbot-mafia_d.a ./libot-mafia_r.a


cleanall: clean cleanobjs


