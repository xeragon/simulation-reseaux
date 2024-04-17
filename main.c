#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reseau.h"
#include "switch.h"
#include "station.h"
#include "equipement.h"
#include "trame.h"

int main(int argc, char const *argv[])
{


    


    // MacAddress mac = {0x4E, 0xFF, 0x56, 0x90, 0x11, 0xAA};
    // // AdresseIp ip = {192, 168, 90, 1};
    // Priority p;
    // intToPriority(12, p);
    // Switch sw1;
    // InitSwitch(&sw1, mac, 4, p);
    // Visualiser_switch(&sw1);
    // Station S1;
    // InitStation(&S1, mac, ip);

    // Equipement SS1;
    // InitEquipemennt(&SS1, (EquipementUnion *)&sw1, SWITCH);
    // Visualiser_equipement(&SS1);
    // Trame t;
    // DataStruct dt;
    // InitData(&dt, (Data){0}, (Bourrage){0});
    // FCS fcs = {0}; // Empty fcs field
    // InitFullTrame(&t, mac, mac, (Type){0xFF, 0xFF}, dt, fcs);
    // InitTrame(&t, mac, mac, (Type){0xFF, 0xFF});
    // Visualiser_Full_Trame_Utilisateur(&t); // permet de visualiser une trame qui serait complete
    // Visualiser_Full_trame(&t);  // permet de visualiser une trame qui serait complete
    // Visualiser_Trame_Utilisateur(&t); // permet de visualiser une trame simplifier que nous utilisont pour les echange de trame
    // Visualiser_trame(&t); // permet de visualiser une trame simplifier que nous utilisont pour les echange de trame

    FILE *file = fopen("example.txt", "r");
    Reseau reseau;
    int nb_equipement;
    int nb_liaison;
    get_head_info(file, &nb_equipement, &nb_liaison);
    InitReseau(&reseau, nb_equipement, nb_liaison);
    create_architecture_from_file(file, &reseau);
    IdentifierVoisin(&reseau);

    Trame t;
    MacAddress macSource;
    MacAddress macDestinataire;
    memcpy(macSource,reseau.equipmentArray[5].eq.sw.mac,sizeof(MacAddress));
    memcpy(macDestinataire,reseau.equipmentArray[7].eq.sw.mac,sizeof(MacAddress));
    InitTramePing(&t,macDestinataire,macSource);



    

    // voyageTrame(t,5,5,&reseau);
    RunSpannigTreeProtocol(&reseau);

    // for(int i = 0; i < nb_equipement;i++){
    //     if(reseau.equipmentArray[i].type == SWITCH){
    //         Visualiser_equipement(&reseau.equipmentArray[i]);
    //     }
    // }

    // printf("=============================================\n");
    // memcpy(macSource,reseau.equipmentArray[7].eq.sw.mac,sizeof(MacAddress));
    // memcpy(macDestinataire,reseau.equipmentArray[5].eq.sw.mac,sizeof(MacAddress));
    // InitTramePing(&t,macDestinataire,macSource);
    // voyageTrame(t,7,7,&reseau);

    // Visualiser_Reseau(&reseau);

    return 0;
}