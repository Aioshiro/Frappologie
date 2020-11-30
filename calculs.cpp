#include "calculs.h"

double moyenneVect(vector<double> vecteurInit) { //calcule la moyenne d'un vecteur
	int n = vecteurInit.size();
	double moy = 0;
	for (int i = 0; i < n; i++) {
		moy += vecteurInit[i];
	}
	return(moy / n);
}

double varianceVect(vector<double> vecteurInit) {//calcule la variance d'un vecteur
	int n = vecteurInit.size();
	double moy = moyenneVect(vecteurInit);
	double variance = 0;
	for (int i = 0; i < n; i++) {
		variance += (vecteurInit[i]-moy)*(vecteurInit[i] - moy);
	}
	return(variance / n);
}

double norme(vector<double> v) { //calcule la norme d'un vecteur
	double norm = 0;
	for (int i = 0; i < v.size(); i++) {
		norm += v[i] * v[i];
	}
	return sqrt(norm);
}

// calcule la decomposition de cholesky d'une matrice symetrique definie positive de taille n,la matrice étant un vecteur a n^2 entrées
vector<vector <double>> calculL(int n,vector<double> infos) { 
    vector<vector <double>> L;
    int indice = 0;
    double l = sqrt(infos[indice]);
    L.push_back({ l }); //terme en place 1,1
    indice += 1;
    for (int i = 1; i < n; i++) { //on remplit la première colonne
        L.push_back({ infos[indice] / l });
        indice += 1;
    }
    for (int i = 1; i < n; i++) { //on remplit les colonnes d'après
        for (int j = 0; j < n; j++) {
            if (j < i) {
                L[j].push_back(0); //on sait que L est triangulaire inférieure
            }
            else if (i == j) { //on applique la formule pour les termes diagonaux
                double s = 0;
                for (int k = 0; k < i; k++) {
                    s += L[i][k] * L[i][k];
                }
                l = sqrt(infos[indice] - s);
                L[i].push_back(l);
                indice += 1;
            }
            else { //on applique la formule pour les termes non diagonaux
                double s = 0;
                for (int k = 0; k < i; k++) {
                    s += L[i][k] * L[j][k];
                }
                L[j].push_back((infos[indice] - s) / l);
                indice += 1;
            }
        }
    }
    return(L);
}

// inverse une matrice triangulaire inférieure de taille n
vector<vector <double>> inversionL(vector<vector <double>> L,int n) {
    vector<vector <double>> I;
    I.resize(n);
    for (int i = 0; i < n; i++) { // on fixe la taille de la matrice
        I[i].resize(n);
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (j>i) {
                I[i][j] = 0; //la matrice finale sera triangulaire inférieure
            }
            else if (i == j) {
                I[i][j] = 1 / L[i][j]; //les termes diagonaux de L^-1 sont l'inverse de ceux de L
            }
            else {
                double s = 0; // les termes non diagonaux sont calculés avec une méthode de substitution
                for (int k = 0; k < i; k++) {
                    s -= L[i][k] * I[k][j];
                }
                I[i][j] = s / L[i][i];
            }
        }
    }
    return(I);
}

// fait le produit XM
vector<double> produitmatricevec(vector<double> X, vector<vector<double>> M) {
    int n = X.size();
    vector<double> resu(n);
    for (int i = 0; i < n; i++) {
        double s = 0;
        for (int k = 0; k < n; k++) {
            s += X[k] * M[k][i];
        }
        X[i] = s;
    }
    return X;
}

//affiche le contenu d'une matrice
void lecture(vector<vector<double>> L) {
    for (int i = 0; i < L.size(); i++) {
        for (int j = 0; j < L[i].size(); j++) {
            cout << L[i][j]<< " ; ";
        }
        cout << endl;
    }
}