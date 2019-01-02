#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "horizontal_markOutputsRed.h"
Morphism *M_horizontal_markOutputsRed = NULL;
#include "horizontal_markOutputsBlue.h"
Morphism *M_horizontal_markOutputsBlue = NULL;
#include "horizontal_markActiveRed.h"
Morphism *M_horizontal_markActiveRed = NULL;
#include "horizontal_markActiveBlue.h"
Morphism *M_horizontal_markActiveBlue = NULL;
#include "horizontal_removeGreyOutputs.h"
Morphism *M_horizontal_removeGreyOutputs = NULL;
#include "horizontal_removeBlueNeutralNode.h"
Morphism *M_horizontal_removeBlueNeutralNode = NULL;
#include "horizontal_removeBlueNeutralEdge.h"
Morphism *M_horizontal_removeBlueNeutralEdge = NULL;
#include "horizontal_markGreenFunc.h"
Morphism *M_horizontal_markGreenFunc = NULL;
#include "horizontal_pickDelete.h"
Morphism *M_horizontal_pickDelete = NULL;
#include "horizontal_deleteEdges.h"
Morphism *M_horizontal_deleteEdges = NULL;
#include "horizontal_deleteNode.h"
Morphism *M_horizontal_deleteNode = NULL;
#include "horizontal_markGreenEdge.h"
Morphism *M_horizontal_markGreenEdge = NULL;
#include "horizontal_moveInputGreen.h"
Morphism *M_horizontal_moveInputGreen = NULL;
#include "horizontal_makeGreenRed.h"
Morphism *M_horizontal_makeGreenRed = NULL;
#include "horizontal_makeBlueRed.h"
Morphism *M_horizontal_makeBlueRed = NULL;

static void horizontal_freeMorphisms(void)
{
   freeMorphism(M_horizontal_markOutputsRed);
   freeMorphism(M_horizontal_markOutputsBlue);
   freeMorphism(M_horizontal_markActiveRed);
   freeMorphism(M_horizontal_markActiveBlue);
   freeMorphism(M_horizontal_removeGreyOutputs);
   freeMorphism(M_horizontal_removeBlueNeutralNode);
   freeMorphism(M_horizontal_removeBlueNeutralEdge);
   freeMorphism(M_horizontal_markGreenFunc);
   freeMorphism(M_horizontal_pickDelete);
   freeMorphism(M_horizontal_deleteEdges);
   freeMorphism(M_horizontal_deleteNode);
   freeMorphism(M_horizontal_markGreenEdge);
   freeMorphism(M_horizontal_moveInputGreen);
   freeMorphism(M_horizontal_makeGreenRed);
   freeMorphism(M_horizontal_makeBlueRed);
}

Graph* horizontal_host = NULL;
int* horizontal_node_map = NULL;
MorphismPot* horizontal_pot = NULL;

static void horizontal_garbageCollect(void)
{
   horizontal_freeMorphisms();
   freePot(horizontal_pot);
}

bool horizontal_success = true;

