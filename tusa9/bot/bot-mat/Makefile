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

all: ./libbot-mat_d.a mat.exe 
mat.exe: ./libbot-mat_d.a ../bot-shared/libbot-shared_d.a $(OBJDIR)/mat.o
		c++ $(OBJDIR)/mat.o -o mat.exe ./libbot-mat_d.a ../bot-shared/libbot-shared_d.a $(LIBS) 
		 strip mat.exe 


./libbot-mat_d.a: \
	$(OBJDIR)/cmds.o
		 ar -r ./libbot-mat_d.a $(OBJDIR)/cmds.o 

./objD/cmds.o: cmds.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h mat.h \
  ../bot-shared/antiflood.h ../bot-shared/misc.h \
  ../bot-shared/mutex_inspector.h ../bot-shared/errs.h
	 c++ $(CFLAGS) ./cmds.cpp -o $(OBJDIR)/cmds.o

./objD/mat.o: mat.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h cmds.h mat.h \
  ../bot-shared/_mutex.h
	 c++ $(CFLAGS) ./mat.cpp -o $(OBJDIR)/mat.o

release: ./libot-mat_r.a mat.release.exe 
mat.release.exe: ./libot-mat_r.a ../bot-shared/libbot-shared_r.a $(ROBJDIR)/mat.o
		c++ $(ROBJDIR)/mat.o -o mat.release.exe ./libot-mat_r.a ../bot-shared/libbot-shared_r.a $(RLIBS)
		 strip mat.release.exe 


./libot-mat_r.a: \
	$(ROBJDIR)/cmds.o 
		 ar -r ./libot-mat_r.a $(ROBJDIR)/cmds.o 

./objR/cmds.o: cmds.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h mat.h \
  ../bot-shared/antiflood.h ../bot-shared/misc.h \
  ../bot-shared/mutex_inspector.h ../bot-shared/errs.h
	 c++ $(RCFLAGS) ./cmds.cpp -o $(ROBJDIR)/cmds.o

./objR/mat.o: mat.cpp ../bot-shared/c_conn.h ../bot-shared/errs.h \
  ../bot-shared/config.h ../bot-shared/utils.h \
  ../bot-shared/oscar_buffer.h ../bot-shared/_mutex.h \
  ../bot-shared/misc.h ../bot-shared/c_conn.h \
  ../bot-shared/mysql_extens.h ../bot-shared/_QUERY.h cmds.h mat.h \
  ../bot-shared/_mutex.h
	 c++ $(RCFLAGS) ./mat.cpp -o $(ROBJDIR)/mat.o

clean:
	 rm mat.exe mat.release.exe z.out kaka.xxx file_dump.cpp TERM* 1 2

both: all release



cleanobjs:
	 rm $(OBJDIR)/cmds.o $(OBJDIR)/mat.o $(ROBJDIR)/cmds.o $(ROBJDIR)/mat.o ./libbot-mat_d.a ./libot-mat_r.a


cleanall: clean cleanobjs


