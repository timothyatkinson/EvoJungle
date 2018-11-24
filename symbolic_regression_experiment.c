#include "evaluate.h"
#include "genetic_operators.h"
#include "function_set.h"
#include "individual_util.h"
#include "ea.h"

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


int main(void){
  //Reset random seed.
  srand(time(NULL));

  Function_Set* fset = get_common_fset("add,sub,mul,div,exp,log,sqrt,tanh,sin");

  char** d_names = dataset_names();
  int* d_inputs = dataset_inputs();

  int train_entries = 700;
  int validation_entries = 300;
  int test_entries = 50000;
  int runs = 100;

  double** res = malloc(42 * sizeof(double*));

  for(int i = 0; i < 21; i++){

    res[i * 2] = malloc(runs * sizeof(double));
    res[(i * 2) + 1] = malloc(runs * sizeof(double));

    char train[50];
    char validation[50];
    char test[50];
    strcpy(train, d_names[i]);
    strcpy(validation, d_names[i]);
    strcpy(test, d_names[i]);
    strcat(train, "TrainingT1000V30.txt");
    strcat(validation, "ValidationT1000V30.txt");
    strcat(test, "Test.txt");
    printf("Running on files %s, %s, %s\n", train, validation, test);

    printf("Loading Datasets\n");
    //No noise
    GP_Dataset* train_d = load_sr_dataset(train, d_inputs[i], train_entries, 0);
    GP_Dataset* validation_d = load_sr_dataset(validation, d_inputs[i], validation_entries, 0);
    GP_Dataset* test_d = load_sr_dataset(test, d_inputs[i], test_entries, 0);
    //Noise
    GP_Dataset* train_d_n = load_sr_dataset(train, d_inputs[i], train_entries, 2);
    GP_Dataset* validation_d_n = load_sr_dataset(validation, d_inputs[i], validation_entries, 2);
    GP_Dataset* test_d_n = load_sr_dataset(test, d_inputs[i], test_entries, 0);

    printf("Running - No Noise\n");
    for(int j = 0; j < runs; j++){
      printf("Run %d\n", j);
      double test_mse = tournament_elitism(train_d, validation_d, test_d, fset, 100, 10, 10, 0.9, 0.02, 500, 4, 50);
      printf("Final test MSE = %.10e\n", test_mse);
      res[2 * i][j] = test_mse;
    }

    printf("Running - Noise\n");
    for(int j = 0; j < runs; j++){
      printf("Run %d\n", j);
      double test_mse = tournament_elitism(train_d_n, validation_d_n, test_d_n, fset, 100, 10, 10, 0.9, 0.02, 500, 4, 50);
      printf("Final test MSE = %.10e\n", test_mse);
      res[(2 * i) + 1][j] = test_mse;
    }

    printf("Freeing Datasets\n");
    free_dataset(train_d);
    free_dataset(validation_d);
    free_dataset(test_d);
    free_dataset(train_d_n);
    free_dataset(validation_d_n);
    free_dataset(test_d_n);
  }

  print_to_csv_file("Results/symres_results.csv", res, 42, 100);

  free_dataset_names(d_names);
  free(d_inputs);
}
