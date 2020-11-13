#include "SDL.h"
#include "SDL_keyboard.h"
#include "UtilisateurToUsers.h"
#include "UserToTest.h"
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
    string rep = "";
    cout << "Voulez-vous creer un nouvel utilisateur ? Repondre par 'oui' ou 'non' " << endl;
    cin >> rep;
    if (rep == "oui") {
        CreerFichierUti();
    }
    cout << "Veuillez vous identifier (ecrire le nom d'utilisateur) " << endl;
    cin >> rep;
    Utilisateur uti1 = LireUtilisateur(rep); //Ajouter une exception pour si l'utilisateur n'existe pas
    cout << "Voulez-vous entrer de nouvelles donnees de votre fichier ? Repondre par 'oui' ou 'non' " << endl;
    cin >> rep;
    bool updateneeded = false;
    while (rep == "oui") { // Ajouter une exception si l'utilisateur rentre n'importe quoi
        StoreData(uti1);
        cout << "Voulez-vous entrer de nouvelles donnees de votre fichier ? Repondre par 'oui' ou 'non' " << endl;
        cin >> rep;
        updateneeded = true;

    }
    if (updateneeded) {
        //Mettre à jour users.txt
        uti1.setTempsUt();
        uti1.writeToFile();
    }
    else{
        //création d'une liste de tous les utilisateurs
    }
    
    cout << "Souhaitez vous vous connecter ? (oui/non)" << endl;
    cin >> rep;
    if (rep == "oui") {
        cout << "Tapez votre identifiant" << endl;
        cin >> rep;
        User nouv(rep);
        rep = "";
        do{
            vector<Uint32> donnees = StoreData(nouv);
            cout <<"Votre score est de " << nouv.CalculScore1(donnees) << endl;
            cout << "Votre score est de " << nouv.CalculScore2(donnees) << endl;
            cout << "Souhaitez vous continuer ? (oui/non)" << endl;
            cin >> rep;
        } while (rep == "oui");

    }
    SDL_Quit();
    return 0;
}
