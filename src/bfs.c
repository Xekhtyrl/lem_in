#include "lem_in.h"

void reset_graph(t_graph* graph) {
    for (int i = 0; i < graph->room_count; i++) {
        graph->rooms[i]->distance = -1;
        graph->rooms[i]->visited = 0;
    }
}

int bfs(t_graph* graph, t_room* start, t_room* end) {
    t_farmlist* head = NULL;

    reset_graph(graph);

    add_end(&head, start);
    start->visited = 1;
    start->distance = 0;

    while (head) {
        t_room* current_room = pop_front(&head);

        if (current_room == end) {
            int result = current_room->distance;
            free_list(head);
            return result;
        }

        for (int i = 0; i < current_room->link_count; i++) {
            t_room* neighbor = current_room->links[i];

            if (!neighbor->visited) {
                neighbor->visited = 1;
                neighbor->distance = current_room->distance + 1;
                add_end(&head, neighbor);
            }
        }
    }

    free_list(head);
    return -1;
}