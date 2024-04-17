#include "types.h"
#include "reseau.h"
#include <string.h>
#include <stdio.h>
void StringToMac(char *string, MacAddress mac)
{
    char splitedString[10][25];
    splitString(string, ":", splitedString, 6);

    for (int i = 0; i < 6; i++)
    {
        mac[i] = (unsigned char)strtol(splitedString[i], NULL, 16);
    }
}

void StringToIp(char *string, AdresseIp ipAdr)
{
    int a, b, c, d;
    sscanf(string, "%d.%d.%d.%d", &a, &b, &c, &d);
    ipAdr[0] = (octet)a;
    ipAdr[1] = (octet)b;
    ipAdr[2] = (octet)c;
    ipAdr[3] = (octet)d;
    return;
    char splitedString[10][25];
    printf("StringToIp:\n");
    printf("\t%s\n", string);
    splitString(string, ":", splitedString, 4);
    for (int i = 0; i < 4; i++)
    {
        printf("\t\t%s\n", splitedString[i]);
        (ipAdr)[i] = (octet)atoi(splitedString[i]);
    }
}

void printBinaire(unsigned char x)
{
    unsigned char byte = x;
    for (int j = 7; j >= 0; j--)
    {
        printf("%d", (byte >> j) & 1);
    }
    printf(" ");
}

void printOctets(octet octets[], int nbOctet)
{
    for (size_t i = 0; i < nbOctet - 1; i++)
    {
        printf("%02X:",octets[i]);
    }
    printf("%02X",octets[nbOctet-1]);

    
}

void intToPriority(int value, Priority priority)
{
    priority[0] = (value >> 8) & 0xFF;
    priority[1] = value & 0xFF;
}

void intToOctet(int value, octet *octet){
    *octet = value & 0xFF;
}