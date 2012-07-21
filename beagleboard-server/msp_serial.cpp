#include<iostream>
#include <cstdio>
#include "SerialPort.h"
#define NR_BYTES 1000
#define PI 3.14159265
#include "SerialPort.cpp"
using namespace std;

SerialPort serialPort;	
//void little_to_big_endianess(unsigned char *,unsigned int);
void format(char * );

int msp_serial(int argc, char * argv)
{
	long i,nbytes;

	int n,in;
	char red[5]={'r'},green[5]={'g'},ack[5],c;
	char * signal;
//	float ax,ay,az,gx,gy,gz;
	//char v;


	FILE *fp;
	cout << "Serial Port Program"	<< endl ;

//	fp=fopen("imu_data.bin","wb");
	
	serialPort.open();
	serialPort.configure(SerialPort::NoParity);
	printf("Configure done");

        format(argv);
	
        serialPort.write(argv,1);
        if (argv[0] == 'r')
        {
	   cout<<"red light on"<<endl;	  
	}
	 else if (argv[0] == 'g')
        {
	   cout<<"green light on"<<endl;	  
	}
	else
	{
		cout<<"Lights off"<<endl;
	}
	serialPort.flush();
	
	serialPort.read(ack,1);
	
	printf("%d \n",ack[0]);

	return 0;
}


void format(char * temp)
{
	
	for (int i=1;i<=strlen(temp);i++)
	{
		temp[i-1]=temp[i];
	}
	
}
