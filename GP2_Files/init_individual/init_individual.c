#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "init_individual_initNodeCounter.h"
Morphism *M_init_individual_initNodeCounter = NULL;
#include "init_individual_initInput.h"
Morphism *M_init_individual_initInput = NULL;
#include "init_individual_addNode.h"
Morphism *M_init_individual_addNode = NULL;
#include "init_individual_addEdgeToArity.h"
Morphism *M_init_individual_addEdgeToArity = NULL;
#include "init_individual_updateDepth.h"
Morphism *M_init_individual_updateDepth = NULL;
#include "init_individual_decolourNode.h"
Morphism *M_init_individual_decolourNode = NULL;
#include "init_individual_connectOutput.h"
Morphism *M_init_individual_connectOutput = NULL;
#include "init_individual_connectOutput2.h"
Morphism *M_init_individual_connectOutput2 = NULL;
#include "init_individual_deleteNodeCounter.h"
Morphism *M_init_individual_deleteNodeCounter = NULL;
#include "init_individual_removeDepth.h"
Morphism *M_init_individual_removeDepth = NULL;
#include "init_individual_resetInput.h"
Morphism *M_init_individual_resetInput = NULL;

static void init_individual_freeMorphisms(void)
{
   freeMorphism(M_init_individual_initNodeCounter);
   freeMorphism(M_init_individual_initInput);
   freeMorphism(M_init_individual_addNode);
   freeMorphism(M_init_individual_addEdgeToArity);
   freeMorphism(M_init_individual_updateDepth);
   freeMorphism(M_init_individual_decolourNode);
   freeMorphism(M_init_individual_connectOutput);
   freeMorphism(M_init_individual_connectOutput2);
   freeMorphism(M_init_individual_deleteNodeCounter);
   freeMorphism(M_init_individual_removeDepth);
   freeMorphism(M_init_individual_resetInput);
}

Graph* init_individual_host = NULL;
int* init_individual_node_map = NULL;
MorphismPot* init_individual_pot = NULL;

static void init_individual_garbageCollect(void)
{
   init_individual_freeMorphisms();
   freePot(init_individual_pot);
}

bool init_individual_success = true;

