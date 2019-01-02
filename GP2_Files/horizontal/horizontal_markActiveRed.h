#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchhorizontal_markActiveRed(Morphism *morphism);

void applyhorizontal_markActiveRed(Morphism *morphism, bool record_changes);
bool fillpothorizontal_markActiveRed(MorphismPot *pot, Morphism *morphism);

