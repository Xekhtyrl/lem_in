#include "lem_in.h"

static char* make_ant_str(int ants_index, char* room) {
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

static int move_ants_in_path(t_farmlist* curr, char **str, int* end_total, t_path* path) {
	if (curr->occupant == -1 || curr->room->type == END)
	{
		if (curr->occupant != -1 && curr->room->type == END)
		{
			*end_total += 1;
			path->flow_in -= 1;
		}
		return 1;
	}
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
	while (end_total < main->ants){
		char *str = NULL;
		for (int i = 0; i < path_nbr; i++){
			if (!move_ants_in_path(paths[i].path, &str, &end_total, &paths[i]))
			{
				if (str)
					free(str);
				return ;
			}
			if (main->ants - (ants_index) >= paths[i].min_ants){
				paths[i].path->occupant = ants_index;
				paths[i].flow_in += 1;
				char *ant_str = make_ant_str(ants_index, paths[i].path->room->name);
				if (!ant_str)
				{
					if (str)
						free(str);
					return;
				}
				ants_index++;
				if (!ant_str)
				{
					if (str)
						free(str);
					return;
				}
				str = ft_strjoin_f(str, ant_str, 1);
				free(ant_str);
				if (!str)
					return;
			}
		}
		if (str)
			ft_printf("%s\n", str);
		free(str);
	}
}

