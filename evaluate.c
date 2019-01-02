#include "evaluate.h"

//Loads a csv dataset for Genetic Programming.
GP_Dataset* load_dataset(char* file, int inputs, int rand_inputs, double rand_min, double rand_max, int outputs, int rows){
  GP_Dataset* dataset = malloc(sizeof(GP_Dataset));
  dataset->inputs = inputs + rand_inputs;
  dataset->outputs = outputs;
  dataset->rows = rows;
  dataset->data = malloc((rows * (inputs + rand_inputs + outputs)) * sizeof(double));
  for(int i = 0; i < rows; i++){
    dataset->data[i] = malloc((inputs + rand_inputs + outputs) * sizeof(double));
    for(int j = 0; j < inputs + outputs; j++){
      dataset->data[i][j] = -1.0;
    }
  }
  FILE* fp = fopen(file, "r");
  if(fp == NULL){
      printf("Error: file %s cannot be found.\n", file);
      exit(0);
  }

  for(int j = 0; j < rand_inputs; j++){
    double r = (((double)rand() / (double)RAND_MAX) * (rand_max - rand_min)) + rand_min;
    for (int i = 0; i < rows; i++){
      dataset->data[i][j] = r;
    }
  }
  for (int i = 0; i < rows; i++){
    for(int j = 0; j < (inputs + outputs); j++){
      int r = fscanf(fp," %lf %*c",&dataset->data[i][j + rand_inputs]);
      if(r != 1){
        printf("Error: file %s does not match the given row and columns dimensions.\n", file);
        exit(0);
      }
    }
  }
  return dataset;
}

