#ifndef LISTENER__H
#define LISTENER__H
#include "util.h"

typedef struct Listener Listener;
typedef void (* OnMessage) (Listener* listener);
struct Listener
{
	OnMessage on_message;
	gchar  const * message;
	gpointer from,to,data;
};
typedef struct Listeners
{
	GList*list;
	gpointer from;
}Listeners;
Listener * listener_new(gpointer from,gchar const message[],
			 gpointer to,OnMessage on_message, gpointer data);
void listeners_init(Listeners *ls, gpointer from);

void listeners_notify	(Listeners *ls,gchar const message[]);
void listeners_remove	(Listeners *ls,gpointer to);
#endif
