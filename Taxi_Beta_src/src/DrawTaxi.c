/*DrawTaxi module*/

#include "GuberClient.h"
#define debug


#ifdef refrence

typedef struct Taxi
{
 int passenger;
 int rideLength;
 double fare;
 double expense;
 int type;
 int taxiID;
 int location;
 int pickup;
 int destination;
}Taxi;

/*context for image surfae*/
struct {
  cairo_surface_t *image;  
} glob;

#endif

/*drawtaxi function*/
void DrawTaxi(GtkWidget *frameL, GtkWidget *vboxLogo) 
{
	assert(frameL);
	assert(vboxLogo);
	
	#ifdef debug
        printf("\n\ntesting drawtaxi\n\n");
        #endif
	
	DrawArea = gtk_drawing_area_new();
        gtk_container_add(GTK_CONTAINER(frameL), DrawArea);
		
	
	g_signal_connect(G_OBJECT(DrawArea), "expose_event",G_CALLBACK(DrawTaxiExposed), NULL);
	/*
  	g_signal_connect(DrawArea, "destroy",G_CALLBACK (gtk_main_quit), NULL);
	*/
}


/*drawing image cairo*/
gboolean DrawTaxiExposed(GtkWidget *Widget,GdkEventExpose *Event, gpointer Data)
{	
	GtkWidget *DrawArea;
	cairo_t *cr;
	
	DrawArea = Widget;
	cr = gdk_cairo_create(DrawArea->window);	
	glob.image = cairo_image_surface_create_from_png("/users/ugrad/2016/fall/jjpatel1/gtk/cairo/taxi_clipart.png");

        cairo_set_source_surface(cr, glob.image, 50,50);
        cairo_paint(cr);

	cairo_surface_destroy(glob.image);
	cairo_destroy(cr);
        return TRUE;	


}
