cmake_minimum_required (VERSION 2.6)

add_executable(chatserver.exe 

admin.cpp
admin_accounts.cpp
admin_ban.cpp
admin_levelup.cpp
admin_logininfo.cpp
admin_other.cpp
admin_privs.cpp
admin_settings.cpp
admin_userlist_command.cpp
admin_vote.cpp
app_con.cpp
app_server.cpp
ch.cpp
channels.cpp
chat_colors.cpp
chat_config.cpp
chat_funny.cpp
chat_globals.cpp
chat_msg.cpp
chat_process_web.cpp
chat_thread.cpp
chat_thread_2.cpp
chatserver.cpp
config.cpp
contact_vec.cpp
cs_conn_data.cpp
do_ban.cpp
file_dump.cpp
forum.cpp
fotos.cpp
fotos_ui.cpp
gallery.cpp
ignore_vec.cpp
irc_admin.cpp
irc_login.cpp
irc_server.cpp
irc_server_config.cpp
irc_tools.cpp
irc_user.cpp
irc_user_cred.cpp
klan_to_db_io.cpp
levels.cpp
local_user_handle.cpp
login.cpp
main.cpp
main_cs.cpp
make_login_out.cpp
make_user_info.cpp
message.cpp
nick_vec.cpp
notes.cpp
notes_containers.cpp
other.cpp
register.cpp
settings.cpp
status_vec.cpp
#tusa_clan_iface.cpp
u_chat.cpp
update_cmd.cpp
url_admin_nickban.cpp
url_admin_userlist.cpp
url_new_nick.cpp
url_settings_credits.cpp
user.cpp
user_credits.cpp
user_info.cpp
user_nick.cpp
user_profile.cpp
user_set.cpp
user_stat.cpp
user_state.cpp
user_status.cpp
utils.cpp
vote.cpp


)
#include_directories(../../main)

IF(FreeBSD)
target_link_libraries(chatserver.exe chat-core chat-coreweb z  pthread)
ELSE()
target_link_libraries(chatserver.exe chat-core chat-coreweb mysqlclient gdbm crypto z  pthread dl)
ENDIF()
install(TARGETS chatserver.exe DESTINATION ${BIN_TARGET_DIR})

