#check_path_wfn(./objR/kall)
#stat ./objR 0
#check_path_wfn(./objD/kall)
#stat ./objD 0

CFLAGS=  `cat ../_CFLAGS_D`  -I. -I../../core -I../../core_web -I../../stdafx

RCFLAGS= `cat ../_CFLAGS_R` -I. -I../../core -I../../core_web -I../../stdafx

LIBS= -lssl -lcrypto /usr/local/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a     /usr/local/lib/libGeoIP.a  -shared -Xlinker "--exclude-libs=libfmD.a" -v

RLIBS= -lssl -lcrypto /usr/local/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a   /usr/local/lib/libGeoIP.a   -shared -Xlinker "--exclude-libs=libfmR.a" -v

OBJDIR=./objD

ROBJDIR=./objR

all: ./libcoreweb_d.a 


./libcoreweb_d.a: \
	$(OBJDIR)/c_conn.o\
	$(OBJDIR)/html_out.o\
	$(OBJDIR)/tcp_dialog_server.o\
	$(OBJDIR)/tcp_oscar_dialog_server.o\
	$(OBJDIR)/tcp_sender.o\
	$(OBJDIR)/tcp_server.o\
	$(OBJDIR)/tcp_server_connection.o\
	$(OBJDIR)/tcp_stats.o\
	$(OBJDIR)/thread_info_report.o\
	$(OBJDIR)/web_adminfo.o\
	$(OBJDIR)/web_cache.o\
	$(OBJDIR)/web_connection.o\
	$(OBJDIR)/web_connection_ptcp.o\
	$(OBJDIR)/web_server.o\
	$(OBJDIR)/web_tools.o
		 ar -r ./libcoreweb_d.a $(OBJDIR)/c_conn.o $(OBJDIR)/html_out.o $(OBJDIR)/tcp_dialog_server.o $(OBJDIR)/tcp_oscar_dialog_server.o $(OBJDIR)/tcp_sender.o $(OBJDIR)/tcp_server.o $(OBJDIR)/tcp_server_connection.o $(OBJDIR)/tcp_stats.o $(OBJDIR)/thread_info_report.o $(OBJDIR)/web_adminfo.o $(OBJDIR)/web_cache.o $(OBJDIR)/web_connection.o $(OBJDIR)/web_connection_ptcp.o $(OBJDIR)/web_server.o $(OBJDIR)/web_tools.o 

./objD/c_conn.o: ../../core_web/c_conn.cpp ../../stdafx/stdafx.h \
  ../../core_web/c_conn.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c \
  /usr/local/include/stlport/stl/_relops_cont.h ../../core/_mutex.h \
  /usr/local/include/stlport/pthread.h /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/PTR.h ../../core/errs.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/tcp_stats.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/str_lib.h ../../core/m_var.h ../../core/Double.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/st_stuff.h \
  ../../core/str_lib.h ../../core_web/tcp_sender.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/errno.h
	 c++ $(CFLAGS) ../../core_web/c_conn.cpp -o $(OBJDIR)/c_conn.o

./objD/html_out.o: ../../core_web/html_out.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_prolog.h \
  /usr/local/include/stlport/stl/config/features.h \
  /usr/local/include/stlport/stl/_stlport_version.h \
  /usr/local/include/stlport/stl/config/user_config.h \
  /usr/local/include/stlport/stl/config/compat.h \
  /usr/local/include/stlport/stl/config/host.h \
  /usr/local/include/stlport/stl/config/_system.h \
  /usr/local/include/stlport/stl/config/_linux.h \
  /usr/local/include/stlport/stl/config/_gcc.h \
  /usr/local/include/stlport/stl/config/stl_confix.h \
  /usr/local/include/stlport/stl/config/_native_headers.h \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c ../../core/PTR.h \
  ../../core/_mutex.h ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core_web/html_out.h ../../core_web/web_tools.h ../../core/m_var.h \
  ../../core/server_config.h ../../core/M_MAP.h ../../core/M_SET.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/file_set.h /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  ../../core/str_lib.h ../../core/m_var.h ../../core/Double.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/oscar_buffer.h
	 c++ $(CFLAGS) ../../core_web/html_out.cpp -o $(OBJDIR)/html_out.o

