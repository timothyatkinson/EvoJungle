#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchinit_individual_removeDepth(Morphism *morphism);

void applyinit_individual_removeDepth(Morphism *morphism, bool record_changes);
bool fillpotinit_individual_removeDepth(MorphismPot *pot, Morphism *morphism);

