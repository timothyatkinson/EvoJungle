#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchhorizontal_pickDelete(Morphism *morphism);

void applyhorizontal_pickDelete(Morphism *morphism, bool record_changes);
bool fillpothorizontal_pickDelete(MorphismPot *pot, Morphism *morphism);

