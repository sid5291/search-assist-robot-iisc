#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define OE1  139
#define DIR1 138
#define OE2  137
#define DIR2 136

int init_val(int,int,int,int);
int init(int argc, char * argv)
{
	int len,pd;
	char buf[100];
	//strcpy(pwmr,"8:");
	//strcpy(pwml,"14:");
	int st,fd,fp;
	
	
	if (!strcmp(argv,"init"))
	{	len = sprintf(buf, SYSFS_GPIO_DIR "/export");
		fp=open(buf,O_WRONLY); 
		if (fp < 0)   
		{	
			printf("Cannot open export file.\n");
			close(fp);
			return(1);
		}		
		sprintf(ud,"%d",OE1);				
		if (pd=write(fp,ud,strlen(ud))!=strlen(ud))		//export right motor input 1
		{
			printf("%s %d",ud,strlen(ud));
			printf("\nError: could not write to the pin %d export file\n",OE1);
			close(fp);			
			return(1);
		}
		else
		{	printf("\n pin %d exported \n",OE1);
			len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", OE1);
			fd = open(buf,O_WRONLY);
				
			if (fd < 0)				// opening direction file of rt motor inp 1
			{	
				printf("Cannot open pin %d direction file.\n",OE1);
				close(fd);			
				return(1);
			}	
			sprintf(ud,"out");
			if (write(fd,ud,strlen(ud))!=strlen(ud))		// setting direction of rt motor inp 1 as out
			{
				printf("\nError: could not write to the %d direction file\n",OE1);
				close(fd);			
				return(1);
			}
			close(fd);		
		}
		sprintf(ud,"%d",DIR1);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//export right motor input 2
		{
			printf("\nError: could not write to the pin %d export file\n",DIR1);
			close(fp);			
			return(1);
		}
		else
		{	printf("\n pin %d exported \n",DIR1);		
			len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", DIR1);
			fd = open(buf,O_WRONLY);		
			if (fd < 0)				// opening direction file of rt motor inp 2
			{	
				printf("Cannot open pin %d direction file.\n",DIR1);
				close(fd);
				return(1);
			}
			sprintf(ud,"out");
			if (write(fd,ud,strlen(ud))!=strlen(ud))		// setting direction of rt motor inp 2 as out
			{
				printf("\nError: could not write to the %d direction file\n",DIR1);
				close(fd);			
				return(1);
			}
			close(fd);		
		}
		sprintf(ud,"%d",OE2);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//export left motor input 1
		{
			printf("\nError: could not write to the pin %d export file\n",OE2);
			close(fp);			
			return(1);
		}
		else
		{	printf("\n pin %d exported \n",OE2);
			len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", OE2);
			fd = open(buf,O_WRONLY);		
			if (fd < 0)				// opening direction file of lt motor inp 1
			{	
				printf("Cannot open pin %d direction file.\n",OE2);
				fd = open(buf,O_WRONLY);
				return(1);
			}
			sprintf(ud,"out");
			if (write(fd,ud,strlen(ud))!=strlen(ud))		// setting direction of lt motor inp 1 as out
			{
				printf("\nError: could not write to the %d direction file\n",OE2);
				close(fd);			
				return(1);
			}
			close(fd);		
		}
		sprintf(ud,"%d",DIR2);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//export left motor input 2
		{
			printf("\nError: could not write to the pin %d export file\n",DIR2);
			close(fp);			
			return(1);
		}
		else
		{	printf("\n pin %d exported \n",DIR2);
			len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", DIR2);		
			fd = open(buf,O_WRONLY);
			if (fd < 0)				// opening direction file of lt motor inp 2
			{	
				printf("Cannot open pin %d direction file.\n",DIR2);
				close(fd);
				return(1);
			}
			sprintf(ud,"out");
			if (write(fd,ud,strlen(ud))!=strlen(ud))		// setting direction of lt motor inp 2 as out
			{
				printf("\nError: could not write to the %d direction file\n",DIR2);
				close(fd);			
				return(1);
			}
			close(fd);		
		}

	init_val(0,1,1,0);	
	
	}
	else if (!strcmp(argv,"init_un"))
	{
		printf("Unintializing pins");	
		len = sprintf(buf, SYSFS_GPIO_DIR "/unexport");
		fp=open(buf,O_WRONLY); 
		if (fp < 0)   
		{	
			printf("Cannot open unexport file.\n");
			close(fp);
			return(1);
		}		
		sprintf(ud,"%d",OE1);				
		if (pd=write(fp,ud,strlen(ud))!=strlen(ud))		//unexport right motor input 1
		{
			printf("%s %d",ud,strlen(ud));
			printf("\nError: could not write to the pin %d unexport file\n",OE1);
			close(fp);			
			return(1);
		}
		else
		{
			printf("\n pin %d unexported \n",OE1);				
		}
		sprintf(ud,"%d",DIR1);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//unexport right motor input 2
		{
			printf("\nError: could not write to the pin %d unexport file\n",DIR1);
			close(fp);			
			return(1);
		}
		else
		{
			printf("\n pin %d unexported \n",DIR1);				
		}
		sprintf(ud,"%d",OE2);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//unexport left motor input 1
		{
			printf("\nError: could not write to the pin %d unexport file\n",OE2);
			close(fp);			
			return(1);
		}
		else
		{
			printf("\n pin %d unexported \n",OE2);		
		}
		sprintf(ud,"%d",DIR2);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//unexport left motor input 2
		{
			printf("\nError: could not write to the pin %d unexport file\n",DIR2);
			close(fp);			
			return(1);
		}
		else
		{	
			printf("\n pin %d unexported \n",DIR2);		
		}
		
	}

	else
	{
		printf("\nError in Command ");
		close(fd);			
		return(1);
	}
}



