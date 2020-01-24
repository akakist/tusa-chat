OBJDIR=./objD
ROBJDIR=./objR


CFLAGS=   -O0 \
	-I/usr/local/include/stlport\ 
	-DDEBUG \
	-Wall  \
	-DTOMSK \
	-I/usr/local/include/mysql  -c   \
	-I/usr/local/ssl/include  \
	-DLINUX  -ftemplate-depth-30   -D__NO_LICENSE	
RCFLAGS=  -O3 \
	-I/usr/local/include/stlport\ 
	-Wall \
	-I/usr/local/include/mysql  -c   \
	-I/usr/local/ssl/include  \
	-DLINUX  -ftemplate-depth-30  -D__NO_LICENSE	


LIBS= -lssl -lcrypto  

RLIBS= -lssl -lcrypto 

LIBNAME=libapps__.a
RLIBNAME=rlibapps__.a

INC_DIRS= . 

TARGETS= mcassa_client.cpp  gen_rsa.cpp gen_rsa_bin.cpp
			
OBJS= st_rsa_client.cpp
