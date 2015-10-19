//
//  main.cpp
//  deanonymization
//
//  Created by Shuyang Shi on 15/9/20.
//  Copyright © 2015年 Shuyang Shi. All rights reserved.
//

#include <cstdio>
#include "graph.hpp"
#include "match.hpp"

#define DEBUG 1

int main(int argc, const char * argv[]) {

	//graph G_a("anonymized.txt");
	//graph G("crawled.txt");

	graph G_a("data/50\%/anonymized.txt");
	graph G("data/50\%/crawled.txt");
	//graph G_a("data/100\%/anonymized.txt");
	//graph G("data/100\%/crawled.txt");

	matcher *M = new matcher(&G_a, &G);
#if DEBUG
	M->debug_print();
#endif
//	M->gen_sim_matrix_simranc();
	M->gen_sim_matrix_word2vec();

	//M->load_matrix();
#if DEBUG
	M->record_matrix();
	M->gen_ans_pairs_oldway();
	FILE * backup_res = fopen("bak_res.txt", "w");
	M->print(backup_res);
	fclose(backup_res);
	fprintf(stderr, "old ways result generated in `bak_res.txt`.\n");
#endif
	M->gen_ans_pairs();
	M->print(stdout);

    return 0;
}
