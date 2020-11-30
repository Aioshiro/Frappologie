#include "SDL.h"
#include "SDL_keyboard.h"
#include "UtilisateurBase.h"
#include "UtilisateurToUsers.h"
#include "UtilisateurToUsersMulti.h"
#include "UserToTest.h"
#include "UserToTestMulti.h"
#include "calculs.h"
#include <iostream>
#include <stdio.h>
using namespace std;

/* main */
int main(int argc, char* argv[]) {

    //initialisations de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << stderr << "Could not initialise SDL: %s" << SDL_GetError();
        return (-1);
    }
    if (!SDL_CreateWindow("Ma fenêtre de jeu",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)) {
        cout << stderr << "Could not set video mode: %s" << SDL_GetError();
        SDL_Quit();
        return (-1);
    }

    bool quit = false;
    while (!quit) {
        cout << "Actions possibles :" << endl;
        cout << "1 - Voulez-vous creer un nouvel utilisateur ?" << endl;
        cout << "2 - Voulez-vous creer un nouvel utilisateur (multi) ?" << endl;
        cout << "3 - Voulez-vous entrer de nouvelles donnees de votre fichier ?" << endl;
        cout << "4 - Voulez-vous entrer de nouvelles donnees de votre fichier ? (multi)" << endl;
        cout << "5 - Souhaitez vous vous connecter ? (un seul utilisateur)" << endl;
        cout << "6 - Souhaitez vous vous connecter ? (multi utilisateur)" << endl;
        cout << "7 - Quitter l'application" << endl;
        int rep = 0;
        cin >> rep;
        switch (rep) {
        case 1: {
            CreerFichierUti();
            break;
        }
        case 2: {
            CreerFichierUtiMulti();
            break;
        }
        case 3: {
            cout << "Veuillez vous identifier (ecrire le nom d'utilisateur) " << endl;
            string reponse = "";
            cin >> reponse;
            Utilisateur uti1 = LireUtilisateur(reponse); //Ajouter une exception pour si l'utilisateur n'existe pas
            do {
                StoreData(uti1);
                cout << "Voulez-vous entrer d'autres donnees dans votre fichier ? (y/n)" << endl;
                cin >> reponse;
            } while (reponse == "y");
            uti1.setTempsUt();
            uti1.writeToFile();
            break; }
        case 4: {
            cout << "Veuillez vous identifier (ecrire le nom d'utilisateur) " << endl;
            string reponse = "";
            cin >> reponse;
            UtilisateurMulti uti1 = LireUtilisateurMulti(reponse); //Ajouter une exception pour si l'utilisateur n'existe pas
            do {
                StoreData(uti1);
                cout << "Voulez-vous entrer d'autres donnees dans votre fichier ? (y/n)" << endl;
                cin >> reponse;
            } while (reponse == "y");
            uti1.setTempsUt();
            uti1.writeToFile();
            break;
        }
        case 5: {
            cout << "Tapez votre identifiant" << endl;
            string reponse = "";
            cin >> reponse;
            User nouv(reponse);
            reponse = "";
            do {
                vector<Uint32> donnees = StoreData(nouv);
                double score1 = nouv.CalculScore1(donnees);
                double score2 = nouv.CalculScore2(donnees);
                cout << "Votre score est de " << score1 << endl;
                cout << "Votre score est de " << score2 << endl;
                if (score1 < 0.0002 && score2 < 0.00007) { //les seuils fixés sont peut etre à modifier
                    cout << "Accepte" << endl;
                }
                else {
                    cout << "Refuse" << endl;
                }
                cout << "Souhaitez vous continuer ? (y/n)" << endl;
                cin >> reponse;
            } while (reponse == "y");
            break; }
        case 6: {
            UserMulti nouv;
            string reponse = "";
            do {
                vector<Uint32> donnees = StoreData(nouv);
                LectureusersMulti(donnees);
                cout << "Souhaitez vous continuer ? (y/n)" << endl;
                cin >> reponse;
            } while (reponse == "y");
            break;
        }
        case 7:
            quit = true;
            break;
        default:
            cout << "Numero incorrect, reessayez" << endl;
            break;
        }

    }
    SDL_Quit();
    return 0;
}