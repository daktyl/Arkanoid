#ifndef ALLEGRO_CONFIG_FILE_H
#define ALLEGRO_CONFIG_FILE_H

struct stack {
    struct stack* next;
    char* name;
    char* value;
} *root;

// Writes setting name and value to the stack (name - setting name, value - seting value).
void push(char* name, char* value);

// Reads and deletes setting name and value from the stack
struct stack* pop();

// Writes the default config file if it wasn't found in the game directory. Returns -1 on fail.
int write_default_config(FILE* fp);

// Reads the configuration file and uses 'push' function to put in onto
// temporary stack for later processing.
void load_config_from_file();

// Reads the configuration settings from the stack and applies them to the game.
// Writes error on the stderr if encountered an error in parsing the config file.
void process_config();

#endif //ALLEGRO_CONFIG_FILE_H
