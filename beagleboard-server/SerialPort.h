	#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <string>

class SerialPort{
	public:
		SerialPort();
		bool open();
		void configure(int);
		void close();
		int getState();
        bool flush();

		int read( char*,int);
        int bytesToBeRead();
		int readTill(char *str,int len,char ch);
		int write(char*,int);
		bool writeCompulsory(const char*,int);
		bool readCompulsory(char*,int);

		~SerialPort();
		enum SerialDevice{TTYS0,TTYS1,TTYS2,TTYS3,TTYUSB0,TTYUSB1,TTYUSB2,TTYUSB3,TTYACM0};
		enum parity{NoParity,EvenParity,OddParity,SpaceParity};
		enum deviceState{Open,Closed};
		static char serialDeviceNames[][20];
		static char baudRates[][20];
	private:
		int fd;
		char deviceName[20];
		int state;
};


#endif
