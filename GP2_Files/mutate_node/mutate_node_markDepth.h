#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchmutate_node_markDepth(Morphism *morphism);

void applymutate_node_markDepth(Morphism *morphism, bool record_changes);
bool fillpotmutate_node_markDepth(MorphismPot *pot, Morphism *morphism);

