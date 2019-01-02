#include "evaluate.h"
#include "genetic_operators.h"
#include "function_set.h"
#include "individual_util.h"
#include "horizontal_ea.h"

char** dataset_names();
char** dataset_names(){
  char** ret = malloc(21 * sizeof(char*));
  ret[0] = "Datasets/F1";
  ret[1] = "Datasets/F2";
  ret[2] = "Datasets/F3";
  ret[3] = "Datasets/F4";
  ret[4] = "Datasets/F5";
  ret[5] = "Datasets/F6";
  ret[6] = "Datasets/F7";
  ret[7] = "Datasets/F8";
  ret[8] = "Datasets/F9";
  ret[9] = "Datasets/F10";
  ret[10] = "Datasets/F11";
  ret[11] = "Datasets/F12";
  ret[12] = "Datasets/F13";
  ret[13] = "Datasets/F14";
  ret[14] = "Datasets/F15";
  ret[15] = "Datasets/F16";
  ret[16] = "Datasets/F17";
  ret[17] = "Datasets/F18";
  ret[18] = "Datasets/F19";
  ret[19] = "Datasets/F20";
  ret[20] = "Datasets/F21";
  return ret;
}

void free_dataset_names(char** names);
void free_dataset_names(char** names){
  free(names);
}

int* dataset_inputs();
int* dataset_inputs(){
  int* ret = malloc(21 * sizeof(int));
  ret[0] = 2;
  ret[1] = 2;
  ret[2] = 5;
  ret[3] = 3;
  ret[4] = 2;
  ret[5] = 2;
  ret[6] = 2;
  ret[7] = 2;
  ret[8] = 2;
  ret[9] = 2;
  ret[10] = 2;
  ret[11] = 10;
  ret[12] = 5;
  ret[13] = 6;
  ret[14] = 5;
  ret[15] = 5;
  ret[16] = 5;
  ret[17] = 5;
  ret[18] = 5;
  ret[19] = 5;
  ret[20] = 5;
  return ret;
}

void print_to_csv_file(char* file_path, double** data, int columns, int rows);
void print_to_csv_file(char* file_path, double** data, int columns, int rows){
  FILE* f = fopen(file_path, "w");
  printf("Writing to File %s\n", file_path);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < columns; j++){
      fprintf(f, "%lf\t", data[j][i]);
    }
    fprintf(f, "\n");
  }
  for(int i = 0; i < columns; i++){
    free(data[i]);
  }
  free(data);
  fclose(f);
}


int main(int argc, char **argv){
  //Reset random seed.
  srand(time(NULL));

  Function_Set* fset = get_common_fset("add,sub,mul,div,exp,log,sqrt,tanh,sin");

  char** d_names = dataset_names();
  int* d_inputs = dataset_inputs();

  int train_entries = 1000;
  int validation_entries = 1000;
  int test_entries = 50000;
  int runs = 100;

  int evals = 24950;
  int n;
  sscanf (argv[1],"%d",&n);
  int l;
  sscanf (argv[2],"%d",&l);
  int x;
  sscanf (argv[3],"%d",&x);
  double hoz_rate = (double)x / 10.0;
  int y;
  sscanf (argv[4],"%d",&y);
  double m_rate = (double)y / 10.0;
  int d;
  sscanf (argv[5],"%d",&d);
  int init_search;
  sscanf (argv[6],"%d",&init_search);

  int max_gens = (evals - init_search) / (n * l);

  init_search = init_search / n;

  printf("Running experiments with n = %d, l = %d max gens = %d, init_search = %d, horizontal rate = %lf, mutation rate = %lf\n", n, l, max_gens, init_search, hoz_rate, m_rate);

  double** res = malloc(42 * sizeof(double*));

  for(int i = d; i < 21; i++){
    double targ = 0.5;
    if(i == 0){
      targ = 0.005;
    }
    else if (i == 2){
      targ = 0.0115;
    }
    res[i * 2] = malloc(runs * sizeof(double));
    res[(i * 2) + 1] = malloc(runs * sizeof(double));

    char train[50];
    char validation[50];
    char test[50];
    char out[50];
    strcpy(train, d_names[i]);
    strcpy(validation, d_names[i]);
    strcpy(test, d_names[i]);
    strcpy(out, d_names[i]);
    strcat(train, "TrainingT1000V0.txt");
    strcat(validation, "TrainingT1000V0.txt");
    strcat(test, "Test.txt");
    strcat(out, "Results.csv");
    out[0] = 'R';
    out[1] = 'e';
    out[2] = 's';
    out[3] = 'u';
    out[4] = 'l';
    out[5] = 't';
    out[6] = 'H';
    out[7] = 'E';
    printf("Running on files %s, %s, %s -> %s\n", train, validation, test, out);


    double** this_res = malloc(2 * sizeof(double*));
    this_res[0] = malloc(runs * sizeof(double));
    this_res[1] = malloc(runs * sizeof(double));


    printf("Loading Datasets\n");
    //No noise
    GP_Dataset** datasets = load_all_datasets(test, d_inputs[i], 0);
    GP_Dataset* train_d = load_sr_dataset(train, d_inputs[i], train_entries, 0);
    GP_Dataset* validation_d = datasets[1];
    GP_Dataset* test_d = datasets[2];
    free_dataset(datasets[0]);
    free(datasets);


    printf("Running - No Noise\n");
    for(int j = 0; j < runs; j++){
      printf("Run %d\n", j);
      double test_mse = horizontal_ea(train_d, validation_d, test_d, fset, 100, 10, 50, m_rate, 0.0, hoz_rate, n, l, 100000, evals, init_search);
      printf("\nFinal test MSE = %.10e\n", test_mse);
      res[2 * i][j] = test_mse;
      this_res[0][j] = res[2 * i][j];
      int count = 0;
      res[2 * i][j] = test_mse;
      this_res[0][j] = res[2 * i][j];
      for(int k = 0; k <= j; k++){
        if(this_res[0][k] < targ){
          count++;
        }
      }
      printf("Final test MSE = %.10e\n", test_mse);
      printf("%d:%d, %lf%%\n", count, (j + 1) - count, (double)count / (double)(j + 1));
    }

    for(int j = 0; j < runs; j++){
      //double test_mse = horizontal_ea(train_d_n, test_d_n, fset, 100, 10, 50, m_rate, 0.0, hoz_rate, n, l, max_gens);
      double test_mse = -1.0;
      res[(2 * i) + 1][j] = test_mse;
      this_res[1][j] = res[(2 * i) + 1][j];
    }

    printf("Freeing Datasets\n");
    free_dataset(train_d);
    free_dataset(validation_d);
    free_dataset(test_d);

    print_to_csv_file(out, this_res, 2, runs);
  }

  print_to_csv_file("Results/symres_no_crossover_results.csv", res, 42, 100);

  free_dataset_names(d_names);
  free(d_inputs);
}
