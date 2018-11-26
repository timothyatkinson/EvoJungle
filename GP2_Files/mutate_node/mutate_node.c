#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "mutate_node_pickNode.h"
Morphism *M_mutate_node_pickNode = NULL;
#include "mutate_node_mutateNode.h"
Morphism *M_mutate_node_mutateNode = NULL;
#include "mutate_node_markOutputsBlue.h"
Morphism *M_mutate_node_markOutputsBlue = NULL;
#include "mutate_node_markOutputsRed.h"
Morphism *M_mutate_node_markOutputsRed = NULL;
#include "mutate_node_markDepth.h"
Morphism *M_mutate_node_markDepth = NULL;
#include "mutate_node_addEdgeToArity.h"
Morphism *M_mutate_node_addEdgeToArity = NULL;
#include "mutate_node_deleteEdgeToArity.h"
Morphism *M_mutate_node_deleteEdgeToArity = NULL;
#include "mutate_node_resetArityCounter.h"
Morphism *M_mutate_node_resetArityCounter = NULL;
#include "mutate_node_bucketEdge.h"
Morphism *M_mutate_node_bucketEdge = NULL;
#include "mutate_node_readdEdge.h"
Morphism *M_mutate_node_readdEdge = NULL;
#include "mutate_node_deleteArityC.h"
Morphism *M_mutate_node_deleteArityC = NULL;
#include "mutate_node_unmarkBlue.h"
Morphism *M_mutate_node_unmarkBlue = NULL;
#include "mutate_node_unmarkRed.h"
Morphism *M_mutate_node_unmarkRed = NULL;

static void mutate_node_freeMorphisms(void)
{
   freeMorphism(M_mutate_node_pickNode);
   freeMorphism(M_mutate_node_mutateNode);
   freeMorphism(M_mutate_node_markOutputsBlue);
   freeMorphism(M_mutate_node_markOutputsRed);
   freeMorphism(M_mutate_node_markDepth);
   freeMorphism(M_mutate_node_addEdgeToArity);
   freeMorphism(M_mutate_node_deleteEdgeToArity);
   freeMorphism(M_mutate_node_resetArityCounter);
   freeMorphism(M_mutate_node_bucketEdge);
   freeMorphism(M_mutate_node_readdEdge);
   freeMorphism(M_mutate_node_deleteArityC);
   freeMorphism(M_mutate_node_unmarkBlue);
   freeMorphism(M_mutate_node_unmarkRed);
}

Graph* mutate_node_host = NULL;
int* mutate_node_node_map = NULL;
MorphismPot* mutate_node_pot = NULL;

static void mutate_node_garbageCollect(void)
{
   mutate_node_freeMorphisms();
   freePot(mutate_node_pot);
}

bool mutate_node_success = true;