//Loads a tsv dataset from the Datasets folder.
GP_Dataset* load_sr_dataset(char* file, int inputs, int rows, int output_skip){
  GP_Dataset* dataset = malloc(sizeof(GP_Dataset));
  //dataset->inputs = inputs + 18;
  int in = 18;
  dataset->inputs = inputs + in;
  int outputs = 1;
  dataset->outputs = outputs;
  dataset->rows = rows;
  dataset->data = malloc(rows * sizeof(double*));
  for(int i = 0; i < rows; i++){
    dataset->data[i] = malloc((inputs + in + outputs) * sizeof(double));
  }
  FILE* fp = fopen(file, "r");
  if(fp == NULL){
      printf("Error: file %s cannot be found.\n", file);
      exit(0);
  }
  fscanf(fp, "%*[^\n]\n", NULL);

  if(in == 1){

    for(int i = 0; i < rows; i++){
      dataset->data[i][0] = 0.1;
    }
  }
  else{
    for(int j = 0; j < 9; j++){
      for (int i = 0; i < rows; i++){
        dataset->data[i][j] = -0.9 + ((double)j / 10.0);
      }
    }

    for(int j = 9; j < 18; j++){
      for (int i = 0; i < rows; i++){
        dataset->data[i][j] = 0.1 + ((double)(j - 9) / 10.0);
      }
    }
  }

  for (int i = 0; i < rows; i++){
    for(int j = 0; j < (inputs + 1); j++){
      int r;
      if(j >= inputs){
        for(int k = 0; k < output_skip; k++){
          double x;
          fscanf(fp," %lf\t", &x);
        }
        int r = fscanf(fp," %lf\t",&dataset->data[i][j + in]);
        if(rows != 50000){
          for(int k = 0; k < 2 - output_skip; k++){
            double x;
            fscanf(fp," %lf\t", &x);
          }
        }
      }
      else{
        int r = fscanf(fp," %lf\t",&dataset->data[i][j + in]);
      }
    }
  }
  fclose(fp);
  return dataset;
}
//
// GP_Dataset** load_all_datasets(char* file, int inputs, int output_skip){
//   GP_Dataset* train_dataset = malloc(sizeof(GP_Dataset));
//   GP_Dataset* validation_dataset = malloc(sizeof(GP_Dataset));
//   GP_Dataset* test_dataset = malloc(sizeof(GP_Dataset));
//   //dataset->inputs = inputs + 18;
//   int in = 18;
//   train_dataset->inputs = inputs + in;
//   validation_dataset->inputs = inputs + in;
//   test_dataset->inputs = inputs + in;
//   int outputs = 1;
//   train_dataset->outputs = outputs;
//   validation_dataset->outputs = outputs;
//   test_dataset->outputs = outputs;
//   train_dataset->rows = 35000;
//   validation_dataset->rows = 5000;
//   test_dataset->rows = 10000;
//   train_dataset->data = malloc(35000 * sizeof(double*));
//   for(int i = 0; i < 35000; i++){
//     train_dataset->data[i] = malloc((inputs + in + outputs) * sizeof(double));
//   }
//   validation_dataset->data = malloc(5000 * sizeof(double*));
//   for(int i = 0; i < 5000; i++){
//     validation_dataset->data[i] = malloc((inputs + in + outputs) * sizeof(double));
//   }
//   test_dataset->data = malloc(10000 * sizeof(double*));
//   for(int i = 0; i < 10000; i++){
//     test_dataset->data[i] = malloc((inputs + in + outputs) * sizeof(double));
//   }
//   FILE* fp = fopen(file, "r");
//   if(fp == NULL){
//       printf("Error: file %s cannot be found.\n", file);
//       exit(0);
//   }
//   fscanf(fp, "%*[^\n]\n", NULL);
//
//   for(int j = 0; j < 9; j++){
//     for (int i = 0; i < 35000; i++){
//       train_dataset->data[i][j] = -0.9 + ((double)j / 10.0);
//     }
//     for (int i = 0; i < 5000; i++){
//       validation_dataset->data[i][j] = -0.9 + ((double)j / 10.0);
//     }
//     for (int i = 0; i < 10000; i++){
//       test_dataset->data[i][j] = -0.9 + ((double)j / 10.0);
//     }
//   }
//
//   for(int j = 9; j < 18; j++){
//     for (int i = 0; i < 35000; i++){
//       train_dataset->data[i][j] = 0.1 + ((double)(j - 9) / 10.0);
//     }
//     for (int i = 0; i < 5000; i++){
//       validation_dataset->data[i][j] = 0.1 + ((double)(j - 9) / 10.0);
//     }
//     for (int i = 0; i < 10000; i++){
//       test_dataset->data[i][j] = 0.1 + ((double)(j - 9) / 10.0);
//     }
//   }
//
//   for (int i = 0; i < 50000; i++){
//     for(int j = 0; j < (inputs + 1); j++){
//       int r;
//       if(j >= inputs){
//         for(int k = 0; k < output_skip; k++){
//           double x;
//           fscanf(fp," %lf\t", &x);
//         }
//         if(i < 35000){
//           int r = fscanf(fp," %lf\t",&train_dataset->data[i][j + in]);
//         }
//         else if (i < 40000){
//           int r = fscanf(fp," %lf\t",&validation_dataset->data[i - 35000][j + in]);
//         }
//         else{
//           int r = fscanf(fp," %lf\t",&test_dataset->data[i - 40000][j + in]);
//         }
//       }
//       else{
//         if(i < 35000){
//           int r = fscanf(fp," %lf\t",&train_dataset->data[i][j + in]);
//         }
//         else if (i < 40000){
//           int r = fscanf(fp," %lf\t",&validation_dataset->data[i - 35000][j + in]);
//         }
//         else{
//           int r = fscanf(fp," %lf\t",&test_dataset->data[i - 40000][j + in]);
//         }
//       }
//     }
//   }
//   fclose(fp);
//   GP_Dataset** datasets = malloc(3 * sizeof(GP_Dataset*));
//   datasets[0] = train_dataset;
//   datasets[1] = validation_dataset;
//   datasets[2] = test_dataset;
//   return datasets;
// }


