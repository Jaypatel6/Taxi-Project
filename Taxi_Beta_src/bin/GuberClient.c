/* Client Application for Guber */
/* adapted from GTK_ClockClient.c by Rainer Doemer */

#include "GuberClient.h"

/*#define debug*/
#define DEBUG 	
#define BUFFSIZE 256
/*#define frame_size*/

void reqBtn_callback(GtkWidget *reqBtn, gpointer user_data);

static void enter_callback(GtkWidget *widget, GtkWidget *entry);

/*** global variables ****************************************************/

const char *Program	/* program name for descriptive diagnostics */
	= NULL;
struct sockaddr_in
	ServerAddress;	/* server address we connect with */

/*** global functions ****************************************************/

void FatalError(		/* print error diagnostics and abort */
	const char *ErrorMsg)
{
    fputs(Program, stderr);
    fputs(": ", stderr);
    perror(ErrorMsg);
    fputs(Program, stderr);
    fputs(": Exiting!\n", stderr);
    exit(20);
} /* end of FatalError */

char *Talk2Server(		/* communicate with the server */
	const char *Message,
	char *RecvBuf)
{
    int n;
    int SocketFD;

    SocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (SocketFD < 0)
    {   FatalError("socket creation failed");
    }
#ifdef DEBUG
    printf("%s: Connecting to the server at port %d...\n",
		Program, ntohs(ServerAddress.sin_port));
#endif
    if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		sizeof(struct sockaddr_in)) < 0)
    {   FatalError("connecting to server failed");
    }
#ifdef DEBUG
    printf("%s: Sending message '%s'...\n", Program, Message);
#endif
    n = write(SocketFD, Message, strlen(Message));
    if (n < 0)
    {   FatalError("writing to socket failed");
    }
#ifdef DEBUG
    printf("%s: Waiting for response...\n", Program);
#endif
    n = read(SocketFD, RecvBuf, BUFFSIZE-1);
    if (n < 0) 
    {   FatalError("reading from socket failed");
    }
    RecvBuf[n] = 0;
#ifdef DEBUG
    printf("%s: Received response: %s\n", Program, RecvBuf);
    printf("%s: Closing the connection...\n", Program);
#endif
    close(SocketFD);
    return(RecvBuf);
} /* end of Talk2Server */

void GetResponseFromServer(		/* ask server for current time, display it */
	GtkWidget *Widget,
	gpointer Data)
{
    GtkWidget *ButtonClicked;
    GtkLabel *LabelToUpdate;
    char RecvBuf[BUFFSIZE];
    const char *Response;

#ifdef DEBUG
    printf("%s: GetMsgFromServer callback starting...\n", Program);
#endif
    ButtonClicked = Widget;
    LabelToUpdate = Data;
    assert(LabelToUpdate);
    Response = Talk2Server("TIME", RecvBuf);
    
	/*display status from server*/
	gtk_label_set_label(LabelToUpdate, Response);
    
} /* end of GetResponseFromServer */

void ShutdownServer(		/* ask server to shutdown */
	GtkWidget *Widget,
	gpointer Data)
{
    char RecvBuf[BUFFSIZE];
    const char *Response;

#ifdef DEBUG
    printf("%s: ShutdownServer callback starting...\n", Program);
#endif
    Response = Talk2Server("SHUTDOWN", RecvBuf);
    if (0 == strcmp(Response, "OK SHUTDOWN"))
    {	/* ok, the server shuts down, so should this client */
	gtk_main_quit();
    }
    else
    {	/* unexpected response, ignore it as invalid */
    }
#ifdef DEBUG
    printf("%s: ShutdownServer callback done.\n", Program);
#endif
} /* end of ShutdownServer */



/*======================== main =================================*/

