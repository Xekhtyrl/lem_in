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
        ft_printf("Parsing failed\n");
        free_graph(&main.graph);
        return 1;
    }

    if (!check_connectivity(&main.graph)) {
        free_graph(&main.graph);
        return 1;
    }
	int path_nbr = 0;
	t_path* paths = find_n_paths(&main, &path_nbr);
	if (!paths){
		free_graph(&main.graph);
		return 1;
	}

	send_ants(&main, paths, path_nbr);
	free_paths(paths, path_nbr);
    // print_main(&main);

    free_graph(&main.graph);
    return 0;
}