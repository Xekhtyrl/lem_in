#include "lem_in.h"

int add_room_to_graph(t_main *main, t_room *room)
{
	t_graph *graph = &main->graph;
	t_room **new_rooms = malloc(sizeof(t_room *) * (graph->room_count + 1));
	if (!new_rooms) {
		ft_printf("Memory allocation failed while adding room '%s'\n", room->name);
		return (0);
	}
    for (int i = 0; i < graph->room_count; i++) {
        new_rooms[i] = graph->rooms[i];
    }
    new_rooms[graph->room_count] = room;
    // if (graph->rooms)
        free(graph->rooms);
	graph->rooms = new_rooms;
	graph->room_count++;
	return (1);
}

t_room *get_room_by_name(t_graph *graph, char *name)
{
	char *trimName = ft_strtrim(name, "\n\t\v");
    for (int i = 0; i < graph->room_count; i++)
    {
        if (ft_strcmp(graph->rooms[i]->name, trimName) == 0)
            return (free(trimName), graph->rooms[i]);
    }
    return (free(trimName), NULL);
}

t_room* get_room_by_index(t_graph* graph, int index){
	for (int i = 0; i < graph->room_count; i++)
    {
		if (graph->rooms[i]->index == index)
			return graph->rooms[i];
	}
	return NULL;
}

int create_link(t_room *a, t_room *b)
{
    t_room **new_links_a = malloc(sizeof(t_room *) * (a->link_count + 1));
    t_room **new_links_b = malloc(sizeof(t_room *) * (b->link_count + 1));
    if (!new_links_a || !new_links_b) {
        free(new_links_a);
        free(new_links_b);
        return (0);
    }
    for (int i = 0; i < a->link_count; i++) {
        new_links_a[i] = a->links[i];
    }
    for (int i = 0; i < b->link_count; i++) {
        new_links_b[i] = b->links[i];
    }
    new_links_a[a->link_count] = b;
    new_links_b[b->link_count] = a;
    free(a->links);
    free(b->links);
    a->links = new_links_a;
    b->links = new_links_b;
    a->link_count++;
    b->link_count++;
    return (1);
}

int start_with(char *str, char *prefix)
{
    while (*prefix) {
        if (*prefix != *str)
            return (0);
        prefix++;
        str++;
    }
    return (1);
}


int	ft_atoi_ants(char *str, int *num)
{
	int sign = 1;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	if (*str > '9' || *str < '0')
		return (0);
	*num = *str - '0';
	while (1)
	{
		str++;
		if (*str < '0' || *str > '9') {
			*num *= sign;
			return (1);
		}
		*num *= 10;
		*num += (*str - '0');
		if (*num > 10000000)
			return (0);
	}
}

int str_count_char(char *str, char c)
{
	int count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return count;
}

int min(int a, int b){
	return a * (a <= b) + b * (b < a);
}