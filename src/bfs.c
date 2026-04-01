#include "lem_in.h"

void reset_graph(t_graph* graph, int use_setup) {
	for (int i = 0; i < graph->room_count; i++) {
		graph->rooms[i]->distance = -1;
		graph->rooms[i]->visited = 0;
		if (use_setup == INIT)
			graph->rooms[i]->flow = 1;
	}
}

int bfs(t_graph* graph, t_room* start, t_room* end, int use_setup) {
    t_farmlist* head = NULL;

    reset_graph(graph, use_setup);

    add_end(&head, start);
    start->distance = 0;

    while (head) {
        t_room* current_room = pop_front(&head);
		current_room->visited = 1;
        if (current_room == end && use_setup == INIT) {
            int result = current_room->distance;
			free_list(head);
			return result;
        }

        for (int i = 0; i < current_room->link_count; i++) {
            t_room* neighbor = current_room->links[i];
			bool use_condition;
			if (use_setup == INIT || use_setup == DINIC)
				use_condition = (neighbor->distance == -1 && neighbor->flow > 0);
			else
				use_condition = (neighbor->distance < current_room->distance + 1 && !neighbor->visited);
			if (use_condition) {
				neighbor->distance = current_room->distance + 1;
				add_end(&head, neighbor);
			}
        }
    }

	free_list(head);
	return end->distance != -1;
}

static void reset_level(int *level, int size){
	for(int i = 0; i < size; i++){
		level[i] = -1;
	}
}

int bfs_matrix(int **graph, int start, int end, int* level) {
	reset_level(level, end + 1);
	level[0] = 0;

	t_intlst* head = NULL;

	ft_dbl_lstadd_back((t_list**)&head, (t_list*)new_intlst(start));
	if (!head)
		return 0;
	while (head){
		t_intlst* curr = pop_frt(&head);
		for (int nxt = 0; nxt < end + 1; nxt++){
			if (graph[curr->val][nxt] > 0 && level[nxt] == -1){
				level[nxt] = level[curr->val] + 1;
				ft_dbl_lstadd_back((t_list**)&head, (t_list*)new_intlst(nxt));
			}
		}
		free(curr);
	}

	free_list((t_farmlist*)head);
	return level[end] != -1;
}