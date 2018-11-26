#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchdepth_start_initInput(Morphism *morphism);

void applydepth_start_initInput(Morphism *morphism, bool record_changes);
bool fillpotdepth_start_initInput(MorphismPot *pot, Morphism *morphism);

