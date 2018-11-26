#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchmutate_edge_markDepth(Morphism *morphism);

void applymutate_edge_markDepth(Morphism *morphism, bool record_changes);
bool fillpotmutate_edge_markDepth(MorphismPot *pot, Morphism *morphism);

