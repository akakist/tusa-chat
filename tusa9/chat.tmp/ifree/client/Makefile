#check_path_wfn(./objR/kall)
#stat ./objR 0
#check_path_wfn(./objD/kall)
#stat ./objD 0

CFLAGS= `cat _CFLAGS_D` -I. -I.. -I../../../core -I../../../core_cs/bos_client -I../../../core_cs/common -I../../../core_web -I../../../stdafx

RCFLAGS= `cat _CFLAGS_R` -I. -I.. -I../../../core -I../../../core_cs/bos_client -I../../../core_cs/common -I../../../core_web -I../../../stdafx

LIBS=  /usr/lib/libssl.a /usr/lib/libcrypto.a  /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread /usr/lib/libz.a /usr/lib/libgdbm.a       

RLIBS=  /usr/lib/libssl.a /usr/lib/libcrypto.a  /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread /usr/lib/libz.a /usr/lib/libgdbm.a     

OBJDIR=./objD

ROBJDIR=./objR

all: libchat_d.a ifree_client.exe 
ifree_client.exe: libchat_d.a  $(OBJDIR)/ifree_client.o
		c++ $(OBJDIR)/ifree_client.o -o ifree_client.exe libchat_d.a  $(LIBS) 
		 strip ifree_client.exe 


libchat_d.a: \
	$(OBJDIR)/PTR.o\
	$(OBJDIR)/__main.o\
	$(OBJDIR)/_mutex.o\
	$(OBJDIR)/_mutex1.o\
	$(OBJDIR)/bos_client.o\
	$(OBJDIR)/bos_client_interface.o\
	$(OBJDIR)/c_conn.o\
	$(OBJDIR)/core_main.o\
	$(OBJDIR)/errs.o\
	$(OBJDIR)/file_set.o\
	$(OBJDIR)/mutex_inspector.o\
	$(OBJDIR)/oscar_buffer.o\
	$(OBJDIR)/oscar_client.o\
	$(OBJDIR)/rijndael.o\
	$(OBJDIR)/server_config.o\
	$(OBJDIR)/st_FILE.o\
	$(OBJDIR)/st_rsa.o\
	$(OBJDIR)/st_stream_str.o\
	$(OBJDIR)/st_stuff.o\
	$(OBJDIR)/str_lib.o\
	$(OBJDIR)/str_lib1.o\
	$(OBJDIR)/str_lib_extra.o\
	$(OBJDIR)/tcp_sender.o\
	$(OBJDIR)/tcp_stats.o\
	$(OBJDIR)/threadable.o\
	$(OBJDIR)/wrappers.o
		 ar -r libchat_d.a $(OBJDIR)/PTR.o $(OBJDIR)/__main.o $(OBJDIR)/_mutex.o $(OBJDIR)/_mutex1.o $(OBJDIR)/bos_client.o $(OBJDIR)/bos_client_interface.o $(OBJDIR)/c_conn.o $(OBJDIR)/core_main.o $(OBJDIR)/errs.o $(OBJDIR)/file_set.o $(OBJDIR)/mutex_inspector.o $(OBJDIR)/oscar_buffer.o $(OBJDIR)/oscar_client.o $(OBJDIR)/rijndael.o $(OBJDIR)/server_config.o $(OBJDIR)/st_FILE.o $(OBJDIR)/st_rsa.o $(OBJDIR)/st_stream_str.o $(OBJDIR)/st_stuff.o $(OBJDIR)/str_lib.o $(OBJDIR)/str_lib1.o $(OBJDIR)/str_lib_extra.o $(OBJDIR)/tcp_sender.o $(OBJDIR)/tcp_stats.o $(OBJDIR)/threadable.o $(OBJDIR)/wrappers.o 

./objD/PTR.o: ../../../core/PTR.cpp ../../../stdafx/stdafx.h ../../../core/PTR.h \
  ../../../core/_mutex.h ../../../core/errs.h ../../../core/m_var.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h
	 c++ $(CFLAGS) ../../../core/PTR.cpp -o $(OBJDIR)/PTR.o

./objD/__main.o: ../../../core/__main.cpp ../../../stdafx/stdafx.h
	 c++ $(CFLAGS) ../../../core/__main.cpp -o $(OBJDIR)/__main.o

./objD/_mutex.o: ../../../core/_mutex.cpp ../../../stdafx/stdafx.h \
  ../../../core/errs.h ../../../core/_mutex.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h \
  ../../../core/str_lib.h ../../../core/m_var.h
	 c++ $(CFLAGS) ../../../core/_mutex.cpp -o $(OBJDIR)/_mutex.o

