/* DrawMap module */

#include "GuberClient.h"
/*#define debug*/

void DrawMap(GtkWidget *FrameL, GtkWidget *vboxLogo)
{
	assert(FrameL);
	assert(vboxLogo);
	#ifdef debug
	printf("\n\ntesting drawmap\n\n");
	#endif
	
	gtk_frame_set_label (GTK_FRAME (frameL), "City of New Irvine");
	gtk_frame_set_label_align(GTK_FRAME(frameL), 0.0, 0.0);
	/* Drawing area for map */
    	DrawArea = gtk_drawing_area_new();
    	gtk_container_add(GTK_CONTAINER(frameL), DrawArea);		
    	/* connect drawing area with function */
 	g_signal_connect(DrawArea, "expose_event", G_CALLBACK(DrawAreaExposed), NULL);

/*
	g_signal_connect(DrawArea, "destroy",G_CALLBACK (gtk_main_quit), NULL);
*/
}

/* cairo */
gboolean DrawAreaExposed(GtkWidget *Widget, GdkEventExpose *Event, gpointer Data)
{
	GtkWidget *DrawArea;
	gint Width, Height;
	cairo_t *cr;		/* cairo context for map */

	/*map struct*/
	Map mapstruct;
	mapstruct = Reader(mapstruct);
	 
	#ifdef debug
	printf("\n W-E streets: %s\n\n", mapstruct.y_names);
	printf("\n N-S streets: %s\n\n", mapstruct.x_names);
	printf("\n rows: %d\n", mapstruct.x);
	printf("\n col: %d\n\n", mapstruct.y);
	#endif
	 
	#ifdef DEBUG
	printf("%s: DrawAreaExposed callback starting...\n", Program);
	#endif
	DrawArea = Widget;
	Width = DrawArea->allocation.width;
	Height = DrawArea->allocation.height;
	#ifdef DEBUG
	printf("%s: Drawing area width=%d, height=%d.\n", Program, Width, Height);
	#endif
	/* prepare a cairo context for the drawing */
	cr = gdk_cairo_create(DrawArea->window);
	/* draw a white rectangular background */
	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_rectangle(cr, 0, 0, Width, Height);
	cairo_fill(cr);

	/*** draw streets lines ***/
	int map_border = Width/9;		/* border space to leave for street names */
	/** set line color and width **/
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 1);
	/** set text font and size **/
	cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 11);

	int num_col = mapstruct.x;
	int num_row = mapstruct.y;
	int i;
	int col_width;
	int col_height;
	
	char *line = NULL;
	
	/**************************************************************/
	/***  draw vertical streets ***/
	for (i = 0; i < num_col; i++)
	{
		col_width = ((i * (Width - (2 * map_border))/num_col) + (2 * map_border));
		cairo_move_to(cr, col_width, map_border);
		cairo_line_to(cr, col_width, (Height - map_border/4));	
	}
	/* draw first vertical street name*/
	line = strtok(mapstruct.x_names, ",");
	col_width = (2 * map_border); 
	/* display first text at angle */
	cairo_save(cr);
	cairo_move_to(cr, (col_width), (map_border - map_border/12));
	cairo_rotate(cr, 5.1);	/* temporarily rotate context */
	cairo_show_text(cr, line); 
	cairo_restore(cr);
	
	/* draw rest of names */
	int j = mapstruct.x;
	i = 1;
	while (j > 0)
	{
		col_width = ((i * (Width - (2 * map_border))/num_col) + (2 * map_border));
		/* display text at angle */
		cairo_save(cr);
		cairo_move_to(cr, (col_width), (map_border - map_border/12));
		cairo_rotate(cr, 5.1);	/* temporarily rotate context */
		line = strtok(NULL, ",");
		cairo_show_text(cr, line); 
		cairo_restore(cr);
		i++;
		j--;	
			
	}
	/******************************************************************/
	/* draw horizontal lines */
	cairo_text_extents_t extents;
	for (i = 0; i < num_row; i++)
	{
		col_height = ((i * ((Height - (map_border))/num_row)) + (map_border));
		cairo_move_to(cr, (2 * map_border), col_height);
		cairo_line_to(cr, (Width - map_border/4), col_height);	
	}
	/* draw first horizontal street name*/
	line = strtok(mapstruct.y_names, ",");
	col_height = map_border; 
	/* get text width */
	cairo_text_extents(cr, line, &extents);		/* store width of street name */
	int x_pos = (2 * map_border) - extents.width - map_border/6;
	/* draw names */
	cairo_move_to(cr, (x_pos), col_height);
	cairo_show_text(cr, line); 
	
	/* draw rest of names */
	int h = mapstruct.y;
	i = 1;
	while (h > 0)
	{
		col_height = ((i * ((Height - (map_border))/num_row)) + (map_border));
		/* get text width */
		line = strtok(NULL, ",");
		cairo_text_extents(cr, line, &extents);		/* store width of street name */
		int x_pos = (2 * map_border) - extents.width - map_border/6;
		cairo_move_to(cr, (x_pos), col_height);
		cairo_show_text(cr, line); 
		i++;
		h--;		
	}
	cairo_stroke(cr);	/* show the lines */
    
	glob.image = cairo_image_surface_create_from_png("/users/ugrad/2016/fall/jjpatel1/gtk/cairo/taxi_clipart.png");
	
	cairo_set_source_surface(cr, glob.image, 20,20);
        cairo_paint(cr);	
    

	/* delete the cairo context and free memory */
	cairo_destroy(cr);
	cairo_surface_destroy(glob.image);
	return TRUE; /* area drawn, done with expose event */
} /* end of DrawAreaExposed */


/* end of DrawMap.c */

/* EOF */



