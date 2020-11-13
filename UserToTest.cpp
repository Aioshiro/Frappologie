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
		getline(file, donnee, ';');
        if (donnee != "f" && donnee !="\n") {
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
    entrebis.push_back(entree[2*mdp.size() -1] - entree[0]);
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


vector<vector <double>> User::calculL() {
    int n = 2 * mdp.size();
    vector<vector <double>> L;
    int indice = n;
    double l = sqrt(infos[indice]);
    L.push_back({ l });
    indice += 1;
    for (int i = 1; i < n; i++) {
        L.push_back({ infos[indice] / l });
        indice += 1;
    }
    for (int i = 1; i < n; i++) {
        double s = 0;
        for (int k = 0; k < i; k++) {
            s += pow(L[i][k],2);
        }
        l = sqrt(abs(infos[indice] - s));
        for (int j = 0; j < n; j++) {
            if (j < i) {
                L[j].push_back(0);
            }
            else if (i == j) {
                L[i].push_back(l);
                indice += 1;
            }
            else {
                s = 0;
                for (int k = 0; k < i; k++) {
                    s += L[i][k] * L[j][k];
                }
                L[j].push_back((infos[indice] - s) / l);
                indice += 1;
            }
        }
    }
    return(L);
}

vector<vector <double>> User::Linversee() {
    vector<vector <double>> L = this->calculL();
    lecture(L);
    vector<vector <double>> I;
    int n = 2 * mdp.size();
    I.resize(n);
    for (int i = 0; i < n; i++) {
        I[i].resize(n);
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (j > i) {
                I[i][j] = 0;
            }
            else if (i == j) {
                I[i][j] = 1 / L[i][j];
            }
            else {
                double s = 0;
                for (int k = 0; k < i; k++) {
                    s -= L[i][k] * I[k][j];
                }
                I[i][j] = s / L[i][i];
            }
        }
    }
    return(I);
}

double User::CalculScore2(vector<Uint32> entree) { //calcule un score dépendant de l'écart entre l'entrée et la moyenne mais avec des variables non independantes
    vector<double> entrebis = this->transfoEntree(entree);
    vector<double> diff;
    for (int i = 0; i < entrebis.size(); i++) {
        diff.push_back(entrebis[i] - this->infos[i]);
    }
    double normesup = norme(produitmatricevec(diff, this->Linversee()));
    double normeentrebis = norme(entrebis);
    double normeinfos = norme(this->infos);
    return pow(normesup,2)/ (normeentrebis * normeinfos);
}