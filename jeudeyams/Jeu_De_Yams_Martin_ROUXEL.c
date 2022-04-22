
/**
 * @file Jeu_De_Yams.c
 * @author Martin ROUXEL <martin.rouxel2310@gmail.com>
 * @brief  Jeu de Yams à deux joueurs
 * @version 1.0
 * @date 2021-11-27
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

/**
 * @brief type correspondant à un nom de joueur de 8 caractères maximum
 * 
 */
typedef char nom[9];
/**
 * @brief constante définie pour être utilisée en indice de création des tableaux de score
 * 
 */
#define LIGNES 17
/**
 * @brief constante définie pour être utilisée en indice de création des tableaux de score
 * 
 */
#define COLONNES 2
/**
 * @brief constante définie pour être utilisée en ondice de création des tableaux de Dés
 * 
 */
#define NOMBREDES 5

/**
 * @brief met à zéro un tableau de [17][2] cases
 * 
 * @param[out] tab un tableau à mettre à zéro
 * 
 * @return void
 */
void MiseAZero(int tab[LIGNES][COLONNES]);
/**
 * @brief procédure calculant les scores totaux et de bonus des deux joueurs puis affiche la fiche de marque.
 * 
 * @param[in] nom1 nom du joueur 1
 * @param[in] nom2 nom du joueur 2
 * @param[in] tab tableau de [17][2] cases représentant le score
 * 
 * @return void
 */
void afficherFeuille(nom nom1, nom nom2, int tab[LIGNES][COLONNES]);
/**
 * @brief met à 1 tous les éléments d'un tableau DES de taille [5]
 * 
 * @param[out] DES tableau de [5] éléments à modifier
 * 
 * @return void 
 */
void MiseAUn(int DES[NOMBREDES]);
/**
 * @brief procédure qui demande au joueur quels dés choisir en faisant varier un tableau de [5] éléments entre 0 et 1 (l'utilisateur entre le numéro du dé à garder/lacher)
 * 
 * @param[out] nbDES tableau de [5] éléments entiers (soit 0 soit 1)
 * 
 * @return void
 */
void choixDES(int nbDES[5]);
/**
 * @brief procédure qui attribue une valeur aléatoire aux éléments d'un tableau[5] "Des" en fonction d'un tableau[5] "nbDes" rempli de 0 ou 1.
 * 
 * @param[in] nbDes tableau[5] rempli de 0 ou 1 déterminant quels dés doivent être lançés.
 * @param[out] Des tableau[5] rempli de valeurs aléatoires entre 1 et 6 par la procédure en fonction du tableau "nbDes".
 * @note seul un entier peut être entré par le joueur, sinon le programme ne fonctionne pas.
 * 
 * @return void
 */
void lancerDES(int nbDes[NOMBREDES], int Des[NOMBREDES]);
/**
 * @brief procédure qui convertit un tableau de dés (valeurs entre 1 et 6) en tableau de caractères spécifique pour l'affichage
 * 
 * @param[in] DES tableau[5] de dés converti par la procédure 
 * @param[out] de tableau[5][7] de caractères (" " ou "*") pour la fonction afficherDES(de)
 * 
 * @return void
 */
void conversion(int DES[5], char de[5][7]);
/**
 * @brief procédure qui affiche les dés de manière pseudo-graphique (des jolis dés en ascii) grâce à une série de printf()
 * 
 * @param[in] de tableau de caractères définissant l'affichage des dés
 * 
 * @return void
 */
void afficherDES(char de[5][7]);
/**
 * @brief fonction demandant au joueur si il veut relancer des dés et retourne 1 si oui 0 si non ou 42 en cas d'erreur
 * 
 * @return Entier (0, 1, 42) 
 */
int demandeValid();
/**
 * @brief procédure qui affiche au joueur les choix qui lui sont encore disponibles
 * 
 * @param[in] tab tableau[17][2] rempli de 0(choix disponible) ou de 1(choix indisponible) qui permet l'affichage des choix disponibles
 * @param[in] joueur numéro du joueur correspondant aux colonnes du tableau "tab"
 * @note attention, le joueur doit obligatoirement rentrer un entier au clavier.
 * 
 * @return void
 */
void affichagechoix(int tab[LIGNES][COLONNES], int joueur);
/**
 * @brief procédure qui trie un tableau par ordre croissant
 * 
 * @param[out] Des tableau à trier
 * @param[in] nbDes taille du tableau à trier
 * 
 * @return void
 */
