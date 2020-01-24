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

all: ./libcommon_d.a 


./libcommon_d.a: \
	$(OBJDIR)/Double.o\
	$(OBJDIR)/PTR.o\
	$(OBJDIR)/_QUERY.o\
	$(OBJDIR)/__main.o\
	$(OBJDIR)/_mutex.o\
	$(OBJDIR)/_mutex1.o\
	$(OBJDIR)/copy_file_common.o\
	$(OBJDIR)/core_main.o\
	$(OBJDIR)/db_config2.o\
	$(OBJDIR)/db_var.o\
	$(OBJDIR)/des_sid.o\
	$(OBJDIR)/errs.o\
	$(OBJDIR)/file_set.o\
	$(OBJDIR)/file_set_init.o\
	$(OBJDIR)/mutex_inspector.o\
	$(OBJDIR)/mysql_extens.o\
	$(OBJDIR)/mysql_extens2.o\
	$(OBJDIR)/oscar_buffer.o\
	$(OBJDIR)/rijndael.o\
	$(OBJDIR)/server_config.o\
	$(OBJDIR)/st_FILE.o\
	$(OBJDIR)/st_rsa.o\
	$(OBJDIR)/st_savecwd.o\
	$(OBJDIR)/st_stream_str.o\
	$(OBJDIR)/st_stuff.o\
	$(OBJDIR)/str_lib.o\
	$(OBJDIR)/str_lib1.o\
	$(OBJDIR)/str_lib_extra.o\
	$(OBJDIR)/threadable.o\
	$(OBJDIR)/wrappers.o
		 ar -r ./libcommon_d.a $(OBJDIR)/Double.o $(OBJDIR)/PTR.o $(OBJDIR)/_QUERY.o $(OBJDIR)/__main.o $(OBJDIR)/_mutex.o $(OBJDIR)/_mutex1.o $(OBJDIR)/copy_file_common.o $(OBJDIR)/core_main.o $(OBJDIR)/db_config2.o $(OBJDIR)/db_var.o $(OBJDIR)/des_sid.o $(OBJDIR)/errs.o $(OBJDIR)/file_set.o $(OBJDIR)/file_set_init.o $(OBJDIR)/mutex_inspector.o $(OBJDIR)/mysql_extens.o $(OBJDIR)/mysql_extens2.o $(OBJDIR)/oscar_buffer.o $(OBJDIR)/rijndael.o $(OBJDIR)/server_config.o $(OBJDIR)/st_FILE.o $(OBJDIR)/st_rsa.o $(OBJDIR)/st_savecwd.o $(OBJDIR)/st_stream_str.o $(OBJDIR)/st_stuff.o $(OBJDIR)/str_lib.o $(OBJDIR)/str_lib1.o $(OBJDIR)/str_lib_extra.o $(OBJDIR)/threadable.o $(OBJDIR)/wrappers.o 

./objD/Double.o: ../../core/Double.cpp ../../stdafx/stdafx.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/vector \
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
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_string_io.c \
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
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c ../../core/Double.h \
  ../../core/str_lib.h ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h
	 c++ $(CFLAGS) ../../core/Double.cpp -o $(OBJDIR)/Double.o

./objD/PTR.o: ../../core/PTR.cpp ../../stdafx/stdafx.h \
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
  /usr/local/include/stlport/stl/_config_compat_post.h ../../core/PTR.h \
  ../../core/_mutex.h ../../core/errs.h /usr/local/include/stlport/vector \
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
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h
	 c++ $(CFLAGS) ../../core/PTR.cpp -o $(OBJDIR)/PTR.o

./objD/_QUERY.o: ../../core/_QUERY.cpp ../../stdafx/stdafx.h ../../core/_mutex.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h ../../core/_QUERY.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h ../../core/mysql_extens.h \
  ../../core/str_lib.h /usr/local/include/stlport/list \
  /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
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
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h
	 c++ $(CFLAGS) ../../core/_QUERY.cpp -o $(OBJDIR)/_QUERY.o

./objD/__main.o: ../../core/__main.cpp ../../stdafx/stdafx.h
	 c++ $(CFLAGS) ../../core/__main.cpp -o $(OBJDIR)/__main.o

./objD/_mutex.o: ../../core/_mutex.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/list \
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
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h ../../core/errs.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/_mutex.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  /usr/local/include/stlport/errno.h ../../core/str_lib.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
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
  /usr/local/include/stlport/stl/_hash_set.h
	 c++ $(CFLAGS) ../../core/_mutex.cpp -o $(OBJDIR)/_mutex.o

./objD/_mutex1.o: ../../core/_mutex1.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/list \
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
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h ../../core/errs.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/_mutex.h \
  ../../core/_mutex1.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  /usr/local/include/stlport/errno.h ../../core/str_lib.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
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
  /usr/local/include/stlport/stl/_hash_set.h
	 c++ $(CFLAGS) ../../core/_mutex1.cpp -o $(OBJDIR)/_mutex1.o

./objD/copy_file_common.o: ../../core/copy_file_common.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/errno.h ../../core/str_lib.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h ../../core/m_var.h \
  ../../core/M_MAP.h ../../core/st_stuff.h ../../core/copy_file.h \
  ../../core/wrappers.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h
	 c++ $(CFLAGS) ../../core/copy_file_common.cpp -o $(OBJDIR)/copy_file_common.o

