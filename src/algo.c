#include "lem_in.h"

int get_path(t_path* path, int **mat, t_graph* graph, int curr, int**origin){
	if (curr == graph->end->index){
		path->length += 1;
		return 1;
	}
	
	for (int nxt = 0; nxt < graph->room_count; nxt++){
		if (mat[curr][nxt] == 0 && origin[curr][nxt] == 1){
			mat[curr][nxt] = 1;
			int flow = get_path(path, mat, graph, nxt, origin);
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

void get_paths(t_path* paths, int** mat, t_main* main, int *path_nbr, int** origin){
	t_graph *graph = &(main->graph);
	int npath = 0;
	for (int i = 0; i < graph->end->index + 1; i++){
		if (npath >= *path_nbr){
			if (mat[0][i] == 0 && origin[graph->start->index][i] == 1)
				ft_printf("Warning: More paths found than expected. Stopping search.\n");}
		else if (mat[0][i] == 0 && origin[graph->start->index][i] == 1){
			ft_printf("Found path(%i) to node %i\n", npath, i);
			mat[graph->start->index][i] = 1;
			get_path(&(paths[npath]), mat, graph, i, origin);
			add_end(&(paths[npath].path), graph->end);
			npath++;
		}
	}
	ft_printf("Total paths found: %i vs %i\n", npath, *path_nbr);
}

void calculate_min_ants_for_path(t_path* paths, int n_path){
	for (int i = 0; i < n_path; i++)
		for (int j = 0; j < n_path; j++)
			if (paths[i].length > paths[j].length)
				paths[i].min_ants += (paths[i].length - paths[j].length);
	for (int i = 0; i < n_path; i++)
		ft_printf("cost for path %i of length %i: %i\n", i, paths[i].length, paths[i].min_ants);
}

t_path* find_n_paths(t_main* main, int* path_nbr){
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
	int *dist = get_distances(&graph);
	if (!dist) {
		ft_printf("Error calculating distances\n");
		free_mat(mat, graph.room_count);
		free_mat(copy, graph.room_count);
		return NULL;
	}
	*path_nbr = dinic_max_flow(mat, 0, graph.end->index, dist);
	if (*path_nbr == -1) {
		ft_printf("Error during max flow calculation\n");
		free_mat(mat, graph.room_count);
		return NULL;
	}

	t_path* paths = calloc(sizeof(t_path), *path_nbr);
	get_paths(paths, mat, main, path_nbr, copy);
	free_mat(mat, graph.room_count);
	free_mat(copy, graph.room_count);
	free(dist);
	calculate_min_ants_for_path(paths, *path_nbr);
	return paths;
}

char* make_ant_str(int ants_index, char* room) {
	char *ant_name = ft_itoa(ants_index);
	char *strs[6] = {"L", ant_name, "-", room, " ", 0};
	char *final = NULL;
	int i = -1;
	while (strs[++i]) {
		final = ft_strjoin_f(final, strs[i], 1);
		if (!final)
			return NULL;
	}
	free(ant_name);
	return final;
}

int move_ants_in_path(t_farmlist* curr, char **str, int* end_total, t_path* path) {
	if (curr->occupant == -1 || curr->room->type == END)
		return 1;
	else
		if (!move_ants_in_path(curr->next, str, end_total, path))
			return 0;
	if (curr->occupant == 0)
		return 1;
	if (curr->next->room->type == END)
	{
		*end_total += 1;
		path->flow_in -= 1;
	}

	curr->next->occupant = curr->occupant;
	char *tmp = make_ant_str(curr->occupant, curr->next->room->name);
	curr->occupant = 0;
	*str = ft_strjoin_f(*str, tmp, 1);
	free(tmp);
	return 1;
}

void send_ants(t_main* main, t_path* paths, int path_nbr){
	int ants_index = 1;
	int end_total = 0;
	ft_printf("Sending ants...\n");
	while (end_total < main->ants){
		char *str = NULL;
		for (int i = 0; i < path_nbr; i++){
			if (!move_ants_in_path(paths[i].path, &str, &end_total, &paths[i]))
				return; // FREE EVERYTHING NEEDED
			if (main->ants - (ants_index - 1) > paths[i].min_ants){
				paths[i].path->occupant = ants_index;
				paths[i].flow_in += 1;
				char *ant_str = make_ant_str(ants_index, paths[i].path->room->name);
				ants_index++;
				if (!ant_str)
					return; // FREE EVERYTHING NEEDED
				str = ft_strjoin_f(str, ant_str, 1);
				if (!str)
					return; // FREE EVERYTHING NEEDED
				free(ant_str);
			}
		}
		if (str)
			ft_printf("%s\n", str);
		free(str);
	}
}

