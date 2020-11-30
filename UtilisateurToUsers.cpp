#include "UtilisateurToUsers.h"

Utilisateur::Utilisateur() {
	pseudo = "";
	mdp = "";
}
Utilisateur::Utilisateur(string pseudo, string mdp) {
	this->pseudo = pseudo;
	this->mdp = mdp;
}
vector<vector<int>> Utilisateur::getTempsUt()const {
	return TempsUt;
}
void Utilisateur::addTempsUt(vector<int> v) { //ajoute une instance de tapage de mdp à l'utilisateur
	TempsUt.push_back(v);
}
void Utilisateur::setTempsUt(){ //set les temps de tapage d'un utilisateur à partir des données de son fichier
    ifstream file;
    file.open(pseudo + ".txt", ifstream::in);
    string donnee = "";
    getline(file, donnee, ';'); //pseudo
    getline(file, donnee, ';'); //mdp
    donnee = "";
    vector<int> tempstappage;
    while (file.peek() != EOF) { // tant qu'on n'a pas fini de lire le fichier
        while (donnee != "f" && donnee != "\n") { //tant qu'on est pas à la fin de la ligne, ie de l'instance de mdp tapé
            getline(file, donnee, ';');
            if (donnee != "f" && donnee != "\n") {
                tempstappage.push_back(stoi(donnee)); //on stocke les temps de tapage dans un vecteur
            }
        }
        if (!tempstappage.empty()) { //si on a bien des données à mettre
            this->addTempsUt(tempstappage); //on les rajoute dans l'utilisateur
            tempstappage.clear();
        }
        donnee = "";
    }
    file.close();
}

double Utilisateur::moyenne_ij(int a, int b) {// calcule la moyenne de la différence des colonnes a et b de tempsut
	double moy = 0;
	int n = TempsUt.size();
	for (int i = 0; i <n; i++) {
		moy += abs(TempsUt[i][a]-TempsUt[i][b]);
	}
	return(moy / n);
}

double Utilisateur::variance_ij(int a, int b) {// calcule la variance de la différence des colonnes a et b de tempsut 
    double moy = moyenne_ij(a,b);
    int n = TempsUt.size();
    double variance = 0;
    for (int i = 0; i < n; i++) {
        variance += (abs(TempsUt[i][a] - TempsUt[i][b])-moy)* (abs(TempsUt[i][a] - TempsUt[i][b]) - moy);
    }
    return(variance / n);
}

double Utilisateur::covariance_ij(int xa, int xb,int ya ,int yb) {// calcule la covariance entre la différence des colonnes xa et xb et la difference des colonnes ya et yb de tempsut 
    double moyx = moyenne_ij(xa, xb);
    double moyy = moyenne_ij(ya, yb);
    int n = TempsUt.size();
    double covariance = 0;
    for (int i = 0; i < n; i++) {
        covariance += (abs(TempsUt[i][xa] - TempsUt[i][xb]) - moyx) * (abs(TempsUt[i][ya] - TempsUt[i][yb]) - moyy);
    }
    return(covariance / n);
}

void Utilisateur::writeToFileold() { // désuet
	ofstream fs;
	fs.open("users.txt", ofstream::out | ofstream::app);
    //std::cout << (TempsUt[0]).size() - 1 << endl;
	fs << this->moyenne_ij(0, (TempsUt[0]).size()-1) << ';';
	for (int i = 0; i < TempsUt.size()-1; i++) {
		for (int j = 0; j < mdp.size()-2; i++) {
		    fs << this->moyenne_ij(TempsUt[i][2*j], TempsUt[i][2*j+1]) << ';';
		} // Calculs et écriture dans le fichier des temps d'appuis sur chacune des touches du mdp
		for (int j = 0; j < mdp.size() - 3; i++) {
		    fs << this->moyenne_ij(TempsUt[i][2 * j], TempsUt[i][2*j + 2]) << ';';
		} // Calculs et écriture dans le fichier des temps entre un premier début d'appui et un second
	}
	fs << "f;" << endl;
	fs.close();
}

