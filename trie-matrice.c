#include "trie-matrice.h"
#include "file.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static NoeudMatrice* creerNoeud() {
    NoeudMatrice* noeud = malloc(sizeof(NoeudMatrice));
    if (!noeud) {
        fprintf(stderr, "Erreur allocation noeud\n");
        exit(1);
    }
    
    for (int i = 0; i < TAILLE_ALPHABET; i++) {
        noeud->transitions[i] = NULL;
    }
    
    noeud->suppleant = NULL;
    noeud->est_fin_mot = 0;
    noeud->nb_mots_finissant = 0;
    
    return noeud;
}

TrieMatrice* createTrie() {
    TrieMatrice* trie = malloc(sizeof(TrieMatrice));
    if (!trie) {
        fprintf(stderr, "Erreur allocation trie\n");
        exit(1);
    }
    
    trie->racine = creerNoeud();
    return trie;
}

void insertInTrie(TrieMatrice* trie, const unsigned char* mot, int longueur) {
    NoeudMatrice* courant = trie->racine;
    
    for (int i = 0; i < longueur; i++) {
        unsigned char c = mot[i];
        
        if (courant->transitions[c] == NULL) {
            courant->transitions[c] = creerNoeud();
        }
        
        courant = courant->transitions[c];
    }
    
    courant->est_fin_mot = 1;
    courant->nb_mots_finissant++;
}

void construireSuppleants(TrieMatrice* trie) {
    File* file = creerFile(1000);
    NoeudMatrice* racine = trie->racine;
    
    racine->suppleant = racine;
    
    for (int c = 0; c < TAILLE_ALPHABET; c++) {
        if (racine->transitions[c] != NULL) {
            racine->transitions[c]->suppleant = racine;
            Enfiler(file, racine->transitions[c]);
        }
    }
    
    while (!estVide(file)) {
        NoeudMatrice* noeud = (NoeudMatrice*)Defiler(file);
        
        for (int c = 0; c < TAILLE_ALPHABET; c++) {
            if (noeud->transitions[c] != NULL) {
                NoeudMatrice* enfant = noeud->transitions[c];
                NoeudMatrice* suppleant = noeud->suppleant;
                
                while (suppleant != racine && suppleant->transitions[c] == NULL) {
                    suppleant = suppleant->suppleant;
                }
                
                if (suppleant->transitions[c] != NULL && suppleant->transitions[c] != enfant) {
                    enfant->suppleant = suppleant->transitions[c];
                } else {
                    enfant->suppleant = racine;
                }
                
                enfant->nb_mots_finissant += enfant->suppleant->nb_mots_finissant;
                
                Enfiler(file, enfant);
            }
        }
    }
    
    detruireFile(file);
}

long long rechercherMotsMatrice(TrieMatrice* trie, const unsigned char* texte, long longueur) {
    long long compteur = 0;
    long long nb_matches = 0;  // Compte le nombre de positions où on trouve quelque chose
    NoeudMatrice* etat = trie->racine;
    
    for (long i = 0; i < longueur; i++) {
        unsigned char c = texte[i];
        
        while (etat != trie->racine && etat->transitions[c] == NULL) {
            etat = etat->suppleant;
        }
        
        if (etat->transitions[c] != NULL) {
            etat = etat->transitions[c];
        }
        
        if (etat->nb_mots_finissant > 0) {
            compteur += etat->nb_mots_finissant;
            nb_matches++;
            
            // DEBUG : affiche les 10 premiers matches
            if (nb_matches <= 10) {
                fprintf(stderr, "Match à position %ld: +%d occurrences (total=%lld)\n", 
                        i, etat->nb_mots_finissant, compteur);
            }
        }
    }
    
    fprintf(stderr, "Total positions avec match: %lld\n", nb_matches);
    return compteur;
}

static void detruireNoeudRecursif(NoeudMatrice* noeud) {
    if (noeud == NULL) return;
    
    for (int i = 0; i < TAILLE_ALPHABET; i++) {
        if (noeud->transitions[i] != NULL) {
            detruireNoeudRecursif(noeud->transitions[i]);
        }
    }
    
    free(noeud);
}

void detruireTrieMatrice(TrieMatrice* trie) {
    if (trie) {
        detruireNoeudRecursif(trie->racine);
        free(trie);
    }
}