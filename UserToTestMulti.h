#pragma once
#include "UserToTest.h"

class UserMulti : public User {
public : 
	UserMulti();
	UserMulti(string pseudo); //fct qui r�cup�re les donn�es d'un utilisateur lorsque l'on tape son pseudo

};

vector<Uint32> StoreData(UserMulti uti); //Fct qui r�cup�re les temps qu'une personne a mis pour taper le mdp d'un utilisateur, avant de comparer ces temps au profil
