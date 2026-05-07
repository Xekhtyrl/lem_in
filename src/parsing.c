#include "lem_in.h"

typedef enum e_parsing_state {
	ANTS,
	ROOMS,
	LINKS
} t_parsing_state;

static int parse_ants_line(char *line, t_main *main, int line_count)
{
	int ants = 0;
	if (!ft_atoi_ants(line, &ants)) {
		if (ants > 10000000) {
			ft_printf("Too many ants at line %d\n", line_count);
			return (0);
		}
		if (ants == 0) {
			ft_printf("Zero ants at line %d\n", line_count);
			return (0);
		}
		if (ants < 0) {
			ft_printf("Negative ants at line %d\n", line_count);
			return (0);
		}
		ft_printf("Invalid ants number at line %d\n", line_count);
		return (0);
	}
	main->ants = ants;
	return (1);
}

static int parse_room_line(char *line, t_main *main, int line_count, t_room_type *type)
{
	if (start_with(line, "##start")) {
		*type = START;
		return (1);
	}
	else if (start_with(line, "##end")) {
		*type = END;
		return (1);
	}
	else if (line[0] == '#') {
		return (1);
	}


	int i = 0;
	if (line[0] == ' ' || line[0] == 'L') {
		ft_printf("Room name cannot start with a space or 'L' at line %d\n", line_count);
		return (0);
	}
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i] != ' ') {
		ft_printf("Invalid room format at line %d\n", line_count);
		return (0);
	}
	line[i] = '\0';
	i += 1;
	char *name = ft_strdup(line);
	if (!name) {
		ft_printf("Memory allocation failed at line %d\n", line_count);
		return (0);
	}
	int x, y;
	if (!ft_atoi_ants(line + i, &x)) {
		ft_printf("Invalid X coordinate at line %d\n", line_count);
		// free(line);
		// line = NULL;
		free(name);
		return (0);
	}
	while (line[i] && line[i] != ' ')
		i++;
	if (!line[i]) {
		ft_printf("Missing Y coordinate at line %d\n", line_count);
		free(name);
		return (0);
	}
	i += 1;
	if (!ft_atoi_ants(line + i, &y)) {
		ft_printf("Invalid Y coordinate at line %d\n", line_count);
		free(name);
		return (0);
	}

	t_room *room = malloc(sizeof(t_room));
	if (!room) {
		ft_printf("Memory allocation failed at line %d\n", line_count);
		free(name);
		return (0);
	}

	room->name = ft_strtrim(name, "\n\t\v");
	free(name);
	room->x = x;
	room->y = y;
	room->type = *type;
	room->link_count = 0;
	room->index = -1;
	room->links = NULL;
	*type = SIMPLE;

	if (!add_room_to_graph(main, room)) {
		ft_printf("Failed to add room '%s' to graph at line %d\n", room->name, line_count);
		free_room(room);
		return (0);
	}

	return (1);
}

static int parse_link_line(char *line, t_main *main, int line_count)
{
	if (line[0] == '#') {
		return (1);
	}

	for (int i = 0; line[i]; i++) {
		if (line[i] == '-') {
			line[i] = '\0';
			char *first_name = line;
			char *second_name = line + i + 1;
			if (!first_name[0] || !second_name[0]) {
				ft_printf("Invalid link format at line %d\n", line_count);
				return (0);
			}
			if (ft_strcmp(first_name, second_name) == 0) {
				ft_printf("Link to the same element at line %d\n", line_count);
				return (0);
			}
			t_room *first_room = get_room_by_name(&main->graph, first_name);
			t_room *second_room = get_room_by_name(&main->graph, second_name);
			if (!first_room || !second_room) {
				ft_printf("Link references unknown room at line %d\n", line_count);
				return (0);
			}
			if (!create_link(first_room, second_room)) {
				ft_printf("Failed to create link between '%s' and '%s' at line %d\n", first_name, second_name, line_count);
				return (0);
			}


			return (1);
		}
	}
	ft_printf("Invalid link format (caracter '-' not found) at line %d\n", line_count);
	return (0);
}

static int error_parsing(char *line) {
	if (line)
		free(line);
	get_next_line(0, 1);
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
		line = get_next_line(0, 0);
		if (!line || line[0] == '\n' || line[0] == '\0')
			break;

		switch (state)
		{
			case ANTS:
				if (!parse_ants_line(line, main, line_count))
					return error_parsing(line);
				state = ROOMS;
				break;
			case ROOMS:
				if (str_count_char(line, '-'))
				{
					state = LINKS;
					if (!parse_link_line(line, main, line_count))
					return error_parsing(line);
				}
				else {
					if (!parse_room_line(line, main, line_count, &room_type))
					return error_parsing(line);
				}
				break;
			case LINKS:
				if (!parse_link_line(line, main, line_count))
					return error_parsing(line);
				break;
		}
		
		free(line);
		line_count++;
	}
	if (!line)
		return (1);
	free(line);
	return (1);
}
