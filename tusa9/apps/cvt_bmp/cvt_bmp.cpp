// cvt_bmp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include "FreeImage.h"
#include <io.h>
#include <vector>
#include <string>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{

	/*if(argc!=3)
	{
		printf("usage cvt file.bmp");
		return 0;
	}*/
	_finddata_t fileinfo ;
	vector<string> v;
	intptr_t h=_findfirst("*.bmp",&fileinfo);
	if(h!=1)v.push_back(fileinfo.name);
	while(1)
	{
		if(h==-1) break;
		printf("%s\n",fileinfo.name);
		v.push_back(fileinfo.name);
		int r=_findnext(h,&fileinfo);
		if(r!=0)
			break;
		printf("%s\n",fileinfo.name);
		v.push_back(fileinfo.name);
	}	
	for(unsigned i=0;i<v.size();i++)
	{
		FIBITMAP *fi =FreeImage_Load(FIF_BMP, v[i].c_str() );
		string pn=v[i]+".png";
		FreeImage_Save(FIF_PNG,fi,pn.c_str());
	}
	
/*	FIBITMAP *fi =FreeImage_Load(FIF_BMP, argv[1] );
	printf("%d\n",argc);*/
	return 0;
}

