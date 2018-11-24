#include "individual_util.h"
#include "GP2_Files/depth_start/depth_start.h"

Graph* disjoint_union(Graph* red, Graph* blue){
  Graph *graph_copy = newGraph(150, 300);
  int node_mapping_red[red->nodes.size];
  int node_mapping_blue[blue->nodes.size];
  //Copy nodes
  for(int i = 0; i < red->nodes.size; i++){
     Node *host_node = getNode(red, i);
     if(host_node == NULL || host_node->index == -1) continue;
     node_mapping_red[i] = addNode(graph_copy, host_node->root, makeHostLabel(1, host_node->label.length, copyHostList(host_node->label.list)));
  }
  for(int i = 0; i < blue->nodes.size; i++){
     Node *host_node = getNode(blue, i);
     if(host_node == NULL || host_node->index == -1) continue;
     node_mapping_blue[i] = addNode(graph_copy, host_node->root, makeHostLabel(3, host_node->label.length, copyHostList(host_node->label.list)));
  }
  //Copy edges
  for(int i = 0; i < red->edges.size; i++){
     Edge *host_edge = getEdge(red, i);
     if(host_edge == NULL || host_edge->index == -1) continue;
     addEdge(graph_copy, makeHostLabel(1, host_edge->label.length, copyHostList(host_edge->label.list)), node_mapping_red[host_edge->source], node_mapping_red[host_edge->target]);
  }
  for(int i = 0; i < blue->edges.size; i++){
     Edge *host_edge = getEdge(blue, i);
     if(host_edge == NULL || host_edge->index == -1) continue;
     addEdge(graph_copy, makeHostLabel(3, host_edge->label.length, copyHostList(host_edge->label.list)), node_mapping_blue[host_edge->source], node_mapping_blue[host_edge->target]);
  }
  return graph_copy;
}

Graph* get_red(Graph* red_blue){
  return get_mark(red_blue, 1, 0);
}

Graph* get_blue(Graph* red_blue){
  return get_mark(red_blue, 3, 0);
}

Graph* get_mark(Graph* multi_mark, int mark, int target_mark){
  Graph *graph_copy = newGraph(150, 300);
  int node_mapping[multi_mark->nodes.size];
  //Copy nodes
  for(int i = 0; i < multi_mark->nodes.size; i++){
    node_mapping[i] = -1;
     Node *host_node = getNode(multi_mark, i);
     if(host_node == NULL || host_node->index == -1 || host_node->label.mark != mark) continue;
     node_mapping[i] = addNode(graph_copy, host_node->root, makeHostLabel(target_mark, host_node->label.length, copyHostList(host_node->label.list)));
  }
  //Copy edges
  for(int i = 0; i < multi_mark->edges.size; i++){
     Edge *host_edge = getEdge(multi_mark, i);
     if(host_edge == NULL || host_edge->index == -1 || node_mapping[host_edge->source] == -1 || node_mapping[host_edge->target] == -1) continue;
     if(host_edge->label.mark != mark){
       printf("Edge %d\n", i);
       printfGraph(multi_mark);
       exit(0);
     }
     addEdge(graph_copy, makeHostLabel(target_mark, host_edge->label.length, copyHostList(host_edge->label.list)), node_mapping[host_edge->source], node_mapping[host_edge->target]);
  }
  return graph_copy;
}

//Graph duplication function
Graph* duplicate_graph(Graph *graph)
{
   Graph *graph_copy = newGraph(150, 300);
	 int node_mapping[graph->nodes.size];
	 //Copy nodes
	 for(int i = 0; i < graph->nodes.size; i++){
			Node *host_node = getNode(graph, i);
			if(host_node == NULL || host_node->index == -1) continue;
			node_mapping[i] = addNode(graph_copy, host_node->root, makeHostLabel(host_node->label.mark, host_node->label.length, copyHostList(host_node->label.list)));
	 }
	 //Copy edges
	 for(int i = 0; i < graph->edges.size; i++){
			Edge *host_edge = getEdge(graph, i);
			if(host_edge == NULL || host_edge->index == -1) continue;
			addEdge(graph_copy, makeHostLabel(host_edge->label.mark, host_edge->label.length, copyHostList(host_edge->label.list)), node_mapping[host_edge->source], node_mapping[host_edge->target]);
	 }
	 return graph_copy;
}

//Counts the active nodes in a GP individual.
int count_active_nodes(Graph* hostG, int inputs, int outputs){
	mark_active_blue(hostG);
	int count = 0;
	for(int host_index = 0; host_index < hostG->nodes.size; host_index++)
	{
		 Node *host_node = getNode(hostG, host_index);
		 if(host_node == NULL || host_node->index == -1) continue;
		 HostLabel label = host_node->label;
		 if(label.mark > 0){
		 	count++;
		 }
	}
	unmark_graph(hostG);
	if(count < (inputs + outputs)){
		return 0;
	}
	return count - (inputs + outputs);
}

