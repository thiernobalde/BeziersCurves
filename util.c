#include "util.h"




void color_set_rgb (GdkColor *color, guint rgb)
{
    color->red   = (rgb & 0xFF0000) >> 8;
    color->green = (rgb & 0x00FF00)     ;
    color->blue  = (rgb & 0x0000FF) << 8;
}

void gc_set_rgb_fg (GdkGC *gc, guint rgb)
{
    gdk_gc_set_rgb_fg_color (gc, static_color_from_rgb (rgb));
}

GdkColor *static_color_from_rgb (guint rgb)
{
    static GdkColor color;
    color_set_rgb (&color, rgb);
    return &color;
}

guint rgb_from_color (GdkColor *color)
{
    return (color->red   & 0xFF00) << 8 |
           (color->green & 0xFF00)      |
           (color->blue  & 0xFF00) >> 8 ;
}

void statusbar_put(GtkStatusbar *bar, gchar text[])
{
	gtk_statusbar_pop(bar,0);
	gtk_statusbar_push(bar,0,text);
}

GtkWidget * frame_new(gchar label[], gboolean is_shadowed)
{
	GtkWidget *frame= gtk_frame_new(label);
	GtkShadowType type=is_shadowed ? GTK_SHADOW_ETCHED_IN : GTK_SHADOW_NONE;
	gtk_frame_set_shadow_type(GTK_FRAME(frame),type);
	return frame;
}
