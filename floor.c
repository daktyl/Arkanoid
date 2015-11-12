#include "floor.h"

extern int SCREEN_W;
extern int SCREEN_H;
extern int FLOOR_W;
extern int FLOOR_H;
extern float floor_x;
extern float floor_y;

void floor_create() {
    floor_x = (float) (SCREEN_W / 2.0 - FLOOR_W / 2.0);
    floor_y = (float) (SCREEN_H*0.9 - FLOOR_H);
}