//Counts the active nodes in a GP individual.
int count_active_edges(Graph* hostG){
	mark_active_blue(hostG);
	int count = 0;
	for(int host_index = 0; host_index < hostG->nodes.size; host_index++)
	{
		 Node *host_node = getNode(hostG, host_index);
		 if(host_node == NULL || host_node->index == -1) continue;
		 HostLabel label = host_node->label;
		 if(label.mark > 0){
        int counter = 0;
       	for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
       	{
       		Edge *host_edge = getNthOutEdge(hostG, host_node, counter);
       		if(host_edge == NULL || host_edge->index == -1) continue;
          count++;
    		}
    }
	}
	unmark_graph(hostG);
  return count;
}


void mark_active_blue(Graph* hostG){

	for(int host_index = 0; host_index < hostG->nodes.size; host_index++)
	{
		 Node *host_node = getNode(hostG, host_index);
		 if(host_node == NULL || host_node->index == -1) continue;

		 HostLabel label = host_node->label;
		 HostListItem *item = label.list->last;
		 if(item->atom.type != 's') break;
		 if(strcmp(item->atom.str, "OUT") == 0){
	   	 changeNodeMark(hostG, host_index, 3);
			 mark_active_children_blue(hostG, host_node);
		 }
	}
}

void mark_active_children_blue(Graph* hostG, Node *node){
	int counter;
	for(counter = 0; counter < node->out_edges.size + 2; counter++)
	{
		Edge *host_edge = getNthOutEdge(hostG, node, counter);
		if(host_edge == NULL || host_edge->index == -1) continue;
		Node *target = getNode(hostG, host_edge->target);
		HostLabel label = target->label;
		if(label.mark == 0){
 	   	changeNodeMark(hostG, target->index, 3);
			mark_active_children_blue(hostG, target);
		}
	}
}

void unmark_graph(Graph* hostG){

		for(int host_index = 0; host_index < hostG->nodes.size; host_index++)
		{
			 Node *host_node = getNode(hostG, host_index);
			 if(host_node == NULL || host_node->index == -1) continue;
			 if(host_node->label.mark != 0){
		   	changeNodeMark(hostG, host_index, 0);
				if(host_node->root){
					host_node->root = false;
				}
			}
		}
}

Graph* build_empty_host_graph()
{
   Graph* new_host = newGraph(150, 300);
   return new_host;
}

void free_graph_array(Graph** array, int graphs){
    for(int i = 0; i < graphs; i++){
     freeGraph(array[i]);
   }
   free(array);
}

void free_graph_data(Graph* graph){
  if(graph == NULL) return;
  printf("Freeing graph\n");
  printfGraph(graph);
  int index;
  for(index = 0; index < graph->nodes.size; index++)
  {
     Node *node = getNode(graph, index);
     if(node == NULL) continue;
     if(node->out_edges.items != NULL) free(node->out_edges.items);
     if(node->in_edges.items != NULL) free(node->in_edges.items);
     removeHostList(node->label.list);
  }
  if(graph->nodes.holes.items) free(graph->nodes.holes.items);
  if(graph->nodes.items) free(graph->nodes.items);

  for(index = 0; index < graph->edges.size; index++)
  {
     Edge *edge = getEdge(graph, index);
     if(edge == NULL) continue;
     removeHostList(edge->label.list);
  }
  if(graph->edges.holes.items != NULL) free(graph->edges.holes.items);
  if(graph->edges.items != NULL) free(graph->edges.items);
  if(graph->root_nodes != NULL)
  {
     RootNodes *iterator = graph->root_nodes;
     while(iterator != NULL)
     {
        RootNodes *temp = iterator;
        iterator = iterator->next;
        free(temp);
     }
  }
}

//Random integer from min (inclusive) to max (exclusive)
int random_int(int min, int max){
   int nu_max = max - 1;
   return min + rand() / (RAND_MAX / (nu_max - min + 1) + 1);
}