./objD/tcp_dialog_server.o: ../../core_web/tcp_dialog_server.cpp \
  ../../stdafx/stdafx.h ../../core/_mutex.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_prolog.h \
  /usr/local/include/stlport/stl/config/features.h \
  /usr/local/include/stlport/stl/_stlport_version.h \
  /usr/local/include/stlport/stl/config/user_config.h \
  /usr/local/include/stlport/stl/config/compat.h \
  /usr/local/include/stlport/stl/config/host.h \
  /usr/local/include/stlport/stl/config/_system.h \
  /usr/local/include/stlport/stl/config/_linux.h \
  /usr/local/include/stlport/stl/config/_gcc.h \
  /usr/local/include/stlport/stl/config/stl_confix.h \
  /usr/local/include/stlport/stl/config/_native_headers.h \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/lockctl.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/lockctl.h ../../core_web/tcp_dialog_server.h \
  ../../core_web/tcp_server.h ../../core/m_var.h ../../core/threadable.h \
  ../../core/M_MAP.h ../../core_web/c_conn.h ../../core/PTR.h \
  ../../core/m_var.h ../../core/mutex_inspector.h \
  ../../core_web/tcp_server_connection.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/M_SET.h \
  ../../core_web/tcp_server_data.h ../../core/M_DEQUE.h \
  ../../core/M_MAP.h ../../core/str_lib.h ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h
	 c++ $(CFLAGS) ../../core_web/tcp_dialog_server.cpp -o $(OBJDIR)/tcp_dialog_server.o

./objD/tcp_oscar_dialog_server.o: ../../core_web/tcp_oscar_dialog_server.cpp \
  ../../stdafx/stdafx.h ../../core/_mutex.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_prolog.h \
  /usr/local/include/stlport/stl/config/features.h \
  /usr/local/include/stlport/stl/_stlport_version.h \
  /usr/local/include/stlport/stl/config/user_config.h \
  /usr/local/include/stlport/stl/config/compat.h \
  /usr/local/include/stlport/stl/config/host.h \
  /usr/local/include/stlport/stl/config/_system.h \
  /usr/local/include/stlport/stl/config/_linux.h \
  /usr/local/include/stlport/stl/config/_gcc.h \
  /usr/local/include/stlport/stl/config/stl_confix.h \
  /usr/local/include/stlport/stl/config/_native_headers.h \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/lockctl.h \
  ../../core/lockctl.h ../../core_web/tcp_oscar_dialog_server.h \
  ../../core_web/tcp_dialog_server.h ../../core_web/tcp_server.h \
  ../../core/m_var.h ../../core/threadable.h ../../core/M_MAP.h \
  ../../core_web/c_conn.h ../../core/PTR.h ../../core/m_var.h \
  ../../core/mutex_inspector.h ../../core_web/tcp_server_connection.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/M_SET.h \
  ../../core/str_lib.h ../../core/m_var.h ../../core/Double.h \
  ../../core/oscar_buffer.h
	 c++ $(CFLAGS) ../../core_web/tcp_oscar_dialog_server.cpp -o $(OBJDIR)/tcp_oscar_dialog_server.o

./objD/tcp_sender.o: ../../core_web/tcp_sender.cpp ../../stdafx/stdafx.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/lockctl.h \
  ../../core_web/tcp_server_data.h ../../core/M_DEQUE.h \
  ../../core_web/tcp_server_connection.h ../../core_web/c_conn.h \
  ../../core/_mutex.h ../../core/m_var.h ../../core/PTR.h \
  ../../core/m_var.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/M_MAP.h ../../core/file_set.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  ../../core/str_lib.h ../../core/m_var.h ../../core/Double.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core_web/tcp_sender.h \
  ../../core/tcp_stats.h ../../core/M_SET.h ../../core/threadable.h \
  ../../core/M_MAP.h /usr/local/include/stlport/cerrno
	 c++ $(CFLAGS) ../../core_web/tcp_sender.cpp -o $(OBJDIR)/tcp_sender.o

./objD/tcp_server.o: ../../core_web/tcp_server.cpp ../../stdafx/stdafx.h \
  ../../core_web/tcp_server_data.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c \
  /usr/local/include/stlport/stl/_relops_cont.h ../../core/M_DEQUE.h \
  ../../core/_mutex.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  ../../core_web/tcp_server_connection.h ../../core_web/c_conn.h \
  ../../core/_mutex.h ../../core/m_var.h ../../core/PTR.h \
  ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/M_MAP.h ../../core_web/tcp_server.h ../../core/threadable.h \
  ../../core/M_MAP.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/errno.h ../../core/str_lib.h \
  ../../core/m_var.h ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/tcp_stats.h
	 c++ $(CFLAGS) ../../core_web/tcp_server.cpp -o $(OBJDIR)/tcp_server.o

