#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchhorizontal_markGreenEdge(Morphism *morphism);

void applyhorizontal_markGreenEdge(Morphism *morphism, bool record_changes);
bool fillpothorizontal_markGreenEdge(MorphismPot *pot, Morphism *morphism);

