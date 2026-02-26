/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:13:10 by tlafay            #+#    #+#             */
/*   Updated: 2022/05/10 14:29:47 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>

# include "get_next_line.h"

typedef enum e_room_type {
    START,
    END,
	SIMPLE
} t_room_type;

typedef struct s_room
{
    char *name;
    int x;
    int y;
	t_room_type type;
    struct s_room **links;
    int link_count;
} t_room;

typedef struct s_graph
{
    t_room **rooms;
    int room_count;
    t_room *start;
    t_room *end;
} t_graph;

typedef struct s_main
{
    t_graph graph;
    int ants;
} t_main;

/********    get_next_line.c    ********/

char		*get_next_line(int fd);

/********    libft.c    ********/

int	ft_atoi(char *str, int *num);
int			ft_strlen(char *str);
int			ft_free(void *str);
int			ft_error(char *str);
void		*ft_malloc(size_t x);
char	*ft_strdup(char *str);


/********    parsing.c    ********/

char		ft_mute_char(int fd, char muted, int type);
// int			ft_redirect_char(char a, int fd, t_map *map);
// int			ft_main_pars(int fd, t_map *map);
int	parsing(t_main *main);

/********    utils.c    ********/

int add_room_to_graph(t_main *main, t_room *room);
void *free_room(t_room *room);
void *free_graph(t_graph *graph);
int start_with(char *str, char *prefix);
void print_main(t_main *main);
int str_count_char(char *str, char c);


#endif