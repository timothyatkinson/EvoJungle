#include "genetic_operators.h"

#include "GP2_Files/init_individual/init_individual.h"
#include "GP2_Files/mutate_edge/mutate_edge.h"
#include "GP2_Files/mutate_node/mutate_node.h"
#include "GP2_Files/local_node_crossover/local_node_crossover.h"
#include "GP2_Files/local_edge_crossover/local_edge_crossover.h"
#include "GP2_Files/remove_depth/remove_depth.h"
#include "GP2_Files/neutral_cap/neutral_cap.h"
#include "GP2_Files/horizontal/horizontal.h"

#include "rand_util.h"

//Util functions to prepare and clean a graph in the mutation procedure eggp_mutate
static void prepare_graph_mutate(Graph* host, Function_Set* fset, int depth);
static void clean_graph_mutate(Graph* host);

//Util functions to prepare and clean a graph in the intialisation procedure eggp_init
static void prepare_graph_init(Graph* host, Function_Set* fset, int inputs, int outputs, int nodes, int depth);
static void clean_graph_init(Graph* host);

static void prepare_neutral_cap(Graph* host, int cap);

void print_invalid(Graph* p1, Node* v, int max_depth);

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

//Mutates a EGGP individual
int mutate_individual(Graph* new_graph, Function_Set* fset, double m_rate, int max_depth){

  //double mutation_rate = m_rate / (double)(count_active_nodes(new_graph, count_inputs(new_graph), count_outputs(new_graph)) + count_active_edges(new_graph));
  double mutation_rate = m_rate / 100.0;

  //Prepare the graph by loading in function set
  int nodes = new_graph->number_of_nodes;
  int edges = new_graph->number_of_edges;
  int mutations = 0;
  int num = new_graph->nodes.size + new_graph->edges.size;
  int active_mutation = 0;
  for(int i = 0; i < num; i++){
    double r = ((double)rand() / (double)RAND_MAX);
    if(r <= mutation_rate){
      double r2 = ((double)rand() / (double)RAND_MAX);
      if(r2 <= ((double)edges / (double)(num))){
      // Graph* old = duplicate_graph(host);
      // make_depth(old);
      // prepare_graph_mutate(old, fset, max_depth);
      //   int x = 0;
      //   if(depth(new_graph) > max_depth){
      //     x = 1;
      //   }
      //   make_depth(new_graph);
      //   prepare_graph_mutate(new_graph, fset, max_depth);
      //   mutate_edge_execute(new_graph);
      //   clean_graph_mutate(new_graph);
      //   remove_depth_execute(new_graph);
      //   mutations++;
      //   if(x == 0 && depth(new_graph) > max_depth){
      //     printf("\nEdge mutation (%d)\n", depth(new_graph));
      //     mark_active_blue(old);
      //     printfGraph(old);
      //     printf("=>\n");
      //     make_depth(new_graph);
      //     mark_active_blue(new_graph);
      //     printfGraph(new_graph);
      //     exit(0);
      //   }
      //   freeGraph(old);
        int active = edge_mutation_fast(new_graph, max_depth);
        if(active == 1){
          active_mutation = 1;
        }
      }
      else{
      // Graph* old = duplicate_graph(host);
      // make_depth(old);
      // prepare_graph_mutate(old, fset, max_depth);
      //   int x = 0;
      //   if(depth(new_graph) > max_depth){
      //     x = 1;
      //   }
      //   make_depth(new_graph);
      //   prepare_graph_mutate(new_graph, fset, max_depth);
      //   mutate_node_execute(new_graph);
      //   mutations++;
      //   if(x == 0 && depth(new_graph) > max_depth){
      //     printf("\nNode mutation (%d)\n", depth(new_graph));
      //     printfGraph(old);
      //     printf("=>\n");
      //     printfGraph(new_graph);
      //
      //   }
      //   clean_graph_mutate(new_graph);
      //   remove_depth_execute(new_graph);
      //   freeGraph(old);
        int active = node_mutation_fast(new_graph, fset, max_depth);
        if(active == 1){
          active_mutation = 1;
        }
      }
    }
  }

  if(mutations == 0){
    double r = ((double)rand() / (double)RAND_MAX);
    if(r <= ((double)edges / (double)(num))){
    // Graph* old = duplicate_graph(host);
    // make_depth(old);
    // prepare_graph_mutate(old, fset, max_depth);
    //   int x = 0;
    //   if(depth(new_graph) > max_depth){
    //     x = 1;
    //   }
    //   make_depth(new_graph);
    //   prepare_graph_mutate(new_graph, fset, max_depth);
    //   mutate_edge_execute(new_graph);
    //   clean_graph_mutate(new_graph);
    //   remove_depth_execute(new_graph);
    //   mutations++;
    //   if(x == 0 && depth(new_graph) > max_depth){
    //     printf("\nEdge mutation (%d)\n", depth(new_graph));
    //     mark_active_blue(old);
    //     printfGraph(old);
    //     printf("=>\n");
    //     make_depth(new_graph);
    //     mark_active_blue(new_graph);
    //     printfGraph(new_graph);
    //     exit(0);
    //   }
    //   freeGraph(old);
      int active = edge_mutation_fast(new_graph, max_depth);
      if(active == 1){
        active_mutation = 1;
      }
    }
    else{
      // make_depth(new_graph);
      // prepare_graph_mutate(new_graph, fset, max_depth);
      // mutate_node_execute(new_graph);
      // clean_graph_mutate(new_graph);
      // remove_depth_execute(new_graph);
        int active = node_mutation_fast(new_graph, fset, max_depth);
        if(active == 1){
          active_mutation = 1;
        }
    }
  }

  return active_mutation;
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

int edge_mutation_fast(Graph* p1, int max_depth){


  //Mark the graph with depth. Linear time.
  make_depth(p1);

  Graph* copy = duplicate_graph(p1);

  //Pick an edge to mutate uniformly at random. O(1)
  int edge = random_integer(0, p1->number_of_edges);

  //Find this edge. O(e)
  Edge* e = NULL;
  int up_to = 0;
  for(int i = 0; i < p1->edges.size; i++){
    Edge* e2 = getEdge(p1, i);
    if(e2 == NULL || e2->index == -1) continue;
    if(up_to == edge){
       e = e2;
     }
     up_to++;
   }

   if(e == NULL){
     printf("Exception: %dth edge not found!\n", edge);
     exit(0);
   }

   int mutate_source = e->source;
   int mutate_target = e->target;

   Node* actual_source = getNode(p1, mutate_source);
   mark_active_blue(p1);
   int active = 0;
   if(actual_source->label.mark == 3){
     active = 1;
   }
   unmark_graph(p1);
   HostLabel source_label = actual_source->label;
   HostListItem* depthDown = source_label.list->last->prev->prev;
   HostListItem* depthUp = source_label.list->last->prev;
   int source_down = depthDown->atom.num;
   int source_up = depthUp->atom.num;

   //Topological sort will allow us to find all invalid mutations in linear time O(v + e). It also handily gives us a enumeratable array of actual nodes, ignoring holes.
   int* top = reverse_topological_sort(p1);
   int* invalid = malloc(p1->nodes.size * sizeof(int));
   int num_valid = p1->number_of_nodes - 2;
   //Initially all nodes are valid. O(v)
   for(int i = 0; i < p1->nodes.size; i++){
     invalid[i] = 0;
   }


    //Find index of source in topological sort. Linear time O(v)
    int top_source = -1;
    int top_target = -1;
    for(int i = 0; i < p1->number_of_nodes; i++){
      if(top[i] == mutate_source){
        top_source = i;
      }
      if(top[i] == mutate_target){
        top_target = i;
      }
    }

    if(top_source == -1){
      printf("Exception %dth source node not found!\n", mutate_source);
      exit(0);
    }
    if(top_target == -1){
      printf("Exception %dth target node not found!\n", mutate_target);
      exit(0);
    }


   invalid[mutate_source] = 1;
   invalid[mutate_target] = 1;

   //Move rightwards in the reverse topological sorting (up the jungle), eliminating any node v with a path to the source, any output node, and any node which might introduce unacceptable depth. Linear time O(v + e)
   for(int i = 0; i < p1->number_of_nodes; i++){
     //Find the node
      Node* v = getNode(p1, top[i]);
      HostLabel label = v->label;

     //Any node with a path to the source is invalid. So we can propagate based on incoming edges. Because we have topological sorted, i must be greater than the topological index of the source.
     if(i >= top_source && invalid[top[i]] == 1){
       for(int counter = 0; counter < v->in_edges.size + 2; counter++)
        {
          Edge *host_edge = getNthInEdge(p1, v, counter);
          if(host_edge == NULL || host_edge->index == -1) continue;
          if(invalid[host_edge->source] != 1){
            invalid[host_edge->source] = 1;
            num_valid--;
          }
        }
     }

     //All output nodes are invalid.
     HostListItem *item = label.list->last;
     if(item->atom.type == 's' && strcmp(item->atom.str, "OUT") == 0 && invalid[top[i]] != 1){
       invalid[top[i]] = 1;
       num_valid--;
     }

     //Nodes with invalid depth are removed.
     HostListItem* dD = item->prev->prev;
     HostListItem* dU = item->prev;
     int cand_dD = dD->atom.num;
     int cand_dU = dU->atom.num;
     if(cand_dD + source_up > max_depth && invalid[top[i]] != 1){
       invalid[top[i]] = 1;
       num_valid--;
     }
   }

   //Only proceed if we can manage to do a valid mutation.
   if(num_valid > 0){
     int new_target = random_integer(0, num_valid);

     Node* new = NULL;
     //Find the new target. O(n)
     int up_to = 0;
     for(int i = 0; i < p1->nodes.size; i++){
       Node* node = getNode(p1, i);
       if(node == NULL || node->index == -1 || invalid[node->index] == 1) continue;
       if(up_to == new_target){
         new = node;
       }
       up_to++;
     }

     if(new == NULL){
       exit(0);
     }

     //Actually perform the mutation.
     addEdge(p1, makeHostLabel(e->label.mark, e->label.length, copyHostList(e->label.list)), mutate_source, new->index);
     removeEdge(p1, e->index);

     if(depth(p1) > max_depth){
       printf("Exception: Edge mutation (%d->%d) -> (%d->%d) introduced depth greater than %d. Target is invalid? %d\n", mutate_source, mutate_target, mutate_source, new->index, max_depth, invalid[new->index]);
       printf("Old graph:\n");
       printfGraph(copy);
       remove_depth_execute(p1);
       make_depth(p1);
       printfGraph(p1);
       print_invalid(copy, actual_source, max_depth);
       exit(0);
     }
   }

   remove_depth_execute(p1);
   freeGraph(copy);
   free(top);
   free(invalid);
   return active;
}

void print_invalid(Graph* p1, Node* v, int max_depth){
  printf("Printing invalid targets with respect to node %d\n", v->index);
  Node* actual_source = v;
  int mutate_source = v->index;
  HostLabel source_label = actual_source->label;
  HostListItem* depthDown = source_label.list->last->prev->prev;
  HostListItem* depthUp = source_label.list->last->prev;
  int source_down = depthDown->atom.num;
  int source_up = depthUp->atom.num;

  //Topological sort will allow us to find all invalid mutations in linear time O(v + e). It also handily gives us a enumeratable array of actual nodes, ignoring holes.
  int* top = reverse_topological_sort(p1);
  int* invalid = malloc(p1->nodes.size * sizeof(int));
  int num_valid = p1->number_of_nodes - 2;
  //Initially all nodes are valid. O(v)
  for(int i = 0; i < p1->nodes.size; i++){
    invalid[i] = 0;
  }

  printf("Topological sort is:\n");
  printf("[");
  for(int i = 0; i < p1->number_of_nodes; i++){
    printf("%d", top[i]);
    if(i != p1->number_of_nodes - 1){
      printf(", ");
    }
  }
  printf("]\n");


   //Find index of source in topological sort. Linear time O(v)
   int top_source = -1;
   for(int i = 0; i < p1->number_of_nodes; i++){
     if(top[i] == mutate_source){
       top_source = i;
     }
   }

   if(top_source == -1){
     printf("Exception %dth node not found!\n", mutate_source);
     exit(0);
   }

   printf("Node %d is %dth in topological sort\n", v->index, top_source);

  invalid[mutate_source] = 1;

  //Move rightwards in the reverse topological sorting (up the jungle), eliminating any node v with a path to the source, any output node, and any node which might introduce unacceptable depth. Linear time O(v + e)
  for(int i = 0; i < p1->number_of_nodes; i++){
    //Find the node
     Node* v = getNode(p1, top[i]);
     HostLabel label = v->label;

    //Any node with a path to the source is invalid. So we can propagate based on incoming edges. Because we have topological sorted, i must be greater than the topological index of the source.
    if(i >= top_source && invalid[top[i]] == 1){
      for(int counter = 0; counter < v->in_edges.size + 2; counter++)
       {
         Edge *host_edge = getNthInEdge(p1, v, counter);
         if(host_edge == NULL || host_edge->index == -1) continue;
         if(invalid[host_edge->source] != 1){
           invalid[host_edge->source] = 1;
           printf("%d is invalid with respect to acyclicty.\n", host_edge->source);
           num_valid--;
         }
       }
    }

    //All output nodes are invalid.
    HostListItem *item = label.list->last;
    if(item->atom.type == 's' && strcmp(item->atom.str, "OUT") == 0 && invalid[top[i]] != 1){
      invalid[top[i]] = 1;
      printf("%d is invalid as it is an output.\n", top[i]);
      num_valid--;
    }

    //Nodes with invalid depth are removed.
    HostListItem* dD = item->prev->prev;
    HostListItem* dU = item->prev;
    int cand_dD = dD->atom.num;
    int cand_dU = dU->atom.num;
    if(cand_dD + source_up > max_depth && invalid[top[i]] != 1){
      invalid[top[i]] = 1;
      printf("%d is invalid with respect to depth\n", top[i]);
      num_valid--;
    }
  }
}

int node_mutation_fast(Graph* p1, Function_Set* fset, int max_depth){

  int inputs = count_inputs(p1);
  int outputs = count_outputs(p1);
  //Mark the graph with depth. Linear time.
  make_depth(p1);


  //Pick an node to mutate uniformly at random. O(1)
  int node = random_integer(0, p1->number_of_nodes - (inputs + outputs));

  //Find this Node. O(v)
  Node* v = NULL;
  int up_to = 0;
  for(int i = 0; i < p1->nodes.size; i++){
    Node* v2 = getNode(p1, i);
    if(v2 == NULL || v2->index == -1) continue;

    HostLabel label = v2->label;
    HostListItem *item = label.list->last;
    if(item->atom.type != 's') break;
    if(strcmp(item->atom.str, "OUT") == 0 || strcmp(item->atom.str, "IN") == 0) continue;
    if(up_to == node){
       v = v2;
     }
     up_to++;
   }

   if(v == NULL){
     printf("Exception: %dth node not found!\n", node);
     exit(0);
   }


   HostLabel label = v->label;
   HostListItem *item = label.list->last;
   if(item->atom.type != 's'){
     printf("Exception: %dth node's final label item is not a string\n", node);
     exit(0);
   }

   char* func = item->atom.str;
   int new = random_integer(0, fset->functionCount - 1);

   Function* old_func = NULL;
   Function* new_func = NULL;

   up_to = 0;
   Function* first = fset->first;
   while(first != NULL){
     if(strcmp(first->name, func) == 0){
       old_func = first;
     }
     else{
       if(up_to == new){
         new_func = first;
       }
       up_to++;
     }
     first = first->next;
   }

   if(old_func == NULL){
     printf("Exception: could not find function represented by %s\n", func);
     exit(0);
   }
   if(new_func == NULL){
     printf("Exception: could not find new function %d\n", new);
     exit(0);
   }

   mark_active_blue(p1);
   int active = 0;
   if(v->label.mark == 3){
     active = 1;
   }
   unmark_graph(p1);

   //Perform node mutation.
   free(item->atom.str);
   item->atom.str = strdup(new_func->name);

   //Delete random edges.
   if(v->outdegree > new_func->arity){
     while(v->outdegree > new_func->arity){
       //Pick edge.
       int delete = random_integer(0, v->outdegree);
       //Find edge.
       up_to = 0;
       Edge* del_edge = NULL;
       for(int counter = 0; counter < v->out_edges.size + 2; counter++)
       	{
       		Edge *host_edge = getNthOutEdge(p1, v, counter);
       		if(host_edge == NULL || host_edge->index == -1) continue;
          if(up_to == delete){
            del_edge = host_edge;
          }
          up_to++;
       	}
       if(del_edge == NULL){
         printf("Exception: could not find %d edge to delete\n", delete);
         exit(0);
       }
       //Delete edge.
       removeEdge(p1, del_edge->index);
     }
   }
   //Add random edges. We must preserve acyclicty, depth, and not targetting outputs.
   else if(v->outdegree < new_func->arity){

     Node* actual_source = v;
     int mutate_source = v->index;
     HostLabel source_label = actual_source->label;
     HostListItem* depthDown = source_label.list->last->prev->prev;
     HostListItem* depthUp = source_label.list->last->prev;
     int source_down = depthDown->atom.num;
     int source_up = depthUp->atom.num;

     //Topological sort will allow us to find all invalid mutations in linear time O(v + e). It also handily gives us a enumeratable array of actual nodes, ignoring holes.
     int* top = reverse_topological_sort(p1);
     int* invalid = malloc(p1->nodes.size * sizeof(int));
     int num_valid = p1->number_of_nodes - 2;
     //Initially all nodes are valid. O(v)
     for(int i = 0; i < p1->nodes.size; i++){
       invalid[i] = 0;
     }


      //Find index of source in topological sort. Linear time O(v)
      int top_source = -1;
      for(int i = 0; i < p1->number_of_nodes; i++){
        if(top[i] == mutate_source){
          top_source = i;
        }
      }

      if(top_source == -1){
        printf("Exception %dth node not found!\n", mutate_source);
        exit(0);
      }

     invalid[mutate_source] = 1;

     //Move rightwards in the reverse topological sorting (up the jungle), eliminating any node v with a path to the source, any output node, and any node which might introduce unacceptable depth. Linear time O(v + e)
     for(int i = 0; i < p1->number_of_nodes; i++){
       //Find the node
        Node* v = getNode(p1, top[i]);
        HostLabel label = v->label;

       //Any node with a path to the source is invalid. So we can propagate based on incoming edges. Because we have topological sorted, i must be greater than the topological index of the source.
       if(i >= top_source && invalid[top[i]] == 1){
         for(int counter = 0; counter < v->in_edges.size + 2; counter++)
          {
            Edge *host_edge = getNthInEdge(p1, v, counter);
            if(host_edge == NULL || host_edge->index == -1) continue;
            if(invalid[host_edge->source] != 1){
              invalid[host_edge->source] = 1;
              num_valid--;
            }
          }
       }

       //All output nodes are invalid.
       HostListItem *item = label.list->last;
       if(item->atom.type == 's' && strcmp(item->atom.str, "OUT") == 0 && invalid[top[i]] != 1){
         invalid[top[i]] = 1;
         num_valid--;
       }

       //Nodes with invalid depth are removed.
       HostListItem* dD = item->prev->prev;
       HostListItem* dU = item->prev;
       int cand_dD = dD->atom.num;
       int cand_dU = dU->atom.num;
       if(cand_dD + source_up > max_depth && invalid[top[i]] != 1){
         invalid[top[i]] = 1;
         num_valid--;
       }
     }

     while(v->outdegree < new_func->arity){
        //Only proceed if we can manage to do a valid addition.
        if(num_valid > 0){
          int new_target = random_integer(0, num_valid);

          Node* new = NULL;
          //Find the new target. O(n)
          up_to = 0;
          for(int i = 0; i < p1->nodes.size; i++){
            Node* node = getNode(p1, i);
            if(node == NULL || node->index == -1 || invalid[i] == 1) continue;
            if(up_to == new_target){
              new = node;
            }
            up_to++;
          }

          if(new == NULL){
            printf("Error: could not find %dth valid node.\n", new_target);
            exit(0);
          }

          //Actually perform the insertion.

          HostAtom array2[1];
          HostLabel label2;
          array2[0].type = 'i';
          array2[0].num = 0;
          HostList *list2 = makeHostList(array2, 1, false);
          label2 = makeHostLabel(0, 1, list2);
          addEdge(p1, label2, mutate_source, new->index);
        }
        else{
          printf("Exception: could not insert new edge!\n");
          printf("Mutate Node %d; %s->%s\n", v->index, old_func->name, new_func->name);
          printfGraph(p1);
          print_invalid(p1, v, max_depth);
          exit(0);
        }
      }
      free(top);
      free(invalid);
   }

   //Shuffle the node's inputs.
   int* new_order = random_order(v->outdegree);
   up_to = 0;
   Edge* del_edge = NULL;
   for(int counter = 0; counter < v->out_edges.size + 2; counter++)
    {
      Edge *host_edge = getNthOutEdge(p1, v, counter);
      if(host_edge == NULL || host_edge->index == -1) continue;
      HostList* l = host_edge->label.list;
      HostListItem* i = l->first;
      i->atom.num = new_order[up_to];
      up_to++;
    }

   free(new_order);

   remove_depth_execute(p1);

   return active;
}


// Graph* local_edge_crossover_fast(Graph* p1, Graph* p2, int max_depth){
//
//   makeDepth(p1);
//   makeDepth(p2);
//
//   //Pick crossover point 1.
//   int edge = random_integer(0, p1->number_of_edges);
//
//   //Find crossover point 1.
//   Edge* e;
//   int up_to = 0;
//   for(int i = 0; i < p1->edges.size; i++){
//     Edge* e2 = getEdge(p1, i);
//     if(e2 == NULL) continue;
//     up_to++;
//     if(up_to == edge){
//       e = e2;
//     }
//   }
//
//   Node* source = getNode(p1, e->source);
//   int source_depth_down = asd
// }

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

Graph* horizontal_gene_transfer(Graph* p1, Graph* p2){
  Graph* U = disjoint_union(p1, p2);
  horizontal_execute(U);
  Graph* new = get_red(U);
  freeGraph(U);
  return new;
}
