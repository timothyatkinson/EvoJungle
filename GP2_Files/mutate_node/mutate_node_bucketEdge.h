#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchmutate_node_bucketEdge(Morphism *morphism);

void applymutate_node_bucketEdge(Morphism *morphism, bool record_changes);
bool fillpotmutate_node_bucketEdge(MorphismPot *pot, Morphism *morphism);

