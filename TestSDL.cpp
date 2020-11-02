#include "SDL.h"
#include "SDL_keyboard.h"
#include "UtilisateurToUsers.h"
#include "calculs.h"
#include <iostream>
#include <stdio.h>
using namespace std;

/* main */
int main(int argc, char* argv[]) {
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
        uti1.writeToFilebis();
    }
    else{
        //création d'une liste de tous les utilisateurs
    }
    
    //Proposer une vérification
    SDL_Quit();
    return 0;

    //SDL_Event event;
    //bool quit = false;
    //Utilisateur lucas;
    //check_if(lucas);
    ///* Initialise SDL */
    //if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    //    cout<<stderr<< "Could not initialise SDL: %s"<< SDL_GetError();
    //    return (-1);
    //}

    ///* Set a video mode */
    //if (!SDL_CreateWindow("Ma fenêtre de jeu",
    //    SDL_WINDOWPOS_CENTERED,
    //    SDL_WINDOWPOS_CENTERED,
    //    640, 480,
    //    SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)) {
    //    cout<<stderr<< "Could not set video mode: %s"<< SDL_GetError();
    //    SDL_Quit();
    //    return (-1);
    //}
    //cout << "Ecrivez :" << endl;
    //cout << "Hello World" << endl;
    //string tapage = "";
    ///* Loop until an SDL_QUIT event is found */
    //while (!quit) {
    //    /* Poll for events */
    //    while (SDL_PollEvent(&event)) {

    //        switch (event.type) {
    //            /* Keyboard event */
    //            /* Pass the event data onto PrintKeyInfo() */
    //        case SDL_KEYDOWN:
    //            //PrintKeyInfo(&event.key);
    //            if (event.key.repeat == 0) {
    //                if (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN) {
    //                    tapage = "";
    //                }
    //                else if (event.key.keysym.sym == SDLK_SPACE) {
    //                    tapage += " ";
    //                }
    //                else if (event.key.keysym.sym == SDLK_BACKSPACE) {
    //                    if (tapage != "") {
    //                        tapage.pop_back();
    //                    }
    //                }
    //                else if (event.key.keysym.sym != SDLK_LSHIFT && event.key.keysym.sym != SDLK_RSHIFT && event.key.keysym.sym != SDLK_SPACE) {
    //                    if (!(SDL_GetModState() & KMOD_SHIFT)) {
    //                        tapage += (char)tolower(*SDL_GetKeyName(event.key.keysym.sym));
    //                        // cout << event.key.timestamp << endl;
    //                    }
    //                    else {
    //                        tapage += SDL_GetKeyName(event.key.keysym.sym);
    //                        //cout << event.key.timestamp << endl;
    //                    }
    //                    //cout << event.key.timestamp << endl;
    //                }
    //                cout << event.key.timestamp << " ";
    //                cout << tapage;
    //            }
    //            break;
    //        case SDL_KEYUP:
    //            cout << " " << event.key.timestamp << endl;
    //            break;
    //            /* SDL_QUIT event (window close) */
    //        case SDL_QUIT:
    //            quit = true;
    //            break;

    //        default:
    //            break;
    //        }

    //    }

    //}


    ///* Clean up */
    //SDL_Quit();
    //return (0);
}