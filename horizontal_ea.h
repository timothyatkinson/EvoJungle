#ifndef H_EA_H
#define H_EA_H

#include "evaluate.h"
#include "function_set.h"
#include "genetic_operators.h"
#include "individual_util.h"
#include "rand_util.h"

#include "graph.h"

double horizontal_ea(GP_Dataset* train_data, GP_Dataset* validation_data, GP_Dataset* test_data, Function_Set* fset,
  int nodes, int max_depth, int max_size, double mutation_rate, double takeover_rate, double horizontal_rate,
  int n, int l, int max_generations, int max_evals, int init_search);
#endif
