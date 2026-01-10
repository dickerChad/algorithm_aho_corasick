#ifndef TRIE_HACHAGE_H
#define TRIE_HACHAGE_H

#define TAILLE_TABLE_HACHAGE 256

typedef struct TransitionHash {
    unsigned char caractere;
    struct NoeudHachage* noeud;
    struct TransitionHash* suivant;
} TransitionHash;

typedef struct NoeudHachage {
    TransitionHash* table[TAILLE_TABLE_HACHAGE];
    struct NoeudHachage* suppleant;
    int est_fin_mot;
    int nb_mots_finissant;
} NoeudHachage;

typedef struct {
    NoeudHachage* racine;
} TrieHachage;

TrieHachage* createTrie();
void insertInTrie(TrieHachage* trie, const unsigned char* mot, int longueur);
void construireSuppleantsHash(TrieHachage* trie);
long long rechercherMotsHachage(TrieHachage* trie, const unsigned char* texte, long longueur);
void detruireTrieHachage(TrieHachage* trie);

#endif