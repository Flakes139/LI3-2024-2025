#ifndef MUSICS_H
#define MUSICS_H

#include "music.h"
#include "musics.h"
#include <glib.h>

typedef struct catalogMusic CatalogMusic;

CatalogMusic *initialize_musics_catalog();

void free_musics_catalog(CatalogMusic *catalog);

void insert_music(CatalogMusic *catalog, Music *music);

GHashTable *get_discography_duration_by_artist_table(void *catalog);

#endif
