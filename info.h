#ifndef INFO__H
#define INFO__H
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "bez_drawing.h"
#include "listeners.h"




typedef struct Edited 
{
	int progress;
	BezSpot spot;
	gboolean align;
}Edited;

typedef struct Info
{
	Listeners listeners;
	
	ToolId selected_tool;
	
	BezDrawing *drawing;
	Edited edited;
	gint show_controls;
}Info;

void info_init_default	 (Info * info);
void info_select_tool	 (Info * info, ToolId tool_id );
void info_edited_init_null		(Info * info);
void info_edited_set_spot_null	(Info * info);
void info_edited_set_progress	(Info * info, int progress);
void info_edited_set_align	(Info * info, gboolean align);
void info_edited_move_spot_control	(Info * info, Point q);
void info_edited_move_spot_curve	(Info * info, Point q);

void info_edited_add_control		(Info * info, Point pointer);
void info_edited_add_curve_first_control	(Info * info, double x, double y);
void info_edited_add_curve_last_control		(Info * info, double x, double y);

#endif



