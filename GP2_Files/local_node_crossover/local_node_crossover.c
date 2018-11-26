#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "local_node_crossover_markOutputsRed.h"
Morphism *M_local_node_crossover_markOutputsRed = NULL;
#include "local_node_crossover_markOutputsBlue.h"
Morphism *M_local_node_crossover_markOutputsBlue = NULL;
#include "local_node_crossover_markActiveRed.h"
Morphism *M_local_node_crossover_markActiveRed = NULL;
#include "local_node_crossover_markActiveBlue.h"
Morphism *M_local_node_crossover_markActiveBlue = NULL;
#include "local_node_crossover_crossover_point.h"
Morphism *M_local_node_crossover_crossover_point = NULL;
#include "local_node_crossover_markGreenFunc.h"
Morphism *M_local_node_crossover_markGreenFunc = NULL;
#include "local_node_crossover_markGreenEdge.h"
Morphism *M_local_node_crossover_markGreenEdge = NULL;
#include "local_node_crossover_moveInputGreen.h"
Morphism *M_local_node_crossover_moveInputGreen = NULL;
#include "local_node_crossover_makeGreenRed.h"
Morphism *M_local_node_crossover_makeGreenRed = NULL;
#include "local_node_crossover_makeBlueRed.h"
Morphism *M_local_node_crossover_makeBlueRed = NULL;
#include "local_node_crossover_makeGreyRed.h"
Morphism *M_local_node_crossover_makeGreyRed = NULL;

static void local_node_crossover_freeMorphisms(void)
{
   freeMorphism(M_local_node_crossover_markOutputsRed);
   freeMorphism(M_local_node_crossover_markOutputsBlue);
   freeMorphism(M_local_node_crossover_markActiveRed);
   freeMorphism(M_local_node_crossover_markActiveBlue);
   freeMorphism(M_local_node_crossover_crossover_point);
   freeMorphism(M_local_node_crossover_markGreenFunc);
   freeMorphism(M_local_node_crossover_markGreenEdge);
   freeMorphism(M_local_node_crossover_moveInputGreen);
   freeMorphism(M_local_node_crossover_makeGreenRed);
   freeMorphism(M_local_node_crossover_makeBlueRed);
   freeMorphism(M_local_node_crossover_makeGreyRed);
}

Graph* local_node_crossover_host = NULL;
int* local_node_crossover_node_map = NULL;
MorphismPot* local_node_crossover_pot = NULL;

static void local_node_crossover_garbageCollect(void)
{
   local_node_crossover_freeMorphisms();
   freePot(local_node_crossover_pot);
}

bool local_node_crossover_success = true;

