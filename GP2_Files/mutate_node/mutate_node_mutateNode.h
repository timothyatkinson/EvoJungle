#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmutate_node_mutateNode(Morphism *morphism);

void applymutate_node_mutateNode(Morphism *morphism, bool record_changes);
bool fillpotmutate_node_mutateNode(MorphismPot *pot, Morphism *morphism);

