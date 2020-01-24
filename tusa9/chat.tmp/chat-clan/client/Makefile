#check_path_wfn(./objR/kall)
#stat ./objR 0
#check_path_wfn(./objD/kall)
#stat ./objD 0

CFLAGS=  `cat ../_CFLAGS_D`  -I. -I../../chatserver -I../../core -I../../core_cs/common -I../../core_web -I../../stdafx

RCFLAGS= `cat ../_CFLAGS_R` -I. -I../../chatserver -I../../core -I../../core_cs/common -I../../core_web -I../../stdafx

LIBS= -lssl -lcrypto /usr/local/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a     /usr/local/lib/libGeoIP.a  -shared -Xlinker "--exclude-libs=libfmD.a" -v

RLIBS= -lssl -lcrypto /usr/local/lib/mysql/libmysqlclient.a /usr/local/lib/libboost_regex-gcc-mt-1_33_1.a -lpthread -lz /usr/lib/libgdbm.a   /usr/local/lib/libGeoIP.a   -shared -Xlinker "--exclude-libs=libfmR.a" -v

OBJDIR=./objD

ROBJDIR=./objR

all: ./libbos_client_d.a 


./libbos_client_d.a: \
	$(OBJDIR)/bos_client.o\
	$(OBJDIR)/bos_client_interface.o
		 ar -r ./libbos_client_d.a $(OBJDIR)/bos_client.o $(OBJDIR)/bos_client_interface.o 

release: ./libbos_client_r.a 


./libbos_client_r.a: \
	$(ROBJDIR)/bos_client.o \
	$(ROBJDIR)/bos_client_interface.o 
		 ar -r ./libbos_client_r.a $(ROBJDIR)/bos_client.o $(ROBJDIR)/bos_client_interface.o 

clean:
	 rm   z.out kaka.xxx file_dump.cpp TERM* 1 2

both: all release



cleanobjs:
	 rm ./libbos_client_d.a ./libbos_client_r.a


cleanall: clean cleanobjs


