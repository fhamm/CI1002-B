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

// Render points

void RenderScore (float score) {

    // Initialize font
    ALLEGRO_FONT* titleFont = al_load_font("resources/fonts/AeroliteBold.otf", 36, 0);

    // Render score
    al_draw_textf (titleFont, al_map_rgb(255, 255, 255), 150, 75, 1, "SCORE: %d", (int) score);

    // Clear font
    al_destroy_font(titleFont);
}

// Menu functions

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

    // Clear background
    al_clear_to_color (al_map_rgb(0, 0, 30));

    // Controls
    al_draw_text (titleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6, 1, "PAUSE");
    al_draw_text (subTitleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 2 * spacing, 1, "SPACE : Jump");
    al_draw_text (subTitleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 3 * spacing, 1, "H : PAUSE");
    al_draw_text (subTitleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 4 * spacing, 1, "Q : QUIT");
    al_draw_text (subTitleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 5 * spacing, 1, "F11: ?");
    
    // Message
    al_draw_text (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 7 * spacing, 1, "This game is pseudo-randomly generated.");
    al_draw_text (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 7.5 * spacing, 1, "If you're on a lose-streak, you can blame your computer for it.");

    // Guide text
    al_draw_text (subTitleFont, al_map_rgb(255, 255, 255), 1 * WINDOW_WIDTH / 8, WINDOW_HEIGHT / 6 + 8 * spacing, 1, "Press ESC to return");

    // Clear fonts
    al_destroy_font(titleFont);
    al_destroy_font(subTitleFont);
    al_destroy_font(messageFont);
}

void RenderGameOverMenu (float score) {

    float first, second, third;
    int spacing = 100;

    LeaderboardHighScores(&first, &second, &third);
    
    // Initialize fonts
    ALLEGRO_FONT* titleFont = al_load_font("resources/fonts/AeroliteBold.otf", 72, 0);
    ALLEGRO_FONT* subTitleFont = al_load_font("resources/fonts/Aerolite.otf", 48, 0);
    ALLEGRO_FONT* messageFont = al_load_font("resources/fonts/DotGothic.ttf", 24, 0);

    // Render menu

    // Clear background
    al_clear_to_color (al_map_rgb(0, 0, 0));

    // Lost & score
    al_draw_text (titleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 1, "YOU LOST");
    al_draw_textf (subTitleFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + spacing, 1, "Your score was %d", (int) score);
    
    // Records
    if (score == first)
        al_draw_textf (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 2 * spacing, 1, "1: %d pts (NEW RECORD)", (int) first);
    else
        al_draw_textf (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 2 * spacing, 1, "1: %d pts", (int) first);

    if (score == second)
        al_draw_textf (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 2.5 * spacing, 1, "2: %d pts (NEW RECORD)", (int) second);
    else
        al_draw_textf (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 2.5 * spacing, 1, "2: %d pts", (int) second);

    if (score == third)
        al_draw_textf (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 3.0 * spacing, 1, "3: %d pts (NEW RECORD)", (int) third);
    else
        al_draw_textf (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 3.0 * spacing, 1, "3: %d pts", (int) third);

    // Random "offenses"
    int message = fmod(score, 10);

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
    if (message == 6)
        al_draw_text (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 7.5 * spacing, 1, "In a parallel universe you're good at this game. A very distant parallel universe.");
    if (message == 7)
        al_draw_text (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 7.5 * spacing, 1, "I should be payed more for watching this disaster.");
    if (message == 8)
        al_draw_text (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 7.5 * spacing, 1, "Are you sure that you don't want me to call the hospital? These reflexes doesn't seem right...");
    if (message == 9)
        al_draw_text (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 7.5 * spacing, 1, "Maybe robots really should assume control of this place...");
    if (message == 10)
        al_draw_text (messageFont, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6 + 7.5 * spacing, 1, "You literally just have to jump. J U M P.");

    // Guide text
    al_draw_text (subTitleFont, al_map_rgb(255, 255, 255), 1 * WINDOW_WIDTH / 10, WINDOW_HEIGHT / 6 + 8 * spacing, 1, "Press Q to quit");
    al_draw_text (subTitleFont, al_map_rgb(255, 255, 255), 8.7 * WINDOW_WIDTH / 10, WINDOW_HEIGHT / 6 + 8 * spacing, 1, "Press Space to retry");

    // Clear fonts
    al_destroy_font(titleFont);
    al_destroy_font(subTitleFont);
    al_destroy_font(messageFont);
} 

// Leaderboard functions

int WriteScoreToLeaderboard (float score) {

    // Open file
    FILE* leaderboardFile  = fopen("resources/data/leaderboard.txt", "ab+");

    if (leaderboardFile == NULL)
        return 0;

    // Calculate file size
    fseek(leaderboardFile, 0L, SEEK_END);
    int fileSize = ftell(leaderboardFile);
    rewind(leaderboardFile);

    // Declare variables
    int elements = fileSize / sizeof(float);

    // Check if score is already on scores
    int found = 0;
    for (int i = 0; i < elements; i++) {
        
        float n;
        fread(&n, sizeof(float), 1, leaderboardFile);

        if (n == score) {
            found = 1;
            break;
        }
    }
    
    // If score doesn't exist on leaderboards, write to file
    if (found == 0)
        fwrite(&score, sizeof(float), 1, leaderboardFile);

    // Close file
    fclose(leaderboardFile);

    return 1;
}

int LeaderboardHighScores (float* first, float* second, float* third) {

    // Open file
    FILE* leaderboardFile = fopen("resources/data/leaderboard.txt", "r+");

    if (leaderboardFile == NULL)
        return 0;
    
    // Calculate file size
    fseek(leaderboardFile, 0L, SEEK_END);
    int fileSize = ftell(leaderboardFile);
    rewind(leaderboardFile);

    // Declare variables
    float* scores = malloc(sizeof(float) * fileSize);
    int elements = fileSize / sizeof(float);

    // Read scores
    fread(scores, sizeof(float), elements, leaderboardFile);

    // Sort values (selection sort)
    int p; 
    for (int i = 0; i < elements - 1; i++) { 
        p = i; 
        for (int j = i+1; j < elements; j++) 
            if (scores[j] < scores[p]) 
                p = j; 

        float aux = scores[p];
        scores[p] = scores[i];
        scores[i] = aux;
    }

    // Get highest scores
    if (elements >= 1)
        *first = scores[elements - 1];
    else
        *first = 0;
    if (elements >= 2)
        *second = scores[elements - 2];
    else
        *second = 0;
    if (elements >= 3)
        *third = scores[elements - 3];
    else
        *third = 0;

    // Free memory
    free(scores);
    fclose(leaderboardFile);

    return 1;
}