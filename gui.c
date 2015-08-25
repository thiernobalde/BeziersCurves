#include "gui.h"
static gchar *tool_labels[]={
	"Add curve" ,"Duplicate curve", "Move curve" , "Remove curve",
	"Add control" , "Move control" , "Remove control","Close curve","Color curve ","Fill curve"
	};
static gchar texte1[]={"Ceci est un editeur de courbes de bezier:\n"
					"-Pour creer une courbe:	selectionner Add curve: "
					"un clic gauche de la souris pour ajouter un controleur"
					" (en maintenant et deplaçant on regle la disposition du controleur)," 
					" un clic droit de la souris pour terminer et fermer la courbe,"
					" un clic milieu de la souris pour terminer sans fermer la courbe.\n\n"
					"-Pour deplacer une courbe: selectionner Move curve:"
					" faire un clic sur un point de controle de la courbe"	};
static gchar texte2[]={  " maintenir enfoncé et deplacer.\n\n"
					"-Pour supprimer une courbe:	selectionner Remove curve"
					" et un clic sur un point de control de la courbe à supprimer.\n\n"
					"-Pour ajouter un controleur:	selectionner Add control,"
					" faire un clic sur un point de control d'un  controleur de la courbe"
					" pour ajouter un controleur juste avant.\n\n"
					"-Pour déplacer/modifier un controleur:	selectionner Move control,ensuite"
					" nous avons trois cas : soit faire un clic sur le point de"};
					
					
static gchar texte3[]={	" controle du controleur par le quel"
					" passe la courbe pour deplacer tout le controleur,"
					" soit faire un clic gauche sur l'un des deux autres points de controle ( "
					"les deux composantes du controleur sont modifiés en mode couplé),"
					" et pour un clic droit chaque composant est modifié seul.\n\n"
					 "-Pour supprimer un controleur:selectionner Remove control"
					" et un clic sur un point de control du controleur à supprimer"
					" (la supression du dernier controleur de la courbe conduit à sa suppression)\n\n" };
					
static gchar texte4[]={ 	"En fin nous pouvons ,avec duplicate reproduire une courbe(plus haute)"
					" en faisant un clic sur un de ses points de controle,"
					" avec color curve et fill curve colorié (respectivement remplir) la courbe en"
					" la sélectionnant et ensuite en choisissant la couleur avec le boutton de couleur,"
					" fermer ou ouvrir une courbe avec Close curve,faire apparaitre ou non les controleurs avec show controls,"
					" Ouvrir ,sauver ou quitter un fichier avec Fichier->(load,save ou quit).\n\n"};
void on_tool_msg_tool_changed(Listener *l)
{
	Gui *g=l->data;
	ToolId k=g->info->selected_tool;
	GtkToggleButton *button=GTK_TOGGLE_BUTTON(g->tool[k]);
	
	gboolean is_active=gtk_toggle_button_get_active(button);
	if(is_active) return;
	gtk_toggle_button_set_active(button,TRUE);
}

void on_tool_toggled(GtkToggleButton *toggle, gpointer  data)
{
	Gui *g=data;
	Info *info=g->info;
	gint value=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(toggle), TOOL_KEY));
 
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(g->tool[value]))==TRUE)
	info_select_tool(info,value);

}

void on_check_button_toggled(GtkToggleButton *button, gpointer data)
{
	Gui *g=data;
	Info *info=g->info;
	info->show_controls=!(gtk_toggle_button_get_active (button));
	listeners_notify(&info->listeners, "aspect-changed");
}
	
void on_color_button_color_set(GtkColorButton *button, gpointer data)
{
	
	Gui *g=data;
	Info *info=g->info;
	BezSpot *s=&info->edited.spot;
	 GdkColor color;
	if(s->curve!=NULL)
	{
	 	
		gtk_color_button_get_color(button,&color);
		
		if((info->selected_tool==8)&&(info->edited.progress==TRUE))
		{
		
			s->curve->is_stroked=TRUE;
			
			s->curve->stroke_color=rgb_from_color(&color);
			info_edited_set_spot_null	(info);
			info_edited_set_progress(info,FALSE);
		}
		else if((info->selected_tool==9)&&(info->edited.progress==TRUE))
		{
		
			s->curve->is_filled=TRUE;
			s->curve->fill_color=rgb_from_color(&color);
			info_edited_set_spot_null	(info);
			info_edited_set_progress(info,FALSE);
		}
		
		listeners_notify(&info->listeners, "aspect-changed");
	}	

}

