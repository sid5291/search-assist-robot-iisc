
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <gdk/gdkx.h>
#include "tcpclient.c"
#include <stdlib.h>
#include "tags.c"



GtkWidget *view, *view1;                // Declaration of the 2 text views
int i=0,con_check=0;                    // con_check flag variable to check if connection is established or not
GtkTextBuffer *buffer, *buffer1;        // global Text Buffers
GtkTextIter iter, iter1;              
GtkRcStyle *rc_style;
GdkColor color;
GtkWidget *mainwindow, *vpaned,*start_client ;    // GTKwidgets for the mainwindow and V pane of the two consoles
GtkWidget *scrolledwindow, *scrolledwindow1;
int fds[2];

int initialize(int argc, char **argv);

int execute();


void input_callback( gpointer data,gint source,GdkInputCondition condition )  // This function reads from the fds pipe opened and displays all the 
{                                                                             // g_print data in the respective console
   gchar buf[1024];
   gchar go[10];	
   gint chars_read;
   chars_read = 1024;
   gtk_text_buffer_get_end_iter(buffer, &iter);
   gtk_text_buffer_get_end_iter(buffer1, &iter1);
	i++;
   while (chars_read == 1024)
     {
        chars_read = read(fds[0], buf, 1024);
 	if (buf[0]=='-')                                                      // '-' is used to tag the Data ment for the main console 
	                                                                      // This is temporary till we use Text boxes for all data seperatelly 
	       {
               	gtk_text_buffer_insert(buffer1, &iter1,buf,chars_read); 
                gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW (view1),&iter1, 0.0, FALSE, 0, 0);
     	       }
	else
		{
		
		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, buf, chars_read, "white_fg", NULL);
		gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW (view),&iter, 0.0, FALSE, 0, 0);
		}   
}
lseek(fds[0],0,SEEK_SET);
}

static void motorhelp(GtkWidget *widget,gpointer data)                       // Function called on clicking motor-help
{                                                                            // displays an image with the key map and also a line of text with  
                                                                             // instructions for the user 
  	g_print("-For Wheels i=forward,k=back,j=left,l=right,+=fast,-=slow,0=stop\n");
	GtkWidget *window;
  	GtkWidget *image;

  
  	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
 	 gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
  	gtk_window_set_title(GTK_WINDOW(window), "DC Motor Keyboard Layout");
  	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

  	gtk_container_set_border_width(GTK_CONTAINER(window), 2);

  	image = gtk_image_new_from_file("keyboard.png");                              // The image displayed must be included in the same folder.
  	gtk_container_add(GTK_CONTAINER(window), image);


  	gtk_widget_show_all(window);

}

static void servohelp(GtkWidget *widget)                                           //Similar as motor-help but for control of the Camera Mount servos
{

	g_print("-For Servo a=left, d=right, w=up, s=down, x=off \n");

	GtkWidget *window;
  	GtkWidget *image;

  
  	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
 	 gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
  	gtk_window_set_title(GTK_WINDOW(window), "DC Motor Keyboard Layout");
  	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

  	gtk_container_set_border_width(GTK_CONTAINER(window), 2);

  	image = gtk_image_new_from_file("keyboard.png");
  	gtk_container_add(GTK_CONTAINER(window), image);

        gtk_widget_show_all(window);
}
static void connect1(GtkWidget *widget)                          // Function called on clicking Connect .. Establishes connection between the client
{                                                                //                                         and server
	int a=0;
	char c;
	if (con_check == 0)
	{
		a=client_connect();	
		if(a == 0)
		 {
			  g_print("-Connected");
		          con_check = 1;
		          
		 }
		else
		 {
			g_print("\nError in Connection");
			return;
		 }
        }
	else
		g_print("\nAlready Connected please disconnect before reattempting to connect");
}

static void init_motor(GtkWidget *widget)                           //Function invoked on Clicking Initialize sends the tags to server to intialize 
{                                                                   // all gpios 
   if (con_check == 1)
	 {
 	         bytes_recieved=recv(sock,recv_data,1024,0);
 	         recv_data[bytes_recieved] = '\0';
 
	          if (strcmp(recv_data , "ack") != 0)
	          {
			
                        close(sock);
			g_print("-Error:Disconnected\n");
			con_check=0;			
			return;
	          }
        	  else
        	   	g_print("\nAcknowledgement Recieved ");
     	
		strcpy(send_data,"minit");

                g_print("\nClient side : %s",send_data);
                send(sock,send_data,strlen(send_data), 0); 
                bytes_recieved=recv(sock,recv_data,1024,0);
 	         recv_data[bytes_recieved] = '\0';
 
	          if (strcmp(recv_data , "ack") != 0)
	          {
			g_print("\n Error Acknowledgment not recieved");
                        close(sock);
			g_print("-Error:Disconnected\n");
			con_check=0;			
			return;
	          }
        	  else
        	   	g_print("\nAcknowledgement Recieved ");
     	
		strcpy(send_data,"init");

                g_print("\nClient side : %s",send_data);
                send(sock,send_data,strlen(send_data), 0); 
		
		}
	else
               g_print("-Please Connect and try again\n");
	
}

