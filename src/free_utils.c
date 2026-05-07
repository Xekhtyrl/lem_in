#include "lem_in.h"

void *free_room(t_room *room)
{
    if (room)
    {
        if (room->name)
            free(room->name);
        if (room->links)
            free(room->links);
        free(room);
    }
    return (NULL);
}

void *free_graph(t_graph *graph)
{
    if (graph)
    {
        for (int i = 0; i < graph->room_count; i++)
        {
            free_room(graph->rooms[i]);
        }
        if (graph->rooms)
            free(graph->rooms);
    }
    return (NULL);
}

void free_mat(int **mat, int size) {
	int i = -1;
	while(++i < size){
		free(mat[i]);
		mat[i] = NULL;
	}
	free(mat);
}

void free_paths(t_path* paths, int n_path){
	for (int i = 0; i < n_path; i++){
		free_list(paths[i].path);
	}
	free(paths);
}

void free_result(t_result* res) {
	t_result* temp;
	while (res) {
		temp = res->next;
		free_paths(res->paths, res->path_nbr);
		free(res);
		res = temp;
	}
}