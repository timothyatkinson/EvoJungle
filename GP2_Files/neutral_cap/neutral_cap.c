#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "neutral_cap_markOutputs.h"
Morphism *M_neutral_cap_markOutputs = NULL;
#include "neutral_cap_markInputs.h"
Morphism *M_neutral_cap_markInputs = NULL;
#include "neutral_cap_markActive.h"
Morphism *M_neutral_cap_markActive = NULL;
#include "neutral_cap_initNCounter.h"
Morphism *M_neutral_cap_initNCounter = NULL;
#include "neutral_cap_countNeutral.h"
Morphism *M_neutral_cap_countNeutral = NULL;
#include "neutral_cap_pickDelete.h"
Morphism *M_neutral_cap_pickDelete = NULL;
#include "neutral_cap_deleteEdges.h"
Morphism *M_neutral_cap_deleteEdges = NULL;
#include "neutral_cap_deleteNode.h"
Morphism *M_neutral_cap_deleteNode = NULL;
#include "neutral_cap_unmark.h"
Morphism *M_neutral_cap_unmark = NULL;

static void neutral_cap_freeMorphisms(void)
{
   freeMorphism(M_neutral_cap_markOutputs);
   freeMorphism(M_neutral_cap_markInputs);
   freeMorphism(M_neutral_cap_markActive);
   freeMorphism(M_neutral_cap_initNCounter);
   freeMorphism(M_neutral_cap_countNeutral);
   freeMorphism(M_neutral_cap_pickDelete);
   freeMorphism(M_neutral_cap_deleteEdges);
   freeMorphism(M_neutral_cap_deleteNode);
   freeMorphism(M_neutral_cap_unmark);
}

Graph* neutral_cap_host = NULL;
int* neutral_cap_node_map = NULL;
MorphismPot* neutral_cap_pot = NULL;

static void neutral_cap_garbageCollect(void)
{
   neutral_cap_freeMorphisms();
   freePot(neutral_cap_pot);
}

bool neutral_cap_success = true;

int neutral_cap_execute(Graph* host_graph)
{
   neutral_cap_host = host_graph;
   neutral_cap_success = true;
   neutral_cap_pot = makeMorphismPot();
   emptyPot(neutral_cap_pot);
   M_neutral_cap_markOutputs = makeMorphism(1, 0, 1);
   M_neutral_cap_markInputs = makeMorphism(1, 0, 1);
   M_neutral_cap_markActive = makeMorphism(2, 1, 3);
   M_neutral_cap_initNCounter = makeMorphism(1, 0, 1);
   M_neutral_cap_countNeutral = makeMorphism(2, 0, 3);
   M_neutral_cap_pickDelete = makeMorphism(3, 0, 3);
   M_neutral_cap_deleteEdges = makeMorphism(2, 1, 3);
   M_neutral_cap_deleteNode = makeMorphism(2, 0, 2);
   M_neutral_cap_unmark = makeMorphism(1, 0, 1);

   /* Loop Statement */
   while(neutral_cap_success)
   {
      /* Rule Call */
      if(matchneutral_cap_markOutputs(M_neutral_cap_markOutputs))
      {
         applyneutral_cap_markOutputs(M_neutral_cap_markOutputs, false);
         neutral_cap_success = true;
      }
      else
      {
         neutral_cap_success = false;
      }
   }
   neutral_cap_success = true;
   /* Loop Statement */
   while(neutral_cap_success)
   {
      /* Rule Call */
      if(matchneutral_cap_markInputs(M_neutral_cap_markInputs))
      {
         applyneutral_cap_markInputs(M_neutral_cap_markInputs, false);
         neutral_cap_success = true;
      }
      else
      {
         neutral_cap_success = false;
      }
   }
   neutral_cap_success = true;
   /* Loop Statement */
   while(neutral_cap_success)
   {
      /* Rule Call */
      if(matchneutral_cap_markActive(M_neutral_cap_markActive))
      {
         applyneutral_cap_markActive(M_neutral_cap_markActive, false);
         neutral_cap_success = true;
      }
      else
      {
         neutral_cap_success = false;
      }
   }
   neutral_cap_success = true;
   /* Rule Call */
   if(matchneutral_cap_initNCounter(M_neutral_cap_initNCounter))
   {
      applyneutral_cap_initNCounter(M_neutral_cap_initNCounter, false);
      neutral_cap_success = true;
   }
   else
   {
      printf("No output graph: rule neutral_cap_initNCounter not applicable.\n");
      neutral_cap_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   while(neutral_cap_success)
   {
      /* Rule Call */
      if(matchneutral_cap_countNeutral(M_neutral_cap_countNeutral))
      {
         applyneutral_cap_countNeutral(M_neutral_cap_countNeutral, false);
         neutral_cap_success = true;
      }
      else
      {
         neutral_cap_success = false;
      }
   }
   neutral_cap_success = true;
   /* Loop Statement */
   int restore_point0 = graph_change_stack == NULL ? 0 : topOfGraphChangeStack();
   while(neutral_cap_success)
   {
      /* Rule Call */
      emptyPot(neutral_cap_pot);
      fillpotneutral_cap_pickDelete(neutral_cap_pot, M_neutral_cap_pickDelete);
      if(potSize(neutral_cap_pot) > 0){
         MorphismHolder *holder = drawFromPot(neutral_cap_pot);
         duplicateMorphism(holder->morphism, M_neutral_cap_pickDelete, neutral_cap_host);
         freeMorphism(holder->morphism);
         free(holder);
         applyneutral_cap_pickDelete(M_neutral_cap_pickDelete, true);
         neutral_cap_success = true;
      }
      else
      {
         neutral_cap_success = false;
         undoChanges(neutral_cap_host, restore_point0);
      }
      emptyPot(neutral_cap_pot);
      if(!neutral_cap_success) break;

      /* Loop Statement */
      while(neutral_cap_success)
      {
         /* Rule Call */
         if(matchneutral_cap_deleteEdges(M_neutral_cap_deleteEdges))
         {
            applyneutral_cap_deleteEdges(M_neutral_cap_deleteEdges, true);
            neutral_cap_success = true;
         }
         else
         {
            neutral_cap_success = false;
         }
      }
      neutral_cap_success = true;
      if(!neutral_cap_success) break;

      /* Rule Call */
      if(matchneutral_cap_deleteNode(M_neutral_cap_deleteNode))
      {
         applyneutral_cap_deleteNode(M_neutral_cap_deleteNode, true);
         neutral_cap_success = true;
      }
      else
      {
         neutral_cap_success = false;
         undoChanges(neutral_cap_host, restore_point0);
      }
      /* Graph changes from loop body may not have been used.
         Discard them so that future graph roll backs are uncorrupted. */
      if(neutral_cap_success) discardChanges(restore_point0);
   }
   neutral_cap_success = true;
   /* Loop Statement */
   while(neutral_cap_success)
   {
      /* Rule Call */
      if(matchneutral_cap_unmark(M_neutral_cap_unmark))
      {
         applyneutral_cap_unmark(M_neutral_cap_unmark, false);
         neutral_cap_success = true;
      }
      else
      {
         neutral_cap_success = false;
      }
   }
   neutral_cap_success = true;
   neutral_cap_garbageCollect();
   return 0;
}

