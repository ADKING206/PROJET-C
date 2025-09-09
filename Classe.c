#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Classe.h"
#include "Salle.h"
#include "Reservation.h"

/*---------------------------------------------------------------------------------*/
void add_class()
{
    char *Niv[] = {"Licence", "Master" , "Doctorat"};
    CLASSE new_class;
    char clniv[10];
    FILE *file;
    file = fopen("classe.bin","ab+");
    if (file == NULL) {
        fprintf(stderr,"Ressayer plus tard");
        exit(EXIT_FAILURE);
    }
    printf("Veillez saisir le code de votre classe: ");
    scanf("%s",new_class.code_unique);
    printf("Veillez saisir le nom de votre classe: ");
    scanf("%s",new_class.class_name);
    printf("Veillez saisr l'effectif de votre classe:");
    scanf("%d",&new_class.class_effectif);
    while (new_class.class_effectif <0) {
        printf("L'effectif de la classe ne peut pas être inférieur à O\n");
        printf("Veillez resaisir l'effectif de la classe: ");
        scanf("%d",&new_class.class_effectif);
    }
    printf("Veillez choisir le niveau de votre classe %s/%s/%s",Niv[0],Niv[1],Niv[2]);
    scanf("%s",clniv);
    for (int i=0;i<3;i++) {
        if (strcmpi(clniv,Niv[i])==0) {
            new_class.class_niveau = i;
        }
    }
    printf("La classe %s de code %s de niveau %s et d'effectif %d a été bien enregistrée\n",new_class.class_name,new_class.code_unique,Niv[new_class.class_niveau],new_class.class_effectif);
    fwrite(&new_class,sizeof(CLASSE),1,file);
    fclose(file);
}