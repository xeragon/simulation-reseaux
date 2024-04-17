#include "reseau.h"

void get_head_info(FILE *file, int *nb_equipement, int *nb_liaison)
{

    int MAX_LINE_LENGTH = 100;

    char line[MAX_LINE_LENGTH];
    char splitedLine[10][25];

    fgets(line, MAX_LINE_LENGTH, file);
    // printf("%s",line);
    splitString(line, " ", splitedLine, 10);
    *nb_equipement = atoi(splitedLine[0]);
    *nb_liaison = atoi(splitedLine[1]);
}

void InitReseau(Reseau *r, int nb_eq, int nb_li)
{
    r->nb_equipements = nb_eq;
    r->nb_liaisons = nb_li;
    r->equipmentArray = (Equipement *)malloc(nb_eq * sizeof(Equipement));
    r->LiaisonArray = (Liaison *)malloc(nb_li * sizeof(Liaison));
}
void Visualiser_Reseau(Reseau *reseau)
{
    printf("nb_eq : %d\n", reseau->nb_equipements);
    printf("nb_li : %d\n", reseau->nb_liaisons);
    for (int i = 0; i < reseau->nb_equipements; i++)
    {
        Visualiser_equipement(&reseau->equipmentArray[i]);
        printf("\n");
    }
    for (int i = 0; i < reseau->nb_liaisons; i++)
    {
        Visualiser_liaison(&reseau->LiaisonArray[i], reseau->equipmentArray);
        printf("\n");
    }
}
void create_architecture_from_file(FILE *file, Reseau *r)
{

    char line[100];

    char splitedLine[10][25];

    for (int i = 0; i < r->nb_equipements; i++)
    {
        fgets(line, 100, file);
        splitString(line, ";", splitedLine, 25);
        if (line[0] == '1')
        {
            // printf("its a station\n");
            Station st;
            MacAddress mac;
            AdresseIp ipAdr;
            StringToMac(splitedLine[1], mac);
            StringToIp(splitedLine[2], ipAdr);
            InitStation(&st, mac, ipAdr);
            InitEquipemennt(&r->equipmentArray[i], (EquipementUnion *)&st, STATION);
        }
        else if (line[0] == '2')
        {
            // printf("its a switch\n");
            Switch sw;
            MacAddress mac;
            Priority p;
            intToPriority(atoi(splitedLine[3]), p);
            StringToMac(splitedLine[1], mac);
            InitSwitch(&sw, mac, atoi(splitedLine[2]), p);
            InitEquipemennt(&r->equipmentArray[i], (EquipementUnion *)&sw, SWITCH);
        }
        else
        {
            printf("error\n");
        }
    }
    for (int i = 0; i < r->nb_liaisons; i++)
    {
        fgets(line, 100, file);
        splitString(line, ";", splitedLine, 25);
        // printf("its a liaison\n");
        InitLiaison(&r->LiaisonArray[i], atoi(splitedLine[0]), atoi(splitedLine[1]), atoi(splitedLine[2]));
    }

    fclose(file);
}

int splitString(const char *input, const char *delimiter, char tokens[][25], int maxTokens)
{
    int const MAX_TOKENS = 10;
    int const MAX_TOKEN_LENGTH = 25;
    char inputCopy[MAX_TOKENS * MAX_TOKEN_LENGTH];
    strcpy(inputCopy, input);

    char *token = strtok(inputCopy, delimiter);
    int tokenCount = 0;

    while (token != NULL && tokenCount < maxTokens)
    {
        strcpy(tokens[tokenCount], token);
        token = strtok(NULL, delimiter);
        tokenCount++;
    }

    return tokenCount;
}