./objD/tcp_server_connection.o: ../../core_web/tcp_server_connection.cpp \
  ../../stdafx/stdafx.h /usr/local/include/stlport/string.h \
  /usr/local/include/stlport/errno.h \
  ../../core_web/tcp_server_connection.h ../../core_web/c_conn.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c \
  /usr/local/include/stlport/stl/_relops_cont.h ../../core/_mutex.h \
  /usr/local/include/stlport/pthread.h /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/PTR.h ../../core/errs.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/errs.h ../../core/str_lib.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/mutex_inspector.h \
  ../../core_web/tcp_sender.h
	 c++ $(CFLAGS) ../../core_web/tcp_server_connection.cpp -o $(OBJDIR)/tcp_server_connection.o

./objD/tcp_stats.o: ../../core/tcp_stats.cpp ../../stdafx/stdafx.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/lockctl.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/str_lib.h ../../core/m_var.h ../../core/Double.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/m_var.h
	 c++ $(CFLAGS) ../../core/tcp_stats.cpp -o $(OBJDIR)/tcp_stats.o

./objD/thread_info_report.o: ../../core_web/thread_info_report.cpp \
  ../../stdafx/stdafx.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c \
  ../../core_web/tcp_server_connection.h ../../core_web/c_conn.h \
  ../../core/_mutex.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/PTR.h ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/errs.h ../../core/str_lib.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/st_stuff.h \
  ../../core/str_lib.h /usr/local/include/stlport/errno.h \
  ../../core/file_set.h ../../core/M_LIST.h ../../core/mutex_inspector.h \
  ../../core/M_DEQUE.h ../../core_web/tcp_server_data.h \
  ../../core/M_MAP.h ../../core/tcp_stats.h
	 c++ $(CFLAGS) ../../core_web/thread_info_report.cpp -o $(OBJDIR)/thread_info_report.o

./objD/web_adminfo.o: ../../core_web/web_adminfo.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c \
  ../../core_web/tcp_server_connection.h ../../core_web/c_conn.h \
  ../../core/_mutex.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/PTR.h ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core_web/web_server.h ../../core_web/tcp_server.h \
  ../../core/threadable.h ../../core/M_MAP.h ../../core/M_MAP.h \
  ../../core/M_SET.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h ../../core/file_set.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  ../../core/errs.h ../../core/str_lib.h ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/st_stuff.h \
  ../../core/str_lib.h /usr/local/include/stlport/errno.h \
  ../../core/des_sid.h ../../core/sid_t.h ../../core/mutex_inspector.h \
  ../../core/M_DEQUE.h ../../core_web/tcp_server_data.h \
  ../../core_web/web_connection.h ../../core/sid_t.h \
  ../../core_web/html_out.h ../../core_web/web_server_data.h \
  ../../core_web/c_conn.h ../../core/tcp_stats.h
	 c++ $(CFLAGS) ../../core_web/web_adminfo.cpp -o $(OBJDIR)/web_adminfo.o

./objD/web_cache.o: ../../core_web/web_cache.cpp ../../stdafx/stdafx.h
	 c++ $(CFLAGS) ../../core_web/web_cache.cpp -o $(OBJDIR)/web_cache.o

./objD/web_connection.o: ../../core_web/web_connection.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_relops_cont.h ../../core/sid_t.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/lockctl.h \
  ../../core_web/web_server.h ../../core/PTR.h ../../core/m_var.h \
  ../../core/mutex_inspector.h ../../core_web/tcp_server.h \
  ../../core/m_var.h ../../core/threadable.h ../../core/M_MAP.h \
  ../../core_web/c_conn.h ../../core/_mutex.h ../../core/M_MAP.h \
  ../../core/M_SET.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h ../../core/file_set.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  ../../core/des_sid.h ../../core/sid_t.h ../../core/str_lib.h \
  ../../core/m_var.h ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h \
  ../../core_web/web_connection.h ../../core_web/tcp_server_connection.h \
  ../../core_web/html_out.h ../../core_web/web_tools.h \
  ../../core_web/web_server_data.h ../../core/M_DEQUE.h \
  ../../core_web/c_conn.h ../../core/st_stuff.h ../../core/str_lib.h \
  ../../core/server_config.h ../../core/M_SET.h ../../core/file_set.h \
  ../../core/oscar_buffer.h
	 c++ $(CFLAGS) ../../core_web/web_connection.cpp -o $(OBJDIR)/web_connection.o

