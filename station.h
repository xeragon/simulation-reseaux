#pragma once
#include "types.h"

typedef struct Station
{
    MacAddress mac;
    AdresseIp adrIp;
    
}Station;

void InitStation(Station *station, MacAddress mac, AdresseIp AdresseIp);
void Visualiser_station(Station *st);