./objD/core_main.o: ../../core/core_main.cpp ../../stdafx/stdafx.h \
  ../../core/server_config.h ../../core/_mutex.h \
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
  /usr/local/include/stlport/stl/_string_io.c ../../core/M_MAP.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h ../../core/M_SET.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/m_var.h ../../core/file_set.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
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
  /usr/local/include/stlport/stl/_hash_set.h
	 c++ $(CFLAGS) ../../core/core_main.cpp -o $(OBJDIR)/core_main.o

./objD/db_config2.o: ../../core/db_config2.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/signal.h \
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
  /usr/local/include/stlport/errno.h ../../core/mutex_inspector.h \
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
  ../../core/db_config2.h ../../core/M_MAP.h ../../core/M_SET.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/m_var.h ../../core/str_lib.h ../../core/m_var.h \
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
  /usr/local/include/stlport/stl/_hash_set.h
	 c++ $(CFLAGS) ../../core/db_config2.cpp -o $(OBJDIR)/db_config2.o

./objD/db_var.o: ../../core/db_var.cpp ../../stdafx/stdafx.h
	 c++ $(CFLAGS) ../../core/db_var.cpp -o $(OBJDIR)/db_var.o

./objD/des_sid.o: ../../core/des_sid.cpp ../../stdafx/stdafx.h \
  ../../core/str_lib.h /usr/local/include/stlport/string \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  ../../core/m_var.h ../../core/des_locl.h ../../core/sid_t.h \
  ../../core/des_sid.h
	 c++ $(CFLAGS) ../../core/des_sid.cpp -o $(OBJDIR)/des_sid.o

./objD/errs.o: ../../core/errs.cpp ../../stdafx/stdafx.h ../../core/errs.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/cstdarg \
  /usr/local/include/stlport/stl/_cstdarg.h ../../core/m_var.h \
  ../../core/server_config.h ../../core/M_MAP.h ../../core/M_SET.h \
  ../../core/file_set.h ../../core/M_LIST.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/st_stuff.h
	 c++ $(CFLAGS) ../../core/errs.cpp -o $(OBJDIR)/errs.o

./objD/file_set.o: ../../core/file_set.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/errno.h \
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
  ../../core/wrappers.h /usr/local/include/stlport/stdio.h \
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
  /usr/local/include/stlport/stl/_string_io.c ../../core/file_set.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/vector ../../core/M_LIST.h \
  ../../core/_mutex.h /usr/local/include/stlport/list \
  /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/lockctl.h \
  ../../core/str_lib.h /usr/local/include/stlport/set \
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
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/st_stuff.h \
  ../../core/server_config.h ../../core/M_MAP.h ../../core/M_SET.h
	 c++ $(CFLAGS) ../../core/file_set.cpp -o $(OBJDIR)/file_set.o

./objD/file_set_init.o: ../../core/file_set_init.cpp ../../stdafx/stdafx.h \
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
  /usr/local/include/stlport/stdio.h ../../core/_mutex.h \
  /usr/local/include/stlport/pthread.h /usr/local/include/stlport/string \
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
  /usr/local/include/stlport/stl/_string_io.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
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
  /usr/local/include/stlport/errno.h ../../core/file_set.h \
  ../../core/M_LIST.h ../../core/m_var.h ../../core/st_stream_str.h \
  ../../core/st_rsa.h ../../core/copy_file.h ../../core/wrappers.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/server_config.h ../../core/M_MAP.h ../../core/M_SET.h
	 c++ $(CFLAGS) ../../core/file_set_init.cpp -o $(OBJDIR)/file_set_init.o

./objD/mutex_inspector.o: ../../core/mutex_inspector.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_prolog.h \
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
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_range_errors.h ../../core/errs.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h ../../core/_mutex1.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/M_MAP.h
	 c++ $(CFLAGS) ../../core/mutex_inspector.cpp -o $(OBJDIR)/mutex_inspector.o

./objD/mysql_extens.o: ../../core/mysql_extens.cpp ../../stdafx/stdafx.h \
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
  ../../core/str_lib.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h ../../core/mysql_extens.h \
  ../../core/_QUERY.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/file_set.h ../../core/M_LIST.h ../../core/m_var.h \
  ../../core/st_stuff.h ../../core/db_config2.h ../../core/M_MAP.h \
  ../../core/M_SET.h
	 c++ $(CFLAGS) ../../core/mysql_extens.cpp -o $(OBJDIR)/mysql_extens.o

./objD/mysql_extens2.o: ../../core/mysql_extens2.cpp ../../stdafx/stdafx.h \
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
  ../../core/str_lib.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h ../../core/mysql_extens.h \
  ../../core/_QUERY.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/file_set.h ../../core/M_LIST.h ../../core/m_var.h \
  ../../core/st_stuff.h ../../core/db_config2.h ../../core/M_MAP.h \
  ../../core/M_SET.h
	 c++ $(CFLAGS) ../../core/mysql_extens2.cpp -o $(OBJDIR)/mysql_extens2.o

./objD/oscar_buffer.o: ../../core/oscar_buffer.cpp ../../stdafx/stdafx.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/vector \
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
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_string_io.c \
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
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c ../../core/str_lib.h \
  ../../core/errs.h /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h
	 c++ $(CFLAGS) ../../core/oscar_buffer.cpp -o $(OBJDIR)/oscar_buffer.o

./objD/rijndael.o: ../../core/rijndael.cpp ../../core/rijndael.h \
  /usr/local/include/stlport/stdlib.h \
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
  /usr/local/include/stlport/string.h /usr/local/include/stlport/stdio.h
	 c++ $(CFLAGS) ../../core/rijndael.cpp -o $(OBJDIR)/rijndael.o

