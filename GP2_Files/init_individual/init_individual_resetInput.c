#include "init_individual_resetInput.h"

#include "init_individual.h"

static bool match_n0(Morphism *morphism);

bool matchinit_individual_resetInput(Morphism *morphism)
{
   if(1 > init_individual_host->number_of_nodes || 0 > init_individual_host->number_of_edges) return false;
   if(match_n0(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, init_individual_host);
      return false;
   }
}

static bool match_n0(Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < init_individual_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(init_individual_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
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
         if(label.length != 3) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         int result = -1;
         /* Matching integer variable 0. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 0, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->next;

         /* Matching rule atom 2. */
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->next;

         /* Matching rule atom 3. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "INPUT") != 0) break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* All items matched! */
            return true;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

void applyinit_individual_resetInput(Morphism *morphism, bool record_changes)
{
   int var_0 = getIntegerValue(morphism, 0);
   int host_node_index = lookupNode(morphism, 0);
   HostLabel label_n0 = getNodeLabel(init_individual_host, host_node_index);
   HostLabel label;
   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 2;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 'i';
   array0[index0++].num = var_0;
   array0[index0].type = 's';
   array0[index0++].str = "INPUT";
   if(list_length0 > 0)
   {
      HostList *list0 = makeHostList(array0, list_length0, false);
      label = makeHostLabel(0, list_length0, list0);
   }
   else label = makeEmptyLabel(0);

   if(equalHostLabels(label_n0, label)) removeHostList(label.list);
   else
   {
      if(record_changes) pushRelabelledNode(host_node_index, label_n0);
      relabelNode(init_individual_host, host_node_index, label);
   }
   /* Reset the morphism. */
   initialiseMorphism(morphism, init_individual_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);

bool fillpotinit_individual_resetInput(MorphismPot *pot, Morphism *morphism)
{
   if(1 > init_individual_host->number_of_nodes || 0 > init_individual_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n0(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, init_individual_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, init_individual_host);
      return false;
   }
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < init_individual_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(init_individual_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
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
         if(label.length != 3) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         int result = -1;
         /* Matching integer variable 0. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 0, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->next;

         /* Matching rule atom 2. */
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->next;

         /* Matching rule atom 3. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "INPUT") != 0) break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* All items matched! */
            putMorphism(pot, morphism, "init_individual_resetInput", init_individual_host);
            removeNodeMap(morphism, 0);
            host_node->matched = false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