void gui_init_tool(Gui *g)
{
	Layout *l= &g->layout;
	Info *info= g->info;
	ToolId k;
	GtkRadioButton * prec= NULL;
	GtkWidget *pSeparator = NULL,*p2Separator=NULL;
	for(k=0;k<NB_TOOLS;k++)
	{
		g->tool[k]= gtk_radio_button_new_with_label_from_widget (prec, tool_labels[k]);
		if(info->selected_tool==k)gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(g->tool[k]),TRUE);
		g_object_set_data(G_OBJECT(g->tool[k]), TOOL_KEY, GINT_TO_POINTER(k));
		ON_SIGNAL (g->tool[k], 	"toggled", on_tool_toggled, g);
		
		gtk_box_pack_start (GTK_BOX (l->tool_box), g->tool[k], FALSE,FALSE , 0);
		prec= GTK_RADIO_BUTTON (g->tool[k]);
	}
	pSeparator = gtk_hseparator_new();
    	gtk_box_pack_start(GTK_BOX(l->tool_box), pSeparator, FALSE, FALSE, 0);
	g->color_button=gtk_color_button_new_with_color(static_color_from_rgb(0x00FF00));
	gtk_box_pack_start(GTK_BOX(l->tool_box),g->color_button,!EXPAND,!FILL,5);
	ON_SIGNAL (g->color_button,"color_set",on_color_button_color_set,g);
	p2Separator = gtk_hseparator_new();
    	gtk_box_pack_start(GTK_BOX(l->tool_box), p2Separator, FALSE, FALSE, 5);
	
	g->check_button=gtk_check_button_new_with_label("Show controls");
	gtk_box_pack_start(GTK_BOX(l->tool_box),g->check_button,!EXPAND,!FILL,5);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(g->check_button),TRUE);
	ON_SIGNAL (g->check_button,"toggled",on_check_button_toggled,g);
	
	listeners_add(&g->info->listeners,g->tool,"tool-changed",on_tool_msg_tool_changed,g);
	
}

void on_utilisation(GtkMenuItem U *item,gpointer  data)
{
    GtkWidget *dialog;
    Gui *g=data;

    
  	dialog = gtk_message_dialog_new (GTK_WINDOW(g->window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "	%s%s%s%s\n",texte1,texte2,texte3,texte4);
        
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
void on_about_project(GtkMenuItem U *item,gpointer  data)
{
    GtkWidget *dialog;
    Gui *g=data;

    dialog = gtk_message_dialog_new (GTK_WINDOW(g->window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "		Interfaces Graphiques\n"
        "Professeurs chargés des cours:\n"
        "Mrs THIELL Edouard et BARBANCHON Regis\n"
        "Projet: Editeur de courbes de beziers\n"
        "proposé par Mr BARBANCHON Regis\n"
        "Réalisé par BALDÉ Thierno (L2 Maths-Info)\n");

    
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
void changer_titre(Gui U *g,gchar *titre)
{
	const gchar* tittle=titre;
	gtk_window_set_title(GTK_WINDOW(g->window),tittle);
}
void on_loadsave_item_activate(GtkMenuItem *item,gpointer  data)
{
	Gui *g=data;
    Info *info=g->info;
    BezFileError B;
    GtkWidget *pFileSelection;
    gchar *sChemin;
    gchar titre[LINE_SIZE];
    
    const gchar* charger={"load"};
     const gchar* sauver={"save"};

    pFileSelection = gtk_file_chooser_dialog_new("Fichiers...",
	GTK_WINDOW(g->window),
	GTK_FILE_CHOOSER_ACTION_OPEN,
	GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	GTK_STOCK_OPEN, GTK_RESPONSE_OK,
	NULL);
    /* On limite les actions a cette fenetre */
    gtk_window_set_modal(GTK_WINDOW(pFileSelection), TRUE);

   
    switch(gtk_dialog_run(GTK_DIALOG(pFileSelection)))
    {
        case GTK_RESPONSE_OK:
           
            sChemin = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pFileSelection));
           
            if(strcmp(gtk_menu_item_get_label(item),sauver)==0)
            {
            	B= bez_drawing_save	(info->drawing,sChemin);
           	
            }
            if(strcmp(gtk_menu_item_get_label(item),charger)==0)
            {
            	if(info->drawing->curves->len!=0) 
            	{
            		bez_drawing_destroy	(info->drawing);
            		info->drawing=bez_drawing_new();
            	}
            	titre[0]='\0';
            	strcat(titre,"editeur de courbes de bezier:(");
            	strcat(titre,sChemin);
            	strcat(titre,")");
            	changer_titre(g,titre);
            	B=bez_drawing_load	(info->drawing,sChemin);
            	listeners_notify(&info->listeners, "aspect-changed");
            }
	    g_free(sChemin);
            break;
        default:
            break;
    }
    gtk_widget_destroy(pFileSelection);
}
void on_quit_item_activate(GtkMenuItem U *item,gpointer  data)
{
	Gui *g=data;
	
	BezDrawing   *d =g->info->drawing;
	bez_drawing_destroy	( d);
	listeners_remove	(&g->info->listeners,g->area);
	listeners_remove	(&g->info->listeners,g->statusbar);
	gtk_main_quit ();
}

void gui_init_help_menu(Gui *g)
{
	
	Menu *m= &g->menu;
	
	m->help_menu=gtk_menu_new();
	
	m->about_item=gtk_menu_item_new_with_label("A propos");
	m->use_item=gtk_menu_item_new_with_label("Utilisation");
	
	
	gtk_menu_shell_append(GTK_MENU_SHELL(m->help_menu),m->about_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(m->help_menu),m->use_item);
	
	ON_SIGNAL(m->about_item,"activate",on_about_project,g);
	ON_SIGNAL(m->use_item,"activate",on_utilisation,g);
	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(m->help_item),m->help_menu);
	
	
}

void gui_init_file_menu(Gui *g)
{
	
	Menu *m= &g->menu;
	
	m->file_menu=gtk_menu_new();
	
	m->load_item=gtk_menu_item_new_with_label("load");
	m->save_item=gtk_menu_item_new_with_label("save");
	m->quit_item=gtk_menu_item_new_with_label("quit");
	
	gtk_menu_shell_append(GTK_MENU_SHELL(m->file_menu),m->load_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(m->file_menu),m->save_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(m->file_menu),m->quit_item);
	
	ON_SIGNAL(m->quit_item,"activate",on_quit_item_activate,g);
	ON_SIGNAL(m->load_item,"activate",on_loadsave_item_activate,g);
	ON_SIGNAL(m->save_item,"activate",on_loadsave_item_activate,g);
	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(m->file_item),m->file_menu);
	
	
}

	
void gui_init_menu_bar(Gui *g)
{
	Layout *l= &g->layout;
	Menu *m= &g->menu;
	
	l->menu_frame=frame_new(NULL,FALSE);
	
	m->bar=gtk_menu_bar_new();
	gtk_container_add (GTK_CONTAINER (l->menu_frame), m->bar);
	
	m->help_item=gtk_menu_item_new_with_label("Aide");
	m->file_item=gtk_menu_item_new_with_label("Fichier");
	
	gui_init_file_menu(g);
	gui_init_help_menu(g);
	
	gtk_menu_shell_append(GTK_MENU_SHELL(m->bar),m->file_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(m->bar),m->help_item);
		
	gtk_box_pack_start (GTK_BOX (l->main_box), l->menu_frame, !EXPAND, !FILL, 0);

}

