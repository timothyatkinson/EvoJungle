#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

bool matchinit_individual_decolourNode(Morphism *morphism);

void applyinit_individual_decolourNode(Morphism *morphism, bool record_changes);
bool fillpotinit_individual_decolourNode(MorphismPot *pot, Morphism *morphism);

