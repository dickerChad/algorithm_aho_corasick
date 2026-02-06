#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Retourne le caractère correspondant à l'index dans l'alphabet
   0 -> 'a', 1 -> 'b', ..., 25 -> 'z', 26 -> 'A', ..., 51 -> 'Z',
   52 -> '0', ..., 61 -> '9', puis symboles pour > 62 */
static char getChar(int index) {
    if (index < 26) {
        return 'a' + index;
    } else if (index < 52) {
        return 'A' + (index - 26);
    } else if (index < 62) {
        return '0' + (index - 52);
    } else {
        /* Symboles pour alphabets > 62 */
        const char symbols[] = "!@#$%^&*()-_=+[]{}|;:,.<>?/~`";
        int sym_index = index - 62;
        if (sym_index < 29) {
            return symbols[sym_index];
        }
        /* Fallback pour très grands alphabets */
        return 33 + (index % 94);
    }
}

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
        taille_alphabet <= 0 || taille_alphabet > 91) {
        fprintf(stderr, "Erreur: taille_alphabet doit être entre 1 et 91\n");
        return 1;
    }

    srand(time(NULL) + 12345);  /* Seed différent de genere-texte */

    for (int i = 0; i < nb_mots; i++) {
        int longueur = long_min + rand() % (long_max - long_min + 1);
        
        for (int j = 0; j < longueur; j++) {
            int index = rand() % taille_alphabet;
            putchar(getChar(index));
        }
        
        putchar('\n');
    }

    return 0;
}