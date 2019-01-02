#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchlocal_node_crossover_markRedGreen(Morphism *morphism);

void applylocal_node_crossover_markRedGreen(Morphism *morphism, bool record_changes);
bool fillpotlocal_node_crossover_markRedGreen(MorphismPot *pot, Morphism *morphism);