GP_Dataset** load_all_datasets(char* file, int inputs, int output_skip){
  GP_Dataset* train_dataset = malloc(sizeof(GP_Dataset));
  GP_Dataset* validation_dataset = malloc(sizeof(GP_Dataset));
  GP_Dataset* test_dataset = malloc(sizeof(GP_Dataset));
  //dataset->inputs = inputs + 18;
  int in = 18;
  train_dataset->inputs = inputs + in;
  validation_dataset->inputs = inputs + in;
  test_dataset->inputs = inputs + in;
  int outputs = 1;
  train_dataset->outputs = outputs;
  validation_dataset->outputs = outputs;
  test_dataset->outputs = outputs;
  train_dataset->rows = 5000;
  validation_dataset->rows = 10000;
  test_dataset->rows = 40000;
  train_dataset->data = malloc(5000 * sizeof(double*));
  for(int i = 0; i < 5000; i++){
    train_dataset->data[i] = malloc((inputs + in + outputs) * sizeof(double));
  }
  validation_dataset->data = malloc(10000 * sizeof(double*));
  for(int i = 0; i < 10000; i++){
    validation_dataset->data[i] = malloc((inputs + in + outputs) * sizeof(double));
  }
  test_dataset->data = malloc(40000 * sizeof(double*));
  for(int i = 0; i < 40000; i++){
    test_dataset->data[i] = malloc((inputs + in + outputs) * sizeof(double));
  }
  FILE* fp = fopen(file, "r");
  if(fp == NULL){
      printf("Error: file %s cannot be found.\n", file);
      exit(0);
  }
  fscanf(fp, "%*[^\n]\n", NULL);

  for(int j = 0; j < 9; j++){
    for (int i = 0; i < 5000; i++){
      train_dataset->data[i][j] = -0.9 + ((double)j / 10.0);
    }
    for (int i = 0; i < 10000; i++){
      validation_dataset->data[i][j] = -0.9 + ((double)j / 10.0);
    }
    for (int i = 0; i < 40000; i++){
      test_dataset->data[i][j] = -0.9 + ((double)j / 10.0);
    }
  }

  for(int j = 9; j < 18; j++){
    for (int i = 0; i < 5000; i++){
      train_dataset->data[i][j] = 0.1 + ((double)(j - 9) / 10.0);
    }
    for (int i = 0; i < 10000; i++){
      validation_dataset->data[i][j] = 0.1 + ((double)(j - 9) / 10.0);
    }
    for (int i = 0; i < 40000; i++){
      test_dataset->data[i][j] = 0.1 + ((double)(j - 9) / 10.0);
    }
  }

  for (int i = 0; i < 50000; i++){
    for(int j = 0; j < (inputs + 1); j++){
      int r;
      if(j >= inputs){
        for(int k = 0; k < output_skip; k++){
          double x;
          fscanf(fp," %lf\t", &x);
        }
        if(i < 0){
          int r = fscanf(fp," %lf\t",&train_dataset->data[i][j + in]);
        }
        else if (i < 10000){
          int r = fscanf(fp," %lf\t",&validation_dataset->data[i][j + in]);
        }
        else{
          int r = fscanf(fp," %lf\t",&test_dataset->data[i - 10000][j + in]);
        }
      }
      else{
        if(i < 0){
          int r = fscanf(fp," %lf\t",&train_dataset->data[i][j + in]);
        }
        else if (i < 10000){
          int r = fscanf(fp," %lf\t",&validation_dataset->data[i][j + in]);
        }
        else{
          int r = fscanf(fp," %lf\t",&test_dataset->data[i - 10000][j + in]);
        }
      }
    }
  }
  fclose(fp);
  GP_Dataset** datasets = malloc(3 * sizeof(GP_Dataset*));
  datasets[0] = train_dataset;
  datasets[1] = validation_dataset;
  datasets[2] = test_dataset;
  return datasets;
}

void free_dataset(GP_Dataset* dataset){
  for(int i = 0; i < dataset->rows; i++){
    free(dataset->data[i]);
  }
  free(dataset->data);
  free(dataset);
}

