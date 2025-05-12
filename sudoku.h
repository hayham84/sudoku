class cellule
{
    friend class sudoku;
	public :
	int l; 			        // Numéro de ligne
	int c; 			        // Numéro de colonne
	int b; 			        // Numéro du bloc où se situe la cellule (l,c)
	int n;			        // Nombre de chiffres qu'il est possible initialement d'utiliser sur la cellule
	cellule(int i, int j);  // Construit la cellule de numéro de ligne i et colonne j
    cellule() : l(0), c(0), b(0), n(9) {}
    
};


/****************************************************************/
/* Objectif : Classe permettant de lire une grille sudoku et de la résoudre*/
class sudoku{
	int grille[9][9];			    // La grille

    cellule * c = new cellule[81];   // Tableau des cellules vides
    int r = 0;               // Nombre de cellules vides


public : 
	sudoku(char filename[]);		// Lecture de la grille sudoku se trouvant dans le fichier filename
	void affichage();               // Affichage de la grille
	bool solution();                // Calcul de solution
	bool Backtracking(int );   // Fonction récursive de backtracking
    void cellule_vide();
    bool verification_l(int k,int v);
    bool verification_c(int k,int v);
    bool verification_b(int k,int v);
    
};



