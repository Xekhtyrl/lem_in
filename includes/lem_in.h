/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:13:10 by tlafay            #+#    #+#             */
/*   Updated: 2026/02/27 17:46:52 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft/headers/get_next_line.h"
# include "libft/headers/ft_printf.h"
# include "libft/headers/libft.h"

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
    int visited;
    int distance;
} t_room;

typedef struct s_farmlist {
    t_room* room;
    struct s_farmlist* next;
} t_farmlist;

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
t_room *get_room_by_name(t_graph *graph, char *name);
int create_link(t_room *a, t_room *b);
int	ft_atoi_ants(char *str, int *num);
int str_count_char(char *str, char c);

/************* connectivity.c */

int check_connectivity(t_graph *graph);

/************* bfs.c */
int bfs(t_graph* graph, t_room* start, t_room* end);


/************* list.c */
int add_end(t_farmlist** head,  t_room* room);
t_room* pop_front(t_farmlist** head);
void free_list(t_farmlist* head);

#endif