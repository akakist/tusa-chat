#include "stdafx.h"
#include <stdio.h>
#include <string>
//#include "st_stuff.h"
//#include "str_lib.h"
//#include "mysql_extens.h"
#include <time.h>
#include "copy_file.h"
#include <sys/types.h>   
#include <sys/socket.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>   
#include "oscar_buffer.h"
using namespace std;

int main(int argc,char *argv[])
{

    int sock=::socket (PF_INET, SOCK_DGRAM, IPPROTO_UDP);



    struct sockaddr_in si;
    si.sin_addr.s_addr=inet_addr("192.168.147.64");
    si.sin_port=htons(2005);
    si.sin_family=AF_INET;
    out_oscar_buffer b;
    b<<2<<200;
    while(1)
    {
        int res=sendto(sock,(char*)b.data(),b.size(),0,(sockaddr*)&si,sizeof(si));
        printf("res %d\n",res);
	sleep(1);
    }
    
	
	return 0;
}