./objD/_mutex1.o: ../../../core/_mutex1.cpp ../../../stdafx/stdafx.h \
  ../../../core/errs.h ../../../core/_mutex.h ../../../core/_mutex1.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h \
  ../../../core/str_lib.h ../../../core/m_var.h
	 c++ $(CFLAGS) ../../../core/_mutex1.cpp -o $(OBJDIR)/_mutex1.o

./objD/bos_client.o: ../../../core_cs/bos_client/bos_client.cpp \
  ../../../stdafx/stdafx.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/errs.h ../../../core/m_var.h ../../../core/_mutex.h \
  ../../../core_cs/bos_client/bos_client.h ../../../core/oscar_buffer.h \
  ../../../core_web/oscar_client.h ../../../core/threadable.h \
  ../../../core/M_MAP.h ../../../core/st_rsa.h \
  ../../../core_cs/common/RTYPES_CORE.h ../../../core/rijndael.h \
  ../../../core_web/c_conn.h ../../../core/_mutex.h ../../../core/PTR.h \
  ../../../core/m_var.h ../../../core/mutex_inspector.h \
  ../../../core/lockctl.h ../../../core/M_DEQUE.h \
  ../../../core_cs/bos_client/bos_client_interface.h
	 c++ $(CFLAGS) ../../../core_cs/bos_client/bos_client.cpp -o $(OBJDIR)/bos_client.o

./objD/bos_client_interface.o:  \
 ../../../core_cs/bos_client/bos_client_interface.cpp \
  ../../../stdafx/stdafx.h ../../../core/m_var.h ../../../core/_mutex.h \
  ../../../core_cs/bos_client/bos_client.h ../../../core/oscar_buffer.h \
  ../../../core_web/oscar_client.h ../../../core/threadable.h \
  ../../../core/M_MAP.h ../../../core/st_rsa.h \
  ../../../core_cs/bos_client/bos_client_interface.h
	 c++ $(CFLAGS) ../../../core_cs/bos_client/bos_client_interface.cpp -o $(OBJDIR)/bos_client_interface.o

./objD/c_conn.o: ../../../core_web/c_conn.cpp ../../../stdafx/stdafx.h \
  ../../../core_web/c_conn.h ../../../core/_mutex.h ../../../core/m_var.h \
  ../../../core/_mutex.h ../../../core/PTR.h ../../../core/errs.h \
  ../../../core/m_var.h ../../../core/mutex_inspector.h \
  ../../../core/lockctl.h ../../../core/tcp_stats.h \
  ../../../core/mutex_inspector.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/st_stuff.h ../../../core/str_lib.h \
  ../../../core_web/tcp_sender.h ../../../core/oscar_buffer.h
	 c++ $(CFLAGS) ../../../core_web/c_conn.cpp -o $(OBJDIR)/c_conn.o

./objD/core_main.o: ../../../core/core_main.cpp ../../../stdafx/stdafx.h \
  ../../../core/server_config.h ../../../core/_mutex.h \
  ../../../core/M_MAP.h ../../../core/M_SET.h ../../../core/m_var.h \
  ../../../core/file_set.h ../../../core/M_LIST.h ../../../core/errs.h \
  ../../../core/str_lib.h ../../../core/m_var.h
	 c++ $(CFLAGS) ../../../core/core_main.cpp -o $(OBJDIR)/core_main.o

./objD/errs.o: ../../../core/errs.cpp ../../../stdafx/stdafx.h \
  ../../../core/errs.h ../../../core/str_lib.h ../../../core/m_var.h \
  ../../../core/_mutex.h ../../../core/m_var.h \
  ../../../core/server_config.h ../../../core/M_MAP.h \
  ../../../core/M_SET.h ../../../core/file_set.h ../../../core/M_LIST.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h
	 c++ $(CFLAGS) ../../../core/errs.cpp -o $(OBJDIR)/errs.o

./objD/file_set.o: ../../../core/file_set.cpp ../../../stdafx/stdafx.h \
  ../../../core/wrappers.h ../../../core/file_set.h \
  ../../../core/M_LIST.h ../../../core/_mutex.h ../../../core/m_var.h \
  ../../../core/mutex_inspector.h ../../../core/errs.h \
  ../../../core/lockctl.h ../../../core/str_lib.h ../../../core/m_var.h \
  ../../../core/st_stuff.h ../../../core/server_config.h \
  ../../../core/M_MAP.h ../../../core/M_SET.h
	 c++ $(CFLAGS) ../../../core/file_set.cpp -o $(OBJDIR)/file_set.o

