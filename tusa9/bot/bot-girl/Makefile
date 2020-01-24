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

all: ./libbot-girl_d.a girl.exe 
girl.exe: ./libbot-girl_d.a ../bot-shared/libbot-shared_d.a $(OBJDIR)/girl.o
		c++ $(OBJDIR)/girl.o -o girl.exe ./libbot-girl_d.a ../bot-shared/libbot-shared_d.a $(LIBS) 
		 strip girl.exe 


./libbot-girl_d.a: \
	$(OBJDIR)/cmd.o
		 ar -r ./libbot-girl_d.a $(OBJDIR)/cmd.o 

./objD/cmd.o: cmd.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h girl.h \
  ../bot-shared/antiflood.h ../bot-shared/misc.h cmd.h \
  ../bot-shared/mutex_inspector.h ../bot-shared/errs.h
	 c++ $(CFLAGS) ./cmd.cpp -o $(OBJDIR)/cmd.o

./objD/girl.o: girl.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h cmd.h girl.h \
  ../bot-shared/mutex_inspector.h ../bot-shared/errs.h
	 c++ $(CFLAGS) ./girl.cpp -o $(OBJDIR)/girl.o

release: ./libot-girl_r.a girl.release.exe 
girl.release.exe: ./libot-girl_r.a ../bot-shared/libbot-shared_r.a $(ROBJDIR)/girl.o
		c++ $(ROBJDIR)/girl.o -o girl.release.exe ./libot-girl_r.a ../bot-shared/libbot-shared_r.a $(RLIBS)
		 strip girl.release.exe 


./libot-girl_r.a: \
	$(ROBJDIR)/cmd.o 
		 ar -r ./libot-girl_r.a $(ROBJDIR)/cmd.o 

./objR/cmd.o: cmd.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h girl.h \
  ../bot-shared/antiflood.h ../bot-shared/misc.h cmd.h \
  ../bot-shared/mutex_inspector.h ../bot-shared/errs.h
	 c++ $(RCFLAGS) ./cmd.cpp -o $(ROBJDIR)/cmd.o

./objR/girl.o: girl.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h cmd.h girl.h \
  ../bot-shared/mutex_inspector.h ../bot-shared/errs.h
	 c++ $(RCFLAGS) ./girl.cpp -o $(ROBJDIR)/girl.o

clean:
	 rm girl.exe girl.release.exe z.out kaka.xxx file_dump.cpp TERM* 1 2

both: all release



cleanobjs:
	 rm $(OBJDIR)/cmd.o $(OBJDIR)/girl.o $(ROBJDIR)/cmd.o $(ROBJDIR)/girl.o ./libbot-girl_d.a ./libot-girl_r.a


cleanall: clean cleanobjs