int main(			
	int argc,
	char *argv[])
{
	Map map;
	map = Reader(map);
#ifdef debug
int i, j;
	for(i = 0; i < map.y; i++){
		for(j = 0; j < map.x; j++){
			printf("%c ",map.arr[i*map.x + j]);
		}
		printf("\n");
	}
#endif
	
#ifdef debug1
	for(i = 0; i < map.num_taxis; i++)
	{
	 printf("%d", taxiFleet[i].taxiID);
	}
#endif
	
/* 	while(1)
	{
	printf("\n%f\n", getServerClock());
	} */
	/*make the array/taxis
	make requests
	service requests increment income and overhead
	refresh taxi locations/job */

     int PortNo;
    struct hostent *Server;

    Program = argv[0];
#ifdef DEBUG
    printf("%s: Starting...\n", argv[0]);
#endif
    if (argc < 3)
    {   fprintf(stderr, "Usage: %s hostname port\n", Program);
	exit(10);
    }
    Server = gethostbyname(argv[1]);
    if (Server == NULL)
    {   fprintf(stderr, "%s: no such host named '%s'\n", Program, argv[1]);
        exit(10);
    }
    PortNo = atoi(argv[2]);
    if (PortNo <= 2000)
    {   fprintf(stderr, "%s: invalid port number %d, should be >2000\n",
		Program, PortNo);
        exit(10);
    }
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(PortNo);
    ServerAddress.sin_addr = *(struct in_addr*)Server->h_addr_list[0];


    /*======================= Create the GUI =============================*/
#ifdef reference
	GdkPixbuf *icon;
	GtkWidget *window;
	GtkWidget *frameMain;	
	GtkWidget *hboxMain;
	GtkWidget *frameL;	
	GtkWidget *frameR;	
	GtkWidget *vboxL;	
	GtkWidget *vboxR;	
	GtkWidget *halignL;
	GtkWidget *halignR;		
	GtkWidget *frameStatus;		
	GtkWidget *frameInput;
	GtkWidget *valignStatus;
	GtkWidget *hboxBtn;
	GtkWidget *halignButtons;	
	GtkWidget *halignBtn;
	GtkWidget *halignCnl;
	GtkWidget *valignBtn;
	GtkWidget *reqBtn;	
	GtkWidget *cnlBtn;	
	GtkWidget *valignEntry;	
	GtkWidget *vboxEntry;
	GtkWidget *frameEntry;
	GtkWidget *vboxPickup;		
	GtkWidget *vboxDropoff;		
	GtkWidget *valignDrop;
	GtkWidget *valignPick;	
	/*GtkWidget *entryPick;*/
	/*GtkWidget *entryDrop;*/
	gint tempPos;
	GtkWidget *labelFare;

	/* cairo */
	GtkWidget *DrawArea;
	GtkWidget *DrawAreaLogo;
	GtkWidget *valignLogo;
	GtkWidget *vboxLogo;

#endif
	
	
	/*** create window ***/
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if (!window)
    	{   
    		fprintf(stderr, "%s: cannot create GUI window\n", Program);
        	exit(15);
    	}
	/*center window title*/
	gtk_window_set_title(GTK_WINDOW(window), "Güber Taxi Services");
	/*choose window size*/		
	gtk_window_set_default_size(GTK_WINDOW(window), 1200, 700);
	/*center window on screen*/		
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	
	/*** load icon ***/
	icon = create_pixbuf("taxi_clipart.png");
	gtk_window_set_icon(GTK_WINDOW(window), icon);
	
	/*** main frame ***/
	/* set border */
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	/* create frame*/
	frameMain = gtk_frame_new(NULL);
	gtk_widget_set_size_request(frameMain, 1150, 700);		/*set fixed size*/
	gtk_container_add(GTK_CONTAINER(window), frameMain);
	
	/*set style of frame*/
	gtk_frame_set_shadow_type(GTK_FRAME(frameMain), GTK_SHADOW_IN);
#ifdef debug
	gtk_frame_set_label (GTK_FRAME (frameMain), "frameMain");
#endif
	hboxMain = gtk_hbox_new(FALSE, 5);	/*FALSE means elements inside not same size*/
	gtk_container_add(GTK_CONTAINER(frameMain), hboxMain);
	
	/*** map and input boxes ***/
	/* left map box */
/*	vboxL = gtk_vbox_new(FALSE, 5);*/
/*	gtk_container_add(GTK_CONTAINER(frameMain), vboxL);*/
	
	frameL = gtk_frame_new(NULL);
/*	gtk_container_add(GTK_CONTAINER(frameL), vboxL);*/
	gtk_container_set_border_width(GTK_CONTAINER(frameL), 10);
#ifdef debug
	gtk_frame_set_label (GTK_FRAME (frameL), "frameL - Map");
#endif	
	gtk_widget_set_size_request(frameL, 800, 700);		/*set fixed size*/
	
	halignL = gtk_alignment_new(0, 0, 0, 0);		/*align map box to left*/
	gtk_container_add(GTK_CONTAINER(halignL), frameL);
	gtk_box_pack_start(GTK_BOX(hboxMain), halignL, TRUE, TRUE, 5);
	
	/* right input box */
	vboxR = gtk_vbox_new(FALSE, 5);
	halignR = gtk_alignment_new(1,0,0,0);
	frameR = gtk_frame_new(NULL);
	gtk_container_set_border_width(GTK_CONTAINER(frameR), 10);
#ifdef debug
	gtk_frame_set_label (GTK_FRAME (frameR), "frameR - Input");
#endif
	gtk_widget_set_size_request(frameR, 350, 700);		/*set fixed size*/
	gtk_container_add(GTK_CONTAINER(frameR), vboxR);
	gtk_container_add(GTK_CONTAINER(halignR), frameR);
	gtk_box_pack_start(GTK_BOX(hboxMain), halignR, TRUE, TRUE, 5);
	
	/* logo */
	valignLogo = gtk_alignment_new(0 ,0, 0, 0);
	gtk_container_add(GTK_CONTAINER(vboxR), valignLogo); 
	vboxLogo = gtk_vbox_new(FALSE, 5);
	gtk_widget_set_size_request(vboxLogo, 300, 250);		/*set fixed size*/
	gtk_container_add(GTK_CONTAINER(valignLogo), vboxLogo);
	GtkWidget *dareaLogo = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER (vboxLogo), dareaLogo);
	
	g_signal_connect(dareaLogo, "expose_event", G_CALLBACK(DrawAreaExposedLogo), NULL); 
	
	
	/*** widgets inside input box ***/
	
	/* status */
	frameStatus = gtk_frame_new(NULL);
	
	gtk_widget_set_size_request(frameStatus, 350, 250);		/*set fixed size*/
	
	gtk_container_set_border_width(GTK_CONTAINER(frameStatus), 10);
