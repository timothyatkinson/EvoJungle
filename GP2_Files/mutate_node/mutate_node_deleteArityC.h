#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchmutate_node_deleteArityC(Morphism *morphism);

void applymutate_node_deleteArityC(Morphism *morphism, bool record_changes);
bool fillpotmutate_node_deleteArityC(MorphismPot *pot, Morphism *morphism);

