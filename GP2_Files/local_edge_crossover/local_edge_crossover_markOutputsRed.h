#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchlocal_edge_crossover_markOutputsRed(Morphism *morphism);

void applylocal_edge_crossover_markOutputsRed(Morphism *morphism, bool record_changes);
bool fillpotlocal_edge_crossover_markOutputsRed(MorphismPot *pot, Morphism *morphism);

