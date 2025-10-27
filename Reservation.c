#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "Classe.h"
#include "Salle.h"
#include "Reservation.h"
/*----------------------------------------------------------------------------------------*/
bool existance_jour(int j,int m, int an )
{
    if (m == 1 || m==3 || m==5 || m==7 || m==8 || m==10 ||m==12)
    {
        if(j>0 || j<=31)
        {
            return true;
        } 
        return false;
    }
    if (m==4 || m==6 || m==9 || m==11)
    {
        if(j>0 || j<=30)
        {
            return true;
        } 
        return false;
    }  
    if (m==2 && an % 4 == 0)
    {
        if(j>0 || j<=29)
        {
            return true;
        } 

        return false;
    }   
    else if (m==2)
    {
        if(j>0 || j<=28)
        {
            return true;
        } 

        return false;
    }   
}
/*----------------------------------------------------------------------------------------*/
bool sauvauch_t_il(int HB , int HF , int JJ , int MM , int AA )
{
    Reservation verifie;
    FILE *file = fopen("reservation.bin","rb+");
    while (fread(&verifie,sizeof(Reservation),1,file) ==1 )
    {
        if (verifie.Heure_de_debut == HB || verifie.Heure_de_fin == HF )
        {
            if (verifie.date_de_reserv.jour == JJ && verifie.date_de_reserv.mois == MM && verifie.date_de_reserv.annee )
            {
                return true;
            }    
        }
        else if (verifie.Heure_de_debut < HB || verifie.Heure_de_fin > HB )
        {
            if (verifie.date_de_reserv.jour == JJ && verifie.date_de_reserv.mois == MM && verifie.date_de_reserv.annee )
            {
                return true;
            }    
        }
        else if (verifie.Heure_de_debut > HF || verifie.Heure_de_fin < HF )
        {
            if (verifie.date_de_reserv.jour == JJ && verifie.date_de_reserv.mois == MM && verifie.date_de_reserv.annee )
            {
                return true;
            }    
        }
        return false;
    }
    /*Ce fonction permet de vérifier si la reservation n'as pas encore été choisi*/
}
/*----------------------------------------------------------------------------------------*/
void add_reserv(void)
{
    FILE *file1 = fopen("classe.bin","rb+");
    FILE *file2 = fopen("salle.bin","rb+");
    Reservation new_reserv;
    FILE *file = fopen("reservation.bin","ab+");
    CLASSE one_classe;
    Salle one_salle;

    srand(time(NULL));
    if (file == NULL)
    {
        fprintf(stderr,"Erreur d'ouverture, Veillez ressayer plustard");
        exit(EXIT_FAILURE);
    }
    if (file1 == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    if (file2 == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    new_reserv.Num_reserv = (rand() % 1000) + 1; /*Le numéro de réservation elle est donné 
    aléatoirement avec la fonction rand()*/
    printf("Veillez saisir le code de votre classe: ");
    scanf("%s",new_reserv.code_classe_reserv);
    while(code_classe_exist(new_reserv.code_classe_reserv))/*Le code de la classe permet de voir
    si la classe que vous voudrais réservé existe*/
    {
        printf("Le code que vous avez saisi n'existe pas\nveillez la resaisir: ");
        scanf("%s",new_reserv.code_classe_reserv);   
    }
/*Le bout de code suivant permet de saisir une salle cependant on doit vérifier si la capacité de 
la salle saisie est capable de recevoir l'effectif de la classe pour cela on lit la classe dans
un variable et la salle dans un variable puis on compare l'effectif de la classe et la capacité de 
la salle cependant pour éviter la repetition du code et l'utilisation du boucle while ou do..while
j'ai préferer utiliser la fonction goto*/
    Revenir_ici_pour_retaper_la_salle_de_clase:
    printf("Veillez saisir le code de votre salle: ");
    scanf("%s",new_reserv.code_salle_reserv);
    while (code_salle_exist(new_reserv.code_salle_reserv));
    {
        printf("Le code que vous avez saisi n'existe pas\nveillez la resaisir: ");
        scanf("%s",new_reserv.code_salle_reserv);       
    }
    while (fread(&one_classe,sizeof(CLASSE),1,file1) == 1)
    {
        if (strcmp(one_classe.code_unique,new_reserv.code_classe_reserv)==0)
        {
            break;
        }
    }
    while (fread(&one_salle,sizeof(Salle),1,file2)==1)
    {
        if (strcmp(one_salle.code_salle,new_reserv.code_salle_reserv)==0)
        {
         break;
        }   
    }
    if (one_salle.salle_capacity < one_classe.class_effectif)
    {
        printf("La salle n'est pas assez grand pour contenir l'effectif de la classe, Veuillez choisir une autre salle\n");
        goto Revenir_ici_pour_retaper_la_salle_de_clase;
    } 
    /*Le bout de code suivant nous permet de gerer la date de la reservation en donnant le jour 
    et la date en format JJ/MM/AAAA eet on vérifie si le années n'est bissextile et le nombre de 
    mois et exact et que le jour choisie en fonction du mois est-elle correct*/
    printf("Saisie de la date JJ/MM/AAAA\n");
    printf("AAAA: ");
    scanf("%d",&new_reserv.date_de_reserv.annee);
    while (new_reserv.date_de_reserv.annee < 2025)
    {
        printf("L'annes que vous avez saisie n'est pas bon veillez la resaisir: ");
        scanf("%d",&new_reserv.date_de_reserv.annee);
    }
    printf("MM: ");
    scanf("%d",&new_reserv.date_de_reserv.mois);
    while (new_reserv.date_de_reserv.mois < MOIS)
    {
        printf("L'annes que vous avez saisie n'est pas bon veillez la resaisir: ");
        scanf("%d",&new_reserv.date_de_reserv.mois);
    }

    printf("JJ : ");
    scanf("%d",&new_reserv.date_de_reserv.jour);
    while (!existance_jour(new_reserv.date_de_reserv.jour,new_reserv.date_de_reserv.mois,new_reserv.date_de_reserv.annee))
    {
        printf("Le jour que vous avez saisie n'est bon veillez la resaisir: ");
        scanf("%d",&new_reserv.date_de_reserv.jour);
    }
    printf("Veillez saisr l'heure de debut : ");
    scanf("%d",new_reserv.Heure_de_debut);
    while (new_reserv.Heure_de_debut < 8 || new_reserv.Heure_de_debut > 19);
    {
        printf("Veillez la resaisir c'est pas bon : ");
        scanf("%d",new_reserv.Heure_de_debut);
    }
    printf("Veillez saisr l'heure de fin : ");
    scanf("%d",new_reserv.Heure_de_fin);
    while (new_reserv.Heure_de_fin < 8 || new_reserv.Heure_de_fin > 19);
    {
        printf("Veillez la resaisir c'est pas bon : ");
        scanf("%d",new_reserv.Heure_de_fin);
    }
    /*Cependant il faut vérifier si deux classe ne sont pas reserve dans une même salle
    le même jour et la même heure*/

    
}