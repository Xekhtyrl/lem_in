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

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/headers/get_next_line.h"
# include "libft/headers/ft_printf.h"
# include "libft/headers/libft.h"
# include <stdbool.h>

typedef enum e_room_type {
	START,
	END,
	SIMPLE
} t_room_type;

typedef struct s_room
{
	char *name;
	int index;
	int x;
	int y;
	t_room_type type;
	struct s_room **links;
	int link_count;
	int flow;
	int distance;
	int visited;
} t_room;

typedef struct s_farmlist {
    struct s_farmlist* next;
    t_room* room;
	int occupant;
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

typedef struct s_int_list
{
	struct s_int_list *next;
	struct s_int_list *prev;
	int val;
} t_intlst;


typedef struct s_path {
	t_farmlist*	path;
	int length;
	int min_ants;
	int flow_in;
} t_path;

typedef struct s_result {
	struct s_result* next;
	t_path* paths;
	int path_nbr;
	int turns;
} t_result;

/********    parsing.c    ********/

int	parsing(t_main *main);

/********    utils.c    ********/

int 	add_room_to_graph(t_main *main, t_room *room);
int 	start_with(char *str, char *prefix);
int 	str_count_char(char *str, char c);
t_room*	get_room_by_name(t_graph *graph, char *name);
t_room*	get_room_by_index(t_graph* graph, int index);
int 	create_link(t_room *a, t_room *b);
int		ft_atoi_ants(char *str, int *num);
int 	str_count_char(char *str, char c);
int 	min(int a, int b);

/************* connectivity.c */

int check_connectivity(t_graph *graph);

/************* bfs.c */
int bfs(t_graph* graph, t_room* start, t_room* end);
int bfs_matrix(int **mat, int start, int end, int* level);

/************* list.c */
int			add_end(t_farmlist** head,  t_room* room);
int 		add_front(t_farmlist** head,  t_room* room);
t_room*		pop_front(t_farmlist** head);
void		free_list(t_farmlist* head);
t_intlst*	new_intlst(int val);
t_intlst* 	pop_frt(t_intlst** lst);

/************* pathfinding.c ************ */
t_result*	find_n_paths(t_main* main);
void		get_paths(t_path* paths, int** mat, t_main* main, int path_nbr, int** origin);
void		calculate_min_ants_for_path(t_path* paths, int n_path);

/************* launch_ants.c ************ */
void		send_ants(t_main* main, t_path* paths, int path_nbr);

/************* print_utils.c ************ */
void print_mat(int** mat, int max_y);
void print_paths(t_path* paths, int path_nbr);
void print_level(int*level, int size);
void print_main(t_main *main);
void print_graph(t_graph graph);

/************* free_utils.c ************ */
void 	free_mat(int **mat, int size);
void 	free_paths(t_path* paths, int n_path);
void	free_result(t_result* res);
void 	*free_room(t_room *room);
void 	*free_graph(t_graph *graph);

/************* dinic.c ************ */
t_result* dinic_max_flow(int** mat, int curr, int end, t_main* main, int** origin);

/************* dinic_utils.c ************ */
void	fill_matrix(t_room* start, int** mat, int** copy);
int**	nodes_to_matrix(t_graph* graph, int*** copy);

/************* dinic_result_creation.c ************ */
t_result*	add_result(t_result* head, t_path* paths, int turns, int path_nbr);
int			count_turns(t_path* paths, int n_path, int ants);

#endif