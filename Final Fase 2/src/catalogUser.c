#include <glib.h>
#include "catalogUser.h"
#include "user.h"
#include "utils.h"

struct catalogUser {
    GHashTable *users;
    GPtrArray *users_array;  // Novo campo
};

CatalogUser *initialize_users_catalog() {
    CatalogUser *catalog = (CatalogUser *)malloc(sizeof(CatalogUser));
    catalog->users = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_user);
    catalog->users_array = g_ptr_array_new_full(10, free);  // Inicializar array
    return catalog;
}

void free_users_catalog(CatalogUser *catalog) {
    g_ptr_array_free(catalog->users_array, TRUE);  // Liberar array
    g_hash_table_destroy(catalog->users);
    free(catalog);
}

void insert_user(CatalogUser *catalog, User *user){
    g_hash_table_insert(catalog->users, get_username(user), user);
}

User *catalog_get_user_by_username(CatalogUser *catalog, char *username) {
  return g_hash_table_lookup(catalog->users, username);
}

int exists_user(char *username, CatalogUser *catalog) {
  return g_hash_table_contains(catalog->users, username);
}

GPtrArray *get_users_by_age_range(CatalogUser *catalog, int min_age, int max_age) {
    GPtrArray *filtered_users = g_ptr_array_new_full(10, free_user);
    
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, catalog->users);
    
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        User *user = (User *)value;
        char *birth_date = get_birth_date(user);
        int age = years_between(birth_date, CURRENT_DATE);
        free(birth_date);

        if (age >= min_age && age <= max_age) {
            g_ptr_array_add(filtered_users, copy_user(user));
        }
    }
    
    return filtered_users;
}

GPtrArray* get_liked_songs_from_users(GPtrArray *users) {
    GPtrArray *liked_songs = g_ptr_array_new_full(10, free);
    
    for (guint i = 0; i < users->len; i++) {
        User *user = g_ptr_array_index(users, i);
        char *songs = get_liked_songs_ids(user);
        g_ptr_array_add(liked_songs, songs);
    }
    
    return liked_songs;
}