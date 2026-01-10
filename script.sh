#!/bin/bash

# Script d'expérimentation pour le TP3 - Aho-Corasick

echo "=== Début des expérimentations ==="
echo

# Créer les répertoires nécessaires
mkdir -p data
mkdir -p resultats

# Paramètres
LONGUEUR_TEXTE=5000000
ALPHABETS=(2 4 20 70)
LONGUEURS_MOTS=("5 15" "15 30" "30 60")
NB_MOTS=100

# Fichier de résultats
RESULTATS="resultats/resultats.csv"
echo "alphabet,taille_mots,implementation,temps_ms,nb_occurrences" > $RESULTATS

echo "=== Génération des textes ==="
for alpha in "${ALPHABETS[@]}"; do
    echo "Génération texte alphabet $alpha..."
    ./genere-texte $LONGUEUR_TEXTE $alpha > data/texte_${alpha}.txt
done
echo

echo "=== Génération des ensembles de mots ==="
for alpha in "${ALPHABETS[@]}"; do
    for i in "${!LONGUEURS_MOTS[@]}"; do
        read min max <<< "${LONGUEURS_MOTS[$i]}"
        nom="mots_${alpha}_${min}_${max}.txt"
        echo "Génération $nom..."
        ./genere-mots $NB_MOTS $min $max $alpha > data/$nom
    done
done
echo

echo "=== Exécution des recherches ==="
for alpha in "${ALPHABETS[@]}"; do
    texte="data/texte_${alpha}.txt"
    
    for i in "${!LONGUEURS_MOTS[@]}"; do
        read min max <<< "${LONGUEURS_MOTS[$i]}"
        mots="data/mots_${alpha}_${min}_${max}.txt"
        taille="${min}-${max}"
        
        echo "Test: alphabet=$alpha, taille_mots=$taille"
        
        # Test ac-matrice
        echo -n "  ac-matrice... "
        START=$(date +%s%N)
        RESULT=$(./ac-matrice $mots $texte)
        END=$(date +%s%N)
        TEMPS=$(( (END - START) / 1000000 ))
        echo "$RESULT occurrences en ${TEMPS}ms"
        echo "$alpha,$taille,matrice,$TEMPS,$RESULT" >> $RESULTATS
        
        # Test ac-hachage
        echo -n "  ac-hachage... "
        START=$(date +%s%N)
        RESULT=$(./ac-hachage $mots $texte)
        END=$(date +%s%N)
        TEMPS=$(( (END - START) / 1000000 ))
        echo "$RESULT occurrences en ${TEMPS}ms"
        echo "$alpha,$taille,hachage,$TEMPS,$RESULT" >> $RESULTATS
        
        echo
    done
done

echo "=== Résultats sauvegardés dans $RESULTATS ==="
echo
echo "Résumé des résultats:"
column -t -s',' $RESULTATS

echo
echo "=== Expérimentations terminées ==="