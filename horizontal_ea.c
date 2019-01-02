#include "horizontal_ea.h"

Graph* make_bounded_individual(int inputs, int nodes, int outputs, Function_Set* fset, int max_depth, int max_size);
Graph* make_bounded_individual(int inputs, int nodes, int outputs, Function_Set* fset, int max_depth, int max_size){
  Graph* c = initialise_individual(inputs, nodes, outputs, fset, max_depth);
  while(count_active_nodes(c, count_inputs(c), count_outputs(c)) > max_size){
    freeGraph(c);
    c = initialise_individual(inputs, nodes, outputs, fset, max_depth);
  }
  return c;
}

static int active_mutation = 0;
Graph* mutate_bounded_individual(Graph* parent, Function_Set* fset, double mutation_rate, int max_depth, int max_size);
Graph* mutate_bounded_individual(Graph* parent, Function_Set* fset, double mutation_rate, int max_depth, int max_size){
  Graph* copy = duplicate_graph(parent);
  int active = mutate_individual(copy, fset, mutation_rate, max_depth);
  while(count_active_nodes(copy, count_inputs(copy), count_outputs(copy)) > max_size){
    freeGraph(copy);
    copy = duplicate_graph(parent);
    active = mutate_individual(copy, fset, mutation_rate, max_depth);
  }
  active_mutation = active;
  return copy;
}

int roulette_select(double* scores, int n, int exclude);
int roulette_select(double* scores, int n, int exclude){
  double sum = 0.0;
  for(int i = 0; i < n; i++){
    if(i != exclude){
      sum += 1.0 / scores[i];
    }
  }
  double r = random_double();
  double sum2 = 0.0;
  for(int i = 0; i < n; i++){
    if(i != exclude){
      sum2 += 1.0 / scores[i];
      if(r <= sum2 / sum){
        return i;
      }
    }
  }
  return 0;
}

double horizontal_ea(GP_Dataset* train_data, GP_Dataset* validation_data, GP_Dataset* test_data, Function_Set* fset,
  int nodes, int max_depth, int max_size, double mutation_rate, double takeover_rate, double horizontal_rate,
  int n, int l, int max_generations, int max_evals, int init_search)
  {
    int generation = 0;
    int evals = 0;
    Graph* validation_individual;
    double validation_score;
    double* scores = malloc(n * sizeof(double));
    Graph** population = malloc(n * sizeof(Graph*));
    for(int i = 0; i < n; i++){
      population[i] = make_bounded_individual(train_data->inputs, nodes, train_data->outputs, fset, max_depth, max_size);
      scores[i] = gp_evaluate_mse(population[i], train_data, fset);
      evals++;
      double val_score = gp_evaluate_mse(population[i], validation_data, fset);
      if(i == 0){
        validation_individual = duplicate_graph(population[i]);
        validation_score = val_score;
      }
      else{
        if(val_score < validation_score){
          freeGraph(validation_individual);
          validation_individual = duplicate_graph(population[i]);
          validation_score = val_score;
        }
      }
      printf("Init score: %lf\n", scores[i]);
      for(int j = 0; j < init_search - 1; j++){
        Graph* cand = make_bounded_individual(train_data->inputs, nodes, train_data->outputs, fset, max_depth, max_size);
        double score = gp_evaluate_mse(cand, train_data, fset);
        evals++;
        //printf("%lf\n", score);
        double val_score = gp_evaluate_mse(cand, validation_data, fset);
        if(val_score < validation_score){
          freeGraph(validation_individual);
          validation_individual = duplicate_graph(cand);
          validation_score = val_score;
        }
        if(score < scores[i]){
          freeGraph(population[i]);
          population[i] = cand;
          scores[i] = score;
        }
        else{
          freeGraph(cand);
        }
      }
    }
    while (generation < max_generations && evals < max_evals){
      //Normal update.
      int* updated = malloc(n * sizeof(int));
      for(int i = 0; i < n; i++){
        Graph* parent = duplicate_graph(population[i]);
        updated[i] = 0;
        for(int j = 0; j < l; j++){
          if(evals < max_evals){
            Graph* cand;
            cand = mutate_bounded_individual(parent, fset, mutation_rate, max_depth, max_size);
            double score;
            if(active_mutation == 1){
              score = gp_evaluate_mse(cand, train_data, fset);
              evals++;
              double val_score = gp_evaluate_mse(cand, validation_data, fset);
              if(val_score < validation_score){
                freeGraph(validation_individual);
                validation_individual = duplicate_graph(cand);
                validation_score = val_score;
              }
            }
            else{
              score = scores[i];//gp_evaluate_mse(cand, train_data, fset);
              if(score != scores[i]){
                printf("Neutral Mutation produced different active score!\n");
                exit(0);
              }
              score = scores[i];
            }
            if(score <= scores[i] + 0.0000000001){
              freeGraph(population[i]);
              population[i] = cand;
              scores[i] = score;
              updated[i] = 1;
            }
            else{
              freeGraph(cand);
            }
          }
        }
        freeGraph(parent);
      }

      //Takeover event.
      if(n > 1 && random_bool(takeover_rate)){
        int p1 = random_int(0, n);
        int p2 = random_int(0, n - 1);
        if(p2 >= p1){
          p2++;
        }
        if(scores[p2] / scores[p1] > 1.2){
          freeGraph(population[p2]);
          population[p2] = duplicate_graph(population[p1]);
          scores[p2] = scores[p1];
          updated[p2] = 2;
        }
        else if (scores[p1] / scores[p2] > 1.2){
          freeGraph(population[p1]);
          population[p1] = duplicate_graph(population[p2]);
          scores[p1] = scores[p2];
          updated[p1] = 2;
        }
      }
      int best = 0;
      double best_score = scores[0];
      for(int i = 1; i < n; i++){
        if(scores[i] < best_score){
          best_score = scores[i];
          best = i;
        }
      }
      //Horizontal event.
      if(n > 1 && random_bool(horizontal_rate)){
        int p1 = random_int(0, n - 1);
        if(p1 >= best){
          p1++;
        }
        int p2 = roulette_select(scores, n, p1);
        Graph* newp1 = horizontal_gene_transfer(population[p1], population[p2]);
        updated[p1] = 3;
        updated[p2] = 4;
        if(p1 == p2){
          printf("Same parent exception!\n");
          exit(0);
        }
        freeGraph(population[p1]);
        population[p1] = newp1;
        double score = gp_evaluate_mse(population[p1], train_data, fset);
        if(score != scores[p1]){
          printf("\n\nException. Score %lf => %lf\n", scores[p1], score);
          exit(0);
        }
      }

      printf("Generation %d Evals %d, scores [", generation, evals);
      for(int i = 0; i < n; i++){
        printf("%.3e - %d", scores[i], updated[i]);
        if(i < n - 1){
          printf(", ");
        }
      }
      printf("] best = %d, validation = %.3e\r", best, validation_score);
      if(generation == 0){
        printf("\n");
      }


      generation++;
      free(updated);
    }

    double test_score = gp_evaluate_mse(validation_individual, test_data, fset);
    freeGraph(validation_individual);
    for(int i = 0; i < n; i++){
      freeGraph(population[i]);
    }
    free(population);
    free(scores);
    return test_score;
  }
