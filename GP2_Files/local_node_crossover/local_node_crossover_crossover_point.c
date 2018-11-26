#include "local_node_crossover_crossover_point.h"

#include "local_node_crossover.h"

bool local_node_crossover_b0 = true;

static bool evaluateCondition(void)
{
   return (local_node_crossover_b0);
}

static void evaluatePredicatelocal_node_crossover_0(Morphism *morphism)
{
   Assignment assignment_7 = getAssignment(morphism, 7);
   /* If the variable is not yet assigned, return. */
   if(assignment_7.type == 'n') return;
   int var_7 = getIntegerValue(morphism, 7);

   Assignment assignment_8 = getAssignment(morphism, 8);
   /* If the variable is not yet assigned, return. */
   if(assignment_8.type == 'n') return;
   int var_8 = getIntegerValue(morphism, 8);

   Assignment assignment_10 = getAssignment(morphism, 10);
   /* If the variable is not yet assigned, return. */
   if(assignment_10.type == 'n') return;
   int var_10 = getIntegerValue(morphism, 10);

   if(var_7 + var_8 <= var_10) local_node_crossover_b0 = true;
   else local_node_crossover_b0 = false;
}

static bool match_n4(Morphism *morphism);
static bool match_n0(Morphism *morphism);
static bool match_e0(Morphism *morphism);
static bool match_n1(Morphism *morphism, Edge *host_edge);
static bool match_n2(Morphism *morphism);
static bool match_e1(Morphism *morphism);
static bool match_n3(Morphism *morphism, Edge *host_edge);

bool matchlocal_node_crossover_crossover_point(Morphism *morphism)
{
   if(5 > local_node_crossover_host->number_of_nodes || 2 > local_node_crossover_host->number_of_edges) return false;
   if(match_n4(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, local_node_crossover_host);
      return false;
   }
}

