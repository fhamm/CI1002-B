#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>


#ifndef CHUNKS
#define CHUNKS
#include "Chunks.h"
#endif

#ifndef PHYSICS
#define PHYSICS
#include "Physics.h"
#endif

#ifndef ENTITIES
#define ENTITIES
#include "Entities.h"
#endif

#ifndef MENUS
#define MENUS
#include "Menus.h"
#endif

void InitializeModule(bool test, const char *description) {
    
    if (test) return;

    printf("Could not initialize %s\n", description);
    exit(1);
}

// ------------

int main() {
       
    InitializeModule(al_init(), "allegro");

    // Initialize timer
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / GAME_FPS);
    InitializeModule(timer, "timer");

    // Initialize event queue
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    InitializeModule(queue, "queue");

    // Initialize display
    ALLEGRO_DISPLAY *disp = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    InitializeModule(disp, "display");
    al_set_window_title(disp, "Redshift");

    // Initialize image addon
    InitializeModule(al_init_image_addon(), "image addon");

    // Initialize font addon
    InitializeModule(al_init_font_addon(), "font addon");
    InitializeModule(al_init_ttf_addon(), "ttf addon");

    // Initialize primitives
    InitializeModule(al_init_primitives_addon(), "primitives");

    // Initialize mouse
    InitializeModule(al_install_mouse(), "mouse");
    al_set_system_mouse_cursor(disp, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    // Initialize keyboard
    InitializeModule(al_install_keyboard(), "keyboard");
    
    // Settings
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);

    // Event handling declarations
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    // Variables
    int state = 0;
    bool reset = false;
    bool done = false;
    bool redraw = true;
    int frameCount = 0;
    //float lastTimestamp = 0;
    ALLEGRO_EVENT event;
    //int mouseX, mouseY;

    // Generate level
    Background* background = InitializeBackground();
    Player* player = InitializePlayer();
    Chunk* chunk = GenerateChunk(time(NULL));
    EntityHandler* entities = InitializeEntities(chunk);

    // Keyboard stuff
    #define KEY_SEEN     1
    #define KEY_RELEASED 2
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    // Start stuff
    al_grab_mouse(disp);
    al_hide_mouse_cursor(disp);
    al_start_timer(timer);
    
    printf("Initialization successful!\n");

    while (1) {
        
        al_wait_for_event(queue, &event);

        // This is where game logic is defined
        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;

                // Quit
                if (key[ALLEGRO_KEY_Q])
                        done = true;

                // Start menu
                if (state == 0) {
                    if (key[ALLEGRO_KEY_ENTER])
                        state = 1;
                }

                // Playing
                if (state == 1) {
                    if (key[ALLEGRO_KEY_H]) {
                        state = 2;
                    }

                    if (key[ALLEGRO_KEY_SPACE])
                        if (player->jumping == 0)
                            player->jumping = 1;
                }

                // Pause menu
                if (state == 2) {         
                    if (key[ALLEGRO_KEY_ESCAPE])
                        state = 1;
                    
                    //if (key[ALLEGRO_KEY_F11])
                    //    PlayRacaNegra();
                }

                // Game over
                if (state == 3) {         
                    if (key[ALLEGRO_KEY_SPACE]) {
                        reset = true;
                        state = 1;
                    }
                }

                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        // Reset game
        if (reset) {
            
            // Free old level
            FreeBackground(background);
            free(player);
            free(chunk);
            FreeEntities(entities);

            // Generate level
            background = InitializeBackground();
            player = InitializePlayer();
            chunk = GenerateChunk(time(NULL));
            entities = InitializeEntities(chunk);

            printf("Game reseted!\n");

            reset = false;
            frameCount = 0;
        }

        // Check if everything is done
        if (done) {
            
            printf("Finishing game...\n");

            FreeBackground(background);
            free(player);
            free(chunk);
            FreeEntities(entities);
            break;
        }

        if (redraw && al_is_event_queue_empty(queue)) {

            float timestamp = al_get_time();
            float score = frameCount / 10;

            // Start menu state
            if (state == 0) {
                RenderStartMenu(timestamp);                
            }

            // Gameplay state
            if (state == 1) {
                
                UpdateBackground(background);

                if (ClearSector(entities, chunk) == 1) {
                    chunk = GenerateChunk(rand());
                    entities = InitializeEntities(chunk);
                }

                if (PlayerOutOfBounds(player) || PlayerCollisionCheck(player, entities)) {
                    //lastTimestamp = timestamp;
                    state = 3;
                }

                UpdatePlayerPhysics(player, entities, timestamp, frameCount);
                RenderPlayer(player);

                RenderEntities(entities);
                UpdateEntities(entities);

                RenderScore(score);

                frameCount++;
                player->jumping = 0;
            }

            // Help menu
            if (state == 2) {
                RenderHelpMenu();
            }

            // Game over menu
            if (state == 3) {             

                if (!WriteScoreToLeaderboard(score))
                    perror("Could not save score in leaderboards");

                RenderGameOverMenu(score);
            }

            redraw = false;
            al_flip_display(); 
        }
    }

    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}