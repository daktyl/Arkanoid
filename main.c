#include <allegro5/allegro.h>
#include <stdio.h>
#include "global_vars.h"
#include "allegro_system.h"
#include "floor.h"
#include "bouncer.h"

int main(int argc, char **argv) {

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_BITMAP* floor = NULL;
    ALLEGRO_BITMAP* bouncer = NULL;

    bool key[4] = {false, false, false, false};         // Holds information about keypresses
    bool redraw = true;                                 // Is it time to redraw a frame?
    bool doexit = false;                                // Did user want to exit?

    // INITIALIZATION PROCESS
    allegro_system_init();

    // MAIN LOOP
    while (!doexit)
    {
        // EVENT HANDLER
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            if (key[KEY_UP]);
            if (key[KEY_DOWN]);
            if (key[KEY_LEFT] && floor_x >= 0.0) {
                floor_x -= 16.0;
            }
            if (key[KEY_RIGHT] && floor_x <= SCREEN_W - FLOOR_W) {
                floor_x += 16.0;
            }
            if (bouncer_movement() == 1) {
                doexit = true;
            }
            redraw = true;
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {
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
                default:break;
            }
        }
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
                default:break;
            }
        }

        // REDRAW

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            al_clear_to_color(al_map_rgb(0,0,0));

            al_draw_bitmap(floor, floor_x, floor_y, 0);
            al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);

            al_flip_display();
        }
    }

    al_destroy_bitmap(bouncer);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}