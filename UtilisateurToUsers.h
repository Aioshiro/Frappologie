#pragma once
#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "SDL.h"
#include "SDL_keyboard.h"
#include "UtilisateurBase.h"
using namespace std;

//permet d'enregistrer les infos de tapage brut
class Utilisateur : public UtilisateurBase{
protected:
	vector<vector<int>> TempsUt; //chaque case du vecteur est un vecteur contenant les temps d'appui et de relachement des touches du mdp
public:
	Utilisateur();
	Utilisateur(string pseudo, string mdp);

	vector<vector<int>> getTempsUt()const;
	void addTempsUt(vector<int> v); //ajoute une instance de tapage de mdp à l'utilisateur
	void setTempsUt(); //set les temps de tapage d'un utilisateur à partir des données de son fichier

	double moyenne_ij(int a, int b); // calcule la moyenne de la différence des colonnes a et b de tempsut 
	double variance_ij(int a, int b);// calcule la variance de la différence des colonnes a et b de tempsut
	double covariance_ij(int xa, int xb, int ya, int yb);// calcule la covariance entre la différence des colonnes xa et xb et la difference des colonnes ya et yb de tempsut 
	void writeToFile(); //crée ou met a jour le fichier users.txt
	void writeToFileold(); //désuet

};


Utilisateur UserConstruct(); //desuet

ostream& operator<<(ostream& os, const Utilisateur& user); //surchage << pour afficher un utilisateur

void CreerFichierUti(); //crée un nouveau fichier pseudo.txt en demandant à l'utilisateur son pseudo et son mdp

void StoreData(Utilisateur user); //enregistre une nouvelle instance de mot de passe tapé et l'inscrit dans le fichier pseudo.txt

Utilisateur LireUtilisateur(string pseudo); //genere un utilisateur avec son pseudo et son mdp à l'aide du fichier pseudo.txt
