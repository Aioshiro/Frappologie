#pragma once
#include <iostream>
using namespace std;

class UtilisateurBase
{
protected:
	string pseudo;
	string mdp;
public:
	string getPseudo()const;
	string getMdp()const;
	void setPseudo(string pseudo);
	void setMdp(string mdp);

};