int horizontal_execute(Graph* host_graph)
{
   horizontal_host = host_graph;
   horizontal_success = true;
   horizontal_pot = makeMorphismPot();
   emptyPot(horizontal_pot);
   M_horizontal_markOutputsRed = makeMorphism(1, 0, 1);
   M_horizontal_markOutputsBlue = makeMorphism(1, 0, 1);
   M_horizontal_markActiveRed = makeMorphism(2, 1, 3);
   M_horizontal_markActiveBlue = makeMorphism(2, 1, 3);
   M_horizontal_removeGreyOutputs = makeMorphism(2, 1, 3);
   M_horizontal_removeBlueNeutralNode = makeMorphism(1, 0, 1);
   M_horizontal_removeBlueNeutralEdge = makeMorphism(2, 1, 3);
   M_horizontal_markGreenFunc = makeMorphism(1, 0, 2);
   M_horizontal_pickDelete = makeMorphism(1, 0, 2);
   M_horizontal_deleteEdges = makeMorphism(2, 1, 3);
   M_horizontal_deleteNode = makeMorphism(1, 0, 1);
   M_horizontal_markGreenEdge = makeMorphism(2, 1, 3);
   M_horizontal_moveInputGreen = makeMorphism(3, 1, 6);
   M_horizontal_makeGreenRed = makeMorphism(1, 0, 1);
   M_horizontal_makeBlueRed = makeMorphism(2, 1, 3);

   /* Loop Statement */
   while(horizontal_success)
   {
      /* Rule Call */
      if(matchhorizontal_markOutputsRed(M_horizontal_markOutputsRed))
      {
         applyhorizontal_markOutputsRed(M_horizontal_markOutputsRed, false);
         horizontal_success = true;
      }
      else
      {
         horizontal_success = false;
      }
   }
   horizontal_success = true;
   /* Rule Call */
   if(matchhorizontal_markOutputsBlue(M_horizontal_markOutputsBlue))
   {
      applyhorizontal_markOutputsBlue(M_horizontal_markOutputsBlue, false);
      horizontal_success = true;
   }
   else
   {
      printf("No output graph: rule horizontal_markOutputsBlue not applicable.\n");
      horizontal_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   while(horizontal_success)
   {
      /* Rule Call */
      if(matchhorizontal_markActiveRed(M_horizontal_markActiveRed))
      {
         applyhorizontal_markActiveRed(M_horizontal_markActiveRed, false);
         horizontal_success = true;
      }
      else
      {
         horizontal_success = false;
      }
   }
   horizontal_success = true;
   /* Loop Statement */
   while(horizontal_success)
   {
      /* Rule Call */
      if(matchhorizontal_markActiveBlue(M_horizontal_markActiveBlue))
      {
         applyhorizontal_markActiveBlue(M_horizontal_markActiveBlue, false);
         horizontal_success = true;
      }
      else
      {
         horizontal_success = false;
      }
   }
   horizontal_success = true;
   /* Loop Statement */
   while(horizontal_success)
   {
      /* Rule Call */
      if(matchhorizontal_removeGreyOutputs(M_horizontal_removeGreyOutputs))
      {
         applyhorizontal_removeGreyOutputs(M_horizontal_removeGreyOutputs, false);
         horizontal_success = true;
      }
      else
      {
         horizontal_success = false;
      }
   }
   horizontal_success = true;
   /* Loop Statement */
   while(horizontal_success)
   {
      /* Rule Set Call */
      do
      {
         if(matchhorizontal_removeBlueNeutralNode(M_horizontal_removeBlueNeutralNode))
         {
            applyhorizontal_removeBlueNeutralNode(M_horizontal_removeBlueNeutralNode, false);
            horizontal_success = true;
            break;
         }
         if(matchhorizontal_removeBlueNeutralEdge(M_horizontal_removeBlueNeutralEdge))
         {
            applyhorizontal_removeBlueNeutralEdge(M_horizontal_removeBlueNeutralEdge, false);
            horizontal_success = true;
         }
         else
         {
            horizontal_success = false;
         }
      } while(false);
   }
   horizontal_success = true;
   /* Loop Statement */
   int restore_point0 = graph_change_stack == NULL ? 0 : topOfGraphChangeStack();
   while(horizontal_success)
   {
      /* Rule Call */
      if(matchhorizontal_markGreenFunc(M_horizontal_markGreenFunc))
      {
         applyhorizontal_markGreenFunc(M_horizontal_markGreenFunc, true);
         horizontal_success = true;
      }
      else
      {
         horizontal_success = false;
         undoChanges(horizontal_host, restore_point0);
      }
      if(!horizontal_success) break;

      /* Rule Call */
      emptyPot(horizontal_pot);
      fillpothorizontal_pickDelete(horizontal_pot, M_horizontal_pickDelete);
      if(potSize(horizontal_pot) > 0){
         MorphismHolder *holder = drawFromPot(horizontal_pot);
         duplicateMorphism(holder->morphism, M_horizontal_pickDelete, horizontal_host);
         freeMorphism(holder->morphism);
         free(holder);
         applyhorizontal_pickDelete(M_horizontal_pickDelete, true);
         horizontal_success = true;
      }
      else
      {
         horizontal_success = false;
         undoChanges(horizontal_host, restore_point0);
      }
      emptyPot(horizontal_pot);
      if(!horizontal_success) break;

      /* Loop Statement */
      while(horizontal_success)
      {
         /* Rule Call */
         if(matchhorizontal_deleteEdges(M_horizontal_deleteEdges))
         {
            applyhorizontal_deleteEdges(M_horizontal_deleteEdges, true);
            horizontal_success = true;
         }
         else
         {
            horizontal_success = false;
         }
      }
      horizontal_success = true;
      if(!horizontal_success) break;

      /* Rule Call */
      if(matchhorizontal_deleteNode(M_horizontal_deleteNode))
      {
         applyhorizontal_deleteNode(M_horizontal_deleteNode, true);
         horizontal_success = true;
      }
      else
      {
         horizontal_success = false;
         undoChanges(horizontal_host, restore_point0);
      }
      /* Graph changes from loop body may not have been used.
         Discard them so that future graph roll backs are uncorrupted. */
      if(horizontal_success) discardChanges(restore_point0);
   }
   horizontal_success = true;
   /* Loop Statement */
   while(horizontal_success)
   {
      /* Rule Set Call */
      do
      {
         if(matchhorizontal_markGreenEdge(M_horizontal_markGreenEdge))
         {
            applyhorizontal_markGreenEdge(M_horizontal_markGreenEdge, false);
            horizontal_success = true;
            break;
         }
         if(matchhorizontal_moveInputGreen(M_horizontal_moveInputGreen))
         {
            applyhorizontal_moveInputGreen(M_horizontal_moveInputGreen, false);
            horizontal_success = true;
         }
         else
         {
            horizontal_success = false;
         }
      } while(false);
   }
   horizontal_success = true;
   /* Loop Statement */
   while(horizontal_success)
   {
      /* Rule Set Call */
      do
      {
         if(matchhorizontal_makeGreenRed(M_horizontal_makeGreenRed))
         {
            applyhorizontal_makeGreenRed(M_horizontal_makeGreenRed, false);
            horizontal_success = true;
            break;
         }
         if(matchhorizontal_makeBlueRed(M_horizontal_makeBlueRed))
         {
            applyhorizontal_makeBlueRed(M_horizontal_makeBlueRed, false);
            horizontal_success = true;
         }
         else
         {
            horizontal_success = false;
         }
      } while(false);
   }
   horizontal_success = true;
   horizontal_garbageCollect();
   return 0;
}

