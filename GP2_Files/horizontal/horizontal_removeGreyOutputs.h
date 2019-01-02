#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchhorizontal_removeGreyOutputs(Morphism *morphism);

void applyhorizontal_removeGreyOutputs(Morphism *morphism, bool record_changes);
bool fillpothorizontal_removeGreyOutputs(MorphismPot *pot, Morphism *morphism);

