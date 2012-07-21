/*
This file allows for DC motor control depending on the string passed to it from host pc it will perform either initialization, direction control and speed control. At the moment as the code has not been tested the we have disabled speed control by commenting the respective parts and including the intialization of setting the PWM inputs for the motordrivers to high hence allowing a constant speed.
*/

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
#define RTMI1 146
#define RTMI2 143
#define LTMI1 158
#define LTMI2 162
#define PWMA  144
#define PWMB  145
#define TOP 2500
#define MAX_BUF 64
extern int cntrt=TOP,cntlt=TOP;
char ud[20],pwmr[20],pwmr1[10],pwml[20],pwml1[10];
int direction(int a,int b,int c,int d);

int dc_motor(int argc, char * argv)
{
	int len,pd;
	char buf[100];
	//strcpy(pwmr,"8:");
	//strcpy(pwml,"14:");
	int st,fd,fp;
	
	if (argc < 2) 
	{
		printf("Usage: %s <motor direction mforward,mreverse,mright,mleft>", argv[0]);
		return(1);
	}

	if (!strcmp(argv,"minit"))
	{	len = sprintf(buf, SYSFS_GPIO_DIR "/export");
		fp=open(buf,O_WRONLY); 
		if (fp < 0)   
		{	
			printf("Cannot open export file.\n");
			close(fp);
			return(1);
		}		
		sprintf(ud,"%d",RTMI1);				
		if (pd=write(fp,ud,strlen(ud))!=strlen(ud))		//export right motor input 1
		{
			printf("%s %d",ud,strlen(ud));
			printf("\nError: could not write to the pin %d export file\n",RTMI1);
			close(fp);			
			return(1);
		}
		else
		{	printf("\n pin %d exported \n",RTMI1);
			len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", RTMI1);
			fd = open(buf,O_WRONLY);
				
			if (fd < 0)				// opening direction file of rt motor inp 1
			{	
				printf("Cannot open pin %d direction file.\n",RTMI1);
				close(fd);			
				return(1);
			}	
			sprintf(ud,"out");
			if (write(fd,ud,strlen(ud))!=strlen(ud))		// setting direction of rt motor inp 1 as out
			{
				printf("\nError: could not write to the %d direction file\n",RTMI1);
				close(fd);			
				return(1);
			}
			close(fd);		
		}
		sprintf(ud,"%d",RTMI2);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//export right motor input 2
		{
			printf("\nError: could not write to the pin %d export file\n",RTMI2);
			close(fp);			
			return(1);
		}
		else
		{	printf("\n pin %d exported \n",RTMI2);		
			len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", RTMI2);
			fd = open(buf,O_WRONLY);		
			if (fd < 0)				// opening direction file of rt motor inp 2
			{	
				printf("Cannot open pin %d direction file.\n",RTMI2);
				close(fd);
				return(1);
			}
			sprintf(ud,"out");
			if (write(fd,ud,strlen(ud))!=strlen(ud))		// setting direction of rt motor inp 2 as out
			{
				printf("\nError: could not write to the %d direction file\n",RTMI2);
				close(fd);			
				return(1);
			}
			close(fd);		
		}
		sprintf(ud,"%d",LTMI1);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//export left motor input 1
		{
			printf("\nError: could not write to the pin %d export file\n",LTMI1);
			close(fp);			
			return(1);
		}
		else
		{	printf("\n pin %d exported \n",LTMI1);
			len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", LTMI1);
			fd = open(buf,O_WRONLY);		
			if (fd < 0)				// opening direction file of lt motor inp 1
			{	
				printf("Cannot open pin %d direction file.\n",LTMI1);
				fd = open(buf,O_WRONLY);
				return(1);
			}
			sprintf(ud,"out");
			if (write(fd,ud,strlen(ud))!=strlen(ud))		// setting direction of lt motor inp 1 as out
			{
				printf("\nError: could not write to the %d direction file\n",LTMI1);
				close(fd);			
				return(1);
			}
			close(fd);		
		}
		sprintf(ud,"%d",LTMI2);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//export left motor input 2
		{
			printf("\nError: could not write to the pin %d export file\n",LTMI2);
			close(fp);			
			return(1);
		}
		else
		{	printf("\n pin %d exported \n",LTMI2);
			len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", LTMI2);		
			fd = open(buf,O_WRONLY);
			if (fd < 0)				// opening direction file of lt motor inp 2
			{	
				printf("Cannot open pin %d direction file.\n",LTMI2);
				close(fd);
				return(1);
			}
			sprintf(ud,"out");
			if (write(fd,ud,strlen(ud))!=strlen(ud))		// setting direction of lt motor inp 2 as out
			{
				printf("\nError: could not write to the %d direction file\n",LTMI2);
				close(fd);			
				return(1);
			}
			close(fd);		
		}

		sprintf(ud,"%d",PWMA);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//export PWMA pin as gpio
		{
			printf("\nError: could not write to the pin %d export file\n",PWMA);
			close(fp);			
			return(1);
		}
		else
		{	printf("\n pin %d exported \n",PWMA);
			len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", PWMA);		
			fd = open(buf,O_WRONLY);
			if (fd < 0)				// opening direction file of PWMA gpio
			{	
				printf("Cannot open pin %d direction file.\n",PWMA);
				close(fd);
				return(1);
			}
			sprintf(ud,"out");
			if (write(fd,ud,strlen(ud))!=strlen(ud))		// setting direction of PWMA gpio as out
			{
				printf("\nError: could not write to the %d direction file\n",PWMA);
				close(fd);			
				return(1);
			}
			close(fd);		
		}

		sprintf(ud,"%d",PWMB);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//export PWMB pin as gpio
		{
			printf("\nError: could not write to the pin %d export file\n",PWMB);
			close(fp);			
			return(1);
		}
		else
		{	printf("\n pin %d exported \n",PWMB);
			len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", PWMB);		
			fd = open(buf,O_WRONLY);
			if (fd < 0)				// opening direction file of PWMA gpio
			{	
				printf("Cannot open pin %d direction file.\n",PWMB);
				close(fd);
				return(1);
			}
			sprintf(ud,"out");
			if (write(fd,ud,strlen(ud))!=strlen(ud))		// setting direction of PWMA gpio as out
			{
				printf("\nError: could not write to the %d direction file\n",PWMB);
				close(fd);			
				return(1);
			}
			close(fd);		
		}
		len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", PWMA); 
		fp = open(buf,O_WRONLY);
		if (fp < 0)				// opening the value file of PWMA
		{
			printf("Cannot open pin %d value file.\n",PWMA);
			close(fp);
			return(1);
		}
		sprintf(ud,"%d",1);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//setting value high to PWMA ( for no speed control)
		{
			printf("\nError: could not write to the %d value file\n",PWMA);
			close(fp);			
			return(1);
		}
		close(fp);
		
		len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", PWMB); 
		fp = open(buf,O_WRONLY);
		if (fp < 0)				// opening the value file of PWMB
		{
			printf("Cannot open pin %d value file.\n",PWMB);
			close(fp);
			return(1);
		}
		sprintf(ud,"%d",1);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//setting value high to PWMB ( for no speed control)
		{
			printf("\nError: could not write to the %d value file\n",PWMB);
			close(fp);			
			return(1);
		}
		close(fp);


		/*fd = open("/dev/servodrive0",O_WRONLY); 			
		if (fd < 0)
		{	
			printf("\nError: /dev/servodrive0 doesnot exist try #modprobe servodrive\n");	
			close(fd);
			return(1);
		}
		sprintf(pwmr1,"%d",cntrt);
		strcat(pwmr,pwmr1);
		if (write(fd,pwmr,strlen(pwmr))!=strlen(pwmr))		//initializing pwm of right motor
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			return(1);
		}
		sprintf(pwml1,"%d",cntlt);
		strcat(pwml,pwml1);
		if (write(fd,pwml,strlen(pwml))!=strlen(pwml))		//initializing pwm of left motor
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			re00turn(1);
		}
		close(fd);*/	
		st=direction(0,0,0,0);
	close(fp);
	return(0);	
	}
	else if(!strcmp(argv,"mforward"))
	{
		st=direction(1,0,0,1);
		return(st);
	}
	else if(!strcmp(argv,"mreverse"))
	{
		st=direction(0,1,1,0);
		return(st);
	}
	else if(!strcmp(argv,"mright"))
	{
		st=direction(0,1,0,1);
		return(st);
	}
	else if(!strcmp(argv,"mleft"))
	{
		st=direction(1,0,1,0);
		return(st);
	}
	else if(!strcmp(argv,"mstop"))
	{
		st=direction(0,0,0,0);
		return(st);
	}
	/*else if (!strcmp(argv,"mfast"))				//increase the pulse of pwm
	{
		fd =open("/dev/servodrive0",O_WRONLY);
		if (fd < 0)	
		{	
			printf("\nError: /dev/servodrive0 doesnot exist try #modprobe servodrive\n");
			close(fd);
			return(1);
		}
		cntrt+=25;
		cntlt+=25;
		sprintf(pwmr1,"%d",cntrt);
		strcat(pwmr,pwmr1);
		if (write(fd,pwmr,strlen(pwmr))!=strlen(pwmr))		//increase the pulse of right motor pwm
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			return(1);
		}
		sprintf(pwml1,"%d",cntlt);
		strcat(pwml,pwml1);
		if (write(fd,pwml,strlen(pwml))!=strlen(pwml))		//increase the pulse of left motor pwm
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			return(1);
		}
		close(fd);
		return(0);
	}
	else if (!strcmp(argv,"mslow"))				//decrease the pulse of pwm
	{
		fd =open("/dev/servodrive0",O_WRONLY);
		if (fd < 0)
		{	
			printf("\nError: /dev/servodrive0 doesnot exist try #modprobe servodrive\n");
			close(fd);
			return(1);
		}
		cntrt-=25;
		cntlt-=25;
		sprintf(pwmr1,"%d",cntrt);
		strcat(pwmr,pwmr1);
		if (write(fd,pwmr,strlen(pwmr))!=strlen(pwmr))		//decrease the pulse of right motor pwm
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			return(1);
		}
		sprintf(pwml1,"%d",cntlt);
		strcat(pwml,pwml1);
		if (write(fd,pwml,strlen(pwml))!=strlen(pwml))		//decrease the pulse of left motor pwm
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			return(1);
		}
		close(fd);
		return(0);
	}*/
	else if(!strcmp(argv,"mquit"))
	{
		printf("Quiting Motor operation");	
		len = sprintf(buf, SYSFS_GPIO_DIR "/unexport");
		fp=open(buf,O_WRONLY); 
		if (fp < 0)   
		{	
			printf("Cannot open unexport file.\n");
			close(fp);
			return(1);
		}		
		sprintf(ud,"%d",RTMI1);				
		if (pd=write(fp,ud,strlen(ud))!=strlen(ud))		//unexport right motor input 1
		{
			printf("%s %d",ud,strlen(ud));
			printf("\nError: could not write to the pin %d unexport file\n",RTMI1);
			close(fp);			
			return(1);
		}
		else
		{
			printf("\n pin %d unexported \n",RTMI1);				
		}
		sprintf(ud,"%d",RTMI2);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//unexport right motor input 2
		{
			printf("\nError: could not write to the pin %d unexport file\n",RTMI2);
			close(fp);			
			return(1);
		}
		else
		{
			printf("\n pin %d unexported \n",RTMI2);				
		}
		sprintf(ud,"%d",LTMI1);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//unexport left motor input 1
		{
			printf("\nError: could not write to the pin %d unexport file\n",LTMI1);
			close(fp);			
			return(1);
		}
		else
		{
			printf("\n pin %d unexported \n",LTMI1);		
		}
		sprintf(ud,"%d",LTMI2);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//unexport left motor input 2
		{
			printf("\nError: could not write to the pin %d unexport file\n",LTMI2);
			close(fp);			
			return(1);
		}
		else
		{	
			printf("\n pin %d unexported \n",LTMI2);		
		}
		sprintf(ud,"%d",PWMA);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//unexport PWMA
		{
			printf("\nError: could not write to the pin %d unexport file\n",PWMA);
			close(fp);			
			return(1);
		}
		else
		{	
			printf("\n pin %d unexported \n",PWMA);		
		}
 		sprintf(ud,"%d",PWMB);
		if (write(fp,ud,strlen(ud))!=strlen(ud))		//unexport PWMB
		{
			printf("\nError: could not write to the pin %d unexport file\n",PWMB);
			close(fp);			
			return(1);
		}
		else
		{	
			printf("\n pin %d unexported \n",PWMB);		
		}
		/*fd = open("/dev/servodrive0",O_WRONLY); 			
		if (fd < 0)
		{	
			printf("\nError: /dev/servodrive0 doesnot exist try #modprobe servodrive\n");	
			close(fd);
			return(1);
		}
		sprintf(pwmr1,"OFF");
		strcat(pwmr,pwmr1);
		if (write(fd,pwmr,strlen(pwmr))!=strlen(pwmr))		//initializing pwm of right motor
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			return(1);
		}
		sprintf(pwml1,"OFF");
		strcat(pwml,pwml1);
		if (write(fd,pwml,strlen(pwml))!=strlen(pwml))		//initializing pwm of left motor
		{
			printf("\nError: could not write to the file\n");
			close(fd);			
			return(1);
		}
		close(fd);*/	
		close(fp);
		return(0);
	}	
	else
	{
		printf("\nError: Command wrong try <mforward/mreverse/mleft/mright/mstop/minit/mexport/mfast/mslow>\n");
		close(fd);			
		return(1);
	}
}



