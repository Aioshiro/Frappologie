#include "UserToTestMulti.h"


UserMulti::UserMulti() {
    pseudo = "";
    mdp = "realite virtuelle";
}

UserMulti::UserMulti(string pseudout) { //fct qui récupère les données d'un utilisateur lorsque l'on tape son pseudo
    ifstream file;

    file.open("usersMulti.txt", ifstream::in);
    string donnee = "";
    while (!(donnee == pseudout || donnee == '\n' + pseudout || file.peek() == EOF)) { // tant qu'on n'a pas trouvé l'user, on continue a chercher
        getline(file, donnee, ';');
    }
    if (file.peek() == EOF) {
        cout << "Erreur : Utilisateur introuvable" << endl;
    }
    this->setPseudo(pseudout); //pseudo
    while (donnee != "f") {
        getline(file, donnee, ';');
        if (donnee != "f" && donnee != "\n") { //on stocke ses données dans infos
            infos.push_back(stod(donnee));
        }
    }
    file.close();
}

vector<Uint32> StoreData(UserMulti uti) {
    SDL_Event event;
    string tapage = "";
    bool quit = false;
    vector<Uint32> temps;
    cout << "Ecrivez \"" <<uti.getMdp()<<"\" : (Dans la fenetre blanche et tapez entree quand vous avez fini)" << endl;
    SDL_FlushEvent(SDL_KEYDOWN);
    SDL_FlushEvent(SDL_KEYUP);
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.repeat == 0) {
                    if (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN) {
                        quit = true;
                        if (tapage == uti.getMdp() && temps.size() == 2 * uti.getMdp().size()) {
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
                        if (!((SDL_GetModState() & KMOD_SHIFT) || (SDL_GetModState() & KMOD_CAPS))) {
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

void LectureusersMulti(vector<Uint32> donnees) { //cherche l'utilisateur le plus probable à l'aide des données de tapage du mdp commun
    ifstream file;

    file.open("usersMulti.txt", ifstream::in);
    string donnee = "";
    UserMulti elu;
    double score1 = 42;
    double score2 = 42; //On initialise des scores hauts pour ne pas en rencontrer de semblables
    UserMulti nouv;
    double score1test=0;
    double score2test=0; //Déclaration des emplacements pour les scores testés
    int nbacceptes = 0; //C'est pour tester combien de profils sont acceptés
    while (file.peek() != EOF) {
        getline(file, donnee, ';');
        if (donnee == "\n") {
            break;
        }
        nouv.setPseudo(donnee);
        vector<double> infos;
        while (donnee != "f" && file.peek()!=EOF) {
            getline(file, donnee, ';');
            if (donnee != "f" && donnee != "\n") {
                infos.push_back(stod(donnee));
            }
        }
        nouv.setInfos(infos);
        score1test = nouv.CalculScore1(donnees);
        score2test = nouv.CalculScore2(donnees);
        if (!isnan(score2test)) {
            if (score1test < 0.002 && score2test < 0.0007) {
                nbacceptes += 1;
            }
            if (score1test < score1 && score2test < score2) {
                elu.setPseudo(nouv.getPseudo());
                elu.setInfos(nouv.getInfos());
                score1 = score1test;
                score2 = score2test;
            }
            else if (score2test < score2 && score1test < 0.002) {
                elu.setPseudo(nouv.getPseudo());
                elu.setInfos(nouv.getInfos()); //Il peut être interessant de savoir si on est dans un cas de configuration pareil
                score1 = score1test;
                score2 = score2test;
            }
        }
        else {
            if (elu.getPseudo() == "" || (score1test < 0.0002 && score1test < score1 && score1 != 42)) {
                elu.setPseudo(nouv.getPseudo());
                elu.setInfos(nouv.getInfos());
                score1 = score1test;
            }
        }
    }
    if (file.peek() == EOF && elu.getMdp()=="") {
        cout << "Erreur : pas de profil correspondant a une frappe pareille" << endl;
    }
    else {
        cout << "Le profil trouve est celui de " << elu.getPseudo() << " avec un score1 de " << score1 << " et un score2 de " << score2 << endl;
    }
    cout << "Nous avons en tout trouve " << nbacceptes << " de profils pouvant correspondre a une telle frappe suivant les criteres etablis." << endl;
    file.close();
}