./objD/server_config.o: ../../core/server_config.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/signal.h \
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
  /usr/local/include/stlport/errno.h ../../core/mutex_inspector.h \
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
  ../../core/str_lib.h /usr/local/include/stlport/set \
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
  /usr/local/include/stlport/stl/_hash_set.h ../../core/server_config.h \
  ../../core/M_MAP.h ../../core/M_SET.h ../../core/m_var.h \
  ../../core/file_set.h ../../core/M_LIST.h ../../core/wrappers.h \
  ../../core/st_stuff.h
	 c++ $(CFLAGS) ../../core/server_config.cpp -o $(OBJDIR)/server_config.o

./objD/st_FILE.o: ../../core/st_FILE.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/stdio.h \
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
  /usr/local/include/stlport/stdlib.h /usr/local/include/stlport/string.h \
  ../../core/st_stuff.h ../../core/errs.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/errno.h ../../core/copy_file.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/wrappers.h
	 c++ $(CFLAGS) ../../core/st_FILE.cpp -o $(OBJDIR)/st_FILE.o

./objD/st_rsa.o: ../../core/st_rsa.cpp ../../stdafx/stdafx.h \
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
  ../../core/st_stuff.h ../../core/errs.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/m_var.h ../../core/st_rsa.h
	 c++ $(CFLAGS) ../../core/st_rsa.cpp -o $(OBJDIR)/st_rsa.o

./objD/st_savecwd.o: ../../core/st_savecwd.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/stdio.h \
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
  /usr/local/include/stlport/stdlib.h /usr/local/include/stlport/string.h \
  ../../core/st_stuff.h ../../core/errs.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/errno.h ../../core/copy_file.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h
	 c++ $(CFLAGS) ../../core/st_savecwd.cpp -o $(OBJDIR)/st_savecwd.o

./objD/st_stream_str.o: ../../core/st_stream_str.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/stdio.h \
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
  /usr/local/include/stlport/stdlib.h /usr/local/include/stlport/string.h \
  ../../core/str_lib.h /usr/local/include/stlport/string \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/errno.h ../../core/st_stream_str.h \
  ../../core/st_stuff.h
	 c++ $(CFLAGS) ../../core/st_stream_str.cpp -o $(OBJDIR)/st_stream_str.o

./objD/st_stuff.o: ../../core/st_stuff.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/stdio.h \
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
  /usr/local/include/stlport/stdlib.h /usr/local/include/stlport/string.h \
  ../../core/st_stuff.h ../../core/errs.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/errno.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h
	 c++ $(CFLAGS) ../../core/st_stuff.cpp -o $(OBJDIR)/st_stuff.o

./objD/str_lib.o: ../../core/str_lib.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/iostream \
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
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/fstream \
  /usr/local/include/stlport/stl/_fstream.h \
  /usr/local/include/stlport/stl/_codecvt.h \
  /usr/local/include/stlport/stl/_fstream.c \
  /usr/local/include/stlport/sstream \
  /usr/local/include/stlport/stl/_sstream.h \
  /usr/local/include/stlport/stl/_sstream.c \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
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
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/errno.h /usr/local/include/stlport/cerrno \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  /usr/local/include/stlport/cstdarg \
  /usr/local/include/stlport/stl/_cstdarg.h
	 c++ $(CFLAGS) ../../core/str_lib.cpp -o $(OBJDIR)/str_lib.o

./objD/str_lib1.o: ../../core/str_lib1.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/iostream \
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
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/fstream \
  /usr/local/include/stlport/stl/_fstream.h \
  /usr/local/include/stlport/stl/_codecvt.h \
  /usr/local/include/stlport/stl/_fstream.c \
  /usr/local/include/stlport/sstream \
  /usr/local/include/stlport/stl/_sstream.h \
  /usr/local/include/stlport/stl/_sstream.c \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c ../../core/oscar_buffer.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
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
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c ../../core/Double.h \
  ../../core/_mutex.h ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  ../../core/m_var.h /usr/local/include/stlport/errno.h \
  /usr/local/include/stlport/cerrno ../../core/mutex_inspector.h \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  /usr/local/include/stlport/cstdarg \
  /usr/local/include/stlport/stl/_cstdarg.h
	 c++ $(CFLAGS) ../../core/str_lib1.cpp -o $(OBJDIR)/str_lib1.o

./objD/str_lib_extra.o: ../../core/str_lib_extra.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/iostream \
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
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/fstream \
  /usr/local/include/stlport/stl/_fstream.h \
  /usr/local/include/stlport/stl/_codecvt.h \
  /usr/local/include/stlport/stl/_fstream.c \
  /usr/local/include/stlport/sstream \
  /usr/local/include/stlport/stl/_sstream.h \
  /usr/local/include/stlport/stl/_sstream.c \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
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
  /usr/local/include/stlport/errno.h /usr/local/include/stlport/cerrno \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  /usr/local/include/stlport/cstdarg \
  /usr/local/include/stlport/stl/_cstdarg.h ../../core/st_stream_str.h
	 c++ $(CFLAGS) ../../core/str_lib_extra.cpp -o $(OBJDIR)/str_lib_extra.o

./objD/threadable.o: ../../core/threadable.cpp ../../stdafx/stdafx.h \
  ../../core/threadable.h ../../core/M_MAP.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_prolog.h \
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
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/list \
  /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/str_lib.h /usr/local/include/stlport/set \
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
  /usr/local/include/stlport/stl/_hash_set.h
	 c++ $(CFLAGS) ../../core/threadable.cpp -o $(OBJDIR)/threadable.o