./objD/ifree_client.o: ifree_client.cpp ../../../stdafx/stdafx.h ifree_client.h \
  ../../../core_cs/bos_client/bos_client_interface.h \
  ../../../core/oscar_buffer.h version.h ifree_data_event.h \
  ifree_requests.h ../../../core/errs.h ../../../core/mutex_inspector.h \
  ../../../core/_mutex.h ../../../core/errs.h ../../../core/lockctl.h \
  ../../../core/str_lib.h ../../../core/m_var.h \
  ../../../core_web/web_tools.h ../../../core/PTR.h ../../../core/m_var.h \
  ../../../core/mutex_inspector.h ../../../core_web/c_conn.h \
  ../../../core/_mutex.h ../../../core/PTR.h
	 c++ $(CFLAGS) ./ifree_client.cpp -o $(OBJDIR)/ifree_client.o

./objD/mutex_inspector.o: ../../../core/mutex_inspector.cpp \
  ../../../stdafx/stdafx.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/_mutex.h ../../../core/_mutex1.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h \
  ../../../core/M_MAP.h
	 c++ $(CFLAGS) ../../../core/mutex_inspector.cpp -o $(OBJDIR)/mutex_inspector.o

./objD/oscar_buffer.o: ../../../core/oscar_buffer.cpp ../../../stdafx/stdafx.h \
  ../../../core/oscar_buffer.h ../../../core/str_lib.h \
  ../../../core/errs.h ../../../core/m_var.h ../../../core/_mutex.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h
	 c++ $(CFLAGS) ../../../core/oscar_buffer.cpp -o $(OBJDIR)/oscar_buffer.o

./objD/oscar_client.o: ../../../core_web/oscar_client.cpp \
  ../../../stdafx/stdafx.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/errs.h ../../../core/m_var.h ../../../core/_mutex.h \
  ../../../core/oscar_buffer.h ../../../core/PTR.h ../../../core/m_var.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h \
  ../../../core_web/oscar_client.h ../../../core/threadable.h \
  ../../../core/M_MAP.h ../../../core_web/c_conn.h ../../../core/_mutex.h
	 c++ $(CFLAGS) ../../../core_web/oscar_client.cpp -o $(OBJDIR)/oscar_client.o

./objD/rijndael.o: ../../../core/rijndael.cpp ../../../core/rijndael.h
	 c++ $(CFLAGS) ../../../core/rijndael.cpp -o $(OBJDIR)/rijndael.o

./objD/server_config.o: ../../../core/server_config.cpp ../../../stdafx/stdafx.h \
  ../../../core/mutex_inspector.h ../../../core/_mutex.h \
  ../../../core/errs.h ../../../core/lockctl.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/server_config.h \
  ../../../core/M_MAP.h ../../../core/M_SET.h ../../../core/m_var.h \
  ../../../core/file_set.h ../../../core/M_LIST.h \
  ../../../core/wrappers.h ../../../core/st_stuff.h
	 c++ $(CFLAGS) ../../../core/server_config.cpp -o $(OBJDIR)/server_config.o

./objD/st_FILE.o: ../../../core/st_FILE.cpp ../../../stdafx/stdafx.h \
  ../../../core/st_stuff.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/_mutex.h ../../../core/copy_file.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h \
  ../../../core/wrappers.h
	 c++ $(CFLAGS) ../../../core/st_FILE.cpp -o $(OBJDIR)/st_FILE.o

./objD/st_rsa.o: ../../../core/st_rsa.cpp ../../../stdafx/stdafx.h \
  ../../../core/st_stuff.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/_mutex.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h \
  ../../../core/m_var.h ../../../core/st_rsa.h
	 c++ $(CFLAGS) ../../../core/st_rsa.cpp -o $(OBJDIR)/st_rsa.o

./objD/st_stream_str.o: ../../../core/st_stream_str.cpp ../../../stdafx/stdafx.h \
  ../../../core/str_lib.h ../../../core/errs.h ../../../core/m_var.h \
  ../../../core/_mutex.h ../../../core/st_stream_str.h \
  ../../../core/st_stuff.h
	 c++ $(CFLAGS) ../../../core/st_stream_str.cpp -o $(OBJDIR)/st_stream_str.o

./objD/st_stuff.o: ../../../core/st_stuff.cpp ../../../stdafx/stdafx.h \
  ../../../core/st_stuff.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/_mutex.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h
	 c++ $(CFLAGS) ../../../core/st_stuff.cpp -o $(OBJDIR)/st_stuff.o

