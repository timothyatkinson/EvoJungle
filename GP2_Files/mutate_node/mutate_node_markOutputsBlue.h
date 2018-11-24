#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_node_markOutputsBlue(Morphism *morphism);

void applymutate_node_markOutputsBlue(Morphism *morphism, bool record_changes);
bool fillpotmutate_node_markOutputsBlue(MorphismPot *pot, Morphism *morphism);
