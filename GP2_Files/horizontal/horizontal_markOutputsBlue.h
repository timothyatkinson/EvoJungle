#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchhorizontal_markOutputsBlue(Morphism *morphism);

void applyhorizontal_markOutputsBlue(Morphism *morphism, bool record_changes);
bool fillpothorizontal_markOutputsBlue(MorphismPot *pot, Morphism *morphism);

