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

int main(int argc, char **argv)
//int main(int argc, char*argv[])

{
	vector<string> v=splitTOK(".-",argv[1]);
	time_t t=atoi(v[1]);
	printf("%s",ctime(&t));
	return 0;
}
