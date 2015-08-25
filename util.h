#ifndef __UTIL__
#define __UTIL__

#include <gtk/gtk.h>
#include <cairo.h>
#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "bez_enum.h"


#define ON_SIGNAL(w,n,c,d) \
    (g_signal_connect(G_OBJECT(w), (n), G_CALLBACK(c), (d) ))



void color_set_rgb (GdkColor *color, guint rgb);
void gc_set_rgb_fg (GdkGC *gc, guint rgb);

GdkColor *static_color_from_rgb (guint rgb);
guint rgb_from_color (GdkColor *color);
void statusbar_put(GtkStatusbar *bar, gchar text[]);
GtkWidget * frame_new(gchar label[], gboolean is_shadowed);


#endif
