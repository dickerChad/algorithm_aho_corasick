#ifndef TRIE_MATRICE_H
#define TRIE_MATRICE_H

#define TAILLE_ALPHABET 256

typedef struct NoeudMatrice {
    struct NoeudMatrice* transitions[TAILLE_ALPHABET];
    struct NoeudMatrice* suppleant;
    int est_fin_mot;
    int nb_mots_finissant;
} NoeudMatrice;

typedef struct {
    NoeudMatrice* racine;
} TrieMatrice;

TrieMatrice* createTrie();
void insertInTrie(TrieMatrice* trie, const unsigned char* mot, int longueur);
void construireSuppleants(TrieMatrice* trie);
long long rechercherMotsMatrice(TrieMatrice* trie, const unsigned char* texte, long longueur);
void detruireTrieMatrice(TrieMatrice* trie);

#endif