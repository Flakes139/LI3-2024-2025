#include <glib.h>
#include "album.h"
#include "catalogAlbum.h"
#include <stdio.h>
#include <utils.h>
#include "catalogArtist.h"

struct catalogAlbum {
    GHashTable *albums;
};

CatalogAlbum *initialize_albums_catalog() {
    CatalogAlbum *catalog = (CatalogAlbum *)malloc(sizeof(CatalogAlbum));
    catalog->albums = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_album);
    return catalog;
}

void free_albums_catalog(CatalogAlbum *catalog) {
    g_hash_table_destroy(catalog->albums);
    free(catalog);
}

void insert_album(CatalogAlbum *catalog, Album *album) {
    g_hash_table_insert(catalog->albums, get_album_id(album), album);
}

int exists_album(char *album_id, CatalogAlbum *catalog) {
    return g_hash_table_contains(catalog->albums, album_id);
}

int count_individual_albums(CatalogAlbum *catalog, char* artist_id) {
    int count = 0;
    GHashTableIter iter;
    gpointer key, value;
    
    g_hash_table_iter_init(&iter, catalog->albums);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Album *album = (Album *)value;
        char *artists_str = get_album_artist_id(album);
        
        // Remove os colchetes e primeira aspa
        char *str = strdup(artists_str);
        str[strlen(str)-1] = '\0';  // Remove ]
        char *artists_list = str + 2;  // Remove [ e primeira aspa
        
        // Dividir a string em IDs individuais
        char *token = strtok(artists_list, ",");
        while (token != NULL) {
            // Limpar cada ID
            while (*token == ' ' || *token == '\'' || *token == '"') token++;
            char *end = token + strlen(token) - 1;
            while (end > token && (*end == ' ' || *end == '\'' || *end == '"')) end--;
            *(end + 1) = '\0';
            
            // Se encontrarmos o ID do artista na lista, então ele está como artista individual
            if (strcmp(token, artist_id) == 0) {
                count++;
                break;  // Não precisamos continuar verificando este álbum
            }
            
            token = strtok(NULL, ",");
        }
        
        free(str);
        free(artists_str);
    }
    return count;
}