./objD/wrappers.o: ../../core/wrappers.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/stdlib.h \
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
  ../../core/str_lib.h /usr/local/include/stlport/string \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h ../../core/copy_file.h \
  ../../core/wrappers.h /usr/local/include/stlport/errno.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/tcp_stats.h
	 c++ $(CFLAGS) ../../core/wrappers.cpp -o $(OBJDIR)/wrappers.o

release: ./libcommon_r.a 


./libcommon_r.a: \
	$(ROBJDIR)/Double.o \
	$(ROBJDIR)/PTR.o \
	$(ROBJDIR)/_QUERY.o \
	$(ROBJDIR)/__main.o \
	$(ROBJDIR)/_mutex.o \
	$(ROBJDIR)/_mutex1.o \
	$(ROBJDIR)/copy_file_common.o \
	$(ROBJDIR)/core_main.o \
	$(ROBJDIR)/db_config2.o \
	$(ROBJDIR)/db_var.o \
	$(ROBJDIR)/des_sid.o \
	$(ROBJDIR)/errs.o \
	$(ROBJDIR)/file_set.o \
	$(ROBJDIR)/file_set_init.o \
	$(ROBJDIR)/mutex_inspector.o \
	$(ROBJDIR)/mysql_extens.o \
	$(ROBJDIR)/mysql_extens2.o \
	$(ROBJDIR)/oscar_buffer.o \
	$(ROBJDIR)/rijndael.o \
	$(ROBJDIR)/server_config.o \
	$(ROBJDIR)/st_FILE.o \
	$(ROBJDIR)/st_rsa.o \
	$(ROBJDIR)/st_savecwd.o \
	$(ROBJDIR)/st_stream_str.o \
	$(ROBJDIR)/st_stuff.o \
	$(ROBJDIR)/str_lib.o \
	$(ROBJDIR)/str_lib1.o \
	$(ROBJDIR)/str_lib_extra.o \
	$(ROBJDIR)/threadable.o \
	$(ROBJDIR)/wrappers.o 
		 ar -r ./libcommon_r.a $(ROBJDIR)/Double.o $(ROBJDIR)/PTR.o $(ROBJDIR)/_QUERY.o $(ROBJDIR)/__main.o $(ROBJDIR)/_mutex.o $(ROBJDIR)/_mutex1.o $(ROBJDIR)/copy_file_common.o $(ROBJDIR)/core_main.o $(ROBJDIR)/db_config2.o $(ROBJDIR)/db_var.o $(ROBJDIR)/des_sid.o $(ROBJDIR)/errs.o $(ROBJDIR)/file_set.o $(ROBJDIR)/file_set_init.o $(ROBJDIR)/mutex_inspector.o $(ROBJDIR)/mysql_extens.o $(ROBJDIR)/mysql_extens2.o $(ROBJDIR)/oscar_buffer.o $(ROBJDIR)/rijndael.o $(ROBJDIR)/server_config.o $(ROBJDIR)/st_FILE.o $(ROBJDIR)/st_rsa.o $(ROBJDIR)/st_savecwd.o $(ROBJDIR)/st_stream_str.o $(ROBJDIR)/st_stuff.o $(ROBJDIR)/str_lib.o $(ROBJDIR)/str_lib1.o $(ROBJDIR)/str_lib_extra.o $(ROBJDIR)/threadable.o $(ROBJDIR)/wrappers.o 

./objR/Double.o: ../../core/Double.cpp ../../stdafx/stdafx.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/vector \
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
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_string_io.c \
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
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c ../../core/Double.h \
  ../../core/str_lib.h ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h
	 c++ $(RCFLAGS) ../../core/Double.cpp -o $(ROBJDIR)/Double.o

./objR/PTR.o: ../../core/PTR.cpp ../../stdafx/stdafx.h \
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
  /usr/local/include/stlport/stl/_config_compat_post.h ../../core/PTR.h \
  ../../core/_mutex.h ../../core/errs.h /usr/local/include/stlport/vector \
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
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h
	 c++ $(RCFLAGS) ../../core/PTR.cpp -o $(ROBJDIR)/PTR.o

./objR/_QUERY.o: ../../core/_QUERY.cpp ../../stdafx/stdafx.h ../../core/_mutex.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h ../../core/_QUERY.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h ../../core/mysql_extens.h \
  ../../core/str_lib.h /usr/local/include/stlport/list \
  /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
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
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h
	 c++ $(RCFLAGS) ../../core/_QUERY.cpp -o $(ROBJDIR)/_QUERY.o

./objR/__main.o: ../../core/__main.cpp ../../stdafx/stdafx.h
	 c++ $(RCFLAGS) ../../core/__main.cpp -o $(ROBJDIR)/__main.o

./objR/_mutex.o: ../../core/_mutex.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/list \
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
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h ../../core/errs.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/_mutex.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  /usr/local/include/stlport/errno.h ../../core/str_lib.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
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
  /usr/local/include/stlport/stl/_hash_set.h
	 c++ $(RCFLAGS) ../../core/_mutex.cpp -o $(ROBJDIR)/_mutex.o

./objR/_mutex1.o: ../../core/_mutex1.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/list \
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
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h ../../core/errs.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/_mutex.h \
  ../../core/_mutex1.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  /usr/local/include/stlport/errno.h ../../core/str_lib.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
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
  /usr/local/include/stlport/stl/_hash_set.h
	 c++ $(RCFLAGS) ../../core/_mutex1.cpp -o $(ROBJDIR)/_mutex1.o

./objR/copy_file_common.o: ../../core/copy_file_common.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/errno.h ../../core/str_lib.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h ../../core/m_var.h \
  ../../core/M_MAP.h ../../core/st_stuff.h ../../core/copy_file.h \
  ../../core/wrappers.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h
	 c++ $(RCFLAGS) ../../core/copy_file_common.cpp -o $(ROBJDIR)/copy_file_common.o

