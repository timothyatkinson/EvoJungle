#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_node_resetArityCounter(Morphism *morphism);

void applymutate_node_resetArityCounter(Morphism *morphism, bool record_changes);
bool fillpotmutate_node_resetArityCounter(MorphismPot *pot, Morphism *morphism);

