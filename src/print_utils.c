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