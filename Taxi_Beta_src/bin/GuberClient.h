#ifndef GUBERCLIENT_H_INCLUDED_
#define GUBERCLIENT_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include <assert.h>
#include "Reader.h"
#include "Taxi.h"
#include <cairo.h>
#include "Belle.h"


GdkPixbuf *create_pixbuf(const gchar * filename);

void FatalError(const char *ErrorMsg);

char *Talk2Server(const char *Message,char *RecvBuf);

void GetResponseFromServer(GtkWidget *Widget, gpointer Data);

void ShutdownServer(GtkWidget *Widget, gpointer Data);

int main(int argc,char *argv[]);

double getServerClock();

void DrawMap(GtkWidget *FrameL, GtkWidget *vboxLogo);

void DrawTaxi(GtkWidget *FrameL, GtkWidget *vboxLogo);

gboolean DrawAreaExposed(GtkWidget *Widget, GdkEventExpose *Event, gpointer Data);
gboolean DrawAreaExposedLogo(GtkWidget *Widget, GdkEventExpose *Event, gpointer Data);

gboolean DrawTaxiExposed(GtkWidget *Widget, GdkEventExpose *Event, gpointer Data);

typedef struct Entry {
    GtkWidget *entryPick;
    GtkWidget *entryDrop;
}entry;

/*for taxi image */
struct {
  cairo_surface_t *image;
} glob;

struct {
  cairo_surface_t *image;  
} logo;

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
GtkWidget *dareaLogo;
GtkWidget *valignLogo;
GtkWidget *vboxLogo;

cairo_t *crLogo;


#endif
