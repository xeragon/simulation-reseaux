#include "trame.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void InitTramePing(Trame *trame, MacAddress dest, MacAddress src)
{

    for (int i = 0; i < 7; i++)
    {
        trame->preambule[i] = 0xAA;
    }
    trame->sfd = (SFD)0xAB;
    memcpy(trame->destination, dest, 6);
    memcpy(trame->source, src, 6);
    Type type = {0xAA,0xAA};
    memcpy(trame->type,type,2);
    

}
void InitFullTrame(Trame *trame, MacAddress dest, MacAddress src, Type type, DataStruct data, FCS fcs)
{
    for (int i = 0; i < 7; i++)
    {
        trame->preambule[i] = 0xAA;
    }
    trame->sfd = (SFD)0xAB;
    memcpy(trame->destination, dest, 6);
    memcpy(trame->source, src, 6);
    memcpy(trame->type, type, 2);
    memcpy(trame->data.bourrage, data.bourrage, 46);
    memcpy(trame->data.data, data.data, 1500);
    memcpy(trame->fcs, fcs, 4);
}
void InitTrameBPDU(Trame *t, MacAddress dest, MacAddress src, Switch switchSource,int cout)
{      
    memcpy(t->destination, dest, 6);
    memcpy(t->source, src, 6);
    Type ty = {0x00,0x00};
    memcpy(t->type,ty, 2);
    memcpy(t->data.data,switchSource.BID,sizeof(switchSource.BID));
    octet c; 
    intToOctet(cout,&c);
    t->data.data[8] = c;
    for (int i = 9; i < 17; i++)
    {
        t->data.data[i] = switchSource.SwitchRacineBID[i];
    }
    
}
void InitData(DataStruct *data, Data d, Bourrage b)
{

    memcpy(data->data, d, 1500);
    memcpy(data->bourrage,b,46);
}

void VisualiserTrameBDPU(Trame *t){
    Visualiser_Trame_Utilisateur(t);
    printf("BID : ");
    printOctets(t->data.data,8);
    printf("\nRacine BID : ");
    for (size_t i = 8; i <15; i++)
    {
        printf("%02X:",t->data.data[i]);
    }
    printf("%02X\n",t->data.data[15]);

    }
void Visualiser_Full_Trame_Utilisateur(Trame *t)
{
    printf("Preambule: ");
    printOctets(t->preambule, 7);
    printf("\n");

    printf("SFD : %02X\n", t->sfd);

    printf("Destination : ");
    printOctets(t->destination, 6);
    printf("\n");

    printf("Source : ");
    printOctets(t->source, 6);
    printf("\n");

    printf("Type : ");
    printOctets(t->type, 2);
    printf("\n");

    printf("Data :");
    // printOctets(t->data.data,1500);
    printf("\n");
    printf("Bourrage :");
    printOctets(t->data.bourrage, 46);
    printf("\n");

    printf("FCS :");
    printOctets(t->fcs, 4);
    printf("\n");
}
void Visualiser_Trame_Utilisateur(Trame *t)
{

    printf("Destination : ");
    printOctets(t->destination, 6);
    printf("\n");

    printf("Source : ");
    printOctets(t->source, 6);
    printf("\n");

    printf("Type : ");
    printOctets(t->type, 2);
    printf("\n");
}

void Visualiser_Full_trame(Trame *t)
{
    printOctets(t->preambule, 7);
    printf(":");
    printf("%02X", t->sfd);
    printf(":");
    printOctets(t->destination, 6);
    printf(":");
    printOctets(t->source, 6);
    printf(":");
    printOctets(t->type, 2);
    printf(":");
    printOctets(t->data.data, 1500);
    printf(":");
    printOctets(t->data.bourrage, 46);
    printf(":");
    printOctets(t->fcs, 4);
    printf("\n");
}
void Visualiser_trame(Trame *t)
{
    printOctets(t->preambule, 7);
    printf(":");
    printf("%02X", t->sfd);
    printf(":");
    printOctets(t->destination, 6);
    printf(":");
    printOctets(t->source, 6);
    printf(":");
    printOctets(t->type, 2);
    printf(":");
    printf("\n");
}
