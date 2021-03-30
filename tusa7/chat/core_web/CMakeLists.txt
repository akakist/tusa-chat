cmake_minimum_required (VERSION 2.6)

#project(dfsCore)
#ADD_SUBDIRECTORY(SQLiteCpp)


#include_directories(../local ../lib/jsoncpp-0.5.0/include /usr/local/include .. . )
#add_definitions(-std=gnu++0x)

add_library(chat-coreweb  STATIC

c_conn.cpp
#core_web.cpp
html_out.cpp
#oscar_client.cpp
tcp_dialog_server.cpp
tcp_sender.cpp
tcp_server.cpp
tcp_server_connection.cpp
thread_info.cpp
thread_info_report.cpp
web_adminfo.cpp
web_connection.cpp
web_connection_ptcp.cpp
web_server.cpp
web_server_config.cpp
web_tools.cpp



           )
#install(TARGETS megatron-core DESTINATION ${LIB_TARGET_DIR})

