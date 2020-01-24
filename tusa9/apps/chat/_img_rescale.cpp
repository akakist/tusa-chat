#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include "copy_file.h"
#include <FreeImage.h>
#include <sys/types.h>  
#include <dirent.h>     
#include <sys/types.h>    
#include <sys/stat.h>     
#include <unistd.h>       

void cvt(const string& from)
{

try{
    printf("cvt %s\n", from.c_str());
	    FREE_IMAGE_FORMAT  fif=FreeImage_GetFIFFromFilename(from.c_str());
	    if(fif!=FIF_JPEG) return;
	    FIBITMAP *dib=FreeImage_Load(fif, from.c_str());

	    int w=FreeImage_GetWidth(dib);
	    int h=FreeImage_GetHeight(dib);
	    
	    int max=w;
	    bool use_w=true;
	    if(h>max)
	    {	
		max=h;
		use_w=false;
	    }
	    
	    if(max>700)
	    {
		float sf=650;
		sf/=max;
		w=sf*w;
		h=sf*h;
		FIBITMAP *cvt_dib=FreeImage_ConvertTo24Bits(dib);
		FIBITMAP *scaleddib=FreeImage_Rescale(cvt_dib, w, h, FILTER_BILINEAR);
		FreeImage_Save(FIF_JPEG, scaleddib, from.c_str());
	    }
	    else
	    {
	    
//		link(from.c_str(),to.c_str());
	    }
    }catch(...)	    
    {
	unlink(from.c_str());
    }
    
}
void scand(const char *p)
{
    printf("scanning %s\n",p);
	DIR *d=opendir(p);
	if(d)
	{
	    while(1)
	    {
		dirent *di=readdir(d);
		if(di)
		{
//		    printf("%s %d\n",di->d_name,di->d_type);
		    string pn=p;
		    pn+=(string)"/"+di->d_name;
		    struct stat st;
		    if(!stat(pn.c_str(),&st))
		    {
			if(st.st_mode&S_IFDIR)
			{
//			    printf("dir %s\n",pn.c_str());
			    if((string)di->d_name!="." && (string)di->d_name!=".." )
			    {
				scand(pn.c_str());
			    }
			    
			    
			}
			else
			{
			    string ppp=strlower(pn);
			    if(ppp.find("jpeg")!=-1 || ppp.find("jpg")!=-1)
			    {
				string cmd="./_img_cvt.exe rescale "+pn;
				system(cmd.c_str());
				//cvt(pn);
			    }
			}
		    }
		}
		else break;
	    }
	    closedir(d);
	}
}

int main(int argc,char *argv[])
{

//	FILE *f=fopen("clear_users.log","a");
        FreeImage_Initialise();

	scand(".");
	exit(1);
	if(argc<2) return 1;
	if(string(argv[1])=="rotate")
	{
	    if(argc<4)return 1;
	    string angle=argv[2];
	    string fn=argv[3];
	    string fn_tmp=fn+".tmp";
            if(angle=="90") FreeImage_JPEGTransform(fn.c_str(),fn_tmp.c_str(),FIJPEG_OP_ROTATE_90);
            else if(angle=="180") FreeImage_JPEGTransform(fn.c_str(),fn_tmp.c_str(),FIJPEG_OP_ROTATE_180);
            else if(angle=="270") FreeImage_JPEGTransform(fn.c_str(),fn_tmp.c_str(),FIJPEG_OP_ROTATE_270);
            unlink(fn.c_str());
            link(fn_tmp.c_str(),fn.c_str());
            unlink(fn_tmp.c_str());
	    
	}
	if(string(argv[1])=="scale")
	{
	    if(argc<5)return 1;
	    int nw=atoi(argv[2]);
	    string from=argv[3];
	    string to=argv[4];
	    check_path_wfn(to);
	    FREE_IMAGE_FORMAT  fif=FreeImage_GetFIFFromFilename(from.c_str());
	    if(fif!=FIF_JPEG) return 1;
	    FIBITMAP *dib=FreeImage_Load(fif, from.c_str());

	    int w=FreeImage_GetWidth(dib);
	    int h=FreeImage_GetHeight(dib);
	    
	    if(w>nw)
	    {
		float sf=nw;
		sf/=w;
		w=sf*w;
		h=sf*h;
		FIBITMAP *cvt_dib=FreeImage_ConvertTo24Bits(dib);
		FIBITMAP *scaleddib=FreeImage_Rescale(cvt_dib, w, h, FILTER_BILINEAR);
		FreeImage_Save(FIF_JPEG, scaleddib, to.c_str());
	    }
	    else
	    {
	    
		link(from.c_str(),to.c_str());
	    }
	    

	}
	
	
	return 0;
}
