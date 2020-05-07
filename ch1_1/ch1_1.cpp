#include <stdio.h>
#include <windows.h> 
#include <errno.h>
#define BUF_SIZE 256

#pragma warning(disable:4996)

int main(int argc, char* argv[])
{
	FILE* inFile, * outFile;
	char rec[BUF_SIZE];
	size_t bytesIn, bytesOut;

	if (argc != 3)
	{
		fprintf(stderr, "Usage : cpc file1 file2");
		return 1;
	}

	inFile = fopen(argv[1], "rb");
	if (inFile == NULL)
	{
		perror(argv[1]);
		return 2;
	}

	outFile = fopen(argv[2], "wb");
	if (outFile == NULL)
	{
		perror(argv[2]);
		fclose(inFile);
		return 3;
	}

	while ((bytesIn = fread(rec, 1, BUF_SIZE, inFile)) > 0)
	{
		bytesOut = fwrite(rec, 1, bytesIn, outFile);
		if (bytesOut != bytesIn)
		{
			perror("Fatal write error");
			fclose(inFile);
			fclose(outFile);
			return 4;
		}
	}

	printf("File copy succeed");

	fclose(inFile);
	fclose(outFile);

	return 0;
}





