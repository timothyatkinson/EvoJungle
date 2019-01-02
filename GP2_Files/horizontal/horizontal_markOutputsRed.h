#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchhorizontal_markOutputsRed(Morphism *morphism);

void applyhorizontal_markOutputsRed(Morphism *morphism, bool record_changes);
bool fillpothorizontal_markOutputsRed(MorphismPot *pot, Morphism *morphism);

