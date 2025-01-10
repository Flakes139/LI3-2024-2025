#include <glib.h>
#include "history.h"
#include "catalogHistory.h"
#include <stdio.h>
#include <utils.h>

struct catalogHistory {
    GHashTable *histories;
};

CatalogHistory *initialize_history_catalog() {
    CatalogHistory *catalog = (CatalogHistory *)malloc(sizeof(CatalogHistory));
    catalog->histories = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_history);
    return catalog;
}

void free_history_catalog(CatalogHistory *catalog) {
    g_hash_table_destroy(catalog->histories);
    free(catalog);
}

void insert_history(CatalogHistory *catalog, History *history) {
    g_hash_table_insert(catalog->histories, get_history_id(history), history);
}

int exists_history(char *history_id, CatalogHistory *catalog) {
    return g_hash_table_contains(catalog->histories, history_id);
}

int count_music_reproductions(CatalogHistory *catalog, char* music_id) {
    int count = 0;
    GHashTableIter iter;
    gpointer key, value;
    
    g_hash_table_iter_init(&iter, catalog->histories);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        History *history = (History *)value;
        char *curr_music_id = get_history_music_id(history);
        
        if (strcmp(curr_music_id, music_id) == 0) {
            count++;
        }
        
        free(curr_music_id);
    }
    
    return count;
}

GHashTable* build_music_reproductions_cache(CatalogHistory *catalog) {
    GHashTable* cache = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free);
    if (!cache) return NULL;
    
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, catalog->histories);
    
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        History* history = (History*)value;
        char* music_id = get_history_music_id(history);
        if (!music_id) continue;
        
        int* count = g_hash_table_lookup(cache, music_id);
        if (!count) {
            count = malloc(sizeof(int));
            if (!count) {
                free(music_id);
                continue;
            }
            *count = 0;
            g_hash_table_insert(cache, music_id, count);
        } else {
            free(music_id);
        }
        
        // Conta uma reprodução por entrada no histórico
        (*count)++;
    }
    
    return cache;
}