/* tcpserver.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "servo_drive.c"
#include "motor_drive.c"
#include "init.c"
#include "msp_serial.cpp"

int main()
{
        int sock, connected, bytes_recieved , true1 = 1,cls = 0;  
        char send_data [1024] , recv_data[1024], cmd[1024];       

        struct sockaddr_in server_addr,client_addr;    
        unsigned int sin_size;
        
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("\nSocket\n");
            exit(1);
        }

        if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true1,sizeof(int)) == -1) {
            perror("\nSetsockopt\n");
            exit(1);
        }
        
        server_addr.sin_family = AF_INET;         
        server_addr.sin_port = htons(3000);     
        server_addr.sin_addr.s_addr = INADDR_ANY; 
        bzero(&(server_addr.sin_zero),8); 

        if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
                                                                       == -1) {
            perror("\nUnable to bind\n");
            exit(1);
        }

        if (listen(sock, 5) == -1) {
            perror("\nListen\n");
            exit(1);
        }
		
	printf("\nTCPServer Waiting for client on port 5000");
        fflush(stdout);


        while(1)
        {  

            sin_size = sizeof(struct sockaddr_in);

            connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);

            printf("\n I got a connection from (%s , %d)",
                   inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

            while (1)
            {
//              printf("\n SEND (q or Q to quit) : ");
              strcpy(send_data,"ack");
              
              send(connected, send_data,strlen(send_data), 0);  

              bytes_recieved = recv(connected,recv_data,1024,0);

              recv_data[bytes_recieved] = '\0';

              if (strcmp(recv_data , "quit") == 0)
              {
		strcpy(cmd,"mquit");
                dc_motor(2,cmd);
		strcpy(cmd,"init_un");
                init(2,cmd);
                close(connected);
		cls=1;                
		break;
              }

              else 
              {
		printf("\n RECIEVED DATA = %s " , recv_data);
		switch(recv_data[0])
		{
		case 'i':		
			if(init(2,recv_data))
			{	printf("\nError: in Execution of servo_drive\n");
				return(1);		
			};break;
		case 's':		
			if(servo(2,recv_data))
			{	printf("\nError: in Execution of servo_drive\n");
				return(1);		
			};break;
		case 'm':if(dc_motor(2,recv_data))
			{	
				printf("\nError: in Execution of motor_drive\n");
				return(1);		
			};break;
		case 'x':if(msp_serial(2,recv_data))
			{	
				printf("\nError: in Execution of msp_serial\n");
				return(1);		
			};break;
		default:printf("\nInvalid input");break;	
		}	
	      }
              fflush(stdout);
            }
	if (cls=1)
	{	
		break;
	}
       }       
	printf("\nConnection Closed!!\n");
      close(sock);
      return 0;
} 