void Utilisateur::writeToFile() { //crée ou met a jour le fichier users.txt
    fstream fs1;
    fstream fs2;
    fs1.open("users.txt", ifstream::in);
    fs2.open("temp.txt", ofstream::out);
    string donnee = "";
    bool premieruti = true;
    while (fs1.peek() != EOF) { //on recopie users.txt dans un fichier temporaire à l'exception de utilisateur à ajouter/modifier
        getline(fs1, donnee, ';');
        if (donnee == pseudo || donnee == "\n" + pseudo) {
            
            while (donnee != "f") {
                getline(fs1, donnee, ';');
            }
            getline(fs1, donnee, ';');
        }
        if (donnee != "\n") {
            if (premieruti) {
                premieruti = false;
                if (donnee[0] == '\n') {
                    donnee = donnee.substr(1, donnee.size() - 1);
                }
            }
            fs2 << donnee<< ';';
        }
    }
    fs2 << endl;
    fs1.close();
    fs2.close();
    
    fs1.open("users.txt", ofstream::out);
    fs2.open("temp.txt", ifstream::in);
    donnee = "";
    bool fichiernonvide = false;
    while (fs2.peek() != EOF) { //on recopie temp.txt dans users.txt
        
        getline(fs2, donnee, ';');
        if (donnee != "\n") {
            fichiernonvide = true;
            fs1 << donnee << ';';
        }
    }
    if (fichiernonvide) {
        fs1 << endl;
    }
    
    fs2.close();
    std::remove("temp.txt"); 
    fs1 << pseudo << ';' << mdp << ';'; //on recopie l'utilisateur à ajouter / mettre à jour
    fs1 << this->moyenne_ij(0, TempsUt[0].size() - 1) << ';';

    for (int j = 0; j < mdp.size(); j++) {
        fs1 << this->moyenne_ij(2 * j, 2 * j + 1) << ';';
    } // Calculs et écriture dans le fichier des moyennes de temps d'appuis sur chacune des touches du mdp
    for (int j = 0; j < mdp.size() - 1; j++) {
        fs1 << this->moyenne_ij(2 * j, 2 * j + 2) << ';';
    } // Calculs et écriture dans le fichier des moyennes temps entre un premier début d'appui et un second
    //Calcul de la partie supérieur de la matrice de covariance
    fs1 << this->variance_ij(0, TempsUt[0].size() - 1) << ';';
    for (int i = 0; i < mdp.size(); i++) {
        fs1 << this->covariance_ij(0, TempsUt[0].size() - 1, 2 * i, 2 * i + 1) << ';'; //Covariance entre le temps total et les temps d'appuis
    }
    for (int i = 0; i < mdp.size()-1; i++) {
        fs1 << this->covariance_ij(0, TempsUt[0].size() - 1, 2 * i, 2 * i + 2) << ';'; //Covariance entre le temps total et le temps entre deux appuis
    }
    for (int i = 0; i < mdp.size() ; i++) {
        fs1 <<  this->variance_ij(2 * i, 2 * i + 1) << ';'; //variance d'un temps d'appui
        for (int j = i + 1; j < mdp.size(); j++) {
            fs1 << this->covariance_ij(2*j, 2*j+1, 2 * i, 2 * i + 1) << ';'; //Covariance entre les temps d'appuis
        }
        for (int j = 0; j < mdp.size()-1; j++) {
            fs1 << this->covariance_ij(2 * j, 2 * j + 2, 2 * i, 2 * i + 1) << ';'; //Covariance entre les temps d'appuis et les temps entre appui
        }
    }
    for (int i = 0; i < mdp.size()-1; i++) {
        fs1 << this->variance_ij(2 * i, 2 * i + 2) << ';'; //variance des temps entres appui
        for (int j = i + 1; j < mdp.size() - 1; j++) {
            fs1 << this->covariance_ij(2 * j, 2 * j + 2, 2 * i, 2 * i + 2) << ';'; //covariance entre les temps entre appui
        }
    }
    fs1 << "f;" << endl;
    fs1.close();
}


Utilisateur UserConstruct() //inutilisé
{
	ifstream file;
	file.open("utilisateurA.txt", ifstream::in);
	string donnee = "";
	Utilisateur uti;
	getline(file, donnee, ';');
	uti.setPseudo(donnee);
	getline(file, donnee, ';');
	uti.setMdp(donnee);
	while (file.peek() != EOF) {
		vector<int> tempstappage;
		while (donnee != "f") {
			getline(file, donnee, ';');
			if (donnee != "f") {
				tempstappage.push_back(stod(donnee));
			}
		}
		uti.addTempsUt(tempstappage);
	}
	file.close();
	return uti;
}