//Evaluates a Genetic Programming individual. Used in CGP, EGGP, PDGP and TinyGP implementations
double gp_evaluate(Graph* host_graph, GP_Dataset* dataset, Function_Set* fset){
	mark_active_blue(host_graph);

  int rows = dataset->rows;
  int inputs = dataset->inputs;
  int outputs = dataset->outputs;
  int width = host_graph->nodes.size;
  double values[rows][width];
  int ready[width];
  double totalError = 0.0;
  //Find inputs and outputs
  int inputIndex[inputs];
  for(int i = 0; i<inputs; i++){
    inputIndex[i] = -1;
  }
  int outputIndex[outputs];
  for(int j = 0; j<outputs; j++){
    outputIndex[j] = -1;
  }

  for(int host_index = 0; host_index < host_graph->nodes.size; host_index++)
  {
     Node *host_node = getNode(host_graph, host_index);
     if(host_node == NULL || host_node->index == -1) continue;

     HostLabel label = host_node->label;

     HostListItem *item = label.list->first;
     HostListItem *item2 = label.list->last;
     if(item->atom.type != 'i') break;
     if(item2->atom.type != 's') break;
     if(strcmp(item2->atom.str, "IN") == 0){
       inputIndex[item->atom.num] = host_index;
     }
     if(strcmp(item2->atom.str, "OUT") == 0){
       outputIndex[item->atom.num] = host_index;
     }
  }

  int queue[host_graph->nodes.size];
  int head = 0;
  int tail = 0;

	for(int x = 0; x < width; x++){
      ready[x] = 0;
	}
  for(int r = 0; r < rows; r++){
    for(int x = 0; x < width; x++){
      values[r][x] = 0.0;
    }
	}
  for(int q = 0; q < width; q++){
    queue[q] = 0;
  }

  //Load inputs
  for(int i = 0; i < inputs; i++){
		for(int r = 0; r < rows; r++){
    	values[r][inputIndex[i]] = (dataset->data)[r][i];
		}
    ready[inputIndex[i]] = 1;
    Node *host_node = getNode(host_graph, inputIndex[i]);
    int counter;
    for(counter = 0; counter < host_node->in_edges.size + 2; counter++)
    {
      Edge *host_edge = getNthInEdge(host_graph, host_node, counter);
      if(host_edge == NULL) continue;
      int source = host_edge->source;
      ready[source]++;
			Node* source_node = getNode(host_graph, source);
			if(source_node->label.mark == 0) continue;
       if(ready[source] >= source_node->outdegree){
        queue[tail] = source;
        tail++;
      }
    }
  }



  while(head < tail){
    int node_index = queue[head];
    head++;
    Node *host_node = getNode(host_graph, node_index);

    HostLabel label = host_node->label;
    HostListItem *item = label.list->last;
    char* function = item->atom.str;

    double in_values[rows][host_node->outdegree];
    int counter;
    for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
    {
      Edge *host_edge = getNthOutEdge(host_graph, host_node, counter);
      if(host_edge == NULL) continue;
      int target = host_edge->target;

			HostLabel label = host_edge->label;
			int vIndex = label.list->first->atom.num;
			for(int r = 0; r < rows; r++){
      	in_values[r][vIndex] = values[r][target];
			}
    }

    if(strcmp(function, "OUT") == 0){
	 	   //printf("OUT function\n");
  		 for(int r = 0; r < rows; r++){
          values[r][node_index] = in_values[r][0];
		// 		//printf("%d: %lf\n", node_index, values[r][node_index]);
	 	   }
     }
     else{
       Function* f = get_function(fset, function);
  		 for(int r = 0; r < rows; r++){
         values[r][node_index] = f->func(in_values[r]);
         if(isnan(values[r][node_index]) || isinf(values[r][node_index])){
           values[r][node_index] = 999999999;
         }
       }
     }

    for(counter = 0; counter < host_node->in_edges.size + 2; counter++)
    {
      Edge *host_edge = getNthInEdge(host_graph, host_node, counter);
      if(host_edge == NULL) continue;
      int source = host_edge->source;
      ready[source]++;
			Node* source_node = getNode(host_graph, source);
			if(source_node->label.mark == 0) continue;
      if(ready[source] >= source_node->outdegree){
        queue[tail] = source;
        tail++;
      }
    }
  }

  for(int o = 0; o < outputs; o++){
		for(int r = 0; r < rows; r++){
      double e = fabs(values[r][outputIndex[o]] - dataset->data[r][inputs + o]);
      if(isnan(e)){
        printf("Error!\n");
        printfGraph(host_graph);
        unmark_graph(host_graph);
        exit(0);
      }
			//printf("Expected %lf got %lf diff %lf\n", data[r][inputs + o], values[r][outputIndex[o]], fabs(values[r][outputIndex[o]] - data[r][inputs + o]));
    	totalError = totalError + fabs(values[r][outputIndex[o]] - dataset->data[r][inputs + o]);
		}
  }
	unmark_graph(host_graph);
  return totalError;
}

