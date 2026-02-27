#include "lem_in.h"

int add_end(t_list** head,  t_room* room) {
    t_list* new_node = malloc(sizeof(t_list));
    if (!new_node)
        return 0;
    new_node->room = room;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        t_list * tail = *head;
        while (tail->next != NULL)
        {
            tail = tail->next;
        }
        tail->next = new_node;
    }
    return 1;
}

t_room* pop_front(t_list** head) {
    if (*head == NULL) {
        return NULL;
    }

    t_list* temp = *head;
    t_room* room = temp->room;
    *head = (*head)->next;

    free(temp);
    return room;
}

void free_list(t_list* head) {
    while (head != NULL) {
        t_list* temp = head;
        head = head->next;
        free(temp);
    }
}