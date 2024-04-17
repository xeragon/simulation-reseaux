#pragma once
#include "types.h"
#include "equipement.h"
typedef struct Liaison
{
    int eq1;    
    int eq2;
    int poids;    
}Liaison;

void InitLiaison(Liaison *liaison, int eq1, int eq2, int poids);
void Visualiser_liaison(Liaison *li, Equipement *eqTab)
;