void ordonnerDes(int Des[], int nbDes);
/**
 * @brief fonction qui permet de compter le nombre de fois qu'un entier apparait dans un tableau de dés
 * 
 * @param[in] DES tableau[5] de dés
 * @param[in] nombre entier à compter dans le tableau de dés
 * 
 * @return Entier représentant le nombre d'itération de "nombre" dans "DES"
 */
int comptageNb(int DES[NOMBREDES], int nombre);
/**
 * @brief fonction qui demande au joueur de choisir une option et qui attribue le score de l'option choisie au tableau de score
 * 
 * @param[in] Des tableau de dés pris en compte pour attribuer un score
 * @param[out] tab tableau[17][2] des scores des deux joueurs pour chaque case de la feuille de marque
 * @param[out] tabtour tableau[17][2] de forme identique à "tab" qui contient des 1 aux options déjà utilisées pour que le joueur ne puisse pas rejouer deux fois la même chose
 * @param[in] joueur numéro du joueur correspondant aux colonnes des deux tableaux "tab" et "tabtour"
 * 
 * @return void
 */
void choixOption(int Des[NOMBREDES], int tab[LIGNES][COLONNES], int tabtour[LIGNES][COLONNES], int joueur);
/**
 * @brief fonction qui compare les scores totaux des deux joueurs et affiche le nom du vainqueur
 * 
 * @param[in] tab tableau[17][2] de scores
 * @param[in] noms tableau[2] de noms des joueurs
 * @note attention, le joueur doit obligatoirement rentrer un entier au clavier
 * 
 * @return void
 */
void annoncerVainqueur(int tab[LIGNES][COLONNES], nom noms[2]);

int main() //début du programme principal
{
    srand(time(NULL));
    /**
     * @brief tableaux comportant respectivement les scores et des valeurs binaires permettant à l'utilisateur de choisir des options
     * 
     */
    int tableau[LIGNES][COLONNES], tableautour[LIGNES][COLONNES];
    /**
     * @brief tableau de deux noms rempli par les joueurs au début de la partie
     * 
     */
    nom noms[2];
    /**
     * @brief compteurs et booléens utiles au déroulement du main() (tour = nb de tours, nbEssais = nb de relances disponibles à chaque tour, joueur = numéro du joueur, valid = booléen de validation fourni par le joueur)
     * 
     */
    int nbEssais, tour, joueur, valid;
    /**
     * @brief tableaux contenant respectivepent les Dés et les Dés à conserver/relancer pour chaque tour
     * 
     */
    int DES[NOMBREDES], nbDES[NOMBREDES];
    /**
     * @brief tableau de caractères utile à l'affichage des dés en ascii
     * 
     */
    char de[5][7];

    printf("entrer le nom du joueur 1 (8 caractères max) :\n"); // demande aux joueurs leurs noms et les entre dans le tableau noms[2]
    scanf("%s", noms[0]);
    while (strlen(noms[0]) > 8)
    {
        printf("nombre de caractère trop élevé\n");
        scanf("%s", noms[0]);
    }
    printf("entrer le nom du joueur 2 (8 caractères max) :\n");
    scanf("%s", noms[1]);
    while (strlen(noms[1]) > 8)
    {
        printf("nombre de caractère trop élevé\n");
        scanf("%s", noms[1]);
    }
    MiseAZero(tableau);               //met le tableau de score à zéro
    MiseAZero(tableautour);           //met le "tableau des choix" à 0, ce tableau indique quelles cases le joueur peut encore remplir.
    for (tour = 0; tour < 13; tour++) //la partie dure 13 tours, le temps de remplir chaque case de la feuille de marque
    {

        for (joueur = 0; joueur < 2; joueur++) //le corps du programme s'execute une fois pour chaque joueur, par tour
        {
            afficherFeuille(noms[0], noms[1], tableau); //affiche la feuille de marque pour que le joueur se repère facilement au niveau des scores
            MiseAUn(nbDES);
            nbEssais = 2;          //configure le nombre de relance de dés disponibles à 2
            lancerDES(nbDES, DES); //remplis le tableau de dés avec des valeurs pseudo-aléatoires de 1 à 6
            conversion(DES, de);
            printf("Au tour de %s :", noms[joueur]); //indique quel joueur doit interagir avec le terminal pour le prochain tour
            afficherDES(de);                         //affiche les dés en caractères ascii

            do //demande au joueur un nombre limité de fois si il souhaite changer certains dés
            {

                valid = demandeValid();

                if (valid == 1) //si le joueur valide, il relance les dés de son choix, sinon il doit directement choisir une option
                {

                    choixDES(nbDES);
                    lancerDES(nbDES, DES);
                    conversion(DES, de);
                    afficherDES(de);
                    nbEssais--; //le nombre de relance est diminué après cette étape
                }
            } while (nbEssais != 0 && valid == 1);

            ordonnerDes(DES, NOMBREDES);                    //trie les dés pour le bon fonctionnement de l'attribution des scores
            choixOption(DES, tableau, tableautour, joueur); //demande au joueur courant de choisir une option non remplie et lui attribue un score
        }
    }

    afficherFeuille(noms[0], noms[1], tableau); //affiche la feuille de marque une dernière fois
    annoncerVainqueur(tableau, noms);           //compare les deux scores et annonce un vainqueur
    return 0;
}

