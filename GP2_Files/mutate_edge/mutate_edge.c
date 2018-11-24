#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "mutate_edge_pickEdge.h"
Morphism *M_mutate_edge_pickEdge = NULL;
#include "mutate_edge_markOutputs.h"
Morphism *M_mutate_edge_markOutputs = NULL;
#include "mutate_edge_markDepth.h"
Morphism *M_mutate_edge_markDepth = NULL;
#include "mutate_edge_mutateEdge.h"
Morphism *M_mutate_edge_mutateEdge = NULL;
#include "mutate_edge_unmarkOutputs.h"
Morphism *M_mutate_edge_unmarkOutputs = NULL;

static void mutate_edge_freeMorphisms(void)
{
   freeMorphism(M_mutate_edge_pickEdge);
   freeMorphism(M_mutate_edge_markOutputs);
   freeMorphism(M_mutate_edge_markDepth);
   freeMorphism(M_mutate_edge_mutateEdge);
   freeMorphism(M_mutate_edge_unmarkOutputs);
}

Graph* mutate_edge_host = NULL;
int* mutate_edge_node_map = NULL;
MorphismPot* mutate_edge_pot = NULL;

static void mutate_edge_garbageCollect(void)
{
   mutate_edge_freeMorphisms();
   freePot(mutate_edge_pot);
}

bool mutate_edge_success = true;

int mutate_edge_execute(Graph* host_graph)
{
   mutate_edge_host = host_graph;
   mutate_edge_success = true;
   mutate_edge_pot = makeMorphismPot();
   emptyPot(mutate_edge_pot);
   M_mutate_edge_pickEdge = makeMorphism(2, 1, 3);
   M_mutate_edge_markOutputs = makeMorphism(2, 1, 3);
   M_mutate_edge_markDepth = makeMorphism(4, 1, 11);
   M_mutate_edge_mutateEdge = makeMorphism(3, 1, 5);
   M_mutate_edge_unmarkOutputs = makeMorphism(1, 0, 1);

   /* Try Statement */
   /* Condition */
   int restore_point0 = graph_change_stack == NULL ? 0 : topOfGraphChangeStack();
   do
   {
      /* Rule Call */
      emptyPot(mutate_edge_pot);
      fillpotmutate_edge_pickEdge(mutate_edge_pot, M_mutate_edge_pickEdge);
      if(potSize(mutate_edge_pot) > 0){
         MorphismHolder *holder = drawFromPot(mutate_edge_pot);
         duplicateMorphism(holder->morphism, M_mutate_edge_pickEdge, mutate_edge_host);
         freeMorphism(holder->morphism);
         free(holder);
         applymutate_edge_pickEdge(M_mutate_edge_pickEdge, true);
         mutate_edge_success = true;
      }
      else
      {
         mutate_edge_success = false;
         break;
      }
      emptyPot(mutate_edge_pot);
      /* Loop Statement */
      while(mutate_edge_success)
      {
         /* Rule Call */
         if(matchmutate_edge_markOutputs(M_mutate_edge_markOutputs))
         {
            applymutate_edge_markOutputs(M_mutate_edge_markOutputs, true);
            mutate_edge_success = true;
         }
         else
         {
            mutate_edge_success = false;
         }
      }
      mutate_edge_success = true;
      /* Loop Statement */
      while(mutate_edge_success)
      {
         /* Rule Call */
         if(matchmutate_edge_markDepth(M_mutate_edge_markDepth))
         {
            applymutate_edge_markDepth(M_mutate_edge_markDepth, true);
            mutate_edge_success = true;
         }
         else
         {
            mutate_edge_success = false;
         }
      }
      mutate_edge_success = true;
      /* Rule Call */
      emptyPot(mutate_edge_pot);
      fillpotmutate_edge_mutateEdge(mutate_edge_pot, M_mutate_edge_mutateEdge);
      if(potSize(mutate_edge_pot) > 0){
         MorphismHolder *holder = drawFromPot(mutate_edge_pot);
         duplicateMorphism(holder->morphism, M_mutate_edge_mutateEdge, mutate_edge_host);
         freeMorphism(holder->morphism);
         free(holder);
         applymutate_edge_mutateEdge(M_mutate_edge_mutateEdge, true);
         mutate_edge_success = true;
      }
      else
      {
         mutate_edge_success = false;
         break;
      }
      emptyPot(mutate_edge_pot);
      /* Loop Statement */
      while(mutate_edge_success)
      {
         /* Rule Call */
         if(matchmutate_edge_unmarkOutputs(M_mutate_edge_unmarkOutputs))
         {
            applymutate_edge_unmarkOutputs(M_mutate_edge_unmarkOutputs, true);
            mutate_edge_success = true;
         }
         else
         {
            mutate_edge_success = false;
         }
      }
      mutate_edge_success = true;
   } while(false);

   /* Then Branch */
   if(mutate_edge_success)
   {
      discardChanges(restore_point0);
      /* Skip Statement */
      mutate_edge_success = true;
   }
   /* Else Branch */
   else
   {
      undoChanges(mutate_edge_host, restore_point0);
      mutate_edge_success = true;
      /* Skip Statement */
      mutate_edge_success = true;
   }
   mutate_edge_garbageCollect();
   return 0;
}