int init_individual_execute(Graph* host_graph)
{
   init_individual_host = host_graph;
   init_individual_success = true;
   init_individual_pot = makeMorphismPot();
   emptyPot(init_individual_pot);
   M_init_individual_initNodeCounter = makeMorphism(1, 0, 1);
   M_init_individual_initInput = makeMorphism(1, 0, 1);
   M_init_individual_addNode = makeMorphism(2, 0, 3);
   M_init_individual_addEdgeToArity = makeMorphism(4, 0, 7);
   M_init_individual_updateDepth = makeMorphism(2, 1, 7);
   M_init_individual_decolourNode = makeMorphism(1, 0, 1);
   M_init_individual_connectOutput = makeMorphism(3, 0, 5);
   M_init_individual_connectOutput2 = makeMorphism(3, 0, 5);
   M_init_individual_deleteNodeCounter = makeMorphism(1, 0, 1);
   M_init_individual_removeDepth = makeMorphism(1, 0, 3);
   M_init_individual_resetInput = makeMorphism(1, 0, 2);

   /* Rule Call */
   if(matchinit_individual_initNodeCounter(M_init_individual_initNodeCounter))
   {
      applyinit_individual_initNodeCounter(M_init_individual_initNodeCounter, false);
      init_individual_success = true;
   }
   else
   {
      printf("No output graph: rule init_individual_initNodeCounter not applicable.\n");
      init_individual_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   int restore_point0 = graph_change_stack == NULL ? 0 : topOfGraphChangeStack();
   while(init_individual_success)
   {
      /* Rule Call */
      emptyPot(init_individual_pot);
      fillpotinit_individual_addNode(init_individual_pot, M_init_individual_addNode);
      if(potSize(init_individual_pot) > 0){
         MorphismHolder *holder = drawFromPot(init_individual_pot);
         duplicateMorphism(holder->morphism, M_init_individual_addNode, init_individual_host);
         freeMorphism(holder->morphism);
         free(holder);
         applyinit_individual_addNode(M_init_individual_addNode, true);
         init_individual_success = true;
      }
      else
      {
         init_individual_success = false;
         undoChanges(init_individual_host, restore_point0);
      }
      emptyPot(init_individual_pot);
      if(!init_individual_success) break;

      /* Loop Statement */
      while(init_individual_success)
      {
         /* Rule Call */
         emptyPot(init_individual_pot);
         fillpotinit_individual_addEdgeToArity(init_individual_pot, M_init_individual_addEdgeToArity);
         if(potSize(init_individual_pot) > 0){
            MorphismHolder *holder = drawFromPot(init_individual_pot);
            duplicateMorphism(holder->morphism, M_init_individual_addEdgeToArity, init_individual_host);
            freeMorphism(holder->morphism);
            free(holder);
            applyinit_individual_addEdgeToArity(M_init_individual_addEdgeToArity, true);
            init_individual_success = true;
         }
         else
         {
            init_individual_success = false;
         }
         emptyPot(init_individual_pot);
      }
      init_individual_success = true;
      if(!init_individual_success) break;

      /* Loop Statement */
      while(init_individual_success)
      {
         /* Rule Call */
         if(matchinit_individual_updateDepth(M_init_individual_updateDepth))
         {
            applyinit_individual_updateDepth(M_init_individual_updateDepth, true);
            init_individual_success = true;
         }
         else
         {
            init_individual_success = false;
         }
      }
      init_individual_success = true;
      if(!init_individual_success) break;

      /* Rule Call */
      if(matchinit_individual_decolourNode(M_init_individual_decolourNode))
      {
         applyinit_individual_decolourNode(M_init_individual_decolourNode, true);
         init_individual_success = true;
      }
      else
      {
         init_individual_success = false;
         undoChanges(init_individual_host, restore_point0);
      }
      /* Graph changes from loop body may not have been used.
         Discard them so that future graph roll backs are uncorrupted. */
      if(init_individual_success) discardChanges(restore_point0);
   }
   init_individual_success = true;
   /* Loop Statement */
   while(init_individual_success)
   {
      /* Rule Call */
      emptyPot(init_individual_pot);
      fillpotinit_individual_connectOutput2(init_individual_pot, M_init_individual_connectOutput2);
      if(potSize(init_individual_pot) > 0){
         MorphismHolder *holder = drawFromPot(init_individual_pot);
         duplicateMorphism(holder->morphism, M_init_individual_connectOutput2, init_individual_host);
         freeMorphism(holder->morphism);
         free(holder);
         applyinit_individual_connectOutput2(M_init_individual_connectOutput2, false);
         init_individual_success = true;
      }
      else
      {
         init_individual_success = false;
      }
      emptyPot(init_individual_pot);
   }
   init_individual_success = true;
   /* Loop Statement */
   while(init_individual_success)
   {
      /* Rule Call */
      if(matchinit_individual_removeDepth(M_init_individual_removeDepth))
      {
         applyinit_individual_removeDepth(M_init_individual_removeDepth, false);
         init_individual_success = true;
      }
      else
      {
         init_individual_success = false;
      }
   }
   init_individual_success = true;
   /* Loop Statement */
   while(init_individual_success)
   {
      /* Rule Call */
      if(matchinit_individual_decolourNode(M_init_individual_decolourNode))
      {
         applyinit_individual_decolourNode(M_init_individual_decolourNode, false);
         init_individual_success = true;
      }
      else
      {
         init_individual_success = false;
      }
   }
   init_individual_success = true;
   /* Rule Call */
   if(matchinit_individual_deleteNodeCounter(M_init_individual_deleteNodeCounter))
   {
      applyinit_individual_deleteNodeCounter(M_init_individual_deleteNodeCounter, false);
      init_individual_success = true;
   }
   else
   {
      printf("No output graph: rule init_individual_deleteNodeCounter not applicable.\n");
      init_individual_garbageCollect();
      return 0;
   }
   init_individual_garbageCollect();
   return 0;
}

