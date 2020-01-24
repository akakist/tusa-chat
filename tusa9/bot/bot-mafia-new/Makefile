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

all: ./libbot-mafia_d.a mafia.exe 
mafia.exe: ./libbot-mafia_d.a ../bot-shared/libbot-shared_d.a $(OBJDIR)/mafia.o
		c++ $(OBJDIR)/mafia.o -o mafia.exe ./libbot-mafia_d.a ../bot-shared/libbot-shared_d.a $(LIBS) 
		 strip mafia.exe 


./libbot-mafia_d.a: \
	$(OBJDIR)/command.o\
	$(OBJDIR)/day.o\
	$(OBJDIR)/game.o\
	$(OBJDIR)/mafia.o\
	$(OBJDIR)/messages.o\
	$(OBJDIR)/night.o\
	$(OBJDIR)/user.o
		 ar -r ./libbot-mafia_d.a $(OBJDIR)/command.o $(OBJDIR)/day.o $(OBJDIR)/game.o $(OBJDIR)/mafia.o $(OBJDIR)/messages.o $(OBJDIR)/night.o $(OBJDIR)/user.o 

./objD/command.o: command.cpp command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h mafia.h \
  ../bot-shared/c_conn.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h ../bot-shared/errs.h game.h user.h messages.h \
  ../bot-shared/config.h night.h day.h ../bot-shared/antiflood.h \
  ../bot-shared/misc.h ../bot-shared/mutex_inspector.h \
  ../bot-shared/errs.h
	 c++ $(CFLAGS) ./command.cpp -o $(OBJDIR)/command.o

./objD/day.o: day.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h messages.h user.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/config.h day.h night.h \
  ../bot-shared/errs.h ../bot-shared/mutex_inspector.h \
  ../bot-shared/errs.h
	 c++ $(CFLAGS) ./day.cpp -o $(OBJDIR)/day.o

./objD/game.o: game.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h messages.h user.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/config.h night.h day.h \
  ../bot-shared/errs.h ../bot-shared/mutex_inspector.h \
  ../bot-shared/errs.h
	 c++ $(CFLAGS) ./game.cpp -o $(OBJDIR)/game.o

./objD/mafia.o: mafia.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h mafia.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h user.h game.h messages.h ../bot-shared/config.h \
  ../bot-shared/utils.h ../bot-shared/oscar_buffer.h \
  ../bot-shared/mutex_inspector.h ../bot-shared/errs.h
	 c++ $(CFLAGS) ./mafia.cpp -o $(OBJDIR)/mafia.o

./objD/messages.o: messages.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h ../bot-shared/errs.h \
  ../bot-shared/utils.h ../bot-shared/oscar_buffer.h \
  ../bot-shared/mutex_inspector.h ../bot-shared/errs.h
	 c++ $(CFLAGS) ./messages.cpp -o $(OBJDIR)/messages.o

./objD/night.o: night.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h messages.h user.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/config.h night.h \
  ../bot-shared/errs.h ../bot-shared/mutex_inspector.h \
  ../bot-shared/errs.h
	 c++ $(CFLAGS) ./night.cpp -o $(OBJDIR)/night.o

./objD/user.o: user.cpp user.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h mafia.h \
  ../bot-shared/c_conn.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h game.h ../bot-shared/config.h \
  ../bot-shared/errs.h ../bot-shared/mutex_inspector.h \
  ../bot-shared/errs.h
	 c++ $(CFLAGS) ./user.cpp -o $(OBJDIR)/user.o

release: ./libot-mafia_r.a mafia.release.exe 
mafia.release.exe: ./libot-mafia_r.a ../bot-shared/libbot-shared_r.a $(ROBJDIR)/mafia.o
		c++ $(ROBJDIR)/mafia.o -o mafia.release.exe ./libot-mafia_r.a ../bot-shared/libbot-shared_r.a $(RLIBS)
		 strip mafia.release.exe 


