#ifndef GEN_OP_H
#define GEN_OP_H

#include "graph.h"
#include "individual_util.h"
#include "function_set.h"

Graph* initialise_individual(int inputs, int nodes, int outputs, Function_Set* fset, int max_depth);
Graph* mutate_individual(Graph* host, Function_Set* fset, double mutation_rate, int max_depth);
Graph* local_node_crossover(Graph* p1, Graph* p2, int max_depth);
Graph* local_edge_crossover(Graph* p1, Graph* p2, int max_depth);
void strip_neutral(Graph* host, int neutral_cap);
#endif
