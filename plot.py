#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pandas as pd
import matplotlib.pyplot as plt
import sys

def plot_results(csv_file):
    # Lire les résultats
    df = pd.read_csv(csv_file)
    
    # Créer une figure avec plusieurs sous-graphiques
    fig, axes = plt.subplots(2, 2, figsize=(15, 12))
    fig.suptitle('Performances Aho-Corasick: Matrice vs Hachage', fontsize=16)
    
    # 1. Temps en fonction de la taille de l'alphabet (par taille de mots)
    ax = axes[0, 0]
    
    # Définir l'ordre correct des tailles
    tailles_ordre = ['5-15', '15-30', '30-60']
    
    for taille in tailles_ordre:
        subset = df[df['taille_mots'] == taille]
        matrice_data = subset[subset['implementation'] == 'matrice']
        hachage_data = subset[subset['implementation'] == 'hachage']
        
        ax.plot(matrice_data['alphabet'], matrice_data['temps_ms'], 
                marker='o', label=f'Matrice (mots {taille})')
        ax.plot(hachage_data['alphabet'], hachage_data['temps_ms'], 
                marker='s', linestyle='--', label=f'Hachage (mots {taille})')
    
    ax.set_xlabel('Taille de l\'alphabet')
    ax.set_ylabel('Temps (ms)')
    ax.set_title('Temps vs Taille alphabet')
    ax.legend()
    ax.grid(True, alpha=0.3)
    
    # 2. Comparaison directe Matrice vs Hachage par alphabet
    ax = axes[0, 1]
    for alpha in df['alphabet'].unique():
        subset = df[df['alphabet'] == alpha]
        matrice_temps = subset[subset['implementation'] == 'matrice']['temps_ms'].values
        hachage_temps = subset[subset['implementation'] == 'hachage']['temps_ms'].values
        
        positions = range(len(matrice_temps))
        width = 0.35
        
        ax.bar([p - width/2 for p in positions], matrice_temps, width, 
               label=f'Matrice (α={alpha})', alpha=0.8)
        ax.bar([p + width/2 for p in positions], hachage_temps, width, 
               label=f'Hachage (α={alpha})', alpha=0.8)
    
    ax.set_xlabel('Configuration')
    ax.set_ylabel('Temps (ms)')
    ax.set_title('Matrice vs Hachage par alphabet')
    ax.legend()
    ax.grid(True, alpha=0.3, axis='y')
    
    # 3. Rapport de performance (Hachage/Matrice)
    ax = axes[1, 0]
    
    # Définir l'ordre correct des tailles
    tailles_ordre = ['5-15', '15-30', '30-60']
    
    for taille in tailles_ordre:
        subset = df[df['taille_mots'] == taille]
        alphabets = subset[subset['implementation'] == 'matrice']['alphabet'].values
        matrice_temps = subset[subset['implementation'] == 'matrice']['temps_ms'].values
        hachage_temps = subset[subset['implementation'] == 'hachage']['temps_ms'].values
        
        ratio = hachage_temps / matrice_temps
        ax.plot(alphabets, ratio, marker='o', label=f'Mots {taille}')
    
    ax.axhline(y=1, color='r', linestyle='--', alpha=0.5, label='Performance égale')
    ax.set_xlabel('Taille de l\'alphabet')
    ax.set_ylabel('Ratio Hachage/Matrice')
    ax.set_title('Rapport de performance (>1 = matrice plus rapide)')
    ax.legend()
    ax.grid(True, alpha=0.3)
    
    # 4. Temps en fonction de la longueur des mots
    ax = axes[1, 1]
    
    # Définir l'ordre correct des tailles
    tailles_ordre = ['5-15', '15-30', '30-60']
    
    for alpha in df['alphabet'].unique():
        subset = df[df['alphabet'] == alpha]
        
        temps_matrice = []
        temps_hachage = []
        
        for taille in tailles_ordre:
            mat = subset[(subset['implementation'] == 'matrice') & (subset['taille_mots'] == taille)]
            hach = subset[(subset['implementation'] == 'hachage') & (subset['taille_mots'] == taille)]
            
            if not mat.empty:
                temps_matrice.append(mat['temps_ms'].values[0])
            if not hach.empty:
                temps_hachage.append(hach['temps_ms'].values[0])
        
        x_pos = range(len(tailles_ordre))
        ax.plot(x_pos, temps_matrice, marker='o', label=f'Matrice (α={alpha})')
        ax.plot(x_pos, temps_hachage, marker='s', linestyle='--', label=f'Hachage (α={alpha})')
    
    ax.set_xticks(range(len(tailles_ordre)))
    ax.set_xticklabels(tailles_ordre)
    ax.set_xlabel('Longueur des mots')
    ax.set_ylabel('Temps (ms)')
    ax.set_title('Temps vs Longueur des mots')
    ax.legend()
    ax.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('resultats/graphiques.png', dpi=300, bbox_inches='tight')
    print("Graphiques sauvegardés dans resultats/graphiques.png")
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 plot_results.py <fichier_csv>")
        sys.exit(1)
    
    plot_results(sys.argv[1])