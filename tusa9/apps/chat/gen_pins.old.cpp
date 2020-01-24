#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include "copy_file.h"
#include "st_rsa.h"
#include "file_set.h"

char sss[1000000];
set<string> used;
void gen_sql(unsigned int N1, unsigned int summa1, const vector<string> &vvvz)
{
    for(unsigned i=0;i<N1+100;i++) sss[i]=rand();
    deque<string> vals;
    string out;
    for(unsigned i=0;i<N1;i++)
    {
	string v=MD5(string(&sss[i],20));
	unsigned int *v1=(unsigned int *)v.data();
	unsigned int *v2=(unsigned int *)(v.data()+4);
	unsigned int *v3=(unsigned int *)(v.data()+8);
	char x[100];
	sprintf(x,"%u%u%u\n",*v1,*v2,*v3);
	string f=string(x).substr(0,12);
	string s1=f.substr(0,4);
	string s2=f.substr(4,4);
	string s3=f.substr(8,4);
	char xs[1000];
	string sf=s1+"-"+s2+"-"+s3;
	if(used.count(sf))
	{
	fprintf(stderr,"key already used %s\n",sf.c_str());
	 continue;
	}
	snprintf(xs,sizeof(xs),"('%s','%s','%s','%s','%d',NOW(),'%s')",s1.c_str(),s2.c_str(),s3.c_str(),sf.c_str(),summa1,MES(vvvz[i%vvvz.size()]+" ### "+sf).c_str());
	vals.push_back(xs);
	used.insert(sf);
    }
    printf("/*!40000 ALTER TABLE `pincodes` DISABLE KEYS */; \n");
    for(unsigned i=0;i<N1;i++)
    {
/*	vector<string> vv;
	for(unsigned j=0;j<1&& i<N1;j++,i++)
	{
	    if(vals.size()){ vv.push_back(*vals.begin());vals.pop_front();}
	    
	}*/
        printf("insert into pincodes (v1,v2,v3,full_v,summa, date_created,sms) values %s;\n",vals[i].c_str()/*,join(",",vv).c_str()*/);
    }
    printf("/*!40000 ALTER TABLE `pincodes` ENABLE KEYS */;  ");

}
int main(int argc, char **argv)
//int main(char *argv[], int atgc)
{
    if(argc!=4) printf("usage %s summa N who\n\n",argv[0]),exit(1);
    srand(time(NULL));
    int summa1=atoi(argv[1]);

    int N1=atoi(argv[2]);
/*    string s1;
    if( load_1_file(s1,argv[3])==-1)
    {
	printf("err cannot load %s",argv[3]);exit(1);
    }*/
    string who=argv[3];
/*    printf("# N1 %d summa1 %d\n",N1,summa1);
    vector<string>vz1=splitTOK("\r\n",s1);


    int summa2=atoi(argv[4]);
    int N2=atoi(argv[5]);
    string s2;
    if( load_1_file(s2,argv[6])==-1)
    {
	printf("err cannot load %s",argv[6]);exit(1);
    }
    vector<string>vz2=splitTOK("\r\n",s2);

    printf("# N2 %d summa2 %d\n",N2,summa2);
*/
    gen_sql(N1,summa1,who);
//    gen_sql(N2,summa2,vz2);
	return 0;
}