./objR/core_main.o: ../../core/core_main.cpp ../../stdafx/stdafx.h \
  ../../core/server_config.h ../../core/_mutex.h \
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
  /usr/local/include/stlport/stl/_string_io.c ../../core/M_MAP.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h ../../core/M_SET.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/m_var.h ../../core/file_set.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h ../../core/M_LIST.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
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
  /usr/local/include/stlport/stl/_hash_set.h
	 c++ $(RCFLAGS) ../../core/core_main.cpp -o $(ROBJDIR)/core_main.o

./objR/db_config2.o: ../../core/db_config2.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/signal.h \
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
  /usr/local/include/stlport/errno.h ../../core/mutex_inspector.h \
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
  ../../core/db_config2.h ../../core/M_MAP.h ../../core/M_SET.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  ../../core/m_var.h ../../core/str_lib.h ../../core/m_var.h \
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
  /usr/local/include/stlport/stl/_hash_set.h
	 c++ $(RCFLAGS) ../../core/db_config2.cpp -o $(ROBJDIR)/db_config2.o

./objR/db_var.o: ../../core/db_var.cpp ../../stdafx/stdafx.h
	 c++ $(RCFLAGS) ../../core/db_var.cpp -o $(ROBJDIR)/db_var.o

./objR/des_sid.o: ../../core/des_sid.cpp ../../stdafx/stdafx.h \
  ../../core/str_lib.h /usr/local/include/stlport/string \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  ../../core/m_var.h ../../core/des_locl.h ../../core/sid_t.h \
  ../../core/des_sid.h
	 c++ $(RCFLAGS) ../../core/des_sid.cpp -o $(ROBJDIR)/des_sid.o

./objR/errs.o: ../../core/errs.cpp ../../stdafx/stdafx.h ../../core/errs.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/cstdarg \
  /usr/local/include/stlport/stl/_cstdarg.h ../../core/m_var.h \
  ../../core/server_config.h ../../core/M_MAP.h ../../core/M_SET.h \
  ../../core/file_set.h ../../core/M_LIST.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/st_stuff.h
	 c++ $(RCFLAGS) ../../core/errs.cpp -o $(ROBJDIR)/errs.o

./objR/file_set.o: ../../core/file_set.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/errno.h \
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
  ../../core/wrappers.h /usr/local/include/stlport/stdio.h \
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
  /usr/local/include/stlport/stl/_string_io.c ../../core/file_set.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/vector ../../core/M_LIST.h \
  ../../core/_mutex.h /usr/local/include/stlport/list \
  /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c ../../core/m_var.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/lockctl.h \
  ../../core/str_lib.h /usr/local/include/stlport/set \
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
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h ../../core/st_stuff.h \
  ../../core/server_config.h ../../core/M_MAP.h ../../core/M_SET.h
	 c++ $(RCFLAGS) ../../core/file_set.cpp -o $(ROBJDIR)/file_set.o

./objR/file_set_init.o: ../../core/file_set_init.cpp ../../stdafx/stdafx.h \
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
  /usr/local/include/stlport/stdio.h ../../core/_mutex.h \
  /usr/local/include/stlport/pthread.h /usr/local/include/stlport/string \
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
  /usr/local/include/stlport/stl/_string_io.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
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
  /usr/local/include/stlport/errno.h ../../core/file_set.h \
  ../../core/M_LIST.h ../../core/m_var.h ../../core/st_stream_str.h \
  ../../core/st_rsa.h ../../core/copy_file.h ../../core/wrappers.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/server_config.h ../../core/M_MAP.h ../../core/M_SET.h
	 c++ $(RCFLAGS) ../../core/file_set_init.cpp -o $(ROBJDIR)/file_set_init.o

./objR/mutex_inspector.o: ../../core/mutex_inspector.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_prolog.h \
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
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_range_errors.h ../../core/errs.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h ../../core/_mutex1.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/M_MAP.h
	 c++ $(RCFLAGS) ../../core/mutex_inspector.cpp -o $(ROBJDIR)/mutex_inspector.o

./objR/mysql_extens.o: ../../core/mysql_extens.cpp ../../stdafx/stdafx.h \
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
  ../../core/str_lib.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h ../../core/mysql_extens.h \
  ../../core/_QUERY.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/file_set.h ../../core/M_LIST.h ../../core/m_var.h \
  ../../core/st_stuff.h ../../core/db_config2.h ../../core/M_MAP.h \
  ../../core/M_SET.h
	 c++ $(RCFLAGS) ../../core/mysql_extens.cpp -o $(ROBJDIR)/mysql_extens.o

./objR/mysql_extens2.o: ../../core/mysql_extens2.cpp ../../stdafx/stdafx.h \
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
  ../../core/str_lib.h /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h ../../core/mysql_extens.h \
  ../../core/_QUERY.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/file_set.h ../../core/M_LIST.h ../../core/m_var.h \
  ../../core/st_stuff.h ../../core/db_config2.h ../../core/M_MAP.h \
  ../../core/M_SET.h
	 c++ $(RCFLAGS) ../../core/mysql_extens2.cpp -o $(ROBJDIR)/mysql_extens2.o

