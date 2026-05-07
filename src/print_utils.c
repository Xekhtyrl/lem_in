#include "lem_in.h"

void print_mat(int** mat, int max_y){
	for (int i = 0; i < max_y; i++){
		ft_printf("[");
		for (int j = 0; j < max_y; j++){
			ft_printf("%i ", mat[i][j]);
		}
		ft_printf("]\n");
	}
}

void print_paths(t_path* paths, int path_nbr){

	for (int i = 0; i < path_nbr; i++){
		ft_printf("Path %i (length %i):\n", i, paths[i].length);
		t_farmlist* temp = paths[i].path;
		while (temp){
			ft_printf("%s, ", temp->room->name);
			temp = temp->next;
		}
		ft_printf("\n");
	}
}

void print_level(int*level, int size){
	ft_printf("Levels:\n");
	for (int i = 0; i < size; i++)
		ft_printf("%i ", level[i]);
	ft_printf("\n");
}

void print_main(t_main *main)
{
    ft_printf("Ants: %d\n", main->ants);
    print_graph(main->graph);
}

void print_graph(t_graph graph)
{
    ft_printf("Graph has %d rooms:\n", graph.room_count);
    for (int i = 0; i < graph.room_count; i++)
    {
        t_room *room = graph.rooms[i];
        char *type_str = (room->type == START) ? "START" : (room->type == END) ? "END" : "SIMPLE";
        ft_printf("Room %d: %s (%d, %d) Type: %s Index: %i Links: %d Visited: %i, Distance: %i\nLinked to:\n", i, room->name, room->x, room->y, type_str, room->index, room->link_count, room->flow, room->distance);
		for (int j = 0; j < room->link_count;j++) {
			ft_printf("Room: %s, ", room->links[j]->name);
		}
		ft_printf("\n");
    }
}