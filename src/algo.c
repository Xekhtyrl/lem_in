#include "lem_in.h"


typedef struct s_path {
	char **path;
	int length;
	struct s_path *next;
	struct s_path *prev;
} t_path;

int depth_first_search(t_room* curr, t_room* end, int flow){
	if (curr == end){
		printf("coucou\n");
		return flow;
	}
	for (int i = 0; i < curr->link_count; i++){
		t_room* next = curr->links[i];
		if (next->flow > 0 && next->distance == curr->distance + 1){
			int avaiable_flow = min(flow, next->flow);
			int used_flow = depth_first_search(next, end, avaiable_flow);
			if (used_flow > 0){
				next->flow -= used_flow;
				curr->flow += used_flow;
				return used_flow;
			}
		}
	}
	return 0;
}

int dinic_max_flow(t_graph* graph, t_room* start, t_room* end){
	int total_flow = 0;

	while (bfs(graph, start, end, false)){
		print_graph(*graph);
		while (true) {
			int flow = depth_first_search(start, end, INT_MAX);
			if (flow == 0)
				break;
			total_flow += flow;
			end->flow = 1;
		}
	}
	return total_flow;
}

void find_n_paths(t_main* main){
	t_graph graph = main->graph;
	
	int n = dinic_max_flow(&graph, graph.start, graph.end);
	printf("\nnumber of path: %i\n after \n", n);
	print_graph(graph);
}