./objD/str_lib.o: ../../../core/str_lib.cpp ../../../stdafx/stdafx.h \
  ../../../core/_mutex.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/mutex_inspector.h \
  ../../../core/lockctl.h
	 c++ $(CFLAGS) ../../../core/str_lib.cpp -o $(OBJDIR)/str_lib.o

./objD/str_lib1.o: ../../../core/str_lib1.cpp ../../../stdafx/stdafx.h \
  ../../../core/_mutex.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/mutex_inspector.h \
  ../../../core/lockctl.h
	 c++ $(CFLAGS) ../../../core/str_lib1.cpp -o $(OBJDIR)/str_lib1.o

./objD/str_lib_extra.o: ../../../core/str_lib_extra.cpp ../../../stdafx/stdafx.h \
  ../../../core/_mutex.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/st_stuff.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h \
  ../../../core/st_stream_str.h
	 c++ $(CFLAGS) ../../../core/str_lib_extra.cpp -o $(OBJDIR)/str_lib_extra.o

./objD/tcp_sender.o: ../../../core_web/tcp_sender.cpp ../../../stdafx/stdafx.h \
  ../../../core/mutex_inspector.h ../../../core/_mutex.h \
  ../../../core/errs.h ../../../core/lockctl.h \
  ../../../core_web/tcp_server_data.h ../../../core/M_DEQUE.h \
  ../../../core_web/tcp_server_connection.h ../../../core_web/c_conn.h \
  ../../../core/_mutex.h ../../../core/m_var.h ../../../core/PTR.h \
  ../../../core/m_var.h ../../../core/mutex_inspector.h \
  ../../../core/M_MAP.h ../../../core/file_set.h ../../../core/M_LIST.h \
  ../../../core/str_lib.h ../../../core/m_var.h \
  ../../../core_web/tcp_sender.h ../../../core/tcp_stats.h \
  ../../../core/M_SET.h ../../../core/threadable.h ../../../core/M_MAP.h
	 c++ $(CFLAGS) ../../../core_web/tcp_sender.cpp -o $(OBJDIR)/tcp_sender.o

./objD/tcp_stats.o: ../../../core/tcp_stats.cpp ../../../stdafx/stdafx.h \
  ../../../core/mutex_inspector.h ../../../core/_mutex.h \
  ../../../core/errs.h ../../../core/lockctl.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/m_var.h
	 c++ $(CFLAGS) ../../../core/tcp_stats.cpp -o $(OBJDIR)/tcp_stats.o

./objD/threadable.o: ../../../core/threadable.cpp ../../../stdafx/stdafx.h \
  ../../../core/threadable.h ../../../core/M_MAP.h ../../../core/_mutex.h \
  ../../../core/errs.h ../../../core/mutex_inspector.h \
  ../../../core/lockctl.h ../../../core/str_lib.h ../../../core/m_var.h
	 c++ $(CFLAGS) ../../../core/threadable.cpp -o $(OBJDIR)/threadable.o

./objD/wrappers.o: ../../../core/wrappers.cpp ../../../stdafx/stdafx.h \
  ../../../core/str_lib.h ../../../core/errs.h ../../../core/m_var.h \
  ../../../core/_mutex.h ../../../core/copy_file.h \
  ../../../core/wrappers.h ../../../core/mutex_inspector.h \
  ../../../core/lockctl.h ../../../core/tcp_stats.h
	 c++ $(CFLAGS) ../../../core/wrappers.cpp -o $(OBJDIR)/wrappers.o

release: libchat_r.a ifree_client.release.exe 
ifree_client.release.exe: libchat_r.a  $(ROBJDIR)/ifree_client.o
		c++ $(ROBJDIR)/ifree_client.o -o ifree_client.release.exe libchat_r.a  $(RLIBS)
		 strip ifree_client.release.exe 


