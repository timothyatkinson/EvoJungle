#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "local_edge_crossover_markOutputsRed.h"
Morphism *M_local_edge_crossover_markOutputsRed = NULL;
#include "local_edge_crossover_markOutputsBlue.h"
Morphism *M_local_edge_crossover_markOutputsBlue = NULL;
#include "local_edge_crossover_markActiveRed.h"
Morphism *M_local_edge_crossover_markActiveRed = NULL;
#include "local_edge_crossover_markActiveBlue.h"
Morphism *M_local_edge_crossover_markActiveBlue = NULL;
#include "local_edge_crossover_crossover_point.h"
Morphism *M_local_edge_crossover_crossover_point = NULL;
#include "local_edge_crossover_crossover_point1.h"
Morphism *M_local_edge_crossover_crossover_point1 = NULL;
#include "local_edge_crossover_crossover_point2.h"
Morphism *M_local_edge_crossover_crossover_point2 = NULL;
#include "local_edge_crossover_markGreenFunc.h"
Morphism *M_local_edge_crossover_markGreenFunc = NULL;
#include "local_edge_crossover_markGreenEdge.h"
Morphism *M_local_edge_crossover_markGreenEdge = NULL;
#include "local_edge_crossover_moveInputGreen.h"
Morphism *M_local_edge_crossover_moveInputGreen = NULL;
#include "local_edge_crossover_makeGreenRed.h"
Morphism *M_local_edge_crossover_makeGreenRed = NULL;
#include "local_edge_crossover_makeBlueRed.h"
Morphism *M_local_edge_crossover_makeBlueRed = NULL;
#include "local_edge_crossover_makeGreyRed.h"
Morphism *M_local_edge_crossover_makeGreyRed = NULL;

static void local_edge_crossover_freeMorphisms(void)
{
   freeMorphism(M_local_edge_crossover_markOutputsRed);
   freeMorphism(M_local_edge_crossover_markOutputsBlue);
   freeMorphism(M_local_edge_crossover_markActiveRed);
   freeMorphism(M_local_edge_crossover_markActiveBlue);
   freeMorphism(M_local_edge_crossover_crossover_point);
   freeMorphism(M_local_edge_crossover_crossover_point1);
   freeMorphism(M_local_edge_crossover_crossover_point2);
   freeMorphism(M_local_edge_crossover_markGreenFunc);
   freeMorphism(M_local_edge_crossover_markGreenEdge);
   freeMorphism(M_local_edge_crossover_moveInputGreen);
   freeMorphism(M_local_edge_crossover_makeGreenRed);
   freeMorphism(M_local_edge_crossover_makeBlueRed);
   freeMorphism(M_local_edge_crossover_makeGreyRed);
}

Graph* local_edge_crossover_host = NULL;
int* local_edge_crossover_node_map = NULL;
MorphismPot* local_edge_crossover_pot = NULL;

static void local_edge_crossover_garbageCollect(void)
{
   local_edge_crossover_freeMorphisms();
   freePot(local_edge_crossover_pot);
}

bool local_edge_crossover_success = true;

