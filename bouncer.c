#include <allegro5/allegro.h>


enum MYDIRECTIONS { LT, RT, LB, RB };
extern const int SCREEN_W;
extern const int SCREEN_H;
extern const int BOUNCER_SIZE;
extern const int FLOOR_W;
extern float floor_x;
extern float floor_y;
extern float bouncer_x;
extern float bouncer_y;
bool direction[4] = { false, false, false, false };            // Holds information about current bouncer direction
bool border[5] = { false, false, false, false, false };        // Holds information which border stopped bouncer from moving
enum MYBORDERS   {  LEFT, RIGHT, UPPER, FLOOR, GAMEOVER };

void bouncer_create() {
    bouncer_x = (float) (SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0);
    bouncer_y = (float) (SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0);
    direction[RT] = true;
}

void bouncer_change_direction() {
    unsigned short int dir;
    for (dir = 0; dir < 4; ++dir) {
        if (direction[dir]) {
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
//        if (border[GAMEOVER]) {
//            return 1;
//        }
        if (border[LEFT]) {
            direction[RB] = true;
            border[LEFT] = false;
        } else if (border[FLOOR]) {
            direction[LT] = true;
            border[FLOOR] = false;
        }
    } else if (direction[RB]) {
        direction[RB] = false;
//        if (border[GAMEOVER]) {
//            return 1;
//        }
        if (border[RIGHT]) {
            direction[LB] = true;
            border[RIGHT] = false;
        } else if (border[FLOOR]) {
            direction[RT] = true;
            border[RIGHT] = false;
        }
    }
}


int bouncer_collision_decection() {
    if
/*Floor*/   ((bouncer_y + BOUNCER_SIZE >= floor_y) && ((bouncer_x >= floor_x) && (bouncer_x <= floor_x + FLOOR_W))) {
            border[FLOOR] = true;
            bouncer_change_direction();
    } else if
/*Left*/    (bouncer_x <= 0) {
            border[LEFT] = true;
            bouncer_change_direction();
    } else if
/*Right*/   (bouncer_x + BOUNCER_SIZE >= SCREEN_W) {
            border[RIGHT] = true;
            bouncer_change_direction();
    } else if
/*Upper*/   (bouncer_y <= 0) {
            border[UPPER] = true;
            bouncer_change_direction();
    } else if
/*Gameover*/(bouncer_y >= SCREEN_H) {
            border[GAMEOVER] = true;
            //bouncer_change_direction();
            return 1;
    }
    return 0;
}

int bouncer_movement() {
    if (bouncer_collision_decection() == 1) {
        return 1;
    };
    if (direction[LT]) {
        bouncer_x -= 4.0;
        bouncer_y -= 4.0;
    }
    else if (direction[RT]) {
        bouncer_x += 4.0;
        bouncer_y -= 4.0;
    }
    else if (direction[LB]) {
        bouncer_x -= 4.0;
        bouncer_y += 4.0;
    }
    else if (direction[RB]) {
        bouncer_x += 4.0;
        bouncer_y += 4.0;
    }
    return 0;
}