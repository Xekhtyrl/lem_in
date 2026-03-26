#include "lem_in.h"

typedef struct s_path {
	char **path;
	int length;
	struct s_path *next;
	struct s_path *prev;
} t_path;


int find_n_path(t_path	**paths, t_main main, int max_path){
	if (max_path > main.ants)
		max_path = main.ants;
}

void f(t_main main){
	t_path *paths;
	int n = find_n_path(&paths, main, main.graph.start->link_count);
}

