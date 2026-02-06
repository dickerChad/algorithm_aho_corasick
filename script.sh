#!/bin/bash

echo "=========================================="
echo "  TP3 - Benchmarks Aho-Corasick"
echo "=========================================="
echo

# Paramètres
LONGUEUR_TEXTE=2000000
ALPHABETS=(2 4 20 70)
LONGUEURS_MOTS=("5 15" "15 30" "30 60")
NB_MOTS=100

# Créer les répertoires
mkdir -p data
mkdir -p resultats

# Fichier de résultats
RESULTATS="resultats/resultats.csv"
echo "alphabet,taille_mots,implementation,temps_ms,nb_occurrences" > $RESULTATS

# echo "=== Génération des textes ==="
# for alpha in "${ALPHABETS[@]}"; do
#     fichier="data/texte_${alpha}.txt"
#     echo "  Texte alphabet $alpha → $fichier"
#     ./genere-texte $LONGUEUR_TEXTE $alpha > "$fichier"
# done
# echo

# echo "=== Génération des ensembles de mots ==="
# for alpha in "${ALPHABETS[@]}"; do
#     for i in "${!LONGUEURS_MOTS[@]}"; do
#         read min max <<< "${LONGUEURS_MOTS[$i]}"
#         fichier="data/mots_${alpha}_${min}_${max}.txt"
#         echo "  Mots alphabet=$alpha longueur=[$min-$max] → $fichier"
#         ./genere-mots $NB_MOTS $min $max $alpha > "$fichier"
#     done
# done
# echo

echo "=== Exécution des recherches ==="
echo

for alpha in "${ALPHABETS[@]}"; do
    texte="data/texte_${alpha}.txt"
    
    echo "Alphabet $alpha:"
    
    for i in "${!LONGUEURS_MOTS[@]}"; do
        read min max <<< "${LONGUEURS_MOTS[$i]}"
        mots="data/mots_${alpha}_${min}_${max}.txt"
        taille="${min}-${max}"
        
        echo "  Mots [$taille]:"
        
        # Test ac-matrice
        echo -n "    ac-matrice... "
        START=$(date +%s%N)
        RESULT=$(./ac-matrice "$mots" "$texte")
        END=$(date +%s%N)
        TEMPS=$(( (END - START) / 1000000 ))
        echo "${RESULT} occurrences en ${TEMPS}ms"
        echo "$alpha,$taille,matrice,$TEMPS,$RESULT" >> $RESULTATS
        
        # Test ac-hachage
        echo -n "    ac-hachage... "
        START=$(date +%s%N)
        RESULT=$(./ac-hachage "$mots" "$texte")
        END=$(date +%s%N)
        TEMPS=$(( (END - START) / 1000000 ))
        echo "${RESULT} occurrences en ${TEMPS}ms"
        echo "$alpha,$taille,hachage,$TEMPS,$RESULT" >> $RESULTATS
    done
    echo
done

echo "=========================================="
echo "  Résultats sauvegardés"
echo "=========================================="
echo
echo "Fichier CSV : $RESULTATS"
echo
echo "Résumé:"
column -t -s',' $RESULTATS
echo
echo "Pour générer les graphiques:"
echo "  python3 plot_results.py $RESULTATS"