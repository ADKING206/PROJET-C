#ifndef _SALLE_H_
#define _SALLE_H_


/*Définition d'une salle*/
typedef struct Salle
{
    char code_salle[10];
    char salle_name[16];
    int salle_capacity;
    char dispo_machine[4];
}Salle;

/*Les prototypes de notre salles*/

void add_salle(void);
void edit_salle(void);
void delete_salle(void);
void search_salle(void);
void show_salle(void);
#endif