int init_val(int a,int b,int c,int d)
{
	int fp,len;
	char buf[MAX_BUF];
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", OE1); 
	fp = open(buf,O_WRONLY);
	if (fp < 0)				// opening the value file of rt motor inp 1
	{
		printf("Cannot open pin %d value file.\n",OE1);
		close(fp);
		return(1);
	}
	sprintf(ud,"%d",a);
	if (write(fp,ud,strlen(ud))!=strlen(ud))		//setting value to rt motor inp 1
	{
		printf("\nError: could not write to the %d value file\n",OE1);
		close(fp);			
		return(1);
	}
	close(fp);
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", DIR1); 
	fp = open(buf,O_WRONLY);	
	if (fp < 0)				// opening the value file of rt motor inp 2
	{
		printf("Cannot open pin %d value file.\n",DIR1);
		close(fp);
		return(1);
	}
	sprintf(ud,"%d",b);
	if (write(fp,ud,strlen(ud))!=strlen(ud))		//setting value to rt motor inp 2
	{
		printf("\nError: could not write to the %d value file\n",DIR1);
		close(fp);			
		return(1);
	}
	close(fp);
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", OE2); 
	fp = open(buf,O_WRONLY);
	if (fp < 0)				// opening the value file of lt motor inp 1
	{
		printf("Cannot open pin %d value file.\n",OE2);
		close(fp);
		return(1);
	}
	sprintf(ud,"%d",c);
	if (write(fp,ud,strlen(ud))!=strlen(ud))		//setting value to lt motor inp 1
	{
		printf("\nError: could not write to the %d value file\n",OE2);
		close(fp);			
		return(1);
	}
	close(fp);
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", DIR2); 
	fp = open(buf,O_WRONLY);
	if (fp < 0)				// opening the value file of lt motor inp 2
	{
		printf("Cannot open pin %d value file.\n",DIR2);
		close(fp);
		return(1);
	}
	sprintf(ud,"%d",d);
	if (write(fp,ud,strlen(ud))!=strlen(ud))		//setting value to lt motor inp 2
	{
		printf("\nError: could not write to the %d value file\n",DIR2);
		close(fp);			
		return(1);
	}
	close(fp);
	return 0;
	
}

