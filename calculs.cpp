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