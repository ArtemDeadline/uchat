#include"../inc/server.h"

void send_response_to_client(t_list_of_clients *list, int *users, int len_array_users, char *response) {
    while(list) {
        //printf("YES\n");
        for(int i = 0; i < len_array_users; i++) {
            //printf("client\n");
            if(list->client.user_id == users[i])  {
                //printf("response\n");
                send(list->client.socket, response, strlen(response), 0);
                break;
            }
        }
        list = list->next;
    }
}
