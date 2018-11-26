#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchdepth_start_initNode(Morphism *morphism);

void applydepth_start_initNode(Morphism *morphism, bool record_changes);
bool fillpotdepth_start_initNode(MorphismPot *pot, Morphism *morphism);

