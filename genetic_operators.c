#include "genetic_operators.h"

#include "GP2_Files/init_individual/init_individual.h"
#include "GP2_Files/mutate_edge/mutate_edge.h"
#include "GP2_Files/mutate_node/mutate_node.h"
#include "GP2_Files/local_node_crossover/local_node_crossover.h"
#include "GP2_Files/local_edge_crossover/local_edge_crossover.h"
#include "GP2_Files/remove_depth/remove_depth.h"
#include "GP2_Files/neutral_cap/neutral_cap.h"


//Util functions to prepare and clean a graph in the mutation procedure eggp_mutate
static void prepare_graph_mutate(Graph* host, Function_Set* fset, int depth);
static void clean_graph_mutate(Graph* host);

//Util functions to prepare and clean a graph in the intialisation procedure eggp_init
static void prepare_graph_init(Graph* host, Function_Set* fset, int inputs, int outputs, int nodes, int depth);
static void clean_graph_init(Graph* host);

static void prepare_neutral_cap(Graph* host, int cap);


//Util function for preparing a graph for generating a EGGP individual
static void prepare_graph_init(Graph* host, Function_Set* fset, int inputs, int outputs, int nodes, int depth){
  /* Initialise host graph */
  /* INPUTS */
  for(int i = 0; i < inputs; i++){
    //Add a node for each input labelled i:"IN" where i is the number of the input and "IN" indicates that it is indeed an input
    HostAtom array[3];
    HostLabel label;
    array[0].type = 'i';
    array[0].num = i;
    array[1].type = 'i';
    array[1].num = 1;
    array[2].type = 's';
    array[2].str = "IN";
    HostList *list = makeHostList(array, 3, false);
    label = makeHostLabel(0, 3, list);
    addNode(host, 0, label);
  }

  /* OUTPUTS */
  for(int i = 0; i < outputs; i++){
    //Add a node for each output labelled i:"OUT" where i is the number of the output and "OUT" indicates that it is indeed an output
    HostAtom array[2];
    HostLabel label;
    array[0].type = 'i';
    array[0].num = i;
    array[1].type = 's';
    array[1].str = "OUT";
    HostList *list = makeHostList(array, 2, false);
    label = makeHostLabel(0, 2, list);
    addNode(host, 0, label);
  }

  /* FUNCTIONSET */
  Function* f = fset->first;
  for(int i = 0; i < fset->functionCount; i++){
    //Add a rooted node for each function labelled "FunctionSet":f:a where f is the string representation of the function and a is the arity.
     HostAtom array[3];
     HostLabel label;
     array[0].type = 's';
     array[0].str = "FunctionSet";
     array[1].type = 's';
     array[1].str = f->name;
     array[2].type = 'i';
     array[2].num = f->arity;
     HostList *list = makeHostList(array, 3, false);
     label = makeHostLabel(0, 3, list);
     addNode(host, 1, label);
     f = f->next;
  }

  /* NODES */
  //Add a rooted node labelled "Nodes":n where n is the number of nodes to add.
   HostAtom array[2];
   HostLabel label;
   array[0].type = 's';
   array[0].str = "Nodes";
   array[1].type = 'i';
   array[1].num = nodes;
   HostList *list = makeHostList(array, 2, false);
   label = makeHostLabel(0, 2, list);
   addNode(host, 1, label);

   /* NODES */
   //Add a rooted node labelled "Depth":n where n is the max depth of nodes to add.
    HostAtom array2[2];
    HostLabel label2;
    array2[0].type = 's';
    array2[0].str = "Depth";
    array2[1].type = 'i';
    array2[1].num = depth;
    HostList *list2 = makeHostList(array2, 2, false);
    label2 = makeHostLabel(0, 2, list2);
    addNode(host, 1, label2);
}

static void clean_graph_init(Graph* host){
  /* REMOVE FUNCTION SET AND NODES COUNTER. These are the only rooted nodes. */
  for(int i = 0; i < host->nodes.size; i++){
     Node *host_node = getNode(host, i);
   if(host_node == NULL) continue;
   if(!host_node->root) continue;
   removeNode(host, i);
  }
}

