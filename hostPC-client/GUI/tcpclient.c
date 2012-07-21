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

int sock, bytes_recieved,chk=0;  
char send_data[1024],recv_data[1024];
struct hostent *host;
struct sockaddr_in server_addr;  


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


int client_connect()

{

        
        host = gethostbyname("10.42.0.2");

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
            g_print("\nSocket Error");
            exit(1);
        }

        server_addr.sin_family = AF_INET;     
        server_addr.sin_port = htons(3000);   
        server_addr.sin_addr = *((struct in_addr *)host->h_addr);
        bzero(&(server_addr.sin_zero),8); 

        if (connect(sock, (struct sockaddr *)&server_addr,
                    sizeof(struct sockaddr)) == -1) 
        {
            g_print("\nConnect\n");
            exit(1);
        }
g_print("\nConnected\n");
return 0;
}

int hello()
{
 g_print("hello\n");
 return 0;
}

