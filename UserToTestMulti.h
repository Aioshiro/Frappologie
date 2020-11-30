#pragma once
#include "UserToTest.h"

class UserMulti : public User {
public : 
	UserMulti();
	UserMulti(string pseudo); //fct qui récupère les données d'un utilisateur lorsque l'on tape son pseudo

};

vector<Uint32> StoreData(UserMulti uti); //Fct qui récupère les temps qu'une personne a mis pour taper le mdp d'un utilisateur, avant de comparer ces temps au profil

void LectureusersMulti(vector<Uint32> donnees); //cherche l'utilisateur le plus probable à l'aide des données de tapage du mdp commun