void make_depth(Graph* graph){
  depth_start_execute(graph);

  //Go down
  int* queue = malloc(graph->nodes.size * sizeof(int));
  int* depthDown = malloc(graph->nodes.size * sizeof(int));
  for(int host_index = 0; host_index < graph->nodes.size; host_index++){
    depthDown[host_index] = 1;
  }
  for(int host_index = 0; host_index < graph->nodes.size; host_index++){
    Node* host_node = getNode(graph, host_index);
    queue[host_index] = 0;
    if(host_node == NULL || host_node->index == -1) continue;
    HostLabel label = host_node->label;
    if(strcmp(label.list->last->atom.str, "OUT") == 0){
      depthDown[host_index] = 0;
    }
    if(host_node->indegree == 0){
      queue[host_index] = 1;
    }
  }
  int empty = 0;
  while(empty == 0){
    empty = 1;
    int* new_queue = malloc(graph->nodes.size * sizeof(int));
    for(int host_index = 0; host_index < graph->nodes.size; host_index++){
      new_queue[host_index] = 0;
    }
    for(int host_index = 0; host_index < graph->nodes.size; host_index++){
      Node* host_node = getNode(graph, host_index);
      if(host_node == NULL || host_node->index == -1 || queue[host_index] == 0 || host_node->outdegree == 0) continue;
      HostLabel label = host_node->label;
      int counter;
      for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
      {
        Edge *host_edge = getNthOutEdge(graph, host_node, counter);
        if(host_edge == NULL || host_edge->index == -1) continue;
        Node *target = getNode(graph, host_edge->target);
        int index = target->index;
        if(depthDown[index] < depthDown[host_index] + 1 || (depthDown[host_index] == 0 && depthDown[index] == 1)){
          depthDown[index] = depthDown[host_index] + 1;
          new_queue[target->index] = 1;
          empty = 0;
        }
      }
    }
    free(queue);
    queue = new_queue;
  }
  free(queue);
  queue = malloc(graph->nodes.size * sizeof(int));
  int* depthUp = malloc(graph->nodes.size * sizeof(int));
  for(int host_index = 0; host_index < graph->nodes.size; host_index++){
    depthUp[host_index] = 1;
  }
  for(int host_index = 0; host_index < graph->nodes.size; host_index++){
    Node* host_node = getNode(graph, host_index);
    queue[host_index] = 0;
    if(host_node == NULL || host_node->index == -1) continue;
    HostLabel label = host_node->label;
    if(host_node->outdegree == 0){
      queue[host_index] = 1;
    }
  }
  empty = 0;
  while(empty == 0){
    empty = 1;
    int* new_queue = malloc(graph->nodes.size * sizeof(int));
    for(int host_index = 0; host_index < graph->nodes.size; host_index++){
      new_queue[host_index] = 0;
    }
    for(int host_index = 0; host_index < graph->nodes.size; host_index++){
      Node* host_node = getNode(graph, host_index);
      if(host_node == NULL || host_node->index == -1 || queue[host_index] == 0 || host_node->indegree == 0) continue;
      HostLabel label = host_node->label;
      int counter;
      for(counter = 0; counter < host_node->in_edges.size + 2; counter++)
      {
        Edge *host_edge = getNthInEdge(graph, host_node, counter);
        if(host_edge == NULL || host_edge->index == -1) continue;
        Node *source = getNode(graph, host_edge->source);
        int index = source->index;
        if(depthUp[index] < depthUp[host_index] + 1){
          depthUp[index] = depthUp[host_index] + 1;
          new_queue[source->index] = 1;
          empty = 0;
        }
      }
    }
    free(queue);
    queue = new_queue;
  }
  free(queue);
  for(int host_index = 0; host_index < graph->nodes.size; host_index++){
    Node* host_node = getNode(graph, host_index);
    if(host_node == NULL || host_node->index == -1) continue;
    HostLabel label = host_node->label;

    HostListItem *item = label.list->last;
    HostListItem *item2 = item->prev;
    HostListItem *item3 = item2->prev;

    item2->atom.num = depthDown[host_index];
    item3->atom.num = depthUp[host_index];
  }
  free(depthUp);
  free(depthDown);
}

int depth(Graph* graph){
  mark_active_blue(graph);
  int* queue = malloc(graph->nodes.size * sizeof(int));
  for(int host_index = 0; host_index < graph->nodes.size; host_index++){
    Node* host_node = getNode(graph, host_index);
    queue[host_index] = 0;
    if(host_node == NULL || host_node->index == -1) continue;
    HostLabel label = host_node->label;
    if(label.mark == 0) continue;
    if(host_node->indegree == 0){
      queue[host_index] = 1;
    }
  }
  int empty = 0;
  int depth = 0;
  while(empty == 0){
    empty = 1;
    int* new_queue = malloc(graph->nodes.size * sizeof(int));
    for(int host_index = 0; host_index < graph->nodes.size; host_index++){
      new_queue[host_index] = 0;
    }
    for(int host_index = 0; host_index < graph->nodes.size; host_index++){
      Node* host_node = getNode(graph, host_index);
      if(host_node == NULL || host_node->index == -1 || queue[host_index] == 0 || host_node->outdegree == 0) continue;
      HostLabel label = host_node->label;
      if(label.mark == 0) continue;
      int counter;
      for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
      {
        Edge *host_edge = getNthOutEdge(graph, host_node, counter);
        if(host_edge == NULL || host_edge->index == -1) continue;
        Node *target = getNode(graph, host_edge->target);
        new_queue[target->index] = 1;
        empty = 0;
      }
    }
    free(queue);
    queue = new_queue;
    depth++;
  }
  free(queue);
  unmark_graph(graph);
  return depth - 2;
}