libchat_r.a: \
	$(ROBJDIR)/PTR.o \
	$(ROBJDIR)/__main.o \
	$(ROBJDIR)/_mutex.o \
	$(ROBJDIR)/_mutex1.o \
	$(ROBJDIR)/bos_client.o \
	$(ROBJDIR)/bos_client_interface.o \
	$(ROBJDIR)/c_conn.o \
	$(ROBJDIR)/core_main.o \
	$(ROBJDIR)/errs.o \
	$(ROBJDIR)/file_set.o \
	$(ROBJDIR)/mutex_inspector.o \
	$(ROBJDIR)/oscar_buffer.o \
	$(ROBJDIR)/oscar_client.o \
	$(ROBJDIR)/rijndael.o \
	$(ROBJDIR)/server_config.o \
	$(ROBJDIR)/st_FILE.o \
	$(ROBJDIR)/st_rsa.o \
	$(ROBJDIR)/st_stream_str.o \
	$(ROBJDIR)/st_stuff.o \
	$(ROBJDIR)/str_lib.o \
	$(ROBJDIR)/str_lib1.o \
	$(ROBJDIR)/str_lib_extra.o \
	$(ROBJDIR)/tcp_sender.o \
	$(ROBJDIR)/tcp_stats.o \
	$(ROBJDIR)/threadable.o \
	$(ROBJDIR)/wrappers.o 
		 ar -r libchat_r.a $(ROBJDIR)/PTR.o $(ROBJDIR)/__main.o $(ROBJDIR)/_mutex.o $(ROBJDIR)/_mutex1.o $(ROBJDIR)/bos_client.o $(ROBJDIR)/bos_client_interface.o $(ROBJDIR)/c_conn.o $(ROBJDIR)/core_main.o $(ROBJDIR)/errs.o $(ROBJDIR)/file_set.o $(ROBJDIR)/mutex_inspector.o $(ROBJDIR)/oscar_buffer.o $(ROBJDIR)/oscar_client.o $(ROBJDIR)/rijndael.o $(ROBJDIR)/server_config.o $(ROBJDIR)/st_FILE.o $(ROBJDIR)/st_rsa.o $(ROBJDIR)/st_stream_str.o $(ROBJDIR)/st_stuff.o $(ROBJDIR)/str_lib.o $(ROBJDIR)/str_lib1.o $(ROBJDIR)/str_lib_extra.o $(ROBJDIR)/tcp_sender.o $(ROBJDIR)/tcp_stats.o $(ROBJDIR)/threadable.o $(ROBJDIR)/wrappers.o 

./objR/PTR.o: ../../../core/PTR.cpp ../../../stdafx/stdafx.h ../../../core/PTR.h \
  ../../../core/_mutex.h ../../../core/errs.h ../../../core/m_var.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h
	 c++ $(RCFLAGS) ../../../core/PTR.cpp -o $(ROBJDIR)/PTR.o

./objR/__main.o: ../../../core/__main.cpp ../../../stdafx/stdafx.h
	 c++ $(RCFLAGS) ../../../core/__main.cpp -o $(ROBJDIR)/__main.o

./objR/_mutex.o: ../../../core/_mutex.cpp ../../../stdafx/stdafx.h \
  ../../../core/errs.h ../../../core/_mutex.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h \
  ../../../core/str_lib.h ../../../core/m_var.h
	 c++ $(RCFLAGS) ../../../core/_mutex.cpp -o $(ROBJDIR)/_mutex.o

./objR/_mutex1.o: ../../../core/_mutex1.cpp ../../../stdafx/stdafx.h \
  ../../../core/errs.h ../../../core/_mutex.h ../../../core/_mutex1.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h \
  ../../../core/str_lib.h ../../../core/m_var.h
	 c++ $(RCFLAGS) ../../../core/_mutex1.cpp -o $(ROBJDIR)/_mutex1.o

./objR/bos_client.o: ../../../core_cs/bos_client/bos_client.cpp \
  ../../../stdafx/stdafx.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/errs.h ../../../core/m_var.h ../../../core/_mutex.h \
  ../../../core_cs/bos_client/bos_client.h ../../../core/oscar_buffer.h \
  ../../../core_web/oscar_client.h ../../../core/threadable.h \
  ../../../core/M_MAP.h ../../../core/st_rsa.h \
  ../../../core_cs/common/RTYPES_CORE.h ../../../core/rijndael.h \
  ../../../core_web/c_conn.h ../../../core/_mutex.h ../../../core/PTR.h \
  ../../../core/m_var.h ../../../core/mutex_inspector.h \
  ../../../core/lockctl.h ../../../core/M_DEQUE.h \
  ../../../core_cs/bos_client/bos_client_interface.h
	 c++ $(RCFLAGS) ../../../core_cs/bos_client/bos_client.cpp -o $(ROBJDIR)/bos_client.o

./objR/bos_client_interface.o:  \
 ../../../core_cs/bos_client/bos_client_interface.cpp \
  ../../../stdafx/stdafx.h ../../../core/m_var.h ../../../core/_mutex.h \
  ../../../core_cs/bos_client/bos_client.h ../../../core/oscar_buffer.h \
  ../../../core_web/oscar_client.h ../../../core/threadable.h \
  ../../../core/M_MAP.h ../../../core/st_rsa.h \
  ../../../core_cs/bos_client/bos_client_interface.h
	 c++ $(RCFLAGS) ../../../core_cs/bos_client/bos_client_interface.cpp -o $(ROBJDIR)/bos_client_interface.o

