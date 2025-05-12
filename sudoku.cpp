#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include "sudoku.h"


/****************************************/
/* Objectif : Construction d'une cellule
/****************************************/
cellule::cellule(int i, int j)
{
    l = i;
    c = j;
    /*if ( i <= 2 and j <= 2 ) b = 0;
    if ( i >= 3 and i <= 5 and j <= 2 ) b = 1;
    if ( i >= 6 and j <= 2 ) b = 2;
    if ( i <= 2 and j >= 3 and j <= 5 ) b = 3;
    if ( i >= 3 and i <= 5 and j >= 3 and j <= 5) b = 4;
    if ( i >= 5 and j >= 3 and j <= 5 ) b = 5;
    if ( i <= 2 and j >= 6 ) b = 6;
    if ( i >= 3 and i <= 5 and  j >= 6 ) b = 7;
    if ( i >= 6 and j >= 6 ) b = 8;*/
    b = (i / 3) * 3 + (j / 3);  
    n = 9;

    
}


/****************************************/
/* Objectif : Construteur avec argument 
permettant la création d'une grille à partir d'un 
fichier.
/****************************************/
sudoku::sudoku(char filename[])
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++) 
            grille[i][j] = 0;
    }
    ifstream file(filename);
    for (int i = 0; i < 9 ; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            file>>grille[i][j];
        }
        
    }
}


/****************************************/
/* Objectif : Affichage de la grille sudoku
/****************************************/
void sudoku::affichage()
{
	cout << setw(3) << "-" << "------------------------------------" << endl;
	for(int i = 0; i < 9; i++){
		if((i == 3) || (i == 6))
			cout << setw(3) << "-" << "------------------------------------" << endl;
		cout << setw(3) << "|";		
		for(int j = 0; j < 8; j++){
			if((j == 3) || (j == 6))
				cout << setw(3) << "|" << setw(3) << grille[i][j];
			else
				cout << setw(3) << grille[i][j];
		}
		cout << setw(3) << grille[i][8] << setw(3)<<  "|" << endl;
	}
	cout << setw(3) << "-" << "------------------------------------" << endl;
}

/****************************************/
/* Objectif : Retourne les cellules vides */
/****************************************/

void sudoku::cellule_vide()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if (grille[i][j] == 0)
            {
                c[r] = cellule(i,j);
                r++;
            }
        }
    }
}

/****************************************/
/* Objectif : Vérification si l'élement v est présent */
/****************************************/

bool sudoku::verification_l(int k, int v)
{
    for ( int i = 0; i < 9 ; i++)
    {
        if ( grille[c[k].l][i] == v )
        {
            return false;
        }
    }
    return true;
}

bool sudoku::verification_c(int k,int v)
{
    for ( int i = 0; i < 9 ; i++)
    {
        if ( grille[i][c[k].c] == v )
        {
            return false;
        }
    }
    return true;
}
bool sudoku::verification_b(int k, int v)
{
    int ligne = (c[k].l / 3) * 3; // Ligne de départ du bloc
    int col = (c[k].c / 3) * 3; // Colonne de départ du bloc

    // Parcourir le bloc 3x3
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            if (grille[ligne + i][col + j] == v) 
            {
                return false;
            }
        }
    }
    return true;
}

/****************************************/
/* Objectif : Backtracking pour résoudre le Sudoku */
/****************************************/

bool sudoku::Backtracking(int k)
{
    if (k == r) 
        return true; // Solution trouvée
    for (int val = 1; val <= 9; val++) 
    {
        if (verification_l(k, val) && verification_c(k, val) && verification_b(k, val))
        {
            grille[c[k].l][c[k].c] = val;
            if (Backtracking(k + 1)) 
            {
                return true;
            }
            grille[c[k].l][c[k].c] = 0;
        }
    }
    return false;
}

/****************************************/
/* Objectif : Détermination d'une solution de la grilleées.
La méthode renvoie vrai si une solution a été trouvée, 0 sinon
/****************************************/
bool sudoku::solution()
{
    cellule_vide();
    return Backtracking(0);
}
