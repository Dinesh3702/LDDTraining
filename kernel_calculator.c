#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
void main()
{
	int fd,fd1;
	char s[50],s1[50];
	fd=open("/dev/dinesh",O_WRONLY,0664);
	printf("enter the string that has  2 interger numbers seperated with , and the function name\n");
	scanf("%s",s);
	write(fd,s,strlen(s));
	close(fd);
	fd1=open("/dev/dinesh",O_RDONLY,0664);
	read(fd1,s1,sizeof(s1));
	printf("%s\n",s1);
	close(fd1);




}
