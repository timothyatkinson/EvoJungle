#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchdepth_start_initOutput(Morphism *morphism);

void applydepth_start_initOutput(Morphism *morphism, bool record_changes);
bool fillpotdepth_start_initOutput(MorphismPot *pot, Morphism *morphism);

