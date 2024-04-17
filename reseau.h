#pragma once

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "liaison.h"
#include "equipement.h"
#include "types.h"
#include "trame.h"

typedef struct Reseau
{
    int nb_equipements;
    int nb_liaisons;
    Equipement *equipmentArray;
Liaison *LiaisonArray;
    
}Reseau;


void IdentifierVoisin(Reseau *r);
void get_head_info(FILE *file, int *nb_equipement, int *nb_liaison);
void create_architecture_from_file(FILE *file,Reseau *r);
int splitString(const char *input, const char *delimiter, char tokens[][25], int maxTokens);
void InitReseau(Reseau *r, int nb_eq, int nb_li);
void Visualiser_Reseau(Reseau *reseau);
void voyageTrame(Trame t, int indexEquipement, int equipementPrecedent, Reseau *r);
void ReceptionPing(Trame  t, int indexEquipement, int equipementPrecedent, Reseau *r);
void EnvoieReponsePing(Trame t, int indexEquipement, int equipementPrecedent, Reseau *r);
void RunSpannigTreeProtocol(Reseau *r);

