//
//  graph.cpp
//  deanonymization
//
//  Created by Shuyang Shi on 15/9/20.
//  Copyright © 2015年 Shuyang Shi. All rights reserved.
//

#include "graph.hpp"

graph::graph(const char * file_name){
	FILE * f=fopen(file_name, "r");
	if (!f) {
		exit(0);
	}
	fscanf(f, "%d%d", &num_nodes, &num_edges);
	edges.resize(num_nodes+1);
	for (int i=1; i<=num_nodes; i++) {
		nodes.push_back(i);
		edges[i] = new vector<int>;
	}
	for (int i=0, j, k; i<num_edges; i++) {
		fscanf(f, "%d%d", &j, &k);
		edges[j]->push_back(k);
	}
	fclose(f);
	printf("Graph read: %d, %d\n", num_nodes, num_edges);
}



vector<int> * graph::extract_neighbors(int node){
	vector<int> * re = new vector<int>;
	for (vector<int> :: iterator it=edges[node]->begin(); it!=edges[node]->end(); it++)
		re->push_back(*it);
	return re; //TODO: extract neighbors
}

graph::subgraph graph::extract_subgraph(int node){
	subgraph re;
	re.center = node;
	re.num_nodes = 1;
	
	queue<int> Q;
	int * flag = new int[MAX_NODES];
	memset(flag, 0, sizeof(int) * MAX_NODES);
	flag[node]=1;
	Q.push(node);
	for (int i=0, last_cnt = 1; i<L; i++) {
		int cnt = 0;
		re.nodes_per_level[i].clear();
		while (last_cnt --) {
			int cur = Q.front();
			Q.pop();
			for (vector<int> :: iterator it=edges[cur]->begin(); it!=edges[cur]->end(); it++) {
				if (!flag[*it]) {
					flag[*it] = 1;
					Q.push(*it);
					re.nodes_per_level[i].push_back(*it);
					cnt++;
				}
			}
		}
		re.num_nodes_seq.push_back(cnt);
		last_cnt = cnt;
	}
	delete []flag;
	return re;
}
