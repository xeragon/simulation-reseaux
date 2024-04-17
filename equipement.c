#include <stdio.h>
#include "liaison.h"
#include "equipement.h"
#include "reseau.h"
#include "stdlib.h"

void InitEquipemennt(Equipement *equipement, EquipementUnion *eqU, EquipementType type)
{
    equipement->type = type;
    equipement->eq = *eqU;
    equipement->nbVoisin = 0;
    
    if (type == SWITCH)
    {
        equipement->port = malloc(eqU->sw.Nb_P * (sizeof(Port)));
    }
    else
    {
        equipement->port = malloc(sizeof(Port));
    }
}

void Visualiser_equipement(Equipement *eq)
{
    if (eq->type == SWITCH) // eq est un switch
    {
        Visualiser_switch(&eq->eq.sw);
        printf("\nmes voisins sont : \n\t") ;
        for (int i = 0; i < eq->nbVoisin; i++)
        {
            printf("%d ",eq->port[i].IndexEqVoisin);
        }
        printf("\n");
        
        
    }
    else if (eq->type == STATION) // eq est une station
    {
        Visualiser_station(&eq->eq.st);
        printf("\nmon voisin est : %d" , eq->port[0].IndexEqVoisin);
    }
}
