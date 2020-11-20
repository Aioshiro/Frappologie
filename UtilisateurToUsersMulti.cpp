#include "UtilisateurToUsersMulti.h"

UtilisateurMulti::UtilisateurMulti() {
    pseudo = "";
    mdp = "realite virtuelle";
}
UtilisateurMulti::UtilisateurMulti(string pseudo) {
    this->pseudo = pseudo;
    mdp = "realite virtuelle";
}
void UtilisateurMulti::setTempsUt(vector<int> v) {
    TempsUt.push_back(v);
}

void UtilisateurMulti::setTempsUt() {
    ifstream file;
    file.open(pseudo + "Multi.txt", ifstream::in);
    string donnee = "";
    getline(file, donnee, ';'); //pseudo
    donnee = "";
    vector<int> tempstappage;
    while (file.peek() != EOF) {
        while (donnee != "f" && donnee != "\n") {
            getline(file, donnee, ';');
            if (donnee != "f" && donnee != "\n") {
                tempstappage.push_back(stoi(donnee));
            }
        }
        if (!tempstappage.empty()) {
            this->setTempsUt(tempstappage);
            tempstappage.clear();
        }
        donnee = "";
    }
    file.close();
}


void UtilisateurMulti::writeToFile() { //crée ou met a jour le fichier usersMulti.txt
    fstream fs1;
    fstream fs2;
    fs1.open("usersMulti.txt", ifstream::in);
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
            fs2 << donnee << ';';
        }
    }
    fs2 << endl;
    fs1.close();
    fs2.close();

    fs1.open("usersMulti.txt", ofstream::out);
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
    fs1 << pseudo << ';'; //on recopie l'utilisateur à ajouter / mettre à jour
    fs1 << this->moyenne_ij(0, TempsUt[0].size() - 1) << ';';

    for (int j = 0; j < mdp.size(); j++) {
        fs1 << this->moyenne_ij(2 * j, 2 * j + 1) << ';';
    } // Calculs et écriture dans le fichier des moyennes de temps d'appuis sur chacune des touches du mdp
    for (int j = 0; j < mdp.size() - 1; j++) {
        fs1 << this->moyenne_ij(2 * j, 2 * j + 2) << ';';
    } // Calculs et écriture dans le fichier des moyennes temps entre un premier début d'appui et un second
    /*Calcul de la partie supérieur de la matrice de covariance*/
    fs1 << this->variance_ij(0, TempsUt[0].size() - 1) << ';';
    for (int i = 0; i < mdp.size(); i++) {
        fs1 << this->covariance_ij(0, TempsUt[0].size() - 1, 2 * i, 2 * i + 1) << ';'; //Covariance entre le temps total et les temps d'appuis
    }
    for (int i = 0; i < mdp.size() - 1; i++) {
        fs1 << this->covariance_ij(0, TempsUt[0].size() - 1, 2 * i, 2 * i + 2) << ';'; //Covariance entre le temps total et le temps entre deux appuis
    }
    for (int i = 0; i < mdp.size(); i++) {
        fs1 << this->variance_ij(2 * i, 2 * i + 1) << ';'; //variance d'un temps d'appui
        for (int j = i + 1; j < mdp.size(); j++) {
            fs1 << this->covariance_ij(2 * j, 2 * j + 1, 2 * i, 2 * i + 1) << ';'; //Covariance entre les temps d'appuis
        }
        for (int j = 0; j < mdp.size() - 1; j++) {
            fs1 << this->covariance_ij(2 * j, 2 * j + 2, 2 * i, 2 * i + 1) << ';'; //Covariance entre les temps d'appuis et les temps entre appui
        }
    }
    for (int i = 0; i < mdp.size() - 1; i++) {
        fs1 << this->variance_ij(2 * i, 2 * i + 2) << ';'; //variance des temps entres appui
        for (int j = i + 1; j < mdp.size() - 1; j++) {
            fs1 << this->covariance_ij(2 * j, 2 * j + 2, 2 * i, 2 * i + 2) << ';'; //covariance entre les temps entre appui
        }
    }
    fs1 << "f;" << endl;
    fs1.close();
}



ostream& operator<<(ostream& os, const UtilisateurMulti& user) {
    os << "Pseudo :" << user.getPseudo() << "Mdp :" << user.getMdp() << endl;
    return os;
}

void CreerFichierUtiMulti() {
    UtilisateurMulti uti;
    string tapage = "";
    std::cout << "Entrez pseudo" << endl;
    cin >> tapage;
    uti.setPseudo(tapage);
    ofstream file;
    file.open(uti.getPseudo() + "Multi.txt", std::fstream::out | std::fstream::app);
    file << uti.getPseudo() << ";" << endl;
    file.close();
}


void StoreData(UtilisateurMulti user) { //enregistre une nouvelle instance de mot de passe tapé et l'inscrit dans le fichier pseudoMulti.txt
    SDL_Event event;
    string tapage = "";
    bool quit = false;
    ofstream file;
    vector<Uint32> temps;
    file.open(user.getPseudo() + "Multi.txt", std::fstream::out | std::fstream::app);
    cout << "Ecrivez \""<< user.getMdp()<<"\" : (Dans la fenetre blanche et tapez entree quand vous avez fini)" << endl;
    SDL_FlushEvent(SDL_KEYDOWN); //on nettoie d'eventuels evenements survenus avant le tapage du mdp
    SDL_FlushEvent(SDL_KEYUP);
    while (!quit) {
        while (SDL_PollEvent(&event)) { //des qu'on a un event
            switch (event.type) {
            case SDL_KEYDOWN: //quand une touche est appuyée
                if (event.key.repeat == 0) { //si ce n'est pas une touche qui est restée appuyée
                    if (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN) { //l'utilisateur valide le mdp
                        quit = true;
                        if (tapage == user.getMdp() && temps.size() == 2 * user.getMdp().size()) {
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
                    else if (event.key.keysym.sym != SDLK_LSHIFT && event.key.keysym.sym != SDLK_RSHIFT) {
                        if (!(SDL_GetModState() & KMOD_SHIFT)) { //si on appuie sur une lettre minuscule, on l'ajoute ainsi que le temps
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
                    if (event.key.keysym.sym != SDLK_LSHIFT && event.key.keysym.sym != SDLK_RSHIFT && event.key.keysym.sym != SDLK_BACKSPACE && event.key.keysym.sym != SDLK_RETURN) {
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

UtilisateurMulti LireUtilisateurMulti(string pseudo) { //genere un utilisateur avec son pseudo à l'aide du fichier pseudo.txt
    UtilisateurMulti uti;
    ifstream file;
    file.open(pseudo + "Multi.txt", ifstream::in);
    string donnee = "";
    getline(file, donnee, ';');
    uti.setPseudo(donnee);
    file.close();
    return uti;
}

