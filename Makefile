CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99

EXEC = genere-texte genere-mots ac-matrice ac-hachage
OBJ = file.o trie-matrice.o trie-hachage.o

all: $(EXEC)

genere-texte: genere-texte.c
	$(CC) $(CFLAGS) -o $@ $<

genere-mots: genere-mots.c
	$(CC) $(CFLAGS) -o $@ $<

file.o: file.c file.h
	$(CC) $(CFLAGS) -c $<

trie-matrice.o: trie-matrice.c trie-matrice.h file.h
	$(CC) $(CFLAGS) -c $<

trie-hachage.o: trie-hachage.c trie-hachage.h file.h
	$(CC) $(CFLAGS) -c $<

ac-matrice: ac-matrice.c trie-matrice.o file.o
	$(CC) $(CFLAGS) -o $@ $^

ac-hachage: ac-hachage.c trie-hachage.o file.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(EXEC)
	rm -f texte3.txt mots3.txt res-ac-matrice res-ac-hachage
	rm -rf data/ resultats/

.PHONY: all clean