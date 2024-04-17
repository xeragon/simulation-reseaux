#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char MacAddress[6];
typedef unsigned int adresseIp[4];

typedef struct Station {
    MacAddress mac;
    adresseIp adrIp; // Array of 4 octets representing IP address
} Station;

typedef struct Comut {
    int *port;
    MacAddress *Mac;
} Comut;

typedef struct Switch {
    MacAddress mac;
    int Nb_P;
    int Priority;
    Comut *tabCommut;
} Switch;

typedef union Equipement {
    Switch sw;
    Station st;
} Equipement;

void InitStation(Station *station, MacAddress mac, adresseIp adrIp) {
    memcpy(station->mac, mac, 6);
    for(int i = 0; i < 4; i++){
        station->adrIp[i] = adrIp[i];
    }
}

void InitSwitch(Switch *switchInit, MacAddress mac, int nb_ports, int priority) {
    memcpy(switchInit->mac, mac, 6);
    switchInit->Nb_P = nb_ports;
    switchInit->Priority = priority;

    switchInit->tabCommut = (Comut *)malloc(nb_ports * sizeof(Comut));
    switchInit->tabCommut->port = (int *)malloc(nb_ports * sizeof(int));
    switchInit->tabCommut->Mac = (MacAddress *)malloc(nb_ports * sizeof(MacAddress));

    for (int i = 0; i < nb_ports; i++) {
        switchInit->tabCommut->port[i] = i + 1;
        memcpy(switchInit->tabCommut->Mac[i], "\x4E\xFF\x56\x90\x11\xAA", 6);
    }
}

void Visualiser_switch(const Switch *sw) {
    printf("Adresse mac: %02X:%02X:%02X:%02X:%02X:%02X\n",
           sw->mac[0], sw->mac[1], sw->mac[2], sw->mac[3], sw->mac[4], sw->mac[5]);
    printf("Nombre de Port: %d\n", sw->Nb_P);
    printf("Table de commutation:\n");
    for (int i = 0; i < sw->Nb_P; i++) {
        printf("Port: %d ", sw->tabCommut->port[i]);
        printf("MacAdress: %02X:%02X:%02X:%02X:%02X:%02X\n",
               sw->tabCommut->Mac[i][0], sw->tabCommut->Mac[i][1], sw->tabCommut->Mac[i][2],
               sw->tabCommut->Mac[i][3], sw->tabCommut->Mac[i][4], sw->tabCommut->Mac[i][5]);
    }
    printf("\n");
}

void Visualiser_station(const Station *st) {
    printf("Adresse mac: %02X:%02X:%02X:%02X:%02X:%02X\n",
           st->mac[0], st->mac[1], st->mac[2], st->mac[3], st->mac[4], st->mac[5]);
    printf("Adresse Ip: %d.%d.%d.%d\n",
           st->adrIp[0], st->adrIp[1], st->adrIp[2], st->adrIp[3]);
}

int main() {
    MacAddress mac = {0x4E, 0xFF, 0x56, 0x90, 0x11, 0xAA};
    adresseIp ip = {192, 168, 90,1};
    Station station;
    InitStation(&station, mac,ip);
    Visualiser_station(&station);

    MacAddress switchMac = {0x4E, 0xFF, 0x56, 0x90, 0x11, 0xBB};
    Switch switchInit;
    InitSwitch(&switchInit, switchMac, 4, 2);
    Visualiser_switch(&switchInit);

    return 0;
}