void MiseAZero(int tab[LIGNES][COLONNES]) //remplace tous les éléments d'un tableau par 0
{
    int i, k; //compteurs
    for (i = 0; i < COLONNES; i++)
    {
        for (k = 0; k < LIGNES; k++)
        {
            tab[k][i] = 0; //remplacement par 0
        }
    }
}

void afficherFeuille(nom nom1, nom nom2, int tab[LIGNES][COLONNES]) //affiche la feuille de marque après avoir calculé les scores totaux
{
    if ((tab[0][0] + tab[1][0] + tab[2][0] + tab[3][0] + tab[4][0] + tab[5][0]) >= 63)
    {
        tab[6][0] = 35; //bonus joueur 1
    }
    if ((tab[0][1] + tab[1][1] + tab[2][1] + tab[3][1] + tab[4][1] + tab[5][1]) >= 63)
    {
        tab[6][1] = 35; //bonus joueur 2
    }
    tab[7][0] = tab[0][0] + tab[1][0] + tab[2][0] + tab[3][0] + tab[4][0] + tab[5][0] + tab[6][0];       //total sup J1
    tab[7][1] = tab[0][1] + tab[1][1] + tab[2][1] + tab[3][1] + tab[4][1] + tab[5][1] + tab[6][1];       //total sup J2
    tab[15][0] = tab[8][0] + tab[9][0] + tab[10][0] + tab[11][0] + tab[12][0] + tab[13][0] + tab[14][0]; //total inf J1
    tab[15][1] = tab[8][1] + tab[9][1] + tab[10][1] + tab[11][1] + tab[12][1] + tab[13][1] + tab[14][1]; //total inf J2
    tab[16][0] = tab[7][0] + tab[15][0];                                                                 //total score J1
    tab[16][1] = tab[7][1] + tab[15][1];                                                                 //total score J2
    printf("\n");
    printf("J1:%8s J2:%8s      J1        J2\n", nom1, nom2);
    printf("---------------------------------------------\n");
    printf("Partie Supérieure\n");
    printf("1 [total de 1]          |   %3d   |   %3d   |\n", tab[0][0], tab[0][1]);
    printf("2 [total de 2]          |   %3d   |   %3d   |\n", tab[1][0], tab[1][1]);
    printf("3 [total de 3]          |   %3d   |   %3d   |\n", tab[2][0], tab[2][1]);
    printf("4 [total de 4]          |   %3d   |   %3d   |\n", tab[3][0], tab[3][1]);
    printf("5 [total de 5]          |   %3d   |   %3d   |\n", tab[4][0], tab[4][1]);
    printf("6 [total de 6]          |   %3d   |   %3d   |\n", tab[5][0], tab[5][1]);
    printf("Bonus                   |   %3d   |   %3d   |\n", tab[6][0], tab[6][1]);
    printf("Total Supérieur         |   %3d   |   %3d   |\n", tab[7][0], tab[7][1]);
    printf("---------------------------------------------\n");
    printf("Partie Inférieure\n");
    printf("Brelan                  |   %3d   |   %3d   |\n", tab[8][0], tab[8][1]);
    printf("Carré                   |   %3d   |   %3d   |\n", tab[9][0], tab[9][1]);
    printf("Full                    |   %3d   |   %3d   |\n", tab[10][0], tab[10][1]);
    printf("Petite Suite            |   %3d   |   %3d   |\n", tab[11][0], tab[11][1]);
    printf("Grande Suite            |   %3d   |   %3d   |\n", tab[12][0], tab[12][1]);
    printf("Yams                    |   %3d   |   %3d   |\n", tab[13][0], tab[13][1]);
    printf("Chance [total des DES]  |   %3d   |   %3d   |\n", tab[14][0], tab[14][1]);
    printf("Total Inférieur         |   %3d   |   %3d   |\n", tab[15][0], tab[15][1]);
    printf("---------------------------------------------\n");
    printf("Total                   |   %3d   |   %3d   |\n\n\n", tab[16][0], tab[16][1]);
}

