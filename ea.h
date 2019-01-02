#ifndef EA_H
#define EA_H

#include "evaluate.h"
#include "function_set.h"
#include "genetic_operators.h"
#include "individual_util.h"
#include "rand_util.h"

#include "graph.h"

double tournament_elitism(GP_Dataset* train_data, GP_Dataset* val_data, GP_Dataset* test_data, Function_Set* fset,
  int init_nodes, int max_depth, int max_neutral, double crossover_rate, double mutation_rate,
  int pop_size, int tournament_size, int generations, int init_search);

double microbial(GP_Dataset* train_data, GP_Dataset* val_data, GP_Dataset* test_data, Function_Set* fset,
  int init_nodes, int max_depth, int max_neutral, double crossover_rate, double mutation_rate, int pop_size, int evals, int init_search);

double n_times_l(GP_Dataset* train_data, GP_Dataset* val_data, GP_Dataset* test_data, Function_Set* fset,
      int n, int l, int nodes, int max_active, double mutation_rate, int generations);

#endif
