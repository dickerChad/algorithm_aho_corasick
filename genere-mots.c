#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <nb_mots> <long_min> <long_max> <taille_alphabet>\n", argv[0]);
        return 1;
    }

    int nb_mots = atoi(argv[1]);
    int long_min = atoi(argv[2]);
    int long_max = atoi(argv[3]);
    int taille_alphabet = atoi(argv[4]);

    if (nb_mots <= 0 || long_min <= 0 || long_max < long_min || 
        taille_alphabet <= 0 || taille_alphabet > 256) {
        fprintf(stderr, "Erreur: paramètres invalides\n");
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < nb_mots; i++) {
        int longueur = long_min + rand() % (long_max - long_min + 1);
        
        for (int j = 0; j < longueur; j++) {
            int c = rand() % taille_alphabet;
            putchar(c);
        }
        
        putchar('\n');
    }

    return 0;
}