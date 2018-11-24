#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchneutral_cap_deleteNode(Morphism *morphism);

void applyneutral_cap_deleteNode(Morphism *morphism, bool record_changes);
bool fillpotneutral_cap_deleteNode(MorphismPot *pot, Morphism *morphism);