static bool match_n4(Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(local_node_crossover_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(local_node_crossover_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) != 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 2) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "Depth") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 10. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 10, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatelocal_node_crossover_0(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               local_node_crossover_b0 = true;
               break;
            }
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 4, host_node->index, new_assignments);
         host_node->matched = true;
         if(match_n0(morphism)) return true;
         else
         {
         removeNodeMap(morphism, 4);
         host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool match_n0(Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < local_node_crossover_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(local_node_crossover_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 2) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         if(label.length < 3) break;
         /* Matching from the start of the host list. */
         HostListItem *item = label.list->first;
         int result = -1;
         HostListItem *start = item;
         item = label.list->last;
         /* The current host list position marks the start of the list that is
            assigned to the list variable. */
         /* More rule atoms to match. If the end of the host list is reached, break. */
         if(start == NULL) break;

         /* Matching from the end of the host list. */
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 4 */
         /* Matching string variable 11. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 11, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 3 */
         /* Matching integer variable 7. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 7, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatelocal_node_crossover_0(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               local_node_crossover_b0 = true;
               break;
            }
         }
         else break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 2 */
         /* Matching integer variable 6. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 6, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->prev;
         /* Matching list variable 0. */
         if(item == start->prev) result = addListAssignment(morphism, 0, NULL);
         else if(item == start)
         {
            if(item->atom.type == 'i') result = addIntegerAssignment(morphism, 0, item->atom.num);
            else result = addStringAssignment(morphism, 0, item->atom.str);
         }
         else
         {
            /* Assign to variable 0 the unmatched sublist of the host list. */
            HostAtom sublist[label.length - 3];
            int list_index = 0;
            HostListItem *iterator = start;
            while(iterator != item->next)
            {
               sublist[list_index++] = iterator->atom;
               iterator = iterator->next;
            }
            HostList *list = makeHostList(sublist, label.length - 3, false);
            result = addListAssignment(morphism, 0, list);
            freeHostList(list);
         }
         if(result >= 0)
         {
            new_assignments += result;
            match = true;
         }
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         if(match_e0(morphism)) return true;
         else
         {
         removeNodeMap(morphism, 0);
         host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool match_e0(Morphism *morphism)
{
   /* Start node is the already-matched node from which the candidate
      edges are drawn. End node may or may not have been matched already. */
   int start_index = lookupNode(morphism, 0);
   int end_index = lookupNode(morphism, 1);
   if(start_index < 0) return false;
   Node *host_node = getNode(local_node_crossover_host, start_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(local_node_crossover_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source == host_edge->target) continue;
      if(host_edge->label.mark != 1) continue;

      /* If the end node has been matched, check that the target of the
       * host edge is the image of the end node. */
      if(end_index >= 0)
      {
         if(host_edge->target != end_index) continue;
      }
      /* Otherwise, the target of the host edge should be unmatched. */
      else
      {
         Node *end_node = getNode(local_node_crossover_host, host_edge->target);
         if(end_node->matched) continue;
      }

      HostLabel label = host_edge->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 4 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 4, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 4, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 4, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addEdgeMap(morphism, 0, host_edge->index, new_assignments);
         host_edge->matched = true;
         if(match_n1(morphism, host_edge)) return true;
         else
         {
            removeEdgeMap(morphism, 0);
            host_edge->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool match_n1(Morphism *morphism, Edge *host_edge)
{
   Node *host_node = getTarget(local_node_crossover_host, host_edge);

   if(host_node->matched) return false;
   if(host_node->label.mark != 2) return false;
      if(host_node->indegree < 1 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 1 - 0) < 0)) return false;;

   HostLabel label = host_node->label;
   bool match = false;
   /* Label Matching */
   int new_assignments = 0;
   /* Match list variable 1 against the whole host list. */
   int result = -1;
   if(label.length == 1)
   {
      if(label.list->first->atom.type == 'i')
         result = addIntegerAssignment(morphism, 1, label.list->first->atom.num);
      else result = addStringAssignment(morphism, 1, label.list->first->atom.str);
   }
   else result = addListAssignment(morphism, 1, label.list);
   if(result >= 0)
   {
      new_assignments += result;
      match = true;
   }
   if(match)
   {
      addNodeMap(morphism, 1, host_node->index, new_assignments);
      host_node->matched = true;
      if(match_n2(morphism)) return true;
      else
      {
      removeNodeMap(morphism, 1);
      host_node->matched = false;
      }
   }
   else removeAssignments(morphism, new_assignments);
   return false;
}

static bool match_n2(Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < local_node_crossover_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(local_node_crossover_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 4) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 2 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 2, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 2, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 2, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addNodeMap(morphism, 2, host_node->index, new_assignments);
         host_node->matched = true;
         if(match_e1(morphism)) return true;
         else
         {
         removeNodeMap(morphism, 2);
         host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool match_e1(Morphism *morphism)
{
   /* Start node is the already-matched node from which the candidate
      edges are drawn. End node may or may not have been matched already. */
   int start_index = lookupNode(morphism, 2);
   int end_index = lookupNode(morphism, 3);
   if(start_index < 0) return false;
   Node *host_node = getNode(local_node_crossover_host, start_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(local_node_crossover_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source == host_edge->target) continue;
      if(host_edge->label.mark != 3) continue;

      /* If the end node has been matched, check that the target of the
       * host edge is the image of the end node. */
      if(end_index >= 0)
      {
         if(host_edge->target != end_index) continue;
      }
      /* Otherwise, the target of the host edge should be unmatched. */
      else
      {
         Node *end_node = getNode(local_node_crossover_host, host_edge->target);
         if(end_node->matched) continue;
      }

      HostLabel label = host_edge->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 5 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 5, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 5, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 5, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addEdgeMap(morphism, 1, host_edge->index, new_assignments);
         host_edge->matched = true;
         if(match_n3(morphism, host_edge)) return true;
         else
         {
            removeEdgeMap(morphism, 1);
            host_edge->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool match_n3(Morphism *morphism, Edge *host_edge)
{
   Node *host_node = getTarget(local_node_crossover_host, host_edge);

   if(host_node->matched) return false;
   if(host_node->label.mark != 4) return false;
      if(host_node->indegree < 1 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 1 - 0) < 0)) return false;;

   HostLabel label = host_node->label;
   bool match = false;
   /* Label Matching */
   int new_assignments = 0;
   do
   {
      if(label.length < 3) break;
      /* Matching from the start of the host list. */
      HostListItem *item = label.list->first;
      int result = -1;
      HostListItem *start = item;
      item = label.list->last;
      /* The current host list position marks the start of the list that is
         assigned to the list variable. */
      /* More rule atoms to match. If the end of the host list is reached, break. */
      if(start == NULL) break;

      /* Matching from the end of the host list. */
      /* Check if the host list has passed "start". */
      if(item == start->prev) break;
      /* Matching rule atom 4 */
      /* Matching string variable 12. */
      if(item->atom.type != 's') break;
      result = addStringAssignment(morphism, 12, item->atom.str);
      if(result >= 0)
      {
         new_assignments += result;
      }
      else break;
      item = item->prev;
      /* Check if the host list has passed "start". */
      if(item == start->prev) break;
      /* Matching rule atom 3 */
      /* Matching integer variable 9. */
      if(item->atom.type != 'i') break;
      result = addIntegerAssignment(morphism, 9, item->atom.num);
      if(result >= 0)
      {
         new_assignments += result;
      }
      else break;
      item = item->prev;
      /* Check if the host list has passed "start". */
      if(item == start->prev) break;
      /* Matching rule atom 2 */
      /* Matching integer variable 8. */
      if(item->atom.type != 'i') break;
      result = addIntegerAssignment(morphism, 8, item->atom.num);
      if(result >= 0)
      {
         new_assignments += result;
         /* Update global booleans for the variable's predicates. */
         evaluatePredicatelocal_node_crossover_0(morphism);
         if(!evaluateCondition())
         {
            /* Reset the boolean variables in the predicates of this variable. */
            local_node_crossover_b0 = true;
            break;
         }
      }
      else break;
      item = item->prev;
      /* Matching list variable 3. */
      if(item == start->prev) result = addListAssignment(morphism, 3, NULL);
      else if(item == start)
      {
         if(item->atom.type == 'i') result = addIntegerAssignment(morphism, 3, item->atom.num);
         else result = addStringAssignment(morphism, 3, item->atom.str);
      }
      else
      {
         /* Assign to variable 3 the unmatched sublist of the host list. */
         HostAtom sublist[label.length - 3];
         int list_index = 0;
         HostListItem *iterator = start;
         while(iterator != item->next)
         {
            sublist[list_index++] = iterator->atom;
            iterator = iterator->next;
         }
         HostList *list = makeHostList(sublist, label.length - 3, false);
         result = addListAssignment(morphism, 3, list);
         freeHostList(list);
      }
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
   } while(false);

   if(match)
   {
      addNodeMap(morphism, 3, host_node->index, new_assignments);
      host_node->matched = true;
      /* All items matched! */
         return true;
   }
   else removeAssignments(morphism, new_assignments);
   return false;
}

void applylocal_node_crossover_crossover_point(Morphism *morphism, bool record_changes)
{
   Assignment var_4 = getAssignment(morphism, 4);
   Assignment var_5 = getAssignment(morphism, 5);
   int var_10 = getIntegerValue(morphism, 10);
   int host_edge_index = lookupEdge(morphism, 0);
   if(record_changes)
   {
      Edge *edge = getEdge(local_node_crossover_host, host_edge_index);
      /* A hole is created if the edge is not at the right-most index of the array. */
      pushRemovedEdge(edge->label, edge->source, edge->target, edge->index,
                      edge->index < local_node_crossover_host->edges.size - 1);
   }
   removeEdge(local_node_crossover_host, host_edge_index);

   host_edge_index = lookupEdge(morphism, 1);
   if(record_changes)
   {
      Edge *edge = getEdge(local_node_crossover_host, host_edge_index);
      /* A hole is created if the edge is not at the right-most index of the array. */
      pushRemovedEdge(edge->label, edge->source, edge->target, edge->index,
                      edge->index < local_node_crossover_host->edges.size - 1);
   }
   removeEdge(local_node_crossover_host, host_edge_index);

   int host_node_index = lookupNode(morphism, 4);
   if(record_changes)
   {
      Node *node = getNode(local_node_crossover_host, host_node_index);
      /* A hole is created if the node is not at the right-most index of the array. */
      pushRemovedNode(node->root, node->label, node->index,
                      node->index < local_node_crossover_host->nodes.size - 1);
   }
   removeNode(local_node_crossover_host, host_node_index);

   /* Array of host node indices indexed by RHS node index. */
   int rhs_node_map[5];

   int node_array_size4 = local_node_crossover_host->nodes.size;
   HostLabel label;
   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 2;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 's';
   array0[index0++].str = "Depth";
   array0[index0].type = 'i';
   array0[index0++].num = var_10;
   if(list_length0 > 0)
   {
      HostList *list0 = makeHostList(array0, list_length0, false);
      label = makeHostLabel(0, list_length0, list0);
   }
   else label = makeEmptyLabel(0);

   host_node_index = addNode(local_node_crossover_host, 1, label);
   rhs_node_map[4] = host_node_index;
   /* If the node array size has not increased after the node addition, then
      the node was added to a hole in the array. */
   if(record_changes)
      pushAddedNode(host_node_index, node_array_size4 == local_node_crossover_host->nodes.size);
   int source, target;
   int edge_array_size0 = local_node_crossover_host->edges.size;
   source = lookupNode(morphism, 0);
   target = lookupNode(morphism, 3);
   int list_var_length1 = 0;
   list_var_length1 += getAssignmentLength(var_4);
   int list_length1 = list_var_length1 + 0;
   HostAtom array1[list_length1];
   int index1 = 0;

   if(var_4.type == 'l' && var_4.list != NULL)
   {
      HostListItem *item1 = var_4.list->first;
      while(item1 != NULL)
      {
         array1[index1++] = item1->atom;
         item1 = item1->next;
      }
   }
   else if(var_4.type == 'i')
   {
      array1[index1].type = 'i';
      array1[index1++].num = var_4.num;
   }
   else if(var_4.type == 's')
   {
      array1[index1].type = 's';
      array1[index1++].str = var_4.str;
   }

   if(list_length1 > 0)
   {
      HostList *list1 = makeHostList(array1, list_length1, false);
      label = makeHostLabel(1, list_length1, list1);
   }
   else label = makeEmptyLabel(1);

   host_edge_index = addEdge(local_node_crossover_host, label, source, target);
   /* If the edge array size has not increased after the edge addition, then
      the edge was added to a hole in the array. */
   if(record_changes)
      pushAddedEdge(host_edge_index, edge_array_size0 == local_node_crossover_host->edges.size);
   int edge_array_size1 = local_node_crossover_host->edges.size;
   source = lookupNode(morphism, 2);
   target = lookupNode(morphism, 1);
   int list_var_length2 = 0;
   list_var_length2 += getAssignmentLength(var_5);
   int list_length2 = list_var_length2 + 0;
   HostAtom array2[list_length2];
   int index2 = 0;

   if(var_5.type == 'l' && var_5.list != NULL)
   {
      HostListItem *item2 = var_5.list->first;
      while(item2 != NULL)
      {
         array2[index2++] = item2->atom;
         item2 = item2->next;
      }
   }
   else if(var_5.type == 'i')
   {
      array2[index2].type = 'i';
      array2[index2++].num = var_5.num;
   }
   else if(var_5.type == 's')
   {
      array2[index2].type = 's';
      array2[index2++].str = var_5.str;
   }

   if(list_length2 > 0)
   {
      HostList *list2 = makeHostList(array2, list_length2, false);
      label = makeHostLabel(3, list_length2, list2);
   }
   else label = makeEmptyLabel(3);

   host_edge_index = addEdge(local_node_crossover_host, label, source, target);
   /* If the edge array size has not increased after the edge addition, then
      the edge was added to a hole in the array. */
   if(record_changes)
      pushAddedEdge(host_edge_index, edge_array_size1 == local_node_crossover_host->edges.size);
   /* Reset the morphism. */
   initialiseMorphism(morphism, local_node_crossover_host);
}

static bool fillpot_n4(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_e0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n1(MorphismPot *pot, Morphism *morphism, Edge *host_edge);
static bool fillpot_n2(MorphismPot *pot, Morphism *morphism);
static bool fillpot_e1(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n3(MorphismPot *pot, Morphism *morphism, Edge *host_edge);

bool fillpotlocal_node_crossover_crossover_point(MorphismPot *pot, Morphism *morphism)
{
   if(5 > local_node_crossover_host->number_of_nodes || 2 > local_node_crossover_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n4(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, local_node_crossover_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, local_node_crossover_host);
      return false;
   }
}

static bool fillpot_n4(MorphismPot *pot, Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(local_node_crossover_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(local_node_crossover_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) != 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 2) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "Depth") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 10. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 10, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatelocal_node_crossover_0(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               local_node_crossover_b0 = true;
               break;
            }
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 4, host_node->index, new_assignments);
         host_node->matched = true;
         if(fillpot_n0(pot, morphism)) return true;
         else
         {
         removeNodeMap(morphism, 4);
         host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < local_node_crossover_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(local_node_crossover_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 2) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         if(label.length < 3) break;
         /* Matching from the start of the host list. */
         HostListItem *item = label.list->first;
         int result = -1;
         HostListItem *start = item;
         item = label.list->last;
         /* The current host list position marks the start of the list that is
            assigned to the list variable. */
         /* More rule atoms to match. If the end of the host list is reached, break. */
         if(start == NULL) break;

         /* Matching from the end of the host list. */
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 4 */
         /* Matching string variable 11. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 11, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 3 */
         /* Matching integer variable 7. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 7, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatelocal_node_crossover_0(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               local_node_crossover_b0 = true;
               break;
            }
         }
         else break;
         item = item->prev;
         /* Check if the host list has passed "start". */
         if(item == start->prev) break;
         /* Matching rule atom 2 */
         /* Matching integer variable 6. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 6, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->prev;
         /* Matching list variable 0. */
         if(item == start->prev) result = addListAssignment(morphism, 0, NULL);
         else if(item == start)
         {
            if(item->atom.type == 'i') result = addIntegerAssignment(morphism, 0, item->atom.num);
            else result = addStringAssignment(morphism, 0, item->atom.str);
         }
         else
         {
            /* Assign to variable 0 the unmatched sublist of the host list. */
            HostAtom sublist[label.length - 3];
            int list_index = 0;
            HostListItem *iterator = start;
            while(iterator != item->next)
            {
               sublist[list_index++] = iterator->atom;
               iterator = iterator->next;
            }
            HostList *list = makeHostList(sublist, label.length - 3, false);
            result = addListAssignment(morphism, 0, list);
            freeHostList(list);
         }
         if(result >= 0)
         {
            new_assignments += result;
            match = true;
         }
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         if(fillpot_e0(pot, morphism)) return true;
         else
         {
         removeNodeMap(morphism, 0);
         host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool fillpot_e0(MorphismPot *pot, Morphism *morphism)
{
   /* Start node is the already-matched node from which the candidate
      edges are drawn. End node may or may not have been matched already. */
   int start_index = lookupNode(morphism, 0);
   int end_index = lookupNode(morphism, 1);
   if(start_index < 0) return false;
   Node *host_node = getNode(local_node_crossover_host, start_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(local_node_crossover_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source == host_edge->target) continue;
      if(host_edge->label.mark != 1) continue;

      /* If the end node has been matched, check that the target of the
       * host edge is the image of the end node. */
      if(end_index >= 0)
      {
         if(host_edge->target != end_index) continue;
      }
      /* Otherwise, the target of the host edge should be unmatched. */
      else
      {
         Node *end_node = getNode(local_node_crossover_host, host_edge->target);
         if(end_node->matched) continue;
      }

      HostLabel label = host_edge->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 4 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 4, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 4, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 4, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addEdgeMap(morphism, 0, host_edge->index, new_assignments);
         host_edge->matched = true;
         if(fillpot_n1(pot, morphism, host_edge)) return true;
         else
         {
            removeEdgeMap(morphism, 0);
            host_edge->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism, Edge *host_edge)
{
   Node *host_node = getTarget(local_node_crossover_host, host_edge);

   if(host_node->matched) return false;
   if(host_node->label.mark != 2) return false;
      if(host_node->indegree < 1 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 1 - 0) < 0)) return false;;

   HostLabel label = host_node->label;
   bool match = false;
   /* Label Matching */
   int new_assignments = 0;
   /* Match list variable 1 against the whole host list. */
   int result = -1;
   if(label.length == 1)
   {
      if(label.list->first->atom.type == 'i')
         result = addIntegerAssignment(morphism, 1, label.list->first->atom.num);
      else result = addStringAssignment(morphism, 1, label.list->first->atom.str);
   }
   else result = addListAssignment(morphism, 1, label.list);
   if(result >= 0)
   {
      new_assignments += result;
      match = true;
   }
   if(match)
   {
      addNodeMap(morphism, 1, host_node->index, new_assignments);
      host_node->matched = true;
      if(fillpot_n2(pot, morphism)) return true;
      else
      {
      removeNodeMap(morphism, 1);
      host_node->matched = false;
      }
   }
   else removeAssignments(morphism, new_assignments);
   return false;
}

static bool fillpot_n2(MorphismPot *pot, Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < local_node_crossover_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(local_node_crossover_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 4) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 2 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 2, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 2, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 2, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addNodeMap(morphism, 2, host_node->index, new_assignments);
         host_node->matched = true;
         if(fillpot_e1(pot, morphism)) return true;
         else
         {
         removeNodeMap(morphism, 2);
         host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool fillpot_e1(MorphismPot *pot, Morphism *morphism)
{
   /* Start node is the already-matched node from which the candidate
      edges are drawn. End node may or may not have been matched already. */
   int start_index = lookupNode(morphism, 2);
   int end_index = lookupNode(morphism, 3);
   if(start_index < 0) return false;
   Node *host_node = getNode(local_node_crossover_host, start_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(local_node_crossover_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source == host_edge->target) continue;
      if(host_edge->label.mark != 3) continue;

      /* If the end node has been matched, check that the target of the
       * host edge is the image of the end node. */
      if(end_index >= 0)
      {
         if(host_edge->target != end_index) continue;
      }
      /* Otherwise, the target of the host edge should be unmatched. */
      else
      {
         Node *end_node = getNode(local_node_crossover_host, host_edge->target);
         if(end_node->matched) continue;
      }

      HostLabel label = host_edge->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 5 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 5, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 5, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 5, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addEdgeMap(morphism, 1, host_edge->index, new_assignments);
         host_edge->matched = true;
         if(fillpot_n3(pot, morphism, host_edge)) return true;
         else
         {
            removeEdgeMap(morphism, 1);
            host_edge->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool fillpot_n3(MorphismPot *pot, Morphism *morphism, Edge *host_edge)
{
   Node *host_node = getTarget(local_node_crossover_host, host_edge);

   if(host_node->matched) return false;
   if(host_node->label.mark != 4) return false;
      if(host_node->indegree < 1 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 1 - 0) < 0)) return false;;

   HostLabel label = host_node->label;
   bool match = false;
   /* Label Matching */
   int new_assignments = 0;
   do
   {
      if(label.length < 3) break;
      /* Matching from the start of the host list. */
      HostListItem *item = label.list->first;
      int result = -1;
      HostListItem *start = item;
      item = label.list->last;
      /* The current host list position marks the start of the list that is
         assigned to the list variable. */
      /* More rule atoms to match. If the end of the host list is reached, break. */
      if(start == NULL) break;

      /* Matching from the end of the host list. */
      /* Check if the host list has passed "start". */
      if(item == start->prev) break;
      /* Matching rule atom 4 */
      /* Matching string variable 12. */
      if(item->atom.type != 's') break;
      result = addStringAssignment(morphism, 12, item->atom.str);
      if(result >= 0)
      {
         new_assignments += result;
      }
      else break;
      item = item->prev;
      /* Check if the host list has passed "start". */
      if(item == start->prev) break;
      /* Matching rule atom 3 */
      /* Matching integer variable 9. */
      if(item->atom.type != 'i') break;
      result = addIntegerAssignment(morphism, 9, item->atom.num);
      if(result >= 0)
      {
         new_assignments += result;
      }
      else break;
      item = item->prev;
      /* Check if the host list has passed "start". */
      if(item == start->prev) break;
      /* Matching rule atom 2 */
      /* Matching integer variable 8. */
      if(item->atom.type != 'i') break;
      result = addIntegerAssignment(morphism, 8, item->atom.num);
      if(result >= 0)
      {
         new_assignments += result;
         /* Update global booleans for the variable's predicates. */
         evaluatePredicatelocal_node_crossover_0(morphism);
         if(!evaluateCondition())
         {
            /* Reset the boolean variables in the predicates of this variable. */
            local_node_crossover_b0 = true;
            break;
         }
      }
      else break;
      item = item->prev;
      /* Matching list variable 3. */
      if(item == start->prev) result = addListAssignment(morphism, 3, NULL);
      else if(item == start)
      {
         if(item->atom.type == 'i') result = addIntegerAssignment(morphism, 3, item->atom.num);
         else result = addStringAssignment(morphism, 3, item->atom.str);
      }
      else
      {
         /* Assign to variable 3 the unmatched sublist of the host list. */
         HostAtom sublist[label.length - 3];
         int list_index = 0;
         HostListItem *iterator = start;
         while(iterator != item->next)
         {
            sublist[list_index++] = iterator->atom;
            iterator = iterator->next;
         }
         HostList *list = makeHostList(sublist, label.length - 3, false);
         result = addListAssignment(morphism, 3, list);
         freeHostList(list);
      }
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
   } while(false);

   if(match)
   {
      addNodeMap(morphism, 3, host_node->index, new_assignments);
      host_node->matched = true;
      /* All items matched! */
         putMorphism(pot, morphism, "local_node_crossover_crossover_point", local_node_crossover_host);
         removeNodeMap(morphism, 3);
         host_node->matched = false;
   }
   else removeAssignments(morphism, new_assignments);
   return false;
}