//Evaluates a Genetic Programming individual. Used in CGP, EGGP, PDGP and TinyGP implementations
double gp_evaluate_square(Graph* host_graph, GP_Dataset* dataset, Function_Set* fset){
	mark_active_blue(host_graph);

  int rows = dataset->rows;
  int inputs = dataset->inputs;
  int outputs = dataset->outputs;
  int width = host_graph->nodes.size;
  double** values = malloc(rows * sizeof(double*));
  for(int r = 0; r < rows; r++){
    values[r] = malloc(width * sizeof(double));
  }
  int ready[width];
  double totalError = 0.0;
  //Find inputs and outputs
  int inputIndex[inputs];
  for(int i = 0; i<inputs; i++){
    inputIndex[i] = -1;
  }
  int outputIndex[outputs];
  for(int j = 0; j<outputs; j++){
    outputIndex[j] = -1;
  }

  for(int host_index = 0; host_index < host_graph->nodes.size; host_index++)
  {
     Node *host_node = getNode(host_graph, host_index);
     if(host_node == NULL || host_node->index == -1) continue;

     HostLabel label = host_node->label;

     HostListItem *item = label.list->first;
     HostListItem *item2 = label.list->last;
     if(item->atom.type != 'i') break;
     if(item2->atom.type != 's') break;
     if(strcmp(item2->atom.str, "IN") == 0){
       inputIndex[item->atom.num] = host_index;
     }
     if(strcmp(item2->atom.str, "OUT") == 0){
       outputIndex[item->atom.num] = host_index;
     }
  }

  int queue[host_graph->nodes.size];
  int head = 0;
  int tail = 0;

  int* visited = malloc(host_graph->nodes.size * sizeof(int));
  for(int i = 0; i < host_graph->nodes.size; i++){
    visited[i] = 0;
  }

	for(int x = 0; x < width; x++){
      ready[x] = 0;
	}
  for(int r = 0; r < rows; r++){
    for(int x = 0; x < width; x++){
      values[r][x] = -1.0;
    }
	}
  for(int q = 0; q < width; q++){
    queue[q] = 0;
  }

  //Load inputs
  for(int i = 0; i < inputs; i++){
		for(int r = 0; r < rows; r++){
    	values[r][inputIndex[i]] = (dataset->data)[r][i];
		}
    ready[inputIndex[i]] = 1;
    Node *host_node = getNode(host_graph, inputIndex[i]);
    int counter;
    for(counter = 0; counter < host_node->in_edges.size + 2; counter++)
    {
      Edge *host_edge = getNthInEdge(host_graph, host_node, counter);
      if(host_edge == NULL) continue;
      int source = host_edge->source;
      ready[source]++;
			Node* source_node = getNode(host_graph, source);
			if(source_node->label.mark == 0) continue;
       if(ready[source] >= source_node->outdegree){
        queue[tail] = source;
        tail++;
      }
    }
  }

  int outputs_found = 0;

  while(head < tail){
    int node_index = queue[head];
    visited[node_index] = 1;
    head++;
    Node *host_node = getNode(host_graph, node_index);

    HostLabel label = host_node->label;
    HostListItem *item = label.list->last;
    char* function = item->atom.str;
    double** in_values = malloc(rows * sizeof(double*));
    for(int r = 0; r < rows; r++){
      in_values[r] = malloc(host_node->outdegree * sizeof(double));
    }
    int counter;
    for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
    {
      Edge *host_edge = getNthOutEdge(host_graph, host_node, counter);
      if(host_edge == NULL) continue;
      int target = host_edge->target;

			HostLabel label = host_edge->label;
			int vIndex = label.list->first->atom.num;
			for(int r = 0; r < rows; r++){
      	in_values[r][vIndex] = values[r][target];
			}
    }

    if(strcmp(function, "OUT") == 0){
        outputs_found++;
	 	   //printf("OUT function\n");
  		 for(int r = 0; r < rows; r++){
          values[r][node_index] = in_values[r][0];
          if(isnan(values[r][node_index]) || isinf(values[r][node_index])){
            values[r][node_index] = DBL_MAX;
          }
		// 		//printf("%d: %lf\n", node_index, values[r][node_index]);
	 	   }
     }
     else{
       Function* f = get_function(fset, function);
  		 for(int r = 0; r < rows; r++){
         values[r][node_index] = f->func(in_values[r]);
       }
     }

    for(counter = 0; counter < host_node->in_edges.size + 2; counter++)
    {
      Edge *host_edge = getNthInEdge(host_graph, host_node, counter);
      if(host_edge == NULL) continue;
      int source = host_edge->source;
      ready[source]++;
			Node* source_node = getNode(host_graph, source);
			if(source_node->label.mark == 0) continue;
      if(ready[source] >= source_node->outdegree){
        queue[tail] = source;
        tail++;
      }
    }
    for(int r = 0; r < rows; r++){
      free(in_values[r]);
    }
    free(in_values);
  }

  if(outputs_found < outputs){
    printf("Error w.r.t outputs!\n");
    printfGraph(host_graph);
    exit(0);
  }

  for(int o = 0; o < outputs; o++){
		for(int r = 0; r < rows; r++){
      if(visited[outputIndex[o]] == 0){
        printf("Output exception:\n");
        printfGraph(host_graph);
      }
			//printf("Expected %lf got %lf diff %lf\n", data[r][inputs + o], values[r][outputIndex[o]], fabs(values[r][outputIndex[o]] - data[r][inputs + o]));
    	totalError = totalError + pow(fabs(values[r][outputIndex[o]] - dataset->data[r][inputs + o]), 2);
		}
  }
  for(int r = 0; r < rows; r++){
    free(values[r]);
  }
  free(values);
  free(visited);
	unmark_graph(host_graph);
  return totalError;
}

