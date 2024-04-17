#pragma once
#include "types.h"


typedef struct Comut
{   int nbMac;
    MacAddress *Mac;
}Comut;

typedef struct Switch
{
    MacAddress mac;
    Priority P;
    Bid BID;
    Bid SwitchRacineBID;
    int SendBid;
    Nb_ports Nb_P;
    Comut *tabCommut;
}Switch;



void InitSwitch(Switch *switchInit, MacAddress mac, int nb_ports, Priority priority);
void Visualiser_switch(Switch *sw);
void ajouterMacToComut(MacAddress mac, Comut *tabComut, int index);
void isInCommut(MacAddress mac, Comut *tabComut, int tailleTabComut, int *r);

