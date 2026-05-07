#include "lem_in.h"

static int get_path(t_path* path, int **mat, t_graph* graph, int curr, int**origin){
	if (curr == graph->end->index){
		path->length += 1;
		return 1;
	}
	
	for (int nxt = 0; nxt < graph->room_count; nxt++){
		if (mat[curr][nxt] == 0 && origin[curr][nxt] == 1){
			mat[curr][nxt] = 1;
			int flow = get_path(path, mat, graph, nxt, origin);
			mat[curr][nxt] = 0;
			if (flow == 1)
			{
				add_front(&(path->path), get_room_by_index(graph, curr));
				path->length += 1;
				return 1;
			}
		}
	}
	return 0;
}

void get_paths(t_path* paths, int** mat, t_main* main, int path_nbr, int** origin){
	t_graph *graph = &(main->graph);
	int npath = 0;
	for (int i = 0; i < graph->end->index + 1; i++){
		if (npath >= path_nbr){
			if (mat[0][i] == 0 && origin[graph->start->index][i] == 1)
				ft_printf("Warning: More paths found than expected. Stopping search.\n");}
		else if (mat[0][i] == 0 && origin[graph->start->index][i] == 1){
			mat[graph->start->index][i] = 1;
			get_path(&(paths[npath]), mat, graph, i, origin);
			mat[graph->start->index][i] = 0;
			add_end(&(paths[npath].path), graph->end);
			npath++;
		}
	}
}

void calculate_min_ants_for_path(t_path* paths, int n_path){
	for (int i = 0; i < n_path; i++)
		for (int j = 0; j < n_path; j++)
			if (paths[i].length > paths[j].length)
				paths[i].min_ants += (paths[i].length - paths[j].length);
}

t_result* find_n_paths(t_main* main){
	t_graph graph = main->graph;
	int **copy = NULL;
	int **mat = nodes_to_matrix(&graph, &copy);

	if (!mat || !copy) {
		ft_printf("Error creating adjacency matrix\n");
		if (mat)
			free_mat(mat, graph.room_count);
		if (copy)
			free_mat(copy, graph.room_count);
		return NULL;
	}
	if (!mat) {
		ft_printf("Memory allocation failed\n");
		return NULL;
	}
	t_result* res = dinic_max_flow(mat, 0, graph.end->index, main, copy);
	if (!res) {
		ft_printf("Error during max flow calculation\n");
		free_mat(mat, graph.room_count);
		free_mat(copy, graph.room_count);
		free_result(res);
		return NULL;
	}
	free_mat(mat, graph.room_count);
	free_mat(copy, graph.room_count);

	return res;
}