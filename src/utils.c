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
		printf("Memory allocation failed while adding room '%s'\n", room->name);
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
    printf("Graph has %d rooms:\n", graph->room_count);
    for (int i = 0; i < graph->room_count; i++)
    {
        t_room *room = graph->rooms[i];
        char *type_str = (room->type == START) ? "START" : (room->type == END) ? "END" : "SIMPLE";
        printf("Room %d: %s (%d, %d) Type: %s Links: %d\n", i, room->name, room->x, room->y, type_str, room->link_count);
    }
}

void print_main(t_main *main)
{
    printf("Ants: %d\n", main->ants);
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