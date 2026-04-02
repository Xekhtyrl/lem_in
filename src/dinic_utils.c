#include "lem_in.h"

void fill_matrix(t_room* start, int** mat, int** copy){
	t_farmlist* head = NULL;
	add_end(&head, start);
	while(head){
		t_room* curr = pop_front(&head);
		for (int i = 0; i < curr->link_count; i++){
			if (mat[curr->index][curr->links[i]->index] != 1){
				mat[curr->index][curr->links[i]->index] = 1;
				copy[curr->index][curr->links[i]->index] = 1;
				add_end(&head, curr->links[i]);
			}
		}
	}
	free_list(head);
}

int **nodes_to_matrix(t_graph* graph, int*** copy){
	int **mat = malloc(sizeof(int*) * (graph->room_count + 1));
	*copy = malloc(sizeof(int*) * (graph->room_count + 1));
	mat[graph->room_count] = NULL;
	(*copy)[graph->room_count] = NULL;
	if (!mat || !(*copy))
		return NULL;
	for (int i = 0; i < graph->room_count; i++) {
		mat[i] = ft_calloc(graph->room_count, sizeof(int));
		(*copy)[i] = ft_calloc(graph->room_count, sizeof(int));
		if (!mat[i] || !(*copy)[i]) {
			free_mat(mat, i);
			free_mat(*copy, i);
			return NULL;
		}
	}
	fill_matrix(graph->start, mat, *copy);
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

int *get_distances(t_graph* graph) {
	int *distances = malloc(sizeof(int) * graph->room_count);
	if (!distances)
		return NULL;
	for (int i = 0; i < graph->room_count; i++) {
		distances[graph->rooms[i]->index] = graph->rooms[i]->distance;
	}
	return distances;
}