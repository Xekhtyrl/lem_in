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

int dinic_max_flow(int** mat, int curr, int end, int *dist){
	int total_flow = 0;
	int *level = malloc(sizeof(int) * (end + 1));

	if (!level)
		return -1;
	while (bfs_matrix(mat, curr, end, level, dist)){
		while (true) {
			int flow = depth_first_search(mat, curr, end, INT_MAX, level);
			if (flow == 0)
				break;
			total_flow += flow;
		}
	}
	free(level);
	return total_flow;
}