
#include "liaison.h"
#include <stdio.h>

void InitLiaison(Liaison *liaison, int eq1, int eq2, int poids)
{
    liaison->eq1 = eq1;
    liaison->eq2 = eq2;
    liaison->poids = poids;
}

void Visualiser_liaison(Liaison *li, Equipement *eqTab)
{
    printf("===== index equipement 1 ===== \n" );
    printf("%d\n", li->eq1);
    printf("===== mac equipement 1 ===== \n" );
    printOctets(eqTab[li->eq1].eq.st.mac,6);
    printf("\n");
    printf("===== index equipement 2 ===== \n" );
    printf("%d\n", li->eq2);
    printf("===== mac equipement 2 ===== \n" );
    printOctets(eqTab[li->eq2].eq.st.mac,6);
    printf("\n");
    printf("Poid %d \n", li->poids);
}