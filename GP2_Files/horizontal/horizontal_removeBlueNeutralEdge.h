#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchhorizontal_removeBlueNeutralEdge(Morphism *morphism);

void applyhorizontal_removeBlueNeutralEdge(Morphism *morphism, bool record_changes);
bool fillpothorizontal_removeBlueNeutralEdge(MorphismPot *pot, Morphism *morphism);

