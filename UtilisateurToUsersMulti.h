#pragma once
#include "UtilisateurToUsers.h"

//permet d'enregistrer les infos de tapage brut
class UtilisateurMulti : public Utilisateur {
public:
	UtilisateurMulti();
	UtilisateurMulti(string pseudo);

	void setTempsUt();//set les temps de tapage d'un utilisateur � partir des donn�es de son fichier
	void writeToFile(); //cr�e ou met a jour le fichier users.txt

};


ostream& operator<<(ostream& os, const UtilisateurMulti& user); //affichage utilisateur pour tests

void CreerFichierUtiMulti(); //cr�e un nouveau fichier pseudo.txt en demandant � l'utilisateur son pseudo

void StoreData(UtilisateurMulti user); //enregistre une nouvelle instance de mot de passe tap� et l'inscrit dans le fichier pseudo.txt

UtilisateurMulti LireUtilisateurMulti(string pseudo); //genere un utilisateur avec son pseudo et son mdp � l'aide du fichier pseudo.txt