./objR/oscar_buffer.o: ../../core/oscar_buffer.cpp ../../stdafx/stdafx.h \
  ../../core/oscar_buffer.h /usr/local/include/stlport/vector \
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
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/iostream \
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_string_io.c \
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
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/hash_map \
  /usr/local/include/stlport/stl/_hash_map.h \
  /usr/local/include/stlport/stl/_hashtable.h \
  /usr/local/include/stlport/stl/_slist.h \
  /usr/local/include/stlport/stl/_slist_base.h \
  /usr/local/include/stlport/stl/_slist_base.c \
  /usr/local/include/stlport/stl/_slist.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c ../../core/str_lib.h \
  ../../core/errs.h /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h
	 c++ $(RCFLAGS) ../../core/oscar_buffer.cpp -o $(ROBJDIR)/oscar_buffer.o

./objR/rijndael.o: ../../core/rijndael.cpp ../../core/rijndael.h \
  /usr/local/include/stlport/stdlib.h \
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
  /usr/local/include/stlport/string.h /usr/local/include/stlport/stdio.h
	 c++ $(RCFLAGS) ../../core/rijndael.cpp -o $(ROBJDIR)/rijndael.o

./objR/server_config.o: ../../core/server_config.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/signal.h \
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
  /usr/local/include/stlport/errno.h ../../core/mutex_inspector.h \
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
  ../../core/str_lib.h /usr/local/include/stlport/set \
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
  /usr/local/include/stlport/stl/_hash_set.h ../../core/server_config.h \
  ../../core/M_MAP.h ../../core/M_SET.h ../../core/m_var.h \
  ../../core/file_set.h ../../core/M_LIST.h ../../core/wrappers.h \
  ../../core/st_stuff.h
	 c++ $(RCFLAGS) ../../core/server_config.cpp -o $(ROBJDIR)/server_config.o

./objR/st_FILE.o: ../../core/st_FILE.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/stdio.h \
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
  /usr/local/include/stlport/stdlib.h /usr/local/include/stlport/string.h \
  ../../core/st_stuff.h ../../core/errs.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/errno.h ../../core/copy_file.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/wrappers.h
	 c++ $(RCFLAGS) ../../core/st_FILE.cpp -o $(ROBJDIR)/st_FILE.o

./objR/st_rsa.o: ../../core/st_rsa.cpp ../../stdafx/stdafx.h \
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
  ../../core/st_stuff.h ../../core/errs.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/m_var.h ../../core/st_rsa.h
	 c++ $(RCFLAGS) ../../core/st_rsa.cpp -o $(ROBJDIR)/st_rsa.o

./objR/st_savecwd.o: ../../core/st_savecwd.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/stdio.h \
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
  /usr/local/include/stlport/stdlib.h /usr/local/include/stlport/string.h \
  ../../core/st_stuff.h ../../core/errs.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/errno.h ../../core/copy_file.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h
	 c++ $(RCFLAGS) ../../core/st_savecwd.cpp -o $(ROBJDIR)/st_savecwd.o

./objR/st_stream_str.o: ../../core/st_stream_str.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/stdio.h \
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
  /usr/local/include/stlport/stdlib.h /usr/local/include/stlport/string.h \
  ../../core/str_lib.h /usr/local/include/stlport/string \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/errno.h ../../core/st_stream_str.h \
  ../../core/st_stuff.h
	 c++ $(RCFLAGS) ../../core/st_stream_str.cpp -o $(ROBJDIR)/st_stream_str.o

./objR/st_stuff.o: ../../core/st_stuff.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/stdio.h \
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
  /usr/local/include/stlport/stdlib.h /usr/local/include/stlport/string.h \
  ../../core/st_stuff.h ../../core/errs.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/errno.h ../../core/mutex_inspector.h \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h
	 c++ $(RCFLAGS) ../../core/st_stuff.cpp -o $(ROBJDIR)/st_stuff.o

./objR/str_lib.o: ../../core/str_lib.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/iostream \
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
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/fstream \
  /usr/local/include/stlport/stl/_fstream.h \
  /usr/local/include/stlport/stl/_codecvt.h \
  /usr/local/include/stlport/stl/_fstream.c \
  /usr/local/include/stlport/sstream \
  /usr/local/include/stlport/stl/_sstream.h \
  /usr/local/include/stlport/stl/_sstream.c \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
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
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/errno.h /usr/local/include/stlport/cerrno \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  /usr/local/include/stlport/cstdarg \
  /usr/local/include/stlport/stl/_cstdarg.h
	 c++ $(RCFLAGS) ../../core/str_lib.cpp -o $(ROBJDIR)/str_lib.o

./objR/str_lib1.o: ../../core/str_lib1.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/iostream \
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
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/fstream \
  /usr/local/include/stlport/stl/_fstream.h \
  /usr/local/include/stlport/stl/_codecvt.h \
  /usr/local/include/stlport/stl/_fstream.c \
  /usr/local/include/stlport/sstream \
  /usr/local/include/stlport/stl/_sstream.h \
  /usr/local/include/stlport/stl/_sstream.c \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c ../../core/oscar_buffer.h \
  /usr/local/include/stlport/set /usr/local/include/stlport/stl/_set.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
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
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/stl/_hashtable.c \
  /usr/local/include/stlport/stl/_relops_hash_cont.h \
  /usr/local/include/stlport/hash_set \
  /usr/local/include/stlport/stl/_hash_set.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c ../../core/Double.h \
  ../../core/_mutex.h ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  ../../core/m_var.h /usr/local/include/stlport/errno.h \
  /usr/local/include/stlport/cerrno ../../core/mutex_inspector.h \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  /usr/local/include/stlport/cstdarg \
  /usr/local/include/stlport/stl/_cstdarg.h
	 c++ $(RCFLAGS) ../../core/str_lib1.cpp -o $(ROBJDIR)/str_lib1.o

