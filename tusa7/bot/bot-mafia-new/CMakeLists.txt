cmake_minimum_required (VERSION 2.6)

add_executable(mafia.exe 

command.cpp
command.h
day.cpp
day.h
game.cpp
game.h
mafia.cpp
mafia.h
messages.cpp
messages.h
night.cpp
night.h
user.cpp
user.h


)

target_link_libraries(mafia.exe bot-shared mysqlclient pthread)
install(TARGETS mafia.exe DESTINATION ${BIN_TARGET_DIR})

