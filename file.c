#include "file.h"
#include <stdlib.h>
#include <stdio.h>

struct File {
    void** elements;
    int debut;
    int fin;
    int taille;
    int capacite;
};

File* creerFile(int capacite) {
    File* file = malloc(sizeof(File));
    if (!file) {
        fprintf(stderr, "Erreur allocation file\n");
        exit(1);
    }
    
    file->elements = malloc(sizeof(void*) * capacite);
    if (!file->elements) {
        fprintf(stderr, "Erreur allocation elements file\n");
        exit(1);
    }
    
    file->debut = 0;
    file->fin = 0;
    file->taille = 0;
    file->capacite = capacite;
    
    return file;
}

void detruireFile(File* file) {
    if (file) {
        free(file->elements);
        free(file);
    }
}

void Enfiler(File* file, void* element) {
    if (file->taille == file->capacite) {
        file->capacite *= 2;
        void** nouveaux = malloc(sizeof(void*) * file->capacite);
        if (!nouveaux) {
            fprintf(stderr, "Erreur reallocation file\n");
            exit(1);
        }
        
        for (int i = 0; i < file->taille; i++) {
            nouveaux[i] = file->elements[(file->debut + i) % file->taille];
        }
        
        free(file->elements);
        file->elements = nouveaux;
        file->debut = 0;
        file->fin = file->taille;
    }
    
    file->elements[file->fin] = element;
    file->fin = (file->fin + 1) % file->capacite;
    file->taille++;
}

void* Defiler(File* file) {
    if (file->taille == 0) {
        return NULL;
    }
    
    void* element = file->elements[file->debut];
    file->debut = (file->debut + 1) % file->capacite;
    file->taille--;
    
    return element;
}

int estVide(File* file) {
    return file->taille == 0;
}