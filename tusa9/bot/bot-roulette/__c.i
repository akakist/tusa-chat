OBJDIR=./objD
ROBJDIR=./objR

CFLAGS=  `cat _CFLAGS_D` 
RCFLAGS= `cat _CFLAGS_R`

LIBS=  `cat _LFLAGS_D` 
RLIBS= `cat _LFLAGS_R`


LIBS_DEP=../bot-shared/libbot-shared_d.a
RLIBS_DEP=../bot-shared/libbot-shared_r.a


LIBNAME=./libbot-roulette_d.a
RLIBNAME=./libot-roulette_r.a
INC_DIRS= . ../bot-shared


TARGETS=roulette.cpp


OBJS=game.cpp


	 
