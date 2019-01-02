#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchhorizontal_moveInputGreen(Morphism *morphism);

void applyhorizontal_moveInputGreen(Morphism *morphism, bool record_changes);
bool fillpothorizontal_moveInputGreen(MorphismPot *pot, Morphism *morphism);

