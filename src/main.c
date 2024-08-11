#include <SDL2/SDL.h>
#include <stdio.h>
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Créer une fenêtre
    SDL_Window *window = SDL_CreateWindow(
        "Hello World",             // Titre de la fenêtre
        SDL_WINDOWPOS_CENTERED,    // Position X
        SDL_WINDOWPOS_CENTERED,    // Position Y
        640,                       // Largeur de la fenêtre
        480,                       // Hauteur de la fenêtre
        SDL_WINDOW_SHOWN           // Flags de la fenêtre
    );

    // Vérifier si la fenêtre a été créée correctement
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Attendre que l'utilisateur ferme la fenêtre
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    // Nettoyer et quitter
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}