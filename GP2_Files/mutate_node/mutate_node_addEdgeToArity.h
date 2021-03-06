#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchmutate_node_addEdgeToArity(Morphism *morphism);

void applymutate_node_addEdgeToArity(Morphism *morphism, bool record_changes);
bool fillpotmutate_node_addEdgeToArity(MorphismPot *pot, Morphism *morphism);

