#!/bin/bash

# Test pour comprendre les chevauchements

echo "Test 1: Mots simples avec chevauchements"
echo "a" > test_mots.txt
echo "aa" >> test_mots.txt
echo "aaa" >> test_mots.txt

echo -n "aaaa" > test_texte.txt

echo "Texte: aaaa"
echo "Mots: a, aa, aaa"
echo
echo "Résultat ac-matrice:"
./ac-matrice test_mots.txt test_texte.txt
echo
echo "Attendu: 9 occurrences"
echo "  Position 0: a, aa, aaa (3)"
echo "  Position 1: a, aa, aaa (3)"
echo "  Position 2: a, aa (2)"
echo "  Position 3: a (1)"
echo

echo "================================"
echo

echo "Test 2: Mots sans chevauchements"
echo "abc" > test_mots2.txt
echo "xyz" >> test_mots2.txt

echo -n "abcxyzabc" > test_texte2.txt

echo "Texte: abcxyzabc"
echo "Mots: abc, xyz"
echo
echo "Résultat ac-matrice:"
./ac-matrice test_mots2.txt test_texte2.txt
echo
echo "Attendu: 3 occurrences (abc à pos 0 et 6, xyz à pos 3)"
echo

# Nettoyage
rm -f test_mots.txt test_texte.txt test_mots2.txt test_texte2.txt