#include<windows.h>
#include<stdio.h>


int main(int argc, LPCSTR argv[])
{
	if(argc != 3)
	{
		printf("Usage : cpcf file1 file2");
		return 1;
	}

	if (!CopyFileA(argv[1], argv[2], FALSE)) 
	{
		printf("Fatal error! %x\n", GetLastError());
		return 2;
	}
	return 0;
}