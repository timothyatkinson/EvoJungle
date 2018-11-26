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
  int pop_size, int tournament_size, int generations){

    //Generation 0. Initialise population.
    int generation = 0;
    Graph** population = malloc(pop_size * sizeof(Graph*));
    double* scores = malloc(pop_size * sizeof(Graph*));
    int elite_index = -1;
    double elite_score;
    Graph* best_found = NULL;
    double best_score;
    for(int i = 0; i < pop_size; i++){
      population[i] = initialise_individual(train_data->inputs, init_nodes, train_data->outputs, fset, max_depth);
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

    generation++;

    printf("Init generation: %d individuals. Elite score %lf, Best score %lf\n", pop_size, elite_score, best_score);
    while(generation < generations){

      Graph** new_pop = malloc(pop_size * sizeof(Graph*));
      double* new_scores = malloc(pop_size * sizeof(double));

      for(int i = 0; i < pop_size; i++){
        //Copy elite individual. Will never get better elite score or validation score than existing ones!
        if(i == elite_index){
          new_pop[i] = duplicate_graph(population[i]);
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
            if(pop_size == 5){
              p1 = elite_index;
            }
            else{
              p1 = tournament(scores, pop_size, tournament_size);
            }

            new_pop[i] = mutate_individual(population[p1], fset, mutation_rate, max_depth);
            strip_neutral(new_pop[i], max_neutral);
          }
        }
        new_scores[i] = gp_evaluate_mse(new_pop[i], train_data, fset);
      }

      //Update elite and best scores.
      int new_elite = elite_index;
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
      if(generation%10 == 0 || generation + 1 == generations){
        char c = '\n';
        if(generations > 1350){
          c = '\r';
        }
        printf("Generation %d: %d individuals. Elite score %lf, Best score %lf%c", generation, pop_size, elite_score, best_score, c);
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
