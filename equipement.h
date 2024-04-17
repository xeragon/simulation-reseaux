#pragma once
#include "switch.h"
#include "station.h"

typedef enum
{
    SWITCH,
    STATION
} EquipementType;

typedef enum
{
    RACINE,
    DESIGNE,
    BLOQUE
} EtatPort;

typedef union EquipementUnion
{
    Switch sw;
    Station st;
} EquipementUnion;

typedef struct
{
    int IndexEqVoisin;
    int poidVersEqVoisin;
    EtatPort etat;

} Port;

typedef struct Equipement
{
    EquipementType type;
    EquipementUnion eq;
    int nbVoisin;
    Port *port;
} Equipement;

void InitEquipemennt(Equipement *equipement, EquipementUnion *eqU, EquipementType type);
void Visualiser_equipement(Equipement *eq);
