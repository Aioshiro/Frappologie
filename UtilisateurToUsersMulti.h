#pragma once
#include "UtilisateurToUsers.h"

//permet d'enregistrer les infos de tapage brut
class UtilisateurMulti : public Utilisateur {
public:

	UtilisateurMulti();
	UtilisateurMulti(string pseudo);

	void setTempsUt();
	void setTempsUt(vector<int> v);
	void writeToFile(); //crée ou met a jour le fichier users.txt

};


ostream& operator<<(ostream& os, const UtilisateurMulti& user); //affichage utilisateur pour tests

void CreerFichierUtiMulti(); //crée un nouveau fichier pseudo.txt en demandant à l'utilisateur son pseudo

void StoreData(UtilisateurMulti user); //enregistre une nouvelle instance de mot de passe tapé et l'inscrit dans le fichier pseudo.txt

UtilisateurMulti LireUtilisateurMulti(string pseudo); //genere un utilisateur avec son pseudo et son mdp à l'aide du fichier pseudo.txt
