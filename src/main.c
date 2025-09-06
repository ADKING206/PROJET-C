#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>
#include <SDL.h>
#include "Classe.h"
#include "Salle.h"
#include "Reservation.h"



int main(int argc, char **argv)
{
    setlocale(LC_ALL,"French");
    SDL_version nb;
    SDL_VERSION(&nb);
    printf("Bienvenue sur é la SDL %d.%d.%d!\n", nb.major,nb.minor,nb.patch);
    return 0;
}