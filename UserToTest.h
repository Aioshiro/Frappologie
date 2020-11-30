#pragma once
#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include "SDL.h"
#include "SDL_keyboard.h"
#include "calculs.h"
#include "UtilisateurBase.h"
using namespace std;


class User : public UtilisateurBase {
protected:
	vector<double> infos; // vecteur des moyennes d'un utilisateur de la base
public:
	User();
	User(string pseudo); //fct qui r�cup�re les donn�es d'un utilisateur lorsque l'on tape son pseudo
	User(string pseudo, string mdp); //cr�e un user avec son mdp et son mot de passe

	vector<double> getInfos()const;
	void setInfos(vector<double> v);

	vector<double> transfoEntree(vector<Uint32> entree); //fct qui � partir de temps de frappe donne les valeurs � comparer pour les moyennes qu'on a choisi
	vector<vector <double>> calculL(); //calcul de la d�composition de cholesky de la matrice de covariance
	vector<vector <double>> Linversee();
	double CalculScore1(vector<Uint32> entree); //fct qui calcul le score de compatibilit� entre une personne et l'utilisateur qu'il pr�tend �tre en supposant des variables ind�pendantes
	double CalculScore2(vector<Uint32> entree); //fct qui calcul le score de compatibilit� entre une personne et l'utilisateur qu'il pr�tend �tre mais avec des variables non independantes

};

vector<Uint32> StoreData(User uti); //Fct qui r�cup�re les temps qu'une personne a mis pour taper le mdp d'un utilisateur, avant de comparer ces temps au profil