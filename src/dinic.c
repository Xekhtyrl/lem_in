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

t_result* dinic_max_flow(int** mat, int curr, int end, t_main* main, int** origin){
	int total_flow = 0;
	int *level = malloc(sizeof(int) * (end + 1));
	t_result* res = NULL;

	if (!level)
		return NULL;
	while (bfs_matrix(mat, curr, end, level)){
		while (true) {
			int flow = depth_first_search(mat, curr, end, INT_MAX, level);
			if (flow == 0)
				break;
			total_flow += flow;
		}
		t_path* paths = calloc(sizeof(t_path), total_flow);
		get_paths(paths, mat, main, total_flow, origin);
		int turns = count_turns(paths, total_flow, main->ants);
		res = add_result(res, paths, turns, total_flow);
		if (!res) {
			free(level);
			return NULL;
		}
	}
	free(level);
	return res;
}
