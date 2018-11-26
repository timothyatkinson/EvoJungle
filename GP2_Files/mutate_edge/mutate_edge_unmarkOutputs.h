#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchmutate_edge_unmarkOutputs(Morphism *morphism);

void applymutate_edge_unmarkOutputs(Morphism *morphism, bool record_changes);
bool fillpotmutate_edge_unmarkOutputs(MorphismPot *pot, Morphism *morphism);

