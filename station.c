#include "station.h"
#include <stdio.h>
#include <string.h>
void InitStation(Station *station, MacAddress mac, AdresseIp adrIp)
{
    memcpy(station->mac, mac, 6);
    for (int i = 0; i < 4; i++)
    {
        station->adrIp[i] = adrIp[i];
    }
}

void Visualiser_station(Station *st)
{
    printf("Adresse mac : ");
    printOctets(st->mac,6);
    printf("\n");
    
    printf("Adresse Ip : %d.%d.%d.%d\n",
           st->adrIp[0], st->adrIp[1], st->adrIp[2], st->adrIp[3]);
}
 