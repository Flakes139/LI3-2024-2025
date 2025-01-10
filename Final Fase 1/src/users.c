#include <glib.h>
#include "users.h"
#include "user.h"

struct catalogUser 
{
  GHashTable *users;
};

CatalogUser *initialize_users_catalog(){
    CatalogUser *catalog = (CatalogUser *)malloc(sizeof(CatalogUser));
    catalog->users = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_user);
    return catalog;
}

void free_users_catalog(CatalogUser *catalog){
    g_hash_table_destroy(catalog->users);
    free(catalog);
}

void insert_user(CatalogUser *catalog, User *user){
    g_hash_table_insert(catalog->users, get_username(user), user);
}

User *catalog_get_user_by_username(CatalogUser *catalog, char *username) {
  return g_hash_table_lookup(catalog->users, username);
}