#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include "global_vars.h"
#include "config_file.h"
#include "allegro_system.h"
#include "floor.h"
#include "bouncer.h"
#include "blocks.h"

int main(int argc, char **argv) {

    load_config_from_file();
    process_config();

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *floor = NULL;
    ALLEGRO_BITMAP *bouncer = NULL;

    bool redraw = true;      // Is it time to redraw a frame?
    bool doexit = false;     // Did user want to exit?

    // INITIALIZATION PROCESS
    allegro_system_init();

    // MAIN LOOP
    while (!doexit) {

        // EVENT HANDLER
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        // TIMER EVENT
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            if (key[KEY_UP]);
            if (key[KEY_DOWN]);
            if (key[KEY_LEFT] && floor_x >= 0.0) {
                floor_x -= 16.0;
            }
            if (key[KEY_RIGHT] && floor_x <= SCREEN_W - FLOOR_W) {
                floor_x += 16.0;
            }

            switch (bouncer_movement()) {
                case 1: // Game over
                    al_stop_timer(timer);
                    al_flush_event_queue(event_queue);
                    switch (al_show_native_message_box(al_get_current_display(),
                                                       "Game over",
                                                       "You have lost.",
                                                       "Do you want to try again?",
                                                       NULL, ALLEGRO_MESSAGEBOX_YES_NO)) {
                        case 2:
                            exit(0);
                        default:
                            --level;
                            advance_level(display);
                            break;
                    }
                    al_start_timer(timer);
                    break;
                case 2: // All blocks got destroyed
                    al_stop_timer(timer);
                    al_flush_event_queue(event_queue);
                    if (advance_level(display) == 1) {
                        // Game completed
                        switch (al_show_native_message_box(al_get_current_display(),
                                                           "Game completed",
                                                           "You have completed the game",
                                                           "Congratulations! Do you want to try again?",
                                                           NULL, ALLEGRO_MESSAGEBOX_YES_NO)) {
                            case 2:
                                exit(0);
                            default:
                                level = 0;
                                bouncer_create();
                                floor_create();
                                advance_level(display);
                                al_start_timer(timer);
                                break;
                        }
                        al_start_timer(timer);
                    }
                    else {
                        // Next level
                        switch (al_show_native_message_box(al_get_current_display(),
                                                           "Next level",
                                                           "Prepare for the next level",
                                                           "Ready!",
                                                           NULL, ALLEGRO_MESSAGEBOX_WARN)) {
                            default:
                                break;
                        }
                    }
                    al_start_timer(timer);
                    break;
                default:
                    // There are blocks remaining and the player didn't lose
                    break;
            }
            redraw = true;
        }
        // DISPLAY CLOSE EVENT
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        // KEY PRESSED EVENT
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    break;

                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    break;

                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = true;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    break;
                case ALLEGRO_KEY_R:
                    --level;
                    advance_level(display);
                default:
                    break;
            }
        }
        // KEY RELEASED EVENT
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = false;
                    break;

                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = false;
                    break;

                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = false;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = false;
                    break;

                case ALLEGRO_KEY_ESCAPE:
                    doexit = true;
                    break;
                default:
                    break;
            }
        }

        // REDRAW
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(floor, floor_x, floor_y, 0);
            al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
            blocks_draw();
            al_flip_display();
        }
    }

    // FREE RESOURCES
    al_destroy_bitmap(bouncer);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}