./objR/c_conn.o: ../../../core_web/c_conn.cpp ../../../stdafx/stdafx.h \
  ../../../core_web/c_conn.h ../../../core/_mutex.h ../../../core/m_var.h \
  ../../../core/_mutex.h ../../../core/PTR.h ../../../core/errs.h \
  ../../../core/m_var.h ../../../core/mutex_inspector.h \
  ../../../core/lockctl.h ../../../core/tcp_stats.h \
  ../../../core/mutex_inspector.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/st_stuff.h ../../../core/str_lib.h \
  ../../../core_web/tcp_sender.h ../../../core/oscar_buffer.h
	 c++ $(RCFLAGS) ../../../core_web/c_conn.cpp -o $(ROBJDIR)/c_conn.o

./objR/core_main.o: ../../../core/core_main.cpp ../../../stdafx/stdafx.h \
  ../../../core/server_config.h ../../../core/_mutex.h \
  ../../../core/M_MAP.h ../../../core/M_SET.h ../../../core/m_var.h \
  ../../../core/file_set.h ../../../core/M_LIST.h ../../../core/errs.h \
  ../../../core/str_lib.h ../../../core/m_var.h
	 c++ $(RCFLAGS) ../../../core/core_main.cpp -o $(ROBJDIR)/core_main.o

./objR/errs.o: ../../../core/errs.cpp ../../../stdafx/stdafx.h \
  ../../../core/errs.h ../../../core/str_lib.h ../../../core/m_var.h \
  ../../../core/_mutex.h ../../../core/m_var.h \
  ../../../core/server_config.h ../../../core/M_MAP.h \
  ../../../core/M_SET.h ../../../core/file_set.h ../../../core/M_LIST.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h
	 c++ $(RCFLAGS) ../../../core/errs.cpp -o $(ROBJDIR)/errs.o

./objR/file_set.o: ../../../core/file_set.cpp ../../../stdafx/stdafx.h \
  ../../../core/wrappers.h ../../../core/file_set.h \
  ../../../core/M_LIST.h ../../../core/_mutex.h ../../../core/m_var.h \
  ../../../core/mutex_inspector.h ../../../core/errs.h \
  ../../../core/lockctl.h ../../../core/str_lib.h ../../../core/m_var.h \
  ../../../core/st_stuff.h ../../../core/server_config.h \
  ../../../core/M_MAP.h ../../../core/M_SET.h
	 c++ $(RCFLAGS) ../../../core/file_set.cpp -o $(ROBJDIR)/file_set.o

./objR/ifree_client.o: ifree_client.cpp ../../../stdafx/stdafx.h ifree_client.h \
  ../../../core_cs/bos_client/bos_client_interface.h \
  ../../../core/oscar_buffer.h version.h ifree_data_event.h \
  ifree_requests.h ../../../core/errs.h ../../../core/mutex_inspector.h \
  ../../../core/_mutex.h ../../../core/errs.h ../../../core/lockctl.h \
  ../../../core/str_lib.h ../../../core/m_var.h \
  ../../../core_web/web_tools.h ../../../core/PTR.h ../../../core/m_var.h \
  ../../../core/mutex_inspector.h ../../../core_web/c_conn.h \
  ../../../core/_mutex.h ../../../core/PTR.h
	 c++ $(RCFLAGS) ./ifree_client.cpp -o $(ROBJDIR)/ifree_client.o

./objR/mutex_inspector.o: ../../../core/mutex_inspector.cpp \
  ../../../stdafx/stdafx.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/_mutex.h ../../../core/_mutex1.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h \
  ../../../core/M_MAP.h
	 c++ $(RCFLAGS) ../../../core/mutex_inspector.cpp -o $(ROBJDIR)/mutex_inspector.o

./objR/oscar_buffer.o: ../../../core/oscar_buffer.cpp ../../../stdafx/stdafx.h \
  ../../../core/oscar_buffer.h ../../../core/str_lib.h \
  ../../../core/errs.h ../../../core/m_var.h ../../../core/_mutex.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h
	 c++ $(RCFLAGS) ../../../core/oscar_buffer.cpp -o $(ROBJDIR)/oscar_buffer.o