#ifdef debug
	gtk_frame_set_label (GTK_FRAME (frameStatus), "frameStatus");
#endif
	valignStatus = gtk_alignment_new(0 ,0.6, 0, 0);
	gtk_container_add(GTK_CONTAINER(valignStatus), frameStatus);
	gtk_box_pack_start(GTK_BOX(vboxR), valignStatus, TRUE, TRUE, 5);
	
	/* status widgets */
	/*=============================insert server messages here==============================================*/
	labelFare = gtk_label_new("Estimated fare: ");
	GtkWidget *valignLabelFare = gtk_alignment_new(0.1, 0.2, 0,0);
	gtk_container_add(GTK_CONTAINER(valignLabelFare), labelFare);
	gtk_container_add(GTK_CONTAINER(frameStatus), valignLabelFare);
	
	/* text entry  - adapted from https://developer.gnome.org/gtk-tutorial/stable/x939.html */
	frameEntry = gtk_frame_new(NULL);
	#ifdef frame_size
	gtk_widget_set_size_request(frameEntry, 350, 200);		/*set fixed size*/
	#endif
	gtk_container_set_border_width(GTK_CONTAINER(frameEntry), 10);
#ifdef debug
	gtk_frame_set_label (GTK_FRAME (frameEntry), "frameEntry");
#endif
	valignEntry = gtk_alignment_new(0, 0.9, 0, 0);
	vboxEntry = gtk_vbox_new(FALSE, 10);
	gtk_container_add(GTK_CONTAINER(frameEntry), vboxEntry);
	gtk_container_add(GTK_CONTAINER(valignEntry), frameEntry);
	
	gtk_box_pack_start(GTK_BOX(vboxR), valignEntry, TRUE, TRUE, 10);
	
	/*entry struct*/
	entry *entries = malloc(sizeof(entry));
   	if(!entries)
	 {
	  perror("\nOut of memory\n");
	  exit(30);
	 }
	
	/* pickup entry */
	vboxPickup = gtk_vbox_new (FALSE, 0);
    	gtk_container_add (GTK_CONTAINER (vboxEntry), vboxPickup);
    	valignPick = gtk_alignment_new(0,0,0,0);
   
    	GtkWidget *entryPick = gtk_entry_new();
    	entries->entryPick = entryPick;
  	
    	gtk_widget_set_size_request(entries->entryPick, 300, 30);
    	gtk_container_add (GTK_CONTAINER (valignPick), entries->entryPick);
    	gtk_entry_set_max_length(GTK_ENTRY(entries->entryPick), 50);
    	g_signal_connect(entries->entryPick, "activate", G_CALLBACK(enter_callback), entries->entryPick);
    	gtk_entry_set_text(GTK_ENTRY(entries->entryPick), "Enter pickup address");
