cmake_minimum_required (VERSION 2.6)

add_executable(mandalina.exe 

cmd.cpp
cmd.h
girl.cpp
girl.h
stdafx.h


)

target_link_libraries(mandalina.exe bot-shared mysqlclient)
install(TARGETS mandalina.exe DESTINATION ${BIN_TARGET_DIR})

