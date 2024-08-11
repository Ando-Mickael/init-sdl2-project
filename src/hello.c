#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Initialiser SDL_ttf
    if (TTF_Init() == -1) {
        printf("Erreur d'initialisation de SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
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
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Créer un rendu
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur lors de la création du rendu: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Charger une police
    TTF_Font *font = TTF_OpenFont("Roboto-Regular.ttf", 24);
    if (font == NULL) {
        printf("Erreur lors du chargement de la police: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Définir la couleur du texte
    SDL_Color color = {255, 255, 255, 255}; // Blanc

    // Créer la surface du texte
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Hello World", color);
    if (textSurface == NULL) {
        printf("Erreur lors de la création de la surface du texte: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Créer une texture à partir de la surface
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface); // Libérer la surface après avoir créé la texture

    if (textTexture == NULL) {
        printf("Erreur lors de la création de la texture du texte: %s\n", SDL_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Obtenir les dimensions du texte
    int textWidth = 0;
    int textHeight = 0;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    // Créer un rectangle pour positionner le texte au centre de l'écran
    SDL_Rect textRect;
    textRect.x = (640 - textWidth) / 2; // Centrer horizontalement
    textRect.y = (480 - textHeight) / 2; // Centrer verticalement
    textRect.w = textWidth;
    textRect.h = textHeight;

    // Boucle principale
    int quit = 0;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir
        SDL_RenderClear(renderer);

        // Dessiner le texte
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        // Présenter le rendu
        SDL_RenderPresent(renderer);
    }

    // Nettoyer et quitter
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
