#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchinit_individual_resetInput(Morphism *morphism);

void applyinit_individual_resetInput(Morphism *morphism, bool record_changes);
bool fillpotinit_individual_resetInput(MorphismPot *pot, Morphism *morphism);

