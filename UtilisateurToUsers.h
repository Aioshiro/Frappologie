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

//permet d'enregistrer les infos de tapage brut
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

	double moyenne_ij(int a, int b); // calcule la moyenne de la diff�rence des colonnes a et b de tempsut 
	double variance_ij(int a, int b);// calcule la variance de la diff�rence des colonnes a et b de tempsut
	double covariance_ij(int xa, int xb, int ya, int yb);// calcule la covariance entre la diff�rence des colonnes xa et xb et la difference des colonnes ya et yb de tempsut 
	void writeToFile(); //cr�e ou met a jour le fichier users.txt
	void writeToFileold(); //d�suet

};


Utilisateur UserConstruct(); //desuet

ostream& operator<<(ostream& os, const Utilisateur& user); //affichage utilisateur pour tests

void CreerFichierUti(); //cr�e un nouveau fichier pseudo.txt en demandant � l'utilisateur son pseudo et son mdp

void StoreData(Utilisateur user); //enregistre une nouvelle instance de mot de passe tap� et l'inscrit dans le fichier pseudo.txt

Utilisateur LireUtilisateur(string pseudo); //genere un utilisateur avec son pseudo et son mdp � l'aide du fichier pseudo.txt
