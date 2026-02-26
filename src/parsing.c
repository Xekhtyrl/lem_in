#include "lem_in.h"

typedef enum e_parsing_state {
	ANTS,
	ROOMS,
	LINKS
} t_parsing_state;

int parse_ants_line(char *line, t_main *main, int line_count)
{
	int ants = 0;
	if (!ft_atoi(line, &ants)) {
		if (ants > 10000000) {
			printf("Too many ants at line %d\n", line_count);
			return (0);
		}
		if (ants == 0) {
			printf("Zero ants at line %d\n", line_count);
			return (0);
		}
		if (ants < 0) {
			printf("Negative ants at line %d\n", line_count);
			return (0);
		}
		printf("Invalid ants number at line %d\n", line_count);
		return (0);
	}
	main->ants = ants;
	return (1);
}

int parse_room_line(char *line, t_main *main, int line_count, t_room_type *type)
{
	if (start_with(line, "##start")) {
		*type = START;
		return (1);
	}
	else if (start_with(line, "##end")) {
		*type = END;
		return (1);
	}


	int i = 0;
	if (line[0] == ' ' || line[0] == 'L') {
		printf("Room name cannot start with a space or 'L' at line %d\n", line_count);
		return (0);
	}
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i] != ' ') {
		printf("Invalid room format at line %d\n", line_count);
		return (0);
	}
	line[i] = '\0';
	i += 1;
	char *name = ft_strdup(line);
	if (!name) {
		printf("Memory allocation failed at line %d\n", line_count);
		return (0);
	}
	int x, y;
	if (!ft_atoi(line + i, &x)) {
		printf("Invalid X coordinate at line %d\n", line_count);
		// free(line);
		// line = NULL;
		free(name);
		return (0);
	}
	while (line[i] && line[i] != ' ')
		i++;
	if (!line[i]) {
		printf("Missing Y coordinate at line %d\n", line_count);
		free(name);
		return (0);
	}
	i += 1;
	if (!ft_atoi(line + i, &y)) {
		printf("Invalid Y coordinate at line %d\n", line_count);
		free(name);
		return (0);
	}

	t_room *room = malloc(sizeof(t_room));
	if (!room) {
		printf("Memory allocation failed at line %d\n", line_count);
		free(name);
		return (0);
	}

	room->name = name;
	room->x = x;
	room->y = y;
	room->type = *type;
	room->link_count = 0;
	room->links = NULL;
	*type = SIMPLE;

	if (!add_room_to_graph(main, room)) {
		printf("Failed to add room '%s' to graph at line %d\n", name, line_count);
		free_room(room);
		return (0);
	}

	return (1);
}

int parse_link_line(char *line, t_main *main, int line_count)
{
	(void)line_count; // Currently unused, but can be used for error reporting
	(void)main; // Currently unused, but will be needed to access the graph
	(void)line; // Currently unused, but will be needed to parse the link
	// Implement link line parsing logic here
	// You would need to extract the two room names and create a link between them
	return (0);
}

int	parsing(t_main *main)
{
	char* line = NULL;
	t_parsing_state state = ANTS;
	t_room_type room_type = SIMPLE;
	int line_count = 1;
	while (1)
	{
		line = get_next_line(0);
		if (!line || line[0] == '\n' || line[0] == '\0')
			break;

		switch (state)
		{
			case ANTS:
				if (!parse_ants_line(line, main, line_count)) {
					free(line);
					line = NULL;
					return (0);
				}
				state = ROOMS;
				break;
			case ROOMS:
				if (str_count_char(line, '-'))
				{
					state = LINKS;
					if (!parse_link_line(line, main, line_count))
					{						
						free(line);
						return (0);
					}
				}
				else {
					if (!parse_room_line(line, main, line_count, &room_type)) {
						free(line);
						line = NULL;
						return (0);
					}
				}
				break;
			case LINKS:
				if (!parse_link_line(line, main, line_count)) {
					free(line);
					return (0);
				}
				break;
		}

		free(line);
		line_count++;
	}
	if (!line)
		return (0);
	free(line);
	return (1);
}
