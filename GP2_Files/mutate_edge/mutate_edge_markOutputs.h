#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchmutate_edge_markOutputs(Morphism *morphism);

void applymutate_edge_markOutputs(Morphism *morphism, bool record_changes);
bool fillpotmutate_edge_markOutputs(MorphismPot *pot, Morphism *morphism);

