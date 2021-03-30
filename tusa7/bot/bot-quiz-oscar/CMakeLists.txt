cmake_minimum_required (VERSION 2.6)

add_executable(quiz.exe 

game.cpp
game.h
quiz.cpp
quiz.h
stdafx.h


)

target_link_libraries(quiz.exe bot-shared mysqlclient)
install(TARGETS quiz.exe DESTINATION ${BIN_TARGET_DIR})

