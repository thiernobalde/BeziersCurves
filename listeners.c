#include "listeners.h"


Listener * listener_new(gpointer from,gchar const message[],
			 gpointer to,OnMessage on_message, gpointer data)
{
	Listener *l=g_new(Listener,1);
	
	l->from=from;
	l->message=message;
	l->to=to;
	l->on_message=on_message;
	l->data=data;
	return l;
}

void listeners_init(Listeners *ls, gpointer from)
{
	
	ls->list=NULL;
	ls->from=from;
}

void listeners_add(Listeners *ls,gpointer to, gchar const message[],OnMessage on_message, gpointer data)
{
	Listener *l;
	
	l=listener_new(ls->from,message, to, on_message, data);
	
	ls->list=g_list_append(ls->list,l);

}

void listeners_notify	(Listeners *ls,gchar const message[])
{
	
	GList *crt;
	for(crt=ls->list;crt;crt=crt->next)
	{
		Listener *l=crt->data;

		if(strcmp(l->message,message)==0)
			l->on_message(l);
	}
	
}
	
void listeners_remove	(Listeners *ls,gpointer to)
{
	GList *crt,*next;
	if(ls==NULL)return;
	for(crt=ls->list;crt;crt=next)
	{
		Listener *l=crt->data;
		next=crt->next;
		if(l->to==to)
		{
			g_free(l);
			ls->list=g_list_delete_link(ls->list,crt);
		}
	}

}

