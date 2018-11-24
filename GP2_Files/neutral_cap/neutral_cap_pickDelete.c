#include "neutral_cap_pickDelete.h"

#include "neutral_cap.h"

bool neutral_cap_b1 = true;
bool neutral_cap_b2 = true;

static bool evaluateCondition(void)
{
   return (neutral_cap_b1 && neutral_cap_b2);
}

static void evaluatePredicateneutral_cap_1(Morphism *morphism)
{
   int n0 = lookupNode(morphism, 0);
   /* If the node is not yet matched by the morphism, return. */
   if(n0 == -1) return;

   if(getIndegree(neutral_cap_host, n0) == 0) neutral_cap_b1 = true;
   else neutral_cap_b1 = false;
}

static void evaluatePredicateneutral_cap_2(Morphism *morphism)
{
   Assignment assignment_1 = getAssignment(morphism, 1);
   /* If the variable is not yet assigned, return. */
   if(assignment_1.type == 'n') return;
   int var_1 = getIntegerValue(morphism, 1);

   Assignment assignment_2 = getAssignment(morphism, 2);
   /* If the variable is not yet assigned, return. */
   if(assignment_2.type == 'n') return;
   int var_2 = getIntegerValue(morphism, 2);

   if(var_1 > var_2) neutral_cap_b2 = true;
   else neutral_cap_b2 = false;
}

static bool match_n1(Morphism *morphism);
static bool match_n2(Morphism *morphism);
static bool match_n0(Morphism *morphism);

bool matchneutral_cap_pickDelete(Morphism *morphism)
{
   if(3 > neutral_cap_host->number_of_nodes || 0 > neutral_cap_host->number_of_edges) return false;
   if(match_n1(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, neutral_cap_host);
      return false;
   }
}

static bool match_n1(Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(neutral_cap_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(neutral_cap_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

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
         else if(strcmp(item->atom.str, "Neutral") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateneutral_cap_2(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               neutral_cap_b2 = true;
               break;
            }
         }
         else break;
         match = true;
      } while(false);

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
   }
   return false;
}

static bool match_n2(Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(neutral_cap_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(neutral_cap_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

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
         else if(strcmp(item->atom.str, "MaxNeutral") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 2. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 2, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateneutral_cap_2(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               neutral_cap_b2 = true;
               break;
            }
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 2, host_node->index, new_assignments);
         host_node->matched = true;
         if(match_n0(morphism)) return true;
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

static bool match_n0(Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < neutral_cap_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(neutral_cap_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 4) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 0 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 0, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 0, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 0, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicateneutral_cap_1(morphism);
         if(evaluateCondition())
         {
            /* All items matched! */
            return true;
         }
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            neutral_cap_b1 = true;
            removeNodeMap(morphism, 0);
            host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

void applyneutral_cap_pickDelete(Morphism *morphism, bool record_changes)
{
   int var_1 = getIntegerValue(morphism, 1);
   int host_node_index = lookupNode(morphism, 0);
   HostLabel label_n0 = getNodeLabel(neutral_cap_host, host_node_index);
   if(record_changes) pushRemarkedNode(host_node_index, label_n0.mark);
   changeNodeMark(neutral_cap_host, host_node_index, 3);

   host_node_index = lookupNode(morphism, 1);
   HostLabel label_n1 = getNodeLabel(neutral_cap_host, host_node_index);
   HostLabel label;
   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 2;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 's';
   array0[index0++].str = "Neutral";
   array0[index0].type = 'i';
   array0[index0++].num = var_1 - 1;
   if(list_length0 > 0)
   {
      HostList *list0 = makeHostList(array0, list_length0, false);
      label = makeHostLabel(0, list_length0, list0);
   }
   else label = makeEmptyLabel(0);

   if(equalHostLabels(label_n1, label)) removeHostList(label.list);
   else
   {
      if(record_changes) pushRelabelledNode(host_node_index, label_n1);
      relabelNode(neutral_cap_host, host_node_index, label);
   }
   /* Reset the morphism. */
   initialiseMorphism(morphism, neutral_cap_host);
}

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n2(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);

bool fillpotneutral_cap_pickDelete(MorphismPot *pot, Morphism *morphism)
{
   if(3 > neutral_cap_host->number_of_nodes || 0 > neutral_cap_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n1(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, neutral_cap_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, neutral_cap_host);
      return false;
   }
}

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(neutral_cap_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(neutral_cap_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

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
         else if(strcmp(item->atom.str, "Neutral") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateneutral_cap_2(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               neutral_cap_b2 = true;
               break;
            }
         }
         else break;
         match = true;
      } while(false);

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
   }
   return false;
}

static bool fillpot_n2(MorphismPot *pot, Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(neutral_cap_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(neutral_cap_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

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
         else if(strcmp(item->atom.str, "MaxNeutral") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 2. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 2, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
            /* Update global booleans for the variable's predicates. */
            evaluatePredicateneutral_cap_2(morphism);
            if(!evaluateCondition())
            {
               /* Reset the boolean variables in the predicates of this variable. */
               neutral_cap_b2 = true;
               break;
            }
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 2, host_node->index, new_assignments);
         host_node->matched = true;
         if(fillpot_n0(pot, morphism)) return true;
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

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < neutral_cap_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(neutral_cap_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 4) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 0 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 0, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 0, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 0, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* Update global booleans representing the node's predicates. */
         evaluatePredicateneutral_cap_1(morphism);
         if(evaluateCondition())
         {
            /* All items matched! */
            putMorphism(pot, morphism, "neutral_cap_pickDelete", neutral_cap_host);
            /* Reset the boolean variables in the predicates of this node. */
            neutral_cap_b1 = true;
            removeNodeMap(morphism, 0);
            host_node->matched = false;
            return false;
         }
         else
         {
            /* Reset the boolean variables in the predicates of this node. */
            neutral_cap_b1 = true;
            removeNodeMap(morphism, 0);
            host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

