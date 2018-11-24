#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "depth_start_initInput.h"
Morphism *M_depth_start_initInput = NULL;
#include "depth_start_initOutput.h"
Morphism *M_depth_start_initOutput = NULL;
#include "depth_start_initNode.h"
Morphism *M_depth_start_initNode = NULL;
#include "depth_start_unmark.h"
Morphism *M_depth_start_unmark = NULL;

static void depth_start_freeMorphisms(void)
{
   freeMorphism(M_depth_start_initInput);
   freeMorphism(M_depth_start_initOutput);
   freeMorphism(M_depth_start_initNode);
   freeMorphism(M_depth_start_unmark);
}

Graph* depth_start_host = NULL;
int* depth_start_node_map = NULL;
MorphismPot* depth_start_pot = NULL;

static void depth_start_garbageCollect(void)
{
   depth_start_freeMorphisms();
   freePot(depth_start_pot);
}

bool depth_start_success = true;

int depth_start_execute(Graph* host_graph)
{
   depth_start_host = host_graph;
   depth_start_success = true;
   depth_start_pot = makeMorphismPot();
   emptyPot(depth_start_pot);
   M_depth_start_initInput = makeMorphism(1, 0, 1);
   M_depth_start_initOutput = makeMorphism(1, 0, 1);
   M_depth_start_initNode = makeMorphism(1, 0, 2);
   M_depth_start_unmark = makeMorphism(1, 0, 1);

   /* Loop Statement */
   while(depth_start_success)
   {
      /* Rule Set Call */
      do
      {
         if(matchdepth_start_initInput(M_depth_start_initInput))
         {
            applydepth_start_initInput(M_depth_start_initInput, false);
            depth_start_success = true;
            break;
         }
         if(matchdepth_start_initOutput(M_depth_start_initOutput))
         {
            applydepth_start_initOutput(M_depth_start_initOutput, false);
            depth_start_success = true;
         }
         else
         {
            depth_start_success = false;
         }
      } while(false);
   }
   depth_start_success = true;
   /* Loop Statement */
   while(depth_start_success)
   {
      /* Rule Call */
      if(matchdepth_start_initNode(M_depth_start_initNode))
      {
         applydepth_start_initNode(M_depth_start_initNode, false);
         depth_start_success = true;
      }
      else
      {
         depth_start_success = false;
      }
   }
   depth_start_success = true;
   /* Loop Statement */
   while(depth_start_success)
   {
      /* Rule Call */
      if(matchdepth_start_unmark(M_depth_start_unmark))
      {
         applydepth_start_unmark(M_depth_start_unmark, false);
         depth_start_success = true;
      }
      else
      {
         depth_start_success = false;
      }
   }
   depth_start_success = true;
   depth_start_garbageCollect();
   return 0;
}

