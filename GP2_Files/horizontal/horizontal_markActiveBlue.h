#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchhorizontal_markActiveBlue(Morphism *morphism);

void applyhorizontal_markActiveBlue(Morphism *morphism, bool record_changes);
bool fillpothorizontal_markActiveBlue(MorphismPot *pot, Morphism *morphism);

