#ifndef EVAL_H
#define EVAL_H

//C Libraries
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <float.h>

//P-GP2 Libraries
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "individual_util.h"
#include "function_set.h"

typedef struct GP_Dataset {
    int inputs;
    int outputs;
    int rows;
    double** data;
} GP_Dataset;

//Loads a dataset
GP_Dataset* load_dataset(char* file, int inputs, int rand_inputs, double rand_min, double rand_max, int outputs, int rows);
//Loads a tsv dataset from the Datasets folder.
GP_Dataset* load_sr_dataset(char* file, int inputs, int rows, int output_skip);
GP_Dataset** load_all_datasets(char* file, int inputs, int output_skip);
void free_dataset(GP_Dataset* dataset);

//Evaluates a computational network against a dataset
double gp_evaluate(Graph* individual, GP_Dataset* dataset, Function_Set* fset);

//Evaluates a computational network against a dataset
double gp_evaluate_square(Graph* individual, GP_Dataset* dataset, Function_Set* fset);

double gp_evaluate_mse(Graph* host_graph, GP_Dataset* dataset, Function_Set* fset);

//Evaluates a computational network against a dataset
double gp_evaluate_worst (Graph* individual, GP_Dataset* dataset, Function_Set* fset);

#endif