/*    	tempPos = GTK_ENTRY(entry->entryPick)->text_length;*/
/*    	gtk_editable_insert_text(GTK_EDITABLE(entryPick), "Enter Pickup Location", -1, &tempPos);*/
/*    	gtk_editable_select_region(GTK_EDITABLE(entryPick), 0, GTK_ENTRY(entryPick)->text_length);	highlight word when double clicked*/
    	
    	gtk_box_pack_start (GTK_BOX (vboxPickup), valignPick, TRUE, TRUE, 10);
    	
    	/* dropoff entry */
	vboxDropoff = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (vboxEntry), vboxDropoff);
	valignDrop = gtk_alignment_new(0,0.5,0,0);
    	
    	GtkWidget *entryDrop = gtk_entry_new();
    	entries->entryDrop = entryDrop;
    	
    	gtk_widget_set_size_request(entries->entryDrop, 300, 30);
    	gtk_container_add (GTK_CONTAINER (valignDrop), entries->entryDrop);
    	gtk_entry_set_max_length(GTK_ENTRY(entries->entryDrop), 50);
    	g_signal_connect(entries->entryDrop, "activate", G_CALLBACK(enter_callback), entries->entryDrop);
    	tempPos = GTK_ENTRY(entries->entryDrop)->text_length;
    	gtk_editable_insert_text(GTK_EDITABLE(entries->entryDrop), "Enter Dropoff Location", -1, &tempPos);
    	gtk_editable_select_region(GTK_EDITABLE(entries->entryDrop), 0, GTK_ENTRY(entries->entryDrop)->text_length);	/*highlight word when double clicked*/
    	
    	gtk_box_pack_start (GTK_BOX (vboxDropoff), valignDrop, TRUE, TRUE, 10);	
	
	/* buttons */
	valignBtn = gtk_alignment_new(0,1,0,0);	
	halignButtons = gtk_alignment_new(0.5,0,0,0);
	hboxBtn = gtk_hbox_new(TRUE,15);				/*TRUE means all buttons in box same size*/
	gtk_widget_set_size_request(hboxBtn, 250, 70);
	gtk_container_set_border_width(GTK_CONTAINER(hboxBtn), 10);
	reqBtn = gtk_button_new_with_label("Request");
	gtk_widget_set_size_request(reqBtn, 70,30);		/*sets minimum size of widget*/
	gtk_container_add(GTK_CONTAINER(hboxBtn), reqBtn);
	cnlBtn = gtk_button_new_with_label("Cancel");
	gtk_container_add(GTK_CONTAINER(hboxBtn), cnlBtn);
	gtk_container_add(GTK_CONTAINER(valignBtn), hboxBtn);
	
	gtk_container_add(GTK_CONTAINER(halignButtons), valignBtn);
	gtk_box_pack_start(GTK_BOX(vboxR), halignButtons, TRUE, FALSE, 0);
	
	g_signal_connect(reqBtn, "clicked", G_CALLBACK(reqBtn_callback), entries);	/* activate when Request button clicked*/

	/*** Draw the map ***/
	DrawMap(frameL, vboxLogo);
	
	DrawTaxi(frameL, vboxLogo);
	
/*********************************************************************************/

	/*** show elements on window ***/	 						
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);	
	gtk_widget_show_all(window);
	
	g_object_unref(icon);		/*free icon memory*/

	gtk_main();					/*program waits for events to occur*/
	cairo_surface_destroy(logo.image);		/* destroy surface when quitting */
	return 0;

} /* end of main */

/*=======================================================================*/

/* Icon */
GdkPixbuf *create_pixbuf(const gchar * filename)
{
	GdkPixbuf *pixbuf;
	GError *error = NULL;
	pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	if (!pixbuf)
	{
		fprintf(stderr, "%s\n", error->message);
		g_error_free(error);
	}
	return pixbuf;
}

/* adapted from https://developer.gnome.org/gtk-tutorial/stable/x939.html */
static void enter_callback(GtkWidget *widget, GtkWidget *entry) 
{
	const gchar *entry_text;
	entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
	printf("Entry contents: %s\n", entry_text);
}

double getServerClock()
{
 clock_t serverClock = clock();
 double clockTimeF = serverClock;
 double clocksPerSec = CLOCKS_PER_SEC;
 return clockTimeF/clocksPerSec;

}

void reqBtn_callback(GtkWidget *reqBtn, gpointer user_data)
{
	/* signal callbacks for buttons */
	entry *entries = user_data;
	assert(entries);
	
	gchar *message;
	message = (gchar *)malloc(sizeof(gchar)*256);
	
	/* create string containing request data for server */
	const gchar *pickup = gtk_entry_get_text(GTK_ENTRY(entries->entryPick));
	const gchar *dropoff = gtk_entry_get_text(GTK_ENTRY(entries->entryDrop));

	strcpy(message, pickup);
/*	strcat(message, " to ");	*/
	strcat(message, dropoff);
	
	#ifdef debug
	printf("\nrequest message is %s \n", message);
	#endif
	
	/*send message to server*/
	Talk2Server("belle", message);
	
}
gboolean DrawAreaExposedLogo(GtkWidget *Widget, GdkEventExpose *Event, gpointer Data)
{
	GtkWidget *dareaLogo;
	gint Width, Height;
	cairo_t *crLogo;		/* cairo context for logo */
	dareaLogo = Widget;
	Width = dareaLogo->allocation.width;
	Height = dareaLogo->allocation.height;
	
	logo.image = cairo_image_surface_create_from_png("logo.png");
	
	crLogo = gdk_cairo_create(dareaLogo->window);
	/* set logo as source */
	
	cairo_set_source_surface(crLogo, logo.image, 0, 0);
  	cairo_paint(crLogo);  

    
	/* delete the cairo context and free memory */
	cairo_destroy(crLogo);
	return TRUE; /* area drawn, done with expose event */
} /* end of DrawAreaExposedLogo */


/* EOF GuberClient.c */