//Util function for preparing a graph for mutating a EGGP_DC individual
static void prepare_graph_mutate(Graph* host, Function_Set* fset, int depth){
  /* Initialise host graph */
  /* FUNCTIONSET */
  Function* f = fset->first;
  for(int i = 0; i < fset->functionCount; i++){
    //Add a rooted node for each function labelled "FunctionSet":f:a where f is the string representation of the function and a is the function's arity.
     HostAtom array[3];
     HostLabel label;
     array[0].type = 's';
     array[0].str = "FunctionSet";
     array[1].type = 's';
     array[1].str = f->name;
     array[2].type = 'i';
     array[2].num = f->arity;
     HostList *list = makeHostList(array, 3, false);
     label = makeHostLabel(0, 3, list);
     addNode(host, 1, label);
     f = f->next;
  }
  /* NODES */
  //Add a rooted node labelled "Depth":n where n is the max depth of nodes to add.
  HostAtom array2[2];
  HostLabel label2;
  array2[0].type = 's';
  array2[0].str = "Depth";
  array2[1].type = 'i';
  array2[1].num = depth;
  HostList *list2 = makeHostList(array2, 2, false);
  label2 = makeHostLabel(0, 2, list2);
  addNode(host, 1, label2);
}
//Util function for preparing a graph for mutating a EGGP_DC individual
static void prepare_neutral_cap(Graph* host, int max_neutral){
  /* NODES */
  //Add a rooted node labelled "Depth":n where n is the max depth of nodes to add.
  HostAtom array2[2];
  HostLabel label2;
  array2[0].type = 's';
  array2[0].str = "MaxNeutral";
  array2[1].type = 'i';
  array2[1].num = max_neutral;
  HostList *list2 = makeHostList(array2, 2, false);
  label2 = makeHostLabel(0, 2, list2);
  addNode(host, 1, label2);
}

static void clean_graph_mutate(Graph* host){
  /* REMOVE FUNCTION SET AND NODES COUNTER. These are the only rooted nodes. */
  for(int i = 0; i < host->nodes.size; i++){
   Node *host_node = getNode(host, i);
   if(host_node == NULL) continue;
   if(!host_node->root) continue;
   removeNode(host, i);
  }
}

//Generates a population of EGGP individuals.
Graph* initialise_individual(int inputs, int nodes, int outputs, Function_Set* fset, int max_depth){

  Graph* ind = build_empty_host_graph();

  prepare_graph_init(ind, fset, inputs, outputs, nodes, max_depth);

  init_individual_execute(ind);

  clean_graph_init(ind);

  return ind;
}

