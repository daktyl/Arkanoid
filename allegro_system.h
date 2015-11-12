#ifndef ALLEGRO_ALLEGRO_SYSTEM_H
#define ALLEGRO_ALLEGRO_SYSTEM_H

// Macro which initializes Allegro and all neccesary mechanisms for game to function.
#define allegro_system_init()                                           \
do {                                                                    \
    if (!al_init()) {                                                   \
        fprintf(stderr, "[ERROR] Failed to initialize Allegro!\n");     \
        return -1;                                                      \
    }                                                                   \
                                                                        \
    if (!al_install_keyboard()) {                                       \
        fprintf(stderr, "[ERROR] Failed to initialize the keyboard!\n");\
        return -1;                                                      \
    }                                                                   \
                                                                        \
    if (!al_install_mouse()) {                                          \
        fprintf(stderr, "[ERROR] Failed to initialize the mouse!\n");   \
        return -1;                                                      \
    }                                                                   \
                                                                        \
    timer = al_create_timer(1.0 / FPS);                                 \
    if (!timer) {                                                       \
        fprintf(stderr, "[ERROR] Failed to create timer!\n");           \
        return -1;                                                      \
    }                                                                   \
                                                                        \
    display = al_create_display(SCREEN_W, SCREEN_H);                    \
    if (!display) {                                                     \
        fprintf(stderr, "[ERROR] Failed to create display!\n");         \
        al_destroy_timer(timer);                                        \
        return -1;                                                      \
    }                                                                   \
                                                                        \
    event_queue = al_create_event_queue();                              \
    if (!event_queue) {                                                 \
        fprintf(stderr, "[ERROR] Failed to create event_queue!\n");     \
        al_destroy_display(display);                                    \
        al_destroy_timer(timer);                                        \
        return -1;                                                      \
    }                                                                   \
                                                                        \
    floor = al_create_bitmap(FLOOR_W, FLOOR_H);                         \
    if (!floor) {                                                       \
        fprintf(stderr, "[ERROR] Failed to create floor bitmap!\n");    \
        al_destroy_event_queue(event_queue);                            \
        al_destroy_display(display);                                    \
        al_destroy_timer(timer);                                        \
        return -1;                                                      \
                                                                        \
    }                                                                   \
    floor_create();                                                     \
                                                                        \
    bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);             \
    if (!bouncer) {                                                     \
        fprintf(stderr, "[ERROR] Failed to create bouncer bitmap!\n");  \
        al_destroy_bitmap(floor);                                       \
        al_destroy_event_queue(event_queue);                            \
        al_destroy_display(display);                                    \
        al_destroy_timer(timer);                                        \
        return -1;                                                      \
    }                                                                   \
    bouncer_create();                                                   \
                                                                        \
    al_register_event_source(event_queue, al_get_display_event_source(display)); /* Wait for event from DISPLAY (like close button (X)) */  \
    al_register_event_source(event_queue, al_get_timer_event_source(timer));                                                                \
    al_register_event_source(event_queue, al_get_mouse_event_source());                                                                     \
    al_register_event_source(event_queue, al_get_keyboard_event_source());                                                                  \
    al_set_target_bitmap(floor);                        /* Setting floor as a drawing target */         \
    al_clear_to_color(al_map_rgb(234,225,100));         /* Coloring floor */                            \
    al_set_target_bitmap(bouncer);                      /* Setting bouncer as a drawing target */       \
    al_clear_to_color(al_map_rgb(255,0,255));           /* Coloring bouncer */                          \
    advance_level(display);                                                                             \
    al_clear_to_color(al_map_rgb(0,0,0));               /* Color the background */                      \
    al_flip_display();                                  /* Print buffer to screen */                    \
    al_start_timer(timer);                              /* Start timer */                               \
} while (0)

#endif //ALLEGRO_ALLEGRO_SYSTEM_H
