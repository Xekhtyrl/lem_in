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

void print_graph(t_graph *graph)
{
    ft_printf("Graph has %d rooms:\n", graph->room_count);
    for (int i = 0; i < graph->room_count; i++)
    {
        t_room *room = graph->rooms[i];
        char *type_str = (room->type == START) ? "START" : (room->type == END) ? "END" : "SIMPLE";
        ft_printf("Room %d: %s (%d, %d) Type: %s Links: %d\n", i, room->name, room->x, room->y, type_str, room->link_count);
    }
}

t_room *get_room_by_name(t_graph *graph, char *name)
{
    for (int i = 0; i < graph->room_count; i++)
    {
        if (ft_strcmp(graph->rooms[i]->name, name) == 0)
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

void print_main(t_main *main)
{
    ft_printf("Ants: %d\n", main->ants);
    print_graph(&main->graph);
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