static void disconnect1(GtkWidget *widget)             // function invoked on clicking Disconnect diconnects the connection between client and server
{
   if (con_check == 1)
	 {
 	         	
 	         bytes_recieved=recv(sock,recv_data,1024,0);
 	         recv_data[bytes_recieved] = '\0';
 
	          if (strcmp(recv_data , "ack") != 0)
	          {
			//g_print("\nError Acknowledgment not recieved");
                        close(sock);
    			g_print("-Error:Disconnected\n");
			con_check=0;			
			return;
	          }
        	  else
        	   	g_print("\nAcknowledgement Recieved ");
     	
		strcpy(send_data,"quit");
     //           g_print("\nClient side : %s",send_data);
                send(sock,send_data,strlen(send_data), 0);
		close(sock);
    		g_print("-Disconnected\n");
		con_check=0;			
		     	
	}	
   else
        g_print("-Already Disconnected\n");
	
}

static void clientserver(GtkWidget *widget,GdkEventKey *kevent, gpointer data)  // This function is invoked when Motor Control is highlited and any  
{                                                                               // key is pressed. The key press is registered and the depening on
	int a=0;                                                                // key value a specific command is sent to the server
	char c;                                                                 // Key presses are only registered when "Motor Control" button is 
       if(kevent->type == GDK_KEY_PRESS)                                        // highlighted
	{
	 gtk_button_set_label (GTK_BUTTON (start_client), "Controlling...");
	if (con_check == 1)
	 {
          bytes_recieved=recv(sock,recv_data,1024,0);
          recv_data[bytes_recieved] = '\0';
 
          if (strcmp(recv_data , "ack") != 0)
          {	                                                            // Checking for positive acknowledgement from server
           close(sock);
	   g_print("-Error:Disconnected\n");
	   con_check=0;	
	   return;	
          }
          else
           	g_print("\nAcknowledgement Recieved ");
     
       
			c=kevent->keyval;
			switch(c)                                                        // The switch case that maps the specific key to a tag
			{	case 'w':strcpy(send_data,"sup");chk=1;break;
				case 's':strcpy(send_data,"sdown");chk=1;break;
				case 'a':strcpy(send_data,"sleft");chk=1;break;
				case 'd':strcpy(send_data,"sright");chk=1;break;
				case 'q':strcpy(send_data,"quit");chk=1;break;
				case 'x':strcpy(send_data,"soff");chk=1;break;
				case 'c':strcpy(send_data,"scalibrate");chk=1;break;
				case 'i':strcpy(send_data,"mforward");chk=1;break;
				case 'k':strcpy(send_data,"mreverse");chk=1;break;				
				case 'j':strcpy(send_data,"mleft");chk=1;break;
				case 'l':strcpy(send_data,"mright");chk=1;break;
				case '+':strcpy(send_data,"mfast");chk=1;break;
				case '-':strcpy(send_data,"mslow");chk=1;break;
				//case '5':strcpy(send_data,"mquit");chk=1;break;
				case '0':strcpy(send_data,"mstop");chk=1;break;
				//case '1':strcpy(send_data,"minit");chk=1;break;
				case 'r':strcpy(send_data,"xr");chk=1;break;
				case 'g':strcpy(send_data,"xg");chk=1;break;
				case 'b':strcpy(send_data,"xb");chk=1;break;
				default :g_print("-Invalid input\n");strcpy(send_data,"error");break;
			}

        send(sock,send_data,strlen(send_data), 0); 
	}
	else
               g_print("-Please Connect and try again\n");
       }
}
static void camera(GtkWidget *widget)                       // invokes the cam.sh script file to display the video feed from the camera
{
	
	char command[20];
	strcpy(command,"./cam.sh &");	
	char ab1[10];
	g_print("calling\n");	
	FILE * rf; 
        rf= popen (command,"r"); 
	  if(!rf){
      		printf("Could not open pipe for output.\n");
      		return;
    		}

}



