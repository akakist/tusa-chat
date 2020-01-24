
#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include "copy_file.h"
#include "st_rsa.h"
#include "file_set.h"
#include "oscar_buffer.h"
#include "PTR.h"
#include "html_out.h"
string ss;
oscar_buffer b;
oscar_buffer b2;
vector<unsigned int> V;
int main(int argc, char **argv)
//int main(char *argv[], int atgc)
{
    hstring h;
    h<< "kall";

    map<string,hstring> m;
    m["kall"]="srall";
    m["k~id"]="12345";
    h<<make_pair(m,"tipo");
    printf("OUT: %s\n",h.as_string().c_str());
    
}