./objD/web_connection_ptcp.o: ../../core_web/web_connection_ptcp.cpp \
  ../../stdafx/stdafx.h /usr/local/include/stlport/list \
  /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_relops_cont.h ../../core/sid_t.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/lockctl.h \
  ../../core_web/web_server.h ../../core/PTR.h ../../core/m_var.h \
  ../../core/mutex_inspector.h ../../core_web/tcp_server.h \
  ../../core/m_var.h ../../core/threadable.h ../../core/M_MAP.h \
  ../../core_web/c_conn.h ../../core/_mutex.h ../../core/M_MAP.h \
  ../../core/M_SET.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h ../../core/file_set.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  ../../core/des_sid.h ../../core/sid_t.h ../../core/str_lib.h \
  ../../core/m_var.h ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h \
  ../../core_web/web_connection.h ../../core_web/tcp_server_connection.h \
  ../../core_web/html_out.h ../../core_web/web_tools.h \
  ../../core_web/web_server_data.h ../../core/M_DEQUE.h \
  ../../core_web/c_conn.h ../../core/st_stuff.h ../../core/str_lib.h \
  ../../core/server_config.h ../../core/M_SET.h ../../core/file_set.h \
  ../../core/thread_descr.h
	 c++ $(CFLAGS) ../../core_web/web_connection_ptcp.cpp -o $(OBJDIR)/web_connection_ptcp.o

./objD/web_server.o: ../../core_web/web_server.cpp ../../stdafx/stdafx.h \
  ../../core_web/web_server.h ../../core/PTR.h ../../core/_mutex.h \
  /usr/local/include/stlport/pthread.h /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c ../../core/errs.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/list \
  /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core_web/tcp_server.h ../../core/m_var.h ../../core/threadable.h \
  ../../core/M_MAP.h ../../core_web/c_conn.h ../../core/_mutex.h \
  ../../core/M_MAP.h ../../core/M_SET.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h ../../core/file_set.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  ../../core_web/web_server_data.h ../../core/M_DEQUE.h \
  ../../core_web/c_conn.h ../../core/mutex_inspector.h \
  ../../core_web/tcp_server_data.h ../../core_web/tcp_server_connection.h \
  ../../core_web/web_connection.h ../../core/sid_t.h \
  ../../core_web/html_out.h ../../core/str_lib.h ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core_web/tcp_sender.h
	 c++ $(CFLAGS) ../../core_web/web_server.cpp -o $(OBJDIR)/web_server.o

./objD/web_tools.o: ../../core_web/web_tools.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c \
  ../../core_web/tcp_server_connection.h ../../core_web/c_conn.h \
  ../../core/_mutex.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/PTR.h ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core_web/web_server.h ../../core_web/tcp_server.h \
  ../../core/threadable.h ../../core/M_MAP.h ../../core/M_MAP.h \
  ../../core/M_SET.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h ../../core/file_set.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  ../../core/errs.h ../../core/str_lib.h ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/st_stuff.h \
  ../../core/str_lib.h /usr/local/include/stlport/errno.h \
  ../../core_web/web_tools.h ../../core/sid_t.h ../../core/des_sid.h \
  ../../core/sid_t.h ../../core/server_config.h ../../core/M_SET.h \
  ../../core/file_set.h ../../core/mutex_inspector.h
	 c++ $(CFLAGS) ../../core_web/web_tools.cpp -o $(OBJDIR)/web_tools.o

release: ./libcoreweb_r.a 


