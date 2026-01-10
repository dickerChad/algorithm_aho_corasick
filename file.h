#ifndef FILE_H
#define FILE_H

typedef struct File File;

File* creerFile(int capacite);
void detruireFile(File* file);
void Enfiler(File* file, void* element);
void* Defiler(File* file);
int estVide(File* file);

#endif