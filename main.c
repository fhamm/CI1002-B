#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "Entities.h"
#include "Physics.h"

void InitializeModule(bool test, const char *description) {
    if (test) 
        return;

    printf("Could not initialize %s\n", description);
    exit(1);
}

// ------------

int main() {

    srand(RANDOM_SEED);
       
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

    // Initialize primitives
    InitializeModule(al_init_primitives_addon(), "primitives");

    // Initialize mouse
    InitializeModule(al_install_mouse(), "mouse");
    al_set_system_mouse_cursor(disp, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
    
    // Settings
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    // Event handling declarations
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    bool done = false;
    bool redraw = true;
    int mouseX, mouseY;
    ALLEGRO_EVENT event;

    al_grab_mouse(disp);
    al_start_timer(timer);

    //al_hide_mouse_cursor(disp); // Why this doesn't work?

    // Generate level
    Background* background = InitializeBackground();
    Player* player = InitializePlayer();
    Chunk* chunk = GenerateChunk(rand());
    EntityHandler* entities = InitializeEntities(chunk);
    
    printf("Initialization successful!\n");

    while (1) {
        
        al_wait_for_event(queue, &event);

        // This is where game logic is defined
        switch (event.type) {

            case ALLEGRO_EVENT_MOUSE_AXES:
                mouseX = event.mouse.x;
                mouseY = event.mouse.y;
                break;

            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        // Check if everything is done
        if (done) {
            free(background);
            free(player);
            free(chunk);
            FreeEntities(entities);
            break;
        }

        if (redraw && al_is_event_queue_empty(queue)) {

            
            
            // This is where things are rendered
            UpdateBackground(background);
            
            if (ClearSector(entities, chunk) == 1) {
                chunk = GenerateChunk(rand());
                entities = InitializeEntities(chunk);
            }

            RenderPlayer(player, mouseX, mouseY);

            RenderEntities(entities);
            UpdateEntities(entities);

            al_flip_display();

            redraw = false;

            if (PlayerCollisionCheck(player, entities))
                done = true;
        }
    }

    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}