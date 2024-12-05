#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
void main()
{
	int fd;
	fd=open("a",O_CREAT|O_WRONLY|O_RDONLY,0664);
	struct stat v;
	if(stat("a",&v)<0)
	{
		perror("stat");
		return;
	}
	printf("%o\n",v.st_mode&0777);
	chmod("a",0644);
	if(stat("a",&v)<0)
	{
		perror("stat");
		return;
	}
	printf("%o\n",v.st_mode&0777);
	
}