int mutate_node_execute(Graph* host_graph)
{
   mutate_node_host = host_graph;
   mutate_node_success = true;
   mutate_node_pot = makeMorphismPot();
   emptyPot(mutate_node_pot);
   M_mutate_node_pickNode = makeMorphism(1, 0, 2);
   M_mutate_node_mutateNode = makeMorphism(2, 0, 4);
   M_mutate_node_markOutputsBlue = makeMorphism(2, 1, 3);
   M_mutate_node_markOutputsRed = makeMorphism(2, 1, 3);
   M_mutate_node_markDepth = makeMorphism(3, 0, 11);
   M_mutate_node_addEdgeToArity = makeMorphism(4, 0, 6);
   M_mutate_node_deleteEdgeToArity = makeMorphism(4, 1, 7);
   M_mutate_node_resetArityCounter = makeMorphism(1, 0, 1);
   M_mutate_node_bucketEdge = makeMorphism(2, 1, 3);
   M_mutate_node_readdEdge = makeMorphism(3, 1, 4);
   M_mutate_node_deleteArityC = makeMorphism(2, 0, 2);
   M_mutate_node_unmarkBlue = makeMorphism(1, 0, 1);
   M_mutate_node_unmarkRed = makeMorphism(1, 0, 1);

   /* Rule Call */
   emptyPot(mutate_node_pot);
   fillpotmutate_node_pickNode(mutate_node_pot, M_mutate_node_pickNode);
   if(potSize(mutate_node_pot) > 0){
      MorphismHolder *holder = drawFromPot(mutate_node_pot);
      duplicateMorphism(holder->morphism, M_mutate_node_pickNode, mutate_node_host);
      freeMorphism(holder->morphism);
      free(holder);
      applymutate_node_pickNode(M_mutate_node_pickNode, false);
      mutate_node_success = true;
   }
   else
   {
      printf("No output graph: rule mutate_node_pickNode not applicable.\n");
      mutate_node_garbageCollect();
      return 0;
   }
   emptyPot(mutate_node_pot);
   /* Rule Call */
   emptyPot(mutate_node_pot);
   fillpotmutate_node_mutateNode(mutate_node_pot, M_mutate_node_mutateNode);
   if(potSize(mutate_node_pot) > 0){
      MorphismHolder *holder = drawFromPot(mutate_node_pot);
      duplicateMorphism(holder->morphism, M_mutate_node_mutateNode, mutate_node_host);
      freeMorphism(holder->morphism);
      free(holder);
      applymutate_node_mutateNode(M_mutate_node_mutateNode, false);
      mutate_node_success = true;
   }
   else
   {
      printf("No output graph: rule mutate_node_mutateNode not applicable.\n");
      mutate_node_garbageCollect();
      return 0;
   }
   emptyPot(mutate_node_pot);
   /* Loop Statement */
   while(mutate_node_success)
   {
      /* Rule Set Call */
      do
      {
         if(matchmutate_node_markOutputsBlue(M_mutate_node_markOutputsBlue))
         {
            applymutate_node_markOutputsBlue(M_mutate_node_markOutputsBlue, false);
            mutate_node_success = true;
            break;
         }
         if(matchmutate_node_markOutputsRed(M_mutate_node_markOutputsRed))
         {
            applymutate_node_markOutputsRed(M_mutate_node_markOutputsRed, false);
            mutate_node_success = true;
         }
         else
         {
            mutate_node_success = false;
         }
      } while(false);
   }
   mutate_node_success = true;
   /* Loop Statement */
   while(mutate_node_success)
   {
      /* Rule Call */
      if(matchmutate_node_markDepth(M_mutate_node_markDepth))
      {
         applymutate_node_markDepth(M_mutate_node_markDepth, false);
         mutate_node_success = true;
      }
      else
      {
         mutate_node_success = false;
      }
   }
   mutate_node_success = true;
   /* Loop Statement */
   while(mutate_node_success)
   {
      /* Rule Set Call */
      do
      {
      bool valid[2];
      double weight[2];
      double totalWeight = 0.0;
      bool someValid = false;
      valid[0] = false;
      weight[0] = 1.000000;
      if(matchmutate_node_addEdgeToArity(M_mutate_node_addEdgeToArity)){
         valid[0] = true;
         totalWeight = totalWeight + weight[0];
         someValid = true;
      }
      initialiseMorphism(M_mutate_node_addEdgeToArity, mutate_node_host);
      valid[1] = false;
      weight[1] = 1.000000;
      if(matchmutate_node_deleteEdgeToArity(M_mutate_node_deleteEdgeToArity)){
         valid[1] = true;
         totalWeight = totalWeight + weight[1];
         someValid = true;
      }
      initialiseMorphism(M_mutate_node_deleteEdgeToArity, mutate_node_host);
      if (someValid){
         double r = ((double)rand() / (double)RAND_MAX);
         r = r * totalWeight;
         double sum = 0.0;
         if(valid[0]){
            sum = sum + weight[0];
            if(r <= sum){
               emptyPot(mutate_node_pot);
               fillpotmutate_node_addEdgeToArity(mutate_node_pot, M_mutate_node_addEdgeToArity);
               if(potSize(mutate_node_pot) > 0){
                  MorphismHolder *holder = drawFromPot(mutate_node_pot);
                  duplicateMorphism(holder->morphism, M_mutate_node_addEdgeToArity, mutate_node_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applymutate_node_addEdgeToArity(M_mutate_node_addEdgeToArity, false);
                  mutate_node_success = true;
                  break;
               }
               emptyPot(mutate_node_pot);
            }
         }
         if(valid[1]){
            sum = sum + weight[1];
            if(r <= sum && r > sum - weight[1]){
               emptyPot(mutate_node_pot);
               fillpotmutate_node_deleteEdgeToArity(mutate_node_pot, M_mutate_node_deleteEdgeToArity);
               if(potSize(mutate_node_pot) > 0){
                  MorphismHolder *holder = drawFromPot(mutate_node_pot);
                  duplicateMorphism(holder->morphism, M_mutate_node_deleteEdgeToArity, mutate_node_host);
                  freeMorphism(holder->morphism);
                  free(holder);
                  applymutate_node_deleteEdgeToArity(M_mutate_node_deleteEdgeToArity, false);
                  mutate_node_success = true;
                  break;
               }
               emptyPot(mutate_node_pot);
            }
         }
      } else {
      mutate_node_success = false;
      }
      } while(false);
   }
   mutate_node_success = true;
   /* Loop Statement */
   while(mutate_node_success)
   {
      /* Rule Call */
      if(matchmutate_node_unmarkBlue(M_mutate_node_unmarkBlue))
      {
         applymutate_node_unmarkBlue(M_mutate_node_unmarkBlue, false);
         mutate_node_success = true;
      }
      else
      {
         mutate_node_success = false;
      }
   }
   mutate_node_success = true;
   /* Rule Call */
   if(matchmutate_node_resetArityCounter(M_mutate_node_resetArityCounter))
   {
      applymutate_node_resetArityCounter(M_mutate_node_resetArityCounter, false);
      mutate_node_success = true;
   }
   else
   {
      printf("No output graph: rule mutate_node_resetArityCounter not applicable.\n");
      mutate_node_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   while(mutate_node_success)
   {
      /* Rule Call */
      if(matchmutate_node_bucketEdge(M_mutate_node_bucketEdge))
      {
         applymutate_node_bucketEdge(M_mutate_node_bucketEdge, false);
         mutate_node_success = true;
      }
      else
      {
         mutate_node_success = false;
      }
   }
   mutate_node_success = true;
   /* Loop Statement */
   while(mutate_node_success)
   {
      /* Rule Call */
      emptyPot(mutate_node_pot);
      fillpotmutate_node_readdEdge(mutate_node_pot, M_mutate_node_readdEdge);
      if(potSize(mutate_node_pot) > 0){
         MorphismHolder *holder = drawFromPot(mutate_node_pot);
         duplicateMorphism(holder->morphism, M_mutate_node_readdEdge, mutate_node_host);
         freeMorphism(holder->morphism);
         free(holder);
         applymutate_node_readdEdge(M_mutate_node_readdEdge, false);
         mutate_node_success = true;
      }
      else
      {
         mutate_node_success = false;
      }
      emptyPot(mutate_node_pot);
   }
   mutate_node_success = true;
   /* Rule Call */
   if(matchmutate_node_deleteArityC(M_mutate_node_deleteArityC))
   {
      applymutate_node_deleteArityC(M_mutate_node_deleteArityC, false);
      mutate_node_success = true;
   }
   else
   {
      printf("No output graph: rule mutate_node_deleteArityC not applicable.\n");
      mutate_node_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   while(mutate_node_success)
   {
      /* Rule Set Call */
      do
      {
         if(matchmutate_node_unmarkBlue(M_mutate_node_unmarkBlue))
         {
            applymutate_node_unmarkBlue(M_mutate_node_unmarkBlue, false);
            mutate_node_success = true;
            break;
         }
         if(matchmutate_node_unmarkRed(M_mutate_node_unmarkRed))
         {
            applymutate_node_unmarkRed(M_mutate_node_unmarkRed, false);
            mutate_node_success = true;
         }
         else
         {
            mutate_node_success = false;
         }
      } while(false);
   }
   mutate_node_success = true;
   mutate_node_garbageCollect();
   return 0;
}

