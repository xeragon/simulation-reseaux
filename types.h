#pragma once

#include <stdint.h>

typedef uint8_t octet;

typedef octet MacAddress[6];
typedef octet AdresseIp[4];
typedef int Nb_ports;
typedef octet Priority[2];
typedef octet Bid[8];

//trame ethernet
typedef octet Preambule[7];
typedef octet SFD;
typedef MacAddress Destination;
typedef MacAddress Source;
typedef unsigned char Type[2];
typedef unsigned char FCS[4];
typedef unsigned char Bourrage[46];
typedef unsigned char Data[1500];


void StringToMac(char *string, MacAddress mac);
void StringToIp(char *string, AdresseIp ipAdr);
void printBinaire(unsigned char x);
void printOctets(octet octets[], int nbOctet);
void intToPriority(int value, Priority priority);
void intToOctet(int value, octet *octet);