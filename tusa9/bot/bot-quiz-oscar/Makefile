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

all: ./libbot-quiz_d.a quiz.exe 
quiz.exe: ./libbot-quiz_d.a ../bot-shared/libbot-shared_d.a $(OBJDIR)/quiz.o
		c++ $(OBJDIR)/quiz.o -o quiz.exe ./libbot-quiz_d.a ../bot-shared/libbot-shared_d.a $(LIBS) 
		 strip quiz.exe 


./libbot-quiz_d.a: \
	$(OBJDIR)/game.o
		 ar -r ./libbot-quiz_d.a $(OBJDIR)/game.o 

./objD/game.o: game.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h quiz.h \
  ../bot-shared/antiflood.h ../bot-shared/misc.h \
  ../bot-shared/oscar_buffer.h
	 c++ $(CFLAGS) ./game.cpp -o $(OBJDIR)/game.o

./objD/quiz.o: quiz.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h game.h quiz.h
	 c++ $(CFLAGS) ./quiz.cpp -o $(OBJDIR)/quiz.o

release: ./libot-quiz_r.a quiz.release.exe 
quiz.release.exe: ./libot-quiz_r.a ../bot-shared/libbot-shared_r.a $(ROBJDIR)/quiz.o
		c++ $(ROBJDIR)/quiz.o -o quiz.release.exe ./libot-quiz_r.a ../bot-shared/libbot-shared_r.a $(RLIBS)
		 strip quiz.release.exe 


./libot-quiz_r.a: \
	$(ROBJDIR)/game.o 
		 ar -r ./libot-quiz_r.a $(ROBJDIR)/game.o 

./objR/game.o: game.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h quiz.h \
  ../bot-shared/antiflood.h ../bot-shared/misc.h \
  ../bot-shared/oscar_buffer.h
	 c++ $(RCFLAGS) ./game.cpp -o $(ROBJDIR)/game.o

./objR/quiz.o: quiz.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h game.h quiz.h
	 c++ $(RCFLAGS) ./quiz.cpp -o $(ROBJDIR)/quiz.o

clean:
	 rm quiz.exe quiz.release.exe z.out kaka.xxx file_dump.cpp TERM* 1 2

both: all release



cleanobjs:
	 rm $(OBJDIR)/game.o $(OBJDIR)/quiz.o $(ROBJDIR)/game.o $(ROBJDIR)/quiz.o ./libbot-quiz_d.a ./libot-quiz_r.a


cleanall: clean cleanobjs


