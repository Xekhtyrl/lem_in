#include "lem_in.h"

int add_end(t_farmlist** head,  t_room* room) {
    t_farmlist* new_node = malloc(sizeof(t_farmlist));
    if (!new_node)
        return 0;
    new_node->room = room;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        t_farmlist * tail = *head;
        while (tail->next != NULL)
        {
            tail = tail->next;
        }
        tail->next = new_node;
    }
    return 1;
}

t_room* pop_front(t_farmlist** head) {
    if (*head == NULL) {
        return NULL;
    }

    t_farmlist* temp = *head;
    t_room* room = temp->room;
    *head = (*head)->next;

    free(temp);
    return room;
}

void free_list(t_farmlist* head) {
    while (head != NULL) {
        t_farmlist* temp = head;
        head = head->next;
        free(temp);
    }
}