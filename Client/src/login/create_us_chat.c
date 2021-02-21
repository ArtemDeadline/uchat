#include "client.h"



static t_user_base *add_element_start(t_user_base *head,t_uchat_bases * widgets){
        t_user_base *tmp = g_slice_new(t_user_base);
        tmp->image = widgets->us_data->user_but->user_info[2];
        tmp->messages = NULL;
        tmp->user_contact = g_slice_new(t_users_in_chat);
        tmp->user_contact->image = widgets->us_data->user_but->user_info[2];
        tmp->user_contact->name = widgets->us_data->user_but->user_info[3];
        tmp->user_contact->next = NULL;
        tmp->bases = gtk_grid_new();
        tmp->type = 0;
        tmp->next = head;

        gtk_widget_set_name(tmp->bases,gtk_widget_get_name(widgets->us_data->user_but->user_info[0]));
        gtk_widget_set_valign(tmp->bases, GTK_ALIGN_END);
        gtk_stack_add_named(GTK_STACK(widgets->stack_1), tmp->bases, gtk_widget_get_name(widgets->us_data->user_but->user_info[0]));
    
        return(tmp);
}






void create_us_chat(t_uchat_bases * widgets){
    
    if(widgets->us_data->user_ch == NULL){
        widgets->us_data->user_ch = g_slice_new(t_user_base);
        widgets->us_data->user_ch->image = widgets->us_data->user_but->user_info[2];
        widgets->us_data->user_ch->messages = NULL;
        widgets->us_data->user_ch->user_contact = g_slice_new(t_users_in_chat);
        widgets->us_data->user_ch->user_contact->image = widgets->us_data->user_but->user_info[2];
        widgets->us_data->user_ch->user_contact->name = widgets->us_data->user_but->user_info[3];
        widgets->us_data->user_ch->user_contact->next = NULL;
        widgets->us_data->user_ch->bases = gtk_grid_new();
        widgets->us_data->user_ch->type = 0;
        widgets->us_data->user_ch->next = NULL;

        gtk_widget_set_name(widgets->us_data->user_ch->bases,gtk_widget_get_name(widgets->us_data->user_but->user_info[0]));
        gtk_widget_set_valign(widgets->us_data->user_ch->bases, GTK_ALIGN_END);
        gtk_stack_add_named(GTK_STACK(widgets->stack_1), widgets->us_data->user_ch->bases, gtk_widget_get_name(widgets->us_data->user_but->user_info[0]));
    }else{
        widgets->us_data->user_ch = add_element_start(widgets->us_data->user_ch, widgets);
    }

}
