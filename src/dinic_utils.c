#include "lem_in.h"

void fill_matrix(t_room* start, t_room* end, int** mat, t_graph* graph){
	t_farmlist* head = NULL;
	// bfs(graph, start, end, MATRIX);
	// print_graph(*graph);
	(void)end;
	(void)graph;
	add_end(&head, start);
	while(head){
		t_room* curr = pop_front(&head);
		// if (curr == end)
		// 	continue;
		for (int i = 0; i < curr->link_count; i++){
			if (mat[curr->index][curr->links[i]->index] != 1){
				mat[curr->index][curr->links[i]->index] = 1;
				// curr->links[i]->distance = -1;
				add_end(&head, curr->links[i]);
			}
			// else{
			// 	ft_printf("Not adding room %s to queue\n", curr->links[i]->name);
			// 	ft_printf("Distance: %i, curr distance: %i\n", curr->links[i]->distance, curr->distance);
			// 	ft_printf("Condition 1: %i\n", mat[curr->links[i]->indeneighborx][curr->index] != 1);
			// 	ft_printf("Condition 2: %i\n", curr->links[i]->distance <= curr->distance);
			// 	ft_printf("Matrix value: %i\n", mat[curr->links[i]->index][curr->index]);
			// }
		}
	}
	free_list(head);
}

int **nodes_to_matrix(t_graph* graph){
	int **mat = malloc(sizeof(int*) * (graph->room_count + 1));
	mat[graph->room_count] = NULL;
	if (!mat)
		return NULL;
	for (int i = 0; i < graph->room_count; i++) {
		mat[i] = ft_calloc(graph->room_count, sizeof(int));
		if (!mat[i]) {
			free_mat(mat, i);
			return NULL;
		}
		//protect malloc
	}
	fill_matrix(graph->start, graph->end, mat, graph);
	free(mat[graph->end->index]);
	mat[graph->end->index] = ft_calloc(sizeof(int), graph->room_count);
	return mat;
}

int path_cost_overload(int **costs, int new_cost, int new_size, int ants) {
	int total = 0;
	int* new_tab = ft_calloc(sizeof(int), new_size);
	if (!new_tab)
		return 0;
	for (int i = 0; i < new_size - 1; i++){
		if ((*costs)[i] < new_cost)
			total += (new_cost - (*costs)[i]);
		new_tab[i] = (*costs)[i];
	}
	new_tab[new_size - 1] = new_cost;
	if (new_size > 1)
		free(*costs);
	*costs = new_tab;
	return total > ants;
	
}