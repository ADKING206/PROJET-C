#ifndef _CLASSE_H_
#define _CLASSE_H_
typedef enum Niveau {
    LICENCE, MASTER, DOCTORAT
}Niveau;

/*Défintion d'une classe*/

typedef struct CLASSE 
{
    char code_unique[10];
    char class_name[26];
    Niveau class_niveau;
    int class_effectif ;
}CLASSE;

/*Prototype de notre classe*/

void add_class(void);
void edit_class(void);
void delete_class(void);
void search_class(void);
void show_class(void);

#endif