./libcoreweb_r.a: \
	$(ROBJDIR)/c_conn.o \
	$(ROBJDIR)/html_out.o \
	$(ROBJDIR)/tcp_dialog_server.o \
	$(ROBJDIR)/tcp_oscar_dialog_server.o \
	$(ROBJDIR)/tcp_sender.o \
	$(ROBJDIR)/tcp_server.o \
	$(ROBJDIR)/tcp_server_connection.o \
	$(ROBJDIR)/tcp_stats.o \
	$(ROBJDIR)/thread_info_report.o \
	$(ROBJDIR)/web_adminfo.o \
	$(ROBJDIR)/web_cache.o \
	$(ROBJDIR)/web_connection.o \
	$(ROBJDIR)/web_connection_ptcp.o \
	$(ROBJDIR)/web_server.o \
	$(ROBJDIR)/web_tools.o 
		 ar -r ./libcoreweb_r.a $(ROBJDIR)/c_conn.o $(ROBJDIR)/html_out.o $(ROBJDIR)/tcp_dialog_server.o $(ROBJDIR)/tcp_oscar_dialog_server.o $(ROBJDIR)/tcp_sender.o $(ROBJDIR)/tcp_server.o $(ROBJDIR)/tcp_server_connection.o $(ROBJDIR)/tcp_stats.o $(ROBJDIR)/thread_info_report.o $(ROBJDIR)/web_adminfo.o $(ROBJDIR)/web_cache.o $(ROBJDIR)/web_connection.o $(ROBJDIR)/web_connection_ptcp.o $(ROBJDIR)/web_server.o $(ROBJDIR)/web_tools.o 

./objR/c_conn.o: ../../core_web/c_conn.cpp ../../stdafx/stdafx.h \
  ../../core_web/c_conn.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c \
  /usr/local/include/stlport/stl/_relops_cont.h ../../core/_mutex.h \
  /usr/local/include/stlport/pthread.h /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/PTR.h ../../core/errs.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/tcp_stats.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/str_lib.h ../../core/m_var.h ../../core/Double.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/st_stuff.h \
  ../../core/str_lib.h ../../core_web/tcp_sender.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/errno.h
	 c++ $(RCFLAGS) ../../core_web/c_conn.cpp -o $(ROBJDIR)/c_conn.o

./objR/html_out.o: ../../core_web/html_out.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_prolog.h \
  /usr/local/include/stlport/stl/config/features.h \
  /usr/local/include/stlport/stl/_stlport_version.h \
  /usr/local/include/stlport/stl/config/user_config.h \
  /usr/local/include/stlport/stl/config/compat.h \
  /usr/local/include/stlport/stl/config/host.h \
  /usr/local/include/stlport/stl/config/_system.h \
  /usr/local/include/stlport/stl/config/_linux.h \
  /usr/local/include/stlport/stl/config/_gcc.h \
  /usr/local/include/stlport/stl/config/stl_confix.h \
  /usr/local/include/stlport/stl/config/_native_headers.h \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c ../../core/PTR.h \
  ../../core/_mutex.h ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core_web/html_out.h ../../core_web/web_tools.h ../../core/m_var.h \
  ../../core/server_config.h ../../core/M_MAP.h ../../core/M_SET.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/file_set.h /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  ../../core/str_lib.h ../../core/m_var.h ../../core/Double.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/oscar_buffer.h
	 c++ $(RCFLAGS) ../../core_web/html_out.cpp -o $(ROBJDIR)/html_out.o

./objR/tcp_dialog_server.o: ../../core_web/tcp_dialog_server.cpp \
  ../../stdafx/stdafx.h ../../core/_mutex.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_prolog.h \
  /usr/local/include/stlport/stl/config/features.h \
  /usr/local/include/stlport/stl/_stlport_version.h \
  /usr/local/include/stlport/stl/config/user_config.h \
  /usr/local/include/stlport/stl/config/compat.h \
  /usr/local/include/stlport/stl/config/host.h \
  /usr/local/include/stlport/stl/config/_system.h \
  /usr/local/include/stlport/stl/config/_linux.h \
  /usr/local/include/stlport/stl/config/_gcc.h \
  /usr/local/include/stlport/stl/config/stl_confix.h \
  /usr/local/include/stlport/stl/config/_native_headers.h \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/lockctl.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/lockctl.h ../../core_web/tcp_dialog_server.h \
  ../../core_web/tcp_server.h ../../core/m_var.h ../../core/threadable.h \
  ../../core/M_MAP.h ../../core_web/c_conn.h ../../core/PTR.h \
  ../../core/m_var.h ../../core/mutex_inspector.h \
  ../../core_web/tcp_server_connection.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/M_SET.h \
  ../../core_web/tcp_server_data.h ../../core/M_DEQUE.h \
  ../../core/M_MAP.h ../../core/str_lib.h ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h
	 c++ $(RCFLAGS) ../../core_web/tcp_dialog_server.cpp -o $(ROBJDIR)/tcp_dialog_server.o

