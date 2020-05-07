#include <stdio.h>
#include <windows.h> 
#include <errno.h>
#define BUF_SIZE 256

int main(int argc, LPTSTR argv[])
{
	HANDLE hIn, hOut;
	DWORD nIn, nOut;
	CHAR BUFFER[BUF_SIZE];

	if (argc != 3)
	{
		printf("usage : cp file1 file2\n");
		return 1;
	}

	hIn = CreateFile(argv[0], GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hIn == INVALID_HANDLE_VALUE)
	{
		printf("Can't open the first file! %x\n", GetLastError());
		return 2;
	}

	hOut = CreateFile(argv[2], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hOut == INVALID_HANDLE_VALUE)
	{
		printf("Can't open second file! %x\n", GetLastError());
		return 3;
	}

	while(ReadFile(hIn, BUFFER, BUF_SIZE, &nIn, NULL) && nIn > 0)
	{
		WriteFile(hOut, BUFFER, BUF_SIZE, &nOut, NULL);
		if(nIn != nOut)
		{
			printf("Fatal write error! %x\n", GetLastError());
			return 4;
		}
	}

	CloseHandle(hIn);
	CloseHandle(hOut);

	return 0;
}



