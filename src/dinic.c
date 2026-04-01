#include "lem_in.h"

static int depth_first_search(int** mat, int curr, int end, int flow, int* level){
	if (curr == end){
		return flow;
	}
	for (int nxt = 0; nxt < end + 1; nxt++){
		if (mat[curr][nxt] > 0 && level[nxt] == level[curr] + 1){
			int avaiable_flow = min(flow, mat[curr][nxt]);
			int used_flow = depth_first_search(mat, nxt, end, avaiable_flow, level);
			if (used_flow > 0){
				mat[curr][nxt] -= used_flow;
				mat[nxt][curr] += used_flow;
				return used_flow;
			}
		}
	}
	return 0;
}

int dinic_max_flow(int** graph, int curr, int end, int ants){
	int total_flow = 0;
	int *level = malloc(sizeof(int) * (end + 1));
	// int *costs = NULL;
	// int iter = 0;

	if (!level)
		return -1;
	while (bfs_matrix(graph, curr, end, level)){
		// iter++;
		// if (path_cost_overload(&costs, level[end], iter, ants))
		// 	break;
		while (true) {
			int flow = depth_first_search(graph, curr, end, INT_MAX, level);
			if (flow == 0)
				break;
			total_flow += flow;
		}
	}
	free(level);
	(void)ants;
	// if (costs)
	// 	free(costs);
	return total_flow;
}