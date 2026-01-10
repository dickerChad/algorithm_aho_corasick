#include "trie-hachage.h"
#include "file.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static unsigned int fonctionHachage(unsigned char c) {
    return ((c * 2654435761U) >> 24) % TAILLE_TABLE_HACHAGE;
}

static NoeudHachage* creerNoeudHash() {
    NoeudHachage* noeud = malloc(sizeof(NoeudHachage));
    if (!noeud) {
        fprintf(stderr, "Erreur allocation noeud\n");
        exit(1);
    }
    
    for (int i = 0; i < TAILLE_TABLE_HACHAGE; i++) {
        noeud->table[i] = NULL;
    }
    
    noeud->suppleant = NULL;
    noeud->est_fin_mot = 0;
    noeud->nb_mots_finissant = 0;
    
    return noeud;
}

static NoeudHachage* obtenirTransition(NoeudHachage* noeud, unsigned char c) {
    unsigned int index = fonctionHachage(c);
    TransitionHash* courant = noeud->table[index];
    
    while (courant != NULL) {
        if (courant->caractere == c) {
            return courant->noeud;
        }
        courant = courant->suivant;
    }
    
    return NULL;
}

static void ajouterTransition(NoeudHachage* noeud, unsigned char c, NoeudHachage* cible) {
    unsigned int index = fonctionHachage(c);
    
    TransitionHash* nouvelle = malloc(sizeof(TransitionHash));
    if (!nouvelle) {
        fprintf(stderr, "Erreur allocation transition\n");
        exit(1);
    }
    
    nouvelle->caractere = c;
    nouvelle->noeud = cible;
    nouvelle->suivant = noeud->table[index];
    noeud->table[index] = nouvelle;
}

TrieHachage* createTrie() {
    TrieHachage* trie = malloc(sizeof(TrieHachage));
    if (!trie) {
        fprintf(stderr, "Erreur allocation trie\n");
        exit(1);
    }
    
    trie->racine = creerNoeudHash();
    return trie;
}

void insertInTrie(TrieHachage* trie, const unsigned char* mot, int longueur) {
    NoeudHachage* courant = trie->racine;
    
    for (int i = 0; i < longueur; i++) {
        unsigned char c = mot[i];
        NoeudHachage* suivant = obtenirTransition(courant, c);
        
        if (suivant == NULL) {
            suivant = creerNoeudHash();
            ajouterTransition(courant, c, suivant);
        }
        
        courant = suivant;
    }
    
    courant->est_fin_mot = 1;
    courant->nb_mots_finissant++;
}

static void obtenirToutesTransitions(NoeudHachage* noeud, unsigned char* caracteres, int* nb) {
    *nb = 0;
    for (int i = 0; i < TAILLE_TABLE_HACHAGE; i++) {
        TransitionHash* courant = noeud->table[i];
        while (courant != NULL) {
            caracteres[*nb] = courant->caractere;
            (*nb)++;
            courant = courant->suivant;
        }
    }
}

void construireSuppleantsHash(TrieHachage* trie) {
    File* file = creerFile(1000);
    NoeudHachage* racine = trie->racine;
    
    racine->suppleant = racine;
    
    unsigned char caracteres[256];
    int nb_transitions;
    obtenirToutesTransitions(racine, caracteres, &nb_transitions);
    
    for (int i = 0; i < nb_transitions; i++) {
        NoeudHachage* enfant = obtenirTransition(racine, caracteres[i]);
        enfant->suppleant = racine;
        Enfiler(file, enfant);
    }
    
    while (!estVide(file)) {
        NoeudHachage* noeud = (NoeudHachage*)Defiler(file);
        
        obtenirToutesTransitions(noeud, caracteres, &nb_transitions);
        
        for (int i = 0; i < nb_transitions; i++) {
            unsigned char c = caracteres[i];
            NoeudHachage* enfant = obtenirTransition(noeud, c);
            NoeudHachage* suppleant = noeud->suppleant;
            
            while (suppleant != racine && obtenirTransition(suppleant, c) == NULL) {
                suppleant = suppleant->suppleant;
            }
            
            NoeudHachage* suiv = obtenirTransition(suppleant, c);
            if (suiv != NULL && suiv != enfant) {
                enfant->suppleant = suiv;
            } else {
                enfant->suppleant = racine;
            }
            
            enfant->nb_mots_finissant += enfant->suppleant->nb_mots_finissant;
            
            Enfiler(file, enfant);
        }
    }
    
    detruireFile(file);
}

long long rechercherMotsHachage(TrieHachage* trie, const unsigned char* texte, long longueur) {
    long long compteur = 0;
    NoeudHachage* etat = trie->racine;
    
    for (long i = 0; i < longueur; i++) {
        unsigned char c = texte[i];
        
        while (etat != trie->racine && obtenirTransition(etat, c) == NULL) {
            etat = etat->suppleant;
        }
        
        NoeudHachage* suivant = obtenirTransition(etat, c);
        if (suivant != NULL) {
            etat = suivant;
        }
        
        if (etat->nb_mots_finissant > 0) {
            compteur += etat->nb_mots_finissant;
        }
    }
    
    return compteur;
}

static void detruireTransitions(TransitionHash* trans) {
    while (trans != NULL) {
        TransitionHash* suivant = trans->suivant;
        free(trans);
        trans = suivant;
    }
}

static void detruireNoeudHashRecursif(NoeudHachage* noeud) {
    if (noeud == NULL) return;
    
    for (int i = 0; i < TAILLE_TABLE_HACHAGE; i++) {
        TransitionHash* courant = noeud->table[i];
        while (courant != NULL) {
            NoeudHachage* enfant = courant->noeud;
            courant = courant->suivant;
            detruireNoeudHashRecursif(enfant);
        }
    }
    
    for (int i = 0; i < TAILLE_TABLE_HACHAGE; i++) {
        detruireTransitions(noeud->table[i]);
    }
    
    free(noeud);
}

void detruireTrieHachage(TrieHachage* trie) {
    if (trie) {
        detruireNoeudHashRecursif(trie->racine);
        free(trie);
    }
}