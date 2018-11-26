#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchneutral_cap_pickDelete(Morphism *morphism);

void applyneutral_cap_pickDelete(Morphism *morphism, bool record_changes);
bool fillpotneutral_cap_pickDelete(MorphismPot *pot, Morphism *morphism);

