#include "ea.h"

int tournament(double* scores, int pop_size, int tournament_size);
int tournament(double* scores, int pop_size, int tournament_size){
  int winner = -1;
  double winner_score = -1;
  for(int i = 0; i < tournament_size; i++){
    int candidate = random_int(0, pop_size);
    if(winner == -1 || scores[candidate] <= winner_score + 0.000000001){
      winner = candidate;
      winner_score = scores[candidate];
    }
  }
  return winner;
}

double tournament_elitism(GP_Dataset* train_data, GP_Dataset* val_data, GP_Dataset* test_data, Function_Set* fset,
  int init_nodes, int max_depth, int max_neutral, double crossover_rate, double mutation_rate,
  int pop_size, int tournament_size, int generations, int init_search){

    //Generation 0. Initialise population.
    int generation = 0;
    Graph** population = malloc(pop_size * sizeof(Graph*));
    double* scores = malloc(pop_size * sizeof(Graph*));
    int elite_index = -1;
    double elite_score;
    Graph* best_found = NULL;
    double best_score;
    if(init_search < pop_size){
      for(int i = 0; i < pop_size; i++){
        population[i] = initialise_individual(train_data->inputs, init_nodes, train_data->outputs, fset, max_depth / 2);
        scores[i] = gp_evaluate_mse(population[i], train_data, fset);
        double val_score;
        if(val_data == NULL){
          val_score = scores[i];
        }
        else{
          val_score = gp_evaluate_mse(population[i], val_data, fset);
        }
        strip_neutral(population[i], max_neutral);

        //Identify elite individual
        if(elite_index == -1 || scores[i] <= elite_score + 0.000000001){
          elite_index = i;
          elite_score = scores[i];
        }

        //Identify best individual w.r.t. validation set (may not be elite individual)
        if(best_found == NULL || val_score < best_score){
          if(best_found != NULL){
            freeGraph(best_found);
          }
          best_found = duplicate_graph(population[i]);
          best_score = val_score;
        }
      }
    }
    else{
      double worst;
      int worst_index;
      for(int i = 0; i < init_search; i++){
        Graph* ind = initialise_individual(train_data->inputs, init_nodes, train_data->outputs, fset, max_depth / 2);
        double score = gp_evaluate_mse(ind, train_data, fset);
        double val_score;
        strip_neutral(ind, max_neutral);
        if(val_data == NULL){
          val_score = score;
        }
        else{
          val_score = gp_evaluate_mse(ind, val_data, fset);
        }
        if(i < pop_size){
          population[i] = ind;
          scores[i] = score;
          if(i == 0 || score > worst){
            worst = score;
            worst_index = i;
          }
        }
        else{
          if(score < worst){
            freeGraph(population[worst_index]);
            scores[worst_index] = score;
            population[worst_index] = ind;
            double new_worst;
            int new_worst_index;
            for(int j = 0; j < pop_size; j++){
              if(j == 0 || scores[j] > new_worst){
                new_worst = scores[j];
                new_worst_index = j;
              }
            }
            worst = new_worst;
            worst_index = new_worst_index;
          }
        }

        //Identify best individual w.r.t. validation set (may not be elite individual)
        if(best_found == NULL || val_score < best_score){
          if(best_found != NULL){
            freeGraph(best_found);
          }
          best_found = duplicate_graph(ind);
          best_score = val_score;
        }
      }
      printf("Init scores[");
      for(int i = 0; i < pop_size; i++){
        printf("%lf", scores[i]);
        if(i != pop_size - 1){
          printf(", ");
        }
        //Identify elite individual
        if(elite_index == -1 || scores[i] <= elite_score + 0.001){
          elite_index = i;
          elite_score = scores[i];
        }
      }
      printf("]\n");
    }

    generation++;

    printf("Init generation: %d individuals. Elite score %lf, Best score %lf\n", pop_size, elite_score, best_score);
    while(generation < generations){

      Graph** new_pop = malloc(pop_size * sizeof(Graph*));
      double* new_scores = malloc(pop_size * sizeof(double));

      for(int i = 0; i < pop_size; i++){
        //Copy elite individual. Will never get better elite score or validation score than existing ones!
        if(i == elite_index){
          new_pop[i] = duplicate_graph(population[i]);
          new_scores[i] = scores[i];
        }
        else{
          //Generate new individual
          if(random_bool(crossover_rate)){
            //Do crossover
            int p1 = tournament(scores, pop_size, tournament_size);
            int p2 = tournament(scores, pop_size, tournament_size);
            new_pop[i] = local_edge_crossover(population[p1], population[p2], max_depth);
            strip_neutral(new_pop[i], max_neutral);
          }
          else{
            int p1;
            if(pop_size < 20){
              p1 = elite_index;
            }
            else{
              p1 = tournament(scores, pop_size, tournament_size);
            }

            new_pop[i] = mutate_individual(population[p1], fset, mutation_rate, max_depth);
            strip_neutral(new_pop[i], max_neutral);
          }
          new_scores[i] = gp_evaluate_mse(new_pop[i], train_data, fset);
        }
      }

      //Update elite and best scores.
      int new_elite = elite_index;
      int update = 0;
      for(int i = 0; i < pop_size; i++){
        double val_score;
        if(val_data == NULL){
          val_score = new_scores[i];
        }
        else{
          val_score = gp_evaluate_mse(new_pop[i], val_data, fset);
        }

        freeGraph(population[i]);
        //Identify elite individual
        if(elite_index == -1 || (new_scores[i] <= elite_score + 0.000000001 && i != elite_index)){
          new_elite = i;
          elite_score = new_scores[i];
          update = 1;
        }

        //Identify best individual w.r.t. validation set (may not be elite individual)
        if(best_found == NULL || val_score < best_score){
          if(best_found != NULL){
            freeGraph(best_found);
          }
          best_found = duplicate_graph(new_pop[i]);
          best_score = val_score;
        }
      }
      elite_index = new_elite;
      free(population);
      free(scores);
      population = new_pop;
      scores = new_scores;


      //Print
      if(generation%1 == 0 || generation + 1 == generations){
        char c = '\r';
        int n = count_active_nodes(population[elite_index], count_inputs(population[elite_index]), count_outputs(population[elite_index]));
        int e = count_active_edges(population[elite_index]);
        double m_rate = mutation_rate / (double)(count_active_nodes(population[elite_index], count_inputs(population[elite_index]), count_outputs(population[elite_index])) + count_active_edges(population[elite_index]));
        // mark_active_blue(population[elite_index]);
        // printfGraph(population[elite_index]);
        // unmark_graph(population[elite_index]);
        printf("Generation %d: %d individuals. Elite score %lf (%d, %d %lf), Best score %lf %d%c", generation, pop_size, elite_score, n, e, m_rate, best_score, update, c);
        printf("Generation %d: %d individuals. Elite score %lf (%d, %d %lf), Best score %lf %d%c", generation, pop_size, elite_score, n, e, m_rate, best_score, update, c);
        printf("Generation %d: %d individuals. Elite score %lf (%d, %d %lf), Best score %lf %d%c", generation, pop_size, elite_score, n, e, m_rate, best_score, update, c);
        // printf("\n[");
        // for(int i = 0; i < pop_size; i++){
        //   printf("%lf, ", scores[i]);
        // }
        // printf("]\n");
      }

      generation++;
    }

    for(int i = 0; i < pop_size; i++){
      freeGraph(population[i]);
    }
    printf("\n");
    free(population);
    free(scores);
    make_depth(best_found);
    mark_active_blue(best_found);
    //printfGraph(best_found);
    double test_score = gp_evaluate_mse(best_found, test_data, fset);
    freeGraph(best_found);
    return test_score;
}