void gui_init_central(Gui *g)
{
	Layout *l = &g->layout;
	
	l->central_box  = gtk_hbox_new (!HOMOGENEOUS, 0);
	gtk_box_pack_start (GTK_BOX (l->main_box), l->central_box, EXPAND, FILL, 0);
	
	l->tool_frame=gtk_frame_new("tool_frame");
	gtk_box_pack_start (GTK_BOX (l->central_box), l->tool_frame, !EXPAND, !FILL, 0);
	
	l->tool_box=gtk_vbox_new (!HOMOGENEOUS, 0);
	gtk_container_add (GTK_CONTAINER (l->tool_frame),l->tool_box);
	
	l->area_frame=gtk_frame_new("area_frame");
	gtk_box_pack_start (GTK_BOX (l->central_box), l->area_frame, EXPAND, FILL, 0);
}
void on_status_bar_msg_tool_changed(Listener * listener)
{
	char text[LINE_SIZE];
	Gui *g=listener->data;
	sprintf(text, "tool '%s' selected...",
		tool_labels[g->info->selected_tool]);
	statusbar_put(GTK_STATUSBAR(g->statusbar),text);

}

void gui_init_statusbar (Gui *g)
{
    	Layout *l = &g->layout;
	
	l->status_frame=frame_new(NULL,FALSE);
	
    	g->statusbar = gtk_statusbar_new ();
     statusbar_put (GTK_STATUSBAR (g->statusbar), "Welcome !");
  	gtk_container_add (GTK_CONTAINER (l->status_frame), g->statusbar);
	gtk_box_pack_start (GTK_BOX (l->main_box), l->status_frame, !EXPAND, !FILL, 0);
	listeners_add(&g->info->listeners,g->statusbar,"tool-changed",on_status_bar_msg_tool_changed,g);
}
    
void gui_init_window(Gui *g)
{      
	g->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
     gtk_window_set_default_size(GTK_WINDOW(g->window),1100,900);
     
	gtk_window_set_title(GTK_WINDOW(g->window),"editeur de courbes de bezier:(nouveau fichier)");
     gtk_container_set_border_width (GTK_CONTAINER (g->window), 0);
    	ON_SIGNAL (g->window, "destroy",on_quit_item_activate, g);
}
void gui_init_layout (Gui *g)
{
 	Layout *l = &g->layout;
	
 	l->main_box = gtk_vbox_new (!HOMOGENEOUS, 0);
	gtk_container_add (GTK_CONTAINER (g->window), l->main_box);

	gui_init_menu_bar(g);
	gui_init_central(g);
	gui_init_area	(g);
	gui_init_tool(g);
	gui_init_statusbar (g);
	
	
    
}

void gui_init(Gui *gui,Info *info)
{
	gui->info=info;
	gui_init_window(gui);
	gui_init_layout(gui);
	
	
}

