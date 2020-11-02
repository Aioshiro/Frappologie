#include "UserToTest.h"


User::User(){
	pseudo = "";
	mdp = "";
}

User::User(string pseudo, string mdp) {
	pseudo = pseudo;
	mdp = mdp;
}

string User::getPseudo()const {
	return pseudo;
}

string User::getMdp()const {
	return mdp;
}

vector<double> User::getInfos()const {
	return infos;
}

void User::setPseudo(string pseudo) {
	this->pseudo = pseudo;
}

void User::setMdp(string mdp) {
	this->mdp = mdp;
}

void User::setInfos(vector<double> v) {
	infos = v;
}

User::User(string pseudo) {
	ifstream file;

	file.open("users.txt", ifstream::in);
	string donnee = "";
	while (donnee != pseudo || file.peek()==EOF) {
		getline(file, donnee, ';');
	}
	if (file.peek() == EOF) {
		cout << "Erreur : Utilisateur introuvable" << endl;
	}
	this->setPseudo(pseudo); //pseudo
	getline(file, donnee, ';'); //mdp
	this->setMdp(donnee);
	while (donnee != "f") {
		getline(file, donnee, ';');
		infos.push_back(stod (donnee));
	}

}


float User::CalculScore1(vector<double> entree) {
	//regarder comment faire les maths
	return(0);
}
