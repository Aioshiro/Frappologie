#include "UserToTest.h"


User::User(){
	pseudo = "";
	mdp = "";
}

User::User(string pseudo, string mdp) { //crée un user avec son mdp et son mot de passe
	pseudo = pseudo;
	mdp = mdp;
}

vector<double> User::getInfos()const {
	return infos;
}

void User::setInfos(vector<double> v) {
	infos = v;
}

User::User(string pseudout) { //fct qui récupère les données d'un utilisateur lorsque l'on tape son pseudo
	ifstream file;

	file.open("users.txt", ifstream::in);
	string donnee = "";
	while (!(donnee == pseudout || donnee == '\n' +pseudout || file.peek()==EOF)) { //on cherche l'utilisateur dans le fichier
		getline(file, donnee, ';');
	}
	if (file.peek() == EOF) {
		cout << "Erreur : Utilisateur introuvable" << endl;
	}
	this->setPseudo(pseudout); //pseudo
	getline(file, donnee, ';'); //mdp
	this->setMdp(donnee);
	while (donnee != "f") { //on stocke ses infos dans infos
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
    cout << "Ecrivez votre mot de passe : (Dans la fenetre blanche et tapez entree quand vous avez fini)" << endl;
    SDL_FlushEvent(SDL_KEYDOWN);
    SDL_FlushEvent(SDL_KEYUP);
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.repeat == 0) {
                    if (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN) {
                        quit = true;
                        if (tapage == uti.getMdp()&&temps.size() == 2 * uti.getMdp().size()) {
                            cout << "Mot de passe accepte" << endl;
                            for (int i = 0; i < temps.size(); i++) {
                                return (temps);
                            }

                        }
                        else {
                            cout << "Mauvais mot de passe/donnees incorrectes" << endl;
                            StoreData(uti);
                        }
                        
                    }
                    else if (event.key.keysym.sym == SDLK_SPACE) {
                        tapage += " ";
                        temps.push_back(event.key.timestamp);
                    }
                    else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                        tapage = "";
                        temps.clear();

                    }
                    else if (event.key.keysym.sym != SDLK_LSHIFT && event.key.keysym.sym != SDLK_RSHIFT && event.key.keysym.sym != SDLK_CAPSLOCK) {
                        if (!((SDL_GetModState() & KMOD_SHIFT)|| (SDL_GetModState() & KMOD_CAPS))) {
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
                    if (event.key.keysym.sym != SDLK_LSHIFT && event.key.keysym.sym != SDLK_RSHIFT && event.key.keysym.sym != SDLK_BACKSPACE && event.key.keysym.sym != SDLK_RETURN && event.key.keysym.sym != SDLK_CAPSLOCK) {
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


vector<double> User::transfoEntree(vector<Uint32> entree) { //fct qui à partir de temps de frappe donne les valeurs à comparer pour les moyennes qu'on a choisi
    vector<double> entrebis;
    entrebis.push_back(entree[2*mdp.size() -1] - entree[0]);
    for (int j = 0; j < mdp.size(); j++) {
        entrebis.push_back(entree[2 * j + 1] - entree[2 * j]);
    } // Calculs et ajout dans le vecteur des temps d'appuis sur chacune des touches du mdp
    for (int j = 0; j < mdp.size() - 1; j++) {
        entrebis.push_back(entree[2 * j + 2] - entree[2 * j]);
    } // Calculs et ajout dans le vecteur des temps entre un premier début d'appui et un second
    
    return(entrebis);
}

double User::CalculScore1(vector<Uint32> entree) { //fct qui calcul le score de compatibilité entre une personne et l'utilisateur qu'il prétend être en supposant des variables indépendantes
    //si X est l'entrée, et M la moyenne, on renvoie ||X-M||^2/(||X||.||M||)
    vector<double> entrebis = this->transfoEntree(entree);
    vector<double> diff;
    for (int i = 0; i < entrebis.size(); i++) {
        diff.push_back(entrebis[i] - this->infos[i]);
    }
    double normeentrebis = norme(entrebis);
    double normeinfos = norme(this->infos);
	return inner_product(diff.begin(), diff.end(), diff.begin(), 0)/(normeentrebis*normeinfos);
}


vector<vector <double>> User::calculL() { //calcul de la décomposition de cholesky de la matrice de covariance
    int n = 2 * mdp.size();
    vector<vector <double>> L;
    int indice = n;
    double l = sqrt(infos[indice]);
    L.push_back({ l }); //terme en place 1,1
    indice += 1;
    for (int i = 1; i < n; i++) { //on remplit la première colonne
        L.push_back({ infos[indice] / l });
        indice += 1;
    }
    for (int i = 1; i < n; i++) { //on remplit les colonnes d'après
        double s = 0;
        for (int k = 0; k < i; k++) { 
            s += pow(L[i][k],2);
        }
        l = sqrt(infos[indice] - s); // si la matrice n'est pas symétrique définie positive, c'est ici qu'on a un problème
        for (int j = 0; j < n; j++) {
            if (j < i) {
                L[j].push_back(0); //on sait que L est triangulaire inférieure
            }
            else if (i == j) { //on applique la formule pour les termes diagonaux
                L[i].push_back(l);
                indice += 1;
            } 
            else { //on applique la formule pour les termes non diagonaux
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

vector<vector <double>> User::Linversee() {// inverse une matrice triangulaire inférieure de taille n
    vector<vector <double>> L = this->calculL();
    vector<vector <double>> I;
    int n = 2 * mdp.size();
    I.resize(n);
    for (int i = 0; i < n; i++) {
        I[i].resize(n); // on fixe la taille de la matrice
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (j > i) {
                I[i][j] = 0; //la matrice finale sera triangulaire inférieure
            }
            else if (i == j) {
                I[i][j] = 1 / L[i][j]; //les termes diagonaux de L^-1 sont l'inverse de ceux de L
            }
            else {
                double s = 0; // les termes non diagonaux sont calculés avec une méthode de substitution
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
     //si X est l'entrée, et M la moyenne et E la matrice de covariance, on renvoie (X-M)^T*E^-1*(X-M)/(||X||.||M||)
    vector<double> entrebis = this->transfoEntree(entree);
    vector<double> diff;
    for (int i = 0; i < entrebis.size(); i++) {
        diff.push_back(entrebis[i] - this->infos[i]);
    }
    double normesup = norme(produitmatricevec(diff, this->Linversee()));
    if (isnan(normesup)) { //l'algo de calcul de L a bugué car la matrice de base n'etait pas symétrique définie positive
        cout << "Calcul de score 2 impossible, matrice non inversible" << endl;
        return normesup;
    }
    double normeentrebis = norme(entrebis);
    double normeinfos = norme(this->infos);
    return pow(normesup,2)/ (normeentrebis * normeinfos);
}