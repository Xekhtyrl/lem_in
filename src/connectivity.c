#include "lem_in.h"

int check_connectivity(t_graph *graph)
{
    for (int i = 0; i < graph->room_count; i++) {
        if (graph->rooms[i]->type == START) {
            graph->start = graph->rooms[i];
        }
        else if (graph->rooms[i]->type == END) {
            graph->end = graph->rooms[i];
        }
    }

    if (!graph->start) {
        ft_printf("Error: Start room is not defined.\n");
        return 0;
    }
    if (!graph->end) {
        ft_printf("Error: End room is not defined.\n");
        return 0;
    }

    int result = bfs(graph, graph->start, graph->end, true);
    if (result == 0) {
        ft_printf("Error: No path exists between start and end rooms.\n");
        return 0;
    }

    ft_printf("a way was found, with %d nodes. \n", result);

    return result;
}