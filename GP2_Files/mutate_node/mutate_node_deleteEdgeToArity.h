#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchmutate_node_deleteEdgeToArity(Morphism *morphism);

void applymutate_node_deleteEdgeToArity(Morphism *morphism, bool record_changes);
bool fillpotmutate_node_deleteEdgeToArity(MorphismPot *pot, Morphism *morphism);

