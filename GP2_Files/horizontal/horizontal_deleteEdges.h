#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchhorizontal_deleteEdges(Morphism *morphism);

void applyhorizontal_deleteEdges(Morphism *morphism, bool record_changes);
bool fillpothorizontal_deleteEdges(MorphismPot *pot, Morphism *morphism);

