cmake_minimum_required (VERSION 2.6)

#project(dfsCore)
#ADD_SUBDIRECTORY(SQLiteCpp)


#include_directories(../local ../lib/jsoncpp-0.5.0/include /usr/local/include .. . )
#add_definitions(-std=gnu++0x)

add_library(chat-core  STATIC

PTR.cpp
_QUERY.cpp
__main.cpp
_mutex.cpp
_mutex1.cpp
cf_utils.cpp
copy_file_common.cpp
#core.cpp
core_main.cpp
db_config.cpp
#db_maps.cpp
db_var.cpp
des_sid.cpp
errs.cpp
file_set.cpp
file_set_init.cpp
mysql_extens.cpp
oscar_buffer.cpp
server_config.cpp
st_FILE.cpp
st_savecwd.cpp
st_stream_str.cpp
st_stuff.cpp
str_lib.cpp
str_lib1.cpp
str_lib_extra.cpp
tcp_stats.cpp
threadable.cpp
wrappers.cpp

           )
#install(TARGETS megatron-core DESTINATION ${LIB_TARGET_DIR})

