#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchhorizontal_deleteNode(Morphism *morphism);

void applyhorizontal_deleteNode(Morphism *morphism, bool record_changes);
bool fillpothorizontal_deleteNode(MorphismPot *pot, Morphism *morphism);

