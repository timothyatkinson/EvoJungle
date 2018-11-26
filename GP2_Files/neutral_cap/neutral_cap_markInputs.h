#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchneutral_cap_markInputs(Morphism *morphism);

void applyneutral_cap_markInputs(Morphism *morphism, bool record_changes);
bool fillpotneutral_cap_markInputs(MorphismPot *pot, Morphism *morphism);