double gp_evaluate_mse(Graph* host_graph, GP_Dataset* dataset, Function_Set* fset){
  return gp_evaluate_square(host_graph, dataset, fset) / (double)dataset->rows;
}

//Evaluates a Genetic Programming individual. Used in CGP, EGGP, PDGP and TinyGP implementations
double gp_evaluate_worst(Graph* host_graph, GP_Dataset* dataset, Function_Set* fset){
	mark_active_blue(host_graph);

  double worst = 0.0;
  int rows = dataset->rows;
  int inputs = dataset->inputs;
  int outputs = dataset->outputs;
  int width = host_graph->nodes.size;
  double values[rows][width];
  int ready[width];
  //Find inputs and outputs
  int inputIndex[inputs];
  for(int i = 0; i<inputs; i++){
    inputIndex[i] = -1;
  }
  int outputIndex[outputs];
  for(int j = 0; j<outputs; j++){
    outputIndex[j] = -1;
  }

  for(int host_index = 0; host_index < host_graph->nodes.size; host_index++)
  {
     Node *host_node = getNode(host_graph, host_index);
     if(host_node == NULL || host_node->index == -1) continue;

     HostLabel label = host_node->label;

     HostListItem *item = label.list->first;
     HostListItem *item2 = label.list->last;
     if(item->atom.type != 'i') break;
     if(item2->atom.type != 's') break;
     if(strcmp(item2->atom.str, "IN") == 0){
       inputIndex[item->atom.num] = host_index;
     }
     if(strcmp(item2->atom.str, "OUT") == 0){
       outputIndex[item->atom.num] = host_index;
     }
  }

  int queue[host_graph->nodes.size];
  int head = 0;
  int tail = 0;

	for(int x = 0; x < width; x++){
      ready[x] = 0;
	}
  for(int r = 0; r < rows; r++){
    for(int x = 0; x < width; x++){
      values[r][x] = -1.0;
    }
	}
  for(int q = 0; q < width; q++){
    queue[q] = 0;
  }

  //Load inputs
  for(int i = 0; i < inputs; i++){
		for(int r = 0; r < rows; r++){
    	values[r][inputIndex[i]] = (dataset->data)[r][i];
		}
    ready[inputIndex[i]] = 1;
    Node *host_node = getNode(host_graph, inputIndex[i]);
    int counter;
    for(counter = 0; counter < host_node->in_edges.size + 2; counter++)
    {
      Edge *host_edge = getNthInEdge(host_graph, host_node, counter);
      if(host_edge == NULL) continue;
      int source = host_edge->source;
      ready[source]++;
			Node* source_node = getNode(host_graph, source);
			if(source_node->label.mark == 0) continue;
       if(ready[source] >= source_node->outdegree){
        queue[tail] = source;
        tail++;
      }
    }
  }



  while(head < tail){
    int node_index = queue[head];
    head++;
    Node *host_node = getNode(host_graph, node_index);

    HostLabel label = host_node->label;
    HostListItem *item = label.list->last;
    char* function = item->atom.str;

    double in_values[rows][host_node->outdegree];
    int counter;
    for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
    {
      Edge *host_edge = getNthOutEdge(host_graph, host_node, counter);
      if(host_edge == NULL) continue;
      int target = host_edge->target;

			HostLabel label = host_edge->label;
			int vIndex = label.list->first->atom.num;
			for(int r = 0; r < rows; r++){
      	in_values[r][vIndex] = values[r][target];
			}
    }

    if(strcmp(function, "OUT") == 0){
	 	   //printf("OUT function\n");
  		 for(int r = 0; r < rows; r++){
          values[r][node_index] = in_values[r][0];
		// 		//printf("%d: %lf\n", node_index, values[r][node_index]);
	 	   }
     }
     else{
       Function* f = get_function(fset, function);
  		 for(int r = 0; r < rows; r++){
         values[r][node_index] = f->func(in_values[r]);
         if(isnan(values[r][node_index]) || isinf(values[r][node_index])){
           values[r][node_index] = 999999999;
         }
       }
     }

    for(counter = 0; counter < host_node->in_edges.size + 2; counter++)
    {
      Edge *host_edge = getNthInEdge(host_graph, host_node, counter);
      if(host_edge == NULL) continue;
      int source = host_edge->source;
      ready[source]++;
			Node* source_node = getNode(host_graph, source);
			if(source_node->label.mark == 0) continue;
      if(ready[source] >= source_node->outdegree){
        queue[tail] = source;
        tail++;
      }
    }
  }

  for(int o = 0; o < outputs; o++){
		for(int r = 0; r < rows; r++){
			//printf("Expected %lf got %lf diff %lf\n", data[r][inputs + o], values[r][outputIndex[o]], fabs(values[r][outputIndex[o]] - data[r][inputs + o]));
    	double error = fabs(values[r][outputIndex[o]] - dataset->data[r][inputs + o]);
      if(error > worst){
        worst = error;
      }
		}
  }
	unmark_graph(host_graph);
  return worst;
}
