#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchinit_individual_updateDepth(Morphism *morphism);

void applyinit_individual_updateDepth(Morphism *morphism, bool record_changes);
bool fillpotinit_individual_updateDepth(MorphismPot *pot, Morphism *morphism);

