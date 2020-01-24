OBJDIR=./objD
ROBJDIR=./objR


CFLAGS= `cat _CFLAGS_D` -DCOMPILE_TIME=`./gettime.pl` -DSVN_VERSION="\"`svnversion`\""

RCFLAGS= `cat _CFLAGS_R` -DCOMPILE_TIME=`./gettime.pl` -DSVN_VERSION="\"`svnversion`\""

LIBS=  `cat _LFLAGS_D` 
RLIBS= `cat _LFLAGS_R`

#


#LIBS=-lssl -lcrypto /usr/local/lib/mysql/libmysqlclient.a   -lpthread -lz -lgdbm   -lexpat -lfreeimage -lz 
#RLIBS=-lssl -lcrypto /usr/local/lib/mysql/libmysqlclient.a  -lpthread -lz -lgdbm  -lexpat -lfreeimage -lz 

#/usr/local/lib/libstlport_gcc.a  /usr/local/lib/libstlport_gcc.a  
#LIBS= /home/oracle/soft/STLport-4.0/lib/libstlport_gcc.a   -lssl -lcrypto  /usr/lib/libmysqlclient.so   -lz \
#	-lpthread -lgdbm  /usr/local/lib/libboost_regex_debug.a
#  	-lssl -lcrypto /usr/local/lib/mysql/libmysqlclient.a
LIBNAME=libapps__.a
RLIBNAME=rlibapps__.a

INC_DIRS= . ../core ../core-web ../udp ../zdes ../kall ./chat ./icq ./tools 

TARGETS=   tools/gen_dump.cpp  tools/crmak1.cpp  chat/URL_anal.cpp chat/return_cred.cpp\
			 chat/gen_pins.cpp  chat/gen_pins_random.cpp \
			  license/gen_rsa.cpp license/sign.cpp license/sign1.cpp     chat/mark_nicks_forsale.cpp\ 
			  chat/URL_anal.cpp \
			  chat/udp_test.cpp chat/geo_test.cpp geo_cvt_blocks.cpp geo_cvt_loc.cpp chat/upgrade_to_clan.cpp \
			  chat/clear_attach.cpp\
			  chat/clear_attach2.cpp\
			  chat/notes_clean.cpp chat/all_backup.cpp  tools/cconv.cpp ra_cvt_real.cpp ra_cvt_real_levels.cpp chat/clear_users.cpp chat/update_str_nick.cpp

			  
			
			
#chat/fix_users.cpp chat/clear_fotos_unref.cpp multicassa/multipay.cpp			chat/clear_users.cpp chat/upgrade_notes.cpp 
			
#_CONFIG.c banners.c file_dump.c tools/crmak.cpp icq/cvt_icq_base.cpp icq/cvt_icq_base1.cpp
#chat/recalc_vote.cpp chat/remove_old_vote.cpp chat/clear_users.cpp chat/conv.cpp  chat/md5str.cpp chat/compare_passwd.cpp chat/update_passwd.cpp chat/compare_passwd2.cpp chat/calc_photo_size.cpp chat/calc_used_space.cpp chat/update_notes.cpp
#projektor/CertAuth.cpp projektor/CertSign.cpp 
OBJS= file_dump.cpp  st_FILE.cpp\
	str_lib1.cpp _mutex1.cpp db_config.cpp db_config2.cpp tcp_stats.cpp  str_lib1.cpp\
	str_lib_extra.cpp errs.cpp str_lib.cpp file_set.cpp st_rsa.cpp _mutex.cpp st_stuff.cpp   wrappers.cpp mysql_extens.cpp mysql_extens2.cpp \
	server_config.cpp  copy_file_common.cpp st_savecwd.cpp _QUERY.cpp  PTR.cpp oscar_buffer.cpp st_stream_str.cpp geoip.cpp threadable.cpp 

#icq_client_handle_sr.c icq_client_send.c icq_client_cb.c  