int local_edge_crossover_execute(Graph* host_graph)
{
   local_edge_crossover_host = host_graph;
   local_edge_crossover_success = true;
   local_edge_crossover_pot = makeMorphismPot();
   emptyPot(local_edge_crossover_pot);
   M_local_edge_crossover_markOutputsRed = makeMorphism(1, 0, 1);
   M_local_edge_crossover_markOutputsBlue = makeMorphism(1, 0, 1);
   M_local_edge_crossover_markActiveRed = makeMorphism(2, 1, 3);
   M_local_edge_crossover_markActiveBlue = makeMorphism(2, 1, 3);
   M_local_edge_crossover_crossover_point = makeMorphism(5, 2, 13);
   M_local_edge_crossover_crossover_point1 = makeMorphism(2, 1, 3);
   M_local_edge_crossover_crossover_point2 = makeMorphism(5, 2, 13);
   M_local_edge_crossover_markGreenFunc = makeMorphism(2, 1, 4);
   M_local_edge_crossover_markGreenEdge = makeMorphism(2, 1, 3);
   M_local_edge_crossover_moveInputGreen = makeMorphism(3, 1, 6);
   M_local_edge_crossover_makeGreenRed = makeMorphism(1, 0, 1);
   M_local_edge_crossover_makeBlueRed = makeMorphism(2, 1, 3);
   M_local_edge_crossover_makeGreyRed = makeMorphism(2, 1, 3);

   /* Loop Statement */
   while(local_edge_crossover_success)
   {
      /* Rule Call */
      if(matchlocal_edge_crossover_markOutputsRed(M_local_edge_crossover_markOutputsRed))
      {
         applylocal_edge_crossover_markOutputsRed(M_local_edge_crossover_markOutputsRed, false);
         local_edge_crossover_success = true;
      }
      else
      {
         local_edge_crossover_success = false;
      }
   }
   local_edge_crossover_success = true;
   /* Rule Call */
   if(matchlocal_edge_crossover_markOutputsBlue(M_local_edge_crossover_markOutputsBlue))
   {
      applylocal_edge_crossover_markOutputsBlue(M_local_edge_crossover_markOutputsBlue, false);
      local_edge_crossover_success = true;
   }
   else
   {
      printf("No output graph: rule local_edge_crossover_markOutputsBlue not applicable.\n");
      local_edge_crossover_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   while(local_edge_crossover_success)
   {
      /* Rule Call */
      if(matchlocal_edge_crossover_markActiveRed(M_local_edge_crossover_markActiveRed))
      {
         applylocal_edge_crossover_markActiveRed(M_local_edge_crossover_markActiveRed, false);
         local_edge_crossover_success = true;
      }
      else
      {
         local_edge_crossover_success = false;
      }
   }
   local_edge_crossover_success = true;
   /* Loop Statement */
   while(local_edge_crossover_success)
   {
      /* Rule Call */
      if(matchlocal_edge_crossover_markActiveBlue(M_local_edge_crossover_markActiveBlue))
      {
         applylocal_edge_crossover_markActiveBlue(M_local_edge_crossover_markActiveBlue, false);
         local_edge_crossover_success = true;
      }
      else
      {
         local_edge_crossover_success = false;
      }
   }
   local_edge_crossover_success = true;
   /* Rule Call */
   emptyPot(local_edge_crossover_pot);
   fillpotlocal_edge_crossover_crossover_point(local_edge_crossover_pot, M_local_edge_crossover_crossover_point);
   if(potSize(local_edge_crossover_pot) > 0){
      MorphismHolder *holder = drawFromPot(local_edge_crossover_pot);
      duplicateMorphism(holder->morphism, M_local_edge_crossover_crossover_point, local_edge_crossover_host);
      freeMorphism(holder->morphism);
      free(holder);
      applylocal_edge_crossover_crossover_point(M_local_edge_crossover_crossover_point, false);
      local_edge_crossover_success = true;
   }
   else
   {
      printf("No output graph: rule local_edge_crossover_crossover_point not applicable.\n");
      local_edge_crossover_garbageCollect();
      return 0;
   }
   emptyPot(local_edge_crossover_pot);
   /* Loop Statement */
   while(local_edge_crossover_success)
   {
      /* Rule Set Call */
      do
      {
         if(matchlocal_edge_crossover_markGreenFunc(M_local_edge_crossover_markGreenFunc))
         {
            applylocal_edge_crossover_markGreenFunc(M_local_edge_crossover_markGreenFunc, false);
            local_edge_crossover_success = true;
            break;
         }
         if(matchlocal_edge_crossover_markGreenEdge(M_local_edge_crossover_markGreenEdge))
         {
            applylocal_edge_crossover_markGreenEdge(M_local_edge_crossover_markGreenEdge, false);
            local_edge_crossover_success = true;
            break;
         }
         if(matchlocal_edge_crossover_moveInputGreen(M_local_edge_crossover_moveInputGreen))
         {
            applylocal_edge_crossover_moveInputGreen(M_local_edge_crossover_moveInputGreen, false);
            local_edge_crossover_success = true;
         }
         else
         {
            local_edge_crossover_success = false;
         }
      } while(false);
   }
   local_edge_crossover_success = true;
   /* Loop Statement */
   while(local_edge_crossover_success)
   {
      /* Rule Set Call */
      do
      {
         if(matchlocal_edge_crossover_makeGreenRed(M_local_edge_crossover_makeGreenRed))
         {
            applylocal_edge_crossover_makeGreenRed(M_local_edge_crossover_makeGreenRed, false);
            local_edge_crossover_success = true;
            break;
         }
         if(matchlocal_edge_crossover_makeBlueRed(M_local_edge_crossover_makeBlueRed))
         {
            applylocal_edge_crossover_makeBlueRed(M_local_edge_crossover_makeBlueRed, false);
            local_edge_crossover_success = true;
            break;
         }
         if(matchlocal_edge_crossover_makeGreyRed(M_local_edge_crossover_makeGreyRed))
         {
            applylocal_edge_crossover_makeGreyRed(M_local_edge_crossover_makeGreyRed, false);
            local_edge_crossover_success = true;
         }
         else
         {
            local_edge_crossover_success = false;
         }
      } while(false);
   }
   local_edge_crossover_success = true;
   local_edge_crossover_garbageCollect();
   return 0;
}

