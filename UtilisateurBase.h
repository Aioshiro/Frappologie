#pragma once
#include <iostream>
using namespace std;

class UtilisateurBase
{
public:
	string pseudo;
	string mdp;

	string getPseudo()const;
	string getMdp()const;
	void setPseudo(string pseudo);
	void setMdp(string mdp);

};

