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
using namespace std;


class User {
public:
	string pseudo;
	string mdp;
	vector<double> infos; // vecteur des moyennes et variance d'un utilisateur de la base

	User();
	User(string pseudo); //fct qui r�cup�re les donn�es d'un utilisateur lorsque l'on tape son pseudo
	User(string pseudo, string mdp);
	string getPseudo()const;
	string getMdp()const;
	vector<double> getInfos()const;
	void setPseudo(string pseudo);
	void setMdp(string mdp);
	void setInfos(vector<double> v);

	vector<double> transfoEntree(vector<Uint32> entree); //fct qui � partir de temps de frappe donne les valeurs � comparer pour les moyennes qu'on a choisi
	double CalculScore1(vector<Uint32> entree); //fct qui calcul le score de compatibilit� entre une personne et l'utilisateur qu'il pr�tend �tre

};

vector<Uint32> StoreData(User uti); //Fct qui r�cup�re les temps qu'une personne a mis pour taper le mdp d'un utilisateur, avant de comparer ces temps au profil

//Pour seconde partie
//typedef vector<User> userList;

//userList CreerListe();
