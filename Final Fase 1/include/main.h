#ifndef MAIN_H
#define MAIN_H

#include "users.h"
#include "musics.h"
#include "artists.h"

#define OUTPUT_NAME "resultados"

#define OUTPUT_FILE_NAME "command%d_output.txt"

#define BUFFER_SIZE 200

typedef struct program Program;

Program* initialize_program(char **arguments);

void run_program(Program *program, char **arguments);

void free_program(Program *program);

CatalogUser *get_users_catalog(Program *program);
CatalogMusic *get_musics_catalog(Program *program);
CatalogArtist *get_artists_catalog(Program *program);

#endif