int initialize(int argc, char **argv)                      // this function initializes the GTK window and the layout
{
  GtkWidget  *start_camera, *servo_help , *motor_help, *motor_init, *connect, *disconnect;
  GtkWidget *hbox, *vbox;
  
  pipe (fds);
   
  dup2 (fds[1], STDOUT_FILENO);

  gtk_init(&argc, &argv);
 
  mainwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);                          // Intializing the Main window
  gtk_window_set_position(GTK_WINDOW(mainwindow), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(mainwindow), 600, 480);                 // the size 600x480
  gtk_container_set_border_width(GTK_CONTAINER(mainwindow), 0);
  g_signal_connect(G_OBJECT(mainwindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  start_client = gtk_button_new_with_label("Motor Control");                     // intializing the button "Motor Control"
  g_signal_connect(start_client,"key_press_event",G_CALLBACK(clientserver),NULL); // Connecting key_press_event with the clientserver function
  
  connect = gtk_button_new_with_label("Connect");                             // intializing the button "Connect" 
  g_signal_connect(connect,"clicked",G_CALLBACK(connect1),NULL);              // connecting the clicked signal with connect1 function
                                                                              // so as to invoke connect1 function on button click   
  motor_init = gtk_button_new_with_label("Initialize");                       //Similarly done for Initialize, Camera, Disconnect,Motor,Servo-Help
  g_signal_connect(motor_init,"clicked",G_CALLBACK(init_motor),NULL);

  start_camera = gtk_button_new_with_label("camera");
  g_signal_connect(start_camera,"clicked",G_CALLBACK(camera),NULL);

  servo_help = gtk_button_new_with_label("servo-help");
  g_signal_connect(servo_help,"clicked",G_CALLBACK(servohelp),NULL);
  
  motor_help = gtk_button_new_with_label("motor-help");
  g_signal_connect(motor_help,"clicked",G_CALLBACK(motorhelp),NULL);


  disconnect = gtk_button_new_with_label("Disconnect");
  g_signal_connect(disconnect,"clicked",G_CALLBACK(disconnect1),NULL);


  hbox = gtk_hbox_new(FALSE, 0);                                    //Establishing the basic boxes that comprimise the layout

  vbox = gtk_vbox_new(FALSE, 0);
 
   
  vpaned = gtk_vpaned_new ();                                      // Creating the vertical pane for both consoles 

  gtk_paned_set_gutter_size (GTK_PANED(vpaned),15);                       
  scrolledwindow = gtk_scrolled_window_new(NULL, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
  view = gtk_text_view_new();
  color.red = 0;
  color.green = 0;
  color.blue = 0;
  gdk_color_parse ("black", &color);                            // establishing the background of the terminal console as black
    
  gtk_widget_modify_base  (view,GTK_STATE_NORMAL, &color);
  
  gtk_container_add(GTK_CONTAINER(scrolledwindow), view);        // Adding the Text View to the scrolled window
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));        //Intializing the buffer for the Text view
  
   gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);         // intializing the pointer iter
 
   create_tags(buffer);
   
   gtk_paned_add2 (GTK_PANED(vpaned),scrolledwindow);

  scrolledwindow1 = gtk_scrolled_window_new(NULL, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
  view1 = gtk_text_view_new();
  gtk_container_add(GTK_CONTAINER(scrolledwindow1), view1);
  buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view1));
  create_tags(buffer1);
  gtk_text_buffer_get_iter_at_offset(buffer1, &iter1, 0);
  gtk_text_buffer_insert_with_tags_by_name(buffer1, &iter1, "Main Console\n",-1, "center","heading", NULL);//writing the heading for the main console
   gtk_paned_add1 (GTK_PANED(vpaned), scrolledwindow1);
   gtk_paned_set_position (GTK_PANED(vpaned),240);
  
  gtk_box_pack_start(GTK_BOX(vbox), connect, FALSE, FALSE, 2);   //Pack all buttons in to a vertical box
  gtk_box_pack_start(GTK_BOX(vbox), motor_init, FALSE, FALSE, 2);
  gtk_box_pack_start(GTK_BOX(vbox), start_client, FALSE, FALSE, 2);
  gtk_box_pack_start(GTK_BOX(vbox), start_camera, FALSE, FALSE, 2);
  gtk_box_pack_start(GTK_BOX(vbox), servo_help, FALSE, FALSE, 2);
  gtk_box_pack_start(GTK_BOX(vbox), motor_help, FALSE, FALSE, 2);
  gtk_box_pack_start(GTK_BOX(vbox), disconnect, FALSE, FALSE, 2);
  gtk_box_pack_start(GTK_BOX(hbox), vbox, FALSE ,FALSE , 0);       // pack the vbox and vpaned to the horizontal box
  gtk_box_pack_start(GTK_BOX(hbox), vpaned, TRUE ,TRUE , 0);
  
  
  gtk_container_add(GTK_CONTAINER(mainwindow), hbox);           // add the hbox to the mainwindow

  
  gdk_input_add(fds[0], GDK_INPUT_READ, input_callback, NULL);  // intialize the fds pipline to read the strings sent to g_print
  
  gtk_widget_show_all(mainwindow);                       // draw and display the mainwindow.

  return 0;
}

int execute() 
{
  gtk_main();

  return 0;
}

int main(int argc, char **argv) 
{
  int result = 0;
 // TopWin* topwin = new TopWin();


  if (0 == initialize(argc, argv)) {
    result = execute();
  }

  //delete topwin;

  return result;
}

