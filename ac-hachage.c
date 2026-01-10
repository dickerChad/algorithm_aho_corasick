#include "trie-hachage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned char* lireFichier(const char* nom_fichier, long* taille) {
    FILE* f = fopen(nom_fichier, "rb");
    if (!f) {
        fprintf(stderr, "Erreur ouverture fichier: %s\n", nom_fichier);
        exit(1);
    }
    
    fseek(f, 0, SEEK_END);
    *taille = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    unsigned char* contenu = malloc(*taille + 1);
    if (!contenu) {
        fprintf(stderr, "Erreur allocation mémoire\n");
        exit(1);
    }
    
    size_t lu = fread(contenu, 1, *taille, f);
    if (lu != (size_t)*taille) {
        fprintf(stderr, "Erreur lecture fichier\n");
        exit(1);
    }
    contenu[*taille] = '\0';
    
    fclose(f);
    return contenu;
}

static void lireMots(const char* nom_fichier, TrieHachage* trie) {
    FILE* f = fopen(nom_fichier, "rb");
    if (!f) {
        fprintf(stderr, "Erreur ouverture fichier mots: %s\n", nom_fichier);
        exit(1);
    }
    
    unsigned char ligne[10000];
    while (fgets((char*)ligne, sizeof(ligne), f)) {
        int longueur = strlen((char*)ligne);
        
        if (longueur > 0 && ligne[longueur - 1] == '\n') {
            longueur--;
        }
        
        if (longueur > 0) {
            insertInTrie(trie, ligne, longueur);
        }
    }
    
    fclose(f);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier_mots> <fichier_texte>\n", argv[0]);
        return 1;
    }
    
    TrieHachage* trie = createTrie();
    
    lireMots(argv[1], trie);
    
    construireSuppleantsHash(trie);
    
    long taille_texte;
    unsigned char* texte = lireFichier(argv[2], &taille_texte);
    
    long long nb_occurrences = rechercherMotsHachage(trie, texte, taille_texte);
    
    printf("%lld\n", nb_occurrences);
    
    free(texte);
    detruireTrieHachage(trie);
    
    return 0;
}