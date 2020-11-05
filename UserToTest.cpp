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

User::User(string pseudout) {
	ifstream file;

	file.open("users.txt", ifstream::in);
	string donnee = "";
	while (!(donnee == pseudout || donnee == '\n' +pseudout || file.peek()==EOF)) {
		getline(file, donnee, ';');
	}
	if (file.peek() == EOF) {
		cout << "Erreur : Utilisateur introuvable" << endl;
	}
	this->setPseudo(pseudout); //pseudo
	getline(file, donnee, ';'); //mdp
	this->setMdp(donnee);
	while (donnee != "f") {
        cout << donnee;
		getline(file, donnee, ';');
        if (donnee != "f") {
            infos.push_back(stod(donnee));
        }
	}
    file.close();
}

vector<Uint32> StoreData(User uti) {
    SDL_Event event;
    string tapage = "";
    bool quit = false;
    vector<Uint32> temps;
    cout << "Ecrivez votre mot de passe : (Dans la fenêtre blanche et tapez entrée quand vous avez fini)" << endl;
    SDL_FlushEvent(SDL_KEYDOWN);
    SDL_FlushEvent(SDL_KEYUP);
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.repeat == 0) {
                    if (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN) {
                        quit = true;
                        if (tapage == uti.getMdp()) {
                            cout << "Mot de passe accepté" << endl;
                            for (int i = 0; i < temps.size(); i++) {
                                return (temps);
                            }

                        }
                        else {
                            cout << "Mauvais mot de passe" << endl;
                            StoreData(uti);
                        }
                        
                    }
                    else if (event.key.keysym.sym == SDLK_SPACE) {
                        tapage += " ";
                    }
                    else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                        if (tapage != "") {
                            tapage.pop_back();
                        }
                        if (!temps.empty()) {
                            temps.pop_back();
                        }
                        if (!temps.empty()) {
                            temps.pop_back();
                        }

                    }
                    else if (event.key.keysym.sym != SDLK_LSHIFT && event.key.keysym.sym != SDLK_RSHIFT) {
                        if (!(SDL_GetModState() & KMOD_SHIFT)) {
                            tapage += (char)tolower(*SDL_GetKeyName(event.key.keysym.sym));
                            temps.push_back(event.key.timestamp);
                        }
                        else {
                            tapage += SDL_GetKeyName(event.key.keysym.sym);
                            temps.push_back(event.key.timestamp);
                        }
                    }
                    cout << tapage << endl;
                }
                break;
            case SDL_KEYUP:
                if (event.key.repeat == 0) {
                    if (event.key.keysym.sym != SDLK_LSHIFT && event.key.keysym.sym != SDLK_RSHIFT && event.key.keysym.sym != SDLK_BACKSPACE && event.key.keysym.sym != SDLK_RETURN && event.key.keysym.sym != SDLK_SPACE) {
                        temps.push_back(event.key.timestamp);
                    }
                }
                break;

            default:
                break;
            }

        }
    }

}


vector<double> User::transfoEntree(vector<Uint32> entree) {
    vector<double> entrebis;
    entrebis.push_back(entree[entree.size() - 1] - entree[0]);
    for (int j = 0; j < mdp.size(); j++) {
        entrebis.push_back(entree[2 * j + 1] - entree[2 * j]);
    } // Calculs et écriture dans le fichier des temps d'appuis sur chacune des touches du mdp
    for (int j = 0; j < mdp.size() - 1; j++) {
        entrebis.push_back(entree[2 * j + 2] - entree[2 * j]);
    } // Calculs et écriture dans le fichier des temps entre un premier début d'appui et un second
    
    return(entrebis);
}

double User::CalculScore1(vector<Uint32> entree) { //calcule un score dépendant de l'écart entre l'entrée et la moyenne
    vector<double> entrebis = this->transfoEntree(entree);
    vector<double> diff;
    for (int i = 0; i < entrebis.size(); i++) {
        diff.push_back(entrebis[i] - this->infos[i]);
    }
    double normeentrebis = norme(entrebis);
    double normeinfos = norme(this->infos);
	return inner_product(diff.begin(), diff.end(), diff.begin(), 0)/(normeentrebis*normeinfos);
}
