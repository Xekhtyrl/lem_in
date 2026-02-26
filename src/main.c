#include "lem_in.h"

void init_main(t_main *main)
{
    main->graph.rooms = NULL;
    main->graph.room_count = 0;
    main->graph.start = NULL;
    main->graph.end = NULL;
    main->ants = 0;
}

int	main()
{
    t_main main;
    init_main(&main);

    if (!parsing(&main)){
        printf("Parsing failed\n");
        free_graph(&main.graph);
        return 0;
    }
    print_main(&main);
    free_graph(&main.graph);
    return 0;
}