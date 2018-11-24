#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchinit_individual_deleteNodeCounter(Morphism *morphism);

void applyinit_individual_deleteNodeCounter(Morphism *morphism, bool record_changes);
bool fillpotinit_individual_deleteNodeCounter(MorphismPot *pot, Morphism *morphism);

