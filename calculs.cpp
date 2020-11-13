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

double CalcScore(vector<double> vecteurInit, double valeur) { 
	double moy = moyenneVect(vecteurInit);
	double variance = varianceVect(vecteurInit);
	return(1/(sqrt(2*3.14159 * variance))*exp(-1/(2*variance)*(valeur-moy)* (valeur - moy)));
}
double norme(vector<double> v) {
	double norm = 0;
	for (int i = 0; i < v.size(); i++) {
		norm += v[i] * v[i];
	}
	return sqrt(norm);
}

vector<vector <double>> calculL(int n,vector<double> infos) {
    vector<vector <double>> L;
    int indice = 0;
    double l = sqrt(infos[indice]);
    L.push_back({ l });
    indice += 1;
    for (int i = 1; i < n; i++) {
        L.push_back({ infos[indice] / l });
        indice += 1;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j < i) {
                L[j].push_back(0);
            }
            else if (i == j) {
                double s = 0;
                for (int k = 0; k < i; k++) {
                    s += L[i][k] * L[i][k];
                }
                l = sqrt(infos[indice] - s);
                L[i].push_back(l);
                indice += 1;
            }
            else {
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

vector<vector <double>> inversionL(vector<vector <double>> L,int n) {
    vector<vector <double>> I;
    I.resize(n);
    for (int i = 0; i < n; i++) {
        I[i].resize(n);
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (j>i) {
                I[i][j] = 0;
            }
            else if (i == j) {
                I[i][j] = 1 / L[i][j];
            }
            else {
                double s = 0;
                for (int k = 0; k < i; k++) {
                    s -= L[i][k] * I[k][j];
                }
                I[i][j] = s / L[i][i];
            }
        }
    }
    return(I);
}

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

void lecture(vector<vector<double>> L) {
    for (int i = 0; i < L.size(); i++) {
        for (int j = 0; j < L[i].size(); j++) {
            cout << L[i][j]<< " ; ";
        }
        cout << endl;
    }
}

