#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_node_markOutputsRed(Morphism *morphism);

void applymutate_node_markOutputsRed(Morphism *morphism, bool record_changes);
bool fillpotmutate_node_markOutputsRed(MorphismPot *pot, Morphism *morphism);

