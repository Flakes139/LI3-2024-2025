#include <glib.h>
#include "artist.h"
#include "catalogArtist.h"
#include <stdio.h>
#include <utils.h>

struct catalogArtist {
    GHashTable *artists;
    GPtrArray *artists_array;
};

CatalogArtist *initialize_artists_catalog() {
    CatalogArtist *catalog = (CatalogArtist *)malloc(sizeof(CatalogArtist));
    catalog->artists = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_artist);
    catalog->artists_array = g_ptr_array_new();
    return catalog;
}

void free_artists_catalog(CatalogArtist *catalog) {
    g_ptr_array_free(catalog->artists_array, TRUE);
    g_hash_table_destroy(catalog->artists);
    free(catalog);
}

void insert_artist(CatalogArtist *catalog, Artist *artist) {
    g_hash_table_insert(catalog->artists, get_artist_id(artist), artist);
}

void sort_artists_by_discography_duration(CatalogArtist *catalog, void *musics_catalog, FetchArtistDiscographyDurationCache *fetch_artist_discography_duration_cache) {
    GHashTable *duration_cache = fetch_artist_discography_duration_cache(musics_catalog);
    
    GHashTableIter artist_iter;
    gpointer artist_key, artist_value;
    g_hash_table_iter_init(&artist_iter, catalog->artists);

    while (g_hash_table_iter_next(&artist_iter, &artist_key, &artist_value)) {
        Artist *artist = (Artist *)artist_value;
        char *artist_id = get_artist_id(artist);
        int *discography_duration = g_hash_table_lookup(duration_cache, artist_id);
        g_free(artist_id);

        set_artist_discography_duration(artist, discography_duration ? *discography_duration : 0);
    }

    g_ptr_array_set_size(catalog->artists_array, 0);
    g_hash_table_iter_init(&artist_iter, catalog->artists);

    while (g_hash_table_iter_next(&artist_iter, &artist_key, &artist_value)) {
        Artist *artist = (Artist *)artist_value;
        g_ptr_array_add(catalog->artists_array, artist);
    }

    g_ptr_array_sort(catalog->artists_array, (GCompareFunc)compare_artists_by_discography_duration);

    g_hash_table_foreach_remove(duration_cache, free_key_value_pair, NULL);
    g_hash_table_destroy(duration_cache);
}


GPtrArray *get_artists_array(CatalogArtist *catalog) {
    return catalog->artists_array;
}

int compare_artists_by_discography_duration(gconstpointer *a1, gconstpointer *a2) {
    Artist *artist1 = *(Artist **)a1;
    Artist *artist2 = *(Artist **)a2;

    return get_artist_discography_duration(artist2) - get_artist_discography_duration(artist1);
}

int exists_artist(char *artist_id, CatalogArtist *catalog) {
    return g_hash_table_contains(catalog->artists, artist_id);
}

Artist* get_artist_by_id(CatalogArtist *catalog, char* artist_id) {
    return g_hash_table_lookup(catalog->artists, artist_id);
}

GPtrArray* get_artist_groups(CatalogArtist *catalog, char* artist_id) {
    GPtrArray* groups = g_ptr_array_new_with_free_func(g_free);
    
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, catalog->artists);
    
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Artist* curr_artist = (Artist*)value;
        if (get_artist_type(curr_artist) == GROUP) {
            char* constituents = get_artist_id_constituent(curr_artist);
            if (strstr(constituents, artist_id) != NULL) {
                g_ptr_array_add(groups, get_artist_id(curr_artist));
            }
            free(constituents);
        }
    }
    
    return groups;
} 

GHashTable* build_artist_groups_cache(CatalogArtist *catalog) {
    GHashTable* cache = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)g_ptr_array_unref);
    
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, catalog->artists);
    
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Artist* curr_artist = (Artist*)value;
        if (get_artist_type(curr_artist) == GROUP) {
            char* constituents = get_artist_id_constituent(curr_artist);
            // Para cada constituinte
            char* copy = strdup(constituents);
            char* token = strtok(copy + 2, "', ]");  // Skip [ e primeira '
            
            while (token != NULL) {
                GPtrArray* groups = g_hash_table_lookup(cache, token);
                if (!groups) {
                    groups = g_ptr_array_new_with_free_func(g_free);
                    g_hash_table_insert(cache, strdup(token), groups);
                }
                g_ptr_array_add(groups, get_artist_id(curr_artist));
                token = strtok(NULL, "', ]");
            }
            
            free(copy);
            free(constituents);
        }
    }
    
    return cache;
}