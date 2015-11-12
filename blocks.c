#include <allegro5/allegro.h>
#include <stdio.h>
#include "blocks.h"
#include "floor.h"
#include "bouncer.h"

extern unsigned short BLOCK_W;
extern unsigned short BLOCK_H;
extern unsigned short BLOCKS_ROWS;
extern int SCREEN_W;
extern int SCREEN_H;
extern int BOUNCER_SIZE;
extern float bouncer_x;
extern float bouncer_y;
extern int level;
extern float hits_counter;
extern bool debug_mode;
extern bool key[];
extern bool border[];

void print_list() {
    struct listNode* current = first;
    while (current != NULL) {
        printf("ID: %d, X: %d, Y: %d\n",current->id, current->x, current->y);
        current = current->next;
    }
}

void block_create(unsigned short x, unsigned short y) { /* Adds new node at the end of the list */
    if (first == NULL) {
        first = (struct listNode*) malloc(sizeof(struct listNode));
        first->id = 0;
        first->x = x;
        first->y = y;
        first->next = NULL;
    } else {
        struct listNode* current;
        current = first;
        while (current->next != NULL) {
            current = current->next;
        }
        struct listNode* previous = current;
        current->next = malloc(sizeof(struct listNode));
        current = current->next;
        current->id = (unsigned short) ((previous->id)+1);
        current->x = x;
        current->y = y;
        current->next = NULL;
        previous->next = current;
    }
}

void block_remove(unsigned short id) {
    if (debug_mode) {
        printf("Removing block %d.\n", id);
        printf("Before:\n");
        print_list();
    }
    struct listNode* current = first;
    if (current->id == id) {
        first = current->next;
    } else {
        struct listNode* previous;
        while (current->id != id) {
            if (current->next == NULL) {
                return;
            } else {
                previous = current;
                current = current->next;
            }
        }
        previous->next = current->next;
    }
    al_destroy_bitmap(current->bitmap);
    free(current);
    if (debug_mode) {
        printf("After:\n");
        print_list();
    }
}

void blocks_initialize(ALLEGRO_DISPLAY* display) {
    unsigned short blocks_in_row = 0;
    unsigned short row = 1;
    unsigned short count = 1;
    while (row <= BLOCKS_ROWS) {
        block_create((blocks_in_row * BLOCK_W), (unsigned short) ((SCREEN_H/2) - (row * BLOCK_H)));
        ++blocks_in_row;
        ++count;
        if (blocks_in_row * BLOCK_W > SCREEN_W) {
            ++row;
            blocks_in_row = 0;
        }
    }
    struct listNode* current = first;
    while (current != NULL) {
        current->bitmap = al_create_bitmap(BLOCK_W, BLOCK_H);
        al_set_target_bitmap(current->bitmap);
        al_clear_to_color(al_map_rgb(234,225,100));
        current = current->next;
    }
    al_set_target_bitmap(al_get_backbuffer(display));   /* Change drawing target to screen buffer */
    al_flip_display();                                  /* Print buffer to screen */
}

void blocks_destroy(struct listNode* current) {
    if (current == NULL)
        return;
    else
        blocks_destroy(current->next);
    al_destroy_bitmap(current->bitmap);
    free(current);
    first = NULL;
}

void blocks_draw() {
    struct listNode *current = first;
    while (current != NULL) {
        al_draw_bitmap(current->bitmap, current->x, current->y, 0);
        current = current->next;
    }
}

bool got_block_hit() {
    struct listNode* current = first;
    while ((current != NULL) &&
            !(((bouncer_x + BOUNCER_SIZE > current->x) && (bouncer_x < current->x + BLOCK_W)) &&
              ((bouncer_y + BOUNCER_SIZE > current->y) && (bouncer_y < current->y + BLOCK_H)))) {
        current = current->next;
    }
    if (current == NULL) {
        return false;
    } else {
        block_remove(current->id);
        return true;
    }
}

bool are_blocks_remaining() {
    return first != NULL;
}

int advance_level(ALLEGRO_DISPLAY* display) {
    // Clear various gamestate tracking variables
    hits_counter = 0;
    key[0] = false; key[1] = false; key[2] = false; key[3] = false;
    border[0] = false; border[1] = false; border[2] = false; border[3] = false; border[4] = false;
    // Setting position of bouncer and floor
    bouncer_create();
    floor_create();
    // Advance
    ++level;
    if (level > 3) {
        printf("[INFO] Congratulations, you have completed the game!\n");
        return 1;
    } else {
        blocks_destroy(first);
        BLOCKS_ROWS = (unsigned short) (level * 4);
        blocks_initialize(display);
        printf("[INFO] LEVEL: %d\n", level);
        return 0;
    }
}