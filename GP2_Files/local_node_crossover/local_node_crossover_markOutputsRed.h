#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchlocal_node_crossover_markOutputsRed(Morphism *morphism);

void applylocal_node_crossover_markOutputsRed(Morphism *morphism, bool record_changes);
bool fillpotlocal_node_crossover_markOutputsRed(MorphismPot *pot, Morphism *morphism);

