#pragma once
#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "SDL.h"
#include "SDL_keyboard.h"
using namespace std;

class Utilisateur {
public:
	string pseudo;
	string mdp;
	vector<vector<int>> TempsUt;

	Utilisateur();
	Utilisateur(string pseudo, string mdp);
	string getPseudo()const;
	string getMdp()const;
	vector<vector<int>> getTempsUt()const;
	void setPseudo(string pseudo);
	void setMdp(string mdp);
	void setTempsUt(vector<int> v);
	void setTempsUt();

	double moyenne_ij(int a, int b);
	double variance_ij(int a, int b);
	void writeToFile();
	void writeToFilebis();

};


Utilisateur UserConstruct();

ostream& operator<<(ostream& os, const Utilisateur& user);

void CreerFichierUti();

void StoreData(Utilisateur user);

Utilisateur LireUtilisateur(string pseudo);
