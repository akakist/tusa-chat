#check_path_wfn(./objR/kall)
#stat ./objR 0
#check_path_wfn(./objD/kall)
#stat ./objD 0

CFLAGS=   -O0 	-I/usr/local/include/stlport	-DDEBUG 	-Wall  	-DTOMSK 	-I/usr/local/include/mysql  -c   	-I/usr/local/ssl/include  	-DLINUX  -ftemplate-depth-30   -D__NO_LICENSE	 -I.

RCFLAGS=  -O3 	-I/usr/local/include/stlport	-Wall 	-I/usr/local/include/mysql  -c   	-I/usr/local/ssl/include  	-DLINUX  -ftemplate-depth-30  -D__NO_LICENSE	 -I.

LIBS= -lssl -lcrypto  

RLIBS= -lssl -lcrypto 

OBJDIR=./objD

ROBJDIR=./objR

all: libapps__.a gen_rsa.exe gen_rsa_bin.exe mcassa_client.exe 
gen_rsa.exe: libapps__.a  $(OBJDIR)/gen_rsa.o
		c++ $(OBJDIR)/gen_rsa.o -o gen_rsa.exe libapps__.a  $(LIBS) 
		 strip gen_rsa.exe 
gen_rsa_bin.exe: libapps__.a  $(OBJDIR)/gen_rsa_bin.o
		c++ $(OBJDIR)/gen_rsa_bin.o -o gen_rsa_bin.exe libapps__.a  $(LIBS) 
		 strip gen_rsa_bin.exe 
mcassa_client.exe: libapps__.a  $(OBJDIR)/mcassa_client.o
		c++ $(OBJDIR)/mcassa_client.o -o mcassa_client.exe libapps__.a  $(LIBS) 
		 strip mcassa_client.exe 


libapps__.a: \
	$(OBJDIR)/st_rsa_client.o
		 ar -r libapps__.a $(OBJDIR)/st_rsa_client.o 

./objD/gen_rsa.o: gen_rsa.cpp st_rsa_client.h
	 c++ $(CFLAGS) ./gen_rsa.cpp -o $(OBJDIR)/gen_rsa.o

./objD/gen_rsa_bin.o: gen_rsa_bin.cpp st_rsa_client.h
	 c++ $(CFLAGS) ./gen_rsa_bin.cpp -o $(OBJDIR)/gen_rsa_bin.o

./objD/mcassa_client.o: mcassa_client.cpp stdafx.h tusa_rsa_pub.cpp
	 c++ $(CFLAGS) ./mcassa_client.cpp -o $(OBJDIR)/mcassa_client.o

./objD/st_rsa_client.o: st_rsa_client.cpp stdafx.h st_rsa_client.h
	 c++ $(CFLAGS) ./st_rsa_client.cpp -o $(OBJDIR)/st_rsa_client.o

release: rlibapps__.a gen_rsa.release.exe gen_rsa_bin.release.exe mcassa_client.release.exe 
gen_rsa.release.exe: rlibapps__.a  $(ROBJDIR)/gen_rsa.o
		c++ $(ROBJDIR)/gen_rsa.o -o gen_rsa.release.exe rlibapps__.a  $(RLIBS)
		 strip gen_rsa.release.exe 
gen_rsa_bin.release.exe: rlibapps__.a  $(ROBJDIR)/gen_rsa_bin.o
		c++ $(ROBJDIR)/gen_rsa_bin.o -o gen_rsa_bin.release.exe rlibapps__.a  $(RLIBS)
		 strip gen_rsa_bin.release.exe 
mcassa_client.release.exe: rlibapps__.a  $(ROBJDIR)/mcassa_client.o
		c++ $(ROBJDIR)/mcassa_client.o -o mcassa_client.release.exe rlibapps__.a  $(RLIBS)
		 strip mcassa_client.release.exe 


rlibapps__.a: \
	$(ROBJDIR)/st_rsa_client.o 
		 ar -r rlibapps__.a $(ROBJDIR)/st_rsa_client.o 

./objR/gen_rsa.o: gen_rsa.cpp st_rsa_client.h
	 c++ $(RCFLAGS) ./gen_rsa.cpp -o $(ROBJDIR)/gen_rsa.o

./objR/gen_rsa_bin.o: gen_rsa_bin.cpp st_rsa_client.h
	 c++ $(RCFLAGS) ./gen_rsa_bin.cpp -o $(ROBJDIR)/gen_rsa_bin.o

./objR/mcassa_client.o: mcassa_client.cpp stdafx.h tusa_rsa_pub.cpp
	 c++ $(RCFLAGS) ./mcassa_client.cpp -o $(ROBJDIR)/mcassa_client.o

./objR/st_rsa_client.o: st_rsa_client.cpp stdafx.h st_rsa_client.h
	 c++ $(RCFLAGS) ./st_rsa_client.cpp -o $(ROBJDIR)/st_rsa_client.o

clean:
	 rm gen_rsa.exe gen_rsa_bin.exe mcassa_client.exe gen_rsa.exe gen_rsa_bin.exe mcassa_client.release.exe z.out kaka.xxx file_dump.cpp TERM* 1 2

both: all release



cleanobjs:
	 rm $(OBJDIR)/gen_rsa.o $(OBJDIR)/gen_rsa_bin.o $(OBJDIR)/mcassa_client.o $(OBJDIR)/st_rsa_client.o $(ROBJDIR)/gen_rsa.o $(ROBJDIR)/gen_rsa_bin.o $(ROBJDIR)/mcassa_client.o $(ROBJDIR)/st_rsa_client.o libapps__.a rlibapps__.a


cleanall: clean cleanobjs