int local_node_crossover_execute(Graph* host_graph)
{
   local_node_crossover_host = host_graph;
   local_node_crossover_success = true;
   local_node_crossover_pot = makeMorphismPot();
   emptyPot(local_node_crossover_pot);
   M_local_node_crossover_markOutputsRed = makeMorphism(1, 0, 1);
   M_local_node_crossover_markOutputsBlue = makeMorphism(1, 0, 1);
   M_local_node_crossover_markActiveRed = makeMorphism(2, 1, 3);
   M_local_node_crossover_markActiveBlue = makeMorphism(2, 1, 3);
   M_local_node_crossover_crossover_point = makeMorphism(5, 2, 13);
   M_local_node_crossover_markGreenFunc = makeMorphism(2, 1, 4);
   M_local_node_crossover_markGreenEdge = makeMorphism(2, 1, 3);
   M_local_node_crossover_moveInputGreen = makeMorphism(3, 1, 6);
   M_local_node_crossover_makeGreenRed = makeMorphism(1, 0, 1);
   M_local_node_crossover_makeBlueRed = makeMorphism(2, 1, 3);
   M_local_node_crossover_makeGreyRed = makeMorphism(2, 1, 3);

   /* Loop Statement */
   while(local_node_crossover_success)
   {
      /* Rule Call */
      if(matchlocal_node_crossover_markOutputsRed(M_local_node_crossover_markOutputsRed))
      {
         applylocal_node_crossover_markOutputsRed(M_local_node_crossover_markOutputsRed, false);
         local_node_crossover_success = true;
      }
      else
      {
         local_node_crossover_success = false;
      }
   }
   local_node_crossover_success = true;
   /* Rule Call */
   if(matchlocal_node_crossover_markOutputsBlue(M_local_node_crossover_markOutputsBlue))
   {
      applylocal_node_crossover_markOutputsBlue(M_local_node_crossover_markOutputsBlue, false);
      local_node_crossover_success = true;
   }
   else
   {
      printf("No output graph: rule local_node_crossover_markOutputsBlue not applicable.\n");
      local_node_crossover_garbageCollect();
      return 0;
   }
   /* Loop Statement */
   while(local_node_crossover_success)
   {
      /* Rule Call */
      if(matchlocal_node_crossover_markActiveRed(M_local_node_crossover_markActiveRed))
      {
         applylocal_node_crossover_markActiveRed(M_local_node_crossover_markActiveRed, false);
         local_node_crossover_success = true;
      }
      else
      {
         local_node_crossover_success = false;
      }
   }
   local_node_crossover_success = true;
   /* Loop Statement */
   while(local_node_crossover_success)
   {
      /* Rule Call */
      if(matchlocal_node_crossover_markActiveBlue(M_local_node_crossover_markActiveBlue))
      {
         applylocal_node_crossover_markActiveBlue(M_local_node_crossover_markActiveBlue, false);
         local_node_crossover_success = true;
      }
      else
      {
         local_node_crossover_success = false;
      }
   }
   local_node_crossover_success = true;
   /* Rule Call */
   emptyPot(local_node_crossover_pot);
   fillpotlocal_node_crossover_crossover_point(local_node_crossover_pot, M_local_node_crossover_crossover_point);
   if(potSize(local_node_crossover_pot) > 0){
      MorphismHolder *holder = drawFromPot(local_node_crossover_pot);
      duplicateMorphism(holder->morphism, M_local_node_crossover_crossover_point, local_node_crossover_host);
      freeMorphism(holder->morphism);
      free(holder);
      applylocal_node_crossover_crossover_point(M_local_node_crossover_crossover_point, false);
      local_node_crossover_success = true;
   }
   else
   {
      printf("No output graph: rule local_node_crossover_crossover_point not applicable.\n");
      local_node_crossover_garbageCollect();
      return 0;
   }
   emptyPot(local_node_crossover_pot);
   /* Loop Statement */
   while(local_node_crossover_success)
   {
      /* Rule Set Call */
      do
      {
         if(matchlocal_node_crossover_markGreenFunc(M_local_node_crossover_markGreenFunc))
         {
            applylocal_node_crossover_markGreenFunc(M_local_node_crossover_markGreenFunc, false);
            local_node_crossover_success = true;
            break;
         }
         if(matchlocal_node_crossover_markGreenEdge(M_local_node_crossover_markGreenEdge))
         {
            applylocal_node_crossover_markGreenEdge(M_local_node_crossover_markGreenEdge, false);
            local_node_crossover_success = true;
            break;
         }
         if(matchlocal_node_crossover_moveInputGreen(M_local_node_crossover_moveInputGreen))
         {
            applylocal_node_crossover_moveInputGreen(M_local_node_crossover_moveInputGreen, false);
            local_node_crossover_success = true;
         }
         else
         {
            local_node_crossover_success = false;
         }
      } while(false);
   }
   local_node_crossover_success = true;
   /* Loop Statement */
   while(local_node_crossover_success)
   {
      /* Rule Set Call */
      do
      {
         if(matchlocal_node_crossover_makeGreenRed(M_local_node_crossover_makeGreenRed))
         {
            applylocal_node_crossover_makeGreenRed(M_local_node_crossover_makeGreenRed, false);
            local_node_crossover_success = true;
            break;
         }
         if(matchlocal_node_crossover_makeBlueRed(M_local_node_crossover_makeBlueRed))
         {
            applylocal_node_crossover_makeBlueRed(M_local_node_crossover_makeBlueRed, false);
            local_node_crossover_success = true;
            break;
         }
         if(matchlocal_node_crossover_makeGreyRed(M_local_node_crossover_makeGreyRed))
         {
            applylocal_node_crossover_makeGreyRed(M_local_node_crossover_makeGreyRed, false);
            local_node_crossover_success = true;
         }
         else
         {
            local_node_crossover_success = false;
         }
      } while(false);
   }
   local_node_crossover_success = true;
   local_node_crossover_garbageCollect();
   return 0;
}

