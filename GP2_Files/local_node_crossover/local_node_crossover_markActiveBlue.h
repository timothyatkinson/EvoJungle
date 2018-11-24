#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchlocal_node_crossover_markActiveBlue(Morphism *morphism);

void applylocal_node_crossover_markActiveBlue(Morphism *morphism, bool record_changes);
bool fillpotlocal_node_crossover_markActiveBlue(MorphismPot *pot, Morphism *morphism);