./objR/oscar_client.o: ../../../core_web/oscar_client.cpp \
  ../../../stdafx/stdafx.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/errs.h ../../../core/m_var.h ../../../core/_mutex.h \
  ../../../core/oscar_buffer.h ../../../core/PTR.h ../../../core/m_var.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h \
  ../../../core_web/oscar_client.h ../../../core/threadable.h \
  ../../../core/M_MAP.h ../../../core_web/c_conn.h ../../../core/_mutex.h
	 c++ $(RCFLAGS) ../../../core_web/oscar_client.cpp -o $(ROBJDIR)/oscar_client.o

./objR/rijndael.o: ../../../core/rijndael.cpp ../../../core/rijndael.h
	 c++ $(RCFLAGS) ../../../core/rijndael.cpp -o $(ROBJDIR)/rijndael.o

./objR/server_config.o: ../../../core/server_config.cpp ../../../stdafx/stdafx.h \
  ../../../core/mutex_inspector.h ../../../core/_mutex.h \
  ../../../core/errs.h ../../../core/lockctl.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/server_config.h \
  ../../../core/M_MAP.h ../../../core/M_SET.h ../../../core/m_var.h \
  ../../../core/file_set.h ../../../core/M_LIST.h \
  ../../../core/wrappers.h ../../../core/st_stuff.h
	 c++ $(RCFLAGS) ../../../core/server_config.cpp -o $(ROBJDIR)/server_config.o

./objR/st_FILE.o: ../../../core/st_FILE.cpp ../../../stdafx/stdafx.h \
  ../../../core/st_stuff.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/_mutex.h ../../../core/copy_file.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h \
  ../../../core/wrappers.h
	 c++ $(RCFLAGS) ../../../core/st_FILE.cpp -o $(ROBJDIR)/st_FILE.o

./objR/st_rsa.o: ../../../core/st_rsa.cpp ../../../stdafx/stdafx.h \
  ../../../core/st_stuff.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/_mutex.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h \
  ../../../core/m_var.h ../../../core/st_rsa.h
	 c++ $(RCFLAGS) ../../../core/st_rsa.cpp -o $(ROBJDIR)/st_rsa.o

./objR/st_stream_str.o: ../../../core/st_stream_str.cpp ../../../stdafx/stdafx.h \
  ../../../core/str_lib.h ../../../core/errs.h ../../../core/m_var.h \
  ../../../core/_mutex.h ../../../core/st_stream_str.h \
  ../../../core/st_stuff.h
	 c++ $(RCFLAGS) ../../../core/st_stream_str.cpp -o $(ROBJDIR)/st_stream_str.o

./objR/st_stuff.o: ../../../core/st_stuff.cpp ../../../stdafx/stdafx.h \
  ../../../core/st_stuff.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/_mutex.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h
	 c++ $(RCFLAGS) ../../../core/st_stuff.cpp -o $(ROBJDIR)/st_stuff.o

./objR/str_lib.o: ../../../core/str_lib.cpp ../../../stdafx/stdafx.h \
  ../../../core/_mutex.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/mutex_inspector.h \
  ../../../core/lockctl.h
	 c++ $(RCFLAGS) ../../../core/str_lib.cpp -o $(ROBJDIR)/str_lib.o

./objR/str_lib1.o: ../../../core/str_lib1.cpp ../../../stdafx/stdafx.h \
  ../../../core/_mutex.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/mutex_inspector.h \
  ../../../core/lockctl.h
	 c++ $(RCFLAGS) ../../../core/str_lib1.cpp -o $(ROBJDIR)/str_lib1.o

./objR/str_lib_extra.o: ../../../core/str_lib_extra.cpp ../../../stdafx/stdafx.h \
  ../../../core/_mutex.h ../../../core/errs.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/st_stuff.h \
  ../../../core/mutex_inspector.h ../../../core/lockctl.h \
  ../../../core/st_stream_str.h
	 c++ $(RCFLAGS) ../../../core/str_lib_extra.cpp -o $(ROBJDIR)/str_lib_extra.o

./objR/tcp_sender.o: ../../../core_web/tcp_sender.cpp ../../../stdafx/stdafx.h \
  ../../../core/mutex_inspector.h ../../../core/_mutex.h \
  ../../../core/errs.h ../../../core/lockctl.h \
  ../../../core_web/tcp_server_data.h ../../../core/M_DEQUE.h \
  ../../../core_web/tcp_server_connection.h ../../../core_web/c_conn.h \
  ../../../core/_mutex.h ../../../core/m_var.h ../../../core/PTR.h \
  ../../../core/m_var.h ../../../core/mutex_inspector.h \
  ../../../core/M_MAP.h ../../../core/file_set.h ../../../core/M_LIST.h \
  ../../../core/str_lib.h ../../../core/m_var.h \
  ../../../core_web/tcp_sender.h ../../../core/tcp_stats.h \
  ../../../core/M_SET.h ../../../core/threadable.h ../../../core/M_MAP.h
	 c++ $(RCFLAGS) ../../../core_web/tcp_sender.cpp -o $(ROBJDIR)/tcp_sender.o