void voyageTrame(Trame t, int indexEquipement, int equipementPrecedent, Reseau *r)
{

    MacAddress macDestinataire;
    memcpy(macDestinataire, t.destination, 6);
    MacAddress macSelf;
    memcpy(macSelf, r->equipmentArray[indexEquipement].eq.sw.mac, 6);
    Equipement *selfEq = &r->equipmentArray[indexEquipement];
    int portComut = 0;
    int portEnvoi = 0;

    if (selfEq->type == SWITCH)
    {
        isInCommut(t.source, selfEq->eq.sw.tabCommut, selfEq->eq.sw.Nb_P, &portComut);
        if (portComut == -1)
        {

            for (int i = 0; i < selfEq->nbVoisin; i++) // on parcours les voisins afin de trouver sur quel port on a recu la trame
            {
                if (equipementPrecedent == selfEq->port[i].IndexEqVoisin)
                {
                    // printf(" \tc le voisin sur le port %d qui m'a envoyer la trame\n", i);
                    ajouterMacToComut(t.source, selfEq->eq.sw.tabCommut, i);
                }
            }
        }
    }

    if (memcmp(macDestinataire, macSelf, sizeof(MacAddress)) == 0)
    {
        if (t.type[0] == 0x00 && t.type[1] == 0x00)
        {
            printf("j'ai recu une trame de type BDPU");
        }
        else
        {
            ReceptionPing(t, indexEquipement, equipementPrecedent, r);
        }
    }
    else if (selfEq->type == SWITCH)
    {

        isInCommut(macDestinataire, selfEq->eq.sw.tabCommut, selfEq->eq.sw.Nb_P, &portEnvoi); // si de destinataire de la trame est dans notre table de commutation alors on lui envoie la trame
        if (portEnvoi != -1)
        {
            printf("Je suis l'equipement(switch) num : %d \n\t  Le destinataire est dans ma table de commutation\n\t\t j'envoie la trame sur le port %d\n",
                   indexEquipement, portEnvoi + 1);
            printf("\n");
            voyageTrame(t, selfEq->port[portEnvoi].IndexEqVoisin, indexEquipement, r);
        }
        else // sinon on envoie la trame a tout les port sauf celui sur lequel ont vient de recevoir la trame
        {
            for (int i = 0; i < selfEq->nbVoisin; i++)
            {
                if (selfEq->port[i].IndexEqVoisin != equipementPrecedent && selfEq->port->etat != BLOQUE)
                {
                    printf("Je suis l'equipement(switch) num : %d \n\t je ne sais pas ou est le destinataire\n\t\t j'envoie la trame a l'equipement %d\n",
                           indexEquipement, r->equipmentArray[indexEquipement].port[i].IndexEqVoisin);
                    printf("\n");
                    voyageTrame(t, selfEq->port[i].IndexEqVoisin, indexEquipement, r);
                }
            }
        }
    }
    else if (selfEq->type == STATION)
    {
        // selfEq->voisinsIndexDansReseau[0] != indexEquipementPrecedent
        if (selfEq->port[0].IndexEqVoisin != equipementPrecedent)
        {
            printf("Je suis l'equipement(station) num : %d \n\t je ne suis pas le destinataire\n\t\t j'envoie la trame à mon voisin \n",
                   indexEquipement);
            printf("\n");

            voyageTrame(t, selfEq->port[0].IndexEqVoisin, equipementPrecedent, r);
        }
    }
}
void ReceptionPing(Trame t, int indexEquipement, int equipementPrecedent, Reseau *r)
{
    MacAddress macDestinataire;
    memcpy(macDestinataire, t.destination, 6);
    MacAddress macSelf;
    memcpy(macSelf, r->equipmentArray[indexEquipement].eq.sw.mac, 6);

    if (t.type[0] == 0xAA && t.type[1] == 0xAA)
    {
        printf("Je suis l'equipement num : %d d'adresse mac : ", indexEquipement);
        printOctets(macSelf, 6);
        printf("\n\t J'ai bien recu la trame \n");
        printf("\t j'envoie la réponse a la machine d'adresse mac :");
        printOctets(t.source, 6);
        printf("\n\n");
        EnvoieReponsePing(t, equipementPrecedent, equipementPrecedent, r);
    }
    else
    {
        printf("Je suis l'equipement num : %d \n\t J'ai bien recu la trame reponse envoyée par la machine d'adresse mac : ", indexEquipement);
        printOctets(t.source, 6);
        printf("\n\n");
    }
}

void EnvoieReponsePing(Trame t, int indexEquipement, int equipementPrecedent, Reseau *r)
{
    Trame tReponse;
    InitTramePing(&tReponse, t.source, t.destination);
    tReponse.type[0] = 0xBB;
    tReponse.type[1] = 0xBB;

    voyageTrame(tReponse, indexEquipement, equipementPrecedent, r);
}
void IdentifierVoisin(Reseau *r)
{
    for (int i = 0; i < r->nb_equipements; i++)
    {
        for (int j = 0; j < r->nb_liaisons; j++)
        {

            if (r->LiaisonArray[j].eq1 == i)
            {
                r->equipmentArray[i].port[r->equipmentArray[i].nbVoisin].IndexEqVoisin = r->LiaisonArray[j].eq2;
                r->equipmentArray[i].port[r->equipmentArray[i].nbVoisin].poidVersEqVoisin = r->LiaisonArray[j].poids;
                r->equipmentArray[i].port[r->equipmentArray[i].nbVoisin].etat = DESIGNE;
                r->equipmentArray[i].nbVoisin += 1;
            }
            else if (r->LiaisonArray[j].eq2 == i)
            {
                r->equipmentArray[i].port[r->equipmentArray[i].nbVoisin].IndexEqVoisin = r->LiaisonArray[j].eq1;
                r->equipmentArray[i].port[r->equipmentArray[i].nbVoisin].poidVersEqVoisin = r->LiaisonArray[j].poids;
                r->equipmentArray[i].port[r->equipmentArray[i].nbVoisin].etat = DESIGNE;
                r->equipmentArray[i].nbVoisin += 1;
            }
        }
    }
}

void RunSpannigTreeProtocol(Reseau *r)
{
    Trame BDPU;

    for (int i = 0; i < r->nb_equipements; i++)
    {
        if (r->equipmentArray[i].type == SWITCH)
        {
            for (int j = 0; j < r->equipmentArray[i].nbVoisin; j++)
            {
                MacAddress dest;
                memcpy(&dest, r->equipmentArray[r->equipmentArray[i].port[j].IndexEqVoisin].eq.sw.mac, 6);
                MacAddress src;
                memcpy(&src, r->equipmentArray[i].eq.sw.mac, 6);

                InitTrameBPDU(&BDPU,dest,src,r->equipmentArray[i].eq.sw,r->equipmentArray[i].port[j].poidVersEqVoisin);
                voyageTrame(t,r->equipmentArray[i].port[j].IndexEqVoisin,i,r);
                // VisualiserTrameBDPU(&BDPU);
                printf("\n");
            }
        }
    }
}