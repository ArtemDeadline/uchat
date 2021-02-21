#include "client.h"




static void load_css(void){
    GtkCssProvider * provider;
    GdkDisplay * display;
    GdkScreen * screen;

    const gchar *css_style_file  = "Resources/css/login.css";
    GFile *css_fp = g_file_new_for_path(css_style_file);
 
    GError *error = 0;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_file(provider, css_fp, &error);

    g_object_unref(provider);
}

static void add_icod_to_entry(GtkEntry * entry, char * file_path,gboolean status){
    GdkPixbuf *    pixbuf;
    GError *error = 0;
    pixbuf = gdk_pixbuf_new_from_file (file_path,&error);
    gtk_entry_set_icon_from_pixbuf (entry,GTK_ENTRY_ICON_SECONDARY,pixbuf);
    if(!status){
        gtk_entry_set_visibility (entry,TRUE);
    }
    else{
        gtk_entry_set_visibility (entry,FALSE);
    }
}

void test_1(GtkAdjustment *adjustment,t_uchat_bases * widgets){
    gtk_adjustment_set_value (adjustment, gtk_adjustment_get_upper(adjustment) );
}

void push_clicked(GtkButton * button, t_uchat_bases * widgets){
    client->who_push = 1;
    g_print("PROBLEMI %d\n",widgets->who_push);
    add_message(widgets,3,(char *)gtk_entry_get_text(GTK_ENTRY(widgets->chat_entry)),0);
}


void user_toggled(GtkToggleButton * togglebutton, gpointer user_data ){
    t_uchat_bases * widgets = user_data ;
    if(widgets->last_user_button == NULL){
        widgets->last_user_button = GTK_WIDGET(togglebutton);
    }else{
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widgets->last_user_button),FALSE);
        widgets->last_user_button = GTK_WIDGET(togglebutton);
    }
    gtk_stack_set_visible_child_name (GTK_STACK(widgets->stack_1), gtk_widget_get_name(GTK_WIDGET(togglebutton)));
    g_print(" id_chat == %s\n",gtk_widget_get_name(GTK_WIDGET(togglebutton)));
    widgets->active_grid = gtk_stack_get_child_by_name (GTK_STACK(widgets->stack_1), gtk_widget_get_name(GTK_WIDGET(togglebutton)));
    gtk_widget_show(widgets->chat_entry);
    gtk_widget_show(widgets->chat_infos);
}

void add_clicked(GtkButton * button, t_uchat_bases * widgets){
    //create_user_button(&(widgets->us_data->user_but));
    g_signal_connect(widgets->us_data->user_but->user_info[0],"toggled",G_CALLBACK(user_toggled),widgets);
    gtk_grid_attach(GTK_GRID(widgets->grid_user_online),widgets->us_data->user_but->user_info[0],0, widgets->grid_v,1,1);
    //
    /*widgets->us_data->user_ch = g_slice_new(t_user_base);
    widgets->us_data->user_ch->image = widgets->us_data->user_but->user_info[2];
    widgets->us_data->user_ch->messages = g_slice_new(t_user_message);
    widgets->us_data->user_ch->messages->next = NULL;
    widgets->us_data->user_ch->user_contact = g_slice_new(t_users_in_chat);
    widgets->us_data->user_ch->bases = gtk_grid_new();
    widgets->us_data->user_ch->another_message = gtk_grid_new();
    widgets->us_data->user_ch->our_message = gtk_grid_new();
    widgets->us_data->user_ch->type = 0;
    gtk_widget_set_valign(widgets->us_data->user_ch->bases, GTK_ALIGN_END);
    gtk_widget_set_size_request(widgets->us_data->user_ch->another_message,500,0);
    gtk_widget_set_size_request(widgets->us_data->user_ch->our_message,500,0);
    gtk_grid_attach(GTK_GRID(widgets->us_data->user_ch->bases),widgets->us_data->user_ch->another_message,0,0,1,1);
    gtk_grid_attach(GTK_GRID(widgets->us_data->user_ch->bases),widgets->us_data->user_ch->our_message,1,0,1,1);
    gtk_stack_add_named(GTK_STACK(widgets->stack_1), widgets->us_data->user_ch->bases, gtk_widget_get_name(widgets->us_data->user_but->user_info[0]));*/
    create_us_chat(widgets);
    gtk_widget_show(widgets->us_data->user_ch->bases);
    
}


static void initilizate_widget(t_uchat_bases **widgets,GtkBuilder *builders);

void uchat_base(){
    gtk_init(NULL,NULL);
    load_css();
    GtkBuilder *builders;
    GtkWidget *uchat_win;
    client->status = 0;
    widgets = g_slice_new(t_uchat_bases);
    builders = gtk_builder_new_from_file("Resources/glade/static_chat.glade");
    uchat_win = GTK_WIDGET(gtk_builder_get_object(builders, "uchat_win"));
    initilizate_widget(&widgets,builders);
    gtk_builder_connect_signals(builders, widgets);
    gtk_widget_show(uchat_win);
    gtk_main();
}

