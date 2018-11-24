#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchdepth_start_unmark(Morphism *morphism);

void applydepth_start_unmark(Morphism *morphism, bool record_changes);
bool fillpotdepth_start_unmark(MorphismPot *pot, Morphism *morphism);

