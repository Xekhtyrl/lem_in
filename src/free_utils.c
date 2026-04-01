#include "lem_in.h"

void free_mat(int **mat, int size) {
	int i = -1;
	while(++i < size){
		free(mat[i]);
		mat[i] = NULL;
	}
	free(mat);
}

void free_paths(t_path* paths, int n_path){
	for (int i = 0; i < n_path; i++)
		free_list(paths[i].path);
	free(paths);
}