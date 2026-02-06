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
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <longueur> <taille_alphabet>\n", argv[0]);
        return 1;
    }

    long longueur = atol(argv[1]);
    int taille_alphabet = atoi(argv[2]);

    if (longueur <= 0 || taille_alphabet <= 0 || taille_alphabet > 91) {
        fprintf(stderr, "Erreur: taille_alphabet doit être entre 1 et 91\n");
        return 1;
    }

    srand(time(NULL));

    for (long i = 0; i < longueur; i++) {
        int index = rand() % taille_alphabet;
        putchar(getChar(index));
    }

    return 0;
}