./objR/tcp_oscar_dialog_server.o: ../../core_web/tcp_oscar_dialog_server.cpp \
  ../../stdafx/stdafx.h ../../core/_mutex.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_prolog.h \
  /usr/local/include/stlport/stl/config/features.h \
  /usr/local/include/stlport/stl/_stlport_version.h \
  /usr/local/include/stlport/stl/config/user_config.h \
  /usr/local/include/stlport/stl/config/compat.h \
  /usr/local/include/stlport/stl/config/host.h \
  /usr/local/include/stlport/stl/config/_system.h \
  /usr/local/include/stlport/stl/config/_linux.h \
  /usr/local/include/stlport/stl/config/_gcc.h \
  /usr/local/include/stlport/stl/config/stl_confix.h \
  /usr/local/include/stlport/stl/config/_native_headers.h \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/lockctl.h \
  ../../core/lockctl.h ../../core_web/tcp_oscar_dialog_server.h \
  ../../core_web/tcp_dialog_server.h ../../core_web/tcp_server.h \
  ../../core/m_var.h ../../core/threadable.h ../../core/M_MAP.h \
  ../../core_web/c_conn.h ../../core/PTR.h ../../core/m_var.h \
  ../../core/mutex_inspector.h ../../core_web/tcp_server_connection.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/M_SET.h \
  ../../core/str_lib.h ../../core/m_var.h ../../core/Double.h \
  ../../core/oscar_buffer.h
	 c++ $(RCFLAGS) ../../core_web/tcp_oscar_dialog_server.cpp -o $(ROBJDIR)/tcp_oscar_dialog_server.o

./objR/tcp_sender.o: ../../core_web/tcp_sender.cpp ../../stdafx/stdafx.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/lockctl.h \
  ../../core_web/tcp_server_data.h ../../core/M_DEQUE.h \
  ../../core_web/tcp_server_connection.h ../../core_web/c_conn.h \
  ../../core/_mutex.h ../../core/m_var.h ../../core/PTR.h \
  ../../core/m_var.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/M_MAP.h ../../core/file_set.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  ../../core/str_lib.h ../../core/m_var.h ../../core/Double.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core_web/tcp_sender.h \
  ../../core/tcp_stats.h ../../core/M_SET.h ../../core/threadable.h \
  ../../core/M_MAP.h /usr/local/include/stlport/cerrno
	 c++ $(RCFLAGS) ../../core_web/tcp_sender.cpp -o $(ROBJDIR)/tcp_sender.o

./objR/tcp_server.o: ../../core_web/tcp_server.cpp ../../stdafx/stdafx.h \
  ../../core_web/tcp_server_data.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c \
  /usr/local/include/stlport/stl/_relops_cont.h ../../core/M_DEQUE.h \
  ../../core/_mutex.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  ../../core_web/tcp_server_connection.h ../../core_web/c_conn.h \
  ../../core/_mutex.h ../../core/m_var.h ../../core/PTR.h \
  ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/M_MAP.h ../../core_web/tcp_server.h ../../core/threadable.h \
  ../../core/M_MAP.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/errno.h ../../core/str_lib.h \
  ../../core/m_var.h ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/tcp_stats.h
	 c++ $(RCFLAGS) ../../core_web/tcp_server.cpp -o $(ROBJDIR)/tcp_server.o

./objR/tcp_server_connection.o: ../../core_web/tcp_server_connection.cpp \
  ../../stdafx/stdafx.h /usr/local/include/stlport/string.h \
  /usr/local/include/stlport/errno.h \
  ../../core_web/tcp_server_connection.h ../../core_web/c_conn.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c \
  /usr/local/include/stlport/stl/_relops_cont.h ../../core/_mutex.h \
  /usr/local/include/stlport/pthread.h /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/PTR.h ../../core/errs.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/errs.h ../../core/str_lib.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/mutex_inspector.h \
  ../../core_web/tcp_sender.h
	 c++ $(RCFLAGS) ../../core_web/tcp_server_connection.cpp -o $(ROBJDIR)/tcp_server_connection.o

./objR/tcp_stats.o: ../../core/tcp_stats.cpp ../../stdafx/stdafx.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/lockctl.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/str_lib.h ../../core/m_var.h ../../core/Double.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/m_var.h
	 c++ $(RCFLAGS) ../../core/tcp_stats.cpp -o $(ROBJDIR)/tcp_stats.o