int direction(int a,int b,int c,int d)
{
	int fp,len;
	char buf[MAX_BUF];
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", RTMI1); 
	fp = open(buf,O_WRONLY);
	if (fp < 0)				                     // opening the value file of rt motor inp 1
	{
		printf("Cannot open pin %d value file.\n",RTMI1);
		close(fp);
		return(1);
	}
	sprintf(ud,"%d",a);
	if (write(fp,ud,strlen(ud))!=strlen(ud))		//setting value to rt motor inp 1
	{
		printf("\nError: could not write to the %d value file\n",RTMI1);
		close(fp);			
		return(1);
	}
	close(fp);
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", RTMI2); 
	fp = open(buf,O_WRONLY);	
	if (fp < 0)				// opening the value file of rt motor inp 2
	{
		printf("Cannot open pin %d value file.\n",RTMI2);
		close(fp);
		return(1);
	}
	sprintf(ud,"%d",b);
	if (write(fp,ud,strlen(ud))!=strlen(ud))		//setting value to rt motor inp 2
	{
		printf("\nError: could not write to the %d value file\n",RTMI2);
		close(fp);			
		return(1);
	}
	close(fp);
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", LTMI1); 
	fp = open(buf,O_WRONLY);
	if (fp < 0)				// opening the value file of lt motor inp 1
	{
		printf("Cannot open pin %d value file.\n",LTMI1);
		close(fp);
		return(1);
	}
	sprintf(ud,"%d",c);
	if (write(fp,ud,strlen(ud))!=strlen(ud))		//setting value to lt motor inp 1
	{
		printf("\nError: could not write to the %d value file\n",LTMI1);
		close(fp);			
		return(1);
	}
	close(fp);
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", LTMI2); 
	fp = open(buf,O_WRONLY);
	if (fp < 0)				// opening the value file of lt motor inp 2
	{
		printf("Cannot open pin %d value file.\n",LTMI2);
		close(fp);
		return(1);
	}
	sprintf(ud,"%d",d);
	if (write(fp,ud,strlen(ud))!=strlen(ud))		//setting value to lt motor inp 2
	{
		printf("\nError: could not write to the %d value file\n",LTMI2);
		close(fp);			
		return(1);
	}
	close(fp);
	return 0;
	
}