./objR/str_lib_extra.o: ../../core/str_lib_extra.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/iostream \
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
  /usr/local/include/stlport/stl/_ioserr.h \
  /usr/local/include/stlport/stl/_iosfwd.h \
  /usr/local/include/stlport/stl/char_traits.h \
  /usr/local/include/stlport/stl/_cstddef.h \
  /usr/local/include/stlport/stl/_cstring.h \
  /usr/local/include/stlport/using/cstring \
  /usr/local/include/stlport/stl/_construct.h \
  /usr/local/include/stlport/stl/_new.h \
  /usr/local/include/stlport/stl/_iterator_base.h \
  /usr/local/include/stlport/stl/_move_construct_fwk.h \
  /usr/local/include/stlport/stl/type_traits.h \
  /usr/local/include/stlport/stl/type_manips.h \
  /usr/local/include/stlport/stl/_cwchar.h \
  /usr/local/include/stlport/stl/_istream.h \
  /usr/local/include/stlport/stl/_ios.h \
  /usr/local/include/stlport/stl/_ios_base.h \
  /usr/local/include/stlport/stl/_stdexcept_base.h \
  /usr/local/include/stlport/stl/_exception.h \
  /usr/local/include/stlport/stl/_string_fwd.h \
  /usr/local/include/stlport/iosfwd /usr/local/include/stlport/utility \
  /usr/local/include/stlport/stl/_pair.h \
  /usr/local/include/stlport/stl/_locale.h \
  /usr/local/include/stlport/stl/_cstdlib.h \
  /usr/local/include/stlport/stl/_cmath.h \
  /usr/local/include/stlport/stl/_threads.h \
  /usr/local/include/stlport/pthread.h \
  /usr/local/include/stlport/stl/_threads.c \
  /usr/local/include/stlport/stl/_ctime.h \
  /usr/local/include/stlport/stl/_string.h \
  /usr/local/include/stlport/stl/_alloc.h \
  /usr/local/include/stlport/stl/_algobase.h \
  /usr/local/include/stlport/climits \
  /usr/local/include/stlport/stl/_algobase.c \
  /usr/local/include/stlport/stl/_iterator.h \
  /usr/local/include/stlport/stl/_alloc.c \
  /usr/local/include/stlport/stl/_function_base.h \
  /usr/local/include/stlport/stl/_uninitialized.h \
  /usr/local/include/stlport/stl/_string_base.h \
  /usr/local/include/stlport/stl/_string_npos.h \
  /usr/local/include/stlport/stl/_string_operators.h \
  /usr/local/include/stlport/stl/_string.c \
  /usr/local/include/stlport/stl/_ctraits_fns.h \
  /usr/local/include/stlport/stl/_range_errors.h \
  /usr/local/include/stlport/stl/_ctype.h \
  /usr/local/include/stlport/stl/c_locale.h \
  /usr/local/include/stlport/ctype.h \
  /usr/local/include/stlport/stl/_numpunct.h \
  /usr/local/include/stlport/stl/_ios.c \
  /usr/local/include/stlport/stl/_streambuf.h \
  /usr/local/include/stlport/stl/_streambuf.c \
  /usr/local/include/stlport/stl/_ostream.h \
  /usr/local/include/stlport/stl/_ostreambuf_iterator.h \
  /usr/local/include/stlport/stl/_ostream.c \
  /usr/local/include/stlport/stl/_num_put.h \
  /usr/local/include/stlport/stl/_iostream_string.h \
  /usr/local/include/stlport/stl/_num_put.c \
  /usr/local/include/stlport/stl/_limits.h \
  /usr/local/include/stlport/cfloat \
  /usr/local/include/stlport/stl/_limits.c \
  /usr/local/include/stlport/stl/_istreambuf_iterator.h \
  /usr/local/include/stlport/stl/_istream.c \
  /usr/local/include/stlport/stl/_num_get.h \
  /usr/local/include/stlport/stl/_num_get.c \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
  /usr/local/include/stlport/fstream \
  /usr/local/include/stlport/stl/_fstream.h \
  /usr/local/include/stlport/stl/_codecvt.h \
  /usr/local/include/stlport/stl/_fstream.c \
  /usr/local/include/stlport/sstream \
  /usr/local/include/stlport/stl/_sstream.h \
  /usr/local/include/stlport/stl/_sstream.c \
  /usr/local/include/stlport/string \
  /usr/local/include/stlport/stl/_string_hash.h \
  /usr/local/include/stlport/stl/_hash_fun.h \
  /usr/local/include/stlport/stl/_string_io.h \
  /usr/local/include/stlport/stl/_string_io.c \
  /usr/local/include/stlport/iterator \
  /usr/local/include/stlport/stl/_stream_iterator.h \
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c ../../core/_mutex.h \
  ../../core/errs.h /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/str_lib.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/m_var.h \
  ../../core/Double.h ../../core/oscar_buffer.h \
  /usr/local/include/stlport/iomanip.h /usr/local/include/stlport/iomanip \
  /usr/local/include/stlport/iostream.h \
  /usr/local/include/stlport/streambuf.h \
  /usr/local/include/stlport/streambuf /usr/local/include/stlport/ios.h \
  /usr/local/include/stlport/ios /usr/local/include/stlport/using/ios \
  /usr/local/include/stlport/ostream.h /usr/local/include/stlport/ostream \
  /usr/local/include/stlport/using/ostream \
  /usr/local/include/stlport/istream.h /usr/local/include/stlport/istream \
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
  /usr/local/include/stlport/errno.h /usr/local/include/stlport/cerrno \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  /usr/local/include/stlport/cstdarg \
  /usr/local/include/stlport/stl/_cstdarg.h ../../core/st_stream_str.h
	 c++ $(RCFLAGS) ../../core/str_lib_extra.cpp -o $(ROBJDIR)/str_lib_extra.o