./objR/thread_info_report.o: ../../core_web/thread_info_report.cpp \
  ../../stdafx/stdafx.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c \
  ../../core_web/tcp_server_connection.h ../../core_web/c_conn.h \
  ../../core/_mutex.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/PTR.h ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/errs.h ../../core/str_lib.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/st_stuff.h \
  ../../core/str_lib.h /usr/local/include/stlport/errno.h \
  ../../core/file_set.h ../../core/M_LIST.h ../../core/mutex_inspector.h \
  ../../core/M_DEQUE.h ../../core_web/tcp_server_data.h \
  ../../core/M_MAP.h ../../core/tcp_stats.h
	 c++ $(RCFLAGS) ../../core_web/thread_info_report.cpp -o $(ROBJDIR)/thread_info_report.o

./objR/web_adminfo.o: ../../core_web/web_adminfo.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c \
  ../../core_web/tcp_server_connection.h ../../core_web/c_conn.h \
  ../../core/_mutex.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/PTR.h ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core_web/web_server.h ../../core_web/tcp_server.h \
  ../../core/threadable.h ../../core/M_MAP.h ../../core/M_MAP.h \
  ../../core/M_SET.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h ../../core/file_set.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  ../../core/errs.h ../../core/str_lib.h ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/st_stuff.h \
  ../../core/str_lib.h /usr/local/include/stlport/errno.h \
  ../../core/des_sid.h ../../core/sid_t.h ../../core/mutex_inspector.h \
  ../../core/M_DEQUE.h ../../core_web/tcp_server_data.h \
  ../../core_web/web_connection.h ../../core/sid_t.h \
  ../../core_web/html_out.h ../../core_web/web_server_data.h \
  ../../core_web/c_conn.h ../../core/tcp_stats.h
	 c++ $(RCFLAGS) ../../core_web/web_adminfo.cpp -o $(ROBJDIR)/web_adminfo.o

./objR/web_cache.o: ../../core_web/web_cache.cpp ../../stdafx/stdafx.h
	 c++ $(RCFLAGS) ../../core_web/web_cache.cpp -o $(ROBJDIR)/web_cache.o

./objR/web_connection.o: ../../core_web/web_connection.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_relops_cont.h ../../core/sid_t.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/lockctl.h \
  ../../core_web/web_server.h ../../core/PTR.h ../../core/m_var.h \
  ../../core/mutex_inspector.h ../../core_web/tcp_server.h \
  ../../core/m_var.h ../../core/threadable.h ../../core/M_MAP.h \
  ../../core_web/c_conn.h ../../core/_mutex.h ../../core/M_MAP.h \
  ../../core/M_SET.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h ../../core/file_set.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  ../../core/des_sid.h ../../core/sid_t.h ../../core/str_lib.h \
  ../../core/m_var.h ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h \
  ../../core_web/web_connection.h ../../core_web/tcp_server_connection.h \
  ../../core_web/html_out.h ../../core_web/web_tools.h \
  ../../core_web/web_server_data.h ../../core/M_DEQUE.h \
  ../../core_web/c_conn.h ../../core/st_stuff.h ../../core/str_lib.h \
  ../../core/server_config.h ../../core/M_SET.h ../../core/file_set.h \
  ../../core/oscar_buffer.h
	 c++ $(RCFLAGS) ../../core_web/web_connection.cpp -o $(ROBJDIR)/web_connection.o

./objR/web_connection_ptcp.o: ../../core_web/web_connection_ptcp.cpp \
  ../../stdafx/stdafx.h /usr/local/include/stlport/list \
  /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_relops_cont.h ../../core/sid_t.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/lockctl.h \
  ../../core_web/web_server.h ../../core/PTR.h ../../core/m_var.h \
  ../../core/mutex_inspector.h ../../core_web/tcp_server.h \
  ../../core/m_var.h ../../core/threadable.h ../../core/M_MAP.h \
  ../../core_web/c_conn.h ../../core/_mutex.h ../../core/M_MAP.h \
  ../../core/M_SET.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h ../../core/file_set.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  ../../core/des_sid.h ../../core/sid_t.h ../../core/str_lib.h \
  ../../core/m_var.h ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h \
  ../../core_web/web_connection.h ../../core_web/tcp_server_connection.h \
  ../../core_web/html_out.h ../../core_web/web_tools.h \
  ../../core_web/web_server_data.h ../../core/M_DEQUE.h \
  ../../core_web/c_conn.h ../../core/st_stuff.h ../../core/str_lib.h \
  ../../core/server_config.h ../../core/M_SET.h ../../core/file_set.h \
  ../../core/thread_descr.h
	 c++ $(RCFLAGS) ../../core_web/web_connection_ptcp.cpp -o $(ROBJDIR)/web_connection_ptcp.o