void MiseAUn(int DES[NOMBREDES]) //remplace les éléments d'un tableau par 1
{
    int i; //compteur
    for (i = 0; i < 5; i++)
    {
        DES[i] = 1; //mise à 1
    }
}

void choixDES(int nbDES[5]) //permet au joueur de sélectionner les dés qu'il veut garder/changer
{
    int rep;        //réponse du joueur
    MiseAUn(nbDES); //par défaut tous les dés sont changés
    do
    {
        printf("\nsélectionnez un dé à conserver ou lacher, 0 pour arrêter\n");
        do
        {
            scanf("%d", &rep);
            if (rep < 0 || rep > 5)
            {
                printf("valeur incorrecte, réentrez un nombre\n\n");
            }
        } while (rep < 0 || rep > 5);
        if (nbDES[rep - 1] == 0) //dé laché si dé déjà gardé
        {
            nbDES[rep - 1] = 1;
            printf("dé %d laché\n", rep);
        }
        else if (nbDES[rep - 1] == 1) //dé gardé si dé déjà laché
        {
            nbDES[rep - 1] = 0;
            printf("dé %d conservé\n", rep);
        }
    } while (rep != 0);
}

void lancerDES(int nbDes[NOMBREDES], int Des[NOMBREDES]) //lance les dés (tableau de 5 entiers)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (nbDes[i] == 1) //pour chaque dé, si le booléen du tableau nbDes correspondant est 1, il est changé
        {
            Des[i] = (rand() % (6 - 1 + 1)) + 1; //entier pseudo-aléatoire entre 1 et 6
        }
    }
}

void conversion(int DES[NOMBREDES], char de[NOMBREDES][7]) //permet de rendre le tableau de dés apte à l'affichage
{
    int i;
    for (i = 0; i < 5; i++) //pour chaque dé
    {
        switch (DES[i])
        {
        case 1: //le dé est un 1
            de[i][0] = ' ';
            de[i][1] = ' ';
            de[i][2] = ' '; // -------  (affichage exemple pour le dé 1)
            de[i][3] = '*'; //|       |
            de[i][4] = ' '; //|   *   |
            de[i][5] = ' '; //|       |
            de[i][6] = ' '; // -------
            break;
        case 2: //le dé est un 2
            de[i][0] = '*';
            de[i][1] = ' ';
            de[i][2] = ' ';
            de[i][3] = ' ';
            de[i][4] = ' ';
            de[i][5] = ' ';
            de[i][6] = '*';
            break;
        case 3: //le dé est un 3
            de[i][0] = '*';
            de[i][1] = ' ';
            de[i][2] = ' ';
            de[i][3] = '*';
            de[i][4] = ' ';
            de[i][5] = ' ';
            de[i][6] = '*';
            break;
        case 4: //le dé est un 4
            de[i][0] = '*';
            de[i][1] = '*';
            de[i][2] = ' ';
            de[i][3] = ' ';
            de[i][4] = ' ';
            de[i][5] = '*';
            de[i][6] = '*';
            break;
        case 5: //le dé est un 5
            de[i][0] = '*';
            de[i][1] = '*';
            de[i][2] = ' ';
            de[i][3] = '*';
            de[i][4] = ' ';
            de[i][5] = '*';
            de[i][6] = '*';
            break;
        case 6: //le dé est un 6
            de[i][0] = '*';
            de[i][1] = '*';
            de[i][2] = '*';
            de[i][3] = ' ';
            de[i][4] = '*';
            de[i][5] = '*';
            de[i][6] = '*';
            break;
        }
    }
}

