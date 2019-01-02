#include "horizontal_removeBlueNeutralNode.h"

#include "horizontal.h"

static bool match_n0(Morphism *morphism);

bool matchhorizontal_removeBlueNeutralNode(Morphism *morphism)
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
      if(host_node->label.mark != 3) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) != 0)) continue;

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
         /* All items matched! */
            return true;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

void applyhorizontal_removeBlueNeutralNode(Morphism *morphism, bool record_changes)
{
   int count;
   for(count = 0; count < morphism->edges; count++)
   {
      if(record_changes)
      {
         Edge *edge = getEdge(horizontal_host, morphism->edge_map[count].host_index);
         /* A hole is created if the edge is not at the right-most index of the array. */
         pushRemovedEdge(edge->label, edge->source, edge->target, edge->index,
                         edge->index < horizontal_host->edges.size - 1);
      }
      removeEdge(horizontal_host, morphism->edge_map[count].host_index);
   }
   for(count = 0; count < morphism->nodes; count++)
   {
      if(record_changes)
      {
         Node *node = getNode(horizontal_host, morphism->node_map[count].host_index);
         /* A hole is created if the node is not at the right-most index of the array. */
         pushRemovedNode(node->root, node->label, node->index,
                         node->index < horizontal_host->nodes.size - 1);
      }
      removeNode(horizontal_host, morphism->node_map[count].host_index);
   }
   initialiseMorphism(morphism, NULL);
   }

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);

bool fillpothorizontal_removeBlueNeutralNode(MorphismPot *pot, Morphism *morphism)
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
      if(host_node->label.mark != 3) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) != 0)) continue;

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
         /* All items matched! */
            putMorphism(pot, morphism, "horizontal_removeBlueNeutralNode", horizontal_host);
            removeNodeMap(morphism, 0);
            host_node->matched = false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