./libot-mafia_r.a: \
	$(ROBJDIR)/command.o \
	$(ROBJDIR)/day.o \
	$(ROBJDIR)/game.o \
	$(ROBJDIR)/mafia.o \
	$(ROBJDIR)/messages.o \
	$(ROBJDIR)/night.o \
	$(ROBJDIR)/user.o 
		 ar -r ./libot-mafia_r.a $(ROBJDIR)/command.o $(ROBJDIR)/day.o $(ROBJDIR)/game.o $(ROBJDIR)/mafia.o $(ROBJDIR)/messages.o $(ROBJDIR)/night.o $(ROBJDIR)/user.o 

./objR/command.o: command.cpp command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h mafia.h \
  ../bot-shared/c_conn.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h ../bot-shared/errs.h game.h user.h messages.h \
  ../bot-shared/config.h night.h day.h ../bot-shared/antiflood.h \
  ../bot-shared/misc.h ../bot-shared/mutex_inspector.h \
  ../bot-shared/errs.h
	 c++ $(RCFLAGS) ./command.cpp -o $(ROBJDIR)/command.o

./objR/day.o: day.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h messages.h user.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/config.h day.h night.h \
  ../bot-shared/errs.h ../bot-shared/mutex_inspector.h \
  ../bot-shared/errs.h
	 c++ $(RCFLAGS) ./day.cpp -o $(ROBJDIR)/day.o

./objR/game.o: game.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h messages.h user.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/config.h night.h day.h \
  ../bot-shared/errs.h ../bot-shared/mutex_inspector.h \
  ../bot-shared/errs.h
	 c++ $(RCFLAGS) ./game.cpp -o $(ROBJDIR)/game.o

./objR/mafia.o: mafia.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h mafia.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h user.h game.h messages.h ../bot-shared/config.h \
  ../bot-shared/utils.h ../bot-shared/oscar_buffer.h \
  ../bot-shared/mutex_inspector.h ../bot-shared/errs.h
	 c++ $(RCFLAGS) ./mafia.cpp -o $(ROBJDIR)/mafia.o

./objR/messages.o: messages.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h ../bot-shared/errs.h \
  ../bot-shared/utils.h ../bot-shared/oscar_buffer.h \
  ../bot-shared/mutex_inspector.h ../bot-shared/errs.h
	 c++ $(RCFLAGS) ./messages.cpp -o $(ROBJDIR)/messages.o

./objR/night.o: night.cpp mafia.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h \
  ../bot-shared/_mutex.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h game.h messages.h user.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/config.h night.h \
  ../bot-shared/errs.h ../bot-shared/mutex_inspector.h \
  ../bot-shared/errs.h
	 c++ $(RCFLAGS) ./night.cpp -o $(ROBJDIR)/night.o

./objR/user.o: user.cpp user.h command.h ../bot-shared/misc.h \
  ../bot-shared/c_conn.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h mafia.h \
  ../bot-shared/c_conn.h ../bot-shared/mysql_extens.h \
  ../bot-shared/_QUERY.h game.h ../bot-shared/config.h \
  ../bot-shared/errs.h ../bot-shared/mutex_inspector.h \
  ../bot-shared/errs.h
	 c++ $(RCFLAGS) ./user.cpp -o $(ROBJDIR)/user.o

clean:
	 rm mafia.exe mafia.release.exe z.out kaka.xxx file_dump.cpp TERM* 1 2

both: all release



cleanobjs:
	 rm $(OBJDIR)/command.o $(OBJDIR)/day.o $(OBJDIR)/game.o $(OBJDIR)/mafia.o $(OBJDIR)/messages.o $(OBJDIR)/night.o $(OBJDIR)/user.o $(ROBJDIR)/command.o $(ROBJDIR)/day.o $(ROBJDIR)/game.o $(ROBJDIR)/mafia.o $(ROBJDIR)/messages.o $(ROBJDIR)/night.o $(ROBJDIR)/user.o ./libbot-mafia_d.a ./libot-mafia_r.a


cleanall: clean cleanobjs


