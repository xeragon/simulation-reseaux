#pragma once
#include "types.h"
#include "switch.h"
typedef struct DataStruct 
{
    Data data;
    Bourrage bourrage;
} DataStruct;

typedef struct Trame
{
    Preambule preambule;
    SFD sfd; 
    MacAddress destination;
    MacAddress source;
    Type type;
    DataStruct data;
    FCS fcs;
} Trame;

void InitFullTrame(Trame *trame, MacAddress dest, MacAddress src, Type type, DataStruct data, FCS fcs);
void InitTramePing(Trame *trame, MacAddress dest, MacAddress src);
void InitTrameBPDU(Trame *t, MacAddress dest, MacAddress src, Switch switchSource,int cout);
void InitData(DataStruct *data, Data d, Bourrage b);
void Visualiser_Full_Trame_Utilisateur(Trame *t);
void Visualiser_Full_trame(Trame *t);
void Visualiser_Trame_Utilisateur(Trame *t);
void Visualiser_trame(Trame *t);
void VisualiserTrameBDPU(Trame *t);