#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchhorizontal_makeGreenRed(Morphism *morphism);

void applyhorizontal_makeGreenRed(Morphism *morphism, bool record_changes);
bool fillpothorizontal_makeGreenRed(MorphismPot *pot, Morphism *morphism);

