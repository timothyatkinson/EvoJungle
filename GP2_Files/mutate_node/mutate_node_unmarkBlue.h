#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchmutate_node_unmarkBlue(Morphism *morphism);

void applymutate_node_unmarkBlue(Morphism *morphism, bool record_changes);
bool fillpotmutate_node_unmarkBlue(MorphismPot *pot, Morphism *morphism);

