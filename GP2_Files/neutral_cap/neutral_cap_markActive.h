#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchneutral_cap_markActive(Morphism *morphism);

void applyneutral_cap_markActive(Morphism *morphism, bool record_changes);
bool fillpotneutral_cap_markActive(MorphismPot *pot, Morphism *morphism);

