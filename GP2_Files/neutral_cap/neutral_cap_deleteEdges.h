#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchneutral_cap_deleteEdges(Morphism *morphism);

void applyneutral_cap_deleteEdges(Morphism *morphism, bool record_changes);
bool fillpotneutral_cap_deleteEdges(MorphismPot *pot, Morphism *morphism);

