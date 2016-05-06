#include <allegro5/allegro.h>
#include <stdio.h>
#include "config_file.h"

extern float FPS;
extern int SCREEN_W;
extern int SCREEN_H;
extern char difficulty;
extern float bouncer_speed;
extern bool debug_mode;
extern char* CONFIGPATH;
struct stack* root = 0;

void push(char* name, char* value) {
    struct stack* new;
    new = malloc(sizeof(struct stack));
    new->next = root;
    new->name = name;
    new->value = value;
    root = new;
}

struct stack* pop() {
    struct stack *val;
    val = root;
    if (root)
        root = root->next;
    return val;
}

int write_default_config(FILE* fp) {
    printf("[INFO] Creating a default config file...");
    if ((fp = fopen(CONFIGPATH, "w"))) {
        fprintf(fp, "[Gameplay]\n");
        fprintf(fp, "SlowMotion=0\n");
        fprintf(fp, "Difficulty=%c\n",difficulty);
        fprintf(fp, "Debug=%d\n",debug_mode);
        fprintf(fp, "[Resolution]\n");
        fprintf(fp, "Width=%d\n",SCREEN_W);
        fprintf(fp, "Height=%d\n",SCREEN_H);
        fclose(fp);
        printf(" OK.\n");
        return 0;
    } else {
        fprintf(stderr, "\r[ERROR] An error occured during writing the default configuration file.\n");
        return -1;
    }
}

void load_config_from_file() {
    char* settName = NULL;
    char* settValue = NULL;
    char buffer[50];
    char currChar;
    size_t pos = 0;
    bool isFoundEqSign = 0;
    FILE* fp;

    if ((fp = fopen(CONFIGPATH, "r"))) {
        while ((currChar = (char) fgetc(fp)) != EOF) {
            switch (currChar) {
                case '=': {
                    settName = strndup(buffer, pos);
                    pos = 0;
                    isFoundEqSign = 1;
                    break;
                }
                case '\n': {
                    if (isFoundEqSign == 1) {
                        settValue = strndup(buffer, pos);
                        push(settName, settValue);
                    } else if (strndup(buffer, pos)[0] != '[') {
                        fprintf(stderr, "[ERROR] Error parsing the config file: No '=' found in the current line.\n");
                    }
                    pos = 0;
                    isFoundEqSign = 0;
                    break;
                }
                default: {
                    buffer[pos] = currChar;
                    pos++;
                }
            }
        }
        fclose(fp);
    }
    else {
        write_default_config(fp);
    }
}

void process_config() {
    struct stack *sett;
    printf("[INFO] Loading configuration...\n");
    for (sett = pop(); sett != NULL; sett = pop()) {
        printf("[CONFIG] %s = %s\n", sett->name, sett->value);
        if ((strcmp(sett->name, "SlowMotion") == 0) && (strcmp(sett->value, "1") == 0)) {
            FPS = 30;
        } else if ((strcmp(sett->name, "Difficulty") == 0)) {
            difficulty = sett->value[0];
            if (difficulty == '2') {
                bouncer_speed = 8.0;
            }
        } else if ((strcmp(sett->name, "Width") == 0)) {
            SCREEN_W = atoi(sett->value);
        } else if ((strcmp(sett->name, "Height") == 0)) {
            SCREEN_H = atoi(sett->value);
        } else if ((strcmp(sett->name, "Debug") == 0)) {
            debug_mode = (bool) atoi(sett->value);
        }
        free(sett->name);
        free(sett->value);
        free(sett);
    }
    printf("[INFO] Configuration loaded.\n");
}