void afficherDES(char de[5][7]) //affiche les dés horizontalement avec l'aide de la fonction précédente
{
    printf("\n -------  -------  -------  -------  ------- \n");
    printf("| %c   %c || %c   %c || %c   %c || %c   %c || %c   %c |\n", de[0][0], de[0][1], de[1][0], de[1][1], de[2][0], de[2][1], de[3][0], de[3][1], de[4][0], de[4][1]);
    printf("| %c %c %c || %c %c %c || %c %c %c || %c %c %c || %c %c %c |\n", de[0][2], de[0][3], de[0][4], de[1][2], de[1][3], de[1][4], de[2][2], de[2][3], de[2][4], de[3][2], de[3][3], de[3][4], de[4][2], de[4][3], de[4][4]);
    printf("| %c   %c || %c   %c || %c   %c || %c   %c || %c   %c |\n", de[0][5], de[0][6], de[1][5], de[1][6], de[2][5], de[2][6], de[3][5], de[3][6], de[4][5], de[4][6]);
    printf(" -------  -------  -------  -------  ------- \n");
}

int demandeValid() //demande au joueur si il veut relancer ou non des dés
{
    int rep = 2;
    while (rep < 0 || rep > 1)
    {
        printf("souhaitez vous relancer 0 (oui)/1 (non)\n");
        scanf("%d", &rep);
    }
    if (rep == 0) //si le joueur répond 0 la procédure retourne 1
    {
        return 1;
    }
    else //sinon elle retourne 0
    {
        return 0;
    }
    return 42; //en cas d'erreur la fonction retourne 42
}

void affichagechoix(int tab[LIGNES][COLONNES], int joueur) //cette fonction affiche les choix que le joueur peut encore faire (les choix ne s'affichent qu'une fois et disparaissent après avoir été utilisés)
{
    printf("\nchoisissez une des options disponibles :\n");
    if (tab[0][joueur] == 0)
    {
        printf("total de 1 = 1\n");
    }
    if (tab[1][joueur] == 0)
    {
        printf("total de 2 = 2\n");
    }
    if (tab[2][joueur] == 0)
    {
        printf("total de 3 = 3\n");
    }
    if (tab[3][joueur] == 0)
    {
        printf("total de 4 = 4\n");
    }
    if (tab[4][joueur] == 0)
    {
        printf("total de 5 = 5\n");
    }
    if (tab[5][joueur] == 0)
    {
        printf("total de 6 = 6\n");
    }
    if (tab[8][joueur] == 0)
    {
        printf("brelan = 7\n");
    }
    if (tab[9][joueur] == 0)
    {
        printf("carré = 8\n");
    }
    if (tab[10][joueur] == 0)
    {
        printf("fullhouse = 9\n");
    }
    if (tab[11][joueur] == 0)
    {
        printf("petite suite = 10\n");
    }
    if (tab[12][joueur] == 0)
    {
        printf("grande suite = 11\n");
    }
    if (tab[13][joueur] == 0)
    {
        printf("Yams = 12\n");
    }
    if (tab[14][joueur] == 0)
    {
        printf("Chance = 13\n");
    }
}

void ordonnerDes(int Des[], int nbDes) //tri du tableau de dés pour le choixOption()
{
    int tampon = 0, v = 0, i;

    do
    {
        for (i = 0; i < nbDes; i++)
        {
            if (Des[i] > Des[i + 1])
            {
                tampon = Des[i];
                Des[i] = Des[i + 1];
                Des[i + 1] = tampon;
            }
        }
        v++;
    } while (v < nbDes);
}

int comptageNb(int DES[NOMBREDES], int nombre) //fonction qui compte le nombre d'apparition d'un entier dans les dés
{
    int i, resultat = 0;
    for (i = 0; i < NOMBREDES; i++)
    {
        if (DES[i] == nombre)
        {
            resultat++;
        }
    }
    return resultat;
}

