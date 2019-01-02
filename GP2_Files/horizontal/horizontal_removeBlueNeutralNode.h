#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchhorizontal_removeBlueNeutralNode(Morphism *morphism);

void applyhorizontal_removeBlueNeutralNode(Morphism *morphism, bool record_changes);
bool fillpothorizontal_removeBlueNeutralNode(MorphismPot *pot, Morphism *morphism);

