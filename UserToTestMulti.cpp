#include "UserToTestMulti.h"


UserMulti::UserMulti() {
    pseudo = "";
    mdp = "realite virtuelle";
}

UserMulti::UserMulti(string pseudout) {
    ifstream file;

    file.open("usersMulti.txt", ifstream::in);
    string donnee = "";
    while (!(donnee == pseudout || donnee == '\n' + pseudout || file.peek() == EOF)) {
        getline(file, donnee, ';');
    }
    if (file.peek() == EOF) {
        cout << "Erreur : Utilisateur introuvable" << endl;
    }
    this->setPseudo(pseudout); //pseudo
    while (donnee != "f") {
        getline(file, donnee, ';');
        if (donnee != "f" && donnee != "\n") {
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