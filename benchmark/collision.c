#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <time.h>
#include <keyvalue.h>
#include <fcntl.h>

int keyvalue[10];

int eq(int *a, int *b)
{
	int i;
	int flag = 1;
	for (i=0;i<8;i++)
	{
		if (a[i] != b[i])
		{
			flag = 0;
			break;
		}
	}
	return flag;	
}

int main()
{
	int key[] = {1,2,3,1,3};
	int data[5][8];
	int devfd;
	int tid;
	int readdata[8];
	
	int i,j;
	for (i=0;i<5;i++)
	{
		for (j=0;j<8;j++)
			data[i][j] = rand()%10;
	}
	
	devfd = open("/dev/keyvalue",O_RDWR);
    if(devfd < 0)
    {
        fprintf(stderr, "Device open failed");
        exit(1);
    }
	
	for (i=0;i<5;i++)
	{
		tid = kv_set(devfd,key[i],8*sizeof(int),data[i]);
		if (tid!=-1)
			printf("Succesfully added key = %d\n", key[i]);
		else
			printf("Cannot add key = %d\n", key[i]);	
	}		
	
	printf("\n\n\n");
		
	int flag;
	// check data
	for (i=0;i<5;i++)
	{
		tid = kv_get(devfd, key[i], 8*sizeof(int), readdata);
		if (tid!=-1)
		{
			//flag = eq(data[dataindex[i-1]], readdata);
			flag = eq(data[i], readdata);
			if (flag == 1)
				printf("Data matched for key = %d\n", key[i]);
			else
				printf("Data NOT matched for key = %d\n", key[i]);	
		}
	}
	
	printf("\n\n\n");
	
	// delete data
	for (i=0;i<5;i++)
	{
		tid = kv_delete(devfd, key[i]);
		if (tid!=-1)
		{
			printf("Data deleted for key = %d\n", key[i]);
		}
		else
		{
			printf("Data NOT deleted for key = %d\n", key[i]);	
		}
	}
	
	close(devfd);
}
