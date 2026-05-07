#include "lem_in.h"

static t_result* new_result(t_path* paths, int turns, int path_nbr){
	t_result* res = malloc(sizeof(t_result));
	if (!res)
		return NULL;
	res->paths = paths;
	res->turns = turns;
	res->path_nbr = path_nbr;
	res->next = NULL;
	return res;
}

t_result* add_result(t_result* head, t_path* paths, int turns, int path_nbr){
	t_result* new = new_result(paths, turns, path_nbr);
	t_result* temp;
	t_result* prev = NULL;

	if (!new)
	{
		free_result(head);
		return NULL;
	}
	if (!head)
		return new;

	temp = head;
	while (temp->next && temp->turns < turns) {
		prev = temp;
		temp = temp->next;
	}
	if (prev == NULL) {
		new->next = head;
		return new;
	}
	prev->next = new;
	new->next = temp;
	return head;
}

int count_turns(t_path* paths, int n_path, int ants){
	calculate_min_ants_for_path(paths, n_path);
	int turns = 0;
	int ants_left = ants;
	for (int i = 0; i < n_path; i++){
		if (paths[i].min_ants == 0)
			turns += paths[i].length;
	}
	while (ants_left > 0){
		for (int i = 0; i < n_path; i++){
			if (ants_left >= paths[i].min_ants)
				ants_left--;
		}
		turns++;
	}
	return turns;
}