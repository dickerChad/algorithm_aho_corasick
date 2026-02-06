# TP3 - Algorithme d'Aho-Corasick

## Compilation

```bash
make
```

Cela génère 4 exécutables :
- `genere-texte`
- `genere-mots`
- `ac-matrice`
- `ac-hachage`

Pour nettoyer :
```bash
make clean
```

## Utilisation

### genere-texte

Génère un texte pseudo-aléatoire.

**Syntaxe :**
```bash
./genere-texte <longueur> <taille_alphabet>
```

**Exemple :**
```bash
./genere-texte 1000000 20 > texte_test.txt
```

Génère un texte de 1 million de caractères sur un alphabet de taille 20.

### genere-mots

Génère un ensemble de mots pseudo-aléatoires (un par ligne).

**Syntaxe :**
```bash
./genere-mots <nb_mots> <long_min> <long_max> <taille_alphabet>
```

**Exemple :**
```bash
./genere-mots 100 5 15 20 > mots_test.txt
```

Génère 100 mots de longueur entre 5 et 15 caractères sur un alphabet de taille 20.

### ac-matrice

Recherche des mots dans un texte avec l'algorithme d'Aho-Corasick (représentation par matrice de transitions).

**Syntaxe :**
```bash
./ac-matrice <fichier_mots> <fichier_texte>
```

**Exemple :**
```bash
./ac-matrice mots.txt texte.txt
```

Affiche le nombre total d'occurrences des mots de `mots.txt` dans `texte.txt`.

### ac-hachage

Même fonctionnalité que `ac-matrice` mais avec une représentation par table de hachage.

**Syntaxe :**
```bash
./ac-hachage <fichier_mots> <fichier_texte>
```

**Exemple :**
```bash
./ac-hachage mots.txt texte.txt
```

## Validation

### Test rapide avec fichiers fournis

```bash
./ac-matrice mots.txt texte.txt   # affiche : 80
./ac-hachage mots.txt texte.txt   # affiche : 80
```

### Test de validation automatique

```bash
bash test_validation.sh
```

Ce script (fourni par le prof) :
- Génère un texte et des mots de test
- Exécute les deux implémentations
- Vérifie automatiquement que les résultats sont identiques

## Expérimentations complètes

Pour effectuer les benchmarks du TP (étapes 4-6) :

```bash
bash script.sh
```

Ce script génère :
- 4 textes de 5 millions de caractères (alphabets : 2, 4, 20, 70)
- 12 ensembles de 100 mots (3 longueurs × 4 alphabets)
- Lance les 24 recherches et mesure les temps d'exécution
- Produit un fichier `resultats/resultats.csv` avec tous les résultats

**Attention :** Ce script peut prendre plusieurs minutes à s'exécuter.


## Algorithme

L'algorithme d'Aho-Corasick permet de rechercher simultanément k mots dans un texte en une seule passe.

**Complexité :**
- Construction du Trie : O(Σ longueurs des mots)
- Calcul des suppléants : O(nombre de nœuds)
- Recherche : O(longueur du texte + nombre d'occurrences)

**Deux implémentations :**
1. **Matrice** : accès O(1), mémoire O(nœuds × taille_alphabet)
2. **Hachage** : accès O(1) amorti, mémoire O(transitions réelles)