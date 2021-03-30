cmake_minimum_required (VERSION 2.6)

add_executable(roulette.exe 

game.cpp
game.h
roulette.cpp
roulette.h
stdafx.h


)

target_link_libraries(roulette.exe bot-shared mysqlclient)
install(TARGETS roulette.exe DESTINATION ${BIN_TARGET_DIR})

