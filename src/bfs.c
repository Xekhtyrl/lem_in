#include "lem_in.h"

void reset_graph(t_graph* graph, bool set_flow) {
	for (int i = 0; i < graph->room_count; i++) {
		graph->rooms[i]->distance = -1;
		if (set_flow)
			graph->rooms[i]->flow = 1;
	}
}

int bfs(t_graph* graph, t_room* start, t_room* end, bool first_setup) {
    t_farmlist* head = NULL;

    reset_graph(graph, first_setup);

    add_end(&head, start);
    start->distance = 0;

    while (head) {
        t_room* current_room = pop_front(&head);

        if (current_room == end && first_setup) {
            int result = current_room->distance;
			free_list(head);
			return result;
        }

        for (int i = 0; i < current_room->link_count; i++) {
            t_room* neighbor = current_room->links[i];

			if (neighbor->distance == -1 && neighbor->flow > 0) {
				neighbor->distance = current_room->distance + 1;
				add_end(&head, neighbor);
			}
        }
    }

	free_list(head);
	return end->distance != -1;
}
