//#include "PROJ_CONFIG.h"
#include "copy_file.h"
#include "st_stuff.h"
#include "mysql_extens.h"
#include <sys/stat.h>
#include "str_lib.h"
#include <vector>
#include <map>
#include "st_stream_str.h"
#include "st_rsa.h"
string MESS(const string &s)
{
    vector<string>v;
    string out;
    for (int i=0;i<s.size();i++)
    {
        char b[10];
        sprintf(b,"0x%x",(unsigned char)s[i]);
        string s=b;
        if (i%20==0)s+="\n";
        v.push_back(s);
    }
//	return out;
    return "{"+join(",",v)+"};";
}

int main(int argc, char **argv)
//int main(int argc, char*argv[])
{
    try{
        st_FILE f(argv[1],"rb");
        struct stat st;
        stat(argv[1],&st);
        char m[st.st_size+10];
        f.read(m,st.st_size);

//        char *p=(char*)m.buf;
        m[st.st_size]=0;
        vector<string> v=splitTOK("\n\r",m);
        st_FILE out("z.out","wb");
//        vector<string>vout;
	map<string,string> vout;
        for (unsigned int i=0;i<v.size();i++)
        {
            FILE *f1=fopen(v[i].c_str(),"rb");
            if (f1==NULL)
	    {
		fprintf(stderr,"cannot open %s",v[i].c_str());
		continue;
	    }
            struct stat st1;
            stat(v[i].c_str(),&st1);
            if (st1.st_size==0)
	    {
		fprintf(stderr,"cannot stat %s",v[i].c_str());
		continue;
	    }
            if (S_ISDIR(st1.st_mode))continue;
            char  m1[st1.st_size+10];
            fread(m1,st1.st_size,1,f1);
            string s((char*)m1,st1.st_size);
	    vout[v[i]]=s;
            fclose(f1);
        }
        out_oscar_buffer o;
        o<<vout;
        st_rsa rsa;
        rsa.generate_key(512);
        string sz=z_compress(o.as_string());
        enc_string es=rsa.private_encrypt(sz);
        string rnd;
        srand(time(NULL));
        int nr=rand()%0x200;
        for (int i=0;i<nr;i++)
        {
            int r=rand();
            rnd+=string((char*)&r,4);
        }
        printf("#include \"stdafx.h\"\n");
        printf("char files_dump_stream[]=%s\n",MESS(es.buf).c_str());
        printf("int original_size=%d;\n",es.original_size);
        printf("char pub_key[]=%s\n",MESS(rsa.public_key()).c_str());
        printf("int pub_key_size=%d;\n", rsa.public_key().size());
        printf("int files_dump_stream_size=%d;\n",es.buf.size());
        printf("char kaka_kakksdfh[]=%s\n",MESS(rnd.c_str()).c_str());
//        printf("\n#include \"core_main.cpp\"\n");

    }catch (cError e){printf("%s",e.error_string.c_str());}
    return 0;
}