static void initilizate_widget(t_uchat_bases **widgets,GtkBuilder *builders){
    (*widgets)->stack_1 = GTK_WIDGET(gtk_builder_get_object(builders, "stack_1"));
    (*widgets)->chat_entry = GTK_WIDGET(gtk_builder_get_object(builders, "chat_entry"));
    (*widgets)->image_user = GTK_WIDGET(gtk_builder_get_object(builders, "image_user"));
    (*widgets)->image_lupa = GTK_WIDGET(gtk_builder_get_object(builders, "image_lupa"));
    (*widgets)->grid_user_online = GTK_WIDGET(gtk_builder_get_object(builders, "grid_user_online"));
    (*widgets)->grid_user_offline = GTK_WIDGET(gtk_builder_get_object(builders, "grid_user_offline"));
    (*widgets)->add_ = GTK_WIDGET(gtk_builder_get_object(builders, "add_"));
    (*widgets)->push = GTK_WIDGET(gtk_builder_get_object(builders, "push"));
    (*widgets)->adj = GTK_ADJUSTMENT(gtk_builder_get_object(builders, "adjustment1"));
    (*widgets)->chat_infos = GTK_WIDGET(gtk_builder_get_object(builders, "chat_infos"));
    (*widgets)->us_data = g_slice_new(t_user_data);
    (*widgets)->last_user_button = NULL;
    (*widgets)->us_data->user_but = NULL;
    (*widgets)->us_data->user_ch = NULL;
    (*widgets)->active_grid = NULL;
    (*widgets)->grid_v = 0;
    (*widgets)->user_names =  GTK_WIDGET(gtk_builder_get_object(builders, "user_names"));
    if(g_strcmp0("No image", client->current_user->image) == 0){
        gtk_image_set_from_file(GTK_IMAGE((*widgets)->image_user),"Resources/images/us_128.png");
    }else{
        GdkPixbuf *    pixbuf;
        GError *error = 0;
        pixbuf = gdk_pixbuf_new_from_file_at_scale (client->current_user->image,128,128,FALSE,&error);
        gtk_image_set_from_pixbuf (GTK_IMAGE((*widgets)->image_user),pixbuf);
    }
    char * text = mx_strjoin(client->current_user->name," ");
    gtk_label_set_text(GTK_LABEL((*widgets)->user_names),mx_strjoin(text,client->current_user->lastname));
    gtk_stack_set_homogeneous (GTK_STACK((*widgets)->stack_1),FALSE);
    for(int i = 0; client->chats[i] != NULL; i++){
        create_user_button(&((*widgets)->us_data->user_but),i);
        g_signal_connect((*widgets)->us_data->user_but->user_info[0],"toggled",G_CALLBACK(user_toggled),(*widgets));
        gtk_grid_attach(GTK_GRID((*widgets)->grid_user_online),(*widgets)->us_data->user_but->user_info[0],0, (*widgets)->grid_v,1,1);
        (*widgets)->grid_v += 1 ;
        //g_print("CREATE grid\n");
        create_us_chat((*widgets));
        gtk_widget_show((*widgets)->us_data->user_ch->bases);
        //g_print("CREATE zapros\n");
        get_chat_info(client->socketfd, client->chats[i]->id,client->current_user->id);
        //g_print("CREATE error ?\n");
        while(client->status == 0){
            g_print("client status == %d\n",client->status);
        }
        client->status = 0;
        g_print("CREATE Noerror ?\n");
        (*widgets)->active_grid = gtk_stack_get_child_by_name (GTK_STACK((*widgets)->stack_1), gtk_widget_get_name(GTK_WIDGET((*widgets)->us_data->user_but->user_info[0])));
        g_print("CREATE add in grid ?\n");
        g_print("ACTIVE GRID %s\n ",gtk_widget_get_name(GTK_WIDGET((*widgets)->us_data->user_but->user_info[0])) );
        g_print("test1 == %d\n",client->chats[i]->id); 
        for(int j = 0; client->chats[i]->messages[j] != NULL; j++){
            //g_print("text == %s\n",client->chats[i]->messages[j]->text); 
            //g_print("message %s, user %d\n",client->chats[i]->messages[j]->text,client->chats[i]->messages[j]->sender->id );
            add_message((*widgets),client->current_user->id == client->chats[i]->messages[j]->sender->id ? 1 : 2,client->chats[i]->messages[j]->text,0);
        }
    }
    print_all_users(client);
    /*for(int i = 0 ; client->chats[i] != NULL ;i++){
        for(int j = 0; client->chats[i]->messages[j] != NULL; j++){
            add_message((*widgets),client->current_user->id == client->chats[i]->messages[j]->sender->id ? 1 : 2,client->chats[i]->messages[j]->text);
        }
    }*/
    
    
}