void choixOption(int Des[NOMBREDES], int tab[LIGNES][COLONNES], int tabtour[LIGNES][COLONNES], int joueur) //fonction au coeur du programme qui permet au joueur de choisir une option parmi celles qui sont disponibles et de gagner des points
{
    int reponse, nb, i; // (reponse = réponse entrée par le joueur, nb = entier affecté de la fonction comptageNb(), i = compteur)
    affichagechoix(tabtour, joueur);
    scanf("%d", &reponse);
    if (reponse < 7) // pour garder des numéros d'options cohérent je divise la table en deux parties (erreurs sinon à cause des cases "total" ou "bonus")
    {
        while (tabtour[reponse - 1][joueur] == 1 || reponse < 1 || reponse > 13)
        {
            printf("\nun score est déjà attribué à cette entrée ou la case sélectionnée n'existe pas, entrez à nouveau une réponse :\n");
            scanf("%d", &reponse);
        }
    }
    else if (reponse > 6) //deuxième partie de la table
    {
        while (tabtour[reponse + 1][joueur] == 1 || reponse < 1 || reponse > 13)
        {
            printf("\nun score est déjà attribué à cette entrée ou la case sélectionnée n'existe pas, entrez à nouveau une réponse :\n");
            scanf("%d", &reponse);
        }
    }
    for (i = 1; i < 7; i++) //pour les réponses 1 à 6 l'affectation du score est la même
    {
        if (reponse == i)
        {
            nb = comptageNb(Des, i);
            tab[i - 1][joueur] = i * nb;
            tabtour[i - 1][joueur] = 1;
        }
    }
    switch (reponse) //switch pour tous les autres cas de réponse possible
    {
    case 7: //brelan (donne les points si trois fois le même dé)
        for (i = 0; i < 6; i++)
        {
            if (comptageNb(Des, i + 1) >= 3)
            {
                tab[8][joueur] = (i + 1) * 3;
                break;
            }
        }
        tabtour[8][joueur] = 1; //pour chaque choix effectué, la case correspondante du tableau tabtour est mise à 1 ce qui empêche l'option d'être affichée ET sélectionnée au futur
        break;

    case 8: //carré (donne les points si quatre fois le même dé)
        for (i = 0; i < 6; i++)
        {
            if (comptageNb(Des, i + 1) >= 4)
            {
                tab[9][joueur] = (i + 1) * 4;
            }
        }
        tabtour[9][joueur] = 1;
        break;

    case 9: //fullhouse (donne les points si 3 dés + 2 dés identiques)

        if ((Des[0] == Des[1] && Des[2] == Des[4]) || (Des[0] == Des[2] && Des[3] == Des[4]))
        {
            tab[10][joueur] = 25;
        }

        tabtour[10][joueur] = 1;
        break;

    case 10: //petite suite (donne les points si les dés présentent une suite croissante de 3 nombres ex : 1,2,3)
        if ((Des[0] + 1 == Des[1] && Des[1] + 1 == Des[2] && Des[2] + 1 == Des[3]) || (Des[1] + 1 == Des[2] && Des[2] + 1 == Des[3] && Des[3] + 1 == Des[4]))
        {
            tab[11][joueur] = 30;
        }

        tabtour[11][joueur] = 1;
        break;

    case 11: //grande suite (donne les points si les dés forment une suite de 5 nombres ex : 1,2,3,4,5)
        if (Des[0] + 1 == Des[1])
        {
            if (Des[1] + 1 == Des[2])
            {
                if (Des[2] + 1 == Des[3])
                {
                    if (Des[3] + 1 == Des[4])
                    {
                        tab[12][joueur] = 40;
                    }
                }
            }
        }
        tabtour[12][joueur] = 1;
        break;

    case 12: //yams (donne les points si tous les dés sont identiques)
        for (i = 0; i < 5; i++)
        {
            if (Des[0] == Des[1] && Des[1] == Des[2] && Des[2] == Des[3] && Des[3] == Des[4])
            {
                tab[13][joueur] = 50;
            }
        }
        tabtour[13][joueur] = 1;
        break;

    case 13: //chance (donne des points équivalents à la somme des dés)
        for (i = 0; i < 5; i++)
        {
            tab[14][joueur] = tab[14][joueur] + Des[i];
        }
        tabtour[14][joueur] = 1;
        break;
    }
}

void annoncerVainqueur(int tab[LIGNES][COLONNES], nom noms[2]) //procédure qui annonce le vainqueur après avoir comparé les scores des joueurs
{
    if (tab[16][0] == tab[16][1])
    {
        printf("égalité entre les deux joueurs avec un total de %d points.\n", tab[16][0]); //cas d'égalité (très très peu probable)
    }
    else if (tab[16][0] > tab[16][1])
    {
        printf("%s l'emporte avec un total de %d points.\n", noms[0], tab[16][0]); //J1 l'emporte
    }
    else
    {
        printf("%s l'emporte avec un total de %d points.\n", noms[1], tab[16][1]); //J2 l'emporte
    }
}