./objR/tcp_stats.o: ../../../core/tcp_stats.cpp ../../../stdafx/stdafx.h \
  ../../../core/mutex_inspector.h ../../../core/_mutex.h \
  ../../../core/errs.h ../../../core/lockctl.h ../../../core/str_lib.h \
  ../../../core/m_var.h ../../../core/m_var.h
	 c++ $(RCFLAGS) ../../../core/tcp_stats.cpp -o $(ROBJDIR)/tcp_stats.o

./objR/threadable.o: ../../../core/threadable.cpp ../../../stdafx/stdafx.h \
  ../../../core/threadable.h ../../../core/M_MAP.h ../../../core/_mutex.h \
  ../../../core/errs.h ../../../core/mutex_inspector.h \
  ../../../core/lockctl.h ../../../core/str_lib.h ../../../core/m_var.h
	 c++ $(RCFLAGS) ../../../core/threadable.cpp -o $(ROBJDIR)/threadable.o

./objR/wrappers.o: ../../../core/wrappers.cpp ../../../stdafx/stdafx.h \
  ../../../core/str_lib.h ../../../core/errs.h ../../../core/m_var.h \
  ../../../core/_mutex.h ../../../core/copy_file.h \
  ../../../core/wrappers.h ../../../core/mutex_inspector.h \
  ../../../core/lockctl.h ../../../core/tcp_stats.h
	 c++ $(RCFLAGS) ../../../core/wrappers.cpp -o $(ROBJDIR)/wrappers.o

clean:
	 rm ifree_client.exe ifree_client.release.exe z.out kaka.xxx file_dump.cpp TERM* 1 2

both: all release



cleanobjs:
	 rm $(OBJDIR)/PTR.o $(OBJDIR)/__main.o $(OBJDIR)/_mutex.o $(OBJDIR)/_mutex1.o $(OBJDIR)/bos_client.o $(OBJDIR)/bos_client_interface.o $(OBJDIR)/c_conn.o $(OBJDIR)/core_main.o $(OBJDIR)/errs.o $(OBJDIR)/file_set.o $(OBJDIR)/ifree_client.o $(OBJDIR)/mutex_inspector.o $(OBJDIR)/oscar_buffer.o $(OBJDIR)/oscar_client.o $(OBJDIR)/rijndael.o $(OBJDIR)/server_config.o $(OBJDIR)/st_FILE.o $(OBJDIR)/st_rsa.o $(OBJDIR)/st_stream_str.o $(OBJDIR)/st_stuff.o $(OBJDIR)/str_lib.o $(OBJDIR)/str_lib1.o $(OBJDIR)/str_lib_extra.o $(OBJDIR)/tcp_sender.o $(OBJDIR)/tcp_stats.o $(OBJDIR)/threadable.o $(OBJDIR)/wrappers.o $(ROBJDIR)/PTR.o $(ROBJDIR)/__main.o $(ROBJDIR)/_mutex.o $(ROBJDIR)/_mutex1.o $(ROBJDIR)/bos_client.o $(ROBJDIR)/bos_client_interface.o $(ROBJDIR)/c_conn.o $(ROBJDIR)/core_main.o $(ROBJDIR)/errs.o $(ROBJDIR)/file_set.o $(ROBJDIR)/ifree_client.o $(ROBJDIR)/mutex_inspector.o $(ROBJDIR)/oscar_buffer.o $(ROBJDIR)/oscar_client.o $(ROBJDIR)/rijndael.o $(ROBJDIR)/server_config.o $(ROBJDIR)/st_FILE.o $(ROBJDIR)/st_rsa.o $(ROBJDIR)/st_stream_str.o $(ROBJDIR)/st_stuff.o $(ROBJDIR)/str_lib.o $(ROBJDIR)/str_lib1.o $(ROBJDIR)/str_lib_extra.o $(ROBJDIR)/tcp_sender.o $(ROBJDIR)/tcp_stats.o $(ROBJDIR)/threadable.o $(ROBJDIR)/wrappers.o libchat_d.a libchat_r.a


cleanall: clean cleanobjs