double microbial(GP_Dataset* train_data, GP_Dataset* val_data, GP_Dataset* test_data, Function_Set* fset,
  int init_nodes, int max_depth, int max_neutral, double crossover_rate, double mutation_rate, int pop_size, int evals, int init_search){

    //Generation 0. Initialise population.
    int eval = 0;
    Graph** population = malloc(pop_size * sizeof(Graph*));
    double* scores = malloc(pop_size * sizeof(Graph*));
    int elite_index = -1;
    double elite_score;
    Graph* best_found = NULL;
    double best_score;
    if(init_search < pop_size){
      eval = pop_size;
      for(int i = 0; i < pop_size; i++){
        population[i] = initialise_individual(train_data->inputs, init_nodes, train_data->outputs, fset, max_depth / 2);
        scores[i] = gp_evaluate_mse(population[i], train_data, fset);
        double val_score;
        if(val_data == NULL){
          val_score = scores[i];
        }
        else{
          val_score = gp_evaluate_mse(population[i], val_data, fset);
        }
        strip_neutral(population[i], max_neutral);

        //Identify elite individual
        if(elite_index == -1 || scores[i] <= elite_score + 0.000000001){
          elite_index = i;
          elite_score = scores[i];
        }

        //Identify best individual w.r.t. validation set (may not be elite individual)
        if(best_found == NULL || val_score < best_score){
          if(best_found != NULL){
            freeGraph(best_found);
          }
          best_found = duplicate_graph(population[i]);
          best_score = val_score;
        }
      }
    }
    else{
      eval = init_search;
      double worst;
      int worst_index;
      for(int i = 0; i < init_search; i++){
        Graph* ind = initialise_individual(train_data->inputs, init_nodes, train_data->outputs, fset, max_depth / 2);
        double score = gp_evaluate_mse(ind, train_data, fset);
        double val_score;
        strip_neutral(ind, max_neutral);
        if(val_data == NULL){
          val_score = score;
        }
        else{
          val_score = gp_evaluate_mse(ind, val_data, fset);
        }
        if(i < pop_size){
          population[i] = ind;
          scores[i] = score;
          if(i == 0 || score > worst){
            worst = score;
            worst_index = i;
          }
        }
        else{
          if(score < worst){
            freeGraph(population[worst_index]);
            scores[worst_index] = score;
            population[worst_index] = ind;
            double new_worst;
            int new_worst_index;
            for(int j = 0; j < pop_size; j++){
              if(j == 0 || scores[j] > new_worst){
                new_worst = scores[j];
                new_worst_index = j;
              }
            }
            worst = new_worst;
            worst_index = new_worst_index;
          }
        }

        //Identify best individual w.r.t. validation set (may not be elite individual)
        if(best_found == NULL || val_score < best_score){
          if(best_found != NULL){
            freeGraph(best_found);
          }
          best_found = duplicate_graph(ind);
          best_score = val_score;
        }
      }
      printf("Init scores[");
      for(int i = 0; i < pop_size; i++){
        printf("%lf", scores[i]);
        if(i != pop_size - 1){
          printf(", ");
        }
        //Identify elite individual
        if(elite_index == -1 || scores[i] <= elite_score + 0.001){
          elite_index = i;
          elite_score = scores[i];
        }
      }
      printf("]\n");
    }


    while(eval < evals){
      //Pick competing individuals.
      int p1 = random_integer(0, pop_size);
      int p2 = random_integer(0, pop_size - 1);
      if(p2 >= p1){
        p2++;
      }
      //Winner is p1. Switch if necessary
      if(scores[p1] > scores[p2]){
        int x = p1;
        p1 = p2;
        p2 = x;
      }
      Graph* child;
      if(random_bool(crossover_rate)){
        child = local_edge_crossover(population[p1], population[p2], max_depth);
      }
      else{
        child = mutate_individual(population[p1], fset, mutation_rate, max_depth);
      }
      double score = gp_evaluate_mse(child, train_data, fset);
      double val_score;

      if(val_data == NULL){
        val_score = score;
      }
      else{
        val_score = gp_evaluate_mse(child, val_data, fset);
      }

      double old = scores[p2];

      if(score < old + 0.0000000001){
          freeGraph(population[p2]);
          population[p2] = child;
          strip_neutral(child, max_neutral);
          scores[p2] = score;
      }
      else{
        freeGraph(child);
      }

      if(scores[p2] <= elite_score + 0.0000000001){
        elite_score = scores[p2];
        elite_index = p2;
      }
      if(val_score < best_score){
        best_score = val_score;
        freeGraph(best_found);
        best_found = duplicate_graph(child);
      }

      int n = count_active_nodes(population[elite_index], count_inputs(population[elite_index]), count_outputs(population[elite_index]));
      int e = count_active_edges(population[elite_index]);
      printf("%d evaluations. %lf best score (%d, %d) - %lf validation score. %.10e -> %.10e      \r", eval, elite_score, n, e, best_score, old, scores[p2]);

      eval++;
    }

    for(int i = 0; i < pop_size; i++){
      freeGraph(population[i]);
    }
    free(population);
    free(scores);
    double test = gp_evaluate_mse(best_found, test_data, fset);
    free(best_found);
    return test;
  }

