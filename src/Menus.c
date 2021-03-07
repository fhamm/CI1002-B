#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
 #include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#ifndef ENTITIES
#define ENTITIES
#include "Entities.h"
#endif

#ifndef MENUS
#define MENUS
#include "Menus.h"
#endif

void RenderStartMenu (float timestamp) {

    // Initialize fonts
    ALLEGRO_FONT* titleFont = al_load_font("resources/fonts/AeroliteBold.otf", 72, 0);
    ALLEGRO_FONT* subTitleFont = al_load_font("resources/fonts/Aerolite.otf", 48, 0);

    if (titleFont == NULL || subTitleFont == NULL)
        perror("Could not load font\n");
    
    // Render animation
    float animationLength = 2.0;

    if (timestamp <= animationLength) {
        al_clear_to_color(al_map_rgb(255 * (timestamp / animationLength), 50, 50));
        al_draw_text(titleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, (WINDOW_HEIGHT / 2) * (timestamp / animationLength), 1, "R E D S H I F T");
    }
    else {
        al_clear_to_color(al_map_rgb(255, 50, 50));
        al_draw_text(titleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 1, "R E D S H I F T");
        al_draw_text(subTitleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT - (WINDOW_HEIGHT / 3), 1, "PRESS ENTER TO PLAY");
    }

    // Clear fonts
    al_destroy_font(titleFont);
    al_destroy_font(subTitleFont);
}

void RenderHelpMenu () {

    // Initialize fonts
    ALLEGRO_FONT* titleFont = al_load_font("resources/fonts/AeroliteBold.otf", 72, 0);
    ALLEGRO_FONT* subTitleFont = al_load_font("resources/fonts/Aerolite.otf", 48, 0);
    ALLEGRO_FONT* messageFont = al_load_font("resources/fonts/DotGothic.ttf", 24, 0);

    int spacing = 100;

    // Render menu

    al_clear_to_color (al_map_rgb(0, 0, 30));

    // Controls
    al_draw_text (titleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6, 1, "PAUSE");
    al_draw_text (subTitleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 2 * spacing, 1, "SPACE : Jump");
    al_draw_text (subTitleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 3 * spacing, 1, "H : PAUSE");
    al_draw_text (subTitleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 4 * spacing, 1, "Q : QUIT");
    al_draw_text (subTitleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 5 * spacing, 1, "F11 1S F0RB1DD3N!");
    
    al_draw_text (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 7 * spacing, 1, "This game is pseudo-randomly generated.");
    al_draw_text (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 7.5 * spacing, 1, "If you're on a lose-streak, you can blame your computer for it.");

    al_draw_text (subTitleFont, al_map_rgb(255, 255, 255), 1 * WINDOW_WIDTH / 10, WINDOW_HEIGHT / 6 + 8 * spacing, 1, "Press ESC to return");

    // Clear fonts
    al_destroy_font(titleFont);
    al_destroy_font(subTitleFont);
    al_destroy_font(messageFont);
}

void RenderGameOverMenu (float score) {

    // Initialize fonts
    ALLEGRO_FONT* titleFont = al_load_font("resources/fonts/AeroliteBold.otf", 72, 0);
    ALLEGRO_FONT* subTitleFont = al_load_font("resources/fonts/Aerolite.otf", 48, 0);
    ALLEGRO_FONT* messageFont = al_load_font("resources/fonts/DotGothic.ttf", 24, 0);

    int spacing = 100;

    // Render menu

    al_clear_to_color (al_map_rgb(0, 0, 0));

    // Controls
    al_draw_text (titleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 1, "YOU LOST");
    al_draw_textf (subTitleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + spacing, 1, "Your score was %f seconds", score);
    

    // Random "offenses"
    int message = fmod(score, 5);

    if (message == 0)
        al_draw_text (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 7.5 * spacing, 1, "Wow. Were you even trying?");
    if (message == 1)
        al_draw_text (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 7.5 * spacing, 1, "That was impressive! For a five-year-old...");
    if (message == 2)
        al_draw_text (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 7.5 * spacing, 1, "So, when are you going to start trying?");
    if (message == 3)
        al_draw_text (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 7.5 * spacing, 1, "I once knew a monkey that could play this game better than you.");
    if (message == 4)
        al_draw_text (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 7.5 * spacing, 1, "Have you been eating your vegetables? Your brain kinda needs them...");
    if (message == 5)
        al_draw_text (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 7.5 * spacing, 1, "Please give the keyboard to your dog. He's certainly better than you.");
    
    al_draw_text (subTitleFont, al_map_rgb(255, 255, 255), 1 * WINDOW_WIDTH / 10, WINDOW_HEIGHT / 6 + 8 * spacing, 1, "Press Q to quit");

    // Clear fonts
    al_destroy_font(titleFont);
    al_destroy_font(subTitleFont);
    al_destroy_font(messageFont);
} 