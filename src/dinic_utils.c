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
