#ifndef ARTISTS_H
#define ARTISTS_H

#include "artist.h"
#include "artists.h"
#include <glib.h>

typedef struct catalogArtist CatalogArtist;

typedef GHashTable *(FetchArtistDiscographyDurationCache)(void*);

CatalogArtist *initialize_artists_catalog();

void free_artists_catalog(CatalogArtist *catalog);

void insert_artist(CatalogArtist *catalog, Artist *artist);

void sort_artists_by_discography_duration(CatalogArtist *catalog, void *musics_catalog, FetchArtistDiscographyDurationCache *fetch_artist_discography_duration);

GPtrArray *get_artists_array(CatalogArtist *catalog);

int compare_artists_by_discography_duration(gconstpointer *a1, gconstpointer *a2);

#endif