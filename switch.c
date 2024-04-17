#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "switch.h"

void InitSwitch(Switch *sw, MacAddress mac, int nb_ports, Priority priority)
{
    memcpy(sw->mac, mac, 6);
    sw->Nb_P = nb_ports;
    memcpy(sw->P,priority,2);

    memcpy(sw->BID, sw->mac,6);
    sw->BID[6] = sw->P[0];
    sw->BID[7] = sw->P[1];
    memcpy(sw->SwitchRacineBID,sw->BID,8);
    
    sw->tabCommut = (Comut *)malloc(nb_ports * sizeof(Comut));

    for (int i = 0; i < nb_ports; i++)
    {
        sw->tabCommut[i].nbMac = 0;
        sw->tabCommut[i].Mac = (MacAddress *)malloc(sw->tabCommut->nbMac * sizeof(MacAddress));
        // for (int j = 0; j < sw->tabCommut[i].nbMac; j++)
        // {
        //     memset(sw->tabCommut[i].Mac[j], 0, sizeof(MacAddress));
        // }
    }
}

void ajouterMacToComut(MacAddress mac, Comut *tabComut, int index)
{
    tabComut[index].nbMac++;

    tabComut[index].Mac = realloc(tabComut[index].Mac, tabComut[index].nbMac * sizeof(MacAddress));

    memcpy(tabComut[index].Mac[tabComut[index].nbMac - 1], mac, sizeof(MacAddress));
}

void Visualiser_switch(Switch *sw)
{
    printf("Adresse mac: ");
    printOctets(sw->mac, 6);
    printf("\n");

    printf("Nombre de Port: %d\n\n", sw->Nb_P);

    printf("---- Table de commutation ----\n\n");
    for (int i = 0; i < sw->Nb_P; i++)
    {
        printf("Port: %d ", i + 1);

        printf("MacAdress");
        for (int j = 0; j < sw->tabCommut[i].nbMac; j++)
        {
            if(j < sw->tabCommut[i].nbMac){
                printf(" | ");
            }
            printOctets(sw->tabCommut[i].Mac[j], 6);
        }

        printf("\n");
    }
    printf("\n");
}

void isInCommut(MacAddress mac, Comut *tabComut, int tailleTabComut, int *r)
{
    for (int i = 0; i < tailleTabComut; i++)
    {
        for (int j = 0; j < tabComut[i].nbMac; j++)
        {
            if (memcmp(mac, tabComut[i].Mac[j], sizeof(MacAddress)) == 0)
            {
                *r = i;
                return;
            }
        }
    }
    *r = -1;
}
