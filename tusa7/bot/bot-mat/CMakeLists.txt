cmake_minimum_required (VERSION 2.6)

add_executable(mat.exe 

cmds.cpp
cmds.h
mat.cpp
mat.h

)

target_link_libraries(mat.exe bot-shared mysqlclient)
install(TARGETS mat.exe DESTINATION ${BIN_TARGET_DIR})

