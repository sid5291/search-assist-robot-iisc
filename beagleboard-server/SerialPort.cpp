#include "SerialPort.h"
//#include<iostream>
//#include <cstdio>
#include <stdio.h>
#include <fcntl.h>	/* File control definitions */
#include <errno.h>	/* Error number definitions */
#include <termios.h>	/* POSIX terminal control definitions */
#include <string.h>



SerialPort::SerialPort()
{
    strcpy(deviceName,serialDeviceNames[TTYACM0]);
    state=Closed;
}

bool SerialPort::open()
{
	//fd = open("/dev/ttyUSB0","r");
    fd = ::open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
     //   fd = ::open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
    // fd = ::open(deviceName, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == NULL)
    {
        perror("Opening Serial Port: Unable to open Device");
        return false;
    }
    fcntl(fd, F_SETFL, 0);
    state=Open;
   printf("open %d\n",state);
    return true;
}
void SerialPort::configure(int argParity)
{
    termios settings;

    // 	Get the current settings for the port...
    tcgetattr(fd, &settings);
	


    //Set local mode
    settings.c_cflag |= CLOCAL;
    //Set the port to read incoming data
   

    settings.c_cflag |= CREAD;
    //Set raw input
    settings.c_lflag &= ~ICANON;
   
//Disable SIGINTR, SIGSUSUP, SIGDSUSP, and SIGQUIT signals
    settings.c_lflag &= ~ISIG;

    //Map uppercase to lower case
    //settings.c_cflag |= XCASE;
    //Disable echoing of input
    settings.c_lflag &= ~ECHO;
    //Disable echoing of erase characters
    settings.c_lflag &= ~ECHOE;


    //Disable outgoing software flow control
    settings.c_iflag &= ~IXON;

    //Disable incoming software flow control
    settings.c_iflag &= ~IXOFF;

    //Disable flow start control by any character
    settings.c_iflag &= ~IXANY;
    
//Don't map NL to CR
    settings.c_iflag &= ~INLCR;

    //Don't map CR to NL
    settings.c_iflag &= ~ICRNL;
    //Don't map uppercase to lower case
    settings.c_iflag &= ~IUCLC;
   //Set raw output (no processing of output)
    settings.c_oflag &= ~OPOST;
   // 	Set the baud rates to 115200...
    cfsetispeed(&settings, B9600);
  cfsetospeed(&settings, B9600);
    if(argParity==NoParity)
    {
        //No Parity
        settings.c_cflag &= ~PARENB;
        settings.c_cflag &= ~CSTOPB;
        settings.c_cflag &= ~CSIZE;
        settings.c_cflag |= CS8;
    }
    else if(argParity==EvenParity)
    {
        //Even Parity
        settings.c_cflag |= PARENB;
        settings.c_cflag &= ~PARODD;
        settings.c_cflag &= ~CSTOPB;
        settings.c_cflag &= ~CSIZE;
        settings.c_cflag |= CS7;

        //Input parity check and strip
        settings.c_iflag |= (INPCK | ISTRIP);
    }
    else if(argParity==OddParity)
    {
        //Odd Parity
        settings.c_cflag |= PARENB;
        settings.c_cflag |= PARODD;
        settings.c_cflag &= ~CSTOPB;
        settings.c_cflag &= ~CSIZE;
        settings.c_cflag |= CS7;

        //Input parity check and strip
        settings.c_iflag |= (INPCK | ISTRIP);
    }

    //Apply settings for the port
    tcsetattr(fd, TCSANOW, &settings);
}


int SerialPort::getState()
{
    return state;
}

char SerialPort::serialDeviceNames[][20] = 
{
    "/dev/ttyS0",
    "/dev/ttyS1",
    "/dev/ttyS2",
    "/dev/ttyS3",
    "/dev/ttyUSB0",
    "/dev/ttyUSB1",
    "/dev/ttyUSB2",
    "/dev/ttyUSB3",
    "/dev/ttyACM0"
};

char SerialPort::baudRates[][20] =
{
    "B9600",
    "B19200",
    "B38400",
    "B57600",
    "B76800",
    "B115200"
};

void SerialPort::close()
{
    state=Closed;
    ::close(fd);
}

bool SerialPort :: flush()
{
    if(tcflush(fd,TCIOFLUSH)==-1)
    {
        printf("Flush operation failed\n");
        return false;
    }
    return true;
}

int SerialPort::read(char * str,int len)
{int inl;
	inl=::read(fd,str,len) ;


    return inl;
}

int SerialPort :: bytesToBeRead()
{
    return 0;
}


int SerialPort::readTill(char *str,int len,char ch)
{
    int bytesRead=0;
    while(len)
    {
        if(::read(fd,str,1)==-1)
            break;
        if(*str==ch)
            break;
        str++;
        len--;
        bytesRead++;
    }
    return bytesRead;
}

int SerialPort::write(char *str,int len)
{   int inl;
    inl=::write(fd,str,len);
   
	return inl;
}

bool SerialPort::writeCompulsory(const char* str,int len)
{
    int temp;
    while(len>0)
    {
        temp=::write(fd,str,len);
        if(temp>=0)
        {
            len-=temp;
            str+=temp;
        }
        else
            return false;
    }
    return true;
}

bool SerialPort::readCompulsory(char* str,int len)
{
    int temp;
    while(len>0)
    {
        temp=::read(fd,str,len);
        if(temp>=0)
        {
            len-=temp;
            str+=temp;
        }
        else
            return false;
    }
    return true;
}

SerialPort::~SerialPort()
{
    if(state!=Closed)
        close();
}