./objR/web_server.o: ../../core_web/web_server.cpp ../../stdafx/stdafx.h \
  ../../core_web/web_server.h ../../core/PTR.h ../../core/_mutex.h \
  /usr/local/include/stlport/pthread.h /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c ../../core/errs.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/list \
  /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core_web/tcp_server.h ../../core/m_var.h ../../core/threadable.h \
  ../../core/M_MAP.h ../../core_web/c_conn.h ../../core/_mutex.h \
  ../../core/M_MAP.h ../../core/M_SET.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h ../../core/file_set.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  ../../core_web/web_server_data.h ../../core/M_DEQUE.h \
  ../../core_web/c_conn.h ../../core/mutex_inspector.h \
  ../../core_web/tcp_server_data.h ../../core_web/tcp_server_connection.h \
  ../../core_web/web_connection.h ../../core/sid_t.h \
  ../../core_web/html_out.h ../../core/str_lib.h ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core_web/tcp_sender.h
	 c++ $(RCFLAGS) ../../core_web/web_server.cpp -o $(ROBJDIR)/web_server.o

./objR/web_tools.o: ../../core_web/web_tools.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c \
  ../../core_web/tcp_server_connection.h ../../core_web/c_conn.h \
  ../../core/_mutex.h /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_string_io.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/PTR.h ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core_web/web_server.h ../../core_web/tcp_server.h \
  ../../core/threadable.h ../../core/M_MAP.h ../../core/M_MAP.h \
  ../../core/M_SET.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h ../../core/file_set.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  ../../core/errs.h ../../core/str_lib.h ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/algorithm \
  /usr/local/include/stlport/stl/_cstdio.h \
  /usr/local/include/stlport/stl/_algo.h \
  /usr/local/include/stlport/stl/_heap.h \
  /usr/local/include/stlport/stl/_heap.c \
  /usr/local/include/stlport/stl/_algo.c \
  /usr/local/include/stlport/stl/_tempbuf.h \
  /usr/local/include/stlport/stl/_tempbuf.c \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/st_stuff.h \
  ../../core/str_lib.h /usr/local/include/stlport/errno.h \
  ../../core_web/web_tools.h ../../core/sid_t.h ../../core/des_sid.h \
  ../../core/sid_t.h ../../core/server_config.h ../../core/M_SET.h \
  ../../core/file_set.h ../../core/mutex_inspector.h
	 c++ $(RCFLAGS) ../../core_web/web_tools.cpp -o $(ROBJDIR)/web_tools.o

clean:
	 rm   z.out kaka.xxx file_dump.cpp TERM* 1 2

both: all release



cleanobjs:
	 rm $(OBJDIR)/c_conn.o $(OBJDIR)/html_out.o $(OBJDIR)/tcp_dialog_server.o $(OBJDIR)/tcp_oscar_dialog_server.o $(OBJDIR)/tcp_sender.o $(OBJDIR)/tcp_server.o $(OBJDIR)/tcp_server_connection.o $(OBJDIR)/tcp_stats.o $(OBJDIR)/thread_info_report.o $(OBJDIR)/web_adminfo.o $(OBJDIR)/web_cache.o $(OBJDIR)/web_connection.o $(OBJDIR)/web_connection_ptcp.o $(OBJDIR)/web_server.o $(OBJDIR)/web_tools.o $(ROBJDIR)/c_conn.o $(ROBJDIR)/html_out.o $(ROBJDIR)/tcp_dialog_server.o $(ROBJDIR)/tcp_oscar_dialog_server.o $(ROBJDIR)/tcp_sender.o $(ROBJDIR)/tcp_server.o $(ROBJDIR)/tcp_server_connection.o $(ROBJDIR)/tcp_stats.o $(ROBJDIR)/thread_info_report.o $(ROBJDIR)/web_adminfo.o $(ROBJDIR)/web_cache.o $(ROBJDIR)/web_connection.o $(ROBJDIR)/web_connection_ptcp.o $(ROBJDIR)/web_server.o $(ROBJDIR)/web_tools.o ./libcoreweb_d.a ./libcoreweb_r.a


cleanall: clean cleanobjs


