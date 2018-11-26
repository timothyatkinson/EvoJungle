#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchneutral_cap_countNeutral(Morphism *morphism);

void applyneutral_cap_countNeutral(Morphism *morphism, bool record_changes);
bool fillpotneutral_cap_countNeutral(MorphismPot *pot, Morphism *morphism);