./objR/threadable.o: ../../core/threadable.cpp ../../stdafx/stdafx.h \
  ../../core/threadable.h ../../core/M_MAP.h \
  /usr/local/include/stlport/map /usr/local/include/stlport/stl/_prolog.h \
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
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/stl/_epilog.h \
  /usr/local/include/stlport/stl/_config_compat_post.h \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/list \
  /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h \
  /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c \
  /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/str_lib.h /usr/local/include/stlport/set \
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
  /usr/local/include/stlport/stl/_hash_set.h
	 c++ $(RCFLAGS) ../../core/threadable.cpp -o $(ROBJDIR)/threadable.o

./objR/wrappers.o: ../../core/wrappers.cpp ../../stdafx/stdafx.h \
  /usr/local/include/stlport/stdlib.h \
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
  ../../core/str_lib.h /usr/local/include/stlport/string \
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
  /usr/local/include/stlport/vector \
  /usr/local/include/stlport/stl/_vector.h \
  /usr/local/include/stlport/stl/_vector.c \
  /usr/local/include/stlport/stl/_bvector.h \
  /usr/local/include/stlport/stl/_relops_cont.h \
  /usr/local/include/stlport/list /usr/local/include/stlport/stl/_list.h \
  /usr/local/include/stlport/stl/_list.c \
  /usr/local/include/stlport/stl/_carray.h /usr/local/include/stlport/map \
  /usr/local/include/stlport/stl/_map.h \
  /usr/local/include/stlport/stl/_tree.h \
  /usr/local/include/stlport/stl/_tree.c /usr/local/include/stlport/set \
  /usr/local/include/stlport/stl/_set.h /usr/local/include/stlport/deque \
  /usr/local/include/stlport/stl/_deque.h \
  /usr/local/include/stlport/stl/_deque.c ../../core/errs.h \
  /usr/local/include/stlport/stdexcept \
  /usr/local/include/stlport/stl/_stdexcept.h ../../core/m_var.h \
  ../../core/_mutex.h ../../core/Double.h ../../core/oscar_buffer.h \
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
  /usr/local/include/stlport/stl/_hash_set.h ../../core/copy_file.h \
  ../../core/wrappers.h /usr/local/include/stlport/errno.h \
  ../../core/mutex_inspector.h /usr/local/include/stlport/stack \
  /usr/local/include/stlport/stl/_stack.h ../../core/lockctl.h \
  ../../core/tcp_stats.h
	 c++ $(RCFLAGS) ../../core/wrappers.cpp -o $(ROBJDIR)/wrappers.o

clean:
	 rm   z.out kaka.xxx file_dump.cpp TERM* 1 2

both: all release



cleanobjs:
	 rm $(OBJDIR)/Double.o $(OBJDIR)/PTR.o $(OBJDIR)/_QUERY.o $(OBJDIR)/__main.o $(OBJDIR)/_mutex.o $(OBJDIR)/_mutex1.o $(OBJDIR)/copy_file_common.o $(OBJDIR)/core_main.o $(OBJDIR)/db_config2.o $(OBJDIR)/db_var.o $(OBJDIR)/des_sid.o $(OBJDIR)/errs.o $(OBJDIR)/file_set.o $(OBJDIR)/file_set_init.o $(OBJDIR)/mutex_inspector.o $(OBJDIR)/mysql_extens.o $(OBJDIR)/mysql_extens2.o $(OBJDIR)/oscar_buffer.o $(OBJDIR)/rijndael.o $(OBJDIR)/server_config.o $(OBJDIR)/st_FILE.o $(OBJDIR)/st_rsa.o $(OBJDIR)/st_savecwd.o $(OBJDIR)/st_stream_str.o $(OBJDIR)/st_stuff.o $(OBJDIR)/str_lib.o $(OBJDIR)/str_lib1.o $(OBJDIR)/str_lib_extra.o $(OBJDIR)/threadable.o $(OBJDIR)/wrappers.o $(ROBJDIR)/Double.o $(ROBJDIR)/PTR.o $(ROBJDIR)/_QUERY.o $(ROBJDIR)/__main.o $(ROBJDIR)/_mutex.o $(ROBJDIR)/_mutex1.o $(ROBJDIR)/copy_file_common.o $(ROBJDIR)/core_main.o $(ROBJDIR)/db_config2.o $(ROBJDIR)/db_var.o $(ROBJDIR)/des_sid.o $(ROBJDIR)/errs.o $(ROBJDIR)/file_set.o $(ROBJDIR)/file_set_init.o $(ROBJDIR)/mutex_inspector.o $(ROBJDIR)/mysql_extens.o $(ROBJDIR)/mysql_extens2.o $(ROBJDIR)/oscar_buffer.o $(ROBJDIR)/rijndael.o $(ROBJDIR)/server_config.o $(ROBJDIR)/st_FILE.o $(ROBJDIR)/st_rsa.o $(ROBJDIR)/st_savecwd.o $(ROBJDIR)/st_stream_str.o $(ROBJDIR)/st_stuff.o $(ROBJDIR)/str_lib.o $(ROBJDIR)/str_lib1.o $(ROBJDIR)/str_lib_extra.o $(ROBJDIR)/threadable.o $(ROBJDIR)/wrappers.o ./libcommon_d.a ./libcommon_r.a


cleanall: clean cleanobjs


