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


class User {
public:
	string pseudo;
	string mdp;
	vector<double> infos;

	User();
	User(string pseudo);
	User(string pseudo, string mdp);
	string getPseudo()const;
	string getMdp()const;
	vector<double> getInfos()const;
	void setPseudo(string pseudo);
	void setMdp(string mdp);
	void setInfos(vector<double> v);

	float CalculScore1(vector<double> entree);

};


//Pour seconde partie
//typedef vector<User> userList;

//userList CreerListe();
