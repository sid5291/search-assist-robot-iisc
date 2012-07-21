/* tcpclient.c */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h> 
#include <unistd.h>

#define END_FILE_CHARACTER 0x04  /* ctrl-d is unix-style eof input key*/


int linux_getch(void) 
{
  struct termios oldstuff;
  struct termios newstuff;
  int    inch;
  
  tcgetattr(STDIN_FILENO, &oldstuff);
  newstuff = oldstuff;                  /* save old attributes               */
  newstuff.c_lflag &= ~(ICANON | ECHO); /* reset "canonical" and "echo" flags*/
  tcsetattr(STDIN_FILENO, TCSANOW, &newstuff); /* set new attributes         */
  inch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldstuff); /* restore old attributes     */

  if (inch == END_FILE_CHARACTER) {
    inch = EOF;
  }
  return inch;
}


int main()

{

        int sock, bytes_recieved,chk=0;  
        char send_data[1024],recv_data[1024],c;
        struct hostent *host;
        struct sockaddr_in server_addr;  

        host = gethostbyname("192.168.0.14");

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        server_addr.sin_family = AF_INET;     
        server_addr.sin_port = htons(3000);   
        server_addr.sin_addr = *((struct in_addr *)host->h_addr);
        bzero(&(server_addr.sin_zero),8); 

        if (connect(sock, (struct sockaddr *)&server_addr,
                    sizeof(struct sockaddr)) == -1) 
        {
            perror("\nConnect\n");
            exit(1);
        }

        while(1)
        {
        
          bytes_recieved=recv(sock,recv_data,1024,0);
          recv_data[bytes_recieved] = '\0';
 
          if (strcmp(recv_data , "ack") != 0)
          {
	   printf("\n Error Acknowledgment not recieved");
           close(sock);
           break;
          }
          else
           	printf("\nAcknowledgement Recieved ");
          
	 while(1)
		{
			c=linux_getch();
			switch(c)
			{	case 'w':strcpy(send_data,"sup");chk=1;break;
				case 's':strcpy(send_data,"sdown");chk=1;break;
				case 'a':strcpy(send_data,"sleft");chk=1;break;
				case 'd':strcpy(send_data,"sright");chk=1;break;
				case 'q':strcpy(send_data,"quit");chk=1;break;
				case 'x':strcpy(send_data,"soff");chk=1;break;
				case 'c':strcpy(send_data,"scalibrate");chk=1;break;
				case '8':strcpy(send_data,"mforward");chk=1;break;
				case '2':strcpy(send_data,"mreverse");chk=1;break;				
				case '4':strcpy(send_data,"mleft");chk=1;break;
				case '6':strcpy(send_data,"mright");chk=1;break;
				case '+':strcpy(send_data,"mfast");chk=1;break;
				case '-':strcpy(send_data,"mslow");chk=1;break;
				case '5':strcpy(send_data,"mquit");chk=1;break;
				case '0':strcpy(send_data,"mstop");chk=1;break;
				case '1':strcpy(send_data,"minit");chk=1;break;
				case 'r':strcpy(send_data,"xr");chk=1;break;
				case 'g':strcpy(send_data,"xg");chk=1;break;
				case 'l':strcpy(send_data,"xl");chk=1;break;
				default :printf("\nInvalid input\n");strcpy(send_data,"error");break;
			}
			if(chk=1)
			{ 	chk=0;	
				break;
			}


		}

          // printf("\nSEND (q or Q to quit) : ");
          // gets(send_data);
           
          //if (strcmp(send_data , "q") != 0 && strcmp(send_data , "Q") != 0)

		printf("Client side : %s\n",send_data);
           send(sock,send_data,strlen(send_data), 0); 

           //send(sock,send_data,strlen(send_data), 0);   
           //close(sock);
           //break;
          
        
        }
printf("\n Connection closed\n");   
return 0;
}
