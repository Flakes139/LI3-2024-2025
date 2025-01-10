#include <glib.h>
#include "musics.h"
#include "music.h"
#include <stdio.h>  

struct catalogMusic 
{
  GHashTable *musics;
};

CatalogMusic *initialize_musics_catalog(){
    CatalogMusic *catalog = (CatalogMusic *)malloc(sizeof(CatalogMusic));
    catalog->musics = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_music);
    return catalog;
}

void free_musics_catalog(CatalogMusic *catalog){
    g_hash_table_destroy(catalog->musics);
    free(catalog);
}

void insert_music(CatalogMusic *catalog, Music *music){
    g_hash_table_insert(catalog->musics, get_id(music), music);
}

GHashTable *get_discography_duration_by_artist_table(void *catalog) {
    GHashTable *duration_cache = g_hash_table_new(g_str_hash, g_str_equal);

    GHashTableIter music_iter;
    gpointer music_key, music_value;
    g_hash_table_iter_init(&music_iter, ((CatalogMusic*)catalog)->musics);

    while (g_hash_table_iter_next(&music_iter, &music_key, &music_value)) {
        Music *music = (Music *)music_value;
        char *artist_ids = get_music_artist_id(music);

        char *start = strchr(artist_ids, '[');
        char *end = strchr(artist_ids, ']');

        if (start != NULL && end != NULL && end > start) {
            size_t length = end - start - 2;
            char *inner_ids = g_strndup(start + 2, length);

            char *token = strtok(inner_ids, "',");
            while (token != NULL) {
                char *artist_id = g_strstrip(g_strdup(token));
                
                int *duration_sum = g_hash_table_lookup(duration_cache, artist_id);
                if (duration_sum == NULL) {
                    duration_sum = malloc(sizeof(int));
                    *duration_sum = 0;
                    g_hash_table_insert(duration_cache, g_strdup(artist_id), duration_sum);
                }

                *duration_sum += get_duration(music);

                g_free(artist_id);
                token = strtok(NULL, "',");
            }

            g_free(inner_ids);
        }

        g_free(artist_ids);
    }

    return duration_cache;
}