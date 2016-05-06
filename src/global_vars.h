#ifndef ALLEGRO_GLOBAL_VARS_H
#define ALLEGRO_GLOBAL_VARS_H

float FPS = 60;
int SCREEN_W = 1024;
int SCREEN_H = 768;
int FLOOR_W = 150;
int FLOOR_H = 5;
int BOUNCER_SIZE = 8;
unsigned short BLOCK_W = 50;
unsigned short BLOCK_H = 20;
unsigned short BLOCKS_ROWS = 1;
float floor_x;
float floor_y;
float bouncer_x;
float bouncer_y;
float bouncer_speed = 7.0;
float bouncer_bonusspeed = 0.0;
float angle_multiplier = 1.0;
float hits_counter = 0.0;
char* CONFIGPATH = "config.ini";
char difficulty = '1';
int level = 0;
bool rand_init = 0;
bool debug_mode = 0;
enum MYKEYS { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };
bool key[4] = {false, false, false, false};  // Holds information about keypresses

#endif //ALLEGRO_GLOBAL_VARS_H
