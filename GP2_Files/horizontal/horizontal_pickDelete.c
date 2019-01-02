#include "horizontal_pickDelete.h"

#include "horizontal.h"

bool horizontal_b1 = true;
bool horizontal_b2 = true;

static bool evaluateCondition(void)
{
   return (horizontal_b1 && horizontal_b2);
}

static void evaluatePredicatehorizontal_1(Morphism *morphism)
{
   int n0 = lookupNode(morphism, 0);
   /* If the node is not yet matched by the morphism, return. */
   if(n0 == -1) return;

   if(getIndegree(horizontal_host, n0) == 0) horizontal_b1 = true;
   else horizontal_b1 = false;
}

static void evaluatePredicatehorizontal_2(Morphism *morphism)
{
   Assignment assignment_1 = getAssignment(morphism, 1);
   /* If the variable is not yet assigned, return. */
   if(assignment_1.type == 'n') return;
   string var_1 = getStringValue(morphism, 1);

   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 1;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 's';
   array0[index0++].str = var_1;

   int list_var_length1 = 0;
   int list_length1 = list_var_length1 + 1;
   HostAtom array1[list_length1];
   int index1 = 0;

   array1[index1].type = 's';
   array1[index1++].str = "IN";

   if(!equalHostLists(array0, array1, list_length0, list_length1)) horizontal_b2 = true;
   else horizontal_b2 = false;
}

static bool match_n0(Morphism *morphism);

bool matchhorizontal_pickDelete(Morphism *morphism)
{
   if(1 > horizontal_host->number_of_nodes || 0 > horizontal_host->number_of_edges) return false;
   if(match_n0(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, horizontal_host);
      return false;
   }
}

static bool match_n0(Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < horizontal_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(horizontal_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 1) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         if(label.length < 1) break;
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
         /* Matching rule atom 2 */
         /* Matching string variable 1. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 1, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatehorizontal_2(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               horizontal_b2 = true;
               break;
            }
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
            HostAtom sublist[label.length - 1];
            int list_index = 0;
            HostListItem *iterator = start;
            while(iterator != item->next)
            {
               sublist[list_index++] = iterator->atom;
               iterator = iterator->next;
            }
            HostList *list = makeHostList(sublist, label.length - 1, false);
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
         /* Update global booleans representing the node's predicates. */
         evaluatePredicatehorizontal_1(morphism);
         if(evaluateCondition())
         {
            /* All items matched! */
            return true;
         }
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            horizontal_b1 = true;
            removeNodeMap(morphism, 0);
            host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

void applyhorizontal_pickDelete(Morphism *morphism, bool record_changes)
{
   int host_node_index = lookupNode(morphism, 0);
   HostLabel label_n0 = getNodeLabel(horizontal_host, host_node_index);
   if(record_changes) pushRemarkedNode(host_node_index, label_n0.mark);
   changeNodeMark(horizontal_host, host_node_index, 3);

   /* Reset the morphism. */
   initialiseMorphism(morphism, horizontal_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);

bool fillpothorizontal_pickDelete(MorphismPot *pot, Morphism *morphism)
{
   if(1 > horizontal_host->number_of_nodes || 0 > horizontal_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n0(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, horizontal_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, horizontal_host);
      return false;
   }
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < horizontal_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(horizontal_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 1) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         if(label.length < 1) break;
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
         /* Matching rule atom 2 */
         /* Matching string variable 1. */
         if(item->atom.type != 's') break;
         result = addStringAssignment(morphism, 1, item->atom.str);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicatehorizontal_2(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               horizontal_b2 = true;
               break;
            }
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
            HostAtom sublist[label.length - 1];
            int list_index = 0;
            HostListItem *iterator = start;
            while(iterator != item->next)
            {
               sublist[list_index++] = iterator->atom;
               iterator = iterator->next;
            }
            HostList *list = makeHostList(sublist, label.length - 1, false);
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
         /* Update global booleans representing the node's predicates. */
         evaluatePredicatehorizontal_1(morphism);
         if(evaluateCondition())
         {
            /* All items matched! */
            putMorphism(pot, morphism, "horizontal_pickDelete", horizontal_host);
            /* Reset the boolean variables in the predicates of this node. */
            horizontal_b1 = true;
            removeNodeMap(morphism, 0);
            host_node->matched = false;
            return false;
         }
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            horizontal_b1 = true;
            removeNodeMap(morphism, 0);
            host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}
