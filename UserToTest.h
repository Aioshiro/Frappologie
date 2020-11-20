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
public:
	vector<double> infos; // vecteur des moyennes d'un utilisateur de la base

	User();
	User(string pseudo); //fct qui récupère les données d'un utilisateur lorsque l'on tape son pseudo
	User(string pseudo, string mdp);

	vector<double> getInfos()const;
	void setInfos(vector<double> v);

	vector<double> transfoEntree(vector<Uint32> entree); //fct qui à partir de temps de frappe donne les valeurs à comparer pour les moyennes qu'on a choisi
	vector<vector <double>> calculL();
	vector<vector <double>> Linversee();
	double CalculScore1(vector<Uint32> entree); //fct qui calcul le score de compatibilité entre une personne et l'utilisateur qu'il prétend être
	double CalculScore2(vector<Uint32> entree); //fct qui calcul le score de compatibilité entre une personne et l'utilisateur qu'il prétend être mais avec des variables non independantes

};

vector<Uint32> StoreData(User uti); //Fct qui récupère les temps qu'une personne a mis pour taper le mdp d'un utilisateur, avant de comparer ces temps au profil