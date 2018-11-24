#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchneutral_cap_markOutputs(Morphism *morphism);

void applyneutral_cap_markOutputs(Morphism *morphism, bool record_changes);
bool fillpotneutral_cap_markOutputs(MorphismPot *pot, Morphism *morphism);

