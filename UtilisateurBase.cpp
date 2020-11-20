#include "UtilisateurBase.h"

string UtilisateurBase::getPseudo()const {
	return pseudo;
}
string UtilisateurBase::getMdp()const {
	return mdp;
}

void UtilisateurBase::setPseudo(string pseudo) {
	this->pseudo = pseudo;
}
void UtilisateurBase::setMdp(string mdp) {
	this->mdp = mdp;
}