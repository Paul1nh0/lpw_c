#include "stdio.h"

int write_data(char* file_name,char* src,int len)
{
	FILE *fpHandle = 0;
	fpHandle = fopen(file_name, "w");
	if (fpHandle != 0)
	{
		fseek(fpHandle, 0, SEEK_SET);
		fwrite(src,len, 1, fpHandle);
		fclose(fpHandle);
		return 0;
	}
	return -1;
}

int main()
{
    FILE* fpHandle = 0;
    char str_buf[10240]={0x00};
    char file_name[70]={0x00};
    printf("start...");
    fpHandle = fopen("´ð¹ýµÄÌâ.txt", "rb");
    if (fpHandle == 0)
    {
        printf("open file failed");
        return -1;
    }
    while (1)
    {
        memset(str_buf,0x00,sizeof(str_buf));
        memset(file_name,0x00,sizeof(file_name));
		if(fgets(str_buf, 10240, fpHandle) == 0)
		{
			break;
		}
		memcpy(file_name,str_buf,10);
		strcat(file_name,".txt");
		printf("file_name is %s",file_name);
		printf("str_buf is %s",str_buf);
		write_data(file_name,str_buf,strlen(str_buf));
    }
    return 0;
}
