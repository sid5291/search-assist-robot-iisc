#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

extern int cntupdown=0,cntleftright=0;
char ud2[20], ud1[10];
char lr[20],lr1[10];

int servo (int argc,char *argv)
{
int fd,fud,flr;

strcpy(ud2,"16:");
strcpy(lr,"18:");
if (argc != 2)
	{
		printf("\nError: usage servo <direction>\n");
		return(1);
	}

fd =open("/dev/servodrive0",O_RDWR);
if (fd < 0)
	{	
		printf("\nError: /dev/servodrive0 doesnot exist try #modprobe servodrive\n");
		return(1);
	}



if (!strcmp(argv,"sup"))
	{
		cntupdown+=5;
		if(cntupdown>=100)
		{
			printf("\nError: The servo has reached 90 degrees\n");
			close(fd);			
			return(1);
		}
		sprintf(ud1,"%d",cntupdown);
		strcat(ud2,ud1);
		if (write(fd,ud2,strlen(ud2))!=strlen(ud2))
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			return(1);
		}
	close(fd);
return(0);
	}
else if (!strcmp(argv,"sdown"))
	{
		cntupdown-=5;
		if(cntupdown<=-100)
		{
			printf("\nError: The servo has reached -90 degrees\n");
			close(fd);			
			return(1);
		}
		sprintf(ud1,"%d",cntupdown);
		strcat(ud2,ud1);
		if (write(fd,ud2,strlen(ud2))!=strlen(ud2))
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			return(1);
		}
	close(fd);
return(0);
	}
else if (!strcmp(argv,"sleft"))
	{
		cntleftright+=5;
		if(cntleftright>=100)
		{
			printf("\nError: The servo has reached 90 degrees\n");
			close(fd);			
			return(1);
		}
		sprintf(lr1,"%d",cntleftright);
		strcat(lr,lr1);
		if (write(fd,lr,strlen(lr))!=strlen(lr))
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			return(1);
		}
	close(fd);
return(0);
	}
else if (!strcmp(argv,"sright"))
	{
		cntleftright-=5;
		if(cntleftright<-100)
		{
			printf("\nError: The servo has reached -90 degrees\n");
			close(fd);			
			return(1);
			
		}
		sprintf(lr1,"%d",cntleftright);
		strcat(lr,lr1);
		if (write(fd,lr,strlen(lr))!=strlen(lr))
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			return(1);
		}
	close(fd);
return(0);
	}
else if (!strcmp(argv,"scalibrate"))
	{
		cntleftright=0;
		cntupdown=0;
		sprintf(lr1,"%d",cntleftright);
		sprintf(ud1,"%d",cntupdown);	
		strcat(lr,lr1);
		strcat(ud2,ud1);
		if (write(fd,lr,strlen(lr))!=strlen(lr))
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			return(1);
		}
		if (write(fd,ud2,strlen(ud2))!=strlen(ud2))
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			return(1);
		}
	close(fd);
return(0);
	}
else if (!strcmp(argv,"soff"))
	{
		sprintf(lr1,"OFF");
		sprintf(ud1,"OFF");	
		strcat(lr,lr1);
		strcat(ud2,ud1);
		if (write(fd,lr,strlen(lr))!=strlen(lr))
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			return(1);
		}
		if (write(fd,ud2,strlen(ud2))!=strlen(ud2))
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			return(1);
		}
	close(fd);
return(0);
	}
else
	{
		printf("\nError: Command wrong try <left/right/up/down/calibrate/off>\n");
		close(fd);			
		return(1);
	}

}
