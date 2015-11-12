#ifndef ALLEGRO_BOUNCER_H
#define ALLEGRO_BOUNCER_H

// Sets the position and randomize the starting direction of a bouncer.
void bouncer_create();

// Changes bouncer's next direction according to the current one and the object that was hit.
void bouncer_change_direction();

// Checks for any collision and calls bouncer_change_direction() if needed.
int bouncer_collision_decection();

// Handles bouncer movement including the velocity and angle changes.
int bouncer_movement();

#endif //ALLEGRO_BOUNCER_H
