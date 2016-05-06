#ifndef ALLEGRO_BLOCKS_H
#define ALLEGRO_BLOCKS_H

struct listNode {
    unsigned short id;
    unsigned short x;
    unsigned short y;
    ALLEGRO_BITMAP* bitmap;
    struct listNode* next;
} *first;

// Adds a block to the linked list (x, y - block coordinates).
void block_create(unsigned short x, unsigned short y);

// Removes a block from the linked list (id - ID of the block to remove).
void block_remove(unsigned short id);

// Sets bitmap to blocks after creating them (uses block_create as a backend)
// and leaves display as a drawing target.
void blocks_initialize(ALLEGRO_DISPLAY* display);

// Removes all blocks from memory (from linked list).
// Should be called with "first" parameter which is the head of a list.
void blocks_destroy(struct listNode* current);

// Draws all blocks included in the linked list on display.
void blocks_draw();

// Returns true if the current position of a bouncer does interfere with any block in the list.
bool got_block_hit();

// Returns true if there are any remaining blocks in the linked list.
bool are_blocks_remaining();

// Moves player to the next level. If the current level is greater than 3, ends the game.
int advance_level(ALLEGRO_DISPLAY* display);

#endif //ALLEGRO_BLOCKS_H
