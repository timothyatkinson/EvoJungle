#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchneutral_cap_unmark(Morphism *morphism);

void applyneutral_cap_unmark(Morphism *morphism, bool record_changes);
bool fillpotneutral_cap_unmark(MorphismPot *pot, Morphism *morphism);

