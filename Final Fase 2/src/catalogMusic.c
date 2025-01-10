#include <glib.h>
#include "catalogMusic.h"
#include "music.h"
#include <stdio.h>  

struct catalogMusic 
{
  GHashTable *musics;
};

struct genreLikes {
    char* genre;
    int likes;
};

GenreLikes* create_genre_likes(char* genre, int likes) {
    GenreLikes* gl = malloc(sizeof(GenreLikes));
    gl->genre = strdup(genre);
    gl->likes = likes;
    return gl;
}

char* get_genre_from_likes(GenreLikes* gl) {
    return strdup(gl->genre);
}

int get_likes_count(GenreLikes* gl) {
    return gl->likes;
}

void free_genre_likes(void* gl_void) {
    GenreLikes* gl = (GenreLikes*)gl_void;
    if (gl) {
        if (gl->genre) free(gl->genre);
        free(gl);
    }
}

int compare_genre_likes(gconstpointer a, gconstpointer b) {
    GenreLikes *genre1 = *(GenreLikes **)a;
    GenreLikes *genre2 = *(GenreLikes **)b;
    
    if (genre2->likes != genre1->likes) {
        return genre2->likes - genre1->likes;
    }
    return strcmp(genre1->genre, genre2->genre);
}

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

int exists_music(char *music_id, CatalogMusic *catalog){
    return g_hash_table_contains(catalog->musics, music_id);
}




GPtrArray* get_genre_likes_from_users(CatalogMusic *catalog, GPtrArray *liked_songs) {
        GHashTable *genre_counts = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free);    // Processar cada lista de músicas curtidas
    for (guint i = 0; i < liked_songs->len; i++) {
        char *songs_list = g_ptr_array_index(liked_songs, i);
        
        // Parse da lista de músicas
        char *songs_copy = strdup(songs_list);
        songs_copy[strlen(songs_copy) - 1] = '\0';  // Remove ]
        char *song_id = strtok(songs_copy + 2, "', ");  // Remove [ e primeira '
        
        while (song_id != NULL) {
            // Remove aspas se presentes
            if (song_id[0] == '\'') {
                song_id++;
                song_id[strlen(song_id)-1] = '\0';
            }
            
            Music *music = g_hash_table_lookup(catalog->musics, song_id);
            if (music) {
                char *genre = get_genre(music);
                
                int *count = g_hash_table_lookup(genre_counts, genre);
                if (count == NULL) {
                    count = malloc(sizeof(int));
                    *count = 0;
                    g_hash_table_insert(genre_counts, strdup(genre), count);
                }
                (*count)++;
                
                free(genre);
            }
            song_id = strtok(NULL, "', ");
        }
        
        free(songs_copy);
    }
    
    // Converter hash table para array ordenado
    GPtrArray *genre_array = g_ptr_array_new_full(10, free_genre_likes);
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, genre_counts);
    
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        GenreLikes *gl = malloc(sizeof(GenreLikes));
        gl->genre = strdup(key);
        gl->likes = *(int*)value;
        g_ptr_array_add(genre_array, gl);
    }
    
    g_ptr_array_sort(genre_array, compare_genre_likes);
    
    g_hash_table_destroy(genre_counts);
    
    return genre_array;
}
GPtrArray* get_artist_musics(CatalogMusic *catalog, char* artist_id) {
    GPtrArray* artist_musics = g_ptr_array_new();
    
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, catalog->musics);
    
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Music *music = (Music *)value;
        char *artists_str = get_music_artist_id(music);
        
        // Manipular a string adequadamente
        char *str = strdup(artists_str);
        str[strlen(str)-1] = '\0'; // Remove ]
        char *token = strtok(str + 2, ","); // Remove [ e pega primeiro token
        
        while (token != NULL) {
            // Limpar o token
            while (*token == ' ' || *token == '"' || *token == '\'') token++;
            char *end = token + strlen(token) - 1;
            while (end > token && (*end == ' ' || *end == '"' || *end == '\'')) end--;
            *(end + 1) = '\0';
            
            if (strcmp(token, artist_id) == 0) {
                g_ptr_array_add(artist_musics, music);
                break;
            }
            token = strtok(NULL, ",");
        }
        
        free(str);
        free(artists_str);
    }
    
    return artist_musics;
}