ostream& operator<<(ostream& os, const Utilisateur& user) {//set les temps de tapage d'un utilisateur à partir des données de son fichier
	os << "Pseudo :" << user.getPseudo() << "Mdp :" << user.getMdp() << endl;
	return os;
}

void CreerFichierUti() { //crée un nouveau fichier pseudo.txt en demandant à l'utilisateur son pseudo et son mdp
    Utilisateur uti;
    string tapage = "";
    std::cout << "Entrez pseudo" << endl;
    cin >> tapage;
    uti.setPseudo(tapage);
    tapage = "";
    cout << "Entrez mot de passe" << endl;
    cin >> tapage;
    uti.setMdp(tapage);
    ofstream file;
    file.open(uti.getPseudo() + ".txt", std::fstream::out | std::fstream::app);
    file << uti.getPseudo() << ";" << uti.getMdp() << ";" << endl;
    file.close();
}


void StoreData(Utilisateur user) { //enregistre une nouvelle instance de mot de passe tapé et l'inscrit dans le fichier pseudo.txt
    SDL_Event event;
    string tapage = "";
    bool quit = false;
    ofstream file;
    vector<Uint32> temps;
    file.open(user.getPseudo() + ".txt", std::fstream::out | std::fstream::app);
    cout << "Ecrivez votre mot de passe : (Dans la fenetre blanche et tapez entree quand vous avez fini)" << endl;
    SDL_FlushEvent(SDL_KEYDOWN); //on nettoie d'eventuels evenements survenus avant le tapage du mdp
    SDL_FlushEvent(SDL_KEYUP);
    while (!quit) {
        while (SDL_PollEvent(&event)) { //des qu'on a un event
            switch (event.type) {
            case SDL_KEYDOWN: //quand une touche est appuyée
                if (event.key.repeat == 0) { //si ce n'est pas une touche qui est restée appuyée
                    if (event.key.keysym.sym == SDLK_KP_ENTER|| event.key.keysym.sym == SDLK_RETURN) { //l'utilisateur valide le mdp
                        quit = true;
                        if (tapage == user.getMdp()&& temps.size() == 2 * user.getMdp().size()) {
                            cout << "Mot de passe accepte" << endl;
                            for (int i = 0; i < temps.size(); i++) {
                                file << temps[i] << ';';
                            }
                            file << "f;" << endl;
                            file.close();
                        }
                        else {
                            file.close();
                            cout << "Mauvais mot de passe / erreur de donnees" << endl;
                            StoreData(user); //on lui fait retaper
                        }
                    }
                    else if (event.key.keysym.sym == SDLK_SPACE) {
                        tapage += " ";
                        temps.push_back(event.key.timestamp);
                    }
                    else if (event.key.keysym.sym == SDLK_BACKSPACE) { //on enleve la derniere lettre et les deux derniers temps
                        tapage = "";
                        temps.clear();

                    }
                    else if (event.key.keysym.sym != SDLK_LSHIFT && event.key.keysym.sym != SDLK_RSHIFT && event.key.keysym.sym != SDLK_CAPSLOCK) {
                        if (!((SDL_GetModState() & KMOD_SHIFT) || (SDL_GetModState() & KMOD_CAPS))) { //si on appuie sur une lettre minuscule, on l'ajoute ainsi que le temps
                            tapage += (char)tolower(*SDL_GetKeyName(event.key.keysym.sym));
                            temps.push_back(event.key.timestamp);
                        }
                        else {
                            tapage += SDL_GetKeyName(event.key.keysym.sym); //sinon on ajoute la minuscule
                            temps.push_back(event.key.timestamp);
                        }
                    }
                    cout << tapage << endl; //on affiche l'état de la chaine de caractère
                }
                break;
            case SDL_KEYUP: //quand on relache une touche
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

Utilisateur LireUtilisateur(string pseudo) { //genere un utilisateur avec son pseudo et son mdp à l'aide du fichier pseudo.txt
	Utilisateur uti;
	ifstream file;
	file.open(pseudo + ".txt", ifstream::in);
	string donnee = "";
    getline(file, donnee, ';');
	uti.setPseudo(donnee);
	getline(file, donnee, ';');
    uti.setMdp(donnee);
	file.close();
	return uti;
}