//Mutates a EGGP individual (copies the individual, rather than overwriting).
Graph* mutate_individual(Graph* host, Function_Set* fset, double mutation_rate, int max_depth){
  //Copy the individual to mutate
  Graph* new_graph = duplicate_graph(host);

  //Prepare the graph by loading in function set
  int nodes = new_graph->number_of_nodes;
  int edges = new_graph->number_of_edges;
  int mutations = 0;
  int num = new_graph->nodes.size + new_graph->edges.size;
  for(int i = 0; i < num; i++){
    double r = ((double)rand() / (double)RAND_MAX);
    if(r <= mutation_rate){
      double r2 = ((double)rand() / (double)RAND_MAX);
      if(r2 <= ((double)edges / (double)(num))){
      Graph* old = duplicate_graph(host);
      make_depth(old);
      prepare_graph_mutate(old, fset, max_depth);
        int x = 0;
        if(depth(new_graph) > max_depth){
          x = 1;
        }
        make_depth(new_graph);
        prepare_graph_mutate(new_graph, fset, max_depth);
        mutate_edge_execute(new_graph);
        clean_graph_mutate(new_graph);
        remove_depth_execute(new_graph);
        mutations++;
        if(x == 0 && depth(new_graph) > max_depth){
          printf("\nEdge mutation (%d)\n", depth(new_graph));
          mark_active_blue(old);
          printfGraph(old);
          printf("=>\n");
          make_depth(new_graph);
          mark_active_blue(new_graph);
          printfGraph(new_graph);
          exit(0);
        }
        freeGraph(old);
      }
      else{
      Graph* old = duplicate_graph(host);
      make_depth(old);
      prepare_graph_mutate(old, fset, max_depth);
        int x = 0;
        if(depth(new_graph) > max_depth){
          x = 1;
        }
        make_depth(new_graph);
        prepare_graph_mutate(new_graph, fset, max_depth);
        mutate_node_execute(new_graph);
        mutations++;
        if(x == 0 && depth(new_graph) > max_depth){
          printf("\nNode mutation (%d)\n", depth(new_graph));
          printfGraph(old);
          printf("=>\n");
          printfGraph(new_graph);

        }
        clean_graph_mutate(new_graph);
        remove_depth_execute(new_graph);
        freeGraph(old);
      }
    }
  }

  if(mutations == 0){
    double r = ((double)rand() / (double)RAND_MAX);
    if(r <= ((double)edges / (double)(num))){
    Graph* old = duplicate_graph(host);
    make_depth(old);
    prepare_graph_mutate(old, fset, max_depth);
      int x = 0;
      if(depth(new_graph) > max_depth){
        x = 1;
      }
      make_depth(new_graph);
      prepare_graph_mutate(new_graph, fset, max_depth);
      mutate_edge_execute(new_graph);
      clean_graph_mutate(new_graph);
      remove_depth_execute(new_graph);
      mutations++;
      if(x == 0 && depth(new_graph) > max_depth){
        printf("\nEdge mutation (%d)\n", depth(new_graph));
        mark_active_blue(old);
        printfGraph(old);
        printf("=>\n");
        make_depth(new_graph);
        mark_active_blue(new_graph);
        printfGraph(new_graph);
        exit(0);
      }
      freeGraph(old);
    }
    else{
      make_depth(new_graph);
      prepare_graph_mutate(new_graph, fset, max_depth);
      mutate_node_execute(new_graph);
      clean_graph_mutate(new_graph);
      remove_depth_execute(new_graph);
    }
  }

  return new_graph;
}


Graph* local_edge_crossover(Graph* p1, Graph* p2, int max_depth){
  make_depth(p1);
  make_depth(p2);
  Graph* U = disjoint_union(p1, p2);
  remove_depth_execute(p1);
  remove_depth_execute(p2);
   /* NODES */
   //Add a rooted node labelled "Depth":n where n is the max depth of nodes to add.
  HostAtom array2[2];
  HostLabel label2;
  array2[0].type = 's';
  array2[0].str = "Depth";
  array2[1].type = 'i';
  array2[1].num = max_depth;
  HostList *list2 = makeHostList(array2, 2, false);
  label2 = makeHostLabel(0, 2, list2);
  addNode(U, 1, label2);

  local_edge_crossover_execute(U);
  clean_graph_mutate(U);
  Graph* child = get_red(U);
  remove_depth_execute(child);
  freeGraph(U);
  return child;
}

Graph* local_node_crossover(Graph* p1, Graph* p2, int max_depth){
  make_depth(p1);
  make_depth(p2);
  Graph* U = disjoint_union(p1, p2);
  remove_depth_execute(p1);
  remove_depth_execute(p2);
   /* NODES */
   //Add a rooted node labelled "Depth":n where n is the max depth of nodes to add.
  HostAtom array2[2];
  HostLabel label2;
  array2[0].type = 's';
  array2[0].str = "Depth";
  array2[1].type = 'i';
  array2[1].num = max_depth;
  HostList *list2 = makeHostList(array2, 2, false);
  label2 = makeHostLabel(0, 2, list2);
  addNode(U, 1, label2);

  local_node_crossover_execute(U);
  clean_graph_mutate(U);
  Graph* child = get_red(U);
  remove_depth_execute(child);
  freeGraph(U);
  return child;
}

void strip_neutral(Graph* host, int neutral_cap){
  prepare_neutral_cap(host, neutral_cap);
  neutral_cap_execute(host);
  clean_graph_mutate(host);
}