double n_times_l(GP_Dataset* train_data, GP_Dataset* val_data, GP_Dataset* test_data, Function_Set* fset,
    int n, int l, int nodes, int max_active, double mutation_rate, int generations){
    Graph** parents = malloc(n * sizeof(Graph*));
    double* scores = malloc(n * sizeof(double));

    Graph* validation_best;
    double validation_score;

    int invalids = 0;

    //First Generation.
    for(int i = 0; i < n; i++){
      Graph* best = NULL;
      double best_score = 0.0;
      for(int j = 0; j < l; j++){
        Graph* ind = initialise_individual(train_data->inputs, nodes, train_data->outputs, fset, nodes);
        while(count_active_nodes(ind, count_inputs(ind), count_outputs(ind)) > max_active){
          invalids++;
          freeGraph(ind);
          ind = initialise_individual(train_data->inputs, nodes, train_data->outputs, fset, nodes);
        }

        if(i == 0 && j == 0){
          validation_best = duplicate_graph(ind);
          validation_score = gp_evaluate_mse(ind, val_data, fset);
        }
        else{
          double v_score = gp_evaluate_mse(ind, val_data, fset);
          if(v_score < validation_score){
            freeGraph(validation_best);
            validation_best = duplicate_graph(ind);
            validation_score = v_score;
          }
        }

        if(j == 0){
          best = ind;
          best_score = gp_evaluate_mse(ind, train_data, fset);
        }
        else{
          double score = gp_evaluate_mse(ind, train_data, fset);
          if(score < best_score){
            freeGraph(best);
            best = ind;
            best_score = score;
          }
          else{
            freeGraph(ind);
          }
        }
      }
      parents[i] = best;
      scores[i] = best_score;
    }

    int generation = 1;
    while(generation < generations){

      printf("Current generation: %d. Scores [", generation);
      for(int i = 0; i < n; i++){
        printf("%lf", scores[i]);
        if(i != n - 1){
          printf(", ");
        }
      }
      printf("] - %lf validation\r", validation_score);

      for(int i = 0; i < n; i++){
        Graph* parent = duplicate_graph(parents[i]);
        double parent_score = scores[i];
        for(int j = 0; j < l; j++){
          Graph* child = mutate_individual(parents[i], fset, mutation_rate, nodes);
          while(count_active_nodes(child, count_inputs(child), count_outputs(child)) > max_active){
            invalids++;
            freeGraph(child);
            child = mutate_individual(parents[i], fset, mutation_rate, nodes);
          }

          double score = gp_evaluate_mse(child, train_data, fset);
          double v_score = gp_evaluate_mse(child, val_data, fset);
          if(v_score < validation_score){
            freeGraph(validation_best);
            validation_best = duplicate_graph(child);
            validation_score = v_score;
          }
          if(score <= parent_score + 0.0000001){
            freeGraph(parent);
            parent = child;
            parent_score = score;
          }
          else{
            freeGraph(child);
          }
        }

        freeGraph(parents[i]);
        parents[i] = parent;
        scores[i] = parent_score;
      }
      generation++;
    }

    printf("\nCurrent generation: %d. Scores [", generation);
    for(int i = 0; i < n; i++){
      printf("%lf", scores[i]);
      freeGraph(parents[i]);
      if(i != n - 1){
        printf(", ");
      }
    }
    printf("] - %lf validation. %lf%% invalid.\n", validation_score, (double)invalids / (double)(n * l * generations));
    double winner_score = gp_evaluate_mse(validation_best, test_data, fset);
    freeGraph(validation_best);
    free(parents);
    free(scores);
    return winner_score;
  }
