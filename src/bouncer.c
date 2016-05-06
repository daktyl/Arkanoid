#include <allegro5/allegro.h>
#include <stdio.h>
#include <math.h>
#include "blocks.h"

extern int SCREEN_W;
extern int SCREEN_H;
extern int BOUNCER_SIZE;
extern int FLOOR_W;
extern int FLOOR_H;
extern float floor_x;
extern float floor_y;
extern float bouncer_x;
extern float bouncer_y;
extern float bouncer_speed;
extern float bouncer_bonusspeed;
extern float angle_multiplier;
extern float hits_counter;
extern char difficulty;
extern int level;
extern bool rand_init;
extern bool key[];

enum MYDIRECTIONS   {   LT,    RT,    LB,    RB  };
bool direction[4] = { false, false, false, false };            // Holds information about current bouncer direction
bool border[5] = { false, false, false, false, false };        // Holds information which border stopped bouncer from moving
enum MYBORDERS   {  BLOCK, LEFT, RIGHT, UPPER, FLOOR, GAMEOVER };
short int lastDirection;

void bouncer_create() {
    if (!rand_init) {
        srand((unsigned int) time(0));
        rand_init = true;
    }
    bouncer_x = (float) (SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0);
    bouncer_y = (floor_y - FLOOR_H - BOUNCER_SIZE);
    direction[rand() % 2] = true;
}

void bouncer_change_direction() {
    unsigned short int dir;
    for (dir = 0; dir < 4; ++dir) {
        if (direction[dir]) {
            lastDirection = dir;
            break;
        }
    }
    if (direction[LT]) {
        direction[LT] = false;
        if (border[LEFT]) {
            direction[RT] = true;
            border[LEFT] = false;
        } else {
            direction[LB] = true;
            border[UPPER] = false;
        }
    } else if (direction[RT]) {
        direction[RT] = false;
        if (border[RIGHT]) {
            direction[LT] = true;
            border[RIGHT] = false;
        } else {
            direction[RB] = true;
            border[UPPER] = false;
        }
    } else if (direction[LB]) {
        direction[LB] = false;
        if (border[LEFT]) {
            direction[RB] = true;
            border[LEFT] = false;
        } else if (border[FLOOR]) {
            direction[LT] = true;
            border[FLOOR] = false;
        } else {
            direction[LT] = true;
            border[BLOCK] = false;
        }
    } else if (direction[RB]) {
        direction[RB] = false;
        if (border[RIGHT]) {
            direction[LB] = true;
            border[RIGHT] = false;
        } else if (border[FLOOR]) {
            direction[RT] = true;
            border[RIGHT] = false;
        } else {
            direction[RT] = true;
            border[BLOCK] = false;
        }
    } else {
        direction[lastDirection] = true;
    }
}


int bouncer_collision_decection() {
/*Block*/if (got_block_hit()) {
            border[BLOCK] = true;
            if (direction[LB] || direction [RB]) {
                ++hits_counter;
            } else {
                if (hits_counter < 2) {
                    hits_counter = 0;
                } else {
                    hits_counter -= 2;
                }
            }
            bouncer_change_direction();
    } else if
/*Floor*/   ((bouncer_y + BOUNCER_SIZE > floor_y) && (bouncer_y < floor_y + FLOOR_H) && (bouncer_x + BOUNCER_SIZE > floor_x) && (bouncer_x < floor_x + FLOOR_W)) {
            border[FLOOR] = true;
            if ((key[3]) || (key[4])) {
                angle_multiplier = 1.25;
            } else {
                angle_multiplier = 1.0;
            }
            bouncer_change_direction();
    } else if
/*Left*/    (bouncer_x <= 0) {
            border[LEFT] = true;
            hits_counter += 0.75;;
            bouncer_change_direction();
    } else if
/*Right*/   (bouncer_x + BOUNCER_SIZE >= SCREEN_W) {
            border[RIGHT] = true;
            hits_counter += 0.75;;
            bouncer_change_direction();
    } else if
/*Upper*/   (bouncer_y <= 0) {
            border[UPPER] = true;
            hits_counter += 0.75;
            bouncer_change_direction();
    } else if
/*Gameover*/(bouncer_y >= SCREEN_H) {
            border[GAMEOVER] = true;
            printf("[INFO] You have lost.\n");
            return 1;
    }
    return 0;
}

int bouncer_movement() {
    if (!are_blocks_remaining()) {
        printf("[INFO] You have completed level %d!\n", level);
        return 2;
    }
    switch (difficulty) {
        case '0':
            bouncer_bonusspeed = 0;
            break;
        default:
            bouncer_bonusspeed = (float) sqrt(sqrt(hits_counter));;
            break;
    }
    if (!(direction[0] || direction[1] || direction[2] || direction[3])) {
        direction[lastDirection] = true;
    }
    if (bouncer_collision_decection() == 1) {
        return 1;
    }
    if (direction[LT]) {
        bouncer_x -= bouncer_speed * angle_multiplier + bouncer_bonusspeed;
        bouncer_y -= bouncer_speed / angle_multiplier + bouncer_bonusspeed;
    }
    else if (direction[RT]) {
        bouncer_x += bouncer_speed * angle_multiplier + bouncer_bonusspeed;
        bouncer_y -= bouncer_speed / angle_multiplier + bouncer_bonusspeed;
    }
    else if (direction[LB]) {
        bouncer_x -= bouncer_speed * angle_multiplier + bouncer_bonusspeed;
        bouncer_y += bouncer_speed / angle_multiplier + bouncer_bonusspeed;
    }
    else if (direction[RB]) {
        bouncer_x += bouncer_speed * angle_multiplier + bouncer_bonusspeed;
        bouncer_y += bouncer_speed / angle_multiplier + bouncer_bonusspeed;
    }
    return 0;
}